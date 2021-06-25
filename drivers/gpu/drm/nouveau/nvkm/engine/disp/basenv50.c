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
#समावेश "channv50.h"
#समावेश "head.h"

#समावेश <core/client.h>

#समावेश <nvअगर/cl507c.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
nv50_disp_base_new_(स्थिर काष्ठा nv50_disp_chan_func *func,
		    स्थिर काष्ठा nv50_disp_chan_mthd *mthd,
		    काष्ठा nv50_disp *disp, पूर्णांक chid,
		    स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nv50_disp_base_channel_dma_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_object *parent = oclass->parent;
	पूर्णांक head, ret = -ENOSYS;
	u64 push;

	nvअगर_ioctl(parent, "create disp base channel dma size %d\n", argc);
	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create disp base channel dma vers %d "
				   "pushbuf %016llx head %d\n",
			   args->v0.version, args->v0.pushbuf, args->v0.head);
		अगर (!nvkm_head_find(&disp->base, args->v0.head))
			वापस -EINVAL;
		push = args->v0.pushbuf;
		head = args->v0.head;
	पूर्ण अन्यथा
		वापस ret;

	वापस nv50_disp_dmac_new_(func, mthd, disp, chid + head,
				   head, push, oclass, pobject);
पूर्ण

अटल स्थिर काष्ठा nv50_disp_mthd_list
nv50_disp_base_mthd_base = अणु
	.mthd = 0x0000,
	.addr = 0x000000,
	.data = अणु
		अणु 0x0080, 0x000000 पूर्ण,
		अणु 0x0084, 0x0008c4 पूर्ण,
		अणु 0x0088, 0x0008d0 पूर्ण,
		अणु 0x008c, 0x0008dc पूर्ण,
		अणु 0x0090, 0x0008e4 पूर्ण,
		अणु 0x0094, 0x610884 पूर्ण,
		अणु 0x00a0, 0x6108a0 पूर्ण,
		अणु 0x00a4, 0x610878 पूर्ण,
		अणु 0x00c0, 0x61086c पूर्ण,
		अणु 0x00e0, 0x610858 पूर्ण,
		अणु 0x00e4, 0x610860 पूर्ण,
		अणु 0x00e8, 0x6108ac पूर्ण,
		अणु 0x00ec, 0x6108b4 पूर्ण,
		अणु 0x0100, 0x610894 पूर्ण,
		अणु 0x0110, 0x6108bc पूर्ण,
		अणु 0x0114, 0x61088c पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

स्थिर काष्ठा nv50_disp_mthd_list
nv50_disp_base_mthd_image = अणु
	.mthd = 0x0400,
	.addr = 0x000000,
	.data = अणु
		अणु 0x0800, 0x6108f0 पूर्ण,
		अणु 0x0804, 0x6108fc पूर्ण,
		अणु 0x0808, 0x61090c पूर्ण,
		अणु 0x080c, 0x610914 पूर्ण,
		अणु 0x0810, 0x610904 पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nv50_disp_chan_mthd
nv50_disp_base_mthd = अणु
	.name = "Base",
	.addr = 0x000540,
	.prev = 0x000004,
	.data = अणु
		अणु "Global", 1, &nv50_disp_base_mthd_base पूर्ण,
		अणु  "Image", 2, &nv50_disp_base_mthd_image पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv50_disp_base_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		   काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_base_new_(&nv50_disp_dmac_func, &nv50_disp_base_mthd,
				   disp, 1, oclass, argv, argc, pobject);
पूर्ण
