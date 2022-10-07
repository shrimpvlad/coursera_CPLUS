#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>


using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
    
    bool operator== (const Record &record) const
    {
        return (id == record.id && title == record.title && user == record.user && timestamp == record.timestamp && karma == record.karma);
    }
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record& record)
    {
        auto [it,flag] = base.insert({record.id, Data{record,{},{},{}}});
        if (!flag)
        {
            return false;
        }
        auto& item = it->second;
        const auto& recordRef = item.record_;
        item.time_it = time.insert({record.timestamp, recordRef});
        item.karma_it = karma.insert({record.karma, recordRef});
        item.user_it = user.insert({record.user, recordRef});
        return true;
    }
    const Record* GetById(const string& id) const
    {
        auto it = base.find(id);
        if (it != base.end())
            return (&it->second.record_);
        return nullptr;
    }
    bool Erase(const string& id)
    {
        if (base.count(id))
        {
            auto &tmp = base[id];
            time.erase(tmp.time_it);
            karma.erase(tmp.karma_it);
            user.erase(tmp.user_it);
            base.erase(id);
            return true;
        }
        return false;
        
    }
    
    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        auto it1 = time.lower_bound(low);
        auto it2 = time.upper_bound(high);
        for (;it1!=it2;++it1)
        {
            if (!callback(it1->second))
                break;
        }
    }
    
    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        auto it1 = karma.lower_bound(low);
        auto it2 = karma.upper_bound(high);
        for (;it1!=it2;++it1)
        {
            if (!callback(it1->second))
                break;
        }
    }
    
    template <typename Callback>
    void AllByUser(const string& us, Callback callback) const
    {
        auto [it1, it2] = user.equal_range(us);
        for (;it1!=it2;++it1)
        {
            if (!callback(it1->second))
                break;
        }
    }
    
private:
    
    template <typename T>
    using mm = multimap<T, const Record&>;
    
    struct Data {
        Record record_;
        mm<int>::iterator time_it;
        mm<int>::iterator karma_it;
        mm<string>::iterator user_it;
    };
    
    unordered_map<string, Data> base;
    
    mm<int> time;
    mm<int> karma;
    mm<string> user;
    
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;
    
    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});
    
    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });
    
    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});
    
    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });
    
    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";
    
    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});
    
    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
