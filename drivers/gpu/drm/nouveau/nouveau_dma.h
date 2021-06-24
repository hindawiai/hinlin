<शैली गुरु>
/*
 * Copyright (C) 2007 Ben Skeggs.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NOUVEAU_DMA_H__
#घोषणा __NOUVEAU_DMA_H__

#समावेश "nouveau_bo.h"
#समावेश "nouveau_chan.h"

पूर्णांक nouveau_dma_रुको(काष्ठा nouveau_channel *, पूर्णांक slots, पूर्णांक size);
व्योम nv50_dma_push(काष्ठा nouveau_channel *, u64 addr, पूर्णांक length);

/*
 * There's a hw race condition where you can't jump to your PUT offset,
 * to aव्योम this we jump to offset + SKIPS and fill the dअगरference with
 * NOPs.
 *
 * xf86-video-nv configures the DMA fetch size to 32 bytes, and uses
 * a SKIPS value of 8.  Lets assume that the race condition is to करो
 * with writing पूर्णांकo the fetch area, we configure a fetch size of 128
 * bytes so we need a larger SKIPS value.
 */
#घोषणा NOUVEAU_DMA_SKIPS (128 / 4)

/* Object handles - क्रम stuff that's doesn't use handle == oclass. */
क्रमागत अणु
	NvDmaFB		= 0x80000002,
	NvDmaTT		= 0x80000003,
	NvNotअगरy0       = 0x80000006,
	NvSema		= 0x8000000f,
	NvEvoSema0	= 0x80000010,
	NvEvoSema1	= 0x80000011,
पूर्ण;

अटल __must_check अंतरभूत पूर्णांक
RING_SPACE(काष्ठा nouveau_channel *chan, पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = nouveau_dma_रुको(chan, 1, size);
	अगर (ret)
		वापस ret;

	chan->dma.मुक्त -= size;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
OUT_RING(काष्ठा nouveau_channel *chan, पूर्णांक data)
अणु
	nouveau_bo_wr32(chan->push.buffer, chan->dma.cur++, data);
पूर्ण

#घोषणा WRITE_PUT(val) करो अणु                                                    \
	mb();                                                   \
	nouveau_bo_rd32(chan->push.buffer, 0);                                 \
	nvअगर_wr32(&chan->user, chan->user_put, ((val) << 2) + chan->push.addr);\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम
FIRE_RING(काष्ठा nouveau_channel *chan)
अणु
	अगर (chan->dma.cur == chan->dma.put)
		वापस;
	chan->accel_करोne = true;

	अगर (chan->dma.ib_max) अणु
		nv50_dma_push(chan, chan->push.addr + (chan->dma.put << 2),
			      (chan->dma.cur - chan->dma.put) << 2);
	पूर्ण अन्यथा अणु
		WRITE_PUT(chan->dma.cur);
	पूर्ण

	chan->dma.put = chan->dma.cur;
पूर्ण

अटल अंतरभूत व्योम
WIND_RING(काष्ठा nouveau_channel *chan)
अणु
	chan->dma.cur = chan->dma.put;
पूर्ण

/* NV_SW object class */
#घोषणा NV_SW_DMA_VBLSEM                                             0x0000018c
#घोषणा NV_SW_VBLSEM_OFFSET                                          0x00000400
#घोषणा NV_SW_VBLSEM_RELEASE_VALUE                                   0x00000404
#घोषणा NV_SW_VBLSEM_RELEASE                                         0x00000408
#घोषणा NV_SW_PAGE_FLIP                                              0x00000500

#पूर्ण_अगर
