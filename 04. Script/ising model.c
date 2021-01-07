#include<stdio.h>
#include<math.h>

#define N 20 
#define total_spin_number (N * N) 

#define T_init	4.0
#define T_final	0.2
#define T_step -0.2 

#define KB 1.0 
#define Beta(T) (1.0/(KB*T))

#define MCS	1000000 
#define MCS_init 20000	
#define Max_step (MCS )
#define MAX_init_step (MCS_init)

#define R_A		16807
#define R_M		((int)pow(2,31)-1)
#define R_Q		127773
#define R_R		2836
#define RANDOM_MAX	(R_M-1) 	// max Random number 	

/* ���� �ʱ����, ��Ʈ�������� �˰���, ���������, ��ȭ��� ����� ����ϴ� �Լ��� �����Լ� �ܺο� ���� �����

   �����Լ����� �̵��� ������ ���� ������ �ڵ��߽��ϴ�. from ������ */

/* ���� ���� */
int spin[N][N];	 
float	T=T_init;  // �Ʒ��� while������ ������ �����ϸ� for�� ����.		  
long RANDOM_NUMBER = 1;
 
 
 // c������ ������ ���̽�� ���� �޶� ���� ��� �ڵ��Ͽ� ��������ϴ�. 30�� ������ �ǳʶٸ� �����Լ��� �����մϴ�. 
  
/* ���� ����  0~RANDOM_MAX */ 
long make_random_number(void)
{
	long U, V;
	U = RANDOM_NUMBER/R_Q;
	V = RANDOM_NUMBER%R_Q;
	RANDOM_NUMBER=R_A*V - R_R*U;
	if(RANDOM_NUMBER<0) RANDOM_NUMBER = RANDOM_NUMBER + R_M;
	return (RANDOM_NUMBER);
}


float random_unit_real_number(void)  /* 0�� 1������ �Ǽ��� ���� ���� */
{
	return ((float)make_random_number()/RANDOM_MAX);
}


int random_inteager_number(int imin, int imax)  /* imin �� imax ������  ������ ���� ���� */
{
	return ((int)((float)make_random_number()/(RANDOM_MAX+1.)*(imax-imin+1))+imin);
} 

void set_random_number_seed(long seed)
{
	RANDOM_NUMBER=seed;
}


// ���⼭���Ͱ� ������.... 

/* ���� �ʱ���� */
void initial_spin_state(void)
{
	int x, y;
	for(x=0; x<N; x++)
		for(y=0; y<N; y++)
			spin[x][y]=random_inteager_number(0,1)*2 -1 ;
}



/* ��Ʈ�������� �˰����� �̿��� ������Ʈ */
void metropolis_update(void)
{
	int x, y , x_left, x_right, y_up, y_down;
	float dE, A, P;
	
	// ������ ������ �����Ѵ�. 
	x =  random_inteager_number(0,N-1);
	y =  random_inteager_number(0,N-1);
	
	// ���� ����� �̿� ��ġ 
	x_left = x-1;
	x_right = x+1;
	y_up = y+ 1 ;
	y_down = y-1 ;

	// ������� 
	if(x==0){ x_left = N-1;}
	if(x==(N-1)) x_right = 0;
	if(y==0) y_up=N-1;
	if(y==(N-1)) y_down=0;

	//dE
	dE = 2*spin[x][y]*(spin[x_left][y]+spin[x_right][y]+spin[x][y_up]+spin[x][y_down]);
	
	/* ��Ʈ�������� �˰����� �̿��� ������Ʈ  */
	A = exp(-1 * Beta(T) * dE);
	if(A>=1)
	{
		spin[x][y] = -1*spin[x][y];
		
	} 
	else
	{
		P = random_unit_real_number();
		if(A>=P)
		{
			spin[x][y]= -1*spin[x][y];
			
		}
	}
}

// ������ ���  
float cal_energy(void)
{
	float energy =0.;
	int x, y, x_right, y_down;
	for(x=0; x<N; x++)
	{
		for(y=0; y<N; y++)
		{
			x_right = x + 1;
			y_down = y + 1;
			if(x==(N-1))  x_right = 0;
			if(y==(N-1))  y_down = 0;
			energy = energy - spin[x][y] * ( spin[x][y_down] + spin[x_right][y] );
		}
    }
	return energy;
}

// ��ȭ�е� ��� 
float cal_magnetization(void)
{
	float mag = 0.;  
	int x, y;
	for(x=0; x<N; x++)
	{
		for(y=0; y<N; y++)
		{
			mag += spin[x][y];  // ���� ��� ���ϸ� ��ȭ�е�		
		}
    }
	return mag;
}


void main()
{
	int i;
	int x,y;
	double energy, energy2, energy_per_spin, E, energy_average2, energy2_average;
	double magnetization, magnetization2, magnetization_per_spin, M, mag2_average, mag_average2;
	double specific_heat, specific_heat_per_spin;
	double susceptability, susceptability_per_spin;

	set_random_number_seed(2);
	initial_spin_state();

	printf("# %d x %d Ising model \n",N,N);
	printf("From %4.1fK to %4.1fK, Step : %4.1fk) \n",T_init, T_final,T_step);
	printf("# Metropolis step : %d\n", MCS);
	
	while(T>=T_final)
	{
		energy = energy2 = 0;
		magnetization = magnetization2 = 0;
		specific_heat = 0;
		susceptability = 0;
		energy_average2 = energy2_average = 0;
		mag_average2 = mag2_average = 0;

		/*until MAX_init_step just update*/
		for(i=0; i<MAX_init_step ;i++)
			metropolis_update();

		
		/* after MCS_init step*/
		for(i=0; i<Max_step; i++)
		{
			metropolis_update();
			
			E = cal_energy();
			energy = energy + E;
			energy2 = energy2 + E*E;
			
			M = cal_magnetization();
			magnetization = magnetization + M;
			magnetization2 = magnetization + M*M;

		} 

		
		energy = energy/ Max_step;
		energy_per_spin = energy / total_spin_number;
		
		energy_average2 = energy * energy;
		energy2_average = energy2 / Max_step;
		
		specific_heat = KB * Beta(T) * Beta(T)*(energy2_average-energy_average2);
		specific_heat_per_spin = specific_heat / total_spin_number;
		
		
		
		
		magnetization = magnetization / Max_step;
		magnetization_per_spin = magnetization / total_spin_number;
		
		mag_average2 = magnetizaton * magnetization;
		mag2_average = magnetization2 / Max_step;
		
		susceptability = KB * Beta(T) * Beta(T)*(mag2_average-mag_average2);
		susceptability_per_spin = susceptability / total_spin_number;
		
		/*
		int x, y;
		for(x=0;x<N;x++){
			for(y=0;y<N;y++){
				if(spin[x][y]==-1){
				printf("0  ");	
				continue;}
				printf("%d  ",spin[x][y]);		
			}
			printf("\n");
		}
		*/
	
		printf("T : %.1f E : %f C : %f  M : %f X : %f\n", T, energy, specific_heat_per_spin, magnetization_per_spin, susceptability_per_spin);
		T += T_step;
     }
     
}



