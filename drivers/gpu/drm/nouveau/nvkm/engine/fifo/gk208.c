<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश "gk104.h"
#समावेश "changk104.h"

#समावेश <nvअगर/class.h>

व्योम
gk208_fअगरo_pbdma_init_समयout(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < fअगरo->pbdma_nr; i++)
		nvkm_wr32(device, 0x04012c + (i * 0x2000), 0x0000ffff);
पूर्ण

स्थिर काष्ठा gk104_fअगरo_pbdma_func
gk208_fअगरo_pbdma = अणु
	.nr = gk104_fअगरo_pbdma_nr,
	.init = gk104_fअगरo_pbdma_init,
	.init_समयout = gk208_fअगरo_pbdma_init_समयout,
पूर्ण;

अटल स्थिर काष्ठा gk104_fअगरo_func
gk208_fअगरo = अणु
	.पूर्णांकr.fault = gf100_fअगरo_पूर्णांकr_fault,
	.pbdma = &gk208_fअगरo_pbdma,
	.fault.access = gk104_fअगरo_fault_access,
	.fault.engine = gk104_fअगरo_fault_engine,
	.fault.reason = gk104_fअगरo_fault_reason,
	.fault.hubclient = gk104_fअगरo_fault_hubclient,
	.fault.gpcclient = gk104_fअगरo_fault_gpcclient,
	.runlist = &gk110_fअगरo_runlist,
	.chan = अणुअणु0,0,KEPLER_CHANNEL_GPFIFO_Aपूर्ण, gk104_fअगरo_gpfअगरo_new पूर्ण,
पूर्ण;

पूर्णांक
gk208_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस gk104_fअगरo_new_(&gk208_fअगरo, device, type, inst, 1024, pfअगरo);
पूर्ण
