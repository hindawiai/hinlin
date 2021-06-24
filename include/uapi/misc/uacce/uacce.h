<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _UAPIUUACCE_H
#घोषणा _UAPIUUACCE_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * UACCE_CMD_START_Q: Start queue
 */
#घोषणा UACCE_CMD_START_Q	_IO('W', 0)

/*
 * UACCE_CMD_PUT_Q:
 * User actively stop queue and मुक्त queue resource immediately
 * Optimization method since बंद fd may delay
 */
#घोषणा UACCE_CMD_PUT_Q		_IO('W', 1)

/*
 * UACCE Device flags:
 * UACCE_DEV_SVA: Shared Virtual Addresses
 *		  Support PASID
 *		  Support device page faults (PCI PRI or SMMU Stall)
 */
#घोषणा UACCE_DEV_SVA		BIT(0)

/**
 * क्रमागत uacce_qfrt: queue file region type
 * @UACCE_QFRT_MMIO: device mmio region
 * @UACCE_QFRT_DUS: device user share region
 */
क्रमागत uacce_qfrt अणु
	UACCE_QFRT_MMIO = 0,
	UACCE_QFRT_DUS = 1,
पूर्ण;

#पूर्ण_अगर
