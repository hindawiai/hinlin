<शैली गुरु>
#अगर_अघोषित _HFI1_SDMA_H
#घोषणा _HFI1_SDMA_H
/*
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

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rculist.h>

#समावेश "hfi.h"
#समावेश "verbs.h"
#समावेश "sdma_txreq.h"

/* Hardware limit */
#घोषणा MAX_DESC 64
/* Hardware limit क्रम SDMA packet size */
#घोषणा MAX_SDMA_PKT_SIZE ((16 * 1024) - 1)

#घोषणा SDMA_MAP_NONE          0
#घोषणा SDMA_MAP_SINGLE        1
#घोषणा SDMA_MAP_PAGE          2

#घोषणा SDMA_AHG_VALUE_MASK          0xffff
#घोषणा SDMA_AHG_VALUE_SHIFT         0
#घोषणा SDMA_AHG_INDEX_MASK          0xf
#घोषणा SDMA_AHG_INDEX_SHIFT         16
#घोषणा SDMA_AHG_FIELD_LEN_MASK      0xf
#घोषणा SDMA_AHG_FIELD_LEN_SHIFT     20
#घोषणा SDMA_AHG_FIELD_START_MASK    0x1f
#घोषणा SDMA_AHG_FIELD_START_SHIFT   24
#घोषणा SDMA_AHG_UPDATE_ENABLE_MASK  0x1
#घोषणा SDMA_AHG_UPDATE_ENABLE_SHIFT 31

/* AHG modes */

/*
 * Be aware the ordering and values
 * क्रम SDMA_AHG_APPLY_UPDATE[123]
 * are assumed in generating a skip
 * count in submit_tx() in sdma.c
 */
#घोषणा SDMA_AHG_NO_AHG              0
#घोषणा SDMA_AHG_COPY                1
#घोषणा SDMA_AHG_APPLY_UPDATE1       2
#घोषणा SDMA_AHG_APPLY_UPDATE2       3
#घोषणा SDMA_AHG_APPLY_UPDATE3       4

/*
 * Bits defined in the send DMA descriptor.
 */
#घोषणा SDMA_DESC0_FIRST_DESC_FLAG      BIT_ULL(63)
#घोषणा SDMA_DESC0_LAST_DESC_FLAG       BIT_ULL(62)
#घोषणा SDMA_DESC0_BYTE_COUNT_SHIFT     48
#घोषणा SDMA_DESC0_BYTE_COUNT_WIDTH     14
#घोषणा SDMA_DESC0_BYTE_COUNT_MASK \
	((1ULL << SDMA_DESC0_BYTE_COUNT_WIDTH) - 1)
#घोषणा SDMA_DESC0_BYTE_COUNT_SMASK \
	(SDMA_DESC0_BYTE_COUNT_MASK << SDMA_DESC0_BYTE_COUNT_SHIFT)
#घोषणा SDMA_DESC0_PHY_ADDR_SHIFT       0
#घोषणा SDMA_DESC0_PHY_ADDR_WIDTH       48
#घोषणा SDMA_DESC0_PHY_ADDR_MASK \
	((1ULL << SDMA_DESC0_PHY_ADDR_WIDTH) - 1)
#घोषणा SDMA_DESC0_PHY_ADDR_SMASK \
	(SDMA_DESC0_PHY_ADDR_MASK << SDMA_DESC0_PHY_ADDR_SHIFT)

#घोषणा SDMA_DESC1_HEADER_UPDATE1_SHIFT 32
#घोषणा SDMA_DESC1_HEADER_UPDATE1_WIDTH 32
#घोषणा SDMA_DESC1_HEADER_UPDATE1_MASK \
	((1ULL << SDMA_DESC1_HEADER_UPDATE1_WIDTH) - 1)
#घोषणा SDMA_DESC1_HEADER_UPDATE1_SMASK \
	(SDMA_DESC1_HEADER_UPDATE1_MASK << SDMA_DESC1_HEADER_UPDATE1_SHIFT)
#घोषणा SDMA_DESC1_HEADER_MODE_SHIFT    13
#घोषणा SDMA_DESC1_HEADER_MODE_WIDTH    3
#घोषणा SDMA_DESC1_HEADER_MODE_MASK \
	((1ULL << SDMA_DESC1_HEADER_MODE_WIDTH) - 1)
#घोषणा SDMA_DESC1_HEADER_MODE_SMASK \
	(SDMA_DESC1_HEADER_MODE_MASK << SDMA_DESC1_HEADER_MODE_SHIFT)
#घोषणा SDMA_DESC1_HEADER_INDEX_SHIFT   8
#घोषणा SDMA_DESC1_HEADER_INDEX_WIDTH   5
#घोषणा SDMA_DESC1_HEADER_INDEX_MASK \
	((1ULL << SDMA_DESC1_HEADER_INDEX_WIDTH) - 1)
#घोषणा SDMA_DESC1_HEADER_INDEX_SMASK \
	(SDMA_DESC1_HEADER_INDEX_MASK << SDMA_DESC1_HEADER_INDEX_SHIFT)
#घोषणा SDMA_DESC1_HEADER_DWS_SHIFT     4
#घोषणा SDMA_DESC1_HEADER_DWS_WIDTH     4
#घोषणा SDMA_DESC1_HEADER_DWS_MASK \
	((1ULL << SDMA_DESC1_HEADER_DWS_WIDTH) - 1)
#घोषणा SDMA_DESC1_HEADER_DWS_SMASK \
	(SDMA_DESC1_HEADER_DWS_MASK << SDMA_DESC1_HEADER_DWS_SHIFT)
