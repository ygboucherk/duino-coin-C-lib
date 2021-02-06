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
socket = connectDuco();
ducologin(socket,"test","test");
balance = ducobalance(socket);

```

#### Sending a transaction
`sendduco(socket,amount,recipient)` requires 3 arguments (socket,amount and recipient).

If transaction's successful, it returns `0`. Else it returns `1`.
