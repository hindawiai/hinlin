<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Implementation of FSF commands.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/blktrace_api.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_fc.h"
#समावेश "zfcp_dbf.h"
#समावेश "zfcp_qdio.h"
#समावेश "zfcp_reqlist.h"
#समावेश "zfcp_diag.h"

/* समयout क्रम FSF requests sent during scsi_eh: पात or FCP TMF */
#घोषणा ZFCP_FSF_SCSI_ER_TIMEOUT (10*HZ)
/* समयout क्रम: exchange config/port data outside ERP, or खोलो/बंद WKA port */
#घोषणा ZFCP_FSF_REQUEST_TIMEOUT (60*HZ)

काष्ठा kmem_cache *zfcp_fsf_qtcb_cache;

अटल bool ber_stop = true;
module_param(ber_stop, bool, 0600);
MODULE_PARM_DESC(ber_stop,
		 "Shuts down FCP devices for FCP channels that report a bit-error count in excess of its threshold (default on)");

अटल व्योम zfcp_fsf_request_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा zfcp_fsf_req *fsf_req = from_समयr(fsf_req, t, समयr);
	काष्ठा zfcp_adapter *adapter = fsf_req->adapter;

	zfcp_qdio_siosl(adapter);
	zfcp_erp_adapter_reखोलो(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
				"fsrth_1");
पूर्ण

अटल व्योम zfcp_fsf_start_समयr(काष्ठा zfcp_fsf_req *fsf_req,
				 अचिन्हित दीर्घ समयout)
अणु
	fsf_req->समयr.function = zfcp_fsf_request_समयout_handler;
	fsf_req->समयr.expires = jअगरfies + समयout;
	add_समयr(&fsf_req->समयr);
पूर्ण

अटल व्योम zfcp_fsf_start_erp_समयr(काष्ठा zfcp_fsf_req *fsf_req)
अणु
	BUG_ON(!fsf_req->erp_action);
	fsf_req->समयr.function = zfcp_erp_समयout_handler;
	fsf_req->समयr.expires = jअगरfies + 30 * HZ;
	add_समयr(&fsf_req->समयr);
पूर्ण

/* association between FSF command and FSF QTCB type */
अटल u32 fsf_qtcb_type[] = अणु
	[FSF_QTCB_FCP_CMND] =             FSF_IO_COMMAND,
	[FSF_QTCB_ABORT_FCP_CMND] =       FSF_SUPPORT_COMMAND,
	[FSF_QTCB_OPEN_PORT_WITH_DID] =   FSF_SUPPORT_COMMAND,
	[FSF_QTCB_OPEN_LUN] =             FSF_SUPPORT_COMMAND,
	[FSF_QTCB_CLOSE_LUN] =            FSF_SUPPORT_COMMAND,
	[FSF_QTCB_CLOSE_PORT] =           FSF_SUPPORT_COMMAND,
	[FSF_QTCB_CLOSE_PHYSICAL_PORT] =  FSF_SUPPORT_COMMAND,
	[FSF_QTCB_SEND_ELS] =             FSF_SUPPORT_COMMAND,
	[FSF_QTCB_SEND_GENERIC] =         FSF_SUPPORT_COMMAND,
	[FSF_QTCB_EXCHANGE_CONFIG_DATA] = FSF_CONFIG_COMMAND,
	[FSF_QTCB_EXCHANGE_PORT_DATA] =   FSF_PORT_COMMAND,
	[FSF_QTCB_DOWNLOAD_CONTROL_खाता] = FSF_SUPPORT_COMMAND,
	[FSF_QTCB_UPLOAD_CONTROL_खाता] =  FSF_SUPPORT_COMMAND
पूर्ण;

अटल व्योम zfcp_fsf_class_not_supp(काष्ठा zfcp_fsf_req *req)
अणु
	dev_err(&req->adapter->ccw_device->dev, "FCP device not "
		"operational because of an unsupported FC class\n");
	zfcp_erp_adapter_shutकरोwn(req->adapter, 0, "fscns_1");
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
पूर्ण

/**
 * zfcp_fsf_req_मुक्त - मुक्त memory used by fsf request
 * @req: poपूर्णांकer to काष्ठा zfcp_fsf_req
 */
व्योम zfcp_fsf_req_मुक्त(काष्ठा zfcp_fsf_req *req)
अणु
	अगर (likely(req->pool)) अणु
		अगर (likely(!zfcp_fsf_req_is_status_पढ़ो_buffer(req)))
			mempool_मुक्त(req->qtcb, req->adapter->pool.qtcb_pool);
		mempool_मुक्त(req, req->pool);
		वापस;
	पूर्ण

	अगर (likely(!zfcp_fsf_req_is_status_पढ़ो_buffer(req)))
		kmem_cache_मुक्त(zfcp_fsf_qtcb_cache, req->qtcb);
	kमुक्त(req);
पूर्ण

अटल व्योम zfcp_fsf_status_पढ़ो_port_बंदd(काष्ठा zfcp_fsf_req *req)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fsf_status_पढ़ो_buffer *sr_buf = req->data;
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_port *port;
	पूर्णांक d_id = ntoh24(sr_buf->d_id);

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		अगर (port->d_id == d_id) अणु
			zfcp_erp_port_reखोलो(port, 0, "fssrpc1");
			अवरोध;
		पूर्ण
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
पूर्ण

व्योम zfcp_fsf_fc_host_link_करोwn(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा Scsi_Host *shost = adapter->scsi_host;

	adapter->hydra_version = 0;
	adapter->peer_wwpn = 0;
	adapter->peer_wwnn = 0;
	adapter->peer_d_id = 0;

	/* अगर there is no shost yet, we have nothing to zero-out */
	अगर (shost == शून्य)
		वापस;

	fc_host_port_id(shost) = 0;
	fc_host_fabric_name(shost) = 0;
	fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
	fc_host_port_type(shost) = FC_PORTTYPE_UNKNOWN;
	snम_लिखो(fc_host_model(shost), FC_SYMBOLIC_NAME_SIZE, "0x%04x", 0);
	स_रखो(fc_host_active_fc4s(shost), 0, FC_FC4_LIST_SIZE);
पूर्ण

अटल व्योम zfcp_fsf_link_करोwn_info_eval(काष्ठा zfcp_fsf_req *req,
					 काष्ठा fsf_link_करोwn_info *link_करोwn)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED)
		वापस;

	atomic_or(ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED, &adapter->status);

	zfcp_scsi_schedule_rports_block(adapter);

	zfcp_fsf_fc_host_link_करोwn(adapter);

	अगर (!link_करोwn)
		जाओ out;

	चयन (link_करोwn->error_code) अणु
	हाल FSF_PSQ_LINK_NO_LIGHT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "There is no light signal from the local "
			 "fibre channel cable\n");
		अवरोध;
	हाल FSF_PSQ_LINK_WRAP_PLUG:
		dev_warn(&req->adapter->ccw_device->dev,
			 "There is a wrap plug instead of a fibre "
			 "channel cable\n");
		अवरोध;
	हाल FSF_PSQ_LINK_NO_FCP:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The adjacent fibre channel node does not "
			 "support FCP\n");
		अवरोध;
	हाल FSF_PSQ_LINK_FIRMWARE_UPDATE:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP device is suspended because of a "
			 "firmware update\n");
		अवरोध;
	हाल FSF_PSQ_LINK_INVALID_WWPN:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP device detected a WWPN that is "
			 "duplicate or not valid\n");
		अवरोध;
	हाल FSF_PSQ_LINK_NO_NPIV_SUPPORT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The fibre channel fabric does not support NPIV\n");
		अवरोध;
	हाल FSF_PSQ_LINK_NO_FCP_RESOURCES:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP adapter cannot support more NPIV ports\n");
		अवरोध;
	हाल FSF_PSQ_LINK_NO_FABRIC_RESOURCES:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The adjacent switch cannot support "
			 "more NPIV ports\n");
		अवरोध;
	हाल FSF_PSQ_LINK_FABRIC_LOGIN_UNABLE:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP adapter could not log in to the "
			 "fibre channel fabric\n");
		अवरोध;
	हाल FSF_PSQ_LINK_WWPN_ASSIGNMENT_CORRUPTED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The WWPN assignment file on the FCP adapter "
			 "has been damaged\n");
		अवरोध;
	हाल FSF_PSQ_LINK_MODE_TABLE_CURRUPTED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The mode table on the FCP adapter "
			 "has been damaged\n");
		अवरोध;
	हाल FSF_PSQ_LINK_NO_WWPN_ASSIGNMENT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "All NPIV ports on the FCP adapter have "
			 "been assigned\n");
		अवरोध;
	शेष:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The link between the FCP adapter and "
			 "the FC fabric is down\n");
	पूर्ण
out:
	zfcp_erp_set_adapter_status(adapter, ZFCP_STATUS_COMMON_ERP_FAILED);
पूर्ण

