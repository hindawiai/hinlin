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
 *
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "ior.h"

अटल स्थिर अक्षर *
nvkm_ior_name[] = अणु
	[DAC] = "DAC",
	[SOR] = "SOR",
	[PIOR] = "PIOR",
पूर्ण;

काष्ठा nvkm_ior *
nvkm_ior_find(काष्ठा nvkm_disp *disp, क्रमागत nvkm_ior_type type, पूर्णांक id)
अणु
	काष्ठा nvkm_ior *ior;
	list_क्रम_each_entry(ior, &disp->ior, head) अणु
		अगर (ior->type == type && (id < 0 || ior->id == id))
			वापस ior;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम
nvkm_ior_del(काष्ठा nvkm_ior **pior)
अणु
	काष्ठा nvkm_ior *ior = *pior;
	अगर (ior) अणु
		IOR_DBG(ior, "dtor");
		list_del(&ior->head);
		kमुक्त(*pior);
		*pior = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_ior_new_(स्थिर काष्ठा nvkm_ior_func *func, काष्ठा nvkm_disp *disp,
	      क्रमागत nvkm_ior_type type, पूर्णांक id)
अणु
	काष्ठा nvkm_ior *ior;
	अगर (!(ior = kzalloc(माप(*ior), GFP_KERNEL)))
		वापस -ENOMEM;
	ior->func = func;
	ior->disp = disp;
	ior->type = type;
	ior->id = id;
	snम_लिखो(ior->name, माप(ior->name), "%s-%d",
		 nvkm_ior_name[ior->type], ior->id);
	list_add_tail(&ior->head, &disp->ior);
	IOR_DBG(ior, "ctor");
	वापस 0;
पूर्ण
