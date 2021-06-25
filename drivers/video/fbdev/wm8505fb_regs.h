<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  GOVR रेजिस्टरs list क्रम WM8505 chips
 *
 *  Copyright (C) 2010 Ed Spiriकरोnov <eकरो.rus@gmail.com>
 *   Based on VIA/WonderMedia wm8510-govrh-reg.h
 *   http://github.com/projectgus/kernel_wm8505/blob/wm8505_2.6.29/
 *         drivers/video/wmt/रेजिस्टर/wm8510/wm8510-govrh-reg.h
 */

#अगर_अघोषित _WM8505FB_REGS_H
#घोषणा _WM8505FB_REGS_H

/*
 * Color space select रेजिस्टर, शेष value 0x1c
 *   BIT0 GOVRH_DVO_YUV2RGB_ENABLE
 *   BIT1 GOVRH_VGA_YUV2RGB_ENABLE
 *   BIT2 GOVRH_RGB_MODE
 *   BIT3 GOVRH_DAC_CLKINV
 *   BIT4 GOVRH_BLANK_ZERO
 */
#घोषणा WMT_GOVR_COLORSPACE	0x1e4
/*
 * Another colorspace select रेजिस्टर, शेष value 1
 *   BIT0 GOVRH_DVO_RGB
 *   BIT1 GOVRH_DVO_YUV422
 */
#घोषणा WMT_GOVR_COLORSPACE1	 0x30

#घोषणा WMT_GOVR_CONTRAST	0x1b8
#घोषणा WMT_GOVR_BRGHTNESS	0x1bc /* incompatible with RGB? */

/* Framubeffer address */
#घोषणा WMT_GOVR_FBADDR		 0x90
#घोषणा WMT_GOVR_FBADDR1	 0x94 /* UV offset in YUV mode */

/* Offset of visible winकरोw */
#घोषणा WMT_GOVR_XPAN		 0xa4
#घोषणा WMT_GOVR_YPAN		 0xa0

#घोषणा WMT_GOVR_XRES		 0x98
#घोषणा WMT_GOVR_XRES_VIRTUAL	 0x9c

#घोषणा WMT_GOVR_MIF_ENABLE	 0x80
#घोषणा WMT_GOVR_FHI		 0xa8
#घोषणा WMT_GOVR_REG_UPDATE	 0xe4

/*
 *   BIT0 GOVRH_DVO_OUTWIDTH
 *   BIT1 GOVRH_DVO_SYNC_POLAR
 *   BIT2 GOVRH_DVO_ENABLE
 */
#घोषणा WMT_GOVR_DVO_SET	0x148

/* Timing generator? */
#घोषणा WMT_GOVR_TG		0x100

/* Timings */
#घोषणा WMT_GOVR_TIMING_H_ALL	0x108
#घोषणा WMT_GOVR_TIMING_V_ALL	0x10c
#घोषणा WMT_GOVR_TIMING_V_START	0x110
#घोषणा WMT_GOVR_TIMING_V_END	0x114
#घोषणा WMT_GOVR_TIMING_H_START	0x118
#घोषणा WMT_GOVR_TIMING_H_END	0x11c
#घोषणा WMT_GOVR_TIMING_V_SYNC	0x128
#घोषणा WMT_GOVR_TIMING_H_SYNC	0x12c

#पूर्ण_अगर /* _WM8505FB_REGS_H */
