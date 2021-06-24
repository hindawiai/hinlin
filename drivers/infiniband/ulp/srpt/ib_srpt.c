<शैली गुरु>
/*
 * Copyright (c) 2006 - 2009 Mellanox Technology Inc.  All rights reserved.
 * Copyright (C) 2008 - 2011 Bart Van Assche <bvanassche@acm.org>.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/inet.h>
#समावेश <rdma/ib_cache.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश "ib_srpt.h"

/* Name of this kernel module. */
#घोषणा DRV_NAME		"ib_srpt"

#घोषणा SRPT_ID_STRING	"Linux SRP target"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) DRV_NAME " " fmt

MODULE_AUTHOR("Vu Pham and Bart Van Assche");
MODULE_DESCRIPTION("SCSI RDMA Protocol target driver");
MODULE_LICENSE("Dual BSD/GPL");

/*
 * Global Variables
 */

अटल u64 srpt_service_guid;
अटल DEFINE_SPINLOCK(srpt_dev_lock);	/* Protects srpt_dev_list. */
अटल LIST_HEAD(srpt_dev_list);	/* List of srpt_device काष्ठाures. */

अटल अचिन्हित srp_max_req_size = DEFAULT_MAX_REQ_SIZE;
module_param(srp_max_req_size, पूर्णांक, 0444);
MODULE_PARM_DESC(srp_max_req_size,
		 "Maximum size of SRP request messages in bytes.");

अटल पूर्णांक srpt_srq_size = DEFAULT_SRPT_SRQ_SIZE;
module_param(srpt_srq_size, पूर्णांक, 0444);
MODULE_PARM_DESC(srpt_srq_size,
		 "Shared receive queue (SRQ) size.");

अटल पूर्णांक srpt_get_u64_x(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "0x%016llx\n", *(u64 *)kp->arg);
पूर्ण
module_param_call(srpt_service_guid, शून्य, srpt_get_u64_x, &srpt_service_guid,
		  0444);
MODULE_PARM_DESC(srpt_service_guid,
		 "Using this value for ioc_guid, id_ext, and cm_listen_id instead of using the node_guid of the first HCA.");

अटल काष्ठा ib_client srpt_client;
/* Protects both rdma_cm_port and rdma_cm_id. */
अटल DEFINE_MUTEX(rdma_cm_mutex);
/* Port number RDMA/CM will bind to. */
अटल u16 rdma_cm_port;
अटल काष्ठा rdma_cm_id *rdma_cm_id;
अटल व्योम srpt_release_cmd(काष्ठा se_cmd *se_cmd);
अटल व्योम srpt_मुक्त_ch(काष्ठा kref *kref);
अटल पूर्णांक srpt_queue_status(काष्ठा se_cmd *cmd);
अटल व्योम srpt_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम srpt_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम srpt_process_रुको_list(काष्ठा srpt_rdma_ch *ch);

/*
 * The only allowed channel state changes are those that change the channel
 * state पूर्णांकo a state with a higher numerical value. Hence the new > prev test.
 */
अटल bool srpt_set_ch_state(काष्ठा srpt_rdma_ch *ch, क्रमागत rdma_ch_state new)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत rdma_ch_state prev;
	bool changed = false;

	spin_lock_irqsave(&ch->spinlock, flags);
	prev = ch->state;
	अगर (new > prev) अणु
		ch->state = new;
		changed = true;
	पूर्ण
	spin_unlock_irqrestore(&ch->spinlock, flags);

	वापस changed;
पूर्ण

/**
 * srpt_event_handler - asynchronous IB event callback function
 * @handler: IB event handler रेजिस्टरed by ib_रेजिस्टर_event_handler().
 * @event: Description of the event that occurred.
 *
 * Callback function called by the InfiniBand core when an asynchronous IB
 * event occurs. This callback may occur in पूर्णांकerrupt context. See also
 * section 11.5.2, Set Asynchronous Event Handler in the InfiniBand
 * Architecture Specअगरication.
 */
अटल व्योम srpt_event_handler(काष्ठा ib_event_handler *handler,
			       काष्ठा ib_event *event)
अणु
	काष्ठा srpt_device *sdev =
		container_of(handler, काष्ठा srpt_device, event_handler);
	काष्ठा srpt_port *sport;
	u8 port_num;

	pr_debug("ASYNC event= %d on device= %s\n", event->event,
		 dev_name(&sdev->device->dev));

	चयन (event->event) अणु
	हाल IB_EVENT_PORT_ERR:
		port_num = event->element.port_num - 1;
		अगर (port_num < sdev->device->phys_port_cnt) अणु
			sport = &sdev->port[port_num];
			sport->lid = 0;
			sport->sm_lid = 0;
		पूर्ण अन्यथा अणु
			WARN(true, "event %d: port_num %d out of range 1..%d\n",
			     event->event, port_num + 1,
			     sdev->device->phys_port_cnt);
		पूर्ण
		अवरोध;
	हाल IB_EVENT_PORT_ACTIVE:
	हाल IB_EVENT_LID_CHANGE:
	हाल IB_EVENT_PKEY_CHANGE:
	हाल IB_EVENT_SM_CHANGE:
	हाल IB_EVENT_CLIENT_REREGISTER:
	हाल IB_EVENT_GID_CHANGE:
		/* Refresh port data asynchronously. */
		port_num = event->element.port_num - 1;
		अगर (port_num < sdev->device->phys_port_cnt) अणु
			sport = &sdev->port[port_num];
			अगर (!sport->lid && !sport->sm_lid)
				schedule_work(&sport->work);
		पूर्ण अन्यथा अणु
			WARN(true, "event %d: port_num %d out of range 1..%d\n",
			     event->event, port_num + 1,
			     sdev->device->phys_port_cnt);
		पूर्ण
		अवरोध;
	शेष:
		pr_err("received unrecognized IB event %d\n", event->event);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * srpt_srq_event - SRQ event callback function
 * @event: Description of the event that occurred.
 * @ctx: Context poपूर्णांकer specअगरied at SRQ creation समय.
 */
अटल व्योम srpt_srq_event(काष्ठा ib_event *event, व्योम *ctx)
अणु
	pr_debug("SRQ event %d\n", event->event);
पूर्ण

अटल स्थिर अक्षर *get_ch_state_name(क्रमागत rdma_ch_state s)
अणु
	चयन (s) अणु
	हाल CH_CONNECTING:
		वापस "connecting";
	हाल CH_LIVE:
		वापस "live";
	हाल CH_DISCONNECTING:
		वापस "disconnecting";
	हाल CH_DRAINING:
		वापस "draining";
	हाल CH_DISCONNECTED:
		वापस "disconnected";
	पूर्ण
	वापस "???";
पूर्ण

/**
 * srpt_qp_event - QP event callback function
 * @event: Description of the event that occurred.
 * @ch: SRPT RDMA channel.
 */
अटल व्योम srpt_qp_event(काष्ठा ib_event *event, काष्ठा srpt_rdma_ch *ch)
अणु
	pr_debug("QP event %d on ch=%p sess_name=%s-%d state=%s\n",
		 event->event, ch, ch->sess_name, ch->qp->qp_num,
		 get_ch_state_name(ch->state));

	चयन (event->event) अणु
	हाल IB_EVENT_COMM_EST:
		अगर (ch->using_rdma_cm)
			rdma_notअगरy(ch->rdma_cm.cm_id, event->event);
		अन्यथा
			ib_cm_notअगरy(ch->ib_cm.cm_id, event->event);
		अवरोध;
	हाल IB_EVENT_QP_LAST_WQE_REACHED:
		pr_debug("%s-%d, state %s: received Last WQE event.\n",
			 ch->sess_name, ch->qp->qp_num,
			 get_ch_state_name(ch->state));
		अवरोध;
	शेष:
		pr_err("received unrecognized IB QP event %d\n", event->event);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * srpt_set_ioc - initialize a IOUnitInfo काष्ठाure
 * @c_list: controller list.
 * @slot: one-based slot number.
 * @value: four-bit value.
 *
 * Copies the lowest four bits of value in element slot of the array of four
 * bit elements called c_list (controller list). The index slot is one-based.
 */
अटल व्योम srpt_set_ioc(u8 *c_list, u32 slot, u8 value)
अणु
	u16 id;
	u8 पंचांगp;

	id = (slot - 1) / 2;
	अगर (slot & 0x1) अणु
		पंचांगp = c_list[id] & 0xf;
		c_list[id] = (value << 4) | पंचांगp;
	पूर्ण अन्यथा अणु
		पंचांगp = c_list[id] & 0xf0;
		c_list[id] = (value & 0xf) | पंचांगp;
	पूर्ण
पूर्ण

/**
 * srpt_get_class_port_info - copy ClassPortInfo to a management datagram
 * @mad: Datagram that will be sent as response to DM_ATTR_CLASS_PORT_INFO.
 *
 * See also section 16.3.3.1 ClassPortInfo in the InfiniBand Architecture
 * Specअगरication.
 */
अटल व्योम srpt_get_class_port_info(काष्ठा ib_dm_mad *mad)
अणु
	काष्ठा ib_class_port_info *cअगर;

	cअगर = (काष्ठा ib_class_port_info *)mad->data;
	स_रखो(cअगर, 0, माप(*cअगर));
	cअगर->base_version = 1;
	cअगर->class_version = 1;

	ib_set_cpi_resp_समय(cअगर, 20);
	mad->mad_hdr.status = 0;
पूर्ण

/**
 * srpt_get_iou - ग_लिखो IOUnitInfo to a management datagram
 * @mad: Datagram that will be sent as response to DM_ATTR_IOU_INFO.
 *
 * See also section 16.3.3.3 IOUnitInfo in the InfiniBand Architecture
 * Specअगरication. See also section B.7, table B.6 in the SRP r16a करोcument.
 */
अटल व्योम srpt_get_iou(काष्ठा ib_dm_mad *mad)
अणु
	काष्ठा ib_dm_iou_info *ioui;
	u8 slot;
	पूर्णांक i;

	ioui = (काष्ठा ib_dm_iou_info *)mad->data;
	ioui->change_id = cpu_to_be16(1);
	ioui->max_controllers = 16;

	/* set present क्रम slot 1 and empty क्रम the rest */
	srpt_set_ioc(ioui->controller_list, 1, 1);
	क्रम (i = 1, slot = 2; i < 16; i++, slot++)
		srpt_set_ioc(ioui->controller_list, slot, 0);

	mad->mad_hdr.status = 0;
पूर्ण

/**
 * srpt_get_ioc - ग_लिखो IOControllerprofile to a management datagram
 * @sport: HCA port through which the MAD has been received.
 * @slot: Slot number specअगरied in DM_ATTR_IOC_PROखाता query.
 * @mad: Datagram that will be sent as response to DM_ATTR_IOC_PROखाता.
 *
 * See also section 16.3.3.4 IOControllerProfile in the InfiniBand
 * Architecture Specअगरication. See also section B.7, table B.7 in the SRP
 * r16a करोcument.
 */
अटल व्योम srpt_get_ioc(काष्ठा srpt_port *sport, u32 slot,
			 काष्ठा ib_dm_mad *mad)
अणु
	काष्ठा srpt_device *sdev = sport->sdev;
	काष्ठा ib_dm_ioc_profile *iocp;
	पूर्णांक send_queue_depth;

	iocp = (काष्ठा ib_dm_ioc_profile *)mad->data;

	अगर (!slot || slot > 16) अणु
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_INVALID_FIELD);
		वापस;
	पूर्ण

	अगर (slot > 2) अणु
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		वापस;
	पूर्ण

	अगर (sdev->use_srq)
		send_queue_depth = sdev->srq_size;
	अन्यथा
		send_queue_depth = min(MAX_SRPT_RQ_SIZE,
				       sdev->device->attrs.max_qp_wr);

	स_रखो(iocp, 0, माप(*iocp));
	म_नकल(iocp->id_string, SRPT_ID_STRING);
	iocp->guid = cpu_to_be64(srpt_service_guid);
	iocp->venकरोr_id = cpu_to_be32(sdev->device->attrs.venकरोr_id);
	iocp->device_id = cpu_to_be32(sdev->device->attrs.venकरोr_part_id);
	iocp->device_version = cpu_to_be16(sdev->device->attrs.hw_ver);
	iocp->subsys_venकरोr_id = cpu_to_be32(sdev->device->attrs.venकरोr_id);
	iocp->subsys_device_id = 0x0;
	iocp->io_class = cpu_to_be16(SRP_REV16A_IB_IO_CLASS);
	iocp->io_subclass = cpu_to_be16(SRP_IO_SUBCLASS);
	iocp->protocol = cpu_to_be16(SRP_PROTOCOL);
	iocp->protocol_version = cpu_to_be16(SRP_PROTOCOL_VERSION);
	iocp->send_queue_depth = cpu_to_be16(send_queue_depth);
	iocp->rdma_पढ़ो_depth = 4;
	iocp->send_size = cpu_to_be32(srp_max_req_size);
	iocp->rdma_size = cpu_to_be32(min(sport->port_attrib.srp_max_rdma_size,
					  1U << 24));
	iocp->num_svc_entries = 1;
	iocp->op_cap_mask = SRP_SEND_TO_IOC | SRP_SEND_FROM_IOC |
		SRP_RDMA_READ_FROM_IOC | SRP_RDMA_WRITE_FROM_IOC;

	mad->mad_hdr.status = 0;
पूर्ण

/**
 * srpt_get_svc_entries - ग_लिखो ServiceEntries to a management datagram
 * @ioc_guid: I/O controller GUID to use in reply.
 * @slot: I/O controller number.
 * @hi: End of the range of service entries to be specअगरied in the reply.
 * @lo: Start of the range of service entries to be specअगरied in the reply..
 * @mad: Datagram that will be sent as response to DM_ATTR_SVC_ENTRIES.
 *
 * See also section 16.3.3.5 ServiceEntries in the InfiniBand Architecture
 * Specअगरication. See also section B.7, table B.8 in the SRP r16a करोcument.
 */
अटल व्योम srpt_get_svc_entries(u64 ioc_guid,
				 u16 slot, u8 hi, u8 lo, काष्ठा ib_dm_mad *mad)
अणु
	काष्ठा ib_dm_svc_entries *svc_entries;

	WARN_ON(!ioc_guid);

	अगर (!slot || slot > 16) अणु
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_INVALID_FIELD);
		वापस;
	पूर्ण

	अगर (slot > 2 || lo > hi || hi > 1) अणु
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		वापस;
	पूर्ण

	svc_entries = (काष्ठा ib_dm_svc_entries *)mad->data;
	स_रखो(svc_entries, 0, माप(*svc_entries));
	svc_entries->service_entries[0].id = cpu_to_be64(ioc_guid);
	snम_लिखो(svc_entries->service_entries[0].name,
		 माप(svc_entries->service_entries[0].name),
		 "%s%016llx",
		 SRP_SERVICE_NAME_PREFIX,
		 ioc_guid);

	mad->mad_hdr.status = 0;
पूर्ण

/**
 * srpt_mgmt_method_get - process a received management datagram
 * @sp:      HCA port through which the MAD has been received.
 * @rq_mad:  received MAD.
 * @rsp_mad: response MAD.
 */
अटल व्योम srpt_mgmt_method_get(काष्ठा srpt_port *sp, काष्ठा ib_mad *rq_mad,
				 काष्ठा ib_dm_mad *rsp_mad)
अणु
	u16 attr_id;
	u32 slot;
	u8 hi, lo;

	attr_id = be16_to_cpu(rq_mad->mad_hdr.attr_id);
	चयन (attr_id) अणु
	हाल DM_ATTR_CLASS_PORT_INFO:
		srpt_get_class_port_info(rsp_mad);
		अवरोध;
	हाल DM_ATTR_IOU_INFO:
		srpt_get_iou(rsp_mad);
		अवरोध;
	हाल DM_ATTR_IOC_PROखाता:
		slot = be32_to_cpu(rq_mad->mad_hdr.attr_mod);
		srpt_get_ioc(sp, slot, rsp_mad);
		अवरोध;
	हाल DM_ATTR_SVC_ENTRIES:
		slot = be32_to_cpu(rq_mad->mad_hdr.attr_mod);
		hi = (u8) ((slot >> 8) & 0xff);
		lo = (u8) (slot & 0xff);
		slot = (u16) ((slot >> 16) & 0xffff);
		srpt_get_svc_entries(srpt_service_guid,
				     slot, hi, lo, rsp_mad);
		अवरोध;
	शेष:
		rsp_mad->mad_hdr.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD_ATTR);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * srpt_mad_send_handler - MAD send completion callback
 * @mad_agent: Return value of ib_रेजिस्टर_mad_agent().
 * @mad_wc: Work completion reporting that the MAD has been sent.
 */
अटल व्योम srpt_mad_send_handler(काष्ठा ib_mad_agent *mad_agent,
				  काष्ठा ib_mad_send_wc *mad_wc)
अणु
	rdma_destroy_ah(mad_wc->send_buf->ah, RDMA_DESTROY_AH_SLEEPABLE);
	ib_मुक्त_send_mad(mad_wc->send_buf);
पूर्ण

/**
 * srpt_mad_recv_handler - MAD reception callback function
 * @mad_agent: Return value of ib_रेजिस्टर_mad_agent().
 * @send_buf: Not used.
 * @mad_wc: Work completion reporting that a MAD has been received.
 */
अटल व्योम srpt_mad_recv_handler(काष्ठा ib_mad_agent *mad_agent,
				  काष्ठा ib_mad_send_buf *send_buf,
				  काष्ठा ib_mad_recv_wc *mad_wc)
अणु
	काष्ठा srpt_port *sport = (काष्ठा srpt_port *)mad_agent->context;
	काष्ठा ib_ah *ah;
	काष्ठा ib_mad_send_buf *rsp;
	काष्ठा ib_dm_mad *dm_mad;

	अगर (!mad_wc || !mad_wc->recv_buf.mad)
		वापस;

	ah = ib_create_ah_from_wc(mad_agent->qp->pd, mad_wc->wc,
				  mad_wc->recv_buf.grh, mad_agent->port_num);
	अगर (IS_ERR(ah))
		जाओ err;

	BUILD_BUG_ON(दुरत्व(काष्ठा ib_dm_mad, data) != IB_MGMT_DEVICE_HDR);

	rsp = ib_create_send_mad(mad_agent, mad_wc->wc->src_qp,
				 mad_wc->wc->pkey_index, 0,
				 IB_MGMT_DEVICE_HDR, IB_MGMT_DEVICE_DATA,
				 GFP_KERNEL,
				 IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(rsp))
		जाओ err_rsp;

	rsp->ah = ah;

	dm_mad = rsp->mad;
	स_नकल(dm_mad, mad_wc->recv_buf.mad, माप(*dm_mad));
	dm_mad->mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
	dm_mad->mad_hdr.status = 0;

	चयन (mad_wc->recv_buf.mad->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET:
		srpt_mgmt_method_get(sport, mad_wc->recv_buf.mad, dm_mad);
		अवरोध;
	हाल IB_MGMT_METHOD_SET:
		dm_mad->mad_hdr.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD_ATTR);
		अवरोध;
	शेष:
		dm_mad->mad_hdr.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD);
		अवरोध;
	पूर्ण

	अगर (!ib_post_send_mad(rsp, शून्य)) अणु
		ib_मुक्त_recv_mad(mad_wc);
		/* will destroy_ah & मुक्त_send_mad in send completion */
		वापस;
	पूर्ण

	ib_मुक्त_send_mad(rsp);

