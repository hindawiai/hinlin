<शैली गुरु>
/*
 * Xen SCSI backend driver
 *
 * Copyright (c) 2008, FUJITSU Limited
 *
 * Based on the blkback driver code.
 * Adaption to kernel taget core infraकाष्ठाure taken from vhost/scsi.c
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

#घोषणा pr_fmt(fmt) "xen-pvscsi: " fmt

#समावेश <मानकतर्क.स>

#समावेश <linux/module.h>
#समावेश <linux/utsname.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/configfs.h>

#समावेश <generated/utsrelease.h>

#समावेश <scsi/scsi_host.h> /* SG_ALL */

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <यंत्र/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/balloon.h>
#समावेश <xen/events.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/page.h>

#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/io/vscsiअगर.h>

#घोषणा VSCSI_VERSION	"v0.1"
#घोषणा VSCSI_NAMELEN	32

काष्ठा ids_tuple अणु
	अचिन्हित पूर्णांक hst;		/* host    */
	अचिन्हित पूर्णांक chn;		/* channel */
	अचिन्हित पूर्णांक tgt;		/* target  */
	अचिन्हित पूर्णांक lun;		/* LUN     */
पूर्ण;

काष्ठा v2p_entry अणु
	काष्ठा ids_tuple v;		/* translate from */
	काष्ठा scsiback_tpg *tpg;	/* translate to   */
	अचिन्हित पूर्णांक lun;
	काष्ठा kref kref;
	काष्ठा list_head l;
पूर्ण;

काष्ठा vscsibk_info अणु
	काष्ठा xenbus_device *dev;

	करोmid_t करोmid;
	अचिन्हित पूर्णांक irq;

	काष्ठा vscsiअगर_back_ring ring;

	spinlock_t ring_lock;
	atomic_t nr_unreplied_reqs;

	spinlock_t v2p_lock;
	काष्ठा list_head v2p_entry_lists;

	रुको_queue_head_t रुकोing_to_मुक्त;

	काष्ठा gnttab_page_cache मुक्त_pages;
पूर्ण;

/* theoretical maximum of grants क्रम one request */
#घोषणा VSCSI_MAX_GRANTS	(SG_ALL + VSCSIIF_SG_TABLESIZE)

/*
 * VSCSI_GRANT_BATCH is the maximum number of grants to be processed in one
 * call to map/unmap grants. Don't choose it too large, as there are arrays
 * with VSCSI_GRANT_BATCH elements allocated on the stack.
 */
#घोषणा VSCSI_GRANT_BATCH	16

काष्ठा vscsibk_pend अणु
	uपूर्णांक16_t rqid;

	uपूर्णांक8_t cmnd[VSCSIIF_MAX_COMMAND_SIZE];
	uपूर्णांक8_t cmd_len;

	uपूर्णांक8_t sc_data_direction;
	uपूर्णांक16_t n_sg;		/* real length of SG list */
	uपूर्णांक16_t n_grants;	/* SG pages and potentially SG list */
	uपूर्णांक32_t data_len;
	uपूर्णांक32_t result;

	काष्ठा vscsibk_info *info;
	काष्ठा v2p_entry *v2p;
	काष्ठा scatterlist *sgl;

	uपूर्णांक8_t sense_buffer[VSCSIIF_SENSE_BUFFERSIZE];

	grant_handle_t grant_handles[VSCSI_MAX_GRANTS];
	काष्ठा page *pages[VSCSI_MAX_GRANTS];

	काष्ठा se_cmd se_cmd;

	काष्ठा completion पंचांगr_करोne;
पूर्ण;

#घोषणा VSCSI_DEFAULT_SESSION_TAGS	128

काष्ठा scsiback_nexus अणु
	/* Poपूर्णांकer to TCM session क्रम I_T Nexus */
	काष्ठा se_session *tvn_se_sess;
पूर्ण;

काष्ठा scsiback_tport अणु
	/* SCSI protocol the tport is providing */
	u8 tport_proto_id;
	/* Binary World Wide unique Port Name क्रम pvscsi Target port */
	u64 tport_wwpn;
	/* ASCII क्रमmatted WWPN क्रम pvscsi Target port */
	अक्षर tport_name[VSCSI_NAMELEN];
	/* Returned by scsiback_make_tport() */
	काष्ठा se_wwn tport_wwn;
पूर्ण;

काष्ठा scsiback_tpg अणु
	/* scsiback port target portal group tag क्रम TCM */
	u16 tport_tpgt;
	/* track number of TPG Port/Lun Links wrt explicit I_T Nexus shutकरोwn */
	पूर्णांक tv_tpg_port_count;
	/* xen-pvscsi references to tpg_nexus, रक्षित by tv_tpg_mutex */
	पूर्णांक tv_tpg_fe_count;
	/* list क्रम scsiback_list */
	काष्ठा list_head tv_tpg_list;
	/* Used to protect access क्रम tpg_nexus */
	काष्ठा mutex tv_tpg_mutex;
	/* Poपूर्णांकer to the TCM pvscsi I_T Nexus क्रम this TPG endpoपूर्णांक */
	काष्ठा scsiback_nexus *tpg_nexus;
	/* Poपूर्णांकer back to scsiback_tport */
	काष्ठा scsiback_tport *tport;
	/* Returned by scsiback_make_tpg() */
	काष्ठा se_portal_group se_tpg;
	/* alias used in xenstore */
	अक्षर param_alias[VSCSI_NAMELEN];
	/* list of info काष्ठाures related to this target portal group */
	काष्ठा list_head info_list;
पूर्ण;

#घोषणा SCSIBACK_INVALID_HANDLE (~0)

अटल bool log_prपूर्णांक_stat;
module_param(log_prपूर्णांक_stat, bool, 0644);

अटल पूर्णांक scsiback_max_buffer_pages = 1024;
module_param_named(max_buffer_pages, scsiback_max_buffer_pages, पूर्णांक, 0644);
MODULE_PARM_DESC(max_buffer_pages,
"Maximum number of free pages to keep in backend buffer");

/* Global spinlock to protect scsiback TPG list */
अटल DEFINE_MUTEX(scsiback_mutex);
अटल LIST_HEAD(scsiback_list);

अटल व्योम scsiback_get(काष्ठा vscsibk_info *info)
अणु
	atomic_inc(&info->nr_unreplied_reqs);
पूर्ण

अटल व्योम scsiback_put(काष्ठा vscsibk_info *info)
अणु
	अगर (atomic_dec_and_test(&info->nr_unreplied_reqs))
		wake_up(&info->रुकोing_to_मुक्त);
पूर्ण

अटल अचिन्हित दीर्घ vaddr_page(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);

	वापस (अचिन्हित दीर्घ)pfn_to_kaddr(pfn);
पूर्ण

अटल अचिन्हित दीर्घ vaddr(काष्ठा vscsibk_pend *req, पूर्णांक seg)
अणु
	वापस vaddr_page(req->pages[seg]);
पूर्ण

अटल व्योम scsiback_prपूर्णांक_status(अक्षर *sense_buffer, पूर्णांक errors,
					काष्ठा vscsibk_pend *pending_req)
अणु
	काष्ठा scsiback_tpg *tpg = pending_req->v2p->tpg;

	pr_err("[%s:%d] cmnd[0]=%02x -> st=%02x msg=%02x host=%02x drv=%02x\n",
	       tpg->tport->tport_name, pending_req->v2p->lun,
	       pending_req->cmnd[0], status_byte(errors), msg_byte(errors),
	       host_byte(errors), driver_byte(errors));
पूर्ण

