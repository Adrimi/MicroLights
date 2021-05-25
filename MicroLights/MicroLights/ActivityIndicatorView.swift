//
//  Created by Adrian Szymanowski on 21/05/2021.
//

import SwiftUI

struct ActivityIndicatorView: UIViewRepresentable {
  @Binding var isAnimating: Bool
  let style: UIActivityIndicatorView.Style
  
  func makeUIView(context: UIViewRepresentableContext<ActivityIndicatorView>) -> UIActivityIndicatorView {
    return UIActivityIndicatorView(style: style)
  }
  
  func updateUIView(_ uiView: UIActivityIndicatorView, context: UIViewRepresentableContext<ActivityIndicatorView>) {
    isAnimating ? uiView.startAnimating() : uiView.stopAnimating()
  }
}

struct ActivityIndicator_Previews: PreviewProvider {
  static var previews: some View {
    ActivityIndicatorView(isAnimating: .constant(true), style: .large)
  }
}

