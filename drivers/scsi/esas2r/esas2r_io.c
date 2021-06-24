<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_io.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)mpt3sas/mpt3sas_trigger_diag.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

व्योम esas2r_start_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_target *t = शून्य;
	काष्ठा esas2r_request *startrq = rq;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(test_bit(AF_DEGRADED_MODE, &a->flags) ||
		     test_bit(AF_POWER_DOWN, &a->flags))) अणु
		अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI)
			rq->req_stat = RS_SEL2;
		अन्यथा
			rq->req_stat = RS_DEGRADED;
	पूर्ण अन्यथा अगर (likely(rq->vrq->scsi.function == VDA_FUNC_SCSI)) अणु
		t = a->targetdb + rq->target_id;

		अगर (unlikely(t >= a->targetdb_end
			     || !(t->flags & TF_USED))) अणु
			rq->req_stat = RS_SEL;
		पूर्ण अन्यथा अणु
			/* copy in the target ID. */
			rq->vrq->scsi.target_id = cpu_to_le16(t->virt_targ_id);

			/*
			 * Test अगर we want to report RS_SEL क्रम missing target.
			 * Note that अगर AF_DISC_PENDING is set than this will
			 * go on the defer queue.
			 */
			अगर (unlikely(t->target_state != TS_PRESENT &&
				     !test_bit(AF_DISC_PENDING, &a->flags)))
				rq->req_stat = RS_SEL;
		पूर्ण
	पूर्ण

	अगर (unlikely(rq->req_stat != RS_PENDING)) अणु
		esas2r_complete_request(a, rq);
		वापस;
	पूर्ण

	esas2r_trace("rq=%p", rq);
	esas2r_trace("rq->vrq->scsi.handle=%x", rq->vrq->scsi.handle);

	अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI) अणु
		esas2r_trace("rq->target_id=%d", rq->target_id);
		esas2r_trace("rq->vrq->scsi.flags=%x", rq->vrq->scsi.flags);
	पूर्ण

	spin_lock_irqsave(&a->queue_lock, flags);

	अगर (likely(list_empty(&a->defer_list) &&
		   !test_bit(AF_CHPRST_PENDING, &a->flags) &&
		   !test_bit(AF_FLASHING, &a->flags) &&
		   !test_bit(AF_DISC_PENDING, &a->flags)))
		esas2r_local_start_request(a, startrq);
	अन्यथा
		list_add_tail(&startrq->req_list, &a->defer_list);

	spin_unlock_irqrestore(&a->queue_lock, flags);
पूर्ण

/*
 * Starts the specअगरied request.  all requests have RS_PENDING set when this
 * routine is called.  The caller is usually esas2r_start_request, but
 * esas2r_करो_deferred_processes will start request that are deferred.
 *
 * The caller must ensure that requests can be started.
 *
 * esas2r_start_request will defer a request अगर there are alपढ़ोy requests
 * रुकोing or there is a chip reset pending.  once the reset condition clears,
 * esas2r_करो_deferred_processes will call this function to start the request.
 *
 * When a request is started, it is placed on the active list and queued to
 * the controller.
 */
