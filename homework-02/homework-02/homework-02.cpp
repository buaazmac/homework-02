#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;
#define MaxN 500
int mode=7;
int n,m,data[MaxN][MaxN];
int sum[MaxN][MaxN];
int pass[MaxN][MaxN];
int pb[MaxN][MaxN];
int qq[MaxN*MaxN];
int change[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int aans=0;

void solve3();
void solve7();
void input()
{
	freopen("input.txt","r",stdin);
	if (mode!=5)
	{
		scanf("%d, %d, ",&n,&m);
		int i,j;
		for (i=1;i<=n;i++)
		{
			for (j=1;j<=m;j++)
				scanf("%d, ",&data[i][j]);
		}
	}else
	{
		scanf("%d, %d, ",&m,&n);
		int i,j;
		for (i=1;i<=m;i++)
			for (j=1;j<=n;j++)
				scanf("%d, ",&data[j][i]);
	}
}

void solve1()
{
	int i,j,s[100],a[100],ans[100];
	memset(s,0,sizeof(s));
	memset(ans,0,sizeof(ans));
	ans[0]=1;
	s[0]=1;
	int flag;
	for (i=1;i<=m;i++)
	{
		if (s[s[0]]<0)
		{
			memset(s,0,sizeof(s));
			s[0]=1;
		}
		flag=0;
		memset(a,0,sizeof(a));
		a[0]=1;a[1]=data[1][i];
		if (a[1]<0)
		{
			a[1]=-a[1];
			flag=1;
		}
		while (a[a[0]]>9)
		{
			a[a[0]+1]=a[a[0]]/10;
			a[a[0]]=a[a[0]]%10;
			a[0]++;
		}
		int l=s[0];
		if (a[0]>l) l=a[0];
		if (flag) {
			for (j=1;j<=l;j++)
			{
				s[j]-=a[j];
				if (s[j]<0 && j<l){
					s[j]+=10;
					s[j+1]-=1;
				}
			}
			while (s[l]==0 && l>1)
				l--;
			s[0]=l;
		}else {
			for (j=1;j<=l;j++)
			{
				s[j]+=a[j];
				if (s[j]>9)
				{
					s[j+1]+=s[j]/10;
					s[j]=s[j]%10;
				}
			}
			if (s[l+1]>0)
				l++;
			s[0]=l;
		}
		int max=0;
		if (s[s[0]]>0){
			if (s[0]>ans[0]){
				max=1;
			}else if (s[0]<ans[0]) {
				max=0;
			}else {
				for (j=s[0];j>0;j--)
					if (s[j]>ans[j])
					{
						max=1;
						break;
					}
					else if (s[j]<ans[j])
					{
						max=0;
						break;
					}
			}
		}
		if (max==1){
			for (j=0;j<=s[0];j++)
				ans[j]=s[j];
		}
	}
	for (i=ans[0];i>0;i--)
		cout<<ans[i];
	cout<<endl;
}

void solve2()
{
	int i,j,k;
	int ans=0;
	memset(sum,0,sizeof(sum));
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
			sum[j][i]=sum[j][i-1]+data[i][j];
	}
	for (i=1;i<=n;i++)
		for (k=1;k<=i;k++)
		{
			int temps=0;
			for (j=1;j<=m;j++)
			{
				int a=sum[j][i]-sum[j][k-1];
				if (temps<0)	temps=0;
				temps+=a;
				if (temps>ans)
					ans=temps;
			}
		}
	cout<<ans<<endl;
}

void	dfs(int x,int y)
{
	if (x>n)
	{
		if (mode==3)
			solve3();
		else 
			solve7();
		return;
	}
	int xx=x,yy=y+1;
	if (yy>m)
	{
		yy=1;
		xx++;
	}
	pass[x][y]=1;
	dfs(xx,yy);
	pass[x][y]=0;
	dfs(xx,yy);
}

void solve3()
{
	memset(qq,0,sizeof(qq));
	memset(pb,0,sizeof(pb));
	int h=1,t=1;
	int i,j,k;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
			if (pass[i][j]==1)
				break;
		if (j<=m)
			break;
	}
	pb[i][j]=1;
	qq[1]=(i-1)*m+j;
	while (h<=t)
	{
		int x,y;
		x=(qq[h]-1)/m+1;
		y=qq[h]%m;
		if (y==0)	y=m;
		for (k=0;k<4;k++)
		{
			int xx=x+change[k][0],yy=y+change[k][1];
			int temp;
			if (xx<1 || xx>n || yy<1 || yy>m)
				continue;
			temp=(xx-1)*m+yy;
			if (pass[xx][yy]==1 && pb[xx][yy]==0)
			{
				qq[++t]=temp;
				pb[xx][yy]=1;
			}	
		}
		h++;
	}
	int flag=0,temps=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (pass[i][j]==1)
			{
				temps+=data[i][j];
				if (pb[i][j]==0)
					flag=1;
			}
	temps=temps;
	if (flag==0 && temps>aans)
		aans=temps;
}

