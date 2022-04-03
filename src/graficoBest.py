import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import sys
sns.set()

parametro = sys.argv[1]

df1 = pd.read_csv("Experimentacion/genetic_grid/7x6x4/exp_genetic_7x6x4_0000.csv")
df2 = pd.read_csv("Experimentacion/genetic_grid/7x6x4/exp_genetic_7x6x4_0001.csv")
df4 = pd.read_csv("Experimentacion/genetic_grid/7x6x4/exp_genetic_7x6x4_0002.csv")
#df["cota"] = (2** df["N"]);
df3 = pd.DataFrame(columns=['Generacion', str(parametro)+str(1), str(parametro)+str(2), str(parametro)+str(3)])

for i in range(200):
	gen_i = df1.loc[df1['Generacion'] == i]
	max1 = gen_i["puntos"].max()
	df_aux1 = gen_i.loc[gen_i['puntos'] == max1]
#	print(max1)
#	print(df_aux1)

	gen_i2 = df2.loc[df2['Generacion'] == i]
	max2 = gen_i2["puntos"].max()
	df_aux2 = gen_i2.loc[gen_i2['puntos'] == max2]

	gen_i4 = df4.loc[df4['Generacion'] == i]
	max4 = gen_i4["puntos"].max()
	df_aux4 = gen_i4.loc[gen_i4['puntos'] == max4]

	best1 = df_aux1[parametro].mean()
	best2 = df_aux2[parametro].mean()
	best4 = df_aux4[parametro].mean()

	df3.loc[i] = [int(i)] + [best1] + [best2] + [best4]


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
ax3 = sns.lineplot(x="Generacion", y=str(parametro)+str(3), data=df3);
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df5);
#ax1 = sns.lineplot(x="N", y="Tiempo", data=df6);
ax1.legend(["0000", "0001", "0002"]);
plt.xlabel("Generacion");
plt.ylabel("Valor de " + parametro);

plt.savefig('Graficos/crossover_' + parametro + '.png')

