# nearest neighbor
# 选择距离最近的向量作为lable
# 优点： 简单， 训练不需要花时间，但是测试花很长时间， 神经网络相反， 训练很久
# 数据维度较低的情况下是不错的选择， 但是对于图像来说维度太高不适合， 高维度下向量之间的距离是反直觉的
# 使用距离来对图片分类是不科学的， 另一个原因是容易被背景主导

# K-nearest neighbor
# 选择最近的K个进行投票
# k如何选取？ 选择L1还是L2？ 
# 注意：测试机是最宝贵的资源， 不到最后一步不能用测试集来调优
# 解决办法： 50000训练集中挑1000来做验证集。 使用验证集来调优， 最终选定k
# 交叉验证： 有时候训练集样本少， 使用交叉验证来确定k， 平均分成5分，4份作为训练集1分作为验证集，
#           最后取平均值作算法验证结果
# 交叉验证缺点： 实际应用中人们不太喜欢用交叉验证， 因为耗费计算资源， 直接把训练集的50-90比例划分
#              如果超参数数量多，验证集就多， 验证集又不够那就乖乖交叉验证吧


# L1 vs L2
# 面对两个向量之间的差异时， L2比L1更不能容忍这些差异。也就是说
# 相对于一个巨大的差异， L2更倾向于接受多个中等程度的差异
