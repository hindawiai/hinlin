<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Interface to Linux SCSI midlayer.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <scsi/fc/fc_fcp.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <linux/atomic.h>
#समावेश "zfcp_ext.h"
#समावेश "zfcp_dbf.h"
#समावेश "zfcp_fc.h"
#समावेश "zfcp_reqlist.h"

अटल अचिन्हित पूर्णांक शेष_depth = 32;
module_param_named(queue_depth, शेष_depth, uपूर्णांक, 0600);
MODULE_PARM_DESC(queue_depth, "Default queue depth for new SCSI devices");

अटल bool enable_dअगर;
module_param_named(dअगर, enable_dअगर, bool, 0400);
MODULE_PARM_DESC(dअगर, "Enable DIF data integrity support (default off)");

bool zfcp_experimental_dix;
module_param_named(dix, zfcp_experimental_dix, bool, 0400);
MODULE_PARM_DESC(dix, "Enable experimental DIX (data integrity extension) support which implies DIF support (default off)");

अटल bool allow_lun_scan = true;
module_param(allow_lun_scan, bool, 0600);
MODULE_PARM_DESC(allow_lun_scan, "For NPIV, scan and attach all storage LUNs");

अटल व्योम zfcp_scsi_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	/* अगर previous slave_alloc वापसed early, there is nothing to करो */
	अगर (!zfcp_sdev->port)
		वापस;

	zfcp_erp_lun_shutकरोwn_रुको(sdev, "scssd_1");
	put_device(&zfcp_sdev->port->dev);
पूर्ण

अटल पूर्णांक zfcp_scsi_slave_configure(काष्ठा scsi_device *sdp)
अणु
	अगर (sdp->tagged_supported)
		scsi_change_queue_depth(sdp, शेष_depth);
	वापस 0;
पूर्ण

अटल व्योम zfcp_scsi_command_fail(काष्ठा scsi_cmnd *scpnt, पूर्णांक result)
अणु
	set_host_byte(scpnt, result);
	zfcp_dbf_scsi_fail_send(scpnt);
	scpnt->scsi_करोne(scpnt);
पूर्ण

अटल
पूर्णांक zfcp_scsi_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *scpnt)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(scpnt->device);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(scpnt->device));
	पूर्णांक    status, scsi_result, ret;

	/* reset the status क्रम this request */
	scpnt->result = 0;
	scpnt->host_scribble = शून्य;

	scsi_result = fc_remote_port_chkपढ़ोy(rport);
	अगर (unlikely(scsi_result)) अणु
		scpnt->result = scsi_result;
		zfcp_dbf_scsi_fail_send(scpnt);
		scpnt->scsi_करोne(scpnt);
		वापस 0;
	पूर्ण

	status = atomic_पढ़ो(&zfcp_sdev->status);
	अगर (unlikely(status & ZFCP_STATUS_COMMON_ERP_FAILED) &&
		     !(atomic_पढ़ो(&zfcp_sdev->port->status) &
		       ZFCP_STATUS_COMMON_ERP_FAILED)) अणु
		/* only LUN access denied, but port is good
		 * not covered by FC transport, have to fail here */
		zfcp_scsi_command_fail(scpnt, DID_ERROR);
		वापस 0;
	पूर्ण

	अगर (unlikely(!(status & ZFCP_STATUS_COMMON_UNBLOCKED))) अणु
		/* This could be
		 * call to rport_delete pending: mimic retry from
		 * 	fc_remote_port_chkपढ़ोy until rport is BLOCKED
		 */
		zfcp_scsi_command_fail(scpnt, DID_IMM_RETRY);
		वापस 0;
	पूर्ण

	ret = zfcp_fsf_fcp_cmnd(scpnt);
	अगर (unlikely(ret == -EBUSY))
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	अन्यथा अगर (unlikely(ret < 0))
		वापस SCSI_MLQUEUE_HOST_BUSY;

	वापस ret;
पूर्ण

