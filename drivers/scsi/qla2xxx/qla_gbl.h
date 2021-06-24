<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#अगर_अघोषित __QLA_GBL_H
#घोषणा	__QLA_GBL_H

#समावेश <linux/पूर्णांकerrupt.h>

/*
 * Global Function Prototypes in qla_init.c source file.
 */
बाह्य पूर्णांक qla2x00_initialize_adapter(scsi_qla_host_t *);

बाह्य पूर्णांक qla2100_pci_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla2300_pci_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_pci_config(scsi_qla_host_t *);
बाह्य पूर्णांक qla25xx_pci_config(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_reset_chip(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_reset_chip(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla2x00_chip_diag(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_chip_diag(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_config_rings(काष्ठा scsi_qla_host *);
बाह्य व्योम qla24xx_config_rings(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla2x00_reset_adapter(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_reset_adapter(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla2x00_nvram_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_nvram_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla81xx_nvram_config(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_update_fw_options(काष्ठा scsi_qla_host *);
बाह्य व्योम qla24xx_update_fw_options(scsi_qla_host_t *);

बाह्य पूर्णांक qla2x00_load_risc(काष्ठा scsi_qla_host *, uपूर्णांक32_t *);
बाह्य पूर्णांक qla24xx_load_risc(scsi_qla_host_t *, uपूर्णांक32_t *);
बाह्य पूर्णांक qla81xx_load_risc(scsi_qla_host_t *, uपूर्णांक32_t *);

बाह्य पूर्णांक qla2x00_perक्रमm_loop_resync(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_loop_resync(scsi_qla_host_t *);
बाह्य व्योम qla2x00_clear_loop_id(fc_port_t *fcport);

बाह्य पूर्णांक qla2x00_fabric_login(scsi_qla_host_t *, fc_port_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_local_device_login(scsi_qla_host_t *, fc_port_t *);

बाह्य पूर्णांक qla24xx_els_dcmd_iocb(scsi_qla_host_t *, पूर्णांक, port_id_t);
बाह्य पूर्णांक qla24xx_els_dcmd2_iocb(scsi_qla_host_t *, पूर्णांक, fc_port_t *, bool);
बाह्य व्योम qla2x00_els_dcmd2_मुक्त(scsi_qla_host_t *vha,
				   काष्ठा els_plogi *els_plogi);

बाह्य व्योम qla2x00_update_fcports(scsi_qla_host_t *);

बाह्य पूर्णांक qla2x00_पात_isp(scsi_qla_host_t *);
बाह्य व्योम qla2x00_पात_isp_cleanup(scsi_qla_host_t *);
बाह्य व्योम qla2x00_quiesce_io(scsi_qla_host_t *);

बाह्य व्योम qla2x00_update_fcport(scsi_qla_host_t *, fc_port_t *);
व्योम qla_रेजिस्टर_fcport_fn(काष्ठा work_काष्ठा *);
बाह्य व्योम qla2x00_alloc_fw_dump(scsi_qla_host_t *);
बाह्य व्योम qla2x00_try_to_stop_firmware(scsi_qla_host_t *);

बाह्य पूर्णांक qla2x00_get_thermal_temp(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य व्योम qla84xx_put_chip(काष्ठा scsi_qla_host *);

बाह्य पूर्णांक qla2x00_async_login(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_async_logout(काष्ठा scsi_qla_host *, fc_port_t *);
बाह्य पूर्णांक qla2x00_async_prlo(काष्ठा scsi_qla_host *, fc_port_t *);
बाह्य पूर्णांक qla2x00_async_adisc(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_async_पंचांग_cmd(fc_port_t *, uपूर्णांक32_t, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम qla2x00_async_login_करोne(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
काष्ठा qla_work_evt *qla2x00_alloc_work(काष्ठा scsi_qla_host *,
    क्रमागत qla_work_type);
बाह्य पूर्णांक qla24xx_async_gnl(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla2x00_post_work(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *e);
बाह्य व्योम *qla2x00_alloc_iocbs_पढ़ोy(काष्ठा qla_qpair *, srb_t *);
बाह्य पूर्णांक qla24xx_update_fcport_fcp_prio(scsi_qla_host_t *, fc_port_t *);
बाह्य पूर्णांक qla24xx_async_पात_cmd(srb_t *, bool);

बाह्य व्योम qla2x00_set_fcport_state(fc_port_t *fcport, पूर्णांक state);
बाह्य fc_port_t *
qla2x00_alloc_fcport(scsi_qla_host_t *, gfp_t );

बाह्य पूर्णांक __qla83xx_set_idc_control(scsi_qla_host_t *, uपूर्णांक32_t);
बाह्य पूर्णांक __qla83xx_get_idc_control(scsi_qla_host_t *, uपूर्णांक32_t *);
बाह्य व्योम qla83xx_idc_audit(scsi_qla_host_t *, पूर्णांक);
बाह्य पूर्णांक qla83xx_nic_core_reset(scsi_qla_host_t *);
बाह्य व्योम qla83xx_reset_ownership(scsi_qla_host_t *);
बाह्य पूर्णांक qla2xxx_mctp_dump(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_alloc_outstanding_cmds(काष्ठा qla_hw_data *, काष्ठा req_que *);
बाह्य पूर्णांक qla2x00_init_rings(scsi_qla_host_t *);
बाह्य काष्ठा qla_qpair *qla2xxx_create_qpair(काष्ठा scsi_qla_host *,
	पूर्णांक, पूर्णांक, bool);
बाह्य पूर्णांक qla2xxx_delete_qpair(काष्ठा scsi_qla_host *, काष्ठा qla_qpair *);
व्योम qla2x00_handle_rscn(scsi_qla_host_t *vha, काष्ठा event_arg *ea);
व्योम qla24xx_handle_plogi_करोne_event(काष्ठा scsi_qla_host *vha,
				     काष्ठा event_arg *ea);
व्योम qla24xx_handle_relogin_event(scsi_qla_host_t *vha,
				  काष्ठा event_arg *ea);
पूर्णांक qla24xx_async_gpdb(काष्ठा scsi_qla_host *, fc_port_t *, u8);
पूर्णांक qla24xx_async_prli(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_async_notअगरy_ack(scsi_qla_host_t *, fc_port_t *,
	काष्ठा imm_ntfy_from_isp *, पूर्णांक);
पूर्णांक qla24xx_post_newsess_work(काष्ठा scsi_qla_host *, port_id_t *, u8 *, u8*,
    व्योम *, u8);
पूर्णांक qla24xx_fcport_handle_login(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_detect_sfp(scsi_qla_host_t *);
पूर्णांक qla24xx_post_gpdb_work(काष्ठा scsi_qla_host *, fc_port_t *, u8);

बाह्य व्योम qla28xx_get_aux_images(काष्ठा scsi_qla_host *,
    काष्ठा active_regions *);
बाह्य व्योम qla27xx_get_active_image(काष्ठा scsi_qla_host *,
    काष्ठा active_regions *);

व्योम qla2x00_async_prlo_करोne(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_prlo_work(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_prlo_करोne_work(काष्ठा scsi_qla_host *,
    fc_port_t *, uपूर्णांक16_t *);
पूर्णांक qla_post_iidma_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport);
व्योम qla_करो_iidma_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport);
पूर्णांक qla2x00_reserve_mgmt_server_loop_id(scsi_qla_host_t *);
व्योम qla_rscn_replay(fc_port_t *fcport);
व्योम qla24xx_मुक्त_purex_item(काष्ठा purex_item *item);
बाह्य bool qla24xx_risc_firmware_invalid(uपूर्णांक32_t *);
व्योम qla_init_iocb_limit(scsi_qla_host_t *);


/*
 * Global Data in qla_os.c source file.
 */
बाह्य अक्षर qla2x00_version_str[];

बाह्य काष्ठा kmem_cache *srb_cachep;
बाह्य काष्ठा kmem_cache *qla_tgt_plogi_cachep;

बाह्य पूर्णांक ql2xlogपूर्णांकimeout;
बाह्य पूर्णांक qlport_करोwn_retry;
बाह्य पूर्णांक ql2xplogiअसलentdevice;
बाह्य पूर्णांक ql2xloginretrycount;
बाह्य पूर्णांक ql2xfdmienable;
बाह्य पूर्णांक ql2xrdpenable;
बाह्य पूर्णांक ql2xsmartsan;
बाह्य पूर्णांक ql2xallocfwdump;
बाह्य पूर्णांक ql2xextended_error_logging;
बाह्य पूर्णांक ql2xiidmaenable;
बाह्य पूर्णांक ql2xmqsupport;
बाह्य पूर्णांक ql2xfwloadbin;
बाह्य पूर्णांक ql2xetsenable;
बाह्य पूर्णांक ql2xshअगरtctondsd;
बाह्य पूर्णांक ql2xdbwr;
बाह्य पूर्णांक ql2xasyncपंचांगfenable;
बाह्य पूर्णांक ql2xgffidenable;
बाह्य पूर्णांक ql2xenabledअगर;
बाह्य पूर्णांक ql2xenablehba_err_chk;
बाह्य पूर्णांक ql2xtargetreset;
बाह्य पूर्णांक ql2xकरोntresethba;
बाह्य uपूर्णांक64_t ql2xmaxlun;
बाह्य पूर्णांक ql2xmdcapmask;
बाह्य पूर्णांक ql2xmdenable;
बाह्य पूर्णांक ql2xexlogins;
बाह्य पूर्णांक ql2xexchoffld;
बाह्य पूर्णांक ql2xiniexchg;
बाह्य पूर्णांक ql2xfwholdabts;
बाह्य पूर्णांक ql2xmvasynctoatio;
बाह्य पूर्णांक ql2xuctrlirq;
बाह्य पूर्णांक ql2xnvmeenable;
बाह्य पूर्णांक ql2xस्वतःdetectsfp;
बाह्य पूर्णांक ql2xenablemsix;
बाह्य पूर्णांक qla2xuseresexchक्रमels;
बाह्य पूर्णांक ql2xexlogins;
बाह्य पूर्णांक ql2xdअगरbundlingपूर्णांकernalbuffers;
बाह्य पूर्णांक ql2xfulldump_on_mpअगरail;
बाह्य पूर्णांक ql2xenक्रमce_iocb_limit;
बाह्य पूर्णांक ql2xabts_रुको_nvme;

बाह्य पूर्णांक qla2x00_loop_reset(scsi_qla_host_t *);
बाह्य व्योम qla2x00_पात_all_cmds(scsi_qla_host_t *, पूर्णांक);
बाह्य पूर्णांक qla2x00_post_aen_work(काष्ठा scsi_qla_host *, क्रमागत
    fc_host_event_code, u32);
बाह्य पूर्णांक qla2x00_post_idc_ack_work(काष्ठा scsi_qla_host *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_login_work(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_logout_work(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_adisc_work(काष्ठा scsi_qla_host *, fc_port_t *,
    uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_post_async_adisc_करोne_work(काष्ठा scsi_qla_host *,
    fc_port_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_set_exlogins_buffer(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_मुक्त_exlogin_buffer(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qla2x00_set_exchoffld_buffer(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_मुक्त_exchoffld_buffer(काष्ठा qla_hw_data *);

बाह्य पूर्णांक qla81xx_restart_mpi_firmware(scsi_qla_host_t *);

बाह्य काष्ठा scsi_qla_host *qla2x00_create_host(काष्ठा scsi_host_ढाँचा *,
	काष्ठा qla_hw_data *);
बाह्य व्योम qla2x00_मुक्त_host(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_relogin(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_करो_work(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_मुक्त_fcports(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_मुक्त_fcport(fc_port_t *);

बाह्य व्योम qla83xx_schedule_work(scsi_qla_host_t *, पूर्णांक);
बाह्य व्योम qla83xx_service_idc_aen(काष्ठा work_काष्ठा *);
बाह्य व्योम qla83xx_nic_core_unrecoverable_work(काष्ठा work_काष्ठा *);
बाह्य व्योम qla83xx_idc_state_handler_work(काष्ठा work_काष्ठा *);
बाह्य व्योम qla83xx_nic_core_reset_work(काष्ठा work_काष्ठा *);

बाह्य व्योम qla83xx_idc_lock(scsi_qla_host_t *, uपूर्णांक16_t);
बाह्य व्योम qla83xx_idc_unlock(scsi_qla_host_t *, uपूर्णांक16_t);
बाह्य पूर्णांक qla83xx_idc_state_handler(scsi_qla_host_t *);
बाह्य पूर्णांक qla83xx_set_drv_presence(scsi_qla_host_t *vha);
बाह्य पूर्णांक __qla83xx_set_drv_presence(scsi_qla_host_t *vha);
बाह्य पूर्णांक qla83xx_clear_drv_presence(scsi_qla_host_t *vha);
बाह्य पूर्णांक __qla83xx_clear_drv_presence(scsi_qla_host_t *vha);
बाह्य पूर्णांक qla2x00_post_uevent_work(काष्ठा scsi_qla_host *, u32);

बाह्य पूर्णांक qla2x00_post_uevent_work(काष्ठा scsi_qla_host *, u32);
बाह्य व्योम qla2x00_disable_board_on_pci_error(काष्ठा work_काष्ठा *);
बाह्य व्योम qla_eeh_work(काष्ठा work_काष्ठा *);
बाह्य व्योम qla2x00_sp_compl(srb_t *sp, पूर्णांक);
बाह्य व्योम qla2xxx_qpair_sp_मुक्त_dma(srb_t *sp);
बाह्य व्योम qla2xxx_qpair_sp_compl(srb_t *sp, पूर्णांक);
बाह्य व्योम qla24xx_sched_upd_fcport(fc_port_t *);
व्योम qla2x00_handle_login_करोne_event(काष्ठा scsi_qla_host *, fc_port_t *,
	uपूर्णांक16_t *);
पूर्णांक qla24xx_post_gnl_work(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_post_relogin_work(काष्ठा scsi_qla_host *vha);
व्योम qla2x00_रुको_क्रम_sess_deletion(scsi_qla_host_t *);
व्योम qla24xx_process_purex_rdp(काष्ठा scsi_qla_host *vha,
			       काष्ठा purex_item *pkt);
व्योम qla_pci_set_eeh_busy(काष्ठा scsi_qla_host *);
व्योम qla_schedule_eeh_work(काष्ठा scsi_qla_host *);

/*
 * Global Functions in qla_mid.c source file.
 */
बाह्य काष्ठा scsi_host_ढाँचा qla2xxx_driver_ढाँचा;
बाह्य काष्ठा scsi_transport_ढाँचा *qla2xxx_transport_vport_ढाँचा;
बाह्य व्योम qla2x00_समयr(काष्ठा समयr_list *);
बाह्य व्योम qla2x00_start_समयr(scsi_qla_host_t *, अचिन्हित दीर्घ);
बाह्य व्योम qla24xx_deallocate_vp_id(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_disable_vp (scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_enable_vp (scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_control_vp(scsi_qla_host_t *, पूर्णांक );
बाह्य पूर्णांक qla24xx_modअगरy_vp_config(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_send_change_request(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t);
बाह्य व्योम qla2x00_vp_stop_समयr(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_configure_vhba (scsi_qla_host_t *);
बाह्य व्योम qla24xx_report_id_acquisition(scsi_qla_host_t *,
    काष्ठा vp_rpt_id_entry_24xx *);
बाह्य व्योम qla2x00_करो_dpc_all_vps(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_vport_create_req_sanity_check(काष्ठा fc_vport *);
बाह्य scsi_qla_host_t *qla24xx_create_vhost(काष्ठा fc_vport *);

बाह्य व्योम qla2x00_sp_मुक्त_dma(srb_t *sp);
बाह्य अक्षर *qla2x00_get_fw_version_str(काष्ठा scsi_qla_host *, अक्षर *);

बाह्य व्योम qla2x00_mark_device_lost(scsi_qla_host_t *, fc_port_t *, पूर्णांक);
बाह्य व्योम qla2x00_mark_all_devices_lost(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_async_पात_cmd(srb_t *, bool);

बाह्य काष्ठा fw_blob *qla2x00_request_firmware(scsi_qla_host_t *);

बाह्य पूर्णांक qla2x00_रुको_क्रम_hba_online(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_रुको_क्रम_chip_reset(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_रुको_क्रम_fcoe_ctx_reset(scsi_qla_host_t *);

बाह्य व्योम qla2xxx_wake_dpc(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_alert_all_vps(काष्ठा rsp_que *, uपूर्णांक16_t *);
बाह्य व्योम qla2x00_async_event(scsi_qla_host_t *, काष्ठा rsp_que *,
	uपूर्णांक16_t *);
बाह्य पूर्णांक  qla2x00_vp_पात_isp(scsi_qla_host_t *);

/*
 * Global Function Prototypes in qla_iocb.c source file.
 */

बाह्य uपूर्णांक16_t qla2x00_calc_iocbs_32(uपूर्णांक16_t);
बाह्य uपूर्णांक16_t qla2x00_calc_iocbs_64(uपूर्णांक16_t);
बाह्य व्योम qla2x00_build_scsi_iocbs_32(srb_t *, cmd_entry_t *, uपूर्णांक16_t);
बाह्य व्योम qla2x00_build_scsi_iocbs_64(srb_t *, cmd_entry_t *, uपूर्णांक16_t);
बाह्य व्योम qla24xx_build_scsi_iocbs(srb_t *, काष्ठा cmd_type_7 *,
	uपूर्णांक16_t, काष्ठा req_que *);
बाह्य uपूर्णांक32_t qla2xxx_get_next_handle(काष्ठा req_que *req);
बाह्य पूर्णांक qla2x00_start_scsi(srb_t *sp);
बाह्य पूर्णांक qla24xx_start_scsi(srb_t *sp);
पूर्णांक qla2x00_marker(काष्ठा scsi_qla_host *, काष्ठा qla_qpair *,
    uपूर्णांक16_t, uपूर्णांक64_t, uपूर्णांक8_t);
बाह्य पूर्णांक qla2x00_start_sp(srb_t *);
बाह्य पूर्णांक qla24xx_dअगर_start_scsi(srb_t *);
बाह्य पूर्णांक qla2x00_start_bidir(srb_t *, काष्ठा scsi_qla_host *, uपूर्णांक32_t);
बाह्य पूर्णांक qla2xxx_dअगर_start_scsi_mq(srb_t *);
बाह्य व्योम qla2x00_init_समयr(srb_t *sp, अचिन्हित दीर्घ पंचांगo);
बाह्य अचिन्हित दीर्घ qla2x00_get_async_समयout(काष्ठा scsi_qla_host *);

बाह्य व्योम *qla2x00_alloc_iocbs(काष्ठा scsi_qla_host *, srb_t *);
बाह्य व्योम *__qla2x00_alloc_iocbs(काष्ठा qla_qpair *, srb_t *);
बाह्य पूर्णांक qla2x00_issue_marker(scsi_qla_host_t *, पूर्णांक);
बाह्य पूर्णांक qla24xx_walk_and_build_sglist_no_dअगरb(काष्ठा qla_hw_data *, srb_t *,
	काष्ठा dsd64 *, uपूर्णांक16_t, काष्ठा qla_tc_param *);
बाह्य पूर्णांक qla24xx_walk_and_build_sglist(काष्ठा qla_hw_data *, srb_t *,
	काष्ठा dsd64 *, uपूर्णांक16_t, काष्ठा qla_tc_param *);
बाह्य पूर्णांक qla24xx_walk_and_build_prot_sglist(काष्ठा qla_hw_data *, srb_t *,
	काष्ठा dsd64 *, uपूर्णांक16_t, काष्ठा qla_tgt_cmd *);
बाह्य पूर्णांक qla24xx_get_one_block_sg(uपूर्णांक32_t, काष्ठा qla2_sgx *, uपूर्णांक32_t *);
बाह्य पूर्णांक qla24xx_configure_prot_mode(srb_t *, uपूर्णांक16_t *);

/*
 * Global Function Prototypes in qla_mbx.c source file.
 */
बाह्य पूर्णांक
qla2x00_load_ram(scsi_qla_host_t *, dma_addr_t, uपूर्णांक32_t, uपूर्णांक32_t);

बाह्य पूर्णांक
qla2x00_dump_ram(scsi_qla_host_t *, dma_addr_t, uपूर्णांक32_t, uपूर्णांक32_t);

बाह्य पूर्णांक
qla2x00_execute_fw(scsi_qla_host_t *, uपूर्णांक32_t);

बाह्य पूर्णांक
qla2x00_get_fw_version(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_get_fw_options(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_set_fw_options(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_mbx_reg_test(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_verअगरy_checksum(scsi_qla_host_t *, uपूर्णांक32_t);

बाह्य पूर्णांक
qla2x00_issue_iocb(scsi_qla_host_t *, व्योम *, dma_addr_t, माप_प्रकार);

बाह्य पूर्णांक
qla2x00_पात_command(srb_t *);

बाह्य पूर्णांक
qla2x00_पात_target(काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);

बाह्य पूर्णांक
qla2x00_lun_reset(काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);

बाह्य पूर्णांक
qla2x00_get_adapter_id(scsi_qla_host_t *, uपूर्णांक16_t *, uपूर्णांक8_t *, uपूर्णांक8_t *,
    uपूर्णांक8_t *, uपूर्णांक16_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_get_retry_cnt(scsi_qla_host_t *, uपूर्णांक8_t *, uपूर्णांक8_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_init_firmware(scsi_qla_host_t *, uपूर्णांक16_t);

बाह्य पूर्णांक
qla2x00_get_port_database(scsi_qla_host_t *, fc_port_t *, uपूर्णांक8_t);

बाह्य पूर्णांक
qla24xx_get_port_database(scsi_qla_host_t *, u16, काष्ठा port_database_24xx *);

बाह्य पूर्णांक
qla2x00_get_firmware_state(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_get_port_name(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक8_t *, uपूर्णांक8_t);

बाह्य पूर्णांक
qla24xx_link_initialize(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_lip_reset(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_send_sns(scsi_qla_host_t *, dma_addr_t, uपूर्णांक16_t, माप_प्रकार);

बाह्य पूर्णांक
qla2x00_login_fabric(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t,
    uपूर्णांक16_t *, uपूर्णांक8_t);
बाह्य पूर्णांक
qla24xx_login_fabric(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t,
    uपूर्णांक16_t *, uपूर्णांक8_t);

बाह्य पूर्णांक
qla2x00_login_local_device(scsi_qla_host_t *, fc_port_t *, uपूर्णांक16_t *,
    uपूर्णांक8_t);

बाह्य पूर्णांक
qla2x00_fabric_logout(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t);

बाह्य पूर्णांक
qla24xx_fabric_logout(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t);

बाह्य पूर्णांक
qla2x00_full_login_lip(scsi_qla_host_t *ha);

बाह्य पूर्णांक
qla2x00_get_id_list(scsi_qla_host_t *, व्योम *, dma_addr_t, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_get_resource_cnts(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_get_fcal_position_map(scsi_qla_host_t *ha, अक्षर *pos_map);

बाह्य पूर्णांक
qla2x00_get_link_status(scsi_qla_host_t *, uपूर्णांक16_t, काष्ठा link_statistics *,
    dma_addr_t);

बाह्य पूर्णांक
qla24xx_get_isp_stats(scsi_qla_host_t *, काष्ठा link_statistics *,
    dma_addr_t, uपूर्णांक16_t);

बाह्य पूर्णांक qla24xx_पात_command(srb_t *);
बाह्य पूर्णांक qla24xx_async_पात_command(srb_t *);
बाह्य पूर्णांक
qla24xx_पात_target(काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);
बाह्य पूर्णांक
qla24xx_lun_reset(काष्ठा fc_port *, uपूर्णांक64_t, पूर्णांक);
बाह्य पूर्णांक
qla2x00_eh_रुको_क्रम_pending_commands(scsi_qla_host_t *, अचिन्हित पूर्णांक,
	uपूर्णांक64_t, क्रमागत nexus_रुको_type);
बाह्य पूर्णांक
qla2x00_प्रणाली_error(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_ग_लिखो_serdes_word(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t);
बाह्य पूर्णांक
qla2x00_पढ़ो_serdes_word(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla8044_ग_लिखो_serdes_word(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक
qla8044_पढ़ो_serdes_word(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t *);

बाह्य पूर्णांक
qla2x00_set_serdes_params(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t);

बाह्य पूर्णांक
qla2x00_stop_firmware(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_enable_eft_trace(scsi_qla_host_t *, dma_addr_t, uपूर्णांक16_t);
बाह्य पूर्णांक
qla2x00_disable_eft_trace(scsi_qla_host_t *);

बाह्य पूर्णांक
qla2x00_enable_fce_trace(scsi_qla_host_t *, dma_addr_t, uपूर्णांक16_t , uपूर्णांक16_t *,
    uपूर्णांक32_t *);

बाह्य पूर्णांक
qla2x00_disable_fce_trace(scsi_qla_host_t *, uपूर्णांक64_t *, uपूर्णांक64_t *);

बाह्य पूर्णांक
qla82xx_set_driver_version(scsi_qla_host_t *, अक्षर *);

बाह्य पूर्णांक
qla25xx_set_driver_version(scsi_qla_host_t *, अक्षर *);

बाह्य पूर्णांक
qla25xx_set_els_cmds_supported(scsi_qla_host_t *);

बाह्य पूर्णांक
qla24xx_get_buffer_credits(scsi_qla_host_t *, काष्ठा buffer_credit_24xx *,
	dma_addr_t);

बाह्य पूर्णांक
qla2x00_पढ़ो_sfp(scsi_qla_host_t *, dma_addr_t, uपूर्णांक8_t *,
	uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t);

बाह्य पूर्णांक
qla2x00_ग_लिखो_sfp(scsi_qla_host_t *, dma_addr_t, uपूर्णांक8_t *,
	uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t);

बाह्य पूर्णांक
qla2x00_set_idma_speed(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t, uपूर्णांक16_t *);

बाह्य पूर्णांक qla84xx_verअगरy_chip(काष्ठा scsi_qla_host *, uपूर्णांक16_t *);

बाह्य पूर्णांक qla81xx_idc_ack(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla81xx_fac_get_sector_size(scsi_qla_host_t *, uपूर्णांक32_t *);

बाह्य पूर्णांक
qla81xx_fac_करो_ग_लिखो_enable(scsi_qla_host_t *, पूर्णांक);

बाह्य पूर्णांक
qla81xx_fac_erase_sector(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);

बाह्य पूर्णांक qla81xx_fac_semaphore_access(scsi_qla_host_t *, पूर्णांक);

बाह्य पूर्णांक
qla2x00_get_xgmac_stats(scsi_qla_host_t *, dma_addr_t, uपूर्णांक16_t, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_get_dcbx_params(scsi_qla_host_t *, dma_addr_t, uपूर्णांक16_t);

बाह्य पूर्णांक
qla2x00_पढ़ो_ram_word(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t *);

बाह्य पूर्णांक
qla2x00_ग_लिखो_ram_word(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);

बाह्य पूर्णांक
qla81xx_ग_लिखो_mpi_रेजिस्टर(scsi_qla_host_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_get_data_rate(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_set_fcp_prio(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t,
	uपूर्णांक16_t *);
बाह्य पूर्णांक
qla81xx_get_port_config(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla81xx_set_port_config(scsi_qla_host_t *, uपूर्णांक16_t *);

बाह्य पूर्णांक
qla2x00_port_logout(scsi_qla_host_t *, काष्ठा fc_port *);

बाह्य पूर्णांक
qla2x00_dump_mctp_data(scsi_qla_host_t *, dma_addr_t, uपूर्णांक32_t, uपूर्णांक32_t);

बाह्य पूर्णांक
qla26xx_dport_diagnostics(scsi_qla_host_t *, व्योम *, uपूर्णांक, uपूर्णांक);

पूर्णांक qla24xx_send_mb_cmd(काष्ठा scsi_qla_host *, mbx_cmd_t *);
पूर्णांक qla24xx_gpdb_रुको(काष्ठा scsi_qla_host *, fc_port_t *, u8);
पूर्णांक qla24xx_gidlist_रुको(काष्ठा scsi_qla_host *, व्योम *, dma_addr_t,
    uपूर्णांक16_t *);
पूर्णांक __qla24xx_parse_gpdb(काष्ठा scsi_qla_host *, fc_port_t *,
	काष्ठा port_database_24xx *);
पूर्णांक qla24xx_get_port_login_templ(scsi_qla_host_t *, dma_addr_t,
				 व्योम *, uपूर्णांक16_t);

बाह्य पूर्णांक qla27xx_get_zio_threshold(scsi_qla_host_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla27xx_set_zio_threshold(scsi_qla_host_t *, uपूर्णांक16_t);
पूर्णांक qla24xx_res_count_रुको(काष्ठा scsi_qla_host *, uपूर्णांक16_t *, पूर्णांक);

बाह्य पूर्णांक qla28xx_secure_flash_update(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t,
    uपूर्णांक32_t, dma_addr_t, uपूर्णांक32_t);

बाह्य पूर्णांक qla2xxx_पढ़ो_remote_रेजिस्टर(scsi_qla_host_t *, uपूर्णांक32_t,
    uपूर्णांक32_t *);
बाह्य पूर्णांक qla2xxx_ग_लिखो_remote_रेजिस्टर(scsi_qla_host_t *, uपूर्णांक32_t,
    uपूर्णांक32_t);

/*
 * Global Function Prototypes in qla_isr.c source file.
 */
बाह्य irqवापस_t qla2100_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य irqवापस_t qla2300_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य irqवापस_t qla24xx_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य व्योम qla2x00_process_response_queue(काष्ठा rsp_que *);
बाह्य व्योम
qla24xx_process_response_queue(काष्ठा scsi_qla_host *, काष्ठा rsp_que *);
बाह्य पूर्णांक qla2x00_request_irqs(काष्ठा qla_hw_data *, काष्ठा rsp_que *);
बाह्य व्योम qla2x00_मुक्त_irqs(scsi_qla_host_t *);

बाह्य पूर्णांक qla2x00_get_data_rate(scsi_qla_host_t *);
बाह्य स्थिर अक्षर *qla2x00_get_link_speed_str(काष्ठा qla_hw_data *, uपूर्णांक16_t);
बाह्य srb_t *
qla2x00_get_sp_from_handle(scsi_qla_host_t *, स्थिर अक्षर *, काष्ठा req_que *,
	व्योम *);
बाह्य व्योम
qla2x00_process_completed_request(काष्ठा scsi_qla_host *, काष्ठा req_que *,
	uपूर्णांक32_t);
बाह्य irqवापस_t
qla2xxx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id);
बाह्य irqवापस_t
qla2xxx_msix_rsp_q_hs(पूर्णांक irq, व्योम *dev_id);
fc_port_t *qla2x00_find_fcport_by_loopid(scsi_qla_host_t *, uपूर्णांक16_t);
fc_port_t *qla2x00_find_fcport_by_wwpn(scsi_qla_host_t *, u8 *, u8);
fc_port_t *qla2x00_find_fcport_by_nportid(scsi_qla_host_t *, port_id_t *, u8);

/*
 * Global Function Prototypes in qla_sup.c source file.
 */
बाह्य व्योम qla2x00_release_nvram_protection(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_पढ़ो_flash_data(scsi_qla_host_t *, uपूर्णांक32_t *,
    uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य uपूर्णांक8_t *qla2x00_पढ़ो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);
बाह्य uपूर्णांक8_t *qla24xx_पढ़ो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);
बाह्य पूर्णांक qla2x00_ग_लिखो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);
बाह्य पूर्णांक qla24xx_ग_लिखो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);
बाह्य uपूर्णांक8_t *qla25xx_पढ़ो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);
बाह्य पूर्णांक qla25xx_ग_लिखो_nvram_data(scsi_qla_host_t *, व्योम *, uपूर्णांक32_t,
    uपूर्णांक32_t);

बाह्य पूर्णांक qla2x00_is_a_vp_did(scsi_qla_host_t *, uपूर्णांक32_t);
bool qla2x00_check_reg32_क्रम_disconnect(scsi_qla_host_t *, uपूर्णांक32_t);
bool qla2x00_check_reg16_क्रम_disconnect(scsi_qla_host_t *, uपूर्णांक16_t);

बाह्य पूर्णांक qla2x00_beacon_on(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla2x00_beacon_off(काष्ठा scsi_qla_host *);
बाह्य व्योम qla2x00_beacon_blink(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_beacon_on(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla24xx_beacon_off(काष्ठा scsi_qla_host *);
बाह्य व्योम qla24xx_beacon_blink(काष्ठा scsi_qla_host *);
बाह्य व्योम qla83xx_beacon_blink(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla82xx_beacon_on(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla82xx_beacon_off(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla83xx_wr_reg(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक qla83xx_rd_reg(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t *);
बाह्य पूर्णांक qla83xx_restart_nic_firmware(scsi_qla_host_t *);
बाह्य पूर्णांक qla83xx_access_control(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक32_t,
				  uपूर्णांक32_t, uपूर्णांक16_t *);

बाह्य व्योम *qla2x00_पढ़ो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
					 uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक qla2x00_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
				     uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम *qla24xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
					 uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक qla24xx_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
				     uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम *qla25xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
					 uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम *qla8044_पढ़ो_optrom_data(काष्ठा scsi_qla_host *,
					 व्योम *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम qla8044_watchकरोg(काष्ठा scsi_qla_host *vha);

बाह्य पूर्णांक qla2x00_get_flash_version(scsi_qla_host_t *, व्योम *);
बाह्य पूर्णांक qla24xx_get_flash_version(scsi_qla_host_t *, व्योम *);
बाह्य पूर्णांक qla82xx_get_flash_version(scsi_qla_host_t *, व्योम *);

बाह्य पूर्णांक qla2xxx_get_flash_info(scsi_qla_host_t *);
बाह्य पूर्णांक qla2xxx_get_vpd_field(scsi_qla_host_t *, अक्षर *, अक्षर *, माप_प्रकार);

बाह्य व्योम qla2xxx_flash_npiv_conf(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_पढ़ो_fcp_prio_cfg(scsi_qla_host_t *);

/*
 * Global Function Prototypes in qla_dbg.c source file.
 */
व्योम qla2xxx_dump_fw(scsi_qla_host_t *vha);
व्योम qla2100_fw_dump(scsi_qla_host_t *vha);
व्योम qla2300_fw_dump(scsi_qla_host_t *vha);
व्योम qla24xx_fw_dump(scsi_qla_host_t *vha);
व्योम qla25xx_fw_dump(scsi_qla_host_t *vha);
व्योम qla81xx_fw_dump(scsi_qla_host_t *vha);
व्योम qla82xx_fw_dump(scsi_qla_host_t *vha);
व्योम qla8044_fw_dump(scsi_qla_host_t *vha);

व्योम qla27xx_fwdump(scsi_qla_host_t *vha);
बाह्य व्योम qla27xx_mpi_fwdump(scsi_qla_host_t *, पूर्णांक);
बाह्य uदीर्घ qla27xx_fwdt_calculate_dump_size(काष्ठा scsi_qla_host *, व्योम *);
बाह्य पूर्णांक qla27xx_fwdt_ढाँचा_valid(व्योम *);
बाह्य uदीर्घ qla27xx_fwdt_ढाँचा_size(व्योम *);

बाह्य व्योम qla2xxx_dump_post_process(scsi_qla_host_t *, पूर्णांक);
बाह्य व्योम ql_dump_regs(uपूर्णांक, scsi_qla_host_t *, uपूर्णांक);
बाह्य व्योम ql_dump_buffer(uपूर्णांक, scsi_qla_host_t *, uपूर्णांक, स्थिर व्योम *, uपूर्णांक);
/*
 * Global Function Prototypes in qla_gs.c source file.
 */
बाह्य व्योम *qla2x00_prep_ms_iocb(scsi_qla_host_t *, काष्ठा ct_arg *);
बाह्य व्योम *qla24xx_prep_ms_iocb(scsi_qla_host_t *, काष्ठा ct_arg *);
बाह्य पूर्णांक qla2x00_ga_nxt(scsi_qla_host_t *, fc_port_t *);
बाह्य पूर्णांक qla2x00_gid_pt(scsi_qla_host_t *, sw_info_t *);
बाह्य पूर्णांक qla2x00_gpn_id(scsi_qla_host_t *, sw_info_t *);
बाह्य पूर्णांक qla2x00_gnn_id(scsi_qla_host_t *, sw_info_t *);
बाह्य व्योम qla2x00_gff_id(scsi_qla_host_t *, sw_info_t *);
बाह्य पूर्णांक qla2x00_rft_id(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_rff_id(scsi_qla_host_t *, u8);
बाह्य पूर्णांक qla2x00_rnn_id(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_rsnn_nn(scsi_qla_host_t *);
बाह्य व्योम *qla2x00_prep_ms_fdmi_iocb(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य व्योम *qla24xx_prep_ms_fdmi_iocb(scsi_qla_host_t *, uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक qla2x00_fdmi_रेजिस्टर(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_gfpn_id(scsi_qla_host_t *, sw_info_t *);
बाह्य पूर्णांक qla2x00_gpsc(scsi_qla_host_t *, sw_info_t *);
बाह्य माप_प्रकार qla2x00_get_sym_node_name(scsi_qla_host_t *, uपूर्णांक8_t *, माप_प्रकार);
बाह्य पूर्णांक qla2x00_chk_ms_status(scsi_qla_host_t *, ms_iocb_entry_t *,
	काष्ठा ct_sns_rsp *, स्थिर अक्षर *);
बाह्य व्योम qla2x00_async_iocb_समयout(व्योम *data);

बाह्य व्योम qla2x00_मुक्त_fcport(fc_port_t *);

बाह्य पूर्णांक qla24xx_post_gpnid_work(काष्ठा scsi_qla_host *, port_id_t *);
बाह्य पूर्णांक qla24xx_async_gpnid(scsi_qla_host_t *, port_id_t *);
व्योम qla24xx_handle_gpnid_event(scsi_qla_host_t *, काष्ठा event_arg *);

पूर्णांक qla24xx_post_gpsc_work(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_async_gpsc(scsi_qla_host_t *, fc_port_t *);
व्योम qla24xx_handle_gpsc_event(scsi_qla_host_t *, काष्ठा event_arg *);
पूर्णांक qla2x00_mgmt_svr_login(scsi_qla_host_t *);
व्योम qla24xx_handle_gffid_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea);
पूर्णांक qla24xx_async_gffid(scsi_qla_host_t *vha, fc_port_t *fcport);
पूर्णांक qla24xx_async_gpnft(scsi_qla_host_t *, u8, srb_t *);
व्योम qla24xx_async_gpnft_करोne(scsi_qla_host_t *, srb_t *);
व्योम qla24xx_async_gnnft_करोne(scsi_qla_host_t *, srb_t *);
पूर्णांक qla24xx_async_gnnid(scsi_qla_host_t *, fc_port_t *);
व्योम qla24xx_handle_gnnid_event(scsi_qla_host_t *, काष्ठा event_arg *);
पूर्णांक qla24xx_post_gnnid_work(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_post_gfpnid_work(काष्ठा scsi_qla_host *, fc_port_t *);
पूर्णांक qla24xx_async_gfpnid(scsi_qla_host_t *, fc_port_t *);
व्योम qla24xx_handle_gfpnid_event(scsi_qla_host_t *, काष्ठा event_arg *);
व्योम qla24xx_sp_unmap(scsi_qla_host_t *, srb_t *);
व्योम qla_scan_work_fn(काष्ठा work_काष्ठा *);
uपूर्णांक qla25xx_fdmi_port_speed_capability(काष्ठा qla_hw_data *);
uपूर्णांक qla25xx_fdmi_port_speed_currently(काष्ठा qla_hw_data *);

/*
 * Global Function Prototypes in qla_attr.c source file.
 */
काष्ठा device_attribute;
बाह्य काष्ठा device_attribute *qla2x00_host_attrs[];
बाह्य काष्ठा device_attribute *qla2x00_host_attrs_dm[];
काष्ठा fc_function_ढाँचा;
बाह्य काष्ठा fc_function_ढाँचा qla2xxx_transport_functions;
बाह्य काष्ठा fc_function_ढाँचा qla2xxx_transport_vport_functions;
बाह्य व्योम qla2x00_alloc_sysfs_attr(scsi_qla_host_t *);
बाह्य व्योम qla2x00_मुक्त_sysfs_attr(scsi_qla_host_t *, bool);
बाह्य व्योम qla2x00_init_host_attr(scsi_qla_host_t *);
बाह्य व्योम qla2x00_alloc_sysfs_attr(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_loopback_test(scsi_qla_host_t *, काष्ठा msg_echo_lb *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla2x00_echo_test(scsi_qla_host_t *,
	काष्ठा msg_echo_lb *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla24xx_update_all_fcp_prio(scsi_qla_host_t *);
बाह्य पूर्णांक qla24xx_fcp_prio_cfg_valid(scsi_qla_host_t *,
	काष्ठा qla_fcp_prio_cfg *, uपूर्णांक8_t);
व्योम qla_insert_tgt_attrs(व्योम);
/*
 * Global Function Prototypes in qla_dfs.c source file.
 */
बाह्य पूर्णांक qla2x00_dfs_setup(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_dfs_हटाओ(scsi_qla_host_t *);

/* Globa function prototypes क्रम multi-q */
बाह्य पूर्णांक qla25xx_request_irq(काष्ठा qla_hw_data *, काष्ठा qla_qpair *,
	काष्ठा qla_msix_entry *, पूर्णांक);
बाह्य पूर्णांक qla25xx_init_req_que(काष्ठा scsi_qla_host *, काष्ठा req_que *);
बाह्य पूर्णांक qla25xx_init_rsp_que(काष्ठा scsi_qla_host *, काष्ठा rsp_que *);
बाह्य पूर्णांक qla25xx_create_req_que(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक8_t,
	uपूर्णांक16_t, पूर्णांक, uपूर्णांक8_t, bool);
बाह्य पूर्णांक qla25xx_create_rsp_que(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक8_t,
	uपूर्णांक16_t, काष्ठा qla_qpair *, bool);

बाह्य व्योम qla2x00_init_response_q_entries(काष्ठा rsp_que *);
बाह्य पूर्णांक qla25xx_delete_req_que(काष्ठा scsi_qla_host *, काष्ठा req_que *);
बाह्य पूर्णांक qla25xx_delete_rsp_que(काष्ठा scsi_qla_host *, काष्ठा rsp_que *);
बाह्य पूर्णांक qla25xx_delete_queues(काष्ठा scsi_qla_host *);
बाह्य uपूर्णांक16_t qla24xx_rd_req_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t);
बाह्य uपूर्णांक16_t qla25xx_rd_req_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t);
बाह्य व्योम qla24xx_wrt_req_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक16_t);
बाह्य व्योम qla25xx_wrt_req_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक16_t);
बाह्य व्योम qla25xx_wrt_rsp_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक16_t);
बाह्य व्योम qla24xx_wrt_rsp_reg(काष्ठा qla_hw_data *, uपूर्णांक16_t, uपूर्णांक16_t);

/* qlafx00 related functions */
बाह्य पूर्णांक qlafx00_pci_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qlafx00_initialize_adapter(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qlafx00_soft_reset(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_chip_diag(scsi_qla_host_t *);
बाह्य व्योम qlafx00_config_rings(काष्ठा scsi_qla_host *);
बाह्य अक्षर *qlafx00_pci_info_str(काष्ठा scsi_qla_host *, अक्षर *, माप_प्रकार);
बाह्य अक्षर *qlafx00_fw_version_str(काष्ठा scsi_qla_host *, अक्षर *, माप_प्रकार);
बाह्य irqवापस_t qlafx00_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य व्योम qlafx00_enable_पूर्णांकrs(काष्ठा qla_hw_data *);
बाह्य व्योम qlafx00_disable_पूर्णांकrs(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qlafx00_पात_target(fc_port_t *, uपूर्णांक64_t, पूर्णांक);
बाह्य पूर्णांक qlafx00_lun_reset(fc_port_t *, uपूर्णांक64_t, पूर्णांक);
बाह्य पूर्णांक qlafx00_start_scsi(srb_t *);
बाह्य पूर्णांक qlafx00_पात_isp(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_iospace_config(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qlafx00_init_firmware(scsi_qla_host_t *, uपूर्णांक16_t);
बाह्य पूर्णांक qlafx00_driver_shutकरोwn(scsi_qla_host_t *, पूर्णांक);
बाह्य पूर्णांक qlafx00_fw_पढ़ोy(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_configure_devices(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_reset_initialize(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_fx_disc(scsi_qla_host_t *, fc_port_t *, uपूर्णांक16_t);
बाह्य व्योम qlafx00_process_aen(काष्ठा scsi_qla_host *, काष्ठा qla_work_evt *);
बाह्य पूर्णांक qlafx00_post_aenfx_work(काष्ठा scsi_qla_host *,  uपूर्णांक32_t,
				   uपूर्णांक32_t *, पूर्णांक);
बाह्य uपूर्णांक32_t qlafx00_fw_state_show(काष्ठा device *,
				      काष्ठा device_attribute *, अक्षर *);
बाह्य व्योम qlafx00_get_host_speed(काष्ठा Scsi_Host *);
बाह्य व्योम qlafx00_init_response_q_entries(काष्ठा rsp_que *);

बाह्य व्योम qlafx00_पंचांग_iocb(srb_t *, काष्ठा tsk_mgmt_entry_fx00 *);
बाह्य व्योम qlafx00_पात_iocb(srb_t *, काष्ठा पात_iocb_entry_fx00 *);
बाह्य व्योम qlafx00_fxdisc_iocb(srb_t *, काष्ठा fxdisc_entry_fx00 *);
बाह्य व्योम qlafx00_समयr_routine(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_rescan_isp(scsi_qla_host_t *);
बाह्य पूर्णांक qlafx00_loop_reset(scsi_qla_host_t *vha);

/* qla82xx related functions */

/* PCI related functions */
बाह्य पूर्णांक qla82xx_pci_config(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla82xx_pci_mem_पढ़ो_2M(काष्ठा qla_hw_data *, u64, व्योम *, पूर्णांक);
बाह्य पूर्णांक qla82xx_pci_region_offset(काष्ठा pci_dev *, पूर्णांक);
बाह्य पूर्णांक qla82xx_iospace_config(काष्ठा qla_hw_data *);

/* Initialization related functions */
बाह्य पूर्णांक qla82xx_reset_chip(काष्ठा scsi_qla_host *);
बाह्य व्योम qla82xx_config_rings(काष्ठा scsi_qla_host *);
बाह्य व्योम qla82xx_watchकरोg(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_start_firmware(scsi_qla_host_t *);

/* Firmware and flash related functions */
बाह्य पूर्णांक qla82xx_load_risc(scsi_qla_host_t *, uपूर्णांक32_t *);
बाह्य व्योम *qla82xx_पढ़ो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
					 uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य पूर्णांक qla82xx_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
				     uपूर्णांक32_t, uपूर्णांक32_t);

/* Mailbox related functions */
बाह्य पूर्णांक qla82xx_पात_isp(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_restart_isp(scsi_qla_host_t *);

/* IOCB related functions */
बाह्य पूर्णांक qla82xx_start_scsi(srb_t *);
बाह्य व्योम qla2x00_sp_मुक्त(srb_t *sp);
बाह्य व्योम qla2x00_sp_समयout(काष्ठा समयr_list *);
बाह्य व्योम qla2x00_bsg_job_करोne(srb_t *sp, पूर्णांक);
बाह्य व्योम qla2x00_bsg_sp_मुक्त(srb_t *sp);
बाह्य व्योम qla2x00_start_iocbs(काष्ठा scsi_qla_host *, काष्ठा req_que *);

/* Interrupt related */
बाह्य irqवापस_t qla82xx_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य irqवापस_t qla82xx_msi_handler(पूर्णांक, व्योम *);
बाह्य irqवापस_t qla82xx_msix_शेष(पूर्णांक, व्योम *);
बाह्य irqवापस_t qla82xx_msix_rsp_q(पूर्णांक, व्योम *);
बाह्य व्योम qla82xx_enable_पूर्णांकrs(काष्ठा qla_hw_data *);
बाह्य व्योम qla82xx_disable_पूर्णांकrs(काष्ठा qla_hw_data *);
बाह्य व्योम qla82xx_poll(पूर्णांक, व्योम *);
बाह्य व्योम qla82xx_init_flags(काष्ठा qla_hw_data *);

/* ISP 8021 hardware related */
बाह्य व्योम qla82xx_set_drv_active(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_wr_32(काष्ठा qla_hw_data *, uदीर्घ, u32);
बाह्य पूर्णांक qla82xx_rd_32(काष्ठा qla_hw_data *, uदीर्घ);
बाह्य पूर्णांक qla82xx_rdmem(काष्ठा qla_hw_data *, u64, व्योम *, पूर्णांक);
बाह्य पूर्णांक qla82xx_wrmem(काष्ठा qla_hw_data *, u64, व्योम *, पूर्णांक);

/* ISP 8021 IDC */
बाह्य व्योम qla82xx_clear_drv_active(काष्ठा qla_hw_data *);
बाह्य uपूर्णांक32_t  qla82xx_रुको_क्रम_state_change(scsi_qla_host_t *, uपूर्णांक32_t);
बाह्य पूर्णांक qla82xx_idc_lock(काष्ठा qla_hw_data *);
बाह्य व्योम qla82xx_idc_unlock(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qla82xx_device_state_handler(scsi_qla_host_t *);
बाह्य व्योम qla8xxx_dev_failed_handler(scsi_qla_host_t *);
बाह्य व्योम qla82xx_clear_qsnt_पढ़ोy(scsi_qla_host_t *);

बाह्य व्योम qla2x00_set_model_info(scsi_qla_host_t *, uपूर्णांक8_t *, माप_प्रकार,
				   स्थिर अक्षर *);
बाह्य पूर्णांक qla82xx_mbx_पूर्णांकr_enable(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_mbx_पूर्णांकr_disable(scsi_qla_host_t *);
बाह्य व्योम qla82xx_start_iocbs(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_fcoe_ctx_reset(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_check_md_needed(scsi_qla_host_t *);
बाह्य व्योम qla82xx_chip_reset_cleanup(scsi_qla_host_t *);
बाह्य पूर्णांक qla81xx_set_led_config(scsi_qla_host_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla81xx_get_led_config(scsi_qla_host_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla82xx_mbx_beacon_ctl(scsi_qla_host_t *, पूर्णांक);
बाह्य अक्षर *qdev_state(uपूर्णांक32_t);
बाह्य व्योम qla82xx_clear_pending_mbx(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_पढ़ो_temperature(scsi_qla_host_t *);
बाह्य पूर्णांक qla8044_पढ़ो_temperature(scsi_qla_host_t *);
बाह्य पूर्णांक qla2x00_पढ़ो_sfp_dev(काष्ठा scsi_qla_host *, अक्षर *, पूर्णांक);
बाह्य पूर्णांक ql26xx_led_config(scsi_qla_host_t *, uपूर्णांक16_t, uपूर्णांक16_t *);

/* BSG related functions */
बाह्य पूर्णांक qla24xx_bsg_request(काष्ठा bsg_job *);
बाह्य पूर्णांक qla24xx_bsg_समयout(काष्ठा bsg_job *);
बाह्य पूर्णांक qla84xx_reset_chip(scsi_qla_host_t *, uपूर्णांक16_t);
बाह्य पूर्णांक qla2x00_issue_iocb_समयout(scsi_qla_host_t *, व्योम *,
	dma_addr_t, माप_प्रकार, uपूर्णांक32_t);
बाह्य पूर्णांक qla2x00_get_idma_speed(scsi_qla_host_t *, uपूर्णांक16_t,
	uपूर्णांक16_t *, uपूर्णांक16_t *);

/* 83xx related functions */
व्योम qla83xx_fw_dump(scsi_qla_host_t *vha);

/* Minidump related functions */
बाह्य पूर्णांक qla82xx_md_get_ढाँचा_size(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_md_get_ढाँचा(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_md_alloc(scsi_qla_host_t *);
बाह्य व्योम qla82xx_md_मुक्त(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_md_collect(scsi_qla_host_t *);
बाह्य व्योम qla82xx_md_prep(scsi_qla_host_t *);
बाह्य व्योम qla82xx_set_reset_owner(scsi_qla_host_t *);
बाह्य पूर्णांक qla82xx_validate_ढाँचा_chksum(scsi_qla_host_t *vha);

/* Function declarations क्रम ISP8044 */
बाह्य पूर्णांक qla8044_idc_lock(काष्ठा qla_hw_data *ha);
बाह्य व्योम qla8044_idc_unlock(काष्ठा qla_hw_data *ha);
बाह्य uपूर्णांक32_t qla8044_rd_reg(काष्ठा qla_hw_data *ha, uदीर्घ addr);
बाह्य व्योम qla8044_wr_reg(काष्ठा qla_hw_data *ha, uदीर्घ addr, uपूर्णांक32_t val);
बाह्य व्योम qla8044_पढ़ो_reset_ढाँचा(काष्ठा scsi_qla_host *ha);
बाह्य व्योम qla8044_set_idc_करोntreset(काष्ठा scsi_qla_host *ha);
बाह्य पूर्णांक qla8044_rd_direct(काष्ठा scsi_qla_host *vha, स्थिर uपूर्णांक32_t crb_reg);
बाह्य व्योम qla8044_wr_direct(काष्ठा scsi_qla_host *vha,
			      स्थिर uपूर्णांक32_t crb_reg, स्थिर uपूर्णांक32_t value);
बाह्य पूर्णांक qla8044_device_state_handler(काष्ठा scsi_qla_host *vha);
बाह्य व्योम qla8044_clear_qsnt_पढ़ोy(काष्ठा scsi_qla_host *vha);
बाह्य व्योम qla8044_clear_drv_active(काष्ठा qla_hw_data *);
व्योम qla8044_get_minidump(काष्ठा scsi_qla_host *vha);
पूर्णांक qla8044_collect_md_data(काष्ठा scsi_qla_host *vha);
बाह्य पूर्णांक qla8044_md_get_ढाँचा(scsi_qla_host_t *);
बाह्य पूर्णांक qla8044_ग_लिखो_optrom_data(काष्ठा scsi_qla_host *, व्योम *,
				     uपूर्णांक32_t, uपूर्णांक32_t);
बाह्य irqवापस_t qla8044_पूर्णांकr_handler(पूर्णांक, व्योम *);
बाह्य व्योम qla82xx_mbx_completion(scsi_qla_host_t *, uपूर्णांक16_t);
बाह्य पूर्णांक qla8044_पात_isp(scsi_qla_host_t *);
बाह्य पूर्णांक qla8044_check_fw_alive(काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qla_get_exlogin_status(scsi_qla_host_t *, uपूर्णांक16_t *,
	uपूर्णांक16_t *);
बाह्य पूर्णांक qla_set_exlogin_mem_cfg(scsi_qla_host_t *vha, dma_addr_t phys_addr);
बाह्य पूर्णांक qla_get_exchoffld_status(scsi_qla_host_t *, uपूर्णांक16_t *, uपूर्णांक16_t *);
बाह्य पूर्णांक qla_set_exchoffld_mem_cfg(scsi_qla_host_t *);
बाह्य व्योम qlt_handle_abts_recv(काष्ठा scsi_qla_host *, काष्ठा rsp_que *,
	response_t *);

पूर्णांक qla24xx_async_notअगरy_ack(scsi_qla_host_t *, fc_port_t *,
	काष्ठा imm_ntfy_from_isp *, पूर्णांक);
व्योम qla24xx_करो_nack_work(काष्ठा scsi_qla_host *, काष्ठा qla_work_evt *);
व्योम qlt_plogi_ack_link(काष्ठा scsi_qla_host *, काष्ठा qlt_plogi_ack_t *,
	काष्ठा fc_port *, क्रमागत qlt_plogi_link_t);
व्योम qlt_plogi_ack_unref(काष्ठा scsi_qla_host *, काष्ठा qlt_plogi_ack_t *);
बाह्य व्योम qlt_schedule_sess_क्रम_deletion(काष्ठा fc_port *);
बाह्य काष्ठा fc_port *qlt_find_sess_invalidate_other(scsi_qla_host_t *,
	uपूर्णांक64_t wwn, port_id_t port_id, uपूर्णांक16_t loop_id, काष्ठा fc_port **);
व्योम qla24xx_delete_sess_fn(काष्ठा work_काष्ठा *);
व्योम qlt_unknown_atio_work_fn(काष्ठा work_काष्ठा *);
व्योम qlt_update_host_map(काष्ठा scsi_qla_host *, port_id_t);
व्योम qlt_हटाओ_target_resources(काष्ठा qla_hw_data *);
व्योम qlt_clr_qp_table(काष्ठा scsi_qla_host *vha);
व्योम qlt_set_mode(काष्ठा scsi_qla_host *);
पूर्णांक qla2x00_set_data_rate(scsi_qla_host_t *vha, uपूर्णांक16_t mode);
बाह्य व्योम qla24xx_process_purex_list(काष्ठा purex_list *);
बाह्य व्योम qla2x00_dfs_create_rport(scsi_qla_host_t *vha, काष्ठा fc_port *fp);
बाह्य व्योम qla2x00_dfs_हटाओ_rport(scsi_qla_host_t *vha, काष्ठा fc_port *fp);
बाह्य व्योम qla_रुको_nvme_release_cmd_kref(srb_t *sp);
बाह्य व्योम qla_nvme_पात_set_option
		(काष्ठा पात_entry_24xx *abt, srb_t *sp);
बाह्य व्योम qla_nvme_पात_process_comp_status
		(काष्ठा पात_entry_24xx *abt, srb_t *sp);

/* nvme.c */
व्योम qla_nvme_unरेजिस्टर_remote_port(काष्ठा fc_port *fcport);
व्योम qla_handle_els_plogi_करोne(scsi_qla_host_t *vha, काष्ठा event_arg *ea);

#घोषणा QLA2XX_HW_ERROR			BIT_0
#घोषणा QLA2XX_SHT_LNK_DWN		BIT_1
#घोषणा QLA2XX_INT_ERR			BIT_2
#घोषणा QLA2XX_CMD_TIMEOUT		BIT_3
#घोषणा QLA2XX_RESET_CMD_ERR		BIT_4
#घोषणा QLA2XX_TGT_SHT_LNK_DOWN		BIT_17

#घोषणा QLA2XX_MAX_LINK_DOWN_TIME	100

पूर्णांक qla2xxx_start_stats(काष्ठा Scsi_Host *shost, u32 flags);
पूर्णांक qla2xxx_stop_stats(काष्ठा Scsi_Host *shost, u32 flags);
पूर्णांक qla2xxx_reset_stats(काष्ठा Scsi_Host *shost, u32 flags);

पूर्णांक qla2xxx_get_ini_stats(काष्ठा Scsi_Host *shost, u32 flags, व्योम *data, u64 size);
पूर्णांक qla2xxx_get_tgt_stats(काष्ठा Scsi_Host *shost, u32 flags,
			  काष्ठा fc_rport *rport, व्योम *data, u64 size);
पूर्णांक qla2xxx_disable_port(काष्ठा Scsi_Host *shost);
पूर्णांक qla2xxx_enable_port(काष्ठा Scsi_Host *shost);

uपूर्णांक64_t qla2x00_get_num_tgts(scsi_qla_host_t *vha);
uपूर्णांक64_t qla2x00_count_set_bits(u32 num);

#पूर्ण_अगर /* _QLA_GBL_H */
