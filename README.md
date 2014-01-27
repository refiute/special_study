# 特別研究

様々な大きさの巡回セールスマン問題に対する解法に関する研究

## アプローチ1 bitを用いた動的計画法による解法

まず、一般的なアプローチとして経路をすべて列挙するという物があるがこれは計算量がO(n!)かかり、nが11程度で一般のPCで解けないようになる。

そこで、すでに行った場所と今いる場所がわかればそれ以前の情報は不要であることを利用して、
(今いる場所,すでに行った場所)という状態にその状態にたどり着くまでのコスト(距離)を記録しておいて、
同じ探索を行わないようにすることで計算量をO(2^n×n^2)に落とすことが出来る。

```TeX
O(2^m*m^2)
```

## アプローチ2 遺伝的アルゴリズムによる解法