अटल पूर्णांक zfcp_scsi_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *) sdev->host->hostdata[0];
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_port *port;
	काष्ठा zfcp_unit *unit;
	पूर्णांक npiv = adapter->connection_features & FSF_FEATURE_NPIV_MODE;

	zfcp_sdev->erp_action.adapter = adapter;
	zfcp_sdev->erp_action.sdev = sdev;

	port = zfcp_get_port_by_wwpn(adapter, rport->port_name);
	अगर (!port)
		वापस -ENXIO;

	zfcp_sdev->erp_action.port = port;

	mutex_lock(&zfcp_sysfs_port_units_mutex);
	अगर (zfcp_sysfs_port_is_removing(port)) अणु
		/* port is alपढ़ोy gone */
		mutex_unlock(&zfcp_sysfs_port_units_mutex);
		put_device(&port->dev); /* unकरो zfcp_get_port_by_wwpn() */
		वापस -ENXIO;
	पूर्ण
	mutex_unlock(&zfcp_sysfs_port_units_mutex);

	unit = zfcp_unit_find(port, zfcp_scsi_dev_lun(sdev));
	अगर (unit)
		put_device(&unit->dev);

	अगर (!unit && !(allow_lun_scan && npiv)) अणु
		put_device(&port->dev);
		वापस -ENXIO;
	पूर्ण

	zfcp_sdev->port = port;
	zfcp_sdev->latencies.ग_लिखो.channel.min = 0xFFFFFFFF;
	zfcp_sdev->latencies.ग_लिखो.fabric.min = 0xFFFFFFFF;
	zfcp_sdev->latencies.पढ़ो.channel.min = 0xFFFFFFFF;
	zfcp_sdev->latencies.पढ़ो.fabric.min = 0xFFFFFFFF;
	zfcp_sdev->latencies.cmd.channel.min = 0xFFFFFFFF;
	zfcp_sdev->latencies.cmd.fabric.min = 0xFFFFFFFF;
	spin_lock_init(&zfcp_sdev->latencies.lock);

	zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_lun_reखोलो(sdev, 0, "scsla_1");
	zfcp_erp_रुको(port->adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक zfcp_scsi_eh_पात_handler(काष्ठा scsi_cmnd *scpnt)
अणु
	काष्ठा Scsi_Host *scsi_host = scpnt->device->host;
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *) scsi_host->hostdata[0];
	काष्ठा zfcp_fsf_req *old_req, *abrt_req;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ old_reqid = (अचिन्हित दीर्घ) scpnt->host_scribble;
	पूर्णांक retval = SUCCESS, ret;
	पूर्णांक retry = 3;
	अक्षर *dbf_tag;

	/* aव्योम race condition between late normal completion and पात */
	ग_लिखो_lock_irqsave(&adapter->पात_lock, flags);

	old_req = zfcp_reqlist_find(adapter->req_list, old_reqid);
	अगर (!old_req) अणु
		ग_लिखो_unlock_irqrestore(&adapter->पात_lock, flags);
		zfcp_dbf_scsi_पात("abrt_or", scpnt, शून्य);
		वापस FAILED; /* completion could be in progress */
	पूर्ण
	old_req->data = शून्य;

	/* करोn't access old fsf_req after releasing the पात_lock */
	ग_लिखो_unlock_irqrestore(&adapter->पात_lock, flags);

	जबतक (retry--) अणु
		abrt_req = zfcp_fsf_पात_fcp_cmnd(scpnt);
		अगर (abrt_req)
			अवरोध;

		zfcp_dbf_scsi_पात("abrt_wt", scpnt, शून्य);
		zfcp_erp_रुको(adapter);
		ret = fc_block_scsi_eh(scpnt);
		अगर (ret) अणु
			zfcp_dbf_scsi_पात("abrt_bl", scpnt, शून्य);
			वापस ret;
		पूर्ण
		अगर (!(atomic_पढ़ो(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING)) अणु
			zfcp_dbf_scsi_पात("abrt_ru", scpnt, शून्य);
			वापस SUCCESS;
		पूर्ण
	पूर्ण
	अगर (!abrt_req) अणु
		zfcp_dbf_scsi_पात("abrt_ar", scpnt, शून्य);
		वापस FAILED;
	पूर्ण

	रुको_क्रम_completion(&abrt_req->completion);

	अगर (abrt_req->status & ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED)
		dbf_tag = "abrt_ok";
	अन्यथा अगर (abrt_req->status & ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED)
		dbf_tag = "abrt_nn";
	अन्यथा अणु
		dbf_tag = "abrt_fa";
		retval = FAILED;
	पूर्ण
	zfcp_dbf_scsi_पात(dbf_tag, scpnt, abrt_req);
	zfcp_fsf_req_मुक्त(abrt_req);
	वापस retval;
पूर्ण

काष्ठा zfcp_scsi_req_filter अणु
	u8 पंचांगf_scope;
	u32 lun_handle;
	u32 port_handle;
पूर्ण;

अटल व्योम zfcp_scsi_क्रमget_cmnd(काष्ठा zfcp_fsf_req *old_req, व्योम *data)
अणु
	काष्ठा zfcp_scsi_req_filter *filter =
		(काष्ठा zfcp_scsi_req_filter *)data;

	/* alपढ़ोy पातed - prevent side-effects - or not a SCSI command */
	अगर (old_req->data == शून्य ||
	    zfcp_fsf_req_is_status_पढ़ो_buffer(old_req) ||
	    old_req->qtcb->header.fsf_command != FSF_QTCB_FCP_CMND)
		वापस;

	/* (पंचांगf_scope == FCP_TMF_TGT_RESET || पंचांगf_scope == FCP_TMF_LUN_RESET) */
	अगर (old_req->qtcb->header.port_handle != filter->port_handle)
		वापस;

	अगर (filter->पंचांगf_scope == FCP_TMF_LUN_RESET &&
	    old_req->qtcb->header.lun_handle != filter->lun_handle)
		वापस;

	zfcp_dbf_scsi_nullcmnd((काष्ठा scsi_cmnd *)old_req->data, old_req);
	old_req->data = शून्य;
पूर्ण

अटल व्योम zfcp_scsi_क्रमget_cmnds(काष्ठा zfcp_scsi_dev *zsdev, u8 पंचांग_flags)
अणु
	काष्ठा zfcp_adapter *adapter = zsdev->port->adapter;
	काष्ठा zfcp_scsi_req_filter filter = अणु
		.पंचांगf_scope = FCP_TMF_TGT_RESET,
		.port_handle = zsdev->port->handle,
	पूर्ण;
	अचिन्हित दीर्घ flags;

	अगर (पंचांग_flags == FCP_TMF_LUN_RESET) अणु
		filter.पंचांगf_scope = FCP_TMF_LUN_RESET;
		filter.lun_handle = zsdev->lun_handle;
	पूर्ण

	/*
	 * पात_lock secures against other processings - in the पात-function
	 * and normal cmnd-handler - of (काष्ठा zfcp_fsf_req *)->data
	 */
	ग_लिखो_lock_irqsave(&adapter->पात_lock, flags);
	zfcp_reqlist_apply_क्रम_all(adapter->req_list, zfcp_scsi_क्रमget_cmnd,
				   &filter);
	ग_लिखो_unlock_irqrestore(&adapter->पात_lock, flags);
पूर्ण

/**
 * zfcp_scsi_task_mgmt_function() - Send a task management function (sync).
 * @sdev: Poपूर्णांकer to SCSI device to send the task management command to.
 * @पंचांग_flags: Task management flags,
 *	      here we only handle %FCP_TMF_TGT_RESET or %FCP_TMF_LUN_RESET.
 */
अटल पूर्णांक zfcp_scsi_task_mgmt_function(काष्ठा scsi_device *sdev, u8 पंचांग_flags)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	काष्ठा zfcp_adapter *adapter = zfcp_sdev->port->adapter;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा zfcp_fsf_req *fsf_req = शून्य;
	पूर्णांक retval = SUCCESS, ret;
	पूर्णांक retry = 3;

	जबतक (retry--) अणु
		fsf_req = zfcp_fsf_fcp_task_mgmt(sdev, पंचांग_flags);
		अगर (fsf_req)
			अवरोध;

		zfcp_dbf_scsi_devreset("wait", sdev, पंचांग_flags, शून्य);
		zfcp_erp_रुको(adapter);
		ret = fc_block_rport(rport);
		अगर (ret) अणु
			zfcp_dbf_scsi_devreset("fiof", sdev, पंचांग_flags, शून्य);
			वापस ret;
		पूर्ण

		अगर (!(atomic_पढ़ो(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING)) अणु
			zfcp_dbf_scsi_devreset("nres", sdev, पंचांग_flags, शून्य);
			वापस SUCCESS;
		पूर्ण
	पूर्ण
	अगर (!fsf_req) अणु
		zfcp_dbf_scsi_devreset("reqf", sdev, पंचांग_flags, शून्य);
		वापस FAILED;
	पूर्ण

	रुको_क्रम_completion(&fsf_req->completion);

	अगर (fsf_req->status & ZFCP_STATUS_FSFREQ_TMFUNCFAILED) अणु
		zfcp_dbf_scsi_devreset("fail", sdev, पंचांग_flags, fsf_req);
		retval = FAILED;
	पूर्ण अन्यथा अणु
		zfcp_dbf_scsi_devreset("okay", sdev, पंचांग_flags, fsf_req);
		zfcp_scsi_क्रमget_cmnds(zfcp_sdev, पंचांग_flags);
	पूर्ण

	zfcp_fsf_req_मुक्त(fsf_req);
	वापस retval;
पूर्ण

अटल पूर्णांक zfcp_scsi_eh_device_reset_handler(काष्ठा scsi_cmnd *scpnt)
अणु
	काष्ठा scsi_device *sdev = scpnt->device;

	वापस zfcp_scsi_task_mgmt_function(sdev, FCP_TMF_LUN_RESET);
पूर्ण

अटल पूर्णांक zfcp_scsi_eh_target_reset_handler(काष्ठा scsi_cmnd *scpnt)
अणु
	काष्ठा scsi_target *starget = scsi_target(scpnt->device);
	काष्ठा fc_rport *rport = starget_to_rport(starget);
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा scsi_device *sdev = शून्य, *पंचांगp_sdev;
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *)shost->hostdata[0];
	पूर्णांक ret;

	shost_क्रम_each_device(पंचांगp_sdev, shost) अणु
		अगर (पंचांगp_sdev->id == starget->id) अणु
			sdev = पंचांगp_sdev;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!sdev) अणु
		ret = FAILED;
		zfcp_dbf_scsi_eh("tr_nosd", adapter, starget->id, ret);
		वापस ret;
	पूर्ण

	ret = zfcp_scsi_task_mgmt_function(sdev, FCP_TMF_TGT_RESET);

	/* release reference from above shost_क्रम_each_device */
	अगर (sdev)
		scsi_device_put(पंचांगp_sdev);

	वापस ret;
