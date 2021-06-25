<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
#समावेश "aux.h"

अटल स्थिर काष्ठा nvkm_i2c_aux_func
gf119_i2c_aux = अणु
	.address_only = true,
	.xfer = g94_i2c_aux_xfer,
पूर्ण;

पूर्णांक
gf119_i2c_aux_new(काष्ठा nvkm_i2c_pad *pad, पूर्णांक index, u8 drive,
		  काष्ठा nvkm_i2c_aux **paux)
अणु
	वापस g94_i2c_aux_new_(&gf119_i2c_aux, pad, index, drive, paux);
पूर्ण