अटल व्योम scsiback_fast_flush_area(काष्ठा vscsibk_pend *req)
अणु
	काष्ठा gnttab_unmap_grant_ref unmap[VSCSI_GRANT_BATCH];
	काष्ठा page *pages[VSCSI_GRANT_BATCH];
	अचिन्हित पूर्णांक i, invcount = 0;
	grant_handle_t handle;
	पूर्णांक err;

	kमुक्त(req->sgl);
	req->sgl = शून्य;
	req->n_sg = 0;

	अगर (!req->n_grants)
		वापस;

	क्रम (i = 0; i < req->n_grants; i++) अणु
		handle = req->grant_handles[i];
		अगर (handle == SCSIBACK_INVALID_HANDLE)
			जारी;
		gnttab_set_unmap_op(&unmap[invcount], vaddr(req, i),
				    GNTMAP_host_map, handle);
		req->grant_handles[i] = SCSIBACK_INVALID_HANDLE;
		pages[invcount] = req->pages[i];
		put_page(pages[invcount]);
		invcount++;
		अगर (invcount < VSCSI_GRANT_BATCH)
			जारी;
		err = gnttab_unmap_refs(unmap, शून्य, pages, invcount);
		BUG_ON(err);
		invcount = 0;
	पूर्ण

	अगर (invcount) अणु
		err = gnttab_unmap_refs(unmap, शून्य, pages, invcount);
		BUG_ON(err);
	पूर्ण

	gnttab_page_cache_put(&req->info->मुक्त_pages, req->pages,
			      req->n_grants);
	req->n_grants = 0;
पूर्ण

अटल व्योम scsiback_मुक्त_translation_entry(काष्ठा kref *kref)
अणु
	काष्ठा v2p_entry *entry = container_of(kref, काष्ठा v2p_entry, kref);
	काष्ठा scsiback_tpg *tpg = entry->tpg;

	mutex_lock(&tpg->tv_tpg_mutex);
	tpg->tv_tpg_fe_count--;
	mutex_unlock(&tpg->tv_tpg_mutex);

	kमुक्त(entry);
पूर्ण

अटल व्योम scsiback_send_response(काष्ठा vscsibk_info *info,
			अक्षर *sense_buffer, पूर्णांक32_t result, uपूर्णांक32_t resid,
			uपूर्णांक16_t rqid)
अणु
	काष्ठा vscsiअगर_response *ring_res;
	पूर्णांक notअगरy;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित दीर्घ flags;
	अचिन्हित len;

	spin_lock_irqsave(&info->ring_lock, flags);

	ring_res = RING_GET_RESPONSE(&info->ring, info->ring.rsp_prod_pvt);
	info->ring.rsp_prod_pvt++;

	ring_res->rslt   = result;
	ring_res->rqid   = rqid;

	अगर (sense_buffer != शून्य &&
	    scsi_normalize_sense(sense_buffer, VSCSIIF_SENSE_BUFFERSIZE,
				 &sshdr)) अणु
		len = min_t(अचिन्हित, 8 + sense_buffer[7],
			    VSCSIIF_SENSE_BUFFERSIZE);
		स_नकल(ring_res->sense_buffer, sense_buffer, len);
		ring_res->sense_len = len;
	पूर्ण अन्यथा अणु
		ring_res->sense_len = 0;
	पूर्ण

	ring_res->residual_len = resid;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&info->ring, notअगरy);
	spin_unlock_irqrestore(&info->ring_lock, flags);

	अगर (notअगरy)
		notअगरy_remote_via_irq(info->irq);
पूर्ण

अटल व्योम scsiback_करो_resp_with_sense(अक्षर *sense_buffer, पूर्णांक32_t result,
			uपूर्णांक32_t resid, काष्ठा vscsibk_pend *pending_req)
अणु
	scsiback_send_response(pending_req->info, sense_buffer, result,
			       resid, pending_req->rqid);

	अगर (pending_req->v2p)
		kref_put(&pending_req->v2p->kref,
			 scsiback_मुक्त_translation_entry);
पूर्ण

अटल व्योम scsiback_cmd_करोne(काष्ठा vscsibk_pend *pending_req)
अणु
	काष्ठा vscsibk_info *info = pending_req->info;
	अचिन्हित अक्षर *sense_buffer;
	अचिन्हित पूर्णांक resid;
	पूर्णांक errors;

	sense_buffer = pending_req->sense_buffer;
	resid        = pending_req->se_cmd.residual_count;
	errors       = pending_req->result;

	अगर (errors && log_prपूर्णांक_stat)
		scsiback_prपूर्णांक_status(sense_buffer, errors, pending_req);

	scsiback_fast_flush_area(pending_req);
	scsiback_करो_resp_with_sense(sense_buffer, errors, resid, pending_req);
	scsiback_put(info);
	/*
	 * Drop the extra KREF_ACK reference taken by target_submit_cmd_map_sgls()
	 * ahead of scsiback_check_stop_मुक्त() ->  transport_generic_मुक्त_cmd()
	 * final se_cmd->cmd_kref put.
	 */
	target_put_sess_cmd(&pending_req->se_cmd);
पूर्ण

अटल व्योम scsiback_cmd_exec(काष्ठा vscsibk_pend *pending_req)
अणु
	काष्ठा se_cmd *se_cmd = &pending_req->se_cmd;
	काष्ठा se_session *sess = pending_req->v2p->tpg->tpg_nexus->tvn_se_sess;

	scsiback_get(pending_req->info);
	se_cmd->tag = pending_req->rqid;
	target_init_cmd(se_cmd, sess, pending_req->sense_buffer,
			pending_req->v2p->lun, pending_req->data_len, 0,
			pending_req->sc_data_direction, TARGET_SCF_ACK_KREF);

	अगर (target_submit_prep(se_cmd, pending_req->cmnd, pending_req->sgl,
			       pending_req->n_sg, शून्य, 0, शून्य, 0, GFP_KERNEL))
		वापस;

	target_submit(se_cmd);
पूर्ण

अटल पूर्णांक scsiback_gnttab_data_map_batch(काष्ठा gnttab_map_grant_ref *map,
	काष्ठा page **pg, grant_handle_t *grant, पूर्णांक cnt)
अणु
	पूर्णांक err, i;

	अगर (!cnt)
		वापस 0;

	err = gnttab_map_refs(map, शून्य, pg, cnt);
	क्रम (i = 0; i < cnt; i++) अणु
		अगर (unlikely(map[i].status != GNTST_okay)) अणु
			pr_err("invalid buffer -- could not remap it\n");
			map[i].handle = SCSIBACK_INVALID_HANDLE;
			अगर (!err)
				err = -ENOMEM;
		पूर्ण अन्यथा अणु
			get_page(pg[i]);
		पूर्ण
		grant[i] = map[i].handle;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक scsiback_gnttab_data_map_list(काष्ठा vscsibk_pend *pending_req,
			काष्ठा scsiअगर_request_segment *seg, काष्ठा page **pg,
			grant_handle_t *grant, पूर्णांक cnt, u32 flags)
अणु
	पूर्णांक mapcount = 0, i, err = 0;
	काष्ठा gnttab_map_grant_ref map[VSCSI_GRANT_BATCH];
	काष्ठा vscsibk_info *info = pending_req->info;

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (gnttab_page_cache_get(&info->मुक्त_pages, pg + mapcount)) अणु
			gnttab_page_cache_put(&info->मुक्त_pages, pg, mapcount);
			pr_err("no grant page\n");
			वापस -ENOMEM;
		पूर्ण
		gnttab_set_map_op(&map[mapcount], vaddr_page(pg[mapcount]),
				  flags, seg[i].gref, info->करोmid);
		mapcount++;
		अगर (mapcount < VSCSI_GRANT_BATCH)
			जारी;
		err = scsiback_gnttab_data_map_batch(map, pg, grant, mapcount);
		pg += mapcount;
		grant += mapcount;
		pending_req->n_grants += mapcount;
		अगर (err)
			वापस err;
		mapcount = 0;
	पूर्ण
	err = scsiback_gnttab_data_map_batch(map, pg, grant, mapcount);
	pending_req->n_grants += mapcount;
	वापस err;
पूर्ण

अटल पूर्णांक scsiback_gnttab_data_map(काष्ठा vscsiअगर_request *ring_req,
					काष्ठा vscsibk_pend *pending_req)
