<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/mempool.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/fc_frame.h>
#समावेश "fnic_io.h"
#समावेश "fnic.h"

स्थिर अक्षर *fnic_state_str[] = अणु
	[FNIC_IN_FC_MODE] =           "FNIC_IN_FC_MODE",
	[FNIC_IN_FC_TRANS_ETH_MODE] = "FNIC_IN_FC_TRANS_ETH_MODE",
	[FNIC_IN_ETH_MODE] =          "FNIC_IN_ETH_MODE",
	[FNIC_IN_ETH_TRANS_FC_MODE] = "FNIC_IN_ETH_TRANS_FC_MODE",
पूर्ण;

अटल स्थिर अक्षर *fnic_ioreq_state_str[] = अणु
	[FNIC_IOREQ_NOT_INITED] = "FNIC_IOREQ_NOT_INITED",
	[FNIC_IOREQ_CMD_PENDING] = "FNIC_IOREQ_CMD_PENDING",
	[FNIC_IOREQ_ABTS_PENDING] = "FNIC_IOREQ_ABTS_PENDING",
	[FNIC_IOREQ_ABTS_COMPLETE] = "FNIC_IOREQ_ABTS_COMPLETE",
	[FNIC_IOREQ_CMD_COMPLETE] = "FNIC_IOREQ_CMD_COMPLETE",
पूर्ण;

अटल स्थिर अक्षर *fcpio_status_str[] =  अणु
	[FCPIO_SUCCESS] = "FCPIO_SUCCESS", /*0x0*/
	[FCPIO_INVALID_HEADER] = "FCPIO_INVALID_HEADER",
	[FCPIO_OUT_OF_RESOURCE] = "FCPIO_OUT_OF_RESOURCE",
	[FCPIO_INVALID_PARAM] = "FCPIO_INVALID_PARAM]",
	[FCPIO_REQ_NOT_SUPPORTED] = "FCPIO_REQ_NOT_SUPPORTED",
	[FCPIO_IO_NOT_FOUND] = "FCPIO_IO_NOT_FOUND",
	[FCPIO_ABORTED] = "FCPIO_ABORTED", /*0x41*/
	[FCPIO_TIMEOUT] = "FCPIO_TIMEOUT",
	[FCPIO_SGL_INVALID] = "FCPIO_SGL_INVALID",
	[FCPIO_MSS_INVALID] = "FCPIO_MSS_INVALID",
	[FCPIO_DATA_CNT_MISMATCH] = "FCPIO_DATA_CNT_MISMATCH",
	[FCPIO_FW_ERR] = "FCPIO_FW_ERR",
	[FCPIO_ITMF_REJECTED] = "FCPIO_ITMF_REJECTED",
	[FCPIO_ITMF_FAILED] = "FCPIO_ITMF_FAILED",
	[FCPIO_ITMF_INCORRECT_LUN] = "FCPIO_ITMF_INCORRECT_LUN",
	[FCPIO_CMND_REJECTED] = "FCPIO_CMND_REJECTED",
	[FCPIO_NO_PATH_AVAIL] = "FCPIO_NO_PATH_AVAIL",
	[FCPIO_PATH_FAILED] = "FCPIO_PATH_FAILED",
	[FCPIO_LUNMAP_CHNG_PEND] = "FCPIO_LUNHMAP_CHNG_PEND",
पूर्ण;

स्थिर अक्षर *fnic_state_to_str(अचिन्हित पूर्णांक state)
अणु
	अगर (state >= ARRAY_SIZE(fnic_state_str) || !fnic_state_str[state])
		वापस "unknown";

	वापस fnic_state_str[state];
पूर्ण

अटल स्थिर अक्षर *fnic_ioreq_state_to_str(अचिन्हित पूर्णांक state)
अणु
	अगर (state >= ARRAY_SIZE(fnic_ioreq_state_str) ||
	    !fnic_ioreq_state_str[state])
		वापस "unknown";

	वापस fnic_ioreq_state_str[state];
पूर्ण

अटल स्थिर अक्षर *fnic_fcpio_status_to_str(अचिन्हित पूर्णांक status)
अणु
	अगर (status >= ARRAY_SIZE(fcpio_status_str) || !fcpio_status_str[status])
		वापस "unknown";

	वापस fcpio_status_str[status];
पूर्ण

अटल व्योम fnic_cleanup_io(काष्ठा fnic *fnic);

अटल अंतरभूत spinlock_t *fnic_io_lock_hash(काष्ठा fnic *fnic,
					    काष्ठा scsi_cmnd *sc)
अणु
	u32 hash = sc->request->tag & (FNIC_IO_LOCKS - 1);

	वापस &fnic->io_req_lock[hash];
पूर्ण

अटल अंतरभूत spinlock_t *fnic_io_lock_tag(काष्ठा fnic *fnic,
					    पूर्णांक tag)
अणु
	वापस &fnic->io_req_lock[tag & (FNIC_IO_LOCKS - 1)];
पूर्ण

/*
 * Unmap the data buffer and sense buffer क्रम an io_req,
 * also unmap and मुक्त the device-निजी scatter/gather list.
 */
अटल व्योम fnic_release_ioreq_buf(काष्ठा fnic *fnic,
				   काष्ठा fnic_io_req *io_req,
				   काष्ठा scsi_cmnd *sc)
अणु
	अगर (io_req->sgl_list_pa)
		dma_unmap_single(&fnic->pdev->dev, io_req->sgl_list_pa,
				 माप(io_req->sgl_list[0]) * io_req->sgl_cnt,
				 DMA_TO_DEVICE);
	scsi_dma_unmap(sc);

	अगर (io_req->sgl_cnt)
		mempool_मुक्त(io_req->sgl_list_alloc,
			     fnic->io_sgl_pool[io_req->sgl_type]);
	अगर (io_req->sense_buf_pa)
		dma_unmap_single(&fnic->pdev->dev, io_req->sense_buf_pa,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
पूर्ण

/* Free up Copy Wq descriptors. Called with copy_wq lock held */
अटल पूर्णांक मुक्त_wq_copy_descs(काष्ठा fnic *fnic, काष्ठा vnic_wq_copy *wq)
अणु
	/* अगर no Ack received from firmware, then nothing to clean */
	अगर (!fnic->fw_ack_recd[0])
		वापस 1;

	/*
	 * Update desc_available count based on number of मुक्तd descriptors
	 * Account क्रम wraparound
	 */
	अगर (wq->to_clean_index <= fnic->fw_ack_index[0])
		wq->ring.desc_avail += (fnic->fw_ack_index[0]
					- wq->to_clean_index + 1);
	अन्यथा
		wq->ring.desc_avail += (wq->ring.desc_count
					- wq->to_clean_index
					+ fnic->fw_ack_index[0] + 1);

	/*
	 * just bump clean index to ack_index+1 accounting क्रम wraparound
	 * this will essentially मुक्त up all descriptors between
	 * to_clean_index and fw_ack_index, both inclusive
	 */
	wq->to_clean_index =
		(fnic->fw_ack_index[0] + 1) % wq->ring.desc_count;

	/* we have processed the acks received so far */
	fnic->fw_ack_recd[0] = 0;
	वापस 0;
पूर्ण


/*
 * __fnic_set_state_flags
 * Sets/Clears bits in fnic's state_flags
 **/
व्योम
__fnic_set_state_flags(काष्ठा fnic *fnic, अचिन्हित दीर्घ st_flags,
			अचिन्हित दीर्घ clearbits)
अणु
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ host_lock_flags = 0;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	spin_lock_irqsave(fnic->lport->host->host_lock, host_lock_flags);

	अगर (clearbits)
		fnic->state_flags &= ~st_flags;
	अन्यथा
		fnic->state_flags |= st_flags;

	spin_unlock_irqrestore(fnic->lport->host->host_lock, host_lock_flags);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	वापस;
पूर्ण


/*
 * fnic_fw_reset_handler
 * Routine to send reset msg to fw
 */
पूर्णांक fnic_fw_reset_handler(काष्ठा fnic *fnic)
अणु
	काष्ठा vnic_wq_copy *wq = &fnic->wq_copy[0];
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	/* indicate fwreset to io path */
	fnic_set_state_flags(fnic, FNIC_FLAGS_FWRESET);

	skb_queue_purge(&fnic->frame_queue);
	skb_queue_purge(&fnic->tx_queue);

	/* रुको क्रम io cmpl */
	जबतक (atomic_पढ़ो(&fnic->in_flight))
		schedule_समयout(msecs_to_jअगरfies(1));

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	अगर (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		मुक्त_wq_copy_descs(fnic, wq);

	अगर (!vnic_wq_copy_desc_avail(wq))
		ret = -EAGAIN;
	अन्यथा अणु
		fnic_queue_wq_copy_desc_fw_reset(wq, SCSI_NO_TAG);
		atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
		अगर (atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
			  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.max_fw_reqs))
			atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
				atomic64_पढ़ो(
				  &fnic->fnic_stats.fw_stats.active_fw_reqs));
	पूर्ण

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);

	अगर (!ret) अणु
		atomic64_inc(&fnic->fnic_stats.reset_stats.fw_resets);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Issued fw reset\n");
	पूर्ण अन्यथा अणु
		fnic_clear_state_flags(fnic, FNIC_FLAGS_FWRESET);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Failed to issue fw reset\n");
	पूर्ण

	वापस ret;
पूर्ण


/*
 * fnic_flogi_reg_handler
 * Routine to send flogi रेजिस्टर msg to fw
 */
पूर्णांक fnic_flogi_reg_handler(काष्ठा fnic *fnic, u32 fc_id)
अणु
	काष्ठा vnic_wq_copy *wq = &fnic->wq_copy[0];
	क्रमागत fcpio_flogi_reg_क्रमmat_type क्रमmat;
	काष्ठा fc_lport *lp = fnic->lport;
	u8 gw_mac[ETH_ALEN];
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	अगर (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		मुक्त_wq_copy_descs(fnic, wq);

	अगर (!vnic_wq_copy_desc_avail(wq)) अणु
		ret = -EAGAIN;
		जाओ flogi_reg_ioreq_end;
	पूर्ण

	अगर (fnic->ctlr.map_dest) अणु
		eth_broadcast_addr(gw_mac);
		क्रमmat = FCPIO_FLOGI_REG_DEF_DEST;
	पूर्ण अन्यथा अणु
		स_नकल(gw_mac, fnic->ctlr.dest_addr, ETH_ALEN);
		क्रमmat = FCPIO_FLOGI_REG_GW_DEST;
	पूर्ण

	अगर ((fnic->config.flags & VFCF_FIP_CAPABLE) && !fnic->ctlr.map_dest) अणु
		fnic_queue_wq_copy_desc_fip_reg(wq, SCSI_NO_TAG,
						fc_id, gw_mac,
						fnic->data_src_addr,
						lp->r_a_tov, lp->e_d_tov);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "FLOGI FIP reg issued fcid %x src %pM dest %pM\n",
			      fc_id, fnic->data_src_addr, gw_mac);
	पूर्ण अन्यथा अणु
		fnic_queue_wq_copy_desc_flogi_reg(wq, SCSI_NO_TAG,
						  क्रमmat, fc_id, gw_mac);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "FLOGI reg issued fcid %x map %d dest %pM\n",
			      fc_id, fnic->ctlr.map_dest, gw_mac);
	पूर्ण

	atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
	अगर (atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.max_fw_reqs))
		atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs));

flogi_reg_ioreq_end:
	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
	वापस ret;
पूर्ण

/*
 * fnic_queue_wq_copy_desc
 * Routine to enqueue a wq copy desc
 */
