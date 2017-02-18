#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

const int maxLength=11112;
const long long radix=1000000000;


struct longNumber
{
	int number[maxLength];
	int count;
};


bool readLongNumber(longNumber &n)
{
	char str[100001];

	if (scanf("%s", str) != 1) return false;

	int len = strlen(str);

	n.count = (len+8)/9;


	memset(n.number, 0, (maxLength)*sizeof n.number[0]);

	int curChar=0, i;
	long long digit;

	int indexDigit=n.count-1;
	int restDigit = len%9;
	if (restDigit>0)
	{
		digit=0;
		for (i = 0; i < restDigit; ++i)
			digit=digit*10+str[curChar++]-'0'; 
		n.number[indexDigit--]=digit;
	}
	
	while (curChar < len)
	{
		digit=0;
		for (i = 0; i < 9; ++i)
			digit=digit*10+str[curChar++]-'0'; 
		n.number[indexDigit--]=digit;
	}

	return true;
}

bool sumLongNumber(longNumber &a, longNumber &b, longNumber &c)
{
	int i, k = 0, max;

	if (a.count > b.count)
		max = a.count;
	else
		max = b.count;

	memset(c.number, 0, (maxLength)*sizeof c.number[0]);

	for (i = 0; i < max; ++i)
	{
		long long t = a.number[i]+b.number[i]+k;
		c.number[i]=t%radix;
		k=t/radix;
	}

	c.number[max] = k;
	c.count = max;
	if (k!=0)
		++c.count;

	if (c.number[maxLength-1] >9)
		return false;

	return true;
}

bool subLongNumber(longNumber &a, longNumber &b, longNumber &c)
{
	int i, k = 0;

	if (a.count < b.count)
		return false;

	memset(c.number, 0, (maxLength)*sizeof c.number[0]);

	for (i = 0; i < a.count; ++i)
	{
		long long t = a.number[i]-b.number[i]+k+radix;
		c.number[i]=t%radix;
		k=t/radix-1;
	}

	i = a.count-1;
	while (i>=0 && c.number[i] == 0)
		--i;
	c.count = i+1;

	if (k!=0)
		return false;

	return true;
}

int cmpLongNumber(longNumber &a, longNumber &b)
{
	if (a.count > b.count)
		return 1;
	else if (a.count < b.count)
		return -1;
	else 
	{
		int i = a.count-1;
		while (i>=0 && a.number[i] == b.number[i]) 
			--i;
		if (i==-1)
			return 0;
		else if (a.number[i]>b.number[i])
			return 1;
		else 
			return -1;
	}
}

bool mulLongNumber(longNumber &a, longNumber &b, longNumber &c)
{
	int i, j, k;
	if (a.count + b.count - 1 > maxLength)
		return false;

        if (a.count==0 || b.count==0 || (a.count==1 && a.number[0] ==0) || (b.count==1 && b.number[0] ==0))
        {
                c.count=0;
                return true;
        }

        longNumber c2;
	memset(c2.number, 0, (maxLength)*sizeof c2.number[0]);

	for (i = 0; i < a.count; ++i)
	{
		k = 0;
		for (j = 0; j < b.count; ++j)
		{
			long long t = (long long) a.number[i]*b.number[j]+k+c2.number[i+j];
			c2.number[i+j]=t%radix;
			k=t/radix;
		}
		c2.number[i+j] = k;
	}

	c2.count = a.count + b.count-1;
	if (k!=0)
		++c2.count;

	if (c2.number[maxLength-1] > 9)
		return false;

        memcpy(c.number, c2.number, sizeof c.number[0] * (maxLength));
        c.count = c2.count;

	return true;
}

