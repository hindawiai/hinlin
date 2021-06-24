<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 **********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn66xx_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "cn23xx_vf_device.h"

काष्ठा iq_post_status अणु
	पूर्णांक status;
	पूर्णांक index;
पूर्ण;

अटल व्योम check_db_समयout(काष्ठा work_काष्ठा *work);
अटल व्योम  __check_db_समयout(काष्ठा octeon_device *oct, u64 iq_no);

अटल व्योम (*reqtype_मुक्त_fn[MAX_OCTEON_DEVICES][REQTYPE_LAST + 1]) (व्योम *);

अटल अंतरभूत पूर्णांक IQ_INSTR_MODE_64B(काष्ठा octeon_device *oct, पूर्णांक iq_no)
अणु
	काष्ठा octeon_instr_queue *iq =
	    (काष्ठा octeon_instr_queue *)oct->instr_queue[iq_no];
	वापस iq->iqcmd_64B;
पूर्ण

#घोषणा IQ_INSTR_MODE_32B(oct, iq_no)  (!IQ_INSTR_MODE_64B(oct, iq_no))

/* Define this to वापस the request status comaptible to old code */
/*#घोषणा OCTEON_USE_OLD_REQ_STATUS*/

/* Return 0 on success, 1 on failure */
पूर्णांक octeon_init_instr_queue(काष्ठा octeon_device *oct,
			    जोड़ oct_txpciq txpciq,
			    u32 num_descs)
अणु
	काष्ठा octeon_instr_queue *iq;
	काष्ठा octeon_iq_config *conf = शून्य;
	u32 iq_no = (u32)txpciq.s.q_no;
	u32 q_size;
	काष्ठा cavium_wq *db_wq;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	अगर (OCTEON_CN6XXX(oct))
		conf = &(CFG_GET_IQ_CFG(CHIP_CONF(oct, cn6xxx)));
	अन्यथा अगर (OCTEON_CN23XX_PF(oct))
		conf = &(CFG_GET_IQ_CFG(CHIP_CONF(oct, cn23xx_pf)));
	अन्यथा अगर (OCTEON_CN23XX_VF(oct))
		conf = &(CFG_GET_IQ_CFG(CHIP_CONF(oct, cn23xx_vf)));

	अगर (!conf) अणु
		dev_err(&oct->pci_dev->dev, "Unsupported Chip %x\n",
			oct->chip_id);
		वापस 1;
	पूर्ण

	q_size = (u32)conf->instr_type * num_descs;

	iq = oct->instr_queue[iq_no];

	iq->oct_dev = oct;

	iq->base_addr = lio_dma_alloc(oct, q_size, &iq->base_addr_dma);
	अगर (!iq->base_addr) अणु
		dev_err(&oct->pci_dev->dev, "Cannot allocate memory for instr queue %d\n",
			iq_no);
		वापस 1;
	पूर्ण

	iq->max_count = num_descs;

	/* Initialize a list to holds requests that have been posted to Octeon
	 * but has yet to be fetched by octeon
	 */
	iq->request_list = vzalloc_node(array_size(num_descs, माप(*iq->request_list)),
					numa_node);
	अगर (!iq->request_list)
		iq->request_list = vzalloc(array_size(num_descs, माप(*iq->request_list)));
	अगर (!iq->request_list) अणु
		lio_dma_मुक्त(oct, q_size, iq->base_addr, iq->base_addr_dma);
		dev_err(&oct->pci_dev->dev, "Alloc failed for IQ[%d] nr free list\n",
			iq_no);
		वापस 1;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "IQ[%d]: base: %p basedma: %pad count: %d\n",
		iq_no, iq->base_addr, &iq->base_addr_dma, iq->max_count);

	iq->txpciq.u64 = txpciq.u64;
	iq->fill_threshold = (u32)conf->db_min;
	iq->fill_cnt = 0;
	iq->host_ग_लिखो_index = 0;
	iq->octeon_पढ़ो_index = 0;
	iq->flush_index = 0;
	iq->last_db_समय = 0;
	iq->करो_स्वतः_flush = 1;
	iq->db_समयout = (u32)conf->db_समयout;
	atomic_set(&iq->instr_pending, 0);
	iq->pkts_processed = 0;

	/* Initialize the spinlock क्रम this inकाष्ठाion queue */
	spin_lock_init(&iq->lock);
	अगर (iq_no == 0) अणु
		iq->allow_soft_cmds = true;
		spin_lock_init(&iq->post_lock);
	पूर्ण अन्यथा अणु
		iq->allow_soft_cmds = false;
	पूर्ण

	spin_lock_init(&iq->iq_flush_running_lock);

	oct->io_qmask.iq |= BIT_ULL(iq_no);

	/* Set the 32B/64B mode क्रम each input queue */
	oct->io_qmask.iq64B |= ((conf->instr_type == 64) << iq_no);
	iq->iqcmd_64B = (conf->instr_type == 64);

	oct->fn_list.setup_iq_regs(oct, iq_no);

	oct->check_db_wq[iq_no].wq = alloc_workqueue("check_iq_db",
						     WQ_MEM_RECLAIM,
						     0);
	अगर (!oct->check_db_wq[iq_no].wq) अणु
		vमुक्त(iq->request_list);
		iq->request_list = शून्य;
		lio_dma_मुक्त(oct, q_size, iq->base_addr, iq->base_addr_dma);
		dev_err(&oct->pci_dev->dev, "check db wq create failed for iq %d\n",
			iq_no);
		वापस 1;
	पूर्ण

	db_wq = &oct->check_db_wq[iq_no];

	INIT_DELAYED_WORK(&db_wq->wk.work, check_db_समयout);
	db_wq->wk.ctxptr = oct;
	db_wq->wk.ctxul = iq_no;
	queue_delayed_work(db_wq->wq, &db_wq->wk.work, msecs_to_jअगरfies(1));

	वापस 0;
