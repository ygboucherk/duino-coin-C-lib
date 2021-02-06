# duino-coin-C-lib
A C library for interacting with Duino-Coin network

## Usage
### Importing library
First put `ducolib.h` in the directory where's ur C program stored

Then include it within program using :
```c
#include "ducolib.h"
```

### Library functions
#### Connecting to DUCO server
`connectDuco()` returns a socket object that can be reused (and is used by next functions)

Example of code using it :
```c
int socket;
socket = connectDuco();
```


#### Logging in
`ducologin(socket,username,password)` takes 3 arguments.

`socket` is the socket previously, `username` is DUCO username and `password` is DUCO password.

example :
```c
int socket;
socket = connectDuco();
ducologin(socket,"test","test");
```


#### Getting balance
`ducobalance(socket)` returns balance as `double` (floating point), and `socket` is socket ID
*note : user should have logged in previously*

example :
```c
int socket;
double balance;
socket = connectDuco();
ducologin(socket,"test","test");
balance = ducobalance(socket);
```

#### Sending a transaction
`sendduco(socket,amount,recipient)` requires 3 arguments (socket,amount and recipient).

If transaction's successful, it returns `0`. Else it returns `1`.

example :
```c
int socket;
int feedback;
socket = connectDuco();
ducologin(socket,"test","test");
sendduco(socket,10,"Yanis");
```


### Full example
Here's a little (but functionnal) example that gets (and shows on screen) balance, and then sends 10 DUCO to user Yanis (me xD) ! Feel free of running it (and giving me 10 Duino-Coins lol) !
```
#include "ducolib.h"
#include <stdio.h>

int socket;
int feedback;
double balance;
socket = connectDuco();
ducologin(socket,"test","test");
balance = ducobalance(socket);
printf("Your DUCO balance is %f", balance);
feedback = sendduco(socket,10,"Yanis");
if (feedback == 0) {
  printf("Successfully sent 10 DUCO to Yanis");
}
else {
  printf("Something went wrong")
}
```

### Why all these `socket` ?
If you tried understanding code, you has seen there was many occurences of `socket`. 
I've used them because if each socket is treated separately, so it allows having multiple threads at the same time (each one having its socket), instead of disconnecting/reconnecting if we want to switch.