bool divLongNumber(longNumber &a2, longNumber &b2, longNumber &c)
{
	int i, j, k;
	long long t;
	if (b2.count==0 || (b2.count==1 && b2.number[0] == 0))
		return false;

	int d = radix/(b2.number[b2.count-1]+1);


	longNumber a;
	memset(a.number, 0, (maxLength) * sizeof a2.number[0]);
	a.count = a2.count+1;
	k = 0;
	for (i = 0; i < a2.count; ++i)
	{
		t = (long long) a2.number[i]*d+k;
		a.number[i] = t % radix;
		k = t / radix;
	}
	a.number[i] = k;

	longNumber b;
	memset(b.number, 0, (maxLength) * sizeof b2.number[0]);
	b.count = b2.count;
	k = 0;

	memset(c.number, 0, (maxLength)*sizeof c.number[0]);
	c.count = 0;

	for (i = 0; i < b2.count; ++i)
	{
		t = (long long) b2.number[i]*d+k;
		b.number[i] = t % radix;
		k = t / radix;
	}


	int bMax = b.number[b.count-1];

	for (i = a.count-1; i >= b.count-1; --i)
	{
		long long maxDigit = (a.number[i+1] * radix + a.number[i])/bMax;

		if (maxDigit != 0)
		{

      if (maxDigit == 1)
        maxDigit = 0;
      else maxDigit = maxDigit - 2;

			k=0;
			for (j = 0; j < b.count; ++j)
			{
				long long t = a.number[i-b.count+j+1]+(radix-b.number[j])*(long long)maxDigit+k;
				a.number[i-b.count+j+1]=t%radix;
				k=t/radix-maxDigit;
			}
			a.number[i+1] = a.number[i+1]+k;






      while(1)
      {
			  j = b.count;
                        while(j>=0)
                        {
				if (a.number[i-b.count+j+1] != b.number[j])
				{
					break;
				}
                                --j;
                        }

			if ((j>=0 && a.number[i-b.count+j+1] > b.number[j]) || j == -1)
			{
				k = 0;
				for (j = 0; j < b.count; ++j)
				{
					long long t = a.number[i-b.count+j+1]+radix-b.number[j]+k;
					a.number[i-b.count+j+1]=t%radix;
					k=t/radix-1;
				}
				a.number[i+1] = a.number[i+1]+k;

				++maxDigit;

			}
      else
        break;


      }


		}

		c.number[i-b.count+1] = maxDigit;



	}
	c.count = a.count - b.count;
	if (c.number[c.count-1] == 0)
		--c.count;

	return true;
}

bool powLongNumber(longNumber &a, int b, longNumber &c)
{
        if (b == 1)
        {
                memcpy(c.number, a.number, sizeof c.number[0] * (maxLength));
                c.count = a.count;
                return true;
        }

        if (powLongNumber(a, b/2, c) && mulLongNumber(c, c, c) && (b%2==0 || mulLongNumber(a, c, c)))
          return true;
        else
          return false;

}

bool powLongNumber(longNumber &a, longNumber &b, longNumber &c)
{
        memset(c.number, 0, (maxLength)*sizeof c.number[0]);

	if (a.count == 0 || (a.count == 1 && a.number[0]==0))
        {
                if (b.count == 0 || (b.count == 1 && b.number[0]==0))
                        return false;
                else
                {
                    c.count=1;
                    return true;
                }
        }

        if ((a.count == 1 && a.number[0]==1) || b.count == 0 || (b.count == 1 && b.number[0]==0))
        {
                c.count=1;
                c.number[0] = 1;
                return true;
        }


    if (b.count > 1)
      return false;

    return powLongNumber(a, b.number[0], c);

}



void writeLongNumber(longNumber &n)
{

	if (n.count==0)
		printf("0");
        else
        {
          printf("%d", n.number[n.count-1]);
          for (int i = n.count-2; i>=0; --i)
		        printf("%09d", n.number[i]);
        }
	printf("\n");
}


int main()
{
	longNumber a, b, c;
	char op;

        while (1)
        {
                if (!readLongNumber(a)) return 0;
	              if (!readLongNumber(b)) return 0;
                op = ' ';
                scanf("\n%c", &op);
                switch (op)
                {
                        case '+':
                                if (sumLongNumber(a, b, c))
                                        writeLongNumber(c);
                                else
                                        printf("Error\n");
                                break;
                        case '-':
                                if (subLongNumber(a, b, c))
                                        writeLongNumber(c);
                                else
                                        printf("Error\n");
                                break;

                        case '*':
                                if (mulLongNumber(a, b, c))
                                        writeLongNumber(c);
                                else
                                        printf("Error\n");
                                break;

                        case '/':
                                if (divLongNumber(a, b, c))
                                        writeLongNumber(c);
                                else
                                        printf("Error\n");
                                break;
                        case '^':
                                if (powLongNumber(a, b, c))
                                        writeLongNumber(c);
                                else
                                        printf("Error\n");
                                break;
                        case '>':
                                if (cmpLongNumber(a, b)>0)
                                        printf("true\n");
                                else
                                        printf("false\n");
                                break;
                        case '<':
                                if (cmpLongNumber(a, b)<0)
                                        printf("true\n");
                                else
                                        printf("false\n");
                                break;
                        case '=':
                                if (cmpLongNumber(a, b)==0)
                                        printf("true\n");
                                else
                                        printf("false\n");
                                break;

                }
        }


        return 0;
}





