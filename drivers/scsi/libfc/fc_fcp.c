<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 * Copyright(c) 2008 Red Hat, Inc.  All rights reserved.
 * Copyright(c) 2008 Mike Christie
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/err.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश <scsi/fc/fc_fc2.h>

#समावेश <scsi/libfc.h>

#समावेश "fc_encode.h"
#समावेश "fc_libfc.h"

अटल काष्ठा kmem_cache *scsi_pkt_cachep;

/* SRB state definitions */
#घोषणा FC_SRB_FREE		0		/* cmd is मुक्त */
#घोषणा FC_SRB_CMD_SENT		(1 << 0)	/* cmd has been sent */
#घोषणा FC_SRB_RCV_STATUS	(1 << 1)	/* response has arrived */
#घोषणा FC_SRB_ABORT_PENDING	(1 << 2)	/* cmd पात sent to device */
#घोषणा FC_SRB_ABORTED		(1 << 3)	/* पात acknowledged */
#घोषणा FC_SRB_DISCONTIG	(1 << 4)	/* non-sequential data recvd */
#घोषणा FC_SRB_COMPL		(1 << 5)	/* fc_io_compl has been run */
#घोषणा FC_SRB_FCP_PROCESSING_TMO (1 << 6)	/* समयr function processing */

#घोषणा FC_SRB_READ		(1 << 1)
#घोषणा FC_SRB_WRITE		(1 << 0)

/*
 * The SCp.ptr should be tested and set under the scsi_pkt_queue lock
 */
#घोषणा CMD_SP(Cmnd)		    ((काष्ठा fc_fcp_pkt *)(Cmnd)->SCp.ptr)
#घोषणा CMD_ENTRY_STATUS(Cmnd)	    ((Cmnd)->SCp.have_data_in)
#घोषणा CMD_COMPL_STATUS(Cmnd)	    ((Cmnd)->SCp.this_residual)
#घोषणा CMD_SCSI_STATUS(Cmnd)	    ((Cmnd)->SCp.Status)
#घोषणा CMD_RESID_LEN(Cmnd)	    ((Cmnd)->SCp.buffers_residual)

/**
 * काष्ठा fc_fcp_पूर्णांकernal - FCP layer पूर्णांकernal data
 * @scsi_pkt_pool: Memory pool to draw FCP packets from
 * @scsi_queue_lock: Protects the scsi_pkt_queue
 * @scsi_pkt_queue: Current FCP packets
 * @last_can_queue_ramp_करोwn_समय: ramp करोwn समय
 * @last_can_queue_ramp_up_समय: ramp up समय
 * @max_can_queue: max can_queue size
 */
काष्ठा fc_fcp_पूर्णांकernal अणु
	mempool_t		*scsi_pkt_pool;
	spinlock_t		scsi_queue_lock;
	काष्ठा list_head	scsi_pkt_queue;
	अचिन्हित दीर्घ		last_can_queue_ramp_करोwn_समय;
	अचिन्हित दीर्घ		last_can_queue_ramp_up_समय;
	पूर्णांक			max_can_queue;
पूर्ण;

#घोषणा fc_get_scsi_पूर्णांकernal(x)	((काष्ठा fc_fcp_पूर्णांकernal *)(x)->scsi_priv)

/*
 * function prototypes
 * FC scsi I/O related functions
 */
