<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Avago Technologies.  All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/parser.h>
#समावेश <linux/अक्रमom.h>
#समावेश <uapi/scsi/fc/fc_fs.h>
#समावेश <uapi/scsi/fc/fc_els.h>

#समावेश "nvmet.h"
#समावेश <linux/nvme-fc-driver.h>
#समावेश <linux/nvme-fc.h>
#समावेश "../host/fc.h"


/* *************************** Data Structures/Defines ****************** */


#घोषणा NVMET_LS_CTX_COUNT		256

काष्ठा nvmet_fc_tgtport;
काष्ठा nvmet_fc_tgt_assoc;

काष्ठा nvmet_fc_ls_iod अणु		/* क्रम an LS RQST RCV */
	काष्ठा nvmefc_ls_rsp		*lsrsp;
	काष्ठा nvmefc_tgt_fcp_req	*fcpreq;	/* only अगर RS */

	काष्ठा list_head		ls_rcv_list; /* tgtport->ls_rcv_list */

	काष्ठा nvmet_fc_tgtport		*tgtport;
	काष्ठा nvmet_fc_tgt_assoc	*assoc;
	व्योम				*hosthandle;

	जोड़ nvmefc_ls_requests	*rqstbuf;
	जोड़ nvmefc_ls_responses	*rspbuf;
	u16				rqstdatalen;
	dma_addr_t			rspdma;

	काष्ठा scatterlist		sg[2];

	काष्ठा work_काष्ठा		work;
पूर्ण __aligned(माप(अचिन्हित दीर्घ दीर्घ));

काष्ठा nvmet_fc_ls_req_op अणु		/* क्रम an LS RQST XMT */
	काष्ठा nvmefc_ls_req		ls_req;

	काष्ठा nvmet_fc_tgtport		*tgtport;
	व्योम				*hosthandle;

	पूर्णांक				ls_error;
	काष्ठा list_head		lsreq_list; /* tgtport->ls_req_list */
	bool				req_queued;
पूर्ण;


/* desired maximum क्रम a single sequence - अगर sg list allows it */
#घोषणा NVMET_FC_MAX_SEQ_LENGTH		(256 * 1024)

क्रमागत nvmet_fcp_datadir अणु
	NVMET_FCP_NODATA,
	NVMET_FCP_WRITE,
	NVMET_FCP_READ,
	NVMET_FCP_ABORTED,
पूर्ण;

काष्ठा nvmet_fc_fcp_iod अणु
	काष्ठा nvmefc_tgt_fcp_req	*fcpreq;

	काष्ठा nvme_fc_cmd_iu		cmdiubuf;
	काष्ठा nvme_fc_ersp_iu		rspiubuf;
	dma_addr_t			rspdma;
	काष्ठा scatterlist		*next_sg;
	काष्ठा scatterlist		*data_sg;
	पूर्णांक				data_sg_cnt;
	u32				offset;
	क्रमागत nvmet_fcp_datadir		io_dir;
	bool				active;
	bool				पात;
	bool				पातed;
	bool				ग_लिखोdataactive;
	spinlock_t			flock;

	काष्ठा nvmet_req		req;
	काष्ठा work_काष्ठा		defer_work;

	काष्ठा nvmet_fc_tgtport		*tgtport;
	काष्ठा nvmet_fc_tgt_queue	*queue;

	काष्ठा list_head		fcp_list;	/* tgtport->fcp_list */
पूर्ण;

काष्ठा nvmet_fc_tgtport अणु
	काष्ठा nvmet_fc_target_port	fc_target_port;

	काष्ठा list_head		tgt_list; /* nvmet_fc_target_list */
	काष्ठा device			*dev;	/* dev क्रम dma mapping */
	काष्ठा nvmet_fc_target_ढाँचा	*ops;

	काष्ठा nvmet_fc_ls_iod		*iod;
	spinlock_t			lock;
	काष्ठा list_head		ls_rcv_list;
	काष्ठा list_head		ls_req_list;
	काष्ठा list_head		ls_busylist;
	काष्ठा list_head		assoc_list;
	काष्ठा list_head		host_list;
	काष्ठा ida			assoc_cnt;
	काष्ठा nvmet_fc_port_entry	*pe;
	काष्ठा kref			ref;
	u32				max_sg_cnt;
पूर्ण;

काष्ठा nvmet_fc_port_entry अणु
	काष्ठा nvmet_fc_tgtport		*tgtport;
	काष्ठा nvmet_port		*port;
	u64				node_name;
	u64				port_name;
	काष्ठा list_head		pe_list;
पूर्ण;

काष्ठा nvmet_fc_defer_fcp_req अणु
	काष्ठा list_head		req_list;
	काष्ठा nvmefc_tgt_fcp_req	*fcp_req;
पूर्ण;

काष्ठा nvmet_fc_tgt_queue अणु
	bool				ninetypercent;
	u16				qid;
	u16				sqsize;
	u16				ersp_ratio;
	__le16				sqhd;
	atomic_t			connected;
	atomic_t			sqtail;
	atomic_t			zrspcnt;
	atomic_t			rsn;
	spinlock_t			qlock;
	काष्ठा nvmet_cq			nvme_cq;
	काष्ठा nvmet_sq			nvme_sq;
	काष्ठा nvmet_fc_tgt_assoc	*assoc;
	काष्ठा list_head		fod_list;
	काष्ठा list_head		pending_cmd_list;
	काष्ठा list_head		avail_defer_list;
	काष्ठा workqueue_काष्ठा		*work_q;
	काष्ठा kref			ref;
	काष्ठा rcu_head			rcu;
	काष्ठा nvmet_fc_fcp_iod		fod[];		/* array of fcp_iods */
पूर्ण __aligned(माप(अचिन्हित दीर्घ दीर्घ));

काष्ठा nvmet_fc_hostport अणु
	काष्ठा nvmet_fc_tgtport		*tgtport;
	व्योम				*hosthandle;
	काष्ठा list_head		host_list;
	काष्ठा kref			ref;
	u8				invalid;
पूर्ण;

काष्ठा nvmet_fc_tgt_assoc अणु
	u64				association_id;
	u32				a_id;
	atomic_t			terminating;
	काष्ठा nvmet_fc_tgtport		*tgtport;
	काष्ठा nvmet_fc_hostport	*hostport;
	काष्ठा nvmet_fc_ls_iod		*rcv_disconn;
	काष्ठा list_head		a_list;
	काष्ठा nvmet_fc_tgt_queue __rcu	*queues[NVMET_NR_QUEUES + 1];
	काष्ठा kref			ref;
	काष्ठा work_काष्ठा		del_work;
	काष्ठा rcu_head			rcu;
पूर्ण;


अटल अंतरभूत पूर्णांक
nvmet_fc_iodnum(काष्ठा nvmet_fc_ls_iod *iodptr)
अणु
	वापस (iodptr - iodptr->tgtport->iod);
पूर्ण

अटल अंतरभूत पूर्णांक
nvmet_fc_fodnum(काष्ठा nvmet_fc_fcp_iod *fodptr)
अणु
	वापस (fodptr - fodptr->queue->fod);
पूर्ण


/*
 * Association and Connection IDs:
 *
 * Association ID will have अक्रमom number in upper 6 bytes and zero
 *   in lower 2 bytes
 *
 * Connection IDs will be Association ID with QID or'd in lower 2 bytes
 *
 * note: Association ID = Connection ID क्रम queue 0
 */
#घोषणा BYTES_FOR_QID			माप(u16)
#घोषणा BYTES_FOR_QID_SHIFT		(BYTES_FOR_QID * 8)
#घोषणा NVMET_FC_QUEUEID_MASK		((u64)((1 << BYTES_FOR_QID_SHIFT) - 1))

अटल अंतरभूत u64
nvmet_fc_makeconnid(काष्ठा nvmet_fc_tgt_assoc *assoc, u16 qid)
अणु
	वापस (assoc->association_id | qid);
पूर्ण

अटल अंतरभूत u64
nvmet_fc_getassociationid(u64 connectionid)
अणु
	वापस connectionid & ~NVMET_FC_QUEUEID_MASK;
पूर्ण

अटल अंतरभूत u16
nvmet_fc_getqueueid(u64 connectionid)
अणु
	वापस (u16)(connectionid & NVMET_FC_QUEUEID_MASK);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_fc_tgtport *
targetport_to_tgtport(काष्ठा nvmet_fc_target_port *targetport)
अणु
	वापस container_of(targetport, काष्ठा nvmet_fc_tgtport,
				 fc_target_port);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_fc_fcp_iod *
nvmet_req_to_fod(काष्ठा nvmet_req *nvme_req)
अणु
	वापस container_of(nvme_req, काष्ठा nvmet_fc_fcp_iod, req);
पूर्ण


/* *************************** Globals **************************** */


अटल DEFINE_SPINLOCK(nvmet_fc_tgtlock);

अटल LIST_HEAD(nvmet_fc_target_list);
अटल DEFINE_IDA(nvmet_fc_tgtport_cnt);
अटल LIST_HEAD(nvmet_fc_portentry_list);


अटल व्योम nvmet_fc_handle_ls_rqst_work(काष्ठा work_काष्ठा *work);
अटल व्योम nvmet_fc_fcp_rqst_op_defer_work(काष्ठा work_काष्ठा *work);
अटल व्योम nvmet_fc_tgt_a_put(काष्ठा nvmet_fc_tgt_assoc *assoc);
अटल पूर्णांक nvmet_fc_tgt_a_get(काष्ठा nvmet_fc_tgt_assoc *assoc);
अटल व्योम nvmet_fc_tgt_q_put(काष्ठा nvmet_fc_tgt_queue *queue);
अटल पूर्णांक nvmet_fc_tgt_q_get(काष्ठा nvmet_fc_tgt_queue *queue);
अटल व्योम nvmet_fc_tgtport_put(काष्ठा nvmet_fc_tgtport *tgtport);
अटल पूर्णांक nvmet_fc_tgtport_get(काष्ठा nvmet_fc_tgtport *tgtport);
अटल व्योम nvmet_fc_handle_fcp_rqst(काष्ठा nvmet_fc_tgtport *tgtport,
					काष्ठा nvmet_fc_fcp_iod *fod);
अटल व्योम nvmet_fc_delete_target_assoc(काष्ठा nvmet_fc_tgt_assoc *assoc);
अटल व्योम nvmet_fc_xmt_ls_rsp(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_ls_iod *iod);


/* *********************** FC-NVME DMA Handling **************************** */

/*
 * The fcloop device passes in a शून्य device poपूर्णांकer. Real LLD's will
 * pass in a valid device poपूर्णांकer. If शून्य is passed to the dma mapping
 * routines, depending on the platक्रमm, it may or may not succeed, and
 * may crash.
 *
 * As such:
 * Wrapper all the dma routines and check the dev poपूर्णांकer.
 *
 * If simple mappings (वापस just a dma address, we'll noop them,
 * वापसing a dma address of 0.
 *
 * On more complex mappings (dma_map_sg), a pseuकरो routine fills
 * in the scatter list, setting all dma addresses to 0.
 */

अटल अंतरभूत dma_addr_t
fc_dma_map_single(काष्ठा device *dev, व्योम *ptr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	वापस dev ? dma_map_single(dev, ptr, size, dir) : (dma_addr_t)0L;
पूर्ण

अटल अंतरभूत पूर्णांक
fc_dma_mapping_error(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस dev ? dma_mapping_error(dev, dma_addr) : 0;
पूर्ण

अटल अंतरभूत व्योम
fc_dma_unmap_single(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
	क्रमागत dma_data_direction dir)
अणु
	अगर (dev)
		dma_unmap_single(dev, addr, size, dir);
पूर्ण

अटल अंतरभूत व्योम
fc_dma_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	अगर (dev)
		dma_sync_single_क्रम_cpu(dev, addr, size, dir);
पूर्ण

अटल अंतरभूत व्योम
fc_dma_sync_single_क्रम_device(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	अगर (dev)
		dma_sync_single_क्रम_device(dev, addr, size, dir);
पूर्ण

/* pseuकरो dma_map_sg call */
अटल पूर्णांक
fc_map_sg(काष्ठा scatterlist *sg, पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	WARN_ON(nents == 0 || sg[0].length == 0);

	क्रम_each_sg(sg, s, nents, i) अणु
		s->dma_address = 0L;
#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
		s->dma_length = s->length;
#पूर्ण_अगर
	पूर्ण
	वापस nents;
पूर्ण

अटल अंतरभूत पूर्णांक
fc_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir)
अणु
	वापस dev ? dma_map_sg(dev, sg, nents, dir) : fc_map_sg(sg, nents);
पूर्ण

अटल अंतरभूत व्योम
fc_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir)
अणु
	अगर (dev)
		dma_unmap_sg(dev, sg, nents, dir);
पूर्ण


/* ********************** FC-NVME LS XMT Handling ************************* */


अटल व्योम
__nvmet_fc_finish_ls_req(काष्ठा nvmet_fc_ls_req_op *lsop)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = lsop->tgtport;
	काष्ठा nvmefc_ls_req *lsreq = &lsop->ls_req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgtport->lock, flags);

	अगर (!lsop->req_queued) अणु
		spin_unlock_irqrestore(&tgtport->lock, flags);
		वापस;
	पूर्ण

	list_del(&lsop->lsreq_list);

	lsop->req_queued = false;

	spin_unlock_irqrestore(&tgtport->lock, flags);

	fc_dma_unmap_single(tgtport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIसूचीECTIONAL);

	nvmet_fc_tgtport_put(tgtport);
पूर्ण

अटल पूर्णांक
__nvmet_fc_send_ls_req(काष्ठा nvmet_fc_tgtport *tgtport,
		काष्ठा nvmet_fc_ls_req_op *lsop,
		व्योम (*करोne)(काष्ठा nvmefc_ls_req *req, पूर्णांक status))
अणु
	काष्ठा nvmefc_ls_req *lsreq = &lsop->ls_req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!tgtport->ops->ls_req)
		वापस -EOPNOTSUPP;

	अगर (!nvmet_fc_tgtport_get(tgtport))
		वापस -ESHUTDOWN;

	lsreq->करोne = करोne;
	lsop->req_queued = false;
	INIT_LIST_HEAD(&lsop->lsreq_list);

	lsreq->rqstdma = fc_dma_map_single(tgtport->dev, lsreq->rqstaddr,
				  lsreq->rqstlen + lsreq->rsplen,
				  DMA_BIसूचीECTIONAL);
	अगर (fc_dma_mapping_error(tgtport->dev, lsreq->rqstdma)) अणु
		ret = -EFAULT;
		जाओ out_puttgtport;
	पूर्ण
	lsreq->rspdma = lsreq->rqstdma + lsreq->rqstlen;

	spin_lock_irqsave(&tgtport->lock, flags);

	list_add_tail(&lsop->lsreq_list, &tgtport->ls_req_list);

	lsop->req_queued = true;

	spin_unlock_irqrestore(&tgtport->lock, flags);

	ret = tgtport->ops->ls_req(&tgtport->fc_target_port, lsop->hosthandle,
				   lsreq);
	अगर (ret)
		जाओ out_unlink;

	वापस 0;

