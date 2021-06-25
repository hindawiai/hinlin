<शैली गुरु>
/*
 * Copyright 2007 Matthieu CASTET <castet.matthieu@मुक्त.fr>
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
#समावेश "nv10.h"
#समावेश "regs.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>
#समावेश <engine/fअगरo/chan.h>
#समावेश <subdev/fb.h>

काष्ठा pipe_state अणु
	u32 pipe_0x0000[0x040/4];
	u32 pipe_0x0040[0x010/4];
	u32 pipe_0x0200[0x0c0/4];
	u32 pipe_0x4400[0x080/4];
	u32 pipe_0x6400[0x3b0/4];
	u32 pipe_0x6800[0x2f0/4];
	u32 pipe_0x6c00[0x030/4];
	u32 pipe_0x7000[0x130/4];
	u32 pipe_0x7400[0x0c0/4];
	u32 pipe_0x7800[0x0c0/4];
पूर्ण;

अटल पूर्णांक nv10_gr_ctx_regs[] = अणु
	NV10_PGRAPH_CTX_SWITCH(0),
	NV10_PGRAPH_CTX_SWITCH(1),
	NV10_PGRAPH_CTX_SWITCH(2),
	NV10_PGRAPH_CTX_SWITCH(3),
	NV10_PGRAPH_CTX_SWITCH(4),
	NV10_PGRAPH_CTX_CACHE(0, 0),
	NV10_PGRAPH_CTX_CACHE(0, 1),
	NV10_PGRAPH_CTX_CACHE(0, 2),
	NV10_PGRAPH_CTX_CACHE(0, 3),
	NV10_PGRAPH_CTX_CACHE(0, 4),
	NV10_PGRAPH_CTX_CACHE(1, 0),
	NV10_PGRAPH_CTX_CACHE(1, 1),
	NV10_PGRAPH_CTX_CACHE(1, 2),
	NV10_PGRAPH_CTX_CACHE(1, 3),
	NV10_PGRAPH_CTX_CACHE(1, 4),
	NV10_PGRAPH_CTX_CACHE(2, 0),
	NV10_PGRAPH_CTX_CACHE(2, 1),
	NV10_PGRAPH_CTX_CACHE(2, 2),
	NV10_PGRAPH_CTX_CACHE(2, 3),
	NV10_PGRAPH_CTX_CACHE(2, 4),
	NV10_PGRAPH_CTX_CACHE(3, 0),
	NV10_PGRAPH_CTX_CACHE(3, 1),
	NV10_PGRAPH_CTX_CACHE(3, 2),
	NV10_PGRAPH_CTX_CACHE(3, 3),
	NV10_PGRAPH_CTX_CACHE(3, 4),
	NV10_PGRAPH_CTX_CACHE(4, 0),
	NV10_PGRAPH_CTX_CACHE(4, 1),
	NV10_PGRAPH_CTX_CACHE(4, 2),
	NV10_PGRAPH_CTX_CACHE(4, 3),
	NV10_PGRAPH_CTX_CACHE(4, 4),
	NV10_PGRAPH_CTX_CACHE(5, 0),
	NV10_PGRAPH_CTX_CACHE(5, 1),
	NV10_PGRAPH_CTX_CACHE(5, 2),
	NV10_PGRAPH_CTX_CACHE(5, 3),
	NV10_PGRAPH_CTX_CACHE(5, 4),
	NV10_PGRAPH_CTX_CACHE(6, 0),
	NV10_PGRAPH_CTX_CACHE(6, 1),
	NV10_PGRAPH_CTX_CACHE(6, 2),
	NV10_PGRAPH_CTX_CACHE(6, 3),
	NV10_PGRAPH_CTX_CACHE(6, 4),
	NV10_PGRAPH_CTX_CACHE(7, 0),
	NV10_PGRAPH_CTX_CACHE(7, 1),
	NV10_PGRAPH_CTX_CACHE(7, 2),
	NV10_PGRAPH_CTX_CACHE(7, 3),
	NV10_PGRAPH_CTX_CACHE(7, 4),
	NV10_PGRAPH_CTX_USER,
	NV04_PGRAPH_DMA_START_0,
	NV04_PGRAPH_DMA_START_1,
	NV04_PGRAPH_DMA_LENGTH,
	NV04_PGRAPH_DMA_MISC,
	NV10_PGRAPH_DMA_PITCH,
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
	NV10_PGRAPH_SURFACE,
	NV10_PGRAPH_STATE,
	NV04_PGRAPH_BSWIZZLE2,
	NV04_PGRAPH_BSWIZZLE5,
	NV04_PGRAPH_BPIXEL,
	NV10_PGRAPH_NOTIFY,
	NV04_PGRAPH_PATT_COLOR0,
	NV04_PGRAPH_PATT_COLOR1,
	NV04_PGRAPH_PATT_COLORRAM, /* 64 values from 0x400900 to 0x4009fc */
	0x00400904,
	0x00400908,
	0x0040090c,
	0x00400910,
	0x00400914,
	0x00400918,
	0x0040091c,
	0x00400920,
	0x00400924,
	0x00400928,
	0x0040092c,
	0x00400930,
	0x00400934,
	0x00400938,
	0x0040093c,
	0x00400940,
	0x00400944,
	0x00400948,
	0x0040094c,
	0x00400950,
	0x00400954,
	0x00400958,
	0x0040095c,
	0x00400960,
	0x00400964,
	0x00400968,
	0x0040096c,
	0x00400970,
	0x00400974,
	0x00400978,
	0x0040097c,
	0x00400980,
	0x00400984,
	0x00400988,
	0x0040098c,
	0x00400990,
	0x00400994,
	0x00400998,
	0x0040099c,
	0x004009a0,
	0x004009a4,
	0x004009a8,
	0x004009ac,
	0x004009b0,
	0x004009b4,
	0x004009b8,
	0x004009bc,
	0x004009c0,
	0x004009c4,
	0x004009c8,
	0x004009cc,
	0x004009d0,
	0x004009d4,
	0x004009d8,
	0x004009dc,
	0x004009e0,
	0x004009e4,
	0x004009e8,
	0x004009ec,
	0x004009f0,
	0x004009f4,
	0x004009f8,
	0x004009fc,
	NV04_PGRAPH_PATTERN,	/* 2 values from 0x400808 to 0x40080c */
	0x0040080c,
	NV04_PGRAPH_PATTERN_SHAPE,
	NV03_PGRAPH_MONO_COLOR0,
	NV04_PGRAPH_ROP3,
	NV04_PGRAPH_CHROMA,
	NV04_PGRAPH_BETA_AND,
	NV04_PGRAPH_BETA_PREMULT,
	0x00400e70,
	0x00400e74,
	0x00400e78,
	0x00400e7c,
	0x00400e80,
	0x00400e84,
	0x00400e88,
	0x00400e8c,
	0x00400ea0,
	0x00400ea4,
	0x00400ea8,
	0x00400e90,
	0x00400e94,
	0x00400e98,
	0x00400e9c,
	NV10_PGRAPH_WINDOWCLIP_HORIZONTAL, /* 8 values from 0x400f00-0x400f1c */
	NV10_PGRAPH_WINDOWCLIP_VERTICAL,   /* 8 values from 0x400f20-0x400f3c */
	0x00400f04,
	0x00400f24,
	0x00400f08,
	0x00400f28,
	0x00400f0c,
	0x00400f2c,
	0x00400f10,
	0x00400f30,
	0x00400f14,
	0x00400f34,
	0x00400f18,
	0x00400f38,
	0x00400f1c,
	0x00400f3c,
	NV10_PGRAPH_XFMODE0,
	NV10_PGRAPH_XFMODE1,
	NV10_PGRAPH_GLOBALSTATE0,
	NV10_PGRAPH_GLOBALSTATE1,
	NV04_PGRAPH_STORED_FMT,
	NV04_PGRAPH_SOURCE_COLOR,
	NV03_PGRAPH_ABS_X_RAM,	/* 32 values from 0x400400 to 0x40047c */
	NV03_PGRAPH_ABS_Y_RAM,	/* 32 values from 0x400480 to 0x4004fc */
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
	NV03_PGRAPH_ABS_UCLIP_XMIN,
	NV03_PGRAPH_ABS_UCLIP_XMAX,
	NV03_PGRAPH_ABS_UCLIP_YMIN,
	NV03_PGRAPH_ABS_UCLIP_YMAX,
	0x00400550,
	0x00400558,
	0x00400554,
	0x0040055c,
	NV03_PGRAPH_ABS_UCLIPA_XMIN,
	NV03_PGRAPH_ABS_UCLIPA_XMAX,
	NV03_PGRAPH_ABS_UCLIPA_YMIN,
	NV03_PGRAPH_ABS_UCLIPA_YMAX,
	NV03_PGRAPH_ABS_ICLIP_XMAX,
	NV03_PGRAPH_ABS_ICLIP_YMAX,
	NV03_PGRAPH_XY_LOGIC_MISC0,
	NV03_PGRAPH_XY_LOGIC_MISC1,
	NV03_PGRAPH_XY_LOGIC_MISC2,
	NV03_PGRAPH_XY_LOGIC_MISC3,
	NV03_PGRAPH_CLIPX_0,
	NV03_PGRAPH_CLIPX_1,
	NV03_PGRAPH_CLIPY_0,
	NV03_PGRAPH_CLIPY_1,
	NV10_PGRAPH_COMBINER0_IN_ALPHA,
	NV10_PGRAPH_COMBINER1_IN_ALPHA,
	NV10_PGRAPH_COMBINER0_IN_RGB,
	NV10_PGRAPH_COMBINER1_IN_RGB,
	NV10_PGRAPH_COMBINER_COLOR0,
	NV10_PGRAPH_COMBINER_COLOR1,
	NV10_PGRAPH_COMBINER0_OUT_ALPHA,
	NV10_PGRAPH_COMBINER1_OUT_ALPHA,
	NV10_PGRAPH_COMBINER0_OUT_RGB,
	NV10_PGRAPH_COMBINER1_OUT_RGB,
	NV10_PGRAPH_COMBINER_FINAL0,
	NV10_PGRAPH_COMBINER_FINAL1,
	0x00400e00,
	0x00400e04,
	0x00400e08,
	0x00400e0c,
	0x00400e10,
	0x00400e14,
	0x00400e18,
	0x00400e1c,
	0x00400e20,
	0x00400e24,
	0x00400e28,
	0x00400e2c,
	0x00400e30,
	0x00400e34,
	0x00400e38,
	0x00400e3c,
	NV04_PGRAPH_PASSTHRU_0,
	NV04_PGRAPH_PASSTHRU_1,
	NV04_PGRAPH_PASSTHRU_2,
	NV10_PGRAPH_DIMX_TEXTURE,
	NV10_PGRAPH_WDIMX_TEXTURE,
	NV10_PGRAPH_DVD_COLORFMT,
	NV10_PGRAPH_SCALED_FORMAT,
	NV04_PGRAPH_MISC24_0,
	NV04_PGRAPH_MISC24_1,
	NV04_PGRAPH_MISC24_2,
	NV03_PGRAPH_X_MISC,
	NV03_PGRAPH_Y_MISC,
	NV04_PGRAPH_VALID1,
	NV04_PGRAPH_VALID2,
