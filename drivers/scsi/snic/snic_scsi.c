<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "snic_io.h"
#समावेश "snic.h"

#घोषणा snic_cmd_tag(sc)	(((काष्ठा scsi_cmnd *) sc)->request->tag)

स्थिर अक्षर *snic_state_str[] = अणु
	[SNIC_INIT]	= "SNIC_INIT",
	[SNIC_ERROR]	= "SNIC_ERROR",
	[SNIC_ONLINE]	= "SNIC_ONLINE",
	[SNIC_OFFLINE]	= "SNIC_OFFLINE",
	[SNIC_FWRESET]	= "SNIC_FWRESET",
पूर्ण;

अटल स्थिर अक्षर * स्थिर snic_req_state_str[] = अणु
	[SNIC_IOREQ_NOT_INITED]	= "SNIC_IOREQ_NOT_INITED",
	[SNIC_IOREQ_PENDING]	= "SNIC_IOREQ_PENDING",
	[SNIC_IOREQ_ABTS_PENDING] = "SNIC_IOREQ_ABTS_PENDING",
	[SNIC_IOREQ_ABTS_COMPLETE] = "SNIC_IOREQ_ABTS_COMPLETE",
	[SNIC_IOREQ_LR_PENDING]	= "SNIC_IOREQ_LR_PENDING",
	[SNIC_IOREQ_LR_COMPLETE] = "SNIC_IOREQ_LR_COMPLETE",
	[SNIC_IOREQ_COMPLETE]	= "SNIC_IOREQ_CMD_COMPLETE",
पूर्ण;

/* snic cmd status strings */
अटल स्थिर अक्षर * स्थिर snic_io_status_str[] = अणु
	[SNIC_STAT_IO_SUCCESS]	= "SNIC_STAT_IO_SUCCESS", /* 0x0 */
	[SNIC_STAT_INVALID_HDR] = "SNIC_STAT_INVALID_HDR",
	[SNIC_STAT_OUT_OF_RES]	= "SNIC_STAT_OUT_OF_RES",
	[SNIC_STAT_INVALID_PARM] = "SNIC_STAT_INVALID_PARM",
	[SNIC_STAT_REQ_NOT_SUP]	= "SNIC_STAT_REQ_NOT_SUP",
	[SNIC_STAT_IO_NOT_FOUND] = "SNIC_STAT_IO_NOT_FOUND",
	[SNIC_STAT_ABORTED]	= "SNIC_STAT_ABORTED",
	[SNIC_STAT_TIMEOUT]	= "SNIC_STAT_TIMEOUT",
	[SNIC_STAT_SGL_INVALID] = "SNIC_STAT_SGL_INVALID",
	[SNIC_STAT_DATA_CNT_MISMATCH] = "SNIC_STAT_DATA_CNT_MISMATCH",
	[SNIC_STAT_FW_ERR]	= "SNIC_STAT_FW_ERR",
	[SNIC_STAT_ITMF_REJECT] = "SNIC_STAT_ITMF_REJECT",
	[SNIC_STAT_ITMF_FAIL]	= "SNIC_STAT_ITMF_FAIL",
	[SNIC_STAT_ITMF_INCORRECT_LUN] = "SNIC_STAT_ITMF_INCORRECT_LUN",
	[SNIC_STAT_CMND_REJECT] = "SNIC_STAT_CMND_REJECT",
	[SNIC_STAT_DEV_OFFLINE] = "SNIC_STAT_DEV_OFFLINE",
	[SNIC_STAT_NO_BOOTLUN]	= "SNIC_STAT_NO_BOOTLUN",
	[SNIC_STAT_SCSI_ERR]	= "SNIC_STAT_SCSI_ERR",
	[SNIC_STAT_NOT_READY]	= "SNIC_STAT_NOT_READY",
	[SNIC_STAT_FATAL_ERROR]	= "SNIC_STAT_FATAL_ERROR",
पूर्ण;

अटल व्योम snic_scsi_cleanup(काष्ठा snic *, पूर्णांक);

स्थिर अक्षर *
snic_state_to_str(अचिन्हित पूर्णांक state)
अणु
	अगर (state >= ARRAY_SIZE(snic_state_str) || !snic_state_str[state])
		वापस "Unknown";

	वापस snic_state_str[state];
पूर्ण

अटल स्थिर अक्षर *
snic_io_status_to_str(अचिन्हित पूर्णांक state)
अणु
	अगर ((state >= ARRAY_SIZE(snic_io_status_str)) ||
	     (!snic_io_status_str[state]))
		वापस "Unknown";

	वापस snic_io_status_str[state];
पूर्ण

अटल स्थिर अक्षर *
snic_ioreq_state_to_str(अचिन्हित पूर्णांक state)
अणु
	अगर (state >= ARRAY_SIZE(snic_req_state_str) ||
			!snic_req_state_str[state])
		वापस "Unknown";

	वापस snic_req_state_str[state];
पूर्ण

अटल अंतरभूत spinlock_t *
snic_io_lock_hash(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	u32 hash = snic_cmd_tag(sc) & (SNIC_IO_LOCKS - 1);

	वापस &snic->io_req_lock[hash];
पूर्ण

अटल अंतरभूत spinlock_t *
snic_io_lock_tag(काष्ठा snic *snic, पूर्णांक tag)
अणु
	वापस &snic->io_req_lock[tag & (SNIC_IO_LOCKS - 1)];
पूर्ण

/* snic_release_req_buf : Releases snic_req_info */
अटल व्योम
snic_release_req_buf(काष्ठा snic *snic,
		   काष्ठा snic_req_info *rqi,
		   काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_host_req *req = rqi_to_req(rqi);

	/* Freeing cmd without marking completion, not okay */
	SNIC_BUG_ON(!((CMD_STATE(sc) == SNIC_IOREQ_COMPLETE) ||
		      (CMD_STATE(sc) == SNIC_IOREQ_ABTS_COMPLETE) ||
		      (CMD_FLAGS(sc) & SNIC_DEV_RST_NOTSUP) ||
		      (CMD_FLAGS(sc) & SNIC_IO_INTERNAL_TERM_ISSUED) ||
		      (CMD_FLAGS(sc) & SNIC_DEV_RST_TERM_ISSUED) ||
		      (CMD_FLAGS(sc) & SNIC_SCSI_CLEANUP) ||
		      (CMD_STATE(sc) == SNIC_IOREQ_LR_COMPLETE)));

	SNIC_SCSI_DBG(snic->shost,
		      "Rel_req:sc %p:tag %x:rqi %p:ioreq %p:abt %p:dr %p: state %s:flags 0x%llx\n",
		      sc, snic_cmd_tag(sc), rqi, rqi->req, rqi->पात_req,
		      rqi->dr_req, snic_ioreq_state_to_str(CMD_STATE(sc)),
		      CMD_FLAGS(sc));

	अगर (req->u.icmnd.sense_addr)
		dma_unmap_single(&snic->pdev->dev,
				 le64_to_cpu(req->u.icmnd.sense_addr),
				 SCSI_SENSE_BUFFERSIZE,
				 DMA_FROM_DEVICE);

	scsi_dma_unmap(sc);

	snic_req_मुक्त(snic, rqi);
पूर्ण /* end of snic_release_req_buf */

/*
 * snic_queue_icmnd_req : Queues snic_icmnd request
 */
अटल पूर्णांक
snic_queue_icmnd_req(काष्ठा snic *snic,
		     काष्ठा snic_req_info *rqi,
		     काष्ठा scsi_cmnd *sc,
		     पूर्णांक sg_cnt)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा snic_sg_desc *sgd;
	dma_addr_t pa = 0;
	काष्ठा scsi_lun lun;
	u16 flags = 0;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;

	अगर (sg_cnt) अणु
		flags = SNIC_ICMND_ESGL;
		sgd = (काष्ठा snic_sg_desc *) req_to_sgl(rqi->req);

		क्रम_each_sg(scsi_sglist(sc), sg, sg_cnt, i) अणु
			sgd->addr = cpu_to_le64(sg_dma_address(sg));
			sgd->len = cpu_to_le32(sg_dma_len(sg));
			sgd->_resvd = 0;
			sgd++;
		पूर्ण
	पूर्ण

	pa = dma_map_single(&snic->pdev->dev,
			    sc->sense_buffer,
			    SCSI_SENSE_BUFFERSIZE,
			    DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&snic->pdev->dev, pa)) अणु
		SNIC_HOST_ERR(snic->shost,
			      "QIcmnd:PCI Map Failed for sns buf %p tag %x\n",
			      sc->sense_buffer, snic_cmd_tag(sc));
		ret = -ENOMEM;

		वापस ret;
	पूर्ण

	पूर्णांक_to_scsilun(sc->device->lun, &lun);
	अगर (sc->sc_data_direction == DMA_FROM_DEVICE)
		flags |= SNIC_ICMND_RD;
	अगर (sc->sc_data_direction == DMA_TO_DEVICE)
		flags |= SNIC_ICMND_WR;

	/* Initialize icmnd */
	snic_icmnd_init(rqi->req,
			snic_cmd_tag(sc),
			snic->config.hid, /* hid */
			(uदीर्घ) rqi,
			flags, /* command flags */
			rqi->tgt_id,
			lun.scsi_lun,
			sc->cmnd,
			sc->cmd_len,
			scsi_bufflen(sc),
			sg_cnt,
			(uदीर्घ) req_to_sgl(rqi->req),
			pa, /* sense buffer pa */
			SCSI_SENSE_BUFFERSIZE);

	atomic64_inc(&snic->s_stats.io.active);
	ret = snic_queue_wq_desc(snic, rqi->req, rqi->req_len);
	अगर (ret) अणु
		atomic64_dec(&snic->s_stats.io.active);
		SNIC_HOST_ERR(snic->shost,
			      "QIcmnd: Queuing Icmnd Failed. ret = %d\n",
			      ret);
	पूर्ण अन्यथा
		snic_stats_update_active_ios(&snic->s_stats);

	वापस ret;
पूर्ण /* end of snic_queue_icmnd_req */

/*
 * snic_issue_scsi_req : Prepares IO request and Issues to FW.
 */
अटल पूर्णांक
snic_issue_scsi_req(काष्ठा snic *snic,
		      काष्ठा snic_tgt *tgt,
		      काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	पूर्णांक sg_cnt = 0;
	पूर्णांक ret = 0;
	u32 tag = snic_cmd_tag(sc);
	u64 cmd_trc = 0, cmd_st_flags = 0;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;

	CMD_STATE(sc) = SNIC_IOREQ_NOT_INITED;
	CMD_FLAGS(sc) = SNIC_NO_FLAGS;
	sg_cnt = scsi_dma_map(sc);
	अगर (sg_cnt < 0) अणु
		SNIC_TRC((u16)snic->shost->host_no, tag, (uदीर्घ) sc, 0,
			 sc->cmnd[0], sg_cnt, CMD_STATE(sc));

		SNIC_HOST_ERR(snic->shost, "issue_sc:Failed to map SG List.\n");
		ret = -ENOMEM;

		जाओ issue_sc_end;
	पूर्ण

	rqi = snic_req_init(snic, sg_cnt);
	अगर (!rqi) अणु
		scsi_dma_unmap(sc);
		ret = -ENOMEM;

		जाओ issue_sc_end;
	पूर्ण

	rqi->tgt_id = tgt->id;
	rqi->sc = sc;

	CMD_STATE(sc) = SNIC_IOREQ_PENDING;
	CMD_SP(sc) = (अक्षर *) rqi;
	cmd_trc = SNIC_TRC_CMD(sc);
	CMD_FLAGS(sc) |= (SNIC_IO_INITIALIZED | SNIC_IO_ISSUED);
	cmd_st_flags = SNIC_TRC_CMD_STATE_FLAGS(sc);
	io_lock = snic_io_lock_hash(snic, sc);

	/* create wq desc and enqueue it */
	ret = snic_queue_icmnd_req(snic, rqi, sc, sg_cnt);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "issue_sc: icmnd qing Failed for sc %p, err %d\n",
			      sc, ret);

		spin_lock_irqsave(io_lock, flags);
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		CMD_SP(sc) = शून्य;
		CMD_STATE(sc) = SNIC_IOREQ_COMPLETE;
		CMD_FLAGS(sc) &= ~SNIC_IO_ISSUED; /* turn off the flag */
		spin_unlock_irqrestore(io_lock, flags);

		अगर (rqi)
			snic_release_req_buf(snic, rqi, sc);

		SNIC_TRC(snic->shost->host_no, tag, (uदीर्घ) sc, 0, 0, 0,
			 SNIC_TRC_CMD_STATE_FLAGS(sc));
	पूर्ण अन्यथा अणु
		u32 io_sz = scsi_bufflen(sc) >> 9;
		u32 qसमय = jअगरfies - rqi->start_समय;
		काष्ठा snic_io_stats *iostats = &snic->s_stats.io;

		अगर (io_sz > atomic64_पढ़ो(&iostats->max_io_sz))
			atomic64_set(&iostats->max_io_sz, io_sz);

		अगर (qसमय > atomic64_पढ़ो(&iostats->max_qसमय))
			atomic64_set(&iostats->max_qसमय, qसमय);

		SNIC_SCSI_DBG(snic->shost,
			      "issue_sc:sc %p, tag %d queued to WQ.\n",
			      sc, tag);

		SNIC_TRC(snic->shost->host_no, tag, (uदीर्घ) sc, (uदीर्घ) rqi,
			 sg_cnt, cmd_trc, cmd_st_flags);
	पूर्ण

issue_sc_end:

	वापस ret;
पूर्ण /* end of snic_issue_scsi_req */


/*
 * snic_queuecommand
 * Routine to send a scsi cdb to LLD
 * Called with host_lock held and पूर्णांकerrupts disabled
 */
पूर्णांक
snic_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_tgt *tgt = शून्य;
	काष्ठा snic *snic = shost_priv(shost);
	पूर्णांक ret;

	tgt = starget_to_tgt(scsi_target(sc->device));
	ret = snic_tgt_chkपढ़ोy(tgt);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost, "Tgt %p id %d Not Ready.\n", tgt, tgt->id);
		atomic64_inc(&snic->s_stats.misc.tgt_not_rdy);
		sc->result = ret;
		sc->scsi_करोne(sc);

		वापस 0;
	पूर्ण

	अगर (snic_get_state(snic) != SNIC_ONLINE) अणु
		SNIC_HOST_ERR(shost, "snic state is %s\n",
			      snic_state_str[snic_get_state(snic)]);

		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	atomic_inc(&snic->ios_inflight);

	SNIC_SCSI_DBG(shost, "sc %p Tag %d (sc %0x) lun %lld in snic_qcmd\n",
		      sc, snic_cmd_tag(sc), sc->cmnd[0], sc->device->lun);

	ret = snic_issue_scsi_req(snic, tgt, sc);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost, "Failed to Q, Scsi Req w/ err %d.\n", ret);
		ret = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	atomic_dec(&snic->ios_inflight);

	वापस ret;
