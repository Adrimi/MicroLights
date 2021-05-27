//
//  ContentViewStore.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 27/05/2021.
//

import SwiftUI
import Combine

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