अटल व्योम zfcp_fsf_status_पढ़ो_link_करोwn(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_status_पढ़ो_buffer *sr_buf = req->data;
	काष्ठा fsf_link_करोwn_info *ldi =
		(काष्ठा fsf_link_करोwn_info *) &sr_buf->payload;

	चयन (sr_buf->status_subtype) अणु
	हाल FSF_STATUS_READ_SUB_NO_PHYSICAL_LINK:
	हाल FSF_STATUS_READ_SUB_FDISC_FAILED:
		zfcp_fsf_link_करोwn_info_eval(req, ldi);
		अवरोध;
	हाल FSF_STATUS_READ_SUB_FIRMWARE_UPDATE:
		zfcp_fsf_link_करोwn_info_eval(req, शून्य);
	पूर्ण
पूर्ण

अटल व्योम
zfcp_fsf_status_पढ़ो_version_change(काष्ठा zfcp_adapter *adapter,
				    काष्ठा fsf_status_पढ़ो_buffer *sr_buf)
अणु
	अगर (sr_buf->status_subtype == FSF_STATUS_READ_SUB_LIC_CHANGE) अणु
		u32 version = sr_buf->payload.version_change.current_version;

		WRITE_ONCE(adapter->fsf_lic_version, version);
		snम_लिखो(fc_host_firmware_version(adapter->scsi_host),
			 FC_VERSION_STRING_SIZE, "%#08x", version);
	पूर्ण
पूर्ण

अटल व्योम zfcp_fsf_status_पढ़ो_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा fsf_status_पढ़ो_buffer *sr_buf = req->data;

	अगर (req->status & ZFCP_STATUS_FSFREQ_DISMISSED) अणु
		zfcp_dbf_hba_fsf_uss("fssrh_1", req);
		mempool_मुक्त(virt_to_page(sr_buf), adapter->pool.sr_data);
		zfcp_fsf_req_मुक्त(req);
		वापस;
	पूर्ण

	zfcp_dbf_hba_fsf_uss("fssrh_4", req);

	चयन (sr_buf->status_type) अणु
	हाल FSF_STATUS_READ_PORT_CLOSED:
		zfcp_fsf_status_पढ़ो_port_बंदd(req);
		अवरोध;
	हाल FSF_STATUS_READ_INCOMING_ELS:
		zfcp_fc_incoming_els(req);
		अवरोध;
	हाल FSF_STATUS_READ_SENSE_DATA_AVAIL:
		अवरोध;
	हाल FSF_STATUS_READ_BIT_ERROR_THRESHOLD:
		zfcp_dbf_hba_bit_err("fssrh_3", req);
		अगर (ber_stop) अणु
			dev_warn(&adapter->ccw_device->dev,
				 "All paths over this FCP device are disused because of excessive bit errors\n");
			zfcp_erp_adapter_shutकरोwn(adapter, 0, "fssrh_b");
		पूर्ण अन्यथा अणु
			dev_warn(&adapter->ccw_device->dev,
				 "The error threshold for checksum statistics has been exceeded\n");
		पूर्ण
		अवरोध;
	हाल FSF_STATUS_READ_LINK_DOWN:
		zfcp_fsf_status_पढ़ो_link_करोwn(req);
		zfcp_fc_enqueue_event(adapter, FCH_EVT_LINKDOWN, 0);
		अवरोध;
	हाल FSF_STATUS_READ_LINK_UP:
		dev_info(&adapter->ccw_device->dev,
			 "The local link has been restored\n");
		/* All ports should be marked as पढ़ोy to run again */
		zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_adapter_reखोलो(adapter,
					ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
					ZFCP_STATUS_COMMON_ERP_FAILED,
					"fssrh_2");
		zfcp_fc_enqueue_event(adapter, FCH_EVT_LINKUP, 0);

		अवरोध;
	हाल FSF_STATUS_READ_NOTIFICATION_LOST:
		अगर (sr_buf->status_subtype & FSF_STATUS_READ_SUB_INCOMING_ELS)
			zfcp_fc_conditional_port_scan(adapter);
		अगर (sr_buf->status_subtype & FSF_STATUS_READ_SUB_VERSION_CHANGE)
			queue_work(adapter->work_queue,
				   &adapter->version_change_lost_work);
		अवरोध;
	हाल FSF_STATUS_READ_FEATURE_UPDATE_ALERT:
		adapter->adapter_features = sr_buf->payload.word[0];
		अवरोध;
	हाल FSF_STATUS_READ_VERSION_CHANGE:
		zfcp_fsf_status_पढ़ो_version_change(adapter, sr_buf);
		अवरोध;
	पूर्ण

	mempool_मुक्त(virt_to_page(sr_buf), adapter->pool.sr_data);
	zfcp_fsf_req_मुक्त(req);

	atomic_inc(&adapter->stat_miss);
	queue_work(adapter->work_queue, &adapter->stat_work);
पूर्ण

अटल व्योम zfcp_fsf_fsख_स्थितिus_qual_eval(काष्ठा zfcp_fsf_req *req)
अणु
	चयन (req->qtcb->header.fsf_status_qual.word[0]) अणु
	हाल FSF_SQ_FCP_RSP_AVAILABLE:
	हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
	हाल FSF_SQ_NO_RETRY_POSSIBLE:
	हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
		वापस;
	हाल FSF_SQ_COMMAND_ABORTED:
		अवरोध;
	हाल FSF_SQ_NO_RECOM:
		dev_err(&req->adapter->ccw_device->dev,
			"The FCP adapter reported a problem "
			"that cannot be recovered\n");
		zfcp_qdio_siosl(req->adapter);
		zfcp_erp_adapter_shutकरोwn(req->adapter, 0, "fsfsqe1");
		अवरोध;
	पूर्ण
	/* all non-वापस stats set FSFREQ_ERROR*/
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
पूर्ण

अटल व्योम zfcp_fsf_fsख_स्थितिus_eval(काष्ठा zfcp_fsf_req *req)
अणु
	अगर (unlikely(req->status & ZFCP_STATUS_FSFREQ_ERROR))
		वापस;

	चयन (req->qtcb->header.fsf_status) अणु
	हाल FSF_UNKNOWN_COMMAND:
		dev_err(&req->adapter->ccw_device->dev,
			"The FCP adapter does not recognize the command 0x%x\n",
			req->qtcb->header.fsf_command);
		zfcp_erp_adapter_shutकरोwn(req->adapter, 0, "fsfse_1");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		zfcp_fsf_fsख_स्थितिus_qual_eval(req);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम zfcp_fsf_protstatus_eval(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा fsf_qtcb *qtcb = req->qtcb;
	जोड़ fsf_prot_status_qual *psq = &qtcb->prefix.prot_status_qual;

	zfcp_dbf_hba_fsf_response(req);

	अगर (req->status & ZFCP_STATUS_FSFREQ_DISMISSED) अणु
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		वापस;
	पूर्ण

	चयन (qtcb->prefix.prot_status) अणु
	हाल FSF_PROT_GOOD:
	हाल FSF_PROT_FSF_STATUS_PRESENTED:
		वापस;
	हाल FSF_PROT_QTCB_VERSION_ERROR:
		dev_err(&adapter->ccw_device->dev,
			"QTCB version 0x%x not supported by FCP adapter "
			"(0x%x to 0x%x)\n", FSF_QTCB_CURRENT_VERSION,
			psq->word[0], psq->word[1]);
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fspse_1");
		अवरोध;
	हाल FSF_PROT_ERROR_STATE:
	हाल FSF_PROT_SEQ_NUMB_ERROR:
		zfcp_erp_adapter_reखोलो(adapter, 0, "fspse_2");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_PROT_UNSUPP_QTCB_TYPE:
		dev_err(&adapter->ccw_device->dev,
			"The QTCB type is not supported by the FCP adapter\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fspse_3");
		अवरोध;
	हाल FSF_PROT_HOST_CONNECTION_INITIALIZING:
		atomic_or(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
				&adapter->status);
		अवरोध;
	हाल FSF_PROT_DUPLICATE_REQUEST_ID:
		dev_err(&adapter->ccw_device->dev,
			"0x%Lx is an ambiguous request identifier\n",
			(अचिन्हित दीर्घ दीर्घ)qtcb->bottom.support.req_handle);
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fspse_4");
		अवरोध;
	हाल FSF_PROT_LINK_DOWN:
		zfcp_fsf_link_करोwn_info_eval(req, &psq->link_करोwn_info);
		/* go through reखोलो to flush pending requests */
		zfcp_erp_adapter_reखोलो(adapter, 0, "fspse_6");
		अवरोध;
	हाल FSF_PROT_REEST_QUEUE:
		/* All ports should be marked as पढ़ोy to run again */
		zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_adapter_reखोलो(adapter,
					ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
					ZFCP_STATUS_COMMON_ERP_FAILED,
					"fspse_8");
		अवरोध;
	शेष:
		dev_err(&adapter->ccw_device->dev,
			"0x%x is not a valid transfer protocol status\n",
			qtcb->prefix.prot_status);
		zfcp_qdio_siosl(adapter);
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fspse_9");
	पूर्ण
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
पूर्ण

/**
 * zfcp_fsf_req_complete - process completion of a FSF request
 * @req: The FSF request that has been completed.
 *
 * When a request has been completed either from the FCP adapter,
 * or it has been dismissed due to a queue shutकरोwn, this function
 * is called to process the completion status and trigger further
 * events related to the FSF request.
 * Caller must ensure that the request has been हटाओd from
 * adapter->req_list, to protect against concurrent modअगरication
 * by zfcp_erp_strategy_check_fsfreq().
 */
अटल व्योम zfcp_fsf_req_complete(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_erp_action *erp_action;

	अगर (unlikely(zfcp_fsf_req_is_status_पढ़ो_buffer(req))) अणु
		zfcp_fsf_status_पढ़ो_handler(req);
		वापस;
	पूर्ण

	del_समयr_sync(&req->समयr);
	zfcp_fsf_protstatus_eval(req);
	zfcp_fsf_fsख_स्थितिus_eval(req);
	req->handler(req);

	erp_action = req->erp_action;
	अगर (erp_action)
		zfcp_erp_notअगरy(erp_action, 0);

	अगर (likely(req->status & ZFCP_STATUS_FSFREQ_CLEANUP))
		zfcp_fsf_req_मुक्त(req);
	अन्यथा
		complete(&req->completion);
पूर्ण

/**
 * zfcp_fsf_req_dismiss_all - dismiss all fsf requests
 * @adapter: poपूर्णांकer to काष्ठा zfcp_adapter
 *
 * Never ever call this without shutting करोwn the adapter first.
 * Otherwise the adapter would जारी using and corrupting s390 storage.
 * Included BUG_ON() call to ensure this is करोne.
 * ERP is supposed to be the only user of this function.
 */
व्योम zfcp_fsf_req_dismiss_all(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा zfcp_fsf_req *req, *पंचांगp;
	LIST_HEAD(हटाओ_queue);

	BUG_ON(atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP);
	zfcp_reqlist_move(adapter->req_list, &हटाओ_queue);

	list_क्रम_each_entry_safe(req, पंचांगp, &हटाओ_queue, list) अणु
		list_del(&req->list);
		req->status |= ZFCP_STATUS_FSFREQ_DISMISSED;
		zfcp_fsf_req_complete(req);
	पूर्ण
पूर्ण

#घोषणा ZFCP_FSF_PORTSPEED_1GBIT	(1 <<  0)
#घोषणा ZFCP_FSF_PORTSPEED_2GBIT	(1 <<  1)
#घोषणा ZFCP_FSF_PORTSPEED_4GBIT	(1 <<  2)
#घोषणा ZFCP_FSF_PORTSPEED_10GBIT	(1 <<  3)
#घोषणा ZFCP_FSF_PORTSPEED_8GBIT	(1 <<  4)
#घोषणा ZFCP_FSF_PORTSPEED_16GBIT	(1 <<  5)
#घोषणा ZFCP_FSF_PORTSPEED_32GBIT	(1 <<  6)
#घोषणा ZFCP_FSF_PORTSPEED_64GBIT	(1 <<  7)
#घोषणा ZFCP_FSF_PORTSPEED_128GBIT	(1 <<  8)
#घोषणा ZFCP_FSF_PORTSPEED_NOT_NEGOTIATED (1 << 15)

u32 zfcp_fsf_convert_portspeed(u32 fsf_speed)
अणु
	u32 fdmi_speed = 0;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_1GBIT)
		fdmi_speed |= FC_PORTSPEED_1GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_2GBIT)
		fdmi_speed |= FC_PORTSPEED_2GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_4GBIT)
		fdmi_speed |= FC_PORTSPEED_4GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_10GBIT)
		fdmi_speed |= FC_PORTSPEED_10GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_8GBIT)
		fdmi_speed |= FC_PORTSPEED_8GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_16GBIT)
		fdmi_speed |= FC_PORTSPEED_16GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_32GBIT)
		fdmi_speed |= FC_PORTSPEED_32GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_64GBIT)
		fdmi_speed |= FC_PORTSPEED_64GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_128GBIT)
		fdmi_speed |= FC_PORTSPEED_128GBIT;
	अगर (fsf_speed & ZFCP_FSF_PORTSPEED_NOT_NEGOTIATED)
		fdmi_speed |= FC_PORTSPEED_NOT_NEGOTIATED;
	वापस fdmi_speed;
पूर्ण

