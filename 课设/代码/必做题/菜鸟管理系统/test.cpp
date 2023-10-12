#include<iostream>
using namespace std;
#include<fstream>
#define MAX_V 1024
#define INFINITY INT_MAX//◊Ó¥Û÷µŒﬁ«Ó
#include<vector>
typedef struct ArcNode//±ﬂµƒ’æµ„Ω·ππ¿‡–Õ
{
    int adjvex;//’æµ„±‡∫≈
    int line;//’æµ„À˘‘⁄¬∑œﬂ
    struct ArcNode* nextarc;
}ArcNode;
typedef struct VexNode//’æµ„Ω·ππ
{
    int order;//’æµ„±‡∫≈
    char name[100];//’æµ„√˚≥∆
    ArcNode* firstarc;
}VexNode;
typedef struct //¡⁄Ω”±Ì
{
    VexNode* VNode;
    int vexnum;
    int size;
}Graph;

//DijkstraÀ„∑®À˘–Ë∏®÷˙ ˝◊È
int* dist;//¥”≥ı ºµ„µΩµ±«∞µ„µƒ◊Ó∂Ãæ‡¿Î
int* flag;//Ω·µ„µƒ—°÷–◊¥Ã¨
int* adjvex;//¥”≥ı ºµ„µΩµ±«∞µ„æ≠π˝µƒ’æµ„±‡∫≈
int* path;//¥”≥ı ºµ„µΩµ±«∞µ„æ≠π˝µƒœﬂ¬∑±‡∫≈

