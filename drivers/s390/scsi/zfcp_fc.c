<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Fibre Channel related functions क्रम the zfcp device driver.
 *
 * Copyright IBM Corp. 2008, 2017
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/utsname.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/bsg-lib.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/libfc.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_fc.h"

काष्ठा kmem_cache *zfcp_fc_req_cache;

अटल u32 zfcp_fc_rscn_range_mask[] = अणु
	[ELS_ADDR_FMT_PORT]		= 0xFFFFFF,
	[ELS_ADDR_FMT_AREA]		= 0xFFFF00,
	[ELS_ADDR_FMT_DOM]		= 0xFF0000,
	[ELS_ADDR_FMT_FAB]		= 0x000000,
पूर्ण;

अटल bool no_स्वतः_port_rescan;
module_param(no_स्वतः_port_rescan, bool, 0600);
MODULE_PARM_DESC(no_स्वतः_port_rescan,
		 "no automatic port_rescan (default off)");

अटल अचिन्हित पूर्णांक port_scan_backoff = 500;
module_param(port_scan_backoff, uपूर्णांक, 0600);
MODULE_PARM_DESC(port_scan_backoff,
	"upper limit of port scan random backoff in msecs (default 500)");

अटल अचिन्हित पूर्णांक port_scan_ratelimit = 60000;
module_param(port_scan_ratelimit, uपूर्णांक, 0600);
MODULE_PARM_DESC(port_scan_ratelimit,
	"minimum interval between port scans in msecs (default 60000)");

अचिन्हित पूर्णांक zfcp_fc_port_scan_backoff(व्योम)
अणु
	अगर (!port_scan_backoff)
		वापस 0;
	वापस pअक्रमom_u32_max(port_scan_backoff);
पूर्ण

अटल व्योम zfcp_fc_port_scan_समय(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = msecs_to_jअगरfies(port_scan_ratelimit);
	अचिन्हित दीर्घ backoff = msecs_to_jअगरfies(zfcp_fc_port_scan_backoff());

	adapter->next_port_scan = jअगरfies + पूर्णांकerval + backoff;
पूर्ण

अटल व्योम zfcp_fc_port_scan(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ next = adapter->next_port_scan;
	अचिन्हित दीर्घ delay = 0, max;

	/* delay only needed within रुकोing period */
	अगर (समय_beक्रमe(now, next)) अणु
		delay = next - now;
		/* paranoia: never ever delay scans दीर्घer than specअगरied */
		max = msecs_to_jअगरfies(port_scan_ratelimit + port_scan_backoff);
		delay = min(delay, max);
	पूर्ण

	queue_delayed_work(adapter->work_queue, &adapter->scan_work, delay);
पूर्ण

व्योम zfcp_fc_conditional_port_scan(काष्ठा zfcp_adapter *adapter)
अणु
	अगर (no_स्वतः_port_rescan)
		वापस;

	zfcp_fc_port_scan(adapter);
पूर्ण

व्योम zfcp_fc_inverse_conditional_port_scan(काष्ठा zfcp_adapter *adapter)
अणु
	अगर (!no_स्वतः_port_rescan)
		वापस;

	zfcp_fc_port_scan(adapter);
पूर्ण

/**
 * zfcp_fc_post_event - post event to userspace via fc_transport
 * @work: work काष्ठा with enqueued events
 */
व्योम zfcp_fc_post_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_fc_event *event = शून्य, *पंचांगp = शून्य;
	LIST_HEAD(पंचांगp_lh);
	काष्ठा zfcp_fc_events *events = container_of(work,
					काष्ठा zfcp_fc_events, work);
	काष्ठा zfcp_adapter *adapter = container_of(events, काष्ठा zfcp_adapter,
						events);

	spin_lock_bh(&events->list_lock);
	list_splice_init(&events->list, &पंचांगp_lh);
	spin_unlock_bh(&events->list_lock);

	list_क्रम_each_entry_safe(event, पंचांगp, &पंचांगp_lh, list) अणु
		fc_host_post_event(adapter->scsi_host, fc_get_event_number(),
				   event->code, event->data);
		list_del(&event->list);
		kमुक्त(event);
	पूर्ण
पूर्ण

/**
 * zfcp_fc_enqueue_event - safely enqueue FC HBA API event from irq context
 * @adapter: The adapter where to enqueue the event
 * @event_code: The event code (as defined in fc_host_event_code in
 *		scsi_transport_fc.h)
 * @event_data: The event data (e.g. n_port page in हाल of els)
 */
व्योम zfcp_fc_enqueue_event(काष्ठा zfcp_adapter *adapter,
			   क्रमागत fc_host_event_code event_code, u32 event_data)
अणु
	काष्ठा zfcp_fc_event *event;

	event = kदो_स्मृति(माप(काष्ठा zfcp_fc_event), GFP_ATOMIC);
	अगर (!event)
		वापस;

	event->code = event_code;
	event->data = event_data;

	spin_lock(&adapter->events.list_lock);
	list_add_tail(&event->list, &adapter->events.list);
	spin_unlock(&adapter->events.list_lock);

	queue_work(adapter->work_queue, &adapter->events.work);
पूर्ण

अटल पूर्णांक zfcp_fc_wka_port_get(काष्ठा zfcp_fc_wka_port *wka_port)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&wka_port->mutex))
		वापस -ERESTARTSYS;

	अगर (wka_port->status == ZFCP_FC_WKA_PORT_OFFLINE ||
	    wka_port->status == ZFCP_FC_WKA_PORT_CLOSING) अणु
		wka_port->status = ZFCP_FC_WKA_PORT_OPENING;
		अगर (zfcp_fsf_खोलो_wka_port(wka_port))
			wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
	पूर्ण

	mutex_unlock(&wka_port->mutex);

	रुको_event(wka_port->completion_wq,
		   wka_port->status == ZFCP_FC_WKA_PORT_ONLINE ||
		   wka_port->status == ZFCP_FC_WKA_PORT_OFFLINE);

	अगर (wka_port->status == ZFCP_FC_WKA_PORT_ONLINE) अणु
		atomic_inc(&wka_port->refcount);
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल व्योम zfcp_fc_wka_port_offline(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा zfcp_fc_wka_port *wka_port =
			container_of(dw, काष्ठा zfcp_fc_wka_port, work);

	mutex_lock(&wka_port->mutex);
	अगर ((atomic_पढ़ो(&wka_port->refcount) != 0) ||
	    (wka_port->status != ZFCP_FC_WKA_PORT_ONLINE))
		जाओ out;

	wka_port->status = ZFCP_FC_WKA_PORT_CLOSING;
	अगर (zfcp_fsf_बंद_wka_port(wka_port)) अणु
		wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
		wake_up(&wka_port->completion_wq);
	पूर्ण
out:
	mutex_unlock(&wka_port->mutex);
पूर्ण

अटल व्योम zfcp_fc_wka_port_put(काष्ठा zfcp_fc_wka_port *wka_port)
अणु
	अगर (atomic_dec_वापस(&wka_port->refcount) != 0)
		वापस;
	/* रुको 10 milliseconds, other reqs might pop in */
	schedule_delayed_work(&wka_port->work, HZ / 100);
पूर्ण

अटल व्योम zfcp_fc_wka_port_init(काष्ठा zfcp_fc_wka_port *wka_port, u32 d_id,
				  काष्ठा zfcp_adapter *adapter)
अणु
	init_रुकोqueue_head(&wka_port->completion_wq);

	wka_port->adapter = adapter;
	wka_port->d_id = d_id;

	wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
	atomic_set(&wka_port->refcount, 0);
	mutex_init(&wka_port->mutex);
	INIT_DELAYED_WORK(&wka_port->work, zfcp_fc_wka_port_offline);
पूर्ण

अटल व्योम zfcp_fc_wka_port_क्रमce_offline(काष्ठा zfcp_fc_wka_port *wka)
अणु
	cancel_delayed_work_sync(&wka->work);
	mutex_lock(&wka->mutex);
	wka->status = ZFCP_FC_WKA_PORT_OFFLINE;
	mutex_unlock(&wka->mutex);
पूर्ण

व्योम zfcp_fc_wka_ports_क्रमce_offline(काष्ठा zfcp_fc_wka_ports *gs)
अणु
	अगर (!gs)
		वापस;
	zfcp_fc_wka_port_क्रमce_offline(&gs->ms);
	zfcp_fc_wka_port_क्रमce_offline(&gs->ts);
	zfcp_fc_wka_port_क्रमce_offline(&gs->ds);
	zfcp_fc_wka_port_क्रमce_offline(&gs->as);
पूर्ण

अटल व्योम _zfcp_fc_incoming_rscn(काष्ठा zfcp_fsf_req *fsf_req, u32 range,
				   काष्ठा fc_els_rscn_page *page)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = fsf_req->adapter;
	काष्ठा zfcp_port *port;

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list) अणु
		अगर ((port->d_id & range) == (ntoh24(page->rscn_fid) & range))
			zfcp_fc_test_link(port);
	पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