err_rsp:
	rdma_destroy_ah(ah, RDMA_DESTROY_AH_SLEEPABLE);
err:
	ib_मुक्त_recv_mad(mad_wc);
पूर्ण

अटल पूर्णांक srpt_क्रमmat_guid(अक्षर *buf, अचिन्हित पूर्णांक size, स्थिर __be64 *guid)
अणु
	स्थिर __be16 *g = (स्थिर __be16 *)guid;

	वापस snम_लिखो(buf, size, "%04x:%04x:%04x:%04x",
			be16_to_cpu(g[0]), be16_to_cpu(g[1]),
			be16_to_cpu(g[2]), be16_to_cpu(g[3]));
पूर्ण

/**
 * srpt_refresh_port - configure a HCA port
 * @sport: SRPT HCA port.
 *
 * Enable InfiniBand management datagram processing, update the cached sm_lid,
 * lid and gid values, and रेजिस्टर a callback function क्रम processing MADs
 * on the specअगरied port.
 *
 * Note: It is safe to call this function more than once क्रम the same port.
 */
अटल पूर्णांक srpt_refresh_port(काष्ठा srpt_port *sport)
अणु
	काष्ठा ib_mad_reg_req reg_req;
	काष्ठा ib_port_modअगरy port_modअगरy;
	काष्ठा ib_port_attr port_attr;
	पूर्णांक ret;

	ret = ib_query_port(sport->sdev->device, sport->port, &port_attr);
	अगर (ret)
		वापस ret;

	sport->sm_lid = port_attr.sm_lid;
	sport->lid = port_attr.lid;

	ret = rdma_query_gid(sport->sdev->device, sport->port, 0, &sport->gid);
	अगर (ret)
		वापस ret;

	sport->port_guid_id.wwn.priv = sport;
	srpt_क्रमmat_guid(sport->port_guid_id.name,
			 माप(sport->port_guid_id.name),
			 &sport->gid.global.पूर्णांकerface_id);
	sport->port_gid_id.wwn.priv = sport;
	snम_लिखो(sport->port_gid_id.name, माप(sport->port_gid_id.name),
		 "0x%016llx%016llx",
		 be64_to_cpu(sport->gid.global.subnet_prefix),
		 be64_to_cpu(sport->gid.global.पूर्णांकerface_id));

	अगर (rdma_protocol_iwarp(sport->sdev->device, sport->port))
		वापस 0;

	स_रखो(&port_modअगरy, 0, माप(port_modअगरy));
	port_modअगरy.set_port_cap_mask = IB_PORT_DEVICE_MGMT_SUP;
	port_modअगरy.clr_port_cap_mask = 0;

	ret = ib_modअगरy_port(sport->sdev->device, sport->port, 0, &port_modअगरy);
	अगर (ret) अणु
		pr_warn("%s-%d: enabling device management failed (%d). Note: this is expected if SR-IOV is enabled.\n",
			dev_name(&sport->sdev->device->dev), sport->port, ret);
		वापस 0;
	पूर्ण

	अगर (!sport->mad_agent) अणु
		स_रखो(&reg_req, 0, माप(reg_req));
		reg_req.mgmt_class = IB_MGMT_CLASS_DEVICE_MGMT;
		reg_req.mgmt_class_version = IB_MGMT_BASE_VERSION;
		set_bit(IB_MGMT_METHOD_GET, reg_req.method_mask);
		set_bit(IB_MGMT_METHOD_SET, reg_req.method_mask);

		sport->mad_agent = ib_रेजिस्टर_mad_agent(sport->sdev->device,
							 sport->port,
							 IB_QPT_GSI,
							 &reg_req, 0,
							 srpt_mad_send_handler,
							 srpt_mad_recv_handler,
							 sport, 0);
		अगर (IS_ERR(sport->mad_agent)) अणु
			pr_err("%s-%d: MAD agent registration failed (%ld). Note: this is expected if SR-IOV is enabled.\n",
			       dev_name(&sport->sdev->device->dev), sport->port,
			       PTR_ERR(sport->mad_agent));
			sport->mad_agent = शून्य;
			स_रखो(&port_modअगरy, 0, माप(port_modअगरy));
			port_modअगरy.clr_port_cap_mask = IB_PORT_DEVICE_MGMT_SUP;
			ib_modअगरy_port(sport->sdev->device, sport->port, 0,
				       &port_modअगरy);

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * srpt_unरेजिस्टर_mad_agent - unरेजिस्टर MAD callback functions
 * @sdev: SRPT HCA poपूर्णांकer.
 * @port_cnt: number of ports with रेजिस्टरed MAD
 *
 * Note: It is safe to call this function more than once क्रम the same device.
 */
अटल व्योम srpt_unरेजिस्टर_mad_agent(काष्ठा srpt_device *sdev, पूर्णांक port_cnt)
अणु
	काष्ठा ib_port_modअगरy port_modअगरy = अणु
		.clr_port_cap_mask = IB_PORT_DEVICE_MGMT_SUP,
	पूर्ण;
	काष्ठा srpt_port *sport;
	पूर्णांक i;

	क्रम (i = 1; i <= port_cnt; i++) अणु
		sport = &sdev->port[i - 1];
		WARN_ON(sport->port != i);
		अगर (sport->mad_agent) अणु
			ib_modअगरy_port(sdev->device, i, 0, &port_modअगरy);
			ib_unरेजिस्टर_mad_agent(sport->mad_agent);
			sport->mad_agent = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * srpt_alloc_ioctx - allocate a SRPT I/O context काष्ठाure
 * @sdev: SRPT HCA poपूर्णांकer.
 * @ioctx_size: I/O context size.
 * @buf_cache: I/O buffer cache.
 * @dir: DMA data direction.
 */
अटल काष्ठा srpt_ioctx *srpt_alloc_ioctx(काष्ठा srpt_device *sdev,
					   पूर्णांक ioctx_size,
					   काष्ठा kmem_cache *buf_cache,
					   क्रमागत dma_data_direction dir)
अणु
	काष्ठा srpt_ioctx *ioctx;

	ioctx = kzalloc(ioctx_size, GFP_KERNEL);
	अगर (!ioctx)
		जाओ err;

	ioctx->buf = kmem_cache_alloc(buf_cache, GFP_KERNEL);
	अगर (!ioctx->buf)
		जाओ err_मुक्त_ioctx;

	ioctx->dma = ib_dma_map_single(sdev->device, ioctx->buf,
				       kmem_cache_size(buf_cache), dir);
	अगर (ib_dma_mapping_error(sdev->device, ioctx->dma))
		जाओ err_मुक्त_buf;

	वापस ioctx;

err_मुक्त_buf:
	kmem_cache_मुक्त(buf_cache, ioctx->buf);
err_मुक्त_ioctx:
	kमुक्त(ioctx);
err:
	वापस शून्य;
पूर्ण

/**
 * srpt_मुक्त_ioctx - मुक्त a SRPT I/O context काष्ठाure
 * @sdev: SRPT HCA poपूर्णांकer.
 * @ioctx: I/O context poपूर्णांकer.
 * @buf_cache: I/O buffer cache.
 * @dir: DMA data direction.
 */
अटल व्योम srpt_मुक्त_ioctx(काष्ठा srpt_device *sdev, काष्ठा srpt_ioctx *ioctx,
			    काष्ठा kmem_cache *buf_cache,
			    क्रमागत dma_data_direction dir)
अणु
	अगर (!ioctx)
		वापस;

	ib_dma_unmap_single(sdev->device, ioctx->dma,
			    kmem_cache_size(buf_cache), dir);
	kmem_cache_मुक्त(buf_cache, ioctx->buf);
	kमुक्त(ioctx);
पूर्ण

/**
 * srpt_alloc_ioctx_ring - allocate a ring of SRPT I/O context काष्ठाures
 * @sdev:       Device to allocate the I/O context ring क्रम.
 * @ring_size:  Number of elements in the I/O context ring.
 * @ioctx_size: I/O context size.
 * @buf_cache:  I/O buffer cache.
 * @alignment_offset: Offset in each ring buffer at which the SRP inक्रमmation
 *		unit starts.
 * @dir:        DMA data direction.
 */
अटल काष्ठा srpt_ioctx **srpt_alloc_ioctx_ring(काष्ठा srpt_device *sdev,
				पूर्णांक ring_size, पूर्णांक ioctx_size,
				काष्ठा kmem_cache *buf_cache,
				पूर्णांक alignment_offset,
				क्रमागत dma_data_direction dir)
अणु
	काष्ठा srpt_ioctx **ring;
	पूर्णांक i;

	WARN_ON(ioctx_size != माप(काष्ठा srpt_recv_ioctx) &&
		ioctx_size != माप(काष्ठा srpt_send_ioctx));

	ring = kvदो_स्मृति_array(ring_size, माप(ring[0]), GFP_KERNEL);
	अगर (!ring)
		जाओ out;
	क्रम (i = 0; i < ring_size; ++i) अणु
		ring[i] = srpt_alloc_ioctx(sdev, ioctx_size, buf_cache, dir);
		अगर (!ring[i])
			जाओ err;
		ring[i]->index = i;
		ring[i]->offset = alignment_offset;
	पूर्ण
	जाओ out;

err:
	जबतक (--i >= 0)
		srpt_मुक्त_ioctx(sdev, ring[i], buf_cache, dir);
	kvमुक्त(ring);
	ring = शून्य;
out:
	वापस ring;
पूर्ण

/**
 * srpt_मुक्त_ioctx_ring - मुक्त the ring of SRPT I/O context काष्ठाures
 * @ioctx_ring: I/O context ring to be मुक्तd.
 * @sdev: SRPT HCA poपूर्णांकer.
 * @ring_size: Number of ring elements.
 * @buf_cache: I/O buffer cache.
 * @dir: DMA data direction.
 */
अटल व्योम srpt_मुक्त_ioctx_ring(काष्ठा srpt_ioctx **ioctx_ring,
				 काष्ठा srpt_device *sdev, पूर्णांक ring_size,
				 काष्ठा kmem_cache *buf_cache,
				 क्रमागत dma_data_direction dir)
अणु
	पूर्णांक i;

	अगर (!ioctx_ring)
		वापस;

	क्रम (i = 0; i < ring_size; ++i)
		srpt_मुक्त_ioctx(sdev, ioctx_ring[i], buf_cache, dir);
	kvमुक्त(ioctx_ring);
पूर्ण

/**
 * srpt_set_cmd_state - set the state of a SCSI command
 * @ioctx: Send I/O context.
 * @new: New I/O context state.
 *
 * Does not modअगरy the state of पातed commands. Returns the previous command
 * state.
 */
अटल क्रमागत srpt_command_state srpt_set_cmd_state(काष्ठा srpt_send_ioctx *ioctx,
						  क्रमागत srpt_command_state new)
अणु
	क्रमागत srpt_command_state previous;

	previous = ioctx->state;
	अगर (previous != SRPT_STATE_DONE)
		ioctx->state = new;

	वापस previous;
पूर्ण

/**
 * srpt_test_and_set_cmd_state - test and set the state of a command
 * @ioctx: Send I/O context.
 * @old: Current I/O context state.
 * @new: New I/O context state.
 *
 * Returns true अगर and only अगर the previous command state was equal to 'old'.
 */
अटल bool srpt_test_and_set_cmd_state(काष्ठा srpt_send_ioctx *ioctx,
					क्रमागत srpt_command_state old,
					क्रमागत srpt_command_state new)
अणु
	क्रमागत srpt_command_state previous;

	WARN_ON(!ioctx);
	WARN_ON(old == SRPT_STATE_DONE);
	WARN_ON(new == SRPT_STATE_NEW);

	previous = ioctx->state;
	अगर (previous == old)
		ioctx->state = new;

	वापस previous == old;
पूर्ण

/**
 * srpt_post_recv - post an IB receive request
 * @sdev: SRPT HCA poपूर्णांकer.
 * @ch: SRPT RDMA channel.
 * @ioctx: Receive I/O context poपूर्णांकer.
 */
अटल पूर्णांक srpt_post_recv(काष्ठा srpt_device *sdev, काष्ठा srpt_rdma_ch *ch,
			  काष्ठा srpt_recv_ioctx *ioctx)
अणु
	काष्ठा ib_sge list;
	काष्ठा ib_recv_wr wr;

	BUG_ON(!sdev);
	list.addr = ioctx->ioctx.dma + ioctx->ioctx.offset;
	list.length = srp_max_req_size;
	list.lkey = sdev->lkey;

	ioctx->ioctx.cqe.करोne = srpt_recv_करोne;
	wr.wr_cqe = &ioctx->ioctx.cqe;
	wr.next = शून्य;
	wr.sg_list = &list;
	wr.num_sge = 1;

	अगर (sdev->use_srq)
		वापस ib_post_srq_recv(sdev->srq, &wr, शून्य);
	अन्यथा
		वापस ib_post_recv(ch->qp, &wr, शून्य);
पूर्ण

/**
 * srpt_zerolength_ग_लिखो - perक्रमm a zero-length RDMA ग_लिखो
 * @ch: SRPT RDMA channel.
 *
 * A quote from the InfiniBand specअगरication: C9-88: For an HCA responder
 * using Reliable Connection service, क्रम each zero-length RDMA READ or WRITE
 * request, the R_Key shall not be validated, even अगर the request includes
 * Immediate data.
 */
अटल पूर्णांक srpt_zerolength_ग_लिखो(काष्ठा srpt_rdma_ch *ch)
अणु
	काष्ठा ib_rdma_wr wr = अणु
		.wr = अणु
			.next		= शून्य,
			अणु .wr_cqe	= &ch->zw_cqe, पूर्ण,
			.opcode		= IB_WR_RDMA_WRITE,
			.send_flags	= IB_SEND_SIGNALED,
		पूर्ण
	पूर्ण;

	pr_debug("%s-%d: queued zerolength write\n", ch->sess_name,
		 ch->qp->qp_num);

	वापस ib_post_send(ch->qp, &wr.wr, शून्य);
पूर्ण

अटल व्योम srpt_zerolength_ग_लिखो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srpt_rdma_ch *ch = wc->qp->qp_context;

	pr_debug("%s-%d wc->status %d\n", ch->sess_name, ch->qp->qp_num,
		 wc->status);

	अगर (wc->status == IB_WC_SUCCESS) अणु
		srpt_process_रुको_list(ch);
	पूर्ण अन्यथा अणु
		अगर (srpt_set_ch_state(ch, CH_DISCONNECTED))
			schedule_work(&ch->release_work);
		अन्यथा
			pr_debug("%s-%d: already disconnected.\n",
				 ch->sess_name, ch->qp->qp_num);
	पूर्ण
पूर्ण

अटल पूर्णांक srpt_alloc_rw_ctxs(काष्ठा srpt_send_ioctx *ioctx,
		काष्ठा srp_direct_buf *db, पूर्णांक nbufs, काष्ठा scatterlist **sg,
		अचिन्हित *sg_cnt)
अणु
	क्रमागत dma_data_direction dir = target_reverse_dma_direction(&ioctx->cmd);
	काष्ठा srpt_rdma_ch *ch = ioctx->ch;
	काष्ठा scatterlist *prev = शून्य;
	अचिन्हित prev_nents;
	पूर्णांक ret, i;

	अगर (nbufs == 1) अणु
		ioctx->rw_ctxs = &ioctx->s_rw_ctx;
	पूर्ण अन्यथा अणु
		ioctx->rw_ctxs = kदो_स्मृति_array(nbufs, माप(*ioctx->rw_ctxs),
			GFP_KERNEL);
		अगर (!ioctx->rw_ctxs)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = ioctx->n_rw_ctx; i < nbufs; i++, db++) अणु
		काष्ठा srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];
		u64 remote_addr = be64_to_cpu(db->va);
		u32 size = be32_to_cpu(db->len);
		u32 rkey = be32_to_cpu(db->key);

		ret = target_alloc_sgl(&ctx->sg, &ctx->nents, size, false,
				i < nbufs - 1);
		अगर (ret)
			जाओ unwind;

		ret = rdma_rw_ctx_init(&ctx->rw, ch->qp, ch->sport->port,
				ctx->sg, ctx->nents, 0, remote_addr, rkey, dir);
		अगर (ret < 0) अणु
			target_मुक्त_sgl(ctx->sg, ctx->nents);
			जाओ unwind;
		पूर्ण

		ioctx->n_rdma += ret;
		ioctx->n_rw_ctx++;

		अगर (prev) अणु
			sg_unmark_end(&prev[prev_nents - 1]);
			sg_chain(prev, prev_nents + 1, ctx->sg);
		पूर्ण अन्यथा अणु
			*sg = ctx->sg;
		पूर्ण

		prev = ctx->sg;
		prev_nents = ctx->nents;

		*sg_cnt += ctx->nents;
	पूर्ण

	वापस 0;

unwind:
	जबतक (--i >= 0) अणु
		काष्ठा srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];

		rdma_rw_ctx_destroy(&ctx->rw, ch->qp, ch->sport->port,
				ctx->sg, ctx->nents, dir);
		target_मुक्त_sgl(ctx->sg, ctx->nents);
	पूर्ण
	अगर (ioctx->rw_ctxs != &ioctx->s_rw_ctx)
		kमुक्त(ioctx->rw_ctxs);
	वापस ret;
पूर्ण

अटल व्योम srpt_मुक्त_rw_ctxs(काष्ठा srpt_rdma_ch *ch,
				    काष्ठा srpt_send_ioctx *ioctx)
अणु
	क्रमागत dma_data_direction dir = target_reverse_dma_direction(&ioctx->cmd);
	पूर्णांक i;

	क्रम (i = 0; i < ioctx->n_rw_ctx; i++) अणु
		काष्ठा srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];

		rdma_rw_ctx_destroy(&ctx->rw, ch->qp, ch->sport->port,
				ctx->sg, ctx->nents, dir);
		target_मुक्त_sgl(ctx->sg, ctx->nents);
	पूर्ण

	अगर (ioctx->rw_ctxs != &ioctx->s_rw_ctx)
		kमुक्त(ioctx->rw_ctxs);
पूर्ण

