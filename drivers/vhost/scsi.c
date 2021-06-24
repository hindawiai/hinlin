<शैली गुरु>
/*******************************************************************************
 * Vhost kernel TCM fabric driver क्रम virtio SCSI initiators
 *
 * (C) Copyright 2010-2013 Datera, Inc.
 * (C) Copyright 2010-2012 IBM Corp.
 *
 * Licensed to the Linux Foundation under the General Public License (GPL) version 2.
 *
 * Authors: Nicholas A. Bellinger <nab@daterainc.com>
 *          Stefan Hajnoczi <stefanha@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 ****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/compat.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/miscdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <linux/vhost.h>
#समावेश <linux/virtio_scsi.h>
#समावेश <linux/llist.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "vhost.h"

#घोषणा VHOST_SCSI_VERSION  "v0.1"
#घोषणा VHOST_SCSI_NAMELEN 256
#घोषणा VHOST_SCSI_MAX_CDB_SIZE 32
#घोषणा VHOST_SCSI_PREALLOC_SGLS 2048
#घोषणा VHOST_SCSI_PREALLOC_UPAGES 2048
#घोषणा VHOST_SCSI_PREALLOC_PROT_SGLS 2048

/* Max number of requests beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others with
 * request.
 */
#घोषणा VHOST_SCSI_WEIGHT 256

काष्ठा vhost_scsi_inflight अणु
	/* Wait क्रम the flush operation to finish */
	काष्ठा completion comp;
	/* Refcount क्रम the inflight reqs */
	काष्ठा kref kref;
पूर्ण;

काष्ठा vhost_scsi_cmd अणु
	/* Descriptor from vhost_get_vq_desc() क्रम virt_queue segment */
	पूर्णांक tvc_vq_desc;
	/* virtio-scsi initiator task attribute */
	पूर्णांक tvc_task_attr;
	/* virtio-scsi response incoming iovecs */
	पूर्णांक tvc_in_iovs;
	/* virtio-scsi initiator data direction */
	क्रमागत dma_data_direction tvc_data_direction;
	/* Expected data transfer length from virtio-scsi header */
	u32 tvc_exp_data_len;
	/* The Tag from include/linux/virtio_scsi.h:काष्ठा virtio_scsi_cmd_req */
	u64 tvc_tag;
	/* The number of scatterlists associated with this cmd */
	u32 tvc_sgl_count;
	u32 tvc_prot_sgl_count;
	/* Saved unpacked SCSI LUN क्रम vhost_scsi_target_queue_cmd() */
	u32 tvc_lun;
	/* Poपूर्णांकer to the SGL क्रमmatted memory from virtio-scsi */
	काष्ठा scatterlist *tvc_sgl;
	काष्ठा scatterlist *tvc_prot_sgl;
	काष्ठा page **tvc_upages;
	/* Poपूर्णांकer to response header iovec */
	काष्ठा iovec tvc_resp_iov;
	/* Poपूर्णांकer to vhost_scsi क्रम our device */
	काष्ठा vhost_scsi *tvc_vhost;
	/* Poपूर्णांकer to vhost_virtqueue क्रम the cmd */
	काष्ठा vhost_virtqueue *tvc_vq;
	/* Poपूर्णांकer to vhost nexus memory */
	काष्ठा vhost_scsi_nexus *tvc_nexus;
	/* The TCM I/O descriptor that is accessed via container_of() */
	काष्ठा se_cmd tvc_se_cmd;
	/* Copy of the incoming SCSI command descriptor block (CDB) */
	अचिन्हित अक्षर tvc_cdb[VHOST_SCSI_MAX_CDB_SIZE];
	/* Sense buffer that will be mapped पूर्णांकo outgoing status */
	अचिन्हित अक्षर tvc_sense_buf[TRANSPORT_SENSE_BUFFER];
	/* Completed commands list, serviced from vhost worker thपढ़ो */
	काष्ठा llist_node tvc_completion_list;
	/* Used to track inflight cmd */
	काष्ठा vhost_scsi_inflight *inflight;
पूर्ण;

काष्ठा vhost_scsi_nexus अणु
	/* Poपूर्णांकer to TCM session क्रम I_T Nexus */
	काष्ठा se_session *tvn_se_sess;
पूर्ण;

काष्ठा vhost_scsi_tpg अणु
	/* Vhost port target portal group tag क्रम TCM */
	u16 tport_tpgt;
	/* Used to track number of TPG Port/Lun Links wrt to explict I_T Nexus shutकरोwn */
	पूर्णांक tv_tpg_port_count;
	/* Used क्रम vhost_scsi device reference to tpg_nexus, रक्षित by tv_tpg_mutex */
	पूर्णांक tv_tpg_vhost_count;
	/* Used क्रम enabling T10-PI with legacy devices */
	पूर्णांक tv_fabric_prot_type;
	/* list क्रम vhost_scsi_list */
	काष्ठा list_head tv_tpg_list;
	/* Used to protect access क्रम tpg_nexus */
	काष्ठा mutex tv_tpg_mutex;
	/* Poपूर्णांकer to the TCM VHost I_T Nexus क्रम this TPG endpoपूर्णांक */
	काष्ठा vhost_scsi_nexus *tpg_nexus;
	/* Poपूर्णांकer back to vhost_scsi_tport */
	काष्ठा vhost_scsi_tport *tport;
	/* Returned by vhost_scsi_make_tpg() */
	काष्ठा se_portal_group se_tpg;
	/* Poपूर्णांकer back to vhost_scsi, रक्षित by tv_tpg_mutex */
	काष्ठा vhost_scsi *vhost_scsi;
	काष्ठा list_head पंचांगf_queue;
पूर्ण;

काष्ठा vhost_scsi_tport अणु
	/* SCSI protocol the tport is providing */
	u8 tport_proto_id;
	/* Binary World Wide unique Port Name क्रम Vhost Target port */
	u64 tport_wwpn;
	/* ASCII क्रमmatted WWPN क्रम Vhost Target port */
	अक्षर tport_name[VHOST_SCSI_NAMELEN];
	/* Returned by vhost_scsi_make_tport() */
	काष्ठा se_wwn tport_wwn;
पूर्ण;

काष्ठा vhost_scsi_evt अणु
	/* event to be sent to guest */
	काष्ठा virtio_scsi_event event;
	/* event list, serviced from vhost worker thपढ़ो */
	काष्ठा llist_node list;
पूर्ण;

क्रमागत अणु
	VHOST_SCSI_VQ_CTL = 0,
	VHOST_SCSI_VQ_EVT = 1,
	VHOST_SCSI_VQ_IO = 2,
पूर्ण;

/* Note: can't set VIRTIO_F_VERSION_1 yet, since that implies ANY_LAYOUT. */
क्रमागत अणु
	VHOST_SCSI_FEATURES = VHOST_FEATURES | (1ULL << VIRTIO_SCSI_F_HOTPLUG) |
					       (1ULL << VIRTIO_SCSI_F_T10_PI)
पूर्ण;

#घोषणा VHOST_SCSI_MAX_TARGET	256
#घोषणा VHOST_SCSI_MAX_VQ	128
#घोषणा VHOST_SCSI_MAX_EVENT	128

काष्ठा vhost_scsi_virtqueue अणु
	काष्ठा vhost_virtqueue vq;
	/*
	 * Reference counting क्रम inflight reqs, used क्रम flush operation. At
	 * each समय, one reference tracks new commands submitted, जबतक we
	 * रुको क्रम another one to reach 0.
	 */
	काष्ठा vhost_scsi_inflight inflights[2];
	/*
	 * Indicate current inflight in use, रक्षित by vq->mutex.
	 * Writers must also take dev mutex and flush under it.
	 */
	पूर्णांक inflight_idx;
	काष्ठा vhost_scsi_cmd *scsi_cmds;
	काष्ठा sbiपंचांगap scsi_tags;
	पूर्णांक max_cmds;
पूर्ण;

काष्ठा vhost_scsi अणु
	/* Protected by vhost_scsi->dev.mutex */
	काष्ठा vhost_scsi_tpg **vs_tpg;
	अक्षर vs_vhost_wwpn[TRANSPORT_IQN_LEN];

	काष्ठा vhost_dev dev;
	काष्ठा vhost_scsi_virtqueue vqs[VHOST_SCSI_MAX_VQ];

	काष्ठा vhost_work vs_completion_work; /* cmd completion work item */
	काष्ठा llist_head vs_completion_list; /* cmd completion queue */

	काष्ठा vhost_work vs_event_work; /* evt injection work item */
	काष्ठा llist_head vs_event_list; /* evt injection queue */

	bool vs_events_missed; /* any missed events, रक्षित by vq->mutex */
	पूर्णांक vs_events_nr; /* num of pending events, रक्षित by vq->mutex */
पूर्ण;

काष्ठा vhost_scsi_पंचांगf अणु
	काष्ठा vhost_work vwork;
	काष्ठा vhost_scsi_tpg *tpg;
	काष्ठा vhost_scsi *vhost;
	काष्ठा vhost_scsi_virtqueue *svq;
	काष्ठा list_head queue_entry;

	काष्ठा se_cmd se_cmd;
	u8 scsi_resp;
	काष्ठा vhost_scsi_inflight *inflight;
	काष्ठा iovec resp_iov;
	पूर्णांक in_iovs;
	पूर्णांक vq_desc;
पूर्ण;

/*
 * Context क्रम processing request and control queue operations.
 */
काष्ठा vhost_scsi_ctx अणु
	पूर्णांक head;
	अचिन्हित पूर्णांक out, in;
	माप_प्रकार req_size, rsp_size;
	माप_प्रकार out_size, in_size;
	u8 *target, *lunp;
	व्योम *req;
	काष्ठा iov_iter out_iter;
पूर्ण;

/* Global spinlock to protect vhost_scsi TPG list क्रम vhost IOCTL access */
अटल DEFINE_MUTEX(vhost_scsi_mutex);
अटल LIST_HEAD(vhost_scsi_list);

अटल व्योम vhost_scsi_करोne_inflight(काष्ठा kref *kref)
अणु
	काष्ठा vhost_scsi_inflight *inflight;

	inflight = container_of(kref, काष्ठा vhost_scsi_inflight, kref);
	complete(&inflight->comp);
पूर्ण

अटल व्योम vhost_scsi_init_inflight(काष्ठा vhost_scsi *vs,
				    काष्ठा vhost_scsi_inflight *old_inflight[])
अणु
	काष्ठा vhost_scsi_inflight *new_inflight;
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक idx, i;

	क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++) अणु
		vq = &vs->vqs[i].vq;

		mutex_lock(&vq->mutex);

		/* store old infight */
		idx = vs->vqs[i].inflight_idx;
		अगर (old_inflight)
			old_inflight[i] = &vs->vqs[i].inflights[idx];

		/* setup new infight */
		vs->vqs[i].inflight_idx = idx ^ 1;
		new_inflight = &vs->vqs[i].inflights[idx ^ 1];
		kref_init(&new_inflight->kref);
		init_completion(&new_inflight->comp);

		mutex_unlock(&vq->mutex);
	पूर्ण
पूर्ण

