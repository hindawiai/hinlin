<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_ALUA_H
#घोषणा TARGET_CORE_ALUA_H

#समावेश <target/target_core_base.h>

/*
 * INQUIRY response data, TPGS Field
 *
 * from spc4r17 section 6.4.2 Table 135
 */
#घोषणा TPGS_NO_ALUA				0x00
#घोषणा TPGS_IMPLICIT_ALUA			0x10
#घोषणा TPGS_EXPLICIT_ALUA			0x20

/*
 * ASYMMETRIC ACCESS STATE field
 *
 * from spc4r36j section 6.37 Table 307
 */
#घोषणा ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED	0x0
#घोषणा ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED	0x1
#घोषणा ALUA_ACCESS_STATE_STANDBY		0x2
#घोषणा ALUA_ACCESS_STATE_UNAVAILABLE		0x3
#घोषणा ALUA_ACCESS_STATE_LBA_DEPENDENT		0x4
#घोषणा ALUA_ACCESS_STATE_OFFLINE		0xe
#घोषणा ALUA_ACCESS_STATE_TRANSITION		0xf

/*
 * from spc4r36j section 6.37 Table 306
 */
#घोषणा ALUA_T_SUP		0x80
#घोषणा ALUA_O_SUP		0x40
#घोषणा ALUA_LBD_SUP		0x10
#घोषणा ALUA_U_SUP		0x08
#घोषणा ALUA_S_SUP		0x04
#घोषणा ALUA_AN_SUP		0x02
#घोषणा ALUA_AO_SUP		0x01

/*
 * REPORT_TARGET_PORT_GROUP STATUS CODE
 *
 * from spc4r17 section 6.27 Table 246
 */
#घोषणा ALUA_STATUS_NONE				0x00
#घोषणा ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG		0x01
#घोषणा ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA		0x02

/*
 * From spc4r17, Table D.1: ASC and ASCQ Assignement
 */
#घोषणा ASCQ_04H_ALUA_STATE_TRANSITION			0x0a
#घोषणा ASCQ_04H_ALUA_TG_PT_STANDBY			0x0b
#घोषणा ASCQ_04H_ALUA_TG_PT_UNAVAILABLE			0x0c
#घोषणा ASCQ_04H_ALUA_OFFLINE				0x12

/*
 * Used as the शेष क्रम Active/NonOptimized delay (in milliseconds)
 * This can also be changed via configfs on a per target port group basis..
 */
#घोषणा ALUA_DEFAULT_NONOP_DELAY_MSECS			100
#घोषणा ALUA_MAX_NONOP_DELAY_MSECS			10000 /* 10 seconds */
/*
 * Used क्रम implicit and explicit ALUA transitional delay, that is disabled
 * by शेष, and is पूर्णांकended to be used क्रम debugging client side ALUA code.
 */
#घोषणा ALUA_DEFAULT_TRANS_DELAY_MSECS			0
#घोषणा ALUA_MAX_TRANS_DELAY_MSECS			30000 /* 30 seconds */
/*
 * Used क्रम the recommended application client implicit transition समयout
 * in seconds, वापसed by the REPORT_TARGET_PORT_GROUPS w/ extended header.
 */
#घोषणा ALUA_DEFAULT_IMPLICIT_TRANS_SECS			0
#घोषणा ALUA_MAX_IMPLICIT_TRANS_SECS			255

/* Used by core_alua_update_tpg_(primary,secondary)_metadata */
#घोषणा ALUA_MD_BUF_LEN					1024

बाह्य काष्ठा kmem_cache *t10_alua_lu_gp_cache;
बाह्य काष्ठा kmem_cache *t10_alua_lu_gp_mem_cache;
बाह्य काष्ठा kmem_cache *t10_alua_tg_pt_gp_cache;
बाह्य काष्ठा kmem_cache *t10_alua_lba_map_cache;
बाह्य काष्ठा kmem_cache *t10_alua_lba_map_mem_cache;

बाह्य sense_reason_t target_emulate_report_target_port_groups(काष्ठा se_cmd *);
बाह्य sense_reason_t target_emulate_set_target_port_groups(काष्ठा se_cmd *);
बाह्य sense_reason_t target_emulate_report_referrals(काष्ठा se_cmd *);
बाह्य पूर्णांक core_alua_check_nonop_delay(काष्ठा se_cmd *);
बाह्य पूर्णांक core_alua_करो_port_transition(काष्ठा t10_alua_tg_pt_gp *,
				काष्ठा se_device *, काष्ठा se_lun *,
				काष्ठा se_node_acl *, पूर्णांक, पूर्णांक);
