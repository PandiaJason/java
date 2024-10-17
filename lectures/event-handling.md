# Event Handling
Event handling in Java is a mechanism that manages events, such as button clicks, key presses, or mouse movements. It is part of Java’s AWT (Abstract Window Toolkit) and Swing libraries.

## Steps for Event Handling in Java:

	1.	Event Source: The object that generates an event, e.g., a button.
	2.	Event Object: The object that encapsulates information about the event, e.g., ActionEvent.
	3.	Event Listener: An interface that defines methods to respond to specific events, e.g., ActionListener.
	4.	Event Handling Code: The code in the listener that executes when the event occurs.

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