अटल अंतरभूत व्योम *srpt_get_desc_buf(काष्ठा srp_cmd *srp_cmd)
अणु
	/*
	 * The poपूर्णांकer computations below will only be compiled correctly
	 * अगर srp_cmd::add_data is declared as s8*, u8*, s8[] or u8[], so check
	 * whether srp_cmd::add_data has been declared as a byte poपूर्णांकer.
	 */
	BUILD_BUG_ON(!__same_type(srp_cmd->add_data[0], (s8)0) &&
		     !__same_type(srp_cmd->add_data[0], (u8)0));

	/*
	 * According to the SRP spec, the lower two bits of the 'ADDITIONAL
	 * CDB LENGTH' field are reserved and the size in bytes of this field
	 * is four बार the value specअगरied in bits 3..7. Hence the "& ~3".
	 */
	वापस srp_cmd->add_data + (srp_cmd->add_cdb_len & ~3);
पूर्ण

/**
 * srpt_get_desc_tbl - parse the data descriptors of a SRP_CMD request
 * @recv_ioctx: I/O context associated with the received command @srp_cmd.
 * @ioctx: I/O context that will be used क्रम responding to the initiator.
 * @srp_cmd: Poपूर्णांकer to the SRP_CMD request data.
 * @dir: Poपूर्णांकer to the variable to which the transfer direction will be
 *   written.
 * @sg: [out] scatterlist क्रम the parsed SRP_CMD.
 * @sg_cnt: [out] length of @sg.
 * @data_len: Poपूर्णांकer to the variable to which the total data length of all
 *   descriptors in the SRP_CMD request will be written.
 * @imm_data_offset: [in] Offset in SRP_CMD requests at which immediate data
 *   starts.
 *
 * This function initializes ioctx->nrbuf and ioctx->r_bufs.
 *
 * Returns -EINVAL when the SRP_CMD request contains inconsistent descriptors;
 * -ENOMEM when memory allocation fails and zero upon success.
 */
अटल पूर्णांक srpt_get_desc_tbl(काष्ठा srpt_recv_ioctx *recv_ioctx,
		काष्ठा srpt_send_ioctx *ioctx,
		काष्ठा srp_cmd *srp_cmd, क्रमागत dma_data_direction *dir,
		काष्ठा scatterlist **sg, अचिन्हित पूर्णांक *sg_cnt, u64 *data_len,
		u16 imm_data_offset)
अणु
	BUG_ON(!dir);
	BUG_ON(!data_len);

	/*
	 * The lower four bits of the buffer क्रमmat field contain the DATA-IN
	 * buffer descriptor क्रमmat, and the highest four bits contain the
	 * DATA-OUT buffer descriptor क्रमmat.
	 */
	अगर (srp_cmd->buf_fmt & 0xf)
		/* DATA-IN: transfer data from target to initiator (पढ़ो). */
		*dir = DMA_FROM_DEVICE;
	अन्यथा अगर (srp_cmd->buf_fmt >> 4)
		/* DATA-OUT: transfer data from initiator to target (ग_लिखो). */
		*dir = DMA_TO_DEVICE;
	अन्यथा
		*dir = DMA_NONE;

	/* initialize data_direction early as srpt_alloc_rw_ctxs needs it */
	ioctx->cmd.data_direction = *dir;

	अगर (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_सूचीECT) ||
	    ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_सूचीECT)) अणु
		काष्ठा srp_direct_buf *db = srpt_get_desc_buf(srp_cmd);

		*data_len = be32_to_cpu(db->len);
		वापस srpt_alloc_rw_ctxs(ioctx, db, 1, sg, sg_cnt);
	पूर्ण अन्यथा अगर (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_INसूचीECT) ||
		   ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_INसूचीECT)) अणु
		काष्ठा srp_indirect_buf *idb = srpt_get_desc_buf(srp_cmd);
		पूर्णांक nbufs = be32_to_cpu(idb->table_desc.len) /
				माप(काष्ठा srp_direct_buf);

		अगर (nbufs >
		    (srp_cmd->data_out_desc_cnt + srp_cmd->data_in_desc_cnt)) अणु
			pr_err("received unsupported SRP_CMD request type (%u out + %u in != %u / %zu)\n",
			       srp_cmd->data_out_desc_cnt,
			       srp_cmd->data_in_desc_cnt,
			       be32_to_cpu(idb->table_desc.len),
			       माप(काष्ठा srp_direct_buf));
			वापस -EINVAL;
		पूर्ण

		*data_len = be32_to_cpu(idb->len);
		वापस srpt_alloc_rw_ctxs(ioctx, idb->desc_list, nbufs,
				sg, sg_cnt);
	पूर्ण अन्यथा अगर ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_IMM) अणु
		काष्ठा srp_imm_buf *imm_buf = srpt_get_desc_buf(srp_cmd);
		व्योम *data = (व्योम *)srp_cmd + imm_data_offset;
		uपूर्णांक32_t len = be32_to_cpu(imm_buf->len);
		uपूर्णांक32_t req_size = imm_data_offset + len;

		अगर (req_size > srp_max_req_size) अणु
			pr_err("Immediate data (length %d + %d) exceeds request size %d\n",
			       imm_data_offset, len, srp_max_req_size);
			वापस -EINVAL;
		पूर्ण
		अगर (recv_ioctx->byte_len < req_size) अणु
			pr_err("Received too few data - %d < %d\n",
			       recv_ioctx->byte_len, req_size);
			वापस -EIO;
		पूर्ण
		/*
		 * The immediate data buffer descriptor must occur beक्रमe the
		 * immediate data itself.
		 */
		अगर ((व्योम *)(imm_buf + 1) > (व्योम *)data) अणु
			pr_err("Received invalid write request\n");
			वापस -EINVAL;
		पूर्ण
		*data_len = len;
		ioctx->recv_ioctx = recv_ioctx;
		अगर ((uपूर्णांकptr_t)data & 511) अणु
			pr_warn_once("Internal error - the receive buffers are not aligned properly.\n");
			वापस -EINVAL;
		पूर्ण
		sg_init_one(&ioctx->imm_sg, data, len);
		*sg = &ioctx->imm_sg;
		*sg_cnt = 1;
		वापस 0;
	पूर्ण अन्यथा अणु
		*data_len = 0;
		वापस 0;
	पूर्ण
पूर्ण

/**
 * srpt_init_ch_qp - initialize queue pair attributes
 * @ch: SRPT RDMA channel.
 * @qp: Queue pair poपूर्णांकer.
 *
 * Initialized the attributes of queue pair 'qp' by allowing local ग_लिखो,
 * remote पढ़ो and remote ग_लिखो. Also transitions 'qp' to state IB_QPS_INIT.
 */