अटल अंतरभूत पूर्णांक fnic_queue_wq_copy_desc(काष्ठा fnic *fnic,
					  काष्ठा vnic_wq_copy *wq,
					  काष्ठा fnic_io_req *io_req,
					  काष्ठा scsi_cmnd *sc,
					  पूर्णांक sg_count)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc->device));
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा host_sg_desc *desc;
	काष्ठा misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ पूर्णांकr_flags;
	पूर्णांक flags;
	u8 exch_flags;
	काष्ठा scsi_lun fc_lun;

	अगर (sg_count) अणु
		/* For each SGE, create a device desc entry */
		desc = io_req->sgl_list;
		क्रम_each_sg(scsi_sglist(sc), sg, sg_count, i) अणु
			desc->addr = cpu_to_le64(sg_dma_address(sg));
			desc->len = cpu_to_le32(sg_dma_len(sg));
			desc->_resvd = 0;
			desc++;
		पूर्ण

		io_req->sgl_list_pa = dma_map_single(&fnic->pdev->dev,
				io_req->sgl_list,
				माप(io_req->sgl_list[0]) * sg_count,
				DMA_TO_DEVICE);
		अगर (dma_mapping_error(&fnic->pdev->dev, io_req->sgl_list_pa)) अणु
			prपूर्णांकk(KERN_ERR "DMA mapping failed\n");
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण
	पूर्ण

	io_req->sense_buf_pa = dma_map_single(&fnic->pdev->dev,
					      sc->sense_buffer,
					      SCSI_SENSE_BUFFERSIZE,
					      DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&fnic->pdev->dev, io_req->sense_buf_pa)) अणु
		dma_unmap_single(&fnic->pdev->dev, io_req->sgl_list_pa,
				माप(io_req->sgl_list[0]) * sg_count,
				DMA_TO_DEVICE);
		prपूर्णांकk(KERN_ERR "DMA mapping failed\n");
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);

	/* Enqueue the descriptor in the Copy WQ */
	spin_lock_irqsave(&fnic->wq_copy_lock[0], पूर्णांकr_flags);

	अगर (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		मुक्त_wq_copy_descs(fnic, wq);

	अगर (unlikely(!vnic_wq_copy_desc_avail(wq))) अणु
		spin_unlock_irqrestore(&fnic->wq_copy_lock[0], पूर्णांकr_flags);
		FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
			  "fnic_queue_wq_copy_desc failure - no descriptors\n");
		atomic64_inc(&misc_stats->io_cpwq_alloc_failures);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	flags = 0;
	अगर (sc->sc_data_direction == DMA_FROM_DEVICE)
		flags = FCPIO_ICMND_RDDATA;
	अन्यथा अगर (sc->sc_data_direction == DMA_TO_DEVICE)
		flags = FCPIO_ICMND_WRDATA;

	exch_flags = 0;
	अगर ((fnic->config.flags & VFCF_FCP_SEQ_LVL_ERR) &&
	    (rp->flags & FC_RP_FLAGS_RETRY))
		exch_flags |= FCPIO_ICMND_SRFLAG_RETRY;

	fnic_queue_wq_copy_desc_icmnd_16(wq, sc->request->tag,
					 0, exch_flags, io_req->sgl_cnt,
					 SCSI_SENSE_BUFFERSIZE,
					 io_req->sgl_list_pa,
					 io_req->sense_buf_pa,
					 0, /* scsi cmd ref, always 0 */
					 FCPIO_ICMND_PTA_SIMPLE,
					 	/* scsi pri and tag */
					 flags,	/* command flags */
					 sc->cmnd, sc->cmd_len,
					 scsi_bufflen(sc),
					 fc_lun.scsi_lun, io_req->port_id,
					 rport->maxframe_size, rp->r_a_tov,
					 rp->e_d_tov);

	atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
	अगर (atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.max_fw_reqs))
		atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs));

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], पूर्णांकr_flags);
	वापस 0;
पूर्ण

/*
 * fnic_queuecommand
 * Routine to send a scsi cdb
 * Called with host_lock held and पूर्णांकerrupts disabled.
 */
अटल पूर्णांक fnic_queuecommand_lck(काष्ठा scsi_cmnd *sc, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा fc_lport *lp = shost_priv(sc->device->host);
	काष्ठा fc_rport *rport;
	काष्ठा fnic_io_req *io_req = शून्य;
	काष्ठा fnic *fnic = lport_priv(lp);
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	काष्ठा vnic_wq_copy *wq;
	पूर्णांक ret;
	u64 cmd_trace;
	पूर्णांक sg_count = 0;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ ptr;
	spinlock_t *io_lock = शून्य;
	पूर्णांक io_lock_acquired = 0;
	काष्ठा fc_rport_libfc_priv *rp;

	अगर (unlikely(fnic_chk_state_flags_locked(fnic, FNIC_FLAGS_IO_BLOCKED)))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (unlikely(fnic_chk_state_flags_locked(fnic, FNIC_FLAGS_FWRESET)))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	rport = starget_to_rport(scsi_target(sc->device));
	अगर (!rport) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"returning DID_NO_CONNECT for IO as rport is NULL\n");
		sc->result = DID_NO_CONNECT << 16;
		करोne(sc);
		वापस 0;
	पूर्ण

	ret = fc_remote_port_chkपढ़ोy(rport);
	अगर (ret) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"rport is not ready\n");
		atomic64_inc(&fnic_stats->misc_stats.rport_not_पढ़ोy);
		sc->result = ret;
		करोne(sc);
		वापस 0;
	पूर्ण

	rp = rport->dd_data;
	अगर (!rp || rp->rp_state == RPORT_ST_DELETE) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"rport 0x%x removed, returning DID_NO_CONNECT\n",
			rport->port_id);

		atomic64_inc(&fnic_stats->misc_stats.rport_not_पढ़ोy);
		sc->result = DID_NO_CONNECT<<16;
		करोne(sc);
		वापस 0;
	पूर्ण

	अगर (rp->rp_state != RPORT_ST_READY) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"rport 0x%x in state 0x%x, returning DID_IMM_RETRY\n",
			rport->port_id, rp->rp_state);

		sc->result = DID_IMM_RETRY << 16;
		करोne(sc);
		वापस 0;
	पूर्ण

	अगर (lp->state != LPORT_ST_READY || !(lp->link_up))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	atomic_inc(&fnic->in_flight);

	/*
	 * Release host lock, use driver resource specअगरic locks from here.
	 * Don't re-enable पूर्णांकerrupts in हाल they were disabled prior to the
	 * caller disabling them.
	 */
	spin_unlock(lp->host->host_lock);
	CMD_STATE(sc) = FNIC_IOREQ_NOT_INITED;
	CMD_FLAGS(sc) = FNIC_NO_FLAGS;

	/* Get a new io_req क्रम this SCSI IO */
	io_req = mempool_alloc(fnic->io_req_pool, GFP_ATOMIC);
	अगर (!io_req) अणु
		atomic64_inc(&fnic_stats->io_stats.alloc_failures);
		ret = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण
	स_रखो(io_req, 0, माप(*io_req));

	/* Map the data buffer */
	sg_count = scsi_dma_map(sc);
	अगर (sg_count < 0) अणु
		FNIC_TRACE(fnic_queuecommand, sc->device->host->host_no,
			  sc->request->tag, sc, 0, sc->cmnd[0],
			  sg_count, CMD_STATE(sc));
		mempool_मुक्त(io_req, fnic->io_req_pool);
		जाओ out;
	पूर्ण

	/* Determine the type of scatter/gather list we need */
	io_req->sgl_cnt = sg_count;
	io_req->sgl_type = FNIC_SGL_CACHE_DFLT;
	अगर (sg_count > FNIC_DFLT_SG_DESC_CNT)
		io_req->sgl_type = FNIC_SGL_CACHE_MAX;

	अगर (sg_count) अणु
		io_req->sgl_list =
			mempool_alloc(fnic->io_sgl_pool[io_req->sgl_type],
				      GFP_ATOMIC);
		अगर (!io_req->sgl_list) अणु
			atomic64_inc(&fnic_stats->io_stats.alloc_failures);
			ret = SCSI_MLQUEUE_HOST_BUSY;
			scsi_dma_unmap(sc);
			mempool_मुक्त(io_req, fnic->io_req_pool);
			जाओ out;
		पूर्ण

		/* Cache sgl list allocated address beक्रमe alignment */
		io_req->sgl_list_alloc = io_req->sgl_list;
		ptr = (अचिन्हित दीर्घ) io_req->sgl_list;
		अगर (ptr % FNIC_SG_DESC_ALIGN) अणु
			io_req->sgl_list = (काष्ठा host_sg_desc *)
				(((अचिन्हित दीर्घ) ptr
				  + FNIC_SG_DESC_ALIGN - 1)
				 & ~(FNIC_SG_DESC_ALIGN - 1));
		पूर्ण
	पूर्ण

	/*
	* Will acquire lock deक्रमe setting to IO initialized.
	*/

	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);

	/* initialize rest of io_req */
	io_lock_acquired = 1;
	io_req->port_id = rport->port_id;
	io_req->start_समय = jअगरfies;
	CMD_STATE(sc) = FNIC_IOREQ_CMD_PENDING;
	CMD_SP(sc) = (अक्षर *)io_req;
	CMD_FLAGS(sc) |= FNIC_IO_INITIALIZED;
	sc->scsi_करोne = करोne;

	/* create copy wq desc and enqueue it */
	wq = &fnic->wq_copy[0];
	ret = fnic_queue_wq_copy_desc(fnic, wq, io_req, sc, sg_count);
	अगर (ret) अणु
		/*
		 * In हाल another thपढ़ो cancelled the request,
		 * refetch the poपूर्णांकer under the lock.
		 */
		FNIC_TRACE(fnic_queuecommand, sc->device->host->host_no,
			  sc->request->tag, sc, 0, 0, 0,
			  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		CMD_SP(sc) = शून्य;
		CMD_STATE(sc) = FNIC_IOREQ_CMD_COMPLETE;
		spin_unlock_irqrestore(io_lock, flags);
		अगर (io_req) अणु
			fnic_release_ioreq_buf(fnic, io_req, sc);
			mempool_मुक्त(io_req, fnic->io_req_pool);
		पूर्ण
		atomic_dec(&fnic->in_flight);
		/* acquire host lock beक्रमe वापसing to SCSI */
		spin_lock(lp->host->host_lock);
		वापस ret;
	पूर्ण अन्यथा अणु
		atomic64_inc(&fnic_stats->io_stats.active_ios);
		atomic64_inc(&fnic_stats->io_stats.num_ios);
		अगर (atomic64_पढ़ो(&fnic_stats->io_stats.active_ios) >
			  atomic64_पढ़ो(&fnic_stats->io_stats.max_active_ios))
			atomic64_set(&fnic_stats->io_stats.max_active_ios,
			     atomic64_पढ़ो(&fnic_stats->io_stats.active_ios));

		/* REVISIT: Use per IO lock in the final code */
		CMD_FLAGS(sc) |= FNIC_IO_ISSUED;
	पूर्ण
out:
	cmd_trace = ((u64)sc->cmnd[0] << 56 | (u64)sc->cmnd[7] << 40 |
			(u64)sc->cmnd[8] << 32 | (u64)sc->cmnd[2] << 24 |
			(u64)sc->cmnd[3] << 16 | (u64)sc->cmnd[4] << 8 |
			sc->cmnd[5]);

	FNIC_TRACE(fnic_queuecommand, sc->device->host->host_no,
		  sc->request->tag, sc, io_req,
		  sg_count, cmd_trace,
		  (((u64)CMD_FLAGS(sc) >> 32) | CMD_STATE(sc)));

	/* अगर only we issued IO, will we have the io lock */
	अगर (io_lock_acquired)
		spin_unlock_irqrestore(io_lock, flags);

	atomic_dec(&fnic->in_flight);
	/* acquire host lock beक्रमe वापसing to SCSI */
	spin_lock(lp->host->host_lock);
	वापस ret;
पूर्ण

DEF_SCSI_QCMD(fnic_queuecommand)

/*
 * fnic_fcpio_fw_reset_cmpl_handler
 * Routine to handle fw reset completion
 */
अटल पूर्णांक fnic_fcpio_fw_reset_cmpl_handler(काष्ठा fnic *fnic,
					    काष्ठा fcpio_fw_req *desc)
अणु
	u8 type;
	u8 hdr_status;
	काष्ठा fcpio_tag tag;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा reset_stats *reset_stats = &fnic->fnic_stats.reset_stats;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);

	atomic64_inc(&reset_stats->fw_reset_completions);

	/* Clean up all outstanding io requests */
	fnic_cleanup_io(fnic);

	atomic64_set(&fnic->fnic_stats.fw_stats.active_fw_reqs, 0);
	atomic64_set(&fnic->fnic_stats.io_stats.active_ios, 0);
	atomic64_set(&fnic->io_cmpl_skip, 0);

	spin_lock_irqsave(&fnic->fnic_lock, flags);

	/* fnic should be in FC_TRANS_ETH_MODE */
	अगर (fnic->state == FNIC_IN_FC_TRANS_ETH_MODE) अणु
		/* Check status of reset completion */
		अगर (!hdr_status) अणु
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "reset cmpl success\n");
			/* Ready to send flogi out */
			fnic->state = FNIC_IN_ETH_MODE;
		पूर्ण अन्यथा अणु
			FNIC_SCSI_DBG(KERN_DEBUG,
				      fnic->lport->host,
				      "fnic fw_reset : failed %s\n",
				      fnic_fcpio_status_to_str(hdr_status));

			/*
			 * Unable to change to eth mode, cannot send out flogi
			 * Change state to fc mode, so that subsequent Flogi
			 * requests from libFC will cause more attempts to
			 * reset the firmware. Free the cached flogi
			 */
			fnic->state = FNIC_IN_FC_MODE;
			atomic64_inc(&reset_stats->fw_reset_failures);
			ret = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		FNIC_SCSI_DBG(KERN_DEBUG,
			      fnic->lport->host,
			      "Unexpected state %s while processing"
			      " reset cmpl\n", fnic_state_to_str(fnic->state));
		atomic64_inc(&reset_stats->fw_reset_failures);
		ret = -1;
	पूर्ण

	/* Thपढ़ो removing device blocks till firmware reset is complete */
	अगर (fnic->हटाओ_रुको)
		complete(fnic->हटाओ_रुको);

	/*
	 * If fnic is being हटाओd, or fw reset failed
	 * मुक्त the flogi frame. Else, send it out
	 */
	अगर (fnic->हटाओ_रुको || ret) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		skb_queue_purge(&fnic->tx_queue);
		जाओ reset_cmpl_handler_end;
	पूर्ण

	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	fnic_flush_tx(fnic);

 reset_cmpl_handler_end:
	fnic_clear_state_flags(fnic, FNIC_FLAGS_FWRESET);

	वापस ret;