अटल काष्ठा vhost_scsi_inflight *
vhost_scsi_get_inflight(काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_scsi_inflight *inflight;
	काष्ठा vhost_scsi_virtqueue *svq;

	svq = container_of(vq, काष्ठा vhost_scsi_virtqueue, vq);
	inflight = &svq->inflights[svq->inflight_idx];
	kref_get(&inflight->kref);

	वापस inflight;
पूर्ण

अटल व्योम vhost_scsi_put_inflight(काष्ठा vhost_scsi_inflight *inflight)
अणु
	kref_put(&inflight->kref, vhost_scsi_करोne_inflight);
पूर्ण

अटल पूर्णांक vhost_scsi_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक vhost_scsi_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल अक्षर *vhost_scsi_get_fabric_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	काष्ठा vhost_scsi_tport *tport = tpg->tport;

	वापस &tport->tport_name[0];
पूर्ण

अटल u16 vhost_scsi_get_tpgt(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	वापस tpg->tport_tpgt;
पूर्ण

अटल पूर्णांक vhost_scsi_check_prot_fabric_only(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);

	वापस tpg->tv_fabric_prot_type;
पूर्ण

अटल u32 vhost_scsi_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल व्योम vhost_scsi_release_cmd_res(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा vhost_scsi_cmd *tv_cmd = container_of(se_cmd,
				काष्ठा vhost_scsi_cmd, tvc_se_cmd);
	काष्ठा vhost_scsi_virtqueue *svq = container_of(tv_cmd->tvc_vq,
				काष्ठा vhost_scsi_virtqueue, vq);
	काष्ठा vhost_scsi_inflight *inflight = tv_cmd->inflight;
	पूर्णांक i;

	अगर (tv_cmd->tvc_sgl_count) अणु
		क्रम (i = 0; i < tv_cmd->tvc_sgl_count; i++)
			put_page(sg_page(&tv_cmd->tvc_sgl[i]));
	पूर्ण
	अगर (tv_cmd->tvc_prot_sgl_count) अणु
		क्रम (i = 0; i < tv_cmd->tvc_prot_sgl_count; i++)
			put_page(sg_page(&tv_cmd->tvc_prot_sgl[i]));
	पूर्ण

	sbiपंचांगap_clear_bit(&svq->scsi_tags, se_cmd->map_tag);
	vhost_scsi_put_inflight(inflight);
पूर्ण

अटल व्योम vhost_scsi_release_पंचांगf_res(काष्ठा vhost_scsi_पंचांगf *पंचांगf)
अणु
	काष्ठा vhost_scsi_tpg *tpg = पंचांगf->tpg;
	काष्ठा vhost_scsi_inflight *inflight = पंचांगf->inflight;

	mutex_lock(&tpg->tv_tpg_mutex);
	list_add_tail(&tpg->पंचांगf_queue, &पंचांगf->queue_entry);
	mutex_unlock(&tpg->tv_tpg_mutex);
	vhost_scsi_put_inflight(inflight);
पूर्ण

अटल व्योम vhost_scsi_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	अगर (se_cmd->se_cmd_flags & SCF_SCSI_TMR_CDB) अणु
		काष्ठा vhost_scsi_पंचांगf *पंचांगf = container_of(se_cmd,
					काष्ठा vhost_scsi_पंचांगf, se_cmd);

		vhost_work_queue(&पंचांगf->vhost->dev, &पंचांगf->vwork);
	पूर्ण अन्यथा अणु
		काष्ठा vhost_scsi_cmd *cmd = container_of(se_cmd,
					काष्ठा vhost_scsi_cmd, tvc_se_cmd);
		काष्ठा vhost_scsi *vs = cmd->tvc_vhost;

		llist_add(&cmd->tvc_completion_list, &vs->vs_completion_list);
		vhost_work_queue(&vs->dev, &vs->vs_completion_work);
	पूर्ण
पूर्ण

अटल u32 vhost_scsi_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	/* Go ahead and process the ग_लिखो immediately */
	target_execute_cmd(se_cmd);
	वापस 0;
पूर्ण

अटल व्योम vhost_scsi_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
	वापस;
पूर्ण

अटल पूर्णांक vhost_scsi_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	transport_generic_मुक्त_cmd(se_cmd, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	transport_generic_मुक्त_cmd(se_cmd, 0);
	वापस 0;
पूर्ण

अटल व्योम vhost_scsi_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा vhost_scsi_पंचांगf *पंचांगf = container_of(se_cmd, काष्ठा vhost_scsi_पंचांगf,
						  se_cmd);

	पंचांगf->scsi_resp = se_cmd->se_पंचांगr_req->response;
	transport_generic_मुक्त_cmd(&पंचांगf->se_cmd, 0);
पूर्ण

अटल व्योम vhost_scsi_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	वापस;
पूर्ण

अटल व्योम vhost_scsi_मुक्त_evt(काष्ठा vhost_scsi *vs, काष्ठा vhost_scsi_evt *evt)
अणु
	vs->vs_events_nr--;
	kमुक्त(evt);
पूर्ण

अटल काष्ठा vhost_scsi_evt *
vhost_scsi_allocate_evt(काष्ठा vhost_scsi *vs,
		       u32 event, u32 reason)
अणु
	काष्ठा vhost_virtqueue *vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;
	काष्ठा vhost_scsi_evt *evt;

	अगर (vs->vs_events_nr > VHOST_SCSI_MAX_EVENT) अणु
		vs->vs_events_missed = true;
		वापस शून्य;
	पूर्ण

	evt = kzalloc(माप(*evt), GFP_KERNEL);
	अगर (!evt) अणु
		vq_err(vq, "Failed to allocate vhost_scsi_evt\n");
		vs->vs_events_missed = true;
		वापस शून्य;
	पूर्ण

	evt->event.event = cpu_to_vhost32(vq, event);
	evt->event.reason = cpu_to_vhost32(vq, reason);
	vs->vs_events_nr++;

	वापस evt;
पूर्ण

अटल पूर्णांक vhost_scsi_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस target_put_sess_cmd(se_cmd);
पूर्ण

अटल व्योम
vhost_scsi_करो_evt_work(काष्ठा vhost_scsi *vs, काष्ठा vhost_scsi_evt *evt)
अणु
	काष्ठा vhost_virtqueue *vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;
	काष्ठा virtio_scsi_event *event = &evt->event;
	काष्ठा virtio_scsi_event __user *eventp;
	अचिन्हित out, in;
	पूर्णांक head, ret;

	अगर (!vhost_vq_get_backend(vq)) अणु
		vs->vs_events_missed = true;
		वापस;
	पूर्ण

again:
	vhost_disable_notअगरy(&vs->dev, vq);
	head = vhost_get_vq_desc(vq, vq->iov,
			ARRAY_SIZE(vq->iov), &out, &in,
			शून्य, शून्य);
	अगर (head < 0) अणु
		vs->vs_events_missed = true;
		वापस;
	पूर्ण
	अगर (head == vq->num) अणु
		अगर (vhost_enable_notअगरy(&vs->dev, vq))
			जाओ again;
		vs->vs_events_missed = true;
		वापस;
	पूर्ण

	अगर ((vq->iov[out].iov_len != माप(काष्ठा virtio_scsi_event))) अणु
		vq_err(vq, "Expecting virtio_scsi_event, got %zu bytes\n",
				vq->iov[out].iov_len);
		vs->vs_events_missed = true;
		वापस;
	पूर्ण

	अगर (vs->vs_events_missed) अणु
		event->event |= cpu_to_vhost32(vq, VIRTIO_SCSI_T_EVENTS_MISSED);
		vs->vs_events_missed = false;
	पूर्ण

	eventp = vq->iov[out].iov_base;
	ret = __copy_to_user(eventp, event, माप(*event));
	अगर (!ret)
		vhost_add_used_and_संकेत(&vs->dev, vq, head, 0);
	अन्यथा
		vq_err(vq, "Faulted on vhost_scsi_send_event\n");
पूर्ण

अटल व्योम vhost_scsi_evt_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_scsi *vs = container_of(work, काष्ठा vhost_scsi,
					vs_event_work);
	काष्ठा vhost_virtqueue *vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;
	काष्ठा vhost_scsi_evt *evt, *t;
	काष्ठा llist_node *llnode;

	mutex_lock(&vq->mutex);
	llnode = llist_del_all(&vs->vs_event_list);
	llist_क्रम_each_entry_safe(evt, t, llnode, list) अणु
		vhost_scsi_करो_evt_work(vs, evt);
		vhost_scsi_मुक्त_evt(vs, evt);
	पूर्ण
	mutex_unlock(&vq->mutex);
पूर्ण

/* Fill in status and संकेत that we are करोne processing this command
 *
 * This is scheduled in the vhost work queue so we are called with the owner
 * process mm and can access the vring.
 */
अटल व्योम vhost_scsi_complete_cmd_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_scsi *vs = container_of(work, काष्ठा vhost_scsi,
					vs_completion_work);
	DECLARE_BITMAP(संकेत, VHOST_SCSI_MAX_VQ);
	काष्ठा virtio_scsi_cmd_resp v_rsp;
	काष्ठा vhost_scsi_cmd *cmd, *t;
	काष्ठा llist_node *llnode;
	काष्ठा se_cmd *se_cmd;
	काष्ठा iov_iter iov_iter;
	पूर्णांक ret, vq;

	biपंचांगap_zero(संकेत, VHOST_SCSI_MAX_VQ);
	llnode = llist_del_all(&vs->vs_completion_list);
	llist_क्रम_each_entry_safe(cmd, t, llnode, tvc_completion_list) अणु
		se_cmd = &cmd->tvc_se_cmd;

		pr_debug("%s tv_cmd %p resid %u status %#02x\n", __func__,
			cmd, se_cmd->residual_count, se_cmd->scsi_status);

		स_रखो(&v_rsp, 0, माप(v_rsp));
		v_rsp.resid = cpu_to_vhost32(cmd->tvc_vq, se_cmd->residual_count);
		/* TODO is status_qualअगरier field needed? */
		v_rsp.status = se_cmd->scsi_status;
		v_rsp.sense_len = cpu_to_vhost32(cmd->tvc_vq,
						 se_cmd->scsi_sense_length);
		स_नकल(v_rsp.sense, cmd->tvc_sense_buf,
		       se_cmd->scsi_sense_length);

		iov_iter_init(&iov_iter, READ, &cmd->tvc_resp_iov,
			      cmd->tvc_in_iovs, माप(v_rsp));
		ret = copy_to_iter(&v_rsp, माप(v_rsp), &iov_iter);
		अगर (likely(ret == माप(v_rsp))) अणु
			काष्ठा vhost_scsi_virtqueue *q;
			vhost_add_used(cmd->tvc_vq, cmd->tvc_vq_desc, 0);
			q = container_of(cmd->tvc_vq, काष्ठा vhost_scsi_virtqueue, vq);
			vq = q - vs->vqs;
			__set_bit(vq, संकेत);
		पूर्ण अन्यथा
			pr_err("Faulted on virtio_scsi_cmd_resp\n");

		vhost_scsi_release_cmd_res(se_cmd);
	पूर्ण

	vq = -1;
	जबतक ((vq = find_next_bit(संकेत, VHOST_SCSI_MAX_VQ, vq + 1))
		< VHOST_SCSI_MAX_VQ)
		vhost_संकेत(&vs->dev, &vs->vqs[vq].vq);
पूर्ण

अटल काष्ठा vhost_scsi_cmd *
vhost_scsi_get_cmd(काष्ठा vhost_virtqueue *vq, काष्ठा vhost_scsi_tpg *tpg,
		   अचिन्हित अक्षर *cdb, u64 scsi_tag, u16 lun, u8 task_attr,
		   u32 exp_data_len, पूर्णांक data_direction)
अणु
	काष्ठा vhost_scsi_virtqueue *svq = container_of(vq,
					काष्ठा vhost_scsi_virtqueue, vq);
	काष्ठा vhost_scsi_cmd *cmd;
	काष्ठा vhost_scsi_nexus *tv_nexus;
	काष्ठा scatterlist *sg, *prot_sg;
	काष्ठा page **pages;
	पूर्णांक tag;

	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		pr_err("Unable to locate active struct vhost_scsi_nexus\n");
		वापस ERR_PTR(-EIO);
	पूर्ण

	tag = sbiपंचांगap_get(&svq->scsi_tags);
	अगर (tag < 0) अणु
		pr_err("Unable to obtain tag for vhost_scsi_cmd\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cmd = &svq->scsi_cmds[tag];
	sg = cmd->tvc_sgl;
	prot_sg = cmd->tvc_prot_sgl;
	pages = cmd->tvc_upages;
	स_रखो(cmd, 0, माप(*cmd));
	cmd->tvc_sgl = sg;
	cmd->tvc_prot_sgl = prot_sg;
	cmd->tvc_upages = pages;
	cmd->tvc_se_cmd.map_tag = tag;
	cmd->tvc_tag = scsi_tag;
	cmd->tvc_lun = lun;
	cmd->tvc_task_attr = task_attr;
	cmd->tvc_exp_data_len = exp_data_len;
	cmd->tvc_data_direction = data_direction;
	cmd->tvc_nexus = tv_nexus;
	cmd->inflight = vhost_scsi_get_inflight(vq);

	स_नकल(cmd->tvc_cdb, cdb, VHOST_SCSI_MAX_CDB_SIZE);

	वापस cmd;
पूर्ण

/*
 * Map a user memory range पूर्णांकo a scatterlist
 *
 * Returns the number of scatterlist entries used or -त्रुटि_सं on error.
 */
अटल पूर्णांक
vhost_scsi_map_to_sgl(काष्ठा vhost_scsi_cmd *cmd,
		      काष्ठा iov_iter *iter,
		      काष्ठा scatterlist *sgl,
		      bool ग_लिखो)
अणु
	काष्ठा page **pages = cmd->tvc_upages;
	काष्ठा scatterlist *sg = sgl;
	sमाप_प्रकार bytes;
	माप_प्रकार offset;
	अचिन्हित पूर्णांक npages = 0;

	bytes = iov_iter_get_pages(iter, pages, दीर्घ_उच्च,
				VHOST_SCSI_PREALLOC_UPAGES, &offset);
	/* No pages were pinned */
	अगर (bytes <= 0)
		वापस bytes < 0 ? bytes : -EFAULT;

	iov_iter_advance(iter, bytes);

	जबतक (bytes) अणु
		अचिन्हित n = min_t(अचिन्हित, PAGE_SIZE - offset, bytes);
		sg_set_page(sg++, pages[npages++], n, offset);
		bytes -= n;
		offset = 0;
	पूर्ण
	वापस npages;
पूर्ण

अटल पूर्णांक
vhost_scsi_calc_sgls(काष्ठा iov_iter *iter, माप_प्रकार bytes, पूर्णांक max_sgls)
अणु
	पूर्णांक sgl_count = 0;

	अगर (!iter || !iter->iov) अणु
		pr_err("%s: iter->iov is NULL, but expected bytes: %zu"
		       " present\n", __func__, bytes);
		वापस -EINVAL;
	पूर्ण

	sgl_count = iov_iter_npages(iter, 0xffff);
	अगर (sgl_count > max_sgls) अणु
		pr_err("%s: requested sgl_count: %d exceeds pre-allocated"
		       " max_sgls: %d\n", __func__, sgl_count, max_sgls);
		वापस -EINVAL;
	पूर्ण
	वापस sgl_count;
पूर्ण

अटल पूर्णांक
vhost_scsi_iov_to_sgl(काष्ठा vhost_scsi_cmd *cmd, bool ग_लिखो,
		      काष्ठा iov_iter *iter,
		      काष्ठा scatterlist *sg, पूर्णांक sg_count)
अणु
	काष्ठा scatterlist *p = sg;
	पूर्णांक ret;

	जबतक (iov_iter_count(iter)) अणु
		ret = vhost_scsi_map_to_sgl(cmd, iter, sg, ग_लिखो);
		अगर (ret < 0) अणु
			जबतक (p < sg) अणु
				काष्ठा page *page = sg_page(p++);
				अगर (page)
					put_page(page);
			पूर्ण
			वापस ret;
		पूर्ण
		sg += ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
vhost_scsi_mapal(काष्ठा vhost_scsi_cmd *cmd,
		 माप_प्रकार prot_bytes, काष्ठा iov_iter *prot_iter,
		 माप_प्रकार data_bytes, काष्ठा iov_iter *data_iter)
अणु
	पूर्णांक sgl_count, ret;
	bool ग_लिखो = (cmd->tvc_data_direction == DMA_FROM_DEVICE);

	अगर (prot_bytes) अणु
		sgl_count = vhost_scsi_calc_sgls(prot_iter, prot_bytes,
						 VHOST_SCSI_PREALLOC_PROT_SGLS);
		अगर (sgl_count < 0)
			वापस sgl_count;

		sg_init_table(cmd->tvc_prot_sgl, sgl_count);
		cmd->tvc_prot_sgl_count = sgl_count;
		pr_debug("%s prot_sg %p prot_sgl_count %u\n", __func__,
			 cmd->tvc_prot_sgl, cmd->tvc_prot_sgl_count);

		ret = vhost_scsi_iov_to_sgl(cmd, ग_लिखो, prot_iter,
					    cmd->tvc_prot_sgl,
					    cmd->tvc_prot_sgl_count);
		अगर (ret < 0) अणु
			cmd->tvc_prot_sgl_count = 0;
			वापस ret;
		पूर्ण
	पूर्ण
	sgl_count = vhost_scsi_calc_sgls(data_iter, data_bytes,
					 VHOST_SCSI_PREALLOC_SGLS);
	अगर (sgl_count < 0)
		वापस sgl_count;

	sg_init_table(cmd->tvc_sgl, sgl_count);
	cmd->tvc_sgl_count = sgl_count;
	pr_debug("%s data_sg %p data_sgl_count %u\n", __func__,
		  cmd->tvc_sgl, cmd->tvc_sgl_count);

	ret = vhost_scsi_iov_to_sgl(cmd, ग_लिखो, data_iter,
				    cmd->tvc_sgl, cmd->tvc_sgl_count);
	अगर (ret < 0) अणु
		cmd->tvc_sgl_count = 0;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_to_tcm_attr(पूर्णांक attr)
अणु
	चयन (attr) अणु
	हाल VIRTIO_SCSI_S_SIMPLE:
		वापस TCM_SIMPLE_TAG;
	हाल VIRTIO_SCSI_S_ORDERED:
		वापस TCM_ORDERED_TAG;
	हाल VIRTIO_SCSI_S_HEAD:
		वापस TCM_HEAD_TAG;
	हाल VIRTIO_SCSI_S_ACA:
		वापस TCM_ACA_TAG;
	शेष:
		अवरोध;
	पूर्ण
	वापस TCM_SIMPLE_TAG;
पूर्ण

अटल व्योम vhost_scsi_target_queue_cmd(काष्ठा vhost_scsi_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->tvc_se_cmd;
	काष्ठा vhost_scsi_nexus *tv_nexus;
	काष्ठा scatterlist *sg_ptr, *sg_prot_ptr = शून्य;

	/* FIXME: BIDI operation */
	अगर (cmd->tvc_sgl_count) अणु
		sg_ptr = cmd->tvc_sgl;

		अगर (cmd->tvc_prot_sgl_count)
			sg_prot_ptr = cmd->tvc_prot_sgl;
		अन्यथा
			se_cmd->prot_pto = true;
	पूर्ण अन्यथा अणु
		sg_ptr = शून्य;
	पूर्ण
	tv_nexus = cmd->tvc_nexus;

	se_cmd->tag = 0;
	target_init_cmd(se_cmd, tv_nexus->tvn_se_sess, &cmd->tvc_sense_buf[0],
			cmd->tvc_lun, cmd->tvc_exp_data_len,
			vhost_scsi_to_tcm_attr(cmd->tvc_task_attr),
			cmd->tvc_data_direction, TARGET_SCF_ACK_KREF);

	अगर (target_submit_prep(se_cmd, cmd->tvc_cdb, sg_ptr,
			       cmd->tvc_sgl_count, शून्य, 0, sg_prot_ptr,
			       cmd->tvc_prot_sgl_count, GFP_KERNEL))
		वापस;

	target_queue_submission(se_cmd);
पूर्ण

अटल व्योम
vhost_scsi_send_bad_target(काष्ठा vhost_scsi *vs,
			   काष्ठा vhost_virtqueue *vq,
			   पूर्णांक head, अचिन्हित out)
अणु
	काष्ठा virtio_scsi_cmd_resp __user *resp;
	काष्ठा virtio_scsi_cmd_resp rsp;
	पूर्णांक ret;

	स_रखो(&rsp, 0, माप(rsp));
	rsp.response = VIRTIO_SCSI_S_BAD_TARGET;
	resp = vq->iov[out].iov_base;
	ret = __copy_to_user(resp, &rsp, माप(rsp));
	अगर (!ret)
		vhost_add_used_and_संकेत(&vs->dev, vq, head, 0);
	अन्यथा
		pr_err("Faulted on virtio_scsi_cmd_resp\n");
पूर्ण

अटल पूर्णांक
vhost_scsi_get_desc(काष्ठा vhost_scsi *vs, काष्ठा vhost_virtqueue *vq,
		    काष्ठा vhost_scsi_ctx *vc)
अणु
	पूर्णांक ret = -ENXIO;

	vc->head = vhost_get_vq_desc(vq, vq->iov,
				     ARRAY_SIZE(vq->iov), &vc->out, &vc->in,
				     शून्य, शून्य);

	pr_debug("vhost_get_vq_desc: head: %d, out: %u in: %u\n",
		 vc->head, vc->out, vc->in);

	/* On error, stop handling until the next kick. */
	अगर (unlikely(vc->head < 0))
		जाओ करोne;

	/* Nothing new?  Wait क्रम eventfd to tell us they refilled. */
	अगर (vc->head == vq->num) अणु
		अगर (unlikely(vhost_enable_notअगरy(&vs->dev, vq))) अणु
			vhost_disable_notअगरy(&vs->dev, vq);
			ret = -EAGAIN;
		पूर्ण
		जाओ करोne;
	पूर्ण

	/*
	 * Get the size of request and response buffers.
	 * FIXME: Not correct क्रम BIDI operation
	 */
	vc->out_size = iov_length(vq->iov, vc->out);
	vc->in_size = iov_length(&vq->iov[vc->out], vc->in);

	/*
	 * Copy over the virtio-scsi request header, which क्रम a
	 * ANY_LAYOUT enabled guest may span multiple iovecs, or a
	 * single iovec may contain both the header + outgoing
	 * WRITE payloads.
	 *
	 * copy_from_iter() will advance out_iter, so that it will
	 * poपूर्णांक at the start of the outgoing WRITE payload, अगर
	 * DMA_TO_DEVICE is set.
	 */
	iov_iter_init(&vc->out_iter, WRITE, vq->iov, vc->out, vc->out_size);
	ret = 0;

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक
vhost_scsi_chk_size(काष्ठा vhost_virtqueue *vq, काष्ठा vhost_scsi_ctx *vc)
अणु
	अगर (unlikely(vc->in_size < vc->rsp_size)) अणु
		vq_err(vq,
		       "Response buf too small, need min %zu bytes got %zu",
		       vc->rsp_size, vc->in_size);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (unlikely(vc->out_size < vc->req_size)) अणु
		vq_err(vq,
		       "Request buf too small, need min %zu bytes got %zu",
		       vc->req_size, vc->out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vhost_scsi_get_req(काष्ठा vhost_virtqueue *vq, काष्ठा vhost_scsi_ctx *vc,
		   काष्ठा vhost_scsi_tpg **tpgp)
अणु
	पूर्णांक ret = -EIO;

	अगर (unlikely(!copy_from_iter_full(vc->req, vc->req_size,
					  &vc->out_iter))) अणु
		vq_err(vq, "Faulted on copy_from_iter_full\n");
	पूर्ण अन्यथा अगर (unlikely(*vc->lunp != 1)) अणु
		/* virtio-scsi spec requires byte 0 of the lun to be 1 */
		vq_err(vq, "Illegal virtio-scsi lun: %u\n", *vc->lunp);
	पूर्ण अन्यथा अणु
		काष्ठा vhost_scsi_tpg **vs_tpg, *tpg;

		vs_tpg = vhost_vq_get_backend(vq);	/* validated at handler entry */

		tpg = READ_ONCE(vs_tpg[*vc->target]);
		अगर (unlikely(!tpg)) अणु
			vq_err(vq, "Target 0x%x does not exist\n", *vc->target);
		पूर्ण अन्यथा अणु
			अगर (tpgp)
				*tpgp = tpg;
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल u16 vhost_buf_to_lun(u8 *lun_buf)
अणु
	वापस ((lun_buf[2] << 8) | lun_buf[3]) & 0x3FFF;
पूर्ण

अटल व्योम
vhost_scsi_handle_vq(काष्ठा vhost_scsi *vs, काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_scsi_tpg **vs_tpg, *tpg;
	काष्ठा virtio_scsi_cmd_req v_req;
	काष्ठा virtio_scsi_cmd_req_pi v_req_pi;
	काष्ठा vhost_scsi_ctx vc;
	काष्ठा vhost_scsi_cmd *cmd;
	काष्ठा iov_iter in_iter, prot_iter, data_iter;
	u64 tag;
	u32 exp_data_len, data_direction;
	पूर्णांक ret, prot_bytes, c = 0;
	u16 lun;
	u8 task_attr;
	bool t10_pi = vhost_has_feature(vq, VIRTIO_SCSI_F_T10_PI);
	व्योम *cdb;

	mutex_lock(&vq->mutex);
	/*
	 * We can handle the vq only after the endpoपूर्णांक is setup by calling the
	 * VHOST_SCSI_SET_ENDPOINT ioctl.
	 */
	vs_tpg = vhost_vq_get_backend(vq);
	अगर (!vs_tpg)
		जाओ out;

	स_रखो(&vc, 0, माप(vc));
	vc.rsp_size = माप(काष्ठा virtio_scsi_cmd_resp);

	vhost_disable_notअगरy(&vs->dev, vq);

	करो अणु
		ret = vhost_scsi_get_desc(vs, vq, &vc);
		अगर (ret)
			जाओ err;

		/*
		 * Setup poपूर्णांकers and values based upon dअगरferent virtio-scsi
		 * request header अगर T10_PI is enabled in KVM guest.
		 */
		अगर (t10_pi) अणु
			vc.req = &v_req_pi;
			vc.req_size = माप(v_req_pi);
			vc.lunp = &v_req_pi.lun[0];
			vc.target = &v_req_pi.lun[1];
		पूर्ण अन्यथा अणु
			vc.req = &v_req;
			vc.req_size = माप(v_req);
			vc.lunp = &v_req.lun[0];
			vc.target = &v_req.lun[1];
		पूर्ण

		/*
		 * Validate the size of request and response buffers.
		 * Check क्रम a sane response buffer so we can report
		 * early errors back to the guest.
		 */
		ret = vhost_scsi_chk_size(vq, &vc);
		अगर (ret)
			जाओ err;

		ret = vhost_scsi_get_req(vq, &vc, &tpg);
		अगर (ret)
			जाओ err;

		ret = -EIO;	/* bad target on any error from here on */

		/*
		 * Determine data_direction by calculating the total outgoing
		 * iovec sizes + incoming iovec sizes vs. virtio-scsi request +
		 * response headers respectively.
		 *
		 * For DMA_TO_DEVICE this is out_iter, which is alपढ़ोy poपूर्णांकing
		 * to the right place.
		 *
		 * For DMA_FROM_DEVICE, the iovec will be just past the end
		 * of the virtio-scsi response header in either the same
		 * or immediately following iovec.
		 *
		 * Any associated T10_PI bytes क्रम the outgoing / incoming
		 * payloads are included in calculation of exp_data_len here.
		 */
		prot_bytes = 0;

		अगर (vc.out_size > vc.req_size) अणु
			data_direction = DMA_TO_DEVICE;
			exp_data_len = vc.out_size - vc.req_size;
			data_iter = vc.out_iter;
		पूर्ण अन्यथा अगर (vc.in_size > vc.rsp_size) अणु
			data_direction = DMA_FROM_DEVICE;
			exp_data_len = vc.in_size - vc.rsp_size;

			iov_iter_init(&in_iter, READ, &vq->iov[vc.out], vc.in,
				      vc.rsp_size + exp_data_len);
			iov_iter_advance(&in_iter, vc.rsp_size);
			data_iter = in_iter;
		पूर्ण अन्यथा अणु
			data_direction = DMA_NONE;
			exp_data_len = 0;
		पूर्ण
		/*
		 * If T10_PI header + payload is present, setup prot_iter values
		 * and recalculate data_iter क्रम vhost_scsi_mapal() mapping to
		 * host scatterlists via get_user_pages_fast().
		 */
		अगर (t10_pi) अणु
			अगर (v_req_pi.pi_bytesout) अणु
				अगर (data_direction != DMA_TO_DEVICE) अणु
					vq_err(vq, "Received non zero pi_bytesout,"
						" but wrong data_direction\n");
					जाओ err;
				पूर्ण
				prot_bytes = vhost32_to_cpu(vq, v_req_pi.pi_bytesout);
			पूर्ण अन्यथा अगर (v_req_pi.pi_bytesin) अणु
				अगर (data_direction != DMA_FROM_DEVICE) अणु
					vq_err(vq, "Received non zero pi_bytesin,"
						" but wrong data_direction\n");
					जाओ err;
				पूर्ण
				prot_bytes = vhost32_to_cpu(vq, v_req_pi.pi_bytesin);
			पूर्ण
			/*
			 * Set prot_iter to data_iter and truncate it to
			 * prot_bytes, and advance data_iter past any
			 * preceeding prot_bytes that may be present.
			 *
			 * Also fix up the exp_data_len to reflect only the
			 * actual data payload length.
			 */
			अगर (prot_bytes) अणु
				exp_data_len -= prot_bytes;
				prot_iter = data_iter;
				iov_iter_truncate(&prot_iter, prot_bytes);
				iov_iter_advance(&data_iter, prot_bytes);
			पूर्ण
			tag = vhost64_to_cpu(vq, v_req_pi.tag);
			task_attr = v_req_pi.task_attr;
			cdb = &v_req_pi.cdb[0];
			lun = vhost_buf_to_lun(v_req_pi.lun);
		पूर्ण अन्यथा अणु
			tag = vhost64_to_cpu(vq, v_req.tag);
			task_attr = v_req.task_attr;
			cdb = &v_req.cdb[0];
			lun = vhost_buf_to_lun(v_req.lun);
		पूर्ण
		/*
		 * Check that the received CDB size करोes not exceeded our
		 * hardcoded max क्रम vhost-scsi, then get a pre-allocated
		 * cmd descriptor क्रम the new virtio-scsi tag.
		 *
		 * TODO what अगर cdb was too small क्रम varlen cdb header?
		 */
		अगर (unlikely(scsi_command_size(cdb) > VHOST_SCSI_MAX_CDB_SIZE)) अणु
			vq_err(vq, "Received SCSI CDB with command_size: %d that"
				" exceeds SCSI_MAX_VARLEN_CDB_SIZE: %d\n",
				scsi_command_size(cdb), VHOST_SCSI_MAX_CDB_SIZE);
				जाओ err;
		पूर्ण
		cmd = vhost_scsi_get_cmd(vq, tpg, cdb, tag, lun, task_attr,
					 exp_data_len + prot_bytes,
					 data_direction);
		अगर (IS_ERR(cmd)) अणु
			vq_err(vq, "vhost_scsi_get_cmd failed %ld\n",
			       PTR_ERR(cmd));
			जाओ err;
		पूर्ण
		cmd->tvc_vhost = vs;
		cmd->tvc_vq = vq;
		cmd->tvc_resp_iov = vq->iov[vc.out];
		cmd->tvc_in_iovs = vc.in;

		pr_debug("vhost_scsi got command opcode: %#02x, lun: %d\n",
			 cmd->tvc_cdb[0], cmd->tvc_lun);
		pr_debug("cmd: %p exp_data_len: %d, prot_bytes: %d data_direction:"
			 " %d\n", cmd, exp_data_len, prot_bytes, data_direction);

		अगर (data_direction != DMA_NONE) अणु
			अगर (unlikely(vhost_scsi_mapal(cmd, prot_bytes,
						      &prot_iter, exp_data_len,
						      &data_iter))) अणु
				vq_err(vq, "Failed to map iov to sgl\n");
				vhost_scsi_release_cmd_res(&cmd->tvc_se_cmd);
				जाओ err;
			पूर्ण
		पूर्ण
		/*
		 * Save the descriptor from vhost_get_vq_desc() to be used to
		 * complete the virtio-scsi request in TCM callback context via
		 * vhost_scsi_queue_data_in() and vhost_scsi_queue_status()
		 */
		cmd->tvc_vq_desc = vc.head;
		vhost_scsi_target_queue_cmd(cmd);
		ret = 0;
err:
		/*
		 * ENXIO:  No more requests, or पढ़ो error, रुको क्रम next kick
		 * EINVAL: Invalid response buffer, drop the request
		 * EIO:    Respond with bad target
		 * EAGAIN: Pending request
		 */
		अगर (ret == -ENXIO)
			अवरोध;
		अन्यथा अगर (ret == -EIO)
			vhost_scsi_send_bad_target(vs, vq, vc.head, vc.out);
	पूर्ण जबतक (likely(!vhost_exceeds_weight(vq, ++c, 0)));
out:
	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम
vhost_scsi_send_पंचांगf_resp(काष्ठा vhost_scsi *vs, काष्ठा vhost_virtqueue *vq,
			 पूर्णांक in_iovs, पूर्णांक vq_desc, काष्ठा iovec *resp_iov,
			 पूर्णांक पंचांगf_resp_code)
अणु
	काष्ठा virtio_scsi_ctrl_पंचांगf_resp rsp;
	काष्ठा iov_iter iov_iter;
	पूर्णांक ret;

	pr_debug("%s\n", __func__);
	स_रखो(&rsp, 0, माप(rsp));
	rsp.response = पंचांगf_resp_code;

	iov_iter_init(&iov_iter, READ, resp_iov, in_iovs, माप(rsp));

	ret = copy_to_iter(&rsp, माप(rsp), &iov_iter);
	अगर (likely(ret == माप(rsp)))
		vhost_add_used_and_संकेत(&vs->dev, vq, vq_desc, 0);
	अन्यथा
		pr_err("Faulted on virtio_scsi_ctrl_tmf_resp\n");
पूर्ण

अटल व्योम vhost_scsi_पंचांगf_resp_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_scsi_पंचांगf *पंचांगf = container_of(work, काष्ठा vhost_scsi_पंचांगf,
						  vwork);
	पूर्णांक resp_code;

	अगर (पंचांगf->scsi_resp == TMR_FUNCTION_COMPLETE)
		resp_code = VIRTIO_SCSI_S_FUNCTION_SUCCEEDED;
	अन्यथा
		resp_code = VIRTIO_SCSI_S_FUNCTION_REJECTED;

	vhost_scsi_send_पंचांगf_resp(पंचांगf->vhost, &पंचांगf->svq->vq, पंचांगf->in_iovs,
				 पंचांगf->vq_desc, &पंचांगf->resp_iov, resp_code);
	vhost_scsi_release_पंचांगf_res(पंचांगf);
पूर्ण

अटल व्योम
vhost_scsi_handle_पंचांगf(काष्ठा vhost_scsi *vs, काष्ठा vhost_scsi_tpg *tpg,
		      काष्ठा vhost_virtqueue *vq,
		      काष्ठा virtio_scsi_ctrl_पंचांगf_req *vपंचांगf,
		      काष्ठा vhost_scsi_ctx *vc)
अणु
	काष्ठा vhost_scsi_virtqueue *svq = container_of(vq,
					काष्ठा vhost_scsi_virtqueue, vq);
	काष्ठा vhost_scsi_पंचांगf *पंचांगf;

	अगर (vhost32_to_cpu(vq, vपंचांगf->subtype) !=
	    VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET)
		जाओ send_reject;

	अगर (!tpg->tpg_nexus || !tpg->tpg_nexus->tvn_se_sess) अणु
		pr_err("Unable to locate active struct vhost_scsi_nexus for LUN RESET.\n");
		जाओ send_reject;
	पूर्ण

	mutex_lock(&tpg->tv_tpg_mutex);
	अगर (list_empty(&tpg->पंचांगf_queue)) अणु
		pr_err("Missing reserve TMF. Could not handle LUN RESET.\n");
		mutex_unlock(&tpg->tv_tpg_mutex);
		जाओ send_reject;
	पूर्ण

	पंचांगf = list_first_entry(&tpg->पंचांगf_queue, काष्ठा vhost_scsi_पंचांगf,
			       queue_entry);
	list_del_init(&पंचांगf->queue_entry);
	mutex_unlock(&tpg->tv_tpg_mutex);

	पंचांगf->tpg = tpg;
	पंचांगf->vhost = vs;
	पंचांगf->svq = svq;
	पंचांगf->resp_iov = vq->iov[vc->out];
	पंचांगf->vq_desc = vc->head;
	पंचांगf->in_iovs = vc->in;
	पंचांगf->inflight = vhost_scsi_get_inflight(vq);

	अगर (target_submit_पंचांगr(&पंचांगf->se_cmd, tpg->tpg_nexus->tvn_se_sess, शून्य,
			      vhost_buf_to_lun(vपंचांगf->lun), शून्य,
			      TMR_LUN_RESET, GFP_KERNEL, 0,
			      TARGET_SCF_ACK_KREF) < 0) अणु
		vhost_scsi_release_पंचांगf_res(पंचांगf);
		जाओ send_reject;
	पूर्ण

	वापस;

send_reject:
	vhost_scsi_send_पंचांगf_resp(vs, vq, vc->in, vc->head, &vq->iov[vc->out],
				 VIRTIO_SCSI_S_FUNCTION_REJECTED);
पूर्ण

अटल व्योम
vhost_scsi_send_an_resp(काष्ठा vhost_scsi *vs,
			काष्ठा vhost_virtqueue *vq,
			काष्ठा vhost_scsi_ctx *vc)
अणु
	काष्ठा virtio_scsi_ctrl_an_resp rsp;
	काष्ठा iov_iter iov_iter;
	पूर्णांक ret;

	pr_debug("%s\n", __func__);
	स_रखो(&rsp, 0, माप(rsp));	/* event_actual = 0 */
	rsp.response = VIRTIO_SCSI_S_OK;

	iov_iter_init(&iov_iter, READ, &vq->iov[vc->out], vc->in, माप(rsp));

	ret = copy_to_iter(&rsp, माप(rsp), &iov_iter);
	अगर (likely(ret == माप(rsp)))
		vhost_add_used_and_संकेत(&vs->dev, vq, vc->head, 0);
	अन्यथा
		pr_err("Faulted on virtio_scsi_ctrl_an_resp\n");
पूर्ण

अटल व्योम
vhost_scsi_ctl_handle_vq(काष्ठा vhost_scsi *vs, काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_scsi_tpg *tpg;
	जोड़ अणु
		__virtio32 type;
		काष्ठा virtio_scsi_ctrl_an_req an;
		काष्ठा virtio_scsi_ctrl_पंचांगf_req पंचांगf;
	पूर्ण v_req;
	काष्ठा vhost_scsi_ctx vc;
	माप_प्रकार typ_size;
	पूर्णांक ret, c = 0;

	mutex_lock(&vq->mutex);
	/*
	 * We can handle the vq only after the endpoपूर्णांक is setup by calling the
	 * VHOST_SCSI_SET_ENDPOINT ioctl.
	 */
	अगर (!vhost_vq_get_backend(vq))
		जाओ out;

	स_रखो(&vc, 0, माप(vc));

	vhost_disable_notअगरy(&vs->dev, vq);

	करो अणु
		ret = vhost_scsi_get_desc(vs, vq, &vc);
		अगर (ret)
			जाओ err;

		/*
		 * Get the request type first in order to setup
		 * other parameters dependent on the type.
		 */
		vc.req = &v_req.type;
		typ_size = माप(v_req.type);

		अगर (unlikely(!copy_from_iter_full(vc.req, typ_size,
						  &vc.out_iter))) अणु
			vq_err(vq, "Faulted on copy_from_iter tmf type\n");
			/*
			 * The size of the response buffer depends on the
			 * request type and must be validated against it.
			 * Since the request type is not known, करोn't send
			 * a response.
			 */
			जारी;
		पूर्ण

		चयन (vhost32_to_cpu(vq, v_req.type)) अणु
		हाल VIRTIO_SCSI_T_TMF:
			vc.req = &v_req.पंचांगf;
			vc.req_size = माप(काष्ठा virtio_scsi_ctrl_पंचांगf_req);
			vc.rsp_size = माप(काष्ठा virtio_scsi_ctrl_पंचांगf_resp);
			vc.lunp = &v_req.पंचांगf.lun[0];
			vc.target = &v_req.पंचांगf.lun[1];
			अवरोध;
		हाल VIRTIO_SCSI_T_AN_QUERY:
		हाल VIRTIO_SCSI_T_AN_SUBSCRIBE:
			vc.req = &v_req.an;
			vc.req_size = माप(काष्ठा virtio_scsi_ctrl_an_req);
			vc.rsp_size = माप(काष्ठा virtio_scsi_ctrl_an_resp);
			vc.lunp = &v_req.an.lun[0];
			vc.target = शून्य;
			अवरोध;
		शेष:
			vq_err(vq, "Unknown control request %d", v_req.type);
			जारी;
		पूर्ण

		/*
		 * Validate the size of request and response buffers.
		 * Check क्रम a sane response buffer so we can report
		 * early errors back to the guest.
		 */
		ret = vhost_scsi_chk_size(vq, &vc);
		अगर (ret)
			जाओ err;

		/*
		 * Get the rest of the request now that its size is known.
		 */
		vc.req += typ_size;
		vc.req_size -= typ_size;

		ret = vhost_scsi_get_req(vq, &vc, &tpg);
		अगर (ret)
			जाओ err;

		अगर (v_req.type == VIRTIO_SCSI_T_TMF)
			vhost_scsi_handle_पंचांगf(vs, tpg, vq, &v_req.पंचांगf, &vc);
		अन्यथा
			vhost_scsi_send_an_resp(vs, vq, &vc);
err:
		/*
		 * ENXIO:  No more requests, or पढ़ो error, रुको क्रम next kick
		 * EINVAL: Invalid response buffer, drop the request
		 * EIO:    Respond with bad target
		 * EAGAIN: Pending request
		 */
		अगर (ret == -ENXIO)
			अवरोध;
		अन्यथा अगर (ret == -EIO)
			vhost_scsi_send_bad_target(vs, vq, vc.head, vc.out);
	पूर्ण जबतक (likely(!vhost_exceeds_weight(vq, ++c, 0)));
out:
	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम vhost_scsi_ctl_handle_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						poll.work);
	काष्ठा vhost_scsi *vs = container_of(vq->dev, काष्ठा vhost_scsi, dev);

	pr_debug("%s: The handling func for control queue.\n", __func__);
	vhost_scsi_ctl_handle_vq(vs, vq);
पूर्ण

अटल व्योम
vhost_scsi_send_evt(काष्ठा vhost_scsi *vs,
		   काष्ठा vhost_scsi_tpg *tpg,
		   काष्ठा se_lun *lun,
		   u32 event,
		   u32 reason)
अणु
	काष्ठा vhost_scsi_evt *evt;

	evt = vhost_scsi_allocate_evt(vs, event, reason);
	अगर (!evt)
		वापस;

	अगर (tpg && lun) अणु
		/* TODO: share lun setup code with virtio-scsi.ko */
		/*
		 * Note: evt->event is zeroed when we allocate it and
		 * lun[4-7] need to be zero according to virtio-scsi spec.
		 */
		evt->event.lun[0] = 0x01;
		evt->event.lun[1] = tpg->tport_tpgt;
		अगर (lun->unpacked_lun >= 256)
			evt->event.lun[2] = lun->unpacked_lun >> 8 | 0x40 ;
		evt->event.lun[3] = lun->unpacked_lun & 0xFF;
	पूर्ण

	llist_add(&evt->list, &vs->vs_event_list);
	vhost_work_queue(&vs->dev, &vs->vs_event_work);
पूर्ण

अटल व्योम vhost_scsi_evt_handle_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						poll.work);
	काष्ठा vhost_scsi *vs = container_of(vq->dev, काष्ठा vhost_scsi, dev);

	mutex_lock(&vq->mutex);
	अगर (!vhost_vq_get_backend(vq))
		जाओ out;

	अगर (vs->vs_events_missed)
		vhost_scsi_send_evt(vs, शून्य, शून्य, VIRTIO_SCSI_T_NO_EVENT, 0);
out:
	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम vhost_scsi_handle_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						poll.work);
	काष्ठा vhost_scsi *vs = container_of(vq->dev, काष्ठा vhost_scsi, dev);

	vhost_scsi_handle_vq(vs, vq);
पूर्ण

अटल व्योम vhost_scsi_flush_vq(काष्ठा vhost_scsi *vs, पूर्णांक index)
अणु
	vhost_poll_flush(&vs->vqs[index].vq.poll);
पूर्ण

/* Callers must hold dev mutex */
अटल व्योम vhost_scsi_flush(काष्ठा vhost_scsi *vs)
अणु
	काष्ठा vhost_scsi_inflight *old_inflight[VHOST_SCSI_MAX_VQ];
	पूर्णांक i;

	/* Init new inflight and remember the old inflight */
	vhost_scsi_init_inflight(vs, old_inflight);

	/*
	 * The inflight->kref was initialized to 1. We decrement it here to
	 * indicate the start of the flush operation so that it will reach 0
	 * when all the reqs are finished.
	 */
	क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		kref_put(&old_inflight[i]->kref, vhost_scsi_करोne_inflight);

	/* Flush both the vhost poll and vhost work */
	क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		vhost_scsi_flush_vq(vs, i);
	vhost_work_flush(&vs->dev, &vs->vs_completion_work);
	vhost_work_flush(&vs->dev, &vs->vs_event_work);

	/* Wait क्रम all reqs issued beक्रमe the flush to be finished */
	क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		रुको_क्रम_completion(&old_inflight[i]->comp);
पूर्ण

अटल व्योम vhost_scsi_destroy_vq_cmds(काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_scsi_virtqueue *svq = container_of(vq,
					काष्ठा vhost_scsi_virtqueue, vq);
	काष्ठा vhost_scsi_cmd *tv_cmd;
	अचिन्हित पूर्णांक i;

	अगर (!svq->scsi_cmds)
		वापस;

	क्रम (i = 0; i < svq->max_cmds; i++) अणु
		tv_cmd = &svq->scsi_cmds[i];

		kमुक्त(tv_cmd->tvc_sgl);
		kमुक्त(tv_cmd->tvc_prot_sgl);
		kमुक्त(tv_cmd->tvc_upages);
	पूर्ण

	sbiपंचांगap_मुक्त(&svq->scsi_tags);
	kमुक्त(svq->scsi_cmds);
	svq->scsi_cmds = शून्य;
पूर्ण

अटल पूर्णांक vhost_scsi_setup_vq_cmds(काष्ठा vhost_virtqueue *vq, पूर्णांक max_cmds)
अणु
	काष्ठा vhost_scsi_virtqueue *svq = container_of(vq,
					काष्ठा vhost_scsi_virtqueue, vq);
	काष्ठा vhost_scsi_cmd *tv_cmd;
	अचिन्हित पूर्णांक i;

	अगर (svq->scsi_cmds)
		वापस 0;

	अगर (sbiपंचांगap_init_node(&svq->scsi_tags, max_cmds, -1, GFP_KERNEL,
			      NUMA_NO_NODE, false, true))
		वापस -ENOMEM;
	svq->max_cmds = max_cmds;

	svq->scsi_cmds = kसुस्मृति(max_cmds, माप(*tv_cmd), GFP_KERNEL);
	अगर (!svq->scsi_cmds) अणु
		sbiपंचांगap_मुक्त(&svq->scsi_tags);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < max_cmds; i++) अणु
		tv_cmd = &svq->scsi_cmds[i];

		tv_cmd->tvc_sgl = kसुस्मृति(VHOST_SCSI_PREALLOC_SGLS,
					  माप(काष्ठा scatterlist),
					  GFP_KERNEL);
		अगर (!tv_cmd->tvc_sgl) अणु
			pr_err("Unable to allocate tv_cmd->tvc_sgl\n");
			जाओ out;
		पूर्ण

		tv_cmd->tvc_upages = kसुस्मृति(VHOST_SCSI_PREALLOC_UPAGES,
					     माप(काष्ठा page *),
					     GFP_KERNEL);
		अगर (!tv_cmd->tvc_upages) अणु
			pr_err("Unable to allocate tv_cmd->tvc_upages\n");
			जाओ out;
		पूर्ण

		tv_cmd->tvc_prot_sgl = kसुस्मृति(VHOST_SCSI_PREALLOC_PROT_SGLS,
					       माप(काष्ठा scatterlist),
					       GFP_KERNEL);
		अगर (!tv_cmd->tvc_prot_sgl) अणु
			pr_err("Unable to allocate tv_cmd->tvc_prot_sgl\n");
			जाओ out;
		पूर्ण
	पूर्ण
	वापस 0;
out:
	vhost_scsi_destroy_vq_cmds(vq);
	वापस -ENOMEM;
पूर्ण

/*
 * Called from vhost_scsi_ioctl() context to walk the list of available
 * vhost_scsi_tpg with an active काष्ठा vhost_scsi_nexus
 *
 *  The lock nesting rule is:
 *    vhost_scsi_mutex -> vs->dev.mutex -> tpg->tv_tpg_mutex -> vq->mutex
 */
अटल पूर्णांक
vhost_scsi_set_endpoपूर्णांक(काष्ठा vhost_scsi *vs,
			काष्ठा vhost_scsi_target *t)
अणु
	काष्ठा se_portal_group *se_tpg;
	काष्ठा vhost_scsi_tport *tv_tport;
	काष्ठा vhost_scsi_tpg *tpg;
	काष्ठा vhost_scsi_tpg **vs_tpg;
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक index, ret, i, len;
	bool match = false;

	mutex_lock(&vhost_scsi_mutex);
	mutex_lock(&vs->dev.mutex);

	/* Verअगरy that ring has been setup correctly. */
	क्रम (index = 0; index < vs->dev.nvqs; ++index) अणु
		/* Verअगरy that ring has been setup correctly. */
		अगर (!vhost_vq_access_ok(&vs->vqs[index].vq)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	len = माप(vs_tpg[0]) * VHOST_SCSI_MAX_TARGET;
	vs_tpg = kzalloc(len, GFP_KERNEL);
	अगर (!vs_tpg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (vs->vs_tpg)
		स_नकल(vs_tpg, vs->vs_tpg, len);

	list_क्रम_each_entry(tpg, &vhost_scsi_list, tv_tpg_list) अणु
		mutex_lock(&tpg->tv_tpg_mutex);
		अगर (!tpg->tpg_nexus) अणु
			mutex_unlock(&tpg->tv_tpg_mutex);
			जारी;
		पूर्ण
		अगर (tpg->tv_tpg_vhost_count != 0) अणु
			mutex_unlock(&tpg->tv_tpg_mutex);
			जारी;
		पूर्ण
		tv_tport = tpg->tport;

		अगर (!म_भेद(tv_tport->tport_name, t->vhost_wwpn)) अणु
			अगर (vs->vs_tpg && vs->vs_tpg[tpg->tport_tpgt]) अणु
				mutex_unlock(&tpg->tv_tpg_mutex);
				ret = -EEXIST;
				जाओ undepend;
			पूर्ण
			/*
			 * In order to ensure inभागidual vhost-scsi configfs
			 * groups cannot be हटाओd जबतक in use by vhost ioctl,
			 * go ahead and take an explicit se_tpg->tpg_group.cg_item
			 * dependency now.
			 */
			se_tpg = &tpg->se_tpg;
			ret = target_depend_item(&se_tpg->tpg_group.cg_item);
			अगर (ret) अणु
				pr_warn("target_depend_item() failed: %d\n", ret);
				mutex_unlock(&tpg->tv_tpg_mutex);
				जाओ undepend;
			पूर्ण
			tpg->tv_tpg_vhost_count++;
			tpg->vhost_scsi = vs;
			vs_tpg[tpg->tport_tpgt] = tpg;
			match = true;
		पूर्ण
		mutex_unlock(&tpg->tv_tpg_mutex);
	पूर्ण

	अगर (match) अणु
		स_नकल(vs->vs_vhost_wwpn, t->vhost_wwpn,
		       माप(vs->vs_vhost_wwpn));

		क्रम (i = VHOST_SCSI_VQ_IO; i < VHOST_SCSI_MAX_VQ; i++) अणु
			vq = &vs->vqs[i].vq;
			अगर (!vhost_vq_is_setup(vq))
				जारी;

			ret = vhost_scsi_setup_vq_cmds(vq, vq->num);
			अगर (ret)
				जाओ destroy_vq_cmds;
		पूर्ण

		क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++) अणु
			vq = &vs->vqs[i].vq;
			mutex_lock(&vq->mutex);
			vhost_vq_set_backend(vq, vs_tpg);
			vhost_vq_init_access(vq);
			mutex_unlock(&vq->mutex);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EEXIST;
	पूर्ण

	/*
	 * Act as synchronize_rcu to make sure access to
	 * old vs->vs_tpg is finished.
	 */
	vhost_scsi_flush(vs);
	kमुक्त(vs->vs_tpg);
	vs->vs_tpg = vs_tpg;
	जाओ out;

destroy_vq_cmds:
	क्रम (i--; i >= VHOST_SCSI_VQ_IO; i--) अणु
		अगर (!vhost_vq_get_backend(&vs->vqs[i].vq))
			vhost_scsi_destroy_vq_cmds(&vs->vqs[i].vq);
	पूर्ण
undepend:
	क्रम (i = 0; i < VHOST_SCSI_MAX_TARGET; i++) अणु
		tpg = vs_tpg[i];
		अगर (tpg) अणु
			tpg->tv_tpg_vhost_count--;
			target_undepend_item(&tpg->se_tpg.tpg_group.cg_item);
		पूर्ण
	पूर्ण
	kमुक्त(vs_tpg);
out:
	mutex_unlock(&vs->dev.mutex);
	mutex_unlock(&vhost_scsi_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
vhost_scsi_clear_endpoपूर्णांक(काष्ठा vhost_scsi *vs,
			  काष्ठा vhost_scsi_target *t)
अणु
	काष्ठा se_portal_group *se_tpg;
	काष्ठा vhost_scsi_tport *tv_tport;
	काष्ठा vhost_scsi_tpg *tpg;
	काष्ठा vhost_virtqueue *vq;
	bool match = false;
	पूर्णांक index, ret, i;
	u8 target;

	mutex_lock(&vhost_scsi_mutex);
	mutex_lock(&vs->dev.mutex);
	/* Verअगरy that ring has been setup correctly. */
	क्रम (index = 0; index < vs->dev.nvqs; ++index) अणु
		अगर (!vhost_vq_access_ok(&vs->vqs[index].vq)) अणु
			ret = -EFAULT;
			जाओ err_dev;
		पूर्ण
	पूर्ण

	अगर (!vs->vs_tpg) अणु
		ret = 0;
		जाओ err_dev;
	पूर्ण

	क्रम (i = 0; i < VHOST_SCSI_MAX_TARGET; i++) अणु
		target = i;
		tpg = vs->vs_tpg[target];
		अगर (!tpg)
			जारी;

		mutex_lock(&tpg->tv_tpg_mutex);
		tv_tport = tpg->tport;
		अगर (!tv_tport) अणु
			ret = -ENODEV;
			जाओ err_tpg;
		पूर्ण

		अगर (म_भेद(tv_tport->tport_name, t->vhost_wwpn)) अणु
			pr_warn("tv_tport->tport_name: %s, tpg->tport_tpgt: %hu"
				" does not match t->vhost_wwpn: %s, t->vhost_tpgt: %hu\n",
				tv_tport->tport_name, tpg->tport_tpgt,
				t->vhost_wwpn, t->vhost_tpgt);
			ret = -EINVAL;
			जाओ err_tpg;
		पूर्ण
		tpg->tv_tpg_vhost_count--;
		tpg->vhost_scsi = शून्य;
		vs->vs_tpg[target] = शून्य;
		match = true;
		mutex_unlock(&tpg->tv_tpg_mutex);
		/*
		 * Release se_tpg->tpg_group.cg_item configfs dependency now
		 * to allow vhost-scsi WWPN se_tpg->tpg_group shutकरोwn to occur.
		 */
		se_tpg = &tpg->se_tpg;
		target_undepend_item(&se_tpg->tpg_group.cg_item);
	पूर्ण
	अगर (match) अणु
		क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++) अणु
			vq = &vs->vqs[i].vq;
			mutex_lock(&vq->mutex);
			vhost_vq_set_backend(vq, शून्य);
			mutex_unlock(&vq->mutex);
			/*
			 * Make sure cmds are not running beक्रमe tearing them
			 * करोwn.
			 */
			vhost_scsi_flush(vs);
			vhost_scsi_destroy_vq_cmds(vq);
		पूर्ण
	पूर्ण
	/*
	 * Act as synchronize_rcu to make sure access to
	 * old vs->vs_tpg is finished.
	 */
	vhost_scsi_flush(vs);
	kमुक्त(vs->vs_tpg);
	vs->vs_tpg = शून्य;
	WARN_ON(vs->vs_events_nr);
	mutex_unlock(&vs->dev.mutex);
	mutex_unlock(&vhost_scsi_mutex);
	वापस 0;

err_tpg:
	mutex_unlock(&tpg->tv_tpg_mutex);
err_dev:
	mutex_unlock(&vs->dev.mutex);
	mutex_unlock(&vhost_scsi_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vhost_scsi_set_features(काष्ठा vhost_scsi *vs, u64 features)
अणु
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक i;

	अगर (features & ~VHOST_SCSI_FEATURES)
		वापस -EOPNOTSUPP;

	mutex_lock(&vs->dev.mutex);
	अगर ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&vs->dev)) अणु
		mutex_unlock(&vs->dev.mutex);
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < VHOST_SCSI_MAX_VQ; i++) अणु
		vq = &vs->vqs[i].vq;
		mutex_lock(&vq->mutex);
		vq->acked_features = features;
		mutex_unlock(&vq->mutex);
	पूर्ण
	mutex_unlock(&vs->dev.mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_scsi *vs;
	काष्ठा vhost_virtqueue **vqs;
	पूर्णांक r = -ENOMEM, i;

	vs = kvzalloc(माप(*vs), GFP_KERNEL);
	अगर (!vs)
		जाओ err_vs;

	vqs = kदो_स्मृति_array(VHOST_SCSI_MAX_VQ, माप(*vqs), GFP_KERNEL);
	अगर (!vqs)
		जाओ err_vqs;

	vhost_work_init(&vs->vs_completion_work, vhost_scsi_complete_cmd_work);
	vhost_work_init(&vs->vs_event_work, vhost_scsi_evt_work);

	vs->vs_events_nr = 0;
	vs->vs_events_missed = false;

	vqs[VHOST_SCSI_VQ_CTL] = &vs->vqs[VHOST_SCSI_VQ_CTL].vq;
	vqs[VHOST_SCSI_VQ_EVT] = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;
	vs->vqs[VHOST_SCSI_VQ_CTL].vq.handle_kick = vhost_scsi_ctl_handle_kick;
	vs->vqs[VHOST_SCSI_VQ_EVT].vq.handle_kick = vhost_scsi_evt_handle_kick;
	क्रम (i = VHOST_SCSI_VQ_IO; i < VHOST_SCSI_MAX_VQ; i++) अणु
		vqs[i] = &vs->vqs[i].vq;
		vs->vqs[i].vq.handle_kick = vhost_scsi_handle_kick;
	पूर्ण
	vhost_dev_init(&vs->dev, vqs, VHOST_SCSI_MAX_VQ, UIO_MAXIOV,
		       VHOST_SCSI_WEIGHT, 0, true, शून्य);

	vhost_scsi_init_inflight(vs, शून्य);

	f->निजी_data = vs;
	वापस 0;

err_vqs:
	kvमुक्त(vs);
err_vs:
	वापस r;
पूर्ण

अटल पूर्णांक vhost_scsi_release(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_scsi *vs = f->निजी_data;
	काष्ठा vhost_scsi_target t;

	mutex_lock(&vs->dev.mutex);
	स_नकल(t.vhost_wwpn, vs->vs_vhost_wwpn, माप(t.vhost_wwpn));
	mutex_unlock(&vs->dev.mutex);
	vhost_scsi_clear_endpoपूर्णांक(vs, &t);
	vhost_dev_stop(&vs->dev);
	vhost_dev_cleanup(&vs->dev);
	/* Jobs can re-queue themselves in evt kick handler. Do extra flush. */
	vhost_scsi_flush(vs);
	kमुक्त(vs->dev.vqs);
	kvमुक्त(vs);
	वापस 0;
पूर्ण

अटल दीर्घ
vhost_scsi_ioctl(काष्ठा file *f,
		 अचिन्हित पूर्णांक ioctl,
		 अचिन्हित दीर्घ arg)
अणु
	काष्ठा vhost_scsi *vs = f->निजी_data;
	काष्ठा vhost_scsi_target backend;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 __user *featurep = argp;
	u32 __user *eventsp = argp;
	u32 events_missed;
	u64 features;
	पूर्णांक r, abi_version = VHOST_SCSI_ABI_VERSION;
	काष्ठा vhost_virtqueue *vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;

	चयन (ioctl) अणु
	हाल VHOST_SCSI_SET_ENDPOINT:
		अगर (copy_from_user(&backend, argp, माप backend))
			वापस -EFAULT;
		अगर (backend.reserved != 0)
			वापस -EOPNOTSUPP;

		वापस vhost_scsi_set_endpoपूर्णांक(vs, &backend);
	हाल VHOST_SCSI_CLEAR_ENDPOINT:
		अगर (copy_from_user(&backend, argp, माप backend))
			वापस -EFAULT;
		अगर (backend.reserved != 0)
			वापस -EOPNOTSUPP;

		वापस vhost_scsi_clear_endpoपूर्णांक(vs, &backend);
	हाल VHOST_SCSI_GET_ABI_VERSION:
		अगर (copy_to_user(argp, &abi_version, माप abi_version))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SCSI_SET_EVENTS_MISSED:
		अगर (get_user(events_missed, eventsp))
			वापस -EFAULT;
		mutex_lock(&vq->mutex);
		vs->vs_events_missed = events_missed;
		mutex_unlock(&vq->mutex);
		वापस 0;
	हाल VHOST_SCSI_GET_EVENTS_MISSED:
		mutex_lock(&vq->mutex);
		events_missed = vs->vs_events_missed;
		mutex_unlock(&vq->mutex);
		अगर (put_user(events_missed, eventsp))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_GET_FEATURES:
		features = VHOST_SCSI_FEATURES;
		अगर (copy_to_user(featurep, &features, माप features))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_FEATURES:
		अगर (copy_from_user(&features, featurep, माप features))
			वापस -EFAULT;
		वापस vhost_scsi_set_features(vs, features);
	शेष:
		mutex_lock(&vs->dev.mutex);
		r = vhost_dev_ioctl(&vs->dev, ioctl, argp);
		/* TODO: flush backend after dev ioctl. */
		अगर (r == -ENOIOCTLCMD)
			r = vhost_vring_ioctl(&vs->dev, ioctl, argp);
		mutex_unlock(&vs->dev.mutex);
		वापस r;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations vhost_scsi_fops = अणु
	.owner          = THIS_MODULE,
	.release        = vhost_scsi_release,
	.unlocked_ioctl = vhost_scsi_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो           = vhost_scsi_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice vhost_scsi_misc = अणु
	MISC_DYNAMIC_MINOR,
	"vhost-scsi",
	&vhost_scsi_fops,
पूर्ण;

अटल पूर्णांक __init vhost_scsi_रेजिस्टर(व्योम)
अणु
	वापस misc_रेजिस्टर(&vhost_scsi_misc);
पूर्ण

अटल व्योम vhost_scsi_deरेजिस्टर(व्योम)
अणु
	misc_deरेजिस्टर(&vhost_scsi_misc);
पूर्ण

अटल अक्षर *vhost_scsi_dump_proto_id(काष्ठा vhost_scsi_tport *tport)
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

अटल व्योम
vhost_scsi_करो_plug(काष्ठा vhost_scsi_tpg *tpg,
		  काष्ठा se_lun *lun, bool plug)
अणु

	काष्ठा vhost_scsi *vs = tpg->vhost_scsi;
	काष्ठा vhost_virtqueue *vq;
	u32 reason;

	अगर (!vs)
		वापस;

	mutex_lock(&vs->dev.mutex);

	अगर (plug)
		reason = VIRTIO_SCSI_EVT_RESET_RESCAN;
	अन्यथा
		reason = VIRTIO_SCSI_EVT_RESET_REMOVED;

	vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;
	mutex_lock(&vq->mutex);
	अगर (vhost_has_feature(vq, VIRTIO_SCSI_F_HOTPLUG))
		vhost_scsi_send_evt(vs, tpg, lun,
				   VIRTIO_SCSI_T_TRANSPORT_RESET, reason);
	mutex_unlock(&vq->mutex);
	mutex_unlock(&vs->dev.mutex);
पूर्ण

अटल व्योम vhost_scsi_hotplug(काष्ठा vhost_scsi_tpg *tpg, काष्ठा se_lun *lun)
अणु
	vhost_scsi_करो_plug(tpg, lun, true);
पूर्ण

अटल व्योम vhost_scsi_hotunplug(काष्ठा vhost_scsi_tpg *tpg, काष्ठा se_lun *lun)
अणु
	vhost_scsi_करो_plug(tpg, lun, false);
पूर्ण

अटल पूर्णांक vhost_scsi_port_link(काष्ठा se_portal_group *se_tpg,
			       काष्ठा se_lun *lun)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	काष्ठा vhost_scsi_पंचांगf *पंचांगf;

	पंचांगf = kzalloc(माप(*पंचांगf), GFP_KERNEL);
	अगर (!पंचांगf)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&पंचांगf->queue_entry);
	vhost_work_init(&पंचांगf->vwork, vhost_scsi_पंचांगf_resp_work);

	mutex_lock(&vhost_scsi_mutex);

	mutex_lock(&tpg->tv_tpg_mutex);
	tpg->tv_tpg_port_count++;
	list_add_tail(&पंचांगf->queue_entry, &tpg->पंचांगf_queue);
	mutex_unlock(&tpg->tv_tpg_mutex);

	vhost_scsi_hotplug(tpg, lun);

	mutex_unlock(&vhost_scsi_mutex);

	वापस 0;
पूर्ण

अटल व्योम vhost_scsi_port_unlink(काष्ठा se_portal_group *se_tpg,
				  काष्ठा se_lun *lun)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	काष्ठा vhost_scsi_पंचांगf *पंचांगf;

	mutex_lock(&vhost_scsi_mutex);

	mutex_lock(&tpg->tv_tpg_mutex);
	tpg->tv_tpg_port_count--;
	पंचांगf = list_first_entry(&tpg->पंचांगf_queue, काष्ठा vhost_scsi_पंचांगf,
			       queue_entry);
	list_del(&पंचांगf->queue_entry);
	kमुक्त(पंचांगf);
	mutex_unlock(&tpg->tv_tpg_mutex);

	vhost_scsi_hotunplug(tpg, lun);

	mutex_unlock(&vhost_scsi_mutex);
पूर्ण

अटल sमाप_प्रकार vhost_scsi_tpg_attrib_fabric_prot_type_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = kम_से_अदीर्घ(page, 0, &val);

	अगर (ret) अणु
		pr_err("kstrtoul() returned %d for fabric_prot_type\n", ret);
		वापस ret;
	पूर्ण
	अगर (val != 0 && val != 1 && val != 3) अणु
		pr_err("Invalid vhost_scsi fabric_prot_type: %lu\n", val);
		वापस -EINVAL;
	पूर्ण
	tpg->tv_fabric_prot_type = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार vhost_scsi_tpg_attrib_fabric_prot_type_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);

	वापस प्र_लिखो(page, "%d\n", tpg->tv_fabric_prot_type);
पूर्ण

CONFIGFS_ATTR(vhost_scsi_tpg_attrib_, fabric_prot_type);

अटल काष्ठा configfs_attribute *vhost_scsi_tpg_attrib_attrs[] = अणु
	&vhost_scsi_tpg_attrib_attr_fabric_prot_type,
	शून्य,
पूर्ण;

अटल पूर्णांक vhost_scsi_make_nexus(काष्ठा vhost_scsi_tpg *tpg,
				स्थिर अक्षर *name)
अणु
	काष्ठा vhost_scsi_nexus *tv_nexus;

	mutex_lock(&tpg->tv_tpg_mutex);
	अगर (tpg->tpg_nexus) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_debug("tpg->tpg_nexus already exists\n");
		वापस -EEXIST;
	पूर्ण

	tv_nexus = kzalloc(माप(*tv_nexus), GFP_KERNEL);
	अगर (!tv_nexus) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to allocate struct vhost_scsi_nexus\n");
		वापस -ENOMEM;
	पूर्ण
	/*
	 * Since we are running in 'demo mode' this call with generate a
	 * काष्ठा se_node_acl क्रम the vhost_scsi काष्ठा se_portal_group with
	 * the SCSI Initiator port name of the passed configfs group 'name'.
	 */
	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg, 0, 0,
					TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS,
					(अचिन्हित अक्षर *)name, tv_nexus, शून्य);
	अगर (IS_ERR(tv_nexus->tvn_se_sess)) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		kमुक्त(tv_nexus);
		वापस -ENOMEM;
	पूर्ण
	tpg->tpg_nexus = tv_nexus;

	mutex_unlock(&tpg->tv_tpg_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_scsi_drop_nexus(काष्ठा vhost_scsi_tpg *tpg)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा vhost_scsi_nexus *tv_nexus;

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
		pr_err("Unable to remove TCM_vhost I_T Nexus with"
			" active TPG port count: %d\n",
			tpg->tv_tpg_port_count);
		वापस -EBUSY;
	पूर्ण

	अगर (tpg->tv_tpg_vhost_count != 0) अणु
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to remove TCM_vhost I_T Nexus with"
			" active TPG vhost count: %d\n",
			tpg->tv_tpg_vhost_count);
		वापस -EBUSY;
	पूर्ण

	pr_debug("TCM_vhost_ConfigFS: Removing I_T Nexus to emulated"
		" %s Initiator Port: %s\n", vhost_scsi_dump_proto_id(tpg->tport),
		tv_nexus->tvn_se_sess->se_node_acl->initiatorname);

	/*
	 * Release the SCSI I_T Nexus to the emulated vhost Target Port
	 */
	target_हटाओ_session(se_sess);
	tpg->tpg_nexus = शून्य;
	mutex_unlock(&tpg->tv_tpg_mutex);

	kमुक्त(tv_nexus);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार vhost_scsi_tpg_nexus_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	काष्ठा vhost_scsi_nexus *tv_nexus;
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

अटल sमाप_प्रकार vhost_scsi_tpg_nexus_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);
	काष्ठा vhost_scsi_tport *tport_wwn = tpg->tport;
	अचिन्हित अक्षर i_port[VHOST_SCSI_NAMELEN], *ptr, *port_ptr;
	पूर्णांक ret;
	/*
	 * Shutकरोwn the active I_T nexus अगर 'NULL' is passed..
	 */
	अगर (!म_भेदन(page, "NULL", 4)) अणु
		ret = vhost_scsi_drop_nexus(tpg);
		वापस (!ret) ? count : ret;
	पूर्ण
	/*
	 * Otherwise make sure the passed भव Initiator port WWN matches
	 * the fabric protocol_id set in vhost_scsi_make_tport(), and call
	 * vhost_scsi_make_nexus().
	 */
	अगर (म_माप(page) >= VHOST_SCSI_NAMELEN) अणु
		pr_err("Emulated NAA Sas Address: %s, exceeds"
				" max: %d\n", page, VHOST_SCSI_NAMELEN);
		वापस -EINVAL;
	पूर्ण
	snम_लिखो(&i_port[0], VHOST_SCSI_NAMELEN, "%s", page);

	ptr = म_माला(i_port, "naa.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_SAS) अणु
			pr_err("Passed SAS Initiator Port %s does not"
				" match target port protoid: %s\n", i_port,
				vhost_scsi_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "fc.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_FCP) अणु
			pr_err("Passed FCP Initiator Port %s does not"
				" match target port protoid: %s\n", i_port,
				vhost_scsi_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[3]; /* Skip over "fc." */
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "iqn.");
	अगर (ptr) अणु
		अगर (tport_wwn->tport_proto_id != SCSI_PROTOCOL_ISCSI) अणु
			pr_err("Passed iSCSI Initiator Port %s does not"
				" match target port protoid: %s\n", i_port,
				vhost_scsi_dump_proto_id(tport_wwn));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	pr_err("Unable to locate prefix for emulated Initiator Port:"
			" %s\n", i_port);
	वापस -EINVAL;
	/*
	 * Clear any trailing newline क्रम the NAA WWN
	 */
check_newline:
	अगर (i_port[म_माप(i_port)-1] == '\n')
		i_port[म_माप(i_port)-1] = '\0';

	ret = vhost_scsi_make_nexus(tpg, port_ptr);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

CONFIGFS_ATTR(vhost_scsi_tpg_, nexus);

अटल काष्ठा configfs_attribute *vhost_scsi_tpg_attrs[] = अणु
	&vhost_scsi_tpg_attr_nexus,
	शून्य,
पूर्ण;

अटल काष्ठा se_portal_group *
vhost_scsi_make_tpg(काष्ठा se_wwn *wwn, स्थिर अक्षर *name)
अणु
	काष्ठा vhost_scsi_tport *tport = container_of(wwn,
			काष्ठा vhost_scsi_tport, tport_wwn);

	काष्ठा vhost_scsi_tpg *tpg;
	u16 tpgt;
	पूर्णांक ret;

	अगर (म_माला(name, "tpgt_") != name)
		वापस ERR_PTR(-EINVAL);
	अगर (kstrtou16(name + 5, 10, &tpgt) || tpgt >= VHOST_SCSI_MAX_TARGET)
		वापस ERR_PTR(-EINVAL);

	tpg = kzalloc(माप(*tpg), GFP_KERNEL);
	अगर (!tpg) अणु
		pr_err("Unable to allocate struct vhost_scsi_tpg");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mutex_init(&tpg->tv_tpg_mutex);
	INIT_LIST_HEAD(&tpg->tv_tpg_list);
	INIT_LIST_HEAD(&tpg->पंचांगf_queue);
	tpg->tport = tport;
	tpg->tport_tpgt = tpgt;

	ret = core_tpg_रेजिस्टर(wwn, &tpg->se_tpg, tport->tport_proto_id);
	अगर (ret < 0) अणु
		kमुक्त(tpg);
		वापस शून्य;
	पूर्ण
	mutex_lock(&vhost_scsi_mutex);
	list_add_tail(&tpg->tv_tpg_list, &vhost_scsi_list);
	mutex_unlock(&vhost_scsi_mutex);

	वापस &tpg->se_tpg;
पूर्ण

अटल व्योम vhost_scsi_drop_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा vhost_scsi_tpg *tpg = container_of(se_tpg,
				काष्ठा vhost_scsi_tpg, se_tpg);

	mutex_lock(&vhost_scsi_mutex);
	list_del(&tpg->tv_tpg_list);
	mutex_unlock(&vhost_scsi_mutex);
	/*
	 * Release the भव I_T Nexus क्रम this vhost TPG
	 */
	vhost_scsi_drop_nexus(tpg);
	/*
	 * Deरेजिस्टर the se_tpg from TCM..
	 */
	core_tpg_deरेजिस्टर(se_tpg);
	kमुक्त(tpg);
पूर्ण

अटल काष्ठा se_wwn *
vhost_scsi_make_tport(काष्ठा target_fabric_configfs *tf,
		     काष्ठा config_group *group,
		     स्थिर अक्षर *name)
अणु
	काष्ठा vhost_scsi_tport *tport;
	अक्षर *ptr;
	u64 wwpn = 0;
	पूर्णांक off = 0;

	/* अगर (vhost_scsi_parse_wwn(name, &wwpn, 1) < 0)
		वापस ERR_PTR(-EINVAL); */

	tport = kzalloc(माप(*tport), GFP_KERNEL);
	अगर (!tport) अणु
		pr_err("Unable to allocate struct vhost_scsi_tport");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
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

	pr_err("Unable to locate prefix for emulated Target Port:"
			" %s\n", name);
	kमुक्त(tport);
	वापस ERR_PTR(-EINVAL);

check_len:
	अगर (म_माप(name) >= VHOST_SCSI_NAMELEN) अणु
		pr_err("Emulated %s Address: %s, exceeds"
			" max: %d\n", name, vhost_scsi_dump_proto_id(tport),
			VHOST_SCSI_NAMELEN);
		kमुक्त(tport);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	snम_लिखो(&tport->tport_name[0], VHOST_SCSI_NAMELEN, "%s", &name[off]);

	pr_debug("TCM_VHost_ConfigFS: Allocated emulated Target"
		" %s Address: %s\n", vhost_scsi_dump_proto_id(tport), name);

	वापस &tport->tport_wwn;
पूर्ण

अटल व्योम vhost_scsi_drop_tport(काष्ठा se_wwn *wwn)
अणु
	काष्ठा vhost_scsi_tport *tport = container_of(wwn,
				काष्ठा vhost_scsi_tport, tport_wwn);

	pr_debug("TCM_VHost_ConfigFS: Deallocating emulated Target"
		" %s Address: %s\n", vhost_scsi_dump_proto_id(tport),
		tport->tport_name);

	kमुक्त(tport);
पूर्ण

अटल sमाप_प्रकार
vhost_scsi_wwn_version_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "TCM_VHOST fabric module %s on %s/%s"
		"on "UTS_RELEASE"\n", VHOST_SCSI_VERSION, utsname()->sysname,
		utsname()->machine);
पूर्ण

CONFIGFS_ATTR_RO(vhost_scsi_wwn_, version);

अटल काष्ठा configfs_attribute *vhost_scsi_wwn_attrs[] = अणु
	&vhost_scsi_wwn_attr_version,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा target_core_fabric_ops vhost_scsi_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "vhost",
	.max_data_sg_nents		= VHOST_SCSI_PREALLOC_SGLS,
	.tpg_get_wwn			= vhost_scsi_get_fabric_wwn,
	.tpg_get_tag			= vhost_scsi_get_tpgt,
	.tpg_check_demo_mode		= vhost_scsi_check_true,
	.tpg_check_demo_mode_cache	= vhost_scsi_check_true,
	.tpg_check_demo_mode_ग_लिखो_protect = vhost_scsi_check_false,
	.tpg_check_prod_mode_ग_लिखो_protect = vhost_scsi_check_false,
	.tpg_check_prot_fabric_only	= vhost_scsi_check_prot_fabric_only,
	.tpg_get_inst_index		= vhost_scsi_tpg_get_inst_index,
	.release_cmd			= vhost_scsi_release_cmd,
	.check_stop_मुक्त		= vhost_scsi_check_stop_मुक्त,
	.sess_get_index			= vhost_scsi_sess_get_index,
	.sess_get_initiator_sid		= शून्य,
	.ग_लिखो_pending			= vhost_scsi_ग_लिखो_pending,
	.set_शेष_node_attributes	= vhost_scsi_set_शेष_node_attrs,
	.get_cmd_state			= vhost_scsi_get_cmd_state,
	.queue_data_in			= vhost_scsi_queue_data_in,
	.queue_status			= vhost_scsi_queue_status,
	.queue_पंचांग_rsp			= vhost_scsi_queue_पंचांग_rsp,
	.पातed_task			= vhost_scsi_पातed_task,
	/*
	 * Setup callers क्रम generic logic in target_core_fabric_configfs.c
	 */
	.fabric_make_wwn		= vhost_scsi_make_tport,
	.fabric_drop_wwn		= vhost_scsi_drop_tport,
	.fabric_make_tpg		= vhost_scsi_make_tpg,
	.fabric_drop_tpg		= vhost_scsi_drop_tpg,
	.fabric_post_link		= vhost_scsi_port_link,
	.fabric_pre_unlink		= vhost_scsi_port_unlink,

	.tfc_wwn_attrs			= vhost_scsi_wwn_attrs,
	.tfc_tpg_base_attrs		= vhost_scsi_tpg_attrs,
	.tfc_tpg_attrib_attrs		= vhost_scsi_tpg_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init vhost_scsi_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	pr_debug("TCM_VHOST fabric module %s on %s/%s"
		" on "UTS_RELEASE"\n", VHOST_SCSI_VERSION, utsname()->sysname,
		utsname()->machine);

	ret = vhost_scsi_रेजिस्टर();
	अगर (ret < 0)
		जाओ out;

	ret = target_रेजिस्टर_ढाँचा(&vhost_scsi_ops);
	अगर (ret < 0)
		जाओ out_vhost_scsi_deरेजिस्टर;

	वापस 0;

out_vhost_scsi_deरेजिस्टर:
	vhost_scsi_deरेजिस्टर();
out:
	वापस ret;
पूर्ण;

अटल व्योम vhost_scsi_निकास(व्योम)
अणु
	target_unरेजिस्टर_ढाँचा(&vhost_scsi_ops);
	vhost_scsi_deरेजिस्टर();
पूर्ण;

MODULE_DESCRIPTION("VHOST_SCSI series fabric driver");
MODULE_ALIAS("tcm_vhost");
MODULE_LICENSE("GPL");
module_init(vhost_scsi_init);
module_निकास(vhost_scsi_निकास);
