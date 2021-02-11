#ifndef DUCOLIB_H
#define DUCOLIB_H

int ducologin(int sock, char *username, char *password);
int ducobalance(int sock);
int sendduco(int sock, double amount, char *recipient);
int connectDuco();
#endif
