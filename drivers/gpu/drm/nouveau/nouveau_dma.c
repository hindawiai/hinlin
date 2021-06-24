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

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_vmm.h"

#समावेश <nvअगर/user.h>

/* Fetch and adjust GPU GET poपूर्णांकer
 *
 * Returns:
 *  value >= 0, the adjusted GET poपूर्णांकer
 *  -EINVAL अगर GET poपूर्णांकer currently outside मुख्य push buffer
 *  -EBUSY अगर समयout exceeded
 */
अटल अंतरभूत पूर्णांक
READ_GET(काष्ठा nouveau_channel *chan, uपूर्णांक64_t *prev_get, पूर्णांक *समयout)
अणु
	uपूर्णांक64_t val;

	val = nvअगर_rd32(&chan->user, chan->user_get);
        अगर (chan->user_get_hi)
                val |= (uपूर्णांक64_t)nvअगर_rd32(&chan->user, chan->user_get_hi) << 32;

	/* reset counter as दीर्घ as GET is still advancing, this is
	 * to aव्योम misdetecting a GPU lockup अगर the GPU happens to
	 * just be processing an operation that takes a दीर्घ समय
	 */
	अगर (val != *prev_get) अणु
		*prev_get = val;
		*समयout = 0;
	पूर्ण

	अगर ((++*समयout & 0xff) == 0) अणु
		udelay(1);
		अगर (*समयout > 100000)
			वापस -EBUSY;
	पूर्ण

	अगर (val < chan->push.addr ||
	    val > chan->push.addr + (chan->dma.max << 2))
		वापस -EINVAL;

	वापस (val - chan->push.addr) >> 2;
पूर्ण

व्योम
nv50_dma_push(काष्ठा nouveau_channel *chan, u64 offset, पूर्णांक length)
अणु
	काष्ठा nvअगर_user *user = &chan->drm->client.device.user;
	काष्ठा nouveau_bo *pb = chan->push.buffer;
	पूर्णांक ip = (chan->dma.ib_put * 2) + chan->dma.ib_base;

	BUG_ON(chan->dma.ib_मुक्त < 1);

	nouveau_bo_wr32(pb, ip++, lower_32_bits(offset));
	nouveau_bo_wr32(pb, ip++, upper_32_bits(offset) | length << 8);

	chan->dma.ib_put = (chan->dma.ib_put + 1) & chan->dma.ib_max;

	mb();
	/* Flush ग_लिखोs. */
	nouveau_bo_rd32(pb, 0);

	nvअगर_wr32(&chan->user, 0x8c, chan->dma.ib_put);
	अगर (user->func && user->func->करोorbell)
		user->func->करोorbell(user, chan->token);
	chan->dma.ib_मुक्त--;
पूर्ण

अटल पूर्णांक
nv50_dma_push_रुको(काष्ठा nouveau_channel *chan, पूर्णांक count)
अणु
	uपूर्णांक32_t cnt = 0, prev_get = 0;

	जबतक (chan->dma.ib_मुक्त < count) अणु
		uपूर्णांक32_t get = nvअगर_rd32(&chan->user, 0x88);
		अगर (get != prev_get) अणु
			prev_get = get;
			cnt = 0;
		पूर्ण

		अगर ((++cnt & 0xff) == 0) अणु
			udelay(1);
			अगर (cnt > 100000)
				वापस -EBUSY;
		पूर्ण

		chan->dma.ib_मुक्त = get - chan->dma.ib_put;
		अगर (chan->dma.ib_मुक्त <= 0)
			chan->dma.ib_मुक्त += chan->dma.ib_max;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_dma_रुको(काष्ठा nouveau_channel *chan, पूर्णांक slots, पूर्णांक count)
