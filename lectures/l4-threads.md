The Java thread model is designed to enable concurrent execution within a single process, allowing multiple tasks (threads) to run simultaneously, share resources, and make efficient use of the CPU. Here is an overview of Java's thread model:

### 1. **What is a Thread?**
   - A **thread** is the smallest unit of execution in a program.
   - In Java, threads are independent, concurrent units of execution within a program, but they share the same process memory space (heap).

### 2. **Multithreading in Java**
   - **Multithreading** is the ability to run multiple threads simultaneously.
   - In Java, multithreading allows for performing multiple tasks in parallel, such as reading files, making network calls, or performing computations concurrently.

### 3. **Thread Creation**
   Java provides two primary ways to create a thread:

   - **Extending the `Thread` Class**:
     You can create a thread by extending the `Thread` class and overriding its `run()` method.
     ```java
     class MyThread extends Thread {
         public void run() {
             System.out.println("Thread is running");
         }
     }
     MyThread thread = new MyThread();
     thread.start();  // Starts the thread, invoking the run() method
     ```

   - **Implementing the `Runnable` Interface**:
     You can create a thread by implementing the `Runnable` interface and passing the `Runnable` object to a `Thread` object.
     ```java
     class MyRunnable implements Runnable {
         public void run() {
             System.out.println("Thread is running");
         }
     }
     MyRunnable myRunnable = new MyRunnable();
     Thread thread = new Thread(myRunnable);
     thread.start();
     ```

### 4. **Thread Lifecycle**
   A thread goes through several states in its lifecycle:
   
   1. **New**: The thread is created but not started (e.g., `Thread t = new Thread()`).
   2. **Runnable**: The thread is ready to run after calling `start()` but may not be running immediately.
   3. **Running**: The thread is executing its `run()` method.
   4. **Blocked/Waiting**: The thread is blocked or waiting (e.g., waiting for a lock or sleeping).
   5. **Terminated**: The thread has finished execution or is terminated.

### 5. **Thread Control Methods**
   - **start()**: Starts a thread, causing it to enter the `Runnable` state and eventually run.
   - **run()**: The method that contains the code the thread executes.
   - **sleep(milliseconds)**: Causes the thread to sleep (pause execution) for a specified period.
   - **yield()**: Pauses the current thread and gives other threads a chance to run.
   - **join()**: Waits for the thread to die (finish execution).
   - **interrupt()**: Interrupts a thread that is sleeping or waiting.

### 6. **Synchronization and Locks**
   When multiple threads access shared resources, synchronization is necessary to avoid data corruption. Java provides two key mechanisms for synchronization:
   
   - **Synchronized Methods and Blocks**: Prevents multiple threads from executing a critical section simultaneously.
     ```java
     synchronized(object) {
         // Code inside this block will be executed by only one thread at a time
     }
     ```
   - **Locks (`ReentrantLock`)**: Java’s `java.util.concurrent.locks` package provides explicit locking mechanisms like `Lock` and `ReentrantLock` for more fine-grained control over thread synchronization.

### 7. **Thread Priority**
   Java threads have priorities that influence thread scheduling. However, thread scheduling is platform-dependent. Priority levels:
   - **MIN_PRIORITY (1)**
   - **NORM_PRIORITY (5)**: Default priority.
   - **MAX_PRIORITY (10)**
   
   You can set the thread’s priority using the `setPriority()` method.

### 8. **Inter-Thread Communication**
   Java provides mechanisms for communication between threads:
   - **wait()**, **notify()**, and **notifyAll()** are methods used for coordinating thread execution, where one thread can pause execution (wait) until another thread signals it (notify).

   Example:
   ```java
   synchronized(object) {
       object.wait();  // Pauses the current thread
       object.notify();  // Wakes up a waiting thread
   }
   ```

### 9. **Thread Pools (Executor Framework)**
   Instead of creating individual threads manually, Java’s `ExecutorService` allows for efficient thread management via thread pools. The thread pool reuses threads for multiple tasks, improving resource management and performance.

   Example using `Executors`:
   ```java
   ExecutorService executor = Executors.newFixedThreadPool(5);
   executor.execute(new MyRunnableTask());
   executor.shutdown();
   ```

### 10. **Concurrency Utilities**
   Java’s `java.util.concurrent` package provides high-level concurrency utilities to manage complex thread interactions:
   - **Locks**: For advanced locking mechanisms (`ReentrantLock`, `ReadWriteLock`).
   - **Atomic Variables**: For thread-safe operations on variables (e.g., `AtomicInteger`).
   - **CountDownLatch**, **Semaphore**, **CyclicBarrier**: For coordinating thread execution.
   - **Concurrent Collections**: Thread-safe collections like `ConcurrentHashMap`, `CopyOnWriteArrayList`, etc.