बाह्य अक्षर *core_alua_dump_status(पूर्णांक);
बाह्य काष्ठा t10_alua_lba_map *core_alua_allocate_lba_map(
				काष्ठा list_head *, u64, u64);
बाह्य पूर्णांक core_alua_allocate_lba_map_mem(काष्ठा t10_alua_lba_map *, पूर्णांक, पूर्णांक);
बाह्य व्योम core_alua_मुक्त_lba_map(काष्ठा list_head *);
बाह्य व्योम core_alua_set_lba_map(काष्ठा se_device *, काष्ठा list_head *,
				पूर्णांक, पूर्णांक);
बाह्य काष्ठा t10_alua_lu_gp *core_alua_allocate_lu_gp(स्थिर अक्षर *, पूर्णांक);
बाह्य पूर्णांक core_alua_set_lu_gp_id(काष्ठा t10_alua_lu_gp *, u16);
बाह्य व्योम core_alua_मुक्त_lu_gp(काष्ठा t10_alua_lu_gp *);
बाह्य व्योम core_alua_मुक्त_lu_gp_mem(काष्ठा se_device *);
बाह्य काष्ठा t10_alua_lu_gp *core_alua_get_lu_gp_by_name(स्थिर अक्षर *);
बाह्य व्योम core_alua_put_lu_gp_from_name(काष्ठा t10_alua_lu_gp *);
बाह्य व्योम __core_alua_attach_lu_gp_mem(काष्ठा t10_alua_lu_gp_member *,
					काष्ठा t10_alua_lu_gp *);
बाह्य व्योम __core_alua_drop_lu_gp_mem(काष्ठा t10_alua_lu_gp_member *,
					काष्ठा t10_alua_lu_gp *);
बाह्य व्योम core_alua_drop_lu_gp_dev(काष्ठा se_device *);
बाह्य काष्ठा t10_alua_tg_pt_gp *core_alua_allocate_tg_pt_gp(
			काष्ठा se_device *, स्थिर अक्षर *, पूर्णांक);
बाह्य पूर्णांक core_alua_set_tg_pt_gp_id(काष्ठा t10_alua_tg_pt_gp *, u16);
बाह्य व्योम core_alua_मुक्त_tg_pt_gp(काष्ठा t10_alua_tg_pt_gp *);
बाह्य व्योम target_detach_tg_pt_gp(काष्ठा se_lun *);
बाह्य व्योम target_attach_tg_pt_gp(काष्ठा se_lun *, काष्ठा t10_alua_tg_pt_gp *);
बाह्य sमाप_प्रकार core_alua_show_tg_pt_gp_info(काष्ठा se_lun *, अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_tg_pt_gp_info(काष्ठा se_lun *, स्थिर अक्षर *,
						माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_access_type(काष्ठा t10_alua_tg_pt_gp *, अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_access_type(काष्ठा t10_alua_tg_pt_gp *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_nonop_delay_msecs(काष्ठा t10_alua_tg_pt_gp *,
						अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_nonop_delay_msecs(काष्ठा t10_alua_tg_pt_gp *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_trans_delay_msecs(काष्ठा t10_alua_tg_pt_gp *,
					अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_trans_delay_msecs(काष्ठा t10_alua_tg_pt_gp *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_implicit_trans_secs(काष्ठा t10_alua_tg_pt_gp *,
					अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_implicit_trans_secs(काष्ठा t10_alua_tg_pt_gp *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_preferred_bit(काष्ठा t10_alua_tg_pt_gp *,
					अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_preferred_bit(काष्ठा t10_alua_tg_pt_gp *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_offline_bit(काष्ठा se_lun *, अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_offline_bit(काष्ठा se_lun *, स्थिर अक्षर *,
					माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_secondary_status(काष्ठा se_lun *, अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_secondary_status(काष्ठा se_lun *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार core_alua_show_secondary_ग_लिखो_metadata(काष्ठा se_lun *,
					अक्षर *);
बाह्य sमाप_प्रकार core_alua_store_secondary_ग_लिखो_metadata(काष्ठा se_lun *,
					स्थिर अक्षर *, माप_प्रकार);
बाह्य पूर्णांक core_setup_alua(काष्ठा se_device *);
बाह्य sense_reason_t target_alua_state_check(काष्ठा se_cmd *cmd);

#पूर्ण_अगर /* TARGET_CORE_ALUA_H */
