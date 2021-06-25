<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_पूर्णांक.c
 *      esas2r पूर्णांकerrupt handling
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  NO WARRANTY
 *  THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 *  LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 *  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 *  solely responsible क्रम determining the appropriateness of using and
 *  distributing the Program and assumes all risks associated with its
 *  exercise of rights under this Agreement, including but not limited to
 *  the risks and costs of program errors, damage to or loss of data,
 *  programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 *  DISCLAIMER OF LIABILITY
 *  NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 *  सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 *  HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश "esas2r.h"

/* Local function prototypes */
अटल व्योम esas2r_करोorbell_पूर्णांकerrupt(काष्ठा esas2r_adapter *a, u32 करोorbell);
अटल व्योम esas2r_get_outbound_responses(काष्ठा esas2r_adapter *a);
अटल व्योम esas2r_process_bus_reset(काष्ठा esas2r_adapter *a);

/*
 * Poll the adapter क्रम पूर्णांकerrupts and service them.
 * This function handles both legacy पूर्णांकerrupts and MSI.
 */
व्योम esas2r_polled_पूर्णांकerrupt(काष्ठा esas2r_adapter *a)
अणु
	u32 पूर्णांकstat;
	u32 करोorbell;

	esas2r_disable_chip_पूर्णांकerrupts(a);

	पूर्णांकstat = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_INT_STATUS_OUT);

	अगर (पूर्णांकstat & MU_INTSTAT_POST_OUT) अणु
		/* clear the पूर्णांकerrupt */

		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT,
					    MU_OLIS_INT);
		esas2r_flush_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT);

		esas2r_get_outbound_responses(a);
	पूर्ण

	अगर (पूर्णांकstat & MU_INTSTAT_DRBL) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell != 0)
			esas2r_करोorbell_पूर्णांकerrupt(a, करोorbell);
	पूर्ण

	esas2r_enable_chip_पूर्णांकerrupts(a);

	अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
		esas2r_करो_deferred_processes(a);
पूर्ण

/*
 * Legacy and MSI पूर्णांकerrupt handlers.  Note that the legacy पूर्णांकerrupt handler
 * schedules a TASKLET to process events, whereas the MSI handler just
 * processes पूर्णांकerrupt events directly.
 */
irqवापस_t esas2r_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)dev_id;

	अगर (!esas2r_adapter_पूर्णांकerrupt_pending(a))
		वापस IRQ_NONE;

	set_bit(AF2_INT_PENDING, &a->flags2);
	esas2r_schedule_tasklet(a);

	वापस IRQ_HANDLED;
पूर्ण

व्योम esas2r_adapter_पूर्णांकerrupt(काष्ठा esas2r_adapter *a)
अणु
	u32 करोorbell;

	अगर (likely(a->पूर्णांक_stat & MU_INTSTAT_POST_OUT)) अणु
		/* clear the पूर्णांकerrupt */
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT,
					    MU_OLIS_INT);
		esas2r_flush_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT);
		esas2r_get_outbound_responses(a);
	पूर्ण

	अगर (unlikely(a->पूर्णांक_stat & MU_INTSTAT_DRBL)) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell != 0)
			esas2r_करोorbell_पूर्णांकerrupt(a, करोorbell);
	पूर्ण

	a->पूर्णांक_mask = ESAS2R_INT_STS_MASK;

	esas2r_enable_chip_पूर्णांकerrupts(a);

	अगर (likely(atomic_पढ़ो(&a->disable_cnt) == 0))
		esas2r_करो_deferred_processes(a);
पूर्ण

