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
#समावेश "head.h"

#समावेश <core/client.h>

#समावेश <nvअगर/cl0046.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nvkm_head *
nvkm_head_find(काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_head *head;
	list_क्रम_each_entry(head, &disp->head, head) अणु
		अगर (head->id == id)
			वापस head;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक
nvkm_head_mthd_scanoutpos(काष्ठा nvkm_object *object,
			  काष्ठा nvkm_head *head, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nv04_disp_scanoutpos_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "head scanoutpos size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "head scanoutpos vers %d\n",
			   args->v0.version);

		head->func->state(head, &head->arm);
		args->v0.vtotal  = head->arm.vtotal;
		args->v0.vblanks = head->arm.vblanks;
		args->v0.vblanke = head->arm.vblanke;
		args->v0.htotal  = head->arm.htotal;
		args->v0.hblanks = head->arm.hblanks;
		args->v0.hblanke = head->arm.hblanke;

		/* We करोn't support पढ़ोing htotal/vtotal on pre-NV50 VGA,
		 * so we have to give up and trigger the बारtamping
		 * fallback in the drm core.
		 */
		अगर (!args->v0.vtotal || !args->v0.htotal)
			वापस -ENOTSUPP;

		args->v0.समय[0] = kसमय_प्रकारo_ns(kसमय_get());
		head->func->rgpos(head, &args->v0.hline, &args->v0.vline);
		args->v0.समय[1] = kसमय_प्रकारo_ns(kसमय_get());
	पूर्ण अन्यथा
		वापस ret;

	वापस 0;
पूर्ण

व्योम
nvkm_head_del(काष्ठा nvkm_head **phead)
अणु
	काष्ठा nvkm_head *head = *phead;
	अगर (head) अणु
		HEAD_DBG(head, "dtor");
		list_del(&head->head);
		kमुक्त(*phead);
		*phead = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_head_new_(स्थिर काष्ठा nvkm_head_func *func,
	       काष्ठा nvkm_disp *disp, पूर्णांक id)
अणु
	काष्ठा nvkm_head *head;
	अगर (!(head = kzalloc(माप(*head), GFP_KERNEL)))
		वापस -ENOMEM;
	head->func = func;
	head->disp = disp;
	head->id = id;
	list_add_tail(&head->head, &disp->head);
	HEAD_DBG(head, "ctor");
	वापस 0;
पूर्ण
