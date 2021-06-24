<शैली गुरु>
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

#समावेश <linux/spinlock.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>

#समावेश "hfi.h"
#समावेश "common.h"
#समावेश "qp.h"
#समावेश "sdma.h"
#समावेश "iowait.h"
#समावेश "trace.h"

/* must be a घातer of 2 >= 64 <= 32768 */
#घोषणा SDMA_DESCQ_CNT 2048
#घोषणा SDMA_DESC_INTR 64
#घोषणा INVALID_TAIL 0xffff
#घोषणा SDMA_PAD max_t(माप_प्रकार, MAX_16B_PADDING, माप(u32))

अटल uपूर्णांक sdma_descq_cnt = SDMA_DESCQ_CNT;
module_param(sdma_descq_cnt, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(sdma_descq_cnt, "Number of SDMA descq entries");

अटल uपूर्णांक sdma_idle_cnt = 250;
module_param(sdma_idle_cnt, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(sdma_idle_cnt, "sdma interrupt idle delay (ns,default 250)");

uपूर्णांक mod_num_sdma;
module_param_named(num_sdma, mod_num_sdma, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num_sdma, "Set max number SDMA engines to use");

अटल uपूर्णांक sdma_desct_पूर्णांकr = SDMA_DESC_INTR;
module_param_named(desct_पूर्णांकr, sdma_desct_पूर्णांकr, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(desct_पूर्णांकr, "Number of SDMA descriptor before interrupt");

#घोषणा SDMA_WAIT_BATCH_SIZE 20
/* max रुको समय क्रम a SDMA engine to indicate it has halted */
#घोषणा SDMA_ERR_HALT_TIMEOUT 10 /* ms */
/* all SDMA engine errors that cause a halt */

#घोषणा SD(name) SEND_DMA_##name
#घोषणा ALL_SDMA_ENG_HALT_ERRS \
	(SD(ENG_ERR_STATUS_SDMA_WRONG_DW_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_GEN_MISMATCH_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_TOO_LONG_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_TAIL_OUT_OF_BOUNDS_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_FIRST_DESC_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_MEM_READ_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HALT_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_LENGTH_MISMATCH_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_PACKET_DESC_OVERFLOW_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HEADER_SELECT_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HEADER_ADDRESS_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HEADER_LENGTH_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_TIMEOUT_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_DESC_TABLE_UNC_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_ASSEMBLY_UNC_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_PACKET_TRACKING_UNC_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HEADER_STORAGE_UNC_ERR_SMASK) \
	| SD(ENG_ERR_STATUS_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_SMASK))

/* sdma_sendctrl operations */
#घोषणा SDMA_SENDCTRL_OP_ENABLE    BIT(0)
#घोषणा SDMA_SENDCTRL_OP_INTENABLE BIT(1)
#घोषणा SDMA_SENDCTRL_OP_HALT      BIT(2)
#घोषणा SDMA_SENDCTRL_OP_CLEANUP   BIT(3)

/* handle दीर्घ defines */
#घोषणा SDMA_EGRESS_PACKET_OCCUPANCY_SMASK \
SEND_EGRESS_SEND_DMA_STATUS_SDMA_EGRESS_PACKET_OCCUPANCY_SMASK
#घोषणा SDMA_EGRESS_PACKET_OCCUPANCY_SHIFT \
SEND_EGRESS_SEND_DMA_STATUS_SDMA_EGRESS_PACKET_OCCUPANCY_SHIFT

अटल स्थिर अक्षर * स्थिर sdma_state_names[] = अणु
	[sdma_state_s00_hw_करोwn]                = "s00_HwDown",
	[sdma_state_s10_hw_start_up_halt_रुको]  = "s10_HwStartUpHaltWait",
	[sdma_state_s15_hw_start_up_clean_रुको] = "s15_HwStartUpCleanWait",
	[sdma_state_s20_idle]                   = "s20_Idle",
	[sdma_state_s30_sw_clean_up_रुको]       = "s30_SwCleanUpWait",
	[sdma_state_s40_hw_clean_up_रुको]       = "s40_HwCleanUpWait",
	[sdma_state_s50_hw_halt_रुको]           = "s50_HwHaltWait",
	[sdma_state_s60_idle_halt_रुको]         = "s60_IdleHaltWait",
	[sdma_state_s80_hw_मुक्तze]		= "s80_HwFreeze",
	[sdma_state_s82_मुक्तze_sw_clean]	= "s82_FreezeSwClean",
	[sdma_state_s99_running]                = "s99_Running",
पूर्ण;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
अटल स्थिर अक्षर * स्थिर sdma_event_names[] = अणु
	[sdma_event_e00_go_hw_करोwn]   = "e00_GoHwDown",
	[sdma_event_e10_go_hw_start]  = "e10_GoHwStart",
	[sdma_event_e15_hw_halt_करोne] = "e15_HwHaltDone",
	[sdma_event_e25_hw_clean_up_करोne] = "e25_HwCleanUpDone",
	[sdma_event_e30_go_running]   = "e30_GoRunning",
	[sdma_event_e40_sw_cleaned]   = "e40_SwCleaned",
	[sdma_event_e50_hw_cleaned]   = "e50_HwCleaned",
	[sdma_event_e60_hw_halted]    = "e60_HwHalted",
	[sdma_event_e70_go_idle]      = "e70_GoIdle",
	[sdma_event_e80_hw_मुक्तze]    = "e80_HwFreeze",
	[sdma_event_e81_hw_frozen]    = "e81_HwFrozen",
	[sdma_event_e82_hw_unमुक्तze]  = "e82_HwUnfreeze",
	[sdma_event_e85_link_करोwn]    = "e85_LinkDown",
	[sdma_event_e90_sw_halted]    = "e90_SwHalted",
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा sdma_set_state_action sdma_action_table[] = अणु
	[sdma_state_s00_hw_करोwn] = अणु
		.go_s99_running_tofalse = 1,
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s10_hw_start_up_halt_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 1,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s15_hw_start_up_clean_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
		.op_cleanup = 1,
	पूर्ण,
	[sdma_state_s20_idle] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s30_sw_clean_up_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s40_hw_clean_up_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 1,
	पूर्ण,
	[sdma_state_s50_hw_halt_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s60_idle_halt_रुको] = अणु
		.go_s99_running_tofalse = 1,
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 1,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s80_hw_मुक्तze] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s82_मुक्तze_sw_clean] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_cleanup = 0,
	पूर्ण,
	[sdma_state_s99_running] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
		.op_cleanup = 0,
		.go_s99_running_totrue = 1,
	पूर्ण,
पूर्ण;

#घोषणा SDMA_TAIL_UPDATE_THRESH 0x1F

/* declare all अटलs here rather than keep sorting */
अटल व्योम sdma_complete(काष्ठा kref *);
अटल व्योम sdma_finalput(काष्ठा sdma_state *);
अटल व्योम sdma_get(काष्ठा sdma_state *);
अटल व्योम sdma_hw_clean_up_task(काष्ठा tasklet_काष्ठा *);
अटल व्योम sdma_put(काष्ठा sdma_state *);
अटल व्योम sdma_set_state(काष्ठा sdma_engine *, क्रमागत sdma_states);
अटल व्योम sdma_start_hw_clean_up(काष्ठा sdma_engine *);
अटल व्योम sdma_sw_clean_up_task(काष्ठा tasklet_काष्ठा *);
अटल व्योम sdma_sendctrl(काष्ठा sdma_engine *, अचिन्हित);
अटल व्योम init_sdma_regs(काष्ठा sdma_engine *, u32, uपूर्णांक);
अटल व्योम sdma_process_event(
	काष्ठा sdma_engine *sde,
	क्रमागत sdma_events event);
अटल व्योम __sdma_process_event(
	काष्ठा sdma_engine *sde,
	क्रमागत sdma_events event);
अटल व्योम dump_sdma_state(काष्ठा sdma_engine *sde);
अटल व्योम sdma_make_progress(काष्ठा sdma_engine *sde, u64 status);
अटल व्योम sdma_desc_avail(काष्ठा sdma_engine *sde, uपूर्णांक avail);
अटल व्योम sdma_flush_descq(काष्ठा sdma_engine *sde);

/**
 * sdma_state_name() - वापस state string from क्रमागत
 * @state: state
 */
अटल स्थिर अक्षर *sdma_state_name(क्रमागत sdma_states state)
अणु
	वापस sdma_state_names[state];
पूर्ण

अटल व्योम sdma_get(काष्ठा sdma_state *ss)
अणु
	kref_get(&ss->kref);
पूर्ण

अटल व्योम sdma_complete(काष्ठा kref *kref)
अणु
	काष्ठा sdma_state *ss =
		container_of(kref, काष्ठा sdma_state, kref);

	complete(&ss->comp);
पूर्ण

अटल व्योम sdma_put(काष्ठा sdma_state *ss)
अणु
	kref_put(&ss->kref, sdma_complete);
पूर्ण

अटल व्योम sdma_finalput(काष्ठा sdma_state *ss)
अणु
	sdma_put(ss);
	रुको_क्रम_completion(&ss->comp);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_sde_csr(
	काष्ठा sdma_engine *sde,
	u32 offset0,
	u64 value)
अणु
	ग_लिखो_kctxt_csr(sde->dd, sde->this_idx, offset0, value);
पूर्ण

अटल अंतरभूत u64 पढ़ो_sde_csr(
	काष्ठा sdma_engine *sde,
	u32 offset0)
अणु
	वापस पढ़ो_kctxt_csr(sde->dd, sde->this_idx, offset0);
पूर्ण

/*
 * sdma_रुको_क्रम_packet_egress() - रुको क्रम the VL FIFO occupancy क्रम
 * sdma engine 'sde' to drop to 0.
 */
अटल व्योम sdma_रुको_क्रम_packet_egress(काष्ठा sdma_engine *sde,
					पूर्णांक छोड़ो)
अणु
	u64 off = 8 * sde->this_idx;
	काष्ठा hfi1_devdata *dd = sde->dd;
	पूर्णांक lcnt = 0;
	u64 reg_prev;
	u64 reg = 0;

	जबतक (1) अणु
		reg_prev = reg;
		reg = पढ़ो_csr(dd, off + SEND_EGRESS_SEND_DMA_STATUS);

		reg &= SDMA_EGRESS_PACKET_OCCUPANCY_SMASK;
		reg >>= SDMA_EGRESS_PACKET_OCCUPANCY_SHIFT;
		अगर (reg == 0)
			अवरोध;
		/* counter is reest अगर accupancy count changes */
		अगर (reg != reg_prev)
			lcnt = 0;
		अगर (lcnt++ > 500) अणु
			/* समयd out - bounce the link */
			dd_dev_err(dd, "%s: engine %u timeout waiting for packets to egress, remaining count %u, bouncing link\n",
				   __func__, sde->this_idx, (u32)reg);
			queue_work(dd->pport->link_wq,
				   &dd->pport->link_bounce_work);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

/*
 * sdma_रुको() - रुको क्रम packet egress to complete क्रम all SDMA engines,
 * and छोड़ो क्रम credit वापस.
 */
व्योम sdma_रुको(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_sdma; i++) अणु
		काष्ठा sdma_engine *sde = &dd->per_sdma[i];

		sdma_रुको_क्रम_packet_egress(sde, 0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sdma_set_desc_cnt(काष्ठा sdma_engine *sde, अचिन्हित cnt)
अणु
	u64 reg;

	अगर (!(sde->dd->flags & HFI1_HAS_SDMA_TIMEOUT))
		वापस;
	reg = cnt;
	reg &= SD(DESC_CNT_CNT_MASK);
	reg <<= SD(DESC_CNT_CNT_SHIFT);
	ग_लिखो_sde_csr(sde, SD(DESC_CNT), reg);
पूर्ण

अटल अंतरभूत व्योम complete_tx(काष्ठा sdma_engine *sde,
			       काष्ठा sdma_txreq *tx,
			       पूर्णांक res)
अणु
	/* protect against complete modअगरying */
	काष्ठा ioरुको *रुको = tx->रुको;
	callback_t complete = tx->complete;

#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	trace_hfi1_sdma_out_sn(sde, tx->sn);
	अगर (WARN_ON_ONCE(sde->head_sn != tx->sn))
		dd_dev_err(sde->dd, "expected %llu got %llu\n",
			   sde->head_sn, tx->sn);
	sde->head_sn++;
#पूर्ण_अगर
	__sdma_txclean(sde->dd, tx);
	अगर (complete)
		(*complete)(tx, res);
	अगर (ioरुको_sdma_dec(रुको))
		ioरुको_drain_wakeup(रुको);
पूर्ण

/*
 * Complete all the sdma requests with a SDMA_TXREQ_S_ABORTED status
 *
 * Depending on timing there can be txreqs in two places:
 * - in the descq ring
 * - in the flush list
 *
 * To aव्योम ordering issues the descq ring needs to be flushed
 * first followed by the flush list.
 *
 * This routine is called from two places
 * - From a work queue item
 * - Directly from the state machine just beक्रमe setting the
 *   state to running
 *
 * Must be called with head_lock held
 *
 */
अटल व्योम sdma_flush(काष्ठा sdma_engine *sde)
अणु
	काष्ठा sdma_txreq *txp, *txp_next;
	LIST_HEAD(flushlist);
	अचिन्हित दीर्घ flags;
	uपूर्णांक seq;

	/* flush from head to tail */
	sdma_flush_descq(sde);
	spin_lock_irqsave(&sde->flushlist_lock, flags);
	/* copy flush list */
	list_splice_init(&sde->flushlist, &flushlist);
	spin_unlock_irqrestore(&sde->flushlist_lock, flags);
	/* flush from flush list */
	list_क्रम_each_entry_safe(txp, txp_next, &flushlist, list)
		complete_tx(sde, txp, SDMA_TXREQ_S_ABORTED);
	/* wakeup QPs orphaned on the dmaरुको list */
	करो अणु
		काष्ठा ioरुको *w, *nw;

		seq = पढ़ो_seqbegin(&sde->रुकोlock);
		अगर (!list_empty(&sde->dmaरुको)) अणु
			ग_लिखो_seqlock(&sde->रुकोlock);
			list_क्रम_each_entry_safe(w, nw, &sde->dmaरुको, list) अणु
				अगर (w->wakeup) अणु
					w->wakeup(w, SDMA_AVAIL_REASON);
					list_del_init(&w->list);
				पूर्ण
			पूर्ण
			ग_लिखो_sequnlock(&sde->रुकोlock);
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqretry(&sde->रुकोlock, seq));
पूर्ण

/*
 * Fields a work request क्रम flushing the descq ring
 * and the flush list
 *
 * If the engine has been brought to running during
 * the scheduling delay, the flush is ignored, assuming
 * that the process of bringing the engine to running
 * would have करोne this flush prior to going to running.
 *
 */
अटल व्योम sdma_field_flush(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sdma_engine *sde =
		container_of(work, काष्ठा sdma_engine, flush_worker);

	ग_लिखो_seqlock_irqsave(&sde->head_lock, flags);
	अगर (!__sdma_running(sde))
		sdma_flush(sde);
	ग_लिखो_sequnlock_irqrestore(&sde->head_lock, flags);
पूर्ण

अटल व्योम sdma_err_halt_रुको(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdma_engine *sde = container_of(work, काष्ठा sdma_engine,
						err_halt_worker);
	u64 statuscsr;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(SDMA_ERR_HALT_TIMEOUT);
	जबतक (1) अणु
		statuscsr = पढ़ो_sde_csr(sde, SD(STATUS));
		statuscsr &= SD(STATUS_ENG_HALTED_SMASK);
		अगर (statuscsr)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dd_dev_err(sde->dd,
				   "SDMA engine %d - timeout waiting for engine to halt\n",
				   sde->this_idx);
			/*
			 * Continue anyway.  This could happen अगर there was
			 * an uncorrectable error in the wrong spot.
			 */
			अवरोध;
		पूर्ण
		usleep_range(80, 120);
	पूर्ण

	sdma_process_event(sde, sdma_event_e15_hw_halt_करोne);
पूर्ण

अटल व्योम sdma_err_progress_check_schedule(काष्ठा sdma_engine *sde)
अणु
	अगर (!is_bx(sde->dd) && HFI1_CAP_IS_KSET(SDMA_AHG)) अणु
		अचिन्हित index;
		काष्ठा hfi1_devdata *dd = sde->dd;

		क्रम (index = 0; index < dd->num_sdma; index++) अणु
			काष्ठा sdma_engine *curr_sdma = &dd->per_sdma[index];

			अगर (curr_sdma != sde)
				curr_sdma->progress_check_head =
							curr_sdma->descq_head;
		पूर्ण
		dd_dev_err(sde->dd,
			   "SDMA engine %d - check scheduled\n",
				sde->this_idx);
		mod_समयr(&sde->err_progress_check_समयr, jअगरfies + 10);
	पूर्ण
पूर्ण

अटल व्योम sdma_err_progress_check(काष्ठा समयr_list *t)
अणु
	अचिन्हित index;
	काष्ठा sdma_engine *sde = from_समयr(sde, t, err_progress_check_समयr);

	dd_dev_err(sde->dd, "SDE progress check event\n");
	क्रम (index = 0; index < sde->dd->num_sdma; index++) अणु
		काष्ठा sdma_engine *curr_sde = &sde->dd->per_sdma[index];
		अचिन्हित दीर्घ flags;

		/* check progress on each engine except the current one */
		अगर (curr_sde == sde)
			जारी;
		/*
		 * We must lock पूर्णांकerrupts when acquiring sde->lock,
		 * to aव्योम a deadlock अगर पूर्णांकerrupt triggers and spins on
		 * the same lock on same CPU
		 */
		spin_lock_irqsave(&curr_sde->tail_lock, flags);
		ग_लिखो_seqlock(&curr_sde->head_lock);

		/* skip non-running queues */
		अगर (curr_sde->state.current_state != sdma_state_s99_running) अणु
			ग_लिखो_sequnlock(&curr_sde->head_lock);
			spin_unlock_irqrestore(&curr_sde->tail_lock, flags);
			जारी;
		पूर्ण

		अगर ((curr_sde->descq_head != curr_sde->descq_tail) &&
		    (curr_sde->descq_head ==
				curr_sde->progress_check_head))
			__sdma_process_event(curr_sde,
					     sdma_event_e90_sw_halted);
		ग_लिखो_sequnlock(&curr_sde->head_lock);
		spin_unlock_irqrestore(&curr_sde->tail_lock, flags);
	पूर्ण
	schedule_work(&sde->err_halt_worker);
पूर्ण

अटल व्योम sdma_hw_clean_up_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sdma_engine *sde = from_tasklet(sde, t,
					       sdma_hw_clean_up_task);
	u64 statuscsr;

	जबतक (1) अणु
#अगर_घोषित CONFIG_SDMA_VERBOSITY
		dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
			   sde->this_idx, slashstrip(__खाता__), __LINE__,
			__func__);
#पूर्ण_अगर
		statuscsr = पढ़ो_sde_csr(sde, SD(STATUS));
		statuscsr &= SD(STATUS_ENG_CLEANED_UP_SMASK);
		अगर (statuscsr)
			अवरोध;
		udelay(10);
	पूर्ण

	sdma_process_event(sde, sdma_event_e25_hw_clean_up_करोne);
पूर्ण

अटल अंतरभूत काष्ठा sdma_txreq *get_txhead(काष्ठा sdma_engine *sde)
अणु
	वापस sde->tx_ring[sde->tx_head & sde->sdma_mask];
पूर्ण

/*
 * flush ring क्रम recovery
 */
अटल व्योम sdma_flush_descq(काष्ठा sdma_engine *sde)
अणु
	u16 head, tail;
	पूर्णांक progress = 0;
	काष्ठा sdma_txreq *txp = get_txhead(sde);

	/* The reason क्रम some of the complनिकासy of this code is that
	 * not all descriptors have corresponding txps.  So, we have to
	 * be able to skip over descs until we wander पूर्णांकo the range of
	 * the next txp on the list.
	 */
	head = sde->descq_head & sde->sdma_mask;
	tail = sde->descq_tail & sde->sdma_mask;
	जबतक (head != tail) अणु
		/* advance head, wrap अगर needed */
		head = ++sde->descq_head & sde->sdma_mask;
		/* अगर now past this txp's descs, करो the callback */
		अगर (txp && txp->next_descq_idx == head) अणु
			/* हटाओ from list */
			sde->tx_ring[sde->tx_head++ & sde->sdma_mask] = शून्य;
			complete_tx(sde, txp, SDMA_TXREQ_S_ABORTED);
			trace_hfi1_sdma_progress(sde, head, tail, txp);
			txp = get_txhead(sde);
		पूर्ण
		progress++;
	पूर्ण
	अगर (progress)
		sdma_desc_avail(sde, sdma_descq_मुक्तcnt(sde));
पूर्ण

अटल व्योम sdma_sw_clean_up_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sdma_engine *sde = from_tasklet(sde, t, sdma_sw_clean_up_task);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sde->tail_lock, flags);
	ग_लिखो_seqlock(&sde->head_lock);

	/*
	 * At this poपूर्णांक, the following should always be true:
	 * - We are halted, so no more descriptors are getting retired.
	 * - We are not running, so no one is submitting new work.
	 * - Only we can send the e40_sw_cleaned, so we can't start
	 *   running again until we say so.  So, the active list and
	 *   descq are ours to play with.
	 */

	/*
	 * In the error clean up sequence, software clean must be called
	 * beक्रमe the hardware clean so we can use the hardware head in
	 * the progress routine.  A hardware clean or SPC unमुक्तze will
	 * reset the hardware head.
	 *
	 * Process all retired requests. The progress routine will use the
	 * latest physical hardware head - we are not running so speed करोes
	 * not matter.
	 */
	sdma_make_progress(sde, 0);

	sdma_flush(sde);

	/*
	 * Reset our notion of head and tail.
	 * Note that the HW रेजिस्टरs have been reset via an earlier
	 * clean up.
	 */
	sde->descq_tail = 0;
	sde->descq_head = 0;
	sde->desc_avail = sdma_descq_मुक्तcnt(sde);
	*sde->head_dma = 0;

	__sdma_process_event(sde, sdma_event_e40_sw_cleaned);

	ग_लिखो_sequnlock(&sde->head_lock);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
पूर्ण

अटल व्योम sdma_sw_tear_करोwn(काष्ठा sdma_engine *sde)
अणु
	काष्ठा sdma_state *ss = &sde->state;

	/* Releasing this reference means the state machine has stopped. */
	sdma_put(ss);

	/* stop रुकोing क्रम all unमुक्तze events to complete */
	atomic_set(&sde->dd->sdma_unमुक्तze_count, -1);
	wake_up_पूर्णांकerruptible(&sde->dd->sdma_unमुक्तze_wq);
पूर्ण

अटल व्योम sdma_start_hw_clean_up(काष्ठा sdma_engine *sde)
अणु
	tasklet_hi_schedule(&sde->sdma_hw_clean_up_task);
पूर्ण

अटल व्योम sdma_set_state(काष्ठा sdma_engine *sde,
			   क्रमागत sdma_states next_state)
अणु
	काष्ठा sdma_state *ss = &sde->state;
	स्थिर काष्ठा sdma_set_state_action *action = sdma_action_table;
	अचिन्हित op = 0;

	trace_hfi1_sdma_state(
		sde,
		sdma_state_names[ss->current_state],
		sdma_state_names[next_state]);

	/* debugging bookkeeping */
	ss->previous_state = ss->current_state;
	ss->previous_op = ss->current_op;
	ss->current_state = next_state;

	अगर (ss->previous_state != sdma_state_s99_running &&
	    next_state == sdma_state_s99_running)
		sdma_flush(sde);

	अगर (action[next_state].op_enable)
		op |= SDMA_SENDCTRL_OP_ENABLE;

	अगर (action[next_state].op_पूर्णांकenable)
		op |= SDMA_SENDCTRL_OP_INTENABLE;

	अगर (action[next_state].op_halt)
		op |= SDMA_SENDCTRL_OP_HALT;

	अगर (action[next_state].op_cleanup)
		op |= SDMA_SENDCTRL_OP_CLEANUP;

	अगर (action[next_state].go_s99_running_tofalse)
		ss->go_s99_running = 0;

	अगर (action[next_state].go_s99_running_totrue)
		ss->go_s99_running = 1;

	ss->current_op = op;
	sdma_sendctrl(sde, ss->current_op);
पूर्ण

/**
 * sdma_get_descq_cnt() - called when device probed
 *
 * Return a validated descq count.
 *
 * This is currently only used in the verbs initialization to build the tx
 * list.
 *
 * This will probably be deleted in favor of a more scalable approach to
 * alloc tx's.
 *
 */
u16 sdma_get_descq_cnt(व्योम)
अणु
	u16 count = sdma_descq_cnt;

	अगर (!count)
		वापस SDMA_DESCQ_CNT;
	/* count must be a घातer of 2 greater than 64 and less than
	 * 32768.   Otherwise वापस शेष.
	 */
	अगर (!is_घातer_of_2(count))
		वापस SDMA_DESCQ_CNT;
	अगर (count < 64 || count > 32768)
		वापस SDMA_DESCQ_CNT;
	वापस count;
पूर्ण

/**
 * sdma_engine_get_vl() - वापस vl क्रम a given sdma engine
 * @sde: sdma engine
 *
 * This function वापसs the vl mapped to a given engine, or an error अगर
 * the mapping can't be found. The mapping fields are रक्षित by RCU.
 */
पूर्णांक sdma_engine_get_vl(काष्ठा sdma_engine *sde)
अणु
	काष्ठा hfi1_devdata *dd = sde->dd;
	काष्ठा sdma_vl_map *m;
	u8 vl;

	अगर (sde->this_idx >= TXE_NUM_SDMA_ENGINES)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	m = rcu_dereference(dd->sdma_map);
	अगर (unlikely(!m)) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	vl = m->engine_to_vl[sde->this_idx];
	rcu_पढ़ो_unlock();

	वापस vl;
पूर्ण

/**
 * sdma_select_engine_vl() - select sdma engine
 * @dd: devdata
 * @selector: a spपढ़ोing factor
 * @vl: this vl
 *
 *
 * This function वापसs an engine based on the selector and a vl.  The
 * mapping fields are रक्षित by RCU.
 */
काष्ठा sdma_engine *sdma_select_engine_vl(
	काष्ठा hfi1_devdata *dd,
	u32 selector,
	u8 vl)
अणु
	काष्ठा sdma_vl_map *m;
	काष्ठा sdma_map_elem *e;
	काष्ठा sdma_engine *rval;

	/* NOTE This should only happen अगर SC->VL changed after the initial
	 *      checks on the QP/AH
	 *      Default will वापस engine 0 below
	 */
	अगर (vl >= num_vls) अणु
		rval = शून्य;
		जाओ करोne;
	पूर्ण

	rcu_पढ़ो_lock();
	m = rcu_dereference(dd->sdma_map);
	अगर (unlikely(!m)) अणु
		rcu_पढ़ो_unlock();
		वापस &dd->per_sdma[0];
	पूर्ण
	e = m->map[vl & m->mask];
	rval = e->sde[selector & e->mask];
	rcu_पढ़ो_unlock();

करोne:
	rval =  !rval ? &dd->per_sdma[0] : rval;
	trace_hfi1_sdma_engine_select(dd, selector, vl, rval->this_idx);
	वापस rval;
पूर्ण

/**
 * sdma_select_engine_sc() - select sdma engine
 * @dd: devdata
 * @selector: a spपढ़ोing factor
 * @sc5: the 5 bit sc
 *
 *
 * This function वापसs an engine based on the selector and an sc.
 */
काष्ठा sdma_engine *sdma_select_engine_sc(
	काष्ठा hfi1_devdata *dd,
	u32 selector,
	u8 sc5)
अणु
	u8 vl = sc_to_vlt(dd, sc5);

	वापस sdma_select_engine_vl(dd, selector, vl);
पूर्ण

काष्ठा sdma_rht_map_elem अणु
	u32 mask;
	u8 ctr;
	काष्ठा sdma_engine *sde[];
पूर्ण;

काष्ठा sdma_rht_node अणु
	अचिन्हित दीर्घ cpu_id;
	काष्ठा sdma_rht_map_elem *map[HFI1_MAX_VLS_SUPPORTED];
	काष्ठा rhash_head node;
पूर्ण;

#घोषणा NR_CPUS_HINT 192

अटल स्थिर काष्ठा rhashtable_params sdma_rht_params = अणु
	.nelem_hपूर्णांक = NR_CPUS_HINT,
	.head_offset = दुरत्व(काष्ठा sdma_rht_node, node),
	.key_offset = दुरत्व(काष्ठा sdma_rht_node, cpu_id),
	.key_len = माप_field(काष्ठा sdma_rht_node, cpu_id),
	.max_size = NR_CPUS,
	.min_size = 8,
	.स्वतःmatic_shrinking = true,
पूर्ण;

/*
 * sdma_select_user_engine() - select sdma engine based on user setup
 * @dd: devdata
 * @selector: a spपढ़ोing factor
 * @vl: this vl
 *
 * This function वापसs an sdma engine क्रम a user sdma request.
 * User defined sdma engine affinity setting is honored when applicable,
 * otherwise प्रणाली शेष sdma engine mapping is used. To ensure correct
 * ordering, the mapping from <selector, vl> to sde must reमुख्य unchanged.
 */
काष्ठा sdma_engine *sdma_select_user_engine(काष्ठा hfi1_devdata *dd,
					    u32 selector, u8 vl)
अणु
	काष्ठा sdma_rht_node *rht_node;
	काष्ठा sdma_engine *sde = शून्य;
	अचिन्हित दीर्घ cpu_id;

	/*
	 * To ensure that always the same sdma engine(s) will be
	 * selected make sure the process is pinned to this CPU only.
	 */
	अगर (current->nr_cpus_allowed != 1)
		जाओ out;

	cpu_id = smp_processor_id();
	rcu_पढ़ो_lock();
	rht_node = rhashtable_lookup(dd->sdma_rht, &cpu_id,
				     sdma_rht_params);

	अगर (rht_node && rht_node->map[vl]) अणु
		काष्ठा sdma_rht_map_elem *map = rht_node->map[vl];

		sde = map->sde[selector & map->mask];
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (sde)
		वापस sde;

out:
	वापस sdma_select_engine_vl(dd, selector, vl);
पूर्ण

अटल व्योम sdma_populate_sde_map(काष्ठा sdma_rht_map_elem *map)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < roundup_घात_of_two(map->ctr ? : 1) - map->ctr; i++)
		map->sde[map->ctr + i] = map->sde[i];
