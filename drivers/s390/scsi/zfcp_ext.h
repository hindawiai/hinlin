<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * External function declarations.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#अगर_अघोषित ZFCP_EXT_H
#घोषणा ZFCP_EXT_H

#समावेश <linux/types.h>
#समावेश <linux/sysfs.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश "zfcp_def.h"
#समावेश "zfcp_fc.h"

/* zfcp_aux.c */
बाह्य काष्ठा zfcp_port *zfcp_get_port_by_wwpn(काष्ठा zfcp_adapter *, u64);
बाह्य काष्ठा zfcp_adapter *zfcp_adapter_enqueue(काष्ठा ccw_device *);
बाह्य काष्ठा zfcp_port *zfcp_port_enqueue(काष्ठा zfcp_adapter *, u64, u32,
					   u32);
बाह्य व्योम zfcp_adapter_release(काष्ठा kref *);
बाह्य व्योम zfcp_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *);

/* zfcp_ccw.c */
बाह्य काष्ठा ccw_driver zfcp_ccw_driver;
बाह्य काष्ठा zfcp_adapter *zfcp_ccw_adapter_by_cdev(काष्ठा ccw_device *);
बाह्य व्योम zfcp_ccw_adapter_put(काष्ठा zfcp_adapter *);

/* zfcp_dbf.c */
बाह्य पूर्णांक zfcp_dbf_adapter_रेजिस्टर(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_dbf_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_dbf_rec_trig(अक्षर *, काष्ठा zfcp_adapter *,
			      काष्ठा zfcp_port *, काष्ठा scsi_device *, u8, u8);
बाह्य व्योम zfcp_dbf_rec_trig_lock(अक्षर *tag, काष्ठा zfcp_adapter *adapter,
				   काष्ठा zfcp_port *port,
				   काष्ठा scsi_device *sdev, u8 want, u8 need);
बाह्य व्योम zfcp_dbf_rec_run(अक्षर *, काष्ठा zfcp_erp_action *);
बाह्य व्योम zfcp_dbf_rec_run_lvl(पूर्णांक level, अक्षर *tag,
				 काष्ठा zfcp_erp_action *erp);
बाह्य व्योम zfcp_dbf_rec_run_wka(अक्षर *, काष्ठा zfcp_fc_wka_port *, u64);
बाह्य व्योम zfcp_dbf_hba_fsf_uss(अक्षर *, काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_dbf_hba_fsf_res(अक्षर *, पूर्णांक, काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_dbf_hba_fsf_fces(अक्षर *tag, स्थिर काष्ठा zfcp_fsf_req *req,
				  u64 wwpn, u32 fc_security_old,
				  u32 fc_security_new);
बाह्य व्योम zfcp_dbf_hba_bit_err(अक्षर *, काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_dbf_hba_def_err(काष्ठा zfcp_adapter *, u64, u16, व्योम **);
बाह्य व्योम zfcp_dbf_san_req(अक्षर *, काष्ठा zfcp_fsf_req *, u32);
बाह्य व्योम zfcp_dbf_san_res(अक्षर *, काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_dbf_san_in_els(अक्षर *, काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_dbf_scsi_common(अक्षर *tag, पूर्णांक level, काष्ठा scsi_device *sdev,
				 काष्ठा scsi_cmnd *sc,
				 काष्ठा zfcp_fsf_req *fsf);
बाह्य व्योम zfcp_dbf_scsi_eh(अक्षर *tag, काष्ठा zfcp_adapter *adapter,
			     अचिन्हित पूर्णांक scsi_id, पूर्णांक ret);

/* zfcp_erp.c */
बाह्य व्योम zfcp_erp_set_adapter_status(काष्ठा zfcp_adapter *, u32);
बाह्य व्योम zfcp_erp_clear_adapter_status(काष्ठा zfcp_adapter *, u32);
बाह्य व्योम zfcp_erp_port_क्रमced_no_port_dbf(अक्षर *dbftag,
					     काष्ठा zfcp_adapter *adapter,
					     u64 port_name, u32 port_id);
बाह्य व्योम zfcp_erp_adapter_reखोलो(काष्ठा zfcp_adapter *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_adapter_shutकरोwn(काष्ठा zfcp_adapter *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_set_port_status(काष्ठा zfcp_port *, u32);
बाह्य व्योम zfcp_erp_clear_port_status(काष्ठा zfcp_port *, u32);
बाह्य व्योम zfcp_erp_port_reखोलो(काष्ठा zfcp_port *port, पूर्णांक clear,
				 अक्षर *dbftag);
बाह्य व्योम zfcp_erp_port_shutकरोwn(काष्ठा zfcp_port *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_port_क्रमced_reखोलो(काष्ठा zfcp_port *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_port_क्रमced_reखोलो_all(काष्ठा zfcp_adapter *adapter,
					    पूर्णांक clear, अक्षर *dbftag);
बाह्य व्योम zfcp_erp_set_lun_status(काष्ठा scsi_device *, u32);
बाह्य व्योम zfcp_erp_clear_lun_status(काष्ठा scsi_device *, u32);
बाह्य व्योम zfcp_erp_lun_reखोलो(काष्ठा scsi_device *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_lun_shutकरोwn(काष्ठा scsi_device *, पूर्णांक, अक्षर *);
बाह्य व्योम zfcp_erp_lun_shutकरोwn_रुको(काष्ठा scsi_device *, अक्षर *);
बाह्य पूर्णांक  zfcp_erp_thपढ़ो_setup(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_erp_thपढ़ो_समाप्त(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_erp_रुको(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_erp_notअगरy(काष्ठा zfcp_erp_action *, अचिन्हित दीर्घ);
बाह्य व्योम zfcp_erp_समयout_handler(काष्ठा समयr_list *t);
बाह्य व्योम zfcp_erp_adapter_reset_sync(काष्ठा zfcp_adapter *adapter,
					अक्षर *dbftag);

/* zfcp_fc.c */
बाह्य काष्ठा kmem_cache *zfcp_fc_req_cache;
बाह्य व्योम zfcp_fc_enqueue_event(काष्ठा zfcp_adapter *,
				क्रमागत fc_host_event_code event_code, u32);
बाह्य व्योम zfcp_fc_post_event(काष्ठा work_काष्ठा *);
बाह्य व्योम zfcp_fc_scan_ports(काष्ठा work_काष्ठा *);
बाह्य व्योम zfcp_fc_incoming_els(काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_fc_port_did_lookup(काष्ठा work_काष्ठा *);
बाह्य व्योम zfcp_fc_trigger_did_lookup(काष्ठा zfcp_port *);
बाह्य व्योम zfcp_fc_plogi_evaluate(काष्ठा zfcp_port *, काष्ठा fc_els_flogi *);
बाह्य व्योम zfcp_fc_test_link(काष्ठा zfcp_port *);
बाह्य व्योम zfcp_fc_link_test_work(काष्ठा work_काष्ठा *);
बाह्य व्योम zfcp_fc_wka_ports_क्रमce_offline(काष्ठा zfcp_fc_wka_ports *);
बाह्य पूर्णांक zfcp_fc_gs_setup(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_fc_gs_destroy(काष्ठा zfcp_adapter *);
बाह्य पूर्णांक zfcp_fc_exec_bsg_job(काष्ठा bsg_job *);
बाह्य पूर्णांक zfcp_fc_समयout_bsg_job(काष्ठा bsg_job *);
बाह्य व्योम zfcp_fc_sym_name_update(काष्ठा work_काष्ठा *);
बाह्य अचिन्हित पूर्णांक zfcp_fc_port_scan_backoff(व्योम);
बाह्य व्योम zfcp_fc_conditional_port_scan(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_fc_inverse_conditional_port_scan(काष्ठा zfcp_adapter *);

/* zfcp_fsf.c */
बाह्य काष्ठा kmem_cache *zfcp_fsf_qtcb_cache;
बाह्य पूर्णांक zfcp_fsf_खोलो_port(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_खोलो_wka_port(काष्ठा zfcp_fc_wka_port *);
बाह्य पूर्णांक zfcp_fsf_बंद_wka_port(काष्ठा zfcp_fc_wka_port *);
बाह्य पूर्णांक zfcp_fsf_बंद_port(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_बंद_physical_port(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_खोलो_lun(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_बंद_lun(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_exchange_config_data(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_exchange_config_data_sync(काष्ठा zfcp_qdio *,
					      काष्ठा fsf_qtcb_bottom_config *);
बाह्य पूर्णांक zfcp_fsf_exchange_port_data(काष्ठा zfcp_erp_action *);
बाह्य पूर्णांक zfcp_fsf_exchange_port_data_sync(काष्ठा zfcp_qdio *,
					    काष्ठा fsf_qtcb_bottom_port *);
बाह्य u32 zfcp_fsf_convert_portspeed(u32 fsf_speed);
बाह्य व्योम zfcp_fsf_req_dismiss_all(काष्ठा zfcp_adapter *);
बाह्य पूर्णांक zfcp_fsf_status_पढ़ो(काष्ठा zfcp_qdio *);
बाह्य पूर्णांक zfcp_status_पढ़ो_refill(काष्ठा zfcp_adapter *adapter);
बाह्य पूर्णांक zfcp_fsf_send_ct(काष्ठा zfcp_fc_wka_port *, काष्ठा zfcp_fsf_ct_els *,
			    mempool_t *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक zfcp_fsf_send_els(काष्ठा zfcp_adapter *, u32,
			     काष्ठा zfcp_fsf_ct_els *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक zfcp_fsf_fcp_cmnd(काष्ठा scsi_cmnd *);
बाह्य व्योम zfcp_fsf_req_मुक्त(काष्ठा zfcp_fsf_req *);
बाह्य व्योम zfcp_fsf_fc_host_link_करोwn(काष्ठा zfcp_adapter *adapter);
बाह्य काष्ठा zfcp_fsf_req *zfcp_fsf_fcp_task_mgmt(काष्ठा scsi_device *sdev,
						   u8 पंचांग_flags);
बाह्य काष्ठा zfcp_fsf_req *zfcp_fsf_पात_fcp_cmnd(काष्ठा scsi_cmnd *);
बाह्य व्योम zfcp_fsf_reqid_check(काष्ठा zfcp_qdio *, पूर्णांक);
क्रमागत zfcp_fsf_prपूर्णांक_fmt अणु
	ZFCP_FSF_PRINT_FMT_LIST,
	ZFCP_FSF_PRINT_FMT_SINGLEITEM,
पूर्ण;
बाह्य sमाप_प्रकार zfcp_fsf_scnprपूर्णांक_fc_security(अक्षर *buf, माप_प्रकार size,
					     u32 fc_security,
					     क्रमागत zfcp_fsf_prपूर्णांक_fmt fmt);

/* zfcp_qdio.c */
बाह्य पूर्णांक zfcp_qdio_setup(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_qdio_destroy(काष्ठा zfcp_qdio *);
बाह्य पूर्णांक zfcp_qdio_sbal_get(काष्ठा zfcp_qdio *);
बाह्य पूर्णांक zfcp_qdio_send(काष्ठा zfcp_qdio *, काष्ठा zfcp_qdio_req *);
बाह्य पूर्णांक zfcp_qdio_sbals_from_sg(काष्ठा zfcp_qdio *, काष्ठा zfcp_qdio_req *,
				   काष्ठा scatterlist *);
बाह्य व्योम zfcp_qdio_shost_update(काष्ठा zfcp_adapter *स्थिर adapter,
				   स्थिर काष्ठा zfcp_qdio *स्थिर qdio);
बाह्य पूर्णांक zfcp_qdio_खोलो(काष्ठा zfcp_qdio *);
बाह्य व्योम zfcp_qdio_बंद(काष्ठा zfcp_qdio *);
बाह्य व्योम zfcp_qdio_siosl(काष्ठा zfcp_adapter *);

/* zfcp_scsi.c */
बाह्य bool zfcp_experimental_dix;
बाह्य काष्ठा scsi_transport_ढाँचा *zfcp_scsi_transport_ढाँचा;
बाह्य पूर्णांक zfcp_scsi_adapter_रेजिस्टर(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_scsi_adapter_unरेजिस्टर(काष्ठा zfcp_adapter *);
बाह्य काष्ठा fc_function_ढाँचा zfcp_transport_functions;
बाह्य व्योम zfcp_scsi_rport_work(काष्ठा work_काष्ठा *);
बाह्य व्योम zfcp_scsi_schedule_rport_रेजिस्टर(काष्ठा zfcp_port *);
बाह्य व्योम zfcp_scsi_schedule_rport_block(काष्ठा zfcp_port *);
बाह्य व्योम zfcp_scsi_schedule_rports_block(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_scsi_set_prot(काष्ठा zfcp_adapter *);
बाह्य व्योम zfcp_scsi_dअगर_sense_error(काष्ठा scsi_cmnd *, पूर्णांक);
बाह्य व्योम zfcp_scsi_shost_update_config_data(
	काष्ठा zfcp_adapter *स्थिर adapter,
	स्थिर काष्ठा fsf_qtcb_bottom_config *स्थिर bottom,
	स्थिर bool bottom_incomplete);
बाह्य व्योम zfcp_scsi_shost_update_port_data(
	काष्ठा zfcp_adapter *स्थिर adapter,
	स्थिर काष्ठा fsf_qtcb_bottom_port *स्थिर bottom);

/* zfcp_sysfs.c */
बाह्य स्थिर काष्ठा attribute_group *zfcp_sysfs_adapter_attr_groups[];
बाह्य स्थिर काष्ठा attribute_group *zfcp_unit_attr_groups[];
बाह्य स्थिर काष्ठा attribute_group *zfcp_port_attr_groups[];
बाह्य काष्ठा mutex zfcp_sysfs_port_units_mutex;
बाह्य काष्ठा device_attribute *zfcp_sysfs_sdev_attrs[];
बाह्य काष्ठा device_attribute *zfcp_sysfs_shost_attrs[];
bool zfcp_sysfs_port_is_removing(स्थिर काष्ठा zfcp_port *स्थिर port);

/* zfcp_unit.c */
बाह्य पूर्णांक zfcp_unit_add(काष्ठा zfcp_port *, u64);
बाह्य पूर्णांक zfcp_unit_हटाओ(काष्ठा zfcp_port *, u64);
बाह्य काष्ठा zfcp_unit *zfcp_unit_find(काष्ठा zfcp_port *, u64);
बाह्य काष्ठा scsi_device *zfcp_unit_sdev(काष्ठा zfcp_unit *unit);
बाह्य व्योम zfcp_unit_scsi_scan(काष्ठा zfcp_unit *);
बाह्य व्योम zfcp_unit_queue_scsi_scan(काष्ठा zfcp_port *);
बाह्य अचिन्हित पूर्णांक zfcp_unit_sdev_status(काष्ठा zfcp_unit *);

#पूर्ण_अगर	/* ZFCP_EXT_H */