पूर्ण

/*
 * fnic_fcpio_flogi_reg_cmpl_handler
 * Routine to handle flogi रेजिस्टर completion
 */
अटल पूर्णांक fnic_fcpio_flogi_reg_cmpl_handler(काष्ठा fnic *fnic,
					     काष्ठा fcpio_fw_req *desc)
अणु
	u8 type;
	u8 hdr_status;
	काष्ठा fcpio_tag tag;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);

	/* Update fnic state based on status of flogi reg completion */
	spin_lock_irqsave(&fnic->fnic_lock, flags);

	अगर (fnic->state == FNIC_IN_ETH_TRANS_FC_MODE) अणु

		/* Check flogi registration completion status */
		अगर (!hdr_status) अणु
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "flog reg succeeded\n");
			fnic->state = FNIC_IN_FC_MODE;
		पूर्ण अन्यथा अणु
			FNIC_SCSI_DBG(KERN_DEBUG,
				      fnic->lport->host,
				      "fnic flogi reg :failed %s\n",
				      fnic_fcpio_status_to_str(hdr_status));
			fnic->state = FNIC_IN_ETH_MODE;
			ret = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Unexpected fnic state %s while"
			      " processing flogi reg completion\n",
			      fnic_state_to_str(fnic->state));
		ret = -1;
	पूर्ण

	अगर (!ret) अणु
		अगर (fnic->stop_rx_link_events) अणु
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			जाओ reg_cmpl_handler_end;
		पूर्ण
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		fnic_flush_tx(fnic);
		queue_work(fnic_event_queue, &fnic->frame_work);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	पूर्ण

reg_cmpl_handler_end:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक is_ack_index_in_range(काष्ठा vnic_wq_copy *wq,
					u16 request_out)
अणु
	अगर (wq->to_clean_index <= wq->to_use_index) अणु
		/* out of range, stale request_out index */
		अगर (request_out < wq->to_clean_index ||
		    request_out >= wq->to_use_index)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* out of range, stale request_out index */
		अगर (request_out < wq->to_clean_index &&
		    request_out >= wq->to_use_index)
			वापस 0;
	पूर्ण
	/* request_out index is in range */
	वापस 1;
पूर्ण


/*
 * Mark that ack received and store the Ack index. If there are multiple
 * acks received beक्रमe Tx thपढ़ो cleans it up, the latest value will be
 * used which is correct behavior. This state should be in the copy Wq
 * instead of in the fnic
 */
अटल अंतरभूत व्योम fnic_fcpio_ack_handler(काष्ठा fnic *fnic,
					  अचिन्हित पूर्णांक cq_index,
					  काष्ठा fcpio_fw_req *desc)
अणु
	काष्ठा vnic_wq_copy *wq;
	u16 request_out = desc->u.ack.request_out;
	अचिन्हित दीर्घ flags;
	u64 *ox_id_tag = (u64 *)(व्योम *)desc;

	/* mark the ack state */
	wq = &fnic->wq_copy[cq_index - fnic->raw_wq_count - fnic->rq_count];
	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	fnic->fnic_stats.misc_stats.last_ack_समय = jअगरfies;
	अगर (is_ack_index_in_range(wq, request_out)) अणु
		fnic->fw_ack_index[0] = request_out;
		fnic->fw_ack_recd[0] = 1;
	पूर्ण अन्यथा
		atomic64_inc(
			&fnic->fnic_stats.misc_stats.ack_index_out_of_range);

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
	FNIC_TRACE(fnic_fcpio_ack_handler,
		  fnic->lport->host->host_no, 0, 0, ox_id_tag[2], ox_id_tag[3],
		  ox_id_tag[4], ox_id_tag[5]);
पूर्ण

/*
 * fnic_fcpio_icmnd_cmpl_handler
 * Routine to handle icmnd completions
 */
अटल व्योम fnic_fcpio_icmnd_cmpl_handler(काष्ठा fnic *fnic,
					 काष्ठा fcpio_fw_req *desc)
अणु
	u8 type;
	u8 hdr_status;
	काष्ठा fcpio_tag tag;
	u32 id;
	u64 xfer_len = 0;
	काष्ठा fcpio_icmnd_cmpl *icmnd_cmpl;
	काष्ठा fnic_io_req *io_req;
	काष्ठा scsi_cmnd *sc;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	अचिन्हित दीर्घ flags;
	spinlock_t *io_lock;
	u64 cmd_trace;
	अचिन्हित दीर्घ start_समय;
	अचिन्हित दीर्घ io_duration_समय;

	/* Decode the cmpl description to get the io_req id */
	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);
	fcpio_tag_id_dec(&tag, &id);
	icmnd_cmpl = &desc->u.icmnd_cmpl;

	अगर (id >= fnic->fnic_max_tag_id) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			"Tag out of range tag %x hdr status = %s\n",
			     id, fnic_fcpio_status_to_str(hdr_status));
		वापस;
	पूर्ण

	sc = scsi_host_find_tag(fnic->lport->host, id);
	WARN_ON_ONCE(!sc);
	अगर (!sc) अणु
		atomic64_inc(&fnic_stats->io_stats.sc_null);
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			  "icmnd_cmpl sc is null - "
			  "hdr status = %s tag = 0x%x desc = 0x%p\n",
			  fnic_fcpio_status_to_str(hdr_status), id, desc);
		FNIC_TRACE(fnic_fcpio_icmnd_cmpl_handler,
			  fnic->lport->host->host_no, id,
			  ((u64)icmnd_cmpl->_resvd0[1] << 16 |
			  (u64)icmnd_cmpl->_resvd0[0]),
			  ((u64)hdr_status << 16 |
			  (u64)icmnd_cmpl->scsi_status << 8 |
			  (u64)icmnd_cmpl->flags), desc,
			  (u64)icmnd_cmpl->residual, 0);
		वापस;
	पूर्ण

	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	WARN_ON_ONCE(!io_req);
	अगर (!io_req) अणु
		atomic64_inc(&fnic_stats->io_stats.ioreq_null);
		CMD_FLAGS(sc) |= FNIC_IO_REQ_शून्य;
		spin_unlock_irqrestore(io_lock, flags);
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			  "icmnd_cmpl io_req is null - "
			  "hdr status = %s tag = 0x%x sc 0x%p\n",
			  fnic_fcpio_status_to_str(hdr_status), id, sc);
		वापस;
	पूर्ण
	start_समय = io_req->start_समय;

	/* firmware completed the io */
	io_req->io_completed = 1;

	/*
	 *  अगर SCSI-ML has alपढ़ोy issued पात on this command,
	 *  set completion of the IO. The abts path will clean it up
	 */
	अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING) अणु

		/*
		 * set the FNIC_IO_DONE so that this करोesn't get
		 * flagged as 'out of order' अगर it was not पातed
		 */
		CMD_FLAGS(sc) |= FNIC_IO_DONE;
		CMD_FLAGS(sc) |= FNIC_IO_ABTS_PENDING;
		spin_unlock_irqrestore(io_lock, flags);
		अगर(FCPIO_ABORTED == hdr_status)
			CMD_FLAGS(sc) |= FNIC_IO_ABORTED;

		FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
			"icmnd_cmpl abts pending "
			  "hdr status = %s tag = 0x%x sc = 0x%p "
			  "scsi_status = %x residual = %d\n",
			  fnic_fcpio_status_to_str(hdr_status),
			  id, sc,
			  icmnd_cmpl->scsi_status,
			  icmnd_cmpl->residual);
		वापस;
	पूर्ण

	/* Mark the IO as complete */
	CMD_STATE(sc) = FNIC_IOREQ_CMD_COMPLETE;

	icmnd_cmpl = &desc->u.icmnd_cmpl;

	चयन (hdr_status) अणु
	हाल FCPIO_SUCCESS:
		sc->result = (DID_OK << 16) | icmnd_cmpl->scsi_status;
		xfer_len = scsi_bufflen(sc);

		अगर (icmnd_cmpl->flags & FCPIO_ICMND_CMPL_RESID_UNDER) अणु
			xfer_len -= icmnd_cmpl->residual;
			scsi_set_resid(sc, icmnd_cmpl->residual);
		पूर्ण

		अगर (icmnd_cmpl->scsi_status == SAM_STAT_CHECK_CONDITION)
			atomic64_inc(&fnic_stats->misc_stats.check_condition);

		अगर (icmnd_cmpl->scsi_status == SAM_STAT_TASK_SET_FULL)
			atomic64_inc(&fnic_stats->misc_stats.queue_fulls);
		अवरोध;

	हाल FCPIO_TIMEOUT:          /* request was समयd out */
		atomic64_inc(&fnic_stats->misc_stats.fcpio_समयout);
		sc->result = (DID_TIME_OUT << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_ABORTED:          /* request was पातed */
		atomic64_inc(&fnic_stats->misc_stats.fcpio_पातed);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_DATA_CNT_MISMATCH: /* recv/sent more/less data than exp. */
		atomic64_inc(&fnic_stats->misc_stats.data_count_mismatch);
		scsi_set_resid(sc, icmnd_cmpl->residual);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_OUT_OF_RESOURCE:  /* out of resources to complete request */
		atomic64_inc(&fnic_stats->fw_stats.fw_out_of_resources);
		sc->result = (DID_REQUEUE << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_IO_NOT_FOUND:     /* requested I/O was not found */
		atomic64_inc(&fnic_stats->io_stats.io_not_found);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_SGL_INVALID:      /* request was पातed due to sgl error */
		atomic64_inc(&fnic_stats->misc_stats.sgl_invalid);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_FW_ERR:           /* request was terminated due fw error */
		atomic64_inc(&fnic_stats->fw_stats.io_fw_errs);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_MSS_INVALID:      /* request was पातed due to mss error */
		atomic64_inc(&fnic_stats->misc_stats.mss_invalid);
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;

	हाल FCPIO_INVALID_HEADER:   /* header contains invalid data */
	हाल FCPIO_INVALID_PARAM:    /* some parameter in request invalid */
	हाल FCPIO_REQ_NOT_SUPPORTED:/* request type is not supported */
	शेष:
		sc->result = (DID_ERROR << 16) | icmnd_cmpl->scsi_status;
		अवरोध;
	पूर्ण

	/* Break link with the SCSI command */
	CMD_SP(sc) = शून्य;
	CMD_FLAGS(sc) |= FNIC_IO_DONE;

	spin_unlock_irqrestore(io_lock, flags);

	अगर (hdr_status != FCPIO_SUCCESS) अणु
		atomic64_inc(&fnic_stats->io_stats.io_failures);
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host, "hdr status = %s\n",
			     fnic_fcpio_status_to_str(hdr_status));
	पूर्ण

	fnic_release_ioreq_buf(fnic, io_req, sc);

	mempool_मुक्त(io_req, fnic->io_req_pool);

	cmd_trace = ((u64)hdr_status << 56) |
		  (u64)icmnd_cmpl->scsi_status << 48 |
		  (u64)icmnd_cmpl->flags << 40 | (u64)sc->cmnd[0] << 32 |
		  (u64)sc->cmnd[2] << 24 | (u64)sc->cmnd[3] << 16 |
		  (u64)sc->cmnd[4] << 8 | sc->cmnd[5];

	FNIC_TRACE(fnic_fcpio_icmnd_cmpl_handler,
		  sc->device->host->host_no, id, sc,
		  ((u64)icmnd_cmpl->_resvd0[1] << 56 |
		  (u64)icmnd_cmpl->_resvd0[0] << 48 |
		  jअगरfies_to_msecs(jअगरfies - start_समय)),
		  desc, cmd_trace,
		  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));

	अगर (sc->sc_data_direction == DMA_FROM_DEVICE) अणु
		fnic->lport->host_stats.fcp_input_requests++;
		fnic->fcp_input_bytes += xfer_len;
	पूर्ण अन्यथा अगर (sc->sc_data_direction == DMA_TO_DEVICE) अणु
		fnic->lport->host_stats.fcp_output_requests++;
		fnic->fcp_output_bytes += xfer_len;
	पूर्ण अन्यथा
		fnic->lport->host_stats.fcp_control_requests++;

	atomic64_dec(&fnic_stats->io_stats.active_ios);
	अगर (atomic64_पढ़ो(&fnic->io_cmpl_skip))
		atomic64_dec(&fnic->io_cmpl_skip);
	अन्यथा
		atomic64_inc(&fnic_stats->io_stats.io_completions);


	io_duration_समय = jअगरfies_to_msecs(jअगरfies) -
						jअगरfies_to_msecs(start_समय);

	अगर(io_duration_समय <= 10)
		atomic64_inc(&fnic_stats->io_stats.io_btw_0_to_10_msec);
	अन्यथा अगर(io_duration_समय <= 100)
		atomic64_inc(&fnic_stats->io_stats.io_btw_10_to_100_msec);
	अन्यथा अगर(io_duration_समय <= 500)
		atomic64_inc(&fnic_stats->io_stats.io_btw_100_to_500_msec);
	अन्यथा अगर(io_duration_समय <= 5000)
		atomic64_inc(&fnic_stats->io_stats.io_btw_500_to_5000_msec);
	अन्यथा अगर(io_duration_समय <= 10000)
		atomic64_inc(&fnic_stats->io_stats.io_btw_5000_to_10000_msec);
	अन्यथा अगर(io_duration_समय <= 30000)
		atomic64_inc(&fnic_stats->io_stats.io_btw_10000_to_30000_msec);
	अन्यथा अणु
		atomic64_inc(&fnic_stats->io_stats.io_greater_than_30000_msec);

		अगर(io_duration_समय > atomic64_पढ़ो(&fnic_stats->io_stats.current_max_io_समय))
			atomic64_set(&fnic_stats->io_stats.current_max_io_समय, io_duration_समय);
	पूर्ण

	/* Call SCSI completion function to complete the IO */
	अगर (sc->scsi_करोne)
		sc->scsi_करोne(sc);
