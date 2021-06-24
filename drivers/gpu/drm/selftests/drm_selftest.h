<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __DRM_SELFTEST_H__
#घोषणा __DRM_SELFTEST_H__

काष्ठा drm_subtest अणु
	पूर्णांक (*func)(व्योम *data);
	स्थिर अक्षर *name;
पूर्ण;

अटल पूर्णांक __drm_subtests(स्थिर अक्षर *caller,
			  स्थिर काष्ठा drm_subtest *st,
			  पूर्णांक count,
			  व्योम *data);
#घोषणा drm_subtests(T, data) \
	__drm_subtests(__func__, T, ARRAY_SIZE(T), data)

#घोषणा SUBTEST(x) अणु x, #x पूर्ण

#पूर्ण_अगर /* __DRM_SELFTEST_H__ */
