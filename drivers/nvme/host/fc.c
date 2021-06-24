<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Avago Technologies.  All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <uapi/scsi/fc/fc_fs.h>
#समावेश <uapi/scsi/fc/fc_els.h>
#समावेश <linux/delay.h>
#समावेश <linux/overflow.h>

#समावेश "nvme.h"
#समावेश "fabrics.h"
#समावेश <linux/nvme-fc-driver.h>
#समावेश <linux/nvme-fc.h>
#समावेश "fc.h"
#समावेश <scsi/scsi_transport_fc.h>

/* *************************** Data Structures/Defines ****************** */


क्रमागत nvme_fc_queue_flags अणु
	NVME_FC_Q_CONNECTED = 0,
	NVME_FC_Q_LIVE,
पूर्ण;

#घोषणा NVME_FC_DEFAULT_DEV_LOSS_TMO	60	/* seconds */
#घोषणा NVME_FC_DEFAULT_RECONNECT_TMO	2	/* delay between reconnects
						 * when connected and a
						 * connection failure.
						 */

काष्ठा nvme_fc_queue अणु
	काष्ठा nvme_fc_ctrl	*ctrl;
	काष्ठा device		*dev;
	काष्ठा blk_mq_hw_ctx	*hctx;
	व्योम			*lldd_handle;
	माप_प्रकार			cmnd_capsule_len;
	u32			qnum;
	u32			rqcnt;
	u32			seqno;

	u64			connection_id;
	atomic_t		csn;

	अचिन्हित दीर्घ		flags;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */

क्रमागत nvme_fcop_flags अणु
	FCOP_FLAGS_TERMIO	= (1 << 0),
	FCOP_FLAGS_AEN		= (1 << 1),
पूर्ण;

काष्ठा nvmefc_ls_req_op अणु
	काष्ठा nvmefc_ls_req	ls_req;

	काष्ठा nvme_fc_rport	*rport;
	काष्ठा nvme_fc_queue	*queue;
	काष्ठा request		*rq;
	u32			flags;

	पूर्णांक			ls_error;
	काष्ठा completion	ls_करोne;
	काष्ठा list_head	lsreq_list;	/* rport->ls_req_list */
	bool			req_queued;
पूर्ण;

काष्ठा nvmefc_ls_rcv_op अणु
	काष्ठा nvme_fc_rport		*rport;
	काष्ठा nvmefc_ls_rsp		*lsrsp;
	जोड़ nvmefc_ls_requests	*rqstbuf;
	जोड़ nvmefc_ls_responses	*rspbuf;
	u16				rqstdatalen;
	bool				handled;
	dma_addr_t			rspdma;
	काष्ठा list_head		lsrcv_list;	/* rport->ls_rcv_list */
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */

क्रमागत nvme_fcpop_state अणु
	FCPOP_STATE_UNINIT	= 0,
	FCPOP_STATE_IDLE	= 1,
	FCPOP_STATE_ACTIVE	= 2,
	FCPOP_STATE_ABORTED	= 3,
	FCPOP_STATE_COMPLETE	= 4,
पूर्ण;

काष्ठा nvme_fc_fcp_op अणु
	काष्ठा nvme_request	nreq;		/*
						 * nvme/host/core.c
						 * requires this to be
						 * the 1st element in the
						 * निजी काष्ठाure
						 * associated with the
						 * request.
						 */
	काष्ठा nvmefc_fcp_req	fcp_req;

	काष्ठा nvme_fc_ctrl	*ctrl;
	काष्ठा nvme_fc_queue	*queue;
	काष्ठा request		*rq;

	atomic_t		state;
	u32			flags;
	u32			rqno;
	u32			nents;

	काष्ठा nvme_fc_cmd_iu	cmd_iu;
	काष्ठा nvme_fc_ersp_iu	rsp_iu;
पूर्ण;

काष्ठा nvme_fcp_op_w_sgl अणु
	काष्ठा nvme_fc_fcp_op	op;
	काष्ठा scatterlist	sgl[NVME_INLINE_SG_CNT];
	uपूर्णांक8_t			priv[];
पूर्ण;

काष्ठा nvme_fc_lport अणु
	काष्ठा nvme_fc_local_port	localport;

	काष्ठा ida			endp_cnt;
	काष्ठा list_head		port_list;	/* nvme_fc_port_list */
	काष्ठा list_head		endp_list;
	काष्ठा device			*dev;	/* physical device क्रम dma */
	काष्ठा nvme_fc_port_ढाँचा	*ops;
	काष्ठा kref			ref;
	atomic_t                        act_rport_cnt;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */

काष्ठा nvme_fc_rport अणु
	काष्ठा nvme_fc_remote_port	remoteport;

	काष्ठा list_head		endp_list; /* क्रम lport->endp_list */
	काष्ठा list_head		ctrl_list;
	काष्ठा list_head		ls_req_list;
	काष्ठा list_head		ls_rcv_list;
	काष्ठा list_head		disc_list;
	काष्ठा device			*dev;	/* physical device क्रम dma */
	काष्ठा nvme_fc_lport		*lport;
	spinlock_t			lock;
	काष्ठा kref			ref;
	atomic_t                        act_ctrl_cnt;
	अचिन्हित दीर्घ			dev_loss_end;
	काष्ठा work_काष्ठा		lsrcv_work;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */

/* fc_ctrl flags values - specअगरied as bit positions */
#घोषणा ASSOC_ACTIVE		0
#घोषणा ASSOC_FAILED		1
#घोषणा FCCTRL_TERMIO		2

काष्ठा nvme_fc_ctrl अणु
	spinlock_t		lock;
	काष्ठा nvme_fc_queue	*queues;
	काष्ठा device		*dev;
	काष्ठा nvme_fc_lport	*lport;
	काष्ठा nvme_fc_rport	*rport;
	u32			cnum;

	bool			ioq_live;
	u64			association_id;
	काष्ठा nvmefc_ls_rcv_op	*rcv_disconn;

	काष्ठा list_head	ctrl_list;	/* rport->ctrl_list */

	काष्ठा blk_mq_tag_set	admin_tag_set;
	काष्ठा blk_mq_tag_set	tag_set;

	काष्ठा work_काष्ठा	ioerr_work;
	काष्ठा delayed_work	connect_work;

	काष्ठा kref		ref;
	अचिन्हित दीर्घ		flags;
	u32			iocnt;
	रुको_queue_head_t	ioपात_रुको;

	काष्ठा nvme_fc_fcp_op	aen_ops[NVME_NR_AEN_COMMANDS];

	काष्ठा nvme_ctrl	ctrl;
पूर्ण;

अटल अंतरभूत काष्ठा nvme_fc_ctrl *
to_fc_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा nvme_fc_ctrl, ctrl);
पूर्ण

अटल अंतरभूत काष्ठा nvme_fc_lport *
localport_to_lport(काष्ठा nvme_fc_local_port *portptr)
अणु
	वापस container_of(portptr, काष्ठा nvme_fc_lport, localport);
पूर्ण

अटल अंतरभूत काष्ठा nvme_fc_rport *
remoteport_to_rport(काष्ठा nvme_fc_remote_port *portptr)
अणु
	वापस container_of(portptr, काष्ठा nvme_fc_rport, remoteport);
पूर्ण

अटल अंतरभूत काष्ठा nvmefc_ls_req_op *
ls_req_to_lsop(काष्ठा nvmefc_ls_req *lsreq)
अणु
	वापस container_of(lsreq, काष्ठा nvmefc_ls_req_op, ls_req);
पूर्ण

अटल अंतरभूत काष्ठा nvme_fc_fcp_op *
fcp_req_to_fcp_op(काष्ठा nvmefc_fcp_req *fcpreq)
अणु
	वापस container_of(fcpreq, काष्ठा nvme_fc_fcp_op, fcp_req);
पूर्ण



/* *************************** Globals **************************** */


अटल DEFINE_SPINLOCK(nvme_fc_lock);

अटल LIST_HEAD(nvme_fc_lport_list);
अटल DEFINE_IDA(nvme_fc_local_port_cnt);
अटल DEFINE_IDA(nvme_fc_ctrl_cnt);

अटल काष्ठा workqueue_काष्ठा *nvme_fc_wq;

अटल bool nvme_fc_रुकोing_to_unload;
अटल DECLARE_COMPLETION(nvme_fc_unload_proceed);

/*
 * These items are लघु-term. They will eventually be moved पूर्णांकo
 * a generic FC class. See comments in module init.
 */
अटल काष्ठा device *fc_udev_device;

अटल व्योम nvme_fc_complete_rq(काष्ठा request *rq);

/* *********************** FC-NVME Port Management ************************ */

अटल व्योम __nvme_fc_delete_hw_queue(काष्ठा nvme_fc_ctrl *,
			काष्ठा nvme_fc_queue *, अचिन्हित पूर्णांक);

अटल व्योम nvme_fc_handle_ls_rqst_work(काष्ठा work_काष्ठा *work);


अटल व्योम
nvme_fc_मुक्त_lport(काष्ठा kref *ref)
अणु
	काष्ठा nvme_fc_lport *lport =
		container_of(ref, काष्ठा nvme_fc_lport, ref);
	अचिन्हित दीर्घ flags;

	WARN_ON(lport->localport.port_state != FC_OBJSTATE_DELETED);
	WARN_ON(!list_empty(&lport->endp_list));

	/* हटाओ from transport list */
	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_del(&lport->port_list);
	अगर (nvme_fc_रुकोing_to_unload && list_empty(&nvme_fc_lport_list))
		complete(&nvme_fc_unload_proceed);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	ida_simple_हटाओ(&nvme_fc_local_port_cnt, lport->localport.port_num);
	ida_destroy(&lport->endp_cnt);

	put_device(lport->dev);

	kमुक्त(lport);
पूर्ण

अटल व्योम
nvme_fc_lport_put(काष्ठा nvme_fc_lport *lport)
अणु
	kref_put(&lport->ref, nvme_fc_मुक्त_lport);
पूर्ण

अटल पूर्णांक
nvme_fc_lport_get(काष्ठा nvme_fc_lport *lport)
अणु
	वापस kref_get_unless_zero(&lport->ref);
पूर्ण


अटल काष्ठा nvme_fc_lport *
nvme_fc_attach_to_unreg_lport(काष्ठा nvme_fc_port_info *pinfo,
			काष्ठा nvme_fc_port_ढाँचा *ops,
			काष्ठा device *dev)
अणु
	काष्ठा nvme_fc_lport *lport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvme_fc_lock, flags);

	list_क्रम_each_entry(lport, &nvme_fc_lport_list, port_list) अणु
		अगर (lport->localport.node_name != pinfo->node_name ||
		    lport->localport.port_name != pinfo->port_name)
			जारी;

		अगर (lport->dev != dev) अणु
			lport = ERR_PTR(-EXDEV);
			जाओ out_करोne;
		पूर्ण

		अगर (lport->localport.port_state != FC_OBJSTATE_DELETED) अणु
			lport = ERR_PTR(-EEXIST);
			जाओ out_करोne;
		पूर्ण

		अगर (!nvme_fc_lport_get(lport)) अणु
			/*
			 * fails अगर ref cnt alपढ़ोy 0. If so,
			 * act as अगर lport alपढ़ोy deleted
			 */
			lport = शून्य;
			जाओ out_करोne;
		पूर्ण

		/* resume the lport */

		lport->ops = ops;
		lport->localport.port_role = pinfo->port_role;
		lport->localport.port_id = pinfo->port_id;
		lport->localport.port_state = FC_OBJSTATE_ONLINE;

		spin_unlock_irqrestore(&nvme_fc_lock, flags);

		वापस lport;
	पूर्ण

	lport = शून्य;

out_करोne:
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	वापस lport;
पूर्ण

/**
 * nvme_fc_रेजिस्टर_localport - transport entry poपूर्णांक called by an
 *                              LLDD to रेजिस्टर the existence of a NVME
 *                              host FC port.
 * @pinfo:     poपूर्णांकer to inक्रमmation about the port to be रेजिस्टरed
 * @ढाँचा:  LLDD entrypoपूर्णांकs and operational parameters क्रम the port
 * @dev:       physical hardware device node port corresponds to. Will be
 *             used क्रम DMA mappings
 * @portptr:   poपूर्णांकer to a local port poपूर्णांकer. Upon success, the routine
 *             will allocate a nvme_fc_local_port काष्ठाure and place its
 *             address in the local port poपूर्णांकer. Upon failure, local port
 *             poपूर्णांकer will be set to 0.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvme_fc_रेजिस्टर_localport(काष्ठा nvme_fc_port_info *pinfo,
			काष्ठा nvme_fc_port_ढाँचा *ढाँचा,
			काष्ठा device *dev,
			काष्ठा nvme_fc_local_port **portptr)
अणु
	काष्ठा nvme_fc_lport *newrec;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx;

	अगर (!ढाँचा->localport_delete || !ढाँचा->remoteport_delete ||
	    !ढाँचा->ls_req || !ढाँचा->fcp_io ||
	    !ढाँचा->ls_पात || !ढाँचा->fcp_पात ||
	    !ढाँचा->max_hw_queues || !ढाँचा->max_sgl_segments ||
	    !ढाँचा->max_dअगर_sgl_segments || !ढाँचा->dma_boundary) अणु
		ret = -EINVAL;
		जाओ out_reghost_failed;
	पूर्ण

	/*
	 * look to see अगर there is alपढ़ोy a localport that had been
	 * deरेजिस्टरed and in the process of रुकोing क्रम all the
	 * references to fully be हटाओd.  If the references haven't
	 * expired, we can simply re-enable the localport. Remoteports
	 * and controller reconnections should resume naturally.
	 */
	newrec = nvme_fc_attach_to_unreg_lport(pinfo, ढाँचा, dev);

	/* found an lport, but something about its state is bad */
	अगर (IS_ERR(newrec)) अणु
		ret = PTR_ERR(newrec);
		जाओ out_reghost_failed;

	/* found existing lport, which was resumed */
	पूर्ण अन्यथा अगर (newrec) अणु
		*portptr = &newrec->localport;
		वापस 0;
	पूर्ण

	/* nothing found - allocate a new localport काष्ठा */

	newrec = kदो_स्मृति((माप(*newrec) + ढाँचा->local_priv_sz),
			 GFP_KERNEL);
	अगर (!newrec) अणु
		ret = -ENOMEM;
		जाओ out_reghost_failed;
	पूर्ण

	idx = ida_simple_get(&nvme_fc_local_port_cnt, 0, 0, GFP_KERNEL);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out_fail_kमुक्त;
	पूर्ण

	अगर (!get_device(dev) && dev) अणु
		ret = -ENODEV;
		जाओ out_ida_put;
	पूर्ण

	INIT_LIST_HEAD(&newrec->port_list);
	INIT_LIST_HEAD(&newrec->endp_list);
	kref_init(&newrec->ref);
	atomic_set(&newrec->act_rport_cnt, 0);
	newrec->ops = ढाँचा;
	newrec->dev = dev;
	ida_init(&newrec->endp_cnt);
	अगर (ढाँचा->local_priv_sz)
		newrec->localport.निजी = &newrec[1];
	अन्यथा
		newrec->localport.निजी = शून्य;
	newrec->localport.node_name = pinfo->node_name;
	newrec->localport.port_name = pinfo->port_name;
	newrec->localport.port_role = pinfo->port_role;
	newrec->localport.port_id = pinfo->port_id;
	newrec->localport.port_state = FC_OBJSTATE_ONLINE;
	newrec->localport.port_num = idx;

	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_add_tail(&newrec->port_list, &nvme_fc_lport_list);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	अगर (dev)
		dma_set_seg_boundary(dev, ढाँचा->dma_boundary);

	*portptr = &newrec->localport;
	वापस 0;

out_ida_put:
	ida_simple_हटाओ(&nvme_fc_local_port_cnt, idx);
out_fail_kमुक्त:
	kमुक्त(newrec);
out_reghost_failed:
	*portptr = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_रेजिस्टर_localport);

/**
 * nvme_fc_unरेजिस्टर_localport - transport entry poपूर्णांक called by an
 *                              LLDD to deरेजिस्टर/हटाओ a previously
 *                              रेजिस्टरed a NVME host FC port.
 * @portptr: poपूर्णांकer to the (रेजिस्टरed) local port that is to be deरेजिस्टरed.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvme_fc_unरेजिस्टर_localport(काष्ठा nvme_fc_local_port *portptr)
अणु
	काष्ठा nvme_fc_lport *lport = localport_to_lport(portptr);
	अचिन्हित दीर्घ flags;

	अगर (!portptr)
		वापस -EINVAL;

	spin_lock_irqsave(&nvme_fc_lock, flags);

	अगर (portptr->port_state != FC_OBJSTATE_ONLINE) अणु
		spin_unlock_irqrestore(&nvme_fc_lock, flags);
		वापस -EINVAL;
	पूर्ण
	portptr->port_state = FC_OBJSTATE_DELETED;

	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	अगर (atomic_पढ़ो(&lport->act_rport_cnt) == 0)
		lport->ops->localport_delete(&lport->localport);

	nvme_fc_lport_put(lport);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_unरेजिस्टर_localport);

/*
 * TRADDR strings, per FC-NVME are fixed क्रमmat:
 *   "nn-0x<16hexdigits>:pn-0x<16hexdigits>" - 43 अक्षरacters
 * udev event will only dअगरfer by prefix of what field is
 * being specअगरied:
 *    "NVMEFC_HOST_TRADDR=" or "NVMEFC_TRADDR=" - 19 max अक्षरacters
 *  19 + 43 + null_fudge = 64 अक्षरacters
 */
#घोषणा FCNVME_TRADDR_LENGTH		64

अटल व्योम
nvme_fc_संकेत_discovery_scan(काष्ठा nvme_fc_lport *lport,
		काष्ठा nvme_fc_rport *rport)