पूर्ण

/* fnic_fcpio_iपंचांगf_cmpl_handler
 * Routine to handle iपंचांगf completions
 */
अटल व्योम fnic_fcpio_iपंचांगf_cmpl_handler(काष्ठा fnic *fnic,
					काष्ठा fcpio_fw_req *desc)
अणु
	u8 type;
	u8 hdr_status;
	काष्ठा fcpio_tag tag;
	u32 id;
	काष्ठा scsi_cmnd *sc;
	काष्ठा fnic_io_req *io_req;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	काष्ठा पात_stats *abts_stats = &fnic->fnic_stats.abts_stats;
	काष्ठा terminate_stats *term_stats = &fnic->fnic_stats.term_stats;
	काष्ठा misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	अचिन्हित दीर्घ flags;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ start_समय;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);
	fcpio_tag_id_dec(&tag, &id);

	अगर ((id & FNIC_TAG_MASK) >= fnic->fnic_max_tag_id) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
		"Tag out of range tag %x hdr status = %s\n",
		id, fnic_fcpio_status_to_str(hdr_status));
		वापस;
	पूर्ण

	sc = scsi_host_find_tag(fnic->lport->host, id & FNIC_TAG_MASK);
	WARN_ON_ONCE(!sc);
	अगर (!sc) अणु
		atomic64_inc(&fnic_stats->io_stats.sc_null);
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			  "itmf_cmpl sc is null - hdr status = %s tag = 0x%x\n",
			  fnic_fcpio_status_to_str(hdr_status), id);
		वापस;
	पूर्ण
	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	WARN_ON_ONCE(!io_req);
	अगर (!io_req) अणु
		atomic64_inc(&fnic_stats->io_stats.ioreq_null);
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_REQ_शून्य;
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			  "itmf_cmpl io_req is null - "
			  "hdr status = %s tag = 0x%x sc 0x%p\n",
			  fnic_fcpio_status_to_str(hdr_status), id, sc);
		वापस;
	पूर्ण
	start_समय = io_req->start_समय;

	अगर ((id & FNIC_TAG_ABORT) && (id & FNIC_TAG_DEV_RST)) अणु
		/* Abort and terminate completion of device reset req */
		/* REVISIT : Add निश्चितs about various flags */
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "dev reset abts cmpl recd. id %x status %s\n",
			      id, fnic_fcpio_status_to_str(hdr_status));
		CMD_STATE(sc) = FNIC_IOREQ_ABTS_COMPLETE;
		CMD_ABTS_STATUS(sc) = hdr_status;
		CMD_FLAGS(sc) |= FNIC_DEV_RST_DONE;
		अगर (io_req->abts_करोne)
			complete(io_req->abts_करोne);
		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण अन्यथा अगर (id & FNIC_TAG_ABORT) अणु
		/* Completion of पात cmd */
		चयन (hdr_status) अणु
		हाल FCPIO_SUCCESS:
			अवरोध;
		हाल FCPIO_TIMEOUT:
			अगर (CMD_FLAGS(sc) & FNIC_IO_ABTS_ISSUED)
				atomic64_inc(&abts_stats->पात_fw_समयouts);
			अन्यथा
				atomic64_inc(
					&term_stats->terminate_fw_समयouts);
			अवरोध;
		हाल FCPIO_ITMF_REJECTED:
			FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
				"abort reject recd. id %d\n",
				(पूर्णांक)(id & FNIC_TAG_MASK));
			अवरोध;
		हाल FCPIO_IO_NOT_FOUND:
			अगर (CMD_FLAGS(sc) & FNIC_IO_ABTS_ISSUED)
				atomic64_inc(&abts_stats->पात_io_not_found);
			अन्यथा
				atomic64_inc(
					&term_stats->terminate_io_not_found);
			अवरोध;
		शेष:
			अगर (CMD_FLAGS(sc) & FNIC_IO_ABTS_ISSUED)
				atomic64_inc(&abts_stats->पात_failures);
			अन्यथा
				atomic64_inc(
					&term_stats->terminate_failures);
			अवरोध;
		पूर्ण
		अगर (CMD_STATE(sc) != FNIC_IOREQ_ABTS_PENDING) अणु
			/* This is a late completion. Ignore it */
			spin_unlock_irqrestore(io_lock, flags);
			वापस;
		पूर्ण

		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_DONE;
		CMD_ABTS_STATUS(sc) = hdr_status;

		/* If the status is IO not found consider it as success */
		अगर (hdr_status == FCPIO_IO_NOT_FOUND)
			CMD_ABTS_STATUS(sc) = FCPIO_SUCCESS;

		अगर (!(CMD_FLAGS(sc) & (FNIC_IO_ABORTED | FNIC_IO_DONE)))
			atomic64_inc(&misc_stats->no_icmnd_iपंचांगf_cmpls);

		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "abts cmpl recd. id %d status %s\n",
			      (पूर्णांक)(id & FNIC_TAG_MASK),
			      fnic_fcpio_status_to_str(hdr_status));

		/*
		 * If scsi_eh thपढ़ो is blocked रुकोing क्रम abts to complete,
		 * संकेत completion to it. IO will be cleaned in the thपढ़ो
		 * अन्यथा clean it in this context
		 */
		अगर (io_req->abts_करोne) अणु
			complete(io_req->abts_करोne);
			spin_unlock_irqrestore(io_lock, flags);
		पूर्ण अन्यथा अणु
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "abts cmpl, completing IO\n");
			CMD_SP(sc) = शून्य;
			sc->result = (DID_ERROR << 16);

			spin_unlock_irqrestore(io_lock, flags);

			fnic_release_ioreq_buf(fnic, io_req, sc);
			mempool_मुक्त(io_req, fnic->io_req_pool);
			अगर (sc->scsi_करोne) अणु
				FNIC_TRACE(fnic_fcpio_iपंचांगf_cmpl_handler,
					sc->device->host->host_no, id,
					sc,
					jअगरfies_to_msecs(jअगरfies - start_समय),
					desc,
					(((u64)hdr_status << 40) |
					(u64)sc->cmnd[0] << 32 |
					(u64)sc->cmnd[2] << 24 |
					(u64)sc->cmnd[3] << 16 |
					(u64)sc->cmnd[4] << 8 | sc->cmnd[5]),
					(((u64)CMD_FLAGS(sc) << 32) |
					CMD_STATE(sc)));
				sc->scsi_करोne(sc);
				atomic64_dec(&fnic_stats->io_stats.active_ios);
				अगर (atomic64_पढ़ो(&fnic->io_cmpl_skip))
					atomic64_dec(&fnic->io_cmpl_skip);
				अन्यथा
					atomic64_inc(&fnic_stats->io_stats.io_completions);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (id & FNIC_TAG_DEV_RST) अणु
		/* Completion of device reset */
		CMD_LR_STATUS(sc) = hdr_status;
		अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING) अणु
			spin_unlock_irqrestore(io_lock, flags);
			CMD_FLAGS(sc) |= FNIC_DEV_RST_ABTS_PENDING;
			FNIC_TRACE(fnic_fcpio_iपंचांगf_cmpl_handler,
				  sc->device->host->host_no, id, sc,
				  jअगरfies_to_msecs(jअगरfies - start_समय),
				  desc, 0,
				  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"Terminate pending "
				"dev reset cmpl recd. id %d status %s\n",
				(पूर्णांक)(id & FNIC_TAG_MASK),
				fnic_fcpio_status_to_str(hdr_status));
			वापस;
		पूर्ण
		अगर (CMD_FLAGS(sc) & FNIC_DEV_RST_TIMED_OUT) अणु
			/* Need to रुको क्रम terminate completion */
			spin_unlock_irqrestore(io_lock, flags);
			FNIC_TRACE(fnic_fcpio_iपंचांगf_cmpl_handler,
				  sc->device->host->host_no, id, sc,
				  jअगरfies_to_msecs(jअगरfies - start_समय),
				  desc, 0,
				  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"dev reset cmpl recd after time out. "
				"id %d status %s\n",
				(पूर्णांक)(id & FNIC_TAG_MASK),
				fnic_fcpio_status_to_str(hdr_status));
			वापस;
		पूर्ण
		CMD_STATE(sc) = FNIC_IOREQ_CMD_COMPLETE;
		CMD_FLAGS(sc) |= FNIC_DEV_RST_DONE;
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "dev reset cmpl recd. id %d status %s\n",
			      (पूर्णांक)(id & FNIC_TAG_MASK),
			      fnic_fcpio_status_to_str(hdr_status));
		अगर (io_req->dr_करोne)
			complete(io_req->dr_करोne);
		spin_unlock_irqrestore(io_lock, flags);

	पूर्ण अन्यथा अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Unexpected itmf io state %s tag %x\n",
			     fnic_ioreq_state_to_str(CMD_STATE(sc)), id);
		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण

पूर्ण

/*
 * fnic_fcpio_cmpl_handler
 * Routine to service the cq क्रम wq_copy
 */
अटल पूर्णांक fnic_fcpio_cmpl_handler(काष्ठा vnic_dev *vdev,
				   अचिन्हित पूर्णांक cq_index,
				   काष्ठा fcpio_fw_req *desc)
अणु
	काष्ठा fnic *fnic = vnic_dev_priv(vdev);

	चयन (desc->hdr.type) अणु
	हाल FCPIO_ICMND_CMPL: /* fw completed a command */
	हाल FCPIO_ITMF_CMPL: /* fw completed iपंचांगf (पात cmd, lun reset)*/
	हाल FCPIO_FLOGI_REG_CMPL: /* fw completed flogi_reg */
	हाल FCPIO_FLOGI_FIP_REG_CMPL: /* fw completed flogi_fip_reg */
	हाल FCPIO_RESET_CMPL: /* fw completed reset */
		atomic64_dec(&fnic->fnic_stats.fw_stats.active_fw_reqs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (desc->hdr.type) अणु
	हाल FCPIO_ACK: /* fw copied copy wq desc to its queue */
		fnic_fcpio_ack_handler(fnic, cq_index, desc);
		अवरोध;

	हाल FCPIO_ICMND_CMPL: /* fw completed a command */
		fnic_fcpio_icmnd_cmpl_handler(fnic, desc);
		अवरोध;

	हाल FCPIO_ITMF_CMPL: /* fw completed iपंचांगf (पात cmd, lun reset)*/
		fnic_fcpio_iपंचांगf_cmpl_handler(fnic, desc);
		अवरोध;

	हाल FCPIO_FLOGI_REG_CMPL: /* fw completed flogi_reg */
	हाल FCPIO_FLOGI_FIP_REG_CMPL: /* fw completed flogi_fip_reg */
		fnic_fcpio_flogi_reg_cmpl_handler(fnic, desc);
		अवरोध;

	हाल FCPIO_RESET_CMPL: /* fw completed reset */
		fnic_fcpio_fw_reset_cmpl_handler(fnic, desc);
		अवरोध;

	शेष:
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "firmware completion type %d\n",
			      desc->hdr.type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * fnic_wq_copy_cmpl_handler
 * Routine to process wq copy
 */
पूर्णांक fnic_wq_copy_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक copy_work_to_करो)
अणु
	अचिन्हित पूर्णांक wq_work_करोne = 0;
	अचिन्हित पूर्णांक i, cq_index;
	अचिन्हित पूर्णांक cur_work_करोne;
	काष्ठा misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	u64 start_jअगरfies = 0;
	u64 end_jअगरfies = 0;
	u64 delta_jअगरfies = 0;
	u64 delta_ms = 0;

	क्रम (i = 0; i < fnic->wq_copy_count; i++) अणु
		cq_index = i + fnic->raw_wq_count + fnic->rq_count;

		start_jअगरfies = jअगरfies;
		cur_work_करोne = vnic_cq_copy_service(&fnic->cq[cq_index],
						     fnic_fcpio_cmpl_handler,
						     copy_work_to_करो);
		end_jअगरfies = jअगरfies;

		wq_work_करोne += cur_work_करोne;
		delta_jअगरfies = end_jअगरfies - start_jअगरfies;
		अगर (delta_jअगरfies >
			(u64) atomic64_पढ़ो(&misc_stats->max_isr_jअगरfies)) अणु
			atomic64_set(&misc_stats->max_isr_jअगरfies,
					delta_jअगरfies);
			delta_ms = jअगरfies_to_msecs(delta_jअगरfies);
			atomic64_set(&misc_stats->max_isr_समय_ms, delta_ms);
			atomic64_set(&misc_stats->corr_work_करोne,
					cur_work_करोne);
		पूर्ण
	पूर्ण
	वापस wq_work_करोne;