पूर्ण

अटल व्योम sdma_cleanup_sde_map(काष्ठा sdma_rht_map_elem *map,
				 काष्ठा sdma_engine *sde)
अणु
	अचिन्हित पूर्णांक i, घात;

	/* only need to check the first ctr entries क्रम a match */
	क्रम (i = 0; i < map->ctr; i++) अणु
		अगर (map->sde[i] == sde) अणु
			स_हटाओ(&map->sde[i], &map->sde[i + 1],
				(map->ctr - i - 1) * माप(map->sde[0]));
			map->ctr--;
			घात = roundup_घात_of_two(map->ctr ? : 1);
			map->mask = घात - 1;
			sdma_populate_sde_map(map);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Prevents concurrent पढ़ोs and ग_लिखोs of the sdma engine cpu_mask
 */
अटल DEFINE_MUTEX(process_to_sde_mutex);

sमाप_प्रकार sdma_set_cpu_to_sde_map(काष्ठा sdma_engine *sde, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा hfi1_devdata *dd = sde->dd;
	cpumask_var_t mask, new_mask;
	अचिन्हित दीर्घ cpu;
	पूर्णांक ret, vl, sz;
	काष्ठा sdma_rht_node *rht_node;

	vl = sdma_engine_get_vl(sde);
	अगर (unlikely(vl < 0 || vl >= ARRAY_SIZE(rht_node->map)))
		वापस -EINVAL;

	ret = zalloc_cpumask_var(&mask, GFP_KERNEL);
	अगर (!ret)
		वापस -ENOMEM;

	ret = zalloc_cpumask_var(&new_mask, GFP_KERNEL);
	अगर (!ret) अणु
		मुक्त_cpumask_var(mask);
		वापस -ENOMEM;
	पूर्ण
	ret = cpulist_parse(buf, mask);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (!cpumask_subset(mask, cpu_online_mask)) अणु
		dd_dev_warn(sde->dd, "Invalid CPU mask\n");
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	sz = माप(काष्ठा sdma_rht_map_elem) +
			(TXE_NUM_SDMA_ENGINES * माप(काष्ठा sdma_engine *));

	mutex_lock(&process_to_sde_mutex);

	क्रम_each_cpu(cpu, mask) अणु
		/* Check अगर we have this alपढ़ोy mapped */
		अगर (cpumask_test_cpu(cpu, &sde->cpu_mask)) अणु
			cpumask_set_cpu(cpu, new_mask);
			जारी;
		पूर्ण

		rht_node = rhashtable_lookup_fast(dd->sdma_rht, &cpu,
						  sdma_rht_params);
		अगर (!rht_node) अणु
			rht_node = kzalloc(माप(*rht_node), GFP_KERNEL);
			अगर (!rht_node) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			rht_node->map[vl] = kzalloc(sz, GFP_KERNEL);
			अगर (!rht_node->map[vl]) अणु
				kमुक्त(rht_node);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			rht_node->cpu_id = cpu;
			rht_node->map[vl]->mask = 0;
			rht_node->map[vl]->ctr = 1;
			rht_node->map[vl]->sde[0] = sde;

			ret = rhashtable_insert_fast(dd->sdma_rht,
						     &rht_node->node,
						     sdma_rht_params);
			अगर (ret) अणु
				kमुक्त(rht_node->map[vl]);
				kमुक्त(rht_node);
				dd_dev_err(sde->dd, "Failed to set process to sde affinity for cpu %lu\n",
					   cpu);
				जाओ out;
			पूर्ण

		पूर्ण अन्यथा अणु
			पूर्णांक ctr, घात;

			/* Add new user mappings */
			अगर (!rht_node->map[vl])
				rht_node->map[vl] = kzalloc(sz, GFP_KERNEL);

			अगर (!rht_node->map[vl]) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			rht_node->map[vl]->ctr++;
			ctr = rht_node->map[vl]->ctr;
			rht_node->map[vl]->sde[ctr - 1] = sde;
			घात = roundup_घात_of_two(ctr);
			rht_node->map[vl]->mask = घात - 1;

			/* Populate the sde map table */
			sdma_populate_sde_map(rht_node->map[vl]);
		पूर्ण
		cpumask_set_cpu(cpu, new_mask);
	पूर्ण

	/* Clean up old mappings */
	क्रम_each_cpu(cpu, cpu_online_mask) अणु
		काष्ठा sdma_rht_node *rht_node;

		/* Don't cleanup sdes that are set in the new mask */
		अगर (cpumask_test_cpu(cpu, mask))
			जारी;

		rht_node = rhashtable_lookup_fast(dd->sdma_rht, &cpu,
						  sdma_rht_params);
		अगर (rht_node) अणु
			bool empty = true;
			पूर्णांक i;

			/* Remove mappings क्रम old sde */
			क्रम (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++)
				अगर (rht_node->map[i])
					sdma_cleanup_sde_map(rht_node->map[i],
							     sde);

			/* Free empty hash table entries */
			क्रम (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++) अणु
				अगर (!rht_node->map[i])
					जारी;

				अगर (rht_node->map[i]->ctr) अणु
					empty = false;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (empty) अणु
				ret = rhashtable_हटाओ_fast(dd->sdma_rht,
							     &rht_node->node,
							     sdma_rht_params);
				WARN_ON(ret);

				क्रम (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++)
					kमुक्त(rht_node->map[i]);

				kमुक्त(rht_node);
			पूर्ण
		पूर्ण
	पूर्ण

	cpumask_copy(&sde->cpu_mask, new_mask);
out:
	mutex_unlock(&process_to_sde_mutex);
out_मुक्त:
	मुक्त_cpumask_var(mask);
	मुक्त_cpumask_var(new_mask);
	वापस ret ? : strnlen(buf, PAGE_SIZE);
पूर्ण

sमाप_प्रकार sdma_get_cpu_to_sde_map(काष्ठा sdma_engine *sde, अक्षर *buf)
अणु
	mutex_lock(&process_to_sde_mutex);
	अगर (cpumask_empty(&sde->cpu_mask))
		snम_लिखो(buf, PAGE_SIZE, "%s\n", "empty");
	अन्यथा
		cpumap_prपूर्णांक_to_pagebuf(true, buf, &sde->cpu_mask);
	mutex_unlock(&process_to_sde_mutex);
	वापस strnlen(buf, PAGE_SIZE);
पूर्ण

अटल व्योम sdma_rht_मुक्त(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा sdma_rht_node *rht_node = ptr;
	पूर्णांक i;

	क्रम (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++)
		kमुक्त(rht_node->map[i]);

	kमुक्त(rht_node);
पूर्ण

/**
 * sdma_seqfile_dump_cpu_list() - debugfs dump the cpu to sdma mappings
 * @s: seq file
 * @dd: hfi1_devdata
 * @cpuid: cpu id
 *
 * This routine dumps the process to sde mappings per cpu
 */
व्योम sdma_seqfile_dump_cpu_list(काष्ठा seq_file *s,
				काष्ठा hfi1_devdata *dd,
				अचिन्हित दीर्घ cpuid)
अणु
	काष्ठा sdma_rht_node *rht_node;
	पूर्णांक i, j;

	rht_node = rhashtable_lookup_fast(dd->sdma_rht, &cpuid,
					  sdma_rht_params);
	अगर (!rht_node)
		वापस;

	seq_म_लिखो(s, "cpu%3lu: ", cpuid);
	क्रम (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++) अणु
		अगर (!rht_node->map[i] || !rht_node->map[i]->ctr)
			जारी;

		seq_म_लिखो(s, " vl%d: [", i);

		क्रम (j = 0; j < rht_node->map[i]->ctr; j++) अणु
			अगर (!rht_node->map[i]->sde[j])
				जारी;

			अगर (j > 0)
				seq_माला_दो(s, ",");

			seq_म_लिखो(s, " sdma%2d",
				   rht_node->map[i]->sde[j]->this_idx);
		पूर्ण
		seq_माला_दो(s, " ]");
	पूर्ण

	seq_माला_दो(s, "\n");
पूर्ण

/*
 * Free the indicated map काष्ठा
 */
अटल व्योम sdma_map_मुक्त(काष्ठा sdma_vl_map *m)
अणु
	पूर्णांक i;

	क्रम (i = 0; m && i < m->actual_vls; i++)
		kमुक्त(m->map[i]);
	kमुक्त(m);
पूर्ण

/*
 * Handle RCU callback
 */
अटल व्योम sdma_map_rcu_callback(काष्ठा rcu_head *list)
अणु
	काष्ठा sdma_vl_map *m = container_of(list, काष्ठा sdma_vl_map, list);

	sdma_map_मुक्त(m);
पूर्ण

/**
 * sdma_map_init - called when # vls change
 * @dd: hfi1_devdata
 * @port: port number
 * @num_vls: number of vls
 * @vl_engines: per vl engine mapping (optional)
 *
 * This routine changes the mapping based on the number of vls.
 *
 * vl_engines is used to specअगरy a non-unअगरorm vl/engine loading. शून्य
 * implies स्वतः computing the loading and giving each VLs a unअगरorm
 * distribution of engines per VL.
 *
 * The स्वतः algorithm computes the sde_per_vl and the number of extra
 * engines.  Any extra engines are added from the last VL on करोwn.
 *
 * rcu locking is used here to control access to the mapping fields.
 *
 * If either the num_vls or num_sdma are non-घातer of 2, the array sizes
 * in the काष्ठा sdma_vl_map and the काष्ठा sdma_map_elem are rounded
 * up to the next highest घातer of 2 and the first entry is reused
 * in a round robin fashion.
 *
 * If an error occurs the map change is not करोne and the mapping is
 * not changed.
 *
 */
पूर्णांक sdma_map_init(काष्ठा hfi1_devdata *dd, u8 port, u8 num_vls, u8 *vl_engines)
अणु
	पूर्णांक i, j;
	पूर्णांक extra, sde_per_vl;
	पूर्णांक engine = 0;
	u8 lvl_engines[OPA_MAX_VLS];
	काष्ठा sdma_vl_map *oldmap, *newmap;

	अगर (!(dd->flags & HFI1_HAS_SEND_DMA))
		वापस 0;

	अगर (!vl_engines) अणु
		/* truncate भागide */
		sde_per_vl = dd->num_sdma / num_vls;
		/* extras */
		extra = dd->num_sdma % num_vls;
		vl_engines = lvl_engines;
		/* add extras from last vl करोwn */
		क्रम (i = num_vls - 1; i >= 0; i--, extra--)
			vl_engines[i] = sde_per_vl + (extra > 0 ? 1 : 0);
	पूर्ण
	/* build new map */
	newmap = kzalloc(
		माप(काष्ठा sdma_vl_map) +
			roundup_घात_of_two(num_vls) *
			माप(काष्ठा sdma_map_elem *),
		GFP_KERNEL);
	अगर (!newmap)
		जाओ bail;
	newmap->actual_vls = num_vls;
	newmap->vls = roundup_घात_of_two(num_vls);
	newmap->mask = (1 << ilog2(newmap->vls)) - 1;
	/* initialize back-map */
	क्रम (i = 0; i < TXE_NUM_SDMA_ENGINES; i++)
		newmap->engine_to_vl[i] = -1;
	क्रम (i = 0; i < newmap->vls; i++) अणु
		/* save क्रम wrap around */
		पूर्णांक first_engine = engine;

		अगर (i < newmap->actual_vls) अणु
			पूर्णांक sz = roundup_घात_of_two(vl_engines[i]);

			/* only allocate once */
			newmap->map[i] = kzalloc(
				माप(काष्ठा sdma_map_elem) +
					sz * माप(काष्ठा sdma_engine *),
				GFP_KERNEL);
			अगर (!newmap->map[i])
				जाओ bail;
			newmap->map[i]->mask = (1 << ilog2(sz)) - 1;
			/* assign engines */
			क्रम (j = 0; j < sz; j++) अणु
				newmap->map[i]->sde[j] =
					&dd->per_sdma[engine];
				अगर (++engine >= first_engine + vl_engines[i])
					/* wrap back to first engine */
					engine = first_engine;
			पूर्ण
			/* assign back-map */
			क्रम (j = 0; j < vl_engines[i]; j++)
				newmap->engine_to_vl[first_engine + j] = i;
		पूर्ण अन्यथा अणु
			/* just re-use entry without allocating */
			newmap->map[i] = newmap->map[i % num_vls];
		पूर्ण
		engine = first_engine + vl_engines[i];
	पूर्ण
	/* newmap in hand, save old map */
	spin_lock_irq(&dd->sde_map_lock);
	oldmap = rcu_dereference_रक्षित(dd->sdma_map,
					   lockdep_is_held(&dd->sde_map_lock));

	/* publish newmap */
	rcu_assign_poपूर्णांकer(dd->sdma_map, newmap);

	spin_unlock_irq(&dd->sde_map_lock);
	/* success, मुक्त any old map after grace period */
	अगर (oldmap)
		call_rcu(&oldmap->list, sdma_map_rcu_callback);
	वापस 0;
bail:
	/* मुक्त any partial allocation */
	sdma_map_मुक्त(newmap);
	वापस -ENOMEM;
पूर्ण

/**
 * sdma_clean - Clean up allocated memory
 * @dd:          काष्ठा hfi1_devdata
 * @num_engines: num sdma engines
 *
 * This routine can be called regardless of the success of
 * sdma_init()
 */
व्योम sdma_clean(काष्ठा hfi1_devdata *dd, माप_प्रकार num_engines)
अणु
	माप_प्रकार i;
	काष्ठा sdma_engine *sde;

	अगर (dd->sdma_pad_dma) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, SDMA_PAD,
				  (व्योम *)dd->sdma_pad_dma,
				  dd->sdma_pad_phys);
		dd->sdma_pad_dma = शून्य;
		dd->sdma_pad_phys = 0;
	पूर्ण
	अगर (dd->sdma_heads_dma) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, dd->sdma_heads_size,
				  (व्योम *)dd->sdma_heads_dma,
				  dd->sdma_heads_phys);
		dd->sdma_heads_dma = शून्य;
		dd->sdma_heads_phys = 0;
	पूर्ण
	क्रम (i = 0; dd->per_sdma && i < num_engines; ++i) अणु
		sde = &dd->per_sdma[i];

		sde->head_dma = शून्य;
		sde->head_phys = 0;

		अगर (sde->descq) अणु
			dma_मुक्त_coherent(
				&dd->pcidev->dev,
				sde->descq_cnt * माप(u64[2]),
				sde->descq,
				sde->descq_phys
			);
			sde->descq = शून्य;
			sde->descq_phys = 0;
		पूर्ण
		kvमुक्त(sde->tx_ring);
		sde->tx_ring = शून्य;
	पूर्ण
	spin_lock_irq(&dd->sde_map_lock);
	sdma_map_मुक्त(rcu_access_poपूर्णांकer(dd->sdma_map));
	RCU_INIT_POINTER(dd->sdma_map, शून्य);
	spin_unlock_irq(&dd->sde_map_lock);
	synchronize_rcu();
	kमुक्त(dd->per_sdma);
	dd->per_sdma = शून्य;

	अगर (dd->sdma_rht) अणु
		rhashtable_मुक्त_and_destroy(dd->sdma_rht, sdma_rht_मुक्त, शून्य);
		kमुक्त(dd->sdma_rht);
		dd->sdma_rht = शून्य;
	पूर्ण
