#include <iostream>
#include <functional>
#include <any>

class MyClass {
public:
    // Définition du type pour la fonction variadique
    template<typename... Args>
    using MyFunctionType = std::function<void(Args...)>;

    // Méthode pour stocker la fonction avec ses paramètres
    template<typename Func, typename... Args>
    void storeFunction(Func func, Args&&... args) {
        storedFunction = std::bind(func, std::forward<Args>(args)...);
    }

    // Méthode pour exécuter la fonction stockée
    void executeStoredFunction() {
        if (storedFunction) {
            storedFunction();
        } else {
            std::cout << "Aucune fonction n'est stockée." << std::endl;
        }
    }

private:
    MyFunctionType<> storedFunction;
};

// Fonction à appeler avec des paramètres variadiques
void myFunction(int &a, double b, const std::string& str) {
    std::cout << "Paramètres : " << a << ", " << b << ", " << str << std::endl;
}

int main() {
    MyClass myClassObject;

    // Stockage de la fonction avec ses paramètres variadiques
    int a = 10;
    myClassObject.storeFunction(myFunction, std::ref(a), 3.14, std::string("hello"));

    // Exécution de la fonction stockée
    myClassObject.executeStoredFunction();
    a=0;
    myClassObject.executeStoredFunction();

    return 0;
}