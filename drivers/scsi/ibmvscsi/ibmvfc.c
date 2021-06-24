<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ibmvfc.c -- driver क्रम IBM Power Virtual Fibre Channel Adapter
 *
 * Written By: Brian King <brking@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) IBM Corporation, 2008
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/bsg-lib.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/vपन.स>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_bsg_fc.h>
#समावेश "ibmvfc.h"

अटल अचिन्हित पूर्णांक init_समयout = IBMVFC_INIT_TIMEOUT;
अटल अचिन्हित पूर्णांक शेष_समयout = IBMVFC_DEFAULT_TIMEOUT;
अटल u64 max_lun = IBMVFC_MAX_LUN;
अटल अचिन्हित पूर्णांक max_tarमाला_लो = IBMVFC_MAX_TARGETS;
अटल अचिन्हित पूर्णांक max_requests = IBMVFC_MAX_REQUESTS_DEFAULT;
अटल अचिन्हित पूर्णांक disc_thपढ़ोs = IBMVFC_MAX_DISC_THREADS;
अटल अचिन्हित पूर्णांक ibmvfc_debug = IBMVFC_DEBUG;
अटल अचिन्हित पूर्णांक log_level = IBMVFC_DEFAULT_LOG_LEVEL;
अटल अचिन्हित पूर्णांक cls3_error = IBMVFC_CLS3_ERROR;
अटल अचिन्हित पूर्णांक mq_enabled = IBMVFC_MQ;
अटल अचिन्हित पूर्णांक nr_scsi_hw_queues = IBMVFC_SCSI_HW_QUEUES;
अटल अचिन्हित पूर्णांक nr_scsi_channels = IBMVFC_SCSI_CHANNELS;
अटल अचिन्हित पूर्णांक mig_channels_only = IBMVFC_MIG_NO_SUB_TO_CRQ;
अटल अचिन्हित पूर्णांक mig_no_less_channels = IBMVFC_MIG_NO_N_TO_M;

अटल LIST_HEAD(ibmvfc_head);
अटल DEFINE_SPINLOCK(ibmvfc_driver_lock);
अटल काष्ठा scsi_transport_ढाँचा *ibmvfc_transport_ढाँचा;

MODULE_DESCRIPTION("IBM Virtual Fibre Channel Driver");
MODULE_AUTHOR("Brian King <brking@linux.vnet.ibm.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION(IBMVFC_DRIVER_VERSION);

module_param_named(mq, mq_enabled, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(mq, "Enable multiqueue support. "
		 "[Default=" __stringअगरy(IBMVFC_MQ) "]");
module_param_named(scsi_host_queues, nr_scsi_hw_queues, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(scsi_host_queues, "Number of SCSI Host submission queues. "
		 "[Default=" __stringअगरy(IBMVFC_SCSI_HW_QUEUES) "]");
module_param_named(scsi_hw_channels, nr_scsi_channels, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(scsi_hw_channels, "Number of hw scsi channels to request. "
		 "[Default=" __stringअगरy(IBMVFC_SCSI_CHANNELS) "]");
module_param_named(mig_channels_only, mig_channels_only, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(mig_channels_only, "Prevent migration to non-channelized system. "
		 "[Default=" __stringअगरy(IBMVFC_MIG_NO_SUB_TO_CRQ) "]");
module_param_named(mig_no_less_channels, mig_no_less_channels, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(mig_no_less_channels, "Prevent migration to system with less channels. "
		 "[Default=" __stringअगरy(IBMVFC_MIG_NO_N_TO_M) "]");

module_param_named(init_समयout, init_समयout, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(init_समयout, "Initialization timeout in seconds. "
		 "[Default=" __stringअगरy(IBMVFC_INIT_TIMEOUT) "]");
module_param_named(शेष_समयout, शेष_समयout, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(शेष_समयout,
		 "Default timeout in seconds for initialization and EH commands. "
		 "[Default=" __stringअगरy(IBMVFC_DEFAULT_TIMEOUT) "]");
module_param_named(max_requests, max_requests, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_requests, "Maximum requests for this adapter. "
		 "[Default=" __stringअगरy(IBMVFC_MAX_REQUESTS_DEFAULT) "]");
module_param_named(max_lun, max_lun, ulदीर्घ, S_IRUGO);
MODULE_PARM_DESC(max_lun, "Maximum allowed LUN. "
		 "[Default=" __stringअगरy(IBMVFC_MAX_LUN) "]");
module_param_named(max_tarमाला_लो, max_tarमाला_लो, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_tarमाला_लो, "Maximum allowed targets. "
		 "[Default=" __stringअगरy(IBMVFC_MAX_TARGETS) "]");
module_param_named(disc_thपढ़ोs, disc_thपढ़ोs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(disc_thपढ़ोs, "Number of device discovery threads to use. "
		 "[Default=" __stringअगरy(IBMVFC_MAX_DISC_THREADS) "]");
module_param_named(debug, ibmvfc_debug, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Enable driver debug information. "
		 "[Default=" __stringअगरy(IBMVFC_DEBUG) "]");
module_param_named(log_level, log_level, uपूर्णांक, 0);
MODULE_PARM_DESC(log_level, "Set to 0 - 4 for increasing verbosity of device driver. "
		 "[Default=" __stringअगरy(IBMVFC_DEFAULT_LOG_LEVEL) "]");
module_param_named(cls3_error, cls3_error, uपूर्णांक, 0);
MODULE_PARM_DESC(cls3_error, "Enable FC Class 3 Error Recovery. "
		 "[Default=" __stringअगरy(IBMVFC_CLS3_ERROR) "]");

अटल स्थिर काष्ठा अणु
	u16 status;
	u16 error;
	u8 result;
	u8 retry;
	पूर्णांक log;
	अक्षर *name;
पूर्ण cmd_status [] = अणु
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_UNABLE_TO_ESTABLISH, DID_ERROR, 1, 1, "unable to establish" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_XPORT_FAULT, DID_OK, 1, 0, "transport fault" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_CMD_TIMEOUT, DID_TIME_OUT, 1, 1, "command timeout" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_ENETDOWN, DID_TRANSPORT_DISRUPTED, 1, 1, "network down" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_HW_FAILURE, DID_ERROR, 1, 1, "hardware failure" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_LINK_DOWN_ERR, DID_REQUEUE, 0, 0, "link down" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_LINK_DEAD_ERR, DID_ERROR, 0, 0, "link dead" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_UNABLE_TO_REGISTER, DID_ERROR, 1, 1, "unable to register" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_XPORT_BUSY, DID_BUS_BUSY, 1, 0, "transport busy" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_XPORT_DEAD, DID_ERROR, 0, 1, "transport dead" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_CONFIG_ERROR, DID_ERROR, 1, 1, "configuration error" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_NAME_SERVER_FAIL, DID_ERROR, 1, 1, "name server failure" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_LINK_HALTED, DID_REQUEUE, 1, 0, "link halted" पूर्ण,
	अणु IBMVFC_FABRIC_MAPPED, IBMVFC_XPORT_GENERAL, DID_OK, 1, 0, "general transport error" पूर्ण,

	अणु IBMVFC_VIOS_FAILURE, IBMVFC_CRQ_FAILURE, DID_REQUEUE, 1, 1, "CRQ failure" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_SW_FAILURE, DID_ERROR, 0, 1, "software failure" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_INVALID_PARAMETER, DID_ERROR, 0, 1, "invalid parameter" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_MISSING_PARAMETER, DID_ERROR, 0, 1, "missing parameter" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_HOST_IO_BUS, DID_ERROR, 1, 1, "host I/O bus failure" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_TRANS_CANCELLED, DID_ERROR, 0, 1, "transaction cancelled" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_TRANS_CANCELLED_IMPLICIT, DID_ERROR, 0, 1, "transaction cancelled implicit" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_INSUFFICIENT_RESOURCE, DID_REQUEUE, 1, 1, "insufficient resources" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_PLOGI_REQUIRED, DID_ERROR, 0, 1, "port login required" पूर्ण,
	अणु IBMVFC_VIOS_FAILURE, IBMVFC_COMMAND_FAILED, DID_ERROR, 1, 1, "command failed" पूर्ण,

	अणु IBMVFC_FC_FAILURE, IBMVFC_INVALID_ELS_CMD_CODE, DID_ERROR, 0, 1, "invalid ELS command code" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_INVALID_VERSION, DID_ERROR, 0, 1, "invalid version level" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_LOGICAL_ERROR, DID_ERROR, 1, 1, "logical error" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_INVALID_CT_IU_SIZE, DID_ERROR, 0, 1, "invalid CT_IU size" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_LOGICAL_BUSY, DID_REQUEUE, 1, 0, "logical busy" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_PROTOCOL_ERROR, DID_ERROR, 1, 1, "protocol error" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_UNABLE_TO_PERFORM_REQ, DID_ERROR, 1, 1, "unable to perform request" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_CMD_NOT_SUPPORTED, DID_ERROR, 0, 0, "command not supported" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_SERVER_NOT_AVAIL, DID_ERROR, 0, 1, "server not available" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_CMD_IN_PROGRESS, DID_ERROR, 0, 1, "command already in progress" पूर्ण,
	अणु IBMVFC_FC_FAILURE, IBMVFC_VENDOR_SPECIFIC, DID_ERROR, 1, 1, "vendor specific" पूर्ण,

	अणु IBMVFC_FC_SCSI_ERROR, 0, DID_OK, 1, 0, "SCSI error" पूर्ण,
	अणु IBMVFC_FC_SCSI_ERROR, IBMVFC_COMMAND_FAILED, DID_ERROR, 0, 1, "PRLI to device failed." पूर्ण,
पूर्ण;

अटल व्योम ibmvfc_npiv_login(काष्ठा ibmvfc_host *);
अटल व्योम ibmvfc_tgt_send_prli(काष्ठा ibmvfc_target *);
अटल व्योम ibmvfc_tgt_send_plogi(काष्ठा ibmvfc_target *);
अटल व्योम ibmvfc_tgt_query_target(काष्ठा ibmvfc_target *);
अटल व्योम ibmvfc_npiv_logout(काष्ठा ibmvfc_host *);
अटल व्योम ibmvfc_tgt_implicit_logout_and_del(काष्ठा ibmvfc_target *);
अटल व्योम ibmvfc_tgt_move_login(काष्ठा ibmvfc_target *);

अटल व्योम ibmvfc_release_sub_crqs(काष्ठा ibmvfc_host *);
अटल व्योम ibmvfc_init_sub_crqs(काष्ठा ibmvfc_host *);

अटल स्थिर अक्षर *unknown_error = "unknown error";

अटल दीर्घ h_reg_sub_crq(अचिन्हित दीर्घ unit_address, अचिन्हित दीर्घ ioba,
			  अचिन्हित दीर्घ length, अचिन्हित दीर्घ *cookie,
			  अचिन्हित दीर्घ *irq)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	rc = plpar_hcall(H_REG_SUB_CRQ, retbuf, unit_address, ioba, length);
	*cookie = retbuf[0];
	*irq = retbuf[1];

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvfc_check_caps(काष्ठा ibmvfc_host *vhost, अचिन्हित दीर्घ cap_flags)
अणु
	u64 host_caps = be64_to_cpu(vhost->login_buf->resp.capabilities);

	वापस (host_caps & cap_flags) ? 1 : 0;
पूर्ण

अटल काष्ठा ibmvfc_fcp_cmd_iu *ibmvfc_get_fcp_iu(काष्ठा ibmvfc_host *vhost,
						   काष्ठा ibmvfc_cmd *vfc_cmd)
अणु
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN))
		वापस &vfc_cmd->v2.iu;
	अन्यथा
		वापस &vfc_cmd->v1.iu;
पूर्ण

अटल काष्ठा ibmvfc_fcp_rsp *ibmvfc_get_fcp_rsp(काष्ठा ibmvfc_host *vhost,
						 काष्ठा ibmvfc_cmd *vfc_cmd)
अणु
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN))
		वापस &vfc_cmd->v2.rsp;
	अन्यथा
		वापस &vfc_cmd->v1.rsp;
पूर्ण

#अगर_घोषित CONFIG_SCSI_IBMVFC_TRACE
/**
 * ibmvfc_trc_start - Log a start trace entry
 * @evt:		ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_trc_start(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_cmd *vfc_cmd = &evt->iu.cmd;
	काष्ठा ibmvfc_mad_common *mad = &evt->iu.mad_common;
	काष्ठा ibmvfc_fcp_cmd_iu *iu = ibmvfc_get_fcp_iu(vhost, vfc_cmd);
	काष्ठा ibmvfc_trace_entry *entry;
	पूर्णांक index = atomic_inc_वापस(&vhost->trace_index) & IBMVFC_TRACE_INDEX_MASK;

	entry = &vhost->trace[index];
	entry->evt = evt;
	entry->समय = jअगरfies;
	entry->fmt = evt->crq.क्रमmat;
	entry->type = IBMVFC_TRC_START;

	चयन (entry->fmt) अणु
	हाल IBMVFC_CMD_FORMAT:
		entry->op_code = iu->cdb[0];
		entry->scsi_id = be64_to_cpu(vfc_cmd->tgt_scsi_id);
		entry->lun = scsilun_to_पूर्णांक(&iu->lun);
		entry->पंचांगf_flags = iu->पंचांगf_flags;
		entry->u.start.xfer_len = be32_to_cpu(iu->xfer_len);
		अवरोध;
	हाल IBMVFC_MAD_FORMAT:
		entry->op_code = be32_to_cpu(mad->opcode);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ibmvfc_trc_end - Log an end trace entry
 * @evt:		ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_trc_end(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_cmd *vfc_cmd = &evt->xfer_iu->cmd;
	काष्ठा ibmvfc_mad_common *mad = &evt->xfer_iu->mad_common;
	काष्ठा ibmvfc_fcp_cmd_iu *iu = ibmvfc_get_fcp_iu(vhost, vfc_cmd);
	काष्ठा ibmvfc_fcp_rsp *rsp = ibmvfc_get_fcp_rsp(vhost, vfc_cmd);
	काष्ठा ibmvfc_trace_entry *entry;
	पूर्णांक index = atomic_inc_वापस(&vhost->trace_index) & IBMVFC_TRACE_INDEX_MASK;

	entry = &vhost->trace[index];
	entry->evt = evt;
	entry->समय = jअगरfies;
	entry->fmt = evt->crq.क्रमmat;
	entry->type = IBMVFC_TRC_END;

	चयन (entry->fmt) अणु
	हाल IBMVFC_CMD_FORMAT:
		entry->op_code = iu->cdb[0];
		entry->scsi_id = be64_to_cpu(vfc_cmd->tgt_scsi_id);
		entry->lun = scsilun_to_पूर्णांक(&iu->lun);
		entry->पंचांगf_flags = iu->पंचांगf_flags;
		entry->u.end.status = be16_to_cpu(vfc_cmd->status);
		entry->u.end.error = be16_to_cpu(vfc_cmd->error);
		entry->u.end.fcp_rsp_flags = rsp->flags;
		entry->u.end.rsp_code = rsp->data.info.rsp_code;
		entry->u.end.scsi_status = rsp->scsi_status;
		अवरोध;
	हाल IBMVFC_MAD_FORMAT:
		entry->op_code = be32_to_cpu(mad->opcode);
		entry->u.end.status = be16_to_cpu(mad->status);
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण
पूर्ण

#अन्यथा
#घोषणा ibmvfc_trc_start(evt) करो अणु पूर्ण जबतक (0)
#घोषणा ibmvfc_trc_end(evt) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * ibmvfc_get_err_index - Find the index पूर्णांकo cmd_status क्रम the fcp response
 * @status:		status / error class
 * @error:		error
 *
 * Return value:
 *	index पूर्णांकo cmd_status / -EINVAL on failure
 **/
अटल पूर्णांक ibmvfc_get_err_index(u16 status, u16 error)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cmd_status); i++)
		अगर ((cmd_status[i].status & status) == cmd_status[i].status &&
		    cmd_status[i].error == error)
			वापस i;

	वापस -EINVAL;
पूर्ण

/**
 * ibmvfc_get_cmd_error - Find the error description क्रम the fcp response
 * @status:		status / error class
 * @error:		error
 *
 * Return value:
 *	error description string
 **/
अटल स्थिर अक्षर *ibmvfc_get_cmd_error(u16 status, u16 error)
अणु
	पूर्णांक rc = ibmvfc_get_err_index(status, error);
	अगर (rc >= 0)
		वापस cmd_status[rc].name;
	वापस unknown_error;
पूर्ण

/**
 * ibmvfc_get_err_result - Find the scsi status to वापस क्रम the fcp response
 * @vhost:      ibmvfc host काष्ठा
 * @vfc_cmd:	ibmvfc command काष्ठा
 *
 * Return value:
 *	SCSI result value to वापस क्रम completed command
 **/
अटल पूर्णांक ibmvfc_get_err_result(काष्ठा ibmvfc_host *vhost, काष्ठा ibmvfc_cmd *vfc_cmd)
अणु
	पूर्णांक err;
	काष्ठा ibmvfc_fcp_rsp *rsp = ibmvfc_get_fcp_rsp(vhost, vfc_cmd);
	पूर्णांक fc_rsp_len = be32_to_cpu(rsp->fcp_rsp_len);

	अगर ((rsp->flags & FCP_RSP_LEN_VALID) &&
	    ((fc_rsp_len && fc_rsp_len != 4 && fc_rsp_len != 8) ||
	     rsp->data.info.rsp_code))
		वापस DID_ERROR << 16;

	err = ibmvfc_get_err_index(be16_to_cpu(vfc_cmd->status), be16_to_cpu(vfc_cmd->error));
	अगर (err >= 0)
		वापस rsp->scsi_status | (cmd_status[err].result << 16);
	वापस rsp->scsi_status | (DID_ERROR << 16);
पूर्ण

/**
 * ibmvfc_retry_cmd - Determine अगर error status is retryable
 * @status:		status / error class
 * @error:		error
 *
 * Return value:
 *	1 अगर error should be retried / 0 अगर it should not
 **/
अटल पूर्णांक ibmvfc_retry_cmd(u16 status, u16 error)
अणु
	पूर्णांक rc = ibmvfc_get_err_index(status, error);

	अगर (rc >= 0)
		वापस cmd_status[rc].retry;
	वापस 1;
पूर्ण

अटल स्थिर अक्षर *unknown_fc_explain = "unknown fc explain";

अटल स्थिर काष्ठा अणु
	u16 fc_explain;
	अक्षर *name;
पूर्ण ls_explain [] = अणु
	अणु 0x00, "no additional explanation" पूर्ण,
	अणु 0x01, "service parameter error - options" पूर्ण,
	अणु 0x03, "service parameter error - initiator control" पूर्ण,
	अणु 0x05, "service parameter error - recipient control" पूर्ण,
	अणु 0x07, "service parameter error - received data field size" पूर्ण,
	अणु 0x09, "service parameter error - concurrent seq" पूर्ण,
	अणु 0x0B, "service parameter error - credit" पूर्ण,
	अणु 0x0D, "invalid N_Port/F_Port_Name" पूर्ण,
	अणु 0x0E, "invalid node/Fabric Name" पूर्ण,
	अणु 0x0F, "invalid common service parameters" पूर्ण,
	अणु 0x11, "invalid association header" पूर्ण,
	अणु 0x13, "association header required" पूर्ण,
	अणु 0x15, "invalid originator S_ID" पूर्ण,
	अणु 0x17, "invalid OX_ID-RX-ID combination" पूर्ण,
	अणु 0x19, "command (request) already in progress" पूर्ण,
	अणु 0x1E, "N_Port Login requested" पूर्ण,
	अणु 0x1F, "Invalid N_Port_ID" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u16 fc_explain;
	अक्षर *name;
पूर्ण gs_explain [] = अणु
	अणु 0x00, "no additional explanation" पूर्ण,
	अणु 0x01, "port identifier not registered" पूर्ण,
	अणु 0x02, "port name not registered" पूर्ण,
	अणु 0x03, "node name not registered" पूर्ण,
	अणु 0x04, "class of service not registered" पूर्ण,
	अणु 0x06, "initial process associator not registered" पूर्ण,
	अणु 0x07, "FC-4 TYPEs not registered" पूर्ण,
	अणु 0x08, "symbolic port name not registered" पूर्ण,
	अणु 0x09, "symbolic node name not registered" पूर्ण,
	अणु 0x0A, "port type not registered" पूर्ण,
	अणु 0xF0, "authorization exception" पूर्ण,
	अणु 0xF1, "authentication exception" पूर्ण,
	अणु 0xF2, "data base full" पूर्ण,
	अणु 0xF3, "data base empty" पूर्ण,
	अणु 0xF4, "processing request" पूर्ण,
	अणु 0xF5, "unable to verify connection" पूर्ण,
	अणु 0xF6, "devices not in a common zone" पूर्ण,
पूर्ण;

/**
 * ibmvfc_get_ls_explain - Return the FC Explain description text
 * @status:	FC Explain status
 *
 * Returns:
 *	error string
 **/
अटल स्थिर अक्षर *ibmvfc_get_ls_explain(u16 status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ls_explain); i++)
		अगर (ls_explain[i].fc_explain == status)
			वापस ls_explain[i].name;

	वापस unknown_fc_explain;
पूर्ण

/**
 * ibmvfc_get_gs_explain - Return the FC Explain description text
 * @status:	FC Explain status
 *
 * Returns:
 *	error string
 **/
अटल स्थिर अक्षर *ibmvfc_get_gs_explain(u16 status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gs_explain); i++)
		अगर (gs_explain[i].fc_explain == status)
			वापस gs_explain[i].name;

	वापस unknown_fc_explain;
पूर्ण

अटल स्थिर काष्ठा अणु
	क्रमागत ibmvfc_fc_type fc_type;
	अक्षर *name;
पूर्ण fc_type [] = अणु
	अणु IBMVFC_FABRIC_REJECT, "fabric reject" पूर्ण,
	अणु IBMVFC_PORT_REJECT, "port reject" पूर्ण,
	अणु IBMVFC_LS_REJECT, "ELS reject" पूर्ण,
	अणु IBMVFC_FABRIC_BUSY, "fabric busy" पूर्ण,
	अणु IBMVFC_PORT_BUSY, "port busy" पूर्ण,
	अणु IBMVFC_BASIC_REJECT, "basic reject" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *unknown_fc_type = "unknown fc type";

/**
 * ibmvfc_get_fc_type - Return the FC Type description text
 * @status:	FC Type error status
 *
 * Returns:
 *	error string
 **/
अटल स्थिर अक्षर *ibmvfc_get_fc_type(u16 status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fc_type); i++)
		अगर (fc_type[i].fc_type == status)
			वापस fc_type[i].name;

	वापस unknown_fc_type;
पूर्ण

/**
 * ibmvfc_set_tgt_action - Set the next init action क्रम the target
 * @tgt:		ibmvfc target काष्ठा
 * @action:		action to perक्रमm
 *
 * Returns:
 *	0 अगर action changed / non-zero अगर not changed
 **/
अटल पूर्णांक ibmvfc_set_tgt_action(काष्ठा ibmvfc_target *tgt,
				  क्रमागत ibmvfc_target_action action)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (tgt->action) अणु
	हाल IBMVFC_TGT_ACTION_LOGOUT_RPORT:
		अगर (action == IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT ||
		    action == IBMVFC_TGT_ACTION_DEL_RPORT) अणु
			tgt->action = action;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT:
		अगर (action == IBMVFC_TGT_ACTION_DEL_RPORT ||
		    action == IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT) अणु
			tgt->action = action;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT:
		अगर (action == IBMVFC_TGT_ACTION_LOGOUT_RPORT) अणु
			tgt->action = action;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT:
		अगर (action == IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT) अणु
			tgt->action = action;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल IBMVFC_TGT_ACTION_DEL_RPORT:
		अगर (action == IBMVFC_TGT_ACTION_DELETED_RPORT) अणु
			tgt->action = action;
			rc = 0;
		पूर्ण
		अवरोध;
	हाल IBMVFC_TGT_ACTION_DELETED_RPORT:
		अवरोध;
	शेष:
		tgt->action = action;
		rc = 0;
		अवरोध;
	पूर्ण

	अगर (action >= IBMVFC_TGT_ACTION_LOGOUT_RPORT)
		tgt->add_rport = 0;

	वापस rc;
पूर्ण

/**
 * ibmvfc_set_host_state - Set the state क्रम the host
 * @vhost:		ibmvfc host काष्ठा
 * @state:		state to set host to
 *
 * Returns:
 *	0 अगर state changed / non-zero अगर not changed
 **/
अटल पूर्णांक ibmvfc_set_host_state(काष्ठा ibmvfc_host *vhost,
				  क्रमागत ibmvfc_host_state state)
अणु
	पूर्णांक rc = 0;

	चयन (vhost->state) अणु
	हाल IBMVFC_HOST_OFFLINE:
		rc = -EINVAL;
		अवरोध;
	शेष:
		vhost->state = state;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ibmvfc_set_host_action - Set the next init action क्रम the host
 * @vhost:		ibmvfc host काष्ठा
 * @action:		action to perक्रमm
 *
 **/
अटल व्योम ibmvfc_set_host_action(काष्ठा ibmvfc_host *vhost,
				   क्रमागत ibmvfc_host_action action)
अणु
	चयन (action) अणु
	हाल IBMVFC_HOST_ACTION_ALLOC_TGTS:
		अगर (vhost->action == IBMVFC_HOST_ACTION_INIT_WAIT)
			vhost->action = action;
		अवरोध;
	हाल IBMVFC_HOST_ACTION_LOGO_WAIT:
		अगर (vhost->action == IBMVFC_HOST_ACTION_LOGO)
			vhost->action = action;
		अवरोध;
	हाल IBMVFC_HOST_ACTION_INIT_WAIT:
		अगर (vhost->action == IBMVFC_HOST_ACTION_INIT)
			vhost->action = action;
		अवरोध;
	हाल IBMVFC_HOST_ACTION_QUERY:
		चयन (vhost->action) अणु
		हाल IBMVFC_HOST_ACTION_INIT_WAIT:
		हाल IBMVFC_HOST_ACTION_NONE:
		हाल IBMVFC_HOST_ACTION_TGT_DEL_FAILED:
			vhost->action = action;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IBMVFC_HOST_ACTION_TGT_INIT:
		अगर (vhost->action == IBMVFC_HOST_ACTION_ALLOC_TGTS)
			vhost->action = action;
		अवरोध;
	हाल IBMVFC_HOST_ACTION_REENABLE:
	हाल IBMVFC_HOST_ACTION_RESET:
		vhost->action = action;
		अवरोध;
	हाल IBMVFC_HOST_ACTION_INIT:
	हाल IBMVFC_HOST_ACTION_TGT_DEL:
	हाल IBMVFC_HOST_ACTION_LOGO:
	हाल IBMVFC_HOST_ACTION_QUERY_TGTS:
	हाल IBMVFC_HOST_ACTION_TGT_DEL_FAILED:
	हाल IBMVFC_HOST_ACTION_NONE:
	शेष:
		चयन (vhost->action) अणु
		हाल IBMVFC_HOST_ACTION_RESET:
		हाल IBMVFC_HOST_ACTION_REENABLE:
			अवरोध;
		शेष:
			vhost->action = action;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ibmvfc_reinit_host - Re-start host initialization (no NPIV Login)
 * @vhost:		ibmvfc host काष्ठा
 *
 * Return value:
 *	nothing
 **/
अटल व्योम ibmvfc_reinit_host(काष्ठा ibmvfc_host *vhost)
अणु
	अगर (vhost->action == IBMVFC_HOST_ACTION_NONE &&
	    vhost->state == IBMVFC_ACTIVE) अणु
		अगर (!ibmvfc_set_host_state(vhost, IBMVFC_INITIALIZING)) अणु
			scsi_block_requests(vhost->host);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY);
		पूर्ण
	पूर्ण अन्यथा
		vhost->reinit = 1;

	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_del_tgt - Schedule cleanup and removal of the target
 * @tgt:		ibmvfc target काष्ठा
 **/