पूर्ण

/**
 * sdma_init() - called when device probed
 * @dd: hfi1_devdata
 * @port: port number (currently only zero)
 *
 * Initializes each sde and its csrs.
 * Interrupts are not required to be enabled.
 *
 * Returns:
 * 0 - success, -त्रुटि_सं on failure
 */
पूर्णांक sdma_init(काष्ठा hfi1_devdata *dd, u8 port)
अणु
	अचिन्हित this_idx;
	काष्ठा sdma_engine *sde;
	काष्ठा rhashtable *पंचांगp_sdma_rht;
	u16 descq_cnt;
	व्योम *curr_head;
	काष्ठा hfi1_pportdata *ppd = dd->pport + port;
	u32 per_sdma_credits;
	uपूर्णांक idle_cnt = sdma_idle_cnt;
	माप_प्रकार num_engines = chip_sdma_engines(dd);
	पूर्णांक ret = -ENOMEM;

	अगर (!HFI1_CAP_IS_KSET(SDMA)) अणु
		HFI1_CAP_CLEAR(SDMA_AHG);
		वापस 0;
	पूर्ण
	अगर (mod_num_sdma &&
	    /* can't exceed chip support */
	    mod_num_sdma <= chip_sdma_engines(dd) &&
	    /* count must be >= vls */
	    mod_num_sdma >= num_vls)
		num_engines = mod_num_sdma;

	dd_dev_info(dd, "SDMA mod_num_sdma: %u\n", mod_num_sdma);
	dd_dev_info(dd, "SDMA chip_sdma_engines: %u\n", chip_sdma_engines(dd));
	dd_dev_info(dd, "SDMA chip_sdma_mem_size: %u\n",
		    chip_sdma_mem_size(dd));

	per_sdma_credits =
		chip_sdma_mem_size(dd) / (num_engines * SDMA_BLOCK_SIZE);

	/* set up मुक्तze रुकोqueue */
	init_रुकोqueue_head(&dd->sdma_unमुक्तze_wq);
	atomic_set(&dd->sdma_unमुक्तze_count, 0);

	descq_cnt = sdma_get_descq_cnt();
	dd_dev_info(dd, "SDMA engines %zu descq_cnt %u\n",
		    num_engines, descq_cnt);

	/* alloc memory क्रम array of send engines */
	dd->per_sdma = kसुस्मृति_node(num_engines, माप(*dd->per_sdma),
				    GFP_KERNEL, dd->node);
	अगर (!dd->per_sdma)
		वापस ret;

	idle_cnt = ns_to_cघड़ी(dd, idle_cnt);
	अगर (idle_cnt)
		dd->शेष_desc1 =
			SDMA_DESC1_HEAD_TO_HOST_FLAG;
	अन्यथा
		dd->शेष_desc1 =
			SDMA_DESC1_INT_REQ_FLAG;

	अगर (!sdma_desct_पूर्णांकr)
		sdma_desct_पूर्णांकr = SDMA_DESC_INTR;

	/* Allocate memory क्रम SendDMA descriptor FIFOs */
	क्रम (this_idx = 0; this_idx < num_engines; ++this_idx) अणु
		sde = &dd->per_sdma[this_idx];
		sde->dd = dd;
		sde->ppd = ppd;
		sde->this_idx = this_idx;
		sde->descq_cnt = descq_cnt;
		sde->desc_avail = sdma_descq_मुक्तcnt(sde);
		sde->sdma_shअगरt = ilog2(descq_cnt);
		sde->sdma_mask = (1 << sde->sdma_shअगरt) - 1;

		/* Create a mask specअगरically क्रम each पूर्णांकerrupt source */
		sde->पूर्णांक_mask = (u64)1 << (0 * TXE_NUM_SDMA_ENGINES +
					   this_idx);
		sde->progress_mask = (u64)1 << (1 * TXE_NUM_SDMA_ENGINES +
						this_idx);
		sde->idle_mask = (u64)1 << (2 * TXE_NUM_SDMA_ENGINES +
					    this_idx);
		/* Create a combined mask to cover all 3 पूर्णांकerrupt sources */
		sde->imask = sde->पूर्णांक_mask | sde->progress_mask |
			     sde->idle_mask;

		spin_lock_init(&sde->tail_lock);
		seqlock_init(&sde->head_lock);
		spin_lock_init(&sde->senddmactrl_lock);
		spin_lock_init(&sde->flushlist_lock);
		seqlock_init(&sde->रुकोlock);
		/* insure there is always a zero bit */
		sde->ahg_bits = 0xfffffffe00000000ULL;

		sdma_set_state(sde, sdma_state_s00_hw_करोwn);

		/* set up reference counting */
		kref_init(&sde->state.kref);
		init_completion(&sde->state.comp);

		INIT_LIST_HEAD(&sde->flushlist);
		INIT_LIST_HEAD(&sde->dmaरुको);

		sde->tail_csr =
			get_kctxt_csr_addr(dd, this_idx, SD(TAIL));

		tasklet_setup(&sde->sdma_hw_clean_up_task,
			      sdma_hw_clean_up_task);
		tasklet_setup(&sde->sdma_sw_clean_up_task,
			      sdma_sw_clean_up_task);
		INIT_WORK(&sde->err_halt_worker, sdma_err_halt_रुको);
		INIT_WORK(&sde->flush_worker, sdma_field_flush);

		sde->progress_check_head = 0;

		समयr_setup(&sde->err_progress_check_समयr,
			    sdma_err_progress_check, 0);

		sde->descq = dma_alloc_coherent(&dd->pcidev->dev,
						descq_cnt * माप(u64[2]),
						&sde->descq_phys, GFP_KERNEL);
		अगर (!sde->descq)
			जाओ bail;
		sde->tx_ring =
			kvzalloc_node(array_size(descq_cnt,
						 माप(काष्ठा sdma_txreq *)),
				      GFP_KERNEL, dd->node);
		अगर (!sde->tx_ring)
			जाओ bail;
	पूर्ण

	dd->sdma_heads_size = L1_CACHE_BYTES * num_engines;
	/* Allocate memory क्रम DMA of head रेजिस्टरs to memory */
	dd->sdma_heads_dma = dma_alloc_coherent(&dd->pcidev->dev,
						dd->sdma_heads_size,
						&dd->sdma_heads_phys,
						GFP_KERNEL);
	अगर (!dd->sdma_heads_dma) अणु
		dd_dev_err(dd, "failed to allocate SendDMA head memory\n");
		जाओ bail;
	पूर्ण

	/* Allocate memory क्रम pad */
	dd->sdma_pad_dma = dma_alloc_coherent(&dd->pcidev->dev, SDMA_PAD,
					      &dd->sdma_pad_phys, GFP_KERNEL);
	अगर (!dd->sdma_pad_dma) अणु
		dd_dev_err(dd, "failed to allocate SendDMA pad memory\n");
		जाओ bail;
	पूर्ण

	/* assign each engine to dअगरferent cacheline and init रेजिस्टरs */
	curr_head = (व्योम *)dd->sdma_heads_dma;
	क्रम (this_idx = 0; this_idx < num_engines; ++this_idx) अणु
		अचिन्हित दीर्घ phys_offset;

		sde = &dd->per_sdma[this_idx];

		sde->head_dma = curr_head;
		curr_head += L1_CACHE_BYTES;
		phys_offset = (अचिन्हित दीर्घ)sde->head_dma -
			      (अचिन्हित दीर्घ)dd->sdma_heads_dma;
		sde->head_phys = dd->sdma_heads_phys + phys_offset;
		init_sdma_regs(sde, per_sdma_credits, idle_cnt);
	पूर्ण
	dd->flags |= HFI1_HAS_SEND_DMA;
	dd->flags |= idle_cnt ? HFI1_HAS_SDMA_TIMEOUT : 0;
	dd->num_sdma = num_engines;
	ret = sdma_map_init(dd, port, ppd->vls_operational, शून्य);
	अगर (ret < 0)
		जाओ bail;

	पंचांगp_sdma_rht = kzalloc(माप(*पंचांगp_sdma_rht), GFP_KERNEL);
	अगर (!पंचांगp_sdma_rht) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	ret = rhashtable_init(पंचांगp_sdma_rht, &sdma_rht_params);
	अगर (ret < 0) अणु
		kमुक्त(पंचांगp_sdma_rht);
		जाओ bail;
	पूर्ण

	dd->sdma_rht = पंचांगp_sdma_rht;

	dd_dev_info(dd, "SDMA num_sdma: %u\n", dd->num_sdma);
	वापस 0;