पूर्ण

अटल bool fnic_cleanup_io_iter(काष्ठा scsi_cmnd *sc, व्योम *data,
				 bool reserved)
अणु
	काष्ठा fnic *fnic = data;
	काष्ठा fnic_io_req *io_req;
	अचिन्हित दीर्घ flags = 0;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ start_समय = 0;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;

	io_lock = fnic_io_lock_tag(fnic, sc->request->tag);
	spin_lock_irqsave(io_lock, flags);

	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर ((CMD_FLAGS(sc) & FNIC_DEVICE_RESET) &&
	    !(CMD_FLAGS(sc) & FNIC_DEV_RST_DONE)) अणु
		/*
		 * We will be here only when FW completes reset
		 * without sending completions क्रम outstanding ios.
		 */
		CMD_FLAGS(sc) |= FNIC_DEV_RST_DONE;
		अगर (io_req && io_req->dr_करोne)
			complete(io_req->dr_करोne);
		अन्यथा अगर (io_req && io_req->abts_करोne)
			complete(io_req->abts_करोne);
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण अन्यथा अगर (CMD_FLAGS(sc) & FNIC_DEVICE_RESET) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		जाओ cleanup_scsi_cmd;
	पूर्ण

	CMD_SP(sc) = शून्य;

	spin_unlock_irqrestore(io_lock, flags);

	/*
	 * If there is a scsi_cmnd associated with this io_req, then
	 * मुक्त the corresponding state
	 */
	start_समय = io_req->start_समय;
	fnic_release_ioreq_buf(fnic, io_req, sc);
	mempool_मुक्त(io_req, fnic->io_req_pool);

cleanup_scsi_cmd:
	sc->result = DID_TRANSPORT_DISRUPTED << 16;
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_cleanup_io: tag:0x%x : sc:0x%p duration = %lu DID_TRANSPORT_DISRUPTED\n",
		      sc->request->tag, sc, (jअगरfies - start_समय));

	अगर (atomic64_पढ़ो(&fnic->io_cmpl_skip))
		atomic64_dec(&fnic->io_cmpl_skip);
	अन्यथा
		atomic64_inc(&fnic_stats->io_stats.io_completions);

	/* Complete the command to SCSI */
	अगर (sc->scsi_करोne) अणु
		अगर (!(CMD_FLAGS(sc) & FNIC_IO_ISSUED))
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "Calling done for IO not issued to fw: tag:0x%x sc:0x%p\n",
				     sc->request->tag, sc);

		FNIC_TRACE(fnic_cleanup_io,
			   sc->device->host->host_no, sc->request->tag, sc,
			   jअगरfies_to_msecs(jअगरfies - start_समय),
			   0, ((u64)sc->cmnd[0] << 32 |
			       (u64)sc->cmnd[2] << 24 |
			       (u64)sc->cmnd[3] << 16 |
			       (u64)sc->cmnd[4] << 8 | sc->cmnd[5]),
			   (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));

		sc->scsi_करोne(sc);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम fnic_cleanup_io(काष्ठा fnic *fnic)
अणु
	scsi_host_busy_iter(fnic->lport->host,
			    fnic_cleanup_io_iter, fnic);
पूर्ण

व्योम fnic_wq_copy_cleanup_handler(काष्ठा vnic_wq_copy *wq,
				  काष्ठा fcpio_host_req *desc)
अणु
	u32 id;
	काष्ठा fnic *fnic = vnic_dev_priv(wq->vdev);
	काष्ठा fnic_io_req *io_req;
	काष्ठा scsi_cmnd *sc;
	अचिन्हित दीर्घ flags;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ start_समय = 0;

	/* get the tag reference */
	fcpio_tag_id_dec(&desc->hdr.tag, &id);
	id &= FNIC_TAG_MASK;

	अगर (id >= fnic->fnic_max_tag_id)
		वापस;

	sc = scsi_host_find_tag(fnic->lport->host, id);
	अगर (!sc)
		वापस;

	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);

	/* Get the IO context which this desc refers to */
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);

	/* fnic पूर्णांकerrupts are turned off by now */

	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		जाओ wq_copy_cleanup_scsi_cmd;
	पूर्ण

	CMD_SP(sc) = शून्य;

	spin_unlock_irqrestore(io_lock, flags);

	start_समय = io_req->start_समय;
	fnic_release_ioreq_buf(fnic, io_req, sc);
	mempool_मुक्त(io_req, fnic->io_req_pool);

wq_copy_cleanup_scsi_cmd:
	sc->result = DID_NO_CONNECT << 16;
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host, "wq_copy_cleanup_handler:"
		      " DID_NO_CONNECT\n");

	अगर (sc->scsi_करोne) अणु
		FNIC_TRACE(fnic_wq_copy_cleanup_handler,
			  sc->device->host->host_no, id, sc,
			  jअगरfies_to_msecs(jअगरfies - start_समय),
			  0, ((u64)sc->cmnd[0] << 32 |
			  (u64)sc->cmnd[2] << 24 | (u64)sc->cmnd[3] << 16 |
			  (u64)sc->cmnd[4] << 8 | sc->cmnd[5]),
			  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));

		sc->scsi_करोne(sc);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक fnic_queue_पात_io_req(काष्ठा fnic *fnic, पूर्णांक tag,
					  u32 task_req, u8 *fc_lun,
					  काष्ठा fnic_io_req *io_req)
अणु
	काष्ठा vnic_wq_copy *wq = &fnic->wq_copy[0];
	काष्ठा Scsi_Host *host = fnic->lport->host;
	काष्ठा misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(host->host_lock, flags);
	अगर (unlikely(fnic_chk_state_flags_locked(fnic,
						FNIC_FLAGS_IO_BLOCKED))) अणु
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस 1;
	पूर्ण अन्यथा
		atomic_inc(&fnic->in_flight);
	spin_unlock_irqrestore(host->host_lock, flags);

	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	अगर (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		मुक्त_wq_copy_descs(fnic, wq);

	अगर (!vnic_wq_copy_desc_avail(wq)) अणु
		spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
		atomic_dec(&fnic->in_flight);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"fnic_queue_abort_io_req: failure: no descriptors\n");
		atomic64_inc(&misc_stats->abts_cpwq_alloc_failures);
		वापस 1;
	पूर्ण
	fnic_queue_wq_copy_desc_iपंचांगf(wq, tag | FNIC_TAG_ABORT,
				     0, task_req, tag, fc_lun, io_req->port_id,
				     fnic->config.ra_tov, fnic->config.ed_tov);

	atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
	अगर (atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.max_fw_reqs))
		atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs));

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
	atomic_dec(&fnic->in_flight);

	वापस 0;
पूर्ण

काष्ठा fnic_rport_पात_io_iter_data अणु
	काष्ठा fnic *fnic;
	u32 port_id;
	पूर्णांक term_cnt;
पूर्ण;

अटल bool fnic_rport_पात_io_iter(काष्ठा scsi_cmnd *sc, व्योम *data,
				     bool reserved)
अणु
	काष्ठा fnic_rport_पात_io_iter_data *iter_data = data;
	काष्ठा fnic *fnic = iter_data->fnic;
	पूर्णांक abt_tag = sc->request->tag;
	काष्ठा fnic_io_req *io_req;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ flags;
	काष्ठा reset_stats *reset_stats = &fnic->fnic_stats.reset_stats;
	काष्ठा terminate_stats *term_stats = &fnic->fnic_stats.term_stats;
	काष्ठा scsi_lun fc_lun;
	क्रमागत fnic_ioreq_state old_ioreq_state;

	io_lock = fnic_io_lock_tag(fnic, abt_tag);
	spin_lock_irqsave(io_lock, flags);

	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);

	अगर (!io_req || io_req->port_id != iter_data->port_id) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण

	अगर ((CMD_FLAGS(sc) & FNIC_DEVICE_RESET) &&
	    (!(CMD_FLAGS(sc) & FNIC_DEV_RST_ISSUED))) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"fnic_rport_exch_reset dev rst not pending sc 0x%p\n",
			sc);
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण

	/*
	 * Found IO that is still pending with firmware and
	 * beदीर्घs to rport that went away
	 */
	अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण
	अगर (io_req->abts_करोne) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			"fnic_rport_exch_reset: io_req->abts_done is set "
			"state is %s\n",
			fnic_ioreq_state_to_str(CMD_STATE(sc)));
	पूर्ण

	अगर (!(CMD_FLAGS(sc) & FNIC_IO_ISSUED)) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "rport_exch_reset "
			     "IO not yet issued %p tag 0x%x flags "
			     "%x state %d\n",
			     sc, abt_tag, CMD_FLAGS(sc), CMD_STATE(sc));
	पूर्ण
	old_ioreq_state = CMD_STATE(sc);
	CMD_STATE(sc) = FNIC_IOREQ_ABTS_PENDING;
	CMD_ABTS_STATUS(sc) = FCPIO_INVALID_CODE;
	अगर (CMD_FLAGS(sc) & FNIC_DEVICE_RESET) अणु
		atomic64_inc(&reset_stats->device_reset_terminates);
		abt_tag |= FNIC_TAG_DEV_RST;
	पूर्ण
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_rport_exch_reset dev rst sc 0x%p\n", sc);
	BUG_ON(io_req->abts_करोne);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_rport_reset_exch: Issuing abts\n");

	spin_unlock_irqrestore(io_lock, flags);

	/* Now queue the पात command to firmware */
	पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);

	अगर (fnic_queue_पात_io_req(fnic, abt_tag,
				    FCPIO_ITMF_ABT_TASK_TERM,
				    fc_lun.scsi_lun, io_req)) अणु
		/*
		 * Revert the cmd state back to old state, अगर
		 * it hasn't changed in between. This cmd will get
		 * पातed later by scsi_eh, or cleaned up during
		 * lun reset
		 */
		spin_lock_irqsave(io_lock, flags);
		अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING)
			CMD_STATE(sc) = old_ioreq_state;
		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(io_lock, flags);
		अगर (CMD_FLAGS(sc) & FNIC_DEVICE_RESET)
			CMD_FLAGS(sc) |= FNIC_DEV_RST_TERM_ISSUED;
		अन्यथा
			CMD_FLAGS(sc) |= FNIC_IO_INTERNAL_TERM_ISSUED;
		spin_unlock_irqrestore(io_lock, flags);
		atomic64_inc(&term_stats->terminates);
		iter_data->term_cnt++;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम fnic_rport_exch_reset(काष्ठा fnic *fnic, u32 port_id)
अणु
	काष्ठा terminate_stats *term_stats = &fnic->fnic_stats.term_stats;
	काष्ठा fnic_rport_पात_io_iter_data iter_data = अणु
		.fnic = fnic,
		.port_id = port_id,
		.term_cnt = 0,
	पूर्ण;

	FNIC_SCSI_DBG(KERN_DEBUG,
		      fnic->lport->host,
		      "fnic_rport_exch_reset called portid 0x%06x\n",
		      port_id);

	अगर (fnic->in_हटाओ)
		वापस;

	scsi_host_busy_iter(fnic->lport->host, fnic_rport_पात_io_iter,
			    &iter_data);
	अगर (iter_data.term_cnt > atomic64_पढ़ो(&term_stats->max_terminates))
		atomic64_set(&term_stats->max_terminates, iter_data.term_cnt);

पूर्ण

