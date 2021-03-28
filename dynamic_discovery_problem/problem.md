# The dynamic discovery problem
One of the problems we face while creating distributed systems is discovery, i.e. how do nodes/pieces know about each other. If there is a static source, then it would not caue much problem; but what if the nodes/pieces come and go, this will lead to dynamic discovery problem.

The solution to this problem is to add an intermediary node or proxy.

For PUB/SUB we use XPUB and XSUB as intermediate proxy.