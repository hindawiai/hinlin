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
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"

अटल व्योम oct_poll_req_completion(काष्ठा work_काष्ठा *work);

पूर्णांक octeon_setup_response_list(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा cavium_wq *cwq;

	क्रम (i = 0; i < MAX_RESPONSE_LISTS; i++) अणु
		INIT_LIST_HEAD(&oct->response_list[i].head);
		spin_lock_init(&oct->response_list[i].lock);
		atomic_set(&oct->response_list[i].pending_req_count, 0);
	पूर्ण
	spin_lock_init(&oct->cmd_resp_wqlock);

	oct->dma_comp_wq.wq = alloc_workqueue("dma-comp", WQ_MEM_RECLAIM, 0);
	अगर (!oct->dma_comp_wq.wq) अणु
		dev_err(&oct->pci_dev->dev, "failed to create wq thread\n");
		वापस -ENOMEM;
	पूर्ण

	cwq = &oct->dma_comp_wq;
	INIT_DELAYED_WORK(&cwq->wk.work, oct_poll_req_completion);
	cwq->wk.ctxptr = oct;
	oct->cmd_resp_state = OCT_DRV_ONLINE;

	वापस ret;
पूर्ण

व्योम octeon_delete_response_list(काष्ठा octeon_device *oct)
अणु
	cancel_delayed_work_sync(&oct->dma_comp_wq.wk.work);
	destroy_workqueue(oct->dma_comp_wq.wq);
पूर्ण

पूर्णांक lio_process_ordered_list(काष्ठा octeon_device *octeon_dev,
			     u32 क्रमce_quit)
अणु
	काष्ठा octeon_response_list *ordered_sc_list;
	काष्ठा octeon_soft_command *sc;
	पूर्णांक request_complete = 0;
	पूर्णांक resp_to_process = MAX_ORD_REQS_TO_PROCESS;
	u32 status;
	u64 status64;

	octeon_मुक्त_sc_करोne_list(octeon_dev);

	ordered_sc_list = &octeon_dev->response_list[OCTEON_ORDERED_SC_LIST];

	करो अणु
		spin_lock_bh(&ordered_sc_list->lock);

		अगर (list_empty(&ordered_sc_list->head)) अणु
			spin_unlock_bh(&ordered_sc_list->lock);
			वापस 1;
		पूर्ण

		sc = list_first_entry(&ordered_sc_list->head,
				      काष्ठा octeon_soft_command, node);

		status = OCTEON_REQUEST_PENDING;

		/* check अगर octeon has finished DMA'ing a response
		 * to where rptr is poपूर्णांकing to
		 */
		status64 = *sc->status_word;

		अगर (status64 != COMPLETION_WORD_INIT) अणु
			/* This logic ensures that all 64b have been written.
			 * 1. check byte 0 क्रम non-FF
			 * 2. अगर non-FF, then swap result from BE to host order
			 * 3. check byte 7 (swapped to 0) क्रम non-FF
			 * 4. अगर non-FF, use the low 32-bit status code
			 * 5. अगर either byte 0 or byte 7 is FF, करोn't use status
			 */
			अगर ((status64 & 0xff) != 0xff) अणु
				octeon_swap_8B_data(&status64, 1);
				अगर (((status64 & 0xff) != 0xff)) अणु
					/* retrieve 16-bit firmware status */
					status = (u32)(status64 & 0xffffULL);
					अगर (status) अणु
						status =
						  FIRMWARE_STATUS_CODE(status);
					पूर्ण अन्यथा अणु
						/* i.e. no error */
						status = OCTEON_REQUEST_DONE;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (unlikely(क्रमce_quit) || (sc->expiry_समय &&
			समय_after(jअगरfies, (अचिन्हित दीर्घ)sc->expiry_समय))) अणु
			काष्ठा octeon_instr_irh *irh =
				(काष्ठा octeon_instr_irh *)&sc->cmd.cmd3.irh;

			dev_err(&octeon_dev->pci_dev->dev, "%s: ", __func__);
			dev_err(&octeon_dev->pci_dev->dev,
				"cmd %x/%x/%llx/%llx failed, ",
				irh->opcode, irh->subcode,
				sc->cmd.cmd3.ossp[0], sc->cmd.cmd3.ossp[1]);
			dev_err(&octeon_dev->pci_dev->dev,
				"timeout (%ld, %ld)\n",
				(दीर्घ)jअगरfies, (दीर्घ)sc->expiry_समय);
			status = OCTEON_REQUEST_TIMEOUT;
		पूर्ण

		अगर (status != OCTEON_REQUEST_PENDING) अणु
			sc->sc_status = status;

			/* we have received a response or we have समयd out */
			/* हटाओ node from linked list */
			list_del(&sc->node);
			atomic_dec(&octeon_dev->response_list
				   [OCTEON_ORDERED_SC_LIST].
				   pending_req_count);

			अगर (!sc->callback) अणु
				atomic_inc(&octeon_dev->response_list
					   [OCTEON_DONE_SC_LIST].
					   pending_req_count);
				list_add_tail(&sc->node,
					      &octeon_dev->response_list
					      [OCTEON_DONE_SC_LIST].head);

				अगर (unlikely(READ_ONCE(sc->caller_is_करोne))) अणु
					/* caller करोes not रुको क्रम response
					 * from firmware
					 */
					अगर (status != OCTEON_REQUEST_DONE) अणु
						काष्ठा octeon_instr_irh *irh;

						irh =
						    (काष्ठा octeon_instr_irh *)
						    &sc->cmd.cmd3.irh;
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "%s: sc failed: opcode=%x, ",
						    __func__, irh->opcode);
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "subcode=%x, ossp[0]=%llx, ",
						    irh->subcode,
						    sc->cmd.cmd3.ossp[0]);
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "ossp[1]=%llx, status=%d\n",
						    sc->cmd.cmd3.ossp[1],
						    status);
					पूर्ण
				पूर्ण अन्यथा अणु
					complete(&sc->complete);
				पूर्ण

				spin_unlock_bh(&ordered_sc_list->lock);
			पूर्ण अन्यथा अणु
				/* sc with callback function */
				अगर (status == OCTEON_REQUEST_TIMEOUT) अणु
					atomic_inc(&octeon_dev->response_list
						   [OCTEON_ZOMBIE_SC_LIST].
						   pending_req_count);
					list_add_tail(&sc->node,
						      &octeon_dev->response_list
						      [OCTEON_ZOMBIE_SC_LIST].
						      head);
				पूर्ण

				spin_unlock_bh(&ordered_sc_list->lock);

				sc->callback(octeon_dev, status,
					     sc->callback_arg);
				/* sc is मुक्तd by caller */
			पूर्ण

			request_complete++;

		पूर्ण अन्यथा अणु
			/* no response yet */
			request_complete = 0;
			spin_unlock_bh
			    (&ordered_sc_list->lock);
		पूर्ण

		/* If we hit the Max Ordered requests to process every loop,
		 * we quit
		 * and let this function be invoked the next समय the poll
		 * thपढ़ो runs
		 * to process the reमुख्यing requests. This function can take up
		 * the entire CPU अगर there is no upper limit to the requests
		 * processed.
		 */
		अगर (request_complete >= resp_to_process)
			अवरोध;
	पूर्ण जबतक (request_complete);

	वापस 0;
पूर्ण

अटल व्योम oct_poll_req_completion(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)wk->ctxptr;
	काष्ठा cavium_wq *cwq = &oct->dma_comp_wq;

	lio_process_ordered_list(oct, 0);

	अगर (atomic_पढ़ो(&oct->response_list
			[OCTEON_ORDERED_SC_LIST].pending_req_count))
		queue_delayed_work(cwq->wq, &cwq->wk.work, msecs_to_jअगरfies(1));
पूर्ण