पूर्ण /* end of snic_queuecommand */

/*
 * snic_process_abts_pending_state:
 * caller should hold IO lock
 */
अटल व्योम
snic_proc_पंचांगreq_pending_state(काष्ठा snic *snic,
			      काष्ठा scsi_cmnd *sc,
			      u8 cmpl_status)
अणु
	पूर्णांक state = CMD_STATE(sc);

	अगर (state == SNIC_IOREQ_ABTS_PENDING)
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_PENDING;
	अन्यथा अगर (state == SNIC_IOREQ_LR_PENDING)
		CMD_FLAGS(sc) |= SNIC_DEV_RST_PENDING;
	अन्यथा
		SNIC_BUG_ON(1);

	चयन (cmpl_status) अणु
	हाल SNIC_STAT_IO_SUCCESS:
		CMD_FLAGS(sc) |= SNIC_IO_DONE;
		अवरोध;

	हाल SNIC_STAT_ABORTED:
		CMD_FLAGS(sc) |= SNIC_IO_ABORTED;
		अवरोध;

	शेष:
		SNIC_BUG_ON(1);
	पूर्ण
पूर्ण

/*
 * snic_process_io_failed_state:
 * Processes IO's error states
 */
अटल व्योम
snic_process_io_failed_state(काष्ठा snic *snic,
			     काष्ठा snic_icmnd_cmpl *icmnd_cmpl,
			     काष्ठा scsi_cmnd *sc,
			     u8 cmpl_stat)
अणु
	पूर्णांक res = 0;

	चयन (cmpl_stat) अणु
	हाल SNIC_STAT_TIMEOUT:		/* Req was समयकरोut */
		atomic64_inc(&snic->s_stats.misc.io_पंचांगo);
		res = DID_TIME_OUT;
		अवरोध;

	हाल SNIC_STAT_ABORTED:		/* Req was पातed */
		atomic64_inc(&snic->s_stats.misc.io_पातed);
		res = DID_ABORT;
		अवरोध;

	हाल SNIC_STAT_DATA_CNT_MISMATCH:/* Recv/Sent more/less data than exp */
		atomic64_inc(&snic->s_stats.misc.data_cnt_mismat);
		scsi_set_resid(sc, le32_to_cpu(icmnd_cmpl->resid));
		res = DID_ERROR;
		अवरोध;

	हाल SNIC_STAT_OUT_OF_RES: /* Out of resources to complete request */
		atomic64_inc(&snic->s_stats.fw.out_of_res);
		res = DID_REQUEUE;
		अवरोध;

	हाल SNIC_STAT_IO_NOT_FOUND:	/* Requested I/O was not found */
		atomic64_inc(&snic->s_stats.io.io_not_found);
		res = DID_ERROR;
		अवरोध;

	हाल SNIC_STAT_SGL_INVALID:	/* Req was पातed to due to sgl error*/
		atomic64_inc(&snic->s_stats.misc.sgl_inval);
		res = DID_ERROR;
		अवरोध;

	हाल SNIC_STAT_FW_ERR:		/* Req terminated due to FW Error */
		atomic64_inc(&snic->s_stats.fw.io_errs);
		res = DID_ERROR;
		अवरोध;

	हाल SNIC_STAT_SCSI_ERR:	/* FW hits SCSI Error */
		atomic64_inc(&snic->s_stats.fw.scsi_errs);
		अवरोध;

	हाल SNIC_STAT_NOT_READY:	/* XPT yet to initialize */
	हाल SNIC_STAT_DEV_OFFLINE:	/* Device offline */
		res = DID_NO_CONNECT;
		अवरोध;

	हाल SNIC_STAT_INVALID_HDR:	/* Hdr contains invalid data */
	हाल SNIC_STAT_INVALID_PARM:	/* Some param in req is invalid */
	हाल SNIC_STAT_REQ_NOT_SUP:	/* Req type is not supported */
	हाल SNIC_STAT_CMND_REJECT:	/* Req rejected */
	हाल SNIC_STAT_FATAL_ERROR:	/* XPT Error */
	शेष:
		SNIC_SCSI_DBG(snic->shost,
			      "Invalid Hdr/Param or Req Not Supported or Cmnd Rejected or Device Offline. or Unknown\n");
		res = DID_ERROR;
		अवरोध;
	पूर्ण

	SNIC_HOST_ERR(snic->shost, "fw returns failed status %s flags 0x%llx\n",
		      snic_io_status_to_str(cmpl_stat), CMD_FLAGS(sc));

	/* Set sc->result */
	sc->result = (res << 16) | icmnd_cmpl->scsi_status;
पूर्ण /* end of snic_process_io_failed_state */

/*
 * snic_पंचांगreq_pending : is task management in progress.
 */
अटल पूर्णांक
snic_पंचांगreq_pending(काष्ठा scsi_cmnd *sc)
अणु
	पूर्णांक state = CMD_STATE(sc);

	वापस ((state == SNIC_IOREQ_ABTS_PENDING) ||
			(state == SNIC_IOREQ_LR_PENDING));
पूर्ण

/*
 * snic_process_icmnd_cmpl_status:
 * Caller should hold io_lock
 */
अटल पूर्णांक
snic_process_icmnd_cmpl_status(काष्ठा snic *snic,
			       काष्ठा snic_icmnd_cmpl *icmnd_cmpl,
			       u8 cmpl_stat,
			       काष्ठा scsi_cmnd *sc)
अणु
	u8 scsi_stat = icmnd_cmpl->scsi_status;
	u64 xfer_len = 0;
	पूर्णांक ret = 0;

	/* Mark the IO as complete */
	CMD_STATE(sc) = SNIC_IOREQ_COMPLETE;

	अगर (likely(cmpl_stat == SNIC_STAT_IO_SUCCESS)) अणु
		sc->result = (DID_OK << 16) | scsi_stat;

		xfer_len = scsi_bufflen(sc);

		/* Update SCSI Cmd with resid value */
		scsi_set_resid(sc, le32_to_cpu(icmnd_cmpl->resid));

		अगर (icmnd_cmpl->flags & SNIC_ICMND_CMPL_UNDR_RUN) अणु
			xfer_len -= le32_to_cpu(icmnd_cmpl->resid);
			atomic64_inc(&snic->s_stats.misc.io_under_run);
		पूर्ण

		अगर (icmnd_cmpl->scsi_status == SAM_STAT_TASK_SET_FULL)
			atomic64_inc(&snic->s_stats.misc.qfull);

		ret = 0;
	पूर्ण अन्यथा अणु
		snic_process_io_failed_state(snic, icmnd_cmpl, sc, cmpl_stat);
		atomic64_inc(&snic->s_stats.io.fail);
		SNIC_HOST_ERR(snic->shost,
			      "icmnd_cmpl: IO Failed : Hdr Status %s flags 0x%llx\n",
			      snic_io_status_to_str(cmpl_stat), CMD_FLAGS(sc));
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण /* end of snic_process_icmnd_cmpl_status */


/*
 * snic_icmnd_cmpl_handler
 * Routine to handle icmnd completions
 */
