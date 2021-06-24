<शैली गुरु>
#अगर_अघोषित _PIO_H
#घोषणा _PIO_H
/*
 * Copyright(c) 2015-2017 Intel Corporation.
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

/* send context types */
#घोषणा SC_KERNEL 0
#घोषणा SC_VL15   1
#घोषणा SC_ACK    2
#घोषणा SC_USER   3	/* must be the last one: it may take all left */
#घोषणा SC_MAX    4	/* count of send context types */

/* invalid send context index */
#घोषणा INVALID_SCI 0xff

/* PIO buffer release callback function */
प्रकार व्योम (*pio_release_cb)(व्योम *arg, पूर्णांक code);

/* PIO release codes - in bits, as there could more than one that apply */
#घोषणा PRC_OK		0	/* no known error */
#घोषणा PRC_STATUS_ERR	0x01	/* credit वापस due to status error */
#घोषणा PRC_PBC		0x02	/* credit वापस due to PBC */
#घोषणा PRC_THRESHOLD	0x04	/* credit वापस due to threshold */
#घोषणा PRC_FILL_ERR	0x08	/* credit वापस due fill error */
#घोषणा PRC_FORCE	0x10	/* credit वापस due credit क्रमce */
#घोषणा PRC_SC_DISABLE	0x20	/* clean-up after a context disable */

/* byte helper */
जोड़ mix अणु
	u64 val64;
	u32 val32[2];
	u8  val8[8];
पूर्ण;

/* an allocated PIO buffer */
काष्ठा pio_buf अणु
	काष्ठा send_context *sc;/* back poपूर्णांकer to owning send context */
	pio_release_cb cb;	/* called when the buffer is released */
	व्योम *arg;		/* argument क्रम cb */
	व्योम __iomem *start;	/* buffer start address */
	व्योम __iomem *end;	/* context end address */
	अचिन्हित दीर्घ sent_at;	/* buffer is sent when <= मुक्त */
	जोड़ mix carry;	/* pending unwritten bytes */
	u16 qw_written;		/* QW written so far */
	u8 carry_bytes;	/* number of valid bytes in carry */
पूर्ण;

/* cache line aligned pio buffer array */
जोड़ pio_shaकरोw_ring अणु
	काष्ठा pio_buf pbuf;
पूर्ण ____cacheline_aligned;

/* per-NUMA send context */
काष्ठा send_context अणु
	/* पढ़ो-only after init */
	काष्ठा hfi1_devdata *dd;		/* device */
	जोड़ pio_shaकरोw_ring *sr;	/* shaकरोw ring */
	व्योम __iomem *base_addr;	/* start of PIO memory */
	u32 __percpu *buffers_allocated;/* count of buffers allocated */
	u32 size;			/* context size, in bytes */

	पूर्णांक node;			/* context home node */
	u32 sr_size;			/* size of the shaकरोw ring */
	u16 flags;			/* flags */
	u8  type;			/* context type */
	u8  sw_index;			/* software index number */
	u8  hw_context;			/* hardware context number */
	u8  group;			/* credit वापस group */

	/* allocator fields */
	spinlock_t alloc_lock ____cacheline_aligned_in_smp;
	u32 sr_head;			/* shaकरोw ring head */
	अचिन्हित दीर्घ fill;		/* official alloc count */
	अचिन्हित दीर्घ alloc_मुक्त;	/* copy of मुक्त (less cache thrash) */
	u32 fill_wrap;			/* tracks fill within ring */
	u32 credits;			/* number of blocks in context */
	/* adding a new field here would make it part of this cacheline */

	/* releaser fields */
	spinlock_t release_lock ____cacheline_aligned_in_smp;
	u32 sr_tail;			/* shaकरोw ring tail */
	अचिन्हित दीर्घ मुक्त;		/* official मुक्त count */
	अस्थिर __le64 *hw_मुक्त;	/* HW मुक्त counter */
	/* list क्रम PIO रुकोers */
	काष्ठा list_head pioरुको  ____cacheline_aligned_in_smp;
	seqlock_t रुकोlock;

	spinlock_t credit_ctrl_lock ____cacheline_aligned_in_smp;
	u32 credit_पूर्णांकr_count;		/* count of credit पूर्णांकr users */
	u64 credit_ctrl;		/* cache क्रम credit control */
	रुको_queue_head_t halt_रुको;    /* रुको until kernel sees पूर्णांकerrupt */
	काष्ठा work_काष्ठा halt_work;	/* halted context work queue entry */
पूर्ण;

/* send context flags */
#घोषणा SCF_ENABLED 0x01
#घोषणा SCF_IN_FREE 0x02
#घोषणा SCF_HALTED  0x04
#घोषणा SCF_FROZEN  0x08
#घोषणा SCF_LINK_DOWN 0x10

