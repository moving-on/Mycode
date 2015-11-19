//////////////////////////////////////////////////////////////////////////
///     COPYRIGHT NOTICE
///     Copyright (c) 2010, ������ͼ(X2Studio.Net)
///     All rights reserved.
///
/// @file MapSearch.h
/// @brief ��ͼ�����߼��ļ�
///
/// ��ͼ����ʱ����Ҫ�߼���ʵ��
/// @version 1.0
/// @author ����
/// @date 2010��10��6��
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <list>
using namespace std;

#define MAP_HEIGHT              10                  ///< ��ͼ�߶�
#define MAP_WIDTH               18                  ///< ��ͼ���
#define ID_ELEM_GUI_START       50                  ///< ����GUI����ʼID

/**
 * @brief ��ͼ����ṹ��
 *
 * ��ͼ����ṹ�壬����x��ֵ��y��ֵ
 * �Լ�һЩ����������
 */
struct CoorType {
    int x;                                          ///< x��
    int y;                                          ///< y��
    
    /**
     * ���ع��캯��
     * ��x��yֵ����ʼ��Ϊ-1
     */
    CoorType()
    {
        x = -1, y = -1;
    }

    /**
     * ���캯������
     * ��x��y����ֵΪb��a
     * @param a ��Ҫ��ֵ��y����ֵ
     * @param b ��Ҫ��ֵ��x����ֵ
     */
    CoorType(int a, int b)
    {
        y = a, x = b;
    }
    
    /**
     * ��������
     * ��x��y����ֵΪb��a
     * @param a ��Ҫ��ֵ��y����ֵ
     * @param b ��Ҫ��ֵ��x����ֵ
     */
    void Set(int a, int b)
    {
        y = a, x = b;
    }

    /**
     * �����"+="����
     * ������������һ�������
     * @param &a ��һ����
     * @return ���ؽ������ֵ
     */
    CoorType & operator += (const CoorType &a)
    {
        y += a.y, x += a.x;
        return *this;
    }

    /**
     * ���������"!="
     * �ж�����һ�����Ƿ��ʾͬһ��ֵ
     * @param &a ��һ����
     * @return ���ز������ͱ�ʾ�Ƿ����
     */
    bool operator != (const CoorType &a)
    {
        if(y != a.y || x != a.x) return false;
        else return true;
    }

    /**
     * �жϴ������Ƿ�Ϸ�
     * �������򲻺Ϸ�
     * @return ���ز������ͱ�ʾ�Ƿ�Ϸ�
     */
    bool isIll()
    {
        if(y >= 0 && x >= 0 && y < MAP_HEIGHT && x < MAP_WIDTH) return true;
        else return false;
    }
};

typedef list<CoorType> Lst;                         ///< ��list<CoorType>������ΪLst
typedef map<int, Lst> STLMap;                       ///< ��map<int, list<CoorType>>������ΪSTLMap

/**
 * @brief ·�߽ṹ��
 *
 * �Ϸ�·�߽ṹ��
 * ��������ĸ��㣨����յ������ת�۵㣩
 */
struct PointPath {
    bool bExist;                                    ///< �Ƿ���·��
    int Num;                                        ///< פ�����
    CoorType Points[4];                             ///< ��פ��
};

/**
 * @brief ��ͼ������
 *
 * ����ָ����ͼ���������Ϸ�·����
 */
class CMapSearch
{
private:
    int Map[MAP_HEIGHT][MAP_WIDTH];                                             ///< ��ͼ���ݾ���
    PointPath dis[MAP_HEIGHT][MAP_WIDTH][MAP_HEIGHT][MAP_WIDTH];                ///< ·������
    STLMap grap;                                                                ///< STLӳ��
    CoorType dir[4];                                                            ///< ������������
    PointPath Hint;                                                             ///< ��ʾʱ�õĺϷ�·��
    
    /**
     * @brief ����Ѱ��
     *
     * ��(x1, y1)��(x2, y2)����Ѱ��
     * @param x1 ��һ�������x��
     * @param y1 ��һ�������y��
     * @param x2 �ڶ��������x��
     * @param y2 �ڶ��������y��
     * @return ����һ��·�߽ṹ���ֵ����������·������ṹ���bExistΪ��
     * @see Abled
     */
    PointPath DoSearch(int y1, int x1, int y2, int x2);
    
public:
    /**
     * @brief ���캯��
     * 
     * @param _Map[][Map_Width] ��ͼ����
     */
    CMapSearch(int _Map[][MAP_WIDTH]);
    
    /**
     * @brief ��������
     */
    ~CMapSearch(void);
    
    /**
     * @brief �����ͼ
     * �Ӿ����������ͼ������
     * 
     * @param _Map[][Map_Width] ��ͼ����
     */
    void LoadMap(int _Map[][MAP_WIDTH]);
    
    /**
     * @brief ������ͼ
     * ��������ͼ��������ÿ������ͬ����֮���·��
     * 
     * @return �����������һ��·���򷵻��棬����Ϊ�٣������Ƿ�����
     * @see CreateSTLMap
     * @see DoSearch
     */
    bool Search();
    
    /**
     * @brief ����mapӳ��
     * ����һ������ID��ӳ�䣬��ÿ��ID����һ���ĸ�ID�ķ����ڵ�ͼ�еĸ����������
     */
    void CreateSTLMap();
    
    /**
     * @brief �ж��Ƿ����ϰ�
     * ����a��b�����꣨��ͬһֱ�ߣ������ж��ڼ��Ƿ��з����ϰ������²�������
     *
     * @param a ����a��ͷ���꣩
     * @param b ����b��β���꣩
     * @param head ������ͷ������Ϊtrue������Ϊfalse
     * @param tail ������β������Ϊtrue������Ϊfalse
     * @return �����ϰ��򷵻�false������Ϊtrue
     */
    bool Abled(CoorType a, CoorType b, bool head = false, bool tail = false);
    
    /**
     * @brief �õ�·��
     * �õ�������������߾���·��
     *
     * @param y1 ��һ�������y��
     * @param x1 ��һ�������x��
     * @param y2 �ڶ��������y��
     * @param x2 �ڶ��������x��
     * @return ����һ��·�߽ṹ�壬��ʾ����������ֱ�ӵ�·��
     */
    PointPath GetPath(int y1, int x1, int y2, int x2);
    
    /**
     * @brief �õ���ʾ·��
     * �õ�һ����ʾ��·������Ӧ��������
     *
     * @param &a ���ܵ�һ������ID�ı���
     * @param &b ���ܵڶ�������ID�ı���
     */
    void GetRandomHint(int &a, int &b);
};
