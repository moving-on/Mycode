//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file TinyButton.h
/// @brief ��ͨGUI��ť���ļ�
///
/// ��ͨGUI��ť���ʵ���ļ�
/// @version 1.0
/// @author ����
/// @date 2010��10��5��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "hgegui.h"

/**
 * @brief ��ͨGUI��ť��
 *
 * ��ͨ�İ�ť�࣬�̳���HGE�����hgeGUIObject��
 */
class CTinyButton : public hgeGUIObject
{
private:
    HEFFECT m_ClickEffect;                                          ///< ��ť���ʱ����Ч
    hgeSprite *m_BtnDown;                                           ///< ��ť����ʱ��ͼƬ����ָ��
    hgeSprite *m_BtnUp;                                             ///< ��ťû����ʱ��ͼƬ����ָ��
    hgeSprite *m_Now;                                               ///< ��ť��ǰͼƬ����ָ�루ָ����ͼƬ�������û����ͼƬ���飩
    float h;                                                        ///< ��ť��
    float w;                                                        ///< ��ť��
    HGE *Engine;                                                    ///< HGE����ָ�룬ָ�򸸶��������

public:
      /**
     * @brief ���캯��
     * ���ݴ����������һ��GUI
     *
     * @param _id GUI��ID
     * @param *_Engine HGE����ָ�룬ָ�򸸶����Engine
     * @param *tex GUI������������Ⱦ��GUI
     * @param _x ��GUI�ڿͻ����������x����ֵ
     * @param _y ��GUI�ڿͻ����������y����ֵ
     * @param _w ��GUI�Ŀ�
     * @param _h ��GUI�ĸ�
     * @param ClickEffect ��GUI����ʱ����Ч
     * @param debug �Ƿ��ǡ���λģʽ������Ϊ�����û����ʱGUIΪ͸���������ڡ���λģʽ���н���״̬��GUI��Ϊ��ɫ
     */
    CTinyButton(int _id, HGE *_Engine, HTEXTURE tex, float _x, float _y, float _w, float _h, HEFFECT ClickEffect, bool debug = false);
    ~CTinyButton(void);
    
      /**
     * @brief GUI���״̬�������麯����
     * ����GUI�������ʱ����Ӧ�Ķ���
     *
     * @param bDown ��������״̬����Ϊ������Ϊtrue������Ϊfalse
     * @return ����ؼ��Ѿ��༭���������״̬��������Ҫ֪ͨ�����ߣ� MouseLButtonӦ����true��������Ӧ����false��
     */
    virtual bool MouseLButton(bool bDown);
    
      /**
     * @brief ��Ⱦ����GUI���麯����
     * ���жԷ���GUI����Ⱦ
     */
    virtual void Render();
};
