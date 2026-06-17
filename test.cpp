#include <iostream>
#include <cassert>
#include <string>

#include "src/Exceptions.hpp"
#include "src/DynamicArray.hpp"
#include "src/LinkedList.hpp"
#include "src/MutableArraySequence.hpp"
#include "src/MutableListSequence.hpp"
#include "src/ImmutableArraySequence.hpp"
#include "src/ImmutableListSequence.hpp"
#include "src/Utilities.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// Вспомогательные функции для Map/Where/Reduce
int squareFunc(int x) { return x * x; }
bool isEvenFunc(int x) { return x % 2 == 0; }
int sumReducer(int acc, int x) { return acc + x; }

// ============================================================================
// 1. ТЕСТЫ ДЛЯ DYNAMIC ARRAY
// ============================================================================
void test_DynamicArray_1_ConstructorAndResize() {
    DynamicArray<int> arr(5);
    assert(arr.GetSize() == 5);
    for (int i = 0; i < 5; i++) arr.Set(i, i * 10);
    
    arr.Resize(8);
    assert(arr.GetSize() == 8);
    assert(arr.Get(0) == 0);
    assert(arr.Get(4) == 40);
}

void test_DynamicArray_2_CopyAndMove() {
    int data[] = {1, 2, 3};
    DynamicArray<int> first(data, 3);
    DynamicArray<int> copy(first);
    
    assert(copy.GetSize() == 3);
    copy.Set(0, 99);
    assert(first.Get(0) == 1);
    
    DynamicArray<int> moved(std::move(first));
    assert(moved.GetSize() == 3);
    assert(moved.Get(1) == 2);
}

void test_DynamicArray_3_Exceptions() {
    DynamicArray<int> arr(2);
    try {
        arr.Get(5);
        assert(false);
    } catch (const IndexOutOfRange& e) {
        assert(true);
    }
}

// ============================================================================
// 2. ТЕСТЫ ДЛЯ LINKED LIST
// ============================================================================
void test_LinkedList_1_AppendPrepend() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Prepend(5);
    
    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 5);
    assert(list.Get(1) == 10);
    assert(list.GetLast() == 20);
}

void test_LinkedList_2_InsertAndRemove() {
    int data[] = {1, 3};
    LinkedList<int> list(data, 2);
    list.InsertAt(2, 1);
    
    assert(list.GetLength() == 3);
    assert(list.Get(1) == 2);
    
    int removed = list.RemoveAt(1);
    assert(removed == 2);
    assert(list.GetLength() == 2);
    assert(list.Get(1) == 3);
}

void test_LinkedList_3_Exceptions() {
    LinkedList<int> emptyList;
    try {
        emptyList.GetFirst();
        assert(false);
    } catch (const EmptyCollectionError& e) {
        assert(true);
    }
}

// ============================================================================
// 3. ТЕСТЫ ДЛЯ MUTABLE ARRAY SEQUENCE
// ============================================================================
void test_MutableArray_1_BasicOps() {
    MutableArraySequence<int> seq;
    seq.Append(1)->Append(2)->Prepend(0);
    
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 0);
    assert(seq.Get(1) == 1);
    assert(seq.GetLast() == 2);
}

void test_MutableArray_2_SubsequenceAndConcat() {
    int data[] = {10, 20, 30, 40};
    MutableArraySequence<int> seq(data, 4);
    
    Sequence<int>* sub = seq.GetSubsequence(1, 2);
    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 20);
    
    MutableArraySequence<int> other;
    other.Append(50);
    Sequence<int>* concatRes = seq.Concat(other);
    assert(concatRes->GetLength() == 5);
    assert(concatRes->GetLast() == 50);
    
    delete sub;
    delete concatRes;
}

void test_MutableArray_3_Operators() {
    MutableArraySequence<int> seq1;
    seq1.Append(1);
    MutableArraySequence<int> seq2;
    seq2.Append(1);
    
    assert(seq1 == seq2);
    seq1[0] = 5;
    assert(seq1.Get(0) == 5);
}

// ============================================================================
// 4. ТЕСТЫ ДЛЯ MUTABLE LIST SEQUENCE
// ============================================================================
void test_MutableList_1_BasicOps() {
    MutableListSequence<std::string> seq;
    seq.Append("world");
    seq.Prepend("hello");
    
    assert(seq.GetLength() == 2);
    assert(seq.GetFirst() == "hello");
    assert(seq.GetLast() == "world");
}

void test_MutableList_2_InsertAt() {
    int data[] = {10, 30};
    MutableListSequence<int> seq(data, 2);
    seq.InsertAt(20, 1);
    
    assert(seq.GetLength() == 3);
    assert(seq.Get(1) == 20);
}