अटल व्योम
snic_icmnd_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	u8 typ, hdr_stat;
	u32 cmnd_id, hid;
	uदीर्घ ctx;
	काष्ठा scsi_cmnd *sc = शून्य;
	काष्ठा snic_icmnd_cmpl *icmnd_cmpl = शून्य;
	काष्ठा snic_host_req *req = शून्य;
	काष्ठा snic_req_info *rqi = शून्य;
	अचिन्हित दीर्घ flags, start_समय;
	spinlock_t *io_lock;
	u8 sc_stat = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	icmnd_cmpl = &fwreq->u.icmnd_cmpl;
	sc_stat = icmnd_cmpl->scsi_status;

	SNIC_SCSI_DBG(snic->shost,
		      "Icmnd_cmpl: type = %x, hdr_stat = %x, cmnd_id = %x, hid = %x,i ctx = %lx\n",
		      typ, hdr_stat, cmnd_id, hid, ctx);

	अगर (cmnd_id >= snic->max_tag_id) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Icmnd_cmpl:Tag Error:Out of Range Tag %d, hdr status = %s\n",
			      cmnd_id, snic_io_status_to_str(hdr_stat));
		वापस;
	पूर्ण

	sc = scsi_host_find_tag(snic->shost, cmnd_id);
	WARN_ON_ONCE(!sc);

	अगर (!sc) अणु
		atomic64_inc(&snic->s_stats.io.sc_null);
		SNIC_HOST_ERR(snic->shost,
			      "Icmnd_cmpl: Scsi Cmnd Not found, sc = NULL Hdr Status = %s tag = 0x%x fwreq = 0x%p\n",
			      snic_io_status_to_str(hdr_stat),
			      cmnd_id,
			      fwreq);

		SNIC_TRC(snic->shost->host_no, cmnd_id, 0,
			 ((u64)hdr_stat << 16 |
			  (u64)sc_stat << 8 | (u64)icmnd_cmpl->flags),
			 (uदीर्घ) fwreq, le32_to_cpu(icmnd_cmpl->resid), ctx);

		वापस;
	पूर्ण

	io_lock = snic_io_lock_hash(snic, sc);

	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	SNIC_SCSI_DBG(snic->shost,
		      "Icmnd_cmpl:lun %lld sc %p cmd %xtag %d flags 0x%llx rqi %p\n",
		      sc->device->lun, sc, sc->cmnd[0], snic_cmd_tag(sc),
		      CMD_FLAGS(sc), rqi);

	अगर (CMD_FLAGS(sc) & SNIC_HOST_RESET_CMD_TERM) अणु
		spin_unlock_irqrestore(io_lock, flags);

		वापस;
	पूर्ण

	SNIC_BUG_ON(rqi != (काष्ठा snic_req_info *)ctx);
	WARN_ON_ONCE(req);
	अगर (!rqi) अणु
		atomic64_inc(&snic->s_stats.io.req_null);
		CMD_FLAGS(sc) |= SNIC_IO_REQ_शून्य;
		spin_unlock_irqrestore(io_lock, flags);

		SNIC_HOST_ERR(snic->shost,
			      "Icmnd_cmpl:Host Req Not Found(null), Hdr Status %s, Tag 0x%x, sc 0x%p flags 0x%llx\n",
			      snic_io_status_to_str(hdr_stat),
			      cmnd_id, sc, CMD_FLAGS(sc));
		वापस;
	पूर्ण

	rqi = (काष्ठा snic_req_info *) ctx;
	start_समय = rqi->start_समय;

	/* firmware completed the io */
	rqi->io_cmpl = 1;

	/*
	 * अगर SCSI-ML has alपढ़ोy issued पात on this command,
	 * ignore completion of the IO. The abts path will clean it up
	 */
	अगर (unlikely(snic_पंचांगreq_pending(sc))) अणु
		snic_proc_पंचांगreq_pending_state(snic, sc, hdr_stat);
		spin_unlock_irqrestore(io_lock, flags);

		snic_stats_update_io_cmpl(&snic->s_stats);

		/* Expected value is SNIC_STAT_ABORTED */
		अगर (likely(hdr_stat == SNIC_STAT_ABORTED))
			वापस;

		SNIC_SCSI_DBG(snic->shost,
			      "icmnd_cmpl:TM Req Pending(%s), Hdr Status %s sc 0x%p scsi status %x resid %d flags 0x%llx\n",
			      snic_ioreq_state_to_str(CMD_STATE(sc)),
			      snic_io_status_to_str(hdr_stat),
			      sc, sc_stat, le32_to_cpu(icmnd_cmpl->resid),
			      CMD_FLAGS(sc));

		SNIC_TRC(snic->shost->host_no, cmnd_id, (uदीर्घ) sc,
			 jअगरfies_to_msecs(jअगरfies - start_समय), (uदीर्घ) fwreq,
			 SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

		वापस;
	पूर्ण

	अगर (snic_process_icmnd_cmpl_status(snic, icmnd_cmpl, hdr_stat, sc)) अणु
		scsi_prपूर्णांक_command(sc);
		SNIC_HOST_ERR(snic->shost,
			      "icmnd_cmpl:IO Failed, sc 0x%p Tag %d Cmd %x Hdr Status %s flags 0x%llx\n",
			      sc, sc->cmnd[0], cmnd_id,
			      snic_io_status_to_str(hdr_stat), CMD_FLAGS(sc));
	पूर्ण

	/* Break link with the SCSI Command */
	CMD_SP(sc) = शून्य;
	CMD_FLAGS(sc) |= SNIC_IO_DONE;

	spin_unlock_irqrestore(io_lock, flags);

	/* For now, consider only successful IO. */
	snic_calc_io_process_समय(snic, rqi);

	snic_release_req_buf(snic, rqi, sc);

	SNIC_TRC(snic->shost->host_no, cmnd_id, (uदीर्घ) sc,
		 jअगरfies_to_msecs(jअगरfies - start_समय), (uदीर्घ) fwreq,
		 SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));


	अगर (sc->scsi_करोne)
		sc->scsi_करोne(sc);

	snic_stats_update_io_cmpl(&snic->s_stats);
पूर्ण /* end of snic_icmnd_cmpl_handler */

अटल व्योम
snic_proc_dr_cmpl_locked(काष्ठा snic *snic,
			 काष्ठा snic_fw_req *fwreq,
			 u8 cmpl_stat,
			 u32 cmnd_id,
			 काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	u32 start_समय = rqi->start_समय;

	CMD_LR_STATUS(sc) = cmpl_stat;

	SNIC_SCSI_DBG(snic->shost, "itmf_cmpl: Cmd State = %s\n",
		      snic_ioreq_state_to_str(CMD_STATE(sc)));

	अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING) अणु
		CMD_FLAGS(sc) |= SNIC_DEV_RST_ABTS_PENDING;

		SNIC_TRC(snic->shost->host_no, cmnd_id, (uदीर्घ) sc,
			 jअगरfies_to_msecs(jअगरfies - start_समय),
			 (uदीर्घ) fwreq, 0, SNIC_TRC_CMD_STATE_FLAGS(sc));

		SNIC_SCSI_DBG(snic->shost,
			      "itmf_cmpl: Terminate Pending Dev Reset Cmpl Recvd.id %x, status %s flags 0x%llx\n",
			      (पूर्णांक)(cmnd_id & SNIC_TAG_MASK),
			      snic_io_status_to_str(cmpl_stat),
			      CMD_FLAGS(sc));

		वापस;
	पूर्ण


	अगर (CMD_FLAGS(sc) & SNIC_DEV_RST_TIMEDOUT) अणु
		SNIC_TRC(snic->shost->host_no, cmnd_id, (uदीर्घ) sc,
			 jअगरfies_to_msecs(jअगरfies - start_समय),
			 (uदीर्घ) fwreq, 0, SNIC_TRC_CMD_STATE_FLAGS(sc));

		SNIC_SCSI_DBG(snic->shost,
			      "itmf_cmpl:Dev Reset Completion Received after timeout. id %d cmpl status %s flags 0x%llx\n",
			      (पूर्णांक)(cmnd_id & SNIC_TAG_MASK),
			      snic_io_status_to_str(cmpl_stat),
			      CMD_FLAGS(sc));

		वापस;
	पूर्ण

	CMD_STATE(sc) = SNIC_IOREQ_LR_COMPLETE;
	CMD_FLAGS(sc) |= SNIC_DEV_RST_DONE;

	SNIC_SCSI_DBG(snic->shost,
		      "itmf_cmpl:Dev Reset Cmpl Recvd id %d cmpl status %s flags 0x%llx\n",
		      (पूर्णांक)(cmnd_id & SNIC_TAG_MASK),
		      snic_io_status_to_str(cmpl_stat),
		      CMD_FLAGS(sc));

	अगर (rqi->dr_करोne)
		complete(rqi->dr_करोne);
पूर्ण /* end of snic_proc_dr_cmpl_locked */

/*
 * snic_update_पात_stats : Updates पात stats based on completion status.
 */
अटल व्योम
snic_update_पात_stats(काष्ठा snic *snic, u8 cmpl_stat)
अणु
	काष्ठा snic_पात_stats *abt_stats = &snic->s_stats.abts;

	SNIC_SCSI_DBG(snic->shost, "Updating Abort stats.\n");

	चयन (cmpl_stat) अणु
	हाल  SNIC_STAT_IO_SUCCESS:
		अवरोध;

	हाल SNIC_STAT_TIMEOUT:
		atomic64_inc(&abt_stats->fw_पंचांगo);
		अवरोध;

	हाल SNIC_STAT_IO_NOT_FOUND:
		atomic64_inc(&abt_stats->io_not_found);
		अवरोध;

	शेष:
		atomic64_inc(&abt_stats->fail);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
snic_process_iपंचांगf_cmpl(काष्ठा snic *snic,
		       काष्ठा snic_fw_req *fwreq,
		       u32 cmnd_id,
		       u8 cmpl_stat,
		       काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	u32 पंचांग_tags = 0;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	u32 start_समय = 0;
	पूर्णांक ret = 0;

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	अगर (CMD_FLAGS(sc) & SNIC_HOST_RESET_CMD_TERM) अणु
		spin_unlock_irqrestore(io_lock, flags);

		वापस ret;
	पूर्ण
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	WARN_ON_ONCE(!rqi);

	अगर (!rqi) अणु
		atomic64_inc(&snic->s_stats.io.req_null);
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_REQ_शून्य;
		SNIC_HOST_ERR(snic->shost,
			      "itmf_cmpl: rqi is null,Hdr stat = %s Tag = 0x%x sc = 0x%p flags 0x%llx\n",
			      snic_io_status_to_str(cmpl_stat), cmnd_id, sc,
			      CMD_FLAGS(sc));

		वापस ret;
	पूर्ण

	/* Extract task management flags */
	पंचांग_tags = cmnd_id & ~(SNIC_TAG_MASK);

	start_समय = rqi->start_समय;
	cmnd_id &= (SNIC_TAG_MASK);

	चयन (पंचांग_tags) अणु
	हाल SNIC_TAG_ABORT:
		/* Abort only issued on cmd */
		snic_update_पात_stats(snic, cmpl_stat);

		अगर (CMD_STATE(sc) != SNIC_IOREQ_ABTS_PENDING) अणु
			/* This is a late completion. Ignore it. */
			ret = -1;
			spin_unlock_irqrestore(io_lock, flags);
			अवरोध;
		पूर्ण

		CMD_STATE(sc) = SNIC_IOREQ_ABTS_COMPLETE;
		CMD_ABTS_STATUS(sc) = cmpl_stat;
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_DONE;

		SNIC_SCSI_DBG(snic->shost,
			      "itmf_cmpl:Abort Cmpl Recvd.Tag 0x%x Status %s flags 0x%llx\n",
			      cmnd_id,
			      snic_io_status_to_str(cmpl_stat),
			      CMD_FLAGS(sc));

		/*
		 * If scsi_eh thपढ़ो is blocked रुकोing क्रम abts complete,
		 * संकेत completion to it. IO will be cleaned in the thपढ़ो,
		 * अन्यथा clean it in this context.
		 */
		अगर (rqi->abts_करोne) अणु
			complete(rqi->abts_करोne);
			spin_unlock_irqrestore(io_lock, flags);

			अवरोध; /* jump out */
		पूर्ण

		CMD_SP(sc) = शून्य;
		sc->result = (DID_ERROR << 16);
		SNIC_SCSI_DBG(snic->shost,
			      "itmf_cmpl: Completing IO. sc %p flags 0x%llx\n",
			      sc, CMD_FLAGS(sc));

		spin_unlock_irqrestore(io_lock, flags);

		snic_release_req_buf(snic, rqi, sc);

		अगर (sc->scsi_करोne) अणु
			SNIC_TRC(snic->shost->host_no, cmnd_id, (uदीर्घ) sc,
				 jअगरfies_to_msecs(jअगरfies - start_समय),
				 (uदीर्घ) fwreq, SNIC_TRC_CMD(sc),
				 SNIC_TRC_CMD_STATE_FLAGS(sc));

			sc->scsi_करोne(sc);
		पूर्ण

		अवरोध;

	हाल SNIC_TAG_DEV_RST:
	हाल SNIC_TAG_DEV_RST | SNIC_TAG_IOCTL_DEV_RST:
		snic_proc_dr_cmpl_locked(snic, fwreq, cmpl_stat, cmnd_id, sc);
		spin_unlock_irqrestore(io_lock, flags);
		ret = 0;

		अवरोध;

	हाल SNIC_TAG_ABORT | SNIC_TAG_DEV_RST:
		/* Abort and terminate completion of device reset req */

		CMD_STATE(sc) = SNIC_IOREQ_ABTS_COMPLETE;
		CMD_ABTS_STATUS(sc) = cmpl_stat;
		CMD_FLAGS(sc) |= SNIC_DEV_RST_DONE;

		SNIC_SCSI_DBG(snic->shost,
			      "itmf_cmpl:dev reset abts cmpl recvd. id %d status %s flags 0x%llx\n",
			      cmnd_id, snic_io_status_to_str(cmpl_stat),
			      CMD_FLAGS(sc));

		अगर (rqi->abts_करोne)
			complete(rqi->abts_करोne);

		spin_unlock_irqrestore(io_lock, flags);

		अवरोध;

	शेष:
		spin_unlock_irqrestore(io_lock, flags);
		SNIC_HOST_ERR(snic->shost,
			      "itmf_cmpl: Unknown TM tag bit 0x%x\n", पंचांग_tags);

		SNIC_HOST_ERR(snic->shost,
			      "itmf_cmpl:Unexpected itmf io stat %s Tag = 0x%x flags 0x%llx\n",
			      snic_ioreq_state_to_str(CMD_STATE(sc)),
			      cmnd_id,
			      CMD_FLAGS(sc));
		ret = -1;
		SNIC_BUG_ON(1);

		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण /* end of snic_process_iपंचांगf_cmpl_status */

/*
 * snic_iपंचांगf_cmpl_handler.
 * Routine to handle iपंचांगf completions.
 */
अटल व्योम
snic_iपंचांगf_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	काष्ठा scsi_cmnd  *sc = शून्य;
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_iपंचांगf_cmpl *iपंचांगf_cmpl = शून्य;
	uदीर्घ ctx;
	u32 cmnd_id;
	u32 hid;
	u8 typ;
	u8 hdr_stat;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	SNIC_SCSI_DBG(snic->shost,
		      "Itmf_cmpl: %s: type = %x, hdr_stat = %x, cmnd_id = %x, hid = %x,ctx = %lx\n",
		      __func__, typ, hdr_stat, cmnd_id, hid, ctx);

	iपंचांगf_cmpl = &fwreq->u.iपंचांगf_cmpl;
	SNIC_SCSI_DBG(snic->shost,
		      "Itmf_cmpl: nterm %u , flags 0x%x\n",
		      le32_to_cpu(iपंचांगf_cmpl->nterminated), iपंचांगf_cmpl->flags);

	/* spl हाल, dev reset issued through ioctl */
	अगर (cmnd_id & SNIC_TAG_IOCTL_DEV_RST) अणु
		rqi = (काष्ठा snic_req_info *) ctx;
		sc = rqi->sc;

		जाओ ioctl_dev_rst;
	पूर्ण

	अगर ((cmnd_id & SNIC_TAG_MASK) >= snic->max_tag_id) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Itmf_cmpl: Tag 0x%x out of Range,HdrStat %s\n",
			      cmnd_id, snic_io_status_to_str(hdr_stat));
		SNIC_BUG_ON(1);

		वापस;
	पूर्ण

	sc = scsi_host_find_tag(snic->shost, cmnd_id & SNIC_TAG_MASK);
	WARN_ON_ONCE(!sc);