out_unlink:
	lsop->ls_error = ret;
	spin_lock_irqsave(&tgtport->lock, flags);
	lsop->req_queued = false;
	list_del(&lsop->lsreq_list);
	spin_unlock_irqrestore(&tgtport->lock, flags);
	fc_dma_unmap_single(tgtport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIसूचीECTIONAL);
out_puttgtport:
	nvmet_fc_tgtport_put(tgtport);

	वापस ret;
पूर्ण

अटल पूर्णांक
nvmet_fc_send_ls_req_async(काष्ठा nvmet_fc_tgtport *tgtport,
		काष्ठा nvmet_fc_ls_req_op *lsop,
		व्योम (*करोne)(काष्ठा nvmefc_ls_req *req, पूर्णांक status))
अणु
	/* करोn't रुको क्रम completion */

	वापस __nvmet_fc_send_ls_req(tgtport, lsop, करोne);
पूर्ण

अटल व्योम
nvmet_fc_disconnect_assoc_करोne(काष्ठा nvmefc_ls_req *lsreq, पूर्णांक status)
अणु
	काष्ठा nvmet_fc_ls_req_op *lsop =
		container_of(lsreq, काष्ठा nvmet_fc_ls_req_op, ls_req);

	__nvmet_fc_finish_ls_req(lsop);

	/* fc-nvme target करोesn't care about success or failure of cmd */

	kमुक्त(lsop);
पूर्ण

/*
 * This routine sends a FC-NVME LS to disconnect (aka terminate)
 * the FC-NVME Association.  Terminating the association also
 * terminates the FC-NVME connections (per queue, both admin and io
 * queues) that are part of the association. E.g. things are torn
 * करोwn, and the related FC-NVME Association ID and Connection IDs
 * become invalid.
 *
 * The behavior of the fc-nvme target is such that it's
 * understanding of the association and connections will implicitly
 * be torn करोwn. The action is implicit as it may be due to a loss of
 * connectivity with the fc-nvme host, so the target may never get a
 * response even अगर it tried.  As such, the action of this routine
 * is to asynchronously send the LS, ignore any results of the LS, and
 * जारी on with terminating the association. If the fc-nvme host
 * is present and receives the LS, it too can tear करोwn.
 */
अटल व्योम
nvmet_fc_xmt_disconnect_assoc(काष्ठा nvmet_fc_tgt_assoc *assoc)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = assoc->tgtport;
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *discon_rqst;
	काष्ठा fcnvme_ls_disconnect_assoc_acc *discon_acc;
	काष्ठा nvmet_fc_ls_req_op *lsop;
	काष्ठा nvmefc_ls_req *lsreq;
	पूर्णांक ret;

	/*
	 * If ls_req is शून्य or no hosthandle, it's an older lldd and no
	 * message is normal. Otherwise, send unless the hostport has
	 * alपढ़ोy been invalidated by the lldd.
	 */
	अगर (!tgtport->ops->ls_req || !assoc->hostport ||
	    assoc->hostport->invalid)
		वापस;

	lsop = kzalloc((माप(*lsop) +
			माप(*discon_rqst) + माप(*discon_acc) +
			tgtport->ops->lsrqst_priv_sz), GFP_KERNEL);
	अगर (!lsop) अणु
		dev_info(tgtport->dev,
			"{%d:%d} send Disconnect Association failed: ENOMEM\n",
			tgtport->fc_target_port.port_num, assoc->a_id);
		वापस;
	पूर्ण

	discon_rqst = (काष्ठा fcnvme_ls_disconnect_assoc_rqst *)&lsop[1];
	discon_acc = (काष्ठा fcnvme_ls_disconnect_assoc_acc *)&discon_rqst[1];
	lsreq = &lsop->ls_req;
	अगर (tgtport->ops->lsrqst_priv_sz)
		lsreq->निजी = (व्योम *)&discon_acc[1];
	अन्यथा
		lsreq->निजी = शून्य;

	lsop->tgtport = tgtport;
	lsop->hosthandle = assoc->hostport->hosthandle;

	nvmefc_fmt_lsreq_discon_assoc(lsreq, discon_rqst, discon_acc,
				assoc->association_id);

	ret = nvmet_fc_send_ls_req_async(tgtport, lsop,
				nvmet_fc_disconnect_assoc_करोne);
	अगर (ret) अणु
		dev_info(tgtport->dev,
			"{%d:%d} XMT Disconnect Association failed: %d\n",
			tgtport->fc_target_port.port_num, assoc->a_id, ret);
		kमुक्त(lsop);
	पूर्ण
पूर्ण


/* *********************** FC-NVME Port Management ************************ */