पूर्ण

पूर्णांक octeon_delete_instr_queue(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	u64 desc_size = 0, q_size;
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_no];

	cancel_delayed_work_sync(&oct->check_db_wq[iq_no].wk.work);
	destroy_workqueue(oct->check_db_wq[iq_no].wq);

	अगर (OCTEON_CN6XXX(oct))
		desc_size =
		    CFG_GET_IQ_INSTR_TYPE(CHIP_CONF(oct, cn6xxx));
	अन्यथा अगर (OCTEON_CN23XX_PF(oct))
		desc_size =
		    CFG_GET_IQ_INSTR_TYPE(CHIP_CONF(oct, cn23xx_pf));
	अन्यथा अगर (OCTEON_CN23XX_VF(oct))
		desc_size =
		    CFG_GET_IQ_INSTR_TYPE(CHIP_CONF(oct, cn23xx_vf));

	vमुक्त(iq->request_list);

	अगर (iq->base_addr) अणु
		q_size = iq->max_count * desc_size;
		lio_dma_मुक्त(oct, (u32)q_size, iq->base_addr,
			     iq->base_addr_dma);
		oct->io_qmask.iq &= ~(1ULL << iq_no);
		vमुक्त(oct->instr_queue[iq_no]);
		oct->instr_queue[iq_no] = शून्य;
		oct->num_iqs--;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* Return 0 on success, 1 on failure */
पूर्णांक octeon_setup_iq(काष्ठा octeon_device *oct,
		    पूर्णांक अगरidx,
		    पूर्णांक q_index,
		    जोड़ oct_txpciq txpciq,
		    u32 num_descs,
		    व्योम *app_ctx)
