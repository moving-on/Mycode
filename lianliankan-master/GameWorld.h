//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file GameWorld.h
/// @brief ��������Ϸ�����ļ�
///
/// ������Ϸ����Ҫ�࣬����HGE���桢��Ⱦ�������߼������ȡ�
/// @version 1.0
/// @author ����
/// @date 2010��10��5��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef GAMEWORLD
#define GAMEWORLD

#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include "TinyButton.h"
#include "ElemButton.h"
#include <hgeanim.h>
#include "MapSearch.h"
#include "list"

#define IMAGE_ZIP               "Texture.X2Pak"            ///< ������Դ���ļ���
#define MUSIC_ZIP               "Music.X2Pak"              ///< ������Դ���ļ���
#define MAP_ZIP                 "Maps.X2Pak"               ///< ��ͼ������Դ���ļ���
#define IMAGE_ZIP_PASSWORD      "X2Studio"                 ///< ������Դ������
#define MUSIC_ZIP_PASSWORD      "X2Studio"                 ///< ������Դ������
#define MAP_ZIP_PASSWORD        "X2Studio"                 ///< ��ͼ������Դ������
#define MAX_ELEM_TEXTURE        10                         ///< ������Դ�ļ���

#define ID_START_BTN            1                          ///< ��ʼ��ťID
#define ID_HINT_BTN             2                          ///< ��ʾ��ťID
#define ID_RESORT_BTN           3                          ///< ���а�ťID

#define MAP_SEED_NUM            16                         ///< ��ͼ������

#define MAP_HEIGHT              10                         ///< ��ͼ�߶�
#define MAP_WIDTH               18                         ///< ��ͼ���
#define MAX_TIME_BAR            330                        ///< ���ʱ����

#define MAX_TIME                45.0f                      ///< �Ѱ��ʱ��
#define ID_ELEM_GUI_START       50                         ///< ����GUI����ʼID

/**
 * @brief �ͻ�����Ļ��������
 *
 * �ͻ�����Ļ���꣬x��yΪ������
 */
struct Coor {
    float x;                                                ///< �ͻ������x������ֵ
    float y;                                                ///< �ͻ������y������ֵ
};

/**
 * @brief ��ͼ��������
 *
 * NumΪ��ͼ���ӱ�ţ���ͼ����ΪH * W�Ĳ������󣬱�ʾ���޷���
 */
struct MapSeedType {
    int Num;                                               ///< ���ӱ��
    bool Seed[MAP_HEIGHT][MAP_WIDTH];                      ///< ��ͼ���Ӿ���
};

#ifndef MAPTYPE
#define MAPTYPE
/**
 * @brief ��ͼ����
 *
 * ������Ϸ�еĵ�ͼ���ͣ�nLeftΪ�˵�ͼʣ�µķ�������Map��һ��int���飬
 * ��ʾ���и��е�Ԫ��id����Ϊ����Ϊ-1
 */
struct MapType {
    int nLeft;                                              ///< ��ͼʣ�µķ���
    int Map[MAP_HEIGHT][MAP_WIDTH];                         ///< ��ͼ��ά����
};
#endif

/**
 * @brief ��ͼ����
 *
 * ������Ϸ�еĵ�ͼ���ͣ�nLeftΪ�˵�ͼʣ�µķ�������Map��һ��int���飬
 * ��ʾ���и��е�Ԫ��id����Ϊ����Ϊ-1
 */
struct MapCoorType {
    int x;                                                  ///< x������
    int y;                                                  ///< y������
    /**
     * ת������
     * ������GUI��IDת��Ϊ��ͼ���겢��ֵ���ṹ��
     * @param id ����GUI��ID
     * @note ��ID_ELEM_GUI_STARTΪ��ʼID
     */     
    void ToCoor(int id)
    {
        id -= ID_ELEM_GUI_START;
        y = id / MAP_WIDTH;
        x = id % MAP_WIDTH;
    }
};

/**
 * @brief ������������
 *
 * ��������Ľṹ�壬��������Ĵ��ʱ�䡢���������е�ʱ��;����λ��x��y
 */
struct BoomAni {
    float timer;                                            ///< �������������
    float delay;                                            ///< ��ʱ��
    hgeAnimation *ani;                                      ///< ��������
    float x;                                                ///< ����λ��x����
    float y;                                                ///< ����λ��y����
    /**
     * �������͹��캯��
     * @param a HGE����Ķ���������
     */
    BoomAni(hgeAnimation a)
    {
        ani = new hgeAnimation(a);
        timer = 0;
        delay = 1.0f;
    }
};

