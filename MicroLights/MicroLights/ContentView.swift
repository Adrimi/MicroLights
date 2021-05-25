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
  let selected: () -> Void
  @Published var state: MQTTServiceState
  private var cancellable: AnyCancellable?
  
  init(id: UUID, name: String, selected: @escaping () -> Void, state: AnyPublisher<MQTTServiceState, Never>) {
    self.id = id
    self.name = name
    self.selected = selected
    self.state = .disconnected
    cancellable = state.sink { [weak self] state in
      self?.state = state
    }
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


struct ContentView: View {
  
  let store: ContentViewStore
  
  var body: some View {
    NavigationView {
      List {
        Section(header: Text("Devices")) {
          ForEach(store.connectableItems) { device in
            HStack {
              Button("\(device.name)", action: device.selected)
                .buttonStyle(PlainButtonStyle())
              
              Spacer()
              
              mapState(device.state)
            }
          }
        }
        
        Section(header: Text("Actions")) {
          Button("Send sample message", action: store.sendSampleMessage)
            .buttonStyle(PlainButtonStyle())
          Button("Clear effect and disconnect", action: store.clearEffect)
            .buttonStyle(PlainButtonStyle())
        }
      }
      .listStyle(InsetGroupedListStyle())
      .navigationTitle(store.title)
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

struct ContentView_Previews: PreviewProvider {
  static var previews: some View {
    ContentView(
      store: ContentViewStore(
        title: "Micro Lights",
        items: [
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}, state: Just(.connected).eraseToAnyPublisher()),
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}, state: Just(.connecting).eraseToAnyPublisher()),
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}, state: Just(.disconnecting).eraseToAnyPublisher()),
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}, state: Just(.disconnected).eraseToAnyPublisher()),
        ], sendSampleMessage: {}, clearEffect: {}
      )
    )
  }
}
