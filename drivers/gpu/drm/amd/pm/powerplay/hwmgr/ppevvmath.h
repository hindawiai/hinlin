<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <यंत्र/भाग64.h>

#घोषणा SHIFT_AMOUNT 16 /* We multiply all original पूर्णांकegers with 2^SHIFT_AMOUNT to get the fInt representation */

#घोषणा PRECISION 5 /* Change this value to change the number of decimal places in the final output - 5 is a good शेष */

#घोषणा SHIFTED_2 (2 << SHIFT_AMOUNT)
#घोषणा MAX (1 << (SHIFT_AMOUNT - 1)) - 1 /* 32767 - Might change in the future */

/* -------------------------------------------------------------------------------
 * NEW TYPE - fINT
 * -------------------------------------------------------------------------------
 * A variable of type fInt can be accessed in 3 ways using the करोt (.) चालक
 * fInt A;
 * A.full => The full number as it is. Generally not easy to पढ़ो
 * A.partial.real => Only the पूर्णांकeger portion
 * A.partial.decimal => Only the fractional portion
 */
प्रकार जोड़ _fInt अणु
    पूर्णांक full;
    काष्ठा _partial अणु
        अचिन्हित पूर्णांक decimal: SHIFT_AMOUNT; /*Needs to always be अचिन्हित*/
        पूर्णांक real: 32 - SHIFT_AMOUNT;
    पूर्ण partial;
पूर्ण fInt;

/* -------------------------------------------------------------------------------
 * Function Declarations
 *  -------------------------------------------------------------------------------
 */
अटल fInt ConvertToFraction(पूर्णांक);                       /* Use this to convert an INT to a FINT */
अटल fInt Convert_ULONG_ToFraction(uपूर्णांक32_t);           /* Use this to convert an uपूर्णांक32_t to a FINT */
अटल fInt GetScaledFraction(पूर्णांक, पूर्णांक);                  /* Use this to convert an INT to a FINT after scaling it by a factor */
अटल पूर्णांक ConvertBackToInteger(fInt);                    /* Convert a FINT back to an INT that is scaled by 1000 (i.e. last 3 digits are the decimal digits) */

अटल fInt fNegate(fInt);                                /* Returns -1 * input fInt value */
अटल fInt fAdd (fInt, fInt);                            /* Returns the sum of two fInt numbers */
अटल fInt fSubtract (fInt A, fInt B);                   /* Returns A-B - Someबार easier than Adding negative numbers */
अटल fInt fMultiply (fInt, fInt);                       /* Returns the product of two fInt numbers */
अटल fInt fDivide (fInt A, fInt B);                     /* Returns A/B */
अटल fInt fGetSquare(fInt);                             /* Returns the square of a fInt number */
अटल fInt fSqrt(fInt);                                  /* Returns the Square Root of a fInt number */

अटल पूर्णांक uAbs(पूर्णांक);                                     /* Returns the Absolute value of the Int */
अटल पूर्णांक uPow(पूर्णांक base, पूर्णांक exponent);                  /* Returns base^exponent an INT */

अटल व्योम SolveQuadracticEqn(fInt, fInt, fInt, fInt[]); /* Returns the 2 roots via the array */
अटल bool Equal(fInt, fInt);                            /* Returns true अगर two fInts are equal to each other */
अटल bool GreaterThan(fInt A, fInt B);                  /* Returns true अगर A > B */

अटल fInt fExponential(fInt exponent);                  /* Can be used to calculate e^exponent */
अटल fInt fNaturalLog(fInt value);                      /* Can be used to calculate ln(value) */

/* Fuse decoding functions
 * -------------------------------------------------------------------------------------
 */
अटल fInt fDecodeLinearFuse(uपूर्णांक32_t fuse_value, fInt f_min, fInt f_range, uपूर्णांक32_t bitlength);
अटल fInt fDecodeLogisticFuse(uपूर्णांक32_t fuse_value, fInt f_average, fInt f_range, uपूर्णांक32_t bitlength);
अटल fInt fDecodeLeakageID (uपूर्णांक32_t leakageID_fuse, fInt ln_max_भाग_min, fInt f_min, uपूर्णांक32_t bitlength);

/* Internal Support Functions - Use these ONLY क्रम testing or adding to पूर्णांकernal functions
 * -------------------------------------------------------------------------------------
 * Some of the following functions take two INTs as their input - This is unsafe क्रम a variety of reasons.
 */