अटल पूर्णांक srpt_init_ch_qp(काष्ठा srpt_rdma_ch *ch, काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr *attr;
	पूर्णांक ret;

	WARN_ON_ONCE(ch->using_rdma_cm);

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	attr->qp_state = IB_QPS_INIT;
	attr->qp_access_flags = IB_ACCESS_LOCAL_WRITE;
	attr->port_num = ch->sport->port;

	ret = ib_find_cached_pkey(ch->sport->sdev->device, ch->sport->port,
				  ch->pkey, &attr->pkey_index);
	अगर (ret < 0)
		pr_err("Translating pkey %#x failed (%d) - using index 0\n",
		       ch->pkey, ret);

	ret = ib_modअगरy_qp(qp, attr,
			   IB_QP_STATE | IB_QP_ACCESS_FLAGS | IB_QP_PORT |
			   IB_QP_PKEY_INDEX);

	kमुक्त(attr);
	वापस ret;
पूर्ण

/**
 * srpt_ch_qp_rtr - change the state of a channel to 'ready to receive' (RTR)
 * @ch: channel of the queue pair.
 * @qp: queue pair to change the state of.
 *
 * Returns zero upon success and a negative value upon failure.
 *
 * Note: currently a काष्ठा ib_qp_attr takes 136 bytes on a 64-bit प्रणाली.
 * If this काष्ठाure ever becomes larger, it might be necessary to allocate
 * it dynamically instead of on the stack.
 */
अटल पूर्णांक srpt_ch_qp_rtr(काष्ठा srpt_rdma_ch *ch, काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक attr_mask;
	पूर्णांक ret;

	WARN_ON_ONCE(ch->using_rdma_cm);

	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_cm_init_qp_attr(ch->ib_cm.cm_id, &qp_attr, &attr_mask);
	अगर (ret)
		जाओ out;

	qp_attr.max_dest_rd_atomic = 4;

	ret = ib_modअगरy_qp(qp, &qp_attr, attr_mask);

out:
	वापस ret;
पूर्ण

/**
 * srpt_ch_qp_rts - change the state of a channel to 'ready to send' (RTS)
 * @ch: channel of the queue pair.
 * @qp: queue pair to change the state of.
 *
 * Returns zero upon success and a negative value upon failure.
 *
 * Note: currently a काष्ठा ib_qp_attr takes 136 bytes on a 64-bit प्रणाली.
 * If this काष्ठाure ever becomes larger, it might be necessary to allocate
 * it dynamically instead of on the stack.
 */
अटल पूर्णांक srpt_ch_qp_rts(काष्ठा srpt_rdma_ch *ch, काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक attr_mask;
	पूर्णांक ret;

	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_cm_init_qp_attr(ch->ib_cm.cm_id, &qp_attr, &attr_mask);
	अगर (ret)
		जाओ out;

	qp_attr.max_rd_atomic = 4;

	ret = ib_modअगरy_qp(qp, &qp_attr, attr_mask);

out:
	वापस ret;
पूर्ण

/**
 * srpt_ch_qp_err - set the channel queue pair state to 'error'
 * @ch: SRPT RDMA channel.
 */
अटल पूर्णांक srpt_ch_qp_err(काष्ठा srpt_rdma_ch *ch)
अणु
	काष्ठा ib_qp_attr qp_attr;

	qp_attr.qp_state = IB_QPS_ERR;
	वापस ib_modअगरy_qp(ch->qp, &qp_attr, IB_QP_STATE);
पूर्ण

/**
 * srpt_get_send_ioctx - obtain an I/O context क्रम sending to the initiator
 * @ch: SRPT RDMA channel.
 */
अटल काष्ठा srpt_send_ioctx *srpt_get_send_ioctx(काष्ठा srpt_rdma_ch *ch)
अणु
	काष्ठा srpt_send_ioctx *ioctx;
	पूर्णांक tag, cpu;

	BUG_ON(!ch);

	tag = sbiपंचांगap_queue_get(&ch->sess->sess_tag_pool, &cpu);
	अगर (tag < 0)
		वापस शून्य;

	ioctx = ch->ioctx_ring[tag];
	BUG_ON(ioctx->ch != ch);
	ioctx->state = SRPT_STATE_NEW;
	WARN_ON_ONCE(ioctx->recv_ioctx);
	ioctx->n_rdma = 0;
	ioctx->n_rw_ctx = 0;
	ioctx->queue_status_only = false;
	/*
	 * transport_init_se_cmd() करोes not initialize all fields, so करो it
	 * here.
	 */
	स_रखो(&ioctx->cmd, 0, माप(ioctx->cmd));
	स_रखो(&ioctx->sense_data, 0, माप(ioctx->sense_data));
	ioctx->cmd.map_tag = tag;
	ioctx->cmd.map_cpu = cpu;

	वापस ioctx;
पूर्ण

/**
 * srpt_पात_cmd - पात a SCSI command
 * @ioctx:   I/O context associated with the SCSI command.
 */
अटल पूर्णांक srpt_पात_cmd(काष्ठा srpt_send_ioctx *ioctx)
अणु
	क्रमागत srpt_command_state state;

	BUG_ON(!ioctx);

	/*
	 * If the command is in a state where the target core is रुकोing क्रम
	 * the ib_srpt driver, change the state to the next state.
	 */

	state = ioctx->state;
	चयन (state) अणु
	हाल SRPT_STATE_NEED_DATA:
		ioctx->state = SRPT_STATE_DATA_IN;
		अवरोध;
	हाल SRPT_STATE_CMD_RSP_SENT:
	हाल SRPT_STATE_MGMT_RSP_SENT:
		ioctx->state = SRPT_STATE_DONE;
		अवरोध;
	शेष:
		WARN_ONCE(true, "%s: unexpected I/O context state %d\n",
			  __func__, state);
		अवरोध;
	पूर्ण

	pr_debug("Aborting cmd with state %d -> %d and tag %lld\n", state,
		 ioctx->state, ioctx->cmd.tag);

	चयन (state) अणु
	हाल SRPT_STATE_NEW:
	हाल SRPT_STATE_DATA_IN:
	हाल SRPT_STATE_MGMT:
	हाल SRPT_STATE_DONE:
		/*
		 * Do nothing - defer पात processing until
		 * srpt_queue_response() is invoked.
		 */
		अवरोध;
	हाल SRPT_STATE_NEED_DATA:
		pr_debug("tag %#llx: RDMA read error\n", ioctx->cmd.tag);
		transport_generic_request_failure(&ioctx->cmd,
					TCM_CHECK_CONDITION_ABORT_CMD);
		अवरोध;
	हाल SRPT_STATE_CMD_RSP_SENT:
		/*
		 * SRP_RSP sending failed or the SRP_RSP send completion has
		 * not been received in समय.
		 */
		transport_generic_मुक्त_cmd(&ioctx->cmd, 0);
		अवरोध;
	हाल SRPT_STATE_MGMT_RSP_SENT:
		transport_generic_मुक्त_cmd(&ioctx->cmd, 0);
		अवरोध;
	शेष:
		WARN(1, "Unexpected command state (%d)", state);
		अवरोध;
	पूर्ण

	वापस state;
पूर्ण

/**
 * srpt_rdma_पढ़ो_करोne - RDMA पढ़ो completion callback
 * @cq: Completion queue.
 * @wc: Work completion.
 *
 * XXX: what is now target_execute_cmd used to be asynchronous, and unmapping
 * the data that has been transferred via IB RDMA had to be postponed until the
 * check_stop_मुक्त() callback.  None of this is necessary anymore and needs to
 * be cleaned up.
 */
अटल व्योम srpt_rdma_पढ़ो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srpt_rdma_ch *ch = wc->qp->qp_context;
	काष्ठा srpt_send_ioctx *ioctx =
		container_of(wc->wr_cqe, काष्ठा srpt_send_ioctx, rdma_cqe);

	WARN_ON(ioctx->n_rdma <= 0);
	atomic_add(ioctx->n_rdma, &ch->sq_wr_avail);
	ioctx->n_rdma = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		pr_info("RDMA_READ for ioctx 0x%p failed with status %d\n",
			ioctx, wc->status);
		srpt_पात_cmd(ioctx);
		वापस;
	पूर्ण

	अगर (srpt_test_and_set_cmd_state(ioctx, SRPT_STATE_NEED_DATA,
					SRPT_STATE_DATA_IN))
		target_execute_cmd(&ioctx->cmd);
	अन्यथा
		pr_err("%s[%d]: wrong state = %d\n", __func__,
		       __LINE__, ioctx->state);
पूर्ण

/**
 * srpt_build_cmd_rsp - build a SRP_RSP response
 * @ch: RDMA channel through which the request has been received.
 * @ioctx: I/O context associated with the SRP_CMD request. The response will
 *   be built in the buffer ioctx->buf poपूर्णांकs at and hence this function will
 *   overग_लिखो the request data.
 * @tag: tag of the request क्रम which this response is being generated.
 * @status: value क्रम the STATUS field of the SRP_RSP inक्रमmation unit.
 *
 * Returns the size in bytes of the SRP_RSP response.
 *
 * An SRP_RSP response contains a SCSI status or service response. See also
 * section 6.9 in the SRP r16a करोcument क्रम the क्रमmat of an SRP_RSP
 * response. See also SPC-2 क्रम more inक्रमmation about sense data.
 */
अटल पूर्णांक srpt_build_cmd_rsp(काष्ठा srpt_rdma_ch *ch,
			      काष्ठा srpt_send_ioctx *ioctx, u64 tag,
			      पूर्णांक status)
अणु
	काष्ठा se_cmd *cmd = &ioctx->cmd;
	काष्ठा srp_rsp *srp_rsp;
	स्थिर u8 *sense_data;
	पूर्णांक sense_data_len, max_sense_len;
	u32 resid = cmd->residual_count;

	/*
	 * The lowest bit of all SAM-3 status codes is zero (see also
	 * paragraph 5.3 in SAM-3).
	 */
	WARN_ON(status & 1);

	srp_rsp = ioctx->ioctx.buf;
	BUG_ON(!srp_rsp);

	sense_data = ioctx->sense_data;
	sense_data_len = ioctx->cmd.scsi_sense_length;
	WARN_ON(sense_data_len > माप(ioctx->sense_data));

	स_रखो(srp_rsp, 0, माप(*srp_rsp));
	srp_rsp->opcode = SRP_RSP;
	srp_rsp->req_lim_delta =
		cpu_to_be32(1 + atomic_xchg(&ch->req_lim_delta, 0));
	srp_rsp->tag = tag;
	srp_rsp->status = status;

	अगर (cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
		अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
			/* residual data from an underflow ग_लिखो */
			srp_rsp->flags = SRP_RSP_FLAG_DOUNDER;
			srp_rsp->data_out_res_cnt = cpu_to_be32(resid);
		पूर्ण अन्यथा अगर (cmd->data_direction == DMA_FROM_DEVICE) अणु
			/* residual data from an underflow पढ़ो */
			srp_rsp->flags = SRP_RSP_FLAG_DIUNDER;
			srp_rsp->data_in_res_cnt = cpu_to_be32(resid);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->se_cmd_flags & SCF_OVERFLOW_BIT) अणु
		अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
			/* residual data from an overflow ग_लिखो */
			srp_rsp->flags = SRP_RSP_FLAG_DOOVER;
			srp_rsp->data_out_res_cnt = cpu_to_be32(resid);
		पूर्ण अन्यथा अगर (cmd->data_direction == DMA_FROM_DEVICE) अणु
			/* residual data from an overflow पढ़ो */
			srp_rsp->flags = SRP_RSP_FLAG_DIOVER;
			srp_rsp->data_in_res_cnt = cpu_to_be32(resid);
		पूर्ण
	पूर्ण

	अगर (sense_data_len) अणु
		BUILD_BUG_ON(MIN_MAX_RSP_SIZE <= माप(*srp_rsp));
		max_sense_len = ch->max_ti_iu_len - माप(*srp_rsp);
		अगर (sense_data_len > max_sense_len) अणु
			pr_warn("truncated sense data from %d to %d bytes\n",
				sense_data_len, max_sense_len);
			sense_data_len = max_sense_len;
		पूर्ण

		srp_rsp->flags |= SRP_RSP_FLAG_SNSVALID;
		srp_rsp->sense_data_len = cpu_to_be32(sense_data_len);
		स_नकल(srp_rsp + 1, sense_data, sense_data_len);
	पूर्ण

	वापस माप(*srp_rsp) + sense_data_len;
पूर्ण

/**
 * srpt_build_tskmgmt_rsp - build a task management response
 * @ch:       RDMA channel through which the request has been received.
 * @ioctx:    I/O context in which the SRP_RSP response will be built.
 * @rsp_code: RSP_CODE that will be stored in the response.
 * @tag:      Tag of the request क्रम which this response is being generated.
 *
 * Returns the size in bytes of the SRP_RSP response.
 *
 * An SRP_RSP response contains a SCSI status or service response. See also
 * section 6.9 in the SRP r16a करोcument क्रम the क्रमmat of an SRP_RSP
 * response.
 */
अटल पूर्णांक srpt_build_tskmgmt_rsp(काष्ठा srpt_rdma_ch *ch,
				  काष्ठा srpt_send_ioctx *ioctx,
				  u8 rsp_code, u64 tag)
अणु
	काष्ठा srp_rsp *srp_rsp;
	पूर्णांक resp_data_len;
	पूर्णांक resp_len;

	resp_data_len = 4;
	resp_len = माप(*srp_rsp) + resp_data_len;

	srp_rsp = ioctx->ioctx.buf;
	BUG_ON(!srp_rsp);
	स_रखो(srp_rsp, 0, माप(*srp_rsp));

	srp_rsp->opcode = SRP_RSP;
	srp_rsp->req_lim_delta =
		cpu_to_be32(1 + atomic_xchg(&ch->req_lim_delta, 0));
	srp_rsp->tag = tag;

	srp_rsp->flags |= SRP_RSP_FLAG_RSPVALID;
	srp_rsp->resp_data_len = cpu_to_be32(resp_data_len);
	srp_rsp->data[3] = rsp_code;

	वापस resp_len;
पूर्ण

अटल पूर्णांक srpt_check_stop_मुक्त(काष्ठा se_cmd *cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx = container_of(cmd,
				काष्ठा srpt_send_ioctx, cmd);

	वापस target_put_sess_cmd(&ioctx->cmd);
पूर्ण

/**
 * srpt_handle_cmd - process a SRP_CMD inक्रमmation unit
 * @ch: SRPT RDMA channel.
 * @recv_ioctx: Receive I/O context.
 * @send_ioctx: Send I/O context.
 */
अटल व्योम srpt_handle_cmd(काष्ठा srpt_rdma_ch *ch,
			    काष्ठा srpt_recv_ioctx *recv_ioctx,
			    काष्ठा srpt_send_ioctx *send_ioctx)
अणु
	काष्ठा se_cmd *cmd;
	काष्ठा srp_cmd *srp_cmd;
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित sg_cnt = 0;
	u64 data_len;
	क्रमागत dma_data_direction dir;
	पूर्णांक rc;

	BUG_ON(!send_ioctx);

	srp_cmd = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;
	cmd->tag = srp_cmd->tag;

	चयन (srp_cmd->task_attr) अणु
	हाल SRP_CMD_SIMPLE_Q:
		cmd->sam_task_attr = TCM_SIMPLE_TAG;
		अवरोध;
	हाल SRP_CMD_ORDERED_Q:
	शेष:
		cmd->sam_task_attr = TCM_ORDERED_TAG;
		अवरोध;
	हाल SRP_CMD_HEAD_OF_Q:
		cmd->sam_task_attr = TCM_HEAD_TAG;
		अवरोध;
	हाल SRP_CMD_ACA:
		cmd->sam_task_attr = TCM_ACA_TAG;
		अवरोध;
	पूर्ण

	rc = srpt_get_desc_tbl(recv_ioctx, send_ioctx, srp_cmd, &dir,
			       &sg, &sg_cnt, &data_len, ch->imm_data_offset);
	अगर (rc) अणु
		अगर (rc != -EAGAIN) अणु
			pr_err("0x%llx: parsing SRP descriptor table failed.\n",
			       srp_cmd->tag);
		पूर्ण
		जाओ busy;
	पूर्ण

	rc = target_init_cmd(cmd, ch->sess, &send_ioctx->sense_data[0],
			     scsilun_to_पूर्णांक(&srp_cmd->lun), data_len,
			     TCM_SIMPLE_TAG, dir, TARGET_SCF_ACK_KREF);
	अगर (rc != 0) अणु
		pr_debug("target_submit_cmd() returned %d for tag %#llx\n", rc,
			 srp_cmd->tag);
		जाओ busy;
	पूर्ण

	अगर (target_submit_prep(cmd, srp_cmd->cdb, sg, sg_cnt, शून्य, 0, शून्य, 0,
			       GFP_KERNEL))
		वापस;

	target_submit(cmd);
	वापस;

busy:
	target_send_busy(cmd);
पूर्ण

अटल पूर्णांक srp_पंचांगr_to_tcm(पूर्णांक fn)
अणु
	चयन (fn) अणु
	हाल SRP_TSK_ABORT_TASK:
		वापस TMR_ABORT_TASK;
	हाल SRP_TSK_ABORT_TASK_SET:
		वापस TMR_ABORT_TASK_SET;
	हाल SRP_TSK_CLEAR_TASK_SET:
		वापस TMR_CLEAR_TASK_SET;
	हाल SRP_TSK_LUN_RESET:
		वापस TMR_LUN_RESET;
	हाल SRP_TSK_CLEAR_ACA:
		वापस TMR_CLEAR_ACA;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/**
 * srpt_handle_tsk_mgmt - process a SRP_TSK_MGMT inक्रमmation unit
 * @ch: SRPT RDMA channel.
 * @recv_ioctx: Receive I/O context.
 * @send_ioctx: Send I/O context.
 *
 * Returns 0 अगर and only अगर the request will be processed by the target core.
 *
 * For more inक्रमmation about SRP_TSK_MGMT inक्रमmation units, see also section
 * 6.7 in the SRP r16a करोcument.
 */
अटल व्योम srpt_handle_tsk_mgmt(काष्ठा srpt_rdma_ch *ch,
				 काष्ठा srpt_recv_ioctx *recv_ioctx,
				 काष्ठा srpt_send_ioctx *send_ioctx)
अणु
	काष्ठा srp_tsk_mgmt *srp_tsk;
	काष्ठा se_cmd *cmd;
	काष्ठा se_session *sess = ch->sess;
	पूर्णांक tcm_पंचांगr;
	पूर्णांक rc;

	BUG_ON(!send_ioctx);

	srp_tsk = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;

	pr_debug("recv tsk_mgmt fn %d for task_tag %lld and cmd tag %lld ch %p sess %p\n",
		 srp_tsk->tsk_mgmt_func, srp_tsk->task_tag, srp_tsk->tag, ch,
		 ch->sess);

	srpt_set_cmd_state(send_ioctx, SRPT_STATE_MGMT);
	send_ioctx->cmd.tag = srp_tsk->tag;
	tcm_पंचांगr = srp_पंचांगr_to_tcm(srp_tsk->tsk_mgmt_func);
	rc = target_submit_पंचांगr(&send_ioctx->cmd, sess, शून्य,
			       scsilun_to_पूर्णांक(&srp_tsk->lun), srp_tsk, tcm_पंचांगr,
			       GFP_KERNEL, srp_tsk->task_tag,
			       TARGET_SCF_ACK_KREF);
	अगर (rc != 0) अणु
		send_ioctx->cmd.se_पंचांगr_req->response = TMR_FUNCTION_REJECTED;
		cmd->se_tfo->queue_पंचांग_rsp(cmd);
	पूर्ण
	वापस;
पूर्ण

/**
 * srpt_handle_new_iu - process a newly received inक्रमmation unit
 * @ch:    RDMA channel through which the inक्रमmation unit has been received.
 * @recv_ioctx: Receive I/O context associated with the inक्रमmation unit.
 */
अटल bool
srpt_handle_new_iu(काष्ठा srpt_rdma_ch *ch, काष्ठा srpt_recv_ioctx *recv_ioctx)
अणु
	काष्ठा srpt_send_ioctx *send_ioctx = शून्य;
	काष्ठा srp_cmd *srp_cmd;
	bool res = false;
	u8 opcode;

	BUG_ON(!ch);
	BUG_ON(!recv_ioctx);

	अगर (unlikely(ch->state == CH_CONNECTING))
		जाओ push;

	ib_dma_sync_single_क्रम_cpu(ch->sport->sdev->device,
				   recv_ioctx->ioctx.dma,
				   recv_ioctx->ioctx.offset + srp_max_req_size,
				   DMA_FROM_DEVICE);

	srp_cmd = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	opcode = srp_cmd->opcode;
	अगर (opcode == SRP_CMD || opcode == SRP_TSK_MGMT) अणु
		send_ioctx = srpt_get_send_ioctx(ch);
		अगर (unlikely(!send_ioctx))
			जाओ push;
	पूर्ण

	अगर (!list_empty(&recv_ioctx->रुको_list)) अणु
		WARN_ON_ONCE(!ch->processing_रुको_list);
		list_del_init(&recv_ioctx->रुको_list);
	पूर्ण

	चयन (opcode) अणु
	हाल SRP_CMD:
		srpt_handle_cmd(ch, recv_ioctx, send_ioctx);
		अवरोध;
	हाल SRP_TSK_MGMT:
		srpt_handle_tsk_mgmt(ch, recv_ioctx, send_ioctx);
		अवरोध;
	हाल SRP_I_LOGOUT:
		pr_err("Not yet implemented: SRP_I_LOGOUT\n");
		अवरोध;
	हाल SRP_CRED_RSP:
		pr_debug("received SRP_CRED_RSP\n");
		अवरोध;
	हाल SRP_AER_RSP:
		pr_debug("received SRP_AER_RSP\n");
		अवरोध;
	हाल SRP_RSP:
		pr_err("Received SRP_RSP\n");
		अवरोध;
	शेष:
		pr_err("received IU with unknown opcode 0x%x\n", opcode);
		अवरोध;
	पूर्ण

	अगर (!send_ioctx || !send_ioctx->recv_ioctx)
		srpt_post_recv(ch->sport->sdev, ch, recv_ioctx);
	res = true;

out:
	वापस res;

push:
	अगर (list_empty(&recv_ioctx->रुको_list)) अणु
		WARN_ON_ONCE(ch->processing_रुको_list);
		list_add_tail(&recv_ioctx->रुको_list, &ch->cmd_रुको_list);
	पूर्ण
	जाओ out;
पूर्ण

अटल व्योम srpt_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srpt_rdma_ch *ch = wc->qp->qp_context;
	काष्ठा srpt_recv_ioctx *ioctx =
		container_of(wc->wr_cqe, काष्ठा srpt_recv_ioctx, ioctx.cqe);

	अगर (wc->status == IB_WC_SUCCESS) अणु
		पूर्णांक req_lim;

		req_lim = atomic_dec_वापस(&ch->req_lim);
		अगर (unlikely(req_lim < 0))
			pr_err("req_lim = %d < 0\n", req_lim);
		ioctx->byte_len = wc->byte_len;
		srpt_handle_new_iu(ch, ioctx);
	पूर्ण अन्यथा अणु
		pr_info_ratelimited("receiving failed for ioctx %p with status %d\n",
				    ioctx, wc->status);
	पूर्ण
पूर्ण

/*
 * This function must be called from the context in which RDMA completions are
 * processed because it accesses the रुको list without protection against
 * access from other thपढ़ोs.
 */
अटल व्योम srpt_process_रुको_list(काष्ठा srpt_rdma_ch *ch)
अणु
	काष्ठा srpt_recv_ioctx *recv_ioctx, *पंचांगp;

	WARN_ON_ONCE(ch->state == CH_CONNECTING);

	अगर (list_empty(&ch->cmd_रुको_list))
		वापस;

	WARN_ON_ONCE(ch->processing_रुको_list);
	ch->processing_रुको_list = true;
	list_क्रम_each_entry_safe(recv_ioctx, पंचांगp, &ch->cmd_रुको_list,
				 रुको_list) अणु
		अगर (!srpt_handle_new_iu(ch, recv_ioctx))
			अवरोध;
	पूर्ण
	ch->processing_रुको_list = false;
पूर्ण

/**
 * srpt_send_करोne - send completion callback
 * @cq: Completion queue.
 * @wc: Work completion.
 *
 * Note: Although this has not yet been observed during tests, at least in
 * theory it is possible that the srpt_get_send_ioctx() call invoked by
 * srpt_handle_new_iu() fails. This is possible because the req_lim_delta
 * value in each response is set to one, and it is possible that this response
 * makes the initiator send a new request beक्रमe the send completion क्रम that
 * response has been processed. This could e.g. happen अगर the call to
 * srpt_put_send_iotcx() is delayed because of a higher priority पूर्णांकerrupt or
 * अगर IB retransmission causes generation of the send completion to be
 * delayed. Incoming inक्रमmation units क्रम which srpt_get_send_ioctx() fails
 * are queued on cmd_रुको_list. The code below processes these delayed
 * requests one at a समय.
 */
अटल व्योम srpt_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srpt_rdma_ch *ch = wc->qp->qp_context;
	काष्ठा srpt_send_ioctx *ioctx =
		container_of(wc->wr_cqe, काष्ठा srpt_send_ioctx, ioctx.cqe);
	क्रमागत srpt_command_state state;

	state = srpt_set_cmd_state(ioctx, SRPT_STATE_DONE);

	WARN_ON(state != SRPT_STATE_CMD_RSP_SENT &&
		state != SRPT_STATE_MGMT_RSP_SENT);

	atomic_add(1 + ioctx->n_rdma, &ch->sq_wr_avail);

	अगर (wc->status != IB_WC_SUCCESS)
		pr_info("sending response for ioctx 0x%p failed with status %d\n",
			ioctx, wc->status);

	अगर (state != SRPT_STATE_DONE) अणु
		transport_generic_मुक्त_cmd(&ioctx->cmd, 0);
	पूर्ण अन्यथा अणु
		pr_err("IB completion has been received too late for wr_id = %u.\n",
		       ioctx->ioctx.index);
	पूर्ण

	srpt_process_रुको_list(ch);
पूर्ण

/**
 * srpt_create_ch_ib - create receive and send completion queues
 * @ch: SRPT RDMA channel.
 */
अटल पूर्णांक srpt_create_ch_ib(काष्ठा srpt_rdma_ch *ch)
अणु
	काष्ठा ib_qp_init_attr *qp_init;
	काष्ठा srpt_port *sport = ch->sport;
	काष्ठा srpt_device *sdev = sport->sdev;
	स्थिर काष्ठा ib_device_attr *attrs = &sdev->device->attrs;
	पूर्णांक sq_size = sport->port_attrib.srp_sq_size;
	पूर्णांक i, ret;

	WARN_ON(ch->rq_size < 1);

	ret = -ENOMEM;
	qp_init = kzalloc(माप(*qp_init), GFP_KERNEL);
	अगर (!qp_init)
		जाओ out;

retry:
	ch->cq = ib_cq_pool_get(sdev->device, ch->rq_size + sq_size, -1,
				 IB_POLL_WORKQUEUE);
	अगर (IS_ERR(ch->cq)) अणु
		ret = PTR_ERR(ch->cq);
		pr_err("failed to create CQ cqe= %d ret= %d\n",
		       ch->rq_size + sq_size, ret);
		जाओ out;
	पूर्ण
	ch->cq_size = ch->rq_size + sq_size;

	qp_init->qp_context = (व्योम *)ch;
	qp_init->event_handler
		= (व्योम(*)(काष्ठा ib_event *, व्योम*))srpt_qp_event;
	qp_init->send_cq = ch->cq;
	qp_init->recv_cq = ch->cq;
	qp_init->sq_sig_type = IB_SIGNAL_REQ_WR;
	qp_init->qp_type = IB_QPT_RC;
	/*
	 * We भागide up our send queue size पूर्णांकo half SEND WRs to send the
	 * completions, and half R/W contexts to actually करो the RDMA
	 * READ/WRITE transfers.  Note that we need to allocate CQ slots क्रम
	 * both both, as RDMA contexts will also post completions क्रम the
	 * RDMA READ हाल.
	 */
	qp_init->cap.max_send_wr = min(sq_size / 2, attrs->max_qp_wr);
	qp_init->cap.max_rdma_ctxs = sq_size / 2;
	qp_init->cap.max_send_sge = attrs->max_send_sge;
	qp_init->cap.max_recv_sge = 1;
	qp_init->port_num = ch->sport->port;
	अगर (sdev->use_srq)
		qp_init->srq = sdev->srq;
	अन्यथा
		qp_init->cap.max_recv_wr = ch->rq_size;

	अगर (ch->using_rdma_cm) अणु
		ret = rdma_create_qp(ch->rdma_cm.cm_id, sdev->pd, qp_init);
		ch->qp = ch->rdma_cm.cm_id->qp;
	पूर्ण अन्यथा अणु
		ch->qp = ib_create_qp(sdev->pd, qp_init);
		अगर (!IS_ERR(ch->qp)) अणु
			ret = srpt_init_ch_qp(ch, ch->qp);
			अगर (ret)
				ib_destroy_qp(ch->qp);
		पूर्ण अन्यथा अणु
			ret = PTR_ERR(ch->qp);
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		bool retry = sq_size > MIN_SRPT_SQ_SIZE;

		अगर (retry) अणु
			pr_debug("failed to create queue pair with sq_size = %d (%d) - retrying\n",
				 sq_size, ret);
			ib_cq_pool_put(ch->cq, ch->cq_size);
			sq_size = max(sq_size / 2, MIN_SRPT_SQ_SIZE);
			जाओ retry;
		पूर्ण अन्यथा अणु
			pr_err("failed to create queue pair with sq_size = %d (%d)\n",
			       sq_size, ret);
			जाओ err_destroy_cq;
		पूर्ण
	पूर्ण

	atomic_set(&ch->sq_wr_avail, qp_init->cap.max_send_wr);

	pr_debug("%s: max_cqe= %d max_sge= %d sq_size = %d ch= %p\n",
		 __func__, ch->cq->cqe, qp_init->cap.max_send_sge,
		 qp_init->cap.max_send_wr, ch);

	अगर (!sdev->use_srq)
		क्रम (i = 0; i < ch->rq_size; i++)
			srpt_post_recv(sdev, ch, ch->ioctx_recv_ring[i]);

out:
	kमुक्त(qp_init);
	वापस ret;

err_destroy_cq:
	ch->qp = शून्य;
	ib_cq_pool_put(ch->cq, ch->cq_size);
	जाओ out;
पूर्ण

अटल व्योम srpt_destroy_ch_ib(काष्ठा srpt_rdma_ch *ch)
अणु
	ib_destroy_qp(ch->qp);
	ib_cq_pool_put(ch->cq, ch->cq_size);
पूर्ण

/**
 * srpt_बंद_ch - बंद a RDMA channel
 * @ch: SRPT RDMA channel.
 *
 * Make sure all resources associated with the channel will be deallocated at
 * an appropriate समय.
 *
 * Returns true अगर and only अगर the channel state has been modअगरied पूर्णांकo
 * CH_DRAINING.
 */
अटल bool srpt_बंद_ch(काष्ठा srpt_rdma_ch *ch)
अणु
	पूर्णांक ret;

	अगर (!srpt_set_ch_state(ch, CH_DRAINING)) अणु
		pr_debug("%s: already closed\n", ch->sess_name);
		वापस false;
	पूर्ण

	kref_get(&ch->kref);

	ret = srpt_ch_qp_err(ch);
	अगर (ret < 0)
		pr_err("%s-%d: changing queue pair into error state failed: %d\n",
		       ch->sess_name, ch->qp->qp_num, ret);

	ret = srpt_zerolength_ग_लिखो(ch);
	अगर (ret < 0) अणु
		pr_err("%s-%d: queuing zero-length write failed: %d\n",
		       ch->sess_name, ch->qp->qp_num, ret);
		अगर (srpt_set_ch_state(ch, CH_DISCONNECTED))
			schedule_work(&ch->release_work);
		अन्यथा
			WARN_ON_ONCE(true);
	पूर्ण

	kref_put(&ch->kref, srpt_मुक्त_ch);

	वापस true;
पूर्ण

/*
 * Change the channel state पूर्णांकo CH_DISCONNECTING. If a channel has not yet
 * reached the connected state, बंद it. If a channel is in the connected
 * state, send a DREQ. If a DREQ has been received, send a DREP. Note: it is
 * the responsibility of the caller to ensure that this function is not
 * invoked concurrently with the code that accepts a connection. This means
 * that this function must either be invoked from inside a CM callback
 * function or that it must be invoked with the srpt_port.mutex held.
 */
अटल पूर्णांक srpt_disconnect_ch(काष्ठा srpt_rdma_ch *ch)
अणु
	पूर्णांक ret;

	अगर (!srpt_set_ch_state(ch, CH_DISCONNECTING))
		वापस -ENOTCONN;

	अगर (ch->using_rdma_cm) अणु
		ret = rdma_disconnect(ch->rdma_cm.cm_id);
	पूर्ण अन्यथा अणु
		ret = ib_send_cm_dreq(ch->ib_cm.cm_id, शून्य, 0);
		अगर (ret < 0)
			ret = ib_send_cm_drep(ch->ib_cm.cm_id, शून्य, 0);
	पूर्ण

	अगर (ret < 0 && srpt_बंद_ch(ch))
		ret = 0;

	वापस ret;
पूर्ण

/* Send DREQ and रुको क्रम DREP. */
अटल व्योम srpt_disconnect_ch_sync(काष्ठा srpt_rdma_ch *ch)
अणु
	DECLARE_COMPLETION_ONSTACK(बंदd);
	काष्ठा srpt_port *sport = ch->sport;

	pr_debug("ch %s-%d state %d\n", ch->sess_name, ch->qp->qp_num,
		 ch->state);

	ch->बंदd = &बंदd;

	mutex_lock(&sport->mutex);
	srpt_disconnect_ch(ch);
	mutex_unlock(&sport->mutex);

	जबतक (रुको_क्रम_completion_समयout(&बंदd, 5 * HZ) == 0)
		pr_info("%s(%s-%d state %d): still waiting ...\n", __func__,
			ch->sess_name, ch->qp->qp_num, ch->state);

पूर्ण

अटल व्योम __srpt_बंद_all_ch(काष्ठा srpt_port *sport)
अणु
	काष्ठा srpt_nexus *nexus;
	काष्ठा srpt_rdma_ch *ch;

	lockdep_निश्चित_held(&sport->mutex);

	list_क्रम_each_entry(nexus, &sport->nexus_list, entry) अणु
		list_क्रम_each_entry(ch, &nexus->ch_list, list) अणु
			अगर (srpt_disconnect_ch(ch) >= 0)
				pr_info("Closing channel %s-%d because target %s_%d has been disabled\n",
					ch->sess_name, ch->qp->qp_num,
					dev_name(&sport->sdev->device->dev),
					sport->port);
			srpt_बंद_ch(ch);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Look up (i_port_id, t_port_id) in sport->nexus_list. Create an entry अगर
 * it करोes not yet exist.
 */
अटल काष्ठा srpt_nexus *srpt_get_nexus(काष्ठा srpt_port *sport,
					 स्थिर u8 i_port_id[16],
					 स्थिर u8 t_port_id[16])
अणु
	काष्ठा srpt_nexus *nexus = शून्य, *पंचांगp_nexus = शून्य, *n;

	क्रम (;;) अणु
		mutex_lock(&sport->mutex);
		list_क्रम_each_entry(n, &sport->nexus_list, entry) अणु
			अगर (स_भेद(n->i_port_id, i_port_id, 16) == 0 &&
			    स_भेद(n->t_port_id, t_port_id, 16) == 0) अणु
				nexus = n;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!nexus && पंचांगp_nexus) अणु
			list_add_tail_rcu(&पंचांगp_nexus->entry,
					  &sport->nexus_list);
			swap(nexus, पंचांगp_nexus);
		पूर्ण
		mutex_unlock(&sport->mutex);

		अगर (nexus)
			अवरोध;
		पंचांगp_nexus = kzalloc(माप(*nexus), GFP_KERNEL);
		अगर (!पंचांगp_nexus) अणु
			nexus = ERR_PTR(-ENOMEM);
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&पंचांगp_nexus->ch_list);
		स_नकल(पंचांगp_nexus->i_port_id, i_port_id, 16);
		स_नकल(पंचांगp_nexus->t_port_id, t_port_id, 16);
	पूर्ण

	kमुक्त(पंचांगp_nexus);

	वापस nexus;
पूर्ण

अटल व्योम srpt_set_enabled(काष्ठा srpt_port *sport, bool enabled)
	__must_hold(&sport->mutex)
अणु
	lockdep_निश्चित_held(&sport->mutex);

	अगर (sport->enabled == enabled)
		वापस;
	sport->enabled = enabled;
	अगर (!enabled)
		__srpt_बंद_all_ch(sport);
पूर्ण

अटल व्योम srpt_drop_sport_ref(काष्ठा srpt_port *sport)
अणु
	अगर (atomic_dec_वापस(&sport->refcount) == 0 && sport->मुक्तd_channels)
		complete(sport->मुक्तd_channels);
पूर्ण

अटल व्योम srpt_मुक्त_ch(काष्ठा kref *kref)
अणु
	काष्ठा srpt_rdma_ch *ch = container_of(kref, काष्ठा srpt_rdma_ch, kref);

	srpt_drop_sport_ref(ch->sport);
	kमुक्त_rcu(ch, rcu);
पूर्ण

/*
 * Shut करोwn the SCSI target session, tell the connection manager to
 * disconnect the associated RDMA channel, transition the QP to the error
 * state and हटाओ the channel from the channel list. This function is
 * typically called from inside srpt_zerolength_ग_लिखो_करोne(). Concurrent
 * srpt_zerolength_ग_लिखो() calls from inside srpt_बंद_ch() are possible
 * as दीर्घ as the channel is on sport->nexus_list.
 */
अटल व्योम srpt_release_channel_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा srpt_rdma_ch *ch;
	काष्ठा srpt_device *sdev;
	काष्ठा srpt_port *sport;
	काष्ठा se_session *se_sess;

	ch = container_of(w, काष्ठा srpt_rdma_ch, release_work);
	pr_debug("%s-%d\n", ch->sess_name, ch->qp->qp_num);

	sdev = ch->sport->sdev;
	BUG_ON(!sdev);

	se_sess = ch->sess;
	BUG_ON(!se_sess);

	target_stop_session(se_sess);
	target_रुको_क्रम_sess_cmds(se_sess);

	target_हटाओ_session(se_sess);
	ch->sess = शून्य;

	अगर (ch->using_rdma_cm)
		rdma_destroy_id(ch->rdma_cm.cm_id);
	अन्यथा
		ib_destroy_cm_id(ch->ib_cm.cm_id);

	sport = ch->sport;
	mutex_lock(&sport->mutex);
	list_del_rcu(&ch->list);
	mutex_unlock(&sport->mutex);

	अगर (ch->बंदd)
		complete(ch->बंदd);

	srpt_destroy_ch_ib(ch);

	srpt_मुक्त_ioctx_ring((काष्ठा srpt_ioctx **)ch->ioctx_ring,
			     ch->sport->sdev, ch->rq_size,
			     ch->rsp_buf_cache, DMA_TO_DEVICE);

	kmem_cache_destroy(ch->rsp_buf_cache);

	srpt_मुक्त_ioctx_ring((काष्ठा srpt_ioctx **)ch->ioctx_recv_ring,
			     sdev, ch->rq_size,
			     ch->req_buf_cache, DMA_FROM_DEVICE);

	kmem_cache_destroy(ch->req_buf_cache);

	kref_put(&ch->kref, srpt_मुक्त_ch);
पूर्ण

/**
 * srpt_cm_req_recv - process the event IB_CM_REQ_RECEIVED
 * @sdev: HCA through which the login request was received.
 * @ib_cm_id: IB/CM connection identअगरier in हाल of IB/CM.
 * @rdma_cm_id: RDMA/CM connection identअगरier in हाल of RDMA/CM.
 * @port_num: Port through which the REQ message was received.
 * @pkey: P_Key of the incoming connection.
 * @req: SRP login request.
 * @src_addr: GID (IB/CM) or IP address (RDMA/CM) of the port that submitted
 * the login request.
 *
 * Ownership of the cm_id is transferred to the target session अगर this
 * function वापसs zero. Otherwise the caller reमुख्यs the owner of cm_id.
 */
अटल पूर्णांक srpt_cm_req_recv(काष्ठा srpt_device *स्थिर sdev,
			    काष्ठा ib_cm_id *ib_cm_id,
			    काष्ठा rdma_cm_id *rdma_cm_id,
			    u8 port_num, __be16 pkey,
			    स्थिर काष्ठा srp_login_req *req,
			    स्थिर अक्षर *src_addr)
अणु
	काष्ठा srpt_port *sport = &sdev->port[port_num - 1];
	काष्ठा srpt_nexus *nexus;
	काष्ठा srp_login_rsp *rsp = शून्य;
	काष्ठा srp_login_rej *rej = शून्य;
	जोड़ अणु
		काष्ठा rdma_conn_param rdma_cm;
		काष्ठा ib_cm_rep_param ib_cm;
	पूर्ण *rep_param = शून्य;
	काष्ठा srpt_rdma_ch *ch = शून्य;
	अक्षर i_port_id[36];
	u32 it_iu_len;
	पूर्णांक i, tag_num, tag_size, ret;
	काष्ठा srpt_tpg *stpg;

	WARN_ON_ONCE(irqs_disabled());

	it_iu_len = be32_to_cpu(req->req_it_iu_len);

	pr_info("Received SRP_LOGIN_REQ with i_port_id %pI6, t_port_id %pI6 and it_iu_len %d on port %d (guid=%pI6); pkey %#04x\n",
		req->initiator_port_id, req->target_port_id, it_iu_len,
		port_num, &sport->gid, be16_to_cpu(pkey));

	nexus = srpt_get_nexus(sport, req->initiator_port_id,
			       req->target_port_id);
	अगर (IS_ERR(nexus)) अणु
		ret = PTR_ERR(nexus);
		जाओ out;
	पूर्ण

	ret = -ENOMEM;
	rsp = kzalloc(माप(*rsp), GFP_KERNEL);
	rej = kzalloc(माप(*rej), GFP_KERNEL);
	rep_param = kzalloc(माप(*rep_param), GFP_KERNEL);
	अगर (!rsp || !rej || !rep_param)
		जाओ out;

	ret = -EINVAL;
	अगर (it_iu_len > srp_max_req_size || it_iu_len < 64) अणु
		rej->reason = cpu_to_be32(
				SRP_LOGIN_REJ_REQ_IT_IU_LENGTH_TOO_LARGE);
		pr_err("rejected SRP_LOGIN_REQ because its length (%d bytes) is out of range (%d .. %d)\n",
		       it_iu_len, 64, srp_max_req_size);
		जाओ reject;
	पूर्ण

	अगर (!sport->enabled) अणु
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_info("rejected SRP_LOGIN_REQ because target port %s_%d has not yet been enabled\n",
			dev_name(&sport->sdev->device->dev), port_num);
		जाओ reject;
	पूर्ण

	अगर (*(__be64 *)req->target_port_id != cpu_to_be64(srpt_service_guid)
	    || *(__be64 *)(req->target_port_id + 8) !=
	       cpu_to_be64(srpt_service_guid)) अणु
		rej->reason = cpu_to_be32(
				SRP_LOGIN_REJ_UNABLE_ASSOCIATE_CHANNEL);
		pr_err("rejected SRP_LOGIN_REQ because it has an invalid target port identifier.\n");
		जाओ reject;
	पूर्ण

	ret = -ENOMEM;
	ch = kzalloc(माप(*ch), GFP_KERNEL);
	अगर (!ch) अणु
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because out of memory.\n");
		जाओ reject;
	पूर्ण

	kref_init(&ch->kref);
	ch->pkey = be16_to_cpu(pkey);
	ch->nexus = nexus;
	ch->zw_cqe.करोne = srpt_zerolength_ग_लिखो_करोne;
	INIT_WORK(&ch->release_work, srpt_release_channel_work);
	ch->sport = sport;
	अगर (ib_cm_id) अणु
		ch->ib_cm.cm_id = ib_cm_id;
		ib_cm_id->context = ch;
	पूर्ण अन्यथा अणु
		ch->using_rdma_cm = true;
		ch->rdma_cm.cm_id = rdma_cm_id;
		rdma_cm_id->context = ch;
	पूर्ण
	/*
	 * ch->rq_size should be at least as large as the initiator queue
	 * depth to aव्योम that the initiator driver has to report QUEUE_FULL
	 * to the SCSI mid-layer.
	 */
	ch->rq_size = min(MAX_SRPT_RQ_SIZE, sdev->device->attrs.max_qp_wr);
	spin_lock_init(&ch->spinlock);
	ch->state = CH_CONNECTING;
	INIT_LIST_HEAD(&ch->cmd_रुको_list);
	ch->max_rsp_size = ch->sport->port_attrib.srp_max_rsp_size;

	ch->rsp_buf_cache = kmem_cache_create("srpt-rsp-buf", ch->max_rsp_size,
					      512, 0, शून्य);
	अगर (!ch->rsp_buf_cache)
		जाओ मुक्त_ch;

	ch->ioctx_ring = (काष्ठा srpt_send_ioctx **)
		srpt_alloc_ioctx_ring(ch->sport->sdev, ch->rq_size,
				      माप(*ch->ioctx_ring[0]),
				      ch->rsp_buf_cache, 0, DMA_TO_DEVICE);
	अगर (!ch->ioctx_ring) अणु
		pr_err("rejected SRP_LOGIN_REQ because creating a new QP SQ ring failed.\n");
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		जाओ मुक्त_rsp_cache;
	पूर्ण

	क्रम (i = 0; i < ch->rq_size; i++)
		ch->ioctx_ring[i]->ch = ch;
	अगर (!sdev->use_srq) अणु
		u16 imm_data_offset = req->req_flags & SRP_IMMED_REQUESTED ?
			be16_to_cpu(req->imm_data_offset) : 0;
		u16 alignment_offset;
		u32 req_sz;

		अगर (req->req_flags & SRP_IMMED_REQUESTED)
			pr_debug("imm_data_offset = %d\n",
				 be16_to_cpu(req->imm_data_offset));
		अगर (imm_data_offset >= माप(काष्ठा srp_cmd)) अणु
			ch->imm_data_offset = imm_data_offset;
			rsp->rsp_flags |= SRP_LOGIN_RSP_IMMED_SUPP;
		पूर्ण अन्यथा अणु
			ch->imm_data_offset = 0;
		पूर्ण
		alignment_offset = round_up(imm_data_offset, 512) -
			imm_data_offset;
		req_sz = alignment_offset + imm_data_offset + srp_max_req_size;
		ch->req_buf_cache = kmem_cache_create("srpt-req-buf", req_sz,
						      512, 0, शून्य);
		अगर (!ch->req_buf_cache)
			जाओ मुक्त_rsp_ring;

		ch->ioctx_recv_ring = (काष्ठा srpt_recv_ioctx **)
			srpt_alloc_ioctx_ring(ch->sport->sdev, ch->rq_size,
					      माप(*ch->ioctx_recv_ring[0]),
					      ch->req_buf_cache,
					      alignment_offset,
					      DMA_FROM_DEVICE);
		अगर (!ch->ioctx_recv_ring) अणु
			pr_err("rejected SRP_LOGIN_REQ because creating a new QP RQ ring failed.\n");
			rej->reason =
			    cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
			जाओ मुक्त_recv_cache;
		पूर्ण
		क्रम (i = 0; i < ch->rq_size; i++)
			INIT_LIST_HEAD(&ch->ioctx_recv_ring[i]->रुको_list);
	पूर्ण

	ret = srpt_create_ch_ib(ch);
	अगर (ret) अणु
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because creating a new RDMA channel failed.\n");
		जाओ मुक्त_recv_ring;
	पूर्ण

	strlcpy(ch->sess_name, src_addr, माप(ch->sess_name));
	snम_लिखो(i_port_id, माप(i_port_id), "0x%016llx%016llx",
			be64_to_cpu(*(__be64 *)nexus->i_port_id),
			be64_to_cpu(*(__be64 *)(nexus->i_port_id + 8)));

	pr_debug("registering src addr %s or i_port_id %s\n", ch->sess_name,
		 i_port_id);

	tag_num = ch->rq_size;
	tag_size = 1; /* ib_srpt करोes not use se_sess->sess_cmd_map */

	mutex_lock(&sport->port_guid_id.mutex);
	list_क्रम_each_entry(stpg, &sport->port_guid_id.tpg_list, entry) अणु
		अगर (!IS_ERR_OR_शून्य(ch->sess))
			अवरोध;
		ch->sess = target_setup_session(&stpg->tpg, tag_num,
						tag_size, TARGET_PROT_NORMAL,
						ch->sess_name, ch, शून्य);
	पूर्ण
	mutex_unlock(&sport->port_guid_id.mutex);

	mutex_lock(&sport->port_gid_id.mutex);
	list_क्रम_each_entry(stpg, &sport->port_gid_id.tpg_list, entry) अणु
		अगर (!IS_ERR_OR_शून्य(ch->sess))
			अवरोध;
		ch->sess = target_setup_session(&stpg->tpg, tag_num,
					tag_size, TARGET_PROT_NORMAL, i_port_id,
					ch, शून्य);
		अगर (!IS_ERR_OR_शून्य(ch->sess))
			अवरोध;
		/* Retry without leading "0x" */
		ch->sess = target_setup_session(&stpg->tpg, tag_num,
						tag_size, TARGET_PROT_NORMAL,
						i_port_id + 2, ch, शून्य);
	पूर्ण
	mutex_unlock(&sport->port_gid_id.mutex);

	अगर (IS_ERR_OR_शून्य(ch->sess)) अणु
		WARN_ON_ONCE(ch->sess == शून्य);
		ret = PTR_ERR(ch->sess);
		ch->sess = शून्य;
		pr_info("Rejected login for initiator %s: ret = %d.\n",
			ch->sess_name, ret);
		rej->reason = cpu_to_be32(ret == -ENOMEM ?
				SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES :
				SRP_LOGIN_REJ_CHANNEL_LIMIT_REACHED);
		जाओ destroy_ib;
	पूर्ण

	/*
	 * Once a session has been created deकाष्ठाion of srpt_rdma_ch objects
	 * will decrement sport->refcount. Hence increment sport->refcount now.
	 */
	atomic_inc(&sport->refcount);

	mutex_lock(&sport->mutex);

	अगर ((req->req_flags & SRP_MTCH_ACTION) == SRP_MULTICHAN_SINGLE) अणु
		काष्ठा srpt_rdma_ch *ch2;

		list_क्रम_each_entry(ch2, &nexus->ch_list, list) अणु
			अगर (srpt_disconnect_ch(ch2) < 0)
				जारी;
			pr_info("Relogin - closed existing channel %s\n",
				ch2->sess_name);
			rsp->rsp_flags |= SRP_LOGIN_RSP_MULTICHAN_TERMINATED;
		पूर्ण
	पूर्ण अन्यथा अणु
		rsp->rsp_flags |= SRP_LOGIN_RSP_MULTICHAN_MAINTAINED;
	पूर्ण

	list_add_tail_rcu(&ch->list, &nexus->ch_list);

	अगर (!sport->enabled) अणु
		rej->reason = cpu_to_be32(
				SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_info("rejected SRP_LOGIN_REQ because target %s_%d is not enabled\n",
			dev_name(&sdev->device->dev), port_num);
		mutex_unlock(&sport->mutex);
		ret = -EINVAL;
		जाओ reject;
	पूर्ण

	mutex_unlock(&sport->mutex);

	ret = ch->using_rdma_cm ? 0 : srpt_ch_qp_rtr(ch, ch->qp);
	अगर (ret) अणु
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("rejected SRP_LOGIN_REQ because enabling RTR failed (error code = %d)\n",
		       ret);
		जाओ reject;
	पूर्ण

	pr_debug("Establish connection sess=%p name=%s ch=%p\n", ch->sess,
		 ch->sess_name, ch);

	/* create srp_login_response */
	rsp->opcode = SRP_LOGIN_RSP;
	rsp->tag = req->tag;
	rsp->max_it_iu_len = cpu_to_be32(srp_max_req_size);
	rsp->max_ti_iu_len = req->req_it_iu_len;
	ch->max_ti_iu_len = it_iu_len;
	rsp->buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_सूचीECT |
				   SRP_BUF_FORMAT_INसूचीECT);
	rsp->req_lim_delta = cpu_to_be32(ch->rq_size);
	atomic_set(&ch->req_lim, ch->rq_size);
	atomic_set(&ch->req_lim_delta, 0);

	/* create cm reply */
	अगर (ch->using_rdma_cm) अणु
		rep_param->rdma_cm.निजी_data = (व्योम *)rsp;
		rep_param->rdma_cm.निजी_data_len = माप(*rsp);
		rep_param->rdma_cm.rnr_retry_count = 7;
		rep_param->rdma_cm.flow_control = 1;
		rep_param->rdma_cm.responder_resources = 4;
		rep_param->rdma_cm.initiator_depth = 4;
	पूर्ण अन्यथा अणु
		rep_param->ib_cm.qp_num = ch->qp->qp_num;
		rep_param->ib_cm.निजी_data = (व्योम *)rsp;
		rep_param->ib_cm.निजी_data_len = माप(*rsp);
		rep_param->ib_cm.rnr_retry_count = 7;
		rep_param->ib_cm.flow_control = 1;
		rep_param->ib_cm.failover_accepted = 0;
		rep_param->ib_cm.srq = 1;
		rep_param->ib_cm.responder_resources = 4;
		rep_param->ib_cm.initiator_depth = 4;
	पूर्ण

	/*
	 * Hold the sport mutex जबतक accepting a connection to aव्योम that
	 * srpt_disconnect_ch() is invoked concurrently with this code.
	 */
	mutex_lock(&sport->mutex);
	अगर (sport->enabled && ch->state == CH_CONNECTING) अणु
		अगर (ch->using_rdma_cm)
			ret = rdma_accept(rdma_cm_id, &rep_param->rdma_cm);
		अन्यथा
			ret = ib_send_cm_rep(ib_cm_id, &rep_param->ib_cm);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&sport->mutex);

	चयन (ret) अणु
	हाल 0:
		अवरोध;
	हाल -EINVAL:
		जाओ reject;
	शेष:
		rej->reason = cpu_to_be32(SRP_LOGIN_REJ_INSUFFICIENT_RESOURCES);
		pr_err("sending SRP_LOGIN_REQ response failed (error code = %d)\n",
		       ret);
		जाओ reject;
	पूर्ण

	जाओ out;

destroy_ib:
	srpt_destroy_ch_ib(ch);

मुक्त_recv_ring:
	srpt_मुक्त_ioctx_ring((काष्ठा srpt_ioctx **)ch->ioctx_recv_ring,
			     ch->sport->sdev, ch->rq_size,
			     ch->req_buf_cache, DMA_FROM_DEVICE);

मुक्त_recv_cache:
	kmem_cache_destroy(ch->req_buf_cache);

मुक्त_rsp_ring:
	srpt_मुक्त_ioctx_ring((काष्ठा srpt_ioctx **)ch->ioctx_ring,
			     ch->sport->sdev, ch->rq_size,
			     ch->rsp_buf_cache, DMA_TO_DEVICE);

मुक्त_rsp_cache:
	kmem_cache_destroy(ch->rsp_buf_cache);

मुक्त_ch:
	अगर (rdma_cm_id)
		rdma_cm_id->context = शून्य;
	अन्यथा
		ib_cm_id->context = शून्य;
	kमुक्त(ch);
	ch = शून्य;

	WARN_ON_ONCE(ret == 0);

reject:
	pr_info("Rejecting login with reason %#x\n", be32_to_cpu(rej->reason));
	rej->opcode = SRP_LOGIN_REJ;
	rej->tag = req->tag;
	rej->buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_सूचीECT |
				   SRP_BUF_FORMAT_INसूचीECT);

	अगर (rdma_cm_id)
		rdma_reject(rdma_cm_id, rej, माप(*rej),
			    IB_CM_REJ_CONSUMER_DEFINED);
	अन्यथा
		ib_send_cm_rej(ib_cm_id, IB_CM_REJ_CONSUMER_DEFINED, शून्य, 0,
			       rej, माप(*rej));

	अगर (ch && ch->sess) अणु
		srpt_बंद_ch(ch);
		/*
		 * Tell the caller not to मुक्त cm_id since
		 * srpt_release_channel_work() will करो that.
		 */
		ret = 0;
	पूर्ण