पूर्ण

अटल व्योम zfcp_fc_incoming_rscn(काष्ठा zfcp_fsf_req *fsf_req)
अणु
	काष्ठा fsf_status_पढ़ो_buffer *status_buffer = (व्योम *)fsf_req->data;
	काष्ठा zfcp_adapter *adapter = fsf_req->adapter;
	काष्ठा fc_els_rscn *head;
	काष्ठा fc_els_rscn_page *page;
	u16 i;
	u16 no_entries;
	अचिन्हित पूर्णांक afmt;

	head = (काष्ठा fc_els_rscn *) status_buffer->payload.data;
	page = (काष्ठा fc_els_rscn_page *) head;

	/* see FC-FS */
	no_entries = be16_to_cpu(head->rscn_plen) /
		माप(काष्ठा fc_els_rscn_page);

	अगर (no_entries > 1) अणु
		/* handle failed ports */
		अचिन्हित दीर्घ flags;
		काष्ठा zfcp_port *port;

		पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
		list_क्रम_each_entry(port, &adapter->port_list, list) अणु
			अगर (port->d_id)
				जारी;
			zfcp_erp_port_reखोलो(port,
					     ZFCP_STATUS_COMMON_ERP_FAILED,
					     "fcrscn1");
		पूर्ण
		पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
	पूर्ण

	क्रम (i = 1; i < no_entries; i++) अणु
		/* skip head and start with 1st element */
		page++;
		afmt = page->rscn_page_flags & ELS_RSCN_ADDR_FMT_MASK;
		_zfcp_fc_incoming_rscn(fsf_req, zfcp_fc_rscn_range_mask[afmt],
				       page);
		zfcp_fc_enqueue_event(fsf_req->adapter, FCH_EVT_RSCN,
				      *(u32 *)page);
	पूर्ण
	zfcp_fc_conditional_port_scan(fsf_req->adapter);
पूर्ण

अटल व्योम zfcp_fc_incoming_wwpn(काष्ठा zfcp_fsf_req *req, u64 wwpn)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_port *port;

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		अगर (port->wwpn == wwpn) अणु
			zfcp_erp_port_क्रमced_reखोलो(port, 0, "fciwwp1");
			अवरोध;
		पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
