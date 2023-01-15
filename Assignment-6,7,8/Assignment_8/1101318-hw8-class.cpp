#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// HugeInt class definition
class HugeInt
{
public:
   // returns true if and only if the specified huge integer is zero
   bool isZero();

   // return true if and only if hugeInt1 == hugeInt2
   bool equal( const HugeInt &hugeInt2 );

   // returns true if and only if hugeInt1 < hugeInt2
   bool less( const HugeInt &hugeInt2 );

   // --hugeInt
   void decrement();

   // minuend -= subtrahend provided that minuend > subtrahend
   void subtraAssign( const HugeInt &subtrahend );

   // multiplicand *= multiplier
   void multiAssign( const HugeInt &multiplier );

   // quotient = dividend / divisor; remainder = dividend % divisor
   void division( const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );

   // hugeInt /= 10, or equivalently, shifts right by one position
   void divideBy10();

   // hugeInt1 = hugeInt2
   void assign( const HugeInt &hugeInt2 );

   void reset();

   int size = 1;       // the number of digits of the integer; it can never be zero
   int *ptr = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

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
            dividend.multiAssign( base );
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
               divisor.multiAssign( base );
               if( divisor.size > maxSize - base.size )
                  break;
            }

            if( divisor.size > maxSize - base.size )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               dividend.decrement(); // --dividend
               divisor.decrement();   // --divisor

               dividend.division( divisor, quotient, remainder );

               if( quotient.size > 1 && quotient.ptr[ quotient.size - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainder.size > 1 && remainder.ptr[ remainder.size - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size < 100 && remainder.isZero() )
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
bool HugeInt::isZero()
{
   return ( size == 1 && ptr[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool HugeInt::equal( const HugeInt &hugeInt2 )
{
   if( size != hugeInt2.size )
      return false;

   for( int i = size - 1; i >= 0; i-- )
      if( ptr[ i ] != hugeInt2.ptr[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool HugeInt::less( const HugeInt &hugeInt2 )
{
    ////////////////////////////////////////
    if (size < hugeInt2.size)
    {
        return true;
    }
    else if (size > hugeInt2.size)
    {
        return false;
    }
    else if (size == hugeInt2.size) //size�@�ˤj��
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (ptr[i] < hugeInt2.ptr[i])
            {
                return true;
            }
            else if (ptr[i] > hugeInt2.ptr[i])
            {
                return false;
            }
        }
        return false; //ptr == hugeInt2.ptr
    }  
    ////////////////////////////////////////
}

// --hugeInt
void HugeInt::decrement()
{
   HugeInt one;
   one.ptr[ 0 ] = 1;
   subtraAssign( one );
   delete[] one.ptr;
}

// minuend -= subtrahend provided that minuend > subtrahend
void HugeInt::subtraAssign( const HugeInt &subtrahend ) //minuend.subtraAssign(subtrahend)
{
   if( equal( subtrahend ) )
   {
      reset();
      return;
   }
   ////////////////////////////////////////
   HugeInt difference; //�ŧi����A���R�Ŷ�
   delete[] difference.ptr;
   difference.size = size;   
   difference.ptr = new int[difference.size]();

   //�D�س��ŦX �Q��� > ���
   //���������
   for (int i = 0; i < subtrahend.size; i++)
   {
       difference.ptr[i] = ptr[i] - subtrahend.ptr[i];
   }
   for (int i = subtrahend.size; i < difference.size; i++)
   {
       difference.ptr[i] = ptr[i];
   }
   //������1
   for (int i = 0; i < difference.size - 1; i++) //�̫�@�줣�i��O�t���A���ˬd�Adifference.size - 1
   {
       if (difference.ptr[i] < 0)
       {
           difference.ptr[i] += 10;
           difference.ptr[i + 1] -= 1;         
       }
   }
   //�P�_diff�j�p
   for (int i = difference.size - 1; i >= 0; i--)
   {
       if (difference.ptr[i] != 0)
       {
           difference.size = i + 1;
           break;
       }
   }
   /*****���ݭndelete*******/
   //delete[] subtrahend.ptr;
  
   ////////////////////////////////////////


   if( difference.size > 1 && difference.ptr[ difference.size - 1 ] == 0 )
      cout << "difference has a leading zero!\n";

   assign( difference ); // minuend = difference     

   delete[] difference.ptr;
}

// multiplicand *= multiplier
void HugeInt::multiAssign( const HugeInt &multiplier )
{
   ////////////////////////////////////////
   HugeInt product;
   delete[] product.ptr;
   product.size = size + multiplier.size;   
   product.ptr = new int[product.size]();

   for (int i = 0; i < multiplier.size; i++)
   {
       for (int i2 = 0; i2 < size; i2++)
       {
           product.ptr[i+i2] += multiplier.ptr[i] * ptr[i2];
       }    
   }
   //�i��
   for (int i = 0; i < product.size - 1; i++)
   {
       if (product.ptr[i] > 9)
       {
           product.ptr[i + 1] += product.ptr[i] / 10;
           product.ptr[i] = product.ptr[i] % 10;
       }
   }
   //�ˬdproduct.size(���i��2x3=6)
   for (int i = product.size - 1; i >= 0; i--)
   {
       if (product.ptr[i] != 0)
       {
           product.size = i + 1;
           break;
       }
   }
   /*****���ݭndelete*******/
   //delete[] multiplier.ptr;

   ////////////////////////////////////////

   if( product.size > 1 && product.ptr[ product.size - 1 ] == 0 )
      cout << "product has a leading zero!\n";

   assign( product ); // *this = product

   delete[] product.ptr;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void HugeInt::division( const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder )
{
   remainder.assign( *this ); // remainder = dividend

   if( less( divisor ) )
      quotient.reset();
   else
   {
      HugeInt buffer;
      buffer.size = size;
      delete[] buffer.ptr;
      buffer.ptr = new int[ buffer.size ]();
      ////////////////////////////////////////
      int n = size - divisor.size;
      for (int i = divisor.size - 1; i >= 0; i--) //divisor�ǭȵ�buffer�A�Ashift n positions
      {
          buffer.ptr[i + n] = divisor.ptr[i];
      }

      //�ˬdbuffer���S���Ӥj�A�H���ˬdquotientSize:
      quotient.size = size - divisor.size;
      if (less(buffer))
      {
          buffer.divideBy10();
      }
      else
      {
          quotient.size++;
      }
      //quotient = 0
      delete[] quotient.ptr;
      quotient.ptr = new int[quotient.size]();

      //�ξl�Ƥ@����buffer�A�ò֥[quotient��e����m���ȡA�Ӷi�氣�k�A����remainder < buffer����
      for (int k = quotient.size - 1; k >= 0; k--)
      {
          while (!remainder.less(buffer))
          {
              remainder.subtraAssign(buffer);
              quotient.ptr[k]++;
              if (remainder.isZero())
              {
                  break; //��break���Oreturn�Areturn�|���Xfunction�A�U����delete[] buffer.ptr���ɷ|�R������
              }
          }
          buffer.divideBy10();
      }

      ////////////////////////////////////////
      delete[] buffer.ptr;
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void HugeInt::divideBy10()
{
   if( size == 1 )
      ptr[ 0 ] = 0;
   else
   {
      HugeInt buffer;
      buffer.assign( *this ); // buffer = *this

      size--;
      delete[] ptr;
      ptr = new int[ size ]();

      for( int i = 1; i <= size; i++ )
         ptr[ i - 1 ] = buffer.ptr[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void HugeInt::assign( const HugeInt &hugeInt2 ) //class����k //��input���O����
{                                               //�u�n�b�s�إߪ�����γo�Ӥ�k�A�s����.assign(hugeInt2)�A�N�|��hugeInt2����size��Ŷ����j��assgin���s����
   size = hugeInt2.size;  //class��member���ӴN��size�A��size���D�{�����s����size
   delete[] ptr;
   ptr = new int[ size ];
   for( int i = 0; i < size; i++ )
      ptr[ i ] = hugeInt2.ptr[ i ];
}

void HugeInt::reset()
{
   size = 1;
   delete[] ptr;
   ptr = new int[ 1 ]();
}