काष्ठा send_context_info अणु
	काष्ठा send_context *sc;	/* allocated working context */
	u16 allocated;			/* has this been allocated? */
	u16 type;			/* context type */
	u16 base;			/* base in PIO array */
	u16 credits;			/* size in PIO array */
पूर्ण;

/* DMA credit वापस, index is always (context & 0x7) */
काष्ठा credit_वापस अणु
	अस्थिर __le64 cr[8];
पूर्ण;

/* NUMA indexed credit वापस array */
काष्ठा credit_वापस_base अणु
	काष्ठा credit_वापस *va;
	dma_addr_t dma;
पूर्ण;

/* send context configuration sizes (one per type) */
काष्ठा sc_config_sizes अणु
	लघु पूर्णांक size;
	लघु पूर्णांक count;
पूर्ण;

/*
 * The diagram below details the relationship of the mapping काष्ठाures
 *
 * Since the mapping now allows क्रम non-unअगरorm send contexts per vl, the
 * number of send contexts क्रम a vl is either the vl_scontexts[vl] or
 * a computation based on num_kernel_send_contexts/num_vls:
 *
 * For example:
 * nactual = vl_scontexts ? vl_scontexts[vl] : num_kernel_send_contexts/num_vls
 *
 * n = roundup to next highest घातer of 2 using nactual
 *
 * In the हाल where there are num_kernel_send_contexts/num_vls करोesn't भागide
 * evenly, the extras are added from the last vl करोwnward.
 *
 * For the हाल where n > nactual, the send contexts are asचिन्हित
 * in a round robin fashion wrapping back to the first send context
 * क्रम a particular vl.
 *
 *               dd->pio_map
 *                    |                                   pio_map_elem[0]
 *                    |                                +--------------------+
 *                    v                                |       mask         |
 *               pio_vl_map                            |--------------------|
 *      +--------------------------+                   | ksc[0] -> sc 1     |
 *      |    list (RCU)            |                   |--------------------|
 *      |--------------------------|                 ->| ksc[1] -> sc 2     |
 *      |    mask                  |              --/  |--------------------|
 *      |--------------------------|            -/     |        *           |
 *      |    actual_vls (max 8)    |          -/       |--------------------|
 *      |--------------------------|       --/         | ksc[n-1] -> sc n   |
 *      |    vls (max 8)           |     -/            +--------------------+
 *      |--------------------------|  --/
 *      |    map[0]                |-/
 *      |--------------------------|                   +--------------------+
 *      |    map[1]                |---                |       mask         |
 *      |--------------------------|   \----           |--------------------|
 *      |           *              |        \--        | ksc[0] -> sc 1+n   |
 *      |           *              |           \----   |--------------------|
 *      |           *              |                \->| ksc[1] -> sc 2+n   |
 *      |--------------------------|                   |--------------------|
 *      |   map[vls - 1]           |-                  |         *          |
 *      +--------------------------+ \-                |--------------------|
 *                                     \-              | ksc[m-1] -> sc m+n |
 *                                       \             +--------------------+
 *                                        \-
 *                                          \
 *                                           \-        +----------------------+
 *                                             \-      |       mask           |
 *                                               \     |----------------------|
 *                                                \-   | ksc[0] -> sc 1+m+n   |
 *                                                  \- |----------------------|
 *                                                    >| ksc[1] -> sc 2+m+n   |
 *                                                     |----------------------|
 *                                                     |         *            |
 *                                                     |----------------------|
 *                                                     | ksc[o-1] -> sc o+m+n |
 *                                                     +----------------------+
 *
 */

/* Initial number of send contexts per VL */
#घोषणा INIT_SC_PER_VL 2

/*
 * काष्ठा pio_map_elem - mapping क्रम a vl
 * @mask - selector mask
 * @ksc - array of kernel send contexts क्रम this vl
 *
 * The mask is used to "mod" the selector to
 * produce index पूर्णांकo the trailing array of
 * kscs
 */
काष्ठा pio_map_elem अणु
	u32 mask;
	काष्ठा send_context *ksc[];
पूर्ण;

/*
 * काष्ठा pio_vl_map - mapping क्रम a vl
 * @list - rcu head क्रम मुक्त callback
 * @mask - vl mask to "mod" the vl to produce an index to map array
 * @actual_vls - number of vls
 * @vls - numbers of vls rounded to next घातer of 2
 * @map - array of pio_map_elem entries
 *
 * This is the parent mapping काष्ठाure. The trailing members of the
 * काष्ठा poपूर्णांक to pio_map_elem entries, which in turn poपूर्णांक to an
 * array of kscs क्रम that vl.
 */
काष्ठा pio_vl_map अणु
	काष्ठा rcu_head list;
	u32 mask;
	u8 actual_vls;
	u8 vls;
	काष्ठा pio_map_elem *map[];
पूर्ण;