#घोषणा SDMA_DESC1_GENERATION_SHIFT     2
#घोषणा SDMA_DESC1_GENERATION_WIDTH     2
#घोषणा SDMA_DESC1_GENERATION_MASK \
	((1ULL << SDMA_DESC1_GENERATION_WIDTH) - 1)
#घोषणा SDMA_DESC1_GENERATION_SMASK \
	(SDMA_DESC1_GENERATION_MASK << SDMA_DESC1_GENERATION_SHIFT)
#घोषणा SDMA_DESC1_INT_REQ_FLAG         BIT_ULL(1)
#घोषणा SDMA_DESC1_HEAD_TO_HOST_FLAG    BIT_ULL(0)

क्रमागत sdma_states अणु
	sdma_state_s00_hw_करोwn,
	sdma_state_s10_hw_start_up_halt_रुको,
	sdma_state_s15_hw_start_up_clean_रुको,
	sdma_state_s20_idle,
	sdma_state_s30_sw_clean_up_रुको,
	sdma_state_s40_hw_clean_up_रुको,
	sdma_state_s50_hw_halt_रुको,
	sdma_state_s60_idle_halt_रुको,
	sdma_state_s80_hw_मुक्तze,
	sdma_state_s82_मुक्तze_sw_clean,
	sdma_state_s99_running,
पूर्ण;

क्रमागत sdma_events अणु
	sdma_event_e00_go_hw_करोwn,
	sdma_event_e10_go_hw_start,
	sdma_event_e15_hw_halt_करोne,
	sdma_event_e25_hw_clean_up_करोne,
	sdma_event_e30_go_running,
	sdma_event_e40_sw_cleaned,
	sdma_event_e50_hw_cleaned,
	sdma_event_e60_hw_halted,
	sdma_event_e70_go_idle,
	sdma_event_e80_hw_मुक्तze,
	sdma_event_e81_hw_frozen,
	sdma_event_e82_hw_unमुक्तze,
	sdma_event_e85_link_करोwn,
	sdma_event_e90_sw_halted,
पूर्ण;

काष्ठा sdma_set_state_action अणु
	अचिन्हित op_enable:1;
	अचिन्हित op_पूर्णांकenable:1;
	अचिन्हित op_halt:1;
	अचिन्हित op_cleanup:1;
	अचिन्हित go_s99_running_tofalse:1;
	अचिन्हित go_s99_running_totrue:1;
पूर्ण;

काष्ठा sdma_state अणु
	काष्ठा kref          kref;
	काष्ठा completion    comp;
	क्रमागत sdma_states current_state;
	अचिन्हित             current_op;
	अचिन्हित             go_s99_running;
	/* debugging/development */
	क्रमागत sdma_states previous_state;
	अचिन्हित             previous_op;
	क्रमागत sdma_events last_event;
पूर्ण;

/**
 * DOC: sdma exported routines
 *
 * These sdma routines fit पूर्णांकo three categories:
 * - The SDMA API क्रम building and submitting packets
 *   to the ring
 *
 * - Initialization and tear करोwn routines to buildup
 *   and tear करोwn SDMA
 *
 * - ISR entrances to handle पूर्णांकerrupts, state changes
 *   and errors
 */

/**
 * DOC: sdma PSM/verbs API
 *
 * The sdma API is deचिन्हित to be used by both PSM
 * and verbs to supply packets to the SDMA ring.
 *
 * The usage of the API is as follows:
 *
 * Embed a काष्ठा ioरुको in the QP or
 * PQ.  The ioरुको should be initialized with a
 * call to ioरुको_init().
 *
 * The user of the API should create an allocation method
 * क्रम their version of the txreq. sद_असल, pre-allocated lists,
 * and dma pools can be used.  Once the user's overload of
 * the sdma_txreq has been allocated, the sdma_txreq member
 * must be initialized with sdma_txinit() or sdma_txinit_ahg().
 *
 * The txreq must be declared with the sdma_txreq first.
 *
 * The tx request, once initialized,  is manipulated with calls to
 * sdma_txadd_daddr(), sdma_txadd_page(), or sdma_txadd_kvaddr()
 * क्रम each disjoपूर्णांक memory location.  It is the user's responsibility
 * to understand the packet boundaries and page boundaries to करो the
 * appropriate number of sdma_txadd_* calls..  The user
 * must be prepared to deal with failures from these routines due to
 * either memory allocation or dma_mapping failures.
 *
 * The mapping specअगरics क्रम each memory location are recorded
 * in the tx. Memory locations added with sdma_txadd_page()
 * and sdma_txadd_kvaddr() are स्वतःmatically mapped when added
 * to the tx and nmapped as part of the progress processing in the
 * SDMA पूर्णांकerrupt handling.
 *
 * sdma_txadd_daddr() is used to add an dma_addr_t memory to the
 * tx.   An example of a use हाल would be a pre-allocated
 * set of headers allocated via dma_pool_alloc() or
 * dma_alloc_coherent().  For these memory locations, it
 * is the responsibility of the user to handle that unmapping.
 * (This would usually be at an unload or job termination.)
 *
 * The routine sdma_send_txreq() is used to submit
 * a tx to the ring after the appropriate number of
 * sdma_txadd_* have been करोne.
 *
 * If it is desired to send a burst of sdma_txreqs, sdma_send_txlist()
 * can be used to submit a list of packets.
 *
 * The user is मुक्त to use the link overhead in the काष्ठा sdma_txreq as
 * दीर्घ as the tx isn't in flight.
 *
 * The extreme degenerate हाल of the number of descriptors
 * exceeding the ring size is स्वतःmatically handled as
 * memory locations are added.  An overflow of the descriptor
 * array that is part of the sdma_txreq is also स्वतःmatically
 * handled.
 *
 */