अणु
	uपूर्णांक64_t prev_get = 0;
	पूर्णांक ret, cnt = 0;

	ret = nv50_dma_push_रुको(chan, slots + 1);
	अगर (unlikely(ret))
		वापस ret;

	जबतक (chan->dma.मुक्त < count) अणु
		पूर्णांक get = READ_GET(chan, &prev_get, &cnt);
		अगर (unlikely(get < 0)) अणु
			अगर (get == -EINVAL)
				जारी;

			वापस get;
		पूर्ण

		अगर (get <= chan->dma.cur) अणु
			chan->dma.मुक्त = chan->dma.max - chan->dma.cur;
			अगर (chan->dma.मुक्त >= count)
				अवरोध;

			FIRE_RING(chan);
			करो अणु
				get = READ_GET(chan, &prev_get, &cnt);
				अगर (unlikely(get < 0)) अणु
					अगर (get == -EINVAL)
						जारी;
					वापस get;
				पूर्ण
			पूर्ण जबतक (get == 0);
			chan->dma.cur = 0;
			chan->dma.put = 0;
		पूर्ण

		chan->dma.मुक्त = get - chan->dma.cur - 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nouveau_dma_रुको(काष्ठा nouveau_channel *chan, पूर्णांक slots, पूर्णांक size)
अणु
	uपूर्णांक64_t prev_get = 0;
	पूर्णांक cnt = 0, get;

	अगर (chan->dma.ib_max)
		वापस nv50_dma_रुको(chan, slots, size);

	जबतक (chan->dma.मुक्त < size) अणु
		get = READ_GET(chan, &prev_get, &cnt);
		अगर (unlikely(get == -EBUSY))
			वापस -EBUSY;

		/* loop until we have a usable GET poपूर्णांकer.  the value
		 * we पढ़ो from the GPU may be outside the मुख्य ring अगर
		 * PFIFO is processing a buffer called from the मुख्य ring,
		 * discard these values until something sensible is seen.
		 *
		 * the other हाल we discard GET is जबतक the GPU is fetching
		 * from the SKIPS area, so the code below करोesn't have to deal
		 * with some fun corner हालs.
		 */
		अगर (unlikely(get == -EINVAL) || get < NOUVEAU_DMA_SKIPS)
			जारी;

		अगर (get <= chan->dma.cur) अणु
			/* engine is fetching behind us, or is completely
			 * idle (GET == PUT) so we have मुक्त space up until
			 * the end of the push buffer
			 *
			 * we can only hit that path once per call due to
			 * looping back to the beginning of the push buffer,
			 * we'll hit the fetching-ahead-of-us path from that
			 * poपूर्णांक on.
			 *
			 * the *one* exception to that rule is अगर we पढ़ो
			 * GET==PUT, in which हाल the below conditional will
			 * always succeed and अवरोध us out of the रुको loop.
			 */
			chan->dma.मुक्त = chan->dma.max - chan->dma.cur;
			अगर (chan->dma.मुक्त >= size)
				अवरोध;

			/* not enough space left at the end of the push buffer,
			 * inकाष्ठा the GPU to jump back to the start right
			 * after processing the currently pending commands.
			 */
			OUT_RING(chan, chan->push.addr | 0x20000000);

			/* रुको क्रम GET to depart from the skips area.
			 * prevents writing GET==PUT and causing a race
			 * condition that causes us to think the GPU is
			 * idle when it's not.
			 */
			करो अणु
				get = READ_GET(chan, &prev_get, &cnt);
				अगर (unlikely(get == -EBUSY))
					वापस -EBUSY;
				अगर (unlikely(get == -EINVAL))
					जारी;
			पूर्ण जबतक (get <= NOUVEAU_DMA_SKIPS);
			WRITE_PUT(NOUVEAU_DMA_SKIPS);

			/* we're now submitting commands at the start of
			 * the push buffer.
			 */
			chan->dma.cur  =
			chan->dma.put  = NOUVEAU_DMA_SKIPS;
		पूर्ण

		/* engine fetching ahead of us, we have space up until the
		 * current GET poपूर्णांकer.  the "- 1" is to ensure there's
		 * space left to emit a jump back to the beginning of the
		 * push buffer अगर we require it.  we can never get GET == PUT
		 * here, so this is safe.
		 */
		chan->dma.मुक्त = get - chan->dma.cur - 1;
	पूर्ण

	वापस 0;
पूर्ण

