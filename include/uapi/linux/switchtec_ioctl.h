<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Microsemi Switchtec PCIe Driver
 * Copyright (c) 2017, Microsemi Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 */

#अगर_अघोषित _UAPI_LINUX_SWITCHTEC_IOCTL_H
#घोषणा _UAPI_LINUX_SWITCHTEC_IOCTL_H

#समावेश <linux/types.h>

#घोषणा SWITCHTEC_IOCTL_PART_CFG0	0
#घोषणा SWITCHTEC_IOCTL_PART_CFG1	1
#घोषणा SWITCHTEC_IOCTL_PART_IMG0	2
#घोषणा SWITCHTEC_IOCTL_PART_IMG1	3
#घोषणा SWITCHTEC_IOCTL_PART_NVLOG	4
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR0	5
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR1	6
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR2	7
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR3	8
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR4	9
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR5	10
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR6	11
#घोषणा SWITCHTEC_IOCTL_PART_VENDOR7	12
#घोषणा SWITCHTEC_IOCTL_PART_BL2_0	13
#घोषणा SWITCHTEC_IOCTL_PART_BL2_1	14
#घोषणा SWITCHTEC_IOCTL_PART_MAP_0	15
#घोषणा SWITCHTEC_IOCTL_PART_MAP_1	16
#घोषणा SWITCHTEC_IOCTL_PART_KEY_0	17
#घोषणा SWITCHTEC_IOCTL_PART_KEY_1	18

#घोषणा SWITCHTEC_NUM_PARTITIONS_GEN3	13
#घोषणा SWITCHTEC_NUM_PARTITIONS_GEN4	19

/* obsolete: क्रम compatibility with old userspace software */
#घोषणा SWITCHTEC_IOCTL_NUM_PARTITIONS	SWITCHTEC_NUM_PARTITIONS_GEN3

काष्ठा चयनtec_ioctl_flash_info अणु
	__u64 flash_length;
	__u32 num_partitions;
	__u32 padding;
पूर्ण;

#घोषणा SWITCHTEC_IOCTL_PART_ACTIVE  1
#घोषणा SWITCHTEC_IOCTL_PART_RUNNING 2

काष्ठा चयनtec_ioctl_flash_part_info अणु
	__u32 flash_partition;
	__u32 address;
	__u32 length;
	__u32 active;
पूर्ण;

काष्ठा चयनtec_ioctl_event_summary_legacy अणु
	__u64 global;
	__u64 part_biपंचांगap;
	__u32 local_part;
	__u32 padding;
	__u32 part[48];
	__u32 pff[48];
पूर्ण;

काष्ठा चयनtec_ioctl_event_summary अणु
	__u64 global;
	__u64 part_biपंचांगap;
	__u32 local_part;
	__u32 padding;
	__u32 part[48];
	__u32 pff[255];
पूर्ण;

