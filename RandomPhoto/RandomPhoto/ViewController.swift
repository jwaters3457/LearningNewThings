//
//  ViewController.swift
//  RandomPhoto
//
//  Created by James Macbook on 5/26/22.
//

import UIKit

class ViewController: UIViewController {
    let colors: Array<UIColor> = [UIColor.white,UIColor.black,UIColor.systemPink,UIColor.blue,UIColor.brown,UIColor.cyan,UIColor.darkGray,UIColor.gray,UIColor.green,UIColor.lightGray,UIColor.magenta]
    
    private let imageView: UIImageView = {
        let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFill
        imageView.backgroundColor = .white
        return imageView
    }()
    
    func getRandomPhoto() {
        let urlString =
        "https://source.unsplash.com/random/600x600"
        let url = URL(string: urlString)!
        
        guard let data = try? Data(contentsOf: url) else {
            return
        }
        imageView.image = UIImage(data: data)
    }
    
    let button: UIButton = {
        let button = UIButton()
        button.backgroundColor = UIColor.white
        button.setTitle("Random Photo", for: UIControl.State.normal)
        button.setTitleColor(.black, for: .normal)
        return button
    }()

    @objc func didTapButton(){
        getRandomPhoto()
        
        view.backgroundColor = colors.randomElement()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .systemPink
        
        view.addSubview(imageView)
        imageView.frame = CGRect(x:0,y:0,width:300,height:300)
        imageView.center = view.center
        
        view.addSubview(button)
        button.addTarget(self, action: #selector(didTapButton), for: .touchUpInside)
        
        getRandomPhoto()
        // Do any additional setup after loading the view.
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        
        button.frame = CGRect(x: 30, y: view.frame.size.height-50-view.safeAreaInsets.bottom, width:view.frame.size.width - 60, height: 55)
        
    }
}