पूर्ण

अटल व्योम zfcp_fc_incoming_plogi(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_status_पढ़ो_buffer *status_buffer;
	काष्ठा fc_els_flogi *plogi;

	status_buffer = (काष्ठा fsf_status_पढ़ो_buffer *) req->data;
	plogi = (काष्ठा fc_els_flogi *) status_buffer->payload.data;
	zfcp_fc_incoming_wwpn(req, be64_to_cpu(plogi->fl_wwpn));
पूर्ण

अटल व्योम zfcp_fc_incoming_logo(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_status_पढ़ो_buffer *status_buffer =
		(काष्ठा fsf_status_पढ़ो_buffer *)req->data;
	काष्ठा fc_els_logo *logo =
		(काष्ठा fc_els_logo *) status_buffer->payload.data;

	zfcp_fc_incoming_wwpn(req, be64_to_cpu(logo->fl_n_port_wwn));
पूर्ण

/**
 * zfcp_fc_incoming_els - handle incoming ELS
 * @fsf_req: request which contains incoming ELS
 */
व्योम zfcp_fc_incoming_els(काष्ठा zfcp_fsf_req *fsf_req)
अणु
	काष्ठा fsf_status_पढ़ो_buffer *status_buffer =
		(काष्ठा fsf_status_पढ़ो_buffer *) fsf_req->data;
	अचिन्हित पूर्णांक els_type = status_buffer->payload.data[0];

	zfcp_dbf_san_in_els("fciels1", fsf_req);
	अगर (els_type == ELS_PLOGI)
		zfcp_fc_incoming_plogi(fsf_req);
	अन्यथा अगर (els_type == ELS_LOGO)
		zfcp_fc_incoming_logo(fsf_req);
	अन्यथा अगर (els_type == ELS_RSCN)
		zfcp_fc_incoming_rscn(fsf_req);
पूर्ण

अटल व्योम zfcp_fc_ns_gid_pn_eval(काष्ठा zfcp_fc_req *fc_req)
अणु
	काष्ठा zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	काष्ठा zfcp_fc_gid_pn_rsp *gid_pn_rsp = &fc_req->u.gid_pn.rsp;

	अगर (ct_els->status)
		वापस;
	अगर (gid_pn_rsp->ct_hdr.ct_cmd != cpu_to_be16(FC_FS_ACC))
		वापस;

	/* looks like a valid d_id */
	ct_els->port->d_id = ntoh24(gid_pn_rsp->gid_pn.fp_fid);
पूर्ण

अटल व्योम zfcp_fc_complete(व्योम *data)
अणु
	complete(data);
पूर्ण

अटल व्योम zfcp_fc_ct_ns_init(काष्ठा fc_ct_hdr *ct_hdr, u16 cmd, u16 mr_size)
अणु
	ct_hdr->ct_rev = FC_CT_REV;
	ct_hdr->ct_fs_type = FC_FST_सूची;
	ct_hdr->ct_fs_subtype = FC_NS_SUBTYPE;
	ct_hdr->ct_cmd = cpu_to_be16(cmd);
	ct_hdr->ct_mr_size = cpu_to_be16(mr_size / 4);
पूर्ण

अटल पूर्णांक zfcp_fc_ns_gid_pn_request(काष्ठा zfcp_port *port,
				     काष्ठा zfcp_fc_req *fc_req)
अणु
	काष्ठा zfcp_adapter *adapter = port->adapter;
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा zfcp_fc_gid_pn_req *gid_pn_req = &fc_req->u.gid_pn.req;
	काष्ठा zfcp_fc_gid_pn_rsp *gid_pn_rsp = &fc_req->u.gid_pn.rsp;
	पूर्णांक ret;

	/* setup parameters क्रम send generic command */
	fc_req->ct_els.port = port;
	fc_req->ct_els.handler = zfcp_fc_complete;
	fc_req->ct_els.handler_data = &completion;
	fc_req->ct_els.req = &fc_req->sg_req;
	fc_req->ct_els.resp = &fc_req->sg_rsp;
	sg_init_one(&fc_req->sg_req, gid_pn_req, माप(*gid_pn_req));
	sg_init_one(&fc_req->sg_rsp, gid_pn_rsp, माप(*gid_pn_rsp));

	zfcp_fc_ct_ns_init(&gid_pn_req->ct_hdr,
			   FC_NS_GID_PN, ZFCP_FC_CT_SIZE_PAGE);
	gid_pn_req->gid_pn.fn_wwpn = cpu_to_be64(port->wwpn);

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, &fc_req->ct_els,
			       adapter->pool.gid_pn_req,
			       ZFCP_FC_CTELS_TMO);
	अगर (!ret) अणु
		रुको_क्रम_completion(&completion);
		zfcp_fc_ns_gid_pn_eval(fc_req);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * zfcp_fc_ns_gid_pn - initiate GID_PN nameserver request
 * @port: port where GID_PN request is needed
 * वापस: -ENOMEM on error, 0 otherwise
 */
अटल पूर्णांक zfcp_fc_ns_gid_pn(काष्ठा zfcp_port *port)
अणु
	पूर्णांक ret;
	काष्ठा zfcp_fc_req *fc_req;
	काष्ठा zfcp_adapter *adapter = port->adapter;

	fc_req = mempool_alloc(adapter->pool.gid_pn, GFP_ATOMIC);
	अगर (!fc_req)
		वापस -ENOMEM;

	स_रखो(fc_req, 0, माप(*fc_req));

	ret = zfcp_fc_wka_port_get(&adapter->gs->ds);
	अगर (ret)
		जाओ out;

	ret = zfcp_fc_ns_gid_pn_request(port, fc_req);

	zfcp_fc_wka_port_put(&adapter->gs->ds);
out:
	mempool_मुक्त(fc_req, adapter->pool.gid_pn);
	वापस ret;
पूर्ण

व्योम zfcp_fc_port_did_lookup(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा zfcp_port *port = container_of(work, काष्ठा zfcp_port,
					      gid_pn_work);

	set_worker_desc("zgidpn%16llx", port->wwpn); /* < WORKER_DESC_LEN=24 */
	ret = zfcp_fc_ns_gid_pn(port);
	अगर (ret) अणु
		/* could not issue gid_pn क्रम some reason */
		zfcp_erp_adapter_reखोलो(port->adapter, 0, "fcgpn_1");
		जाओ out;
	पूर्ण

	अगर (!port->d_id) अणु
		zfcp_erp_set_port_status(port, ZFCP_STATUS_COMMON_ERP_FAILED);
		जाओ out;
	पूर्ण

	zfcp_erp_port_reखोलो(port, 0, "fcgpn_3");
out:
	put_device(&port->dev);
पूर्ण

/**
 * zfcp_fc_trigger_did_lookup - trigger the d_id lookup using a GID_PN request
 * @port: The zfcp_port to lookup the d_id क्रम.
 */
व्योम zfcp_fc_trigger_did_lookup(काष्ठा zfcp_port *port)
अणु
	get_device(&port->dev);
	अगर (!queue_work(port->adapter->work_queue, &port->gid_pn_work))
		put_device(&port->dev);
पूर्ण

/**
 * zfcp_fc_plogi_evaluate - evaluate PLOGI playload
 * @port: zfcp_port काष्ठाure
 * @plogi: plogi payload
 *
 * Evaluate PLOGI playload and copy important fields पूर्णांकo zfcp_port काष्ठाure
 */
व्योम zfcp_fc_plogi_evaluate(काष्ठा zfcp_port *port, काष्ठा fc_els_flogi *plogi)
अणु
	अगर (be64_to_cpu(plogi->fl_wwpn) != port->wwpn) अणु
		port->d_id = 0;
		dev_warn(&port->adapter->ccw_device->dev,
			 "A port opened with WWPN 0x%016Lx returned data that "
			 "identifies it as WWPN 0x%016Lx\n",
			 (अचिन्हित दीर्घ दीर्घ) port->wwpn,
			 (अचिन्हित दीर्घ दीर्घ) be64_to_cpu(plogi->fl_wwpn));
		वापस;
	पूर्ण

	port->wwnn = be64_to_cpu(plogi->fl_wwnn);
	port->maxframe_size = be16_to_cpu(plogi->fl_csp.sp_bb_data);

	अगर (plogi->fl_cssp[0].cp_class & cpu_to_be16(FC_CPC_VALID))
		port->supported_classes |= FC_COS_CLASS1;
	अगर (plogi->fl_cssp[1].cp_class & cpu_to_be16(FC_CPC_VALID))
		port->supported_classes |= FC_COS_CLASS2;
	अगर (plogi->fl_cssp[2].cp_class & cpu_to_be16(FC_CPC_VALID))
		port->supported_classes |= FC_COS_CLASS3;
	अगर (plogi->fl_cssp[3].cp_class & cpu_to_be16(FC_CPC_VALID))
		port->supported_classes |= FC_COS_CLASS4;
पूर्ण

अटल व्योम zfcp_fc_adisc_handler(व्योम *data)
अणु
	काष्ठा zfcp_fc_req *fc_req = data;
	काष्ठा zfcp_port *port = fc_req->ct_els.port;
	काष्ठा fc_els_adisc *adisc_resp = &fc_req->u.adisc.rsp;

	अगर (fc_req->ct_els.status) अणु
		/* request rejected or समयd out */
		zfcp_erp_port_क्रमced_reखोलो(port, ZFCP_STATUS_COMMON_ERP_FAILED,
					    "fcadh_1");
		जाओ out;
	पूर्ण

	अगर (!port->wwnn)
		port->wwnn = be64_to_cpu(adisc_resp->adisc_wwnn);

	अगर ((port->wwpn != be64_to_cpu(adisc_resp->adisc_wwpn)) ||
	    !(atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_OPEN)) अणु
		zfcp_erp_port_reखोलो(port, ZFCP_STATUS_COMMON_ERP_FAILED,
				     "fcadh_2");
		जाओ out;
	पूर्ण

	/* port is good, unblock rport without going through erp */
	zfcp_scsi_schedule_rport_रेजिस्टर(port);
 out:
	atomic_andnot(ZFCP_STATUS_PORT_LINK_TEST, &port->status);
	put_device(&port->dev);
	kmem_cache_मुक्त(zfcp_fc_req_cache, fc_req);
पूर्ण

अटल पूर्णांक zfcp_fc_adisc(काष्ठा zfcp_port *port)
अणु
	काष्ठा zfcp_fc_req *fc_req;
	काष्ठा zfcp_adapter *adapter = port->adapter;
	काष्ठा Scsi_Host *shost = adapter->scsi_host;
	पूर्णांक ret;

	fc_req = kmem_cache_zalloc(zfcp_fc_req_cache, GFP_ATOMIC);
	अगर (!fc_req)
		वापस -ENOMEM;

	fc_req->ct_els.port = port;
	fc_req->ct_els.req = &fc_req->sg_req;
	fc_req->ct_els.resp = &fc_req->sg_rsp;
	sg_init_one(&fc_req->sg_req, &fc_req->u.adisc.req,
		    माप(काष्ठा fc_els_adisc));
	sg_init_one(&fc_req->sg_rsp, &fc_req->u.adisc.rsp,
		    माप(काष्ठा fc_els_adisc));

	fc_req->ct_els.handler = zfcp_fc_adisc_handler;
	fc_req->ct_els.handler_data = fc_req;

	/* acc. to FC-FS, hard_nport_id in ADISC should not be set क्रम ports
	   without FC-AL-2 capability, so we करोn't set it */
	fc_req->u.adisc.req.adisc_wwpn = cpu_to_be64(fc_host_port_name(shost));
	fc_req->u.adisc.req.adisc_wwnn = cpu_to_be64(fc_host_node_name(shost));
	fc_req->u.adisc.req.adisc_cmd = ELS_ADISC;
	hton24(fc_req->u.adisc.req.adisc_port_id, fc_host_port_id(shost));

	ret = zfcp_fsf_send_els(adapter, port->d_id, &fc_req->ct_els,
				ZFCP_FC_CTELS_TMO);
	अगर (ret)
		kmem_cache_मुक्त(zfcp_fc_req_cache, fc_req);

	वापस ret;
पूर्ण

व्योम zfcp_fc_link_test_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_port *port =
		container_of(work, काष्ठा zfcp_port, test_link_work);
	पूर्णांक retval;

	set_worker_desc("zadisc%16llx", port->wwpn); /* < WORKER_DESC_LEN=24 */
	get_device(&port->dev);
	port->rport_task = RPORT_DEL;
	zfcp_scsi_rport_work(&port->rport_work);

	/* only issue one test command at one समय per port */
	अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_PORT_LINK_TEST)
		जाओ out;

	atomic_or(ZFCP_STATUS_PORT_LINK_TEST, &port->status);

	retval = zfcp_fc_adisc(port);
	अगर (retval == 0)
		वापस;

	/* send of ADISC was not possible */
	atomic_andnot(ZFCP_STATUS_PORT_LINK_TEST, &port->status);
	zfcp_erp_port_क्रमced_reखोलो(port, 0, "fcltwk1");

out:
	put_device(&port->dev);
पूर्ण

/**
 * zfcp_fc_test_link - lightweight link test procedure
 * @port: port to be tested
 *
 * Test status of a link to a remote port using the ELS command ADISC.
 * If there is a problem with the remote port, error recovery steps
 * will be triggered.
 */
व्योम zfcp_fc_test_link(काष्ठा zfcp_port *port)
अणु
	get_device(&port->dev);
	अगर (!queue_work(port->adapter->work_queue, &port->test_link_work))
		put_device(&port->dev);
पूर्ण

/**
 * zfcp_fc_sg_मुक्त_table - मुक्त memory used by scatterlists
 * @sg: poपूर्णांकer to scatterlist
 * @count: number of scatterlist which are to be मुक्त'ed
 * the scatterlist are expected to reference pages always
 */
अटल व्योम zfcp_fc_sg_मुक्त_table(काष्ठा scatterlist *sg, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++, sg = sg_next(sg))
		अगर (sg)
			मुक्त_page((अचिन्हित दीर्घ) sg_virt(sg));
		अन्यथा
			अवरोध;
पूर्ण

/**
 * zfcp_fc_sg_setup_table - init scatterlist and allocate, assign buffers
 * @sg: poपूर्णांकer to काष्ठा scatterlist
 * @count: number of scatterlists which should be asचिन्हित with buffers
 * of size page
 *
 * Returns: 0 on success, -ENOMEM otherwise
 */
अटल पूर्णांक zfcp_fc_sg_setup_table(काष्ठा scatterlist *sg, पूर्णांक count)
अणु
	व्योम *addr;
	पूर्णांक i;

	sg_init_table(sg, count);
	क्रम (i = 0; i < count; i++, sg = sg_next(sg)) अणु
		addr = (व्योम *) get_zeroed_page(GFP_KERNEL);
		अगर (!addr) अणु
			zfcp_fc_sg_मुक्त_table(sg, i);
			वापस -ENOMEM;
		पूर्ण
		sg_set_buf(sg, addr, PAGE_SIZE);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा zfcp_fc_req *zfcp_fc_alloc_sg_env(पूर्णांक buf_num)
अणु
	काष्ठा zfcp_fc_req *fc_req;

	fc_req = kmem_cache_zalloc(zfcp_fc_req_cache, GFP_KERNEL);
	अगर (!fc_req)
		वापस शून्य;

	अगर (zfcp_fc_sg_setup_table(&fc_req->sg_rsp, buf_num)) अणु
		kmem_cache_मुक्त(zfcp_fc_req_cache, fc_req);
		वापस शून्य;
	पूर्ण

	sg_init_one(&fc_req->sg_req, &fc_req->u.gpn_ft.req,
		    माप(काष्ठा zfcp_fc_gpn_ft_req));

	वापस fc_req;
पूर्ण

अटल पूर्णांक zfcp_fc_send_gpn_ft(काष्ठा zfcp_fc_req *fc_req,
			       काष्ठा zfcp_adapter *adapter, पूर्णांक max_bytes)
अणु
	काष्ठा zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	काष्ठा zfcp_fc_gpn_ft_req *req = &fc_req->u.gpn_ft.req;
	DECLARE_COMPLETION_ONSTACK(completion);
	पूर्णांक ret;

	zfcp_fc_ct_ns_init(&req->ct_hdr, FC_NS_GPN_FT, max_bytes);
	req->gpn_ft.fn_fc4_type = FC_TYPE_FCP;

	ct_els->handler = zfcp_fc_complete;
	ct_els->handler_data = &completion;
	ct_els->req = &fc_req->sg_req;
	ct_els->resp = &fc_req->sg_rsp;

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, ct_els, शून्य,
			       ZFCP_FC_CTELS_TMO);
	अगर (!ret)
		रुको_क्रम_completion(&completion);
	वापस ret;