const char szElemFileNamePrefix[]       = "Elem";           ///< ������Դ�ļ���ǰ׺
const char szElemFileNameSuffix[]       = ".png";           ///< ������Դ�ļ�����׺
const char szMapSeedFileNamePrefix[]    = "Map";            ///< ������Դ�ļ���ǰ׺
const char szMapSeedFileNameSuffix[]    = ".txt";           ///< ������Դ�ļ�����׺

bool LogicFunc();
bool RenderFunc();

class CMapSearch;
struct PointPath;

/**
 * @brief ��Ϸ��
 *
 * ��������Ϸ�ĺ����࣬������Ҫ���߼�����Ⱦ�Ⱥ�����������
 */
class CGameWorld
{
private:
    hgeQuad Background;                                                                              ///< �����ı���ͼԪ

    HTEXTURE m_CursorTexture;                                                                        ///< �������
    HTEXTURE StartBtnTexture;                                                                        ///< ��ʼ��ť����
    HTEXTURE m_ElemTexture[MAX_ELEM_TEXTURE];                                                        ///< ������������
    HTEXTURE m_ElemSelTexture;                                                                       ///< ����ѡ��Ч������
    HTEXTURE m_BoomTexture;                                                                          ///< ��ը��������
    HTEXTURE m_ElecTexture[6];                                                                       ///< ���綯����������
    HTEXTURE m_TimeBarTexture;                                                                       ///< ʱ��������
    HTEXTURE m_HintTexture;                                                                          ///< ��ʾ��������
    HTEXTURE m_ResortTexture;                                                                        ///< ���ŵ�������
    
    hgeGUI *gui;                                                                                     ///< ����GUI����        

    hgeSprite *m_pCursor;                                                                            ///< HGE��꾫��
    hgeSprite *m_pElement[MAX_ELEM_TEXTURE * 4];                                                     ///< HGE���龫������
    hgeSprite *m_pElemSel;                                                                           ///< HGEѡ��Ч������
    hgeSprite *m_pTimeBar;                                                                           ///< HGEʱ���ᾫ��
    
    HEFFECT BGM;                                                                                     ///< ��������
    HEFFECT StartSE;                                                                                 ///< ��ʼ��ťSE
    HEFFECT ElemSelSE;                                                                               ///< ѡ��Ч��SE
    HEFFECT ElecSE;                                                                                  ///< ����SE
    HEFFECT EndSE;                                                                                   ///< ��Ϸ����SE
    HEFFECT ItemBoomSE;                                                                              ///< ���鱬ըSE
    HEFFECT LessTimeSE;                                                                              ///< ʱ��쵽SE
    HEFFECT HintSE;                                                                                  ///< ��ʾ����SE
    HEFFECT ResortSE;                                                                                ///< ���ĵ���SE
    
    MapSeedType m_MapSeed[MAP_SEED_NUM];                                                             ///< ��ͼ����
    
    int m_nLastGUIID;                                                                                ///< ����µ�GUI��ID
    int m_nSeedID;                                                                                   ///< ��ǰ��ͼ������ID
    HCHANNEL BGMChannel;                                                                             ///< HGE��BGMƵ��
    MapType m_Map;                                                                                   ///< ��ͼ
    hgeFont *fnt;                                                                                    ///< HGE����
    
    hgeAnimation *m_BoomAni;                                                                         ///< ��ը��������
    hgeAnimation *m_ThunderAni[6];                                                                   ///< ���綯������
    CElemButton *m_pElemButtonArr[300];                                                              ///< ����GUI����
    CMapSearch *m_pMapSearch;                                                                        ///< ��ͼ�������ʵ��
    float m_thisTime;                                                                                ///< ��һ�εļ�ʱ
    list<BoomAni> BA;                                                                                ///< ��ǰ��Ҫ��ʾ�Ķ�������
    
private:
    /**
     * @brief ���綯����Ⱦ
     * �������е����綯��������Ⱦ����ʱ�Ķ�����������ɾ��
     */
    void BoomLineRender();
    
public:
    HGE *Engine;                                                                                     ///< *���� ���� HGE����
    bool m_bGameStarted;                                                                             ///< ��Ϸ�Ƿ�ʼ
    bool m_bLose;                                                                                    ///< ��Ϸ�Ƿ�ʧ��
    bool m_bWin;                                                                                     ///< ��Ϸ�Ƿ�ʤ��
    bool m_bTimeNotified;                                                                            ///< �Ƿ��Ѿ���ʾʱ���
    int m_nSelArr[2];                                                                                ///< ѡ�з����ID(���ѡ��2��)
    
public:
    CGameWorld(void);
    ~CGameWorld(void);
    
