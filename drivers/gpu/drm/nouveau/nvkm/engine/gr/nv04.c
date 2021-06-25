<शैली गुरु>
/*
 * Copyright 2007 Stephane Marchesin
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragr) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "priv.h"
#समावेश "regs.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>
#समावेश <engine/fअगरo/chan.h>
#समावेश <subdev/insपंचांगem.h>
#समावेश <subdev/समयr.h>

अटल u32
nv04_gr_ctx_regs[] = अणु
	0x0040053c,
	0x00400544,
	0x00400540,
	0x00400548,
	NV04_PGRAPH_CTX_SWITCH1,
	NV04_PGRAPH_CTX_SWITCH2,
	NV04_PGRAPH_CTX_SWITCH3,
	NV04_PGRAPH_CTX_SWITCH4,
	NV04_PGRAPH_CTX_CACHE1,
	NV04_PGRAPH_CTX_CACHE2,
	NV04_PGRAPH_CTX_CACHE3,
	NV04_PGRAPH_CTX_CACHE4,
	0x00400184,
	0x004001a4,
	0x004001c4,
	0x004001e4,
	0x00400188,
	0x004001a8,
	0x004001c8,
	0x004001e8,
	0x0040018c,
	0x004001ac,
	0x004001cc,
	0x004001ec,
	0x00400190,
	0x004001b0,
	0x004001d0,
	0x004001f0,
	0x00400194,
	0x004001b4,
	0x004001d4,
	0x004001f4,
	0x00400198,
	0x004001b8,
	0x004001d8,
	0x004001f8,
	0x0040019c,
	0x004001bc,
	0x004001dc,
	0x004001fc,
	0x00400174,
	NV04_PGRAPH_DMA_START_0,
	NV04_PGRAPH_DMA_START_1,
	NV04_PGRAPH_DMA_LENGTH,
	NV04_PGRAPH_DMA_MISC,
	NV04_PGRAPH_DMA_PITCH,
	NV04_PGRAPH_BOFFSET0,
	NV04_PGRAPH_BBASE0,
	NV04_PGRAPH_BLIMIT0,
	NV04_PGRAPH_BOFFSET1,
	NV04_PGRAPH_BBASE1,
	NV04_PGRAPH_BLIMIT1,
	NV04_PGRAPH_BOFFSET2,
	NV04_PGRAPH_BBASE2,
	NV04_PGRAPH_BLIMIT2,
	NV04_PGRAPH_BOFFSET3,
	NV04_PGRAPH_BBASE3,
	NV04_PGRAPH_BLIMIT3,
	NV04_PGRAPH_BOFFSET4,
	NV04_PGRAPH_BBASE4,
	NV04_PGRAPH_BLIMIT4,
	NV04_PGRAPH_BOFFSET5,
	NV04_PGRAPH_BBASE5,
	NV04_PGRAPH_BLIMIT5,
	NV04_PGRAPH_BPITCH0,
	NV04_PGRAPH_BPITCH1,
	NV04_PGRAPH_BPITCH2,
	NV04_PGRAPH_BPITCH3,
	NV04_PGRAPH_BPITCH4,
	NV04_PGRAPH_SURFACE,
	NV04_PGRAPH_STATE,
	NV04_PGRAPH_BSWIZZLE2,
	NV04_PGRAPH_BSWIZZLE5,
	NV04_PGRAPH_BPIXEL,
	NV04_PGRAPH_NOTIFY,
	NV04_PGRAPH_PATT_COLOR0,
	NV04_PGRAPH_PATT_COLOR1,
	NV04_PGRAPH_PATT_COLORRAM+0x00,
	NV04_PGRAPH_PATT_COLORRAM+0x04,
	NV04_PGRAPH_PATT_COLORRAM+0x08,
	NV04_PGRAPH_PATT_COLORRAM+0x0c,
	NV04_PGRAPH_PATT_COLORRAM+0x10,
	NV04_PGRAPH_PATT_COLORRAM+0x14,
	NV04_PGRAPH_PATT_COLORRAM+0x18,
	NV04_PGRAPH_PATT_COLORRAM+0x1c,
	NV04_PGRAPH_PATT_COLORRAM+0x20,
	NV04_PGRAPH_PATT_COLORRAM+0x24,
	NV04_PGRAPH_PATT_COLORRAM+0x28,
	NV04_PGRAPH_PATT_COLORRAM+0x2c,
	NV04_PGRAPH_PATT_COLORRAM+0x30,
	NV04_PGRAPH_PATT_COLORRAM+0x34,
	NV04_PGRAPH_PATT_COLORRAM+0x38,
	NV04_PGRAPH_PATT_COLORRAM+0x3c,
	NV04_PGRAPH_PATT_COLORRAM+0x40,
	NV04_PGRAPH_PATT_COLORRAM+0x44,
	NV04_PGRAPH_PATT_COLORRAM+0x48,
	NV04_PGRAPH_PATT_COLORRAM+0x4c,
	NV04_PGRAPH_PATT_COLORRAM+0x50,
	NV04_PGRAPH_PATT_COLORRAM+0x54,
	NV04_PGRAPH_PATT_COLORRAM+0x58,
	NV04_PGRAPH_PATT_COLORRAM+0x5c,
	NV04_PGRAPH_PATT_COLORRAM+0x60,
	NV04_PGRAPH_PATT_COLORRAM+0x64,
	NV04_PGRAPH_PATT_COLORRAM+0x68,
	NV04_PGRAPH_PATT_COLORRAM+0x6c,
	NV04_PGRAPH_PATT_COLORRAM+0x70,
	NV04_PGRAPH_PATT_COLORRAM+0x74,
	NV04_PGRAPH_PATT_COLORRAM+0x78,
	NV04_PGRAPH_PATT_COLORRAM+0x7c,
	NV04_PGRAPH_PATT_COLORRAM+0x80,
	NV04_PGRAPH_PATT_COLORRAM+0x84,
	NV04_PGRAPH_PATT_COLORRAM+0x88,
	NV04_PGRAPH_PATT_COLORRAM+0x8c,
	NV04_PGRAPH_PATT_COLORRAM+0x90,
	NV04_PGRAPH_PATT_COLORRAM+0x94,
	NV04_PGRAPH_PATT_COLORRAM+0x98,
	NV04_PGRAPH_PATT_COLORRAM+0x9c,
	NV04_PGRAPH_PATT_COLORRAM+0xa0,
	NV04_PGRAPH_PATT_COLORRAM+0xa4,
	NV04_PGRAPH_PATT_COLORRAM+0xa8,
	NV04_PGRAPH_PATT_COLORRAM+0xac,
	NV04_PGRAPH_PATT_COLORRAM+0xb0,
	NV04_PGRAPH_PATT_COLORRAM+0xb4,
	NV04_PGRAPH_PATT_COLORRAM+0xb8,
	NV04_PGRAPH_PATT_COLORRAM+0xbc,
	NV04_PGRAPH_PATT_COLORRAM+0xc0,
	NV04_PGRAPH_PATT_COLORRAM+0xc4,
	NV04_PGRAPH_PATT_COLORRAM+0xc8,
	NV04_PGRAPH_PATT_COLORRAM+0xcc,
	NV04_PGRAPH_PATT_COLORRAM+0xd0,
	NV04_PGRAPH_PATT_COLORRAM+0xd4,
	NV04_PGRAPH_PATT_COLORRAM+0xd8,
	NV04_PGRAPH_PATT_COLORRAM+0xdc,
	NV04_PGRAPH_PATT_COLORRAM+0xe0,
	NV04_PGRAPH_PATT_COLORRAM+0xe4,
	NV04_PGRAPH_PATT_COLORRAM+0xe8,
	NV04_PGRAPH_PATT_COLORRAM+0xec,
	NV04_PGRAPH_PATT_COLORRAM+0xf0,
	NV04_PGRAPH_PATT_COLORRAM+0xf4,
	NV04_PGRAPH_PATT_COLORRAM+0xf8,
	NV04_PGRAPH_PATT_COLORRAM+0xfc,
	NV04_PGRAPH_PATTERN,
	0x0040080c,
	NV04_PGRAPH_PATTERN_SHAPE,
	0x00400600,
	NV04_PGRAPH_ROP3,
	NV04_PGRAPH_CHROMA,
	NV04_PGRAPH_BETA_AND,
	NV04_PGRAPH_BETA_PREMULT,
	NV04_PGRAPH_CONTROL0,
	NV04_PGRAPH_CONTROL1,
	NV04_PGRAPH_CONTROL2,
	NV04_PGRAPH_BLEND,
	NV04_PGRAPH_STORED_FMT,
	NV04_PGRAPH_SOURCE_COLOR,
	0x00400560,
	0x00400568,
	0x00400564,
	0x0040056c,
	0x00400400,
	0x00400480,
	0x00400404,
	0x00400484,
	0x00400408,
	0x00400488,
	0x0040040c,
	0x0040048c,
	0x00400410,
	0x00400490,
	0x00400414,
	0x00400494,
	0x00400418,
	0x00400498,
	0x0040041c,
	0x0040049c,
	0x00400420,
	0x004004a0,
	0x00400424,
	0x004004a4,
	0x00400428,
	0x004004a8,
	0x0040042c,
	0x004004ac,
	0x00400430,
	0x004004b0,
	0x00400434,
	0x004004b4,
	0x00400438,
	0x004004b8,
	0x0040043c,
	0x004004bc,
	0x00400440,
	0x004004c0,
	0x00400444,
	0x004004c4,
	0x00400448,
	0x004004c8,
	0x0040044c,
	0x004004cc,
	0x00400450,
	0x004004d0,
	0x00400454,
	0x004004d4,
	0x00400458,
	0x004004d8,
	0x0040045c,
	0x004004dc,
	0x00400460,
	0x004004e0,
	0x00400464,
	0x004004e4,
	0x00400468,
	0x004004e8,
	0x0040046c,
	0x004004ec,
	0x00400470,
	0x004004f0,
	0x00400474,
	0x004004f4,
	0x00400478,
	0x004004f8,
	0x0040047c,
	0x004004fc,
	0x00400534,
	0x00400538,
	0x00400514,
	0x00400518,
	0x0040051c,
	0x00400520,
	0x00400524,
	0x00400528,
	0x0040052c,
	0x00400530,
	0x00400d00,
	0x00400d40,
	0x00400d80,
	0x00400d04,
	0x00400d44,
	0x00400d84,
	0x00400d08,
	0x00400d48,
	0x00400d88,
	0x00400d0c,
	0x00400d4c,
	0x00400d8c,
	0x00400d10,
	0x00400d50,
	0x00400d90,
	0x00400d14,
	0x00400d54,
	0x00400d94,
	0x00400d18,
	0x00400d58,
	0x00400d98,
	0x00400d1c,
	0x00400d5c,
	0x00400d9c,
	0x00400d20,
	0x00400d60,
	0x00400da0,
	0x00400d24,
	0x00400d64,
	0x00400da4,
	0x00400d28,
	0x00400d68,
	0x00400da8,
	0x00400d2c,
	0x00400d6c,
	0x00400dac,
	0x00400d30,
	0x00400d70,
	0x00400db0,
	0x00400d34,
	0x00400d74,
	0x00400db4,
	0x00400d38,
	0x00400d78,
	0x00400db8,
	0x00400d3c,
	0x00400d7c,
	0x00400dbc,
	0x00400590,
	0x00400594,
	0x00400598,
	0x0040059c,
	0x004005a8,
	0x004005ac,
	0x004005b0,
	0x004005b4,
	0x004005c0,
	0x004005c4,
	0x004005c8,
	0x004005cc,
	0x004005d0,
	0x004005d4,
	0x004005d8,
	0x004005dc,
	0x004005e0,
	NV04_PGRAPH_PASSTHRU_0,
	NV04_PGRAPH_PASSTHRU_1,
	NV04_PGRAPH_PASSTHRU_2,
	NV04_PGRAPH_DVD_COLORFMT,
	NV04_PGRAPH_SCALED_FORMAT,
	NV04_PGRAPH_MISC24_0,
	NV04_PGRAPH_MISC24_1,
	NV04_PGRAPH_MISC24_2,
	0x00400500,
	0x00400504,
	NV04_PGRAPH_VALID1,
	NV04_PGRAPH_VALID2,
	NV04_PGRAPH_DEBUG_3
पूर्ण;

#घोषणा nv04_gr(p) container_of((p), काष्ठा nv04_gr, base)

काष्ठा nv04_gr अणु
	काष्ठा nvkm_gr base;
	काष्ठा nv04_gr_chan *chan[16];
	spinlock_t lock;
पूर्ण;

#घोषणा nv04_gr_chan(p) container_of((p), काष्ठा nv04_gr_chan, object)

काष्ठा nv04_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv04_gr *gr;
	पूर्णांक chid;
	u32 nv04[ARRAY_SIZE(nv04_gr_ctx_regs)];
पूर्ण;

/*******************************************************************************
 * Graphics object classes
 ******************************************************************************/

