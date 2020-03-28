import matplotlib.pyplot as plt 

# Hilos  tiempo
# 1        6 ms 
# 2        5 ms
# 4        6 ms
# 8        5 ms
# 16       5 ms

x = [6,5,4,6,5,5,4,5,6,5,5,6,5,5,5,5]
plt.plot(x)
plt.axis([1, 16, 0, 10])
plt.show()