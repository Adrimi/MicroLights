//
//  ContentView.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import SwiftUI
import Combine

class ConnectableDevice: ObservableObject, Identifiable {
  let id: UUID
  let name: String
  @Published var state: MQTTServiceState
  var cancellable: AnyCancellable?
  let selected: () -> Void
  let sampleMessage: () -> Void
  let clear: () -> Void
  
  init(id: UUID, name: String, state: AnyPublisher<MQTTServiceState, Never>, selected: @escaping () -> Void, sampleMessage: @escaping () -> Void, clear: @escaping () -> Void) {
    self.id = id
    self.name = name
    self.state = .disconnected
    self.selected = selected
    self.sampleMessage = sampleMessage
    self.clear = clear
    self.cancellable = state
      .receive(on: RunLoop.main)
      .sink(receiveValue: { [weak self] state in
      self?.state = state
    })
  }
}



class ContentViewStore: ObservableObject {
  @Published var connectableItems: [ConnectableDevice]
  let title: String
  let sendSampleMessage: () -> Void
  let clearEffect: () -> Void
  
  init(
    title: String,
    items: [ConnectableDevice],
    sendSampleMessage: @escaping () -> Void,
    clearEffect: @escaping () -> Void
  ) {
    self.connectableItems = items
    self.title = title
    self.sendSampleMessage = sendSampleMessage
    self.clearEffect = clearEffect
  }
}


struct ConnectableDeviceView: View {
  @ObservedObject var store: ConnectableDevice
  
  var body: some View {
    HStack {
      Button(action: store.selected) {
        Text("\(store.name)")
      }
      .buttonStyle(PlainButtonStyle())
      
      Spacer()
      
      mapState(store.state)
    }
  }
  
  @ViewBuilder
  func mapState(_ state: MQTTServiceState) -> some View {
    switch state {
      case .connecting:
        ActivityIndicatorView(isAnimating: .constant(true), style: .medium)
        
      case .connected:
        RoundedRectangle(cornerRadius: 11)
          .frame(width: 22, height: 22)
          .foregroundColor(.green)
        
      case .disconnecting:
        RoundedRectangle(cornerRadius: 11)
          .frame(width: 22, height: 22)
          .foregroundColor(.orange)
        
      default:
        EmptyView()
    }
  }

}

struct ContentView: View {
  
  @ObservedObject var store: ContentViewStore
  
  var body: some View {
    NavigationView {
      List {
        Section(header: Text("Devices")) {
          ForEach(store.connectableItems) { device in
            ConnectableDeviceView(store: device)
          }
        }
        
        Section(header: Text("Actions")) {
          Button(action: store.sendSampleMessage) {
            Text("Send sample message")
          }
          .buttonStyle(PlainButtonStyle())
          
          Button(action: store.clearEffect) {
            Text("Clear effect and disconnect")
          }
          .buttonStyle(PlainButtonStyle())
        }
      }
      .listStyle(InsetGroupedListStyle())
      .navigationTitle(store.title)
    }
  }
}

struct ContentView_Previews: PreviewProvider {
  static var previews: some View {
    ContentView(
      store: ContentViewStore(
        title: "Micro Lights",
        items: [], sendSampleMessage: {}, clearEffect: {}
      )
    )
  }
}
