#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// returns true if and only if the specified huge integer is zero
bool isZero( int *hugeInt, int size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// --hugeInt
void decrement( int *&hugeInt, int &size );

// addend += adder
void addAssign( int *&addend, int *adder, int &addendSize, int adderSize );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( int *&minuend, int *subtrahend, int &minuendSize, int subtrahendSize );

// multiplicand *= multiplier
void multiAssign( int *&multiplicand, int *multiplier, int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int *&hugeInt, int &size );

// hugeInt1 = hugeInt2; assignment
void assign( int *&hugeInt1, int *hugeInt2, int &size1, int size2 );

void reset( int *&hugeInt, int &size );

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
         int *dividend = new int[ 1 ]();
         int *divisor = new int[ 1 ]();
         int *quotient = new int[ 1 ]();
         int *remainder = new int[ 1 ]();

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         // put all digits of t into base
         int *base = new int[ 10 ]();
         int baseSize = 0;
         for( int i = t; i > 0; i /= 10 )
            base[ baseSize++ ] = i % 10;

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiAssign( dividend, base, dividendSize, baseSize );
            if( dividendSize > maxSize - baseSize )
               break;
         }

         if( dividendSize > maxSize - baseSize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiAssign( divisor, base, divisorSize, baseSize );
               if( divisorSize > maxSize - baseSize )
                  break;
            }

            if( divisorSize > maxSize - baseSize )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend, dividendSize ); // --dividend
               decrement( divisor, divisorSize );   // --divisor

               division( dividend, divisor, quotient, remainder,
                  dividendSize, divisorSize, quotientSize, remainderSize );

               if( quotientSize > 1 && quotient[ quotientSize - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainderSize > 1 && remainder[ remainderSize - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotientSize < 100 && isZero( remainder, remainderSize ) )
                  for( int i = quotientSize - 1; i >= 0; i-- )
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
bool isZero( int *hugeInt, int size )
{
   return ( size == 1 && hugeInt[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 )
{
   if( size1 != size2 )
      return false;

   for( int i = size1 - 1; i >= 0; i-- )
      if( hugeInt1[ i ] != hugeInt2[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 ) //判斷第一個數是否小於第二個數
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (size1 < size2)
    {
        return true;
    }
    else if (size1 > size2)
    {
        return false;
    }
    else if (size1 == size2)
    {
        for (int i = size1 - 1; i >= 0; i--) //從最高位來比較大小
        {
            if (hugeInt1[i] > hugeInt2[i]) //hugeInt1 > hugeInt2
            {
                return false;
            }
            else if (hugeInt1[i] < hugeInt2[i]) //hugeInt1 < hugeInt2
            {
                return true;
            }
        }
        return false; //********** hugeInt1 == hugeInt2 **********
    }   
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// --hugeInt
void decrement( int *&hugeInt, int &size ) //題目的括號減一
{
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
   //用來減1的空間
   int oneSize = 1;
   int* one = new int[oneSize]();//()代表每個元素值都是0
   one[0] = 1;

   //hugeInt assign 給 buffer 來計算減1
   int bufferSize = size;
   int* buffer = new int[bufferSize]();

   assign(buffer, hugeInt, bufferSize, size); //buffer = hugeInt
   subtraAssign(buffer, one, bufferSize, oneSize);

   //刪空間***刪空間***刪空間***刪空間***刪空間***
   delete[] one;

   /////////////////////////////////////////////////////////////////////////////////////////////////////////
   if( bufferSize > 1 && buffer[ bufferSize - 1 ] == 0 )
      cout << "buffer has a leading zero!\n";
   //計算完的buffer assign給hugeInt
   assign( hugeInt, buffer, size, bufferSize ); // hugeInt = buffer
   //刪空間***刪空間***刪空間***刪空間***刪空間***
   delete[] buffer;

}

// addend += adder
void addAssign( int *&addend, int *adder, int &addendSize, int adderSize )
{
   int sumSize = ( addendSize >= adderSize ) ? addendSize + 1 : adderSize + 1; //決定sumSize
   int *sum = new int[ sumSize ]();

   for( int i = 0; i < addendSize; i++ )
      sum[ i ] = addend[ i ];

   for( int i = 0; i < adderSize; i++ )
      sum[ i ] += adder[ i ];

   for( int i = 0; i < sumSize - 1; i++ ) //進位
      if( sum[ i ] > 9 ) // carrying
      {
         sum[ i ] -= 10;
         sum[ i + 1 ]++;
      }

   if( sum[ sumSize - 1 ] == 0 )
      sumSize--;

   if( sumSize > 1 && sum[ sumSize - 1 ] == 0 )
      cout << "sum has a leading zero!\n";

   assign( addend, sum, addendSize, sumSize ); // addend = sum

   delete[] sum;
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( int *&minuend, int *subtrahend, int &minuendSize, int subtrahendSize )
{
   if( equal( minuend, subtrahend, minuendSize, subtrahendSize ) )
   {
      reset( minuend, minuendSize );
      return;
   }

   /////////////////////////////////////////////////////////////////////////////////////////////////////////
   int differenceSize = minuendSize;
   int* difference = new int[differenceSize]();
  
   //題目都符合 被減數 > 減數
   //先做減的部分
   for (int i = 0; i < subtrahendSize; i++) //********** i < subtrahendSize
   {
       difference[i] = minuend[i] - subtrahend[i];
   }
   //再把高位數剩餘的minuend丟進difference
   for (int i = subtrahendSize; i < differenceSize; i++)
   {
       difference[i] = minuend[i];
   }
   
   //減完後不夠借一的整理
   for (int i = 0; i < differenceSize - 1; i++) //最後一位不可能是負的不檢查 => differenceSize - 1
   {
       if (difference[i] < 0) //ex: -2
       {
           difference[i] += 10;
           difference[i + 1] -= 1;
       }
   }
   //檢查differenceSize，最高幾位可能是0
   for (int i = differenceSize - 1; i >= 0; i--) //********** (int i = size - 1; i >= 0; i--) **********
   {
       if (difference[i] != 0)
       {
           differenceSize = i + 1; //********** size = i + 1 **********
           break;
       }
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////

   if( differenceSize > 1 && difference[ differenceSize - 1 ] == 0 )
      cout << "difference has a leading zero!\n";

   assign( minuend, difference, minuendSize, differenceSize ); // minuend = difference //把difference assign給 minuend
   //刪空間***刪空間***刪空間***刪空間***刪空間***
   delete[] difference; 
}

// multiplicand *= multiplier
void multiAssign( int *&multiplicand, int *multiplier, int &multiplicandSize, int multiplierSize )
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    int productSize = multiplicandSize + multiplierSize; //最大 ex:5x4=20 or 5x1=5
    int* product = new int[productSize]();

    //乘法
    for (int i = 0; i < multiplierSize; i++)
    {
        for (int i2 = 0; i2 < multiplicandSize; i2++)
        {
            product[i + i2] += multiplier[i] * multiplicand[i2];
        }
    }
    //carry進位
    for (int i = 0; i < productSize - 1; i++) //檢查到前一位 productSize-1，因為最高位數不可能再往下進位
    {
        if (product[i] > 9)
        {
            product[i + 1] += product[i] / 10; //ex: 48/10 = 4
            product[i] %= 10;
        }
    }
    //檢查productSize 預設最大ex:5x4=20，但有可能ex:2x2=4
    for (int i = productSize - 1; i >= 0; i--)
    {
        if (product[i] != 0)
        {
            productSize = i + 1;
            break;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////



   if( productSize > 1 && product[ productSize - 1 ] == 0 )
      cout << "product has a leading zero!\n";

   assign( multiplicand, product, multiplicandSize, productSize ); // multiplicand = product
   //刪空間***刪空間***刪空間***刪空間***刪空間***
   delete[] product;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
   assign( remainder, dividend, remainderSize, dividendSize ); // remainder = dividend

   if( less( dividend, divisor, dividendSize, divisorSize ) )
      reset( quotient, quotientSize ); //答案直接為0
   else
   {
      int bufferSize = dividendSize;
      int *buffer = new int[ bufferSize ]();

      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      //除數補0加到buffer:
      int n = dividendSize - divisorSize; //差了n格，要補n個0 
      for (int i = divisorSize - 1; i >= 0; i--) //從divisor的最高位補n個0丟到buffer，以此類推  p.s.buffer原本全為0
      {
          buffer[i + n] = divisor[i]; 
      }     

      //檢查buffer有沒有太大，以及檢查quotientSize:
      quotientSize = dividendSize - divisorSize; //預設最小ex:20/5=4，但可能ex:50/5=10
      if (less(dividend, buffer, dividendSize, bufferSize)) //dividend < buffer (補過0的buffer最高位 > dividend最高位)
      {
          divideBy10(buffer, bufferSize);
      }
      else //buffer <= dividend ex:50/5=10 => 實際的size為2
      {
          quotientSize++; 
      }

      //quotient = 0 : 
      delete[] quotient; //因為quotient指的空間要回傳回去，所以不能在外面刪掉，只能等到下一次要重算的時候才歸0
      quotient = new int[quotientSize]();
      
      //除法計算quotient:
      //用餘數一直減buffer，並累加quotient指到位置的值，直到remainder < buffer 或 remainder剩0 結束
      for (int k = quotientSize - 1; k >= 0; k--) //k為quotient指到的位置(當前計算商的位置)
      {
          while (!less(remainder, buffer, remainderSize, bufferSize)) //不要是 remainder < buffer則執行
          {
              subtraAssign(remainder, buffer, remainderSize, bufferSize);
              quotient[k]++;
              if (isZero(remainder, remainderSize)) //remainder剩0 結束
              {
                  return;
              }
          }
          divideBy10(buffer, bufferSize); //計算完一個商後，buffer少一個0
      }
      
      //***刪空間***刪空間***刪空間***刪空間***刪空間
      delete[] buffer;
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int *&hugeInt, int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      int *buffer = new int[ 1 ];
      int bufferSize = 1;
      assign( buffer, hugeInt, bufferSize, size ); // buffer = hugeInt

      size--;
      delete[] hugeInt;
      hugeInt = new int[ size ]();

      for( int i = 1; i <= size; i++ )
         hugeInt[ i - 1 ] = buffer[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void assign( int *&hugeInt1, int *hugeInt2, int &size1, int size2 )
{
   size1 = size2;
   delete[] hugeInt1;
   hugeInt1 = new int[ size1 ];
   for( int i = 0; i < size1; i++ )
      hugeInt1[ i ] = hugeInt2[ i ];
}

void reset( int *&hugeInt, int &size ) //把數字變0
{
   size = 1;
   delete[] hugeInt;
   hugeInt = new int[ 1 ]();
}