अणु
	अक्षर hostaddr[FCNVME_TRADDR_LENGTH];	/* NVMEFC_HOST_TRADDR=...*/
	अक्षर tgtaddr[FCNVME_TRADDR_LENGTH];	/* NVMEFC_TRADDR=...*/
	अक्षर *envp[4] = अणु "FC_EVENT=nvmediscovery", hostaddr, tgtaddr, शून्य पूर्ण;

	अगर (!(rport->remoteport.port_role & FC_PORT_ROLE_NVME_DISCOVERY))
		वापस;

	snम_लिखो(hostaddr, माप(hostaddr),
		"NVMEFC_HOST_TRADDR=nn-0x%016llx:pn-0x%016llx",
		lport->localport.node_name, lport->localport.port_name);
	snम_लिखो(tgtaddr, माप(tgtaddr),
		"NVMEFC_TRADDR=nn-0x%016llx:pn-0x%016llx",
		rport->remoteport.node_name, rport->remoteport.port_name);
	kobject_uevent_env(&fc_udev_device->kobj, KOBJ_CHANGE, envp);
पूर्ण

अटल व्योम
nvme_fc_मुक्त_rport(काष्ठा kref *ref)
अणु
	काष्ठा nvme_fc_rport *rport =
		container_of(ref, काष्ठा nvme_fc_rport, ref);
	काष्ठा nvme_fc_lport *lport =
			localport_to_lport(rport->remoteport.localport);
	अचिन्हित दीर्घ flags;

	WARN_ON(rport->remoteport.port_state != FC_OBJSTATE_DELETED);
	WARN_ON(!list_empty(&rport->ctrl_list));

	/* हटाओ from lport list */
	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_del(&rport->endp_list);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	WARN_ON(!list_empty(&rport->disc_list));
	ida_simple_हटाओ(&lport->endp_cnt, rport->remoteport.port_num);

	kमुक्त(rport);

	nvme_fc_lport_put(lport);
पूर्ण

अटल व्योम
nvme_fc_rport_put(काष्ठा nvme_fc_rport *rport)
अणु
	kref_put(&rport->ref, nvme_fc_मुक्त_rport);
पूर्ण

अटल पूर्णांक
nvme_fc_rport_get(काष्ठा nvme_fc_rport *rport)
अणु
	वापस kref_get_unless_zero(&rport->ref);
पूर्ण

अटल व्योम
nvme_fc_resume_controller(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	चयन (ctrl->ctrl.state) अणु
	हाल NVME_CTRL_NEW:
	हाल NVME_CTRL_CONNECTING:
		/*
		 * As all reconnects were suppressed, schedule a
		 * connect.
		 */
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: connectivity re-established. "
			"Attempting reconnect\n", ctrl->cnum);

		queue_delayed_work(nvme_wq, &ctrl->connect_work, 0);
		अवरोध;

	हाल NVME_CTRL_RESETTING:
		/*
		 * Controller is alपढ़ोy in the process of terminating the
		 * association. No need to करो anything further. The reconnect
		 * step will naturally occur after the reset completes.
		 */
		अवरोध;

	शेष:
		/* no action to take - let it delete */
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा nvme_fc_rport *
nvme_fc_attach_to_suspended_rport(काष्ठा nvme_fc_lport *lport,
				काष्ठा nvme_fc_port_info *pinfo)
अणु
	काष्ठा nvme_fc_rport *rport;
	काष्ठा nvme_fc_ctrl *ctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvme_fc_lock, flags);

	list_क्रम_each_entry(rport, &lport->endp_list, endp_list) अणु
		अगर (rport->remoteport.node_name != pinfo->node_name ||
		    rport->remoteport.port_name != pinfo->port_name)
			जारी;

		अगर (!nvme_fc_rport_get(rport)) अणु
			rport = ERR_PTR(-ENOLCK);
			जाओ out_करोne;
		पूर्ण

		spin_unlock_irqrestore(&nvme_fc_lock, flags);

		spin_lock_irqsave(&rport->lock, flags);

		/* has it been unरेजिस्टरed */
		अगर (rport->remoteport.port_state != FC_OBJSTATE_DELETED) अणु
			/* means lldd called us twice */
			spin_unlock_irqrestore(&rport->lock, flags);
			nvme_fc_rport_put(rport);
			वापस ERR_PTR(-ESTALE);
		पूर्ण

		rport->remoteport.port_role = pinfo->port_role;
		rport->remoteport.port_id = pinfo->port_id;
		rport->remoteport.port_state = FC_OBJSTATE_ONLINE;
		rport->dev_loss_end = 0;

		/*
		 * kick off a reconnect attempt on all associations to the
		 * remote port. A successful reconnects will resume i/o.
		 */
		list_क्रम_each_entry(ctrl, &rport->ctrl_list, ctrl_list)
			nvme_fc_resume_controller(ctrl);

		spin_unlock_irqrestore(&rport->lock, flags);

		वापस rport;
	पूर्ण

	rport = शून्य;

out_करोne:
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	वापस rport;
पूर्ण

अटल अंतरभूत व्योम
__nvme_fc_set_dev_loss_पंचांगo(काष्ठा nvme_fc_rport *rport,
			काष्ठा nvme_fc_port_info *pinfo)
अणु
	अगर (pinfo->dev_loss_पंचांगo)
		rport->remoteport.dev_loss_पंचांगo = pinfo->dev_loss_पंचांगo;
	अन्यथा
		rport->remoteport.dev_loss_पंचांगo = NVME_FC_DEFAULT_DEV_LOSS_TMO;
पूर्ण

/**
 * nvme_fc_रेजिस्टर_remoteport - transport entry poपूर्णांक called by an
 *                              LLDD to रेजिस्टर the existence of a NVME
 *                              subप्रणाली FC port on its fabric.
 * @localport: poपूर्णांकer to the (रेजिस्टरed) local port that the remote
 *             subप्रणाली port is connected to.
 * @pinfo:     poपूर्णांकer to inक्रमmation about the port to be रेजिस्टरed
 * @portptr:   poपूर्णांकer to a remote port poपूर्णांकer. Upon success, the routine
 *             will allocate a nvme_fc_remote_port काष्ठाure and place its
 *             address in the remote port poपूर्णांकer. Upon failure, remote port
 *             poपूर्णांकer will be set to 0.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvme_fc_रेजिस्टर_remoteport(काष्ठा nvme_fc_local_port *localport,
				काष्ठा nvme_fc_port_info *pinfo,
				काष्ठा nvme_fc_remote_port **portptr)
अणु
	काष्ठा nvme_fc_lport *lport = localport_to_lport(localport);
	काष्ठा nvme_fc_rport *newrec;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx;

	अगर (!nvme_fc_lport_get(lport)) अणु
		ret = -ESHUTDOWN;
		जाओ out_reghost_failed;
	पूर्ण

	/*
	 * look to see अगर there is alपढ़ोy a remoteport that is रुकोing
	 * क्रम a reconnect (within dev_loss_पंचांगo) with the same WWN's.
	 * If so, transition to it and reconnect.
	 */
	newrec = nvme_fc_attach_to_suspended_rport(lport, pinfo);

	/* found an rport, but something about its state is bad */
	अगर (IS_ERR(newrec)) अणु
		ret = PTR_ERR(newrec);
		जाओ out_lport_put;

	/* found existing rport, which was resumed */
	पूर्ण अन्यथा अगर (newrec) अणु
		nvme_fc_lport_put(lport);
		__nvme_fc_set_dev_loss_पंचांगo(newrec, pinfo);
		nvme_fc_संकेत_discovery_scan(lport, newrec);
		*portptr = &newrec->remoteport;
		वापस 0;
	पूर्ण

	/* nothing found - allocate a new remoteport काष्ठा */

	newrec = kदो_स्मृति((माप(*newrec) + lport->ops->remote_priv_sz),
			 GFP_KERNEL);
	अगर (!newrec) अणु
		ret = -ENOMEM;
		जाओ out_lport_put;
	पूर्ण

	idx = ida_simple_get(&lport->endp_cnt, 0, 0, GFP_KERNEL);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out_kमुक्त_rport;
	पूर्ण

	INIT_LIST_HEAD(&newrec->endp_list);
	INIT_LIST_HEAD(&newrec->ctrl_list);
	INIT_LIST_HEAD(&newrec->ls_req_list);
	INIT_LIST_HEAD(&newrec->disc_list);
	kref_init(&newrec->ref);
	atomic_set(&newrec->act_ctrl_cnt, 0);
	spin_lock_init(&newrec->lock);
	newrec->remoteport.localport = &lport->localport;
	INIT_LIST_HEAD(&newrec->ls_rcv_list);
	newrec->dev = lport->dev;
	newrec->lport = lport;
	अगर (lport->ops->remote_priv_sz)
		newrec->remoteport.निजी = &newrec[1];
	अन्यथा
		newrec->remoteport.निजी = शून्य;
	newrec->remoteport.port_role = pinfo->port_role;
	newrec->remoteport.node_name = pinfo->node_name;
	newrec->remoteport.port_name = pinfo->port_name;
	newrec->remoteport.port_id = pinfo->port_id;
	newrec->remoteport.port_state = FC_OBJSTATE_ONLINE;
	newrec->remoteport.port_num = idx;
	__nvme_fc_set_dev_loss_पंचांगo(newrec, pinfo);
	INIT_WORK(&newrec->lsrcv_work, nvme_fc_handle_ls_rqst_work);

	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_add_tail(&newrec->endp_list, &lport->endp_list);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	nvme_fc_संकेत_discovery_scan(lport, newrec);

	*portptr = &newrec->remoteport;
	वापस 0;

out_kमुक्त_rport:
	kमुक्त(newrec);
out_lport_put:
	nvme_fc_lport_put(lport);
out_reghost_failed:
	*portptr = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_रेजिस्टर_remoteport);

अटल पूर्णांक
nvme_fc_पात_lsops(काष्ठा nvme_fc_rport *rport)
अणु
	काष्ठा nvmefc_ls_req_op *lsop;
	अचिन्हित दीर्घ flags;

restart:
	spin_lock_irqsave(&rport->lock, flags);

	list_क्रम_each_entry(lsop, &rport->ls_req_list, lsreq_list) अणु
		अगर (!(lsop->flags & FCOP_FLAGS_TERMIO)) अणु
			lsop->flags |= FCOP_FLAGS_TERMIO;
			spin_unlock_irqrestore(&rport->lock, flags);
			rport->lport->ops->ls_पात(&rport->lport->localport,
						&rport->remoteport,
						&lsop->ls_req);
			जाओ restart;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rport->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम
nvme_fc_ctrl_connectivity_loss(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	dev_info(ctrl->ctrl.device,
		"NVME-FC{%d}: controller connectivity lost. Awaiting "
		"Reconnect", ctrl->cnum);

	चयन (ctrl->ctrl.state) अणु
	हाल NVME_CTRL_NEW:
	हाल NVME_CTRL_LIVE:
		/*
		 * Schedule a controller reset. The reset will terminate the
		 * association and schedule the reconnect समयr.  Reconnects
		 * will be attempted until either the ctlr_loss_पंचांगo
		 * (max_retries * connect_delay) expires or the remoteport's
		 * dev_loss_पंचांगo expires.
		 */
		अगर (nvme_reset_ctrl(&ctrl->ctrl)) अणु
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: Couldn't schedule reset.\n",
				ctrl->cnum);
			nvme_delete_ctrl(&ctrl->ctrl);
		पूर्ण
		अवरोध;

	हाल NVME_CTRL_CONNECTING:
		/*
		 * The association has alपढ़ोy been terminated and the
		 * controller is attempting reconnects.  No need to करो anything
		 * futher.  Reconnects will be attempted until either the
		 * ctlr_loss_पंचांगo (max_retries * connect_delay) expires or the
		 * remoteport's dev_loss_पंचांगo expires.
		 */
		अवरोध;

	हाल NVME_CTRL_RESETTING:
		/*
		 * Controller is alपढ़ोy in the process of terminating the
		 * association.  No need to करो anything further. The reconnect
		 * step will kick in naturally after the association is
		 * terminated.
		 */
		अवरोध;

	हाल NVME_CTRL_DELETING:
	हाल NVME_CTRL_DELETING_NOIO:
	शेष:
		/* no action to take - let it delete */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * nvme_fc_unरेजिस्टर_remoteport - transport entry poपूर्णांक called by an
 *                              LLDD to deरेजिस्टर/हटाओ a previously
 *                              रेजिस्टरed a NVME subप्रणाली FC port.
 * @portptr: poपूर्णांकer to the (रेजिस्टरed) remote port that is to be
 *           deरेजिस्टरed.
 *
 * Returns:
 * a completion status. Must be 0 upon success; a negative त्रुटि_सं
 * (ex: -ENXIO) upon failure.
 */
पूर्णांक
nvme_fc_unरेजिस्टर_remoteport(काष्ठा nvme_fc_remote_port *portptr)
अणु
	काष्ठा nvme_fc_rport *rport = remoteport_to_rport(portptr);
	काष्ठा nvme_fc_ctrl *ctrl;
	अचिन्हित दीर्घ flags;

	अगर (!portptr)
		वापस -EINVAL;

	spin_lock_irqsave(&rport->lock, flags);

	अगर (portptr->port_state != FC_OBJSTATE_ONLINE) अणु
		spin_unlock_irqrestore(&rport->lock, flags);
		वापस -EINVAL;
	पूर्ण
	portptr->port_state = FC_OBJSTATE_DELETED;

	rport->dev_loss_end = jअगरfies + (portptr->dev_loss_पंचांगo * HZ);

	list_क्रम_each_entry(ctrl, &rport->ctrl_list, ctrl_list) अणु
		/* अगर dev_loss_पंचांगo==0, dev loss is immediate */
		अगर (!portptr->dev_loss_पंचांगo) अणु
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: controller connectivity lost.\n",
				ctrl->cnum);
			nvme_delete_ctrl(&ctrl->ctrl);
		पूर्ण अन्यथा
			nvme_fc_ctrl_connectivity_loss(ctrl);
	पूर्ण

	spin_unlock_irqrestore(&rport->lock, flags);

	nvme_fc_पात_lsops(rport);

	अगर (atomic_पढ़ो(&rport->act_ctrl_cnt) == 0)
		rport->lport->ops->remoteport_delete(portptr);

	/*
	 * release the reference, which will allow, अगर all controllers
	 * go away, which should only occur after dev_loss_पंचांगo occurs,
	 * क्रम the rport to be torn करोwn.
	 */
	nvme_fc_rport_put(rport);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_unरेजिस्टर_remoteport);

/**
 * nvme_fc_rescan_remoteport - transport entry poपूर्णांक called by an
 *                              LLDD to request a nvme device rescan.
 * @remoteport: poपूर्णांकer to the (रेजिस्टरed) remote port that is to be
 *              rescanned.
 *
 * Returns: N/A
 */
व्योम
nvme_fc_rescan_remoteport(काष्ठा nvme_fc_remote_port *remoteport)
अणु
	काष्ठा nvme_fc_rport *rport = remoteport_to_rport(remoteport);

	nvme_fc_संकेत_discovery_scan(rport->lport, rport);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_rescan_remoteport);

पूर्णांक
nvme_fc_set_remoteport_devloss(काष्ठा nvme_fc_remote_port *portptr,
			u32 dev_loss_पंचांगo)
अणु
	काष्ठा nvme_fc_rport *rport = remoteport_to_rport(portptr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rport->lock, flags);

	अगर (portptr->port_state != FC_OBJSTATE_ONLINE) अणु
		spin_unlock_irqrestore(&rport->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* a dev_loss_पंचांगo of 0 (immediate) is allowed to be set */
	rport->remoteport.dev_loss_पंचांगo = dev_loss_पंचांगo;

	spin_unlock_irqrestore(&rport->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_set_remoteport_devloss);


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

/* *********************** FC-NVME LS Handling **************************** */

अटल व्योम nvme_fc_ctrl_put(काष्ठा nvme_fc_ctrl *);
अटल पूर्णांक nvme_fc_ctrl_get(काष्ठा nvme_fc_ctrl *);

अटल व्योम nvme_fc_error_recovery(काष्ठा nvme_fc_ctrl *ctrl, अक्षर *errmsg);

अटल व्योम
__nvme_fc_finish_ls_req(काष्ठा nvmefc_ls_req_op *lsop)
अणु
	काष्ठा nvme_fc_rport *rport = lsop->rport;
	काष्ठा nvmefc_ls_req *lsreq = &lsop->ls_req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rport->lock, flags);

	अगर (!lsop->req_queued) अणु
		spin_unlock_irqrestore(&rport->lock, flags);
		वापस;
	पूर्ण

	list_del(&lsop->lsreq_list);

	lsop->req_queued = false;

	spin_unlock_irqrestore(&rport->lock, flags);

	fc_dma_unmap_single(rport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIसूचीECTIONAL);

	nvme_fc_rport_put(rport);
पूर्ण

अटल पूर्णांक
__nvme_fc_send_ls_req(काष्ठा nvme_fc_rport *rport,
		काष्ठा nvmefc_ls_req_op *lsop,
		व्योम (*करोne)(काष्ठा nvmefc_ls_req *req, पूर्णांक status))
अणु
	काष्ठा nvmefc_ls_req *lsreq = &lsop->ls_req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
		वापस -ECONNREFUSED;

	अगर (!nvme_fc_rport_get(rport))
		वापस -ESHUTDOWN;

	lsreq->करोne = करोne;
	lsop->rport = rport;
	lsop->req_queued = false;
	INIT_LIST_HEAD(&lsop->lsreq_list);
	init_completion(&lsop->ls_करोne);

	lsreq->rqstdma = fc_dma_map_single(rport->dev, lsreq->rqstaddr,
				  lsreq->rqstlen + lsreq->rsplen,
				  DMA_BIसूचीECTIONAL);
	अगर (fc_dma_mapping_error(rport->dev, lsreq->rqstdma)) अणु
		ret = -EFAULT;
		जाओ out_putrport;
	पूर्ण
	lsreq->rspdma = lsreq->rqstdma + lsreq->rqstlen;

	spin_lock_irqsave(&rport->lock, flags);

	list_add_tail(&lsop->lsreq_list, &rport->ls_req_list);

	lsop->req_queued = true;

	spin_unlock_irqrestore(&rport->lock, flags);

	ret = rport->lport->ops->ls_req(&rport->lport->localport,
					&rport->remoteport, lsreq);
	अगर (ret)
		जाओ out_unlink;

	वापस 0;