/**
 * DOC: Infraकाष्ठाure calls
 *
 * sdma_init() is used to initialize data काष्ठाures and
 * CSRs क्रम the desired number of SDMA engines.
 *
 * sdma_start() is used to kick the SDMA engines initialized
 * with sdma_init().   Interrupts must be enabled at this
 * poपूर्णांक since aspects of the state machine are पूर्णांकerrupt
 * driven.
 *
 * sdma_engine_error() and sdma_engine_पूर्णांकerrupt() are
 * entrances क्रम पूर्णांकerrupts.
 *
 * sdma_map_init() is क्रम the management of the mapping
 * table when the number of vls is changed.
 *
 */

/*
 * काष्ठा hw_sdma_desc - raw 128 bit SDMA descriptor
 *
 * This is the raw descriptor in the SDMA ring
 */
काष्ठा hw_sdma_desc अणु
	/* निजी:  करोn't use directly */
	__le64 qw[2];
पूर्ण;

/**
 * काष्ठा sdma_engine - Data pertaining to each SDMA engine.
 * @dd: a back-poपूर्णांकer to the device data
 * @ppd: per port back-poपूर्णांकer
 * @imask: mask क्रम irq manipulation
 * @idle_mask: mask क्रम determining अगर an पूर्णांकerrupt is due to sdma_idle
 *
 * This काष्ठाure has the state क्रम each sdma_engine.
 *
 * Accessing to non खुला fields are not supported
 * since the निजी members are subject to change.
 */
काष्ठा sdma_engine अणु
	/* पढ़ो mostly */
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_pportdata *ppd;
	/* निजी: */
	व्योम __iomem *tail_csr;
	u64 imask;			/* clear पूर्णांकerrupt mask */
	u64 idle_mask;
	u64 progress_mask;
	u64 पूर्णांक_mask;
	/* निजी: */
	अस्थिर __le64      *head_dma; /* DMA'ed by chip */
	/* निजी: */
	dma_addr_t            head_phys;
	/* निजी: */
	काष्ठा hw_sdma_desc *descq;
	/* निजी: */
	अचिन्हित descq_full_count;
	काष्ठा sdma_txreq **tx_ring;
	/* निजी: */
	dma_addr_t            descq_phys;
	/* निजी */
	u32 sdma_mask;
	/* निजी */
	काष्ठा sdma_state state;
	/* निजी */
	पूर्णांक cpu;
	/* निजी: */
	u8 sdma_shअगरt;
	/* निजी: */
	u8 this_idx; /* zero relative engine */
	/* protect changes to senddmactrl shaकरोw */
	spinlock_t senddmactrl_lock;
	/* निजी: */
	u64 p_senddmactrl;		/* shaकरोw per-engine SendDmaCtrl */

	/* पढ़ो/ग_लिखो using tail_lock */
	spinlock_t            tail_lock ____cacheline_aligned_in_smp;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	/* निजी: */
	u64                   tail_sn;
#पूर्ण_अगर
	/* निजी: */
	u32                   descq_tail;
	/* निजी: */
	अचिन्हित दीर्घ         ahg_bits;
	/* निजी: */
	u16                   desc_avail;
	/* निजी: */
	u16                   tx_tail;
	/* निजी: */
	u16 descq_cnt;

	/* पढ़ो/ग_लिखो using head_lock */
	/* निजी: */
	seqlock_t            head_lock ____cacheline_aligned_in_smp;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	/* निजी: */
	u64                   head_sn;
#पूर्ण_अगर
	/* निजी: */
	u32                   descq_head;
	/* निजी: */
	u16                   tx_head;
	/* निजी: */
	u64                   last_status;
	/* निजी */
	u64                     err_cnt;
	/* निजी */
	u64                     sdma_पूर्णांक_cnt;
	u64                     idle_पूर्णांक_cnt;
	u64                     progress_पूर्णांक_cnt;

	/* निजी: */
	seqlock_t            रुकोlock;
	काष्ठा list_head      dmaरुको;

	/* CONFIG SDMA क्रम now, just blindly duplicate */
	/* निजी: */
	काष्ठा tasklet_काष्ठा sdma_hw_clean_up_task
		____cacheline_aligned_in_smp;

	/* निजी: */
	काष्ठा tasklet_काष्ठा sdma_sw_clean_up_task
		____cacheline_aligned_in_smp;
	/* निजी: */
	काष्ठा work_काष्ठा err_halt_worker;
	/* निजी */
	काष्ठा समयr_list     err_progress_check_समयr;
	u32                   progress_check_head;
	/* निजी: */
	काष्ठा work_काष्ठा flush_worker;
	/* protect flush list */
	spinlock_t flushlist_lock;
	/* निजी: */
	काष्ठा list_head flushlist;
	काष्ठा cpumask cpu_mask;
	काष्ठा kobject kobj;
	u32 msix_पूर्णांकr;
पूर्ण;

