//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file LinkMe.cpp
/// @brief ��������Ϸ����ļ�
///
/// ��Ϸ����ļ�
/// @version 1.0
/// @author ����
/// @date 2010��10��5��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#include "GameWorld.h"
#include "Global.h"

/**
 * ������ں���WinMain
 * �ú���ʵ����һ��CGameWorld�ಢ���г�ʼ������
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    g_GameWorld = new CGameWorld();
    g_GameWorld->Init();

    return 0;
}
