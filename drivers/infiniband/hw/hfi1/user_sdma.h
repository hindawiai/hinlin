<शैली गुरु>
#अगर_अघोषित _HFI1_USER_SDMA_H
#घोषणा _HFI1_USER_SDMA_H
/*
 * Copyright(c) 2020 - Cornelis Networks, Inc.
 * Copyright(c) 2015 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>

#समावेश "common.h"
#समावेश "iowait.h"
#समावेश "user_exp_rcv.h"
#समावेश "mmu_rb.h"

/* The maximum number of Data io vectors per message/request */
#घोषणा MAX_VECTORS_PER_REQ 8
/*
 * Maximum number of packet to send from each message/request
 * beक्रमe moving to the next one.
 */
#घोषणा MAX_PKTS_PER_QUEUE 16

#घोषणा num_pages(x) (1 + ((((x) - 1) & PAGE_MASK) >> PAGE_SHIFT))

#घोषणा req_opcode(x) \
	(((x) >> HFI1_SDMA_REQ_OPCODE_SHIFT) & HFI1_SDMA_REQ_OPCODE_MASK)
#घोषणा req_version(x) \
	(((x) >> HFI1_SDMA_REQ_VERSION_SHIFT) & HFI1_SDMA_REQ_OPCODE_MASK)
#घोषणा req_iovcnt(x) \
	(((x) >> HFI1_SDMA_REQ_IOVCNT_SHIFT) & HFI1_SDMA_REQ_IOVCNT_MASK)

/* Number of BTH.PSN bits used क्रम sequence number in expected rcvs */
#घोषणा BTH_SEQ_MASK 0x7ffull

#घोषणा AHG_KDETH_INTR_SHIFT 12
#घोषणा AHG_KDETH_SH_SHIFT   13
#घोषणा AHG_KDETH_ARRAY_SIZE  9

#घोषणा PBC2LRH(x) ((((x) & 0xfff) << 2) - 4)
#घोषणा LRH2PBC(x) ((((x) >> 2) + 1) & 0xfff)

/**
 * Build an SDMA AHG header update descriptor and save it to an array.
 * @arr        - Array to save the descriptor to.
 * @idx        - Index of the array at which the descriptor will be saved.
 * @array_size - Size of the array arr.
 * @dw         - Update index पूर्णांकo the header in DWs.
 * @bit        - Start bit.
 * @width      - Field width.
 * @value      - 16 bits of immediate data to ग_लिखो पूर्णांकo the field.
 * Returns -दुस्फल अगर idx is invalid. If successful, वापसs the next index
 * (idx + 1) of the array to be used क्रम the next descriptor.
 */
अटल अंतरभूत पूर्णांक ahg_header_set(u32 *arr, पूर्णांक idx, माप_प्रकार array_size,
				 u8 dw, u8 bit, u8 width, u16 value)
अणु
	अगर ((माप_प्रकार)idx >= array_size)
		वापस -दुस्फल;
	arr[idx++] = sdma_build_ahg_descriptor(value, dw, bit, width);
	वापस idx;
पूर्ण

/* Tx request flag bits */
#घोषणा TXREQ_FLAGS_REQ_ACK   BIT(0)      /* Set the ACK bit in the header */
#घोषणा TXREQ_FLAGS_REQ_DISABLE_SH BIT(1) /* Disable header suppression */

क्रमागत pkt_q_sdma_state अणु
	SDMA_PKT_Q_ACTIVE,
	SDMA_PKT_Q_DEFERRED,
पूर्ण;

#घोषणा SDMA_IOWAIT_TIMEOUT 1000 /* in milliseconds */