irqवापस_t esas2r_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)dev_id;
	u32 पूर्णांकstat;
	u32 करोorbell;

	पूर्णांकstat = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_INT_STATUS_OUT);

	अगर (likely(पूर्णांकstat & MU_INTSTAT_POST_OUT)) अणु
		/* clear the पूर्णांकerrupt */

		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT,
					    MU_OLIS_INT);
		esas2r_flush_रेजिस्टर_dword(a, MU_OUT_LIST_INT_STAT);

		esas2r_get_outbound_responses(a);
	पूर्ण

	अगर (unlikely(पूर्णांकstat & MU_INTSTAT_DRBL)) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell != 0)
			esas2r_करोorbell_पूर्णांकerrupt(a, करोorbell);
	पूर्ण

	/*
	 * Work around a chip bug and क्रमce a new MSI to be sent अगर one is
	 * still pending.
	 */
	esas2r_disable_chip_पूर्णांकerrupts(a);
	esas2r_enable_chip_पूर्णांकerrupts(a);

	अगर (likely(atomic_पढ़ो(&a->disable_cnt) == 0))
		esas2r_करो_deferred_processes(a);

	esas2r_करो_tasklet_tasks(a);

	वापस 1;
पूर्ण



अटल व्योम esas2r_handle_outbound_rsp_err(काष्ठा esas2r_adapter *a,
					   काष्ठा esas2r_request *rq,
					   काष्ठा atto_vda_ob_rsp *rsp)