out_unlink:
	lsop->ls_error = ret;
	spin_lock_irqsave(&rport->lock, flags);
	lsop->req_queued = false;
	list_del(&lsop->lsreq_list);
	spin_unlock_irqrestore(&rport->lock, flags);
	fc_dma_unmap_single(rport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIसूचीECTIONAL);
out_putrport:
	nvme_fc_rport_put(rport);

	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_send_ls_req_करोne(काष्ठा nvmefc_ls_req *lsreq, पूर्णांक status)
अणु
	काष्ठा nvmefc_ls_req_op *lsop = ls_req_to_lsop(lsreq);

	lsop->ls_error = status;
	complete(&lsop->ls_करोne);
पूर्ण

अटल पूर्णांक
nvme_fc_send_ls_req(काष्ठा nvme_fc_rport *rport, काष्ठा nvmefc_ls_req_op *lsop)
अणु
	काष्ठा nvmefc_ls_req *lsreq = &lsop->ls_req;
	काष्ठा fcnvme_ls_rjt *rjt = lsreq->rspaddr;
	पूर्णांक ret;

	ret = __nvme_fc_send_ls_req(rport, lsop, nvme_fc_send_ls_req_करोne);

	अगर (!ret) अणु
		/*
		 * No समयout/not पूर्णांकerruptible as we need the काष्ठा
		 * to exist until the lldd calls us back. Thus mandate
		 * रुको until driver calls back. lldd responsible क्रम
		 * the समयout action
		 */
		रुको_क्रम_completion(&lsop->ls_करोne);

		__nvme_fc_finish_ls_req(lsop);

		ret = lsop->ls_error;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* ACC or RJT payload ? */
	अगर (rjt->w0.ls_cmd == FCNVME_LS_RJT)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
nvme_fc_send_ls_req_async(काष्ठा nvme_fc_rport *rport,
		काष्ठा nvmefc_ls_req_op *lsop,
		व्योम (*करोne)(काष्ठा nvmefc_ls_req *req, पूर्णांक status))
अणु
	/* करोn't रुको क्रम completion */

	वापस __nvme_fc_send_ls_req(rport, lsop, करोne);
पूर्ण

अटल पूर्णांक
nvme_fc_connect_admin_queue(काष्ठा nvme_fc_ctrl *ctrl,
	काष्ठा nvme_fc_queue *queue, u16 qsize, u16 ersp_ratio)
अणु
	काष्ठा nvmefc_ls_req_op *lsop;
	काष्ठा nvmefc_ls_req *lsreq;
	काष्ठा fcnvme_ls_cr_assoc_rqst *assoc_rqst;
	काष्ठा fcnvme_ls_cr_assoc_acc *assoc_acc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, fcret = 0;

	lsop = kzalloc((माप(*lsop) +
			 माप(*assoc_rqst) + माप(*assoc_acc) +
			 ctrl->lport->ops->lsrqst_priv_sz), GFP_KERNEL);
	अगर (!lsop) अणु
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: send Create Association failed: ENOMEM\n",
			ctrl->cnum);
		ret = -ENOMEM;
		जाओ out_no_memory;
	पूर्ण

	assoc_rqst = (काष्ठा fcnvme_ls_cr_assoc_rqst *)&lsop[1];
	assoc_acc = (काष्ठा fcnvme_ls_cr_assoc_acc *)&assoc_rqst[1];
	lsreq = &lsop->ls_req;
	अगर (ctrl->lport->ops->lsrqst_priv_sz)
		lsreq->निजी = &assoc_acc[1];
	अन्यथा
		lsreq->निजी = शून्य;

	assoc_rqst->w0.ls_cmd = FCNVME_LS_CREATE_ASSOCIATION;
	assoc_rqst->desc_list_len =
			cpu_to_be32(माप(काष्ठा fcnvme_lsdesc_cr_assoc_cmd));

	assoc_rqst->assoc_cmd.desc_tag =
			cpu_to_be32(FCNVME_LSDESC_CREATE_ASSOC_CMD);
	assoc_rqst->assoc_cmd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_cr_assoc_cmd));

	assoc_rqst->assoc_cmd.ersp_ratio = cpu_to_be16(ersp_ratio);
	assoc_rqst->assoc_cmd.sqsize = cpu_to_be16(qsize - 1);
	/* Linux supports only Dynamic controllers */
	assoc_rqst->assoc_cmd.cntlid = cpu_to_be16(0xffff);
	uuid_copy(&assoc_rqst->assoc_cmd.hostid, &ctrl->ctrl.opts->host->id);
	म_नकलन(assoc_rqst->assoc_cmd.hostnqn, ctrl->ctrl.opts->host->nqn,
		min(FCNVME_ASSOC_HOSTNQN_LEN, NVMF_NQN_SIZE));
	म_नकलन(assoc_rqst->assoc_cmd.subnqn, ctrl->ctrl.opts->subsysnqn,
		min(FCNVME_ASSOC_SUBNQN_LEN, NVMF_NQN_SIZE));

	lsop->queue = queue;
	lsreq->rqstaddr = assoc_rqst;
	lsreq->rqstlen = माप(*assoc_rqst);
	lsreq->rspaddr = assoc_acc;
	lsreq->rsplen = माप(*assoc_acc);
	lsreq->समयout = NVME_FC_LS_TIMEOUT_SEC;

	ret = nvme_fc_send_ls_req(ctrl->rport, lsop);
	अगर (ret)
		जाओ out_मुक्त_buffer;

	/* process connect LS completion */

	/* validate the ACC response */
	अगर (assoc_acc->hdr.w0.ls_cmd != FCNVME_LS_ACC)
		fcret = VERR_LSACC;
	अन्यथा अगर (assoc_acc->hdr.desc_list_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_cr_assoc_acc)))
		fcret = VERR_CR_ASSOC_ACC_LEN;
	अन्यथा अगर (assoc_acc->hdr.rqst.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_RQST))
		fcret = VERR_LSDESC_RQST;
	अन्यथा अगर (assoc_acc->hdr.rqst.desc_len !=
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_rqst)))
		fcret = VERR_LSDESC_RQST_LEN;
	अन्यथा अगर (assoc_acc->hdr.rqst.w0.ls_cmd != FCNVME_LS_CREATE_ASSOCIATION)
		fcret = VERR_CR_ASSOC;
	अन्यथा अगर (assoc_acc->associd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_ASSOC_ID))
		fcret = VERR_ASSOC_ID;
	अन्यथा अगर (assoc_acc->associd.desc_len !=
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id)))
		fcret = VERR_ASSOC_ID_LEN;
	अन्यथा अगर (assoc_acc->connectid.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CONN_ID))
		fcret = VERR_CONN_ID;
	अन्यथा अगर (assoc_acc->connectid.desc_len !=
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_conn_id)))
		fcret = VERR_CONN_ID_LEN;

	अगर (fcret) अणु
		ret = -EBADF;
		dev_err(ctrl->dev,
			"q %d Create Association LS failed: %s\n",
			queue->qnum, validation_errors[fcret]);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ctrl->lock, flags);
		ctrl->association_id =
			be64_to_cpu(assoc_acc->associd.association_id);
		queue->connection_id =
			be64_to_cpu(assoc_acc->connectid.connection_id);
		set_bit(NVME_FC_Q_CONNECTED, &queue->flags);
		spin_unlock_irqrestore(&ctrl->lock, flags);
	पूर्ण

out_मुक्त_buffer:
	kमुक्त(lsop);
out_no_memory:
	अगर (ret)
		dev_err(ctrl->dev,
			"queue %d connect admin queue failed (%d).\n",
			queue->qnum, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvme_fc_connect_queue(काष्ठा nvme_fc_ctrl *ctrl, काष्ठा nvme_fc_queue *queue,
			u16 qsize, u16 ersp_ratio)
अणु
	काष्ठा nvmefc_ls_req_op *lsop;
	काष्ठा nvmefc_ls_req *lsreq;
	काष्ठा fcnvme_ls_cr_conn_rqst *conn_rqst;
	काष्ठा fcnvme_ls_cr_conn_acc *conn_acc;
	पूर्णांक ret, fcret = 0;

	lsop = kzalloc((माप(*lsop) +
			 माप(*conn_rqst) + माप(*conn_acc) +
			 ctrl->lport->ops->lsrqst_priv_sz), GFP_KERNEL);
	अगर (!lsop) अणु
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: send Create Connection failed: ENOMEM\n",
			ctrl->cnum);
		ret = -ENOMEM;
		जाओ out_no_memory;
	पूर्ण

	conn_rqst = (काष्ठा fcnvme_ls_cr_conn_rqst *)&lsop[1];
	conn_acc = (काष्ठा fcnvme_ls_cr_conn_acc *)&conn_rqst[1];
	lsreq = &lsop->ls_req;
	अगर (ctrl->lport->ops->lsrqst_priv_sz)
		lsreq->निजी = (व्योम *)&conn_acc[1];
	अन्यथा
		lsreq->निजी = शून्य;

	conn_rqst->w0.ls_cmd = FCNVME_LS_CREATE_CONNECTION;
	conn_rqst->desc_list_len = cpu_to_be32(
				माप(काष्ठा fcnvme_lsdesc_assoc_id) +
				माप(काष्ठा fcnvme_lsdesc_cr_conn_cmd));

	conn_rqst->associd.desc_tag = cpu_to_be32(FCNVME_LSDESC_ASSOC_ID);
	conn_rqst->associd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_assoc_id));
	conn_rqst->associd.association_id = cpu_to_be64(ctrl->association_id);
	conn_rqst->connect_cmd.desc_tag =
			cpu_to_be32(FCNVME_LSDESC_CREATE_CONN_CMD);
	conn_rqst->connect_cmd.desc_len =
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_lsdesc_cr_conn_cmd));
	conn_rqst->connect_cmd.ersp_ratio = cpu_to_be16(ersp_ratio);
	conn_rqst->connect_cmd.qid  = cpu_to_be16(queue->qnum);
	conn_rqst->connect_cmd.sqsize = cpu_to_be16(qsize - 1);

	lsop->queue = queue;
	lsreq->rqstaddr = conn_rqst;
	lsreq->rqstlen = माप(*conn_rqst);
	lsreq->rspaddr = conn_acc;
	lsreq->rsplen = माप(*conn_acc);
	lsreq->समयout = NVME_FC_LS_TIMEOUT_SEC;

	ret = nvme_fc_send_ls_req(ctrl->rport, lsop);
	अगर (ret)
		जाओ out_मुक्त_buffer;

	/* process connect LS completion */

	/* validate the ACC response */
	अगर (conn_acc->hdr.w0.ls_cmd != FCNVME_LS_ACC)
		fcret = VERR_LSACC;
	अन्यथा अगर (conn_acc->hdr.desc_list_len !=
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_ls_cr_conn_acc)))
		fcret = VERR_CR_CONN_ACC_LEN;
	अन्यथा अगर (conn_acc->hdr.rqst.desc_tag != cpu_to_be32(FCNVME_LSDESC_RQST))
		fcret = VERR_LSDESC_RQST;
	अन्यथा अगर (conn_acc->hdr.rqst.desc_len !=
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_rqst)))
		fcret = VERR_LSDESC_RQST_LEN;
	अन्यथा अगर (conn_acc->hdr.rqst.w0.ls_cmd != FCNVME_LS_CREATE_CONNECTION)
		fcret = VERR_CR_CONN;
	अन्यथा अगर (conn_acc->connectid.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CONN_ID))
		fcret = VERR_CONN_ID;
	अन्यथा अगर (conn_acc->connectid.desc_len !=
			fcnvme_lsdesc_len(माप(काष्ठा fcnvme_lsdesc_conn_id)))
		fcret = VERR_CONN_ID_LEN;

	अगर (fcret) अणु
		ret = -EBADF;
		dev_err(ctrl->dev,
			"q %d Create I/O Connection LS failed: %s\n",
			queue->qnum, validation_errors[fcret]);
	पूर्ण अन्यथा अणु
		queue->connection_id =
			be64_to_cpu(conn_acc->connectid.connection_id);
		set_bit(NVME_FC_Q_CONNECTED, &queue->flags);
	पूर्ण

out_मुक्त_buffer:
	kमुक्त(lsop);
out_no_memory:
	अगर (ret)
		dev_err(ctrl->dev,
			"queue %d connect I/O queue failed (%d).\n",
			queue->qnum, ret);
	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_disconnect_assoc_करोne(काष्ठा nvmefc_ls_req *lsreq, पूर्णांक status)
अणु
	काष्ठा nvmefc_ls_req_op *lsop = ls_req_to_lsop(lsreq);

	__nvme_fc_finish_ls_req(lsop);

	/* fc-nvme initiator करोesn't care about success or failure of cmd */

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
 * The behavior of the fc-nvme initiator is such that it's
 * understanding of the association and connections will implicitly
 * be torn करोwn. The action is implicit as it may be due to a loss of
 * connectivity with the fc-nvme target, so you may never get a
 * response even अगर you tried.  As such, the action of this routine
 * is to asynchronously send the LS, ignore any results of the LS, and
 * जारी on with terminating the association. If the fc-nvme target
 * is present and receives the LS, it too can tear करोwn.
 */
अटल व्योम
nvme_fc_xmt_disconnect_assoc(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *discon_rqst;
	काष्ठा fcnvme_ls_disconnect_assoc_acc *discon_acc;
	काष्ठा nvmefc_ls_req_op *lsop;
	काष्ठा nvmefc_ls_req *lsreq;
	पूर्णांक ret;

	lsop = kzalloc((माप(*lsop) +
			माप(*discon_rqst) + माप(*discon_acc) +
			ctrl->lport->ops->lsrqst_priv_sz), GFP_KERNEL);
	अगर (!lsop) अणु
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: send Disconnect Association "
			"failed: ENOMEM\n",
			ctrl->cnum);
		वापस;
	पूर्ण

	discon_rqst = (काष्ठा fcnvme_ls_disconnect_assoc_rqst *)&lsop[1];
	discon_acc = (काष्ठा fcnvme_ls_disconnect_assoc_acc *)&discon_rqst[1];
	lsreq = &lsop->ls_req;
	अगर (ctrl->lport->ops->lsrqst_priv_sz)
		lsreq->निजी = (व्योम *)&discon_acc[1];
	अन्यथा
		lsreq->निजी = शून्य;

	nvmefc_fmt_lsreq_discon_assoc(lsreq, discon_rqst, discon_acc,
				ctrl->association_id);

	ret = nvme_fc_send_ls_req_async(ctrl->rport, lsop,
				nvme_fc_disconnect_assoc_करोne);
	अगर (ret)
		kमुक्त(lsop);
पूर्ण

अटल व्योम
nvme_fc_xmt_ls_rsp_करोne(काष्ठा nvmefc_ls_rsp *lsrsp)
अणु
	काष्ठा nvmefc_ls_rcv_op *lsop = lsrsp->nvme_fc_निजी;
	काष्ठा nvme_fc_rport *rport = lsop->rport;
	काष्ठा nvme_fc_lport *lport = rport->lport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rport->lock, flags);
	list_del(&lsop->lsrcv_list);
	spin_unlock_irqrestore(&rport->lock, flags);

	fc_dma_sync_single_क्रम_cpu(lport->dev, lsop->rspdma,
				माप(*lsop->rspbuf), DMA_TO_DEVICE);
	fc_dma_unmap_single(lport->dev, lsop->rspdma,
			माप(*lsop->rspbuf), DMA_TO_DEVICE);

	kमुक्त(lsop);

	nvme_fc_rport_put(rport);
पूर्ण

अटल व्योम
nvme_fc_xmt_ls_rsp(काष्ठा nvmefc_ls_rcv_op *lsop)
अणु
	काष्ठा nvme_fc_rport *rport = lsop->rport;
	काष्ठा nvme_fc_lport *lport = rport->lport;
	काष्ठा fcnvme_ls_rqst_w0 *w0 = &lsop->rqstbuf->w0;
	पूर्णांक ret;

	fc_dma_sync_single_क्रम_device(lport->dev, lsop->rspdma,
				  माप(*lsop->rspbuf), DMA_TO_DEVICE);

	ret = lport->ops->xmt_ls_rsp(&lport->localport, &rport->remoteport,
				     lsop->lsrsp);
	अगर (ret) अणु
		dev_warn(lport->dev,
			"LLDD rejected LS RSP xmt: LS %d status %d\n",
			w0->ls_cmd, ret);
		nvme_fc_xmt_ls_rsp_करोne(lsop->lsrsp);
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा nvme_fc_ctrl *
nvme_fc_match_disconn_ls(काष्ठा nvme_fc_rport *rport,
		      काष्ठा nvmefc_ls_rcv_op *lsop)
अणु
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *rqst =
					&lsop->rqstbuf->rq_dis_assoc;
	काष्ठा nvme_fc_ctrl *ctrl, *ret = शून्य;
	काष्ठा nvmefc_ls_rcv_op *oldls = शून्य;
	u64 association_id = be64_to_cpu(rqst->associd.association_id);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rport->lock, flags);

	list_क्रम_each_entry(ctrl, &rport->ctrl_list, ctrl_list) अणु
		अगर (!nvme_fc_ctrl_get(ctrl))
			जारी;
		spin_lock(&ctrl->lock);
		अगर (association_id == ctrl->association_id) अणु
			oldls = ctrl->rcv_disconn;
			ctrl->rcv_disconn = lsop;
			ret = ctrl;
		पूर्ण
		spin_unlock(&ctrl->lock);
		अगर (ret)
			/* leave the ctrl get reference */
			अवरोध;
		nvme_fc_ctrl_put(ctrl);
	पूर्ण

	spin_unlock_irqrestore(&rport->lock, flags);

	/* transmit a response क्रम anything that was pending */
	अगर (oldls) अणु
		dev_info(rport->lport->dev,
			"NVME-FC{%d}: Multiple Disconnect Association "
			"LS's received\n", ctrl->cnum);
		/* overग_लिखो good response with bogus failure */
		oldls->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(oldls->rspbuf,
						माप(*oldls->rspbuf),
						rqst->w0.ls_cmd,
						FCNVME_RJT_RC_UNAB,
						FCNVME_RJT_EXP_NONE, 0);
		nvme_fc_xmt_ls_rsp(oldls);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * वापसs true to mean LS handled and ls_rsp can be sent
 * वापसs false to defer ls_rsp xmt (will be करोne as part of
 *     association termination)
 */