पूर्ण;

अटल पूर्णांक nv17_gr_ctx_regs[] = अणु
	NV10_PGRAPH_DEBUG_4,
	0x004006b0,
	0x00400eac,
	0x00400eb0,
	0x00400eb4,
	0x00400eb8,
	0x00400ebc,
	0x00400ec0,
	0x00400ec4,
	0x00400ec8,
	0x00400ecc,
	0x00400ed0,
	0x00400ed4,
	0x00400ed8,
	0x00400edc,
	0x00400ee0,
	0x00400a00,
	0x00400a04,
पूर्ण;

#घोषणा nv10_gr(p) container_of((p), काष्ठा nv10_gr, base)

काष्ठा nv10_gr अणु
	काष्ठा nvkm_gr base;
	काष्ठा nv10_gr_chan *chan[32];
	spinlock_t lock;
पूर्ण;

#घोषणा nv10_gr_chan(p) container_of((p), काष्ठा nv10_gr_chan, object)

काष्ठा nv10_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv10_gr *gr;
	पूर्णांक chid;
	पूर्णांक nv10[ARRAY_SIZE(nv10_gr_ctx_regs)];
	पूर्णांक nv17[ARRAY_SIZE(nv17_gr_ctx_regs)];
	काष्ठा pipe_state pipe_state;
	u32 lma_winकरोw[4];