अटल पूर्णांक
nvmet_fc_alloc_ls_iodlist(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_ls_iod *iod;
	पूर्णांक i;

	iod = kसुस्मृति(NVMET_LS_CTX_COUNT, माप(काष्ठा nvmet_fc_ls_iod),
			GFP_KERNEL);
	अगर (!iod)
		वापस -ENOMEM;

	tgtport->iod = iod;

	क्रम (i = 0; i < NVMET_LS_CTX_COUNT; iod++, i++) अणु
		INIT_WORK(&iod->work, nvmet_fc_handle_ls_rqst_work);
		iod->tgtport = tgtport;
		list_add_tail(&iod->ls_rcv_list, &tgtport->ls_rcv_list);

		iod->rqstbuf = kzalloc(माप(जोड़ nvmefc_ls_requests) +
				       माप(जोड़ nvmefc_ls_responses),
				       GFP_KERNEL);
		अगर (!iod->rqstbuf)
			जाओ out_fail;

		iod->rspbuf = (जोड़ nvmefc_ls_responses *)&iod->rqstbuf[1];

		iod->rspdma = fc_dma_map_single(tgtport->dev, iod->rspbuf,
						माप(*iod->rspbuf),
						DMA_TO_DEVICE);
		अगर (fc_dma_mapping_error(tgtport->dev, iod->rspdma))
			जाओ out_fail;
	पूर्ण

	वापस 0;

out_fail:
	kमुक्त(iod->rqstbuf);
	list_del(&iod->ls_rcv_list);
	क्रम (iod--, i--; i >= 0; iod--, i--) अणु
		fc_dma_unmap_single(tgtport->dev, iod->rspdma,
				माप(*iod->rspbuf), DMA_TO_DEVICE);
		kमुक्त(iod->rqstbuf);
		list_del(&iod->ls_rcv_list);
	पूर्ण

	kमुक्त(iod);

	वापस -EFAULT;
पूर्ण

अटल व्योम
nvmet_fc_मुक्त_ls_iodlist(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_ls_iod *iod = tgtport->iod;
	पूर्णांक i;

	क्रम (i = 0; i < NVMET_LS_CTX_COUNT; iod++, i++) अणु
		fc_dma_unmap_single(tgtport->dev,
				iod->rspdma, माप(*iod->rspbuf),
				DMA_TO_DEVICE);
		kमुक्त(iod->rqstbuf);
		list_del(&iod->ls_rcv_list);
	पूर्ण
	kमुक्त(tgtport->iod);
पूर्ण

अटल काष्ठा nvmet_fc_ls_iod *
nvmet_fc_alloc_ls_iod(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_ls_iod *iod;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgtport->lock, flags);
	iod = list_first_entry_or_null(&tgtport->ls_rcv_list,
					काष्ठा nvmet_fc_ls_iod, ls_rcv_list);
	अगर (iod)
		list_move_tail(&iod->ls_rcv_list, &tgtport->ls_busylist);
	spin_unlock_irqrestore(&tgtport->lock, flags);
	वापस iod;
पूर्ण


अटल व्योम
nvmet_fc_मुक्त_ls_iod(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_ls_iod *iod)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgtport->lock, flags);
	list_move(&iod->ls_rcv_list, &tgtport->ls_rcv_list);
	spin_unlock_irqrestore(&tgtport->lock, flags);
पूर्ण

अटल व्योम
nvmet_fc_prep_fcp_iodlist(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = queue->fod;
	पूर्णांक i;

	क्रम (i = 0; i < queue->sqsize; fod++, i++) अणु
		INIT_WORK(&fod->defer_work, nvmet_fc_fcp_rqst_op_defer_work);
		fod->tgtport = tgtport;
		fod->queue = queue;
		fod->active = false;
		fod->पात = false;
		fod->पातed = false;
		fod->fcpreq = शून्य;
		list_add_tail(&fod->fcp_list, &queue->fod_list);
		spin_lock_init(&fod->flock);

		fod->rspdma = fc_dma_map_single(tgtport->dev, &fod->rspiubuf,
					माप(fod->rspiubuf), DMA_TO_DEVICE);
		अगर (fc_dma_mapping_error(tgtport->dev, fod->rspdma)) अणु
			list_del(&fod->fcp_list);
			क्रम (fod--, i--; i >= 0; fod--, i--) अणु
				fc_dma_unmap_single(tgtport->dev, fod->rspdma,
						माप(fod->rspiubuf),
						DMA_TO_DEVICE);
				fod->rspdma = 0L;
				list_del(&fod->fcp_list);
			पूर्ण

			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nvmet_fc_destroy_fcp_iodlist(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = queue->fod;
	पूर्णांक i;

	क्रम (i = 0; i < queue->sqsize; fod++, i++) अणु
		अगर (fod->rspdma)
			fc_dma_unmap_single(tgtport->dev, fod->rspdma,
				माप(fod->rspiubuf), DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल काष्ठा nvmet_fc_fcp_iod *
nvmet_fc_alloc_fcp_iod(काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod;

	lockdep_निश्चित_held(&queue->qlock);

	fod = list_first_entry_or_null(&queue->fod_list,
					काष्ठा nvmet_fc_fcp_iod, fcp_list);
	अगर (fod) अणु
		list_del(&fod->fcp_list);
		fod->active = true;
		/*
		 * no queue reference is taken, as it was taken by the
		 * queue lookup just prior to the allocation. The iod
		 * will "inherit" that reference.
		 */
	पूर्ण
	वापस fod;
पूर्ण


अटल व्योम
nvmet_fc_queue_fcp_req(काष्ठा nvmet_fc_tgtport *tgtport,
		       काष्ठा nvmet_fc_tgt_queue *queue,
		       काष्ठा nvmefc_tgt_fcp_req *fcpreq)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_निजी;

	/*
	 * put all admin cmds on hw queue id 0. All io commands go to
	 * the respective hw queue based on a modulo basis
	 */
	fcpreq->hwqid = queue->qid ?
			((queue->qid - 1) % tgtport->ops->max_hw_queues) : 0;

	nvmet_fc_handle_fcp_rqst(tgtport, fod);
पूर्ण

अटल व्योम
nvmet_fc_fcp_rqst_op_defer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod =
		container_of(work, काष्ठा nvmet_fc_fcp_iod, defer_work);

	/* Submit deferred IO क्रम processing */
	nvmet_fc_queue_fcp_req(fod->tgtport, fod->queue, fod->fcpreq);

पूर्ण

अटल व्योम
nvmet_fc_मुक्त_fcp_iod(काष्ठा nvmet_fc_tgt_queue *queue,
			काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	काष्ठा nvmet_fc_tgtport *tgtport = fod->tgtport;
	काष्ठा nvmet_fc_defer_fcp_req *deferfcp;
	अचिन्हित दीर्घ flags;

	fc_dma_sync_single_क्रम_cpu(tgtport->dev, fod->rspdma,
				माप(fod->rspiubuf), DMA_TO_DEVICE);

	fcpreq->nvmet_fc_निजी = शून्य;

	fod->active = false;
	fod->पात = false;
	fod->पातed = false;
	fod->ग_लिखोdataactive = false;
	fod->fcpreq = शून्य;

	tgtport->ops->fcp_req_release(&tgtport->fc_target_port, fcpreq);

	/* release the queue lookup reference on the completed IO */
	nvmet_fc_tgt_q_put(queue);

	spin_lock_irqsave(&queue->qlock, flags);
	deferfcp = list_first_entry_or_null(&queue->pending_cmd_list,
				काष्ठा nvmet_fc_defer_fcp_req, req_list);
	अगर (!deferfcp) अणु
		list_add_tail(&fod->fcp_list, &fod->queue->fod_list);
		spin_unlock_irqrestore(&queue->qlock, flags);
		वापस;
	पूर्ण

	/* Re-use the fod क्रम the next pending cmd that was deferred */
	list_del(&deferfcp->req_list);

	fcpreq = deferfcp->fcp_req;

	/* deferfcp can be reused क्रम another IO at a later date */
	list_add_tail(&deferfcp->req_list, &queue->avail_defer_list);

	spin_unlock_irqrestore(&queue->qlock, flags);

	/* Save NVME CMD IO in fod */
	स_नकल(&fod->cmdiubuf, fcpreq->rspaddr, fcpreq->rsplen);

	/* Setup new fcpreq to be processed */
	fcpreq->rspaddr = शून्य;
	fcpreq->rsplen  = 0;
	fcpreq->nvmet_fc_निजी = fod;
	fod->fcpreq = fcpreq;
	fod->active = true;

	/* inक्रमm LLDD IO is now being processed */
	tgtport->ops->defer_rcv(&tgtport->fc_target_port, fcpreq);

	/*
	 * Leave the queue lookup get reference taken when
	 * fod was originally allocated.
	 */

	queue_work(queue->work_q, &fod->defer_work);
पूर्ण

अटल काष्ठा nvmet_fc_tgt_queue *
nvmet_fc_alloc_target_queue(काष्ठा nvmet_fc_tgt_assoc *assoc,
			u16 qid, u16 sqsize)
अणु
	काष्ठा nvmet_fc_tgt_queue *queue;
	पूर्णांक ret;

	अगर (qid > NVMET_NR_QUEUES)
		वापस शून्य;

	queue = kzalloc(काष्ठा_size(queue, fod, sqsize), GFP_KERNEL);
	अगर (!queue)
		वापस शून्य;

	अगर (!nvmet_fc_tgt_a_get(assoc))
		जाओ out_मुक्त_queue;

	queue->work_q = alloc_workqueue("ntfc%d.%d.%d", 0, 0,
				assoc->tgtport->fc_target_port.port_num,
				assoc->a_id, qid);
	अगर (!queue->work_q)
		जाओ out_a_put;

	queue->qid = qid;
	queue->sqsize = sqsize;
	queue->assoc = assoc;
	INIT_LIST_HEAD(&queue->fod_list);
	INIT_LIST_HEAD(&queue->avail_defer_list);
	INIT_LIST_HEAD(&queue->pending_cmd_list);
	atomic_set(&queue->connected, 0);
	atomic_set(&queue->sqtail, 0);
	atomic_set(&queue->rsn, 1);
	atomic_set(&queue->zrspcnt, 0);
	spin_lock_init(&queue->qlock);
	kref_init(&queue->ref);

	nvmet_fc_prep_fcp_iodlist(assoc->tgtport, queue);

	ret = nvmet_sq_init(&queue->nvme_sq);
	अगर (ret)
		जाओ out_fail_iodlist;

	WARN_ON(assoc->queues[qid]);
	rcu_assign_poपूर्णांकer(assoc->queues[qid], queue);

	वापस queue;

out_fail_iodlist:
	nvmet_fc_destroy_fcp_iodlist(assoc->tgtport, queue);
	destroy_workqueue(queue->work_q);
out_a_put:
	nvmet_fc_tgt_a_put(assoc);
out_मुक्त_queue:
	kमुक्त(queue);
	वापस शून्य;
पूर्ण


अटल व्योम
nvmet_fc_tgt_queue_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_fc_tgt_queue *queue =
		container_of(ref, काष्ठा nvmet_fc_tgt_queue, ref);

	rcu_assign_poपूर्णांकer(queue->assoc->queues[queue->qid], शून्य);

	nvmet_fc_destroy_fcp_iodlist(queue->assoc->tgtport, queue);

	nvmet_fc_tgt_a_put(queue->assoc);

	destroy_workqueue(queue->work_q);

	kमुक्त_rcu(queue, rcu);
पूर्ण

अटल व्योम
nvmet_fc_tgt_q_put(काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	kref_put(&queue->ref, nvmet_fc_tgt_queue_मुक्त);
पूर्ण

अटल पूर्णांक
nvmet_fc_tgt_q_get(काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	वापस kref_get_unless_zero(&queue->ref);
पूर्ण


अटल व्योम
nvmet_fc_delete_target_queue(काष्ठा nvmet_fc_tgt_queue *queue)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = queue->assoc->tgtport;
	काष्ठा nvmet_fc_fcp_iod *fod = queue->fod;
	काष्ठा nvmet_fc_defer_fcp_req *deferfcp, *tempptr;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	bool disconnect;

	disconnect = atomic_xchg(&queue->connected, 0);

	/* अगर not connected, nothing to करो */
	अगर (!disconnect)
		वापस;

	spin_lock_irqsave(&queue->qlock, flags);
	/* पात outstanding io's */
	क्रम (i = 0; i < queue->sqsize; fod++, i++) अणु
		अगर (fod->active) अणु
			spin_lock(&fod->flock);
			fod->पात = true;
			/*
			 * only call lldd पात routine अगर रुकोing क्रम
			 * ग_लिखोdata. other outstanding ops should finish
			 * on their own.
			 */
			अगर (fod->ग_लिखोdataactive) अणु
				fod->पातed = true;
				spin_unlock(&fod->flock);
				tgtport->ops->fcp_पात(
					&tgtport->fc_target_port, fod->fcpreq);
			पूर्ण अन्यथा
				spin_unlock(&fod->flock);
		पूर्ण
	पूर्ण

	/* Cleanup defer'ed IOs in queue */
	list_क्रम_each_entry_safe(deferfcp, tempptr, &queue->avail_defer_list,
				req_list) अणु
		list_del(&deferfcp->req_list);
		kमुक्त(deferfcp);
	पूर्ण

	क्रम (;;) अणु
		deferfcp = list_first_entry_or_null(&queue->pending_cmd_list,
				काष्ठा nvmet_fc_defer_fcp_req, req_list);
		अगर (!deferfcp)
			अवरोध;

		list_del(&deferfcp->req_list);
		spin_unlock_irqrestore(&queue->qlock, flags);

		tgtport->ops->defer_rcv(&tgtport->fc_target_port,
				deferfcp->fcp_req);

		tgtport->ops->fcp_पात(&tgtport->fc_target_port,
				deferfcp->fcp_req);

		tgtport->ops->fcp_req_release(&tgtport->fc_target_port,
				deferfcp->fcp_req);

		/* release the queue lookup reference */
		nvmet_fc_tgt_q_put(queue);

		kमुक्त(deferfcp);

		spin_lock_irqsave(&queue->qlock, flags);
	पूर्ण
	spin_unlock_irqrestore(&queue->qlock, flags);

	flush_workqueue(queue->work_q);

	nvmet_sq_destroy(&queue->nvme_sq);

	nvmet_fc_tgt_q_put(queue);
पूर्ण

अटल काष्ठा nvmet_fc_tgt_queue *
nvmet_fc_find_target_queue(काष्ठा nvmet_fc_tgtport *tgtport,
				u64 connection_id)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc;
	काष्ठा nvmet_fc_tgt_queue *queue;
	u64 association_id = nvmet_fc_getassociationid(connection_id);
	u16 qid = nvmet_fc_getqueueid(connection_id);

	अगर (qid > NVMET_NR_QUEUES)
		वापस शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(assoc, &tgtport->assoc_list, a_list) अणु
		अगर (association_id == assoc->association_id) अणु
			queue = rcu_dereference(assoc->queues[qid]);
			अगर (queue &&
			    (!atomic_पढ़ो(&queue->connected) ||
			     !nvmet_fc_tgt_q_get(queue)))
				queue = शून्य;
			rcu_पढ़ो_unlock();
			वापस queue;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल व्योम
nvmet_fc_hostport_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_fc_hostport *hostport =
		container_of(ref, काष्ठा nvmet_fc_hostport, ref);
	काष्ठा nvmet_fc_tgtport *tgtport = hostport->tgtport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgtport->lock, flags);
	list_del(&hostport->host_list);
	spin_unlock_irqrestore(&tgtport->lock, flags);
	अगर (tgtport->ops->host_release && hostport->invalid)
		tgtport->ops->host_release(hostport->hosthandle);
	kमुक्त(hostport);
	nvmet_fc_tgtport_put(tgtport);
पूर्ण

अटल व्योम
nvmet_fc_hostport_put(काष्ठा nvmet_fc_hostport *hostport)
अणु
	kref_put(&hostport->ref, nvmet_fc_hostport_मुक्त);
पूर्ण

अटल पूर्णांक
nvmet_fc_hostport_get(काष्ठा nvmet_fc_hostport *hostport)
अणु
	वापस kref_get_unless_zero(&hostport->ref);
पूर्ण

अटल व्योम
nvmet_fc_मुक्त_hostport(काष्ठा nvmet_fc_hostport *hostport)
अणु
	/* अगर LLDD not implemented, leave as शून्य */
	अगर (!hostport || !hostport->hosthandle)
		वापस;

	nvmet_fc_hostport_put(hostport);
पूर्ण

अटल काष्ठा nvmet_fc_hostport *
nvmet_fc_match_hostport(काष्ठा nvmet_fc_tgtport *tgtport, व्योम *hosthandle)
अणु
	काष्ठा nvmet_fc_hostport *host;

	lockdep_निश्चित_held(&tgtport->lock);

	list_क्रम_each_entry(host, &tgtport->host_list, host_list) अणु
		अगर (host->hosthandle == hosthandle && !host->invalid) अणु
			अगर (nvmet_fc_hostport_get(host))
				वापस (host);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा nvmet_fc_hostport *
nvmet_fc_alloc_hostport(काष्ठा nvmet_fc_tgtport *tgtport, व्योम *hosthandle)
अणु
	काष्ठा nvmet_fc_hostport *newhost, *match = शून्य;
	अचिन्हित दीर्घ flags;

	/* अगर LLDD not implemented, leave as शून्य */
	अगर (!hosthandle)
		वापस शून्य;

	/*
	 * take reference क्रम what will be the newly allocated hostport अगर
	 * we end up using a new allocation
	 */
	अगर (!nvmet_fc_tgtport_get(tgtport))
		वापस ERR_PTR(-EINVAL);

	spin_lock_irqsave(&tgtport->lock, flags);
	match = nvmet_fc_match_hostport(tgtport, hosthandle);
	spin_unlock_irqrestore(&tgtport->lock, flags);

	अगर (match) अणु
		/* no new allocation - release reference */
		nvmet_fc_tgtport_put(tgtport);
		वापस match;
	पूर्ण

	newhost = kzalloc(माप(*newhost), GFP_KERNEL);
	अगर (!newhost) अणु
		/* no new allocation - release reference */
		nvmet_fc_tgtport_put(tgtport);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	spin_lock_irqsave(&tgtport->lock, flags);
	match = nvmet_fc_match_hostport(tgtport, hosthandle);
	अगर (match) अणु
		/* new allocation not needed */
		kमुक्त(newhost);
		newhost = match;
		/* no new allocation - release reference */
		nvmet_fc_tgtport_put(tgtport);
	पूर्ण अन्यथा अणु
		newhost->tgtport = tgtport;
		newhost->hosthandle = hosthandle;
		INIT_LIST_HEAD(&newhost->host_list);
		kref_init(&newhost->ref);

		list_add_tail(&newhost->host_list, &tgtport->host_list);
	पूर्ण
	spin_unlock_irqrestore(&tgtport->lock, flags);

	वापस newhost;
पूर्ण

अटल व्योम
nvmet_fc_delete_assoc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc =
		container_of(work, काष्ठा nvmet_fc_tgt_assoc, del_work);

	nvmet_fc_delete_target_assoc(assoc);
	nvmet_fc_tgt_a_put(assoc);
पूर्ण

अटल काष्ठा nvmet_fc_tgt_assoc *
nvmet_fc_alloc_target_assoc(काष्ठा nvmet_fc_tgtport *tgtport, व्योम *hosthandle)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc, *पंचांगpassoc;
	अचिन्हित दीर्घ flags;
	u64 ran;
	पूर्णांक idx;
	bool needअक्रमom = true;

	assoc = kzalloc(माप(*assoc), GFP_KERNEL);
	अगर (!assoc)
		वापस शून्य;

	idx = ida_simple_get(&tgtport->assoc_cnt, 0, 0, GFP_KERNEL);
	अगर (idx < 0)
		जाओ out_मुक्त_assoc;

	अगर (!nvmet_fc_tgtport_get(tgtport))
		जाओ out_ida;

	assoc->hostport = nvmet_fc_alloc_hostport(tgtport, hosthandle);
	अगर (IS_ERR(assoc->hostport))
		जाओ out_put;

	assoc->tgtport = tgtport;
	assoc->a_id = idx;
	INIT_LIST_HEAD(&assoc->a_list);
	kref_init(&assoc->ref);
	INIT_WORK(&assoc->del_work, nvmet_fc_delete_assoc);
	atomic_set(&assoc->terminating, 0);

	जबतक (needअक्रमom) अणु
		get_अक्रमom_bytes(&ran, माप(ran) - BYTES_FOR_QID);
		ran = ran << BYTES_FOR_QID_SHIFT;

		spin_lock_irqsave(&tgtport->lock, flags);
		needअक्रमom = false;
		list_क्रम_each_entry(पंचांगpassoc, &tgtport->assoc_list, a_list) अणु
			अगर (ran == पंचांगpassoc->association_id) अणु
				needअक्रमom = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!needअक्रमom) अणु
			assoc->association_id = ran;
			list_add_tail_rcu(&assoc->a_list, &tgtport->assoc_list);
		पूर्ण
		spin_unlock_irqrestore(&tgtport->lock, flags);
	पूर्ण

	वापस assoc;

out_put:
	nvmet_fc_tgtport_put(tgtport);
out_ida:
	ida_simple_हटाओ(&tgtport->assoc_cnt, idx);
out_मुक्त_assoc:
	kमुक्त(assoc);
	वापस शून्य;
पूर्ण

अटल व्योम
nvmet_fc_target_assoc_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc =
		container_of(ref, काष्ठा nvmet_fc_tgt_assoc, ref);
	काष्ठा nvmet_fc_tgtport *tgtport = assoc->tgtport;
	काष्ठा nvmet_fc_ls_iod	*oldls;
	अचिन्हित दीर्घ flags;

	/* Send Disconnect now that all i/o has completed */
	nvmet_fc_xmt_disconnect_assoc(assoc);

	nvmet_fc_मुक्त_hostport(assoc->hostport);
	spin_lock_irqsave(&tgtport->lock, flags);
	list_del_rcu(&assoc->a_list);
	oldls = assoc->rcv_disconn;
	spin_unlock_irqrestore(&tgtport->lock, flags);
	/* अगर pending Rcv Disconnect Association LS, send rsp now */
	अगर (oldls)
		nvmet_fc_xmt_ls_rsp(tgtport, oldls);
	ida_simple_हटाओ(&tgtport->assoc_cnt, assoc->a_id);
	dev_info(tgtport->dev,
		"{%d:%d} Association freed\n",
		tgtport->fc_target_port.port_num, assoc->a_id);
	kमुक्त_rcu(assoc, rcu);
	nvmet_fc_tgtport_put(tgtport);
पूर्ण

अटल व्योम
nvmet_fc_tgt_a_put(काष्ठा nvmet_fc_tgt_assoc *assoc)
अणु
	kref_put(&assoc->ref, nvmet_fc_target_assoc_मुक्त);
पूर्ण

अटल पूर्णांक
nvmet_fc_tgt_a_get(काष्ठा nvmet_fc_tgt_assoc *assoc)
अणु
	वापस kref_get_unless_zero(&assoc->ref);
पूर्ण

अटल व्योम
nvmet_fc_delete_target_assoc(काष्ठा nvmet_fc_tgt_assoc *assoc)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = assoc->tgtport;
	काष्ठा nvmet_fc_tgt_queue *queue;
	पूर्णांक i, terminating;

	terminating = atomic_xchg(&assoc->terminating, 1);

	/* अगर alपढ़ोy terminating, करो nothing */
	अगर (terminating)
		वापस;


	क्रम (i = NVMET_NR_QUEUES; i >= 0; i--) अणु
		rcu_पढ़ो_lock();
		queue = rcu_dereference(assoc->queues[i]);
		अगर (!queue) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		अगर (!nvmet_fc_tgt_q_get(queue)) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		rcu_पढ़ो_unlock();
		nvmet_fc_delete_target_queue(queue);
		nvmet_fc_tgt_q_put(queue);
	पूर्ण

	dev_info(tgtport->dev,
		"{%d:%d} Association deleted\n",
		tgtport->fc_target_port.port_num, assoc->a_id);

	nvmet_fc_tgt_a_put(assoc);
पूर्ण

अटल काष्ठा nvmet_fc_tgt_assoc *
nvmet_fc_find_target_assoc(काष्ठा nvmet_fc_tgtport *tgtport,
				u64 association_id)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc;
	काष्ठा nvmet_fc_tgt_assoc *ret = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(assoc, &tgtport->assoc_list, a_list) अणु
		अगर (association_id == assoc->association_id) अणु
			ret = assoc;
			अगर (!nvmet_fc_tgt_a_get(assoc))
				ret = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम
nvmet_fc_portentry_bind(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_port_entry *pe,
			काष्ठा nvmet_port *port)
अणु
	lockdep_निश्चित_held(&nvmet_fc_tgtlock);

	pe->tgtport = tgtport;
	tgtport->pe = pe;

	pe->port = port;
	port->priv = pe;

	pe->node_name = tgtport->fc_target_port.node_name;
	pe->port_name = tgtport->fc_target_port.port_name;
	INIT_LIST_HEAD(&pe->pe_list);

	list_add_tail(&pe->pe_list, &nvmet_fc_portentry_list);
पूर्ण

अटल व्योम
nvmet_fc_portentry_unbind(काष्ठा nvmet_fc_port_entry *pe)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	अगर (pe->tgtport)
		pe->tgtport->pe = शून्य;
	list_del(&pe->pe_list);
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);
पूर्ण

/*
 * called when a targetport deरेजिस्टरs. Breaks the relationship
 * with the nvmet port, but leaves the port_entry in place so that
 * re-registration can resume operation.
 */
अटल व्योम
nvmet_fc_portentry_unbind_tgt(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_port_entry *pe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	pe = tgtport->pe;
	अगर (pe)
		pe->tgtport = शून्य;
	tgtport->pe = शून्य;
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);
पूर्ण

/*
 * called when a new targetport is रेजिस्टरed. Looks in the
 * existing nvmet port_entries to see अगर the nvmet layer is
 * configured क्रम the targetport's wwn's. (the targetport existed,
 * nvmet configured, the lldd unरेजिस्टरed the tgtport, and is now
 * reरेजिस्टरing the same targetport).  If so, set the nvmet port
 * port entry on the targetport.
 */
अटल व्योम
nvmet_fc_portentry_rebind_tgt(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_port_entry *pe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_क्रम_each_entry(pe, &nvmet_fc_portentry_list, pe_list) अणु
		अगर (tgtport->fc_target_port.node_name == pe->node_name &&
		    tgtport->fc_target_port.port_name == pe->port_name) अणु
			WARN_ON(pe->tgtport);
			tgtport->pe = pe;
			pe->tgtport = tgtport;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);
पूर्ण

/**
 * nvme_fc_रेजिस्टर_targetport - transport entry poपूर्णांक called by an
 *                              LLDD to रेजिस्टर the existence of a local
 *                              NVME subystem FC port.
 * @pinfo:     poपूर्णांकer to inक्रमmation about the port to be रेजिस्टरed
 * @ढाँचा:  LLDD entrypoपूर्णांकs and operational parameters क्रम the port
 * @dev:       physical hardware device node port corresponds to. Will be
 *             used क्रम DMA mappings
 * @portptr:   poपूर्णांकer to a local port poपूर्णांकer. Upon success, the routine
 *             will allocate a nvme_fc_local_port काष्ठाure and place its
 *             address in the local port poपूर्णांकer. Upon failure, local port
 *             poपूर्णांकer will be set to शून्य.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvmet_fc_रेजिस्टर_targetport(काष्ठा nvmet_fc_port_info *pinfo,
			काष्ठा nvmet_fc_target_ढाँचा *ढाँचा,
			काष्ठा device *dev,
			काष्ठा nvmet_fc_target_port **portptr)
अणु
	काष्ठा nvmet_fc_tgtport *newrec;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx;

	अगर (!ढाँचा->xmt_ls_rsp || !ढाँचा->fcp_op ||
	    !ढाँचा->fcp_पात ||
	    !ढाँचा->fcp_req_release || !ढाँचा->targetport_delete ||
	    !ढाँचा->max_hw_queues || !ढाँचा->max_sgl_segments ||
	    !ढाँचा->max_dअगर_sgl_segments || !ढाँचा->dma_boundary) अणु
		ret = -EINVAL;
		जाओ out_regtgt_failed;
	पूर्ण

	newrec = kzalloc((माप(*newrec) + ढाँचा->target_priv_sz),
			 GFP_KERNEL);
	अगर (!newrec) अणु
		ret = -ENOMEM;
		जाओ out_regtgt_failed;
	पूर्ण

	idx = ida_simple_get(&nvmet_fc_tgtport_cnt, 0, 0, GFP_KERNEL);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out_fail_kमुक्त;
	पूर्ण

	अगर (!get_device(dev) && dev) अणु
		ret = -ENODEV;
		जाओ out_ida_put;
	पूर्ण

	newrec->fc_target_port.node_name = pinfo->node_name;
	newrec->fc_target_port.port_name = pinfo->port_name;
	अगर (ढाँचा->target_priv_sz)
		newrec->fc_target_port.निजी = &newrec[1];
	अन्यथा
		newrec->fc_target_port.निजी = शून्य;
	newrec->fc_target_port.port_id = pinfo->port_id;
	newrec->fc_target_port.port_num = idx;
	INIT_LIST_HEAD(&newrec->tgt_list);
	newrec->dev = dev;
	newrec->ops = ढाँचा;
	spin_lock_init(&newrec->lock);
	INIT_LIST_HEAD(&newrec->ls_rcv_list);
	INIT_LIST_HEAD(&newrec->ls_req_list);
	INIT_LIST_HEAD(&newrec->ls_busylist);
	INIT_LIST_HEAD(&newrec->assoc_list);
	INIT_LIST_HEAD(&newrec->host_list);
	kref_init(&newrec->ref);
	ida_init(&newrec->assoc_cnt);
	newrec->max_sg_cnt = ढाँचा->max_sgl_segments;

	ret = nvmet_fc_alloc_ls_iodlist(newrec);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_newrec;
	पूर्ण

	nvmet_fc_portentry_rebind_tgt(newrec);

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_add_tail(&newrec->tgt_list, &nvmet_fc_target_list);
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);

	*portptr = &newrec->fc_target_port;
	वापस 0;

out_मुक्त_newrec:
	put_device(dev);
out_ida_put:
	ida_simple_हटाओ(&nvmet_fc_tgtport_cnt, idx);
out_fail_kमुक्त:
	kमुक्त(newrec);
out_regtgt_failed:
	*portptr = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_रेजिस्टर_targetport);


अटल व्योम
nvmet_fc_मुक्त_tgtport(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport =
		container_of(ref, काष्ठा nvmet_fc_tgtport, ref);
	काष्ठा device *dev = tgtport->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_del(&tgtport->tgt_list);
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);

	nvmet_fc_मुक्त_ls_iodlist(tgtport);

	/* let the LLDD know we've finished tearing it करोwn */
	tgtport->ops->targetport_delete(&tgtport->fc_target_port);

	ida_simple_हटाओ(&nvmet_fc_tgtport_cnt,
			tgtport->fc_target_port.port_num);

	ida_destroy(&tgtport->assoc_cnt);

	kमुक्त(tgtport);

	put_device(dev);
पूर्ण

अटल व्योम
nvmet_fc_tgtport_put(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	kref_put(&tgtport->ref, nvmet_fc_मुक्त_tgtport);
पूर्ण

अटल पूर्णांक
nvmet_fc_tgtport_get(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	वापस kref_get_unless_zero(&tgtport->ref);
पूर्ण

अटल व्योम
__nvmet_fc_मुक्त_assocs(काष्ठा nvmet_fc_tgtport *tgtport)
अणु
	काष्ठा nvmet_fc_tgt_assoc *assoc;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(assoc, &tgtport->assoc_list, a_list) अणु
		अगर (!nvmet_fc_tgt_a_get(assoc))
			जारी;
		अगर (!schedule_work(&assoc->del_work))
			/* alपढ़ोy deleting - release local reference */
			nvmet_fc_tgt_a_put(assoc);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * nvmet_fc_invalidate_host - transport entry poपूर्णांक called by an LLDD
 *                       to हटाओ references to a hosthandle क्रम LS's.
 *
 * The nvmet-fc layer ensures that any references to the hosthandle
 * on the targetport are क्रमgotten (set to शून्य).  The LLDD will
 * typically call this when a login with a remote host port has been
 * lost, thus LS's क्रम the remote host port are no दीर्घer possible.
 *
 * If an LS request is outstanding to the targetport/hosthandle (or
 * issued concurrently with the call to invalidate the host), the
 * LLDD is responsible क्रम terminating/पातing the LS and completing
 * the LS request. It is recommended that these terminations/पातs
 * occur after calling to invalidate the host handle to aव्योम additional
 * retries by the nvmet-fc transport. The nvmet-fc transport may
 * जारी to reference host handle जबतक it cleans up outstanding
 * NVME associations. The nvmet-fc transport will call the
 * ops->host_release() callback to notअगरy the LLDD that all references
 * are complete and the related host handle can be recovered.
 * Note: अगर there are no references, the callback may be called beक्रमe
 * the invalidate host call वापसs.
 *
 * @target_port: poपूर्णांकer to the (रेजिस्टरed) target port that a prior
 *              LS was received on and which supplied the transport the
 *              hosthandle.
 * @hosthandle: the handle (poपूर्णांकer) that represents the host port
 *              that no दीर्घer has connectivity and that LS's should
 *              no दीर्घer be directed to.
 */
व्योम
nvmet_fc_invalidate_host(काष्ठा nvmet_fc_target_port *target_port,
			व्योम *hosthandle)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);
	काष्ठा nvmet_fc_tgt_assoc *assoc, *next;
	अचिन्हित दीर्घ flags;
	bool noassoc = true;

	spin_lock_irqsave(&tgtport->lock, flags);
	list_क्रम_each_entry_safe(assoc, next,
				&tgtport->assoc_list, a_list) अणु
		अगर (!assoc->hostport ||
		    assoc->hostport->hosthandle != hosthandle)
			जारी;
		अगर (!nvmet_fc_tgt_a_get(assoc))
			जारी;
		assoc->hostport->invalid = 1;
		noassoc = false;
		अगर (!schedule_work(&assoc->del_work))
			/* alपढ़ोy deleting - release local reference */
			nvmet_fc_tgt_a_put(assoc);
	पूर्ण
	spin_unlock_irqrestore(&tgtport->lock, flags);

	/* अगर there's nothing to रुको क्रम - call the callback */
	अगर (noassoc && tgtport->ops->host_release)
		tgtport->ops->host_release(hosthandle);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_invalidate_host);

/*
 * nvmet layer has called to terminate an association
 */
अटल व्योम
nvmet_fc_delete_ctrl(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport, *next;
	काष्ठा nvmet_fc_tgt_assoc *assoc;
	काष्ठा nvmet_fc_tgt_queue *queue;
	अचिन्हित दीर्घ flags;
	bool found_ctrl = false;

	/* this is a bit ugly, but करोn't want to make locks layered */
	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_क्रम_each_entry_safe(tgtport, next, &nvmet_fc_target_list,
			tgt_list) अणु
		अगर (!nvmet_fc_tgtport_get(tgtport))
			जारी;
		spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(assoc, &tgtport->assoc_list, a_list) अणु
			queue = rcu_dereference(assoc->queues[0]);
			अगर (queue && queue->nvme_sq.ctrl == ctrl) अणु
				अगर (nvmet_fc_tgt_a_get(assoc))
					found_ctrl = true;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();

		nvmet_fc_tgtport_put(tgtport);

		अगर (found_ctrl) अणु
			अगर (!schedule_work(&assoc->del_work))
				/* alपढ़ोy deleting - release local reference */
				nvmet_fc_tgt_a_put(assoc);
			वापस;
		पूर्ण

		spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	पूर्ण
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);
पूर्ण

/**
 * nvme_fc_unरेजिस्टर_targetport - transport entry poपूर्णांक called by an
 *                              LLDD to deरेजिस्टर/हटाओ a previously
 *                              रेजिस्टरed a local NVME subप्रणाली FC port.
 * @target_port: poपूर्णांकer to the (रेजिस्टरed) target port that is to be
 *               deरेजिस्टरed.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvmet_fc_unरेजिस्टर_targetport(काष्ठा nvmet_fc_target_port *target_port)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);

	nvmet_fc_portentry_unbind_tgt(tgtport);

	/* terminate any outstanding associations */
	__nvmet_fc_मुक्त_assocs(tgtport);

	/*
	 * should terminate LS's as well. However, LS's will be generated
	 * at the tail end of association termination, so they likely करोn't
	 * exist yet. And even अगर they did, it's worthजबतक to just let
	 * them finish and targetport ref counting will clean things up.
	 */

	nvmet_fc_tgtport_put(tgtport);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_unरेजिस्टर_targetport);


/* ********************** FC-NVME LS RCV Handling ************************* */


अटल व्योम
nvmet_fc_ls_create_association(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_ls_iod *iod)
अणु
	काष्ठा fcnvme_ls_cr_assoc_rqst *rqst = &iod->rqstbuf->rq_cr_assoc;
	काष्ठा fcnvme_ls_cr_assoc_acc *acc = &iod->rspbuf->rsp_cr_assoc;
	काष्ठा nvmet_fc_tgt_queue *queue;
	पूर्णांक ret = 0;

	स_रखो(acc, 0, माप(*acc));

	/*
	 * FC-NVME spec changes. There are initiators sending dअगरferent
	 * lengths as padding sizes क्रम Create Association Cmd descriptor
	 * was incorrect.
	 * Accept anything of "minimum" length. Assume क्रमmat per 1.15
	 * spec (with HOSTID reduced to 16 bytes), ignore how दीर्घ the
	 * trailing pad length is.
	 */
	अगर (iod->rqstdatalen < FCNVME_LSDESC_CRA_RQST_MINLEN)
		ret = VERR_CR_ASSOC_LEN;
	अन्यथा अगर (be32_to_cpu(rqst->desc_list_len) <
			FCNVME_LSDESC_CRA_RQST_MIN_LISTLEN)
		ret = VERR_CR_ASSOC_RQST_LEN;
	अन्यथा अगर (rqst->assoc_cmd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CREATE_ASSOC_CMD))
		ret = VERR_CR_ASSOC_CMD;
	अन्यथा अगर (be32_to_cpu(rqst->assoc_cmd.desc_len) <
			FCNVME_LSDESC_CRA_CMD_DESC_MIN_DESCLEN)
		ret = VERR_CR_ASSOC_CMD_LEN;
	अन्यथा अगर (!rqst->assoc_cmd.ersp_ratio ||
		 (be16_to_cpu(rqst->assoc_cmd.ersp_ratio) >=
				be16_to_cpu(rqst->assoc_cmd.sqsize)))
		ret = VERR_ERSP_RATIO;

	अन्यथा अणु
		/* new association w/ admin queue */
		iod->assoc = nvmet_fc_alloc_target_assoc(
						tgtport, iod->hosthandle);
		अगर (!iod->assoc)
			ret = VERR_ASSOC_ALLOC_FAIL;
		अन्यथा अणु
			queue = nvmet_fc_alloc_target_queue(iod->assoc, 0,
					be16_to_cpu(rqst->assoc_cmd.sqsize));
			अगर (!queue)
				ret = VERR_QUEUE_ALLOC_FAIL;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(tgtport->dev,
			"Create Association LS failed: %s\n",
			validation_errors[ret]);
		iod->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(acc,
				माप(*acc), rqst->w0.ls_cmd,
				FCNVME_RJT_RC_LOGIC,
				FCNVME_RJT_EXP_NONE, 0);
		वापस;
	पूर्ण

	queue->ersp_ratio = be16_to_cpu(rqst->assoc_cmd.ersp_ratio);
	atomic_set(&queue->connected, 1);
	queue->sqhd = 0;	/* best place to init value */

	dev_info(tgtport->dev,
		"{%d:%d} Association created\n",
		tgtport->fc_target_port.port_num, iod->assoc->a_id);

	/* क्रमmat a response */

	iod->lsrsp->rsplen = माप(*acc);

	nvme_fc_क्रमmat_rsp_hdr(acc, FCNVME_LS_ACC,
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_cr_assoc_acc)),
			FCNVME_LS_CREATE_ASSOCIATION);
	acc->associd.desc_tag = cpu_to_be32(FCNVME_LSDESC_ASSOC_ID);
	acc->associd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id));
	acc->associd.association_id =
			cpu_to_be64(nvmet_fc_makeconnid(iod->assoc, 0));
	acc->connectid.desc_tag = cpu_to_be32(FCNVME_LSDESC_CONN_ID);
	acc->connectid.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_conn_id));
	acc->connectid.connection_id = acc->associd.association_id;
