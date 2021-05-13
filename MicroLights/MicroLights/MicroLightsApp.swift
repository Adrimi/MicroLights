//
//  MicroLightsApp.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import SwiftUI
import Combine
import Moscapsule

@main
struct MicroLightsApp: App {
  @State private var items: [ConnectableDevice] = []
  @State private var cancellable: Cancellable?
  
  var body: some Scene {
    WindowGroup {
      contentView
    }
  }
  
  private var contentView: some View {
    ContentView(
      store: ContentViewStore(
        title: "List of items",
        items: items
      )
    )
    .onAppear(perform: scanLocalNetwork)
  }
  
  private func scanLocalNetwork() {
    cancellable = makeLocalNetworkScanner()
      .sink { devices in
        self.items = devices.map { device in
          ConnectableDevice(id: UUID(), name: device, selected: {
            connectTo(device)
          })
        }
      }
  }
  
  private func connectTo(_ device: String) {
    let config = MQTTConfig(clientId: "iOS", host: device, port: 1883, keepAlive: 60)
    let service = MQTTService(config: config)
    service.connect()
  }
  
  private func makeLocalNetworkScanner() -> AnyPublisher<[String], Never> {
    MQTTBrowser()
      .listenDevices(using: MQTTBrowser.tcpMqttBrowser)
      .tryMap(MQTTBrowserMapper.map)
      .replaceError(with: [])
      .eraseToAnyPublisher()
  }
}