पूर्ण

अटल पूर्णांक zfcp_scsi_eh_host_reset_handler(काष्ठा scsi_cmnd *scpnt)
अणु
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(scpnt->device);
	काष्ठा zfcp_adapter *adapter = zfcp_sdev->port->adapter;
	पूर्णांक ret = SUCCESS, fc_ret;

	अगर (!(adapter->connection_features & FSF_FEATURE_NPIV_MODE)) अणु
		zfcp_erp_port_क्रमced_reखोलो_all(adapter, 0, "schrh_p");
		zfcp_erp_रुको(adapter);
	पूर्ण
	zfcp_erp_adapter_reखोलो(adapter, 0, "schrh_1");
	zfcp_erp_रुको(adapter);
	fc_ret = fc_block_scsi_eh(scpnt);
	अगर (fc_ret)
		ret = fc_ret;

	zfcp_dbf_scsi_eh("schrh_r", adapter, ~0, ret);
	वापस ret;
पूर्ण

/**
 * zfcp_scsi_sysfs_host_reset() - Support scsi_host sysfs attribute host_reset.
 * @shost: Poपूर्णांकer to Scsi_Host to perक्रमm action on.
 * @reset_type: We support %SCSI_ADAPTER_RESET but not %SCSI_FIRMWARE_RESET.
 *
 * Return: 0 on %SCSI_ADAPTER_RESET, -%EOPNOTSUPP otherwise.
 *
 * This is similar to zfcp_sysfs_adapter_failed_store().
 */
