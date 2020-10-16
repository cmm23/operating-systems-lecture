#Carolina Medina A00825117
#Graph: https://drive.google.com/file/d/1WokOMFotWjlOBiaQU-7m3ofOXqgtnCBy/view?usp=sharing

#import numpy as np
import matplotlib.pyplot as plt

def printInfo():
	print ("Quantums")
	print (quantums)
	print ("Avg Turnaround times:")
	print (avg_turnaround_tms)
	print("Initial processes")
	print (processes)


quantum = int(input("Enter the initial quantum: "))
quantum_max = int(input("Enter the final quantum: "))
quantums = []
avg_turnaround_tms = []

processes =[2,3,4,12,8,5,6,1]
num_processes = len(processes)
q = []

while quantum <= quantum_max:

    context_switch = 2
    execution_time = 0
    avg_turnaround_tm = 0.0

    i = 0
    quantums.append(quantum)

    while i < len(processes):
        q.append(processes[i])
        i+=1
       
    while 0<len(q):
        current_process = q.pop(0)
        if current_process <= quantum:
            execution_time += current_process
        else:
            remain_time = current_process - quantum
            execution_time+=quantum
            execution_time+=context_switch
            q.append(remain_time)


    avg_turnaround_tm = float(execution_time)/float(num_processes)
    avg_turnaround_tms.append(avg_turnaround_tm)
    quantum+=1

printInfo()

plt.plot(quantums, avg_turnaround_tms)
plt.title('Quantum time vs Turn around time')
plt.xlabel('Quantums')
plt.ylabel('TurnaroundTime')
plt.show()