#घोषणा SDMA_DBG(req, fmt, ...)				     \
	hfi1_cdbg(SDMA, "[%u:%u:%u:%u] " fmt, (req)->pq->dd->unit, \
		 (req)->pq->ctxt, (req)->pq->subctxt, (req)->info.comp_idx, \
		 ##__VA_ARGS__)

काष्ठा hfi1_user_sdma_pkt_q अणु
	u16 ctxt;
	u16 subctxt;
	u16 n_max_reqs;
	atomic_t n_reqs;
	u16 reqidx;
	काष्ठा hfi1_devdata *dd;
	काष्ठा kmem_cache *txreq_cache;
	काष्ठा user_sdma_request *reqs;
	अचिन्हित दीर्घ *req_in_use;
	काष्ठा ioरुको busy;
	क्रमागत pkt_q_sdma_state state;
	रुको_queue_head_t रुको;
	अचिन्हित दीर्घ unpinned;
	काष्ठा mmu_rb_handler *handler;
	atomic_t n_locked;
पूर्ण;

काष्ठा hfi1_user_sdma_comp_q अणु
	u16 nentries;
	काष्ठा hfi1_sdma_comp_entry *comps;
पूर्ण;

काष्ठा sdma_mmu_node अणु
	काष्ठा mmu_rb_node rb;
	काष्ठा hfi1_user_sdma_pkt_q *pq;
	atomic_t refcount;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक npages;
पूर्ण;

काष्ठा user_sdma_iovec अणु
	काष्ठा list_head list;
	काष्ठा iovec iov;
	/* number of pages in this vector */
	अचिन्हित पूर्णांक npages;
	/* array of pinned pages क्रम this vector */
	काष्ठा page **pages;
	/*
	 * offset पूर्णांकo the भव address space of the vector at
	 * which we last left off.
	 */
	u64 offset;
	काष्ठा sdma_mmu_node *node;
पूर्ण;

/* evict operation argument */
काष्ठा evict_data अणु
	u32 cleared;	/* count evicted so far */
	u32 target;	/* target count to evict */
पूर्ण;

काष्ठा user_sdma_request अणु
	/* This is the original header from user space */
	काष्ठा hfi1_pkt_header hdr;

	/* Read mostly fields */
	काष्ठा hfi1_user_sdma_pkt_q *pq ____cacheline_aligned_in_smp;
	काष्ठा hfi1_user_sdma_comp_q *cq;
	/*
	 * Poपूर्णांकer to the SDMA engine क्रम this request.
	 * Since dअगरferent request could be on dअगरferent VLs,
	 * each request will need it's own engine poपूर्णांकer.
	 */
	काष्ठा sdma_engine *sde;
	काष्ठा sdma_req_info info;
	/* TID array values copied from the tid_iov vector */
	u32 *tids;
	/* total length of the data in the request */
	u32 data_len;
	/* number of elements copied to the tids array */
	u16 n_tids;
	/*
	 * We copy the iovs क्रम this request (based on
	 * info.iovcnt). These are only the data vectors
	 */
	u8 data_iovs;
	s8 ahg_idx;

	/* Writeable fields shared with पूर्णांकerrupt */
	u16 seqcomp ____cacheline_aligned_in_smp;
	u16 seqsubmitted;

	/* Send side fields */
	काष्ठा list_head txps ____cacheline_aligned_in_smp;
	u16 seqnum;
	/*
	 * KDETH.OFFSET (TID) field
	 * The offset can cover multiple packets, depending on the
	 * size of the TID entry.
	 */
	u32 tiकरोffset;
	/*
	 * KDETH.Offset (Eager) field
	 * We need to remember the initial value so the headers
	 * can be updated properly.
	 */
	u32 koffset;
	u32 sent;
	/* TID index copied from the tid_iov vector */
	u16 tididx;
	/* progress index moving aदीर्घ the iovs array */
	u8 iov_idx;
	u8 has_error;

	काष्ठा user_sdma_iovec iovs[MAX_VECTORS_PER_REQ];
पूर्ण ____cacheline_aligned_in_smp;

/*
 * A single txreq could span up to 3 physical pages when the MTU
 * is sufficiently large (> 4K). Each of the IOV poपूर्णांकers also
 * needs it's own set of flags so the vector has been handled
 * independently of each other.
 */
काष्ठा user_sdma_txreq अणु
	/* Packet header क्रम the txreq */
	काष्ठा hfi1_pkt_header hdr;
	काष्ठा sdma_txreq txreq;
	काष्ठा list_head list;
	काष्ठा user_sdma_request *req;
	u16 flags;
	u16 seqnum;
पूर्ण;

पूर्णांक hfi1_user_sdma_alloc_queues(काष्ठा hfi1_ctxtdata *uctxt,
				काष्ठा hfi1_filedata *fd);
पूर्णांक hfi1_user_sdma_मुक्त_queues(काष्ठा hfi1_filedata *fd,
			       काष्ठा hfi1_ctxtdata *uctxt);
पूर्णांक hfi1_user_sdma_process_request(काष्ठा hfi1_filedata *fd,
				   काष्ठा iovec *iovec, अचिन्हित दीर्घ dim,
				   अचिन्हित दीर्घ *count);

अटल अंतरभूत काष्ठा mm_काष्ठा *mm_from_sdma_node(काष्ठा sdma_mmu_node *node)
अणु
	वापस node->rb.handler->mn.mm;
पूर्ण

#पूर्ण_अगर /* _HFI1_USER_SDMA_H */
