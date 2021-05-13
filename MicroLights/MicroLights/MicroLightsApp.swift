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
  @State private var service: MQTTService?
  
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
        sendSampleMessage: sendSampleMessage,
        clearEffect: clearEffect
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
  
  private func sendSampleMessage() {
    service?.publish(message: "3:3$", topic: "esp/config")
  }
  
  private func clearEffect() {
    service?.publish(message: "0:0$", topic: "esp/config")
    service?.disconnect()
    service = nil
  }
  
  private func connectTo(_ device: String) {
    let config = MQTTConfig(clientId: "iOS", host: device, port: 1883, keepAlive: 60)
    service = MQTTService(config: config)
    service?.connect()
  }
  
  private func makeLocalNetworkScanner() -> AnyPublisher<[String], Never> {
    MQTTBrowser()
      .listenDevices(using: MQTTBrowser.tcpMqttBrowser)
      .tryMap(MQTTBrowserMapper.map)
      .replaceError(with: [])
      .eraseToAnyPublisher()
  }
}
