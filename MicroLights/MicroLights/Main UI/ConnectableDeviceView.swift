//
//  ConnectableDeviceView.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 27/05/2021.
//

import SwiftUI

struct ConnectableDeviceView: View {
  @ObservedObject var store: ConnectableDevice
  
  var body: some View {
    HStack {
      Button(action: store.selected) {
        Text("\(store.name)")
      }
      .buttonStyle(PlainButtonStyle())
      
      Spacer()
      
      mapState(store.state)
    }
  }
  
  @ViewBuilder
  func mapState(_ state: MQTTServiceState) -> some View {
    switch state {
      case .connecting:
        ActivityIndicatorView(isAnimating: .constant(true), style: .medium)
        
      case .connected:
        RoundedRectangle(cornerRadius: 11)
          .frame(width: 22, height: 22)
          .foregroundColor(.green)
        
      case .disconnecting:
        RoundedRectangle(cornerRadius: 11)
          .frame(width: 22, height: 22)
          .foregroundColor(.orange)
        
      default:
        EmptyView()
    }
  }
  
}

