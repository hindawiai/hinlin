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
#समावेश "chan.h"
#समावेश "nvsw.h"

#समावेश <nvअगर/class.h>

/*******************************************************************************
 * software context
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_sw_chan_func
nv10_sw_chan = अणु
पूर्ण;

अटल पूर्णांक
nv10_sw_chan_new(काष्ठा nvkm_sw *sw, काष्ठा nvkm_fअगरo_chan *fअगरo,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_sw_chan *chan;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->object;

	वापस nvkm_sw_chan_ctor(&nv10_sw_chan, sw, fअगरo, oclass, chan);
पूर्ण

/*******************************************************************************
 * software engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_sw_func
nv10_sw = अणु
	.chan_new = nv10_sw_chan_new,
	.sclass = अणु
		अणु nvkm_nvsw_new, अणु -1, -1, NVIF_CLASS_SW_NV10 पूर्ण पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv10_sw_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_sw **psw)
अणु
	वापस nvkm_sw_new_(&nv10_sw, device, type, inst, psw);
पूर्ण