अटल पूर्णांक zfcp_fsf_exchange_config_evaluate(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा fsf_qtcb_bottom_config *bottom = &req->qtcb->bottom.config;
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा fc_els_flogi *plogi;

	/* adjust poपूर्णांकers क्रम missing command code */
	plogi = (काष्ठा fc_els_flogi *) ((u8 *)&bottom->plogi_payload
					- माप(u32));

	अगर (req->data)
		स_नकल(req->data, bottom, माप(*bottom));

	adapter->समयr_ticks = bottom->समयr_पूर्णांकerval & ZFCP_FSF_TIMER_INT_MASK;
	adapter->stat_पढ़ो_buf_num = max(bottom->status_पढ़ो_buf_num,
					 (u16)FSF_STATUS_READS_RECOM);

	/* no error वापस above here, otherwise must fix call chains */
	/* करो not evaluate invalid fields */
	अगर (req->qtcb->header.fsf_status == FSF_EXCHANGE_CONFIG_DATA_INCOMPLETE)
		वापस 0;

	adapter->hydra_version = bottom->adapter_type;

	चयन (bottom->fc_topology) अणु
	हाल FSF_TOPO_P2P:
		adapter->peer_d_id = ntoh24(bottom->peer_d_id);
		adapter->peer_wwpn = be64_to_cpu(plogi->fl_wwpn);
		adapter->peer_wwnn = be64_to_cpu(plogi->fl_wwnn);
		अवरोध;
	हाल FSF_TOPO_FABRIC:
		अवरोध;
	हाल FSF_TOPO_AL:
	शेष:
		dev_err(&adapter->ccw_device->dev,
			"Unknown or unsupported arbitrated loop "
			"fibre channel topology detected\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fsece_1");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zfcp_fsf_exchange_config_data_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_diag_header *स्थिर diag_hdr =
		&adapter->diagnostics->config_data.header;
	काष्ठा fsf_qtcb *qtcb = req->qtcb;
	काष्ठा fsf_qtcb_bottom_config *bottom = &qtcb->bottom.config;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	adapter->fsf_lic_version = bottom->lic_version;
	adapter->adapter_features = bottom->adapter_features;
	adapter->connection_features = bottom->connection_features;
	adapter->peer_wwpn = 0;
	adapter->peer_wwnn = 0;
	adapter->peer_d_id = 0;

	चयन (qtcb->header.fsf_status) अणु
	हाल FSF_GOOD:
		/*
		 * usually we रुको with an update till the cache is too old,
		 * but because we have the data available, update it anyway
		 */
		zfcp_diag_update_xdata(diag_hdr, bottom, false);

		zfcp_scsi_shost_update_config_data(adapter, bottom, false);
		अगर (zfcp_fsf_exchange_config_evaluate(req))
			वापस;

		अगर (bottom->max_qtcb_size < माप(काष्ठा fsf_qtcb)) अणु
			dev_err(&adapter->ccw_device->dev,
				"FCP adapter maximum QTCB size (%d bytes) "
				"is too small\n",
				bottom->max_qtcb_size);
			zfcp_erp_adapter_shutकरोwn(adapter, 0, "fsecdh1");
			वापस;
		पूर्ण
		atomic_or(ZFCP_STATUS_ADAPTER_XCONFIG_OK,
				&adapter->status);
		अवरोध;
	हाल FSF_EXCHANGE_CONFIG_DATA_INCOMPLETE:
		zfcp_diag_update_xdata(diag_hdr, bottom, true);
		req->status |= ZFCP_STATUS_FSFREQ_XDATAINCOMPLETE;

		/* aव्योमs adapter shutकरोwn to be able to recognize
		 * events such as LINK UP */
		atomic_or(ZFCP_STATUS_ADAPTER_XCONFIG_OK,
				&adapter->status);
		zfcp_fsf_link_करोwn_info_eval(req,
			&qtcb->header.fsf_status_qual.link_करोwn_info);

		zfcp_scsi_shost_update_config_data(adapter, bottom, true);
		अगर (zfcp_fsf_exchange_config_evaluate(req))
			वापस;
		अवरोध;
	शेष:
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fsecdh3");
		वापस;
	पूर्ण

	अगर (adapter->adapter_features & FSF_FEATURE_HBAAPI_MANAGEMENT)
		adapter->hardware_version = bottom->hardware_version;

	अगर (FSF_QTCB_CURRENT_VERSION < bottom->low_qtcb_version) अणु
		dev_err(&adapter->ccw_device->dev,
			"The FCP adapter only supports newer "
			"control block versions\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fsecdh4");
		वापस;
	पूर्ण
	अगर (FSF_QTCB_CURRENT_VERSION > bottom->high_qtcb_version) अणु
		dev_err(&adapter->ccw_device->dev,
			"The FCP adapter only supports older "
			"control block versions\n");
		zfcp_erp_adapter_shutकरोwn(adapter, 0, "fsecdh5");
	पूर्ण
पूर्ण

/*
 * Mapping of FC Endpoपूर्णांक Security flag masks to mnemonics
 *
 * NOTE: Update macro ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH when making any
 *       changes.
 */
अटल स्थिर काष्ठा अणु
	u32	mask;
	अक्षर	*name;
पूर्ण zfcp_fsf_fc_security_mnemonics[] = अणु
	अणु FSF_FC_SECURITY_AUTH,		"Authentication" पूर्ण,
	अणु FSF_FC_SECURITY_ENC_FCSP2 |
	  FSF_FC_SECURITY_ENC_ERAS,	"Encryption" पूर्ण,
पूर्ण;

/* maximum म_माप(zfcp_fsf_fc_security_mnemonics[...].name) + 1 */
#घोषणा ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH 15

/**
 * zfcp_fsf_scnprपूर्णांक_fc_security() - translate FC Endpoपूर्णांक Security flags पूर्णांकo
 *                                   mnemonics and place in a buffer
 * @buf        : the buffer to place the translated FC Endpoपूर्णांक Security flag(s)
 *               पूर्णांकo
 * @size       : the size of the buffer, including the trailing null space
 * @fc_security: one or more FC Endpoपूर्णांक Security flags, or zero
 * @fmt        : specअगरies whether a list or a single item is to be put पूर्णांकo the
 *               buffer
 *
 * The Fibre Channel (FC) Endpoपूर्णांक Security flags are translated पूर्णांकo mnemonics.
 * If the FC Endpoपूर्णांक Security flags are zero "none" is placed पूर्णांकo the buffer.
 *
 * With ZFCP_FSF_PRINT_FMT_LIST the mnemonics are placed as a list separated by
 * a comma followed by a space पूर्णांकo the buffer. If one or more FC Endpoपूर्णांक
 * Security flags cannot be translated पूर्णांकo a mnemonic, as they are undefined
 * in zfcp_fsf_fc_security_mnemonics, their bitwise ORed value in hexadecimal
 * representation is placed पूर्णांकo the buffer.
 *
 * With ZFCP_FSF_PRINT_FMT_SINGLEITEM only one single mnemonic is placed पूर्णांकo
 * the buffer. If the FC Endpoपूर्णांक Security flag cannot be translated, as it is
 * undefined in zfcp_fsf_fc_security_mnemonics, its value in hexadecimal
 * representation is placed पूर्णांकo the buffer. If more than one FC Endpoपूर्णांक
 * Security flag was specअगरied, their value in hexadecimal representation is
 * placed पूर्णांकo the buffer. The macro ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH
 * can be used to define a buffer that is large enough to hold one mnemonic.
 *
 * Return: The number of अक्षरacters written पूर्णांकo buf not including the trailing
 *         '\0'. If size is == 0 the function वापसs 0.
 */
sमाप_प्रकार zfcp_fsf_scnprपूर्णांक_fc_security(अक्षर *buf, माप_प्रकार size, u32 fc_security,
				      क्रमागत zfcp_fsf_prपूर्णांक_fmt fmt)
अणु
	स्थिर अक्षर *prefix = "";
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	अगर (fc_security == 0)
		वापस scnम_लिखो(buf, size, "none");
	अगर (fmt == ZFCP_FSF_PRINT_FMT_SINGLEITEM && hweight32(fc_security) != 1)
		वापस scnम_लिखो(buf, size, "0x%08x", fc_security);

	क्रम (i = 0; i < ARRAY_SIZE(zfcp_fsf_fc_security_mnemonics); i++) अणु
		अगर (!(fc_security & zfcp_fsf_fc_security_mnemonics[i].mask))
			जारी;

		len += scnम_लिखो(buf + len, size - len, "%s%s", prefix,
				 zfcp_fsf_fc_security_mnemonics[i].name);
		prefix = ", ";
		fc_security &= ~zfcp_fsf_fc_security_mnemonics[i].mask;
	पूर्ण

	अगर (fc_security != 0)
		len += scnम_लिखो(buf + len, size - len, "%s0x%08x",
				 prefix, fc_security);

	वापस len;
पूर्ण

अटल व्योम zfcp_fsf_dbf_adapter_fc_security(काष्ठा zfcp_adapter *adapter,
					     काष्ठा zfcp_fsf_req *req)
अणु
	अगर (adapter->fc_security_algorithms ==
	    adapter->fc_security_algorithms_old) अणु
		/* no change, no trace */
		वापस;
	पूर्ण

	zfcp_dbf_hba_fsf_fces("fsfcesa", req, ZFCP_DBF_INVALID_WWPN,
			      adapter->fc_security_algorithms_old,
			      adapter->fc_security_algorithms);

	adapter->fc_security_algorithms_old = adapter->fc_security_algorithms;
पूर्ण

अटल व्योम zfcp_fsf_exchange_port_evaluate(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा fsf_qtcb_bottom_port *bottom = &req->qtcb->bottom.port;

	अगर (req->data)
		स_नकल(req->data, bottom, माप(*bottom));

	अगर (adapter->adapter_features & FSF_FEATURE_FC_SECURITY)
		adapter->fc_security_algorithms =
			bottom->fc_security_algorithms;
	अन्यथा
		adapter->fc_security_algorithms = 0;
	zfcp_fsf_dbf_adapter_fc_security(adapter, req);
पूर्ण

अटल व्योम zfcp_fsf_exchange_port_data_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_diag_header *स्थिर diag_hdr =
		&req->adapter->diagnostics->port_data.header;
	काष्ठा fsf_qtcb *qtcb = req->qtcb;
	काष्ठा fsf_qtcb_bottom_port *bottom = &qtcb->bottom.port;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	चयन (qtcb->header.fsf_status) अणु
	हाल FSF_GOOD:
		/*
		 * usually we रुको with an update till the cache is too old,
		 * but because we have the data available, update it anyway
		 */
		zfcp_diag_update_xdata(diag_hdr, bottom, false);

		zfcp_scsi_shost_update_port_data(req->adapter, bottom);
		zfcp_fsf_exchange_port_evaluate(req);
		अवरोध;
	हाल FSF_EXCHANGE_CONFIG_DATA_INCOMPLETE:
		zfcp_diag_update_xdata(diag_hdr, bottom, true);
		req->status |= ZFCP_STATUS_FSFREQ_XDATAINCOMPLETE;

		zfcp_fsf_link_करोwn_info_eval(req,
			&qtcb->header.fsf_status_qual.link_करोwn_info);

		zfcp_scsi_shost_update_port_data(req->adapter, bottom);
		zfcp_fsf_exchange_port_evaluate(req);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा zfcp_fsf_req *zfcp_fsf_alloc(mempool_t *pool)
अणु
	काष्ठा zfcp_fsf_req *req;

	अगर (likely(pool))
		req = mempool_alloc(pool, GFP_ATOMIC);
	अन्यथा
		req = kदो_स्मृति(माप(*req), GFP_ATOMIC);

	अगर (unlikely(!req))
		वापस शून्य;

	स_रखो(req, 0, माप(*req));
	req->pool = pool;
	वापस req;
पूर्ण

अटल काष्ठा fsf_qtcb *zfcp_fsf_qtcb_alloc(mempool_t *pool)
अणु
	काष्ठा fsf_qtcb *qtcb;

	अगर (likely(pool))
		qtcb = mempool_alloc(pool, GFP_ATOMIC);
	अन्यथा
		qtcb = kmem_cache_alloc(zfcp_fsf_qtcb_cache, GFP_ATOMIC);

	अगर (unlikely(!qtcb))
		वापस शून्य;

	स_रखो(qtcb, 0, माप(*qtcb));
	वापस qtcb;
पूर्ण

अटल काष्ठा zfcp_fsf_req *zfcp_fsf_req_create(काष्ठा zfcp_qdio *qdio,
						u32 fsf_cmd, u8 sbtype,
						mempool_t *pool)
अणु
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	काष्ठा zfcp_fsf_req *req = zfcp_fsf_alloc(pool);

	अगर (unlikely(!req))
		वापस ERR_PTR(-ENOMEM);

	अगर (adapter->req_no == 0)
		adapter->req_no++;

	समयr_setup(&req->समयr, शून्य, 0);
	init_completion(&req->completion);

	req->adapter = adapter;
	req->req_id = adapter->req_no;

	अगर (likely(fsf_cmd != FSF_QTCB_UNSOLICITED_STATUS)) अणु
		अगर (likely(pool))
			req->qtcb = zfcp_fsf_qtcb_alloc(
				adapter->pool.qtcb_pool);
		अन्यथा
			req->qtcb = zfcp_fsf_qtcb_alloc(शून्य);

		अगर (unlikely(!req->qtcb)) अणु
			zfcp_fsf_req_मुक्त(req);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		req->qtcb->prefix.req_seq_no = adapter->fsf_req_seq_no;
		req->qtcb->prefix.req_id = req->req_id;
		req->qtcb->prefix.ulp_info = 26;
		req->qtcb->prefix.qtcb_type = fsf_qtcb_type[fsf_cmd];
		req->qtcb->prefix.qtcb_version = FSF_QTCB_CURRENT_VERSION;
		req->qtcb->header.req_handle = req->req_id;
		req->qtcb->header.fsf_command = fsf_cmd;
	पूर्ण

	zfcp_qdio_req_init(adapter->qdio, &req->qdio_req, req->req_id, sbtype,
			   req->qtcb, माप(काष्ठा fsf_qtcb));

	वापस req;
पूर्ण

अटल पूर्णांक zfcp_fsf_req_send(काष्ठा zfcp_fsf_req *req)
अणु
	स्थिर bool is_srb = zfcp_fsf_req_is_status_पढ़ो_buffer(req);
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_qdio *qdio = adapter->qdio;
	पूर्णांक req_id = req->req_id;

	zfcp_reqlist_add(adapter->req_list, req);

	req->qdio_req.qdio_outb_usage = atomic_पढ़ो(&qdio->req_q_मुक्त);
	req->issued = get_tod_घड़ी();
	अगर (zfcp_qdio_send(qdio, &req->qdio_req)) अणु
		del_समयr_sync(&req->समयr);
		/* lookup request again, list might have changed */
		zfcp_reqlist_find_rm(adapter->req_list, req_id);
		zfcp_erp_adapter_reखोलो(adapter, 0, "fsrs__1");
		वापस -EIO;
	पूर्ण

	/*
	 * NOTE: DO NOT TOUCH ASYNC req PAST THIS POINT.
	 *	 ONLY TOUCH SYNC req AGAIN ON req->completion.
	 *
	 * The request might complete and be मुक्तd concurrently at any poपूर्णांक
	 * now. This is not रक्षित by the QDIO-lock (req_q_lock). So any
	 * uncontrolled access after this might result in an use-after-मुक्त bug.
	 * Only अगर the request करोesn't have ZFCP_STATUS_FSFREQ_CLEANUP set, and
	 * when it is completed via req->completion, is it safe to use req
	 * again.
	 */

	/* Don't increase क्रम unsolicited status */
	अगर (!is_srb)
		adapter->fsf_req_seq_no++;
	adapter->req_no++;

	वापस 0;
पूर्ण

/**
 * zfcp_fsf_status_पढ़ो - send status पढ़ो request
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * Returns: 0 on success, ERROR otherwise
 */
पूर्णांक zfcp_fsf_status_पढ़ो(काष्ठा zfcp_qdio *qdio)
अणु
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	काष्ठा zfcp_fsf_req *req;
	काष्ठा fsf_status_पढ़ो_buffer *sr_buf;
	काष्ठा page *page;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_UNSOLICITED_STATUS,
				  SBAL_SFLAGS0_TYPE_STATUS,
				  adapter->pool.status_पढ़ो_req);
	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	page = mempool_alloc(adapter->pool.sr_data, GFP_ATOMIC);
	अगर (!page) अणु
		retval = -ENOMEM;
		जाओ failed_buf;
	पूर्ण
	sr_buf = page_address(page);
	स_रखो(sr_buf, 0, माप(*sr_buf));
	req->data = sr_buf;

	zfcp_qdio_fill_next(qdio, &req->qdio_req, sr_buf, माप(*sr_buf));
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	retval = zfcp_fsf_req_send(req);
	अगर (retval)
		जाओ failed_req_send;
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */

	जाओ out;

failed_req_send:
	req->data = शून्य;
	mempool_मुक्त(virt_to_page(sr_buf), adapter->pool.sr_data);
failed_buf:
	zfcp_dbf_hba_fsf_uss("fssr__1", req);
	zfcp_fsf_req_मुक्त(req);
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_पात_fcp_command_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा scsi_device *sdev = req->data;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;
	जोड़ fsf_status_qual *fsq = &req->qtcb->header.fsf_status_qual;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	zfcp_sdev = sdev_to_zfcp(sdev);

	चयन (req->qtcb->header.fsf_status) अणु
	हाल FSF_PORT_HANDLE_NOT_VALID:
		अगर (fsq->word[0] == fsq->word[1]) अणु
			zfcp_erp_adapter_reखोलो(zfcp_sdev->port->adapter, 0,
						"fsafch1");
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		पूर्ण
		अवरोध;
	हाल FSF_LUN_HANDLE_NOT_VALID:
		अगर (fsq->word[0] == fsq->word[1]) अणु
			zfcp_erp_port_reखोलो(zfcp_sdev->port, 0, "fsafch2");
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		पूर्ण
		अवरोध;
	हाल FSF_FCP_COMMAND_DOES_NOT_EXIST:
		req->status |= ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED;
		अवरोध;
	हाल FSF_PORT_BOXED:
		zfcp_erp_set_port_status(zfcp_sdev->port,
					 ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_port_reखोलो(zfcp_sdev->port,
				     ZFCP_STATUS_COMMON_ERP_FAILED, "fsafch3");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_LUN_BOXED:
		zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_lun_reखोलो(sdev, ZFCP_STATUS_COMMON_ERP_FAILED,
				    "fsafch4");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
                अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (fsq->word[0]) अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(zfcp_sdev->port);
			fallthrough;
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FSF_GOOD:
		req->status |= ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_fsf_पात_fcp_cmnd - पात running SCSI command
 * @scmnd: The SCSI command to पात
 * Returns: poपूर्णांकer to काष्ठा zfcp_fsf_req
 */

काष्ठा zfcp_fsf_req *zfcp_fsf_पात_fcp_cmnd(काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा zfcp_fsf_req *req = शून्य;
	काष्ठा scsi_device *sdev = scmnd->device;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_qdio *qdio = zfcp_sdev->port->adapter->qdio;
	अचिन्हित दीर्घ old_req_id = (अचिन्हित दीर्घ) scmnd->host_scribble;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;
	req = zfcp_fsf_req_create(qdio, FSF_QTCB_ABORT_FCP_CMND,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.scsi_पात);
	अगर (IS_ERR(req)) अणु
		req = शून्य;
		जाओ out;
	पूर्ण

	अगर (unlikely(!(atomic_पढ़ो(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		जाओ out_error_मुक्त;

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->data = sdev;
	req->handler = zfcp_fsf_पात_fcp_command_handler;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->qtcb->header.port_handle = zfcp_sdev->port->handle;
	req->qtcb->bottom.support.req_handle = (u64) old_req_id;

	zfcp_fsf_start_समयr(req, ZFCP_FSF_SCSI_ER_TIMEOUT);
	अगर (!zfcp_fsf_req_send(req)) अणु
		/* NOTE: DO NOT TOUCH req, UNTIL IT COMPLETES! */
		जाओ out;
	पूर्ण

out_error_मुक्त:
	zfcp_fsf_req_मुक्त(req);
	req = शून्य;
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस req;
पूर्ण

अटल व्योम zfcp_fsf_send_ct_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_fsf_ct_els *ct = req->data;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;

	ct->status = -EINVAL;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		जाओ skip_fsख_स्थितिus;

	चयन (header->fsf_status) अणु
        हाल FSF_GOOD:
		ct->status = 0;
		zfcp_dbf_san_res("fsscth2", req);
		अवरोध;
        हाल FSF_SERVICE_CLASS_NOT_SUPPORTED:
		zfcp_fsf_class_not_supp(req);
		अवरोध;
        हाल FSF_ADAPTER_STATUS_AVAILABLE:
                चयन (header->fsf_status_qual.word[0])अणु
                हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
                हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
                पूर्ण
                अवरोध;
        हाल FSF_PORT_BOXED:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(adapter, 0, "fsscth1");
		fallthrough;
	हाल FSF_GENERIC_COMMAND_REJECTED:
	हाल FSF_PAYLOAD_SIZE_MISMATCH:
	हाल FSF_REQUEST_SIZE_TOO_LARGE:
	हाल FSF_RESPONSE_SIZE_TOO_LARGE:
	हाल FSF_SBAL_MISMATCH:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	पूर्ण

skip_fsख_स्थितिus:
	अगर (ct->handler)
		ct->handler(ct->handler_data);
पूर्ण

अटल व्योम zfcp_fsf_setup_ct_els_unchained(काष्ठा zfcp_qdio *qdio,
					    काष्ठा zfcp_qdio_req *q_req,
					    काष्ठा scatterlist *sg_req,
					    काष्ठा scatterlist *sg_resp)
अणु
	zfcp_qdio_fill_next(qdio, q_req, sg_virt(sg_req), sg_req->length);
	zfcp_qdio_fill_next(qdio, q_req, sg_virt(sg_resp), sg_resp->length);
	zfcp_qdio_set_sbale_last(qdio, q_req);
पूर्ण

अटल पूर्णांक zfcp_fsf_setup_ct_els_sbals(काष्ठा zfcp_fsf_req *req,
				       काष्ठा scatterlist *sg_req,
				       काष्ठा scatterlist *sg_resp)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_qdio *qdio = adapter->qdio;
	काष्ठा fsf_qtcb *qtcb = req->qtcb;
	u32 feat = adapter->adapter_features;

	अगर (zfcp_adapter_multi_buffer_active(adapter)) अणु
		अगर (zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req, sg_req))
			वापस -EIO;
		qtcb->bottom.support.req_buf_length =
			zfcp_qdio_real_bytes(sg_req);
		अगर (zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req, sg_resp))
			वापस -EIO;
		qtcb->bottom.support.resp_buf_length =
			zfcp_qdio_real_bytes(sg_resp);

		zfcp_qdio_set_data_भाग(qdio, &req->qdio_req, sg_nents(sg_req));
		zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);
		zfcp_qdio_set_scount(qdio, &req->qdio_req);
		वापस 0;
	पूर्ण

	/* use single, unchained SBAL अगर it can hold the request */
	अगर (zfcp_qdio_sg_one_sbale(sg_req) && zfcp_qdio_sg_one_sbale(sg_resp)) अणु
		zfcp_fsf_setup_ct_els_unchained(qdio, &req->qdio_req,
						sg_req, sg_resp);
		वापस 0;
	पूर्ण

	अगर (!(feat & FSF_FEATURE_ELS_CT_CHAINED_SBALS))
		वापस -EOPNOTSUPP;

	अगर (zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req, sg_req))
		वापस -EIO;

	qtcb->bottom.support.req_buf_length = zfcp_qdio_real_bytes(sg_req);

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);
	zfcp_qdio_skip_to_last_sbale(qdio, &req->qdio_req);

	अगर (zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req, sg_resp))
		वापस -EIO;

	qtcb->bottom.support.resp_buf_length = zfcp_qdio_real_bytes(sg_resp);

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	वापस 0;
पूर्ण

अटल पूर्णांक zfcp_fsf_setup_ct_els(काष्ठा zfcp_fsf_req *req,
				 काष्ठा scatterlist *sg_req,
				 काष्ठा scatterlist *sg_resp,
				 अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = zfcp_fsf_setup_ct_els_sbals(req, sg_req, sg_resp);
	अगर (ret)
		वापस ret;

	/* common settings क्रम ct/gs and els requests */
	अगर (समयout > 255)
		समयout = 255; /* max value accepted by hardware */
	req->qtcb->bottom.support.service_class = FSF_CLASS_3;
	req->qtcb->bottom.support.समयout = समयout;
	zfcp_fsf_start_समयr(req, (समयout + 10) * HZ);

	वापस 0;
पूर्ण

/**
 * zfcp_fsf_send_ct - initiate a Generic Service request (FC-GS)
 * @wka_port: poपूर्णांकer to zfcp WKA port to send CT/GS to
 * @ct: poपूर्णांकer to काष्ठा zfcp_send_ct with data क्रम request
 * @pool: अगर non-null this mempool is used to allocate काष्ठा zfcp_fsf_req
 * @समयout: समयout that hardware should use, and a later software समयout
 */
पूर्णांक zfcp_fsf_send_ct(काष्ठा zfcp_fc_wka_port *wka_port,
		     काष्ठा zfcp_fsf_ct_els *ct, mempool_t *pool,
		     अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा zfcp_qdio *qdio = wka_port->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक ret = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_SEND_GENERIC,
				  SBAL_SFLAGS0_TYPE_WRITE_READ, pool);

	अगर (IS_ERR(req)) अणु
		ret = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	ret = zfcp_fsf_setup_ct_els(req, ct->req, ct->resp, समयout);
	अगर (ret)
		जाओ failed_send;

	req->handler = zfcp_fsf_send_ct_handler;
	req->qtcb->header.port_handle = wka_port->handle;
	ct->d_id = wka_port->d_id;
	req->data = ct;

	zfcp_dbf_san_req("fssct_1", req, wka_port->d_id);

	ret = zfcp_fsf_req_send(req);
	अगर (ret)
		जाओ failed_send;
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */

	जाओ out;

failed_send:
	zfcp_fsf_req_मुक्त(req);
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस ret;
पूर्ण

अटल व्योम zfcp_fsf_send_els_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_fsf_ct_els *send_els = req->data;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;

	send_els->status = -EINVAL;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		जाओ skip_fsख_स्थितिus;

	चयन (header->fsf_status) अणु
	हाल FSF_GOOD:
		send_els->status = 0;
		zfcp_dbf_san_res("fsselh1", req);
		अवरोध;
	हाल FSF_SERVICE_CLASS_NOT_SUPPORTED:
		zfcp_fsf_class_not_supp(req);
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (header->fsf_status_qual.word[0])अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
		हाल FSF_SQ_RETRY_IF_POSSIBLE:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FSF_ELS_COMMAND_REJECTED:
	हाल FSF_PAYLOAD_SIZE_MISMATCH:
	हाल FSF_REQUEST_SIZE_TOO_LARGE:
	हाल FSF_RESPONSE_SIZE_TOO_LARGE:
		अवरोध;
	हाल FSF_SBAL_MISMATCH:
		/* should never occur, aव्योमed in zfcp_fsf_send_els */
		fallthrough;
	शेष:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	पूर्ण
skip_fsख_स्थितिus:
	अगर (send_els->handler)
		send_els->handler(send_els->handler_data);
पूर्ण

/**
 * zfcp_fsf_send_els - initiate an ELS command (FC-FS)
 * @adapter: poपूर्णांकer to zfcp adapter
 * @d_id: N_Port_ID to send ELS to
 * @els: poपूर्णांकer to काष्ठा zfcp_send_els with data क्रम the command
 * @समयout: समयout that hardware should use, and a later software समयout
 */
पूर्णांक zfcp_fsf_send_els(काष्ठा zfcp_adapter *adapter, u32 d_id,
		      काष्ठा zfcp_fsf_ct_els *els, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा zfcp_fsf_req *req;
	काष्ठा zfcp_qdio *qdio = adapter->qdio;
	पूर्णांक ret = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_SEND_ELS,
				  SBAL_SFLAGS0_TYPE_WRITE_READ, शून्य);

	अगर (IS_ERR(req)) अणु
		ret = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;

	अगर (!zfcp_adapter_multi_buffer_active(adapter))
		zfcp_qdio_sbal_limit(qdio, &req->qdio_req, 2);

	ret = zfcp_fsf_setup_ct_els(req, els->req, els->resp, समयout);

	अगर (ret)
		जाओ failed_send;

	hton24(req->qtcb->bottom.support.d_id, d_id);
	req->handler = zfcp_fsf_send_els_handler;
	els->d_id = d_id;
	req->data = els;

	zfcp_dbf_san_req("fssels1", req, d_id);

	ret = zfcp_fsf_req_send(req);
	अगर (ret)
		जाओ failed_send;
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */

	जाओ out;

failed_send:
	zfcp_fsf_req_मुक्त(req);
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस ret;
पूर्ण

पूर्णांक zfcp_fsf_exchange_config_data(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_fsf_req *req;
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_EXCHANGE_CONFIG_DATA,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->qtcb->bottom.config.feature_selection =
			FSF_FEATURE_NOTIFICATION_LOST |
			FSF_FEATURE_UPDATE_ALERT |
			FSF_FEATURE_REQUEST_SFP_DATA |
			FSF_FEATURE_FC_SECURITY;
	req->erp_action = erp_action;
	req->handler = zfcp_fsf_exchange_config_data_handler;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण


/**
 * zfcp_fsf_exchange_config_data_sync() - Request inक्रमmation about FCP channel.
 * @qdio: poपूर्णांकer to the QDIO-Queue to use क्रम sending the command.
 * @data: poपूर्णांकer to the QTCB-Bottom क्रम storing the result of the command,
 *	  might be %शून्य.
 *
 * Returns:
 * * 0		- Exchange Config Data was successful, @data is complete
 * * -EIO	- Exchange Config Data was not successful, @data is invalid
 * * -EAGAIN	- @data contains incomplete data
 * * -ENOMEM	- Some memory allocation failed aदीर्घ the way
 */
पूर्णांक zfcp_fsf_exchange_config_data_sync(काष्ठा zfcp_qdio *qdio,
				       काष्ठा fsf_qtcb_bottom_config *data)
अणु
	काष्ठा zfcp_fsf_req *req = शून्य;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out_unlock;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_EXCHANGE_CONFIG_DATA,
				  SBAL_SFLAGS0_TYPE_READ, शून्य);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out_unlock;
	पूर्ण

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);
	req->handler = zfcp_fsf_exchange_config_data_handler;

	req->qtcb->bottom.config.feature_selection =
			FSF_FEATURE_NOTIFICATION_LOST |
			FSF_FEATURE_UPDATE_ALERT |
			FSF_FEATURE_REQUEST_SFP_DATA |
			FSF_FEATURE_FC_SECURITY;

	अगर (data)
		req->data = data;

	zfcp_fsf_start_समयr(req, ZFCP_FSF_REQUEST_TIMEOUT);
	retval = zfcp_fsf_req_send(req);
	spin_unlock_irq(&qdio->req_q_lock);

	अगर (!retval) अणु
		/* NOTE: ONLY TOUCH SYNC req AGAIN ON req->completion. */
		रुको_क्रम_completion(&req->completion);

		अगर (req->status &
		    (ZFCP_STATUS_FSFREQ_ERROR | ZFCP_STATUS_FSFREQ_DISMISSED))
			retval = -EIO;
		अन्यथा अगर (req->status & ZFCP_STATUS_FSFREQ_XDATAINCOMPLETE)
			retval = -EAGAIN;
	पूर्ण

	zfcp_fsf_req_मुक्त(req);
	वापस retval;

out_unlock:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

/**
 * zfcp_fsf_exchange_port_data - request inक्रमmation about local port
 * @erp_action: ERP action क्रम the adapter क्रम which port data is requested
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_exchange_port_data(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	अगर (!(qdio->adapter->adapter_features & FSF_FEATURE_HBAAPI_MANAGEMENT))
		वापस -EOPNOTSUPP;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_EXCHANGE_PORT_DATA,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_exchange_port_data_handler;
	req->erp_action = erp_action;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

/**
 * zfcp_fsf_exchange_port_data_sync() - Request inक्रमmation about local port.
 * @qdio: poपूर्णांकer to the QDIO-Queue to use क्रम sending the command.
 * @data: poपूर्णांकer to the QTCB-Bottom क्रम storing the result of the command,
 *	  might be %शून्य.
 *
 * Returns:
 * * 0		- Exchange Port Data was successful, @data is complete
 * * -EIO	- Exchange Port Data was not successful, @data is invalid
 * * -EAGAIN	- @data contains incomplete data
 * * -ENOMEM	- Some memory allocation failed aदीर्घ the way
 * * -EOPNOTSUPP	- This operation is not supported
 */
पूर्णांक zfcp_fsf_exchange_port_data_sync(काष्ठा zfcp_qdio *qdio,
				     काष्ठा fsf_qtcb_bottom_port *data)
अणु
	काष्ठा zfcp_fsf_req *req = शून्य;
	पूर्णांक retval = -EIO;

	अगर (!(qdio->adapter->adapter_features & FSF_FEATURE_HBAAPI_MANAGEMENT))
		वापस -EOPNOTSUPP;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out_unlock;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_EXCHANGE_PORT_DATA,
				  SBAL_SFLAGS0_TYPE_READ, शून्य);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out_unlock;
	पूर्ण

	अगर (data)
		req->data = data;

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_exchange_port_data_handler;
	zfcp_fsf_start_समयr(req, ZFCP_FSF_REQUEST_TIMEOUT);
	retval = zfcp_fsf_req_send(req);
	spin_unlock_irq(&qdio->req_q_lock);

	अगर (!retval) अणु
		/* NOTE: ONLY TOUCH SYNC req AGAIN ON req->completion. */
		रुको_क्रम_completion(&req->completion);

		अगर (req->status &
		    (ZFCP_STATUS_FSFREQ_ERROR | ZFCP_STATUS_FSFREQ_DISMISSED))
			retval = -EIO;
		अन्यथा अगर (req->status & ZFCP_STATUS_FSFREQ_XDATAINCOMPLETE)
			retval = -EAGAIN;
	पूर्ण

	zfcp_fsf_req_मुक्त(req);
	वापस retval;