void test_MutableList_3_Subsequence() {
    int data[] = {1, 2, 3, 4};
    MutableListSequence<int> seq(data, 4);
    Sequence<int>* sub = seq.GetSubsequence(0, 2);
    
    assert(sub->GetLength() == 3);
    assert(sub->GetFirst() == 1);
    assert(sub->GetLast() == 3);
    delete sub;
}

// ============================================================================
// 5. ТЕСТЫ ДЛЯ IMMUTABLE ARRAY SEQUENCE
// ============================================================================
void test_ImmutableArray_1_Immutability() {
    ImmutableArraySequence<int> seq;
    Sequence<int>* next1 = seq.Append(1);
    
    assert(seq.GetLength() == 0);
    assert(next1->GetLength() == 1);
    assert(next1->Get(0) == 1);
    
    delete next1;
}

void test_ImmutableArray_2_Operators() {
    int data1[] = {1, 2};
    int data2[] = {3, 4};
    ImmutableArraySequence<int> imm1(data1, 2);
    ImmutableArraySequence<int> imm2(data2, 2);
    
    ImmutableArraySequence<int> sum = imm1 + imm2;
    assert(sum.GetLength() == 4);
    assert(sum.Get(2) == 3);
}

void test_ImmutableArray_3_Builder() {
    ImmutableArraySequence<int> seq;
    ISequenceBuilder<int>* builder = seq.CreateBuilder();
    builder->Append(10)->Append(20)->Append(30);
    
    Sequence<int>* built = builder->Build();
    assert(built->GetLength() == 3);
    assert(built->Get(1) == 20);
    
    delete builder;
    delete built;
}

// ============================================================================
// 6. ТЕСТЫ ДЛЯ IMMUTABLE LIST SEQUENCE
// ============================================================================
void test_ImmutableList_1_Immutability() {
    ImmutableListSequence<int> seq;
    Sequence<int>* next = seq.Prepend(100);
    
    assert(seq.GetLength() == 0);
    assert(next->GetLength() == 1);
    assert(next->Get(0) == 100);
    
    delete next;
}

void test_ImmutableList_2_EqualOperator() {
    int data[] = {5, 6, 7};
    ImmutableListSequence<int> l1(data, 3);
    ImmutableListSequence<int> l2(data, 3);
    
    assert(l1 == l2);
}

// ============================================================================
// 7. ТЕСТЫ ДЛЯ ИТЕРАТОРОВ (ENUMERATORS)
// ============================================================================
void test_Enumerator_1_ArraySequence() {
    int data[] = {10, 20, 30};
    MutableArraySequence<int> seq(data, 3);
    IEnumerator<int>* en = seq.GetEnumerator();
    
    assert(en->MoveNext() == true);
    assert(en->GetCurrent() == 10);
    assert(en->MoveNext() == true);
    assert(en->GetCurrent() == 20);
    assert(en->MoveNext() == true);
    assert(en->GetCurrent() == 30);
    assert(en->MoveNext() == false);
    
    en->Reset();
    assert(en->MoveNext() == true);
    assert(en->GetCurrent() == 10);
    
    delete en;
}

void test_Enumerator_2_LinkedList() {
    LinkedList<int> list;
    list.Append(5);
    IEnumerator<int>* en = list.GetEnumerator();
    
    assert(en->MoveNext() == true);
    assert(en->GetCurrent() == 5);
    assert(en->MoveNext() == false);
    
    delete en;
}

// ============================================================================
// 8. ТЕСТЫ ДЛЯ ФУНКЦИОНАЛЬНЫХ МЕТОДОВ СБОРКИ (MAP/WHERE/REDUCE)
// ============================================================================
void test_Functional_1_Map() {
    int data[] = {1, 2, 3};
    MutableArraySequence<int> seq(data, 3);
    Sequence<int>* mapped = seq.Map(squareFunc);
    
    assert(mapped->GetLength() == 3);
    assert(mapped->Get(0) == 1);
    assert(mapped->Get(1) == 4);
    assert(mapped->Get(2) == 9);
    
    delete mapped;
}

void test_Functional_2_Where() {
    int data[] = {1, 2, 3, 4, 5, 6};
    MutableListSequence<int> seq(data, 6);
    Sequence<int>* filtered = seq.Where(isEvenFunc);
    
    assert(filtered->GetLength() == 3);
    assert(filtered->Get(0) == 2);
    assert(filtered->Get(1) == 4);
    assert(filtered->Get(2) == 6);
    
    delete filtered;
}