अटल bool
nvme_fc_ls_disconnect_assoc(काष्ठा nvmefc_ls_rcv_op *lsop)
अणु
	काष्ठा nvme_fc_rport *rport = lsop->rport;
	काष्ठा fcnvme_ls_disconnect_assoc_rqst *rqst =
					&lsop->rqstbuf->rq_dis_assoc;
	काष्ठा fcnvme_ls_disconnect_assoc_acc *acc =
					&lsop->rspbuf->rsp_dis_assoc;
	काष्ठा nvme_fc_ctrl *ctrl = शून्य;
	पूर्णांक ret = 0;

	स_रखो(acc, 0, माप(*acc));

	ret = nvmefc_vldt_lsreq_discon_assoc(lsop->rqstdatalen, rqst);
	अगर (!ret) अणु
		/* match an active association */
		ctrl = nvme_fc_match_disconn_ls(rport, lsop);
		अगर (!ctrl)
			ret = VERR_NO_ASSOC;
	पूर्ण

	अगर (ret) अणु
		dev_info(rport->lport->dev,
			"Disconnect LS failed: %s\n",
			validation_errors[ret]);
		lsop->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(acc,
					माप(*acc), rqst->w0.ls_cmd,
					(ret == VERR_NO_ASSOC) ?
						FCNVME_RJT_RC_INV_ASSOC :
						FCNVME_RJT_RC_LOGIC,
					FCNVME_RJT_EXP_NONE, 0);
		वापस true;
	पूर्ण

	/* क्रमmat an ACCept response */

	lsop->lsrsp->rsplen = माप(*acc);

	nvme_fc_क्रमmat_rsp_hdr(acc, FCNVME_LS_ACC,
			fcnvme_lsdesc_len(
				माप(काष्ठा fcnvme_ls_disconnect_assoc_acc)),
			FCNVME_LS_DISCONNECT_ASSOC);

	/*
	 * the transmit of the response will occur after the exchanges
	 * क्रम the association have been ABTS'd by
	 * nvme_fc_delete_association().
	 */

	/* fail the association */
	nvme_fc_error_recovery(ctrl, "Disconnect Association LS received");

	/* release the reference taken by nvme_fc_match_disconn_ls() */
	nvme_fc_ctrl_put(ctrl);

	वापस false;
पूर्ण

/*
 * Actual Processing routine क्रम received FC-NVME LS Requests from the LLD
 * वापसs true अगर a response should be sent afterward, false अगर rsp will
 * be sent asynchronously.
 */
अटल bool
nvme_fc_handle_ls_rqst(काष्ठा nvmefc_ls_rcv_op *lsop)
अणु
	काष्ठा fcnvme_ls_rqst_w0 *w0 = &lsop->rqstbuf->w0;
	bool ret = true;

	lsop->lsrsp->nvme_fc_निजी = lsop;
	lsop->lsrsp->rspbuf = lsop->rspbuf;
	lsop->lsrsp->rspdma = lsop->rspdma;
	lsop->lsrsp->करोne = nvme_fc_xmt_ls_rsp_करोne;
	/* Be preventative. handlers will later set to valid length */
	lsop->lsrsp->rsplen = 0;

	/*
	 * handlers:
	 *   parse request input, execute the request, and क्रमmat the
	 *   LS response
	 */
	चयन (w0->ls_cmd) अणु
	हाल FCNVME_LS_DISCONNECT_ASSOC:
		ret = nvme_fc_ls_disconnect_assoc(lsop);
		अवरोध;
	हाल FCNVME_LS_DISCONNECT_CONN:
		lsop->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(lsop->rspbuf,
				माप(*lsop->rspbuf), w0->ls_cmd,
				FCNVME_RJT_RC_UNSUP, FCNVME_RJT_EXP_NONE, 0);
		अवरोध;
	हाल FCNVME_LS_CREATE_ASSOCIATION:
	हाल FCNVME_LS_CREATE_CONNECTION:
		lsop->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(lsop->rspbuf,
				माप(*lsop->rspbuf), w0->ls_cmd,
				FCNVME_RJT_RC_LOGIC, FCNVME_RJT_EXP_NONE, 0);
		अवरोध;
	शेष:
		lsop->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(lsop->rspbuf,
				माप(*lsop->rspbuf), w0->ls_cmd,
				FCNVME_RJT_RC_INVAL, FCNVME_RJT_EXP_NONE, 0);
		अवरोध;
	पूर्ण

	वापस(ret);
पूर्ण

अटल व्योम
nvme_fc_handle_ls_rqst_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_fc_rport *rport =
		container_of(work, काष्ठा nvme_fc_rport, lsrcv_work);
	काष्ठा fcnvme_ls_rqst_w0 *w0;
	काष्ठा nvmefc_ls_rcv_op *lsop;
	अचिन्हित दीर्घ flags;
	bool sendrsp;

restart:
	sendrsp = true;
	spin_lock_irqsave(&rport->lock, flags);
	list_क्रम_each_entry(lsop, &rport->ls_rcv_list, lsrcv_list) अणु
		अगर (lsop->handled)
			जारी;

		lsop->handled = true;
		अगर (rport->remoteport.port_state == FC_OBJSTATE_ONLINE) अणु
			spin_unlock_irqrestore(&rport->lock, flags);
			sendrsp = nvme_fc_handle_ls_rqst(lsop);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&rport->lock, flags);
			w0 = &lsop->rqstbuf->w0;
			lsop->lsrsp->rsplen = nvme_fc_क्रमmat_rjt(
						lsop->rspbuf,
						माप(*lsop->rspbuf),
						w0->ls_cmd,
						FCNVME_RJT_RC_UNAB,
						FCNVME_RJT_EXP_NONE, 0);
		पूर्ण
		अगर (sendrsp)
			nvme_fc_xmt_ls_rsp(lsop);
		जाओ restart;
	पूर्ण
	spin_unlock_irqrestore(&rport->lock, flags);
पूर्ण

/**
 * nvme_fc_rcv_ls_req - transport entry poपूर्णांक called by an LLDD
 *                       upon the reception of a NVME LS request.
 *
 * The nvme-fc layer will copy payload to an पूर्णांकernal काष्ठाure क्रम
 * processing.  As such, upon completion of the routine, the LLDD may
 * immediately मुक्त/reuse the LS request buffer passed in the call.
 *
 * If this routine वापसs error, the LLDD should पात the exchange.
 *
 * @portptr:    poपूर्णांकer to the (रेजिस्टरed) remote port that the LS
 *              was received from. The remoteport is associated with
 *              a specअगरic localport.
 * @lsrsp:      poपूर्णांकer to a nvmefc_ls_rsp response काष्ठाure to be
 *              used to reference the exchange corresponding to the LS
 *              when issuing an ls response.
 * @lsreqbuf:   poपूर्णांकer to the buffer containing the LS Request
 * @lsreqbuf_len: length, in bytes, of the received LS request
 */
पूर्णांक
nvme_fc_rcv_ls_req(काष्ठा nvme_fc_remote_port *portptr,
			काष्ठा nvmefc_ls_rsp *lsrsp,
			व्योम *lsreqbuf, u32 lsreqbuf_len)
