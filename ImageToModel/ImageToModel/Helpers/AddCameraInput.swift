//
//  CameraSetup.swift
//  ImageToModel
//
//  Created by James Macbook on 5/28/22.
//

import Foundation
import AVFoundation

extension ViewController{
    func addCameraInput(){
        guard let device = AVCaptureDevice.DiscoverySession(
            deviceTypes: [.builtInWideAngleCamera, .builtInDualCamera,.builtInTrueDepthCamera],
            mediaType:.video,
            position:.back
        ).devices.first else {
            fatalError("No Camera Device Detected")
        }
        
        let cameraInput = try! AVCaptureDeviceInput(device: device)
        self.captureSession.addInput(cameraInput)
    }
}
