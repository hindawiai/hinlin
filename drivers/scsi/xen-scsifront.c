<शैली गुरु>
/*
 * Xen SCSI frontend driver
 *
 * Copyright (c) 2008, FUJITSU Limited
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pfn.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>

#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/io/vscsiअगर.h>
#समावेश <xen/पूर्णांकerface/io/protocols.h>

#समावेश <यंत्र/xen/hypervisor.h>


#घोषणा GRANT_INVALID_REF	0

#घोषणा VSCSIFRONT_OP_ADD_LUN	1
#घोषणा VSCSIFRONT_OP_DEL_LUN	2
#घोषणा VSCSIFRONT_OP_READD_LUN	3

/* Tuning poपूर्णांक. */
#घोषणा VSCSIIF_DEFAULT_CMD_PER_LUN 10
#घोषणा VSCSIIF_MAX_TARGET          64
#घोषणा VSCSIIF_MAX_LUN             255

#घोषणा VSCSIIF_RING_SIZE	__CONST_RING_SIZE(vscsiअगर, PAGE_SIZE)
#घोषणा VSCSIIF_MAX_REQS	VSCSIIF_RING_SIZE

#घोषणा vscsiअगर_grants_sg(_sg)	(PFN_UP((_sg) *		\
				माप(काष्ठा scsiअगर_request_segment)))

काष्ठा vscsअगरrnt_shaकरोw अणु
	/* command between backend and frontend */
	अचिन्हित अक्षर act;
	uपूर्णांक8_t nr_segments;
	uपूर्णांक16_t rqid;
	uपूर्णांक16_t ref_rqid;

	अचिन्हित पूर्णांक nr_grants;		/* number of grants in gref[] */
	काष्ठा scsiअगर_request_segment *sg;	/* scatter/gather elements */
	काष्ठा scsiअगर_request_segment seg[VSCSIIF_SG_TABLESIZE];

	/* Do reset or पात function. */
	रुको_queue_head_t wq_reset;	/* reset work queue           */
	पूर्णांक रुको_reset;			/* reset work queue condition */
	पूर्णांक32_t rslt_reset;		/* reset response status:     */
					/* SUCCESS or FAILED or:      */
#घोषणा RSLT_RESET_WAITING	0
#घोषणा RSLT_RESET_ERR		-1

	/* Requested काष्ठा scsi_cmnd is stored from kernel. */
	काष्ठा scsi_cmnd *sc;
	पूर्णांक gref[vscsiअगर_grants_sg(SG_ALL) + SG_ALL];
पूर्ण;

काष्ठा vscsअगरrnt_info अणु
	काष्ठा xenbus_device *dev;

	काष्ठा Scsi_Host *host;
	पूर्णांक host_active;

	अचिन्हित पूर्णांक evtchn;
	अचिन्हित पूर्णांक irq;

	grant_ref_t ring_ref;
	काष्ठा vscsiअगर_front_ring ring;
	काष्ठा vscsiअगर_response	ring_rsp;

	spinlock_t shaकरोw_lock;
	DECLARE_BITMAP(shaकरोw_मुक्त_biपंचांगap, VSCSIIF_MAX_REQS);
	काष्ठा vscsअगरrnt_shaकरोw *shaकरोw[VSCSIIF_MAX_REQS];

	/* Following items are रक्षित by the host lock. */
	रुको_queue_head_t wq_sync;
	रुको_queue_head_t wq_छोड़ो;
	अचिन्हित पूर्णांक रुको_ring_available:1;
	अचिन्हित पूर्णांक रुकोing_छोड़ो:1;
	अचिन्हित पूर्णांक छोड़ो:1;
	अचिन्हित callers;

	अक्षर dev_state_path[64];
	काष्ठा task_काष्ठा *curr;
पूर्ण;

अटल DEFINE_MUTEX(scsअगरront_mutex);

अटल व्योम scsअगरront_wake_up(काष्ठा vscsअगरrnt_info *info)
अणु
	info->रुको_ring_available = 0;
	wake_up(&info->wq_sync);
पूर्ण

