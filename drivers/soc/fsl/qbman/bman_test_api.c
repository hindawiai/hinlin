<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "bman_test.h"

#घोषणा NUM_BUFS	93
#घोषणा LOOPS		3
#घोषणा BMAN_TOKEN_MASK 0x00FFFFFFFFFFLLU

अटल काष्ठा bman_pool *pool;
अटल काष्ठा bm_buffer bufs_in[NUM_BUFS] ____cacheline_aligned;
अटल काष्ठा bm_buffer bufs_out[NUM_BUFS] ____cacheline_aligned;
अटल पूर्णांक bufs_received;

अटल व्योम bufs_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_BUFS; i++)
		bm_buffer_set64(&bufs_in[i], 0xfedc01234567LLU * i);
	bufs_received = 0;
पूर्ण

अटल अंतरभूत पूर्णांक bufs_cmp(स्थिर काष्ठा bm_buffer *a, स्थिर काष्ठा bm_buffer *b)
अणु
	अगर (bman_ip_rev == BMAN_REV20 || bman_ip_rev == BMAN_REV21) अणु

		/*
		 * On SoCs with BMan revison 2.0, BMan only respects the 40
		 * LS-bits of buffer addresses, masking off the upper 8-bits on
		 * release commands. The API provides क्रम 48-bit addresses
		 * because some SoCs support all 48-bits. When generating
		 * garbage addresses क्रम testing, we either need to zero the
		 * upper 8-bits when releasing to BMan (otherwise we'll be
		 * disappoपूर्णांकed when the buffers we acquire back from BMan
		 * करोn't match), or we need to mask the upper 8-bits off when
		 * comparing. We करो the latter.
		 */
		अगर ((bm_buffer_get64(a) & BMAN_TOKEN_MASK) <
		    (bm_buffer_get64(b) & BMAN_TOKEN_MASK))
			वापस -1;
		अगर ((bm_buffer_get64(a) & BMAN_TOKEN_MASK) >
		    (bm_buffer_get64(b) & BMAN_TOKEN_MASK))
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (bm_buffer_get64(a) < bm_buffer_get64(b))
			वापस -1;
		अगर (bm_buffer_get64(a) > bm_buffer_get64(b))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bufs_confirm(व्योम)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < NUM_BUFS; i++) अणु
		पूर्णांक matches = 0;

		क्रम (j = 0; j < NUM_BUFS; j++)
			अगर (!bufs_cmp(&bufs_in[i], &bufs_out[j]))
				matches++;
		WARN_ON(matches != 1);
	पूर्ण
पूर्ण

/* test */
व्योम bman_test_api(व्योम)
अणु
	पूर्णांक i, loops = LOOPS;

	bufs_init();

	pr_info("%s(): Starting\n", __func__);

	pool = bman_new_pool();
	अगर (!pool) अणु
		pr_crit("bman_new_pool() failed\n");
		जाओ failed;
	पूर्ण

	/* Release buffers */
करो_loop:
	i = 0;
	जबतक (i < NUM_BUFS) अणु
		पूर्णांक num = 8;

		अगर (i + num > NUM_BUFS)
			num = NUM_BUFS - i;
		अगर (bman_release(pool, bufs_in + i, num)) अणु
			pr_crit("bman_release() failed\n");
			जाओ failed;
		पूर्ण
		i += num;
	पूर्ण

	/* Acquire buffers */
	जबतक (i > 0) अणु
		पूर्णांक पंचांगp, num = 8;

		अगर (num > i)
			num = i;
		पंचांगp = bman_acquire(pool, bufs_out + i - num, num);
		WARN_ON(पंचांगp != num);
		i -= num;
	पूर्ण
	i = bman_acquire(pool, शून्य, 1);
	WARN_ON(i > 0);

	bufs_confirm();

	अगर (--loops)
		जाओ करो_loop;

	/* Clean up */
	bman_मुक्त_pool(pool);
	pr_info("%s(): Finished\n", __func__);
	वापस;

failed:
	WARN_ON(1);
पूर्ण