अणु
	u32 iq_no = (u32)txpciq.s.q_no;
	पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

	अगर (oct->instr_queue[iq_no]) अणु
		dev_dbg(&oct->pci_dev->dev, "IQ is in use. Cannot create the IQ: %d again\n",
			iq_no);
		oct->instr_queue[iq_no]->txpciq.u64 = txpciq.u64;
		oct->instr_queue[iq_no]->app_ctx = app_ctx;
		वापस 0;
	पूर्ण
	oct->instr_queue[iq_no] =
	    vzalloc_node(माप(काष्ठा octeon_instr_queue), numa_node);
	अगर (!oct->instr_queue[iq_no])
		oct->instr_queue[iq_no] =
		    vzalloc(माप(काष्ठा octeon_instr_queue));
	अगर (!oct->instr_queue[iq_no])
		वापस 1;


	oct->instr_queue[iq_no]->q_index = q_index;
	oct->instr_queue[iq_no]->app_ctx = app_ctx;
	oct->instr_queue[iq_no]->अगरidx = अगरidx;

	अगर (octeon_init_instr_queue(oct, txpciq, num_descs)) अणु
		vमुक्त(oct->instr_queue[iq_no]);
		oct->instr_queue[iq_no] = शून्य;
		वापस 1;
	पूर्ण

	oct->num_iqs++;
	अगर (oct->fn_list.enable_io_queues(oct)) अणु
		octeon_delete_instr_queue(oct, iq_no);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक lio_रुको_क्रम_instr_fetch(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i, retry = 1000, pending, instr_cnt = 0;

	करो अणु
		instr_cnt = 0;

		क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
			अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
				जारी;
			pending =
			    atomic_पढ़ो(&oct->instr_queue[i]->instr_pending);
			अगर (pending)
				__check_db_समयout(oct, i);
			instr_cnt += pending;
		पूर्ण

		अगर (instr_cnt == 0)
			अवरोध;

		schedule_समयout_unपूर्णांकerruptible(1);

	पूर्ण जबतक (retry-- && instr_cnt);

	वापस instr_cnt;
पूर्ण

अटल अंतरभूत व्योम
ring_करोorbell(काष्ठा octeon_device *oct, काष्ठा octeon_instr_queue *iq)
अणु
	अगर (atomic_पढ़ो(&oct->status) == OCT_DEV_RUNNING) अणु
		ग_लिखोl(iq->fill_cnt, iq->करोorbell_reg);
		/* make sure करोorbell ग_लिखो goes through */
		iq->fill_cnt = 0;
		iq->last_db_समय = jअगरfies;
		वापस;
	पूर्ण
पूर्ण

व्योम
octeon_ring_करोorbell_locked(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	काष्ठा octeon_instr_queue *iq;

	iq = oct->instr_queue[iq_no];
	spin_lock(&iq->post_lock);
	अगर (iq->fill_cnt)
		ring_करोorbell(oct, iq);
	spin_unlock(&iq->post_lock);
पूर्ण

अटल अंतरभूत व्योम __copy_cmd_पूर्णांकo_iq(काष्ठा octeon_instr_queue *iq,
				      u8 *cmd)
अणु
	u8 *iqptr, cmdsize;

	cmdsize = ((iq->iqcmd_64B) ? 64 : 32);
	iqptr = iq->base_addr + (cmdsize * iq->host_ग_लिखो_index);

	स_नकल(iqptr, cmd, cmdsize);
पूर्ण

अटल अंतरभूत काष्ठा iq_post_status
__post_command2(काष्ठा octeon_instr_queue *iq, u8 *cmd)
अणु
	काष्ठा iq_post_status st;

	st.status = IQ_SEND_OK;

	/* This ensures that the पढ़ो index करोes not wrap around to the same
	 * position अगर queue माला_लो full beक्रमe Octeon could fetch any instr.
	 */
	अगर (atomic_पढ़ो(&iq->instr_pending) >= (s32)(iq->max_count - 1)) अणु
		st.status = IQ_SEND_FAILED;
		st.index = -1;
		वापस st;
	पूर्ण

	अगर (atomic_पढ़ो(&iq->instr_pending) >= (s32)(iq->max_count - 2))
		st.status = IQ_SEND_STOP;

	__copy_cmd_पूर्णांकo_iq(iq, cmd);

	/* "index" is वापसed, host_ग_लिखो_index is modअगरied. */
	st.index = iq->host_ग_लिखो_index;
	iq->host_ग_लिखो_index = incr_index(iq->host_ग_लिखो_index, 1,
					  iq->max_count);
	iq->fill_cnt++;

	/* Flush the command पूर्णांकo memory. We need to be sure the data is in
	 * memory beक्रमe indicating that the inकाष्ठाion is pending.
	 */
	wmb();

	atomic_inc(&iq->instr_pending);

	वापस st;
पूर्ण

पूर्णांक
octeon_रेजिस्टर_reqtype_मुक्त_fn(काष्ठा octeon_device *oct, पूर्णांक reqtype,
				व्योम (*fn)(व्योम *))
अणु
	अगर (reqtype > REQTYPE_LAST) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid reqtype: %d\n",
			__func__, reqtype);
		वापस -EINVAL;
	पूर्ण

	reqtype_मुक्त_fn[oct->octeon_id][reqtype] = fn;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
__add_to_request_list(काष्ठा octeon_instr_queue *iq,
		      पूर्णांक idx, व्योम *buf, पूर्णांक reqtype)
अणु
	iq->request_list[idx].buf = buf;
	iq->request_list[idx].reqtype = reqtype;
पूर्ण

/* Can only run in process context */
पूर्णांक
lio_process_iq_request_list(काष्ठा octeon_device *oct,
			    काष्ठा octeon_instr_queue *iq, u32 napi_budget)
अणु
	काष्ठा cavium_wq *cwq = &oct->dma_comp_wq;
	पूर्णांक reqtype;
	व्योम *buf;
	u32 old = iq->flush_index;
	u32 inst_count = 0;
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	काष्ठा octeon_soft_command *sc;
	अचिन्हित दीर्घ flags;

	जबतक (old != iq->octeon_पढ़ो_index) अणु
		reqtype = iq->request_list[old].reqtype;
		buf     = iq->request_list[old].buf;

		अगर (reqtype == REQTYPE_NONE)
			जाओ skip_this;

		octeon_update_tx_completion_counters(buf, reqtype, &pkts_compl,
						     &bytes_compl);

		चयन (reqtype) अणु
		हाल REQTYPE_NORESP_NET:
		हाल REQTYPE_NORESP_NET_SG:
		हाल REQTYPE_RESP_NET_SG:
			reqtype_मुक्त_fn[oct->octeon_id][reqtype](buf);
			अवरोध;
		हाल REQTYPE_RESP_NET:
		हाल REQTYPE_SOFT_COMMAND:
			sc = buf;
			/* We're expecting a response from Octeon.
			 * It's up to lio_process_ordered_list() to
			 * process  sc. Add sc to the ordered soft
			 * command response list because we expect
			 * a response from Octeon.
			 */
			spin_lock_irqsave(&oct->response_list
					  [OCTEON_ORDERED_SC_LIST].lock, flags);
			atomic_inc(&oct->response_list
				   [OCTEON_ORDERED_SC_LIST].pending_req_count);
			list_add_tail(&sc->node, &oct->response_list
				[OCTEON_ORDERED_SC_LIST].head);
			spin_unlock_irqrestore(&oct->response_list
					       [OCTEON_ORDERED_SC_LIST].lock,
					       flags);
			अवरोध;
		शेष:
			dev_err(&oct->pci_dev->dev,
				"%s Unknown reqtype: %d buf: %p at idx %d\n",
				__func__, reqtype, buf, old);
		पूर्ण

		iq->request_list[old].buf = शून्य;
		iq->request_list[old].reqtype = 0;

 skip_this:
		inst_count++;
		old = incr_index(old, 1, iq->max_count);

		अगर ((napi_budget) && (inst_count >= napi_budget))
			अवरोध;
	पूर्ण
	अगर (bytes_compl)
		octeon_report_tx_completion_to_bql(iq->app_ctx, pkts_compl,
						   bytes_compl);
	iq->flush_index = old;

	अगर (atomic_पढ़ो(&oct->response_list
			[OCTEON_ORDERED_SC_LIST].pending_req_count))
		queue_work(cwq->wq, &cwq->wk.work.work);

	वापस inst_count;
पूर्ण

/* Can only be called from process context */
पूर्णांक
octeon_flush_iq(काष्ठा octeon_device *oct, काष्ठा octeon_instr_queue *iq,
		u32 napi_budget)
अणु
	u32 inst_processed = 0;
	u32 tot_inst_processed = 0;
	पूर्णांक tx_करोne = 1;

	अगर (!spin_trylock(&iq->iq_flush_running_lock))
		वापस tx_करोne;

	spin_lock_bh(&iq->lock);

	iq->octeon_पढ़ो_index = oct->fn_list.update_iq_पढ़ो_idx(iq);

	करो अणु
		/* Process any outstanding IQ packets. */
		अगर (iq->flush_index == iq->octeon_पढ़ो_index)
			अवरोध;

		अगर (napi_budget)
			inst_processed =
				lio_process_iq_request_list(oct, iq,
							    napi_budget -
							    tot_inst_processed);
		अन्यथा
			inst_processed =
				lio_process_iq_request_list(oct, iq, 0);

		अगर (inst_processed) अणु
			iq->pkts_processed += inst_processed;
			atomic_sub(inst_processed, &iq->instr_pending);
			iq->stats.instr_processed += inst_processed;
		पूर्ण

		tot_inst_processed += inst_processed;
	पूर्ण जबतक (tot_inst_processed < napi_budget);

	अगर (napi_budget && (tot_inst_processed >= napi_budget))
		tx_करोne = 0;

	iq->last_db_समय = jअगरfies;

	spin_unlock_bh(&iq->lock);

	spin_unlock(&iq->iq_flush_running_lock);

	वापस tx_करोne;
पूर्ण

/* Process inकाष्ठाion queue after समयout.
 * This routine माला_लो called from a workqueue or when removing the module.
 */
अटल व्योम __check_db_समयout(काष्ठा octeon_device *oct, u64 iq_no)
अणु
	काष्ठा octeon_instr_queue *iq;
	u64 next_समय;

	अगर (!oct)
		वापस;

	iq = oct->instr_queue[iq_no];
	अगर (!iq)
		वापस;

	/* वापस immediately, अगर no work pending */
	अगर (!atomic_पढ़ो(&iq->instr_pending))
		वापस;
	/* If jअगरfies - last_db_समय < db_समयout करो nothing  */
	next_समय = iq->last_db_समय + iq->db_समयout;
	अगर (!समय_after(jअगरfies, (अचिन्हित दीर्घ)next_समय))
		वापस;
	iq->last_db_समय = jअगरfies;

	/* Flush the inकाष्ठाion queue */
	octeon_flush_iq(oct, iq, 0);

	lio_enable_irq(शून्य, iq);
पूर्ण

/* Called by the Poll thपढ़ो at regular पूर्णांकervals to check the inकाष्ठाion
 * queue क्रम commands to be posted and क्रम commands that were fetched by Octeon.
 */
अटल व्योम check_db_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)wk->ctxptr;
	u64 iq_no = wk->ctxul;
	काष्ठा cavium_wq *db_wq = &oct->check_db_wq[iq_no];
	u32 delay = 10;

	__check_db_समयout(oct, iq_no);
	queue_delayed_work(db_wq->wq, &db_wq->wk.work, msecs_to_jअगरfies(delay));