out:
	kमुक्त(rep_param);
	kमुक्त(rsp);
	kमुक्त(rej);

	वापस ret;
पूर्ण

अटल पूर्णांक srpt_ib_cm_req_recv(काष्ठा ib_cm_id *cm_id,
			       स्थिर काष्ठा ib_cm_req_event_param *param,
			       व्योम *निजी_data)
अणु
	अक्षर sguid[40];

	srpt_क्रमmat_guid(sguid, माप(sguid),
			 &param->primary_path->dgid.global.पूर्णांकerface_id);

	वापस srpt_cm_req_recv(cm_id->context, cm_id, शून्य, param->port,
				param->primary_path->pkey,
				निजी_data, sguid);
पूर्ण

अटल पूर्णांक srpt_rdma_cm_req_recv(काष्ठा rdma_cm_id *cm_id,
				 काष्ठा rdma_cm_event *event)
अणु
	काष्ठा srpt_device *sdev;
	काष्ठा srp_login_req req;
	स्थिर काष्ठा srp_login_req_rdma *req_rdma;
	काष्ठा sa_path_rec *path_rec = cm_id->route.path_rec;
	अक्षर src_addr[40];

	sdev = ib_get_client_data(cm_id->device, &srpt_client);
	अगर (!sdev)
		वापस -ECONNREFUSED;

	अगर (event->param.conn.निजी_data_len < माप(*req_rdma))
		वापस -EINVAL;

	/* Transक्रमm srp_login_req_rdma पूर्णांकo srp_login_req. */
	req_rdma = event->param.conn.निजी_data;
	स_रखो(&req, 0, माप(req));
	req.opcode		= req_rdma->opcode;
	req.tag			= req_rdma->tag;
	req.req_it_iu_len	= req_rdma->req_it_iu_len;
	req.req_buf_fmt		= req_rdma->req_buf_fmt;
	req.req_flags		= req_rdma->req_flags;
	स_नकल(req.initiator_port_id, req_rdma->initiator_port_id, 16);
	स_नकल(req.target_port_id, req_rdma->target_port_id, 16);
	req.imm_data_offset	= req_rdma->imm_data_offset;

	snम_लिखो(src_addr, माप(src_addr), "%pIS",
		 &cm_id->route.addr.src_addr);

	वापस srpt_cm_req_recv(sdev, शून्य, cm_id, cm_id->port_num,
				path_rec ? path_rec->pkey : 0, &req, src_addr);
