#include "MapSearch.h"
#include "cstring"

CMapSearch::CMapSearch(int _Map[][MAP_WIDTH])
{
    //��ʼ��
    memcpy(Map, _Map, sizeof(Map));
    dir[0].Set(0, -1);
    dir[1].Set(0, 1);
    dir[2].Set(-1, 0);
    dir[3].Set(1, 0);
}

CMapSearch::~CMapSearch(void)
{
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++) i->second.clear();
    grap.clear();
}

void CMapSearch::LoadMap(int _Map[][MAP_WIDTH])
{
    //�����ͼ
    memcpy(Map, _Map, sizeof(_Map));
}

bool CMapSearch::Search()
{
    bool bFlag = false;

    //����STLMap
    CreateSTLMap();
    memset(dis, 0, sizeof(dis));

    //����Map
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++)
    {
        Lst tmpLst = i->second;

        //������ַ�������֮��ľ���
        while(!tmpLst.empty())
        {
            CoorType c = tmpLst.front();
            tmpLst.pop_front();
            if(tmpLst.empty()) break;

            for(Lst::iterator j = tmpLst.begin(); j != tmpLst.end(); j++)
            {
                //��c��j֮���·��
                dis[c.y][c.x][j->y][j->x] = dis[j->y][j->x][c.y][c.x] = DoSearch(c.y, c.x, j->y, j->x);
                if(dis[c.y][c.x][j->y][j->x].bExist)
                {
                    Hint = dis[c.y][c.x][j->y][j->x];
                    bFlag = true;
                }
            }
        }
    }

    return bFlag;
}

PointPath CMapSearch::GetPath(int y1, int x1, int y2, int x2)
{
    return dis[y1][x1][y2][x2];
}

PointPath CMapSearch::DoSearch(int y1, int x1, int y2, int x2)
{
    PointPath ans;
    CoorType a(y1, x1), b(y2, x2), c, d;

    //�����ֱ��
    if(a.x == b.x || a.y == b.y)
    {
        if(Abled(a, b, true, true))
        {
            ans.bExist = true;
            ans.Num = 2;
            ans.Points[0] = a, ans.Points[1] = b;
            return ans;
        }
    }

    //�����һ��ת�۵�
    for(int i = 0; i < 2; i++)
    {
        if(i == 0) c.Set(a.y, b.x);
        else c.Set(b.y, a.x);

        //���ת�۵�Ϸ�
        if(Map[c.y][c.x] == -1)
            if(Abled(a, c, true) && Abled(c, b, false, true))
            {
                ans.bExist = true;
                ans.Num = 3;
                ans.Points[0] = a, ans.Points[1] = c, ans.Points[2] = b;
                return ans;
            }
    }

    //���������ת�۵�
    for(int i = 0; i < 4; i++)
    {
        //����ת�۵�1
        c.Set(y1, x1);
        c += dir[i];

        //�����ת�۵�Ϸ�
        while(c.isIll() && Map[c.y][c.x] == -1)
        {
            if(Abled(a, c, true))
            {
                //����ת�۵�2
                switch(i) {
                    case 0: 
                    case 1: d.Set(b.y, c.x); break;
                    case 2: 
                    case 3: d.Set(c.y, b.x); break;
                    default: break;
                }

                //���ת�۵�2�Ϸ�
                if(Map[d.y][d.x] == -1)
                {
                    if(Abled(c, d) && Abled(d, b, false, true))
                    {
                        ans.bExist = true;
                        ans.Num = 4;
                        ans.Points[0] = a;
                        ans.Points[1] = c;
                        ans.Points[2] = d;
                        ans.Points[3] = b;
                        return ans;
                    }
                }
            }
            else break;

            c += dir[i];
        }
    }

    ans.bExist = false;
    return ans;
}

bool CMapSearch::Abled(CoorType a, CoorType b, bool head, bool tail)
{
    CoorType ca = a, cb = b;
    if(ca.x == cb.x)
    {
        if(tail)
        {
            if(ca.y < cb.y) b.y--;
            else b.y++;
        }
        if(head)
        {
            if(ca.y < cb.y) a.y++;
            else a.y--;
        }
        int sm = ((ca.y < cb.y) ? a.y : b.y), bg = ((ca.y > cb.y) ? a.y : b.y);
        for(int i = sm; i <= bg; i++)
        {
            if(Map[i][a.x] != -1) return false;
        }
    }
    else
    if(ca.y == cb.y)
    {
        if(tail)
        {
            if(ca.x < cb.x) b.x--;
            else b.x++;
        }
        if(head)
        {
            if(ca.x < cb.x) a.x++;
            else a.x--;
        }
        int sm = ((ca.x < cb.x) ? a.x : b.x), bg = ((ca.x > cb.x) ? a.x : b.x);
        for(int i = sm; i <= bg; i++)
        {
            if(Map[a.y][i] != -1) return false;
        }
    }

    return true;
}

void CMapSearch::CreateSTLMap()
{
    //һ����������
    for(STLMap::iterator i = grap.begin(); i != grap.end(); i++) i->second.clear();
    grap.clear();

    //����Ԫ�����뵽map��list����
    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            if(Map[i][j] != -1)
            {
                CoorType tmp(i, j);
                grap[Map[i][j]].push_front(tmp);
            }
        }
    }
}

void CMapSearch::GetRandomHint(int &a, int &b)
{
    a = ID_ELEM_GUI_START + (Hint.Points[0].y * MAP_WIDTH + Hint.Points[0].x);
    b = ID_ELEM_GUI_START + (Hint.Points[Hint.Num - 1].y * MAP_WIDTH + Hint.Points[Hint.Num - 1].x);
}