पूर्ण;


/*******************************************************************************
 * Graphics object classes
 ******************************************************************************/

#घोषणा PIPE_SAVE(gr, state, addr)					\
	करो अणु								\
		पूर्णांक __i;						\
		nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, addr);		\
		क्रम (__i = 0; __i < ARRAY_SIZE(state); __i++)		\
			state[__i] = nvkm_rd32(device, NV10_PGRAPH_PIPE_DATA); \
	पूर्ण जबतक (0)

#घोषणा PIPE_RESTORE(gr, state, addr)					\
	करो अणु								\
		पूर्णांक __i;						\
		nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, addr);		\
		क्रम (__i = 0; __i < ARRAY_SIZE(state); __i++)		\
			nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, state[__i]); \
	पूर्ण जबतक (0)

अटल व्योम
nv17_gr_mthd_lma_winकरोw(काष्ठा nv10_gr_chan *chan, u32 mthd, u32 data)
अणु
	काष्ठा nvkm_device *device = chan->object.engine->subdev.device;
	काष्ठा nvkm_gr *gr = &chan->gr->base;
	काष्ठा pipe_state *pipe = &chan->pipe_state;
	u32 pipe_0x0040[1], pipe_0x64c0[8], pipe_0x6a80[3], pipe_0x6ab0[3];
	u32 xभ_शेषe0, xभ_शेषe1;
	पूर्णांक i;

	chan->lma_winकरोw[(mthd - 0x1638) / 4] = data;

	अगर (mthd != 0x1644)
		वापस;

	nv04_gr_idle(gr);

	PIPE_SAVE(device, pipe_0x0040, 0x0040);
	PIPE_SAVE(device, pipe->pipe_0x0200, 0x0200);

	PIPE_RESTORE(device, chan->lma_winकरोw, 0x6790);

	nv04_gr_idle(gr);

	xभ_शेषe0 = nvkm_rd32(device, NV10_PGRAPH_XFMODE0);
	xभ_शेषe1 = nvkm_rd32(device, NV10_PGRAPH_XFMODE1);

	PIPE_SAVE(device, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(device, pipe_0x64c0, 0x64c0);
	PIPE_SAVE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_SAVE(device, pipe_0x6a80, 0x6a80);

	nv04_gr_idle(gr);

	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, 0x10000000);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x000064c0);
	क्रम (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);
	क्रम (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006ab0);
	क्रम (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006a80);
	क्रम (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00000040);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000008);

	PIPE_RESTORE(device, pipe->pipe_0x0200, 0x0200);

	nv04_gr_idle(gr);

	PIPE_RESTORE(device, pipe_0x0040, 0x0040);

	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, xभ_शेषe0);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, xभ_शेषe1);

	PIPE_RESTORE(device, pipe_0x64c0, 0x64c0);
	PIPE_RESTORE(device, pipe_0x6ab0, 0x6ab0);
	PIPE_RESTORE(device, pipe_0x6a80, 0x6a80);
	PIPE_RESTORE(device, pipe->pipe_0x4400, 0x4400);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x000000c0);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nv04_gr_idle(gr);