पूर्ण

अटल व्योम srpt_cm_rej_recv(काष्ठा srpt_rdma_ch *ch,
			     क्रमागत ib_cm_rej_reason reason,
			     स्थिर u8 *निजी_data,
			     u8 निजी_data_len)
अणु
	अक्षर *priv = शून्य;
	पूर्णांक i;

	अगर (निजी_data_len && (priv = kदो_स्मृति(निजी_data_len * 3 + 1,
						GFP_KERNEL))) अणु
		क्रम (i = 0; i < निजी_data_len; i++)
			प्र_लिखो(priv + 3 * i, " %02x", निजी_data[i]);
	पूर्ण
	pr_info("Received CM REJ for ch %s-%d; reason %d%s%s.\n",
		ch->sess_name, ch->qp->qp_num, reason, निजी_data_len ?
		"; private data" : "", priv ? priv : " (?)");
	kमुक्त(priv);
पूर्ण

/**
 * srpt_cm_rtu_recv - process an IB_CM_RTU_RECEIVED or USER_ESTABLISHED event
 * @ch: SRPT RDMA channel.
 *
 * An RTU (पढ़ोy to use) message indicates that the connection has been
 * established and that the recipient may begin transmitting.
 */
अटल व्योम srpt_cm_rtu_recv(काष्ठा srpt_rdma_ch *ch)
अणु
	पूर्णांक ret;

	ret = ch->using_rdma_cm ? 0 : srpt_ch_qp_rts(ch, ch->qp);
	अगर (ret < 0) अणु
		pr_err("%s-%d: QP transition to RTS failed\n", ch->sess_name,
		       ch->qp->qp_num);
		srpt_बंद_ch(ch);
		वापस;
	पूर्ण

	/*
	 * Note: calling srpt_बंद_ch() अगर the transition to the LIVE state
	 * fails is not necessary since that means that that function has
	 * alपढ़ोy been invoked from another thपढ़ो.
	 */
	अगर (!srpt_set_ch_state(ch, CH_LIVE)) अणु
		pr_err("%s-%d: channel transition to LIVE state failed\n",
		       ch->sess_name, ch->qp->qp_num);
		वापस;
	पूर्ण

	/* Trigger रुको list processing. */
	ret = srpt_zerolength_ग_लिखो(ch);
	WARN_ONCE(ret < 0, "%d\n", ret);
पूर्ण

/**
 * srpt_cm_handler - IB connection manager callback function
 * @cm_id: IB/CM connection identअगरier.
 * @event: IB/CM event.
 *
 * A non-zero वापस value will cause the caller destroy the CM ID.
 *
 * Note: srpt_cm_handler() must only वापस a non-zero value when transferring
 * ownership of the cm_id to a channel by srpt_cm_req_recv() failed. Returning
 * a non-zero value in any other हाल will trigger a race with the
 * ib_destroy_cm_id() call in srpt_release_channel().
 */
अटल पूर्णांक srpt_cm_handler(काष्ठा ib_cm_id *cm_id,
			   स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा srpt_rdma_ch *ch = cm_id->context;
	पूर्णांक ret;

	ret = 0;
	चयन (event->event) अणु
	हाल IB_CM_REQ_RECEIVED:
		ret = srpt_ib_cm_req_recv(cm_id, &event->param.req_rcvd,
					  event->निजी_data);
		अवरोध;
	हाल IB_CM_REJ_RECEIVED:
		srpt_cm_rej_recv(ch, event->param.rej_rcvd.reason,
				 event->निजी_data,
				 IB_CM_REJ_PRIVATE_DATA_SIZE);
		अवरोध;
	हाल IB_CM_RTU_RECEIVED:
	हाल IB_CM_USER_ESTABLISHED:
		srpt_cm_rtu_recv(ch);
		अवरोध;
	हाल IB_CM_DREQ_RECEIVED:
		srpt_disconnect_ch(ch);
		अवरोध;
	हाल IB_CM_DREP_RECEIVED:
		pr_info("Received CM DREP message for ch %s-%d.\n",
			ch->sess_name, ch->qp->qp_num);
		srpt_बंद_ch(ch);
		अवरोध;
	हाल IB_CM_TIMEWAIT_EXIT:
		pr_info("Received CM TimeWait exit for ch %s-%d.\n",
			ch->sess_name, ch->qp->qp_num);
		srpt_बंद_ch(ch);
		अवरोध;
	हाल IB_CM_REP_ERROR:
		pr_info("Received CM REP error for ch %s-%d.\n", ch->sess_name,
			ch->qp->qp_num);
		अवरोध;
	हाल IB_CM_DREQ_ERROR:
		pr_info("Received CM DREQ ERROR event.\n");
		अवरोध;
	हाल IB_CM_MRA_RECEIVED:
		pr_info("Received CM MRA event\n");
		अवरोध;
	शेष:
		pr_err("received unrecognized CM event %d\n", event->event);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक srpt_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
				काष्ठा rdma_cm_event *event)
अणु
	काष्ठा srpt_rdma_ch *ch = cm_id->context;
	पूर्णांक ret = 0;

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = srpt_rdma_cm_req_recv(cm_id, event);
		अवरोध;
	हाल RDMA_CM_EVENT_REJECTED:
		srpt_cm_rej_recv(ch, event->status,
				 event->param.conn.निजी_data,
				 event->param.conn.निजी_data_len);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		srpt_cm_rtu_recv(ch);
		अवरोध;
	हाल RDMA_CM_EVENT_DISCONNECTED:
		अगर (ch->state < CH_DISCONNECTING)
			srpt_disconnect_ch(ch);
		अन्यथा
			srpt_बंद_ch(ch);
		अवरोध;
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		srpt_बंद_ch(ch);
		अवरोध;
	हाल RDMA_CM_EVENT_UNREACHABLE:
		pr_info("Received CM REP error for ch %s-%d.\n", ch->sess_name,
			ch->qp->qp_num);
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
		अवरोध;
	शेष:
		pr_err("received unrecognized RDMA CM event %d\n",
		       event->event);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * srpt_ग_लिखो_pending - Start data transfer from initiator to target (ग_लिखो).
 */
अटल पूर्णांक srpt_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx =
		container_of(se_cmd, काष्ठा srpt_send_ioctx, cmd);
	काष्ठा srpt_rdma_ch *ch = ioctx->ch;
	काष्ठा ib_send_wr *first_wr = शून्य;
	काष्ठा ib_cqe *cqe = &ioctx->rdma_cqe;
	क्रमागत srpt_command_state new_state;
	पूर्णांक ret, i;

	अगर (ioctx->recv_ioctx) अणु
		srpt_set_cmd_state(ioctx, SRPT_STATE_DATA_IN);
		target_execute_cmd(&ioctx->cmd);
		वापस 0;
	पूर्ण

	new_state = srpt_set_cmd_state(ioctx, SRPT_STATE_NEED_DATA);
	WARN_ON(new_state == SRPT_STATE_DONE);

	अगर (atomic_sub_वापस(ioctx->n_rdma, &ch->sq_wr_avail) < 0) अणु
		pr_warn("%s: IB send queue full (needed %d)\n",
				__func__, ioctx->n_rdma);
		ret = -ENOMEM;
		जाओ out_unकरो;
	पूर्ण

	cqe->करोne = srpt_rdma_पढ़ो_करोne;
	क्रम (i = ioctx->n_rw_ctx - 1; i >= 0; i--) अणु
		काष्ठा srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];

		first_wr = rdma_rw_ctx_wrs(&ctx->rw, ch->qp, ch->sport->port,
				cqe, first_wr);
		cqe = शून्य;
	पूर्ण

	ret = ib_post_send(ch->qp, first_wr, शून्य);
	अगर (ret) अणु
		pr_err("%s: ib_post_send() returned %d for %d (avail: %d)\n",
			 __func__, ret, ioctx->n_rdma,
			 atomic_पढ़ो(&ch->sq_wr_avail));
		जाओ out_unकरो;
	पूर्ण

	वापस 0;
out_unकरो:
	atomic_add(ioctx->n_rdma, &ch->sq_wr_avail);
	वापस ret;
पूर्ण

अटल u8 tcm_to_srp_tsk_mgmt_status(स्थिर पूर्णांक tcm_mgmt_status)
अणु
	चयन (tcm_mgmt_status) अणु
	हाल TMR_FUNCTION_COMPLETE:
		वापस SRP_TSK_MGMT_SUCCESS;
	हाल TMR_FUNCTION_REJECTED:
		वापस SRP_TSK_MGMT_FUNC_NOT_SUPP;
	पूर्ण
	वापस SRP_TSK_MGMT_FAILED;
पूर्ण

/**
 * srpt_queue_response - transmit the response to a SCSI command
 * @cmd: SCSI target command.
 *
 * Callback function called by the TCM core. Must not block since it can be
 * invoked on the context of the IB completion handler.
 */