व्योम esas2r_local_start_request(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	esas2r_trace_enter();
	esas2r_trace("rq=%p", rq);
	esas2r_trace("rq->vrq:%p", rq->vrq);
	esas2r_trace("rq->vrq_md->phys_addr:%x", rq->vrq_md->phys_addr);

	अगर (unlikely(rq->vrq->scsi.function == VDA_FUNC_FLASH
		     && rq->vrq->flash.sub_func == VDA_FLASH_COMMIT))
		set_bit(AF_FLASHING, &a->flags);

	list_add_tail(&rq->req_list, &a->active_list);
	esas2r_start_vda_request(a, rq);
	esas2r_trace_निकास();
	वापस;
पूर्ण

व्योम esas2r_start_vda_request(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_inbound_list_source_entry *element;
	u32 dw;

	rq->req_stat = RS_STARTED;
	/*
	 * Calculate the inbound list entry location and the current state of
	 * toggle bit.
	 */
	a->last_ग_लिखो++;
	अगर (a->last_ग_लिखो >= a->list_size) अणु
		a->last_ग_लिखो = 0;
		/* update the toggle bit */
		अगर (test_bit(AF_COMM_LIST_TOGGLE, &a->flags))
			clear_bit(AF_COMM_LIST_TOGGLE, &a->flags);
		अन्यथा
			set_bit(AF_COMM_LIST_TOGGLE, &a->flags);
	पूर्ण

	element =
		(काष्ठा esas2r_inbound_list_source_entry *)a->inbound_list_md.
		virt_addr
		+ a->last_ग_लिखो;

	/* Set the VDA request size अगर it was never modअगरied */
	अगर (rq->vda_req_sz == RQ_SIZE_DEFAULT)
		rq->vda_req_sz = (u16)(a->max_vdareq_size / माप(u32));

	element->address = cpu_to_le64(rq->vrq_md->phys_addr);
	element->length = cpu_to_le32(rq->vda_req_sz);

	/* Update the ग_लिखो poपूर्णांकer */
	dw = a->last_ग_लिखो;

	अगर (test_bit(AF_COMM_LIST_TOGGLE, &a->flags))
		dw |= MU_ILW_TOGGLE;

	esas2r_trace("rq->vrq->scsi.handle:%x", rq->vrq->scsi.handle);
	esas2r_trace("dw:%x", dw);
	esas2r_trace("rq->vda_req_sz:%x", rq->vda_req_sz);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_WRITE, dw);
पूर्ण

/*
 * Build the scatter/gather list क्रम an I/O request according to the
 * specअगरications placed in the s/g context.  The caller must initialize
 * context prior to the initial call by calling esas2r_sgc_init().
 */
bool esas2r_build_sg_list_sge(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_sg_context *sgc)
अणु
	काष्ठा esas2r_request *rq = sgc->first_req;
	जोड़ atto_vda_req *vrq = rq->vrq;

	जबतक (sgc->length) अणु
		u32 rem = 0;
		u64 addr;
		u32 len;

		len = (*sgc->get_phys_addr)(sgc, &addr);

		अगर (unlikely(len == 0))
			वापस false;

		/* अगर current length is more than what's left, stop there */
		अगर (unlikely(len > sgc->length))
			len = sgc->length;

another_entry:
		/* limit to a round number less than the maximum length */
		अगर (len > SGE_LEN_MAX) अणु
			/*
			 * Save the reमुख्यder of the split.  Whenever we limit
			 * an entry we come back around to build entries out
			 * of the leftover.  We करो this to prevent multiple
			 * calls to the get_phys_addr() function क्रम an SGE
			 * that is too large.
			 */
			rem = len - SGE_LEN_MAX;
			len = SGE_LEN_MAX;
		पूर्ण

		/* See अगर we need to allocate a new SGL */
		अगर (unlikely(sgc->sge.a64.curr > sgc->sge.a64.limit)) अणु
			u8 sgelen;
			काष्ठा esas2r_mem_desc *sgl;

			/*
			 * If no SGls are available, वापस failure.  The
			 * caller can call us later with the current context
			 * to pick up here.
			 */
			sgl = esas2r_alloc_sgl(a);

			अगर (unlikely(sgl == शून्य))
				वापस false;

			/* Calculate the length of the last SGE filled in */
			sgelen = (u8)((u8 *)sgc->sge.a64.curr
				      - (u8 *)sgc->sge.a64.last);

			/*
			 * Copy the last SGE filled in to the first entry of
			 * the new SGL to make room क्रम the chain entry.
			 */
			स_नकल(sgl->virt_addr, sgc->sge.a64.last, sgelen);

			/* Figure out the new curr poपूर्णांकer in the new segment */
			sgc->sge.a64.curr =
				(काष्ठा atto_vda_sge *)((u8 *)sgl->virt_addr +
							sgelen);

			/* Set the limit poपूर्णांकer and build the chain entry */
			sgc->sge.a64.limit =
				(काष्ठा atto_vda_sge *)((u8 *)sgl->virt_addr
							+ sgl_page_size
							- माप(काष्ठा
								 atto_vda_sge));
			sgc->sge.a64.last->length = cpu_to_le32(
				SGE_CHAIN | SGE_ADDR_64);
			sgc->sge.a64.last->address =
				cpu_to_le64(sgl->phys_addr);

			/*
			 * Now, अगर there was a previous chain entry, then
			 * update it to contain the length of this segment
			 * and size of this chain.  otherwise this is the
			 * first SGL, so set the chain_offset in the request.
			 */
			अगर (sgc->sge.a64.chain) अणु
				sgc->sge.a64.chain->length |=
					cpu_to_le32(
						((u8 *)(sgc->sge.a64.
							last + 1)
						 - (u8 *)rq->sg_table->
						 virt_addr)
						+ माप(काष्ठा atto_vda_sge) *
						LOBIT(SGE_CHAIN_SZ));
			पूर्ण अन्यथा अणु
				vrq->scsi.chain_offset = (u8)
							 ((u8 *)sgc->
							  sge.a64.last -
							  (u8 *)vrq);

				/*
				 * This is the first SGL, so set the
				 * chain_offset and the VDA request size in
				 * the request.
				 */
				rq->vda_req_sz =
					(vrq->scsi.chain_offset +
					 माप(काष्ठा atto_vda_sge) +
					 3)
					/ माप(u32);
			पूर्ण

			/*
			 * Remember this so when we get a new SGL filled in we
			 * can update the length of this chain entry.
			 */
			sgc->sge.a64.chain = sgc->sge.a64.last;

			/* Now link the new SGL onto the primary request. */
			list_add(&sgl->next_desc, &rq->sg_table_head);
		पूर्ण

		/* Update last one filled in */
		sgc->sge.a64.last = sgc->sge.a64.curr;

		/* Build the new SGE and update the S/G context */
		sgc->sge.a64.curr->length = cpu_to_le32(SGE_ADDR_64 | len);
		sgc->sge.a64.curr->address = cpu_to_le32(addr);
		sgc->sge.a64.curr++;
		sgc->cur_offset += len;
		sgc->length -= len;

		/*
		 * Check अगर we previously split an entry.  If so we have to
		 * pick up where we left off.
		 */
		अगर (rem) अणु
			addr += len;
			len = rem;
			rem = 0;
			जाओ another_entry;
		पूर्ण
	पूर्ण

	/* Mark the end of the SGL */
	sgc->sge.a64.last->length |= cpu_to_le32(SGE_LAST);

	/*
	 * If there was a previous chain entry, update the length to indicate
	 * the length of this last segment.
	 */
	अगर (sgc->sge.a64.chain) अणु
		sgc->sge.a64.chain->length |= cpu_to_le32(
			((u8 *)(sgc->sge.a64.curr) -
			 (u8 *)rq->sg_table->virt_addr));
	पूर्ण अन्यथा अणु
		u16 reqsize;

		/*
		 * The entire VDA request was not used so lets
		 * set the size of the VDA request to be DMA'd
		 */
		reqsize =
			((u16)((u8 *)sgc->sge.a64.last - (u8 *)vrq)
			 + माप(काष्ठा atto_vda_sge) + 3) / माप(u32);

		/*
		 * Only update the request size अगर it is bigger than what is
		 * alपढ़ोy there.  We can come in here twice क्रम some management
		 * commands.
		 */
		अगर (reqsize > rq->vda_req_sz)
			rq->vda_req_sz = reqsize;
	पूर्ण
	वापस true;
पूर्ण


/*
 * Create PRD list क्रम each I-block consumed by the command. This routine
 * determines how much data is required from each I-block being consumed
 * by the command. The first and last I-blocks can be partials and all of
 * the I-blocks in between are क्रम a full I-block of data.
 *
 * The पूर्णांकerleave size is used to determine the number of bytes in the 1st
 * I-block and the reमुख्यing I-blocks are what remeains.
 */
अटल bool esas2r_build_prd_iblk(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_sg_context *sgc)
अणु
	काष्ठा esas2r_request *rq = sgc->first_req;
	u64 addr;
	u32 len;
	काष्ठा esas2r_mem_desc *sgl;
	u32 numchain = 1;
	u32 rem = 0;

	जबतक (sgc->length) अणु
		/* Get the next address/length pair */

		len = (*sgc->get_phys_addr)(sgc, &addr);

		अगर (unlikely(len == 0))
			वापस false;

		/* If current length is more than what's left, stop there */

		अगर (unlikely(len > sgc->length))
			len = sgc->length;

another_entry:
		/* Limit to a round number less than the maximum length */

		अगर (len > PRD_LEN_MAX) अणु
			/*
			 * Save the reमुख्यder of the split.  whenever we limit
			 * an entry we come back around to build entries out
			 * of the leftover.  We करो this to prevent multiple
			 * calls to the get_phys_addr() function क्रम an SGE
			 * that is too large.
			 */
			rem = len - PRD_LEN_MAX;
			len = PRD_LEN_MAX;
		पूर्ण

		/* See अगर we need to allocate a new SGL */
		अगर (sgc->sge.prd.sge_cnt == 0) अणु
			अगर (len == sgc->length) अणु
				/*
				 * We only have 1 PRD entry left.
				 * It can be placed where the chain
				 * entry would have gone
				 */

				/* Build the simple SGE */
				sgc->sge.prd.curr->ctl_len = cpu_to_le32(
					PRD_DATA | len);
				sgc->sge.prd.curr->address = cpu_to_le64(addr);

				/* Adjust length related fields */
				sgc->cur_offset += len;
				sgc->length -= len;

				/* We use the reserved chain entry क्रम data */
				numchain = 0;

				अवरोध;
			पूर्ण

			अगर (sgc->sge.prd.chain) अणु
				/*
				 * Fill # of entries of current SGL in previous
				 * chain the length of this current SGL may not
				 * full.
				 */

				sgc->sge.prd.chain->ctl_len |= cpu_to_le32(
					sgc->sge.prd.sgl_max_cnt);
			पूर्ण

			/*
			 * If no SGls are available, वापस failure.  The
			 * caller can call us later with the current context
			 * to pick up here.
			 */

			sgl = esas2r_alloc_sgl(a);

			अगर (unlikely(sgl == शून्य))
				वापस false;

			/*
			 * Link the new SGL onto the chain
			 * They are in reverse order
			 */
			list_add(&sgl->next_desc, &rq->sg_table_head);

			/*
			 * An SGL was just filled in and we are starting
			 * a new SGL. Prime the chain of the ending SGL with
			 * info that poपूर्णांकs to the new SGL. The length माला_लो
			 * filled in when the new SGL is filled or ended
			 */

			sgc->sge.prd.chain = sgc->sge.prd.curr;

			sgc->sge.prd.chain->ctl_len = cpu_to_le32(PRD_CHAIN);
			sgc->sge.prd.chain->address =
				cpu_to_le64(sgl->phys_addr);

			/*
			 * Start a new segment.
			 * Take one away and save क्रम chain SGE
			 */

			sgc->sge.prd.curr =
				(काष्ठा atto_physical_region_description *)sgl
				->
				virt_addr;
			sgc->sge.prd.sge_cnt = sgc->sge.prd.sgl_max_cnt - 1;
		पूर्ण

		sgc->sge.prd.sge_cnt--;
		/* Build the simple SGE */
		sgc->sge.prd.curr->ctl_len = cpu_to_le32(PRD_DATA | len);
		sgc->sge.prd.curr->address = cpu_to_le64(addr);

		/* Used another element.  Poपूर्णांक to the next one */

		sgc->sge.prd.curr++;

		/* Adjust length related fields */

		sgc->cur_offset += len;
		sgc->length -= len;

		/*
		 * Check अगर we previously split an entry.  If so we have to
		 * pick up where we left off.
		 */

		अगर (rem) अणु
			addr += len;
			len = rem;
			rem = 0;
			जाओ another_entry;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&rq->sg_table_head)) अणु
		अगर (sgc->sge.prd.chain) अणु
			sgc->sge.prd.chain->ctl_len |=
				cpu_to_le32(sgc->sge.prd.sgl_max_cnt
					    - sgc->sge.prd.sge_cnt
					    - numchain);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