bail:
	sdma_clean(dd, num_engines);
	वापस ret;
पूर्ण

/**
 * sdma_all_running() - called when the link goes up
 * @dd: hfi1_devdata
 *
 * This routine moves all engines to the running state.
 */
व्योम sdma_all_running(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा sdma_engine *sde;
	अचिन्हित पूर्णांक i;

	/* move all engines to running */
	क्रम (i = 0; i < dd->num_sdma; ++i) अणु
		sde = &dd->per_sdma[i];
		sdma_process_event(sde, sdma_event_e30_go_running);
	पूर्ण
पूर्ण

/**
 * sdma_all_idle() - called when the link goes करोwn
 * @dd: hfi1_devdata
 *
 * This routine moves all engines to the idle state.
 */
व्योम sdma_all_idle(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा sdma_engine *sde;
	अचिन्हित पूर्णांक i;

	/* idle all engines */
	क्रम (i = 0; i < dd->num_sdma; ++i) अणु
		sde = &dd->per_sdma[i];
		sdma_process_event(sde, sdma_event_e70_go_idle);
	पूर्ण
पूर्ण

/**
 * sdma_start() - called to kick off state processing क्रम all engines
 * @dd: hfi1_devdata
 *
 * This routine is क्रम kicking off the state processing क्रम all required
 * sdma engines.  Interrupts need to be working at this poपूर्णांक.
 *
 */
व्योम sdma_start(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित i;
	काष्ठा sdma_engine *sde;

	/* kick off the engines state processing */
	क्रम (i = 0; i < dd->num_sdma; ++i) अणु
		sde = &dd->per_sdma[i];
		sdma_process_event(sde, sdma_event_e10_go_hw_start);
	पूर्ण
पूर्ण

/**
 * sdma_निकास() - used when module is हटाओd
 * @dd: hfi1_devdata
 */
व्योम sdma_निकास(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित this_idx;
	काष्ठा sdma_engine *sde;

	क्रम (this_idx = 0; dd->per_sdma && this_idx < dd->num_sdma;
			++this_idx) अणु
		sde = &dd->per_sdma[this_idx];
		अगर (!list_empty(&sde->dmaरुको))
			dd_dev_err(dd, "sde %u: dmawait list not empty!\n",
				   sde->this_idx);
		sdma_process_event(sde, sdma_event_e00_go_hw_करोwn);

		del_समयr_sync(&sde->err_progress_check_समयr);

		/*
		 * This रुकोs क्रम the state machine to निकास so it is not
		 * necessary to समाप्त the sdma_sw_clean_up_task to make sure
		 * it is not running.
		 */
		sdma_finalput(&sde->state);
	पूर्ण
पूर्ण

/*
 * unmap the indicated descriptor
 */
अटल अंतरभूत व्योम sdma_unmap_desc(
	काष्ठा hfi1_devdata *dd,
	काष्ठा sdma_desc *descp)
अणु
	चयन (sdma_mapping_type(descp)) अणु
	हाल SDMA_MAP_SINGLE:
		dma_unmap_single(
			&dd->pcidev->dev,
			sdma_mapping_addr(descp),
			sdma_mapping_len(descp),
			DMA_TO_DEVICE);
		अवरोध;
	हाल SDMA_MAP_PAGE:
		dma_unmap_page(
			&dd->pcidev->dev,
			sdma_mapping_addr(descp),
			sdma_mapping_len(descp),
			DMA_TO_DEVICE);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * वापस the mode as indicated by the first
 * descriptor in the tx.
 */
अटल अंतरभूत u8 ahg_mode(काष्ठा sdma_txreq *tx)
अणु
	वापस (tx->descp[0].qw[1] & SDMA_DESC1_HEADER_MODE_SMASK)
		>> SDMA_DESC1_HEADER_MODE_SHIFT;
पूर्ण

/**
 * __sdma_txclean() - clean tx of mappings, descp *kदो_स्मृति's
 * @dd: hfi1_devdata क्रम unmapping
 * @tx: tx request to clean
 *
 * This is used in the progress routine to clean the tx or
 * by the ULP to toss an in-process tx build.
 *
 * The code can be called multiple बार without issue.
 *
 */
व्योम __sdma_txclean(
	काष्ठा hfi1_devdata *dd,
	काष्ठा sdma_txreq *tx)
अणु
	u16 i;

	अगर (tx->num_desc) अणु
		u8 skip = 0, mode = ahg_mode(tx);

		/* unmap first */
		sdma_unmap_desc(dd, &tx->descp[0]);
		/* determine number of AHG descriptors to skip */
		अगर (mode > SDMA_AHG_APPLY_UPDATE1)
			skip = mode >> 1;
		क्रम (i = 1 + skip; i < tx->num_desc; i++)
			sdma_unmap_desc(dd, &tx->descp[i]);
		tx->num_desc = 0;
	पूर्ण
	kमुक्त(tx->coalesce_buf);
	tx->coalesce_buf = शून्य;
	/* kदो_स्मृति'ed descp */
	अगर (unlikely(tx->desc_limit > ARRAY_SIZE(tx->descs))) अणु
		tx->desc_limit = ARRAY_SIZE(tx->descs);
		kमुक्त(tx->descp);
	पूर्ण
पूर्ण

अटल अंतरभूत u16 sdma_gethead(काष्ठा sdma_engine *sde)
अणु
	काष्ठा hfi1_devdata *dd = sde->dd;
	पूर्णांक use_dmahead;
	u16 hwhead;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__खाता__), __LINE__, __func__);
#पूर्ण_अगर

retry:
	use_dmahead = HFI1_CAP_IS_KSET(USE_SDMA_HEAD) && __sdma_running(sde) &&
					(dd->flags & HFI1_HAS_SDMA_TIMEOUT);
	hwhead = use_dmahead ?
		(u16)le64_to_cpu(*sde->head_dma) :
		(u16)पढ़ो_sde_csr(sde, SD(HEAD));

	अगर (unlikely(HFI1_CAP_IS_KSET(SDMA_HEAD_CHECK))) अणु
		u16 cnt;
		u16 swtail;
		u16 swhead;
		पूर्णांक sane;

		swhead = sde->descq_head & sde->sdma_mask;
		/* this code is really bad क्रम cache line trading */
		swtail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
		cnt = sde->descq_cnt;

		अगर (swhead < swtail)
			/* not wrapped */
			sane = (hwhead >= swhead) & (hwhead <= swtail);
		अन्यथा अगर (swhead > swtail)
			/* wrapped around */
			sane = ((hwhead >= swhead) && (hwhead < cnt)) ||
				(hwhead <= swtail);
		अन्यथा
			/* empty */
			sane = (hwhead == swhead);

		अगर (unlikely(!sane)) अणु
			dd_dev_err(dd, "SDMA(%u) bad head (%s) hwhd=%u swhd=%u swtl=%u cnt=%u\n",
				   sde->this_idx,
				   use_dmahead ? "dma" : "kreg",
				   hwhead, swhead, swtail, cnt);
			अगर (use_dmahead) अणु
				/* try one more समय, using csr */
				use_dmahead = 0;
				जाओ retry;
			पूर्ण
			/* proceed as अगर no progress */
			hwhead = swhead;
		पूर्ण
	पूर्ण
	वापस hwhead;
पूर्ण

/*
 * This is called when there are send DMA descriptors that might be
 * available.
 *
 * This is called with head_lock held.
 */
अटल व्योम sdma_desc_avail(काष्ठा sdma_engine *sde, uपूर्णांक avail)
अणु
	काष्ठा ioरुको *रुको, *nw, *tरुको;
	काष्ठा ioरुको *रुकोs[SDMA_WAIT_BATCH_SIZE];
	uपूर्णांक i, n = 0, seq, tidx = 0;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__खाता__), __LINE__, __func__);
	dd_dev_err(sde->dd, "avail: %u\n", avail);
