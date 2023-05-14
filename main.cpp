#include "Teste/teste.h"

#include "Domain/domain.h"
#include "UI/ui.h"
#include "Service/service.h"
#include "Repository/repo.h"
#include "UI/gui.h"
#include <assert.h>

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>


int main(int argc, char* argv[]) {

    //testAll<ListaRepo<Produs>>();

    QApplication Aplicatie(argc, argv);

    RepoAbstract<Produs>*repo = new RepoFisier<Produs>("produse.txt");
    Service service(repo);
    auto main = new GUI(service);
    main->show();

    Aplicatie.exec();


    /*

     run_all_tests();
    RepoAbstract<Produs>*repo = new RepoFisier<Produs>("produse.txt");
    Service service(repo);
    UI aplicatie(service);
  // aplicatie.run_ui();
     */
    return 0;
}