व्योम fnic_terminate_rport_io(काष्ठा fc_rport *rport)
अणु
	काष्ठा fc_rport_libfc_priv *rdata;
	काष्ठा fc_lport *lport;
	काष्ठा fnic *fnic;

	अगर (!rport) अणु
		prपूर्णांकk(KERN_ERR "fnic_terminate_rport_io: rport is NULL\n");
		वापस;
	पूर्ण
	rdata = rport->dd_data;

	अगर (!rdata) अणु
		prपूर्णांकk(KERN_ERR "fnic_terminate_rport_io: rdata is NULL\n");
		वापस;
	पूर्ण
	lport = rdata->local_port;

	अगर (!lport) अणु
		prपूर्णांकk(KERN_ERR "fnic_terminate_rport_io: lport is NULL\n");
		वापस;
	पूर्ण
	fnic = lport_priv(lport);
	FNIC_SCSI_DBG(KERN_DEBUG,
		      fnic->lport->host, "fnic_terminate_rport_io called"
		      " wwpn 0x%llx, wwnn0x%llx, rport 0x%p, portid 0x%06x\n",
		      rport->port_name, rport->node_name, rport,
		      rport->port_id);

	अगर (fnic->in_हटाओ)
		वापस;

	fnic_rport_exch_reset(fnic, rport->port_id);
पूर्ण

/*
 * This function is exported to SCSI क्रम sending पात cmnds.
 * A SCSI IO is represented by a io_req in the driver.
 * The ioreq is linked to the SCSI Cmd, thus a link with the ULP's IO.
 */
पूर्णांक fnic_पात_cmd(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा fc_lport *lp;
	काष्ठा fnic *fnic;
	काष्ठा fnic_io_req *io_req = शून्य;
	काष्ठा fc_rport *rport;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ start_समय = 0;
	पूर्णांक ret = SUCCESS;
	u32 task_req = 0;
	काष्ठा scsi_lun fc_lun;
	काष्ठा fnic_stats *fnic_stats;
	काष्ठा पात_stats *abts_stats;
	काष्ठा terminate_stats *term_stats;
	क्रमागत fnic_ioreq_state old_ioreq_state;
	पूर्णांक tag;
	अचिन्हित दीर्घ abt_issued_समय;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);

	/* Wait क्रम rport to unblock */
	fc_block_scsi_eh(sc);

	/* Get local-port, check पढ़ोy and link up */
	lp = shost_priv(sc->device->host);

	fnic = lport_priv(lp);
	fnic_stats = &fnic->fnic_stats;
	abts_stats = &fnic->fnic_stats.abts_stats;
	term_stats = &fnic->fnic_stats.term_stats;

	rport = starget_to_rport(scsi_target(sc->device));
	tag = sc->request->tag;
	FNIC_SCSI_DBG(KERN_DEBUG,
		fnic->lport->host,
		"Abort Cmd called FCID 0x%x, LUN 0x%llx TAG %x flags %x\n",
		rport->port_id, sc->device->lun, tag, CMD_FLAGS(sc));

	CMD_FLAGS(sc) = FNIC_NO_FLAGS;

	अगर (lp->state != LPORT_ST_READY || !(lp->link_up)) अणु
		ret = FAILED;
		जाओ fnic_पात_cmd_end;
	पूर्ण

	/*
	 * Aव्योम a race between SCSI issuing the पात and the device
	 * completing the command.
	 *
	 * If the command is alपढ़ोy completed by the fw cmpl code,
	 * we just वापस SUCCESS from here. This means that the पात
	 * succeeded. In the SCSI ML, since the समयout क्रम command has
	 * happened, the completion wont actually complete the command
	 * and it will be considered as an पातed command
	 *
	 * The CMD_SP will not be cleared except जबतक holding io_req_lock.
	 */
	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		जाओ fnic_पात_cmd_end;
	पूर्ण

	io_req->abts_करोne = &पंचांग_करोne;

	अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING) अणु
		spin_unlock_irqrestore(io_lock, flags);
		जाओ रुको_pending;
	पूर्ण

	abt_issued_समय = jअगरfies_to_msecs(jअगरfies) - jअगरfies_to_msecs(io_req->start_समय);
	अगर (abt_issued_समय <= 6000)
		atomic64_inc(&abts_stats->पात_issued_btw_0_to_6_sec);
	अन्यथा अगर (abt_issued_समय > 6000 && abt_issued_समय <= 20000)
		atomic64_inc(&abts_stats->पात_issued_btw_6_to_20_sec);
	अन्यथा अगर (abt_issued_समय > 20000 && abt_issued_समय <= 30000)
		atomic64_inc(&abts_stats->पात_issued_btw_20_to_30_sec);
	अन्यथा अगर (abt_issued_समय > 30000 && abt_issued_समय <= 40000)
		atomic64_inc(&abts_stats->पात_issued_btw_30_to_40_sec);
	अन्यथा अगर (abt_issued_समय > 40000 && abt_issued_समय <= 50000)
		atomic64_inc(&abts_stats->पात_issued_btw_40_to_50_sec);
	अन्यथा अगर (abt_issued_समय > 50000 && abt_issued_समय <= 60000)
		atomic64_inc(&abts_stats->पात_issued_btw_50_to_60_sec);
	अन्यथा
		atomic64_inc(&abts_stats->पात_issued_greater_than_60_sec);

	FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
		"CBD Opcode: %02x Abort issued time: %lu msec\n", sc->cmnd[0], abt_issued_समय);
	/*
	 * Command is still pending, need to पात it
	 * If the firmware completes the command after this poपूर्णांक,
	 * the completion wont be करोne till mid-layer, since पात
	 * has alपढ़ोy started.
	 */
	old_ioreq_state = CMD_STATE(sc);
	CMD_STATE(sc) = FNIC_IOREQ_ABTS_PENDING;
	CMD_ABTS_STATUS(sc) = FCPIO_INVALID_CODE;

	spin_unlock_irqrestore(io_lock, flags);

	/*
	 * Check पढ़ोiness of the remote port. If the path to remote
	 * port is up, then send abts to the remote port to terminate
	 * the IO. Else, just locally terminate the IO in the firmware
	 */
	अगर (fc_remote_port_chkपढ़ोy(rport) == 0)
		task_req = FCPIO_ITMF_ABT_TASK;
	अन्यथा अणु
		atomic64_inc(&fnic_stats->misc_stats.rport_not_पढ़ोy);
		task_req = FCPIO_ITMF_ABT_TASK_TERM;
	पूर्ण

	/* Now queue the पात command to firmware */
	पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);

	अगर (fnic_queue_पात_io_req(fnic, sc->request->tag, task_req,
				    fc_lun.scsi_lun, io_req)) अणु
		spin_lock_irqsave(io_lock, flags);
		अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING)
			CMD_STATE(sc) = old_ioreq_state;
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		अगर (io_req)
			io_req->abts_करोne = शून्य;
		spin_unlock_irqrestore(io_lock, flags);
		ret = FAILED;
		जाओ fnic_पात_cmd_end;
	पूर्ण
	अगर (task_req == FCPIO_ITMF_ABT_TASK) अणु
		CMD_FLAGS(sc) |= FNIC_IO_ABTS_ISSUED;
		atomic64_inc(&fnic_stats->abts_stats.पातs);
	पूर्ण अन्यथा अणु
		CMD_FLAGS(sc) |= FNIC_IO_TERM_ISSUED;
		atomic64_inc(&fnic_stats->term_stats.terminates);
	पूर्ण

	/*
	 * We queued an पात IO, रुको क्रम its completion.
	 * Once the firmware completes the पात command, it will
	 * wake up this thपढ़ो.
	 */
 रुको_pending:
	रुको_क्रम_completion_समयout(&पंचांग_करोne,
				    msecs_to_jअगरfies
				    (2 * fnic->config.ra_tov +
				     fnic->config.ed_tov));

	/* Check the पात status */
	spin_lock_irqsave(io_lock, flags);

	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		atomic64_inc(&fnic_stats->io_stats.ioreq_null);
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_REQ_शून्य;
		ret = FAILED;
		जाओ fnic_पात_cmd_end;
	पूर्ण
	io_req->abts_करोne = शून्य;

	/* fw did not complete पात, समयd out */
	अगर (CMD_ABTS_STATUS(sc) == FCPIO_INVALID_CODE) अणु
		spin_unlock_irqrestore(io_lock, flags);
		अगर (task_req == FCPIO_ITMF_ABT_TASK) अणु
			atomic64_inc(&abts_stats->पात_drv_समयouts);
		पूर्ण अन्यथा अणु
			atomic64_inc(&term_stats->terminate_drv_समयouts);
		पूर्ण
		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_TIMED_OUT;
		ret = FAILED;
		जाओ fnic_पात_cmd_end;
	पूर्ण

	/* IO out of order */

	अगर (!(CMD_FLAGS(sc) & (FNIC_IO_ABORTED | FNIC_IO_DONE))) अणु
		spin_unlock_irqrestore(io_lock, flags);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"Issuing Host reset due to out of order IO\n");

		ret = FAILED;
		जाओ fnic_पात_cmd_end;
	पूर्ण

	CMD_STATE(sc) = FNIC_IOREQ_ABTS_COMPLETE;

	start_समय = io_req->start_समय;
	/*
	 * firmware completed the पात, check the status,
	 * मुक्त the io_req अगर successful. If पात fails,
	 * Device reset will clean the I/O.
	 */
	अगर (CMD_ABTS_STATUS(sc) == FCPIO_SUCCESS)
		CMD_SP(sc) = शून्य;
	अन्यथा अणु
		ret = FAILED;
		spin_unlock_irqrestore(io_lock, flags);
		जाओ fnic_पात_cmd_end;
	पूर्ण

	spin_unlock_irqrestore(io_lock, flags);

	fnic_release_ioreq_buf(fnic, io_req, sc);
	mempool_मुक्त(io_req, fnic->io_req_pool);

	अगर (sc->scsi_करोne) अणु
	/* Call SCSI completion function to complete the IO */
		sc->result = (DID_ABORT << 16);
		sc->scsi_करोne(sc);
		atomic64_dec(&fnic_stats->io_stats.active_ios);
		अगर (atomic64_पढ़ो(&fnic->io_cmpl_skip))
			atomic64_dec(&fnic->io_cmpl_skip);
		अन्यथा
			atomic64_inc(&fnic_stats->io_stats.io_completions);
	पूर्ण

fnic_पात_cmd_end:
	FNIC_TRACE(fnic_पात_cmd, sc->device->host->host_no,
		  sc->request->tag, sc,
		  jअगरfies_to_msecs(jअगरfies - start_समय),
		  0, ((u64)sc->cmnd[0] << 32 |
		  (u64)sc->cmnd[2] << 24 | (u64)sc->cmnd[3] << 16 |
		  (u64)sc->cmnd[4] << 8 | sc->cmnd[5]),
		  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Returning from abort cmd type %x %s\n", task_req,
		      (ret == SUCCESS) ?
		      "SUCCESS" : "FAILED");
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक fnic_queue_dr_io_req(काष्ठा fnic *fnic,
				       काष्ठा scsi_cmnd *sc,
				       काष्ठा fnic_io_req *io_req)
अणु
	काष्ठा vnic_wq_copy *wq = &fnic->wq_copy[0];
	काष्ठा Scsi_Host *host = fnic->lport->host;
	काष्ठा misc_stats *misc_stats = &fnic->fnic_stats.misc_stats;
	काष्ठा scsi_lun fc_lun;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ पूर्णांकr_flags;

	spin_lock_irqsave(host->host_lock, पूर्णांकr_flags);
	अगर (unlikely(fnic_chk_state_flags_locked(fnic,
						FNIC_FLAGS_IO_BLOCKED))) अणु
		spin_unlock_irqrestore(host->host_lock, पूर्णांकr_flags);
		वापस FAILED;
	पूर्ण अन्यथा
		atomic_inc(&fnic->in_flight);
	spin_unlock_irqrestore(host->host_lock, पूर्णांकr_flags);

	spin_lock_irqsave(&fnic->wq_copy_lock[0], पूर्णांकr_flags);

	अगर (vnic_wq_copy_desc_avail(wq) <= fnic->wq_copy_desc_low[0])
		मुक्त_wq_copy_descs(fnic, wq);

	अगर (!vnic_wq_copy_desc_avail(wq)) अणु
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			  "queue_dr_io_req failure - no descriptors\n");
		atomic64_inc(&misc_stats->devrst_cpwq_alloc_failures);
		ret = -EAGAIN;
		जाओ lr_io_req_end;
	पूर्ण

	/* fill in the lun info */
	पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);

	fnic_queue_wq_copy_desc_iपंचांगf(wq, sc->request->tag | FNIC_TAG_DEV_RST,
				     0, FCPIO_ITMF_LUN_RESET, SCSI_NO_TAG,
				     fc_lun.scsi_lun, io_req->port_id,
				     fnic->config.ra_tov, fnic->config.ed_tov);

	atomic64_inc(&fnic->fnic_stats.fw_stats.active_fw_reqs);
	अगर (atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs) >
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.max_fw_reqs))
		atomic64_set(&fnic->fnic_stats.fw_stats.max_fw_reqs,
		  atomic64_पढ़ो(&fnic->fnic_stats.fw_stats.active_fw_reqs));

lr_io_req_end:
	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], पूर्णांकr_flags);
	atomic_dec(&fnic->in_flight);

	वापस ret;
पूर्ण

काष्ठा fnic_pending_पातs_iter_data अणु
	काष्ठा fnic *fnic;
	काष्ठा scsi_cmnd *lr_sc;
	काष्ठा scsi_device *lun_dev;
	पूर्णांक ret;