#पूर्ण_अगर

	करो अणु
		seq = पढ़ो_seqbegin(&sde->रुकोlock);
		अगर (!list_empty(&sde->dmaरुको)) अणु
			/* at least one item */
			ग_लिखो_seqlock(&sde->रुकोlock);
			/* Harvest रुकोers wanting DMA descriptors */
			list_क्रम_each_entry_safe(
					रुको,
					nw,
					&sde->dmaरुको,
					list) अणु
				u32 num_desc;

				अगर (!रुको->wakeup)
					जारी;
				अगर (n == ARRAY_SIZE(रुकोs))
					अवरोध;
				ioरुको_init_priority(रुको);
				num_desc = ioरुको_get_all_desc(रुको);
				अगर (num_desc > avail)
					अवरोध;
				avail -= num_desc;
				/* Find the top-priority रुको memeber */
				अगर (n) अणु
					tरुको = रुकोs[tidx];
					tidx =
					    ioरुको_priority_update_top(रुको,
								       tरुको,
								       n,
								       tidx);
				पूर्ण
				list_del_init(&रुको->list);
				रुकोs[n++] = रुको;
			पूर्ण
			ग_लिखो_sequnlock(&sde->रुकोlock);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqretry(&sde->रुकोlock, seq));

	/* Schedule the top-priority entry first */
	अगर (n)
		रुकोs[tidx]->wakeup(रुकोs[tidx], SDMA_AVAIL_REASON);

	क्रम (i = 0; i < n; i++)
		अगर (i != tidx)
			रुकोs[i]->wakeup(रुकोs[i], SDMA_AVAIL_REASON);
पूर्ण

/* head_lock must be held */
अटल व्योम sdma_make_progress(काष्ठा sdma_engine *sde, u64 status)
अणु
	काष्ठा sdma_txreq *txp = शून्य;
	पूर्णांक progress = 0;
	u16 hwhead, swhead;
	पूर्णांक idle_check_करोne = 0;

	hwhead = sdma_gethead(sde);

	/* The reason क्रम some of the complनिकासy of this code is that
	 * not all descriptors have corresponding txps.  So, we have to
	 * be able to skip over descs until we wander पूर्णांकo the range of
	 * the next txp on the list.
	 */

retry:
	txp = get_txhead(sde);
	swhead = sde->descq_head & sde->sdma_mask;
	trace_hfi1_sdma_progress(sde, hwhead, swhead, txp);
	जबतक (swhead != hwhead) अणु
		/* advance head, wrap अगर needed */
		swhead = ++sde->descq_head & sde->sdma_mask;

		/* अगर now past this txp's descs, करो the callback */
		अगर (txp && txp->next_descq_idx == swhead) अणु
			/* हटाओ from list */
			sde->tx_ring[sde->tx_head++ & sde->sdma_mask] = शून्य;
			complete_tx(sde, txp, SDMA_TXREQ_S_OK);
			/* see अगर there is another txp */
			txp = get_txhead(sde);
		पूर्ण
		trace_hfi1_sdma_progress(sde, hwhead, swhead, txp);
		progress++;
	पूर्ण

	/*
	 * The SDMA idle पूर्णांकerrupt is not guaranteed to be ordered with respect
	 * to updates to the the dma_head location in host memory. The head
	 * value पढ़ो might not be fully up to date. If there are pending
	 * descriptors and the SDMA idle पूर्णांकerrupt fired then पढ़ो from the
	 * CSR SDMA head instead to get the latest value from the hardware.
	 * The hardware SDMA head should be पढ़ो at most once in this invocation
	 * of sdma_make_progress(..) which is ensured by idle_check_करोne flag
	 */
	अगर ((status & sde->idle_mask) && !idle_check_करोne) अणु
		u16 swtail;

		swtail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
		अगर (swtail != hwhead) अणु
			hwhead = (u16)पढ़ो_sde_csr(sde, SD(HEAD));
			idle_check_करोne = 1;
			जाओ retry;
		पूर्ण
	पूर्ण

	sde->last_status = status;
	अगर (progress)
		sdma_desc_avail(sde, sdma_descq_मुक्तcnt(sde));
पूर्ण

/*
 * sdma_engine_पूर्णांकerrupt() - पूर्णांकerrupt handler क्रम engine
 * @sde: sdma engine
 * @status: sdma पूर्णांकerrupt reason
 *
 * Status is a mask of the 3 possible पूर्णांकerrupts क्रम this engine.  It will
 * contain bits _only_ क्रम this SDMA engine.  It will contain at least one
 * bit, it may contain more.
 */
व्योम sdma_engine_पूर्णांकerrupt(काष्ठा sdma_engine *sde, u64 status)
अणु
	trace_hfi1_sdma_engine_पूर्णांकerrupt(sde, status);
	ग_लिखो_seqlock(&sde->head_lock);
	sdma_set_desc_cnt(sde, sdma_desct_पूर्णांकr);
	अगर (status & sde->idle_mask)
		sde->idle_पूर्णांक_cnt++;
	अन्यथा अगर (status & sde->progress_mask)
		sde->progress_पूर्णांक_cnt++;
	अन्यथा अगर (status & sde->पूर्णांक_mask)
		sde->sdma_पूर्णांक_cnt++;
	sdma_make_progress(sde, status);
	ग_लिखो_sequnlock(&sde->head_lock);
पूर्ण

/**
 * sdma_engine_error() - error handler क्रम engine
 * @sde: sdma engine
 * @status: sdma पूर्णांकerrupt reason
 */
व्योम sdma_engine_error(काष्ठा sdma_engine *sde, u64 status)
अणु
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) error status 0x%llx state %s\n",
		   sde->this_idx,
		   (अचिन्हित दीर्घ दीर्घ)status,
		   sdma_state_names[sde->state.current_state]);
#पूर्ण_अगर
	spin_lock_irqsave(&sde->tail_lock, flags);
	ग_लिखो_seqlock(&sde->head_lock);
	अगर (status & ALL_SDMA_ENG_HALT_ERRS)
		__sdma_process_event(sde, sdma_event_e60_hw_halted);
	अगर (status & ~SD(ENG_ERR_STATUS_SDMA_HALT_ERR_SMASK)) अणु
		dd_dev_err(sde->dd,
			   "SDMA (%u) engine error: 0x%llx state %s\n",
			   sde->this_idx,
			   (अचिन्हित दीर्घ दीर्घ)status,
			   sdma_state_names[sde->state.current_state]);
		dump_sdma_state(sde);
	पूर्ण
	ग_लिखो_sequnlock(&sde->head_lock);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
पूर्ण

अटल व्योम sdma_sendctrl(काष्ठा sdma_engine *sde, अचिन्हित op)
अणु
	u64 set_senddmactrl = 0;
	u64 clr_senddmactrl = 0;
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) senddmactrl E=%d I=%d H=%d C=%d\n",
		   sde->this_idx,
		   (op & SDMA_SENDCTRL_OP_ENABLE) ? 1 : 0,
		   (op & SDMA_SENDCTRL_OP_INTENABLE) ? 1 : 0,
		   (op & SDMA_SENDCTRL_OP_HALT) ? 1 : 0,
		   (op & SDMA_SENDCTRL_OP_CLEANUP) ? 1 : 0);
#पूर्ण_अगर

	अगर (op & SDMA_SENDCTRL_OP_ENABLE)
		set_senddmactrl |= SD(CTRL_SDMA_ENABLE_SMASK);
	अन्यथा
		clr_senddmactrl |= SD(CTRL_SDMA_ENABLE_SMASK);

	अगर (op & SDMA_SENDCTRL_OP_INTENABLE)
		set_senddmactrl |= SD(CTRL_SDMA_INT_ENABLE_SMASK);
	अन्यथा
		clr_senddmactrl |= SD(CTRL_SDMA_INT_ENABLE_SMASK);

	अगर (op & SDMA_SENDCTRL_OP_HALT)
		set_senddmactrl |= SD(CTRL_SDMA_HALT_SMASK);
	अन्यथा
		clr_senddmactrl |= SD(CTRL_SDMA_HALT_SMASK);

	spin_lock_irqsave(&sde->senddmactrl_lock, flags);

	sde->p_senddmactrl |= set_senddmactrl;
	sde->p_senddmactrl &= ~clr_senddmactrl;

	अगर (op & SDMA_SENDCTRL_OP_CLEANUP)
		ग_लिखो_sde_csr(sde, SD(CTRL),
			      sde->p_senddmactrl |
			      SD(CTRL_SDMA_CLEANUP_SMASK));
	अन्यथा
		ग_लिखो_sde_csr(sde, SD(CTRL), sde->p_senddmactrl);

	spin_unlock_irqrestore(&sde->senddmactrl_lock, flags);

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	sdma_dumpstate(sde);
#पूर्ण_अगर
पूर्ण

अटल व्योम sdma_setlengen(काष्ठा sdma_engine *sde)
अणु
#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__खाता__), __LINE__, __func__);
#पूर्ण_अगर

	/*
	 * Set SendDmaLenGen and clear-then-set the MSB of the generation
	 * count to enable generation checking and load the पूर्णांकernal
	 * generation counter.
	 */
	ग_लिखो_sde_csr(sde, SD(LEN_GEN),
		      (sde->descq_cnt / 64) << SD(LEN_GEN_LENGTH_SHIFT));
	ग_लिखो_sde_csr(sde, SD(LEN_GEN),
		      ((sde->descq_cnt / 64) << SD(LEN_GEN_LENGTH_SHIFT)) |
		      (4ULL << SD(LEN_GEN_GENERATION_SHIFT)));
पूर्ण

अटल अंतरभूत व्योम sdma_update_tail(काष्ठा sdma_engine *sde, u16 tail)
अणु
	/* Commit ग_लिखोs to memory and advance the tail on the chip */
	smp_wmb(); /* see get_txhead() */
	ग_लिखोq(tail, sde->tail_csr);
