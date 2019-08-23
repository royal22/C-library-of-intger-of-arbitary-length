#include<stdio.h>
#include<stdlib.h>
#include"intal.h"
#include<ctype.h>
#include<string.h>
typedef struct 
{
int n;
int d[0];
} verylong;
verylong **hz=NULL;
int hzn=0;
void longint(int);
void *intal_create(const char *a){
	int i,j,n=0,m,k;verylong *d;
	while(*a=='0')
	a++;
	
	while(a[n++]!='\0');
	n--;
	m=(n+7)/8;
	if(m==0)
	{
	d=(verylong*)malloc(sizeof(verylong)+sizeof(int));
	d->n=1;
	d->d[0]=0;
	return (void*)d;
	}

	d=(verylong*)malloc(sizeof(verylong)+sizeof(int)*m);
	d->n=m;
	
	for(i=0;i<m-1;i++)
	{
		n=n-8;k=0;
		for(j=0;j<8;j++)
			k=10*k+(a[n+j]-'0');
		d->d[i]=k;
	}
	
	k=0;
	for(i=0;i<n;i++)
		k=10*k+(a[i]-'0');
	d->d[m-1]=k;
	
	return (void*)d;
}

char *intal2str(void *a){
	verylong *d;int i,j,n,m,k;char *o,*m1="NaN";
	if(a==NULL)
	{
	o=(char*)malloc(sizeof(char)*4);
		for(i=0;i<4;i++)
			o[i]=m1[i];
		return o;
	}
	d=(verylong*)a;
	m=d->n;
	k=d->d[m-1];n=8*(m-1);
	if(d->n==1&&d->d[0]==0)
	{
	o=(char*)malloc(sizeof(char)*2);
	o[0]='0';
	o[1]='\0';
	return o;
	}
	while(k)
	{
	k=k/10;n++;
	}
	o=(char*)malloc(sizeof(char)*(n+1));
	o[n--]='\0';
	for(i=0;i<m-1;i++)
	{
	k=d->d[i];
	for(j=0;j<8;j++,k/=10)
	o[n--]=(k%10)+'0';
	}
	k=d->d[m-1];
	while(k)
	{
	o[n--]=(k%10)+'0';
	k=k/10;
	}

	int ksp;
	for(ksp=0;o[ksp]!='\0';ksp++)
	{
		if(isalpha(o[ksp]))
			printf("null");
			//return "0";
	}
	return o;
}

/*void print(verylong *d){
	char *o;
	o=intal2str((void*)d);
	printf("i:%s\n",o);
	free((void*)o);
}*/

int intal_compare(void *a,void *b){
	verylong *x,*y;int i;
	if(a==NULL||b==NULL)
	return -2;
	
	x=(verylong*)a;y=(verylong*)b;
	
	if(x->n!=y->n)
	return 1-2*(x->n<y->n);
	
	i=x->n;
	
	while(i--)
	{
	if(x->d[i]!=y->d[i])
	return 1-2*(x->d[i]<y->d[i]);
	}
	
return 0;
}

void *intal_increment(void *a){
	verylong *d,*o;int i,m;
	if(a==NULL)
	return NULL;
	d=(verylong*)a;m=d->n;
	for(i=0;i<m;i++)
		if(d->d[i]!=99999999)
			break;
	if(i==m)
	{
	free(a);
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*(m+1));
	o->n=m+1;
	o->d[m]=1;
	for(i=0;i<m;i++)
		o->d[i]=0;
	return (void*)o;
	}
	d->d[i]++;i--;
	while(i>=0)
		d->d[i--]=0;
	return a;
}

void *intal_decrement(void *a){
	verylong *d,*o;int i,m;

	if(a==NULL)
	{
	return NULL;
	}

        d=(verylong*)a;
	m=d->n;

	if(m==1&&d->d[0]==0)
	{
	return a;
	}

	for(i=0;i<m;i++)
	{
		if(d->d[i]!=0)
		{
		break;
		}
	}
	
	if(i==m-1&&d->d[m-1]==1)
	{	
		if(i==0)
		{
		free(a);
		return intal_create("0");
		}
		
		else
		{
		free(a);
		o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*(m-1));
		o->n=m-1;
		for(i=0;i<m-1;i++)
		{
		o->d[i]=99999999;
		}
		return (void*)o;
		}
	}
	
	d->d[i]--;
	i--;

	while(i>=0)
	{
	d->d[i--]=99999999;
	}

return a;
}

void *intal_add(void *a,void *b){
	verylong *o,*x,*y;int i,m,n,k,l;
	if(a==NULL||b==NULL)
	return NULL;
	x=(verylong*)a;
	y=(verylong*)b;
	m=x->n;
	n=y->n;
	l=m>n?m:n;
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*l);o->n=l;
	l=m<n?m:n;k=0;
	for(i=0;i<l;i++)
	{
	k=x->d[i]+y->d[i]+k;
	o->d[i]=k%100000000;
	k=k/100000000;
	}
	l=o->n;
	x=m>n?x:y;
	while(i<l)
	{
	k=x->d[i]+k;
	o->d[i]=k%100000000;
	k=k/100000000;i++;
	}
	if(k)
	{
	o=(verylong*)realloc((void*)o,sizeof(verylong)+sizeof(int)*(l+1));
	o->n=l+1;
	o->d[l]=k;
	}
	return (void*)o;
}

