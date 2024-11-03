#include <iostream>
using namespace std;
enum State
{
    STATE_USING,    //桶正在使用
    STATE_UNUSE,    //桶从未使用
    STATE_DELE,     //桶使用过但是当前被删除了
};

struct Bucket
{
    Bucket(int value = 0,State state = State::STATE_UNUSE):key(value),state(state) {

    }
    int key;    //桶存储的数值
    State state;    //桶的状态
};

class HashTable
{
public:
    HashTable(int size = 0,double loadFactor = 0.75)
    :table_size(size)
    ,bucket_size(0)
    ,loadFactor(loadFactor)
    ,prime_index(0)
    {
        //先对传入的table_size进行合理转换
        if(table_size != prime_index) {
            int i = 0;
            for(;i < PRIME_SIZE;i++) {
                //从素数表中找第一个比传入的size值大的素数。
                if(size < prime_table[i]) {
                    break;
                }
            }
            table_size = prime_table[i];
            prime_index = i;
        }
        else {
            table_size = prime_table[size];
            prime_index = size;
        }

        bucket_ = new Bucket[table_size];
    }
    ~HashTable()
    {
        delete[] bucket_;
        bucket_ = nullptr;
    }
    //增加元素
    bool insert(int key) {
        int idx = key % table_size;
  
        //是否需要扩容
        double now_load_factor = bucket_size*1.0 / table_size;
        cout <<"now load factor : " <<now_load_factor << endl;
        if(now_load_factor > loadFactor) {
            expand();
        }

        int i = idx;
        do
        {
            if(bucket_[i].state == State::STATE_UNUSE) {
                //插入元素
                bucket_[i].state = State::STATE_USING;
                bucket_[i].key = key;
                bucket_size++;
                return true;
            }
            i = (i + 1) % table_size;
        } while (i != idx);
        return false;         
    }
    //删除元素
    bool erase(int key)
    {
        int idx = key % table_size;
        int i = idx;
        do
        {
            if(bucket_[i].state == State::STATE_USING && bucket_[i].key == key) {
                //删除元素
                bucket_[i].state = State::STATE_DELE;
                bucket_size--;
            }
            i = (i + 1) % table_size;
        } while (bucket_[i].state != State::STATE_UNUSE && i != idx);
        return true;
    }
    //查找元素
    bool find(int key)
    {
        int idx = key % table_size;
        int i = idx;
        do
        {
            if(bucket_[i].state == State::STATE_USING &&bucket_[i].key == key) {
                return true;
            }
            i = (i + 1) % table_size;
        } while (bucket_[i].state != State::STATE_UNUSE && i != idx);
        return false;
    }
private:
    void expand()
    {
        //判断是否具备扩容条件
        prime_index++;
        if(prime_index == PRIME_SIZE) {
            throw "Hash Table too many bucket,can not expand anymore!";
        }

        Bucket* newTable = new Bucket[prime_table[prime_index]];
        //将旧表数据拷贝到新表，将数据在新表重新哈希
        for(int i = 0;i < table_size;i++) {
            if(bucket_[i].state == State::STATE_USING) {
                //对新表重新哈希
                int k = bucket_[i].key % prime_table[prime_index];
                do {
                    if(newTable[k].state == State::STATE_UNUSE) {
                        newTable[k].key = bucket_[i].key;
                        newTable[k].state = State::STATE_USING;
                    }
                    //k = (k + 1) % prime_table[prime_index];
                }while (k !=  bucket_[i].key % prime_table[prime_index]);
            }
        }
        delete []bucket_;
        bucket_ = newTable;
        table_size = prime_table[prime_index];
    }
private:
    Bucket* bucket_;     //指向桶数组的指针
    int table_size;     //哈希表的大小
    int bucket_size;     //已经使用的桶的个数
    double loadFactor;      //装载因子

    //这里为什么要用素数，因为除余留数法，size是素数那么得到的结果会更加的平均分布，减少哈希冲突。
    static const int PRIME_SIZE = 10;    //素数表的大小
    static int prime_table[PRIME_SIZE];     //素数表
    int prime_index;        //当前使用的素数表下标
};

int HashTable::prime_table[PRIME_SIZE] = {3,7,23,47,97,251,443,911,1471,42773};

int main()
{
    HashTable hash;
    hash.insert(21);
    hash.insert(41);
    hash.insert(33);
    hash.insert(56);
    hash.insert(6);

    cout << hash.find(6) << endl;

    hash.erase(6);
    cout << hash.find(6) << endl;

}