अणु
	u32 flags;
	पूर्णांक i, err, n_segs, i_seg = 0;
	काष्ठा page **pg;
	काष्ठा scsiअगर_request_segment *seg;
	अचिन्हित दीर्घ end_seg = 0;
	अचिन्हित पूर्णांक nr_segments = (अचिन्हित पूर्णांक)ring_req->nr_segments;
	अचिन्हित पूर्णांक nr_sgl = 0;
	काष्ठा scatterlist *sg;
	grant_handle_t *grant;

	pending_req->n_sg = 0;
	pending_req->n_grants = 0;
	pending_req->data_len = 0;

	nr_segments &= ~VSCSIIF_SG_GRANT;
	अगर (!nr_segments)
		वापस 0;

	अगर (nr_segments > VSCSIIF_SG_TABLESIZE) अणु
		pr_debug("invalid parameter nr_seg = %d\n",
			ring_req->nr_segments);
		वापस -EINVAL;
	पूर्ण

	अगर (ring_req->nr_segments & VSCSIIF_SG_GRANT) अणु
		err = scsiback_gnttab_data_map_list(pending_req, ring_req->seg,
			pending_req->pages, pending_req->grant_handles,
			nr_segments, GNTMAP_host_map | GNTMAP_पढ़ोonly);
		अगर (err)
			वापस err;
		nr_sgl = nr_segments;
		nr_segments = 0;
		क्रम (i = 0; i < nr_sgl; i++) अणु
			n_segs = ring_req->seg[i].length /
				 माप(काष्ठा scsiअगर_request_segment);
			अगर ((अचिन्हित)ring_req->seg[i].offset +
			    (अचिन्हित)ring_req->seg[i].length > PAGE_SIZE ||
			    n_segs * माप(काष्ठा scsiअगर_request_segment) !=
			    ring_req->seg[i].length)
				वापस -EINVAL;
			nr_segments += n_segs;
		पूर्ण
		अगर (nr_segments > SG_ALL) अणु
			pr_debug("invalid nr_seg = %d\n", nr_segments);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* मुक्त of (sgl) in fast_flush_area() */
	pending_req->sgl = kदो_स्मृति_array(nr_segments,
					माप(काष्ठा scatterlist), GFP_KERNEL);
	अगर (!pending_req->sgl)
		वापस -ENOMEM;

	sg_init_table(pending_req->sgl, nr_segments);
	pending_req->n_sg = nr_segments;

	flags = GNTMAP_host_map;
	अगर (pending_req->sc_data_direction == DMA_TO_DEVICE)
		flags |= GNTMAP_पढ़ोonly;

	pg = pending_req->pages + nr_sgl;
	grant = pending_req->grant_handles + nr_sgl;
	अगर (!nr_sgl) अणु
		seg = ring_req->seg;
		err = scsiback_gnttab_data_map_list(pending_req, seg,
			pg, grant, nr_segments, flags);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nr_sgl; i++) अणु
			seg = (काष्ठा scsiअगर_request_segment *)(
			      vaddr(pending_req, i) + ring_req->seg[i].offset);
			n_segs = ring_req->seg[i].length /
				 माप(काष्ठा scsiअगर_request_segment);
			err = scsiback_gnttab_data_map_list(pending_req, seg,
				pg, grant, n_segs, flags);
			अगर (err)
				वापस err;
			pg += n_segs;
			grant += n_segs;
		पूर्ण
		end_seg = vaddr(pending_req, 0) + ring_req->seg[0].offset;
		seg = (काष्ठा scsiअगर_request_segment *)end_seg;
		end_seg += ring_req->seg[0].length;
		pg = pending_req->pages + nr_sgl;
	पूर्ण

	क्रम_each_sg(pending_req->sgl, sg, nr_segments, i) अणु
		sg_set_page(sg, pg[i], seg->length, seg->offset);
		pending_req->data_len += seg->length;
		seg++;
		अगर (nr_sgl && (अचिन्हित दीर्घ)seg >= end_seg) अणु
			i_seg++;
			end_seg = vaddr(pending_req, i_seg) +
				  ring_req->seg[i_seg].offset;
			seg = (काष्ठा scsiअगर_request_segment *)end_seg;
			end_seg += ring_req->seg[i_seg].length;
		पूर्ण
		अगर (sg->offset >= PAGE_SIZE ||
		    sg->length > PAGE_SIZE ||
		    sg->offset + sg->length > PAGE_SIZE)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scsiback_disconnect(काष्ठा vscsibk_info *info)
अणु
	रुको_event(info->रुकोing_to_मुक्त,
		atomic_पढ़ो(&info->nr_unreplied_reqs) == 0);

	unbind_from_irqhandler(info->irq, info);
	info->irq = 0;
	xenbus_unmap_ring_vमुक्त(info->dev, info->ring.sring);
पूर्ण

अटल व्योम scsiback_device_action(काष्ठा vscsibk_pend *pending_req,
	क्रमागत tcm_पंचांगreq_table act, पूर्णांक tag)
अणु
	काष्ठा scsiback_tpg *tpg = pending_req->v2p->tpg;
	काष्ठा scsiback_nexus *nexus = tpg->tpg_nexus;
	काष्ठा se_cmd *se_cmd = &pending_req->se_cmd;
	u64 unpacked_lun = pending_req->v2p->lun;
	पूर्णांक rc, err = FAILED;

	init_completion(&pending_req->पंचांगr_करोne);

	rc = target_submit_पंचांगr(&pending_req->se_cmd, nexus->tvn_se_sess,
			       &pending_req->sense_buffer[0],
			       unpacked_lun, शून्य, act, GFP_KERNEL,
			       tag, TARGET_SCF_ACK_KREF);
	अगर (rc)
		जाओ err;

	रुको_क्रम_completion(&pending_req->पंचांगr_करोne);

	err = (se_cmd->se_पंचांगr_req->response == TMR_FUNCTION_COMPLETE) ?
		SUCCESS : FAILED;

	scsiback_करो_resp_with_sense(शून्य, err, 0, pending_req);
	transport_generic_मुक्त_cmd(&pending_req->se_cmd, 0);
	वापस;

err:
	scsiback_करो_resp_with_sense(शून्य, err, 0, pending_req);
पूर्ण

/*
  Perक्रमm भव to physical translation
*/
अटल काष्ठा v2p_entry *scsiback_करो_translation(काष्ठा vscsibk_info *info,
			काष्ठा ids_tuple *v)
अणु
	काष्ठा v2p_entry *entry;
	काष्ठा list_head *head = &(info->v2p_entry_lists);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->v2p_lock, flags);
	list_क्रम_each_entry(entry, head, l) अणु
		अगर ((entry->v.chn == v->chn) &&
		    (entry->v.tgt == v->tgt) &&
		    (entry->v.lun == v->lun)) अणु
			kref_get(&entry->kref);
			जाओ out;
		पूर्ण
	पूर्ण
	entry = शून्य;

out:
	spin_unlock_irqrestore(&info->v2p_lock, flags);
	वापस entry;
पूर्ण

अटल काष्ठा vscsibk_pend *scsiback_get_pend_req(काष्ठा vscsiअगर_back_ring *ring,
				काष्ठा v2p_entry *v2p)