अटल व्योम srpt_queue_response(काष्ठा se_cmd *cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx =
		container_of(cmd, काष्ठा srpt_send_ioctx, cmd);
	काष्ठा srpt_rdma_ch *ch = ioctx->ch;
	काष्ठा srpt_device *sdev = ch->sport->sdev;
	काष्ठा ib_send_wr send_wr, *first_wr = &send_wr;
	काष्ठा ib_sge sge;
	क्रमागत srpt_command_state state;
	पूर्णांक resp_len, ret, i;
	u8 srp_पंचांग_status;

	state = ioctx->state;
	चयन (state) अणु
	हाल SRPT_STATE_NEW:
	हाल SRPT_STATE_DATA_IN:
		ioctx->state = SRPT_STATE_CMD_RSP_SENT;
		अवरोध;
	हाल SRPT_STATE_MGMT:
		ioctx->state = SRPT_STATE_MGMT_RSP_SENT;
		अवरोध;
	शेष:
		WARN(true, "ch %p; cmd %d: unexpected command state %d\n",
			ch, ioctx->ioctx.index, ioctx->state);
		अवरोध;
	पूर्ण

	अगर (WARN_ON_ONCE(state == SRPT_STATE_CMD_RSP_SENT))
		वापस;

	/* For पढ़ो commands, transfer the data to the initiator. */
	अगर (ioctx->cmd.data_direction == DMA_FROM_DEVICE &&
	    ioctx->cmd.data_length &&
	    !ioctx->queue_status_only) अणु
		क्रम (i = ioctx->n_rw_ctx - 1; i >= 0; i--) अणु
			काष्ठा srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];

			first_wr = rdma_rw_ctx_wrs(&ctx->rw, ch->qp,
					ch->sport->port, शून्य, first_wr);
		पूर्ण
	पूर्ण

	अगर (state != SRPT_STATE_MGMT)
		resp_len = srpt_build_cmd_rsp(ch, ioctx, ioctx->cmd.tag,
					      cmd->scsi_status);
	अन्यथा अणु
		srp_पंचांग_status
			= tcm_to_srp_tsk_mgmt_status(cmd->se_पंचांगr_req->response);
		resp_len = srpt_build_tskmgmt_rsp(ch, ioctx, srp_पंचांग_status,
						 ioctx->cmd.tag);
	पूर्ण

	atomic_inc(&ch->req_lim);

	अगर (unlikely(atomic_sub_वापस(1 + ioctx->n_rdma,
			&ch->sq_wr_avail) < 0)) अणु
		pr_warn("%s: IB send queue full (needed %d)\n",
				__func__, ioctx->n_rdma);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ib_dma_sync_single_क्रम_device(sdev->device, ioctx->ioctx.dma, resp_len,
				      DMA_TO_DEVICE);

	sge.addr = ioctx->ioctx.dma;
	sge.length = resp_len;
	sge.lkey = sdev->lkey;

	ioctx->ioctx.cqe.करोne = srpt_send_करोne;
	send_wr.next = शून्य;
	send_wr.wr_cqe = &ioctx->ioctx.cqe;
	send_wr.sg_list = &sge;
	send_wr.num_sge = 1;
	send_wr.opcode = IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(ch->qp, first_wr, शून्य);
	अगर (ret < 0) अणु
		pr_err("%s: sending cmd response failed for tag %llu (%d)\n",
			__func__, ioctx->cmd.tag, ret);
		जाओ out;
	पूर्ण

	वापस;

out:
	atomic_add(1 + ioctx->n_rdma, &ch->sq_wr_avail);
	atomic_dec(&ch->req_lim);
	srpt_set_cmd_state(ioctx, SRPT_STATE_DONE);
	target_put_sess_cmd(&ioctx->cmd);
पूर्ण

अटल पूर्णांक srpt_queue_data_in(काष्ठा se_cmd *cmd)
अणु
	srpt_queue_response(cmd);
	वापस 0;
पूर्ण

अटल व्योम srpt_queue_पंचांग_rsp(काष्ठा se_cmd *cmd)
अणु
	srpt_queue_response(cmd);
पूर्ण

/*
 * This function is called क्रम पातed commands अगर no response is sent to the
 * initiator. Make sure that the credits मुक्तd by पातing a command are
 * वापसed to the initiator the next समय a response is sent by incrementing
 * ch->req_lim_delta.
 */
अटल व्योम srpt_पातed_task(काष्ठा se_cmd *cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx = container_of(cmd,
				काष्ठा srpt_send_ioctx, cmd);
	काष्ठा srpt_rdma_ch *ch = ioctx->ch;

	atomic_inc(&ch->req_lim_delta);
पूर्ण

अटल पूर्णांक srpt_queue_status(काष्ठा se_cmd *cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx;

	ioctx = container_of(cmd, काष्ठा srpt_send_ioctx, cmd);
	BUG_ON(ioctx->sense_data != cmd->sense_buffer);
	अगर (cmd->se_cmd_flags &
	    (SCF_TRANSPORT_TASK_SENSE | SCF_EMULATED_TASK_SENSE))
		WARN_ON(cmd->scsi_status != SAM_STAT_CHECK_CONDITION);
	ioctx->queue_status_only = true;
	srpt_queue_response(cmd);
	वापस 0;
पूर्ण

अटल व्योम srpt_refresh_port_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srpt_port *sport = container_of(work, काष्ठा srpt_port, work);

	srpt_refresh_port(sport);
पूर्ण

/**
 * srpt_release_sport - disable login and रुको क्रम associated channels
 * @sport: SRPT HCA port.
 */
अटल पूर्णांक srpt_release_sport(काष्ठा srpt_port *sport)
अणु
	DECLARE_COMPLETION_ONSTACK(c);
	काष्ठा srpt_nexus *nexus, *next_n;
	काष्ठा srpt_rdma_ch *ch;

	WARN_ON_ONCE(irqs_disabled());

	sport->मुक्तd_channels = &c;

	mutex_lock(&sport->mutex);
	srpt_set_enabled(sport, false);
	mutex_unlock(&sport->mutex);

	जबतक (atomic_पढ़ो(&sport->refcount) > 0 &&
	       रुको_क्रम_completion_समयout(&c, 5 * HZ) <= 0) अणु
		pr_info("%s_%d: waiting for unregistration of %d sessions ...\n",
			dev_name(&sport->sdev->device->dev), sport->port,
			atomic_पढ़ो(&sport->refcount));
		rcu_पढ़ो_lock();
		list_क्रम_each_entry(nexus, &sport->nexus_list, entry) अणु
			list_क्रम_each_entry(ch, &nexus->ch_list, list) अणु
				pr_info("%s-%d: state %s\n",
					ch->sess_name, ch->qp->qp_num,
					get_ch_state_name(ch->state));
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	mutex_lock(&sport->mutex);
	list_क्रम_each_entry_safe(nexus, next_n, &sport->nexus_list, entry) अणु
		list_del(&nexus->entry);
		kमुक्त_rcu(nexus, rcu);
	पूर्ण
	mutex_unlock(&sport->mutex);

	वापस 0;
पूर्ण

अटल काष्ठा se_wwn *__srpt_lookup_wwn(स्थिर अक्षर *name)
अणु
	काष्ठा ib_device *dev;
	काष्ठा srpt_device *sdev;
	काष्ठा srpt_port *sport;
	पूर्णांक i;

	list_क्रम_each_entry(sdev, &srpt_dev_list, list) अणु
		dev = sdev->device;
		अगर (!dev)
			जारी;

		क्रम (i = 0; i < dev->phys_port_cnt; i++) अणु
			sport = &sdev->port[i];

			अगर (म_भेद(sport->port_guid_id.name, name) == 0)
				वापस &sport->port_guid_id.wwn;
			अगर (म_भेद(sport->port_gid_id.name, name) == 0)
				वापस &sport->port_gid_id.wwn;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा se_wwn *srpt_lookup_wwn(स्थिर अक्षर *name)
अणु
	काष्ठा se_wwn *wwn;

	spin_lock(&srpt_dev_lock);
	wwn = __srpt_lookup_wwn(name);
	spin_unlock(&srpt_dev_lock);

	वापस wwn;
पूर्ण

अटल व्योम srpt_मुक्त_srq(काष्ठा srpt_device *sdev)
अणु
	अगर (!sdev->srq)
		वापस;

	ib_destroy_srq(sdev->srq);
	srpt_मुक्त_ioctx_ring((काष्ठा srpt_ioctx **)sdev->ioctx_ring, sdev,
			     sdev->srq_size, sdev->req_buf_cache,
			     DMA_FROM_DEVICE);
	kmem_cache_destroy(sdev->req_buf_cache);
	sdev->srq = शून्य;
पूर्ण

अटल पूर्णांक srpt_alloc_srq(काष्ठा srpt_device *sdev)
अणु
	काष्ठा ib_srq_init_attr srq_attr = अणु
		.event_handler = srpt_srq_event,
		.srq_context = (व्योम *)sdev,
		.attr.max_wr = sdev->srq_size,
		.attr.max_sge = 1,
		.srq_type = IB_SRQT_BASIC,
	पूर्ण;
	काष्ठा ib_device *device = sdev->device;
	काष्ठा ib_srq *srq;
	पूर्णांक i;

	WARN_ON_ONCE(sdev->srq);
	srq = ib_create_srq(sdev->pd, &srq_attr);
	अगर (IS_ERR(srq)) अणु
		pr_debug("ib_create_srq() failed: %ld\n", PTR_ERR(srq));
		वापस PTR_ERR(srq);
	पूर्ण

	pr_debug("create SRQ #wr= %d max_allow=%d dev= %s\n", sdev->srq_size,
		 sdev->device->attrs.max_srq_wr, dev_name(&device->dev));

	sdev->req_buf_cache = kmem_cache_create("srpt-srq-req-buf",
						srp_max_req_size, 0, 0, शून्य);
	अगर (!sdev->req_buf_cache)
		जाओ मुक्त_srq;

	sdev->ioctx_ring = (काष्ठा srpt_recv_ioctx **)
		srpt_alloc_ioctx_ring(sdev, sdev->srq_size,
				      माप(*sdev->ioctx_ring[0]),
				      sdev->req_buf_cache, 0, DMA_FROM_DEVICE);
	अगर (!sdev->ioctx_ring)
		जाओ मुक्त_cache;

	sdev->use_srq = true;
	sdev->srq = srq;

	क्रम (i = 0; i < sdev->srq_size; ++i) अणु
		INIT_LIST_HEAD(&sdev->ioctx_ring[i]->रुको_list);
		srpt_post_recv(sdev, शून्य, sdev->ioctx_ring[i]);
	पूर्ण

	वापस 0;

मुक्त_cache:
	kmem_cache_destroy(sdev->req_buf_cache);

मुक्त_srq:
	ib_destroy_srq(srq);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक srpt_use_srq(काष्ठा srpt_device *sdev, bool use_srq)
अणु
	काष्ठा ib_device *device = sdev->device;
	पूर्णांक ret = 0;

	अगर (!use_srq) अणु
		srpt_मुक्त_srq(sdev);
		sdev->use_srq = false;
	पूर्ण अन्यथा अगर (use_srq && !sdev->srq) अणु
		ret = srpt_alloc_srq(sdev);
	पूर्ण
	pr_debug("%s(%s): use_srq = %d; ret = %d\n", __func__,
		 dev_name(&device->dev), sdev->use_srq, ret);
	वापस ret;
पूर्ण

/**
 * srpt_add_one - InfiniBand device addition callback function
 * @device: Describes a HCA.
 */
अटल पूर्णांक srpt_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा srpt_device *sdev;
	काष्ठा srpt_port *sport;
	पूर्णांक ret;
	u32 i;

	pr_debug("device = %p\n", device);

	sdev = kzalloc(काष्ठा_size(sdev, port, device->phys_port_cnt),
		       GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->device = device;
	mutex_init(&sdev->sdev_mutex);

	sdev->pd = ib_alloc_pd(device, 0);
	अगर (IS_ERR(sdev->pd)) अणु
		ret = PTR_ERR(sdev->pd);
		जाओ मुक्त_dev;
	पूर्ण

	sdev->lkey = sdev->pd->local_dma_lkey;

	sdev->srq_size = min(srpt_srq_size, sdev->device->attrs.max_srq_wr);

	srpt_use_srq(sdev, sdev->port[0].port_attrib.use_srq);

	अगर (!srpt_service_guid)
		srpt_service_guid = be64_to_cpu(device->node_guid);

	अगर (rdma_port_get_link_layer(device, 1) == IB_LINK_LAYER_INFINIBAND)
		sdev->cm_id = ib_create_cm_id(device, srpt_cm_handler, sdev);
	अगर (IS_ERR(sdev->cm_id)) अणु
		pr_info("ib_create_cm_id() failed: %ld\n",
			PTR_ERR(sdev->cm_id));
		ret = PTR_ERR(sdev->cm_id);
		sdev->cm_id = शून्य;
		अगर (!rdma_cm_id)
			जाओ err_ring;
	पूर्ण

	/* prपूर्णांक out target login inक्रमmation */
	pr_debug("Target login info: id_ext=%016llx,ioc_guid=%016llx,pkey=ffff,service_id=%016llx\n",
		 srpt_service_guid, srpt_service_guid, srpt_service_guid);

	/*
	 * We करो not have a consistent service_id (ie. also id_ext of target_id)
	 * to identअगरy this target. We currently use the guid of the first HCA
	 * in the प्रणाली as service_id; thereक्रमe, the target_id will change
	 * अगर this HCA is gone bad and replaced by dअगरferent HCA
	 */
	ret = sdev->cm_id ?
		ib_cm_listen(sdev->cm_id, cpu_to_be64(srpt_service_guid), 0) :
		0;
	अगर (ret < 0) अणु
		pr_err("ib_cm_listen() failed: %d (cm_id state = %d)\n", ret,
		       sdev->cm_id->state);
		जाओ err_cm;
	पूर्ण

	INIT_IB_EVENT_HANDLER(&sdev->event_handler, sdev->device,
			      srpt_event_handler);
	ib_रेजिस्टर_event_handler(&sdev->event_handler);

	क्रम (i = 1; i <= sdev->device->phys_port_cnt; i++) अणु
		sport = &sdev->port[i - 1];
		INIT_LIST_HEAD(&sport->nexus_list);
		mutex_init(&sport->mutex);
		sport->sdev = sdev;
		sport->port = i;
		sport->port_attrib.srp_max_rdma_size = DEFAULT_MAX_RDMA_SIZE;
		sport->port_attrib.srp_max_rsp_size = DEFAULT_MAX_RSP_SIZE;
		sport->port_attrib.srp_sq_size = DEF_SRPT_SQ_SIZE;
		sport->port_attrib.use_srq = false;
		INIT_WORK(&sport->work, srpt_refresh_port_work);
		mutex_init(&sport->port_guid_id.mutex);
		INIT_LIST_HEAD(&sport->port_guid_id.tpg_list);
		mutex_init(&sport->port_gid_id.mutex);
		INIT_LIST_HEAD(&sport->port_gid_id.tpg_list);

		ret = srpt_refresh_port(sport);
		अगर (ret) अणु
			pr_err("MAD registration failed for %s-%d.\n",
			       dev_name(&sdev->device->dev), i);
			i--;
			जाओ err_port;
		पूर्ण
	पूर्ण

	spin_lock(&srpt_dev_lock);
	list_add_tail(&sdev->list, &srpt_dev_list);
	spin_unlock(&srpt_dev_lock);

	ib_set_client_data(device, &srpt_client, sdev);
	pr_debug("added %s.\n", dev_name(&device->dev));
	वापस 0;

err_port:
	srpt_unरेजिस्टर_mad_agent(sdev, i);
	ib_unरेजिस्टर_event_handler(&sdev->event_handler);
err_cm:
	अगर (sdev->cm_id)
		ib_destroy_cm_id(sdev->cm_id);
err_ring:
	srpt_मुक्त_srq(sdev);
	ib_dealloc_pd(sdev->pd);
मुक्त_dev:
	kमुक्त(sdev);
	pr_info("%s(%s) failed.\n", __func__, dev_name(&device->dev));
	वापस ret;
पूर्ण

/**
 * srpt_हटाओ_one - InfiniBand device removal callback function
 * @device: Describes a HCA.
 * @client_data: The value passed as the third argument to ib_set_client_data().
 */
अटल व्योम srpt_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा srpt_device *sdev = client_data;
	पूर्णांक i;

	srpt_unरेजिस्टर_mad_agent(sdev, sdev->device->phys_port_cnt);

	ib_unरेजिस्टर_event_handler(&sdev->event_handler);

	/* Cancel any work queued by the just unरेजिस्टरed IB event handler. */
	क्रम (i = 0; i < sdev->device->phys_port_cnt; i++)
		cancel_work_sync(&sdev->port[i].work);

	अगर (sdev->cm_id)
		ib_destroy_cm_id(sdev->cm_id);

	ib_set_client_data(device, &srpt_client, शून्य);

	/*
	 * Unरेजिस्टरing a target must happen after destroying sdev->cm_id
	 * such that no new SRP_LOGIN_REQ inक्रमmation units can arrive जबतक
	 * destroying the target.
	 */
	spin_lock(&srpt_dev_lock);
	list_del(&sdev->list);
	spin_unlock(&srpt_dev_lock);

	क्रम (i = 0; i < sdev->device->phys_port_cnt; i++)
		srpt_release_sport(&sdev->port[i]);

	srpt_मुक्त_srq(sdev);

	ib_dealloc_pd(sdev->pd);

	kमुक्त(sdev);
पूर्ण

अटल काष्ठा ib_client srpt_client = अणु
	.name = DRV_NAME,
	.add = srpt_add_one,
	.हटाओ = srpt_हटाओ_one
पूर्ण;

अटल पूर्णांक srpt_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक srpt_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा srpt_port *srpt_tpg_to_sport(काष्ठा se_portal_group *tpg)
अणु
	वापस tpg->se_tpg_wwn->priv;
पूर्ण

अटल काष्ठा srpt_port_id *srpt_wwn_to_sport_id(काष्ठा se_wwn *wwn)
अणु
	काष्ठा srpt_port *sport = wwn->priv;

	अगर (wwn == &sport->port_guid_id.wwn)
		वापस &sport->port_guid_id;
	अगर (wwn == &sport->port_gid_id.wwn)
		वापस &sport->port_gid_id;
	WARN_ON_ONCE(true);
	वापस शून्य;
पूर्ण

अटल अक्षर *srpt_get_fabric_wwn(काष्ठा se_portal_group *tpg)
अणु
	काष्ठा srpt_tpg *stpg = container_of(tpg, typeof(*stpg), tpg);

	वापस stpg->sport_id->name;
पूर्ण

अटल u16 srpt_get_tag(काष्ठा se_portal_group *tpg)
अणु
	वापस 1;
पूर्ण

अटल u32 srpt_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल व्योम srpt_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx = container_of(se_cmd,
				काष्ठा srpt_send_ioctx, cmd);
	काष्ठा srpt_rdma_ch *ch = ioctx->ch;
	काष्ठा srpt_recv_ioctx *recv_ioctx = ioctx->recv_ioctx;

	WARN_ON_ONCE(ioctx->state != SRPT_STATE_DONE &&
		     !(ioctx->cmd.transport_state & CMD_T_ABORTED));

	अगर (recv_ioctx) अणु
		WARN_ON_ONCE(!list_empty(&recv_ioctx->रुको_list));
		ioctx->recv_ioctx = शून्य;
		srpt_post_recv(ch->sport->sdev, ch, recv_ioctx);
	पूर्ण

	अगर (ioctx->n_rw_ctx) अणु
		srpt_मुक्त_rw_ctxs(ch, ioctx);
		ioctx->n_rw_ctx = 0;
	पूर्ण

	target_मुक्त_tag(se_cmd->se_sess, se_cmd);
पूर्ण

/**
 * srpt_बंद_session - क्रमcibly बंद a session
 * @se_sess: SCSI target session.
 *
 * Callback function invoked by the TCM core to clean up sessions associated
 * with a node ACL when the user invokes
 * सूची_हटाओ /sys/kernel/config/target/$driver/$port/$tpg/acls/$i_port_id
 */
अटल व्योम srpt_बंद_session(काष्ठा se_session *se_sess)
अणु
	काष्ठा srpt_rdma_ch *ch = se_sess->fabric_sess_ptr;

	srpt_disconnect_ch_sync(ch);
पूर्ण

/**
 * srpt_sess_get_index - वापस the value of scsiAttIntrPortIndex (SCSI-MIB)
 * @se_sess: SCSI target session.
 *
 * A quote from RFC 4455 (SCSI-MIB) about this MIB object:
 * This object represents an arbitrary पूर्णांकeger used to uniquely identअगरy a
 * particular attached remote initiator port to a particular SCSI target port
 * within a particular SCSI target device within a particular SCSI instance.
 */
अटल u32 srpt_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल व्योम srpt_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
पूर्ण

/* Note: only used from inside debug prपूर्णांकk's by the TCM core. */
अटल पूर्णांक srpt_get_tcm_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा srpt_send_ioctx *ioctx;

	ioctx = container_of(se_cmd, काष्ठा srpt_send_ioctx, cmd);
	वापस ioctx->state;
पूर्ण

अटल पूर्णांक srpt_parse_guid(u64 *guid, स्थिर अक्षर *name)
अणु
	u16 w[4];
	पूर्णांक ret = -EINVAL;

	अगर (माला_पूछो(name, "%hx:%hx:%hx:%hx", &w[0], &w[1], &w[2], &w[3]) != 4)
		जाओ out;
	*guid = get_unaligned_be64(w);
	ret = 0;
out:
	वापस ret;
पूर्ण

/**
 * srpt_parse_i_port_id - parse an initiator port ID
 * @name: ASCII representation of a 128-bit initiator port ID.
 * @i_port_id: Binary 128-bit port ID.
 */
अटल पूर्णांक srpt_parse_i_port_id(u8 i_port_id[16], स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *p;
	अचिन्हित len, count, leading_zero_bytes;
	पूर्णांक ret;

	p = name;
	अगर (strnहालcmp(p, "0x", 2) == 0)
		p += 2;
	ret = -EINVAL;
	len = म_माप(p);
	अगर (len % 2)
		जाओ out;
	count = min(len / 2, 16U);
	leading_zero_bytes = 16 - count;
	स_रखो(i_port_id, 0, leading_zero_bytes);
	ret = hex2bin(i_port_id + leading_zero_bytes, p, count);

out:
	वापस ret;
पूर्ण

/*
 * configfs callback function invoked क्रम सूची_गढ़ो
 * /sys/kernel/config/target/$driver/$port/$tpg/acls/$i_port_id
 *
 * i_port_id must be an initiator port GUID, GID or IP address. See also the
 * target_alloc_session() calls in this driver. Examples of valid initiator
 * port IDs:
 * 0x0000000000000000505400fffe4a0b7b
 * 0000000000000000505400fffe4a0b7b
 * 5054:00ff:fe4a:0b7b
 * 192.168.122.76
 */
अटल पूर्णांक srpt_init_nodeacl(काष्ठा se_node_acl *se_nacl, स्थिर अक्षर *name)
अणु
	काष्ठा sockaddr_storage sa;
	u64 guid;
	u8 i_port_id[16];
	पूर्णांक ret;

	ret = srpt_parse_guid(&guid, name);
	अगर (ret < 0)
		ret = srpt_parse_i_port_id(i_port_id, name);
	अगर (ret < 0)
		ret = inet_pton_with_scope(&init_net, AF_UNSPEC, name, शून्य,
					   &sa);
	अगर (ret < 0)
		pr_err("invalid initiator port ID %s\n", name);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_max_rdma_size_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	वापस sysfs_emit(page, "%u\n", sport->port_attrib.srp_max_rdma_size);
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_max_rdma_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &val);
	अगर (ret < 0) अणु
		pr_err("kstrtoul() failed with ret: %d\n", ret);
		वापस -EINVAL;
	पूर्ण
	अगर (val > MAX_SRPT_RDMA_SIZE) अणु
		pr_err("val: %lu exceeds MAX_SRPT_RDMA_SIZE: %d\n", val,
			MAX_SRPT_RDMA_SIZE);
		वापस -EINVAL;
	पूर्ण
	अगर (val < DEFAULT_MAX_RDMA_SIZE) अणु
		pr_err("val: %lu smaller than DEFAULT_MAX_RDMA_SIZE: %d\n",
			val, DEFAULT_MAX_RDMA_SIZE);
		वापस -EINVAL;
	पूर्ण
	sport->port_attrib.srp_max_rdma_size = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_max_rsp_size_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	वापस sysfs_emit(page, "%u\n", sport->port_attrib.srp_max_rsp_size);
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_max_rsp_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &val);
	अगर (ret < 0) अणु
		pr_err("kstrtoul() failed with ret: %d\n", ret);
		वापस -EINVAL;
	पूर्ण
	अगर (val > MAX_SRPT_RSP_SIZE) अणु
		pr_err("val: %lu exceeds MAX_SRPT_RSP_SIZE: %d\n", val,
			MAX_SRPT_RSP_SIZE);
		वापस -EINVAL;
	पूर्ण
	अगर (val < MIN_MAX_RSP_SIZE) अणु
		pr_err("val: %lu smaller than MIN_MAX_RSP_SIZE: %d\n", val,
			MIN_MAX_RSP_SIZE);
		वापस -EINVAL;
	पूर्ण
	sport->port_attrib.srp_max_rsp_size = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_sq_size_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	वापस sysfs_emit(page, "%u\n", sport->port_attrib.srp_sq_size);
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_srp_sq_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &val);
	अगर (ret < 0) अणु
		pr_err("kstrtoul() failed with ret: %d\n", ret);
		वापस -EINVAL;
	पूर्ण
	अगर (val > MAX_SRPT_SRQ_SIZE) अणु
		pr_err("val: %lu exceeds MAX_SRPT_SRQ_SIZE: %d\n", val,
			MAX_SRPT_SRQ_SIZE);
		वापस -EINVAL;
	पूर्ण
	अगर (val < MIN_SRPT_SRQ_SIZE) अणु
		pr_err("val: %lu smaller than MIN_SRPT_SRQ_SIZE: %d\n", val,
			MIN_SRPT_SRQ_SIZE);
		वापस -EINVAL;
	पूर्ण
	sport->port_attrib.srp_sq_size = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_use_srq_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	वापस sysfs_emit(page, "%d\n", sport->port_attrib.use_srq);
पूर्ण

अटल sमाप_प्रकार srpt_tpg_attrib_use_srq_store(काष्ठा config_item *item,
					     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	काष्ठा srpt_device *sdev = sport->sdev;
	अचिन्हित दीर्घ val;
	bool enabled;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val != !!val)
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&sdev->sdev_mutex);
	अगर (ret < 0)
		वापस ret;
	ret = mutex_lock_पूर्णांकerruptible(&sport->mutex);
	अगर (ret < 0)
		जाओ unlock_sdev;
	enabled = sport->enabled;
	/* Log out all initiator प्रणालीs beक्रमe changing 'use_srq'. */
	srpt_set_enabled(sport, false);
	sport->port_attrib.use_srq = val;
	srpt_use_srq(sdev, sport->port_attrib.use_srq);
	srpt_set_enabled(sport, enabled);
	ret = count;
	mutex_unlock(&sport->mutex);
