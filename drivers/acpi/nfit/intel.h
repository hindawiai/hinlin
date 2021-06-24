<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 * Intel specअगरic definitions क्रम NVDIMM Firmware Interface Table - NFIT
 */
#अगर_अघोषित _NFIT_INTEL_H_
#घोषणा _NFIT_INTEL_H_

#घोषणा ND_INTEL_SMART 1

#घोषणा ND_INTEL_SMART_SHUTDOWN_COUNT_VALID     (1 << 5)
#घोषणा ND_INTEL_SMART_SHUTDOWN_VALID           (1 << 10)

काष्ठा nd_पूर्णांकel_smart अणु
	u32 status;
	जोड़ अणु
		काष्ठा अणु
			u32 flags;
			u8 reserved0[4];
			u8 health;
			u8 spares;
			u8 lअगरe_used;
			u8 alarm_flags;
			u16 media_temperature;
			u16 ctrl_temperature;
			u32 shutकरोwn_count;
			u8 ait_status;
			u16 pmic_temperature;
			u8 reserved1[8];
			u8 shutकरोwn_state;
			u32 venकरोr_size;
			u8 venकरोr_data[92];
		पूर्ण __packed;
		u8 data[128];
	पूर्ण;
पूर्ण __packed;

बाह्य स्थिर काष्ठा nvdimm_security_ops *पूर्णांकel_security_ops;

#घोषणा ND_INTEL_STATUS_SIZE		4
#घोषणा ND_INTEL_PASSPHRASE_SIZE	32

#घोषणा ND_INTEL_STATUS_NOT_SUPPORTED	1
#घोषणा ND_INTEL_STATUS_RETRY		5
#घोषणा ND_INTEL_STATUS_NOT_READY	9
#घोषणा ND_INTEL_STATUS_INVALID_STATE	10
#घोषणा ND_INTEL_STATUS_INVALID_PASS	11
#घोषणा ND_INTEL_STATUS_OVERWRITE_UNSUPPORTED	0x10007
#घोषणा ND_INTEL_STATUS_OQUERY_INPROGRESS	0x10007
#घोषणा ND_INTEL_STATUS_OQUERY_SEQUENCE_ERR	0x20007

#घोषणा ND_INTEL_SEC_STATE_ENABLED	0x02
#घोषणा ND_INTEL_SEC_STATE_LOCKED	0x04
#घोषणा ND_INTEL_SEC_STATE_FROZEN	0x08
#घोषणा ND_INTEL_SEC_STATE_PLIMIT	0x10
#घोषणा ND_INTEL_SEC_STATE_UNSUPPORTED	0x20
#घोषणा ND_INTEL_SEC_STATE_OVERWRITE	0x40

#घोषणा ND_INTEL_SEC_ESTATE_ENABLED	0x01
#घोषणा ND_INTEL_SEC_ESTATE_PLIMIT	0x02

काष्ठा nd_पूर्णांकel_get_security_state अणु
	u32 status;
	u8 extended_state;
	u8 reserved[3];
	u8 state;
	u8 reserved1[3];
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_set_passphrase अणु
	u8 old_pass[ND_INTEL_PASSPHRASE_SIZE];
	u8 new_pass[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_unlock_unit अणु
	u8 passphrase[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_disable_passphrase अणु
	u8 passphrase[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_मुक्तze_lock अणु
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_secure_erase अणु
	u8 passphrase[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_overग_लिखो अणु
	u8 passphrase[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_query_overग_लिखो अणु
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_set_master_passphrase अणु
	u8 old_pass[ND_INTEL_PASSPHRASE_SIZE];
	u8 new_pass[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

काष्ठा nd_पूर्णांकel_master_secure_erase अणु
	u8 passphrase[ND_INTEL_PASSPHRASE_SIZE];
	u32 status;
पूर्ण __packed;

#घोषणा ND_INTEL_FWA_IDLE 0
#घोषणा ND_INTEL_FWA_ARMED 1
#घोषणा ND_INTEL_FWA_BUSY 2

#घोषणा ND_INTEL_DIMM_FWA_NONE 0
#घोषणा ND_INTEL_DIMM_FWA_NOTSTAGED 1
#घोषणा ND_INTEL_DIMM_FWA_SUCCESS 2
#घोषणा ND_INTEL_DIMM_FWA_NEEDRESET 3
#घोषणा ND_INTEL_DIMM_FWA_MEDIAFAILED 4
#घोषणा ND_INTEL_DIMM_FWA_ABORT 5
#घोषणा ND_INTEL_DIMM_FWA_NOTSUPP 6
#घोषणा ND_INTEL_DIMM_FWA_ERROR 7

काष्ठा nd_पूर्णांकel_fw_activate_dimminfo अणु
	u32 status;
	u16 result;
	u8 state;
	u8 reserved[7];
पूर्ण __packed;

#घोषणा ND_INTEL_DIMM_FWA_ARM 1
#घोषणा ND_INTEL_DIMM_FWA_DISARM 0

काष्ठा nd_पूर्णांकel_fw_activate_arm अणु
	u8 activate_arm;
	u32 status;
पूर्ण __packed;

/* Root device command payloads */
#घोषणा ND_INTEL_BUS_FWA_CAP_FWQUIESCE (1 << 0)
#घोषणा ND_INTEL_BUS_FWA_CAP_OSQUIESCE (1 << 1)
#घोषणा ND_INTEL_BUS_FWA_CAP_RESET     (1 << 2)

काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo अणु
	u32 status;
	u16 reserved;
	u8 state;
	u8 capability;
	u64 activate_पंचांगo;
	u64 cpu_quiesce_पंचांगo;
	u64 io_quiesce_पंचांगo;
	u64 max_quiesce_पंचांगo;
पूर्ण __packed;

#घोषणा ND_INTEL_BUS_FWA_STATUS_NOARM  (6 | 1 << 16)
#घोषणा ND_INTEL_BUS_FWA_STATUS_BUSY   (6 | 2 << 16)
#घोषणा ND_INTEL_BUS_FWA_STATUS_NOFW   (6 | 3 << 16)
#घोषणा ND_INTEL_BUS_FWA_STATUS_TMO    (6 | 4 << 16)
#घोषणा ND_INTEL_BUS_FWA_STATUS_NOIDLE (6 | 5 << 16)
#घोषणा ND_INTEL_BUS_FWA_STATUS_ABORT  (6 | 6 << 16)

#घोषणा ND_INTEL_BUS_FWA_IODEV_FORCE_IDLE (0)
#घोषणा ND_INTEL_BUS_FWA_IODEV_OS_IDLE (1)
काष्ठा nd_पूर्णांकel_bus_fw_activate अणु
	u8 iodev_state;
	u32 status;
पूर्ण __packed;

बाह्य स्थिर काष्ठा nvdimm_fw_ops *पूर्णांकel_fw_ops;
बाह्य स्थिर काष्ठा nvdimm_bus_fw_ops *पूर्णांकel_bus_fw_ops;
#पूर्ण_अगर