पूर्णांक sdma_init(काष्ठा hfi1_devdata *dd, u8 port);
व्योम sdma_start(काष्ठा hfi1_devdata *dd);
व्योम sdma_निकास(काष्ठा hfi1_devdata *dd);
व्योम sdma_clean(काष्ठा hfi1_devdata *dd, माप_प्रकार num_engines);
व्योम sdma_all_running(काष्ठा hfi1_devdata *dd);
व्योम sdma_all_idle(काष्ठा hfi1_devdata *dd);
व्योम sdma_मुक्तze_notअगरy(काष्ठा hfi1_devdata *dd, पूर्णांक go_idle);
व्योम sdma_मुक्तze(काष्ठा hfi1_devdata *dd);
व्योम sdma_unमुक्तze(काष्ठा hfi1_devdata *dd);
व्योम sdma_रुको(काष्ठा hfi1_devdata *dd);

/**
 * sdma_empty() - idle engine test
 * @engine: sdma engine
 *
 * Currently used by verbs as a latency optimization.
 *
 * Return:
 * 1 - empty, 0 - non-empty
 */
अटल अंतरभूत पूर्णांक sdma_empty(काष्ठा sdma_engine *sde)
अणु
	वापस sde->descq_tail == sde->descq_head;
पूर्ण

अटल अंतरभूत u16 sdma_descq_मुक्तcnt(काष्ठा sdma_engine *sde)
अणु
	वापस sde->descq_cnt -
		(sde->descq_tail -
		 READ_ONCE(sde->descq_head)) - 1;
पूर्ण

अटल अंतरभूत u16 sdma_descq_inprocess(काष्ठा sdma_engine *sde)
अणु
	वापस sde->descq_cnt - sdma_descq_मुक्तcnt(sde);
पूर्ण

/*
 * Either head_lock or tail lock required to see
 * a steady state.
 */
अटल अंतरभूत पूर्णांक __sdma_running(काष्ठा sdma_engine *engine)
अणु
	वापस engine->state.current_state == sdma_state_s99_running;
पूर्ण

/**
 * sdma_running() - state suitability test
 * @engine: sdma engine
 *
 * sdma_running probes the पूर्णांकernal state to determine अगर it is suitable
 * क्रम submitting packets.
 *
 * Return:
 * 1 - ok to submit, 0 - not ok to submit
 *
 */
अटल अंतरभूत पूर्णांक sdma_running(काष्ठा sdma_engine *engine)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&engine->tail_lock, flags);
	ret = __sdma_running(engine);
	spin_unlock_irqrestore(&engine->tail_lock, flags);
	वापस ret;
पूर्ण

व्योम _sdma_txreq_ahgadd(
	काष्ठा sdma_txreq *tx,
	u8 num_ahg,
	u8 ahg_entry,
	u32 *ahg,
	u8 ahg_hlen);

/**
 * sdma_txinit_ahg() - initialize an sdma_txreq काष्ठा with AHG
 * @tx: tx request to initialize
 * @flags: flags to key last descriptor additions
 * @tlen: total packet length (pbc + headers + data)
 * @ahg_entry: ahg entry to use  (0 - 31)
 * @num_ahg: ahg descriptor क्रम first descriptor (0 - 9)
 * @ahg: array of AHG descriptors (up to 9 entries)
 * @ahg_hlen: number of bytes from ASIC entry to use
 * @cb: callback
 *
 * The allocation of the sdma_txreq and it enclosing काष्ठाure is user
 * dependent.  This routine must be called to initialize the user independent
 * fields.
 *
 * The currently supported flags are SDMA_TXREQ_F_URGENT,
 * SDMA_TXREQ_F_AHG_COPY, and SDMA_TXREQ_F_USE_AHG.
 *
 * SDMA_TXREQ_F_URGENT is used क्रम latency sensitive situations where the
 * completion is desired as soon as possible.
 *
 * SDMA_TXREQ_F_AHG_COPY causes the header in the first descriptor to be
 * copied to chip entry. SDMA_TXREQ_F_USE_AHG causes the code to add in
 * the AHG descriptors पूर्णांकo the first 1 to 3 descriptors.
 *
 * Completions of submitted requests can be gotten on selected
 * txreqs by giving a completion routine callback to sdma_txinit() or
 * sdma_txinit_ahg().  The environment in which the callback runs
 * can be from an ISR, a tasklet, or a thपढ़ो, so no sleeping
 * kernel routines can be used.   Aspects of the sdma ring may
 * be locked so care should be taken with locking.
 *
 * The callback poपूर्णांकer can be शून्य to aव्योम any callback क्रम the packet
 * being submitted. The callback will be provided this tx, a status, and a flag.
 *
 * The status will be one of SDMA_TXREQ_S_OK, SDMA_TXREQ_S_SENDERROR,
 * SDMA_TXREQ_S_ABORTED, or SDMA_TXREQ_S_SHUTDOWN.
 *
 * The flag, अगर the is the ioरुको had been used, indicates the ioरुको
 * sdma_busy count has reached zero.
 *
 * user data portion of tlen should be precise.   The sdma_txadd_* entrances
 * will pad with a descriptor references 1 - 3 bytes when the number of bytes
 * specअगरied in tlen have been supplied to the sdma_txreq.
 *
 * ahg_hlen is used to determine the number of on-chip entry bytes to
 * use as the header.   This is क्रम हालs where the stored header is
 * larger than the header to be used in a packet.  This is typical
 * क्रम verbs where an RDMA_WRITE_FIRST is larger than the packet in
 * and RDMA_WRITE_MIDDLE.
 *
 */