ioctl_dev_rst:
	अगर (!sc) अणु
		atomic64_inc(&snic->s_stats.io.sc_null);
		SNIC_HOST_ERR(snic->shost,
			      "Itmf_cmpl: sc is NULL - Hdr Stat %s Tag 0x%x\n",
			      snic_io_status_to_str(hdr_stat), cmnd_id);

		वापस;
	पूर्ण

	snic_process_iपंचांगf_cmpl(snic, fwreq, cmnd_id, hdr_stat, sc);
पूर्ण /* end of snic_iपंचांगf_cmpl_handler */



अटल व्योम
snic_hba_reset_scsi_cleanup(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_stats *st = &snic->s_stats;
	दीर्घ act_ios = 0, act_fwreqs = 0;

	SNIC_SCSI_DBG(snic->shost, "HBA Reset scsi cleanup.\n");
	snic_scsi_cleanup(snic, snic_cmd_tag(sc));

	/* Update stats on pending IOs */
	act_ios = atomic64_पढ़ो(&st->io.active);
	atomic64_add(act_ios, &st->io.compl);
	atomic64_sub(act_ios, &st->io.active);

	act_fwreqs = atomic64_पढ़ो(&st->fw.actv_reqs);
	atomic64_sub(act_fwreqs, &st->fw.actv_reqs);
पूर्ण

/*
 * snic_hba_reset_cmpl_handler :
 *
 * Notes :
 * 1. Cleanup all the scsi cmds, release all snic specअगरic cmds
 * 2. Issue Report Tarमाला_लो in हाल of SAN tarमाला_लो
 */
अटल पूर्णांक
snic_hba_reset_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	uदीर्घ ctx;
	u32 cmnd_id;
	u32 hid;
	u8 typ;
	u8 hdr_stat;
	काष्ठा scsi_cmnd *sc = शून्य;
	काष्ठा snic_req_info *rqi = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags, gflags;
	पूर्णांक ret = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	SNIC_HOST_INFO(snic->shost,
		       "reset_cmpl:Tag %d ctx %lx cmpl status %s HBA Reset Completion received.\n",
		       cmnd_id, ctx, snic_io_status_to_str(hdr_stat));

	SNIC_SCSI_DBG(snic->shost,
		      "reset_cmpl: type = %x, hdr_stat = %x, cmnd_id = %x, hid = %x, ctx = %lx\n",
		      typ, hdr_stat, cmnd_id, hid, ctx);

	/* spl हाल, host reset issued through ioctl */
	अगर (cmnd_id == SCSI_NO_TAG) अणु
		rqi = (काष्ठा snic_req_info *) ctx;
		SNIC_HOST_INFO(snic->shost,
			       "reset_cmpl:Tag %d ctx %lx cmpl stat %s\n",
			       cmnd_id, ctx, snic_io_status_to_str(hdr_stat));
		sc = rqi->sc;

		जाओ ioctl_hba_rst;
	पूर्ण

	अगर (cmnd_id >= snic->max_tag_id) अणु
		SNIC_HOST_ERR(snic->shost,
			      "reset_cmpl: Tag 0x%x out of Range,HdrStat %s\n",
			      cmnd_id, snic_io_status_to_str(hdr_stat));
		SNIC_BUG_ON(1);

		वापस 1;
	पूर्ण

	sc = scsi_host_find_tag(snic->shost, cmnd_id);
ioctl_hba_rst:
	अगर (!sc) अणु
		atomic64_inc(&snic->s_stats.io.sc_null);
		SNIC_HOST_ERR(snic->shost,
			      "reset_cmpl: sc is NULL - Hdr Stat %s Tag 0x%x\n",
			      snic_io_status_to_str(hdr_stat), cmnd_id);
		ret = 1;

		वापस ret;
	पूर्ण

	SNIC_HOST_INFO(snic->shost,
		       "reset_cmpl: sc %p rqi %p Tag %d flags 0x%llx\n",
		       sc, rqi, cmnd_id, CMD_FLAGS(sc));

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);

	अगर (!snic->हटाओ_रुको) अणु
		spin_unlock_irqrestore(io_lock, flags);
		SNIC_HOST_ERR(snic->shost,
			      "reset_cmpl:host reset completed after timeout\n");
		ret = 1;

		वापस ret;
	पूर्ण

	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	WARN_ON_ONCE(!rqi);

	अगर (!rqi) अणु
		atomic64_inc(&snic->s_stats.io.req_null);
		spin_unlock_irqrestore(io_lock, flags);
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_REQ_शून्य;
		SNIC_HOST_ERR(snic->shost,
			      "reset_cmpl: rqi is null,Hdr stat %s Tag 0x%x sc 0x%p flags 0x%llx\n",
			      snic_io_status_to_str(hdr_stat), cmnd_id, sc,
			      CMD_FLAGS(sc));

		ret = 1;

		वापस ret;
	पूर्ण
	/* stats */
	spin_unlock_irqrestore(io_lock, flags);

	/* scsi cleanup */
	snic_hba_reset_scsi_cleanup(snic, sc);

	SNIC_BUG_ON(snic_get_state(snic) != SNIC_OFFLINE &&
		    snic_get_state(snic) != SNIC_FWRESET);

	/* Careful locking between snic_lock and io lock */
	spin_lock_irqsave(io_lock, flags);
	spin_lock_irqsave(&snic->snic_lock, gflags);
	अगर (snic_get_state(snic) == SNIC_FWRESET)
		snic_set_state(snic, SNIC_ONLINE);
	spin_unlock_irqrestore(&snic->snic_lock, gflags);

	अगर (snic->हटाओ_रुको)
		complete(snic->हटाओ_रुको);

	spin_unlock_irqrestore(io_lock, flags);
	atomic64_inc(&snic->s_stats.reset.hba_reset_cmpl);

	ret = 0;
	/* Rediscovery is क्रम SAN */
	अगर (snic->config.xpt_type == SNIC_DAS)
			वापस ret;

	SNIC_SCSI_DBG(snic->shost, "reset_cmpl: Queuing discovery work.\n");
	queue_work(snic_glob->event_q, &snic->disc_work);

	वापस ret;
पूर्ण

अटल व्योम
snic_msg_ack_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	SNIC_HOST_INFO(snic->shost, "Message Ack Received.\n");

	SNIC_ASSERT_NOT_IMPL(1);
पूर्ण

अटल व्योम
snic_aen_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	u8 typ, hdr_stat;
	u32 cmnd_id, hid;
	uदीर्घ ctx;
	काष्ठा snic_async_evnotअगरy *aen = &fwreq->u.async_ev;
	u32 event_id = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	SNIC_SCSI_DBG(snic->shost,
		      "aen: type = %x, hdr_stat = %x, cmnd_id = %x, hid = %x, ctx = %lx\n",
		      typ, hdr_stat, cmnd_id, hid, ctx);

	event_id = le32_to_cpu(aen->ev_id);

	चयन (event_id) अणु
	हाल SNIC_EV_TGT_OFFLINE:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_OFFLINE Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_TGT_ONLINE:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_ONLINE Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_LUN_OFFLINE:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_OFFLINE Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_LUN_ONLINE:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_ONLINE Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_CONF_CHG:
		SNIC_HOST_INFO(snic->shost, "aen:Config Change Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_TGT_ADDED:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_ADD Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_TGT_DELTD:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_DEL Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_LUN_ADDED:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_ADD Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_LUN_DELTD:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_DEL Event Recvd.\n");
		अवरोध;

	हाल SNIC_EV_DISC_CMPL:
		SNIC_HOST_INFO(snic->shost, "aen:DISC_CMPL Event Recvd.\n");
		अवरोध;

	शेष:
		SNIC_HOST_INFO(snic->shost, "aen:Unknown Event Recvd.\n");
		SNIC_BUG_ON(1);
		अवरोध;
	पूर्ण

	SNIC_ASSERT_NOT_IMPL(1);
पूर्ण /* end of snic_aen_handler */

/*
 * snic_io_cmpl_handler
 * Routine to process CQ entries(IO Completions) posted by fw.
 */
अटल पूर्णांक
snic_io_cmpl_handler(काष्ठा vnic_dev *vdev,
		     अचिन्हित पूर्णांक cq_idx,
		     काष्ठा snic_fw_req *fwreq)
अणु
	काष्ठा snic *snic = svnic_dev_priv(vdev);
	u64 start = jअगरfies, cmpl_समय;

	snic_prपूर्णांक_desc(__func__, (अक्षर *)fwreq, माप(*fwreq));

	/* Update FW Stats */
	अगर ((fwreq->hdr.type >= SNIC_RSP_REPORT_TGTS_CMPL) &&
		(fwreq->hdr.type <= SNIC_RSP_BOOT_LUNS_CMPL))
		atomic64_dec(&snic->s_stats.fw.actv_reqs);

	SNIC_BUG_ON((fwreq->hdr.type > SNIC_RSP_BOOT_LUNS_CMPL) &&
		    (fwreq->hdr.type < SNIC_MSG_ASYNC_EVNOTIFY));

	/* Check क्रम snic subsys errors */
	चयन (fwreq->hdr.status) अणु
	हाल SNIC_STAT_NOT_READY:	/* XPT yet to initialize */
		SNIC_HOST_ERR(snic->shost,
			      "sNIC SubSystem is NOT Ready.\n");
		अवरोध;

	हाल SNIC_STAT_FATAL_ERROR:	/* XPT Error */
		SNIC_HOST_ERR(snic->shost,
			      "sNIC SubSystem in Unrecoverable State.\n");
		अवरोध;
	पूर्ण

	चयन (fwreq->hdr.type) अणु
	हाल SNIC_RSP_EXCH_VER_CMPL:
		snic_io_exch_ver_cmpl_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_RSP_REPORT_TGTS_CMPL:
		snic_report_tgt_cmpl_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_RSP_ICMND_CMPL:
		snic_icmnd_cmpl_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_RSP_ITMF_CMPL:
		snic_iपंचांगf_cmpl_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_RSP_HBA_RESET_CMPL:
		snic_hba_reset_cmpl_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_MSG_ACK:
		snic_msg_ack_handler(snic, fwreq);
		अवरोध;

	हाल SNIC_MSG_ASYNC_EVNOTIFY:
		snic_aen_handler(snic, fwreq);
		अवरोध;

	शेष:
		SNIC_BUG_ON(1);
		SNIC_SCSI_DBG(snic->shost,
			      "Unknown Firmware completion request type %d\n",
			      fwreq->hdr.type);
		अवरोध;
	पूर्ण

	/* Update Stats */
	cmpl_समय = jअगरfies - start;
	अगर (cmpl_समय > atomic64_पढ़ो(&snic->s_stats.io.max_cmpl_समय))
		atomic64_set(&snic->s_stats.io.max_cmpl_समय, cmpl_समय);

	वापस 0;
