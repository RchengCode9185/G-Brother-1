#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *ptr = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 );

// --hugeInt
void decrement( HugeInt &hugeInt );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend );

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt );

// hugeInt1 = hugeInt2
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 );

void reset( HugeInt &hugeInt );

const int maxSize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInt dividend;
         HugeInt divisor;
         HugeInt quotient;
         HugeInt remainder;

         // put all digits of t into base
         HugeInt base;
         delete[] base.ptr;
         base.ptr = new int[ 10 ]();
         base.size = 0;
         for( int i = t; i > 0; i /= 10 )
            base.ptr[ base.size++ ] = i % 10;

         // dividend = pow( t, a )
         dividend.ptr[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiAssign( dividend, base );
            if( dividend.size > maxSize - base.size )
               break;
         }

         if( dividend.size > maxSize - base.size )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor.ptr[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiAssign( divisor, base );
               if( divisor.size > maxSize - base.size )
                  break;
            }

            if( divisor.size > maxSize - base.size )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend ); // --dividend
               decrement( divisor );   // --divisor

               division( dividend, divisor, quotient, remainder );

               if( quotient.size > 1 && quotient.ptr[ quotient.size - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainder.size > 1 && remainder.ptr[ remainder.size - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size < 100 && isZero( remainder ) )
                  for( int i = quotient.size - 1; i >= 0; i-- )
                     cout << quotient.ptr[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }

         delete[] dividend.ptr;
         delete[] divisor.ptr;
         delete[] quotient.ptr;
         delete[] remainder.ptr;
      }
   }

   system( "pause" );
}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt )
{
   return ( hugeInt.size == 1 && hugeInt.ptr[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.ptr[ i ] != hugeInt2.ptr[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 )
{
    /////////////////////////////////////////////////////////////////////////
    if (hugeInt1.size < hugeInt2.size)
    {
        return true;
    }
    else if (hugeInt1.size > hugeInt2.size)
    {
        return false;
    }
    else if (hugeInt1.size == hugeInt2.size)
    {
        for (int i = hugeInt1.size - 1; i >= 0; i--) //�q�̰����ˬd�C�@��
        {
            if (hugeInt1.ptr[i] > hugeInt2.ptr[i]) //hugeInt1 > hugeInt2
            {
                return false;
            }
            else if (hugeInt1.ptr[i] < hugeInt2.ptr[i]) //hugeInt1 < hugeInt2
            {
                return true;
            }             
        }
        return false; //hugeInt1 == hugeInt2
    }   
    /////////////////////////////////////////////////////////////////////////
}

// --hugeInt
void decrement( HugeInt &hugeInt )
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    HugeInt one;
    delete[] one.ptr; //***�n���R�쥻structure�̭��w�]��one���Ŷ�
    one.size = 1;
    one.ptr = new int[one.size]();
    one.ptr[0] = 1;

    subtraAssign(hugeInt, one);
    delete[] one.ptr;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      reset( minuend );
      return;
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
   HugeInt difference;
   delete[] difference.ptr;
   difference.size = minuend.size;
   difference.ptr = new int[minuend.size]();

   //�D�س��ŦX �Q��� > ���
   //���������
   for (int i = 0; i < subtrahend.size; i++) //********** i < subtrahendSize
   {
       difference.ptr[i] = minuend.ptr[i] - subtrahend.ptr[i];
   }
   //�A�Ⱚ��ƳѾl��minuend��idifference
   for (int i = subtrahend.size; i < difference.size; i++)
   {
       difference.ptr[i] = minuend.ptr[i];
   }
  
   //��ᤣ���ɤ@����z
   for (int i = 0; i < difference.size - 1; i++) //�̫�@�줣�i��O�t���A���ˬd�AdifferenceSize - 1
   {
       if (difference.ptr[i] < 0) //ex: -2
       {
           difference.ptr[i] += 10;
           difference.ptr[i + 1] -= 1;
       }
   }
   //�ˬddifferenceSize�A�̰��X��i��O0
   for (int i = difference.size - 1; i >= 0; i--)
   {
       if (difference.ptr[i] != 0)
       {
           difference.size = i + 1;
           break;
       }
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
   if( difference.size > 1 && difference.ptr[ difference.size - 1 ] == 0 )
      cout << "difference has a leading zero!\n";

   assign( minuend, difference ); // minuend = difference

   delete[] difference.ptr;
}

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier )
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    HugeInt product;
    delete[] product.ptr;
    product.size = multiplicand.size + multiplier.size; //�̤j
    product.ptr = new int[product.size]();

    //���k
    for (int i = 0; i < multiplier.size; i++)
    {
        for (int i2 = 0; i2 < multiplicand.size; i2++)
        {
            product.ptr[i + i2] += multiplier.ptr[i] * multiplicand.ptr[i2];
        }
    }
    //carry�i��
    for (int i = 0; i < product.size - 1; i++) //�ˬd��e�@�� productSize-
    {
        if (product.ptr[i] > 9)
        {
            product.ptr[i + 1] += product.ptr[i] / 10;
            product.ptr[i] %= 10;
        }
    }
    //�ˬdproductSize ex:2x2=4 productSize�w�]1+1=2�A���̫�productSize��1
    for (int i = product.size - 1; i >= 0; i--)
    {
        if (product.ptr[i] != 0)
        {
            product.size = i + 1;
            break;
        }
    }
    //////////////////////////////////////////////////////////////////

   if( product.size > 1 && product.ptr[ product.size - 1 ] == 0 )
      cout << "product has a leading zero!\n";

   assign( multiplicand, product ); // multiplicand = product

   delete[] product.ptr;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder )
{
   assign( remainder, dividend ); // remainder = dividend

   if( less( dividend, divisor ) )
      reset( quotient );
   else
   {
      HugeInt buffer;
      delete buffer.ptr;
      buffer.size = dividend.size;      
      buffer.ptr = new int[ buffer.size ]();


      //���Ƹ�0�[��buffer:
      int n = dividend.size - divisor.size; //�t�Fn��A�n��n��0
      for (int i = divisor.size - 1; i >= 0; i--) 
      {
          buffer.ptr[i + n] = divisor.ptr[i];
      }
      
      //�ˬdbuffer���S���Ӥj�A�H���ˬdquotientSize:
      quotient.size = dividend.size - divisor.size; //�w�]�̤p���i��
      if (less(dividend, buffer)) //dividend < buffer
      {
          divideBy10(buffer);
      }
      else //buffer <= dividend
      {
          quotient.size++; //40/2=20
      }

      //quotient = 0;
      delete[] quotient.ptr;
      quotient.ptr = new int[quotient.size]();
      
      //�ξl�Ƥ@����buffer�A�ò֥[quotient��e����m���ȡA�Ӷi�氣�k�A����remainder < buffer����
      for (int k = quotient.size - 1; k >= 0; k--) //k����e�p��Ӫ���m
      {
          while (!less(remainder, buffer)) //���n�O remainder < buffer�h����
          {
              subtraAssign(remainder, buffer);
              quotient.ptr[k]++;
              if (isZero(remainder))
              {
                  return;
              }
          }
          divideBy10(buffer);
      }

      //***�R�Ŷ�***�R�Ŷ�***�R�Ŷ�***�R�Ŷ�***�R�Ŷ�
      delete[] buffer.ptr;
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.ptr[ 0 ] = 0;
   else
   {
      HugeInt buffer;
      assign( buffer, hugeInt ); // buffer = hugeInt

      hugeInt.size--;
      delete[] hugeInt.ptr;
      hugeInt.ptr = new int[ hugeInt.size ]();

      for( int i = 1; i <= hugeInt.size; i++ )
         hugeInt.ptr[ i - 1 ] = buffer.ptr[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 )
{
   hugeInt1.size = hugeInt2.size;
   delete[] hugeInt1.ptr;
   hugeInt1.ptr = new int[ hugeInt1.size ];
   for( int i = 0; i < hugeInt1.size; i++ )
      hugeInt1.ptr[ i ] = hugeInt2.ptr[ i ];
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.ptr;
   hugeInt.ptr = new int[ 1 ]();
}