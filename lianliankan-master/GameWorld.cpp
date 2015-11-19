#include "Global.h"
#include "GameWorld.h"
#include "cstring"
#include "cstdio"

CGameWorld::CGameWorld(void)
    : Engine(NULL)
    , m_bGameStarted(false)
    , m_nLastGUIID(0)
    , m_pMapSearch(NULL)
    , m_nSeedID(-1)
    , m_bLose(false)
    , m_bWin(false)
    , m_bTimeNotified(false)
{
    for(int i = 0; i < 6; i++) m_ThunderAni[i] = NULL;
}

void CGameWorld::Init()
{
    //��ʼ��HGE����
    Engine = hgeCreate(HGE_VERSION);

    Engine->System_SetState(HGE_LOGFILE, "LinkMe.log");
    Engine->System_SetState(HGE_FRAMEFUNC, LogicFunc);
    Engine->System_SetState(HGE_RENDERFUNC, RenderFunc);
    Engine->System_SetState(HGE_TITLE, "������ - ������");
    Engine->System_SetState(HGE_WINDOWED, true);
    Engine->System_SetState(HGE_SCREENWIDTH, 794);
    Engine->System_SetState(HGE_SCREENHEIGHT, 572);
    Engine->System_SetState(HGE_SCREENBPP, 32);
    Engine->System_SetState(HGE_FPS, 100);
    Engine->System_SetState(HGE_ICON, "Client.ico");
    Engine->System_SetState(HGE_SHOWSPLASH, false);

    if(Engine->System_Initiate())
    {
        if(LoadResource()) Engine->System_Start();
        else MessageBox(NULL, L"��Դ�������������Ϸ�����ԣ�", L"����", MB_ICONSTOP);
    }
}

