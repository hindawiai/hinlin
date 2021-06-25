<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/mach-omap1/opp.h
 *
 *  Copyright (C) 2004 - 2005 Nokia corporation
 *  Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *  Based on घड़ीs.h by Tony Lindgren, Gorकरोn McNutt and RidgeRun, Inc
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP1_OPP_H
#घोषणा __ARCH_ARM_MACH_OMAP1_OPP_H

#समावेश <linux/types.h>

काष्ठा mpu_rate अणु
	अचिन्हित दीर्घ		rate;
	अचिन्हित दीर्घ		xtal;
	अचिन्हित दीर्घ		pll_rate;
	__u16			ckctl_val;
	__u16			dpllctl_val;
	u32			flags;
पूर्ण;

बाह्य काष्ठा mpu_rate omap1_rate_table[];

#पूर्ण_अगर
