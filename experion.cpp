#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<string,int> players;
unordered_map<string,vector<string>> batsmen;
unordered_map<string,vector<string>> bowlers;
void split(string str,char tok,vector<string>& out){
    int pos;
    string cur;
    out.push_back(str);
    while(true){
        cur=out.back();
        int pos;
        pos=cur.find(tok);
        if(cur.back()=='\"'){
          cout<<cur<<endl;
          cur.pop_back();
          pos=cur.find('\"');
        }
        if(pos==string::npos)
          break;
        out.back()=cur.substr(0,pos);
        out.push_back(cur.substr(pos+1,cur.size()-(pos+1)));
    }
}
class csv{
  public:
    csv(string file){
      ifstream fin;
      fin.open(file);
      if(!fin.is_open()){
        cout<<"[FATAL] Failed to open dataset " + file;
        exit(1);
      }
      string line;
      getline(fin,line);
      line.pop_back();
      vector<string> colv;
      split(line,',',colv);
      for(int i=0;i<colv.size();i++)
        col[colv[i]]=i;
      while(getline(fin,line)){
        line.pop_back();
        vector<string> ccol;
        split(line,',',ccol);
        vector<string> entry;
        data.push_back(entry);
        int ix=data.size()-1;
        for(int i=0;i<ccol.size();i++)
          data[ix].push_back(ccol[i]);
      }
    }
    string get(int entry,string field){
      return data[entry][col[field]];
    }
    int size(){
      return data.size();
    }
  private:
    unordered_map<string,int> col;
    vector<vector<string>> data;
};
int main(){
  csv log22("IPL_Ball_by_Ball_2022.csv");
  csv match22("IPL_Matches_2022.csv");
  unordered_map<int,string> btteam;
  unordered_map<int,string> blteam;
  for(int i=0;i<match22.size();i++){
    blteam[stoi(match22.get(i,"ID"))]=match22.get(i,"TossWinner");
    if(match22.get(i,"Team1")==match22.get(i,"TossWinner"))
      btteam[stoi(match22.get(i,"ID"))]=match22.get(i,"Team2");
    else
      btteam[stoi(match22.get(i,"ID"))]=match22.get(i,"Team1");
    cout<<stoi(match22.get(i,"ID"))<<' '<<btteam[stoi(match22.get(i,"ID"))]<<' '<<blteam[stoi(match22.get(i,"ID"))]<<endl;
  }
  return 0;
}
