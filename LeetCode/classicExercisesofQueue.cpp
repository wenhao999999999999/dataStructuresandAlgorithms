// 队列的经典习题

#include <bits/stdc++.h>
using namespace std;

// 1.最近请求次数
    // 写一个 RecentCounter 类来计算特定时间范围内最近的请求
    // RecentCounter() 初始化计数器，请求数为 0 
    // int ping(int t) 在时间 t 添加一个新请求，其中 t 表示以毫秒为单位的某个时间
    // ，并返回过去 3000 毫秒内发生的所有请求数（包括新请求）。确切地说
    // ，返回在 [t-3000, t] 内发生的请求数。
class RecentCounter {
public :
    // 初始化一个队列，用于存储请求的时间
    queue<int> q;

    RecentCounter () {

    }

    int ping (int t) {
        q.push(t);

        // 只保留[t-3000, t]这个时间段内地的请求
        while (q.front() < t - 3000) {

            // t 是递增的，所以可以从队头删除 3000 毫秒之前的请求
            q.pop();
        }

        return q.size();
    }
    
};

// ************队列的相关设计***********
// 2.设计循环队列,你的实现应该支持如下操作：
    // MyCircularQueue(k): 构造器，设置队列长度为 k 。
    // Front: 从队首获取元素。如果队列为空，返回 -1 。
    // Rear: 获取队尾元素。如果队列为空，返回 -1 。
    // enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
    // deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
    // isEmpty(): 检查循环队列是否为空。
    // isFull(): 检查循环队列是否已满。
    // 请不要使用内置的队列库。

// 用环形数组实现动态容量循环队列 
// 模板类   
template<typename E>
class ArrayQueue {
private:
    // 队列有效元素数量
    int size;
    // 环形数组结构
    vector<optional<E>> data;
    // 数组初始容量大小
    static const int INIT_CAP = 2;
    // 队头索引，下一个入队元素会插入到的索引
    int first, last;

    void resize(int newCap) {
        vector<optional<E>> temp(newCap);

        // first ----- last
        // --- last    first ---

        for (int i = 0; i < size; i++) {
            temp[i] = data[(first + i) % data.size()];
        }

        // 注意：数组大小调整以后，队头指针指向索引为0的位置
        first = 0;
        last = size;

        // 原来的 data 释放其旧内容
        // 从 temp 中“偷走”底层资源（如堆上的数组指针）赋给 data
        data = move(temp);
    }
public:
    ArrayQueue(int initCap) : size(0), data(initCap), first(0), last(0) {}

    ArrayQueue() : ArrayQueue(INIT_CAP) {
        // 不传参数，默认大小为 INIT_CAP
    }

    // 增
    void enqueue(E e) {

        // 如果当前队列元素数量达到上限，就把队列容量扩充为原来的两倍
        if (size == data.size()) {
            resize(size * 2);
        }

        // 队尾添加元素
        data[last] = e;

        // 队尾指针后移
        last++;

        // 队尾指针超出索引范围，队尾指针移到开头
        if (last == data.size()) {
            last = 0;
        }
        // 元素数量+1
        size++;
    }

    // 删
    E dequeue() {

        // 如果队列为空，抛出异常
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }

        // 如果有效元素数量为当数组的
        if (size == data.size() / 4) {
            resize(data.size() / 2);
        }

        // 存储队头元素
        E oldVal = *data[first];

        // 队头元素置空
            // 置空的好处：
                // 显式释放资源（尤其对复杂类型），调用 reset() 可以立刻释放其所占用的内存（比如堆内存），而不是等到整个 std::vector 被销毁时才统一释放。
        data[first].reset();

        // 队头元素索引后移
        first++;

        // 队头指针超出索引范围，队头指针移到开头
        if (first == data.size()) {
            first = 0;
        }

        // 元素数量-1
        size--;

        // 返回删除的元素
        return oldVal;
    }

    // 查
    E peekFirst() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }
        return *data[first];
    }
    
    E peekLast() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }
        // 注意：如果队尾指针在开头，要返回索引为 data.size() - 1 的元素
        if (last == 0) return *data[data.size() - 1];
        return *data[last - 1];
    }
    
    int getSize() const {
        return size;
    }    

    bool isEmpty() const {
        return size == 0;
    }
};

// 循环队列实现定长版循环队列
class MyCircularQueue {
private:
    ArrayQueue<int> q;
    int maxCap;

public:
    MyCircularQueue(int k) : q(k), maxCap(k) {}

    bool enQueue(int value) {
        // 如果队列已经满了，则入队失败
        if (q.getSize() == maxCap) {
            return false;
        }

        // 入队
        q.enqueue(value);
        return true;
    }
    
