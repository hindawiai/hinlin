<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  dcdbas.h: Definitions क्रम Dell Systems Management Base driver
 *
 *  Copyright (C) 1995-2005 Dell Inc.
 */

#अगर_अघोषित _DCDBAS_H_
#घोषणा _DCDBAS_H_

#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#घोषणा MAX_SMI_DATA_BUF_SIZE			(256 * 1024)

#घोषणा HC_ACTION_NONE				(0)
#घोषणा HC_ACTION_HOST_CONTROL_POWEROFF		BIT(1)
#घोषणा HC_ACTION_HOST_CONTROL_POWERCYCLE	BIT(2)

#घोषणा HC_SMITYPE_NONE				(0)
#घोषणा HC_SMITYPE_TYPE1			(1)
#घोषणा HC_SMITYPE_TYPE2			(2)
#घोषणा HC_SMITYPE_TYPE3			(3)

#घोषणा ESM_APM_CMD				(0x0A0)
#घोषणा ESM_APM_POWER_CYCLE			(0x10)
#घोषणा ESM_STATUS_CMD_UNSUCCESSFUL		(-1)

#घोषणा CMOS_BASE_PORT				(0x070)
#घोषणा CMOS_PAGE1_INDEX_PORT			(0)
#घोषणा CMOS_PAGE1_DATA_PORT			(1)
#घोषणा CMOS_PAGE2_INDEX_PORT_PIIX4		(2)
#घोषणा CMOS_PAGE2_DATA_PORT_PIIX4		(3)
#घोषणा PE1400_APM_CONTROL_PORT			(0x0B0)
#घोषणा PCAT_APM_CONTROL_PORT			(0x0B2)
#घोषणा PCAT_APM_STATUS_PORT			(0x0B3)
#घोषणा PE1300_CMOS_CMD_STRUCT_PTR		(0x38)
#घोषणा PE1400_CMOS_CMD_STRUCT_PTR		(0x70)

#घोषणा MAX_SYSMGMT_SHORTCMD_PARMBUF_LEN	(14)
#घोषणा MAX_SYSMGMT_LONGCMD_SGENTRY_NUM		(16)

#घोषणा TIMEOUT_USEC_SHORT_SEMA_BLOCKING	(10000)
#घोषणा EXPIRED_TIMER				(0)

#घोषणा SMI_CMD_MAGIC				(0x534D4931)
#घोषणा SMM_EPS_SIG				"$SCB"

#घोषणा DCDBAS_DEV_ATTR_RW(_name) \
	DEVICE_ATTR(_name,0600,_name##_show,_name##_store);

#घोषणा DCDBAS_DEV_ATTR_RO(_name) \
	DEVICE_ATTR(_name,0400,_name##_show,शून्य);

#घोषणा DCDBAS_DEV_ATTR_WO(_name) \
	DEVICE_ATTR(_name,0200,शून्य,_name##_store);

#घोषणा DCDBAS_BIN_ATTR_RW(_name) \
काष्ठा bin_attribute bin_attr_##_name = अणु \
	.attr =  अणु .name = __stringअगरy(_name), \
		   .mode = 0600 पूर्ण, \
	.पढ़ो =  _name##_पढ़ो, \
	.ग_लिखो = _name##_ग_लिखो, \
पूर्ण

काष्ठा smi_cmd अणु
	__u32 magic;
	__u32 ebx;
	__u32 ecx;
	__u16 command_address;
	__u8 command_code;
	__u8 reserved;
	__u8 command_buffer[1];
पूर्ण __attribute__ ((packed));

काष्ठा apm_cmd अणु
	__u8 command;
	__s8 status;
	__u16 reserved;
	जोड़ अणु
		काष्ठा अणु
			__u8 parm[MAX_SYSMGMT_SHORTCMD_PARMBUF_LEN];
		पूर्ण __attribute__ ((packed)) लघुreq;

		काष्ठा अणु
			__u16 num_sg_entries;
			काष्ठा अणु
				__u32 size;
				__u64 addr;
			पूर्ण __attribute__ ((packed))
			    sglist[MAX_SYSMGMT_LONGCMD_SGENTRY_NUM];
		पूर्ण __attribute__ ((packed)) दीर्घreq;
	पूर्ण __attribute__ ((packed)) parameters;
पूर्ण __attribute__ ((packed));

पूर्णांक dcdbas_smi_request(काष्ठा smi_cmd *smi_cmd);

काष्ठा smm_eps_table अणु
	अक्षर smm_comm_buff_anchor[4];
	u8 length;
	u8 checksum;
	u8 version;
	u64 smm_comm_buff_addr;
	u64 num_of_4k_pages;
पूर्ण __packed;

#पूर्ण_अगर /* _DCDBAS_H_ */

