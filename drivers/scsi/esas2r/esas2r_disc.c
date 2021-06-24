<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_disc.c
 *      esas2r device discovery routines
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

/* Miscellaneous पूर्णांकernal discovery routines */
अटल व्योम esas2r_disc_पात(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_जारी(काष्ठा esas2r_adapter *a,
				 काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_fix_curr_requests(काष्ठा esas2r_adapter *a);
अटल u32 esas2r_disc_get_phys_addr(काष्ठा esas2r_sg_context *sgc, u64 *addr);
अटल bool esas2r_disc_start_request(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq);

/* Internal discovery routines that process the states */
अटल bool esas2r_disc_block_dev_scan(काष्ठा esas2r_adapter *a,
				       काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_block_dev_scan_cb(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_dev_add(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_dev_हटाओ(काष्ठा esas2r_adapter *a,
				   काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_part_info(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_part_info_cb(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_passthru_dev_info(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_passthru_dev_info_cb(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_passthru_dev_addr(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_passthru_dev_addr_cb(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq);
अटल bool esas2r_disc_raid_grp_info(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq);
अटल व्योम esas2r_disc_raid_grp_info_cb(काष्ठा esas2r_adapter *a,
					 काष्ठा esas2r_request *rq);

व्योम esas2r_disc_initialize(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_sas_nvram *nvr = a->nvram;

	esas2r_trace_enter();

	clear_bit(AF_DISC_IN_PROG, &a->flags);
	clear_bit(AF2_DEV_SCAN, &a->flags2);
	clear_bit(AF2_DEV_CNT_OK, &a->flags2);

	a->disc_start_समय = jअगरfies_to_msecs(jअगरfies);
	a->disc_रुको_समय = nvr->dev_रुको_समय * 1000;
	a->disc_रुको_cnt = nvr->dev_रुको_count;

	अगर (a->disc_रुको_cnt > ESAS2R_MAX_TARGETS)
		a->disc_रुको_cnt = ESAS2R_MAX_TARGETS;

	/*
	 * If we are करोing chip reset or घातer management processing, always
	 * रुको क्रम devices.  use the NVRAM device count अगर it is greater than
	 * previously discovered devices.
	 */

	esas2r_hdebug("starting discovery...");

	a->general_req.पूर्णांकerrupt_cx = शून्य;

	अगर (test_bit(AF_CHPRST_DETECTED, &a->flags) ||
	    test_bit(AF_POWER_MGT, &a->flags)) अणु
		अगर (a->prev_dev_cnt == 0) अणु
			/* Don't bother रुकोing अगर there is nothing to रुको
			 * क्रम.
			 */
			a->disc_रुको_समय = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Set the device रुको count to what was previously
			 * found.  We करोn't care अगर the user only configured
			 * a समय because we know the exact count to रुको क्रम.
			 * There is no need to honor the user's wishes to
			 * always रुको the full समय.
			 */
			a->disc_रुको_cnt = a->prev_dev_cnt;

			/*
			 * bump the minimum रुको समय to 15 seconds since the
			 * शेष is 3 (प्रणाली boot or the boot driver usually
			 * buys us more समय).
			 */
			अगर (a->disc_रुको_समय < 15000)
				a->disc_रुको_समय = 15000;
		पूर्ण
	पूर्ण

	esas2r_trace("disc wait count: %d", a->disc_रुको_cnt);
	esas2r_trace("disc wait time: %d", a->disc_रुको_समय);

	अगर (a->disc_रुको_समय == 0)
		esas2r_disc_check_complete(a);

	esas2r_trace_निकास();
पूर्ण

व्योम esas2r_disc_start_रुकोing(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&a->mem_lock, flags);

	अगर (a->disc_ctx.disc_evt)
		esas2r_disc_start_port(a);

	spin_unlock_irqrestore(&a->mem_lock, flags);
पूर्ण

व्योम esas2r_disc_check_क्रम_work(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_request *rq = &a->general_req;

	/* service any pending पूर्णांकerrupts first */

	esas2r_polled_पूर्णांकerrupt(a);

	/*
	 * now, पूर्णांकerrupt processing may have queued up a discovery event.  go
	 * see अगर we have one to start.  we couldn't start it in the ISR since
	 * polled discovery would cause a deadlock.
	 */

	esas2r_disc_start_रुकोing(a);

	अगर (rq->पूर्णांकerrupt_cx == शून्य)
		वापस;

	अगर (rq->req_stat == RS_STARTED
	    && rq->समयout <= RQ_MAX_TIMEOUT) अणु
		/* रुको क्रम the current discovery request to complete. */
		esas2r_रुको_request(a, rq);

		अगर (rq->req_stat == RS_TIMEOUT) अणु
			esas2r_disc_पात(a, rq);
			esas2r_local_reset_adapter(a);
			वापस;
		पूर्ण
	पूर्ण

	अगर (rq->req_stat == RS_PENDING
	    || rq->req_stat == RS_STARTED)
		वापस;

	esas2r_disc_जारी(a, rq);
पूर्ण

व्योम esas2r_disc_check_complete(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;

	esas2r_trace_enter();

	/* check to see अगर we should be रुकोing क्रम devices */
	अगर (a->disc_रुको_समय) अणु
		u32 currसमय = jअगरfies_to_msecs(jअगरfies);
		u32 समय = currसमय - a->disc_start_समय;

		/*
		 * Wait until the device रुको समय is exhausted or the device
		 * रुको count is satisfied.
		 */
		अगर (समय < a->disc_रुको_समय
		    && (esas2r_targ_db_get_tgt_cnt(a) < a->disc_रुको_cnt
			|| a->disc_रुको_cnt == 0)) अणु
			/* After three seconds of रुकोing, schedule a scan. */
			अगर (समय >= 3000
			    && !test_and_set_bit(AF2_DEV_SCAN, &a->flags2)) अणु
				spin_lock_irqsave(&a->mem_lock, flags);
				esas2r_disc_queue_event(a, DCDE_DEV_SCAN);
				spin_unlock_irqrestore(&a->mem_lock, flags);
			पूर्ण

			esas2r_trace_निकास();
			वापस;
		पूर्ण

		/*
		 * We are करोne रुकोing...we think.  Adjust the रुको समय to
		 * consume events after the count is met.
		 */
		अगर (!test_and_set_bit(AF2_DEV_CNT_OK, &a->flags2))
			a->disc_रुको_समय = समय + 3000;

		/* If we haven't करोne a full scan yet, करो it now. */
		अगर (!test_and_set_bit(AF2_DEV_SCAN, &a->flags2)) अणु
			spin_lock_irqsave(&a->mem_lock, flags);
			esas2r_disc_queue_event(a, DCDE_DEV_SCAN);
			spin_unlock_irqrestore(&a->mem_lock, flags);
			esas2r_trace_निकास();
			वापस;
		पूर्ण

		/*
		 * Now, अगर there is still समय left to consume events, जारी
		 * रुकोing.
		 */
		अगर (समय < a->disc_रुको_समय) अणु
			esas2r_trace_निकास();
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!test_and_set_bit(AF2_DEV_SCAN, &a->flags2)) अणु
			spin_lock_irqsave(&a->mem_lock, flags);
			esas2r_disc_queue_event(a, DCDE_DEV_SCAN);
			spin_unlock_irqrestore(&a->mem_lock, flags);
		पूर्ण
	पूर्ण

	/* We want to stop रुकोing क्रम devices. */
	a->disc_रुको_समय = 0;

	अगर (test_bit(AF_DISC_POLLED, &a->flags) &&
	    test_bit(AF_DISC_IN_PROG, &a->flags)) अणु
		/*
		 * Polled discovery is still pending so जारी the active
		 * discovery until it is करोne.  At that poपूर्णांक, we will stop
		 * polled discovery and transition to पूर्णांकerrupt driven
		 * discovery.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * Done रुकोing क्रम devices.  Note that we get here immediately
		 * after deferred रुकोing completes because that is पूर्णांकerrupt
		 * driven; i.e. There is no transition.
		 */
		esas2r_disc_fix_curr_requests(a);
		clear_bit(AF_DISC_PENDING, &a->flags);

		/*
		 * We have deferred target state changes until now because we
		 * करोn't want to report any removals (due to the first arrival)
		 * until the device रुको समय expires.
		 */
		set_bit(AF_PORT_CHANGE, &a->flags);
	पूर्ण

	esas2r_trace_निकास();
पूर्ण

व्योम esas2r_disc_queue_event(काष्ठा esas2r_adapter *a, u8 disc_evt)
अणु
	काष्ठा esas2r_disc_context *dc = &a->disc_ctx;

	esas2r_trace_enter();

	esas2r_trace("disc_event: %d", disc_evt);

	/* Initialize the discovery context */
	dc->disc_evt |= disc_evt;

	/*
	 * Don't start discovery beक्रमe or during polled discovery.  अगर we did,
	 * we would have a deadlock अगर we are in the ISR alपढ़ोy.
	 */
	अगर (!test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_DISC_POLLED, &a->flags))
		esas2r_disc_start_port(a);

	esas2r_trace_निकास();
पूर्ण

bool esas2r_disc_start_port(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_request *rq = &a->general_req;
	काष्ठा esas2r_disc_context *dc = &a->disc_ctx;
	bool ret;

	esas2r_trace_enter();

	अगर (test_bit(AF_DISC_IN_PROG, &a->flags)) अणु
		esas2r_trace_निकास();

		वापस false;
	पूर्ण

	/* If there is a discovery रुकोing, process it. */
	अगर (dc->disc_evt) अणु
		अगर (test_bit(AF_DISC_POLLED, &a->flags)
		    && a->disc_रुको_समय == 0) अणु
			/*
			 * We are करोing polled discovery, but we no दीर्घer want
			 * to रुको क्रम devices.  Stop polled discovery and
			 * transition to पूर्णांकerrupt driven discovery.
			 */

			esas2r_trace_निकास();

			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Discovery is complete. */

		esas2r_hdebug("disc done");

		set_bit(AF_PORT_CHANGE, &a->flags);

		esas2r_trace_निकास();

		वापस false;
	पूर्ण

	/* Handle the discovery context */
	esas2r_trace("disc_evt: %d", dc->disc_evt);
	set_bit(AF_DISC_IN_PROG, &a->flags);
	dc->flags = 0;

	अगर (test_bit(AF_DISC_POLLED, &a->flags))
		dc->flags |= DCF_POLLED;

	rq->पूर्णांकerrupt_cx = dc;
	rq->req_stat = RS_SUCCESS;

	/* Decode the event code */
	अगर (dc->disc_evt & DCDE_DEV_SCAN) अणु
		dc->disc_evt &= ~DCDE_DEV_SCAN;

		dc->flags |= DCF_DEV_SCAN;
		dc->state = DCS_BLOCK_DEV_SCAN;
	पूर्ण अन्यथा अगर (dc->disc_evt & DCDE_DEV_CHANGE) अणु
		dc->disc_evt &= ~DCDE_DEV_CHANGE;

		dc->flags |= DCF_DEV_CHANGE;
		dc->state = DCS_DEV_RMV;
	पूर्ण

	/* Continue पूर्णांकerrupt driven discovery */
	अगर (!test_bit(AF_DISC_POLLED, &a->flags))
		ret = esas2r_disc_जारी(a, rq);
	अन्यथा
		ret = true;

	esas2r_trace_निकास();

	वापस ret;
पूर्ण

अटल bool esas2r_disc_जारी(काष्ठा esas2r_adapter *a,
				 काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;

	/* Device discovery/removal */
	जबतक (dc->flags & (DCF_DEV_CHANGE | DCF_DEV_SCAN)) अणु
		rslt = false;

		चयन (dc->state) अणु
		हाल DCS_DEV_RMV:

			rslt = esas2r_disc_dev_हटाओ(a, rq);
			अवरोध;

		हाल DCS_DEV_ADD:

			rslt = esas2r_disc_dev_add(a, rq);
			अवरोध;

		हाल DCS_BLOCK_DEV_SCAN:

			rslt = esas2r_disc_block_dev_scan(a, rq);
			अवरोध;

		हाल DCS_RAID_GRP_INFO:

			rslt = esas2r_disc_raid_grp_info(a, rq);
			अवरोध;

		हाल DCS_PART_INFO:

			rslt = esas2r_disc_part_info(a, rq);
			अवरोध;

		हाल DCS_PT_DEV_INFO:

			rslt = esas2r_disc_passthru_dev_info(a, rq);
			अवरोध;
		हाल DCS_PT_DEV_ADDR:

			rslt = esas2r_disc_passthru_dev_addr(a, rq);
			अवरोध;
		हाल DCS_DISC_DONE:

			dc->flags &= ~(DCF_DEV_CHANGE | DCF_DEV_SCAN);
			अवरोध;

		शेष:

			esas2r_bugon();
			dc->state = DCS_DISC_DONE;
			अवरोध;
		पूर्ण

		अगर (rslt)
			वापस true;
	पूर्ण

	/* Discovery is करोne...क्रम now. */
	rq->पूर्णांकerrupt_cx = शून्य;

	अगर (!test_bit(AF_DISC_PENDING, &a->flags))
		esas2r_disc_fix_curr_requests(a);

	clear_bit(AF_DISC_IN_PROG, &a->flags);

	/* Start the next discovery. */
	वापस esas2r_disc_start_port(a);
पूर्ण

अटल bool esas2r_disc_start_request(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq)
अणु
	अचिन्हित दीर्घ flags;

	/* Set the समयout to a minimum value. */
	अगर (rq->समयout < ESAS2R_DEFAULT_TMO)
		rq->समयout = ESAS2R_DEFAULT_TMO;

	/*
	 * Override the request type to distinguish discovery requests.  If we
	 * end up deferring the request, esas2r_disc_local_start_request()
	 * will be called to restart it.
	 */
	rq->req_type = RT_DISC_REQ;

	spin_lock_irqsave(&a->queue_lock, flags);

	अगर (!test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_FLASHING, &a->flags))
		esas2r_disc_local_start_request(a, rq);
	अन्यथा
		list_add_tail(&rq->req_list, &a->defer_list);

	spin_unlock_irqrestore(&a->queue_lock, flags);

	वापस true;
पूर्ण

व्योम esas2r_disc_local_start_request(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq)
अणु
	esas2r_trace_enter();

	list_add_tail(&rq->req_list, &a->active_list);

	esas2r_start_vda_request(a, rq);

	esas2r_trace_निकास();

	वापस;
पूर्ण

अटल व्योम esas2r_disc_पात(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;

	esas2r_trace_enter();

	/* पात the current discovery */

	dc->state = DCS_DISC_DONE;

	esas2r_trace_निकास();
पूर्ण

अटल bool esas2r_disc_block_dev_scan(काष्ठा esas2r_adapter *a,
				       काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;

	esas2r_trace_enter();

	esas2r_rq_init_request(rq, a);

	esas2r_build_mgt_req(a,
			     rq,
			     VDAMGT_DEV_SCAN,
			     0,
			     0,
			     0,
			     शून्य);

	rq->comp_cb = esas2r_disc_block_dev_scan_cb;

	rq->समयout = 30000;
	rq->पूर्णांकerrupt_cx = dc;

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_निकास();

	वापस rslt;
पूर्ण

अटल व्योम esas2r_disc_block_dev_scan_cb(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	अचिन्हित दीर्घ flags;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	अगर (rq->req_stat == RS_SUCCESS)
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;

	dc->state = DCS_RAID_GRP_INFO;
	dc->raid_grp_ix = 0;

	esas2r_rq_destroy_request(rq, a);

	/* जारी discovery अगर it's पूर्णांकerrupt driven */

	अगर (!(dc->flags & DCF_POLLED))
		esas2r_disc_जारी(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_निकास();
पूर्ण

अटल bool esas2r_disc_raid_grp_info(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;
	काष्ठा atto_vda_grp_info *grpinfo;

	esas2r_trace_enter();

	esas2r_trace("raid_group_idx: %d", dc->raid_grp_ix);

	अगर (dc->raid_grp_ix >= VDA_MAX_RAID_GROUPS) अणु
		dc->state = DCS_DISC_DONE;

		esas2r_trace_निकास();

		वापस false;
	पूर्ण

	esas2r_rq_init_request(rq, a);

	grpinfo = &rq->vda_rsp_data->mgt_data.data.grp_info;

	स_रखो(grpinfo, 0, माप(काष्ठा atto_vda_grp_info));

	esas2r_build_mgt_req(a,
			     rq,
			     VDAMGT_GRP_INFO,
			     dc->scan_gen,
			     0,
			     माप(काष्ठा atto_vda_grp_info),
			     शून्य);

	grpinfo->grp_index = dc->raid_grp_ix;

	rq->comp_cb = esas2r_disc_raid_grp_info_cb;

	rq->पूर्णांकerrupt_cx = dc;

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_निकास();

	वापस rslt;
पूर्ण

अटल व्योम esas2r_disc_raid_grp_info_cb(काष्ठा esas2r_adapter *a,
					 काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	अचिन्हित दीर्घ flags;
	काष्ठा atto_vda_grp_info *grpinfo;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	अगर (rq->req_stat == RS_SCAN_GEN) अणु
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;
		dc->raid_grp_ix = 0;
		जाओ करोne;
	पूर्ण

	अगर (rq->req_stat == RS_SUCCESS) अणु
		grpinfo = &rq->vda_rsp_data->mgt_data.data.grp_info;

		अगर (grpinfo->status != VDA_GRP_STAT_ONLINE
		    && grpinfo->status != VDA_GRP_STAT_DEGRADED) अणु
			/* go to the next group. */

			dc->raid_grp_ix++;
		पूर्ण अन्यथा अणु
			स_नकल(&dc->raid_grp_name[0],
			       &grpinfo->grp_name[0],
			       माप(grpinfo->grp_name));

			dc->पूर्णांकerleave = le32_to_cpu(grpinfo->पूर्णांकerleave);
			dc->block_size = le32_to_cpu(grpinfo->block_size);

			dc->state = DCS_PART_INFO;
			dc->part_num = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(rq->req_stat == RS_GRP_INVALID)) अणु
			esas2r_log(ESAS2R_LOG_WARN,
				   "A request for RAID group info failed - "
				   "returned with %x",
				   rq->req_stat);
		पूर्ण

		dc->dev_ix = 0;
		dc->state = DCS_PT_DEV_INFO;
	पूर्ण

करोne:

	esas2r_rq_destroy_request(rq, a);

	/* जारी discovery अगर it's पूर्णांकerrupt driven */

	अगर (!(dc->flags & DCF_POLLED))
		esas2r_disc_जारी(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_निकास();
पूर्ण

अटल bool esas2r_disc_part_info(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;
	काष्ठा atto_vdapart_info *partinfo;

	esas2r_trace_enter();

	esas2r_trace("part_num: %d", dc->part_num);

	अगर (dc->part_num >= VDA_MAX_PARTITIONS) अणु
		dc->state = DCS_RAID_GRP_INFO;
		dc->raid_grp_ix++;

		esas2r_trace_निकास();

		वापस false;
	पूर्ण

	esas2r_rq_init_request(rq, a);

	partinfo = &rq->vda_rsp_data->mgt_data.data.part_info;

	स_रखो(partinfo, 0, माप(काष्ठा atto_vdapart_info));

	esas2r_build_mgt_req(a,
			     rq,
			     VDAMGT_PART_INFO,
			     dc->scan_gen,
			     0,
			     माप(काष्ठा atto_vdapart_info),
			     शून्य);

	partinfo->part_no = dc->part_num;

	स_नकल(&partinfo->grp_name[0],
	       &dc->raid_grp_name[0],
	       माप(partinfo->grp_name));

	rq->comp_cb = esas2r_disc_part_info_cb;

	rq->पूर्णांकerrupt_cx = dc;

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_निकास();

	वापस rslt;
पूर्ण

अटल व्योम esas2r_disc_part_info_cb(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	अचिन्हित दीर्घ flags;
	काष्ठा atto_vdapart_info *partinfo;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	अगर (rq->req_stat == RS_SCAN_GEN) अणु
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;
		dc->raid_grp_ix = 0;
		dc->state = DCS_RAID_GRP_INFO;
	पूर्ण अन्यथा अगर (rq->req_stat == RS_SUCCESS) अणु
		partinfo = &rq->vda_rsp_data->mgt_data.data.part_info;

		dc->part_num = partinfo->part_no;

		dc->curr_virt_id = le16_to_cpu(partinfo->target_id);

		esas2r_targ_db_add_raid(a, dc);

		dc->part_num++;
	पूर्ण अन्यथा अणु
		अगर (!(rq->req_stat == RS_PART_LAST)) अणु
			esas2r_log(ESAS2R_LOG_WARN,
				   "A request for RAID group partition info "
				   "failed - status:%d", rq->req_stat);
		पूर्ण

		dc->state = DCS_RAID_GRP_INFO;
		dc->raid_grp_ix++;
	पूर्ण

	esas2r_rq_destroy_request(rq, a);

	/* जारी discovery अगर it's पूर्णांकerrupt driven */

	अगर (!(dc->flags & DCF_POLLED))
		esas2r_disc_जारी(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_निकास();
पूर्ण

अटल bool esas2r_disc_passthru_dev_info(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;
	काष्ठा atto_vda_devinfo *devinfo;

	esas2r_trace_enter();

	esas2r_trace("dev_ix: %d", dc->dev_ix);

	esas2r_rq_init_request(rq, a);

	devinfo = &rq->vda_rsp_data->mgt_data.data.dev_info;

	स_रखो(devinfo, 0, माप(काष्ठा atto_vda_devinfo));

	esas2r_build_mgt_req(a,
			     rq,
			     VDAMGT_DEV_PT_INFO,
			     dc->scan_gen,
			     dc->dev_ix,
			     माप(काष्ठा atto_vda_devinfo),
			     शून्य);

	rq->comp_cb = esas2r_disc_passthru_dev_info_cb;

	rq->पूर्णांकerrupt_cx = dc;

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_निकास();

	वापस rslt;
पूर्ण

अटल व्योम esas2r_disc_passthru_dev_info_cb(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	अचिन्हित दीर्घ flags;
	काष्ठा atto_vda_devinfo *devinfo;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	अगर (rq->req_stat == RS_SCAN_GEN) अणु
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;
		dc->dev_ix = 0;
		dc->state = DCS_PT_DEV_INFO;
	पूर्ण अन्यथा अगर (rq->req_stat == RS_SUCCESS) अणु
		devinfo = &rq->vda_rsp_data->mgt_data.data.dev_info;

		dc->dev_ix = le16_to_cpu(rq->func_rsp.mgt_rsp.dev_index);

		dc->curr_virt_id = le16_to_cpu(devinfo->target_id);

		अगर (le16_to_cpu(devinfo->features) & VDADEVFEAT_PHYS_ID) अणु
			dc->curr_phys_id =
				le16_to_cpu(devinfo->phys_target_id);
			dc->dev_addr_type = ATTO_GDA_AT_PORT;
			dc->state = DCS_PT_DEV_ADDR;

			esas2r_trace("curr_virt_id: %d", dc->curr_virt_id);
			esas2r_trace("curr_phys_id: %d", dc->curr_phys_id);
		पूर्ण अन्यथा अणु
			dc->dev_ix++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(rq->req_stat == RS_DEV_INVALID)) अणु
			esas2r_log(ESAS2R_LOG_WARN,
				   "A request for device information failed - "
				   "status:%d", rq->req_stat);
		पूर्ण

		dc->state = DCS_DISC_DONE;
	पूर्ण

	esas2r_rq_destroy_request(rq, a);

	/* जारी discovery अगर it's पूर्णांकerrupt driven */

	अगर (!(dc->flags & DCF_POLLED))
		esas2r_disc_जारी(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_निकास();
पूर्ण

अटल bool esas2r_disc_passthru_dev_addr(काष्ठा esas2r_adapter *a,
					  काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	bool rslt;
	काष्ठा atto_ioctl *hi;
	काष्ठा esas2r_sg_context sgc;

	esas2r_trace_enter();

	esas2r_rq_init_request(rq, a);

	/* क्रमmat the request. */

	sgc.cur_offset = शून्य;
	sgc.get_phys_addr = (PGETPHYSADDR)esas2r_disc_get_phys_addr;
	sgc.length = दुरत्व(काष्ठा atto_ioctl, data)
		     + माप(काष्ठा atto_hba_get_device_address);

	esas2r_sgc_init(&sgc, a, rq, rq->vrq->ioctl.sge);

	esas2r_build_ioctl_req(a, rq, sgc.length, VDA_IOCTL_HBA);

	अगर (!esas2r_build_sg_list(a, rq, &sgc)) अणु
		esas2r_rq_destroy_request(rq, a);

		esas2r_trace_निकास();

		वापस false;
	पूर्ण

	rq->comp_cb = esas2r_disc_passthru_dev_addr_cb;

	rq->पूर्णांकerrupt_cx = dc;

	/* क्रमmat the IOCTL data. */

	hi = (काष्ठा atto_ioctl *)a->disc_buffer;

	स_रखो(a->disc_buffer, 0, ESAS2R_DISC_BUF_LEN);

	hi->version = ATTO_VER_GET_DEV_ADDR0;
	hi->function = ATTO_FUNC_GET_DEV_ADDR;
	hi->flags = HBAF_TUNNEL;

	hi->data.get_dev_addr.target_id = le32_to_cpu(dc->curr_phys_id);
	hi->data.get_dev_addr.addr_type = dc->dev_addr_type;

	/* start it up. */

	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_निकास();

	वापस rslt;
पूर्ण

अटल व्योम esas2r_disc_passthru_dev_addr_cb(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_target *t = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा atto_ioctl *hi;
	u16 addrlen;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	hi = (काष्ठा atto_ioctl *)a->disc_buffer;

	अगर (rq->req_stat == RS_SUCCESS
	    && hi->status == ATTO_STS_SUCCESS) अणु
		addrlen = le16_to_cpu(hi->data.get_dev_addr.addr_len);

		अगर (dc->dev_addr_type == ATTO_GDA_AT_PORT) अणु
			अगर (addrlen == माप(u64))
				स_नकल(&dc->sas_addr,
				       &hi->data.get_dev_addr.address[0],
				       addrlen);
			अन्यथा
				स_रखो(&dc->sas_addr, 0, माप(dc->sas_addr));

			/* Get the unique identअगरier. */
			dc->dev_addr_type = ATTO_GDA_AT_UNIQUE;

			जाओ next_dev_addr;
		पूर्ण अन्यथा अणु
			/* Add the pass through target. */
			अगर (HIBYTE(addrlen) == 0) अणु
				t = esas2r_targ_db_add_pthru(a,
							     dc,
							     &hi->data.
							     get_dev_addr.
							     address[0],
							     (u8)hi->data.
							     get_dev_addr.
							     addr_len);

				अगर (t)
					स_नकल(&t->sas_addr, &dc->sas_addr,
					       माप(t->sas_addr));
			पूर्ण अन्यथा अणु
				/* getting the back end data failed */

				esas2r_log(ESAS2R_LOG_WARN,
					   "an error occurred retrieving the "
					   "back end data (%s:%d)",
					   __func__,
					   __LINE__);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* getting the back end data failed */

		esas2r_log(ESAS2R_LOG_WARN,
			   "an error occurred retrieving the back end data - "
			   "rq->req_stat:%d hi->status:%d",
			   rq->req_stat, hi->status);
	पूर्ण

	/* proceed to the next device. */

	अगर (dc->flags & DCF_DEV_SCAN) अणु
		dc->dev_ix++;
		dc->state = DCS_PT_DEV_INFO;
	पूर्ण अन्यथा अगर (dc->flags & DCF_DEV_CHANGE) अणु
		dc->curr_targ++;
		dc->state = DCS_DEV_ADD;
	पूर्ण अन्यथा अणु
		esas2r_bugon();
	पूर्ण

next_dev_addr:
	esas2r_rq_destroy_request(rq, a);

	/* जारी discovery अगर it's पूर्णांकerrupt driven */

	अगर (!(dc->flags & DCF_POLLED))
		esas2r_disc_जारी(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_निकास();
पूर्ण

अटल u32 esas2r_disc_get_phys_addr(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	काष्ठा esas2r_adapter *a = sgc->adapter;

	अगर (sgc->length > ESAS2R_DISC_BUF_LEN) अणु
		esas2r_bugon();
	पूर्ण

	*addr = a->uncached_phys
		+ (u64)((u8 *)a->disc_buffer - a->uncached);

	वापस sgc->length;
पूर्ण

अटल bool esas2r_disc_dev_हटाओ(काष्ठा esas2r_adapter *a,
				   काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_target *t;
	काष्ठा esas2r_target *t2;

	esas2r_trace_enter();

	/* process removals. */

	क्रम (t = a->targetdb; t < a->targetdb_end; t++) अणु
		अगर (t->new_target_state != TS_NOT_PRESENT)
			जारी;

		t->new_target_state = TS_INVALID;

		/* हटाओ the right target! */

		t2 =
			esas2r_targ_db_find_by_virt_id(a,
						       esas2r_targ_get_id(t,
									  a));

		अगर (t2)
			esas2r_targ_db_हटाओ(a, t2);
	पूर्ण

	/* removals complete.  process arrivals. */

	dc->state = DCS_DEV_ADD;
	dc->curr_targ = a->targetdb;

	esas2r_trace_निकास();

	वापस false;
पूर्ण

अटल bool esas2r_disc_dev_add(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_disc_context *dc =
		(काष्ठा esas2r_disc_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_target *t = dc->curr_targ;

	अगर (t >= a->targetdb_end) अणु
		/* करोne processing state changes. */

		dc->state = DCS_DISC_DONE;
	पूर्ण अन्यथा अगर (t->new_target_state == TS_PRESENT) अणु
		काष्ठा atto_vda_ae_lu *luevt = &t->lu_event;

		esas2r_trace_enter();

		/* clear this now in हाल more events come in. */

		t->new_target_state = TS_INVALID;

		/* setup the discovery context क्रम adding this device. */

		dc->curr_virt_id = esas2r_targ_get_id(t, a);

		अगर ((luevt->hdr.bylength >= दुरत्व(काष्ठा atto_vda_ae_lu, id)
		     + माप(काष्ठा atto_vda_ae_lu_tgt_lun_raid))
		    && !(luevt->dwevent & VDAAE_LU_PASSTHROUGH)) अणु
			dc->block_size = luevt->id.tgtlun_raid.dwblock_size;
			dc->पूर्णांकerleave = luevt->id.tgtlun_raid.dwपूर्णांकerleave;
		पूर्ण अन्यथा अणु
			dc->block_size = 0;
			dc->पूर्णांकerleave = 0;
		पूर्ण

		/* determine the device type being added. */

		अगर (luevt->dwevent & VDAAE_LU_PASSTHROUGH) अणु
			अगर (luevt->dwevent & VDAAE_LU_PHYS_ID) अणु
				dc->state = DCS_PT_DEV_ADDR;
				dc->dev_addr_type = ATTO_GDA_AT_PORT;
				dc->curr_phys_id = luevt->wphys_target_id;
			पूर्ण अन्यथा अणु
				esas2r_log(ESAS2R_LOG_WARN,
					   "luevt->dwevent does not have the "
					   "VDAAE_LU_PHYS_ID bit set (%s:%d)",
					   __func__, __LINE__);
			पूर्ण
		पूर्ण अन्यथा अणु
			dc->raid_grp_name[0] = 0;

			esas2r_targ_db_add_raid(a, dc);
		पूर्ण

		esas2r_trace("curr_virt_id: %d", dc->curr_virt_id);
		esas2r_trace("curr_phys_id: %d", dc->curr_phys_id);
		esas2r_trace("dwevent: %d", luevt->dwevent);

		esas2r_trace_निकास();
	पूर्ण

	अगर (dc->state == DCS_DEV_ADD) अणु
		/* go to the next device. */

		dc->curr_targ++;
	पूर्ण

	वापस false;
पूर्ण

/*
 * When discovery is करोne, find all requests on defer queue and
 * test अगर they need to be modअगरied. If a target is no दीर्घer present
 * then complete the request with RS_SEL. Otherwise, update the
 * target_id since after a hibernate it can be a dअगरferent value.
 * VDA करोes not make passthrough target IDs persistent.
 */
अटल व्योम esas2r_disc_fix_curr_requests(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा esas2r_target *t;
	काष्ठा esas2r_request *rq;
	काष्ठा list_head *element;

	/* update virt_targ_id in any outstanding esas2r_requests  */

	spin_lock_irqsave(&a->queue_lock, flags);

	list_क्रम_each(element, &a->defer_list) अणु
		rq = list_entry(element, काष्ठा esas2r_request, req_list);
		अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI) अणु
			t = a->targetdb + rq->target_id;

			अगर (t->target_state == TS_PRESENT)
				rq->vrq->scsi.target_id = le16_to_cpu(
					t->virt_targ_id);
			अन्यथा
				rq->req_stat = RS_SEL;
		पूर्ण

	पूर्ण

	spin_unlock_irqrestore(&a->queue_lock, flags);
पूर्ण