पूर्ण

अटल व्योम zfcp_fc_validate_port(काष्ठा zfcp_port *port, काष्ठा list_head *lh)
अणु
	अगर (!(atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_NOESC))
		वापस;

	atomic_andnot(ZFCP_STATUS_COMMON_NOESC, &port->status);

	अगर ((port->supported_classes != 0) ||
	    !list_empty(&port->unit_list))
		वापस;

	list_move_tail(&port->list, lh);
पूर्ण

अटल पूर्णांक zfcp_fc_eval_gpn_ft(काष्ठा zfcp_fc_req *fc_req,
			       काष्ठा zfcp_adapter *adapter, पूर्णांक max_entries)
अणु
	काष्ठा zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	काष्ठा scatterlist *sg = &fc_req->sg_rsp;
	काष्ठा fc_ct_hdr *hdr = sg_virt(sg);
	काष्ठा fc_gpn_ft_resp *acc = sg_virt(sg);
	काष्ठा zfcp_port *port, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(हटाओ_lh);
	u32 d_id;
	पूर्णांक ret = 0, x, last = 0;

	अगर (ct_els->status)
		वापस -EIO;

	अगर (hdr->ct_cmd != cpu_to_be16(FC_FS_ACC)) अणु
		अगर (hdr->ct_reason == FC_FS_RJT_UNABL)
			वापस -EAGAIN; /* might be a temporary condition */
		वापस -EIO;
	पूर्ण

	अगर (hdr->ct_mr_size) अणु
		dev_warn(&adapter->ccw_device->dev,
			 "The name server reported %d words residual data\n",
			 hdr->ct_mr_size);
		वापस -E2BIG;
	पूर्ण

	/* first entry is the header */
	क्रम (x = 1; x < max_entries && !last; x++) अणु
		अगर (x % (ZFCP_FC_GPN_FT_ENT_PAGE + 1))
			acc++;
		अन्यथा
			acc = sg_virt(++sg);

		last = acc->fp_flags & FC_NS_FID_LAST;
		d_id = ntoh24(acc->fp_fid);

		/* करोn't attach ports with a well known address */
		अगर (d_id >= FC_FID_WELL_KNOWN_BASE)
			जारी;
		/* skip the adapter's port and known remote ports */
		अगर (be64_to_cpu(acc->fp_wwpn) ==
		    fc_host_port_name(adapter->scsi_host))
			जारी;

		port = zfcp_port_enqueue(adapter, be64_to_cpu(acc->fp_wwpn),
					 ZFCP_STATUS_COMMON_NOESC, d_id);
		अगर (!IS_ERR(port))
			zfcp_erp_port_reखोलो(port, 0, "fcegpf1");
		अन्यथा अगर (PTR_ERR(port) != -EEXIST)
			ret = PTR_ERR(port);
	पूर्ण

	zfcp_erp_रुको(adapter);
	ग_लिखो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry_safe(port, पंचांगp, &adapter->port_list, list)
		zfcp_fc_validate_port(port, &हटाओ_lh);
	ग_लिखो_unlock_irqrestore(&adapter->port_list_lock, flags);

	list_क्रम_each_entry_safe(port, पंचांगp, &हटाओ_lh, list) अणु
		zfcp_erp_port_shutकरोwn(port, 0, "fcegpf2");
		device_unरेजिस्टर(&port->dev);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * zfcp_fc_scan_ports - scan remote ports and attach new ports
 * @work: reference to scheduled work
 */