unlock_sdev:
	mutex_unlock(&sdev->sdev_mutex);

	वापस ret;
पूर्ण

CONFIGFS_ATTR(srpt_tpg_attrib_,  srp_max_rdma_size);
CONFIGFS_ATTR(srpt_tpg_attrib_,  srp_max_rsp_size);
CONFIGFS_ATTR(srpt_tpg_attrib_,  srp_sq_size);
CONFIGFS_ATTR(srpt_tpg_attrib_,  use_srq);

अटल काष्ठा configfs_attribute *srpt_tpg_attrib_attrs[] = अणु
	&srpt_tpg_attrib_attr_srp_max_rdma_size,
	&srpt_tpg_attrib_attr_srp_max_rsp_size,
	&srpt_tpg_attrib_attr_srp_sq_size,
	&srpt_tpg_attrib_attr_use_srq,
	शून्य,
पूर्ण;

अटल काष्ठा rdma_cm_id *srpt_create_rdma_id(काष्ठा sockaddr *listen_addr)
अणु
	काष्ठा rdma_cm_id *rdma_cm_id;
	पूर्णांक ret;

	rdma_cm_id = rdma_create_id(&init_net, srpt_rdma_cm_handler,
				    शून्य, RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(rdma_cm_id)) अणु
		pr_err("RDMA/CM ID creation failed: %ld\n",
		       PTR_ERR(rdma_cm_id));
		जाओ out;
	पूर्ण

	ret = rdma_bind_addr(rdma_cm_id, listen_addr);
	अगर (ret) अणु
		अक्षर addr_str[64];

		snम_लिखो(addr_str, माप(addr_str), "%pISp", listen_addr);
		pr_err("Binding RDMA/CM ID to address %s failed: %d\n",
		       addr_str, ret);
		rdma_destroy_id(rdma_cm_id);
		rdma_cm_id = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	ret = rdma_listen(rdma_cm_id, 128);
	अगर (ret) अणु
		pr_err("rdma_listen() failed: %d\n", ret);
		rdma_destroy_id(rdma_cm_id);
		rdma_cm_id = ERR_PTR(ret);
	पूर्ण

out:
	वापस rdma_cm_id;
पूर्ण

अटल sमाप_प्रकार srpt_rdma_cm_port_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस sysfs_emit(page, "%d\n", rdma_cm_port);
पूर्ण

अटल sमाप_प्रकार srpt_rdma_cm_port_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा sockaddr_in  addr4 = अणु .sin_family  = AF_INET  पूर्ण;
	काष्ठा sockaddr_in6 addr6 = अणु .sin6_family = AF_INET6 पूर्ण;
	काष्ठा rdma_cm_id *new_id = शून्य;
	u16 val;
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &val);
	अगर (ret < 0)
		वापस ret;
	ret = count;
	अगर (rdma_cm_port == val)
		जाओ out;

	अगर (val) अणु
		addr6.sin6_port = cpu_to_be16(val);
		new_id = srpt_create_rdma_id((काष्ठा sockaddr *)&addr6);
		अगर (IS_ERR(new_id)) अणु
			addr4.sin_port = cpu_to_be16(val);
			new_id = srpt_create_rdma_id((काष्ठा sockaddr *)&addr4);
			अगर (IS_ERR(new_id)) अणु
				ret = PTR_ERR(new_id);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_lock(&rdma_cm_mutex);
	rdma_cm_port = val;
	swap(rdma_cm_id, new_id);
	mutex_unlock(&rdma_cm_mutex);

	अगर (new_id)
		rdma_destroy_id(new_id);
	ret = count;
out:
	वापस ret;
पूर्ण

CONFIGFS_ATTR(srpt_, rdma_cm_port);

अटल काष्ठा configfs_attribute *srpt_da_attrs[] = अणु
	&srpt_attr_rdma_cm_port,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार srpt_tpg_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	वापस sysfs_emit(page, "%d\n", sport->enabled);
पूर्ण

अटल sमाप_प्रकार srpt_tpg_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract srpt_tpg_store_enable\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		pr_err("Illegal value for srpt_tpg_store_enable: %lu\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&sport->mutex);
	srpt_set_enabled(sport, पंचांगp);
	mutex_unlock(&sport->mutex);

	वापस count;
पूर्ण

CONFIGFS_ATTR(srpt_tpg_, enable);

अटल काष्ठा configfs_attribute *srpt_tpg_attrs[] = अणु
	&srpt_tpg_attr_enable,
	शून्य,
पूर्ण;

/**
 * srpt_make_tpg - configfs callback invoked क्रम सूची_गढ़ो /sys/kernel/config/target/$driver/$port/$tpg
 * @wwn: Corresponds to $driver/$port.
 * @name: $tpg.
 */
अटल काष्ठा se_portal_group *srpt_make_tpg(काष्ठा se_wwn *wwn,
					     स्थिर अक्षर *name)
अणु
	काष्ठा srpt_port_id *sport_id = srpt_wwn_to_sport_id(wwn);
	काष्ठा srpt_tpg *stpg;
	पूर्णांक res = -ENOMEM;

	stpg = kzalloc(माप(*stpg), GFP_KERNEL);
	अगर (!stpg)
		वापस ERR_PTR(res);
	stpg->sport_id = sport_id;
	res = core_tpg_रेजिस्टर(wwn, &stpg->tpg, SCSI_PROTOCOL_SRP);
	अगर (res) अणु
		kमुक्त(stpg);
		वापस ERR_PTR(res);
	पूर्ण

	mutex_lock(&sport_id->mutex);
	list_add_tail(&stpg->entry, &sport_id->tpg_list);
	mutex_unlock(&sport_id->mutex);

	वापस &stpg->tpg;
पूर्ण

/**
 * srpt_drop_tpg - configfs callback invoked क्रम सूची_हटाओ /sys/kernel/config/target/$driver/$port/$tpg
 * @tpg: Target portal group to deरेजिस्टर.
 */
अटल व्योम srpt_drop_tpg(काष्ठा se_portal_group *tpg)
अणु
	काष्ठा srpt_tpg *stpg = container_of(tpg, typeof(*stpg), tpg);
	काष्ठा srpt_port_id *sport_id = stpg->sport_id;
	काष्ठा srpt_port *sport = srpt_tpg_to_sport(tpg);

	mutex_lock(&sport_id->mutex);
	list_del(&stpg->entry);
	mutex_unlock(&sport_id->mutex);

	sport->enabled = false;
	core_tpg_deरेजिस्टर(tpg);
	kमुक्त(stpg);
पूर्ण

/**
 * srpt_make_tport - configfs callback invoked क्रम सूची_गढ़ो /sys/kernel/config/target/$driver/$port
 * @tf: Not used.
 * @group: Not used.
 * @name: $port.
 */
अटल काष्ठा se_wwn *srpt_make_tport(काष्ठा target_fabric_configfs *tf,
				      काष्ठा config_group *group,
				      स्थिर अक्षर *name)
अणु
	वापस srpt_lookup_wwn(name) ? : ERR_PTR(-EINVAL);
पूर्ण

/**
 * srpt_drop_tport - configfs callback invoked क्रम सूची_हटाओ /sys/kernel/config/target/$driver/$port
 * @wwn: $port.
 */
अटल व्योम srpt_drop_tport(काष्ठा se_wwn *wwn)
अणु
पूर्ण

अटल sमाप_प्रकार srpt_wwn_version_show(काष्ठा config_item *item, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "\n");
पूर्ण

CONFIGFS_ATTR_RO(srpt_wwn_, version);

अटल काष्ठा configfs_attribute *srpt_wwn_attrs[] = अणु
	&srpt_wwn_attr_version,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा target_core_fabric_ops srpt_ढाँचा = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "srpt",
	.tpg_get_wwn			= srpt_get_fabric_wwn,
	.tpg_get_tag			= srpt_get_tag,
	.tpg_check_demo_mode		= srpt_check_false,
	.tpg_check_demo_mode_cache	= srpt_check_true,
	.tpg_check_demo_mode_ग_लिखो_protect = srpt_check_true,
	.tpg_check_prod_mode_ग_लिखो_protect = srpt_check_false,
	.tpg_get_inst_index		= srpt_tpg_get_inst_index,
	.release_cmd			= srpt_release_cmd,
	.check_stop_मुक्त		= srpt_check_stop_मुक्त,
	.बंद_session			= srpt_बंद_session,
	.sess_get_index			= srpt_sess_get_index,
	.sess_get_initiator_sid		= शून्य,
	.ग_लिखो_pending			= srpt_ग_लिखो_pending,
	.set_शेष_node_attributes	= srpt_set_शेष_node_attrs,
	.get_cmd_state			= srpt_get_tcm_cmd_state,
	.queue_data_in			= srpt_queue_data_in,
	.queue_status			= srpt_queue_status,
	.queue_पंचांग_rsp			= srpt_queue_पंचांग_rsp,
	.पातed_task			= srpt_पातed_task,
	/*
	 * Setup function poपूर्णांकers क्रम generic logic in
	 * target_core_fabric_configfs.c
	 */
	.fabric_make_wwn		= srpt_make_tport,
	.fabric_drop_wwn		= srpt_drop_tport,
	.fabric_make_tpg		= srpt_make_tpg,
	.fabric_drop_tpg		= srpt_drop_tpg,
	.fabric_init_nodeacl		= srpt_init_nodeacl,

	.tfc_discovery_attrs		= srpt_da_attrs,
	.tfc_wwn_attrs			= srpt_wwn_attrs,
	.tfc_tpg_base_attrs		= srpt_tpg_attrs,
	.tfc_tpg_attrib_attrs		= srpt_tpg_attrib_attrs,
पूर्ण;

/**
 * srpt_init_module - kernel module initialization
 *
 * Note: Since ib_रेजिस्टर_client() रेजिस्टरs callback functions, and since at
 * least one of these callback functions (srpt_add_one()) calls target core
 * functions, this driver must be रेजिस्टरed with the target core beक्रमe
 * ib_रेजिस्टर_client() is called.
 */
अटल पूर्णांक __init srpt_init_module(व्योम)
अणु
	पूर्णांक ret;

	ret = -EINVAL;
	अगर (srp_max_req_size < MIN_MAX_REQ_SIZE) अणु
		pr_err("invalid value %d for kernel module parameter srp_max_req_size -- must be at least %d.\n",
		       srp_max_req_size, MIN_MAX_REQ_SIZE);
		जाओ out;
	पूर्ण

	अगर (srpt_srq_size < MIN_SRPT_SRQ_SIZE
	    || srpt_srq_size > MAX_SRPT_SRQ_SIZE) अणु
		pr_err("invalid value %d for kernel module parameter srpt_srq_size -- must be in the range [%d..%d].\n",
		       srpt_srq_size, MIN_SRPT_SRQ_SIZE, MAX_SRPT_SRQ_SIZE);
		जाओ out;
	पूर्ण

	ret = target_रेजिस्टर_ढाँचा(&srpt_ढाँचा);
	अगर (ret)
		जाओ out;

	ret = ib_रेजिस्टर_client(&srpt_client);
	अगर (ret) अणु
		pr_err("couldn't register IB client\n");
		जाओ out_unरेजिस्टर_target;
	पूर्ण

	वापस 0;

out_unरेजिस्टर_target:
	target_unरेजिस्टर_ढाँचा(&srpt_ढाँचा);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास srpt_cleanup_module(व्योम)
अणु
	अगर (rdma_cm_id)
		rdma_destroy_id(rdma_cm_id);
	ib_unरेजिस्टर_client(&srpt_client);
	target_unरेजिस्टर_ढाँचा(&srpt_ढाँचा);
पूर्ण

module_init(srpt_init_module);
module_निकास(srpt_cleanup_module);