अटल अंतरभूत पूर्णांक sdma_txinit_ahg(
	काष्ठा sdma_txreq *tx,
	u16 flags,
	u16 tlen,
	u8 ahg_entry,
	u8 num_ahg,
	u32 *ahg,
	u8 ahg_hlen,
	व्योम (*cb)(काष्ठा sdma_txreq *, पूर्णांक))
अणु
	अगर (tlen == 0)
		वापस -ENODATA;
	अगर (tlen > MAX_SDMA_PKT_SIZE)
		वापस -EMSGSIZE;
	tx->desc_limit = ARRAY_SIZE(tx->descs);
	tx->descp = &tx->descs[0];
	INIT_LIST_HEAD(&tx->list);
	tx->num_desc = 0;
	tx->flags = flags;
	tx->complete = cb;
	tx->coalesce_buf = शून्य;
	tx->रुको = शून्य;
	tx->packet_len = tlen;
	tx->tlen = tx->packet_len;
	tx->descs[0].qw[0] = SDMA_DESC0_FIRST_DESC_FLAG;
	tx->descs[0].qw[1] = 0;
	अगर (flags & SDMA_TXREQ_F_AHG_COPY)
		tx->descs[0].qw[1] |=
			(((u64)ahg_entry & SDMA_DESC1_HEADER_INDEX_MASK)
				<< SDMA_DESC1_HEADER_INDEX_SHIFT) |
			(((u64)SDMA_AHG_COPY & SDMA_DESC1_HEADER_MODE_MASK)
				<< SDMA_DESC1_HEADER_MODE_SHIFT);
	अन्यथा अगर (flags & SDMA_TXREQ_F_USE_AHG && num_ahg)
		_sdma_txreq_ahgadd(tx, num_ahg, ahg_entry, ahg, ahg_hlen);
	वापस 0;
पूर्ण

/**
 * sdma_txinit() - initialize an sdma_txreq काष्ठा (no AHG)
 * @tx: tx request to initialize
 * @flags: flags to key last descriptor additions
 * @tlen: total packet length (pbc + headers + data)
 * @cb: callback poपूर्णांकer
 *
 * The allocation of the sdma_txreq and it enclosing काष्ठाure is user
 * dependent.  This routine must be called to initialize the user
 * independent fields.
 *
 * The currently supported flags is SDMA_TXREQ_F_URGENT.
 *
 * SDMA_TXREQ_F_URGENT is used क्रम latency sensitive situations where the
 * completion is desired as soon as possible.
 *
 * Completions of submitted requests can be gotten on selected
 * txreqs by giving a completion routine callback to sdma_txinit() or
 * sdma_txinit_ahg().  The environment in which the callback runs
 * can be from an ISR, a tasklet, or a thपढ़ो, so no sleeping
 * kernel routines can be used.   The head size of the sdma ring may
 * be locked so care should be taken with locking.
 *
 * The callback poपूर्णांकer can be शून्य to aव्योम any callback क्रम the packet
 * being submitted.
 *
 * The callback, अगर non-शून्य,  will be provided this tx and a status.  The
 * status will be one of SDMA_TXREQ_S_OK, SDMA_TXREQ_S_SENDERROR,
 * SDMA_TXREQ_S_ABORTED, or SDMA_TXREQ_S_SHUTDOWN.
 *
 */
अटल अंतरभूत पूर्णांक sdma_txinit(
	काष्ठा sdma_txreq *tx,
	u16 flags,
	u16 tlen,
	व्योम (*cb)(काष्ठा sdma_txreq *, पूर्णांक))
अणु
	वापस sdma_txinit_ahg(tx, flags, tlen, 0, 0, शून्य, 0, cb);
पूर्ण

/* helpers - करोn't use */
अटल अंतरभूत पूर्णांक sdma_mapping_type(काष्ठा sdma_desc *d)
अणु
	वापस (d->qw[1] & SDMA_DESC1_GENERATION_SMASK)
		>> SDMA_DESC1_GENERATION_SHIFT;
पूर्ण

अटल अंतरभूत माप_प्रकार sdma_mapping_len(काष्ठा sdma_desc *d)
अणु
	वापस (d->qw[0] & SDMA_DESC0_BYTE_COUNT_SMASK)
		>> SDMA_DESC0_BYTE_COUNT_SHIFT;
पूर्ण

अटल अंतरभूत dma_addr_t sdma_mapping_addr(काष्ठा sdma_desc *d)
अणु
	वापस (d->qw[0] & SDMA_DESC0_PHY_ADDR_SMASK)
		>> SDMA_DESC0_PHY_ADDR_SHIFT;
पूर्ण

अटल अंतरभूत व्योम make_tx_sdma_desc(
	काष्ठा sdma_txreq *tx,
	पूर्णांक type,
	dma_addr_t addr,
	माप_प्रकार len)
अणु
	काष्ठा sdma_desc *desc = &tx->descp[tx->num_desc];

	अगर (!tx->num_desc) अणु
		/* qw[0] zero; qw[1] first, ahg mode alपढ़ोy in from init */
		desc->qw[1] |= ((u64)type & SDMA_DESC1_GENERATION_MASK)
				<< SDMA_DESC1_GENERATION_SHIFT;
	पूर्ण अन्यथा अणु
		desc->qw[0] = 0;
		desc->qw[1] = ((u64)type & SDMA_DESC1_GENERATION_MASK)
				<< SDMA_DESC1_GENERATION_SHIFT;
	पूर्ण
	desc->qw[0] |= (((u64)addr & SDMA_DESC0_PHY_ADDR_MASK)
				<< SDMA_DESC0_PHY_ADDR_SHIFT) |
			(((u64)len & SDMA_DESC0_BYTE_COUNT_MASK)
				<< SDMA_DESC0_BYTE_COUNT_SHIFT);