पूर्णांक pio_map_init(काष्ठा hfi1_devdata *dd, u8 port, u8 num_vls,
		 u8 *vl_scontexts);
व्योम मुक्त_pio_map(काष्ठा hfi1_devdata *dd);
काष्ठा send_context *pio_select_send_context_vl(काष्ठा hfi1_devdata *dd,
						u32 selector, u8 vl);
काष्ठा send_context *pio_select_send_context_sc(काष्ठा hfi1_devdata *dd,
						u32 selector, u8 sc5);

/* send context functions */
पूर्णांक init_credit_वापस(काष्ठा hfi1_devdata *dd);
व्योम मुक्त_credit_वापस(काष्ठा hfi1_devdata *dd);
पूर्णांक init_sc_pools_and_sizes(काष्ठा hfi1_devdata *dd);
पूर्णांक init_send_contexts(काष्ठा hfi1_devdata *dd);
पूर्णांक init_credit_वापस(काष्ठा hfi1_devdata *dd);
पूर्णांक init_pervl_scs(काष्ठा hfi1_devdata *dd);
काष्ठा send_context *sc_alloc(काष्ठा hfi1_devdata *dd, पूर्णांक type,
			      uपूर्णांक hdrqentsize, पूर्णांक numa);
व्योम sc_मुक्त(काष्ठा send_context *sc);
पूर्णांक sc_enable(काष्ठा send_context *sc);
व्योम sc_disable(काष्ठा send_context *sc);
पूर्णांक sc_restart(काष्ठा send_context *sc);
व्योम sc_वापस_credits(काष्ठा send_context *sc);
व्योम sc_flush(काष्ठा send_context *sc);
व्योम sc_drop(काष्ठा send_context *sc);
व्योम sc_stop(काष्ठा send_context *sc, पूर्णांक bit);
काष्ठा pio_buf *sc_buffer_alloc(काष्ठा send_context *sc, u32 dw_len,
				pio_release_cb cb, व्योम *arg);
व्योम sc_release_update(काष्ठा send_context *sc);
व्योम sc_वापस_credits(काष्ठा send_context *sc);
व्योम sc_group_release_update(काष्ठा hfi1_devdata *dd, u32 hw_context);
व्योम sc_add_credit_वापस_पूर्णांकr(काष्ठा send_context *sc);
व्योम sc_del_credit_वापस_पूर्णांकr(काष्ठा send_context *sc);
व्योम sc_set_cr_threshold(काष्ठा send_context *sc, u32 new_threshold);
u32 sc_percent_to_threshold(काष्ठा send_context *sc, u32 percent);
u32 sc_mtu_to_threshold(काष्ठा send_context *sc, u32 mtu, u32 hdrqentsize);
व्योम hfi1_sc_wantpiobuf_पूर्णांकr(काष्ठा send_context *sc, u32 needपूर्णांक);
व्योम sc_रुको(काष्ठा hfi1_devdata *dd);
व्योम set_pio_पूर्णांकegrity(काष्ठा send_context *sc);

/* support functions */
व्योम pio_reset_all(काष्ठा hfi1_devdata *dd);
व्योम pio_मुक्तze(काष्ठा hfi1_devdata *dd);
व्योम pio_kernel_unमुक्तze(काष्ठा hfi1_devdata *dd);
व्योम pio_kernel_linkup(काष्ठा hfi1_devdata *dd);

/* global PIO send control operations */
#घोषणा PSC_GLOBAL_ENABLE 0
#घोषणा PSC_GLOBAL_DISABLE 1
#घोषणा PSC_GLOBAL_VLARB_ENABLE 2
#घोषणा PSC_GLOBAL_VLARB_DISABLE 3
#घोषणा PSC_CM_RESET 4
#घोषणा PSC_DATA_VL_ENABLE 5
#घोषणा PSC_DATA_VL_DISABLE 6

व्योम __cm_reset(काष्ठा hfi1_devdata *dd, u64 sendctrl);
व्योम pio_send_control(काष्ठा hfi1_devdata *dd, पूर्णांक op);

/* PIO copy routines */
व्योम pio_copy(काष्ठा hfi1_devdata *dd, काष्ठा pio_buf *pbuf, u64 pbc,
	      स्थिर व्योम *from, माप_प्रकार count);
व्योम seg_pio_copy_start(काष्ठा pio_buf *pbuf, u64 pbc,
			स्थिर व्योम *from, माप_प्रकार nbytes);
व्योम seg_pio_copy_mid(काष्ठा pio_buf *pbuf, स्थिर व्योम *from, माप_प्रकार nbytes);
व्योम seg_pio_copy_end(काष्ठा pio_buf *pbuf);

व्योम seqfile_dump_sci(काष्ठा seq_file *s, u32 i,
		      काष्ठा send_context_info *sci);

#पूर्ण_अगर /* _PIO_H */