अटल पूर्णांक scsअगरront_get_rqid(काष्ठा vscsअगरrnt_info *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक मुक्त;

	spin_lock_irqsave(&info->shaकरोw_lock, flags);

	मुक्त = find_first_bit(info->shaकरोw_मुक्त_biपंचांगap, VSCSIIF_MAX_REQS);
	__clear_bit(मुक्त, info->shaकरोw_मुक्त_biपंचांगap);

	spin_unlock_irqrestore(&info->shaकरोw_lock, flags);

	वापस मुक्त;
पूर्ण

अटल पूर्णांक _scsअगरront_put_rqid(काष्ठा vscsअगरrnt_info *info, uपूर्णांक32_t id)
अणु
	पूर्णांक empty = biपंचांगap_empty(info->shaकरोw_मुक्त_biपंचांगap, VSCSIIF_MAX_REQS);

	__set_bit(id, info->shaकरोw_मुक्त_biपंचांगap);
	info->shaकरोw[id] = शून्य;

	वापस empty || info->रुको_ring_available;
पूर्ण

अटल व्योम scsअगरront_put_rqid(काष्ठा vscsअगरrnt_info *info, uपूर्णांक32_t id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक kick;

	spin_lock_irqsave(&info->shaकरोw_lock, flags);
	kick = _scsअगरront_put_rqid(info, id);
	spin_unlock_irqrestore(&info->shaकरोw_lock, flags);

	अगर (kick)
		scsअगरront_wake_up(info);
पूर्ण

अटल पूर्णांक scsअगरront_करो_request(काष्ठा vscsअगरrnt_info *info,
				काष्ठा vscsअगरrnt_shaकरोw *shaकरोw)
अणु
	काष्ठा vscsiअगर_front_ring *ring = &(info->ring);
	काष्ठा vscsiअगर_request *ring_req;
	काष्ठा scsi_cmnd *sc = shaकरोw->sc;
	uपूर्णांक32_t id;
	पूर्णांक i, notअगरy;

	अगर (RING_FULL(&info->ring))
		वापस -EBUSY;

	id = scsअगरront_get_rqid(info);	/* use id in response */
	अगर (id >= VSCSIIF_MAX_REQS)
		वापस -EBUSY;

	info->shaकरोw[id] = shaकरोw;
	shaकरोw->rqid = id;

	ring_req = RING_GET_REQUEST(&(info->ring), ring->req_prod_pvt);
	ring->req_prod_pvt++;

	ring_req->rqid        = id;
	ring_req->act         = shaकरोw->act;
	ring_req->ref_rqid    = shaकरोw->ref_rqid;
	ring_req->nr_segments = shaकरोw->nr_segments;

	ring_req->id      = sc->device->id;
	ring_req->lun     = sc->device->lun;
	ring_req->channel = sc->device->channel;
	ring_req->cmd_len = sc->cmd_len;

	BUG_ON(sc->cmd_len > VSCSIIF_MAX_COMMAND_SIZE);

	स_नकल(ring_req->cmnd, sc->cmnd, sc->cmd_len);

	ring_req->sc_data_direction   = (uपूर्णांक8_t)sc->sc_data_direction;
	ring_req->समयout_per_command = sc->request->समयout / HZ;

	क्रम (i = 0; i < (shaकरोw->nr_segments & ~VSCSIIF_SG_GRANT); i++)
		ring_req->seg[i] = shaकरोw->seg[i];

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(ring, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(info->irq);

	वापस 0;
पूर्ण

अटल व्योम scsअगरront_gnttab_करोne(काष्ठा vscsअगरrnt_info *info,
				  काष्ठा vscsअगरrnt_shaकरोw *shaकरोw)
अणु
	पूर्णांक i;

	अगर (shaकरोw->sc->sc_data_direction == DMA_NONE)
		वापस;

	क्रम (i = 0; i < shaकरोw->nr_grants; i++) अणु
		अगर (unlikely(gnttab_query_क्रमeign_access(shaकरोw->gref[i]))) अणु
			shost_prपूर्णांकk(KERN_ALERT, info->host, KBUILD_MODNAME
				     "grant still in use by backend\n");
			BUG();
		पूर्ण
		gnttab_end_क्रमeign_access(shaकरोw->gref[i], 0, 0UL);
	पूर्ण

	kमुक्त(shaकरोw->sg);
पूर्ण

अटल व्योम scsअगरront_cdb_cmd_करोne(काष्ठा vscsअगरrnt_info *info,
				   काष्ठा vscsiअगर_response *ring_rsp)
अणु
	काष्ठा vscsअगरrnt_shaकरोw *shaकरोw;
	काष्ठा scsi_cmnd *sc;
	uपूर्णांक32_t id;
	uपूर्णांक8_t sense_len;

	id = ring_rsp->rqid;
	shaकरोw = info->shaकरोw[id];
	sc = shaकरोw->sc;

	BUG_ON(sc == शून्य);

	scsअगरront_gnttab_करोne(info, shaकरोw);
	scsअगरront_put_rqid(info, id);

	sc->result = ring_rsp->rslt;
	scsi_set_resid(sc, ring_rsp->residual_len);

	sense_len = min_t(uपूर्णांक8_t, VSCSIIF_SENSE_BUFFERSIZE,
			  ring_rsp->sense_len);

	अगर (sense_len)
		स_नकल(sc->sense_buffer, ring_rsp->sense_buffer, sense_len);

	sc->scsi_करोne(sc);
पूर्ण

अटल व्योम scsअगरront_sync_cmd_करोne(काष्ठा vscsअगरrnt_info *info,
				    काष्ठा vscsiअगर_response *ring_rsp)
अणु
	uपूर्णांक16_t id = ring_rsp->rqid;
	अचिन्हित दीर्घ flags;
	काष्ठा vscsअगरrnt_shaकरोw *shaकरोw = info->shaकरोw[id];
	पूर्णांक kick;

	spin_lock_irqsave(&info->shaकरोw_lock, flags);
	shaकरोw->रुको_reset = 1;
	चयन (shaकरोw->rslt_reset) अणु
	हाल RSLT_RESET_WAITING:
		shaकरोw->rslt_reset = ring_rsp->rslt;
		अवरोध;
	हाल RSLT_RESET_ERR:
		kick = _scsअगरront_put_rqid(info, id);
		spin_unlock_irqrestore(&info->shaकरोw_lock, flags);
		kमुक्त(shaकरोw);
		अगर (kick)
			scsअगरront_wake_up(info);
		वापस;
	शेष:
		shost_prपूर्णांकk(KERN_ERR, info->host, KBUILD_MODNAME
			     "bad reset state %d, possibly leaking %u\n",
			     shaकरोw->rslt_reset, id);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&info->shaकरोw_lock, flags);

	wake_up(&shaकरोw->wq_reset);
पूर्ण

अटल व्योम scsअगरront_करो_response(काष्ठा vscsअगरrnt_info *info,
				  काष्ठा vscsiअगर_response *ring_rsp)
अणु
	अगर (WARN(ring_rsp->rqid >= VSCSIIF_MAX_REQS ||
		 test_bit(ring_rsp->rqid, info->shaकरोw_मुक्त_biपंचांगap),
		 "illegal rqid %u returned by backend!\n", ring_rsp->rqid))
		वापस;

	अगर (info->shaकरोw[ring_rsp->rqid]->act == VSCSIIF_ACT_SCSI_CDB)
		scsअगरront_cdb_cmd_करोne(info, ring_rsp);
	अन्यथा
		scsअगरront_sync_cmd_करोne(info, ring_rsp);
पूर्ण

अटल पूर्णांक scsअगरront_ring_drain(काष्ठा vscsअगरrnt_info *info)
अणु
	काष्ठा vscsiअगर_response *ring_rsp;
	RING_IDX i, rp;
	पूर्णांक more_to_करो = 0;

	rp = info->ring.sring->rsp_prod;
	rmb();	/* ordering required respective to करोm0 */
	क्रम (i = info->ring.rsp_cons; i != rp; i++) अणु
		ring_rsp = RING_GET_RESPONSE(&info->ring, i);
		scsअगरront_करो_response(info, ring_rsp);
	पूर्ण

	info->ring.rsp_cons = i;

	अगर (i != info->ring.req_prod_pvt)
		RING_FINAL_CHECK_FOR_RESPONSES(&info->ring, more_to_करो);
	अन्यथा
		info->ring.sring->rsp_event = i + 1;

	वापस more_to_करो;
पूर्ण

अटल पूर्णांक scsअगरront_cmd_करोne(काष्ठा vscsअगरrnt_info *info)
अणु
	पूर्णांक more_to_करो;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(info->host->host_lock, flags);

	more_to_करो = scsअगरront_ring_drain(info);

	info->रुको_ring_available = 0;

	spin_unlock_irqrestore(info->host->host_lock, flags);

	wake_up(&info->wq_sync);

	वापस more_to_करो;
पूर्ण

अटल irqवापस_t scsअगरront_irq_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vscsअगरrnt_info *info = dev_id;

	जबतक (scsअगरront_cmd_करोne(info))
		/* Yield poपूर्णांक क्रम this unbounded loop. */
		cond_resched();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम scsअगरront_finish_all(काष्ठा vscsअगरrnt_info *info)
अणु
	अचिन्हित i;
	काष्ठा vscsiअगर_response resp;

	scsअगरront_ring_drain(info);

	क्रम (i = 0; i < VSCSIIF_MAX_REQS; i++) अणु
		अगर (test_bit(i, info->shaकरोw_मुक्त_biपंचांगap))
			जारी;
		resp.rqid = i;
		resp.sense_len = 0;
		resp.rslt = DID_RESET << 16;
		resp.residual_len = 0;
		scsअगरront_करो_response(info, &resp);
	पूर्ण
पूर्ण

अटल पूर्णांक map_data_क्रम_request(काष्ठा vscsअगरrnt_info *info,
				काष्ठा scsi_cmnd *sc,
				काष्ठा vscsअगरrnt_shaकरोw *shaकरोw)
अणु
	grant_ref_t gref_head;
	काष्ठा page *page;
	पूर्णांक err, ref, ref_cnt = 0;
	पूर्णांक grant_ro = (sc->sc_data_direction == DMA_TO_DEVICE);
	अचिन्हित पूर्णांक i, off, len, bytes;
	अचिन्हित पूर्णांक data_len = scsi_bufflen(sc);
	अचिन्हित पूर्णांक data_grants = 0, seg_grants = 0;
	काष्ठा scatterlist *sg;
	काष्ठा scsiअगर_request_segment *seg;

	अगर (sc->sc_data_direction == DMA_NONE || !data_len)
		वापस 0;

	scsi_क्रम_each_sg(sc, sg, scsi_sg_count(sc), i)
		data_grants += PFN_UP(sg->offset + sg->length);

	अगर (data_grants > VSCSIIF_SG_TABLESIZE) अणु
		अगर (data_grants > info->host->sg_tablesize) अणु
			shost_prपूर्णांकk(KERN_ERR, info->host, KBUILD_MODNAME
			     "Unable to map request_buffer for command!\n");
			वापस -E2BIG;
		पूर्ण
		seg_grants = vscsiअगर_grants_sg(data_grants);
		shaकरोw->sg = kसुस्मृति(data_grants,
			माप(काष्ठा scsiअगर_request_segment), GFP_ATOMIC);
		अगर (!shaकरोw->sg)
			वापस -ENOMEM;
	पूर्ण
	seg = shaकरोw->sg ? : shaकरोw->seg;

	err = gnttab_alloc_grant_references(seg_grants + data_grants,
					    &gref_head);
	अगर (err) अणु
		kमुक्त(shaकरोw->sg);
		shost_prपूर्णांकk(KERN_ERR, info->host, KBUILD_MODNAME
			     "gnttab_alloc_grant_references() error\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (seg_grants) अणु
		page = virt_to_page(seg);
		off = offset_in_page(seg);
		len = माप(काष्ठा scsiअगर_request_segment) * data_grants;
		जबतक (len > 0) अणु
			bytes = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE - off);

			ref = gnttab_claim_grant_reference(&gref_head);
			BUG_ON(ref == -ENOSPC);

			gnttab_grant_क्रमeign_access_ref(ref,
				info->dev->otherend_id,
				xen_page_to_gfn(page), 1);
			shaकरोw->gref[ref_cnt] = ref;
			shaकरोw->seg[ref_cnt].gref   = ref;
			shaकरोw->seg[ref_cnt].offset = (uपूर्णांक16_t)off;
			shaकरोw->seg[ref_cnt].length = (uपूर्णांक16_t)bytes;

			page++;
			len -= bytes;
			off = 0;
			ref_cnt++;
		पूर्ण
		BUG_ON(seg_grants < ref_cnt);
		seg_grants = ref_cnt;
	पूर्ण

	scsi_क्रम_each_sg(sc, sg, scsi_sg_count(sc), i) अणु
		page = sg_page(sg);
		off = sg->offset;
		len = sg->length;

		जबतक (len > 0 && data_len > 0) अणु
			/*
			 * sg sends a scatterlist that is larger than
			 * the data_len it wants transferred क्रम certain
			 * IO sizes.
			 */
			bytes = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE - off);
			bytes = min(bytes, data_len);

			ref = gnttab_claim_grant_reference(&gref_head);
			BUG_ON(ref == -ENOSPC);

			gnttab_grant_क्रमeign_access_ref(ref,
				info->dev->otherend_id,
				xen_page_to_gfn(page),
				grant_ro);

			shaकरोw->gref[ref_cnt] = ref;
			seg->gref   = ref;
			seg->offset = (uपूर्णांक16_t)off;
			seg->length = (uपूर्णांक16_t)bytes;

			page++;
			seg++;
			len -= bytes;
			data_len -= bytes;
			off = 0;
			ref_cnt++;
		पूर्ण
	पूर्ण

	अगर (seg_grants)
		shaकरोw->nr_segments = VSCSIIF_SG_GRANT | seg_grants;
	अन्यथा
		shaकरोw->nr_segments = (uपूर्णांक8_t)ref_cnt;
	shaकरोw->nr_grants = ref_cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक scsअगरront_enter(काष्ठा vscsअगरrnt_info *info)
अणु
	अगर (info->छोड़ो)
		वापस 1;
	info->callers++;
	वापस 0;
पूर्ण

अटल व्योम scsअगरront_वापस(काष्ठा vscsअगरrnt_info *info)
अणु
	info->callers--;
	अगर (info->callers)
		वापस;

	अगर (!info->रुकोing_छोड़ो)
		वापस;

	info->रुकोing_छोड़ो = 0;
	wake_up(&info->wq_छोड़ो);
पूर्ण

अटल पूर्णांक scsअगरront_queuecommand(काष्ठा Scsi_Host *shost,
				  काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा vscsअगरrnt_info *info = shost_priv(shost);
	काष्ठा vscsअगरrnt_shaकरोw *shaकरोw = scsi_cmd_priv(sc);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	sc->result = 0;

	shaकरोw->sc  = sc;
	shaकरोw->act = VSCSIIF_ACT_SCSI_CDB;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (scsअगरront_enter(info)) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	err = map_data_क्रम_request(info, sc, shaकरोw);
	अगर (err < 0) अणु
		pr_debug("%s: err %d\n", __func__, err);
		scsअगरront_वापस(info);
		spin_unlock_irqrestore(shost->host_lock, flags);
		अगर (err == -ENOMEM)
			वापस SCSI_MLQUEUE_HOST_BUSY;
		sc->result = DID_ERROR << 16;
		sc->scsi_करोne(sc);
		वापस 0;
	पूर्ण

	अगर (scsअगरront_करो_request(info, shaकरोw)) अणु
		scsअगरront_gnttab_करोne(info, shaकरोw);
		जाओ busy;
	पूर्ण

	scsअगरront_वापस(info);
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस 0;

busy:
	scsअगरront_वापस(info);
	spin_unlock_irqrestore(shost->host_lock, flags);
	pr_debug("%s: busy\n", __func__);
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

/*
 * Any exception handling (reset or पात) must be क्रमwarded to the backend.
 * We have to रुको until an answer is वापसed. This answer contains the
 * result to be वापसed to the requestor.
 */
अटल पूर्णांक scsअगरront_action_handler(काष्ठा scsi_cmnd *sc, uपूर्णांक8_t act)
अणु
	काष्ठा Scsi_Host *host = sc->device->host;
	काष्ठा vscsअगरrnt_info *info = shost_priv(host);
	काष्ठा vscsअगरrnt_shaकरोw *shaकरोw, *s = scsi_cmd_priv(sc);
	पूर्णांक err = 0;

	shaकरोw = kzalloc(माप(*shaकरोw), GFP_NOIO);
	अगर (!shaकरोw)
		वापस FAILED;

	shaकरोw->act = act;
	shaकरोw->rslt_reset = RSLT_RESET_WAITING;
	shaकरोw->sc = sc;
	shaकरोw->ref_rqid = s->rqid;
	init_रुकोqueue_head(&shaकरोw->wq_reset);

	spin_lock_irq(host->host_lock);

	क्रम (;;) अणु
		अगर (scsअगरront_enter(info))
			जाओ fail;

		अगर (!scsअगरront_करो_request(info, shaकरोw))
			अवरोध;

		scsअगरront_वापस(info);
		अगर (err)
			जाओ fail;
		info->रुको_ring_available = 1;
		spin_unlock_irq(host->host_lock);
		err = रुको_event_पूर्णांकerruptible(info->wq_sync,
					       !info->रुको_ring_available);
		spin_lock_irq(host->host_lock);
	पूर्ण

	spin_unlock_irq(host->host_lock);
	err = रुको_event_पूर्णांकerruptible(shaकरोw->wq_reset, shaकरोw->रुको_reset);
	spin_lock_irq(host->host_lock);

	अगर (!err) अणु
		err = shaकरोw->rslt_reset;
		scsअगरront_put_rqid(info, shaकरोw->rqid);
		kमुक्त(shaकरोw);
	पूर्ण अन्यथा अणु
		spin_lock(&info->shaकरोw_lock);
		shaकरोw->rslt_reset = RSLT_RESET_ERR;
		spin_unlock(&info->shaकरोw_lock);
		err = FAILED;
	पूर्ण

	scsअगरront_वापस(info);
	spin_unlock_irq(host->host_lock);
	वापस err;

fail:
	spin_unlock_irq(host->host_lock);
	kमुक्त(shaकरोw);
	वापस FAILED;
पूर्ण

अटल पूर्णांक scsअगरront_eh_पात_handler(काष्ठा scsi_cmnd *sc)
अणु
	pr_debug("%s\n", __func__);
	वापस scsअगरront_action_handler(sc, VSCSIIF_ACT_SCSI_ABORT);
पूर्ण

अटल पूर्णांक scsअगरront_dev_reset_handler(काष्ठा scsi_cmnd *sc)
अणु
	pr_debug("%s\n", __func__);
	वापस scsअगरront_action_handler(sc, VSCSIIF_ACT_SCSI_RESET);
पूर्ण

अटल पूर्णांक scsअगरront_sdev_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा vscsअगरrnt_info *info = shost_priv(sdev->host);
	पूर्णांक err;

	अगर (info && current == info->curr) अणु
		err = xenbus_म_लिखो(XBT_NIL, info->dev->nodename,
			      info->dev_state_path, "%d", XenbusStateConnected);
		अगर (err) अणु
			xenbus_dev_error(info->dev, err,
				"%s: writing dev_state_path", __func__);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scsअगरront_sdev_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा vscsअगरrnt_info *info = shost_priv(sdev->host);
	पूर्णांक err;

	अगर (info && current == info->curr) अणु
		err = xenbus_म_लिखो(XBT_NIL, info->dev->nodename,
			      info->dev_state_path, "%d", XenbusStateClosed);
		अगर (err)
			xenbus_dev_error(info->dev, err,
				"%s: writing dev_state_path", __func__);
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा scsअगरront_sht = अणु
	.module			= THIS_MODULE,
	.name			= "Xen SCSI frontend driver",
	.queuecommand		= scsअगरront_queuecommand,
	.eh_पात_handler	= scsअगरront_eh_पात_handler,
	.eh_device_reset_handler = scsअगरront_dev_reset_handler,
	.slave_configure	= scsअगरront_sdev_configure,
	.slave_destroy		= scsअगरront_sdev_destroy,
	.cmd_per_lun		= VSCSIIF_DEFAULT_CMD_PER_LUN,
	.can_queue		= VSCSIIF_MAX_REQS,
	.this_id		= -1,
	.cmd_size		= माप(काष्ठा vscsअगरrnt_shaकरोw),
	.sg_tablesize		= VSCSIIF_SG_TABLESIZE,
	.proc_name		= "scsifront",
पूर्ण;

अटल पूर्णांक scsअगरront_alloc_ring(काष्ठा vscsअगरrnt_info *info)
अणु
	काष्ठा xenbus_device *dev = info->dev;
	काष्ठा vscsiअगर_sring *sring;
	grant_ref_t gref;
	पूर्णांक err = -ENOMEM;

	/***** Frontend to Backend ring start *****/
	sring = (काष्ठा vscsiअगर_sring *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!sring) अणु
		xenbus_dev_fatal(dev, err,
			"fail to allocate shared ring (Front to Back)");
		वापस err;
	पूर्ण
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&info->ring, sring, PAGE_SIZE);

	err = xenbus_grant_ring(dev, sring, 1, &gref);
	अगर (err < 0) अणु
		मुक्त_page((अचिन्हित दीर्घ)sring);
		xenbus_dev_fatal(dev, err,
			"fail to grant shared ring (Front to Back)");
		वापस err;
	पूर्ण
	info->ring_ref = gref;

	err = xenbus_alloc_evtchn(dev, &info->evtchn);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "xenbus_alloc_evtchn");
		जाओ मुक्त_gnttab;
	पूर्ण

	err = bind_evtchn_to_irq(info->evtchn);
	अगर (err <= 0) अणु
		xenbus_dev_fatal(dev, err, "bind_evtchn_to_irq");
		जाओ मुक्त_gnttab;
	पूर्ण

	info->irq = err;

	err = request_thपढ़ोed_irq(info->irq, शून्य, scsअगरront_irq_fn,
				   IRQF_ONESHOT, "scsifront", info);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "request_threaded_irq");
		जाओ मुक्त_irq;
	पूर्ण

	वापस 0;