अटल fInt Divide (पूर्णांक, पूर्णांक);                            /* Divide two INTs and वापस result as FINT */
अटल fInt fNegate(fInt);

अटल पूर्णांक uGetScaledDecimal (fInt);                      /* Internal function */
अटल पूर्णांक GetReal (fInt A);                              /* Internal function */

/* -------------------------------------------------------------------------------------
 * TROUBLESHOOTING INFORMATION
 * -------------------------------------------------------------------------------------
 * 1) ConvertToFraction - InputOutOfRangeException: Only accepts numbers smaller than MAX (शेष: 32767)
 * 2) fAdd - OutputOutOfRangeException: Output bigger than MAX (शेष: 32767)
 * 3) fMultiply - OutputOutOfRangeException:
 * 4) fGetSquare - OutputOutOfRangeException:
 * 5) fDivide - DivideByZeroException
 * 6) fSqrt - NegativeSquareRootException: Input cannot be a negative number
 */

/* -------------------------------------------------------------------------------------
 * START OF CODE
 * -------------------------------------------------------------------------------------
 */
अटल fInt fExponential(fInt exponent)        /*Can be used to calculate e^exponent*/
अणु
	uपूर्णांक32_t i;
	bool bNegated = false;

	fInt fPositiveOne = ConvertToFraction(1);
	fInt fZERO = ConvertToFraction(0);

	fInt lower_bound = Divide(78, 10000);
	fInt solution = fPositiveOne; /*Starting off with baseline of 1 */
	fInt error_term;

	अटल स्थिर uपूर्णांक32_t k_array[11] = अणु55452, 27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78पूर्ण;
	अटल स्थिर uपूर्णांक32_t expk_array[11] = अणु2560000, 160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078पूर्ण;

	अगर (GreaterThan(fZERO, exponent)) अणु
		exponent = fNegate(exponent);
		bNegated = true;
	पूर्ण

	जबतक (GreaterThan(exponent, lower_bound)) अणु
		क्रम (i = 0; i < 11; i++) अणु
			अगर (GreaterThan(exponent, GetScaledFraction(k_array[i], 10000))) अणु
				exponent = fSubtract(exponent, GetScaledFraction(k_array[i], 10000));
				solution = fMultiply(solution, GetScaledFraction(expk_array[i], 10000));
			पूर्ण
		पूर्ण
	पूर्ण

	error_term = fAdd(fPositiveOne, exponent);

	solution = fMultiply(solution, error_term);

	अगर (bNegated)
		solution = fDivide(fPositiveOne, solution);

	वापस solution;
पूर्ण

अटल fInt fNaturalLog(fInt value)
अणु
	uपूर्णांक32_t i;
	fInt upper_bound = Divide(8, 1000);
	fInt fNegativeOne = ConvertToFraction(-1);
	fInt solution = ConvertToFraction(0); /*Starting off with baseline of 0 */
	fInt error_term;

	अटल स्थिर uपूर्णांक32_t k_array[10] = अणु160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078पूर्ण;
	अटल स्थिर uपूर्णांक32_t logk_array[10] = अणु27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78पूर्ण;

	जबतक (GreaterThan(fAdd(value, fNegativeOne), upper_bound)) अणु
		क्रम (i = 0; i < 10; i++) अणु
			अगर (GreaterThan(value, GetScaledFraction(k_array[i], 10000))) अणु
				value = fDivide(value, GetScaledFraction(k_array[i], 10000));
				solution = fAdd(solution, GetScaledFraction(logk_array[i], 10000));
			पूर्ण
		पूर्ण
	पूर्ण

	error_term = fAdd(fNegativeOne, value);

	वापस (fAdd(solution, error_term));
पूर्ण

अटल fInt fDecodeLinearFuse(uपूर्णांक32_t fuse_value, fInt f_min, fInt f_range, uपूर्णांक32_t bitlength)
अणु
	fInt f_fuse_value = Convert_ULONG_ToFraction(fuse_value);
	fInt f_bit_max_value = Convert_ULONG_ToFraction((uPow(2, bitlength)) - 1);

	fInt f_decoded_value;

	f_decoded_value = fDivide(f_fuse_value, f_bit_max_value);
	f_decoded_value = fMultiply(f_decoded_value, f_range);
	f_decoded_value = fAdd(f_decoded_value, f_min);

	वापस f_decoded_value;
पूर्ण