//������Դ�ļ�
bool CGameWorld::LoadResource()
{
    //������Դ��
    Engine->Resource_AttachPack(IMAGE_ZIP, IMAGE_ZIP_PASSWORD);
    Engine->Resource_AttachPack(MUSIC_ZIP, MUSIC_ZIP_PASSWORD);
    Engine->Resource_AttachPack(MAP_ZIP, MAP_ZIP_PASSWORD);

    //����������Դ
    fnt = new hgeFont("Font.fnt");
    if(fnt == NULL) return false;

    //���뱳������
    BGM = Engine->Effect_Load("BGM.ogg");
    if(!BGM) return false;

    //���밴ť����
    StartSE = Engine->Effect_Load("Start.wav");
    if(!StartSE) return false;
    ElemSelSE = Engine->Effect_Load("Sel.wav");
    if(!ElemSelSE) return false;
    ElecSE = Engine->Effect_Load("Elec.wav");
    if(!ElecSE) return false;
    ItemBoomSE = Engine->Effect_Load("ItemBoom.wav");
    if(!ItemBoomSE) return false;
    EndSE = Engine->Effect_Load("End.wav");
    if(!EndSE) return false;
    LessTimeSE = Engine->Effect_Load("TimeNotify.wav");
    if(!LessTimeSE) return false;
    HintSE = Engine->Effect_Load("Hint.wav");
    if(!HintSE) return false;
    ResortSE = Engine->Effect_Load("Resort.wav");
    if(!ResortSE) return false;

    //���밴ťͼƬ
    StartBtnTexture = Engine->Texture_Load("Start.jpg");
    m_HintTexture = Engine->Texture_Load("Hint.png");
    m_ResortTexture = Engine->Texture_Load("Resort.png");

    //�½�GUI
    gui = new hgeGUI();
    gui->AddCtrl(new CTinyButton(ID_START_BTN, Engine, StartBtnTexture, 618, 527, 80, 36, StartSE));
    gui->AddCtrl(new CTinyButton(ID_HINT_BTN, Engine, m_HintTexture, 615, 163, 25, 25, HintSE));
    gui->AddCtrl(new CTinyButton(ID_RESORT_BTN, Engine, m_ResortTexture, 640, 163, 25, 25, ResortSE));

    //�������
    m_CursorTexture = Engine->Texture_Load("Cursor.png");
    if(!m_CursorTexture) return false;
    else
    {
        m_pCursor = new hgeSprite(m_CursorTexture, 0, 0, 32, 32);
        gui->SetCursor(m_pCursor);
    }

    //���뱳��
    if(!QLoad(Background, "Background.jpg")) return false;
    else
    {
        //���ñ�����ϸ
        QuadTexture(Background, 0, 0, 794, 572);
        QuadScreen(Background, 0, 0, 794, 572);
    }

    //���뱬ը��Դ
    m_BoomTexture = Engine->Texture_Load("Boom.png");
    if(!m_BoomTexture) return false;
    else
    {
        //���챬ը����
        m_BoomAni = new hgeAnimation(m_BoomTexture, 10, 15, 0, 0, 31, 35);
        m_BoomAni->SetMode(HGEANIM_NOLOOP | HGEANIM_FWD);
    }

    //����ʱ����
    m_TimeBarTexture = Engine->Texture_Load("TimeBar.png");
    if(!m_TimeBarTexture) return false;
    else
    {
        m_pTimeBar = new hgeSprite(m_TimeBarTexture, 0, 0, 3, 14);
    }

    //����������Դ
    for(int i = 0; i < 6; i++)
    {
        char FN[256];
        sprintf(FN, "Elec%d.png", i + 1);
        m_ElecTexture[i] = Engine->Texture_Load(FN);
        if(!m_ElecTexture[i]) return false;
        else
        {
            //�������綯��
            m_ThunderAni[i] = new hgeAnimation(m_ElecTexture[i], 2, 15, 0, 0, 35, 39);
            m_ThunderAni[i]->SetMode(HGEANIM_LOOP | HGEANIM_FWD);
        }
    }

    //���뷽����Ϣ
    m_ElemSelTexture = Engine->Texture_Load("Sel.png");     //����ѡ��ʱЧ��
    if(!m_ElemSelTexture) return false;
    else
    {
        m_pElemSel = new hgeSprite(m_ElemSelTexture, 0, 0, 31, 35);
    }

    char szElemFileName[256];
    for(int i = 0; i < MAX_ELEM_TEXTURE; i++)
    {
        //�����ļ���
        sprintf(szElemFileName, "%s%d%s", 
            szElemFileNamePrefix, i + 1, szElemFileNameSuffix);

        m_ElemTexture[i] = Engine->Texture_Load(szElemFileName);

        //������벻�ɹ��򷵻�false
        if(!m_ElemTexture[i]) return false;

        //��������䵽�����龫��֮��
        for(int j = 0; j < 4; j++)
        {
            m_pElement[i * 4 + j] = new hgeSprite(m_ElemTexture[i],
                GetElemTex[j].x, GetElemTex[j].y, 35, 39);
        }
    }

    //�����ͼ����
    char szMapSeedFileName[256];
    char *pBuffer;
    DWORD nLength = 0;
    for(int i = 0; i < MAP_SEED_NUM; i++)
    {
        sprintf(szMapSeedFileName, "%s%d%s", 
            szMapSeedFileNamePrefix, i + 1, szMapSeedFileNameSuffix);

        //����ͼ���Ӷ����ڴ�
        pBuffer = (char *)Engine->Resource_Load(szMapSeedFileName, &nLength);
        if(!pBuffer) return false;

        //���ڴ��еĵ�ͼ����ת��ΪMapSeedType
        int pos = 0;
        m_MapSeed[i].Num = 0;
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            for(int k = 0; k < MAP_WIDTH; k++)
            {
                while(pBuffer[pos] == '\r' || pBuffer[pos] == '\n') pos++;
                m_MapSeed[i].Seed[j][k] = pBuffer[pos] - '0';
                if(m_MapSeed[i].Seed[j][k]) m_MapSeed[i].Num++;

                pos++;
            }
        }

        Engine->Resource_Free((void *)pBuffer);

        //����ͼ�������󣬼����鲻��˫
        if(m_MapSeed[i].Num % 2)
        {
            MessageBox(NULL, L"����ĵ�ͼ���ݣ�", L"����", MB_ICONSTOP);
            return false;
        }
    }

    return true;
}