पूर्ण

अटल व्योम
nv17_gr_mthd_lma_enable(काष्ठा nv10_gr_chan *chan, u32 mthd, u32 data)
अणु
	काष्ठा nvkm_device *device = chan->object.engine->subdev.device;
	काष्ठा nvkm_gr *gr = &chan->gr->base;

	nv04_gr_idle(gr);

	nvkm_mask(device, NV10_PGRAPH_DEBUG_4, 0x00000100, 0x00000100);
	nvkm_mask(device, 0x4006b0, 0x08000000, 0x08000000);
पूर्ण

अटल bool
nv17_gr_mthd_celcius(काष्ठा nv10_gr_chan *chan, u32 mthd, u32 data)
अणु
	व्योम (*func)(काष्ठा nv10_gr_chan *, u32, u32);
	चयन (mthd) अणु
	हाल 0x1638 ... 0x1644:
		     func = nv17_gr_mthd_lma_winकरोw; अवरोध;
	हाल 0x1658: func = nv17_gr_mthd_lma_enable; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	func(chan, mthd, data);
	वापस true;
पूर्ण

अटल bool
nv10_gr_mthd(काष्ठा nv10_gr_chan *chan, u8 class, u32 mthd, u32 data)
अणु
	bool (*func)(काष्ठा nv10_gr_chan *, u32, u32);
	चयन (class) अणु
	हाल 0x99: func = nv17_gr_mthd_celcius; अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस func(chan, mthd, data);
पूर्ण

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल काष्ठा nv10_gr_chan *
nv10_gr_channel(काष्ठा nv10_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nv10_gr_chan *chan = शून्य;
	अगर (nvkm_rd32(device, 0x400144) & 0x00010000) अणु
		पूर्णांक chid = nvkm_rd32(device, 0x400148) >> 24;
		अगर (chid < ARRAY_SIZE(gr->chan))
			chan = gr->chan[chid];
	पूर्ण
	वापस chan;
पूर्ण

अटल व्योम
nv10_gr_save_pipe(काष्ठा nv10_gr_chan *chan)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा pipe_state *pipe = &chan->pipe_state;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	PIPE_SAVE(gr, pipe->pipe_0x4400, 0x4400);
	PIPE_SAVE(gr, pipe->pipe_0x0200, 0x0200);
	PIPE_SAVE(gr, pipe->pipe_0x6400, 0x6400);
	PIPE_SAVE(gr, pipe->pipe_0x6800, 0x6800);
	PIPE_SAVE(gr, pipe->pipe_0x6c00, 0x6c00);
	PIPE_SAVE(gr, pipe->pipe_0x7000, 0x7000);
	PIPE_SAVE(gr, pipe->pipe_0x7400, 0x7400);
	PIPE_SAVE(gr, pipe->pipe_0x7800, 0x7800);
	PIPE_SAVE(gr, pipe->pipe_0x0040, 0x0040);
	PIPE_SAVE(gr, pipe->pipe_0x0000, 0x0000);
पूर्ण

अटल व्योम
nv10_gr_load_pipe(काष्ठा nv10_gr_chan *chan)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा pipe_state *pipe = &chan->pipe_state;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 xभ_शेषe0, xभ_शेषe1;
	पूर्णांक i;

	nv04_gr_idle(&gr->base);
	/* XXX check haiku comments */
	xभ_शेषe0 = nvkm_rd32(device, NV10_PGRAPH_XFMODE0);
	xभ_शेषe1 = nvkm_rd32(device, NV10_PGRAPH_XFMODE1);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, 0x10000000);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x000064c0);
	क्रम (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);
	क्रम (i = 0; i < 4; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006ab0);
	क्रम (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x3f800000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00006a80);
	क्रम (i = 0; i < 3; i++)
		nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000000);

	nvkm_wr32(device, NV10_PGRAPH_PIPE_ADDRESS, 0x00000040);
	nvkm_wr32(device, NV10_PGRAPH_PIPE_DATA, 0x00000008);


	PIPE_RESTORE(gr, pipe->pipe_0x0200, 0x0200);
	nv04_gr_idle(&gr->base);

	/* restore XFMODE */
	nvkm_wr32(device, NV10_PGRAPH_XFMODE0, xभ_शेषe0);
	nvkm_wr32(device, NV10_PGRAPH_XFMODE1, xभ_शेषe1);
	PIPE_RESTORE(gr, pipe->pipe_0x6400, 0x6400);
	PIPE_RESTORE(gr, pipe->pipe_0x6800, 0x6800);
	PIPE_RESTORE(gr, pipe->pipe_0x6c00, 0x6c00);
	PIPE_RESTORE(gr, pipe->pipe_0x7000, 0x7000);
	PIPE_RESTORE(gr, pipe->pipe_0x7400, 0x7400);
	PIPE_RESTORE(gr, pipe->pipe_0x7800, 0x7800);
	PIPE_RESTORE(gr, pipe->pipe_0x4400, 0x4400);
	PIPE_RESTORE(gr, pipe->pipe_0x0000, 0x0000);
	PIPE_RESTORE(gr, pipe->pipe_0x0040, 0x0040);
	nv04_gr_idle(&gr->base);
