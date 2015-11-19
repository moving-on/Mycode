#include "ElemButton.h"
#include "GameWorld.h"

CElemButton::CElemButton(int _id, CGameWorld *pGameWorld, hgeSprite *pElem, hgeSprite *pSel, HEFFECT snd, hgeAnimation *pBoomAni)
: m_bSelected(false)
, timer(0.0f)
, m_bLeaving(false)
{
    id = _id;
    m_pGameWorld = pGameWorld;

    m_pElem = new hgeSprite(*pElem);
    m_pSel = new hgeSprite(*pSel);
    m_pBoomAni = new hgeAnimation(*pBoomAni);
    m_SelSE = snd;

    //GUI����ʵID
    m_nRealID = id - ID_ELEM_GUI_START;

    //GUI�ڵ�ͼ�е�����
    Map_y = m_nRealID / MAP_WIDTH;
    Map_x = m_nRealID % MAP_WIDTH;

    //GUI����Ļ�е�����
    Screen_x = PADDING_LEFT + ELEM_INTERFACE_WIDTH * Map_x + ELEM_INTERFACE_OFFSET_X;
    Screen_y = PADDING_TOP + ELEM_INTERFACE_HEIGHT * Map_y + ELEM_INTERFACE_OFFSET_Y;

    bStatic = false, bVisible = true, bEnabled = true;

    rect.Set(Screen_x, Screen_y, Screen_x + 35, Screen_y + 39);
}

void CElemButton::Render()
{
    if(!m_bLeaving && bVisible)     //���������״̬
    {
        //����÷����Ѿ�ʧȥ�˽��㣬��ѡ��״̬��Ϊfalse
        if(m_pGameWorld->m_nSelArr[0] != id && m_pGameWorld->m_nSelArr[1] != id)
            m_bSelected = false;

        //������
        m_pElem->Render(rect.x1, rect.y1);

        if(m_bSelected) m_pSel->Render(rect.x1 + 4, rect.y1);
    }
    else
    if(m_bLeaving && bVisible)      //�������ȥ����״̬
    {
        float dt = m_pGameWorld->Engine->Timer_GetDelta();
        m_pBoomAni->Update(dt);
        m_pBoomAni->Render(rect.x1, rect.y1);
    }
}

void CElemButton::ToLeave()         //��ȥԤ����
{
    timer = 0;
    m_bLeaving = true;
    m_pBoomAni->Play();
    bEnabled = false;
}

void CElemButton::Update(float dt)
{
    //��״̬Ϊ��ȥ��������ʼ����ʱ������ͬʱ���㱬ը͸����
    if(m_bLeaving)
    {
        timer += dt;
        int alpha = 255 - (int)((timer / 1.5) * 255);
        m_pBoomAni->SetColor(ARGB(alpha, 0xff, 0xff, 0xff));

        if(timer > 1.5)
        {
            bVisible = false;
            m_bLeaving = false;
        }
    }
    else
    if(!m_pGameWorld->m_bGameStarted && m_pGameWorld->m_bLose)         //���ʱ�䵽
    {
        bEnabled = false;
        m_pElem->SetColor(0xff999999);
    }
}

bool CElemButton::MouseLButton(bool bDown)
{
    //����������
    if(bDown)
    {
        //������Ч
        m_pGameWorld->Engine->Effect_Play(m_SelSE);
        //����Ϊѡ��
        m_bSelected = true;

        //�жϿͻ�����ѡ��Ԫ��
        if(m_pGameWorld->m_nSelArr[0] == id || m_pGameWorld->m_nSelArr[1] == id){}
        else
        if(m_pGameWorld->m_nSelArr[0] == -1) m_pGameWorld->m_nSelArr[0] = id;
        else
        if(m_pGameWorld->m_nSelArr[1] == -1) m_pGameWorld->m_nSelArr[1] = id;
    }

    return bDown ? false : true;
}

CElemButton::~CElemButton(void)
{
    delete m_pElem;
    delete m_pSel;
}