void CGameWorld::QuadTexture(hgeQuad &quad, float x1, float y1, float x2, float y2)
{
    float h = Engine->Texture_GetHeight(quad.tex);
    float w = Engine->Texture_GetWidth(quad.tex);

    quad.v[0].tx = x1 / w, quad.v[0].ty = y1 / h;
    quad.v[1].tx = x2 / w, quad.v[1].ty = y1 / h;
    quad.v[2].tx = x2 / w, quad.v[2].ty = y2 / h;
    quad.v[3].tx = x1 / w, quad.v[3].ty = y2 / h;
}

void CGameWorld::QuadScreen(hgeQuad &quad, float x1, float y1, float x2, float y2)
{
    quad.blend = BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
    quad.v[0].x = x1, quad.v[0].y = y1;
    quad.v[1].x = x2, quad.v[1].y = y1;
    quad.v[2].x = x2, quad.v[2].y = y2;
    quad.v[3].x = x1, quad.v[3].y = y2;
    for(int i = 0; i < 4; i++)
    {
        quad.v[i].z = 0.5f;
        quad.v[i].col = 0xFFFFFFFF;
    }
}

bool CGameWorld::QLoad(hgeQuad &quad, char *filename)
{
    quad.tex = Engine->Texture_Load(filename);

    if(quad.tex) return true;
    else return false;
}

CGameWorld::~CGameWorld(void)
{
    DelResource();
    Engine->System_Shutdown();
    Engine->Release();
}

void CGameWorld::DelResource()
{
    delete gui;
    delete m_pCursor;
    Engine->Texture_Free(Background.tex);

    //ɾ��������Ϣ
    for(int i = 0; i < MAX_ELEM_TEXTURE; i++)
    {
        Engine->Texture_Free(m_ElemTexture[i]);

        for(int j = 0; j < 4; j++) delete m_pElement[i * 4 + j];
    }

    Engine->Effect_Free(BGM);
    Engine->Effect_Free(StartSE);
}

