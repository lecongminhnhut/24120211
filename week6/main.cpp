#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
using namespace std;
struct Company {
    string name;
    string profit_tax;
    string address;
};
struct HashNode {
    string key;
    Company val;
    bool isDeleted;
    HashNode() : key(""), isDeleted(false) {}
    HashNode(string k, Company v) : key(k), val(v), isDeleted(false) {}
};

struct HashTable {
    static const int TABLE_SIZE = 2000;
    vector<HashNode> table;

    HashTable() {
        table.resize(TABLE_SIZE);
    }
};

vector<Company> readCompanyList(string filename)
{
    vector<Company> companies;
    ifstream fin (filename);
    if (!fin) {
        cerr << "Không thể mở file đầu vào.\n";
        return companies;
    }
    string line;
    // Bỏ qua dòng tiêu đề
    getline(fin, line);
    while (getline(fin, line)) {
        stringstream ss(line);
        string part;
        vector<string> parts;

    // Phân tách dòng bằng dấu '|'
    while (getline(ss, part, '|')) 
    {
        parts.push_back(part);
    }

    if (parts.size() >= 3) {
        Company company;
        company.name = parts[0];
        company.profit_tax = parts[1];
        company.address = parts[2];
        companies.push_back(company);
    }
    }
    fin.close();
    return companies;
}

long long hashString(string company_name)
{
    long long temp = 1;
    long long hash = 0;
    unsigned int n = company_name.size();
    if (n > 20)
    {
        company_name = company_name.substr(n - 20);
        n = company_name.size();
    }
    for (unsigned int i = 0; i < n; i++)
    {
        hash = (hash + (temp * company_name[i]) % 2000) % 2000;
        temp = ((temp) * 31) % 2000;
    }
    return hash; 
}


HashTable* createHashTable(vector<Company> list_company)
{

    HashTable* hashTable = new HashTable();

    for (unsigned int i = 0; i < list_company.size(); ++i) {
        string key = list_company[i].name; // Giả sử Company có trường 'name'
        int hashIndex = hashString(key);

        // Đảm bảo hashIndex luôn dương
        if (hashIndex < 0) {
            hashIndex += HashTable::TABLE_SIZE;
        }

        // Linear Probing để tìm vị trí trống
        while (!hashTable->table[hashIndex].key.empty() && !hashTable->table[hashIndex].isDeleted) {
            hashIndex = (hashIndex + 1) % HashTable::TABLE_SIZE;
        }

        // Gán phần tử vào bảng
        hashTable->table[hashIndex] = HashNode(key, list_company[i]);
    }

    return hashTable;
}

void insert(HashTable* hash_table, Company company)
{
    string key = company.name;
    int company_Index = hashString(key);

    if (company_Index < 0)
    {
        company_Index += HashTable::TABLE_SIZE;
    }

    int startIndex = company_Index;
    bool inserted = false;

    do {
        if (hash_table->table[company_Index].key.empty() || hash_table->table[company_Index].isDeleted) 
        {
            hash_table->table[company_Index] = HashNode(key, company);
            inserted = true;
            break;
        }
        company_Index = (company_Index + 1) % HashTable::TABLE_SIZE;
    } while (company_Index != startIndex);

    if (!inserted) {
        return;
    }
}

Company* search(HashTable* hash_table, string company_name)
{
    int hashIndex = hashString(company_name);

    if (hashIndex < 0)
        hashIndex += HashTable::TABLE_SIZE;

    int startIndex = hashIndex;

    while (!hash_table->table[hashIndex].key.empty())
    {
        if (!hash_table->table[hashIndex].isDeleted &&
            hash_table->table[hashIndex].val.name == company_name)
        {
            return &hash_table->table[hashIndex].val;
        }

        hashIndex = (hashIndex + 1) % HashTable::TABLE_SIZE;

        // Quay vòng lại vị trí ban đầu, dừng
        if (hashIndex == startIndex)
            break;
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
         cerr << "Usage: " << argv[0] << " ./MST.txt ./input.txt ./output.txt";
         return 1;
    }
    ifstream f_MST(argv[1]);
    ifstream fin(argv[2]);
    ofstream fout(argv[3]);

    if (!f_MST)
    {
        cerr << "Không thể mở file MST";
    }
    if (!fin) {
        cerr << "Không thể mở file đầu vào.\n";
        return 1;
    }
    if (!fout) {
        cerr << "Không thể mở file đầu ra.\n";
        return 1;
    }
    vector<Company> c = readCompanyList(argv[1]);
    HashTable* hash_table = createHashTable(c);
    Company* company = new Company();
    string line;
    while(getline(fin, line))
    {
        company = search(hash_table, line);
        if (company != NULL)
        {
            fout << company->name << "|" << company->profit_tax << "|" << company->address << endl;
        }
    }
    return 0;
}