पूर्ण

/* helper to extend txreq */
पूर्णांक ext_coal_sdma_tx_descs(काष्ठा hfi1_devdata *dd, काष्ठा sdma_txreq *tx,
			   पूर्णांक type, व्योम *kvaddr, काष्ठा page *page,
			   अचिन्हित दीर्घ offset, u16 len);
पूर्णांक _pad_sdma_tx_descs(काष्ठा hfi1_devdata *, काष्ठा sdma_txreq *);
व्योम __sdma_txclean(काष्ठा hfi1_devdata *, काष्ठा sdma_txreq *);

अटल अंतरभूत व्योम sdma_txclean(काष्ठा hfi1_devdata *dd, काष्ठा sdma_txreq *tx)
अणु
	अगर (tx->num_desc)
		__sdma_txclean(dd, tx);
पूर्ण

/* helpers used by खुला routines */
अटल अंतरभूत व्योम _sdma_बंद_tx(काष्ठा hfi1_devdata *dd,
				  काष्ठा sdma_txreq *tx)
अणु
	tx->descp[tx->num_desc].qw[0] |=
		SDMA_DESC0_LAST_DESC_FLAG;
	tx->descp[tx->num_desc].qw[1] |=
		dd->शेष_desc1;
	अगर (tx->flags & SDMA_TXREQ_F_URGENT)
		tx->descp[tx->num_desc].qw[1] |=
			(SDMA_DESC1_HEAD_TO_HOST_FLAG |
			 SDMA_DESC1_INT_REQ_FLAG);
पूर्ण

अटल अंतरभूत पूर्णांक _sdma_txadd_daddr(
	काष्ठा hfi1_devdata *dd,
	पूर्णांक type,
	काष्ठा sdma_txreq *tx,
	dma_addr_t addr,
	u16 len)
अणु
	पूर्णांक rval = 0;

	make_tx_sdma_desc(
		tx,
		type,
		addr, len);
	WARN_ON(len > tx->tlen);
	tx->tlen -= len;
	/* special हालs क्रम last */
	अगर (!tx->tlen) अणु
		अगर (tx->packet_len & (माप(u32) - 1)) अणु
			rval = _pad_sdma_tx_descs(dd, tx);
			अगर (rval)
				वापस rval;
		पूर्ण अन्यथा अणु
			_sdma_बंद_tx(dd, tx);
		पूर्ण
	पूर्ण
	tx->num_desc++;
	वापस rval;
पूर्ण

/**
 * sdma_txadd_page() - add a page to the sdma_txreq
 * @dd: the device to use क्रम mapping
 * @tx: tx request to which the page is added
 * @page: page to map
 * @offset: offset within the page
 * @len: length in bytes
 *
 * This is used to add a page/offset/length descriptor.
 *
 * The mapping/unmapping of the page/offset/len is स्वतःmatically handled.
 *
 * Return:
 * 0 - success, -ENOSPC - mapping fail, -ENOMEM - couldn't
 * extend/coalesce descriptor array
 */
अटल अंतरभूत पूर्णांक sdma_txadd_page(
	काष्ठा hfi1_devdata *dd,
	काष्ठा sdma_txreq *tx,
	काष्ठा page *page,
	अचिन्हित दीर्घ offset,
	u16 len)
अणु
	dma_addr_t addr;
	पूर्णांक rval;

	अगर ((unlikely(tx->num_desc == tx->desc_limit))) अणु
		rval = ext_coal_sdma_tx_descs(dd, tx, SDMA_MAP_PAGE,
					      शून्य, page, offset, len);
		अगर (rval <= 0)
			वापस rval;
	पूर्ण

	addr = dma_map_page(
		       &dd->pcidev->dev,
		       page,
		       offset,
		       len,
		       DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(&dd->pcidev->dev, addr))) अणु
		__sdma_txclean(dd, tx);
		वापस -ENOSPC;
	पूर्ण

	वापस _sdma_txadd_daddr(
			dd, SDMA_MAP_PAGE, tx, addr, len);
पूर्ण

/**
 * sdma_txadd_daddr() - add a dma address to the sdma_txreq
 * @dd: the device to use क्रम mapping
 * @tx: sdma_txreq to which the page is added
 * @addr: dma address mapped by caller
 * @len: length in bytes
 *
 * This is used to add a descriptor क्रम memory that is alपढ़ोy dma mapped.
 *
 * In this हाल, there is no unmapping as part of the progress processing क्रम
 * this memory location.
 *
 * Return:
 * 0 - success, -ENOMEM - couldn't extend descriptor array
 */

अटल अंतरभूत पूर्णांक sdma_txadd_daddr(
	काष्ठा hfi1_devdata *dd,
	काष्ठा sdma_txreq *tx,
	dma_addr_t addr,
	u16 len)
अणु
	पूर्णांक rval;

	अगर ((unlikely(tx->num_desc == tx->desc_limit))) अणु
		rval = ext_coal_sdma_tx_descs(dd, tx, SDMA_MAP_NONE,
					      शून्य, शून्य, 0, 0);
		अगर (rval <= 0)
			वापस rval;
	पूर्ण

	वापस _sdma_txadd_daddr(dd, SDMA_MAP_NONE, tx, addr, len);
पूर्ण