अटल fInt fDecodeLogisticFuse(uपूर्णांक32_t fuse_value, fInt f_average, fInt f_range, uपूर्णांक32_t bitlength)
अणु
	fInt f_fuse_value = Convert_ULONG_ToFraction(fuse_value);
	fInt f_bit_max_value = Convert_ULONG_ToFraction((uPow(2, bitlength)) - 1);

	fInt f_CONSTANT_NEG13 = ConvertToFraction(-13);
	fInt f_CONSTANT1 = ConvertToFraction(1);

	fInt f_decoded_value;

	f_decoded_value = fSubtract(fDivide(f_bit_max_value, f_fuse_value), f_CONSTANT1);
	f_decoded_value = fNaturalLog(f_decoded_value);
	f_decoded_value = fMultiply(f_decoded_value, fDivide(f_range, f_CONSTANT_NEG13));
	f_decoded_value = fAdd(f_decoded_value, f_average);

	वापस f_decoded_value;
पूर्ण

अटल fInt fDecodeLeakageID (uपूर्णांक32_t leakageID_fuse, fInt ln_max_भाग_min, fInt f_min, uपूर्णांक32_t bitlength)
अणु
	fInt fLeakage;
	fInt f_bit_max_value = Convert_ULONG_ToFraction((uPow(2, bitlength)) - 1);

	fLeakage = fMultiply(ln_max_भाग_min, Convert_ULONG_ToFraction(leakageID_fuse));
	fLeakage = fDivide(fLeakage, f_bit_max_value);
	fLeakage = fExponential(fLeakage);
	fLeakage = fMultiply(fLeakage, f_min);

	वापस fLeakage;
पूर्ण

अटल fInt ConvertToFraction(पूर्णांक X) /*Add all range checking here. Is it possible to make fInt a निजी declaration? */
अणु
	fInt temp;

	अगर (X <= MAX)
		temp.full = (X << SHIFT_AMOUNT);
	अन्यथा
		temp.full = 0;

	वापस temp;
पूर्ण

अटल fInt fNegate(fInt X)
अणु
	fInt CONSTANT_NEGONE = ConvertToFraction(-1);
	वापस (fMultiply(X, CONSTANT_NEGONE));
पूर्ण

अटल fInt Convert_ULONG_ToFraction(uपूर्णांक32_t X)
अणु
	fInt temp;

	अगर (X <= MAX)
		temp.full = (X << SHIFT_AMOUNT);
	अन्यथा
		temp.full = 0;

	वापस temp;
पूर्ण

अटल fInt GetScaledFraction(पूर्णांक X, पूर्णांक factor)
अणु
	पूर्णांक बार_shअगरted, factor_shअगरted;
	bool bNEGATED;
	fInt fValue;

	बार_shअगरted = 0;
	factor_shअगरted = 0;
	bNEGATED = false;

	अगर (X < 0) अणु
		X = -1*X;
		bNEGATED = true;
	पूर्ण

	अगर (factor < 0) अणु
		factor = -1*factor;
		bNEGATED = !bNEGATED; /*If bNEGATED = true due to X < 0, this will cover the हाल of negative cancelling negative */
	पूर्ण

	अगर ((X > MAX) || factor > MAX) अणु
		अगर ((X/factor) <= MAX) अणु
			जबतक (X > MAX) अणु
				X = X >> 1;
				बार_shअगरted++;
			पूर्ण

			जबतक (factor > MAX) अणु
				factor = factor >> 1;
				factor_shअगरted++;
			पूर्ण
		पूर्ण अन्यथा अणु
			fValue.full = 0;
			वापस fValue;
		पूर्ण
	पूर्ण

	अगर (factor == 1)
		वापस ConvertToFraction(X);

	fValue = fDivide(ConvertToFraction(X * uPow(-1, bNEGATED)), ConvertToFraction(factor));

	fValue.full = fValue.full << बार_shअगरted;
	fValue.full = fValue.full >> factor_shअगरted;

	वापस fValue;
पूर्ण

/* Addition using two fInts */
अटल fInt fAdd (fInt X, fInt Y)
अणु
	fInt Sum;

	Sum.full = X.full + Y.full;

	वापस Sum;
पूर्ण

/* Addition using two fInts */
अटल fInt fSubtract (fInt X, fInt Y)
अणु
	fInt Dअगरference;

	Dअगरference.full = X.full - Y.full;

	वापस Dअगरference;
पूर्ण

अटल bool Equal(fInt A, fInt B)
अणु
	अगर (A.full == B.full)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool GreaterThan(fInt A, fInt B)
