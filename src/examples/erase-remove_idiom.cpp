#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Dummy {
public:
    Dummy(int id) : id(id) {}
    
    void markForDeletion() { toBeDeleted = true; }
    bool isMarkedForDeletion() const { return toBeDeleted; }
    
    int getId() const { return id; }

private:
    int id;
    bool toBeDeleted = false;
};

int main() {
    // Vector de punteros inteligentes a Dummy
    std::vector<std::unique_ptr<Dummy>> items;

    // Crear y agregar 5 objetos
    for (int i = 0; i < 5; ++i) {
        items.push_back(std::make_unique<Dummy>(i));
    }

    // Marcamos algunos para eliminar (por ejemplo los de ID 1 y 3)
    items[1]->markForDeletion();
    items[3]->markForDeletion();

    std::cout << "Antes de borrar:\n";
    for (const auto& item : items) {
        std::cout << "- Dummy ID: " << item->getId()
                  << " (marcado: " << item->isMarkedForDeletion() << ")\n";
    }

    // 💡 erase-remove idiom: borra todos los marcados
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [](const std::unique_ptr<Dummy>& item) {
                return item->isMarkedForDeletion();
            }),
        items.end()
    );

    std::cout << "\nDespués de borrar:\n";
    for (const auto& item : items) {
        std::cout << "- Dummy ID: " << item->getId() << '\n';
    }

    return 0;
}
