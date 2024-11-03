#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class hashTable
{
public:
    hashTable(int size = prime_table[0],double factor_load = 0.75)
    :use_buket_size(0)
    ,factor_load(factor_load)
    ,prime_index(0)
    {
        //判断传入的size是否符合素数表
        if(size != prime_table[0]) {
            for(;prime_index != PRIME_SIZE;prime_index++) {
                if(size >= prime_table[prime_index]) {
                    break;
                }
            }
        }
        if(prime_index == PRIME_SIZE) {
            prime_index--;
        }
        table.resize(prime_table[prime_index]);
    }
    //相同的key会被忽略
    void insert(int key) {
        //是否需要扩容
        double now_factor_load = use_buket_size * 1.0 / table.size();
        std::cout << "now factor load : "<< now_factor_load << std::endl;
        if(now_factor_load > factor_load) {
            expand();
        }

        int idx = key % table.size();
        if(table[idx].empty()) {
            //当前桶没有放入链表，直接插入。
            table[idx].emplace_front(key);
            use_buket_size++;
        } else {
            //发生哈希冲突
            //元素key不存在链表中才进行插入
            auto it = std::find(table[idx].begin(),table[idx].end(),key);
            if(it == table[idx].end()) {
                table[idx].emplace_front(key);
            }
        }
    }
    void erase(int key)
    {
        int idx = key % table.size();
        if(table[idx].empty()) {
            return;
        } else {
            auto it = std::find(table[idx].begin(),table[idx].end(),key);
            if(it != table[idx].end()) {
                table[idx].erase(it);
                //链表是否为空
                if(table[idx].empty()) {
                    use_buket_size--;
                }
            }
        }
    }
    bool find(int key) {
        int idx = key % table.size();
        auto it = std::find(table[idx].begin(),table[idx].end(),key);
        return it != table[idx].end();
    }
private:
    void expand()
    {
        prime_index++;
        //判断边界
        if(prime_index == PRIME_SIZE) {
            throw "Hash Table too many bucket,can not expand anymore!";
        }

        use_buket_size = 0;
        std::vector<std::list<int>> old_table;
        table.swap(old_table);
        table.resize(prime_table[prime_index]);
        for(const auto& bucket : old_table) {  
            for(int data : bucket) {
                //将元素拷贝至新表，并且重新哈希
                int idx = data % table.size();  
                if(table[idx].empty()) {
                    use_buket_size++;
                }
                table[idx].emplace_front(data);
            }
        }
        
    }

    
private:
    std::vector<std::list<int>> table;  //存储哈希表
    int use_buket_size;     //已经使用桶的个数
    double factor_load;     //装载因子

    //这里为什么要用素数，因为除余留数法，size是素数那么得到的结果会更加的平均分布，减少哈希冲突。
    static const int PRIME_SIZE = 10;    //素数表的大小
    static int prime_table[PRIME_SIZE];     //素数表
    int prime_index;        //当前使用的素数表下标
};

int hashTable::prime_table[PRIME_SIZE] = {3,7,23,47,97,251,443,911,1471,42773};


int main()
{
    hashTable hash;
    hash.insert(21);
    hash.insert(33);
    hash.insert(41);
    hash.insert(4);
    hash.insert(74);
    hash.insert(23);
    hash.insert(9);
    hash.insert(6);
    hash.insert(2);
    hash.insert(17);
    hash.insert(51);
    hash.insert(99);
    hash.insert(77);
    hash.insert(722);
    hash.insert(786);

    hash.insert(56);
    std::cout << hash.find(6) << std::endl;

    hash.erase(6);
    std::cout << hash.find(6) << std::endl;

}