/*
 * Software methods, why they are needed, and how they all work:
 *
 * NV04 and NV05 keep most of the state in PGRAPH context itself, but some
 * 2d engine settings are kept inside the grobjs themselves. The grobjs are
 * 3 words दीर्घ on both. grobj क्रमmat on NV04 is:
 *
 * word 0:
 *  - bits 0-7: class
 *  - bit 12: color key active
 *  - bit 13: clip rect active
 *  - bit 14: अगर set, destination surface is swizzled and taken from buffer 5
 *            [set by NV04_SWIZZLED_SURFACE], otherwise it's linear and taken
 *            from buffer 0 [set by NV04_CONTEXT_SURFACES_2D or
 *            NV03_CONTEXT_SURFACE_DST].
 *  - bits 15-17: 2d operation [aka patch config]
 *  - bit 24: patch valid [enables rendering using this object]
 *  - bit 25: surf3d valid [क्रम tex_tri and multitex_tri only]
 * word 1:
 *  - bits 0-1: mono क्रमmat
 *  - bits 8-13: color क्रमmat
 *  - bits 16-31: DMA_NOTIFY instance
 * word 2:
 *  - bits 0-15: DMA_A instance
 *  - bits 16-31: DMA_B instance
 *
 * On NV05 it's:
 *
 * word 0:
 *  - bits 0-7: class
 *  - bit 12: color key active
 *  - bit 13: clip rect active
 *  - bit 14: अगर set, destination surface is swizzled and taken from buffer 5
 *            [set by NV04_SWIZZLED_SURFACE], otherwise it's linear and taken
 *            from buffer 0 [set by NV04_CONTEXT_SURFACES_2D or
 *            NV03_CONTEXT_SURFACE_DST].
 *  - bits 15-17: 2d operation [aka patch config]
 *  - bits 20-22: dither mode
 *  - bit 24: patch valid [enables rendering using this object]
 *  - bit 25: surface_dst/surface_color/surf2d/surf3d valid
 *  - bit 26: surface_src/surface_zeta valid
 *  - bit 27: pattern valid
 *  - bit 28: rop valid
 *  - bit 29: beta1 valid
 *  - bit 30: beta4 valid
 * word 1:
 *  - bits 0-1: mono क्रमmat
 *  - bits 8-13: color क्रमmat
 *  - bits 16-31: DMA_NOTIFY instance
 * word 2:
 *  - bits 0-15: DMA_A instance
 *  - bits 16-31: DMA_B instance
 *
 * NV05 will set/unset the relevant valid bits when you poke the relevant
 * object-binding methods with object of the proper type, or with the शून्य
 * type. It'll only allow rendering using the grobj अगर all needed objects
 * are bound. The needed set of objects depends on selected operation: क्रम
 * example rop object is needed by ROP_AND, but not by SRCCOPY_AND.
 *
 * NV04 करोesn't have these methods implemented at all, and doesn't have the
 * relevant bits in grobj. Instead, it'll allow rendering whenever bit 24
 * is set. So we have to emulate them in software, पूर्णांकernally keeping the
 * same bits as NV05 करोes. Since grobjs are aligned to 16 bytes on nv04,
 * but the last word isn't actually used क्रम anything, we abuse it क्रम this
 * purpose.
 *
 * Actually, NV05 can optionally check bit 24 too, but we disable this since
 * there's no use क्रम it.
 *
 * For unknown reasons, NV04 implements surf3d binding in hardware as an
 * exception. Also क्रम unknown reasons, NV04 करोesn't implement the clipping
 * methods on the surf3d object, so we have to emulate them too.
 */

