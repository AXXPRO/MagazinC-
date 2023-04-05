#include "Teste/teste.h"

#include "Domain/domain.h"
#include "UI/ui.h"
#include "Service/service.h"
#include "Repository/repo.h"
int main() {

    run_all_tests();
    Repo repo;
    Service service(repo);
    UI aplicatie(service);
    aplicatie.run_ui();
    return 0;
}
