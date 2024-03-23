#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Atribute{
public:
    string name;
    float value;

    Atribute(string name, float value){
        this->name = name;
        this->value = value;
    }
    string getName(){
        return name;
    }
    float getValue(){
        return value;
    }

    void setValue(float value){
        this->value = value;
    }
};

class Entity{
public:
    string name;
    vector<Atribute> atributes;
    float mean;

    Entity(string name){
        this->name = name;
    }
    void addAtribute(Atribute atribute){
        atributes.push_back(atribute);
    }
    string getName(){
        return name;
    }
    vector<Atribute> getAtributes(){
        return atributes;
    }

    void setMean(float mean){
        this->mean = mean;
    }

    float getMean(){
        return mean;
    }

    void AtributesMean(){
        float sum = 0;
        for (int i = 0; i < atributes.size(); i++) {
            sum += atributes[i].getValue();
        }
        setMean(sum/atributes.size());
    }
};

bool isOutsideLimits(float value){
    return value < 0 || value > 10;
}

// Ordena el vector de entidades de mayor a menor
void sortEntities(vector<Entity> &entities){
    for (int i = 0; i < entities.size(); i++) {
        for (int j = 0; j < entities.size()-1; j++) {
            if(entities[j].getMean() < entities[j+1].getMean()){
                Entity temp = entities[j];
                entities[j] = entities[j+1];
                entities[j+1] = temp;
            }
        }
    }
}

void printEntities(vector<Entity> entities){
    for (int i = 0; i < entities.size(); i++) {
        cout << entities[i].getName() << " con un promedio de " << entities[i].getMean() << endl;
    }
}

void uniqueMeans(vector<Entity> &entities){
    set<float> means;
    for (int i = 0; i < entities.size(); i++) {
        means.insert(entities[i].getMean());
    }


    for (auto it = means.begin(); it != means.end(); it++) {
        cout << "Elementos con media " << *it << endl;
        for (int i = 0; i < entities.size(); i++) {
            if(entities[i].getMean() == *it){
                cout << entities[i].getName() << endl;
            }
        }
    }
}


int main() {
    float valor;
    string name;
    int numAttributes;
    vector<Atribute> attributes;
    vector<Entity> entities;

    cout << "Indique el número de atributos que tendrá cada elemento: ";
    cin >> numAttributes;

    for (int i = 0; i < numAttributes; i++) {
        cout << "\nIngrese el nombre de su atributo: ";
        cin >> name;
        Atribute attribute(name, 0);
        attributes.push_back(attribute);
    }

    cin.ignore();

    cout << "\nDiganos cual es el nombre de su elemento (o ingrese un espacio en blanco para salir): ";
    getline(cin, name);

    while (name != "") {
        Entity entity(name);
        for (int i = 0; i < numAttributes; i++) {
            cout << "Ingrese el valor de " << attributes[i].getName() << " para " << entity.getName() << ": ";
            cin >> valor;
            while(isOutsideLimits(valor)){
                cout << "El valor ingresado no es válido, por favor ingrese un valor entre 0 y 10: ";
                cin >> valor;
            }
            attributes[i].setValue(valor);
            entity.addAtribute(attributes[i]);
        }


        cin.ignore();

        entity.AtributesMean();

        entities.push_back(entity);

        cout << "\nDiganos cual es el nombre de su elemento (o ingrese un espacio en blanco para salir): ";
        getline(cin, name);
    }

    sortEntities(entities);

    printEntities(entities);


    return 0;
}

