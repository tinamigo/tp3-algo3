import random as rand
import os
import sys

n = sys.argv[1]
m = sys.argv[2]
c = sys.argv[3]
inp = sys.argv[4]

os.system("make clean")
os.system("make genetic")

for fitness in [0]:
	for crossover in [1,2]:
		for mutation in [0,1]:
			for selection in [0,1,2]:
				if (crossover == 2 and mutation == 0 and selection == 2): 
					break
				if (crossover == 2 and mutation == 1):
					break
				f=open("input"+str(inp)+".txt", "w+")
				f.write(str(n)+"\n"
						+str(m)+"\n"
						+str(c)+"\n"
						+str(fitness)+"\n"
						+str(crossover)+"\n"
						+str(mutation)+"\n"
						+str(selection)+"\n")
				f.close()
				os.system( "./genetic < input"+str(inp)+".txt  > Experimentacion/exp_genetic/"+str(n)+"x"+str(m)+"x"+str(c)+"/exp_genetic_remake_"+str(n)+"x"+str(m)+"x"+str(c)+"_"+str(fitness)+str(crossover)+str(mutation)+str(selection)+".txt")