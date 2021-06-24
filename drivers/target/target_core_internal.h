<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_INTERNAL_H
#घोषणा TARGET_CORE_INTERNAL_H

#समावेश <linux/configfs.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <target/target_core_base.h>

#घोषणा TARGET_CORE_NAME_MAX_LEN	64
#घोषणा TARGET_FABRIC_NAME_SIZE		32

काष्ठा target_backend अणु
	काष्ठा list_head list;

	स्थिर काष्ठा target_backend_ops *ops;

	काष्ठा config_item_type tb_dev_cit;
	काष्ठा config_item_type tb_dev_attrib_cit;
	काष्ठा config_item_type tb_dev_action_cit;
	काष्ठा config_item_type tb_dev_pr_cit;
	काष्ठा config_item_type tb_dev_wwn_cit;
	काष्ठा config_item_type tb_dev_alua_tg_pt_gps_cit;
	काष्ठा config_item_type tb_dev_stat_cit;
पूर्ण;

काष्ठा target_fabric_configfs अणु
	atomic_t		tf_access_cnt;
	काष्ठा list_head	tf_list;
	काष्ठा config_group	tf_group;
	काष्ठा config_group	tf_disc_group;
	स्थिर काष्ठा target_core_fabric_ops *tf_ops;

	काष्ठा config_item_type tf_discovery_cit;
	काष्ठा config_item_type	tf_wwn_cit;
	काष्ठा config_item_type tf_wwn_fabric_stats_cit;
	काष्ठा config_item_type tf_wwn_param_cit;
	काष्ठा config_item_type tf_tpg_cit;
	काष्ठा config_item_type tf_tpg_base_cit;
	काष्ठा config_item_type tf_tpg_lun_cit;
	काष्ठा config_item_type tf_tpg_port_cit;
	काष्ठा config_item_type tf_tpg_port_stat_cit;
	काष्ठा config_item_type tf_tpg_np_cit;
	काष्ठा config_item_type tf_tpg_np_base_cit;
	काष्ठा config_item_type tf_tpg_attrib_cit;
	काष्ठा config_item_type tf_tpg_auth_cit;
	काष्ठा config_item_type tf_tpg_param_cit;
	काष्ठा config_item_type tf_tpg_nacl_cit;
	काष्ठा config_item_type tf_tpg_nacl_base_cit;
	काष्ठा config_item_type tf_tpg_nacl_attrib_cit;
	काष्ठा config_item_type tf_tpg_nacl_auth_cit;
	काष्ठा config_item_type tf_tpg_nacl_param_cit;
	काष्ठा config_item_type tf_tpg_nacl_stat_cit;
	काष्ठा config_item_type tf_tpg_mappedlun_cit;
	काष्ठा config_item_type tf_tpg_mappedlun_stat_cit;
पूर्ण;

/* target_core_alua.c */
बाह्य काष्ठा t10_alua_lu_gp *शेष_lu_gp;

/* target_core_device.c */
पूर्णांक	core_alloc_rtpi(काष्ठा se_lun *lun, काष्ठा se_device *dev);
काष्ठा se_dev_entry *core_get_se_deve_from_rtpi(काष्ठा se_node_acl *, u16);
व्योम	target_pr_kref_release(काष्ठा kref *);
व्योम	core_मुक्त_device_list_क्रम_node(काष्ठा se_node_acl *,
		काष्ठा se_portal_group *);
व्योम	core_update_device_list_access(u64, bool, काष्ठा se_node_acl *);
काष्ठा se_dev_entry *target_nacl_find_deve(काष्ठा se_node_acl *, u64);
पूर्णांक	core_enable_device_list_क्रम_node(काष्ठा se_lun *, काष्ठा se_lun_acl *,
		u64, bool, काष्ठा se_node_acl *, काष्ठा se_portal_group *);
व्योम	core_disable_device_list_क्रम_node(काष्ठा se_lun *, काष्ठा se_dev_entry *,
		काष्ठा se_node_acl *, काष्ठा se_portal_group *);
व्योम	core_clear_lun_from_tpg(काष्ठा se_lun *, काष्ठा se_portal_group *);
पूर्णांक	core_dev_add_lun(काष्ठा se_portal_group *, काष्ठा se_device *,
		काष्ठा se_lun *lun);
व्योम	core_dev_del_lun(काष्ठा se_portal_group *, काष्ठा se_lun *);
काष्ठा se_lun_acl *core_dev_init_initiator_node_lun_acl(काष्ठा se_portal_group *,
		काष्ठा se_node_acl *, u64, पूर्णांक *);
पूर्णांक	core_dev_add_initiator_node_lun_acl(काष्ठा se_portal_group *,
		काष्ठा se_lun_acl *, काष्ठा se_lun *lun, bool);
पूर्णांक	core_dev_del_initiator_node_lun_acl(काष्ठा se_lun *,
		काष्ठा se_lun_acl *);
व्योम	core_dev_मुक्त_initiator_node_lun_acl(काष्ठा se_portal_group *,
		काष्ठा se_lun_acl *lacl);
पूर्णांक	core_dev_setup_भव_lun0(व्योम);
व्योम	core_dev_release_भव_lun0(व्योम);
काष्ठा se_device *target_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name);
पूर्णांक	target_configure_device(काष्ठा se_device *dev);
व्योम	target_मुक्त_device(काष्ठा se_device *);
पूर्णांक	target_क्रम_each_device(पूर्णांक (*fn)(काष्ठा se_device *dev, व्योम *data),
			       व्योम *data);

