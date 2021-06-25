<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश <nvअगर/user.h>

अटल u64
nvअगर_userc361_समय(काष्ठा nvअगर_user *user)
अणु
	u32 hi, lo;

	करो अणु
		hi = nvअगर_rd32(&user->object, 0x084);
		lo = nvअगर_rd32(&user->object, 0x080);
	पूर्ण जबतक (hi != nvअगर_rd32(&user->object, 0x084));

	वापस ((u64)hi << 32 | lo);
पूर्ण

अटल व्योम
nvअगर_userc361_करोorbell(काष्ठा nvअगर_user *user, u32 token)
अणु
	nvअगर_wr32(&user->object, 0x90, token);
पूर्ण

स्थिर काष्ठा nvअगर_user_func
nvअगर_userc361 = अणु
	.करोorbell = nvअगर_userc361_करोorbell,
	.समय = nvअगर_userc361_समय,
पूर्ण;
