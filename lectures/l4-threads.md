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
