<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/iscsi_boot_sysfs.h>
#समावेश <linux/inet.h>

#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsicam.h>

#समावेश "ql4_def.h"
#समावेश "ql4_version.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"
#समावेश "ql4_83xx.h"

/*
 * Driver version
 */
अटल अक्षर qla4xxx_version_str[40];

/*
 * SRB allocation cache
 */
अटल काष्ठा kmem_cache *srb_cachep;

/*
 * Module parameter inक्रमmation and variables
 */
अटल पूर्णांक ql4xdisablesysfsboot = 1;
module_param(ql4xdisablesysfsboot, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xdisablesysfsboot,
		 " Set to disable exporting boot targets to sysfs.\n"
		 "\t\t  0 - Export boot targets\n"
		 "\t\t  1 - Do not export boot targets (Default)");

पूर्णांक ql4xकरोntresethba;
module_param(ql4xकरोntresethba, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xकरोntresethba,
		 " Don't reset the HBA for driver recovery.\n"
		 "\t\t  0 - It will reset HBA (Default)\n"
		 "\t\t  1 - It will NOT reset HBA");

पूर्णांक ql4xextended_error_logging;
module_param(ql4xextended_error_logging, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xextended_error_logging,
		 " Option to enable extended error logging.\n"
		 "\t\t  0 - no logging (Default)\n"
		 "\t\t  2 - debug logging");

पूर्णांक ql4xenablemsix = 1;
module_param(ql4xenablemsix, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql4xenablemsix,
		 " Set to enable MSI or MSI-X interrupt mechanism.\n"
		 "\t\t  0 = enable INTx interrupt mechanism.\n"
		 "\t\t  1 = enable MSI-X interrupt mechanism (Default).\n"
		 "\t\t  2 = enable MSI interrupt mechanism.");

#घोषणा QL4_DEF_QDEPTH 32
अटल पूर्णांक ql4xmaxqdepth = QL4_DEF_QDEPTH;
module_param(ql4xmaxqdepth, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xmaxqdepth,
		 " Maximum queue depth to report for target devices.\n"
		 "\t\t  Default: 32.");

अटल पूर्णांक ql4xqfulltracking = 1;
module_param(ql4xqfulltracking, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xqfulltracking,
		 " Enable or disable dynamic tracking and adjustment of\n"
		 "\t\t scsi device queue depth.\n"
		 "\t\t  0 - Disable.\n"
		 "\t\t  1 - Enable. (Default)");

अटल पूर्णांक ql4xsess_recovery_पंचांगo = QL4_SESS_RECOVERY_TMO;
module_param(ql4xsess_recovery_पंचांगo, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql4xsess_recovery_पंचांगo,
		" Target Session Recovery Timeout.\n"
		"\t\t  Default: 120 sec.");

पूर्णांक ql4xmdcapmask = 0;
module_param(ql4xmdcapmask, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ql4xmdcapmask,
		 " Set the Minidump driver capture mask level.\n"
		 "\t\t  Default is 0 (firmware default capture mask)\n"
		 "\t\t  Can be set to 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF");

पूर्णांक ql4xenablemd = 1;
module_param(ql4xenablemd, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ql4xenablemd,
		 " Set to enable minidump.\n"
		 "\t\t  0 - disable minidump\n"
		 "\t\t  1 - enable minidump (Default)");

अटल पूर्णांक qla4xxx_रुको_क्रम_hba_online(काष्ठा scsi_qla_host *ha);
/*
 * SCSI host ढाँचा entry poपूर्णांकs
 */
अटल व्योम qla4xxx_config_dma_addressing(काष्ठा scsi_qla_host *ha);

/*
 * iSCSI ढाँचा entry poपूर्णांकs
 */
अटल पूर्णांक qla4xxx_session_get_param(काष्ठा iscsi_cls_session *cls_sess,
				     क्रमागत iscsi_param param, अक्षर *buf);
अटल पूर्णांक qla4xxx_conn_get_param(काष्ठा iscsi_cls_conn *conn,
				  क्रमागत iscsi_param param, अक्षर *buf);
अटल पूर्णांक qla4xxx_host_get_param(काष्ठा Scsi_Host *shost,
				  क्रमागत iscsi_host_param param, अक्षर *buf);
अटल पूर्णांक qla4xxx_अगरace_set_param(काष्ठा Scsi_Host *shost, व्योम *data,
				   uपूर्णांक32_t len);
अटल पूर्णांक qla4xxx_get_अगरace_param(काष्ठा iscsi_अगरace *अगरace,
				   क्रमागत iscsi_param_type param_type,
				   पूर्णांक param, अक्षर *buf);
अटल क्रमागत blk_eh_समयr_वापस qla4xxx_eh_cmd_समयd_out(काष्ठा scsi_cmnd *sc);
अटल काष्ठा iscsi_endpoपूर्णांक *qla4xxx_ep_connect(काष्ठा Scsi_Host *shost,
						 काष्ठा sockaddr *dst_addr,
						 पूर्णांक non_blocking);
अटल पूर्णांक qla4xxx_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms);
अटल व्योम qla4xxx_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep);
अटल पूर्णांक qla4xxx_get_ep_param(काष्ठा iscsi_endpoपूर्णांक *ep,
				क्रमागत iscsi_param param, अक्षर *buf);
अटल पूर्णांक qla4xxx_conn_start(काष्ठा iscsi_cls_conn *conn);
अटल काष्ठा iscsi_cls_conn *
qla4xxx_conn_create(काष्ठा iscsi_cls_session *cls_sess, uपूर्णांक32_t conn_idx);
अटल पूर्णांक qla4xxx_conn_bind(काष्ठा iscsi_cls_session *cls_session,
			     काष्ठा iscsi_cls_conn *cls_conn,
			     uपूर्णांक64_t transport_fd, पूर्णांक is_leading);
अटल व्योम qla4xxx_conn_destroy(काष्ठा iscsi_cls_conn *conn);
अटल काष्ठा iscsi_cls_session *
qla4xxx_session_create(काष्ठा iscsi_endpoपूर्णांक *ep, uपूर्णांक16_t cmds_max,
			uपूर्णांक16_t qdepth, uपूर्णांक32_t initial_cmdsn);
अटल व्योम qla4xxx_session_destroy(काष्ठा iscsi_cls_session *sess);
अटल व्योम qla4xxx_task_work(काष्ठा work_काष्ठा *wdata);
अटल पूर्णांक qla4xxx_alloc_pdu(काष्ठा iscsi_task *, uपूर्णांक8_t);
अटल पूर्णांक qla4xxx_task_xmit(काष्ठा iscsi_task *);
अटल व्योम qla4xxx_task_cleanup(काष्ठा iscsi_task *);
अटल व्योम qla4xxx_fail_session(काष्ठा iscsi_cls_session *cls_session);
अटल व्योम qla4xxx_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
				   काष्ठा iscsi_stats *stats);
अटल पूर्णांक qla4xxx_send_ping(काष्ठा Scsi_Host *shost, uपूर्णांक32_t अगरace_num,
			     uपूर्णांक32_t अगरace_type, uपूर्णांक32_t payload_size,
			     uपूर्णांक32_t pid, काष्ठा sockaddr *dst_addr);
अटल पूर्णांक qla4xxx_get_chap_list(काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx,
				 uपूर्णांक32_t *num_entries, अक्षर *buf);
अटल पूर्णांक qla4xxx_delete_chap(काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx);
अटल पूर्णांक qla4xxx_set_chap_entry(काष्ठा Scsi_Host *shost, व्योम  *data,
				  पूर्णांक len);
अटल पूर्णांक qla4xxx_get_host_stats(काष्ठा Scsi_Host *shost, अक्षर *buf, पूर्णांक len);

/*
 * SCSI host ढाँचा entry poपूर्णांकs
 */
अटल पूर्णांक qla4xxx_queuecommand(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक qla4xxx_eh_पात(काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक qla4xxx_eh_device_reset(काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक qla4xxx_eh_target_reset(काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक qla4xxx_eh_host_reset(काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक qla4xxx_slave_alloc(काष्ठा scsi_device *device);
अटल umode_t qla4_attr_is_visible(पूर्णांक param_type, पूर्णांक param);
अटल पूर्णांक qla4xxx_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type);

/*
 * iSCSI Flash DDB sysfs entry poपूर्णांकs
 */
अटल पूर्णांक
qla4xxx_sysfs_ddb_set_param(काष्ठा iscsi_bus_flash_session *fnode_sess,
			    काष्ठा iscsi_bus_flash_conn *fnode_conn,
			    व्योम *data, पूर्णांक len);
अटल पूर्णांक
qla4xxx_sysfs_ddb_get_param(काष्ठा iscsi_bus_flash_session *fnode_sess,
			    पूर्णांक param, अक्षर *buf);
अटल पूर्णांक qla4xxx_sysfs_ddb_add(काष्ठा Scsi_Host *shost, स्थिर अक्षर *buf,
				 पूर्णांक len);
अटल पूर्णांक
qla4xxx_sysfs_ddb_delete(काष्ठा iscsi_bus_flash_session *fnode_sess);
अटल पूर्णांक qla4xxx_sysfs_ddb_login(काष्ठा iscsi_bus_flash_session *fnode_sess,
				   काष्ठा iscsi_bus_flash_conn *fnode_conn);
अटल पूर्णांक qla4xxx_sysfs_ddb_logout(काष्ठा iscsi_bus_flash_session *fnode_sess,
				    काष्ठा iscsi_bus_flash_conn *fnode_conn);
अटल पूर्णांक qla4xxx_sysfs_ddb_logout_sid(काष्ठा iscsi_cls_session *cls_sess);

अटल काष्ठा qla4_8xxx_legacy_पूर्णांकr_set legacy_पूर्णांकr[] =
    QLA82XX_LEGACY_INTR_CONFIG;

अटल स्थिर uपूर्णांक32_t qla4_82xx_reg_tbl[] = अणु
	QLA82XX_PEG_HALT_STATUS1,
	QLA82XX_PEG_HALT_STATUS2,
	QLA82XX_PEG_ALIVE_COUNTER,
	QLA82XX_CRB_DRV_ACTIVE,
	QLA82XX_CRB_DEV_STATE,
	QLA82XX_CRB_DRV_STATE,
	QLA82XX_CRB_DRV_SCRATCH,
	QLA82XX_CRB_DEV_PART_INFO,
	QLA82XX_CRB_DRV_IDC_VERSION,
	QLA82XX_FW_VERSION_MAJOR,
	QLA82XX_FW_VERSION_MINOR,
	QLA82XX_FW_VERSION_SUB,
	CRB_CMDPEG_STATE,
	CRB_TEMP_STATE,
पूर्ण;

अटल स्थिर uपूर्णांक32_t qla4_83xx_reg_tbl[] = अणु
	QLA83XX_PEG_HALT_STATUS1,
	QLA83XX_PEG_HALT_STATUS2,
	QLA83XX_PEG_ALIVE_COUNTER,
	QLA83XX_CRB_DRV_ACTIVE,
	QLA83XX_CRB_DEV_STATE,
	QLA83XX_CRB_DRV_STATE,
	QLA83XX_CRB_DRV_SCRATCH,
	QLA83XX_CRB_DEV_PART_INFO1,
	QLA83XX_CRB_IDC_VER_MAJOR,
	QLA83XX_FW_VER_MAJOR,
	QLA83XX_FW_VER_MINOR,
	QLA83XX_FW_VER_SUB,
	QLA83XX_CMDPEG_STATE,
	QLA83XX_ASIC_TEMP,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा qla4xxx_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= DRIVER_NAME,
	.proc_name		= DRIVER_NAME,
	.queuecommand		= qla4xxx_queuecommand,

	.eh_पात_handler	= qla4xxx_eh_पात,
	.eh_device_reset_handler = qla4xxx_eh_device_reset,
	.eh_target_reset_handler = qla4xxx_eh_target_reset,
	.eh_host_reset_handler	= qla4xxx_eh_host_reset,
	.eh_समयd_out		= qla4xxx_eh_cmd_समयd_out,

	.slave_alloc		= qla4xxx_slave_alloc,
	.change_queue_depth	= scsi_change_queue_depth,

	.this_id		= -1,
	.cmd_per_lun		= 3,
	.sg_tablesize		= SG_ALL,

	.max_sectors		= 0xFFFF,
	.shost_attrs		= qla4xxx_host_attrs,
	.host_reset		= qla4xxx_host_reset,
	.venकरोr_id		= SCSI_NL_VID_TYPE_PCI | PCI_VENDOR_ID_QLOGIC,
पूर्ण;

अटल काष्ठा iscsi_transport qla4xxx_iscsi_transport = अणु
	.owner			= THIS_MODULE,
	.name			= DRIVER_NAME,
	.caps			= CAP_TEXT_NEGO |
				  CAP_DATA_PATH_OFFLOAD | CAP_HDRDGST |
				  CAP_DATADGST | CAP_LOGIN_OFFLOAD |
				  CAP_MULTI_R2T,
	.attr_is_visible	= qla4_attr_is_visible,
	.create_session         = qla4xxx_session_create,
	.destroy_session        = qla4xxx_session_destroy,
	.start_conn             = qla4xxx_conn_start,
	.create_conn            = qla4xxx_conn_create,
	.bind_conn              = qla4xxx_conn_bind,
	.stop_conn              = iscsi_conn_stop,
	.destroy_conn           = qla4xxx_conn_destroy,
	.set_param              = iscsi_set_param,
	.get_conn_param		= qla4xxx_conn_get_param,
	.get_session_param	= qla4xxx_session_get_param,
	.get_ep_param           = qla4xxx_get_ep_param,
	.ep_connect		= qla4xxx_ep_connect,
	.ep_poll		= qla4xxx_ep_poll,
	.ep_disconnect		= qla4xxx_ep_disconnect,
	.get_stats		= qla4xxx_conn_get_stats,
	.send_pdu		= iscsi_conn_send_pdu,
	.xmit_task		= qla4xxx_task_xmit,
	.cleanup_task		= qla4xxx_task_cleanup,
	.alloc_pdu		= qla4xxx_alloc_pdu,

	.get_host_param		= qla4xxx_host_get_param,
	.set_अगरace_param	= qla4xxx_अगरace_set_param,
	.get_अगरace_param	= qla4xxx_get_अगरace_param,
	.bsg_request		= qla4xxx_bsg_request,
	.send_ping		= qla4xxx_send_ping,
	.get_chap		= qla4xxx_get_chap_list,
	.delete_chap		= qla4xxx_delete_chap,
	.set_chap		= qla4xxx_set_chap_entry,
	.get_flashnode_param	= qla4xxx_sysfs_ddb_get_param,
	.set_flashnode_param	= qla4xxx_sysfs_ddb_set_param,
	.new_flashnode		= qla4xxx_sysfs_ddb_add,
	.del_flashnode		= qla4xxx_sysfs_ddb_delete,
	.login_flashnode	= qla4xxx_sysfs_ddb_login,
	.logout_flashnode	= qla4xxx_sysfs_ddb_logout,
	.logout_flashnode_sid	= qla4xxx_sysfs_ddb_logout_sid,
	.get_host_stats		= qla4xxx_get_host_stats,
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *qla4xxx_scsi_transport;

अटल पूर्णांक qla4xxx_isp_check_reg(काष्ठा scsi_qla_host *ha)
अणु
	u32 reg_val = 0;
	पूर्णांक rval = QLA_SUCCESS;

	अगर (is_qla8022(ha))
		reg_val = पढ़ोl(&ha->qla4_82xx_reg->host_status);
	अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha))
		reg_val = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_ALIVE_COUNTER);
	अन्यथा
		reg_val = पढ़ोw(&ha->reg->ctrl_status);

	अगर (reg_val == QL4_ISP_REG_DISCONNECT)
		rval = QLA_ERROR;

	वापस rval;
पूर्ण

अटल पूर्णांक qla4xxx_send_ping(काष्ठा Scsi_Host *shost, uपूर्णांक32_t अगरace_num,
			     uपूर्णांक32_t अगरace_type, uपूर्णांक32_t payload_size,
			     uपूर्णांक32_t pid, काष्ठा sockaddr *dst_addr)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;
	uपूर्णांक32_t options = 0;
	uपूर्णांक8_t ipaddr[IPv6_ADDR_LEN];
	पूर्णांक rval;

	स_रखो(ipaddr, 0, IPv6_ADDR_LEN);
	/* IPv4 to IPv4 */
	अगर ((अगरace_type == ISCSI_IFACE_TYPE_IPV4) &&
	    (dst_addr->sa_family == AF_INET)) अणु
		addr = (काष्ठा sockaddr_in *)dst_addr;
		स_नकल(ipaddr, &addr->sin_addr.s_addr, IP_ADDR_LEN);
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IPv4 Ping src: %pI4 "
				  "dest: %pI4\n", __func__,
				  &ha->ip_config.ip_address, ipaddr));
		rval = qla4xxx_ping_iocb(ha, options, payload_size, pid,
					 ipaddr);
		अगर (rval)
			rval = -EINVAL;
	पूर्ण अन्यथा अगर ((अगरace_type == ISCSI_IFACE_TYPE_IPV6) &&
		   (dst_addr->sa_family == AF_INET6)) अणु
		/* IPv6 to IPv6 */
		addr6 = (काष्ठा sockaddr_in6 *)dst_addr;
		स_नकल(ipaddr, &addr6->sin6_addr.in6_u.u6_addr8, IPv6_ADDR_LEN);

		options |= PING_IPV6_PROTOCOL_ENABLE;

		/* Ping using LinkLocal address */
		अगर ((अगरace_num == 0) || (अगरace_num == 1)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: LinkLocal Ping "
					  "src: %pI6 dest: %pI6\n", __func__,
					  &ha->ip_config.ipv6_link_local_addr,
					  ipaddr));
			options |= PING_IPV6_LINKLOCAL_ADDR;
			rval = qla4xxx_ping_iocb(ha, options, payload_size,
						 pid, ipaddr);
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: iface num = %d "
				   "not supported\n", __func__, अगरace_num);
			rval = -ENOSYS;
			जाओ निकास_send_ping;
		पूर्ण

		/*
		 * If ping using LinkLocal address fails, try ping using
		 * IPv6 address
		 */
		अगर (rval != QLA_SUCCESS) अणु
			options &= ~PING_IPV6_LINKLOCAL_ADDR;
			अगर (अगरace_num == 0) अणु
				options |= PING_IPV6_ADDR0;
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IPv6 "
						  "Ping src: %pI6 "
						  "dest: %pI6\n", __func__,
						  &ha->ip_config.ipv6_addr0,
						  ipaddr));
			पूर्ण अन्यथा अगर (अगरace_num == 1) अणु
				options |= PING_IPV6_ADDR1;
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IPv6 "
						  "Ping src: %pI6 "
						  "dest: %pI6\n", __func__,
						  &ha->ip_config.ipv6_addr1,
						  ipaddr));
			पूर्ण
			rval = qla4xxx_ping_iocb(ha, options, payload_size,
						 pid, ipaddr);
			अगर (rval)
				rval = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		rval = -ENOSYS;
निकास_send_ping:
	वापस rval;
पूर्ण

अटल umode_t qla4_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_IPADDRESS:
		हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		हाल ISCSI_HOST_PARAM_PORT_STATE:
		हाल ISCSI_HOST_PARAM_PORT_SPEED:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_TARGET_ALIAS:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_CHAP_OUT_IDX:
		हाल ISCSI_PARAM_CHAP_IN_IDX:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_AUTO_SND_TGT_DISABLE:
		हाल ISCSI_PARAM_DISCOVERY_SESS:
		हाल ISCSI_PARAM_PORTAL_TYPE:
		हाल ISCSI_PARAM_CHAP_AUTH_EN:
		हाल ISCSI_PARAM_DISCOVERY_LOGOUT_EN:
		हाल ISCSI_PARAM_BIDI_CHAP_EN:
		हाल ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL:
		हाल ISCSI_PARAM_DEF_TIME2WAIT:
		हाल ISCSI_PARAM_DEF_TIME2RETAIN:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_MAX_SEGMENT_SIZE:
		हाल ISCSI_PARAM_TCP_TIMESTAMP_STAT:
		हाल ISCSI_PARAM_TCP_WSF_DISABLE:
		हाल ISCSI_PARAM_TCP_NAGLE_DISABLE:
		हाल ISCSI_PARAM_TCP_TIMER_SCALE:
		हाल ISCSI_PARAM_TCP_TIMESTAMP_EN:
		हाल ISCSI_PARAM_TCP_XMIT_WSF:
		हाल ISCSI_PARAM_TCP_RECV_WSF:
		हाल ISCSI_PARAM_IP_FRAGMENT_DISABLE:
		हाल ISCSI_PARAM_IPV4_TOS:
		हाल ISCSI_PARAM_IPV6_TC:
		हाल ISCSI_PARAM_IPV6_FLOW_LABEL:
		हाल ISCSI_PARAM_IS_FW_ASSIGNED_IPV6:
		हाल ISCSI_PARAM_KEEPALIVE_TMO:
		हाल ISCSI_PARAM_LOCAL_PORT:
		हाल ISCSI_PARAM_ISID:
		हाल ISCSI_PARAM_TSID:
		हाल ISCSI_PARAM_DEF_TASKMGMT_TMO:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_STATSN:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_DISCOVERY_PARENT_IDX:
		हाल ISCSI_PARAM_DISCOVERY_PARENT_TYPE:
		हाल ISCSI_PARAM_LOCAL_IPADDR:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_NET_PARAM:
		चयन (param) अणु
		हाल ISCSI_NET_PARAM_IPV4_ADDR:
		हाल ISCSI_NET_PARAM_IPV4_SUBNET:
		हाल ISCSI_NET_PARAM_IPV4_GW:
		हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL:
		हाल ISCSI_NET_PARAM_IPV6_ADDR:
		हाल ISCSI_NET_PARAM_IPV6_ROUTER:
		हाल ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG:
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG:
		हाल ISCSI_NET_PARAM_VLAN_ID:
		हाल ISCSI_NET_PARAM_VLAN_PRIORITY:
		हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		हाल ISCSI_NET_PARAM_MTU:
		हाल ISCSI_NET_PARAM_PORT:
		हाल ISCSI_NET_PARAM_IPADDR_STATE:
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL_STATE:
		हाल ISCSI_NET_PARAM_IPV6_ROUTER_STATE:
		हाल ISCSI_NET_PARAM_DELAYED_ACK_EN:
		हाल ISCSI_NET_PARAM_TCP_NAGLE_DISABLE:
		हाल ISCSI_NET_PARAM_TCP_WSF_DISABLE:
		हाल ISCSI_NET_PARAM_TCP_WSF:
		हाल ISCSI_NET_PARAM_TCP_TIMER_SCALE:
		हाल ISCSI_NET_PARAM_TCP_TIMESTAMP_EN:
		हाल ISCSI_NET_PARAM_CACHE_ID:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN:
		हाल ISCSI_NET_PARAM_IPV4_TOS_EN:
		हाल ISCSI_NET_PARAM_IPV4_TOS:
		हाल ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID:
		हाल ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN:
		हाल ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE:
		हाल ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN:
		हाल ISCSI_NET_PARAM_REसूचीECT_EN:
		हाल ISCSI_NET_PARAM_IPV4_TTL:
		हाल ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN:
		हाल ISCSI_NET_PARAM_IPV6_MLD_EN:
		हाल ISCSI_NET_PARAM_IPV6_FLOW_LABEL:
		हाल ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS:
		हाल ISCSI_NET_PARAM_IPV6_HOP_LIMIT:
		हाल ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO:
		हाल ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME:
		हाल ISCSI_NET_PARAM_IPV6_ND_STALE_TMO:
		हाल ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT:
		हाल ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_IFACE_PARAM:
		चयन (param) अणु
		हाल ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO:
		हाल ISCSI_IFACE_PARAM_HDRDGST_EN:
		हाल ISCSI_IFACE_PARAM_DATADGST_EN:
		हाल ISCSI_IFACE_PARAM_IMM_DATA_EN:
		हाल ISCSI_IFACE_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_IFACE_PARAM_PDU_INORDER_EN:
		हाल ISCSI_IFACE_PARAM_ERL:
		हाल ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_IFACE_PARAM_FIRST_BURST:
		हाल ISCSI_IFACE_PARAM_MAX_R2T:
		हाल ISCSI_IFACE_PARAM_MAX_BURST:
		हाल ISCSI_IFACE_PARAM_CHAP_AUTH_EN:
		हाल ISCSI_IFACE_PARAM_BIDI_CHAP_EN:
		हाल ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL:
		हाल ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN:
		हाल ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN:
		हाल ISCSI_IFACE_PARAM_INITIATOR_NAME:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_FLASHNODE_PARAM:
		चयन (param) अणु
		हाल ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6:
		हाल ISCSI_FLASHNODE_PORTAL_TYPE:
		हाल ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE:
		हाल ISCSI_FLASHNODE_DISCOVERY_SESS:
		हाल ISCSI_FLASHNODE_ENTRY_EN:
		हाल ISCSI_FLASHNODE_HDR_DGST_EN:
		हाल ISCSI_FLASHNODE_DATA_DGST_EN:
		हाल ISCSI_FLASHNODE_IMM_DATA_EN:
		हाल ISCSI_FLASHNODE_INITIAL_R2T_EN:
		हाल ISCSI_FLASHNODE_DATASEQ_INORDER:
		हाल ISCSI_FLASHNODE_PDU_INORDER:
		हाल ISCSI_FLASHNODE_CHAP_AUTH_EN:
		हाल ISCSI_FLASHNODE_SNACK_REQ_EN:
		हाल ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN:
		हाल ISCSI_FLASHNODE_BIDI_CHAP_EN:
		हाल ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL:
		हाल ISCSI_FLASHNODE_ERL:
		हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT:
		हाल ISCSI_FLASHNODE_TCP_NAGLE_DISABLE:
		हाल ISCSI_FLASHNODE_TCP_WSF_DISABLE:
		हाल ISCSI_FLASHNODE_TCP_TIMER_SCALE:
		हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_EN:
		हाल ISCSI_FLASHNODE_IP_FRAG_DISABLE:
		हाल ISCSI_FLASHNODE_MAX_RECV_DLENGTH:
		हाल ISCSI_FLASHNODE_MAX_XMIT_DLENGTH:
		हाल ISCSI_FLASHNODE_FIRST_BURST:
		हाल ISCSI_FLASHNODE_DEF_TIME2WAIT:
		हाल ISCSI_FLASHNODE_DEF_TIME2RETAIN:
		हाल ISCSI_FLASHNODE_MAX_R2T:
		हाल ISCSI_FLASHNODE_KEEPALIVE_TMO:
		हाल ISCSI_FLASHNODE_ISID:
		हाल ISCSI_FLASHNODE_TSID:
		हाल ISCSI_FLASHNODE_PORT:
		हाल ISCSI_FLASHNODE_MAX_BURST:
		हाल ISCSI_FLASHNODE_DEF_TASKMGMT_TMO:
		हाल ISCSI_FLASHNODE_IPADDR:
		हाल ISCSI_FLASHNODE_ALIAS:
		हाल ISCSI_FLASHNODE_REसूचीECT_IPADDR:
		हाल ISCSI_FLASHNODE_MAX_SEGMENT_SIZE:
		हाल ISCSI_FLASHNODE_LOCAL_PORT:
		हाल ISCSI_FLASHNODE_IPV4_TOS:
		हाल ISCSI_FLASHNODE_IPV6_TC:
		हाल ISCSI_FLASHNODE_IPV6_FLOW_LABEL:
		हाल ISCSI_FLASHNODE_NAME:
		हाल ISCSI_FLASHNODE_TPGT:
		हाल ISCSI_FLASHNODE_LINK_LOCAL_IPV6:
		हाल ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX:
		हाल ISCSI_FLASHNODE_DISCOVERY_PARENT_TYPE:
		हाल ISCSI_FLASHNODE_TCP_XMIT_WSF:
		हाल ISCSI_FLASHNODE_TCP_RECV_WSF:
		हाल ISCSI_FLASHNODE_CHAP_OUT_IDX:
		हाल ISCSI_FLASHNODE_USERNAME:
		हाल ISCSI_FLASHNODE_PASSWORD:
		हाल ISCSI_FLASHNODE_STATSN:
		हाल ISCSI_FLASHNODE_EXP_STATSN:
		हाल ISCSI_FLASHNODE_IS_BOOT_TGT:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * qla4xxx_create_chap_list - Create CHAP list from FLASH
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Read flash and make a list of CHAP entries, during login when a CHAP entry
 * is received, it will be checked in this list. If entry exist then the CHAP
 * entry index is set in the DDB. If CHAP entry करोes not exist in this list
 * then a new entry is added in FLASH in CHAP table and the index obtained is
 * used in the DDB.
 **/
अटल व्योम qla4xxx_create_chap_list(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval = 0;
	uपूर्णांक8_t *chap_flash_data = शून्य;
	uपूर्णांक32_t offset;
	dma_addr_t chap_dma;
	uपूर्णांक32_t chap_size = 0;

	अगर (is_qla40XX(ha))
		chap_size = MAX_CHAP_ENTRIES_40XX *
			    माप(काष्ठा ql4_chap_table);
	अन्यथा	/* Single region contains CHAP info क्रम both
		 * ports which is भागided पूर्णांकo half क्रम each port.
		 */
		chap_size = ha->hw.flt_chap_size / 2;

	chap_flash_data = dma_alloc_coherent(&ha->pdev->dev, chap_size,
					     &chap_dma, GFP_KERNEL);
	अगर (!chap_flash_data) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "No memory for chap_flash_data\n");
		वापस;
	पूर्ण

	अगर (is_qla40XX(ha)) अणु
		offset = FLASH_CHAP_OFFSET;
	पूर्ण अन्यथा अणु
		offset = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_region_chap << 2);
		अगर (ha->port_num == 1)
			offset += chap_size;
	पूर्ण

	rval = qla4xxx_get_flash(ha, chap_dma, offset, chap_size);
	अगर (rval != QLA_SUCCESS)
		जाओ निकास_chap_list;

	अगर (ha->chap_list == शून्य)
		ha->chap_list = vदो_स्मृति(chap_size);
	अगर (ha->chap_list == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "No memory for ha->chap_list\n");
		जाओ निकास_chap_list;
	पूर्ण

	स_रखो(ha->chap_list, 0, chap_size);
	स_नकल(ha->chap_list, chap_flash_data, chap_size);

निकास_chap_list:
	dma_मुक्त_coherent(&ha->pdev->dev, chap_size, chap_flash_data, chap_dma);
पूर्ण

अटल पूर्णांक qla4xxx_get_chap_by_index(काष्ठा scsi_qla_host *ha,
				     पूर्णांक16_t chap_index,
				     काष्ठा ql4_chap_table **chap_entry)
अणु
	पूर्णांक rval = QLA_ERROR;
	पूर्णांक max_chap_entries;

	अगर (!ha->chap_list) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "CHAP table cache is empty!\n");
		जाओ निकास_get_chap;
	पूर्ण

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
				   माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (chap_index > max_chap_entries) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Invalid Chap index\n");
		जाओ निकास_get_chap;
	पूर्ण

	*chap_entry = (काष्ठा ql4_chap_table *)ha->chap_list + chap_index;
	अगर ((*chap_entry)->cookie !=
	     __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE)) अणु
		*chap_entry = शून्य;
	पूर्ण अन्यथा अणु
		rval = QLA_SUCCESS;
	पूर्ण

निकास_get_chap:
	वापस rval;
पूर्ण

/**
 * qla4xxx_find_मुक्त_chap_index - Find the first मुक्त chap index
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @chap_index: CHAP index to be वापसed
 *
 * Find the first मुक्त chap index available in the chap table
 *
 * Note: Caller should acquire the chap lock beक्रमe getting here.
 **/
अटल पूर्णांक qla4xxx_find_मुक्त_chap_index(काष्ठा scsi_qla_host *ha,
					uपूर्णांक16_t *chap_index)
अणु
	पूर्णांक i, rval;
	पूर्णांक मुक्त_index = -1;
	पूर्णांक max_chap_entries = 0;
	काष्ठा ql4_chap_table *chap_table;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
						माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (!ha->chap_list) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "CHAP table cache is empty!\n");
		rval = QLA_ERROR;
		जाओ निकास_find_chap;
	पूर्ण

	क्रम (i = 0; i < max_chap_entries; i++) अणु
		chap_table = (काष्ठा ql4_chap_table *)ha->chap_list + i;

		अगर ((chap_table->cookie !=
		    __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE)) &&
		   (i > MAX_RESRV_CHAP_IDX)) अणु
				मुक्त_index = i;
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (मुक्त_index != -1) अणु
		*chap_index = मुक्त_index;
		rval = QLA_SUCCESS;
	पूर्ण अन्यथा अणु
		rval = QLA_ERROR;
	पूर्ण

निकास_find_chap:
	वापस rval;
पूर्ण

अटल पूर्णांक qla4xxx_get_chap_list(काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx,
				  uपूर्णांक32_t *num_entries, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा ql4_chap_table *chap_table;
	काष्ठा iscsi_chap_rec *chap_rec;
	पूर्णांक max_chap_entries = 0;
	पूर्णांक valid_chap_entries = 0;
	पूर्णांक ret = 0, i;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
					माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: num_entries = %d, CHAP idx = %d\n",
			__func__, *num_entries, chap_tbl_idx);

	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ निकास_get_chap_list;
	पूर्ण

	qla4xxx_create_chap_list(ha);

	chap_rec = (काष्ठा iscsi_chap_rec *) buf;
	mutex_lock(&ha->chap_sem);
	क्रम (i = chap_tbl_idx; i < max_chap_entries; i++) अणु
		chap_table = (काष्ठा ql4_chap_table *)ha->chap_list + i;
		अगर (chap_table->cookie !=
		    __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE))
			जारी;

		chap_rec->chap_tbl_idx = i;
		strlcpy(chap_rec->username, chap_table->name,
			ISCSI_CHAP_AUTH_NAME_MAX_LEN);
		strlcpy(chap_rec->password, chap_table->secret,
			QL4_CHAP_MAX_SECRET_LEN);
		chap_rec->password_length = chap_table->secret_len;

		अगर (chap_table->flags & BIT_7) /* local */
			chap_rec->chap_type = CHAP_TYPE_OUT;

		अगर (chap_table->flags & BIT_6) /* peer */
			chap_rec->chap_type = CHAP_TYPE_IN;

		chap_rec++;

		valid_chap_entries++;
		अगर (valid_chap_entries == *num_entries)
			अवरोध;
		अन्यथा
			जारी;
	पूर्ण
	mutex_unlock(&ha->chap_sem);

निकास_get_chap_list:
	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Valid CHAP Entries = %d\n",
			__func__,  valid_chap_entries);
	*num_entries = valid_chap_entries;
	वापस ret;
पूर्ण

अटल पूर्णांक __qla4xxx_is_chap_active(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक16_t *chap_tbl_idx = (uपूर्णांक16_t *) data;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;

	अगर (!iscsi_is_session_dev(dev))
		जाओ निकास_is_chap_active;

	cls_session = iscsi_dev_to_session(dev);
	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;

	अगर (iscsi_is_session_online(cls_session))
		जाओ निकास_is_chap_active;

	अगर (ddb_entry->chap_tbl_idx == *chap_tbl_idx)
		ret = 1;

निकास_is_chap_active:
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_is_chap_active(काष्ठा Scsi_Host *shost,
				  uपूर्णांक16_t chap_tbl_idx)
अणु
	पूर्णांक ret = 0;

	ret = device_क्रम_each_child(&shost->shost_gendev, &chap_tbl_idx,
				    __qla4xxx_is_chap_active);

	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_delete_chap(काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा ql4_chap_table *chap_table;
	dma_addr_t chap_dma;
	पूर्णांक max_chap_entries = 0;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t chap_size;
	पूर्णांक ret = 0;

	chap_table = dma_pool_zalloc(ha->chap_dma_pool, GFP_KERNEL, &chap_dma);
	अगर (chap_table == शून्य)
		वापस -ENOMEM;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
				   माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (chap_tbl_idx > max_chap_entries) अणु
		ret = -EINVAL;
		जाओ निकास_delete_chap;
	पूर्ण

	/* Check अगर chap index is in use.
	 * If chap is in use करोn't delet chap entry */
	ret = qla4xxx_is_chap_active(shost, chap_tbl_idx);
	अगर (ret) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "CHAP entry %d is in use, cannot "
			   "delete from flash\n", chap_tbl_idx);
		ret = -EBUSY;
		जाओ निकास_delete_chap;
	पूर्ण

	chap_size = माप(काष्ठा ql4_chap_table);
	अगर (is_qla40XX(ha))
		offset = FLASH_CHAP_OFFSET | (chap_tbl_idx * chap_size);
	अन्यथा अणु
		offset = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_region_chap << 2);
		/* flt_chap_size is CHAP table size क्रम both ports
		 * so भागide it by 2 to calculate the offset क्रम second port
		 */
		अगर (ha->port_num == 1)
			offset += (ha->hw.flt_chap_size / 2);
		offset += (chap_tbl_idx * chap_size);
	पूर्ण

	ret = qla4xxx_get_flash(ha, chap_dma, offset, chap_size);
	अगर (ret != QLA_SUCCESS) अणु
		ret = -EINVAL;
		जाओ निकास_delete_chap;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Chap Cookie: x%x\n",
			  __le16_to_cpu(chap_table->cookie)));

	अगर (__le16_to_cpu(chap_table->cookie) != CHAP_VALID_COOKIE) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "No valid chap entry found\n");
		जाओ निकास_delete_chap;
	पूर्ण

	chap_table->cookie = __स्थिरant_cpu_to_le16(0xFFFF);

	offset = FLASH_CHAP_OFFSET |
			(chap_tbl_idx * माप(काष्ठा ql4_chap_table));
	ret = qla4xxx_set_flash(ha, chap_dma, offset, chap_size,
				FLASH_OPT_RMW_COMMIT);
	अगर (ret == QLA_SUCCESS && ha->chap_list) अणु
		mutex_lock(&ha->chap_sem);
		/* Update ha chap_list cache */
		स_नकल((काष्ठा ql4_chap_table *)ha->chap_list + chap_tbl_idx,
			chap_table, माप(काष्ठा ql4_chap_table));
		mutex_unlock(&ha->chap_sem);
	पूर्ण
	अगर (ret != QLA_SUCCESS)
		ret =  -EINVAL;

निकास_delete_chap:
	dma_pool_मुक्त(ha->chap_dma_pool, chap_table, chap_dma);
	वापस ret;
पूर्ण

/**
 * qla4xxx_set_chap_entry - Make chap entry with given inक्रमmation
 * @shost: poपूर्णांकer to host
 * @data: chap info - credentials, index and type to make chap entry
 * @len: length of data
 *
 * Add or update chap entry with the given inक्रमmation
 **/
अटल पूर्णांक qla4xxx_set_chap_entry(काष्ठा Scsi_Host *shost, व्योम *data, पूर्णांक len)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_chap_rec chap_rec;
	काष्ठा ql4_chap_table *chap_entry = शून्य;
	काष्ठा iscsi_param_info *param_info;
	काष्ठा nlattr *attr;
	पूर्णांक max_chap_entries = 0;
	पूर्णांक type;
	पूर्णांक rem = len;
	पूर्णांक rc = 0;
	पूर्णांक size;

	स_रखो(&chap_rec, 0, माप(chap_rec));

	nla_क्रम_each_attr(attr, data, len, rem) अणु
		param_info = nla_data(attr);

		चयन (param_info->param) अणु
		हाल ISCSI_CHAP_PARAM_INDEX:
			chap_rec.chap_tbl_idx = *(uपूर्णांक16_t *)param_info->value;
			अवरोध;
		हाल ISCSI_CHAP_PARAM_CHAP_TYPE:
			chap_rec.chap_type = param_info->value[0];
			अवरोध;
		हाल ISCSI_CHAP_PARAM_USERNAME:
			size = min_t(माप_प्रकार, माप(chap_rec.username),
				     param_info->len);
			स_नकल(chap_rec.username, param_info->value, size);
			अवरोध;
		हाल ISCSI_CHAP_PARAM_PASSWORD:
			size = min_t(माप_प्रकार, माप(chap_rec.password),
				     param_info->len);
			स_नकल(chap_rec.password, param_info->value, size);
			अवरोध;
		हाल ISCSI_CHAP_PARAM_PASSWORD_LEN:
			chap_rec.password_length = param_info->value[0];
			अवरोध;
		शेष:
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "%s: No such sysfs attribute\n", __func__);
			rc = -ENOSYS;
			जाओ निकास_set_chap;
		पूर्ण
	पूर्ण

	अगर (chap_rec.chap_type == CHAP_TYPE_IN)
		type = BIDI_CHAP;
	अन्यथा
		type = LOCAL_CHAP;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
				   माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	mutex_lock(&ha->chap_sem);
	अगर (chap_rec.chap_tbl_idx < max_chap_entries) अणु
		rc = qla4xxx_get_chap_by_index(ha, chap_rec.chap_tbl_idx,
					       &chap_entry);
		अगर (!rc) अणु
			अगर (!(type == qla4xxx_get_chap_type(chap_entry))) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha,
					   "Type mismatch for CHAP entry %d\n",
					   chap_rec.chap_tbl_idx);
				rc = -EINVAL;
				जाओ निकास_unlock_chap;
			पूर्ण

			/* If chap index is in use then करोn't modअगरy it */
			rc = qla4xxx_is_chap_active(shost,
						    chap_rec.chap_tbl_idx);
			अगर (rc) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha,
					   "CHAP entry %d is in use\n",
					   chap_rec.chap_tbl_idx);
				rc = -EBUSY;
				जाओ निकास_unlock_chap;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = qla4xxx_find_मुक्त_chap_index(ha, &chap_rec.chap_tbl_idx);
		अगर (rc) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "CHAP entry not available\n");
			rc = -EBUSY;
			जाओ निकास_unlock_chap;
		पूर्ण
	पूर्ण

	rc = qla4xxx_set_chap(ha, chap_rec.username, chap_rec.password,
			      chap_rec.chap_tbl_idx, type);

निकास_unlock_chap:
	mutex_unlock(&ha->chap_sem);

निकास_set_chap:
	वापस rc;
पूर्ण


अटल पूर्णांक qla4xxx_get_host_stats(काष्ठा Scsi_Host *shost, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_offload_host_stats *host_stats = शून्य;
	पूर्णांक host_stats_size;
	पूर्णांक ret = 0;
	पूर्णांक ddb_idx = 0;
	काष्ठा ql_iscsi_stats *ql_iscsi_stats = शून्य;
	पूर्णांक stats_size;
	dma_addr_t iscsi_stats_dma;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Func: %s\n", __func__));

	host_stats_size = माप(काष्ठा iscsi_offload_host_stats);

	अगर (host_stats_size != len) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host_stats size mismatch expected = %d, is = %d\n",
			   __func__, len, host_stats_size);
		ret = -EINVAL;
		जाओ निकास_host_stats;
	पूर्ण
	host_stats = (काष्ठा iscsi_offload_host_stats *)buf;

	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ निकास_host_stats;
	पूर्ण

	stats_size = PAGE_ALIGN(माप(काष्ठा ql_iscsi_stats));

	ql_iscsi_stats = dma_alloc_coherent(&ha->pdev->dev, stats_size,
					    &iscsi_stats_dma, GFP_KERNEL);
	अगर (!ql_iscsi_stats) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "Unable to allocate memory for iscsi stats\n");
		ret = -ENOMEM;
		जाओ निकास_host_stats;
	पूर्ण

	ret =  qla4xxx_get_mgmt_data(ha, ddb_idx, stats_size,
				     iscsi_stats_dma);
	अगर (ret != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "Unable to retrieve iscsi stats\n");
		ret = -EIO;
		जाओ निकास_host_stats;
	पूर्ण
	host_stats->mactx_frames = le64_to_cpu(ql_iscsi_stats->mac_tx_frames);
	host_stats->mactx_bytes = le64_to_cpu(ql_iscsi_stats->mac_tx_bytes);
	host_stats->mactx_multicast_frames =
			le64_to_cpu(ql_iscsi_stats->mac_tx_multicast_frames);
	host_stats->mactx_broadcast_frames =
			le64_to_cpu(ql_iscsi_stats->mac_tx_broadcast_frames);
	host_stats->mactx_छोड़ो_frames =
			le64_to_cpu(ql_iscsi_stats->mac_tx_छोड़ो_frames);
	host_stats->mactx_control_frames =
			le64_to_cpu(ql_iscsi_stats->mac_tx_control_frames);
	host_stats->mactx_deferral =
			le64_to_cpu(ql_iscsi_stats->mac_tx_deferral);
	host_stats->mactx_excess_deferral =
			le64_to_cpu(ql_iscsi_stats->mac_tx_excess_deferral);
	host_stats->mactx_late_collision =
			le64_to_cpu(ql_iscsi_stats->mac_tx_late_collision);
	host_stats->mactx_पात	= le64_to_cpu(ql_iscsi_stats->mac_tx_पात);
	host_stats->mactx_single_collision =
			le64_to_cpu(ql_iscsi_stats->mac_tx_single_collision);
	host_stats->mactx_multiple_collision =
			le64_to_cpu(ql_iscsi_stats->mac_tx_multiple_collision);
	host_stats->mactx_collision =
			le64_to_cpu(ql_iscsi_stats->mac_tx_collision);
	host_stats->mactx_frames_dropped =
			le64_to_cpu(ql_iscsi_stats->mac_tx_frames_dropped);
	host_stats->mactx_jumbo_frames =
			le64_to_cpu(ql_iscsi_stats->mac_tx_jumbo_frames);
	host_stats->macrx_frames = le64_to_cpu(ql_iscsi_stats->mac_rx_frames);
	host_stats->macrx_bytes = le64_to_cpu(ql_iscsi_stats->mac_rx_bytes);
	host_stats->macrx_unknown_control_frames =
		le64_to_cpu(ql_iscsi_stats->mac_rx_unknown_control_frames);
	host_stats->macrx_छोड़ो_frames =
			le64_to_cpu(ql_iscsi_stats->mac_rx_छोड़ो_frames);
	host_stats->macrx_control_frames =
			le64_to_cpu(ql_iscsi_stats->mac_rx_control_frames);
	host_stats->macrx_dribble =
			le64_to_cpu(ql_iscsi_stats->mac_rx_dribble);
	host_stats->macrx_frame_length_error =
			le64_to_cpu(ql_iscsi_stats->mac_rx_frame_length_error);
	host_stats->macrx_jabber = le64_to_cpu(ql_iscsi_stats->mac_rx_jabber);
	host_stats->macrx_carrier_sense_error =
		le64_to_cpu(ql_iscsi_stats->mac_rx_carrier_sense_error);
	host_stats->macrx_frame_discarded =
			le64_to_cpu(ql_iscsi_stats->mac_rx_frame_discarded);
	host_stats->macrx_frames_dropped =
			le64_to_cpu(ql_iscsi_stats->mac_rx_frames_dropped);
	host_stats->mac_crc_error = le64_to_cpu(ql_iscsi_stats->mac_crc_error);
	host_stats->mac_encoding_error =
			le64_to_cpu(ql_iscsi_stats->mac_encoding_error);
	host_stats->macrx_length_error_large =
			le64_to_cpu(ql_iscsi_stats->mac_rx_length_error_large);
	host_stats->macrx_length_error_small =
			le64_to_cpu(ql_iscsi_stats->mac_rx_length_error_small);
	host_stats->macrx_multicast_frames =
			le64_to_cpu(ql_iscsi_stats->mac_rx_multicast_frames);
	host_stats->macrx_broadcast_frames =
			le64_to_cpu(ql_iscsi_stats->mac_rx_broadcast_frames);
	host_stats->iptx_packets = le64_to_cpu(ql_iscsi_stats->ip_tx_packets);
	host_stats->iptx_bytes = le64_to_cpu(ql_iscsi_stats->ip_tx_bytes);
	host_stats->iptx_fragments =
			le64_to_cpu(ql_iscsi_stats->ip_tx_fragments);
	host_stats->iprx_packets = le64_to_cpu(ql_iscsi_stats->ip_rx_packets);
	host_stats->iprx_bytes = le64_to_cpu(ql_iscsi_stats->ip_rx_bytes);
	host_stats->iprx_fragments =
			le64_to_cpu(ql_iscsi_stats->ip_rx_fragments);
	host_stats->ip_datagram_reassembly =
			le64_to_cpu(ql_iscsi_stats->ip_datagram_reassembly);
	host_stats->ip_invalid_address_error =
			le64_to_cpu(ql_iscsi_stats->ip_invalid_address_error);
	host_stats->ip_error_packets =
			le64_to_cpu(ql_iscsi_stats->ip_error_packets);
	host_stats->ip_fragrx_overlap =
			le64_to_cpu(ql_iscsi_stats->ip_fragrx_overlap);
	host_stats->ip_fragrx_outoक्रमder =
			le64_to_cpu(ql_iscsi_stats->ip_fragrx_outoक्रमder);
	host_stats->ip_datagram_reassembly_समयout =
		le64_to_cpu(ql_iscsi_stats->ip_datagram_reassembly_समयout);
	host_stats->ipv6tx_packets =
			le64_to_cpu(ql_iscsi_stats->ipv6_tx_packets);
	host_stats->ipv6tx_bytes = le64_to_cpu(ql_iscsi_stats->ipv6_tx_bytes);
	host_stats->ipv6tx_fragments =
			le64_to_cpu(ql_iscsi_stats->ipv6_tx_fragments);
	host_stats->ipv6rx_packets =
			le64_to_cpu(ql_iscsi_stats->ipv6_rx_packets);
	host_stats->ipv6rx_bytes = le64_to_cpu(ql_iscsi_stats->ipv6_rx_bytes);
	host_stats->ipv6rx_fragments =
			le64_to_cpu(ql_iscsi_stats->ipv6_rx_fragments);
	host_stats->ipv6_datagram_reassembly =
			le64_to_cpu(ql_iscsi_stats->ipv6_datagram_reassembly);
	host_stats->ipv6_invalid_address_error =
		le64_to_cpu(ql_iscsi_stats->ipv6_invalid_address_error);
	host_stats->ipv6_error_packets =
			le64_to_cpu(ql_iscsi_stats->ipv6_error_packets);
	host_stats->ipv6_fragrx_overlap =
			le64_to_cpu(ql_iscsi_stats->ipv6_fragrx_overlap);
	host_stats->ipv6_fragrx_outoक्रमder =
			le64_to_cpu(ql_iscsi_stats->ipv6_fragrx_outoक्रमder);
	host_stats->ipv6_datagram_reassembly_समयout =
		le64_to_cpu(ql_iscsi_stats->ipv6_datagram_reassembly_समयout);
	host_stats->tcptx_segments =
			le64_to_cpu(ql_iscsi_stats->tcp_tx_segments);
	host_stats->tcptx_bytes	= le64_to_cpu(ql_iscsi_stats->tcp_tx_bytes);
	host_stats->tcprx_segments =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_segments);
	host_stats->tcprx_byte = le64_to_cpu(ql_iscsi_stats->tcp_rx_byte);
	host_stats->tcp_duplicate_ack_retx =
			le64_to_cpu(ql_iscsi_stats->tcp_duplicate_ack_retx);
	host_stats->tcp_retx_समयr_expired =
			le64_to_cpu(ql_iscsi_stats->tcp_retx_समयr_expired);
	host_stats->tcprx_duplicate_ack	=
			le64_to_cpu(ql_iscsi_stats->tcp_rx_duplicate_ack);
	host_stats->tcprx_pure_ackr =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_pure_ackr);
	host_stats->tcptx_delayed_ack =
			le64_to_cpu(ql_iscsi_stats->tcp_tx_delayed_ack);
	host_stats->tcptx_pure_ack =
			le64_to_cpu(ql_iscsi_stats->tcp_tx_pure_ack);
	host_stats->tcprx_segment_error =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_segment_error);
	host_stats->tcprx_segment_outoक्रमder =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_segment_outoक्रमder);
	host_stats->tcprx_winकरोw_probe =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_winकरोw_probe);
	host_stats->tcprx_winकरोw_update =
			le64_to_cpu(ql_iscsi_stats->tcp_rx_winकरोw_update);
	host_stats->tcptx_winकरोw_probe_persist =
		le64_to_cpu(ql_iscsi_stats->tcp_tx_winकरोw_probe_persist);
	host_stats->ecc_error_correction =
			le64_to_cpu(ql_iscsi_stats->ecc_error_correction);
	host_stats->iscsi_pdu_tx = le64_to_cpu(ql_iscsi_stats->iscsi_pdu_tx);
	host_stats->iscsi_data_bytes_tx =
			le64_to_cpu(ql_iscsi_stats->iscsi_data_bytes_tx);
	host_stats->iscsi_pdu_rx = le64_to_cpu(ql_iscsi_stats->iscsi_pdu_rx);
	host_stats->iscsi_data_bytes_rx	=
			le64_to_cpu(ql_iscsi_stats->iscsi_data_bytes_rx);
	host_stats->iscsi_io_completed =
			le64_to_cpu(ql_iscsi_stats->iscsi_io_completed);
	host_stats->iscsi_unexpected_io_rx =
			le64_to_cpu(ql_iscsi_stats->iscsi_unexpected_io_rx);
	host_stats->iscsi_क्रमmat_error =
			le64_to_cpu(ql_iscsi_stats->iscsi_क्रमmat_error);
	host_stats->iscsi_hdr_digest_error =
			le64_to_cpu(ql_iscsi_stats->iscsi_hdr_digest_error);
	host_stats->iscsi_data_digest_error =
			le64_to_cpu(ql_iscsi_stats->iscsi_data_digest_error);
	host_stats->iscsi_sequence_error =
			le64_to_cpu(ql_iscsi_stats->iscsi_sequence_error);
निकास_host_stats:
	अगर (ql_iscsi_stats)
		dma_मुक्त_coherent(&ha->pdev->dev, stats_size,
				  ql_iscsi_stats, iscsi_stats_dma);

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Get host stats done\n",
		   __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_get_अगरace_param(काष्ठा iscsi_अगरace *अगरace,
				   क्रमागत iscsi_param_type param_type,
				   पूर्णांक param, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = iscsi_अगरace_to_shost(अगरace);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	पूर्णांक ival;
	अक्षर *pval = शून्य;
	पूर्णांक len = -ENOSYS;

	अगर (param_type == ISCSI_NET_PARAM) अणु
		चयन (param) अणु
		हाल ISCSI_NET_PARAM_IPV4_ADDR:
			len = प्र_लिखो(buf, "%pI4\n", &ha->ip_config.ip_address);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_SUBNET:
			len = प्र_लिखो(buf, "%pI4\n",
				      &ha->ip_config.subnet_mask);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_GW:
			len = प्र_लिखो(buf, "%pI4\n", &ha->ip_config.gateway);
			अवरोध;
		हाल ISCSI_NET_PARAM_IFACE_ENABLE:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(ha->ip_config.ipv4_options,
					 IPOPT_IPV4_PROTOCOL_ENABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(ha->ip_config.ipv6_options,
					 IPV6_OPT_IPV6_PROTOCOL_ENABLE, pval);
			पूर्ण

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
			len = प्र_लिखो(buf, "%s\n",
				      (ha->ip_config.tcp_options &
				       TCPOPT_DHCP_ENABLE) ?
				      "dhcp" : "static");
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ADDR:
			अगर (अगरace->अगरace_num == 0)
				len = प्र_लिखो(buf, "%pI6\n",
					      &ha->ip_config.ipv6_addr0);
			अगर (अगरace->अगरace_num == 1)
				len = प्र_लिखो(buf, "%pI6\n",
					      &ha->ip_config.ipv6_addr1);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL:
			len = प्र_लिखो(buf, "%pI6\n",
				      &ha->ip_config.ipv6_link_local_addr);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ROUTER:
			len = प्र_लिखो(buf, "%pI6\n",
				      &ha->ip_config.ipv6_शेष_router_addr);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG:
			pval = (ha->ip_config.ipv6_addl_options &
				IPV6_ADDOPT_NEIGHBOR_DISCOVERY_ADDR_ENABLE) ?
				"nd" : "static";

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG:
			pval = (ha->ip_config.ipv6_addl_options &
				IPV6_ADDOPT_AUTOCONFIG_LINK_LOCAL_ADDR) ?
				"auto" : "static";

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_VLAN_ID:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				ival = ha->ip_config.ipv4_vlan_tag &
				       ISCSI_MAX_VLAN_ID;
			अन्यथा
				ival = ha->ip_config.ipv6_vlan_tag &
				       ISCSI_MAX_VLAN_ID;

			len = प्र_लिखो(buf, "%d\n", ival);
			अवरोध;
		हाल ISCSI_NET_PARAM_VLAN_PRIORITY:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				ival = (ha->ip_config.ipv4_vlan_tag >> 13) &
				       ISCSI_MAX_VLAN_PRIORITY;
			अन्यथा
				ival = (ha->ip_config.ipv6_vlan_tag >> 13) &
				       ISCSI_MAX_VLAN_PRIORITY;

			len = प्र_लिखो(buf, "%d\n", ival);
			अवरोध;
		हाल ISCSI_NET_PARAM_VLAN_ENABLED:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(ha->ip_config.ipv4_options,
					 IPOPT_VLAN_TAGGING_ENABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(ha->ip_config.ipv6_options,
					 IPV6_OPT_VLAN_TAGGING_ENABLE, pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_MTU:
			len = प्र_लिखो(buf, "%d\n", ha->ip_config.eth_mtu_size);
			अवरोध;
		हाल ISCSI_NET_PARAM_PORT:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.ipv4_port);
			अन्यथा
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.ipv6_port);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPADDR_STATE:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				pval = iscsi_get_ipaddress_state_name(
						ha->ip_config.ipv4_addr_state);
			पूर्ण अन्यथा अणु
				अगर (अगरace->अगरace_num == 0)
					pval = iscsi_get_ipaddress_state_name(
						ha->ip_config.ipv6_addr0_state);
				अन्यथा अगर (अगरace->अगरace_num == 1)
					pval = iscsi_get_ipaddress_state_name(
						ha->ip_config.ipv6_addr1_state);
			पूर्ण

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL_STATE:
			pval = iscsi_get_ipaddress_state_name(
					ha->ip_config.ipv6_link_local_state);
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ROUTER_STATE:
			pval = iscsi_get_router_state_name(
				      ha->ip_config.ipv6_शेष_router_state);
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_DELAYED_ACK_EN:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(~ha->ip_config.tcp_options,
					 TCPOPT_DELAYED_ACK_DISABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(~ha->ip_config.ipv6_tcp_options,
					 IPV6_TCPOPT_DELAYED_ACK_DISABLE, pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_TCP_NAGLE_DISABLE:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(~ha->ip_config.tcp_options,
					 TCPOPT_NAGLE_ALGO_DISABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(~ha->ip_config.ipv6_tcp_options,
					 IPV6_TCPOPT_NAGLE_ALGO_DISABLE, pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_TCP_WSF_DISABLE:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(~ha->ip_config.tcp_options,
					 TCPOPT_WINDOW_SCALE_DISABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(~ha->ip_config.ipv6_tcp_options,
					 IPV6_TCPOPT_WINDOW_SCALE_DISABLE,
					 pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_TCP_WSF:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.tcp_wsf);
			अन्यथा
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.ipv6_tcp_wsf);
			अवरोध;
		हाल ISCSI_NET_PARAM_TCP_TIMER_SCALE:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				ival = (ha->ip_config.tcp_options &
					TCPOPT_TIMER_SCALE) >> 1;
			अन्यथा
				ival = (ha->ip_config.ipv6_tcp_options &
					IPV6_TCPOPT_TIMER_SCALE) >> 1;

			len = प्र_लिखो(buf, "%d\n", ival);
			अवरोध;
		हाल ISCSI_NET_PARAM_TCP_TIMESTAMP_EN:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(ha->ip_config.tcp_options,
					 TCPOPT_TIMESTAMP_ENABLE, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(ha->ip_config.ipv6_tcp_options,
					 IPV6_TCPOPT_TIMESTAMP_EN, pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_CACHE_ID:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4)
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.ipv4_cache_id);
			अन्यथा
				len = प्र_लिखो(buf, "%d\n",
					      ha->ip_config.ipv6_cache_id);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN:
			OP_STATE(ha->ip_config.tcp_options,
				 TCPOPT_DNS_SERVER_IP_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN:
			OP_STATE(ha->ip_config.tcp_options,
				 TCPOPT_SLP_DA_INFO_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_TOS_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_IPV4_TOS_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_TOS:
			len = प्र_लिखो(buf, "%d\n", ha->ip_config.ipv4_tos);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_GRAT_ARP_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN:
			OP_STATE(ha->ip_config.ipv4_options, IPOPT_ALT_CID_EN,
				 pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID:
			pval = (ha->ip_config.ipv4_alt_cid_len) ?
			       (अक्षर *)ha->ip_config.ipv4_alt_cid : "";

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_REQ_VID_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_USE_VID_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID:
			pval = (ha->ip_config.ipv4_vid_len) ?
			       (अक्षर *)ha->ip_config.ipv4_vid : "";

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_LEARN_IQN_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE:
			OP_STATE(~ha->ip_config.ipv4_options,
				 IPOPT_FRAGMENTATION_DISABLE, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN:
			OP_STATE(ha->ip_config.ipv4_options,
				 IPOPT_IN_FORWARD_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_REसूचीECT_EN:
			अगर (अगरace->अगरace_type == ISCSI_IFACE_TYPE_IPV4) अणु
				OP_STATE(ha->ip_config.ipv4_options,
					 IPOPT_ARP_REसूचीECT_EN, pval);
			पूर्ण अन्यथा अणु
				OP_STATE(ha->ip_config.ipv6_options,
					 IPV6_OPT_REसूचीECT_EN, pval);
			पूर्ण
			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV4_TTL:
			len = प्र_लिखो(buf, "%d\n", ha->ip_config.ipv4_ttl);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN:
			OP_STATE(ha->ip_config.ipv6_options,
				 IPV6_OPT_GRAT_NEIGHBOR_ADV_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_MLD_EN:
			OP_STATE(ha->ip_config.ipv6_addl_options,
				 IPV6_ADDOPT_MLD_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_FLOW_LABEL:
			len = प्र_लिखो(buf, "%u\n", ha->ip_config.ipv6_flow_lbl);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_traffic_class);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_HOP_LIMIT:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_hop_limit);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_nd_reach_समय);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_nd_rexmit_समयr);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_ND_STALE_TMO:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_nd_stale_समयout);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_dup_addr_detect_count);
			अवरोध;
		हाल ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.ipv6_gw_advrt_mtu);
			अवरोध;
		शेष:
			len = -ENOSYS;
		पूर्ण
	पूर्ण अन्यथा अगर (param_type == ISCSI_IFACE_PARAM) अणु
		चयन (param) अणु
		हाल ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO:
			len = प्र_लिखो(buf, "%d\n", ha->ip_config.def_समयout);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_HDRDGST_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_HEADER_DIGEST_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_DATADGST_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_DATA_DIGEST_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_IMM_DATA_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_IMMEDIATE_DATA_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_INITIAL_R2T_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_INITIAL_R2T_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_DATA_SEQ_INORDER_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_PDU_INORDER_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_DATA_PDU_INORDER_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_ERL:
			len = प्र_लिखो(buf, "%d\n",
				      (ha->ip_config.iscsi_options &
				       ISCSIOPTS_ERL));
			अवरोध;
		हाल ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH:
			len = प्र_लिखो(buf, "%u\n",
				      ha->ip_config.iscsi_max_pdu_size *
				      BYTE_UNITS);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_FIRST_BURST:
			len = प्र_लिखो(buf, "%u\n",
				      ha->ip_config.iscsi_first_burst_len *
				      BYTE_UNITS);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_MAX_R2T:
			len = प्र_लिखो(buf, "%d\n",
				      ha->ip_config.iscsi_max_outstnd_r2t);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_MAX_BURST:
			len = प्र_लिखो(buf, "%u\n",
				      ha->ip_config.iscsi_max_burst_len *
				      BYTE_UNITS);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_CHAP_AUTH_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_CHAP_AUTH_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_BIDI_CHAP_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_BIDI_CHAP_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_DISCOVERY_AUTH_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_DISCOVERY_LOGOUT_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN:
			OP_STATE(ha->ip_config.iscsi_options,
				 ISCSIOPTS_STRICT_LOGIN_COMP_EN, pval);

			len = प्र_लिखो(buf, "%s\n", pval);
			अवरोध;
		हाल ISCSI_IFACE_PARAM_INITIATOR_NAME:
			len = प्र_लिखो(buf, "%s\n", ha->ip_config.iscsi_name);
			अवरोध;
		शेष:
			len = -ENOSYS;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल काष्ठा iscsi_endpoपूर्णांक *
qla4xxx_ep_connect(काष्ठा Scsi_Host *shost, काष्ठा sockaddr *dst_addr,
		   पूर्णांक non_blocking)
अणु
	पूर्णांक ret;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा qla_endpoपूर्णांक *qla_ep;
	काष्ठा scsi_qla_host *ha;
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;

	अगर (!shost) अणु
		ret = -ENXIO;
		pr_err("%s: shost is NULL\n", __func__);
		वापस ERR_PTR(ret);
	पूर्ण

	ha = iscsi_host_priv(shost);
	ep = iscsi_create_endpoपूर्णांक(माप(काष्ठा qla_endpoपूर्णांक));
	अगर (!ep) अणु
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण

	qla_ep = ep->dd_data;
	स_रखो(qla_ep, 0, माप(काष्ठा qla_endpoपूर्णांक));
	अगर (dst_addr->sa_family == AF_INET) अणु
		स_नकल(&qla_ep->dst_addr, dst_addr, माप(काष्ठा sockaddr_in));
		addr = (काष्ठा sockaddr_in *)&qla_ep->dst_addr;
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: %pI4\n", __func__,
				  (अक्षर *)&addr->sin_addr));
	पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_INET6) अणु
		स_नकल(&qla_ep->dst_addr, dst_addr,
		       माप(काष्ठा sockaddr_in6));
		addr6 = (काष्ठा sockaddr_in6 *)&qla_ep->dst_addr;
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: %pI6\n", __func__,
				  (अक्षर *)&addr6->sin6_addr));
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: Invalid endpoint\n",
			   __func__);
	पूर्ण

	qla_ep->host = shost;

	वापस ep;
पूर्ण

अटल पूर्णांक qla4xxx_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा qla_endpoपूर्णांक *qla_ep;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक ret = 0;

	qla_ep = ep->dd_data;
	ha = to_qla_host(qla_ep->host);
	DEBUG2(pr_info_ratelimited("%s: host: %ld\n", __func__, ha->host_no));

	अगर (adapter_up(ha) && !test_bit(AF_BUILD_DDB_LIST, &ha->flags))
		ret = 1;

	वापस ret;
पूर्ण

अटल व्योम qla4xxx_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा qla_endpoपूर्णांक *qla_ep;
	काष्ठा scsi_qla_host *ha;

	qla_ep = ep->dd_data;
	ha = to_qla_host(qla_ep->host);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host: %ld\n", __func__,
			  ha->host_no));
	iscsi_destroy_endpoपूर्णांक(ep);
पूर्ण

अटल पूर्णांक qla4xxx_get_ep_param(काष्ठा iscsi_endpoपूर्णांक *ep,
				क्रमागत iscsi_param param,
				अक्षर *buf)
अणु
	काष्ठा qla_endpoपूर्णांक *qla_ep = ep->dd_data;
	काष्ठा sockaddr *dst_addr;
	काष्ठा scsi_qla_host *ha;

	अगर (!qla_ep)
		वापस -ENOTCONN;

	ha = to_qla_host(qla_ep->host);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host: %ld\n", __func__,
			  ha->host_no));

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_CONN_ADDRESS:
		dst_addr = (काष्ठा sockaddr *)&qla_ep->dst_addr;
		अगर (!dst_addr)
			वापस -ENOTCONN;

		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
						 &qla_ep->dst_addr, param, buf);
	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
				   काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	काष्ठा ql_iscsi_stats *ql_iscsi_stats;
	पूर्णांक stats_size;
	पूर्णांक ret;
	dma_addr_t iscsi_stats_dma;

	cls_sess = iscsi_conn_to_session(cls_conn);
	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host: %ld\n", __func__,
			  ha->host_no));
	stats_size = PAGE_ALIGN(माप(काष्ठा ql_iscsi_stats));
	/* Allocate memory */
	ql_iscsi_stats = dma_alloc_coherent(&ha->pdev->dev, stats_size,
					    &iscsi_stats_dma, GFP_KERNEL);
	अगर (!ql_iscsi_stats) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "Unable to allocate memory for iscsi stats\n");
		जाओ निकास_get_stats;
	पूर्ण

	ret =  qla4xxx_get_mgmt_data(ha, ddb_entry->fw_ddb_index, stats_size,
				     iscsi_stats_dma);
	अगर (ret != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "Unable to retrieve iscsi stats\n");
		जाओ मुक्त_stats;
	पूर्ण

	/* octets */
	stats->txdata_octets = le64_to_cpu(ql_iscsi_stats->tx_data_octets);
	stats->rxdata_octets = le64_to_cpu(ql_iscsi_stats->rx_data_octets);
	/* xmit pdus */
	stats->noptx_pdus = le32_to_cpu(ql_iscsi_stats->tx_nopout_pdus);
	stats->scsicmd_pdus = le32_to_cpu(ql_iscsi_stats->tx_scsi_cmd_pdus);
	stats->पंचांगfcmd_pdus = le32_to_cpu(ql_iscsi_stats->tx_पंचांगf_cmd_pdus);
	stats->login_pdus = le32_to_cpu(ql_iscsi_stats->tx_login_cmd_pdus);
	stats->text_pdus = le32_to_cpu(ql_iscsi_stats->tx_text_cmd_pdus);
	stats->dataout_pdus = le32_to_cpu(ql_iscsi_stats->tx_scsi_ग_लिखो_pdus);
	stats->logout_pdus = le32_to_cpu(ql_iscsi_stats->tx_logout_cmd_pdus);
	stats->snack_pdus = le32_to_cpu(ql_iscsi_stats->tx_snack_req_pdus);
	/* recv pdus */
	stats->noprx_pdus = le32_to_cpu(ql_iscsi_stats->rx_nopin_pdus);
	stats->scsirsp_pdus = le32_to_cpu(ql_iscsi_stats->rx_scsi_resp_pdus);
	stats->पंचांगfrsp_pdus = le32_to_cpu(ql_iscsi_stats->rx_पंचांगf_resp_pdus);
	stats->textrsp_pdus = le32_to_cpu(ql_iscsi_stats->rx_text_resp_pdus);
	stats->datain_pdus = le32_to_cpu(ql_iscsi_stats->rx_scsi_पढ़ो_pdus);
	stats->logoutrsp_pdus =
			le32_to_cpu(ql_iscsi_stats->rx_logout_resp_pdus);
	stats->r2t_pdus = le32_to_cpu(ql_iscsi_stats->rx_r2t_pdus);
	stats->async_pdus = le32_to_cpu(ql_iscsi_stats->rx_async_pdus);
	stats->rjt_pdus = le32_to_cpu(ql_iscsi_stats->rx_reject_pdus);

मुक्त_stats:
	dma_मुक्त_coherent(&ha->pdev->dev, stats_size, ql_iscsi_stats,
			  iscsi_stats_dma);
निकास_get_stats:
	वापस;
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस qla4xxx_eh_cmd_समयd_out(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा iscsi_cls_session *session;
	अचिन्हित दीर्घ flags;
	क्रमागत blk_eh_समयr_वापस ret = BLK_EH_DONE;

	session = starget_to_session(scsi_target(sc->device));

	spin_lock_irqsave(&session->lock, flags);
	अगर (session->state == ISCSI_SESSION_FAILED)
		ret = BLK_EH_RESET_TIMER;
	spin_unlock_irqrestore(&session->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम qla4xxx_set_port_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	uपूर्णांक32_t speed = ISCSI_PORT_SPEED_UNKNOWN;

	qla4xxx_get_firmware_state(ha);

	चयन (ha->addl_fw_state & 0x0F00) अणु
	हाल FW_ADDSTATE_LINK_SPEED_10MBPS:
		speed = ISCSI_PORT_SPEED_10MBPS;
		अवरोध;
	हाल FW_ADDSTATE_LINK_SPEED_100MBPS:
		speed = ISCSI_PORT_SPEED_100MBPS;
		अवरोध;
	हाल FW_ADDSTATE_LINK_SPEED_1GBPS:
		speed = ISCSI_PORT_SPEED_1GBPS;
		अवरोध;
	हाल FW_ADDSTATE_LINK_SPEED_10GBPS:
		speed = ISCSI_PORT_SPEED_10GBPS;
		अवरोध;
	पूर्ण
	ihost->port_speed = speed;
पूर्ण

अटल व्योम qla4xxx_set_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_cls_host *ihost = shost->shost_data;
	uपूर्णांक32_t state = ISCSI_PORT_STATE_DOWN;

	अगर (test_bit(AF_LINK_UP, &ha->flags))
		state = ISCSI_PORT_STATE_UP;

	ihost->port_state = state;
पूर्ण

अटल पूर्णांक qla4xxx_host_get_param(काष्ठा Scsi_Host *shost,
				  क्रमागत iscsi_host_param param, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	पूर्णांक len;

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_क्रमmat_mac(buf, ha->my_mac, MAC_ADDR_LEN);
		अवरोध;
	हाल ISCSI_HOST_PARAM_IPADDRESS:
		len = प्र_लिखो(buf, "%pI4\n", &ha->ip_config.ip_address);
		अवरोध;
	हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
		len = प्र_लिखो(buf, "%s\n", ha->name_string);
		अवरोध;
	हाल ISCSI_HOST_PARAM_PORT_STATE:
		qla4xxx_set_port_state(shost);
		len = प्र_लिखो(buf, "%s\n", iscsi_get_port_state_name(shost));
		अवरोध;
	हाल ISCSI_HOST_PARAM_PORT_SPEED:
		qla4xxx_set_port_speed(shost);
		len = प्र_लिखो(buf, "%s\n", iscsi_get_port_speed_name(shost));
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम qla4xxx_create_ipv4_अगरace(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->अगरace_ipv4)
		वापस;

	/* IPv4 */
	ha->अगरace_ipv4 = iscsi_create_अगरace(ha->host,
					    &qla4xxx_iscsi_transport,
					    ISCSI_IFACE_TYPE_IPV4, 0, 0);
	अगर (!ha->अगरace_ipv4)
		ql4_prपूर्णांकk(KERN_ERR, ha, "Could not create IPv4 iSCSI "
			   "iface0.\n");
पूर्ण

अटल व्योम qla4xxx_create_ipv6_अगरace(काष्ठा scsi_qla_host *ha)
अणु
	अगर (!ha->अगरace_ipv6_0)
		/* IPv6 अगरace-0 */
		ha->अगरace_ipv6_0 = iscsi_create_अगरace(ha->host,
						      &qla4xxx_iscsi_transport,
						      ISCSI_IFACE_TYPE_IPV6, 0,
						      0);
	अगर (!ha->अगरace_ipv6_0)
		ql4_prपूर्णांकk(KERN_ERR, ha, "Could not create IPv6 iSCSI "
			   "iface0.\n");

	अगर (!ha->अगरace_ipv6_1)
		/* IPv6 अगरace-1 */
		ha->अगरace_ipv6_1 = iscsi_create_अगरace(ha->host,
						      &qla4xxx_iscsi_transport,
						      ISCSI_IFACE_TYPE_IPV6, 1,
						      0);
	अगर (!ha->अगरace_ipv6_1)
		ql4_prपूर्णांकk(KERN_ERR, ha, "Could not create IPv6 iSCSI "
			   "iface1.\n");
पूर्ण

अटल व्योम qla4xxx_create_अगरaces(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->ip_config.ipv4_options & IPOPT_IPV4_PROTOCOL_ENABLE)
		qla4xxx_create_ipv4_अगरace(ha);

	अगर (ha->ip_config.ipv6_options & IPV6_OPT_IPV6_PROTOCOL_ENABLE)
		qla4xxx_create_ipv6_अगरace(ha);
पूर्ण

अटल व्योम qla4xxx_destroy_ipv4_अगरace(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->अगरace_ipv4) अणु
		iscsi_destroy_अगरace(ha->अगरace_ipv4);
		ha->अगरace_ipv4 = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_destroy_ipv6_अगरace(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->अगरace_ipv6_0) अणु
		iscsi_destroy_अगरace(ha->अगरace_ipv6_0);
		ha->अगरace_ipv6_0 = शून्य;
	पूर्ण
	अगर (ha->अगरace_ipv6_1) अणु
		iscsi_destroy_अगरace(ha->अगरace_ipv6_1);
		ha->अगरace_ipv6_1 = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_destroy_अगरaces(काष्ठा scsi_qla_host *ha)
अणु
	qla4xxx_destroy_ipv4_अगरace(ha);
	qla4xxx_destroy_ipv6_अगरace(ha);
पूर्ण

अटल व्योम qla4xxx_set_ipv6(काष्ठा scsi_qla_host *ha,
			     काष्ठा iscsi_अगरace_param_info *अगरace_param,
			     काष्ठा addr_ctrl_blk *init_fw_cb)
अणु
	/*
	 * अगरace_num 0 is valid क्रम IPv6 Addr, linklocal, router, स्वतःcfg.
	 * अगरace_num 1 is valid only क्रम IPv6 Addr.
	 */
	चयन (अगरace_param->param) अणु
	हाल ISCSI_NET_PARAM_IPV6_ADDR:
		अगर (अगरace_param->अगरace_num & 0x1)
			/* IPv6 Addr 1 */
			स_नकल(init_fw_cb->ipv6_addr1, अगरace_param->value,
			       माप(init_fw_cb->ipv6_addr1));
		अन्यथा
			/* IPv6 Addr 0 */
			स_नकल(init_fw_cb->ipv6_addr0, अगरace_param->value,
			       माप(init_fw_cb->ipv6_addr0));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		स_नकल(init_fw_cb->ipv6_अगर_id, &अगरace_param->value[8],
		       माप(init_fw_cb->ipv6_अगर_id));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ROUTER:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		स_नकल(init_fw_cb->ipv6_dflt_rtr_addr, अगरace_param->value,
		       माप(init_fw_cb->ipv6_dflt_rtr_addr));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG:
		/* Autocfg applies to even पूर्णांकerface */
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;

		अगर (अगरace_param->value[0] == ISCSI_IPV6_AUTOCFG_DISABLE)
			init_fw_cb->ipv6_addtl_opts &=
				cpu_to_le16(
				  ~IPV6_ADDOPT_NEIGHBOR_DISCOVERY_ADDR_ENABLE);
		अन्यथा अगर (अगरace_param->value[0] == ISCSI_IPV6_AUTOCFG_ND_ENABLE)
			init_fw_cb->ipv6_addtl_opts |=
				cpu_to_le16(
				  IPV6_ADDOPT_NEIGHBOR_DISCOVERY_ADDR_ENABLE);
		अन्यथा
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "Invalid autocfg setting for IPv6 addr\n");
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG:
		/* Autocfg applies to even पूर्णांकerface */
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;

		अगर (अगरace_param->value[0] ==
		    ISCSI_IPV6_LINKLOCAL_AUTOCFG_ENABLE)
			init_fw_cb->ipv6_addtl_opts |= cpu_to_le16(
					IPV6_ADDOPT_AUTOCONFIG_LINK_LOCAL_ADDR);
		अन्यथा अगर (अगरace_param->value[0] ==
			 ISCSI_IPV6_LINKLOCAL_AUTOCFG_DISABLE)
			init_fw_cb->ipv6_addtl_opts &= cpu_to_le16(
				       ~IPV6_ADDOPT_AUTOCONFIG_LINK_LOCAL_ADDR);
		अन्यथा
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "Invalid autocfg setting for IPv6 linklocal addr\n");
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ROUTER_AUTOCFG:
		/* Autocfg applies to even पूर्णांकerface */
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;

		अगर (अगरace_param->value[0] == ISCSI_IPV6_ROUTER_AUTOCFG_ENABLE)
			स_रखो(init_fw_cb->ipv6_dflt_rtr_addr, 0,
			       माप(init_fw_cb->ipv6_dflt_rtr_addr));
		अवरोध;
	हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		अगर (अगरace_param->value[0] == ISCSI_IFACE_ENABLE) अणु
			init_fw_cb->ipv6_opts |=
				cpu_to_le16(IPV6_OPT_IPV6_PROTOCOL_ENABLE);
			qla4xxx_create_ipv6_अगरace(ha);
		पूर्ण अन्यथा अणु
			init_fw_cb->ipv6_opts &=
				cpu_to_le16(~IPV6_OPT_IPV6_PROTOCOL_ENABLE &
					    0xFFFF);
			qla4xxx_destroy_ipv6_अगरace(ha);
		पूर्ण
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_TAG:
		अगर (अगरace_param->len != माप(init_fw_cb->ipv6_vlan_tag))
			अवरोध;
		init_fw_cb->ipv6_vlan_tag =
				cpu_to_be16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		अगर (अगरace_param->value[0] == ISCSI_VLAN_ENABLE)
			init_fw_cb->ipv6_opts |=
				cpu_to_le16(IPV6_OPT_VLAN_TAGGING_ENABLE);
		अन्यथा
			init_fw_cb->ipv6_opts &=
				cpu_to_le16(~IPV6_OPT_VLAN_TAGGING_ENABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_MTU:
		init_fw_cb->eth_mtu_size =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_PORT:
		/* Autocfg applies to even पूर्णांकerface */
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;

		init_fw_cb->ipv6_port =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_DELAYED_ACK_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv6_tcp_opts |=
				cpu_to_le16(IPV6_TCPOPT_DELAYED_ACK_DISABLE);
		अन्यथा
			init_fw_cb->ipv6_tcp_opts &=
				cpu_to_le16(~IPV6_TCPOPT_DELAYED_ACK_DISABLE &
					    0xFFFF);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_NAGLE_DISABLE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv6_tcp_opts |=
				cpu_to_le16(IPV6_TCPOPT_NAGLE_ALGO_DISABLE);
		अन्यथा
			init_fw_cb->ipv6_tcp_opts &=
				cpu_to_le16(~IPV6_TCPOPT_NAGLE_ALGO_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_WSF_DISABLE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv6_tcp_opts |=
				cpu_to_le16(IPV6_TCPOPT_WINDOW_SCALE_DISABLE);
		अन्यथा
			init_fw_cb->ipv6_tcp_opts &=
				cpu_to_le16(~IPV6_TCPOPT_WINDOW_SCALE_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_WSF:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_tcp_wsf = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_TIMER_SCALE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_tcp_opts &=
					cpu_to_le16(~IPV6_TCPOPT_TIMER_SCALE);
		init_fw_cb->ipv6_tcp_opts |=
				cpu_to_le16((अगरace_param->value[0] << 1) &
					    IPV6_TCPOPT_TIMER_SCALE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_TIMESTAMP_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv6_tcp_opts |=
				cpu_to_le16(IPV6_TCPOPT_TIMESTAMP_EN);
		अन्यथा
			init_fw_cb->ipv6_tcp_opts &=
				cpu_to_le16(~IPV6_TCPOPT_TIMESTAMP_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv6_opts |=
				cpu_to_le16(IPV6_OPT_GRAT_NEIGHBOR_ADV_EN);
		अन्यथा
			init_fw_cb->ipv6_opts &=
				cpu_to_le16(~IPV6_OPT_GRAT_NEIGHBOR_ADV_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_REसूचीECT_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv6_opts |=
				cpu_to_le16(IPV6_OPT_REसूचीECT_EN);
		अन्यथा
			init_fw_cb->ipv6_opts &=
				cpu_to_le16(~IPV6_OPT_REसूचीECT_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_MLD_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv6_addtl_opts |=
				cpu_to_le16(IPV6_ADDOPT_MLD_EN);
		अन्यथा
			init_fw_cb->ipv6_addtl_opts &=
				cpu_to_le16(~IPV6_ADDOPT_MLD_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_FLOW_LABEL:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_flow_lbl =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_traffic_class = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_HOP_LIMIT:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_hop_limit = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_nd_reach_समय =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_nd_rexmit_समयr =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_ND_STALE_TMO:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_nd_stale_समयout =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_dup_addr_detect_count = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv6_gw_advrt_mtu =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value);
		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "Unknown IPv6 param = %d\n",
			   अगरace_param->param);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_set_ipv4(काष्ठा scsi_qla_host *ha,
			     काष्ठा iscsi_अगरace_param_info *अगरace_param,
			     काष्ठा addr_ctrl_blk *init_fw_cb)
अणु
	चयन (अगरace_param->param) अणु
	हाल ISCSI_NET_PARAM_IPV4_ADDR:
		स_नकल(init_fw_cb->ipv4_addr, अगरace_param->value,
		       माप(init_fw_cb->ipv4_addr));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_SUBNET:
		स_नकल(init_fw_cb->ipv4_subnet,	अगरace_param->value,
		       माप(init_fw_cb->ipv4_subnet));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_GW:
		स_नकल(init_fw_cb->ipv4_gw_addr, अगरace_param->value,
		       माप(init_fw_cb->ipv4_gw_addr));
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		अगर (अगरace_param->value[0] == ISCSI_BOOTPROTO_DHCP)
			init_fw_cb->ipv4_tcp_opts |=
					cpu_to_le16(TCPOPT_DHCP_ENABLE);
		अन्यथा अगर (अगरace_param->value[0] == ISCSI_BOOTPROTO_STATIC)
			init_fw_cb->ipv4_tcp_opts &=
					cpu_to_le16(~TCPOPT_DHCP_ENABLE);
		अन्यथा
			ql4_prपूर्णांकk(KERN_ERR, ha, "Invalid IPv4 bootproto\n");
		अवरोध;
	हाल ISCSI_NET_PARAM_IFACE_ENABLE:
		अगर (अगरace_param->value[0] == ISCSI_IFACE_ENABLE) अणु
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_IPV4_PROTOCOL_ENABLE);
			qla4xxx_create_ipv4_अगरace(ha);
		पूर्ण अन्यथा अणु
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_IPV4_PROTOCOL_ENABLE &
					    0xFFFF);
			qla4xxx_destroy_ipv4_अगरace(ha);
		पूर्ण
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_TAG:
		अगर (अगरace_param->len != माप(init_fw_cb->ipv4_vlan_tag))
			अवरोध;
		init_fw_cb->ipv4_vlan_tag =
				cpu_to_be16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_VLAN_ENABLED:
		अगर (अगरace_param->value[0] == ISCSI_VLAN_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
					cpu_to_le16(IPOPT_VLAN_TAGGING_ENABLE);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
					cpu_to_le16(~IPOPT_VLAN_TAGGING_ENABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_MTU:
		init_fw_cb->eth_mtu_size =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_PORT:
		init_fw_cb->ipv4_port =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_NET_PARAM_DELAYED_ACK_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_DELAYED_ACK_DISABLE);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_DELAYED_ACK_DISABLE &
					    0xFFFF);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_NAGLE_DISABLE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_NAGLE_ALGO_DISABLE);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_NAGLE_ALGO_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_WSF_DISABLE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_WINDOW_SCALE_DISABLE);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_WINDOW_SCALE_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_WSF:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv4_tcp_wsf = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_TIMER_SCALE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv4_tcp_opts &= cpu_to_le16(~TCPOPT_TIMER_SCALE);
		init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16((अगरace_param->value[0] << 1) &
					    TCPOPT_TIMER_SCALE);
		अवरोध;
	हाल ISCSI_NET_PARAM_TCP_TIMESTAMP_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_TIMESTAMP_ENABLE);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_TIMESTAMP_ENABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_DNS_SERVER_IP_EN);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_DNS_SERVER_IP_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_tcp_opts |=
				cpu_to_le16(TCPOPT_SLP_DA_INFO_EN);
		अन्यथा
			init_fw_cb->ipv4_tcp_opts &=
				cpu_to_le16(~TCPOPT_SLP_DA_INFO_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_TOS_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_IPV4_TOS_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_IPV4_TOS_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_TOS:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv4_tos = अगरace_param->value[0];
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
					cpu_to_le16(IPOPT_GRAT_ARP_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
					cpu_to_le16(~IPOPT_GRAT_ARP_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_ALT_CID_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_ALT_CID_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		स_नकल(init_fw_cb->ipv4_dhcp_alt_cid, अगरace_param->value,
		       (माप(init_fw_cb->ipv4_dhcp_alt_cid) - 1));
		init_fw_cb->ipv4_dhcp_alt_cid_len =
					म_माप(init_fw_cb->ipv4_dhcp_alt_cid);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
					cpu_to_le16(IPOPT_REQ_VID_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
					cpu_to_le16(~IPOPT_REQ_VID_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
					cpu_to_le16(IPOPT_USE_VID_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
					cpu_to_le16(~IPOPT_USE_VID_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		स_नकल(init_fw_cb->ipv4_dhcp_vid, अगरace_param->value,
		       (माप(init_fw_cb->ipv4_dhcp_vid) - 1));
		init_fw_cb->ipv4_dhcp_vid_len =
					म_माप(init_fw_cb->ipv4_dhcp_vid);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
					cpu_to_le16(IPOPT_LEARN_IQN_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
					cpu_to_le16(~IPOPT_LEARN_IQN_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_DISABLE)
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_FRAGMENTATION_DISABLE);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_FRAGMENTATION_DISABLE);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_IN_FORWARD_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_IN_FORWARD_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_REसूचीECT_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->ipv4_ip_opts |=
				cpu_to_le16(IPOPT_ARP_REसूचीECT_EN);
		अन्यथा
			init_fw_cb->ipv4_ip_opts &=
				cpu_to_le16(~IPOPT_ARP_REसूचीECT_EN);
		अवरोध;
	हाल ISCSI_NET_PARAM_IPV4_TTL:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->ipv4_ttl = अगरace_param->value[0];
		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "Unknown IPv4 param = %d\n",
			   अगरace_param->param);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_set_iscsi_param(काष्ठा scsi_qla_host *ha,
				    काष्ठा iscsi_अगरace_param_info *अगरace_param,
				    काष्ठा addr_ctrl_blk *init_fw_cb)
अणु
	चयन (अगरace_param->param) अणु
	हाल ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->def_समयout =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_HDRDGST_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_HEADER_DIGEST_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_HEADER_DIGEST_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_DATADGST_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_DATA_DIGEST_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_DATA_DIGEST_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_IMM_DATA_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_IMMEDIATE_DATA_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_IMMEDIATE_DATA_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_INITIAL_R2T_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_INITIAL_R2T_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_INITIAL_R2T_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_DATA_SEQ_INORDER_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_DATA_SEQ_INORDER_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_PDU_INORDER_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_DATA_PDU_INORDER_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_DATA_PDU_INORDER_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_ERL:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->iscsi_opts &= cpu_to_le16(~ISCSIOPTS_ERL);
		init_fw_cb->iscsi_opts |= cpu_to_le16(अगरace_param->value[0] &
						      ISCSIOPTS_ERL);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->iscsi_max_pdu_size =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value) /
				BYTE_UNITS;
		अवरोध;
	हाल ISCSI_IFACE_PARAM_FIRST_BURST:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->iscsi_fburst_len =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value) /
				BYTE_UNITS;
		अवरोध;
	हाल ISCSI_IFACE_PARAM_MAX_R2T:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->iscsi_max_outstnd_r2t =
				cpu_to_le16(*(uपूर्णांक16_t *)अगरace_param->value);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_MAX_BURST:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		init_fw_cb->iscsi_max_burst_len =
				cpu_to_le32(*(uपूर्णांक32_t *)अगरace_param->value) /
				BYTE_UNITS;
		अवरोध;
	हाल ISCSI_IFACE_PARAM_CHAP_AUTH_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_CHAP_AUTH_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_CHAP_AUTH_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_BIDI_CHAP_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_BIDI_CHAP_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_BIDI_CHAP_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_DISCOVERY_AUTH_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_DISCOVERY_AUTH_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_DISCOVERY_LOGOUT_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_DISCOVERY_LOGOUT_EN);
		अवरोध;
	हाल ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN:
		अगर (अगरace_param->अगरace_num & 0x1)
			अवरोध;
		अगर (अगरace_param->value[0] == ISCSI_NET_PARAM_ENABLE)
			init_fw_cb->iscsi_opts |=
				cpu_to_le16(ISCSIOPTS_STRICT_LOGIN_COMP_EN);
		अन्यथा
			init_fw_cb->iscsi_opts &=
				cpu_to_le16(~ISCSIOPTS_STRICT_LOGIN_COMP_EN);
		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "Unknown iscsi param = %d\n",
			   अगरace_param->param);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
qla4xxx_initcb_to_acb(काष्ठा addr_ctrl_blk *init_fw_cb)
अणु
	काष्ठा addr_ctrl_blk_def *acb;
	acb = (काष्ठा addr_ctrl_blk_def *)init_fw_cb;
	स_रखो(acb->reserved1, 0, माप(acb->reserved1));
	स_रखो(acb->reserved2, 0, माप(acb->reserved2));
	स_रखो(acb->reserved3, 0, माप(acb->reserved3));
	स_रखो(acb->reserved4, 0, माप(acb->reserved4));
	स_रखो(acb->reserved5, 0, माप(acb->reserved5));
	स_रखो(acb->reserved6, 0, माप(acb->reserved6));
	स_रखो(acb->reserved7, 0, माप(acb->reserved7));
	स_रखो(acb->reserved8, 0, माप(acb->reserved8));
	स_रखो(acb->reserved9, 0, माप(acb->reserved9));
	स_रखो(acb->reserved10, 0, माप(acb->reserved10));
	स_रखो(acb->reserved11, 0, माप(acb->reserved11));
	स_रखो(acb->reserved12, 0, माप(acb->reserved12));
	स_रखो(acb->reserved13, 0, माप(acb->reserved13));
	स_रखो(acb->reserved14, 0, माप(acb->reserved14));
	स_रखो(acb->reserved15, 0, माप(acb->reserved15));
पूर्ण

अटल पूर्णांक
qla4xxx_अगरace_set_param(काष्ठा Scsi_Host *shost, व्योम *data, uपूर्णांक32_t len)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	पूर्णांक rval = 0;
	काष्ठा iscsi_अगरace_param_info *अगरace_param = शून्य;
	काष्ठा addr_ctrl_blk *init_fw_cb = शून्य;
	dma_addr_t init_fw_cb_dma;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	uपूर्णांक32_t rem = len;
	काष्ठा nlattr *attr;

	init_fw_cb = dma_alloc_coherent(&ha->pdev->dev,
					माप(काष्ठा addr_ctrl_blk),
					&init_fw_cb_dma, GFP_KERNEL);
	अगर (!init_fw_cb) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unable to alloc init_cb\n",
			   __func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	अगर (qla4xxx_get_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb_dma)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: get ifcb failed\n", __func__);
		rval = -EIO;
		जाओ निकास_init_fw_cb;
	पूर्ण

	nla_क्रम_each_attr(attr, data, len, rem) अणु
		अगरace_param = nla_data(attr);

		अगर (अगरace_param->param_type == ISCSI_NET_PARAM) अणु
			चयन (अगरace_param->अगरace_type) अणु
			हाल ISCSI_IFACE_TYPE_IPV4:
				चयन (अगरace_param->अगरace_num) अणु
				हाल 0:
					qla4xxx_set_ipv4(ha, अगरace_param,
							 init_fw_cb);
					अवरोध;
				शेष:
				/* Cannot have more than one IPv4 पूर्णांकerface */
					ql4_prपूर्णांकk(KERN_ERR, ha,
						   "Invalid IPv4 iface number = %d\n",
						   अगरace_param->अगरace_num);
					अवरोध;
				पूर्ण
				अवरोध;
			हाल ISCSI_IFACE_TYPE_IPV6:
				चयन (अगरace_param->अगरace_num) अणु
				हाल 0:
				हाल 1:
					qla4xxx_set_ipv6(ha, अगरace_param,
							 init_fw_cb);
					अवरोध;
				शेष:
				/* Cannot have more than two IPv6 पूर्णांकerface */
					ql4_prपूर्णांकk(KERN_ERR, ha,
						   "Invalid IPv6 iface number = %d\n",
						   अगरace_param->अगरace_num);
					अवरोध;
				पूर्ण
				अवरोध;
			शेष:
				ql4_prपूर्णांकk(KERN_ERR, ha,
					   "Invalid iface type\n");
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (अगरace_param->param_type == ISCSI_IFACE_PARAM) अणु
				qla4xxx_set_iscsi_param(ha, अगरace_param,
							init_fw_cb);
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण
	पूर्ण

	init_fw_cb->cookie = cpu_to_le32(0x11BEAD5A);

	rval = qla4xxx_set_flash(ha, init_fw_cb_dma, FLASH_SEGMENT_IFCB,
				 माप(काष्ठा addr_ctrl_blk),
				 FLASH_OPT_RMW_COMMIT);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: set flash mbx failed\n",
			   __func__);
		rval = -EIO;
		जाओ निकास_init_fw_cb;
	पूर्ण

	rval = qla4xxx_disable_acb(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: disable acb mbx failed\n",
			   __func__);
		rval = -EIO;
		जाओ निकास_init_fw_cb;
	पूर्ण

	रुको_क्रम_completion_समयout(&ha->disable_acb_comp,
				    DISABLE_ACB_TOV * HZ);

	qla4xxx_initcb_to_acb(init_fw_cb);

	rval = qla4xxx_set_acb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb_dma);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: set acb mbx failed\n",
			   __func__);
		rval = -EIO;
		जाओ निकास_init_fw_cb;
	पूर्ण

	स_रखो(init_fw_cb, 0, माप(काष्ठा addr_ctrl_blk));
	qla4xxx_update_local_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb,
				  init_fw_cb_dma);

निकास_init_fw_cb:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा addr_ctrl_blk),
			  init_fw_cb, init_fw_cb_dma);

	वापस rval;
पूर्ण

अटल पूर्णांक qla4xxx_session_get_param(काष्ठा iscsi_cls_session *cls_sess,
				     क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_session *sess = cls_sess->dd_data;
	काष्ठा ddb_entry *ddb_entry = sess->dd_data;
	काष्ठा scsi_qla_host *ha = ddb_entry->ha;
	काष्ठा iscsi_cls_conn *cls_conn = ddb_entry->conn;
	काष्ठा ql4_chap_table chap_tbl;
	पूर्णांक rval, len;
	uपूर्णांक16_t idx;

	स_रखो(&chap_tbl, 0, माप(chap_tbl));
	चयन (param) अणु
	हाल ISCSI_PARAM_CHAP_IN_IDX:
		rval = qla4xxx_get_chap_index(ha, sess->username_in,
					      sess->password_in, BIDI_CHAP,
					      &idx);
		अगर (rval)
			len = प्र_लिखो(buf, "\n");
		अन्यथा
			len = प्र_लिखो(buf, "%hu\n", idx);
		अवरोध;
	हाल ISCSI_PARAM_CHAP_OUT_IDX:
		अगर (ddb_entry->ddb_type == FLASH_DDB) अणु
			अगर (ddb_entry->chap_tbl_idx != INVALID_ENTRY) अणु
				idx = ddb_entry->chap_tbl_idx;
				rval = QLA_SUCCESS;
			पूर्ण अन्यथा अणु
				rval = QLA_ERROR;
			पूर्ण
		पूर्ण अन्यथा अणु
			rval = qla4xxx_get_chap_index(ha, sess->username,
						      sess->password,
						      LOCAL_CHAP, &idx);
		पूर्ण
		अगर (rval)
			len = प्र_लिखो(buf, "\n");
		अन्यथा
			len = प्र_लिखो(buf, "%hu\n", idx);
		अवरोध;
	हाल ISCSI_PARAM_USERNAME:
	हाल ISCSI_PARAM_PASSWORD:
		/* First, populate session username and password क्रम FLASH DDB,
		 * अगर not alपढ़ोy करोne. This happens when session login fails
		 * क्रम a FLASH DDB.
		 */
		अगर (ddb_entry->ddb_type == FLASH_DDB &&
		    ddb_entry->chap_tbl_idx != INVALID_ENTRY &&
		    !sess->username && !sess->password) अणु
			idx = ddb_entry->chap_tbl_idx;
			rval = qla4xxx_get_uni_chap_at_index(ha, chap_tbl.name,
							    chap_tbl.secret,
							    idx);
			अगर (!rval) अणु
				iscsi_set_param(cls_conn, ISCSI_PARAM_USERNAME,
						(अक्षर *)chap_tbl.name,
						म_माप((अक्षर *)chap_tbl.name));
				iscsi_set_param(cls_conn, ISCSI_PARAM_PASSWORD,
						(अक्षर *)chap_tbl.secret,
						chap_tbl.secret_len);
			पूर्ण
		पूर्ण
		fallthrough;
	शेष:
		वापस iscsi_session_get_param(cls_sess, param, buf);
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक qla4xxx_conn_get_param(काष्ठा iscsi_cls_conn *cls_conn,
				  क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा qla_conn *qla_conn;
	काष्ठा sockaddr *dst_addr;

	conn = cls_conn->dd_data;
	qla_conn = conn->dd_data;
	dst_addr = (काष्ठा sockaddr *)&qla_conn->qla_ep->dst_addr;

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_CONN_ADDRESS:
		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
						 dst_addr, param, buf);
	शेष:
		वापस iscsi_conn_get_param(cls_conn, param, buf);
	पूर्ण
पूर्ण

पूर्णांक qla4xxx_get_ddb_index(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t *ddb_index)
अणु
	uपूर्णांक32_t mbx_sts = 0;
	uपूर्णांक16_t पंचांगp_ddb_index;
	पूर्णांक ret;

get_ddb_index:
	पंचांगp_ddb_index = find_first_zero_bit(ha->ddb_idx_map, MAX_DDB_ENTRIES);

	अगर (पंचांगp_ddb_index >= MAX_DDB_ENTRIES) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Free DDB index not available\n"));
		ret = QLA_ERROR;
		जाओ निकास_get_ddb_index;
	पूर्ण

	अगर (test_and_set_bit(पंचांगp_ddb_index, ha->ddb_idx_map))
		जाओ get_ddb_index;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Found a free DDB index at %d\n", पंचांगp_ddb_index));
	ret = qla4xxx_req_ddb_entry(ha, पंचांगp_ddb_index, &mbx_sts);
	अगर (ret == QLA_ERROR) अणु
		अगर (mbx_sts == MBOX_STS_COMMAND_ERROR) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "DDB index = %d not available trying next\n",
				   पंचांगp_ddb_index);
			जाओ get_ddb_index;
		पूर्ण
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Free FW DDB not available\n"));
	पूर्ण

	*ddb_index = पंचांगp_ddb_index;

निकास_get_ddb_index:
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_match_ipaddress(काष्ठा scsi_qla_host *ha,
				   काष्ठा ddb_entry *ddb_entry,
				   अक्षर *existing_ipaddr,
				   अक्षर *user_ipaddr)
अणु
	uपूर्णांक8_t dst_ipaddr[IPv6_ADDR_LEN];
	अक्षर क्रमmatted_ipaddr[DDB_IPADDR_LEN];
	पूर्णांक status = QLA_SUCCESS, ret = 0;

	अगर (ddb_entry->fw_ddb_entry.options & DDB_OPT_IPV6_DEVICE) अणु
		ret = in6_pton(user_ipaddr, म_माप(user_ipaddr), dst_ipaddr,
			       '\0', शून्य);
		अगर (ret == 0) अणु
			status = QLA_ERROR;
			जाओ out_match;
		पूर्ण
		ret = प्र_लिखो(क्रमmatted_ipaddr, "%pI6", dst_ipaddr);
	पूर्ण अन्यथा अणु
		ret = in4_pton(user_ipaddr, म_माप(user_ipaddr), dst_ipaddr,
			       '\0', शून्य);
		अगर (ret == 0) अणु
			status = QLA_ERROR;
			जाओ out_match;
		पूर्ण
		ret = प्र_लिखो(क्रमmatted_ipaddr, "%pI4", dst_ipaddr);
	पूर्ण

	अगर (म_भेद(existing_ipaddr, क्रमmatted_ipaddr))
		status = QLA_ERROR;

out_match:
	वापस status;
पूर्ण

अटल पूर्णांक qla4xxx_match_fwdb_session(काष्ठा scsi_qla_host *ha,
				      काष्ठा iscsi_cls_conn *cls_conn)
अणु
	पूर्णांक idx = 0, max_ddbs, rval;
	काष्ठा iscsi_cls_session *cls_sess = iscsi_conn_to_session(cls_conn);
	काष्ठा iscsi_session *sess, *existing_sess;
	काष्ठा iscsi_conn *conn, *existing_conn;
	काष्ठा ddb_entry *ddb_entry;

	sess = cls_sess->dd_data;
	conn = cls_conn->dd_data;

	अगर (sess->targetname == शून्य ||
	    conn->persistent_address == शून्य ||
	    conn->persistent_port == 0)
		वापस QLA_ERROR;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	क्रम (idx = 0; idx < max_ddbs; idx++) अणु
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		अगर (ddb_entry == शून्य)
			जारी;

		अगर (ddb_entry->ddb_type != FLASH_DDB)
			जारी;

		existing_sess = ddb_entry->sess->dd_data;
		existing_conn = ddb_entry->conn->dd_data;

		अगर (existing_sess->targetname == शून्य ||
		    existing_conn->persistent_address == शून्य ||
		    existing_conn->persistent_port == 0)
			जारी;

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "IQN = %s User IQN = %s\n",
				  existing_sess->targetname,
				  sess->targetname));

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "IP = %s User IP = %s\n",
				  existing_conn->persistent_address,
				  conn->persistent_address));

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Port = %d User Port = %d\n",
				  existing_conn->persistent_port,
				  conn->persistent_port));

		अगर (म_भेद(existing_sess->targetname, sess->targetname))
			जारी;
		rval = qla4xxx_match_ipaddress(ha, ddb_entry,
					existing_conn->persistent_address,
					conn->persistent_address);
		अगर (rval == QLA_ERROR)
			जारी;
		अगर (existing_conn->persistent_port != conn->persistent_port)
			जारी;
		अवरोध;
	पूर्ण

	अगर (idx == max_ddbs)
		वापस QLA_ERROR;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Match found in fwdb sessions\n"));
	वापस QLA_SUCCESS;
पूर्ण

अटल काष्ठा iscsi_cls_session *
qla4xxx_session_create(काष्ठा iscsi_endpoपूर्णांक *ep,
			uपूर्णांक16_t cmds_max, uपूर्णांक16_t qdepth,
			uपूर्णांक32_t initial_cmdsn)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा scsi_qla_host *ha;
	काष्ठा qla_endpoपूर्णांक *qla_ep;
	काष्ठा ddb_entry *ddb_entry;
	uपूर्णांक16_t ddb_index;
	काष्ठा iscsi_session *sess;
	पूर्णांक ret;

	अगर (!ep) अणु
		prपूर्णांकk(KERN_ERR "qla4xxx: missing ep.\n");
		वापस शून्य;
	पूर्ण

	qla_ep = ep->dd_data;
	ha = to_qla_host(qla_ep->host);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host: %ld\n", __func__,
			  ha->host_no));

	ret = qla4xxx_get_ddb_index(ha, &ddb_index);
	अगर (ret == QLA_ERROR)
		वापस शून्य;

	cls_sess = iscsi_session_setup(&qla4xxx_iscsi_transport, qla_ep->host,
				       cmds_max, माप(काष्ठा ddb_entry),
				       माप(काष्ठा ql4_task_data),
				       initial_cmdsn, ddb_index);
	अगर (!cls_sess)
		वापस शून्य;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ddb_entry->fw_ddb_index = ddb_index;
	ddb_entry->fw_ddb_device_state = DDB_DS_NO_CONNECTION_ACTIVE;
	ddb_entry->ha = ha;
	ddb_entry->sess = cls_sess;
	ddb_entry->unblock_sess = qla4xxx_unblock_ddb;
	ddb_entry->ddb_change = qla4xxx_ddb_change;
	clear_bit(DDB_CONN_CLOSE_FAILURE, &ddb_entry->flags);
	cls_sess->recovery_पंचांगo = ql4xsess_recovery_पंचांगo;
	ha->fw_ddb_index_map[ddb_entry->fw_ddb_index] = ddb_entry;
	ha->tot_ddbs++;

	वापस cls_sess;
पूर्ण

अटल व्योम qla4xxx_session_destroy(काष्ठा iscsi_cls_session *cls_sess)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	अचिन्हित दीर्घ flags, wसमय;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक32_t ddb_state;
	पूर्णांक ret;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: host: %ld\n", __func__,
			  ha->host_no));

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		जाओ destroy_session;
	पूर्ण

	wसमय = jअगरfies + (HZ * LOGOUT_TOV);
	करो अणु
		ret = qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index,
					      fw_ddb_entry, fw_ddb_entry_dma,
					      शून्य, शून्य, &ddb_state, शून्य,
					      शून्य, शून्य);
		अगर (ret == QLA_ERROR)
			जाओ destroy_session;

		अगर ((ddb_state == DDB_DS_NO_CONNECTION_ACTIVE) ||
		    (ddb_state == DDB_DS_SESSION_FAILED))
			जाओ destroy_session;

		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण जबतक ((समय_after(wसमय, jअगरfies)));

destroy_session:
	qla4xxx_clear_ddb_entry(ha, ddb_entry->fw_ddb_index);
	अगर (test_and_clear_bit(DDB_CONN_CLOSE_FAILURE, &ddb_entry->flags))
		clear_bit(ddb_entry->fw_ddb_index, ha->ddb_idx_map);
	spin_lock_irqsave(&ha->hardware_lock, flags);
	qla4xxx_मुक्त_ddb(ha, ddb_entry);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	iscsi_session_tearकरोwn(cls_sess);

	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
पूर्ण

अटल काष्ठा iscsi_cls_conn *
qla4xxx_conn_create(काष्ठा iscsi_cls_session *cls_sess, uपूर्णांक32_t conn_idx)
अणु
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	cls_conn = iscsi_conn_setup(cls_sess, माप(काष्ठा qla_conn),
				    conn_idx);
	अगर (!cls_conn) अणु
		pr_info("%s: Can not create connection for conn_idx = %u\n",
			__func__, conn_idx);
		वापस शून्य;
	पूर्ण

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ddb_entry->conn = cls_conn;

	ha = ddb_entry->ha;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: conn_idx = %u\n", __func__,
			  conn_idx));
	वापस cls_conn;
पूर्ण

अटल पूर्णांक qla4xxx_conn_bind(काष्ठा iscsi_cls_session *cls_session,
			     काष्ठा iscsi_cls_conn *cls_conn,
			     uपूर्णांक64_t transport_fd, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा qla_conn *qla_conn;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	काष्ठा iscsi_session *sess;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: sid = %d, cid = %d\n", __func__,
			  cls_session->sid, cls_conn->cid));

	अगर (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		वापस -EINVAL;
	ep = iscsi_lookup_endpoपूर्णांक(transport_fd);
	अगर (!ep)
		वापस -EINVAL;
	conn = cls_conn->dd_data;
	qla_conn = conn->dd_data;
	qla_conn->qla_ep = ep->dd_data;
	वापस 0;
पूर्ण

अटल पूर्णांक qla4xxx_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_cls_session *cls_sess = iscsi_conn_to_session(cls_conn);
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक32_t mbx_sts = 0;
	पूर्णांक ret = 0;
	पूर्णांक status = QLA_SUCCESS;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: sid = %d, cid = %d\n", __func__,
			  cls_sess->sid, cls_conn->cid));

	/* Check अगर we have  matching FW DDB, अगर yes then करो not
	 * login to this target. This could cause target to logout previous
	 * connection
	 */
	ret = qla4xxx_match_fwdb_session(ha, cls_conn);
	अगर (ret == QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "Session already exist in FW.\n");
		ret = -EEXIST;
		जाओ निकास_conn_start;
	पूर्ण

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		ret = -ENOMEM;
		जाओ निकास_conn_start;
	पूर्ण

	ret = qla4xxx_set_param_ddbentry(ha, ddb_entry, cls_conn, &mbx_sts);
	अगर (ret) अणु
		/* If iscsid is stopped and started then no need to करो
		* set param again since ddb state will be alपढ़ोy
		* active and FW करोes not allow set ddb to an
		* active session.
		*/
		अगर (mbx_sts)
			अगर (ddb_entry->fw_ddb_device_state ==
						DDB_DS_SESSION_ACTIVE) अणु
				ddb_entry->unblock_sess(ddb_entry->sess);
				जाओ निकास_set_param;
			पूर्ण

		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Failed set param for index[%d]\n",
			   __func__, ddb_entry->fw_ddb_index);
		जाओ निकास_conn_start;
	पूर्ण

	status = qla4xxx_conn_खोलो(ha, ddb_entry->fw_ddb_index);
	अगर (status == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Login failed: %s\n", __func__,
			   sess->targetname);
		ret = -EINVAL;
		जाओ निकास_conn_start;
	पूर्ण

	अगर (ddb_entry->fw_ddb_device_state == DDB_DS_NO_CONNECTION_ACTIVE)
		ddb_entry->fw_ddb_device_state = DDB_DS_LOGIN_IN_PROCESS;

	DEBUG2(prपूर्णांकk(KERN_INFO "%s: DDB state [%d]\n", __func__,
		      ddb_entry->fw_ddb_device_state));

निकास_set_param:
	ret = 0;

निकास_conn_start:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	वापस ret;
पूर्ण

अटल व्योम qla4xxx_conn_destroy(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_cls_session *cls_sess = iscsi_conn_to_session(cls_conn);
	काष्ठा iscsi_session *sess;
	काष्ठा scsi_qla_host *ha;
	काष्ठा ddb_entry *ddb_entry;
	पूर्णांक options;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: cid = %d\n", __func__,
			  cls_conn->cid));

	options = LOGOUT_OPTION_CLOSE_SESSION;
	अगर (qla4xxx_session_logout_ddb(ha, ddb_entry, options) == QLA_ERROR)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Logout failed\n", __func__);
पूर्ण

अटल व्योम qla4xxx_task_work(काष्ठा work_काष्ठा *wdata)
अणु
	काष्ठा ql4_task_data *task_data;
	काष्ठा scsi_qla_host *ha;
	काष्ठा passthru_status *sts;
	काष्ठा iscsi_task *task;
	काष्ठा iscsi_hdr *hdr;
	uपूर्णांक8_t *data;
	uपूर्णांक32_t data_len;
	काष्ठा iscsi_conn *conn;
	पूर्णांक hdr_len;
	itt_t itt;

	task_data = container_of(wdata, काष्ठा ql4_task_data, task_work);
	ha = task_data->ha;
	task = task_data->task;
	sts = &task_data->sts;
	hdr_len = माप(काष्ठा iscsi_hdr);

	DEBUG3(prपूर्णांकk(KERN_INFO "Status returned\n"));
	DEBUG3(qla4xxx_dump_buffer(sts, 64));
	DEBUG3(prपूर्णांकk(KERN_INFO "Response buffer"));
	DEBUG3(qla4xxx_dump_buffer(task_data->resp_buffer, 64));

	conn = task->conn;

	चयन (sts->completionStatus) अणु
	हाल PASSTHRU_STATUS_COMPLETE:
		hdr = (काष्ठा iscsi_hdr *)task_data->resp_buffer;
		/* Assign back the itt in hdr, until we use the PREASSIGN_TAG */
		itt = sts->handle;
		hdr->itt = itt;
		data = task_data->resp_buffer + hdr_len;
		data_len = task_data->resp_len - hdr_len;
		iscsi_complete_pdu(conn, hdr, data, data_len);
		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "Passthru failed status = 0x%x\n",
			   sts->completionStatus);
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक qla4xxx_alloc_pdu(काष्ठा iscsi_task *task, uपूर्णांक8_t opcode)
अणु
	काष्ठा ql4_task_data *task_data;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक hdr_len;

	sess = task->conn->session;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	task_data = task->dd_data;
	स_रखो(task_data, 0, माप(काष्ठा ql4_task_data));

	अगर (task->sc) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: SCSI Commands not implemented\n", __func__);
		वापस -EINVAL;
	पूर्ण

	hdr_len = माप(काष्ठा iscsi_hdr);
	task_data->ha = ha;
	task_data->task = task;

	अगर (task->data_count) अणु
		task_data->data_dma = dma_map_single(&ha->pdev->dev, task->data,
						     task->data_count,
						     DMA_TO_DEVICE);
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: MaxRecvLen %u, iscsi hrd %d\n",
		      __func__, task->conn->max_recv_dlength, hdr_len));

	task_data->resp_len = task->conn->max_recv_dlength + hdr_len;
	task_data->resp_buffer = dma_alloc_coherent(&ha->pdev->dev,
						    task_data->resp_len,
						    &task_data->resp_dma,
						    GFP_ATOMIC);
	अगर (!task_data->resp_buffer)
		जाओ निकास_alloc_pdu;

	task_data->req_len = task->data_count + hdr_len;
	task_data->req_buffer = dma_alloc_coherent(&ha->pdev->dev,
						   task_data->req_len,
						   &task_data->req_dma,
						   GFP_ATOMIC);
	अगर (!task_data->req_buffer)
		जाओ निकास_alloc_pdu;

	task->hdr = task_data->req_buffer;

	INIT_WORK(&task_data->task_work, qla4xxx_task_work);

	वापस 0;

निकास_alloc_pdu:
	अगर (task_data->resp_buffer)
		dma_मुक्त_coherent(&ha->pdev->dev, task_data->resp_len,
				  task_data->resp_buffer, task_data->resp_dma);

	अगर (task_data->req_buffer)
		dma_मुक्त_coherent(&ha->pdev->dev, task_data->req_len,
				  task_data->req_buffer, task_data->req_dma);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qla4xxx_task_cleanup(काष्ठा iscsi_task *task)
अणु
	काष्ठा ql4_task_data *task_data;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक hdr_len;

	hdr_len = माप(काष्ठा iscsi_hdr);
	sess = task->conn->session;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	task_data = task->dd_data;

	अगर (task->data_count) अणु
		dma_unmap_single(&ha->pdev->dev, task_data->data_dma,
				 task->data_count, DMA_TO_DEVICE);
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: MaxRecvLen %u, iscsi hrd %d\n",
		      __func__, task->conn->max_recv_dlength, hdr_len));

	dma_मुक्त_coherent(&ha->pdev->dev, task_data->resp_len,
			  task_data->resp_buffer, task_data->resp_dma);
	dma_मुक्त_coherent(&ha->pdev->dev, task_data->req_len,
			  task_data->req_buffer, task_data->req_dma);
	वापस;
पूर्ण

अटल पूर्णांक qla4xxx_task_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा scsi_cmnd *sc = task->sc;
	काष्ठा iscsi_session *sess = task->conn->session;
	काष्ठा ddb_entry *ddb_entry = sess->dd_data;
	काष्ठा scsi_qla_host *ha = ddb_entry->ha;

	अगर (!sc)
		वापस qla4xxx_send_passthru0(task);

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: scsi cmd xmit not implemented\n",
		   __func__);
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक qla4xxx_copy_from_fwddb_param(काष्ठा iscsi_bus_flash_session *sess,
					 काष्ठा iscsi_bus_flash_conn *conn,
					 काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	अचिन्हित दीर्घ options = 0;
	पूर्णांक rc = 0;

	options = le16_to_cpu(fw_ddb_entry->options);
	conn->is_fw_asचिन्हित_ipv6 = test_bit(OPT_IS_FW_ASSIGNED_IPV6, &options);
	अगर (test_bit(OPT_IPV6_DEVICE, &options)) अणु
		rc = iscsi_चयन_str_param(&sess->portal_type,
					    PORTAL_TYPE_IPV6);
		अगर (rc)
			जाओ निकास_copy;
	पूर्ण अन्यथा अणु
		rc = iscsi_चयन_str_param(&sess->portal_type,
					    PORTAL_TYPE_IPV4);
		अगर (rc)
			जाओ निकास_copy;
	पूर्ण

	sess->स्वतः_snd_tgt_disable = test_bit(OPT_AUTO_SENDTGTS_DISABLE,
					      &options);
	sess->discovery_sess = test_bit(OPT_DISC_SESSION, &options);
	sess->entry_state = test_bit(OPT_ENTRY_STATE, &options);

	options = le16_to_cpu(fw_ddb_entry->iscsi_options);
	conn->hdrdgst_en = test_bit(ISCSIOPT_HEADER_DIGEST_EN, &options);
	conn->datadgst_en = test_bit(ISCSIOPT_DATA_DIGEST_EN, &options);
	sess->imm_data_en = test_bit(ISCSIOPT_IMMEDIATE_DATA_EN, &options);
	sess->initial_r2t_en = test_bit(ISCSIOPT_INITIAL_R2T_EN, &options);
	sess->dataseq_inorder_en = test_bit(ISCSIOPT_DATA_SEQ_IN_ORDER,
					    &options);
	sess->pdu_inorder_en = test_bit(ISCSIOPT_DATA_PDU_IN_ORDER, &options);
	sess->chap_auth_en = test_bit(ISCSIOPT_CHAP_AUTH_EN, &options);
	conn->snack_req_en = test_bit(ISCSIOPT_SNACK_REQ_EN, &options);
	sess->discovery_logout_en = test_bit(ISCSIOPT_DISCOVERY_LOGOUT_EN,
					     &options);
	sess->bidi_chap_en = test_bit(ISCSIOPT_BIDI_CHAP_EN, &options);
	sess->discovery_auth_optional =
			test_bit(ISCSIOPT_DISCOVERY_AUTH_OPTIONAL, &options);
	अगर (test_bit(ISCSIOPT_ERL1, &options))
		sess->erl |= BIT_1;
	अगर (test_bit(ISCSIOPT_ERL0, &options))
		sess->erl |= BIT_0;

	options = le16_to_cpu(fw_ddb_entry->tcp_options);
	conn->tcp_बारtamp_stat = test_bit(TCPOPT_TIMESTAMP_STAT, &options);
	conn->tcp_nagle_disable = test_bit(TCPOPT_NAGLE_DISABLE, &options);
	conn->tcp_wsf_disable = test_bit(TCPOPT_WSF_DISABLE, &options);
	अगर (test_bit(TCPOPT_TIMER_SCALE3, &options))
		conn->tcp_समयr_scale |= BIT_3;
	अगर (test_bit(TCPOPT_TIMER_SCALE2, &options))
		conn->tcp_समयr_scale |= BIT_2;
	अगर (test_bit(TCPOPT_TIMER_SCALE1, &options))
		conn->tcp_समयr_scale |= BIT_1;

	conn->tcp_समयr_scale >>= 1;
	conn->tcp_बारtamp_en = test_bit(TCPOPT_TIMESTAMP_EN, &options);

	options = le16_to_cpu(fw_ddb_entry->ip_options);
	conn->fragment_disable = test_bit(IPOPT_FRAGMENT_DISABLE, &options);

	conn->max_recv_dlength = BYTE_UNITS *
			  le16_to_cpu(fw_ddb_entry->iscsi_max_rcv_data_seg_len);
	conn->max_xmit_dlength = BYTE_UNITS *
			  le16_to_cpu(fw_ddb_entry->iscsi_max_snd_data_seg_len);
	sess->first_burst = BYTE_UNITS *
			       le16_to_cpu(fw_ddb_entry->iscsi_first_burst_len);
	sess->max_burst = BYTE_UNITS *
				 le16_to_cpu(fw_ddb_entry->iscsi_max_burst_len);
	sess->max_r2t = le16_to_cpu(fw_ddb_entry->iscsi_max_outsnd_r2t);
	sess->समय2रुको = le16_to_cpu(fw_ddb_entry->iscsi_def_समय2रुको);
	sess->समय2retain = le16_to_cpu(fw_ddb_entry->iscsi_def_समय2retain);
	sess->tpgt = le32_to_cpu(fw_ddb_entry->tgt_portal_grp);
	conn->max_segment_size = le16_to_cpu(fw_ddb_entry->mss);
	conn->tcp_xmit_wsf = fw_ddb_entry->tcp_xmt_wsf;
	conn->tcp_recv_wsf = fw_ddb_entry->tcp_rcv_wsf;
	conn->ipv6_flow_label = le16_to_cpu(fw_ddb_entry->ipv6_flow_lbl);
	conn->keepalive_समयout = le16_to_cpu(fw_ddb_entry->ka_समयout);
	conn->local_port = le16_to_cpu(fw_ddb_entry->lcl_port);
	conn->statsn = le32_to_cpu(fw_ddb_entry->stat_sn);
	conn->exp_statsn = le32_to_cpu(fw_ddb_entry->exp_stat_sn);
	sess->discovery_parent_idx = le16_to_cpu(fw_ddb_entry->ddb_link);
	sess->discovery_parent_type = le16_to_cpu(fw_ddb_entry->ddb_link);
	sess->chap_out_idx = le16_to_cpu(fw_ddb_entry->chap_tbl_idx);
	sess->tsid = le16_to_cpu(fw_ddb_entry->tsid);

	sess->शेष_taskmgmt_समयout =
				le16_to_cpu(fw_ddb_entry->def_समयout);
	conn->port = le16_to_cpu(fw_ddb_entry->port);

	options = le16_to_cpu(fw_ddb_entry->options);
	conn->ipaddress = kzalloc(IPv6_ADDR_LEN, GFP_KERNEL);
	अगर (!conn->ipaddress) अणु
		rc = -ENOMEM;
		जाओ निकास_copy;
	पूर्ण

	conn->redirect_ipaddr = kzalloc(IPv6_ADDR_LEN, GFP_KERNEL);
	अगर (!conn->redirect_ipaddr) अणु
		rc = -ENOMEM;
		जाओ निकास_copy;
	पूर्ण

	स_नकल(conn->ipaddress, fw_ddb_entry->ip_addr, IPv6_ADDR_LEN);
	स_नकल(conn->redirect_ipaddr, fw_ddb_entry->tgt_addr, IPv6_ADDR_LEN);

	अगर (test_bit(OPT_IPV6_DEVICE, &options)) अणु
		conn->ipv6_traffic_class = fw_ddb_entry->ipv4_tos;

		conn->link_local_ipv6_addr = kmemdup(
					fw_ddb_entry->link_local_ipv6_addr,
					IPv6_ADDR_LEN, GFP_KERNEL);
		अगर (!conn->link_local_ipv6_addr) अणु
			rc = -ENOMEM;
			जाओ निकास_copy;
		पूर्ण
	पूर्ण अन्यथा अणु
		conn->ipv4_tos = fw_ddb_entry->ipv4_tos;
	पूर्ण

	अगर (fw_ddb_entry->iscsi_name[0]) अणु
		rc = iscsi_चयन_str_param(&sess->targetname,
					    (अक्षर *)fw_ddb_entry->iscsi_name);
		अगर (rc)
			जाओ निकास_copy;
	पूर्ण

	अगर (fw_ddb_entry->iscsi_alias[0]) अणु
		rc = iscsi_चयन_str_param(&sess->targetalias,
					    (अक्षर *)fw_ddb_entry->iscsi_alias);
		अगर (rc)
			जाओ निकास_copy;
	पूर्ण

	COPY_ISID(sess->isid, fw_ddb_entry->isid);

निकास_copy:
	वापस rc;
पूर्ण

अटल पूर्णांक qla4xxx_copy_to_fwddb_param(काष्ठा iscsi_bus_flash_session *sess,
				       काष्ठा iscsi_bus_flash_conn *conn,
				       काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	uपूर्णांक16_t options;
	पूर्णांक rc = 0;

	options = le16_to_cpu(fw_ddb_entry->options);
	SET_BITVAL(conn->is_fw_asचिन्हित_ipv6,  options, BIT_11);
	अगर (!म_भेदन(sess->portal_type, PORTAL_TYPE_IPV6, 4))
		options |= BIT_8;
	अन्यथा
		options &= ~BIT_8;

	SET_BITVAL(sess->स्वतः_snd_tgt_disable, options, BIT_6);
	SET_BITVAL(sess->discovery_sess, options, BIT_4);
	SET_BITVAL(sess->entry_state, options, BIT_3);
	fw_ddb_entry->options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->iscsi_options);
	SET_BITVAL(conn->hdrdgst_en, options, BIT_13);
	SET_BITVAL(conn->datadgst_en, options, BIT_12);
	SET_BITVAL(sess->imm_data_en, options, BIT_11);
	SET_BITVAL(sess->initial_r2t_en, options, BIT_10);
	SET_BITVAL(sess->dataseq_inorder_en, options, BIT_9);
	SET_BITVAL(sess->pdu_inorder_en, options, BIT_8);
	SET_BITVAL(sess->chap_auth_en, options, BIT_7);
	SET_BITVAL(conn->snack_req_en, options, BIT_6);
	SET_BITVAL(sess->discovery_logout_en, options, BIT_5);
	SET_BITVAL(sess->bidi_chap_en, options, BIT_4);
	SET_BITVAL(sess->discovery_auth_optional, options, BIT_3);
	SET_BITVAL(sess->erl & BIT_1, options, BIT_1);
	SET_BITVAL(sess->erl & BIT_0, options, BIT_0);
	fw_ddb_entry->iscsi_options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->tcp_options);
	SET_BITVAL(conn->tcp_बारtamp_stat, options, BIT_6);
	SET_BITVAL(conn->tcp_nagle_disable, options, BIT_5);
	SET_BITVAL(conn->tcp_wsf_disable, options, BIT_4);
	SET_BITVAL(conn->tcp_समयr_scale & BIT_2, options, BIT_3);
	SET_BITVAL(conn->tcp_समयr_scale & BIT_1, options, BIT_2);
	SET_BITVAL(conn->tcp_समयr_scale & BIT_0, options, BIT_1);
	SET_BITVAL(conn->tcp_बारtamp_en, options, BIT_0);
	fw_ddb_entry->tcp_options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->ip_options);
	SET_BITVAL(conn->fragment_disable, options, BIT_4);
	fw_ddb_entry->ip_options = cpu_to_le16(options);

	fw_ddb_entry->iscsi_max_outsnd_r2t = cpu_to_le16(sess->max_r2t);
	fw_ddb_entry->iscsi_max_rcv_data_seg_len =
			       cpu_to_le16(conn->max_recv_dlength / BYTE_UNITS);
	fw_ddb_entry->iscsi_max_snd_data_seg_len =
			       cpu_to_le16(conn->max_xmit_dlength / BYTE_UNITS);
	fw_ddb_entry->iscsi_first_burst_len =
				cpu_to_le16(sess->first_burst / BYTE_UNITS);
	fw_ddb_entry->iscsi_max_burst_len = cpu_to_le16(sess->max_burst /
					    BYTE_UNITS);
	fw_ddb_entry->iscsi_def_समय2रुको = cpu_to_le16(sess->समय2रुको);
	fw_ddb_entry->iscsi_def_समय2retain = cpu_to_le16(sess->समय2retain);
	fw_ddb_entry->tgt_portal_grp = cpu_to_le16(sess->tpgt);
	fw_ddb_entry->mss = cpu_to_le16(conn->max_segment_size);
	fw_ddb_entry->tcp_xmt_wsf = (uपूर्णांक8_t) cpu_to_le32(conn->tcp_xmit_wsf);
	fw_ddb_entry->tcp_rcv_wsf = (uपूर्णांक8_t) cpu_to_le32(conn->tcp_recv_wsf);
	fw_ddb_entry->ipv6_flow_lbl = cpu_to_le16(conn->ipv6_flow_label);
	fw_ddb_entry->ka_समयout = cpu_to_le16(conn->keepalive_समयout);
	fw_ddb_entry->lcl_port = cpu_to_le16(conn->local_port);
	fw_ddb_entry->stat_sn = cpu_to_le32(conn->statsn);
	fw_ddb_entry->exp_stat_sn = cpu_to_le32(conn->exp_statsn);
	fw_ddb_entry->ddb_link = cpu_to_le16(sess->discovery_parent_idx);
	fw_ddb_entry->chap_tbl_idx = cpu_to_le16(sess->chap_out_idx);
	fw_ddb_entry->tsid = cpu_to_le16(sess->tsid);
	fw_ddb_entry->port = cpu_to_le16(conn->port);
	fw_ddb_entry->def_समयout =
				cpu_to_le16(sess->शेष_taskmgmt_समयout);

	अगर (!म_भेदन(sess->portal_type, PORTAL_TYPE_IPV6, 4))
		fw_ddb_entry->ipv4_tos = conn->ipv6_traffic_class;
	अन्यथा
		fw_ddb_entry->ipv4_tos = conn->ipv4_tos;

	अगर (conn->ipaddress)
		स_नकल(fw_ddb_entry->ip_addr, conn->ipaddress,
		       माप(fw_ddb_entry->ip_addr));

	अगर (conn->redirect_ipaddr)
		स_नकल(fw_ddb_entry->tgt_addr, conn->redirect_ipaddr,
		       माप(fw_ddb_entry->tgt_addr));

	अगर (conn->link_local_ipv6_addr)
		स_नकल(fw_ddb_entry->link_local_ipv6_addr,
		       conn->link_local_ipv6_addr,
		       माप(fw_ddb_entry->link_local_ipv6_addr));

	अगर (sess->targetname)
		स_नकल(fw_ddb_entry->iscsi_name, sess->targetname,
		       माप(fw_ddb_entry->iscsi_name));

	अगर (sess->targetalias)
		स_नकल(fw_ddb_entry->iscsi_alias, sess->targetalias,
		       माप(fw_ddb_entry->iscsi_alias));

	COPY_ISID(fw_ddb_entry->isid, sess->isid);

	वापस rc;
पूर्ण

अटल व्योम qla4xxx_copy_to_sess_conn_params(काष्ठा iscsi_conn *conn,
					     काष्ठा iscsi_session *sess,
					     काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	अचिन्हित दीर्घ options = 0;
	uपूर्णांक16_t ddb_link;
	uपूर्णांक16_t disc_parent;
	अक्षर ip_addr[DDB_IPADDR_LEN];

	options = le16_to_cpu(fw_ddb_entry->options);
	conn->is_fw_asचिन्हित_ipv6 = test_bit(OPT_IS_FW_ASSIGNED_IPV6, &options);
	sess->स्वतः_snd_tgt_disable = test_bit(OPT_AUTO_SENDTGTS_DISABLE,
					      &options);
	sess->discovery_sess = test_bit(OPT_DISC_SESSION, &options);

	options = le16_to_cpu(fw_ddb_entry->iscsi_options);
	conn->hdrdgst_en = test_bit(ISCSIOPT_HEADER_DIGEST_EN, &options);
	conn->datadgst_en = test_bit(ISCSIOPT_DATA_DIGEST_EN, &options);
	sess->imm_data_en = test_bit(ISCSIOPT_IMMEDIATE_DATA_EN, &options);
	sess->initial_r2t_en = test_bit(ISCSIOPT_INITIAL_R2T_EN, &options);
	sess->dataseq_inorder_en = test_bit(ISCSIOPT_DATA_SEQ_IN_ORDER,
					    &options);
	sess->pdu_inorder_en = test_bit(ISCSIOPT_DATA_PDU_IN_ORDER, &options);
	sess->chap_auth_en = test_bit(ISCSIOPT_CHAP_AUTH_EN, &options);
	sess->discovery_logout_en = test_bit(ISCSIOPT_DISCOVERY_LOGOUT_EN,
					     &options);
	sess->bidi_chap_en = test_bit(ISCSIOPT_BIDI_CHAP_EN, &options);
	sess->discovery_auth_optional =
			test_bit(ISCSIOPT_DISCOVERY_AUTH_OPTIONAL, &options);
	अगर (test_bit(ISCSIOPT_ERL1, &options))
		sess->erl |= BIT_1;
	अगर (test_bit(ISCSIOPT_ERL0, &options))
		sess->erl |= BIT_0;

	options = le16_to_cpu(fw_ddb_entry->tcp_options);
	conn->tcp_बारtamp_stat = test_bit(TCPOPT_TIMESTAMP_STAT, &options);
	conn->tcp_nagle_disable = test_bit(TCPOPT_NAGLE_DISABLE, &options);
	conn->tcp_wsf_disable = test_bit(TCPOPT_WSF_DISABLE, &options);
	अगर (test_bit(TCPOPT_TIMER_SCALE3, &options))
		conn->tcp_समयr_scale |= BIT_3;
	अगर (test_bit(TCPOPT_TIMER_SCALE2, &options))
		conn->tcp_समयr_scale |= BIT_2;
	अगर (test_bit(TCPOPT_TIMER_SCALE1, &options))
		conn->tcp_समयr_scale |= BIT_1;

	conn->tcp_समयr_scale >>= 1;
	conn->tcp_बारtamp_en = test_bit(TCPOPT_TIMESTAMP_EN, &options);

	options = le16_to_cpu(fw_ddb_entry->ip_options);
	conn->fragment_disable = test_bit(IPOPT_FRAGMENT_DISABLE, &options);

	conn->max_recv_dlength = BYTE_UNITS *
			  le16_to_cpu(fw_ddb_entry->iscsi_max_rcv_data_seg_len);
	conn->max_xmit_dlength = BYTE_UNITS *
			  le16_to_cpu(fw_ddb_entry->iscsi_max_snd_data_seg_len);
	sess->max_r2t = le16_to_cpu(fw_ddb_entry->iscsi_max_outsnd_r2t);
	sess->first_burst = BYTE_UNITS *
			       le16_to_cpu(fw_ddb_entry->iscsi_first_burst_len);
	sess->max_burst = BYTE_UNITS *
				 le16_to_cpu(fw_ddb_entry->iscsi_max_burst_len);
	sess->समय2रुको = le16_to_cpu(fw_ddb_entry->iscsi_def_समय2रुको);
	sess->समय2retain = le16_to_cpu(fw_ddb_entry->iscsi_def_समय2retain);
	sess->tpgt = le32_to_cpu(fw_ddb_entry->tgt_portal_grp);
	conn->max_segment_size = le16_to_cpu(fw_ddb_entry->mss);
	conn->tcp_xmit_wsf = fw_ddb_entry->tcp_xmt_wsf;
	conn->tcp_recv_wsf = fw_ddb_entry->tcp_rcv_wsf;
	conn->ipv4_tos = fw_ddb_entry->ipv4_tos;
	conn->keepalive_पंचांगo = le16_to_cpu(fw_ddb_entry->ka_समयout);
	conn->local_port = le16_to_cpu(fw_ddb_entry->lcl_port);
	conn->statsn = le32_to_cpu(fw_ddb_entry->stat_sn);
	conn->exp_statsn = le32_to_cpu(fw_ddb_entry->exp_stat_sn);
	sess->tsid = le16_to_cpu(fw_ddb_entry->tsid);
	COPY_ISID(sess->isid, fw_ddb_entry->isid);

	ddb_link = le16_to_cpu(fw_ddb_entry->ddb_link);
	अगर (ddb_link == DDB_ISNS)
		disc_parent = ISCSI_DISC_PARENT_ISNS;
	अन्यथा अगर (ddb_link == DDB_NO_LINK)
		disc_parent = ISCSI_DISC_PARENT_UNKNOWN;
	अन्यथा अगर (ddb_link < MAX_DDB_ENTRIES)
		disc_parent = ISCSI_DISC_PARENT_SENDTGT;
	अन्यथा
		disc_parent = ISCSI_DISC_PARENT_UNKNOWN;

	iscsi_set_param(conn->cls_conn, ISCSI_PARAM_DISCOVERY_PARENT_TYPE,
			iscsi_get_discovery_parent_name(disc_parent), 0);

	iscsi_set_param(conn->cls_conn, ISCSI_PARAM_TARGET_ALIAS,
			(अक्षर *)fw_ddb_entry->iscsi_alias, 0);

	options = le16_to_cpu(fw_ddb_entry->options);
	अगर (options & DDB_OPT_IPV6_DEVICE) अणु
		स_रखो(ip_addr, 0, माप(ip_addr));
		प्र_लिखो(ip_addr, "%pI6", fw_ddb_entry->link_local_ipv6_addr);
		iscsi_set_param(conn->cls_conn, ISCSI_PARAM_LOCAL_IPADDR,
				(अक्षर *)ip_addr, 0);
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_copy_fwddb_param(काष्ठा scsi_qla_host *ha,
				     काष्ठा dev_db_entry *fw_ddb_entry,
				     काष्ठा iscsi_cls_session *cls_sess,
				     काष्ठा iscsi_cls_conn *cls_conn)
अणु
	पूर्णांक buflen = 0;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा ql4_chap_table chap_tbl;
	काष्ठा iscsi_conn *conn;
	अक्षर ip_addr[DDB_IPADDR_LEN];
	uपूर्णांक16_t options = 0;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	conn = cls_conn->dd_data;
	स_रखो(&chap_tbl, 0, माप(chap_tbl));

	ddb_entry->chap_tbl_idx = le16_to_cpu(fw_ddb_entry->chap_tbl_idx);

	qla4xxx_copy_to_sess_conn_params(conn, sess, fw_ddb_entry);

	sess->def_taskmgmt_पंचांगo = le16_to_cpu(fw_ddb_entry->def_समयout);
	conn->persistent_port = le16_to_cpu(fw_ddb_entry->port);

	स_रखो(ip_addr, 0, माप(ip_addr));
	options = le16_to_cpu(fw_ddb_entry->options);
	अगर (options & DDB_OPT_IPV6_DEVICE) अणु
		iscsi_set_param(cls_conn, ISCSI_PARAM_PORTAL_TYPE, "ipv6", 4);

		स_रखो(ip_addr, 0, माप(ip_addr));
		प्र_लिखो(ip_addr, "%pI6", fw_ddb_entry->ip_addr);
	पूर्ण अन्यथा अणु
		iscsi_set_param(cls_conn, ISCSI_PARAM_PORTAL_TYPE, "ipv4", 4);
		प्र_लिखो(ip_addr, "%pI4", fw_ddb_entry->ip_addr);
	पूर्ण

	iscsi_set_param(cls_conn, ISCSI_PARAM_PERSISTENT_ADDRESS,
			(अक्षर *)ip_addr, buflen);
	iscsi_set_param(cls_conn, ISCSI_PARAM_TARGET_NAME,
			(अक्षर *)fw_ddb_entry->iscsi_name, buflen);
	iscsi_set_param(cls_conn, ISCSI_PARAM_INITIATOR_NAME,
			(अक्षर *)ha->name_string, buflen);

	अगर (ddb_entry->chap_tbl_idx != INVALID_ENTRY) अणु
		अगर (!qla4xxx_get_uni_chap_at_index(ha, chap_tbl.name,
						   chap_tbl.secret,
						   ddb_entry->chap_tbl_idx)) अणु
			iscsi_set_param(cls_conn, ISCSI_PARAM_USERNAME,
					(अक्षर *)chap_tbl.name,
					म_माप((अक्षर *)chap_tbl.name));
			iscsi_set_param(cls_conn, ISCSI_PARAM_PASSWORD,
					(अक्षर *)chap_tbl.secret,
					chap_tbl.secret_len);
		पूर्ण
	पूर्ण
पूर्ण

व्योम qla4xxx_update_session_conn_fwddb_param(काष्ठा scsi_qla_host *ha,
					     काष्ठा ddb_entry *ddb_entry)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	uपूर्णांक32_t ddb_state;
	dma_addr_t fw_ddb_entry_dma;
	काष्ठा dev_db_entry *fw_ddb_entry;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		जाओ निकास_session_conn_fwddb_param;
	पूर्ण

	अगर (qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index, fw_ddb_entry,
				    fw_ddb_entry_dma, शून्य, शून्य, &ddb_state,
				    शून्य, शून्य, शून्य) == QLA_ERROR) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: failed "
				  "get_ddb_entry for fw_ddb_index %d\n",
				  ha->host_no, __func__,
				  ddb_entry->fw_ddb_index));
		जाओ निकास_session_conn_fwddb_param;
	पूर्ण

	cls_sess = ddb_entry->sess;

	cls_conn = ddb_entry->conn;

	/* Update params */
	qla4xxx_copy_fwddb_param(ha, fw_ddb_entry, cls_sess, cls_conn);

निकास_session_conn_fwddb_param:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
पूर्ण

व्योम qla4xxx_update_session_conn_param(काष्ठा scsi_qla_host *ha,
				       काष्ठा ddb_entry *ddb_entry)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_conn *conn;
	uपूर्णांक32_t ddb_state;
	dma_addr_t fw_ddb_entry_dma;
	काष्ठा dev_db_entry *fw_ddb_entry;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		जाओ निकास_session_conn_param;
	पूर्ण

	अगर (qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index, fw_ddb_entry,
				    fw_ddb_entry_dma, शून्य, शून्य, &ddb_state,
				    शून्य, शून्य, शून्य) == QLA_ERROR) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: failed "
				  "get_ddb_entry for fw_ddb_index %d\n",
				  ha->host_no, __func__,
				  ddb_entry->fw_ddb_index));
		जाओ निकास_session_conn_param;
	पूर्ण

	cls_sess = ddb_entry->sess;
	sess = cls_sess->dd_data;

	cls_conn = ddb_entry->conn;
	conn = cls_conn->dd_data;

	/* Update समयrs after login */
	ddb_entry->शेष_relogin_समयout =
		(le16_to_cpu(fw_ddb_entry->def_समयout) > LOGIN_TOV) &&
		 (le16_to_cpu(fw_ddb_entry->def_समयout) < LOGIN_TOV * 10) ?
		 le16_to_cpu(fw_ddb_entry->def_समयout) : LOGIN_TOV;
	ddb_entry->शेष_समय2रुको =
				le16_to_cpu(fw_ddb_entry->iscsi_def_समय2रुको);

	/* Update params */
	ddb_entry->chap_tbl_idx = le16_to_cpu(fw_ddb_entry->chap_tbl_idx);
	qla4xxx_copy_to_sess_conn_params(conn, sess, fw_ddb_entry);

	स_नकल(sess->initiatorname, ha->name_string,
	       min(माप(ha->name_string), माप(sess->initiatorname)));

निकास_session_conn_param:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
पूर्ण

/*
 * Timer routines
 */
अटल व्योम qla4xxx_समयr(काष्ठा समयr_list *t);

अटल व्योम qla4xxx_start_समयr(काष्ठा scsi_qla_host *ha,
				अचिन्हित दीर्घ पूर्णांकerval)
अणु
	DEBUG(prपूर्णांकk("scsi: %s: Starting timer thread for adapter %d\n",
		     __func__, ha->host->host_no));
	समयr_setup(&ha->समयr, qla4xxx_समयr, 0);
	ha->समयr.expires = jअगरfies + पूर्णांकerval * HZ;
	add_समयr(&ha->समयr);
	ha->समयr_active = 1;
पूर्ण

अटल व्योम qla4xxx_stop_समयr(काष्ठा scsi_qla_host *ha)
अणु
	del_समयr_sync(&ha->समयr);
	ha->समयr_active = 0;
पूर्ण

/***
 * qla4xxx_mark_device_missing - blocks the session
 * @cls_session: Poपूर्णांकer to the session to be blocked
 * @ddb_entry: Poपूर्णांकer to device database entry
 *
 * This routine marks a device missing and बंद connection.
 **/
व्योम qla4xxx_mark_device_missing(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_block_session(cls_session);
पूर्ण

/**
 * qla4xxx_mark_all_devices_missing - mark all devices as missing.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine marks a device missing and resets the relogin retry count.
 **/
व्योम qla4xxx_mark_all_devices_missing(काष्ठा scsi_qla_host *ha)
अणु
	iscsi_host_क्रम_each_session(ha->host, qla4xxx_mark_device_missing);
पूर्ण

अटल काष्ठा srb* qla4xxx_get_new_srb(काष्ठा scsi_qla_host *ha,
				       काष्ठा ddb_entry *ddb_entry,
				       काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा srb *srb;

	srb = mempool_alloc(ha->srb_mempool, GFP_ATOMIC);
	अगर (!srb)
		वापस srb;

	kref_init(&srb->srb_ref);
	srb->ha = ha;
	srb->ddb = ddb_entry;
	srb->cmd = cmd;
	srb->flags = 0;
	CMD_SP(cmd) = (व्योम *)srb;

	वापस srb;
पूर्ण

अटल व्योम qla4xxx_srb_मुक्त_dma(काष्ठा scsi_qla_host *ha, काष्ठा srb *srb)
अणु
	काष्ठा scsi_cmnd *cmd = srb->cmd;

	अगर (srb->flags & SRB_DMA_VALID) अणु
		scsi_dma_unmap(cmd);
		srb->flags &= ~SRB_DMA_VALID;
	पूर्ण
	CMD_SP(cmd) = शून्य;
पूर्ण

व्योम qla4xxx_srb_compl(काष्ठा kref *ref)
अणु
	काष्ठा srb *srb = container_of(ref, काष्ठा srb, srb_ref);
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	काष्ठा scsi_qla_host *ha = srb->ha;

	qla4xxx_srb_मुक्त_dma(ha, srb);

	mempool_मुक्त(srb, ha->srb_mempool);

	cmd->scsi_करोne(cmd);
पूर्ण

/**
 * qla4xxx_queuecommand - scsi layer issues scsi command to driver.
 * @host: scsi host
 * @cmd: Poपूर्णांकer to Linux's SCSI command काष्ठाure
 *
 * Remarks:
 * This routine is invoked by Linux to send a SCSI command to the driver.
 * The mid-level driver tries to ensure that queuecommand never माला_लो
 * invoked concurrently with itself or the पूर्णांकerrupt handler (although
 * the पूर्णांकerrupt handler may call this routine as part of request-
 * completion handling).   Unक्रमtunely, it someबार calls the scheduler
 * in पूर्णांकerrupt context which is a big NO! NO!.
 **/
अटल पूर्णांक qla4xxx_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(host);
	काष्ठा ddb_entry *ddb_entry = cmd->device->hostdata;
	काष्ठा iscsi_cls_session *sess = ddb_entry->sess;
	काष्ठा srb *srb;
	पूर्णांक rval;

	अगर (test_bit(AF_EEH_BUSY, &ha->flags)) अणु
		अगर (test_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags))
			cmd->result = DID_NO_CONNECT << 16;
		अन्यथा
			cmd->result = DID_REQUEUE << 16;
		जाओ qc_fail_command;
	पूर्ण

	अगर (!sess) अणु
		cmd->result = DID_IMM_RETRY << 16;
		जाओ qc_fail_command;
	पूर्ण

	rval = iscsi_session_chkपढ़ोy(sess);
	अगर (rval) अणु
		cmd->result = rval;
		जाओ qc_fail_command;
	पूर्ण

	अगर (test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	    test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags) ||
	    test_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags) ||
	    !test_bit(AF_ONLINE, &ha->flags) ||
	    !test_bit(AF_LINK_UP, &ha->flags) ||
	    test_bit(AF_LOOPBACK, &ha->flags) ||
	    test_bit(DPC_POST_IDC_ACK, &ha->dpc_flags) ||
	    test_bit(DPC_RESTORE_ACB, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags))
		जाओ qc_host_busy;

	srb = qla4xxx_get_new_srb(ha, ddb_entry, cmd);
	अगर (!srb)
		जाओ qc_host_busy;

	rval = qla4xxx_send_command_to_isp(ha, srb);
	अगर (rval != QLA_SUCCESS)
		जाओ qc_host_busy_मुक्त_sp;

	वापस 0;

qc_host_busy_मुक्त_sp:
	qla4xxx_srb_मुक्त_dma(ha, srb);
	mempool_मुक्त(srb, ha->srb_mempool);

qc_host_busy:
	वापस SCSI_MLQUEUE_HOST_BUSY;

qc_fail_command:
	cmd->scsi_करोne(cmd);

	वापस 0;
पूर्ण

/**
 * qla4xxx_mem_मुक्त - मुक्तs memory allocated to adapter
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Frees memory previously allocated by qla4xxx_mem_alloc
 **/
अटल व्योम qla4xxx_mem_मुक्त(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->queues)
		dma_मुक्त_coherent(&ha->pdev->dev, ha->queues_len, ha->queues,
				  ha->queues_dma);

	vमुक्त(ha->fw_dump);

	ha->queues_len = 0;
	ha->queues = शून्य;
	ha->queues_dma = 0;
	ha->request_ring = शून्य;
	ha->request_dma = 0;
	ha->response_ring = शून्य;
	ha->response_dma = 0;
	ha->shaकरोw_regs = शून्य;
	ha->shaकरोw_regs_dma = 0;
	ha->fw_dump = शून्य;
	ha->fw_dump_size = 0;

	/* Free srb pool. */
	mempool_destroy(ha->srb_mempool);
	ha->srb_mempool = शून्य;

	dma_pool_destroy(ha->chap_dma_pool);

	vमुक्त(ha->chap_list);
	ha->chap_list = शून्य;

	dma_pool_destroy(ha->fw_ddb_dma_pool);

	/* release io space रेजिस्टरs  */
	अगर (is_qla8022(ha)) अणु
		अगर (ha->nx_pcibase)
			iounmap(
			    (काष्ठा device_reg_82xx __iomem *)ha->nx_pcibase);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		अगर (ha->nx_pcibase)
			iounmap(
			    (काष्ठा device_reg_83xx __iomem *)ha->nx_pcibase);
	पूर्ण अन्यथा अगर (ha->reg) अणु
		iounmap(ha->reg);
	पूर्ण

	vमुक्त(ha->reset_पंचांगplt.buff);

	pci_release_regions(ha->pdev);
पूर्ण

/**
 * qla4xxx_mem_alloc - allocates memory क्रम use by adapter.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure
 *
 * Allocates DMA memory क्रम request and response queues. Also allocates memory
 * क्रम srbs.
 **/
अटल पूर्णांक qla4xxx_mem_alloc(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ align;

	/* Allocate contiguous block of DMA memory क्रम queues. */
	ha->queues_len = ((REQUEST_QUEUE_DEPTH * QUEUE_SIZE) +
			  (RESPONSE_QUEUE_DEPTH * QUEUE_SIZE) +
			  माप(काष्ठा shaकरोw_regs) +
			  MEM_ALIGN_VALUE +
			  (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1);
	ha->queues = dma_alloc_coherent(&ha->pdev->dev, ha->queues_len,
					&ha->queues_dma, GFP_KERNEL);
	अगर (ha->queues == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "Memory Allocation failed - queues.\n");

		जाओ mem_alloc_error_निकास;
	पूर्ण

	/*
	 * As per RISC alignment requirements -- the bus-address must be a
	 * multiple of the request-ring size (in bytes).
	 */
	align = 0;
	अगर ((अचिन्हित दीर्घ)ha->queues_dma & (MEM_ALIGN_VALUE - 1))
		align = MEM_ALIGN_VALUE - ((अचिन्हित दीर्घ)ha->queues_dma &
					   (MEM_ALIGN_VALUE - 1));

	/* Update request and response queue poपूर्णांकers. */
	ha->request_dma = ha->queues_dma + align;
	ha->request_ring = (काष्ठा queue_entry *) (ha->queues + align);
	ha->response_dma = ha->queues_dma + align +
		(REQUEST_QUEUE_DEPTH * QUEUE_SIZE);
	ha->response_ring = (काष्ठा queue_entry *) (ha->queues + align +
						    (REQUEST_QUEUE_DEPTH *
						     QUEUE_SIZE));
	ha->shaकरोw_regs_dma = ha->queues_dma + align +
		(REQUEST_QUEUE_DEPTH * QUEUE_SIZE) +
		(RESPONSE_QUEUE_DEPTH * QUEUE_SIZE);
	ha->shaकरोw_regs = (काष्ठा shaकरोw_regs *) (ha->queues + align +
						  (REQUEST_QUEUE_DEPTH *
						   QUEUE_SIZE) +
						  (RESPONSE_QUEUE_DEPTH *
						   QUEUE_SIZE));

	/* Allocate memory क्रम srb pool. */
	ha->srb_mempool = mempool_create(SRB_MIN_REQ, mempool_alloc_slab,
					 mempool_मुक्त_slab, srb_cachep);
	अगर (ha->srb_mempool == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "Memory Allocation failed - SRB Pool.\n");

		जाओ mem_alloc_error_निकास;
	पूर्ण

	ha->chap_dma_pool = dma_pool_create("ql4_chap", &ha->pdev->dev,
					    CHAP_DMA_BLOCK_SIZE, 8, 0);

	अगर (ha->chap_dma_pool == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "%s: chap_dma_pool allocation failed..\n", __func__);
		जाओ mem_alloc_error_निकास;
	पूर्ण

	ha->fw_ddb_dma_pool = dma_pool_create("ql4_fw_ddb", &ha->pdev->dev,
					      DDB_DMA_BLOCK_SIZE, 8, 0);

	अगर (ha->fw_ddb_dma_pool == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "%s: fw_ddb_dma_pool allocation failed..\n",
			   __func__);
		जाओ mem_alloc_error_निकास;
	पूर्ण

	वापस QLA_SUCCESS;

mem_alloc_error_निकास:
	वापस QLA_ERROR;
पूर्ण

/**
 * qla4_8xxx_check_temp - Check the ISP82XX temperature.
 * @ha: adapter block poपूर्णांकer.
 *
 * Note: The caller should not hold the idc lock.
 **/
अटल पूर्णांक qla4_8xxx_check_temp(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t temp, temp_state, temp_val;
	पूर्णांक status = QLA_SUCCESS;

	temp = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_TEMP_STATE);

	temp_state = qla82xx_get_temp_state(temp);
	temp_val = qla82xx_get_temp_val(temp);

	अगर (temp_state == QLA82XX_TEMP_PANIC) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Device temperature %d degrees C"
			   " exceeds maximum allowed. Hardware has been shut"
			   " down.\n", temp_val);
		status = QLA_ERROR;
	पूर्ण अन्यथा अगर (temp_state == QLA82XX_TEMP_WARN) अणु
		अगर (ha->temperature == QLA82XX_TEMP_NORMAL)
			ql4_prपूर्णांकk(KERN_WARNING, ha, "Device temperature %d"
				   " degrees C exceeds operating range."
				   " Immediate action needed.\n", temp_val);
	पूर्ण अन्यथा अणु
		अगर (ha->temperature == QLA82XX_TEMP_WARN)
			ql4_prपूर्णांकk(KERN_INFO, ha, "Device temperature is"
				   " now %d degrees C in normal range.\n",
				   temp_val);
	पूर्ण
	ha->temperature = temp_state;
	वापस status;
पूर्ण

/**
 * qla4_8xxx_check_fw_alive  - Check firmware health
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Context: Interrupt
 **/
अटल पूर्णांक qla4_8xxx_check_fw_alive(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t fw_heartbeat_counter;
	पूर्णांक status = QLA_SUCCESS;

	fw_heartbeat_counter = qla4_8xxx_rd_direct(ha,
						   QLA8XXX_PEG_ALIVE_COUNTER);
	/* If PEG_ALIVE_COUNTER is 0xffffffff, AER/EEH is in progress, ignore */
	अगर (fw_heartbeat_counter == 0xffffffff) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING "scsi%ld: %s: Device in frozen "
		    "state, QLA82XX_PEG_ALIVE_COUNTER is 0xffffffff\n",
		    ha->host_no, __func__));
		वापस status;
	पूर्ण

	अगर (ha->fw_heartbeat_counter == fw_heartbeat_counter) अणु
		ha->seconds_since_last_heartbeat++;
		/* FW not alive after 2 seconds */
		अगर (ha->seconds_since_last_heartbeat == 2) अणु
			ha->seconds_since_last_heartbeat = 0;
			qla4_8xxx_dump_peg_reg(ha);
			status = QLA_ERROR;
		पूर्ण
	पूर्ण अन्यथा
		ha->seconds_since_last_heartbeat = 0;

	ha->fw_heartbeat_counter = fw_heartbeat_counter;
	वापस status;
पूर्ण

अटल व्योम qla4_8xxx_process_fw_error(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t halt_status;
	पूर्णांक halt_status_unrecoverable = 0;

	halt_status = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_HALT_STATUS1);

	अगर (is_qla8022(ha)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: disabling pause transmit on port 0 & 1.\n",
			   __func__);
		qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x98,
				CRB_NIU_XG_PAUSE_CTL_P0 |
				CRB_NIU_XG_PAUSE_CTL_P1);

		अगर (QLA82XX_FWERROR_CODE(halt_status) == 0x67)
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Firmware aborted with error code 0x00006700. Device is being reset\n",
				   __func__);
		अगर (halt_status & HALT_STATUS_UNRECOVERABLE)
			halt_status_unrecoverable = 1;
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		अगर (halt_status & QLA83XX_HALT_STATUS_FW_RESET)
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Firmware error detected device is being reset\n",
				   __func__);
		अन्यथा अगर (halt_status & QLA83XX_HALT_STATUS_UNRECOVERABLE)
			halt_status_unrecoverable = 1;
	पूर्ण

	/*
	 * Since we cannot change dev_state in पूर्णांकerrupt context,
	 * set appropriate DPC flag then wakeup DPC
	 */
	अगर (halt_status_unrecoverable) अणु
		set_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags);
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: detect abort needed!\n",
			   __func__);
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
	पूर्ण
	qla4xxx_mailbox_premature_completion(ha);
	qla4xxx_wake_dpc(ha);
पूर्ण

/**
 * qla4_8xxx_watchकरोg - Poll dev state
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Context: Interrupt
 **/
व्योम qla4_8xxx_watchकरोg(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t dev_state;
	uपूर्णांक32_t idc_ctrl;

	अगर (is_qla8032(ha) &&
	    (qla4_83xx_is_detached(ha) == QLA_SUCCESS))
		WARN_ONCE(1, "%s: iSCSI function %d marked invisible\n",
			  __func__, ha->func_num);

	/* करोn't poll अगर reset is going on */
	अगर (!(test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	    test_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags))) अणु
		dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);

		अगर (qla4_8xxx_check_temp(ha)) अणु
			अगर (is_qla8022(ha)) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "disabling pause transmit on port 0 & 1.\n");
				qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x98,
						CRB_NIU_XG_PAUSE_CTL_P0 |
						CRB_NIU_XG_PAUSE_CTL_P1);
			पूर्ण
			set_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags);
			qla4xxx_wake_dpc(ha);
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_RESET &&
			   !test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु

			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: HW State: NEED RESET!\n",
				   __func__);

			अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				idc_ctrl = qla4_83xx_rd_reg(ha,
							QLA83XX_IDC_DRV_CTRL);
				अगर (!(idc_ctrl & GRACEFUL_RESET_BIT1)) अणु
					ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Graceful reset bit is not set\n",
						   __func__);
					qla4xxx_mailbox_premature_completion(
									    ha);
				पूर्ण
			पूर्ण

			अगर ((is_qla8032(ha) || is_qla8042(ha)) ||
			    (is_qla8022(ha) && !ql4xकरोntresethba)) अणु
				set_bit(DPC_RESET_HA, &ha->dpc_flags);
				qla4xxx_wake_dpc(ha);
			पूर्ण
		पूर्ण अन्यथा अगर (dev_state == QLA8XXX_DEV_NEED_QUIESCENT &&
		    !test_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: HW State: NEED QUIES!\n",
			    __func__);
			set_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags);
			qla4xxx_wake_dpc(ha);
		पूर्ण अन्यथा  अणु
			/* Check firmware health */
			अगर (qla4_8xxx_check_fw_alive(ha))
				qla4_8xxx_process_fw_error(ha);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_check_relogin_flash_ddb(काष्ठा iscsi_cls_session *cls_sess)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	अगर (!(ddb_entry->ddb_type == FLASH_DDB))
		वापस;

	अगर (adapter_up(ha) && !test_bit(DF_RELOGIN, &ddb_entry->flags) &&
	    !iscsi_is_session_online(cls_sess)) अणु
		अगर (atomic_पढ़ो(&ddb_entry->retry_relogin_समयr) !=
		    INVALID_ENTRY) अणु
			अगर (atomic_पढ़ो(&ddb_entry->retry_relogin_समयr) ==
					0) अणु
				atomic_set(&ddb_entry->retry_relogin_समयr,
					   INVALID_ENTRY);
				set_bit(DPC_RELOGIN_DEVICE, &ha->dpc_flags);
				set_bit(DF_RELOGIN, &ddb_entry->flags);
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				       "%s: index [%d] login device\n",
					__func__, ddb_entry->fw_ddb_index));
			पूर्ण अन्यथा
				atomic_dec(&ddb_entry->retry_relogin_समयr);
		पूर्ण
	पूर्ण

	/* Wait क्रम relogin to समयout */
	अगर (atomic_पढ़ो(&ddb_entry->relogin_समयr) &&
	    (atomic_dec_and_test(&ddb_entry->relogin_समयr) != 0)) अणु
		/*
		 * If the relogin बार out and the device is
		 * still NOT ONLINE then try and relogin again.
		 */
		अगर (!iscsi_is_session_online(cls_sess)) अणु
			/* Reset retry relogin समयr */
			atomic_inc(&ddb_entry->relogin_retry_count);
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				"%s: index[%d] relogin timed out-retrying"
				" relogin (%d), retry (%d)\n", __func__,
				ddb_entry->fw_ddb_index,
				atomic_पढ़ो(&ddb_entry->relogin_retry_count),
				ddb_entry->शेष_समय2रुको + 4));
			set_bit(DPC_RELOGIN_DEVICE, &ha->dpc_flags);
			atomic_set(&ddb_entry->retry_relogin_समयr,
				   ddb_entry->शेष_समय2रुको + 4);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * qla4xxx_समयr - checks every second क्रम work to करो.
 * @t: Context to obtain poपूर्णांकer to host adapter काष्ठाure.
 **/
अटल व्योम qla4xxx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा scsi_qla_host *ha = from_समयr(ha, t, समयr);
	पूर्णांक start_dpc = 0;
	uपूर्णांक16_t w;

	iscsi_host_क्रम_each_session(ha->host, qla4xxx_check_relogin_flash_ddb);

	/* If we are in the middle of AER/EEH processing
	 * skip any processing and reschedule the समयr
	 */
	अगर (test_bit(AF_EEH_BUSY, &ha->flags)) अणु
		mod_समयr(&ha->समयr, jअगरfies + HZ);
		वापस;
	पूर्ण

	/* Hardware पढ़ो to trigger an EEH error during mailbox रुकोs. */
	अगर (!pci_channel_offline(ha->pdev))
		pci_पढ़ो_config_word(ha->pdev, PCI_VENDOR_ID, &w);

	अगर (is_qla80XX(ha))
		qla4_8xxx_watchकरोg(ha);

	अगर (is_qla40XX(ha)) अणु
		/* Check क्रम heartbeat पूर्णांकerval. */
		अगर (ha->firmware_options & FWOPT_HEARTBEAT_ENABLE &&
		    ha->heartbeat_पूर्णांकerval != 0) अणु
			ha->seconds_since_last_heartbeat++;
			अगर (ha->seconds_since_last_heartbeat >
			    ha->heartbeat_पूर्णांकerval + 2)
				set_bit(DPC_RESET_HA, &ha->dpc_flags);
		पूर्ण
	पूर्ण

	/* Process any deferred work. */
	अगर (!list_empty(&ha->work_list))
		start_dpc++;

	/* Wakeup the dpc routine क्रम this adapter, अगर needed. */
	अगर (start_dpc ||
	     test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	     test_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags) ||
	     test_bit(DPC_RELOGIN_DEVICE, &ha->dpc_flags) ||
	     test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags) ||
	     test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	     test_bit(DPC_GET_DHCP_IP_ADDR, &ha->dpc_flags) ||
	     test_bit(DPC_LINK_CHANGED, &ha->dpc_flags) ||
	     test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags) ||
	     test_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags) ||
	     test_bit(DPC_SYSFS_DDB_EXPORT, &ha->dpc_flags) ||
	     test_bit(DPC_AEN, &ha->dpc_flags)) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: scheduling dpc routine"
			      " - dpc flags = 0x%lx\n",
			      ha->host_no, __func__, ha->dpc_flags));
		qla4xxx_wake_dpc(ha);
	पूर्ण

	/* Reschedule समयr thपढ़ो to call us back in one second */
	mod_समयr(&ha->समयr, jअगरfies + HZ);

	DEBUG2(ha->seconds_since_last_पूर्णांकr++);
पूर्ण

/**
 * qla4xxx_cmd_रुको - रुकोs क्रम all outstanding commands to complete
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine stalls the driver until all outstanding commands are वापसed.
 * Caller must release the Hardware Lock prior to calling this routine.
 **/
अटल पूर्णांक qla4xxx_cmd_रुको(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t index = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *cmd;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक32_t wपंचांगo;

	अगर (is_qla40XX(ha))
		wपंचांगo = WAIT_CMD_TOV;
	अन्यथा
		wपंचांगo = ha->nx_reset_समयout / 2;

	wसमय = jअगरfies + (wपंचांगo * HZ);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Wait up to %u seconds for cmds to complete\n",
			  wपंचांगo));

	जबतक (!समय_after_eq(jअगरfies, wसमय)) अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		/* Find a command that hasn't completed. */
		क्रम (index = 0; index < ha->host->can_queue; index++) अणु
			cmd = scsi_host_find_tag(ha->host, index);
			/*
			 * We cannot just check अगर the index is valid,
			 * beहाल अगर we are run from the scsi eh, then
			 * the scsi/block layer is going to prevent
			 * the tag from being released.
			 */
			अगर (cmd != शून्य && CMD_SP(cmd))
				अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		/* If No Commands are pending, रुको is complete */
		अगर (index == ha->host->can_queue)
			वापस QLA_SUCCESS;

		msleep(1000);
	पूर्ण
	/* If we समयd out on रुकोing क्रम commands to come back
	 * वापस ERROR. */
	वापस QLA_ERROR;
पूर्ण

पूर्णांक qla4xxx_hw_reset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t ctrl_status;
	अचिन्हित दीर्घ flags = 0;

	DEBUG2(prपूर्णांकk(KERN_ERR "scsi%ld: %s\n", ha->host_no, __func__));

	अगर (ql4xxx_lock_drvr_रुको(ha) != QLA_SUCCESS)
		वापस QLA_ERROR;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/*
	 * If the SCSI Reset Interrupt bit is set, clear it.
	 * Otherwise, the Soft Reset won't work.
	 */
	ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
	अगर ((ctrl_status & CSR_SCSI_RESET_INTR) != 0)
		ग_लिखोl(set_rmask(CSR_SCSI_RESET_INTR), &ha->reg->ctrl_status);

	/* Issue Soft Reset */
	ग_लिखोl(set_rmask(CSR_SOFT_RESET), &ha->reg->ctrl_status);
	पढ़ोl(&ha->reg->ctrl_status);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_soft_reset - perक्रमms soft reset.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_soft_reset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t max_रुको_समय;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक status;
	uपूर्णांक32_t ctrl_status;

	status = qla4xxx_hw_reset(ha);
	अगर (status != QLA_SUCCESS)
		वापस status;

	status = QLA_ERROR;
	/* Wait until the Network Reset Intr bit is cleared */
	max_रुको_समय = RESET_INTR_TOV;
	करो अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		अगर ((ctrl_status & CSR_NET_RESET_INTR) == 0)
			अवरोध;

		msleep(1000);
	पूर्ण जबतक ((--max_रुको_समय));

	अगर ((ctrl_status & CSR_NET_RESET_INTR) != 0) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING
			      "scsi%ld: Network Reset Intr not cleared by "
			      "Network function, clearing it now!\n",
			      ha->host_no));
		spin_lock_irqsave(&ha->hardware_lock, flags);
		ग_लिखोl(set_rmask(CSR_NET_RESET_INTR), &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण

	/* Wait until the firmware tells us the Soft Reset is करोne */
	max_रुको_समय = SOFT_RESET_TOV;
	करो अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		अगर ((ctrl_status & CSR_SOFT_RESET) == 0) अणु
			status = QLA_SUCCESS;
			अवरोध;
		पूर्ण

		msleep(1000);
	पूर्ण जबतक ((--max_रुको_समय));

	/*
	 * Also, make sure that the SCSI Reset Interrupt bit has been cleared
	 * after the soft reset has taken place.
	 */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
	अगर ((ctrl_status & CSR_SCSI_RESET_INTR) != 0) अणु
		ग_लिखोl(set_rmask(CSR_SCSI_RESET_INTR), &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* If soft reset fails then most probably the bios on other
	 * function is also enabled.
	 * Since the initialization is sequential the other fn
	 * wont be able to acknowledge the soft reset.
	 * Issue a क्रमce soft reset to workaround this scenario.
	 */
	अगर (max_रुको_समय == 0) अणु
		/* Issue Force Soft Reset */
		spin_lock_irqsave(&ha->hardware_lock, flags);
		ग_लिखोl(set_rmask(CSR_FORCE_SOFT_RESET), &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		/* Wait until the firmware tells us the Soft Reset is करोne */
		max_रुको_समय = SOFT_RESET_TOV;
		करो अणु
			spin_lock_irqsave(&ha->hardware_lock, flags);
			ctrl_status = पढ़ोw(&ha->reg->ctrl_status);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);

			अगर ((ctrl_status & CSR_FORCE_SOFT_RESET) == 0) अणु
				status = QLA_SUCCESS;
				अवरोध;
			पूर्ण

			msleep(1000);
		पूर्ण जबतक ((--max_रुको_समय));
	पूर्ण

	वापस status;
पूर्ण

/**
 * qla4xxx_पात_active_cmds - वापसs all outstanding i/o requests to O.S.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @res: वापसed scsi status
 *
 * This routine is called just prior to a HARD RESET to वापस all
 * outstanding commands back to the Operating System.
 * Caller should make sure that the following locks are released
 * beक्रमe this calling routine: Hardware lock, and io_request_lock.
 **/
अटल व्योम qla4xxx_पात_active_cmds(काष्ठा scsi_qla_host *ha, पूर्णांक res)
अणु
	काष्ठा srb *srb;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (i = 0; i < ha->host->can_queue; i++) अणु
		srb = qla4xxx_del_from_active_array(ha, i);
		अगर (srb != शून्य) अणु
			srb->cmd->result = res;
			kref_put(&srb->srb_ref, qla4xxx_srb_compl);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

व्योम qla4xxx_dead_adapter_cleanup(काष्ठा scsi_qla_host *ha)
अणु
	clear_bit(AF_ONLINE, &ha->flags);

	/* Disable the board */
	ql4_prपूर्णांकk(KERN_INFO, ha, "Disabling the board\n");

	qla4xxx_पात_active_cmds(ha, DID_NO_CONNECT << 16);
	qla4xxx_mark_all_devices_missing(ha);
	clear_bit(AF_INIT_DONE, &ha->flags);
पूर्ण

अटल व्योम qla4xxx_fail_session(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ddb_entry->fw_ddb_device_state = DDB_DS_SESSION_FAILED;

	अगर (ddb_entry->ddb_type == FLASH_DDB)
		iscsi_block_session(ddb_entry->sess);
	अन्यथा
		iscsi_session_failure(cls_session->dd_data,
				      ISCSI_ERR_CONN_FAILED);
पूर्ण

/**
 * qla4xxx_recover_adapter - recovers adapter after a fatal error
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
अटल पूर्णांक qla4xxx_recover_adapter(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status = QLA_ERROR;
	uपूर्णांक8_t reset_chip = 0;
	uपूर्णांक32_t dev_state;
	अचिन्हित दीर्घ रुको;

	/* Stall incoming I/O until we are करोne */
	scsi_block_requests(ha->host);
	clear_bit(AF_ONLINE, &ha->flags);
	clear_bit(AF_LINK_UP, &ha->flags);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: adapter OFFLINE\n", __func__));

	set_bit(DPC_RESET_ACTIVE, &ha->dpc_flags);

	अगर ((is_qla8032(ha) || is_qla8042(ha)) &&
	    !test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: disabling pause transmit on port 0 & 1.\n",
			   __func__);
		/* disable छोड़ो frame क्रम ISP83xx */
		qla4_83xx_disable_छोड़ो(ha);
	पूर्ण

	iscsi_host_क्रम_each_session(ha->host, qla4xxx_fail_session);

	अगर (test_bit(DPC_RESET_HA, &ha->dpc_flags))
		reset_chip = 1;

	/* For the DPC_RESET_HA_INTR हाल (ISP-4xxx specअगरic)
	 * करो not reset adapter, jump to initialize_adapter */
	अगर (test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags)) अणु
		status = QLA_SUCCESS;
		जाओ recover_ha_init_adapter;
	पूर्ण

	/* For the ISP-8xxx adapter, issue a stop_firmware अगर invoked
	 * from eh_host_reset or ioctl module */
	अगर (is_qla80XX(ha) && !reset_chip &&
	    test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags)) अणु

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "scsi%ld: %s - Performing stop_firmware...\n",
		    ha->host_no, __func__));
		status = ha->isp_ops->reset_firmware(ha);
		अगर (status == QLA_SUCCESS) अणु
			ha->isp_ops->disable_पूर्णांकrs(ha);
			qla4xxx_process_aen(ha, FLUSH_DDB_CHANGED_AENS);
			qla4xxx_पात_active_cmds(ha, DID_RESET << 16);
		पूर्ण अन्यथा अणु
			/* If the stop_firmware fails then
			 * reset the entire chip */
			reset_chip = 1;
			clear_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags);
			set_bit(DPC_RESET_HA, &ha->dpc_flags);
		पूर्ण
	पूर्ण

	/* Issue full chip reset अगर recovering from a catastrophic error,
	 * or अगर stop_firmware fails क्रम ISP-8xxx.
	 * This is the शेष हाल क्रम ISP-4xxx */
	अगर (is_qla40XX(ha) || reset_chip) अणु
		अगर (is_qla40XX(ha))
			जाओ chip_reset;

		/* Check अगर 8XXX firmware is alive or not
		 * We may have arrived here from NEED_RESET
		 * detection only */
		अगर (test_bit(AF_FW_RECOVERY, &ha->flags))
			जाओ chip_reset;

		रुको = jअगरfies + (FW_ALIVE_WAIT_TOV * HZ);
		जबतक (समय_beक्रमe(jअगरfies, रुको)) अणु
			अगर (qla4_8xxx_check_fw_alive(ha)) अणु
				qla4xxx_mailbox_premature_completion(ha);
				अवरोध;
			पूर्ण

			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(HZ);
		पूर्ण
chip_reset:
		अगर (!test_bit(AF_FW_RECOVERY, &ha->flags))
			qla4xxx_cmd_रुको(ha);

		qla4xxx_process_aen(ha, FLUSH_DDB_CHANGED_AENS);
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "scsi%ld: %s - Performing chip reset..\n",
		    ha->host_no, __func__));
		status = ha->isp_ops->reset_chip(ha);
		qla4xxx_पात_active_cmds(ha, DID_RESET << 16);
	पूर्ण

	/* Flush any pending ddb changed AENs */
	qla4xxx_process_aen(ha, FLUSH_DDB_CHANGED_AENS);

recover_ha_init_adapter:
	/* Upon successful firmware/chip reset, re-initialize the adapter */
	अगर (status == QLA_SUCCESS) अणु
		/* For ISP-4xxx, क्रमce function 1 to always initialize
		 * beक्रमe function 3 to prevent both funcions from
		 * stepping on top of the other */
		अगर (is_qla40XX(ha) && (ha->mac_index == 3))
			ssleep(6);

		/* NOTE: AF_ONLINE flag set upon successful completion of
		 * qla4xxx_initialize_adapter */
		status = qla4xxx_initialize_adapter(ha, RESET_ADAPTER);
		अगर (is_qla80XX(ha) && (status == QLA_ERROR)) अणु
			status = qla4_8xxx_check_init_adapter_retry(ha);
			अगर (status == QLA_ERROR) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: Don't retry recover adapter\n",
					   ha->host_no, __func__);
				qla4xxx_dead_adapter_cleanup(ha);
				clear_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA_FW_CONTEXT,
					  &ha->dpc_flags);
				जाओ निकास_recover;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Retry failed adapter initialization, अगर necessary
	 * Do not retry initialize_adapter क्रम RESET_HA_INTR (ISP-4xxx specअगरic)
	 * हाल to prevent ping-pong resets between functions */
	अगर (!test_bit(AF_ONLINE, &ha->flags) &&
	    !test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags)) अणु
		/* Adapter initialization failed, see अगर we can retry
		 * resetting the ha.
		 * Since we करोn't want to block the DPC क्रम too दीर्घ
		 * with multiple resets in the same thपढ़ो,
		 * utilize DPC to retry */
		अगर (is_qla80XX(ha)) अणु
			ha->isp_ops->idc_lock(ha);
			dev_state = qla4_8xxx_rd_direct(ha,
							QLA8XXX_CRB_DEV_STATE);
			ha->isp_ops->idc_unlock(ha);
			अगर (dev_state == QLA8XXX_DEV_FAILED) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: don't retry "
					   "recover adapter. H/W is in Failed "
					   "state\n", __func__);
				qla4xxx_dead_adapter_cleanup(ha);
				clear_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA_FW_CONTEXT,
						&ha->dpc_flags);
				status = QLA_ERROR;

				जाओ निकास_recover;
			पूर्ण
		पूर्ण

		अगर (!test_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags)) अणु
			ha->retry_reset_ha_cnt = MAX_RESET_HA_RETRIES;
			DEBUG2(prपूर्णांकk("scsi%ld: recover adapter - retrying "
				      "(%d) more times\n", ha->host_no,
				      ha->retry_reset_ha_cnt));
			set_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags);
			status = QLA_ERROR;
		पूर्ण अन्यथा अणु
			अगर (ha->retry_reset_ha_cnt > 0) अणु
				/* Schedule another Reset HA--DPC will retry */
				ha->retry_reset_ha_cnt--;
				DEBUG2(prपूर्णांकk("scsi%ld: recover adapter - "
					      "retry remaining %d\n",
					      ha->host_no,
					      ha->retry_reset_ha_cnt));
				status = QLA_ERROR;
			पूर्ण

			अगर (ha->retry_reset_ha_cnt == 0) अणु
				/* Recover adapter retries have been exhausted.
				 * Adapter DEAD */
				DEBUG2(prपूर्णांकk("scsi%ld: recover adapter "
					      "failed - board disabled\n",
					      ha->host_no));
				qla4xxx_dead_adapter_cleanup(ha);
				clear_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA, &ha->dpc_flags);
				clear_bit(DPC_RESET_HA_FW_CONTEXT,
					  &ha->dpc_flags);
				status = QLA_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(DPC_RESET_HA, &ha->dpc_flags);
		clear_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags);
		clear_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags);
	पूर्ण

निकास_recover:
	ha->adapter_error_count++;

	अगर (test_bit(AF_ONLINE, &ha->flags))
		ha->isp_ops->enable_पूर्णांकrs(ha);

	scsi_unblock_requests(ha->host);

	clear_bit(DPC_RESET_ACTIVE, &ha->dpc_flags);
	DEBUG2(prपूर्णांकk("scsi%ld: recover adapter: %s\n", ha->host_no,
	    status == QLA_ERROR ? "FAILED" : "SUCCEEDED"));

	वापस status;
पूर्ण

अटल व्योम qla4xxx_relogin_devices(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	अगर (!iscsi_is_session_online(cls_session)) अणु
		अगर (ddb_entry->fw_ddb_device_state == DDB_DS_SESSION_ACTIVE) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ddb[%d]"
				   " unblock session\n", ha->host_no, __func__,
				   ddb_entry->fw_ddb_index);
			iscsi_unblock_session(ddb_entry->sess);
		पूर्ण अन्यथा अणु
			/* Trigger relogin */
			अगर (ddb_entry->ddb_type == FLASH_DDB) अणु
				अगर (!(test_bit(DF_RELOGIN, &ddb_entry->flags) ||
				      test_bit(DF_DISABLE_RELOGIN,
					       &ddb_entry->flags)))
					qla4xxx_arm_relogin_समयr(ddb_entry);
			पूर्ण अन्यथा
				iscsi_session_failure(cls_session->dd_data,
						      ISCSI_ERR_CONN_FAILED);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक qla4xxx_unblock_flash_ddb(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ddb[%d]"
		   " unblock session\n", ha->host_no, __func__,
		   ddb_entry->fw_ddb_index);

	iscsi_unblock_session(ddb_entry->sess);

	/* Start scan target */
	अगर (test_bit(AF_ONLINE, &ha->flags)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ddb[%d]"
			   " start scan\n", ha->host_no, __func__,
			   ddb_entry->fw_ddb_index);
		scsi_queue_work(ha->host, &ddb_entry->sess->scan_work);
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक qla4xxx_unblock_ddb(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक status = QLA_SUCCESS;

	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;
	ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ddb[%d]"
		   " unblock user space session\n", ha->host_no, __func__,
		   ddb_entry->fw_ddb_index);

	अगर (!iscsi_is_session_online(cls_session)) अणु
		iscsi_conn_start(ddb_entry->conn);
		iscsi_conn_login_event(ddb_entry->conn,
				       ISCSI_CONN_STATE_LOGGED_IN);
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "scsi%ld: %s: ddb[%d] session [%d] already logged in\n",
			   ha->host_no, __func__, ddb_entry->fw_ddb_index,
			   cls_session->sid);
		status = QLA_ERROR;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम qla4xxx_relogin_all_devices(काष्ठा scsi_qla_host *ha)
अणु
	iscsi_host_क्रम_each_session(ha->host, qla4xxx_relogin_devices);
पूर्ण

अटल व्योम qla4xxx_relogin_flash_ddb(काष्ठा iscsi_cls_session *cls_sess)
अणु
	uपूर्णांक16_t relogin_समयr;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	relogin_समयr = max(ddb_entry->शेष_relogin_समयout,
			    (uपूर्णांक16_t)RELOGIN_TOV);
	atomic_set(&ddb_entry->relogin_समयr, relogin_समयr);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "scsi%ld: Relogin index [%d]. TOV=%d\n", ha->host_no,
			  ddb_entry->fw_ddb_index, relogin_समयr));

	qla4xxx_login_flash_ddb(cls_sess);
पूर्ण

अटल व्योम qla4xxx_dpc_relogin(काष्ठा iscsi_cls_session *cls_sess)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा scsi_qla_host *ha;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	अगर (!(ddb_entry->ddb_type == FLASH_DDB))
		वापस;

	अगर (test_bit(DF_DISABLE_RELOGIN, &ddb_entry->flags))
		वापस;

	अगर (test_and_clear_bit(DF_RELOGIN, &ddb_entry->flags) &&
	    !iscsi_is_session_online(cls_sess)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "relogin issued\n"));
		qla4xxx_relogin_flash_ddb(cls_sess);
	पूर्ण
पूर्ण

व्योम qla4xxx_wake_dpc(काष्ठा scsi_qla_host *ha)
अणु
	अगर (ha->dpc_thपढ़ो)
		queue_work(ha->dpc_thपढ़ो, &ha->dpc_work);
पूर्ण

अटल काष्ठा qla4_work_evt *
qla4xxx_alloc_work(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t data_size,
		   क्रमागत qla4_work_type type)
अणु
	काष्ठा qla4_work_evt *e;
	uपूर्णांक32_t size = माप(काष्ठा qla4_work_evt) + data_size;

	e = kzalloc(size, GFP_ATOMIC);
	अगर (!e)
		वापस शून्य;

	INIT_LIST_HEAD(&e->list);
	e->type = type;
	वापस e;
पूर्ण

अटल व्योम qla4xxx_post_work(काष्ठा scsi_qla_host *ha,
			     काष्ठा qla4_work_evt *e)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->work_lock, flags);
	list_add_tail(&e->list, &ha->work_list);
	spin_unlock_irqrestore(&ha->work_lock, flags);
	qla4xxx_wake_dpc(ha);
पूर्ण

पूर्णांक qla4xxx_post_aen_work(काष्ठा scsi_qla_host *ha,
			  क्रमागत iscsi_host_event_code aen_code,
			  uपूर्णांक32_t data_size, uपूर्णांक8_t *data)
अणु
	काष्ठा qla4_work_evt *e;

	e = qla4xxx_alloc_work(ha, data_size, QLA4_EVENT_AEN);
	अगर (!e)
		वापस QLA_ERROR;

	e->u.aen.code = aen_code;
	e->u.aen.data_size = data_size;
	स_नकल(e->u.aen.data, data, data_size);

	qla4xxx_post_work(ha, e);

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक qla4xxx_post_ping_evt_work(काष्ठा scsi_qla_host *ha,
			       uपूर्णांक32_t status, uपूर्णांक32_t pid,
			       uपूर्णांक32_t data_size, uपूर्णांक8_t *data)
अणु
	काष्ठा qla4_work_evt *e;

	e = qla4xxx_alloc_work(ha, data_size, QLA4_EVENT_PING_STATUS);
	अगर (!e)
		वापस QLA_ERROR;

	e->u.ping.status = status;
	e->u.ping.pid = pid;
	e->u.ping.data_size = data_size;
	स_नकल(e->u.ping.data, data, data_size);

	qla4xxx_post_work(ha, e);

	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम qla4xxx_करो_work(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा qla4_work_evt *e, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(work);

	spin_lock_irqsave(&ha->work_lock, flags);
	list_splice_init(&ha->work_list, &work);
	spin_unlock_irqrestore(&ha->work_lock, flags);

	list_क्रम_each_entry_safe(e, पंचांगp, &work, list) अणु
		list_del_init(&e->list);

		चयन (e->type) अणु
		हाल QLA4_EVENT_AEN:
			iscsi_post_host_event(ha->host_no,
					      &qla4xxx_iscsi_transport,
					      e->u.aen.code,
					      e->u.aen.data_size,
					      e->u.aen.data);
			अवरोध;
		हाल QLA4_EVENT_PING_STATUS:
			iscsi_ping_comp_event(ha->host_no,
					      &qla4xxx_iscsi_transport,
					      e->u.ping.status,
					      e->u.ping.pid,
					      e->u.ping.data_size,
					      e->u.ping.data);
			अवरोध;
		शेष:
			ql4_prपूर्णांकk(KERN_WARNING, ha, "event type: 0x%x not "
				   "supported", e->type);
		पूर्ण
		kमुक्त(e);
	पूर्ण
पूर्ण

/**
 * qla4xxx_करो_dpc - dpc routine
 * @work: Context to obtain poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine is a task that is schedule by the पूर्णांकerrupt handler
 * to perक्रमm the background processing क्रम पूर्णांकerrupts.  We put it
 * on a task queue that is consumed whenever the scheduler runs; that's
 * so you can करो anything (i.e. put the process to sleep etc).  In fact,
 * the mid-level tries to sleep when it reaches the driver threshold
 * "host->can_queue". This can cause a panic अगर we were in our पूर्णांकerrupt code.
 **/
अटल व्योम qla4xxx_करो_dpc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_qla_host *ha =
		container_of(work, काष्ठा scsi_qla_host, dpc_work);
	पूर्णांक status = QLA_ERROR;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "scsi%ld: %s: DPC handler waking up. flags = 0x%08lx, dpc_flags = 0x%08lx\n",
			  ha->host_no, __func__, ha->flags, ha->dpc_flags));

	/* Initialization not yet finished. Don't करो anything yet. */
	अगर (!test_bit(AF_INIT_DONE, &ha->flags))
		वापस;

	अगर (test_bit(AF_EEH_BUSY, &ha->flags)) अणु
		DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: flags = %lx\n",
		    ha->host_no, __func__, ha->flags));
		वापस;
	पूर्ण

	/* post events to application */
	qla4xxx_करो_work(ha);

	अगर (is_qla80XX(ha)) अणु
		अगर (test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags)) अणु
			अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: disabling pause transmit on port 0 & 1.\n",
					   __func__);
				/* disable छोड़ो frame क्रम ISP83xx */
				qla4_83xx_disable_छोड़ो(ha);
			पूर्ण

			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
			ha->isp_ops->idc_unlock(ha);
			ql4_prपूर्णांकk(KERN_INFO, ha, "HW State: FAILED\n");
			qla4_8xxx_device_state_handler(ha);
		पूर्ण

		अगर (test_bit(DPC_POST_IDC_ACK, &ha->dpc_flags)) अणु
			अगर (is_qla8042(ha)) अणु
				अगर (ha->idc_info.info2 &
				    ENABLE_INTERNAL_LOOPBACK) अणु
					ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Disabling ACB\n",
						   __func__);
					status = qla4_84xx_config_acb(ha,
							    ACB_CONFIG_DISABLE);
					अगर (status != QLA_SUCCESS) अणु
						ql4_prपूर्णांकk(KERN_INFO, ha, "%s: ACB config failed\n",
							   __func__);
					पूर्ण
				पूर्ण
			पूर्ण
			qla4_83xx_post_idc_ack(ha);
			clear_bit(DPC_POST_IDC_ACK, &ha->dpc_flags);
		पूर्ण

		अगर (is_qla8042(ha) &&
		    test_bit(DPC_RESTORE_ACB, &ha->dpc_flags)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Restoring ACB\n",
				   __func__);
			अगर (qla4_84xx_config_acb(ha, ACB_CONFIG_SET) !=
			    QLA_SUCCESS) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "%s: ACB config failed ",
					   __func__);
			पूर्ण
			clear_bit(DPC_RESTORE_ACB, &ha->dpc_flags);
		पूर्ण

		अगर (test_and_clear_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags)) अणु
			qla4_8xxx_need_qsnt_handler(ha);
		पूर्ण
	पूर्ण

	अगर (!test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) &&
	    (test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags))) अणु
		अगर ((is_qla8022(ha) && ql4xकरोntresethba) ||
		    ((is_qla8032(ha) || is_qla8042(ha)) &&
		     qla4_83xx_idc_करोntreset(ha))) अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Don't Reset HBA\n",
			    ha->host_no, __func__));
			clear_bit(DPC_RESET_HA, &ha->dpc_flags);
			clear_bit(DPC_RESET_HA_INTR, &ha->dpc_flags);
			clear_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags);
			जाओ dpc_post_reset_ha;
		पूर्ण
		अगर (test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags) ||
		    test_bit(DPC_RESET_HA, &ha->dpc_flags))
			qla4xxx_recover_adapter(ha);

		अगर (test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags)) अणु
			uपूर्णांक8_t रुको_समय = RESET_INTR_TOV;

			जबतक ((पढ़ोw(&ha->reg->ctrl_status) &
				(CSR_SOFT_RESET | CSR_FORCE_SOFT_RESET)) != 0) अणु
				अगर (--रुको_समय == 0)
					अवरोध;
				msleep(1000);
			पूर्ण
			अगर (रुको_समय == 0)
				DEBUG2(prपूर्णांकk("scsi%ld: %s: SR|FSR "
					      "bit not cleared-- resetting\n",
					      ha->host_no, __func__));
			qla4xxx_पात_active_cmds(ha, DID_RESET << 16);
			अगर (ql4xxx_lock_drvr_रुको(ha) == QLA_SUCCESS) अणु
				qla4xxx_process_aen(ha, FLUSH_DDB_CHANGED_AENS);
				status = qla4xxx_recover_adapter(ha);
			पूर्ण
			clear_bit(DPC_RESET_HA_INTR, &ha->dpc_flags);
			अगर (status == QLA_SUCCESS)
				ha->isp_ops->enable_पूर्णांकrs(ha);
		पूर्ण
	पूर्ण

dpc_post_reset_ha:
	/* ---- process AEN? --- */
	अगर (test_and_clear_bit(DPC_AEN, &ha->dpc_flags))
		qla4xxx_process_aen(ha, PROCESS_ALL_AENS);

	/* ---- Get DHCP IP Address? --- */
	अगर (test_and_clear_bit(DPC_GET_DHCP_IP_ADDR, &ha->dpc_flags))
		qla4xxx_get_dhcp_ip_address(ha);

	/* ---- relogin device? --- */
	अगर (adapter_up(ha) &&
	    test_and_clear_bit(DPC_RELOGIN_DEVICE, &ha->dpc_flags)) अणु
		iscsi_host_क्रम_each_session(ha->host, qla4xxx_dpc_relogin);
	पूर्ण

	/* ---- link change? --- */
	अगर (!test_bit(AF_LOOPBACK, &ha->flags) &&
	    test_and_clear_bit(DPC_LINK_CHANGED, &ha->dpc_flags)) अणु
		अगर (!test_bit(AF_LINK_UP, &ha->flags)) अणु
			/* ---- link करोwn? --- */
			qla4xxx_mark_all_devices_missing(ha);
		पूर्ण अन्यथा अणु
			/* ---- link up? --- *
			 * F/W will स्वतः login to all devices ONLY ONCE after
			 * link up during driver initialization and runसमय
			 * fatal error recovery.  Thereक्रमe, the driver must
			 * manually relogin to devices when recovering from
			 * connection failures, logouts, expired KATO, etc. */
			अगर (test_and_clear_bit(AF_BUILD_DDB_LIST, &ha->flags)) अणु
				qla4xxx_build_ddb_list(ha, ha->is_reset);
				iscsi_host_क्रम_each_session(ha->host,
						qla4xxx_login_flash_ddb);
			पूर्ण अन्यथा
				qla4xxx_relogin_all_devices(ha);
		पूर्ण
	पूर्ण
	अगर (test_and_clear_bit(DPC_SYSFS_DDB_EXPORT, &ha->dpc_flags)) अणु
		अगर (qla4xxx_sysfs_ddb_export(ha))
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Error exporting ddb to sysfs\n",
				   __func__);
	पूर्ण
पूर्ण

/**
 * qla4xxx_मुक्त_adapter - release the adapter
 * @ha: poपूर्णांकer to adapter काष्ठाure
 **/
अटल व्योम qla4xxx_मुक्त_adapter(काष्ठा scsi_qla_host *ha)
अणु
	qla4xxx_पात_active_cmds(ha, DID_NO_CONNECT << 16);

	/* Turn-off पूर्णांकerrupts on the card. */
	ha->isp_ops->disable_पूर्णांकrs(ha);

	अगर (is_qla40XX(ha)) अणु
		ग_लिखोl(set_rmask(CSR_SCSI_PROCESSOR_INTR),
		       &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
	पूर्ण अन्यथा अगर (is_qla8022(ha)) अणु
		ग_लिखोl(0, &ha->qla4_82xx_reg->host_पूर्णांक);
		पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ग_लिखोl(0, &ha->qla4_83xx_reg->risc_पूर्णांकr);
		पढ़ोl(&ha->qla4_83xx_reg->risc_पूर्णांकr);
	पूर्ण

	/* Remove समयr thपढ़ो, अगर present */
	अगर (ha->समयr_active)
		qla4xxx_stop_समयr(ha);

	/* Kill the kernel thपढ़ो क्रम this host */
	अगर (ha->dpc_thपढ़ो)
		destroy_workqueue(ha->dpc_thपढ़ो);

	/* Kill the kernel thपढ़ो क्रम this host */
	अगर (ha->task_wq)
		destroy_workqueue(ha->task_wq);

	/* Put firmware in known state */
	ha->isp_ops->reset_firmware(ha);

	अगर (is_qla80XX(ha)) अणु
		ha->isp_ops->idc_lock(ha);
		qla4_8xxx_clear_drv_active(ha);
		ha->isp_ops->idc_unlock(ha);
	पूर्ण

	/* Detach पूर्णांकerrupts */
	qla4xxx_मुक्त_irqs(ha);

	/* मुक्त extra memory */
	qla4xxx_mem_मुक्त(ha);
पूर्ण

पूर्णांक qla4_8xxx_iospace_config(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक status = 0;
	अचिन्हित दीर्घ mem_base, mem_len;
	काष्ठा pci_dev *pdev = ha->pdev;

	status = pci_request_regions(pdev, DRIVER_NAME);
	अगर (status) अणु
		prपूर्णांकk(KERN_WARNING
		    "scsi(%ld) Failed to reserve PIO regions (%s) "
		    "status=%d\n", ha->host_no, pci_name(pdev), status);
		जाओ iospace_error_निकास;
	पूर्ण

	DEBUG2(prपूर्णांकk(KERN_INFO "%s: revision-id=%d\n",
	    __func__, pdev->revision));
	ha->revision_id = pdev->revision;

	/* remap phys address */
	mem_base = pci_resource_start(pdev, 0); /* 0 is क्रम BAR 0 */
	mem_len = pci_resource_len(pdev, 0);
	DEBUG2(prपूर्णांकk(KERN_INFO "%s: ioremap from %lx a size of %lx\n",
	    __func__, mem_base, mem_len));

	/* mapping of pcibase poपूर्णांकer */
	ha->nx_pcibase = (अचिन्हित दीर्घ)ioremap(mem_base, mem_len);
	अगर (!ha->nx_pcibase) अणु
		prपूर्णांकk(KERN_ERR
		    "cannot remap MMIO (%s), aborting\n", pci_name(pdev));
		pci_release_regions(ha->pdev);
		जाओ iospace_error_निकास;
	पूर्ण

	/* Mapping of IO base poपूर्णांकer, करोor bell पढ़ो and ग_लिखो poपूर्णांकer */

	/* mapping of IO base poपूर्णांकer */
	अगर (is_qla8022(ha)) अणु
		ha->qla4_82xx_reg = (काष्ठा device_reg_82xx  __iomem *)
				    ((uपूर्णांक8_t *)ha->nx_pcibase + 0xbc000 +
				     (ha->pdev->devfn << 11));
		ha->nx_db_wr_ptr = (ha->pdev->devfn == 4 ? QLA82XX_CAM_RAM_DB1 :
				    QLA82XX_CAM_RAM_DB2);
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ha->qla4_83xx_reg = (काष्ठा device_reg_83xx __iomem *)
				    ((uपूर्णांक8_t *)ha->nx_pcibase);
	पूर्ण

	वापस 0;
iospace_error_निकास:
	वापस -ENOMEM;
पूर्ण

/***
 * qla4xxx_iospace_config - maps रेजिस्टरs
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * This routines maps HBA's रेजिस्टरs from the pci address space
 * पूर्णांकo the kernel भव address space क्रम memory mapped i/o.
 **/
पूर्णांक qla4xxx_iospace_config(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ pio, pio_len, pio_flags;
	अचिन्हित दीर्घ mmio, mmio_len, mmio_flags;

	pio = pci_resource_start(ha->pdev, 0);
	pio_len = pci_resource_len(ha->pdev, 0);
	pio_flags = pci_resource_flags(ha->pdev, 0);
	अगर (pio_flags & IORESOURCE_IO) अणु
		अगर (pio_len < MIN_IOBASE_LEN) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
				"Invalid PCI I/O region size\n");
			pio = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "region #0 not a PIO resource\n");
		pio = 0;
	पूर्ण

	/* Use MMIO operations क्रम all accesses. */
	mmio = pci_resource_start(ha->pdev, 1);
	mmio_len = pci_resource_len(ha->pdev, 1);
	mmio_flags = pci_resource_flags(ha->pdev, 1);

	अगर (!(mmio_flags & IORESOURCE_MEM)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
		    "region #0 not an MMIO resource, aborting\n");

		जाओ iospace_error_निकास;
	पूर्ण

	अगर (mmio_len < MIN_IOBASE_LEN) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
		    "Invalid PCI mem region size, aborting\n");
		जाओ iospace_error_निकास;
	पूर्ण

	अगर (pci_request_regions(ha->pdev, DRIVER_NAME)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "Failed to reserve PIO/MMIO regions\n");

		जाओ iospace_error_निकास;
	पूर्ण

	ha->pio_address = pio;
	ha->pio_length = pio_len;
	ha->reg = ioremap(mmio, MIN_IOBASE_LEN);
	अगर (!ha->reg) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
		    "cannot remap MMIO, aborting\n");

		जाओ iospace_error_निकास;
	पूर्ण

	वापस 0;

iospace_error_निकास:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा isp_operations qla4xxx_isp_ops = अणु
	.iospace_config         = qla4xxx_iospace_config,
	.pci_config             = qla4xxx_pci_config,
	.disable_पूर्णांकrs          = qla4xxx_disable_पूर्णांकrs,
	.enable_पूर्णांकrs           = qla4xxx_enable_पूर्णांकrs,
	.start_firmware         = qla4xxx_start_firmware,
	.पूर्णांकr_handler           = qla4xxx_पूर्णांकr_handler,
	.पूर्णांकerrupt_service_routine = qla4xxx_पूर्णांकerrupt_service_routine,
	.reset_chip             = qla4xxx_soft_reset,
	.reset_firmware         = qla4xxx_hw_reset,
	.queue_iocb             = qla4xxx_queue_iocb,
	.complete_iocb          = qla4xxx_complete_iocb,
	.rd_shdw_req_q_out      = qla4xxx_rd_shdw_req_q_out,
	.rd_shdw_rsp_q_in       = qla4xxx_rd_shdw_rsp_q_in,
	.get_sys_info           = qla4xxx_get_sys_info,
	.queue_mailbox_command	= qla4xxx_queue_mbox_cmd,
	.process_mailbox_पूर्णांकerrupt = qla4xxx_process_mbox_पूर्णांकr,
पूर्ण;

अटल काष्ठा isp_operations qla4_82xx_isp_ops = अणु
	.iospace_config         = qla4_8xxx_iospace_config,
	.pci_config             = qla4_8xxx_pci_config,
	.disable_पूर्णांकrs          = qla4_82xx_disable_पूर्णांकrs,
	.enable_पूर्णांकrs           = qla4_82xx_enable_पूर्णांकrs,
	.start_firmware         = qla4_8xxx_load_risc,
	.restart_firmware	= qla4_82xx_try_start_fw,
	.पूर्णांकr_handler           = qla4_82xx_पूर्णांकr_handler,
	.पूर्णांकerrupt_service_routine = qla4_82xx_पूर्णांकerrupt_service_routine,
	.need_reset		= qla4_8xxx_need_reset,
	.reset_chip             = qla4_82xx_isp_reset,
	.reset_firmware         = qla4_8xxx_stop_firmware,
	.queue_iocb             = qla4_82xx_queue_iocb,
	.complete_iocb          = qla4_82xx_complete_iocb,
	.rd_shdw_req_q_out      = qla4_82xx_rd_shdw_req_q_out,
	.rd_shdw_rsp_q_in       = qla4_82xx_rd_shdw_rsp_q_in,
	.get_sys_info           = qla4_8xxx_get_sys_info,
	.rd_reg_direct		= qla4_82xx_rd_32,
	.wr_reg_direct		= qla4_82xx_wr_32,
	.rd_reg_indirect	= qla4_82xx_md_rd_32,
	.wr_reg_indirect	= qla4_82xx_md_wr_32,
	.idc_lock		= qla4_82xx_idc_lock,
	.idc_unlock		= qla4_82xx_idc_unlock,
	.rom_lock_recovery	= qla4_82xx_rom_lock_recovery,
	.queue_mailbox_command	= qla4_82xx_queue_mbox_cmd,
	.process_mailbox_पूर्णांकerrupt = qla4_82xx_process_mbox_पूर्णांकr,
पूर्ण;

अटल काष्ठा isp_operations qla4_83xx_isp_ops = अणु
	.iospace_config		= qla4_8xxx_iospace_config,
	.pci_config		= qla4_8xxx_pci_config,
	.disable_पूर्णांकrs		= qla4_83xx_disable_पूर्णांकrs,
	.enable_पूर्णांकrs		= qla4_83xx_enable_पूर्णांकrs,
	.start_firmware		= qla4_8xxx_load_risc,
	.restart_firmware	= qla4_83xx_start_firmware,
	.पूर्णांकr_handler		= qla4_83xx_पूर्णांकr_handler,
	.पूर्णांकerrupt_service_routine = qla4_83xx_पूर्णांकerrupt_service_routine,
	.need_reset		= qla4_8xxx_need_reset,
	.reset_chip		= qla4_83xx_isp_reset,
	.reset_firmware		= qla4_8xxx_stop_firmware,
	.queue_iocb		= qla4_83xx_queue_iocb,
	.complete_iocb		= qla4_83xx_complete_iocb,
	.rd_shdw_req_q_out	= qla4xxx_rd_shdw_req_q_out,
	.rd_shdw_rsp_q_in	= qla4xxx_rd_shdw_rsp_q_in,
	.get_sys_info		= qla4_8xxx_get_sys_info,
	.rd_reg_direct		= qla4_83xx_rd_reg,
	.wr_reg_direct		= qla4_83xx_wr_reg,
	.rd_reg_indirect	= qla4_83xx_rd_reg_indirect,
	.wr_reg_indirect	= qla4_83xx_wr_reg_indirect,
	.idc_lock		= qla4_83xx_drv_lock,
	.idc_unlock		= qla4_83xx_drv_unlock,
	.rom_lock_recovery	= qla4_83xx_rom_lock_recovery,
	.queue_mailbox_command	= qla4_83xx_queue_mbox_cmd,
	.process_mailbox_पूर्णांकerrupt = qla4_83xx_process_mbox_पूर्णांकr,
पूर्ण;

uपूर्णांक16_t qla4xxx_rd_shdw_req_q_out(काष्ठा scsi_qla_host *ha)
अणु
	वापस (uपूर्णांक16_t)le32_to_cpu(ha->shaकरोw_regs->req_q_out);
पूर्ण

uपूर्णांक16_t qla4_82xx_rd_shdw_req_q_out(काष्ठा scsi_qla_host *ha)
अणु
	वापस (uपूर्णांक16_t)le32_to_cpu(पढ़ोl(&ha->qla4_82xx_reg->req_q_out));
पूर्ण

uपूर्णांक16_t qla4xxx_rd_shdw_rsp_q_in(काष्ठा scsi_qla_host *ha)
अणु
	वापस (uपूर्णांक16_t)le32_to_cpu(ha->shaकरोw_regs->rsp_q_in);
पूर्ण

uपूर्णांक16_t qla4_82xx_rd_shdw_rsp_q_in(काष्ठा scsi_qla_host *ha)
अणु
	वापस (uपूर्णांक16_t)le32_to_cpu(पढ़ोl(&ha->qla4_82xx_reg->rsp_q_in));
पूर्ण

अटल sमाप_प्रकार qla4xxx_show_boot_eth_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = data;
	अक्षर *str = buf;
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_FLAGS:
		rc = प्र_लिखो(str, "%d\n", SYSFS_FLAG_FW_SEL_BOOT);
		अवरोध;
	हाल ISCSI_BOOT_ETH_INDEX:
		rc = प्र_लिखो(str, "0\n");
		अवरोध;
	हाल ISCSI_BOOT_ETH_MAC:
		rc = sysfs_क्रमmat_mac(str, ha->my_mac,
				      MAC_ADDR_LEN);
		अवरोध;
	शेष:
		rc = -ENOSYS;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल umode_t qla4xxx_eth_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_ETH_FLAGS:
	हाल ISCSI_BOOT_ETH_MAC:
	हाल ISCSI_BOOT_ETH_INDEX:
		rc = S_IRUGO;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार qla4xxx_show_boot_ini_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = data;
	अक्षर *str = buf;
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = प्र_लिखो(str, "%s\n", ha->name_string);
		अवरोध;
	शेष:
		rc = -ENOSYS;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल umode_t qla4xxx_ini_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = S_IRUGO;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार
qla4xxx_show_boot_tgt_info(काष्ठा ql4_boot_session_info *boot_sess, पूर्णांक type,
			   अक्षर *buf)
अणु
	काष्ठा ql4_conn_info *boot_conn = &boot_sess->conn_list[0];
	अक्षर *str = buf;
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_NAME:
		rc = प्र_लिखो(buf, "%s\n", (अक्षर *)&boot_sess->target_name);
		अवरोध;
	हाल ISCSI_BOOT_TGT_IP_ADDR:
		अगर (boot_sess->conn_list[0].dest_ipaddr.ip_type == 0x1)
			rc = प्र_लिखो(buf, "%pI4\n",
				     &boot_conn->dest_ipaddr.ip_address);
		अन्यथा
			rc = प्र_लिखो(str, "%pI6\n",
				     &boot_conn->dest_ipaddr.ip_address);
		अवरोध;
	हाल ISCSI_BOOT_TGT_PORT:
			rc = प्र_लिखो(str, "%d\n", boot_conn->dest_port);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
		rc = प्र_लिखो(str,  "%.*s\n",
			     boot_conn->chap.target_chap_name_length,
			     (अक्षर *)&boot_conn->chap.target_chap_name);
		अवरोध;
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
		rc = प्र_लिखो(str,  "%.*s\n",
			     boot_conn->chap.target_secret_length,
			     (अक्षर *)&boot_conn->chap.target_secret);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
		rc = प्र_लिखो(str,  "%.*s\n",
			     boot_conn->chap.पूर्णांकr_chap_name_length,
			     (अक्षर *)&boot_conn->chap.पूर्णांकr_chap_name);
		अवरोध;
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		rc = प्र_लिखो(str,  "%.*s\n",
			     boot_conn->chap.पूर्णांकr_secret_length,
			     (अक्षर *)&boot_conn->chap.पूर्णांकr_secret);
		अवरोध;
	हाल ISCSI_BOOT_TGT_FLAGS:
		rc = प्र_लिखो(str, "%d\n", SYSFS_FLAG_FW_SEL_BOOT);
		अवरोध;
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
		rc = प्र_लिखो(str, "0\n");
		अवरोध;
	शेष:
		rc = -ENOSYS;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार qla4xxx_show_boot_tgt_pri_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = data;
	काष्ठा ql4_boot_session_info *boot_sess = &(ha->boot_tgt.boot_pri_sess);

	वापस qla4xxx_show_boot_tgt_info(boot_sess, type, buf);
पूर्ण

अटल sमाप_प्रकार qla4xxx_show_boot_tgt_sec_info(व्योम *data, पूर्णांक type, अक्षर *buf)
अणु
	काष्ठा scsi_qla_host *ha = data;
	काष्ठा ql4_boot_session_info *boot_sess = &(ha->boot_tgt.boot_sec_sess);

	वापस qla4xxx_show_boot_tgt_info(boot_sess, type, buf);
पूर्ण

अटल umode_t qla4xxx_tgt_get_attr_visibility(व्योम *data, पूर्णांक type)
अणु
	पूर्णांक rc;

	चयन (type) अणु
	हाल ISCSI_BOOT_TGT_NAME:
	हाल ISCSI_BOOT_TGT_IP_ADDR:
	हाल ISCSI_BOOT_TGT_PORT:
	हाल ISCSI_BOOT_TGT_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_CHAP_SECRET:
	हाल ISCSI_BOOT_TGT_REV_CHAP_NAME:
	हाल ISCSI_BOOT_TGT_REV_CHAP_SECRET:
	हाल ISCSI_BOOT_TGT_NIC_ASSOC:
	हाल ISCSI_BOOT_TGT_FLAGS:
		rc = S_IRUGO;
		अवरोध;
	शेष:
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम qla4xxx_boot_release(व्योम *data)
अणु
	काष्ठा scsi_qla_host *ha = data;

	scsi_host_put(ha->host);
पूर्ण

अटल पूर्णांक get_fw_boot_info(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t ddb_index[])
अणु
	dma_addr_t buf_dma;
	uपूर्णांक32_t addr, pri_addr, sec_addr;
	uपूर्णांक32_t offset;
	uपूर्णांक16_t func_num;
	uपूर्णांक8_t val;
	uपूर्णांक8_t *buf = शून्य;
	माप_प्रकार size = 13 * माप(uपूर्णांक8_t);
	पूर्णांक ret = QLA_SUCCESS;

	func_num = PCI_FUNC(ha->pdev->devfn);

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Get FW boot info for 0x%x func %d\n",
		   __func__, ha->pdev->device, func_num);

	अगर (is_qla40XX(ha)) अणु
		अगर (func_num == 1) अणु
			addr = NVRAM_PORT0_BOOT_MODE;
			pri_addr = NVRAM_PORT0_BOOT_PRI_TGT;
			sec_addr = NVRAM_PORT0_BOOT_SEC_TGT;
		पूर्ण अन्यथा अगर (func_num == 3) अणु
			addr = NVRAM_PORT1_BOOT_MODE;
			pri_addr = NVRAM_PORT1_BOOT_PRI_TGT;
			sec_addr = NVRAM_PORT1_BOOT_SEC_TGT;
		पूर्ण अन्यथा अणु
			ret = QLA_ERROR;
			जाओ निकास_boot_info;
		पूर्ण

		/* Check Boot Mode */
		val = rd_nvram_byte(ha, addr);
		अगर (!(val & 0x07)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Adapter boot "
					  "options : 0x%x\n", __func__, val));
			ret = QLA_ERROR;
			जाओ निकास_boot_info;
		पूर्ण

		/* get primary valid target index */
		val = rd_nvram_byte(ha, pri_addr);
		अगर (val & BIT_7)
			ddb_index[0] = (val & 0x7f);

		/* get secondary valid target index */
		val = rd_nvram_byte(ha, sec_addr);
		अगर (val & BIT_7)
			ddb_index[1] = (val & 0x7f);
		जाओ निकास_boot_info;
	पूर्ण अन्यथा अगर (is_qla80XX(ha)) अणु
		buf = dma_alloc_coherent(&ha->pdev->dev, size,
					 &buf_dma, GFP_KERNEL);
		अगर (!buf) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
					  "%s: Unable to allocate dma buffer\n",
					   __func__));
			ret = QLA_ERROR;
			जाओ निकास_boot_info;
		पूर्ण

		अगर (ha->port_num == 0)
			offset = BOOT_PARAM_OFFSET_PORT0;
		अन्यथा अगर (ha->port_num == 1)
			offset = BOOT_PARAM_OFFSET_PORT1;
		अन्यथा अणु
			ret = QLA_ERROR;
			जाओ निकास_boot_info_मुक्त;
		पूर्ण
		addr = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_iscsi_param * 4) +
		       offset;
		अगर (qla4xxx_get_flash(ha, buf_dma, addr,
				      13 * माप(uपूर्णांक8_t)) != QLA_SUCCESS) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: Get Flash"
					  " failed\n", ha->host_no, __func__));
			ret = QLA_ERROR;
			जाओ निकास_boot_info_मुक्त;
		पूर्ण
		/* Check Boot Mode */
		अगर (!(buf[1] & 0x07)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Firmware boot options"
					  " : 0x%x\n", buf[1]));
			ret = QLA_ERROR;
			जाओ निकास_boot_info_मुक्त;
		पूर्ण

		/* get primary valid target index */
		अगर (buf[2] & BIT_7)
			ddb_index[0] = buf[2] & 0x7f;

		/* get secondary valid target index */
		अगर (buf[11] & BIT_7)
			ddb_index[1] = buf[11] & 0x7f;
	पूर्ण अन्यथा अणु
		ret = QLA_ERROR;
		जाओ निकास_boot_info;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Primary target ID %d, Secondary"
			  " target ID %d\n", __func__, ddb_index[0],
			  ddb_index[1]));

निकास_boot_info_मुक्त:
	dma_मुक्त_coherent(&ha->pdev->dev, size, buf, buf_dma);
निकास_boot_info:
	ha->pri_ddb_idx = ddb_index[0];
	ha->sec_ddb_idx = ddb_index[1];
	वापस ret;
पूर्ण

/**
 * qla4xxx_get_bidi_chap - Get a BIDI CHAP user and password
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @username: CHAP username to be वापसed
 * @password: CHAP password to be वापसed
 *
 * If a boot entry has BIDI CHAP enabled then we need to set the BIDI CHAP
 * user and password in the sysfs entry in /sys/firmware/iscsi_boot#/.
 * So from the CHAP cache find the first BIDI CHAP entry and set it
 * to the boot record in sysfs.
 **/
अटल पूर्णांक qla4xxx_get_bidi_chap(काष्ठा scsi_qla_host *ha, अक्षर *username,
			    अक्षर *password)
अणु
	पूर्णांक i, ret = -EINVAL;
	पूर्णांक max_chap_entries = 0;
	काष्ठा ql4_chap_table *chap_table;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
						माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (!ha->chap_list) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Do not have CHAP table cache\n");
		वापस ret;
	पूर्ण

	mutex_lock(&ha->chap_sem);
	क्रम (i = 0; i < max_chap_entries; i++) अणु
		chap_table = (काष्ठा ql4_chap_table *)ha->chap_list + i;
		अगर (chap_table->cookie !=
		    __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE)) अणु
			जारी;
		पूर्ण

		अगर (chap_table->flags & BIT_7) /* local */
			जारी;

		अगर (!(chap_table->flags & BIT_6)) /* Not BIDI */
			जारी;

		strlcpy(password, chap_table->secret, QL4_CHAP_MAX_SECRET_LEN);
		strlcpy(username, chap_table->name, QL4_CHAP_MAX_NAME_LEN);
		ret = 0;
		अवरोध;
	पूर्ण
	mutex_unlock(&ha->chap_sem);

	वापस ret;
पूर्ण


अटल पूर्णांक qla4xxx_get_boot_target(काष्ठा scsi_qla_host *ha,
				   काष्ठा ql4_boot_session_info *boot_sess,
				   uपूर्णांक16_t ddb_index)
अणु
	काष्ठा ql4_conn_info *boot_conn = &boot_sess->conn_list[0];
	काष्ठा dev_db_entry *fw_ddb_entry;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक16_t idx;
	uपूर्णांक16_t options;
	पूर्णांक ret = QLA_SUCCESS;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer.\n",
				  __func__));
		ret = QLA_ERROR;
		वापस ret;
	पूर्ण

	अगर (qla4xxx_bootdb_by_index(ha, fw_ddb_entry,
				   fw_ddb_entry_dma, ddb_index)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: No Flash DDB found at "
				  "index [%d]\n", __func__, ddb_index));
		ret = QLA_ERROR;
		जाओ निकास_boot_target;
	पूर्ण

	/* Update target name and IP from DDB */
	स_नकल(boot_sess->target_name, fw_ddb_entry->iscsi_name,
	       min(माप(boot_sess->target_name),
		   माप(fw_ddb_entry->iscsi_name)));

	options = le16_to_cpu(fw_ddb_entry->options);
	अगर (options & DDB_OPT_IPV6_DEVICE) अणु
		स_नकल(&boot_conn->dest_ipaddr.ip_address,
		       &fw_ddb_entry->ip_addr[0], IPv6_ADDR_LEN);
	पूर्ण अन्यथा अणु
		boot_conn->dest_ipaddr.ip_type = 0x1;
		स_नकल(&boot_conn->dest_ipaddr.ip_address,
		       &fw_ddb_entry->ip_addr[0], IP_ADDR_LEN);
	पूर्ण

	boot_conn->dest_port = le16_to_cpu(fw_ddb_entry->port);

	/* update chap inक्रमmation */
	idx = __le16_to_cpu(fw_ddb_entry->chap_tbl_idx);

	अगर (BIT_7 & le16_to_cpu(fw_ddb_entry->iscsi_options))	अणु

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Setting chap\n"));

		ret = qla4xxx_get_chap(ha, (अक्षर *)&boot_conn->chap.
				       target_chap_name,
				       (अक्षर *)&boot_conn->chap.target_secret,
				       idx);
		अगर (ret) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "Failed to set chap\n");
			ret = QLA_ERROR;
			जाओ निकास_boot_target;
		पूर्ण

		boot_conn->chap.target_chap_name_length = QL4_CHAP_MAX_NAME_LEN;
		boot_conn->chap.target_secret_length = QL4_CHAP_MAX_SECRET_LEN;
	पूर्ण

	अगर (BIT_4 & le16_to_cpu(fw_ddb_entry->iscsi_options)) अणु

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Setting BIDI chap\n"));

		ret = qla4xxx_get_bidi_chap(ha,
				    (अक्षर *)&boot_conn->chap.पूर्णांकr_chap_name,
				    (अक्षर *)&boot_conn->chap.पूर्णांकr_secret);

		अगर (ret) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "Failed to set BIDI chap\n");
			ret = QLA_ERROR;
			जाओ निकास_boot_target;
		पूर्ण

		boot_conn->chap.पूर्णांकr_chap_name_length = QL4_CHAP_MAX_NAME_LEN;
		boot_conn->chap.पूर्णांकr_secret_length = QL4_CHAP_MAX_SECRET_LEN;
	पूर्ण

निकास_boot_target:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
			  fw_ddb_entry, fw_ddb_entry_dma);
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_get_boot_info(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक16_t ddb_index[2];
	पूर्णांक ret = QLA_ERROR;
	पूर्णांक rval;

	स_रखो(ddb_index, 0, माप(ddb_index));
	ddb_index[0] = 0xffff;
	ddb_index[1] = 0xffff;
	ret = get_fw_boot_info(ha, ddb_index);
	अगर (ret != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				"%s: No boot target configured.\n", __func__));
		वापस ret;
	पूर्ण

	अगर (ql4xdisablesysfsboot)
		वापस QLA_SUCCESS;

	अगर (ddb_index[0] == 0xffff)
		जाओ sec_target;

	rval = qla4xxx_get_boot_target(ha, &(ha->boot_tgt.boot_pri_sess),
				      ddb_index[0]);
	अगर (rval != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Primary boot target not "
				  "configured\n", __func__));
	पूर्ण अन्यथा
		ret = QLA_SUCCESS;

sec_target:
	अगर (ddb_index[1] == 0xffff)
		जाओ निकास_get_boot_info;

	rval = qla4xxx_get_boot_target(ha, &(ha->boot_tgt.boot_sec_sess),
				      ddb_index[1]);
	अगर (rval != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Secondary boot target not"
				  " configured\n", __func__));
	पूर्ण अन्यथा
		ret = QLA_SUCCESS;

निकास_get_boot_info:
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_setup_boot_info(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा iscsi_boot_kobj *boot_kobj;

	अगर (qla4xxx_get_boot_info(ha) != QLA_SUCCESS)
		वापस QLA_ERROR;

	अगर (ql4xdisablesysfsboot) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: syfsboot disabled - driver will trigger login "
			   "and publish session for discovery .\n", __func__);
		वापस QLA_SUCCESS;
	पूर्ण


	ha->boot_kset = iscsi_boot_create_host_kset(ha->host->host_no);
	अगर (!ha->boot_kset)
		जाओ kset_मुक्त;

	अगर (!scsi_host_get(ha->host))
		जाओ kset_मुक्त;
	boot_kobj = iscsi_boot_create_target(ha->boot_kset, 0, ha,
					     qla4xxx_show_boot_tgt_pri_info,
					     qla4xxx_tgt_get_attr_visibility,
					     qla4xxx_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(ha->host))
		जाओ kset_मुक्त;
	boot_kobj = iscsi_boot_create_target(ha->boot_kset, 1, ha,
					     qla4xxx_show_boot_tgt_sec_info,
					     qla4xxx_tgt_get_attr_visibility,
					     qla4xxx_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(ha->host))
		जाओ kset_मुक्त;
	boot_kobj = iscsi_boot_create_initiator(ha->boot_kset, 0, ha,
					       qla4xxx_show_boot_ini_info,
					       qla4xxx_ini_get_attr_visibility,
					       qla4xxx_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	अगर (!scsi_host_get(ha->host))
		जाओ kset_मुक्त;
	boot_kobj = iscsi_boot_create_ethernet(ha->boot_kset, 0, ha,
					       qla4xxx_show_boot_eth_info,
					       qla4xxx_eth_get_attr_visibility,
					       qla4xxx_boot_release);
	अगर (!boot_kobj)
		जाओ put_host;

	वापस QLA_SUCCESS;

put_host:
	scsi_host_put(ha->host);
kset_मुक्त:
	iscsi_boot_destroy_kset(ha->boot_kset);
	वापस -ENOMEM;
पूर्ण


अटल व्योम qla4xxx_get_param_ddb(काष्ठा ddb_entry *ddb_entry,
				  काष्ठा ql4_tuple_ddb *tddb)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_conn *conn;

	DEBUG2(prपूर्णांकk(KERN_INFO "Func: %s\n", __func__));
	cls_sess = ddb_entry->sess;
	sess = cls_sess->dd_data;
	cls_conn = ddb_entry->conn;
	conn = cls_conn->dd_data;

	tddb->tpgt = sess->tpgt;
	tddb->port = conn->persistent_port;
	strlcpy(tddb->iscsi_name, sess->targetname, ISCSI_NAME_SIZE);
	strlcpy(tddb->ip_addr, conn->persistent_address, DDB_IPADDR_LEN);
पूर्ण

अटल व्योम qla4xxx_convert_param_ddb(काष्ठा dev_db_entry *fw_ddb_entry,
				      काष्ठा ql4_tuple_ddb *tddb,
				      uपूर्णांक8_t *flash_isid)
अणु
	uपूर्णांक16_t options = 0;

	tddb->tpgt = le32_to_cpu(fw_ddb_entry->tgt_portal_grp);
	स_नकल(&tddb->iscsi_name[0], &fw_ddb_entry->iscsi_name[0],
	       min(माप(tddb->iscsi_name), माप(fw_ddb_entry->iscsi_name)));

	options = le16_to_cpu(fw_ddb_entry->options);
	अगर (options & DDB_OPT_IPV6_DEVICE)
		प्र_लिखो(tddb->ip_addr, "%pI6", fw_ddb_entry->ip_addr);
	अन्यथा
		प्र_लिखो(tddb->ip_addr, "%pI4", fw_ddb_entry->ip_addr);

	tddb->port = le16_to_cpu(fw_ddb_entry->port);

	अगर (flash_isid == शून्य)
		स_नकल(&tddb->isid[0], &fw_ddb_entry->isid[0],
		       माप(tddb->isid));
	अन्यथा
		स_नकल(&tddb->isid[0], &flash_isid[0], माप(tddb->isid));
पूर्ण

अटल पूर्णांक qla4xxx_compare_tuple_ddb(काष्ठा scsi_qla_host *ha,
				     काष्ठा ql4_tuple_ddb *old_tddb,
				     काष्ठा ql4_tuple_ddb *new_tddb,
				     uपूर्णांक8_t is_isid_compare)
अणु
	अगर (म_भेद(old_tddb->iscsi_name, new_tddb->iscsi_name))
		वापस QLA_ERROR;

	अगर (म_भेद(old_tddb->ip_addr, new_tddb->ip_addr))
		वापस QLA_ERROR;

	अगर (old_tddb->port != new_tddb->port)
		वापस QLA_ERROR;

	/* For multi sessions, driver generates the ISID, so करो not compare
	 * ISID in reset path since it would be a comparison between the
	 * driver generated ISID and firmware generated ISID. This could
	 * lead to adding duplicated DDBs in the list as driver generated
	 * ISID would not match firmware generated ISID.
	 */
	अगर (is_isid_compare) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			"%s: old ISID [%pmR] New ISID [%pmR]\n",
			__func__, old_tddb->isid, new_tddb->isid));

		अगर (स_भेद(&old_tddb->isid[0], &new_tddb->isid[0],
			   माप(old_tddb->isid)))
			वापस QLA_ERROR;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Match Found, fw[%d,%d,%s,%s], [%d,%d,%s,%s]",
			  old_tddb->port, old_tddb->tpgt, old_tddb->ip_addr,
			  old_tddb->iscsi_name, new_tddb->port, new_tddb->tpgt,
			  new_tddb->ip_addr, new_tddb->iscsi_name));

	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक qla4xxx_is_session_exists(काष्ठा scsi_qla_host *ha,
				     काष्ठा dev_db_entry *fw_ddb_entry,
				     uपूर्णांक32_t *index)
अणु
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा ql4_tuple_ddb *fw_tddb = शून्य;
	काष्ठा ql4_tuple_ddb *पंचांगp_tddb = शून्य;
	पूर्णांक idx;
	पूर्णांक ret = QLA_ERROR;

	fw_tddb = vzalloc(माप(*fw_tddb));
	अगर (!fw_tddb) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		जाओ निकास_check;
	पूर्ण

	पंचांगp_tddb = vzalloc(माप(*पंचांगp_tddb));
	अगर (!पंचांगp_tddb) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		जाओ निकास_check;
	पूर्ण

	qla4xxx_convert_param_ddb(fw_ddb_entry, fw_tddb, शून्य);

	क्रम (idx = 0; idx < MAX_DDB_ENTRIES; idx++) अणु
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		अगर (ddb_entry == शून्य)
			जारी;

		qla4xxx_get_param_ddb(ddb_entry, पंचांगp_tddb);
		अगर (!qla4xxx_compare_tuple_ddb(ha, fw_tddb, पंचांगp_tddb, false)) अणु
			ret = QLA_SUCCESS; /* found */
			अगर (index != शून्य)
				*index = idx;
			जाओ निकास_check;
		पूर्ण
	पूर्ण

निकास_check:
	vमुक्त(fw_tddb);
	vमुक्त(पंचांगp_tddb);
	वापस ret;
पूर्ण

/**
 * qla4xxx_check_existing_isid - check अगर target with same isid exist
 *				 in target list
 * @list_nt: list of target
 * @isid: isid to check
 *
 * This routine वापस QLA_SUCCESS अगर target with same isid exist
 **/
अटल पूर्णांक qla4xxx_check_existing_isid(काष्ठा list_head *list_nt, uपूर्णांक8_t *isid)
अणु
	काष्ठा qla_ddb_index *nt_ddb_idx, *nt_ddb_idx_पंचांगp;
	काष्ठा dev_db_entry *fw_ddb_entry;

	list_क्रम_each_entry_safe(nt_ddb_idx, nt_ddb_idx_पंचांगp, list_nt, list) अणु
		fw_ddb_entry = &nt_ddb_idx->fw_ddb;

		अगर (स_भेद(&fw_ddb_entry->isid[0], &isid[0],
			   माप(nt_ddb_idx->fw_ddb.isid)) == 0) अणु
			वापस QLA_SUCCESS;
		पूर्ण
	पूर्ण
	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_update_isid - compare ddbs and updated isid
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @list_nt: list of nt target
 * @fw_ddb_entry: firmware ddb entry
 *
 * This routine update isid अगर ddbs have same iqn, same isid and
 * dअगरferent IP addr.
 * Return QLA_SUCCESS अगर isid is updated.
 **/
अटल पूर्णांक qla4xxx_update_isid(काष्ठा scsi_qla_host *ha,
			       काष्ठा list_head *list_nt,
			       काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	uपूर्णांक8_t base_value, i;

	base_value = fw_ddb_entry->isid[1] & 0x1f;
	क्रम (i = 0; i < 8; i++) अणु
		fw_ddb_entry->isid[1] = (base_value | (i << 5));
		अगर (qla4xxx_check_existing_isid(list_nt, fw_ddb_entry->isid))
			अवरोध;
	पूर्ण

	अगर (!qla4xxx_check_existing_isid(list_nt, fw_ddb_entry->isid))
		वापस QLA_ERROR;

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_should_update_isid - check अगर isid need to update
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @old_tddb: ddb tuple
 * @new_tddb: ddb tuple
 *
 * Return QLA_SUCCESS अगर dअगरferent IP, dअगरferent PORT, same iqn,
 * same isid
 **/
अटल पूर्णांक qla4xxx_should_update_isid(काष्ठा scsi_qla_host *ha,
				      काष्ठा ql4_tuple_ddb *old_tddb,
				      काष्ठा ql4_tuple_ddb *new_tddb)
अणु
	अगर (म_भेद(old_tddb->ip_addr, new_tddb->ip_addr) == 0) अणु
		/* Same ip */
		अगर (old_tddb->port == new_tddb->port)
			वापस QLA_ERROR;
	पूर्ण

	अगर (म_भेद(old_tddb->iscsi_name, new_tddb->iscsi_name))
		/* dअगरferent iqn */
		वापस QLA_ERROR;

	अगर (स_भेद(&old_tddb->isid[0], &new_tddb->isid[0],
		   माप(old_tddb->isid)))
		/* dअगरferent isid */
		वापस QLA_ERROR;

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_is_flash_ddb_exists - check अगर fw_ddb_entry alपढ़ोy exists in list_nt
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @list_nt: list of nt target.
 * @fw_ddb_entry: firmware ddb entry.
 *
 * This routine check अगर fw_ddb_entry alपढ़ोy exists in list_nt to aव्योम
 * duplicate ddb in list_nt.
 * Return QLA_SUCCESS अगर duplicate ddb निकास in list_nl.
 * Note: This function also update isid of DDB अगर required.
 **/

अटल पूर्णांक qla4xxx_is_flash_ddb_exists(काष्ठा scsi_qla_host *ha,
				       काष्ठा list_head *list_nt,
				       काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	काष्ठा qla_ddb_index  *nt_ddb_idx, *nt_ddb_idx_पंचांगp;
	काष्ठा ql4_tuple_ddb *fw_tddb = शून्य;
	काष्ठा ql4_tuple_ddb *पंचांगp_tddb = शून्य;
	पूर्णांक rval, ret = QLA_ERROR;

	fw_tddb = vzalloc(माप(*fw_tddb));
	अगर (!fw_tddb) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		जाओ निकास_check;
	पूर्ण

	पंचांगp_tddb = vzalloc(माप(*पंचांगp_tddb));
	अगर (!पंचांगp_tddb) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "Memory Allocation failed.\n"));
		ret = QLA_SUCCESS;
		जाओ निकास_check;
	पूर्ण

	qla4xxx_convert_param_ddb(fw_ddb_entry, fw_tddb, शून्य);

	list_क्रम_each_entry_safe(nt_ddb_idx, nt_ddb_idx_पंचांगp, list_nt, list) अणु
		qla4xxx_convert_param_ddb(&nt_ddb_idx->fw_ddb, पंचांगp_tddb,
					  nt_ddb_idx->flash_isid);
		ret = qla4xxx_compare_tuple_ddb(ha, fw_tddb, पंचांगp_tddb, true);
		/* found duplicate ddb */
		अगर (ret == QLA_SUCCESS)
			जाओ निकास_check;
	पूर्ण

	list_क्रम_each_entry_safe(nt_ddb_idx, nt_ddb_idx_पंचांगp, list_nt, list) अणु
		qla4xxx_convert_param_ddb(&nt_ddb_idx->fw_ddb, पंचांगp_tddb, शून्य);

		ret = qla4xxx_should_update_isid(ha, पंचांगp_tddb, fw_tddb);
		अगर (ret == QLA_SUCCESS) अणु
			rval = qla4xxx_update_isid(ha, list_nt, fw_ddb_entry);
			अगर (rval == QLA_SUCCESS)
				ret = QLA_ERROR;
			अन्यथा
				ret = QLA_SUCCESS;

			जाओ निकास_check;
		पूर्ण
	पूर्ण

निकास_check:
	vमुक्त(fw_tddb);
	vमुक्त(पंचांगp_tddb);
	वापस ret;
पूर्ण

अटल व्योम qla4xxx_मुक्त_ddb_list(काष्ठा list_head *list_ddb)
अणु
	काष्ठा qla_ddb_index  *ddb_idx, *ddb_idx_पंचांगp;

	list_क्रम_each_entry_safe(ddb_idx, ddb_idx_पंचांगp, list_ddb, list) अणु
		list_del_init(&ddb_idx->list);
		vमुक्त(ddb_idx);
	पूर्ण
पूर्ण

अटल काष्ठा iscsi_endpoपूर्णांक *qla4xxx_get_ep_fwdb(काष्ठा scsi_qla_host *ha,
					काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा sockaddr *t_addr;
	काष्ठा sockaddr_storage *dst_addr;
	अक्षर *ip;

	/* TODO: need to destroy on unload iscsi_endpoपूर्णांक*/
	dst_addr = vदो_स्मृति(माप(*dst_addr));
	अगर (!dst_addr)
		वापस शून्य;

	अगर (fw_ddb_entry->options & DDB_OPT_IPV6_DEVICE) अणु
		t_addr = (काष्ठा sockaddr *)dst_addr;
		t_addr->sa_family = AF_INET6;
		addr6 = (काष्ठा sockaddr_in6 *)dst_addr;
		ip = (अक्षर *)&addr6->sin6_addr;
		स_नकल(ip, fw_ddb_entry->ip_addr, IPv6_ADDR_LEN);
		addr6->sin6_port = htons(le16_to_cpu(fw_ddb_entry->port));

	पूर्ण अन्यथा अणु
		t_addr = (काष्ठा sockaddr *)dst_addr;
		t_addr->sa_family = AF_INET;
		addr = (काष्ठा sockaddr_in *)dst_addr;
		ip = (अक्षर *)&addr->sin_addr;
		स_नकल(ip, fw_ddb_entry->ip_addr, IP_ADDR_LEN);
		addr->sin_port = htons(le16_to_cpu(fw_ddb_entry->port));
	पूर्ण

	ep = qla4xxx_ep_connect(ha->host, (काष्ठा sockaddr *)dst_addr, 0);
	vमुक्त(dst_addr);
	वापस ep;
पूर्ण

अटल पूर्णांक qla4xxx_verअगरy_boot_idx(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t idx)
अणु
	अगर (ql4xdisablesysfsboot)
		वापस QLA_SUCCESS;
	अगर (idx == ha->pri_ddb_idx || idx == ha->sec_ddb_idx)
		वापस QLA_ERROR;
	वापस QLA_SUCCESS;
पूर्ण

अटल व्योम qla4xxx_setup_flash_ddb_entry(काष्ठा scsi_qla_host *ha,
					  काष्ठा ddb_entry *ddb_entry,
					  uपूर्णांक16_t idx)
अणु
	uपूर्णांक16_t def_समयout;

	ddb_entry->ddb_type = FLASH_DDB;
	ddb_entry->fw_ddb_index = INVALID_ENTRY;
	ddb_entry->fw_ddb_device_state = DDB_DS_NO_CONNECTION_ACTIVE;
	ddb_entry->ha = ha;
	ddb_entry->unblock_sess = qla4xxx_unblock_flash_ddb;
	ddb_entry->ddb_change = qla4xxx_flash_ddb_change;
	ddb_entry->chap_tbl_idx = INVALID_ENTRY;

	atomic_set(&ddb_entry->retry_relogin_समयr, INVALID_ENTRY);
	atomic_set(&ddb_entry->relogin_समयr, 0);
	atomic_set(&ddb_entry->relogin_retry_count, 0);
	def_समयout = le16_to_cpu(ddb_entry->fw_ddb_entry.def_समयout);
	ddb_entry->शेष_relogin_समयout =
		(def_समयout > LOGIN_TOV) && (def_समयout < LOGIN_TOV * 10) ?
		def_समयout : LOGIN_TOV;
	ddb_entry->शेष_समय2रुको =
		le16_to_cpu(ddb_entry->fw_ddb_entry.iscsi_def_समय2रुको);

	अगर (ql4xdisablesysfsboot &&
	    (idx == ha->pri_ddb_idx || idx == ha->sec_ddb_idx))
		set_bit(DF_BOOT_TGT, &ddb_entry->flags);
पूर्ण

अटल व्योम qla4xxx_रुको_क्रम_ip_configuration(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t idx = 0;
	uपूर्णांक32_t ip_idx[IP_ADDR_COUNT] = अणु0, 1, 2, 3पूर्ण; /* 4 IP पूर्णांकerfaces */
	uपूर्णांक32_t sts[MBOX_REG_COUNT];
	uपूर्णांक32_t ip_state;
	अचिन्हित दीर्घ wसमय;
	पूर्णांक ret;

	wसमय = jअगरfies + (HZ * IP_CONFIG_TOV);
	करो अणु
		क्रम (idx = 0; idx < IP_ADDR_COUNT; idx++) अणु
			अगर (ip_idx[idx] == -1)
				जारी;

			ret = qla4xxx_get_ip_state(ha, 0, ip_idx[idx], sts);

			अगर (ret == QLA_ERROR) अणु
				ip_idx[idx] = -1;
				जारी;
			पूर्ण

			ip_state = (sts[1] & IP_STATE_MASK) >> IP_STATE_SHIFT;

			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "Waiting for IP state for idx = %d, state = 0x%x\n",
					  ip_idx[idx], ip_state));
			अगर (ip_state == IP_ADDRSTATE_UNCONFIGURED ||
			    ip_state == IP_ADDRSTATE_INVALID ||
			    ip_state == IP_ADDRSTATE_PREFERRED ||
			    ip_state == IP_ADDRSTATE_DEPRICATED ||
			    ip_state == IP_ADDRSTATE_DISABLING)
				ip_idx[idx] = -1;
		पूर्ण

		/* Break अगर all IP states checked */
		अगर ((ip_idx[0] == -1) &&
		    (ip_idx[1] == -1) &&
		    (ip_idx[2] == -1) &&
		    (ip_idx[3] == -1))
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण जबतक (समय_after(wसमय, jअगरfies));
पूर्ण

अटल पूर्णांक qla4xxx_cmp_fw_stentry(काष्ठा dev_db_entry *fw_ddb_entry,
				  काष्ठा dev_db_entry *flash_ddb_entry)
अणु
	uपूर्णांक16_t options = 0;
	माप_प्रकार ip_len = IP_ADDR_LEN;

	options = le16_to_cpu(fw_ddb_entry->options);
	अगर (options & DDB_OPT_IPV6_DEVICE)
		ip_len = IPv6_ADDR_LEN;

	अगर (स_भेद(fw_ddb_entry->ip_addr, flash_ddb_entry->ip_addr, ip_len))
		वापस QLA_ERROR;

	अगर (स_भेद(&fw_ddb_entry->isid[0], &flash_ddb_entry->isid[0],
		   माप(fw_ddb_entry->isid)))
		वापस QLA_ERROR;

	अगर (स_भेद(&fw_ddb_entry->port, &flash_ddb_entry->port,
		   माप(fw_ddb_entry->port)))
		वापस QLA_ERROR;

	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक qla4xxx_find_flash_st_idx(काष्ठा scsi_qla_host *ha,
				     काष्ठा dev_db_entry *fw_ddb_entry,
				     uपूर्णांक32_t fw_idx, uपूर्णांक32_t *flash_index)
अणु
	काष्ठा dev_db_entry *flash_ddb_entry;
	dma_addr_t flash_ddb_entry_dma;
	uपूर्णांक32_t idx = 0;
	पूर्णांक max_ddbs;
	पूर्णांक ret = QLA_ERROR, status;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	flash_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
					 &flash_ddb_entry_dma);
	अगर (flash_ddb_entry == शून्य || fw_ddb_entry == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Out of memory\n");
		जाओ निकास_find_st_idx;
	पूर्ण

	status = qla4xxx_flashdb_by_index(ha, flash_ddb_entry,
					  flash_ddb_entry_dma, fw_idx);
	अगर (status == QLA_SUCCESS) अणु
		status = qla4xxx_cmp_fw_stentry(fw_ddb_entry, flash_ddb_entry);
		अगर (status == QLA_SUCCESS) अणु
			*flash_index = fw_idx;
			ret = QLA_SUCCESS;
			जाओ निकास_find_st_idx;
		पूर्ण
	पूर्ण

	क्रम (idx = 0; idx < max_ddbs; idx++) अणु
		status = qla4xxx_flashdb_by_index(ha, flash_ddb_entry,
						  flash_ddb_entry_dma, idx);
		अगर (status == QLA_ERROR)
			जारी;

		status = qla4xxx_cmp_fw_stentry(fw_ddb_entry, flash_ddb_entry);
		अगर (status == QLA_SUCCESS) अणु
			*flash_index = idx;
			ret = QLA_SUCCESS;
			जाओ निकास_find_st_idx;
		पूर्ण
	पूर्ण

	अगर (idx == max_ddbs)
		ql4_prपूर्णांकk(KERN_ERR, ha, "Failed to find ST [%d] in flash\n",
			   fw_idx);

निकास_find_st_idx:
	अगर (flash_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, flash_ddb_entry,
			      flash_ddb_entry_dma);

	वापस ret;
पूर्ण

अटल व्योम qla4xxx_build_st_list(काष्ठा scsi_qla_host *ha,
				  काष्ठा list_head *list_st)
अणु
	काष्ठा qla_ddb_index  *st_ddb_idx;
	पूर्णांक max_ddbs;
	पूर्णांक fw_idx_size;
	काष्ठा dev_db_entry *fw_ddb_entry;
	dma_addr_t fw_ddb_dma;
	पूर्णांक ret;
	uपूर्णांक32_t idx = 0, next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	uपूर्णांक32_t flash_index = -1;
	uपूर्णांक16_t conn_id = 0;

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	अगर (fw_ddb_entry == शून्य) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Out of memory\n"));
		जाओ निकास_st_list;
	पूर्ण

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;
	fw_idx_size = माप(काष्ठा qla_ddb_index);

	क्रम (idx = 0; idx < max_ddbs; idx = next_idx) अणु
		ret = qla4xxx_get_fwddb_entry(ha, idx, fw_ddb_entry, fw_ddb_dma,
					      शून्य, &next_idx, &state,
					      &conn_err, शून्य, &conn_id);
		अगर (ret == QLA_ERROR)
			अवरोध;

		/* Ignore DDB अगर invalid state (unasचिन्हित) */
		अगर (state == DDB_DS_UNASSIGNED)
			जाओ जारी_next_st;

		/* Check अगर ST, add to the list_st */
		अगर (म_माप((अक्षर *) fw_ddb_entry->iscsi_name) != 0)
			जाओ जारी_next_st;

		st_ddb_idx = vzalloc(fw_idx_size);
		अगर (!st_ddb_idx)
			अवरोध;

		ret = qla4xxx_find_flash_st_idx(ha, fw_ddb_entry, idx,
						&flash_index);
		अगर (ret == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "No flash entry for ST at idx [%d]\n", idx);
			st_ddb_idx->flash_ddb_idx = idx;
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "ST at idx [%d] is stored at flash [%d]\n",
				   idx, flash_index);
			st_ddb_idx->flash_ddb_idx = flash_index;
		पूर्ण

		st_ddb_idx->fw_ddb_idx = idx;

		list_add_tail(&st_ddb_idx->list, list_st);
जारी_next_st:
		अगर (next_idx == 0)
			अवरोध;
	पूर्ण

निकास_st_list:
	अगर (fw_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);
पूर्ण

/**
 * qla4xxx_हटाओ_failed_ddb - Remove inactive or failed ddb from list
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @list_ddb: List from which failed ddb to be हटाओd
 *
 * Iterate over the list of DDBs and find and हटाओ DDBs that are either in
 * no connection active state or failed state
 **/
अटल व्योम qla4xxx_हटाओ_failed_ddb(काष्ठा scsi_qla_host *ha,
				      काष्ठा list_head *list_ddb)
अणु
	काष्ठा qla_ddb_index  *ddb_idx, *ddb_idx_पंचांगp;
	uपूर्णांक32_t next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(ddb_idx, ddb_idx_पंचांगp, list_ddb, list) अणु
		ret = qla4xxx_get_fwddb_entry(ha, ddb_idx->fw_ddb_idx,
					      शून्य, 0, शून्य, &next_idx, &state,
					      &conn_err, शून्य, शून्य);
		अगर (ret == QLA_ERROR)
			जारी;

		अगर (state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAILED) अणु
			list_del_init(&ddb_idx->list);
			vमुक्त(ddb_idx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_update_sess_disc_idx(काष्ठा scsi_qla_host *ha,
					 काष्ठा ddb_entry *ddb_entry,
					 काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_session *sess;
	uपूर्णांक32_t max_ddbs = 0;
	uपूर्णांक16_t ddb_link = -1;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	cls_sess = ddb_entry->sess;
	sess = cls_sess->dd_data;

	ddb_link = le16_to_cpu(fw_ddb_entry->ddb_link);
	अगर (ddb_link < max_ddbs)
		sess->discovery_parent_idx = ddb_link;
	अन्यथा
		sess->discovery_parent_idx = DDB_NO_LINK;
पूर्ण

अटल पूर्णांक qla4xxx_sess_conn_setup(काष्ठा scsi_qla_host *ha,
				   काष्ठा dev_db_entry *fw_ddb_entry,
				   पूर्णांक is_reset, uपूर्णांक16_t idx)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	uपूर्णांक16_t cmds_max = 32;
	uपूर्णांक16_t conn_id = 0;
	uपूर्णांक32_t initial_cmdsn = 0;
	पूर्णांक ret = QLA_SUCCESS;

	काष्ठा ddb_entry *ddb_entry = शून्य;

	/* Create session object, with INVALID_ENTRY,
	 * the targer_id would get set when we issue the login
	 */
	cls_sess = iscsi_session_setup(&qla4xxx_iscsi_transport, ha->host,
				       cmds_max, माप(काष्ठा ddb_entry),
				       माप(काष्ठा ql4_task_data),
				       initial_cmdsn, INVALID_ENTRY);
	अगर (!cls_sess) अणु
		ret = QLA_ERROR;
		जाओ निकास_setup;
	पूर्ण

	/*
	 * so calling module_put function to decrement the
	 * reference count.
	 **/
	module_put(qla4xxx_iscsi_transport.owner);
	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ddb_entry->sess = cls_sess;

	cls_sess->recovery_पंचांगo = ql4xsess_recovery_पंचांगo;
	स_नकल(&ddb_entry->fw_ddb_entry, fw_ddb_entry,
	       माप(काष्ठा dev_db_entry));

	qla4xxx_setup_flash_ddb_entry(ha, ddb_entry, idx);

	cls_conn = iscsi_conn_setup(cls_sess, माप(काष्ठा qla_conn), conn_id);

	अगर (!cls_conn) अणु
		ret = QLA_ERROR;
		जाओ निकास_setup;
	पूर्ण

	ddb_entry->conn = cls_conn;

	/* Setup ep, क्रम displaying attributes in sysfs */
	ep = qla4xxx_get_ep_fwdb(ha, fw_ddb_entry);
	अगर (ep) अणु
		ep->conn = cls_conn;
		cls_conn->ep = ep;
	पूर्ण अन्यथा अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Unable to get ep\n"));
		ret = QLA_ERROR;
		जाओ निकास_setup;
	पूर्ण

	/* Update sess/conn params */
	qla4xxx_copy_fwddb_param(ha, fw_ddb_entry, cls_sess, cls_conn);
	qla4xxx_update_sess_disc_idx(ha, ddb_entry, fw_ddb_entry);

	अगर (is_reset == RESET_ADAPTER) अणु
		iscsi_block_session(cls_sess);
		/* Use the relogin path to discover new devices
		 *  by लघु-circuiting the logic of setting
		 *  समयr to relogin - instead set the flags
		 *  to initiate login right away.
		 */
		set_bit(DPC_RELOGIN_DEVICE, &ha->dpc_flags);
		set_bit(DF_RELOGIN, &ddb_entry->flags);
	पूर्ण

निकास_setup:
	वापस ret;
पूर्ण

अटल व्योम qla4xxx_update_fw_ddb_link(काष्ठा scsi_qla_host *ha,
				       काष्ठा list_head *list_ddb,
				       काष्ठा dev_db_entry *fw_ddb_entry)
अणु
	काष्ठा qla_ddb_index  *ddb_idx, *ddb_idx_पंचांगp;
	uपूर्णांक16_t ddb_link;

	ddb_link = le16_to_cpu(fw_ddb_entry->ddb_link);

	list_क्रम_each_entry_safe(ddb_idx, ddb_idx_पंचांगp, list_ddb, list) अणु
		अगर (ddb_idx->fw_ddb_idx == ddb_link) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "Updating NT parent idx from [%d] to [%d]\n",
					  ddb_link, ddb_idx->flash_ddb_idx));
			fw_ddb_entry->ddb_link =
					    cpu_to_le16(ddb_idx->flash_ddb_idx);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_build_nt_list(काष्ठा scsi_qla_host *ha,
				  काष्ठा list_head *list_nt,
				  काष्ठा list_head *list_st,
				  पूर्णांक is_reset)
अणु
	काष्ठा dev_db_entry *fw_ddb_entry;
	काष्ठा ddb_entry *ddb_entry = शून्य;
	dma_addr_t fw_ddb_dma;
	पूर्णांक max_ddbs;
	पूर्णांक fw_idx_size;
	पूर्णांक ret;
	uपूर्णांक32_t idx = 0, next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	uपूर्णांक32_t ddb_idx = -1;
	uपूर्णांक16_t conn_id = 0;
	uपूर्णांक16_t ddb_link = -1;
	काष्ठा qla_ddb_index  *nt_ddb_idx;

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	अगर (fw_ddb_entry == शून्य) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Out of memory\n"));
		जाओ निकास_nt_list;
	पूर्ण
	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;
	fw_idx_size = माप(काष्ठा qla_ddb_index);

	क्रम (idx = 0; idx < max_ddbs; idx = next_idx) अणु
		ret = qla4xxx_get_fwddb_entry(ha, idx, fw_ddb_entry, fw_ddb_dma,
					      शून्य, &next_idx, &state,
					      &conn_err, शून्य, &conn_id);
		अगर (ret == QLA_ERROR)
			अवरोध;

		अगर (qla4xxx_verअगरy_boot_idx(ha, idx) != QLA_SUCCESS)
			जाओ जारी_next_nt;

		/* Check अगर NT, then add to list it */
		अगर (म_माप((अक्षर *) fw_ddb_entry->iscsi_name) == 0)
			जाओ जारी_next_nt;

		ddb_link = le16_to_cpu(fw_ddb_entry->ddb_link);
		अगर (ddb_link < max_ddbs)
			qla4xxx_update_fw_ddb_link(ha, list_st, fw_ddb_entry);

		अगर (!(state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAILED) &&
		    (is_reset == INIT_ADAPTER))
			जाओ जारी_next_nt;

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Adding  DDB to session = 0x%x\n", idx));

		अगर (is_reset == INIT_ADAPTER) अणु
			nt_ddb_idx = vदो_स्मृति(fw_idx_size);
			अगर (!nt_ddb_idx)
				अवरोध;

			nt_ddb_idx->fw_ddb_idx = idx;

			/* Copy original isid as it may get updated in function
			 * qla4xxx_update_isid(). We need original isid in
			 * function qla4xxx_compare_tuple_ddb to find duplicate
			 * target */
			स_नकल(&nt_ddb_idx->flash_isid[0],
			       &fw_ddb_entry->isid[0],
			       माप(nt_ddb_idx->flash_isid));

			ret = qla4xxx_is_flash_ddb_exists(ha, list_nt,
							  fw_ddb_entry);
			अगर (ret == QLA_SUCCESS) अणु
				/* मुक्त nt_ddb_idx and करो not add to list_nt */
				vमुक्त(nt_ddb_idx);
				जाओ जारी_next_nt;
			पूर्ण

			/* Copy updated isid */
			स_नकल(&nt_ddb_idx->fw_ddb, fw_ddb_entry,
			       माप(काष्ठा dev_db_entry));

			list_add_tail(&nt_ddb_idx->list, list_nt);
		पूर्ण अन्यथा अगर (is_reset == RESET_ADAPTER) अणु
			ret = qla4xxx_is_session_exists(ha, fw_ddb_entry,
							&ddb_idx);
			अगर (ret == QLA_SUCCESS) अणु
				ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha,
								       ddb_idx);
				अगर (ddb_entry != शून्य)
					qla4xxx_update_sess_disc_idx(ha,
								     ddb_entry,
								  fw_ddb_entry);
				जाओ जारी_next_nt;
			पूर्ण
		पूर्ण

		ret = qla4xxx_sess_conn_setup(ha, fw_ddb_entry, is_reset, idx);
		अगर (ret == QLA_ERROR)
			जाओ निकास_nt_list;

जारी_next_nt:
		अगर (next_idx == 0)
			अवरोध;
	पूर्ण

निकास_nt_list:
	अगर (fw_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);
पूर्ण

अटल व्योम qla4xxx_build_new_nt_list(काष्ठा scsi_qla_host *ha,
				      काष्ठा list_head *list_nt,
				      uपूर्णांक16_t target_id)
अणु
	काष्ठा dev_db_entry *fw_ddb_entry;
	dma_addr_t fw_ddb_dma;
	पूर्णांक max_ddbs;
	पूर्णांक fw_idx_size;
	पूर्णांक ret;
	uपूर्णांक32_t idx = 0, next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	uपूर्णांक16_t conn_id = 0;
	काष्ठा qla_ddb_index  *nt_ddb_idx;

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	अगर (fw_ddb_entry == शून्य) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "Out of memory\n"));
		जाओ निकास_new_nt_list;
	पूर्ण
	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;
	fw_idx_size = माप(काष्ठा qla_ddb_index);

	क्रम (idx = 0; idx < max_ddbs; idx = next_idx) अणु
		ret = qla4xxx_get_fwddb_entry(ha, idx, fw_ddb_entry, fw_ddb_dma,
					      शून्य, &next_idx, &state,
					      &conn_err, शून्य, &conn_id);
		अगर (ret == QLA_ERROR)
			अवरोध;

		/* Check अगर NT, then add it to list */
		अगर (म_माप((अक्षर *)fw_ddb_entry->iscsi_name) == 0)
			जाओ जारी_next_new_nt;

		अगर (!(state == DDB_DS_NO_CONNECTION_ACTIVE))
			जाओ जारी_next_new_nt;

		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "Adding  DDB to session = 0x%x\n", idx));

		nt_ddb_idx = vदो_स्मृति(fw_idx_size);
		अगर (!nt_ddb_idx)
			अवरोध;

		nt_ddb_idx->fw_ddb_idx = idx;

		ret = qla4xxx_is_session_exists(ha, fw_ddb_entry, शून्य);
		अगर (ret == QLA_SUCCESS) अणु
			/* मुक्त nt_ddb_idx and करो not add to list_nt */
			vमुक्त(nt_ddb_idx);
			जाओ जारी_next_new_nt;
		पूर्ण

		अगर (target_id < max_ddbs)
			fw_ddb_entry->ddb_link = cpu_to_le16(target_id);

		list_add_tail(&nt_ddb_idx->list, list_nt);

		ret = qla4xxx_sess_conn_setup(ha, fw_ddb_entry, RESET_ADAPTER,
					      idx);
		अगर (ret == QLA_ERROR)
			जाओ निकास_new_nt_list;

जारी_next_new_nt:
		अगर (next_idx == 0)
			अवरोध;
	पूर्ण

निकास_new_nt_list:
	अगर (fw_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);
पूर्ण

/**
 * qla4xxx_sysfs_ddb_is_non_persistent - check क्रम non-persistence of ddb entry
 * @dev: dev associated with the sysfs entry
 * @data: poपूर्णांकer to flashnode session object
 *
 * Returns:
 *	1: अगर flashnode entry is non-persistent
 *	0: अगर flashnode entry is persistent
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_is_non_persistent(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess;

	अगर (!iscsi_flashnode_bus_match(dev, शून्य))
		वापस 0;

	fnode_sess = iscsi_dev_to_flash_session(dev);

	वापस (fnode_sess->flash_state == DEV_DB_NON_PERSISTENT);
पूर्ण

/**
 * qla4xxx_sysfs_ddb_tgt_create - Create sysfs entry क्रम target
 * @ha: poपूर्णांकer to host
 * @fw_ddb_entry: flash ddb data
 * @idx: target index
 * @user: अगर set then this call is made from userland अन्यथा from kernel
 *
 * Returns:
 * On sucess: QLA_SUCCESS
 * On failure: QLA_ERROR
 *
 * This create separate sysfs entries क्रम session and connection attributes of
 * the given fw ddb entry.
 * If this is invoked as a result of a userspace call then the entry is marked
 * as nonpersistent using flash_state field.
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_tgt_create(काष्ठा scsi_qla_host *ha,
					काष्ठा dev_db_entry *fw_ddb_entry,
					uपूर्णांक16_t *idx, पूर्णांक user)
अणु
	काष्ठा iscsi_bus_flash_session *fnode_sess = शून्य;
	काष्ठा iscsi_bus_flash_conn *fnode_conn = शून्य;
	पूर्णांक rc = QLA_ERROR;

	fnode_sess = iscsi_create_flashnode_sess(ha->host, *idx,
						 &qla4xxx_iscsi_transport, 0);
	अगर (!fnode_sess) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to create session sysfs entry for flashnode %d of host%lu\n",
			   __func__, *idx, ha->host_no);
		जाओ निकास_tgt_create;
	पूर्ण

	fnode_conn = iscsi_create_flashnode_conn(ha->host, fnode_sess,
						 &qla4xxx_iscsi_transport, 0);
	अगर (!fnode_conn) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to create conn sysfs entry for flashnode %d of host%lu\n",
			   __func__, *idx, ha->host_no);
		जाओ मुक्त_sess;
	पूर्ण

	अगर (user) अणु
		fnode_sess->flash_state = DEV_DB_NON_PERSISTENT;
	पूर्ण अन्यथा अणु
		fnode_sess->flash_state = DEV_DB_PERSISTENT;

		अगर (*idx == ha->pri_ddb_idx || *idx == ha->sec_ddb_idx)
			fnode_sess->is_boot_target = 1;
		अन्यथा
			fnode_sess->is_boot_target = 0;
	पूर्ण

	rc = qla4xxx_copy_from_fwddb_param(fnode_sess, fnode_conn,
					   fw_ddb_entry);
	अगर (rc)
		जाओ मुक्त_sess;

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: sysfs entry %s created\n",
		   __func__, fnode_sess->dev.kobj.name);

	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: sysfs entry %s created\n",
		   __func__, fnode_conn->dev.kobj.name);

	वापस QLA_SUCCESS;

मुक्त_sess:
	iscsi_destroy_flashnode_sess(fnode_sess);

निकास_tgt_create:
	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_add - Add new ddb entry in flash
 * @shost: poपूर्णांकer to host
 * @buf: type of ddb entry (ipv4/ipv6)
 * @len: length of buf
 *
 * This creates new ddb entry in the flash by finding first मुक्त index and
 * storing शेष ddb there. And then create sysfs entry क्रम the new ddb entry.
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_add(काष्ठा Scsi_Host *shost, स्थिर अक्षर *buf,
				 पूर्णांक len)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	काष्ठा device *dev;
	uपूर्णांक16_t idx = 0;
	uपूर्णांक16_t max_ddbs = 0;
	uपूर्णांक32_t options = 0;
	uपूर्णांक32_t rval = QLA_ERROR;

	अगर (strnहालcmp(PORTAL_TYPE_IPV4, buf, 4) &&
	    strnहालcmp(PORTAL_TYPE_IPV6, buf, 4)) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid portal type\n",
				  __func__));
		जाओ निकास_ddb_add;
	पूर्ण

	max_ddbs =  is_qla40XX(ha) ? MAX_PRST_DEV_DB_ENTRIES :
				     MAX_DEV_DB_ENTRIES;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		जाओ निकास_ddb_add;
	पूर्ण

	dev = iscsi_find_flashnode_sess(ha->host, शून्य,
					qla4xxx_sysfs_ddb_is_non_persistent);
	अगर (dev) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: A non-persistent entry %s found\n",
			   __func__, dev->kobj.name);
		put_device(dev);
		जाओ निकास_ddb_add;
	पूर्ण

	/* Index 0 and 1 are reserved क्रम boot target entries */
	क्रम (idx = 2; idx < max_ddbs; idx++) अणु
		अगर (qla4xxx_flashdb_by_index(ha, fw_ddb_entry,
					     fw_ddb_entry_dma, idx))
			अवरोध;
	पूर्ण

	अगर (idx == max_ddbs)
		जाओ निकास_ddb_add;

	अगर (!strnहालcmp("ipv6", buf, 4))
		options |= IPV6_DEFAULT_DDB_ENTRY;

	rval = qla4xxx_get_शेष_ddb(ha, options, fw_ddb_entry_dma);
	अगर (rval == QLA_ERROR)
		जाओ निकास_ddb_add;

	rval = qla4xxx_sysfs_ddb_tgt_create(ha, fw_ddb_entry, &idx, 1);

निकास_ddb_add:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	अगर (rval == QLA_SUCCESS)
		वापस idx;
	अन्यथा
		वापस -EIO;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_apply - ग_लिखो the target ddb contents to Flash
 * @fnode_sess: poपूर्णांकer to session attrs of flash ddb entry
 * @fnode_conn: poपूर्णांकer to connection attrs of flash ddb entry
 *
 * This ग_लिखोs the contents of target ddb buffer to Flash with a valid cookie
 * value in order to make the ddb entry persistent.
 **/
अटल पूर्णांक  qla4xxx_sysfs_ddb_apply(काष्ठा iscsi_bus_flash_session *fnode_sess,
				    काष्ठा iscsi_bus_flash_conn *fnode_conn)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	uपूर्णांक32_t dev_db_start_offset = FLASH_OFFSET_DB_INFO;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक32_t options = 0;
	पूर्णांक rval = 0;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		rval = -ENOMEM;
		जाओ निकास_ddb_apply;
	पूर्ण

	अगर (!strnहालcmp(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
		options |= IPV6_DEFAULT_DDB_ENTRY;

	rval = qla4xxx_get_शेष_ddb(ha, options, fw_ddb_entry_dma);
	अगर (rval == QLA_ERROR)
		जाओ निकास_ddb_apply;

	dev_db_start_offset += (fnode_sess->target_id *
				माप(*fw_ddb_entry));

	qla4xxx_copy_to_fwddb_param(fnode_sess, fnode_conn, fw_ddb_entry);
	fw_ddb_entry->cookie = DDB_VALID_COOKIE;

	rval = qla4xxx_set_flash(ha, fw_ddb_entry_dma, dev_db_start_offset,
				 माप(*fw_ddb_entry), FLASH_OPT_RMW_COMMIT);

	अगर (rval == QLA_SUCCESS) अणु
		fnode_sess->flash_state = DEV_DB_PERSISTENT;
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: flash node %u of host %lu written to flash\n",
			   __func__, fnode_sess->target_id, ha->host_no);
	पूर्ण अन्यथा अणु
		rval = -EIO;
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Error while writing flash node %u of host %lu to flash\n",
			   __func__, fnode_sess->target_id, ha->host_no);
	पूर्ण

निकास_ddb_apply:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	वापस rval;
पूर्ण

अटल sमाप_प्रकार qla4xxx_sysfs_ddb_conn_खोलो(काष्ठा scsi_qla_host *ha,
					   काष्ठा dev_db_entry *fw_ddb_entry,
					   uपूर्णांक16_t idx)
अणु
	काष्ठा dev_db_entry *ddb_entry = शून्य;
	dma_addr_t ddb_entry_dma;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक32_t mbx_sts = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	uपूर्णांक16_t पंचांगo = 0;
	पूर्णांक ret = 0;

	ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*ddb_entry),
				       &ddb_entry_dma, GFP_KERNEL);
	अगर (!ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		वापस QLA_ERROR;
	पूर्ण

	स_नकल(ddb_entry, fw_ddb_entry, माप(*ddb_entry));

	ret = qla4xxx_set_ddb_entry(ha, idx, ddb_entry_dma, &mbx_sts);
	अगर (ret != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to set ddb entry for index %d\n",
				  __func__, idx));
		जाओ निकास_ddb_conn_खोलो;
	पूर्ण

	qla4xxx_conn_खोलो(ha, idx);

	/* To ensure that sendtarमाला_लो is करोne, रुको क्रम at least 12 secs */
	पंचांगo = ((ha->def_समयout > LOGIN_TOV) &&
	       (ha->def_समयout < LOGIN_TOV * 10) ?
	       ha->def_समयout : LOGIN_TOV);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Default time to wait for login to ddb %d\n", पंचांगo));

	wसमय = jअगरfies + (HZ * पंचांगo);
	करो अणु
		ret = qla4xxx_get_fwddb_entry(ha, idx, शून्य, 0, शून्य,
					      शून्य, &state, &conn_err, शून्य,
					      शून्य);
		अगर (ret == QLA_ERROR)
			जारी;

		अगर (state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAILED)
			अवरोध;

		schedule_समयout_unपूर्णांकerruptible(HZ / 10);
	पूर्ण जबतक (समय_after(wसमय, jअगरfies));

निकास_ddb_conn_खोलो:
	अगर (ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*ddb_entry),
				  ddb_entry, ddb_entry_dma);
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_ddb_login_st(काष्ठा scsi_qla_host *ha,
				काष्ठा dev_db_entry *fw_ddb_entry,
				uपूर्णांक16_t target_id)
अणु
	काष्ठा qla_ddb_index *ddb_idx, *ddb_idx_पंचांगp;
	काष्ठा list_head list_nt;
	uपूर्णांक16_t ddb_index;
	पूर्णांक ret = 0;

	अगर (test_bit(AF_ST_DISCOVERY_IN_PROGRESS, &ha->flags)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "%s: A discovery already in progress!\n", __func__);
		वापस QLA_ERROR;
	पूर्ण

	INIT_LIST_HEAD(&list_nt);

	set_bit(AF_ST_DISCOVERY_IN_PROGRESS, &ha->flags);

	ret = qla4xxx_get_ddb_index(ha, &ddb_index);
	अगर (ret == QLA_ERROR)
		जाओ निकास_login_st_clr_bit;

	ret = qla4xxx_sysfs_ddb_conn_खोलो(ha, fw_ddb_entry, ddb_index);
	अगर (ret == QLA_ERROR)
		जाओ निकास_login_st;

	qla4xxx_build_new_nt_list(ha, &list_nt, target_id);

	list_क्रम_each_entry_safe(ddb_idx, ddb_idx_पंचांगp, &list_nt, list) अणु
		list_del_init(&ddb_idx->list);
		qla4xxx_clear_ddb_entry(ha, ddb_idx->fw_ddb_idx);
		vमुक्त(ddb_idx);
	पूर्ण

निकास_login_st:
	अगर (qla4xxx_clear_ddb_entry(ha, ddb_index) == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "Unable to clear DDB index = 0x%x\n", ddb_index);
	पूर्ण

	clear_bit(ddb_index, ha->ddb_idx_map);

निकास_login_st_clr_bit:
	clear_bit(AF_ST_DISCOVERY_IN_PROGRESS, &ha->flags);
	वापस ret;
पूर्ण

अटल पूर्णांक qla4xxx_ddb_login_nt(काष्ठा scsi_qla_host *ha,
				काष्ठा dev_db_entry *fw_ddb_entry,
				uपूर्णांक16_t idx)
अणु
	पूर्णांक ret = QLA_ERROR;

	ret = qla4xxx_is_session_exists(ha, fw_ddb_entry, शून्य);
	अगर (ret != QLA_SUCCESS)
		ret = qla4xxx_sess_conn_setup(ha, fw_ddb_entry, RESET_ADAPTER,
					      idx);
	अन्यथा
		ret = -EPERM;

	वापस ret;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_login - Login to the specअगरied target
 * @fnode_sess: poपूर्णांकer to session attrs of flash ddb entry
 * @fnode_conn: poपूर्णांकer to connection attrs of flash ddb entry
 *
 * This logs in to the specअगरied target
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_login(काष्ठा iscsi_bus_flash_session *fnode_sess,
				   काष्ठा iscsi_bus_flash_conn *fnode_conn)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक32_t options = 0;
	पूर्णांक ret = 0;

	अगर (fnode_sess->flash_state == DEV_DB_NON_PERSISTENT) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Target info is not persistent\n", __func__);
		ret = -EIO;
		जाओ निकास_ddb_login;
	पूर्ण

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		ret = -ENOMEM;
		जाओ निकास_ddb_login;
	पूर्ण

	अगर (!strnहालcmp(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
		options |= IPV6_DEFAULT_DDB_ENTRY;

	ret = qla4xxx_get_शेष_ddb(ha, options, fw_ddb_entry_dma);
	अगर (ret == QLA_ERROR)
		जाओ निकास_ddb_login;

	qla4xxx_copy_to_fwddb_param(fnode_sess, fnode_conn, fw_ddb_entry);
	fw_ddb_entry->cookie = DDB_VALID_COOKIE;

	अगर (म_माप((अक्षर *)fw_ddb_entry->iscsi_name) == 0)
		ret = qla4xxx_ddb_login_st(ha, fw_ddb_entry,
					   fnode_sess->target_id);
	अन्यथा
		ret = qla4xxx_ddb_login_nt(ha, fw_ddb_entry,
					   fnode_sess->target_id);

	अगर (ret > 0)
		ret = -EIO;

निकास_ddb_login:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	वापस ret;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_logout_sid - Logout session क्रम the specअगरied target
 * @cls_sess: poपूर्णांकer to session to be logged out
 *
 * This perक्रमms session log out from the specअगरied target
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_logout_sid(काष्ठा iscsi_cls_session *cls_sess)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb_entry = शून्य;
	काष्ठा scsi_qla_host *ha;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक32_t ddb_state;
	पूर्णांक options;
	पूर्णांक ret = 0;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	अगर (ddb_entry->ddb_type != FLASH_DDB) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Not a flash node session\n",
			   __func__);
		ret = -ENXIO;
		जाओ निकास_ddb_logout;
	पूर्ण

	अगर (test_bit(DF_BOOT_TGT, &ddb_entry->flags)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Logout from boot target entry is not permitted.\n",
			   __func__);
		ret = -EPERM;
		जाओ निकास_ddb_logout;
	पूर्ण

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		ret = -ENOMEM;
		जाओ निकास_ddb_logout;
	पूर्ण

	अगर (test_and_set_bit(DF_DISABLE_RELOGIN, &ddb_entry->flags))
		जाओ ddb_logout_init;

	ret = qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index,
				      fw_ddb_entry, fw_ddb_entry_dma,
				      शून्य, शून्य, &ddb_state, शून्य,
				      शून्य, शून्य);
	अगर (ret == QLA_ERROR)
		जाओ ddb_logout_init;

	अगर (ddb_state == DDB_DS_SESSION_ACTIVE)
		जाओ ddb_logout_init;

	/* रुको until next relogin is triggered using DF_RELOGIN and
	 * clear DF_RELOGIN to aव्योम invocation of further relogin
	 */
	wसमय = jअगरfies + (HZ * RELOGIN_TOV);
	करो अणु
		अगर (test_and_clear_bit(DF_RELOGIN, &ddb_entry->flags))
			जाओ ddb_logout_init;

		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण जबतक ((समय_after(wसमय, jअगरfies)));

ddb_logout_init:
	atomic_set(&ddb_entry->retry_relogin_समयr, INVALID_ENTRY);
	atomic_set(&ddb_entry->relogin_समयr, 0);

	options = LOGOUT_OPTION_CLOSE_SESSION;
	qla4xxx_session_logout_ddb(ha, ddb_entry, options);

	स_रखो(fw_ddb_entry, 0, माप(*fw_ddb_entry));
	wसमय = jअगरfies + (HZ * LOGOUT_TOV);
	करो अणु
		ret = qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index,
					      fw_ddb_entry, fw_ddb_entry_dma,
					      शून्य, शून्य, &ddb_state, शून्य,
					      शून्य, शून्य);
		अगर (ret == QLA_ERROR)
			जाओ ddb_logout_clr_sess;

		अगर ((ddb_state == DDB_DS_NO_CONNECTION_ACTIVE) ||
		    (ddb_state == DDB_DS_SESSION_FAILED))
			जाओ ddb_logout_clr_sess;

		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण जबतक ((समय_after(wसमय, jअगरfies)));

ddb_logout_clr_sess:
	qla4xxx_clear_ddb_entry(ha, ddb_entry->fw_ddb_index);
	/*
	 * we have decremented the reference count of the driver
	 * when we setup the session to have the driver unload
	 * to be seamless without actually destroying the
	 * session
	 **/
	try_module_get(qla4xxx_iscsi_transport.owner);
	iscsi_destroy_endpoपूर्णांक(ddb_entry->conn->ep);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qla4xxx_मुक्त_ddb(ha, ddb_entry);
	clear_bit(ddb_entry->fw_ddb_index, ha->ddb_idx_map);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	iscsi_session_tearकरोwn(ddb_entry->sess);

	clear_bit(DF_DISABLE_RELOGIN, &ddb_entry->flags);
	ret = QLA_SUCCESS;

निकास_ddb_logout:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	वापस ret;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_logout - Logout from the specअगरied target
 * @fnode_sess: poपूर्णांकer to session attrs of flash ddb entry
 * @fnode_conn: poपूर्णांकer to connection attrs of flash ddb entry
 *
 * This perक्रमms log out from the specअगरied target
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_logout(काष्ठा iscsi_bus_flash_session *fnode_sess,
				    काष्ठा iscsi_bus_flash_conn *fnode_conn)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा ql4_tuple_ddb *flash_tddb = शून्य;
	काष्ठा ql4_tuple_ddb *पंचांगp_tddb = शून्य;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	काष्ठा ddb_entry *ddb_entry = शून्य;
	dma_addr_t fw_ddb_dma;
	uपूर्णांक32_t next_idx = 0;
	uपूर्णांक32_t state = 0, conn_err = 0;
	uपूर्णांक16_t conn_id = 0;
	पूर्णांक idx, index;
	पूर्णांक status, ret = 0;

	fw_ddb_entry = dma_pool_alloc(ha->fw_ddb_dma_pool, GFP_KERNEL,
				      &fw_ddb_dma);
	अगर (fw_ddb_entry == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s:Out of memory\n", __func__);
		ret = -ENOMEM;
		जाओ निकास_ddb_logout;
	पूर्ण

	flash_tddb = vzalloc(माप(*flash_tddb));
	अगर (!flash_tddb) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "%s:Memory Allocation failed.\n", __func__);
		ret = -ENOMEM;
		जाओ निकास_ddb_logout;
	पूर्ण

	पंचांगp_tddb = vzalloc(माप(*पंचांगp_tddb));
	अगर (!पंचांगp_tddb) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "%s:Memory Allocation failed.\n", __func__);
		ret = -ENOMEM;
		जाओ निकास_ddb_logout;
	पूर्ण

	अगर (!fnode_sess->targetname) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s:Cannot logout from SendTarget entry\n",
			   __func__);
		ret = -EPERM;
		जाओ निकास_ddb_logout;
	पूर्ण

	अगर (fnode_sess->is_boot_target) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Logout from boot target entry is not permitted.\n",
			   __func__);
		ret = -EPERM;
		जाओ निकास_ddb_logout;
	पूर्ण

	strlcpy(flash_tddb->iscsi_name, fnode_sess->targetname,
		ISCSI_NAME_SIZE);

	अगर (!म_भेदन(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
		प्र_लिखो(flash_tddb->ip_addr, "%pI6", fnode_conn->ipaddress);
	अन्यथा
		प्र_लिखो(flash_tddb->ip_addr, "%pI4", fnode_conn->ipaddress);

	flash_tddb->tpgt = fnode_sess->tpgt;
	flash_tddb->port = fnode_conn->port;

	COPY_ISID(flash_tddb->isid, fnode_sess->isid);

	क्रम (idx = 0; idx < MAX_DDB_ENTRIES; idx++) अणु
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		अगर (ddb_entry == शून्य)
			जारी;

		अगर (ddb_entry->ddb_type != FLASH_DDB)
			जारी;

		index = ddb_entry->sess->target_id;
		status = qla4xxx_get_fwddb_entry(ha, index, fw_ddb_entry,
						 fw_ddb_dma, शून्य, &next_idx,
						 &state, &conn_err, शून्य,
						 &conn_id);
		अगर (status == QLA_ERROR) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		qla4xxx_convert_param_ddb(fw_ddb_entry, पंचांगp_tddb, शून्य);

		status = qla4xxx_compare_tuple_ddb(ha, flash_tddb, पंचांगp_tddb,
						   true);
		अगर (status == QLA_SUCCESS) अणु
			ret = qla4xxx_sysfs_ddb_logout_sid(ddb_entry->sess);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (idx == MAX_DDB_ENTRIES)
		ret = -ESRCH;

निकास_ddb_logout:
	vमुक्त(flash_tddb);
	vमुक्त(पंचांगp_tddb);
	अगर (fw_ddb_entry)
		dma_pool_मुक्त(ha->fw_ddb_dma_pool, fw_ddb_entry, fw_ddb_dma);

	वापस ret;
पूर्ण

अटल पूर्णांक
qla4xxx_sysfs_ddb_get_param(काष्ठा iscsi_bus_flash_session *fnode_sess,
			    पूर्णांक param, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_bus_flash_conn *fnode_conn;
	काष्ठा ql4_chap_table chap_tbl;
	काष्ठा device *dev;
	पूर्णांक parent_type;
	पूर्णांक rc = 0;

	dev = iscsi_find_flashnode_conn(fnode_sess);
	अगर (!dev)
		वापस -EIO;

	fnode_conn = iscsi_dev_to_flash_conn(dev);

	चयन (param) अणु
	हाल ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->is_fw_asचिन्हित_ipv6);
		अवरोध;
	हाल ISCSI_FLASHNODE_PORTAL_TYPE:
		rc = प्र_लिखो(buf, "%s\n", fnode_sess->portal_type);
		अवरोध;
	हाल ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->स्वतः_snd_tgt_disable);
		अवरोध;
	हाल ISCSI_FLASHNODE_DISCOVERY_SESS:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->discovery_sess);
		अवरोध;
	हाल ISCSI_FLASHNODE_ENTRY_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->entry_state);
		अवरोध;
	हाल ISCSI_FLASHNODE_HDR_DGST_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->hdrdgst_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_DATA_DGST_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->datadgst_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_IMM_DATA_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->imm_data_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_INITIAL_R2T_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->initial_r2t_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_DATASEQ_INORDER:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->dataseq_inorder_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_PDU_INORDER:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->pdu_inorder_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_CHAP_AUTH_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->chap_auth_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_SNACK_REQ_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->snack_req_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->discovery_logout_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_BIDI_CHAP_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->bidi_chap_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->discovery_auth_optional);
		अवरोध;
	हाल ISCSI_FLASHNODE_ERL:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->erl);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_बारtamp_stat);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_NAGLE_DISABLE:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_nagle_disable);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_WSF_DISABLE:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_wsf_disable);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_TIMER_SCALE:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_समयr_scale);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_EN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_बारtamp_en);
		अवरोध;
	हाल ISCSI_FLASHNODE_IP_FRAG_DISABLE:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->fragment_disable);
		अवरोध;
	हाल ISCSI_FLASHNODE_MAX_RECV_DLENGTH:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->max_recv_dlength);
		अवरोध;
	हाल ISCSI_FLASHNODE_MAX_XMIT_DLENGTH:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->max_xmit_dlength);
		अवरोध;
	हाल ISCSI_FLASHNODE_FIRST_BURST:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->first_burst);
		अवरोध;
	हाल ISCSI_FLASHNODE_DEF_TIME2WAIT:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->समय2रुको);
		अवरोध;
	हाल ISCSI_FLASHNODE_DEF_TIME2RETAIN:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->समय2retain);
		अवरोध;
	हाल ISCSI_FLASHNODE_MAX_R2T:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->max_r2t);
		अवरोध;
	हाल ISCSI_FLASHNODE_KEEPALIVE_TMO:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->keepalive_समयout);
		अवरोध;
	हाल ISCSI_FLASHNODE_ISID:
		rc = प्र_लिखो(buf, "%pm\n", fnode_sess->isid);
		अवरोध;
	हाल ISCSI_FLASHNODE_TSID:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->tsid);
		अवरोध;
	हाल ISCSI_FLASHNODE_PORT:
		rc = प्र_लिखो(buf, "%d\n", fnode_conn->port);
		अवरोध;
	हाल ISCSI_FLASHNODE_MAX_BURST:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->max_burst);
		अवरोध;
	हाल ISCSI_FLASHNODE_DEF_TASKMGMT_TMO:
		rc = प्र_लिखो(buf, "%u\n",
			     fnode_sess->शेष_taskmgmt_समयout);
		अवरोध;
	हाल ISCSI_FLASHNODE_IPADDR:
		अगर (!म_भेदन(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
			rc = प्र_लिखो(buf, "%pI6\n", fnode_conn->ipaddress);
		अन्यथा
			rc = प्र_लिखो(buf, "%pI4\n", fnode_conn->ipaddress);
		अवरोध;
	हाल ISCSI_FLASHNODE_ALIAS:
		अगर (fnode_sess->targetalias)
			rc = प्र_लिखो(buf, "%s\n", fnode_sess->targetalias);
		अन्यथा
			rc = प्र_लिखो(buf, "\n");
		अवरोध;
	हाल ISCSI_FLASHNODE_REसूचीECT_IPADDR:
		अगर (!म_भेदन(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
			rc = प्र_लिखो(buf, "%pI6\n",
				     fnode_conn->redirect_ipaddr);
		अन्यथा
			rc = प्र_लिखो(buf, "%pI4\n",
				     fnode_conn->redirect_ipaddr);
		अवरोध;
	हाल ISCSI_FLASHNODE_MAX_SEGMENT_SIZE:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->max_segment_size);
		अवरोध;
	हाल ISCSI_FLASHNODE_LOCAL_PORT:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->local_port);
		अवरोध;
	हाल ISCSI_FLASHNODE_IPV4_TOS:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->ipv4_tos);
		अवरोध;
	हाल ISCSI_FLASHNODE_IPV6_TC:
		अगर (!म_भेदन(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
			rc = प्र_लिखो(buf, "%u\n",
				     fnode_conn->ipv6_traffic_class);
		अन्यथा
			rc = प्र_लिखो(buf, "\n");
		अवरोध;
	हाल ISCSI_FLASHNODE_IPV6_FLOW_LABEL:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->ipv6_flow_label);
		अवरोध;
	हाल ISCSI_FLASHNODE_LINK_LOCAL_IPV6:
		अगर (!म_भेदन(fnode_sess->portal_type, PORTAL_TYPE_IPV6, 4))
			rc = प्र_लिखो(buf, "%pI6\n",
				     fnode_conn->link_local_ipv6_addr);
		अन्यथा
			rc = प्र_लिखो(buf, "\n");
		अवरोध;
	हाल ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->discovery_parent_idx);
		अवरोध;
	हाल ISCSI_FLASHNODE_DISCOVERY_PARENT_TYPE:
		अगर (fnode_sess->discovery_parent_type == DDB_ISNS)
			parent_type = ISCSI_DISC_PARENT_ISNS;
		अन्यथा अगर (fnode_sess->discovery_parent_type == DDB_NO_LINK)
			parent_type = ISCSI_DISC_PARENT_UNKNOWN;
		अन्यथा अगर (fnode_sess->discovery_parent_type < MAX_DDB_ENTRIES)
			parent_type = ISCSI_DISC_PARENT_SENDTGT;
		अन्यथा
			parent_type = ISCSI_DISC_PARENT_UNKNOWN;

		rc = प्र_लिखो(buf, "%s\n",
			     iscsi_get_discovery_parent_name(parent_type));
		अवरोध;
	हाल ISCSI_FLASHNODE_NAME:
		अगर (fnode_sess->targetname)
			rc = प्र_लिखो(buf, "%s\n", fnode_sess->targetname);
		अन्यथा
			rc = प्र_लिखो(buf, "\n");
		अवरोध;
	हाल ISCSI_FLASHNODE_TPGT:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->tpgt);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_XMIT_WSF:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_xmit_wsf);
		अवरोध;
	हाल ISCSI_FLASHNODE_TCP_RECV_WSF:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->tcp_recv_wsf);
		अवरोध;
	हाल ISCSI_FLASHNODE_CHAP_OUT_IDX:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->chap_out_idx);
		अवरोध;
	हाल ISCSI_FLASHNODE_USERNAME:
		अगर (fnode_sess->chap_auth_en) अणु
			qla4xxx_get_uni_chap_at_index(ha,
						      chap_tbl.name,
						      chap_tbl.secret,
						      fnode_sess->chap_out_idx);
			rc = प्र_लिखो(buf, "%s\n", chap_tbl.name);
		पूर्ण अन्यथा अणु
			rc = प्र_लिखो(buf, "\n");
		पूर्ण
		अवरोध;
	हाल ISCSI_FLASHNODE_PASSWORD:
		अगर (fnode_sess->chap_auth_en) अणु
			qla4xxx_get_uni_chap_at_index(ha,
						      chap_tbl.name,
						      chap_tbl.secret,
						      fnode_sess->chap_out_idx);
			rc = प्र_लिखो(buf, "%s\n", chap_tbl.secret);
		पूर्ण अन्यथा अणु
			rc = प्र_लिखो(buf, "\n");
		पूर्ण
		अवरोध;
	हाल ISCSI_FLASHNODE_STATSN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->statsn);
		अवरोध;
	हाल ISCSI_FLASHNODE_EXP_STATSN:
		rc = प्र_लिखो(buf, "%u\n", fnode_conn->exp_statsn);
		अवरोध;
	हाल ISCSI_FLASHNODE_IS_BOOT_TGT:
		rc = प्र_लिखो(buf, "%u\n", fnode_sess->is_boot_target);
		अवरोध;
	शेष:
		rc = -ENOSYS;
		अवरोध;
	पूर्ण

	put_device(dev);
	वापस rc;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_set_param - Set parameter क्रम firmware DDB entry
 * @fnode_sess: poपूर्णांकer to session attrs of flash ddb entry
 * @fnode_conn: poपूर्णांकer to connection attrs of flash ddb entry
 * @data: Parameters and their values to update
 * @len: len of data
 *
 * This sets the parameter of flash ddb entry and ग_लिखोs them to flash
 **/
अटल पूर्णांक
qla4xxx_sysfs_ddb_set_param(काष्ठा iscsi_bus_flash_session *fnode_sess,
			    काष्ठा iscsi_bus_flash_conn *fnode_conn,
			    व्योम *data, पूर्णांक len)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	काष्ठा iscsi_flashnode_param_info *fnode_param;
	काष्ठा ql4_chap_table chap_tbl;
	काष्ठा nlattr *attr;
	uपूर्णांक16_t chap_out_idx = INVALID_ENTRY;
	पूर्णांक rc = QLA_ERROR;
	uपूर्णांक32_t rem = len;

	स_रखो((व्योम *)&chap_tbl, 0, माप(chap_tbl));
	nla_क्रम_each_attr(attr, data, len, rem) अणु
		fnode_param = nla_data(attr);

		चयन (fnode_param->param) अणु
		हाल ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6:
			fnode_conn->is_fw_asचिन्हित_ipv6 = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_PORTAL_TYPE:
			स_नकल(fnode_sess->portal_type, fnode_param->value,
			       म_माप(fnode_sess->portal_type));
			अवरोध;
		हाल ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE:
			fnode_sess->स्वतः_snd_tgt_disable =
							fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_DISCOVERY_SESS:
			fnode_sess->discovery_sess = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_ENTRY_EN:
			fnode_sess->entry_state = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_HDR_DGST_EN:
			fnode_conn->hdrdgst_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_DATA_DGST_EN:
			fnode_conn->datadgst_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_IMM_DATA_EN:
			fnode_sess->imm_data_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_INITIAL_R2T_EN:
			fnode_sess->initial_r2t_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_DATASEQ_INORDER:
			fnode_sess->dataseq_inorder_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_PDU_INORDER:
			fnode_sess->pdu_inorder_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_CHAP_AUTH_EN:
			fnode_sess->chap_auth_en = fnode_param->value[0];
			/* Invalidate chap index अगर chap auth is disabled */
			अगर (!fnode_sess->chap_auth_en)
				fnode_sess->chap_out_idx = INVALID_ENTRY;

			अवरोध;
		हाल ISCSI_FLASHNODE_SNACK_REQ_EN:
			fnode_conn->snack_req_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN:
			fnode_sess->discovery_logout_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_BIDI_CHAP_EN:
			fnode_sess->bidi_chap_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL:
			fnode_sess->discovery_auth_optional =
							fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_ERL:
			fnode_sess->erl = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT:
			fnode_conn->tcp_बारtamp_stat = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_NAGLE_DISABLE:
			fnode_conn->tcp_nagle_disable = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_WSF_DISABLE:
			fnode_conn->tcp_wsf_disable = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_TIMER_SCALE:
			fnode_conn->tcp_समयr_scale = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_TIMESTAMP_EN:
			fnode_conn->tcp_बारtamp_en = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_IP_FRAG_DISABLE:
			fnode_conn->fragment_disable = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_MAX_RECV_DLENGTH:
			fnode_conn->max_recv_dlength =
					*(अचिन्हित *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_MAX_XMIT_DLENGTH:
			fnode_conn->max_xmit_dlength =
					*(अचिन्हित *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_FIRST_BURST:
			fnode_sess->first_burst =
					*(अचिन्हित *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_DEF_TIME2WAIT:
			fnode_sess->समय2रुको = *(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_DEF_TIME2RETAIN:
			fnode_sess->समय2retain =
						*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_MAX_R2T:
			fnode_sess->max_r2t =
					*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_KEEPALIVE_TMO:
			fnode_conn->keepalive_समयout =
				*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_ISID:
			स_नकल(fnode_sess->isid, fnode_param->value,
			       माप(fnode_sess->isid));
			अवरोध;
		हाल ISCSI_FLASHNODE_TSID:
			fnode_sess->tsid = *(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_PORT:
			fnode_conn->port = *(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_MAX_BURST:
			fnode_sess->max_burst = *(अचिन्हित *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_DEF_TASKMGMT_TMO:
			fnode_sess->शेष_taskmgmt_समयout =
						*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_IPADDR:
			स_नकल(fnode_conn->ipaddress, fnode_param->value,
			       IPv6_ADDR_LEN);
			अवरोध;
		हाल ISCSI_FLASHNODE_ALIAS:
			rc = iscsi_चयन_str_param(&fnode_sess->targetalias,
						    (अक्षर *)fnode_param->value);
			अवरोध;
		हाल ISCSI_FLASHNODE_REसूचीECT_IPADDR:
			स_नकल(fnode_conn->redirect_ipaddr, fnode_param->value,
			       IPv6_ADDR_LEN);
			अवरोध;
		हाल ISCSI_FLASHNODE_MAX_SEGMENT_SIZE:
			fnode_conn->max_segment_size =
					*(अचिन्हित *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_LOCAL_PORT:
			fnode_conn->local_port =
						*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_IPV4_TOS:
			fnode_conn->ipv4_tos = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_IPV6_TC:
			fnode_conn->ipv6_traffic_class = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_IPV6_FLOW_LABEL:
			fnode_conn->ipv6_flow_label = fnode_param->value[0];
			अवरोध;
		हाल ISCSI_FLASHNODE_NAME:
			rc = iscsi_चयन_str_param(&fnode_sess->targetname,
						    (अक्षर *)fnode_param->value);
			अवरोध;
		हाल ISCSI_FLASHNODE_TPGT:
			fnode_sess->tpgt = *(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_LINK_LOCAL_IPV6:
			स_नकल(fnode_conn->link_local_ipv6_addr,
			       fnode_param->value, IPv6_ADDR_LEN);
			अवरोध;
		हाल ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX:
			fnode_sess->discovery_parent_idx =
						*(uपूर्णांक16_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_XMIT_WSF:
			fnode_conn->tcp_xmit_wsf =
						*(uपूर्णांक8_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_TCP_RECV_WSF:
			fnode_conn->tcp_recv_wsf =
						*(uपूर्णांक8_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_STATSN:
			fnode_conn->statsn = *(uपूर्णांक32_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_EXP_STATSN:
			fnode_conn->exp_statsn =
						*(uपूर्णांक32_t *)fnode_param->value;
			अवरोध;
		हाल ISCSI_FLASHNODE_CHAP_OUT_IDX:
			chap_out_idx = *(uपूर्णांक16_t *)fnode_param->value;
			अगर (!qla4xxx_get_uni_chap_at_index(ha,
							   chap_tbl.name,
							   chap_tbl.secret,
							   chap_out_idx)) अणु
				fnode_sess->chap_out_idx = chap_out_idx;
				/* Enable chap auth अगर chap index is valid */
				fnode_sess->chap_auth_en = QL4_PARAM_ENABLE;
			पूर्ण
			अवरोध;
		शेष:
			ql4_prपूर्णांकk(KERN_ERR, ha,
				   "%s: No such sysfs attribute\n", __func__);
			rc = -ENOSYS;
			जाओ निकास_set_param;
		पूर्ण
	पूर्ण

	rc = qla4xxx_sysfs_ddb_apply(fnode_sess, fnode_conn);

निकास_set_param:
	वापस rc;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_delete - Delete firmware DDB entry
 * @fnode_sess: poपूर्णांकer to session attrs of flash ddb entry
 *
 * This invalidates the flash ddb entry at the given index
 **/
अटल पूर्णांक qla4xxx_sysfs_ddb_delete(काष्ठा iscsi_bus_flash_session *fnode_sess)
अणु
	काष्ठा Scsi_Host *shost = iscsi_flash_session_to_shost(fnode_sess);
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	uपूर्णांक32_t dev_db_start_offset;
	uपूर्णांक32_t dev_db_end_offset;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक16_t *ddb_cookie = शून्य;
	माप_प्रकार ddb_size = 0;
	व्योम *pddb = शून्य;
	पूर्णांक target_id;
	पूर्णांक rc = 0;

	अगर (fnode_sess->is_boot_target) अणु
		rc = -EPERM;
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Deletion of boot target entry is not permitted.\n",
				  __func__));
		जाओ निकास_ddb_del;
	पूर्ण

	अगर (fnode_sess->flash_state == DEV_DB_NON_PERSISTENT)
		जाओ sysfs_ddb_del;

	अगर (is_qla40XX(ha)) अणु
		dev_db_start_offset = FLASH_OFFSET_DB_INFO;
		dev_db_end_offset = FLASH_OFFSET_DB_END;
		dev_db_start_offset += (fnode_sess->target_id *
				       माप(*fw_ddb_entry));
		ddb_size = माप(*fw_ddb_entry);
	पूर्ण अन्यथा अणु
		dev_db_start_offset = FLASH_RAW_ACCESS_ADDR +
				      (ha->hw.flt_region_ddb << 2);
		/* flt_ddb_size is DDB table size क्रम both ports
		 * so भागide it by 2 to calculate the offset क्रम second port
		 */
		अगर (ha->port_num == 1)
			dev_db_start_offset += (ha->hw.flt_ddb_size / 2);

		dev_db_end_offset = dev_db_start_offset +
				    (ha->hw.flt_ddb_size / 2);

		dev_db_start_offset += (fnode_sess->target_id *
				       माप(*fw_ddb_entry));
		dev_db_start_offset += दुरत्व(काष्ठा dev_db_entry, cookie);

		ddb_size = माप(*ddb_cookie);
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s: start offset=%u, end offset=%u\n",
			  __func__, dev_db_start_offset, dev_db_end_offset));

	अगर (dev_db_start_offset > dev_db_end_offset) अणु
		rc = -EIO;
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s:Invalid DDB index %u\n",
				  __func__, fnode_sess->target_id));
		जाओ निकास_ddb_del;
	पूर्ण

	pddb = dma_alloc_coherent(&ha->pdev->dev, ddb_size,
				  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!pddb) अणु
		rc = -ENOMEM;
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		जाओ निकास_ddb_del;
	पूर्ण

	अगर (is_qla40XX(ha)) अणु
		fw_ddb_entry = pddb;
		स_रखो(fw_ddb_entry, 0, ddb_size);
		ddb_cookie = &fw_ddb_entry->cookie;
	पूर्ण अन्यथा अणु
		ddb_cookie = pddb;
	पूर्ण

	/* invalidate the cookie */
	*ddb_cookie = 0xFFEE;
	qla4xxx_set_flash(ha, fw_ddb_entry_dma, dev_db_start_offset,
			  ddb_size, FLASH_OPT_RMW_COMMIT);

sysfs_ddb_del:
	target_id = fnode_sess->target_id;
	iscsi_destroy_flashnode_sess(fnode_sess);
	ql4_prपूर्णांकk(KERN_INFO, ha,
		   "%s: session and conn entries for flashnode %u of host %lu deleted\n",
		   __func__, target_id, ha->host_no);
निकास_ddb_del:
	अगर (pddb)
		dma_मुक्त_coherent(&ha->pdev->dev, ddb_size, pddb,
				  fw_ddb_entry_dma);
	वापस rc;
पूर्ण

/**
 * qla4xxx_sysfs_ddb_export - Create sysfs entries क्रम firmware DDBs
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Export the firmware DDB क्रम all send tarमाला_लो and normal tarमाला_लो to sysfs.
 **/
पूर्णांक qla4xxx_sysfs_ddb_export(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	uपूर्णांक16_t max_ddbs;
	uपूर्णांक16_t idx = 0;
	पूर्णांक ret = QLA_SUCCESS;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev,
					  माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		वापस -ENOMEM;
	पूर्ण

	max_ddbs =  is_qla40XX(ha) ? MAX_PRST_DEV_DB_ENTRIES :
				     MAX_DEV_DB_ENTRIES;

	क्रम (idx = 0; idx < max_ddbs; idx++) अणु
		अगर (qla4xxx_flashdb_by_index(ha, fw_ddb_entry, fw_ddb_entry_dma,
					     idx))
			जारी;

		ret = qla4xxx_sysfs_ddb_tgt_create(ha, fw_ddb_entry, &idx, 0);
		अगर (ret) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry), fw_ddb_entry,
			  fw_ddb_entry_dma);

	वापस ret;
पूर्ण

अटल व्योम qla4xxx_sysfs_ddb_हटाओ(काष्ठा scsi_qla_host *ha)
अणु
	iscsi_destroy_all_flashnode(ha->host);
पूर्ण

/**
 * qla4xxx_build_ddb_list - Build ddb list and setup sessions
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @is_reset: Is this init path or reset path
 *
 * Create a list of sendtarमाला_लो (st) from firmware DDBs, issue send tarमाला_लो
 * using connection खोलो, then create the list of normal tarमाला_लो (nt)
 * from firmware DDBs. Based on the list of nt setup session and connection
 * objects.
 **/
व्योम qla4xxx_build_ddb_list(काष्ठा scsi_qla_host *ha, पूर्णांक is_reset)
अणु
	uपूर्णांक16_t पंचांगo = 0;
	काष्ठा list_head list_st, list_nt;
	काष्ठा qla_ddb_index  *st_ddb_idx, *st_ddb_idx_पंचांगp;
	अचिन्हित दीर्घ wसमय;

	अगर (!test_bit(AF_LINK_UP, &ha->flags)) अणु
		set_bit(AF_BUILD_DDB_LIST, &ha->flags);
		ha->is_reset = is_reset;
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&list_st);
	INIT_LIST_HEAD(&list_nt);

	qla4xxx_build_st_list(ha, &list_st);

	/* Beक्रमe issuing conn खोलो mbox, ensure all IPs states are configured
	 * Note, conn खोलो fails अगर IPs are not configured
	 */
	qla4xxx_रुको_क्रम_ip_configuration(ha);

	/* Go thru the STs and fire the sendtarमाला_लो by issuing conn खोलो mbx */
	list_क्रम_each_entry_safe(st_ddb_idx, st_ddb_idx_पंचांगp, &list_st, list) अणु
		qla4xxx_conn_खोलो(ha, st_ddb_idx->fw_ddb_idx);
	पूर्ण

	/* Wait to ensure all sendtarमाला_लो are करोne क्रम min 12 sec रुको */
	पंचांगo = ((ha->def_समयout > LOGIN_TOV) &&
	       (ha->def_समयout < LOGIN_TOV * 10) ?
	       ha->def_समयout : LOGIN_TOV);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "Default time to wait for build ddb %d\n", पंचांगo));

	wसमय = jअगरfies + (HZ * पंचांगo);
	करो अणु
		अगर (list_empty(&list_st))
			अवरोध;

		qla4xxx_हटाओ_failed_ddb(ha, &list_st);
		schedule_समयout_unपूर्णांकerruptible(HZ / 10);
	पूर्ण जबतक (समय_after(wसमय, jअगरfies));


	qla4xxx_build_nt_list(ha, &list_nt, &list_st, is_reset);

	qla4xxx_मुक्त_ddb_list(&list_st);
	qla4xxx_मुक्त_ddb_list(&list_nt);

	qla4xxx_मुक्त_ddb_index(ha);
पूर्ण

/**
 * qla4xxx_रुको_login_resp_boot_tgt -  Wait क्रम iSCSI boot target login
 * response.
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * When the boot entry is normal iSCSI target then DF_BOOT_TGT flag will be
 * set in DDB and we will रुको क्रम login response of boot tarमाला_लो during
 * probe.
 **/
अटल व्योम qla4xxx_रुको_login_resp_boot_tgt(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक32_t ddb_state;
	पूर्णांक max_ddbs, idx, ret;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		जाओ निकास_login_resp;
	पूर्ण

	wसमय = jअगरfies + (HZ * BOOT_LOGIN_RESP_TOV);

	क्रम (idx = 0; idx < max_ddbs; idx++) अणु
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		अगर (ddb_entry == शून्य)
			जारी;

		अगर (test_bit(DF_BOOT_TGT, &ddb_entry->flags)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: DDB index [%d]\n", __func__,
					  ddb_entry->fw_ddb_index));
			करो अणु
				ret = qla4xxx_get_fwddb_entry(ha,
						ddb_entry->fw_ddb_index,
						fw_ddb_entry, fw_ddb_entry_dma,
						शून्य, शून्य, &ddb_state, शून्य,
						शून्य, शून्य);
				अगर (ret == QLA_ERROR)
					जाओ निकास_login_resp;

				अगर ((ddb_state == DDB_DS_SESSION_ACTIVE) ||
				    (ddb_state == DDB_DS_SESSION_FAILED))
					अवरोध;

				schedule_समयout_unपूर्णांकerruptible(HZ);

			पूर्ण जबतक ((समय_after(wसमय, jअगरfies)));

			अगर (!समय_after(wसमय, jअगरfies)) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "%s: Login response wait timer expired\n",
						  __func__));
				 जाओ निकास_login_resp;
			पूर्ण
		पूर्ण
	पूर्ण

निकास_login_resp:
	अगर (fw_ddb_entry)
		dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
पूर्ण

/**
 * qla4xxx_probe_adapter - callback function to probe HBA
 * @pdev: poपूर्णांकer to pci_dev काष्ठाure
 * @ent: poपूर्णांकer to pci_device entry
 *
 * This routine will probe क्रम Qlogic 4xxx iSCSI host adapters.
 * It वापसs zero अगर successful. It also initializes all data necessary क्रम
 * the driver.
 **/
अटल पूर्णांक qla4xxx_probe_adapter(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret = -ENODEV, status;
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_qla_host *ha;
	uपूर्णांक8_t init_retry_count = 0;
	अक्षर buf[34];
	काष्ठा qla4_8xxx_legacy_पूर्णांकr_set *nx_legacy_पूर्णांकr;
	uपूर्णांक32_t dev_state;

	अगर (pci_enable_device(pdev))
		वापस -1;

	host = iscsi_host_alloc(&qla4xxx_driver_ढाँचा, माप(*ha), 0);
	अगर (host == शून्य) अणु
		prपूर्णांकk(KERN_WARNING
		       "qla4xxx: Couldn't allocate host from scsi layer!\n");
		जाओ probe_disable_device;
	पूर्ण

	/* Clear our data area */
	ha = to_qla_host(host);
	स_रखो(ha, 0, माप(*ha));

	/* Save the inक्रमmation from PCI BIOS.	*/
	ha->pdev = pdev;
	ha->host = host;
	ha->host_no = host->host_no;
	ha->func_num = PCI_FUNC(ha->pdev->devfn);

	pci_enable_pcie_error_reporting(pdev);

	/* Setup Runसमय configurable options */
	अगर (is_qla8022(ha)) अणु
		ha->isp_ops = &qla4_82xx_isp_ops;
		ha->reg_tbl = (uपूर्णांक32_t *) qla4_82xx_reg_tbl;
		ha->qdr_sn_winकरोw = -1;
		ha->ddr_mn_winकरोw = -1;
		ha->curr_winकरोw = 255;
		nx_legacy_पूर्णांकr = &legacy_पूर्णांकr[ha->func_num];
		ha->nx_legacy_पूर्णांकr.पूर्णांक_vec_bit = nx_legacy_पूर्णांकr->पूर्णांक_vec_bit;
		ha->nx_legacy_पूर्णांकr.tgt_status_reg =
			nx_legacy_पूर्णांकr->tgt_status_reg;
		ha->nx_legacy_पूर्णांकr.tgt_mask_reg = nx_legacy_पूर्णांकr->tgt_mask_reg;
		ha->nx_legacy_पूर्णांकr.pci_पूर्णांक_reg = nx_legacy_पूर्णांकr->pci_पूर्णांक_reg;
	पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ha->isp_ops = &qla4_83xx_isp_ops;
		ha->reg_tbl = (uपूर्णांक32_t *)qla4_83xx_reg_tbl;
	पूर्ण अन्यथा अणु
		ha->isp_ops = &qla4xxx_isp_ops;
	पूर्ण

	अगर (is_qla80XX(ha)) अणु
		rwlock_init(&ha->hw_lock);
		ha->pf_bit = ha->func_num << 16;
		/* Set EEH reset type to fundamental अगर required by hba */
		pdev->needs_freset = 1;
	पूर्ण

	/* Configure PCI I/O space. */
	ret = ha->isp_ops->iospace_config(ha);
	अगर (ret)
		जाओ probe_failed_ioconfig;

	ql4_prपूर्णांकk(KERN_INFO, ha, "Found an ISP%04x, irq %d, iobase 0x%p\n",
		   pdev->device, pdev->irq, ha->reg);

	qla4xxx_config_dma_addressing(ha);

	/* Initialize lists and spinlocks. */
	INIT_LIST_HEAD(&ha->मुक्त_srb_q);

	mutex_init(&ha->mbox_sem);
	mutex_init(&ha->chap_sem);
	init_completion(&ha->mbx_पूर्णांकr_comp);
	init_completion(&ha->disable_acb_comp);
	init_completion(&ha->idc_comp);
	init_completion(&ha->link_up_comp);

	spin_lock_init(&ha->hardware_lock);
	spin_lock_init(&ha->work_lock);

	/* Initialize work list */
	INIT_LIST_HEAD(&ha->work_list);

	/* Allocate dma buffers */
	अगर (qla4xxx_mem_alloc(ha)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "[ERROR] Failed to allocate memory for adapter\n");

		ret = -ENOMEM;
		जाओ probe_failed;
	पूर्ण

	host->cmd_per_lun = 3;
	host->max_channel = 0;
	host->max_lun = MAX_LUNS - 1;
	host->max_id = MAX_TARGETS;
	host->max_cmd_len = IOCB_MAX_CDB_LEN;
	host->can_queue = MAX_SRBS ;
	host->transportt = qla4xxx_scsi_transport;

	pci_set_drvdata(pdev, ha);

	ret = scsi_add_host(host, &pdev->dev);
	अगर (ret)
		जाओ probe_failed;

	अगर (is_qla80XX(ha))
		qla4_8xxx_get_flash_info(ha);

	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		qla4_83xx_पढ़ो_reset_ढाँचा(ha);
		/*
		 * NOTE: If ql4करोntresethba==1, set IDC_CTRL DONTRESET_BIT0.
		 * If DONRESET_BIT0 is set, drivers should not set dev_state
		 * to NEED_RESET. But अगर NEED_RESET is set, drivers should
		 * should honor the reset.
		 */
		अगर (ql4xकरोntresethba == 1)
			qla4_83xx_set_idc_करोntreset(ha);
	पूर्ण

	/*
	 * Initialize the Host adapter request/response queues and
	 * firmware
	 * NOTE: पूर्णांकerrupts enabled upon successful completion
	 */
	status = qla4xxx_initialize_adapter(ha, INIT_ADAPTER);

	/* Dont retry adapter initialization अगर IRQ allocation failed */
	अगर (is_qla80XX(ha) && (status == QLA_ERROR))
		जाओ skip_retry_init;

	जबतक ((!test_bit(AF_ONLINE, &ha->flags)) &&
	    init_retry_count++ < MAX_INIT_RETRIES) अणु

		अगर (is_qla80XX(ha)) अणु
			ha->isp_ops->idc_lock(ha);
			dev_state = qla4_8xxx_rd_direct(ha,
							QLA8XXX_CRB_DEV_STATE);
			ha->isp_ops->idc_unlock(ha);
			अगर (dev_state == QLA8XXX_DEV_FAILED) अणु
				ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: don't retry "
				    "initialize adapter. H/W is in failed state\n",
				    __func__);
				अवरोध;
			पूर्ण
		पूर्ण
		DEBUG2(prपूर्णांकk("scsi: %s: retrying adapter initialization "
			      "(%d)\n", __func__, init_retry_count));

		अगर (ha->isp_ops->reset_chip(ha) == QLA_ERROR)
			जारी;

		status = qla4xxx_initialize_adapter(ha, INIT_ADAPTER);
		अगर (is_qla80XX(ha) && (status == QLA_ERROR)) अणु
			अगर (qla4_8xxx_check_init_adapter_retry(ha) == QLA_ERROR)
				जाओ skip_retry_init;
		पूर्ण
	पूर्ण

skip_retry_init:
	अगर (!test_bit(AF_ONLINE, &ha->flags)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Failed to initialize adapter\n");

		अगर ((is_qla8022(ha) && ql4xकरोntresethba) ||
		    ((is_qla8032(ha) || is_qla8042(ha)) &&
		     qla4_83xx_idc_करोntreset(ha))) अणु
			/* Put the device in failed state. */
			DEBUG2(prपूर्णांकk(KERN_ERR "HW STATE: FAILED\n"));
			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
			ha->isp_ops->idc_unlock(ha);
		पूर्ण
		ret = -ENODEV;
		जाओ हटाओ_host;
	पूर्ण

	/* Startup the kernel thपढ़ो क्रम this host adapter. */
	DEBUG2(prपूर्णांकk("scsi: %s: Starting kernel thread for "
		      "qla4xxx_dpc\n", __func__));
	प्र_लिखो(buf, "qla4xxx_%lu_dpc", ha->host_no);
	ha->dpc_thपढ़ो = create_singlethपढ़ो_workqueue(buf);
	अगर (!ha->dpc_thपढ़ो) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Unable to start DPC thread!\n");
		ret = -ENODEV;
		जाओ हटाओ_host;
	पूर्ण
	INIT_WORK(&ha->dpc_work, qla4xxx_करो_dpc);

	ha->task_wq = alloc_workqueue("qla4xxx_%lu_task", WQ_MEM_RECLAIM, 1,
				      ha->host_no);
	अगर (!ha->task_wq) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Unable to start task thread!\n");
		ret = -ENODEV;
		जाओ हटाओ_host;
	पूर्ण

	/*
	 * For ISP-8XXX, request_irqs is called in qla4_8xxx_load_risc
	 * (which is called indirectly by qla4xxx_initialize_adapter),
	 * so that irqs will be रेजिस्टरed after crbinit but beक्रमe
	 * mbx_पूर्णांकr_enable.
	 */
	अगर (is_qla40XX(ha)) अणु
		ret = qla4xxx_request_irqs(ha);
		अगर (ret) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha, "Failed to reserve "
			    "interrupt %d already in use.\n", pdev->irq);
			जाओ हटाओ_host;
		पूर्ण
	पूर्ण

	pci_save_state(ha->pdev);
	ha->isp_ops->enable_पूर्णांकrs(ha);

	/* Start समयr thपढ़ो. */
	qla4xxx_start_समयr(ha, 1);

	set_bit(AF_INIT_DONE, &ha->flags);

	qla4_8xxx_alloc_sysfs_attr(ha);

	prपूर्णांकk(KERN_INFO
	       " QLogic iSCSI HBA Driver version: %s\n"
	       "  QLogic ISP%04x @ %s, host#=%ld, fw=%02d.%02d.%02d.%02d\n",
	       qla4xxx_version_str, ha->pdev->device, pci_name(ha->pdev),
	       ha->host_no, ha->fw_info.fw_major, ha->fw_info.fw_minor,
	       ha->fw_info.fw_patch, ha->fw_info.fw_build);

	/* Set the driver version */
	अगर (is_qla80XX(ha))
		qla4_8xxx_set_param(ha, SET_DRVR_VERSION);

	अगर (qla4xxx_setup_boot_info(ha))
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: No iSCSI boot target configured\n", __func__);

	set_bit(DPC_SYSFS_DDB_EXPORT, &ha->dpc_flags);
	/* Perक्रमm the build ddb list and login to each */
	qla4xxx_build_ddb_list(ha, INIT_ADAPTER);
	iscsi_host_क्रम_each_session(ha->host, qla4xxx_login_flash_ddb);
	qla4xxx_रुको_login_resp_boot_tgt(ha);

	qla4xxx_create_chap_list(ha);

	qla4xxx_create_अगरaces(ha);
	वापस 0;

हटाओ_host:
	scsi_हटाओ_host(ha->host);

probe_failed:
	qla4xxx_मुक्त_adapter(ha);

probe_failed_ioconfig:
	pci_disable_pcie_error_reporting(pdev);
	scsi_host_put(ha->host);

probe_disable_device:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

/**
 * qla4xxx_prevent_other_port_reinit - prevent other port from re-initialize
 * @ha: poपूर्णांकer to adapter काष्ठाure
 *
 * Mark the other ISP-4xxx port to indicate that the driver is being हटाओd,
 * so that the other port will not re-initialize जबतक in the process of
 * removing the ha due to driver unload or hba hotplug.
 **/
अटल व्योम qla4xxx_prevent_other_port_reinit(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा scsi_qla_host *other_ha = शून्य;
	काष्ठा pci_dev *other_pdev = शून्य;
	पूर्णांक fn = ISP4XXX_PCI_FN_2;

	/*iscsi function numbers क्रम ISP4xxx is 1 and 3*/
	अगर (PCI_FUNC(ha->pdev->devfn) & BIT_1)
		fn = ISP4XXX_PCI_FN_1;

	other_pdev =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(ha->pdev->bus),
		ha->pdev->bus->number, PCI_DEVFN(PCI_SLOT(ha->pdev->devfn),
		fn));

	/* Get other_ha अगर other_pdev is valid and state is enable*/
	अगर (other_pdev) अणु
		अगर (atomic_पढ़ो(&other_pdev->enable_cnt)) अणु
			other_ha = pci_get_drvdata(other_pdev);
			अगर (other_ha) अणु
				set_bit(AF_HA_REMOVAL, &other_ha->flags);
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: "
				    "Prevent %s reinit\n", __func__,
				    dev_name(&other_ha->pdev->dev)));
			पूर्ण
		पूर्ण
		pci_dev_put(other_pdev);
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_destroy_ddb(काष्ठा scsi_qla_host *ha,
		काष्ठा ddb_entry *ddb_entry)
अणु
	काष्ठा dev_db_entry *fw_ddb_entry = शून्य;
	dma_addr_t fw_ddb_entry_dma;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक32_t ddb_state;
	पूर्णांक options;
	पूर्णांक status;

	options = LOGOUT_OPTION_CLOSE_SESSION;
	अगर (qla4xxx_session_logout_ddb(ha, ddb_entry, options) == QLA_ERROR) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Logout failed\n", __func__);
		जाओ clear_ddb;
	पूर्ण

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Unable to allocate dma buffer\n", __func__);
		जाओ clear_ddb;
	पूर्ण

	wसमय = jअगरfies + (HZ * LOGOUT_TOV);
	करो अणु
		status = qla4xxx_get_fwddb_entry(ha, ddb_entry->fw_ddb_index,
						 fw_ddb_entry, fw_ddb_entry_dma,
						 शून्य, शून्य, &ddb_state, शून्य,
						 शून्य, शून्य);
		अगर (status == QLA_ERROR)
			जाओ मुक्त_ddb;

		अगर ((ddb_state == DDB_DS_NO_CONNECTION_ACTIVE) ||
		    (ddb_state == DDB_DS_SESSION_FAILED))
			जाओ मुक्त_ddb;

		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण जबतक ((समय_after(wसमय, jअगरfies)));

मुक्त_ddb:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
			  fw_ddb_entry, fw_ddb_entry_dma);
clear_ddb:
	qla4xxx_clear_ddb_entry(ha, ddb_entry->fw_ddb_index);
पूर्ण

अटल व्योम qla4xxx_destroy_fw_ddb_session(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा ddb_entry *ddb_entry;
	पूर्णांक idx;

	क्रम (idx = 0; idx < MAX_DDB_ENTRIES; idx++) अणु

		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		अगर ((ddb_entry != शून्य) &&
		    (ddb_entry->ddb_type == FLASH_DDB)) अणु

			qla4xxx_destroy_ddb(ha, ddb_entry);
			/*
			 * we have decremented the reference count of the driver
			 * when we setup the session to have the driver unload
			 * to be seamless without actually destroying the
			 * session
			 **/
			try_module_get(qla4xxx_iscsi_transport.owner);
			iscsi_destroy_endpoपूर्णांक(ddb_entry->conn->ep);
			qla4xxx_मुक्त_ddb(ha, ddb_entry);
			iscsi_session_tearकरोwn(ddb_entry->sess);
		पूर्ण
	पूर्ण
पूर्ण
/**
 * qla4xxx_हटाओ_adapter - callback function to हटाओ adapter.
 * @pdev: PCI device poपूर्णांकer
 **/
अटल व्योम qla4xxx_हटाओ_adapter(काष्ठा pci_dev *pdev)
अणु
	काष्ठा scsi_qla_host *ha;

	/*
	 * If the PCI device is disabled then it means probe_adapter had
	 * failed and resources alपढ़ोy cleaned up on probe_adapter निकास.
	 */
	अगर (!pci_is_enabled(pdev))
		वापस;

	ha = pci_get_drvdata(pdev);

	अगर (is_qla40XX(ha))
		qla4xxx_prevent_other_port_reinit(ha);

	/* destroy अगरace from sysfs */
	qla4xxx_destroy_अगरaces(ha);

	अगर ((!ql4xdisablesysfsboot) && ha->boot_kset)
		iscsi_boot_destroy_kset(ha->boot_kset);

	qla4xxx_destroy_fw_ddb_session(ha);
	qla4_8xxx_मुक्त_sysfs_attr(ha);

	qla4xxx_sysfs_ddb_हटाओ(ha);
	scsi_हटाओ_host(ha->host);

	qla4xxx_मुक्त_adapter(ha);

	scsi_host_put(ha->host);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * qla4xxx_config_dma_addressing() - Configure OS DMA addressing method.
 * @ha: HA context
 */
अटल व्योम qla4xxx_config_dma_addressing(काष्ठा scsi_qla_host *ha)
अणु
	/* Update our PCI device dma_mask क्रम full 64 bit mask */
	अगर (dma_set_mask_and_coherent(&ha->pdev->dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(&ha->pdev->dev,
			  "Failed to set 64 bit PCI consistent mask; "
			   "using 32 bit.\n");
		dma_set_mask_and_coherent(&ha->pdev->dev, DMA_BIT_MASK(32));
	पूर्ण
पूर्ण

अटल पूर्णांक qla4xxx_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_session *sess;
	काष्ठा ddb_entry *ddb;
	पूर्णांक queue_depth = QL4_DEF_QDEPTH;

	cls_sess = starget_to_session(sdev->sdev_target);
	sess = cls_sess->dd_data;
	ddb = sess->dd_data;

	sdev->hostdata = ddb;

	अगर (ql4xmaxqdepth != 0 && ql4xmaxqdepth <= 0xffffU)
		queue_depth = ql4xmaxqdepth;

	scsi_change_queue_depth(sdev, queue_depth);
	वापस 0;
पूर्ण

/**
 * qla4xxx_del_from_active_array - वापसs an active srb
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @index: index पूर्णांकo the active_array
 *
 * This routine हटाओs and वापसs the srb at the specअगरied index
 **/
काष्ठा srb *qla4xxx_del_from_active_array(काष्ठा scsi_qla_host *ha,
    uपूर्णांक32_t index)
अणु
	काष्ठा srb *srb = शून्य;
	काष्ठा scsi_cmnd *cmd = शून्य;

	cmd = scsi_host_find_tag(ha->host, index);
	अगर (!cmd)
		वापस srb;

	srb = (काष्ठा srb *)CMD_SP(cmd);
	अगर (!srb)
		वापस srb;

	/* update counters */
	अगर (srb->flags & SRB_DMA_VALID) अणु
		ha->iocb_cnt -= srb->iocb_cnt;
		अगर (srb->cmd)
			srb->cmd->host_scribble =
				(अचिन्हित अक्षर *)(अचिन्हित दीर्घ) MAX_SRBS;
	पूर्ण
	वापस srb;
पूर्ण

/**
 * qla4xxx_eh_रुको_on_command - रुकोs क्रम command to be वापसed by firmware
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @cmd: Scsi Command to रुको on.
 *
 * This routine रुकोs क्रम the command to be वापसed by the Firmware
 * क्रम some max समय.
 **/
अटल पूर्णांक qla4xxx_eh_रुको_on_command(काष्ठा scsi_qla_host *ha,
				      काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक करोne = 0;
	काष्ठा srb *rp;
	uपूर्णांक32_t max_रुको_समय = EH_WAIT_CMD_TOV;
	पूर्णांक ret = SUCCESS;

	/* Dont रुको on command अगर PCI error is being handled
	 * by PCI AER driver
	 */
	अगर (unlikely(pci_channel_offline(ha->pdev)) ||
	    (test_bit(AF_EEH_BUSY, &ha->flags))) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: Return from %s\n",
		    ha->host_no, __func__);
		वापस ret;
	पूर्ण

	करो अणु
		/* Checking to see अगर its वापसed to OS */
		rp = (काष्ठा srb *) CMD_SP(cmd);
		अगर (rp == शून्य) अणु
			करोne++;
			अवरोध;
		पूर्ण

		msleep(2000);
	पूर्ण जबतक (max_रुको_समय--);

	वापस करोne;
पूर्ण

/**
 * qla4xxx_रुको_क्रम_hba_online - रुकोs क्रम HBA to come online
 * @ha: Poपूर्णांकer to host adapter काष्ठाure
 **/
अटल पूर्णांक qla4xxx_रुको_क्रम_hba_online(काष्ठा scsi_qla_host *ha)
अणु
	अचिन्हित दीर्घ रुको_online;

	रुको_online = jअगरfies + (HBA_ONLINE_TOV * HZ);
	जबतक (समय_beक्रमe(jअगरfies, रुको_online)) अणु

		अगर (adapter_up(ha))
			वापस QLA_SUCCESS;

		msleep(2000);
	पूर्ण

	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_eh_रुको_क्रम_commands - रुको क्रम active cmds to finish.
 * @ha: poपूर्णांकer to HBA
 * @stgt: poपूर्णांकer to SCSI target
 * @sdev: poपूर्णांकer to SCSI device
 *
 * This function रुकोs क्रम all outstanding commands to a lun to complete. It
 * वापसs 0 अगर all pending commands are वापसed and 1 otherwise.
 **/
अटल पूर्णांक qla4xxx_eh_रुको_क्रम_commands(काष्ठा scsi_qla_host *ha,
					काष्ठा scsi_target *stgt,
					काष्ठा scsi_device *sdev)
अणु
	पूर्णांक cnt;
	पूर्णांक status = 0;
	काष्ठा scsi_cmnd *cmd;

	/*
	 * Waiting क्रम all commands क्रम the designated target or dev
	 * in the active array
	 */
	क्रम (cnt = 0; cnt < ha->host->can_queue; cnt++) अणु
		cmd = scsi_host_find_tag(ha->host, cnt);
		अगर (cmd && stgt == scsi_target(cmd->device) &&
		    (!sdev || sdev == cmd->device)) अणु
			अगर (!qla4xxx_eh_रुको_on_command(ha, cmd)) अणु
				status++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla4xxx_eh_पात - callback क्रम पात task.
 * @cmd: Poपूर्णांकer to Linux's SCSI command काष्ठाure
 *
 * This routine is called by the Linux OS to पात the specअगरied
 * command.
 **/
अटल पूर्णांक qla4xxx_eh_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(cmd->device->host);
	अचिन्हित पूर्णांक id = cmd->device->id;
	uपूर्णांक64_t lun = cmd->device->lun;
	अचिन्हित दीर्घ flags;
	काष्ठा srb *srb = शून्य;
	पूर्णांक ret = SUCCESS;
	पूर्णांक रुको = 0;
	पूर्णांक rval;

	ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld:%d:%llu: Abort command issued cmd=%p, cdb=0x%x\n",
		   ha->host_no, id, lun, cmd, cmd->cmnd[0]);

	rval = qla4xxx_isp_check_reg(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "PCI/Register disconnect, exiting.\n");
		वापस FAILED;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);
	srb = (काष्ठा srb *) CMD_SP(cmd);
	अगर (!srb) अणु
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld:%d:%llu: Specified command has already completed.\n",
			   ha->host_no, id, lun);
		वापस SUCCESS;
	पूर्ण
	kref_get(&srb->srb_ref);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (qla4xxx_पात_task(ha, srb) != QLA_SUCCESS) अणु
		DEBUG3(prपूर्णांकk("scsi%ld:%d:%llu: Abort_task mbx failed.\n",
		    ha->host_no, id, lun));
		ret = FAILED;
	पूर्ण अन्यथा अणु
		DEBUG3(prपूर्णांकk("scsi%ld:%d:%llu: Abort_task mbx success.\n",
		    ha->host_no, id, lun));
		रुको = 1;
	पूर्ण

	kref_put(&srb->srb_ref, qla4xxx_srb_compl);

	/* Wait क्रम command to complete */
	अगर (रुको) अणु
		अगर (!qla4xxx_eh_रुको_on_command(ha, cmd)) अणु
			DEBUG2(prपूर्णांकk("scsi%ld:%d:%llu: Abort handler timed out\n",
			    ha->host_no, id, lun));
			ret = FAILED;
		पूर्ण
	पूर्ण

	ql4_prपूर्णांकk(KERN_INFO, ha,
	    "scsi%ld:%d:%llu: Abort command - %s\n",
	    ha->host_no, id, lun, (ret == SUCCESS) ? "succeeded" : "failed");

	वापस ret;
पूर्ण

/**
 * qla4xxx_eh_device_reset - callback क्रम target reset.
 * @cmd: Poपूर्णांकer to Linux's SCSI command काष्ठाure
 *
 * This routine is called by the Linux OS to reset all luns on the
 * specअगरied target.
 **/
अटल पूर्णांक qla4xxx_eh_device_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(cmd->device->host);
	काष्ठा ddb_entry *ddb_entry = cmd->device->hostdata;
	पूर्णांक ret = FAILED, stat;
	पूर्णांक rval;

	अगर (!ddb_entry)
		वापस ret;

	ret = iscsi_block_scsi_eh(cmd);
	अगर (ret)
		वापस ret;
	ret = FAILED;

	ql4_prपूर्णांकk(KERN_INFO, ha,
		   "scsi%ld:%d:%d:%llu: DEVICE RESET ISSUED.\n", ha->host_no,
		   cmd->device->channel, cmd->device->id, cmd->device->lun);

	DEBUG2(prपूर्णांकk(KERN_INFO
		      "scsi%ld: DEVICE_RESET cmd=%p jiffies = 0x%lx, to=%x,"
		      "dpc_flags=%lx, status=%x allowed=%d\n", ha->host_no,
		      cmd, jअगरfies, cmd->request->समयout / HZ,
		      ha->dpc_flags, cmd->result, cmd->allowed));

	rval = qla4xxx_isp_check_reg(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "PCI/Register disconnect, exiting.\n");
		वापस FAILED;
	पूर्ण

	/* FIXME: रुको क्रम hba to go online */
	stat = qla4xxx_reset_lun(ha, ddb_entry, cmd->device->lun);
	अगर (stat != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "DEVICE RESET FAILED. %d\n", stat);
		जाओ eh_dev_reset_करोne;
	पूर्ण

	अगर (qla4xxx_eh_रुको_क्रम_commands(ha, scsi_target(cmd->device),
					 cmd->device)) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "DEVICE RESET FAILED - waiting for "
			   "commands.\n");
		जाओ eh_dev_reset_करोne;
	पूर्ण

	/* Send marker. */
	अगर (qla4xxx_send_marker_iocb(ha, ddb_entry, cmd->device->lun,
		MM_LUN_RESET) != QLA_SUCCESS)
		जाओ eh_dev_reset_करोne;

	ql4_prपूर्णांकk(KERN_INFO, ha,
		   "scsi(%ld:%d:%d:%llu): DEVICE RESET SUCCEEDED.\n",
		   ha->host_no, cmd->device->channel, cmd->device->id,
		   cmd->device->lun);

	ret = SUCCESS;

eh_dev_reset_करोne:

	वापस ret;
पूर्ण

/**
 * qla4xxx_eh_target_reset - callback क्रम target reset.
 * @cmd: Poपूर्णांकer to Linux's SCSI command काष्ठाure
 *
 * This routine is called by the Linux OS to reset the target.
 **/
अटल पूर्णांक qla4xxx_eh_target_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(cmd->device->host);
	काष्ठा ddb_entry *ddb_entry = cmd->device->hostdata;
	पूर्णांक stat, ret;
	पूर्णांक rval;

	अगर (!ddb_entry)
		वापस FAILED;

	ret = iscsi_block_scsi_eh(cmd);
	अगर (ret)
		वापस ret;

	starget_prपूर्णांकk(KERN_INFO, scsi_target(cmd->device),
		       "WARM TARGET RESET ISSUED.\n");

	DEBUG2(prपूर्णांकk(KERN_INFO
		      "scsi%ld: TARGET_DEVICE_RESET cmd=%p jiffies = 0x%lx, "
		      "to=%x,dpc_flags=%lx, status=%x allowed=%d\n",
		      ha->host_no, cmd, jअगरfies, cmd->request->समयout / HZ,
		      ha->dpc_flags, cmd->result, cmd->allowed));

	rval = qla4xxx_isp_check_reg(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "PCI/Register disconnect, exiting.\n");
		वापस FAILED;
	पूर्ण

	stat = qla4xxx_reset_target(ha, ddb_entry);
	अगर (stat != QLA_SUCCESS) अणु
		starget_prपूर्णांकk(KERN_INFO, scsi_target(cmd->device),
			       "WARM TARGET RESET FAILED.\n");
		वापस FAILED;
	पूर्ण

	अगर (qla4xxx_eh_रुको_क्रम_commands(ha, scsi_target(cmd->device),
					 शून्य)) अणु
		starget_prपूर्णांकk(KERN_INFO, scsi_target(cmd->device),
			       "WARM TARGET DEVICE RESET FAILED - "
			       "waiting for commands.\n");
		वापस FAILED;
	पूर्ण

	/* Send marker. */
	अगर (qla4xxx_send_marker_iocb(ha, ddb_entry, cmd->device->lun,
		MM_TGT_WARM_RESET) != QLA_SUCCESS) अणु
		starget_prपूर्णांकk(KERN_INFO, scsi_target(cmd->device),
			       "WARM TARGET DEVICE RESET FAILED - "
			       "marker iocb failed.\n");
		वापस FAILED;
	पूर्ण

	starget_prपूर्णांकk(KERN_INFO, scsi_target(cmd->device),
		       "WARM TARGET RESET SUCCEEDED.\n");
	वापस SUCCESS;
पूर्ण

/**
 * qla4xxx_is_eh_active - check अगर error handler is running
 * @shost: Poपूर्णांकer to SCSI Host काष्ठा
 *
 * This routine finds that अगर reset host is called in EH
 * scenario or from some application like sg_reset
 **/
अटल पूर्णांक qla4xxx_is_eh_active(काष्ठा Scsi_Host *shost)
अणु
	अगर (shost->shost_state == SHOST_RECOVERY)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * qla4xxx_eh_host_reset - kernel callback
 * @cmd: Poपूर्णांकer to Linux's SCSI command काष्ठाure
 *
 * This routine is invoked by the Linux kernel to perक्रमm fatal error
 * recovery on the specअगरied adapter.
 **/
अटल पूर्णांक qla4xxx_eh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक वापस_status = FAILED;
	काष्ठा scsi_qla_host *ha;
	पूर्णांक rval;

	ha = to_qla_host(cmd->device->host);

	rval = qla4xxx_isp_check_reg(ha);
	अगर (rval != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "PCI/Register disconnect, exiting.\n");
		वापस FAILED;
	पूर्ण

	अगर ((is_qla8032(ha) || is_qla8042(ha)) && ql4xकरोntresethba)
		qla4_83xx_set_idc_करोntreset(ha);

	/*
	 * For ISP8324 and ISP8042, अगर IDC_CTRL DONTRESET_BIT0 is set by other
	 * protocol drivers, we should not set device_state to NEED_RESET
	 */
	अगर (ql4xकरोntresethba ||
	    ((is_qla8032(ha) || is_qla8042(ha)) &&
	     qla4_83xx_idc_करोntreset(ha))) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Don't Reset HBA\n",
		     ha->host_no, __func__));

		/* Clear outstanding srb in queues */
		अगर (qla4xxx_is_eh_active(cmd->device->host))
			qla4xxx_पात_active_cmds(ha, DID_ABORT << 16);

		वापस FAILED;
	पूर्ण

	ql4_prपूर्णांकk(KERN_INFO, ha,
		   "scsi(%ld:%d:%d:%llu): HOST RESET ISSUED.\n", ha->host_no,
		   cmd->device->channel, cmd->device->id, cmd->device->lun);

	अगर (qla4xxx_रुको_क्रम_hba_online(ha) != QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld:%d: %s: Unable to reset host.  Adapter "
			      "DEAD.\n", ha->host_no, cmd->device->channel,
			      __func__));

		वापस FAILED;
	पूर्ण

	अगर (!test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु
		अगर (is_qla80XX(ha))
			set_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags);
		अन्यथा
			set_bit(DPC_RESET_HA, &ha->dpc_flags);
	पूर्ण

	अगर (qla4xxx_recover_adapter(ha) == QLA_SUCCESS)
		वापस_status = SUCCESS;

	ql4_prपूर्णांकk(KERN_INFO, ha, "HOST RESET %s.\n",
		   वापस_status == FAILED ? "FAILED" : "SUCCEEDED");

	वापस वापस_status;
पूर्ण

अटल पूर्णांक qla4xxx_context_reset(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा addr_ctrl_blk_def *acb = शून्य;
	uपूर्णांक32_t acb_len = माप(काष्ठा addr_ctrl_blk_def);
	पूर्णांक rval = QLA_SUCCESS;
	dma_addr_t acb_dma;

	acb = dma_alloc_coherent(&ha->pdev->dev,
				 माप(काष्ठा addr_ctrl_blk_def),
				 &acb_dma, GFP_KERNEL);
	अगर (!acb) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unable to alloc acb\n",
			   __func__);
		rval = -ENOMEM;
		जाओ निकास_port_reset;
	पूर्ण

	स_रखो(acb, 0, acb_len);

	rval = qla4xxx_get_acb(ha, acb_dma, PRIMARI_ACB, acb_len);
	अगर (rval != QLA_SUCCESS) अणु
		rval = -EIO;
		जाओ निकास_मुक्त_acb;
	पूर्ण

	rval = qla4xxx_disable_acb(ha);
	अगर (rval != QLA_SUCCESS) अणु
		rval = -EIO;
		जाओ निकास_मुक्त_acb;
	पूर्ण

	रुको_क्रम_completion_समयout(&ha->disable_acb_comp,
				    DISABLE_ACB_TOV * HZ);

	rval = qla4xxx_set_acb(ha, &mbox_cmd[0], &mbox_sts[0], acb_dma);
	अगर (rval != QLA_SUCCESS) अणु
		rval = -EIO;
		जाओ निकास_मुक्त_acb;
	पूर्ण

निकास_मुक्त_acb:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा addr_ctrl_blk_def),
			  acb, acb_dma);
निकास_port_reset:
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s %s\n", __func__,
			  rval == QLA_SUCCESS ? "SUCCEEDED" : "FAILED"));
	वापस rval;
पूर्ण

अटल पूर्णांक qla4xxx_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type)
अणु
	काष्ठा scsi_qla_host *ha = to_qla_host(shost);
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t idc_ctrl;

	अगर (ql4xकरोntresethba) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Don't Reset HBA\n",
				  __func__));
		rval = -EPERM;
		जाओ निकास_host_reset;
	पूर्ण

	अगर (test_bit(DPC_RESET_HA, &ha->dpc_flags))
		जाओ recover_adapter;

	चयन (reset_type) अणु
	हाल SCSI_ADAPTER_RESET:
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
		अवरोध;
	हाल SCSI_FIRMWARE_RESET:
		अगर (!test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु
			अगर (is_qla80XX(ha))
				/* set firmware context reset */
				set_bit(DPC_RESET_HA_FW_CONTEXT,
					&ha->dpc_flags);
			अन्यथा अणु
				rval = qla4xxx_context_reset(ha);
				जाओ निकास_host_reset;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

recover_adapter:
	/* For ISP8324 and ISP8042 set graceful reset bit in IDC_DRV_CTRL अगर
	 * reset is issued by application */
	अगर ((is_qla8032(ha) || is_qla8042(ha)) &&
	    test_bit(DPC_RESET_HA, &ha->dpc_flags)) अणु
		idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
		qla4_83xx_wr_reg(ha, QLA83XX_IDC_DRV_CTRL,
				 (idc_ctrl | GRACEFUL_RESET_BIT1));
	पूर्ण

	rval = qla4xxx_recover_adapter(ha);
	अगर (rval != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: recover adapter fail\n",
				  __func__));
		rval = -EIO;
	पूर्ण

निकास_host_reset:
	वापस rval;
पूर्ण

/* PCI AER driver recovers from all correctable errors w/o
 * driver पूर्णांकervention. For uncorrectable errors PCI AER
 * driver calls the following device driver's callbacks
 *
 * - Fatal Errors - link_reset
 * - Non-Fatal Errors - driver's error_detected() which
 * वापसs CAN_RECOVER, NEED_RESET or DISCONNECT.
 *
 * PCI AER driver calls
 * CAN_RECOVER - driver's mmio_enabled(), mmio_enabled()
 *               वापसs RECOVERED or NEED_RESET अगर fw_hung
 * NEED_RESET - driver's slot_reset()
 * DISCONNECT - device is dead & cannot recover
 * RECOVERED - driver's resume()
 */
अटल pci_ers_result_t
qla4xxx_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा scsi_qla_host *ha = pci_get_drvdata(pdev);

	ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: error detected:state %x\n",
	    ha->host_no, __func__, state);

	अगर (!is_aer_supported(ha))
		वापस PCI_ERS_RESULT_NONE;

	चयन (state) अणु
	हाल pci_channel_io_normal:
		clear_bit(AF_EEH_BUSY, &ha->flags);
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_frozen:
		set_bit(AF_EEH_BUSY, &ha->flags);
		qla4xxx_mailbox_premature_completion(ha);
		qla4xxx_मुक्त_irqs(ha);
		pci_disable_device(pdev);
		/* Return back all IOs */
		qla4xxx_पात_active_cmds(ha, DID_RESET << 16);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		set_bit(AF_EEH_BUSY, &ha->flags);
		set_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags);
		qla4xxx_पात_active_cmds(ha, DID_NO_CONNECT << 16);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * qla4xxx_pci_mmio_enabled() - माला_लो called अगर
 * qla4xxx_pci_error_detected() वापसs PCI_ERS_RESULT_CAN_RECOVER
 * and पढ़ो/ग_लिखो to the device still works.
 * @pdev: PCI device poपूर्णांकer
 **/
अटल pci_ers_result_t
qla4xxx_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	काष्ठा scsi_qla_host *ha = pci_get_drvdata(pdev);

	अगर (!is_aer_supported(ha))
		वापस PCI_ERS_RESULT_NONE;

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल uपूर्णांक32_t qla4_8xxx_error_recovery(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t rval = QLA_ERROR;
	पूर्णांक fn;
	काष्ठा pci_dev *other_pdev = शून्य;

	ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: In %s\n", ha->host_no, __func__);

	set_bit(DPC_RESET_ACTIVE, &ha->dpc_flags);

	अगर (test_bit(AF_ONLINE, &ha->flags)) अणु
		clear_bit(AF_ONLINE, &ha->flags);
		clear_bit(AF_LINK_UP, &ha->flags);
		iscsi_host_क्रम_each_session(ha->host, qla4xxx_fail_session);
		qla4xxx_process_aen(ha, FLUSH_DDB_CHANGED_AENS);
	पूर्ण

	fn = PCI_FUNC(ha->pdev->devfn);
	अगर (is_qla8022(ha)) अणु
		जबतक (fn > 0) अणु
			fn--;
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: Finding PCI device at func %x\n",
				   ha->host_no, __func__, fn);
			/* Get the pci device given the करोमुख्य, bus,
			 * slot/function number */
			other_pdev = pci_get_करोमुख्य_bus_and_slot(
					   pci_करोमुख्य_nr(ha->pdev->bus),
					   ha->pdev->bus->number,
					   PCI_DEVFN(PCI_SLOT(ha->pdev->devfn),
					   fn));

			अगर (!other_pdev)
				जारी;

			अगर (atomic_पढ़ो(&other_pdev->enable_cnt)) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: Found PCI func in enabled state%x\n",
					   ha->host_no, __func__, fn);
				pci_dev_put(other_pdev);
				अवरोध;
			पूर्ण
			pci_dev_put(other_pdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this हाल is meant क्रम ISP83xx/ISP84xx only */
		अगर (qla4_83xx_can_perक्रमm_reset(ha)) अणु
			/* reset fn as iSCSI is going to perक्रमm the reset */
			fn = 0;
		पूर्ण
	पूर्ण

	/* The first function on the card, the reset owner will
	 * start & initialize the firmware. The other functions
	 * on the card will reset the firmware context
	 */
	अगर (!fn) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: devfn being reset "
		    "0x%x is the owner\n", ha->host_no, __func__,
		    ha->pdev->devfn);

		ha->isp_ops->idc_lock(ha);
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
				    QLA8XXX_DEV_COLD);
		ha->isp_ops->idc_unlock(ha);

		rval = qla4_8xxx_update_idc_reg(ha);
		अगर (rval == QLA_ERROR) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: HW State: FAILED\n",
				   ha->host_no, __func__);
			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
			ha->isp_ops->idc_unlock(ha);
			जाओ निकास_error_recovery;
		पूर्ण

		clear_bit(AF_FW_RECOVERY, &ha->flags);
		rval = qla4xxx_initialize_adapter(ha, RESET_ADAPTER);

		अगर (rval != QLA_SUCCESS) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: HW State: "
			    "FAILED\n", ha->host_no, __func__);
			qla4xxx_मुक्त_irqs(ha);
			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_clear_drv_active(ha);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
			ha->isp_ops->idc_unlock(ha);
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: HW State: "
			    "READY\n", ha->host_no, __func__);
			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_READY);
			/* Clear driver state रेजिस्टर */
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_STATE, 0);
			qla4_8xxx_set_drv_active(ha);
			ha->isp_ops->idc_unlock(ha);
			ha->isp_ops->enable_पूर्णांकrs(ha);
		पूर्ण
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: devfn 0x%x is not "
		    "the reset owner\n", ha->host_no, __func__,
		    ha->pdev->devfn);
		अगर ((qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE) ==
		     QLA8XXX_DEV_READY)) अणु
			clear_bit(AF_FW_RECOVERY, &ha->flags);
			rval = qla4xxx_initialize_adapter(ha, RESET_ADAPTER);
			अगर (rval == QLA_SUCCESS)
				ha->isp_ops->enable_पूर्णांकrs(ha);
			अन्यथा
				qla4xxx_मुक्त_irqs(ha);

			ha->isp_ops->idc_lock(ha);
			qla4_8xxx_set_drv_active(ha);
			ha->isp_ops->idc_unlock(ha);
		पूर्ण
	पूर्ण
निकास_error_recovery:
	clear_bit(DPC_RESET_ACTIVE, &ha->dpc_flags);
	वापस rval;
पूर्ण

अटल pci_ers_result_t
qla4xxx_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t ret = PCI_ERS_RESULT_DISCONNECT;
	काष्ठा scsi_qla_host *ha = pci_get_drvdata(pdev);
	पूर्णांक rc;

	ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: slot_reset\n",
	    ha->host_no, __func__);

	अगर (!is_aer_supported(ha))
		वापस PCI_ERS_RESULT_NONE;

	/* Restore the saved state of PCIe device -
	 * BAR रेजिस्टरs, PCI Config space, PCIX, MSI,
	 * IOV states
	 */
	pci_restore_state(pdev);

	/* pci_restore_state() clears the saved_state flag of the device
	 * save restored state which resets saved_state flag
	 */
	pci_save_state(pdev);

	/* Initialize device or resume अगर in suspended state */
	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: Can't re-enable "
		    "device after reset\n", ha->host_no, __func__);
		जाओ निकास_slot_reset;
	पूर्ण

	ha->isp_ops->disable_पूर्णांकrs(ha);

	अगर (is_qla80XX(ha)) अणु
		अगर (qla4_8xxx_error_recovery(ha) == QLA_SUCCESS) अणु
			ret = PCI_ERS_RESULT_RECOVERED;
			जाओ निकास_slot_reset;
		पूर्ण अन्यथा
			जाओ निकास_slot_reset;
	पूर्ण

निकास_slot_reset:
	ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: Return=%x\n"
	    "device after reset\n", ha->host_no, __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम
qla4xxx_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा scsi_qla_host *ha = pci_get_drvdata(pdev);
	पूर्णांक ret;

	ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: pci_resume\n",
	    ha->host_no, __func__);

	ret = qla4xxx_रुको_क्रम_hba_online(ha);
	अगर (ret != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: the device failed to "
		    "resume I/O from slot/link_reset\n", ha->host_no,
		     __func__);
	पूर्ण

	clear_bit(AF_EEH_BUSY, &ha->flags);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers qla4xxx_err_handler = अणु
	.error_detected = qla4xxx_pci_error_detected,
	.mmio_enabled = qla4xxx_pci_mmio_enabled,
	.slot_reset = qla4xxx_pci_slot_reset,
	.resume = qla4xxx_pci_resume,
पूर्ण;

अटल काष्ठा pci_device_id qla4xxx_pci_tbl[] = अणु
	अणु
		.venकरोr		= PCI_VENDOR_ID_QLOGIC,
		.device		= PCI_DEVICE_ID_QLOGIC_ISP4010,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_QLOGIC,
		.device		= PCI_DEVICE_ID_QLOGIC_ISP4022,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_QLOGIC,
		.device		= PCI_DEVICE_ID_QLOGIC_ISP4032,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr         = PCI_VENDOR_ID_QLOGIC,
		.device         = PCI_DEVICE_ID_QLOGIC_ISP8022,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_QLOGIC,
		.device		= PCI_DEVICE_ID_QLOGIC_ISP8324,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_QLOGIC,
		.device		= PCI_DEVICE_ID_QLOGIC_ISP8042,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, qla4xxx_pci_tbl);

अटल काष्ठा pci_driver qla4xxx_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= qla4xxx_pci_tbl,
	.probe		= qla4xxx_probe_adapter,
	.हटाओ		= qla4xxx_हटाओ_adapter,
	.err_handler = &qla4xxx_err_handler,
पूर्ण;

अटल पूर्णांक __init qla4xxx_module_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (ql4xqfulltracking)
		qla4xxx_driver_ढाँचा.track_queue_depth = 1;

	/* Allocate cache क्रम SRBs. */
	srb_cachep = kmem_cache_create("qla4xxx_srbs", माप(काष्ठा srb), 0,
				       SLAB_HWCACHE_ALIGN, शून्य);
	अगर (srb_cachep == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: Unable to allocate SRB cache..."
		       "Failing load!\n", DRIVER_NAME);
		ret = -ENOMEM;
		जाओ no_srp_cache;
	पूर्ण

	/* Derive version string. */
	म_नकल(qla4xxx_version_str, QLA4XXX_DRIVER_VERSION);
	अगर (ql4xextended_error_logging)
		म_जोड़ो(qla4xxx_version_str, "-debug");

	qla4xxx_scsi_transport =
		iscsi_रेजिस्टर_transport(&qla4xxx_iscsi_transport);
	अगर (!qla4xxx_scsi_transport)अणु
		ret = -ENODEV;
		जाओ release_srb_cache;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&qla4xxx_pci_driver);
	अगर (ret)
		जाओ unरेजिस्टर_transport;

	prपूर्णांकk(KERN_INFO "QLogic iSCSI HBA Driver\n");
	वापस 0;

unरेजिस्टर_transport:
	iscsi_unरेजिस्टर_transport(&qla4xxx_iscsi_transport);
release_srb_cache:
	kmem_cache_destroy(srb_cachep);
no_srp_cache:
	वापस ret;
पूर्ण

अटल व्योम __निकास qla4xxx_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qla4xxx_pci_driver);
	iscsi_unरेजिस्टर_transport(&qla4xxx_iscsi_transport);
	kmem_cache_destroy(srb_cachep);
पूर्ण

module_init(qla4xxx_module_init);
module_निकास(qla4xxx_module_निकास);

MODULE_AUTHOR("QLogic Corporation");
MODULE_DESCRIPTION("QLogic iSCSI HBA Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(QLA4XXX_DRIVER_VERSION);
