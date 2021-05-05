//
//  MicroLightsApp.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import SwiftUI
import Combine

@main
struct MicroLightsApp: App {
    @State private var items: [ConnectableDevice] = []
    @State private var cancellable: Cancellable?
    
    var body: some Scene {
        WindowGroup {
            ContentView(
                store: ContentViewStore(
                    title: "List of items",
                    items: items
                )
            )
            .onAppear(perform: scanLocalNetwork)
        }
    }
    
    private func scanLocalNetwork() {
        cancellable = makeLocalNetworkScanner()
            .sink { devices in
                self.items = devices.map { item in
                    ConnectableDevice(id: UUID(), name: item)
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
