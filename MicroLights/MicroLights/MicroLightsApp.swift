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
  
  @State private var items: [(service: MQTTService, device:  ConnectableDevice)] = []
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
        items: items.map(\.device),
        features: [
          .init(name: "Rainbow", action: {
            items.execute { $0.rainbowEffect() }
          }),
          .init(name: "Static rainbow", action: {
            items.execute { $0.staticRainbow() }
          }),
          .init(name: "Simple green", action: {
            items.execute { $0.simpleGreen() }
          }),
          .init(name: "Turn Off", action: {
            items.execute { $0.clearEffect() }
          }),
        ]
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
          let id = UUID()
          
          let device = ConnectableDevice(
            id: id,
            name: device,
            state: service.state.eraseToAnyPublisher(),
            selected: {
              if service.state.value == .disconnected {
                service.connect(with: makeConfig(for: device, id: id))
              } else if service.state.value == .connected {
                service.disconnect()
              }
            })
          
          return (service, device)
        }
      }
  }
  
  private func makeConfig(for device: String, id: UUID) -> MQTTConfig {
    MQTTConfig(clientId: "iOS" + id.uuidString, host: device, port: 1883, keepAlive: 60)
  }
  
  private func makeLocalNetworkScanner() -> AnyPublisher<[String], Never> {
    MQTTBrowser()
      .listenDevices(using: MQTTBrowser.tcpMqttBrowser)
      .tryMap(MQTTBrowserMapper.map)
      .replaceError(with: [])
      .eraseToAnyPublisher()
  }
}

extension Collection where Element == (service: MQTTService, device:  ConnectableDevice) {
  func distincConnectedServices() -> [MQTTService] {
    compactMap { service, device in
      device.state == .connected ? service : nil
    }
  }
  
  func execute(_ action: (MQTTService) -> Void) {
    distincConnectedServices().forEach { action($0) }
  }
}