out_unlock:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_log_port_fc_security(काष्ठा zfcp_port *port,
					  काष्ठा zfcp_fsf_req *req)
अणु
	अक्षर mnemonic_old[ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH];
	अक्षर mnemonic_new[ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH];

	अगर (port->connection_info == port->connection_info_old) अणु
		/* no change, no log nor trace */
		वापस;
	पूर्ण

	zfcp_dbf_hba_fsf_fces("fsfcesp", req, port->wwpn,
			      port->connection_info_old,
			      port->connection_info);

	zfcp_fsf_scnprपूर्णांक_fc_security(mnemonic_old, माप(mnemonic_old),
				      port->connection_info_old,
				      ZFCP_FSF_PRINT_FMT_SINGLEITEM);
	zfcp_fsf_scnprपूर्णांक_fc_security(mnemonic_new, माप(mnemonic_new),
				      port->connection_info,
				      ZFCP_FSF_PRINT_FMT_SINGLEITEM);

	अगर (म_भेदन(mnemonic_old, mnemonic_new,
		    ZFCP_FSF_MAX_FC_SECURITY_MNEMONIC_LENGTH) == 0) अणु
		/* no change in string representation, no log */
		जाओ out;
	पूर्ण

	अगर (port->connection_info_old == 0) अणु
		/* activation */
		dev_info(&port->adapter->ccw_device->dev,
			 "FC Endpoint Security of connection to remote port 0x%16llx enabled: %s\n",
			 port->wwpn, mnemonic_new);
	पूर्ण अन्यथा अगर (port->connection_info == 0) अणु
		/* deactivation */
		dev_warn(&port->adapter->ccw_device->dev,
			 "FC Endpoint Security of connection to remote port 0x%16llx disabled: was %s\n",
			 port->wwpn, mnemonic_old);
	पूर्ण अन्यथा अणु
		/* change */
		dev_warn(&port->adapter->ccw_device->dev,
			 "FC Endpoint Security of connection to remote port 0x%16llx changed: from %s to %s\n",
			 port->wwpn, mnemonic_old, mnemonic_new);
	पूर्ण