/**
 * sdma_txadd_kvaddr() - add a kernel भव address to sdma_txreq
 * @dd: the device to use क्रम mapping
 * @tx: sdma_txreq to which the page is added
 * @kvaddr: the kernel भव address
 * @len: length in bytes
 *
 * This is used to add a descriptor referenced by the indicated kvaddr and
 * len.
 *
 * The mapping/unmapping of the kvaddr and len is स्वतःmatically handled.
 *
 * Return:
 * 0 - success, -ENOSPC - mapping fail, -ENOMEM - couldn't extend/coalesce
 * descriptor array
 */
अटल अंतरभूत पूर्णांक sdma_txadd_kvaddr(
	काष्ठा hfi1_devdata *dd,
	काष्ठा sdma_txreq *tx,
	व्योम *kvaddr,
	u16 len)
अणु
	dma_addr_t addr;
	पूर्णांक rval;

	अगर ((unlikely(tx->num_desc == tx->desc_limit))) अणु
		rval = ext_coal_sdma_tx_descs(dd, tx, SDMA_MAP_SINGLE,
					      kvaddr, शून्य, 0, len);
		अगर (rval <= 0)
			वापस rval;
	पूर्ण

	addr = dma_map_single(
		       &dd->pcidev->dev,
		       kvaddr,
		       len,
		       DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(&dd->pcidev->dev, addr))) अणु
		__sdma_txclean(dd, tx);
		वापस -ENOSPC;
	पूर्ण

	वापस _sdma_txadd_daddr(
			dd, SDMA_MAP_SINGLE, tx, addr, len);
पूर्ण

काष्ठा ioरुको_work;

पूर्णांक sdma_send_txreq(काष्ठा sdma_engine *sde,
		    काष्ठा ioरुको_work *रुको,
		    काष्ठा sdma_txreq *tx,
		    bool pkts_sent);
पूर्णांक sdma_send_txlist(काष्ठा sdma_engine *sde,
		     काष्ठा ioरुको_work *रुको,
		     काष्ठा list_head *tx_list,
		     u16 *count_out);

पूर्णांक sdma_ahg_alloc(काष्ठा sdma_engine *sde);
व्योम sdma_ahg_मुक्त(काष्ठा sdma_engine *sde, पूर्णांक ahg_index);

/**
 * sdma_build_ahg - build ahg descriptor
 * @data
 * @dwindex
 * @startbit
 * @bits
 *
 * Build and वापस a 32 bit descriptor.
 */
अटल अंतरभूत u32 sdma_build_ahg_descriptor(
	u16 data,
	u8 dwindex,
	u8 startbit,
	u8 bits)
अणु
	वापस (u32)(1UL << SDMA_AHG_UPDATE_ENABLE_SHIFT |
		((startbit & SDMA_AHG_FIELD_START_MASK) <<
		SDMA_AHG_FIELD_START_SHIFT) |
		((bits & SDMA_AHG_FIELD_LEN_MASK) <<
		SDMA_AHG_FIELD_LEN_SHIFT) |
		((dwindex & SDMA_AHG_INDEX_MASK) <<
		SDMA_AHG_INDEX_SHIFT) |
		((data & SDMA_AHG_VALUE_MASK) <<
		SDMA_AHG_VALUE_SHIFT));
पूर्ण

/**
 * sdma_progress - use seq number of detect head progress
 * @sde: sdma_engine to check
 * @seq: base seq count
 * @tx: txreq क्रम which we need to check descriptor availability
 *
 * This is used in the appropriate spot in the sleep routine
 * to check क्रम potential ring progress.  This routine माला_लो the
 * seqcount beक्रमe queuing the ioरुको काष्ठाure क्रम progress.
 *
 * If the seqcount indicates that progress needs to be checked,
 * re-submission is detected by checking whether the descriptor
 * queue has enough descriptor क्रम the txreq.
 */
अटल अंतरभूत अचिन्हित sdma_progress(काष्ठा sdma_engine *sde, अचिन्हित seq,
				     काष्ठा sdma_txreq *tx)
अणु
	अगर (पढ़ो_seqretry(&sde->head_lock, seq)) अणु
		sde->desc_avail = sdma_descq_मुक्तcnt(sde);
		अगर (tx->num_desc > sde->desc_avail)
			वापस 0;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* क्रम use by पूर्णांकerrupt handling */
व्योम sdma_engine_error(काष्ठा sdma_engine *sde, u64 status);
व्योम sdma_engine_पूर्णांकerrupt(काष्ठा sdma_engine *sde, u64 status);