अणु

	/*
	 * For I/O requests, only copy the response अगर an error
	 * occurred and setup a callback to करो error processing.
	 */
	अगर (unlikely(rq->req_stat != RS_SUCCESS)) अणु
		स_नकल(&rq->func_rsp, &rsp->func_rsp, माप(rsp->func_rsp));

		अगर (rq->req_stat == RS_ABORTED) अणु
			अगर (rq->समयout > RQ_MAX_TIMEOUT)
				rq->req_stat = RS_TIMEOUT;
		पूर्ण अन्यथा अगर (rq->req_stat == RS_SCSI_ERROR) अणु
			u8 scsistatus = rq->func_rsp.scsi_rsp.scsi_stat;

			esas2r_trace("scsistatus: %x", scsistatus);

			/* Any of these are a good result. */
			अगर (scsistatus == SAM_STAT_GOOD || scsistatus ==
			    SAM_STAT_CONDITION_MET || scsistatus ==
			    SAM_STAT_INTERMEDIATE || scsistatus ==
			    SAM_STAT_INTERMEDIATE_CONDITION_MET) अणु
				rq->req_stat = RS_SUCCESS;
				rq->func_rsp.scsi_rsp.scsi_stat =
					SAM_STAT_GOOD;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esas2r_get_outbound_responses(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा atto_vda_ob_rsp *rsp;
	u32 rspput_ptr;
	u32 rspget_ptr;
	काष्ठा esas2r_request *rq;
	u32 handle;
	अचिन्हित दीर्घ flags;

	LIST_HEAD(comp_list);

	esas2r_trace_enter();

	spin_lock_irqsave(&a->queue_lock, flags);

	/* Get the outbound limit and poपूर्णांकers */
	rspput_ptr = le32_to_cpu(*a->outbound_copy) & MU_OLC_WRT_PTR;
	rspget_ptr = a->last_पढ़ो;

	esas2r_trace("rspput_ptr: %x, rspget_ptr: %x", rspput_ptr, rspget_ptr);

	/* If we करोn't have anything to process, get out */
	अगर (unlikely(rspget_ptr == rspput_ptr)) अणु
		spin_unlock_irqrestore(&a->queue_lock, flags);
		esas2r_trace_निकास();
		वापस;
	पूर्ण

	/* Make sure the firmware is healthy */
	अगर (unlikely(rspput_ptr >= a->list_size)) अणु
		spin_unlock_irqrestore(&a->queue_lock, flags);
		esas2r_bugon();
		esas2r_local_reset_adapter(a);
		esas2r_trace_निकास();
		वापस;
	पूर्ण

	करो अणु
		rspget_ptr++;

		अगर (rspget_ptr >= a->list_size)
			rspget_ptr = 0;

		rsp = (काष्ठा atto_vda_ob_rsp *)a->outbound_list_md.virt_addr
		      + rspget_ptr;

		handle = rsp->handle;

		/* Verअगरy the handle range */
		अगर (unlikely(LOWORD(handle) == 0
			     || LOWORD(handle) > num_requests +
			     num_ae_requests + 1)) अणु
			esas2r_bugon();
			जारी;
		पूर्ण

		/* Get the request क्रम this handle */
		rq = a->req_table[LOWORD(handle)];

		अगर (unlikely(rq == शून्य || rq->vrq->scsi.handle != handle)) अणु
			esas2r_bugon();
			जारी;
		पूर्ण

		list_del(&rq->req_list);

		/* Get the completion status */
		rq->req_stat = rsp->req_stat;

		esas2r_trace("handle: %x", handle);
		esas2r_trace("rq: %p", rq);
		esas2r_trace("req_status: %x", rq->req_stat);

		अगर (likely(rq->vrq->scsi.function == VDA_FUNC_SCSI)) अणु
			esas2r_handle_outbound_rsp_err(a, rq, rsp);
		पूर्ण अन्यथा अणु
			/*
			 * Copy the outbound completion काष्ठा क्रम non-I/O
			 * requests.
			 */
			स_नकल(&rq->func_rsp, &rsp->func_rsp,
			       माप(rsp->func_rsp));
		पूर्ण

		/* Queue the request क्रम completion. */
		list_add_tail(&rq->comp_list, &comp_list);

	पूर्ण जबतक (rspget_ptr != rspput_ptr);

	a->last_पढ़ो = rspget_ptr;
	spin_unlock_irqrestore(&a->queue_lock, flags);

	esas2r_comp_list_drain(a, &comp_list);
	esas2r_trace_निकास();
पूर्ण

/*
 * Perक्रमm all deferred processes क्रम the adapter.  Deferred
 * processes can only be करोne जबतक the current पूर्णांकerrupt
 * disable_cnt क्रम the adapter is zero.
 */
व्योम esas2r_करो_deferred_processes(काष्ठा esas2r_adapter *a)
अणु
	पूर्णांक startreqs = 2;
	काष्ठा esas2r_request *rq;
	अचिन्हित दीर्घ flags;

	/*
	 * startreqs is used to control starting requests
	 * that are on the deferred queue
	 *  = 0 - करो not start any requests
	 *  = 1 - can start discovery requests
	 *  = 2 - can start any request
	 */

	अगर (test_bit(AF_CHPRST_PENDING, &a->flags) ||
	    test_bit(AF_FLASHING, &a->flags))
		startreqs = 0;
	अन्यथा अगर (test_bit(AF_DISC_PENDING, &a->flags))
		startreqs = 1;

	atomic_inc(&a->disable_cnt);

	/* Clear off the completed list to be processed later. */

	अगर (esas2r_is_tasklet_pending(a)) अणु
		esas2r_schedule_tasklet(a);

		startreqs = 0;
	पूर्ण

	/*
	 * If we can start requests then traverse the defer queue
	 * looking क्रम requests to start or complete
	 */
	अगर (startreqs && !list_empty(&a->defer_list)) अणु
		LIST_HEAD(comp_list);
		काष्ठा list_head *element, *next;

		spin_lock_irqsave(&a->queue_lock, flags);

		list_क्रम_each_safe(element, next, &a->defer_list) अणु
			rq = list_entry(element, काष्ठा esas2r_request,
					req_list);

			अगर (rq->req_stat != RS_PENDING) अणु
				list_del(element);
				list_add_tail(&rq->comp_list, &comp_list);
			पूर्ण
			/*
			 * Process discovery and OS requests separately.  We
			 * can't hold up discovery requests when discovery is
			 * pending.  In general, there may be dअगरferent sets of
			 * conditions क्रम starting dअगरferent types of requests.
			 */
			अन्यथा अगर (rq->req_type == RT_DISC_REQ) अणु
				list_del(element);
				esas2r_disc_local_start_request(a, rq);
			पूर्ण अन्यथा अगर (startreqs == 2) अणु
				list_del(element);
				esas2r_local_start_request(a, rq);

				/*
				 * Flashing could have been set by last local
				 * start
				 */
				अगर (test_bit(AF_FLASHING, &a->flags))
					अवरोध;
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&a->queue_lock, flags);
		esas2r_comp_list_drain(a, &comp_list);
	पूर्ण

	atomic_dec(&a->disable_cnt);
पूर्ण

/*
 * Process an adapter reset (or one that is about to happen)
 * by making sure all outstanding requests are completed that
 * haven't been alपढ़ोy.
 */
