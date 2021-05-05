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
}

class ContentViewStore: ObservableObject {
    @Published var connectableItems: [ConnectableDevice]
    let title: String
    
    init(title: String, items: [ConnectableDevice]) {
        self.connectableItems = items
        self.title = title
    }
}

struct ContentView: View {
    
    let store: ContentViewStore
    
    var body: some View {
        NavigationView {
            List {
                ForEach(store.connectableItems) { device in
                    Text("\(device.name)")
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
                title: "List of devices",
                items: [
                    ConnectableDevice(id: UUID(), name: "esp8266"),
                    ConnectableDevice(id: UUID(), name: "esp8266"),
                ]
            )
        )
    }
}
