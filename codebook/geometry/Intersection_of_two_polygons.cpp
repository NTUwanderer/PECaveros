double area(Pt* ps,int n){  
    ps[n]=ps[0];  
    double res=0;  
    for(int i=0;i<n;i++){  
        res+=ps[i].x*ps[i+1].y-ps[i].y*ps[i+1].x;  
    }  
    return res/2.0;  
}  
int lineCross(Pt a,Pt b,Pt c,Pt d,Pt&p){  
    double s1,s2;  
    s1=cross(a,b,c);  
    s2=cross(a,b,d);  
    if(sig(s1)==0&&sig(s2)==0) return 2;  
    if(sig(s2-s1)==0) return 0;  
    p.x=(c.x*s2-d.x*s1)/(s2-s1);  
    p.y=(c.y*s2-d.y*s1)/(s2-s1);  
    return 1;  
}  
void polygon_cut(Pt*p,int&n,Pt a,Pt b){  
    static Pt pp[maxn];  
    int m=0;p[n]=p[0];  
    for(int i=0;i<n;i++){  
        if(sig(cross(a,b,p[i]))>0) pp[m++]=p[i];  
        if(sig(cross(a,b,p[i]))!=sig(cross(a,b,p[i+1])))  
            lineCross(a,b,p[i],p[i+1],pp[m++]);  
    }  
    n=0;  
    for(int i=0;i<m;i++)  
        if(!i||!(pp[i]==pp[i-1]))  
            p[n++]=pp[i];  
    while(n>1&&p[n-1]==p[0])n--;  
}
double intersectArea(Pt a,Pt b,Pt c,Pt d){  
    Pt o(0,0);  
    int s1=sig(cross(o,a,b));  
    int s2=sig(cross(o,c,d));  
    if(s1==0||s2==0)return 0.0;
    if(s1==-1) swap(a,b);  
    if(s2==-1) swap(c,d);  
    Pt p[10]={o,a,b};  
    int n=3;  
    polygon_cut(p,n,o,c);  
    polygon_cut(p,n,c,d);  
    polygon_cut(p,n,d,o);  
    double res=fabs(area(p,n));  
    if(s1*s2==-1) res=-res;return res;  
}  