अणु
	काष्ठा scsiback_tpg *tpg = v2p->tpg;
	काष्ठा scsiback_nexus *nexus = tpg->tpg_nexus;
	काष्ठा se_session *se_sess = nexus->tvn_se_sess;
	काष्ठा vscsibk_pend *req;
	पूर्णांक tag, cpu, i;

	tag = sbiपंचांगap_queue_get(&se_sess->sess_tag_pool, &cpu);
	अगर (tag < 0) अणु
		pr_err("Unable to obtain tag for vscsiif_request\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	req = &((काष्ठा vscsibk_pend *)se_sess->sess_cmd_map)[tag];
	स_रखो(req, 0, माप(*req));
	req->se_cmd.map_tag = tag;
	req->se_cmd.map_cpu = cpu;

	क्रम (i = 0; i < VSCSI_MAX_GRANTS; i++)
		req->grant_handles[i] = SCSIBACK_INVALID_HANDLE;

	वापस req;
पूर्ण

अटल काष्ठा vscsibk_pend *prepare_pending_reqs(काष्ठा vscsibk_info *info,
				काष्ठा vscsiअगर_back_ring *ring,
				काष्ठा vscsiअगर_request *ring_req)
अणु
	काष्ठा vscsibk_pend *pending_req;
	काष्ठा v2p_entry *v2p;
	काष्ठा ids_tuple vir;

	/* request range check from frontend */
	अगर ((ring_req->sc_data_direction != DMA_BIसूचीECTIONAL) &&
		(ring_req->sc_data_direction != DMA_TO_DEVICE) &&
		(ring_req->sc_data_direction != DMA_FROM_DEVICE) &&
		(ring_req->sc_data_direction != DMA_NONE)) अणु
		pr_debug("invalid parameter data_dir = %d\n",
			ring_req->sc_data_direction);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (ring_req->cmd_len > VSCSIIF_MAX_COMMAND_SIZE) अणु
		pr_debug("invalid parameter cmd_len = %d\n",
			ring_req->cmd_len);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	vir.chn = ring_req->channel;
	vir.tgt = ring_req->id;
	vir.lun = ring_req->lun;

	v2p = scsiback_करो_translation(info, &vir);
	अगर (!v2p) अणु
		pr_debug("the v2p of (chn:%d, tgt:%d, lun:%d) doesn't exist.\n",
			 vir.chn, vir.tgt, vir.lun);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	pending_req = scsiback_get_pend_req(ring, v2p);
	अगर (IS_ERR(pending_req)) अणु
		kref_put(&v2p->kref, scsiback_मुक्त_translation_entry);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pending_req->rqid = ring_req->rqid;
	pending_req->info = info;
	pending_req->v2p = v2p;
	pending_req->sc_data_direction = ring_req->sc_data_direction;
	pending_req->cmd_len = ring_req->cmd_len;
	स_नकल(pending_req->cmnd, ring_req->cmnd, pending_req->cmd_len);

	वापस pending_req;
पूर्ण

अटल पूर्णांक scsiback_करो_cmd_fn(काष्ठा vscsibk_info *info,
			      अचिन्हित पूर्णांक *eoi_flags)
अणु
	काष्ठा vscsiअगर_back_ring *ring = &info->ring;
	काष्ठा vscsiअगर_request ring_req;
	काष्ठा vscsibk_pend *pending_req;
	RING_IDX rc, rp;
	पूर्णांक more_to_करो;
	uपूर्णांक32_t result;

	rc = ring->req_cons;
	rp = ring->sring->req_prod;
	rmb();	/* guest प्रणाली is accessing ring, too */

	अगर (RING_REQUEST_PROD_OVERFLOW(ring, rp)) अणु
		rc = ring->rsp_prod_pvt;
		pr_warn("Dom%d provided bogus ring requests (%#x - %#x = %u). Halting ring processing\n",
			   info->करोmid, rp, rc, rp - rc);
		वापस -EINVAL;
	पूर्ण

	जबतक ((rc != rp)) अणु
		*eoi_flags &= ~XEN_EOI_FLAG_SPURIOUS;

		अगर (RING_REQUEST_CONS_OVERFLOW(ring, rc))
			अवरोध;

		RING_COPY_REQUEST(ring, rc, &ring_req);
		ring->req_cons = ++rc;

		pending_req = prepare_pending_reqs(info, ring, &ring_req);
		अगर (IS_ERR(pending_req)) अणु
			चयन (PTR_ERR(pending_req)) अणु
			हाल -ENODEV:
				result = DID_NO_CONNECT;
				अवरोध;
			शेष:
				result = DRIVER_ERROR;
				अवरोध;
			पूर्ण
			scsiback_send_response(info, शून्य, result << 24, 0,
					       ring_req.rqid);
			वापस 1;
		पूर्ण

		चयन (ring_req.act) अणु
		हाल VSCSIIF_ACT_SCSI_CDB:
			अगर (scsiback_gnttab_data_map(&ring_req, pending_req)) अणु
				scsiback_fast_flush_area(pending_req);
				scsiback_करो_resp_with_sense(शून्य,
						DRIVER_ERROR << 24, 0, pending_req);
				transport_generic_मुक्त_cmd(&pending_req->se_cmd, 0);
			पूर्ण अन्यथा अणु
				scsiback_cmd_exec(pending_req);
			पूर्ण
			अवरोध;
		हाल VSCSIIF_ACT_SCSI_ABORT:
			scsiback_device_action(pending_req, TMR_ABORT_TASK,
				ring_req.ref_rqid);
			अवरोध;
		हाल VSCSIIF_ACT_SCSI_RESET:
			scsiback_device_action(pending_req, TMR_LUN_RESET, 0);
			अवरोध;
		शेष:
			pr_err_ratelimited("invalid request\n");
			scsiback_करो_resp_with_sense(शून्य, DRIVER_ERROR << 24, 0,
						    pending_req);
			transport_generic_मुक्त_cmd(&pending_req->se_cmd, 0);
			अवरोध;
		पूर्ण

		/* Yield poपूर्णांक क्रम this unbounded loop. */
		cond_resched();
	पूर्ण

	gnttab_page_cache_shrink(&info->मुक्त_pages, scsiback_max_buffer_pages);

	RING_FINAL_CHECK_FOR_REQUESTS(&info->ring, more_to_करो);
	वापस more_to_करो;
पूर्ण

अटल irqवापस_t scsiback_irq_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vscsibk_info *info = dev_id;
	पूर्णांक rc;
	अचिन्हित पूर्णांक eoi_flags = XEN_EOI_FLAG_SPURIOUS;

	जबतक ((rc = scsiback_करो_cmd_fn(info, &eoi_flags)) > 0)
		cond_resched();

	/* In हाल of a ring error we keep the event channel masked. */
	अगर (!rc)
		xen_irq_lateeoi(irq, eoi_flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक scsiback_init_sring(काष्ठा vscsibk_info *info, grant_ref_t ring_ref,
			evtchn_port_t evtchn)
अणु
	व्योम *area;
	काष्ठा vscsiअगर_sring *sring;
	पूर्णांक err;

	अगर (info->irq)
		वापस -1;

	err = xenbus_map_ring_valloc(info->dev, &ring_ref, 1, &area);
	अगर (err)
		वापस err;

	sring = (काष्ठा vscsiअगर_sring *)area;
	BACK_RING_INIT(&info->ring, sring, PAGE_SIZE);

	err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi(info->dev, evtchn);
	अगर (err < 0)
		जाओ unmap_page;

	info->irq = err;

	err = request_thपढ़ोed_irq(info->irq, शून्य, scsiback_irq_fn,
				   IRQF_ONESHOT, "vscsiif-backend", info);
	अगर (err)
		जाओ मुक्त_irq;

	वापस 0;

मुक्त_irq:
	unbind_from_irqhandler(info->irq, info);
	info->irq = 0;
unmap_page:
	xenbus_unmap_ring_vमुक्त(info->dev, area);

	वापस err;
पूर्ण

अटल पूर्णांक scsiback_map(काष्ठा vscsibk_info *info)
अणु
	काष्ठा xenbus_device *dev = info->dev;
	अचिन्हित पूर्णांक ring_ref;
	evtchn_port_t evtchn;
	पूर्णांक err;

	err = xenbus_gather(XBT_NIL, dev->otherend,
			"ring-ref", "%u", &ring_ref,
			"event-channel", "%u", &evtchn, शून्य);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "reading %s ring", dev->otherend);
		वापस err;
	पूर्ण

	वापस scsiback_init_sring(info, ring_ref, evtchn);
पूर्ण

/*
  Check क्रम a translation entry being present
*/
अटल काष्ठा v2p_entry *scsiback_chk_translation_entry(
	काष्ठा vscsibk_info *info, काष्ठा ids_tuple *v)
अणु
	काष्ठा list_head *head = &(info->v2p_entry_lists);
	काष्ठा v2p_entry *entry;

	list_क्रम_each_entry(entry, head, l)
		अगर ((entry->v.chn == v->chn) &&
		    (entry->v.tgt == v->tgt) &&
		    (entry->v.lun == v->lun))
			वापस entry;

	वापस शून्य;
पूर्ण

/*
  Add a new translation entry
*/
अटल पूर्णांक scsiback_add_translation_entry(काष्ठा vscsibk_info *info,
					  अक्षर *phy, काष्ठा ids_tuple *v)
अणु
	पूर्णांक err = 0;
	काष्ठा v2p_entry *new;
	अचिन्हित दीर्घ flags;
	अक्षर *lunp;
	अचिन्हित दीर्घ दीर्घ unpacked_lun;
	काष्ठा se_lun *se_lun;
	काष्ठा scsiback_tpg *tpg_entry, *tpg = शून्य;
	अक्षर *error = "doesn't exist";

	lunp = म_खोजप(phy, ':');
	अगर (!lunp) अणु
		pr_err("illegal format of physical device %s\n", phy);
		वापस -EINVAL;
	पूर्ण
	*lunp = 0;
	lunp++;
	err = kम_से_अदीर्घl(lunp, 10, &unpacked_lun);
	अगर (err < 0) अणु
		pr_err("lun number not valid: %s\n", lunp);
		वापस err;
	पूर्ण

	mutex_lock(&scsiback_mutex);
	list_क्रम_each_entry(tpg_entry, &scsiback_list, tv_tpg_list) अणु
		अगर (!म_भेद(phy, tpg_entry->tport->tport_name) ||
		    !म_भेद(phy, tpg_entry->param_alias)) अणु
			mutex_lock(&tpg_entry->se_tpg.tpg_lun_mutex);
			hlist_क्रम_each_entry(se_lun, &tpg_entry->se_tpg.tpg_lun_hlist, link) अणु
				अगर (se_lun->unpacked_lun == unpacked_lun) अणु
					अगर (!tpg_entry->tpg_nexus)
						error = "nexus undefined";
					अन्यथा
						tpg = tpg_entry;
					अवरोध;
				पूर्ण
			पूर्ण
			mutex_unlock(&tpg_entry->se_tpg.tpg_lun_mutex);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (tpg) अणु
		mutex_lock(&tpg->tv_tpg_mutex);
		tpg->tv_tpg_fe_count++;
		mutex_unlock(&tpg->tv_tpg_mutex);
	पूर्ण
	mutex_unlock(&scsiback_mutex);

	अगर (!tpg) अणु
		pr_err("%s:%llu %s\n", phy, unpacked_lun, error);
		वापस -ENODEV;
	पूर्ण

	new = kदो_स्मृति(माप(काष्ठा v2p_entry), GFP_KERNEL);
	अगर (new == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_irqsave(&info->v2p_lock, flags);

	/* Check द्विगुन assignment to identical भव ID */
	अगर (scsiback_chk_translation_entry(info, v)) अणु
		pr_warn("Virtual ID is already used. Assignment was not performed.\n");
		err = -EEXIST;
		जाओ out;
	पूर्ण

	/* Create a new translation entry and add to the list */
	kref_init(&new->kref);
	new->v = *v;
	new->tpg = tpg;
	new->lun = unpacked_lun;
	list_add_tail(&new->l, &info->v2p_entry_lists);

out:
	spin_unlock_irqrestore(&info->v2p_lock, flags);

out_मुक्त:
	अगर (err) अणु
		mutex_lock(&tpg->tv_tpg_mutex);
		tpg->tv_tpg_fe_count--;
		mutex_unlock(&tpg->tv_tpg_mutex);
		kमुक्त(new);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __scsiback_del_translation_entry(काष्ठा v2p_entry *entry)
अणु
	list_del(&entry->l);
	kref_put(&entry->kref, scsiback_मुक्त_translation_entry);
पूर्ण

/*
  Delete the translation entry specअगरied
*/
अटल पूर्णांक scsiback_del_translation_entry(काष्ठा vscsibk_info *info,
					  काष्ठा ids_tuple *v)
अणु
	काष्ठा v2p_entry *entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&info->v2p_lock, flags);
	/* Find out the translation entry specअगरied */
	entry = scsiback_chk_translation_entry(info, v);
	अगर (entry)
		__scsiback_del_translation_entry(entry);
	अन्यथा
		ret = -ENOENT;

	spin_unlock_irqrestore(&info->v2p_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम scsiback_करो_add_lun(काष्ठा vscsibk_info *info, स्थिर अक्षर *state,
				अक्षर *phy, काष्ठा ids_tuple *vir, पूर्णांक try)
अणु
	काष्ठा v2p_entry *entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (try) अणु
		spin_lock_irqsave(&info->v2p_lock, flags);
		entry = scsiback_chk_translation_entry(info, vir);
		spin_unlock_irqrestore(&info->v2p_lock, flags);
		अगर (entry)
			वापस;
	पूर्ण
	अगर (!scsiback_add_translation_entry(info, phy, vir)) अणु
		अगर (xenbus_म_लिखो(XBT_NIL, info->dev->nodename, state,
				  "%d", XenbusStateInitialised)) अणु
			pr_err("xenbus_printf error %s\n", state);
			scsiback_del_translation_entry(info, vir);
		पूर्ण
	पूर्ण अन्यथा अगर (!try) अणु
		err = xenbus_म_लिखो(XBT_NIL, info->dev->nodename, state,
			      "%d", XenbusStateClosed);
		अगर (err)
			xenbus_dev_error(info->dev, err,
				"%s: writing %s", __func__, state);
	पूर्ण
पूर्ण

अटल व्योम scsiback_करो_del_lun(काष्ठा vscsibk_info *info, स्थिर अक्षर *state,
				काष्ठा ids_tuple *vir)
अणु
	अगर (!scsiback_del_translation_entry(info, vir)) अणु
		अगर (xenbus_म_लिखो(XBT_NIL, info->dev->nodename, state,
				  "%d", XenbusStateClosed))
			pr_err("xenbus_printf error %s\n", state);
	पूर्ण
पूर्ण

#घोषणा VSCSIBACK_OP_ADD_OR_DEL_LUN	1
#घोषणा VSCSIBACK_OP_UPDATEDEV_STATE	2

अटल व्योम scsiback_करो_1lun_hotplug(काष्ठा vscsibk_info *info, पूर्णांक op,
				     अक्षर *ent)
अणु
	पूर्णांक err;
	काष्ठा ids_tuple vir;
	अक्षर *val;
	पूर्णांक device_state;
	अक्षर phy[VSCSI_NAMELEN];
	अक्षर str[64];
	अक्षर state[64];
	काष्ठा xenbus_device *dev = info->dev;

	/* पढ़ो status */
	snम_लिखो(state, माप(state), "vscsi-devs/%s/state", ent);
	err = xenbus_म_पूछो(XBT_NIL, dev->nodename, state, "%u", &device_state);
	अगर (XENBUS_EXIST_ERR(err))
		वापस;

	/* physical SCSI device */
	snम_लिखो(str, माप(str), "vscsi-devs/%s/p-dev", ent);
	val = xenbus_पढ़ो(XBT_NIL, dev->nodename, str, शून्य);
	अगर (IS_ERR(val)) अणु
		err = xenbus_म_लिखो(XBT_NIL, dev->nodename, state,
			      "%d", XenbusStateClosed);
		अगर (err)
			xenbus_dev_error(info->dev, err,
				"%s: writing %s", __func__, state);
		वापस;
	पूर्ण
	strlcpy(phy, val, VSCSI_NAMELEN);
	kमुक्त(val);

	/* भव SCSI device */
	snम_लिखो(str, माप(str), "vscsi-devs/%s/v-dev", ent);
	err = xenbus_म_पूछो(XBT_NIL, dev->nodename, str, "%u:%u:%u:%u",
			   &vir.hst, &vir.chn, &vir.tgt, &vir.lun);
	अगर (XENBUS_EXIST_ERR(err)) अणु
		err = xenbus_म_लिखो(XBT_NIL, dev->nodename, state,
			      "%d", XenbusStateClosed);
		अगर (err)
			xenbus_dev_error(info->dev, err,
				"%s: writing %s", __func__, state);
		वापस;
	पूर्ण

	चयन (op) अणु
	हाल VSCSIBACK_OP_ADD_OR_DEL_LUN:
		चयन (device_state) अणु
		हाल XenbusStateInitialising:
			scsiback_करो_add_lun(info, state, phy, &vir, 0);
			अवरोध;
		हाल XenbusStateConnected:
			scsiback_करो_add_lun(info, state, phy, &vir, 1);
			अवरोध;
		हाल XenbusStateClosing:
			scsiback_करो_del_lun(info, state, &vir);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल VSCSIBACK_OP_UPDATEDEV_STATE:
		अगर (device_state == XenbusStateInitialised) अणु
			/* modअगरy vscsi-devs/dev-x/state */
			अगर (xenbus_म_लिखो(XBT_NIL, dev->nodename, state,
					  "%d", XenbusStateConnected)) अणु
				pr_err("xenbus_printf error %s\n", str);
				scsiback_del_translation_entry(info, &vir);
				xenbus_म_लिखो(XBT_NIL, dev->nodename, state,
					      "%d", XenbusStateClosed);
			पूर्ण
		पूर्ण
		अवरोध;
	/* When it is necessary, processing is added here. */
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम scsiback_करो_lun_hotplug(काष्ठा vscsibk_info *info, पूर्णांक op)
अणु
	पूर्णांक i;
	अक्षर **dir;
	अचिन्हित पूर्णांक ndir = 0;

	dir = xenbus_directory(XBT_NIL, info->dev->nodename, "vscsi-devs",
			       &ndir);
	अगर (IS_ERR(dir))
		वापस;

	क्रम (i = 0; i < ndir; i++)
		scsiback_करो_1lun_hotplug(info, op, dir[i]);

	kमुक्त(dir);
पूर्ण

अटल व्योम scsiback_frontend_changed(काष्ठा xenbus_device *dev,
					क्रमागत xenbus_state frontend_state)
अणु
	काष्ठा vscsibk_info *info = dev_get_drvdata(&dev->dev);

	चयन (frontend_state) अणु
	हाल XenbusStateInitialising:
		अवरोध;

	हाल XenbusStateInitialised:
		अगर (scsiback_map(info))
			अवरोध;

		scsiback_करो_lun_hotplug(info, VSCSIBACK_OP_ADD_OR_DEL_LUN);
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateConnected:
		scsiback_करो_lun_hotplug(info, VSCSIBACK_OP_UPDATEDEV_STATE);

		अगर (dev->state == XenbusStateConnected)
			अवरोध;

		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosing:
		अगर (info->irq)
			scsiback_disconnect(info);

		xenbus_चयन_state(dev, XenbusStateClosing);
		अवरोध;

	हाल XenbusStateClosed:
		xenbus_चयन_state(dev, XenbusStateClosed);
		अगर (xenbus_dev_is_online(dev))
			अवरोध;
		fallthrough;	/* अगर not online */
	हाल XenbusStateUnknown:
		device_unरेजिस्टर(&dev->dev);
		अवरोध;

	हाल XenbusStateReconfiguring:
		scsiback_करो_lun_hotplug(info, VSCSIBACK_OP_ADD_OR_DEL_LUN);
		xenbus_चयन_state(dev, XenbusStateReconfigured);

		अवरोध;

	शेष:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
					frontend_state);
		अवरोध;
	पूर्ण
पूर्ण

/*
  Release the translation entry specfied
*/
अटल व्योम scsiback_release_translation_entry(काष्ठा vscsibk_info *info)
अणु
	काष्ठा v2p_entry *entry, *पंचांगp;
	काष्ठा list_head *head = &(info->v2p_entry_lists);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->v2p_lock, flags);

	list_क्रम_each_entry_safe(entry, पंचांगp, head, l)
		__scsiback_del_translation_entry(entry);

	spin_unlock_irqrestore(&info->v2p_lock, flags);