### 11. **Volatile Keyword**
   The `volatile` keyword ensures that changes made to a variable are visible to all threads. It’s used for variables that are shared between threads but do not require locking.
   ```java
   private volatile boolean flag = true;
   ```

### 12. **Callable and Future**
   Java’s `Callable` interface is similar to `Runnable`, but it can return a result or throw an exception.
   - **Callable**: Represents a task that returns a result.
   - **Future**: Represents the result of an asynchronous computation.
   ```java
   Callable<Integer> task = () -> 42;
   Future<Integer> future = executor.submit(task);
   ```

### 13. **Deadlock and Livelock**
   - **Deadlock**: Occurs when two or more threads are blocked forever, waiting for each other to release resources.
   - **Livelock**: Occurs when threads are continuously changing their states in response to each other but unable to make progress.

### Summary
- **Thread**: A unit of execution in Java that runs concurrently within a program.
- **Thread Creation**: You can create threads by extending the `Thread` class or implementing the `Runnable` interface.
- **Synchronization**: Java provides synchronization tools like `synchronized` blocks, methods, and locks to prevent race conditions.
- **Executor Framework**: Use thread pools via `ExecutorService` for efficient thread management.
- **Concurrency Utilities**: Java’s concurrency utilities help with more complex thread interactions.

The Java thread model is a flexible and powerful system designed to handle multiple threads efficiently, enabling developers to build responsive, parallelized, and scalable applications.


# Threads with Synchronization

### Java Program: Summing Array Segments Using Threads with Synchronization

```java
class ArraySumThread extends Thread {
    private int[] array;
    private int start;
    private int end;
    private int partialSum = 0;
    private static int totalSum = 0;

    // Constructor to initialize thread with array segment
    public ArraySumThread(int[] array, int start, int end) {
        this.array = array;
        this.start = start;
        this.end = end;
    }

    // Thread task: calculate the sum of the array segment
    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            partialSum += array[i];
        }
        // Synchronize access to shared resource (totalSum)
        addPartialSum(partialSum);
    }

    // Synchronized method to ensure only one thread modifies totalSum at a time
    private synchronized static void addPartialSum(int partialSum) {
        totalSum += partialSum;
    }

    // Getter for total sum
    public static int getTotalSum() {
        return totalSum;
    }
}

public class MultiThreadedArraySum {
    public static void main(String[] args) {
        // Define an array to sum
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int numberOfThreads = 3; // Number of threads
        int segmentSize = array.length / numberOfThreads; // Size of each segment

        // Create and start threads
        ArraySumThread[] threads = new ArraySumThread[numberOfThreads];
        for (int i = 0; i < numberOfThreads; i++) {
            int start = i * segmentSize;
            int end = (i == numberOfThreads - 1) ? array.length : start + segmentSize;
            threads[i] = new ArraySumThread(array, start, end);
            threads[i].start();
        }

        // Wait for all threads to finish
        for (int i = 0; i < numberOfThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Get and print the final total sum
        System.out.println("Total sum of array: " + ArraySumThread.getTotalSum());
    }
}
```

### Explanation:

1. **ArraySumThread Class**:
    - Extends `Thread` and defines the task for each thread, which is to sum a portion (segment) of the array.
    - The `run()` method contains the logic to calculate the partial sum of the array segment assigned to the thread.
    - The `addPartialSum()` method is declared `synchronized`, ensuring that only one thread can add its partial sum to the shared `totalSum` at a time, avoiding race conditions.

2. **Synchronization**:
    - The critical section here is the `totalSum` variable, which is shared among multiple threads. To avoid race conditions, access to this variable is synchronized using the `synchronized` keyword on the `addPartialSum()` method.
    - This ensures that when one thread is modifying `totalSum`, no other thread can interfere.

3. **Main Program**:
    - The array is divided into segments, and each thread is responsible for summing a segment.
    - The `start()` method starts the execution of each thread.
    - After starting all threads, the `join()` method is used to wait for all threads to finish before accessing the final result.
    - Finally, the total sum is printed after all threads complete their execution.

