# B-Tree
## insert方法的一些记录：

 <img src="./Images/1.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/2.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/3.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/4.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/5.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/6.jpg" width = "300" height = "400" alt="图片名称" align=center />

# remove
记录remove的一些思路：  
--    
 <img src="Images/remove1.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="Images/remove2.jpg" width = "300" height = "400" alt="图片名称" align=center /> 

<img src="Images/remove3.jpeg" width = "300" height = "400" alt="图片名称" align=center />  



# 如何测试：
----
测试的时候各种问题都会出现，记录一些测试心得在这里。  
----
 <img src="Images/remove4.jpeg" width = "300" height = "400" alt="图片名称" align=center /> 
  <img src="Images/remove5.jpeg" width = "300" height = "400" alt="图片名称" align=center />  



## 解决Show函数的换行问题
对于一个MAXIMUM=4的B-Tree来说Show函数输出以下内容并不是很友好，因为不能明显的表现出树各节点的关系。
```
27 54
9 18 --|||--36 45 --|||--63 72 81 90
3 6 --|||--12 15 --|||--21 24
30 33 --|||--39 42 --|||--48 51
48 51 --|||--57 60 --|||--66 69 --|||--84 87 --|||--93 96
1 2 --|||--4 5 --|||--7 8
10 11 --|||--13 14 --|||--16 17
16 17 --|||--19 20 --|||--22 23
22 23 --|||--28 29 --|||--31 32
31 32 --|||--37 38 --|||--40 41
40 41 --|||--46 47 --|||--49 50
40 41 --|||--46 47 --|||--49 50
49 50 --|||--55 56 --|||--58 59
58 59 --|||--64 65 --|||--67 68
67 68 --|||--82 83 --|||--85 86
85 86 --|||--91 92 --|||--94 95 99
```

# fix_shortage()中极其愚蠢的错误
这个错误是这样的，我要释放一个节点，然后把之后的节点前移。然后我先前移覆盖了要释放的位置，再把对应位置的内容释放掉（但其实这个内容已经被覆盖了），我释放掉了不该释放的内容。
```cpp
for (j = 1; j < child_count-1; j++) {
    subset[j] = subset[j + 1];
}
delete subset[1];
```
所以先删除指针再进行移位覆盖即可。

# size_t是无符号类型！循环的时候不要用size_t