#घोषणा SWITCHTEC_IOCTL_EVENT_STACK_ERROR		0
#घोषणा SWITCHTEC_IOCTL_EVENT_PPU_ERROR			1
#घोषणा SWITCHTEC_IOCTL_EVENT_ISP_ERROR			2
#घोषणा SWITCHTEC_IOCTL_EVENT_SYS_RESET			3
#घोषणा SWITCHTEC_IOCTL_EVENT_FW_EXC			4
#घोषणा SWITCHTEC_IOCTL_EVENT_FW_NMI			5
#घोषणा SWITCHTEC_IOCTL_EVENT_FW_NON_FATAL		6
#घोषणा SWITCHTEC_IOCTL_EVENT_FW_FATAL			7
#घोषणा SWITCHTEC_IOCTL_EVENT_TWI_MRPC_COMP		8
#घोषणा SWITCHTEC_IOCTL_EVENT_TWI_MRPC_COMP_ASYNC	9
#घोषणा SWITCHTEC_IOCTL_EVENT_CLI_MRPC_COMP		10
#घोषणा SWITCHTEC_IOCTL_EVENT_CLI_MRPC_COMP_ASYNC	11
#घोषणा SWITCHTEC_IOCTL_EVENT_GPIO_INT			12
#घोषणा SWITCHTEC_IOCTL_EVENT_PART_RESET		13
#घोषणा SWITCHTEC_IOCTL_EVENT_MRPC_COMP			14
#घोषणा SWITCHTEC_IOCTL_EVENT_MRPC_COMP_ASYNC		15
#घोषणा SWITCHTEC_IOCTL_EVENT_DYN_PART_BIND_COMP	16
#घोषणा SWITCHTEC_IOCTL_EVENT_AER_IN_P2P		17
#घोषणा SWITCHTEC_IOCTL_EVENT_AER_IN_VEP		18
#घोषणा SWITCHTEC_IOCTL_EVENT_DPC			19
#घोषणा SWITCHTEC_IOCTL_EVENT_CTS			20
#घोषणा SWITCHTEC_IOCTL_EVENT_HOTPLUG			21
#घोषणा SWITCHTEC_IOCTL_EVENT_IER			22
#घोषणा SWITCHTEC_IOCTL_EVENT_THRESH			23
#घोषणा SWITCHTEC_IOCTL_EVENT_POWER_MGMT		24
#घोषणा SWITCHTEC_IOCTL_EVENT_TLP_THROTTLING		25
#घोषणा SWITCHTEC_IOCTL_EVENT_FORCE_SPEED		26
#घोषणा SWITCHTEC_IOCTL_EVENT_CREDIT_TIMEOUT		27
#घोषणा SWITCHTEC_IOCTL_EVENT_LINK_STATE		28
#घोषणा SWITCHTEC_IOCTL_EVENT_GFMS			29
#घोषणा SWITCHTEC_IOCTL_EVENT_INTERCOMM_REQ_NOTIFY	30
#घोषणा SWITCHTEC_IOCTL_EVENT_UEC			31
#घोषणा SWITCHTEC_IOCTL_MAX_EVENTS			32

#घोषणा SWITCHTEC_IOCTL_EVENT_LOCAL_PART_IDX -1
#घोषणा SWITCHTEC_IOCTL_EVENT_IDX_ALL -2

#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_CLEAR     (1 << 0)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_EN_POLL   (1 << 1)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_EN_LOG    (1 << 2)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_EN_CLI    (1 << 3)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_EN_FATAL  (1 << 4)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_DIS_POLL  (1 << 5)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_DIS_LOG   (1 << 6)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_DIS_CLI   (1 << 7)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_DIS_FATAL (1 << 8)
#घोषणा SWITCHTEC_IOCTL_EVENT_FLAG_UNUSED    (~0x1ff)

काष्ठा चयनtec_ioctl_event_ctl अणु
	__u32 event_id;
	__s32 index;
	__u32 flags;
	__u32 occurred;
	__u32 count;
	__u32 data[5];
पूर्ण;

#घोषणा SWITCHTEC_IOCTL_PFF_VEP 100
काष्ठा चयनtec_ioctl_pff_port अणु
	__u32 pff;
	__u32 partition;
	__u32 port;
पूर्ण;

#घोषणा SWITCHTEC_IOCTL_FLASH_INFO \
	_IOR('W', 0x40, काष्ठा चयनtec_ioctl_flash_info)
#घोषणा SWITCHTEC_IOCTL_FLASH_PART_INFO \
	_IOWR('W', 0x41, काष्ठा चयनtec_ioctl_flash_part_info)
#घोषणा SWITCHTEC_IOCTL_EVENT_SUMMARY \
	_IOR('W', 0x42, काष्ठा चयनtec_ioctl_event_summary)
#घोषणा SWITCHTEC_IOCTL_EVENT_SUMMARY_LEGACY \
	_IOR('W', 0x42, काष्ठा चयनtec_ioctl_event_summary_legacy)
#घोषणा SWITCHTEC_IOCTL_EVENT_CTL \
	_IOWR('W', 0x43, काष्ठा चयनtec_ioctl_event_ctl)
#घोषणा SWITCHTEC_IOCTL_PFF_TO_PORT \
	_IOWR('W', 0x44, काष्ठा चयनtec_ioctl_pff_port)
#घोषणा SWITCHTEC_IOCTL_PORT_TO_PFF \
	_IOWR('W', 0x45, काष्ठा चयनtec_ioctl_pff_port)

#पूर्ण_अगर