व्योम esas2r_process_adapter_reset(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_request *rq = &a->general_req;
	अचिन्हित दीर्घ flags;
	काष्ठा esas2r_disc_context *dc;

	LIST_HEAD(comp_list);
	काष्ठा list_head *element;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->queue_lock, flags);

	/* पात the active discovery, अगर any.   */

	अगर (rq->पूर्णांकerrupt_cx) अणु
		dc = (काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;

		dc->disc_evt = 0;

		clear_bit(AF_DISC_IN_PROG, &a->flags);
	पूर्ण

	/*
	 * just clear the पूर्णांकerrupt callback क्रम now.  it will be dequeued अगर
	 * and when we find it on the active queue and we करोn't want the
	 * callback called.  also set the dummy completion callback in हाल we
	 * were करोing an I/O request.
	 */

	rq->पूर्णांकerrupt_cx = शून्य;
	rq->पूर्णांकerrupt_cb = शून्य;

	rq->comp_cb = esas2r_dummy_complete;

	/* Reset the पढ़ो and ग_लिखो poपूर्णांकers */

	*a->outbound_copy =
		a->last_ग_लिखो =
			a->last_पढ़ो = a->list_size - 1;

	set_bit(AF_COMM_LIST_TOGGLE, &a->flags);

	/* Kill all the requests on the active list */
	list_क्रम_each(element, &a->defer_list) अणु
		rq = list_entry(element, काष्ठा esas2r_request, req_list);

		अगर (rq->req_stat == RS_STARTED)
			अगर (esas2r_ioreq_पातed(a, rq, RS_ABORTED))
				list_add_tail(&rq->comp_list, &comp_list);
	पूर्ण

	spin_unlock_irqrestore(&a->queue_lock, flags);
	esas2r_comp_list_drain(a, &comp_list);
	esas2r_process_bus_reset(a);
	esas2r_trace_निकास();
पूर्ण

अटल व्योम esas2r_process_bus_reset(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_request *rq;
	काष्ठा list_head *element;
	अचिन्हित दीर्घ flags;

	LIST_HEAD(comp_list);

	esas2r_trace_enter();

	esas2r_hdebug("reset detected");

	spin_lock_irqsave(&a->queue_lock, flags);

	/* समाप्त all the requests on the deferred queue */
	list_क्रम_each(element, &a->defer_list) अणु
		rq = list_entry(element, काष्ठा esas2r_request, req_list);
		अगर (esas2r_ioreq_पातed(a, rq, RS_ABORTED))
			list_add_tail(&rq->comp_list, &comp_list);
	पूर्ण

	spin_unlock_irqrestore(&a->queue_lock, flags);

	esas2r_comp_list_drain(a, &comp_list);

	अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
		esas2r_करो_deferred_processes(a);

	clear_bit(AF_OS_RESET, &a->flags);

	esas2r_trace_निकास();
पूर्ण

अटल व्योम esas2r_chip_rst_needed_during_tasklet(काष्ठा esas2r_adapter *a)
अणु

	clear_bit(AF_CHPRST_NEEDED, &a->flags);
	clear_bit(AF_BUSRST_NEEDED, &a->flags);
	clear_bit(AF_BUSRST_DETECTED, &a->flags);
	clear_bit(AF_BUSRST_PENDING, &a->flags);
	/*
	 * Make sure we करोn't get attempt more than 3 resets
	 * when the upसमय between resets करोes not exceed one
	 * minute.  This will stop any situation where there is
	 * really something wrong with the hardware.  The way
	 * this works is that we start with upसमय ticks at 0.
	 * Each समय we करो a reset, we add 20 seconds worth to
	 * the count.  Each समय a समयr tick occurs, as दीर्घ
	 * as a chip reset is not pending, we decrement the
	 * tick count.  If the upसमय ticks ever माला_लो to 60
	 * seconds worth, we disable the adapter from that
	 * poपूर्णांक क्रमward.  Three strikes, you're out.
	 */
	अगर (!esas2r_is_adapter_present(a) || (a->chip_upसमय >=
					      ESAS2R_CHP_UPTIME_MAX)) अणु
		esas2r_hdebug("*** adapter disabled ***");

		/*
		 * Ok, some kind of hard failure.  Make sure we
		 * निकास this loop with chip पूर्णांकerrupts
		 * permanently disabled so we करोn't lock up the
		 * entire प्रणाली.  Also flag degraded mode to
		 * prevent the heartbeat from trying to recover.
		 */

		set_bit(AF_DEGRADED_MODE, &a->flags);
		set_bit(AF_DISABLED, &a->flags);
		clear_bit(AF_CHPRST_PENDING, &a->flags);
		clear_bit(AF_DISC_PENDING, &a->flags);

		esas2r_disable_chip_पूर्णांकerrupts(a);
		a->पूर्णांक_mask = 0;
		esas2r_process_adapter_reset(a);

		esas2r_log(ESAS2R_LOG_CRIT,
			   "Adapter disabled because of hardware failure");
	पूर्ण अन्यथा अणु
		bool alrdyrst = test_and_set_bit(AF_CHPRST_STARTED, &a->flags);

		अगर (!alrdyrst)
			/*
			 * Only disable पूर्णांकerrupts अगर this is
			 * the first reset attempt.
			 */
			esas2r_disable_chip_पूर्णांकerrupts(a);

		अगर ((test_bit(AF_POWER_MGT, &a->flags)) &&
		    !test_bit(AF_FIRST_INIT, &a->flags) && !alrdyrst) अणु
			/*
			 * Don't reset the chip on the first
			 * deferred घातer up attempt.
			 */
		पूर्ण अन्यथा अणु
			esas2r_hdebug("*** resetting chip ***");
			esas2r_reset_chip(a);
		पूर्ण

		/* Kick off the reinitialization */
		a->chip_upसमय += ESAS2R_CHP_UPTIME_CNT;
		a->chip_init_समय = jअगरfies_to_msecs(jअगरfies);
		अगर (!test_bit(AF_POWER_MGT, &a->flags)) अणु
			esas2r_process_adapter_reset(a);

			अगर (!alrdyrst) अणु
				/* Remove devices now that I/O is cleaned up. */
				a->prev_dev_cnt =
					esas2r_targ_db_get_tgt_cnt(a);
				esas2r_targ_db_हटाओ_all(a, false);
			पूर्ण
		पूर्ण

		a->पूर्णांक_mask = 0;
	पूर्ण
पूर्ण

अटल व्योम esas2r_handle_chip_rst_during_tasklet(काष्ठा esas2r_adapter *a)
अणु
	जबतक (test_bit(AF_CHPRST_DETECTED, &a->flags)) अणु
		/*
		 * Balance the enable in esas2r_initadapter_hw.
		 * Esas2r_घातer_करोwn alपढ़ोy took care of it क्रम घातer
		 * management.
		 */
		अगर (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
		    !test_bit(AF_POWER_MGT, &a->flags))
			esas2r_disable_chip_पूर्णांकerrupts(a);

		/* Reinitialize the chip. */
		esas2r_check_adapter(a);
		esas2r_init_adapter_hw(a, 0);

		अगर (test_bit(AF_CHPRST_NEEDED, &a->flags))
			अवरोध;

		अगर (test_bit(AF_POWER_MGT, &a->flags)) अणु
			/* Recovery from घातer management. */
			अगर (test_bit(AF_FIRST_INIT, &a->flags)) अणु
				/* Chip reset during normal घातer up */
				esas2r_log(ESAS2R_LOG_CRIT,
					   "The firmware was reset during a normal power-up sequence");
			पूर्ण अन्यथा अणु
				/* Deferred घातer up complete. */
				clear_bit(AF_POWER_MGT, &a->flags);
				esas2r_send_reset_ae(a, true);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Recovery from online chip reset. */
			अगर (test_bit(AF_FIRST_INIT, &a->flags)) अणु
				/* Chip reset during driver load */
			पूर्ण अन्यथा अणु
				/* Chip reset after driver load */
				esas2r_send_reset_ae(a, false);
			पूर्ण

			esas2r_log(ESAS2R_LOG_CRIT,
				   "Recovering from a chip reset while the chip was online");
		पूर्ण

		clear_bit(AF_CHPRST_STARTED, &a->flags);
		esas2r_enable_chip_पूर्णांकerrupts(a);

		/*
		 * Clear this flag last!  this indicates that the chip has been
		 * reset alपढ़ोy during initialization.
		 */
		clear_bit(AF_CHPRST_DETECTED, &a->flags);
	पूर्ण
पूर्ण


/* Perक्रमm deferred tasks when chip पूर्णांकerrupts are disabled */
व्योम esas2r_करो_tasklet_tasks(काष्ठा esas2r_adapter *a)
अणु

	अगर (test_bit(AF_CHPRST_NEEDED, &a->flags) ||
	    test_bit(AF_CHPRST_DETECTED, &a->flags)) अणु
		अगर (test_bit(AF_CHPRST_NEEDED, &a->flags))
			esas2r_chip_rst_needed_during_tasklet(a);

		esas2r_handle_chip_rst_during_tasklet(a);
	पूर्ण

	अगर (test_bit(AF_BUSRST_NEEDED, &a->flags)) अणु
		esas2r_hdebug("hard resetting bus");

		clear_bit(AF_BUSRST_NEEDED, &a->flags);

		अगर (test_bit(AF_FLASHING, &a->flags))
			set_bit(AF_BUSRST_DETECTED, &a->flags);
		अन्यथा
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN,
						    DRBL_RESET_BUS);
	पूर्ण

	अगर (test_bit(AF_BUSRST_DETECTED, &a->flags)) अणु
		esas2r_process_bus_reset(a);

		esas2r_log_dev(ESAS2R_LOG_WARN,
			       &(a->host->shost_gendev),
			       "scsi_report_bus_reset() called");

		scsi_report_bus_reset(a->host, 0);

		clear_bit(AF_BUSRST_DETECTED, &a->flags);
		clear_bit(AF_BUSRST_PENDING, &a->flags);

		esas2r_log(ESAS2R_LOG_WARN, "Bus reset complete");
	पूर्ण

	अगर (test_bit(AF_PORT_CHANGE, &a->flags)) अणु
		clear_bit(AF_PORT_CHANGE, &a->flags);

		esas2r_targ_db_report_changes(a);
	पूर्ण

	अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
		esas2r_करो_deferred_processes(a);
पूर्ण

अटल व्योम esas2r_करोorbell_पूर्णांकerrupt(काष्ठा esas2r_adapter *a, u32 करोorbell)
अणु
	अगर (!(करोorbell & DRBL_FORCE_INT)) अणु
		esas2r_trace_enter();
		esas2r_trace("doorbell: %x", करोorbell);
	पूर्ण

	/* First clear the करोorbell bits */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT, करोorbell);

	अगर (करोorbell & DRBL_RESET_BUS)
		set_bit(AF_BUSRST_DETECTED, &a->flags);

	अगर (करोorbell & DRBL_FORCE_INT)
		clear_bit(AF_HEARTBEAT, &a->flags);

	अगर (करोorbell & DRBL_PANIC_REASON_MASK) अणु
		esas2r_hdebug("*** Firmware Panic ***");
		esas2r_log(ESAS2R_LOG_CRIT, "The firmware has panicked");
	पूर्ण

	अगर (करोorbell & DRBL_FW_RESET) अणु
		set_bit(AF2_COREDUMP_AVAIL, &a->flags2);
		esas2r_local_reset_adapter(a);
	पूर्ण

	अगर (!(करोorbell & DRBL_FORCE_INT)) अणु
		esas2r_trace_निकास();
	पूर्ण
