<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio SCSI HBA driver
 *
 * Copyright IBM Corp. 2010
 * Copyright Red Hat, Inc. 2011
 *
 * Authors:
 *  Stefan Hajnoczi   <stefanha@linux.vnet.ibm.com>
 *  Paolo Bonzini   <pbonzini@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mempool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_scsi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/blk-mq-virtपन.स>

#समावेश "sd.h"

#घोषणा VIRTIO_SCSI_MEMPOOL_SZ 64
#घोषणा VIRTIO_SCSI_EVENT_LEN 8
#घोषणा VIRTIO_SCSI_VQ_BASE 2

/* Command queue element */
काष्ठा virtio_scsi_cmd अणु
	काष्ठा scsi_cmnd *sc;
	काष्ठा completion *comp;
	जोड़ अणु
		काष्ठा virtio_scsi_cmd_req       cmd;
		काष्ठा virtio_scsi_cmd_req_pi    cmd_pi;
		काष्ठा virtio_scsi_ctrl_पंचांगf_req  पंचांगf;
		काष्ठा virtio_scsi_ctrl_an_req   an;
	पूर्ण req;
	जोड़ अणु
		काष्ठा virtio_scsi_cmd_resp      cmd;
		काष्ठा virtio_scsi_ctrl_पंचांगf_resp पंचांगf;
		काष्ठा virtio_scsi_ctrl_an_resp  an;
		काष्ठा virtio_scsi_event         evt;
	पूर्ण resp;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा virtio_scsi_event_node अणु
	काष्ठा virtio_scsi *vscsi;
	काष्ठा virtio_scsi_event event;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा virtio_scsi_vq अणु
	/* Protects vq */
	spinlock_t vq_lock;

	काष्ठा virtqueue *vq;
पूर्ण;

/* Driver instance state */
काष्ठा virtio_scsi अणु
	काष्ठा virtio_device *vdev;

	/* Get some buffers पढ़ोy क्रम event vq */
	काष्ठा virtio_scsi_event_node event_list[VIRTIO_SCSI_EVENT_LEN];

	u32 num_queues;

	काष्ठा hlist_node node;

	/* Protected by event_vq lock */
	bool stop_events;

	काष्ठा virtio_scsi_vq ctrl_vq;
	काष्ठा virtio_scsi_vq event_vq;
	काष्ठा virtio_scsi_vq req_vqs[];
पूर्ण;

अटल काष्ठा kmem_cache *virtscsi_cmd_cache;
अटल mempool_t *virtscsi_cmd_pool;

अटल अंतरभूत काष्ठा Scsi_Host *virtio_scsi_host(काष्ठा virtio_device *vdev)
अणु
	वापस vdev->priv;
पूर्ण

अटल व्योम virtscsi_compute_resid(काष्ठा scsi_cmnd *sc, u32 resid)
अणु
	अगर (resid)
		scsi_set_resid(sc, resid);
पूर्ण

/*
 * virtscsi_complete_cmd - finish a scsi_cmd and invoke scsi_करोne
 *
 * Called with vq_lock held.
 */
अटल व्योम virtscsi_complete_cmd(काष्ठा virtio_scsi *vscsi, व्योम *buf)
अणु
	काष्ठा virtio_scsi_cmd *cmd = buf;
	काष्ठा scsi_cmnd *sc = cmd->sc;
	काष्ठा virtio_scsi_cmd_resp *resp = &cmd->resp.cmd;

	dev_dbg(&sc->device->sdev_gendev,
		"cmd %p response %u status %#02x sense_len %u\n",
		sc, resp->response, resp->status, resp->sense_len);

	sc->result = resp->status;
	virtscsi_compute_resid(sc, virtio32_to_cpu(vscsi->vdev, resp->resid));
	चयन (resp->response) अणु
	हाल VIRTIO_SCSI_S_OK:
		set_host_byte(sc, DID_OK);
		अवरोध;
	हाल VIRTIO_SCSI_S_OVERRUN:
		set_host_byte(sc, DID_ERROR);
		अवरोध;
	हाल VIRTIO_SCSI_S_ABORTED:
		set_host_byte(sc, DID_ABORT);
		अवरोध;
	हाल VIRTIO_SCSI_S_BAD_TARGET:
		set_host_byte(sc, DID_BAD_TARGET);
		अवरोध;
	हाल VIRTIO_SCSI_S_RESET:
		set_host_byte(sc, DID_RESET);
		अवरोध;
	हाल VIRTIO_SCSI_S_BUSY:
		set_host_byte(sc, DID_BUS_BUSY);
		अवरोध;
	हाल VIRTIO_SCSI_S_TRANSPORT_FAILURE:
		set_host_byte(sc, DID_TRANSPORT_DISRUPTED);
		अवरोध;
	हाल VIRTIO_SCSI_S_TARGET_FAILURE:
		set_host_byte(sc, DID_TARGET_FAILURE);
		अवरोध;
	हाल VIRTIO_SCSI_S_NEXUS_FAILURE:
		set_host_byte(sc, DID_NEXUS_FAILURE);
		अवरोध;
	शेष:
		scmd_prपूर्णांकk(KERN_WARNING, sc, "Unknown response %d",
			    resp->response);
		fallthrough;
	हाल VIRTIO_SCSI_S_FAILURE:
		set_host_byte(sc, DID_ERROR);
		अवरोध;
	पूर्ण

	WARN_ON(virtio32_to_cpu(vscsi->vdev, resp->sense_len) >
		VIRTIO_SCSI_SENSE_SIZE);
	अगर (sc->sense_buffer) अणु
		स_नकल(sc->sense_buffer, resp->sense,
		       min_t(u32,
			     virtio32_to_cpu(vscsi->vdev, resp->sense_len),
			     VIRTIO_SCSI_SENSE_SIZE));
		अगर (resp->sense_len)
			set_driver_byte(sc, DRIVER_SENSE);
	पूर्ण

	sc->scsi_करोne(sc);
