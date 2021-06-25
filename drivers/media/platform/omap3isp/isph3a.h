<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * isph3a.h
 *
 * TI OMAP3 ISP - H3A AF module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmail.com>
 *	     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_H3A_H
#घोषणा OMAP3_ISP_H3A_H

#समावेश <linux/omap3isp.h>

/*
 * ----------
 * -H3A AEWB-
 * ----------
 */

#घोषणा AEWB_PACKET_SIZE	16
#घोषणा AEWB_SATURATION_LIMIT	0x3ff

/* Flags क्रम changed रेजिस्टरs */
#घोषणा PCR_CHNG		(1 << 0)
#घोषणा AEWWIN1_CHNG		(1 << 1)
#घोषणा AEWINSTART_CHNG		(1 << 2)
#घोषणा AEWINBLK_CHNG		(1 << 3)
#घोषणा AEWSUBWIN_CHNG		(1 << 4)
#घोषणा PRV_WBDGAIN_CHNG	(1 << 5)
#घोषणा PRV_WBGAIN_CHNG		(1 << 6)

/* ISPH3A REGISTERS bits */
#घोषणा ISPH3A_PCR_AF_EN	(1 << 0)
#घोषणा ISPH3A_PCR_AF_ALAW_EN	(1 << 1)
#घोषणा ISPH3A_PCR_AF_MED_EN	(1 << 2)
#घोषणा ISPH3A_PCR_AF_BUSY	(1 << 15)
#घोषणा ISPH3A_PCR_AEW_EN	(1 << 16)
#घोषणा ISPH3A_PCR_AEW_ALAW_EN	(1 << 17)
#घोषणा ISPH3A_PCR_AEW_BUSY	(1 << 18)
#घोषणा ISPH3A_PCR_AEW_MASK	(ISPH3A_PCR_AEW_ALAW_EN | \
				 ISPH3A_PCR_AEW_AVE2LMT_MASK)

/*
 * --------
 * -H3A AF-
 * --------
 */

/* Peripheral Revision */
#घोषणा AFPID				0x0

#घोषणा AFCOEF_OFFSET			0x00000004	/* COEF base address */

/* PCR fields */
#घोषणा AF_BUSYAF			(1 << 15)
#घोषणा AF_FVMODE			(1 << 14)
#घोषणा AF_RGBPOS			(0x7 << 11)
#घोषणा AF_MED_TH			(0xFF << 3)
#घोषणा AF_MED_EN			(1 << 2)
#घोषणा AF_ALAW_EN			(1 << 1)
#घोषणा AF_EN				(1 << 0)
#घोषणा AF_PCR_MASK			(AF_FVMODE | AF_RGBPOS | AF_MED_TH | \
					 AF_MED_EN | AF_ALAW_EN)

/* AFPAX1 fields */
#घोषणा AF_PAXW				(0x7F << 16)
#घोषणा AF_PAXH				0x7F

/* AFPAX2 fields */
#घोषणा AF_AFINCV			(0xF << 13)
#घोषणा AF_PAXVC			(0x7F << 6)
#घोषणा AF_PAXHC			0x3F

/* AFPAXSTART fields */
#घोषणा AF_PAXSH			(0xFFF<<16)
#घोषणा AF_PAXSV			0xFFF

/* COEFFICIENT MASK */
#घोषणा AF_COEF_MASK0			0xFFF
#घोषणा AF_COEF_MASK1			(0xFFF<<16)

/* BIT SHIFTS */
#घोषणा AF_RGBPOS_SHIFT			11
#घोषणा AF_MED_TH_SHIFT			3
#घोषणा AF_PAXW_SHIFT			16
#घोषणा AF_LINE_INCR_SHIFT		13
#घोषणा AF_VT_COUNT_SHIFT		6
#घोषणा AF_HZ_START_SHIFT		16
#घोषणा AF_COEF_SHIFT			16

/* Init and cleanup functions */
पूर्णांक omap3isp_h3a_aewb_init(काष्ठा isp_device *isp);
पूर्णांक omap3isp_h3a_af_init(काष्ठा isp_device *isp);

व्योम omap3isp_h3a_aewb_cleanup(काष्ठा isp_device *isp);
व्योम omap3isp_h3a_af_cleanup(काष्ठा isp_device *isp);

#पूर्ण_अगर /* OMAP3_ISP_H3A_H */
