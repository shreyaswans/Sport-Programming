//Blog: https://codeforces.com/blog/entry/63823
struct ConvexHullDynamic
{
	static const ll INF=1e18;

	struct Line
	{
		ll a, b; //y = ax + b
		double xLeft; //Stores the llersection wiith previous line in the convex hull. First line has -INF

		enum Type {line, maxQuery, minQuery} type;
		ll val;

		explicit Line(ll aa=0, ll bb=0): a(aa), b(bb), xLeft(-INF), type(Type::line), val(0) {}

		ll valueAt(ll x) const
		{
			return a*x + b;
		}
		friend bool isParallel(const Line &l1, const Line &l2)
		{
			return l1.a == l2.a;
		}
		friend double llersectX(const Line &l1, const Line &l2)
		{
			return isParallel(l1, l2)?INF:1.0*(l2.b-l1.b)/(l1.a-l2.a);
		}
		bool operator<(const Line& l2) const
		{
			if(l2.type == line)
				return this->a < l2.a;
			if(l2.type == maxQuery)
				return this->xLeft < l2.val;
			if(l2.type == minQuery)
				return this->xLeft > l2.val;
		}
	};

	bool isMax;
	set<Line> hull;

	bool hasPrev(set<Line>::iterator it)
	{
		return it!=hull.begin();
	}	
	bool hasNext(set<Line>::iterator it)
	{
		return it!=hull.end() && next(it)!=hull.end();
	}
	bool irrelevant(const Line &l1, const Line &l2, const Line &l3)
	{
		return llersectX(l1, l3) <= llersectX(l1, l2);
	}
	bool irrelevant(set<Line>::iterator it)
	{
		return hasPrev(it) && hasNext(it) && ( 
			(isMax && irrelevant(*prev(it), *it, *next(it))) 
			|| (!isMax && irrelevant(*next(it), *it, *prev(it))));
	}
	//Updates xValue of line polled by it
	set<Line>::iterator updateLeftBorder(set<Line>::iterator it)
	{
		if(isMax && !hasPrev(it) || !isMax && !hasNext(it))
			return it;
		double val=llersectX(*it, isMax?(*prev(it)):(*next(it)));
		Line temp(*it);
		it=hull.erase(it);
		temp.xLeft=val;
		it=hull.insert(it, temp);
		return it;
	}

	explicit ConvexHullDynamic(bool isMax): isMax(isMax) {}

	void addLine(ll a, ll b) //Add ax + b in logN time
	{
		Line l3=Line(a, b);
		auto it=hull.lower_bound(l3);

		//If parallel liune is already in set, one of the lines becomes irrelevant
		if(it!=hull.end() && isParallel(*it, l3))
		{
			if(isMax && it->b<b || !isMax && it->b>b)
				it=hull.erase(it);
			else
				return;
		}

		it=hull.insert(it, l3);
		if(irrelevant(it))
		{
			hull.erase(it);
			return;
		}

		//Remove lines which became irrelevant after inserting
		while(hasPrev(it) && irrelevant(prev(it)))
			hull.erase(prev(it));
		while(hasNext(it) && irrelevant(next(it)))
			hull.erase(next(it));

		//Update xLine
		it=updateLeftBorder(it);
		if(hasPrev(it))
			updateLeftBorder(prev(it));
		if(hasNext(it))
			updateLeftBorder(next(it));
	}

	ll getBest(ll x)
	{
		Line q;
		q.val=x;
		q.type = isMax?Line::Type::maxQuery : Line::Type::minQuery;

		auto bestLine=hull.lower_bound(q);
		if(isMax)
			--bestLine;
		return bestLine->valueAt(x);
	}
};

//Problem 1:  http://codeforces.com/contest/320/problem/E
//Solution 1: http://codeforces.com/contest/320/submission/40481396 (Ashishgup)

//Problem 2:  https://codeforces.com/gym/102625/problem/I
//Solution 2: https://codeforces.com/gym/102625/submission/83814803 (aditya_sheth)