पूर्ण /* end of snic_io_cmpl_handler */

/*
 * snic_fwcq_cmpl_handler
 * Routine to process fwCQ
 * This CQ is independent, and not associated with wq/rq/wq_copy queues
 */
पूर्णांक
snic_fwcq_cmpl_handler(काष्ठा snic *snic, पूर्णांक io_cmpl_work)
अणु
	अचिन्हित पूर्णांक num_ent = 0;	/* number cq entries processed */
	अचिन्हित पूर्णांक cq_idx;
	अचिन्हित पूर्णांक nent_per_cq;
	काष्ठा snic_misc_stats *misc_stats = &snic->s_stats.misc;

	क्रम (cq_idx = snic->wq_count; cq_idx < snic->cq_count; cq_idx++) अणु
		nent_per_cq = vnic_cq_fw_service(&snic->cq[cq_idx],
						 snic_io_cmpl_handler,
						 io_cmpl_work);
		num_ent += nent_per_cq;

		अगर (nent_per_cq > atomic64_पढ़ो(&misc_stats->max_cq_ents))
			atomic64_set(&misc_stats->max_cq_ents, nent_per_cq);
	पूर्ण

	वापस num_ent;
पूर्ण /* end of snic_fwcq_cmpl_handler */

/*
 * snic_queue_iपंचांगf_req: Common API to queue Task Management requests.
 * Use rqi->पंचांग_tag क्रम passing special tags.
 * @req_id : पातed request's tag, -1 क्रम lun reset.
 */
अटल पूर्णांक
snic_queue_iपंचांगf_req(काष्ठा snic *snic,
		    काष्ठा snic_host_req *पंचांगreq,
		    काष्ठा scsi_cmnd *sc,
		    u32 पंचांगf,
		    u32 req_id)
अणु
	काष्ठा snic_req_info *rqi = req_to_rqi(पंचांगreq);
	काष्ठा scsi_lun lun;
	पूर्णांक पंचांग_tag = snic_cmd_tag(sc) | rqi->पंचांग_tag;
	पूर्णांक ret = 0;

	SNIC_BUG_ON(!rqi);
	SNIC_BUG_ON(!rqi->पंचांग_tag);

	/* fill in lun info */
	पूर्णांक_to_scsilun(sc->device->lun, &lun);

	/* Initialize snic_host_req: iपंचांगf */
	snic_iपंचांगf_init(पंचांगreq,
		       पंचांग_tag,
		       snic->config.hid,
		       (uदीर्घ) rqi,
		       0 /* flags */,
		       req_id, /* Command to be पातed. */
		       rqi->tgt_id,
		       lun.scsi_lun,
		       पंचांगf);

	/*
	 * In हाल of multiple पातs on same cmd,
	 * use try_रुको_क्रम_completion and completion_करोne() to check
	 * whether it queues पातs even after completion of पात issued
	 * prior.SNIC_BUG_ON(completion_करोne(&rqi->करोne));
	 */

	ret = snic_queue_wq_desc(snic, पंचांगreq, माप(*पंचांगreq));
	अगर (ret)
		SNIC_HOST_ERR(snic->shost,
			      "qitmf:Queuing ITMF(%d) Req sc %p, rqi %p, req_id %d tag %d Failed, ret = %d\n",
			      पंचांगf, sc, rqi, req_id, snic_cmd_tag(sc), ret);
	अन्यथा
		SNIC_SCSI_DBG(snic->shost,
			      "qitmf:Queuing ITMF(%d) Req sc %p, rqi %p, req_id %d, tag %d (req_id)- Success.",
			      पंचांगf, sc, rqi, req_id, snic_cmd_tag(sc));

	वापस ret;
पूर्ण /* end of snic_queue_iपंचांगf_req */

अटल पूर्णांक
snic_issue_पंचांग_req(काष्ठा snic *snic,
		    काष्ठा snic_req_info *rqi,
		    काष्ठा scsi_cmnd *sc,
		    पूर्णांक पंचांगf)
अणु
	काष्ठा snic_host_req *पंचांगreq = शून्य;
	पूर्णांक req_id = 0, tag = snic_cmd_tag(sc);
	पूर्णांक ret = 0;

	अगर (snic_get_state(snic) == SNIC_FWRESET)
		वापस -EBUSY;

	atomic_inc(&snic->ios_inflight);

	SNIC_SCSI_DBG(snic->shost,
		      "issu_tmreq: Task mgmt req %d. rqi %p w/ tag %x\n",
		      पंचांगf, rqi, tag);


	अगर (पंचांगf == SNIC_ITMF_LUN_RESET) अणु
		पंचांगreq = snic_dr_req_init(snic, rqi);
		req_id = SCSI_NO_TAG;
	पूर्ण अन्यथा अणु
		पंचांगreq = snic_पात_req_init(snic, rqi);
		req_id = tag;
	पूर्ण

	अगर (!पंचांगreq) अणु
		ret = -ENOMEM;

		जाओ पंचांगreq_err;
	पूर्ण

	ret = snic_queue_iपंचांगf_req(snic, पंचांगreq, sc, पंचांगf, req_id);

पंचांगreq_err:
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "issu_tmreq: Queueing ITMF(%d) Req, sc %p rqi %p req_id %d tag %x fails err = %d\n",
			      पंचांगf, sc, rqi, req_id, tag, ret);
	पूर्ण अन्यथा अणु
		SNIC_SCSI_DBG(snic->shost,
			      "issu_tmreq: Queueing ITMF(%d) Req, sc %p, rqi %p, req_id %d tag %x - Success.\n",
			      पंचांगf, sc, rqi, req_id, tag);
	पूर्ण

	atomic_dec(&snic->ios_inflight);

	वापस ret;
पूर्ण

/*
 * snic_queue_पात_req : Queues पात req to WQ
 */
अटल पूर्णांक
snic_queue_पात_req(काष्ठा snic *snic,
		     काष्ठा snic_req_info *rqi,
		     काष्ठा scsi_cmnd *sc,
		     पूर्णांक पंचांगf)
अणु
	SNIC_SCSI_DBG(snic->shost, "q_abtreq: sc %p, rqi %p, tag %x, tmf %d\n",
		      sc, rqi, snic_cmd_tag(sc), पंचांगf);

	/* Add special tag क्रम पात */
	rqi->पंचांग_tag |= SNIC_TAG_ABORT;

	वापस snic_issue_पंचांग_req(snic, rqi, sc, पंचांगf);
पूर्ण

/*
 * snic_पात_finish : called by snic_पात_cmd on queuing पात successfully.
 */
अटल पूर्णांक
snic_पात_finish(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, tag = snic_cmd_tag(sc);

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi) अणु
		atomic64_inc(&snic->s_stats.io.req_null);
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_REQ_शून्य;

		SNIC_SCSI_DBG(snic->shost,
			      "abt_fini:req info is null tag 0x%x, sc 0x%p flags 0x%llx\n",
			      tag, sc, CMD_FLAGS(sc));
		ret = FAILED;

		जाओ पात_fail;
	पूर्ण

	rqi->abts_करोne = शून्य;

	ret = FAILED;

	/* Check the पात status. */
	चयन (CMD_ABTS_STATUS(sc)) अणु
	हाल SNIC_INVALID_CODE:
		/* Firmware didn't complete पात req, समयकरोut */
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TIMEDOUT;
		atomic64_inc(&snic->s_stats.abts.drv_पंचांगo);
		SNIC_SCSI_DBG(snic->shost,
			      "abt_fini:sc %p Tag %x Driver Timeout.flags 0x%llx\n",
			      sc, snic_cmd_tag(sc), CMD_FLAGS(sc));
		/* करो not release snic request in समयकरोut हाल */
		rqi = शून्य;

		जाओ पात_fail;

	हाल SNIC_STAT_IO_SUCCESS:
	हाल SNIC_STAT_IO_NOT_FOUND:
		ret = SUCCESS;
		/*
		 * If पात path करोesn't call scsi_करोne(),
		 * the # IO समयouts == 2, will cause the LUN offline.
		 * Call scsi_करोne to complete the IO.
		 */
		sc->result = (DID_ERROR << 16);
		sc->scsi_करोne(sc);
		अवरोध;

	शेष:
		/* Firmware completed पात with error */
		ret = FAILED;
		rqi = शून्य;
		अवरोध;
	पूर्ण

	CMD_SP(sc) = शून्य;
	SNIC_HOST_INFO(snic->shost,
		       "abt_fini: Tag %x, Cmpl Status %s flags 0x%llx\n",
		       tag, snic_io_status_to_str(CMD_ABTS_STATUS(sc)),
		       CMD_FLAGS(sc));

पात_fail:
	spin_unlock_irqrestore(io_lock, flags);
	अगर (rqi)
		snic_release_req_buf(snic, rqi, sc);

	वापस ret;
पूर्ण /* end of snic_पात_finish */

/*
 * snic_send_पात_and_रुको : Issues Abort, and Waits
 */
अटल पूर्णांक
snic_send_पात_and_रुको(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	क्रमागत snic_ioreq_state sv_state;
	काष्ठा snic_tgt *tgt = शून्य;
	spinlock_t *io_lock = शून्य;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, पंचांगf = 0, tag = snic_cmd_tag(sc);

	tgt = starget_to_tgt(scsi_target(sc->device));
	अगर ((snic_tgt_chkपढ़ोy(tgt) != 0) && (tgt->tdata.typ == SNIC_TGT_SAN))
		पंचांगf = SNIC_ITMF_ABTS_TASK_TERM;
	अन्यथा
		पंचांगf = SNIC_ITMF_ABTS_TASK;

	/* stats */

	io_lock = snic_io_lock_hash(snic, sc);

	/*
	 * Aव्योम a race between SCSI issuing the पात and the device
	 * completing the command.
	 *
	 * If the command is alपढ़ोy completed by fw_cmpl code,
	 * we just वापस SUCCESS from here. This means that the पात
	 * succeeded. In the SCSI ML, since the समयout क्रम command has
	 * happend, the completion wont actually complete the command
	 * and it will be considered as an पातed command
	 *
	 * The CMD_SP will not be cleared except जबतक holding io_lock
	 */
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi) अणु
		spin_unlock_irqrestore(io_lock, flags);

		SNIC_HOST_ERR(snic->shost,
			      "abt_cmd: rqi is null. Tag %d flags 0x%llx\n",
			      tag, CMD_FLAGS(sc));

		ret = SUCCESS;

		जाओ send_abts_end;
	पूर्ण

	rqi->abts_करोne = &पंचांग_करोne;
	अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING) अणु
		spin_unlock_irqrestore(io_lock, flags);

		ret = 0;
		जाओ abts_pending;
	पूर्ण
	SNIC_BUG_ON(!rqi->abts_करोne);

	/* Save Command State, should be restored on failed to Queue. */
	sv_state = CMD_STATE(sc);

	/*
	 * Command is still pending, need to पात it
	 * If the fw completes the command after this poपूर्णांक,
	 * the completion won't be करोne till mid-layer, since abot
	 * has alपढ़ोy started.
	 */
	CMD_STATE(sc) = SNIC_IOREQ_ABTS_PENDING;
	CMD_ABTS_STATUS(sc) = SNIC_INVALID_CODE;

	SNIC_SCSI_DBG(snic->shost, "send_abt_cmd: TAG 0x%x\n", tag);

	spin_unlock_irqrestore(io_lock, flags);

	/* Now Queue the पात command to firmware */
	ret = snic_queue_पात_req(snic, rqi, sc, पंचांगf);
	अगर (ret) अणु
		atomic64_inc(&snic->s_stats.abts.q_fail);
		SNIC_HOST_ERR(snic->shost,
			      "send_abt_cmd: IO w/ Tag 0x%x fail w/ err %d flags 0x%llx\n",
			      tag, ret, CMD_FLAGS(sc));

		spin_lock_irqsave(io_lock, flags);
		/* Restore Command's previous state */
		CMD_STATE(sc) = sv_state;
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (rqi)
			rqi->abts_करोne = शून्य;
		spin_unlock_irqrestore(io_lock, flags);
		ret = FAILED;

		जाओ send_abts_end;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	अगर (पंचांगf == SNIC_ITMF_ABTS_TASK) अणु
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_ISSUED;
		atomic64_inc(&snic->s_stats.abts.num);
	पूर्ण अन्यथा अणु
		/* term stats */
		CMD_FLAGS(sc) |= SNIC_IO_TERM_ISSUED;
	पूर्ण
	spin_unlock_irqrestore(io_lock, flags);

	SNIC_SCSI_DBG(snic->shost,
		      "send_abt_cmd: sc %p Tag %x flags 0x%llx\n",
		      sc, tag, CMD_FLAGS(sc));


	ret = 0;

