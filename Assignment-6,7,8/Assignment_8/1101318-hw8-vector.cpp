#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

#include <vector>
using std::vector;

// returns true if and only if the specified huge integer is zero
bool isZero( const vector< int > &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( const vector< int > &hugeInt1, const vector< int > &hugeInt2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( const vector< int > &hugeInt1, const vector< int > &hugeInt2 );

// --hugeInt
void decrement( vector< int > &hugeInt );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( vector< int > &minuend, const vector< int > &subtrahend );

// multiplicand *= multiplier
void multiplication( vector< int > &multiplicand, const vector< int > &multiplier );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( const vector< int > &dividend, const vector< int > &divisor,
               vector< int > &quotient, vector< int > &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt );

const int arraySize = 200;

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
         vector< int > dividend( 1 );
         vector< int > divisor( 1 );
         vector< int > quotient( 1 );
         vector< int > remainder( 1 );

         // put all digits of t into base
         vector< int > base;
         for( int i = t; i > 0; i /= 10 )
            base.push_back( i % 10 );

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( dividend, base );
            if( dividend.size() > arraySize - base.size() )
               break;
         }

         if( dividend.size() > arraySize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiplication( divisor, base );
               if( divisor.size() > arraySize - base.size() )
                  break;
            }

            if( divisor.size() > arraySize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend ); // --dividend
               decrement( divisor );   // --divisor

               division( dividend, divisor, quotient, remainder );

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && isZero( remainder ) )
                  for( int i = quotient.size() - 1; i >= 0; i-- )
                     cout << quotient[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( const vector< int > &hugeInt )
{
   return ( hugeInt.size() == 1 && hugeInt[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( const vector< int > &hugeInt1, const vector< int > &hugeInt2 )
{
   if( hugeInt1.size() != hugeInt2.size() )
      return false;

   for( int i = hugeInt1.size() - 1; i >= 0; i-- )
      if( hugeInt1[ i ] != hugeInt2[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( const vector< int > &hugeInt1, const vector< int > &hugeInt2 )
{
    ////////////////////////////////////////
    if (hugeInt1.size() < hugeInt2.size())
    {
        return true;
    }
    else if (hugeInt1.size() > hugeInt2.size())
    {
        return false;
    }
    else if (hugeInt1.size() == hugeInt2.size()) //size一樣大時
    {
        for (int i = hugeInt1.size() - 1; i >= 0; i--)
        {
            if (hugeInt1[i] > hugeInt2[i])
            {
                return false;
            }
            else if (hugeInt1[i] < hugeInt2[i])
            {
                return true;
            }
        }
        return false; 
    }

    ////////////////////////////////////////
}

// --hugeInt
void decrement( vector< int > &hugeInt )
{
   vector< int > one( 1 );
   one[ 0 ] = 1;
   subtraAssign( hugeInt, one );
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( vector< int > &minuend, const vector< int > &subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      minuend.resize( 1 );
      minuend[ 0 ] = 0;
      return;
   }
   ////////////////////////////////////////
   //相減
   for (int i = 0; i < subtrahend.size(); i++)
   {
       minuend[i] -= subtrahend[i];
   }
   //不夠借一
   for (int i = 0; i < minuend.size() - 1; i++) //最後一位不可能是負的，不檢查，difference.size - 1
   {
       if (minuend[i] < 0)
       {
           minuend[i] += 10;
           minuend[i + 1] -= 1;
       }
   }
   //判斷minuend大小
   int minuendSize = 0; //***拿來resize
   for (int i = minuend.size() - 1; i >= 0; i--)
   {
       if (minuend[i] != 0)
       {
           minuendSize = i + 1;
           break;
       }
   }

   ////////////////////////////////////////
   minuend.resize( minuendSize );
}

// multiplicand *= multiplier
void multiplication( vector< int > &multiplicand, const vector< int > &multiplier )
{
   int multiplicandSize = multiplicand.size();
   int multiplierSize = multiplier.size();
   vector< int > product( multiplicandSize + multiplierSize );
   ////////////////////////////////////////
   int productSize = product.size();
   //乘法
   for (int i = 0; i < multiplierSize; i++)
   {
       for (int i2 = 0; i2 < multiplicandSize; i2++)
       {
           product[i + i2] += multiplier[i] * multiplicand[i2];
       }
   }
   //進位
   for (int i = 0; i < productSize - 1; i++)
   {
       if (product[i] > 9)
       {
           product[i + 1] += product[i] / 10;
           product[i] = product[i] % 10;
       }
   }
   ////////////////////////////////////////
   if( product[ productSize - 1 ] == 0 ) //ex:3 x 2 = 6 (原本size預設最大是2)
      product.pop_back();
   //*********回傳值*********
   multiplicand = product; //************vector可直接用等號assign*********
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( const vector< int > &dividend, const vector< int > &divisor,
               vector< int > &quotient, vector< int > &remainder )
{
   remainder = dividend;

   if( less( dividend, divisor ) )
      quotient.resize( 1 );
   else
   {
      int dividendSize = dividend.size();
      int divisorSize = divisor.size();
      int quotientSize = dividendSize - divisorSize;
      vector< int > buffer( dividendSize );
      ////////////////////////////////////////
      //除數補0加到buffer:
      for (int i = divisor.size() - 1; i >= 0; i--) //divisor傳值給buffer，再shift n positions
      {
          buffer[i + quotientSize] = divisor[i];
      }

      //檢查buffer有沒有太大，以及檢查quotientSize:
      if (less(dividend, buffer))
      {
          divideBy10(buffer);
      }
      else
      {
          quotientSize++;
      }

      //quotient每次傳進來的都是大小1且值為0的vector
      //把(quotient = 0)步驟改成resize
      quotient.resize(quotientSize);
      
      //計算
      for (int k = quotient.size() - 1; k >= 0; k--)
      {
          while (!less(remainder,buffer))
          {
              subtraAssign(remainder,buffer);
              quotient[k]++;
              if (isZero(remainder))
              {
                  return;
              }
          }
          divideBy10(buffer);
      }

      ////////////////////////////////////////
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt )
{
   if( hugeInt.size() == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      int size = hugeInt.size();
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      hugeInt.pop_back();
   }
}