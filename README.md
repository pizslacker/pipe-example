# pipe-example

### How to play with it
You will need two separate terminal windows for this to work.

#### **Step 1**: Compile both programs
```bash
gcc -o broadcaster broadcaster.c
gcc -o receiver receiver.c
```

#### **Step 2**: Start the Broadcaster (Terminal 1)
```bash
./broadcaster
```

#### **Step 3**: Start the Radio (Terminal 2)
```bash
./receiver
```

Step 4: Talk!
Type anything into Terminal 1 and hit Enter. Watch as it instantly appears in Terminal 2. It feels like magic because they are completely disconnected processes communicating entirely through a temporary ghost file in your `/tmp` directory.

    Fun trick: You don't even need the C radio program to listen! Because it's a file, you can just use standard Unix tools. Try running `./broadcaster` in Terminal 1, and in Terminal 2 just run cat /tmp/my_receiver_channel. The cat command will act as your reader!