पूर्ण

/*
 * This is called when changing to state s10_hw_start_up_halt_रुको as
 * a result of send buffer errors or send DMA descriptor errors.
 */
अटल व्योम sdma_hw_start_up(काष्ठा sdma_engine *sde)
अणु
	u64 reg;

#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__खाता__), __LINE__, __func__);
#पूर्ण_अगर

	sdma_setlengen(sde);
	sdma_update_tail(sde, 0); /* Set SendDmaTail */
	*sde->head_dma = 0;

	reg = SD(ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_MASK) <<
	      SD(ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_SHIFT);
	ग_लिखो_sde_csr(sde, SD(ENG_ERR_CLEAR), reg);
पूर्ण

/*
 * set_sdma_पूर्णांकegrity
 *
 * Set the SEND_DMA_CHECK_ENABLE रेजिस्टर क्रम send DMA engine 'sde'.
 */
अटल व्योम set_sdma_पूर्णांकegrity(काष्ठा sdma_engine *sde)
अणु
	काष्ठा hfi1_devdata *dd = sde->dd;

	ग_लिखो_sde_csr(sde, SD(CHECK_ENABLE),
		      hfi1_pkt_base_sdma_पूर्णांकegrity(dd));
पूर्ण

अटल व्योम init_sdma_regs(
	काष्ठा sdma_engine *sde,
	u32 credits,
	uपूर्णांक idle_cnt)
अणु
	u8 opval, opmask;
#अगर_घोषित CONFIG_SDMA_VERBOSITY
	काष्ठा hfi1_devdata *dd = sde->dd;

	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__खाता__), __LINE__, __func__);
#पूर्ण_अगर

	ग_लिखो_sde_csr(sde, SD(BASE_ADDR), sde->descq_phys);
	sdma_setlengen(sde);
	sdma_update_tail(sde, 0); /* Set SendDmaTail */
	ग_लिखो_sde_csr(sde, SD(RELOAD_CNT), idle_cnt);
	ग_लिखो_sde_csr(sde, SD(DESC_CNT), 0);
	ग_लिखो_sde_csr(sde, SD(HEAD_ADDR), sde->head_phys);
	ग_लिखो_sde_csr(sde, SD(MEMORY),
		      ((u64)credits << SD(MEMORY_SDMA_MEMORY_CNT_SHIFT)) |
		      ((u64)(credits * sde->this_idx) <<
		       SD(MEMORY_SDMA_MEMORY_INDEX_SHIFT)));
	ग_लिखो_sde_csr(sde, SD(ENG_ERR_MASK), ~0ull);
	set_sdma_पूर्णांकegrity(sde);
	opmask = OPCODE_CHECK_MASK_DISABLED;
	opval = OPCODE_CHECK_VAL_DISABLED;
	ग_लिखो_sde_csr(sde, SD(CHECK_OPCODE),
		      (opmask << SEND_CTXT_CHECK_OPCODE_MASK_SHIFT) |
		      (opval << SEND_CTXT_CHECK_OPCODE_VALUE_SHIFT));
पूर्ण

#अगर_घोषित CONFIG_SDMA_VERBOSITY

#घोषणा sdma_dumpstate_helper0(reg) करो अणु \
		csr = पढ़ो_csr(sde->dd, reg); \
		dd_dev_err(sde->dd, "%36s     0x%016llx\n", #reg, csr); \
	पूर्ण जबतक (0)

#घोषणा sdma_dumpstate_helper(reg) करो अणु \
		csr = पढ़ो_sde_csr(sde, reg); \
		dd_dev_err(sde->dd, "%36s[%02u] 0x%016llx\n", \
			#reg, sde->this_idx, csr); \
	पूर्ण जबतक (0)

#घोषणा sdma_dumpstate_helper2(reg) करो अणु \
		csr = पढ़ो_csr(sde->dd, reg + (8 * i)); \
		dd_dev_err(sde->dd, "%33s_%02u     0x%016llx\n", \
				#reg, i, csr); \
	पूर्ण जबतक (0)

व्योम sdma_dumpstate(काष्ठा sdma_engine *sde)
अणु
	u64 csr;
	अचिन्हित i;

	sdma_dumpstate_helper(SD(CTRL));
	sdma_dumpstate_helper(SD(STATUS));
	sdma_dumpstate_helper0(SD(ERR_STATUS));
	sdma_dumpstate_helper0(SD(ERR_MASK));
	sdma_dumpstate_helper(SD(ENG_ERR_STATUS));
	sdma_dumpstate_helper(SD(ENG_ERR_MASK));

	क्रम (i = 0; i < CCE_NUM_INT_CSRS; ++i) अणु
		sdma_dumpstate_helper2(CCE_INT_STATUS);
		sdma_dumpstate_helper2(CCE_INT_MASK);
		sdma_dumpstate_helper2(CCE_INT_BLOCKED);
	पूर्ण

	sdma_dumpstate_helper(SD(TAIL));
	sdma_dumpstate_helper(SD(HEAD));
	sdma_dumpstate_helper(SD(PRIORITY_THLD));
	sdma_dumpstate_helper(SD(IDLE_CNT));
	sdma_dumpstate_helper(SD(RELOAD_CNT));
	sdma_dumpstate_helper(SD(DESC_CNT));
	sdma_dumpstate_helper(SD(DESC_FETCHED_CNT));
	sdma_dumpstate_helper(SD(MEMORY));
	sdma_dumpstate_helper0(SD(ENGINES));
	sdma_dumpstate_helper0(SD(MEM_SIZE));
	/* sdma_dumpstate_helper(SEND_EGRESS_SEND_DMA_STATUS);  */
	sdma_dumpstate_helper(SD(BASE_ADDR));
	sdma_dumpstate_helper(SD(LEN_GEN));
	sdma_dumpstate_helper(SD(HEAD_ADDR));
	sdma_dumpstate_helper(SD(CHECK_ENABLE));
	sdma_dumpstate_helper(SD(CHECK_VL));
	sdma_dumpstate_helper(SD(CHECK_JOB_KEY));
	sdma_dumpstate_helper(SD(CHECK_PARTITION_KEY));
	sdma_dumpstate_helper(SD(CHECK_SLID));
	sdma_dumpstate_helper(SD(CHECK_OPCODE));
पूर्ण
#पूर्ण_अगर

अटल व्योम dump_sdma_state(काष्ठा sdma_engine *sde)
अणु
	काष्ठा hw_sdma_desc *descqp;
	u64 desc[2];
	u64 addr;
	u8 gen;
	u16 len;
	u16 head, tail, cnt;

	head = sde->descq_head & sde->sdma_mask;
	tail = sde->descq_tail & sde->sdma_mask;
	cnt = sdma_descq_मुक्तcnt(sde);

	dd_dev_err(sde->dd,
		   "SDMA (%u) descq_head: %u descq_tail: %u freecnt: %u FLE %d\n",
		   sde->this_idx, head, tail, cnt,
		   !list_empty(&sde->flushlist));

	/* prपूर्णांक info क्रम each entry in the descriptor queue */
	जबतक (head != tail) अणु
		अक्षर flags[6] = अणु 'x', 'x', 'x', 'x', 0 पूर्ण;

		descqp = &sde->descq[head];
		desc[0] = le64_to_cpu(descqp->qw[0]);
		desc[1] = le64_to_cpu(descqp->qw[1]);
		flags[0] = (desc[1] & SDMA_DESC1_INT_REQ_FLAG) ? 'I' : '-';
		flags[1] = (desc[1] & SDMA_DESC1_HEAD_TO_HOST_FLAG) ?
				'H' : '-';
		flags[2] = (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG) ? 'F' : '-';
		flags[3] = (desc[0] & SDMA_DESC0_LAST_DESC_FLAG) ? 'L' : '-';
		addr = (desc[0] >> SDMA_DESC0_PHY_ADDR_SHIFT)
			& SDMA_DESC0_PHY_ADDR_MASK;
		gen = (desc[1] >> SDMA_DESC1_GENERATION_SHIFT)
			& SDMA_DESC1_GENERATION_MASK;
		len = (desc[0] >> SDMA_DESC0_BYTE_COUNT_SHIFT)
			& SDMA_DESC0_BYTE_COUNT_MASK;
		dd_dev_err(sde->dd,
			   "SDMA sdmadesc[%u]: flags:%s addr:0x%016llx gen:%u len:%u bytes\n",
			   head, flags, addr, gen, len);
		dd_dev_err(sde->dd,
			   "\tdesc0:0x%016llx desc1 0x%016llx\n",
			   desc[0], desc[1]);
		अगर (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG)
			dd_dev_err(sde->dd,
				   "\taidx: %u amode: %u alen: %u\n",
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_INDEX_SMASK) >>
					SDMA_DESC1_HEADER_INDEX_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_MODE_SMASK) >>
					SDMA_DESC1_HEADER_MODE_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_DWS_SMASK) >>
					SDMA_DESC1_HEADER_DWS_SHIFT));
		head++;
		head &= sde->sdma_mask;
	पूर्ण
पूर्ण

#घोषणा SDE_FMT \
	"SDE %u CPU %d STE %s C 0x%llx S 0x%016llx E 0x%llx T(HW) 0x%llx T(SW) 0x%x H(HW) 0x%llx H(SW) 0x%x H(D) 0x%llx DM 0x%llx GL 0x%llx R 0x%llx LIS 0x%llx AHGI 0x%llx TXT %u TXH %u DT %u DH %u FLNE %d DQF %u SLC 0x%llx\n"
/**
 * sdma_seqfile_dump_sde() - debugfs dump of sde
 * @s: seq file
 * @sde: send dma engine to dump
 *
 * This routine dumps the sde to the indicated seq file.
 */
व्योम sdma_seqfile_dump_sde(काष्ठा seq_file *s, काष्ठा sdma_engine *sde)
अणु
	u16 head, tail;
	काष्ठा hw_sdma_desc *descqp;
	u64 desc[2];
	u64 addr;
	u8 gen;
	u16 len;

	head = sde->descq_head & sde->sdma_mask;
	tail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
	seq_म_लिखो(s, SDE_FMT, sde->this_idx,
		   sde->cpu,
		   sdma_state_name(sde->state.current_state),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(CTRL)),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(STATUS)),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(ENG_ERR_STATUS)),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(TAIL)), tail,
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(HEAD)), head,
		   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(*sde->head_dma),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(MEMORY)),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(LEN_GEN)),
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SD(RELOAD_CNT)),
		   (अचिन्हित दीर्घ दीर्घ)sde->last_status,
		   (अचिन्हित दीर्घ दीर्घ)sde->ahg_bits,
		   sde->tx_tail,
		   sde->tx_head,
		   sde->descq_tail,
		   sde->descq_head,
		   !list_empty(&sde->flushlist),
		   sde->descq_full_count,
		   (अचिन्हित दीर्घ दीर्घ)पढ़ो_sde_csr(sde, SEND_DMA_CHECK_SLID));

	/* prपूर्णांक info क्रम each entry in the descriptor queue */
	जबतक (head != tail) अणु
		अक्षर flags[6] = अणु 'x', 'x', 'x', 'x', 0 पूर्ण;

		descqp = &sde->descq[head];
		desc[0] = le64_to_cpu(descqp->qw[0]);
		desc[1] = le64_to_cpu(descqp->qw[1]);
		flags[0] = (desc[1] & SDMA_DESC1_INT_REQ_FLAG) ? 'I' : '-';
		flags[1] = (desc[1] & SDMA_DESC1_HEAD_TO_HOST_FLAG) ?
				'H' : '-';
		flags[2] = (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG) ? 'F' : '-';
		flags[3] = (desc[0] & SDMA_DESC0_LAST_DESC_FLAG) ? 'L' : '-';
		addr = (desc[0] >> SDMA_DESC0_PHY_ADDR_SHIFT)
			& SDMA_DESC0_PHY_ADDR_MASK;
		gen = (desc[1] >> SDMA_DESC1_GENERATION_SHIFT)
			& SDMA_DESC1_GENERATION_MASK;
		len = (desc[0] >> SDMA_DESC0_BYTE_COUNT_SHIFT)
			& SDMA_DESC0_BYTE_COUNT_MASK;
		seq_म_लिखो(s,
			   "\tdesc[%u]: flags:%s addr:0x%016llx gen:%u len:%u bytes\n",
			   head, flags, addr, gen, len);
		अगर (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG)
			seq_म_लिखो(s, "\t\tahgidx: %u ahgmode: %u\n",
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_INDEX_SMASK) >>
					SDMA_DESC1_HEADER_INDEX_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_MODE_SMASK) >>
					SDMA_DESC1_HEADER_MODE_SHIFT));
		head = (head + 1) & sde->sdma_mask;
	पूर्ण
पूर्ण

/*
 * add the generation number पूर्णांकo
 * the qw1 and वापस
 */
अटल अंतरभूत u64 add_gen(काष्ठा sdma_engine *sde, u64 qw1)
अणु
	u8 generation = (sde->descq_tail >> sde->sdma_shअगरt) & 3;

	qw1 &= ~SDMA_DESC1_GENERATION_SMASK;
	qw1 |= ((u64)generation & SDMA_DESC1_GENERATION_MASK)
			<< SDMA_DESC1_GENERATION_SHIFT;
	वापस qw1;
पूर्ण

/*
 * This routine submits the indicated tx
 *
 * Space has alपढ़ोy been guaranteed and
 * tail side of ring is locked.
 *
 * The hardware tail update is करोne
 * in the caller and that is facilitated
 * by वापसing the new tail.
 *
 * There is special हाल logic क्रम ahg
 * to not add the generation number क्रम
 * up to 2 descriptors that follow the
 * first descriptor.
 *
 */
