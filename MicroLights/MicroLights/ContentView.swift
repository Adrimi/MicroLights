//
//  ContentView.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import SwiftUI
import Combine

struct ConnectableDevice: Identifiable {
  let id: UUID
  let name: String
  let selected: () -> Void
}

class ContentViewStore: ObservableObject {
  @Published var connectableItems: [ConnectableDevice]
  let title: String
  let sendSampleMessage: () -> Void
  let clearEffect: () -> Void
  
  init(title: String, items: [ConnectableDevice], sendSampleMessage: @escaping () -> Void, clearEffect: @escaping () -> Void) {
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
            Button("\(device.name)", action: device.selected)
              .buttonStyle(PlainButtonStyle())
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
}

struct ContentView_Previews: PreviewProvider {
  static var previews: some View {
    ContentView(
      store: ContentViewStore(
        title: "Micro Lights",
        items: [
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}),
          ConnectableDevice(id: UUID(), name: "esp8266", selected: {}),
        ], sendSampleMessage: {}, clearEffect: {}
      )
    )
  }
}
