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

#समावेश <nvअगर/cl507b.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
nv50_disp_oimm_new_(स्थिर काष्ठा nv50_disp_chan_func *func,
		    काष्ठा nv50_disp *disp, पूर्णांक ctrl, पूर्णांक user,
		    स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nv50_disp_overlay_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_object *parent = oclass->parent;
	पूर्णांक head, ret = -ENOSYS;

	nvअगर_ioctl(parent, "create disp overlay size %d\n", argc);
	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create disp overlay vers %d head %d\n",
			   args->v0.version, args->v0.head);
		अगर (!nvkm_head_find(&disp->base, args->v0.head))
			वापस -EINVAL;
		head = args->v0.head;
	पूर्ण अन्यथा
		वापस ret;

	वापस nv50_disp_chan_new_(func, शून्य, disp, ctrl + head, user + head,
				   head, oclass, pobject);
पूर्ण

पूर्णांक
nv50_disp_oimm_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		   काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_oimm_new_(&nv50_disp_pioc_func, disp, 5, 5,
				   oclass, argv, argc, pobject);
पूर्ण
