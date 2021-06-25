<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright 2018-2020 Broadcom.
 */

#अगर_अघोषित __UAPI_LINUX_MISC_BCM_VK_H
#घोषणा __UAPI_LINUX_MISC_BCM_VK_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा BCM_VK_MAX_खाताNAME 64

काष्ठा vk_image अणु
	__u32 type; /* Type of image */
#घोषणा VK_IMAGE_TYPE_BOOT1 1 /* 1st stage (load to SRAM) */
#घोषणा VK_IMAGE_TYPE_BOOT2 2 /* 2nd stage (load to DDR) */
	__u8 filename[BCM_VK_MAX_खाताNAME]; /* Filename of image */
पूर्ण;

काष्ठा vk_reset अणु
	__u32 arg1;
	__u32 arg2;
पूर्ण;

#घोषणा VK_MAGIC		0x5e

/* Load image to Valkyrie */
#घोषणा VK_IOCTL_LOAD_IMAGE	_IOW(VK_MAGIC, 0x2, काष्ठा vk_image)

/* Send Reset to Valkyrie */
#घोषणा VK_IOCTL_RESET		_IOW(VK_MAGIC, 0x4, काष्ठा vk_reset)

/*
 * Firmware Status accessed directly via BAR space
 */
#घोषणा VK_BAR_FWSTS			0x41c
#घोषणा VK_BAR_COP_FWSTS		0x428
/* VK_FWSTS definitions */
#घोषणा VK_FWSTS_RELOCATION_ENTRY	(1UL << 0)
#घोषणा VK_FWSTS_RELOCATION_EXIT	(1UL << 1)
#घोषणा VK_FWSTS_INIT_START		(1UL << 2)
#घोषणा VK_FWSTS_ARCH_INIT_DONE		(1UL << 3)
#घोषणा VK_FWSTS_PRE_KNL1_INIT_DONE	(1UL << 4)
#घोषणा VK_FWSTS_PRE_KNL2_INIT_DONE	(1UL << 5)
#घोषणा VK_FWSTS_POST_KNL_INIT_DONE	(1UL << 6)
#घोषणा VK_FWSTS_INIT_DONE		(1UL << 7)
#घोषणा VK_FWSTS_APP_INIT_START		(1UL << 8)
#घोषणा VK_FWSTS_APP_INIT_DONE		(1UL << 9)
#घोषणा VK_FWSTS_MASK			0xffffffff
#घोषणा VK_FWSTS_READY			(VK_FWSTS_INIT_START | \
					 VK_FWSTS_ARCH_INIT_DONE | \
					 VK_FWSTS_PRE_KNL1_INIT_DONE | \
					 VK_FWSTS_PRE_KNL2_INIT_DONE | \
					 VK_FWSTS_POST_KNL_INIT_DONE | \
					 VK_FWSTS_INIT_DONE | \
					 VK_FWSTS_APP_INIT_START | \
					 VK_FWSTS_APP_INIT_DONE)
/* Deinit */
#घोषणा VK_FWSTS_APP_DEINIT_START	(1UL << 23)
#घोषणा VK_FWSTS_APP_DEINIT_DONE	(1UL << 24)
#घोषणा VK_FWSTS_DRV_DEINIT_START	(1UL << 25)
#घोषणा VK_FWSTS_DRV_DEINIT_DONE	(1UL << 26)
#घोषणा VK_FWSTS_RESET_DONE		(1UL << 27)
#घोषणा VK_FWSTS_DEINIT_TRIGGERED	(VK_FWSTS_APP_DEINIT_START | \
					 VK_FWSTS_APP_DEINIT_DONE  | \
					 VK_FWSTS_DRV_DEINIT_START | \
					 VK_FWSTS_DRV_DEINIT_DONE)
/* Last nibble क्रम reboot reason */
#घोषणा VK_FWSTS_RESET_REASON_SHIFT	28
#घोषणा VK_FWSTS_RESET_REASON_MASK	(0xf << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_SYS_PWRUP	(0x0 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_MBOX_DB		(0x1 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_M7_WDOG		(0x2 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_TEMP		(0x3 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_PCI_FLR		(0x4 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_PCI_HOT		(0x5 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_PCI_WARM		(0x6 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_PCI_COLD		(0x7 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_L1		(0x8 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_L0		(0x9 << VK_FWSTS_RESET_REASON_SHIFT)
#घोषणा VK_FWSTS_RESET_UNKNOWN		(0xf << VK_FWSTS_RESET_REASON_SHIFT)

#पूर्ण_अगर /* __UAPI_LINUX_MISC_BCM_VK_H */