पूर्ण

अटल व्योम virtscsi_vq_करोne(काष्ठा virtio_scsi *vscsi,
			     काष्ठा virtio_scsi_vq *virtscsi_vq,
			     व्योम (*fn)(काष्ठा virtio_scsi *vscsi, व्योम *buf))
अणु
	व्योम *buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ flags;
	काष्ठा virtqueue *vq = virtscsi_vq->vq;

	spin_lock_irqsave(&virtscsi_vq->vq_lock, flags);
	करो अणु
		virtqueue_disable_cb(vq);
		जबतक ((buf = virtqueue_get_buf(vq, &len)) != शून्य)
			fn(vscsi, buf);

		अगर (unlikely(virtqueue_is_broken(vq)))
			अवरोध;
	पूर्ण जबतक (!virtqueue_enable_cb(vq));
	spin_unlock_irqrestore(&virtscsi_vq->vq_lock, flags);
पूर्ण

अटल व्योम virtscsi_req_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा Scsi_Host *sh = virtio_scsi_host(vq->vdev);
	काष्ठा virtio_scsi *vscsi = shost_priv(sh);
	पूर्णांक index = vq->index - VIRTIO_SCSI_VQ_BASE;
	काष्ठा virtio_scsi_vq *req_vq = &vscsi->req_vqs[index];

	virtscsi_vq_करोne(vscsi, req_vq, virtscsi_complete_cmd);
पूर्ण;

अटल व्योम virtscsi_poll_requests(काष्ठा virtio_scsi *vscsi)
अणु
	पूर्णांक i, num_vqs;

	num_vqs = vscsi->num_queues;
	क्रम (i = 0; i < num_vqs; i++)
		virtscsi_vq_करोne(vscsi, &vscsi->req_vqs[i],
				 virtscsi_complete_cmd);
पूर्ण

अटल व्योम virtscsi_complete_मुक्त(काष्ठा virtio_scsi *vscsi, व्योम *buf)
अणु
	काष्ठा virtio_scsi_cmd *cmd = buf;

	अगर (cmd->comp)
		complete(cmd->comp);
पूर्ण

अटल व्योम virtscsi_ctrl_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा Scsi_Host *sh = virtio_scsi_host(vq->vdev);
	काष्ठा virtio_scsi *vscsi = shost_priv(sh);

	virtscsi_vq_करोne(vscsi, &vscsi->ctrl_vq, virtscsi_complete_मुक्त);
पूर्ण;

अटल व्योम virtscsi_handle_event(काष्ठा work_काष्ठा *work);

अटल पूर्णांक virtscsi_kick_event(काष्ठा virtio_scsi *vscsi,
			       काष्ठा virtio_scsi_event_node *event_node)