out:
	port->connection_info_old = port->connection_info;
पूर्ण

अटल व्योम zfcp_fsf_log_security_error(स्थिर काष्ठा device *dev, u32 fsf_sqw0,
					u64 wwpn)
अणु
	चयन (fsf_sqw0) अणु

	/*
	 * Open Port command error codes
	 */

	हाल FSF_SQ_SECURITY_REQUIRED:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: FC security is required but not supported or configured on remote port 0x%016llx\n",
				     wwpn);
		अवरोध;
	हाल FSF_SQ_SECURITY_TIMEOUT:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: a timeout prevented opening remote port 0x%016llx\n",
				     wwpn);
		अवरोध;
	हाल FSF_SQ_SECURITY_KM_UNAVAILABLE:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: opening remote port 0x%016llx failed because local and external key manager cannot communicate\n",
				     wwpn);
		अवरोध;
	हाल FSF_SQ_SECURITY_RKM_UNAVAILABLE:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: opening remote port 0x%016llx failed because it cannot communicate with the external key manager\n",
				     wwpn);
		अवरोध;
	हाल FSF_SQ_SECURITY_AUTH_FAILURE:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: the device could not verify the identity of remote port 0x%016llx\n",
				     wwpn);
		अवरोध;

	/*
	 * Send FCP command error codes
	 */

	हाल FSF_SQ_SECURITY_ENC_FAILURE:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: FC connection to remote port 0x%016llx closed because encryption broke down\n",
				     wwpn);
		अवरोध;

	/*
	 * Unknown error codes
	 */

	शेष:
		dev_warn_ratelimited(dev,
				     "FC Endpoint Security error: the device issued an unknown error code 0x%08x related to the FC connection to remote port 0x%016llx\n",
				     fsf_sqw0, wwpn);
	पूर्ण
