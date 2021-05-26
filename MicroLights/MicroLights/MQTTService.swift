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
  var state = CurrentValueSubject<MQTTServiceState, Never>(.disconnected)
  
  func connect(with cfg: MQTTConfig) {
    let config = cfg
    config.onConnectCallback = { [weak self] _ in
      self?.state.send(.connected)
    }
    config.onDisconnectCallback = { [weak self] _ in
      self?.state.send(.disconnected)
    }
    
    state.send(.connecting)
    client = MQTT.newConnection(config)
  }
  
  func publish(message: String, topic: String = "esp/config") {
    client?.publish(string: message, topic: topic, qos: 2, retain: false)
  }
  
  func disconnect() {
    state.send(.disconnecting)
    client?.disconnect()
    client = nil
  }
  
  func clearEffect() {
    publish(message: "0:0$")
  }
  
  func simpleGreen() {
    publish(message: "1:0$")
  }
  
  func staticRainbow() {
    publish(message: "2:0$")
  }
  
  func rainbowEffect() {
    publish(message: "3:3$")
  }
  
  
}
