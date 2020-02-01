#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;


const int N = 50000;

pii edge[N]; //ok

int val[N]; //ok
vector<int> adj[N]; //ok

int sum_w[N][2]; //ok
int res[N][2]; //ok

int biggest[N][2]; //ok
int s_big[N][2]; //ok

int resFin[N][2];
pii posFin[N][2];
int profFin[N][2];
pii from[N][2];


int n;
int mini;

void solve(int id, int s)
{
    if(resFin[id][s] >= 0)
        return;

    resFin[id][s] = res[id][s];
    posFin[id][s] = mp(id, s);
    profFin[id][s] = 0;

    if(biggest[id][s] == -1)
        return;
    from[biggest[id][s]][s_big[id][s]] = mp(id, s);
    solve(biggest[id][s], s_big[id][s]);
    int prof_cur = 1 + profFin[biggest[id][s]][s_big[id][s]];
    int resCur = res[id][s] - res[biggest[id][s]][s_big[id][s]] - sum_w[biggest[id][s]][s_big[id][s]] + (sum_w[id][s] - sum_w[biggest[id][s]][s_big[id][s]]) * prof_cur + resFin[biggest[id][s]][s_big[id][s]];

    int xcur = posFin[biggest[id][s]][s_big[id][s]].x; int scur = posFin[biggest[id][s]][s_big[id][s]].y;
    while(xcur != id && sum_w[id][s] > 2*sum_w[xcur][scur]){
        resCur += 2*sum_w[xcur][scur] - sum_w[id][s];
        int x_nouv = from[xcur][scur].x;
        int s_nouv = from[xcur][scur].y;
        xcur = x_nouv; scur = s_nouv;
        prof_cur--;
    }

    // cout << id << " " << s << " -> " << xcur << " " << scur << " -> " << resCur << endl;

    posFin[id][s] = mp(xcur, scur);
    profFin[id][s] = prof_cur;
    resFin[id][s] = resCur;
}


void calc(int id, int s)
{
    if(sum_w[id][s] > 0)
        return; // Se o sumw de id, s tiver sido calculado pular
    int cur = (s == 0) ? edge[id].x : edge[id].y; //s determina o lado da edge que vai ser usado
    sum_w[id][s] = val[cur]; //sumw comeca com o valor original da edge
    res[id][s] = 0;
    for(int id_nouv : adj[cur]){ //para toodas as edges ligadas ao vertice curr
        if(id_nouv == id)
            continue;
        int s_nouv = (edge[id_nouv].x == cur) ? 1 : 0; //selecionar s de maneira a sair do vertice atual
        calc(id_nouv, s_nouv); //calc novamente considerando a direcao saindo do vertice atual
        sum_w[id][s] += sum_w[id_nouv][s_nouv];
        res[id][s] += res[id_nouv][s_nouv] + sum_w[id_nouv][s_nouv];
        if(biggest[id][s] == -1 || sum_w[biggest[id][s]][s_big[id][s]] < sum_w[id_nouv][s_nouv]){
            biggest[id][s] = id_nouv;
            s_big[id][s] = s_nouv;
        }
    }
}


int main()
{
    // freopen("entree.txt", "r", stdin);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i=0;i<n-1;i++){
        cin >> edge[i].x >> edge[i].y; edge[i].x--; edge[i].y--;
        adj[edge[i].x].pb(i); adj[edge[i].y].pb(i);
        sum_w[i][0] = -1; sum_w[i][1] = -1;
        res[i][0] = -1; res[i][1] = -1;
        biggest[i][0] = -1; biggest[i][1] = -1;
        from[i][0] = mp(-1,-1); from[i][1] = mp(-1, -1);
        resFin[i][0] = -1; resFin[i][1] = -1;
    }
    for(int i=0;i<n;i++)
        cin >> val[i];

    calc(0,0); calc(0, 1); //calcula todas as somas e resultados
    mini = res[0][0] + res[0][1];
    for(int i=1;i<n-1;i++){
        calc(i, 0); calc(i, 1);
        mini = min(mini, res[i][0] + res[i][1]);
    }

    for(int i=0;i<n-1;i++){
        solve(i, 0);
        solve(i, 1);
        mini = min(mini, resFin[i][0] + resFin[i][1]);
        // cout << "cut " << resFin[i][0] << " " << resFin[i][1] << endl;
    }

    cout << mini << endl;
    return 0;
}