पूर्ण

अटल व्योम
nv10_gr_create_pipe(काष्ठा nv10_gr_chan *chan)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा pipe_state *pipe_state = &chan->pipe_state;
	u32 *pipe_state_addr;
	पूर्णांक i;
#घोषणा PIPE_INIT(addr) \
	करो अणु \
		pipe_state_addr = pipe_state->pipe_##addr; \
	पूर्ण जबतक (0)
#घोषणा PIPE_INIT_END(addr) \
	करो अणु \
		u32 *__end_addr = pipe_state->pipe_##addr + \
				ARRAY_SIZE(pipe_state->pipe_##addr); \
		अगर (pipe_state_addr != __end_addr) \
			nvkm_error(subdev, "incomplete pipe init for 0x%x :  %p/%p\n", \
				addr, pipe_state_addr, __end_addr); \
	पूर्ण जबतक (0)
#घोषणा NV_WRITE_PIPE_INIT(value) *(pipe_state_addr++) = value

	PIPE_INIT(0x0200);
	क्रम (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0200);

	PIPE_INIT(0x6400);
	क्रम (i = 0; i < 211; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x40000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f000000);
	NV_WRITE_PIPE_INIT(0x3f000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	PIPE_INIT_END(0x6400);

	PIPE_INIT(0x6800);
	क्रम (i = 0; i < 162; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x3f800000);
	क्रम (i = 0; i < 25; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6800);

	PIPE_INIT(0x6c00);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0xbf800000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x6c00);

	PIPE_INIT(0x7000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x00000000);
	NV_WRITE_PIPE_INIT(0x7149f2ca);
	क्रम (i = 0; i < 35; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7000);

	PIPE_INIT(0x7400);
	क्रम (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7400);

	PIPE_INIT(0x7800);
	क्रम (i = 0; i < 48; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x7800);

	PIPE_INIT(0x4400);
	क्रम (i = 0; i < 32; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x4400);

	PIPE_INIT(0x0000);
	क्रम (i = 0; i < 16; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0000);

	PIPE_INIT(0x0040);
	क्रम (i = 0; i < 4; i++)
		NV_WRITE_PIPE_INIT(0x00000000);
	PIPE_INIT_END(0x0040);

#अघोषित PIPE_INIT
#अघोषित PIPE_INIT_END
#अघोषित NV_WRITE_PIPE_INIT
पूर्ण

अटल पूर्णांक
nv10_gr_ctx_regs_find_offset(काष्ठा nv10_gr *gr, पूर्णांक reg)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(nv10_gr_ctx_regs); i++) अणु
		अगर (nv10_gr_ctx_regs[i] == reg)
			वापस i;
	पूर्ण
	nvkm_error(subdev, "unknown offset nv10_ctx_regs %d\n", reg);
	वापस -1;
पूर्ण

अटल पूर्णांक
nv17_gr_ctx_regs_find_offset(काष्ठा nv10_gr *gr, पूर्णांक reg)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(nv17_gr_ctx_regs); i++) अणु
		अगर (nv17_gr_ctx_regs[i] == reg)
			वापस i;
	पूर्ण
	nvkm_error(subdev, "unknown offset nv17_ctx_regs %d\n", reg);
	वापस -1;
