#include "Teste/teste.h"

#include "Domain/domain.h"
#include "UI/ui.h"
#include "Service/service.h"
#include "Repository/repo.h"
#include <assert.h>

template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    double totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.getPret();
    }
    Produs p{ "total","tt","a",totalPrice };
    v.append(p);
    return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Produs p{ std::to_string(i) + "_type",std::to_string(i) + "_spec","a", i + 10.0 };
        v.append(p);
    }
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addPets(v, 100);
    assert(v.len() == 100);
    assert(v.search("50_type").getNume() == "50_type");

    MyVector v2{ v };//constructor de copiere
    assert(v2.len() == 100);
    assert(v2.search("50_type").getNume() == "50_type");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.len() == 100);
    assert(v3.search("50_type").getNume() == "50_type");

    auto v4 = testCopyIterate(v3);
    assert(v4.len() == 101);
    assert(v4.search("50_type").getNume() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addPets(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.len() == 0);

}

template <typename MyVector>
void testAll() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}


int main() {

    //testAll<ListaRepo<Produs>>();


    run_all_tests();
    RepoFisier<Produs> repo("produse.txt");
    Service service(repo);
    UI aplicatie(service);
  // aplicatie.run_ui();
    return 0;
}
