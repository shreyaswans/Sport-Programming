// used to generate smallest prime factor of every number from 1 to "last", with this vector in hand
// you can factorise all numbers including large primes in O(log n), only disavantage is that "last" <= 1e7 
// must hold 

ll last = 1e7 + 10;
vec mprim(last + 1, 0);
	mprim[1] = 1;
	for(int i = 2; i <= last; i ++)
		if(mprim[i] == 0)
			for(int j = i; j <= last; j += i)
				if(mprim[j] == 0)	
					mprim[j] = i;
