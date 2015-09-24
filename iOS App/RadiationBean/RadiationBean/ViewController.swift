//
//  ViewController.swift
//  RadiationBean
//
//  Created by Stuart Feichtinger on 9/23/15.
//  Copyright © 2015 Stuart Feichtinger. All rights reserved.
//

import UIKit
import CoreData

//Add UITableViewDataSource to class declaration
class ViewController: UIViewController, UITableViewDataSource {

    @IBOutlet weak var tableView: UITableView!
    func tableView(tableView: UITableView,
        numberOfRowsInSection section: Int) -> Int {
            return people.count
    }
    
    func tableView(tableView: UITableView,
        cellForRowAtIndexPath
        indexPath: NSIndexPath) -> UITableViewCell {
            
            let cell =
            tableView.dequeueReusableCellWithIdentifier("Cell")
                as UITableViewCell!
            
            let person = people[indexPath.row]
            cell.textLabel!.text = person.valueForKey("name") as? String
            
            return cell
    }
    
    
    func saveName(name: String) {
        //1
        let appDelegate =
        UIApplication.sharedApplication().delegate as! AppDelegate
        
        let managedContext = appDelegate.managedObjectContext
        
        //2
        let entity =  NSEntityDescription.entityForName("Person",
            inManagedObjectContext:
            managedContext)
        
        let person = NSManagedObject(entity: entity!,
            insertIntoManagedObjectContext:managedContext)
        
        //3
        person.setValue(name, forKey: "name")
        
        //4
        //_;: NSError?
        do{
            
        try managedContext.save()
        }
            catch{
            print("Could not save \(error)")
            }
        
        //5
        people.append(person)
    }

    var people = [NSManagedObject]()
    @IBAction func addPeople(sender: AnyObject) {
  
        let alert = UIAlertController(title: "New people",
            message: "Add a new name",
            preferredStyle: .Alert)
        
        let saveAction = UIAlertAction(title: "Save",
            style: .Default) { (action: UIAlertAction!) -> Void in
                
                let textField = alert.textFields![0] 
                self.saveName(textField.text!)
                self.tableView.reloadData()
        }
        let cancelAction = UIAlertAction(title: "Cancel",
            style: .Default) { (action: UIAlertAction!) -> Void in
        }
        
        alert.addTextFieldWithConfigurationHandler {
            (textField: UITextField!) -> Void in
        }
        
        alert.addAction(saveAction)
        alert.addAction(cancelAction)
        
        presentViewController(alert,
            animated: true,
            completion: nil)
    }
    
        
    override func viewDidLoad() {
        super.viewDidLoad()
        title = "\"The List\""
        tableView.registerClass(UITableViewCell.self,
            forCellReuseIdentifier: "Cell")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }




}