व्योम zfcp_fc_scan_ports(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा zfcp_adapter *adapter = container_of(dw, काष्ठा zfcp_adapter,
						    scan_work);
	पूर्णांक ret, i;
	काष्ठा zfcp_fc_req *fc_req;
	पूर्णांक chain, max_entries, buf_num, max_bytes;

	zfcp_fc_port_scan_समय(adapter);

	chain = adapter->adapter_features & FSF_FEATURE_ELS_CT_CHAINED_SBALS;
	buf_num = chain ? ZFCP_FC_GPN_FT_NUM_BUFS : 1;
	max_entries = chain ? ZFCP_FC_GPN_FT_MAX_ENT : ZFCP_FC_GPN_FT_ENT_PAGE;
	max_bytes = chain ? ZFCP_FC_GPN_FT_MAX_SIZE : ZFCP_FC_CT_SIZE_PAGE;

	अगर (fc_host_port_type(adapter->scsi_host) != FC_PORTTYPE_NPORT &&
	    fc_host_port_type(adapter->scsi_host) != FC_PORTTYPE_NPIV)
		वापस;

	अगर (zfcp_fc_wka_port_get(&adapter->gs->ds))
		वापस;

	fc_req = zfcp_fc_alloc_sg_env(buf_num);
	अगर (!fc_req)
		जाओ out;

	क्रम (i = 0; i < 3; i++) अणु
		ret = zfcp_fc_send_gpn_ft(fc_req, adapter, max_bytes);
		अगर (!ret) अणु
			ret = zfcp_fc_eval_gpn_ft(fc_req, adapter, max_entries);
			अगर (ret == -EAGAIN)
				ssleep(1);
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	zfcp_fc_sg_मुक्त_table(&fc_req->sg_rsp, buf_num);
	kmem_cache_मुक्त(zfcp_fc_req_cache, fc_req);
out:
	zfcp_fc_wka_port_put(&adapter->gs->ds);
पूर्ण

अटल पूर्णांक zfcp_fc_gspn(काष्ठा zfcp_adapter *adapter,
			काष्ठा zfcp_fc_req *fc_req)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	अक्षर devno[] = "DEVNO:";
	काष्ठा zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	काष्ठा zfcp_fc_gspn_req *gspn_req = &fc_req->u.gspn.req;
	काष्ठा zfcp_fc_gspn_rsp *gspn_rsp = &fc_req->u.gspn.rsp;
	पूर्णांक ret;

	zfcp_fc_ct_ns_init(&gspn_req->ct_hdr, FC_NS_GSPN_ID,
			   FC_SYMBOLIC_NAME_SIZE);
	hton24(gspn_req->gspn.fp_fid, fc_host_port_id(adapter->scsi_host));

	sg_init_one(&fc_req->sg_req, gspn_req, माप(*gspn_req));
	sg_init_one(&fc_req->sg_rsp, gspn_rsp, माप(*gspn_rsp));

	ct_els->handler = zfcp_fc_complete;
	ct_els->handler_data = &completion;
	ct_els->req = &fc_req->sg_req;
	ct_els->resp = &fc_req->sg_rsp;

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, ct_els, शून्य,
			       ZFCP_FC_CTELS_TMO);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion(&completion);
	अगर (ct_els->status)
		वापस ct_els->status;

	अगर (fc_host_port_type(adapter->scsi_host) == FC_PORTTYPE_NPIV &&
	    !(म_माला(gspn_rsp->gspn.fp_name, devno)))
		snम_लिखो(fc_host_symbolic_name(adapter->scsi_host),
			 FC_SYMBOLIC_NAME_SIZE, "%s%s %s NAME: %s",
			 gspn_rsp->gspn.fp_name, devno,
			 dev_name(&adapter->ccw_device->dev),
			 init_utsname()->nodename);
	अन्यथा
		strlcpy(fc_host_symbolic_name(adapter->scsi_host),
			gspn_rsp->gspn.fp_name, FC_SYMBOLIC_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम zfcp_fc_rspn(काष्ठा zfcp_adapter *adapter,
			 काष्ठा zfcp_fc_req *fc_req)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा Scsi_Host *shost = adapter->scsi_host;
	काष्ठा zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	काष्ठा zfcp_fc_rspn_req *rspn_req = &fc_req->u.rspn.req;
	काष्ठा fc_ct_hdr *rspn_rsp = &fc_req->u.rspn.rsp;
	पूर्णांक ret, len;

	zfcp_fc_ct_ns_init(&rspn_req->ct_hdr, FC_NS_RSPN_ID,
			   FC_SYMBOLIC_NAME_SIZE);
	hton24(rspn_req->rspn.fr_fid.fp_fid, fc_host_port_id(shost));
	len = strlcpy(rspn_req->rspn.fr_name, fc_host_symbolic_name(shost),
		      FC_SYMBOLIC_NAME_SIZE);
	rspn_req->rspn.fr_name_len = len;

	sg_init_one(&fc_req->sg_req, rspn_req, माप(*rspn_req));
	sg_init_one(&fc_req->sg_rsp, rspn_rsp, माप(*rspn_rsp));

	ct_els->handler = zfcp_fc_complete;
	ct_els->handler_data = &completion;
	ct_els->req = &fc_req->sg_req;
	ct_els->resp = &fc_req->sg_rsp;

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, ct_els, शून्य,
			       ZFCP_FC_CTELS_TMO);
	अगर (!ret)
		रुको_क्रम_completion(&completion);
