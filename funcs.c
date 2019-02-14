
/******************************************************************************************
* Function name: Compare
* Input: int x, int y
* Output: int result
* Function Operation: The function gets tow numbers and returns the follow-
*					  1 if x bigger, -1 if y bigger and 0 if equal
*					  without if or loops
******************************************************************************************/
int bitAnd(int x, int y){
	int p = (x-y)>>31; // x bigger -> 0, y bigger -> -1, equals -> 0
	int q = (y-x)>>31; // x bigger -> -1, y bigger -> 0, equals -> 0
	int mask = (0x1 & q)<<1; // x bigger -> 2, y bigger -> 0, equals -> 0
	return (p + q + mask) ; // x bigger -> 1, y bigger -> -1, equals -> 0
}

/******************************************************************************************
* Function name: bitAnd
* Input: int x, int y
* Output: int result
* Function Operation: The function gets tow numbers and returns x&y
*					  as we now from Discrete math- p&q it is like ~(~p|~q) (-DeMorgan)
*					  for example -  6&5 == ~(~6|~5) == 4
******************************************************************************************/
int bitAnd(int x, int y){
	int result;
	// make ~x and ~y
	x = ~x;
	y = ~y;
	// set the result to be an or of the new x and y
	result = x | y;
	// do ~ to the result
	result = ~result;
	return result;
}

// didnt succes to do this func
int bitCount(int x){
	return 0;
}

/******************************************************************************************
* Function name: bang
* Input: int x
* Output: int msbR
* Function Operation: The function gets a number and return it's logical NOT-
*					  if the number == 0 - return 1
*					  if the number =!0 (positive or negative) - return 0
*					  for example -  if 0 returns 1, if 3 returns 0, if -29 returns 0...
******************************************************************************************/
int bang(int x){
	int designatedMask;
	// mask = 00...001
	int maskOne = 0x1;
	int msbR;
	/* if the number is negative - mask wil be 11111111..
	if the number is positive/0- mask wil be 0000000... */
	designatedMask = x >> 31;
	/* flip-
	if the number is negative - mask wil be 0000000..
	if the number is positive/0- mask wil be 11111111... */
	designatedMask = ~designatedMask;
	/* if x is negative - it will stay the same
	if positive / 0 - it will flip the '0' and '1' */
	x = x ^ designatedMask;
	/* if x is negative - the MSB right will be 0
	if positive/0 - the MSB right will be 1 */
	msbR = maskOne & designatedMask;
	/* if x negative - add 0 (do nothing)
	if positive/0 - add 1 */
	x = x + msbR;
	/* now- if the original number was positive/negative- it is negative now. if 0- its 0
	if the number is 0 - mask wil be 000000000..
	else - mask wil be 11111111... */
	designatedMask = x >> 31;
	/* if the number is 0 - MSBright will be 0
	else - the MSB right will be 1 */
	msbR = maskOne & designatedMask;
	// return the sign- 1 if x=0 and 0 if x!=0
	msbR = msbR^maskOne;
	return msbR;
}

/******************************************************************************************
* Function name: fitsBits
* Input: int x, int n
* Output: int x (0 or 1)
* Function Operation: The function gets tow numbers and checks if x can be represented
*					  with n bits (or less)
*					  for example-(x = 4, n = 2) return 0, (x = 4, n = 9) returns 1...
******************************************************************************************/
int fitsBits(int x, int n){
	// mask = 1111111..1111 (32 times)
	int mask = -1;
	// flip the '0's and '1's
	x = ~x;
	// place '0's in the right with the size of n
	mask = mask << (n);
	/* add between x and mask-
	if x can be presented with n- it will be only 1 in the left from n and 0 from the right*/
	x = x & mask;
	// move x n times right - only if the number can be presented it will be 1111...111 (==-1)
	// do it in 2 actions in case it n = 32
	x = x >> (n-1);
	x = x >> (1);
	/* add 1. if x can be presented with n bits (the number is now -1), it will be 0
	else - it will be !=0*/
	x = x + 1;
	// do logical not- if it 0 make it 1(can be presented), else- make it 0 (cant)
	x = !x;
	// return 1 if x can be presented with n bits, and 0 if not
	return x;
}