पूर्ण;

अटल bool fnic_pending_पातs_iter(काष्ठा scsi_cmnd *sc,
				     व्योम *data, bool reserved)
अणु
	काष्ठा fnic_pending_पातs_iter_data *iter_data = data;
	काष्ठा fnic *fnic = iter_data->fnic;
	काष्ठा scsi_device *lun_dev = iter_data->lun_dev;
	पूर्णांक abt_tag = sc->request->tag;
	काष्ठा fnic_io_req *io_req;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_lun fc_lun;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);
	क्रमागत fnic_ioreq_state old_ioreq_state;

	अगर (sc == iter_data->lr_sc || sc->device != lun_dev)
		वापस true;
	अगर (reserved)
		वापस true;

	io_lock = fnic_io_lock_tag(fnic, abt_tag);
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण

	/*
	 * Found IO that is still pending with firmware and
	 * beदीर्घs to the LUN that we are resetting
	 */
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Found IO in %s on lun\n",
		      fnic_ioreq_state_to_str(CMD_STATE(sc)));

	अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण
	अगर ((CMD_FLAGS(sc) & FNIC_DEVICE_RESET) &&
	    (!(CMD_FLAGS(sc) & FNIC_DEV_RST_ISSUED))) अणु
		FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
			      "%s dev rst not pending sc 0x%p\n", __func__,
			      sc);
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण

	अगर (io_req->abts_करोne)
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "%s: io_req->abts_done is set state is %s\n",
			     __func__, fnic_ioreq_state_to_str(CMD_STATE(sc)));
	old_ioreq_state = CMD_STATE(sc);
	/*
	 * Any pending IO issued prior to reset is expected to be
	 * in abts pending state, अगर not we need to set
	 * FNIC_IOREQ_ABTS_PENDING to indicate the IO is पात pending.
	 * When IO is completed, the IO will be handed over and
	 * handled in this function.
	 */
	CMD_STATE(sc) = FNIC_IOREQ_ABTS_PENDING;

	BUG_ON(io_req->abts_करोne);

	अगर (CMD_FLAGS(sc) & FNIC_DEVICE_RESET) अणु
		abt_tag |= FNIC_TAG_DEV_RST;
		FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
			      "%s: dev rst sc 0x%p\n", __func__, sc);
	पूर्ण

	CMD_ABTS_STATUS(sc) = FCPIO_INVALID_CODE;
	io_req->abts_करोne = &पंचांग_करोne;
	spin_unlock_irqrestore(io_lock, flags);

	/* Now queue the पात command to firmware */
	पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);

	अगर (fnic_queue_पात_io_req(fnic, abt_tag,
				    FCPIO_ITMF_ABT_TASK_TERM,
				    fc_lun.scsi_lun, io_req)) अणु
		spin_lock_irqsave(io_lock, flags);
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		अगर (io_req)
			io_req->abts_करोne = शून्य;
		अगर (CMD_STATE(sc) == FNIC_IOREQ_ABTS_PENDING)
			CMD_STATE(sc) = old_ioreq_state;
		spin_unlock_irqrestore(io_lock, flags);
		iter_data->ret = FAILED;
		वापस false;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(io_lock, flags);
		अगर (CMD_FLAGS(sc) & FNIC_DEVICE_RESET)
			CMD_FLAGS(sc) |= FNIC_DEV_RST_TERM_ISSUED;
		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण
	CMD_FLAGS(sc) |= FNIC_IO_INTERNAL_TERM_ISSUED;

	रुको_क्रम_completion_समयout(&पंचांग_करोne, msecs_to_jअगरfies
				    (fnic->config.ed_tov));

	/* Recheck cmd state to check अगर it is now पातed */
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_REQ_शून्य;
		वापस true;
	पूर्ण

	io_req->abts_करोne = शून्य;

	/* अगर पात is still pending with fw, fail */
	अगर (CMD_ABTS_STATUS(sc) == FCPIO_INVALID_CODE) अणु
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= FNIC_IO_ABT_TERM_DONE;
		iter_data->ret = FAILED;
		वापस false;
	पूर्ण
	CMD_STATE(sc) = FNIC_IOREQ_ABTS_COMPLETE;

	/* original sc used क्रम lr is handled by dev reset code */
	अगर (sc != iter_data->lr_sc)
		CMD_SP(sc) = शून्य;
	spin_unlock_irqrestore(io_lock, flags);

	/* original sc used क्रम lr is handled by dev reset code */
	अगर (sc != iter_data->lr_sc) अणु
		fnic_release_ioreq_buf(fnic, io_req, sc);
		mempool_मुक्त(io_req, fnic->io_req_pool);
	पूर्ण

	/*
	 * Any IO is वापसed during reset, it needs to call scsi_करोne
	 * to वापस the scsi_cmnd to upper layer.
	 */
	अगर (sc->scsi_करोne) अणु
		/* Set result to let upper SCSI layer retry */
		sc->result = DID_RESET << 16;
		sc->scsi_करोne(sc);
	पूर्ण
	वापस true;
पूर्ण

/*
 * Clean up any pending पातs on the lun
 * For each outstanding IO on this lun, whose पात is not completed by fw,
 * issue a local पात. Wait क्रम पात to complete. Return 0 अगर all commands
 * successfully पातed, 1 otherwise
 */
अटल पूर्णांक fnic_clean_pending_पातs(काष्ठा fnic *fnic,
				     काष्ठा scsi_cmnd *lr_sc,
				     bool new_sc)

अणु
	पूर्णांक ret = SUCCESS;
	काष्ठा fnic_pending_पातs_iter_data iter_data = अणु
		.fnic = fnic,
		.lun_dev = lr_sc->device,
		.ret = SUCCESS,
	पूर्ण;

	अगर (new_sc)
		iter_data.lr_sc = lr_sc;

	scsi_host_busy_iter(fnic->lport->host,
			    fnic_pending_पातs_iter, &iter_data);
	अगर (iter_data.ret == FAILED) अणु
		ret = iter_data.ret;
		जाओ clean_pending_पातs_end;
	पूर्ण
	schedule_समयout(msecs_to_jअगरfies(2 * fnic->config.ed_tov));

	/* walk again to check, अगर IOs are still pending in fw */
	अगर (fnic_is_abts_pending(fnic, lr_sc))
		ret = FAILED;

clean_pending_पातs_end:
	वापस ret;
पूर्ण

/*
 * fnic_scsi_host_start_tag
 * Allocates tagid from host's tag list
 **/
अटल अंतरभूत पूर्णांक
fnic_scsi_host_start_tag(काष्ठा fnic *fnic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा request_queue *q = sc->request->q;
	काष्ठा request *dummy;

	dummy = blk_mq_alloc_request(q, REQ_OP_WRITE, BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(dummy))
		वापस SCSI_NO_TAG;

	sc->tag = sc->request->tag = dummy->tag;
	sc->host_scribble = (अचिन्हित अक्षर *)dummy;

	वापस dummy->tag;
पूर्ण

/*
 * fnic_scsi_host_end_tag
 * मुक्तs tag allocated by fnic_scsi_host_start_tag.
 **/
अटल अंतरभूत व्योम
fnic_scsi_host_end_tag(काष्ठा fnic *fnic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा request *dummy = (काष्ठा request *)sc->host_scribble;

	blk_mq_मुक्त_request(dummy);
पूर्ण

/*
 * SCSI Eh thपढ़ो issues a Lun Reset when one or more commands on a LUN
 * fail to get पातed. It calls driver's eh_device_reset with a SCSI command
 * on the LUN.
 */
पूर्णांक fnic_device_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा fc_lport *lp;
	काष्ठा fnic *fnic;
	काष्ठा fnic_io_req *io_req = शून्य;
	काष्ठा fc_rport *rport;
	पूर्णांक status;
	पूर्णांक ret = FAILED;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ start_समय = 0;
	काष्ठा scsi_lun fc_lun;
	काष्ठा fnic_stats *fnic_stats;
	काष्ठा reset_stats *reset_stats;
	पूर्णांक tag = 0;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);
	पूर्णांक tag_gen_flag = 0;   /*to track tags allocated by fnic driver*/
	bool new_sc = 0;

	/* Wait क्रम rport to unblock */
	fc_block_scsi_eh(sc);

	/* Get local-port, check पढ़ोy and link up */
	lp = shost_priv(sc->device->host);

	fnic = lport_priv(lp);
	fnic_stats = &fnic->fnic_stats;
	reset_stats = &fnic->fnic_stats.reset_stats;

	atomic64_inc(&reset_stats->device_resets);

	rport = starget_to_rport(scsi_target(sc->device));
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Device reset called FCID 0x%x, LUN 0x%llx sc 0x%p\n",
		      rport->port_id, sc->device->lun, sc);

	अगर (lp->state != LPORT_ST_READY || !(lp->link_up))
		जाओ fnic_device_reset_end;

	/* Check अगर remote port up */
	अगर (fc_remote_port_chkपढ़ोy(rport)) अणु
		atomic64_inc(&fnic_stats->misc_stats.rport_not_पढ़ोy);
		जाओ fnic_device_reset_end;
	पूर्ण

	CMD_FLAGS(sc) = FNIC_DEVICE_RESET;
	/* Allocate tag अगर not present */

	tag = sc->request->tag;
	अगर (unlikely(tag < 0)) अणु
		/*
		 * Really should fix the midlayer to pass in a proper
		 * request क्रम ioctls...
		 */
		tag = fnic_scsi_host_start_tag(fnic, sc);
		अगर (unlikely(tag == SCSI_NO_TAG))
			जाओ fnic_device_reset_end;
		tag_gen_flag = 1;
		new_sc = 1;
	पूर्ण
	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);

	/*
	 * If there is a io_req attached to this command, then use it,
	 * अन्यथा allocate a new one.
	 */
	अगर (!io_req) अणु
		io_req = mempool_alloc(fnic->io_req_pool, GFP_ATOMIC);
		अगर (!io_req) अणु
			spin_unlock_irqrestore(io_lock, flags);
			जाओ fnic_device_reset_end;
		पूर्ण
		स_रखो(io_req, 0, माप(*io_req));
		io_req->port_id = rport->port_id;
		CMD_SP(sc) = (अक्षर *)io_req;
	पूर्ण
	io_req->dr_करोne = &पंचांग_करोne;
	CMD_STATE(sc) = FNIC_IOREQ_CMD_PENDING;
	CMD_LR_STATUS(sc) = FCPIO_INVALID_CODE;
	spin_unlock_irqrestore(io_lock, flags);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host, "TAG %x\n", tag);

	/*
	 * issue the device reset, अगर enqueue failed, clean up the ioreq
	 * and अवरोध assoc with scsi cmd
	 */
	अगर (fnic_queue_dr_io_req(fnic, sc, io_req)) अणु
		spin_lock_irqsave(io_lock, flags);
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		अगर (io_req)
			io_req->dr_करोne = शून्य;
		जाओ fnic_device_reset_clean;
	पूर्ण
	spin_lock_irqsave(io_lock, flags);
	CMD_FLAGS(sc) |= FNIC_DEV_RST_ISSUED;
	spin_unlock_irqrestore(io_lock, flags);

	/*
	 * Wait on the local completion क्रम LUN reset.  The io_req may be
	 * मुक्तd जबतक we रुको since we hold no lock.
	 */
	रुको_क्रम_completion_समयout(&पंचांग_करोne,
				    msecs_to_jअगरfies(FNIC_LUN_RESET_TIMEOUT));

	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"io_req is null tag 0x%x sc 0x%p\n", tag, sc);
		जाओ fnic_device_reset_end;
	पूर्ण
	io_req->dr_करोne = शून्य;

	status = CMD_LR_STATUS(sc);

	/*
	 * If lun reset not completed, bail out with failed. io_req
	 * माला_लो cleaned up during higher levels of EH
	 */
	अगर (status == FCPIO_INVALID_CODE) अणु
		atomic64_inc(&reset_stats->device_reset_समयouts);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Device reset timed out\n");
		CMD_FLAGS(sc) |= FNIC_DEV_RST_TIMED_OUT;
		spin_unlock_irqrestore(io_lock, flags);
		पूर्णांक_to_scsilun(sc->device->lun, &fc_lun);
		/*
		 * Issue पात and terminate on device reset request.
		 * If q'ing of terminate fails, retry it after a delay.
		 */
		जबतक (1) अणु
			spin_lock_irqsave(io_lock, flags);
			अगर (CMD_FLAGS(sc) & FNIC_DEV_RST_TERM_ISSUED) अणु
				spin_unlock_irqrestore(io_lock, flags);
				अवरोध;
			पूर्ण
			spin_unlock_irqrestore(io_lock, flags);
			अगर (fnic_queue_पात_io_req(fnic,
				tag | FNIC_TAG_DEV_RST,
				FCPIO_ITMF_ABT_TASK_TERM,
				fc_lun.scsi_lun, io_req)) अणु
				रुको_क्रम_completion_समयout(&पंचांग_करोne,
				msecs_to_jअगरfies(FNIC_ABT_TERM_DELAY_TIMEOUT));
			पूर्ण अन्यथा अणु
				spin_lock_irqsave(io_lock, flags);
				CMD_FLAGS(sc) |= FNIC_DEV_RST_TERM_ISSUED;
				CMD_STATE(sc) = FNIC_IOREQ_ABTS_PENDING;
				io_req->abts_करोne = &पंचांग_करोne;
				spin_unlock_irqrestore(io_lock, flags);
				FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				"Abort and terminate issued on Device reset "
				"tag 0x%x sc 0x%p\n", tag, sc);
				अवरोध;
			पूर्ण
		पूर्ण
		जबतक (1) अणु
			spin_lock_irqsave(io_lock, flags);
			अगर (!(CMD_FLAGS(sc) & FNIC_DEV_RST_DONE)) अणु
				spin_unlock_irqrestore(io_lock, flags);
				रुको_क्रम_completion_समयout(&पंचांग_करोne,
				msecs_to_jअगरfies(FNIC_LUN_RESET_TIMEOUT));
				अवरोध;
			पूर्ण अन्यथा अणु
				io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
				io_req->abts_करोne = शून्य;
				जाओ fnic_device_reset_clean;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण

	/* Completed, but not successful, clean up the io_req, वापस fail */
	अगर (status != FCPIO_SUCCESS) अणु
		spin_lock_irqsave(io_lock, flags);
		FNIC_SCSI_DBG(KERN_DEBUG,
			      fnic->lport->host,
			      "Device reset completed - failed\n");
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		जाओ fnic_device_reset_clean;
	पूर्ण

	/*
	 * Clean up any पातs on this lun that have still not
	 * completed. If any of these fail, then LUN reset fails.
	 * clean_pending_पातs cleans all cmds on this lun except
	 * the lun reset cmd. If all cmds get cleaned, the lun reset
	 * succeeds
	 */
	अगर (fnic_clean_pending_पातs(fnic, sc, new_sc)) अणु
		spin_lock_irqsave(io_lock, flags);
		io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Device reset failed"
			      " since could not abort all IOs\n");
		जाओ fnic_device_reset_clean;
	पूर्ण

	/* Clean lun reset command */
	spin_lock_irqsave(io_lock, flags);
	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (io_req)
		/* Completed, and successful */
		ret = SUCCESS;

