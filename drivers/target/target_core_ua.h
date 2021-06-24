<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_UA_H
#घोषणा TARGET_CORE_UA_H

#समावेश <target/target_core_base.h>

/*
 * From spc4r17, Table D.1: ASC and ASCQ Assignement
 */
#घोषणा ASCQ_29H_POWER_ON_RESET_OR_BUS_DEVICE_RESET_OCCURED	0x00
#घोषणा ASCQ_29H_POWER_ON_OCCURRED				0x01
#घोषणा ASCQ_29H_SCSI_BUS_RESET_OCCURED				0x02
#घोषणा ASCQ_29H_BUS_DEVICE_RESET_FUNCTION_OCCURRED		0x03
#घोषणा ASCQ_29H_DEVICE_INTERNAL_RESET				0x04
#घोषणा ASCQ_29H_TRANSCEIVER_MODE_CHANGED_TO_SINGLE_ENDED	0x05
#घोषणा ASCQ_29H_TRANSCEIVER_MODE_CHANGED_TO_LVD		0x06
#घोषणा ASCQ_29H_NEXUS_LOSS_OCCURRED				0x07

#घोषणा ASCQ_2AH_PARAMETERS_CHANGED				0x00
#घोषणा ASCQ_2AH_MODE_PARAMETERS_CHANGED			0x01
#घोषणा ASCQ_2AH_LOG_PARAMETERS_CHANGED				0x02
#घोषणा ASCQ_2AH_RESERVATIONS_PREEMPTED				0x03
#घोषणा ASCQ_2AH_RESERVATIONS_RELEASED				0x04
#घोषणा ASCQ_2AH_REGISTRATIONS_PREEMPTED			0x05
#घोषणा ASCQ_2AH_ASYMMETRIC_ACCESS_STATE_CHANGED		0x06
#घोषणा ASCQ_2AH_IMPLICIT_ASYMMETRIC_ACCESS_STATE_TRANSITION_FAILED 0x07
#घोषणा ASCQ_2AH_PRIORITY_CHANGED				0x08

#घोषणा ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS		0x09

#घोषणा ASCQ_3FH_INQUIRY_DATA_HAS_CHANGED			0x03
#घोषणा ASCQ_3FH_REPORTED_LUNS_DATA_HAS_CHANGED			0x0E

बाह्य काष्ठा kmem_cache *se_ua_cache;

बाह्य sense_reason_t target_scsi3_ua_check(काष्ठा se_cmd *);
बाह्य पूर्णांक core_scsi3_ua_allocate(काष्ठा se_dev_entry *, u8, u8);
बाह्य व्योम target_ua_allocate_lun(काष्ठा se_node_acl *, u32, u8, u8);
बाह्य व्योम core_scsi3_ua_release_all(काष्ठा se_dev_entry *);
बाह्य bool core_scsi3_ua_क्रम_check_condition(काष्ठा se_cmd *, u8 *, u8 *,
					      u8 *);
बाह्य पूर्णांक core_scsi3_ua_clear_क्रम_request_sense(काष्ठा se_cmd *,
						u8 *, u8 *);

#पूर्ण_अगर /* TARGET_CORE_UA_H */