### Key Points of Thread Synchronization:
- **Race Condition**: Without synchronization, multiple threads might try to update the `totalSum` simultaneously, leading to inconsistent results. Synchronizing the update ensures that only one thread modifies the shared resource at a time.
- **`synchronized` Keyword**: This ensures mutual exclusion, preventing multiple threads from executing the critical section of the code simultaneously.
- **Thread Communication**: The `join()` method ensures the main thread waits for all worker threads to complete before proceeding, ensuring the final result is accurate.

### Example Output:

```
Total sum of array: 55
```

This program demonstrates how to use multithreading and synchronization to safely compute the sum of an array by dividing the work across multiple threads and ensuring proper synchronization when updating shared data.


### Creation of a Thread using both the Thread class and the Runnable interface.

### Program

```java
// Thread creation by extending the Thread class
class MyThreadClass extends Thread {
    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("Thread using Thread class: " + i);
            try {
                Thread.sleep(500);  // Pausing execution for 500 milliseconds
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}

// Thread creation by implementing the Runnable interface
class MyRunnableClass implements Runnable {
    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("Thread using Runnable interface: " + i);
            try {
                Thread.sleep(500);  // Pausing execution for 500 milliseconds
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}

public class ThreadDemo {
    public static void main(String[] args) {
        // Creating and starting a thread using the Thread class
        MyThreadClass thread1 = new MyThreadClass();
        thread1.start();

        // Creating and starting a thread using the Runnable interface
        Thread thread2 = new Thread(new MyRunnableClass());
        thread2.start();
    }
}
```

### Comparison Between the Two Approaches

#### 1. **Using `Thread` Class**
   - **Advantages**:
     - Simple to implement by directly overriding the `run()` method.
     - You don’t need to create a separate `Runnable` object.
   - **Disadvantages**:
     - **Single Inheritance Limitation**: Since Java doesn't support multiple inheritance, your class can’t extend any other class if it extends `Thread`.
     - Tightly couples the task logic with the thread itself, making code less reusable.

#### 2. **Using `Runnable` Interface**
   - **Advantages**:
     - **Flexibility**: Your class can extend another class while implementing `Runnable`.
     - **Separation of Concerns**: The task logic is separated from thread control, making it easier to reuse the same task in different threads or scenarios.
     - More aligned with good object-oriented design principles.
   - **Disadvantages**:
     - Slightly more verbose: You need to pass the `Runnable` instance to a `Thread` object before starting the thread.

### Conclusion:
- Use **`Thread` class** when you have simple, one-off tasks and don’t need to extend any other class.
- Use **`Runnable` interface** when you need more flexibility, plan to reuse the task across multiple threads, or when your class already extends another class.


### Java Program: Simulating a Simple Banking System with UPI Transactions

In this program, multiple customers (threads) try to withdraw money from the same bank account. To ensure that the account balance is not overdrawn, we use **synchronization** to protect the withdrawal operation, ensuring thread safety.

### Java Code

```java
// Bank Account class simulating a shared bank account
class BankAccount {
    private int balance;

    public BankAccount(int balance) {
        this.balance = balance;
    }

    // Synchronized method to withdraw money
    public synchronized void withdraw(String customer, int amount) {
        System.out.println(customer + " tries to withdraw: " + amount);

        if (balance >= amount) {
            System.out.println(customer + " proceeds with the withdrawal.");
            try {
                Thread.sleep(100);  // Simulate transaction delay
            } catch (InterruptedException e) {
                System.out.println("Transaction interrupted.");
            }
            balance -= amount;
            System.out.println(customer + " successfully withdrew: " + amount);
            System.out.println("Remaining balance: " + balance);
        } else {
            System.out.println(customer + " failed to withdraw. Insufficient balance.");
        }
    }

    public int getBalance() {
        return balance;
    }
}

// Customer class representing a customer making a withdrawal
class Customer extends Thread {
    private BankAccount account;
    private int amount;
    private String customerName;

    public Customer(String customerName, BankAccount account, int amount) {
        this.customerName = customerName;
        this.account = account;
        this.amount = amount;
    }

    @Override
    public void run() {
        account.withdraw(customerName, amount);
    }
}

public class BankingSystem {
    public static void main(String[] args) {
        // Shared bank account with an initial balance
        BankAccount account = new BankAccount(1000);

        // Creating customer threads attempting to withdraw money
        Customer customer1 = new Customer("Customer 1", account, 500);
        Customer customer2 = new Customer("Customer 2", account, 700);
        Customer customer3 = new Customer("Customer 3", account, 300);

        // Starting the customer threads
        customer1.start();
        customer2.start();
        customer3.start();
    }
}
```