/******************************************************************************************
* Function name: divpwr2
* Input: int x, int n
* Output: int x (result)
* Function Operation: The function gets tow numbers and returns (x/2^n)
*					  it returns the int that closer to 0
*					  for example -  (x = 33, n = 4) == 2, (x = -33, n = 4) == -2...
******************************************************************************************/
int divpwr2(int x, int n){
	x = (unsigned int)x;
	int designatedMask;
	// mask = 00...001
	int maskOne = 0x1;
	int msbR;
	/* if the number is negative - mask wil be 11111111..
	if the number is positive- mask wil be 0000000...*/
	designatedMask = x >> 31;
	/* if x positive - it will stay the same
	 if negative - it will flip the '0' and '1' */
	x = x ^ designatedMask;
	/* if x positive - the MSB right will be 0
	if negative - the MSB right will be 1 */
	msbR = maskOne & designatedMask;
	/* if x positive - add 0 (do nothing)
	if negative - add 1 */
	x = x + msbR;
	// now its a positive number for sure - divide it
	x = x >> n;
	/* in the same way as before-
	if the result is positive - it will stay the same
	if negative - it will flip the '0' and '1' */
	x = x ^ designatedMask;
	/* if the result is positive - add 0 (do nothing)
	if negative - add 1 */
	x = x + msbR;
	//return the result
	return x;
}

/******************************************************************************************
* Function name: negate
* Input: int x
* Output: int x (the additive inverse)
* Function Operation: The function gets a number and returns the negative
*					  for example -  if 0 returns 0, if 1 returns -1, if -29 returns 29...
******************************************************************************************/
int negate(int x){
	// flip the digits in x
	x = ~x;
	// add 1 to x
	x = x + 1;
	return x;
}

/******************************************************************************************
* Function name: isPositive
* Input: int x
* Output: int x (0 or 1)
* Function Operation: The function gets a number and returns if is positive >0
*					  if <= 0 - return 0, if > 0 - return 1
*					  for example -  if 0 returns 0, if -12 returns 0, if 29 returns 1...
******************************************************************************************/
int isPositive(int x){
	// mask = 00000001;
	int mask = 1;
	int temp;
	/* place x's MSB in the rightest bit
	if x negative- temp is 11111111, if positive/0- temp is 00000000 */
	temp = x >> 31;
	/* keep just the rightest bit by & to mask(00000001)
	if x negative- temp is 00000001, if positive/0- temp is 00000000*/
	temp = temp&mask;
	// if x is 0- now it is 00000001, else- its 0;
	x = (!x);
	/* if x is negative or '0'- make x to 1
	if x is positive - make x to 0 */
	x = (x|temp);
	// if x positive - make it 1, if negative/0- make it 0
	x = (!x);
	// return 1 if >0, else- return 0
	return x;
}

/******************************************************************************************
* Function name: isLessOrEqual
* Input: int x, int y
* Output: int sign (0 or 1)
* Function Operation: The function gets tow numbers and checks if x is less or equal
*					  to y.
*					  for example-(x=4, y=4) return 1,(x=-4, y=2) return 1 (x=14, y=9) returns 0
******************************************************************************************/
int isLessOrEqual(int x, int y){
	int sign;
	// if x negative make it positive and if is positive make it negative
	x = ~x;
	x = x + 1;
	// set sign to the sum of (-x) and y
	sign = x + y;
	/* if the sum is positive (x is less or equel to y) it wil be 000000...
	 if the sum is negative (x is bigger than y) it wil be 11111111...*/
	sign = sign >> 31;
	/* if x is less or equel to - it wil be 1
	if x is bigger than y- it wil be 0 */
	sign = sign + 1;
	// return 0 or 1- the sign
	return sign;
}
