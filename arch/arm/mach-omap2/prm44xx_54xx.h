<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP44xx and 54xx PRM common functions
 *
 * Copyright (C) 2009-2013 Texas Instruments, Inc.
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Paul Walmsley (paul@pwsan.com)
 * Rajendra Nayak (rnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This file is स्वतःmatically generated from the OMAP hardware databases.
 * We respectfully ask that any modअगरications to this file be coordinated
 * with the खुला linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the स्वतःgeneration scripts are kept
 * up-to-date with the file contents.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRM44XX_54XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRM44XX_54XX_H

#समावेश "prcm-common.h"

/* Function prototypes */
#अगर_अघोषित __ASSEMBLER__

/*
 * OMAP4/OMAP5 access functions क्रम voltage controller (VC) and
 * voltage proccessor (VP) in the PRM.
 */
बाह्य u32 omap4_prm_vcvp_पढ़ो(u8 offset);
बाह्य व्योम omap4_prm_vcvp_ग_लिखो(u32 val, u8 offset);
बाह्य u32 omap4_prm_vcvp_rmw(u32 mask, u32 bits, u8 offset);

पूर्णांक __init omap44xx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data);

#पूर्ण_अगर

#पूर्ण_अगर