पूर्ण

/**
 * zfcp_fc_sym_name_update - Retrieve and update the symbolic port name
 * @work: ns_up_work of the adapter where to update the symbolic port name
 *
 * Retrieve the current symbolic port name that may have been set by
 * the hardware using the GSPN request and update the fc_host
 * symbolic_name sysfs attribute. When running in NPIV mode (and hence
 * the port name is unique क्रम this प्रणाली), update the symbolic port
 * name to add Linux specअगरic inक्रमmation and update the FC nameserver
 * using the RSPN request.
 */
व्योम zfcp_fc_sym_name_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_adapter *adapter = container_of(work, काष्ठा zfcp_adapter,
						    ns_up_work);
	पूर्णांक ret;
	काष्ठा zfcp_fc_req *fc_req;

	अगर (fc_host_port_type(adapter->scsi_host) != FC_PORTTYPE_NPORT &&
	    fc_host_port_type(adapter->scsi_host) != FC_PORTTYPE_NPIV)
		वापस;

	fc_req = kmem_cache_zalloc(zfcp_fc_req_cache, GFP_KERNEL);
	अगर (!fc_req)
		वापस;

	ret = zfcp_fc_wka_port_get(&adapter->gs->ds);
	अगर (ret)
		जाओ out_मुक्त;

	ret = zfcp_fc_gspn(adapter, fc_req);
	अगर (ret || fc_host_port_type(adapter->scsi_host) != FC_PORTTYPE_NPIV)
		जाओ out_ds_put;

	स_रखो(fc_req, 0, माप(*fc_req));
	zfcp_fc_rspn(adapter, fc_req);