पूर्ण

अटल व्योम zfcp_fsf_खोलो_port_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा zfcp_port *port = req->data;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;
	काष्ठा fsf_qtcb_bottom_support *bottom = &req->qtcb->bottom.support;
	काष्ठा fc_els_flogi *plogi;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		जाओ out;

	चयन (header->fsf_status) अणु
	हाल FSF_PORT_ALREADY_OPEN:
		अवरोध;
	हाल FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED:
		dev_warn(&adapter->ccw_device->dev,
			 "Not enough FCP adapter resources to open "
			 "remote port 0x%016Lx\n",
			 (अचिन्हित दीर्घ दीर्घ)port->wwpn);
		zfcp_erp_set_port_status(port,
					 ZFCP_STATUS_COMMON_ERP_FAILED);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_SECURITY_ERROR:
		zfcp_fsf_log_security_error(&req->adapter->ccw_device->dev,
					    header->fsf_status_qual.word[0],
					    port->wwpn);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (header->fsf_status_qual.word[0]) अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			/* no zfcp_fc_test_link() with failed खोलो port */
			fallthrough;
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
		हाल FSF_SQ_NO_RETRY_POSSIBLE:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FSF_GOOD:
		port->handle = header->port_handle;
		अगर (adapter->adapter_features & FSF_FEATURE_FC_SECURITY)
			port->connection_info = bottom->connection_info;
		अन्यथा
			port->connection_info = 0;
		zfcp_fsf_log_port_fc_security(port, req);
		atomic_or(ZFCP_STATUS_COMMON_OPEN |
				ZFCP_STATUS_PORT_PHYS_OPEN, &port->status);
		atomic_andnot(ZFCP_STATUS_COMMON_ACCESS_BOXED,
		                  &port->status);
		/* check whether D_ID has changed during खोलो */
		/*
		 * FIXME: This check is not airtight, as the FCP channel करोes
		 * not monitor closures of target port connections caused on
		 * the remote side. Thus, they might miss out on invalidating
		 * locally cached WWPNs (and other N_Port parameters) of gone
		 * target ports. So, our heroic attempt to make things safe
		 * could be undermined by 'open port' response data tagged with
		 * obsolete WWPNs. Another reason to monitor potential
		 * connection closures ourself at least (by पूर्णांकerpreting
		 * incoming ELS' and unsolicited status). It just crosses my
		 * mind that one should be able to cross-check by means of
		 * another GID_PN straight after a port has been खोलोed.
		 * Alternately, an ADISC/PDISC ELS should suffice, as well.
		 */
		plogi = (काष्ठा fc_els_flogi *) bottom->els;
		अगर (bottom->els1_length >= FSF_PLOGI_MIN_LEN)
			zfcp_fc_plogi_evaluate(port, plogi);
		अवरोध;
	हाल FSF_UNKNOWN_OP_SUBTYPE:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	पूर्ण

out:
	put_device(&port->dev);
पूर्ण