पूर्ण

पूर्णांक
octeon_send_command(काष्ठा octeon_device *oct, u32 iq_no,
		    u32 क्रमce_db, व्योम *cmd, व्योम *buf,
		    u32 datasize, u32 reqtype)
अणु
	पूर्णांक xmit_stopped;
	काष्ठा iq_post_status st;
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_no];

	/* Get the lock and prevent other tasks and tx पूर्णांकerrupt handler from
	 * running.
	 */
	अगर (iq->allow_soft_cmds)
		spin_lock_bh(&iq->post_lock);

	st = __post_command2(iq, cmd);

	अगर (st.status != IQ_SEND_FAILED) अणु
		xmit_stopped = octeon_report_sent_bytes_to_bql(buf, reqtype);
		__add_to_request_list(iq, st.index, buf, reqtype);
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, bytes_sent, datasize);
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_posted, 1);

		अगर (iq->fill_cnt >= MAX_OCTEON_FILL_COUNT || क्रमce_db ||
		    xmit_stopped || st.status == IQ_SEND_STOP)
			ring_करोorbell(oct, iq);
	पूर्ण अन्यथा अणु
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_dropped, 1);
	पूर्ण

	अगर (iq->allow_soft_cmds)
		spin_unlock_bh(&iq->post_lock);

	/* This is only करोne here to expedite packets being flushed
	 * क्रम हालs where there are no IQ completion पूर्णांकerrupts.
	 */

	वापस st.status;
