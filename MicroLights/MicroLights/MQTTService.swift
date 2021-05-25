//
//  MQTTService.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 13/05/2021.
//

import Foundation
import Moscapsule
import Combine

enum MQTTServiceState {
  case connecting
  case connected
  case disconnecting
  case disconnected
}

class MQTTService {
  private var client: MQTTClient?
  
  var state = PassthroughSubject<MQTTServiceState, Never>()
  
  func connect(with cfg: MQTTConfig) {
    let config = cfg
    config.onConnectCallback = { [weak self] _ in
      self?.state.send(.connected)
    }
    config.onDisconnectCallback = { [weak self] _ in
      self?.state.send(.disconnected)
    }
    client = MQTT.newConnection(config)
    state.send(.connecting)
  }
  
  func publish(message: String, topic: String) {
    client?.publish(string: message, topic: topic, qos: 2, retain: false)
  }
  
  func disconnect() {
    state.send(.disconnecting)
    client?.disconnect()
    client = nil
  }
}
