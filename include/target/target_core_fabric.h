<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_FABRIC_H
#घोषणा TARGET_CORE_FABRIC_H

#समावेश <linux/configfs.h>
#समावेश <linux/types.h>
#समावेश <target/target_core_base.h>

काष्ठा target_core_fabric_ops अणु
	काष्ठा module *module;
	/*
	 * XXX: Special हाल क्रम iscsi/iSCSI...
	 * If non-null, fabric_alias is used क्रम matching target/$fabric
	 * ConfigFS paths. If null, fabric_name is used क्रम this (see below).
	 */
	स्थिर अक्षर *fabric_alias;
	/*
	 * fabric_name is used क्रम matching target/$fabric ConfigFS paths
	 * without a fabric_alias (see above). It's also used क्रम the ALUA state
	 * path and is stored on disk with PR state.
	 */
	स्थिर अक्षर *fabric_name;
	माप_प्रकार node_acl_size;
	/*
	 * Limits number of scatterlist entries per SCF_SCSI_DATA_CDB payload.
	 * Setting this value tells target-core to enक्रमce this limit, and
	 * report as INQUIRY EVPD=b0 MAXIMUM TRANSFER LENGTH.
	 *
	 * target-core will currently reset se_cmd->data_length to this
	 * maximum size, and set UNDERFLOW residual count अगर length exceeds
	 * this limit.
	 *
	 * XXX: Not all initiator hosts honor this block-limit EVPD
	 * XXX: Currently assumes single PAGE_SIZE per scatterlist entry
	 */
	u32 max_data_sg_nents;
	अक्षर *(*tpg_get_wwn)(काष्ठा se_portal_group *);
	u16 (*tpg_get_tag)(काष्ठा se_portal_group *);
	u32 (*tpg_get_शेष_depth)(काष्ठा se_portal_group *);
	पूर्णांक (*tpg_check_demo_mode)(काष्ठा se_portal_group *);
	पूर्णांक (*tpg_check_demo_mode_cache)(काष्ठा se_portal_group *);
	पूर्णांक (*tpg_check_demo_mode_ग_लिखो_protect)(काष्ठा se_portal_group *);
	पूर्णांक (*tpg_check_prod_mode_ग_लिखो_protect)(काष्ठा se_portal_group *);
	/*
	 * Optionally used by fabrics to allow demo-mode login, but not
	 * expose any TPG LUNs, and वापस 'not connected' in standard
	 * inquiry response
	 */
	पूर्णांक (*tpg_check_demo_mode_login_only)(काष्ठा se_portal_group *);
	/*
	 * Optionally used as a configfs tunable to determine when
	 * target-core should संकेत the PROTECT=1 feature bit क्रम
	 * backends that करोn't support T10-PI, so that either fabric
	 * HW offload or target-core emulation perक्रमms the associated
	 * WRITE_STRIP and READ_INSERT operations.
	 */
	पूर्णांक (*tpg_check_prot_fabric_only)(काष्ठा se_portal_group *);
	u32 (*tpg_get_inst_index)(काष्ठा se_portal_group *);
	/*
	 * Optional to release काष्ठा se_cmd and fabric dependent allocated
	 * I/O descriptor after command execution has finished.
	 *
	 * Returning 1 will संकेत a descriptor has been released.
	 * Returning 0 will संकेत a descriptor has not been released.
	 */
	पूर्णांक (*check_stop_मुक्त)(काष्ठा se_cmd *);
	व्योम (*release_cmd)(काष्ठा se_cmd *);
	व्योम (*बंद_session)(काष्ठा se_session *);
	u32 (*sess_get_index)(काष्ठा se_session *);
	/*
	 * Used only क्रम SCSI fabrics that contain multi-value TransportIDs
	 * (like iSCSI).  All other SCSI fabrics should set this to शून्य.
	 */
	u32 (*sess_get_initiator_sid)(काष्ठा se_session *,
				      अचिन्हित अक्षर *, u32);
	पूर्णांक (*ग_लिखो_pending)(काष्ठा se_cmd *);
	व्योम (*set_शेष_node_attributes)(काष्ठा se_node_acl *);
	पूर्णांक (*get_cmd_state)(काष्ठा se_cmd *);
	पूर्णांक (*queue_data_in)(काष्ठा se_cmd *);
	पूर्णांक (*queue_status)(काष्ठा se_cmd *);
	व्योम (*queue_पंचांग_rsp)(काष्ठा se_cmd *);
	व्योम (*पातed_task)(काष्ठा se_cmd *);
	/*
	 * fabric module calls क्रम target_core_fabric_configfs.c
	 */
	काष्ठा se_wwn *(*fabric_make_wwn)(काष्ठा target_fabric_configfs *,
				काष्ठा config_group *, स्थिर अक्षर *);
	व्योम (*fabric_drop_wwn)(काष्ठा se_wwn *);
	व्योम (*add_wwn_groups)(काष्ठा se_wwn *);
	काष्ठा se_portal_group *(*fabric_make_tpg)(काष्ठा se_wwn *,
						   स्थिर अक्षर *);
	व्योम (*fabric_drop_tpg)(काष्ठा se_portal_group *);
	पूर्णांक (*fabric_post_link)(काष्ठा se_portal_group *,
				काष्ठा se_lun *);
	व्योम (*fabric_pre_unlink)(काष्ठा se_portal_group *,
				काष्ठा se_lun *);
	काष्ठा se_tpg_np *(*fabric_make_np)(काष्ठा se_portal_group *,
				काष्ठा config_group *, स्थिर अक्षर *);
	व्योम (*fabric_drop_np)(काष्ठा se_tpg_np *);
	पूर्णांक (*fabric_init_nodeacl)(काष्ठा se_node_acl *, स्थिर अक्षर *);

	काष्ठा configfs_attribute **tfc_discovery_attrs;
	काष्ठा configfs_attribute **tfc_wwn_attrs;
	काष्ठा configfs_attribute **tfc_tpg_base_attrs;
	काष्ठा configfs_attribute **tfc_tpg_np_base_attrs;
	काष्ठा configfs_attribute **tfc_tpg_attrib_attrs;
	काष्ठा configfs_attribute **tfc_tpg_auth_attrs;
	काष्ठा configfs_attribute **tfc_tpg_param_attrs;
	काष्ठा configfs_attribute **tfc_tpg_nacl_base_attrs;
	काष्ठा configfs_attribute **tfc_tpg_nacl_attrib_attrs;
	काष्ठा configfs_attribute **tfc_tpg_nacl_auth_attrs;
	काष्ठा configfs_attribute **tfc_tpg_nacl_param_attrs;

	/*
	 * Set this member variable to true अगर the SCSI transport protocol
	 * (e.g. iSCSI) requires that the Data-Out buffer is transferred in
	 * its entirety beक्रमe a command is पातed.
	 */
	bool ग_लिखो_pending_must_be_called;