bool CGameWorld::GameLogicFunc()
{
    //����GUI
    float dt = Engine->Timer_GetDelta();
    m_nLastGUIID = gui->Update(dt);

    //������µ��ǿ�ʼ����ʼ��Ϸ
    if(m_nLastGUIID == ID_START_BTN)
    {
        GameStart();
    }
    else
    if(m_bGameStarted && m_nLastGUIID == ID_HINT_BTN)                      //���������ʾ
    {
        int ida, idb;
        m_pMapSearch->GetRandomHint(ida, idb);

        m_nSelArr[0] = ida, m_nSelArr[1] = idb;
        m_pElemButtonArr[ida]->m_bSelected = m_pElemButtonArr[idb]->m_bSelected = true;
    }
    else
    if(m_bGameStarted && m_nLastGUIID == ID_RESORT_BTN)                     //�����������
    {
        Resort();
    }
    else
    if(m_bGameStarted && m_nLastGUIID >= ID_ELEM_GUI_START)              //������µ��Ƿ�������Ϸ��ʼ����ʼ�߼��ж�
    {
        if(m_nSelArr[0] != -1 && m_nSelArr[1] != -1)
        {
            MapCoorType a, b;
            a.ToCoor(m_nSelArr[0]);
            b.ToCoor(m_nSelArr[1]);

            if(m_Map.Map[a.y][a.x] == m_Map.Map[b.y][b.x])
            {
                PointPath pp(m_pMapSearch->GetPath(a.y, a.x, b.y, b.x));
                if(pp.bExist)
                {
                    m_thisTime = 0;
                    Engine->Effect_Play(ElecSE);
                    //Engine->Effect_Play(ItemBoomSE);
                    m_bTimeNotified = false;
                    PutAni(pp);

                    m_Map.Map[a.y][a.x] = m_Map.Map[b.y][b.x] = -1;
                    m_pElemButtonArr[m_nSelArr[0]]->ToLeave();
                    m_pElemButtonArr[m_nSelArr[1]]->ToLeave();
                    m_Map.nLeft -= 2;
                    m_nSelArr[0] = m_nSelArr[1] = -1;

                    ToSearchMap();
                }
                else
                {
                    m_nSelArr[0] = m_nSelArr[1];
                    m_nSelArr[1] = -1;
                }
            }
            else
            {
                m_nSelArr[0] = m_nSelArr[1];
                m_nSelArr[1] = -1;
            }
        }
    }
    else
    if(m_bGameStarted) //��ʱ
    {
        m_thisTime += dt;
        //��ʱ�䵽
        if(m_thisTime > MAX_TIME)
        {
            m_bGameStarted = false;
            m_bLose = true;
            Engine->Effect_Play(EndSE);
        }

        if(MAX_TIME - m_thisTime < 8 && !m_bTimeNotified)
        {
            m_bTimeNotified = true;
            Engine->Effect_Play(LessTimeSE);
        }

        //�ж�Ӯ
        if(m_Map.nLeft == 0)
        {
            m_bGameStarted = false;
            m_bWin = true;
            Engine->Effect_Play(EndSE);
        }
    }
    else
    if(!m_bGameStarted)             //�����Ϸû�п�ʼ
    {
        if(Engine->Channel_IsPlaying(BGMChannel))
            Engine->Channel_Stop(BGMChannel);
    }

    return false;
}

//�����綯����������
void CGameWorld::PutAni(PointPath path)
{
    hgeAnimation *pAni;
    //ѭ��·������
    for(int i = 1; i < path.Num; i++)
    {
        //ѭ����·����ÿ���㣬����㵽�յ�֮ǰ�ĵ�
        for(int j = path.Points[i - 1].x, k = path.Points[i - 1].y;
            !(j == path.Points[i].x && k == path.Points[i].y); )
        {
            //�����������㣨��Ϊ����㲻�û���
            if(!(i == 1 && j == path.Points[i - 1].x && k == path.Points[i - 1].y))
            {
                //���������·����㣨��Ϊ��������㣬���Կ϶���ת�ۣ�
                if(j == path.Points[i - 1].x && k == path.Points[i - 1].y)
                {
                    if(path.Points[i - 2].x == path.Points[i - 1].x)
                    {
                        if(path.Points[i - 2].y > path.Points[i - 1].y)
                        {
                            if(path.Points[i].x > path.Points[i - 1].x) pAni = m_ThunderAni[2];
                            else pAni = m_ThunderAni[3];
                        }
                        else
                        if(path.Points[i - 2].y < path.Points[i - 1].y)
                        {
                            if(path.Points[i].x > path.Points[i - 1].x) pAni = m_ThunderAni[4];
                            else pAni = m_ThunderAni[5];
                        }
                    }
                    else
                    if(path.Points[i - 2].y == path.Points[i - 1].y)
                    {
                        if(path.Points[i - 2].x > path.Points[i - 1].x)
                        {
                            if(path.Points[i].y > path.Points[i - 1].y) pAni = m_ThunderAni[2];
                            else pAni = m_ThunderAni[4];
                        }
                        else
                        if(path.Points[i - 2].x < path.Points[i - 1].x)
                        {
                            if(path.Points[i].y > path.Points[i - 1].y) pAni = m_ThunderAni[3];
                            else pAni = m_ThunderAni[5];
                        }
                    }
                }
                else
                if(path.Points[i - 1].x == path.Points[i].x) pAni = m_ThunderAni[0];
                else
                if(path.Points[i - 1].y == path.Points[i].y) pAni = m_ThunderAni[1];

                BoomAni tmp(*pAni);
                tmp.x = PADDING_LEFT + ELEM_INTERFACE_WIDTH * j + ELEM_INTERFACE_OFFSET_X;
                tmp.y = PADDING_TOP + ELEM_INTERFACE_HEIGHT * k + ELEM_INTERFACE_OFFSET_Y;

                BA.push_back(tmp);
                BA.back().ani->Play();
            }

            if(path.Points[i].x != path.Points[i - 1].x)
            {
                if(path.Points[i].x > path.Points[i - 1].x) j++;
                else j--;
            }
            if(path.Points[i].y != path.Points[i - 1].y)
            {
                if(path.Points[i].y > path.Points[i - 1].y) k++;
                else k--;
            }
        }
    }
}

