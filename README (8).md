English | [العربية](README.ar.md)

# ATM System — C++ Console App 🏧

A customer-facing ATM simulator in C++ — instead of a teller managing clients, this is the client logging in themselves to withdraw, deposit, and check their own balance. It reads and writes the exact same `ClientRecord.txt` used by the [Bank System](https://github.com/AhmadSlik/bank-system-cpp): one data store, two different front-ends.

> Project 2 of **Algorithms & Problem Solving Level 4** (Course 8 of Dr. Mohammed Abu-Hadhoud's programming roadmap).

## Features

- Customer login with **Account Number + PIN** (not a staff username/password — this is the self-service side)
- **Quick Withdraw** — pick from preset amounts (20, 50, 100, 200, 400, 600, 800, 1000)
- **Normal Withdraw** — enter any amount, as long as it's a multiple of 5 and within your balance
- **Deposit** — add money to your own account
- **Check Balance**
- Shares the same client file as the Bank System, so a deposit made here shows up there too

## Sample: Quick Withdraw

```
____________________________________________________
____________________________________________________
		QucikWithdraw Screen 
____________________________________________________
____________________________________________________
	[1] 20	[2] 50.
	[3] 100	[4] 200
	[5] 400	[6] 600
	[7] 800.[8] 1000
	[9] Exit
____________________________________________________
____________________________________________________
```

## How to Run

```bash
g++ main.cpp -o atm_system
./atm_system
```

> This program uses a Linux-specific system call (`system("clear")`) to clear the screen, so it runs best on Linux/macOS terminals. It expects a `ClientRecord.txt` file with existing accounts (created by the Bank System) in the same folder.

## Concepts Practiced

- Function overloading — two functions are both named `CheckBalance`, one for a single record and one that searches a list and calls the other; the compiler picks the right one from the argument types
- Two validation rules combined in one condition — a withdrawal must fit the balance *and* be a multiple of 5, matching how a real ATM only holds fixed denominations
- Reusing an existing file format so two completely separate programs (teller software, self-service ATM) share the same customer records without any conversion
- Recursion for session navigation and for retrying a failed account lookup

## Author

**Ahmad Slik** — 17 y/o self-taught AI builder, currently following Dr. Mohammed Abu-Hadhoud's programming roadmap.

- Portfolio: [ahmadslik.netlify.app](https://ahmadslik.netlify.app)
- GitHub: [@AhmadSlik](https://github.com/AhmadSlik)