पूर्ण

व्योम esas2r_क्रमce_पूर्णांकerrupt(काष्ठा esas2r_adapter *a)
अणु
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN, DRBL_FORCE_INT |
				    DRBL_DRV_VER);
पूर्ण


अटल व्योम esas2r_lun_event(काष्ठा esas2r_adapter *a, जोड़ atto_vda_ae *ae,
			     u16 target, u32 length)
अणु
	काष्ठा esas2r_target *t = a->targetdb + target;
	u32 cplen = length;
	अचिन्हित दीर्घ flags;

	अगर (cplen > माप(t->lu_event))
		cplen = माप(t->lu_event);

	esas2r_trace("ae->lu.dwevent: %x", ae->lu.dwevent);
	esas2r_trace("ae->lu.bystate: %x", ae->lu.bystate);

	spin_lock_irqsave(&a->mem_lock, flags);

	t->new_target_state = TS_INVALID;

	अगर (ae->lu.dwevent  & VDAAE_LU_LOST) अणु
		t->new_target_state = TS_NOT_PRESENT;
	पूर्ण अन्यथा अणु
		चयन (ae->lu.bystate) अणु
		हाल VDAAE_LU_NOT_PRESENT:
		हाल VDAAE_LU_OFFLINE:
		हाल VDAAE_LU_DELETED:
		हाल VDAAE_LU_FACTORY_DISABLED:
			t->new_target_state = TS_NOT_PRESENT;
			अवरोध;

		हाल VDAAE_LU_ONLINE:
		हाल VDAAE_LU_DEGRADED:
			t->new_target_state = TS_PRESENT;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (t->new_target_state != TS_INVALID) अणु
		स_नकल(&t->lu_event, &ae->lu, cplen);

		esas2r_disc_queue_event(a, DCDE_DEV_CHANGE);
	पूर्ण

	spin_unlock_irqrestore(&a->mem_lock, flags);