void CGameWorld::GameStart()
{
    GameReset();

    m_nSelArr[0] = m_nSelArr[1] = -1;
    MakeMap();
    CreateElemGUI();
    m_bGameStarted = true;
    BGMChannel = Engine->Effect_PlayEx(BGM, 100, 0, 1.0, true);

    //����һ�ε�ͼ
    ToSearchMap();

    m_thisTime = 0;
}

void CGameWorld::ToSearchMap()
{
    if(m_pMapSearch != NULL) free(m_pMapSearch);
    m_pMapSearch = new CMapSearch(m_Map.Map);

    if(!m_pMapSearch->Search() && !m_bWin && m_Map.nLeft != 0)
    {
        Engine->Effect_Play(ResortSE);
        Resort();
    }
}

void CGameWorld::CreateElemGUI()
{
    //������GUI������
    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int j = MAP_WIDTH - 1; j >= 0; j--)
        {
            if(m_Map.Map[i][j] != -1)
            {
                int id = ID_ELEM_GUI_START + i * MAP_WIDTH + j;     //����ID
                m_pElemButtonArr[id] = new CElemButton(id, this, m_pElement[m_Map.Map[i][j]], m_pElemSel, ElemSelSE, m_BoomAni);
                gui->AddCtrl(m_pElemButtonArr[id]);
            }
        }
    }
}

void CGameWorld::MakeMap()
{
    memset(m_Map.Map, 0, sizeof(m_Map.Map));
    Engine->Random_Seed();                                  //�����������

    int nElemID[MAP_HEIGHT * MAP_WIDTH];                    //�����������
    int nSeedID = Engine->Random_Int(0, MAP_SEED_NUM - 1);  //���ʹ�õ�ͼ����
    int nTime = m_MapSeed[nSeedID].Num / 2;                 //��������

    m_nSeedID = nSeedID;

    //ѡ������Щ������Χ
    for(int i = 0; i < nTime; i++)
    {
        //��0�ŵ�MAX_ELEM_TEXTURE * 4 - 1��ѡȡ����
        nElemID[i * 2] = nElemID[i * 2 + 1] = Engine->Random_Int(0, MAX_ELEM_TEXTURE * 4 - 1);
    }

    //�����������ͼ
    m_Map.nLeft = m_MapSeed[nSeedID].Num;
    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            //�����ͼ���ӵ�i��j����true�������Χ���������ѡһ�����ȥ
            if(m_MapSeed[nSeedID].Seed[i][j])
            {
                int tmp = Engine->Random_Int(0, m_MapSeed[nSeedID].Num - 1);

                //���֮ǰ�ѱ�ѡ��ȥ������ѡ
                while(nElemID[tmp] == -1) tmp = Engine->Random_Int(0, m_MapSeed[nSeedID].Num - 1);

                //��tmp��id���ȥ���ҽ�������Ϊ��ѡ
                m_Map.Map[i][j] = nElemID[tmp];
                nElemID[tmp] = -1;
            }
            else m_Map.Map[i][j] = -1;
        }
    }
}