out_ds_put:
	zfcp_fc_wka_port_put(&adapter->gs->ds);
out_मुक्त:
	kmem_cache_मुक्त(zfcp_fc_req_cache, fc_req);
पूर्ण

अटल व्योम zfcp_fc_ct_els_job_handler(व्योम *data)
अणु
	काष्ठा bsg_job *job = data;
	काष्ठा zfcp_fsf_ct_els *zfcp_ct_els = job->dd_data;
	काष्ठा fc_bsg_reply *jr = job->reply;

	jr->reply_payload_rcv_len = job->reply_payload.payload_len;
	jr->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	jr->result = zfcp_ct_els->status ? -EIO : 0;
	bsg_job_करोne(job, jr->result, jr->reply_payload_rcv_len);
पूर्ण

अटल काष्ठा zfcp_fc_wka_port *zfcp_fc_job_wka_port(काष्ठा bsg_job *job)
अणु
	u32 preamble_word1;
	u8 gs_type;
	काष्ठा zfcp_adapter *adapter;
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);
	काष्ठा Scsi_Host *shost;

	preamble_word1 = bsg_request->rqst_data.r_ct.preamble_word1;
	gs_type = (preamble_word1 & 0xff000000) >> 24;

	shost = rport ? rport_to_shost(rport) : fc_bsg_to_shost(job);
	adapter = (काष्ठा zfcp_adapter *) shost->hostdata[0];

	चयन (gs_type) अणु
	हाल FC_FST_ALIAS:
		वापस &adapter->gs->as;
	हाल FC_FST_MGMT:
		वापस &adapter->gs->ms;
	हाल FC_FST_TIME:
		वापस &adapter->gs->ts;
		अवरोध;
	हाल FC_FST_सूची:
		वापस &adapter->gs->ds;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम zfcp_fc_ct_job_handler(व्योम *data)
