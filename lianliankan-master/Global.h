//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file Global.h
/// @brief ȫ�ֱ����ļ�
///
/// ������һЩȫ�ֱ���
/// @version 1.0
/// @author ����
/// @date 2010��10��5��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#include "GameWorld.h"

extern CGameWorld *g_GameWorld;             ///< ������Ϸ���ʵ��

/**
 * ��Ϸ�߼�����
 * �߼�������HGE���濪ʼ�󽫲�ͣ������\n
 * ����ĺ���������CGameWorld���ȫ�ֱ���g_GameWorld�е�GameLogicFunc����
 *
 * @see CGameWorld::GameLogicFunc
 * @return �����򽫹ر��򷵻�true�����򷵻�false
 */
extern bool LogicFunc();

/**
 * ��Ϸ��Ⱦ����
 * ��Ⱦ������HGE���濪ʼ�󽫲�ͣ������\n
 * ����ĺ���������CGameWorld���ȫ�ֱ���g_GameWorld�е�GameRenderFunc����
 *
 * @see CGameWorld::GameRenderFunc
 * @return �����򽫹ر��򷵻�true�����򷵻�false
 */
extern bool RenderFunc();

extern Coor GetElemTex[4];                  ///< ������ͼƬ���ĸ�����Ķ�������
