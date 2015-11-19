#define M 1 
/* B 树的阶，即非根节点中键的最小数目。
* 有些人把阶定义为非根节点中子树的最大数目。
*/
typedef int typekey;
typedef struct btnode { /* B-Tree 节点 */
	int d; /* 节点中键的数目 */
	typekey k[2 * M]; /* 键 */
	char *v[2 * M]; /* 值 */
	struct btnode *p[2 * M + 1]; /* 指向子树的指针 */
} node, *btree;
/*
* 每个键的左子树中的所有的键都小于这个键，
* 每个键的右子树中的所有的键都大于等于这个键。
* 叶子节点中的每个键都没有子树。
*/

/* 当 M 等于 1 时也称为 2-3 树
* +----+----+
* | k0 | k1 |
* +-+----+----+---
* | p0 | p1 | p2 |
* +----+----+----+
*/
extern int btree_disp; /* 查找时找到的键在节点中的位置 */
extern char * InsValue; /* 与要插的键相对应的值 */

extern btree search(typekey, btree);
extern btree insert(typekey, btree);
extern btree Delete(typekey, btree);
extern int height(btree);
extern int count(btree);
extern double payload(btree);
extern btree deltree(btree);