अटल व्योम ibmvfc_del_tgt(काष्ठा ibmvfc_target *tgt)
अणु
	अगर (!ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_LOGOUT_RPORT))
		tgt->job_step = ibmvfc_tgt_implicit_logout_and_del;
	wake_up(&tgt->vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_link_करोwn - Handle a link करोwn event from the adapter
 * @vhost:	ibmvfc host काष्ठा
 * @state:	ibmvfc host state to enter
 *
 **/
अटल व्योम ibmvfc_link_करोwn(काष्ठा ibmvfc_host *vhost,
			     क्रमागत ibmvfc_host_state state)
अणु
	काष्ठा ibmvfc_target *tgt;

	ENTER;
	scsi_block_requests(vhost->host);
	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
		ibmvfc_del_tgt(tgt);
	ibmvfc_set_host_state(vhost, state);
	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_TGT_DEL);
	vhost->events_to_log |= IBMVFC_AE_LINKDOWN;
	wake_up(&vhost->work_रुको_q);
	LEAVE;
पूर्ण

/**
 * ibmvfc_init_host - Start host initialization
 * @vhost:		ibmvfc host काष्ठा
 *
 * Return value:
 *	nothing
 **/
अटल व्योम ibmvfc_init_host(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_target *tgt;

	अगर (vhost->action == IBMVFC_HOST_ACTION_INIT_WAIT) अणु
		अगर (++vhost->init_retries > IBMVFC_MAX_HOST_INIT_RETRIES) अणु
			dev_err(vhost->dev,
				"Host initialization retries exceeded. Taking adapter offline\n");
			ibmvfc_link_करोwn(vhost, IBMVFC_HOST_OFFLINE);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!ibmvfc_set_host_state(vhost, IBMVFC_INITIALIZING)) अणु
		स_रखो(vhost->async_crq.msgs.async, 0, PAGE_SIZE);
		vhost->async_crq.cur = 0;

		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			ibmvfc_del_tgt(tgt);
		scsi_block_requests(vhost->host);
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT);
		vhost->job_step = ibmvfc_npiv_login;
		wake_up(&vhost->work_रुको_q);
	पूर्ण
पूर्ण

/**
 * ibmvfc_send_crq - Send a CRQ
 * @vhost:	ibmvfc host काष्ठा
 * @word1:	the first 64 bits of the data
 * @word2:	the second 64 bits of the data
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_send_crq(काष्ठा ibmvfc_host *vhost, u64 word1, u64 word2)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);
	वापस plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, word1, word2);
पूर्ण

अटल पूर्णांक ibmvfc_send_sub_crq(काष्ठा ibmvfc_host *vhost, u64 cookie, u64 word1,
			       u64 word2, u64 word3, u64 word4)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);

	वापस plpar_hcall_norets(H_SEND_SUB_CRQ, vdev->unit_address, cookie,
				  word1, word2, word3, word4);
पूर्ण

/**
 * ibmvfc_send_crq_init - Send a CRQ init message
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_send_crq_init(काष्ठा ibmvfc_host *vhost)
अणु
	ibmvfc_dbg(vhost, "Sending CRQ init\n");
	वापस ibmvfc_send_crq(vhost, 0xC001000000000000LL, 0);
पूर्ण

/**
 * ibmvfc_send_crq_init_complete - Send a CRQ init complete message
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_send_crq_init_complete(काष्ठा ibmvfc_host *vhost)
अणु
	ibmvfc_dbg(vhost, "Sending CRQ init complete\n");
	वापस ibmvfc_send_crq(vhost, 0xC002000000000000LL, 0);
पूर्ण

/**
 * ibmvfc_init_event_pool - Allocates and initializes the event pool क्रम a host
 * @vhost:	ibmvfc host who owns the event pool
 * @queue:      ibmvfc queue काष्ठा
 * @size:       pool size
 *
 * Returns zero on success.
 **/
अटल पूर्णांक ibmvfc_init_event_pool(काष्ठा ibmvfc_host *vhost,
				  काष्ठा ibmvfc_queue *queue,
				  अचिन्हित पूर्णांक size)
अणु
	पूर्णांक i;
	काष्ठा ibmvfc_event_pool *pool = &queue->evt_pool;

	ENTER;
	अगर (!size)
		वापस 0;

	pool->size = size;
	pool->events = kसुस्मृति(size, माप(*pool->events), GFP_KERNEL);
	अगर (!pool->events)
		वापस -ENOMEM;

	pool->iu_storage = dma_alloc_coherent(vhost->dev,
					      size * माप(*pool->iu_storage),
					      &pool->iu_token, 0);

	अगर (!pool->iu_storage) अणु
		kमुक्त(pool->events);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&queue->sent);
	INIT_LIST_HEAD(&queue->मुक्त);
	spin_lock_init(&queue->l_lock);

	क्रम (i = 0; i < size; ++i) अणु
		काष्ठा ibmvfc_event *evt = &pool->events[i];

		atomic_set(&evt->मुक्त, 1);
		evt->crq.valid = 0x80;
		evt->crq.ioba = cpu_to_be64(pool->iu_token + (माप(*evt->xfer_iu) * i));
		evt->xfer_iu = pool->iu_storage + i;
		evt->vhost = vhost;
		evt->queue = queue;
		evt->ext_list = शून्य;
		list_add_tail(&evt->queue_list, &queue->मुक्त);
	पूर्ण

	LEAVE;
	वापस 0;
पूर्ण

/**
 * ibmvfc_मुक्त_event_pool - Frees memory of the event pool of a host
 * @vhost:	ibmvfc host who owns the event pool
 * @queue:      ibmvfc queue काष्ठा
 *
 **/
अटल व्योम ibmvfc_मुक्त_event_pool(काष्ठा ibmvfc_host *vhost,
				   काष्ठा ibmvfc_queue *queue)
अणु
	पूर्णांक i;
	काष्ठा ibmvfc_event_pool *pool = &queue->evt_pool;

	ENTER;
	क्रम (i = 0; i < pool->size; ++i) अणु
		list_del(&pool->events[i].queue_list);
		BUG_ON(atomic_पढ़ो(&pool->events[i].मुक्त) != 1);
		अगर (pool->events[i].ext_list)
			dma_pool_मुक्त(vhost->sg_pool,
				      pool->events[i].ext_list,
				      pool->events[i].ext_list_token);
	पूर्ण

	kमुक्त(pool->events);
	dma_मुक्त_coherent(vhost->dev,
			  pool->size * माप(*pool->iu_storage),
			  pool->iu_storage, pool->iu_token);
	LEAVE;
पूर्ण

/**
 * ibmvfc_मुक्त_queue - Deallocate queue
 * @vhost:	ibmvfc host काष्ठा
 * @queue:	ibmvfc queue काष्ठा
 *
 * Unmaps dma and deallocates page क्रम messages
 **/
अटल व्योम ibmvfc_मुक्त_queue(काष्ठा ibmvfc_host *vhost,
			      काष्ठा ibmvfc_queue *queue)
अणु
	काष्ठा device *dev = vhost->dev;

	dma_unmap_single(dev, queue->msg_token, PAGE_SIZE, DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)queue->msgs.handle);
	queue->msgs.handle = शून्य;

	ibmvfc_मुक्त_event_pool(vhost, queue);
पूर्ण

/**
 * ibmvfc_release_crq_queue - Deallocates data and unरेजिस्टरs CRQ
 * @vhost:	ibmvfc host काष्ठा
 *
 * Frees irq, deallocates a page क्रम messages, unmaps dma, and unरेजिस्टरs
 * the crq with the hypervisor.
 **/
अटल व्योम ibmvfc_release_crq_queue(काष्ठा ibmvfc_host *vhost)
अणु
	दीर्घ rc = 0;
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);
	काष्ठा ibmvfc_queue *crq = &vhost->crq;

	ibmvfc_dbg(vhost, "Releasing CRQ\n");
	मुक्त_irq(vdev->irq, vhost);
	tasklet_समाप्त(&vhost->tasklet);
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	vhost->state = IBMVFC_NO_CRQ;
	vhost->logged_in = 0;

	ibmvfc_मुक्त_queue(vhost, crq);
पूर्ण

/**
 * ibmvfc_reenable_crq_queue - reenables the CRQ
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_reenable_crq_queue(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक rc = 0;
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);
	अचिन्हित दीर्घ flags;

	ibmvfc_release_sub_crqs(vhost);

	/* Re-enable the CRQ */
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_ENABLE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_IN_PROGRESS || rc == H_BUSY || H_IS_LONG_BUSY(rc));

	अगर (rc)
		dev_err(vhost->dev, "Error enabling adapter (rc=%d)\n", rc);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	spin_lock(vhost->crq.q_lock);
	vhost->करो_enquiry = 1;
	vhost->using_channels = 0;
	spin_unlock(vhost->crq.q_lock);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	ibmvfc_init_sub_crqs(vhost);

	वापस rc;
पूर्ण

/**
 * ibmvfc_reset_crq - resets a crq after a failure
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_reset_crq(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);
	काष्ठा ibmvfc_queue *crq = &vhost->crq;

	ibmvfc_release_sub_crqs(vhost);

	/* Close the CRQ */
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	spin_lock_irqsave(vhost->host->host_lock, flags);
	spin_lock(vhost->crq.q_lock);
	vhost->state = IBMVFC_NO_CRQ;
	vhost->logged_in = 0;
	vhost->करो_enquiry = 1;
	vhost->using_channels = 0;

	/* Clean out the queue */
	स_रखो(crq->msgs.crq, 0, PAGE_SIZE);
	crq->cur = 0;

	/* And re-खोलो it again */
	rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
				crq->msg_token, PAGE_SIZE);

	अगर (rc == H_CLOSED)
		/* Adapter is good, but other end is not पढ़ोy */
		dev_warn(vhost->dev, "Partner adapter not ready\n");
	अन्यथा अगर (rc != 0)
		dev_warn(vhost->dev, "Couldn't register crq (rc=%d)\n", rc);

	spin_unlock(vhost->crq.q_lock);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	ibmvfc_init_sub_crqs(vhost);

	वापस rc;
पूर्ण

/**
 * ibmvfc_valid_event - Determines अगर event is valid.
 * @pool:	event_pool that contains the event
 * @evt:	ibmvfc event to be checked क्रम validity
 *
 * Return value:
 *	1 अगर event is valid / 0 अगर event is not valid
 **/
अटल पूर्णांक ibmvfc_valid_event(काष्ठा ibmvfc_event_pool *pool,
			      काष्ठा ibmvfc_event *evt)
अणु
	पूर्णांक index = evt - pool->events;
	अगर (index < 0 || index >= pool->size)	/* outside of bounds */
		वापस 0;
	अगर (evt != pool->events + index)	/* unaligned */
		वापस 0;
	वापस 1;
पूर्ण

/**
 * ibmvfc_मुक्त_event - Free the specअगरied event
 * @evt:	ibmvfc_event to be मुक्तd
 *
 **/
अटल व्योम ibmvfc_मुक्त_event(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_event_pool *pool = &evt->queue->evt_pool;
	अचिन्हित दीर्घ flags;

	BUG_ON(!ibmvfc_valid_event(pool, evt));
	BUG_ON(atomic_inc_वापस(&evt->मुक्त) != 1);

	spin_lock_irqsave(&evt->queue->l_lock, flags);
	list_add_tail(&evt->queue_list, &evt->queue->मुक्त);
	अगर (evt->eh_comp)
		complete(evt->eh_comp);
	spin_unlock_irqrestore(&evt->queue->l_lock, flags);
पूर्ण

/**
 * ibmvfc_scsi_eh_करोne - EH करोne function क्रम queuecommand commands
 * @evt:	ibmvfc event काष्ठा
 *
 * This function करोes not setup any error status, that must be करोne
 * beक्रमe this function माला_लो called.
 **/
अटल व्योम ibmvfc_scsi_eh_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा scsi_cmnd *cmnd = evt->cmnd;

	अगर (cmnd) अणु
		scsi_dma_unmap(cmnd);
		cmnd->scsi_करोne(cmnd);
	पूर्ण

	ibmvfc_मुक्त_event(evt);
पूर्ण

/**
 * ibmvfc_complete_purge - Complete failed command list
 * @purge_list:		list head of failed commands
 *
 * This function runs completions on commands to fail as a result of a
 * host reset or platक्रमm migration.
 **/
अटल व्योम ibmvfc_complete_purge(काष्ठा list_head *purge_list)
अणु
	काष्ठा ibmvfc_event *evt, *pos;

	list_क्रम_each_entry_safe(evt, pos, purge_list, queue_list) अणु
		list_del(&evt->queue_list);
		ibmvfc_trc_end(evt);
		evt->करोne(evt);
	पूर्ण
पूर्ण

/**
 * ibmvfc_fail_request - Fail request with specअगरied error code
 * @evt:		ibmvfc event काष्ठा
 * @error_code:	error code to fail request with
 *
 * Return value:
 *	none
 **/
अटल व्योम ibmvfc_fail_request(काष्ठा ibmvfc_event *evt, पूर्णांक error_code)
अणु
	अगर (evt->cmnd) अणु
		evt->cmnd->result = (error_code << 16);
		evt->करोne = ibmvfc_scsi_eh_करोne;
	पूर्ण अन्यथा
		evt->xfer_iu->mad_common.status = cpu_to_be16(IBMVFC_MAD_DRIVER_FAILED);

	del_समयr(&evt->समयr);
पूर्ण

/**
 * ibmvfc_purge_requests - Our भव adapter just shut करोwn. Purge any sent requests
 * @vhost:		ibmvfc host काष्ठा
 * @error_code:	error code to fail requests with
 *
 * Return value:
 *	none
 **/
अटल व्योम ibmvfc_purge_requests(काष्ठा ibmvfc_host *vhost, पूर्णांक error_code)
अणु
	काष्ठा ibmvfc_event *evt, *pos;
	काष्ठा ibmvfc_queue *queues = vhost->scsi_scrqs.scrqs;
	अचिन्हित दीर्घ flags;
	पूर्णांक hwqs = 0;
	पूर्णांक i;

	अगर (vhost->using_channels)
		hwqs = vhost->scsi_scrqs.active_queues;

	ibmvfc_dbg(vhost, "Purging all requests\n");
	spin_lock_irqsave(&vhost->crq.l_lock, flags);
	list_क्रम_each_entry_safe(evt, pos, &vhost->crq.sent, queue_list)
		ibmvfc_fail_request(evt, error_code);
	list_splice_init(&vhost->crq.sent, &vhost->purge);
	spin_unlock_irqrestore(&vhost->crq.l_lock, flags);

	क्रम (i = 0; i < hwqs; i++) अणु
		spin_lock_irqsave(queues[i].q_lock, flags);
		spin_lock(&queues[i].l_lock);
		list_क्रम_each_entry_safe(evt, pos, &queues[i].sent, queue_list)
			ibmvfc_fail_request(evt, error_code);
		list_splice_init(&queues[i].sent, &vhost->purge);
		spin_unlock(&queues[i].l_lock);
		spin_unlock_irqrestore(queues[i].q_lock, flags);
	पूर्ण
पूर्ण

/**
 * ibmvfc_hard_reset_host - Reset the connection to the server by अवरोधing the CRQ
 * @vhost:	काष्ठा ibmvfc host to reset
 **/
अटल व्योम ibmvfc_hard_reset_host(काष्ठा ibmvfc_host *vhost)
अणु
	ibmvfc_purge_requests(vhost, DID_ERROR);
	ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_RESET);
पूर्ण

/**
 * __ibmvfc_reset_host - Reset the connection to the server (no locking)
 * @vhost:	काष्ठा ibmvfc host to reset
 **/
अटल व्योम __ibmvfc_reset_host(काष्ठा ibmvfc_host *vhost)
अणु
	अगर (vhost->logged_in && vhost->action != IBMVFC_HOST_ACTION_LOGO_WAIT &&
	    !ibmvfc_set_host_state(vhost, IBMVFC_INITIALIZING)) अणु
		scsi_block_requests(vhost->host);
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_LOGO);
		vhost->job_step = ibmvfc_npiv_logout;
		wake_up(&vhost->work_रुको_q);
	पूर्ण अन्यथा
		ibmvfc_hard_reset_host(vhost);
पूर्ण

/**
 * ibmvfc_reset_host - Reset the connection to the server
 * @vhost:	ibmvfc host काष्ठा
 **/
अटल व्योम ibmvfc_reset_host(काष्ठा ibmvfc_host *vhost)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	__ibmvfc_reset_host(vhost);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_retry_host_init - Retry host initialization अगर allowed
 * @vhost:	ibmvfc host काष्ठा
 *
 * Returns: 1 अगर init will be retried / 0 अगर not
 *
 **/
अटल पूर्णांक ibmvfc_retry_host_init(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक retry = 0;

	अगर (vhost->action == IBMVFC_HOST_ACTION_INIT_WAIT) अणु
		vhost->delay_init = 1;
		अगर (++vhost->init_retries > IBMVFC_MAX_HOST_INIT_RETRIES) अणु
			dev_err(vhost->dev,
				"Host initialization retries exceeded. Taking adapter offline\n");
			ibmvfc_link_करोwn(vhost, IBMVFC_HOST_OFFLINE);
		पूर्ण अन्यथा अगर (vhost->init_retries == IBMVFC_MAX_HOST_INIT_RETRIES)
			__ibmvfc_reset_host(vhost);
		अन्यथा अणु
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT);
			retry = 1;
		पूर्ण
	पूर्ण

	wake_up(&vhost->work_रुको_q);
	वापस retry;
पूर्ण

/**
 * __ibmvfc_get_target - Find the specअगरied scsi_target (no locking)
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 *	ibmvfc_target काष्ठा / शून्य अगर not found
 **/