### Explanation:
1. **Synchronization**: 
   - The `withdraw` method is marked `synchronized`, ensuring that only one thread can access it at a time, avoiding race conditions when multiple customers attempt to withdraw simultaneously.
   
2. **Shared Resource**: 
   - All customer threads access the same `BankAccount` object, which holds the balance. Without synchronization, multiple withdrawals could result in an inconsistent state, like overdrawing the account.

3. **Thread Safety**:
   - Thread safety is achieved by ensuring that checking the balance and withdrawing money is done atomically (as one unit of work), which prevents two threads from withdrawing at the same time and causing overdraft.

### Sample Output:
```
Customer 1 tries to withdraw: 500
Customer 1 proceeds with the withdrawal.
Customer 2 tries to withdraw: 700
Customer 3 tries to withdraw: 300
Customer 1 successfully withdrew: 500
Remaining balance: 500
Customer 3 proceeds with the withdrawal.
Customer 3 successfully withdrew: 300
Remaining balance: 200
Customer 2 failed to withdraw. Insufficient balance.
```

### How Thread Safety is Ensured:
- **Synchronized Block**: The `synchronized` keyword ensures that only one thread at a time can execute the `withdraw()` method on the same object. This prevents multiple threads from interfering with each other while accessing or modifying the shared `balance` variable.
- **Atomic Operations**: The check for balance and the withdrawal are done together in the synchronized method, ensuring that no other thread can interrupt during this critical operation.



Inter-thread communication in Java allows threads to communicate with each other by sharing resources or signaling each other to ensure proper synchronization. This is important in multi-threaded environments where threads need to coordinate their execution.

Java provides three key methods in the `Object` class to facilitate inter-thread communication:

1. **`wait()`**: A thread can call `wait()` on an object to release the lock and enter a waiting state until another thread notifies it.

2. **`notify()`**: Wakes up one of the threads waiting on the same object's lock. The awakened thread then tries to re-acquire the lock.

3. **`notifyAll()`**: Wakes up all threads waiting on that object's lock. All awakened threads then compete to re-acquire the lock.

### Example:
```java
class SharedResource {
    synchronized void produce() throws InterruptedException {
        System.out.println("Producing...");
        wait(); // release lock and wait
        System.out.println("Resumed after consumption");
    }

    synchronized void consume() {
        System.out.println("Consuming...");
        notify(); // notify waiting thread
    }
}

public class InterThreadCommunication {
    public static void main(String[] args) {
        SharedResource resource = new SharedResource();

        new Thread(() -> {
            try { resource.produce(); } catch (InterruptedException e) { e.printStackTrace(); }
        }).start();

        new Thread(() -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { e.printStackTrace(); }
            resource.consume();
        }).start();
    }
}
```

### Key points:
- **Synchronized blocks** or methods are required to ensure the thread holds the object's monitor before calling `wait()`, `notify()`, or `notifyAll()`.
- These methods help coordinate threads, especially in scenarios like producer-consumer problems.

In Java, **Auto Boxing** is the automatic conversion of primitive types into their corresponding wrapper class objects, and **Unboxing** is the reverse. This helps bridge the gap between primitives and objects, particularly when dealing with collections, generics, or object-oriented programming.

### Example:

- **Auto Boxing**: Primitive to Wrapper
  ```java
  int i = 10;
  Integer wrappedInt = i; // Auto-boxing
  ```

- **Unboxing**: Wrapper to Primitive
  ```java
  Integer wrappedInt = 10;
  int i = wrappedInt; // Unboxing
  ```

This allows you to seamlessly use primitive types where objects are required (e.g., in collections like `ArrayList<Integer>`).

### Benefits:
- Reduces code complexity by eliminating manual conversions.


In Java, Input/Output (I/O) operations are handled through classes in the `java.io` and `java.nio` packages. These allow reading and writing data (bytes or characters) to different types of data sources like files, networks, and memory.

### Types of I/O in Java:

1. **Byte Streams**:
   - Used for reading and writing binary data (e.g., images, audio).
   - Classes: `InputStream`, `OutputStream`.
   - Examples:
     - **FileInputStream**: Reads bytes from a file.
     - **FileOutputStream**: Writes bytes to a file.

   ```java
   FileInputStream fis = new FileInputStream("input.txt");
   int data = fis.read();
   ```

2. **Character Streams**:
   - Used for reading and writing text data.
   - Classes: `Reader`, `Writer`.
   - Examples:
     - **FileReader**: Reads characters from a file.
     - **FileWriter**: Writes characters to a file.

   ```java
   FileReader fr = new FileReader("input.txt");
   int data = fr.read();
   ```

