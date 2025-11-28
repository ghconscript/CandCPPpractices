import pandas as pd
import matplotlib.pyplot as plt

# 读取 CSV 文件
df = pd.read_csv('sort_performance.csv')

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(df['数据规模'], df['归并排序'], label='归并排序', marker='o')
plt.plot(df['数据规模'], df['快速排序'], label='快速排序', marker='s')
plt.plot(df['数据规模'], df['选择排序'], label='选择排序', marker='^')

# 设置图表属性
plt.xlabel('数据规模')
plt.ylabel('执行时间（秒）')
plt.title('排序算法性能对比')
plt.legend()
plt.grid(True)

# 显示图表
plt.show()