void *intal_diff(void *a,void *b){
	verylong *o,*x,*y;int i,m,n,k;
	if(a==NULL||b==NULL)
	{
	return NULL;
	}
	x=(verylong *)a;
	y=(verylong*)b;
	m=x->n;
	n=y->n;
	if(m==n)
	{	
		for(i=m-1;i>=0;i--)
		{
		if(x->d[i]!=y->d[i])
			break;
		}
		
		if(i==-1)
		{
		o=(verylong*)malloc(sizeof(verylong)+sizeof(int));
		o->n=1;
		o->d[0]=0;
		return (void*)o;
		}
		
		if(y->d[i]>x->d[i])
		{
		o=x;x=y;y=o;
		}
		
		m=i+1;
		o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*m);
		o->n=m;
		for(i=0,k=1;i<m;i++)
		{
		k=x->d[i]+99999999-y->d[i]+k;
		o->d[i]=k%100000000;
		k=k/100000000;
		}
		i=m-1;
		while(o->d[i]==0)
		{
		i--;
		}
		o=(verylong*)realloc((void*)o,sizeof(verylong)+sizeof(int)*(i+1));
		o->n=i+1;
	return ((void*)o);
	}
	
	if(m<n)
	{
	k=m;m=n;n=k;o=x;x=y;y=o;
	}
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*m);
	o->n=m;

	for(i=m-1;i>=0;i--)
	{
	o->d[i]=x->d[i];//o=(verylong*)intal_decrement((void*)o);
	}	

	for(i=0,k=1;i<n;i++)
	{
	k=k+x->d[i]+99999999-y->d[i];
	o->d[i]=k%100000000;
	k=k/100000000;
	}
	
	if(k==0)
	{
	while(o->d[i]==0)
	{
	o->d[i]=999999999;
	i++;
	}
	o->d[i]--;
	}
	
	i=o->n;
	while(i--)
	{	if(o->d[i])
			break;
	}	
	o->n=i+1;
	o=(verylong*)realloc((void*)o,sizeof(verylong)+(i+1)*sizeof(int));
	
return (void*)o;
}

void add_rec(int *d,int *a,int *b,int n){
	int i,k;
	for(i=0,k=0;i<n;i++)
	{
	k=a[i]+b[i]+k;d[i]=k%100000000;
	k=k/100000000;
	}
	if(k)d[n]+=k;
}

void *dbl_intal(void *a){
	verylong *d,*o;int i,k,n;d=(verylong*)a;
	n=d->n;
	if(d->d[n-1]<50000000)
	{
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*n);
	o->n=n;
	for(i=0,k=0;i<n;i++)
	{
	k=2*d->d[i]+k;
	o->d[i]=k%100000000;
	k=k/100000000;
	}
	return (void*)o;
	}
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*(n+1));
	o->n=n+1;
	for(i=0,k=0;i<n;i++)
	{
	k=2*d->d[i]+k;
	o->d[i]=k%100000000;
	k=k/100000000;
	}
	o->d[n]=k;
	return (void*)o;
}

void *hlf_intal(void *a){
	verylong *d,*o;int i,k,n;d=(verylong*)a;
	n=d->n;
	if(d->d[n-1]==1)
	{
	if(n==1)
	{
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int));
	o->n=1;
	o->d[0]=0;
	return (void*)o;
	}
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*(n-1));
	o->n=n-1;
	k=50000000;
	for(i=n-2;i>=0;i--)
	{
	k=k+(d->d[i])/2;
	o->d[i]=k;
	k=(d->d[i]%2)*50000000;
	}
	return (void*)o;
	}
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*n);
	o->n=n;
	k=0;
	for(i=n-1;i>=0;i--)
	{
	k=k+(d->d[i])/2;
	o->d[i]=k;
	k=(d->d[i]%2)*50000000;
	}
	return (void*)o;
}

static void sub_rec(int *a,int *b,int n){
	int i,k;a[n]--;
	for(i=0,k=1;i<n;i++){k=a[i]+99999999-b[i]+k;a[i]=k%100000000;k=k/100000000;}
	if(k)a[n]+=k;
}