/* मुक्त resource */
मुक्त_irq:
	unbind_from_irqhandler(info->irq, info);
मुक्त_gnttab:
	gnttab_end_क्रमeign_access(info->ring_ref, 0,
				  (अचिन्हित दीर्घ)info->ring.sring);

	वापस err;
पूर्ण

अटल व्योम scsअगरront_मुक्त_ring(काष्ठा vscsअगरrnt_info *info)
अणु
	unbind_from_irqhandler(info->irq, info);
	gnttab_end_क्रमeign_access(info->ring_ref, 0,
				  (अचिन्हित दीर्घ)info->ring.sring);
पूर्ण

अटल पूर्णांक scsअगरront_init_ring(काष्ठा vscsअगरrnt_info *info)
अणु
	काष्ठा xenbus_device *dev = info->dev;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;

	pr_debug("%s\n", __func__);

	err = scsअगरront_alloc_ring(info);
	अगर (err)
		वापस err;
	pr_debug("%s: %u %u\n", __func__, info->ring_ref, info->evtchn);

again:
	err = xenbus_transaction_start(&xbt);
	अगर (err)
		xenbus_dev_fatal(dev, err, "starting transaction");

	err = xenbus_म_लिखो(xbt, dev->nodename, "ring-ref", "%u",
			    info->ring_ref);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "%s", "writing ring-ref");
		जाओ fail;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "event-channel", "%u",
			    info->evtchn);

	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "%s", "writing event-channel");
		जाओ fail;
	पूर्ण

	err = xenbus_transaction_end(xbt, 0);
	अगर (err) अणु
		अगर (err == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, err, "completing transaction");
		जाओ मुक्त_sring;
	पूर्ण

	वापस 0;

