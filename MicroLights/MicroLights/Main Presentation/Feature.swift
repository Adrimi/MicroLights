//
//  Feature.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 27/05/2021.
//

import Foundation


struct Feature: Hashable {
  static func == (lhs: Feature, rhs: Feature) -> Bool {
    lhs.id == rhs.id
  }
  
  func hash(into hasher: inout Hasher) {
    hasher.combine(id)
  }
  
  let id: UUID = UUID()
  let name: String
  let action: () -> Void
}