int *mul_rec(int *a,int *b,int n){
	int i,*o,*e,*ac,*bd,*t;
	o=(int*)malloc(sizeof(int)*2*n);
	if(n==1)
	{
	int w,x,y,z;w=a[0]%10000;x=a[0]/10000;y=b[0]%10000;z=b[0]/10000;
	o[0]=w*y;
	o[1]=x*z;
	i=(w+x)*(y+z)-o[0]-o[1];
	o[0]+=10000*(i%10000);
	o[1]+=o[0]/100000000+i/10000;
	o[0]=o[0]%100000000;
	return o;
	}
	e=(int*)malloc(sizeof(int)*2*n);
	for(i=0;i<2*n;i++)
		e[i]=o[i]=0;
	add_rec(e,a,a+n/2,n/2);
	add_rec(e+n,b,b+n/2,n/2);
	bd=mul_rec(a,b,n/2);
	ac=mul_rec(a+n/2,b+n/2,n/2);
	if(e[n/2]||e[3*n/2])
	{
	t=mul_rec(e,e+n,n);
	for(i=0;i<3*n/2;i++)
		o[i+n/2]=t[i];
	}
	else 
	{
	t=mul_rec(e,e+n,n/2);
	for(i=0;i<n;i++)
		o[i+n/2]=t[i];
	}
	free((void*)t);
	sub_rec(o+n/2,ac,n);
	sub_rec(o+n/2,bd,n);
	add_rec(o+n,o+n,ac,n);
	add_rec(o,o,bd,n);
	free((void*)e);
	free((void*)ac);
	free((void*)bd);
	return o;
}

void *intal_multiply(void *a,void *b){
	verylong *x,*y,*o;int i,m,n,l,*p,*q,*t;
	if(a==NULL||b==NULL)
	return NULL;
	x=(verylong*)a;
	y=(verylong*)b;
	m=x->n;
	n=y->n;
	l=m>n?m:n;
	l--;
	i=0;
	while(l>>i)
		i++;
	l=1<<i;
	p=(int*)malloc(sizeof(int)*l);
	q=(int*)malloc(sizeof(int)*l);
	for(i=0;i<m;i++)
		p[i]=x->d[i];
	while(i<l)
		p[i++]=0;
	for(i=0;i<n;i++)
		q[i]=y->d[i];
	while(i<l)
		q[i++]=0;
	t=mul_rec(p,q,l);
	i=2*l-1;
	while(t[i]==0&&i>=0)
		i--;
	free((void*)p);
	free((void*)q);
	if(i==-1)
	{
	free((void*)t);
	return intal_create("0");
	}
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*(i+1));
	o->n=i+1;
	while(i>=0)
	{
	o->d[i]=t[i];
	i--;
	}
	free((void*)t);
	return (void*)o;
}

verylong *copy_intal(verylong*d){
	verylong *o;
	int i;
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int)*d->n);
	for(i=0;i<d->n;i++)
		o->d[i]=d->d[i];
	o->n=d->n;
	return o;
}

void *intal_divide(void *a,void *b){
	verylong *x,*y,*o,*t,*r[200];int i;
	if(a==NULL||b==NULL)
		return NULL;
	x=(verylong*)a;
	y=(verylong*)b;
	if(y->n==1&&y->d[0]==0)
		return NULL;
	o=(verylong*)malloc(sizeof(verylong)+sizeof(int));
	o->d[0]=0;o->n=1;
	if(x->n<y->n)
	{
	return (void*)o;
	}
	i=0;t=copy_intal(y);
	while(intal_compare((void*)x,(void*)t)!=-1){
		r[i++]=t;t=dbl_intal((void*)t);
		if(i>=hzn)
			longint(20);
	}
	i--;
	intal_destroy((void*)t);
	if(i==-1)
	return (void*)o;
	
	t=copy_intal(x);
	while(i>=0){
		if(intal_compare((void*)t,(void*)r[i])==-1)
		{
		free((void*)r[i]);
		i--;
		continue;
		}
		y=intal_diff((void*)t,(void*)r[i]);
		free((void*)t);
		free((void*)r[i]);
		t=intal_add((void*)o,(void*)hz[i]);
		free((void*)o);
		o=t;
		t=y;
		i--;
		}
		free((void*)t);
	return (void*)o;
}

void *intal_pow(void *a,void *b){
	verylong *x,*y,*m,*n;
	//return NULL;
	if(a==NULL||b==NULL)
	return NULL;
	x=(verylong*)a;
	y=(verylong*)b;
	if(y->n==1)
	{
	if(y->d[0]==0)
	return intal_create("1");
	if(y->d[0]==1)
	return (void*)copy_intal(x);
	}
	m=hlf_intal(y);
	n=intal_pow(a,(void*)m);
	intal_destroy((void*)m);m=(verylong*)intal_multiply((void*)n,(void*)n);
	intal_destroy((void*)n);
	n=m;
	if(y->d[0]%2)
	{
	n=(verylong*)intal_multiply((void*)m,(void*)x);
	intal_destroy((void*)m);
	m=n;
	}
	return (void*)m;
}

void intal_destroy(void *a){

if(a==NULL)
 return;			

free(a);
}

void longint(int l){
	verylong *a;int i;
	
	if(hz==NULL)
	 {
	hz=(verylong**)malloc(sizeof(verylong*)*l);
	a=(verylong*)intal_create("1");
	i=0;
	}
	
	else 
	{
	hz=(verylong**)realloc((void*)hz,sizeof(verylong*)*(hzn+l));
	a=dbl_intal(hz[hzn-1]);
	i=hzn;
	}
	
	hzn+=l;
	
	while(i<hzn)
	{
	hz[i++]=a;
	a=dbl_intal((void*)a);
	}
	free((void*)a);
}

