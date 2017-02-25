Test your program with a message with block length 1024.
Test your program further by passing the encoded data through a binary symmetric channel. Try channel crossover probabilities of 0.0001, 0.001, 0.01 and 0.1. Calculate the probabilites of undetected errors.

消息位为1024bit，随机生成，校验过程严格按照规定。

N为100000（N更大可以得到更精确的数，但执行时间更长）。

加入project1老师给的代码生成随机数，建立BSC信道。

消息位越少，漏检的消息越多。例如，消息位为32bit，P=0.1, 漏检消息数在15+-