void solve4()
{
	int i,j,k;
	int ans=0;
	memset(sum,0,sizeof(sum));
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++){
			sum[j][i]=sum[j][i-1]+data[i][j];
			sum[j+m][i]=sum[j][i];
		}
	}
	for (i=1;i<=n;i++)
		for (k=1;k<=i;k++)
		{
			int temps=0,templ=0,asum=0,min=9999999;
			for (j=1;j<=m;j++)
			{
				int a=sum[j][i]-sum[j][k-1];
				if (temps<0)	temps=0;
				temps+=a;
				if (temps>ans)
					ans=temps;
				if (templ>0)	templ=0;
				templ+=a;
				if (templ<min)
					min=templ;
				asum+=a;
			}
			if (asum-min>ans)
				ans=asum-min;
		}
	cout<<ans<<endl;
}

void solve5()
{
	solve4();
}

void solve6()
{
	int i,j,k;
	int ans=0;
	memset(sum,0,sizeof(sum));
	for (i=1;i<=2*n;i++)
	{
		int ii=i;
		if (ii>n)
			ii-=n;
		for (j=1;j<=m;j++)
			sum[j][i]=sum[j][i-1]+data[ii][j];
	}
	for (i=1;i<=2*n;i++)
		for (k=1;k<=i;k++)
		{
			if (i-k>=n)
				continue;
			int temps=0,templ=0,asum=0,min=9999999;
			for (j=1;j<=m;j++)
			{
				int a=sum[j][i]-sum[j][k-1];
				if (temps<0)	temps=0;
				temps+=a;
				if (temps>ans)
					ans=temps;
				if (templ>0)	templ=0;
				templ+=a;
				if (templ<min)
					min=templ;
				asum+=a;
			}
			if (asum-min>ans)
				ans=asum-min;
		}
	cout<<ans<<endl;
}

void solve7()
{
	memset(qq,0,sizeof(qq));
	memset(pb,0,sizeof(pb));
	int h=1,t=1;
	int i,j,k;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
			if (pass[i][j]==1)
				break;
		if (j<=m)
			break;
	}
	pb[i][j]=1;
	qq[1]=(i-1)*m+j;
	while (h<=t)
	{
		int x,y;
		x=(qq[h]-1)/m+1;
		y=qq[h]%m;
		if (y==0)	y=m;
		for (k=0;k<4;k++)
		{
			int xx=x+change[k][0],yy=y+change[k][1];
			int temp;
			if (xx<1)
				xx=n;
			if (xx>n)
				xx=1;
			if (yy<1)
				yy=m;
			if (yy>m)
				yy=1;
			temp=(xx-1)*m+yy;
			if (pass[xx][yy]==1 && pb[xx][yy]==0)
			{
				qq[++t]=temp;
				pb[xx][yy]=1;
			}	
		}
		h++;
	}
	int flag=0,temps=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (pass[i][j]==1)
			{
				temps+=data[i][j];
				if (pb[i][j]==0)
					flag=1;
			}
	temps=temps;
	if (flag==0 && temps>aans)
		aans=temps;
}



int main(int argc,char *argv[])
{
	// /*
	memset(pass,0,sizeof(pass));
	char filename[100];
	if (argc==2)
	{
		strcpy(filename,argv[1]);
		mode=1;
	}else if (argc==3)
	{
		strcpy(filename,argv[2]);
		if (strcmp(argv[1],"/v"))
			mode=5;
		if (strcmp(argv[1],"/h"))
			mode=4;
		if (strcmp(argv[1],"/a"))
			mode=3;
		if (strcmp(argv[1],""))
			mode=2;
	}else if (argc==4)
	{
		mode=6;
		strcpy(filename,argv[3]);
	}
	else if (argc==5)
	{
		mode=7;
		strcpy(filename,argv[4]);
	}
	// */
	input();
	if (mode==1)
		solve1();
	else if (mode==2)
		solve2();
	else if (mode==3)
		dfs(1,1);
	else if (mode==4)
		solve4();
	else if (mode==5)
		solve5();
	else if (mode==6)
		solve6();
	else if (mode==7)
		dfs(1,1);
	if (mode==3 || mode==7)
		cout<<aans<<endl;
	return 0;
}