    bool deQueue() {
        if (q.isEmpty()) {
            return false;
        }
        q.dequeue();
        return true;
    }
    
    int Front() {
        if (q.isEmpty()) {
            return -1;
        }
        return q.peekFirst();
    }

    int Rear() {
        if (q.isEmpty()) {
            return -1;
        }
        return q.peekLast();
    }

    bool isEmpty() {
        return q.isEmpty();
    }    
    
    bool isFull() {
        return q.getSize() == maxCap;
    }    
        
};

// 基于循环数组实现双端队列
template <typename E>
class MyArrayDeque {
private:
    int currentSize; // Renamed from size   
    vector<E> data;
    static const int INIT_CAP = 2;
    int first, last;

    void resize(int newCap) {
        vector<E> temp(newCap);
        // first ----- last
        // --- last    first ---

        for (int i = 0; i < currentSize; i++) {
            temp[i] = data[(first + i) % data.size()];
        }

        first = 0;
        last = currentSize;
        data = move(temp);
    }    
public:
    MyArrayDeque(int initCap) : currentSize(0), data(initCap), first(0), last(0) {}

    MyArrayDeque() : MyArrayDeque(INIT_CAP) {
        // 不传参数，默认大小为 INIT_CAP
    }    

    // last 是下一次应该添加元素的索引
    // first----last, [first, last)
    // 比如 first = 1，last = 3，size = 2

    // 从头部获取元素
    E getFirst() {
        if (isEmpty()) {
            throw out_of_range("No such element");
        }
        return data[first];
    }

    // 从尾部获取元素
    E getLast() {
        if (isEmpty()) {
            throw out_of_range("No such element");
        }

        if (last == 0) return data[data.size() - 1];
        return data[last - 1];
    } 
    
    // 从头部插入元素
    void addFirst(E e) {
        if (currentSize == data.size()) {
            resize(currentSize * 2);
        }

        // 情况一：first----last
        // 情况二：---last  first---

        // 左移 first，所以 first == 0 是一种特殊情况
        if (first == 0) {
            first = data.size() - 1;
        } else {
            first--;
        }
        // 插入元素
        data[first] = e;

        // 注意：插入元素后有效元素要+1
        currentSize++;
    }

    // 从尾部插入元素
    void addLast(E e) {
        if (currentSize == data.size()) {
            resize(currentSize * 2);
        }
        // 插入元素
        data[last] = e;
        last++;
        if (last == data.size()) {
            last = 0;
        }

        currentSize++;
    }

    // 从头部删除元素
    E removeFirst() {
        if (isEmpty()) {
            throw out_of_range("No such element");
        }

        if (currentSize == data.size() / 4) {
            resize(data.size() / 2);
        }

        E oldVal = data[first];
        data[first] = E(); // Assign default value

        first++;
        if (first == data.size()) {
            first = 0;
        }

        currentSize--;
        return oldVal;
    }
    
    // 从尾部删除元素
    E removeLast() {
        if (isEmpty()) {
            throw out_of_range("No such element");
        }

        if (currentSize == data.size() / 4) {
            resize(data.size() / 2);
        }

        // 情况一：first----last
        // 情况二：---last  first---

        // 左移 last，当 last == 0 的时候是特殊情况
        if (last == 0) {
            last = data.size() - 1;
        } else {
            last--;
        }
        E oldVal = data[last];
        // 删除元素
        data[last] = E(); // Assign default value

        currentSize--;
        return oldVal;
    }

    int size() {
        return currentSize;
    }

    bool isEmpty() {
        return currentSize == 0;
    }
};





// 设计循环双端队列，实现 MyCircularDeque 类
class MyCircularDeque {
private:
    int cap;
    MyArrayDeque<int> list;
public:

    MyCircularDeque(int k) : cap(k) {

    }

    bool insertFront(int value) {
        if (list.size() == cap) {
            return false;
        }

        list.addFirst(value);
        return true;
    }

    bool insertLast(int value) {
        if (list.size() == cap) {
            return false;
        }

        list.addLast(value);
        return true;
    }

    bool deleteFront() {
        if (list.isEmpty()) {
            return false;
        }

        list.removeFirst();
        return true;
    }

    bool deleteLast() {
        if (list.isEmpty()) {
            return false;
        }

        list.removeLast();
        return true;
    }

    int getFront() {
        if (list.isEmpty()) {
            return -1;
        }

        return list.getFirst();
    }

    int getRear() {
        if (list.isEmpty()) {
            return -1;
        }

        return list.getLast();
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    bool isFull() {
        return list.size() == cap;
    }

};


