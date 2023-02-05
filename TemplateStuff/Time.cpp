#include <bits/stdc++.h>

using namespace std;

/// the following three lines are for debugging purposes only
#ifdef ONLINE_JUDGE
#undef ONLINE_JUDGE 
#endif

/// The time_mointor() code starts here
inline void time_monitor( const string& s, const function< void() >& procedure )
{
#ifndef ONLINE_JUDGE
    typedef chrono::high_resolution_clock clock_t;

    auto start_time  = clock_t::now();
#endif // ONLINE_JUDGE

    procedure();

#ifndef ONLINE_JUDGE
    auto duration = clock_t::now() - start_time;

    typedef chrono::milliseconds time_scale;

    auto elapsed_time = chrono::duration_cast< time_scale >( duration ).count();

    cout << "void " << s << "() used " << elapsed_time << " ms\n";
#endif // ONLINE_JUDGE
}

#define time__( procedure ) time_monitor( #procedure, procedure )
/// The code ends here

/// An example 

const int N = 1e7; int a[ N ];

void procedure_1()
{
    cout << "procedure 1" << endl;

    for( int i = 0; i < N; i++ )
    	a[ i ] = i;
}

void procedure_2()
{
    cout << "procedure 2" << endl;

    for( int i = 0; i < N; i++ )
    	a[ i ] = -i;
}

int main()
{
    ios_base::sync_with_stdio( false ), cin.tie( nullptr ), cout.tie( nullptr );

    time__( procedure_1 );

    time__( procedure_2 );
}