/**
 * zfcp_fsf_खोलो_port - create and send खोलो port request
 * @erp_action: poपूर्णांकer to काष्ठा zfcp_erp_action
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_खोलो_port(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	काष्ठा zfcp_port *port = erp_action->port;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_OPEN_PORT_WITH_DID,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_खोलो_port_handler;
	hton24(req->qtcb->bottom.support.d_id, port->d_id);
	req->data = port;
	req->erp_action = erp_action;
	erp_action->fsf_req_id = req->req_id;
	get_device(&port->dev);

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
		put_device(&port->dev);
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_बंद_port_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_port *port = req->data;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	चयन (req->qtcb->header.fsf_status) अणु
	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(port->adapter, 0, "fscph_1");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		अवरोध;
	हाल FSF_GOOD:
		zfcp_erp_clear_port_status(port, ZFCP_STATUS_COMMON_OPEN);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_fsf_बंद_port - create and send बंद port request
 * @erp_action: poपूर्णांकer to काष्ठा zfcp_erp_action
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_बंद_port(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_CLOSE_PORT,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_बंद_port_handler;
	req->data = erp_action->port;
	req->erp_action = erp_action;
	req->qtcb->header.port_handle = erp_action->port->handle;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_खोलो_wka_port_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_fc_wka_port *wka_port = req->data;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR) अणु
		wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
		जाओ out;
	पूर्ण

	चयन (header->fsf_status) अणु
	हाल FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "Opening WKA port 0x%x failed\n", wka_port->d_id);
		fallthrough;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
		अवरोध;
	हाल FSF_GOOD:
		wka_port->handle = header->port_handle;
		fallthrough;
	हाल FSF_PORT_ALREADY_OPEN:
		wka_port->status = ZFCP_FC_WKA_PORT_ONLINE;
	पूर्ण
out:
	wake_up(&wka_port->completion_wq);
पूर्ण

/**
 * zfcp_fsf_खोलो_wka_port - create and send खोलो wka-port request
 * @wka_port: poपूर्णांकer to काष्ठा zfcp_fc_wka_port
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_खोलो_wka_port(काष्ठा zfcp_fc_wka_port *wka_port)
अणु
	काष्ठा zfcp_qdio *qdio = wka_port->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	अचिन्हित दीर्घ req_id = 0;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_OPEN_PORT_WITH_DID,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_खोलो_wka_port_handler;
	hton24(req->qtcb->bottom.support.d_id, wka_port->d_id);
	req->data = wka_port;

	req_id = req->req_id;

	zfcp_fsf_start_समयr(req, ZFCP_FSF_REQUEST_TIMEOUT);
	retval = zfcp_fsf_req_send(req);
	अगर (retval)
		zfcp_fsf_req_मुक्त(req);
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	अगर (!retval)
		zfcp_dbf_rec_run_wka("fsowp_1", wka_port, req_id);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_बंद_wka_port_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_fc_wka_port *wka_port = req->data;

	अगर (req->qtcb->header.fsf_status == FSF_PORT_HANDLE_NOT_VALID) अणु
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		zfcp_erp_adapter_reखोलो(wka_port->adapter, 0, "fscwph1");
	पूर्ण

	wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
	wake_up(&wka_port->completion_wq);
पूर्ण

/**
 * zfcp_fsf_बंद_wka_port - create and send बंद wka port request
 * @wka_port: WKA port to खोलो
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_बंद_wka_port(काष्ठा zfcp_fc_wka_port *wka_port)
अणु
	काष्ठा zfcp_qdio *qdio = wka_port->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	अचिन्हित दीर्घ req_id = 0;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_CLOSE_PORT,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->handler = zfcp_fsf_बंद_wka_port_handler;
	req->data = wka_port;
	req->qtcb->header.port_handle = wka_port->handle;

	req_id = req->req_id;

	zfcp_fsf_start_समयr(req, ZFCP_FSF_REQUEST_TIMEOUT);
	retval = zfcp_fsf_req_send(req);
	अगर (retval)
		zfcp_fsf_req_मुक्त(req);
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	अगर (!retval)
		zfcp_dbf_rec_run_wka("fscwp_1", wka_port, req_id);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_बंद_physical_port_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_port *port = req->data;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;
	काष्ठा scsi_device *sdev;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	चयन (header->fsf_status) अणु
	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(port->adapter, 0, "fscpph1");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_PORT_BOXED:
		/* can't use generic zfcp_erp_modअगरy_port_status because
		 * ZFCP_STATUS_COMMON_OPEN must not be reset क्रम the port */
		atomic_andnot(ZFCP_STATUS_PORT_PHYS_OPEN, &port->status);
		shost_क्रम_each_device(sdev, port->adapter->scsi_host)
			अगर (sdev_to_zfcp(sdev)->port == port)
				atomic_andnot(ZFCP_STATUS_COMMON_OPEN,
						  &sdev_to_zfcp(sdev)->status);
		zfcp_erp_set_port_status(port, ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_port_reखोलो(port, ZFCP_STATUS_COMMON_ERP_FAILED,
				     "fscpph2");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (header->fsf_status_qual.word[0]) अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FSF_GOOD:
		/* can't use generic zfcp_erp_modअगरy_port_status because
		 * ZFCP_STATUS_COMMON_OPEN must not be reset क्रम the port
		 */
		atomic_andnot(ZFCP_STATUS_PORT_PHYS_OPEN, &port->status);
		shost_क्रम_each_device(sdev, port->adapter->scsi_host)
			अगर (sdev_to_zfcp(sdev)->port == port)
				atomic_andnot(ZFCP_STATUS_COMMON_OPEN,
						  &sdev_to_zfcp(sdev)->status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_fsf_बंद_physical_port - बंद physical port
 * @erp_action: poपूर्णांकer to काष्ठा zfcp_erp_action
 * Returns: 0 on success
 */
पूर्णांक zfcp_fsf_बंद_physical_port(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_CLOSE_PHYSICAL_PORT,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->data = erp_action->port;
	req->qtcb->header.port_handle = erp_action->port->handle;
	req->erp_action = erp_action;
	req->handler = zfcp_fsf_बंद_physical_port_handler;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_खोलो_lun_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा zfcp_adapter *adapter = req->adapter;
	काष्ठा scsi_device *sdev = req->data;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;
	जोड़ fsf_status_qual *qual = &header->fsf_status_qual;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(ZFCP_STATUS_COMMON_ACCESS_DENIED |
			  ZFCP_STATUS_COMMON_ACCESS_BOXED,
			  &zfcp_sdev->status);

	चयन (header->fsf_status) अणु

	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(adapter, 0, "fsouh_1");
		fallthrough;
	हाल FSF_LUN_ALREADY_OPEN:
		अवरोध;
	हाल FSF_PORT_BOXED:
		zfcp_erp_set_port_status(zfcp_sdev->port,
					 ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_port_reखोलो(zfcp_sdev->port,
				     ZFCP_STATUS_COMMON_ERP_FAILED, "fsouh_2");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_LUN_SHARING_VIOLATION:
		अगर (qual->word[0])
			dev_warn(&zfcp_sdev->port->adapter->ccw_device->dev,
				 "LUN 0x%016Lx on port 0x%016Lx is already in "
				 "use by CSS%d, MIF Image ID %x\n",
				 zfcp_scsi_dev_lun(sdev),
				 (अचिन्हित दीर्घ दीर्घ)zfcp_sdev->port->wwpn,
				 qual->fsf_queue_designator.cssid,
				 qual->fsf_queue_designator.hla);
		zfcp_erp_set_lun_status(sdev,
					ZFCP_STATUS_COMMON_ERP_FAILED |
					ZFCP_STATUS_COMMON_ACCESS_DENIED);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_MAXIMUM_NUMBER_OF_LUNS_EXCEEDED:
		dev_warn(&adapter->ccw_device->dev,
			 "No handle is available for LUN "
			 "0x%016Lx on port 0x%016Lx\n",
			 (अचिन्हित दीर्घ दीर्घ)zfcp_scsi_dev_lun(sdev),
			 (अचिन्हित दीर्घ दीर्घ)zfcp_sdev->port->wwpn);
		zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_ERP_FAILED);
		fallthrough;
	हाल FSF_INVALID_COMMAND_OPTION:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (header->fsf_status_qual.word[0]) अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(zfcp_sdev->port);
			fallthrough;
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल FSF_GOOD:
		zfcp_sdev->lun_handle = header->lun_handle;
		atomic_or(ZFCP_STATUS_COMMON_OPEN, &zfcp_sdev->status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_fsf_खोलो_lun - खोलो LUN
 * @erp_action: poपूर्णांकer to काष्ठा zfcp_erp_action
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_खोलो_lun(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_adapter *adapter = erp_action->adapter;
	काष्ठा zfcp_qdio *qdio = adapter->qdio;
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_OPEN_LUN,
				  SBAL_SFLAGS0_TYPE_READ,
				  adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->qtcb->header.port_handle = erp_action->port->handle;
	req->qtcb->bottom.support.fcp_lun = zfcp_scsi_dev_lun(erp_action->sdev);
	req->handler = zfcp_fsf_खोलो_lun_handler;
	req->data = erp_action->sdev;
	req->erp_action = erp_action;
	erp_action->fsf_req_id = req->req_id;

	अगर (!(adapter->connection_features & FSF_FEATURE_NPIV_MODE))
		req->qtcb->bottom.support.option = FSF_OPEN_LUN_SUPPRESS_BOXING;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_बंद_lun_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा scsi_device *sdev = req->data;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;

	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		वापस;

	zfcp_sdev = sdev_to_zfcp(sdev);

	चयन (req->qtcb->header.fsf_status) अणु
	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(zfcp_sdev->port->adapter, 0, "fscuh_1");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_LUN_HANDLE_NOT_VALID:
		zfcp_erp_port_reखोलो(zfcp_sdev->port, 0, "fscuh_2");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_PORT_BOXED:
		zfcp_erp_set_port_status(zfcp_sdev->port,
					 ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_port_reखोलो(zfcp_sdev->port,
				     ZFCP_STATUS_COMMON_ERP_FAILED, "fscuh_3");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		चयन (req->qtcb->header.fsf_status_qual.word[0]) अणु
		हाल FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(zfcp_sdev->port);
			fallthrough;
		हाल FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FSF_GOOD:
		atomic_andnot(ZFCP_STATUS_COMMON_OPEN, &zfcp_sdev->status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * zfcp_fsf_बंद_LUN - बंद LUN
 * @erp_action: poपूर्णांकer to erp_action triggering the "close LUN"
 * Returns: 0 on success, error otherwise
 */
पूर्णांक zfcp_fsf_बंद_lun(काष्ठा zfcp_erp_action *erp_action)
अणु
	काष्ठा zfcp_qdio *qdio = erp_action->adapter->qdio;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(erp_action->sdev);
	काष्ठा zfcp_fsf_req *req;
	पूर्णांक retval = -EIO;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_CLOSE_LUN,
				  SBAL_SFLAGS0_TYPE_READ,
				  qdio->adapter->pool.erp_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	req->qtcb->header.port_handle = erp_action->port->handle;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->handler = zfcp_fsf_बंद_lun_handler;
	req->data = erp_action->sdev;
	req->erp_action = erp_action;
	erp_action->fsf_req_id = req->req_id;

	zfcp_fsf_start_erp_समयr(req);
	retval = zfcp_fsf_req_send(req);
	अगर (retval) अणु
		zfcp_fsf_req_मुक्त(req);
		erp_action->fsf_req_id = 0;
	पूर्ण
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_update_lat(काष्ठा zfcp_latency_record *lat_rec, u32 lat)
अणु
	lat_rec->sum += lat;
	lat_rec->min = min(lat_rec->min, lat);
	lat_rec->max = max(lat_rec->max, lat);
पूर्ण

अटल व्योम zfcp_fsf_req_trace(काष्ठा zfcp_fsf_req *req, काष्ठा scsi_cmnd *scsi)
अणु
	काष्ठा fsf_qual_latency_info *lat_in;
	काष्ठा zfcp_latency_cont *lat = शून्य;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;
	काष्ठा zfcp_blk_drv_data blktrc;
	पूर्णांक ticks = req->adapter->समयr_ticks;

	lat_in = &req->qtcb->prefix.prot_status_qual.latency_info;

	blktrc.flags = 0;
	blktrc.magic = ZFCP_BLK_DRV_DATA_MAGIC;
	अगर (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		blktrc.flags |= ZFCP_BLK_REQ_ERROR;
	blktrc.inb_usage = 0;
	blktrc.outb_usage = req->qdio_req.qdio_outb_usage;

	अगर (req->adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA &&
	    !(req->status & ZFCP_STATUS_FSFREQ_ERROR)) अणु
		zfcp_sdev = sdev_to_zfcp(scsi->device);
		blktrc.flags |= ZFCP_BLK_LAT_VALID;
		blktrc.channel_lat = lat_in->channel_lat * ticks;
		blktrc.fabric_lat = lat_in->fabric_lat * ticks;

		चयन (req->qtcb->bottom.io.data_direction) अणु
		हाल FSF_DATAसूची_DIF_READ_STRIP:
		हाल FSF_DATAसूची_DIF_READ_CONVERT:
		हाल FSF_DATAसूची_READ:
			lat = &zfcp_sdev->latencies.पढ़ो;
			अवरोध;
		हाल FSF_DATAसूची_DIF_WRITE_INSERT:
		हाल FSF_DATAसूची_DIF_WRITE_CONVERT:
		हाल FSF_DATAसूची_WRITE:
			lat = &zfcp_sdev->latencies.ग_लिखो;
			अवरोध;
		हाल FSF_DATAसूची_CMND:
			lat = &zfcp_sdev->latencies.cmd;
			अवरोध;
		पूर्ण

		अगर (lat) अणु
			spin_lock(&zfcp_sdev->latencies.lock);
			zfcp_fsf_update_lat(&lat->channel, lat_in->channel_lat);
			zfcp_fsf_update_lat(&lat->fabric, lat_in->fabric_lat);
			lat->counter++;
			spin_unlock(&zfcp_sdev->latencies.lock);
		पूर्ण
	पूर्ण

	blk_add_driver_data(scsi->request, &blktrc, माप(blktrc));
पूर्ण

/**
 * zfcp_fsf_fcp_handler_common() - FCP response handler common to I/O and TMF.
 * @req: Poपूर्णांकer to FSF request.
 * @sdev: Poपूर्णांकer to SCSI device as request context.
 */
अटल व्योम zfcp_fsf_fcp_handler_common(काष्ठा zfcp_fsf_req *req,
					काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev;
	काष्ठा fsf_qtcb_header *header = &req->qtcb->header;

	अगर (unlikely(req->status & ZFCP_STATUS_FSFREQ_ERROR))
		वापस;

	zfcp_sdev = sdev_to_zfcp(sdev);

	चयन (header->fsf_status) अणु
	हाल FSF_HANDLE_MISMATCH:
	हाल FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reखोलो(req->adapter, 0, "fssfch1");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_FCPLUN_NOT_VALID:
	हाल FSF_LUN_HANDLE_NOT_VALID:
		zfcp_erp_port_reखोलो(zfcp_sdev->port, 0, "fssfch2");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_SERVICE_CLASS_NOT_SUPPORTED:
		zfcp_fsf_class_not_supp(req);
		अवरोध;
	हाल FSF_सूचीECTION_INDICATOR_NOT_VALID:
		dev_err(&req->adapter->ccw_device->dev,
			"Incorrect direction %d, LUN 0x%016Lx on port "
			"0x%016Lx closed\n",
			req->qtcb->bottom.io.data_direction,
			(अचिन्हित दीर्घ दीर्घ)zfcp_scsi_dev_lun(sdev),
			(अचिन्हित दीर्घ दीर्घ)zfcp_sdev->port->wwpn);
		zfcp_erp_adapter_shutकरोwn(req->adapter, 0, "fssfch3");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_CMND_LENGTH_NOT_VALID:
		dev_err(&req->adapter->ccw_device->dev,
			"Incorrect FCP_CMND length %d, FCP device closed\n",
			req->qtcb->bottom.io.fcp_cmnd_length);
		zfcp_erp_adapter_shutकरोwn(req->adapter, 0, "fssfch4");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_PORT_BOXED:
		zfcp_erp_set_port_status(zfcp_sdev->port,
					 ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_port_reखोलो(zfcp_sdev->port,
				     ZFCP_STATUS_COMMON_ERP_FAILED, "fssfch5");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_LUN_BOXED:
		zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_ACCESS_BOXED);
		zfcp_erp_lun_reखोलो(sdev, ZFCP_STATUS_COMMON_ERP_FAILED,
				    "fssfch6");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_ADAPTER_STATUS_AVAILABLE:
		अगर (header->fsf_status_qual.word[0] ==
		    FSF_SQ_INVOKE_LINK_TEST_PROCEDURE)
			zfcp_fc_test_link(zfcp_sdev->port);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	हाल FSF_SECURITY_ERROR:
		zfcp_fsf_log_security_error(&req->adapter->ccw_device->dev,
					    header->fsf_status_qual.word[0],
					    zfcp_sdev->port->wwpn);
		zfcp_erp_port_क्रमced_reखोलो(zfcp_sdev->port, 0, "fssfch7");
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम zfcp_fsf_fcp_cmnd_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा scsi_cmnd *scpnt;
	काष्ठा fcp_resp_with_ext *fcp_rsp;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&req->adapter->पात_lock, flags);

	scpnt = req->data;
	अगर (unlikely(!scpnt)) अणु
		पढ़ो_unlock_irqrestore(&req->adapter->पात_lock, flags);
		वापस;
	पूर्ण

	zfcp_fsf_fcp_handler_common(req, scpnt->device);

	अगर (unlikely(req->status & ZFCP_STATUS_FSFREQ_ERROR)) अणु
		set_host_byte(scpnt, DID_TRANSPORT_DISRUPTED);
		जाओ skip_fsख_स्थितिus;
	पूर्ण

	चयन (req->qtcb->header.fsf_status) अणु
	हाल FSF_INCONSISTENT_PROT_DATA:
	हाल FSF_INVALID_PROT_PARM:
		set_host_byte(scpnt, DID_ERROR);
		जाओ skip_fsख_स्थितिus;
	हाल FSF_BLOCK_GUARD_CHECK_FAILURE:
		zfcp_scsi_dअगर_sense_error(scpnt, 0x1);
		जाओ skip_fsख_स्थितिus;
	हाल FSF_APP_TAG_CHECK_FAILURE:
		zfcp_scsi_dअगर_sense_error(scpnt, 0x2);
		जाओ skip_fsख_स्थितिus;
	हाल FSF_REF_TAG_CHECK_FAILURE:
		zfcp_scsi_dअगर_sense_error(scpnt, 0x3);
		जाओ skip_fsख_स्थितिus;
	पूर्ण
	BUILD_BUG_ON(माप(काष्ठा fcp_resp_with_ext) > FSF_FCP_RSP_SIZE);
	fcp_rsp = &req->qtcb->bottom.io.fcp_rsp.iu;
	zfcp_fc_eval_fcp_rsp(fcp_rsp, scpnt);

skip_fsख_स्थितिus:
	zfcp_fsf_req_trace(req, scpnt);
	zfcp_dbf_scsi_result(scpnt, req);

	scpnt->host_scribble = शून्य;
	(scpnt->scsi_करोne) (scpnt);
	/*
	 * We must hold this lock until scsi_करोne has been called.
	 * Otherwise we may call scsi_करोne after पात regarding this
	 * command has completed.
	 * Note: scsi_करोne must not block!
	 */
	पढ़ो_unlock_irqrestore(&req->adapter->पात_lock, flags);
पूर्ण

अटल पूर्णांक zfcp_fsf_set_data_dir(काष्ठा scsi_cmnd *scsi_cmnd, u32 *data_dir)
अणु
	चयन (scsi_get_prot_op(scsi_cmnd)) अणु
	हाल SCSI_PROT_NORMAL:
		चयन (scsi_cmnd->sc_data_direction) अणु
		हाल DMA_NONE:
			*data_dir = FSF_DATAसूची_CMND;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			*data_dir = FSF_DATAसूची_READ;
			अवरोध;
		हाल DMA_TO_DEVICE:
			*data_dir = FSF_DATAसूची_WRITE;
			अवरोध;
		हाल DMA_BIसूचीECTIONAL:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल SCSI_PROT_READ_STRIP:
		*data_dir = FSF_DATAसूची_DIF_READ_STRIP;
		अवरोध;
	हाल SCSI_PROT_WRITE_INSERT:
		*data_dir = FSF_DATAसूची_DIF_WRITE_INSERT;
		अवरोध;
	हाल SCSI_PROT_READ_PASS:
		*data_dir = FSF_DATAसूची_DIF_READ_CONVERT;
		अवरोध;
	हाल SCSI_PROT_WRITE_PASS:
		*data_dir = FSF_DATAसूची_DIF_WRITE_CONVERT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zfcp_fsf_fcp_cmnd - initiate an FCP command (क्रम a SCSI command)
 * @scsi_cmnd: scsi command to be sent
 */
पूर्णांक zfcp_fsf_fcp_cmnd(काष्ठा scsi_cmnd *scsi_cmnd)
अणु
	काष्ठा zfcp_fsf_req *req;
	काष्ठा fcp_cmnd *fcp_cmnd;
	u8 sbtype = SBAL_SFLAGS0_TYPE_READ;
	पूर्णांक retval = -EIO;
	काष्ठा scsi_device *sdev = scsi_cmnd->device;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_adapter *adapter = zfcp_sdev->port->adapter;
	काष्ठा zfcp_qdio *qdio = adapter->qdio;
	काष्ठा fsf_qtcb_bottom_io *io;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!(atomic_पढ़ो(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		वापस -EBUSY;

	spin_lock_irqsave(&qdio->req_q_lock, flags);
	अगर (atomic_पढ़ो(&qdio->req_q_मुक्त) <= 0) अणु
		atomic_inc(&qdio->req_q_full);
		जाओ out;
	पूर्ण

	अगर (scsi_cmnd->sc_data_direction == DMA_TO_DEVICE)
		sbtype = SBAL_SFLAGS0_TYPE_WRITE;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_FCP_CMND,
				  sbtype, adapter->pool.scsi_req);

	अगर (IS_ERR(req)) अणु
		retval = PTR_ERR(req);
		जाओ out;
	पूर्ण

	scsi_cmnd->host_scribble = (अचिन्हित अक्षर *) req->req_id;

	io = &req->qtcb->bottom.io;
	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	req->data = scsi_cmnd;
	req->handler = zfcp_fsf_fcp_cmnd_handler;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->qtcb->header.port_handle = zfcp_sdev->port->handle;
	io->service_class = FSF_CLASS_3;
	io->fcp_cmnd_length = FCP_CMND_LEN;

	अगर (scsi_get_prot_op(scsi_cmnd) != SCSI_PROT_NORMAL) अणु
		io->data_block_length = scsi_cmnd->device->sector_size;
		io->ref_tag_value = scsi_get_lba(scsi_cmnd) & 0xFFFFFFFF;
	पूर्ण

	अगर (zfcp_fsf_set_data_dir(scsi_cmnd, &io->data_direction))
		जाओ failed_scsi_cmnd;

	BUILD_BUG_ON(माप(काष्ठा fcp_cmnd) > FSF_FCP_CMND_SIZE);
	fcp_cmnd = &req->qtcb->bottom.io.fcp_cmnd.iu;
	zfcp_fc_scsi_to_fcp(fcp_cmnd, scsi_cmnd);

	अगर ((scsi_get_prot_op(scsi_cmnd) != SCSI_PROT_NORMAL) &&
	    scsi_prot_sg_count(scsi_cmnd)) अणु
		zfcp_qdio_set_data_भाग(qdio, &req->qdio_req,
				       scsi_prot_sg_count(scsi_cmnd));
		retval = zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req,
						 scsi_prot_sglist(scsi_cmnd));
		अगर (retval)
			जाओ failed_scsi_cmnd;
		io->prot_data_length = zfcp_qdio_real_bytes(
						scsi_prot_sglist(scsi_cmnd));
	पूर्ण

	retval = zfcp_qdio_sbals_from_sg(qdio, &req->qdio_req,
					 scsi_sglist(scsi_cmnd));
	अगर (unlikely(retval))
		जाओ failed_scsi_cmnd;

	zfcp_qdio_set_sbale_last(adapter->qdio, &req->qdio_req);
	अगर (zfcp_adapter_multi_buffer_active(adapter))
		zfcp_qdio_set_scount(qdio, &req->qdio_req);

	retval = zfcp_fsf_req_send(req);
	अगर (unlikely(retval))
		जाओ failed_scsi_cmnd;
	/* NOTE: DO NOT TOUCH req PAST THIS POINT! */

	जाओ out;

failed_scsi_cmnd:
	zfcp_fsf_req_मुक्त(req);
	scsi_cmnd->host_scribble = शून्य;
out:
	spin_unlock_irqrestore(&qdio->req_q_lock, flags);
	वापस retval;
पूर्ण

अटल व्योम zfcp_fsf_fcp_task_mgmt_handler(काष्ठा zfcp_fsf_req *req)
अणु
	काष्ठा scsi_device *sdev = req->data;
	काष्ठा fcp_resp_with_ext *fcp_rsp;
	काष्ठा fcp_resp_rsp_info *rsp_info;

	zfcp_fsf_fcp_handler_common(req, sdev);

	fcp_rsp = &req->qtcb->bottom.io.fcp_rsp.iu;
	rsp_info = (काष्ठा fcp_resp_rsp_info *) &fcp_rsp[1];

	अगर ((rsp_info->rsp_code != FCP_TMF_CMPL) ||
	     (req->status & ZFCP_STATUS_FSFREQ_ERROR))
		req->status |= ZFCP_STATUS_FSFREQ_TMFUNCFAILED;
पूर्ण

/**
 * zfcp_fsf_fcp_task_mgmt() - Send SCSI task management command (TMF).
 * @sdev: Poपूर्णांकer to SCSI device to send the task management command to.
 * @पंचांग_flags: Unचिन्हित byte क्रम task management flags.
 *
 * Return: On success poपूर्णांकer to काष्ठा zfcp_fsf_req, %शून्य otherwise.
 */
काष्ठा zfcp_fsf_req *zfcp_fsf_fcp_task_mgmt(काष्ठा scsi_device *sdev,
					    u8 पंचांग_flags)
अणु
	काष्ठा zfcp_fsf_req *req = शून्य;
	काष्ठा fcp_cmnd *fcp_cmnd;
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_qdio *qdio = zfcp_sdev->port->adapter->qdio;

	अगर (unlikely(!(atomic_पढ़ो(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		वापस शून्य;

	spin_lock_irq(&qdio->req_q_lock);
	अगर (zfcp_qdio_sbal_get(qdio))
		जाओ out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_FCP_CMND,
				  SBAL_SFLAGS0_TYPE_WRITE,
				  qdio->adapter->pool.scsi_req);

	अगर (IS_ERR(req)) अणु
		req = शून्य;
		जाओ out;
	पूर्ण

	req->data = sdev;

	req->handler = zfcp_fsf_fcp_task_mgmt_handler;
	req->qtcb->header.lun_handle = zfcp_sdev->lun_handle;
	req->qtcb->header.port_handle = zfcp_sdev->port->handle;
	req->qtcb->bottom.io.data_direction = FSF_DATAसूची_CMND;
	req->qtcb->bottom.io.service_class = FSF_CLASS_3;
	req->qtcb->bottom.io.fcp_cmnd_length = FCP_CMND_LEN;

	zfcp_qdio_set_sbale_last(qdio, &req->qdio_req);

	fcp_cmnd = &req->qtcb->bottom.io.fcp_cmnd.iu;
	zfcp_fc_fcp_पंचांग(fcp_cmnd, sdev, पंचांग_flags);

	zfcp_fsf_start_समयr(req, ZFCP_FSF_SCSI_ER_TIMEOUT);
	अगर (!zfcp_fsf_req_send(req)) अणु
		/* NOTE: DO NOT TOUCH req, UNTIL IT COMPLETES! */
		जाओ out;
	पूर्ण

	zfcp_fsf_req_मुक्त(req);
	req = शून्य;
out:
	spin_unlock_irq(&qdio->req_q_lock);
	वापस req;
पूर्ण

/**
 * zfcp_fsf_reqid_check - validate req_id contained in SBAL वापसed by QDIO
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @sbal_idx: response queue index of SBAL to be processed
 */
व्योम zfcp_fsf_reqid_check(काष्ठा zfcp_qdio *qdio, पूर्णांक sbal_idx)
अणु
	काष्ठा zfcp_adapter *adapter = qdio->adapter;
	काष्ठा qdio_buffer *sbal = qdio->res_q[sbal_idx];
	काष्ठा qdio_buffer_element *sbale;
	काष्ठा zfcp_fsf_req *fsf_req;
	अचिन्हित दीर्घ req_id;
	पूर्णांक idx;

	क्रम (idx = 0; idx < QDIO_MAX_ELEMENTS_PER_BUFFER; idx++) अणु

		sbale = &sbal->element[idx];
		req_id = sbale->addr;
		fsf_req = zfcp_reqlist_find_rm(adapter->req_list, req_id);

		अगर (!fsf_req) अणु
			/*
			 * Unknown request means that we have potentially memory
			 * corruption and must stop the machine immediately.
			 */
			zfcp_qdio_siosl(adapter);
			panic("error: unknown req_id (%lx) on adapter %s.\n",
			      req_id, dev_name(&adapter->ccw_device->dev));
		पूर्ण

		zfcp_fsf_req_complete(fsf_req);

		अगर (likely(sbale->eflags & SBAL_EFLAGS_LAST_ENTRY))
			अवरोध;
	पूर्ण
पूर्ण
