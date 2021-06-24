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
#समावेश "nv50.h"

#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_status[] = अणु
	अणु 0x00000001, "BUSY" पूर्ण, /* set when any bit is set */
	अणु 0x00000002, "DISPATCH" पूर्ण,
	अणु 0x00000004, "UNK2" पूर्ण,
	अणु 0x00000008, "UNK3" पूर्ण,
	अणु 0x00000010, "UNK4" पूर्ण,
	अणु 0x00000020, "UNK5" पूर्ण,
	अणु 0x00000040, "M2MF" पूर्ण,
	अणु 0x00000080, "UNK7" पूर्ण,
	अणु 0x00000100, "CTXPROG" पूर्ण,
	अणु 0x00000200, "VFETCH" पूर्ण,
	अणु 0x00000400, "CCACHE_PREGEOM" पूर्ण,
	अणु 0x00000800, "STRMOUT_VATTR_POSTGEOM" पूर्ण,
	अणु 0x00001000, "VCLIP" पूर्ण,
	अणु 0x00002000, "RATTR_APLANE" पूर्ण,
	अणु 0x00004000, "TRAST" पूर्ण,
	अणु 0x00008000, "CLIPID" पूर्ण,
	अणु 0x00010000, "ZCULL" पूर्ण,
	अणु 0x00020000, "ENG2D" पूर्ण,
	अणु 0x00040000, "RMASK" पूर्ण,
	अणु 0x00080000, "TPC_RAST" पूर्ण,
	अणु 0x00100000, "TPC_PROP" पूर्ण,
	अणु 0x00200000, "TPC_TEX" पूर्ण,
	अणु 0x00400000, "TPC_GEOM" पूर्ण,
	अणु 0x00800000, "TPC_MP" पूर्ण,
	अणु 0x01000000, "ROP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield
nv50_gr_vstatus_0[] = अणु
	अणु 0x01, "VFETCH" पूर्ण,
	अणु 0x02, "CCACHE" पूर्ण,
	अणु 0x04, "PREGEOM" पूर्ण,
	अणु 0x08, "POSTGEOM" पूर्ण,
	अणु 0x10, "VATTR" पूर्ण,
	अणु 0x20, "STRMOUT" पूर्ण,
	अणु 0x40, "VCLIP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield
nv50_gr_vstatus_1[] = अणु
	अणु 0x01, "TPC_RAST" पूर्ण,
	अणु 0x02, "TPC_PROP" पूर्ण,
	अणु 0x04, "TPC_TEX" पूर्ण,
	अणु 0x08, "TPC_GEOM" पूर्ण,
	अणु 0x10, "TPC_MP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield
nv50_gr_vstatus_2[] = अणु
	अणु 0x01, "RATTR" पूर्ण,
	अणु 0x02, "APLANE" पूर्ण,
	अणु 0x04, "TRAST" पूर्ण,
	अणु 0x08, "CLIPID" पूर्ण,
	अणु 0x10, "ZCULL" पूर्ण,
	अणु 0x20, "ENG2D" पूर्ण,
	अणु 0x40, "RMASK" पूर्ण,
	अणु 0x80, "ROP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nvkm_gr_vstatus_prपूर्णांक(काष्ठा nv50_gr *gr, पूर्णांक r,
		      स्थिर काष्ठा nvkm_bitfield *units, u32 status)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	u32 stat = status;
	u8  mask = 0x00;
	अक्षर msg[64];
	पूर्णांक i;

	क्रम (i = 0; units[i].name && status; i++) अणु
		अगर ((status & 7) == 1)
			mask |= (1 << i);
		status >>= 3;
	पूर्ण

	nvkm_snprपूर्णांकbf(msg, माप(msg), units, mask);
	nvkm_error(subdev, "PGRAPH_VSTATUS%d: %08x [%s]\n", r, stat, msg);
पूर्ण

पूर्णांक
g84_gr_tlb_flush(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv50_gr *gr = nv50_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_समयr *पंचांगr = device->समयr;
	bool idle, समयout = false;
	अचिन्हित दीर्घ flags;
	अक्षर status[128];
	u64 start;
	u32 पंचांगp;

	spin_lock_irqsave(&gr->lock, flags);
	nvkm_mask(device, 0x400500, 0x00000001, 0x00000000);

	start = nvkm_समयr_पढ़ो(पंचांगr);
	करो अणु
		idle = true;

		क्रम (पंचांगp = nvkm_rd32(device, 0x400380); पंचांगp && idle; पंचांगp >>= 3) अणु
			अगर ((पंचांगp & 7) == 1)
				idle = false;
		पूर्ण

		क्रम (पंचांगp = nvkm_rd32(device, 0x400384); पंचांगp && idle; पंचांगp >>= 3) अणु
			अगर ((पंचांगp & 7) == 1)
				idle = false;
		पूर्ण

		क्रम (पंचांगp = nvkm_rd32(device, 0x400388); पंचांगp && idle; पंचांगp >>= 3) अणु
			अगर ((पंचांगp & 7) == 1)
				idle = false;
		पूर्ण
	पूर्ण जबतक (!idle &&
		 !(समयout = nvkm_समयr_पढ़ो(पंचांगr) - start > 2000000000));

	अगर (समयout) अणु
		nvkm_error(subdev, "PGRAPH TLB flush idle timeout fail\n");

		पंचांगp = nvkm_rd32(device, 0x400700);
		nvkm_snprपूर्णांकbf(status, माप(status), nv50_gr_status, पंचांगp);
		nvkm_error(subdev, "PGRAPH_STATUS %08x [%s]\n", पंचांगp, status);

		nvkm_gr_vstatus_prपूर्णांक(gr, 0, nv50_gr_vstatus_0,
				       nvkm_rd32(device, 0x400380));
		nvkm_gr_vstatus_prपूर्णांक(gr, 1, nv50_gr_vstatus_1,
				       nvkm_rd32(device, 0x400384));
		nvkm_gr_vstatus_prपूर्णांक(gr, 2, nv50_gr_vstatus_2,
				       nvkm_rd32(device, 0x400388));
	पूर्ण


	nvkm_wr32(device, 0x100c80, 0x00000001);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x100c80) & 0x00000001))
			अवरोध;
	);
	nvkm_mask(device, 0x400500, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस समयout ? -EBUSY : 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
g84_gr = अणु
	.init = nv50_gr_init,
	.पूर्णांकr = nv50_gr_पूर्णांकr,
	.chan_new = nv50_gr_chan_new,
	.tlb_flush = g84_gr_tlb_flush,
	.units = nv50_gr_units,
	.sclass = अणु
		अणु -1, -1, NV_शून्य_CLASS, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_TWOD, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_MEMORY_TO_MEMORY_FORMAT, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_COMPUTE, &nv50_gr_object पूर्ण,
		अणु -1, -1, G82_TESLA, &nv50_gr_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g84_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv50_gr_new_(&g84_gr, device, type, inst, pgr);
पूर्ण
