# Uber - term project for OOP course

## Introduction

This is my implementation of the task - a simple taxi service management service.

## Compilation

You can use the provided CMakeLists.txt file if you want to!

## Usage

After compilation just execute it...

## Available commands
```
--------Users--------
register <type> <username> <password> <first name> <last name> <car number> <phone number>
login <username> <password>
logout
change_password <new password>
whoami

--------Order----------
order
check_order <id>
cancel_order <id>
pay <id> <amount>
rate <id> <rating>
add_money <amount>

--------Drivers----------
change_address <name> <x coordinate> <y coordinate>
check_messages
accept_order <id> <minutes> <amount>
decline_order <id>
pickup_passengers <id>
finish_order <id>
accept_payment <id> <amount>
```

## Example order workflow

```mermaid
flowchart TB
    A[Start] --> B[login] & B2[register]
    B --Driver--> C[change_address];
    B --Client--> D[order];
    D --Order info printed--> E[check_order < id >] --Get info about wait time, amount and driver--> J[add_money < amount >] --Add money to pay--> M[pay < id > < amount >] --After payment is accepted, rating can be added--> N[rate < id > < rating>];
    C --Current location to get nearest orders--> F[check_messages] --Accept order--> G[accept_order < id >] --Arrived at address--> H[pickup_passengers < id >] --Destination reached--> I[finish_order < id >] --Waiting for payment--> K[accept_payment < id > < amount >];
    F --Deny order--> L[deny_order < id >];
    
    D -.-> C -.-> F -.-> G -.-> E -.-> H -.-> I -.-> M -.-> K -.-> N;

    K & N --> X[exit]
```

###### Solid line indicates sequence of user action, dotted line indicates sequence of actions in time