अटल काष्ठा ibmvfc_target *__ibmvfc_get_target(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	काष्ठा ibmvfc_target *tgt;

	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
		अगर (tgt->target_id == starget->id) अणु
			kref_get(&tgt->kref);
			वापस tgt;
		पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ibmvfc_get_target - Find the specअगरied scsi_target
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 *	ibmvfc_target काष्ठा / शून्य अगर not found
 **/
अटल काष्ठा ibmvfc_target *ibmvfc_get_target(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ibmvfc_target *tgt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	tgt = __ibmvfc_get_target(starget);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस tgt;
पूर्ण

/**
 * ibmvfc_get_host_speed - Get host port speed
 * @shost:		scsi host काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (vhost->state == IBMVFC_ACTIVE) अणु
		चयन (be64_to_cpu(vhost->login_buf->resp.link_speed) / 100) अणु
		हाल 1:
			fc_host_speed(shost) = FC_PORTSPEED_1GBIT;
			अवरोध;
		हाल 2:
			fc_host_speed(shost) = FC_PORTSPEED_2GBIT;
			अवरोध;
		हाल 4:
			fc_host_speed(shost) = FC_PORTSPEED_4GBIT;
			अवरोध;
		हाल 8:
			fc_host_speed(shost) = FC_PORTSPEED_8GBIT;
			अवरोध;
		हाल 10:
			fc_host_speed(shost) = FC_PORTSPEED_10GBIT;
			अवरोध;
		हाल 16:
			fc_host_speed(shost) = FC_PORTSPEED_16GBIT;
			अवरोध;
		शेष:
			ibmvfc_log(vhost, 3, "Unknown port speed: %lld Gbit\n",
				   be64_to_cpu(vhost->login_buf->resp.link_speed) / 100);
			fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * ibmvfc_get_host_port_state - Get host port state
 * @shost:		scsi host काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	चयन (vhost->state) अणु
	हाल IBMVFC_INITIALIZING:
	हाल IBMVFC_ACTIVE:
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
		अवरोध;
	हाल IBMVFC_LINK_DOWN:
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		अवरोध;
	हाल IBMVFC_LINK_DEAD:
	हाल IBMVFC_HOST_OFFLINE:
		fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
		अवरोध;
	हाल IBMVFC_HALTED:
		fc_host_port_state(shost) = FC_PORTSTATE_BLOCKED;
		अवरोध;
	हाल IBMVFC_NO_CRQ:
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
		अवरोध;
	शेष:
		ibmvfc_log(vhost, 3, "Unknown port state: %d\n", vhost->state);
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);
पूर्ण

/**
 * ibmvfc_set_rport_dev_loss_पंचांगo - Set rport's device loss समयout
 * @rport:		rport काष्ठा
 * @समयout:	समयout value
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_set_rport_dev_loss_पंचांगo(काष्ठा fc_rport *rport, u32 समयout)
अणु
	अगर (समयout)
		rport->dev_loss_पंचांगo = समयout;
	अन्यथा
		rport->dev_loss_पंचांगo = 1;
पूर्ण

/**
 * ibmvfc_release_tgt - Free memory allocated क्रम a target
 * @kref:		kref काष्ठा
 *
 **/
अटल व्योम ibmvfc_release_tgt(काष्ठा kref *kref)
अणु
	काष्ठा ibmvfc_target *tgt = container_of(kref, काष्ठा ibmvfc_target, kref);
	kमुक्त(tgt);
पूर्ण

/**
 * ibmvfc_get_starget_node_name - Get SCSI target's node name
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_get_starget_node_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा ibmvfc_target *tgt = ibmvfc_get_target(starget);
	fc_starget_port_name(starget) = tgt ? tgt->ids.node_name : 0;
	अगर (tgt)
		kref_put(&tgt->kref, ibmvfc_release_tgt);
पूर्ण

/**
 * ibmvfc_get_starget_port_name - Get SCSI target's port name
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_get_starget_port_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा ibmvfc_target *tgt = ibmvfc_get_target(starget);
	fc_starget_port_name(starget) = tgt ? tgt->ids.port_name : 0;
	अगर (tgt)
		kref_put(&tgt->kref, ibmvfc_release_tgt);
पूर्ण

/**
 * ibmvfc_get_starget_port_id - Get SCSI target's port ID
 * @starget:	scsi target काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_get_starget_port_id(काष्ठा scsi_target *starget)
अणु
	काष्ठा ibmvfc_target *tgt = ibmvfc_get_target(starget);
	fc_starget_port_id(starget) = tgt ? tgt->scsi_id : -1;
	अगर (tgt)
		kref_put(&tgt->kref, ibmvfc_release_tgt);
पूर्ण

/**
 * ibmvfc_रुको_जबतक_resetting - Wait जबतक the host resets
 * @vhost:		ibmvfc host काष्ठा
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_रुको_जबतक_resetting(काष्ठा ibmvfc_host *vhost)
अणु
	दीर्घ समयout = रुको_event_समयout(vhost->init_रुको_q,
					  ((vhost->state == IBMVFC_ACTIVE ||
					    vhost->state == IBMVFC_HOST_OFFLINE ||
					    vhost->state == IBMVFC_LINK_DEAD) &&
					   vhost->action == IBMVFC_HOST_ACTION_NONE),
					  (init_समयout * HZ));

	वापस समयout ? 0 : -EIO;
पूर्ण

/**
 * ibmvfc_issue_fc_host_lip - Re-initiate link initialization
 * @shost:		scsi host काष्ठा
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_issue_fc_host_lip(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);

	dev_err(vhost->dev, "Initiating host LIP. Resetting connection\n");
	ibmvfc_reset_host(vhost);
	वापस ibmvfc_रुको_जबतक_resetting(vhost);
पूर्ण

/**
 * ibmvfc_gather_partition_info - Gather info about the LPAR
 * @vhost:      ibmvfc host काष्ठा
 *
 * Return value:
 *	none
 **/
अटल व्योम ibmvfc_gather_partition_info(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा device_node *rootdn;
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *num;

	rootdn = of_find_node_by_path("/");
	अगर (!rootdn)
		वापस;

	name = of_get_property(rootdn, "ibm,partition-name", शून्य);
	अगर (name)
		म_नकलन(vhost->partition_name, name, माप(vhost->partition_name));
	num = of_get_property(rootdn, "ibm,partition-no", शून्य);
	अगर (num)
		vhost->partition_number = *num;
	of_node_put(rootdn);
पूर्ण

/**
 * ibmvfc_set_login_info - Setup info क्रम NPIV login
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 *	none
 **/
अटल व्योम ibmvfc_set_login_info(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_npiv_login *login_info = &vhost->login_info;
	काष्ठा ibmvfc_queue *async_crq = &vhost->async_crq;
	काष्ठा device_node *of_node = vhost->dev->of_node;
	स्थिर अक्षर *location;

	स_रखो(login_info, 0, माप(*login_info));

	login_info->ostype = cpu_to_be32(IBMVFC_OS_LINUX);
	login_info->max_dma_len = cpu_to_be64(IBMVFC_MAX_SECTORS << 9);
	login_info->max_payload = cpu_to_be32(माप(काष्ठा ibmvfc_fcp_cmd_iu));
	login_info->max_response = cpu_to_be32(माप(काष्ठा ibmvfc_fcp_rsp));
	login_info->partition_num = cpu_to_be32(vhost->partition_number);
	login_info->vfc_frame_version = cpu_to_be32(1);
	login_info->fcp_version = cpu_to_be16(3);
	login_info->flags = cpu_to_be16(IBMVFC_FLUSH_ON_HALT);
	अगर (vhost->client_migrated)
		login_info->flags |= cpu_to_be16(IBMVFC_CLIENT_MIGRATED);

	login_info->max_cmds = cpu_to_be32(max_requests + IBMVFC_NUM_INTERNAL_REQ);
	login_info->capabilities = cpu_to_be64(IBMVFC_CAN_MIGRATE | IBMVFC_CAN_SEND_VF_WWPN);

	अगर (vhost->mq_enabled || vhost->using_channels)
		login_info->capabilities |= cpu_to_be64(IBMVFC_CAN_USE_CHANNELS);

	login_info->async.va = cpu_to_be64(vhost->async_crq.msg_token);
	login_info->async.len = cpu_to_be32(async_crq->size *
					    माप(*async_crq->msgs.async));
	म_नकलन(login_info->partition_name, vhost->partition_name, IBMVFC_MAX_NAME);
	म_नकलन(login_info->device_name,
		dev_name(&vhost->host->shost_gendev), IBMVFC_MAX_NAME);

	location = of_get_property(of_node, "ibm,loc-code", शून्य);
	location = location ? location : dev_name(vhost->dev);
	म_नकलन(login_info->drc_name, location, IBMVFC_MAX_NAME);
पूर्ण

/**
 * ibmvfc_get_event - Gets the next मुक्त event in pool
 * @queue:      ibmvfc queue काष्ठा
 *
 * Returns a मुक्त event from the pool.
 **/
अटल काष्ठा ibmvfc_event *ibmvfc_get_event(काष्ठा ibmvfc_queue *queue)
अणु
	काष्ठा ibmvfc_event *evt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->l_lock, flags);
	BUG_ON(list_empty(&queue->मुक्त));
	evt = list_entry(queue->मुक्त.next, काष्ठा ibmvfc_event, queue_list);
	atomic_set(&evt->मुक्त, 0);
	list_del(&evt->queue_list);
	spin_unlock_irqrestore(&queue->l_lock, flags);
	वापस evt;
पूर्ण

/**
 * ibmvfc_locked_करोne - Calls evt completion with host_lock held
 * @evt:	ibmvfc evt to complete
 *
 * All non-scsi command completion callbacks have the expectation that the
 * host_lock is held. This callback is used by ibmvfc_init_event to wrap a
 * MAD evt with the host_lock.
 **/
अटल व्योम ibmvfc_locked_करोne(काष्ठा ibmvfc_event *evt)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(evt->vhost->host->host_lock, flags);
	evt->_करोne(evt);
	spin_unlock_irqrestore(evt->vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_init_event - Initialize fields in an event काष्ठा that are always
 *				required.
 * @evt:	The event
 * @करोne:	Routine to call when the event is responded to
 * @क्रमmat:	SRP or MAD क्रमmat
 **/
अटल व्योम ibmvfc_init_event(काष्ठा ibmvfc_event *evt,
			      व्योम (*करोne) (काष्ठा ibmvfc_event *), u8 क्रमmat)
अणु
	evt->cmnd = शून्य;
	evt->sync_iu = शून्य;
	evt->eh_comp = शून्य;
	evt->crq.क्रमmat = क्रमmat;
	अगर (क्रमmat == IBMVFC_CMD_FORMAT)
		evt->करोne = करोne;
	अन्यथा अणु
		evt->_करोne = करोne;
		evt->करोne = ibmvfc_locked_करोne;
	पूर्ण
	evt->hwq = 0;
पूर्ण

/**
 * ibmvfc_map_sg_list - Initialize scatterlist
 * @scmd:	scsi command काष्ठा
 * @nseg:	number of scatterlist segments
 * @md:	memory descriptor list to initialize
 **/
अटल व्योम ibmvfc_map_sg_list(काष्ठा scsi_cmnd *scmd, पूर्णांक nseg,
			       काष्ठा srp_direct_buf *md)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	scsi_क्रम_each_sg(scmd, sg, nseg, i) अणु
		md[i].va = cpu_to_be64(sg_dma_address(sg));
		md[i].len = cpu_to_be32(sg_dma_len(sg));
		md[i].key = 0;
	पूर्ण
पूर्ण

/**
 * ibmvfc_map_sg_data - Maps dma क्रम a scatterlist and initializes descriptor fields
 * @scmd:		काष्ठा scsi_cmnd with the scatterlist
 * @evt:		ibmvfc event काष्ठा
 * @vfc_cmd:	vfc_cmd that contains the memory descriptor
 * @dev:		device क्रम which to map dma memory
 *
 * Returns:
 *	0 on success / non-zero on failure
 **/
अटल पूर्णांक ibmvfc_map_sg_data(काष्ठा scsi_cmnd *scmd,
			      काष्ठा ibmvfc_event *evt,
			      काष्ठा ibmvfc_cmd *vfc_cmd, काष्ठा device *dev)
अणु

	पूर्णांक sg_mapped;
	काष्ठा srp_direct_buf *data = &vfc_cmd->ioba;
	काष्ठा ibmvfc_host *vhost = dev_get_drvdata(dev);
	काष्ठा ibmvfc_fcp_cmd_iu *iu = ibmvfc_get_fcp_iu(evt->vhost, vfc_cmd);

	अगर (cls3_error)
		vfc_cmd->flags |= cpu_to_be16(IBMVFC_CLASS_3_ERR);

	sg_mapped = scsi_dma_map(scmd);
	अगर (!sg_mapped) अणु
		vfc_cmd->flags |= cpu_to_be16(IBMVFC_NO_MEM_DESC);
		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(sg_mapped < 0)) अणु
		अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
			scmd_prपूर्णांकk(KERN_ERR, scmd, "Failed to map DMA buffer for command\n");
		वापस sg_mapped;
	पूर्ण

	अगर (scmd->sc_data_direction == DMA_TO_DEVICE) अणु
		vfc_cmd->flags |= cpu_to_be16(IBMVFC_WRITE);
		iu->add_cdb_len |= IBMVFC_WRDATA;
	पूर्ण अन्यथा अणु
		vfc_cmd->flags |= cpu_to_be16(IBMVFC_READ);
		iu->add_cdb_len |= IBMVFC_RDDATA;
	पूर्ण

	अगर (sg_mapped == 1) अणु
		ibmvfc_map_sg_list(scmd, sg_mapped, data);
		वापस 0;
	पूर्ण

	vfc_cmd->flags |= cpu_to_be16(IBMVFC_SCATTERLIST);

	अगर (!evt->ext_list) अणु
		evt->ext_list = dma_pool_alloc(vhost->sg_pool, GFP_ATOMIC,
					       &evt->ext_list_token);

		अगर (!evt->ext_list) अणु
			scsi_dma_unmap(scmd);
			अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
				scmd_prपूर्णांकk(KERN_ERR, scmd, "Can't allocate memory for scatterlist\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ibmvfc_map_sg_list(scmd, sg_mapped, evt->ext_list);

	data->va = cpu_to_be64(evt->ext_list_token);
	data->len = cpu_to_be32(sg_mapped * माप(काष्ठा srp_direct_buf));
	data->key = 0;
	वापस 0;
पूर्ण

/**
 * ibmvfc_समयout - Internal command समयout handler
 * @t:	काष्ठा ibmvfc_event that समयd out
 *
 * Called when an पूर्णांकernally generated command बार out
 **/
अटल व्योम ibmvfc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ibmvfc_event *evt = from_समयr(evt, t, समयr);
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	dev_err(vhost->dev, "Command timed out (%p). Resetting connection\n", evt);
	ibmvfc_reset_host(vhost);
पूर्ण

/**
 * ibmvfc_send_event - Transक्रमms event to u64 array and calls send_crq()
 * @evt:		event to be sent
 * @vhost:		ibmvfc host काष्ठा
 * @समयout:	समयout in seconds - 0 means करो not समय command
 *
 * Returns the value वापसed from ibmvfc_send_crq(). (Zero क्रम success)
 **/
अटल पूर्णांक ibmvfc_send_event(काष्ठा ibmvfc_event *evt,
			     काष्ठा ibmvfc_host *vhost, अचिन्हित दीर्घ समयout)
अणु
	__be64 *crq_as_u64 = (__be64 *) &evt->crq;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/* Copy the IU पूर्णांकo the transfer area */
	*evt->xfer_iu = evt->iu;
	अगर (evt->crq.क्रमmat == IBMVFC_CMD_FORMAT)
		evt->xfer_iu->cmd.tag = cpu_to_be64((u64)evt);
	अन्यथा अगर (evt->crq.क्रमmat == IBMVFC_MAD_FORMAT)
		evt->xfer_iu->mad_common.tag = cpu_to_be64((u64)evt);
	अन्यथा
		BUG();

	समयr_setup(&evt->समयr, ibmvfc_समयout, 0);

	अगर (समयout) अणु
		evt->समयr.expires = jअगरfies + (समयout * HZ);
		add_समयr(&evt->समयr);
	पूर्ण

	spin_lock_irqsave(&evt->queue->l_lock, flags);
	list_add_tail(&evt->queue_list, &evt->queue->sent);

	mb();

	अगर (evt->queue->fmt == IBMVFC_SUB_CRQ_FMT)
		rc = ibmvfc_send_sub_crq(vhost,
					 evt->queue->vios_cookie,
					 be64_to_cpu(crq_as_u64[0]),
					 be64_to_cpu(crq_as_u64[1]),
					 0, 0);
	अन्यथा
		rc = ibmvfc_send_crq(vhost, be64_to_cpu(crq_as_u64[0]),
				     be64_to_cpu(crq_as_u64[1]));

	अगर (rc) अणु
		list_del(&evt->queue_list);
		spin_unlock_irqrestore(&evt->queue->l_lock, flags);
		del_समयr(&evt->समयr);

		/* If send_crq वापसs H_CLOSED, वापस SCSI_MLQUEUE_HOST_BUSY.
		 * Firmware will send a CRQ with a transport event (0xFF) to
		 * tell this client what has happened to the transport. This
		 * will be handled in ibmvfc_handle_crq()
		 */
		अगर (rc == H_CLOSED) अणु
			अगर (prपूर्णांकk_ratelimit())
				dev_warn(vhost->dev, "Send warning. Receive queue closed, will retry.\n");
			अगर (evt->cmnd)
				scsi_dma_unmap(evt->cmnd);
			ibmvfc_मुक्त_event(evt);
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण

		dev_err(vhost->dev, "Send error (rc=%d)\n", rc);
		अगर (evt->cmnd) अणु
			evt->cmnd->result = DID_ERROR << 16;
			evt->करोne = ibmvfc_scsi_eh_करोne;
		पूर्ण अन्यथा
			evt->xfer_iu->mad_common.status = cpu_to_be16(IBMVFC_MAD_CRQ_ERROR);

		evt->करोne(evt);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&evt->queue->l_lock, flags);
		ibmvfc_trc_start(evt);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ibmvfc_log_error - Log an error क्रम the failed command अगर appropriate
 * @evt:	ibmvfc event to log
 *
 **/
अटल व्योम ibmvfc_log_error(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_cmd *vfc_cmd = &evt->xfer_iu->cmd;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_fcp_rsp *rsp = ibmvfc_get_fcp_rsp(vhost, vfc_cmd);
	काष्ठा scsi_cmnd *cmnd = evt->cmnd;
	स्थिर अक्षर *err = unknown_error;
	पूर्णांक index = ibmvfc_get_err_index(be16_to_cpu(vfc_cmd->status), be16_to_cpu(vfc_cmd->error));
	पूर्णांक logerr = 0;
	पूर्णांक rsp_code = 0;

	अगर (index >= 0) अणु
		logerr = cmd_status[index].log;
		err = cmd_status[index].name;
	पूर्ण

	अगर (!logerr && (vhost->log_level <= (IBMVFC_DEFAULT_LOG_LEVEL + 1)))
		वापस;

	अगर (rsp->flags & FCP_RSP_LEN_VALID)
		rsp_code = rsp->data.info.rsp_code;

	scmd_prपूर्णांकk(KERN_ERR, cmnd, "Command (%02X) : %s (%x:%x) "
		    "flags: %x fcp_rsp: %x, resid=%d, scsi_status: %x\n",
		    cmnd->cmnd[0], err, be16_to_cpu(vfc_cmd->status), be16_to_cpu(vfc_cmd->error),
		    rsp->flags, rsp_code, scsi_get_resid(cmnd), rsp->scsi_status);
पूर्ण

/**
 * ibmvfc_relogin - Log back पूर्णांकo the specअगरied device
 * @sdev:	scsi device काष्ठा
 *
 **/
अटल व्योम ibmvfc_relogin(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा ibmvfc_target *tgt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (rport == tgt->rport) अणु
			ibmvfc_del_tgt(tgt);
			अवरोध;
		पूर्ण
	पूर्ण

	ibmvfc_reinit_host(vhost);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_scsi_करोne - Handle responses from commands
 * @evt:	ibmvfc event to be handled
 *
 * Used as a callback when sending scsi cmds.
 **/
अटल व्योम ibmvfc_scsi_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_cmd *vfc_cmd = &evt->xfer_iu->cmd;
	काष्ठा ibmvfc_fcp_rsp *rsp = ibmvfc_get_fcp_rsp(evt->vhost, vfc_cmd);
	काष्ठा scsi_cmnd *cmnd = evt->cmnd;
	u32 rsp_len = 0;
	u32 sense_len = be32_to_cpu(rsp->fcp_sense_len);

	अगर (cmnd) अणु
		अगर (be16_to_cpu(vfc_cmd->response_flags) & IBMVFC_ADAPTER_RESID_VALID)
			scsi_set_resid(cmnd, be32_to_cpu(vfc_cmd->adapter_resid));
		अन्यथा अगर (rsp->flags & FCP_RESID_UNDER)
			scsi_set_resid(cmnd, be32_to_cpu(rsp->fcp_resid));
		अन्यथा
			scsi_set_resid(cmnd, 0);

		अगर (vfc_cmd->status) अणु
			cmnd->result = ibmvfc_get_err_result(evt->vhost, vfc_cmd);

			अगर (rsp->flags & FCP_RSP_LEN_VALID)
				rsp_len = be32_to_cpu(rsp->fcp_rsp_len);
			अगर ((sense_len + rsp_len) > SCSI_SENSE_BUFFERSIZE)
				sense_len = SCSI_SENSE_BUFFERSIZE - rsp_len;
			अगर ((rsp->flags & FCP_SNS_LEN_VALID) && rsp->fcp_sense_len && rsp_len <= 8)
				स_नकल(cmnd->sense_buffer, rsp->data.sense + rsp_len, sense_len);
			अगर ((be16_to_cpu(vfc_cmd->status) & IBMVFC_VIOS_FAILURE) &&
			    (be16_to_cpu(vfc_cmd->error) == IBMVFC_PLOGI_REQUIRED))
				ibmvfc_relogin(cmnd->device);

			अगर (!cmnd->result && (!scsi_get_resid(cmnd) || (rsp->flags & FCP_RESID_OVER)))
				cmnd->result = (DID_ERROR << 16);

			ibmvfc_log_error(evt);
		पूर्ण

		अगर (!cmnd->result &&
		    (scsi_bufflen(cmnd) - scsi_get_resid(cmnd) < cmnd->underflow))
			cmnd->result = (DID_ERROR << 16);

		scsi_dma_unmap(cmnd);
		cmnd->scsi_करोne(cmnd);
	पूर्ण

	ibmvfc_मुक्त_event(evt);
पूर्ण

/**
 * ibmvfc_host_chkपढ़ोy - Check अगर the host can accept commands
 * @vhost:	 काष्ठा ibmvfc host
 *
 * Returns:
 *	1 अगर host can accept command / 0 अगर not
 **/
अटल अंतरभूत पूर्णांक ibmvfc_host_chkपढ़ोy(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक result = 0;

	चयन (vhost->state) अणु
	हाल IBMVFC_LINK_DEAD:
	हाल IBMVFC_HOST_OFFLINE:
		result = DID_NO_CONNECT << 16;
		अवरोध;
	हाल IBMVFC_NO_CRQ:
	हाल IBMVFC_INITIALIZING:
	हाल IBMVFC_HALTED:
	हाल IBMVFC_LINK_DOWN:
		result = DID_REQUEUE << 16;
		अवरोध;
	हाल IBMVFC_ACTIVE:
		result = 0;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल काष्ठा ibmvfc_cmd *ibmvfc_init_vfc_cmd(काष्ठा ibmvfc_event *evt, काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_cmd *vfc_cmd = &evt->iu.cmd;
	काष्ठा ibmvfc_fcp_cmd_iu *iu = ibmvfc_get_fcp_iu(vhost, vfc_cmd);
	काष्ठा ibmvfc_fcp_rsp *rsp = ibmvfc_get_fcp_rsp(vhost, vfc_cmd);
	माप_प्रकार offset;

	स_रखो(vfc_cmd, 0, माप(*vfc_cmd));
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN)) अणु
		offset = दुरत्व(काष्ठा ibmvfc_cmd, v2.rsp);
		vfc_cmd->target_wwpn = cpu_to_be64(rport->port_name);
	पूर्ण अन्यथा
		offset = दुरत्व(काष्ठा ibmvfc_cmd, v1.rsp);
	vfc_cmd->resp.va = cpu_to_be64(be64_to_cpu(evt->crq.ioba) + offset);
	vfc_cmd->resp.len = cpu_to_be32(माप(*rsp));
	vfc_cmd->frame_type = cpu_to_be32(IBMVFC_SCSI_FCP_TYPE);
	vfc_cmd->payload_len = cpu_to_be32(माप(*iu));
	vfc_cmd->resp_len = cpu_to_be32(माप(*rsp));
	vfc_cmd->cancel_key = cpu_to_be32((अचिन्हित दीर्घ)sdev->hostdata);
	vfc_cmd->tgt_scsi_id = cpu_to_be64(rport->port_id);
	पूर्णांक_to_scsilun(sdev->lun, &iu->lun);

	वापस vfc_cmd;
पूर्ण

/**
 * ibmvfc_queuecommand - The queuecommand function of the scsi ढाँचा
 * @shost:	scsi host काष्ठा
 * @cmnd:	काष्ठा scsi_cmnd to be executed
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));
	काष्ठा ibmvfc_cmd *vfc_cmd;
	काष्ठा ibmvfc_fcp_cmd_iu *iu;
	काष्ठा ibmvfc_event *evt;
	u32 tag_and_hwq = blk_mq_unique_tag(cmnd->request);
	u16 hwq = blk_mq_unique_tag_to_hwq(tag_and_hwq);
	u16 scsi_channel;
	पूर्णांक rc;

	अगर (unlikely((rc = fc_remote_port_chkपढ़ोy(rport))) ||
	    unlikely((rc = ibmvfc_host_chkपढ़ोy(vhost)))) अणु
		cmnd->result = rc;
		cmnd->scsi_करोne(cmnd);
		वापस 0;
	पूर्ण

	cmnd->result = (DID_OK << 16);
	अगर (vhost->using_channels) अणु
		scsi_channel = hwq % vhost->scsi_scrqs.active_queues;
		evt = ibmvfc_get_event(&vhost->scsi_scrqs.scrqs[scsi_channel]);
		evt->hwq = hwq % vhost->scsi_scrqs.active_queues;
	पूर्ण अन्यथा
		evt = ibmvfc_get_event(&vhost->crq);

	ibmvfc_init_event(evt, ibmvfc_scsi_करोne, IBMVFC_CMD_FORMAT);
	evt->cmnd = cmnd;

	vfc_cmd = ibmvfc_init_vfc_cmd(evt, cmnd->device);
	iu = ibmvfc_get_fcp_iu(vhost, vfc_cmd);

	iu->xfer_len = cpu_to_be32(scsi_bufflen(cmnd));
	स_नकल(iu->cdb, cmnd->cmnd, cmnd->cmd_len);

	अगर (cmnd->flags & SCMD_TAGGED) अणु
		vfc_cmd->task_tag = cpu_to_be64(cmnd->tag);
		iu->pri_task_attr = IBMVFC_SIMPLE_TASK;
	पूर्ण

	vfc_cmd->correlation = cpu_to_be64((u64)evt);

	अगर (likely(!(rc = ibmvfc_map_sg_data(cmnd, evt, vfc_cmd, vhost->dev))))
		वापस ibmvfc_send_event(evt, vhost, 0);

	ibmvfc_मुक्त_event(evt);
	अगर (rc == -ENOMEM)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
		scmd_prपूर्णांकk(KERN_ERR, cmnd,
			    "Failed to map DMA buffer for command. rc=%d\n", rc);

	cmnd->result = DID_ERROR << 16;
	cmnd->scsi_करोne(cmnd);
	वापस 0;
पूर्ण

/**
 * ibmvfc_sync_completion - Signal that a synchronous command has completed
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_sync_completion(काष्ठा ibmvfc_event *evt)
अणु
	/* copy the response back */
	अगर (evt->sync_iu)
		*evt->sync_iu = *evt->xfer_iu;

	complete(&evt->comp);
पूर्ण

/**
 * ibmvfc_bsg_समयout_करोne - Completion handler क्रम cancelling BSG commands
 * @evt:	काष्ठा ibmvfc_event
 *
 **/
अटल व्योम ibmvfc_bsg_समयout_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;

	ibmvfc_मुक्त_event(evt);
	vhost->पातing_passthru = 0;
	dev_info(vhost->dev, "Passthru command cancelled\n");
पूर्ण

/**
 * ibmvfc_bsg_समयout - Handle a BSG समयout
 * @job:	काष्ठा bsg_job that समयd out
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_bsg_समयout(काष्ठा bsg_job *job)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(fc_bsg_to_shost(job));
	अचिन्हित दीर्घ port_id = (अचिन्हित दीर्घ)job->dd_data;
	काष्ठा ibmvfc_event *evt;
	काष्ठा ibmvfc_पंचांगf *पंचांगf;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	ENTER;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	अगर (vhost->पातing_passthru || vhost->state != IBMVFC_ACTIVE) अणु
		__ibmvfc_reset_host(vhost);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		वापस 0;
	पूर्ण

	vhost->पातing_passthru = 1;
	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, ibmvfc_bsg_समयout_करोne, IBMVFC_MAD_FORMAT);

	पंचांगf = &evt->iu.पंचांगf;
	स_रखो(पंचांगf, 0, माप(*पंचांगf));
	पंचांगf->common.version = cpu_to_be32(1);
	पंचांगf->common.opcode = cpu_to_be32(IBMVFC_TMF_MAD);
	पंचांगf->common.length = cpu_to_be16(माप(*पंचांगf));
	पंचांगf->scsi_id = cpu_to_be64(port_id);
	पंचांगf->cancel_key = cpu_to_be32(IBMVFC_PASSTHRU_CANCEL_KEY);
	पंचांगf->my_cancel_key = cpu_to_be32(IBMVFC_INTERNAL_CANCEL_KEY);
	rc = ibmvfc_send_event(evt, vhost, शेष_समयout);

	अगर (rc != 0) अणु
		vhost->पातing_passthru = 0;
		dev_err(vhost->dev, "Failed to send cancel event. rc=%d\n", rc);
		rc = -EIO;
	पूर्ण अन्यथा
		dev_info(vhost->dev, "Cancelling passthru command to port id 0x%lx\n",
			 port_id);

	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_bsg_plogi - PLOGI पूर्णांकo a target to handle a BSG command
 * @vhost:		काष्ठा ibmvfc_host to send command
 * @port_id:	port ID to send command
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_bsg_plogi(काष्ठा ibmvfc_host *vhost, अचिन्हित पूर्णांक port_id)
अणु
	काष्ठा ibmvfc_port_login *plogi;
	काष्ठा ibmvfc_target *tgt;
	काष्ठा ibmvfc_event *evt;
	जोड़ ibmvfc_iu rsp_iu;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0, issue_login = 1;

	ENTER;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->scsi_id == port_id) अणु
			issue_login = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!issue_login)
		जाओ unlock_out;
	अगर (unlikely((rc = ibmvfc_host_chkपढ़ोy(vhost))))
		जाओ unlock_out;

	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, ibmvfc_sync_completion, IBMVFC_MAD_FORMAT);
	plogi = &evt->iu.plogi;
	स_रखो(plogi, 0, माप(*plogi));
	plogi->common.version = cpu_to_be32(1);
	plogi->common.opcode = cpu_to_be32(IBMVFC_PORT_LOGIN);
	plogi->common.length = cpu_to_be16(माप(*plogi));
	plogi->scsi_id = cpu_to_be64(port_id);
	evt->sync_iu = &rsp_iu;
	init_completion(&evt->comp);

	rc = ibmvfc_send_event(evt, vhost, शेष_समयout);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (rc)
		वापस -EIO;

	रुको_क्रम_completion(&evt->comp);

	अगर (rsp_iu.plogi.common.status)
		rc = -EIO;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_मुक्त_event(evt);
unlock_out:
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_bsg_request - Handle a BSG request
 * @job:	काष्ठा bsg_job to be executed
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_bsg_request(काष्ठा bsg_job *job)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(fc_bsg_to_shost(job));
	काष्ठा fc_rport *rport = fc_bsg_to_rport(job);
	काष्ठा ibmvfc_passthru_mad *mad;
	काष्ठा ibmvfc_event *evt;
	जोड़ ibmvfc_iu rsp_iu;
	अचिन्हित दीर्घ flags, port_id = -1;
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	अचिन्हित पूर्णांक code = bsg_request->msgcode;
	पूर्णांक rc = 0, req_seg, rsp_seg, issue_login = 0;
	u32 fc_flags, rsp_len;

	ENTER;
	bsg_reply->reply_payload_rcv_len = 0;
	अगर (rport)
		port_id = rport->port_id;

	चयन (code) अणु
	हाल FC_BSG_HST_ELS_NOLOGIN:
		port_id = (bsg_request->rqst_data.h_els.port_id[0] << 16) |
			(bsg_request->rqst_data.h_els.port_id[1] << 8) |
			bsg_request->rqst_data.h_els.port_id[2];
		fallthrough;
	हाल FC_BSG_RPT_ELS:
		fc_flags = IBMVFC_FC_ELS;
		अवरोध;
	हाल FC_BSG_HST_CT:
		issue_login = 1;
		port_id = (bsg_request->rqst_data.h_ct.port_id[0] << 16) |
			(bsg_request->rqst_data.h_ct.port_id[1] << 8) |
			bsg_request->rqst_data.h_ct.port_id[2];
		fallthrough;
	हाल FC_BSG_RPT_CT:
		fc_flags = IBMVFC_FC_CT_IU;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (port_id == -1)
		वापस -EINVAL;
	अगर (!mutex_trylock(&vhost->passthru_mutex))
		वापस -EBUSY;

	job->dd_data = (व्योम *)port_id;
	req_seg = dma_map_sg(vhost->dev, job->request_payload.sg_list,
			     job->request_payload.sg_cnt, DMA_TO_DEVICE);

	अगर (!req_seg) अणु
		mutex_unlock(&vhost->passthru_mutex);
		वापस -ENOMEM;
	पूर्ण

	rsp_seg = dma_map_sg(vhost->dev, job->reply_payload.sg_list,
			     job->reply_payload.sg_cnt, DMA_FROM_DEVICE);

	अगर (!rsp_seg) अणु
		dma_unmap_sg(vhost->dev, job->request_payload.sg_list,
			     job->request_payload.sg_cnt, DMA_TO_DEVICE);
		mutex_unlock(&vhost->passthru_mutex);
		वापस -ENOMEM;
	पूर्ण

	अगर (req_seg > 1 || rsp_seg > 1) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (issue_login)
		rc = ibmvfc_bsg_plogi(vhost, port_id);

	spin_lock_irqsave(vhost->host->host_lock, flags);

	अगर (unlikely(rc || (rport && (rc = fc_remote_port_chkपढ़ोy(rport)))) ||
	    unlikely((rc = ibmvfc_host_chkपढ़ोy(vhost)))) अणु
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		जाओ out;
	पूर्ण

	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, ibmvfc_sync_completion, IBMVFC_MAD_FORMAT);
	mad = &evt->iu.passthru;

	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_PASSTHRU);
	mad->common.length = cpu_to_be16(माप(*mad) - माप(mad->fc_iu) - माप(mad->iu));

	mad->cmd_ioba.va = cpu_to_be64(be64_to_cpu(evt->crq.ioba) +
		दुरत्व(काष्ठा ibmvfc_passthru_mad, iu));
	mad->cmd_ioba.len = cpu_to_be32(माप(mad->iu));

	mad->iu.cmd_len = cpu_to_be32(job->request_payload.payload_len);
	mad->iu.rsp_len = cpu_to_be32(job->reply_payload.payload_len);
	mad->iu.flags = cpu_to_be32(fc_flags);
	mad->iu.cancel_key = cpu_to_be32(IBMVFC_PASSTHRU_CANCEL_KEY);

	mad->iu.cmd.va = cpu_to_be64(sg_dma_address(job->request_payload.sg_list));
	mad->iu.cmd.len = cpu_to_be32(sg_dma_len(job->request_payload.sg_list));
	mad->iu.rsp.va = cpu_to_be64(sg_dma_address(job->reply_payload.sg_list));
	mad->iu.rsp.len = cpu_to_be32(sg_dma_len(job->reply_payload.sg_list));
	mad->iu.scsi_id = cpu_to_be64(port_id);
	mad->iu.tag = cpu_to_be64((u64)evt);
	rsp_len = be32_to_cpu(mad->iu.rsp.len);

	evt->sync_iu = &rsp_iu;
	init_completion(&evt->comp);
	rc = ibmvfc_send_event(evt, vhost, 0);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (rc) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	रुको_क्रम_completion(&evt->comp);

	अगर (rsp_iu.passthru.common.status)
		rc = -EIO;
	अन्यथा
		bsg_reply->reply_payload_rcv_len = rsp_len;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_मुक्त_event(evt);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	bsg_reply->result = rc;
	bsg_job_करोne(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	rc = 0;
out:
	dma_unmap_sg(vhost->dev, job->request_payload.sg_list,
		     job->request_payload.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(vhost->dev, job->reply_payload.sg_list,
		     job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	mutex_unlock(&vhost->passthru_mutex);
	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_reset_device - Reset the device with the specअगरied reset type
 * @sdev:	scsi device to reset
 * @type:	reset type
 * @desc:	reset type description क्रम log messages
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_reset_device(काष्ठा scsi_device *sdev, पूर्णांक type, अक्षर *desc)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा ibmvfc_cmd *पंचांगf;
	काष्ठा ibmvfc_event *evt = शून्य;
	जोड़ ibmvfc_iu rsp_iu;
	काष्ठा ibmvfc_fcp_cmd_iu *iu;
	काष्ठा ibmvfc_fcp_rsp *fc_rsp = ibmvfc_get_fcp_rsp(vhost, &rsp_iu.cmd);
	पूर्णांक rsp_rc = -EBUSY;
	अचिन्हित दीर्घ flags;
	पूर्णांक rsp_code = 0;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	अगर (vhost->state == IBMVFC_ACTIVE) अणु
		अगर (vhost->using_channels)
			evt = ibmvfc_get_event(&vhost->scsi_scrqs.scrqs[0]);
		अन्यथा
			evt = ibmvfc_get_event(&vhost->crq);

		ibmvfc_init_event(evt, ibmvfc_sync_completion, IBMVFC_CMD_FORMAT);
		पंचांगf = ibmvfc_init_vfc_cmd(evt, sdev);
		iu = ibmvfc_get_fcp_iu(vhost, पंचांगf);

		पंचांगf->flags = cpu_to_be16((IBMVFC_NO_MEM_DESC | IBMVFC_TMF));
		अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN))
			पंचांगf->target_wwpn = cpu_to_be64(rport->port_name);
		iu->पंचांगf_flags = type;
		evt->sync_iu = &rsp_iu;

		init_completion(&evt->comp);
		rsp_rc = ibmvfc_send_event(evt, vhost, शेष_समयout);
	पूर्ण
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (rsp_rc != 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, sdev, "Failed to send %s reset event. rc=%d\n",
			    desc, rsp_rc);
		वापस -EIO;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Resetting %s\n", desc);
	रुको_क्रम_completion(&evt->comp);

	अगर (rsp_iu.cmd.status)
		rsp_code = ibmvfc_get_err_result(vhost, &rsp_iu.cmd);

	अगर (rsp_code) अणु
		अगर (fc_rsp->flags & FCP_RSP_LEN_VALID)
			rsp_code = fc_rsp->data.info.rsp_code;

		sdev_prपूर्णांकk(KERN_ERR, sdev, "%s reset failed: %s (%x:%x) "
			    "flags: %x fcp_rsp: %x, scsi_status: %x\n", desc,
			    ibmvfc_get_cmd_error(be16_to_cpu(rsp_iu.cmd.status), be16_to_cpu(rsp_iu.cmd.error)),
			    be16_to_cpu(rsp_iu.cmd.status), be16_to_cpu(rsp_iu.cmd.error), fc_rsp->flags, rsp_code,
			    fc_rsp->scsi_status);
		rsp_rc = -EIO;
	पूर्ण अन्यथा
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s reset successful\n", desc);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_मुक्त_event(evt);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस rsp_rc;
पूर्ण

/**
 * ibmvfc_match_rport - Match function क्रम specअगरied remote port
 * @evt:	ibmvfc event काष्ठा
 * @rport:	device to match
 *
 * Returns:
 *	1 अगर event matches rport / 0 अगर event करोes not match rport
 **/
अटल पूर्णांक ibmvfc_match_rport(काष्ठा ibmvfc_event *evt, व्योम *rport)
अणु
	काष्ठा fc_rport *cmd_rport;

	अगर (evt->cmnd) अणु
		cmd_rport = starget_to_rport(scsi_target(evt->cmnd->device));
		अगर (cmd_rport == rport)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ibmvfc_match_target - Match function क्रम specअगरied target
 * @evt:	ibmvfc event काष्ठा
 * @device:	device to match (starget)
 *
 * Returns:
 *	1 अगर event matches starget / 0 अगर event करोes not match starget
 **/
अटल पूर्णांक ibmvfc_match_target(काष्ठा ibmvfc_event *evt, व्योम *device)
अणु
	अगर (evt->cmnd && scsi_target(evt->cmnd->device) == device)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ibmvfc_match_lun - Match function क्रम specअगरied LUN
 * @evt:	ibmvfc event काष्ठा
 * @device:	device to match (sdev)
 *
 * Returns:
 *	1 अगर event matches sdev / 0 अगर event करोes not match sdev
 **/
अटल पूर्णांक ibmvfc_match_lun(काष्ठा ibmvfc_event *evt, व्योम *device)
अणु
	अगर (evt->cmnd && evt->cmnd->device == device)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ibmvfc_event_is_मुक्त - Check अगर event is मुक्त or not
 * @evt:	ibmvfc event काष्ठा
 *
 * Returns:
 *	true / false
 **/
अटल bool ibmvfc_event_is_मुक्त(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_event *loop_evt;

	list_क्रम_each_entry(loop_evt, &evt->queue->मुक्त, queue_list)
		अगर (loop_evt == evt)
			वापस true;

	वापस false;
पूर्ण

/**
 * ibmvfc_रुको_क्रम_ops - Wait क्रम ops to complete
 * @vhost:	ibmvfc host काष्ठा
 * @device:	device to match (starget or sdev)
 * @match:	match function
 *
 * Returns:
 *	SUCCESS / FAILED
 **/
अटल पूर्णांक ibmvfc_रुको_क्रम_ops(काष्ठा ibmvfc_host *vhost, व्योम *device,
			       पूर्णांक (*match) (काष्ठा ibmvfc_event *, व्योम *))
अणु
	काष्ठा ibmvfc_event *evt;
	DECLARE_COMPLETION_ONSTACK(comp);
	पूर्णांक रुको, i, q_index, q_size;
	अचिन्हित दीर्घ flags;
	चिन्हित दीर्घ समयout = IBMVFC_ABORT_WAIT_TIMEOUT * HZ;
	काष्ठा ibmvfc_queue *queues;

	ENTER;
	अगर (vhost->mq_enabled && vhost->using_channels) अणु
		queues = vhost->scsi_scrqs.scrqs;
		q_size = vhost->scsi_scrqs.active_queues;
	पूर्ण अन्यथा अणु
		queues = &vhost->crq;
		q_size = 1;
	पूर्ण

	करो अणु
		रुको = 0;
		spin_lock_irqsave(vhost->host->host_lock, flags);
		क्रम (q_index = 0; q_index < q_size; q_index++) अणु
			spin_lock(&queues[q_index].l_lock);
			क्रम (i = 0; i < queues[q_index].evt_pool.size; i++) अणु
				evt = &queues[q_index].evt_pool.events[i];
				अगर (!ibmvfc_event_is_मुक्त(evt)) अणु
					अगर (match(evt, device)) अणु
						evt->eh_comp = &comp;
						रुको++;
					पूर्ण
				पूर्ण
			पूर्ण
			spin_unlock(&queues[q_index].l_lock);
		पूर्ण
		spin_unlock_irqrestore(vhost->host->host_lock, flags);

		अगर (रुको) अणु
			समयout = रुको_क्रम_completion_समयout(&comp, समयout);

			अगर (!समयout) अणु
				रुको = 0;
				spin_lock_irqsave(vhost->host->host_lock, flags);
				क्रम (q_index = 0; q_index < q_size; q_index++) अणु
					spin_lock(&queues[q_index].l_lock);
					क्रम (i = 0; i < queues[q_index].evt_pool.size; i++) अणु
						evt = &queues[q_index].evt_pool.events[i];
						अगर (!ibmvfc_event_is_मुक्त(evt)) अणु
							अगर (match(evt, device)) अणु
								evt->eh_comp = शून्य;
								रुको++;
							पूर्ण
						पूर्ण
					पूर्ण
					spin_unlock(&queues[q_index].l_lock);
				पूर्ण
				spin_unlock_irqrestore(vhost->host->host_lock, flags);
				अगर (रुको)
					dev_err(vhost->dev, "Timed out waiting for aborted commands\n");
				LEAVE;
				वापस रुको ? FAILED : SUCCESS;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (रुको);

	LEAVE;
	वापस SUCCESS;
पूर्ण

अटल काष्ठा ibmvfc_event *ibmvfc_init_पंचांगf(काष्ठा ibmvfc_queue *queue,
					    काष्ठा scsi_device *sdev,
					    पूर्णांक type)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा scsi_target *starget = scsi_target(sdev);
	काष्ठा fc_rport *rport = starget_to_rport(starget);
	काष्ठा ibmvfc_event *evt;
	काष्ठा ibmvfc_पंचांगf *पंचांगf;

	evt = ibmvfc_get_event(queue);
	ibmvfc_init_event(evt, ibmvfc_sync_completion, IBMVFC_MAD_FORMAT);

	पंचांगf = &evt->iu.पंचांगf;
	स_रखो(पंचांगf, 0, माप(*पंचांगf));
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN)) अणु
		पंचांगf->common.version = cpu_to_be32(2);
		पंचांगf->target_wwpn = cpu_to_be64(rport->port_name);
	पूर्ण अन्यथा अणु
		पंचांगf->common.version = cpu_to_be32(1);
	पूर्ण
	पंचांगf->common.opcode = cpu_to_be32(IBMVFC_TMF_MAD);
	पंचांगf->common.length = cpu_to_be16(माप(*पंचांगf));
	पंचांगf->scsi_id = cpu_to_be64(rport->port_id);
	पूर्णांक_to_scsilun(sdev->lun, &पंचांगf->lun);
	अगर (!ibmvfc_check_caps(vhost, IBMVFC_CAN_SUPPRESS_ABTS))
		type &= ~IBMVFC_TMF_SUPPRESS_ABTS;
	अगर (vhost->state == IBMVFC_ACTIVE)
		पंचांगf->flags = cpu_to_be32((type | IBMVFC_TMF_LUA_VALID));
	अन्यथा
		पंचांगf->flags = cpu_to_be32(((type & IBMVFC_TMF_SUPPRESS_ABTS) | IBMVFC_TMF_LUA_VALID));
	पंचांगf->cancel_key = cpu_to_be32((अचिन्हित दीर्घ)sdev->hostdata);
	पंचांगf->my_cancel_key = cpu_to_be32((अचिन्हित दीर्घ)starget->hostdata);

	init_completion(&evt->comp);

	वापस evt;
पूर्ण

अटल पूर्णांक ibmvfc_cancel_all_mq(काष्ठा scsi_device *sdev, पूर्णांक type)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा ibmvfc_event *evt, *found_evt, *temp;
	काष्ठा ibmvfc_queue *queues = vhost->scsi_scrqs.scrqs;
	अचिन्हित दीर्घ flags;
	पूर्णांक num_hwq, i;
	पूर्णांक fail = 0;
	LIST_HEAD(cancelq);
	u16 status;

	ENTER;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	num_hwq = vhost->scsi_scrqs.active_queues;
	क्रम (i = 0; i < num_hwq; i++) अणु
		spin_lock(queues[i].q_lock);
		spin_lock(&queues[i].l_lock);
		found_evt = शून्य;
		list_क्रम_each_entry(evt, &queues[i].sent, queue_list) अणु
			अगर (evt->cmnd && evt->cmnd->device == sdev) अणु
				found_evt = evt;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&queues[i].l_lock);

		अगर (found_evt && vhost->logged_in) अणु
			evt = ibmvfc_init_पंचांगf(&queues[i], sdev, type);
			evt->sync_iu = &queues[i].cancel_rsp;
			ibmvfc_send_event(evt, vhost, शेष_समयout);
			list_add_tail(&evt->cancel, &cancelq);
		पूर्ण

		spin_unlock(queues[i].q_lock);
	पूर्ण
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (list_empty(&cancelq)) अणु
		अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
			sdev_prपूर्णांकk(KERN_INFO, sdev, "No events found to cancel\n");
		वापस 0;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Cancelling outstanding commands.\n");

	list_क्रम_each_entry_safe(evt, temp, &cancelq, cancel) अणु
		रुको_क्रम_completion(&evt->comp);
		status = be16_to_cpu(evt->queue->cancel_rsp.mad_common.status);
		list_del(&evt->cancel);
		ibmvfc_मुक्त_event(evt);

		अगर (status != IBMVFC_MAD_SUCCESS) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev, "Cancel failed with rc=%x\n", status);
			चयन (status) अणु
			हाल IBMVFC_MAD_DRIVER_FAILED:
			हाल IBMVFC_MAD_CRQ_ERROR:
			/* Host adapter most likely going through reset, वापस success to
			 * the caller will रुको क्रम the command being cancelled to get वापसed
			 */
				अवरोध;
			शेष:
				fail = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fail)
		वापस -EIO;

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Successfully cancelled outstanding commands\n");
	LEAVE;
	वापस 0;
पूर्ण

अटल पूर्णांक ibmvfc_cancel_all_sq(काष्ठा scsi_device *sdev, पूर्णांक type)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा ibmvfc_event *evt, *found_evt;
	जोड़ ibmvfc_iu rsp;
	पूर्णांक rsp_rc = -EBUSY;
	अचिन्हित दीर्घ flags;
	u16 status;

	ENTER;
	found_evt = शून्य;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	spin_lock(&vhost->crq.l_lock);
	list_क्रम_each_entry(evt, &vhost->crq.sent, queue_list) अणु
		अगर (evt->cmnd && evt->cmnd->device == sdev) अणु
			found_evt = evt;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&vhost->crq.l_lock);

	अगर (!found_evt) अणु
		अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
			sdev_prपूर्णांकk(KERN_INFO, sdev, "No events found to cancel\n");
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		वापस 0;
	पूर्ण

	अगर (vhost->logged_in) अणु
		evt = ibmvfc_init_पंचांगf(&vhost->crq, sdev, type);
		evt->sync_iu = &rsp;
		rsp_rc = ibmvfc_send_event(evt, vhost, शेष_समयout);
	पूर्ण

	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (rsp_rc != 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, sdev, "Failed to send cancel event. rc=%d\n", rsp_rc);
		/* If failure is received, the host adapter is most likely going
		 through reset, वापस success so the caller will रुको क्रम the command
		 being cancelled to get वापसed */
		वापस 0;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Cancelling outstanding commands.\n");

	रुको_क्रम_completion(&evt->comp);
	status = be16_to_cpu(rsp.mad_common.status);
	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_मुक्त_event(evt);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (status != IBMVFC_MAD_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdev, "Cancel failed with rc=%x\n", status);
		चयन (status) अणु
		हाल IBMVFC_MAD_DRIVER_FAILED:
		हाल IBMVFC_MAD_CRQ_ERROR:
			/* Host adapter most likely going through reset, वापस success to
			 the caller will रुको क्रम the command being cancelled to get वापसed */
			वापस 0;
		शेष:
			वापस -EIO;
		पूर्ण;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Successfully cancelled outstanding commands\n");
	वापस 0;