अणु
	काष्ठा bsg_job *job = data;
	काष्ठा zfcp_fc_wka_port *wka_port;

	wka_port = zfcp_fc_job_wka_port(job);
	zfcp_fc_wka_port_put(wka_port);

	zfcp_fc_ct_els_job_handler(data);
पूर्ण

अटल पूर्णांक zfcp_fc_exec_els_job(काष्ठा bsg_job *job,
				काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_fsf_ct_els *els = job->dd_data;
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा zfcp_port *port;
	u32 d_id;

	अगर (rport) अणु
		port = zfcp_get_port_by_wwpn(adapter, rport->port_name);
		अगर (!port)
			वापस -EINVAL;

		d_id = port->d_id;
		put_device(&port->dev);
	पूर्ण अन्यथा
		d_id = ntoh24(bsg_request->rqst_data.h_els.port_id);

	els->handler = zfcp_fc_ct_els_job_handler;
	वापस zfcp_fsf_send_els(adapter, d_id, els, job->समयout / HZ);
पूर्ण

अटल पूर्णांक zfcp_fc_exec_ct_job(काष्ठा bsg_job *job,
			       काष्ठा zfcp_adapter *adapter)
अणु
	पूर्णांक ret;
	काष्ठा zfcp_fsf_ct_els *ct = job->dd_data;
	काष्ठा zfcp_fc_wka_port *wka_port;

	wka_port = zfcp_fc_job_wka_port(job);
	अगर (!wka_port)
		वापस -EINVAL;

	ret = zfcp_fc_wka_port_get(wka_port);
	अगर (ret)
		वापस ret;

	ct->handler = zfcp_fc_ct_job_handler;
	ret = zfcp_fsf_send_ct(wka_port, ct, शून्य, job->समयout / HZ);
	अगर (ret)
		zfcp_fc_wka_port_put(wka_port);

	वापस ret;
पूर्ण

पूर्णांक zfcp_fc_exec_bsg_job(काष्ठा bsg_job *job)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा zfcp_adapter *adapter;
	काष्ठा zfcp_fsf_ct_els *ct_els = job->dd_data;
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);

	shost = rport ? rport_to_shost(rport) : fc_bsg_to_shost(job);
	adapter = (काष्ठा zfcp_adapter *)shost->hostdata[0];

	अगर (!(atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_COMMON_OPEN))
		वापस -EINVAL;

	ct_els->req = job->request_payload.sg_list;
	ct_els->resp = job->reply_payload.sg_list;
	ct_els->handler_data = job;

	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_RPT_ELS:
	हाल FC_BSG_HST_ELS_NOLOGIN:
		वापस zfcp_fc_exec_els_job(job, adapter);
	हाल FC_BSG_RPT_CT:
	हाल FC_BSG_HST_CT:
		वापस zfcp_fc_exec_ct_job(job, adapter);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक zfcp_fc_समयout_bsg_job(काष्ठा bsg_job *job)
अणु
	/* hardware tracks समयout, reset bsg समयout to not पूर्णांकerfere */
	वापस -EAGAIN;
पूर्ण

पूर्णांक zfcp_fc_gs_setup(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_fc_wka_ports *wka_ports;

	wka_ports = kzalloc(माप(काष्ठा zfcp_fc_wka_ports), GFP_KERNEL);
	अगर (!wka_ports)
		वापस -ENOMEM;

	adapter->gs = wka_ports;
	zfcp_fc_wka_port_init(&wka_ports->ms, FC_FID_MGMT_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->ts, FC_FID_TIME_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->ds, FC_FID_सूची_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->as, FC_FID_ALIASES, adapter);

	वापस 0;
पूर्ण

व्योम zfcp_fc_gs_destroy(काष्ठा zfcp_adapter *adapter)
अणु
	kमुक्त(adapter->gs);
	adapter->gs = शून्य;
पूर्ण