अटल व्योम
nv04_gr_set_ctx1(काष्ठा nvkm_device *device, u32 inst, u32 mask, u32 value)
अणु
	पूर्णांक subc = (nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR) >> 13) & 0x7;
	u32 पंचांगp;

	पंचांगp  = nvkm_rd32(device, 0x700000 + inst);
	पंचांगp &= ~mask;
	पंचांगp |= value;
	nvkm_wr32(device, 0x700000 + inst, पंचांगp);

	nvkm_wr32(device, NV04_PGRAPH_CTX_SWITCH1, पंचांगp);
	nvkm_wr32(device, NV04_PGRAPH_CTX_CACHE1 + (subc << 2), पंचांगp);
पूर्ण

अटल व्योम
nv04_gr_set_ctx_val(काष्ठा nvkm_device *device, u32 inst, u32 mask, u32 value)
अणु
	पूर्णांक class, op, valid = 1;
	u32 पंचांगp, ctx1;

	ctx1 = nvkm_rd32(device, 0x700000 + inst);
	class = ctx1 & 0xff;
	op = (ctx1 >> 15) & 7;

	पंचांगp = nvkm_rd32(device, 0x70000c + inst);
	पंचांगp &= ~mask;
	पंचांगp |= value;
	nvkm_wr32(device, 0x70000c + inst, पंचांगp);

	/* check क्रम valid surf2d/surf_dst/surf_color */
	अगर (!(पंचांगp & 0x02000000))
		valid = 0;
	/* check क्रम valid surf_src/surf_zeta */
	अगर ((class == 0x1f || class == 0x48) && !(पंचांगp & 0x04000000))
		valid = 0;

	चयन (op) अणु
	/* SRCCOPY_AND, SRCCOPY: no extra objects required */
	हाल 0:
	हाल 3:
		अवरोध;
	/* ROP_AND: requires pattern and rop */
	हाल 1:
		अगर (!(पंचांगp & 0x18000000))
			valid = 0;
		अवरोध;
	/* BLEND_AND: requires beta1 */
	हाल 2:
		अगर (!(पंचांगp & 0x20000000))
			valid = 0;
		अवरोध;
	/* SRCCOPY_PREMULT, BLEND_PREMULT: beta4 required */
	हाल 4:
	हाल 5:
		अगर (!(पंचांगp & 0x40000000))
			valid = 0;
		अवरोध;
	पूर्ण

	nv04_gr_set_ctx1(device, inst, 0x01000000, valid << 24);