पूर्ण

अटल पूर्णांक scsiback_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा vscsibk_info *info = dev_get_drvdata(&dev->dev);

	अगर (info->irq)
		scsiback_disconnect(info);

	scsiback_release_translation_entry(info);

	gnttab_page_cache_shrink(&info->मुक्त_pages, 0);

	dev_set_drvdata(&dev->dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक scsiback_probe(काष्ठा xenbus_device *dev,
			   स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err;

	काष्ठा vscsibk_info *info = kzalloc(माप(काष्ठा vscsibk_info),
					    GFP_KERNEL);

	pr_debug("%s %p %d\n", __func__, dev, dev->otherend_id);

	अगर (!info) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating backend structure");
		वापस -ENOMEM;
	पूर्ण
	info->dev = dev;
	dev_set_drvdata(&dev->dev, info);

	info->करोmid = dev->otherend_id;
	spin_lock_init(&info->ring_lock);
	atomic_set(&info->nr_unreplied_reqs, 0);
	init_रुकोqueue_head(&info->रुकोing_to_मुक्त);
	info->dev = dev;
	info->irq = 0;
	INIT_LIST_HEAD(&info->v2p_entry_lists);
	spin_lock_init(&info->v2p_lock);
	gnttab_page_cache_init(&info->मुक्त_pages);

	err = xenbus_म_लिखो(XBT_NIL, dev->nodename, "feature-sg-grant", "%u",
			    SG_ALL);
	अगर (err)
		xenbus_dev_error(dev, err, "writing feature-sg-grant");

	err = xenbus_चयन_state(dev, XenbusStateInitWait);
	अगर (err)
		जाओ fail;

	वापस 0;

fail:
	pr_warn("%s failed\n", __func__);
	scsiback_हटाओ(dev);

	वापस err;
पूर्ण

अटल अक्षर *scsiback_dump_proto_id(काष्ठा scsiback_tport *tport)
अणु
	चयन (tport->tport_proto_id) अणु
	हाल SCSI_PROTOCOL_SAS:
		वापस "SAS";
	हाल SCSI_PROTOCOL_FCP:
		वापस "FCP";
	हाल SCSI_PROTOCOL_ISCSI:
		वापस "iSCSI";
	शेष:
		अवरोध;
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल अक्षर *scsiback_get_fabric_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);
	काष्ठा scsiback_tport *tport = tpg->tport;

	वापस &tport->tport_name[0];
पूर्ण

अटल u16 scsiback_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);
	वापस tpg->tport_tpgt;
