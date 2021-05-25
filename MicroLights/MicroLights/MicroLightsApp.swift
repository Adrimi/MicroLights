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
  @State private var networkScannerTask: Cancellable?
  
  var body: some Scene {
    WindowGroup {
      contentView
    }
  }
  
  private var contentView: some View {
    ContentView(
      store: ContentViewStore(
        title: "Micro Lights",
        items: items,
        sendSampleMessage: { items.filter { $0.state == .connected }.forEach { $0.sampleMessage() } },
        clearEffect: { items.filter { $0.state == .connected }.forEach { $0.clear() } }
      )
    )
    .onAppear(perform: scanLocalNetwork)
  }
  
  private func scanLocalNetwork() {
    networkScannerTask = makeLocalNetworkScanner()
      .removeDuplicates()
      .sink { devices in
        self.items = devices.map { device in
          let service = MQTTService()
           
          return ConnectableDevice(
            id: UUID(),
            name: device,
            state: service.state.eraseToAnyPublisher(),
            selected: {
              if service.state.value == .disconnected {
                let config = MQTTConfig(clientId: "iOS", host: device, port: 1883, keepAlive: 60)
                service.connect(with: config)
              } else if service.state.value == .connected {
                service.disconnect()
              }
            },
            sampleMessage: { service.sendSampleMessage() },
            clear: { service.clearEffect() })
        }
      }
  }
  
  private func makeLocalNetworkScanner() -> AnyPublisher<[String], Never> {
    MQTTBrowser()
      .listenDevices(using: MQTTBrowser.tcpMqttBrowser)
      .tryMap(MQTTBrowserMapper.map)
      .replaceError(with: [])
      .eraseToAnyPublisher()
  }
}
