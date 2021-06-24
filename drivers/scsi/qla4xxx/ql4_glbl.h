<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#अगर_अघोषित __QLA4x_GBL_H
#घोषणा	__QLA4x_GBL_H

काष्ठा iscsi_cls_conn;

पूर्णांक qla4xxx_hw_reset(काष्ठा scsi_qla_host *ha);
पूर्णांक ql4xxx_lock_drvr_रुको(काष्ठा scsi_qla_host *a);
पूर्णांक qla4xxx_send_command_to_isp(काष्ठा scsi_qla_host *ha, काष्ठा srb *srb);
पूर्णांक qla4xxx_initialize_adapter(काष्ठा scsi_qla_host *ha, पूर्णांक is_reset);
पूर्णांक qla4xxx_soft_reset(काष्ठा scsi_qla_host *ha);
irqवापस_t qla4xxx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id);

व्योम qla4xxx_मुक्त_ddb(काष्ठा scsi_qla_host *ha, काष्ठा ddb_entry *ddb_entry);
व्योम qla4xxx_process_aen(काष्ठा scsi_qla_host *ha, uपूर्णांक8_t process_aen);

पूर्णांक qla4xxx_get_dhcp_ip_address(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_पात_task(काष्ठा scsi_qla_host *ha, काष्ठा srb *srb);
पूर्णांक qla4xxx_reset_lun(काष्ठा scsi_qla_host *ha, काष्ठा ddb_entry *ddb_entry,
		      uपूर्णांक64_t lun);
पूर्णांक qla4xxx_reset_target(काष्ठा scsi_qla_host *ha,
			 काष्ठा ddb_entry *ddb_entry);
पूर्णांक qla4xxx_get_flash(काष्ठा scsi_qla_host *ha, dma_addr_t dma_addr,
		      uपूर्णांक32_t offset, uपूर्णांक32_t len);
पूर्णांक qla4xxx_get_firmware_status(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_get_firmware_state(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_initialize_fw_cb(काष्ठा scsi_qla_host *ha);

/* FIXME: Goodness!  this really wants a small काष्ठा to hold the
 * parameters. On x86 the args will get passed on the stack! */
पूर्णांक qla4xxx_get_fwddb_entry(काष्ठा scsi_qla_host *ha,
			    uपूर्णांक16_t fw_ddb_index,
			    काष्ठा dev_db_entry *fw_ddb_entry,
			    dma_addr_t fw_ddb_entry_dma,
			    uपूर्णांक32_t *num_valid_ddb_entries,
			    uपूर्णांक32_t *next_ddb_index,
			    uपूर्णांक32_t *fw_ddb_device_state,
			    uपूर्णांक32_t *conn_err_detail,
			    uपूर्णांक16_t *tcp_source_port_num,
			    uपूर्णांक16_t *connection_id);

पूर्णांक qla4xxx_set_ddb_entry(काष्ठा scsi_qla_host * ha, uपूर्णांक16_t fw_ddb_index,
			  dma_addr_t fw_ddb_entry_dma, uपूर्णांक32_t *mbx_sts);
uपूर्णांक8_t qla4xxx_get_अगरcb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
			 uपूर्णांक32_t *mbox_sts, dma_addr_t init_fw_cb_dma);
पूर्णांक qla4xxx_conn_बंद_sess_logout(काष्ठा scsi_qla_host *ha,
				   uपूर्णांक16_t fw_ddb_index,
				   uपूर्णांक16_t connection_id,
				   uपूर्णांक16_t option);
पूर्णांक qla4xxx_disable_acb(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_set_acb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
		    uपूर्णांक32_t *mbox_sts, dma_addr_t acb_dma);
पूर्णांक qla4xxx_get_acb(काष्ठा scsi_qla_host *ha, dma_addr_t acb_dma,
		    uपूर्णांक32_t acb_type, uपूर्णांक32_t len);
पूर्णांक qla4xxx_get_ip_state(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t acb_idx,
			 uपूर्णांक32_t ip_idx, uपूर्णांक32_t *sts);
व्योम qla4xxx_mark_device_missing(काष्ठा iscsi_cls_session *cls_session);
u16 rd_nvram_word(काष्ठा scsi_qla_host *ha, पूर्णांक offset);
u8 rd_nvram_byte(काष्ठा scsi_qla_host *ha, पूर्णांक offset);
व्योम qla4xxx_get_crash_record(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_is_nvram_configuration_valid(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_about_firmware(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host *ha,
				       uपूर्णांक32_t पूर्णांकr_status);
पूर्णांक qla4xxx_init_rings(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_srb_compl(काष्ठा kref *ref);
काष्ठा srb *qla4xxx_del_from_active_array(काष्ठा scsi_qla_host *ha,
		uपूर्णांक32_t index);
पूर्णांक qla4xxx_process_ddb_changed(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
		uपूर्णांक32_t state, uपूर्णांक32_t conn_error);
व्योम qla4xxx_dump_buffer(व्योम *b, uपूर्णांक32_t size);
पूर्णांक qla4xxx_send_marker_iocb(काष्ठा scsi_qla_host *ha,
	काष्ठा ddb_entry *ddb_entry, uपूर्णांक64_t lun, uपूर्णांक16_t mrkr_mod);
पूर्णांक qla4xxx_set_flash(काष्ठा scsi_qla_host *ha, dma_addr_t dma_addr,
		      uपूर्णांक32_t offset, uपूर्णांक32_t length, uपूर्णांक32_t options);
पूर्णांक qla4xxx_mailbox_command(काष्ठा scsi_qla_host *ha, uपूर्णांक8_t inCount,
		uपूर्णांक8_t outCount, uपूर्णांक32_t *mbx_cmd, uपूर्णांक32_t *mbx_sts);
पूर्णांक qla4xxx_get_chap_index(काष्ठा scsi_qla_host *ha, अक्षर *username,
			   अक्षर *password, पूर्णांक bidi, uपूर्णांक16_t *chap_index);
पूर्णांक qla4xxx_set_chap(काष्ठा scsi_qla_host *ha, अक्षर *username, अक्षर *password,
		     uपूर्णांक16_t idx, पूर्णांक bidi);

व्योम qla4xxx_queue_iocb(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_complete_iocb(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_get_sys_info(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_iospace_config(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_pci_config(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_start_firmware(काष्ठा scsi_qla_host *ha);
irqवापस_t qla4xxx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id);
uपूर्णांक16_t qla4xxx_rd_shdw_req_q_out(काष्ठा scsi_qla_host *ha);
uपूर्णांक16_t qla4xxx_rd_shdw_rsp_q_in(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_request_irqs(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_मुक्त_irqs(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_process_response_queue(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_wake_dpc(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_get_conn_event_log(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_mailbox_premature_completion(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_dump_रेजिस्टरs(काष्ठा scsi_qla_host *ha);
uपूर्णांक8_t qla4xxx_update_local_अगरcb(काष्ठा scsi_qla_host *ha,
				  uपूर्णांक32_t *mbox_cmd,
				  uपूर्णांक32_t *mbox_sts,
				  काष्ठा addr_ctrl_blk *init_fw_cb,
				  dma_addr_t init_fw_cb_dma);

व्योम qla4_8xxx_pci_config(काष्ठा scsi_qla_host *);
पूर्णांक qla4_8xxx_iospace_config(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_load_risc(काष्ठा scsi_qla_host *);
irqवापस_t qla4_82xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id);
व्योम qla4_82xx_queue_iocb(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_complete_iocb(काष्ठा scsi_qla_host *ha);

व्योम qla4_82xx_crb_win_unlock(काष्ठा scsi_qla_host *);
पूर्णांक qla4_82xx_pci_get_crb_addr_2M(काष्ठा scsi_qla_host *, uदीर्घ *);
व्योम qla4_82xx_wr_32(काष्ठा scsi_qla_host *, uदीर्घ, u32);
uपूर्णांक32_t qla4_82xx_rd_32(काष्ठा scsi_qla_host *, uदीर्घ);
पूर्णांक qla4_82xx_pci_mem_पढ़ो_2M(काष्ठा scsi_qla_host *, u64, व्योम *, पूर्णांक);
पूर्णांक qla4_82xx_pci_mem_ग_लिखो_2M(काष्ठा scsi_qla_host *ha, u64, व्योम *, पूर्णांक);
पूर्णांक qla4_82xx_isp_reset(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host *ha,
		uपूर्णांक32_t पूर्णांकr_status);
uपूर्णांक16_t qla4_82xx_rd_shdw_req_q_out(काष्ठा scsi_qla_host *ha);
uपूर्णांक16_t qla4_82xx_rd_shdw_rsp_q_in(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_get_sys_info(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_watchकरोg(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_stop_firmware(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_get_flash_info(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_enable_msix(काष्ठा scsi_qla_host *ha);
irqवापस_t qla4_8xxx_msi_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t qla4_8xxx_शेष_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t qla4_8xxx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id);
व्योम qla4xxx_mark_all_devices_missing(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_dead_adapter_cleanup(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_82xx_idc_lock(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_idc_unlock(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_device_state_handler(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_need_qsnt_handler(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_clear_drv_active(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_set_drv_active(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_conn_खोलो(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t fw_ddb_index);
पूर्णांक qla4xxx_set_param_ddbentry(काष्ठा scsi_qla_host *ha,
			       काष्ठा ddb_entry *ddb_entry,
			       काष्ठा iscsi_cls_conn *cls_conn,
			       uपूर्णांक32_t *mbx_sts);
पूर्णांक qla4xxx_session_logout_ddb(काष्ठा scsi_qla_host *ha,
			       काष्ठा ddb_entry *ddb_entry, पूर्णांक options);
पूर्णांक qla4xxx_req_ddb_entry(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
			  uपूर्णांक32_t *mbx_sts);
पूर्णांक qla4xxx_clear_ddb_entry(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index);
पूर्णांक qla4xxx_send_passthru0(काष्ठा iscsi_task *task);
व्योम qla4xxx_मुक्त_ddb_index(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_get_mgmt_data(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t fw_ddb_index,
			  uपूर्णांक16_t stats_size, dma_addr_t stats_dma);
व्योम qla4xxx_update_session_conn_param(काष्ठा scsi_qla_host *ha,
				       काष्ठा ddb_entry *ddb_entry);
व्योम qla4xxx_update_session_conn_fwddb_param(काष्ठा scsi_qla_host *ha,
					     काष्ठा ddb_entry *ddb_entry);
पूर्णांक qla4xxx_bootdb_by_index(काष्ठा scsi_qla_host *ha,
			    काष्ठा dev_db_entry *fw_ddb_entry,
			    dma_addr_t fw_ddb_entry_dma, uपूर्णांक16_t ddb_index);
पूर्णांक qla4xxx_get_chap(काष्ठा scsi_qla_host *ha, अक्षर *username,
		     अक्षर *password, uपूर्णांक16_t idx);
पूर्णांक qla4xxx_get_nvram(काष्ठा scsi_qla_host *ha, dma_addr_t nvram_dma,
		      uपूर्णांक32_t offset, uपूर्णांक32_t size);
पूर्णांक qla4xxx_set_nvram(काष्ठा scsi_qla_host *ha, dma_addr_t nvram_dma,
		      uपूर्णांक32_t offset, uपूर्णांक32_t size);
पूर्णांक qla4xxx_restore_factory_शेषs(काष्ठा scsi_qla_host *ha,
				     uपूर्णांक32_t region, uपूर्णांक32_t field0,
				     uपूर्णांक32_t field1);
पूर्णांक qla4xxx_get_ddb_index(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t *ddb_index);
व्योम qla4xxx_login_flash_ddb(काष्ठा iscsi_cls_session *cls_session);
पूर्णांक qla4xxx_unblock_ddb(काष्ठा iscsi_cls_session *cls_session);
पूर्णांक qla4xxx_unblock_flash_ddb(काष्ठा iscsi_cls_session *cls_session);
पूर्णांक qla4xxx_flash_ddb_change(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
			     काष्ठा ddb_entry *ddb_entry, uपूर्णांक32_t state);
पूर्णांक qla4xxx_ddb_change(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t fw_ddb_index,
		       काष्ठा ddb_entry *ddb_entry, uपूर्णांक32_t state);
व्योम qla4xxx_build_ddb_list(काष्ठा scsi_qla_host *ha, पूर्णांक is_reset);
पूर्णांक qla4xxx_post_aen_work(काष्ठा scsi_qla_host *ha,
			  क्रमागत iscsi_host_event_code aen_code,
			  uपूर्णांक32_t data_size, uपूर्णांक8_t *data);
पूर्णांक qla4xxx_ping_iocb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t options,
		      uपूर्णांक32_t payload_size, uपूर्णांक32_t pid, uपूर्णांक8_t *ipaddr);
पूर्णांक qla4xxx_post_ping_evt_work(काष्ठा scsi_qla_host *ha,
			       uपूर्णांक32_t status, uपूर्णांक32_t pid,
			       uपूर्णांक32_t data_size, uपूर्णांक8_t *data);
पूर्णांक qla4xxx_flashdb_by_index(काष्ठा scsi_qla_host *ha,
			     काष्ठा dev_db_entry *fw_ddb_entry,
			     dma_addr_t fw_ddb_entry_dma, uपूर्णांक16_t ddb_index);

/* BSG Functions */
पूर्णांक qla4xxx_bsg_request(काष्ठा bsg_job *bsg_job);
पूर्णांक qla4xxx_process_venकरोr_specअगरic(काष्ठा bsg_job *bsg_job);

व्योम qla4xxx_arm_relogin_समयr(काष्ठा ddb_entry *ddb_entry);
पूर्णांक qla4xxx_get_minidump_ढाँचा(काष्ठा scsi_qla_host *ha,
				  dma_addr_t phys_addr);
पूर्णांक qla4xxx_req_ढाँचा_size(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_alloc_sysfs_attr(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_मुक्त_sysfs_attr(काष्ठा scsi_qla_host *ha);
व्योम qla4xxx_alloc_fw_dump(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_82xx_try_start_fw(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_need_reset(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_82xx_md_rd_32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t off, uपूर्णांक32_t *data);
पूर्णांक qla4_82xx_md_wr_32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t off, uपूर्णांक32_t data);
व्योम qla4_82xx_rom_lock_recovery(काष्ठा scsi_qla_host *ha);
व्योम qla4_82xx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			      पूर्णांक incount);
व्योम qla4_82xx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक outcount);
व्योम qla4xxx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			    पूर्णांक incount);
व्योम qla4xxx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक outcount);
व्योम qla4_8xxx_dump_peg_reg(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_disable_पूर्णांकrs(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_enable_पूर्णांकrs(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_start_firmware(काष्ठा scsi_qla_host *ha);
irqवापस_t qla4_83xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id);
व्योम qla4_83xx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host *ha,
					 uपूर्णांक32_t पूर्णांकr_status);
पूर्णांक qla4_83xx_isp_reset(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_queue_iocb(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_complete_iocb(काष्ठा scsi_qla_host *ha);
uपूर्णांक32_t qla4_83xx_rd_reg(काष्ठा scsi_qla_host *ha, uदीर्घ addr);
व्योम qla4_83xx_wr_reg(काष्ठा scsi_qla_host *ha, uदीर्घ addr, uपूर्णांक32_t val);
पूर्णांक qla4_83xx_rd_reg_indirect(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr,
			      uपूर्णांक32_t *data);
पूर्णांक qla4_83xx_wr_reg_indirect(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t addr,
			      uपूर्णांक32_t data);
पूर्णांक qla4_83xx_drv_lock(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_drv_unlock(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_rom_lock_recovery(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			      पूर्णांक incount);
व्योम qla4_83xx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक outcount);
व्योम qla4_83xx_पढ़ो_reset_ढाँचा(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_set_idc_करोntreset(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_idc_करोntreset(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_lockless_flash_पढ़ो_u32(काष्ठा scsi_qla_host *ha,
				      uपूर्णांक32_t flash_addr, uपूर्णांक8_t *p_data,
				      पूर्णांक u32_word_count);
व्योम qla4_83xx_clear_idc_करोntreset(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_need_reset_handler(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_flash_पढ़ो_u32(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t flash_addr,
			     uपूर्णांक8_t *p_data, पूर्णांक u32_word_count);
व्योम qla4_83xx_get_idc_param(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_set_rst_पढ़ोy(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_clear_rst_पढ़ोy(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_device_bootstrap(काष्ठा scsi_qla_host *ha);
व्योम qla4_8xxx_get_minidump(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_पूर्णांकr_disable(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_पूर्णांकr_enable(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_8xxx_set_param(काष्ठा scsi_qla_host *ha, पूर्णांक param);
पूर्णांक qla4_8xxx_update_idc_reg(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_post_idc_ack(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_disable_छोड़ो(काष्ठा scsi_qla_host *ha);
व्योम qla4_83xx_enable_mbox_पूर्णांकrs(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_can_perक्रमm_reset(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_get_शेष_ddb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t options,
			    dma_addr_t dma_addr);
पूर्णांक qla4xxx_get_uni_chap_at_index(काष्ठा scsi_qla_host *ha, अक्षर *username,
				  अक्षर *password, uपूर्णांक16_t chap_index);
पूर्णांक qla4xxx_disable_acb(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_set_acb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
		    uपूर्णांक32_t *mbox_sts, dma_addr_t acb_dma);
पूर्णांक qla4xxx_get_acb(काष्ठा scsi_qla_host *ha, dma_addr_t acb_dma,
		    uपूर्णांक32_t acb_type, uपूर्णांक32_t len);
पूर्णांक qla4_84xx_config_acb(काष्ठा scsi_qla_host *ha, पूर्णांक acb_config);
पूर्णांक qla4_8xxx_ms_mem_ग_लिखो_128b(काष्ठा scsi_qla_host *ha,
				uपूर्णांक64_t addr, uपूर्णांक32_t *data, uपूर्णांक32_t count);
uपूर्णांक8_t qla4xxx_set_ipaddr_state(uपूर्णांक8_t fw_ipaddr_state);
पूर्णांक qla4_83xx_get_port_config(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *config);
पूर्णांक qla4_83xx_set_port_config(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *config);
पूर्णांक qla4_8xxx_check_init_adapter_retry(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4_83xx_is_detached(काष्ठा scsi_qla_host *ha);
पूर्णांक qla4xxx_sysfs_ddb_export(काष्ठा scsi_qla_host *ha);

बाह्य पूर्णांक ql4xextended_error_logging;
बाह्य पूर्णांक ql4xकरोntresethba;
बाह्य पूर्णांक ql4xenablemsix;
बाह्य पूर्णांक ql4xmdcapmask;
बाह्य पूर्णांक ql4xenablemd;

बाह्य काष्ठा device_attribute *qla4xxx_host_attrs[];
#पूर्ण_अगर /* _QLA4x_GBL_H */