पूर्ण;

पूर्णांक target_रेजिस्टर_ढाँचा(स्थिर काष्ठा target_core_fabric_ops *fo);
व्योम target_unरेजिस्टर_ढाँचा(स्थिर काष्ठा target_core_fabric_ops *fo);

पूर्णांक target_depend_item(काष्ठा config_item *item);
व्योम target_undepend_item(काष्ठा config_item *item);

काष्ठा se_session *target_setup_session(काष्ठा se_portal_group *,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, क्रमागत target_prot_op prot_op,
		स्थिर अक्षर *, व्योम *,
		पूर्णांक (*callback)(काष्ठा se_portal_group *,
				काष्ठा se_session *, व्योम *));
व्योम target_हटाओ_session(काष्ठा se_session *);

पूर्णांक transport_init_session(काष्ठा se_session *se_sess);
काष्ठा se_session *transport_alloc_session(क्रमागत target_prot_op);
पूर्णांक transport_alloc_session_tags(काष्ठा se_session *, अचिन्हित पूर्णांक,
		अचिन्हित पूर्णांक);
व्योम	__transport_रेजिस्टर_session(काष्ठा se_portal_group *,
		काष्ठा se_node_acl *, काष्ठा se_session *, व्योम *);
व्योम	transport_रेजिस्टर_session(काष्ठा se_portal_group *,
		काष्ठा se_node_acl *, काष्ठा se_session *, व्योम *);
sमाप_प्रकार	target_show_dynamic_sessions(काष्ठा se_portal_group *, अक्षर *);
व्योम	transport_मुक्त_session(काष्ठा se_session *);
व्योम	target_spc2_release(काष्ठा se_node_acl *nacl);
व्योम	target_put_nacl(काष्ठा se_node_acl *);
व्योम	transport_deरेजिस्टर_session_configfs(काष्ठा se_session *);
व्योम	transport_deरेजिस्टर_session(काष्ठा se_session *);


व्योम	__target_init_cmd(काष्ठा se_cmd *,
		स्थिर काष्ठा target_core_fabric_ops *,
		काष्ठा se_session *, u32, पूर्णांक, पूर्णांक, अचिन्हित अक्षर *, u64);
पूर्णांक	target_init_cmd(काष्ठा se_cmd *se_cmd, काष्ठा se_session *se_sess,
		अचिन्हित अक्षर *sense, u64 unpacked_lun, u32 data_length,
		पूर्णांक task_attr, पूर्णांक data_dir, पूर्णांक flags);
पूर्णांक	target_submit_prep(काष्ठा se_cmd *se_cmd, अचिन्हित अक्षर *cdb,
		काष्ठा scatterlist *sgl, u32 sgl_count,
		काष्ठा scatterlist *sgl_bidi, u32 sgl_bidi_count,
		काष्ठा scatterlist *sgl_prot, u32 sgl_prot_count, gfp_t gfp);
व्योम	target_submit(काष्ठा se_cmd *se_cmd);
sense_reason_t transport_lookup_cmd_lun(काष्ठा se_cmd *);
sense_reason_t target_cmd_init_cdb(काष्ठा se_cmd *se_cmd, अचिन्हित अक्षर *cdb,
				   gfp_t gfp);