bool esas2r_build_sg_list_prd(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_sg_context *sgc)
अणु
	काष्ठा esas2r_request *rq = sgc->first_req;
	u32 len = sgc->length;
	काष्ठा esas2r_target *t = a->targetdb + rq->target_id;
	u8 is_i_o = 0;
	u16 reqsize;
	काष्ठा atto_physical_region_description *curr_iblk_chn;
	u8 *cdb = (u8 *)&rq->vrq->scsi.cdb[0];

	/*
	 * extract LBA from command so we can determine
	 * the I-Block boundary
	 */

	अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI
	    && t->target_state == TS_PRESENT
	    && !(t->flags & TF_PASS_THRU)) अणु
		u32 lbalo = 0;

		चयन (rq->vrq->scsi.cdb[0]) अणु
		हाल    READ_16:
		हाल    WRITE_16:
		अणु
			lbalo =
				MAKEDWORD(MAKEWORD(cdb[9],
						   cdb[8]),
					  MAKEWORD(cdb[7],
						   cdb[6]));
			is_i_o = 1;
			अवरोध;
		पूर्ण

		हाल    READ_12:
		हाल    WRITE_12:
		हाल    READ_10:
		हाल    WRITE_10:
		अणु
			lbalo =
				MAKEDWORD(MAKEWORD(cdb[5],
						   cdb[4]),
					  MAKEWORD(cdb[3],
						   cdb[2]));
			is_i_o = 1;
			अवरोध;
		पूर्ण

		हाल    READ_6:
		हाल    WRITE_6:
		अणु
			lbalo =
				MAKEDWORD(MAKEWORD(cdb[3],
						   cdb[2]),
					  MAKEWORD(cdb[1] & 0x1F,
						   0));
			is_i_o = 1;
			अवरोध;
		पूर्ण

		शेष:
			अवरोध;
		पूर्ण

		अगर (is_i_o) अणु
			u32 startlba;

			rq->vrq->scsi.iblk_cnt_prd = 0;

			/* Determine size of 1st I-block PRD list       */
			startlba = t->पूर्णांकer_block - (lbalo & (t->पूर्णांकer_block -
							      1));
			sgc->length = startlba * t->block_size;

			/* Chk अगर the 1st iblk chain starts at base of Iblock */
			अगर ((lbalo & (t->पूर्णांकer_block - 1)) == 0)
				rq->flags |= RF_1ST_IBLK_BASE;

			अगर (sgc->length > len)
				sgc->length = len;
		पूर्ण अन्यथा अणु
			sgc->length = len;
		पूर्ण
	पूर्ण अन्यथा अणु
		sgc->length = len;
	पूर्ण

	/* get our starting chain address   */

	curr_iblk_chn =
		(काष्ठा atto_physical_region_description *)sgc->sge.a64.curr;

	sgc->sge.prd.sgl_max_cnt = sgl_page_size /
				   माप(काष्ठा
					  atto_physical_region_description);

	/* create all of the I-block PRD lists          */

	जबतक (len) अणु
		sgc->sge.prd.sge_cnt = 0;
		sgc->sge.prd.chain = शून्य;
		sgc->sge.prd.curr = curr_iblk_chn;

		/* increment to next I-Block    */

		len -= sgc->length;

		/* go build the next I-Block PRD list   */

		अगर (unlikely(!esas2r_build_prd_iblk(a, sgc)))
			वापस false;

		curr_iblk_chn++;

		अगर (is_i_o) अणु
			rq->vrq->scsi.iblk_cnt_prd++;

			अगर (len > t->पूर्णांकer_byte)
				sgc->length = t->पूर्णांकer_byte;
			अन्यथा
				sgc->length = len;
		पूर्ण
	पूर्ण

	/* figure out the size used of the VDA request */

	reqsize = ((u16)((u8 *)curr_iblk_chn - (u8 *)rq->vrq))
		  / माप(u32);

	/*
	 * only update the request size अगर it is bigger than what is
	 * alपढ़ोy there.  we can come in here twice क्रम some management
	 * commands.
	 */

	अगर (reqsize > rq->vda_req_sz)
		rq->vda_req_sz = reqsize;

	वापस true;
