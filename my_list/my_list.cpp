#include "List.h"
#include "Array.h"
#include <iostream>
#include <fstream>

using namespace std;

List<int> create_from_file(string filename)
{
    ifstream in(filename);

    List<int> l;
    int data;
    while (in >> data) l.push_back(data);

    in.close();

    return l;
}

List<int> l1_and_l2_minus_l3(List<int>& l1, List<int>& l2, List<int>& l3)
{
    List<int> result;
    int data;
    while (l1.get_p())
    {
        data = l1.get_value();
        if (l2.contains(data) && !l3.contains(data))
            result.push_back(data);
        l1.next();
    }

    return result;
}

List<int> copy_without_doubles(List<int>& l)
{
    List<int> result;
    int data;
    l.to_start();
    while (l.get_p())
    {
        data = l.get_value();
        if (!result.contains(data))
            result.push_back(data);

        l.next();
    }
    return result;
}

template <class T, class T1>
bool _find(T& cont, const T1& target)
{
    typename T::Iterator it = cont.begin();
    while (it != cont.end())
    {
        if (*it == target) return true;
        ++it;
    }
        
    return false;
}

template <class T, class T1>
void replace(T& cont, const T1& old_item, const T1& new_item)
{
    typename T::Iterator it = cont.begin();
    while (it != cont.end())
    {
        if (*it == old_item) *it = new_item;
        it++;
    }
}

template <class T>
void print(T& cont, ostream& out)
{
    typename T::Iterator it = cont.begin();
    while (it != cont.end())
    {
        out << *it << ' ';
        ++it;
    }
    out << endl;
}

template <class T>
bool is_in(T& cont1, T& cont2)
{
    bool all_in = true;
    bool this_in = false;
    typename T::Iterator it1 = cont1.begin();
    typename T::Iterator it2;
    while (it1 != cont1.end() && all_in)
    {
        this_in = false;
        it2 = cont2.begin();
        while (it2 != cont2.end() && !this_in)
        {
            if (*it1 == *it2) this_in = true;
            it2++;
        }
        if (!this_in) all_in = false;
        it1++;
    }

    return all_in;
}

template <class T >
bool is_subsequence(T& cont1, T& cont2)
{
    typename T::Iterator it1 = cont1.begin();
    typename T::Iterator it2 = cont2.begin();
    typename T::Iterator it22 = cont2.begin();
    bool result = false;
    bool is_start;
    while (it2 != cont2.end() && !result)
    {
        it1 = cont1.begin();
        if (*it2 == *it1)
        {
            it22 = it2;
            is_start = true;
            while (it1 != cont1.end() && it22 != cont2.end() && is_start)
            {
                if (*it1 != *it22) is_start = false;
                it1++;
                it22++;
            }
            if (it1 == cont1.end() && is_start) result = true;
        }
        it2++;
    }

    return result;
}

int main()
{
    /*List<int> l1;
    cin >> l1;
    cout << l1;
    List<int> l2;
    cin >> l2;
    cout << l2;
    bool are_equal = l1 == l2;
    cout << are_equal << endl;
    l2 = l1;
    cout << l2;
    l1.add_after_current(10);
    l1.add_before_current(10);
    cout << l1;*/


    List<int> l1 = create_from_file("l1.txt");
    cout << l1;
    List<int> l2 = create_from_file("l2.txt");
    cout << l2;
    /*List<int> l3 = create_from_file("l3.txt");
    cout << l3;

    List<int> l4 = l1_and_l2_minus_l3(l1, l2, l3);
    cout << l4;

    List<int> l5 = copy_without_doubles(l4);
    cout << l5;


    SortedList<int> sl4 = l4;
    cout << sl4;
    SortedList<int> sl5 = l5;
    cout << sl5;*/

    /*cout << _find(l1, 0) << endl;
    replace(l1, 7, 9);
    replace(l1, 1, 0);
    print(l1, cout);
    cout << is_in(l2, l1);*/
    //cout << is_subsequence(l2, l1);
    

    /*Array<int> a1(4);
    Array<int> a2(8);
    cin >> a1 >> a2;;
    cout << a1 << a2;
    cout << is_subsequence(a1, a2);*/
    //cout << is_in(a2, a1);
    //cout << _find(a1, 10) << endl;
    //replace(a1, 1, 0);
    //print(a1, cout);


}