void CreatGraph(Graph& G, Graph& F)
//¥¥Ω®¡Ω’≈¡⁄Ω”±Ì
//1.Õ¨“ª¬∑œﬂ…œµƒ¡Ω’æµ„÷Æº‰¥Ê‘⁄±ﬂ
//2.œ‡¡⁄¡Ω’æ÷Æº‰¥Ê‘⁄±ﬂ
{
    fstream file;
    char r[1000];//∂¡»°Œƒº˛
    char station[100];//’æµ„
    int j = 0;//º∆ ˝
    G.VNode = new VexNode[MAX_V];
    F.VNode = new VexNode[MAX_V];
    G.size = MAX_V;
    F.size = MAX_V;
    G.vexnum = 0;
    F.vexnum = 0;
    file.open("南京公交线路.txt", ios::in);
    if (!file)
    {
        cout << "Œƒº˛¥Úø™ ß∞‹";
        exit(0);
    }
    while (!file.eof())
    {
        int a = 0;//º«¬º «∑Ò“—∂¡»°µΩ’æµ„Œª÷√£®ø’∏Ò∫Û£©
        int q = 0;//º«¬ºµ±«∞œﬂ¬∑±‡∫≈
        file.getline(r, 1001);
        vector<int>Node;//±£¥Ê’‚Ãıœﬂ¬∑…œµƒÀ˘”–Ω·µ„±‡∫≈
        for (int i = 0; i <= strlen(r); i++)
        {
            if (a == 0 && (r[i] >= 48 && r[i] <= 57))//œﬂ¬∑∫≈
            {
                q = q * 10 + r[i] - 48;
            }
            else if (r[i] == ' ')//ø’∏Ò≥ˆœ÷£¨ø™ º∂¡»°’æµ„
            {
                a = 1;//pŒ™1 ±∂¡»°’æµ„
            }
            else if (a == 1)//¥¶¿Ì’æµ„ ˝æ›
            {
                if (r[i] != ',' && r[i] != '\0')
                {
                    station[j] = r[i];
                    j++;
                }
                else//“ª∏ˆ’æµ„ ‰»ÎÕÍ±œ
                {
                    station[j] = '\0';
                    j = 0;
                    int t = 0;//’æµ„“—Ω®¡¢Õ∑Ω·µ„±Í◊¢1
                    int n;//µ±«∞’æµ„±‡∫≈
                    for (int k = 0; k < F.vexnum; k++)//≤Èø¥ «∑ÒΩ®¡¢Õ∑Ω·µ„
                    {
                        if (strcmp(F.VNode[k].name, station) == 0)
                        {
                            t = 1;
                            n = k;//µ±«∞±‡∫≈
                            break;//’“µΩÃ¯≥ˆ—≠ª∑
                        }
                    }
                    if (t == 0)//Œ¥Ω®¡¢Õ∑Ω·µ„
                    {
                        if (G.size <= G.vexnum)
                        {
                            G.VNode = (VexNode*)realloc(G.VNode, (G.size + MAX_V));
                            G.size = G.size + MAX_V;
                        }
                        if (F.size <= F.vexnum)
                        {
                            F.VNode = (VexNode*)realloc(F.VNode, (F.size + MAX_V));
                            F.size = F.size + MAX_V;
                        }
                        //»Ùø’º‰≤ªπª‘ˆ¿©ø’º‰
                        strcpy_s(G.VNode[G.vexnum].name, station);
                        strcpy_s(F.VNode[F.vexnum].name, station);
                        G.VNode[G.vexnum].order = G.vexnum;
                        F.VNode[F.vexnum].order = F.vexnum;
                        G.VNode[G.vexnum].firstarc = NULL;
                        F.VNode[F.vexnum].firstarc = NULL;
                        n = F.vexnum;
                        G.vexnum++;
                        F.vexnum++;
                    }
                    if (!Node.empty())//µ±«∞’æµ„≤¢∑«œﬂ¬∑µƒµ⁄“ª∏ˆ’æµ„
                    {
                        //1±Ì£∫”Îµ±«∞¬∑œﬂµƒ∆‰À˚À˘”–’æµ„¥Ê‘⁄±ﬂ
                        ArcNode* p, * pre;
                        for (int k = 0; k < Node.size(); k++)
                        {
                            p = new ArcNode;
                            p->nextarc = NULL;
                            p->adjvex = n;
                            p->line = q;
                            pre = G.VNode[Node[k]].firstarc;
                            if (pre == NULL)
                            {
                                G.VNode[Node[k]].firstarc = p;
                            }
                            else
                            {
                                while (pre->nextarc != NULL)
                                {
                                    pre = pre->nextarc;
                                }
                                pre->nextarc = p;
                            }
                            //∂‘≥∆Ω®¡¢
                            p = new ArcNode;
                            p->adjvex = Node[k];
                            p->line = q;
                            p->nextarc = NULL;
                            pre = G.VNode[n].firstarc;
                            if (pre == NULL)
                            {
                                G.VNode[n].firstarc = p;
                            }
                            else
                            {
                                while (pre->nextarc != NULL)
                                {
                                    pre = pre->nextarc;
                                }
                                pre->nextarc = p;
                            }
                        }
                        //2±Ì ”Î«∞“ª’æµ„¥Ê‘⁄±ﬂ
                        int front = Node[Node.size() - 1];//«∞“ª’æµ„µ„µƒ±‡∫≈
                        p = new ArcNode;
                        p->adjvex = n;
                        p->line = q;
                        p->nextarc = NULL;
                        pre = F.VNode[front].firstarc;
                        if (pre == NULL)
                        {
                            F.VNode[front].firstarc = p;
                        }
                        else
                        {
                            while (pre->nextarc != NULL)
                            {
                                pre = pre->nextarc;
                            }
                            pre->nextarc = p;
                        }
                        //∂‘≥∆
                        p = new ArcNode;
                        p->adjvex = front;
                        p->line = q;
                        p->nextarc = NULL;
                        pre = F.VNode[n].firstarc;
                        if (pre == NULL)
                        {
                            F.VNode[n].firstarc = p;
                        }
                        else
                        {
                            while (pre->nextarc != NULL)
                            {
                                pre = pre->nextarc;
                            }
                            pre->nextarc = p;
                        }
                    }
                    Node.push_back(n);
                }
            }
        }
    }
    file.close();
}
//¥¥Ω®¡Ω’≈¡⁄Ω”±Ì
void Dijkstra(Graph G, int s)
{
    dist[s] = 0;
    flag[s] = 1;//—°÷–≥ı ºµ„
    ArcNode* p;
    int num = 1;//º«¬ºƒø«∞±ª—°÷–µƒ’æµ„ ˝
    while (num < G.vexnum)
    {
        p = G.VNode[s].firstarc;//—°÷–µ„µƒ ◊∏ˆ¡⁄Ω”µ„
        while (p != NULL)//–¬µƒΩ·µ„º”»Î
        {
            if (flag[p->adjvex] == 0 && dist[p->adjvex] > dist[s] + 1)
            {
                dist[p->adjvex] = dist[s] + 1;
                adjvex[p->adjvex] = s;
                path[p->adjvex] = p->line;
            }
            p = p->nextarc;
        }//≥ı ºªØ
        int mindist = INFINITY;
        for (int i = 1; i <= G.vexnum; i++)
        {
            if (flag[i] != 1 && dist[i] < mindist)
            {
                mindist = dist[i];
                s = i;
            }
        }
        flag[s] = 1;
        num++;
    }
}
//µœΩ‹ÀπÃÿ¿≠À„∑®«Ûµ•‘¥◊Ó∂Ã¬∑æ∂£®»®÷µ1£©
void outpath(Graph G, int start, int end, string station)
{
    cout << "æﬂÃÂ¬∑œﬂŒ™£∫" << endl;
    vector<int>Path;
    int a = end;
    while (a != start)
    {
        Path.push_back(a);
        a = adjvex[a];
    }
    int b = path[Path[Path.size() - 1]];
    cout << b << "¬∑£∫" << station;
    for (int i = Path.size() - 1; i >= 0; i--)
    {
        if (path[Path[i]] != b)
        {
            b = path[Path[i]];
            cout << endl << "ªª≥ÀµΩ" << b << "¬∑£∫" << G.VNode[Path[i + 1]].name;
        }
        cout << "--" << G.VNode[Path[i]].name;
    }
    cout << endl;
    cout << endl;
}
// ‰≥ˆ¬∑œﬂ
void menu()
{
    cout << "ª∂”≠¿¥µΩπ´Ωªœﬂ¬∑Ã· æœµÕ≥£°" << endl;
    cout << "   ±æœµÕ≥Ã·π©“‘œ¬π¶ƒ‹" << endl;
    cout << "1.œ‘ æ◊™≥µ¥Œ ˝◊Ó…Ÿµƒ≥À≥µ¬∑œﬂ" << endl;
    cout << "2.œ‘ ææ≠π˝’æµ„◊Ó…Ÿµƒ≥À≥µ¬∑œﬂ" << endl;
    cout << "3.ÕÀ≥ˆœµÕ≥" << endl;
    cout << "«Î—°‘Òπ¶ƒ‹£∫";
}
//Ã· æ≤Ÿ◊˜
void findpath(Graph G)
{
    string start;
    string end;
    cout << "«Î ‰»Î…œ≥µµƒ’æµ„√˚≥∆:";
    cin >> start;
    cout << "«Î ‰»Îœ¬≥µµƒ’æµ„√˚≥∆:";
    cin >> end;
    int a = -1, b = -1;
    for (int i = 0; i < G.vexnum; i++)//—∞’“∆ º’æµ„±‡∫≈
    {
        if (G.VNode[i].name == start)
        {
            a = i;
        }
        if (G.VNode[i].name == end)
        {
            b = i;
        }
    }if (a == -1)
    {
        cout << "Œ¥’“µΩ∆ º’æµ„" << endl;
        return;
    }
    if (b == -1)
    {
        cout << "Œ¥’“µΩΩ· ¯’æµ„" << endl;
        return;
    }
    for (int i = 1; i <= G.vexnum; i++)//∏®÷˙ ˝◊È≥ı ºªØ
    {
        adjvex[i] = a;
        path[i] = 0;
        dist[i] = INFINITY;
        flag[i] = 0;
    }
    Dijkstra(G, a);
    cout << "¥”" << start << "µΩ" << end << "µƒªª≥À¥Œ ˝◊Ó…ŸŒ™" << dist[b] - 1 << "¥Œ" << endl;
    outpath(G, a, b, start);
}
void findadj(Graph G)
{
    string start;
    string end;
    cout << "«Î ‰»Î…œ≥µµƒ’æµ„√˚≥∆:";
    cin >> start;
    cout << "«Î ‰»Îœ¬≥µµƒ’æµ„√˚≥∆:";
    cin >> end;
    int a = -1, b = -1;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.VNode[i].name == start)
        {
            a = i;
        }
        if (G.VNode[i].name == end)
        {
            b = i;
        }
    }
    if (a == -1)
    {
        cout << "Œ¥’“µΩ∆ º’æµ„" << endl;
        return;
    }
    if (b == -1)
    {
        cout << "Œ¥’“µΩΩ· ¯’æµ„" << endl;
        return;
    }
    for (int i = 1; i <= G.vexnum; i++)
    {
        dist[i] = INFINITY;
        adjvex[i] = a;
        path[i] = 0;
        flag[i] = 0;
    }
    Dijkstra(G, a);
    cout << "¥”" << start << "µΩ" << end << "µƒæ≠π˝’æµ„∏ˆ ˝◊Ó…ŸŒ™" << dist[b] + 1 << "∏ˆ" << endl;
    outpath(G, a, b, start);
}

void function(Graph G, Graph F)
{
    while (1)
    {
        menu();
        int choice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            findpath(G);
            break;
        }
        case 2:
        {
            findadj(F);
            break;
        }
        case 3:
        {
            exit(0);
        }
        default:
        {
            cout << " ‰»Î¥ÌŒÛ£°" << endl;
            break;
        }
        }
    }
}
//π¶ƒ‹—°‘Ò


int main()
{
    Graph G, F;
    CreatGraph(G, F);
    adjvex = new int[G.vexnum + 1];
    path = new int[G.vexnum + 1];
    dist = new int[G.vexnum + 1];
    flag = new int[G.vexnum + 1];
    function(G, F);
    return 0;
}