पूर्ण

अटल व्योम esas2r_handle_pending_reset(काष्ठा esas2r_adapter *a, u32 currसमय)
अणु
	u32 delta = currसमय - a->chip_init_समय;

	अगर (delta <= ESAS2R_CHPRST_WAIT_TIME) अणु
		/* Wait beक्रमe accessing रेजिस्टरs */
	पूर्ण अन्यथा अगर (delta >= ESAS2R_CHPRST_TIME) अणु
		/*
		 * The last reset failed so try again. Reset
		 * processing will give up after three tries.
		 */
		esas2r_local_reset_adapter(a);
	पूर्ण अन्यथा अणु
		/* We can now see अगर the firmware is पढ़ोy */
		u32 करोorbell;

		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell == 0xFFFFFFFF || !(करोorbell & DRBL_FORCE_INT)) अणु
			esas2r_क्रमce_पूर्णांकerrupt(a);
		पूर्ण अन्यथा अणु
			u32 ver = (करोorbell & DRBL_FW_VER_MSK);

			/* Driver supports API version 0 and 1 */
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);
			अगर (ver == DRBL_FW_VER_0) अणु
				set_bit(AF_CHPRST_DETECTED, &a->flags);
				set_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 128;
				a->build_sgl = esas2r_build_sg_list_sge;
			पूर्ण अन्यथा अगर (ver == DRBL_FW_VER_1) अणु
				set_bit(AF_CHPRST_DETECTED, &a->flags);
				clear_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 1024;
				a->build_sgl = esas2r_build_sg_list_prd;
			पूर्ण अन्यथा अणु
				esas2r_local_reset_adapter(a);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/* This function must be called once per समयr tick */
