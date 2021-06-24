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

#अगर_अघोषित __FSL_BMAN_H
#घोषणा __FSL_BMAN_H

/* wrapper क्रम 48-bit buffers */
काष्ठा bm_buffer अणु
	जोड़ अणु
		काष्ठा अणु
			__be16 bpid; /* hi 8-bits reserved */
			__be16 hi; /* High 16-bits of 48-bit address */
			__be32 lo; /* Low 32-bits of 48-bit address */
		पूर्ण;
		__be64 data;
	पूर्ण;
पूर्ण __aligned(8);
/*
 * Restore the 48 bit address previously stored in BMan
 * hardware pools as a dma_addr_t
 */
अटल अंतरभूत dma_addr_t bm_buf_addr(स्थिर काष्ठा bm_buffer *buf)
अणु
	वापस be64_to_cpu(buf->data) & 0xffffffffffffLLU;
पूर्ण

अटल अंतरभूत u64 bm_buffer_get64(स्थिर काष्ठा bm_buffer *buf)
अणु
	वापस be64_to_cpu(buf->data) & 0xffffffffffffLLU;
पूर्ण

अटल अंतरभूत व्योम bm_buffer_set64(काष्ठा bm_buffer *buf, u64 addr)
अणु
	buf->hi = cpu_to_be16(upper_32_bits(addr));
	buf->lo = cpu_to_be32(lower_32_bits(addr));
पूर्ण

अटल अंतरभूत u8 bm_buffer_get_bpid(स्थिर काष्ठा bm_buffer *buf)
अणु
	वापस be16_to_cpu(buf->bpid) & 0xff;
पूर्ण

अटल अंतरभूत व्योम bm_buffer_set_bpid(काष्ठा bm_buffer *buf, पूर्णांक bpid)
अणु
	buf->bpid = cpu_to_be16(bpid & 0xff);
पूर्ण

/* Managed portal, high-level i/face */

/* Portal and Buffer Pools */
काष्ठा bman_portal;
काष्ठा bman_pool;

#घोषणा BM_POOL_MAX		64 /* max # of buffer pools */

/**
 * bman_new_pool - Allocates a Buffer Pool object
 *
 * Creates a pool object, and वापसs a reference to it or शून्य on error.
 */
काष्ठा bman_pool *bman_new_pool(व्योम);

/**
 * bman_मुक्त_pool - Deallocates a Buffer Pool object
 * @pool: the pool object to release
 */
व्योम bman_मुक्त_pool(काष्ठा bman_pool *pool);

/**
 * bman_get_bpid - Returns a pool object's BPID.
 * @pool: the pool object
 *
 * The वापसed value is the index of the encapsulated buffer pool,
 * in the range of [0, @BM_POOL_MAX-1].
 */
पूर्णांक bman_get_bpid(स्थिर काष्ठा bman_pool *pool);

/**
 * bman_release - Release buffer(s) to the buffer pool
 * @pool: the buffer pool object to release to
 * @bufs: an array of buffers to release
 * @num: the number of buffers in @bufs (1-8)
 *
 * Adds the given buffers to RCR entries. If the RCR ring is unresponsive,
 * the function will वापस -ETIMEDOUT. Otherwise, it वापसs zero.
 */
पूर्णांक bman_release(काष्ठा bman_pool *pool, स्थिर काष्ठा bm_buffer *bufs, u8 num);

/**
 * bman_acquire - Acquire buffer(s) from a buffer pool
 * @pool: the buffer pool object to acquire from
 * @bufs: array क्रम storing the acquired buffers
 * @num: the number of buffers desired (@bufs is at least this big)
 *
 * Issues an "Acquire" command via the portal's management command पूर्णांकerface.
 * The वापस value will be the number of buffers obtained from the pool, or a
 * negative error code अगर a h/w error or pool starvation was encountered. In
 * the latter हाल, the content of @bufs is undefined.
 */
पूर्णांक bman_acquire(काष्ठा bman_pool *pool, काष्ठा bm_buffer *bufs, u8 num);

/**
 * bman_is_probed - Check अगर bman is probed
 *
 * Returns 1 अगर the bman driver successfully probed, -1 अगर the bman driver
 * failed to probe or 0 अगर the bman driver did not probed yet.
 */
पूर्णांक bman_is_probed(व्योम);
/**
 * bman_portals_probed - Check अगर all cpu bound bman portals are probed
 *
 * Returns 1 अगर all the required cpu bound bman portals successfully probed,
 * -1 अगर probe errors appeared or 0 अगर the bman portals did not yet finished
 * probing.
 */
पूर्णांक bman_portals_probed(व्योम);

#पूर्ण_अगर	/* __FSL_BMAN_H */