पूर्ण

/**
 * ibmvfc_cancel_all - Cancel all outstanding commands to the device
 * @sdev:	scsi device to cancel commands
 * @type:	type of error recovery being perक्रमmed
 *
 * This sends a cancel to the VIOS क्रम the specअगरied device. This करोes
 * NOT send any पात to the actual device. That must be करोne separately.
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_cancel_all(काष्ठा scsi_device *sdev, पूर्णांक type)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);

	अगर (vhost->mq_enabled && vhost->using_channels)
		वापस ibmvfc_cancel_all_mq(sdev, type);
	अन्यथा
		वापस ibmvfc_cancel_all_sq(sdev, type);
पूर्ण

/**
 * ibmvfc_match_key - Match function क्रम specअगरied cancel key
 * @evt:	ibmvfc event काष्ठा
 * @key:	cancel key to match
 *
 * Returns:
 *	1 अगर event matches key / 0 अगर event करोes not match key
 **/
अटल पूर्णांक ibmvfc_match_key(काष्ठा ibmvfc_event *evt, व्योम *key)
अणु
	अचिन्हित दीर्घ cancel_key = (अचिन्हित दीर्घ)key;

	अगर (evt->crq.क्रमmat == IBMVFC_CMD_FORMAT &&
	    be32_to_cpu(evt->iu.cmd.cancel_key) == cancel_key)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ibmvfc_match_evt - Match function क्रम specअगरied event
 * @evt:	ibmvfc event काष्ठा
 * @match:	event to match
 *
 * Returns:
 *	1 अगर event matches key / 0 अगर event करोes not match key
 **/
अटल पूर्णांक ibmvfc_match_evt(काष्ठा ibmvfc_event *evt, व्योम *match)
अणु
	अगर (evt == match)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ibmvfc_पात_task_set - Abort outstanding commands to the device
 * @sdev:	scsi device to पात commands
 *
 * This sends an Abort Task Set to the VIOS क्रम the specअगरied device. This करोes
 * NOT send any cancel to the VIOS. That must be करोne separately.
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_पात_task_set(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा ibmvfc_cmd *पंचांगf;
	काष्ठा ibmvfc_event *evt, *found_evt;
	जोड़ ibmvfc_iu rsp_iu;
	काष्ठा ibmvfc_fcp_cmd_iu *iu;
	काष्ठा ibmvfc_fcp_rsp *fc_rsp = ibmvfc_get_fcp_rsp(vhost, &rsp_iu.cmd);
	पूर्णांक rc, rsp_rc = -EBUSY;
	अचिन्हित दीर्घ flags, समयout = IBMVFC_ABORT_TIMEOUT;
	पूर्णांक rsp_code = 0;

	found_evt = शून्य;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	spin_lock(&vhost->crq.l_lock);
	list_क्रम_each_entry(evt, &vhost->crq.sent, queue_list) अणु
		अगर (evt->cmnd && evt->cmnd->device == sdev) अणु
			found_evt = evt;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&vhost->crq.l_lock);

	अगर (!found_evt) अणु
		अगर (vhost->log_level > IBMVFC_DEFAULT_LOG_LEVEL)
			sdev_prपूर्णांकk(KERN_INFO, sdev, "No events found to abort\n");
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		वापस 0;
	पूर्ण

	अगर (vhost->state == IBMVFC_ACTIVE) अणु
		evt = ibmvfc_get_event(&vhost->crq);
		ibmvfc_init_event(evt, ibmvfc_sync_completion, IBMVFC_CMD_FORMAT);
		पंचांगf = ibmvfc_init_vfc_cmd(evt, sdev);
		iu = ibmvfc_get_fcp_iu(vhost, पंचांगf);

		अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN))
			पंचांगf->target_wwpn = cpu_to_be64(rport->port_name);
		iu->पंचांगf_flags = IBMVFC_ABORT_TASK_SET;
		पंचांगf->flags = cpu_to_be16((IBMVFC_NO_MEM_DESC | IBMVFC_TMF));
		evt->sync_iu = &rsp_iu;

		पंचांगf->correlation = cpu_to_be64((u64)evt);

		init_completion(&evt->comp);
		rsp_rc = ibmvfc_send_event(evt, vhost, शेष_समयout);
	पूर्ण

	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	अगर (rsp_rc != 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, sdev, "Failed to send abort. rc=%d\n", rsp_rc);
		वापस -EIO;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "Aborting outstanding commands\n");
	समयout = रुको_क्रम_completion_समयout(&evt->comp, समयout);

	अगर (!समयout) अणु
		rc = ibmvfc_cancel_all(sdev, 0);
		अगर (!rc) अणु
			rc = ibmvfc_रुको_क्रम_ops(vhost, sdev->hostdata, ibmvfc_match_key);
			अगर (rc == SUCCESS)
				rc = 0;
		पूर्ण

		अगर (rc) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev, "Cancel failed, resetting host\n");
			ibmvfc_reset_host(vhost);
			rsp_rc = -EIO;
			rc = ibmvfc_रुको_क्रम_ops(vhost, sdev->hostdata, ibmvfc_match_key);

			अगर (rc == SUCCESS)
				rsp_rc = 0;

			rc = ibmvfc_रुको_क्रम_ops(vhost, evt, ibmvfc_match_evt);
			अगर (rc != SUCCESS) अणु
				spin_lock_irqsave(vhost->host->host_lock, flags);
				ibmvfc_hard_reset_host(vhost);
				spin_unlock_irqrestore(vhost->host->host_lock, flags);
				rsp_rc = 0;
			पूर्ण

			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rsp_iu.cmd.status)
		rsp_code = ibmvfc_get_err_result(vhost, &rsp_iu.cmd);

	अगर (rsp_code) अणु
		अगर (fc_rsp->flags & FCP_RSP_LEN_VALID)
			rsp_code = fc_rsp->data.info.rsp_code;

		sdev_prपूर्णांकk(KERN_ERR, sdev, "Abort failed: %s (%x:%x) "
			    "flags: %x fcp_rsp: %x, scsi_status: %x\n",
			    ibmvfc_get_cmd_error(be16_to_cpu(rsp_iu.cmd.status), be16_to_cpu(rsp_iu.cmd.error)),
			    be16_to_cpu(rsp_iu.cmd.status), be16_to_cpu(rsp_iu.cmd.error), fc_rsp->flags, rsp_code,
			    fc_rsp->scsi_status);
		rsp_rc = -EIO;
	पूर्ण अन्यथा
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Abort successful\n");

out:
	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_मुक्त_event(evt);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस rsp_rc;
पूर्ण

/**
 * ibmvfc_eh_पात_handler - Abort a command
 * @cmd:	scsi command to पात
 *
 * Returns:
 *	SUCCESS / FAST_IO_FAIL / FAILED
 **/
अटल पूर्णांक ibmvfc_eh_पात_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	पूर्णांक cancel_rc, block_rc;
	पूर्णांक rc = FAILED;

	ENTER;
	block_rc = fc_block_scsi_eh(cmd);
	ibmvfc_रुको_जबतक_resetting(vhost);
	अगर (block_rc != FAST_IO_FAIL) अणु
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_ABORT_TASK_SET);
		ibmvfc_पात_task_set(sdev);
	पूर्ण अन्यथा
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_SUPPRESS_ABTS);

	अगर (!cancel_rc)
		rc = ibmvfc_रुको_क्रम_ops(vhost, sdev, ibmvfc_match_lun);

	अगर (block_rc == FAST_IO_FAIL && rc != FAILED)
		rc = FAST_IO_FAIL;

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_eh_device_reset_handler - Reset a single LUN
 * @cmd:	scsi command काष्ठा
 *
 * Returns:
 *	SUCCESS / FAST_IO_FAIL / FAILED
 **/
अटल पूर्णांक ibmvfc_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	पूर्णांक cancel_rc, block_rc, reset_rc = 0;
	पूर्णांक rc = FAILED;

	ENTER;
	block_rc = fc_block_scsi_eh(cmd);
	ibmvfc_रुको_जबतक_resetting(vhost);
	अगर (block_rc != FAST_IO_FAIL) अणु
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_LUN_RESET);
		reset_rc = ibmvfc_reset_device(sdev, IBMVFC_LUN_RESET, "LUN");
	पूर्ण अन्यथा
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_SUPPRESS_ABTS);

	अगर (!cancel_rc && !reset_rc)
		rc = ibmvfc_रुको_क्रम_ops(vhost, sdev, ibmvfc_match_lun);

	अगर (block_rc == FAST_IO_FAIL && rc != FAILED)
		rc = FAST_IO_FAIL;

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_dev_cancel_all_noreset - Device iterated cancel all function
 * @sdev:	scsi device काष्ठा
 * @data:	वापस code
 *
 **/
अटल व्योम ibmvfc_dev_cancel_all_noreset(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	अचिन्हित दीर्घ *rc = data;
	*rc |= ibmvfc_cancel_all(sdev, IBMVFC_TMF_SUPPRESS_ABTS);
पूर्ण

/**
 * ibmvfc_dev_cancel_all_reset - Device iterated cancel all function
 * @sdev:	scsi device काष्ठा
 * @data:	वापस code
 *
 **/
अटल व्योम ibmvfc_dev_cancel_all_reset(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	अचिन्हित दीर्घ *rc = data;
	*rc |= ibmvfc_cancel_all(sdev, IBMVFC_TMF_TGT_RESET);
पूर्ण

/**
 * ibmvfc_eh_target_reset_handler - Reset the target
 * @cmd:	scsi command काष्ठा
 *
 * Returns:
 *	SUCCESS / FAST_IO_FAIL / FAILED
 **/
अटल पूर्णांक ibmvfc_eh_target_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा ibmvfc_host *vhost = shost_priv(sdev->host);
	काष्ठा scsi_target *starget = scsi_target(sdev);
	पूर्णांक block_rc;
	पूर्णांक reset_rc = 0;
	पूर्णांक rc = FAILED;
	अचिन्हित दीर्घ cancel_rc = 0;

	ENTER;
	block_rc = fc_block_scsi_eh(cmd);
	ibmvfc_रुको_जबतक_resetting(vhost);
	अगर (block_rc != FAST_IO_FAIL) अणु
		starget_क्रम_each_device(starget, &cancel_rc, ibmvfc_dev_cancel_all_reset);
		reset_rc = ibmvfc_reset_device(sdev, IBMVFC_TARGET_RESET, "target");
	पूर्ण अन्यथा
		starget_क्रम_each_device(starget, &cancel_rc, ibmvfc_dev_cancel_all_noreset);

	अगर (!cancel_rc && !reset_rc)
		rc = ibmvfc_रुको_क्रम_ops(vhost, starget, ibmvfc_match_target);

	अगर (block_rc == FAST_IO_FAIL && rc != FAILED)
		rc = FAST_IO_FAIL;

	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_eh_host_reset_handler - Reset the connection to the server
 * @cmd:	काष्ठा scsi_cmnd having problems
 *
 **/
अटल पूर्णांक ibmvfc_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;
	काष्ठा ibmvfc_host *vhost = shost_priv(cmd->device->host);

	dev_err(vhost->dev, "Resetting connection due to error recovery\n");
	rc = ibmvfc_issue_fc_host_lip(vhost->host);

	वापस rc ? FAILED : SUCCESS;
पूर्ण

/**
 * ibmvfc_terminate_rport_io - Terminate all pending I/O to the rport.
 * @rport:		rport काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_terminate_rport_io(काष्ठा fc_rport *rport)
अणु
	काष्ठा Scsi_Host *shost = rport_to_shost(rport);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	काष्ठा fc_rport *dev_rport;
	काष्ठा scsi_device *sdev;
	काष्ठा ibmvfc_target *tgt;
	अचिन्हित दीर्घ rc, flags;
	अचिन्हित पूर्णांक found;

	ENTER;
	shost_क्रम_each_device(sdev, shost) अणु
		dev_rport = starget_to_rport(scsi_target(sdev));
		अगर (dev_rport != rport)
			जारी;
		ibmvfc_cancel_all(sdev, IBMVFC_TMF_SUPPRESS_ABTS);
	पूर्ण

	rc = ibmvfc_रुको_क्रम_ops(vhost, rport, ibmvfc_match_rport);

	अगर (rc == FAILED)
		ibmvfc_issue_fc_host_lip(shost);

	spin_lock_irqsave(shost->host_lock, flags);
	found = 0;
	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->scsi_id == rport->port_id) अणु
			found++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found && tgt->action == IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT) अणु
		/*
		 * If we get here, that means we previously attempted to send
		 * an implicit logout to the target but it failed, most likely
		 * due to I/O being pending, so we need to send it again
		 */
		ibmvfc_del_tgt(tgt);
		ibmvfc_reinit_host(vhost);
	पूर्ण

	spin_unlock_irqrestore(shost->host_lock, flags);
	LEAVE;
पूर्ण

अटल स्थिर काष्ठा ibmvfc_async_desc ae_desc [] = अणु
	अणु "PLOGI",	IBMVFC_AE_ELS_PLOGI,	IBMVFC_DEFAULT_LOG_LEVEL + 1 पूर्ण,
	अणु "LOGO",	IBMVFC_AE_ELS_LOGO,	IBMVFC_DEFAULT_LOG_LEVEL + 1 पूर्ण,
	अणु "PRLO",	IBMVFC_AE_ELS_PRLO,	IBMVFC_DEFAULT_LOG_LEVEL + 1 पूर्ण,
	अणु "N-Port SCN",	IBMVFC_AE_SCN_NPORT,	IBMVFC_DEFAULT_LOG_LEVEL + 1 पूर्ण,
	अणु "Group SCN",	IBMVFC_AE_SCN_GROUP,	IBMVFC_DEFAULT_LOG_LEVEL + 1 पूर्ण,
	अणु "Domain SCN",	IBMVFC_AE_SCN_DOMAIN,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Fabric SCN",	IBMVFC_AE_SCN_FABRIC,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Link Up",	IBMVFC_AE_LINK_UP,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Link Down",	IBMVFC_AE_LINK_DOWN,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Link Dead",	IBMVFC_AE_LINK_DEAD,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Halt",	IBMVFC_AE_HALT,		IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Resume",	IBMVFC_AE_RESUME,	IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
	अणु "Adapter Failed", IBMVFC_AE_ADAPTER_FAILED, IBMVFC_DEFAULT_LOG_LEVEL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ibmvfc_async_desc unknown_ae = अणु
	"Unknown async", 0, IBMVFC_DEFAULT_LOG_LEVEL
पूर्ण;

/**
 * ibmvfc_get_ae_desc - Get text description क्रम async event
 * @ae:	async event
 *
 **/
अटल स्थिर काष्ठा ibmvfc_async_desc *ibmvfc_get_ae_desc(u64 ae)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ae_desc); i++)
		अगर (ae_desc[i].ae == ae)
			वापस &ae_desc[i];

	वापस &unknown_ae;