पूर्ण

अटल व्योम
nvmet_fc_ls_create_connection(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_ls_iod *iod)
अणु
	काष्ठा fcnvme_ls_cr_conn_rqst *rqst = &iod->rqstbuf->rq_cr_conn;
	काष्ठा fcnvme_ls_cr_conn_acc *acc = &iod->rspbuf->rsp_cr_conn;
	काष्ठा nvmet_fc_tgt_queue *queue;
	पूर्णांक ret = 0;

	स_रखो(acc, 0, माप(*acc));

	अगर (iod->rqstdatalen < माप(काष्ठा fcnvme_ls_cr_conn_rqst))
		ret = VERR_CR_CONN_LEN;
	अन्यथा अगर (rqst->desc_list_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_cr_conn_rqst)))
		ret = VERR_CR_CONN_RQST_LEN;
	अन्यथा अगर (rqst->associd.desc_tag != cpu_to_be32(FCNVME_LSDESC_ASSOC_ID))
		ret = VERR_ASSOC_ID;
	अन्यथा अगर (rqst->associd.desc_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id)))
		ret = VERR_ASSOC_ID_LEN;
	अन्यथा अगर (rqst->connect_cmd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CREATE_CONN_CMD))
		ret = VERR_CR_CONN_CMD;
	अन्यथा अगर (rqst->connect_cmd.desc_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_cr_conn_cmd)))
		ret = VERR_CR_CONN_CMD_LEN;
	अन्यथा अगर (!rqst->connect_cmd.ersp_ratio ||
		 (be16_to_cpu(rqst->connect_cmd.ersp_ratio) >=
				be16_to_cpu(rqst->connect_cmd.sqsize)))
		ret = VERR_ERSP_RATIO;

	अन्यथा अणु
		/* new io queue */
		iod->assoc = nvmet_fc_find_target_assoc(tgtport,
				be64_to_cpu(rqst->associd.association_id));
		अगर (!iod->assoc)
			ret = VERR_NO_ASSOC;
		अन्यथा अणु
			queue = nvmet_fc_alloc_target_queue(iod->assoc,
					be16_to_cpu(rqst->connect_cmd.qid),
					be16_to_cpu(rqst->connect_cmd.sqsize));
			अगर (!queue)
				ret = VERR_QUEUE_ALLOC_FAIL;

			/* release get taken in nvmet_fc_find_target_assoc */
			nvmet_fc_tgt_a_put(iod->assoc);
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(tgtport->dev,
			"Create Connection LS failed: %s\n",
			validation_errors[ret]);
		iod->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(acc,
				माप(*acc), rqst->w0.ls_cmd,
				(ret == VERR_NO_ASSOC) ?
					FCNVME_RJT_RC_INV_ASSOC :
					FCNVME_RJT_RC_LOGIC,
				FCNVME_RJT_EXP_NONE, 0);
		वापस;
	पूर्ण

	queue->ersp_ratio = be16_to_cpu(rqst->connect_cmd.ersp_ratio);
	atomic_set(&queue->connected, 1);
	queue->sqhd = 0;	/* best place to init value */

	/* क्रमmat a response */

	iod->lsrsp->rsplen = माप(*acc);

	nvme_fc_क्रमmat_rsp_hdr(acc, FCNVME_LS_ACC,
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_ls_cr_conn_acc)),
			FCNVME_LS_CREATE_CONNECTION);
	acc->connectid.desc_tag = cpu_to_be32(FCNVME_LSDESC_CONN_ID);
	acc->connectid.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_conn_id));
	acc->connectid.connection_id =
			cpu_to_be64(nvmet_fc_makeconnid(iod->assoc,
				be16_to_cpu(rqst->connect_cmd.qid)));