अटल अंतरभूत u16 submit_tx(काष्ठा sdma_engine *sde, काष्ठा sdma_txreq *tx)
अणु
	पूर्णांक i;
	u16 tail;
	काष्ठा sdma_desc *descp = tx->descp;
	u8 skip = 0, mode = ahg_mode(tx);

	tail = sde->descq_tail & sde->sdma_mask;
	sde->descq[tail].qw[0] = cpu_to_le64(descp->qw[0]);
	sde->descq[tail].qw[1] = cpu_to_le64(add_gen(sde, descp->qw[1]));
	trace_hfi1_sdma_descriptor(sde, descp->qw[0], descp->qw[1],
				   tail, &sde->descq[tail]);
	tail = ++sde->descq_tail & sde->sdma_mask;
	descp++;
	अगर (mode > SDMA_AHG_APPLY_UPDATE1)
		skip = mode >> 1;
	क्रम (i = 1; i < tx->num_desc; i++, descp++) अणु
		u64 qw1;

		sde->descq[tail].qw[0] = cpu_to_le64(descp->qw[0]);
		अगर (skip) अणु
			/* edits करोn't have generation */
			qw1 = descp->qw[1];
			skip--;
		पूर्ण अन्यथा अणु
			/* replace generation with real one क्रम non-edits */
			qw1 = add_gen(sde, descp->qw[1]);
		पूर्ण
		sde->descq[tail].qw[1] = cpu_to_le64(qw1);
		trace_hfi1_sdma_descriptor(sde, descp->qw[0], qw1,
					   tail, &sde->descq[tail]);
		tail = ++sde->descq_tail & sde->sdma_mask;
	पूर्ण
	tx->next_descq_idx = tail;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	tx->sn = sde->tail_sn++;
	trace_hfi1_sdma_in_sn(sde, tx->sn);
	WARN_ON_ONCE(sde->tx_ring[sde->tx_tail & sde->sdma_mask]);
#पूर्ण_अगर
	sde->tx_ring[sde->tx_tail++ & sde->sdma_mask] = tx;
	sde->desc_avail -= tx->num_desc;
	वापस tail;
पूर्ण

/*
 * Check क्रम progress
 */
अटल पूर्णांक sdma_check_progress(
	काष्ठा sdma_engine *sde,
	काष्ठा ioरुको_work *रुको,
	काष्ठा sdma_txreq *tx,
	bool pkts_sent)
अणु
	पूर्णांक ret;

	sde->desc_avail = sdma_descq_मुक्तcnt(sde);
	अगर (tx->num_desc <= sde->desc_avail)
		वापस -EAGAIN;
	/* pulse the head_lock */
	अगर (रुको && ioरुको_ioww_to_iow(रुको)->sleep) अणु
		अचिन्हित seq;

		seq = raw_seqcount_begin(
			(स्थिर seqcount_t *)&sde->head_lock.seqcount);
		ret = रुको->iow->sleep(sde, रुको, tx, seq, pkts_sent);
		अगर (ret == -EAGAIN)
			sde->desc_avail = sdma_descq_मुक्तcnt(sde);
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * sdma_send_txreq() - submit a tx req to ring
 * @sde: sdma engine to use
 * @रुको: SE रुको काष्ठाure to use when full (may be शून्य)
 * @tx: sdma_txreq to submit
 * @pkts_sent: has any packet been sent yet?
 *
 * The call submits the tx पूर्णांकo the ring.  If a ioरुको काष्ठाure is non-शून्य
 * the packet will be queued to the list in रुको.
 *
 * Return:
 * 0 - Success, -EINVAL - sdma_txreq incomplete, -EBUSY - no space in
 * ring (रुको == शून्य)
 * -EIOCBQUEUED - tx queued to ioरुको, -ECOMM bad sdma state
 */
पूर्णांक sdma_send_txreq(काष्ठा sdma_engine *sde,
		    काष्ठा ioरुको_work *रुको,
		    काष्ठा sdma_txreq *tx,
		    bool pkts_sent)
अणु
	पूर्णांक ret = 0;
	u16 tail;
	अचिन्हित दीर्घ flags;

	/* user should have supplied entire packet */
	अगर (unlikely(tx->tlen))
		वापस -EINVAL;
	tx->रुको = ioरुको_ioww_to_iow(रुको);
	spin_lock_irqsave(&sde->tail_lock, flags);
retry:
	अगर (unlikely(!__sdma_running(sde)))
		जाओ unlock_noconn;
	अगर (unlikely(tx->num_desc > sde->desc_avail))
		जाओ nodesc;
	tail = submit_tx(sde, tx);
	अगर (रुको)
		ioरुको_sdma_inc(ioरुको_ioww_to_iow(रुको));
	sdma_update_tail(sde, tail);
unlock:
	spin_unlock_irqrestore(&sde->tail_lock, flags);
	वापस ret;
unlock_noconn:
	अगर (रुको)
		ioरुको_sdma_inc(ioरुको_ioww_to_iow(रुको));
	tx->next_descq_idx = 0;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	tx->sn = sde->tail_sn++;
	trace_hfi1_sdma_in_sn(sde, tx->sn);
#पूर्ण_अगर
	spin_lock(&sde->flushlist_lock);
	list_add_tail(&tx->list, &sde->flushlist);
	spin_unlock(&sde->flushlist_lock);
	ioरुको_inc_रुको_count(रुको, tx->num_desc);
	queue_work_on(sde->cpu, प्रणाली_highpri_wq, &sde->flush_worker);
	ret = -ECOMM;
	जाओ unlock;
nodesc:
	ret = sdma_check_progress(sde, रुको, tx, pkts_sent);
	अगर (ret == -EAGAIN) अणु
		ret = 0;
		जाओ retry;
	पूर्ण
	sde->descq_full_count++;
	जाओ unlock;
पूर्ण

/**
 * sdma_send_txlist() - submit a list of tx req to ring
 * @sde: sdma engine to use
 * @रुको: SE रुको काष्ठाure to use when full (may be शून्य)
 * @tx_list: list of sdma_txreqs to submit
 * @count_out: poपूर्णांकer to a u16 which, after वापस will contain the total number of
 *             sdma_txreqs हटाओd from the tx_list. This will include sdma_txreqs
 *             whose SDMA descriptors are submitted to the ring and the sdma_txreqs
 *             which are added to SDMA engine flush list अगर the SDMA engine state is
 *             not running.
 *
 * The call submits the list पूर्णांकo the ring.
 *
 * If the ioरुको काष्ठाure is non-शून्य and not equal to the ioरुको list
 * the unprocessed part of the list  will be appended to the list in रुको.
 *
 * In all हालs, the tx_list will be updated so the head of the tx_list is
 * the list of descriptors that have yet to be transmitted.
 *
 * The पूर्णांकent of this call is to provide a more efficient
 * way of submitting multiple packets to SDMA जबतक holding the tail
 * side locking.
 *
 * Return:
 * 0 - Success,
 * -EINVAL - sdma_txreq incomplete, -EBUSY - no space in ring (रुको == शून्य)
 * -EIOCBQUEUED - tx queued to ioरुको, -ECOMM bad sdma state
 */
पूर्णांक sdma_send_txlist(काष्ठा sdma_engine *sde, काष्ठा ioरुको_work *रुको,
		     काष्ठा list_head *tx_list, u16 *count_out)
अणु
	काष्ठा sdma_txreq *tx, *tx_next;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	u16 tail = INVALID_TAIL;
	u32 submit_count = 0, flush_count = 0, total_count;

	spin_lock_irqsave(&sde->tail_lock, flags);
retry:
	list_क्रम_each_entry_safe(tx, tx_next, tx_list, list) अणु
		tx->रुको = ioरुको_ioww_to_iow(रुको);
		अगर (unlikely(!__sdma_running(sde)))
			जाओ unlock_noconn;
		अगर (unlikely(tx->num_desc > sde->desc_avail))
			जाओ nodesc;
		अगर (unlikely(tx->tlen)) अणु
			ret = -EINVAL;
			जाओ update_tail;
		पूर्ण
		list_del_init(&tx->list);
		tail = submit_tx(sde, tx);
		submit_count++;
		अगर (tail != INVALID_TAIL &&
		    (submit_count & SDMA_TAIL_UPDATE_THRESH) == 0) अणु
			sdma_update_tail(sde, tail);
			tail = INVALID_TAIL;
		पूर्ण
	पूर्ण
update_tail:
	total_count = submit_count + flush_count;
	अगर (रुको) अणु
		ioरुको_sdma_add(ioरुको_ioww_to_iow(रुको), total_count);
		ioरुको_starve_clear(submit_count > 0,
				    ioरुको_ioww_to_iow(रुको));
	पूर्ण
	अगर (tail != INVALID_TAIL)
		sdma_update_tail(sde, tail);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
	*count_out = total_count;
	वापस ret;
unlock_noconn:
	spin_lock(&sde->flushlist_lock);
	list_क्रम_each_entry_safe(tx, tx_next, tx_list, list) अणु
		tx->रुको = ioरुको_ioww_to_iow(रुको);
		list_del_init(&tx->list);
		tx->next_descq_idx = 0;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
		tx->sn = sde->tail_sn++;
		trace_hfi1_sdma_in_sn(sde, tx->sn);
#पूर्ण_अगर
		list_add_tail(&tx->list, &sde->flushlist);
		flush_count++;
		ioरुको_inc_रुको_count(रुको, tx->num_desc);
	पूर्ण
	spin_unlock(&sde->flushlist_lock);
	queue_work_on(sde->cpu, प्रणाली_highpri_wq, &sde->flush_worker);
	ret = -ECOMM;
	जाओ update_tail;
nodesc:
	ret = sdma_check_progress(sde, रुको, tx, submit_count > 0);
	अगर (ret == -EAGAIN) अणु
		ret = 0;
		जाओ retry;
	पूर्ण
	sde->descq_full_count++;
	जाओ update_tail;
पूर्ण

अटल व्योम sdma_process_event(काष्ठा sdma_engine *sde, क्रमागत sdma_events event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sde->tail_lock, flags);
	ग_लिखो_seqlock(&sde->head_lock);

	__sdma_process_event(sde, event);

	अगर (sde->state.current_state == sdma_state_s99_running)
		sdma_desc_avail(sde, sdma_descq_मुक्तcnt(sde));

	ग_लिखो_sequnlock(&sde->head_lock);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
पूर्ण

अटल व्योम __sdma_process_event(काष्ठा sdma_engine *sde,
				 क्रमागत sdma_events event)
अणु
	काष्ठा sdma_state *ss = &sde->state;
	पूर्णांक need_progress = 0;

	/* CONFIG SDMA temporary */
#अगर_घोषित CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) [%s] %s\n", sde->this_idx,
		   sdma_state_names[ss->current_state],
		   sdma_event_names[event]);
#पूर्ण_अगर

	चयन (ss->current_state) अणु
	हाल sdma_state_s00_hw_करोwn:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			अवरोध;
		हाल sdma_event_e30_go_running:
			/*
			 * If करोwn, but running requested (usually result
			 * of link up, then we need to start up.
			 * This can happen when hw करोwn is requested जबतक
			 * bringing the link up with traffic active on
			 * 7220, e.g.
			 */
			ss->go_s99_running = 1;
			fallthrough;	/* and start dma engine */
		हाल sdma_event_e10_go_hw_start:
			/* This reference means the state machine is started */
			sdma_get(&sde->state);
			sdma_set_state(sde,
				       sdma_state_s10_hw_start_up_halt_रुको);
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			sdma_sw_tear_करोwn(sde);
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s10_hw_start_up_halt_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			sdma_sw_tear_करोwn(sde);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			sdma_set_state(sde,
				       sdma_state_s15_hw_start_up_clean_रुको);
			sdma_start_hw_clean_up(sde);
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s15_hw_start_up_clean_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			sdma_sw_tear_करोwn(sde);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s20_idle:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			sdma_sw_tear_करोwn(sde);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			sdma_set_state(sde, sdma_state_s99_running);
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			sdma_set_state(sde, sdma_state_s50_hw_halt_रुको);
			schedule_work(&sde->err_halt_worker);
			अवरोध;
		हाल sdma_event_e70_go_idle:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
		हाल sdma_event_e80_hw_मुक्तze:
			sdma_set_state(sde, sdma_state_s80_hw_मुक्तze);
			atomic_dec(&sde->dd->sdma_unमुक्तze_count);
			wake_up_पूर्णांकerruptible(&sde->dd->sdma_unमुक्तze_wq);
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s30_sw_clean_up_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			sdma_set_state(sde, sdma_state_s40_hw_clean_up_रुको);
			sdma_start_hw_clean_up(sde);
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s40_hw_clean_up_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s50_hw_halt_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_रुको);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s60_idle_halt_रुको:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_रुको);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s80_hw_मुक्तze:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			sdma_set_state(sde, sdma_state_s82_मुक्तze_sw_clean);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s82_मुक्तze_sw_clean:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			/* notअगरy caller this engine is करोne cleaning */
			atomic_dec(&sde->dd->sdma_unमुक्तze_count);
			wake_up_पूर्णांकerruptible(&sde->dd->sdma_unमुक्तze_wq);
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			अवरोध;
		हाल sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल sdma_event_e80_hw_मुक्तze:
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			अवरोध;
		हाल sdma_event_e90_sw_halted:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल sdma_state_s99_running:
		चयन (event) अणु
		हाल sdma_event_e00_go_hw_करोwn:
			sdma_set_state(sde, sdma_state_s00_hw_करोwn);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			अवरोध;
		हाल sdma_event_e10_go_hw_start:
			अवरोध;
		हाल sdma_event_e15_hw_halt_करोne:
			अवरोध;
		हाल sdma_event_e25_hw_clean_up_करोne:
			अवरोध;
		हाल sdma_event_e30_go_running:
			अवरोध;
		हाल sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल sdma_event_e60_hw_halted:
			need_progress = 1;
			sdma_err_progress_check_schedule(sde);
			fallthrough;
		हाल sdma_event_e90_sw_halted:
			/*
			* SW initiated halt करोes not perक्रमm engines
			* progress check
			*/
			sdma_set_state(sde, sdma_state_s50_hw_halt_रुको);
			schedule_work(&sde->err_halt_worker);
			अवरोध;
		हाल sdma_event_e70_go_idle:
			sdma_set_state(sde, sdma_state_s60_idle_halt_रुको);
			अवरोध;
		हाल sdma_event_e85_link_करोwn:
			ss->go_s99_running = 0;
			fallthrough;
		हाल sdma_event_e80_hw_मुक्तze:
			sdma_set_state(sde, sdma_state_s80_hw_मुक्तze);
			atomic_dec(&sde->dd->sdma_unमुक्तze_count);
			wake_up_पूर्णांकerruptible(&sde->dd->sdma_unमुक्तze_wq);
			अवरोध;
		हाल sdma_event_e81_hw_frozen:
			अवरोध;
		हाल sdma_event_e82_hw_unमुक्तze:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	ss->last_event = event;
	अगर (need_progress)
		sdma_make_progress(sde, 0);
पूर्ण