fail:
	xenbus_transaction_end(xbt, 1);
मुक्त_sring:
	scsअगरront_मुक्त_ring(info);

	वापस err;
पूर्ण


अटल पूर्णांक scsअगरront_probe(काष्ठा xenbus_device *dev,
			   स्थिर काष्ठा xenbus_device_id *id)
अणु
	काष्ठा vscsअगरrnt_info *info;
	काष्ठा Scsi_Host *host;
	पूर्णांक err = -ENOMEM;
	अक्षर name[TASK_COMM_LEN];

	host = scsi_host_alloc(&scsअगरront_sht, माप(*info));
	अगर (!host) अणु
		xenbus_dev_fatal(dev, err, "fail to allocate scsi host");
		वापस err;
	पूर्ण
	info = (काष्ठा vscsअगरrnt_info *)host->hostdata;

	dev_set_drvdata(&dev->dev, info);
	info->dev = dev;

	biपंचांगap_fill(info->shaकरोw_मुक्त_biपंचांगap, VSCSIIF_MAX_REQS);

	err = scsअगरront_init_ring(info);
	अगर (err) अणु
		scsi_host_put(host);
		वापस err;
	पूर्ण

	init_रुकोqueue_head(&info->wq_sync);
	init_रुकोqueue_head(&info->wq_छोड़ो);
	spin_lock_init(&info->shaकरोw_lock);

	snम_लिखो(name, TASK_COMM_LEN, "vscsiif.%d", host->host_no);

	host->max_id      = VSCSIIF_MAX_TARGET;
	host->max_channel = 0;
	host->max_lun     = VSCSIIF_MAX_LUN;
	host->max_sectors = (host->sg_tablesize - 1) * PAGE_SIZE / 512;
	host->max_cmd_len = VSCSIIF_MAX_COMMAND_SIZE;

	err = scsi_add_host(host, &dev->dev);
	अगर (err) अणु
		dev_err(&dev->dev, "fail to add scsi host %d\n", err);
		जाओ मुक्त_sring;
	पूर्ण
	info->host = host;
	info->host_active = 1;

	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;