पूर्ण

अटल काष्ठा se_wwn *
scsiback_make_tport(काष्ठा target_fabric_configfs *tf,
		     काष्ठा config_group *group,
		     स्थिर अक्षर *name)
अणु
	काष्ठा scsiback_tport *tport;
	अक्षर *ptr;
	u64 wwpn = 0;
	पूर्णांक off = 0;

	tport = kzalloc(माप(काष्ठा scsiback_tport), GFP_KERNEL);
	अगर (!tport)
		वापस ERR_PTR(-ENOMEM);

	tport->tport_wwpn = wwpn;
	/*
	 * Determine the emulated Protocol Identअगरier and Target Port Name
	 * based on the incoming configfs directory name.
	 */
	ptr = म_माला(name, "naa.");
	अगर (ptr) अणु
		tport->tport_proto_id = SCSI_PROTOCOL_SAS;
		जाओ check_len;
	पूर्ण
	ptr = म_माला(name, "fc.");
	अगर (ptr) अणु
		tport->tport_proto_id = SCSI_PROTOCOL_FCP;
		off = 3; /* Skip over "fc." */
		जाओ check_len;
	पूर्ण
	ptr = म_माला(name, "iqn.");
	अगर (ptr) अणु
		tport->tport_proto_id = SCSI_PROTOCOL_ISCSI;
		जाओ check_len;
	पूर्ण

	pr_err("Unable to locate prefix for emulated Target Port: %s\n", name);
	kमुक्त(tport);
	वापस ERR_PTR(-EINVAL);

