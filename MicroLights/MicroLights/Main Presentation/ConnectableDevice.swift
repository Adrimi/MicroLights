//
//  ConnectableDevice.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 27/05/2021.
//

import SwiftUI
import Combine

class ConnectableDevice: ObservableObject, Identifiable {
  let id: UUID
  let name: String
  @Published var state: MQTTServiceState
  var cancellable: AnyCancellable?
  let selected: () -> Void
  
  init(id: UUID, name: String, state: AnyPublisher<MQTTServiceState, Never>, selected: @escaping () -> Void) {
    self.id = id
    self.name = name
    self.state = .disconnected
    self.selected = selected
    self.cancellable = state
      .receive(on: RunLoop.main)
      .sink(receiveValue: { [weak self] state in
        self?.state = state
      })
  }
}