अणु
	पूर्णांक err;
	काष्ठा scatterlist sg;
	अचिन्हित दीर्घ flags;

	INIT_WORK(&event_node->work, virtscsi_handle_event);
	sg_init_one(&sg, &event_node->event, माप(काष्ठा virtio_scsi_event));

	spin_lock_irqsave(&vscsi->event_vq.vq_lock, flags);

	err = virtqueue_add_inbuf(vscsi->event_vq.vq, &sg, 1, event_node,
				  GFP_ATOMIC);
	अगर (!err)
		virtqueue_kick(vscsi->event_vq.vq);

	spin_unlock_irqrestore(&vscsi->event_vq.vq_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक virtscsi_kick_event_all(काष्ठा virtio_scsi *vscsi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VIRTIO_SCSI_EVENT_LEN; i++) अणु
		vscsi->event_list[i].vscsi = vscsi;
		virtscsi_kick_event(vscsi, &vscsi->event_list[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virtscsi_cancel_event_work(काष्ठा virtio_scsi *vscsi)
अणु
	पूर्णांक i;

	/* Stop scheduling work beक्रमe calling cancel_work_sync.  */
	spin_lock_irq(&vscsi->event_vq.vq_lock);
	vscsi->stop_events = true;
	spin_unlock_irq(&vscsi->event_vq.vq_lock);

	क्रम (i = 0; i < VIRTIO_SCSI_EVENT_LEN; i++)
		cancel_work_sync(&vscsi->event_list[i].work);
पूर्ण

अटल व्योम virtscsi_handle_transport_reset(काष्ठा virtio_scsi *vscsi,
					    काष्ठा virtio_scsi_event *event)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost = virtio_scsi_host(vscsi->vdev);
	अचिन्हित पूर्णांक target = event->lun[1];
	अचिन्हित पूर्णांक lun = (event->lun[2] << 8) | event->lun[3];

	चयन (virtio32_to_cpu(vscsi->vdev, event->reason)) अणु
	हाल VIRTIO_SCSI_EVT_RESET_RESCAN:
		अगर (lun == 0) अणु
			scsi_scan_target(&shost->shost_gendev, 0, target,
					 SCAN_WILD_CARD, SCSI_SCAN_INITIAL);
		पूर्ण अन्यथा अणु
			scsi_add_device(shost, 0, target, lun);
		पूर्ण
		अवरोध;
	हाल VIRTIO_SCSI_EVT_RESET_REMOVED:
		sdev = scsi_device_lookup(shost, 0, target, lun);
		अगर (sdev) अणु
			scsi_हटाओ_device(sdev);
			scsi_device_put(sdev);
		पूर्ण अन्यथा अणु
			pr_err("SCSI device %d 0 %d %d not found\n",
				shost->host_no, target, lun);
		पूर्ण
		अवरोध;
	शेष:
		pr_info("Unsupport virtio scsi event reason %x\n", event->reason);
	पूर्ण
पूर्ण

अटल व्योम virtscsi_handle_param_change(काष्ठा virtio_scsi *vscsi,
					 काष्ठा virtio_scsi_event *event)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost = virtio_scsi_host(vscsi->vdev);
	अचिन्हित पूर्णांक target = event->lun[1];
	अचिन्हित पूर्णांक lun = (event->lun[2] << 8) | event->lun[3];
	u8 asc = virtio32_to_cpu(vscsi->vdev, event->reason) & 255;
	u8 ascq = virtio32_to_cpu(vscsi->vdev, event->reason) >> 8;

	sdev = scsi_device_lookup(shost, 0, target, lun);
	अगर (!sdev) अणु
		pr_err("SCSI device %d 0 %d %d not found\n",
			shost->host_no, target, lun);
		वापस;
	पूर्ण

	/* Handle "Parameters changed", "Mode parameters changed", and
	   "Capacity data has changed".  */
	अगर (asc == 0x2a && (ascq == 0x00 || ascq == 0x01 || ascq == 0x09))
		scsi_rescan_device(&sdev->sdev_gendev);

	scsi_device_put(sdev);
पूर्ण

अटल व्योम virtscsi_rescan_hotunplug(काष्ठा virtio_scsi *vscsi)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost = virtio_scsi_host(vscsi->vdev);
	अचिन्हित अक्षर scsi_cmd[MAX_COMMAND_SIZE];
	पूर्णांक result, inquiry_len, inq_result_len = 256;
	अक्षर *inq_result = kदो_स्मृति(inq_result_len, GFP_KERNEL);

	shost_क्रम_each_device(sdev, shost) अणु
		inquiry_len = sdev->inquiry_len ? sdev->inquiry_len : 36;

		स_रखो(scsi_cmd, 0, माप(scsi_cmd));
		scsi_cmd[0] = INQUIRY;
		scsi_cmd[4] = (अचिन्हित अक्षर) inquiry_len;

		स_रखो(inq_result, 0, inq_result_len);

		result = scsi_execute_req(sdev, scsi_cmd, DMA_FROM_DEVICE,
					  inq_result, inquiry_len, शून्य,
					  SD_TIMEOUT, SD_MAX_RETRIES, शून्य);

		अगर (result == 0 && inq_result[0] >> 5) अणु
			/* PQ indicates the LUN is not attached */
			scsi_हटाओ_device(sdev);
		पूर्ण अन्यथा अगर (host_byte(result) == DID_BAD_TARGET) अणु
			/*
			 * If all LUNs of a virtio-scsi device are unplugged
			 * it will respond with BAD TARGET on any INQUIRY
			 * command.
			 * Remove the device in this हाल as well.
			 */
			scsi_हटाओ_device(sdev);
		पूर्ण
	पूर्ण

	kमुक्त(inq_result);
पूर्ण

अटल व्योम virtscsi_handle_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_scsi_event_node *event_node =
		container_of(work, काष्ठा virtio_scsi_event_node, work);
	काष्ठा virtio_scsi *vscsi = event_node->vscsi;
	काष्ठा virtio_scsi_event *event = &event_node->event;

	अगर (event->event &
	    cpu_to_virtio32(vscsi->vdev, VIRTIO_SCSI_T_EVENTS_MISSED)) अणु
		event->event &= ~cpu_to_virtio32(vscsi->vdev,
						   VIRTIO_SCSI_T_EVENTS_MISSED);
		virtscsi_rescan_hotunplug(vscsi);
		scsi_scan_host(virtio_scsi_host(vscsi->vdev));
	पूर्ण

	चयन (virtio32_to_cpu(vscsi->vdev, event->event)) अणु
	हाल VIRTIO_SCSI_T_NO_EVENT:
		अवरोध;
	हाल VIRTIO_SCSI_T_TRANSPORT_RESET:
		virtscsi_handle_transport_reset(vscsi, event);
		अवरोध;
	हाल VIRTIO_SCSI_T_PARAM_CHANGE:
		virtscsi_handle_param_change(vscsi, event);
		अवरोध;
	शेष:
		pr_err("Unsupport virtio scsi event %x\n", event->event);
	पूर्ण
	virtscsi_kick_event(vscsi, event_node);
पूर्ण

अटल व्योम virtscsi_complete_event(काष्ठा virtio_scsi *vscsi, व्योम *buf)
अणु
	काष्ठा virtio_scsi_event_node *event_node = buf;

	अगर (!vscsi->stop_events)
		queue_work(प्रणाली_मुक्तzable_wq, &event_node->work);
पूर्ण

अटल व्योम virtscsi_event_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा Scsi_Host *sh = virtio_scsi_host(vq->vdev);
	काष्ठा virtio_scsi *vscsi = shost_priv(sh);

	virtscsi_vq_करोne(vscsi, &vscsi->event_vq, virtscsi_complete_event);
पूर्ण;

अटल पूर्णांक __virtscsi_add_cmd(काष्ठा virtqueue *vq,
			    काष्ठा virtio_scsi_cmd *cmd,
			    माप_प्रकार req_size, माप_प्रकार resp_size)
अणु
	काष्ठा scsi_cmnd *sc = cmd->sc;
	काष्ठा scatterlist *sgs[6], req, resp;
	काष्ठा sg_table *out, *in;
	अचिन्हित out_num = 0, in_num = 0;

	out = in = शून्य;

	अगर (sc && sc->sc_data_direction != DMA_NONE) अणु
		अगर (sc->sc_data_direction != DMA_FROM_DEVICE)
			out = &sc->sdb.table;
		अगर (sc->sc_data_direction != DMA_TO_DEVICE)
			in = &sc->sdb.table;
	पूर्ण

	/* Request header.  */
	sg_init_one(&req, &cmd->req, req_size);
	sgs[out_num++] = &req;

	/* Data-out buffer.  */
	अगर (out) अणु
		/* Place WRITE protection SGLs beक्रमe Data OUT payload */
		अगर (scsi_prot_sg_count(sc))
			sgs[out_num++] = scsi_prot_sglist(sc);
		sgs[out_num++] = out->sgl;
	पूर्ण

	/* Response header.  */
	sg_init_one(&resp, &cmd->resp, resp_size);
	sgs[out_num + in_num++] = &resp;

	/* Data-in buffer */
	अगर (in) अणु
		/* Place READ protection SGLs beक्रमe Data IN payload */
		अगर (scsi_prot_sg_count(sc))
			sgs[out_num + in_num++] = scsi_prot_sglist(sc);
		sgs[out_num + in_num++] = in->sgl;
	पूर्ण

	वापस virtqueue_add_sgs(vq, sgs, out_num, in_num, cmd, GFP_ATOMIC);
पूर्ण

अटल व्योम virtscsi_kick_vq(काष्ठा virtio_scsi_vq *vq)
अणु
	bool needs_kick;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vq->vq_lock, flags);
	needs_kick = virtqueue_kick_prepare(vq->vq);
	spin_unlock_irqrestore(&vq->vq_lock, flags);

	अगर (needs_kick)
		virtqueue_notअगरy(vq->vq);
पूर्ण

/**
 * virtscsi_add_cmd - add a virtio_scsi_cmd to a virtqueue, optionally kick it
 * @vq		: the काष्ठा virtqueue we're talking about
 * @cmd		: command काष्ठाure
 * @req_size	: size of the request buffer
 * @resp_size	: size of the response buffer
 * @kick	: whether to kick the virtqueue immediately
 */
अटल पूर्णांक virtscsi_add_cmd(काष्ठा virtio_scsi_vq *vq,
			     काष्ठा virtio_scsi_cmd *cmd,
			     माप_प्रकार req_size, माप_प्रकार resp_size,
			     bool kick)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	bool needs_kick = false;

	spin_lock_irqsave(&vq->vq_lock, flags);
	err = __virtscsi_add_cmd(vq->vq, cmd, req_size, resp_size);
	अगर (!err && kick)
		needs_kick = virtqueue_kick_prepare(vq->vq);

	spin_unlock_irqrestore(&vq->vq_lock, flags);

	अगर (needs_kick)
		virtqueue_notअगरy(vq->vq);
	वापस err;
पूर्ण

अटल व्योम virtio_scsi_init_hdr(काष्ठा virtio_device *vdev,
				 काष्ठा virtio_scsi_cmd_req *cmd,
				 काष्ठा scsi_cmnd *sc)
अणु
	cmd->lun[0] = 1;
	cmd->lun[1] = sc->device->id;
	cmd->lun[2] = (sc->device->lun >> 8) | 0x40;
	cmd->lun[3] = sc->device->lun & 0xff;
	cmd->tag = cpu_to_virtio64(vdev, (अचिन्हित दीर्घ)sc);
	cmd->task_attr = VIRTIO_SCSI_S_SIMPLE;
	cmd->prio = 0;
	cmd->crn = 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल व्योम virtio_scsi_init_hdr_pi(काष्ठा virtio_device *vdev,
				    काष्ठा virtio_scsi_cmd_req_pi *cmd_pi,
				    काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा request *rq = sc->request;
	काष्ठा blk_पूर्णांकegrity *bi;

	virtio_scsi_init_hdr(vdev, (काष्ठा virtio_scsi_cmd_req *)cmd_pi, sc);

	अगर (!rq || !scsi_prot_sg_count(sc))
		वापस;

	bi = blk_get_पूर्णांकegrity(rq->rq_disk);

	अगर (sc->sc_data_direction == DMA_TO_DEVICE)
		cmd_pi->pi_bytesout = cpu_to_virtio32(vdev,
						      bio_पूर्णांकegrity_bytes(bi,
							blk_rq_sectors(rq)));
	अन्यथा अगर (sc->sc_data_direction == DMA_FROM_DEVICE)
		cmd_pi->pi_bytesin = cpu_to_virtio32(vdev,
						     bio_पूर्णांकegrity_bytes(bi,
							blk_rq_sectors(rq)));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा virtio_scsi_vq *virtscsi_pick_vq_mq(काष्ठा virtio_scsi *vscsi,
						  काष्ठा scsi_cmnd *sc)
अणु
	u32 tag = blk_mq_unique_tag(sc->request);
	u16 hwq = blk_mq_unique_tag_to_hwq(tag);

	वापस &vscsi->req_vqs[hwq];
पूर्ण

अटल पूर्णांक virtscsi_queuecommand(काष्ठा Scsi_Host *shost,
				 काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा virtio_scsi *vscsi = shost_priv(shost);
	काष्ठा virtio_scsi_vq *req_vq = virtscsi_pick_vq_mq(vscsi, sc);
	काष्ठा virtio_scsi_cmd *cmd = scsi_cmd_priv(sc);
	bool kick;
	अचिन्हित दीर्घ flags;
	पूर्णांक req_size;
	पूर्णांक ret;

	BUG_ON(scsi_sg_count(sc) > shost->sg_tablesize);

	/* TODO: check feature bit and fail अगर unsupported?  */
	BUG_ON(sc->sc_data_direction == DMA_BIसूचीECTIONAL);

	dev_dbg(&sc->device->sdev_gendev,
		"cmd %p CDB: %#02x\n", sc, sc->cmnd[0]);

	cmd->sc = sc;

	BUG_ON(sc->cmd_len > VIRTIO_SCSI_CDB_SIZE);

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	अगर (virtio_has_feature(vscsi->vdev, VIRTIO_SCSI_F_T10_PI)) अणु
		virtio_scsi_init_hdr_pi(vscsi->vdev, &cmd->req.cmd_pi, sc);
		स_नकल(cmd->req.cmd_pi.cdb, sc->cmnd, sc->cmd_len);
		req_size = माप(cmd->req.cmd_pi);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		virtio_scsi_init_hdr(vscsi->vdev, &cmd->req.cmd, sc);
		स_नकल(cmd->req.cmd.cdb, sc->cmnd, sc->cmd_len);
		req_size = माप(cmd->req.cmd);
	पूर्ण

	kick = (sc->flags & SCMD_LAST) != 0;
	ret = virtscsi_add_cmd(req_vq, cmd, req_size, माप(cmd->resp.cmd), kick);
	अगर (ret == -EIO) अणु
		cmd->resp.cmd.response = VIRTIO_SCSI_S_BAD_TARGET;
		spin_lock_irqsave(&req_vq->vq_lock, flags);
		virtscsi_complete_cmd(vscsi, cmd);
		spin_unlock_irqrestore(&req_vq->vq_lock, flags);
	पूर्ण अन्यथा अगर (ret != 0) अणु
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक virtscsi_पंचांगf(काष्ठा virtio_scsi *vscsi, काष्ठा virtio_scsi_cmd *cmd)
अणु
	DECLARE_COMPLETION_ONSTACK(comp);
	पूर्णांक ret = FAILED;

	cmd->comp = &comp;
	अगर (virtscsi_add_cmd(&vscsi->ctrl_vq, cmd,
			      माप cmd->req.पंचांगf, माप cmd->resp.पंचांगf, true) < 0)
		जाओ out;

	रुको_क्रम_completion(&comp);
	अगर (cmd->resp.पंचांगf.response == VIRTIO_SCSI_S_OK ||
	    cmd->resp.पंचांगf.response == VIRTIO_SCSI_S_FUNCTION_SUCCEEDED)
		ret = SUCCESS;

	/*
	 * The spec guarantees that all requests related to the TMF have
	 * been completed, but the callback might not have run yet अगर
	 * we're using independent पूर्णांकerrupts (e.g. MSI).  Poll the
	 * virtqueues once.
	 *
	 * In the पात हाल, sc->scsi_करोne will करो nothing, because
	 * the block layer must have detected a समयout and as a result
	 * REQ_ATOM_COMPLETE has been set.
	 */
	virtscsi_poll_requests(vscsi);

out:
	mempool_मुक्त(cmd, virtscsi_cmd_pool);
	वापस ret;
पूर्ण

अटल पूर्णांक virtscsi_device_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा virtio_scsi *vscsi = shost_priv(sc->device->host);
	काष्ठा virtio_scsi_cmd *cmd;

	sdev_prपूर्णांकk(KERN_INFO, sc->device, "device reset\n");
	cmd = mempool_alloc(virtscsi_cmd_pool, GFP_NOIO);
	अगर (!cmd)
		वापस FAILED;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->req.पंचांगf = (काष्ठा virtio_scsi_ctrl_पंचांगf_req)अणु
		.type = VIRTIO_SCSI_T_TMF,
		.subtype = cpu_to_virtio32(vscsi->vdev,
					     VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET),
		.lun[0] = 1,
		.lun[1] = sc->device->id,
		.lun[2] = (sc->device->lun >> 8) | 0x40,
		.lun[3] = sc->device->lun & 0xff,
	पूर्ण;
	वापस virtscsi_पंचांगf(vscsi, cmd);
पूर्ण

अटल पूर्णांक virtscsi_device_alloc(काष्ठा scsi_device *sdevice)
अणु
	/*
	 * Passed through SCSI tarमाला_लो (e.g. with qemu's 'scsi-block')
	 * may have transfer limits which come from the host SCSI
	 * controller or something on the host side other than the
	 * target itself.
	 *
	 * To make this work properly, the hypervisor can adjust the
	 * target's VPD inक्रमmation to advertise these limits.  But
	 * क्रम that to work, the guest has to look at the VPD pages,
	 * which we won't करो by शेष अगर it is an SPC-2 device, even
	 * अगर it करोes actually support it.
	 *
	 * So, set the blist to always try to पढ़ो the VPD pages.
	 */
	sdevice->sdev_bflags = BLIST_TRY_VPD_PAGES;

	वापस 0;
पूर्ण


/**
 * virtscsi_change_queue_depth() - Change a virtscsi target's queue depth
 * @sdev:	Virtscsi target whose queue depth to change
 * @qdepth:	New queue depth
 */
अटल पूर्णांक virtscsi_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	पूर्णांक max_depth = shost->cmd_per_lun;

	वापस scsi_change_queue_depth(sdev, min(max_depth, qdepth));
पूर्ण

अटल पूर्णांक virtscsi_पात(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा virtio_scsi *vscsi = shost_priv(sc->device->host);
	काष्ठा virtio_scsi_cmd *cmd;

	scmd_prपूर्णांकk(KERN_INFO, sc, "abort\n");
	cmd = mempool_alloc(virtscsi_cmd_pool, GFP_NOIO);
	अगर (!cmd)
		वापस FAILED;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->req.पंचांगf = (काष्ठा virtio_scsi_ctrl_पंचांगf_req)अणु
		.type = VIRTIO_SCSI_T_TMF,
		.subtype = VIRTIO_SCSI_T_TMF_ABORT_TASK,
		.lun[0] = 1,
		.lun[1] = sc->device->id,
		.lun[2] = (sc->device->lun >> 8) | 0x40,
		.lun[3] = sc->device->lun & 0xff,
		.tag = cpu_to_virtio64(vscsi->vdev, (अचिन्हित दीर्घ)sc),
	पूर्ण;
	वापस virtscsi_पंचांगf(vscsi, cmd);
पूर्ण

अटल पूर्णांक virtscsi_map_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा virtio_scsi *vscsi = shost_priv(shost);
	काष्ठा blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];

	वापस blk_mq_virtio_map_queues(qmap, vscsi->vdev, 2);
पूर्ण

अटल व्योम virtscsi_commit_rqs(काष्ठा Scsi_Host *shost, u16 hwq)
अणु
	काष्ठा virtio_scsi *vscsi = shost_priv(shost);

	virtscsi_kick_vq(&vscsi->req_vqs[hwq]);
पूर्ण

/*
 * The host guarantees to respond to each command, although I/O
 * latencies might be higher than on bare metal.  Reset the समयr
 * unconditionally to give the host a chance to perक्रमm EH.
 */
अटल क्रमागत blk_eh_समयr_वापस virtscsi_eh_समयd_out(काष्ठा scsi_cmnd *scmnd)
अणु
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा virtscsi_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "Virtio SCSI HBA",
	.proc_name = "virtio_scsi",
	.this_id = -1,
	.cmd_size = माप(काष्ठा virtio_scsi_cmd),
	.queuecommand = virtscsi_queuecommand,
	.commit_rqs = virtscsi_commit_rqs,
	.change_queue_depth = virtscsi_change_queue_depth,
	.eh_पात_handler = virtscsi_पात,
	.eh_device_reset_handler = virtscsi_device_reset,
	.eh_समयd_out = virtscsi_eh_समयd_out,
	.slave_alloc = virtscsi_device_alloc,

	.dma_boundary = अच_पूर्णांक_उच्च,
	.map_queues = virtscsi_map_queues,
	.track_queue_depth = 1,
पूर्ण;

#घोषणा virtscsi_config_get(vdev, fld) \
	(अणु \
		__virtio_native_type(काष्ठा virtio_scsi_config, fld) __val; \
		virtio_cपढ़ो(vdev, काष्ठा virtio_scsi_config, fld, &__val); \
		__val; \
	पूर्ण)

#घोषणा virtscsi_config_set(vdev, fld, val) \
	करो अणु \
		__virtio_native_type(काष्ठा virtio_scsi_config, fld) __val = (val); \
		virtio_cग_लिखो(vdev, काष्ठा virtio_scsi_config, fld, &__val); \
	पूर्ण जबतक(0)

अटल व्योम virtscsi_init_vq(काष्ठा virtio_scsi_vq *virtscsi_vq,
			     काष्ठा virtqueue *vq)
अणु
	spin_lock_init(&virtscsi_vq->vq_lock);
	virtscsi_vq->vq = vq;
पूर्ण

अटल व्योम virtscsi_हटाओ_vqs(काष्ठा virtio_device *vdev)
अणु
	/* Stop all the virtqueues. */
	vdev->config->reset(vdev);
	vdev->config->del_vqs(vdev);
पूर्ण

अटल पूर्णांक virtscsi_init(काष्ठा virtio_device *vdev,
			 काष्ठा virtio_scsi *vscsi)
अणु
	पूर्णांक err;
	u32 i;
	u32 num_vqs;
	vq_callback_t **callbacks;
	स्थिर अक्षर **names;
	काष्ठा virtqueue **vqs;
	काष्ठा irq_affinity desc = अणु .pre_vectors = 2 पूर्ण;

	num_vqs = vscsi->num_queues + VIRTIO_SCSI_VQ_BASE;
	vqs = kदो_स्मृति_array(num_vqs, माप(काष्ठा virtqueue *), GFP_KERNEL);
	callbacks = kदो_स्मृति_array(num_vqs, माप(vq_callback_t *),
				  GFP_KERNEL);
	names = kदो_स्मृति_array(num_vqs, माप(अक्षर *), GFP_KERNEL);

	अगर (!callbacks || !vqs || !names) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	callbacks[0] = virtscsi_ctrl_करोne;
	callbacks[1] = virtscsi_event_करोne;
	names[0] = "control";
	names[1] = "event";
	क्रम (i = VIRTIO_SCSI_VQ_BASE; i < num_vqs; i++) अणु
		callbacks[i] = virtscsi_req_करोne;
		names[i] = "request";
	पूर्ण

	/* Discover virtqueues and ग_लिखो inक्रमmation to configuration.  */
	err = virtio_find_vqs(vdev, num_vqs, vqs, callbacks, names, &desc);
	अगर (err)
		जाओ out;

	virtscsi_init_vq(&vscsi->ctrl_vq, vqs[0]);
	virtscsi_init_vq(&vscsi->event_vq, vqs[1]);
	क्रम (i = VIRTIO_SCSI_VQ_BASE; i < num_vqs; i++)
		virtscsi_init_vq(&vscsi->req_vqs[i - VIRTIO_SCSI_VQ_BASE],
				 vqs[i]);

	virtscsi_config_set(vdev, cdb_size, VIRTIO_SCSI_CDB_SIZE);
	virtscsi_config_set(vdev, sense_size, VIRTIO_SCSI_SENSE_SIZE);

	err = 0;

out:
	kमुक्त(names);
	kमुक्त(callbacks);
	kमुक्त(vqs);
	अगर (err)
		virtscsi_हटाओ_vqs(vdev);
	वापस err;
पूर्ण

अटल पूर्णांक virtscsi_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा virtio_scsi *vscsi;
	पूर्णांक err;
	u32 sg_elems, num_tarमाला_लो;
	u32 cmd_per_lun;
	u32 num_queues;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* We need to know how many queues beक्रमe we allocate. */
	num_queues = virtscsi_config_get(vdev, num_queues) ? : 1;
	num_queues = min_t(अचिन्हित पूर्णांक, nr_cpu_ids, num_queues);

	num_tarमाला_लो = virtscsi_config_get(vdev, max_target) + 1;

	shost = scsi_host_alloc(&virtscsi_host_ढाँचा,
				काष्ठा_size(vscsi, req_vqs, num_queues));
	अगर (!shost)
		वापस -ENOMEM;

	sg_elems = virtscsi_config_get(vdev, seg_max) ?: 1;
	shost->sg_tablesize = sg_elems;
	vscsi = shost_priv(shost);
	vscsi->vdev = vdev;
	vscsi->num_queues = num_queues;
	vdev->priv = shost;

	err = virtscsi_init(vdev, vscsi);
	अगर (err)
		जाओ virtscsi_init_failed;

	shost->can_queue = virtqueue_get_vring_size(vscsi->req_vqs[0].vq);

	cmd_per_lun = virtscsi_config_get(vdev, cmd_per_lun) ?: 1;
	shost->cmd_per_lun = min_t(u32, cmd_per_lun, shost->can_queue);
	shost->max_sectors = virtscsi_config_get(vdev, max_sectors) ?: 0xFFFF;

	/* LUNs > 256 are reported with क्रमmat 1, so they go in the range
	 * 16640-32767.
	 */
	shost->max_lun = virtscsi_config_get(vdev, max_lun) + 1 + 0x4000;
	shost->max_id = num_tarमाला_लो;
	shost->max_channel = 0;
	shost->max_cmd_len = VIRTIO_SCSI_CDB_SIZE;
	shost->nr_hw_queues = num_queues;

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	अगर (virtio_has_feature(vdev, VIRTIO_SCSI_F_T10_PI)) अणु
		पूर्णांक host_prot;

		host_prot = SHOST_DIF_TYPE1_PROTECTION | SHOST_DIF_TYPE2_PROTECTION |
			    SHOST_DIF_TYPE3_PROTECTION | SHOST_DIX_TYPE1_PROTECTION |
			    SHOST_DIX_TYPE2_PROTECTION | SHOST_DIX_TYPE3_PROTECTION;

		scsi_host_set_prot(shost, host_prot);
		scsi_host_set_guard(shost, SHOST_DIX_GUARD_CRC);
	पूर्ण
#पूर्ण_अगर

	err = scsi_add_host(shost, &vdev->dev);
	अगर (err)
		जाओ scsi_add_host_failed;

	virtio_device_पढ़ोy(vdev);

	अगर (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_kick_event_all(vscsi);

	scsi_scan_host(shost);
	वापस 0;

scsi_add_host_failed:
	vdev->config->del_vqs(vdev);
virtscsi_init_failed:
	scsi_host_put(shost);
	वापस err;
पूर्ण

अटल व्योम virtscsi_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा Scsi_Host *shost = virtio_scsi_host(vdev);
	काष्ठा virtio_scsi *vscsi = shost_priv(shost);

	अगर (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_cancel_event_work(vscsi);

	scsi_हटाओ_host(shost);
	virtscsi_हटाओ_vqs(vdev);
	scsi_host_put(shost);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtscsi_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	virtscsi_हटाओ_vqs(vdev);
	वापस 0;
पूर्ण

अटल पूर्णांक virtscsi_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा Scsi_Host *sh = virtio_scsi_host(vdev);
	काष्ठा virtio_scsi *vscsi = shost_priv(sh);
	पूर्णांक err;

	err = virtscsi_init(vdev, vscsi);
	अगर (err)
		वापस err;

	virtio_device_पढ़ोy(vdev);

	अगर (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_kick_event_all(vscsi);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_SCSI, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_SCSI_F_HOTPLUG,
	VIRTIO_SCSI_F_CHANGE,
#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	VIRTIO_SCSI_F_T10_PI,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा virtio_driver virtio_scsi_driver = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = id_table,
	.probe = virtscsi_probe,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze = virtscsi_मुक्तze,
	.restore = virtscsi_restore,
#पूर्ण_अगर
	.हटाओ = virtscsi_हटाओ,
पूर्ण;

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	virtscsi_cmd_cache = KMEM_CACHE(virtio_scsi_cmd, 0);
	अगर (!virtscsi_cmd_cache) अणु
		pr_err("kmem_cache_create() for virtscsi_cmd_cache failed\n");
		जाओ error;
	पूर्ण


	virtscsi_cmd_pool =
		mempool_create_slab_pool(VIRTIO_SCSI_MEMPOOL_SZ,
					 virtscsi_cmd_cache);
	अगर (!virtscsi_cmd_pool) अणु
		pr_err("mempool_create() for virtscsi_cmd_pool failed\n");
		जाओ error;
	पूर्ण
	ret = रेजिस्टर_virtio_driver(&virtio_scsi_driver);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	mempool_destroy(virtscsi_cmd_pool);
	virtscsi_cmd_pool = शून्य;
	kmem_cache_destroy(virtscsi_cmd_cache);
	virtscsi_cmd_cache = शून्य;
	वापस ret;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_scsi_driver);
	mempool_destroy(virtscsi_cmd_pool);
	kmem_cache_destroy(virtscsi_cmd_cache);
पूर्ण
module_init(init);
module_निकास(fini);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio SCSI HBA driver");
MODULE_LICENSE("GPL");