पूर्ण

/*
 * Returns true अगर the LS response is to be transmit
 * Returns false अगर the LS response is to be delayed
 */
अटल पूर्णांक
nvmet_fc_ls_disconnect(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_ls_iod *iod)
अणु
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *rqst =
						&iod->rqstbuf->rq_dis_assoc;
	काष्ठा fcnvme_ls_disconnect_assoc_acc *acc =
						&iod->rspbuf->rsp_dis_assoc;
	काष्ठा nvmet_fc_tgt_assoc *assoc = शून्य;
	काष्ठा nvmet_fc_ls_iod *oldls = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	स_रखो(acc, 0, माप(*acc));

	ret = nvmefc_vldt_lsreq_discon_assoc(iod->rqstdatalen, rqst);
	अगर (!ret) अणु
		/* match an active association - takes an assoc ref अगर !शून्य */
		assoc = nvmet_fc_find_target_assoc(tgtport,
				be64_to_cpu(rqst->associd.association_id));
		iod->assoc = assoc;
		अगर (!assoc)
			ret = VERR_NO_ASSOC;
	पूर्ण

	अगर (ret || !assoc) अणु
		dev_err(tgtport->dev,
			"Disconnect LS failed: %s\n",
			validation_errors[ret]);
		iod->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(acc,
				माप(*acc), rqst->w0.ls_cmd,
				(ret == VERR_NO_ASSOC) ?
					FCNVME_RJT_RC_INV_ASSOC :
					FCNVME_RJT_RC_LOGIC,
				FCNVME_RJT_EXP_NONE, 0);
		वापस true;
	पूर्ण

	/* क्रमmat a response */

	iod->lsrsp->rsplen = माप(*acc);

	nvme_fc_क्रमmat_rsp_hdr(acc, FCNVME_LS_ACC,
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_disconnect_assoc_acc)),
			FCNVME_LS_DISCONNECT_ASSOC);

	/* release get taken in nvmet_fc_find_target_assoc */
	nvmet_fc_tgt_a_put(assoc);

	/*
	 * The rules क्रम LS response says the response cannot
	 * go back until ABTS's have been sent क्रम all outstanding
	 * I/O and a Disconnect Association LS has been sent.
	 * So... save off the Disconnect LS to send the response
	 * later. If there was a prior LS alपढ़ोy saved, replace
	 * it with the newer one and send a can't perक्रमm reject
	 * on the older one.
	 */
	spin_lock_irqsave(&tgtport->lock, flags);
	oldls = assoc->rcv_disconn;
	assoc->rcv_disconn = iod;
	spin_unlock_irqrestore(&tgtport->lock, flags);

	nvmet_fc_delete_target_assoc(assoc);

	अगर (oldls) अणु
		dev_info(tgtport->dev,
			"{%d:%d} Multiple Disconnect Association LS's "
			"received\n",
			tgtport->fc_target_port.port_num, assoc->a_id);
		/* overग_लिखो good response with bogus failure */
		oldls->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(oldls->rspbuf,
						माप(*iod->rspbuf),
						/* ok to use rqst, LS is same */
						rqst->w0.ls_cmd,
						FCNVME_RJT_RC_UNAB,
						FCNVME_RJT_EXP_NONE, 0);
		nvmet_fc_xmt_ls_rsp(tgtport, oldls);
	पूर्ण

	वापस false;
पूर्ण


/* *********************** NVME Ctrl Routines **************************** */


अटल व्योम nvmet_fc_fcp_nvme_cmd_करोne(काष्ठा nvmet_req *nvme_req);

अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_fc_tgt_fcp_ops;

अटल व्योम
nvmet_fc_xmt_ls_rsp_करोne(काष्ठा nvmefc_ls_rsp *lsrsp)
अणु
	काष्ठा nvmet_fc_ls_iod *iod = lsrsp->nvme_fc_निजी;
	काष्ठा nvmet_fc_tgtport *tgtport = iod->tgtport;

	fc_dma_sync_single_क्रम_cpu(tgtport->dev, iod->rspdma,
				माप(*iod->rspbuf), DMA_TO_DEVICE);
	nvmet_fc_मुक्त_ls_iod(tgtport, iod);
	nvmet_fc_tgtport_put(tgtport);
पूर्ण

अटल व्योम
nvmet_fc_xmt_ls_rsp(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_ls_iod *iod)
अणु
	पूर्णांक ret;

	fc_dma_sync_single_क्रम_device(tgtport->dev, iod->rspdma,
				  माप(*iod->rspbuf), DMA_TO_DEVICE);

	ret = tgtport->ops->xmt_ls_rsp(&tgtport->fc_target_port, iod->lsrsp);
	अगर (ret)
		nvmet_fc_xmt_ls_rsp_करोne(iod->lsrsp);
पूर्ण

/*
 * Actual processing routine क्रम received FC-NVME LS Requests from the LLD
 */
अटल व्योम
nvmet_fc_handle_ls_rqst(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_ls_iod *iod)
अणु
	काष्ठा fcnvme_ls_rqst_w0 *w0 = &iod->rqstbuf->rq_cr_assoc.w0;
	bool sendrsp = true;

	iod->lsrsp->nvme_fc_निजी = iod;
	iod->lsrsp->rspbuf = iod->rspbuf;
	iod->lsrsp->rspdma = iod->rspdma;
	iod->lsrsp->करोne = nvmet_fc_xmt_ls_rsp_करोne;
	/* Be preventative. handlers will later set to valid length */
	iod->lsrsp->rsplen = 0;

	iod->assoc = शून्य;

	/*
	 * handlers:
	 *   parse request input, execute the request, and क्रमmat the
	 *   LS response
	 */
	चयन (w0->ls_cmd) अणु
	हाल FCNVME_LS_CREATE_ASSOCIATION:
		/* Creates Association and initial Admin Queue/Connection */
		nvmet_fc_ls_create_association(tgtport, iod);
		अवरोध;
	हाल FCNVME_LS_CREATE_CONNECTION:
		/* Creates an IO Queue/Connection */
		nvmet_fc_ls_create_connection(tgtport, iod);
		अवरोध;
	हाल FCNVME_LS_DISCONNECT_ASSOC:
		/* Terminate a Queue/Connection or the Association */
		sendrsp = nvmet_fc_ls_disconnect(tgtport, iod);
		अवरोध;
	शेष:
		iod->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(iod->rspbuf,
				माप(*iod->rspbuf), w0->ls_cmd,
				FCNVME_RJT_RC_INVAL, FCNVME_RJT_EXP_NONE, 0);
	पूर्ण

	अगर (sendrsp)
		nvmet_fc_xmt_ls_rsp(tgtport, iod);
पूर्ण

/*
 * Actual processing routine क्रम received FC-NVME LS Requests from the LLD
 */
अटल व्योम
nvmet_fc_handle_ls_rqst_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_fc_ls_iod *iod =
		container_of(work, काष्ठा nvmet_fc_ls_iod, work);
	काष्ठा nvmet_fc_tgtport *tgtport = iod->tgtport;

	nvmet_fc_handle_ls_rqst(tgtport, iod);
पूर्ण


/**
 * nvmet_fc_rcv_ls_req - transport entry poपूर्णांक called by an LLDD
 *                       upon the reception of a NVME LS request.
 *
 * The nvmet-fc layer will copy payload to an पूर्णांकernal काष्ठाure क्रम
 * processing.  As such, upon completion of the routine, the LLDD may
 * immediately मुक्त/reuse the LS request buffer passed in the call.
 *
 * If this routine वापसs error, the LLDD should पात the exchange.
 *
 * @target_port: poपूर्णांकer to the (रेजिस्टरed) target port the LS was
 *              received on.
 * @hosthandle: poपूर्णांकer to the host specअगरic data, माला_लो stored in iod.
 * @lsrsp:      poपूर्णांकer to a lsrsp काष्ठाure to be used to reference
 *              the exchange corresponding to the LS.
 * @lsreqbuf:   poपूर्णांकer to the buffer containing the LS Request
 * @lsreqbuf_len: length, in bytes, of the received LS request
 */