sense_reason_t target_cmd_parse_cdb(काष्ठा se_cmd *);
व्योम	target_submit_cmd(काष्ठा se_cmd *, काष्ठा se_session *, अचिन्हित अक्षर *,
		अचिन्हित अक्षर *, u64, u32, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम	target_queue_submission(काष्ठा se_cmd *se_cmd);

पूर्णांक	target_submit_पंचांगr(काष्ठा se_cmd *se_cmd, काष्ठा se_session *se_sess,
		अचिन्हित अक्षर *sense, u64 unpacked_lun,
		व्योम *fabric_पंचांगr_ptr, अचिन्हित अक्षर पंचांग_type,
		gfp_t, u64, पूर्णांक);
पूर्णांक	transport_handle_cdb_direct(काष्ठा se_cmd *);
sense_reason_t	transport_generic_new_cmd(काष्ठा se_cmd *);

व्योम	target_put_cmd_and_रुको(काष्ठा se_cmd *cmd);
व्योम	target_execute_cmd(काष्ठा se_cmd *cmd);

पूर्णांक	transport_generic_मुक्त_cmd(काष्ठा se_cmd *, पूर्णांक);

bool	transport_रुको_क्रम_tasks(काष्ठा se_cmd *);
पूर्णांक	transport_send_check_condition_and_sense(काष्ठा se_cmd *,
		sense_reason_t, पूर्णांक);
पूर्णांक	target_send_busy(काष्ठा se_cmd *cmd);
पूर्णांक	target_get_sess_cmd(काष्ठा se_cmd *, bool);
पूर्णांक	target_put_sess_cmd(काष्ठा se_cmd *);
व्योम	target_stop_session(काष्ठा se_session *se_sess);
व्योम	target_रुको_क्रम_sess_cmds(काष्ठा se_session *);
व्योम	target_show_cmd(स्थिर अक्षर *pfx, काष्ठा se_cmd *cmd);

पूर्णांक	core_alua_check_nonop_delay(काष्ठा se_cmd *);

पूर्णांक	core_पंचांगr_alloc_req(काष्ठा se_cmd *, व्योम *, u8, gfp_t);
व्योम	core_पंचांगr_release_req(काष्ठा se_पंचांगr_req *);
पूर्णांक	transport_generic_handle_पंचांगr(काष्ठा se_cmd *);
व्योम	transport_generic_request_failure(काष्ठा se_cmd *, sense_reason_t);
पूर्णांक	transport_lookup_पंचांगr_lun(काष्ठा se_cmd *);
व्योम	core_allocate_nexus_loss_ua(काष्ठा se_node_acl *acl);

काष्ठा se_node_acl *core_tpg_get_initiator_node_acl(काष्ठा se_portal_group *tpg,
		अचिन्हित अक्षर *);
bool	target_tpg_has_node_acl(काष्ठा se_portal_group *tpg,
		स्थिर अक्षर *);
काष्ठा se_node_acl *core_tpg_check_initiator_node_acl(काष्ठा se_portal_group *,
		अचिन्हित अक्षर *);
पूर्णांक	core_tpg_set_initiator_node_queue_depth(काष्ठा se_node_acl *, u32);
पूर्णांक	core_tpg_set_initiator_node_tag(काष्ठा se_portal_group *,
		काष्ठा se_node_acl *, स्थिर अक्षर *);
पूर्णांक	core_tpg_रेजिस्टर(काष्ठा se_wwn *, काष्ठा se_portal_group *, पूर्णांक);
पूर्णांक	core_tpg_deरेजिस्टर(काष्ठा se_portal_group *);

पूर्णांक	target_alloc_sgl(काष्ठा scatterlist **sgl, अचिन्हित पूर्णांक *nents,
		u32 length, bool zero_page, bool chainable);
व्योम	target_मुक्त_sgl(काष्ठा scatterlist *sgl, पूर्णांक nents);

/*
 * The LIO target core uses DMA_TO_DEVICE to mean that data is going
 * to the target (eg handling a WRITE) and DMA_FROM_DEVICE to mean
 * that data is coming from the target (eg handling a READ).  However,
 * this is just the opposite of what we have to tell the DMA mapping
 * layer -- eg when handling a READ, the HBA will have to DMA the data
 * out of memory so it can send it to the initiator, which means we
 * need to use DMA_TO_DEVICE when we map the data.
 */
अटल अंतरभूत क्रमागत dma_data_direction
target_reverse_dma_direction(काष्ठा se_cmd *se_cmd)
अणु
	अगर (se_cmd->se_cmd_flags & SCF_BIDI)
		वापस DMA_BIसूचीECTIONAL;

	चयन (se_cmd->data_direction) अणु
	हाल DMA_TO_DEVICE:
		वापस DMA_FROM_DEVICE;
	हाल DMA_FROM_DEVICE:
		वापस DMA_TO_DEVICE;
	हाल DMA_NONE:
	शेष:
		वापस DMA_NONE;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* TARGET_CORE_FABRICH */
