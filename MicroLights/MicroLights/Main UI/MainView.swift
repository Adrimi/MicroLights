//
//  ContentView.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import SwiftUI
import Combine

struct MainView: View {
  
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
    MainView(
      store: ContentViewStore(
        title: "Micro Lights",
        items: [],
        features: []
      )
    )
  }
}