अटल व्योम fc_fcp_recv_data(काष्ठा fc_fcp_pkt *, काष्ठा fc_frame *);
अटल व्योम fc_fcp_recv(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
अटल व्योम fc_fcp_resp(काष्ठा fc_fcp_pkt *, काष्ठा fc_frame *);
अटल व्योम fc_fcp_complete_locked(काष्ठा fc_fcp_pkt *);
अटल व्योम fc_पंचांग_करोne(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
अटल व्योम fc_fcp_error(काष्ठा fc_fcp_pkt *, काष्ठा fc_frame *);
अटल व्योम fc_fcp_recovery(काष्ठा fc_fcp_pkt *, u8 code);
अटल व्योम fc_fcp_समयout(काष्ठा समयr_list *);
अटल व्योम fc_fcp_rec(काष्ठा fc_fcp_pkt *);
अटल व्योम fc_fcp_rec_error(काष्ठा fc_fcp_pkt *, काष्ठा fc_frame *);
अटल व्योम fc_fcp_rec_resp(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
अटल व्योम fc_io_compl(काष्ठा fc_fcp_pkt *);

अटल व्योम fc_fcp_srr(काष्ठा fc_fcp_pkt *, क्रमागत fc_rctl, u32);
अटल व्योम fc_fcp_srr_resp(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
अटल व्योम fc_fcp_srr_error(काष्ठा fc_fcp_pkt *, काष्ठा fc_frame *);

/*
 * command status codes
 */
#घोषणा FC_COMPLETE		0
#घोषणा FC_CMD_ABORTED		1
#घोषणा FC_CMD_RESET		2
#घोषणा FC_CMD_PLOGO		3
#घोषणा FC_SNS_RCV		4
#घोषणा FC_TRANS_ERR		5
#घोषणा FC_DATA_OVRRUN		6
#घोषणा FC_DATA_UNDRUN		7
#घोषणा FC_ERROR		8
#घोषणा FC_HRD_ERROR		9
#घोषणा FC_CRC_ERROR		10
#घोषणा FC_TIMED_OUT		11
#घोषणा FC_TRANS_RESET		12

/*
 * Error recovery समयout values.
 */
#घोषणा FC_SCSI_TM_TOV		(10 * HZ)
#घोषणा FC_HOST_RESET_TIMEOUT	(30 * HZ)
#घोषणा FC_CAN_QUEUE_PERIOD	(60 * HZ)

#घोषणा FC_MAX_ERROR_CNT	5
#घोषणा FC_MAX_RECOV_RETRY	3

#घोषणा FC_FCP_DFLT_QUEUE_DEPTH 32

/**
 * fc_fcp_pkt_alloc() - Allocate a fcp_pkt
 * @lport: The local port that the FCP packet is क्रम
 * @gfp:   GFP flags क्रम allocation
 *
 * Return value: fcp_pkt काष्ठाure or null on allocation failure.
 * Context:	 Can be called from process context, no lock is required.
 */
अटल काष्ठा fc_fcp_pkt *fc_fcp_pkt_alloc(काष्ठा fc_lport *lport, gfp_t gfp)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);
	काष्ठा fc_fcp_pkt *fsp;

	fsp = mempool_alloc(si->scsi_pkt_pool, gfp);
	अगर (fsp) अणु
		स_रखो(fsp, 0, माप(*fsp));
		fsp->lp = lport;
		fsp->xfer_ddp = FC_XID_UNKNOWN;
		refcount_set(&fsp->ref_cnt, 1);
		समयr_setup(&fsp->समयr, शून्य, 0);
		INIT_LIST_HEAD(&fsp->list);
		spin_lock_init(&fsp->scsi_pkt_lock);
	पूर्ण अन्यथा अणु
		per_cpu_ptr(lport->stats, get_cpu())->FcpPktAllocFails++;
		put_cpu();
	पूर्ण
	वापस fsp;
पूर्ण

/**
 * fc_fcp_pkt_release() - Release hold on a fcp_pkt
 * @fsp: The FCP packet to be released
 *
 * Context: Can be called from process or पूर्णांकerrupt context,
 *	    no lock is required.
 */
अटल व्योम fc_fcp_pkt_release(काष्ठा fc_fcp_pkt *fsp)
अणु
	अगर (refcount_dec_and_test(&fsp->ref_cnt)) अणु
		काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(fsp->lp);

		mempool_मुक्त(fsp, si->scsi_pkt_pool);
	पूर्ण
पूर्ण

/**
 * fc_fcp_pkt_hold() - Hold a fcp_pkt
 * @fsp: The FCP packet to be held
 */
अटल व्योम fc_fcp_pkt_hold(काष्ठा fc_fcp_pkt *fsp)
अणु
	refcount_inc(&fsp->ref_cnt);
पूर्ण

/**
 * fc_fcp_pkt_destroy() - Release hold on a fcp_pkt
 * @seq: The sequence that the FCP packet is on (required by deकाष्ठाor API)
 * @fsp: The FCP packet to be released
 *
 * This routine is called by a deकाष्ठाor callback in the fc_exch_seq_send()
 * routine of the libfc Transport Template. The 'struct fc_seq' is a required
 * argument even though it is not used by this routine.
 *
 * Context: No locking required.
 */
अटल व्योम fc_fcp_pkt_destroy(काष्ठा fc_seq *seq, व्योम *fsp)
अणु
	fc_fcp_pkt_release(fsp);
पूर्ण

/**
 * fc_fcp_lock_pkt() - Lock a fcp_pkt and increase its reference count
 * @fsp: The FCP packet to be locked and incremented
 *
 * We should only वापस error अगर we वापस a command to SCSI-ml beक्रमe
 * getting a response. This can happen in हालs where we send a पात, but
 * करो not रुको क्रम the response and the पात and command can be passing
 * each other on the wire/network-layer.
 *
 * Note: this function locks the packet and माला_लो a reference to allow
 * callers to call the completion function जबतक the lock is held and
 * not have to worry about the packets refcount.
 *
 * TODO: Maybe we should just have callers grab/release the lock and
 * have a function that they call to verअगरy the fsp and grab a ref अगर
 * needed.
 */
अटल अंतरभूत पूर्णांक fc_fcp_lock_pkt(काष्ठा fc_fcp_pkt *fsp)
अणु
	spin_lock_bh(&fsp->scsi_pkt_lock);
	अगर (fsp->state & FC_SRB_COMPL) अणु
		spin_unlock_bh(&fsp->scsi_pkt_lock);
		वापस -EPERM;
	पूर्ण

	fc_fcp_pkt_hold(fsp);
	वापस 0;
पूर्ण

/**
 * fc_fcp_unlock_pkt() - Release a fcp_pkt's lock and decrement its
 *			 reference count
 * @fsp: The FCP packet to be unlocked and decremented
 */
अटल अंतरभूत व्योम fc_fcp_unlock_pkt(काष्ठा fc_fcp_pkt *fsp)
अणु
	spin_unlock_bh(&fsp->scsi_pkt_lock);
	fc_fcp_pkt_release(fsp);
पूर्ण

/**
 * fc_fcp_समयr_set() - Start a समयr क्रम a fcp_pkt
 * @fsp:   The FCP packet to start a समयr क्रम
 * @delay: The समयout period in jअगरfies
 */
अटल व्योम fc_fcp_समयr_set(काष्ठा fc_fcp_pkt *fsp, अचिन्हित दीर्घ delay)
अणु
	अगर (!(fsp->state & FC_SRB_COMPL)) अणु
		mod_समयr(&fsp->समयr, jअगरfies + delay);
		fsp->समयr_delay = delay;
	पूर्ण
पूर्ण

अटल व्योम fc_fcp_पात_करोne(काष्ठा fc_fcp_pkt *fsp)
अणु
	fsp->state |= FC_SRB_ABORTED;
	fsp->state &= ~FC_SRB_ABORT_PENDING;

	अगर (fsp->रुको_क्रम_comp)
		complete(&fsp->पंचांग_करोne);
	अन्यथा
		fc_fcp_complete_locked(fsp);
पूर्ण

/**
 * fc_fcp_send_पात() - Send an पात क्रम exchanges associated with a
 *			 fcp_pkt
 * @fsp: The FCP packet to पात exchanges on
 */
अटल पूर्णांक fc_fcp_send_पात(काष्ठा fc_fcp_pkt *fsp)
अणु
	पूर्णांक rc;

	अगर (!fsp->seq_ptr)
		वापस -EINVAL;

	per_cpu_ptr(fsp->lp->stats, get_cpu())->FcpPktAborts++;
	put_cpu();

	fsp->state |= FC_SRB_ABORT_PENDING;
	rc = fc_seq_exch_पात(fsp->seq_ptr, 0);
	/*
	 * fc_seq_exch_पात() might वापस -ENXIO अगर
	 * the sequence is alपढ़ोy completed
	 */
	अगर (rc == -ENXIO) अणु
		fc_fcp_पात_करोne(fsp);
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * fc_fcp_retry_cmd() - Retry a fcp_pkt
 * @fsp: The FCP packet to be retried
 * @status_code: The FCP status code to set
 *
 * Sets the status code to be FC_ERROR and then calls
 * fc_fcp_complete_locked() which in turn calls fc_io_compl().
 * fc_io_compl() will notअगरy the SCSI-ml that the I/O is करोne.
 * The SCSI-ml will retry the command.
 */
अटल व्योम fc_fcp_retry_cmd(काष्ठा fc_fcp_pkt *fsp, पूर्णांक status_code)
अणु
	अगर (fsp->seq_ptr) अणु
		fc_exch_करोne(fsp->seq_ptr);
		fsp->seq_ptr = शून्य;
	पूर्ण

	fsp->state &= ~FC_SRB_ABORT_PENDING;
	fsp->io_status = 0;
	fsp->status_code = status_code;
	fc_fcp_complete_locked(fsp);
पूर्ण

/**
 * fc_fcp_ddp_setup() - Calls a LLD's ddp_setup routine to set up DDP context
 * @fsp: The FCP packet that will manage the DDP frames
 * @xid: The XID that will be used क्रम the DDP exchange
 */
व्योम fc_fcp_ddp_setup(काष्ठा fc_fcp_pkt *fsp, u16 xid)
अणु
	काष्ठा fc_lport *lport;

	lport = fsp->lp;
	अगर ((fsp->req_flags & FC_SRB_READ) &&
	    (lport->lro_enabled) && (lport->tt.ddp_setup)) अणु
		अगर (lport->tt.ddp_setup(lport, xid, scsi_sglist(fsp->cmd),
					scsi_sg_count(fsp->cmd)))
			fsp->xfer_ddp = xid;
	पूर्ण
पूर्ण

/**
 * fc_fcp_ddp_करोne() - Calls a LLD's ddp_करोne routine to release any
 *		       DDP related resources क्रम a fcp_pkt
 * @fsp: The FCP packet that DDP had been used on
 */
व्योम fc_fcp_ddp_करोne(काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_lport *lport;

	अगर (!fsp)
		वापस;

	अगर (fsp->xfer_ddp == FC_XID_UNKNOWN)
		वापस;

	lport = fsp->lp;
	अगर (lport->tt.ddp_करोne) अणु
		fsp->xfer_len = lport->tt.ddp_करोne(lport, fsp->xfer_ddp);
		fsp->xfer_ddp = FC_XID_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * fc_fcp_can_queue_ramp_up() - increases can_queue
 * @lport: lport to ramp up can_queue
 */
अटल व्योम fc_fcp_can_queue_ramp_up(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);
	अचिन्हित दीर्घ flags;
	पूर्णांक can_queue;

	spin_lock_irqsave(lport->host->host_lock, flags);

	अगर (si->last_can_queue_ramp_up_समय &&
	    (समय_beक्रमe(jअगरfies, si->last_can_queue_ramp_up_समय +
			 FC_CAN_QUEUE_PERIOD)))
		जाओ unlock;

	अगर (समय_beक्रमe(jअगरfies, si->last_can_queue_ramp_करोwn_समय +
			FC_CAN_QUEUE_PERIOD))
		जाओ unlock;

	si->last_can_queue_ramp_up_समय = jअगरfies;

	can_queue = lport->host->can_queue << 1;
	अगर (can_queue >= si->max_can_queue) अणु
		can_queue = si->max_can_queue;
		si->last_can_queue_ramp_करोwn_समय = 0;
	पूर्ण
	lport->host->can_queue = can_queue;
	shost_prपूर्णांकk(KERN_ERR, lport->host, "libfc: increased "
		     "can_queue to %d.\n", can_queue);

unlock:
	spin_unlock_irqrestore(lport->host->host_lock, flags);
पूर्ण

/**
 * fc_fcp_can_queue_ramp_करोwn() - reduces can_queue
 * @lport: lport to reduce can_queue
 *
 * If we are getting memory allocation failures, then we may
 * be trying to execute too many commands. We let the running
 * commands complete or समयout, then try again with a reduced
 * can_queue. Eventually we will hit the poपूर्णांक where we run
 * on all reserved काष्ठाs.
 */
अटल bool fc_fcp_can_queue_ramp_करोwn(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);
	अचिन्हित दीर्घ flags;
	पूर्णांक can_queue;
	bool changed = false;

	spin_lock_irqsave(lport->host->host_lock, flags);

	अगर (si->last_can_queue_ramp_करोwn_समय &&
	    (समय_beक्रमe(jअगरfies, si->last_can_queue_ramp_करोwn_समय +
			 FC_CAN_QUEUE_PERIOD)))
		जाओ unlock;

	si->last_can_queue_ramp_करोwn_समय = jअगरfies;

	can_queue = lport->host->can_queue;
	can_queue >>= 1;
	अगर (!can_queue)
		can_queue = 1;
	lport->host->can_queue = can_queue;
	changed = true;

unlock:
	spin_unlock_irqrestore(lport->host->host_lock, flags);
	वापस changed;
पूर्ण

/*
 * fc_fcp_frame_alloc() -  Allocates fc_frame काष्ठाure and buffer.
 * @lport:	fc lport काष्ठा
 * @len:	payload length
 *
 * Allocates fc_frame काष्ठाure and buffer but अगर fails to allocate
 * then reduce can_queue.
 */
अटल अंतरभूत काष्ठा fc_frame *fc_fcp_frame_alloc(काष्ठा fc_lport *lport,
						  माप_प्रकार len)
अणु
	काष्ठा fc_frame *fp;

	fp = fc_frame_alloc(lport, len);
	अगर (likely(fp))
		वापस fp;

	per_cpu_ptr(lport->stats, get_cpu())->FcpFrameAllocFails++;
	put_cpu();
	/* error हाल */
	fc_fcp_can_queue_ramp_करोwn(lport);
	shost_prपूर्णांकk(KERN_ERR, lport->host,
		     "libfc: Could not allocate frame, "
		     "reducing can_queue to %d.\n", lport->host->can_queue);
	वापस शून्य;
पूर्ण

/**
 * get_fsp_rec_tov() - Helper function to get REC_TOV
 * @fsp: the FCP packet
 *
 * Returns rec tov in jअगरfies as rpriv->e_d_tov + 1 second
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_fsp_rec_tov(काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_rport_libfc_priv *rpriv = fsp->rport->dd_data;
	अचिन्हित पूर्णांक e_d_tov = FC_DEF_E_D_TOV;

	अगर (rpriv && rpriv->e_d_tov > e_d_tov)
		e_d_tov = rpriv->e_d_tov;
	वापस msecs_to_jअगरfies(e_d_tov) + HZ;
पूर्ण

/**
 * fc_fcp_recv_data() - Handler क्रम receiving SCSI-FCP data from a target
 * @fsp: The FCP packet the data is on
 * @fp:	 The data frame
 */
अटल व्योम fc_fcp_recv_data(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	काष्ठा scsi_cmnd *sc = fsp->cmd;
	काष्ठा fc_lport *lport = fsp->lp;
	काष्ठा fc_stats *stats;
	काष्ठा fc_frame_header *fh;
	माप_प्रकार start_offset;
	माप_प्रकार offset;
	u32 crc;
	u32 copy_len = 0;
	माप_प्रकार len;
	व्योम *buf;
	काष्ठा scatterlist *sg;
	u32 nents;
	u8 host_bcode = FC_COMPLETE;

	fh = fc_frame_header_get(fp);
	offset = ntohl(fh->fh_parm_offset);
	start_offset = offset;
	len = fr_len(fp) - माप(*fh);
	buf = fc_frame_payload_get(fp, 0);

	/*
	 * अगर this I/O is ddped then clear it and initiate recovery since data
	 * frames are expected to be placed directly in that हाल.
	 *
	 * Indicate error to scsi-ml because something went wrong with the
	 * ddp handling to get us here.
	 */
	अगर (fsp->xfer_ddp != FC_XID_UNKNOWN) अणु
		fc_fcp_ddp_करोne(fsp);
		FC_FCP_DBG(fsp, "DDP I/O in fc_fcp_recv_data set ERROR\n");
		host_bcode = FC_ERROR;
		जाओ err;
	पूर्ण
	अगर (offset + len > fsp->data_len) अणु
		/* this should never happen */
		अगर ((fr_flags(fp) & FCPHF_CRC_UNCHECKED) &&
		    fc_frame_crc_check(fp))
			जाओ crc_err;
		FC_FCP_DBG(fsp, "data received past end. len %zx offset %zx "
			   "data_len %x\n", len, offset, fsp->data_len);

		/* Data is corrupted indicate scsi-ml should retry */
		host_bcode = FC_DATA_OVRRUN;
		जाओ err;
	पूर्ण
	अगर (offset != fsp->xfer_len)
		fsp->state |= FC_SRB_DISCONTIG;

	sg = scsi_sglist(sc);
	nents = scsi_sg_count(sc);

	अगर (!(fr_flags(fp) & FCPHF_CRC_UNCHECKED)) अणु
		copy_len = fc_copy_buffer_to_sglist(buf, len, sg, &nents,
						    &offset, शून्य);
	पूर्ण अन्यथा अणु
		crc = crc32(~0, (u8 *) fh, माप(*fh));
		copy_len = fc_copy_buffer_to_sglist(buf, len, sg, &nents,
						    &offset, &crc);
		buf = fc_frame_payload_get(fp, 0);
		अगर (len % 4)
			crc = crc32(crc, buf + len, 4 - (len % 4));

		अगर (~crc != le32_to_cpu(fr_crc(fp))) अणु
crc_err:
			stats = per_cpu_ptr(lport->stats, get_cpu());
			stats->ErrorFrames++;
			/* per cpu count, not total count, but OK क्रम limit */
			अगर (stats->InvalidCRCCount++ < FC_MAX_ERROR_CNT)
				prपूर्णांकk(KERN_WARNING "libfc: CRC error on data "
				       "frame for port (%6.6x)\n",
				       lport->port_id);
			put_cpu();
			/*
			 * Assume the frame is total garbage.
			 * We may have copied it over the good part
			 * of the buffer.
			 * If so, we need to retry the entire operation.
			 * Otherwise, ignore it.
			 */
			अगर (fsp->state & FC_SRB_DISCONTIG) अणु
				host_bcode = FC_CRC_ERROR;
				जाओ err;
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	अगर (fsp->xfer_contig_end == start_offset)
		fsp->xfer_contig_end += copy_len;
	fsp->xfer_len += copy_len;

	/*
	 * In the very rare event that this data arrived after the response
	 * and completes the transfer, call the completion handler.
	 */
	अगर (unlikely(fsp->state & FC_SRB_RCV_STATUS) &&
	    fsp->xfer_len == fsp->data_len - fsp->scsi_resid) अणु
		FC_FCP_DBG( fsp, "complete out-of-order sequence\n" );
		fc_fcp_complete_locked(fsp);
	पूर्ण
	वापस;
err:
	fc_fcp_recovery(fsp, host_bcode);
पूर्ण

/**
 * fc_fcp_send_data() - Send SCSI data to a target
 * @fsp:      The FCP packet the data is on
 * @seq:      The sequence the data is to be sent on
 * @offset:   The starting offset क्रम this data request
 * @seq_blen: The burst length क्रम this data request
 *
 * Called after receiving a Transfer Ready data descriptor.
 * If the LLD is capable of sequence offload then send करोwn the
 * seq_blen amount of data in single frame, otherwise send
 * multiple frames of the maximum frame payload supported by
 * the target port.
 */
अटल पूर्णांक fc_fcp_send_data(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_seq *seq,
			    माप_प्रकार offset, माप_प्रकार seq_blen)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा scsi_cmnd *sc;
	काष्ठा scatterlist *sg;
	काष्ठा fc_frame *fp = शून्य;
	काष्ठा fc_lport *lport = fsp->lp;
	काष्ठा page *page;
	माप_प्रकार reमुख्यing;
	माप_प्रकार t_blen;
	माप_प्रकार tlen;
	माप_प्रकार sg_bytes;
	माप_प्रकार frame_offset, fh_parm_offset;
	माप_प्रकार off;
	पूर्णांक error;
	व्योम *data = शून्य;
	व्योम *page_addr;
	पूर्णांक using_sg = lport->sg_supp;
	u32 f_ctl;

	WARN_ON(seq_blen <= 0);
	अगर (unlikely(offset + seq_blen > fsp->data_len)) अणु
		/* this should never happen */
		FC_FCP_DBG(fsp, "xfer-ready past end. seq_blen %zx "
			   "offset %zx\n", seq_blen, offset);
		fc_fcp_send_पात(fsp);
		वापस 0;
	पूर्ण अन्यथा अगर (offset != fsp->xfer_len) अणु
		/* Out of Order Data Request - no problem, but unexpected. */
		FC_FCP_DBG(fsp, "xfer-ready non-contiguous. "
			   "seq_blen %zx offset %zx\n", seq_blen, offset);
	पूर्ण

	/*
	 * अगर LLD is capable of seq_offload then set transport
	 * burst length (t_blen) to seq_blen, otherwise set t_blen
	 * to max FC frame payload previously set in fsp->max_payload.
	 */
	t_blen = fsp->max_payload;
	अगर (lport->seq_offload) अणु
		t_blen = min(seq_blen, (माप_प्रकार)lport->lso_max);
		FC_FCP_DBG(fsp, "fsp=%p:lso:blen=%zx lso_max=0x%x t_blen=%zx\n",
			   fsp, seq_blen, lport->lso_max, t_blen);
	पूर्ण

	अगर (t_blen > 512)
		t_blen &= ~(512 - 1);	/* round करोwn to block size */
	sc = fsp->cmd;

	reमुख्यing = seq_blen;
	fh_parm_offset = frame_offset = offset;
	tlen = 0;
	seq = fc_seq_start_next(seq);
	f_ctl = FC_FC_REL_OFF;
	WARN_ON(!seq);

	sg = scsi_sglist(sc);

	जबतक (reमुख्यing > 0 && sg) अणु
		अगर (offset >= sg->length) अणु
			offset -= sg->length;
			sg = sg_next(sg);
			जारी;
		पूर्ण
		अगर (!fp) अणु
			tlen = min(t_blen, reमुख्यing);

			/*
			 * TODO.  Temporary workaround.	 fc_seq_send() can't
			 * handle odd lengths in non-linear skbs.
			 * This will be the final fragment only.
			 */
			अगर (tlen % 4)
				using_sg = 0;
			fp = fc_frame_alloc(lport, using_sg ? 0 : tlen);
			अगर (!fp)
				वापस -ENOMEM;

			data = fc_frame_header_get(fp) + 1;
			fh_parm_offset = frame_offset;
			fr_max_payload(fp) = fsp->max_payload;
		पूर्ण

		off = offset + sg->offset;
		sg_bytes = min(tlen, sg->length - offset);
		sg_bytes = min(sg_bytes,
			       (माप_प्रकार) (PAGE_SIZE - (off & ~PAGE_MASK)));
		page = sg_page(sg) + (off >> PAGE_SHIFT);
		अगर (using_sg) अणु
			get_page(page);
			skb_fill_page_desc(fp_skb(fp),
					   skb_shinfo(fp_skb(fp))->nr_frags,
					   page, off & ~PAGE_MASK, sg_bytes);
			fp_skb(fp)->data_len += sg_bytes;
			fr_len(fp) += sg_bytes;
			fp_skb(fp)->truesize += PAGE_SIZE;
		पूर्ण अन्यथा अणु
			/*
			 * The scatterlist item may be bigger than PAGE_SIZE,
			 * but we must not cross pages inside the kmap.
			 */
			page_addr = kmap_atomic(page);
			स_नकल(data, (अक्षर *)page_addr + (off & ~PAGE_MASK),
			       sg_bytes);
			kunmap_atomic(page_addr);
			data += sg_bytes;
		पूर्ण
		offset += sg_bytes;
		frame_offset += sg_bytes;
		tlen -= sg_bytes;
		reमुख्यing -= sg_bytes;

		अगर ((skb_shinfo(fp_skb(fp))->nr_frags < FC_FRAME_SG_LEN) &&
		    (tlen))
			जारी;

		/*
		 * Send sequence with transfer sequence initiative in हाल
		 * this is last FCP frame of the sequence.
		 */
		अगर (reमुख्यing == 0)
			f_ctl |= FC_FC_SEQ_INIT | FC_FC_END_SEQ;

		ep = fc_seq_exch(seq);
		fc_fill_fc_hdr(fp, FC_RCTL_DD_SOL_DATA, ep->did, ep->sid,
			       FC_TYPE_FCP, f_ctl, fh_parm_offset);

		/*
		 * send fragment using क्रम a sequence.
		 */
		error = fc_seq_send(lport, seq, fp);
		अगर (error) अणु
			WARN_ON(1);		/* send error should be rare */
			वापस error;
		पूर्ण
		fp = शून्य;
	पूर्ण
	fsp->xfer_len += seq_blen;	/* premature count? */
	वापस 0;
पूर्ण

/**
 * fc_fcp_abts_resp() - Receive an ABTS response
 * @fsp: The FCP packet that is being पातed
 * @fp:	 The response frame
 */
अटल व्योम fc_fcp_abts_resp(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	पूर्णांक ba_करोne = 1;
	काष्ठा fc_ba_rjt *brp;
	काष्ठा fc_frame_header *fh;

	fh = fc_frame_header_get(fp);
	चयन (fh->fh_r_ctl) अणु
	हाल FC_RCTL_BA_ACC:
		अवरोध;
	हाल FC_RCTL_BA_RJT:
		brp = fc_frame_payload_get(fp, माप(*brp));
		अगर (brp && brp->br_reason == FC_BA_RJT_LOG_ERR)
			अवरोध;
		fallthrough;
	शेष:
		/*
		 * we will let the command समयout
		 * and scsi-ml recover in this हाल,
		 * thereक्रमe cleared the ba_करोne flag.
		 */
		ba_करोne = 0;
	पूर्ण

	अगर (ba_करोne)
		fc_fcp_पात_करोne(fsp);
पूर्ण

/**
 * fc_fcp_recv() - Receive an FCP frame
 * @seq: The sequence the frame is on
 * @fp:	 The received frame
 * @arg: The related FCP packet
 *
 * Context: Called from Soft IRQ context. Can not be called
 *	    holding the FCP packet list lock.
 */
अटल व्योम fc_fcp_recv(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_fcp_pkt *fsp = (काष्ठा fc_fcp_pkt *)arg;
	काष्ठा fc_lport *lport = fsp->lp;
	काष्ठा fc_frame_header *fh;
	काष्ठा fcp_txrdy *dd;
	u8 r_ctl;
	पूर्णांक rc = 0;

	अगर (IS_ERR(fp)) अणु
		fc_fcp_error(fsp, fp);
		वापस;
	पूर्ण

	fh = fc_frame_header_get(fp);
	r_ctl = fh->fh_r_ctl;

	अगर (lport->state != LPORT_ST_READY) अणु
		FC_FCP_DBG(fsp, "lport state %d, ignoring r_ctl %x\n",
			   lport->state, r_ctl);
		जाओ out;
	पूर्ण
	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;

	अगर (fh->fh_type == FC_TYPE_BLS) अणु
		fc_fcp_abts_resp(fsp, fp);
		जाओ unlock;
	पूर्ण

	अगर (fsp->state & (FC_SRB_ABORTED | FC_SRB_ABORT_PENDING)) अणु
		FC_FCP_DBG(fsp, "command aborted, ignoring r_ctl %x\n", r_ctl);
		जाओ unlock;
	पूर्ण

	अगर (r_ctl == FC_RCTL_DD_DATA_DESC) अणु
		/*
		 * received XFER RDY from the target
		 * need to send data to the target
		 */
		WARN_ON(fr_flags(fp) & FCPHF_CRC_UNCHECKED);
		dd = fc_frame_payload_get(fp, माप(*dd));
		WARN_ON(!dd);

		rc = fc_fcp_send_data(fsp, seq,
				      (माप_प्रकार) ntohl(dd->ft_data_ro),
				      (माप_प्रकार) ntohl(dd->ft_burst_len));
		अगर (!rc)
			seq->rec_data = fsp->xfer_len;
	पूर्ण अन्यथा अगर (r_ctl == FC_RCTL_DD_SOL_DATA) अणु
		/*
		 * received a DATA frame
		 * next we will copy the data to the प्रणाली buffer
		 */
		WARN_ON(fr_len(fp) < माप(*fh));	/* len may be 0 */
		fc_fcp_recv_data(fsp, fp);
		seq->rec_data = fsp->xfer_contig_end;
	पूर्ण अन्यथा अगर (r_ctl == FC_RCTL_DD_CMD_STATUS) अणु
		WARN_ON(fr_flags(fp) & FCPHF_CRC_UNCHECKED);

		fc_fcp_resp(fsp, fp);
	पूर्ण अन्यथा अणु
		FC_FCP_DBG(fsp, "unexpected frame.  r_ctl %x\n", r_ctl);
	पूर्ण
unlock:
	fc_fcp_unlock_pkt(fsp);
out:
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_fcp_resp() - Handler क्रम FCP responses
 * @fsp: The FCP packet the response is क्रम
 * @fp:	 The response frame
 */
अटल व्योम fc_fcp_resp(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh;
	काष्ठा fcp_resp *fc_rp;
	काष्ठा fcp_resp_ext *rp_ex;
	काष्ठा fcp_resp_rsp_info *fc_rp_info;
	u32 plen;
	u32 expected_len;
	u32 respl = 0;
	u32 snsl = 0;
	u8 flags = 0;

	plen = fr_len(fp);
	fh = (काष्ठा fc_frame_header *)fr_hdr(fp);
	अगर (unlikely(plen < माप(*fh) + माप(*fc_rp)))
		जाओ len_err;
	plen -= माप(*fh);
	fc_rp = (काष्ठा fcp_resp *)(fh + 1);
	fsp->cdb_status = fc_rp->fr_status;
	flags = fc_rp->fr_flags;
	fsp->scsi_comp_flags = flags;
	expected_len = fsp->data_len;

	/* अगर ddp, update xfer len */
	fc_fcp_ddp_करोne(fsp);

	अगर (unlikely((flags & ~FCP_CONF_REQ) || fc_rp->fr_status)) अणु
		rp_ex = (व्योम *)(fc_rp + 1);
		अगर (flags & (FCP_RSP_LEN_VAL | FCP_SNS_LEN_VAL)) अणु
			अगर (plen < माप(*fc_rp) + माप(*rp_ex))
				जाओ len_err;
			fc_rp_info = (काष्ठा fcp_resp_rsp_info *)(rp_ex + 1);
			अगर (flags & FCP_RSP_LEN_VAL) अणु
				respl = ntohl(rp_ex->fr_rsp_len);
				अगर ((respl != FCP_RESP_RSP_INFO_LEN4) &&
				    (respl != FCP_RESP_RSP_INFO_LEN8))
					जाओ len_err;
				अगर (fsp->रुको_क्रम_comp) अणु
					/* Abuse cdb_status क्रम rsp code */
					fsp->cdb_status = fc_rp_info->rsp_code;
					complete(&fsp->पंचांग_करोne);
					/*
					 * पंचांगfs will not have any scsi cmd so
					 * निकास here
					 */
					वापस;
				पूर्ण
			पूर्ण
			अगर (flags & FCP_SNS_LEN_VAL) अणु
				snsl = ntohl(rp_ex->fr_sns_len);
				अगर (snsl > SCSI_SENSE_BUFFERSIZE)
					snsl = SCSI_SENSE_BUFFERSIZE;
				स_नकल(fsp->cmd->sense_buffer,
				       (अक्षर *)fc_rp_info + respl, snsl);
			पूर्ण
		पूर्ण
		अगर (flags & (FCP_RESID_UNDER | FCP_RESID_OVER)) अणु
			अगर (plen < माप(*fc_rp) + माप(rp_ex->fr_resid))
				जाओ len_err;
			अगर (flags & FCP_RESID_UNDER) अणु
				fsp->scsi_resid = ntohl(rp_ex->fr_resid);
				/*
				 * The cmnd->underflow is the minimum number of
				 * bytes that must be transferred क्रम this
				 * command.  Provided a sense condition is not
				 * present, make sure the actual amount
				 * transferred is at least the underflow value
				 * or fail.
				 */
				अगर (!(flags & FCP_SNS_LEN_VAL) &&
				    (fc_rp->fr_status == 0) &&
				    (scsi_bufflen(fsp->cmd) -
				     fsp->scsi_resid) < fsp->cmd->underflow)
					जाओ err;
				expected_len -= fsp->scsi_resid;
			पूर्ण अन्यथा अणु
				fsp->status_code = FC_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण
	fsp->state |= FC_SRB_RCV_STATUS;

	/*
	 * Check क्रम missing or extra data frames.
	 */
	अगर (unlikely(fsp->cdb_status == SAM_STAT_GOOD &&
		     fsp->xfer_len != expected_len)) अणु
		अगर (fsp->xfer_len < expected_len) अणु
			/*
			 * Some data may be queued locally,
			 * Wait a at least one jअगरfy to see अगर it is delivered.
			 * If this expires without data, we may करो SRR.
			 */
			अगर (fsp->lp->qfull) अणु
				FC_FCP_DBG(fsp, "tgt %6.6x queue busy retry\n",
					   fsp->rport->port_id);
				वापस;
			पूर्ण
			FC_FCP_DBG(fsp, "tgt %6.6x xfer len %zx data underrun "
				   "len %x, data len %x\n",
				   fsp->rport->port_id,
				   fsp->xfer_len, expected_len, fsp->data_len);
			fc_fcp_समयr_set(fsp, get_fsp_rec_tov(fsp));
			वापस;
		पूर्ण
		fsp->status_code = FC_DATA_OVRRUN;
		FC_FCP_DBG(fsp, "tgt %6.6x xfer len %zx greater than expected, "
			   "len %x, data len %x\n",
			   fsp->rport->port_id,
			   fsp->xfer_len, expected_len, fsp->data_len);
	पूर्ण
	fc_fcp_complete_locked(fsp);
	वापस;

len_err:
	FC_FCP_DBG(fsp, "short FCP response. flags 0x%x len %u respl %u "
		   "snsl %u\n", flags, fr_len(fp), respl, snsl);
err:
	fsp->status_code = FC_ERROR;
	fc_fcp_complete_locked(fsp);
पूर्ण

/**
 * fc_fcp_complete_locked() - Complete processing of a fcp_pkt with the
 *			      fcp_pkt lock held
 * @fsp: The FCP packet to be completed
 *
 * This function may sleep अगर a समयr is pending. The packet lock must be
 * held, and the host lock must not be held.
 */
अटल व्योम fc_fcp_complete_locked(काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_lport *lport = fsp->lp;
	काष्ठा fc_seq *seq;
	काष्ठा fc_exch *ep;
	u32 f_ctl;

	अगर (fsp->state & FC_SRB_ABORT_PENDING)
		वापस;

	अगर (fsp->state & FC_SRB_ABORTED) अणु
		अगर (!fsp->status_code)
			fsp->status_code = FC_CMD_ABORTED;
	पूर्ण अन्यथा अणु
		/*
		 * Test क्रम transport underrun, independent of response
		 * underrun status.
		 */
		अगर (fsp->cdb_status == SAM_STAT_GOOD &&
		    fsp->xfer_len < fsp->data_len && !fsp->io_status &&
		    (!(fsp->scsi_comp_flags & FCP_RESID_UNDER) ||
		     fsp->xfer_len < fsp->data_len - fsp->scsi_resid)) अणु
			FC_FCP_DBG(fsp, "data underrun, xfer %zx data %x\n",
				    fsp->xfer_len, fsp->data_len);
			fsp->status_code = FC_DATA_UNDRUN;
		पूर्ण
	पूर्ण

	seq = fsp->seq_ptr;
	अगर (seq) अणु
		fsp->seq_ptr = शून्य;
		अगर (unlikely(fsp->scsi_comp_flags & FCP_CONF_REQ)) अणु
			काष्ठा fc_frame *conf_frame;
			काष्ठा fc_seq *csp;

			csp = fc_seq_start_next(seq);
			conf_frame = fc_fcp_frame_alloc(fsp->lp, 0);
			अगर (conf_frame) अणु
				f_ctl = FC_FC_SEQ_INIT;
				f_ctl |= FC_FC_LAST_SEQ | FC_FC_END_SEQ;
				ep = fc_seq_exch(seq);
				fc_fill_fc_hdr(conf_frame, FC_RCTL_DD_SOL_CTL,
					       ep->did, ep->sid,
					       FC_TYPE_FCP, f_ctl, 0);
				fc_seq_send(lport, csp, conf_frame);
			पूर्ण
		पूर्ण
		fc_exch_करोne(seq);
	पूर्ण
	/*
	 * Some resets driven by SCSI are not I/Os and करो not have
	 * SCSI commands associated with the requests. We should not
	 * call I/O completion अगर we करो not have a SCSI command.
	 */
	अगर (fsp->cmd)
		fc_io_compl(fsp);
पूर्ण

/**
 * fc_fcp_cleanup_cmd() - Cancel the active exchange on a fcp_pkt
 * @fsp:   The FCP packet whose exchanges should be canceled
 * @error: The reason क्रम the cancellation
 */
अटल व्योम fc_fcp_cleanup_cmd(काष्ठा fc_fcp_pkt *fsp, पूर्णांक error)
अणु
	अगर (fsp->seq_ptr) अणु
		fc_exch_करोne(fsp->seq_ptr);
		fsp->seq_ptr = शून्य;
	पूर्ण
	fsp->status_code = error;
पूर्ण

/**
 * fc_fcp_cleanup_each_cmd() - Cancel all exchanges on a local port
 * @lport: The local port whose exchanges should be canceled
 * @id:	   The target's ID
 * @lun:   The LUN
 * @error: The reason क्रम cancellation
 *
 * If lun or id is -1, they are ignored.
 */
अटल व्योम fc_fcp_cleanup_each_cmd(काष्ठा fc_lport *lport, अचिन्हित पूर्णांक id,
				    अचिन्हित पूर्णांक lun, पूर्णांक error)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);
	काष्ठा fc_fcp_pkt *fsp;
	काष्ठा scsi_cmnd *sc_cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&si->scsi_queue_lock, flags);
restart:
	list_क्रम_each_entry(fsp, &si->scsi_pkt_queue, list) अणु
		sc_cmd = fsp->cmd;
		अगर (id != -1 && scmd_id(sc_cmd) != id)
			जारी;

		अगर (lun != -1 && sc_cmd->device->lun != lun)
			जारी;

		fc_fcp_pkt_hold(fsp);
		spin_unlock_irqrestore(&si->scsi_queue_lock, flags);

		spin_lock_bh(&fsp->scsi_pkt_lock);
		अगर (!(fsp->state & FC_SRB_COMPL)) अणु
			fsp->state |= FC_SRB_COMPL;
			/*
			 * TODO: dropping scsi_pkt_lock and then reacquiring
			 * again around fc_fcp_cleanup_cmd() is required,
			 * since fc_fcp_cleanup_cmd() calls पूर्णांकo
			 * fc_seq_set_resp() and that func preempts cpu using
			 * schedule. May be schedule and related code should be
			 * हटाओd instead of unlocking here to aव्योम scheduling
			 * जबतक atomic bug.
			 */
			spin_unlock_bh(&fsp->scsi_pkt_lock);

			fc_fcp_cleanup_cmd(fsp, error);

			spin_lock_bh(&fsp->scsi_pkt_lock);
			fc_io_compl(fsp);
		पूर्ण
		spin_unlock_bh(&fsp->scsi_pkt_lock);

		fc_fcp_pkt_release(fsp);
		spin_lock_irqsave(&si->scsi_queue_lock, flags);
		/*
		 * जबतक we dropped the lock multiple pkts could
		 * have been released, so we have to start over.
		 */
		जाओ restart;
	पूर्ण
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
पूर्ण

/**
 * fc_fcp_पात_io() - Abort all FCP-SCSI exchanges on a local port
 * @lport: The local port whose exchanges are to be पातed
 */
अटल व्योम fc_fcp_पात_io(काष्ठा fc_lport *lport)
अणु
	fc_fcp_cleanup_each_cmd(lport, -1, -1, FC_HRD_ERROR);
पूर्ण

/**
 * fc_fcp_pkt_send() - Send a fcp_pkt
 * @lport: The local port to send the FCP packet on
 * @fsp:   The FCP packet to send
 *
 * Return:  Zero क्रम success and -1 क्रम failure
 * Locks:   Called without locks held
 */
अटल पूर्णांक fc_fcp_pkt_send(काष्ठा fc_lport *lport, काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	fsp->cmd->SCp.ptr = (अक्षर *)fsp;
	fsp->cdb_cmd.fc_dl = htonl(fsp->data_len);
	fsp->cdb_cmd.fc_flags = fsp->req_flags & ~FCP_CFL_LEN_MASK;

	पूर्णांक_to_scsilun(fsp->cmd->device->lun, &fsp->cdb_cmd.fc_lun);
	स_नकल(fsp->cdb_cmd.fc_cdb, fsp->cmd->cmnd, fsp->cmd->cmd_len);

	spin_lock_irqsave(&si->scsi_queue_lock, flags);
	list_add_tail(&fsp->list, &si->scsi_pkt_queue);
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
	rc = lport->tt.fcp_cmd_send(lport, fsp, fc_fcp_recv);
	अगर (unlikely(rc)) अणु
		spin_lock_irqsave(&si->scsi_queue_lock, flags);
		fsp->cmd->SCp.ptr = शून्य;
		list_del(&fsp->list);
		spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * fc_fcp_cmd_send() - Send a FCP command
 * @lport: The local port to send the command on
 * @fsp:   The FCP packet the command is on
 * @resp:  The handler क्रम the response
 */
अटल पूर्णांक fc_fcp_cmd_send(काष्ठा fc_lport *lport, काष्ठा fc_fcp_pkt *fsp,
			   व्योम (*resp)(काष्ठा fc_seq *,
					काष्ठा fc_frame *fp,
					व्योम *arg))
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_seq *seq;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_libfc_priv *rpriv;
	स्थिर माप_प्रकार len = माप(fsp->cdb_cmd);
	पूर्णांक rc = 0;

	अगर (fc_fcp_lock_pkt(fsp))
		वापस 0;

	fp = fc_fcp_frame_alloc(lport, माप(fsp->cdb_cmd));
	अगर (!fp) अणु
		rc = -1;
		जाओ unlock;
	पूर्ण

	स_नकल(fc_frame_payload_get(fp, len), &fsp->cdb_cmd, len);
	fr_fsp(fp) = fsp;
	rport = fsp->rport;
	fsp->max_payload = rport->maxframe_size;
	rpriv = rport->dd_data;

	fc_fill_fc_hdr(fp, FC_RCTL_DD_UNSOL_CMD, rport->port_id,
		       rpriv->local_port->port_id, FC_TYPE_FCP,
		       FC_FCTL_REQ, 0);

	seq = fc_exch_seq_send(lport, fp, resp, fc_fcp_pkt_destroy, fsp, 0);
	अगर (!seq) अणु
		rc = -1;
		जाओ unlock;
	पूर्ण
	fsp->seq_ptr = seq;
	fc_fcp_pkt_hold(fsp);	/* hold क्रम fc_fcp_pkt_destroy */

	fsp->समयr.function = fc_fcp_समयout;
	अगर (rpriv->flags & FC_RP_FLAGS_REC_SUPPORTED)
		fc_fcp_समयr_set(fsp, get_fsp_rec_tov(fsp));

unlock:
	fc_fcp_unlock_pkt(fsp);
	वापस rc;
पूर्ण

/**
 * fc_fcp_error() - Handler क्रम FCP layer errors
 * @fsp: The FCP packet the error is on
 * @fp:	 The frame that has errored
 */
अटल व्योम fc_fcp_error(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	पूर्णांक error = PTR_ERR(fp);

	अगर (fc_fcp_lock_pkt(fsp))
		वापस;

	अगर (error == -FC_EX_CLOSED) अणु
		fc_fcp_retry_cmd(fsp, FC_ERROR);
		जाओ unlock;
	पूर्ण

	/*
	 * clear पात pending, because the lower layer
	 * decided to क्रमce completion.
	 */
	fsp->state &= ~FC_SRB_ABORT_PENDING;
	fsp->status_code = FC_CMD_PLOGO;
	fc_fcp_complete_locked(fsp);
unlock:
	fc_fcp_unlock_pkt(fsp);
पूर्ण

/**
 * fc_fcp_pkt_पात() - Abort a fcp_pkt
 * @fsp:   The FCP packet to पात on
 *
 * Called to send an पात and then रुको क्रम पात completion
 */
अटल पूर्णांक fc_fcp_pkt_पात(काष्ठा fc_fcp_pkt *fsp)
अणु
	पूर्णांक rc = FAILED;
	अचिन्हित दीर्घ ticks_left;

	FC_FCP_DBG(fsp, "pkt abort state %x\n", fsp->state);
	अगर (fc_fcp_send_पात(fsp)) अणु
		FC_FCP_DBG(fsp, "failed to send abort\n");
		वापस FAILED;
	पूर्ण

	अगर (fsp->state & FC_SRB_ABORTED) अणु
		FC_FCP_DBG(fsp, "target abort cmd  completed\n");
		वापस SUCCESS;
	पूर्ण

	init_completion(&fsp->पंचांग_करोne);
	fsp->रुको_क्रम_comp = 1;

	spin_unlock_bh(&fsp->scsi_pkt_lock);
	ticks_left = रुको_क्रम_completion_समयout(&fsp->पंचांग_करोne,
							FC_SCSI_TM_TOV);
	spin_lock_bh(&fsp->scsi_pkt_lock);
	fsp->रुको_क्रम_comp = 0;

	अगर (!ticks_left) अणु
		FC_FCP_DBG(fsp, "target abort cmd  failed\n");
	पूर्ण अन्यथा अगर (fsp->state & FC_SRB_ABORTED) अणु
		FC_FCP_DBG(fsp, "target abort cmd  passed\n");
		rc = SUCCESS;
		fc_fcp_complete_locked(fsp);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * fc_lun_reset_send() - Send LUN reset command
 * @t: Timer context used to fetch the FSP packet
 */
अटल व्योम fc_lun_reset_send(काष्ठा समयr_list *t)
अणु
	काष्ठा fc_fcp_pkt *fsp = from_समयr(fsp, t, समयr);
	काष्ठा fc_lport *lport = fsp->lp;

	अगर (lport->tt.fcp_cmd_send(lport, fsp, fc_पंचांग_करोne)) अणु
		अगर (fsp->recov_retry++ >= FC_MAX_RECOV_RETRY)
			वापस;
		अगर (fc_fcp_lock_pkt(fsp))
			वापस;
		fsp->समयr.function = fc_lun_reset_send;
		fc_fcp_समयr_set(fsp, get_fsp_rec_tov(fsp));
		fc_fcp_unlock_pkt(fsp);
	पूर्ण
पूर्ण

/**
 * fc_lun_reset() - Send a LUN RESET command to a device
 *		    and रुको क्रम the reply
 * @lport: The local port to sent the command on
 * @fsp:   The FCP packet that identअगरies the LUN to be reset
 * @id:	   The SCSI command ID
 * @lun:   The LUN ID to be reset
 */
अटल पूर्णांक fc_lun_reset(काष्ठा fc_lport *lport, काष्ठा fc_fcp_pkt *fsp,
			अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक lun)
अणु
	पूर्णांक rc;

	fsp->cdb_cmd.fc_dl = htonl(fsp->data_len);
	fsp->cdb_cmd.fc_पंचांग_flags = FCP_TMF_LUN_RESET;
	पूर्णांक_to_scsilun(lun, &fsp->cdb_cmd.fc_lun);

	fsp->रुको_क्रम_comp = 1;
	init_completion(&fsp->पंचांग_करोne);

	fc_lun_reset_send(&fsp->समयr);

	/*
	 * रुको क्रम completion of reset
	 * after that make sure all commands are terminated
	 */
	rc = रुको_क्रम_completion_समयout(&fsp->पंचांग_करोne, FC_SCSI_TM_TOV);

	spin_lock_bh(&fsp->scsi_pkt_lock);
	fsp->state |= FC_SRB_COMPL;
	spin_unlock_bh(&fsp->scsi_pkt_lock);

	del_समयr_sync(&fsp->समयr);

	spin_lock_bh(&fsp->scsi_pkt_lock);
	अगर (fsp->seq_ptr) अणु
		fc_exch_करोne(fsp->seq_ptr);
		fsp->seq_ptr = शून्य;
	पूर्ण
	fsp->रुको_क्रम_comp = 0;
	spin_unlock_bh(&fsp->scsi_pkt_lock);

	अगर (!rc) अणु
		FC_SCSI_DBG(lport, "lun reset failed\n");
		वापस FAILED;
	पूर्ण

	/* cdb_status holds the पंचांगf's rsp code */
	अगर (fsp->cdb_status != FCP_TMF_CMPL)
		वापस FAILED;

	FC_SCSI_DBG(lport, "lun reset to lun %u completed\n", lun);
	fc_fcp_cleanup_each_cmd(lport, id, lun, FC_CMD_ABORTED);
	वापस SUCCESS;
पूर्ण

/**
 * fc_पंचांग_करोne() - Task Management response handler
 * @seq: The sequence that the response is on
 * @fp:	 The response frame
 * @arg: The FCP packet the response is क्रम
 */
अटल व्योम fc_पंचांग_करोne(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_fcp_pkt *fsp = arg;
	काष्ठा fc_frame_header *fh;

	अगर (IS_ERR(fp)) अणु
		/*
		 * If there is an error just let it समयout or रुको
		 * क्रम TMF to be पातed अगर it समयकरोut.
		 *
		 * scsi-eh will escalate क्रम when either happens.
		 */
		वापस;
	पूर्ण

	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;

	/*
	 * raced with eh समयout handler.
	 */
	अगर (!fsp->seq_ptr || !fsp->रुको_क्रम_comp)
		जाओ out_unlock;

	fh = fc_frame_header_get(fp);
	अगर (fh->fh_type != FC_TYPE_BLS)
		fc_fcp_resp(fsp, fp);
	fsp->seq_ptr = शून्य;
	fc_exch_करोne(seq);
out_unlock:
	fc_fcp_unlock_pkt(fsp);
out:
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_fcp_cleanup() - Cleanup all FCP exchanges on a local port
 * @lport: The local port to be cleaned up
 */
अटल व्योम fc_fcp_cleanup(काष्ठा fc_lport *lport)
अणु
	fc_fcp_cleanup_each_cmd(lport, -1, -1, FC_ERROR);
पूर्ण

/**
 * fc_fcp_समयout() - Handler क्रम fcp_pkt समयouts
 * @t: Timer context used to fetch the FSP packet
 *
 * If REC is supported then just issue it and वापस. The REC exchange will
 * complete or समय out and recovery can जारी at that poपूर्णांक. Otherwise,
 * अगर the response has been received without all the data it has been
 * ER_TIMEOUT since the response was received. If the response has not been
 * received we see अगर data was received recently. If it has been then we
 * जारी रुकोing, otherwise, we पात the command.
 */
अटल व्योम fc_fcp_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा fc_fcp_pkt *fsp = from_समयr(fsp, t, समयr);
	काष्ठा fc_rport *rport = fsp->rport;
	काष्ठा fc_rport_libfc_priv *rpriv = rport->dd_data;

	अगर (fc_fcp_lock_pkt(fsp))
		वापस;

	अगर (fsp->cdb_cmd.fc_पंचांग_flags)
		जाओ unlock;

	अगर (fsp->lp->qfull) अणु
		FC_FCP_DBG(fsp, "fcp timeout, resetting timer delay %d\n",
			   fsp->समयr_delay);
		fsp->समयr.function = fc_fcp_समयout;
		fc_fcp_समयr_set(fsp, fsp->समयr_delay);
		जाओ unlock;
	पूर्ण
	FC_FCP_DBG(fsp, "fcp timeout, delay %d flags %x state %x\n",
		   fsp->समयr_delay, rpriv->flags, fsp->state);
	fsp->state |= FC_SRB_FCP_PROCESSING_TMO;

	अगर (rpriv->flags & FC_RP_FLAGS_REC_SUPPORTED)
		fc_fcp_rec(fsp);
	अन्यथा अगर (fsp->state & FC_SRB_RCV_STATUS)
		fc_fcp_complete_locked(fsp);
	अन्यथा
		fc_fcp_recovery(fsp, FC_TIMED_OUT);
	fsp->state &= ~FC_SRB_FCP_PROCESSING_TMO;
unlock:
	fc_fcp_unlock_pkt(fsp);
पूर्ण

/**
 * fc_fcp_rec() - Send a REC ELS request
 * @fsp: The FCP packet to send the REC request on
 */
अटल व्योम fc_fcp_rec(काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame *fp;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_libfc_priv *rpriv;

	lport = fsp->lp;
	rport = fsp->rport;
	rpriv = rport->dd_data;
	अगर (!fsp->seq_ptr || rpriv->rp_state != RPORT_ST_READY) अणु
		fsp->status_code = FC_HRD_ERROR;
		fsp->io_status = 0;
		fc_fcp_complete_locked(fsp);
		वापस;
	पूर्ण

	fp = fc_fcp_frame_alloc(lport, माप(काष्ठा fc_els_rec));
	अगर (!fp)
		जाओ retry;

	fr_seq(fp) = fsp->seq_ptr;
	fc_fill_fc_hdr(fp, FC_RCTL_ELS_REQ, rport->port_id,
		       rpriv->local_port->port_id, FC_TYPE_ELS,
		       FC_FCTL_REQ, 0);
	अगर (lport->tt.elsct_send(lport, rport->port_id, fp, ELS_REC,
				 fc_fcp_rec_resp, fsp,
				 2 * lport->r_a_tov)) अणु
		fc_fcp_pkt_hold(fsp);		/* hold जबतक REC outstanding */
		वापस;
	पूर्ण
retry:
	अगर (fsp->recov_retry++ < FC_MAX_RECOV_RETRY)
		fc_fcp_समयr_set(fsp, get_fsp_rec_tov(fsp));
	अन्यथा
		fc_fcp_recovery(fsp, FC_TIMED_OUT);
पूर्ण

/**
 * fc_fcp_rec_resp() - Handler क्रम REC ELS responses
 * @seq: The sequence the response is on
 * @fp:	 The response frame
 * @arg: The FCP packet the response is on
 *
 * If the response is a reject then the scsi layer will handle
 * the समयout. If the response is a LS_ACC then अगर the I/O was not completed
 * set the समयout and वापस. If the I/O was completed then complete the
 * exchange and tell the SCSI layer.
 */
अटल व्योम fc_fcp_rec_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_fcp_pkt *fsp = (काष्ठा fc_fcp_pkt *)arg;
	काष्ठा fc_els_rec_acc *recp;
	काष्ठा fc_els_ls_rjt *rjt;
	u32 e_stat;
	u8 opcode;
	u32 offset;
	क्रमागत dma_data_direction data_dir;
	क्रमागत fc_rctl r_ctl;
	काष्ठा fc_rport_libfc_priv *rpriv;

	अगर (IS_ERR(fp)) अणु
		fc_fcp_rec_error(fsp, fp);
		वापस;
	पूर्ण

	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;

	fsp->recov_retry = 0;
	opcode = fc_frame_payload_op(fp);
	अगर (opcode == ELS_LS_RJT) अणु
		rjt = fc_frame_payload_get(fp, माप(*rjt));
		चयन (rjt->er_reason) अणु
		शेष:
			FC_FCP_DBG(fsp,
				   "device %x invalid REC reject %d/%d\n",
				   fsp->rport->port_id, rjt->er_reason,
				   rjt->er_explan);
			fallthrough;
		हाल ELS_RJT_UNSUP:
			FC_FCP_DBG(fsp, "device does not support REC\n");
			rpriv = fsp->rport->dd_data;
			/*
			 * अगर we करो not spport RECs or got some bogus
			 * reason then resetup समयr so we check क्रम
			 * making progress.
			 */
			rpriv->flags &= ~FC_RP_FLAGS_REC_SUPPORTED;
			अवरोध;
		हाल ELS_RJT_LOGIC:
		हाल ELS_RJT_UNAB:
			FC_FCP_DBG(fsp, "device %x REC reject %d/%d\n",
				   fsp->rport->port_id, rjt->er_reason,
				   rjt->er_explan);
			/*
			 * If response got lost or is stuck in the
			 * queue somewhere we have no idea अगर and when
			 * the response will be received. So quarantine
			 * the xid and retry the command.
			 */
			अगर (rjt->er_explan == ELS_EXPL_OXID_RXID) अणु
				काष्ठा fc_exch *ep = fc_seq_exch(fsp->seq_ptr);
				ep->state |= FC_EX_QUARANTINE;
				fsp->state |= FC_SRB_ABORTED;
				fc_fcp_retry_cmd(fsp, FC_TRANS_RESET);
				अवरोध;
			पूर्ण
			fc_fcp_recovery(fsp, FC_TRANS_RESET);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (opcode == ELS_LS_ACC) अणु
		अगर (fsp->state & FC_SRB_ABORTED)
			जाओ unlock_out;

		data_dir = fsp->cmd->sc_data_direction;
		recp = fc_frame_payload_get(fp, माप(*recp));
		offset = ntohl(recp->reca_fc4value);
		e_stat = ntohl(recp->reca_e_stat);

		अगर (e_stat & ESB_ST_COMPLETE) अणु

			/*
			 * The exchange is complete.
			 *
			 * For output, we must've lost the response.
			 * For input, all data must've been sent.
			 * We lost may have lost the response
			 * (and a confirmation was requested) and maybe
			 * some data.
			 *
			 * If all data received, send SRR
			 * asking क्रम response.	 If partial data received,
			 * or gaps, SRR requests data at start of gap.
			 * Recovery via SRR relies on in-order-delivery.
			 */
			अगर (data_dir == DMA_TO_DEVICE) अणु
				r_ctl = FC_RCTL_DD_CMD_STATUS;
			पूर्ण अन्यथा अगर (fsp->xfer_contig_end == offset) अणु
				r_ctl = FC_RCTL_DD_CMD_STATUS;
			पूर्ण अन्यथा अणु
				offset = fsp->xfer_contig_end;
				r_ctl = FC_RCTL_DD_SOL_DATA;
			पूर्ण
			fc_fcp_srr(fsp, r_ctl, offset);
		पूर्ण अन्यथा अगर (e_stat & ESB_ST_SEQ_INIT) अणु
			/*
			 * The remote port has the initiative, so just
			 * keep रुकोing क्रम it to complete.
			 */
			fc_fcp_समयr_set(fsp,  get_fsp_rec_tov(fsp));
		पूर्ण अन्यथा अणु

			/*
			 * The exchange is incomplete, we have seq. initiative.
			 * Lost response with requested confirmation,
			 * lost confirmation, lost transfer पढ़ोy or
			 * lost ग_लिखो data.
			 *
			 * For output, अगर not all data was received, ask
			 * क्रम transfer पढ़ोy to be repeated.
			 *
			 * If we received or sent all the data, send SRR to
			 * request response.
			 *
			 * If we lost a response, we may have lost some पढ़ो
			 * data as well.
			 */
			r_ctl = FC_RCTL_DD_SOL_DATA;
			अगर (data_dir == DMA_TO_DEVICE) अणु
				r_ctl = FC_RCTL_DD_CMD_STATUS;
				अगर (offset < fsp->data_len)
					r_ctl = FC_RCTL_DD_DATA_DESC;
			पूर्ण अन्यथा अगर (offset == fsp->xfer_contig_end) अणु
				r_ctl = FC_RCTL_DD_CMD_STATUS;
			पूर्ण अन्यथा अगर (fsp->xfer_contig_end < offset) अणु
				offset = fsp->xfer_contig_end;
			पूर्ण
			fc_fcp_srr(fsp, r_ctl, offset);
		पूर्ण
	पूर्ण
unlock_out:
	fc_fcp_unlock_pkt(fsp);
out:
	fc_fcp_pkt_release(fsp);	/* drop hold क्रम outstanding REC */
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_fcp_rec_error() - Handler क्रम REC errors
 * @fsp: The FCP packet the error is on
 * @fp:	 The REC frame
 */
अटल व्योम fc_fcp_rec_error(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	पूर्णांक error = PTR_ERR(fp);

	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;

	चयन (error) अणु
	हाल -FC_EX_CLOSED:
		FC_FCP_DBG(fsp, "REC %p fid %6.6x exchange closed\n",
			   fsp, fsp->rport->port_id);
		fc_fcp_retry_cmd(fsp, FC_ERROR);
		अवरोध;

	शेष:
		FC_FCP_DBG(fsp, "REC %p fid %6.6x error unexpected error %d\n",
			   fsp, fsp->rport->port_id, error);
		fsp->status_code = FC_CMD_PLOGO;
		fallthrough;

	हाल -FC_EX_TIMEOUT:
		/*
		 * Assume REC or LS_ACC was lost.
		 * The exchange manager will have पातed REC, so retry.
		 */
		FC_FCP_DBG(fsp, "REC %p fid %6.6x exchange timeout retry %d/%d\n",
			   fsp, fsp->rport->port_id, fsp->recov_retry,
			   FC_MAX_RECOV_RETRY);
		अगर (fsp->recov_retry++ < FC_MAX_RECOV_RETRY)
			fc_fcp_rec(fsp);
		अन्यथा
			fc_fcp_recovery(fsp, FC_ERROR);
		अवरोध;
	पूर्ण
	fc_fcp_unlock_pkt(fsp);
out:
	fc_fcp_pkt_release(fsp);	/* drop hold क्रम outstanding REC */
पूर्ण

/**
 * fc_fcp_recovery() - Handler क्रम fcp_pkt recovery
 * @fsp: The FCP pkt that needs to be पातed
 * @code: The FCP status code to set
 */
अटल व्योम fc_fcp_recovery(काष्ठा fc_fcp_pkt *fsp, u8 code)
अणु
	FC_FCP_DBG(fsp, "start recovery code %x\n", code);
	fsp->status_code = code;
	fsp->cdb_status = 0;
	fsp->io_status = 0;
	/*
	 * अगर this fails then we let the scsi command समयr fire and
	 * scsi-ml escalate.
	 */
	fc_fcp_send_पात(fsp);
पूर्ण

/**
 * fc_fcp_srr() - Send a SRR request (Sequence Retransmission Request)
 * @fsp:   The FCP packet the SRR is to be sent on
 * @r_ctl: The R_CTL field क्रम the SRR request
 * @offset: The SRR relative offset
 * This is called after receiving status but insufficient data, or
 * when expecting status but the request has समयd out.
 */
अटल व्योम fc_fcp_srr(काष्ठा fc_fcp_pkt *fsp, क्रमागत fc_rctl r_ctl, u32 offset)
अणु
	काष्ठा fc_lport *lport = fsp->lp;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_libfc_priv *rpriv;
	काष्ठा fc_exch *ep = fc_seq_exch(fsp->seq_ptr);
	काष्ठा fc_seq *seq;
	काष्ठा fcp_srr *srr;
	काष्ठा fc_frame *fp;

	rport = fsp->rport;
	rpriv = rport->dd_data;

	अगर (!(rpriv->flags & FC_RP_FLAGS_RETRY) ||
	    rpriv->rp_state != RPORT_ST_READY)
		जाओ retry;			/* shouldn't happen */
	fp = fc_fcp_frame_alloc(lport, माप(*srr));
	अगर (!fp)
		जाओ retry;

	srr = fc_frame_payload_get(fp, माप(*srr));
	स_रखो(srr, 0, माप(*srr));
	srr->srr_op = ELS_SRR;
	srr->srr_ox_id = htons(ep->oxid);
	srr->srr_rx_id = htons(ep->rxid);
	srr->srr_r_ctl = r_ctl;
	srr->srr_rel_off = htonl(offset);

	fc_fill_fc_hdr(fp, FC_RCTL_ELS4_REQ, rport->port_id,
		       rpriv->local_port->port_id, FC_TYPE_FCP,
		       FC_FCTL_REQ, 0);

	seq = fc_exch_seq_send(lport, fp, fc_fcp_srr_resp,
			       fc_fcp_pkt_destroy,
			       fsp, get_fsp_rec_tov(fsp));
	अगर (!seq)
		जाओ retry;

	fsp->recov_seq = seq;
	fsp->xfer_len = offset;
	fsp->xfer_contig_end = offset;
	fsp->state &= ~FC_SRB_RCV_STATUS;
	fc_fcp_pkt_hold(fsp);		/* hold क्रम outstanding SRR */
	वापस;
retry:
	fc_fcp_retry_cmd(fsp, FC_TRANS_RESET);
पूर्ण

/**
 * fc_fcp_srr_resp() - Handler क्रम SRR response
 * @seq: The sequence the SRR is on
 * @fp:	 The SRR frame
 * @arg: The FCP packet the SRR is on
 */
अटल व्योम fc_fcp_srr_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_fcp_pkt *fsp = arg;
	काष्ठा fc_frame_header *fh;

	अगर (IS_ERR(fp)) अणु
		fc_fcp_srr_error(fsp, fp);
		वापस;
	पूर्ण

	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;

	fh = fc_frame_header_get(fp);
	/*
	 * BUG? fc_fcp_srr_error calls fc_exch_करोne which would release
	 * the ep. But अगर fc_fcp_srr_error had got -FC_EX_TIMEOUT,
	 * then fc_exch_समयout would be sending an पात. The fc_exch_करोne
	 * call by fc_fcp_srr_error would prevent fc_exch.c from seeing
	 * an पात response though.
	 */
	अगर (fh->fh_type == FC_TYPE_BLS) अणु
		fc_fcp_unlock_pkt(fsp);
		वापस;
	पूर्ण

	चयन (fc_frame_payload_op(fp)) अणु
	हाल ELS_LS_ACC:
		fsp->recov_retry = 0;
		fc_fcp_समयr_set(fsp, get_fsp_rec_tov(fsp));
		अवरोध;
	हाल ELS_LS_RJT:
	शेष:
		fc_fcp_recovery(fsp, FC_ERROR);
		अवरोध;
	पूर्ण
	fc_fcp_unlock_pkt(fsp);
out:
	fc_exch_करोne(seq);
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_fcp_srr_error() - Handler क्रम SRR errors
 * @fsp: The FCP packet that the SRR error is on
 * @fp:	 The SRR frame
 */
अटल व्योम fc_fcp_srr_error(काष्ठा fc_fcp_pkt *fsp, काष्ठा fc_frame *fp)
अणु
	अगर (fc_fcp_lock_pkt(fsp))
		जाओ out;
	चयन (PTR_ERR(fp)) अणु
	हाल -FC_EX_TIMEOUT:
		FC_FCP_DBG(fsp, "SRR timeout, retries %d\n", fsp->recov_retry);
		अगर (fsp->recov_retry++ < FC_MAX_RECOV_RETRY)
			fc_fcp_rec(fsp);
		अन्यथा
			fc_fcp_recovery(fsp, FC_TIMED_OUT);
		अवरोध;
	हाल -FC_EX_CLOSED:			/* e.g., link failure */
		FC_FCP_DBG(fsp, "SRR error, exchange closed\n");
		fallthrough;
	शेष:
		fc_fcp_retry_cmd(fsp, FC_ERROR);
		अवरोध;
	पूर्ण
	fc_fcp_unlock_pkt(fsp);
out:
	fc_exch_करोne(fsp->recov_seq);
पूर्ण

/**
 * fc_fcp_lport_queue_पढ़ोy() - Determine अगर the lport and it's queue is पढ़ोy
 * @lport: The local port to be checked
 */
अटल अंतरभूत पूर्णांक fc_fcp_lport_queue_पढ़ोy(काष्ठा fc_lport *lport)
अणु
	/* lock ? */
	वापस (lport->state == LPORT_ST_READY) &&
		lport->link_up && !lport->qfull;
पूर्ण

/**
 * fc_queuecommand() - The queuecommand function of the SCSI ढाँचा
 * @shost: The Scsi_Host that the command was issued to
 * @sc_cmd:   The scsi_cmnd to be executed
 *
 * This is the i/o strategy routine, called by the SCSI layer.
 */
पूर्णांक fc_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_fcp_pkt *fsp;
	पूर्णांक rval;
	पूर्णांक rc = 0;
	काष्ठा fc_stats *stats;

	rval = fc_remote_port_chkपढ़ोy(rport);
	अगर (rval) अणु
		sc_cmd->result = rval;
		sc_cmd->scsi_करोne(sc_cmd);
		वापस 0;
	पूर्ण

	अगर (!*(काष्ठा fc_remote_port **)rport->dd_data) अणु
		/*
		 * rport is transitioning from blocked/deleted to
		 * online
		 */
		sc_cmd->result = DID_IMM_RETRY << 16;
		sc_cmd->scsi_करोne(sc_cmd);
		जाओ out;
	पूर्ण

	अगर (!fc_fcp_lport_queue_पढ़ोy(lport)) अणु
		अगर (lport->qfull) अणु
			अगर (fc_fcp_can_queue_ramp_करोwn(lport))
				shost_prपूर्णांकk(KERN_ERR, lport->host,
					     "libfc: queue full, "
					     "reducing can_queue to %d.\n",
					     lport->host->can_queue);
		पूर्ण
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	fsp = fc_fcp_pkt_alloc(lport, GFP_ATOMIC);
	अगर (fsp == शून्य) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	/*
	 * build the libfc request pkt
	 */
	fsp->cmd = sc_cmd;	/* save the cmd */
	fsp->rport = rport;	/* set the remote port ptr */

	/*
	 * set up the transfer length
	 */
	fsp->data_len = scsi_bufflen(sc_cmd);
	fsp->xfer_len = 0;

	/*
	 * setup the data direction
	 */
	stats = per_cpu_ptr(lport->stats, get_cpu());
	अगर (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		fsp->req_flags = FC_SRB_READ;
		stats->InputRequests++;
		stats->InputBytes += fsp->data_len;
	पूर्ण अन्यथा अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		fsp->req_flags = FC_SRB_WRITE;
		stats->OutputRequests++;
		stats->OutputBytes += fsp->data_len;
	पूर्ण अन्यथा अणु
		fsp->req_flags = 0;
		stats->ControlRequests++;
	पूर्ण
	put_cpu();

	/*
	 * send it to the lower layer
	 * अगर we get -1 वापस then put the request in the pending
	 * queue.
	 */
	rval = fc_fcp_pkt_send(lport, fsp);
	अगर (rval != 0) अणु
		fsp->state = FC_SRB_FREE;
		fc_fcp_pkt_release(fsp);
		rc = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_queuecommand);

/**
 * fc_io_compl() - Handle responses क्रम completed commands
 * @fsp: The FCP packet that is complete
 *
 * Translates fcp_pkt errors to a Linux SCSI errors.
 * The fcp packet lock must be held when calling.
 */
अटल व्योम fc_io_compl(काष्ठा fc_fcp_pkt *fsp)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si;
	काष्ठा scsi_cmnd *sc_cmd;
	काष्ठा fc_lport *lport;
	अचिन्हित दीर्घ flags;

	/* release outstanding ddp context */
	fc_fcp_ddp_करोne(fsp);

	fsp->state |= FC_SRB_COMPL;
	अगर (!(fsp->state & FC_SRB_FCP_PROCESSING_TMO)) अणु
		spin_unlock_bh(&fsp->scsi_pkt_lock);
		del_समयr_sync(&fsp->समयr);
		spin_lock_bh(&fsp->scsi_pkt_lock);
	पूर्ण

	lport = fsp->lp;
	si = fc_get_scsi_पूर्णांकernal(lport);

	/*
	 * अगर can_queue ramp करोwn is करोne then try can_queue ramp up
	 * since commands are completing now.
	 */
	अगर (si->last_can_queue_ramp_करोwn_समय)
		fc_fcp_can_queue_ramp_up(lport);

	sc_cmd = fsp->cmd;
	CMD_SCSI_STATUS(sc_cmd) = fsp->cdb_status;
	चयन (fsp->status_code) अणु
	हाल FC_COMPLETE:
		अगर (fsp->cdb_status == 0) अणु
			/*
			 * good I/O status
			 */
			sc_cmd->result = DID_OK << 16;
			अगर (fsp->scsi_resid)
				CMD_RESID_LEN(sc_cmd) = fsp->scsi_resid;
		पूर्ण अन्यथा अणु
			/*
			 * transport level I/O was ok but scsi
			 * has non zero status
			 */
			sc_cmd->result = (DID_OK << 16) | fsp->cdb_status;
		पूर्ण
		अवरोध;
	हाल FC_ERROR:
		FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml "
			   "due to FC_ERROR\n");
		sc_cmd->result = DID_ERROR << 16;
		अवरोध;
	हाल FC_DATA_UNDRUN:
		अगर ((fsp->cdb_status == 0) && !(fsp->req_flags & FC_SRB_READ)) अणु
			/*
			 * scsi status is good but transport level
			 * underrun.
			 */
			अगर (fsp->state & FC_SRB_RCV_STATUS) अणु
				sc_cmd->result = DID_OK << 16;
			पूर्ण अन्यथा अणु
				FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml"
					   " due to FC_DATA_UNDRUN (trans)\n");
				sc_cmd->result = DID_ERROR << 16;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * scsi got underrun, this is an error
			 */
			FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml "
				   "due to FC_DATA_UNDRUN (scsi)\n");
			CMD_RESID_LEN(sc_cmd) = fsp->scsi_resid;
			sc_cmd->result = (DID_ERROR << 16) | fsp->cdb_status;
		पूर्ण
		अवरोध;
	हाल FC_DATA_OVRRUN:
		/*
		 * overrun is an error
		 */
		FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml "
			   "due to FC_DATA_OVRRUN\n");
		sc_cmd->result = (DID_ERROR << 16) | fsp->cdb_status;
		अवरोध;
	हाल FC_CMD_ABORTED:
		अगर (host_byte(sc_cmd->result) == DID_TIME_OUT)
			FC_FCP_DBG(fsp, "Returning DID_TIME_OUT to scsi-ml "
				   "due to FC_CMD_ABORTED\n");
		अन्यथा अणु
			FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml "
				   "due to FC_CMD_ABORTED\n");
			set_host_byte(sc_cmd, DID_ERROR);
		पूर्ण
		sc_cmd->result |= fsp->io_status;
		अवरोध;
	हाल FC_CMD_RESET:
		FC_FCP_DBG(fsp, "Returning DID_RESET to scsi-ml "
			   "due to FC_CMD_RESET\n");
		sc_cmd->result = (DID_RESET << 16);
		अवरोध;
	हाल FC_TRANS_RESET:
		FC_FCP_DBG(fsp, "Returning DID_SOFT_ERROR to scsi-ml "
			   "due to FC_TRANS_RESET\n");
		sc_cmd->result = (DID_SOFT_ERROR << 16);
		अवरोध;
	हाल FC_HRD_ERROR:
		FC_FCP_DBG(fsp, "Returning DID_NO_CONNECT to scsi-ml "
			   "due to FC_HRD_ERROR\n");
		sc_cmd->result = (DID_NO_CONNECT << 16);
		अवरोध;
	हाल FC_CRC_ERROR:
		FC_FCP_DBG(fsp, "Returning DID_PARITY to scsi-ml "
			   "due to FC_CRC_ERROR\n");
		sc_cmd->result = (DID_PARITY << 16);
		अवरोध;
	हाल FC_TIMED_OUT:
		FC_FCP_DBG(fsp, "Returning DID_BUS_BUSY to scsi-ml "
			   "due to FC_TIMED_OUT\n");
		sc_cmd->result = (DID_BUS_BUSY << 16) | fsp->io_status;
		अवरोध;
	शेष:
		FC_FCP_DBG(fsp, "Returning DID_ERROR to scsi-ml "
			   "due to unknown error\n");
		sc_cmd->result = (DID_ERROR << 16);
		अवरोध;
	पूर्ण

	अगर (lport->state != LPORT_ST_READY && fsp->status_code != FC_COMPLETE)
		sc_cmd->result = (DID_TRANSPORT_DISRUPTED << 16);

	spin_lock_irqsave(&si->scsi_queue_lock, flags);
	list_del(&fsp->list);
	sc_cmd->SCp.ptr = शून्य;
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
	sc_cmd->scsi_करोne(sc_cmd);

	/* release ref from initial allocation in queue command */
	fc_fcp_pkt_release(fsp);
पूर्ण

/**
 * fc_eh_पात() - Abort a command
 * @sc_cmd: The SCSI command to पात
 *
 * From SCSI host ढाँचा.
 * Send an ABTS to the target device and रुको क्रम the response.
 */
पूर्णांक fc_eh_पात(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_fcp_pkt *fsp;
	काष्ठा fc_lport *lport;
	काष्ठा fc_fcp_पूर्णांकernal *si;
	पूर्णांक rc = FAILED;
	अचिन्हित दीर्घ flags;
	पूर्णांक rval;

	rval = fc_block_scsi_eh(sc_cmd);
	अगर (rval)
		वापस rval;

	lport = shost_priv(sc_cmd->device->host);
	अगर (lport->state != LPORT_ST_READY)
		वापस rc;
	अन्यथा अगर (!lport->link_up)
		वापस rc;

	si = fc_get_scsi_पूर्णांकernal(lport);
	spin_lock_irqsave(&si->scsi_queue_lock, flags);
	fsp = CMD_SP(sc_cmd);
	अगर (!fsp) अणु
		/* command completed जबतक scsi eh was setting up */
		spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
		वापस SUCCESS;
	पूर्ण
	/* grab a ref so the fsp and sc_cmd cannot be released from under us */
	fc_fcp_pkt_hold(fsp);
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);

	अगर (fc_fcp_lock_pkt(fsp)) अणु
		/* completed जबतक we were रुकोing क्रम समयr to be deleted */
		rc = SUCCESS;
		जाओ release_pkt;
	पूर्ण

	rc = fc_fcp_pkt_पात(fsp);
	fc_fcp_unlock_pkt(fsp);

release_pkt:
	fc_fcp_pkt_release(fsp);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_eh_पात);

/**
 * fc_eh_device_reset() - Reset a single LUN
 * @sc_cmd: The SCSI command which identअगरies the device whose
 *	    LUN is to be reset
 *
 * Set from SCSI host ढाँचा.
 */
पूर्णांक fc_eh_device_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_fcp_pkt *fsp;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	पूर्णांक rc = FAILED;
	पूर्णांक rval;

	rval = fc_block_scsi_eh(sc_cmd);
	अगर (rval)
		वापस rval;

	lport = shost_priv(sc_cmd->device->host);

	अगर (lport->state != LPORT_ST_READY)
		वापस rc;

	FC_SCSI_DBG(lport, "Resetting rport (%6.6x)\n", rport->port_id);

	fsp = fc_fcp_pkt_alloc(lport, GFP_NOIO);
	अगर (fsp == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "libfc: could not allocate scsi_pkt\n");
		जाओ out;
	पूर्ण

	/*
	 * Build the libfc request pkt. Do not set the scsi cmnd, because
	 * the sc passed in is not setup क्रम execution like when sent
	 * through the queuecommand callout.
	 */
	fsp->rport = rport;	/* set the remote port ptr */

	/*
	 * flush outstanding commands
	 */
	rc = fc_lun_reset(lport, fsp, scmd_id(sc_cmd), sc_cmd->device->lun);
	fsp->state = FC_SRB_FREE;
	fc_fcp_pkt_release(fsp);

out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_eh_device_reset);

/**
 * fc_eh_host_reset() - Reset a Scsi_Host.
 * @sc_cmd: The SCSI command that identअगरies the SCSI host to be reset
 */
पूर्णांक fc_eh_host_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा Scsi_Host *shost = sc_cmd->device->host;
	काष्ठा fc_lport *lport = shost_priv(shost);
	अचिन्हित दीर्घ रुको_पंचांगo;

	FC_SCSI_DBG(lport, "Resetting host\n");

	fc_lport_reset(lport);
	रुको_पंचांगo = jअगरfies + FC_HOST_RESET_TIMEOUT;
	जबतक (!fc_fcp_lport_queue_पढ़ोy(lport) && समय_beक्रमe(jअगरfies,
							       रुको_पंचांगo))
		msleep(1000);

	अगर (fc_fcp_lport_queue_पढ़ोy(lport)) अणु
		shost_prपूर्णांकk(KERN_INFO, shost, "libfc: Host reset succeeded "
			     "on port (%6.6x)\n", lport->port_id);
		वापस SUCCESS;
	पूर्ण अन्यथा अणु
		shost_prपूर्णांकk(KERN_INFO, shost, "libfc: Host reset failed, "
			     "port (%6.6x) is not ready.\n",
			     lport->port_id);
		वापस FAILED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_eh_host_reset);

/**
 * fc_slave_alloc() - Configure the queue depth of a Scsi_Host
 * @sdev: The SCSI device that identअगरies the SCSI host
 *
 * Configures queue depth based on host's cmd_per_len. If not set
 * then we use the libfc शेष.
 */
पूर्णांक fc_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	scsi_change_queue_depth(sdev, FC_FCP_DFLT_QUEUE_DEPTH);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_slave_alloc);

/**
 * fc_fcp_destroy() - Tear करोwn the FCP layer क्रम a given local port
 * @lport: The local port that no दीर्घer needs the FCP layer
 */
व्योम fc_fcp_destroy(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_fcp_पूर्णांकernal *si = fc_get_scsi_पूर्णांकernal(lport);

	अगर (!list_empty(&si->scsi_pkt_queue))
		prपूर्णांकk(KERN_ERR "libfc: Leaked SCSI packets when destroying "
		       "port (%6.6x)\n", lport->port_id);

	mempool_destroy(si->scsi_pkt_pool);
	kमुक्त(si);
	lport->scsi_priv = शून्य;
पूर्ण
EXPORT_SYMBOL(fc_fcp_destroy);

पूर्णांक fc_setup_fcp(व्योम)
अणु
	पूर्णांक rc = 0;

	scsi_pkt_cachep = kmem_cache_create("libfc_fcp_pkt",
					    माप(काष्ठा fc_fcp_pkt),
					    0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!scsi_pkt_cachep) अणु
		prपूर्णांकk(KERN_ERR "libfc: Unable to allocate SRB cache, "
		       "module load failed!");
		rc = -ENOMEM;
	पूर्ण

	वापस rc;
पूर्ण

व्योम fc_destroy_fcp(व्योम)
अणु
	kmem_cache_destroy(scsi_pkt_cachep);
पूर्ण

/**
 * fc_fcp_init() - Initialize the FCP layer क्रम a local port
 * @lport: The local port to initialize the exchange layer क्रम
 */
पूर्णांक fc_fcp_init(काष्ठा fc_lport *lport)
अणु
	पूर्णांक rc;
	काष्ठा fc_fcp_पूर्णांकernal *si;

	अगर (!lport->tt.fcp_cmd_send)
		lport->tt.fcp_cmd_send = fc_fcp_cmd_send;

	अगर (!lport->tt.fcp_cleanup)
		lport->tt.fcp_cleanup = fc_fcp_cleanup;

	अगर (!lport->tt.fcp_पात_io)
		lport->tt.fcp_पात_io = fc_fcp_पात_io;

	si = kzalloc(माप(काष्ठा fc_fcp_पूर्णांकernal), GFP_KERNEL);
	अगर (!si)
		वापस -ENOMEM;
	lport->scsi_priv = si;
	si->max_can_queue = lport->host->can_queue;
	INIT_LIST_HEAD(&si->scsi_pkt_queue);
	spin_lock_init(&si->scsi_queue_lock);

	si->scsi_pkt_pool = mempool_create_slab_pool(2, scsi_pkt_cachep);
	अगर (!si->scsi_pkt_pool) अणु
		rc = -ENOMEM;
		जाओ मुक्त_पूर्णांकernal;
	पूर्ण
	वापस 0;

मुक्त_पूर्णांकernal:
	kमुक्त(si);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_fcp_init);