मुक्त_sring:
	scsअगरront_मुक्त_ring(info);
	scsi_host_put(host);
	वापस err;
पूर्ण

अटल पूर्णांक scsअगरront_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा vscsअगरrnt_info *info = dev_get_drvdata(&dev->dev);
	काष्ठा Scsi_Host *host = info->host;
	पूर्णांक err;

	spin_lock_irq(host->host_lock);

	/* Finish all still pending commands. */
	scsअगरront_finish_all(info);

	spin_unlock_irq(host->host_lock);

	/* Reconnect to करोm0. */
	scsअगरront_मुक्त_ring(info);
	err = scsअगरront_init_ring(info);
	अगर (err) अणु
		dev_err(&dev->dev, "fail to resume %d\n", err);
		scsi_host_put(host);
		वापस err;
	पूर्ण

	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;
पूर्ण

अटल पूर्णांक scsअगरront_suspend(काष्ठा xenbus_device *dev)
अणु
	काष्ठा vscsअगरrnt_info *info = dev_get_drvdata(&dev->dev);
	काष्ठा Scsi_Host *host = info->host;
	पूर्णांक err = 0;

	/* No new commands क्रम the backend. */
	spin_lock_irq(host->host_lock);
	info->छोड़ो = 1;
	जबतक (info->callers && !err) अणु
		info->रुकोing_छोड़ो = 1;
		info->रुको_ring_available = 0;
		spin_unlock_irq(host->host_lock);
		wake_up(&info->wq_sync);
		err = रुको_event_पूर्णांकerruptible(info->wq_छोड़ो,
					       !info->रुकोing_छोड़ो);
		spin_lock_irq(host->host_lock);
	पूर्ण
	spin_unlock_irq(host->host_lock);
	वापस err;
