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
  case connect(device: String)
  case connecting
  case connected
  case publish(message: String, topic: String)
  case disconnecting
  case disconnected
}

class MQTTService {
  private let config: MQTTConfig
  private var client: MQTTClient?
  
  var state = PassthroughSubject<MQTTServiceState, Never>()
  
  init(config: MQTTConfig) {
    self.config = config
  }
  
  func connect() {
    client = MQTT.newConnection(config)
  }
  
  func publish(message: String, topic: String) {
    client?.publish(string: message, topic: topic, qos: 2, retain: false)
  }
  
  func disconnect() {
    client?.disconnect()
    client = nil
  }
}