पूर्ण

अटल व्योम
nv10_gr_load_dma_vtxbuf(काष्ठा nv10_gr_chan *chan, पूर्णांक chid, u32 inst)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 st2, st2_dl, st2_dh, fअगरo_ptr, fअगरo[0x60/4];
	u32 ctx_user, ctx_चयन[5];
	पूर्णांक i, subchan = -1;

	/* NV10TCL_DMA_VTXBUF (method 0x18c) modअगरies hidden state
	 * that cannot be restored via MMIO. Do it through the FIFO
	 * instead.
	 */

	/* Look क्रम a celsius object */
	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक class = nvkm_rd32(device, NV10_PGRAPH_CTX_CACHE(i, 0)) & 0xfff;

		अगर (class == 0x56 || class == 0x96 || class == 0x99) अणु
			subchan = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (subchan < 0 || !inst)
		वापस;

	/* Save the current ctx object */
	ctx_user = nvkm_rd32(device, NV10_PGRAPH_CTX_USER);
	क्रम (i = 0; i < 5; i++)
		ctx_चयन[i] = nvkm_rd32(device, NV10_PGRAPH_CTX_SWITCH(i));

	/* Save the FIFO state */
	st2 = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2);
	st2_dl = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2_DL);
	st2_dh = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_ST2_DH);
	fअगरo_ptr = nvkm_rd32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR);

	क्रम (i = 0; i < ARRAY_SIZE(fअगरo); i++)
		fअगरo[i] = nvkm_rd32(device, 0x4007a0 + 4 * i);

	/* Switch to the celsius subchannel */
	क्रम (i = 0; i < 5; i++)
		nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(i),
			nvkm_rd32(device, NV10_PGRAPH_CTX_CACHE(subchan, i)));
	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xe000, subchan << 13);

	/* Inject NV10TCL_DMA_VTXBUF */
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR, 0);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2,
		0x2c000000 | chid << 20 | subchan << 16 | 0x18c);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DL, inst);
	nvkm_mask(device, NV10_PGRAPH_CTX_CONTROL, 0, 0x10000);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);

	/* Restore the FIFO state */
	क्रम (i = 0; i < ARRAY_SIZE(fअगरo); i++)
		nvkm_wr32(device, 0x4007a0 + 4 * i, fअगरo[i]);

	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_FIFO_PTR, fअगरo_ptr);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2, st2);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DL, st2_dl);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2_DH, st2_dh);

	/* Restore the current ctx object */
	क्रम (i = 0; i < 5; i++)
		nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(i), ctx_चयन[i]);
	nvkm_wr32(device, NV10_PGRAPH_CTX_USER, ctx_user);
पूर्ण

अटल पूर्णांक
nv10_gr_load_context(काष्ठा nv10_gr_chan *chan, पूर्णांक chid)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 inst;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nv10_gr_ctx_regs); i++)
		nvkm_wr32(device, nv10_gr_ctx_regs[i], chan->nv10[i]);

	अगर (device->card_type >= NV_11 && device->chipset >= 0x17) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nv17_gr_ctx_regs); i++)
			nvkm_wr32(device, nv17_gr_ctx_regs[i], chan->nv17[i]);
	पूर्ण

	nv10_gr_load_pipe(chan);

	inst = nvkm_rd32(device, NV10_PGRAPH_GLOBALSTATE1) & 0xffff;
	nv10_gr_load_dma_vtxbuf(chan, chid, inst);

	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10010100);
	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xff000000, chid << 24);
	nvkm_mask(device, NV10_PGRAPH_FFINTFC_ST2, 0x30000000, 0x00000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv10_gr_unload_context(काष्ठा nv10_gr_chan *chan)
अणु
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nv10_gr_ctx_regs); i++)
		chan->nv10[i] = nvkm_rd32(device, nv10_gr_ctx_regs[i]);

	अगर (device->card_type >= NV_11 && device->chipset >= 0x17) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nv17_gr_ctx_regs); i++)
			chan->nv17[i] = nvkm_rd32(device, nv17_gr_ctx_regs[i]);
	पूर्ण

	nv10_gr_save_pipe(chan);

	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10000000);
	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xff000000, 0x1f000000);
	वापस 0;
पूर्ण

अटल व्योम
nv10_gr_context_चयन(काष्ठा nv10_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nv10_gr_chan *prev = शून्य;
	काष्ठा nv10_gr_chan *next = शून्य;
	पूर्णांक chid;

	nv04_gr_idle(&gr->base);

	/* If previous context is valid, we need to save it */
	prev = nv10_gr_channel(gr);
	अगर (prev)
		nv10_gr_unload_context(prev);

	/* load context क्रम next channel */
	chid = (nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR) >> 20) & 0x1f;
	next = gr->chan[chid];
	अगर (next)
		nv10_gr_load_context(next, chid);
