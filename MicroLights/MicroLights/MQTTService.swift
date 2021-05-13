//
//  MQTTService.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 13/05/2021.
//

import Foundation
import Moscapsule

class MQTTService {
  private let config: MQTTConfig
  private var client: MQTTClient?
  
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