अटल पूर्णांक zfcp_scsi_sysfs_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type)
अणु
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *)shost->hostdata[0];
	पूर्णांक ret = 0;

	अगर (reset_type != SCSI_ADAPTER_RESET) अणु
		ret = -EOPNOTSUPP;
		zfcp_dbf_scsi_eh("scshr_n", adapter, ~0, ret);
		वापस ret;
	पूर्ण

	zfcp_erp_adapter_reset_sync(adapter, "scshr_y");
	वापस ret;
पूर्ण

काष्ठा scsi_transport_ढाँचा *zfcp_scsi_transport_ढाँचा;

अटल काष्ठा scsi_host_ढाँचा zfcp_scsi_host_ढाँचा = अणु
	.module			 = THIS_MODULE,
	.name			 = "zfcp",
	.queuecommand		 = zfcp_scsi_queuecommand,
	.eh_समयd_out		 = fc_eh_समयd_out,
	.eh_पात_handler	 = zfcp_scsi_eh_पात_handler,
	.eh_device_reset_handler = zfcp_scsi_eh_device_reset_handler,
	.eh_target_reset_handler = zfcp_scsi_eh_target_reset_handler,
	.eh_host_reset_handler	 = zfcp_scsi_eh_host_reset_handler,
	.slave_alloc		 = zfcp_scsi_slave_alloc,
	.slave_configure	 = zfcp_scsi_slave_configure,
	.slave_destroy		 = zfcp_scsi_slave_destroy,
	.change_queue_depth	 = scsi_change_queue_depth,
	.host_reset		 = zfcp_scsi_sysfs_host_reset,
	.proc_name		 = "zfcp",
	.can_queue		 = 4096,
	.this_id		 = -1,
	.sg_tablesize		 = (((QDIO_MAX_ELEMENTS_PER_BUFFER - 1)
				     * ZFCP_QDIO_MAX_SBALS_PER_REQ) - 2),
				   /* GCD, adjusted later */
	.max_sectors		 = (((QDIO_MAX_ELEMENTS_PER_BUFFER - 1)
				     * ZFCP_QDIO_MAX_SBALS_PER_REQ) - 2) * 8,
				   /* GCD, adjusted later */
	/* report size limit per scatter-gather segment */
	.max_segment_size	 = ZFCP_QDIO_SBALE_LEN,
	.dma_boundary		 = ZFCP_QDIO_SBALE_LEN - 1,
	.shost_attrs		 = zfcp_sysfs_shost_attrs,
	.sdev_attrs		 = zfcp_sysfs_sdev_attrs,
	.track_queue_depth	 = 1,
	.supported_mode		 = MODE_INITIATOR,
पूर्ण;

/**
 * zfcp_scsi_adapter_रेजिस्टर() - Allocate and रेजिस्टर SCSI and FC host with
 *				  SCSI midlayer
 * @adapter: The zfcp adapter to रेजिस्टर with the SCSI midlayer
 *
 * Allocates the SCSI host object क्रम the given adapter, sets basic properties
 * (such as the transport ढाँचा, QDIO limits, ...), and रेजिस्टरs it with
 * the midlayer.
 *
 * During registration with the midlayer the corresponding FC host object क्रम
 * the referenced transport class is also implicitely allocated.
 *
 * Upon success adapter->scsi_host is set, and upon failure it reमुख्यs शून्य. If
 * adapter->scsi_host is alपढ़ोy set, nothing is करोne.
 *
 * Return:
 * * 0	     - Allocation and registration was successful
 * * -EEXIST - SCSI and FC host did alपढ़ोy exist, nothing was करोne, nothing
 *	       was changed
 * * -EIO    - Allocation or registration failed
 */