पूर्ण

अटल पूर्णांक scsअगरront_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा vscsअगरrnt_info *info = dev_get_drvdata(&dev->dev);

	pr_debug("%s: %s removed\n", __func__, dev->nodename);

	mutex_lock(&scsअगरront_mutex);
	अगर (info->host_active) अणु
		/* Scsi_host not yet हटाओd */
		scsi_हटाओ_host(info->host);
		info->host_active = 0;
	पूर्ण
	mutex_unlock(&scsअगरront_mutex);

	scsअगरront_मुक्त_ring(info);
	scsi_host_put(info->host);

	वापस 0;
पूर्ण

अटल व्योम scsअगरront_disconnect(काष्ठा vscsअगरrnt_info *info)
अणु
	काष्ठा xenbus_device *dev = info->dev;
	काष्ठा Scsi_Host *host = info->host;

	pr_debug("%s: %s disconnect\n", __func__, dev->nodename);

	/*
	 * When this function is executed, all devices of
	 * Frontend have been deleted.
	 * Thereक्रमe, it need not block I/O beक्रमe हटाओ_host.
	 */

	mutex_lock(&scsअगरront_mutex);
	अगर (info->host_active) अणु
		scsi_हटाओ_host(host);
		info->host_active = 0;
	पूर्ण
	mutex_unlock(&scsअगरront_mutex);

	xenbus_frontend_बंदd(dev);
