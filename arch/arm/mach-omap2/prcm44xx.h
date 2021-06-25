<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP4 PRCM definitions
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 *
 * Paul Walmsley
 *
 * This file contains macros and functions that are common to all of
 * the PRM/CM/PRCM blocks on the OMAP4 devices: PRM, CM1, CM2,
 * PRCM_MPU, SCRM
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRCM44XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRCM44XX_H

/*
 * OMAP4 PRCM partition IDs
 *
 * The numbers and order are arbitrary, but 0 is reserved क्रम the
 * 'invalid' partition in हाल someone क्रममाला_लो to add a
 * .prcm_partition field.
 */
#घोषणा OMAP4430_INVALID_PRCM_PARTITION		0
#घोषणा OMAP4430_PRM_PARTITION			1
#घोषणा OMAP4430_CM1_PARTITION			2
#घोषणा OMAP4430_CM2_PARTITION			3
#घोषणा OMAP4430_SCRM_PARTITION			4
#घोषणा OMAP4430_PRCM_MPU_PARTITION		5

#घोषणा OMAP54XX_PRM_PARTITION			1
#घोषणा OMAP54XX_CM_CORE_AON_PARTITION		2
#घोषणा OMAP54XX_CM_CORE_PARTITION		3
#घोषणा OMAP54XX_SCRM_PARTITION			4
#घोषणा OMAP54XX_PRCM_MPU_PARTITION		5

#घोषणा DRA7XX_PRM_PARTITION                   1
#घोषणा DRA7XX_CM_CORE_AON_PARTITION           2
#घोषणा DRA7XX_CM_CORE_PARTITION               3
#घोषणा DRA7XX_MPU_PRCM_PARTITION              5

/*
 * OMAP4_MAX_PRCM_PARTITIONS: set to the highest value of the PRCM partition
 * IDs, plus one
 */
#घोषणा OMAP4_MAX_PRCM_PARTITIONS		6


#पूर्ण_अगर
