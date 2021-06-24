<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_PR_H
#घोषणा TARGET_CORE_PR_H

#समावेश <linux/types.h>
#समावेश <target/target_core_base.h>

/*
 * PERSISTENT_RESERVE_OUT service action codes
 *
 * spc5r04b section 6.15.2 Table 174
 */
#घोषणा PRO_REGISTER				0x00
#घोषणा PRO_RESERVE				0x01
#घोषणा PRO_RELEASE				0x02
#घोषणा PRO_CLEAR				0x03
#घोषणा PRO_PREEMPT				0x04
#घोषणा PRO_PREEMPT_AND_ABORT			0x05
#घोषणा PRO_REGISTER_AND_IGNORE_EXISTING_KEY	0x06
#घोषणा PRO_REGISTER_AND_MOVE			0x07
#घोषणा PRO_REPLACE_LOST_RESERVATION	0x08
/*
 * PERSISTENT_RESERVE_IN service action codes
 *
 * spc5r04b section 6.14.1 Table 162
 */
#घोषणा PRI_READ_KEYS				0x00
#घोषणा PRI_READ_RESERVATION			0x01
#घोषणा PRI_REPORT_CAPABILITIES			0x02
#घोषणा PRI_READ_FULL_STATUS			0x03
/*
 * PERSISTENT_RESERVE_ SCOPE field
 *
 * spc5r04b section 6.14.3.2 Table 166
 */
#घोषणा PR_SCOPE_LU_SCOPE			0x00
/*
 * PERSISTENT_RESERVE_* TYPE field
 *
 * spc5r04b section 6.14.3.3 Table 167
 */
#घोषणा PR_TYPE_WRITE_EXCLUSIVE			0x01
#घोषणा PR_TYPE_EXCLUSIVE_ACCESS		0x03
#घोषणा PR_TYPE_WRITE_EXCLUSIVE_REGONLY		0x05
#घोषणा PR_TYPE_EXCLUSIVE_ACCESS_REGONLY	0x06
#घोषणा PR_TYPE_WRITE_EXCLUSIVE_ALLREG		0x07
#घोषणा PR_TYPE_EXCLUSIVE_ACCESS_ALLREG		0x08

#घोषणा PR_APTPL_MAX_IPORT_LEN			256
#घोषणा PR_APTPL_MAX_TPORT_LEN			256

/*
 *  Function defined in target_core_spc.c
 */
व्योम spc_parse_naa_6h_venकरोr_specअगरic(काष्ठा se_device *, अचिन्हित अक्षर *);

बाह्य काष्ठा kmem_cache *t10_pr_reg_cache;

बाह्य व्योम core_pr_dump_initiator_port(काष्ठा t10_pr_registration *,
			अक्षर *, u32);
बाह्य व्योम target_release_reservation(काष्ठा se_device *dev);
बाह्य sense_reason_t target_scsi2_reservation_release(काष्ठा se_cmd *);
बाह्य sense_reason_t target_scsi2_reservation_reserve(काष्ठा se_cmd *);
बाह्य पूर्णांक core_scsi3_alloc_aptpl_registration(
			काष्ठा t10_reservation *, u64,
			अचिन्हित अक्षर *, अचिन्हित अक्षर *, u64,
			अचिन्हित अक्षर *, u16, u64, पूर्णांक, पूर्णांक, u8);
बाह्य पूर्णांक core_scsi3_check_aptpl_registration(काष्ठा se_device *,
			काष्ठा se_portal_group *, काष्ठा se_lun *,
			काष्ठा se_node_acl *, u64);
बाह्य व्योम core_scsi3_मुक्त_pr_reg_from_nacl(काष्ठा se_device *,
					     काष्ठा se_node_acl *);
बाह्य व्योम core_scsi3_मुक्त_all_registrations(काष्ठा se_device *);
बाह्य अचिन्हित अक्षर *core_scsi3_pr_dump_type(पूर्णांक);

बाह्य sense_reason_t target_scsi3_emulate_pr_in(काष्ठा se_cmd *);
बाह्य sense_reason_t target_scsi3_emulate_pr_out(काष्ठा se_cmd *);
बाह्य sense_reason_t target_check_reservation(काष्ठा se_cmd *);

#पूर्ण_अगर /* TARGET_CORE_PR_H */