पूर्ण

अटल स्थिर काष्ठा अणु
	क्रमागत ibmvfc_ae_link_state state;
	स्थिर अक्षर *desc;
पूर्ण link_desc [] = अणु
	अणु IBMVFC_AE_LS_LINK_UP,		" link up" पूर्ण,
	अणु IBMVFC_AE_LS_LINK_BOUNCED,	" link bounced" पूर्ण,
	अणु IBMVFC_AE_LS_LINK_DOWN,	" link down" पूर्ण,
	अणु IBMVFC_AE_LS_LINK_DEAD,	" link dead" पूर्ण,
पूर्ण;

/**
 * ibmvfc_get_link_state - Get text description क्रम link state
 * @state:	link state
 *
 **/
अटल स्थिर अक्षर *ibmvfc_get_link_state(क्रमागत ibmvfc_ae_link_state state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(link_desc); i++)
		अगर (link_desc[i].state == state)
			वापस link_desc[i].desc;

	वापस "";
पूर्ण

/**
 * ibmvfc_handle_async - Handle an async event from the adapter
 * @crq:	crq to process
 * @vhost:	ibmvfc host काष्ठा
 *
 **/
अटल व्योम ibmvfc_handle_async(काष्ठा ibmvfc_async_crq *crq,
				काष्ठा ibmvfc_host *vhost)
अणु
	स्थिर काष्ठा ibmvfc_async_desc *desc = ibmvfc_get_ae_desc(be64_to_cpu(crq->event));
	काष्ठा ibmvfc_target *tgt;

	ibmvfc_log(vhost, desc->log_level, "%s event received. scsi_id: %llx, wwpn: %llx,"
		   " node_name: %llx%s\n", desc->desc, be64_to_cpu(crq->scsi_id),
		   be64_to_cpu(crq->wwpn), be64_to_cpu(crq->node_name),
		   ibmvfc_get_link_state(crq->link_state));

	चयन (be64_to_cpu(crq->event)) अणु
	हाल IBMVFC_AE_RESUME:
		चयन (crq->link_state) अणु
		हाल IBMVFC_AE_LS_LINK_DOWN:
			ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
			अवरोध;
		हाल IBMVFC_AE_LS_LINK_DEAD:
			ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
			अवरोध;
		हाल IBMVFC_AE_LS_LINK_UP:
		हाल IBMVFC_AE_LS_LINK_BOUNCED:
		शेष:
			vhost->events_to_log |= IBMVFC_AE_LINKUP;
			vhost->delay_init = 1;
			__ibmvfc_reset_host(vhost);
			अवरोध;
		पूर्ण

		अवरोध;
	हाल IBMVFC_AE_LINK_UP:
		vhost->events_to_log |= IBMVFC_AE_LINKUP;
		vhost->delay_init = 1;
		__ibmvfc_reset_host(vhost);
		अवरोध;
	हाल IBMVFC_AE_SCN_FABRIC:
	हाल IBMVFC_AE_SCN_DOMAIN:
		vhost->events_to_log |= IBMVFC_AE_RSCN;
		अगर (vhost->state < IBMVFC_HALTED) अणु
			vhost->delay_init = 1;
			__ibmvfc_reset_host(vhost);
		पूर्ण
		अवरोध;
	हाल IBMVFC_AE_SCN_NPORT:
	हाल IBMVFC_AE_SCN_GROUP:
		vhost->events_to_log |= IBMVFC_AE_RSCN;
		ibmvfc_reinit_host(vhost);
		अवरोध;
	हाल IBMVFC_AE_ELS_LOGO:
	हाल IBMVFC_AE_ELS_PRLO:
	हाल IBMVFC_AE_ELS_PLOGI:
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (!crq->scsi_id && !crq->wwpn && !crq->node_name)
				अवरोध;
			अगर (crq->scsi_id && cpu_to_be64(tgt->scsi_id) != crq->scsi_id)
				जारी;
			अगर (crq->wwpn && cpu_to_be64(tgt->ids.port_name) != crq->wwpn)
				जारी;
			अगर (crq->node_name && cpu_to_be64(tgt->ids.node_name) != crq->node_name)
				जारी;
			अगर (tgt->need_login && be64_to_cpu(crq->event) == IBMVFC_AE_ELS_LOGO)
				tgt->logo_rcvd = 1;
			अगर (!tgt->need_login || be64_to_cpu(crq->event) == IBMVFC_AE_ELS_PLOGI) अणु
				ibmvfc_del_tgt(tgt);
				ibmvfc_reinit_host(vhost);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IBMVFC_AE_LINK_DOWN:
	हाल IBMVFC_AE_ADAPTER_FAILED:
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
		अवरोध;
	हाल IBMVFC_AE_LINK_DEAD:
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		अवरोध;
	हाल IBMVFC_AE_HALT:
		ibmvfc_link_करोwn(vhost, IBMVFC_HALTED);
		अवरोध;
	शेष:
		dev_err(vhost->dev, "Unknown async event received: %lld\n", crq->event);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ibmvfc_handle_crq - Handles and मुक्तs received events in the CRQ
 * @crq:	Command/Response queue
 * @vhost:	ibmvfc host काष्ठा
 * @evt_करोneq:	Event करोne queue
 *
**/
अटल व्योम ibmvfc_handle_crq(काष्ठा ibmvfc_crq *crq, काष्ठा ibmvfc_host *vhost,
			      काष्ठा list_head *evt_करोneq)
अणु
	दीर्घ rc;
	काष्ठा ibmvfc_event *evt = (काष्ठा ibmvfc_event *)be64_to_cpu(crq->ioba);

	चयन (crq->valid) अणु
	हाल IBMVFC_CRQ_INIT_RSP:
		चयन (crq->क्रमmat) अणु
		हाल IBMVFC_CRQ_INIT:
			dev_info(vhost->dev, "Partner initialized\n");
			/* Send back a response */
			rc = ibmvfc_send_crq_init_complete(vhost);
			अगर (rc == 0)
				ibmvfc_init_host(vhost);
			अन्यथा
				dev_err(vhost->dev, "Unable to send init rsp. rc=%ld\n", rc);
			अवरोध;
		हाल IBMVFC_CRQ_INIT_COMPLETE:
			dev_info(vhost->dev, "Partner initialization complete\n");
			ibmvfc_init_host(vhost);
			अवरोध;
		शेष:
			dev_err(vhost->dev, "Unknown crq message type: %d\n", crq->क्रमmat);
		पूर्ण
		वापस;
	हाल IBMVFC_CRQ_XPORT_EVENT:
		vhost->state = IBMVFC_NO_CRQ;
		vhost->logged_in = 0;
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_NONE);
		अगर (crq->क्रमmat == IBMVFC_PARTITION_MIGRATED) अणु
			/* We need to re-setup the पूर्णांकerpartition connection */
			dev_info(vhost->dev, "Partition migrated, Re-enabling adapter\n");
			vhost->client_migrated = 1;
			ibmvfc_purge_requests(vhost, DID_REQUEUE);
			ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_REENABLE);
		पूर्ण अन्यथा अगर (crq->क्रमmat == IBMVFC_PARTNER_FAILED || crq->क्रमmat == IBMVFC_PARTNER_DEREGISTER) अणु
			dev_err(vhost->dev, "Host partner adapter deregistered or failed (rc=%d)\n", crq->क्रमmat);
			ibmvfc_purge_requests(vhost, DID_ERROR);
			ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_RESET);
		पूर्ण अन्यथा अणु
			dev_err(vhost->dev, "Received unknown transport event from partner (rc=%d)\n", crq->क्रमmat);
		पूर्ण
		वापस;
	हाल IBMVFC_CRQ_CMD_RSP:
		अवरोध;
	शेष:
		dev_err(vhost->dev, "Got an invalid message type 0x%02x\n", crq->valid);
		वापस;
	पूर्ण

	अगर (crq->क्रमmat == IBMVFC_ASYNC_EVENT)
		वापस;

	/* The only kind of payload CRQs we should get are responses to
	 * things we send. Make sure this response is to something we
	 * actually sent
	 */
	अगर (unlikely(!ibmvfc_valid_event(&vhost->crq.evt_pool, evt))) अणु
		dev_err(vhost->dev, "Returned correlation_token 0x%08llx is invalid!\n",
			crq->ioba);
		वापस;
	पूर्ण

	अगर (unlikely(atomic_पढ़ो(&evt->मुक्त))) अणु
		dev_err(vhost->dev, "Received duplicate correlation_token 0x%08llx!\n",
			crq->ioba);
		वापस;
	पूर्ण

	spin_lock(&evt->queue->l_lock);
	list_move_tail(&evt->queue_list, evt_करोneq);
	spin_unlock(&evt->queue->l_lock);
पूर्ण

/**
 * ibmvfc_scan_finished - Check अगर the device scan is करोne.
 * @shost:	scsi host काष्ठा
 * @समय:	current elapsed समय
 *
 * Returns:
 *	0 अगर scan is not करोne / 1 अगर scan is करोne
 **/
अटल पूर्णांक ibmvfc_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	पूर्णांक करोne = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (समय >= (init_समयout * HZ)) अणु
		dev_info(vhost->dev, "Scan taking longer than %d seconds, "
			 "continuing initialization\n", init_समयout);
		करोne = 1;
	पूर्ण

	अगर (vhost->scan_complete)
		करोne = 1;
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस करोne;
पूर्ण

/**
 * ibmvfc_slave_alloc - Setup the device's task set value
 * @sdev:	काष्ठा scsi_device device to configure
 *
 * Set the device's task set value so that error handling works as
 * expected.
 *
 * Returns:
 *	0 on success / -ENXIO अगर device करोes not exist
 **/
अटल पूर्णांक ibmvfc_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	spin_lock_irqsave(shost->host_lock, flags);
	sdev->hostdata = (व्योम *)(अचिन्हित दीर्घ)vhost->task_set++;
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस 0;
पूर्ण

/**
 * ibmvfc_target_alloc - Setup the target's task set value
 * @starget:	काष्ठा scsi_target
 *
 * Set the target's task set value so that error handling works as
 * expected.
 *
 * Returns:
 *	0 on success / -ENXIO अगर device करोes not exist
 **/
अटल पूर्णांक ibmvfc_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	starget->hostdata = (व्योम *)(अचिन्हित दीर्घ)vhost->task_set++;
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस 0;
पूर्ण

/**
 * ibmvfc_slave_configure - Configure the device
 * @sdev:	काष्ठा scsi_device device to configure
 *
 * Enable allow_restart क्रम a device अगर it is a disk. Adjust the
 * queue_depth here also.
 *
 * Returns:
 *	0
 **/
अटल पूर्णांक ibmvfc_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	अगर (sdev->type == TYPE_DISK) अणु
		sdev->allow_restart = 1;
		blk_queue_rq_समयout(sdev->request_queue, 120 * HZ);
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस 0;
पूर्ण

/**
 * ibmvfc_change_queue_depth - Change the device's queue depth
 * @sdev:	scsi device काष्ठा
 * @qdepth:	depth to set
 *
 * Return value:
 * 	actual depth set
 **/