पूर्णांक zfcp_scsi_adapter_रेजिस्टर(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा ccw_dev_id dev_id;

	अगर (adapter->scsi_host)
		वापस -EEXIST;

	ccw_device_get_id(adapter->ccw_device, &dev_id);
	/* रेजिस्टर adapter as SCSI host with mid layer of SCSI stack */
	adapter->scsi_host = scsi_host_alloc(&zfcp_scsi_host_ढाँचा,
					     माप (काष्ठा zfcp_adapter *));
	अगर (!adapter->scsi_host)
		जाओ err_out;

	/* tell the SCSI stack some अक्षरacteristics of this adapter */
	adapter->scsi_host->max_id = 511;
	adapter->scsi_host->max_lun = 0xFFFFFFFF;
	adapter->scsi_host->max_channel = 0;
	adapter->scsi_host->unique_id = dev_id.devno;
	adapter->scsi_host->max_cmd_len = 16; /* in काष्ठा fcp_cmnd */
	adapter->scsi_host->transportt = zfcp_scsi_transport_ढाँचा;

	/* make all basic properties known at registration समय */
	zfcp_qdio_shost_update(adapter, adapter->qdio);
	zfcp_scsi_set_prot(adapter);

	adapter->scsi_host->hostdata[0] = (अचिन्हित दीर्घ) adapter;

	अगर (scsi_add_host(adapter->scsi_host, &adapter->ccw_device->dev)) अणु
		scsi_host_put(adapter->scsi_host);
		जाओ err_out;
	पूर्ण

	वापस 0;
err_out:
	adapter->scsi_host = शून्य;
	dev_err(&adapter->ccw_device->dev,
		"Registering the FCP device with the SCSI stack failed\n");
	वापस -EIO;
पूर्ण

/**
 * zfcp_scsi_adapter_unरेजिस्टर - Unरेजिस्टर SCSI and FC host from SCSI midlayer
 * @adapter: The zfcp adapter to unरेजिस्टर.
 */
व्योम zfcp_scsi_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा zfcp_port *port;

	shost = adapter->scsi_host;
	अगर (!shost)
		वापस;

	पढ़ो_lock_irq(&adapter->port_list_lock);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		port->rport = शून्य;
	पढ़ो_unlock_irq(&adapter->port_list_lock);

	fc_हटाओ_host(shost);
	scsi_हटाओ_host(shost);
	scsi_host_put(shost);
	adapter->scsi_host = शून्य;
पूर्ण

अटल काष्ठा fc_host_statistics*
zfcp_scsi_init_fc_host_stats(काष्ठा zfcp_adapter *adapter)
अणु
	काष्ठा fc_host_statistics *fc_stats;

	अगर (!adapter->fc_stats) अणु
		fc_stats = kदो_स्मृति(माप(*fc_stats), GFP_KERNEL);
		अगर (!fc_stats)
			वापस शून्य;
		adapter->fc_stats = fc_stats; /* मुक्तd in adapter_release */
	पूर्ण
	स_रखो(adapter->fc_stats, 0, माप(*adapter->fc_stats));
	वापस adapter->fc_stats;
पूर्ण

अटल व्योम zfcp_scsi_adjust_fc_host_stats(काष्ठा fc_host_statistics *fc_stats,
					   काष्ठा fsf_qtcb_bottom_port *data,
					   काष्ठा fsf_qtcb_bottom_port *old)
अणु
	fc_stats->seconds_since_last_reset =
		data->seconds_since_last_reset - old->seconds_since_last_reset;
	fc_stats->tx_frames = data->tx_frames - old->tx_frames;
	fc_stats->tx_words = data->tx_words - old->tx_words;
	fc_stats->rx_frames = data->rx_frames - old->rx_frames;
	fc_stats->rx_words = data->rx_words - old->rx_words;
	fc_stats->lip_count = data->lip - old->lip;
	fc_stats->nos_count = data->nos - old->nos;
	fc_stats->error_frames = data->error_frames - old->error_frames;
	fc_stats->dumped_frames = data->dumped_frames - old->dumped_frames;
	fc_stats->link_failure_count = data->link_failure - old->link_failure;
	fc_stats->loss_of_sync_count = data->loss_of_sync - old->loss_of_sync;
	fc_stats->loss_of_संकेत_count =
		data->loss_of_संकेत - old->loss_of_संकेत;
	fc_stats->prim_seq_protocol_err_count =
		data->psp_error_counts - old->psp_error_counts;
	fc_stats->invalid_tx_word_count =
		data->invalid_tx_words - old->invalid_tx_words;
	fc_stats->invalid_crc_count = data->invalid_crcs - old->invalid_crcs;
	fc_stats->fcp_input_requests =
		data->input_requests - old->input_requests;
	fc_stats->fcp_output_requests =
		data->output_requests - old->output_requests;
	fc_stats->fcp_control_requests =
		data->control_requests - old->control_requests;
	fc_stats->fcp_input_megabytes = data->input_mb - old->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb - old->output_mb;
पूर्ण

अटल व्योम zfcp_scsi_set_fc_host_stats(काष्ठा fc_host_statistics *fc_stats,
					काष्ठा fsf_qtcb_bottom_port *data)
अणु
	fc_stats->seconds_since_last_reset = data->seconds_since_last_reset;
	fc_stats->tx_frames = data->tx_frames;
	fc_stats->tx_words = data->tx_words;
	fc_stats->rx_frames = data->rx_frames;
	fc_stats->rx_words = data->rx_words;
	fc_stats->lip_count = data->lip;
	fc_stats->nos_count = data->nos;
	fc_stats->error_frames = data->error_frames;
	fc_stats->dumped_frames = data->dumped_frames;
	fc_stats->link_failure_count = data->link_failure;
	fc_stats->loss_of_sync_count = data->loss_of_sync;
	fc_stats->loss_of_संकेत_count = data->loss_of_संकेत;
	fc_stats->prim_seq_protocol_err_count = data->psp_error_counts;
	fc_stats->invalid_tx_word_count = data->invalid_tx_words;
	fc_stats->invalid_crc_count = data->invalid_crcs;
	fc_stats->fcp_input_requests = data->input_requests;
	fc_stats->fcp_output_requests = data->output_requests;
	fc_stats->fcp_control_requests = data->control_requests;
	fc_stats->fcp_input_megabytes = data->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb;
पूर्ण

अटल काष्ठा fc_host_statistics *
zfcp_scsi_get_fc_host_stats(काष्ठा Scsi_Host *host)
अणु
	काष्ठा zfcp_adapter *adapter;
	काष्ठा fc_host_statistics *fc_stats;
	काष्ठा fsf_qtcb_bottom_port *data;
	पूर्णांक ret;

	adapter = (काष्ठा zfcp_adapter *)host->hostdata[0];
	fc_stats = zfcp_scsi_init_fc_host_stats(adapter);
	अगर (!fc_stats)
		वापस शून्य;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	ret = zfcp_fsf_exchange_port_data_sync(adapter->qdio, data);
	अगर (ret != 0 && ret != -EAGAIN) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	अगर (adapter->stats_reset &&
	    ((jअगरfies/HZ - adapter->stats_reset) <
	     data->seconds_since_last_reset))
		zfcp_scsi_adjust_fc_host_stats(fc_stats, data,
					       adapter->stats_reset_data);
	अन्यथा
		zfcp_scsi_set_fc_host_stats(fc_stats, data);

	kमुक्त(data);
	वापस fc_stats;
पूर्ण

अटल व्योम zfcp_scsi_reset_fc_host_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा zfcp_adapter *adapter;
	काष्ठा fsf_qtcb_bottom_port *data;
	पूर्णांक ret;

	adapter = (काष्ठा zfcp_adapter *)shost->hostdata[0];
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस;

	ret = zfcp_fsf_exchange_port_data_sync(adapter->qdio, data);
	अगर (ret != 0 && ret != -EAGAIN)
		kमुक्त(data);
	अन्यथा अणु
		adapter->stats_reset = jअगरfies/HZ;
		kमुक्त(adapter->stats_reset_data);
		adapter->stats_reset_data = data; /* finally मुक्तd in
						     adapter_release */
	पूर्ण
पूर्ण

अटल व्योम zfcp_scsi_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *)shost->hostdata[0];
	पूर्णांक status = atomic_पढ़ो(&adapter->status);

	अगर ((status & ZFCP_STATUS_COMMON_RUNNING) &&
	    !(status & ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED))
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
	अन्यथा अगर (status & ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED)
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
	अन्यथा अगर (status & ZFCP_STATUS_COMMON_ERP_FAILED)
		fc_host_port_state(shost) = FC_PORTSTATE_ERROR;
	अन्यथा
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
पूर्ण