पूर्ण



व्योम esas2r_ae_complete(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	जोड़ atto_vda_ae *ae =
		(जोड़ atto_vda_ae *)rq->vda_rsp_data->ae_data.event_data;
	u32 length = le32_to_cpu(rq->func_rsp.ae_rsp.length);
	जोड़ atto_vda_ae *last =
		(जोड़ atto_vda_ae *)(rq->vda_rsp_data->ae_data.event_data
				      + length);

	esas2r_trace_enter();
	esas2r_trace("length: %d", length);

	अगर (length > माप(काष्ठा atto_vda_ae_data)
	    || (length & 3) != 0
	    || length == 0) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "The AE request response length (%p) is too long: %d",
			   rq, length);

		esas2r_hdebug("aereq->length (0x%x) too long", length);
		esas2r_bugon();

		last = ae;
	पूर्ण

	जबतक (ae < last) अणु
		u16 target;

		esas2r_trace("ae: %p", ae);
		esas2r_trace("ae->hdr: %p", &(ae->hdr));

		length = ae->hdr.bylength;

		अगर (length > (u32)((u8 *)last - (u8 *)ae)
		    || (length & 3) != 0
		    || length == 0) अणु
			esas2r_log(ESAS2R_LOG_CRIT,
				   "the async event length is invalid (%p): %d",
				   ae, length);

			esas2r_hdebug("ae->hdr.length (0x%x) invalid", length);
			esas2r_bugon();

			अवरोध;
		पूर्ण

		esas2r_nuxi_ae_data(ae);

		esas2r_queue_fw_event(a, fw_event_vda_ae, ae,
				      माप(जोड़ atto_vda_ae));

		चयन (ae->hdr.bytype) अणु
		हाल VDAAE_HDR_TYPE_RAID:

			अगर (ae->raid.dwflags & (VDAAE_GROUP_STATE
						| VDAAE_RBLD_STATE
						| VDAAE_MEMBER_CHG
						| VDAAE_PART_CHG)) अणु
				esas2r_log(ESAS2R_LOG_INFO,
					   "RAID event received - name:%s rebuild_state:%d group_state:%d",
					   ae->raid.acname,
					   ae->raid.byrebuild_state,
					   ae->raid.bygroup_state);
			पूर्ण

			अवरोध;

		हाल VDAAE_HDR_TYPE_LU:
			esas2r_log(ESAS2R_LOG_INFO,
				   "LUN event received: event:%d target_id:%d LUN:%d state:%d",
				   ae->lu.dwevent,
				   ae->lu.id.tgtlun.wtarget_id,
				   ae->lu.id.tgtlun.bylun,
				   ae->lu.bystate);

			target = ae->lu.id.tgtlun.wtarget_id;

			अगर (target < ESAS2R_MAX_TARGETS)
				esas2r_lun_event(a, ae, target, length);

			अवरोध;

		हाल VDAAE_HDR_TYPE_DISK:
			esas2r_log(ESAS2R_LOG_INFO, "Disk event received");
			अवरोध;

		शेष:

			/* Silently ignore the rest and let the apps deal with
			 * them.
			 */

			अवरोध;
		पूर्ण

		ae = (जोड़ atto_vda_ae *)((u8 *)ae + length);
	पूर्ण

	/* Now requeue it. */
	esas2r_start_ae_request(a, rq);
	esas2r_trace_निकास();