अटल पूर्णांक ibmvfc_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	अगर (qdepth > IBMVFC_MAX_CMDS_PER_LUN)
		qdepth = IBMVFC_MAX_CMDS_PER_LUN;

	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_partition_name(काष्ठा device *dev,
						 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			vhost->login_buf->resp.partition_name);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_device_name(काष्ठा device *dev,
					    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			vhost->login_buf->resp.device_name);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_loc_code(काष्ठा device *dev,
					 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			vhost->login_buf->resp.port_loc_code);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_drc_name(काष्ठा device *dev,
					 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			vhost->login_buf->resp.drc_name);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_npiv_version(काष्ठा device *dev,
					     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", be32_to_cpu(vhost->login_buf->resp.version));
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_host_capabilities(काष्ठा device *dev,
					     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	वापस snम_लिखो(buf, PAGE_SIZE, "%llx\n", be64_to_cpu(vhost->login_buf->resp.capabilities));
पूर्ण

/**
 * ibmvfc_show_log_level - Show the adapter's error logging level
 * @dev:	class device काष्ठा
 * @attr:	unused
 * @buf:	buffer
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ibmvfc_show_log_level(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(shost->host_lock, flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%d\n", vhost->log_level);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस len;
पूर्ण

/**
 * ibmvfc_store_log_level - Change the adapter's error logging level
 * @dev:	class device काष्ठा
 * @attr:	unused
 * @buf:	buffer
 * @count:      buffer size
 *
 * Return value:
 * 	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ibmvfc_store_log_level(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	vhost->log_level = simple_म_से_अदीर्घ(buf, शून्य, 10);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार ibmvfc_show_scsi_channels(काष्ठा device *dev,
					 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक len;

	spin_lock_irqsave(shost->host_lock, flags);
	len = snम_लिखो(buf, PAGE_SIZE, "%d\n", vhost->client_scsi_channels);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस len;
पूर्ण

अटल sमाप_प्रकार ibmvfc_store_scsi_channels(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक channels;

	spin_lock_irqsave(shost->host_lock, flags);
	channels = simple_म_से_अदीर्घ(buf, शून्य, 10);
	vhost->client_scsi_channels = min(channels, nr_scsi_hw_queues);
	ibmvfc_hard_reset_host(vhost);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस म_माप(buf);
पूर्ण

अटल DEVICE_ATTR(partition_name, S_IRUGO, ibmvfc_show_host_partition_name, शून्य);
अटल DEVICE_ATTR(device_name, S_IRUGO, ibmvfc_show_host_device_name, शून्य);
अटल DEVICE_ATTR(port_loc_code, S_IRUGO, ibmvfc_show_host_loc_code, शून्य);
अटल DEVICE_ATTR(drc_name, S_IRUGO, ibmvfc_show_host_drc_name, शून्य);
अटल DEVICE_ATTR(npiv_version, S_IRUGO, ibmvfc_show_host_npiv_version, शून्य);
अटल DEVICE_ATTR(capabilities, S_IRUGO, ibmvfc_show_host_capabilities, शून्य);
अटल DEVICE_ATTR(log_level, S_IRUGO | S_IWUSR,
		   ibmvfc_show_log_level, ibmvfc_store_log_level);
अटल DEVICE_ATTR(nr_scsi_channels, S_IRUGO | S_IWUSR,
		   ibmvfc_show_scsi_channels, ibmvfc_store_scsi_channels);

#अगर_घोषित CONFIG_SCSI_IBMVFC_TRACE
/**
 * ibmvfc_पढ़ो_trace - Dump the adapter trace
 * @filp:		खोलो sysfs file
 * @kobj:		kobject काष्ठा
 * @bin_attr:	bin_attribute काष्ठा
 * @buf:		buffer
 * @off:		offset
 * @count:		buffer size
 *
 * Return value:
 *	number of bytes prपूर्णांकed to buffer
 **/
अटल sमाप_प्रकार ibmvfc_पढ़ो_trace(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvfc_host *vhost = shost_priv(shost);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक size = IBMVFC_TRACE_SIZE;
	अक्षर *src = (अक्षर *)vhost->trace;

	अगर (off > size)
		वापस 0;
	अगर (off + count > size) अणु
		size -= off;
		count = size;
	पूर्ण

	spin_lock_irqsave(shost->host_lock, flags);
	स_नकल(buf, &src[off], count);
	spin_unlock_irqrestore(shost->host_lock, flags);
	वापस count;
पूर्ण

अटल काष्ठा bin_attribute ibmvfc_trace_attr = अणु
	.attr =	अणु
		.name = "trace",
		.mode = S_IRUGO,
	पूर्ण,
	.size = 0,
	.पढ़ो = ibmvfc_पढ़ो_trace,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा device_attribute *ibmvfc_attrs[] = अणु
	&dev_attr_partition_name,
	&dev_attr_device_name,
	&dev_attr_port_loc_code,
	&dev_attr_drc_name,
	&dev_attr_npiv_version,
	&dev_attr_capabilities,
	&dev_attr_log_level,
	&dev_attr_nr_scsi_channels,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "IBM POWER Virtual FC Adapter",
	.proc_name = IBMVFC_NAME,
	.queuecommand = ibmvfc_queuecommand,
	.eh_समयd_out = fc_eh_समयd_out,
	.eh_पात_handler = ibmvfc_eh_पात_handler,
	.eh_device_reset_handler = ibmvfc_eh_device_reset_handler,
	.eh_target_reset_handler = ibmvfc_eh_target_reset_handler,
	.eh_host_reset_handler = ibmvfc_eh_host_reset_handler,
	.slave_alloc = ibmvfc_slave_alloc,
	.slave_configure = ibmvfc_slave_configure,
	.target_alloc = ibmvfc_target_alloc,
	.scan_finished = ibmvfc_scan_finished,
	.change_queue_depth = ibmvfc_change_queue_depth,
	.cmd_per_lun = 16,
	.can_queue = IBMVFC_MAX_REQUESTS_DEFAULT,
	.this_id = -1,
	.sg_tablesize = SG_ALL,
	.max_sectors = IBMVFC_MAX_SECTORS,
	.shost_attrs = ibmvfc_attrs,
	.track_queue_depth = 1,
	.host_tagset = 1,
पूर्ण;

/**
 * ibmvfc_next_async_crq - Returns the next entry in async queue
 * @vhost:	ibmvfc host काष्ठा
 *
 * Returns:
 *	Poपूर्णांकer to next entry in queue / शून्य अगर empty
 **/
अटल काष्ठा ibmvfc_async_crq *ibmvfc_next_async_crq(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_queue *async_crq = &vhost->async_crq;
	काष्ठा ibmvfc_async_crq *crq;

	crq = &async_crq->msgs.async[async_crq->cur];
	अगर (crq->valid & 0x80) अणु
		अगर (++async_crq->cur == async_crq->size)
			async_crq->cur = 0;
		rmb();
	पूर्ण अन्यथा
		crq = शून्य;

	वापस crq;
पूर्ण

/**
 * ibmvfc_next_crq - Returns the next entry in message queue
 * @vhost:	ibmvfc host काष्ठा
 *
 * Returns:
 *	Poपूर्णांकer to next entry in queue / शून्य अगर empty
 **/
अटल काष्ठा ibmvfc_crq *ibmvfc_next_crq(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_queue *queue = &vhost->crq;
	काष्ठा ibmvfc_crq *crq;

	crq = &queue->msgs.crq[queue->cur];
	अगर (crq->valid & 0x80) अणु
		अगर (++queue->cur == queue->size)
			queue->cur = 0;
		rmb();
	पूर्ण अन्यथा
		crq = शून्य;

	वापस crq;
पूर्ण

/**
 * ibmvfc_पूर्णांकerrupt - Interrupt handler
 * @irq:		number of irq to handle, not used
 * @dev_instance: ibmvfc_host that received पूर्णांकerrupt
 *
 * Returns:
 *	IRQ_HANDLED
 **/
अटल irqवापस_t ibmvfc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ibmvfc_host *vhost = (काष्ठा ibmvfc_host *)dev_instance;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	vio_disable_पूर्णांकerrupts(to_vio_dev(vhost->dev));
	tasklet_schedule(&vhost->tasklet);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ibmvfc_tasklet - Interrupt handler tasklet
 * @data:		ibmvfc host काष्ठा
 *
 * Returns:
 *	Nothing
 **/
अटल व्योम ibmvfc_tasklet(व्योम *data)
अणु
	काष्ठा ibmvfc_host *vhost = data;
	काष्ठा vio_dev *vdev = to_vio_dev(vhost->dev);
	काष्ठा ibmvfc_crq *crq;
	काष्ठा ibmvfc_async_crq *async;
	काष्ठा ibmvfc_event *evt, *temp;
	अचिन्हित दीर्घ flags;
	पूर्णांक करोne = 0;
	LIST_HEAD(evt_करोneq);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	spin_lock(vhost->crq.q_lock);
	जबतक (!करोne) अणु
		/* Pull all the valid messages off the async CRQ */
		जबतक ((async = ibmvfc_next_async_crq(vhost)) != शून्य) अणु
			ibmvfc_handle_async(async, vhost);
			async->valid = 0;
			wmb();
		पूर्ण

		/* Pull all the valid messages off the CRQ */
		जबतक ((crq = ibmvfc_next_crq(vhost)) != शून्य) अणु
			ibmvfc_handle_crq(crq, vhost, &evt_करोneq);
			crq->valid = 0;
			wmb();
		पूर्ण

		vio_enable_पूर्णांकerrupts(vdev);
		अगर ((async = ibmvfc_next_async_crq(vhost)) != शून्य) अणु
			vio_disable_पूर्णांकerrupts(vdev);
			ibmvfc_handle_async(async, vhost);
			async->valid = 0;
			wmb();
		पूर्ण अन्यथा अगर ((crq = ibmvfc_next_crq(vhost)) != शून्य) अणु
			vio_disable_पूर्णांकerrupts(vdev);
			ibmvfc_handle_crq(crq, vhost, &evt_करोneq);
			crq->valid = 0;
			wmb();
		पूर्ण अन्यथा
			करोne = 1;
	पूर्ण

	spin_unlock(vhost->crq.q_lock);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	list_क्रम_each_entry_safe(evt, temp, &evt_करोneq, queue_list) अणु
		del_समयr(&evt->समयr);
		list_del(&evt->queue_list);
		ibmvfc_trc_end(evt);
		evt->करोne(evt);
	पूर्ण
पूर्ण

अटल पूर्णांक ibmvfc_toggle_scrq_irq(काष्ठा ibmvfc_queue *scrq, पूर्णांक enable)
अणु
	काष्ठा device *dev = scrq->vhost->dev;
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	अचिन्हित दीर्घ rc;
	पूर्णांक irq_action = H_ENABLE_VIO_INTERRUPT;

	अगर (!enable)
		irq_action = H_DISABLE_VIO_INTERRUPT;

	rc = plpar_hcall_norets(H_VIOCTL, vdev->unit_address, irq_action,
				scrq->hw_irq, 0, 0);

	अगर (rc)
		dev_err(dev, "Couldn't %s sub-crq[%lu] irq. rc=%ld\n",
			enable ? "enable" : "disable", scrq->hwq_id, rc);

	वापस rc;
पूर्ण

अटल व्योम ibmvfc_handle_scrq(काष्ठा ibmvfc_crq *crq, काष्ठा ibmvfc_host *vhost,
			       काष्ठा list_head *evt_करोneq)
अणु
	काष्ठा ibmvfc_event *evt = (काष्ठा ibmvfc_event *)be64_to_cpu(crq->ioba);

	चयन (crq->valid) अणु
	हाल IBMVFC_CRQ_CMD_RSP:
		अवरोध;
	हाल IBMVFC_CRQ_XPORT_EVENT:
		वापस;
	शेष:
		dev_err(vhost->dev, "Got and invalid message type 0x%02x\n", crq->valid);
		वापस;
	पूर्ण

	/* The only kind of payload CRQs we should get are responses to
	 * things we send. Make sure this response is to something we
	 * actually sent
	 */
	अगर (unlikely(!ibmvfc_valid_event(&evt->queue->evt_pool, evt))) अणु
		dev_err(vhost->dev, "Returned correlation_token 0x%08llx is invalid!\n",
			crq->ioba);
		वापस;
	पूर्ण

	अगर (unlikely(atomic_पढ़ो(&evt->मुक्त))) अणु
		dev_err(vhost->dev, "Received duplicate correlation_token 0x%08llx!\n",
			crq->ioba);
		वापस;
	पूर्ण

	spin_lock(&evt->queue->l_lock);
	list_move_tail(&evt->queue_list, evt_करोneq);
	spin_unlock(&evt->queue->l_lock);
पूर्ण

अटल काष्ठा ibmvfc_crq *ibmvfc_next_scrq(काष्ठा ibmvfc_queue *scrq)
अणु
	काष्ठा ibmvfc_crq *crq;

	crq = &scrq->msgs.scrq[scrq->cur].crq;
	अगर (crq->valid & 0x80) अणु
		अगर (++scrq->cur == scrq->size)
			scrq->cur = 0;
		rmb();
	पूर्ण अन्यथा
		crq = शून्य;

	वापस crq;
पूर्ण

अटल व्योम ibmvfc_drain_sub_crq(काष्ठा ibmvfc_queue *scrq)
अणु
	काष्ठा ibmvfc_crq *crq;
	काष्ठा ibmvfc_event *evt, *temp;
	अचिन्हित दीर्घ flags;
	पूर्णांक करोne = 0;
	LIST_HEAD(evt_करोneq);

	spin_lock_irqsave(scrq->q_lock, flags);
	जबतक (!करोne) अणु
		जबतक ((crq = ibmvfc_next_scrq(scrq)) != शून्य) अणु
			ibmvfc_handle_scrq(crq, scrq->vhost, &evt_करोneq);
			crq->valid = 0;
			wmb();
		पूर्ण

		ibmvfc_toggle_scrq_irq(scrq, 1);
		अगर ((crq = ibmvfc_next_scrq(scrq)) != शून्य) अणु
			ibmvfc_toggle_scrq_irq(scrq, 0);
			ibmvfc_handle_scrq(crq, scrq->vhost, &evt_करोneq);
			crq->valid = 0;
			wmb();
		पूर्ण अन्यथा
			करोne = 1;
	पूर्ण
	spin_unlock_irqrestore(scrq->q_lock, flags);

	list_क्रम_each_entry_safe(evt, temp, &evt_करोneq, queue_list) अणु
		del_समयr(&evt->समयr);
		list_del(&evt->queue_list);
		ibmvfc_trc_end(evt);
		evt->करोne(evt);
	पूर्ण
पूर्ण

अटल irqवापस_t ibmvfc_पूर्णांकerrupt_scsi(पूर्णांक irq, व्योम *scrq_instance)
अणु
	काष्ठा ibmvfc_queue *scrq = (काष्ठा ibmvfc_queue *)scrq_instance;

	ibmvfc_toggle_scrq_irq(scrq, 0);
	ibmvfc_drain_sub_crq(scrq);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ibmvfc_init_tgt - Set the next init job step क्रम the target
 * @tgt:		ibmvfc target काष्ठा
 * @job_step:	job step to perक्रमm
 *
 **/
अटल व्योम ibmvfc_init_tgt(काष्ठा ibmvfc_target *tgt,
			    व्योम (*job_step) (काष्ठा ibmvfc_target *))
अणु
	अगर (!ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT))
		tgt->job_step = job_step;
	wake_up(&tgt->vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_retry_tgt_init - Attempt to retry a step in target initialization
 * @tgt:		ibmvfc target काष्ठा
 * @job_step:	initialization job step
 *
 * Returns: 1 अगर step will be retried / 0 अगर not
 *
 **/
अटल पूर्णांक ibmvfc_retry_tgt_init(काष्ठा ibmvfc_target *tgt,
				  व्योम (*job_step) (काष्ठा ibmvfc_target *))
अणु
	अगर (++tgt->init_retries > IBMVFC_MAX_TGT_INIT_RETRIES) अणु
		ibmvfc_del_tgt(tgt);
		wake_up(&tgt->vhost->work_रुको_q);
		वापस 0;
	पूर्ण अन्यथा
		ibmvfc_init_tgt(tgt, job_step);
	वापस 1;
पूर्ण

/* Defined in FC-LS */
अटल स्थिर काष्ठा अणु
	पूर्णांक code;
	पूर्णांक retry;
	पूर्णांक logged_in;
पूर्ण prli_rsp [] = अणु
	अणु 0, 1, 0 पूर्ण,
	अणु 1, 0, 1 पूर्ण,
	अणु 2, 1, 0 पूर्ण,
	अणु 3, 1, 0 पूर्ण,
	अणु 4, 0, 0 पूर्ण,
	अणु 5, 0, 0 पूर्ण,
	अणु 6, 0, 1 पूर्ण,
	अणु 7, 0, 0 पूर्ण,
	अणु 8, 1, 0 पूर्ण,
पूर्ण;

/**
 * ibmvfc_get_prli_rsp - Find PRLI response index
 * @flags:	PRLI response flags
 *
 **/
अटल पूर्णांक ibmvfc_get_prli_rsp(u16 flags)
अणु
	पूर्णांक i;
	पूर्णांक code = (flags & 0x0f00) >> 8;

	क्रम (i = 0; i < ARRAY_SIZE(prli_rsp); i++)
		अगर (prli_rsp[i].code == code)
			वापस i;

	वापस 0;
पूर्ण

/**
 * ibmvfc_tgt_prli_करोne - Completion handler क्रम Process Login
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_prli_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_process_login *rsp = &evt->xfer_iu->prli;
	काष्ठा ibmvfc_prli_svc_parms *parms = &rsp->parms;
	u32 status = be16_to_cpu(rsp->common.status);
	पूर्णांक index, level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_thपढ़ोs--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Process Login succeeded: %X %02X %04X\n",
			parms->type, parms->flags, parms->service_parms);

		अगर (parms->type == IBMVFC_SCSI_FCP_TYPE) अणु
			index = ibmvfc_get_prli_rsp(be16_to_cpu(parms->flags));
			अगर (prli_rsp[index].logged_in) अणु
				अगर (be16_to_cpu(parms->flags) & IBMVFC_PRLI_EST_IMG_PAIR) अणु
					tgt->need_login = 0;
					tgt->ids.roles = 0;
					अगर (be32_to_cpu(parms->service_parms) & IBMVFC_PRLI_TARGET_FUNC)
						tgt->ids.roles |= FC_PORT_ROLE_FCP_TARGET;
					अगर (be32_to_cpu(parms->service_parms) & IBMVFC_PRLI_INITIATOR_FUNC)
						tgt->ids.roles |= FC_PORT_ROLE_FCP_INITIATOR;
					tgt->add_rport = 1;
				पूर्ण अन्यथा
					ibmvfc_del_tgt(tgt);
			पूर्ण अन्यथा अगर (prli_rsp[index].retry)
				ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
			अन्यथा
				ibmvfc_del_tgt(tgt);
		पूर्ण अन्यथा
			ibmvfc_del_tgt(tgt);
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	हाल IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		अगर ((be16_to_cpu(rsp->status) & IBMVFC_VIOS_FAILURE) &&
		     be16_to_cpu(rsp->error) == IBMVFC_PLOGI_REQUIRED)
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		अन्यथा अगर (tgt->logo_rcvd)
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		अन्यथा अगर (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_prli);
		अन्यथा
			ibmvfc_del_tgt(tgt);

		tgt_log(tgt, level, "Process Login failed: %s (%x:%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
			be16_to_cpu(rsp->status), be16_to_cpu(rsp->error), status);
		अवरोध;
	पूर्ण

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_tgt_send_prli - Send a process login
 * @tgt:	ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_send_prli(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_process_login *prli;
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	vhost->discovery_thपढ़ोs++;
	ibmvfc_init_event(evt, ibmvfc_tgt_prli_करोne, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;
	prli = &evt->iu.prli;
	स_रखो(prli, 0, माप(*prli));
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN)) अणु
		prli->common.version = cpu_to_be32(2);
		prli->target_wwpn = cpu_to_be64(tgt->wwpn);
	पूर्ण अन्यथा अणु
		prli->common.version = cpu_to_be32(1);
	पूर्ण
	prli->common.opcode = cpu_to_be32(IBMVFC_PROCESS_LOGIN);
	prli->common.length = cpu_to_be16(माप(*prli));
	prli->scsi_id = cpu_to_be64(tgt->scsi_id);

	prli->parms.type = IBMVFC_SCSI_FCP_TYPE;
	prli->parms.flags = cpu_to_be16(IBMVFC_PRLI_EST_IMG_PAIR);
	prli->parms.service_parms = cpu_to_be32(IBMVFC_PRLI_INITIATOR_FUNC);
	prli->parms.service_parms |= cpu_to_be32(IBMVFC_PRLI_READ_FCP_XFER_RDY_DISABLED);

	अगर (cls3_error)
		prli->parms.service_parms |= cpu_to_be32(IBMVFC_PRLI_RETRY);

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent process login\n");
पूर्ण

/**
 * ibmvfc_tgt_plogi_करोne - Completion handler क्रम Port Login
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_plogi_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_port_login *rsp = &evt->xfer_iu->plogi;
	u32 status = be16_to_cpu(rsp->common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_thपढ़ोs--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Port Login succeeded\n");
		अगर (tgt->ids.port_name &&
		    tgt->ids.port_name != wwn_to_u64(rsp->service_parms.port_name)) अणु
			vhost->reinit = 1;
			tgt_dbg(tgt, "Port re-init required\n");
			अवरोध;
		पूर्ण
		tgt->ids.node_name = wwn_to_u64(rsp->service_parms.node_name);
		tgt->ids.port_name = wwn_to_u64(rsp->service_parms.port_name);
		tgt->ids.port_id = tgt->scsi_id;
		स_नकल(&tgt->service_parms, &rsp->service_parms,
		       माप(tgt->service_parms));
		स_नकल(&tgt->service_parms_change, &rsp->service_parms_change,
		       माप(tgt->service_parms_change));
		ibmvfc_init_tgt(tgt, ibmvfc_tgt_send_prli);
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	हाल IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		अगर (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_send_plogi);
		अन्यथा
			ibmvfc_del_tgt(tgt);

		tgt_log(tgt, level, "Port Login failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
					     be16_to_cpu(rsp->status), be16_to_cpu(rsp->error),
			ibmvfc_get_fc_type(be16_to_cpu(rsp->fc_type)), be16_to_cpu(rsp->fc_type),
			ibmvfc_get_ls_explain(be16_to_cpu(rsp->fc_explain)), be16_to_cpu(rsp->fc_explain), status);
		अवरोध;
	पूर्ण

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_tgt_send_plogi - Send PLOGI to the specअगरied target
 * @tgt:	ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_send_plogi(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_port_login *plogi;
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	kref_get(&tgt->kref);
	tgt->logo_rcvd = 0;
	evt = ibmvfc_get_event(&vhost->crq);
	vhost->discovery_thपढ़ोs++;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	ibmvfc_init_event(evt, ibmvfc_tgt_plogi_करोne, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;
	plogi = &evt->iu.plogi;
	स_रखो(plogi, 0, माप(*plogi));
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN)) अणु
		plogi->common.version = cpu_to_be32(2);
		plogi->target_wwpn = cpu_to_be64(tgt->wwpn);
	पूर्ण अन्यथा अणु
		plogi->common.version = cpu_to_be32(1);
	पूर्ण
	plogi->common.opcode = cpu_to_be32(IBMVFC_PORT_LOGIN);
	plogi->common.length = cpu_to_be16(माप(*plogi));
	plogi->scsi_id = cpu_to_be64(tgt->scsi_id);

	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent port login\n");
पूर्ण

/**
 * ibmvfc_tgt_implicit_logout_करोne - Completion handler क्रम Implicit Logout MAD
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_implicit_logout_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_implicit_logout *rsp = &evt->xfer_iu->implicit_logout;
	u32 status = be16_to_cpu(rsp->common.status);

	vhost->discovery_thपढ़ोs--;
	ibmvfc_मुक्त_event(evt);
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);

	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Implicit Logout succeeded\n");
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		wake_up(&vhost->work_रुको_q);
		वापस;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		tgt_err(tgt, "Implicit Logout failed: rc=0x%02X\n", status);
		अवरोध;
	पूर्ण

	ibmvfc_init_tgt(tgt, ibmvfc_tgt_send_plogi);
	kref_put(&tgt->kref, ibmvfc_release_tgt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * __ibmvfc_tgt_get_implicit_logout_evt - Allocate and init an event क्रम implicit logout
 * @tgt:		ibmvfc target काष्ठा
 * @करोne:		Routine to call when the event is responded to
 *
 * Returns:
 *	Allocated and initialized ibmvfc_event काष्ठा
 **/
अटल काष्ठा ibmvfc_event *__ibmvfc_tgt_get_implicit_logout_evt(काष्ठा ibmvfc_target *tgt,
								 व्योम (*करोne) (काष्ठा ibmvfc_event *))
अणु
	काष्ठा ibmvfc_implicit_logout *mad;
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, करोne, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;
	mad = &evt->iu.implicit_logout;
	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_IMPLICIT_LOGOUT);
	mad->common.length = cpu_to_be16(माप(*mad));
	mad->old_scsi_id = cpu_to_be64(tgt->scsi_id);
	वापस evt;
पूर्ण

/**
 * ibmvfc_tgt_implicit_logout - Initiate an Implicit Logout क्रम specअगरied target
 * @tgt:		ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_implicit_logout(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	vhost->discovery_thपढ़ोs++;
	evt = __ibmvfc_tgt_get_implicit_logout_evt(tgt,
						   ibmvfc_tgt_implicit_logout_करोne);

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent Implicit Logout\n");
पूर्ण

/**
 * ibmvfc_tgt_implicit_logout_and_del_करोne - Completion handler क्रम Implicit Logout MAD
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_implicit_logout_and_del_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_passthru_mad *mad = &evt->xfer_iu->passthru;
	u32 status = be16_to_cpu(mad->common.status);

	vhost->discovery_thपढ़ोs--;
	ibmvfc_मुक्त_event(evt);

	/*
	 * If our state is IBMVFC_HOST_OFFLINE, we could be unloading the
	 * driver in which हाल we need to मुक्त up all the tarमाला_लो. If we are
	 * not unloading, we will still go through a hard reset to get out of
	 * offline state, so there is no need to track the old tarमाला_लो in that
	 * हाल.
	 */
	अगर (status == IBMVFC_MAD_SUCCESS || vhost->state == IBMVFC_HOST_OFFLINE)
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
	अन्यथा
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT);

	tgt_dbg(tgt, "Implicit Logout %s\n", (status == IBMVFC_MAD_SUCCESS) ? "succeeded" : "failed");
	kref_put(&tgt->kref, ibmvfc_release_tgt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_tgt_implicit_logout_and_del - Initiate an Implicit Logout क्रम specअगरied target
 * @tgt:		ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_implicit_logout_and_del(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (!vhost->logged_in) अणु
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		वापस;
	पूर्ण

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	vhost->discovery_thपढ़ोs++;
	evt = __ibmvfc_tgt_get_implicit_logout_evt(tgt,
						   ibmvfc_tgt_implicit_logout_and_del_करोne);

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT);
	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent Implicit Logout\n");
पूर्ण

/**
 * ibmvfc_tgt_move_login_करोne - Completion handler क्रम Move Login
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_move_login_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_move_login *rsp = &evt->xfer_iu->move_login;
	u32 status = be16_to_cpu(rsp->common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_thपढ़ोs--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Move Login succeeded for old scsi_id: %llX\n", tgt->old_scsi_id);
		tgt->ids.node_name = wwn_to_u64(rsp->service_parms.node_name);
		tgt->ids.port_name = wwn_to_u64(rsp->service_parms.port_name);
		tgt->ids.port_id = tgt->scsi_id;
		स_नकल(&tgt->service_parms, &rsp->service_parms,
		       माप(tgt->service_parms));
		स_नकल(&tgt->service_parms_change, &rsp->service_parms_change,
		       माप(tgt->service_parms_change));
		ibmvfc_init_tgt(tgt, ibmvfc_tgt_send_prli);
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	हाल IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_move_login);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_move_login);

		tgt_log(tgt, level,
			"Move Login failed: old scsi_id: %llX, flags:%x, vios_flags:%x, rc=0x%02X\n",
			tgt->old_scsi_id, be32_to_cpu(rsp->flags), be16_to_cpu(rsp->vios_flags),
			status);
		अवरोध;
	पूर्ण

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण


/**
 * ibmvfc_tgt_move_login - Initiate a move login क्रम specअगरied target
 * @tgt:		ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_move_login(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_move_login *move;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	vhost->discovery_thपढ़ोs++;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	ibmvfc_init_event(evt, ibmvfc_tgt_move_login_करोne, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;
	move = &evt->iu.move_login;
	स_रखो(move, 0, माप(*move));
	move->common.version = cpu_to_be32(1);
	move->common.opcode = cpu_to_be32(IBMVFC_MOVE_LOGIN);
	move->common.length = cpu_to_be16(माप(*move));

	move->old_scsi_id = cpu_to_be64(tgt->old_scsi_id);
	move->new_scsi_id = cpu_to_be64(tgt->scsi_id);
	move->wwpn = cpu_to_be64(tgt->wwpn);
	move->node_name = cpu_to_be64(tgt->ids.node_name);

	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent Move Login for old scsi_id: %llX\n", tgt->old_scsi_id);
पूर्ण

/**
 * ibmvfc_adisc_needs_plogi - Does device need PLOGI?
 * @mad:	ibmvfc passthru mad काष्ठा
 * @tgt:	ibmvfc target काष्ठा
 *
 * Returns:
 *	1 अगर PLOGI needed / 0 अगर PLOGI not needed
 **/
अटल पूर्णांक ibmvfc_adisc_needs_plogi(काष्ठा ibmvfc_passthru_mad *mad,
				    काष्ठा ibmvfc_target *tgt)
अणु
	अगर (wwn_to_u64((u8 *)&mad->fc_iu.response[2]) != tgt->ids.port_name)
		वापस 1;
	अगर (wwn_to_u64((u8 *)&mad->fc_iu.response[4]) != tgt->ids.node_name)
		वापस 1;
	अगर (be32_to_cpu(mad->fc_iu.response[6]) != tgt->scsi_id)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ibmvfc_tgt_adisc_करोne - Completion handler क्रम ADISC
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_adisc_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_passthru_mad *mad = &evt->xfer_iu->passthru;
	u32 status = be16_to_cpu(mad->common.status);
	u8 fc_reason, fc_explain;

	vhost->discovery_thपढ़ोs--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	del_समयr(&tgt->समयr);

	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "ADISC succeeded\n");
		अगर (ibmvfc_adisc_needs_plogi(mad, tgt))
			ibmvfc_del_tgt(tgt);
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		ibmvfc_del_tgt(tgt);
		fc_reason = (be32_to_cpu(mad->fc_iu.response[1]) & 0x00ff0000) >> 16;
		fc_explain = (be32_to_cpu(mad->fc_iu.response[1]) & 0x0000ff00) >> 8;
		tgt_info(tgt, "ADISC failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			 ibmvfc_get_cmd_error(be16_to_cpu(mad->iu.status), be16_to_cpu(mad->iu.error)),
			 be16_to_cpu(mad->iu.status), be16_to_cpu(mad->iu.error),
			 ibmvfc_get_fc_type(fc_reason), fc_reason,
			 ibmvfc_get_ls_explain(fc_explain), fc_explain, status);
		अवरोध;
	पूर्ण

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_init_passthru - Initialize an event काष्ठा क्रम FC passthru
 * @evt:		ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_init_passthru(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_passthru_mad *mad = &evt->iu.passthru;

	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_PASSTHRU);
	mad->common.length = cpu_to_be16(माप(*mad) - माप(mad->fc_iu) - माप(mad->iu));
	mad->cmd_ioba.va = cpu_to_be64((u64)be64_to_cpu(evt->crq.ioba) +
		दुरत्व(काष्ठा ibmvfc_passthru_mad, iu));
	mad->cmd_ioba.len = cpu_to_be32(माप(mad->iu));
	mad->iu.cmd_len = cpu_to_be32(माप(mad->fc_iu.payload));
	mad->iu.rsp_len = cpu_to_be32(माप(mad->fc_iu.response));
	mad->iu.cmd.va = cpu_to_be64((u64)be64_to_cpu(evt->crq.ioba) +
		दुरत्व(काष्ठा ibmvfc_passthru_mad, fc_iu) +
		दुरत्व(काष्ठा ibmvfc_passthru_fc_iu, payload));
	mad->iu.cmd.len = cpu_to_be32(माप(mad->fc_iu.payload));
	mad->iu.rsp.va = cpu_to_be64((u64)be64_to_cpu(evt->crq.ioba) +
		दुरत्व(काष्ठा ibmvfc_passthru_mad, fc_iu) +
		दुरत्व(काष्ठा ibmvfc_passthru_fc_iu, response));
	mad->iu.rsp.len = cpu_to_be32(माप(mad->fc_iu.response));
पूर्ण

/**
 * ibmvfc_tgt_adisc_cancel_करोne - Completion handler when cancelling an ADISC
 * @evt:		ibmvfc event काष्ठा
 *
 * Just cleanup this event काष्ठा. Everything अन्यथा is handled by
 * the ADISC completion handler. If the ADISC never actually comes
 * back, we still have the समयr running on the ADISC event काष्ठा
 * which will fire and cause the CRQ to get reset.
 *
 **/
अटल व्योम ibmvfc_tgt_adisc_cancel_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_target *tgt = evt->tgt;

	tgt_dbg(tgt, "ADISC cancel complete\n");
	vhost->पात_thपढ़ोs--;
	ibmvfc_मुक्त_event(evt);
	kref_put(&tgt->kref, ibmvfc_release_tgt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_adisc_समयout - Handle an ADISC समयout
 * @t:		ibmvfc target काष्ठा
 *
 * If an ADISC बार out, send a cancel. If the cancel बार
 * out, reset the CRQ. When the ADISC comes back as cancelled,
 * log back पूर्णांकo the target.
 **/
अटल व्योम ibmvfc_adisc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ibmvfc_target *tgt = from_समयr(tgt, t, समयr);
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;
	काष्ठा ibmvfc_पंचांगf *पंचांगf;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	tgt_dbg(tgt, "ADISC timeout\n");
	spin_lock_irqsave(vhost->host->host_lock, flags);
	अगर (vhost->पात_thपढ़ोs >= disc_thपढ़ोs ||
	    tgt->action != IBMVFC_TGT_ACTION_INIT_WAIT ||
	    vhost->state != IBMVFC_INITIALIZING ||
	    vhost->action != IBMVFC_HOST_ACTION_QUERY_TGTS) अणु
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		वापस;
	पूर्ण

	vhost->पात_thपढ़ोs++;
	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, ibmvfc_tgt_adisc_cancel_करोne, IBMVFC_MAD_FORMAT);

	evt->tgt = tgt;
	पंचांगf = &evt->iu.पंचांगf;
	स_रखो(पंचांगf, 0, माप(*पंचांगf));
	अगर (ibmvfc_check_caps(vhost, IBMVFC_HANDLE_VF_WWPN)) अणु
		पंचांगf->common.version = cpu_to_be32(2);
		पंचांगf->target_wwpn = cpu_to_be64(tgt->wwpn);
	पूर्ण अन्यथा अणु
		पंचांगf->common.version = cpu_to_be32(1);
	पूर्ण
	पंचांगf->common.opcode = cpu_to_be32(IBMVFC_TMF_MAD);
	पंचांगf->common.length = cpu_to_be16(माप(*पंचांगf));
	पंचांगf->scsi_id = cpu_to_be64(tgt->scsi_id);
	पंचांगf->cancel_key = cpu_to_be32(tgt->cancel_key);

	rc = ibmvfc_send_event(evt, vhost, शेष_समयout);

	अगर (rc) अणु
		tgt_err(tgt, "Failed to send cancel event for ADISC. rc=%d\n", rc);
		vhost->पात_thपढ़ोs--;
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		__ibmvfc_reset_host(vhost);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Attempting to cancel ADISC\n");
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_tgt_adisc - Initiate an ADISC क्रम specअगरied target
 * @tgt:		ibmvfc target काष्ठा
 *
 * When sending an ADISC we end up with two समयrs running. The
 * first समयr is the समयr in the ibmvfc target काष्ठा. If this
 * fires, we send a cancel to the target. The second समयr is the
 * समयr on the ibmvfc event क्रम the ADISC, which is दीर्घer. If that
 * fires, it means the ADISC समयd out and our attempt to cancel it
 * also failed, so we need to reset the CRQ.
 **/
अटल व्योम ibmvfc_tgt_adisc(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_passthru_mad *mad;
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	vhost->discovery_thपढ़ोs++;
	ibmvfc_init_event(evt, ibmvfc_tgt_adisc_करोne, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;

	ibmvfc_init_passthru(evt);
	mad = &evt->iu.passthru;
	mad->iu.flags = cpu_to_be32(IBMVFC_FC_ELS);
	mad->iu.scsi_id = cpu_to_be64(tgt->scsi_id);
	mad->iu.cancel_key = cpu_to_be32(tgt->cancel_key);

	mad->fc_iu.payload[0] = cpu_to_be32(IBMVFC_ADISC);
	स_नकल(&mad->fc_iu.payload[2], &vhost->login_buf->resp.port_name,
	       माप(vhost->login_buf->resp.port_name));
	स_नकल(&mad->fc_iu.payload[4], &vhost->login_buf->resp.node_name,
	       माप(vhost->login_buf->resp.node_name));
	mad->fc_iu.payload[6] = cpu_to_be32(be64_to_cpu(vhost->login_buf->resp.scsi_id) & 0x00ffffff);

	अगर (समयr_pending(&tgt->समयr))
		mod_समयr(&tgt->समयr, jअगरfies + (IBMVFC_ADISC_TIMEOUT * HZ));
	अन्यथा अणु
		tgt->समयr.expires = jअगरfies + (IBMVFC_ADISC_TIMEOUT * HZ);
		add_समयr(&tgt->समयr);
	पूर्ण

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	अगर (ibmvfc_send_event(evt, vhost, IBMVFC_ADISC_PLUS_CANCEL_TIMEOUT)) अणु
		vhost->discovery_thपढ़ोs--;
		del_समयr(&tgt->समयr);
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent ADISC\n");
पूर्ण

/**
 * ibmvfc_tgt_query_target_करोne - Completion handler क्रम Query Target MAD
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_query_target_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_target *tgt = evt->tgt;
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_query_tgt *rsp = &evt->xfer_iu->query_tgt;
	u32 status = be16_to_cpu(rsp->common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	vhost->discovery_thपढ़ोs--;
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
	चयन (status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Query Target succeeded\n");
		अगर (be64_to_cpu(rsp->scsi_id) != tgt->scsi_id)
			ibmvfc_del_tgt(tgt);
		अन्यथा
			ibmvfc_init_tgt(tgt, ibmvfc_tgt_adisc);
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	हाल IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_query_target);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	शेष:
		अगर ((be16_to_cpu(rsp->status) & IBMVFC_FABRIC_MAPPED) == IBMVFC_FABRIC_MAPPED &&
		    be16_to_cpu(rsp->error) == IBMVFC_UNABLE_TO_PERFORM_REQ &&
		    be16_to_cpu(rsp->fc_explain) == IBMVFC_PORT_NAME_NOT_REG)
			ibmvfc_del_tgt(tgt);
		अन्यथा अगर (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_tgt_init(tgt, ibmvfc_tgt_query_target);
		अन्यथा
			ibmvfc_del_tgt(tgt);

		tgt_log(tgt, level, "Query Target failed: %s (%x:%x) %s (%x) %s (%x) rc=0x%02X\n",
			ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
			be16_to_cpu(rsp->status), be16_to_cpu(rsp->error),
			ibmvfc_get_fc_type(be16_to_cpu(rsp->fc_type)), be16_to_cpu(rsp->fc_type),
			ibmvfc_get_gs_explain(be16_to_cpu(rsp->fc_explain)), be16_to_cpu(rsp->fc_explain),
			status);
		अवरोध;
	पूर्ण

	kref_put(&tgt->kref, ibmvfc_release_tgt);
	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_tgt_query_target - Initiate a Query Target क्रम specअगरied target
 * @tgt:	ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_query_target(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_query_tgt *query_tgt;
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा ibmvfc_event *evt;

	अगर (vhost->discovery_thपढ़ोs >= disc_thपढ़ोs)
		वापस;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(&vhost->crq);
	vhost->discovery_thपढ़ोs++;
	evt->tgt = tgt;
	ibmvfc_init_event(evt, ibmvfc_tgt_query_target_करोne, IBMVFC_MAD_FORMAT);
	query_tgt = &evt->iu.query_tgt;
	स_रखो(query_tgt, 0, माप(*query_tgt));
	query_tgt->common.version = cpu_to_be32(1);
	query_tgt->common.opcode = cpu_to_be32(IBMVFC_QUERY_TARGET);
	query_tgt->common.length = cpu_to_be16(माप(*query_tgt));
	query_tgt->wwpn = cpu_to_be64(tgt->ids.port_name);

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	अगर (ibmvfc_send_event(evt, vhost, शेष_समयout)) अणु
		vhost->discovery_thपढ़ोs--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "Sent Query Target\n");
पूर्ण

/**
 * ibmvfc_alloc_target - Allocate and initialize an ibmvfc target
 * @vhost:		ibmvfc host काष्ठा
 * @target:		Holds SCSI ID to allocate target क्रमand the WWPN
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_alloc_target(काष्ठा ibmvfc_host *vhost,
			       काष्ठा ibmvfc_discover_tarमाला_लो_entry *target)
अणु
	काष्ठा ibmvfc_target *stgt = शून्य;
	काष्ठा ibmvfc_target *wtgt = शून्य;
	काष्ठा ibmvfc_target *tgt;
	अचिन्हित दीर्घ flags;
	u64 scsi_id = be32_to_cpu(target->scsi_id) & IBMVFC_DISC_TGT_SCSI_ID_MASK;
	u64 wwpn = be64_to_cpu(target->wwpn);

	/* Look to see अगर we alपढ़ोy have a target allocated क्रम this SCSI ID or WWPN */
	spin_lock_irqsave(vhost->host->host_lock, flags);
	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->wwpn == wwpn) अणु
			wtgt = tgt;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->scsi_id == scsi_id) अणु
			stgt = tgt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (wtgt && !stgt) अणु
		/*
		 * A WWPN target has moved and we still are tracking the old
		 * SCSI ID.  The only way we should be able to get here is अगर
		 * we attempted to send an implicit logout क्रम the old SCSI ID
		 * and it failed क्रम some reason, such as there being I/O
		 * pending to the target. In this हाल, we will have alपढ़ोy
		 * deleted the rport from the FC transport so we करो a move
		 * login, which works even with I/O pending, as it will cancel
		 * any active commands.
		 */
		अगर (wtgt->action == IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT) अणु
			/*
			 * Do a move login here. The old target is no दीर्घer
			 * known to the transport layer We करोn't use the
			 * normal ibmvfc_set_tgt_action to set this, as we
			 * करोn't normally want to allow this state change.
			 */
			wtgt->old_scsi_id = wtgt->scsi_id;
			wtgt->scsi_id = scsi_id;
			wtgt->action = IBMVFC_TGT_ACTION_INIT;
			ibmvfc_init_tgt(wtgt, ibmvfc_tgt_move_login);
			जाओ unlock_out;
		पूर्ण अन्यथा अणु
			tgt_err(wtgt, "Unexpected target state: %d, %p\n",
				wtgt->action, wtgt->rport);
		पूर्ण
	पूर्ण अन्यथा अगर (stgt) अणु
		अगर (tgt->need_login)
			ibmvfc_init_tgt(tgt, ibmvfc_tgt_implicit_logout);
		जाओ unlock_out;
	पूर्ण
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	tgt = mempool_alloc(vhost->tgt_pool, GFP_NOIO);
	स_रखो(tgt, 0, माप(*tgt));
	tgt->scsi_id = scsi_id;
	tgt->wwpn = wwpn;
	tgt->vhost = vhost;
	tgt->need_login = 1;
	समयr_setup(&tgt->समयr, ibmvfc_adisc_समयout, 0);
	kref_init(&tgt->kref);
	ibmvfc_init_tgt(tgt, ibmvfc_tgt_implicit_logout);
	spin_lock_irqsave(vhost->host->host_lock, flags);
	tgt->cancel_key = vhost->task_set++;
	list_add_tail(&tgt->queue, &vhost->tarमाला_लो);

unlock_out:
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस 0;
पूर्ण

/**
 * ibmvfc_alloc_tarमाला_लो - Allocate and initialize ibmvfc tarमाला_लो
 * @vhost:		ibmvfc host काष्ठा
 *
 * Returns:
 *	0 on success / other on failure
 **/
अटल पूर्णांक ibmvfc_alloc_tarमाला_लो(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0, rc = 0; !rc && i < vhost->num_tarमाला_लो; i++)
		rc = ibmvfc_alloc_target(vhost, &vhost->disc_buf[i]);

	वापस rc;
पूर्ण

/**
 * ibmvfc_discover_tarमाला_लो_करोne - Completion handler क्रम discover tarमाला_लो MAD
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_discover_tarमाला_लो_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_discover_tarमाला_लो *rsp = &evt->xfer_iu->discover_tarमाला_लो;
	u32 mad_status = be16_to_cpu(rsp->common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	चयन (mad_status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		ibmvfc_dbg(vhost, "Discover Targets succeeded\n");
		vhost->num_tarमाला_लो = be32_to_cpu(rsp->num_written);
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_ALLOC_TGTS);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
		level += ibmvfc_retry_host_init(vhost);
		ibmvfc_log(vhost, level, "Discover Targets failed: %s (%x:%x)\n",
			   ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
			   be16_to_cpu(rsp->status), be16_to_cpu(rsp->error));
		अवरोध;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		अवरोध;
	शेष:
		dev_err(vhost->dev, "Invalid Discover Targets response: 0x%x\n", mad_status);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		अवरोध;
	पूर्ण

	ibmvfc_मुक्त_event(evt);
	wake_up(&vhost->work_रुको_q);
पूर्ण

/**
 * ibmvfc_discover_tarमाला_लो - Send Discover Tarमाला_लो MAD
 * @vhost:	ibmvfc host काष्ठा
 *
 **/
अटल व्योम ibmvfc_discover_tarमाला_लो(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_discover_tarमाला_लो *mad;
	काष्ठा ibmvfc_event *evt = ibmvfc_get_event(&vhost->crq);

	ibmvfc_init_event(evt, ibmvfc_discover_tarमाला_लो_करोne, IBMVFC_MAD_FORMAT);
	mad = &evt->iu.discover_tarमाला_लो;
	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_DISC_TARGETS);
	mad->common.length = cpu_to_be16(माप(*mad));
	mad->bufflen = cpu_to_be32(vhost->disc_buf_sz);
	mad->buffer.va = cpu_to_be64(vhost->disc_buf_dma);
	mad->buffer.len = cpu_to_be32(vhost->disc_buf_sz);
	mad->flags = cpu_to_be32(IBMVFC_DISC_TGT_PORT_ID_WWPN_LIST);
	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT_WAIT);

	अगर (!ibmvfc_send_event(evt, vhost, शेष_समयout))
		ibmvfc_dbg(vhost, "Sent discover targets\n");
	अन्यथा
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
पूर्ण

अटल व्योम ibmvfc_channel_setup_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_channel_setup *setup = vhost->channel_setup_buf;
	काष्ठा ibmvfc_scsi_channels *scrqs = &vhost->scsi_scrqs;
	u32 mad_status = be16_to_cpu(evt->xfer_iu->channel_setup.common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;
	पूर्णांक flags, active_queues, i;

	ibmvfc_मुक्त_event(evt);

	चयन (mad_status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		ibmvfc_dbg(vhost, "Channel Setup succeeded\n");
		flags = be32_to_cpu(setup->flags);
		vhost->करो_enquiry = 0;
		active_queues = be32_to_cpu(setup->num_scsi_subq_channels);
		scrqs->active_queues = active_queues;

		अगर (flags & IBMVFC_CHANNELS_CANCELED) अणु
			ibmvfc_dbg(vhost, "Channels Canceled\n");
			vhost->using_channels = 0;
		पूर्ण अन्यथा अणु
			अगर (active_queues)
				vhost->using_channels = 1;
			क्रम (i = 0; i < active_queues; i++)
				scrqs->scrqs[i].vios_cookie =
					be64_to_cpu(setup->channel_handles[i]);

			ibmvfc_dbg(vhost, "Using %u channels\n",
				   vhost->scsi_scrqs.active_queues);
		पूर्ण
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
		level += ibmvfc_retry_host_init(vhost);
		ibmvfc_log(vhost, level, "Channel Setup failed\n");
		fallthrough;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		वापस;
	शेष:
		dev_err(vhost->dev, "Invalid Channel Setup response: 0x%x\n",
			mad_status);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		वापस;
	पूर्ण

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY);
	wake_up(&vhost->work_रुको_q);
पूर्ण

अटल व्योम ibmvfc_channel_setup(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_channel_setup_mad *mad;
	काष्ठा ibmvfc_channel_setup *setup_buf = vhost->channel_setup_buf;
	काष्ठा ibmvfc_event *evt = ibmvfc_get_event(&vhost->crq);
	काष्ठा ibmvfc_scsi_channels *scrqs = &vhost->scsi_scrqs;
	अचिन्हित पूर्णांक num_channels =
		min(vhost->client_scsi_channels, vhost->max_vios_scsi_channels);
	पूर्णांक i;

	स_रखो(setup_buf, 0, माप(*setup_buf));
	अगर (num_channels == 0)
		setup_buf->flags = cpu_to_be32(IBMVFC_CANCEL_CHANNELS);
	अन्यथा अणु
		setup_buf->num_scsi_subq_channels = cpu_to_be32(num_channels);
		क्रम (i = 0; i < num_channels; i++)
			setup_buf->channel_handles[i] = cpu_to_be64(scrqs->scrqs[i].cookie);
	पूर्ण

	ibmvfc_init_event(evt, ibmvfc_channel_setup_करोne, IBMVFC_MAD_FORMAT);
	mad = &evt->iu.channel_setup;
	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_CHANNEL_SETUP);
	mad->common.length = cpu_to_be16(माप(*mad));
	mad->buffer.va = cpu_to_be64(vhost->channel_setup_dma);
	mad->buffer.len = cpu_to_be32(माप(*vhost->channel_setup_buf));

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT_WAIT);

	अगर (!ibmvfc_send_event(evt, vhost, शेष_समयout))
		ibmvfc_dbg(vhost, "Sent channel setup\n");
	अन्यथा
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DOWN);
पूर्ण

अटल व्योम ibmvfc_channel_enquiry_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	काष्ठा ibmvfc_channel_enquiry *rsp = &evt->xfer_iu->channel_enquiry;
	u32 mad_status = be16_to_cpu(rsp->common.status);
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	चयन (mad_status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		ibmvfc_dbg(vhost, "Channel Enquiry succeeded\n");
		vhost->max_vios_scsi_channels = be32_to_cpu(rsp->num_scsi_subq_channels);
		ibmvfc_मुक्त_event(evt);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
		level += ibmvfc_retry_host_init(vhost);
		ibmvfc_log(vhost, level, "Channel Enquiry failed\n");
		fallthrough;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		ibmvfc_मुक्त_event(evt);
		वापस;
	शेष:
		dev_err(vhost->dev, "Invalid Channel Enquiry response: 0x%x\n",
			mad_status);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		ibmvfc_मुक्त_event(evt);
		वापस;
	पूर्ण

	ibmvfc_channel_setup(vhost);
पूर्ण

अटल व्योम ibmvfc_channel_enquiry(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_channel_enquiry *mad;
	काष्ठा ibmvfc_event *evt = ibmvfc_get_event(&vhost->crq);

	ibmvfc_init_event(evt, ibmvfc_channel_enquiry_करोne, IBMVFC_MAD_FORMAT);
	mad = &evt->iu.channel_enquiry;
	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_CHANNEL_ENQUIRY);
	mad->common.length = cpu_to_be16(माप(*mad));

	अगर (mig_channels_only)
		mad->flags |= cpu_to_be32(IBMVFC_NO_CHANNELS_TO_CRQ_SUPPORT);
	अगर (mig_no_less_channels)
		mad->flags |= cpu_to_be32(IBMVFC_NO_N_TO_M_CHANNELS_SUPPORT);

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT_WAIT);

	अगर (!ibmvfc_send_event(evt, vhost, शेष_समयout))
		ibmvfc_dbg(vhost, "Send channel enquiry\n");
	अन्यथा
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
पूर्ण

/**
 * ibmvfc_npiv_login_करोne - Completion handler क्रम NPIV Login
 * @evt:	ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_npiv_login_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	u32 mad_status = be16_to_cpu(evt->xfer_iu->npiv_login.common.status);
	काष्ठा ibmvfc_npiv_login_resp *rsp = &vhost->login_buf->resp;
	अचिन्हित पूर्णांक npiv_max_sectors;
	पूर्णांक level = IBMVFC_DEFAULT_LOG_LEVEL;

	चयन (mad_status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		ibmvfc_मुक्त_event(evt);
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
		अगर (ibmvfc_retry_cmd(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)))
			level += ibmvfc_retry_host_init(vhost);
		अन्यथा
			ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		ibmvfc_log(vhost, level, "NPIV Login failed: %s (%x:%x)\n",
			   ibmvfc_get_cmd_error(be16_to_cpu(rsp->status), be16_to_cpu(rsp->error)),
						be16_to_cpu(rsp->status), be16_to_cpu(rsp->error));
		ibmvfc_मुक्त_event(evt);
		वापस;
	हाल IBMVFC_MAD_CRQ_ERROR:
		ibmvfc_retry_host_init(vhost);
		fallthrough;
	हाल IBMVFC_MAD_DRIVER_FAILED:
		ibmvfc_मुक्त_event(evt);
		वापस;
	शेष:
		dev_err(vhost->dev, "Invalid NPIV Login response: 0x%x\n", mad_status);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		ibmvfc_मुक्त_event(evt);
		वापस;
	पूर्ण

	vhost->client_migrated = 0;

	अगर (!(be32_to_cpu(rsp->flags) & IBMVFC_NATIVE_FC)) अणु
		dev_err(vhost->dev, "Virtual adapter does not support FC. %x\n",
			rsp->flags);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		wake_up(&vhost->work_रुको_q);
		वापस;
	पूर्ण

	अगर (be32_to_cpu(rsp->max_cmds) <= IBMVFC_NUM_INTERNAL_REQ) अणु
		dev_err(vhost->dev, "Virtual adapter supported queue depth too small: %d\n",
			rsp->max_cmds);
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
		wake_up(&vhost->work_रुको_q);
		वापस;
	पूर्ण

	vhost->logged_in = 1;
	npiv_max_sectors = min((uपूर्णांक)(be64_to_cpu(rsp->max_dma_len) >> 9), IBMVFC_MAX_SECTORS);
	dev_info(vhost->dev, "Host partition: %s, device: %s %s %s max sectors %u\n",
		 rsp->partition_name, rsp->device_name, rsp->port_loc_code,
		 rsp->drc_name, npiv_max_sectors);

	fc_host_fabric_name(vhost->host) = be64_to_cpu(rsp->node_name);
	fc_host_node_name(vhost->host) = be64_to_cpu(rsp->node_name);
	fc_host_port_name(vhost->host) = be64_to_cpu(rsp->port_name);
	fc_host_port_id(vhost->host) = be64_to_cpu(rsp->scsi_id);
	fc_host_port_type(vhost->host) = FC_PORTTYPE_NPIV;
	fc_host_supported_classes(vhost->host) = 0;
	अगर (be32_to_cpu(rsp->service_parms.class1_parms[0]) & 0x80000000)
		fc_host_supported_classes(vhost->host) |= FC_COS_CLASS1;
	अगर (be32_to_cpu(rsp->service_parms.class2_parms[0]) & 0x80000000)
		fc_host_supported_classes(vhost->host) |= FC_COS_CLASS2;
	अगर (be32_to_cpu(rsp->service_parms.class3_parms[0]) & 0x80000000)
		fc_host_supported_classes(vhost->host) |= FC_COS_CLASS3;
	fc_host_maxframe_size(vhost->host) =
		be16_to_cpu(rsp->service_parms.common.bb_rcv_sz) & 0x0fff;

	vhost->host->can_queue = be32_to_cpu(rsp->max_cmds) - IBMVFC_NUM_INTERNAL_REQ;
	vhost->host->max_sectors = npiv_max_sectors;

	अगर (ibmvfc_check_caps(vhost, IBMVFC_CAN_SUPPORT_CHANNELS) && vhost->करो_enquiry) अणु
		ibmvfc_channel_enquiry(vhost);
	पूर्ण अन्यथा अणु
		vhost->करो_enquiry = 0;
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY);
		wake_up(&vhost->work_रुको_q);
	पूर्ण
पूर्ण

/**
 * ibmvfc_npiv_login - Sends NPIV login
 * @vhost:	ibmvfc host काष्ठा
 *
 **/
अटल व्योम ibmvfc_npiv_login(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_npiv_login_mad *mad;
	काष्ठा ibmvfc_event *evt = ibmvfc_get_event(&vhost->crq);

	ibmvfc_gather_partition_info(vhost);
	ibmvfc_set_login_info(vhost);
	ibmvfc_init_event(evt, ibmvfc_npiv_login_करोne, IBMVFC_MAD_FORMAT);

	स_नकल(vhost->login_buf, &vhost->login_info, माप(vhost->login_info));
	mad = &evt->iu.npiv_login;
	स_रखो(mad, 0, माप(काष्ठा ibmvfc_npiv_login_mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_NPIV_LOGIN);
	mad->common.length = cpu_to_be16(माप(काष्ठा ibmvfc_npiv_login_mad));
	mad->buffer.va = cpu_to_be64(vhost->login_buf_dma);
	mad->buffer.len = cpu_to_be32(माप(*vhost->login_buf));

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT_WAIT);

	अगर (!ibmvfc_send_event(evt, vhost, शेष_समयout))
		ibmvfc_dbg(vhost, "Sent NPIV login\n");
	अन्यथा
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
पूर्ण

/**
 * ibmvfc_npiv_logout_करोne - Completion handler क्रम NPIV Logout
 * @evt:		ibmvfc event काष्ठा
 *
 **/
अटल व्योम ibmvfc_npiv_logout_करोne(काष्ठा ibmvfc_event *evt)
अणु
	काष्ठा ibmvfc_host *vhost = evt->vhost;
	u32 mad_status = be16_to_cpu(evt->xfer_iu->npiv_logout.common.status);

	ibmvfc_मुक्त_event(evt);

	चयन (mad_status) अणु
	हाल IBMVFC_MAD_SUCCESS:
		अगर (list_empty(&vhost->crq.sent) &&
		    vhost->action == IBMVFC_HOST_ACTION_LOGO_WAIT) अणु
			ibmvfc_init_host(vhost);
			वापस;
		पूर्ण
		अवरोध;
	हाल IBMVFC_MAD_FAILED:
	हाल IBMVFC_MAD_NOT_SUPPORTED:
	हाल IBMVFC_MAD_CRQ_ERROR:
	हाल IBMVFC_MAD_DRIVER_FAILED:
	शेष:
		ibmvfc_dbg(vhost, "NPIV Logout failed. 0x%X\n", mad_status);
		अवरोध;
	पूर्ण

	ibmvfc_hard_reset_host(vhost);
पूर्ण

/**
 * ibmvfc_npiv_logout - Issue an NPIV Logout
 * @vhost:		ibmvfc host काष्ठा
 *
 **/
अटल व्योम ibmvfc_npiv_logout(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_npiv_logout_mad *mad;
	काष्ठा ibmvfc_event *evt;

	evt = ibmvfc_get_event(&vhost->crq);
	ibmvfc_init_event(evt, ibmvfc_npiv_logout_करोne, IBMVFC_MAD_FORMAT);

	mad = &evt->iu.npiv_logout;
	स_रखो(mad, 0, माप(*mad));
	mad->common.version = cpu_to_be32(1);
	mad->common.opcode = cpu_to_be32(IBMVFC_NPIV_LOGOUT);
	mad->common.length = cpu_to_be16(माप(काष्ठा ibmvfc_npiv_logout_mad));

	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_LOGO_WAIT);

	अगर (!ibmvfc_send_event(evt, vhost, शेष_समयout))
		ibmvfc_dbg(vhost, "Sent NPIV logout\n");
	अन्यथा
		ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
पूर्ण

/**
 * ibmvfc_dev_init_to_करो - Is there target initialization work to करो?
 * @vhost:		ibmvfc host काष्ठा
 *
 * Returns:
 *	1 अगर work to करो / 0 अगर not
 **/
अटल पूर्णांक ibmvfc_dev_init_to_करो(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_target *tgt;

	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->action == IBMVFC_TGT_ACTION_INIT ||
		    tgt->action == IBMVFC_TGT_ACTION_INIT_WAIT)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ibmvfc_dev_logo_to_करो - Is there target logout work to करो?
 * @vhost:		ibmvfc host काष्ठा
 *
 * Returns:
 *	1 अगर work to करो / 0 अगर not
 **/
अटल पूर्णांक ibmvfc_dev_logo_to_करो(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_target *tgt;

	list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
		अगर (tgt->action == IBMVFC_TGT_ACTION_LOGOUT_RPORT ||
		    tgt->action == IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * __ibmvfc_work_to_करो - Is there task level work to करो? (no locking)
 * @vhost:		ibmvfc host काष्ठा
 *
 * Returns:
 *	1 अगर work to करो / 0 अगर not
 **/
अटल पूर्णांक __ibmvfc_work_to_करो(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_target *tgt;

	अगर (kthपढ़ो_should_stop())
		वापस 1;
	चयन (vhost->action) अणु
	हाल IBMVFC_HOST_ACTION_NONE:
	हाल IBMVFC_HOST_ACTION_INIT_WAIT:
	हाल IBMVFC_HOST_ACTION_LOGO_WAIT:
		वापस 0;
	हाल IBMVFC_HOST_ACTION_TGT_INIT:
	हाल IBMVFC_HOST_ACTION_QUERY_TGTS:
		अगर (vhost->discovery_thपढ़ोs == disc_thपढ़ोs)
			वापस 0;
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			अगर (tgt->action == IBMVFC_TGT_ACTION_INIT)
				वापस 1;
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			अगर (tgt->action == IBMVFC_TGT_ACTION_INIT_WAIT)
				वापस 0;
		वापस 1;
	हाल IBMVFC_HOST_ACTION_TGT_DEL:
	हाल IBMVFC_HOST_ACTION_TGT_DEL_FAILED:
		अगर (vhost->discovery_thपढ़ोs == disc_thपढ़ोs)
			वापस 0;
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			अगर (tgt->action == IBMVFC_TGT_ACTION_LOGOUT_RPORT)
				वापस 1;
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			अगर (tgt->action == IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT)
				वापस 0;
		वापस 1;
	हाल IBMVFC_HOST_ACTION_LOGO:
	हाल IBMVFC_HOST_ACTION_INIT:
	हाल IBMVFC_HOST_ACTION_ALLOC_TGTS:
	हाल IBMVFC_HOST_ACTION_QUERY:
	हाल IBMVFC_HOST_ACTION_RESET:
	हाल IBMVFC_HOST_ACTION_REENABLE:
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * ibmvfc_work_to_करो - Is there task level work to करो?
 * @vhost:		ibmvfc host काष्ठा
 *
 * Returns:
 *	1 अगर work to करो / 0 अगर not
 **/
अटल पूर्णांक ibmvfc_work_to_करो(काष्ठा ibmvfc_host *vhost)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	rc = __ibmvfc_work_to_करो(vhost);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस rc;
पूर्ण

/**
 * ibmvfc_log_ae - Log async events अगर necessary
 * @vhost:		ibmvfc host काष्ठा
 * @events:		events to log
 *
 **/
अटल व्योम ibmvfc_log_ae(काष्ठा ibmvfc_host *vhost, पूर्णांक events)
अणु
	अगर (events & IBMVFC_AE_RSCN)
		fc_host_post_event(vhost->host, fc_get_event_number(), FCH_EVT_RSCN, 0);
	अगर ((events & IBMVFC_AE_LINKDOWN) &&
	    vhost->state >= IBMVFC_HALTED)
		fc_host_post_event(vhost->host, fc_get_event_number(), FCH_EVT_LINKDOWN, 0);
	अगर ((events & IBMVFC_AE_LINKUP) &&
	    vhost->state == IBMVFC_INITIALIZING)
		fc_host_post_event(vhost->host, fc_get_event_number(), FCH_EVT_LINKUP, 0);
पूर्ण

/**
 * ibmvfc_tgt_add_rport - Tell the FC transport about a new remote port
 * @tgt:		ibmvfc target काष्ठा
 *
 **/
अटल व्योम ibmvfc_tgt_add_rport(काष्ठा ibmvfc_target *tgt)
अणु
	काष्ठा ibmvfc_host *vhost = tgt->vhost;
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;

	tgt_dbg(tgt, "Adding rport\n");
	rport = fc_remote_port_add(vhost->host, 0, &tgt->ids);
	spin_lock_irqsave(vhost->host->host_lock, flags);

	अगर (rport && tgt->action == IBMVFC_TGT_ACTION_DEL_RPORT) अणु
		tgt_dbg(tgt, "Deleting rport\n");
		list_del(&tgt->queue);
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DELETED_RPORT);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		fc_remote_port_delete(rport);
		del_समयr_sync(&tgt->समयr);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		वापस;
	पूर्ण अन्यथा अगर (rport && tgt->action == IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT) अणु
		tgt_dbg(tgt, "Deleting rport with outstanding I/O\n");
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT);
		tgt->rport = शून्य;
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		fc_remote_port_delete(rport);
		वापस;
	पूर्ण अन्यथा अगर (rport && tgt->action == IBMVFC_TGT_ACTION_DELETED_RPORT) अणु
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		वापस;
	पूर्ण

	अगर (rport) अणु
		tgt_dbg(tgt, "rport add succeeded\n");
		tgt->rport = rport;
		rport->maxframe_size = be16_to_cpu(tgt->service_parms.common.bb_rcv_sz) & 0x0fff;
		rport->supported_classes = 0;
		tgt->target_id = rport->scsi_target_id;
		अगर (be32_to_cpu(tgt->service_parms.class1_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS1;
		अगर (be32_to_cpu(tgt->service_parms.class2_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS2;
		अगर (be32_to_cpu(tgt->service_parms.class3_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS3;
		अगर (rport->rqst_q)
			blk_queue_max_segments(rport->rqst_q, 1);
	पूर्ण अन्यथा
		tgt_dbg(tgt, "rport add failed\n");
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_करो_work - Do task level work
 * @vhost:		ibmvfc host काष्ठा
 *
 **/
अटल व्योम ibmvfc_करो_work(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_target *tgt;
	अचिन्हित दीर्घ flags;
	काष्ठा fc_rport *rport;
	LIST_HEAD(purge);
	पूर्णांक rc;

	ibmvfc_log_ae(vhost, vhost->events_to_log);
	spin_lock_irqsave(vhost->host->host_lock, flags);
	vhost->events_to_log = 0;
	चयन (vhost->action) अणु
	हाल IBMVFC_HOST_ACTION_NONE:
	हाल IBMVFC_HOST_ACTION_LOGO_WAIT:
	हाल IBMVFC_HOST_ACTION_INIT_WAIT:
		अवरोध;
	हाल IBMVFC_HOST_ACTION_RESET:
		list_splice_init(&vhost->purge, &purge);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		ibmvfc_complete_purge(&purge);
		rc = ibmvfc_reset_crq(vhost);

		spin_lock_irqsave(vhost->host->host_lock, flags);
		अगर (!rc || rc == H_CLOSED)
			vio_enable_पूर्णांकerrupts(to_vio_dev(vhost->dev));
		अगर (vhost->action == IBMVFC_HOST_ACTION_RESET) अणु
			/*
			 * The only action we could have changed to would have
			 * been reenable, in which हाल, we skip the rest of
			 * this path and रुको until we've करोne the re-enable
			 * beक्रमe sending the crq init.
			 */
			vhost->action = IBMVFC_HOST_ACTION_TGT_DEL;

			अगर (rc || (rc = ibmvfc_send_crq_init(vhost)) ||
			    (rc = vio_enable_पूर्णांकerrupts(to_vio_dev(vhost->dev)))) अणु
				ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
				dev_err(vhost->dev, "Error after reset (rc=%d)\n", rc);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IBMVFC_HOST_ACTION_REENABLE:
		list_splice_init(&vhost->purge, &purge);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		ibmvfc_complete_purge(&purge);
		rc = ibmvfc_reenable_crq_queue(vhost);

		spin_lock_irqsave(vhost->host->host_lock, flags);
		अगर (vhost->action == IBMVFC_HOST_ACTION_REENABLE) अणु
			/*
			 * The only action we could have changed to would have
			 * been reset, in which हाल, we skip the rest of this
			 * path and रुको until we've करोne the reset beक्रमe
			 * sending the crq init.
			 */
			vhost->action = IBMVFC_HOST_ACTION_TGT_DEL;
			अगर (rc || (rc = ibmvfc_send_crq_init(vhost))) अणु
				ibmvfc_link_करोwn(vhost, IBMVFC_LINK_DEAD);
				dev_err(vhost->dev, "Error after enable (rc=%d)\n", rc);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IBMVFC_HOST_ACTION_LOGO:
		vhost->job_step(vhost);
		अवरोध;
	हाल IBMVFC_HOST_ACTION_INIT:
		BUG_ON(vhost->state != IBMVFC_INITIALIZING);
		अगर (vhost->delay_init) अणु
			vhost->delay_init = 0;
			spin_unlock_irqrestore(vhost->host->host_lock, flags);
			ssleep(15);
			वापस;
		पूर्ण अन्यथा
			vhost->job_step(vhost);
		अवरोध;
	हाल IBMVFC_HOST_ACTION_QUERY:
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue)
			ibmvfc_init_tgt(tgt, ibmvfc_tgt_query_target);
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY_TGTS);
		अवरोध;
	हाल IBMVFC_HOST_ACTION_QUERY_TGTS:
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (tgt->action == IBMVFC_TGT_ACTION_INIT) अणु
				tgt->job_step(tgt);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!ibmvfc_dev_init_to_करो(vhost))
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_TGT_DEL);
		अवरोध;
	हाल IBMVFC_HOST_ACTION_TGT_DEL:
	हाल IBMVFC_HOST_ACTION_TGT_DEL_FAILED:
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (tgt->action == IBMVFC_TGT_ACTION_LOGOUT_RPORT) अणु
				tgt->job_step(tgt);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ibmvfc_dev_logo_to_करो(vhost)) अणु
			spin_unlock_irqrestore(vhost->host->host_lock, flags);
			वापस;
		पूर्ण

		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (tgt->action == IBMVFC_TGT_ACTION_DEL_RPORT) अणु
				tgt_dbg(tgt, "Deleting rport\n");
				rport = tgt->rport;
				tgt->rport = शून्य;
				list_del(&tgt->queue);
				ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DELETED_RPORT);
				spin_unlock_irqrestore(vhost->host->host_lock, flags);
				अगर (rport)
					fc_remote_port_delete(rport);
				del_समयr_sync(&tgt->समयr);
				kref_put(&tgt->kref, ibmvfc_release_tgt);
				वापस;
			पूर्ण अन्यथा अगर (tgt->action == IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT) अणु
				tgt_dbg(tgt, "Deleting rport with I/O outstanding\n");
				rport = tgt->rport;
				tgt->rport = शून्य;
				ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT);
				spin_unlock_irqrestore(vhost->host->host_lock, flags);
				अगर (rport)
					fc_remote_port_delete(rport);
				वापस;
			पूर्ण
		पूर्ण

		अगर (vhost->state == IBMVFC_INITIALIZING) अणु
			अगर (vhost->action == IBMVFC_HOST_ACTION_TGT_DEL_FAILED) अणु
				अगर (vhost->reinit) अणु
					vhost->reinit = 0;
					scsi_block_requests(vhost->host);
					ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY);
					spin_unlock_irqrestore(vhost->host->host_lock, flags);
				पूर्ण अन्यथा अणु
					ibmvfc_set_host_state(vhost, IBMVFC_ACTIVE);
					ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_NONE);
					wake_up(&vhost->init_रुको_q);
					schedule_work(&vhost->rport_add_work_q);
					vhost->init_retries = 0;
					spin_unlock_irqrestore(vhost->host->host_lock, flags);
					scsi_unblock_requests(vhost->host);
				पूर्ण

				वापस;
			पूर्ण अन्यथा अणु
				ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_INIT);
				vhost->job_step = ibmvfc_discover_tarमाला_लो;
			पूर्ण
		पूर्ण अन्यथा अणु
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_NONE);
			spin_unlock_irqrestore(vhost->host->host_lock, flags);
			scsi_unblock_requests(vhost->host);
			wake_up(&vhost->init_रुको_q);
			वापस;
		पूर्ण
		अवरोध;
	हाल IBMVFC_HOST_ACTION_ALLOC_TGTS:
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_TGT_INIT);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		ibmvfc_alloc_tarमाला_लो(vhost);
		spin_lock_irqsave(vhost->host->host_lock, flags);
		अवरोध;
	हाल IBMVFC_HOST_ACTION_TGT_INIT:
		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (tgt->action == IBMVFC_TGT_ACTION_INIT) अणु
				tgt->job_step(tgt);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!ibmvfc_dev_init_to_करो(vhost))
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_TGT_DEL_FAILED);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(vhost->host->host_lock, flags);
पूर्ण

