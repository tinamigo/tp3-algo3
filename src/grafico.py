import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import sys
sns.set()

parametro = sys.argv[1]

df1 = pd.read_csv("Experimentacion/exp_genetic/10x10x4/exp_genetic_10x10x4_0000.csv")
df2 = pd.read_csv("Experimentacion/exp_genetic/10x10x4/exp_genetic_10x10x4_0001.csv")
#df["cota"] = (2** df["N"]);
df3 = pd.DataFrame(columns=['Generacion', str(parametro)+str(1), str(parametro)+str(2)])

for i in range(200):
	is_gen_i = df1["Generacion"] == i
	df1_gen_i = df1[is_gen_i]

	is_gen_i2 = df2["Generacion"] == i
	df2_gen_i = df2[is_gen_i2]
	
	mean = df1_gen_i[parametro].mean()
	mean2 = df2_gen_i[parametro].mean()
	df3.loc[i] = [int(i)] + [mean] + [mean2]


'''
ax1 = sns.lmplot(x = 'Tiempo', y = 'cota', data = df);
plt.xlabel("t(n)");
plt.ylabel("cota(n)");

r = np.corrcoef(df["Tiempo"], df["cota"])[0,1];
print("El coeficiente de correlación de Pearson es: r="+str(r))

'''

# Graficamos el tiempo en función de n, con series variando m.
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df1);
ax1 = sns.lineplot(x="Generacion", y=str(parametro)+str(1), data=df3);
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df3);
ax2 = sns.lineplot(x="Generacion", y=str(parametro)+str(2), data=df3);
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df5);
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df6);
#ax1.legend(["Gorda", "Flaca","Gorda Inv", "Flaca Inv"]);
plt.xlabel("Generacion");
plt.ylabel("Valor");


plt.show()