/*
 * _extend_sdma_tx_descs() - helper to extend txreq
 *
 * This is called once the initial nominal allocation
 * of descriptors in the sdma_txreq is exhausted.
 *
 * The code will bump the allocation up to the max
 * of MAX_DESC (64) descriptors. There करोesn't seem
 * much poपूर्णांक in an पूर्णांकerim step. The last descriptor
 * is reserved क्रम coalesce buffer in order to support
 * हालs where input packet has >MAX_DESC iovecs.
 *
 */
अटल पूर्णांक _extend_sdma_tx_descs(काष्ठा hfi1_devdata *dd, काष्ठा sdma_txreq *tx)
अणु
	पूर्णांक i;

	/* Handle last descriptor */
	अगर (unlikely((tx->num_desc == (MAX_DESC - 1)))) अणु
		/* अगर tlen is 0, it is क्रम padding, release last descriptor */
		अगर (!tx->tlen) अणु
			tx->desc_limit = MAX_DESC;
		पूर्ण अन्यथा अगर (!tx->coalesce_buf) अणु
			/* allocate coalesce buffer with space क्रम padding */
			tx->coalesce_buf = kदो_स्मृति(tx->tlen + माप(u32),
						   GFP_ATOMIC);
			अगर (!tx->coalesce_buf)
				जाओ enomem;
			tx->coalesce_idx = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (unlikely(tx->num_desc == MAX_DESC))
		जाओ enomem;

	tx->descp = kदो_स्मृति_array(
			MAX_DESC,
			माप(काष्ठा sdma_desc),
			GFP_ATOMIC);
	अगर (!tx->descp)
		जाओ enomem;

	/* reserve last descriptor क्रम coalescing */
	tx->desc_limit = MAX_DESC - 1;
	/* copy ones alपढ़ोy built */
	क्रम (i = 0; i < tx->num_desc; i++)
		tx->descp[i] = tx->descs[i];
	वापस 0;
enomem:
	__sdma_txclean(dd, tx);
	वापस -ENOMEM;
पूर्ण

/*
 * ext_coal_sdma_tx_descs() - extend or coalesce sdma tx descriptors
 *
 * This is called once the initial nominal allocation of descriptors
 * in the sdma_txreq is exhausted.
 *
 * This function calls _extend_sdma_tx_descs to extend or allocate
 * coalesce buffer. If there is a allocated coalesce buffer, it will
 * copy the input packet data पूर्णांकo the coalesce buffer. It also adds
 * coalesce buffer descriptor once when whole packet is received.
 *
 * Return:
 * <0 - error
 * 0 - coalescing, करोn't populate descriptor
 * 1 - जारी with populating descriptor
 */
पूर्णांक ext_coal_sdma_tx_descs(काष्ठा hfi1_devdata *dd, काष्ठा sdma_txreq *tx,
			   पूर्णांक type, व्योम *kvaddr, काष्ठा page *page,
			   अचिन्हित दीर्घ offset, u16 len)
अणु
	पूर्णांक pad_len, rval;
	dma_addr_t addr;

	rval = _extend_sdma_tx_descs(dd, tx);
	अगर (rval) अणु
		__sdma_txclean(dd, tx);
		वापस rval;
	पूर्ण

	/* If coalesce buffer is allocated, copy data पूर्णांकo it */
	अगर (tx->coalesce_buf) अणु
		अगर (type == SDMA_MAP_NONE) अणु
			__sdma_txclean(dd, tx);
			वापस -EINVAL;
		पूर्ण

		अगर (type == SDMA_MAP_PAGE) अणु
			kvaddr = kmap(page);
			kvaddr += offset;
		पूर्ण अन्यथा अगर (WARN_ON(!kvaddr)) अणु
			__sdma_txclean(dd, tx);
			वापस -EINVAL;
		पूर्ण

		स_नकल(tx->coalesce_buf + tx->coalesce_idx, kvaddr, len);
		tx->coalesce_idx += len;
		अगर (type == SDMA_MAP_PAGE)
			kunmap(page);

		/* If there is more data, वापस */
		अगर (tx->tlen - tx->coalesce_idx)
			वापस 0;

		/* Whole packet is received; add any padding */
		pad_len = tx->packet_len & (माप(u32) - 1);
		अगर (pad_len) अणु
			pad_len = माप(u32) - pad_len;
			स_रखो(tx->coalesce_buf + tx->coalesce_idx, 0, pad_len);
			/* padding is taken care of क्रम coalescing हाल */
			tx->packet_len += pad_len;
			tx->tlen += pad_len;
		पूर्ण

		/* dma map the coalesce buffer */
		addr = dma_map_single(&dd->pcidev->dev,
				      tx->coalesce_buf,
				      tx->tlen,
				      DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(&dd->pcidev->dev, addr))) अणु
			__sdma_txclean(dd, tx);
			वापस -ENOSPC;
		पूर्ण

		/* Add descriptor क्रम coalesce buffer */
		tx->desc_limit = MAX_DESC;
		वापस _sdma_txadd_daddr(dd, SDMA_MAP_SINGLE, tx,
					 addr, tx->tlen);
	पूर्ण

	वापस 1;
पूर्ण

/* Update sdes when the lmc changes */
व्योम sdma_update_lmc(काष्ठा hfi1_devdata *dd, u64 mask, u32 lid)
अणु
	काष्ठा sdma_engine *sde;
	पूर्णांक i;
	u64 sreg;

	sreg = ((mask & SD(CHECK_SLID_MASK_MASK)) <<
		SD(CHECK_SLID_MASK_SHIFT)) |
		(((lid & mask) & SD(CHECK_SLID_VALUE_MASK)) <<
		SD(CHECK_SLID_VALUE_SHIFT));

	क्रम (i = 0; i < dd->num_sdma; i++) अणु
		hfi1_cdbg(LINKVERB, "SendDmaEngine[%d].SLID_CHECK = 0x%x",
			  i, (u32)sreg);
		sde = &dd->per_sdma[i];
		ग_लिखो_sde_csr(sde, SD(CHECK_SLID), sreg);
	पूर्ण
पूर्ण

/* tx not dword sized - pad */
पूर्णांक _pad_sdma_tx_descs(काष्ठा hfi1_devdata *dd, काष्ठा sdma_txreq *tx)
अणु
	पूर्णांक rval = 0;

	tx->num_desc++;
	अगर ((unlikely(tx->num_desc == tx->desc_limit))) अणु
		rval = _extend_sdma_tx_descs(dd, tx);
		अगर (rval) अणु
			__sdma_txclean(dd, tx);
			वापस rval;
		पूर्ण
	पूर्ण
	/* finish the one just added */
	make_tx_sdma_desc(
		tx,
		SDMA_MAP_NONE,
		dd->sdma_pad_phys,
		माप(u32) - (tx->packet_len & (माप(u32) - 1)));
	_sdma_बंद_tx(dd, tx);
	वापस rval;
पूर्ण

/*
 * Add ahg to the sdma_txreq
 *
 * The logic will consume up to 3
 * descriptors at the beginning of
 * sdma_txreq.
 */
व्योम _sdma_txreq_ahgadd(
	काष्ठा sdma_txreq *tx,
	u8 num_ahg,
	u8 ahg_entry,
	u32 *ahg,
	u8 ahg_hlen)
अणु
	u32 i, shअगरt = 0, desc = 0;
	u8 mode;

	WARN_ON_ONCE(num_ahg > 9 || (ahg_hlen & 3) || ahg_hlen == 4);
	/* compute mode */
	अगर (num_ahg == 1)
		mode = SDMA_AHG_APPLY_UPDATE1;
	अन्यथा अगर (num_ahg <= 5)
		mode = SDMA_AHG_APPLY_UPDATE2;
	अन्यथा
		mode = SDMA_AHG_APPLY_UPDATE3;
	tx->num_desc++;
	/* initialize to consumed descriptors to zero */
	चयन (mode) अणु
	हाल SDMA_AHG_APPLY_UPDATE3:
		tx->num_desc++;
		tx->descs[2].qw[0] = 0;
		tx->descs[2].qw[1] = 0;
		fallthrough;
	हाल SDMA_AHG_APPLY_UPDATE2:
		tx->num_desc++;
		tx->descs[1].qw[0] = 0;
		tx->descs[1].qw[1] = 0;
		अवरोध;
	पूर्ण
	ahg_hlen >>= 2;
	tx->descs[0].qw[1] |=
		(((u64)ahg_entry & SDMA_DESC1_HEADER_INDEX_MASK)
			<< SDMA_DESC1_HEADER_INDEX_SHIFT) |
		(((u64)ahg_hlen & SDMA_DESC1_HEADER_DWS_MASK)
			<< SDMA_DESC1_HEADER_DWS_SHIFT) |
		(((u64)mode & SDMA_DESC1_HEADER_MODE_MASK)
			<< SDMA_DESC1_HEADER_MODE_SHIFT) |
		(((u64)ahg[0] & SDMA_DESC1_HEADER_UPDATE1_MASK)
			<< SDMA_DESC1_HEADER_UPDATE1_SHIFT);
	क्रम (i = 0; i < (num_ahg - 1); i++) अणु
		अगर (!shअगरt && !(i & 2))
			desc++;
		tx->descs[desc].qw[!!(i & 2)] |=
			(((u64)ahg[i + 1])
				<< shअगरt);
		shअगरt = (shअगरt + 32) & 63;
	पूर्ण
पूर्ण

/**
 * sdma_ahg_alloc - allocate an AHG entry
 * @sde: engine to allocate from
 *
 * Return:
 * 0-31 when successful, -EOPNOTSUPP अगर AHG is not enabled,
 * -ENOSPC अगर an entry is not available
 */
पूर्णांक sdma_ahg_alloc(काष्ठा sdma_engine *sde)
अणु
	पूर्णांक nr;
	पूर्णांक oldbit;

	अगर (!sde) अणु
		trace_hfi1_ahg_allocate(sde, -EINVAL);
		वापस -EINVAL;
	पूर्ण
	जबतक (1) अणु
		nr = ffz(READ_ONCE(sde->ahg_bits));
		अगर (nr > 31) अणु
			trace_hfi1_ahg_allocate(sde, -ENOSPC);
			वापस -ENOSPC;
		पूर्ण
		oldbit = test_and_set_bit(nr, &sde->ahg_bits);
		अगर (!oldbit)
			अवरोध;
		cpu_relax();
	पूर्ण
	trace_hfi1_ahg_allocate(sde, nr);
	वापस nr;
पूर्ण

/**
 * sdma_ahg_मुक्त - मुक्त an AHG entry
 * @sde: engine to वापस AHG entry
 * @ahg_index: index to मुक्त
 *
 * This routine मुक्तs the indicate AHG entry.
 */
व्योम sdma_ahg_मुक्त(काष्ठा sdma_engine *sde, पूर्णांक ahg_index)
अणु
	अगर (!sde)
		वापस;
	trace_hfi1_ahg_deallocate(sde, ahg_index);
	अगर (ahg_index < 0 || ahg_index > 31)
		वापस;
	clear_bit(ahg_index, &sde->ahg_bits);
पूर्ण

/*
 * SPC मुक्तze handling क्रम SDMA engines.  Called when the driver knows
 * the SPC is going पूर्णांकo a मुक्तze but beक्रमe the मुक्तze is fully
 * settled.  Generally an error पूर्णांकerrupt.
 *
 * This event will pull the engine out of running so no more entries can be
 * added to the engine's queue.
 */
व्योम sdma_मुक्तze_notअगरy(काष्ठा hfi1_devdata *dd, पूर्णांक link_करोwn)
अणु
	पूर्णांक i;
	क्रमागत sdma_events event = link_करोwn ? sdma_event_e85_link_करोwn :
					     sdma_event_e80_hw_मुक्तze;

	/* set up the रुको but करो not रुको here */
	atomic_set(&dd->sdma_unमुक्तze_count, dd->num_sdma);

	/* tell all engines to stop running and रुको */
	क्रम (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i], event);

	/* sdma_मुक्तze() will रुको क्रम all engines to have stopped */
पूर्ण

/*
 * SPC मुक्तze handling क्रम SDMA engines.  Called when the driver knows
 * the SPC is fully frozen.
 */
व्योम sdma_मुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Make sure all engines have moved out of the running state beक्रमe
	 * continuing.
	 */
	ret = रुको_event_पूर्णांकerruptible(dd->sdma_unमुक्तze_wq,
				       atomic_पढ़ो(&dd->sdma_unमुक्तze_count) <=
				       0);
	/* पूर्णांकerrupted or count is negative, then unloading - just निकास */
	अगर (ret || atomic_पढ़ो(&dd->sdma_unमुक्तze_count) < 0)
		वापस;

	/* set up the count क्रम the next रुको */
	atomic_set(&dd->sdma_unमुक्तze_count, dd->num_sdma);

	/* tell all engines that the SPC is frozen, they can start cleaning */
	क्रम (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i], sdma_event_e81_hw_frozen);

	/*
	 * Wait क्रम everyone to finish software clean beक्रमe निकासing.  The
	 * software clean will पढ़ो engine CSRs, so must be completed beक्रमe
	 * the next step, which will clear the engine CSRs.
	 */
	(व्योम)रुको_event_पूर्णांकerruptible(dd->sdma_unमुक्तze_wq,
				atomic_पढ़ो(&dd->sdma_unमुक्तze_count) <= 0);
	/* no need to check results - करोne no matter what */
पूर्ण

/*
 * SPC मुक्तze handling क्रम the SDMA engines.  Called after the SPC is unfrozen.
 *
 * The SPC मुक्तze acts like a SDMA halt and a hardware clean combined.  All
 * that is left is a software clean.  We could करो it after the SPC is fully
 * frozen, but then we'd have to add another state to रुको क्रम the unमुक्तze.
 * Instead, just defer the software clean until the unमुक्तze step.
 */
व्योम sdma_unमुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	/* tell all engines start मुक्तze clean up */
	क्रम (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i],
				   sdma_event_e82_hw_unमुक्तze);
पूर्ण

/**
 * _sdma_engine_progress_schedule() - schedule progress on engine
 * @sde: sdma_engine to schedule progress
 *
 */
व्योम _sdma_engine_progress_schedule(
	काष्ठा sdma_engine *sde)
अणु
	trace_hfi1_sdma_engine_progress(sde, sde->progress_mask);
	/* assume we have selected a good cpu */
	ग_लिखो_csr(sde->dd,
		  CCE_INT_FORCE + (8 * (IS_SDMA_START / 64)),
		  sde->progress_mask);
पूर्ण