/**
 * ibmvfc_work - Do task level work
 * @data:		ibmvfc host काष्ठा
 *
 * Returns:
 *	zero
 **/
अटल पूर्णांक ibmvfc_work(व्योम *data)
अणु
	काष्ठा ibmvfc_host *vhost = data;
	पूर्णांक rc;

	set_user_nice(current, MIN_NICE);

	जबतक (1) अणु
		rc = रुको_event_पूर्णांकerruptible(vhost->work_रुको_q,
					      ibmvfc_work_to_करो(vhost));

		BUG_ON(rc);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		ibmvfc_करो_work(vhost);
	पूर्ण

	ibmvfc_dbg(vhost, "ibmvfc kthread exiting...\n");
	वापस 0;
पूर्ण

/**
 * ibmvfc_alloc_queue - Allocate queue
 * @vhost:	ibmvfc host काष्ठा
 * @queue:	ibmvfc queue to allocate
 * @fmt:	queue क्रमmat to allocate
 *
 * Returns:
 *	0 on success / non-zero on failure
 **/
अटल पूर्णांक ibmvfc_alloc_queue(काष्ठा ibmvfc_host *vhost,
			      काष्ठा ibmvfc_queue *queue,
			      क्रमागत ibmvfc_msg_fmt fmt)
अणु
	काष्ठा device *dev = vhost->dev;
	माप_प्रकार fmt_size;
	अचिन्हित पूर्णांक pool_size = 0;

	ENTER;
	spin_lock_init(&queue->_lock);
	queue->q_lock = &queue->_lock;

	चयन (fmt) अणु
	हाल IBMVFC_CRQ_FMT:
		fmt_size = माप(*queue->msgs.crq);
		pool_size = max_requests + IBMVFC_NUM_INTERNAL_REQ;
		अवरोध;
	हाल IBMVFC_ASYNC_FMT:
		fmt_size = माप(*queue->msgs.async);
		अवरोध;
	हाल IBMVFC_SUB_CRQ_FMT:
		fmt_size = माप(*queue->msgs.scrq);
		/* We need one extra event क्रम Cancel Commands */
		pool_size = max_requests + 1;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown command/response queue message format: %d\n", fmt);
		वापस -EINVAL;
	पूर्ण

	अगर (ibmvfc_init_event_pool(vhost, queue, pool_size)) अणु
		dev_err(dev, "Couldn't initialize event pool.\n");
		वापस -ENOMEM;
	पूर्ण

	queue->msgs.handle = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!queue->msgs.handle)
		वापस -ENOMEM;

	queue->msg_token = dma_map_single(dev, queue->msgs.handle, PAGE_SIZE,
					  DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(dev, queue->msg_token)) अणु
		मुक्त_page((अचिन्हित दीर्घ)queue->msgs.handle);
		queue->msgs.handle = शून्य;
		वापस -ENOMEM;
	पूर्ण

	queue->cur = 0;
	queue->fmt = fmt;
	queue->size = PAGE_SIZE / fmt_size;
	वापस 0;