अणु
	अगर (A.full > B.full)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल fInt fMultiply (fInt X, fInt Y) /* Uses 64-bit पूर्णांकegers (पूर्णांक64_t) */
अणु
	fInt Product;
	पूर्णांक64_t tempProduct;

	/*The following is क्रम a very specअगरic common हाल: Non-zero number with ONLY fractional portion*/
	/* TEMPORARILY DISABLED - CAN BE USED TO IMPROVE PRECISION
	bool X_LessThanOne, Y_LessThanOne;

	X_LessThanOne = (X.partial.real == 0 && X.partial.decimal != 0 && X.full >= 0);
	Y_LessThanOne = (Y.partial.real == 0 && Y.partial.decimal != 0 && Y.full >= 0);

	अगर (X_LessThanOne && Y_LessThanOne) अणु
		Product.full = X.full * Y.full;
		वापस Product
	पूर्ण*/

	tempProduct = ((पूर्णांक64_t)X.full) * ((पूर्णांक64_t)Y.full); /*Q(16,16)*Q(16,16) = Q(32, 32) - Might become a negative number! */
	tempProduct = tempProduct >> 16; /*Remove lagging 16 bits - Will lose some precision from decimal; */
	Product.full = (पूर्णांक)tempProduct; /*The पूर्णांक64_t will lose the leading 16 bits that were part of the पूर्णांकeger portion */

	वापस Product;
पूर्ण

अटल fInt fDivide (fInt X, fInt Y)
अणु
	fInt fZERO, fQuotient;
	पूर्णांक64_t दीर्घदीर्घX, दीर्घदीर्घY;

	fZERO = ConvertToFraction(0);

	अगर (Equal(Y, fZERO))
		वापस fZERO;

	दीर्घदीर्घX = (पूर्णांक64_t)X.full;
	दीर्घदीर्घY = (पूर्णांक64_t)Y.full;

	दीर्घदीर्घX = दीर्घदीर्घX << 16; /*Q(16,16) -> Q(32,32) */

	भाग64_s64(दीर्घदीर्घX, दीर्घदीर्घY); /*Q(32,32) भागided by Q(16,16) = Q(16,16) Back to original क्रमmat */

	fQuotient.full = (पूर्णांक)दीर्घदीर्घX;
	वापस fQuotient;
पूर्ण

अटल पूर्णांक ConvertBackToInteger (fInt A) /*THIS is the function that will be used to check with the Golden settings table*/
अणु
	fInt fullNumber, scaledDecimal, scaledReal;

	scaledReal.full = GetReal(A) * uPow(10, PRECISION-1); /* DOUBLE CHECK THISSSS!!! */

	scaledDecimal.full = uGetScaledDecimal(A);

	fullNumber = fAdd(scaledDecimal,scaledReal);

	वापस fullNumber.full;
पूर्ण

अटल fInt fGetSquare(fInt A)
अणु
	वापस fMultiply(A,A);
पूर्ण

/* x_new = x_old - (x_old^2 - C) / (2 * x_old) */
अटल fInt fSqrt(fInt num)
अणु
	fInt F_भागide_Fprime, Fprime;
	fInt test;
	fInt twoShअगरted;
	पूर्णांक seed, counter, error;
	fInt x_new, x_old, C, y;

	fInt fZERO = ConvertToFraction(0);

	/* (0 > num) is the same as (num < 0), i.e., num is negative */

	अगर (GreaterThan(fZERO, num) || Equal(fZERO, num))
		वापस fZERO;

	C = num;

	अगर (num.partial.real > 3000)
		seed = 60;
	अन्यथा अगर (num.partial.real > 1000)
		seed = 30;
	अन्यथा अगर (num.partial.real > 100)
		seed = 10;
	अन्यथा
		seed = 2;

	counter = 0;

	अगर (Equal(num, fZERO)) /*Square Root of Zero is zero */
		वापस fZERO;

	twoShअगरted = ConvertToFraction(2);
	x_new = ConvertToFraction(seed);

	करो अणु
		counter++;

		x_old.full = x_new.full;

		test = fGetSquare(x_old); /*1.75*1.75 is reverting back to 1 when shअगरted करोwn */
		y = fSubtract(test, C); /*y = f(x) = x^2 - C; */

		Fprime = fMultiply(twoShअगरted, x_old);
		F_भागide_Fprime = fDivide(y, Fprime);

		x_new = fSubtract(x_old, F_भागide_Fprime);

		error = ConvertBackToInteger(x_new) - ConvertBackToInteger(x_old);

		अगर (counter > 20) /*20 is alपढ़ोy way too many iterations. If we करोnt have an answer by then, we never will*/
			वापस x_new;

	पूर्ण जबतक (uAbs(error) > 0);

	वापस (x_new);
