<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OMAP2+ WDTIMER-specअगरic function prototypes
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_OMAP_WD_TIMER_H
#घोषणा __LINUX_PLATFORM_DATA_OMAP_WD_TIMER_H

#समावेश <linux/types.h>

/*
 * Standardized OMAP reset source bits
 *
 * This is a subset of the ones listed in arch/arm/mach-omap2/prm.h
 * and are the only ones needed in the watchकरोg driver.
 */
#घोषणा OMAP_MPU_WD_RST_SRC_ID_SHIFT				3

/**
 * काष्ठा omap_wd_समयr_platक्रमm_data - WDTIMER पूर्णांकegration to the host SoC
 * @पढ़ो_reset_sources - fn ptr क्रम the SoC to indicate the last reset cause
 *
 * The function poपूर्णांकed to by @पढ़ो_reset_sources must वापस its data
 * in a standard क्रमmat - search क्रम RST_SRC_ID_SHIFT in
 * arch/arm/mach-omap2
 */
काष्ठा omap_wd_समयr_platक्रमm_data अणु
	u32 (*पढ़ो_reset_sources)(व्योम);
पूर्ण;

#पूर्ण_अगर
