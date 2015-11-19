#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 50010;
const int MAXK = 5;
const int MAXM = 10;

int n, m, k;
struct Point
{
	int p[MAXK];
	inline void input()
	{
		for (int i = 0; i<k; ++i)
		{
			scanf_s("%d", &p[i]);
		}
	}
	inline void output() const
	{
		for (int i = 0; i<k; ++i)
		{
			if (i)
			{
				printf(" ");
			}
			printf("%d", p[i]);
		}
		printf("\n");
	}
}point[MAXN], searchPoint;
int pointSet[16][MAXN];
int pointNumber[16];
set<Point> ans;

inline int getDistance(const Point &a, const Point &b)
{
	int ans = 0;
	for (int i = 0; i<k; ++i)
	{
		ans += (a.p[i] -b.p[i]) * (a.p[i] -b.p[i]);
	}
	return ans;
}

bool operator < (const Point &a, const Point &b)
{
	return getDistance(a, searchPoint) < getDistance(b, searchPoint);
}

struct TreeNode
{
	int dim, index;
	bool left, right;
}tree[MAXN];

int sortDimension;
bool compare(int x, int y)
{
	return point[x].p[sortDimension] < point[y].p[sortDimension];
}

bool buildTree(int x, int depth)
{
	int dim = depth % k;
	if (pointNumber[depth] == 0)
	{
		return false;
	}
	else if (pointNumber[depth] == 1)
	{
		tree[x].dim = dim;
		tree[x].index = pointSet[depth][0];
		tree[x].left = false;
		tree[x].right = false;
		return true;
	}
	sortDimension = dim;
	sort(pointSet[depth], pointSet[depth] + pointNumber[depth], compare);
	int mid = pointNumber[depth] >> 1;
	tree[x].dim = dim;
	tree[x].index = pointSet[depth][mid];
	pointNumber[depth + 1] = 0;
	for (int i = 0; i<mid; ++i)
	{
		pointSet[depth + 1][pointNumber[depth + 1] ++] = pointSet[depth][i];
	}
	tree[x].left = buildTree(x << 1, depth + 1);
	pointNumber[depth + 1] = 0;
	for (int i = mid + 1; i<pointNumber[depth]; ++i)
	{
		pointSet[depth + 1][pointNumber[depth + 1] ++] = pointSet[depth][i];
	}
	tree[x].right = buildTree((x << 1) + 1, depth + 1);
	return true;
}

#ifndef ONLINE_JUDGE
void printTree(int x, int depth)
{
	printf("Layer %d: ", depth);
	point[tree[x].index].output();
	if (tree[x].left)
	{
		printTree(x << 1, depth + 1);
	}
	if (tree[x].right)
	{
		printTree((x << 1) + 1, depth + 1);
	}
}
#endif

inline void insertPossibility(const Point &point)
{
	ans.insert(point);
	if (ans.size() > m)
	{
		set<Point>::reverse_iterator it = ans.rbegin();
		ans.erase(*it);
	}
}

void queryTree(int x)
{
	insertPossibility(point[tree[x].index]);
	if (!tree[x].left && !tree[x].right)
	{
		return;
	}
	bool flag = false;
	int dist1 = searchPoint.p[tree[x].dim] - point[tree[x].index].p[tree[x].dim];
	dist1 *= dist1;
	if (searchPoint.p[tree[x].dim] < point[tree[x].index].p[tree[x].dim])
	{
		if (tree[x].left)
		{
			queryTree(x << 1);
		}
		if (tree[x].right)
		{
			if (ans.size() < m)
			{
				flag = true;
			}
			else
			{
				set<Point>::reverse_iterator it = ans.rbegin();
				Point temp = *it;
				int dist2 = getDistance(temp, searchPoint);
				if (dist1 <= dist2)
				{
					flag = true;
				}
			}
			if (flag)
			{
				queryTree((x << 1) + 1);
			}
		}
	}
	else
	{
		if (tree[x].right)
		{
			queryTree((x << 1) + 1);
		}
		if (tree[x].left)
		{
			if (ans.size() < m)
			{
				flag = true;
			}
			else
			{
				set<Point>::reverse_iterator it = ans.rbegin();
				Point temp = *it;
				int dist2 = getDistance(temp, searchPoint);
				if (dist1 <= dist2)
				{
					flag = true;
				}
			}
			if (flag)
			{
				queryTree(x << 1);
			}
		}
	}
}

void solve()
{
	ans.clear();
	queryTree(1);
}

int main()
{
	int t;
	while (~scanf_s("%d%d", &n, &k))
	{
		pointNumber[0] = n;
		for (int i = 0; i<n; ++i)
		{
			point[i].input();
			pointSet[0][i] = i;
		}
		buildTree(1, 0);
#ifndef ONLINE_JUDGE
		printTree(1, 0);
#endif
		scanf_s("%d", &t);
		while (t--)
		{
			searchPoint.input();
			scanf_s("%d", &m);
			solve();
			printf("the closest %d points are:\n", m);
			for (set<Point>::iterator it = ans.begin(); it != ans.end(); ++it)
			{
				it->output();
			}
		}
	}
	return 0;
}