3. **Buffered Streams**:
   - Improve performance by buffering the data to reduce the number of I/O operations.
   - Classes: `BufferedReader`, `BufferedWriter`, `BufferedInputStream`, `BufferedOutputStream`.

   ```java
   BufferedReader br = new BufferedReader(new FileReader("input.txt"));
   String line = br.readLine();
   ```

4. **Data Streams**:
   - For reading and writing primitive data types (int, float, etc.).
   - Classes: `DataInputStream`, `DataOutputStream`.

   ```java
   DataOutputStream dos = new DataOutputStream(new FileOutputStream("data.bin"));
   dos.writeInt(123);
   ```

5. **Object Streams**:
   - Used to serialize and deserialize Java objects.
   - Classes: `ObjectInputStream`, `ObjectOutputStream`.

   ```java
   ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("object.dat"));
   oos.writeObject(new MyObject());
   ```

6. **Console I/O**:
   - Reading from and writing to the console.
   - Classes: `Scanner` (for input), `System.out` (for output).

   ```java
   Scanner sc = new Scanner(System.in);
   String input = sc.nextLine();
   System.out.println("You entered: " + input);
   ```

### Basic Methods:
- **read()**: Reads a single byte/character or an array.
- **write()**: Writes a single byte/character or an array.
- **flush()**: Flushes the stream, forcing any buffered output to be written immediately.
- **close()**: Closes the stream and releases resources.


In Java, reading and writing to the console can be done using standard I/O streams.

Writing to the Console

You can use System.out.print(), System.out.println(), or System.out.printf() to print to the console.

// Using print (without newline)
System.out.print("Hello, World!");

// Using println (with newline)
System.out.println("Hello, World!");

// Using printf (formatted output)
System.out.printf("Hello, %s!%n", "Jason");

Reading from the Console

For reading input, the Scanner class is commonly used.

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Reading a string
        System.out.print("Enter your name: ");
        String name = scanner.nextLine();
        System.out.println("Hello, " + name + "!");

        // Reading an integer
        System.out.print("Enter your age: ");
        int age = scanner.nextInt();
        System.out.println("You are " + age + " years old.");

        scanner.close();
    }
}

Key Points:

	•	System.out handles output.
	•	Scanner reads input from various data types.

The PrintWriter class in Java is used for writing formatted text to files or other output streams (like the console). It’s more flexible than System.out because it allows you to write to files, socket connections, or even memory buffers, with options for automatic flushing.

Key Features:

	•	Supports formatted output, like printf().
	•	Can write to any Writer (like FileWriter, StringWriter, etc.).
	•	Allows automatic flushing when certain methods are called (like println()).

Example: Writing to a File Using PrintWriter

import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            // Create a PrintWriter object to write to a file
            PrintWriter writer = new PrintWriter(new FileWriter("output.txt"));

            // Writing data to the file
            writer.println("Hello, Jason!");
            writer.printf("Your score is: %d%n", 100);

            // Close the writer
            writer.close();
            System.out.println("Data written to file.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

Features of PrintWriter:

	1.	println(): Writes data with a newline.
	2.	printf(): Supports formatted output like in C.
	3.	Automatic Flushing: Can be enabled by passing true in the constructor for flushing the buffer automatically after each write.

Example with Auto-Flush:

PrintWriter writer = new PrintWriter(new FileWriter("output.txt"), true);



In Java, reading and writing files can be done using various classes from the java.io and java.nio packages. Here are some common ways to handle file I/O.

Writing to a File

	1.	Using FileWriter and BufferedWriter

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            // FileWriter writes to the file, BufferedWriter improves performance
            BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
            writer.write("Hello, Jason!");
            writer.newLine(); // Adds a new line
            writer.write("Welcome to Java File I/O.");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


	2.	Using PrintWriter

import java.io.PrintWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            PrintWriter writer = new PrintWriter("output.txt");
            writer.println("Hello, Jason!");
            writer.println("Writing to a file with PrintWriter.");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}



Reading from a File

	1.	Using BufferedReader and FileReader

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("output.txt"));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


	2.	Using Files.readAllLines() (NIO)

import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            List<String> lines = Files.readAllLines(Paths.get("output.txt"));
            for (String line : lines) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}



Key Points:

	•	BufferedReader and BufferedWriter: Efficient for reading/writing text files.
	•	PrintWriter: Useful for formatted output.
	•	Files (from java.nio.file): Modern, simpler, and more efficient for reading and writing.