पूर्ण

अटल पूर्णांक
nv10_gr_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nv10_gr_chan *chan = nv10_gr_chan(object);
	काष्ठा nv10_gr *gr = chan->gr;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);
	अगर (nv10_gr_channel(gr) == chan)
		nv10_gr_unload_context(chan);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम *
nv10_gr_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv10_gr_chan *chan = nv10_gr_chan(object);
	काष्ठा nv10_gr *gr = chan->gr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = शून्य;
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv10_gr_chan = अणु
	.dtor = nv10_gr_chan_dtor,
	.fini = nv10_gr_chan_fini,
पूर्ण;

#घोषणा NV_WRITE_CTX(reg, val) करो अणु \
	पूर्णांक offset = nv10_gr_ctx_regs_find_offset(gr, reg); \
	अगर (offset > 0) \
		chan->nv10[offset] = val; \
	पूर्ण जबतक (0)

#घोषणा NV17_WRITE_CTX(reg, val) करो अणु \
	पूर्णांक offset = nv17_gr_ctx_regs_find_offset(gr, reg); \
	अगर (offset > 0) \
		chan->nv17[offset] = val; \
	पूर्ण जबतक (0)

पूर्णांक
nv10_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv10_gr *gr = nv10_gr(base);
	काष्ठा nv10_gr_chan *chan;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	अचिन्हित दीर्घ flags;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv10_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	NV_WRITE_CTX(0x00400e88, 0x08000000);
	NV_WRITE_CTX(0x00400e9c, 0x4b7fffff);
	NV_WRITE_CTX(NV03_PGRAPH_XY_LOGIC_MISC0, 0x0001ffff);
	NV_WRITE_CTX(0x00400e10, 0x00001000);
	NV_WRITE_CTX(0x00400e14, 0x00001000);
	NV_WRITE_CTX(0x00400e30, 0x00080008);
	NV_WRITE_CTX(0x00400e34, 0x00080008);
	अगर (device->card_type >= NV_11 && device->chipset >= 0x17) अणु
		/* is it really needed ??? */
		NV17_WRITE_CTX(NV10_PGRAPH_DEBUG_4,
			       nvkm_rd32(device, NV10_PGRAPH_DEBUG_4));
		NV17_WRITE_CTX(0x004006b0, nvkm_rd32(device, 0x004006b0));
		NV17_WRITE_CTX(0x00400eac, 0x0fff0000);
		NV17_WRITE_CTX(0x00400eb0, 0x0fff0000);
		NV17_WRITE_CTX(0x00400ec0, 0x00000080);
		NV17_WRITE_CTX(0x00400ed0, 0x00000080);
	पूर्ण
	NV_WRITE_CTX(NV10_PGRAPH_CTX_USER, chan->chid << 24);

	nv10_gr_create_pipe(chan);

	spin_lock_irqsave(&gr->lock, flags);
	gr->chan[chan->chid] = chan;
	spin_unlock_irqrestore(&gr->lock, flags);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

