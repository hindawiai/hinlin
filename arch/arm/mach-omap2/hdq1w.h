<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Shared macros and function prototypes क्रम the HDQ1W/1-wire IP block
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 */
#अगर_अघोषित ARCH_ARM_MACH_OMAP2_HDQ1W_H
#घोषणा ARCH_ARM_MACH_OMAP2_HDQ1W_H

#समावेश "omap_hwmod.h"

/*
 * XXX A future cleanup patch should modअगरy
 * drivers/w1/masters/omap_hdq.c to use these macros
 */
#घोषणा HDQ_CTRL_STATUS_OFFSET			0x0c
#घोषणा HDQ_CTRL_STATUS_CLOCKENABLE_SHIFT	5


बाह्य पूर्णांक omap_hdq1w_reset(काष्ठा omap_hwmod *oh);

#पूर्ण_अगर