पूर्ण

अटल व्योम scsअगरront_करो_lun_hotplug(काष्ठा vscsअगरrnt_info *info, पूर्णांक op)
अणु
	काष्ठा xenbus_device *dev = info->dev;
	पूर्णांक i, err = 0;
	अक्षर str[64];
	अक्षर **dir;
	अचिन्हित पूर्णांक dir_n = 0;
	अचिन्हित पूर्णांक device_state;
	अचिन्हित पूर्णांक hst, chn, tgt, lun;
	काष्ठा scsi_device *sdev;

	dir = xenbus_directory(XBT_NIL, dev->otherend, "vscsi-devs", &dir_n);
	अगर (IS_ERR(dir))
		वापस;

	/* mark current task as the one allowed to modअगरy device states */
	BUG_ON(info->curr);
	info->curr = current;

	क्रम (i = 0; i < dir_n; i++) अणु
		/* पढ़ो status */
		snम_लिखो(str, माप(str), "vscsi-devs/%s/state", dir[i]);
		err = xenbus_म_पूछो(XBT_NIL, dev->otherend, str, "%u",
				   &device_state);
		अगर (XENBUS_EXIST_ERR(err))
			जारी;

		/* भव SCSI device */
		snम_लिखो(str, माप(str), "vscsi-devs/%s/v-dev", dir[i]);
		err = xenbus_म_पूछो(XBT_NIL, dev->otherend, str,
				   "%u:%u:%u:%u", &hst, &chn, &tgt, &lun);
		अगर (XENBUS_EXIST_ERR(err))
			जारी;

		/*
		 * Front device state path, used in slave_configure called
		 * on successfull scsi_add_device, and in slave_destroy called
		 * on हटाओ of a device.
		 */
		snम_लिखो(info->dev_state_path, माप(info->dev_state_path),
			 "vscsi-devs/%s/state", dir[i]);

		चयन (op) अणु
		हाल VSCSIFRONT_OP_ADD_LUN:
			अगर (device_state != XenbusStateInitialised)
				अवरोध;

			अगर (scsi_add_device(info->host, chn, tgt, lun)) अणु
				dev_err(&dev->dev, "scsi_add_device\n");
				err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
					      info->dev_state_path,
					      "%d", XenbusStateClosed);
				अगर (err)
					xenbus_dev_error(dev, err,
						"%s: writing dev_state_path", __func__);
			पूर्ण
			अवरोध;
		हाल VSCSIFRONT_OP_DEL_LUN:
			अगर (device_state != XenbusStateClosing)
				अवरोध;

			sdev = scsi_device_lookup(info->host, chn, tgt, lun);
			अगर (sdev) अणु
				scsi_हटाओ_device(sdev);
				scsi_device_put(sdev);
			पूर्ण
			अवरोध;
		हाल VSCSIFRONT_OP_READD_LUN:
			अगर (device_state == XenbusStateConnected) अणु
				err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
					      info->dev_state_path,
					      "%d", XenbusStateConnected);
				अगर (err)
					xenbus_dev_error(dev, err,
						"%s: writing dev_state_path", __func__);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	info->curr = शून्य;

	kमुक्त(dir);
