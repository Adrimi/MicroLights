//: A UIKit based Playground for presenting user interface
  
import UIKit
import PlaygroundSupport

let rgbstring = """
0 | 128 17 238
1 | 141 11 230
2 | 154 6 222
3 | 167 3 213
4 | 179 1 202
5 | 191 0 191
6 | 202 1 179
7 | 213 3 167
8 | 222 6 154
9 | 231 11 141
10 | 238 17 127
11 | 244 24 114
12 | 249 33 101
13 | 252 42 88
14 | 254 53 75
15 | 255 64 64
16 | 254 76 52
17 | 252 88 42
18 | 249 101 33
19 | 244 114 24
20 | 238 128 17
21 | 231 141 11
22 | 222 154 6
23 | 213 167 3
24 | 203 179 1
25 | 191 191 0
26 | 180 202 1
27 | 167 213 3
28 | 154 222 6
29 | 141 231 11
30 | 128 238 17
31 | 114 244 24
32 | 101 249 33
33 | 88 252 42
34 | 76 254 53
35 | 64 255 64
36 | 53 254 76
37 | 42 252 88
38 | 33 249 101
39 | 25 244 114
40 | 17 238 128
41 | 11 231 141
42 | 6 222 154
43 | 3 213 167
44 | 1 203 179
45 | 0 191 191
46 | 1 180 202
47 | 3 167 213
48 | 6 154 222
49 | 11 141 231
50 | 17 128 238
51 | 24 114 244
52 | 33 101 249
53 | 42 88 252
54 | 52 76 254
55 | 63 64 255
56 | 75 53 254
57 | 88 42 252
58 | 101 33 249
59 | 114 25 244
"""


class MyViewController : UIViewController {
    
    override func loadView() {
        self.view = UIView()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let colorStack = rgbstring
            .split(separator: "\n")
            .map { line in
                line.split(separator: "|")[1]
                    .split(separator: " ")
            }
            .map { colorArray -> UIView in
                let view = UIView()
                view.translatesAutoresizingMaskIntoConstraints = false
                NSLayoutConstraint.activate([
                    view.widthAnchor.constraint(equalToConstant: 3),
                    view.heightAnchor.constraint(equalToConstant: 100),
                ])
                
                view.backgroundColor = UIColor(
                    red: CGFloat(Int(colorArray[0])!) / 255.0,
                    green: CGFloat(Int(colorArray[1])!) / 255.0,
                    blue: CGFloat(Int(colorArray[2])!) / 255.0,
                    alpha: 1)
                return view
            }
            .reduce(into: UIStackView()) { stack, view in
                stack.addArrangedSubview(view)
            }
        colorStack.addArrangedSubview(UIView())
        colorStack.axis = .horizontal
        colorStack.alignment = .center
        colorStack.spacing = 1
        view.addSubview(colorStack)
        colorStack.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            colorStack.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            colorStack.topAnchor.constraint(equalTo: view.topAnchor),
        ])
    }
}
// Present the view controller in the Live View window
PlaygroundPage.current.liveView = MyViewController()
