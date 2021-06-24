<शैली गुरु>
/*
 * Copyright 2020 Red Hat Inc.
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
 */
#समावेश <nvअगर/समयr.h>
#समावेश <nvअगर/device.h>

s64
nvअगर_समयr_रुको_test(काष्ठा nvअगर_समयr_रुको *रुको)
अणु
	u64 समय = nvअगर_device_समय(रुको->device);

	अगर (रुको->पढ़ोs == 0) अणु
		रुको->समय0 = समय;
		रुको->समय1 = समय;
	पूर्ण

	अगर (रुको->समय1 == समय) अणु
		अगर (WARN_ON(रुको->पढ़ोs++ == 16))
			वापस -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		रुको->समय1 = समय;
		रुको->पढ़ोs = 1;
	पूर्ण

	अगर (रुको->समय1 - रुको->समय0 > रुको->limit)
		वापस -ETIMEDOUT;

	वापस रुको->समय1 - रुको->समय0;
पूर्ण

व्योम
nvअगर_समयr_रुको_init(काष्ठा nvअगर_device *device, u64 nsec,
		     काष्ठा nvअगर_समयr_रुको *रुको)
अणु
	रुको->device = device;
	रुको->limit = nsec;
	रुको->पढ़ोs = 0;
पूर्ण