check_len:
	अगर (म_माप(name) >= VSCSI_NAMELEN) अणु
		pr_err("Emulated %s Address: %s, exceeds max: %d\n", name,
			scsiback_dump_proto_id(tport), VSCSI_NAMELEN);
		kमुक्त(tport);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	snम_लिखो(&tport->tport_name[0], VSCSI_NAMELEN, "%s", &name[off]);

	pr_debug("Allocated emulated Target %s Address: %s\n",
		 scsiback_dump_proto_id(tport), name);

	वापस &tport->tport_wwn;
पूर्ण

अटल व्योम scsiback_drop_tport(काष्ठा se_wwn *wwn)
अणु
	काष्ठा scsiback_tport *tport = container_of(wwn,
				काष्ठा scsiback_tport, tport_wwn);

	pr_debug("Deallocating emulated Target %s Address: %s\n",
		 scsiback_dump_proto_id(tport), tport->tport_name);

	kमुक्त(tport);
पूर्ण

अटल u32 scsiback_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक scsiback_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस transport_generic_मुक्त_cmd(se_cmd, 0);
पूर्ण

अटल व्योम scsiback_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	target_मुक्त_tag(se_cmd->se_sess, se_cmd);
पूर्ण

अटल u32 scsiback_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक scsiback_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	/* Go ahead and process the ग_लिखो immediately */
	target_execute_cmd(se_cmd);

	वापस 0;
पूर्ण

अटल व्योम scsiback_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
पूर्ण

अटल पूर्णांक scsiback_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक scsiback_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा vscsibk_pend *pending_req = container_of(se_cmd,
				काष्ठा vscsibk_pend, se_cmd);

	pending_req->result = SAM_STAT_GOOD;
	scsiback_cmd_करोne(pending_req);
	वापस 0;
पूर्ण

अटल पूर्णांक scsiback_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा vscsibk_pend *pending_req = container_of(se_cmd,
				काष्ठा vscsibk_pend, se_cmd);

	अगर (se_cmd->sense_buffer &&
	    ((se_cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ||
	     (se_cmd->se_cmd_flags & SCF_EMULATED_TASK_SENSE)))
		pending_req->result = (DRIVER_SENSE << 24) |
				      SAM_STAT_CHECK_CONDITION;
	अन्यथा
		pending_req->result = se_cmd->scsi_status;

	scsiback_cmd_करोne(pending_req);
	वापस 0;
पूर्ण

अटल व्योम scsiback_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा vscsibk_pend *pending_req = container_of(se_cmd,
				काष्ठा vscsibk_pend, se_cmd);

	complete(&pending_req->पंचांगr_करोne);
पूर्ण

अटल व्योम scsiback_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
पूर्ण

अटल sमाप_प्रकार scsiback_tpg_param_alias_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = param_to_tpg(item);
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg, काष्ठा scsiback_tpg,
						se_tpg);
	sमाप_प्रकार rb;

	mutex_lock(&tpg->tv_tpg_mutex);
	rb = snम_लिखो(page, PAGE_SIZE, "%s\n", tpg->param_alias);
	mutex_unlock(&tpg->tv_tpg_mutex);

	वापस rb;
पूर्ण

अटल sमाप_प्रकार scsiback_tpg_param_alias_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = param_to_tpg(item);
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg, काष्ठा scsiback_tpg,
						se_tpg);
	पूर्णांक len;

	अगर (म_माप(page) >= VSCSI_NAMELEN) अणु
		pr_err("param alias: %s, exceeds max: %d\n", page,
			VSCSI_NAMELEN);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&tpg->tv_tpg_mutex);
	len = snम_लिखो(tpg->param_alias, VSCSI_NAMELEN, "%s", page);
	अगर (tpg->param_alias[len - 1] == '\n')
		tpg->param_alias[len - 1] = '\0';
	mutex_unlock(&tpg->tv_tpg_mutex);

	वापस count;
पूर्ण

CONFIGFS_ATTR(scsiback_tpg_param_, alias);

अटल काष्ठा configfs_attribute *scsiback_param_attrs[] = अणु
	&scsiback_tpg_param_attr_alias,
	शून्य,
पूर्ण;

अटल पूर्णांक scsiback_alloc_sess_cb(काष्ठा se_portal_group *se_tpg,
				  काष्ठा se_session *se_sess, व्योम *p)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);

	tpg->tpg_nexus = p;
	वापस 0;
पूर्ण

अटल पूर्णांक scsiback_make_nexus(काष्ठा scsiback_tpg *tpg,
				स्थिर अक्षर *name)
अणु
	काष्ठा scsiback_nexus *tv_nexus;
	पूर्णांक ret = 0;

	mutex_lock(&tpg->tv_tpg_mutex);
	अगर (tpg->tpg_nexus) अणु
		pr_debug("tpg->tpg_nexus already exists\n");
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	tv_nexus = kzalloc(माप(काष्ठा scsiback_nexus), GFP_KERNEL);
	अगर (!tv_nexus) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg,
						     VSCSI_DEFAULT_SESSION_TAGS,
						     माप(काष्ठा vscsibk_pend),
						     TARGET_PROT_NORMAL, name,
						     tv_nexus, scsiback_alloc_sess_cb);
	अगर (IS_ERR(tv_nexus->tvn_se_sess)) अणु
		kमुक्त(tv_nexus);
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