abts_pending:
	/*
	 * Queued an पात IO, रुको क्रम its completion.
	 * Once the fw completes the पात command, it will
	 * wakeup this thपढ़ो.
	 */
	रुको_क्रम_completion_समयout(&पंचांग_करोne, SNIC_ABTS_TIMEOUT);

send_abts_end:
	वापस ret;
पूर्ण /* end of snic_send_पात_and_रुको */

/*
 * This function is exported to SCSI क्रम sending पात cmnds.
 * A SCSI IO is represent by snic_ioreq in the driver.
 * The snic_ioreq is linked to the SCSI Cmd, thus a link with the ULP'S IO
 */
पूर्णांक
snic_पात_cmd(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic *snic = shost_priv(sc->device->host);
	पूर्णांक ret = SUCCESS, tag = snic_cmd_tag(sc);
	u32 start_समय = jअगरfies;

	SNIC_SCSI_DBG(snic->shost, "abt_cmd:sc %p :0x%x :req = %p :tag = %d\n",
		       sc, sc->cmnd[0], sc->request, tag);

	अगर (unlikely(snic_get_state(snic) != SNIC_ONLINE)) अणु
		SNIC_HOST_ERR(snic->shost,
			      "abt_cmd: tag %x Parent Devs are not rdy\n",
			      tag);
		ret = FAST_IO_FAIL;

		जाओ पात_end;
	पूर्ण


	ret = snic_send_पात_and_रुको(snic, sc);
	अगर (ret)
		जाओ पात_end;

	ret = snic_पात_finish(snic, sc);

पात_end:
	SNIC_TRC(snic->shost->host_no, tag, (uदीर्घ) sc,
		 jअगरfies_to_msecs(jअगरfies - start_समय), 0,
		 SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

	SNIC_SCSI_DBG(snic->shost,
		      "abts: Abort Req Status = %s\n",
		      (ret == SUCCESS) ? "SUCCESS" :
		       ((ret == FAST_IO_FAIL) ? "FAST_IO_FAIL" : "FAILED"));

	वापस ret;
पूर्ण



अटल पूर्णांक
snic_is_abts_pending(काष्ठा snic *snic, काष्ठा scsi_cmnd *lr_sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा scsi_cmnd *sc = शून्य;
	काष्ठा scsi_device *lr_sdev = शून्य;
	spinlock_t *io_lock = शून्य;
	u32 tag;
	अचिन्हित दीर्घ flags;

	अगर (lr_sc)
		lr_sdev = lr_sc->device;

	/* walk through the tag map, an dcheck अगर IOs are still pending in fw*/
	क्रम (tag = 0; tag < snic->max_tag_id; tag++) अणु
		io_lock = snic_io_lock_tag(snic, tag);

		spin_lock_irqsave(io_lock, flags);
		sc = scsi_host_find_tag(snic->shost, tag);

		अगर (!sc || (lr_sc && (sc->device != lr_sdev || sc == lr_sc))) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण

		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (!rqi) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण

		/*
		 * Found IO that is still pending w/ firmware and beदीर्घs to
		 * the LUN that is under reset, अगर lr_sc != शून्य
		 */
		SNIC_SCSI_DBG(snic->shost, "Found IO in %s on LUN\n",
			      snic_ioreq_state_to_str(CMD_STATE(sc)));

		अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING) अणु
			spin_unlock_irqrestore(io_lock, flags);

			वापस 1;
		पूर्ण

		spin_unlock_irqrestore(io_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण /* end of snic_is_abts_pending */

अटल पूर्णांक
snic_dr_clean_single_req(काष्ठा snic *snic,
			 u32 tag,
			 काष्ठा scsi_device *lr_sdev)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_tgt *tgt = शून्य;
	काष्ठा scsi_cmnd *sc = शून्य;
	spinlock_t *io_lock = शून्य;
	u32 sv_state = 0, पंचांगf = 0;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	io_lock = snic_io_lock_tag(snic, tag);
	spin_lock_irqsave(io_lock, flags);
	sc = scsi_host_find_tag(snic->shost, tag);

	/* Ignore Cmd that करोn't beदीर्घ to Lun Reset device */
	अगर (!sc || sc->device != lr_sdev)
		जाओ skip_clean;

	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);

	अगर (!rqi)
		जाओ skip_clean;


	अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING)
		जाओ skip_clean;


	अगर ((CMD_FLAGS(sc) & SNIC_DEVICE_RESET) &&
			(!(CMD_FLAGS(sc) & SNIC_DEV_RST_ISSUED))) अणु

		SNIC_SCSI_DBG(snic->shost,
			      "clean_single_req: devrst is not pending sc 0x%p\n",
			      sc);

		जाओ skip_clean;
	पूर्ण

	SNIC_SCSI_DBG(snic->shost,
		"clean_single_req: Found IO in %s on lun\n",
		snic_ioreq_state_to_str(CMD_STATE(sc)));

	/* Save Command State */
	sv_state = CMD_STATE(sc);

	/*
	 * Any pending IO issued prior to reset is expected to be
	 * in abts pending state, अगर not we need to set SNIC_IOREQ_ABTS_PENDING
	 * to indicate the IO is पात pending.
	 * When IO is completed, the IO will be handed over and handled
	 * in this function.
	 */

	CMD_STATE(sc) = SNIC_IOREQ_ABTS_PENDING;
	SNIC_BUG_ON(rqi->abts_करोne);

	अगर (CMD_FLAGS(sc) & SNIC_DEVICE_RESET) अणु
		rqi->पंचांग_tag = SNIC_TAG_DEV_RST;

		SNIC_SCSI_DBG(snic->shost,
			      "clean_single_req:devrst sc 0x%p\n", sc);
	पूर्ण

	CMD_ABTS_STATUS(sc) = SNIC_INVALID_CODE;
	rqi->abts_करोne = &पंचांग_करोne;
	spin_unlock_irqrestore(io_lock, flags);

	tgt = starget_to_tgt(scsi_target(sc->device));
	अगर ((snic_tgt_chkपढ़ोy(tgt) != 0) && (tgt->tdata.typ == SNIC_TGT_SAN))
		पंचांगf = SNIC_ITMF_ABTS_TASK_TERM;
	अन्यथा
		पंचांगf = SNIC_ITMF_ABTS_TASK;

	/* Now queue the पात command to firmware */
	ret = snic_queue_पात_req(snic, rqi, sc, पंचांगf);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "clean_single_req_err:sc %p, tag %d abt failed. tm_tag %d flags 0x%llx\n",
			      sc, tag, rqi->पंचांग_tag, CMD_FLAGS(sc));

		spin_lock_irqsave(io_lock, flags);
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (rqi)
			rqi->abts_करोne = शून्य;

		/* Restore Command State */
		अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING)
			CMD_STATE(sc) = sv_state;

		ret = 1;
		जाओ skip_clean;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	अगर (CMD_FLAGS(sc) & SNIC_DEVICE_RESET)
		CMD_FLAGS(sc) |= SNIC_DEV_RST_TERM_ISSUED;

	CMD_FLAGS(sc) |= SNIC_IO_INTERNAL_TERM_ISSUED;
	spin_unlock_irqrestore(io_lock, flags);

	रुको_क्रम_completion_समयout(&पंचांग_करोne, SNIC_ABTS_TIMEOUT);

	/* Recheck cmd state to check अगर it now पातed. */
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi) अणु
		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_REQ_शून्य;
		जाओ skip_clean;
	पूर्ण
	rqi->abts_करोne = शून्य;

	/* अगर पात is still pending w/ fw, fail */
	अगर (CMD_ABTS_STATUS(sc) == SNIC_INVALID_CODE) अणु
		SNIC_HOST_ERR(snic->shost,
			      "clean_single_req_err:sc %p tag %d abt still pending w/ fw, tm_tag %d flags 0x%llx\n",
			      sc, tag, rqi->पंचांग_tag, CMD_FLAGS(sc));

		CMD_FLAGS(sc) |= SNIC_IO_ABTS_TERM_DONE;
		ret = 1;

		जाओ skip_clean;
	पूर्ण

	CMD_STATE(sc) = SNIC_IOREQ_ABTS_COMPLETE;
	CMD_SP(sc) = शून्य;
	spin_unlock_irqrestore(io_lock, flags);

	snic_release_req_buf(snic, rqi, sc);

	sc->result = (DID_ERROR << 16);
	sc->scsi_करोne(sc);

	ret = 0;

	वापस ret;

skip_clean:
	spin_unlock_irqrestore(io_lock, flags);

	वापस ret;
पूर्ण /* end of snic_dr_clean_single_req */

अटल पूर्णांक
snic_dr_clean_pending_req(काष्ठा snic *snic, काष्ठा scsi_cmnd *lr_sc)
अणु
	काष्ठा scsi_device *lr_sdev = lr_sc->device;
	u32 tag = 0;
	पूर्णांक ret = FAILED;

	क्रम (tag = 0; tag < snic->max_tag_id; tag++) अणु
		अगर (tag == snic_cmd_tag(lr_sc))
			जारी;

		ret = snic_dr_clean_single_req(snic, tag, lr_sdev);
		अगर (ret) अणु
			SNIC_HOST_ERR(snic->shost, "clean_err:tag = %d\n", tag);

			जाओ clean_err;
		पूर्ण
	पूर्ण

	schedule_समयout(msecs_to_jअगरfies(100));

	/* Walk through all the cmds and check abts status. */
	अगर (snic_is_abts_pending(snic, lr_sc)) अणु
		ret = FAILED;

		जाओ clean_err;
	पूर्ण

	ret = 0;
	SNIC_SCSI_DBG(snic->shost, "clean_pending_req: Success.\n");

	वापस ret;

clean_err:
	ret = FAILED;
	SNIC_HOST_ERR(snic->shost,
		      "Failed to Clean Pending IOs on %s device.\n",
		      dev_name(&lr_sdev->sdev_gendev));

	वापस ret;

पूर्ण /* end of snic_dr_clean_pending_req */

/*
 * snic_dr_finish : Called by snic_device_reset
 */