अटल व्योम zfcp_scsi_set_rport_dev_loss_पंचांगo(काष्ठा fc_rport *rport,
					     u32 समयout)
अणु
	rport->dev_loss_पंचांगo = समयout;
पूर्ण

/**
 * zfcp_scsi_terminate_rport_io - Terminate all I/O on a rport
 * @rport: The FC rport where to teminate I/O
 *
 * Abort all pending SCSI commands क्रम a port by closing the
 * port. Using a reखोलो aव्योमs a conflict with a shutकरोwn
 * overwriting a reखोलो. The "forced" ensures that a disappeared port
 * is not खोलोed again as valid due to the cached plogi data in
 * non-NPIV mode.
 */
अटल व्योम zfcp_scsi_terminate_rport_io(काष्ठा fc_rport *rport)
अणु
	काष्ठा zfcp_port *port;
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा zfcp_adapter *adapter =
		(काष्ठा zfcp_adapter *)shost->hostdata[0];

	port = zfcp_get_port_by_wwpn(adapter, rport->port_name);

	अगर (port) अणु
		zfcp_erp_port_क्रमced_reखोलो(port, 0, "sctrpi1");
		put_device(&port->dev);
	पूर्ण अन्यथा अणु
		zfcp_erp_port_क्रमced_no_port_dbf(
			"sctrpin", adapter,
			rport->port_name /* zfcp_scsi_rport_रेजिस्टर */,
			rport->port_id /* zfcp_scsi_rport_रेजिस्टर */);
	पूर्ण
पूर्ण

अटल व्योम zfcp_scsi_rport_रेजिस्टर(काष्ठा zfcp_port *port)
अणु
	काष्ठा fc_rport_identअगरiers ids;
	काष्ठा fc_rport *rport;

	अगर (port->rport)
		वापस;

	ids.node_name = port->wwnn;
	ids.port_name = port->wwpn;
	ids.port_id = port->d_id;
	ids.roles = FC_RPORT_ROLE_FCP_TARGET;

	zfcp_dbf_rec_trig_lock("scpaddy", port->adapter, port, शून्य,
			       ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD,
			       ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD);
	rport = fc_remote_port_add(port->adapter->scsi_host, 0, &ids);
	अगर (!rport) अणु
		dev_err(&port->adapter->ccw_device->dev,
			"Registering port 0x%016Lx failed\n",
			(अचिन्हित दीर्घ दीर्घ)port->wwpn);
		वापस;
	पूर्ण

	rport->maxframe_size = port->maxframe_size;
	rport->supported_classes = port->supported_classes;
	port->rport = rport;
	port->starget_id = rport->scsi_target_id;

	zfcp_unit_queue_scsi_scan(port);
