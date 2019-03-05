/* 	NAMA 	: MUHAMMAD FAHMI ALWAN
	NPM  	: 140810170052
	KELAS 	: B
	JUDUL	: GALE SHAPLEY
	DIBUAT	: 5/3/19
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;
 
const char *men_data[][6] = {
    { "victor",  "bertha","amy","diane","erika","clare" },
    { "wyatt",  "diane","bertha","amy","clare","erika" },
    { "xavier",  "bertha","erika","clare","diane","amy" },
    { "yancey",  "amy","diane","clare","bertha","erika" },
    { "zeus",   "bertha","diane","amy","erika","clare" }
};
 
const char *women_data[][6] = {
    { "amy",  "zeus","victor","wyatt","yancey","xavier" },
    { "bertha",  "xavier","wyatt","yancey","victor","zeus" },
    { "clare", "wyatt","xavier","yancey","zeus","victor" },
    { "diane",  "victor","zeus","yancey","xavier","wyatt" },
    { "erika",  "yancey","wyatt","zeus","xavier","victor" }
};
 
typedef vector<string> PrefList;
typedef map<string, PrefList> PrefMap;
typedef map<string, string> Couples;
 
// Does 'first' appear before 'second' in preference list? *membedakan list pertama sebagai yg punya preferensi dengan preferensinya
bool prefers(const PrefList &prefer, const string &first, const string &second)
{
    for (PrefList::const_iterator it = prefer.begin(); it != prefer.end(); ++it)
    {
        if (*it == first) return true; // orang yg punya preferensi
        if (*it == second) return false; // preferensinya
    }
    return false; // tidak ada preferensi

 
 
int main()
{
    PrefMap men_pref, women_pref;
    queue<string> bachelors;
 
    // init data structures
    for (int i = 0; i < 5; ++i) // orangnya
    {
        for (int j = 1; j < 6; ++j) // preferensinya
        {
              men_pref[  men_data[i][0]].push_back(  men_data[i][j]);
            women_pref[women_data[i][0]].push_back(women_data[i][j]);
        }
        bachelors.push(men_data[i][0]);
    }
 
    Couples engaged; // <perempuan, pria>
 
    cout << "Proses Matchmaking:\n"; //tampil proses untuk mendapatkan pasangan
    while (!bachelors.empty())
    {
        const string &suitor = bachelors.front();
        const PrefList &preflist = men_pref[suitor];
 
        for (PrefList::const_iterator it = preflist.begin(); it != preflist.end(); ++it)
        {
            const string &bride = *it;
 
            if (engaged.find(bride) == engaged.end()) // perempuannya masih kosong
            {
                cout << "\t" << bride << " dan " << suitor << "\n";
                engaged[bride] = suitor; // berpasangan
                break;
            }
 
            const string &groom = engaged[bride];
 
            if (prefers(women_pref[bride], suitor, groom))
            {
                cout << "\t" << bride << " memutus " << groom << " untuk " << suitor << "\n";
                bachelors.push(groom); // ngeputusin prianya
                engaged[bride] = suitor; // milih pria yang di preferensinya
                break;
            }
        }
        bachelors.pop(); // pop diakhir untuk tidak membatalkan preferensi pelamar
    }
 
    cout << "Hasil Pasangan\n"; //tampil hasil pasangan
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << "\t" << it->first << " dan " << it->second << "\n";
    }
 
}