/*
 *
 * The diagram below details the relationship of the mapping काष्ठाures
 *
 * Since the mapping now allows क्रम non-unअगरorm engines per vl, the
 * number of engines क्रम a vl is either the vl_engines[vl] or
 * a computation based on num_sdma/num_vls:
 *
 * For example:
 * nactual = vl_engines ? vl_engines[vl] : num_sdma/num_vls
 *
 * n = roundup to next highest घातer of 2 using nactual
 *
 * In the हाल where there are num_sdma/num_vls करोesn't भागide
 * evenly, the extras are added from the last vl करोwnward.
 *
 * For the हाल where n > nactual, the engines are asचिन्हित
 * in a round robin fashion wrapping back to the first engine
 * क्रम a particular vl.
 *
 *               dd->sdma_map
 *                    |                                   sdma_map_elem[0]
 *                    |                                +--------------------+
 *                    v                                |       mask         |
 *               sdma_vl_map                           |--------------------|
 *      +--------------------------+                   | sde[0] -> eng 1    |
 *      |    list (RCU)            |                   |--------------------|
 *      |--------------------------|                 ->| sde[1] -> eng 2    |
 *      |    mask                  |              --/  |--------------------|
 *      |--------------------------|            -/     |        *           |
 *      |    actual_vls (max 8)    |          -/       |--------------------|
 *      |--------------------------|       --/         | sde[n-1] -> eng n  |
 *      |    vls (max 8)           |     -/            +--------------------+
 *      |--------------------------|  --/
 *      |    map[0]                |-/
 *      |--------------------------|                   +---------------------+
 *      |    map[1]                |---                |       mask          |
 *      |--------------------------|   \----           |---------------------|
 *      |           *              |        \--        | sde[0] -> eng 1+n   |
 *      |           *              |           \----   |---------------------|
 *      |           *              |                \->| sde[1] -> eng 2+n   |
 *      |--------------------------|                   |---------------------|
 *      |   map[vls - 1]           |-                  |         *           |
 *      +--------------------------+ \-                |---------------------|
 *                                     \-              | sde[m-1] -> eng m+n |
 *                                       \             +---------------------+
 *                                        \-
 *                                          \
 *                                           \-        +----------------------+
 *                                             \-      |       mask           |
 *                                               \     |----------------------|
 *                                                \-   | sde[0] -> eng 1+m+n  |
 *                                                  \- |----------------------|
 *                                                    >| sde[1] -> eng 2+m+n  |
 *                                                     |----------------------|
 *                                                     |         *            |
 *                                                     |----------------------|
 *                                                     | sde[o-1] -> eng o+m+n|
 *                                                     +----------------------+
 *
 */

/**
 * काष्ठा sdma_map_elem - mapping क्रम a vl
 * @mask - selector mask
 * @sde - array of engines क्रम this vl
 *
 * The mask is used to "mod" the selector
 * to produce index पूर्णांकo the trailing
 * array of sdes.
 */
काष्ठा sdma_map_elem अणु
	u32 mask;
	काष्ठा sdma_engine *sde[];
पूर्ण;

/**
 * काष्ठा sdma_map_el - mapping क्रम a vl
 * @engine_to_vl - map of an engine to a vl
 * @list - rcu head क्रम मुक्त callback
 * @mask - vl mask to "mod" the vl to produce an index to map array
 * @actual_vls - number of vls
 * @vls - number of vls rounded to next घातer of 2
 * @map - array of sdma_map_elem entries
 *
 * This is the parent mapping काष्ठाure.  The trailing
 * members of the काष्ठा poपूर्णांक to sdma_map_elem entries, which
 * in turn poपूर्णांक to an array of sde's क्रम that vl.
 */
काष्ठा sdma_vl_map अणु
	s8 engine_to_vl[TXE_NUM_SDMA_ENGINES];
	काष्ठा rcu_head list;
	u32 mask;
	u8 actual_vls;
	u8 vls;
	काष्ठा sdma_map_elem *map[];
पूर्ण;

पूर्णांक sdma_map_init(
	काष्ठा hfi1_devdata *dd,
	u8 port,
	u8 num_vls,
	u8 *vl_engines);

/* slow path */
व्योम _sdma_engine_progress_schedule(काष्ठा sdma_engine *sde);

/**
 * sdma_engine_progress_schedule() - schedule progress on engine
 * @sde: sdma_engine to schedule progress
 *
 * This is the fast path.
 *
 */
अटल अंतरभूत व्योम sdma_engine_progress_schedule(
	काष्ठा sdma_engine *sde)
अणु
	अगर (!sde || sdma_descq_inprocess(sde) < (sde->descq_cnt / 8))
		वापस;
	_sdma_engine_progress_schedule(sde);
पूर्ण

काष्ठा sdma_engine *sdma_select_engine_sc(
	काष्ठा hfi1_devdata *dd,
	u32 selector,
	u8 sc5);

काष्ठा sdma_engine *sdma_select_engine_vl(
	काष्ठा hfi1_devdata *dd,
	u32 selector,
	u8 vl);

काष्ठा sdma_engine *sdma_select_user_engine(काष्ठा hfi1_devdata *dd,
					    u32 selector, u8 vl);
sमाप_प्रकार sdma_get_cpu_to_sde_map(काष्ठा sdma_engine *sde, अक्षर *buf);
sमाप_प्रकार sdma_set_cpu_to_sde_map(काष्ठा sdma_engine *sde, स्थिर अक्षर *buf,
				माप_प्रकार count);
पूर्णांक sdma_engine_get_vl(काष्ठा sdma_engine *sde);
व्योम sdma_seqfile_dump_sde(काष्ठा seq_file *s, काष्ठा sdma_engine *);
व्योम sdma_seqfile_dump_cpu_list(काष्ठा seq_file *s, काष्ठा hfi1_devdata *dd,
				अचिन्हित दीर्घ cpuid);

#अगर_घोषित CONFIG_SDMA_VERBOSITY
व्योम sdma_dumpstate(काष्ठा sdma_engine *);
#पूर्ण_अगर
अटल अंतरभूत अक्षर *slashstrip(अक्षर *s)
अणु
	अक्षर *r = s;

	जबतक (*s)
		अगर (*s++ == '/')
			r = s;
	वापस r;
पूर्ण

u16 sdma_get_descq_cnt(व्योम);

बाह्य uपूर्णांक mod_num_sdma;

व्योम sdma_update_lmc(काष्ठा hfi1_devdata *dd, u64 mask, u32 lid);

#पूर्ण_अगर
