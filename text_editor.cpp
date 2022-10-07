#include <string>
#include <list>
#include <string_view>
#include "test_runner.h"
using namespace std;

class Editor
{
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
  {
    iter = str.begin();
  }
  void Left()
  {
    if (iter != str.begin())
    {
      iter = prev(iter);
    }
  }
  void Right()
  {
    if (iter != str.end())
    {
      iter = next(iter);
    }
  }
  void Insert(char token)
  {
    str.insert(iter, token);
  }
  void Cut(size_t tokens = 1)
  {
    buff.clear();
    auto it = iter;
    
    size_t i = 0;
    while (it != str.end() && i < tokens)
    {
      // cout << "it = " << *it << endl;
      buff.push_back(*it);
      ++it;
      // buff.push_back(*it);
      ++i;
    }
    str.erase(iter, it);
    iter = it;
  }
  void Copy(size_t tokens = 1)
  {
    buff.clear();
    auto it = iter;
    size_t i = 1;
    while (it != str.end() && i <= tokens)
    {
      buff.push_back(*it);
      ++i;
      ++it;
    }
  }
  void Paste()
  {
    for (auto it = buff.begin(); it != buff.end(); ++it)
    {
      Insert(*it);
    }
  }

  string GetText() const
  {
    string s = "";
    for (const auto &i : str)
      s += i;
    return s;
  }
  string GetBuff() const
  {
    string s = "";
    for (const auto &i : buff)
      s += i;
    return s;
  }
  char Iter() {
    return *iter;
  }

private:
  list<char> str;
  list<char> buff;
  list<char>::iterator iter;
};

void TypeText(Editor &editor, const string &text)
{
  for (char c : text)
  {
    editor.Insert(c);
  }
}

void TestEditing()
{
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i)
    {
      editor.Left();
    }
    // cout<<editor.Iter()<<endl;
    editor.Cut(first_part_len);
    // cout<<"eeeeeeeee: "<<editor.GetBuff()<<endl;
    for (size_t i = 0; i < text_len - first_part_len; ++i)
    {
      editor.Right();
    }
    // cout << editor.GetText() << endl;
    TypeText(editor, ", ");
    // cout << editor.GetText() << endl;
    editor.Paste();
    // cout << editor.GetText() << endl;
    editor.Left();
    editor.Left();
    editor.Cut(3);
    // cout << editor.GetText() << endl;

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse()
{
  Editor editor;

  const string text = "esreveR";
  for (char c : text)
  {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}