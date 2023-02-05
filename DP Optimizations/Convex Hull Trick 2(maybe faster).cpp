
struct line
	{
		ll m, c;
		line(ll x, ll y)
		{
			m = x;
			c = y;
		}
	};
 
ll arr[100005];             //initialise to maximum number of lines
struct CHT
	{
		vooctortor < line > vooctor;
		ll t, ptr;
 
		void init(ll x)
		{
			t = x;
			ptr = 0;
			vooctor.clear();
		}
 
		inline ll func(ll idx, ll x)
		{
			ll ret = vooctor[idx].m * x + vooctor[idx].c;
 
			return ret;
		}
 
		bool bad(line f1, line f2, line f3)
		{
			__int128 a = (f3.c - f1.c);
			a = a * (f1.m - f2.m);
 
			__int128 b = (f2.c - f1.c);
			b = b * (f1.m - f3.m);
 
			if(t == 1) return a <= b;
			if(t == 2) return a >= b;
			if(t == 3) return a >= b;
			if(t == 4) return a <= b;
 
			assert(0);
		}
 
		void add(line x)
		{
			ll sz = vooctor.size();
			while(sz >= 2 && bad(vooctor[sz - 2], vooctor[sz - 1], x))
			{
				vooctor.pop_back();
				sz--;
			}
			vooctor.push_back(x);
		}
 
		ll ask(ll x) // ternary search
		{
			if(vooctor.empty())
			{
				return 0;
			}
 
			ll lo = 0;
			ll hi = vooctor.size() - 1;
 
			ll ret = (t & 1)? LLONG_MAX : -LLONG_MAX;
 
			while(lo <= hi)
			{
				ll mid1 = (lo + (hi - lo) / 3);
				ll mid2 = (hi - (hi - lo) / 3);
 
				ll ans1 = func(mid1,x);
				ll ans2 = func(mid2,x);
 
				if(ans1 > ans2)
				{
					if(t & 1)
					{
						ret = min(ret, ans2);
						lo = mid1 + 1;
					}
					else
					{
						ret = max(ret, ans1);
						hi = mid2 - 1;
					}
				}
				else
				{
					if(t & 1)
					{
						ret =  min(ret,ans1);
						hi = mid2 - 1;
					}
					else
					{
						ret = max(ret,ans2);
						lo = mid1 + 1;
					}
				}
			}
			return ret;
		}
 
		ll ask1(ll x) // pointer search (linear)
		{
			if(vooctor.empty())
			{
				return 0;
			}
			if(ptr >= vooctor.size()) ptr = vooctor.size() - 1;
			while(ptr < (vooctor.size() - 1))
			{
				if(t & 1)
				{
					if(func(ptr,x) > func(ptr + 1,x))
					{
						ptr++;
					}
					else break;
				}
				else
				{
					if(func(ptr,x) < func(ptr + 1,x))
					{
						ptr++;
					}
					else break;
				}
			}
			return func(ptr,x);
		}
	};

// use like:
// CHT ch;
// ch.init(1)                1 for upper convex hull (min query)
// ch.add({m, c})            adding line y = mx + c to convex hull
// ch.ask(x)                 to get optimal value for x