पूर्णांक
nvmet_fc_rcv_ls_req(काष्ठा nvmet_fc_target_port *target_port,
			व्योम *hosthandle,
			काष्ठा nvmefc_ls_rsp *lsrsp,
			व्योम *lsreqbuf, u32 lsreqbuf_len)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);
	काष्ठा nvmet_fc_ls_iod *iod;
	काष्ठा fcnvme_ls_rqst_w0 *w0 = (काष्ठा fcnvme_ls_rqst_w0 *)lsreqbuf;

	अगर (lsreqbuf_len > माप(जोड़ nvmefc_ls_requests)) अणु
		dev_info(tgtport->dev,
			"RCV %s LS failed: payload too large (%d)\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "",
			lsreqbuf_len);
		वापस -E2BIG;
	पूर्ण

	अगर (!nvmet_fc_tgtport_get(tgtport)) अणु
		dev_info(tgtport->dev,
			"RCV %s LS failed: target deleting\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		वापस -ESHUTDOWN;
	पूर्ण

	iod = nvmet_fc_alloc_ls_iod(tgtport);
	अगर (!iod) अणु
		dev_info(tgtport->dev,
			"RCV %s LS failed: context allocation failed\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		nvmet_fc_tgtport_put(tgtport);
		वापस -ENOENT;
	पूर्ण

	iod->lsrsp = lsrsp;
	iod->fcpreq = शून्य;
	स_नकल(iod->rqstbuf, lsreqbuf, lsreqbuf_len);
	iod->rqstdatalen = lsreqbuf_len;
	iod->hosthandle = hosthandle;

	schedule_work(&iod->work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_rcv_ls_req);


/*
 * **********************
 * Start of FCP handling
 * **********************
 */

अटल पूर्णांक
nvmet_fc_alloc_tgt_pgs(काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक nent;

	sg = sgl_alloc(fod->req.transfer_len, GFP_KERNEL, &nent);
	अगर (!sg)
		जाओ out;

	fod->data_sg = sg;
	fod->data_sg_cnt = nent;
	fod->data_sg_cnt = fc_dma_map_sg(fod->tgtport->dev, sg, nent,
				((fod->io_dir == NVMET_FCP_WRITE) ?
					DMA_FROM_DEVICE : DMA_TO_DEVICE));
				/* note: ग_लिखो from initiator perspective */
	fod->next_sg = fod->data_sg;

	वापस 0;

out:
	वापस NVME_SC_INTERNAL;
पूर्ण

अटल व्योम
nvmet_fc_मुक्त_tgt_pgs(काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	अगर (!fod->data_sg || !fod->data_sg_cnt)
		वापस;

	fc_dma_unmap_sg(fod->tgtport->dev, fod->data_sg, fod->data_sg_cnt,
				((fod->io_dir == NVMET_FCP_WRITE) ?
					DMA_FROM_DEVICE : DMA_TO_DEVICE));
	sgl_मुक्त(fod->data_sg);
	fod->data_sg = शून्य;
	fod->data_sg_cnt = 0;
पूर्ण


अटल bool
queue_90percent_full(काष्ठा nvmet_fc_tgt_queue *q, u32 sqhd)
अणु
	u32 sqtail, used;

	/* egad, this is ugly. And sqtail is just a best guess */
	sqtail = atomic_पढ़ो(&q->sqtail) % q->sqsize;

	used = (sqtail < sqhd) ? (sqtail + q->sqsize - sqhd) : (sqtail - sqhd);
	वापस ((used * 10) >= (((u32)(q->sqsize - 1) * 9)));
पूर्ण

/*
 * Prep RSP payload.
 * May be a NVMET_FCOP_RSP or NVMET_FCOP_READDATA_RSP op
 */
अटल व्योम
nvmet_fc_prep_fcp_rsp(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा nvme_fc_ersp_iu *ersp = &fod->rspiubuf;
	काष्ठा nvme_common_command *sqe = &fod->cmdiubuf.sqe.common;
	काष्ठा nvme_completion *cqe = &ersp->cqe;
	u32 *cqewd = (u32 *)cqe;
	bool send_ersp = false;
	u32 rsn, rspcnt, xfr_length;

	अगर (fod->fcpreq->op == NVMET_FCOP_READDATA_RSP)
		xfr_length = fod->req.transfer_len;
	अन्यथा
		xfr_length = fod->offset;

	/*
	 * check to see अगर we can send a 0's rsp.
	 *   Note: to send a 0's response, the NVME-FC host transport will
	 *   recreate the CQE. The host transport knows: sq id, SQHD (last
	 *   seen in an ersp), and command_id. Thus it will create a
	 *   zero-filled CQE with those known fields filled in. Transport
	 *   must send an ersp क्रम any condition where the cqe won't match
	 *   this.
	 *
	 * Here are the FC-NVME mandated हालs where we must send an ersp:
	 *  every N responses, where N=ersp_ratio
	 *  क्रमce fabric commands to send ersp's (not in FC-NVME but good
	 *    practice)
	 *  normal cmds: any समय status is non-zero, or status is zero
	 *     but words 0 or 1 are non-zero.
	 *  the SQ is 90% or more full
	 *  the cmd is a fused command
	 *  transferred data length not equal to cmd iu length
	 */
	rspcnt = atomic_inc_वापस(&fod->queue->zrspcnt);
	अगर (!(rspcnt % fod->queue->ersp_ratio) ||
	    nvme_is_fabrics((काष्ठा nvme_command *) sqe) ||
	    xfr_length != fod->req.transfer_len ||
	    (le16_to_cpu(cqe->status) & 0xFFFE) || cqewd[0] || cqewd[1] ||
	    (sqe->flags & (NVME_CMD_FUSE_FIRST | NVME_CMD_FUSE_SECOND)) ||
	    queue_90percent_full(fod->queue, le16_to_cpu(cqe->sq_head)))
		send_ersp = true;

	/* re-set the fields */
	fod->fcpreq->rspaddr = ersp;
	fod->fcpreq->rspdma = fod->rspdma;

	अगर (!send_ersp) अणु
		स_रखो(ersp, 0, NVME_FC_SIZखातापूर्ण_ZEROS_RSP);
		fod->fcpreq->rsplen = NVME_FC_SIZखातापूर्ण_ZEROS_RSP;
	पूर्ण अन्यथा अणु
		ersp->iu_len = cpu_to_be16(माप(*ersp)/माप(u32));
		rsn = atomic_inc_वापस(&fod->queue->rsn);
		ersp->rsn = cpu_to_be32(rsn);
		ersp->xfrd_len = cpu_to_be32(xfr_length);
		fod->fcpreq->rsplen = माप(*ersp);
	पूर्ण

	fc_dma_sync_single_क्रम_device(tgtport->dev, fod->rspdma,
				  माप(fod->rspiubuf), DMA_TO_DEVICE);
पूर्ण

अटल व्योम nvmet_fc_xmt_fcp_op_करोne(काष्ठा nvmefc_tgt_fcp_req *fcpreq);

अटल व्योम
nvmet_fc_पात_op(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;

	/* data no दीर्घer needed */
	nvmet_fc_मुक्त_tgt_pgs(fod);

	/*
	 * अगर an ABTS was received or we issued the fcp_पात early
	 * करोn't call पात routine again.
	 */
	/* no need to take lock - lock was taken earlier to get here */
	अगर (!fod->पातed)
		tgtport->ops->fcp_पात(&tgtport->fc_target_port, fcpreq);

	nvmet_fc_मुक्त_fcp_iod(fod->queue, fod);
पूर्ण

अटल व्योम
nvmet_fc_xmt_fcp_rsp(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	पूर्णांक ret;

	fod->fcpreq->op = NVMET_FCOP_RSP;
	fod->fcpreq->समयout = 0;

	nvmet_fc_prep_fcp_rsp(tgtport, fod);

	ret = tgtport->ops->fcp_op(&tgtport->fc_target_port, fod->fcpreq);
	अगर (ret)
		nvmet_fc_पात_op(tgtport, fod);
पूर्ण

अटल व्योम
nvmet_fc_transfer_fcp_data(काष्ठा nvmet_fc_tgtport *tgtport,
				काष्ठा nvmet_fc_fcp_iod *fod, u8 op)
अणु
	काष्ठा nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	काष्ठा scatterlist *sg = fod->next_sg;
	अचिन्हित दीर्घ flags;
	u32 reमुख्यinglen = fod->req.transfer_len - fod->offset;
	u32 tlen = 0;
	पूर्णांक ret;

	fcpreq->op = op;
	fcpreq->offset = fod->offset;
	fcpreq->समयout = NVME_FC_TGTOP_TIMEOUT_SEC;

	/*
	 * क्रम next sequence:
	 *  अवरोध at a sg element boundary
	 *  attempt to keep sequence length capped at
	 *    NVMET_FC_MAX_SEQ_LENGTH but allow sequence to
	 *    be दीर्घer अगर a single sg element is larger
	 *    than that amount. This is करोne to aव्योम creating
	 *    a new sg list to use क्रम the tgtport api.
	 */
	fcpreq->sg = sg;
	fcpreq->sg_cnt = 0;
	जबतक (tlen < reमुख्यinglen &&
	       fcpreq->sg_cnt < tgtport->max_sg_cnt &&
	       tlen + sg_dma_len(sg) < NVMET_FC_MAX_SEQ_LENGTH) अणु
		fcpreq->sg_cnt++;
		tlen += sg_dma_len(sg);
		sg = sg_next(sg);
	पूर्ण
	अगर (tlen < reमुख्यinglen && fcpreq->sg_cnt == 0) अणु
		fcpreq->sg_cnt++;
		tlen += min_t(u32, sg_dma_len(sg), reमुख्यinglen);
		sg = sg_next(sg);
	पूर्ण
	अगर (tlen < reमुख्यinglen)
		fod->next_sg = sg;
	अन्यथा
		fod->next_sg = शून्य;

	fcpreq->transfer_length = tlen;
	fcpreq->transferred_length = 0;
	fcpreq->fcp_error = 0;
	fcpreq->rsplen = 0;

	/*
	 * If the last READDATA request: check अगर LLDD supports
	 * combined xfr with response.
	 */
	अगर ((op == NVMET_FCOP_READDATA) &&
	    ((fod->offset + fcpreq->transfer_length) == fod->req.transfer_len) &&
	    (tgtport->ops->target_features & NVMET_FCTGTFEAT_READDATA_RSP)) अणु
		fcpreq->op = NVMET_FCOP_READDATA_RSP;
		nvmet_fc_prep_fcp_rsp(tgtport, fod);
	पूर्ण

	ret = tgtport->ops->fcp_op(&tgtport->fc_target_port, fod->fcpreq);
	अगर (ret) अणु
		/*
		 * should be ok to set w/o lock as its in the thपढ़ो of
		 * execution (not an async समयr routine) and करोesn't
		 * contend with any clearing action
		 */
		fod->पात = true;

		अगर (op == NVMET_FCOP_WRITEDATA) अणु
			spin_lock_irqsave(&fod->flock, flags);
			fod->ग_लिखोdataactive = false;
			spin_unlock_irqrestore(&fod->flock, flags);
			nvmet_req_complete(&fod->req, NVME_SC_INTERNAL);
		पूर्ण अन्यथा /* NVMET_FCOP_READDATA or NVMET_FCOP_READDATA_RSP */ अणु
			fcpreq->fcp_error = ret;
			fcpreq->transferred_length = 0;
			nvmet_fc_xmt_fcp_op_करोne(fod->fcpreq);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool
__nvmet_fc_fod_op_पात(काष्ठा nvmet_fc_fcp_iod *fod, bool पात)
अणु
	काष्ठा nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	काष्ठा nvmet_fc_tgtport *tgtport = fod->tgtport;

	/* अगर in the middle of an io and we need to tear करोwn */
	अगर (पात) अणु
		अगर (fcpreq->op == NVMET_FCOP_WRITEDATA) अणु
			nvmet_req_complete(&fod->req, NVME_SC_INTERNAL);
			वापस true;
		पूर्ण

		nvmet_fc_पात_op(tgtport, fod);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * actual करोne handler क्रम FCP operations when completed by the lldd
 */
अटल व्योम
nvmet_fc_fod_op_करोne(काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	काष्ठा nvmet_fc_tgtport *tgtport = fod->tgtport;
	अचिन्हित दीर्घ flags;
	bool पात;

	spin_lock_irqsave(&fod->flock, flags);
	पात = fod->पात;
	fod->ग_लिखोdataactive = false;
	spin_unlock_irqrestore(&fod->flock, flags);

	चयन (fcpreq->op) अणु

	हाल NVMET_FCOP_WRITEDATA:
		अगर (__nvmet_fc_fod_op_पात(fod, पात))
			वापस;
		अगर (fcpreq->fcp_error ||
		    fcpreq->transferred_length != fcpreq->transfer_length) अणु
			spin_lock_irqsave(&fod->flock, flags);
			fod->पात = true;
			spin_unlock_irqrestore(&fod->flock, flags);

			nvmet_req_complete(&fod->req, NVME_SC_INTERNAL);
			वापस;
		पूर्ण

		fod->offset += fcpreq->transferred_length;
		अगर (fod->offset != fod->req.transfer_len) अणु
			spin_lock_irqsave(&fod->flock, flags);
			fod->ग_लिखोdataactive = true;
			spin_unlock_irqrestore(&fod->flock, flags);

			/* transfer the next chunk */
			nvmet_fc_transfer_fcp_data(tgtport, fod,
						NVMET_FCOP_WRITEDATA);
			वापस;
		पूर्ण

		/* data transfer complete, resume with nvmet layer */
		fod->req.execute(&fod->req);
		अवरोध;

	हाल NVMET_FCOP_READDATA:
	हाल NVMET_FCOP_READDATA_RSP:
		अगर (__nvmet_fc_fod_op_पात(fod, पात))
			वापस;
		अगर (fcpreq->fcp_error ||
		    fcpreq->transferred_length != fcpreq->transfer_length) अणु
			nvmet_fc_पात_op(tgtport, fod);
			वापस;
		पूर्ण

		/* success */

		अगर (fcpreq->op == NVMET_FCOP_READDATA_RSP) अणु
			/* data no दीर्घer needed */
			nvmet_fc_मुक्त_tgt_pgs(fod);
			nvmet_fc_मुक्त_fcp_iod(fod->queue, fod);
			वापस;
		पूर्ण

		fod->offset += fcpreq->transferred_length;
		अगर (fod->offset != fod->req.transfer_len) अणु
			/* transfer the next chunk */
			nvmet_fc_transfer_fcp_data(tgtport, fod,
						NVMET_FCOP_READDATA);
			वापस;
		पूर्ण

		/* data transfer complete, send response */

		/* data no दीर्घer needed */
		nvmet_fc_मुक्त_tgt_pgs(fod);

		nvmet_fc_xmt_fcp_rsp(tgtport, fod);

		अवरोध;

	हाल NVMET_FCOP_RSP:
		अगर (__nvmet_fc_fod_op_पात(fod, पात))
			वापस;
		nvmet_fc_मुक्त_fcp_iod(fod->queue, fod);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
nvmet_fc_xmt_fcp_op_करोne(काष्ठा nvmefc_tgt_fcp_req *fcpreq)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_निजी;

	nvmet_fc_fod_op_करोne(fod);
पूर्ण

/*
 * actual completion handler after execution by the nvmet layer
 */
अटल व्योम
__nvmet_fc_fcp_nvme_cmd_करोne(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_fcp_iod *fod, पूर्णांक status)
अणु
	काष्ठा nvme_common_command *sqe = &fod->cmdiubuf.sqe.common;
	काष्ठा nvme_completion *cqe = &fod->rspiubuf.cqe;
	अचिन्हित दीर्घ flags;
	bool पात;

	spin_lock_irqsave(&fod->flock, flags);
	पात = fod->पात;
	spin_unlock_irqrestore(&fod->flock, flags);

	/* अगर we have a CQE, snoop the last sq_head value */
	अगर (!status)
		fod->queue->sqhd = cqe->sq_head;

	अगर (पात) अणु
		nvmet_fc_पात_op(tgtport, fod);
		वापस;
	पूर्ण

	/* अगर an error handling the cmd post initial parsing */
	अगर (status) अणु
		/* fudge up a failed CQE status क्रम our transport error */
		स_रखो(cqe, 0, माप(*cqe));
		cqe->sq_head = fod->queue->sqhd;	/* echo last cqe sqhd */
		cqe->sq_id = cpu_to_le16(fod->queue->qid);
		cqe->command_id = sqe->command_id;
		cqe->status = cpu_to_le16(status);
	पूर्ण अन्यथा अणु

		/*
		 * try to push the data even अगर the SQE status is non-zero.
		 * There may be a status where data still was पूर्णांकended to
		 * be moved
		 */
		अगर ((fod->io_dir == NVMET_FCP_READ) && (fod->data_sg_cnt)) अणु
			/* push the data over beक्रमe sending rsp */
			nvmet_fc_transfer_fcp_data(tgtport, fod,
						NVMET_FCOP_READDATA);
			वापस;
		पूर्ण

		/* ग_लिखोs & no data - fall thru */
	पूर्ण

	/* data no दीर्घer needed */
	nvmet_fc_मुक्त_tgt_pgs(fod);

	nvmet_fc_xmt_fcp_rsp(tgtport, fod);
पूर्ण


अटल व्योम
nvmet_fc_fcp_nvme_cmd_करोne(काष्ठा nvmet_req *nvme_req)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = nvmet_req_to_fod(nvme_req);
	काष्ठा nvmet_fc_tgtport *tgtport = fod->tgtport;

	__nvmet_fc_fcp_nvme_cmd_करोne(tgtport, fod, 0);
पूर्ण


/*
 * Actual processing routine क्रम received FC-NVME I/O Requests from the LLD
 */
अटल व्योम
nvmet_fc_handle_fcp_rqst(काष्ठा nvmet_fc_tgtport *tgtport,
			काष्ठा nvmet_fc_fcp_iod *fod)
अणु
	काष्ठा nvme_fc_cmd_iu *cmdiu = &fod->cmdiubuf;
	u32 xfrlen = be32_to_cpu(cmdiu->data_len);
	पूर्णांक ret;

	/*
	 * अगर there is no nvmet mapping to the targetport there
	 * shouldn't be requests. just terminate them.
	 */
	अगर (!tgtport->pe)
		जाओ transport_error;

	/*
	 * Fused commands are currently not supported in the linux
	 * implementation.
	 *
	 * As such, the implementation of the FC transport करोes not
	 * look at the fused commands and order delivery to the upper
	 * layer until we have both based on csn.
	 */

	fod->fcpreq->करोne = nvmet_fc_xmt_fcp_op_करोne;

	अगर (cmdiu->flags & FCNVME_CMD_FLAGS_WRITE) अणु
		fod->io_dir = NVMET_FCP_WRITE;
		अगर (!nvme_is_ग_लिखो(&cmdiu->sqe))
			जाओ transport_error;
	पूर्ण अन्यथा अगर (cmdiu->flags & FCNVME_CMD_FLAGS_READ) अणु
		fod->io_dir = NVMET_FCP_READ;
		अगर (nvme_is_ग_लिखो(&cmdiu->sqe))
			जाओ transport_error;
	पूर्ण अन्यथा अणु
		fod->io_dir = NVMET_FCP_NODATA;
		अगर (xfrlen)
			जाओ transport_error;
	पूर्ण

	fod->req.cmd = &fod->cmdiubuf.sqe;
	fod->req.cqe = &fod->rspiubuf.cqe;
	fod->req.port = tgtport->pe->port;

	/* clear any response payload */
	स_रखो(&fod->rspiubuf, 0, माप(fod->rspiubuf));

	fod->data_sg = शून्य;
	fod->data_sg_cnt = 0;

	ret = nvmet_req_init(&fod->req,
				&fod->queue->nvme_cq,
				&fod->queue->nvme_sq,
				&nvmet_fc_tgt_fcp_ops);
	अगर (!ret) अणु
		/* bad SQE content or invalid ctrl state */
		/* nvmet layer has alपढ़ोy called op करोne to send rsp. */
		वापस;
	पूर्ण

	fod->req.transfer_len = xfrlen;

	/* keep a running counter of tail position */
	atomic_inc(&fod->queue->sqtail);

	अगर (fod->req.transfer_len) अणु
		ret = nvmet_fc_alloc_tgt_pgs(fod);
		अगर (ret) अणु
			nvmet_req_complete(&fod->req, ret);
			वापस;
		पूर्ण
	पूर्ण
	fod->req.sg = fod->data_sg;
	fod->req.sg_cnt = fod->data_sg_cnt;
	fod->offset = 0;

	अगर (fod->io_dir == NVMET_FCP_WRITE) अणु
		/* pull the data over beक्रमe invoking nvmet layer */
		nvmet_fc_transfer_fcp_data(tgtport, fod, NVMET_FCOP_WRITEDATA);
		वापस;
	पूर्ण

	/*
	 * Reads or no data:
	 *
	 * can invoke the nvmet_layer now. If पढ़ो data, cmd completion will
	 * push the data
	 */
	fod->req.execute(&fod->req);
	वापस;

transport_error:
	nvmet_fc_पात_op(tgtport, fod);
पूर्ण

/**
 * nvmet_fc_rcv_fcp_req - transport entry poपूर्णांक called by an LLDD
 *                       upon the reception of a NVME FCP CMD IU.
 *
 * Pass a FC-NVME FCP CMD IU received from the FC link to the nvmet-fc
 * layer क्रम processing.
 *
 * The nvmet_fc layer allocates a local job काष्ठाure (काष्ठा
 * nvmet_fc_fcp_iod) from the queue क्रम the io and copies the
 * CMD IU buffer to the job काष्ठाure. As such, on a successful
 * completion (वापसs 0), the LLDD may immediately मुक्त/reuse
 * the CMD IU buffer passed in the call.
 *
 * However, in some circumstances, due to the packetized nature of FC
 * and the api of the FC LLDD which may issue a hw command to send the
 * response, but the LLDD may not get the hw completion क्रम that command
 * and upcall the nvmet_fc layer beक्रमe a new command may be
 * asynchronously received - its possible क्रम a command to be received
 * beक्रमe the LLDD and nvmet_fc have recycled the job काष्ठाure. It gives
 * the appearance of more commands received than fits in the sq.
 * To alleviate this scenario, a temporary queue is मुख्यtained in the
 * transport क्रम pending LLDD requests रुकोing क्रम a queue job काष्ठाure.
 * In these "overrun" हालs, a temporary queue element is allocated
 * the LLDD request and CMD iu buffer inक्रमmation remembered, and the
 * routine वापसs a -EOVERFLOW status. Subsequently, when a queue job
 * काष्ठाure is मुक्तd, it is immediately पुनः_स्मृतिated क्रम anything on the
 * pending request list. The LLDDs defer_rcv() callback is called,
 * inक्रमming the LLDD that it may reuse the CMD IU buffer, and the io
 * is then started normally with the transport.
 *
 * The LLDD, when receiving an -EOVERFLOW completion status, is to treat
 * the completion as successful but must not reuse the CMD IU buffer
 * until the LLDD's defer_rcv() callback has been called क्रम the
 * corresponding काष्ठा nvmefc_tgt_fcp_req poपूर्णांकer.
 *
 * If there is any other condition in which an error occurs, the
 * transport will वापस a non-zero status indicating the error.
 * In all हालs other than -EOVERFLOW, the transport has not accepted the
 * request and the LLDD should पात the exchange.
 *
 * @target_port: poपूर्णांकer to the (रेजिस्टरed) target port the FCP CMD IU
 *              was received on.
 * @fcpreq:     poपूर्णांकer to a fcpreq request काष्ठाure to be used to reference
 *              the exchange corresponding to the FCP Exchange.
 * @cmdiubuf:   poपूर्णांकer to the buffer containing the FCP CMD IU
 * @cmdiubuf_len: length, in bytes, of the received FCP CMD IU
 */
पूर्णांक
nvmet_fc_rcv_fcp_req(काष्ठा nvmet_fc_target_port *target_port,
			काष्ठा nvmefc_tgt_fcp_req *fcpreq,
			व्योम *cmdiubuf, u32 cmdiubuf_len)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);
	काष्ठा nvme_fc_cmd_iu *cmdiu = cmdiubuf;
	काष्ठा nvmet_fc_tgt_queue *queue;
	काष्ठा nvmet_fc_fcp_iod *fod;
	काष्ठा nvmet_fc_defer_fcp_req *deferfcp;
	अचिन्हित दीर्घ flags;

	/* validate iu, so the connection id can be used to find the queue */
	अगर ((cmdiubuf_len != माप(*cmdiu)) ||
			(cmdiu->क्रमmat_id != NVME_CMD_FORMAT_ID) ||
			(cmdiu->fc_id != NVME_CMD_FC_ID) ||
			(be16_to_cpu(cmdiu->iu_len) != (माप(*cmdiu)/4)))
		वापस -EIO;

	queue = nvmet_fc_find_target_queue(tgtport,
				be64_to_cpu(cmdiu->connection_id));
	अगर (!queue)
		वापस -ENOTCONN;

	/*
	 * note: reference taken by find_target_queue
	 * After successful fod allocation, the fod will inherit the
	 * ownership of that reference and will हटाओ the reference
	 * when the fod is मुक्तd.
	 */

	spin_lock_irqsave(&queue->qlock, flags);

	fod = nvmet_fc_alloc_fcp_iod(queue);
	अगर (fod) अणु
		spin_unlock_irqrestore(&queue->qlock, flags);

		fcpreq->nvmet_fc_निजी = fod;
		fod->fcpreq = fcpreq;

		स_नकल(&fod->cmdiubuf, cmdiubuf, cmdiubuf_len);

		nvmet_fc_queue_fcp_req(tgtport, queue, fcpreq);

		वापस 0;
	पूर्ण

	अगर (!tgtport->ops->defer_rcv) अणु
		spin_unlock_irqrestore(&queue->qlock, flags);
		/* release the queue lookup reference */
		nvmet_fc_tgt_q_put(queue);
		वापस -ENOENT;
	पूर्ण

	deferfcp = list_first_entry_or_null(&queue->avail_defer_list,
			काष्ठा nvmet_fc_defer_fcp_req, req_list);
	अगर (deferfcp) अणु
		/* Just re-use one that was previously allocated */
		list_del(&deferfcp->req_list);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&queue->qlock, flags);

		/* Now we need to dynamically allocate one */
		deferfcp = kदो_स्मृति(माप(*deferfcp), GFP_KERNEL);
		अगर (!deferfcp) अणु
			/* release the queue lookup reference */
			nvmet_fc_tgt_q_put(queue);
			वापस -ENOMEM;
		पूर्ण
		spin_lock_irqsave(&queue->qlock, flags);
	पूर्ण

	/* For now, use rspaddr / rsplen to save payload inक्रमmation */
	fcpreq->rspaddr = cmdiubuf;
	fcpreq->rsplen  = cmdiubuf_len;
	deferfcp->fcp_req = fcpreq;

	/* defer processing till a fod becomes available */
	list_add_tail(&deferfcp->req_list, &queue->pending_cmd_list);

	/* NOTE: the queue lookup reference is still valid */

	spin_unlock_irqrestore(&queue->qlock, flags);

	वापस -EOVERFLOW;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_rcv_fcp_req);

/**
 * nvmet_fc_rcv_fcp_पात - transport entry poपूर्णांक called by an LLDD
 *                       upon the reception of an ABTS क्रम a FCP command
 *
 * Notअगरy the transport that an ABTS has been received क्रम a FCP command
 * that had been given to the transport via nvmet_fc_rcv_fcp_req(). The
 * LLDD believes the command is still being worked on
 * (ढाँचा_ops->fcp_req_release() has not been called).
 *
 * The transport will रुको क्रम any outstanding work (an op to the LLDD,
 * which the lldd should complete with error due to the ABTS; or the
 * completion from the nvmet layer of the nvme command), then will
 * stop processing and call the nvmet_fc_rcv_fcp_req() callback to
 * वापस the i/o context to the LLDD.  The LLDD may send the BA_ACC
 * to the ABTS either after वापस from this function (assuming any
 * outstanding op work has been terminated) or upon the callback being
 * called.
 *
 * @target_port: poपूर्णांकer to the (रेजिस्टरed) target port the FCP CMD IU
 *              was received on.
 * @fcpreq:     poपूर्णांकer to the fcpreq request काष्ठाure that corresponds
 *              to the exchange that received the ABTS.
 */
व्योम
nvmet_fc_rcv_fcp_पात(काष्ठा nvmet_fc_target_port *target_port,
			काष्ठा nvmefc_tgt_fcp_req *fcpreq)
अणु
	काष्ठा nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_निजी;
	काष्ठा nvmet_fc_tgt_queue *queue;
	अचिन्हित दीर्घ flags;

	अगर (!fod || fod->fcpreq != fcpreq)
		/* job appears to have alपढ़ोy completed, ignore पात */
		वापस;

	queue = fod->queue;

	spin_lock_irqsave(&queue->qlock, flags);
	अगर (fod->active) अणु
		/*
		 * mark as पात. The पात handler, invoked upon completion
		 * of any work, will detect the पातed status and करो the
		 * callback.
		 */
		spin_lock(&fod->flock);
		fod->पात = true;
		fod->पातed = true;
		spin_unlock(&fod->flock);
	पूर्ण
	spin_unlock_irqrestore(&queue->qlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_fc_rcv_fcp_पात);


काष्ठा nvmet_fc_traddr अणु
	u64	nn;
	u64	pn;
पूर्ण;

अटल पूर्णांक
__nvme_fc_parse_u64(substring_t *sstr, u64 *val)
अणु
	u64 token64;

	अगर (match_u64(sstr, &token64))
		वापस -EINVAL;
	*val = token64;

	वापस 0;
पूर्ण

/*
 * This routine validates and extracts the WWN's from the TRADDR string.
 * As kernel parsers need the 0x to determine number base, universally
 * build string to parse with 0x prefix beक्रमe parsing name strings.
 */
अटल पूर्णांक
nvme_fc_parse_traddr(काष्ठा nvmet_fc_traddr *traddr, अक्षर *buf, माप_प्रकार blen)
अणु
	अक्षर name[2 + NVME_FC_TRADDR_HEXNAMELEN + 1];
	substring_t wwn = अणु name, &name[माप(name)-1] पूर्ण;
	पूर्णांक nnoffset, pnoffset;

	/* validate अगर string is one of the 2 allowed क्रमmats */
	अगर (strnlen(buf, blen) == NVME_FC_TRADDR_MAXLENGTH &&
			!म_भेदन(buf, "nn-0x", NVME_FC_TRADDR_OXNNLEN) &&
			!म_भेदन(&buf[NVME_FC_TRADDR_MAX_PN_OFFSET],
				"pn-0x", NVME_FC_TRADDR_OXNNLEN)) अणु
		nnoffset = NVME_FC_TRADDR_OXNNLEN;
		pnoffset = NVME_FC_TRADDR_MAX_PN_OFFSET +
						NVME_FC_TRADDR_OXNNLEN;
	पूर्ण अन्यथा अगर ((strnlen(buf, blen) == NVME_FC_TRADDR_MINLENGTH &&
			!म_भेदन(buf, "nn-", NVME_FC_TRADDR_NNLEN) &&
			!म_भेदन(&buf[NVME_FC_TRADDR_MIN_PN_OFFSET],
				"pn-", NVME_FC_TRADDR_NNLEN))) अणु
		nnoffset = NVME_FC_TRADDR_NNLEN;
		pnoffset = NVME_FC_TRADDR_MIN_PN_OFFSET + NVME_FC_TRADDR_NNLEN;
	पूर्ण अन्यथा
		जाओ out_einval;

	name[0] = '0';
	name[1] = 'x';
	name[2 + NVME_FC_TRADDR_HEXNAMELEN] = 0;

	स_नकल(&name[2], &buf[nnoffset], NVME_FC_TRADDR_HEXNAMELEN);
	अगर (__nvme_fc_parse_u64(&wwn, &traddr->nn))
		जाओ out_einval;

	स_नकल(&name[2], &buf[pnoffset], NVME_FC_TRADDR_HEXNAMELEN);
	अगर (__nvme_fc_parse_u64(&wwn, &traddr->pn))
		जाओ out_einval;

	वापस 0;

out_einval:
	pr_warn("%s: bad traddr string\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvmet_fc_add_port(काष्ठा nvmet_port *port)
अणु
	काष्ठा nvmet_fc_tgtport *tgtport;
	काष्ठा nvmet_fc_port_entry *pe;
	काष्ठा nvmet_fc_traddr traddr = अणु 0L, 0L पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* validate the address info */
	अगर ((port->disc_addr.trtype != NVMF_TRTYPE_FC) ||
	    (port->disc_addr.adrfam != NVMF_ADDR_FAMILY_FC))
		वापस -EINVAL;

	/* map the traddr address info to a target port */

	ret = nvme_fc_parse_traddr(&traddr, port->disc_addr.traddr,
			माप(port->disc_addr.traddr));
	अगर (ret)
		वापस ret;

	pe = kzalloc(माप(*pe), GFP_KERNEL);
	अगर (!pe)
		वापस -ENOMEM;

	ret = -ENXIO;
	spin_lock_irqsave(&nvmet_fc_tgtlock, flags);
	list_क्रम_each_entry(tgtport, &nvmet_fc_target_list, tgt_list) अणु
		अगर ((tgtport->fc_target_port.node_name == traddr.nn) &&
		    (tgtport->fc_target_port.port_name == traddr.pn)) अणु
			/* a FC port can only be 1 nvmet port id */
			अगर (!tgtport->pe) अणु
				nvmet_fc_portentry_bind(tgtport, pe, port);
				ret = 0;
			पूर्ण अन्यथा
				ret = -EALREADY;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&nvmet_fc_tgtlock, flags);

	अगर (ret)
		kमुक्त(pe);

	वापस ret;
पूर्ण

अटल व्योम
nvmet_fc_हटाओ_port(काष्ठा nvmet_port *port)
अणु
	काष्ठा nvmet_fc_port_entry *pe = port->priv;

	nvmet_fc_portentry_unbind(pe);

	kमुक्त(pe);
पूर्ण

अटल व्योम
nvmet_fc_discovery_chg(काष्ठा nvmet_port *port)
अणु
	काष्ठा nvmet_fc_port_entry *pe = port->priv;
	काष्ठा nvmet_fc_tgtport *tgtport = pe->tgtport;

	अगर (tgtport && tgtport->ops->discovery_event)
		tgtport->ops->discovery_event(&tgtport->fc_target_port);
पूर्ण

अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_fc_tgt_fcp_ops = अणु
	.owner			= THIS_MODULE,
	.type			= NVMF_TRTYPE_FC,
	.msdbd			= 1,
	.add_port		= nvmet_fc_add_port,
	.हटाओ_port		= nvmet_fc_हटाओ_port,
	.queue_response		= nvmet_fc_fcp_nvme_cmd_करोne,
	.delete_ctrl		= nvmet_fc_delete_ctrl,
	.discovery_chg		= nvmet_fc_discovery_chg,
पूर्ण;

अटल पूर्णांक __init nvmet_fc_init_module(व्योम)
अणु
	वापस nvmet_रेजिस्टर_transport(&nvmet_fc_tgt_fcp_ops);
पूर्ण

अटल व्योम __निकास nvmet_fc_निकास_module(व्योम)
अणु
	/* sanity check - all lports should be हटाओd */
	अगर (!list_empty(&nvmet_fc_target_list))
		pr_warn("%s: targetport list not empty\n", __func__);

	nvmet_unरेजिस्टर_transport(&nvmet_fc_tgt_fcp_ops);

	ida_destroy(&nvmet_fc_tgtport_cnt);
पूर्ण

module_init(nvmet_fc_init_module);
module_निकास(nvmet_fc_निकास_module);

MODULE_LICENSE("GPL v2");