व्योम
nv10_gr_tile(काष्ठा nvkm_gr *base, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nv10_gr *gr = nv10_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;
	अचिन्हित दीर्घ flags;

	nvkm_fअगरo_छोड़ो(fअगरo, &flags);
	nv04_gr_idle(&gr->base);

	nvkm_wr32(device, NV10_PGRAPH_TLIMIT(i), tile->limit);
	nvkm_wr32(device, NV10_PGRAPH_TSIZE(i), tile->pitch);
	nvkm_wr32(device, NV10_PGRAPH_TILE(i), tile->addr);

	nvkm_fअगरo_start(fअगरo, &flags);
पूर्ण

स्थिर काष्ठा nvkm_bitfield nv10_gr_पूर्णांकr_name[] = अणु
	अणु NV_PGRAPH_INTR_NOTIFY, "NOTIFY" पूर्ण,
	अणु NV_PGRAPH_INTR_ERROR,  "ERROR"  पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_bitfield nv10_gr_nstatus[] = अणु
	अणु NV10_PGRAPH_NSTATUS_STATE_IN_USE,       "STATE_IN_USE" पूर्ण,
	अणु NV10_PGRAPH_NSTATUS_INVALID_STATE,      "INVALID_STATE" पूर्ण,
	अणु NV10_PGRAPH_NSTATUS_BAD_ARGUMENT,       "BAD_ARGUMENT" पूर्ण,
	अणु NV10_PGRAPH_NSTATUS_PROTECTION_FAULT,   "PROTECTION_FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
nv10_gr_पूर्णांकr(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv10_gr *gr = nv10_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, NV03_PGRAPH_INTR);
	u32 nsource = nvkm_rd32(device, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nvkm_rd32(device, NV03_PGRAPH_NSTATUS);
	u32 addr = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR);
	u32 chid = (addr & 0x01f00000) >> 20;
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nvkm_rd32(device, 0x400160 + subc * 4) & 0xfff;
	u32 show = stat;
	अक्षर msg[128], src[128], sta[128];
	काष्ठा nv10_gr_chan *chan;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->lock, flags);
	chan = gr->chan[chid];

	अगर (stat & NV_PGRAPH_INTR_ERROR) अणु
		अगर (chan && (nsource & NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD)) अणु
			अगर (!nv10_gr_mthd(chan, class, mthd, data))
				show &= ~NV_PGRAPH_INTR_ERROR;
		पूर्ण
	पूर्ण

	अगर (stat & NV_PGRAPH_INTR_CONTEXT_SWITCH) अणु
		nvkm_wr32(device, NV03_PGRAPH_INTR, NV_PGRAPH_INTR_CONTEXT_SWITCH);
		stat &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		show &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		nv10_gr_context_चयन(gr);
	पूर्ण

	nvkm_wr32(device, NV03_PGRAPH_INTR, stat);
	nvkm_wr32(device, NV04_PGRAPH_FIFO, 0x00000001);

	अगर (show) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), nv10_gr_पूर्णांकr_name, show);
		nvkm_snprपूर्णांकbf(src, माप(src), nv04_gr_nsource, nsource);
		nvkm_snprपूर्णांकbf(sta, माप(sta), nv10_gr_nstatus, nstatus);
		nvkm_error(subdev, "intr %08x [%s] nsource %08x [%s] "
				   "nstatus %08x [%s] ch %d [%s] subc %d "
				   "class %04x mthd %04x data %08x\n",
			   show, msg, nsource, src, nstatus, sta, chid,
			   chan ? chan->object.client->name : "unknown",
			   subc, class, mthd, data);
	पूर्ण

	spin_unlock_irqrestore(&gr->lock, flags);
पूर्ण

पूर्णांक
nv10_gr_init(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv10_gr *gr = nv10_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x00118700);
	/* nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x24E00810); */ /* 0x25f92ad9 */
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x25f92ad9);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0x55DE0830 | (1 << 29) | (1 << 31));

	अगर (device->card_type >= NV_11 && device->chipset >= 0x17) अणु
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x1f000000);
		nvkm_wr32(device, 0x400a10, 0x03ff3fb6);
		nvkm_wr32(device, 0x400838, 0x002f8684);
		nvkm_wr32(device, 0x40083c, 0x00115f3f);
		nvkm_wr32(device, 0x4006b0, 0x40000020);
	पूर्ण अन्यथा अणु
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x00000000);
	पूर्ण

	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(0), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(1), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(2), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(3), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(4), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_STATE, 0xFFFFFFFF);

	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xff000000, 0x1f000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2, 0x08000000);
	वापस 0;
पूर्ण

पूर्णांक
nv10_gr_new_(स्थिर काष्ठा nvkm_gr_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	काष्ठा nv10_gr *gr;

	अगर (!(gr = kzalloc(माप(*gr), GFP_KERNEL)))
		वापस -ENOMEM;
	spin_lock_init(&gr->lock);
	*pgr = &gr->base;

	वापस nvkm_gr_ctor(func, device, type, inst, true, &gr->base);
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv10_gr = अणु
	.init = nv10_gr_init,
	.पूर्णांकr = nv10_gr_पूर्णांकr,
	.tile = nv10_gr_tile,
	.chan_new = nv10_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv04_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0019, &nv04_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x0030, &nv04_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0039, &nv04_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0043, &nv04_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv04_gr_object पूर्ण, /* pattern */
		अणु -1, -1, 0x004a, &nv04_gr_object पूर्ण, /* gdi */
		अणु -1, -1, 0x0052, &nv04_gr_object पूर्ण, /* swzsurf */
		अणु -1, -1, 0x005f, &nv04_gr_object पूर्ण, /* blit */
		अणु -1, -1, 0x0062, &nv04_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0072, &nv04_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0089, &nv04_gr_object पूर्ण, /* sअगरm */
		अणु -1, -1, 0x008a, &nv04_gr_object पूर्ण, /* अगरc */
		अणु -1, -1, 0x009f, &nv04_gr_object पूर्ण, /* blit */
		अणु -1, -1, 0x0093, &nv04_gr_object पूर्ण, /* surf3d */
		अणु -1, -1, 0x0094, &nv04_gr_object पूर्ण, /* ttri */
		अणु -1, -1, 0x0095, &nv04_gr_object पूर्ण, /* mtri */
		अणु -1, -1, 0x0056, &nv04_gr_object पूर्ण, /* celcius */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv10_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv10_gr_new_(&nv10_gr, device, type, inst, pgr);
पूर्ण
