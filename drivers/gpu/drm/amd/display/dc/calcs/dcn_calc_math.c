<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#समावेश "dcn_calc_math.h"

#घोषणा isNaN(number) ((number) != (number))

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

भग्न dcn_bw_mod(स्थिर भग्न arg1, स्थिर भग्न arg2)
अणु
	अगर (isNaN(arg1))
		वापस arg2;
	अगर (isNaN(arg2))
		वापस arg1;
	वापस arg1 - arg1 * ((पूर्णांक) (arg1 / arg2));
पूर्ण

भग्न dcn_bw_min2(स्थिर भग्न arg1, स्थिर भग्न arg2)
अणु
	अगर (isNaN(arg1))
		वापस arg2;
	अगर (isNaN(arg2))
		वापस arg1;
	वापस arg1 < arg2 ? arg1 : arg2;
पूर्ण

अचिन्हित पूर्णांक dcn_bw_max(स्थिर अचिन्हित पूर्णांक arg1, स्थिर अचिन्हित पूर्णांक arg2)
अणु
	वापस arg1 > arg2 ? arg1 : arg2;
पूर्ण
भग्न dcn_bw_max2(स्थिर भग्न arg1, स्थिर भग्न arg2)
अणु
	अगर (isNaN(arg1))
		वापस arg2;
	अगर (isNaN(arg2))
		वापस arg1;
	वापस arg1 > arg2 ? arg1 : arg2;
पूर्ण

भग्न dcn_bw_न्यूनमान2(स्थिर भग्न arg, स्थिर भग्न signअगरicance)
अणु
	अगर (signअगरicance == 0)
		वापस 0;
	वापस ((पूर्णांक) (arg / signअगरicance)) * signअगरicance;
पूर्ण
भग्न dcn_bw_न्यूनमान(स्थिर भग्न arg)
अणु
	वापस ((पूर्णांक) (arg));
पूर्ण

भग्न dcn_bw_उच्चमान(स्थिर भग्न arg)
अणु
	भग्न flr = dcn_bw_न्यूनमान2(arg, 1);

	वापस flr + 0.00001 >= arg ? arg : flr + 1;
पूर्ण

भग्न dcn_bw_उच्चमान2(स्थिर भग्न arg, स्थिर भग्न signअगरicance)
अणु
	भग्न flr = dcn_bw_न्यूनमान2(arg, signअगरicance);
	अगर (signअगरicance == 0)
		वापस 0;
	वापस flr + 0.00001 >= arg ? arg : flr + signअगरicance;
पूर्ण

भग्न dcn_bw_max3(भग्न v1, भग्न v2, भग्न v3)
अणु
	वापस v3 > dcn_bw_max2(v1, v2) ? v3 : dcn_bw_max2(v1, v2);
पूर्ण

भग्न dcn_bw_max5(भग्न v1, भग्न v2, भग्न v3, भग्न v4, भग्न v5)
अणु
	वापस dcn_bw_max3(v1, v2, v3) > dcn_bw_max2(v4, v5) ? dcn_bw_max3(v1, v2, v3) : dcn_bw_max2(v4, v5);
पूर्ण

भग्न dcn_bw_घात(भग्न a, भग्न exp)
अणु
	भग्न temp;
	/*ASSERT(exp == (पूर्णांक)exp);*/
	अगर ((पूर्णांक)exp == 0)
		वापस 1;
	temp = dcn_bw_घात(a, (पूर्णांक)(exp / 2));
	अगर (((पूर्णांक)exp % 2) == 0) अणु
		वापस temp * temp;
	पूर्ण अन्यथा अणु
		अगर ((पूर्णांक)exp > 0)
			वापस a * temp * temp;
		अन्यथा
			वापस (temp * temp) / a;
	पूर्ण
पूर्ण

द्विगुन dcn_bw_भ_असल(द्विगुन a)
अणु
	अगर (a > 0)
		वापस (a);
	अन्यथा
		वापस (-a);
पूर्ण


भग्न dcn_bw_log(भग्न a, भग्न b)
अणु
	पूर्णांक * स्थिर exp_ptr = (पूर्णांक *)(&a);
	पूर्णांक x = *exp_ptr;
	स्थिर पूर्णांक log_2 = ((x >> 23) & 255) - 128;
	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptr = x;

	a = ((-1.0f / 3) * a + 2) * a - 2.0f / 3;

	अगर (b > 2.00001 || b < 1.99999)
		वापस (a + log_2) / dcn_bw_log(b, 2);
	अन्यथा
		वापस (a + log_2);
पूर्ण
