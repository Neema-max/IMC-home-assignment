# IMC-home-assignment

Hi there here is my updated submition for IMC trading home assignment
Changes are appreciate.

Here is the feedback : 

ConcurrentQueue

Found the bug in the concurrent queue. Explanation is quite clear, but lacks proper punctuation, grammar is off and even has some typos.
We Would have also preferred a solution to be proposed

RPS

Player move() function should be pure virtual
Use of friend keyword is not ideal, and too casually used here
Symbol_rps meant to abstract move types but is quite messy
Every call to move() leaks memory, moves dynamically allocated and never deleted
Indentation is not consistent
Good player injection without relying on dynamic allocation
set_name not used
test_player not used, test_player::move does not return a value
Test doesn’t verify individual results, so as long as the game is balanced it will pass