/* target_core_configfs.c */
बाह्य काष्ठा configfs_item_operations target_core_dev_item_ops;
व्योम	target_setup_backend_cits(काष्ठा target_backend *);

/* target_core_fabric_configfs.c */
पूर्णांक	target_fabric_setup_cits(काष्ठा target_fabric_configfs *);

/* target_core_fabric_lib.c */
पूर्णांक	target_get_pr_transport_id_len(काष्ठा se_node_acl *nacl,
		काष्ठा t10_pr_registration *pr_reg, पूर्णांक *क्रमmat_code);
पूर्णांक	target_get_pr_transport_id(काष्ठा se_node_acl *nacl,
		काष्ठा t10_pr_registration *pr_reg, पूर्णांक *क्रमmat_code,
		अचिन्हित अक्षर *buf);
स्थिर अक्षर *target_parse_pr_out_transport_id(काष्ठा se_portal_group *tpg,
		अक्षर *buf, u32 *out_tid_len, अक्षर **port_nexus_ptr);

/* target_core_hba.c */
काष्ठा se_hba *core_alloc_hba(स्थिर अक्षर *, u32, u32);
पूर्णांक	core_delete_hba(काष्ठा se_hba *);

/* target_core_पंचांगr.c */
व्योम	core_पंचांगr_पात_task(काष्ठा se_device *, काष्ठा se_पंचांगr_req *,
			काष्ठा se_session *);
पूर्णांक	core_पंचांगr_lun_reset(काष्ठा se_device *, काष्ठा se_पंचांगr_req *,
		काष्ठा list_head *, काष्ठा se_cmd *);

/* target_core_tpg.c */
बाह्य काष्ठा se_device *g_lun0_dev;

काष्ठा se_node_acl *__core_tpg_get_initiator_node_acl(काष्ठा se_portal_group *tpg,
		स्थिर अक्षर *);
व्योम	core_tpg_add_node_to_devs(काष्ठा se_node_acl *, काष्ठा se_portal_group *,
				  काष्ठा se_lun *);
व्योम	core_tpg_रुको_क्रम_nacl_pr_ref(काष्ठा se_node_acl *);
काष्ठा se_lun *core_tpg_alloc_lun(काष्ठा se_portal_group *, u64);
पूर्णांक	core_tpg_add_lun(काष्ठा se_portal_group *, काष्ठा se_lun *,
		bool, काष्ठा se_device *);
व्योम core_tpg_हटाओ_lun(काष्ठा se_portal_group *, काष्ठा se_lun *);
काष्ठा se_node_acl *core_tpg_add_initiator_node_acl(काष्ठा se_portal_group *tpg,
		स्थिर अक्षर *initiatorname);
व्योम core_tpg_del_initiator_node_acl(काष्ठा se_node_acl *acl);

/* target_core_transport.c */
बाह्य काष्ठा kmem_cache *se_पंचांगr_req_cache;

पूर्णांक	init_se_kmem_caches(व्योम);
व्योम	release_se_kmem_caches(व्योम);
u32	scsi_get_new_index(scsi_index_t);
व्योम	transport_subप्रणाली_check_init(व्योम);
व्योम	transport_uninit_session(काष्ठा se_session *);
अचिन्हित अक्षर *transport_dump_cmd_direction(काष्ठा se_cmd *);
व्योम	transport_dump_dev_state(काष्ठा se_device *, अक्षर *, पूर्णांक *);
व्योम	transport_dump_dev_info(काष्ठा se_device *, काष्ठा se_lun *,
		अचिन्हित दीर्घ दीर्घ, अक्षर *, पूर्णांक *);
व्योम	transport_dump_vpd_proto_id(काष्ठा t10_vpd *, अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक	transport_dump_vpd_assoc(काष्ठा t10_vpd *, अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक	transport_dump_vpd_ident_type(काष्ठा t10_vpd *, अचिन्हित अक्षर *, पूर्णांक);
पूर्णांक	transport_dump_vpd_ident(काष्ठा t10_vpd *, अचिन्हित अक्षर *, पूर्णांक);
व्योम	transport_clear_lun_ref(काष्ठा se_lun *);
sense_reason_t	target_cmd_size_check(काष्ठा se_cmd *cmd, अचिन्हित पूर्णांक size);
व्योम	target_qf_करो_work(काष्ठा work_काष्ठा *work);
bool	target_check_wce(काष्ठा se_device *dev);
bool	target_check_fua(काष्ठा se_device *dev);
व्योम	__target_execute_cmd(काष्ठा se_cmd *, bool);
व्योम	target_queued_submit_work(काष्ठा work_काष्ठा *work);

/* target_core_stat.c */
व्योम	target_stat_setup_dev_शेष_groups(काष्ठा se_device *);
व्योम	target_stat_setup_port_शेष_groups(काष्ठा se_lun *);
व्योम	target_stat_setup_mappedlun_शेष_groups(काष्ठा se_lun_acl *);

/* target_core_xcopy.c */
बाह्य काष्ठा se_portal_group xcopy_pt_tpg;

/* target_core_configfs.c */
#घोषणा DB_ROOT_LEN		4096
#घोषणा	DB_ROOT_DEFAULT		"/var/target"
#घोषणा	DB_ROOT_PREFERRED	"/etc/target"

बाह्य अक्षर db_root[];

#पूर्ण_अगर /* TARGET_CORE_INTERNAL_H */
