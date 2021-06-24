<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * SPU info काष्ठाures
 *
 * (C) Copyright 2006 IBM Corp.
 *
 * Author: Dwayne Grant McConnell <decimal@us.ibm.com>
 */

#अगर_अघोषित _UAPI_SPU_INFO_H
#घोषणा _UAPI_SPU_INFO_H

#समावेश <linux/types.h>

#अगर_अघोषित __KERNEL__
काष्ठा mfc_cq_sr अणु
	__u64 mfc_cq_data0_RW;
	__u64 mfc_cq_data1_RW;
	__u64 mfc_cq_data2_RW;
	__u64 mfc_cq_data3_RW;
पूर्ण;
#पूर्ण_अगर /* __KERNEL__ */

काष्ठा spu_dma_info अणु
	__u64 dma_info_type;
	__u64 dma_info_mask;
	__u64 dma_info_status;
	__u64 dma_info_stall_and_notअगरy;
	__u64 dma_info_atomic_command_status;
	काष्ठा mfc_cq_sr dma_info_command_data[16];
पूर्ण;

काष्ठा spu_proxydma_info अणु
	__u64 proxydma_info_type;
	__u64 proxydma_info_mask;
	__u64 proxydma_info_status;
	काष्ठा mfc_cq_sr proxydma_info_command_data[8];
पूर्ण;

#पूर्ण_अगर /* _UAPI_SPU_INFO_H */
