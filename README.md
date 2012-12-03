

Permits to launch predefined commands.

Methods
=======

Method specification exemple
----------------------------

    ```json
    {
        "name": "helloWorld",
        "user": 512,
        "group": 512,
        "limits": {
            "cputime": 100,
            "filesize": 1000
        },
        "command": "/usr/bin/echo",
        "arguments": [ "--", { "-n": { "occurences": 1, "kind": "number", "defaultValue": "2", "maxValue": 3, "minValue": 1 } } ]
    }```

The above means that upon request to execute helloWorld, "/usr/bin/echo" will be executed with "--" as first argument. Then 


Method limits
-------------

  - ``cputime`` the maximum number of cpu-seconds to be used by each process

  - filesize the largest single file which can be created

  - datasize the maximum growth of the data+stack region via sbrk(2) beyond the end of the program text

  - stacksize the maximum size of the automatically-extended stack region

  - coredumpsize the size of the largest core dump that will be created

  - memoryuse the maximum amount of physical memory a process may have allocated to it at a given time

  - vmemoryuse the maximum amount of virtual memory a process may have allocated to it at a given time (address space)

  - vmemoryuse the maximum amount of virtual memory a process may have allocated to it at a given time

  - heapsize the maximum amount of memory a process may allocate per brk() system call

  - descriptors or openfiles the maximum number of open files for this process

  - concurrency the maximum number of threads for this process

  - memorylocked the maximum size which a process may lock into memory using mlock(2)

  - maxproc the maximum number of simultaneous processes for this user id

  - sbsize the maximum size of socket buffer usage for this user

  - swapsize

Request specification exemple
-----------------------------

    ```json
    {
        "name": "helloWorld",
        "arguments": [ 2 ]
    }```

