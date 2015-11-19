//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file ElemButton.h
/// @brief ����GUI���ļ�
///
/// ����GUI���ʵ���ļ�
/// @version 1.0
/// @author ����
/// @date 2010��10��5��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <hge.h>
#include <hgegui.h>
#include <hgeanim.h>

class CGameWorld;

#define PADDING_TOP             172                 ///< ��Ϸ���򶥲�����
#define PADDING_LEFT            20                  ///< ��Ϸ�����󲿾���

#define MAP_HEIGHT              10                  ///< ��ͼ�߶�
#define MAP_WIDTH               18                  ///< ��ͼ���
#define ID_ELEM_GUI_START       50                  ///< ����GUI����ʼID

#define ELEM_INTERFACE_HEIGHT   36                  ///< �������ĸ߶�
#define ELEM_INTERFACE_WIDTH    32                  ///< �������Ŀ��
#define ELEM_INTERFACE_OFFSET_X -4                  ///< �����x��ƫ����
#define ELEM_INTERFACE_OFFSET_Y 0                   ///< �����y��ƫ����

/**
 * @brief ����GUI��
 *
 * ����GUI�࣬�̳���HGE�����hgeGUIObject�ࡣ
 * ��Ϸ�е����з��鶼��������ʵ����
 */
class CElemButton : public hgeGUIObject
{
private:
    hgeSprite *m_pElem;                             ///< ����GUI�Ļ��澫�飬�ں���������
    hgeSprite *m_pSel;                              ///< ����GUIѡ��Ч������
    CGameWorld *m_pGameWorld;                       ///< ��Ϸ������ָ�룬ָ�����ĸ�����
    float Screen_x;                                 ///< ��GUI�ڿͻ������е�x����
    float Screen_y;                                 ///< ��GUI�ڿͻ������е�y����
    int Map_x;                                      ///< ��GUI�ڵ�ͼ�е�x����
    int Map_y;                                      ///< ��GUI�ڵ�ͼ�е�y����
    int m_nRealID;                                  ///< ��GUI��ʵ��ID����ȥ��ʼ�� ID_ELEM_GUI_START��
    HEFFECT m_SelSE;                                ///< ѡ�и�GUIʱ����Ч
    hgeAnimation *m_pBoomAni;                       ///< ��GUI��ȥʱ�Ķ���
    float timer;                                    ///< ��GUI����ȥ��ʱ��ʱ�䵽����ֹͣ���Ų���GUI��ʧ��
    bool m_bLeaving;                                ///< GUI�Ƿ�������ʧ

public:
    bool m_bSelected;                               ///< GUI�Ƿ�ѡ��
    
      /**
     * @brief ���캯��
     * ���ݴ����������һ������GUI
     *
     * @param _id �÷����ID����ʼIDΪID_ELEM_GUI_START��
     * @param *pGameWorld ��Ϸ��ָ�룬ָ�򸸶���
     * @param *pElem �÷���GUI����Ӧ��ͼ����ָ�룬���ڴ����÷�����ʽ
     * @param *pSel ����GUIѡ��Ч������Ӧ��ͼ����ָ��
     * @param snd ����GUI����Ч
     * @param *pBoomAni ����GUI��ըʱ����Ӧ�Ķ�������ָ��
     */
    CElemButton(int _id, CGameWorld *pGameWorld, hgeSprite *pElem, hgeSprite *pSel, HEFFECT snd, hgeAnimation *pBoomAni);
    ~CElemButton(void);
    
      /**
     * @brief ��Ⱦ����GUI���麯����
     * ���жԷ���GUI����Ⱦ
     */
    virtual void Render();
    
      /**
     * @brief ����GUI���״̬�������麯����
     * ����GUI�������ʱ����Ӧ�Ķ���
     *
     * @param bDown ��������״̬����Ϊ������Ϊtrue������Ϊfalse
     * @return ����ؼ��Ѿ��༭���������״̬��������Ҫ֪ͨ�����ߣ� MouseLButtonӦ����true��������Ӧ����false��
     */
    virtual bool MouseLButton(bool bDown);
    
      /**
     * @brief ÿ��GUI����ʱ���ã����ڸ��¿ؼ����������麯����
     *
     * @param dt ����һ�ε���Update���������ʱ����������Ϊ��λ�� 
     */
    virtual void Update(float dt);
    
      /**
     * @brief ���ø÷����״̬Ϊ��Ҫ��ȥ
     */
    void ToLeave();
};