पूर्ण

अटल व्योम zfcp_scsi_rport_block(काष्ठा zfcp_port *port)
अणु
	काष्ठा fc_rport *rport = port->rport;

	अगर (rport) अणु
		zfcp_dbf_rec_trig_lock("scpdely", port->adapter, port, शून्य,
				       ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL,
				       ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL);
		fc_remote_port_delete(rport);
		port->rport = शून्य;
	पूर्ण
पूर्ण

व्योम zfcp_scsi_schedule_rport_रेजिस्टर(काष्ठा zfcp_port *port)
अणु
	get_device(&port->dev);
	port->rport_task = RPORT_ADD;

	अगर (!queue_work(port->adapter->work_queue, &port->rport_work))
		put_device(&port->dev);
पूर्ण

व्योम zfcp_scsi_schedule_rport_block(काष्ठा zfcp_port *port)
अणु
	get_device(&port->dev);
	port->rport_task = RPORT_DEL;

	अगर (port->rport && queue_work(port->adapter->work_queue,
				      &port->rport_work))
		वापस;

	put_device(&port->dev);
पूर्ण

व्योम zfcp_scsi_schedule_rports_block(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zfcp_port *port;

	पढ़ो_lock_irqsave(&adapter->port_list_lock, flags);
	list_क्रम_each_entry(port, &adapter->port_list, list)
		zfcp_scsi_schedule_rport_block(port);
	पढ़ो_unlock_irqrestore(&adapter->port_list_lock, flags);
पूर्ण

व्योम zfcp_scsi_rport_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_port *port = container_of(work, काष्ठा zfcp_port,
					      rport_work);

	set_worker_desc("zrp%c-%16llx",
			(port->rport_task == RPORT_ADD) ? 'a' : 'd',
			port->wwpn); /* < WORKER_DESC_LEN=24 */
	जबतक (port->rport_task) अणु
		अगर (port->rport_task == RPORT_ADD) अणु
			port->rport_task = RPORT_NONE;
			zfcp_scsi_rport_रेजिस्टर(port);
		पूर्ण अन्यथा अणु
			port->rport_task = RPORT_NONE;
			zfcp_scsi_rport_block(port);
		पूर्ण
	पूर्ण

	put_device(&port->dev);
पूर्ण

/**
 * zfcp_scsi_set_prot - Configure DIF/DIX support in scsi_host
 * @adapter: The adapter where to configure DIF/DIX क्रम the SCSI host
 */
व्योम zfcp_scsi_set_prot(काष्ठा zfcp_adapter *adapter)
अणु
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक data_भाग;
	काष्ठा Scsi_Host *shost = adapter->scsi_host;

	data_भाग = atomic_पढ़ो(&adapter->status) &
		   ZFCP_STATUS_ADAPTER_DATA_DIV_ENABLED;

	अगर ((enable_dअगर || zfcp_experimental_dix) &&
	    adapter->adapter_features & FSF_FEATURE_DIF_PROT_TYPE1)
		mask |= SHOST_DIF_TYPE1_PROTECTION;

	अगर (zfcp_experimental_dix && data_भाग &&
	    adapter->adapter_features & FSF_FEATURE_DIX_PROT_TCPIP) अणु
		mask |= SHOST_DIX_TYPE1_PROTECTION;
		scsi_host_set_guard(shost, SHOST_DIX_GUARD_IP);
		shost->sg_prot_tablesize = adapter->qdio->max_sbale_per_req / 2;
		shost->sg_tablesize = adapter->qdio->max_sbale_per_req / 2;
		shost->max_sectors = shost->sg_tablesize * 8;
	पूर्ण

	scsi_host_set_prot(shost, mask);
पूर्ण

/**
 * zfcp_scsi_dअगर_sense_error - Report DIF/DIX error as driver sense error
 * @scmd: The SCSI command to report the error क्रम
 * @ascq: The ASCQ to put in the sense buffer
 *
 * See the error handling in sd_करोne क्रम the sense codes used here.
 * Set DID_SOFT_ERROR to retry the request, अगर possible.
 */
व्योम zfcp_scsi_dअगर_sense_error(काष्ठा scsi_cmnd *scmd, पूर्णांक ascq)
अणु
	scsi_build_sense_buffer(1, scmd->sense_buffer,
				ILLEGAL_REQUEST, 0x10, ascq);
	set_driver_byte(scmd, DRIVER_SENSE);
	scmd->result |= SAM_STAT_CHECK_CONDITION;
	set_host_byte(scmd, DID_SOFT_ERROR);
पूर्ण

व्योम zfcp_scsi_shost_update_config_data(
	काष्ठा zfcp_adapter *स्थिर adapter,
	स्थिर काष्ठा fsf_qtcb_bottom_config *स्थिर bottom,
	स्थिर bool bottom_incomplete)
अणु
	काष्ठा Scsi_Host *स्थिर shost = adapter->scsi_host;
	स्थिर काष्ठा fc_els_flogi *nsp, *plogi;

	अगर (shost == शून्य)
		वापस;

	snम_लिखो(fc_host_firmware_version(shost), FC_VERSION_STRING_SIZE,
		 "0x%08x", bottom->lic_version);

	अगर (adapter->adapter_features & FSF_FEATURE_HBAAPI_MANAGEMENT) अणु
		snम_लिखो(fc_host_hardware_version(shost),
			 FC_VERSION_STRING_SIZE,
			 "0x%08x", bottom->hardware_version);
		स_नकल(fc_host_serial_number(shost), bottom->serial_number,
		       min(FC_SERIAL_NUMBER_SIZE, 17));
		EBCASC(fc_host_serial_number(shost),
		       min(FC_SERIAL_NUMBER_SIZE, 17));
	पूर्ण

	/* adjust poपूर्णांकers क्रम missing command code */
	nsp = (काष्ठा fc_els_flogi *) ((u8 *)&bottom->nport_serv_param
					- माप(u32));
	plogi = (काष्ठा fc_els_flogi *) ((u8 *)&bottom->plogi_payload
					- माप(u32));

	snम_लिखो(fc_host_manufacturer(shost), FC_SERIAL_NUMBER_SIZE, "%s",
		 "IBM");
	fc_host_port_name(shost) = be64_to_cpu(nsp->fl_wwpn);
	fc_host_node_name(shost) = be64_to_cpu(nsp->fl_wwnn);
	fc_host_supported_classes(shost) = FC_COS_CLASS2 | FC_COS_CLASS3;

	zfcp_scsi_set_prot(adapter);

	/* करो not evaluate invalid fields */
	अगर (bottom_incomplete)
		वापस;

	fc_host_port_id(shost) = ntoh24(bottom->s_id);
	fc_host_speed(shost) =
		zfcp_fsf_convert_portspeed(bottom->fc_link_speed);

	snम_लिखो(fc_host_model(shost), FC_SYMBOLIC_NAME_SIZE, "0x%04x",
		 bottom->adapter_type);

	चयन (bottom->fc_topology) अणु
	हाल FSF_TOPO_P2P:
		fc_host_port_type(shost) = FC_PORTTYPE_PTP;
		fc_host_fabric_name(shost) = 0;
		अवरोध;
	हाल FSF_TOPO_FABRIC:
		fc_host_fabric_name(shost) = be64_to_cpu(plogi->fl_wwnn);
		अगर (bottom->connection_features & FSF_FEATURE_NPIV_MODE)
			fc_host_port_type(shost) = FC_PORTTYPE_NPIV;
		अन्यथा
			fc_host_port_type(shost) = FC_PORTTYPE_NPORT;
		अवरोध;
	हाल FSF_TOPO_AL:
		fc_host_port_type(shost) = FC_PORTTYPE_NLPORT;
		fallthrough;
	शेष:
		fc_host_fabric_name(shost) = 0;
		अवरोध;
	पूर्ण
पूर्ण

व्योम zfcp_scsi_shost_update_port_data(
	काष्ठा zfcp_adapter *स्थिर adapter,
	स्थिर काष्ठा fsf_qtcb_bottom_port *स्थिर bottom)
अणु
	काष्ठा Scsi_Host *स्थिर shost = adapter->scsi_host;

	अगर (shost == शून्य)
		वापस;

	fc_host_permanent_port_name(shost) = bottom->wwpn;
	fc_host_maxframe_size(shost) = bottom->maximum_frame_size;
	fc_host_supported_speeds(shost) =
		zfcp_fsf_convert_portspeed(bottom->supported_speed);
	स_नकल(fc_host_supported_fc4s(shost), bottom->supported_fc4_types,
	       FC_FC4_LIST_SIZE);
	स_नकल(fc_host_active_fc4s(shost), bottom->active_fc4_types,
	       FC_FC4_LIST_SIZE);
पूर्ण

काष्ठा fc_function_ढाँचा zfcp_transport_functions = अणु
	.show_starget_port_id = 1,
	.show_starget_port_name = 1,
	.show_starget_node_name = 1,
	.show_rport_supported_classes = 1,
	.show_rport_maxframe_size = 1,
	.show_rport_dev_loss_पंचांगo = 1,
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_permanent_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_supported_speeds = 1,
	.show_host_maxframe_size = 1,
	.show_host_serial_number = 1,
	.show_host_manufacturer = 1,
	.show_host_model = 1,
	.show_host_hardware_version = 1,
	.show_host_firmware_version = 1,
	.get_fc_host_stats = zfcp_scsi_get_fc_host_stats,
	.reset_fc_host_stats = zfcp_scsi_reset_fc_host_stats,
	.set_rport_dev_loss_पंचांगo = zfcp_scsi_set_rport_dev_loss_पंचांगo,
	.get_host_port_state = zfcp_scsi_get_host_port_state,
	.terminate_rport_io = zfcp_scsi_terminate_rport_io,
	.show_host_port_state = 1,
	.show_host_active_fc4s = 1,
	.bsg_request = zfcp_fc_exec_bsg_job,
	.bsg_समयout = zfcp_fc_समयout_bsg_job,
	/* no functions रेजिस्टरed क्रम following dynamic attributes but
	   directly set by LLDD */
	.show_host_port_type = 1,
	.show_host_symbolic_name = 1,
	.show_host_speed = 1,
	.show_host_port_id = 1,
	.show_host_fabric_name = 1,
	.dd_bsg_size = माप(काष्ठा zfcp_fsf_ct_els),
पूर्ण;