पूर्ण

अटल व्योम scsअगरront_पढ़ो_backend_params(काष्ठा xenbus_device *dev,
					  काष्ठा vscsअगरrnt_info *info)
अणु
	अचिन्हित पूर्णांक sg_grant, nr_segs;
	काष्ठा Scsi_Host *host = info->host;

	sg_grant = xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-sg-grant", 0);
	nr_segs = min_t(अचिन्हित पूर्णांक, sg_grant, SG_ALL);
	nr_segs = max_t(अचिन्हित पूर्णांक, nr_segs, VSCSIIF_SG_TABLESIZE);
	nr_segs = min_t(अचिन्हित पूर्णांक, nr_segs,
			VSCSIIF_SG_TABLESIZE * PAGE_SIZE /
			माप(काष्ठा scsiअगर_request_segment));

	अगर (!info->छोड़ो && sg_grant)
		dev_info(&dev->dev, "using up to %d SG entries\n", nr_segs);
	अन्यथा अगर (info->छोड़ो && nr_segs < host->sg_tablesize)
		dev_warn(&dev->dev,
			 "SG entries decreased from %d to %u - device may not work properly anymore\n",
			 host->sg_tablesize, nr_segs);

	host->sg_tablesize = nr_segs;
	host->max_sectors = (nr_segs - 1) * PAGE_SIZE / 512;
पूर्ण

अटल व्योम scsअगरront_backend_changed(काष्ठा xenbus_device *dev,
				      क्रमागत xenbus_state backend_state)
अणु
	काष्ठा vscsअगरrnt_info *info = dev_get_drvdata(&dev->dev);

	pr_debug("%s: %p %u %u\n", __func__, dev, dev->state, backend_state);

	चयन (backend_state) अणु
	हाल XenbusStateUnknown:
	हाल XenbusStateInitialising:
	हाल XenbusStateInitWait:
	हाल XenbusStateInitialised:
		अवरोध;

	हाल XenbusStateConnected:
		scsअगरront_पढ़ो_backend_params(dev, info);

		अगर (info->छोड़ो) अणु
			scsअगरront_करो_lun_hotplug(info, VSCSIFRONT_OP_READD_LUN);
			xenbus_चयन_state(dev, XenbusStateConnected);
			info->छोड़ो = 0;
			वापस;
		पूर्ण

		अगर (xenbus_पढ़ो_driver_state(dev->nodename) ==
		    XenbusStateInitialised)
			scsअगरront_करो_lun_hotplug(info, VSCSIFRONT_OP_ADD_LUN);

		अगर (dev->state != XenbusStateConnected)
			xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's Closing state */
	हाल XenbusStateClosing:
		scsअगरront_disconnect(info);
		अवरोध;

	हाल XenbusStateReconfiguring:
		scsअगरront_करो_lun_hotplug(info, VSCSIFRONT_OP_DEL_LUN);
		xenbus_चयन_state(dev, XenbusStateReconfiguring);
		अवरोध;

	हाल XenbusStateReconfigured:
		scsअगरront_करो_lun_hotplug(info, VSCSIFRONT_OP_ADD_LUN);
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id scsअगरront_ids[] = अणु
	अणु "vscsi" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver scsअगरront_driver = अणु
	.ids			= scsअगरront_ids,
	.probe			= scsअगरront_probe,
	.हटाओ			= scsअगरront_हटाओ,
	.resume			= scsअगरront_resume,
	.suspend		= scsअगरront_suspend,
	.otherend_changed	= scsअगरront_backend_changed,
पूर्ण;

अटल पूर्णांक __init scsअगरront_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	वापस xenbus_रेजिस्टर_frontend(&scsअगरront_driver);
पूर्ण
module_init(scsअगरront_init);

अटल व्योम __निकास scsअगरront_निकास(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&scsअगरront_driver);
पूर्ण
module_निकास(scsअगरront_निकास);

MODULE_DESCRIPTION("Xen SCSI frontend driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:vscsi");
MODULE_AUTHOR("Juergen Gross <jgross@suse.com>");
