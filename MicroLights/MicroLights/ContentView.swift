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
  let rainbowEffect: () -> Void
  let turnOff: () -> Void
  
  init(id: UUID, name: String, state: AnyPublisher<MQTTServiceState, Never>, selected: @escaping () -> Void, rainbowEffect: @escaping () -> Void, turnOff: @escaping () -> Void) {
    self.id = id
    self.name = name
    self.state = .disconnected
    self.selected = selected
    self.rainbowEffect = rainbowEffect
    self.turnOff = turnOff
    self.cancellable = state
      .receive(on: RunLoop.main)
      .sink(receiveValue: { [weak self] state in
      self?.state = state
    })
  }
}

struct Feature: Hashable {
  static func == (lhs: Feature, rhs: Feature) -> Bool {
    lhs.id == rhs.id
  }
  
  func hash(into hasher: inout Hasher) {
    hasher.combine(id)
  }
  
  let id: UUID = UUID()
  let name: String
  let action: () -> Void
}

class ContentViewStore: ObservableObject {
  let title: String
  @Published var connectableItems: [ConnectableDevice]
  let features: [Feature]
  
  init(
    title: String,
    items: [ConnectableDevice],
    features: [Feature]
  ) {
    self.connectableItems = items
    self.title = title
    self.features = features
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
        Section(header: Text("Actions")) {
          ForEach(store.features, id: \.self) { f in
            Button(action: f.action) {
              Text(f.name)
            }
            .buttonStyle(PlainButtonStyle())
          }
        }
        
        Section(header: Text("Devices")) {
          ForEach(store.connectableItems) { device in
            ConnectableDeviceView(store: device)
          }
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
        items: [],
        features: []
      )
    )
  }
}