पूर्ण

अटल bool
nv04_gr_mthd_set_operation(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	u8 class = nvkm_rd32(device, 0x700000) & 0x000000ff;
	अगर (data > 5)
		वापस false;
	/* Old versions of the objects only accept first three operations. */
	अगर (data > 2 && class < 0x40)
		वापस false;
	nv04_gr_set_ctx1(device, inst, 0x00038000, data << 15);
	/* changing operation changes set of objects needed क्रम validation */
	nv04_gr_set_ctx_val(device, inst, 0, 0);
	वापस true;
पूर्ण

अटल bool
nv04_gr_mthd_surf3d_clip_h(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	अगर (min & 0x8000)
		/* too large */
		वापस false;
	अगर (w & 0x8000)
		/* yes, it accepts negative क्रम some reason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nvkm_wr32(device, 0x40053c, min);
	nvkm_wr32(device, 0x400544, max);
	वापस true;
पूर्ण

अटल bool
nv04_gr_mthd_surf3d_clip_v(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	अगर (min & 0x8000)
		/* too large */
		वापस false;
	अगर (w & 0x8000)
		/* yes, it accepts negative क्रम some reason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nvkm_wr32(device, 0x400540, min);
	nvkm_wr32(device, 0x400548, max);
	वापस true;
पूर्ण

अटल u8
nv04_gr_mthd_bind_class(काष्ठा nvkm_device *device, u32 inst)
अणु
	वापस nvkm_rd32(device, 0x700000 + (inst << 4));
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf2d(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0);
		वापस true;
	हाल 0x42:
		nv04_gr_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0x02000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf2d_swzsurf(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0);
		वापस true;
	हाल 0x42:
		nv04_gr_set_ctx1(device, inst, 0x00004000, 0);
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0x02000000);
		वापस true;
	हाल 0x52:
		nv04_gr_set_ctx1(device, inst, 0x00004000, 0x00004000);
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0x02000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv01_gr_mthd_bind_patt(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x08000000, 0);
		वापस true;
	हाल 0x18:
		nv04_gr_set_ctx_val(device, inst, 0x08000000, 0x08000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_patt(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x08000000, 0);
		वापस true;
	हाल 0x44:
		nv04_gr_set_ctx_val(device, inst, 0x08000000, 0x08000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_rop(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x10000000, 0);
		वापस true;
	हाल 0x43:
		nv04_gr_set_ctx_val(device, inst, 0x10000000, 0x10000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_beta1(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x20000000, 0);
		वापस true;
	हाल 0x12:
		nv04_gr_set_ctx_val(device, inst, 0x20000000, 0x20000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_beta4(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x40000000, 0);
		वापस true;
	हाल 0x72:
		nv04_gr_set_ctx_val(device, inst, 0x40000000, 0x40000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf_dst(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0);
		वापस true;
	हाल 0x58:
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0x02000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf_src(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0);
		वापस true;
	हाल 0x59:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0x04000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf_color(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0);
		वापस true;
	हाल 0x5a:
		nv04_gr_set_ctx_val(device, inst, 0x02000000, 0x02000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv04_gr_mthd_bind_surf_zeta(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0);
		वापस true;
	हाल 0x5b:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0x04000000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv01_gr_mthd_bind_clip(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx1(device, inst, 0x2000, 0);
		वापस true;
	हाल 0x19:
		nv04_gr_set_ctx1(device, inst, 0x2000, 0x2000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv01_gr_mthd_bind_chroma(काष्ठा nvkm_device *device, u32 inst, u32 data)
अणु
	चयन (nv04_gr_mthd_bind_class(device, data)) अणु
	हाल 0x30:
		nv04_gr_set_ctx1(device, inst, 0x1000, 0);
		वापस true;
	/* Yes, क्रम some reason even the old versions of objects
	 * accept 0x57 and not 0x17. Consistency be damned.
	 */
	हाल 0x57:
		nv04_gr_set_ctx1(device, inst, 0x1000, 0x1000);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
nv03_gr_mthd_gdi(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x0188: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_gdi(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0188: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv01_gr_mthd_blit(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x018c: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x019c: func = nv04_gr_mthd_bind_surf_src; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_blit(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x019c: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_iअगरc(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0188: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x018c: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x019c: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x01a0: func = nv04_gr_mthd_bind_surf2d_swzsurf; अवरोध;
	हाल 0x03e4: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv01_gr_mthd_अगरc(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x018c: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_अगरc(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x019c: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv03_gr_mthd_sअगरc(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_sअगरc(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_chroma; अवरोध;
	हाल 0x0188: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv03_gr_mthd_sअगरm(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0188: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x0304: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_sअगरm(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0188: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x0304: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_surf3d(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x02f8: func = nv04_gr_mthd_surf3d_clip_h; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_surf3d_clip_v; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv03_gr_mthd_ttri(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0188: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_surf_color; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_surf_zeta; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv01_gr_mthd_prim(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x0188: func = nv01_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_surf_dst; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd_prim(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32);
	चयन (mthd) अणु
	हाल 0x0184: func = nv01_gr_mthd_bind_clip; अवरोध;
	हाल 0x0188: func = nv04_gr_mthd_bind_patt; अवरोध;
	हाल 0x018c: func = nv04_gr_mthd_bind_rop; अवरोध;
	हाल 0x0190: func = nv04_gr_mthd_bind_beta1; अवरोध;
	हाल 0x0194: func = nv04_gr_mthd_bind_beta4; अवरोध;
	हाल 0x0198: func = nv04_gr_mthd_bind_surf2d; अवरोध;
	हाल 0x02fc: func = nv04_gr_mthd_set_operation; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, data);
पूर्ण

अटल bool
nv04_gr_mthd(काष्ठा nvkm_device *device, u32 inst, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nvkm_device *, u32, u32, u32);
	चयन (nvkm_rd32(device, 0x700000 + inst) & 0x000000ff) अणु
	हाल 0x1c ... 0x1e:
		   func = nv01_gr_mthd_prim; अवरोध;
	हाल 0x1f: func = nv01_gr_mthd_blit; अवरोध;
	हाल 0x21: func = nv01_gr_mthd_अगरc; अवरोध;
	हाल 0x36: func = nv03_gr_mthd_sअगरc; अवरोध;
	हाल 0x37: func = nv03_gr_mthd_sअगरm; अवरोध;
	हाल 0x48: func = nv03_gr_mthd_ttri; अवरोध;
	हाल 0x4a: func = nv04_gr_mthd_gdi; अवरोध;
	हाल 0x4b: func = nv03_gr_mthd_gdi; अवरोध;
	हाल 0x53: func = nv04_gr_mthd_surf3d; अवरोध;
	हाल 0x5c ... 0x5e:
		   func = nv04_gr_mthd_prim; अवरोध;
	हाल 0x5f: func = nv04_gr_mthd_blit; अवरोध;
	हाल 0x60: func = nv04_gr_mthd_iअगरc; अवरोध;
	हाल 0x61: func = nv04_gr_mthd_अगरc; अवरोध;
	हाल 0x76: func = nv04_gr_mthd_sअगरc; अवरोध;
	हाल 0x77: func = nv04_gr_mthd_sअगरm; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(device, inst, mthd, data);
पूर्ण

अटल पूर्णांक
nv04_gr_object_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		    पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 16, align,
				  false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
#अगर_घोषित __BIG_ENDIAN
		nvkm_mo32(*pgpuobj, 0x00, 0x00080000, 0x00080000);
#पूर्ण_अगर
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_object_func
nv04_gr_object = अणु
	.bind = nv04_gr_object_bind,
पूर्ण;

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल काष्ठा nv04_gr_chan *
nv04_gr_channel(काष्ठा nv04_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nv04_gr_chan *chan = शून्य;
	अगर (nvkm_rd32(device, NV04_PGRAPH_CTX_CONTROL) & 0x00010000) अणु
		पूर्णांक chid = nvkm_rd32(device, NV04_PGRAPH_CTX_USER) >> 24;
		अगर (chid < ARRAY_SIZE(gr->chan))
			chan = gr->chan[chid];
	पूर्ण
	वापस chan;
पूर्ण

अटल पूर्णांक
nv04_gr_load_context(काष्ठा nv04_gr_chan *chan, पूर्णांक chid)
अणु
	काष्ठा nvkm_device *device = chan->gr->base.engine.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nv04_gr_ctx_regs); i++)
		nvkm_wr32(device, nv04_gr_ctx_regs[i], chan->nv04[i]);

	nvkm_wr32(device, NV04_PGRAPH_CTX_CONTROL, 0x10010100);
	nvkm_mask(device, NV04_PGRAPH_CTX_USER, 0xff000000, chid << 24);
	nvkm_mask(device, NV04_PGRAPH_FFINTFC_ST2, 0xfff00000, 0x00000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv04_gr_unload_context(काष्ठा nv04_gr_chan *chan)
अणु
	काष्ठा nvkm_device *device = chan->gr->base.engine.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nv04_gr_ctx_regs); i++)
		chan->nv04[i] = nvkm_rd32(device, nv04_gr_ctx_regs[i]);

	nvkm_wr32(device, NV04_PGRAPH_CTX_CONTROL, 0x10000000);
	nvkm_mask(device, NV04_PGRAPH_CTX_USER, 0xff000000, 0x0f000000);
	वापस 0;
पूर्ण

अटल व्योम
nv04_gr_context_चयन(काष्ठा nv04_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nv04_gr_chan *prev = शून्य;
	काष्ठा nv04_gr_chan *next = शून्य;
	पूर्णांक chid;

	nv04_gr_idle(&gr->base);

	/* If previous context is valid, we need to save it */
	prev = nv04_gr_channel(gr);
	अगर (prev)
		nv04_gr_unload_context(prev);

	/* load context क्रम next channel */
	chid = (nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR) >> 24) & 0x0f;
	next = gr->chan[chid];
	अगर (next)
		nv04_gr_load_context(next, chid);
पूर्ण

अटल u32 *ctx_reg(काष्ठा nv04_gr_chan *chan, u32 reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nv04_gr_ctx_regs); i++) अणु
		अगर (nv04_gr_ctx_regs[i] == reg)
			वापस &chan->nv04[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *
nv04_gr_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv04_gr_chan *chan = nv04_gr_chan(object);
	काष्ठा nv04_gr *gr = chan->gr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = शून्य;
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस chan;
पूर्ण

अटल पूर्णांक
nv04_gr_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nv04_gr_chan *chan = nv04_gr_chan(object);
	काष्ठा nv04_gr *gr = chan->gr;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);
	अगर (nv04_gr_channel(gr) == chan)
		nv04_gr_unload_context(chan);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv04_gr_chan = अणु
	.dtor = nv04_gr_chan_dtor,
	.fini = nv04_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv04_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv04_gr *gr = nv04_gr(base);
	काष्ठा nv04_gr_chan *chan;
	अचिन्हित दीर्घ flags;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv04_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	*ctx_reg(chan, NV04_PGRAPH_DEBUG_3) = 0xfad4ff31;

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = chan;
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

bool
nv04_gr_idle(काष्ठा nvkm_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = 0xffffffff;

	अगर (device->card_type == NV_40)
		mask &= ~NV40_PGRAPH_STATUS_SYNC_STALL;

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, NV04_PGRAPH_STATUS) & mask))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "idle timed out with status %08x\n",
			   nvkm_rd32(device, NV04_PGRAPH_STATUS));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा nvkm_bitfield
nv04_gr_पूर्णांकr_name[] = अणु
	अणु NV_PGRAPH_INTR_NOTIFY, "NOTIFY" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield
nv04_gr_nstatus[] = अणु
	अणु NV04_PGRAPH_NSTATUS_STATE_IN_USE,       "STATE_IN_USE" पूर्ण,
	अणु NV04_PGRAPH_NSTATUS_INVALID_STATE,      "INVALID_STATE" पूर्ण,
	अणु NV04_PGRAPH_NSTATUS_BAD_ARGUMENT,       "BAD_ARGUMENT" पूर्ण,
	अणु NV04_PGRAPH_NSTATUS_PROTECTION_FAULT,   "PROTECTION_FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_bitfield
nv04_gr_nsource[] = अणु
	अणु NV03_PGRAPH_NSOURCE_NOTIFICATION,       "NOTIFICATION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DATA_ERROR,         "DATA_ERROR" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_PROTECTION_ERROR,   "PROTECTION_ERROR" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_RANGE_EXCEPTION,    "RANGE_EXCEPTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_LIMIT_COLOR,        "LIMIT_COLOR" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_LIMIT_ZETA,         "LIMIT_ZETA" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD,       "ILLEGAL_MTHD" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DMA_R_PROTECTION,   "DMA_R_PROTECTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DMA_W_PROTECTION,   "DMA_W_PROTECTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_FORMAT_EXCEPTION,   "FORMAT_EXCEPTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_PATCH_EXCEPTION,    "PATCH_EXCEPTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_STATE_INVALID,      "STATE_INVALID" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DOUBLE_NOTIFY,      "DOUBLE_NOTIFY" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_NOTIFY_IN_USE,      "NOTIFY_IN_USE" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_METHOD_CNT,         "METHOD_CNT" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_BFR_NOTIFICATION,   "BFR_NOTIFICATION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION, "DMA_VTX_PROTECTION" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DMA_WIDTH_A,        "DMA_WIDTH_A" पूर्ण,
	अणु NV03_PGRAPH_NSOURCE_DMA_WIDTH_B,        "DMA_WIDTH_B" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv04_gr_पूर्णांकr(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv04_gr *gr = nv04_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, NV03_PGRAPH_INTR);
	u32 nsource = nvkm_rd32(device, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nvkm_rd32(device, NV03_PGRAPH_NSTATUS);
	u32 addr = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR);
	u32 chid = (addr & 0x0f000000) >> 24;
	u32 subc = (addr & 0x0000e000) >> 13;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nvkm_rd32(device, 0x400180 + subc * 4) & 0xff;
	u32 inst = (nvkm_rd32(device, 0x40016c) & 0xffff) << 4;
	u32 show = stat;
	अक्षर msg[128], src[128], sta[128];
	काष्ठा nv04_gr_chan *chan;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	chan = gr->chan[chid];

	अगर (stat & NV_PGRAPH_INTR_NOTIFY) अणु
		अगर (chan && (nsource & NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD)) अणु
			अगर (!nv04_gr_mthd(device, inst, mthd, data))
				show &= ~NV_PGRAPH_INTR_NOTIFY;
		पूर्ण
	पूर्ण

	अगर (stat & NV_PGRAPH_INTR_CONTEXT_SWITCH) अणु
		nvkm_wr32(device, NV03_PGRAPH_INTR, NV_PGRAPH_INTR_CONTEXT_SWITCH);
		stat &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		show &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		nv04_gr_context_चयन(gr);
	पूर्ण

	nvkm_wr32(device, NV03_PGRAPH_INTR, stat);
	nvkm_wr32(device, NV04_PGRAPH_FIFO, 0x00000001);

	अगर (show) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), nv04_gr_पूर्णांकr_name, show);
		nvkm_snprपूर्णांकbf(src, माप(src), nv04_gr_nsource, nsource);
		nvkm_snprपूर्णांकbf(sta, माप(sta), nv04_gr_nstatus, nstatus);
		nvkm_error(subdev, "intr %08x [%s] nsource %08x [%s] "
				   "nstatus %08x [%s] ch %d [%s] subc %d "
				   "class %04x mthd %04x data %08x\n",
			   show, msg, nsource, src, nstatus, sta, chid,
			   chan ? chan->object.client->name : "unknown",
			   subc, class, mthd, data);
	पूर्ण

	spin_unlock_irqrestore(&gr->lock, flags);
पूर्ण

अटल पूर्णांक
nv04_gr_init(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv04_gr *gr = nv04_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	/* Enable PGRAPH पूर्णांकerrupts */
	nvkm_wr32(device, NV03_PGRAPH_INTR, 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_VALID1, 0);
	nvkm_wr32(device, NV04_PGRAPH_VALID2, 0);
	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x000001FF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x001FFFFF);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x1231c000);
	/*1231C000 blob, 001 haiku*/
	/*V_WRITE(NV04_PGRAPH_DEBUG_1, 0xf2d91100);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x72111100);
	/*0x72111100 blob , 01 haiku*/
	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x11d5f870);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x11d5f071);
	/*haiku same*/

	/*nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xfad4ff31);*/
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xf0d4ff31);
	/*haiku and blob 10d4*/

	nvkm_wr32(device, NV04_PGRAPH_STATE        , 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_CTX_CONTROL  , 0x10000100);
	nvkm_mask(device, NV04_PGRAPH_CTX_USER, 0xff000000, 0x0f000000);

	/* These करोn't belong here, they're part of a per-channel context */
	nvkm_wr32(device, NV04_PGRAPH_PATTERN_SHAPE, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_BETA_AND     , 0xFFFFFFFF);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv04_gr = अणु
	.init = nv04_gr_init,
	.पूर्णांकr = nv04_gr_पूर्णांकr,
	.chan_new = nv04_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv04_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0017, &nv04_gr_object पूर्ण, /* chroma */
		अणु -1, -1, 0x0018, &nv04_gr_object पूर्ण, /* pattern (nv01) */
		अणु -1, -1, 0x0019, &nv04_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x001c, &nv04_gr_object पूर्ण, /* line */
		अणु -1, -1, 0x001d, &nv04_gr_object पूर्ण, /* tri */
		अणु -1, -1, 0x001e, &nv04_gr_object पूर्ण, /* rect */
		अणु -1, -1, 0x001f, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0021, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0030, &nv04_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0036, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0037, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0038, &nv04_gr_object पूर्ण, /* dvd subpicture */
		अणु -1, -1, 0x0039, &nv04_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0042, &nv04_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0043, &nv04_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv04_gr_object पूर्ण, /* pattern */
		अणु -1, -1, 0x0048, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x004a, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x004b, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0052, &nv04_gr_object पूर्ण, /* swzsurf */
		अणु -1, -1, 0x0053, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0054, &nv04_gr_object पूर्ण, /* ttri */
		अणु -1, -1, 0x0055, &nv04_gr_object पूर्ण, /* mtri */
		अणु -1, -1, 0x0057, &nv04_gr_object पूर्ण, /* chroma */
		अणु -1, -1, 0x0058, &nv04_gr_object पूर्ण, /* surf_dst */
		अणु -1, -1, 0x0059, &nv04_gr_object पूर्ण, /* surf_src */
		अणु -1, -1, 0x005a, &nv04_gr_object पूर्ण, /* surf_color */
		अणु -1, -1, 0x005b, &nv04_gr_object पूर्ण, /* surf_zeta */
		अणु -1, -1, 0x005c, &nv04_gr_object पूर्ण, /* line */
		अणु -1, -1, 0x005d, &nv04_gr_object पूर्ण, /* tri */
		अणु -1, -1, 0x005e, &nv04_gr_object पूर्ण, /* rect */
		अणु -1, -1, 0x005f, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0060, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0061, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0064, &nv04_gr_object पूर्ण, /* iअगरc (nv05) */
		अणु -1, -1, 0x0065, &nv04_gr_object पूर्ण, /* अगरc (nv05) */
		अणु -1, -1, 0x0066, &nv04_gr_object पूर्ण, /* sअगरc (nv05) */
		अणु -1, -1, 0x0072, &nv04_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0076, &nv04_gr_object पूर्ण,
		अणु -1, -1, 0x0077, &nv04_gr_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv04_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	काष्ठा nv04_gr *gr;

	अगर (!(gr = kzalloc(माप(*gr), GFP_KERNEL)))
		वापस -ENOMEM;
	spin_lock_init(&gr->lock);
	*pgr = &gr->base;

	वापस nvkm_gr_ctor(&nv04_gr, device, type, inst, true, &gr->base);
पूर्ण
