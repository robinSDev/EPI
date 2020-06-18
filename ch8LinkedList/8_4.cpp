#include "./singly_linked_list.hpp"
#include <vector> //for test data
using namespace std;

template <typename T>
SLL_Node<T> *find_cycle(SLL_Node<T> *&head)
{
    SLL_Node<T> *fast = head, *slow = head;

    while (fast and fast->next and fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            //cycle found
            SLL_Node<T> *cycle_length_calculator = fast;
            unsigned cycle_length = 0;
            do //let the 'cycle_length_calculator' go around in the cycle till it again reaches the start, i.e. 'slow'
            {
                ++cycle_length;
                cycle_length_calculator = cycle_length_calculator->next;
            } while (slow != cycle_length_calculator);
            cout << "cycle_length: " << cycle_length << endl;
            // If loop exists. Start slow from
            // head and fast from meeting point.
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }

            return slow;
        }
    }
    return nullptr; //no cycle
}

int main(int argc, char const *argv[])
{
    vector<int> v1 = {1, 3, 5, 7, 9, 11}, v2 = {2, 4, 6, 8, 10, 12};
    vector<int> v3 = v1;
    v3.reserve(v1.size() + v2.size());
    v3.insert(std::end(v3), std::begin(v2), std::end(v2));

    LinkedList<int> l1(v1), l2(v2), l3(v3);
    l2.tail->next = l2.head->next->next;
    l1.tail->next = l1.head;

    cout << l1.head << " " << l2.tail->next << endl;

    cout << find_cycle(l1.head)->data << endl;
    cout << find_cycle(l2.head)->data << endl;
    
    //output should be 0
    cout << find_cycle(l3.head);

    return 0;
}