fnic_device_reset_clean:
	अगर (io_req)
		CMD_SP(sc) = शून्य;

	spin_unlock_irqrestore(io_lock, flags);

	अगर (io_req) अणु
		start_समय = io_req->start_समय;
		fnic_release_ioreq_buf(fnic, io_req, sc);
		mempool_मुक्त(io_req, fnic->io_req_pool);
	पूर्ण

fnic_device_reset_end:
	FNIC_TRACE(fnic_device_reset, sc->device->host->host_no,
		  sc->request->tag, sc,
		  jअगरfies_to_msecs(jअगरfies - start_समय),
		  0, ((u64)sc->cmnd[0] << 32 |
		  (u64)sc->cmnd[2] << 24 | (u64)sc->cmnd[3] << 16 |
		  (u64)sc->cmnd[4] << 8 | sc->cmnd[5]),
		  (((u64)CMD_FLAGS(sc) << 32) | CMD_STATE(sc)));

	/* मुक्त tag अगर it is allocated */
	अगर (unlikely(tag_gen_flag))
		fnic_scsi_host_end_tag(fnic, sc);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Returning from device reset %s\n",
		      (ret == SUCCESS) ?
		      "SUCCESS" : "FAILED");

	अगर (ret == FAILED)
		atomic64_inc(&reset_stats->device_reset_failures);

	वापस ret;
पूर्ण

/* Clean up all IOs, clean up libFC local port */
पूर्णांक fnic_reset(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lp;
	काष्ठा fnic *fnic;
	पूर्णांक ret = 0;
	काष्ठा reset_stats *reset_stats;

	lp = shost_priv(shost);
	fnic = lport_priv(lp);
	reset_stats = &fnic->fnic_stats.reset_stats;

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_reset called\n");

	atomic64_inc(&reset_stats->fnic_resets);

	/*
	 * Reset local port, this will clean up libFC exchanges,
	 * reset remote port sessions, and अगर link is up, begin flogi
	 */
	ret = fc_lport_reset(lp);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Returning from fnic reset %s\n",
		      (ret == 0) ?
		      "SUCCESS" : "FAILED");

	अगर (ret == 0)
		atomic64_inc(&reset_stats->fnic_reset_completions);
	अन्यथा
		atomic64_inc(&reset_stats->fnic_reset_failures);

	वापस ret;
पूर्ण

/*
 * SCSI Error handling calls driver's eh_host_reset अगर all prior
 * error handling levels वापस FAILED. If host reset completes
 * successfully, and अगर link is up, then Fabric login begins.
 *
 * Host Reset is the highest level of error recovery. If this fails, then
 * host is offlined by SCSI.
 *
 */
पूर्णांक fnic_host_reset(काष्ठा scsi_cmnd *sc)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ रुको_host_पंचांगo;
	काष्ठा Scsi_Host *shost = sc->device->host;
	काष्ठा fc_lport *lp = shost_priv(shost);
	काष्ठा fnic *fnic = lport_priv(lp);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (!fnic->पूर्णांकernal_reset_inprogress) अणु
		fnic->पूर्णांकernal_reset_inprogress = true;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			"host reset in progress skipping another host reset\n");
		वापस SUCCESS;
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	/*
	 * If fnic_reset is successful, रुको क्रम fabric login to complete
	 * scsi-ml tries to send a TUR to every device अगर host reset is
	 * successful, so beक्रमe वापसing to scsi, fabric should be up
	 */
	ret = (fnic_reset(shost) == 0) ? SUCCESS : FAILED;
	अगर (ret == SUCCESS) अणु
		रुको_host_पंचांगo = jअगरfies + FNIC_HOST_RESET_SETTLE_TIME * HZ;
		ret = FAILED;
		जबतक (समय_beक्रमe(jअगरfies, रुको_host_पंचांगo)) अणु
			अगर ((lp->state == LPORT_ST_READY) &&
			    (lp->link_up)) अणु
				ret = SUCCESS;
				अवरोध;
			पूर्ण
			ssleep(1);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->पूर्णांकernal_reset_inprogress = false;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	वापस ret;
पूर्ण

/*
 * This fxn is called from libFC when host is हटाओd
 */
व्योम fnic_scsi_पात_io(काष्ठा fc_lport *lp)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	क्रमागत fnic_state old_state;
	काष्ठा fnic *fnic = lport_priv(lp);
	DECLARE_COMPLETION_ONSTACK(हटाओ_रुको);

	/* Issue firmware reset क्रम fnic, रुको क्रम reset to complete */
retry_fw_reset:
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (unlikely(fnic->state == FNIC_IN_FC_TRANS_ETH_MODE) &&
		     fnic->link_events) अणु
		/* fw reset is in progress, poll क्रम its completion */
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		schedule_समयout(msecs_to_jअगरfies(100));
		जाओ retry_fw_reset;
	पूर्ण

	fnic->हटाओ_रुको = &हटाओ_रुको;
	old_state = fnic->state;
	fnic->state = FNIC_IN_FC_TRANS_ETH_MODE;
	fnic_update_mac_locked(fnic, fnic->ctlr.ctl_src_addr);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	err = fnic_fw_reset_handler(fnic);
	अगर (err) अणु
		spin_lock_irqsave(&fnic->fnic_lock, flags);
		अगर (fnic->state == FNIC_IN_FC_TRANS_ETH_MODE)
			fnic->state = old_state;
		fnic->हटाओ_रुको = शून्य;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण

	/* Wait क्रम firmware reset to complete */
	रुको_क्रम_completion_समयout(&हटाओ_रुको,
				    msecs_to_jअगरfies(FNIC_RMDEVICE_TIMEOUT));

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->हटाओ_रुको = शून्य;
	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_scsi_abort_io %s\n",
		      (fnic->state == FNIC_IN_ETH_MODE) ?
		      "SUCCESS" : "FAILED");
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

पूर्ण

/*
 * This fxn called from libFC to clean up driver IO state on link करोwn
 */
व्योम fnic_scsi_cleanup(काष्ठा fc_lport *lp)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत fnic_state old_state;
	काष्ठा fnic *fnic = lport_priv(lp);

	/* issue fw reset */
retry_fw_reset:
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (unlikely(fnic->state == FNIC_IN_FC_TRANS_ETH_MODE)) अणु
		/* fw reset is in progress, poll क्रम its completion */
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		schedule_समयout(msecs_to_jअगरfies(100));
		जाओ retry_fw_reset;
	पूर्ण
	old_state = fnic->state;
	fnic->state = FNIC_IN_FC_TRANS_ETH_MODE;
	fnic_update_mac_locked(fnic, fnic->ctlr.ctl_src_addr);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	अगर (fnic_fw_reset_handler(fnic)) अणु
		spin_lock_irqsave(&fnic->fnic_lock, flags);
		अगर (fnic->state == FNIC_IN_FC_TRANS_ETH_MODE)
			fnic->state = old_state;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	पूर्ण

पूर्ण

व्योम fnic_empty_scsi_cleanup(काष्ठा fc_lport *lp)
अणु
पूर्ण

व्योम fnic_exch_mgr_reset(काष्ठा fc_lport *lp, u32 sid, u32 did)
अणु
	काष्ठा fnic *fnic = lport_priv(lp);

	/* Non-zero sid, nothing to करो */
	अगर (sid)
		जाओ call_fc_exch_mgr_reset;

	अगर (did) अणु
		fnic_rport_exch_reset(fnic, did);
		जाओ call_fc_exch_mgr_reset;
	पूर्ण

	/*
	 * sid = 0, did = 0
	 * link करोwn or device being हटाओd
	 */
	अगर (!fnic->in_हटाओ)
		fnic_scsi_cleanup(lp);
	अन्यथा
		fnic_scsi_पात_io(lp);

	/* call libFC exch mgr reset to reset its exchanges */
call_fc_exch_mgr_reset:
	fc_exch_mgr_reset(lp, sid, did);

पूर्ण

अटल bool fnic_abts_pending_iter(काष्ठा scsi_cmnd *sc, व्योम *data,
				   bool reserved)
अणु
	काष्ठा fnic_pending_पातs_iter_data *iter_data = data;
	काष्ठा fnic *fnic = iter_data->fnic;
	पूर्णांक cmd_state;
	काष्ठा fnic_io_req *io_req;
	spinlock_t *io_lock;
	अचिन्हित दीर्घ flags;

	/*
	 * ignore this lun reset cmd or cmds that करो not beदीर्घ to
	 * this lun
	 */
	अगर (iter_data->lr_sc && sc == iter_data->lr_sc)
		वापस true;
	अगर (iter_data->lun_dev && sc->device != iter_data->lun_dev)
		वापस true;

	io_lock = fnic_io_lock_hash(fnic, sc);
	spin_lock_irqsave(io_lock, flags);

	io_req = (काष्ठा fnic_io_req *)CMD_SP(sc);
	अगर (!io_req) अणु
		spin_unlock_irqrestore(io_lock, flags);
		वापस true;
	पूर्ण

	/*
	 * Found IO that is still pending with firmware and
	 * beदीर्घs to the LUN that we are resetting
	 */
	FNIC_SCSI_DBG(KERN_INFO, fnic->lport->host,
		      "Found IO in %s on lun\n",
		      fnic_ioreq_state_to_str(CMD_STATE(sc)));
	cmd_state = CMD_STATE(sc);
	spin_unlock_irqrestore(io_lock, flags);
	अगर (cmd_state == FNIC_IOREQ_ABTS_PENDING)
		iter_data->ret = 1;

	वापस iter_data->ret ? false : true;
पूर्ण

/*
 * fnic_is_abts_pending() is a helper function that
 * walks through tag map to check अगर there is any IOs pending,अगर there is one,
 * then it वापसs 1 (true), otherwise 0 (false)
 * अगर @lr_sc is non शून्य, then it checks IOs specअगरic to particular LUN,
 * otherwise, it checks क्रम all IOs.
 */
पूर्णांक fnic_is_abts_pending(काष्ठा fnic *fnic, काष्ठा scsi_cmnd *lr_sc)
अणु
	काष्ठा fnic_pending_पातs_iter_data iter_data = अणु
		.fnic = fnic,
		.lun_dev = शून्य,
		.ret = 0,
	पूर्ण;

	अगर (lr_sc) अणु
		iter_data.lun_dev = lr_sc->device;
		iter_data.lr_sc = lr_sc;
	पूर्ण

	/* walk again to check, अगर IOs are still pending in fw */
	scsi_host_busy_iter(fnic->lport->host,
			    fnic_abts_pending_iter, &iter_data);

	वापस iter_data.ret;
पूर्ण
