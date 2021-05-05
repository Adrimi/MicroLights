//
//  LocalNetworkScanner.swift
//  MicroLights
//
//  Created by Adrian Szymanowski on 05/05/2021.
//

import Combine
import Network

public enum LocalScannerPolicy {
    static var dataTransferProtocol: String { "tcp" }
    static var serviceProtocol: String { "mqtt" }
    static var domain: String { "local" }
}

extension MQTTBrowser {
    private static let descriptorType: String = "_\(LocalScannerPolicy.serviceProtocol)._\(LocalScannerPolicy.dataTransferProtocol)"
    
    static var tcpMqttBrowser: NWBrowser = {
        return NWBrowser(for: .bonjour(type: descriptorType, domain: LocalScannerPolicy.domain), using: .tcp)
    }()
}

extension MQTTBrowser {
    typealias Publisher = AnyPublisher<[NWBrowser.Result], Error>
    
    func listenDevices(using browser: NWBrowser) -> Publisher {
        Future { promise in
            MQTTBrowser.listen(using: browser) { result in
                if case let .success(foundDevices) = result {
                    promise(.success(foundDevices))
                }
            }
        }
        .eraseToAnyPublisher()
    }
}

class MQTTBrowser { 
    typealias Result = Swift.Result<[NWBrowser.Result], Error>
    
    static func listen(using browser: NWBrowser, completion: @escaping (Result) -> Void) {
        browser.browseResultsChangedHandler = { results, changes in
            let recentlyAdded = changes.compactMap { change -> NWBrowser.Result? in
                if case let .added(result) = change { return result }
                else { return nil }
            }
            completion(.success(recentlyAdded))
        }
        browser.start(queue: .global(qos: .userInitiated))
    }
}

class MQTTBrowserMapper {
    enum MapError: Error {
        case invalidData
    }
    
    static func map(_ results: [NWBrowser.Result]) throws -> [String] {
        try results.compactMap { result in
            try self.map(result)
        }
    }
    
    static private func map(_ result: NWBrowser.Result) throws -> String {
        guard let result = parse(result) else {
            throw MapError.invalidData
        }
        return result
    }
    
    private static func parse(_ result: NWBrowser.Result) -> String? {
        String(describing: result)
            .replacingOccurrences(of: "Result(", with: "")
            .replacingOccurrences(of: "}", with: "")
            .split(separator: ",")
            .first { $0.contains("nw:") }?
            .replacingOccurrences(of: "nw: ", with: "")
            .split(separator: ".")
            .filter { stringArrayItem in
                return ["_", "@"].allSatisfy { item in
                    !stringArrayItem.contains(item)
                }}
            .joined(separator: ".")
    }
}