अटल पूर्णांक
snic_dr_finish(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक lr_res = 0;
	पूर्णांक ret = FAILED;

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi) अणु
		spin_unlock_irqrestore(io_lock, flags);
		SNIC_SCSI_DBG(snic->shost,
			      "dr_fini: rqi is null tag 0x%x sc 0x%p flags 0x%llx\n",
			      snic_cmd_tag(sc), sc, CMD_FLAGS(sc));

		ret = FAILED;
		जाओ dr_fini_end;
	पूर्ण

	rqi->dr_करोne = शून्य;

	lr_res = CMD_LR_STATUS(sc);

	चयन (lr_res) अणु
	हाल SNIC_INVALID_CODE:
		/* stats */
		SNIC_SCSI_DBG(snic->shost,
			      "dr_fini: Tag %x Dev Reset Timedout. flags 0x%llx\n",
			      snic_cmd_tag(sc), CMD_FLAGS(sc));

		CMD_FLAGS(sc) |= SNIC_DEV_RST_TIMEDOUT;
		ret = FAILED;

		जाओ dr_failed;

	हाल SNIC_STAT_IO_SUCCESS:
		SNIC_SCSI_DBG(snic->shost,
			      "dr_fini: Tag %x Dev Reset cmpl\n",
			      snic_cmd_tag(sc));
		ret = 0;
		अवरोध;

	शेष:
		SNIC_HOST_ERR(snic->shost,
			      "dr_fini:Device Reset completed& failed.Tag = %x lr_status %s flags 0x%llx\n",
			      snic_cmd_tag(sc),
			      snic_io_status_to_str(lr_res), CMD_FLAGS(sc));
		ret = FAILED;
		जाओ dr_failed;
	पूर्ण
	spin_unlock_irqrestore(io_lock, flags);

	/*
	 * Cleanup any IOs on this LUN that have still not completed.
	 * If any of these fail, then LUN Reset fails.
	 * Cleanup cleans all commands on this LUN except
	 * the lun reset command. If all cmds get cleaned, the LUN Reset
	 * succeeds.
	 */

	ret = snic_dr_clean_pending_req(snic, sc);
	अगर (ret) अणु
		spin_lock_irqsave(io_lock, flags);
		SNIC_SCSI_DBG(snic->shost,
			      "dr_fini: Device Reset Failed since could not abort all IOs. Tag = %x.\n",
			      snic_cmd_tag(sc));
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);

		जाओ dr_failed;
	पूर्ण अन्यथा अणु
		/* Cleanup LUN Reset Command */
		spin_lock_irqsave(io_lock, flags);
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (rqi)
			ret = SUCCESS; /* Completed Successfully */
		अन्यथा
			ret = FAILED;
	पूर्ण

dr_failed:
	lockdep_निश्चित_held(io_lock);
	अगर (rqi)
		CMD_SP(sc) = शून्य;
	spin_unlock_irqrestore(io_lock, flags);

	अगर (rqi)
		snic_release_req_buf(snic, rqi, sc);

dr_fini_end:
	वापस ret;
पूर्ण /* end of snic_dr_finish */

अटल पूर्णांक
snic_queue_dr_req(काष्ठा snic *snic,
		  काष्ठा snic_req_info *rqi,
		  काष्ठा scsi_cmnd *sc)
अणु
	/* Add special tag क्रम device reset */
	rqi->पंचांग_tag |= SNIC_TAG_DEV_RST;

	वापस snic_issue_पंचांग_req(snic, rqi, sc, SNIC_ITMF_LUN_RESET);
पूर्ण

अटल पूर्णांक
snic_send_dr_and_रुको(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	क्रमागत snic_ioreq_state sv_state;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	DECLARE_COMPLETION_ONSTACK(पंचांग_करोne);
	पूर्णांक ret = FAILED, tag = snic_cmd_tag(sc);

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	CMD_FLAGS(sc) |= SNIC_DEVICE_RESET;
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi) अणु
		SNIC_HOST_ERR(snic->shost,
			      "send_dr: rqi is null, Tag 0x%x flags 0x%llx\n",
			      tag, CMD_FLAGS(sc));
		spin_unlock_irqrestore(io_lock, flags);

		ret = FAILED;
		जाओ send_dr_end;
	पूर्ण

	/* Save Command state to restore in हाल Queuing failed. */
	sv_state = CMD_STATE(sc);

	CMD_STATE(sc) = SNIC_IOREQ_LR_PENDING;
	CMD_LR_STATUS(sc) = SNIC_INVALID_CODE;

	SNIC_SCSI_DBG(snic->shost, "dr: TAG = %x\n", tag);

	rqi->dr_करोne = &पंचांग_करोne;
	SNIC_BUG_ON(!rqi->dr_करोne);

	spin_unlock_irqrestore(io_lock, flags);
	/*
	 * The Command state is changed to IOREQ_PENDING,
	 * in this हाल, अगर the command is completed, the icmnd_cmpl will
	 * mark the cmd as completed.
	 * This logic still makes LUN Reset is inevitable.
	 */

	ret = snic_queue_dr_req(snic, rqi, sc);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "send_dr: IO w/ Tag 0x%x Failed err = %d. flags 0x%llx\n",
			      tag, ret, CMD_FLAGS(sc));

		spin_lock_irqsave(io_lock, flags);
		/* Restore State */
		CMD_STATE(sc) = sv_state;
		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (rqi)
			rqi->dr_करोne = शून्य;
		/* rqi is मुक्तd in caller. */
		spin_unlock_irqrestore(io_lock, flags);
		ret = FAILED;

		जाओ send_dr_end;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	CMD_FLAGS(sc) |= SNIC_DEV_RST_ISSUED;
	spin_unlock_irqrestore(io_lock, flags);

	ret = 0;

	रुको_क्रम_completion_समयout(&पंचांग_करोne, SNIC_LUN_RESET_TIMEOUT);

send_dr_end:
	वापस ret;
पूर्ण

/*
 * auxillary funciton to check lun reset op is supported or not
 * Not supported अगर वापसs 0
 */
अटल पूर्णांक
snic_dev_reset_supported(काष्ठा scsi_device *sdev)
अणु
	काष्ठा snic_tgt *tgt = starget_to_tgt(scsi_target(sdev));

	अगर (tgt->tdata.typ == SNIC_TGT_DAS)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम
snic_unlink_and_release_req(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc, पूर्णांक flag)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	u32 start_समय = jअगरfies;

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (rqi) अणु
		start_समय = rqi->start_समय;
		CMD_SP(sc) = शून्य;
	पूर्ण

	CMD_FLAGS(sc) |= flag;
	spin_unlock_irqrestore(io_lock, flags);

	अगर (rqi)
		snic_release_req_buf(snic, rqi, sc);

	SNIC_TRC(snic->shost->host_no, snic_cmd_tag(sc), (uदीर्घ) sc,
		 jअगरfies_to_msecs(jअगरfies - start_समय), (uदीर्घ) rqi,
		 SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));
पूर्ण

/*
 * SCSI Eh thपढ़ो issues a LUN Reset when one or more commands on a LUN
 * fail to get पातed. It calls driver's eh_device_reset with a SCSI
 * command on the LUN.
 */
पूर्णांक
snic_device_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा Scsi_Host *shost = sc->device->host;
	काष्ठा snic *snic = shost_priv(shost);
	काष्ठा snic_req_info *rqi = शून्य;
	पूर्णांक tag = snic_cmd_tag(sc);
	पूर्णांक start_समय = jअगरfies;
	पूर्णांक ret = FAILED;
	पूर्णांक dr_supp = 0;

	SNIC_SCSI_DBG(shost, "dev_reset:sc %p :0x%x :req = %p :tag = %d\n",
		      sc, sc->cmnd[0], sc->request,
		      snic_cmd_tag(sc));
	dr_supp = snic_dev_reset_supported(sc->device);
	अगर (!dr_supp) अणु
		/* device reset op is not supported */
		SNIC_HOST_INFO(shost, "LUN Reset Op not supported.\n");
		snic_unlink_and_release_req(snic, sc, SNIC_DEV_RST_NOTSUP);

		जाओ dev_rst_end;
	पूर्ण

	अगर (unlikely(snic_get_state(snic) != SNIC_ONLINE)) अणु
		snic_unlink_and_release_req(snic, sc, 0);
		SNIC_HOST_ERR(shost, "Devrst: Parent Devs are not online.\n");

		जाओ dev_rst_end;
	पूर्ण

	/* There is no tag when lun reset is issue through ioctl. */
	अगर (unlikely(tag <= SNIC_NO_TAG)) अणु
		SNIC_HOST_INFO(snic->shost,
			       "Devrst: LUN Reset Recvd thru IOCTL.\n");

		rqi = snic_req_init(snic, 0);
		अगर (!rqi)
			जाओ dev_rst_end;

		स_रखो(scsi_cmd_priv(sc), 0,
			माप(काष्ठा snic_पूर्णांकernal_io_state));
		CMD_SP(sc) = (अक्षर *)rqi;
		CMD_FLAGS(sc) = SNIC_NO_FLAGS;

		/* Add special tag क्रम dr coming from user spc */
		rqi->पंचांग_tag = SNIC_TAG_IOCTL_DEV_RST;
		rqi->sc = sc;
	पूर्ण

	ret = snic_send_dr_and_रुको(snic, sc);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Devrst: IO w/ Tag %x Failed w/ err = %d\n",
			      tag, ret);

		snic_unlink_and_release_req(snic, sc, 0);

		जाओ dev_rst_end;
	पूर्ण

	ret = snic_dr_finish(snic, sc);

dev_rst_end:
	SNIC_TRC(snic->shost->host_no, tag, (uदीर्घ) sc,
		 jअगरfies_to_msecs(jअगरfies - start_समय),
		 0, SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

	SNIC_SCSI_DBG(snic->shost,
		      "Devrst: Returning from Device Reset : %s\n",
		      (ret == SUCCESS) ? "SUCCESS" : "FAILED");

	वापस ret;
पूर्ण /* end of snic_device_reset */

/*
 * SCSI Error handling calls driver's eh_host_reset अगर all prior
 * error handling levels वापस FAILED.
 *
 * Host Reset is the highest level of error recovery. If this fails, then
 * host is offlined by SCSI.
 */
/*
 * snic_issue_hba_reset : Queues FW Reset Request.
 */
अटल पूर्णांक
snic_issue_hba_reset(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_host_req *req = शून्य;
	spinlock_t *io_lock = शून्य;
	DECLARE_COMPLETION_ONSTACK(रुको);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOMEM;

	rqi = snic_req_init(snic, 0);
	अगर (!rqi) अणु
		ret = -ENOMEM;

		जाओ hba_rst_end;
	पूर्ण

	अगर (snic_cmd_tag(sc) == SCSI_NO_TAG) अणु
		स_रखो(scsi_cmd_priv(sc), 0,
			माप(काष्ठा snic_पूर्णांकernal_io_state));
		SNIC_HOST_INFO(snic->shost, "issu_hr:Host reset thru ioctl.\n");
		rqi->sc = sc;
	पूर्ण

	req = rqi_to_req(rqi);

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	SNIC_BUG_ON(CMD_SP(sc) != शून्य);
	CMD_STATE(sc) = SNIC_IOREQ_PENDING;
	CMD_SP(sc) = (अक्षर *) rqi;
	CMD_FLAGS(sc) |= SNIC_IO_INITIALIZED;
	snic->हटाओ_रुको = &रुको;
	spin_unlock_irqrestore(io_lock, flags);

	/* Initialize Request */
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_HBA_RESET, 0, snic_cmd_tag(sc),
			snic->config.hid, 0, (uदीर्घ) rqi);

	req->u.reset.flags = 0;

	ret = snic_queue_wq_desc(snic, req, माप(*req));
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "issu_hr:Queuing HBA Reset Failed. w err %d\n",
			      ret);

		जाओ hba_rst_err;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	CMD_FLAGS(sc) |= SNIC_HOST_RESET_ISSUED;
	spin_unlock_irqrestore(io_lock, flags);
	atomic64_inc(&snic->s_stats.reset.hba_resets);
	SNIC_HOST_INFO(snic->shost, "Queued HBA Reset Successfully.\n");

	रुको_क्रम_completion_समयout(snic->हटाओ_रुको,
				    SNIC_HOST_RESET_TIMEOUT);

	अगर (snic_get_state(snic) == SNIC_FWRESET) अणु
		SNIC_HOST_ERR(snic->shost, "reset_cmpl: Reset Timedout.\n");
		ret = -ETIMEDOUT;

		जाओ hba_rst_err;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	snic->हटाओ_रुको = शून्य;
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	CMD_SP(sc) = शून्य;
	spin_unlock_irqrestore(io_lock, flags);

	अगर (rqi)
		snic_req_मुक्त(snic, rqi);

	ret = 0;

	वापस ret;

hba_rst_err:
	spin_lock_irqsave(io_lock, flags);
	snic->हटाओ_रुको = शून्य;
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	CMD_SP(sc) = शून्य;
	spin_unlock_irqrestore(io_lock, flags);

	अगर (rqi)
		snic_req_मुक्त(snic, rqi);

hba_rst_end:
	SNIC_HOST_ERR(snic->shost,
		      "reset:HBA Reset Failed w/ err = %d.\n",
		      ret);

	वापस ret;