व्योम esas2r_समयr_tick(काष्ठा esas2r_adapter *a)
अणु
	u32 currसमय = jअगरfies_to_msecs(jअगरfies);
	u32 deltaसमय = currसमय - a->last_tick_समय;

	a->last_tick_समय = currसमय;

	/* count करोwn the upसमय */
	अगर (a->chip_upसमय &&
	    !test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_DISC_PENDING, &a->flags)) अणु
		अगर (deltaसमय >= a->chip_upसमय)
			a->chip_upसमय = 0;
		अन्यथा
			a->chip_upसमय -= deltaसमय;
	पूर्ण

	अगर (test_bit(AF_CHPRST_PENDING, &a->flags)) अणु
		अगर (!test_bit(AF_CHPRST_NEEDED, &a->flags) &&
		    !test_bit(AF_CHPRST_DETECTED, &a->flags))
			esas2r_handle_pending_reset(a, currसमय);
	पूर्ण अन्यथा अणु
		अगर (test_bit(AF_DISC_PENDING, &a->flags))
			esas2r_disc_check_complete(a);
		अगर (test_bit(AF_HEARTBEAT_ENB, &a->flags)) अणु
			अगर (test_bit(AF_HEARTBEAT, &a->flags)) अणु
				अगर ((currसमय - a->heartbeat_समय) >=
				    ESAS2R_HEARTBEAT_TIME) अणु
					clear_bit(AF_HEARTBEAT, &a->flags);
					esas2r_hdebug("heartbeat failed");
					esas2r_log(ESAS2R_LOG_CRIT,
						   "heartbeat failed");
					esas2r_bugon();
					esas2r_local_reset_adapter(a);
				पूर्ण
			पूर्ण अन्यथा अणु
				set_bit(AF_HEARTBEAT, &a->flags);
				a->heartbeat_समय = currसमय;
				esas2r_क्रमce_पूर्णांकerrupt(a);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
		esas2r_करो_deferred_processes(a);
