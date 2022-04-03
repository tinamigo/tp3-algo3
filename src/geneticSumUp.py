import random as rand
import os
import sys

f2=open("ganadores7x6x4.txt", "+w")
for fitness in [0,1]:
	for crossover in [0,1,2]:
		for mutation in [0,1]:
			for selection in [0,1,2]:
				f=open("Experimentacion/genetic_grid/7x6x4/exp_genetic_7x6x4_"+str(fitness)+str(crossover)+str(mutation)+str(selection)+".csv", "r")
				for x in range(3186):
					linea = f.readline()
				f.close()
				f2.write(linea)
f2.close()