पूर्ण

अटल व्योम SolveQuadracticEqn(fInt A, fInt B, fInt C, fInt Roots[])
अणु
	fInt *pRoots = &Roots[0];
	fInt temp, root_first, root_second;
	fInt f_CONSTANT10, f_CONSTANT100;

	f_CONSTANT100 = ConvertToFraction(100);
	f_CONSTANT10 = ConvertToFraction(10);

	जबतक(GreaterThan(A, f_CONSTANT100) || GreaterThan(B, f_CONSTANT100) || GreaterThan(C, f_CONSTANT100)) अणु
		A = fDivide(A, f_CONSTANT10);
		B = fDivide(B, f_CONSTANT10);
		C = fDivide(C, f_CONSTANT10);
	पूर्ण

	temp = fMultiply(ConvertToFraction(4), A); /* root = 4*A */
	temp = fMultiply(temp, C); /* root = 4*A*C */
	temp = fSubtract(fGetSquare(B), temp); /* root = b^2 - 4AC */
	temp = fSqrt(temp); /*root = Sqrt (b^2 - 4AC); */

	root_first = fSubtract(fNegate(B), temp); /* b - Sqrt(b^2 - 4AC) */
	root_second = fAdd(fNegate(B), temp); /* b + Sqrt(b^2 - 4AC) */

	root_first = fDivide(root_first, ConvertToFraction(2)); /* [b +- Sqrt(b^2 - 4AC)]/[2] */
	root_first = fDivide(root_first, A); /*[b +- Sqrt(b^2 - 4AC)]/[2*A] */

	root_second = fDivide(root_second, ConvertToFraction(2)); /* [b +- Sqrt(b^2 - 4AC)]/[2] */
	root_second = fDivide(root_second, A); /*[b +- Sqrt(b^2 - 4AC)]/[2*A] */

	*(pRoots + 0) = root_first;
	*(pRoots + 1) = root_second;
पूर्ण

/* -----------------------------------------------------------------------------
 * SUPPORT FUNCTIONS
 * -----------------------------------------------------------------------------
 */

/* Conversion Functions */
अटल पूर्णांक GetReal (fInt A)
अणु
	वापस (A.full >> SHIFT_AMOUNT);
पूर्ण

अटल fInt Divide (पूर्णांक X, पूर्णांक Y)
अणु
	fInt A, B, Quotient;

	A.full = X << SHIFT_AMOUNT;
	B.full = Y << SHIFT_AMOUNT;

	Quotient = fDivide(A, B);

	वापस Quotient;
पूर्ण

अटल पूर्णांक uGetScaledDecimal (fInt A) /*Converts the fractional portion to whole पूर्णांकegers - Costly function */
अणु
	पूर्णांक dec[PRECISION];
	पूर्णांक i, scaledDecimal = 0, पंचांगp = A.partial.decimal;

	क्रम (i = 0; i < PRECISION; i++) अणु
		dec[i] = पंचांगp / (1 << SHIFT_AMOUNT);
		पंचांगp = पंचांगp - ((1 << SHIFT_AMOUNT)*dec[i]);
		पंचांगp *= 10;
		scaledDecimal = scaledDecimal + dec[i]*uPow(10, PRECISION - 1 -i);
	पूर्ण

	वापस scaledDecimal;
पूर्ण

अटल पूर्णांक uPow(पूर्णांक base, पूर्णांक घातer)
अणु
	अगर (घातer == 0)
		वापस 1;
	अन्यथा
		वापस (base)*uPow(base, घातer - 1);
पूर्ण

अटल पूर्णांक uAbs(पूर्णांक X)
अणु
	अगर (X < 0)
		वापस (X * -1);
	अन्यथा
		वापस X;
पूर्ण

अटल fInt fRoundUpByStepSize(fInt A, fInt fStepSize, bool error_term)
अणु
	fInt solution;

	solution = fDivide(A, fStepSize);
	solution.partial.decimal = 0; /*All fractional digits changes to 0 */

	अगर (error_term)
		solution.partial.real += 1; /*Error term of 1 added */

	solution = fMultiply(solution, fStepSize);
	solution = fAdd(solution, fStepSize);

	वापस solution;
पूर्ण

