<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ARM Power State and Coordination Interface (PSCI) header
 *
 * This header holds common PSCI defines and macros shared
 * by: ARM kernel, ARM64 kernel, KVM ARM/ARM64 and user space.
 *
 * Copyright (C) 2014 Linaro Ltd.
 * Author: Anup Patel <anup.patel@linaro.org>
 */

#अगर_अघोषित _UAPI_LINUX_PSCI_H
#घोषणा _UAPI_LINUX_PSCI_H

/*
 * PSCI v0.1 पूर्णांकerface
 *
 * The PSCI v0.1 function numbers are implementation defined.
 *
 * Only PSCI वापस values such as: SUCCESS, NOT_SUPPORTED,
 * INVALID_PARAMS, and DENIED defined below are applicable
 * to PSCI v0.1.
 */

/* PSCI v0.2 पूर्णांकerface */
#घोषणा PSCI_0_2_FN_BASE			0x84000000
#घोषणा PSCI_0_2_FN(n)				(PSCI_0_2_FN_BASE + (n))
#घोषणा PSCI_0_2_64BIT				0x40000000
#घोषणा PSCI_0_2_FN64_BASE			\
					(PSCI_0_2_FN_BASE + PSCI_0_2_64BIT)
#घोषणा PSCI_0_2_FN64(n)			(PSCI_0_2_FN64_BASE + (n))

#घोषणा PSCI_0_2_FN_PSCI_VERSION		PSCI_0_2_FN(0)
#घोषणा PSCI_0_2_FN_CPU_SUSPEND			PSCI_0_2_FN(1)
#घोषणा PSCI_0_2_FN_CPU_OFF			PSCI_0_2_FN(2)
#घोषणा PSCI_0_2_FN_CPU_ON			PSCI_0_2_FN(3)
#घोषणा PSCI_0_2_FN_AFFINITY_INFO		PSCI_0_2_FN(4)
#घोषणा PSCI_0_2_FN_MIGRATE			PSCI_0_2_FN(5)
#घोषणा PSCI_0_2_FN_MIGRATE_INFO_TYPE		PSCI_0_2_FN(6)
#घोषणा PSCI_0_2_FN_MIGRATE_INFO_UP_CPU		PSCI_0_2_FN(7)
#घोषणा PSCI_0_2_FN_SYSTEM_OFF			PSCI_0_2_FN(8)
#घोषणा PSCI_0_2_FN_SYSTEM_RESET		PSCI_0_2_FN(9)

#घोषणा PSCI_0_2_FN64_CPU_SUSPEND		PSCI_0_2_FN64(1)
#घोषणा PSCI_0_2_FN64_CPU_ON			PSCI_0_2_FN64(3)
#घोषणा PSCI_0_2_FN64_AFFINITY_INFO		PSCI_0_2_FN64(4)
#घोषणा PSCI_0_2_FN64_MIGRATE			PSCI_0_2_FN64(5)
#घोषणा PSCI_0_2_FN64_MIGRATE_INFO_UP_CPU	PSCI_0_2_FN64(7)

#घोषणा PSCI_1_0_FN_PSCI_FEATURES		PSCI_0_2_FN(10)
#घोषणा PSCI_1_0_FN_SYSTEM_SUSPEND		PSCI_0_2_FN(14)
#घोषणा PSCI_1_0_FN_SET_SUSPEND_MODE		PSCI_0_2_FN(15)
#घोषणा PSCI_1_1_FN_SYSTEM_RESET2		PSCI_0_2_FN(18)

#घोषणा PSCI_1_0_FN64_SYSTEM_SUSPEND		PSCI_0_2_FN64(14)
#घोषणा PSCI_1_1_FN64_SYSTEM_RESET2		PSCI_0_2_FN64(18)

/* PSCI v0.2 घातer state encoding क्रम CPU_SUSPEND function */
#घोषणा PSCI_0_2_POWER_STATE_ID_MASK		0xffff
#घोषणा PSCI_0_2_POWER_STATE_ID_SHIFT		0
#घोषणा PSCI_0_2_POWER_STATE_TYPE_SHIFT		16
#घोषणा PSCI_0_2_POWER_STATE_TYPE_MASK		\
				(0x1 << PSCI_0_2_POWER_STATE_TYPE_SHIFT)