void test_Functional_3_Reduce() {
    int data[] = {1, 2, 3, 4};
    MutableArraySequence<int> seq(data, 4);
    int sum = seq.Reduce(sumReducer, 0);
    
    assert(sum == 10);
}

// ============================================================================
// 9. ТЕСТЫ ДЛЯ SEQUENCE UTILITIES (ZIP/UNZIP/SPLIT)
// ============================================================================
void test_Utilities_1_Zip() {
    int d1[] = {1, 2};
    int d2[] = {10, 20};
    MutableArraySequence<int> s1(d1, 2);
    MutableArraySequence<int> s2(d2, 2);
    
    Sequence<SequenceUtilities::Pair<int, int>>* zipped = SequenceUtilities::Zip(s1, s2);
    assert(zipped->GetLength() == 2);
    assert(zipped->Get(0).first == 1);
    assert(zipped->Get(0).second == 10);
    assert(zipped->Get(1).first == 2);
    assert(zipped->Get(1).second == 20);
    
    delete zipped;
}

void test_Utilities_2_Unzip() {
    using namespace SequenceUtilities;
    Pair<int, int> data[] = { {1, 10}, {2, 20} };
    MutableArraySequence<Pair<int, int>> pairs(data, 2);
    
    Pair<Sequence<int>*, Sequence<int>*> unzipped = Unzip(pairs);
    assert(unzipped.first->GetLength() == 2);
    assert(unzipped.second->GetLength() == 2);
    assert(unzipped.first->Get(1) == 2);
    assert(unzipped.second->Get(1) == 20);
    
    delete unzipped.first;
    delete unzipped.second;
}

void test_Utilities_3_Split() {
    int data[] = {1, 2, 0, 3, 4, 0, 5};
    MutableArraySequence<int> seq(data, 7);
    
    Sequence<Sequence<int>*>* parts = SequenceUtilities::Split(seq, 0);
    assert(parts->GetLength() == 3);
    assert(parts->Get(0)->GetLength() == 2);
    assert(parts->Get(1)->GetLength() == 2);
    assert(parts->Get(2)->GetLength() == 1);
    
    for(int i = 0; i < parts->GetLength(); i++) {
        delete parts->Get(i);
    }
    delete parts;
}

int main() {
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    std::cout << "=== Тестирование ===" << std::endl;

    // 1. DynamicArray
    test_DynamicArray_1_ConstructorAndResize();
    test_DynamicArray_2_CopyAndMove();
    test_DynamicArray_3_Exceptions();
    std::cout << "[ОК] Тесты DynamicArray успешно пройдены." << std::endl;

    // 2. LinkedList
    test_LinkedList_1_AppendPrepend();
    test_LinkedList_2_InsertAndRemove();
    test_LinkedList_3_Exceptions();
    std::cout << "[ОК] Тесты LinkedList успешно пройдены." << std::endl;

    // 3. MutableArraySequence
    test_MutableArray_1_BasicOps();
    test_MutableArray_2_SubsequenceAndConcat();
    test_MutableArray_3_Operators();
    std::cout << "[ОК] Тесты MutableArraySequence успешно пройдены." << std::endl;

    // 4. MutableListSequence
    test_MutableList_1_BasicOps();
    test_MutableList_2_InsertAt();
    test_MutableList_3_Subsequence();
    std::cout << "[ОК] Тесты MutableListSequence успешно пройдены." << std::endl;

    // 5. ImmutableArraySequence
    test_ImmutableArray_1_Immutability();
    test_ImmutableArray_2_Operators();
    test_ImmutableArray_3_Builder();
    std::cout << "[ОК] Тесты ImmutableArraySequence успешно пройдены." << std::endl;

    // 6. ImmutableListSequence
    test_ImmutableList_1_Immutability();
    test_ImmutableList_2_EqualOperator();
    std::cout << "[ОК] Тесты ImmutableListSequence успешно пройдены." << std::endl;

    // 7. Enumerators
    test_Enumerator_1_ArraySequence();
    test_Enumerator_2_LinkedList();
    std::cout << "[ОК] Тесты Итераторов (Enumerators) успешно пройдены." << std::endl;

    // 8. Map/Where/Reduce
    test_Functional_1_Map();
    test_Functional_2_Where();
    test_Functional_3_Reduce();
    std::cout << "[ОК] Тесты Map/Where/Reduce успешно пройдены." << std::endl;

    // 9. Utilities
    test_Utilities_1_Zip();
    test_Utilities_2_Unzip();
    test_Utilities_3_Split();
    std::cout << "[ОК] Тесты Утилит (Zip/Unzip/Split) успешно пройдены." << std::endl;
    return 0;
}