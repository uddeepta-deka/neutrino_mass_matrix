//This program finds the neutrino mass matrix elements

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>

float pi=4.0*atan(1.0); //Defining pi

/**Function that generates random number between 0 and 1 (uniform distribution) and stores them in 3 arrays
Parameters:
n: number of uniformly distributed random numbers required
x[n]: array which stores the generated random numbers
**/
void rand_zero_one(int n,double x1[n],double x2[n],double x3[n], double x4[n], double x5[n])
{
	srand(time(0));
	double r;
	for(int i=0;i<(5*n);i++)
	{
		r=((double)rand()/(RAND_MAX));
		if(i<n)			
			x1[i]=r;
		else if ((i>=n)&&(i<(2*n)))
			x2[i-n]=r;
		else if (i>=(2*n)&&(i<(3*n)))			
			x3[i-(2*n)]=r;
		else if (i>=(3*n)&&(i<(4*n)))			
			x4[i-(3*n)]=r;
		else if (i>=(4*n)&&(i<(5*n)))			
			x5[i-(4*n)]=r;
	}
}


/**Function that generates floating random numbers in a given range and stores them in an array
Parameters:
max: maximum value of the random number to be generated
min: minimum value of the random number to be generated
n: number of random numbers required
x[n]: array which stores the generated random numbers
**/
void randInRange(double max1, double max2, double max3, double max4, double min1, double min2, double min3, double min4, int n, double x1[n], double x2[n], double x3[n], double x4[n])
{
	srand((unsigned int)time(NULL));
	double a,b,c,d,r;
	a=max1-min1;
	b=max2-min2;
	c=max3-min3;
	d=max4-min4;
	for(int i=0;i<(4*n);i++)
	{
		if(i<n)
		{
			r=min1+((double)rand()/(double)(RAND_MAX))*a;
			x1[i]=r;
		}
		else if((i>=n)&&(i<(2*n)))
		{
			r=min2+((double)rand()/(double)(RAND_MAX))*b;
			x2[i-n]=r;
		}
		else if((i>=(2*n))&&(i<(3*n)))
		{
			r=min3+((double)rand()/(double)(RAND_MAX))*c;
			x3[i-(2*n)]=r;
		}
		else if((i>=(3*n))&&(i<(4*n)))
		{
			r=min4+((double)rand()/(double)(RAND_MAX))*d;
			x4[i-(3*n)]=r;
		}
	}
}


/**Function that generates random numbers from gaussian distribution
Parameters:
mu: mean of the distribution
sig: standard deviation of the distribution
n: no. of random numbers to be generated
x[n]: array that will store the random numbers between 0 and 1
PD[n-1]: array that will store the generated gaussian random numbers
**/
void gaussRan(double mu,double sig,int n,double x[n],double PD[n-1])
{
	double p[10000];
	int i;
	for(i=0;i<(n-1);i++)
	{	
		p[i]=(double)((sin(2.0*pi*x[i]))*sqrt(-2.0*log(x[i+1])));
		PD[i]=(double)(mu+sig*p[i]);
	}
}