    /**
     * @brief ��ʼ������
     * ������г�ʼ����������Դ�����Լ�HGE����ĳ�ʼ��
     *
     * @see LoadResource
     */
    void Init();
    
    /**
     * @brief ��Դ���뺯��
     * ����Ҫ����Դ���뵽�ڴ浱��
     *
     * @return ��������һ����Դ����ʧ���򷵻�false�����򷵻�true
     */
    bool LoadResource();
    
    /**
     * @brief �ı���ͼԪ����
     * ���ļ�����һ���ı���ͼԪ
     *
     * @param quad �������ı���ͼԪ�ı���
     * @param filename ͼƬ�ļ���
     * @return ������ɹ��򷵻�true�����򷵻�false
     */
    bool QLoad(hgeQuad &quad, char *filename);
    
    /**
     * @brief �ı���ͼԪ������������
     * ����һ��ͼԪ���������꣨��������һ�����Σ�
     *
     * @param quad �����������ı���ͼԪ�ı���
     * @param x1 ���Ͻ�x����
     * @param y1 ���Ͻ�y����
     * @param x2 ���½�x����
     * @param y2 ���½�y����
     */
    void QuadTexture(hgeQuad &quad, float x1, float y1, float x2, float y2);
    
    /**
     * @brief �ı���ͼԪ�ͻ�������������
     * ����һ��ͼԪ�Ŀͻ��������꣨��������һ�����Σ�
     *
     * @param quad �����������ı���ͼԪ�ı���
     * @param x1 ���Ͻ�x����
     * @param y1 ���Ͻ�y����
     * @param x2 ���½�x����
     * @param y2 ���½�y����
     */
    void QuadScreen(hgeQuad &quad, float x1, float y1, float x2, float y2);
    
    /**
     * @brief ɾ����Դ
     * ��Ϸ�˳�֮ǰ�ͷ���Դ\n
     * *�������û�кܺõ����
     */  
    void DelResource();
    
    /**
     * @brief ��Ϸ�߼�����
     * ��Ϸ�Ķ����ڴˣ����簴ť���¡����鰴�¡���ʱ����
     *
     * @see GameStart
     * @see Resort
     * @see CMapSearch::GetPath
     * @see PutAni
     * @see ToSearchMap
     * @return ����Ҫ�˳���Ϸ�����򷵻�true�����򷵻�false
     */  
    bool GameLogicFunc();
    
      /**
     * @brief ��Ϸ��Ⱦ����
     * ������Ϸ������Ⱦ
     *
     * @see BoomLineRender
     * @return ����Ҫ�˳���Ϸ�����򷵻�true�����򷵻�false
     */  
    bool GameRenderFunc();
    
    /**
     * @brief ��Ϸ��ʼ����
     * ��ʼ��Ϸʱ��һЩ��ʼ������
     *
     * @see GameReset
     * @see MakeMap
     * @see CreateElemGUI
     * @see ToSearchMap
     */  
    void GameStart();
    
    /**
     * @brief ��Ϸ���ú���
     * ����һЩ��Ϸ����
     *
     * @see ClearElemGUI
     */  
    void GameReset();
    
    /**
     * @brief ������ͼ����
     * �������һ������ID�������ݸ�����������ɵ�ͼ
     *
     * @see ClearElemGUI
     */  
    void MakeMap();
    
    /**
     * @brief ��������GUI
     * ���ݵ�ͼ��Ϣ�½�����GUI
     *
     * @see CElemButton::CElemButton
     */  
    void CreateElemGUI();
    
    /**
     * @brief ɾ������GUI
     * ɾ��ȫ������GUI
     */ 
    void ClearElemGUI();
    
    /**
     * @brief ��ʼ������ͼ
     * ����ͼ��������CMapSearch���ʵ�������ø�ʵ����������
     *
     * @see CMapSearch
     * @see CMapSearch::Search
     * @see Resort
     */ 
    void ToSearchMap();
    
    /**
     * @brief �Ŷ�������
     * ����Ҫ��ʾ�����綯������ͬ���꣩����һ������
     *
     * @param path ·�߽ṹ�壬�������ڴ�·����ÿһ����ͼ�������һ�����綯�������������
     */ 
    void PutAni(PointPath path);
    
    /**
     * @brief ���ŵ�ͼ����
     * ����ͼ���ݵ�ǰ״̬�������У����ڵ������л��ߵ�ǰ״̬�޽�������
     *
     * @see ClearElemGUI
     * @see CreateElemGUI
     * @see ToSearchMap
     */ 
    void Resort();
};

#endif