पूर्ण

/**
 * ibmvfc_init_crq - Initializes and रेजिस्टरs CRQ with hypervisor
 * @vhost:	ibmvfc host काष्ठा
 *
 * Allocates a page क्रम messages, maps it क्रम dma, and रेजिस्टरs
 * the crq with the hypervisor.
 *
 * Return value:
 *	zero on success / other on failure
 **/
अटल पूर्णांक ibmvfc_init_crq(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक rc, retrc = -ENOMEM;
	काष्ठा device *dev = vhost->dev;
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा ibmvfc_queue *crq = &vhost->crq;

	ENTER;
	अगर (ibmvfc_alloc_queue(vhost, crq, IBMVFC_CRQ_FMT))
		वापस -ENOMEM;

	retrc = rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
					crq->msg_token, PAGE_SIZE);

	अगर (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		retrc = rc = ibmvfc_reset_crq(vhost);

	अगर (rc == H_CLOSED)
		dev_warn(dev, "Partner adapter not ready\n");
	अन्यथा अगर (rc) अणु
		dev_warn(dev, "Error %d opening adapter\n", rc);
		जाओ reg_crq_failed;
	पूर्ण

	retrc = 0;

	tasklet_init(&vhost->tasklet, (व्योम *)ibmvfc_tasklet, (अचिन्हित दीर्घ)vhost);

	अगर ((rc = request_irq(vdev->irq, ibmvfc_पूर्णांकerrupt, 0, IBMVFC_NAME, vhost))) अणु
		dev_err(dev, "Couldn't register irq 0x%x. rc=%d\n", vdev->irq, rc);
		जाओ req_irq_failed;
	पूर्ण

	अगर ((rc = vio_enable_पूर्णांकerrupts(vdev))) अणु
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		जाओ req_irq_failed;
	पूर्ण

	LEAVE;
	वापस retrc;

req_irq_failed:
	tasklet_समाप्त(&vhost->tasklet);
	करो अणु
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));
reg_crq_failed:
	ibmvfc_मुक्त_queue(vhost, crq);
	वापस retrc;
पूर्ण

अटल पूर्णांक ibmvfc_रेजिस्टर_scsi_channel(काष्ठा ibmvfc_host *vhost,
				  पूर्णांक index)
अणु
	काष्ठा device *dev = vhost->dev;
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा ibmvfc_queue *scrq = &vhost->scsi_scrqs.scrqs[index];
	पूर्णांक rc = -ENOMEM;

	ENTER;

	अगर (ibmvfc_alloc_queue(vhost, scrq, IBMVFC_SUB_CRQ_FMT))
		वापस -ENOMEM;

	rc = h_reg_sub_crq(vdev->unit_address, scrq->msg_token, PAGE_SIZE,
			   &scrq->cookie, &scrq->hw_irq);

	/* H_CLOSED indicates successful रेजिस्टर, but no CRQ partner */
	अगर (rc && rc != H_CLOSED) अणु
		dev_warn(dev, "Error registering sub-crq: %d\n", rc);
		अगर (rc == H_PARAMETER)
			dev_warn_once(dev, "Firmware may not support MQ\n");
		जाओ reg_failed;
	पूर्ण

	scrq->irq = irq_create_mapping(शून्य, scrq->hw_irq);

	अगर (!scrq->irq) अणु
		rc = -EINVAL;
		dev_err(dev, "Error mapping sub-crq[%d] irq\n", index);
		जाओ irq_failed;
	पूर्ण

	snम_लिखो(scrq->name, माप(scrq->name), "ibmvfc-%x-scsi%d",
		 vdev->unit_address, index);
	rc = request_irq(scrq->irq, ibmvfc_पूर्णांकerrupt_scsi, 0, scrq->name, scrq);

	अगर (rc) अणु
		dev_err(dev, "Couldn't register sub-crq[%d] irq\n", index);
		irq_dispose_mapping(scrq->irq);
		जाओ irq_failed;
	पूर्ण

	scrq->hwq_id = index;
	scrq->vhost = vhost;

	LEAVE;
	वापस 0;

irq_failed:
	करो अणु
		rc = plpar_hcall_norets(H_FREE_SUB_CRQ, vdev->unit_address, scrq->cookie);
	पूर्ण जबतक (rtas_busy_delay(rc));
reg_failed:
	ibmvfc_मुक्त_queue(vhost, scrq);
	LEAVE;
	वापस rc;
पूर्ण

अटल व्योम ibmvfc_deरेजिस्टर_scsi_channel(काष्ठा ibmvfc_host *vhost, पूर्णांक index)
अणु
	काष्ठा device *dev = vhost->dev;
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा ibmvfc_queue *scrq = &vhost->scsi_scrqs.scrqs[index];
	दीर्घ rc;

	ENTER;

	मुक्त_irq(scrq->irq, scrq);
	irq_dispose_mapping(scrq->irq);
	scrq->irq = 0;

	करो अणु
		rc = plpar_hcall_norets(H_FREE_SUB_CRQ, vdev->unit_address,
					scrq->cookie);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	अगर (rc)
		dev_err(dev, "Failed to free sub-crq[%d]: rc=%ld\n", index, rc);

	ibmvfc_मुक्त_queue(vhost, scrq);
	LEAVE;
पूर्ण

अटल व्योम ibmvfc_init_sub_crqs(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक i, j;

	ENTER;
	अगर (!vhost->mq_enabled)
		वापस;

	vhost->scsi_scrqs.scrqs = kसुस्मृति(nr_scsi_hw_queues,
					  माप(*vhost->scsi_scrqs.scrqs),
					  GFP_KERNEL);
	अगर (!vhost->scsi_scrqs.scrqs) अणु
		vhost->करो_enquiry = 0;
		वापस;
	पूर्ण

	क्रम (i = 0; i < nr_scsi_hw_queues; i++) अणु
		अगर (ibmvfc_रेजिस्टर_scsi_channel(vhost, i)) अणु
			क्रम (j = i; j > 0; j--)
				ibmvfc_deरेजिस्टर_scsi_channel(vhost, j - 1);
			kमुक्त(vhost->scsi_scrqs.scrqs);
			vhost->scsi_scrqs.scrqs = शून्य;
			vhost->scsi_scrqs.active_queues = 0;
			vhost->करो_enquiry = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	LEAVE;
पूर्ण

अटल व्योम ibmvfc_release_sub_crqs(काष्ठा ibmvfc_host *vhost)
अणु
	पूर्णांक i;

	ENTER;
	अगर (!vhost->scsi_scrqs.scrqs)
		वापस;

	क्रम (i = 0; i < nr_scsi_hw_queues; i++)
		ibmvfc_deरेजिस्टर_scsi_channel(vhost, i);

	kमुक्त(vhost->scsi_scrqs.scrqs);
	vhost->scsi_scrqs.scrqs = शून्य;
	vhost->scsi_scrqs.active_queues = 0;
	LEAVE;
पूर्ण

/**
 * ibmvfc_मुक्त_mem - Free memory क्रम vhost
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 * 	none
 **/
अटल व्योम ibmvfc_मुक्त_mem(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_queue *async_q = &vhost->async_crq;

	ENTER;
	mempool_destroy(vhost->tgt_pool);
	kमुक्त(vhost->trace);
	dma_मुक्त_coherent(vhost->dev, vhost->disc_buf_sz, vhost->disc_buf,
			  vhost->disc_buf_dma);
	dma_मुक्त_coherent(vhost->dev, माप(*vhost->login_buf),
			  vhost->login_buf, vhost->login_buf_dma);
	dma_मुक्त_coherent(vhost->dev, माप(*vhost->channel_setup_buf),
			  vhost->channel_setup_buf, vhost->channel_setup_dma);
	dma_pool_destroy(vhost->sg_pool);
	ibmvfc_मुक्त_queue(vhost, async_q);
	LEAVE;
पूर्ण

/**
 * ibmvfc_alloc_mem - Allocate memory क्रम vhost
 * @vhost:	ibmvfc host काष्ठा
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल पूर्णांक ibmvfc_alloc_mem(काष्ठा ibmvfc_host *vhost)
अणु
	काष्ठा ibmvfc_queue *async_q = &vhost->async_crq;
	काष्ठा device *dev = vhost->dev;

	ENTER;
	अगर (ibmvfc_alloc_queue(vhost, async_q, IBMVFC_ASYNC_FMT)) अणु
		dev_err(dev, "Couldn't allocate/map async queue.\n");
		जाओ nomem;
	पूर्ण

	vhost->sg_pool = dma_pool_create(IBMVFC_NAME, dev,
					 SG_ALL * माप(काष्ठा srp_direct_buf),
					 माप(काष्ठा srp_direct_buf), 0);

	अगर (!vhost->sg_pool) अणु
		dev_err(dev, "Failed to allocate sg pool\n");
		जाओ unmap_async_crq;
	पूर्ण

	vhost->login_buf = dma_alloc_coherent(dev, माप(*vhost->login_buf),
					      &vhost->login_buf_dma, GFP_KERNEL);

	अगर (!vhost->login_buf) अणु
		dev_err(dev, "Couldn't allocate NPIV login buffer\n");
		जाओ मुक्त_sg_pool;
	पूर्ण

	vhost->disc_buf_sz = माप(*vhost->disc_buf) * max_tarमाला_लो;
	vhost->disc_buf = dma_alloc_coherent(dev, vhost->disc_buf_sz,
					     &vhost->disc_buf_dma, GFP_KERNEL);

	अगर (!vhost->disc_buf) अणु
		dev_err(dev, "Couldn't allocate Discover Targets buffer\n");
		जाओ मुक्त_login_buffer;
	पूर्ण

	vhost->trace = kसुस्मृति(IBMVFC_NUM_TRACE_ENTRIES,
			       माप(काष्ठा ibmvfc_trace_entry), GFP_KERNEL);
	atomic_set(&vhost->trace_index, -1);

	अगर (!vhost->trace)
		जाओ मुक्त_disc_buffer;

	vhost->tgt_pool = mempool_create_kदो_स्मृति_pool(IBMVFC_TGT_MEMPOOL_SZ,
						      माप(काष्ठा ibmvfc_target));

	अगर (!vhost->tgt_pool) अणु
		dev_err(dev, "Couldn't allocate target memory pool\n");
		जाओ मुक्त_trace;
	पूर्ण

	vhost->channel_setup_buf = dma_alloc_coherent(dev, माप(*vhost->channel_setup_buf),
						      &vhost->channel_setup_dma,
						      GFP_KERNEL);

	अगर (!vhost->channel_setup_buf) अणु
		dev_err(dev, "Couldn't allocate Channel Setup buffer\n");
		जाओ मुक्त_tgt_pool;
	पूर्ण

	LEAVE;
	वापस 0;

मुक्त_tgt_pool:
	mempool_destroy(vhost->tgt_pool);
मुक्त_trace:
	kमुक्त(vhost->trace);
मुक्त_disc_buffer:
	dma_मुक्त_coherent(dev, vhost->disc_buf_sz, vhost->disc_buf,
			  vhost->disc_buf_dma);
मुक्त_login_buffer:
	dma_मुक्त_coherent(dev, माप(*vhost->login_buf),
			  vhost->login_buf, vhost->login_buf_dma);
मुक्त_sg_pool:
	dma_pool_destroy(vhost->sg_pool);
unmap_async_crq:
	ibmvfc_मुक्त_queue(vhost, async_q);
nomem:
	LEAVE;
	वापस -ENOMEM;
पूर्ण

/**
 * ibmvfc_rport_add_thपढ़ो - Worker thपढ़ो क्रम rport adds
 * @work:	work काष्ठा
 *
 **/
अटल व्योम ibmvfc_rport_add_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ibmvfc_host *vhost = container_of(work, काष्ठा ibmvfc_host,
						 rport_add_work_q);
	काष्ठा ibmvfc_target *tgt;
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;
	पूर्णांक did_work;

	ENTER;
	spin_lock_irqsave(vhost->host->host_lock, flags);
	करो अणु
		did_work = 0;
		अगर (vhost->state != IBMVFC_ACTIVE)
			अवरोध;

		list_क्रम_each_entry(tgt, &vhost->tarमाला_लो, queue) अणु
			अगर (tgt->add_rport) अणु
				did_work = 1;
				tgt->add_rport = 0;
				kref_get(&tgt->kref);
				rport = tgt->rport;
				अगर (!rport) अणु
					spin_unlock_irqrestore(vhost->host->host_lock, flags);
					ibmvfc_tgt_add_rport(tgt);
				पूर्ण अन्यथा अगर (get_device(&rport->dev)) अणु
					spin_unlock_irqrestore(vhost->host->host_lock, flags);
					tgt_dbg(tgt, "Setting rport roles\n");
					fc_remote_port_rolechg(rport, tgt->ids.roles);
					put_device(&rport->dev);
				पूर्ण अन्यथा अणु
					spin_unlock_irqrestore(vhost->host->host_lock, flags);
				पूर्ण

				kref_put(&tgt->kref, ibmvfc_release_tgt);
				spin_lock_irqsave(vhost->host->host_lock, flags);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक(did_work);

	अगर (vhost->state == IBMVFC_ACTIVE)
		vhost->scan_complete = 1;
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	LEAVE;
पूर्ण

/**
 * ibmvfc_probe - Adapter hot plug add entry poपूर्णांक
 * @vdev:	vio device काष्ठा
 * @id:	vio device id काष्ठा
 *
 * Return value:
 * 	0 on success / non-zero on failure
 **/
अटल पूर्णांक ibmvfc_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा ibmvfc_host *vhost;
	काष्ठा Scsi_Host *shost;
	काष्ठा device *dev = &vdev->dev;
	पूर्णांक rc = -ENOMEM;
	अचिन्हित पूर्णांक max_scsi_queues = IBMVFC_MAX_SCSI_QUEUES;

	ENTER;
	shost = scsi_host_alloc(&driver_ढाँचा, माप(*vhost));
	अगर (!shost) अणु
		dev_err(dev, "Couldn't allocate host data\n");
		जाओ out;
	पूर्ण

	shost->transportt = ibmvfc_transport_ढाँचा;
	shost->can_queue = max_requests;
	shost->max_lun = max_lun;
	shost->max_id = max_tarमाला_लो;
	shost->max_sectors = IBMVFC_MAX_SECTORS;
	shost->max_cmd_len = IBMVFC_MAX_CDB_LEN;
	shost->unique_id = shost->host_no;
	shost->nr_hw_queues = mq_enabled ? min(max_scsi_queues, nr_scsi_hw_queues) : 1;

	vhost = shost_priv(shost);
	INIT_LIST_HEAD(&vhost->tarमाला_लो);
	INIT_LIST_HEAD(&vhost->purge);
	प्र_लिखो(vhost->name, IBMVFC_NAME);
	vhost->host = shost;
	vhost->dev = dev;
	vhost->partition_number = -1;
	vhost->log_level = log_level;
	vhost->task_set = 1;

	vhost->mq_enabled = mq_enabled;
	vhost->client_scsi_channels = min(shost->nr_hw_queues, nr_scsi_channels);
	vhost->using_channels = 0;
	vhost->करो_enquiry = 1;

	म_नकल(vhost->partition_name, "UNKNOWN");
	init_रुकोqueue_head(&vhost->work_रुको_q);
	init_रुकोqueue_head(&vhost->init_रुको_q);
	INIT_WORK(&vhost->rport_add_work_q, ibmvfc_rport_add_thपढ़ो);
	mutex_init(&vhost->passthru_mutex);

	अगर ((rc = ibmvfc_alloc_mem(vhost)))
		जाओ मुक्त_scsi_host;

	vhost->work_thपढ़ो = kthपढ़ो_run(ibmvfc_work, vhost, "%s_%d", IBMVFC_NAME,
					 shost->host_no);

	अगर (IS_ERR(vhost->work_thपढ़ो)) अणु
		dev_err(dev, "Couldn't create kernel thread: %ld\n",
			PTR_ERR(vhost->work_thपढ़ो));
		rc = PTR_ERR(vhost->work_thपढ़ो);
		जाओ मुक्त_host_mem;
	पूर्ण

	अगर ((rc = ibmvfc_init_crq(vhost))) अणु
		dev_err(dev, "Couldn't initialize crq. rc=%d\n", rc);
		जाओ समाप्त_kthपढ़ो;
	पूर्ण

	अगर ((rc = scsi_add_host(shost, dev)))
		जाओ release_crq;

	fc_host_dev_loss_पंचांगo(shost) = IBMVFC_DEV_LOSS_TMO;

	अगर ((rc = ibmvfc_create_trace_file(&shost->shost_dev.kobj,
					   &ibmvfc_trace_attr))) अणु
		dev_err(dev, "Failed to create trace file. rc=%d\n", rc);
		जाओ हटाओ_shost;
	पूर्ण

	ibmvfc_init_sub_crqs(vhost);

	अगर (shost_to_fc_host(shost)->rqst_q)
		blk_queue_max_segments(shost_to_fc_host(shost)->rqst_q, 1);
	dev_set_drvdata(dev, vhost);
	spin_lock(&ibmvfc_driver_lock);
	list_add_tail(&vhost->queue, &ibmvfc_head);
	spin_unlock(&ibmvfc_driver_lock);

	ibmvfc_send_crq_init(vhost);
	scsi_scan_host(shost);
	वापस 0;

हटाओ_shost:
	scsi_हटाओ_host(shost);
release_crq:
	ibmvfc_release_crq_queue(vhost);
समाप्त_kthपढ़ो:
	kthपढ़ो_stop(vhost->work_thपढ़ो);
मुक्त_host_mem:
	ibmvfc_मुक्त_mem(vhost);
मुक्त_scsi_host:
	scsi_host_put(shost);
out:
	LEAVE;
	वापस rc;
पूर्ण

/**
 * ibmvfc_हटाओ - Adapter hot plug हटाओ entry poपूर्णांक
 * @vdev:	vio device काष्ठा
 *
 * Return value:
 * 	0
 **/
अटल व्योम ibmvfc_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा ibmvfc_host *vhost = dev_get_drvdata(&vdev->dev);
	LIST_HEAD(purge);
	अचिन्हित दीर्घ flags;

	ENTER;
	ibmvfc_हटाओ_trace_file(&vhost->host->shost_dev.kobj, &ibmvfc_trace_attr);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_link_करोwn(vhost, IBMVFC_HOST_OFFLINE);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);

	ibmvfc_रुको_जबतक_resetting(vhost);
	kthपढ़ो_stop(vhost->work_thपढ़ो);
	fc_हटाओ_host(vhost->host);
	scsi_हटाओ_host(vhost->host);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	ibmvfc_purge_requests(vhost, DID_ERROR);
	list_splice_init(&vhost->purge, &purge);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	ibmvfc_complete_purge(&purge);
	ibmvfc_release_sub_crqs(vhost);
	ibmvfc_release_crq_queue(vhost);

	ibmvfc_मुक्त_mem(vhost);
	spin_lock(&ibmvfc_driver_lock);
	list_del(&vhost->queue);
	spin_unlock(&ibmvfc_driver_lock);
	scsi_host_put(vhost->host);
	LEAVE;
पूर्ण

/**
 * ibmvfc_resume - Resume from suspend
 * @dev:	device काष्ठा
 *
 * We may have lost an पूर्णांकerrupt across suspend/resume, so kick the
 * पूर्णांकerrupt handler
 *
 */
अटल पूर्णांक ibmvfc_resume(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ibmvfc_host *vhost = dev_get_drvdata(dev);
	काष्ठा vio_dev *vdev = to_vio_dev(dev);

	spin_lock_irqsave(vhost->host->host_lock, flags);
	vio_disable_पूर्णांकerrupts(vdev);
	tasklet_schedule(&vhost->tasklet);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	वापस 0;
पूर्ण

/**
 * ibmvfc_get_desired_dma - Calculate DMA resources needed by the driver
 * @vdev:	vio device काष्ठा
 *
 * Return value:
 *	Number of bytes the driver will need to DMA map at the same समय in
 *	order to perक्रमm well.
 */
अटल अचिन्हित दीर्घ ibmvfc_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	अचिन्हित दीर्घ pool_dma = max_requests * माप(जोड़ ibmvfc_iu);
	वापस pool_dma + ((512 * 1024) * driver_ढाँचा.cmd_per_lun);
पूर्ण

अटल स्थिर काष्ठा vio_device_id ibmvfc_device_table[] = अणु
	अणु"fcp", "IBM,vfc-client"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmvfc_device_table);

अटल स्थिर काष्ठा dev_pm_ops ibmvfc_pm_ops = अणु
	.resume = ibmvfc_resume
पूर्ण;

अटल काष्ठा vio_driver ibmvfc_driver = अणु
	.id_table = ibmvfc_device_table,
	.probe = ibmvfc_probe,
	.हटाओ = ibmvfc_हटाओ,
	.get_desired_dma = ibmvfc_get_desired_dma,
	.name = IBMVFC_NAME,
	.pm = &ibmvfc_pm_ops,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा ibmvfc_transport_functions = अणु
	.show_host_fabric_name = 1,
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_port_type = 1,
	.show_host_port_id = 1,
	.show_host_maxframe_size = 1,

	.get_host_port_state = ibmvfc_get_host_port_state,
	.show_host_port_state = 1,

	.get_host_speed = ibmvfc_get_host_speed,
	.show_host_speed = 1,

	.issue_fc_host_lip = ibmvfc_issue_fc_host_lip,
	.terminate_rport_io = ibmvfc_terminate_rport_io,

	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.set_rport_dev_loss_पंचांगo = ibmvfc_set_rport_dev_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,

	.get_starget_node_name = ibmvfc_get_starget_node_name,
	.show_starget_node_name = 1,

	.get_starget_port_name = ibmvfc_get_starget_port_name,
	.show_starget_port_name = 1,

	.get_starget_port_id = ibmvfc_get_starget_port_id,
	.show_starget_port_id = 1,

	.bsg_request = ibmvfc_bsg_request,
	.bsg_समयout = ibmvfc_bsg_समयout,
पूर्ण;

/**
 * ibmvfc_module_init - Initialize the ibmvfc module
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक __init ibmvfc_module_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!firmware_has_feature(FW_FEATURE_VIO))
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO IBMVFC_NAME": IBM Virtual Fibre Channel Driver version: %s %s\n",
	       IBMVFC_DRIVER_VERSION, IBMVFC_DRIVER_DATE);

	ibmvfc_transport_ढाँचा = fc_attach_transport(&ibmvfc_transport_functions);
	अगर (!ibmvfc_transport_ढाँचा)
		वापस -ENOMEM;

	rc = vio_रेजिस्टर_driver(&ibmvfc_driver);
	अगर (rc)
		fc_release_transport(ibmvfc_transport_ढाँचा);
	वापस rc;
पूर्ण

/**
 * ibmvfc_module_निकास - Tearकरोwn the ibmvfc module
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम __निकास ibmvfc_module_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&ibmvfc_driver);
	fc_release_transport(ibmvfc_transport_ढाँचा);
पूर्ण

module_init(ibmvfc_module_init);
module_निकास(ibmvfc_module_निकास);