void CGameWorld::GameReset()
{
    m_bLose = m_bWin = false;
    if(m_pMapSearch != NULL) 
    {
        free(m_pMapSearch);
        m_pMapSearch = NULL;
    }
    if(BGMChannel) Engine->Channel_Stop(BGMChannel);
    ClearElemGUI();
    m_bTimeNotified = false;
}

void CGameWorld::ClearElemGUI()
{
    //������ɾ��
    if(m_nSeedID == -1) return;
    for(int i = MAP_HEIGHT - 1; i >= 0; i--)
    {
        for(int j = MAP_WIDTH - 1; j >= 0; j--)
        {
            if(m_MapSeed[m_nSeedID].Seed[i][j])
            {
                int id = ID_ELEM_GUI_START + i * MAP_WIDTH + j;     //����ID
                //free(m_pElemButtonArr[id]);
                //gui->AddCtrl(new CElemButton(id, Engine, m_pElement[m_Map.Map[i][j]], m_pElemSel));
                gui->DelCtrl(id);
                //m_pElemButtonArr[id]->bEnabled = false;
                //m_pElemButtonArr[id]->bVisible = false;
                //m_pElemButtonArr[id]->bStatic = false;
            }
        }
    }
}

void CGameWorld::BoomLineRender()
{
    float dt = Engine->Timer_GetDelta();
    for(list<BoomAni>::iterator i = BA.begin(); i != BA.end();)
    {
        i->timer += dt;
        if(i->timer > i->delay)
        {
            BA.erase(i++);
            continue;
        }

        int alpha = (int)((i->delay - i->timer) / i->delay * 255);
        if(alpha < 0) alpha = 0;

        i->ani->SetColor(ARGB(alpha, 0xff, 0xff, 0xff));
        i->ani->Update(dt);
        i->ani->Render(i->x, i->y);

        ++i;
    }
}

bool CGameWorld::GameRenderFunc()
{
    Engine->Gfx_BeginScene();
    Engine->Gfx_Clear(0);

    Engine->Gfx_RenderQuad(&Background);    //��Ⱦ����
    gui->Render();                          //��ȾGUI
    BoomLineRender();                       //��Ⱦ����

    if(m_bGameStarted)
    {
        fnt->SetColor(0xffffffff);              //����������ɫ
        fnt->printf(500, 550, HGETEXT_LEFT, "%d", m_Map.nLeft);

        //ʱ����
        float m_THeight = 14;
        float m_TWidth = (m_thisTime / MAX_TIME) * MAX_TIME_BAR;
        
        m_pTimeBar->RenderStretch(78, 549, 78 + m_TWidth, 549 + m_THeight);
    }

    Engine->Gfx_EndScene();
    return false;
}

void CGameWorld::Resort()
{
    ClearElemGUI();                             //ɾ��ԭ����Ʒ
    int nElemID[MAP_HEIGHT * MAP_WIDTH];        //�����������
    int pos = 0;

    for(int i = 0; i < MAP_HEIGHT; i++)         //�����ݸ�ֵ��������
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            if(m_Map.Map[i][j] != -1) nElemID[pos++] = m_Map.Map[i][j];
        }
    }

    Engine->Random_Seed();                      //�����������
    for(int i = 0; i < MAP_HEIGHT; i++)         //���������������ͼ
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            if(m_Map.Map[i][j] != -1)
            {
                //���������
                int tmp = Engine->Random_Int(0, pos - 1);
                while(nElemID[tmp] == -1)
                {
                    tmp = Engine->Random_Int(0, pos - 1);
                }

                m_Map.Map[i][j] = nElemID[tmp];
                nElemID[tmp] = -1;
            }
        }
    }

    CreateElemGUI();                            //����GUI

    //����һ�ε�ͼ
    ToSearchMap();

    m_nSelArr[0] = m_nSelArr[1] = -1;

    m_thisTime = 0;
}
