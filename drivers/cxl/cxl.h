<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright(c) 2020 Intel Corporation. */

#अगर_अघोषित __CXL_H__
#घोषणा __CXL_H__

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>

/* CXL 2.0 8.2.8.1 Device Capabilities Array Register */
#घोषणा CXLDEV_CAP_ARRAY_OFFSET 0x0
#घोषणा   CXLDEV_CAP_ARRAY_CAP_ID 0
#घोषणा   CXLDEV_CAP_ARRAY_ID_MASK GENMASK_ULL(15, 0)
#घोषणा   CXLDEV_CAP_ARRAY_COUNT_MASK GENMASK_ULL(47, 32)
/* CXL 2.0 8.2.8.2 CXL Device Capability Header Register */
#घोषणा CXLDEV_CAP_HDR_CAP_ID_MASK GENMASK(15, 0)
/* CXL 2.0 8.2.8.2.1 CXL Device Capabilities */
#घोषणा CXLDEV_CAP_CAP_ID_DEVICE_STATUS 0x1
#घोषणा CXLDEV_CAP_CAP_ID_PRIMARY_MAILBOX 0x2
#घोषणा CXLDEV_CAP_CAP_ID_SECONDARY_MAILBOX 0x3
#घोषणा CXLDEV_CAP_CAP_ID_MEMDEV 0x4000

/* CXL 2.0 8.2.8.4 Mailbox Registers */
#घोषणा CXLDEV_MBOX_CAPS_OFFSET 0x00
#घोषणा   CXLDEV_MBOX_CAP_PAYLOAD_SIZE_MASK GENMASK(4, 0)
#घोषणा CXLDEV_MBOX_CTRL_OFFSET 0x04
#घोषणा   CXLDEV_MBOX_CTRL_DOORBELL BIT(0)
#घोषणा CXLDEV_MBOX_CMD_OFFSET 0x08
#घोषणा   CXLDEV_MBOX_CMD_COMMAND_OPCODE_MASK GENMASK_ULL(15, 0)
#घोषणा   CXLDEV_MBOX_CMD_PAYLOAD_LENGTH_MASK GENMASK_ULL(36, 16)
#घोषणा CXLDEV_MBOX_STATUS_OFFSET 0x10
#घोषणा   CXLDEV_MBOX_STATUS_RET_CODE_MASK GENMASK_ULL(47, 32)
#घोषणा CXLDEV_MBOX_BG_CMD_STATUS_OFFSET 0x18
#घोषणा CXLDEV_MBOX_PAYLOAD_OFFSET 0x20

/* CXL 2.0 8.2.8.5.1.1 Memory Device Status Register */
#घोषणा CXLMDEV_STATUS_OFFSET 0x0
#घोषणा   CXLMDEV_DEV_FATAL BIT(0)
#घोषणा   CXLMDEV_FW_HALT BIT(1)
#घोषणा   CXLMDEV_STATUS_MEDIA_STATUS_MASK GENMASK(3, 2)
#घोषणा     CXLMDEV_MS_NOT_READY 0
#घोषणा     CXLMDEV_MS_READY 1
#घोषणा     CXLMDEV_MS_ERROR 2
#घोषणा     CXLMDEV_MS_DISABLED 3
#घोषणा CXLMDEV_READY(status)                                                  \
	(FIELD_GET(CXLMDEV_STATUS_MEDIA_STATUS_MASK, status) ==                \
	 CXLMDEV_MS_READY)
#घोषणा   CXLMDEV_MBOX_IF_READY BIT(4)
#घोषणा   CXLMDEV_RESET_NEEDED_MASK GENMASK(7, 5)
#घोषणा     CXLMDEV_RESET_NEEDED_NOT 0
#घोषणा     CXLMDEV_RESET_NEEDED_COLD 1
#घोषणा     CXLMDEV_RESET_NEEDED_WARM 2
#घोषणा     CXLMDEV_RESET_NEEDED_HOT 3
#घोषणा     CXLMDEV_RESET_NEEDED_CXL 4
#घोषणा CXLMDEV_RESET_NEEDED(status)                                           \
	(FIELD_GET(CXLMDEV_RESET_NEEDED_MASK, status) !=                       \
	 CXLMDEV_RESET_NEEDED_NOT)

काष्ठा cxl_memdev;
/**
 * काष्ठा cxl_mem - A CXL memory device
 * @pdev: The PCI device associated with this CXL device.
 * @regs: IO mappings to the device's MMIO
 * @status_regs: CXL 2.0 8.2.8.3 Device Status Registers
 * @mbox_regs: CXL 2.0 8.2.8.4 Mailbox Registers
 * @memdev_regs: CXL 2.0 8.2.8.5 Memory Device Registers
 * @payload_size: Size of space क्रम payload
 *                (CXL 2.0 8.2.8.4.3 Mailbox Capabilities Register)
 * @mbox_mutex: Mutex to synchronize mailbox access.
 * @firmware_version: Firmware version क्रम the memory device.
 * @enabled_commands: Hardware commands found enabled in CEL.
 * @pmem_range: Persistent memory capacity inक्रमmation.
 * @ram_range: Volatile memory capacity inक्रमmation.
 */
काष्ठा cxl_mem अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *regs;
	काष्ठा cxl_memdev *cxlmd;

	व्योम __iomem *status_regs;
	व्योम __iomem *mbox_regs;
	व्योम __iomem *memdev_regs;

	माप_प्रकार payload_size;
	काष्ठा mutex mbox_mutex; /* Protects device mailbox and firmware */
	अक्षर firmware_version[0x10];
	अचिन्हित दीर्घ *enabled_cmds;

	काष्ठा range pmem_range;
	काष्ठा range ram_range;
पूर्ण;

बाह्य काष्ठा bus_type cxl_bus_type;
#पूर्ण_अगर /* __CXL_H__ */