पूर्ण /* end of snic_issue_hba_reset */

पूर्णांक
snic_reset(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic *snic = shost_priv(shost);
	क्रमागत snic_state sv_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = FAILED;

	/* Set snic state as SNIC_FWRESET*/
	sv_state = snic_get_state(snic);

	spin_lock_irqsave(&snic->snic_lock, flags);
	अगर (snic_get_state(snic) == SNIC_FWRESET) अणु
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		SNIC_HOST_INFO(shost, "reset:prev reset is in progres\n");

		msleep(SNIC_HOST_RESET_TIMEOUT);
		ret = SUCCESS;

		जाओ reset_end;
	पूर्ण

	snic_set_state(snic, SNIC_FWRESET);
	spin_unlock_irqrestore(&snic->snic_lock, flags);


	/* Wait क्रम all the IOs that are entered in Qcmd */
	जबतक (atomic_पढ़ो(&snic->ios_inflight))
		schedule_समयout(msecs_to_jअगरfies(1));

	ret = snic_issue_hba_reset(snic, sc);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "reset:Host Reset Failed w/ err %d.\n",
			      ret);
		spin_lock_irqsave(&snic->snic_lock, flags);
		snic_set_state(snic, sv_state);
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		atomic64_inc(&snic->s_stats.reset.hba_reset_fail);
		ret = FAILED;

		जाओ reset_end;
	पूर्ण

	ret = SUCCESS;

reset_end:
	वापस ret;
पूर्ण /* end of snic_reset */

/*
 * SCSI Error handling calls driver's eh_host_reset अगर all prior
 * error handling levels वापस FAILED.
 *
 * Host Reset is the highest level of error recovery. If this fails, then
 * host is offlined by SCSI.
 */
पूर्णांक
snic_host_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा Scsi_Host *shost = sc->device->host;
	u32 start_समय  = jअगरfies;
	पूर्णांक ret = FAILED;

	SNIC_SCSI_DBG(shost,
		      "host reset:sc %p sc_cmd 0x%x req %p tag %d flags 0x%llx\n",
		      sc, sc->cmnd[0], sc->request,
		      snic_cmd_tag(sc), CMD_FLAGS(sc));

	ret = snic_reset(shost, sc);

	SNIC_TRC(shost->host_no, snic_cmd_tag(sc), (uदीर्घ) sc,
		 jअगरfies_to_msecs(jअगरfies - start_समय),
		 0, SNIC_TRC_CMD(sc), SNIC_TRC_CMD_STATE_FLAGS(sc));

	वापस ret;
पूर्ण /* end of snic_host_reset */

/*
 * snic_cmpl_pending_पंचांगreq : Caller should hold io_lock
 */
अटल व्योम
snic_cmpl_pending_पंचांगreq(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा snic_req_info *rqi = शून्य;

	SNIC_SCSI_DBG(snic->shost,
		      "Completing Pending TM Req sc %p, state %s flags 0x%llx\n",
		      sc, snic_io_status_to_str(CMD_STATE(sc)), CMD_FLAGS(sc));

	/*
	 * CASE : FW didn't post iपंचांगf completion due to PCIe Errors.
	 * Marking the पात status as Success to call scsi completion
	 * in snic_पात_finish()
	 */
	CMD_ABTS_STATUS(sc) = SNIC_STAT_IO_SUCCESS;

	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi)
		वापस;

	अगर (rqi->dr_करोne)
		complete(rqi->dr_करोne);
	अन्यथा अगर (rqi->abts_करोne)
		complete(rqi->abts_करोne);
पूर्ण

/*
 * snic_scsi_cleanup: Walks through tag map and releases the reqs
 */
अटल व्योम
snic_scsi_cleanup(काष्ठा snic *snic, पूर्णांक ex_tag)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा scsi_cmnd *sc = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक tag;
	u64 st_समय = 0;

	SNIC_SCSI_DBG(snic->shost, "sc_clean: scsi cleanup.\n");

	क्रम (tag = 0; tag < snic->max_tag_id; tag++) अणु
		/* Skip ex_tag */
		अगर (tag == ex_tag)
			जारी;

		io_lock = snic_io_lock_tag(snic, tag);
		spin_lock_irqsave(io_lock, flags);
		sc = scsi_host_find_tag(snic->shost, tag);
		अगर (!sc) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण

		अगर (unlikely(snic_पंचांगreq_pending(sc))) अणु
			/*
			 * When FW Completes reset w/o sending completions
			 * क्रम outstanding ios.
			 */
			snic_cmpl_pending_पंचांगreq(snic, sc);
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण

		rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
		अगर (!rqi) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जाओ cleanup;
		पूर्ण

		SNIC_SCSI_DBG(snic->shost,
			      "sc_clean: sc %p, rqi %p, tag %d flags 0x%llx\n",
			      sc, rqi, tag, CMD_FLAGS(sc));

		CMD_SP(sc) = शून्य;
		CMD_FLAGS(sc) |= SNIC_SCSI_CLEANUP;
		spin_unlock_irqrestore(io_lock, flags);
		st_समय = rqi->start_समय;

		SNIC_HOST_INFO(snic->shost,
			       "sc_clean: Releasing rqi %p : flags 0x%llx\n",
			       rqi, CMD_FLAGS(sc));

		snic_release_req_buf(snic, rqi, sc);

cleanup:
		sc->result = DID_TRANSPORT_DISRUPTED << 16;
		SNIC_HOST_INFO(snic->shost,
			       "sc_clean: DID_TRANSPORT_DISRUPTED for sc %p, Tag %d flags 0x%llx rqi %p duration %u msecs\n",
			       sc, sc->request->tag, CMD_FLAGS(sc), rqi,
			       jअगरfies_to_msecs(jअगरfies - st_समय));

		/* Update IO stats */
		snic_stats_update_io_cmpl(&snic->s_stats);

		अगर (sc->scsi_करोne) अणु
			SNIC_TRC(snic->shost->host_no, tag, (uदीर्घ) sc,
				 jअगरfies_to_msecs(jअगरfies - st_समय), 0,
				 SNIC_TRC_CMD(sc),
				 SNIC_TRC_CMD_STATE_FLAGS(sc));

			sc->scsi_करोne(sc);
		पूर्ण
	पूर्ण
पूर्ण /* end of snic_scsi_cleanup */

व्योम
snic_shutकरोwn_scsi_cleanup(काष्ठा snic *snic)
अणु
	SNIC_HOST_INFO(snic->shost, "Shutdown time SCSI Cleanup.\n");

	snic_scsi_cleanup(snic, SCSI_NO_TAG);
पूर्ण /* end of snic_shutकरोwn_scsi_cleanup */

/*
 * snic_पूर्णांकernal_पात_io
 * called by : snic_tgt_scsi_पात_io
 */
अटल पूर्णांक
snic_पूर्णांकernal_पात_io(काष्ठा snic *snic, काष्ठा scsi_cmnd *sc, पूर्णांक पंचांगf)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	u32 sv_state = 0;
	पूर्णांक ret = 0;

	io_lock = snic_io_lock_hash(snic, sc);
	spin_lock_irqsave(io_lock, flags);
	rqi = (काष्ठा snic_req_info *) CMD_SP(sc);
	अगर (!rqi)
		जाओ skip_पूर्णांकernal_abts;

	अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING)
		जाओ skip_पूर्णांकernal_abts;

	अगर ((CMD_FLAGS(sc) & SNIC_DEVICE_RESET) &&
		(!(CMD_FLAGS(sc) & SNIC_DEV_RST_ISSUED))) अणु

		SNIC_SCSI_DBG(snic->shost,
			      "internal_abts: dev rst not pending sc 0x%p\n",
			      sc);

		जाओ skip_पूर्णांकernal_abts;
	पूर्ण


	अगर (!(CMD_FLAGS(sc) & SNIC_IO_ISSUED)) अणु
		SNIC_SCSI_DBG(snic->shost,
			"internal_abts: IO not yet issued sc 0x%p tag 0x%x flags 0x%llx state %d\n",
			sc, snic_cmd_tag(sc), CMD_FLAGS(sc), CMD_STATE(sc));

		जाओ skip_पूर्णांकernal_abts;
	पूर्ण

	sv_state = CMD_STATE(sc);
	CMD_STATE(sc) = SNIC_IOREQ_ABTS_PENDING;
	CMD_ABTS_STATUS(sc) = SNIC_INVALID_CODE;
	CMD_FLAGS(sc) |= SNIC_IO_INTERNAL_TERM_PENDING;

	अगर (CMD_FLAGS(sc) & SNIC_DEVICE_RESET) अणु
		/* stats */
		rqi->पंचांग_tag = SNIC_TAG_DEV_RST;
		SNIC_SCSI_DBG(snic->shost, "internal_abts:dev rst sc %p\n", sc);
	पूर्ण

	SNIC_SCSI_DBG(snic->shost, "internal_abts: Issuing abts tag %x\n",
		      snic_cmd_tag(sc));
	SNIC_BUG_ON(rqi->abts_करोne);
	spin_unlock_irqrestore(io_lock, flags);

	ret = snic_queue_पात_req(snic, rqi, sc, पंचांगf);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "internal_abts: Tag = %x , Failed w/ err = %d\n",
			      snic_cmd_tag(sc), ret);

		spin_lock_irqsave(io_lock, flags);

		अगर (CMD_STATE(sc) == SNIC_IOREQ_ABTS_PENDING)
			CMD_STATE(sc) = sv_state;

		जाओ skip_पूर्णांकernal_abts;
	पूर्ण

	spin_lock_irqsave(io_lock, flags);
	अगर (CMD_FLAGS(sc) & SNIC_DEVICE_RESET)
		CMD_FLAGS(sc) |= SNIC_DEV_RST_TERM_ISSUED;
	अन्यथा
		CMD_FLAGS(sc) |= SNIC_IO_INTERNAL_TERM_ISSUED;

	ret = SUCCESS;

skip_पूर्णांकernal_abts:
	lockdep_निश्चित_held(io_lock);
	spin_unlock_irqrestore(io_lock, flags);

	वापस ret;
पूर्ण /* end of snic_पूर्णांकernal_पात_io */

/*
 * snic_tgt_scsi_पात_io : called by snic_tgt_del
 */
पूर्णांक
snic_tgt_scsi_पात_io(काष्ठा snic_tgt *tgt)
अणु
	काष्ठा snic *snic = शून्य;
	काष्ठा scsi_cmnd *sc = शून्य;
	काष्ठा snic_tgt *sc_tgt = शून्य;
	spinlock_t *io_lock = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0, tag, abt_cnt = 0, पंचांगf = 0;

	अगर (!tgt)
		वापस -1;

	snic = shost_priv(snic_tgt_to_shost(tgt));
	SNIC_SCSI_DBG(snic->shost, "tgt_abt_io: Cleaning Pending IOs.\n");

	अगर (tgt->tdata.typ == SNIC_TGT_DAS)
		पंचांगf = SNIC_ITMF_ABTS_TASK;
	अन्यथा
		पंचांगf = SNIC_ITMF_ABTS_TASK_TERM;

	क्रम (tag = 0; tag < snic->max_tag_id; tag++) अणु
		io_lock = snic_io_lock_tag(snic, tag);

		spin_lock_irqsave(io_lock, flags);
		sc = scsi_host_find_tag(snic->shost, tag);
		अगर (!sc) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण

		sc_tgt = starget_to_tgt(scsi_target(sc->device));
		अगर (sc_tgt != tgt) अणु
			spin_unlock_irqrestore(io_lock, flags);

			जारी;
		पूर्ण
		spin_unlock_irqrestore(io_lock, flags);

		ret = snic_पूर्णांकernal_पात_io(snic, sc, पंचांगf);
		अगर (ret < 0) अणु
			SNIC_HOST_ERR(snic->shost,
				      "tgt_abt_io: Tag %x, Failed w err = %d\n",
				      tag, ret);

			जारी;
		पूर्ण

		अगर (ret == SUCCESS)
			abt_cnt++;
	पूर्ण

	SNIC_SCSI_DBG(snic->shost, "tgt_abt_io: abt_cnt = %d\n", abt_cnt);

	वापस 0;
पूर्ण /* end of snic_tgt_scsi_पात_io */
