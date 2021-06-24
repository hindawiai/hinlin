<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __GK20A_VOLT_H__
#घोषणा __GK20A_VOLT_H__

काष्ठा cvb_coef अणु
	पूर्णांक c0;
	पूर्णांक c1;
	पूर्णांक c2;
	पूर्णांक c3;
	पूर्णांक c4;
	पूर्णांक c5;
पूर्ण;

काष्ठा gk20a_volt अणु
	काष्ठा nvkm_volt base;
	काष्ठा regulator *vdd;
पूर्ण;

पूर्णांक gk20a_volt_ctor(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type, पूर्णांक,
		    स्थिर काष्ठा cvb_coef *coefs, पूर्णांक nb_coefs,
		    पूर्णांक vmin, काष्ठा gk20a_volt *volt);

#पूर्ण_अगर