out_unlock:
	mutex_unlock(&tpg->tv_tpg_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक scsiback_drop_nexus(काष्ठा scsiback_tpg *tpg)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा scsiback_nexus *tv_nexus;

	mutex_lock(&tpg->tv_tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		वापस -ENODEV;
	पूर्ण

	se_sess = tv_nexus->tvn_se_sess;
	अगर (!se_sess) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		वापस -ENODEV;
	पूर्ण

	अगर (tpg->tv_tpg_port_count != 0) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to remove xen-pvscsi I_T Nexus with active TPG port count: %d\n",
			tpg->tv_tpg_port_count);
		वापस -EBUSY;
	पूर्ण

	अगर (tpg->tv_tpg_fe_count != 0) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to remove xen-pvscsi I_T Nexus with active TPG frontend count: %d\n",
			tpg->tv_tpg_fe_count);
		वापस -EBUSY;
	पूर्ण

	pr_debug("Removing I_T Nexus to emulated %s Initiator Port: %s\n",
		scsiback_dump_proto_id(tpg->tport),
		tv_nexus->tvn_se_sess->se_node_acl->initiatorname);

	/*
	 * Release the SCSI I_T Nexus to the emulated xen-pvscsi Target Port
	 */
	target_हटाओ_session(se_sess);
	tpg->tpg_nexus = शून्य;
	mutex_unlock(&tpg->tv_tpg_mutex);

	kमुक्त(tv_nexus);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार scsiback_tpg_nexus_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);
	काष्ठा scsiback_nexus *tv_nexus;
	sमाप_प्रकार ret;

	mutex_lock(&tpg->tv_tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		वापस -ENODEV;
	पूर्ण
	ret = snम_लिखो(page, PAGE_SIZE, "%s\n",
			tv_nexus->tvn_se_sess->se_node_acl->initiatorname);
	mutex_unlock(&tpg->tv_tpg_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार scsiback_tpg_nexus_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);
	काष्ठा scsiback_tport *tport_wwn = tpg->tport;
	अचिन्हित अक्षर i_port[VSCSI_NAMELEN], *ptr, *port_ptr;
	पूर्णांक ret;
	/*
	 * Shutकरोwn the active I_T nexus अगर 'NULL' is passed.
	 */
	अगर (!म_भेदन(page, "NULL", 4)) अणु
		ret = scsiback_drop_nexus(tpg);
		वापस (!ret) ? count : ret;
	पूर्ण
	/*
	 * Otherwise make sure the passed भव Initiator port WWN matches
	 * the fabric protocol_id set in scsiback_make_tport(), and call
	 * scsiback_make_nexus().
	 */
	अगर (म_माप(page) >= VSCSI_NAMELEN) अणु
		pr_err("Emulated NAA Sas Address: %s, exceeds max: %d\n",
			page, VSCSI_NAMELEN);
		वापस -EINVAL;
	पूर्ण
	snम_लिखो(&i_port[0], VSCSI_NAMELEN, "%s", page);

	ptr = म_माला(i_port, "naa.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_SAS) अणु
			pr_err("Passed SAS Initiator Port %s does not match target port protoid: %s\n",
				i_port, scsiback_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "fc.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_FCP) अणु
			pr_err("Passed FCP Initiator Port %s does not match target port protoid: %s\n",
				i_port, scsiback_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[3]; /* Skip over "fc." */
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "iqn.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_ISCSI) अणु
			pr_err("Passed iSCSI Initiator Port %s does not match target port protoid: %s\n",
				i_port, scsiback_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	pr_err("Unable to locate prefix for emulated Initiator Port: %s\n",
		i_port);
	वापस -EINVAL;
	/*
	 * Clear any trailing newline क्रम the NAA WWN
	 */
check_newline:
	अगर (i_port[म_माप(i_port) - 1] == '\n')
		i_port[म_माप(i_port) - 1] = '\0';

	ret = scsiback_make_nexus(tpg, port_ptr);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

CONFIGFS_ATTR(scsiback_tpg_, nexus);

अटल काष्ठा configfs_attribute *scsiback_tpg_attrs[] = अणु
	&scsiback_tpg_attr_nexus,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार
scsiback_wwn_version_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "xen-pvscsi fabric module %s on %s/%s on "
		UTS_RELEASE"\n",
		VSCSI_VERSION, utsname()->sysname, utsname()->machine);
पूर्ण

CONFIGFS_ATTR_RO(scsiback_wwn_, version);

अटल काष्ठा configfs_attribute *scsiback_wwn_attrs[] = अणु
	&scsiback_wwn_attr_version,
	शून्य,
पूर्ण;

अटल पूर्णांक scsiback_port_link(काष्ठा se_portal_group *se_tpg,
			       काष्ठा se_lun *lun)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);

	mutex_lock(&tpg->tv_tpg_mutex);
	tpg->tv_tpg_port_count++;
	mutex_unlock(&tpg->tv_tpg_mutex);

	वापस 0;
पूर्ण

अटल व्योम scsiback_port_unlink(काष्ठा se_portal_group *se_tpg,
				  काष्ठा se_lun *lun)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);

	mutex_lock(&tpg->tv_tpg_mutex);
	tpg->tv_tpg_port_count--;
	mutex_unlock(&tpg->tv_tpg_mutex);
पूर्ण

अटल काष्ठा se_portal_group *
scsiback_make_tpg(काष्ठा se_wwn *wwn, स्थिर अक्षर *name)
अणु
	काष्ठा scsiback_tport *tport = container_of(wwn,
			काष्ठा scsiback_tport, tport_wwn);

	काष्ठा scsiback_tpg *tpg;
	u16 tpgt;
	पूर्णांक ret;

	अगर (म_माला(name, "tpgt_") != name)
		वापस ERR_PTR(-EINVAL);
	ret = kstrtou16(name + 5, 10, &tpgt);
	अगर (ret)
		वापस ERR_PTR(ret);

	tpg = kzalloc(माप(काष्ठा scsiback_tpg), GFP_KERNEL);
	अगर (!tpg)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&tpg->tv_tpg_mutex);
	INIT_LIST_HEAD(&tpg->tv_tpg_list);
	INIT_LIST_HEAD(&tpg->info_list);
	tpg->tport = tport;
	tpg->tport_tpgt = tpgt;

	ret = core_tpg_रेजिस्टर(wwn, &tpg->se_tpg, tport->tport_proto_id);
	अगर (ret < 0) अणु
		kमुक्त(tpg);
		वापस शून्य;
	पूर्ण
	mutex_lock(&scsiback_mutex);
	list_add_tail(&tpg->tv_tpg_list, &scsiback_list);
	mutex_unlock(&scsiback_mutex);

	वापस &tpg->se_tpg;
पूर्ण

अटल व्योम scsiback_drop_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा scsiback_tpg *tpg = container_of(se_tpg,
				काष्ठा scsiback_tpg, se_tpg);

	mutex_lock(&scsiback_mutex);
	list_del(&tpg->tv_tpg_list);
	mutex_unlock(&scsiback_mutex);
	/*
	 * Release the भव I_T Nexus क्रम this xen-pvscsi TPG
	 */
	scsiback_drop_nexus(tpg);
	/*
	 * Deरेजिस्टर the se_tpg from TCM.
	 */
	core_tpg_deरेजिस्टर(se_tpg);
	kमुक्त(tpg);
पूर्ण

अटल पूर्णांक scsiback_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक scsiback_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा target_core_fabric_ops scsiback_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "xen-pvscsi",
	.tpg_get_wwn			= scsiback_get_fabric_wwn,
	.tpg_get_tag			= scsiback_get_tag,
	.tpg_check_demo_mode		= scsiback_check_true,
	.tpg_check_demo_mode_cache	= scsiback_check_true,
	.tpg_check_demo_mode_ग_लिखो_protect = scsiback_check_false,
	.tpg_check_prod_mode_ग_लिखो_protect = scsiback_check_false,
	.tpg_get_inst_index		= scsiback_tpg_get_inst_index,
	.check_stop_मुक्त		= scsiback_check_stop_मुक्त,
	.release_cmd			= scsiback_release_cmd,
	.sess_get_index			= scsiback_sess_get_index,
	.sess_get_initiator_sid		= शून्य,
	.ग_लिखो_pending			= scsiback_ग_लिखो_pending,
	.set_शेष_node_attributes	= scsiback_set_शेष_node_attrs,
	.get_cmd_state			= scsiback_get_cmd_state,
	.queue_data_in			= scsiback_queue_data_in,
	.queue_status			= scsiback_queue_status,
	.queue_पंचांग_rsp			= scsiback_queue_पंचांग_rsp,
	.पातed_task			= scsiback_पातed_task,
	/*
	 * Setup callers क्रम generic logic in target_core_fabric_configfs.c
	 */
	.fabric_make_wwn		= scsiback_make_tport,
	.fabric_drop_wwn		= scsiback_drop_tport,
	.fabric_make_tpg		= scsiback_make_tpg,
	.fabric_drop_tpg		= scsiback_drop_tpg,
	.fabric_post_link		= scsiback_port_link,
	.fabric_pre_unlink		= scsiback_port_unlink,

	.tfc_wwn_attrs			= scsiback_wwn_attrs,
	.tfc_tpg_base_attrs		= scsiback_tpg_attrs,
	.tfc_tpg_param_attrs		= scsiback_param_attrs,
पूर्ण;

अटल स्थिर काष्ठा xenbus_device_id scsiback_ids[] = अणु
	अणु "vscsi" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver scsiback_driver = अणु
	.ids			= scsiback_ids,
	.probe			= scsiback_probe,
	.हटाओ			= scsiback_हटाओ,
	.otherend_changed	= scsiback_frontend_changed
पूर्ण;

अटल पूर्णांक __init scsiback_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	pr_debug("xen-pvscsi: fabric module %s on %s/%s on "UTS_RELEASE"\n",
		 VSCSI_VERSION, utsname()->sysname, utsname()->machine);

	ret = xenbus_रेजिस्टर_backend(&scsiback_driver);
	अगर (ret)
		जाओ out;

	ret = target_रेजिस्टर_ढाँचा(&scsiback_ops);
	अगर (ret)
		जाओ out_unरेजिस्टर_xenbus;

	वापस 0;

out_unरेजिस्टर_xenbus:
	xenbus_unरेजिस्टर_driver(&scsiback_driver);
out:
	pr_err("%s: error %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम __निकास scsiback_निकास(व्योम)
अणु
	target_unरेजिस्टर_ढाँचा(&scsiback_ops);
	xenbus_unरेजिस्टर_driver(&scsiback_driver);
पूर्ण

module_init(scsiback_init);
module_निकास(scsiback_निकास);

MODULE_DESCRIPTION("Xen SCSI backend driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("xen-backend:vscsi");
MODULE_AUTHOR("Juergen Gross <jgross@suse.com>");