पूर्ण

व्योम
octeon_prepare_soft_command(काष्ठा octeon_device *oct,
			    काष्ठा octeon_soft_command *sc,
			    u8 opcode,
			    u8 subcode,
			    u32 irh_ossp,
			    u64 ossp0,
			    u64 ossp1)
अणु
	काष्ठा octeon_config *oct_cfg;
	काष्ठा octeon_instr_ih2 *ih2;
	काष्ठा octeon_instr_ih3 *ih3;
	काष्ठा octeon_instr_pki_ih3 *pki_ih3;
	काष्ठा octeon_instr_irh *irh;
	काष्ठा octeon_instr_rdp *rdp;

	WARN_ON(opcode > 15);
	WARN_ON(subcode > 127);

	oct_cfg = octeon_get_conf(oct);

	अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) अणु
		ih3 = (काष्ठा octeon_instr_ih3 *)&sc->cmd.cmd3.ih3;

		ih3->pkind = oct->instr_queue[sc->iq_no]->txpciq.s.pkind;

		pki_ih3 = (काष्ठा octeon_instr_pki_ih3 *)&sc->cmd.cmd3.pki_ih3;

		pki_ih3->w           = 1;
		pki_ih3->raw         = 1;
		pki_ih3->utag        = 1;
		pki_ih3->uqpg        =
			oct->instr_queue[sc->iq_no]->txpciq.s.use_qpg;
		pki_ih3->utt         = 1;
		pki_ih3->tag     = LIO_CONTROL;
		pki_ih3->tagtype = ATOMIC_TAG;
		pki_ih3->qpg         =
			oct->instr_queue[sc->iq_no]->txpciq.s.ctrl_qpg;

		pki_ih3->pm          = 0x7;
		pki_ih3->sl          = 8;

		अगर (sc->datasize)
			ih3->dlengsz = sc->datasize;

		irh            = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd3.irh;
		irh->opcode    = opcode;
		irh->subcode   = subcode;

		/* opcode/subcode specअगरic parameters (ossp) */
		irh->ossp       = irh_ossp;
		sc->cmd.cmd3.ossp[0] = ossp0;
		sc->cmd.cmd3.ossp[1] = ossp1;

		अगर (sc->rdatasize) अणु
			rdp = (काष्ठा octeon_instr_rdp *)&sc->cmd.cmd3.rdp;
			rdp->pcie_port = oct->pcie_port;
			rdp->rlen      = sc->rdatasize;

			irh->rflag =  1;
			/*PKI IH3*/
			/* pki_ih3 irh+ossp[0]+ossp[1]+rdp+rptr = 48 bytes */
			ih3->fsz    = LIO_SOFTCMDRESP_IH3;
		पूर्ण अन्यथा अणु
			irh->rflag =  0;
			/*PKI IH3*/
			/* pki_h3 + irh + ossp[0] + ossp[1] = 32 bytes */
			ih3->fsz    = LIO_PCICMD_O3;
		पूर्ण

	पूर्ण अन्यथा अणु
		ih2          = (काष्ठा octeon_instr_ih2 *)&sc->cmd.cmd2.ih2;
		ih2->tagtype = ATOMIC_TAG;
		ih2->tag     = LIO_CONTROL;
		ih2->raw     = 1;
		ih2->grp     = CFG_GET_CTRL_Q_GRP(oct_cfg);

		अगर (sc->datasize) अणु
			ih2->dlengsz = sc->datasize;
			ih2->rs = 1;
		पूर्ण

		irh            = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd2.irh;
		irh->opcode    = opcode;
		irh->subcode   = subcode;

		/* opcode/subcode specअगरic parameters (ossp) */
		irh->ossp       = irh_ossp;
		sc->cmd.cmd2.ossp[0] = ossp0;
		sc->cmd.cmd2.ossp[1] = ossp1;

		अगर (sc->rdatasize) अणु
			rdp = (काष्ठा octeon_instr_rdp *)&sc->cmd.cmd2.rdp;
			rdp->pcie_port = oct->pcie_port;
			rdp->rlen      = sc->rdatasize;

			irh->rflag =  1;
			/* irh+ossp[0]+ossp[1]+rdp+rptr = 40 bytes */
			ih2->fsz   = LIO_SOFTCMDRESP_IH2;
		पूर्ण अन्यथा अणु
			irh->rflag =  0;
			/* irh + ossp[0] + ossp[1] = 24 bytes */
			ih2->fsz   = LIO_PCICMD_O2;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक octeon_send_soft_command(काष्ठा octeon_device *oct,
			     काष्ठा octeon_soft_command *sc)