//Main function
void main()
{
	int i, j, nruns=10000; //parameters for random number generation
	double rmee,rmeu,rmet,rmuu,rmut,rmtt,imee,imeu,imet,imuu,imut,imtt; //declaration of matrix elements
	double t12[10000],t13[10000],t23[10000]; 
	double m1[10000], m2[10000], m3[10000], delM21[10000], delM32[10000];
	double alpha[10000], beta[10000], delta[10000];
	double temp1[10000], temp2[10000], temp3[10000], temp4[10000], temp5[10000];
	double mu12=0.307, mu13=0.0212, mu23=0.417, sig12=0.013, sig13=0.0008, sig23=0.02333, muDelM32=0.00251, sigDelM32=0.00004545, muDelM21=0.0000753, sigDelM21=0.0000018; 
	double st12[10000],st13[10000],st23[10000];
	double p,q;

	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	FILE *fp3 = NULL;
	FILE *fp4 = NULL;
	FILE *fp5 = NULL;
	FILE *fp6 = NULL;
	//files that will store the real values of neutrino mass matrix elements
	fp1 = fopen("rM11.txt","w");
	fp2 = fopen("rM12.txt","w");
	fp3 = fopen("rM13.txt","w");
	fp4 = fopen("rM22.txt","w");
	fp5 = fopen("rM23.txt","w");
	fp6 = fopen("rM33.txt","w");

	FILE *fp7 = NULL;
	FILE *fp8 = NULL;
	FILE *fp9 = NULL;
	FILE *fp10 = NULL;
	FILE *fp11 = NULL;
	FILE *fp12 = NULL;
	//files that will store the imaginary values of neutrino mass matrix elements
	fp7  = fopen("iM11.txt","w");
	fp8  = fopen("iM12.txt","w");
	fp9  = fopen("iM13.txt","w");
	fp10 = fopen("iM22.txt","w");
	fp11 = fopen("iM23.txt","w");
	fp12 = fopen("iM33.txt","w");
	
	FILE *ex1 = NULL;
	FILE *ex2 = NULL;
	FILE *ex3 = NULL;
	FILE *ex4 = NULL;
	FILE *ex5 = NULL;
	FILE *ex6 = NULL;
	FILE *ex7 = NULL;
	FILE *ex8 = NULL;
	FILE *ex9 = NULL;
	ex1 = fopen("m1.txt","w");
	ex2 = fopen("m2.txt","w");
	ex3 = fopen("m3.txt","w");
	ex4 = fopen("t12.txt","w");
	ex5 = fopen("t13.txt","w");
	ex6 = fopen("t23.txt","w");
	ex7 = fopen("alpha.txt","w");
	ex8 = fopen("beta.txt","w");
	ex9 = fopen("delta.txt","w");	
	FILE *ex10 = NULL;
	FILE *ex11 = NULL;
	FILE *ex12 = NULL;
	ex10 = fopen("st12.txt","w");
	ex11 = fopen("st13.txt","w");
	ex12 = fopen("st23.txt","w");

	//generating uniform random numbers for the CP violating phases and m1
	randInRange(2.0*pi, pi, pi, 0.1, 0.0, 0.0, 0.0, 0.00001, nruns, delta, alpha, beta, m1);
	
	//generating uniform random numbers 
	rand_zero_one(nruns, temp1, temp2, temp3, temp4, temp5);

	//generating gaussian random numbers for the angles t12,t13,t23
	gaussRan(mu12,sig12,nruns,temp1,st12);
	gaussRan(mu13,sig13,nruns,temp2,st13);
	gaussRan(mu23,sig23,nruns,temp3,st23);
	for(j=0;j<nruns-1;j++)
	{
		//t12[j]=(sqrt(abs(st12[j])));
		//t13[j]=(sqrt(abs(st13[j])));
		//t23[j]=(sqrt(abs(st23[j])));
		t12[j]=asin(sqrt(st12[j]));
		t13[j]=asin(sqrt(st13[j]));
		t23[j]=asin(sqrt(st23[j]));
	}

	//generating gaussian random numbers for delM21 and delM32
	gaussRan(muDelM21,sigDelM21,nruns,temp4,delM21);
	gaussRan(muDelM32,sigDelM32,nruns,temp5,delM32);
	for(i=0;i<nruns-1;i++)
	{
		p = delM21[i]+pow(m1[i],2);
		m2[i] = sqrt(p);
		q = delM32[i]+pow(m2[i],2);
		m3[i] = sqrt(q);
	}


	//To calculate the values of the matrix elements and store them in respective .txt files
	for(i=0;i<nruns-1;i++)
	{
		rmee = pow(cos(t13[i]),2)*pow(cos(t12[i]),2)*m1[i] + pow(cos(t13[i]),2)*pow(sin(t12[i]),2)*m2[i]*cos(2.0*alpha[i])+pow(sin(t13[i]),2)*m3[i]*cos(2.0*beta[i]);
		imee = pow(cos(t13[i]),2)*pow(sin(t12[i]),2)*m2[i]*sin(2.0*alpha[i])+pow(sin(t13[i]),2)*m3[i]*sin(2.0*beta[i]);

		rmeu = cos(t13[i])*(sin(t13[i])*sin(t23[i])*((cos(delta[i]+2.0*beta[i])*m3[i])-(pow(sin(t12[i]),2)*m2[i]*cos(delta[i]+2.0*alpha[i])))-cos(t12[i])*cos(t23[i])*sin(t12[i])*(m1[i]-m2[i]*cos(2.0*alpha[i]))-pow(cos(t12[i]),2)*sin(t13[i])*sin(t23[i])*m1[i]*cos(delta[i]));
		imeu = cos(t13[i])*(sin(t13[i])*sin(t23[i])*((sin(delta[i]+2.0*beta[i])*m3[i])-(pow(sin(t12[i]),2)*m2[i]*sin(delta[i]+2.0*alpha[i])))+cos(t12[i])*cos(t23[i])*sin(t12[i])*m2[i]*sin(2.0*alpha[i])-pow(cos(t12[i]),2)*sin(t13[i])*sin(t23[i])*m1[i]*sin(delta[i]));
	
		rmet = cos(t13[i])*(sin(t13[i])*sin(t23[i])*((cos(delta[i]+2.0*beta[i])*m3[i])-(pow(sin(t12[i]),2)*m2[i]*cos(delta[i]+2.0*alpha[i])))+cos(t12[i])*sin(t23[i])*sin(t12[i])*(m1[i]-m2[i]*cos(2.0*alpha[i]))-pow(cos(t12[i]),2)*sin(t13[i])*cos(t23[i])*m1[i]*cos(delta[i]));
		imet = cos(t13[i])*(sin(t13[i])*sin(t23[i])*((sin(delta[i]+2.0*beta[i])*m3[i])-(pow(sin(t12[i]),2)*m2[i]*sin(delta[i]+2.0*alpha[i])))-cos(t12[i])*sin(t23[i])*sin(t12[i])*m2[i]*sin(2.0*alpha[i])-pow(cos(t12[i]),2)*sin(t13[i])*cos(t23[i])*m1[i]*sin(delta[i]));
	
		rmuu = m1[i]*((pow(sin(t12[i]),2)*pow(cos(t23[i]),2))+(pow(cos(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*cos(2.0*delta[i]))+(2.0*sin(t12[i])*sin(t13[i])*sin(t23[i])*cos(t12[i])*cos(t23[i])*cos(delta[i])))+m2[i]*((cos(2*alpha[i])*pow(cos(t12[i]),2)*pow(cos(t23[i]),2))+(cos(2*alpha[i])*pow(sin(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*cos(2.0*delta[i]))-(sin(2*alpha[i])*pow(sin(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*sin(2.0*delta[i]))-(2.0*cos(2.0*alpha[i])*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t23[i])*sin(t13[i])*cos(delta[i]))+(2.0*sin(2.0*alpha[i])*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t23[i])*sin(t13[i])*sin(delta[i])))+m3[i]*cos(2.0*(beta[i]+delta[i]))*pow(sin(t23[i]),2)*pow(cos(t13[i]),2);
		imuu = m1[i]*((pow(cos(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*sin(2.0*delta[i]))+(2.0*sin(t12[i])*sin(t13[i])*sin(t23[i])*cos(t12[i])*cos(t23[i])*sin(delta[i])))+m2[i]*((sin(2*alpha[i])*pow(cos(t12[i]),2)*pow(cos(t23[i]),2))+(cos(2*alpha[i])*pow(sin(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*sin(2.0*delta[i]))+(sin(2*alpha[i])*pow(sin(t12[i]),2)*pow(sin(t23[i]),2)*pow(sin(t13[i]),2)*cos(2.0*delta[i]))-(2.0*cos(2.0*alpha[i])*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t23[i])*sin(t13[i])*sin(delta[i]))-(2.0*sin(2.0*alpha[i])*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t23[i])*sin(t13[i])*cos(delta[i])))+m3[i]*sin(2.0*(beta[i]+delta[i]))*pow(sin(t23[i]),2)*pow(cos(t13[i]),2);
	
		rmut = -m1[i]*((pow(sin(t12[i]),2)*sin(t23[i])*cos(t23[i]))+(cos(delta[i])*sin(t12[i])*sin(t13[i])*cos(t12[i])*(pow(sin(t23[i]),2)-pow(cos(t23[i]),2)))-(pow(cos(t12[i]),2)*pow(sin(t13[i]),2)*sin(t23[i])*cos(t23[i])*cos(2.0*delta[i])))-m2[i]*((pow(cos(t12[i]),2)*sin(t23[i])*cos(t23[i])*cos(2.0*alpha[i]))+(cos((2.0*alpha[i])+delta[i])*cos(t12[i])*sin(t12[i])*sin(t13[i])*(pow(cos(t23[i]),2)-pow(sin(t23[i]),2)))-(pow(sin(t12[i]),2)*pow(sin(t13[i]),2)*sin(t23[i])*cos(t23[i])*cos(2.0*(alpha[i]+delta[i]))))+m3[i]*sin(t23[i])*cos(t23[i])*pow(cos(t13[i]),2)*cos(2.0*(beta[i]+delta[i]));
		imut = -m1[i]*((sin(delta[i])*sin(t12[i])*sin(t13[i])*cos(t12[i])*(pow(sin(t23[i]),2)-pow(cos(t23[i]),2)))-(pow(cos(t12[i]),2)*pow(sin(t13[i]),2)*sin(t23[i])*cos(t23[i])*sin(2.0*delta[i])))-m2[i]*((pow(cos(t12[i]),2)*sin(t23[i])*cos(t23[i])*sin(2.0*alpha[i]))+(sin((2.0*alpha[i])+delta[i])*cos(t12[i])*sin(t12[i])*sin(t13[i])*(pow(cos(t23[i]),2)-pow(sin(t23[i]),2)))-(pow(sin(t12[i]),2)*pow(sin(t13[i]),2)*sin(t23[i])*cos(t23[i])*sin(2.0*(alpha[i]+delta[i]))))+m3[i]*sin(t23[i])*cos(t23[i])*pow(cos(t13[i]),2)*sin(2.0*(beta[i]+delta[i]));
	
		rmtt = m1[i]*((pow(sin(t12[i]),2)*pow(sin(t23[i]),2))+(pow(sin(t13[i]),2)*pow(cos(t12[i]),2)*pow(cos(t23[i]),2)*cos(2.0*delta[i]))-(2.0*sin(t12[i])*sin(t13[i])*sin(t23[i])*cos(t12[i])*cos(t23[i])*cos(delta[i])))+m2[i]*((pow(cos(t12[i]),2)*pow(sin(t23[i]),2)*cos(2.0*alpha[i]))+(pow(sin(t12[i]),2)*pow(cos(t23[i]),2)*pow(sin(t13[i]),2)*cos(2.0*(alpha[i]+delta[i])))+(2.0*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t13[i])*sin(t23[i])*cos((2.0*alpha[i])+delta[i])))+m3[i]*cos(2.0*(beta[i]+delta[i]))*pow(cos(t13[i]),2)*pow(cos(t23[i]),2);
		imtt = m1[i]*((pow(sin(t13[i]),2)*pow(cos(t12[i]),2)*pow(cos(t23[i]),2)*sin(2.0*delta[i]))-(2.0*sin(t12[i])*sin(t13[i])*sin(t23[i])*cos(t12[i])*cos(t23[i])*sin(delta[i])))+m2[i]*((pow(cos(t12[i]),2)*pow(sin(t23[i]),2)*sin(2.0*alpha[i]))+(pow(sin(t12[i]),2)*pow(cos(t23[i]),2)*pow(sin(t13[i]),2)*sin(2.0*(alpha[i]+delta[i])))+(2.0*cos(t12[i])*cos(t23[i])*sin(t12[i])*sin(t13[i])*sin(t23[i])*sin((2.0*alpha[i])+delta[i])))+m3[i]*sin(2.0*(beta[i]+delta[i]))*pow(cos(t13[i]),2)*pow(cos(t23[i]),2);
		
		fprintf(fp1,"%lf\n",rmee);
		fprintf(fp2,"%lf\n",rmeu);
		fprintf(fp3,"%lf\n",rmet);
		fprintf(fp4,"%lf\n",rmuu);
		fprintf(fp5,"%lf\n",rmut);
		fprintf(fp6,"%lf\n",rmtt);
		fprintf(fp7,"%lf\n",imee);
		fprintf(fp8,"%lf\n",imeu);
		fprintf(fp9,"%lf\n",imet);
		fprintf(fp10,"%lf\n",imuu);
		fprintf(fp11,"%lf\n",imut);
		fprintf(fp12,"%lf\n",imtt);

		fprintf(ex1,"%lf\n",m1[i]);
		fprintf(ex2,"%lf\n",m2[i]);
		fprintf(ex3,"%lf\n",m3[i]);
		fprintf(ex4,"%lf\n",t12[i]);
		fprintf(ex5,"%lf\n",t13[i]);
		fprintf(ex6,"%lf\n",t23[i]);
		fprintf(ex7,"%lf\n",alpha[i]);
		fprintf(ex8,"%lf\n",beta[i]);
		fprintf(ex9,"%lf\n",delta[i]);

		fprintf(ex10,"%lf\n",st12[i]);
		fprintf(ex11,"%lf\n",st13[i]);
		fprintf(ex12,"%lf\n",st23[i]);
	}
	
}