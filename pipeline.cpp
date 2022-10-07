#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }
    
protected:
    
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const
    {
        if (ptr != nullptr)
            ptr->Process(move(email));
    }
    unique_ptr<Worker> ptr;
public:
    void SetNext(unique_ptr<Worker> next)
    {
        ptr = move(next);
    }
    
};

istream& operator>>(istream& is, Email& email)
{
    getline(is, email.from);
    getline(is, email.to);
    getline(is, email.body);
    
    return is;
}

class Reader : public Worker {
public:
    Reader(istream &in)
    {
        Email email;
        while (in>>email)
        {
            emails.push_back(make_unique<Email>(move(email)));
        }
    }
    void Run() override
    {
        for (auto &email : emails)
            PassOn(move(email));
    }
    void Process(unique_ptr<Email> email) override
    {
        PassOn(move(email));
    }
private:
    vector<unique_ptr<Email>> emails;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email&)>;
public:
    Filter(Function &function) : func(function)
    {}
    void Process(unique_ptr<Email> email) override
    {
        if (func(*email))
            PassOn(move(email));
    }
private:
    Function func;
};


class Copier : public Worker {
public:
    Copier(string &str) : reciever(str)
    {}
    void Process(unique_ptr<Email> email) override
    {
        unique_ptr<Email> copy = nullptr;
        if (email->to != reciever)
        {
            copy = make_unique<Email>(Email{email->from, reciever, email->body});
        }
        PassOn(move(email));
        if (copy != nullptr)
        {
            PassOn(move(copy));
        }
    }
private:
    string reciever;
};


class Sender : public Worker {
public:
    Sender (ostream &out) : output(out)
    {}
    void Process(unique_ptr<Email> email) override
    {
        output<<email->from<<"\n"<<email->to<<"\n"<<email->body<<"\n";
        PassOn(move(email));
    }
private:
    ostream &output;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in)
    {
        workers.push_back(unique_ptr<Reader>(new Reader(in)));
    }
    
    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter)
    {
        workers.push_back(unique_ptr<Filter>(new Filter(filter)));
        return  *this;
    }
    
    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient)
    {
        workers.push_back(unique_ptr<Copier>(new Copier(recipient)));
        return  *this;
    }
    
    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out)
    {
        workers.push_back(unique_ptr<Sender>(new Sender(out)));
        return  *this;
    }
    
    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build()
    {
        if (workers.size() == 0)
            return nullptr;
        for (size_t i = workers.size() - 1; i != 0; i--) {
            workers[i - 1]->SetNext(move(workers[i]));
        }
        unique_ptr<Worker> worker = move(workers[0]);
        workers.clear();
        return worker;
    }
private:
    vector<unique_ptr<Worker>> workers;
};


void TestSanity() {
    string input = (
                    "erich@example.com\n"
                    "richard@example.com\n"
                    "Hello there\n"

                    "erich@example.com\n"
                    "ralph@example.com\n"
                    "Are you sure you pressed the right button?\n"

                    "ralph@example.com\n"
                    "erich@example.com\n"
                    "I do not make mistakes of that kind\n"
                    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
                             "erich@example.com\n"
                             "richard@example.com\n"
                             "Hello there\n"

                             "erich@example.com\n"
                             "ralph@example.com\n"
                             "Are you sure you pressed the right button?\n"

                             "erich@example.com\n"
                             "richard@example.com\n"
                             "Are you sure you pressed the right button?\n"
                             );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
