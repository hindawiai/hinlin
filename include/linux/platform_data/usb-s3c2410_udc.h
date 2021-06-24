<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* arch/arm/plat-samsung/include/plat/udc.h
 *
 * Copyright (c) 2005 Arnaud Patard <arnaud.patard@rtp-net.org>
 *
 *  Changelog:
 *	14-Mar-2005	RTP	Created file
 *	02-Aug-2005	RTP	File नाम
 *	07-Sep-2005	BJD	Minor cleanups, changed cmd to क्रमागत
 *	18-Jan-2007	HMW	Add per-platक्रमm vbus_draw function
*/

#अगर_अघोषित __ASM_ARM_ARCH_UDC_H
#घोषणा __ASM_ARM_ARCH_UDC_H

क्रमागत s3c2410_udc_cmd_e अणु
	S3C2410_UDC_P_ENABLE	= 1,	/* Pull-up enable        */
	S3C2410_UDC_P_DISABLE	= 2,	/* Pull-up disable       */
	S3C2410_UDC_P_RESET	= 3,	/* UDC reset, in हाल of */
पूर्ण;

काष्ठा s3c2410_udc_mach_info अणु
	व्योम	(*udc_command)(क्रमागत s3c2410_udc_cmd_e);
	व्योम	(*vbus_draw)(अचिन्हित पूर्णांक ma);

	अचिन्हित पूर्णांक pullup_pin;
	अचिन्हित पूर्णांक pullup_pin_inverted;

	अचिन्हित पूर्णांक vbus_pin;
	अचिन्हित अक्षर vbus_pin_inverted;
पूर्ण;

बाह्य व्योम __init s3c24xx_udc_set_platdata(काष्ठा s3c2410_udc_mach_info *);

काष्ठा s3c24xx_hsudc_platdata;

बाह्य व्योम __init s3c24xx_hsudc_set_platdata(काष्ठा s3c24xx_hsudc_platdata *pd);

#पूर्ण_अगर /* __ASM_ARM_ARCH_UDC_H */