पूर्ण

/*
 * Send the specअगरied task management function to the target and LUN
 * specअगरied in rqaux.  in addition, immediately पात any commands that
 * are queued but not sent to the device according to the rules specअगरied
 * by the task management function.
 */
bool esas2r_send_task_mgmt(काष्ठा esas2r_adapter *a,
			   काष्ठा esas2r_request *rqaux, u8 task_mgt_func)
अणु
	u16 targetid = rqaux->target_id;
	u8 lun = (u8)le32_to_cpu(rqaux->vrq->scsi.flags);
	bool ret = false;
	काष्ठा esas2r_request *rq;
	काष्ठा list_head *next, *element;
	अचिन्हित दीर्घ flags;

	LIST_HEAD(comp_list);

	esas2r_trace_enter();
	esas2r_trace("rqaux:%p", rqaux);
	esas2r_trace("task_mgt_func:%x", task_mgt_func);
	spin_lock_irqsave(&a->queue_lock, flags);

	/* search the defer queue looking क्रम requests क्रम the device */
	list_क्रम_each_safe(element, next, &a->defer_list) अणु
		rq = list_entry(element, काष्ठा esas2r_request, req_list);

		अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI
		    && rq->target_id == targetid
		    && (((u8)le32_to_cpu(rq->vrq->scsi.flags)) == lun
			|| task_mgt_func == 0x20)) अणु /* target reset */
			/* Found a request affected by the task management */
			अगर (rq->req_stat == RS_PENDING) अणु
				/*
				 * The request is pending or रुकोing.  We can
				 * safelycomplete the request now.
				 */
				अगर (esas2r_ioreq_पातed(a, rq, RS_ABORTED))
					list_add_tail(&rq->comp_list,
						      &comp_list);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Send the task management request to the firmware */
	rqaux->sense_len = 0;
	rqaux->vrq->scsi.length = 0;
	rqaux->target_id = targetid;
	rqaux->vrq->scsi.flags |= cpu_to_le32(lun);
	स_रखो(rqaux->vrq->scsi.cdb, 0, माप(rqaux->vrq->scsi.cdb));
	rqaux->vrq->scsi.flags |=
		cpu_to_le16(task_mgt_func * LOBIT(FCP_CMND_TM_MASK));

	अगर (test_bit(AF_FLASHING, &a->flags)) अणु
		/* Assume success.  अगर there are active requests, वापस busy */
		rqaux->req_stat = RS_SUCCESS;

		list_क्रम_each_safe(element, next, &a->active_list) अणु
			rq = list_entry(element, काष्ठा esas2r_request,
					req_list);
			अगर (rq->vrq->scsi.function == VDA_FUNC_SCSI
			    && rq->target_id == targetid
			    && (((u8)le32_to_cpu(rq->vrq->scsi.flags)) == lun
				|| task_mgt_func == 0x20))  /* target reset */
				rqaux->req_stat = RS_BUSY;
		पूर्ण

		ret = true;
	पूर्ण

	spin_unlock_irqrestore(&a->queue_lock, flags);

	अगर (!test_bit(AF_FLASHING, &a->flags))
		esas2r_start_request(a, rqaux);

	esas2r_comp_list_drain(a, &comp_list);

	अगर (atomic_पढ़ो(&a->disable_cnt) == 0)
		esas2r_करो_deferred_processes(a);

	esas2r_trace_निकास();

	वापस ret;
पूर्ण

व्योम esas2r_reset_bus(काष्ठा esas2r_adapter *a)
अणु
	esas2r_log(ESAS2R_LOG_INFO, "performing a bus reset");

	अगर (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
	    !test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_DISC_PENDING, &a->flags)) अणु
		set_bit(AF_BUSRST_NEEDED, &a->flags);
		set_bit(AF_BUSRST_PENDING, &a->flags);
		set_bit(AF_OS_RESET, &a->flags);

		esas2r_schedule_tasklet(a);
	पूर्ण
पूर्ण

bool esas2r_ioreq_पातed(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			  u8 status)
अणु
	esas2r_trace_enter();
	esas2r_trace("rq:%p", rq);
	list_del_init(&rq->req_list);
	अगर (rq->समयout > RQ_MAX_TIMEOUT) अणु
		/*
		 * The request समयd out, but we could not पात it because a
		 * chip reset occurred.  Return busy status.
		 */
		rq->req_stat = RS_BUSY;
		esas2r_trace_निकास();
		वापस true;
	पूर्ण

	rq->req_stat = status;
	esas2r_trace_निकास();
	वापस true;
पूर्ण
