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
#अगर_अघोषित PP_DEBUG_H
#घोषणा PP_DEBUG_H

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "amdgpu: [powerplay] " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#घोषणा PP_ASSERT_WITH_CODE(cond, msg, code)	\
	करो अणु					\
		अगर (!(cond)) अणु			\
			pr_warn_ratelimited("%s\n", msg);	\
			code;			\
		पूर्ण				\
	पूर्ण जबतक (0)

#घोषणा PP_ASSERT(cond, msg)	\
	करो अणु					\
		अगर (!(cond)) अणु			\
			pr_warn_ratelimited("%s\n", msg);	\
		पूर्ण				\
	पूर्ण जबतक (0)

#घोषणा PP_DBG_LOG(fmt, ...) \
	करो अणु \
		pr_debug(fmt, ##__VA_ARGS__); \
	पूर्ण जबतक (0)


#घोषणा GET_FLEXIBLE_ARRAY_MEMBER_ADDR(type, member, ptr, n)	\
	(type *)((अक्षर *)&(ptr)->member + (माप(type) * (n)))

#पूर्ण_अगर /* PP_DEBUG_H */

