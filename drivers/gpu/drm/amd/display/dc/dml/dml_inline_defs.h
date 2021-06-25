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

#अगर_अघोषित __DML_INLINE_DEFS_H__
#घोषणा __DML_INLINE_DEFS_H__

#समावेश "dcn_calc_math.h"
#समावेश "dml_logger.h"

अटल अंतरभूत द्विगुन dml_min(द्विगुन a, द्विगुन b)
अणु
	वापस (द्विगुन) dcn_bw_min2(a, b);
पूर्ण

अटल अंतरभूत द्विगुन dml_min3(द्विगुन a, द्विगुन b, द्विगुन c)
अणु
	वापस dml_min(dml_min(a, b), c);
पूर्ण

अटल अंतरभूत द्विगुन dml_min4(द्विगुन a, द्विगुन b, द्विगुन c, द्विगुन d)
अणु
	वापस dml_min(dml_min(a, b), dml_min(c, d));
पूर्ण

अटल अंतरभूत द्विगुन dml_max(द्विगुन a, द्विगुन b)
अणु
	वापस (द्विगुन) dcn_bw_max2(a, b);
पूर्ण

अटल अंतरभूत द्विगुन dml_max3(द्विगुन a, द्विगुन b, द्विगुन c)
अणु
	वापस dml_max(dml_max(a, b), c);
पूर्ण

अटल अंतरभूत द्विगुन dml_max4(द्विगुन a, द्विगुन b, द्विगुन c, द्विगुन d)
अणु
	वापस dml_max(dml_max(a, b), dml_max(c, d));
पूर्ण

अटल अंतरभूत द्विगुन dml_max5(द्विगुन a, द्विगुन b, द्विगुन c, द्विगुन d, द्विगुन e)
अणु
	वापस dml_max(dml_max4(a, b, c, d), e);
पूर्ण

अटल अंतरभूत द्विगुन dml_उच्चमान(द्विगुन a, द्विगुन granularity)
अणु
	वापस (द्विगुन) dcn_bw_उच्चमान2(a, granularity);
पूर्ण

अटल अंतरभूत द्विगुन dml_न्यूनमान(द्विगुन a, द्विगुन granularity)
अणु
	वापस (द्विगुन) dcn_bw_न्यूनमान2(a, granularity);
पूर्ण

अटल अंतरभूत द्विगुन dml_round(द्विगुन a)
अणु
	द्विगुन round_pt = 0.5;
	द्विगुन उच्चमान = dml_उच्चमान(a, 1);
	द्विगुन न्यूनमान = dml_न्यूनमान(a, 1);

	अगर (a - न्यूनमान >= round_pt)
		वापस उच्चमान;
	अन्यथा
		वापस न्यूनमान;
पूर्ण

/* भग्न
अटल अंतरभूत पूर्णांक dml_log2(भग्न x)
अणु
	अचिन्हित पूर्णांक ix = *((अचिन्हित पूर्णांक *)&x);

	वापस (पूर्णांक)((ix >> 23) & 0xff) - 127;
पूर्ण*/

/* द्विगुन */
अटल अंतरभूत पूर्णांक dml_log2(द्विगुन x)
अणु
	अचिन्हित दीर्घ दीर्घ ix = *((अचिन्हित दीर्घ दीर्घ *)&x);

	वापस (पूर्णांक)((ix >> 52) & 0x7ff) - 1023;
पूर्ण

अटल अंतरभूत द्विगुन dml_घात(द्विगुन a, पूर्णांक exp)
अणु
	वापस (द्विगुन) dcn_bw_घात(a, exp);
पूर्ण

अटल अंतरभूत द्विगुन dml_भ_शेष(द्विगुन f, पूर्णांक val)
अणु
	वापस (द्विगुन) dcn_bw_mod(f, val);
पूर्ण

अटल अंतरभूत द्विगुन dml_उच्चमान_2(द्विगुन f)
अणु
	वापस (द्विगुन) dcn_bw_उच्चमान2(f, 2);
पूर्ण

अटल अंतरभूत द्विगुन dml_उच्चमान_ex(द्विगुन x, द्विगुन granularity)
अणु
	वापस (द्विगुन) dcn_bw_उच्चमान2(x, granularity);
पूर्ण

अटल अंतरभूत द्विगुन dml_न्यूनमान_ex(द्विगुन x, द्विगुन granularity)
अणु
	वापस (द्विगुन) dcn_bw_न्यूनमान2(x, granularity);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dml_round_to_multiple(अचिन्हित पूर्णांक num,
						 अचिन्हित पूर्णांक multiple,
						 अचिन्हित अक्षर up)
अणु
	अचिन्हित पूर्णांक reमुख्यder;

	अगर (multiple == 0)
		वापस num;

	reमुख्यder = num % multiple;

	अगर (reमुख्यder == 0)
		वापस num;

	अगर (up)
		वापस (num + multiple - reमुख्यder);
	अन्यथा
		वापस (num - reमुख्यder);
पूर्ण
अटल अंतरभूत द्विगुन dml_असल(द्विगुन a)
अणु
	अगर (a > 0)
		वापस a;
	अन्यथा
		वापस (a*(-1));
पूर्ण

#पूर्ण_अगर