#घोषणा PSCI_0_2_POWER_STATE_AFFL_SHIFT		24
#घोषणा PSCI_0_2_POWER_STATE_AFFL_MASK		\
				(0x3 << PSCI_0_2_POWER_STATE_AFFL_SHIFT)

/* PSCI extended घातer state encoding क्रम CPU_SUSPEND function */
#घोषणा PSCI_1_0_EXT_POWER_STATE_ID_MASK	0xfffffff
#घोषणा PSCI_1_0_EXT_POWER_STATE_ID_SHIFT	0
#घोषणा PSCI_1_0_EXT_POWER_STATE_TYPE_SHIFT	30
#घोषणा PSCI_1_0_EXT_POWER_STATE_TYPE_MASK	\
				(0x1 << PSCI_1_0_EXT_POWER_STATE_TYPE_SHIFT)

/* PSCI v0.2 affinity level state वापसed by AFFINITY_INFO */
#घोषणा PSCI_0_2_AFFINITY_LEVEL_ON		0
#घोषणा PSCI_0_2_AFFINITY_LEVEL_OFF		1
#घोषणा PSCI_0_2_AFFINITY_LEVEL_ON_PENDING	2

/* PSCI v0.2 multicore support in Trusted OS वापसed by MIGRATE_INFO_TYPE */
#घोषणा PSCI_0_2_TOS_UP_MIGRATE			0
#घोषणा PSCI_0_2_TOS_UP_NO_MIGRATE		1
#घोषणा PSCI_0_2_TOS_MP				2

/* PSCI version decoding (independent of PSCI version) */
#घोषणा PSCI_VERSION_MAJOR_SHIFT		16
#घोषणा PSCI_VERSION_MINOR_MASK			\
		((1U << PSCI_VERSION_MAJOR_SHIFT) - 1)
#घोषणा PSCI_VERSION_MAJOR_MASK			~PSCI_VERSION_MINOR_MASK
#घोषणा PSCI_VERSION_MAJOR(ver)			\
		(((ver) & PSCI_VERSION_MAJOR_MASK) >> PSCI_VERSION_MAJOR_SHIFT)
#घोषणा PSCI_VERSION_MINOR(ver)			\
		((ver) & PSCI_VERSION_MINOR_MASK)
#घोषणा PSCI_VERSION(maj, min)						\
	((((maj) << PSCI_VERSION_MAJOR_SHIFT) & PSCI_VERSION_MAJOR_MASK) | \
	 ((min) & PSCI_VERSION_MINOR_MASK))

/* PSCI features decoding (>=1.0) */
#घोषणा PSCI_1_0_FEATURES_CPU_SUSPEND_PF_SHIFT	1
#घोषणा PSCI_1_0_FEATURES_CPU_SUSPEND_PF_MASK	\
			(0x1 << PSCI_1_0_FEATURES_CPU_SUSPEND_PF_SHIFT)

#घोषणा PSCI_1_0_OS_INITIATED			BIT(0)
#घोषणा PSCI_1_0_SUSPEND_MODE_PC		0
#घोषणा PSCI_1_0_SUSPEND_MODE_OSI		1

/* PSCI वापस values (inclusive of all PSCI versions) */
#घोषणा PSCI_RET_SUCCESS			0
#घोषणा PSCI_RET_NOT_SUPPORTED			-1
#घोषणा PSCI_RET_INVALID_PARAMS			-2
#घोषणा PSCI_RET_DENIED				-3
#घोषणा PSCI_RET_ALREADY_ON			-4
#घोषणा PSCI_RET_ON_PENDING			-5
#घोषणा PSCI_RET_INTERNAL_FAILURE		-6
#घोषणा PSCI_RET_NOT_PRESENT			-7
#घोषणा PSCI_RET_DISABLED			-8
#घोषणा PSCI_RET_INVALID_ADDRESS		-9

#पूर्ण_अगर /* _UAPI_LINUX_PSCI_H */