अणु
	काष्ठा octeon_instr_queue *iq;
	काष्ठा octeon_instr_ih2 *ih2;
	काष्ठा octeon_instr_ih3 *ih3;
	काष्ठा octeon_instr_irh *irh;
	u32 len;

	iq = oct->instr_queue[sc->iq_no];
	अगर (!iq->allow_soft_cmds) अणु
		dev_err(&oct->pci_dev->dev, "Soft commands are not allowed on Queue %d\n",
			sc->iq_no);
		INCR_INSTRQUEUE_PKT_COUNT(oct, sc->iq_no, instr_dropped, 1);
		वापस IQ_SEND_FAILED;
	पूर्ण

	अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) अणु
		ih3 =  (काष्ठा octeon_instr_ih3 *)&sc->cmd.cmd3.ih3;
		अगर (ih3->dlengsz) अणु
			WARN_ON(!sc->dmadptr);
			sc->cmd.cmd3.dptr = sc->dmadptr;
		पूर्ण
		irh = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd3.irh;
		अगर (irh->rflag) अणु
			WARN_ON(!sc->dmarptr);
			WARN_ON(!sc->status_word);
			*sc->status_word = COMPLETION_WORD_INIT;
			sc->cmd.cmd3.rptr = sc->dmarptr;
		पूर्ण
		len = (u32)ih3->dlengsz;
	पूर्ण अन्यथा अणु
		ih2 = (काष्ठा octeon_instr_ih2 *)&sc->cmd.cmd2.ih2;
		अगर (ih2->dlengsz) अणु
			WARN_ON(!sc->dmadptr);
			sc->cmd.cmd2.dptr = sc->dmadptr;
		पूर्ण
		irh = (काष्ठा octeon_instr_irh *)&sc->cmd.cmd2.irh;
		अगर (irh->rflag) अणु
			WARN_ON(!sc->dmarptr);
			WARN_ON(!sc->status_word);
			*sc->status_word = COMPLETION_WORD_INIT;
			sc->cmd.cmd2.rptr = sc->dmarptr;
		पूर्ण
		len = (u32)ih2->dlengsz;
	पूर्ण

	sc->expiry_समय = jअगरfies + msecs_to_jअगरfies(LIO_SC_MAX_TMO_MS);

	वापस (octeon_send_command(oct, sc->iq_no, 1, &sc->cmd, sc,
				    len, REQTYPE_SOFT_COMMAND));