अणु
	काष्ठा nvme_fc_rport *rport = remoteport_to_rport(portptr);
	काष्ठा nvme_fc_lport *lport = rport->lport;
	काष्ठा fcnvme_ls_rqst_w0 *w0 = (काष्ठा fcnvme_ls_rqst_w0 *)lsreqbuf;
	काष्ठा nvmefc_ls_rcv_op *lsop;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	nvme_fc_rport_get(rport);

	/* validate there's a routine to transmit a response */
	अगर (!lport->ops->xmt_ls_rsp) अणु
		dev_info(lport->dev,
			"RCV %s LS failed: no LLDD xmt_ls_rsp\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		ret = -EINVAL;
		जाओ out_put;
	पूर्ण

	अगर (lsreqbuf_len > माप(जोड़ nvmefc_ls_requests)) अणु
		dev_info(lport->dev,
			"RCV %s LS failed: payload too large\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		ret = -E2BIG;
		जाओ out_put;
	पूर्ण

	lsop = kzalloc(माप(*lsop) +
			माप(जोड़ nvmefc_ls_requests) +
			माप(जोड़ nvmefc_ls_responses),
			GFP_KERNEL);
	अगर (!lsop) अणु
		dev_info(lport->dev,
			"RCV %s LS failed: No memory\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण
	lsop->rqstbuf = (जोड़ nvmefc_ls_requests *)&lsop[1];
	lsop->rspbuf = (जोड़ nvmefc_ls_responses *)&lsop->rqstbuf[1];

	lsop->rspdma = fc_dma_map_single(lport->dev, lsop->rspbuf,
					माप(*lsop->rspbuf),
					DMA_TO_DEVICE);
	अगर (fc_dma_mapping_error(lport->dev, lsop->rspdma)) अणु
		dev_info(lport->dev,
			"RCV %s LS failed: DMA mapping failure\n",
			(w0->ls_cmd <= NVME_FC_LAST_LS_CMD_VALUE) ?
				nvmefc_ls_names[w0->ls_cmd] : "");
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	lsop->rport = rport;
	lsop->lsrsp = lsrsp;

	स_नकल(lsop->rqstbuf, lsreqbuf, lsreqbuf_len);
	lsop->rqstdatalen = lsreqbuf_len;

	spin_lock_irqsave(&rport->lock, flags);
	अगर (rport->remoteport.port_state != FC_OBJSTATE_ONLINE) अणु
		spin_unlock_irqrestore(&rport->lock, flags);
		ret = -ENOTCONN;
		जाओ out_unmap;
	पूर्ण
	list_add_tail(&lsop->lsrcv_list, &rport->ls_rcv_list);
	spin_unlock_irqrestore(&rport->lock, flags);

	schedule_work(&rport->lsrcv_work);

	वापस 0;

out_unmap:
	fc_dma_unmap_single(lport->dev, lsop->rspdma,
			माप(*lsop->rspbuf), DMA_TO_DEVICE);
out_मुक्त:
	kमुक्त(lsop);
out_put:
	nvme_fc_rport_put(rport);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fc_rcv_ls_req);


/* *********************** NVME Ctrl Routines **************************** */

अटल व्योम
__nvme_fc_निकास_request(काष्ठा nvme_fc_ctrl *ctrl,
		काष्ठा nvme_fc_fcp_op *op)
अणु
	fc_dma_unmap_single(ctrl->lport->dev, op->fcp_req.rspdma,
				माप(op->rsp_iu), DMA_FROM_DEVICE);
	fc_dma_unmap_single(ctrl->lport->dev, op->fcp_req.cmddma,
				माप(op->cmd_iu), DMA_TO_DEVICE);

	atomic_set(&op->state, FCPOP_STATE_UNINIT);
पूर्ण

अटल व्योम
nvme_fc_निकास_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);

	वापस __nvme_fc_निकास_request(set->driver_data, op);
पूर्ण

अटल पूर्णांक
__nvme_fc_पात_op(काष्ठा nvme_fc_ctrl *ctrl, काष्ठा nvme_fc_fcp_op *op)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक opstate;

	spin_lock_irqsave(&ctrl->lock, flags);
	opstate = atomic_xchg(&op->state, FCPOP_STATE_ABORTED);
	अगर (opstate != FCPOP_STATE_ACTIVE)
		atomic_set(&op->state, opstate);
	अन्यथा अगर (test_bit(FCCTRL_TERMIO, &ctrl->flags)) अणु
		op->flags |= FCOP_FLAGS_TERMIO;
		ctrl->iocnt++;
	पूर्ण
	spin_unlock_irqrestore(&ctrl->lock, flags);

	अगर (opstate != FCPOP_STATE_ACTIVE)
		वापस -ECANCELED;

	ctrl->lport->ops->fcp_पात(&ctrl->lport->localport,
					&ctrl->rport->remoteport,
					op->queue->lldd_handle,
					&op->fcp_req);

	वापस 0;
पूर्ण

अटल व्योम
nvme_fc_पात_aen_ops(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_fcp_op *aen_op = ctrl->aen_ops;
	पूर्णांक i;

	/* ensure we've initialized the ops once */
	अगर (!(aen_op->flags & FCOP_FLAGS_AEN))
		वापस;

	क्रम (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++)
		__nvme_fc_पात_op(ctrl, aen_op);
पूर्ण

अटल अंतरभूत व्योम
__nvme_fc_fcpop_chk_tearकरोwns(काष्ठा nvme_fc_ctrl *ctrl,
		काष्ठा nvme_fc_fcp_op *op, पूर्णांक opstate)
अणु
	अचिन्हित दीर्घ flags;

	अगर (opstate == FCPOP_STATE_ABORTED) अणु
		spin_lock_irqsave(&ctrl->lock, flags);
		अगर (test_bit(FCCTRL_TERMIO, &ctrl->flags) &&
		    op->flags & FCOP_FLAGS_TERMIO) अणु
			अगर (!--ctrl->iocnt)
				wake_up(&ctrl->ioपात_रुको);
		पूर्ण
		spin_unlock_irqrestore(&ctrl->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम
nvme_fc_ctrl_ioerr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_fc_ctrl *ctrl =
			container_of(work, काष्ठा nvme_fc_ctrl, ioerr_work);

	nvme_fc_error_recovery(ctrl, "transport detected io error");
पूर्ण

अटल व्योम
nvme_fc_fcpio_करोne(काष्ठा nvmefc_fcp_req *req)
अणु
	काष्ठा nvme_fc_fcp_op *op = fcp_req_to_fcp_op(req);
	काष्ठा request *rq = op->rq;
	काष्ठा nvmefc_fcp_req *freq = &op->fcp_req;
	काष्ठा nvme_fc_ctrl *ctrl = op->ctrl;
	काष्ठा nvme_fc_queue *queue = op->queue;
	काष्ठा nvme_completion *cqe = &op->rsp_iu.cqe;
	काष्ठा nvme_command *sqe = &op->cmd_iu.sqe;
	__le16 status = cpu_to_le16(NVME_SC_SUCCESS << 1);
	जोड़ nvme_result result;
	bool terminate_assoc = true;
	पूर्णांक opstate;

	/*
	 * WARNING:
	 * The current linux implementation of a nvme controller
	 * allocates a single tag set क्रम all io queues and sizes
	 * the io queues to fully hold all possible tags. Thus, the
	 * implementation करोes not reference or care about the sqhd
	 * value as it never needs to use the sqhd/sqtail poपूर्णांकers
	 * क्रम submission pacing.
	 *
	 * This affects the FC-NVME implementation in two ways:
	 * 1) As the value करोesn't matter, we don't need to waste
	 *    cycles extracting it from ERSPs and stamping it in the
	 *    हालs where the transport fabricates CQEs on successful
	 *    completions.
	 * 2) The FC-NVME implementation requires that delivery of
	 *    ERSP completions are to go back to the nvme layer in order
	 *    relative to the rsn, such that the sqhd value will always
	 *    be "in order" क्रम the nvme layer. As the nvme layer in
	 *    linux करोesn't care about sqhd, there's no need to वापस
	 *    them in order.
	 *
	 * Additionally:
	 * As the core nvme layer in linux currently करोes not look at
	 * every field in the cqe - in हालs where the FC transport must
	 * fabricate a CQE, the following fields will not be set as they
	 * are not referenced:
	 *      cqe.sqid,  cqe.sqhd,  cqe.command_id
	 *
	 * Failure or error of an inभागidual i/o, in a transport
	 * detected fashion unrelated to the nvme completion status,
	 * potentially cause the initiator and target sides to get out
	 * of sync on SQ head/tail (aka outstanding io count allowed).
	 * Per FC-NVME spec, failure of an inभागidual command requires
	 * the connection to be terminated, which in turn requires the
	 * association to be terminated.
	 */

	opstate = atomic_xchg(&op->state, FCPOP_STATE_COMPLETE);

	fc_dma_sync_single_क्रम_cpu(ctrl->lport->dev, op->fcp_req.rspdma,
				माप(op->rsp_iu), DMA_FROM_DEVICE);

	अगर (opstate == FCPOP_STATE_ABORTED)
		status = cpu_to_le16(NVME_SC_HOST_ABORTED_CMD << 1);
	अन्यथा अगर (freq->status) अणु
		status = cpu_to_le16(NVME_SC_HOST_PATH_ERROR << 1);
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: io failed due to lldd error %d\n",
			ctrl->cnum, freq->status);
	पूर्ण

	/*
	 * For the linux implementation, अगर we have an unsuccesful
	 * status, they blk-mq layer can typically be called with the
	 * non-zero status and the content of the cqe isn't important.
	 */
	अगर (status)
		जाओ करोne;

	/*
	 * command completed successfully relative to the wire
	 * protocol. However, validate anything received and
	 * extract the status and result from the cqe (create it
	 * where necessary).
	 */

	चयन (freq->rcv_rsplen) अणु

	हाल 0:
	हाल NVME_FC_SIZखातापूर्ण_ZEROS_RSP:
		/*
		 * No response payload or 12 bytes of payload (which
		 * should all be zeros) are considered successful and
		 * no payload in the CQE by the transport.
		 */
		अगर (freq->transferred_length !=
		    be32_to_cpu(op->cmd_iu.data_len)) अणु
			status = cpu_to_le16(NVME_SC_HOST_PATH_ERROR << 1);
			dev_info(ctrl->ctrl.device,
				"NVME-FC{%d}: io failed due to bad transfer "
				"length: %d vs expected %d\n",
				ctrl->cnum, freq->transferred_length,
				be32_to_cpu(op->cmd_iu.data_len));
			जाओ करोne;
		पूर्ण
		result.u64 = 0;
		अवरोध;

	हाल माप(काष्ठा nvme_fc_ersp_iu):
		/*
		 * The ERSP IU contains a full completion with CQE.
		 * Validate ERSP IU and look at cqe.
		 */
		अगर (unlikely(be16_to_cpu(op->rsp_iu.iu_len) !=
					(freq->rcv_rsplen / 4) ||
			     be32_to_cpu(op->rsp_iu.xfrd_len) !=
					freq->transferred_length ||
			     op->rsp_iu.ersp_result ||
			     sqe->common.command_id != cqe->command_id)) अणु
			status = cpu_to_le16(NVME_SC_HOST_PATH_ERROR << 1);
			dev_info(ctrl->ctrl.device,
				"NVME-FC{%d}: io failed due to bad NVMe_ERSP: "
				"iu len %d, xfr len %d vs %d, status code "
				"%d, cmdid %d vs %d\n",
				ctrl->cnum, be16_to_cpu(op->rsp_iu.iu_len),
				be32_to_cpu(op->rsp_iu.xfrd_len),
				freq->transferred_length,
				op->rsp_iu.ersp_result,
				sqe->common.command_id,
				cqe->command_id);
			जाओ करोne;
		पूर्ण
		result = cqe->result;
		status = cqe->status;
		अवरोध;

	शेष:
		status = cpu_to_le16(NVME_SC_HOST_PATH_ERROR << 1);
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: io failed due to odd NVMe_xRSP iu "
			"len %d\n",
			ctrl->cnum, freq->rcv_rsplen);
		जाओ करोne;
	पूर्ण

	terminate_assoc = false;

करोne:
	अगर (op->flags & FCOP_FLAGS_AEN) अणु
		nvme_complete_async_event(&queue->ctrl->ctrl, status, &result);
		__nvme_fc_fcpop_chk_tearकरोwns(ctrl, op, opstate);
		atomic_set(&op->state, FCPOP_STATE_IDLE);
		op->flags = FCOP_FLAGS_AEN;	/* clear other flags */
		nvme_fc_ctrl_put(ctrl);
		जाओ check_error;
	पूर्ण

	__nvme_fc_fcpop_chk_tearकरोwns(ctrl, op, opstate);
	अगर (!nvme_try_complete_req(rq, status, result))
		nvme_fc_complete_rq(rq);

check_error:
	अगर (terminate_assoc && ctrl->ctrl.state != NVME_CTRL_RESETTING)
		queue_work(nvme_reset_wq, &ctrl->ioerr_work);
पूर्ण

अटल पूर्णांक
__nvme_fc_init_request(काष्ठा nvme_fc_ctrl *ctrl,
		काष्ठा nvme_fc_queue *queue, काष्ठा nvme_fc_fcp_op *op,
		काष्ठा request *rq, u32 rqno)
अणु
	काष्ठा nvme_fcp_op_w_sgl *op_w_sgl =
		container_of(op, typeof(*op_w_sgl), op);
	काष्ठा nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	पूर्णांक ret = 0;

	स_रखो(op, 0, माप(*op));
	op->fcp_req.cmdaddr = &op->cmd_iu;
	op->fcp_req.cmdlen = माप(op->cmd_iu);
	op->fcp_req.rspaddr = &op->rsp_iu;
	op->fcp_req.rsplen = माप(op->rsp_iu);
	op->fcp_req.करोne = nvme_fc_fcpio_करोne;
	op->ctrl = ctrl;
	op->queue = queue;
	op->rq = rq;
	op->rqno = rqno;

	cmdiu->क्रमmat_id = NVME_CMD_FORMAT_ID;
	cmdiu->fc_id = NVME_CMD_FC_ID;
	cmdiu->iu_len = cpu_to_be16(माप(*cmdiu) / माप(u32));
	अगर (queue->qnum)
		cmdiu->rsv_cat = fccmnd_set_cat_css(0,
					(NVME_CC_CSS_NVM >> NVME_CC_CSS_SHIFT));
	अन्यथा
		cmdiu->rsv_cat = fccmnd_set_cat_admin(0);

	op->fcp_req.cmddma = fc_dma_map_single(ctrl->lport->dev,
				&op->cmd_iu, माप(op->cmd_iu), DMA_TO_DEVICE);
	अगर (fc_dma_mapping_error(ctrl->lport->dev, op->fcp_req.cmddma)) अणु
		dev_err(ctrl->dev,
			"FCP Op failed - cmdiu dma mapping failed.\n");
		ret = -EFAULT;
		जाओ out_on_error;
	पूर्ण

	op->fcp_req.rspdma = fc_dma_map_single(ctrl->lport->dev,
				&op->rsp_iu, माप(op->rsp_iu),
				DMA_FROM_DEVICE);
	अगर (fc_dma_mapping_error(ctrl->lport->dev, op->fcp_req.rspdma)) अणु
		dev_err(ctrl->dev,
			"FCP Op failed - rspiu dma mapping failed.\n");
		ret = -EFAULT;
	पूर्ण

	atomic_set(&op->state, FCPOP_STATE_IDLE);
out_on_error:
	वापस ret;
पूर्ण

अटल पूर्णांक
nvme_fc_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
		अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = set->driver_data;
	काष्ठा nvme_fcp_op_w_sgl *op = blk_mq_rq_to_pdu(rq);
	पूर्णांक queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	काष्ठा nvme_fc_queue *queue = &ctrl->queues[queue_idx];
	पूर्णांक res;

	res = __nvme_fc_init_request(ctrl, queue, &op->op, rq, queue->rqcnt++);
	अगर (res)
		वापस res;
	op->op.fcp_req.first_sgl = op->sgl;
	op->op.fcp_req.निजी = &op->priv[0];
	nvme_req(rq)->ctrl = &ctrl->ctrl;
	nvme_req(rq)->cmd = &op->op.cmd_iu.sqe;
	वापस res;
पूर्ण

अटल पूर्णांक
nvme_fc_init_aen_ops(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_fcp_op *aen_op;
	काष्ठा nvme_fc_cmd_iu *cmdiu;
	काष्ठा nvme_command *sqe;
	व्योम *निजी = शून्य;
	पूर्णांक i, ret;

	aen_op = ctrl->aen_ops;
	क्रम (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++) अणु
		अगर (ctrl->lport->ops->fcprqst_priv_sz) अणु
			निजी = kzalloc(ctrl->lport->ops->fcprqst_priv_sz,
						GFP_KERNEL);
			अगर (!निजी)
				वापस -ENOMEM;
		पूर्ण

		cmdiu = &aen_op->cmd_iu;
		sqe = &cmdiu->sqe;
		ret = __nvme_fc_init_request(ctrl, &ctrl->queues[0],
				aen_op, (काष्ठा request *)शून्य,
				(NVME_AQ_BLK_MQ_DEPTH + i));
		अगर (ret) अणु
			kमुक्त(निजी);
			वापस ret;
		पूर्ण

		aen_op->flags = FCOP_FLAGS_AEN;
		aen_op->fcp_req.निजी = निजी;

		स_रखो(sqe, 0, माप(*sqe));
		sqe->common.opcode = nvme_admin_async_event;
		/* Note: core layer may overग_लिखो the sqe.command_id value */
		sqe->common.command_id = NVME_AQ_BLK_MQ_DEPTH + i;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
nvme_fc_term_aen_ops(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_fcp_op *aen_op;
	पूर्णांक i;

	cancel_work_sync(&ctrl->ctrl.async_event_work);
	aen_op = ctrl->aen_ops;
	क्रम (i = 0; i < NVME_NR_AEN_COMMANDS; i++, aen_op++) अणु
		__nvme_fc_निकास_request(ctrl, aen_op);

		kमुक्त(aen_op->fcp_req.निजी);
		aen_op->fcp_req.निजी = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
__nvme_fc_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा nvme_fc_ctrl *ctrl,
		अचिन्हित पूर्णांक qidx)
अणु
	काष्ठा nvme_fc_queue *queue = &ctrl->queues[qidx];

	hctx->driver_data = queue;
	queue->hctx = hctx;
पूर्ण

अटल पूर्णांक
nvme_fc_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = data;

	__nvme_fc_init_hctx(hctx, ctrl, hctx_idx + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvme_fc_init_admin_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = data;

	__nvme_fc_init_hctx(hctx, ctrl, hctx_idx);

	वापस 0;
पूर्ण

अटल व्योम
nvme_fc_init_queue(काष्ठा nvme_fc_ctrl *ctrl, पूर्णांक idx)
अणु
	काष्ठा nvme_fc_queue *queue;

	queue = &ctrl->queues[idx];
	स_रखो(queue, 0, माप(*queue));
	queue->ctrl = ctrl;
	queue->qnum = idx;
	atomic_set(&queue->csn, 0);
	queue->dev = ctrl->dev;

	अगर (idx > 0)
		queue->cmnd_capsule_len = ctrl->ctrl.ioccsz * 16;
	अन्यथा
		queue->cmnd_capsule_len = माप(काष्ठा nvme_command);

	/*
	 * Considered whether we should allocate buffers क्रम all SQEs
	 * and CQEs and dma map them - mapping their respective entries
	 * पूर्णांकo the request काष्ठाures (kernel vm addr and dma address)
	 * thus the driver could use the buffers/mappings directly.
	 * It only makes sense अगर the LLDD would use them क्रम its
	 * messaging api. It's very unlikely most adapter api's would use
	 * a native NVME sqe/cqe. More reasonable अगर FC-NVME IU payload
	 * काष्ठाures were used instead.
	 */
पूर्ण

/*
 * This routine terminates a queue at the transport level.
 * The transport has alपढ़ोy ensured that all outstanding ios on
 * the queue have been terminated.
 * The transport will send a Disconnect LS request to terminate
 * the queue's connection. Termination of the admin queue will also
 * terminate the association at the target.
 */
अटल व्योम
nvme_fc_मुक्त_queue(काष्ठा nvme_fc_queue *queue)
अणु
	अगर (!test_and_clear_bit(NVME_FC_Q_CONNECTED, &queue->flags))
		वापस;

	clear_bit(NVME_FC_Q_LIVE, &queue->flags);
	/*
	 * Current implementation never disconnects a single queue.
	 * It always terminates a whole association. So there is never
	 * a disconnect(queue) LS sent to the target.
	 */

	queue->connection_id = 0;
	atomic_set(&queue->csn, 0);
पूर्ण

अटल व्योम
__nvme_fc_delete_hw_queue(काष्ठा nvme_fc_ctrl *ctrl,
	काष्ठा nvme_fc_queue *queue, अचिन्हित पूर्णांक qidx)
अणु
	अगर (ctrl->lport->ops->delete_queue)
		ctrl->lport->ops->delete_queue(&ctrl->lport->localport, qidx,
				queue->lldd_handle);
	queue->lldd_handle = शून्य;
पूर्ण

अटल व्योम
nvme_fc_मुक्त_io_queues(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++)
		nvme_fc_मुक्त_queue(&ctrl->queues[i]);
पूर्ण

अटल पूर्णांक
__nvme_fc_create_hw_queue(काष्ठा nvme_fc_ctrl *ctrl,
	काष्ठा nvme_fc_queue *queue, अचिन्हित पूर्णांक qidx, u16 qsize)
अणु
	पूर्णांक ret = 0;

	queue->lldd_handle = शून्य;
	अगर (ctrl->lport->ops->create_queue)
		ret = ctrl->lport->ops->create_queue(&ctrl->lport->localport,
				qidx, qsize, &queue->lldd_handle);

	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_delete_hw_io_queues(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_queue *queue = &ctrl->queues[ctrl->ctrl.queue_count - 1];
	पूर्णांक i;

	क्रम (i = ctrl->ctrl.queue_count - 1; i >= 1; i--, queue--)
		__nvme_fc_delete_hw_queue(ctrl, queue, i);
पूर्ण

अटल पूर्णांक
nvme_fc_create_hw_io_queues(काष्ठा nvme_fc_ctrl *ctrl, u16 qsize)
अणु
	काष्ठा nvme_fc_queue *queue = &ctrl->queues[1];
	पूर्णांक i, ret;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++, queue++) अणु
		ret = __nvme_fc_create_hw_queue(ctrl, queue, i, qsize);
		अगर (ret)
			जाओ delete_queues;
	पूर्ण

	वापस 0;

delete_queues:
	क्रम (; i > 0; i--)
		__nvme_fc_delete_hw_queue(ctrl, &ctrl->queues[i], i);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvme_fc_connect_io_queues(काष्ठा nvme_fc_ctrl *ctrl, u16 qsize)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++) अणु
		ret = nvme_fc_connect_queue(ctrl, &ctrl->queues[i], qsize,
					(qsize / 5));
		अगर (ret)
			अवरोध;
		ret = nvmf_connect_io_queue(&ctrl->ctrl, i, false);
		अगर (ret)
			अवरोध;

		set_bit(NVME_FC_Q_LIVE, &ctrl->queues[i].flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_init_io_queues(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++)
		nvme_fc_init_queue(ctrl, i);
पूर्ण

अटल व्योम
nvme_fc_ctrl_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvme_fc_ctrl *ctrl =
		container_of(ref, काष्ठा nvme_fc_ctrl, ref);
	अचिन्हित दीर्घ flags;

	अगर (ctrl->ctrl.tagset) अणु
		blk_cleanup_queue(ctrl->ctrl.connect_q);
		blk_mq_मुक्त_tag_set(&ctrl->tag_set);
	पूर्ण

	/* हटाओ from rport list */
	spin_lock_irqsave(&ctrl->rport->lock, flags);
	list_del(&ctrl->ctrl_list);
	spin_unlock_irqrestore(&ctrl->rport->lock, flags);

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);
	blk_cleanup_queue(ctrl->ctrl.admin_q);
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
	blk_mq_मुक्त_tag_set(&ctrl->admin_tag_set);

	kमुक्त(ctrl->queues);

	put_device(ctrl->dev);
	nvme_fc_rport_put(ctrl->rport);

	ida_simple_हटाओ(&nvme_fc_ctrl_cnt, ctrl->cnum);
	अगर (ctrl->ctrl.opts)
		nvmf_मुक्त_options(ctrl->ctrl.opts);
	kमुक्त(ctrl);
पूर्ण

अटल व्योम
nvme_fc_ctrl_put(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	kref_put(&ctrl->ref, nvme_fc_ctrl_मुक्त);
पूर्ण

अटल पूर्णांक
nvme_fc_ctrl_get(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	वापस kref_get_unless_zero(&ctrl->ref);
पूर्ण

/*
 * All accesses from nvme core layer करोne - can now मुक्त the
 * controller. Called after last nvme_put_ctrl() call
 */
अटल व्योम
nvme_fc_nvme_ctrl_मुक्तd(काष्ठा nvme_ctrl *nctrl)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = to_fc_ctrl(nctrl);

	WARN_ON(nctrl != &ctrl->ctrl);

	nvme_fc_ctrl_put(ctrl);
पूर्ण

/*
 * This routine is used by the transport when it needs to find active
 * io on a queue that is to be terminated. The transport uses
 * blk_mq_tagset_busy_itr() to find the busy requests, which then invoke
 * this routine to समाप्त them on a 1 by 1 basis.
 *
 * As FC allocates FC exchange क्रम each io, the transport must contact
 * the LLDD to terminate the exchange, thus releasing the FC exchange.
 * After terminating the exchange the LLDD will call the transport's
 * normal io करोne path क्रम the request, but it will have an पातed
 * status. The करोne path will वापस the io request back to the block
 * layer with an error status.
 */
अटल bool
nvme_fc_terminate_exchange(काष्ठा request *req, व्योम *data, bool reserved)
अणु
	काष्ठा nvme_ctrl *nctrl = data;
	काष्ठा nvme_fc_ctrl *ctrl = to_fc_ctrl(nctrl);
	काष्ठा nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(req);

	op->nreq.flags |= NVME_REQ_CANCELLED;
	__nvme_fc_पात_op(ctrl, op);
	वापस true;
पूर्ण

/*
 * This routine runs through all outstanding commands on the association
 * and पातs them.  This routine is typically be called by the
 * delete_association routine. It is also called due to an error during
 * reconnect. In that scenario, it is most likely a command that initializes
 * the controller, including fabric Connect commands on io queues, that
 * may have समयd out or failed thus the io must be समाप्तed क्रम the connect
 * thपढ़ो to see the error.
 */
अटल व्योम
__nvme_fc_पात_outstanding_ios(काष्ठा nvme_fc_ctrl *ctrl, bool start_queues)
अणु
	पूर्णांक q;

	/*
	 * अगर पातing io, the queues are no दीर्घer good, mark them
	 * all as not live.
	 */
	अगर (ctrl->ctrl.queue_count > 1) अणु
		क्रम (q = 1; q < ctrl->ctrl.queue_count; q++)
			clear_bit(NVME_FC_Q_LIVE, &ctrl->queues[q].flags);
	पूर्ण
	clear_bit(NVME_FC_Q_LIVE, &ctrl->queues[0].flags);

	/*
	 * If io queues are present, stop them and terminate all outstanding
	 * ios on them. As FC allocates FC exchange क्रम each io, the
	 * transport must contact the LLDD to terminate the exchange,
	 * thus releasing the FC exchange. We use blk_mq_tagset_busy_itr()
	 * to tell us what io's are busy and invoke a transport routine
	 * to समाप्त them with the LLDD.  After terminating the exchange
	 * the LLDD will call the transport's normal io करोne path, but it
	 * will have an पातed status. The करोne path will वापस the
	 * io requests back to the block layer as part of normal completions
	 * (but with error status).
	 */
	अगर (ctrl->ctrl.queue_count > 1) अणु
		nvme_stop_queues(&ctrl->ctrl);
		blk_mq_tagset_busy_iter(&ctrl->tag_set,
				nvme_fc_terminate_exchange, &ctrl->ctrl);
		blk_mq_tagset_रुको_completed_request(&ctrl->tag_set);
		अगर (start_queues)
			nvme_start_queues(&ctrl->ctrl);
	पूर्ण

	/*
	 * Other transports, which करोn't have link-level contexts bound
	 * to sqe's, would try to gracefully shutकरोwn the controller by
	 * writing the रेजिस्टरs क्रम shutकरोwn and polling (call
	 * nvme_shutकरोwn_ctrl()). Given a bunch of i/o was potentially
	 * just पातed and we will रुको on those contexts, and given
	 * there was no indication of how live the controlelr is on the
	 * link, करोn't send more io to create more contexts क्रम the
	 * shutकरोwn. Let the controller fail via keepalive failure अगर
	 * its still present.
	 */

	/*
	 * clean up the admin queue. Same thing as above.
	 */
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	blk_mq_tagset_busy_iter(&ctrl->admin_tag_set,
				nvme_fc_terminate_exchange, &ctrl->ctrl);
	blk_mq_tagset_रुको_completed_request(&ctrl->admin_tag_set);
पूर्ण

अटल व्योम
nvme_fc_error_recovery(काष्ठा nvme_fc_ctrl *ctrl, अक्षर *errmsg)
अणु
	/*
	 * अगर an error (io समयout, etc) जबतक (re)connecting, the remote
	 * port requested terminating of the association (disconnect_ls)
	 * or an error (समयout or पात) occurred on an io जबतक creating
	 * the controller.  Abort any ios on the association and let the
	 * create_association error path resolve things.
	 */
	अगर (ctrl->ctrl.state == NVME_CTRL_CONNECTING) अणु
		__nvme_fc_पात_outstanding_ios(ctrl, true);
		set_bit(ASSOC_FAILED, &ctrl->flags);
		वापस;
	पूर्ण

	/* Otherwise, only proceed अगर in LIVE state - e.g. on first error */
	अगर (ctrl->ctrl.state != NVME_CTRL_LIVE)
		वापस;

	dev_warn(ctrl->ctrl.device,
		"NVME-FC{%d}: transport association event: %s\n",
		ctrl->cnum, errmsg);
	dev_warn(ctrl->ctrl.device,
		"NVME-FC{%d}: resetting controller\n", ctrl->cnum);

	nvme_reset_ctrl(&ctrl->ctrl);
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस
nvme_fc_समयout(काष्ठा request *rq, bool reserved)
अणु
	काष्ठा nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_fc_ctrl *ctrl = op->ctrl;
	काष्ठा nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	काष्ठा nvme_command *sqe = &cmdiu->sqe;

	/*
	 * Attempt to पात the offending command. Command completion
	 * will detect the पातed io and will fail the connection.
	 */
	dev_info(ctrl->ctrl.device,
		"NVME-FC{%d.%d}: io timeout: opcode %d fctype %d w10/11: "
		"x%08x/x%08x\n",
		ctrl->cnum, op->queue->qnum, sqe->common.opcode,
		sqe->connect.fctype, sqe->common.cdw10, sqe->common.cdw11);
	अगर (__nvme_fc_पात_op(ctrl, op))
		nvme_fc_error_recovery(ctrl, "io timeout abort failed");

	/*
	 * the io पात has been initiated. Have the reset समयr
	 * restarted and the पात completion will complete the io
	 * लघुly. Aव्योमs a synchronous रुको जबतक the पात finishes.
	 */
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल पूर्णांक
nvme_fc_map_data(काष्ठा nvme_fc_ctrl *ctrl, काष्ठा request *rq,
		काष्ठा nvme_fc_fcp_op *op)
अणु
	काष्ठा nvmefc_fcp_req *freq = &op->fcp_req;
	पूर्णांक ret;

	freq->sg_cnt = 0;

	अगर (!blk_rq_nr_phys_segments(rq))
		वापस 0;

	freq->sg_table.sgl = freq->first_sgl;
	ret = sg_alloc_table_chained(&freq->sg_table,
			blk_rq_nr_phys_segments(rq), freq->sg_table.sgl,
			NVME_INLINE_SG_CNT);
	अगर (ret)
		वापस -ENOMEM;

	op->nents = blk_rq_map_sg(rq->q, rq, freq->sg_table.sgl);
	WARN_ON(op->nents > blk_rq_nr_phys_segments(rq));
	freq->sg_cnt = fc_dma_map_sg(ctrl->lport->dev, freq->sg_table.sgl,
				op->nents, rq_dma_dir(rq));
	अगर (unlikely(freq->sg_cnt <= 0)) अणु
		sg_मुक्त_table_chained(&freq->sg_table, NVME_INLINE_SG_CNT);
		freq->sg_cnt = 0;
		वापस -EFAULT;
	पूर्ण

	/*
	 * TODO: blk_पूर्णांकegrity_rq(rq)  क्रम DIF
	 */
	वापस 0;
पूर्ण

अटल व्योम
nvme_fc_unmap_data(काष्ठा nvme_fc_ctrl *ctrl, काष्ठा request *rq,
		काष्ठा nvme_fc_fcp_op *op)
अणु
	काष्ठा nvmefc_fcp_req *freq = &op->fcp_req;

	अगर (!freq->sg_cnt)
		वापस;

	fc_dma_unmap_sg(ctrl->lport->dev, freq->sg_table.sgl, op->nents,
			rq_dma_dir(rq));

	sg_मुक्त_table_chained(&freq->sg_table, NVME_INLINE_SG_CNT);

	freq->sg_cnt = 0;
पूर्ण

/*
 * In FC, the queue is a logical thing. At transport connect, the target
 * creates its "queue" and वापसs a handle that is to be given to the
 * target whenever it posts something to the corresponding SQ.  When an
 * SQE is sent on a SQ, FC effectively considers the SQE, or rather the
 * command contained within the SQE, an io, and assigns a FC exchange
 * to it. The SQE and the associated SQ handle are sent in the initial
 * CMD IU sents on the exchange. All transfers relative to the io occur
 * as part of the exchange.  The CQE is the last thing क्रम the io,
 * which is transferred (explicitly or implicitly) with the RSP IU
 * sent on the exchange. After the CQE is received, the FC exchange is
 * terminaed and the Exchange may be used on a dअगरferent io.
 *
 * The transport to LLDD api has the transport making a request क्रम a
 * new fcp io request to the LLDD. The LLDD then allocates a FC exchange
 * resource and transfers the command. The LLDD will then process all
 * steps to complete the io. Upon completion, the transport करोne routine
 * is called.
 *
 * So - जबतक the operation is outstanding to the LLDD, there is a link
 * level FC exchange resource that is also outstanding. This must be
 * considered in all cleanup operations.
 */
अटल blk_status_t
nvme_fc_start_fcp_op(काष्ठा nvme_fc_ctrl *ctrl, काष्ठा nvme_fc_queue *queue,
	काष्ठा nvme_fc_fcp_op *op, u32 data_len,
	क्रमागत nvmefc_fcp_datadir	io_dir)
अणु
	काष्ठा nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	काष्ठा nvme_command *sqe = &cmdiu->sqe;
	पूर्णांक ret, opstate;

	/*
	 * beक्रमe attempting to send the io, check to see अगर we believe
	 * the target device is present
	 */
	अगर (ctrl->rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
		वापस BLK_STS_RESOURCE;

	अगर (!nvme_fc_ctrl_get(ctrl))
		वापस BLK_STS_IOERR;

	/* क्रमmat the FC-NVME CMD IU and fcp_req */
	cmdiu->connection_id = cpu_to_be64(queue->connection_id);
	cmdiu->data_len = cpu_to_be32(data_len);
	चयन (io_dir) अणु
	हाल NVMEFC_FCP_WRITE:
		cmdiu->flags = FCNVME_CMD_FLAGS_WRITE;
		अवरोध;
	हाल NVMEFC_FCP_READ:
		cmdiu->flags = FCNVME_CMD_FLAGS_READ;
		अवरोध;
	हाल NVMEFC_FCP_NODATA:
		cmdiu->flags = 0;
		अवरोध;
	पूर्ण
	op->fcp_req.payload_length = data_len;
	op->fcp_req.io_dir = io_dir;
	op->fcp_req.transferred_length = 0;
	op->fcp_req.rcv_rsplen = 0;
	op->fcp_req.status = NVME_SC_SUCCESS;
	op->fcp_req.sqid = cpu_to_le16(queue->qnum);

	/*
	 * validate per fabric rules, set fields mandated by fabric spec
	 * as well as those by FC-NVME spec.
	 */
	WARN_ON_ONCE(sqe->common.metadata);
	sqe->common.flags |= NVME_CMD_SGL_METABUF;

	/*
	 * क्रमmat SQE DPTR field per FC-NVME rules:
	 *    type=0x5     Transport SGL Data Block Descriptor
	 *    subtype=0xA  Transport-specअगरic value
	 *    address=0
	 *    length=length of the data series
	 */
	sqe->rw.dptr.sgl.type = (NVME_TRANSPORT_SGL_DATA_DESC << 4) |
					NVME_SGL_FMT_TRANSPORT_A;
	sqe->rw.dptr.sgl.length = cpu_to_le32(data_len);
	sqe->rw.dptr.sgl.addr = 0;

	अगर (!(op->flags & FCOP_FLAGS_AEN)) अणु
		ret = nvme_fc_map_data(ctrl, op->rq, op);
		अगर (ret < 0) अणु
			nvme_cleanup_cmd(op->rq);
			nvme_fc_ctrl_put(ctrl);
			अगर (ret == -ENOMEM || ret == -EAGAIN)
				वापस BLK_STS_RESOURCE;
			वापस BLK_STS_IOERR;
		पूर्ण
	पूर्ण

	fc_dma_sync_single_क्रम_device(ctrl->lport->dev, op->fcp_req.cmddma,
				  माप(op->cmd_iu), DMA_TO_DEVICE);

	atomic_set(&op->state, FCPOP_STATE_ACTIVE);

	अगर (!(op->flags & FCOP_FLAGS_AEN))
		blk_mq_start_request(op->rq);

	cmdiu->csn = cpu_to_be32(atomic_inc_वापस(&queue->csn));
	ret = ctrl->lport->ops->fcp_io(&ctrl->lport->localport,
					&ctrl->rport->remoteport,
					queue->lldd_handle, &op->fcp_req);

	अगर (ret) अणु
		/*
		 * If the lld fails to send the command is there an issue with
		 * the csn value?  If the command that fails is the Connect,
		 * no - as the connection won't be live.  If it is a command
		 * post-connect, it's possible a gap in csn may be created.
		 * Does this matter?  As Linux initiators करोn't send fused
		 * commands, no.  The gap would exist, but as there's nothing
		 * that depends on csn order to be delivered on the target
		 * side, it shouldn't hurt.  It would be dअगरficult क्रम a
		 * target to even detect the csn gap as it has no idea when the
		 * cmd with the csn was supposed to arrive.
		 */
		opstate = atomic_xchg(&op->state, FCPOP_STATE_COMPLETE);
		__nvme_fc_fcpop_chk_tearकरोwns(ctrl, op, opstate);

		अगर (!(op->flags & FCOP_FLAGS_AEN)) अणु
			nvme_fc_unmap_data(ctrl, op->rq, op);
			nvme_cleanup_cmd(op->rq);
		पूर्ण

		nvme_fc_ctrl_put(ctrl);

		अगर (ctrl->rport->remoteport.port_state == FC_OBJSTATE_ONLINE &&
				ret != -EBUSY)
			वापस BLK_STS_IOERR;

		वापस BLK_STS_RESOURCE;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t
nvme_fc_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nvme_ns *ns = hctx->queue->queuedata;
	काष्ठा nvme_fc_queue *queue = hctx->driver_data;
	काष्ठा nvme_fc_ctrl *ctrl = queue->ctrl;
	काष्ठा request *rq = bd->rq;
	काष्ठा nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	क्रमागत nvmefc_fcp_datadir	io_dir;
	bool queue_पढ़ोy = test_bit(NVME_FC_Q_LIVE, &queue->flags);
	u32 data_len;
	blk_status_t ret;

	अगर (ctrl->rport->remoteport.port_state != FC_OBJSTATE_ONLINE ||
	    !nvme_check_पढ़ोy(&queue->ctrl->ctrl, rq, queue_पढ़ोy))
		वापस nvme_fail_nonपढ़ोy_command(&queue->ctrl->ctrl, rq);

	ret = nvme_setup_cmd(ns, rq);
	अगर (ret)
		वापस ret;

	/*
	 * nvme core करोesn't quite treat the rq opaquely. Commands such
	 * as WRITE ZEROES will वापस a non-zero rq payload_bytes yet
	 * there is no actual payload to be transferred.
	 * To get it right, key data transmission on there being 1 or
	 * more physical segments in the sg list. If there is no
	 * physical segments, there is no payload.
	 */
	अगर (blk_rq_nr_phys_segments(rq)) अणु
		data_len = blk_rq_payload_bytes(rq);
		io_dir = ((rq_data_dir(rq) == WRITE) ?
					NVMEFC_FCP_WRITE : NVMEFC_FCP_READ);
	पूर्ण अन्यथा अणु
		data_len = 0;
		io_dir = NVMEFC_FCP_NODATA;
	पूर्ण


	वापस nvme_fc_start_fcp_op(ctrl, queue, op, data_len, io_dir);
पूर्ण

अटल व्योम
nvme_fc_submit_async_event(काष्ठा nvme_ctrl *arg)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = to_fc_ctrl(arg);
	काष्ठा nvme_fc_fcp_op *aen_op;
	blk_status_t ret;

	अगर (test_bit(FCCTRL_TERMIO, &ctrl->flags))
		वापस;

	aen_op = &ctrl->aen_ops[0];

	ret = nvme_fc_start_fcp_op(ctrl, aen_op->queue, aen_op, 0,
					NVMEFC_FCP_NODATA);
	अगर (ret)
		dev_err(ctrl->ctrl.device,
			"failed async event work\n");
पूर्ण

अटल व्योम
nvme_fc_complete_rq(काष्ठा request *rq)
अणु
	काष्ठा nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_fc_ctrl *ctrl = op->ctrl;

	atomic_set(&op->state, FCPOP_STATE_IDLE);
	op->flags &= ~FCOP_FLAGS_TERMIO;

	nvme_fc_unmap_data(ctrl, rq, op);
	nvme_complete_rq(rq);
	nvme_fc_ctrl_put(ctrl);
पूर्ण


अटल स्थिर काष्ठा blk_mq_ops nvme_fc_mq_ops = अणु
	.queue_rq	= nvme_fc_queue_rq,
	.complete	= nvme_fc_complete_rq,
	.init_request	= nvme_fc_init_request,
	.निकास_request	= nvme_fc_निकास_request,
	.init_hctx	= nvme_fc_init_hctx,
	.समयout	= nvme_fc_समयout,
पूर्ण;

अटल पूर्णांक
nvme_fc_create_io_queues(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	अचिन्हित पूर्णांक nr_io_queues;
	पूर्णांक ret;

	nr_io_queues = min(min(opts->nr_io_queues, num_online_cpus()),
				ctrl->lport->ops->max_hw_queues);
	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	अगर (ret) अणु
		dev_info(ctrl->ctrl.device,
			"set_queue_count failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ctrl->ctrl.queue_count = nr_io_queues + 1;
	अगर (!nr_io_queues)
		वापस 0;

	nvme_fc_init_io_queues(ctrl);

	स_रखो(&ctrl->tag_set, 0, माप(ctrl->tag_set));
	ctrl->tag_set.ops = &nvme_fc_mq_ops;
	ctrl->tag_set.queue_depth = ctrl->ctrl.opts->queue_size;
	ctrl->tag_set.reserved_tags = NVMF_RESERVED_TAGS;
	ctrl->tag_set.numa_node = ctrl->ctrl.numa_node;
	ctrl->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ctrl->tag_set.cmd_size =
		काष्ठा_size((काष्ठा nvme_fcp_op_w_sgl *)शून्य, priv,
			    ctrl->lport->ops->fcprqst_priv_sz);
	ctrl->tag_set.driver_data = ctrl;
	ctrl->tag_set.nr_hw_queues = ctrl->ctrl.queue_count - 1;
	ctrl->tag_set.समयout = NVME_IO_TIMEOUT;

	ret = blk_mq_alloc_tag_set(&ctrl->tag_set);
	अगर (ret)
		वापस ret;

	ctrl->ctrl.tagset = &ctrl->tag_set;

	ctrl->ctrl.connect_q = blk_mq_init_queue(&ctrl->tag_set);
	अगर (IS_ERR(ctrl->ctrl.connect_q)) अणु
		ret = PTR_ERR(ctrl->ctrl.connect_q);
		जाओ out_मुक्त_tag_set;
	पूर्ण

	ret = nvme_fc_create_hw_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	अगर (ret)
		जाओ out_cleanup_blk_queue;

	ret = nvme_fc_connect_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	अगर (ret)
		जाओ out_delete_hw_queues;

	ctrl->ioq_live = true;

	वापस 0;

out_delete_hw_queues:
	nvme_fc_delete_hw_io_queues(ctrl);
out_cleanup_blk_queue:
	blk_cleanup_queue(ctrl->ctrl.connect_q);
out_मुक्त_tag_set:
	blk_mq_मुक्त_tag_set(&ctrl->tag_set);
	nvme_fc_मुक्त_io_queues(ctrl);

	/* क्रमce put मुक्त routine to ignore io queues */
	ctrl->ctrl.tagset = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक
nvme_fc_recreate_io_queues(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	u32 prior_ioq_cnt = ctrl->ctrl.queue_count - 1;
	अचिन्हित पूर्णांक nr_io_queues;
	पूर्णांक ret;

	nr_io_queues = min(min(opts->nr_io_queues, num_online_cpus()),
				ctrl->lport->ops->max_hw_queues);
	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	अगर (ret) अणु
		dev_info(ctrl->ctrl.device,
			"set_queue_count failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!nr_io_queues && prior_ioq_cnt) अणु
		dev_info(ctrl->ctrl.device,
			"Fail Reconnect: At least 1 io queue "
			"required (was %d)\n", prior_ioq_cnt);
		वापस -ENOSPC;
	पूर्ण

	ctrl->ctrl.queue_count = nr_io_queues + 1;
	/* check क्रम io queues existing */
	अगर (ctrl->ctrl.queue_count == 1)
		वापस 0;

	ret = nvme_fc_create_hw_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	अगर (ret)
		जाओ out_मुक्त_io_queues;

	ret = nvme_fc_connect_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	अगर (ret)
		जाओ out_delete_hw_queues;

	अगर (prior_ioq_cnt != nr_io_queues) अणु
		dev_info(ctrl->ctrl.device,
			"reconnect: revising io queue count from %d to %d\n",
			prior_ioq_cnt, nr_io_queues);
		nvme_रुको_मुक्तze(&ctrl->ctrl);
		blk_mq_update_nr_hw_queues(&ctrl->tag_set, nr_io_queues);
		nvme_unमुक्तze(&ctrl->ctrl);
	पूर्ण

	वापस 0;

out_delete_hw_queues:
	nvme_fc_delete_hw_io_queues(ctrl);
out_मुक्त_io_queues:
	nvme_fc_मुक्त_io_queues(ctrl);
	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_rport_active_on_lport(काष्ठा nvme_fc_rport *rport)
अणु
	काष्ठा nvme_fc_lport *lport = rport->lport;

	atomic_inc(&lport->act_rport_cnt);
पूर्ण

अटल व्योम
nvme_fc_rport_inactive_on_lport(काष्ठा nvme_fc_rport *rport)
अणु
	काष्ठा nvme_fc_lport *lport = rport->lport;
	u32 cnt;

	cnt = atomic_dec_वापस(&lport->act_rport_cnt);
	अगर (cnt == 0 && lport->localport.port_state == FC_OBJSTATE_DELETED)
		lport->ops->localport_delete(&lport->localport);
पूर्ण

अटल पूर्णांक
nvme_fc_ctlr_active_on_rport(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_rport *rport = ctrl->rport;
	u32 cnt;

	अगर (test_and_set_bit(ASSOC_ACTIVE, &ctrl->flags))
		वापस 1;

	cnt = atomic_inc_वापस(&rport->act_ctrl_cnt);
	अगर (cnt == 1)
		nvme_fc_rport_active_on_lport(rport);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvme_fc_ctlr_inactive_on_rport(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvme_fc_rport *rport = ctrl->rport;
	काष्ठा nvme_fc_lport *lport = rport->lport;
	u32 cnt;

	/* clearing of ctrl->flags ASSOC_ACTIVE bit is in association delete */

	cnt = atomic_dec_वापस(&rport->act_ctrl_cnt);
	अगर (cnt == 0) अणु
		अगर (rport->remoteport.port_state == FC_OBJSTATE_DELETED)
			lport->ops->remoteport_delete(&rport->remoteport);
		nvme_fc_rport_inactive_on_lport(rport);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This routine restarts the controller on the host side, and
 * on the link side, recreates the controller association.
 */
अटल पूर्णांक
nvme_fc_create_association(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	काष्ठा nvmefc_ls_rcv_op *disls = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool changed;

	++ctrl->ctrl.nr_reconnects;

	अगर (ctrl->rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
		वापस -ENODEV;

	अगर (nvme_fc_ctlr_active_on_rport(ctrl))
		वापस -ENOTUNIQ;

	dev_info(ctrl->ctrl.device,
		"NVME-FC{%d}: create association : host wwpn 0x%016llx "
		" rport wwpn 0x%016llx: NQN \"%s\"\n",
		ctrl->cnum, ctrl->lport->localport.port_name,
		ctrl->rport->remoteport.port_name, ctrl->ctrl.opts->subsysnqn);

	clear_bit(ASSOC_FAILED, &ctrl->flags);

	/*
	 * Create the admin queue
	 */

	ret = __nvme_fc_create_hw_queue(ctrl, &ctrl->queues[0], 0,
				NVME_AQ_DEPTH);
	अगर (ret)
		जाओ out_मुक्त_queue;

	ret = nvme_fc_connect_admin_queue(ctrl, &ctrl->queues[0],
				NVME_AQ_DEPTH, (NVME_AQ_DEPTH / 4));
	अगर (ret)
		जाओ out_delete_hw_queue;

	ret = nvmf_connect_admin_queue(&ctrl->ctrl);
	अगर (ret)
		जाओ out_disconnect_admin_queue;

	set_bit(NVME_FC_Q_LIVE, &ctrl->queues[0].flags);

	/*
	 * Check controller capabilities
	 *
	 * toकरो:- add code to check अगर ctrl attributes changed from
	 * prior connection values
	 */

	ret = nvme_enable_ctrl(&ctrl->ctrl);
	अगर (ret || test_bit(ASSOC_FAILED, &ctrl->flags))
		जाओ out_disconnect_admin_queue;

	ctrl->ctrl.max_segments = ctrl->lport->ops->max_sgl_segments;
	ctrl->ctrl.max_hw_sectors = ctrl->ctrl.max_segments <<
						(ilog2(SZ_4K) - 9);

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	ret = nvme_init_ctrl_finish(&ctrl->ctrl);
	अगर (ret || test_bit(ASSOC_FAILED, &ctrl->flags))
		जाओ out_disconnect_admin_queue;

	/* sanity checks */

	/* FC-NVME करोes not have other data in the capsule */
	अगर (ctrl->ctrl.icकरोff) अणु
		dev_err(ctrl->ctrl.device, "icdoff %d is not supported!\n",
				ctrl->ctrl.icकरोff);
		ret = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out_disconnect_admin_queue;
	पूर्ण

	/* FC-NVME supports normal SGL Data Block Descriptors */
	अगर (!(ctrl->ctrl.sgls & ((1 << 0) | (1 << 1)))) अणु
		dev_err(ctrl->ctrl.device,
			"Mandatory sgls are not supported!\n");
		ret = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out_disconnect_admin_queue;
	पूर्ण

	अगर (opts->queue_size > ctrl->ctrl.maxcmd) अणु
		/* warn अगर maxcmd is lower than queue_size */
		dev_warn(ctrl->ctrl.device,
			"queue_size %zu > ctrl maxcmd %u, reducing "
			"to maxcmd\n",
			opts->queue_size, ctrl->ctrl.maxcmd);
		opts->queue_size = ctrl->ctrl.maxcmd;
	पूर्ण

	अगर (opts->queue_size > ctrl->ctrl.sqsize + 1) अणु
		/* warn अगर sqsize is lower than queue_size */
		dev_warn(ctrl->ctrl.device,
			"queue_size %zu > ctrl sqsize %u, reducing "
			"to sqsize\n",
			opts->queue_size, ctrl->ctrl.sqsize + 1);
		opts->queue_size = ctrl->ctrl.sqsize + 1;
	पूर्ण

	ret = nvme_fc_init_aen_ops(ctrl);
	अगर (ret)
		जाओ out_term_aen_ops;

	/*
	 * Create the io queues
	 */

	अगर (ctrl->ctrl.queue_count > 1) अणु
		अगर (!ctrl->ioq_live)
			ret = nvme_fc_create_io_queues(ctrl);
		अन्यथा
			ret = nvme_fc_recreate_io_queues(ctrl);
	पूर्ण
	अगर (ret || test_bit(ASSOC_FAILED, &ctrl->flags))
		जाओ out_term_aen_ops;

	changed = nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_LIVE);

	ctrl->ctrl.nr_reconnects = 0;

	अगर (changed)
		nvme_start_ctrl(&ctrl->ctrl);

	वापस 0;	/* Success */

out_term_aen_ops:
	nvme_fc_term_aen_ops(ctrl);
out_disconnect_admin_queue:
	/* send a Disconnect(association) LS to fc-nvme target */
	nvme_fc_xmt_disconnect_assoc(ctrl);
	spin_lock_irqsave(&ctrl->lock, flags);
	ctrl->association_id = 0;
	disls = ctrl->rcv_disconn;
	ctrl->rcv_disconn = शून्य;
	spin_unlock_irqrestore(&ctrl->lock, flags);
	अगर (disls)
		nvme_fc_xmt_ls_rsp(disls);
out_delete_hw_queue:
	__nvme_fc_delete_hw_queue(ctrl, &ctrl->queues[0], 0);
out_मुक्त_queue:
	nvme_fc_मुक्त_queue(&ctrl->queues[0]);
	clear_bit(ASSOC_ACTIVE, &ctrl->flags);
	nvme_fc_ctlr_inactive_on_rport(ctrl);

	वापस ret;
पूर्ण


/*
 * This routine stops operation of the controller on the host side.
 * On the host os stack side: Admin and IO queues are stopped,
 *   outstanding ios on them terminated via FC ABTS.
 * On the link side: the association is terminated.
 */
अटल व्योम
nvme_fc_delete_association(काष्ठा nvme_fc_ctrl *ctrl)
अणु
	काष्ठा nvmefc_ls_rcv_op *disls = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (!test_and_clear_bit(ASSOC_ACTIVE, &ctrl->flags))
		वापस;

	spin_lock_irqsave(&ctrl->lock, flags);
	set_bit(FCCTRL_TERMIO, &ctrl->flags);
	ctrl->iocnt = 0;
	spin_unlock_irqrestore(&ctrl->lock, flags);

	__nvme_fc_पात_outstanding_ios(ctrl, false);

	/* समाप्त the aens as they are a separate path */
	nvme_fc_पात_aen_ops(ctrl);

	/* रुको क्रम all io that had to be पातed */
	spin_lock_irq(&ctrl->lock);
	रुको_event_lock_irq(ctrl->ioपात_रुको, ctrl->iocnt == 0, ctrl->lock);
	clear_bit(FCCTRL_TERMIO, &ctrl->flags);
	spin_unlock_irq(&ctrl->lock);

	nvme_fc_term_aen_ops(ctrl);

	/*
	 * send a Disconnect(association) LS to fc-nvme target
	 * Note: could have been sent at top of process, but
	 * cleaner on link traffic अगर after the पातs complete.
	 * Note: अगर association करोesn't exist, association_id will be 0
	 */
	अगर (ctrl->association_id)
		nvme_fc_xmt_disconnect_assoc(ctrl);

	spin_lock_irqsave(&ctrl->lock, flags);
	ctrl->association_id = 0;
	disls = ctrl->rcv_disconn;
	ctrl->rcv_disconn = शून्य;
	spin_unlock_irqrestore(&ctrl->lock, flags);
	अगर (disls)
		/*
		 * अगर a Disconnect Request was रुकोing क्रम a response, send
		 * now that all ABTS's have been issued (and are complete).
		 */
		nvme_fc_xmt_ls_rsp(disls);

	अगर (ctrl->ctrl.tagset) अणु
		nvme_fc_delete_hw_io_queues(ctrl);
		nvme_fc_मुक्त_io_queues(ctrl);
	पूर्ण

	__nvme_fc_delete_hw_queue(ctrl, &ctrl->queues[0], 0);
	nvme_fc_मुक्त_queue(&ctrl->queues[0]);

	/* re-enable the admin_q so anything new can fast fail */
	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	/* resume the io queues so that things will fast fail */
	nvme_start_queues(&ctrl->ctrl);

	nvme_fc_ctlr_inactive_on_rport(ctrl);
पूर्ण

अटल व्योम
nvme_fc_delete_ctrl(काष्ठा nvme_ctrl *nctrl)
अणु
	काष्ठा nvme_fc_ctrl *ctrl = to_fc_ctrl(nctrl);

	cancel_work_sync(&ctrl->ioerr_work);
	cancel_delayed_work_sync(&ctrl->connect_work);
	/*
	 * समाप्त the association on the link side.  this will block
	 * रुकोing क्रम io to terminate
	 */
	nvme_fc_delete_association(ctrl);
पूर्ण

अटल व्योम
nvme_fc_reconnect_or_delete(काष्ठा nvme_fc_ctrl *ctrl, पूर्णांक status)
अणु
	काष्ठा nvme_fc_rport *rport = ctrl->rport;
	काष्ठा nvme_fc_remote_port *portptr = &rport->remoteport;
	अचिन्हित दीर्घ recon_delay = ctrl->ctrl.opts->reconnect_delay * HZ;
	bool recon = true;

	अगर (ctrl->ctrl.state != NVME_CTRL_CONNECTING)
		वापस;

	अगर (portptr->port_state == FC_OBJSTATE_ONLINE) अणु
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: reset: Reconnect attempt failed (%d)\n",
			ctrl->cnum, status);
		अगर (status > 0 && (status & NVME_SC_DNR))
			recon = false;
	पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, rport->dev_loss_end))
		recon = false;

	अगर (recon && nvmf_should_reconnect(&ctrl->ctrl)) अणु
		अगर (portptr->port_state == FC_OBJSTATE_ONLINE)
			dev_info(ctrl->ctrl.device,
				"NVME-FC{%d}: Reconnect attempt in %ld "
				"seconds\n",
				ctrl->cnum, recon_delay / HZ);
		अन्यथा अगर (समय_after(jअगरfies + recon_delay, rport->dev_loss_end))
			recon_delay = rport->dev_loss_end - jअगरfies;

		queue_delayed_work(nvme_wq, &ctrl->connect_work, recon_delay);
	पूर्ण अन्यथा अणु
		अगर (portptr->port_state == FC_OBJSTATE_ONLINE) अणु
			अगर (status > 0 && (status & NVME_SC_DNR))
				dev_warn(ctrl->ctrl.device,
					 "NVME-FC{%d}: reconnect failure\n",
					 ctrl->cnum);
			अन्यथा
				dev_warn(ctrl->ctrl.device,
					 "NVME-FC{%d}: Max reconnect attempts "
					 "(%d) reached.\n",
					 ctrl->cnum, ctrl->ctrl.nr_reconnects);
		पूर्ण अन्यथा
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: dev_loss_tmo (%d) expired "
				"while waiting for remoteport connectivity.\n",
				ctrl->cnum, min_t(पूर्णांक, portptr->dev_loss_पंचांगo,
					(ctrl->ctrl.opts->max_reconnects *
					 ctrl->ctrl.opts->reconnect_delay)));
		WARN_ON(nvme_delete_ctrl(&ctrl->ctrl));
	पूर्ण
पूर्ण

अटल व्योम
nvme_fc_reset_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_fc_ctrl *ctrl =
		container_of(work, काष्ठा nvme_fc_ctrl, ctrl.reset_work);

	nvme_stop_ctrl(&ctrl->ctrl);

	/* will block will रुकोing क्रम io to terminate */
	nvme_fc_delete_association(ctrl);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING))
		dev_err(ctrl->ctrl.device,
			"NVME-FC{%d}: error_recovery: Couldn't change state "
			"to CONNECTING\n", ctrl->cnum);

	अगर (ctrl->rport->remoteport.port_state == FC_OBJSTATE_ONLINE) अणु
		अगर (!queue_delayed_work(nvme_wq, &ctrl->connect_work, 0)) अणु
			dev_err(ctrl->ctrl.device,
				"NVME-FC{%d}: failed to schedule connect "
				"after reset\n", ctrl->cnum);
		पूर्ण अन्यथा अणु
			flush_delayed_work(&ctrl->connect_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		nvme_fc_reconnect_or_delete(ctrl, -ENOTCONN);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा nvme_ctrl_ops nvme_fc_ctrl_ops = अणु
	.name			= "fc",
	.module			= THIS_MODULE,
	.flags			= NVME_F_FABRICS,
	.reg_पढ़ो32		= nvmf_reg_पढ़ो32,
	.reg_पढ़ो64		= nvmf_reg_पढ़ो64,
	.reg_ग_लिखो32		= nvmf_reg_ग_लिखो32,
	.मुक्त_ctrl		= nvme_fc_nvme_ctrl_मुक्तd,
	.submit_async_event	= nvme_fc_submit_async_event,
	.delete_ctrl		= nvme_fc_delete_ctrl,
	.get_address		= nvmf_get_address,
पूर्ण;

अटल व्योम
nvme_fc_connect_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;

	काष्ठा nvme_fc_ctrl *ctrl =
			container_of(to_delayed_work(work),
				काष्ठा nvme_fc_ctrl, connect_work);

	ret = nvme_fc_create_association(ctrl);
	अगर (ret)
		nvme_fc_reconnect_or_delete(ctrl, ret);
	अन्यथा
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: controller connect complete\n",
			ctrl->cnum);
पूर्ण


अटल स्थिर काष्ठा blk_mq_ops nvme_fc_admin_mq_ops = अणु
	.queue_rq	= nvme_fc_queue_rq,
	.complete	= nvme_fc_complete_rq,
	.init_request	= nvme_fc_init_request,
	.निकास_request	= nvme_fc_निकास_request,
	.init_hctx	= nvme_fc_init_admin_hctx,
	.समयout	= nvme_fc_समयout,
पूर्ण;


/*
 * Fails a controller request अगर it matches an existing controller
 * (association) with the same tuple:
 * <Host NQN, Host ID, local FC port, remote FC port, SUBSYS NQN>
 *
 * The ports करोn't need to be compared as they are पूर्णांकrinsically
 * alपढ़ोy matched by the port poपूर्णांकers supplied.
 */
अटल bool
nvme_fc_existing_controller(काष्ठा nvme_fc_rport *rport,
		काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_fc_ctrl *ctrl;
	अचिन्हित दीर्घ flags;
	bool found = false;

	spin_lock_irqsave(&rport->lock, flags);
	list_क्रम_each_entry(ctrl, &rport->ctrl_list, ctrl_list) अणु
		found = nvmf_ctlr_matches_baseopts(&ctrl->ctrl, opts);
		अगर (found)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&rport->lock, flags);

	वापस found;
पूर्ण

अटल काष्ठा nvme_ctrl *
nvme_fc_init_ctrl(काष्ठा device *dev, काष्ठा nvmf_ctrl_options *opts,
	काष्ठा nvme_fc_lport *lport, काष्ठा nvme_fc_rport *rport)
अणु
	काष्ठा nvme_fc_ctrl *ctrl;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx, ctrl_loss_पंचांगo;

	अगर (!(rport->remoteport.port_role &
	    (FC_PORT_ROLE_NVME_DISCOVERY | FC_PORT_ROLE_NVME_TARGET))) अणु
		ret = -EBADR;
		जाओ out_fail;
	पूर्ण

	अगर (!opts->duplicate_connect &&
	    nvme_fc_existing_controller(rport, opts)) अणु
		ret = -EALREADY;
		जाओ out_fail;
	पूर्ण

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl) अणु
		ret = -ENOMEM;
		जाओ out_fail;
	पूर्ण

	idx = ida_simple_get(&nvme_fc_ctrl_cnt, 0, 0, GFP_KERNEL);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out_मुक्त_ctrl;
	पूर्ण

	/*
	 * अगर ctrl_loss_पंचांगo is being enक्रमced and the शेष reconnect delay
	 * is being used, change to a लघुer reconnect delay क्रम FC.
	 */
	अगर (opts->max_reconnects != -1 &&
	    opts->reconnect_delay == NVMF_DEF_RECONNECT_DELAY &&
	    opts->reconnect_delay > NVME_FC_DEFAULT_RECONNECT_TMO) अणु
		ctrl_loss_पंचांगo = opts->max_reconnects * opts->reconnect_delay;
		opts->reconnect_delay = NVME_FC_DEFAULT_RECONNECT_TMO;
		opts->max_reconnects = DIV_ROUND_UP(ctrl_loss_पंचांगo,
						opts->reconnect_delay);
	पूर्ण

	ctrl->ctrl.opts = opts;
	ctrl->ctrl.nr_reconnects = 0;
	अगर (lport->dev)
		ctrl->ctrl.numa_node = dev_to_node(lport->dev);
	अन्यथा
		ctrl->ctrl.numa_node = NUMA_NO_NODE;
	INIT_LIST_HEAD(&ctrl->ctrl_list);
	ctrl->lport = lport;
	ctrl->rport = rport;
	ctrl->dev = lport->dev;
	ctrl->cnum = idx;
	ctrl->ioq_live = false;
	init_रुकोqueue_head(&ctrl->ioपात_रुको);

	get_device(ctrl->dev);
	kref_init(&ctrl->ref);

	INIT_WORK(&ctrl->ctrl.reset_work, nvme_fc_reset_ctrl_work);
	INIT_DELAYED_WORK(&ctrl->connect_work, nvme_fc_connect_ctrl_work);
	INIT_WORK(&ctrl->ioerr_work, nvme_fc_ctrl_ioerr_work);
	spin_lock_init(&ctrl->lock);

	/* io queue count */
	ctrl->ctrl.queue_count = min_t(अचिन्हित पूर्णांक,
				opts->nr_io_queues,
				lport->ops->max_hw_queues);
	ctrl->ctrl.queue_count++;	/* +1 क्रम admin queue */

	ctrl->ctrl.sqsize = opts->queue_size - 1;
	ctrl->ctrl.kato = opts->kato;
	ctrl->ctrl.cntlid = 0xffff;

	ret = -ENOMEM;
	ctrl->queues = kसुस्मृति(ctrl->ctrl.queue_count,
				माप(काष्ठा nvme_fc_queue), GFP_KERNEL);
	अगर (!ctrl->queues)
		जाओ out_मुक्त_ida;

	nvme_fc_init_queue(ctrl, 0);

	स_रखो(&ctrl->admin_tag_set, 0, माप(ctrl->admin_tag_set));
	ctrl->admin_tag_set.ops = &nvme_fc_admin_mq_ops;
	ctrl->admin_tag_set.queue_depth = NVME_AQ_MQ_TAG_DEPTH;
	ctrl->admin_tag_set.reserved_tags = NVMF_RESERVED_TAGS;
	ctrl->admin_tag_set.numa_node = ctrl->ctrl.numa_node;
	ctrl->admin_tag_set.cmd_size =
		काष्ठा_size((काष्ठा nvme_fcp_op_w_sgl *)शून्य, priv,
			    ctrl->lport->ops->fcprqst_priv_sz);
	ctrl->admin_tag_set.driver_data = ctrl;
	ctrl->admin_tag_set.nr_hw_queues = 1;
	ctrl->admin_tag_set.समयout = NVME_ADMIN_TIMEOUT;
	ctrl->admin_tag_set.flags = BLK_MQ_F_NO_SCHED;

	ret = blk_mq_alloc_tag_set(&ctrl->admin_tag_set);
	अगर (ret)
		जाओ out_मुक्त_queues;
	ctrl->ctrl.admin_tagset = &ctrl->admin_tag_set;

	ctrl->ctrl.fabrics_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	अगर (IS_ERR(ctrl->ctrl.fabrics_q)) अणु
		ret = PTR_ERR(ctrl->ctrl.fabrics_q);
		जाओ out_मुक्त_admin_tag_set;
	पूर्ण

	ctrl->ctrl.admin_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	अगर (IS_ERR(ctrl->ctrl.admin_q)) अणु
		ret = PTR_ERR(ctrl->ctrl.admin_q);
		जाओ out_cleanup_fabrics_q;
	पूर्ण

	/*
	 * Would have been nice to init io queues tag set as well.
	 * However, we require पूर्णांकeraction from the controller
	 * क्रम max io queue count beक्रमe we can करो so.
	 * Defer this to the connect path.
	 */

	ret = nvme_init_ctrl(&ctrl->ctrl, dev, &nvme_fc_ctrl_ops, 0);
	अगर (ret)
		जाओ out_cleanup_admin_q;

	/* at this poपूर्णांक, tearकरोwn path changes to ref counting on nvme ctrl */

	spin_lock_irqsave(&rport->lock, flags);
	list_add_tail(&ctrl->ctrl_list, &rport->ctrl_list);
	spin_unlock_irqrestore(&rport->lock, flags);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_RESETTING) ||
	    !nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING)) अणु
		dev_err(ctrl->ctrl.device,
			"NVME-FC{%d}: failed to init ctrl state\n", ctrl->cnum);
		जाओ fail_ctrl;
	पूर्ण

	अगर (!queue_delayed_work(nvme_wq, &ctrl->connect_work, 0)) अणु
		dev_err(ctrl->ctrl.device,
			"NVME-FC{%d}: failed to schedule initial connect\n",
			ctrl->cnum);
		जाओ fail_ctrl;
	पूर्ण

	flush_delayed_work(&ctrl->connect_work);

	dev_info(ctrl->ctrl.device,
		"NVME-FC{%d}: new ctrl: NQN \"%s\"\n",
		ctrl->cnum, ctrl->ctrl.opts->subsysnqn);

	वापस &ctrl->ctrl;

fail_ctrl:
	nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_DELETING);
	cancel_work_sync(&ctrl->ioerr_work);
	cancel_work_sync(&ctrl->ctrl.reset_work);
	cancel_delayed_work_sync(&ctrl->connect_work);

	ctrl->ctrl.opts = शून्य;

	/* initiate nvme ctrl ref counting tearकरोwn */
	nvme_uninit_ctrl(&ctrl->ctrl);

	/* Remove core ctrl ref. */
	nvme_put_ctrl(&ctrl->ctrl);

	/* as we're past the poपूर्णांक where we transition to the ref
	 * counting tearकरोwn path, अगर we वापस a bad poपूर्णांकer here,
	 * the calling routine, thinking it's prior to the
	 * transition, will करो an rport put. Since the tearकरोwn
	 * path also करोes a rport put, we करो an extra get here to
	 * so proper order/tearकरोwn happens.
	 */
	nvme_fc_rport_get(rport);

	वापस ERR_PTR(-EIO);

out_cleanup_admin_q:
	blk_cleanup_queue(ctrl->ctrl.admin_q);
out_cleanup_fabrics_q:
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
out_मुक्त_admin_tag_set:
	blk_mq_मुक्त_tag_set(&ctrl->admin_tag_set);
out_मुक्त_queues:
	kमुक्त(ctrl->queues);
out_मुक्त_ida:
	put_device(ctrl->dev);
	ida_simple_हटाओ(&nvme_fc_ctrl_cnt, ctrl->cnum);
out_मुक्त_ctrl:
	kमुक्त(ctrl);
out_fail:
	/* निकास via here करोesn't follow ctlr ref poपूर्णांकs */
	वापस ERR_PTR(ret);
पूर्ण


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

अटल काष्ठा nvme_ctrl *
nvme_fc_create_ctrl(काष्ठा device *dev, काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_fc_lport *lport;
	काष्ठा nvme_fc_rport *rport;
	काष्ठा nvme_ctrl *ctrl;
	काष्ठा nvmet_fc_traddr laddr = अणु 0L, 0L पूर्ण;
	काष्ठा nvmet_fc_traddr raddr = अणु 0L, 0L पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = nvme_fc_parse_traddr(&raddr, opts->traddr, NVMF_TRADDR_SIZE);
	अगर (ret || !raddr.nn || !raddr.pn)
		वापस ERR_PTR(-EINVAL);

	ret = nvme_fc_parse_traddr(&laddr, opts->host_traddr, NVMF_TRADDR_SIZE);
	अगर (ret || !laddr.nn || !laddr.pn)
		वापस ERR_PTR(-EINVAL);

	/* find the host and remote ports to connect together */
	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_क्रम_each_entry(lport, &nvme_fc_lport_list, port_list) अणु
		अगर (lport->localport.node_name != laddr.nn ||
		    lport->localport.port_name != laddr.pn ||
		    lport->localport.port_state != FC_OBJSTATE_ONLINE)
			जारी;

		list_क्रम_each_entry(rport, &lport->endp_list, endp_list) अणु
			अगर (rport->remoteport.node_name != raddr.nn ||
			    rport->remoteport.port_name != raddr.pn ||
			    rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
				जारी;

			/* अगर fail to get reference fall through. Will error */
			अगर (!nvme_fc_rport_get(rport))
				अवरोध;

			spin_unlock_irqrestore(&nvme_fc_lock, flags);

			ctrl = nvme_fc_init_ctrl(dev, opts, lport, rport);
			अगर (IS_ERR(ctrl))
				nvme_fc_rport_put(rport);
			वापस ctrl;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	pr_warn("%s: %s - %s combination not found\n",
		__func__, opts->traddr, opts->host_traddr);
	वापस ERR_PTR(-ENOENT);
पूर्ण


अटल काष्ठा nvmf_transport_ops nvme_fc_transport = अणु
	.name		= "fc",
	.module		= THIS_MODULE,
	.required_opts	= NVMF_OPT_TRADDR | NVMF_OPT_HOST_TRADDR,
	.allowed_opts	= NVMF_OPT_RECONNECT_DELAY | NVMF_OPT_CTRL_LOSS_TMO,
	.create_ctrl	= nvme_fc_create_ctrl,
पूर्ण;

/* Arbitrary successive failures max. With lots of subप्रणालीs could be high */
#घोषणा DISCOVERY_MAX_FAIL	20

अटल sमाप_प्रकार nvme_fc_nvme_discovery_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(local_disc_list);
	काष्ठा nvme_fc_lport *lport;
	काष्ठा nvme_fc_rport *rport;
	पूर्णांक failcnt = 0;

	spin_lock_irqsave(&nvme_fc_lock, flags);
restart:
	list_क्रम_each_entry(lport, &nvme_fc_lport_list, port_list) अणु
		list_क्रम_each_entry(rport, &lport->endp_list, endp_list) अणु
			अगर (!nvme_fc_lport_get(lport))
				जारी;
			अगर (!nvme_fc_rport_get(rport)) अणु
				/*
				 * This is a temporary condition. Upon restart
				 * this rport will be gone from the list.
				 *
				 * Revert the lport put and retry.  Anything
				 * added to the list alपढ़ोy will be skipped (as
				 * they are no दीर्घer list_empty).  Loops should
				 * resume at rports that were not yet seen.
				 */
				nvme_fc_lport_put(lport);

				अगर (failcnt++ < DISCOVERY_MAX_FAIL)
					जाओ restart;

				pr_err("nvme_discovery: too many reference "
				       "failures\n");
				जाओ process_local_list;
			पूर्ण
			अगर (list_empty(&rport->disc_list))
				list_add_tail(&rport->disc_list,
					      &local_disc_list);
		पूर्ण
	पूर्ण

process_local_list:
	जबतक (!list_empty(&local_disc_list)) अणु
		rport = list_first_entry(&local_disc_list,
					 काष्ठा nvme_fc_rport, disc_list);
		list_del_init(&rport->disc_list);
		spin_unlock_irqrestore(&nvme_fc_lock, flags);

		lport = rport->lport;
		/* संकेत discovery. Won't hurt अगर it repeats */
		nvme_fc_संकेत_discovery_scan(lport, rport);
		nvme_fc_rport_put(rport);
		nvme_fc_lport_put(lport);

		spin_lock_irqsave(&nvme_fc_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(nvme_discovery, 0200, शून्य, nvme_fc_nvme_discovery_store);

अटल काष्ठा attribute *nvme_fc_attrs[] = अणु
	&dev_attr_nvme_discovery.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nvme_fc_attr_group = अणु
	.attrs = nvme_fc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nvme_fc_attr_groups[] = अणु
	&nvme_fc_attr_group,
	शून्य
पूर्ण;

अटल काष्ठा class fc_class = अणु
	.name = "fc",
	.dev_groups = nvme_fc_attr_groups,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nvme_fc_init_module(व्योम)
अणु
	पूर्णांक ret;

	nvme_fc_wq = alloc_workqueue("nvme_fc_wq", WQ_MEM_RECLAIM, 0);
	अगर (!nvme_fc_wq)
		वापस -ENOMEM;

	/*
	 * NOTE:
	 * It is expected that in the future the kernel will combine
	 * the FC-isms that are currently under scsi and now being
	 * added to by NVME पूर्णांकo a new standalone FC class. The SCSI
	 * and NVME protocols and their devices would be under this
	 * new FC class.
	 *
	 * As we need something to post FC-specअगरic udev events to,
	 * specअगरically क्रम nvme probe events, start by creating the
	 * new device class.  When the new standalone FC class is
	 * put in place, this code will move to a more generic
	 * location क्रम the class.
	 */
	ret = class_रेजिस्टर(&fc_class);
	अगर (ret) अणु
		pr_err("couldn't register class fc\n");
		जाओ out_destroy_wq;
	पूर्ण

	/*
	 * Create a device क्रम the FC-centric udev events
	 */
	fc_udev_device = device_create(&fc_class, शून्य, MKDEV(0, 0), शून्य,
				"fc_udev_device");
	अगर (IS_ERR(fc_udev_device)) अणु
		pr_err("couldn't create fc_udev device!\n");
		ret = PTR_ERR(fc_udev_device);
		जाओ out_destroy_class;
	पूर्ण

	ret = nvmf_रेजिस्टर_transport(&nvme_fc_transport);
	अगर (ret)
		जाओ out_destroy_device;

	वापस 0;

out_destroy_device:
	device_destroy(&fc_class, MKDEV(0, 0));
out_destroy_class:
	class_unरेजिस्टर(&fc_class);
out_destroy_wq:
	destroy_workqueue(nvme_fc_wq);

	वापस ret;
पूर्ण

अटल व्योम
nvme_fc_delete_controllers(काष्ठा nvme_fc_rport *rport)
अणु
	काष्ठा nvme_fc_ctrl *ctrl;

	spin_lock(&rport->lock);
	list_क्रम_each_entry(ctrl, &rport->ctrl_list, ctrl_list) अणु
		dev_warn(ctrl->ctrl.device,
			"NVME-FC{%d}: transport unloading: deleting ctrl\n",
			ctrl->cnum);
		nvme_delete_ctrl(&ctrl->ctrl);
	पूर्ण
	spin_unlock(&rport->lock);
पूर्ण

अटल व्योम
nvme_fc_cleanup_क्रम_unload(व्योम)
अणु
	काष्ठा nvme_fc_lport *lport;
	काष्ठा nvme_fc_rport *rport;

	list_क्रम_each_entry(lport, &nvme_fc_lport_list, port_list) अणु
		list_क्रम_each_entry(rport, &lport->endp_list, endp_list) अणु
			nvme_fc_delete_controllers(rport);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __निकास nvme_fc_निकास_module(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	bool need_cleanup = false;

	spin_lock_irqsave(&nvme_fc_lock, flags);
	nvme_fc_रुकोing_to_unload = true;
	अगर (!list_empty(&nvme_fc_lport_list)) अणु
		need_cleanup = true;
		nvme_fc_cleanup_क्रम_unload();
	पूर्ण
	spin_unlock_irqrestore(&nvme_fc_lock, flags);
	अगर (need_cleanup) अणु
		pr_info("%s: waiting for ctlr deletes\n", __func__);
		रुको_क्रम_completion(&nvme_fc_unload_proceed);
		pr_info("%s: ctrl deletes complete\n", __func__);
	पूर्ण

	nvmf_unरेजिस्टर_transport(&nvme_fc_transport);

	ida_destroy(&nvme_fc_local_port_cnt);
	ida_destroy(&nvme_fc_ctrl_cnt);

	device_destroy(&fc_class, MKDEV(0, 0));
	class_unरेजिस्टर(&fc_class);
	destroy_workqueue(nvme_fc_wq);
पूर्ण

module_init(nvme_fc_init_module);
module_निकास(nvme_fc_निकास_module);

MODULE_LICENSE("GPL v2");
