<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

अटल पूर्णांक
nvkm_fannil_get(काष्ठा nvkm_therm *therm)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nvkm_fannil_set(काष्ठा nvkm_therm *therm, पूर्णांक percent)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक
nvkm_fannil_create(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_fan *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	therm->fan = priv;
	अगर (!priv)
		वापस -ENOMEM;

	priv->type = "none / external";
	priv->get = nvkm_fannil_get;
	priv->set = nvkm_fannil_set;
	वापस 0;
पूर्ण
