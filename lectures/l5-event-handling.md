# Event Handling
Event handling in Java is a mechanism that manages events, such as button clicks, key presses, or mouse movements. It is part of Java’s AWT (Abstract Window Toolkit) and Swing libraries.

![image](https://github.com/user-attachments/assets/3bba69a6-a6a7-4536-b9a9-acfdc6c86608)

## Steps for Event Handling in Java:

	1.	Event Source: The object that generates an event, e.g., a button.
	2.	Event Object: The object that encapsulates information about the event, e.g., ActionEvent.
	3.	Event Listener: An interface that defines methods to respond to specific events, e.g., ActionListener.
	4.	Event Handling Code: The code in the listener that executes when the event occurs.

![image](https://github.com/user-attachments/assets/c98bd496-12dc-4845-8f24-bc54b4f518fe)

## Example:
```java
import java.awt.*;
import java.awt.event.*;

public class MyEventDemo extends Frame implements ActionListener {
    Button button;

    MyEventDemo() {
        button = new Button("Click Me");
        button.setBounds(50, 100, 80, 30); // Button size and position
        button.addActionListener(this);    // Register listener
        add(button);  // Add button to frame
        setSize(200, 200);
        setLayout(null);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println("Button clicked");
    }

    public static void main(String[] args) {
        new MyEventDemo();
    }
}
```
This example creates a button, and when clicked, the event listener prints a message.

## Event handling mechanism in java

The event handling mechanism in Java follows the “Delegation Event Model,” which separates the event source from the event listener. Here’s how it works:

1. Event Source:

	•	The component that triggers events, like a button or a text field.
	•	Example: Button, TextField, Frame, etc.

2. Event Object:

	•	Captures the details of the event (e.g., a button click or a key press).
	•	Example: ActionEvent, MouseEvent, KeyEvent.

3. Event Listener:

	•	An object that listens for events and defines what action to take.
	•	Implemented through interfaces like ActionListener, MouseListener, KeyListener.

4. Event Handling Process:

	1.	Register the Listener:
The event source registers one or more event listeners to handle the event.
	2.	Event Occurrence:
When the event occurs (e.g., a button is clicked), the event source notifies the registered listener(s).
	3.	Invoke Event Listener Method:
The listener responds by executing the appropriate method (e.g., actionPerformed()).

## Key Components of the Event Handling Mechanism:

	•	Event Classes: Represent specific events like ActionEvent, MouseEvent.
	•	Listener Interfaces: Interfaces like ActionListener, MouseListener define event-handling methods.
	•	Adapter Classes: Provide empty implementations for listener interfaces, allowing you to override only the methods you need.

## Example Workflow:

	1.	Register Listener:

```java
button.addActionListener(this);  // 'this' refers to a class that implements ActionListener
```

	2.	Handle the Event:
```java
public void actionPerformed(ActionEvent e) {
    System.out.println("Button clicked");
}
```

This architecture ensures that the event source (button) delegates the responsibility of handling the event to the listener.

# Event class in java
In Java, an event class is a part of the event handling mechanism that encapsulates the details of an event (e.g., button clicks, key presses). It provides information about the event, such as the type of event and the source object that generated it.

## Hierarchy of Event Classes:

All event classes in Java inherit from the java.util.EventObject class, which is the root class for all event-related objects.
```sh
java.lang.Object
   ↳ java.util.EventObject
      ↳ java.awt.AWTEvent
         ↳ Specific Event Classes (e.g., ActionEvent, MouseEvent, KeyEvent)
```
## Common Event Classes:

	1.	ActionEvent:
	•	Generated when an action occurs, such as a button click or pressing the Enter key in a text field.
	•	Example:
```java
button.addActionListener(new ActionListener() {
    public void actionPerformed(ActionEvent e) {
        System.out.println("Button clicked");
    }
});
```

	2.	MouseEvent:
	•	Generated when mouse actions occur, like clicking, pressing, releasing, or moving the mouse.
	•	Example: Mouse click, double-click, mouse entering a component.
	3.	KeyEvent:
	•	Generated when keyboard actions occur, such as key presses and releases.
	4.	WindowEvent:
	•	Generated when window-related actions occur, such as opening, closing, or minimizing a window.
	5.	ItemEvent:
	•	Generated when an item is selected or deselected, such as in a checkbox or a list.
	6.	FocusEvent:
	•	Generated when a component gains or loses focus (e.g., a text field gaining input focus).
	7.	TextEvent:
	•	Generated when the value of a text component changes, such as a TextField.

## Example of ActionEvent:
```java
import java.awt.*;
import java.awt.event.*;

public class ActionEventExample {
    public static void main(String[] args) {
        Frame frame = new Frame("Event Example");
        Button button = new Button("Click Me");
        
        button.setBounds(50, 50, 80, 30);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.out.println("Button Clicked: " + e.getSource());
            }
        });
        
        frame.add(button);
        frame.setSize(200, 200);
        frame.setLayout(null);
        frame.setVisible(true);
    }
}
```
In this example, the ActionEvent is triggered when the button is clicked, and the event details are captured using the ActionEvent object.



# ActionListener Interface in Java:

The ActionListener interface is part of Java’s java.awt.event package and is used to handle ActionEvents such as button clicks or menu selections. It defines a method that gets called when an action occurs.

### Key Points of ActionListener:

	•	Single Method: It has one method, actionPerformed(), which handles the event.
```java
void actionPerformed(ActionEvent e);
```
	•	ActionEvent e: Contains details about the event, like the event source and the action command.

### How to Use ActionListener:

	1.	Create a Component: Such as a button or menu item.
	2.	Register a Listener: Use methods like addActionListener() to register the listener.
	3.	Implement the actionPerformed() Method: Define what happens when the event is triggered.

### Example of ActionListener:
```java
import java.awt.*;
import java.awt.event.*;

public class ActionListenerExample extends Frame implements ActionListener {
    Button button;

    ActionListenerExample() {
        button = new Button("Click Me");
        button.setBounds(100, 100, 80, 30);

        // Registering the ActionListener
        button.addActionListener(this);

        add(button);
        setSize(300, 300);
        setLayout(null);
        setVisible(true);
    }

    // Implementing the actionPerformed method
    public void actionPerformed(ActionEvent e) {
        System.out.println("Button clicked!");
    }

    public static void main(String[] args) {
        new ActionListenerExample();
    }
}
```

## AWT Fundamentals (Abstract Window Toolkit):
![image](https://github.com/user-attachments/assets/4a3508b2-5c8a-4128-b5c4-178d448b363b)


AWT is Java’s original GUI framework for creating platform-independent window-based applications. It provides components, containers, and event handling for developing graphical user interfaces.

### Key Components in AWT:

	1.	Components:
	•	Basic UI elements like buttons, text fields, labels, etc.
	•	Examples:
	•	Button
	•	TextField
	•	Label
	•	Checkbox
```java
Button b = new Button("Submit");
TextField tf = new TextField();
Label label = new Label("Enter Name:");
```

	2.	Containers:
	•	Containers hold components. The most common container is the Frame (a window with borders and title).
	•	Examples:
	•	Frame
	•	Panel
	•	Dialog
```java
Frame frame = new Frame("My AWT Frame");
```

	3.	Layouts:
	•	AWT uses layout managers to position components in a container.
	•	Common layout managers:
	•	FlowLayout: Places components in a row.
	•	BorderLayout: Divides the container into five regions.
	•	GridLayout: Places components in a grid of rows and columns.
```java
frame.setLayout(new FlowLayout());
```

	4.	Event Handling:
	•	AWT uses the Delegation Event Model where events (e.g., button clicks) are captured by listeners (e.g., ActionListener).
	•	Common events:
	•	ActionEvent (button clicks)
	•	MouseEvent (mouse movements)
	•	KeyEvent (keyboard actions)

## Simple AWT Example:
```java
import java.awt.*;
import java.awt.event.*;

public class AWTExample extends Frame implements ActionListener {
    Button button;

    AWTExample() {
        // Create and set up components
        button = new Button("Click Me");
        button.setBounds(100, 100, 80, 30);
        button.addActionListener(this);

        // Add button to frame
        add(button);

        // Frame properties
        setSize(300, 300);
        setLayout(null);  // No layout manager
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println("Button clicked!");
    }

    public static void main(String[] args) {
        new AWTExample();
    }
}
```

### Breakdown of the Example:

	•	Button: A simple button component.
	•	ActionListener: The AWTExample class implements ActionListener to handle button clicks.
	•	Frame: The main window for the GUI application.

### Summary of AWT Fundamentals:

	•	Components: Basic UI elements (e.g., Button, TextField).
	•	Containers: Hold components (e.g., Frame, Panel).
	•	Layouts: Manage the arrangement of components within containers.
	•	Event Handling: Listeners like ActionListener respond to user interactions.

By using AWT components and event handling, you can create interactive, platform-independent GUI applications.


## Case Study: ATM System

An ATM (Automated Teller Machine) system allows bank customers to perform financial transactions like withdrawals, deposits, and balance inquiries. It is a real-world application that requires robust security, transaction management, and user interaction. Below is a simple overview of the key components and operations involved in building an ATM system.

### Key Components of an ATM System:

	1.	Card Reader:
	•	Reads the customer’s bank card to retrieve card details (e.g., card number).
	•	Typically interfaces with a back-end system to authenticate the card.
	2.	PIN Authentication:
	•	The user inputs a PIN (Personal Identification Number) to verify their identity.
	•	This PIN is verified against a secure back-end system to grant access.
	3.	Transaction Options:
	•	Withdraw: Allows the user to withdraw a certain amount from their account.
	•	Deposit: Allows the user to deposit money into their account.
	•	Balance Inquiry: Displays the current balance in the user’s account.
	4.	Account Management:
	•	Keeps track of account balances, transaction history, and security.
	•	Connects to a back-end database for storing and updating user information.
	5.	Receipt Printing:
	•	Provides the user with a receipt of the transaction for future reference.

### Operations in an ATM System:

	1.	Card Insertion:
	•	The user inserts the card, and the system reads the card details.
	2.	PIN Entry and Validation:
	•	The user enters a PIN, and the system verifies it against the bank database.
	3.	Transaction Selection:
	•	The user selects the type of transaction they want to perform (withdrawal, deposit, balance inquiry).
	4.	Processing Transactions:
	•	For withdrawals, the system checks if the user has sufficient balance.
	•	For deposits, the amount is credited to the user’s account.
	5.	Transaction Confirmation:
	•	The system displays a confirmation message or prints a receipt.

### UML Representation:

	•	Classes: ATM, CardReader, Account, Transaction, ReceiptPrinter.
	•	Methods:
	•	validateCard(), validatePIN(), performTransaction(), checkBalance(), withdraw(), deposit().

## Case Study: Payroll System

A Payroll System is used to automate the process of paying employees, keeping track of hours worked, salary payments, and deductions like taxes and benefits. The system needs to ensure that each employee receives accurate payment on time.

### Key Components of a Payroll System:

	1.	Employee Database:
	•	Stores employee details such as employee ID, name, salary, position, and employment status.
	•	Provides easy access for managing employee information.
	2.	Time Management System:
	•	Tracks the hours worked by each employee.
	•	Integrates with attendance systems (e.g., swipe cards or login systems) to calculate hours.
	3.	Salary Calculation:
	•	Calculates the gross pay based on the hours worked and the employee’s hourly rate or salary.
	•	Deductions for taxes, insurance, and benefits are applied.
	4.	Deductions:
	•	Includes deductions like federal/state taxes, health insurance, and retirement savings.
	5.	Payroll Processing:
	•	Automatically processes payroll at the end of each pay period (weekly, bi-weekly, or monthly).
	•	Generates paychecks or direct deposits.
	6.	Tax Management:
	•	Ensures the appropriate taxes are deducted from each paycheck.
	•	Provides tax reporting tools for both employees and the organization.

### Operations in a Payroll System:

	1.	Employee Management:
	•	The system maintains details like job title, salary, and hours worked.
	2.	Work Hours Entry:
	•	Employees log their work hours, and the system records this data.
	3.	Salary Calculation:
	•	Based on the work hours, the system calculates gross pay and applies deductions.
	4.	Payroll Generation:
	•	Generates a payslip or paycheck for the employee.
	5.	Payroll Distribution:
	•	Sends the paycheck or initiates a direct deposit to the employee’s account.

### UML Representation:

	•	Classes: Employee, Payroll, Salary, Deductions, TimeSheet.
	•	Methods:
	•	calculateSalary(), processPayroll(), generatePayslip(), deductTaxes(), recordHours().

### Summary:

	•	ATM System: Focuses on user authentication, secure transactions (withdrawals, deposits), and account management.
	•	Payroll System: Manages employee data, time tracking, salary calculations, and payroll processing.

Both systems have defined workflows and use object-oriented concepts like class relationships and inheritance to manage real-world tasks efficiently.