पूर्ण

/* Send an asynchronous event क्रम a chip reset or घातer management. */
व्योम esas2r_send_reset_ae(काष्ठा esas2r_adapter *a, bool pwr_mgt)
अणु
	काष्ठा atto_vda_ae_hdr ae;

	अगर (pwr_mgt)
		ae.bytype = VDAAE_HDR_TYPE_PWRMGT;
	अन्यथा
		ae.bytype = VDAAE_HDR_TYPE_RESET;

	ae.byversion = VDAAE_HDR_VER_0;
	ae.byflags = 0;
	ae.bylength = (u8)माप(काष्ठा atto_vda_ae_hdr);

	अगर (pwr_mgt) अणु
		esas2r_hdebug("*** sending power management AE ***");
	पूर्ण अन्यथा अणु
		esas2r_hdebug("*** sending reset AE ***");
	पूर्ण

	esas2r_queue_fw_event(a, fw_event_vda_ae, &ae,
			      माप(जोड़ atto_vda_ae));
पूर्ण

व्योम esas2r_dummy_complete(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणुपूर्ण

अटल व्योम esas2r_check_req_rsp_sense(काष्ठा esas2r_adapter *a,
				       काष्ठा esas2r_request *rq)
अणु
	u8 snslen, snslen2;

	snslen = snslen2 = rq->func_rsp.scsi_rsp.sense_len;

	अगर (snslen > rq->sense_len)
		snslen = rq->sense_len;

	अगर (snslen) अणु
		अगर (rq->sense_buf)
			स_नकल(rq->sense_buf, rq->data_buf, snslen);
		अन्यथा
			rq->sense_buf = (u8 *)rq->data_buf;

		/* See about possible sense data */
		अगर (snslen2 > 0x0c) अणु
			u8 *s = (u8 *)rq->data_buf;

			esas2r_trace_enter();

			/* Report LUNS data has changed */
			अगर (s[0x0c] == 0x3f && s[0x0d] == 0x0E) अणु
				esas2r_trace("rq->target_id: %d",
					     rq->target_id);
				esas2r_target_state_changed(a, rq->target_id,
							    TS_LUN_CHANGE);
			पूर्ण

			esas2r_trace("add_sense_key=%x", s[0x0c]);
			esas2r_trace("add_sense_qual=%x", s[0x0d]);
			esas2r_trace_निकास();
		पूर्ण
	पूर्ण

	rq->sense_len = snslen;
पूर्ण


व्योम esas2r_complete_request(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_request *rq)
अणु
	अगर (rq->vrq->scsi.function == VDA_FUNC_FLASH
	    && rq->vrq->flash.sub_func == VDA_FLASH_COMMIT)
		clear_bit(AF_FLASHING, &a->flags);

	/* See अगर we setup a callback to करो special processing */

	अगर (rq->पूर्णांकerrupt_cb) अणु
		(*rq->पूर्णांकerrupt_cb)(a, rq);

		अगर (rq->req_stat == RS_PENDING) अणु
			esas2r_start_request(a, rq);
			वापस;
		पूर्ण
	पूर्ण

	अगर (likely(rq->vrq->scsi.function == VDA_FUNC_SCSI)
	    && unlikely(rq->req_stat != RS_SUCCESS)) अणु
		esas2r_check_req_rsp_sense(a, rq);
		esas2r_log_request_failure(a, rq);
	पूर्ण

	(*rq->comp_cb)(a, rq);
पूर्ण