पूर्ण

पूर्णांक octeon_setup_sc_buffer_pool(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i;
	u64 dma_addr;
	काष्ठा octeon_soft_command *sc;

	INIT_LIST_HEAD(&oct->sc_buf_pool.head);
	spin_lock_init(&oct->sc_buf_pool.lock);
	atomic_set(&oct->sc_buf_pool.alloc_buf_count, 0);

	क्रम (i = 0; i < MAX_SOFT_COMMAND_BUFFERS; i++) अणु
		sc = (काष्ठा octeon_soft_command *)
			lio_dma_alloc(oct,
				      SOFT_COMMAND_BUFFER_SIZE,
					  (dma_addr_t *)&dma_addr);
		अगर (!sc) अणु
			octeon_मुक्त_sc_buffer_pool(oct);
			वापस 1;
		पूर्ण

		sc->dma_addr = dma_addr;
		sc->size = SOFT_COMMAND_BUFFER_SIZE;

		list_add_tail(&sc->node, &oct->sc_buf_pool.head);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक octeon_मुक्त_sc_करोne_list(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_response_list *करोne_sc_list, *zombie_sc_list;
	काष्ठा octeon_soft_command *sc;
	काष्ठा list_head *पंचांगp, *पंचांगp2;
	spinlock_t *sc_lists_lock; /* lock क्रम response_list */

	करोne_sc_list = &oct->response_list[OCTEON_DONE_SC_LIST];
	zombie_sc_list = &oct->response_list[OCTEON_ZOMBIE_SC_LIST];

	अगर (!atomic_पढ़ो(&करोne_sc_list->pending_req_count))
		वापस 0;

	sc_lists_lock = &oct->response_list[OCTEON_ORDERED_SC_LIST].lock;

	spin_lock_bh(sc_lists_lock);

	list_क्रम_each_safe(पंचांगp, पंचांगp2, &करोne_sc_list->head) अणु
		sc = list_entry(पंचांगp, काष्ठा octeon_soft_command, node);

		अगर (READ_ONCE(sc->caller_is_करोne)) अणु
			list_del(&sc->node);
			atomic_dec(&करोne_sc_list->pending_req_count);

			अगर (*sc->status_word == COMPLETION_WORD_INIT) अणु
				/* समयout; move sc to zombie list */
				list_add_tail(&sc->node, &zombie_sc_list->head);
				atomic_inc(&zombie_sc_list->pending_req_count);
			पूर्ण अन्यथा अणु
				octeon_मुक्त_soft_command(oct, sc);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(sc_lists_lock);

	वापस 0;
पूर्ण

पूर्णांक octeon_मुक्त_sc_zombie_list(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_response_list *zombie_sc_list;
	काष्ठा octeon_soft_command *sc;
	काष्ठा list_head *पंचांगp, *पंचांगp2;
	spinlock_t *sc_lists_lock; /* lock क्रम response_list */

	zombie_sc_list = &oct->response_list[OCTEON_ZOMBIE_SC_LIST];
	sc_lists_lock = &oct->response_list[OCTEON_ORDERED_SC_LIST].lock;

	spin_lock_bh(sc_lists_lock);

	list_क्रम_each_safe(पंचांगp, पंचांगp2, &zombie_sc_list->head) अणु
		list_del(पंचांगp);
		atomic_dec(&zombie_sc_list->pending_req_count);
		sc = list_entry(पंचांगp, काष्ठा octeon_soft_command, node);
		octeon_मुक्त_soft_command(oct, sc);
	पूर्ण

	spin_unlock_bh(sc_lists_lock);

	वापस 0;
पूर्ण

पूर्णांक octeon_मुक्त_sc_buffer_pool(काष्ठा octeon_device *oct)
अणु
	काष्ठा list_head *पंचांगp, *पंचांगp2;
	काष्ठा octeon_soft_command *sc;

	octeon_मुक्त_sc_zombie_list(oct);

	spin_lock_bh(&oct->sc_buf_pool.lock);

	list_क्रम_each_safe(पंचांगp, पंचांगp2, &oct->sc_buf_pool.head) अणु
		list_del(पंचांगp);

		sc = (काष्ठा octeon_soft_command *)पंचांगp;

		lio_dma_मुक्त(oct, sc->size, sc, sc->dma_addr);
	पूर्ण

	INIT_LIST_HEAD(&oct->sc_buf_pool.head);

	spin_unlock_bh(&oct->sc_buf_pool.lock);

	वापस 0;
पूर्ण

काष्ठा octeon_soft_command *octeon_alloc_soft_command(काष्ठा octeon_device *oct,
						      u32 datasize,
						      u32 rdatasize,
						      u32 ctxsize)
अणु
	u64 dma_addr;
	u32 size;
	u32 offset = माप(काष्ठा octeon_soft_command);
	काष्ठा octeon_soft_command *sc = शून्य;
	काष्ठा list_head *पंचांगp;

	अगर (!rdatasize)
		rdatasize = 16;

	WARN_ON((offset + datasize + rdatasize + ctxsize) >
	       SOFT_COMMAND_BUFFER_SIZE);

	spin_lock_bh(&oct->sc_buf_pool.lock);

	अगर (list_empty(&oct->sc_buf_pool.head)) अणु
		spin_unlock_bh(&oct->sc_buf_pool.lock);
		वापस शून्य;
	पूर्ण

	list_क्रम_each(पंचांगp, &oct->sc_buf_pool.head)
		अवरोध;

	list_del(पंचांगp);

	atomic_inc(&oct->sc_buf_pool.alloc_buf_count);

	spin_unlock_bh(&oct->sc_buf_pool.lock);

	sc = (काष्ठा octeon_soft_command *)पंचांगp;

	dma_addr = sc->dma_addr;
	size = sc->size;

	स_रखो(sc, 0, sc->size);

	sc->dma_addr = dma_addr;
	sc->size = size;

	अगर (ctxsize) अणु
		sc->ctxptr = (u8 *)sc + offset;
		sc->ctxsize = ctxsize;
	पूर्ण

	/* Start data at 128 byte boundary */
	offset = (offset + ctxsize + 127) & 0xffffff80;

	अगर (datasize) अणु
		sc->virtdptr = (u8 *)sc + offset;
		sc->dmadptr = dma_addr + offset;
		sc->datasize = datasize;
	पूर्ण

	/* Start rdata at 128 byte boundary */
	offset = (offset + datasize + 127) & 0xffffff80;

	अगर (rdatasize) अणु
		WARN_ON(rdatasize < 16);
		sc->virtrptr = (u8 *)sc + offset;
		sc->dmarptr = dma_addr + offset;
		sc->rdatasize = rdatasize;
		sc->status_word = (u64 *)((u8 *)(sc->virtrptr) + rdatasize - 8);
	पूर्ण

	वापस sc;
पूर्ण

व्योम octeon_मुक्त_soft_command(काष्ठा octeon_device *oct,
			      काष्ठा octeon_soft_command *sc)
अणु
	spin_lock_bh(&oct->sc_buf_pool.lock);

	list_add_tail(&sc->node, &oct->sc_buf_pool.head);

	atomic_dec(&oct->sc_buf_pool.alloc_buf_count);

	spin_unlock_bh(&oct->sc_buf_pool.lock);
पूर्ण
