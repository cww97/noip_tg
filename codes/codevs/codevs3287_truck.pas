{
作者:CWW970329
题目:p3287 货车运输
}
program cx;
uses math;
var i,m,n,sa,tg,treenum,cnt,qq,t:longint;
    home,ax,ay,aw,gym,head,next,e,w,h:array[0..100000]of longint;
    q:array[0..1000000]of longint;
    v:array[0..100000]of boolean;
    f,g:array[0..10000,0..20]of longint;

function find(x:longint):longint;
begin
  if home[x]=x then exit(x);
  home[x]:=find(home[x]);
  exit(home[x]);
end;

procedure link(x,y,z:longint);
begin
  inc(cnt); e[cnt]:=y; w[cnt]:=z;
  next[cnt]:=head[x]; head[x]:=cnt;
end;

procedure sort(l,r: longint);
var i,j,x,y: longint;
begin
  i:=l; j:=r;
  x:=aw[(l+r) >>1];
  repeat
    while aw[i]<x do inc(i);
    while x<aw[j] do dec(j);
    if not(i>j) then
      begin
        y:=aw[i]; aw[i]:=aw[j]; aw[j]:=y;
        y:=ax[i]; ax[i]:=ax[j]; ax[j]:=y;
        y:=ay[i]; ay[i]:=ay[j]; ay[j]:=y;
        inc(i); j:=j-1;
      end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;

procedure kruskal;
var i,tot:longint;
begin
  fillchar(v,sizeof(v),0);
  for i:=1 to n do
    if not v[find(i)] then
      begin inc(treenum); v[find(i)]:=true; end;
  for i:=1 to n do home[i]:=i;
  sort(1,m);
  tot:=0;
  for i:=m downto 1 do
    begin
      if find(ax[i])=find(ay[i]) then continue;
      home[find(ax[i])]:=find(ay[i]);
      link(ax[i],ay[i],aw[i]);
      link(ay[i],ax[i],aw[i]);
      inc(tot);
      if tot=n-treenum then break;
    end;
end;

procedure dfs(x:longint);
var i,t:longint;
begin
  v[x]:=true;
  for i:=1 to 17 do
    begin
      if h[x]<(1<<i) then break;
      f[x,i]:=f[f[x,i-1],i-1];
      g[x,i]:=min(g[x,i-1],g[f[x,i-1],i-1]);
    end;
  t:=head[x];
  while t>0 do
    begin
      if not v[e[t]] then
        begin
          f[e[t],0]:=x;
          g[e[t],0]:=w[t];
          h[e[t]]:=h[x]+1;
          dfs(e[t]);
        end;
      t:=next[t];
    end;
end;

function lca(x,y:longint):longint;
var i,t:longint;
begin
  if h[x]<h[y] then begin t:=x; x:=y; y:=t; end;
  t:=h[x]-h[y];
  for i:=0 to 17 do
    if not (((1<<i) and t)=0) then
      x:=f[x,i];
  if x=y then exit(x);
  for i:=17 downto 0 do
    if f[x,i]<>f[y,i] then
      begin x:=f[x,i]; y:=f[y,i]; end;
  if x=y then exit(x);
  exit(f[x,0]);
end;

function ask(x,y:longint):longint;
var i,hk,t:longint;
begin
  hk:=maxlongint;
  t:=h[x]-h[y];
  for i:=0 to 17 do
    if not ((1<<i)and t=0) then
      begin
        hk:=min(hk,g[x,i]);
        x:=f[x,i];
      end;
  exit(hk);
end;

begin
  read(n,m);
  for i:=1 to n do home[i]:=i;
  for i:=1 to m do
    begin
      read(ax[i],ay[i],aw[i]);
      home[find(ax[i])]:=find(ay[i]);
    end;
  kruskal;

  fillchar(v,sizeof(v),0);
  for i:=1 to n do
    if not v[i] then dfs(i);
  read(qq);
  for i:=1 to qq do
    begin
      read(sa,tg);
      if find(sa)<>find(tg) then writeln(-1)
        else begin
               t:=lca(sa,tg);
               writeln(min(ask(sa,t),ask(tg,t)));
             end;
    end;
end.