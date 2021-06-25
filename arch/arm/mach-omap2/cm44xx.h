<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP4 Clock Management (CM) definitions
 *
 * Copyright (C) 2007-2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2009 Nokia Corporation
 *
 * Written by Paul Walmsley
 *
 * OMAP4 has two separate CM blocks, CM1 and CM2.  This file contains
 * macros and function prototypes that are applicable to both.
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_CM44XX_H
#घोषणा __ARCH_ASM_MACH_OMAP2_CM44XX_H


#समावेश "prcm-common.h"
#समावेश "cm.h"

#घोषणा OMAP4_CM_CLKSTCTRL				0x0000
#घोषणा OMAP4_CM_STATICDEP				0x0004

पूर्णांक omap4_cm_init(स्थिर काष्ठा omap_prcm_init_data *data);

#पूर्ण_अगर
