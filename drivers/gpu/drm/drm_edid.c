<शैली गुरु>
/*
 * Copyright (c) 2006 Luc Verhaegen (quirks list)
 * Copyright (c) 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright 2010 Red Hat, Inc.
 *
 * DDC probing routines (drm_ddc_पढ़ो & drm_करो_probe_ddc_edid) originally from
 * FB layer.
 *   Copyright (C) 2006 Dennis Munsie <dmunsie@cecropia.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_displayid.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_scdc_helper.h>

#समावेश "drm_crtc_internal.h"

#घोषणा version_greater(edid, maj, min) \
	(((edid)->version > (maj)) || \
	 ((edid)->version == (maj) && (edid)->revision > (min)))

#घोषणा EDID_EST_TIMINGS 16
#घोषणा EDID_STD_TIMINGS 8
#घोषणा EDID_DETAILED_TIMINGS 4

/*
 * EDID blocks out in the wild have a variety of bugs, try to collect
 * them here (note that userspace may work around broken monitors first,
 * but fixes should make their way here so that the kernel "just works"
 * on as many displays as possible).
 */

/* First detailed mode wrong, use largest 60Hz mode */
#घोषणा EDID_QUIRK_PREFER_LARGE_60		(1 << 0)
/* Reported 135MHz pixel घड़ी is too high, needs adjusपंचांगent */
#घोषणा EDID_QUIRK_135_CLOCK_TOO_HIGH		(1 << 1)
/* Prefer the largest mode at 75 Hz */
#घोषणा EDID_QUIRK_PREFER_LARGE_75		(1 << 2)
/* Detail timing is in cm not mm */
#घोषणा EDID_QUIRK_DETAILED_IN_CM		(1 << 3)
/* Detailed timing descriptors have bogus size values, so just take the
 * maximum size and use that.
 */
#घोषणा EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE	(1 << 4)
/* use +hsync +vsync क्रम detailed mode */
#घोषणा EDID_QUIRK_DETAILED_SYNC_PP		(1 << 6)
/* Force reduced-blanking timings क्रम detailed modes */
#घोषणा EDID_QUIRK_FORCE_REDUCED_BLANKING	(1 << 7)
/* Force 8bpc */
#घोषणा EDID_QUIRK_FORCE_8BPC			(1 << 8)
/* Force 12bpc */
#घोषणा EDID_QUIRK_FORCE_12BPC			(1 << 9)
/* Force 6bpc */
#घोषणा EDID_QUIRK_FORCE_6BPC			(1 << 10)
/* Force 10bpc */
#घोषणा EDID_QUIRK_FORCE_10BPC			(1 << 11)
/* Non desktop display (i.e. HMD) */
#घोषणा EDID_QUIRK_NON_DESKTOP			(1 << 12)

काष्ठा detailed_mode_closure अणु
	काष्ठा drm_connector *connector;
	काष्ठा edid *edid;
	bool preferred;
	u32 quirks;
	पूर्णांक modes;
पूर्ण;

#घोषणा LEVEL_DMT	0
#घोषणा LEVEL_GTF	1
#घोषणा LEVEL_GTF2	2
#घोषणा LEVEL_CVT	3

अटल स्थिर काष्ठा edid_quirk अणु
	अक्षर venकरोr[4];
	पूर्णांक product_id;
	u32 quirks;
पूर्ण edid_quirk_list[] = अणु
	/* Acer AL1706 */
	अणु "ACR", 44358, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,
	/* Acer F51 */
	अणु "API", 0x7602, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,

	/* AEO model 0 reports 8 bpc, but is a 6 bpc panel */
	अणु "AEO", 0, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* BOE model on HP Pavilion 15-n233sl reports 8 bpc, but is a 6 bpc panel */
	अणु "BOE", 0x78b, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* CPT panel of Asus UX303LA reports 8 bpc, but is a 6 bpc panel */
	अणु "CPT", 0x17df, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* SDC panel of Lenovo B50-80 reports 8 bpc, but is a 6 bpc panel */
	अणु "SDC", 0x3652, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* BOE model 0x0771 reports 8 bpc, but is a 6 bpc panel */
	अणु "BOE", 0x0771, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* Belinea 10 15 55 */
	अणु "MAX", 1516, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,
	अणु "MAX", 0x77e, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,

	/* Envision Peripherals, Inc. EN-7100e */
	अणु "EPI", 59264, EDID_QUIRK_135_CLOCK_TOO_HIGH पूर्ण,
	/* Envision EN2028 */
	अणु "EPI", 8232, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,

	/* Funai Electronics PM36B */
	अणु "FCM", 13600, EDID_QUIRK_PREFER_LARGE_75 |
	  EDID_QUIRK_DETAILED_IN_CM पूर्ण,

	/* LGD panel of HP zBook 17 G2, eDP 10 bpc, but reports unknown bpc */
	अणु "LGD", 764, EDID_QUIRK_FORCE_10BPC पूर्ण,

	/* LG Philips LCD LP154W01-A5 */
	अणु "LPL", 0, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE पूर्ण,
	अणु "LPL", 0x2a00, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE पूर्ण,

	/* Samsung SyncMaster 205BW.  Note: irony */
	अणु "SAM", 541, EDID_QUIRK_DETAILED_SYNC_PP पूर्ण,
	/* Samsung SyncMaster 22[5-6]BW */
	अणु "SAM", 596, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,
	अणु "SAM", 638, EDID_QUIRK_PREFER_LARGE_60 पूर्ण,

	/* Sony PVM-2541A करोes up to 12 bpc, but only reports max 8 bpc */
	अणु "SNY", 0x2541, EDID_QUIRK_FORCE_12BPC पूर्ण,

	/* ViewSonic VA2026w */
	अणु "VSC", 5020, EDID_QUIRK_FORCE_REDUCED_BLANKING पूर्ण,

	/* Medion MD 30217 PG */
	अणु "MED", 0x7b8, EDID_QUIRK_PREFER_LARGE_75 पूर्ण,

	/* Lenovo G50 */
	अणु "SDC", 18514, EDID_QUIRK_FORCE_6BPC पूर्ण,

	/* Panel in Samsung NP700G7A-S01PL notebook reports 6bpc */
	अणु "SEC", 0xd033, EDID_QUIRK_FORCE_8BPC पूर्ण,

	/* Rotel RSX-1058 क्रमwards sink's EDID but only करोes HDMI 1.1*/
	अणु "ETR", 13896, EDID_QUIRK_FORCE_8BPC पूर्ण,

	/* Valve Index Headset */
	अणु "VLV", 0x91a8, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b0, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b1, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b2, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b3, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b4, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b5, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b6, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b7, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b8, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91b9, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91ba, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91bb, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91bc, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91bd, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91be, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "VLV", 0x91bf, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* HTC Vive and Vive Pro VR Headsets */
	अणु "HVR", 0xaa01, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "HVR", 0xaa02, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* Oculus Rअगरt DK1, DK2, CV1 and Rअगरt S VR Headsets */
	अणु "OVR", 0x0001, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "OVR", 0x0003, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "OVR", 0x0004, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "OVR", 0x0012, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* Winकरोws Mixed Reality Headsets */
	अणु "ACR", 0x7fce, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "HPN", 0x3515, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "LEN", 0x0408, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "LEN", 0xb800, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "FUJ", 0x1970, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "DEL", 0x7fce, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "SEC", 0x144a, EDID_QUIRK_NON_DESKTOP पूर्ण,
	अणु "AUS", 0xc102, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* Sony PlayStation VR Headset */
	अणु "SNY", 0x0704, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* Sensics VR Headsets */
	अणु "SEN", 0x1019, EDID_QUIRK_NON_DESKTOP पूर्ण,

	/* OSVR HDK and HDK2 VR Headsets */
	अणु "SVR", 0x1019, EDID_QUIRK_NON_DESKTOP पूर्ण,
पूर्ण;

/*
 * Autogenerated from the DMT spec.
 * This table is copied from xमुक्त86/modes/xf86EdidModes.c.
 */
अटल स्थिर काष्ठा drm_display_mode drm_dmt_modes[] = अणु
	/* 0x01 - 640x350@85Hz */
	अणु DRM_MODE("640x350", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
		   736, 832, 0, 350, 382, 385, 445, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x02 - 640x400@85Hz */
	अणु DRM_MODE("640x400", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
		   736, 832, 0, 400, 401, 404, 445, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x03 - 720x400@85Hz */
	अणु DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 756,
		   828, 936, 0, 400, 401, 404, 446, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x04 - 640x480@60Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x05 - 640x480@72Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
		   704, 832, 0, 480, 489, 492, 520, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x06 - 640x480@75Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
		   720, 840, 0, 480, 481, 484, 500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x07 - 640x480@85Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 36000, 640, 696,
		   752, 832, 0, 480, 481, 484, 509, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x08 - 800x600@56Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
		   896, 1024, 0, 600, 601, 603, 625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x09 - 800x600@60Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x0a - 800x600@72Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
		   976, 1040, 0, 600, 637, 643, 666, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x0b - 800x600@75Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
		   896, 1056, 0, 600, 601, 604, 625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x0c - 800x600@85Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 56250, 800, 832,
		   896, 1048, 0, 600, 601, 604, 631, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x0d - 800x600@120Hz RB */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 73250, 800, 848,
		   880, 960, 0, 600, 603, 607, 636, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x0e - 848x480@60Hz */
	अणु DRM_MODE("848x480", DRM_MODE_TYPE_DRIVER, 33750, 848, 864,
		   976, 1088, 0, 480, 486, 494, 517, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x0f - 1024x768@43Hz, पूर्णांकerlace */
	अणु DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER, 44900, 1024, 1032,
		   1208, 1264, 0, 768, 768, 776, 817, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE) पूर्ण,
	/* 0x10 - 1024x768@60Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0, 768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x11 - 1024x768@70Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
		   1184, 1328, 0, 768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x12 - 1024x768@75Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78750, 1024, 1040,
		   1136, 1312, 0, 768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x13 - 1024x768@85Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 94500, 1024, 1072,
		   1168, 1376, 0, 768, 769, 772, 808, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x14 - 1024x768@120Hz RB */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 115500, 1024, 1072,
		   1104, 1184, 0, 768, 771, 775, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x15 - 1152x864@75Hz */
	अणु DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0, 864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x55 - 1280x720@60Hz */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x16 - 1280x768@60Hz RB */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 68250, 1280, 1328,
		   1360, 1440, 0, 768, 771, 778, 790, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x17 - 1280x768@60Hz */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 79500, 1280, 1344,
		   1472, 1664, 0, 768, 771, 778, 798, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x18 - 1280x768@75Hz */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 102250, 1280, 1360,
		   1488, 1696, 0, 768, 771, 778, 805, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x19 - 1280x768@85Hz */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 117500, 1280, 1360,
		   1496, 1712, 0, 768, 771, 778, 809, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x1a - 1280x768@120Hz RB */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 140250, 1280, 1328,
		   1360, 1440, 0, 768, 771, 778, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x1b - 1280x800@60Hz RB */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 71000, 1280, 1328,
		   1360, 1440, 0, 800, 803, 809, 823, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x1c - 1280x800@60Hz */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 83500, 1280, 1352,
		   1480, 1680, 0, 800, 803, 809, 831, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x1d - 1280x800@75Hz */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 106500, 1280, 1360,
		   1488, 1696, 0, 800, 803, 809, 838, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x1e - 1280x800@85Hz */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 122500, 1280, 1360,
		   1496, 1712, 0, 800, 803, 809, 843, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x1f - 1280x800@120Hz RB */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 146250, 1280, 1328,
		   1360, 1440, 0, 800, 803, 809, 847, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x20 - 1280x960@60Hz */
	अणु DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1376,
		   1488, 1800, 0, 960, 961, 964, 1000, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x21 - 1280x960@85Hz */
	अणु DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1344,
		   1504, 1728, 0, 960, 961, 964, 1011, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x22 - 1280x960@120Hz RB */
	अणु DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 175500, 1280, 1328,
		   1360, 1440, 0, 960, 963, 967, 1017, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x23 - 1280x1024@60Hz */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1328,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x24 - 1280x1024@75Hz */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x25 - 1280x1024@85Hz */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 157500, 1280, 1344,
		   1504, 1728, 0, 1024, 1025, 1028, 1072, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x26 - 1280x1024@120Hz RB */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 187250, 1280, 1328,
		   1360, 1440, 0, 1024, 1027, 1034, 1084, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x27 - 1360x768@60Hz */
	अणु DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 85500, 1360, 1424,
		   1536, 1792, 0, 768, 771, 777, 795, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x28 - 1360x768@120Hz RB */
	अणु DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 148250, 1360, 1408,
		   1440, 1520, 0, 768, 771, 776, 813, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x51 - 1366x768@60Hz */
	अणु DRM_MODE("1366x768", DRM_MODE_TYPE_DRIVER, 85500, 1366, 1436,
		   1579, 1792, 0, 768, 771, 774, 798, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x56 - 1366x768@60Hz */
	अणु DRM_MODE("1366x768", DRM_MODE_TYPE_DRIVER, 72000, 1366, 1380,
		   1436, 1500, 0, 768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x29 - 1400x1050@60Hz RB */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 101000, 1400, 1448,
		   1480, 1560, 0, 1050, 1053, 1057, 1080, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x2a - 1400x1050@60Hz */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 121750, 1400, 1488,
		   1632, 1864, 0, 1050, 1053, 1057, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x2b - 1400x1050@75Hz */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 156000, 1400, 1504,
		   1648, 1896, 0, 1050, 1053, 1057, 1099, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x2c - 1400x1050@85Hz */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 179500, 1400, 1504,
		   1656, 1912, 0, 1050, 1053, 1057, 1105, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x2d - 1400x1050@120Hz RB */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 208000, 1400, 1448,
		   1480, 1560, 0, 1050, 1053, 1057, 1112, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x2e - 1440x900@60Hz RB */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 88750, 1440, 1488,
		   1520, 1600, 0, 900, 903, 909, 926, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x2f - 1440x900@60Hz */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 106500, 1440, 1520,
		   1672, 1904, 0, 900, 903, 909, 934, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x30 - 1440x900@75Hz */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 136750, 1440, 1536,
		   1688, 1936, 0, 900, 903, 909, 942, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x31 - 1440x900@85Hz */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 157000, 1440, 1544,
		   1696, 1952, 0, 900, 903, 909, 948, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x32 - 1440x900@120Hz RB */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 182750, 1440, 1488,
		   1520, 1600, 0, 900, 903, 909, 953, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x53 - 1600x900@60Hz */
	अणु DRM_MODE("1600x900", DRM_MODE_TYPE_DRIVER, 108000, 1600, 1624,
		   1704, 1800, 0, 900, 901, 904, 1000, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x33 - 1600x1200@60Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 162000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x34 - 1600x1200@65Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 175500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x35 - 1600x1200@70Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 189000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x36 - 1600x1200@75Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 202500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x37 - 1600x1200@85Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 229500, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x38 - 1600x1200@120Hz RB */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 268250, 1600, 1648,
		   1680, 1760, 0, 1200, 1203, 1207, 1271, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x39 - 1680x1050@60Hz RB */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 119000, 1680, 1728,
		   1760, 1840, 0, 1050, 1053, 1059, 1080, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x3a - 1680x1050@60Hz */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 146250, 1680, 1784,
		   1960, 2240, 0, 1050, 1053, 1059, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x3b - 1680x1050@75Hz */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 187000, 1680, 1800,
		   1976, 2272, 0, 1050, 1053, 1059, 1099, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x3c - 1680x1050@85Hz */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 214750, 1680, 1808,
		   1984, 2288, 0, 1050, 1053, 1059, 1105, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x3d - 1680x1050@120Hz RB */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 245500, 1680, 1728,
		   1760, 1840, 0, 1050, 1053, 1059, 1112, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x3e - 1792x1344@60Hz */
	अणु DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 204750, 1792, 1920,
		   2120, 2448, 0, 1344, 1345, 1348, 1394, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x3f - 1792x1344@75Hz */
	अणु DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 261000, 1792, 1888,
		   2104, 2456, 0, 1344, 1345, 1348, 1417, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x40 - 1792x1344@120Hz RB */
	अणु DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 333250, 1792, 1840,
		   1872, 1952, 0, 1344, 1347, 1351, 1423, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x41 - 1856x1392@60Hz */
	अणु DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 218250, 1856, 1952,
		   2176, 2528, 0, 1392, 1393, 1396, 1439, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x42 - 1856x1392@75Hz */
	अणु DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 288000, 1856, 1984,
		   2208, 2560, 0, 1392, 1393, 1396, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x43 - 1856x1392@120Hz RB */
	अणु DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 356500, 1856, 1904,
		   1936, 2016, 0, 1392, 1395, 1399, 1474, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x52 - 1920x1080@60Hz */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x44 - 1920x1200@60Hz RB */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 154000, 1920, 1968,
		   2000, 2080, 0, 1200, 1203, 1209, 1235, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x45 - 1920x1200@60Hz */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 193250, 1920, 2056,
		   2256, 2592, 0, 1200, 1203, 1209, 1245, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x46 - 1920x1200@75Hz */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 245250, 1920, 2056,
		   2264, 2608, 0, 1200, 1203, 1209, 1255, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x47 - 1920x1200@85Hz */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 281250, 1920, 2064,
		   2272, 2624, 0, 1200, 1203, 1209, 1262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x48 - 1920x1200@120Hz RB */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 317000, 1920, 1968,
		   2000, 2080, 0, 1200, 1203, 1209, 1271, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x49 - 1920x1440@60Hz */
	अणु DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 234000, 1920, 2048,
		   2256, 2600, 0, 1440, 1441, 1444, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x4a - 1920x1440@75Hz */
	अणु DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2064,
		   2288, 2640, 0, 1440, 1441, 1444, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x4b - 1920x1440@120Hz RB */
	अणु DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 380500, 1920, 1968,
		   2000, 2080, 0, 1440, 1443, 1447, 1525, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x54 - 2048x1152@60Hz */
	अणु DRM_MODE("2048x1152", DRM_MODE_TYPE_DRIVER, 162000, 2048, 2074,
		   2154, 2250, 0, 1152, 1153, 1156, 1200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x4c - 2560x1600@60Hz RB */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 268500, 2560, 2608,
		   2640, 2720, 0, 1600, 1603, 1609, 1646, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x4d - 2560x1600@60Hz */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 348500, 2560, 2752,
		   3032, 3504, 0, 1600, 1603, 1609, 1658, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x4e - 2560x1600@75Hz */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 443250, 2560, 2768,
		   3048, 3536, 0, 1600, 1603, 1609, 1672, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x4f - 2560x1600@85Hz */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 505250, 2560, 2768,
		   3048, 3536, 0, 1600, 1603, 1609, 1682, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 0x50 - 2560x1600@120Hz RB */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 552750, 2560, 2608,
		   2640, 2720, 0, 1600, 1603, 1609, 1694, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x57 - 4096x2160@60Hz RB */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 556744, 4096, 4104,
		   4136, 4176, 0, 2160, 2208, 2216, 2222, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 0x58 - 4096x2160@59.94Hz RB */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 556188, 4096, 4104,
		   4136, 4176, 0, 2160, 2208, 2216, 2222, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
पूर्ण;

/*
 * These more or less come from the DMT spec.  The 720x400 modes are
 * inferred from historical 80x25 practice.  The 640x480@67 and 832x624@75
 * modes are old-school Mac modes.  The EDID spec says the 1152x864@75 mode
 * should be 1152x870, again क्रम the Mac, but instead we use the x864 DMT
 * mode.
 *
 * The DMT modes have been fact-checked; the rest are mild guesses.
 */
अटल स्थिर काष्ठा drm_display_mode edid_est_modes[] = अणु
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 800x600@60Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
		   896, 1024, 0, 600, 601, 603,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 800x600@56Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
		   720, 840, 0, 480, 481, 484, 500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 640x480@75Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
		   704,  832, 0, 480, 489, 492, 520, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 640x480@72Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 30240, 640, 704,
		   768,  864, 0, 480, 483, 486, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 640x480@67Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 640x480@60Hz */
	अणु DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 738,
		   846, 900, 0, 400, 421, 423,  449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 720x400@88Hz */
	अणु DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 28320, 720, 738,
		   846,  900, 0, 400, 412, 414, 449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 720x400@70Hz */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 1280x1024@75Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78750, 1024, 1040,
		   1136, 1312, 0,  768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 1024x768@75Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
		   1184, 1328, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 1024x768@70Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 1024x768@60Hz */
	अणु DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER,44900, 1024, 1032,
		   1208, 1264, 0, 768, 768, 776, 817, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_INTERLACE) पूर्ण, /* 1024x768@43Hz */
	अणु DRM_MODE("832x624", DRM_MODE_TYPE_DRIVER, 57284, 832, 864,
		   928, 1152, 0, 624, 625, 628, 667, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण, /* 832x624@75Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
		   896, 1056, 0, 600, 601, 604,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 800x600@75Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
		   976, 1040, 0, 600, 637, 643, 666, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 800x600@72Hz */
	अणु DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0,  864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण, /* 1152x864@75Hz */
पूर्ण;

काष्ठा minimode अणु
	लघु w;
	लघु h;
	लघु r;
	लघु rb;
पूर्ण;

अटल स्थिर काष्ठा minimode est3_modes[] = अणु
	/* byte 6 */
	अणु 640, 350, 85, 0 पूर्ण,
	अणु 640, 400, 85, 0 पूर्ण,
	अणु 720, 400, 85, 0 पूर्ण,
	अणु 640, 480, 85, 0 पूर्ण,
	अणु 848, 480, 60, 0 पूर्ण,
	अणु 800, 600, 85, 0 पूर्ण,
	अणु 1024, 768, 85, 0 पूर्ण,
	अणु 1152, 864, 75, 0 पूर्ण,
	/* byte 7 */
	अणु 1280, 768, 60, 1 पूर्ण,
	अणु 1280, 768, 60, 0 पूर्ण,
	अणु 1280, 768, 75, 0 पूर्ण,
	अणु 1280, 768, 85, 0 पूर्ण,
	अणु 1280, 960, 60, 0 पूर्ण,
	अणु 1280, 960, 85, 0 पूर्ण,
	अणु 1280, 1024, 60, 0 पूर्ण,
	अणु 1280, 1024, 85, 0 पूर्ण,
	/* byte 8 */
	अणु 1360, 768, 60, 0 पूर्ण,
	अणु 1440, 900, 60, 1 पूर्ण,
	अणु 1440, 900, 60, 0 पूर्ण,
	अणु 1440, 900, 75, 0 पूर्ण,
	अणु 1440, 900, 85, 0 पूर्ण,
	अणु 1400, 1050, 60, 1 पूर्ण,
	अणु 1400, 1050, 60, 0 पूर्ण,
	अणु 1400, 1050, 75, 0 पूर्ण,
	/* byte 9 */
	अणु 1400, 1050, 85, 0 पूर्ण,
	अणु 1680, 1050, 60, 1 पूर्ण,
	अणु 1680, 1050, 60, 0 पूर्ण,
	अणु 1680, 1050, 75, 0 पूर्ण,
	अणु 1680, 1050, 85, 0 पूर्ण,
	अणु 1600, 1200, 60, 0 पूर्ण,
	अणु 1600, 1200, 65, 0 पूर्ण,
	अणु 1600, 1200, 70, 0 पूर्ण,
	/* byte 10 */
	अणु 1600, 1200, 75, 0 पूर्ण,
	अणु 1600, 1200, 85, 0 पूर्ण,
	अणु 1792, 1344, 60, 0 पूर्ण,
	अणु 1792, 1344, 75, 0 पूर्ण,
	अणु 1856, 1392, 60, 0 पूर्ण,
	अणु 1856, 1392, 75, 0 पूर्ण,
	अणु 1920, 1200, 60, 1 पूर्ण,
	अणु 1920, 1200, 60, 0 पूर्ण,
	/* byte 11 */
	अणु 1920, 1200, 75, 0 पूर्ण,
	अणु 1920, 1200, 85, 0 पूर्ण,
	अणु 1920, 1440, 60, 0 पूर्ण,
	अणु 1920, 1440, 75, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा minimode extra_modes[] = अणु
	अणु 1024, 576,  60, 0 पूर्ण,
	अणु 1366, 768,  60, 0 पूर्ण,
	अणु 1600, 900,  60, 0 पूर्ण,
	अणु 1680, 945,  60, 0 पूर्ण,
	अणु 1920, 1080, 60, 0 पूर्ण,
	अणु 2048, 1152, 60, 0 पूर्ण,
	अणु 2048, 1536, 60, 0 पूर्ण,
पूर्ण;

/*
 * From CEA/CTA-861 spec.
 *
 * Do not access directly, instead always use cea_mode_क्रम_vic().
 */
अटल स्थिर काष्ठा drm_display_mode edid_cea_modes_1[] = अणु
	/* 1 - 640x480@60Hz 4:3 */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 2 - 720x480@60Hz 4:3 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 3 - 720x480@60Hz 16:9 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 4 - 1280x720@60Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 5 - 1920x1080i@60Hz 16:9 */
	अणु DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 6 - 720(1440)x480i@60Hz 4:3 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 7 - 720(1440)x480i@60Hz 16:9 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 8 - 720(1440)x240@60Hz 4:3 */
	अणु DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 9 - 720(1440)x240@60Hz 16:9 */
	अणु DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
		   801, 858, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 10 - 2880x480i@60Hz 4:3 */
	अणु DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 11 - 2880x480i@60Hz 16:9 */
	अणु DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 12 - 2880x240@60Hz 4:3 */
	अणु DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 13 - 2880x240@60Hz 16:9 */
	अणु DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 14 - 1440x480@60Hz 4:3 */
	अणु DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 15 - 1440x480@60Hz 16:9 */
	अणु DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 16 - 1920x1080@60Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 17 - 720x576@50Hz 4:3 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 18 - 720x576@50Hz 16:9 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 19 - 1280x720@50Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 20 - 1920x1080i@50Hz 16:9 */
	अणु DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 21 - 720(1440)x576i@50Hz 4:3 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 22 - 720(1440)x576i@50Hz 16:9 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 23 - 720(1440)x288@50Hz 4:3 */
	अणु DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 24 - 720(1440)x288@50Hz 16:9 */
	अणु DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
		   795, 864, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 25 - 2880x576i@50Hz 4:3 */
	अणु DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 26 - 2880x576i@50Hz 16:9 */
	अणु DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 27 - 2880x288@50Hz 4:3 */
	अणु DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 28 - 2880x288@50Hz 16:9 */
	अणु DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 29 - 1440x576@50Hz 4:3 */
	अणु DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 30 - 1440x576@50Hz 16:9 */
	अणु DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 31 - 1920x1080@50Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 32 - 1920x1080@24Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 33 - 1920x1080@25Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 34 - 1920x1080@30Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 35 - 2880x480@60Hz 4:3 */
	अणु DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 36 - 2880x480@60Hz 16:9 */
	अणु DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 37 - 2880x576@50Hz 4:3 */
	अणु DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 38 - 2880x576@50Hz 16:9 */
	अणु DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 39 - 1920x1080i@50Hz 16:9 */
	अणु DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 72000, 1920, 1952,
		   2120, 2304, 0, 1080, 1126, 1136, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 40 - 1920x1080i@100Hz 16:9 */
	अणु DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 41 - 1280x720@100Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 42 - 720x576@100Hz 4:3 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 43 - 720x576@100Hz 16:9 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 44 - 720(1440)x576i@100Hz 4:3 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 45 - 720(1440)x576i@100Hz 16:9 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 46 - 1920x1080i@120Hz 16:9 */
	अणु DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
		   DRM_MODE_FLAG_INTERLACE),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 47 - 1280x720@120Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 48 - 720x480@120Hz 4:3 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 49 - 720x480@120Hz 16:9 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 50 - 720(1440)x480i@120Hz 4:3 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 51 - 720(1440)x480i@120Hz 16:9 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 52 - 720x576@200Hz 4:3 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 53 - 720x576@200Hz 16:9 */
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 54 - 720(1440)x576i@200Hz 4:3 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 55 - 720(1440)x576i@200Hz 16:9 */
	अणु DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   795, 864, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 56 - 720x480@240Hz 4:3 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 57 - 720x480@240Hz 16:9 */
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 58 - 720(1440)x480i@240Hz 4:3 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3, पूर्ण,
	/* 59 - 720(1440)x480i@240Hz 16:9 */
	अणु DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
		   801, 858, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
		   DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 60 - 1280x720@24Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 61 - 1280x720@25Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
		   3740, 3960, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 62 - 1280x720@30Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 63 - 1920x1080@120Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 64 - 1920x1080@100Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 65 - 1280x720@24Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 66 - 1280x720@25Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
		   3740, 3960, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 67 - 1280x720@30Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 68 - 1280x720@50Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 69 - 1280x720@60Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 70 - 1280x720@100Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 71 - 1280x720@120Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 72 - 1920x1080@24Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 73 - 1920x1080@25Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 74 - 1920x1080@30Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 75 - 1920x1080@50Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 76 - 1920x1080@60Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 77 - 1920x1080@100Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 78 - 1920x1080@120Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 79 - 1680x720@24Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 80 - 1680x720@25Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 2908,
		   2948, 3168, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 81 - 1680x720@30Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400, 1680, 2380,
		   2420, 2640, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 82 - 1680x720@50Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 82500, 1680, 1940,
		   1980, 2200, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 83 - 1680x720@60Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 99000, 1680, 1940,
		   1980, 2200, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 84 - 1680x720@100Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 165000, 1680, 1740,
		   1780, 2000, 0, 720, 725, 730, 825, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 85 - 1680x720@120Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 198000, 1680, 1740,
		   1780, 2000, 0, 720, 725, 730, 825, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 86 - 2560x1080@24Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 99000, 2560, 3558,
		   3602, 3750, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 87 - 2560x1080@25Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 90000, 2560, 3008,
		   3052, 3200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 88 - 2560x1080@30Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 118800, 2560, 3328,
		   3372, 3520, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 89 - 2560x1080@50Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 185625, 2560, 3108,
		   3152, 3300, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 90 - 2560x1080@60Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 198000, 2560, 2808,
		   2852, 3000, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 91 - 2560x1080@100Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 371250, 2560, 2778,
		   2822, 2970, 0, 1080, 1084, 1089, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 92 - 2560x1080@120Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 495000, 2560, 3108,
		   3152, 3300, 0, 1080, 1084, 1089, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 93 - 3840x2160@24Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 94 - 3840x2160@25Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 95 - 3840x2160@30Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 96 - 3840x2160@50Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 97 - 3840x2160@60Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 98 - 4096x2160@24Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 99 - 4096x2160@25Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 5064,
		   5152, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 100 - 4096x2160@30Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 101 - 4096x2160@50Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 5064,
		   5152, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 102 - 4096x2160@60Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 103 - 3840x2160@24Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 104 - 3840x2160@25Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 105 - 3840x2160@30Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 106 - 3840x2160@50Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 107 - 3840x2160@60Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 108 - 1280x720@48Hz 16:9 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 90000, 1280, 2240,
		   2280, 2500, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 109 - 1280x720@48Hz 64:27 */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 90000, 1280, 2240,
		   2280, 2500, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 110 - 1680x720@48Hz 64:27 */
	अणु DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 99000, 1680, 2490,
		   2530, 2750, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 111 - 1920x1080@48Hz 16:9 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 112 - 1920x1080@48Hz 64:27 */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 113 - 2560x1080@48Hz 64:27 */
	अणु DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 198000, 2560, 3558,
		   3602, 3750, 0, 1080, 1084, 1089, 1100, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 114 - 3840x2160@48Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 115 - 4096x2160@48Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000, 4096, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 116 - 3840x2160@48Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000, 3840, 5116,
		   5204, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 117 - 3840x2160@100Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 118 - 3840x2160@120Hz 16:9 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 119 - 3840x2160@100Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 120 - 3840x2160@120Hz 64:27 */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 1188000, 3840, 4016,
		   4104, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 121 - 5120x2160@24Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 7116,
		   7204, 7500, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 122 - 5120x2160@25Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 6816,
		   6904, 7200, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 123 - 5120x2160@30Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 396000, 5120, 5784,
		   5872, 6000, 0, 2160, 2168, 2178, 2200, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 124 - 5120x2160@48Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 5866,
		   5954, 6250, 0, 2160, 2168, 2178, 2475, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 125 - 5120x2160@50Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 6216,
		   6304, 6600, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 126 - 5120x2160@60Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 742500, 5120, 5284,
		   5372, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 127 - 5120x2160@100Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 1485000, 5120, 6216,
		   6304, 6600, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
पूर्ण;

/*
 * From CEA/CTA-861 spec.
 *
 * Do not access directly, instead always use cea_mode_क्रम_vic().
 */
अटल स्थिर काष्ठा drm_display_mode edid_cea_modes_193[] = अणु
	/* 193 - 5120x2160@120Hz 64:27 */
	अणु DRM_MODE("5120x2160", DRM_MODE_TYPE_DRIVER, 1485000, 5120, 5284,
		   5372, 5500, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 194 - 7680x4320@24Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 195 - 7680x4320@25Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 196 - 7680x4320@30Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 197 - 7680x4320@48Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 198 - 7680x4320@50Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 199 - 7680x4320@60Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 200 - 7680x4320@100Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 9792,
		   9968, 10560, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 201 - 7680x4320@120Hz 16:9 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 8032,
		   8208, 8800, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 202 - 7680x4320@24Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 203 - 7680x4320@25Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 204 - 7680x4320@30Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 1188000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 205 - 7680x4320@48Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10232,
		   10408, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 206 - 7680x4320@50Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 10032,
		   10208, 10800, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 207 - 7680x4320@60Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000, 7680, 8232,
		   8408, 9000, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 208 - 7680x4320@100Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 9792,
		   9968, 10560, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 209 - 7680x4320@120Hz 64:27 */
	अणु DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 4752000, 7680, 8032,
		   8208, 8800, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 210 - 10240x4320@24Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 11732,
		   11908, 12500, 0, 4320, 4336, 4356, 4950, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 211 - 10240x4320@25Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 12732,
		   12908, 13500, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 212 - 10240x4320@30Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 1485000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 213 - 10240x4320@48Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 11732,
		   11908, 12500, 0, 4320, 4336, 4356, 4950, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 214 - 10240x4320@50Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 12732,
		   12908, 13500, 0, 4320, 4336, 4356, 4400, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 215 - 10240x4320@60Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 2970000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 216 - 10240x4320@100Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 5940000, 10240, 12432,
		   12608, 13200, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 217 - 10240x4320@120Hz 64:27 */
	अणु DRM_MODE("10240x4320", DRM_MODE_TYPE_DRIVER, 5940000, 10240, 10528,
		   10704, 11000, 0, 4320, 4336, 4356, 4500, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27, पूर्ण,
	/* 218 - 4096x2160@100Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 1188000, 4096, 4896,
		   4984, 5280, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
	/* 219 - 4096x2160@120Hz 256:135 */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 1188000, 4096, 4184,
		   4272, 4400, 0, 2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
पूर्ण;

/*
 * HDMI 1.4 4k modes. Index using the VIC.
 */
अटल स्थिर काष्ठा drm_display_mode edid_4k_modes[] = अणु
	/* 0 - dummy, VICs start at 1 */
	अणु पूर्ण,
	/* 1 - 3840x2160@30Hz */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 4016, 4104, 4400, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 2 - 3840x2160@25Hz */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 4896, 4984, 5280, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 3 - 3840x2160@24Hz */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   3840, 5116, 5204, 5500, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, पूर्ण,
	/* 4 - 4096x2160@24Hz (SMPTE) */
	अणु DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
		   4096, 5116, 5204, 5500, 0,
		   2160, 2168, 2178, 2250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135, पूर्ण,
पूर्ण;

/*** DDC fetch and block validation ***/

अटल स्थिर u8 edid_header[] = अणु
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
पूर्ण;

/**
 * drm_edid_header_is_valid - sanity check the header of the base EDID block
 * @raw_edid: poपूर्णांकer to raw base EDID block
 *
 * Sanity check the header of the base EDID block.
 *
 * Return: 8 अगर the header is perfect, करोwn to 0 अगर it's totally wrong.
 */
पूर्णांक drm_edid_header_is_valid(स्थिर u8 *raw_edid)
अणु
	पूर्णांक i, score = 0;

	क्रम (i = 0; i < माप(edid_header); i++)
		अगर (raw_edid[i] == edid_header[i])
			score++;

	वापस score;
पूर्ण
EXPORT_SYMBOL(drm_edid_header_is_valid);

अटल पूर्णांक edid_fixup __पढ़ो_mostly = 6;
module_param_named(edid_fixup, edid_fixup, पूर्णांक, 0400);
MODULE_PARM_DESC(edid_fixup,
		 "Minimum number of valid EDID header bytes (0-8, default 6)");

अटल पूर्णांक drm_edid_block_checksum(स्थिर u8 *raw_edid)
अणु
	पूर्णांक i;
	u8 csum = 0, crc = 0;

	क्रम (i = 0; i < EDID_LENGTH - 1; i++)
		csum += raw_edid[i];

	crc = 0x100 - csum;

	वापस crc;
पूर्ण

अटल bool drm_edid_block_checksum_dअगरf(स्थिर u8 *raw_edid, u8 real_checksum)
अणु
	अगर (raw_edid[EDID_LENGTH - 1] != real_checksum)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool drm_edid_is_zero(स्थिर u8 *in_edid, पूर्णांक length)
अणु
	अगर (स_प्रथम_inv(in_edid, 0, length))
		वापस false;

	वापस true;
पूर्ण

/**
 * drm_edid_are_equal - compare two edid blobs.
 * @edid1: poपूर्णांकer to first blob
 * @edid2: poपूर्णांकer to second blob
 * This helper can be used during probing to determine अगर
 * edid had changed.
 */
bool drm_edid_are_equal(स्थिर काष्ठा edid *edid1, स्थिर काष्ठा edid *edid2)
अणु
	पूर्णांक edid1_len, edid2_len;
	bool edid1_present = edid1 != शून्य;
	bool edid2_present = edid2 != शून्य;

	अगर (edid1_present != edid2_present)
		वापस false;

	अगर (edid1) अणु
		edid1_len = EDID_LENGTH * (1 + edid1->extensions);
		edid2_len = EDID_LENGTH * (1 + edid2->extensions);

		अगर (edid1_len != edid2_len)
			वापस false;

		अगर (स_भेद(edid1, edid2, edid1_len))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_edid_are_equal);

/**
 * drm_edid_block_valid - Sanity check the EDID block (base or extension)
 * @raw_edid: poपूर्णांकer to raw EDID block
 * @block: type of block to validate (0 क्रम base, extension otherwise)
 * @prपूर्णांक_bad_edid: अगर true, dump bad EDID blocks to the console
 * @edid_corrupt: अगर true, the header or checksum is invalid
 *
 * Validate a base or extension EDID block and optionally dump bad blocks to
 * the console.
 *
 * Return: True अगर the block is valid, false otherwise.
 */
bool drm_edid_block_valid(u8 *raw_edid, पूर्णांक block, bool prपूर्णांक_bad_edid,
			  bool *edid_corrupt)
अणु
	u8 csum;
	काष्ठा edid *edid = (काष्ठा edid *)raw_edid;

	अगर (WARN_ON(!raw_edid))
		वापस false;

	अगर (edid_fixup > 8 || edid_fixup < 0)
		edid_fixup = 6;

	अगर (block == 0) अणु
		पूर्णांक score = drm_edid_header_is_valid(raw_edid);

		अगर (score == 8) अणु
			अगर (edid_corrupt)
				*edid_corrupt = false;
		पूर्ण अन्यथा अगर (score >= edid_fixup) अणु
			/* Displayport Link CTS Core 1.2 rev1.1 test 4.2.2.6
			 * The corrupt flag needs to be set here otherwise, the
			 * fix-up code here will correct the problem, the
			 * checksum is correct and the test fails
			 */
			अगर (edid_corrupt)
				*edid_corrupt = true;
			DRM_DEBUG("Fixing EDID header, your hardware may be failing\n");
			स_नकल(raw_edid, edid_header, माप(edid_header));
		पूर्ण अन्यथा अणु
			अगर (edid_corrupt)
				*edid_corrupt = true;
			जाओ bad;
		पूर्ण
	पूर्ण

	csum = drm_edid_block_checksum(raw_edid);
	अगर (drm_edid_block_checksum_dअगरf(raw_edid, csum)) अणु
		अगर (edid_corrupt)
			*edid_corrupt = true;

		/* allow CEA to slide through, चयनes mangle this */
		अगर (raw_edid[0] == CEA_EXT) अणु
			DRM_DEBUG("EDID checksum is invalid, remainder is %d\n", csum);
			DRM_DEBUG("Assuming a KVM switch modified the CEA block but left the original checksum\n");
		पूर्ण अन्यथा अणु
			अगर (prपूर्णांक_bad_edid)
				DRM_NOTE("EDID checksum is invalid, remainder is %d\n", csum);

			जाओ bad;
		पूर्ण
	पूर्ण

	/* per-block-type checks */
	चयन (raw_edid[0]) अणु
	हाल 0: /* base */
		अगर (edid->version != 1) अणु
			DRM_NOTE("EDID has major version %d, instead of 1\n", edid->version);
			जाओ bad;
		पूर्ण

		अगर (edid->revision > 4)
			DRM_DEBUG("EDID minor > 4, assuming backward compatibility\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस true;

bad:
	अगर (prपूर्णांक_bad_edid) अणु
		अगर (drm_edid_is_zero(raw_edid, EDID_LENGTH)) अणु
			pr_notice("EDID block is all zeroes\n");
		पूर्ण अन्यथा अणु
			pr_notice("Raw EDID:\n");
			prपूर्णांक_hex_dump(KERN_NOTICE,
				       " \t", DUMP_PREFIX_NONE, 16, 1,
				       raw_edid, EDID_LENGTH, false);
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_edid_block_valid);

/**
 * drm_edid_is_valid - sanity check EDID data
 * @edid: EDID data
 *
 * Sanity-check an entire EDID record (including extensions)
 *
 * Return: True अगर the EDID data is valid, false otherwise.
 */
bool drm_edid_is_valid(काष्ठा edid *edid)
अणु
	पूर्णांक i;
	u8 *raw = (u8 *)edid;

	अगर (!edid)
		वापस false;

	क्रम (i = 0; i <= edid->extensions; i++)
		अगर (!drm_edid_block_valid(raw + i * EDID_LENGTH, i, true, शून्य))
			वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_edid_is_valid);

#घोषणा DDC_SEGMENT_ADDR 0x30
/**
 * drm_करो_probe_ddc_edid() - get EDID inक्रमmation via I2C
 * @data: I2C device adapter
 * @buf: EDID data buffer to be filled
 * @block: 128 byte EDID block to start fetching from
 * @len: EDID data buffer length to fetch
 *
 * Try to fetch EDID inक्रमmation by calling I2C driver functions.
 *
 * Return: 0 on success or -1 on failure.
 */
अटल पूर्णांक
drm_करो_probe_ddc_edid(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा i2c_adapter *adapter = data;
	अचिन्हित अक्षर start = block * EDID_LENGTH;
	अचिन्हित अक्षर segment = block >> 1;
	अचिन्हित अक्षर xfers = segment ? 3 : 2;
	पूर्णांक ret, retries = 5;

	/*
	 * The core I2C driver will स्वतःmatically retry the transfer अगर the
	 * adapter reports EAGAIN. However, we find that bit-banging transfers
	 * are susceptible to errors under a heavily loaded machine and
	 * generate spurious NAKs and समयouts. Retrying the transfer
	 * of the inभागidual block a few बार seems to overcome this.
	 */
	करो अणु
		काष्ठा i2c_msg msgs[] = अणु
			अणु
				.addr	= DDC_SEGMENT_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &segment,
			पूर्ण, अणु
				.addr	= DDC_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &start,
			पूर्ण, अणु
				.addr	= DDC_ADDR,
				.flags	= I2C_M_RD,
				.len	= len,
				.buf	= buf,
			पूर्ण
		पूर्ण;

		/*
		 * Aव्योम sending the segment addr to not upset non-compliant
		 * DDC monitors.
		 */
		ret = i2c_transfer(adapter, &msgs[3 - xfers], xfers);

		अगर (ret == -ENXIO) अणु
			DRM_DEBUG_KMS("drm: skipping non-existent adapter %s\n",
					adapter->name);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (ret != xfers && --retries);

	वापस ret == xfers ? 0 : -1;
पूर्ण

अटल व्योम connector_bad_edid(काष्ठा drm_connector *connector,
			       u8 *edid, पूर्णांक num_blocks)
अणु
	पूर्णांक i;
	u8 num_of_ext = edid[0x7e];

	/* Calculate real checksum क्रम the last edid extension block data */
	connector->real_edid_checksum =
		drm_edid_block_checksum(edid + num_of_ext * EDID_LENGTH);

	अगर (connector->bad_edid_counter++ && !drm_debug_enabled(DRM_UT_KMS))
		वापस;

	drm_dbg_kms(connector->dev, "%s: EDID is invalid:\n", connector->name);
	क्रम (i = 0; i < num_blocks; i++) अणु
		u8 *block = edid + i * EDID_LENGTH;
		अक्षर prefix[20];

		अगर (drm_edid_is_zero(block, EDID_LENGTH))
			प्र_लिखो(prefix, "\t[%02x] ZERO ", i);
		अन्यथा अगर (!drm_edid_block_valid(block, i, false, शून्य))
			प्र_लिखो(prefix, "\t[%02x] BAD  ", i);
		अन्यथा
			प्र_लिखो(prefix, "\t[%02x] GOOD ", i);

		prपूर्णांक_hex_dump(KERN_DEBUG,
			       prefix, DUMP_PREFIX_NONE, 16, 1,
			       block, EDID_LENGTH, false);
	पूर्ण
पूर्ण

/* Get override or firmware EDID */
अटल काष्ठा edid *drm_get_override_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *override = शून्य;

	अगर (connector->override_edid)
		override = drm_edid_duplicate(connector->edid_blob_ptr->data);

	अगर (!override)
		override = drm_load_edid_firmware(connector);

	वापस IS_ERR(override) ? शून्य : override;
पूर्ण

/**
 * drm_add_override_edid_modes - add modes from override/firmware EDID
 * @connector: connector we're probing
 *
 * Add modes from the override/firmware EDID, अगर available. Only to be used from
 * drm_helper_probe_single_connector_modes() as a fallback क्रम when DDC probe
 * failed during drm_get_edid() and caused the override/firmware EDID to be
 * skipped.
 *
 * Return: The number of modes added or 0 अगर we couldn't find any.
 */
पूर्णांक drm_add_override_edid_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *override;
	पूर्णांक num_modes = 0;

	override = drm_get_override_edid(connector);
	अगर (override) अणु
		drm_connector_update_edid_property(connector, override);
		num_modes = drm_add_edid_modes(connector, override);
		kमुक्त(override);

		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] adding %d modes via fallback override/firmware EDID\n",
			      connector->base.id, connector->name, num_modes);
	पूर्ण

	वापस num_modes;
पूर्ण
EXPORT_SYMBOL(drm_add_override_edid_modes);

/**
 * drm_करो_get_edid - get EDID data using a custom EDID block पढ़ो function
 * @connector: connector we're probing
 * @get_edid_block: EDID block पढ़ो function
 * @data: निजी data passed to the block पढ़ो function
 *
 * When the I2C adapter connected to the DDC bus is hidden behind a device that
 * exposes a dअगरferent पूर्णांकerface to पढ़ो EDID blocks this function can be used
 * to get EDID data using a custom block पढ़ो function.
 *
 * As in the general हाल the DDC bus is accessible by the kernel at the I2C
 * level, drivers must make all reasonable efक्रमts to expose it as an I2C
 * adapter and use drm_get_edid() instead of abusing this function.
 *
 * The EDID may be overridden using debugfs override_edid or firmare EDID
 * (drm_load_edid_firmware() and drm.edid_firmware parameter), in this priority
 * order. Having either of them bypasses actual EDID पढ़ोs.
 *
 * Return: Poपूर्णांकer to valid EDID or शून्य अगर we couldn't find any.
 */
काष्ठा edid *drm_करो_get_edid(काष्ठा drm_connector *connector,
	पूर्णांक (*get_edid_block)(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block,
			      माप_प्रकार len),
	व्योम *data)
अणु
	पूर्णांक i, j = 0, valid_extensions = 0;
	u8 *edid, *new;
	काष्ठा edid *override;

	override = drm_get_override_edid(connector);
	अगर (override)
		वापस override;

	अगर ((edid = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL)) == शून्य)
		वापस शून्य;

	/* base block fetch */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (get_edid_block(data, edid, 0, EDID_LENGTH))
			जाओ out;
		अगर (drm_edid_block_valid(edid, 0, false,
					 &connector->edid_corrupt))
			अवरोध;
		अगर (i == 0 && drm_edid_is_zero(edid, EDID_LENGTH)) अणु
			connector->null_edid_counter++;
			जाओ carp;
		पूर्ण
	पूर्ण
	अगर (i == 4)
		जाओ carp;

	/* अगर there's no extensions, we're करोne */
	valid_extensions = edid[0x7e];
	अगर (valid_extensions == 0)
		वापस (काष्ठा edid *)edid;

	new = kपुनः_स्मृति(edid, (valid_extensions + 1) * EDID_LENGTH, GFP_KERNEL);
	अगर (!new)
		जाओ out;
	edid = new;

	क्रम (j = 1; j <= edid[0x7e]; j++) अणु
		u8 *block = edid + j * EDID_LENGTH;

		क्रम (i = 0; i < 4; i++) अणु
			अगर (get_edid_block(data, block, j, EDID_LENGTH))
				जाओ out;
			अगर (drm_edid_block_valid(block, j, false, शून्य))
				अवरोध;
		पूर्ण

		अगर (i == 4)
			valid_extensions--;
	पूर्ण

	अगर (valid_extensions != edid[0x7e]) अणु
		u8 *base;

		connector_bad_edid(connector, edid, edid[0x7e] + 1);

		edid[EDID_LENGTH-1] += edid[0x7e] - valid_extensions;
		edid[0x7e] = valid_extensions;

		new = kदो_स्मृति_array(valid_extensions + 1, EDID_LENGTH,
				    GFP_KERNEL);
		अगर (!new)
			जाओ out;

		base = new;
		क्रम (i = 0; i <= edid[0x7e]; i++) अणु
			u8 *block = edid + i * EDID_LENGTH;

			अगर (!drm_edid_block_valid(block, i, false, शून्य))
				जारी;

			स_नकल(base, block, EDID_LENGTH);
			base += EDID_LENGTH;
		पूर्ण

		kमुक्त(edid);
		edid = new;
	पूर्ण

	वापस (काष्ठा edid *)edid;

carp:
	connector_bad_edid(connector, edid, 1);
out:
	kमुक्त(edid);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(drm_करो_get_edid);

/**
 * drm_probe_ddc() - probe DDC presence
 * @adapter: I2C adapter to probe
 *
 * Return: True on success, false on failure.
 */
bool
drm_probe_ddc(काष्ठा i2c_adapter *adapter)
अणु
	अचिन्हित अक्षर out;

	वापस (drm_करो_probe_ddc_edid(adapter, &out, 0, 1) == 0);
पूर्ण
EXPORT_SYMBOL(drm_probe_ddc);

/**
 * drm_get_edid - get EDID data, अगर available
 * @connector: connector we're probing
 * @adapter: I2C adapter to use क्रम DDC
 *
 * Poke the given I2C channel to grab EDID data अगर possible.  If found,
 * attach it to the connector.
 *
 * Return: Poपूर्णांकer to valid EDID or शून्य अगर we couldn't find any.
 */
काष्ठा edid *drm_get_edid(काष्ठा drm_connector *connector,
			  काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा edid *edid;

	अगर (connector->क्रमce == DRM_FORCE_OFF)
		वापस शून्य;

	अगर (connector->क्रमce == DRM_FORCE_UNSPECIFIED && !drm_probe_ddc(adapter))
		वापस शून्य;

	edid = drm_करो_get_edid(connector, drm_करो_probe_ddc_edid, adapter);
	drm_connector_update_edid_property(connector, edid);
	वापस edid;
पूर्ण
EXPORT_SYMBOL(drm_get_edid);

/**
 * drm_get_edid_चयनeroo - get EDID data क्रम a vga_चयनeroo output
 * @connector: connector we're probing
 * @adapter: I2C adapter to use क्रम DDC
 *
 * Wrapper around drm_get_edid() क्रम laptops with dual GPUs using one set of
 * outमाला_दो. The wrapper adds the requisite vga_चयनeroo calls to temporarily
 * चयन DDC to the GPU which is retrieving EDID.
 *
 * Return: Poपूर्णांकer to valid EDID or %शून्य अगर we couldn't find any.
 */
काष्ठा edid *drm_get_edid_चयनeroo(काष्ठा drm_connector *connector,
				     काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा edid *edid;

	अगर (drm_WARN_ON_ONCE(dev, !dev_is_pci(dev->dev)))
		वापस शून्य;

	vga_चयनeroo_lock_ddc(pdev);
	edid = drm_get_edid(connector, adapter);
	vga_चयनeroo_unlock_ddc(pdev);

	वापस edid;
पूर्ण
EXPORT_SYMBOL(drm_get_edid_चयनeroo);

/**
 * drm_edid_duplicate - duplicate an EDID and the extensions
 * @edid: EDID to duplicate
 *
 * Return: Poपूर्णांकer to duplicated EDID or शून्य on allocation failure.
 */
काष्ठा edid *drm_edid_duplicate(स्थिर काष्ठा edid *edid)
अणु
	वापस kmemdup(edid, (edid->extensions + 1) * EDID_LENGTH, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(drm_edid_duplicate);

/*** EDID parsing ***/

/**
 * edid_venकरोr - match a string against EDID's obfuscated venकरोr field
 * @edid: EDID to match
 * @venकरोr: venकरोr string
 *
 * Returns true अगर @venकरोr is in @edid, false otherwise
 */
अटल bool edid_venकरोr(स्थिर काष्ठा edid *edid, स्थिर अक्षर *venकरोr)
अणु
	अक्षर edid_venकरोr[3];

	edid_venकरोr[0] = ((edid->mfg_id[0] & 0x7c) >> 2) + '@';
	edid_venकरोr[1] = (((edid->mfg_id[0] & 0x3) << 3) |
			  ((edid->mfg_id[1] & 0xe0) >> 5)) + '@';
	edid_venकरोr[2] = (edid->mfg_id[1] & 0x1f) + '@';

	वापस !म_भेदन(edid_venकरोr, venकरोr, 3);
पूर्ण

/**
 * edid_get_quirks - वापस quirk flags क्रम a given EDID
 * @edid: EDID to process
 *
 * This tells subsequent routines what fixes they need to apply.
 */
अटल u32 edid_get_quirks(स्थिर काष्ठा edid *edid)
अणु
	स्थिर काष्ठा edid_quirk *quirk;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(edid_quirk_list); i++) अणु
		quirk = &edid_quirk_list[i];

		अगर (edid_venकरोr(edid, quirk->venकरोr) &&
		    (EDID_PRODUCT_ID(edid) == quirk->product_id))
			वापस quirk->quirks;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MODE_SIZE(m) ((m)->hdisplay * (m)->vdisplay)
#घोषणा MODE_REFRESH_DIFF(c,t) (असल((c) - (t)))

/**
 * edid_fixup_preferred - set preferred modes based on quirk list
 * @connector: has mode list to fix up
 * @quirks: quirks list
 *
 * Walk the mode list क्रम @connector, clearing the preferred status
 * on existing modes and setting it anew क्रम the right mode ala @quirks.
 */
अटल व्योम edid_fixup_preferred(काष्ठा drm_connector *connector,
				 u32 quirks)
अणु
	काष्ठा drm_display_mode *t, *cur_mode, *preferred_mode;
	पूर्णांक target_refresh = 0;
	पूर्णांक cur_vrefresh, preferred_vrefresh;

	अगर (list_empty(&connector->probed_modes))
		वापस;

	अगर (quirks & EDID_QUIRK_PREFER_LARGE_60)
		target_refresh = 60;
	अगर (quirks & EDID_QUIRK_PREFER_LARGE_75)
		target_refresh = 75;

	preferred_mode = list_first_entry(&connector->probed_modes,
					  काष्ठा drm_display_mode, head);

	list_क्रम_each_entry_safe(cur_mode, t, &connector->probed_modes, head) अणु
		cur_mode->type &= ~DRM_MODE_TYPE_PREFERRED;

		अगर (cur_mode == preferred_mode)
			जारी;

		/* Largest mode is preferred */
		अगर (MODE_SIZE(cur_mode) > MODE_SIZE(preferred_mode))
			preferred_mode = cur_mode;

		cur_vrefresh = drm_mode_vrefresh(cur_mode);
		preferred_vrefresh = drm_mode_vrefresh(preferred_mode);
		/* At a given size, try to get बंदst to target refresh */
		अगर ((MODE_SIZE(cur_mode) == MODE_SIZE(preferred_mode)) &&
		    MODE_REFRESH_DIFF(cur_vrefresh, target_refresh) <
		    MODE_REFRESH_DIFF(preferred_vrefresh, target_refresh)) अणु
			preferred_mode = cur_mode;
		पूर्ण
	पूर्ण

	preferred_mode->type |= DRM_MODE_TYPE_PREFERRED;
पूर्ण

अटल bool
mode_is_rb(स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस (mode->htotal - mode->hdisplay == 160) &&
	       (mode->hsync_end - mode->hdisplay == 80) &&
	       (mode->hsync_end - mode->hsync_start == 32) &&
	       (mode->vsync_start - mode->vdisplay == 3);
पूर्ण

/*
 * drm_mode_find_dmt - Create a copy of a mode अगर present in DMT
 * @dev: Device to duplicate against
 * @hsize: Mode width
 * @vsize: Mode height
 * @fresh: Mode refresh rate
 * @rb: Mode reduced-blanking-ness
 *
 * Walk the DMT mode list looking क्रम a match क्रम the given parameters.
 *
 * Return: A newly allocated copy of the mode, or शून्य अगर not found.
 */
काष्ठा drm_display_mode *drm_mode_find_dmt(काष्ठा drm_device *dev,
					   पूर्णांक hsize, पूर्णांक vsize, पूर्णांक fresh,
					   bool rb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(drm_dmt_modes); i++) अणु
		स्थिर काष्ठा drm_display_mode *ptr = &drm_dmt_modes[i];

		अगर (hsize != ptr->hdisplay)
			जारी;
		अगर (vsize != ptr->vdisplay)
			जारी;
		अगर (fresh != drm_mode_vrefresh(ptr))
			जारी;
		अगर (rb != mode_is_rb(ptr))
			जारी;

		वापस drm_mode_duplicate(dev, ptr);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_mode_find_dmt);

अटल bool is_display_descriptor(स्थिर u8 d[18], u8 tag)
अणु
	वापस d[0] == 0x00 && d[1] == 0x00 &&
		d[2] == 0x00 && d[3] == tag;
पूर्ण

अटल bool is_detailed_timing_descriptor(स्थिर u8 d[18])
अणु
	वापस d[0] != 0x00 || d[1] != 0x00;
पूर्ण

प्रकार व्योम detailed_cb(काष्ठा detailed_timing *timing, व्योम *closure);

अटल व्योम
cea_क्रम_each_detailed_block(u8 *ext, detailed_cb *cb, व्योम *closure)
अणु
	पूर्णांक i, n;
	u8 d = ext[0x02];
	u8 *det_base = ext + d;

	अगर (d < 4 || d > 127)
		वापस;

	n = (127 - d) / 18;
	क्रम (i = 0; i < n; i++)
		cb((काष्ठा detailed_timing *)(det_base + 18 * i), closure);
पूर्ण

अटल व्योम
vtb_क्रम_each_detailed_block(u8 *ext, detailed_cb *cb, व्योम *closure)
अणु
	अचिन्हित पूर्णांक i, n = min((पूर्णांक)ext[0x02], 6);
	u8 *det_base = ext + 5;

	अगर (ext[0x01] != 1)
		वापस; /* unknown version */

	क्रम (i = 0; i < n; i++)
		cb((काष्ठा detailed_timing *)(det_base + 18 * i), closure);
पूर्ण

अटल व्योम
drm_क्रम_each_detailed_block(u8 *raw_edid, detailed_cb *cb, व्योम *closure)
अणु
	पूर्णांक i;
	काष्ठा edid *edid = (काष्ठा edid *)raw_edid;

	अगर (edid == शून्य)
		वापस;

	क्रम (i = 0; i < EDID_DETAILED_TIMINGS; i++)
		cb(&(edid->detailed_timings[i]), closure);

	क्रम (i = 1; i <= raw_edid[0x7e]; i++) अणु
		u8 *ext = raw_edid + (i * EDID_LENGTH);

		चयन (*ext) अणु
		हाल CEA_EXT:
			cea_क्रम_each_detailed_block(ext, cb, closure);
			अवरोध;
		हाल VTB_EXT:
			vtb_क्रम_each_detailed_block(ext, cb, closure);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
is_rb(काष्ठा detailed_timing *t, व्योम *data)
अणु
	u8 *r = (u8 *)t;

	अगर (!is_display_descriptor(r, EDID_DETAIL_MONITOR_RANGE))
		वापस;

	अगर (r[15] & 0x10)
		*(bool *)data = true;
पूर्ण

/* EDID 1.4 defines this explicitly.  For EDID 1.3, we guess, badly. */
अटल bool
drm_monitor_supports_rb(काष्ठा edid *edid)
अणु
	अगर (edid->revision >= 4) अणु
		bool ret = false;

		drm_क्रम_each_detailed_block((u8 *)edid, is_rb, &ret);
		वापस ret;
	पूर्ण

	वापस ((edid->input & DRM_EDID_INPUT_DIGITAL) != 0);
पूर्ण

अटल व्योम
find_gtf2(काष्ठा detailed_timing *t, व्योम *data)
अणु
	u8 *r = (u8 *)t;

	अगर (!is_display_descriptor(r, EDID_DETAIL_MONITOR_RANGE))
		वापस;

	अगर (r[10] == 0x02)
		*(u8 **)data = r;
पूर्ण

/* Secondary GTF curve kicks in above some अवरोध frequency */
अटल पूर्णांक
drm_gtf2_hअवरोध(काष्ठा edid *edid)
अणु
	u8 *r = शून्य;

	drm_क्रम_each_detailed_block((u8 *)edid, find_gtf2, &r);
	वापस r ? (r[12] * 2) : 0;
पूर्ण

अटल पूर्णांक
drm_gtf2_2c(काष्ठा edid *edid)
अणु
	u8 *r = शून्य;

	drm_क्रम_each_detailed_block((u8 *)edid, find_gtf2, &r);
	वापस r ? r[13] : 0;
पूर्ण

अटल पूर्णांक
drm_gtf2_m(काष्ठा edid *edid)
अणु
	u8 *r = शून्य;

	drm_क्रम_each_detailed_block((u8 *)edid, find_gtf2, &r);
	वापस r ? (r[15] << 8) + r[14] : 0;
पूर्ण

अटल पूर्णांक
drm_gtf2_k(काष्ठा edid *edid)
अणु
	u8 *r = शून्य;

	drm_क्रम_each_detailed_block((u8 *)edid, find_gtf2, &r);
	वापस r ? r[16] : 0;
पूर्ण

अटल पूर्णांक
drm_gtf2_2j(काष्ठा edid *edid)
अणु
	u8 *r = शून्य;

	drm_क्रम_each_detailed_block((u8 *)edid, find_gtf2, &r);
	वापस r ? r[17] : 0;
पूर्ण

/**
 * standard_timing_level - get std. timing level(CVT/GTF/DMT)
 * @edid: EDID block to scan
 */
अटल पूर्णांक standard_timing_level(काष्ठा edid *edid)
अणु
	अगर (edid->revision >= 2) अणु
		अगर (edid->revision >= 4 && (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF))
			वापस LEVEL_CVT;
		अगर (drm_gtf2_hअवरोध(edid))
			वापस LEVEL_GTF2;
		अगर (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)
			वापस LEVEL_GTF;
	पूर्ण
	वापस LEVEL_DMT;
पूर्ण

/*
 * 0 is reserved.  The spec says 0x01 fill क्रम unused timings.  Some old
 * monitors fill with ascii space (0x20) instead.
 */
अटल पूर्णांक
bad_std_timing(u8 a, u8 b)
अणु
	वापस (a == 0x00 && b == 0x00) ||
	       (a == 0x01 && b == 0x01) ||
	       (a == 0x20 && b == 0x20);
पूर्ण

अटल पूर्णांक drm_mode_hsync(स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->htotal <= 0)
		वापस 0;

	वापस DIV_ROUND_CLOSEST(mode->घड़ी, mode->htotal);
पूर्ण

/**
 * drm_mode_std - convert standard mode info (width, height, refresh) पूर्णांकo mode
 * @connector: connector of क्रम the EDID block
 * @edid: EDID block to scan
 * @t: standard timing params
 *
 * Take the standard timing params (in this हाल width, aspect, and refresh)
 * and convert them पूर्णांकo a real mode using CVT/GTF/DMT.
 */
अटल काष्ठा drm_display_mode *
drm_mode_std(काष्ठा drm_connector *connector, काष्ठा edid *edid,
	     काष्ठा std_timing *t)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *m, *mode = शून्य;
	पूर्णांक hsize, vsize;
	पूर्णांक vrefresh_rate;
	अचिन्हित aspect_ratio = (t->vfreq_aspect & EDID_TIMING_ASPECT_MASK)
		>> EDID_TIMING_ASPECT_SHIFT;
	अचिन्हित vfreq = (t->vfreq_aspect & EDID_TIMING_VFREQ_MASK)
		>> EDID_TIMING_VFREQ_SHIFT;
	पूर्णांक timing_level = standard_timing_level(edid);

	अगर (bad_std_timing(t->hsize, t->vfreq_aspect))
		वापस शून्य;

	/* According to the EDID spec, the hdisplay = hsize * 8 + 248 */
	hsize = t->hsize * 8 + 248;
	/* vrefresh_rate = vfreq + 60 */
	vrefresh_rate = vfreq + 60;
	/* the vdisplay is calculated based on the aspect ratio */
	अगर (aspect_ratio == 0) अणु
		अगर (edid->revision < 3)
			vsize = hsize;
		अन्यथा
			vsize = (hsize * 10) / 16;
	पूर्ण अन्यथा अगर (aspect_ratio == 1)
		vsize = (hsize * 3) / 4;
	अन्यथा अगर (aspect_ratio == 2)
		vsize = (hsize * 4) / 5;
	अन्यथा
		vsize = (hsize * 9) / 16;

	/* HDTV hack, part 1 */
	अगर (vrefresh_rate == 60 &&
	    ((hsize == 1360 && vsize == 765) ||
	     (hsize == 1368 && vsize == 769))) अणु
		hsize = 1366;
		vsize = 768;
	पूर्ण

	/*
	 * If this connector alपढ़ोy has a mode क्रम this size and refresh
	 * rate (because it came from detailed or CVT info), use that
	 * instead.  This way we करोn't have to guess at पूर्णांकerlace or
	 * reduced blanking.
	 */
	list_क्रम_each_entry(m, &connector->probed_modes, head)
		अगर (m->hdisplay == hsize && m->vdisplay == vsize &&
		    drm_mode_vrefresh(m) == vrefresh_rate)
			वापस शून्य;

	/* HDTV hack, part 2 */
	अगर (hsize == 1366 && vsize == 768 && vrefresh_rate == 60) अणु
		mode = drm_cvt_mode(dev, 1366, 768, vrefresh_rate, 0, 0,
				    false);
		अगर (!mode)
			वापस शून्य;
		mode->hdisplay = 1366;
		mode->hsync_start = mode->hsync_start - 1;
		mode->hsync_end = mode->hsync_end - 1;
		वापस mode;
	पूर्ण

	/* check whether it can be found in शेष mode table */
	अगर (drm_monitor_supports_rb(edid)) अणु
		mode = drm_mode_find_dmt(dev, hsize, vsize, vrefresh_rate,
					 true);
		अगर (mode)
			वापस mode;
	पूर्ण
	mode = drm_mode_find_dmt(dev, hsize, vsize, vrefresh_rate, false);
	अगर (mode)
		वापस mode;

	/* okay, generate it */
	चयन (timing_level) अणु
	हाल LEVEL_DMT:
		अवरोध;
	हाल LEVEL_GTF:
		mode = drm_gtf_mode(dev, hsize, vsize, vrefresh_rate, 0, 0);
		अवरोध;
	हाल LEVEL_GTF2:
		/*
		 * This is potentially wrong अगर there's ever a monitor with
		 * more than one ranges section, each claiming a dअगरferent
		 * secondary GTF curve.  Please करोn't करो that.
		 */
		mode = drm_gtf_mode(dev, hsize, vsize, vrefresh_rate, 0, 0);
		अगर (!mode)
			वापस शून्य;
		अगर (drm_mode_hsync(mode) > drm_gtf2_hअवरोध(edid)) अणु
			drm_mode_destroy(dev, mode);
			mode = drm_gtf_mode_complex(dev, hsize, vsize,
						    vrefresh_rate, 0, 0,
						    drm_gtf2_m(edid),
						    drm_gtf2_2c(edid),
						    drm_gtf2_k(edid),
						    drm_gtf2_2j(edid));
		पूर्ण
		अवरोध;
	हाल LEVEL_CVT:
		mode = drm_cvt_mode(dev, hsize, vsize, vrefresh_rate, 0, 0,
				    false);
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

/*
 * EDID is delightfully ambiguous about how पूर्णांकerlaced modes are to be
 * encoded.  Our पूर्णांकernal representation is of frame height, but some
 * HDTV detailed timings are encoded as field height.
 *
 * The क्रमmat list here is from CEA, in frame size.  Technically we
 * should be checking refresh rate too.  Whatever.
 */
अटल व्योम
drm_mode_करो_पूर्णांकerlace_quirk(काष्ठा drm_display_mode *mode,
			    काष्ठा detailed_pixel_timing *pt)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा अणु
		पूर्णांक w, h;
	पूर्ण cea_पूर्णांकerlaced[] = अणु
		अणु 1920, 1080 पूर्ण,
		अणु  720,  480 पूर्ण,
		अणु 1440,  480 पूर्ण,
		अणु 2880,  480 पूर्ण,
		अणु  720,  576 पूर्ण,
		अणु 1440,  576 पूर्ण,
		अणु 2880,  576 पूर्ण,
	पूर्ण;

	अगर (!(pt->misc & DRM_EDID_PT_INTERLACED))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(cea_पूर्णांकerlaced); i++) अणु
		अगर ((mode->hdisplay == cea_पूर्णांकerlaced[i].w) &&
		    (mode->vdisplay == cea_पूर्णांकerlaced[i].h / 2)) अणु
			mode->vdisplay *= 2;
			mode->vsync_start *= 2;
			mode->vsync_end *= 2;
			mode->vtotal *= 2;
			mode->vtotal |= 1;
		पूर्ण
	पूर्ण

	mode->flags |= DRM_MODE_FLAG_INTERLACE;
पूर्ण

/**
 * drm_mode_detailed - create a new mode from an EDID detailed timing section
 * @dev: DRM device (needed to create new mode)
 * @edid: EDID block
 * @timing: EDID detailed timing info
 * @quirks: quirks to apply
 *
 * An EDID detailed timing block contains enough info क्रम us to create and
 * वापस a new काष्ठा drm_display_mode.
 */
अटल काष्ठा drm_display_mode *drm_mode_detailed(काष्ठा drm_device *dev,
						  काष्ठा edid *edid,
						  काष्ठा detailed_timing *timing,
						  u32 quirks)
अणु
	काष्ठा drm_display_mode *mode;
	काष्ठा detailed_pixel_timing *pt = &timing->data.pixel_data;
	अचिन्हित hactive = (pt->hactive_hblank_hi & 0xf0) << 4 | pt->hactive_lo;
	अचिन्हित vactive = (pt->vactive_vblank_hi & 0xf0) << 4 | pt->vactive_lo;
	अचिन्हित hblank = (pt->hactive_hblank_hi & 0xf) << 8 | pt->hblank_lo;
	अचिन्हित vblank = (pt->vactive_vblank_hi & 0xf) << 8 | pt->vblank_lo;
	अचिन्हित hsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc0) << 2 | pt->hsync_offset_lo;
	अचिन्हित hsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x30) << 4 | pt->hsync_pulse_width_lo;
	अचिन्हित vsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc) << 2 | pt->vsync_offset_pulse_width_lo >> 4;
	अचिन्हित vsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x3) << 4 | (pt->vsync_offset_pulse_width_lo & 0xf);

	/* ignore tiny modes */
	अगर (hactive < 64 || vactive < 64)
		वापस शून्य;

	अगर (pt->misc & DRM_EDID_PT_STEREO) अणु
		DRM_DEBUG_KMS("stereo mode not supported\n");
		वापस शून्य;
	पूर्ण
	अगर (!(pt->misc & DRM_EDID_PT_SEPARATE_SYNC)) अणु
		DRM_DEBUG_KMS("composite sync not supported\n");
	पूर्ण

	/* it is incorrect अगर hsync/vsync width is zero */
	अगर (!hsync_pulse_width || !vsync_pulse_width) अणु
		DRM_DEBUG_KMS("Incorrect Detailed timing. "
				"Wrong Hsync/Vsync pulse width\n");
		वापस शून्य;
	पूर्ण

	अगर (quirks & EDID_QUIRK_FORCE_REDUCED_BLANKING) अणु
		mode = drm_cvt_mode(dev, hactive, vactive, 60, true, false, false);
		अगर (!mode)
			वापस शून्य;

		जाओ set_size;
	पूर्ण

	mode = drm_mode_create(dev);
	अगर (!mode)
		वापस शून्य;

	अगर (quirks & EDID_QUIRK_135_CLOCK_TOO_HIGH)
		timing->pixel_घड़ी = cpu_to_le16(1088);

	mode->घड़ी = le16_to_cpu(timing->pixel_घड़ी) * 10;

	mode->hdisplay = hactive;
	mode->hsync_start = mode->hdisplay + hsync_offset;
	mode->hsync_end = mode->hsync_start + hsync_pulse_width;
	mode->htotal = mode->hdisplay + hblank;

	mode->vdisplay = vactive;
	mode->vsync_start = mode->vdisplay + vsync_offset;
	mode->vsync_end = mode->vsync_start + vsync_pulse_width;
	mode->vtotal = mode->vdisplay + vblank;

	/* Some EDIDs have bogus h/vtotal values */
	अगर (mode->hsync_end > mode->htotal)
		mode->htotal = mode->hsync_end + 1;
	अगर (mode->vsync_end > mode->vtotal)
		mode->vtotal = mode->vsync_end + 1;

	drm_mode_करो_पूर्णांकerlace_quirk(mode, pt);

	अगर (quirks & EDID_QUIRK_DETAILED_SYNC_PP) अणु
		pt->misc |= DRM_EDID_PT_HSYNC_POSITIVE | DRM_EDID_PT_VSYNC_POSITIVE;
	पूर्ण

	mode->flags |= (pt->misc & DRM_EDID_PT_HSYNC_POSITIVE) ?
		DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= (pt->misc & DRM_EDID_PT_VSYNC_POSITIVE) ?
		DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;

set_size:
	mode->width_mm = pt->width_mm_lo | (pt->width_height_mm_hi & 0xf0) << 4;
	mode->height_mm = pt->height_mm_lo | (pt->width_height_mm_hi & 0xf) << 8;

	अगर (quirks & EDID_QUIRK_DETAILED_IN_CM) अणु
		mode->width_mm *= 10;
		mode->height_mm *= 10;
	पूर्ण

	अगर (quirks & EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE) अणु
		mode->width_mm = edid->width_cm * 10;
		mode->height_mm = edid->height_cm * 10;
	पूर्ण

	mode->type = DRM_MODE_TYPE_DRIVER;
	drm_mode_set_name(mode);

	वापस mode;
पूर्ण

अटल bool
mode_in_hsync_range(स्थिर काष्ठा drm_display_mode *mode,
		    काष्ठा edid *edid, u8 *t)
अणु
	पूर्णांक hsync, hmin, hmax;

	hmin = t[7];
	अगर (edid->revision >= 4)
	    hmin += ((t[4] & 0x04) ? 255 : 0);
	hmax = t[8];
	अगर (edid->revision >= 4)
	    hmax += ((t[4] & 0x08) ? 255 : 0);
	hsync = drm_mode_hsync(mode);

	वापस (hsync <= hmax && hsync >= hmin);
पूर्ण

अटल bool
mode_in_vsync_range(स्थिर काष्ठा drm_display_mode *mode,
		    काष्ठा edid *edid, u8 *t)
अणु
	पूर्णांक vsync, vmin, vmax;

	vmin = t[5];
	अगर (edid->revision >= 4)
	    vmin += ((t[4] & 0x01) ? 255 : 0);
	vmax = t[6];
	अगर (edid->revision >= 4)
	    vmax += ((t[4] & 0x02) ? 255 : 0);
	vsync = drm_mode_vrefresh(mode);

	वापस (vsync <= vmax && vsync >= vmin);
पूर्ण

अटल u32
range_pixel_घड़ी(काष्ठा edid *edid, u8 *t)
अणु
	/* unspecअगरied */
	अगर (t[9] == 0 || t[9] == 255)
		वापस 0;

	/* 1.4 with CVT support gives us real precision, yay */
	अगर (edid->revision >= 4 && t[10] == 0x04)
		वापस (t[9] * 10000) - ((t[12] >> 2) * 250);

	/* 1.3 is pathetic, so fuzz up a bit */
	वापस t[9] * 10000 + 5001;
पूर्ण

अटल bool
mode_in_range(स्थिर काष्ठा drm_display_mode *mode, काष्ठा edid *edid,
	      काष्ठा detailed_timing *timing)
अणु
	u32 max_घड़ी;
	u8 *t = (u8 *)timing;

	अगर (!mode_in_hsync_range(mode, edid, t))
		वापस false;

	अगर (!mode_in_vsync_range(mode, edid, t))
		वापस false;

	अगर ((max_घड़ी = range_pixel_घड़ी(edid, t)))
		अगर (mode->घड़ी > max_घड़ी)
			वापस false;

	/* 1.4 max horizontal check */
	अगर (edid->revision >= 4 && t[10] == 0x04)
		अगर (t[13] && mode->hdisplay > 8 * (t[13] + (256 * (t[12]&0x3))))
			वापस false;

	अगर (mode_is_rb(mode) && !drm_monitor_supports_rb(edid))
		वापस false;

	वापस true;
पूर्ण

अटल bool valid_inferred_mode(स्थिर काष्ठा drm_connector *connector,
				स्थिर काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा drm_display_mode *m;
	bool ok = false;

	list_क्रम_each_entry(m, &connector->probed_modes, head) अणु
		अगर (mode->hdisplay == m->hdisplay &&
		    mode->vdisplay == m->vdisplay &&
		    drm_mode_vrefresh(mode) == drm_mode_vrefresh(m))
			वापस false; /* duplicated */
		अगर (mode->hdisplay <= m->hdisplay &&
		    mode->vdisplay <= m->vdisplay)
			ok = true;
	पूर्ण
	वापस ok;
पूर्ण

अटल पूर्णांक
drm_dmt_modes_क्रम_range(काष्ठा drm_connector *connector, काष्ठा edid *edid,
			काष्ठा detailed_timing *timing)
अणु
	पूर्णांक i, modes = 0;
	काष्ठा drm_display_mode *newmode;
	काष्ठा drm_device *dev = connector->dev;

	क्रम (i = 0; i < ARRAY_SIZE(drm_dmt_modes); i++) अणु
		अगर (mode_in_range(drm_dmt_modes + i, edid, timing) &&
		    valid_inferred_mode(connector, drm_dmt_modes + i)) अणु
			newmode = drm_mode_duplicate(dev, &drm_dmt_modes[i]);
			अगर (newmode) अणु
				drm_mode_probed_add(connector, newmode);
				modes++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस modes;
पूर्ण

/* fix up 1366x768 mode from 1368x768;
 * GFT/CVT can't express 1366 width which isn't भागidable by 8
 */
व्योम drm_mode_fixup_1366x768(काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->hdisplay == 1368 && mode->vdisplay == 768) अणु
		mode->hdisplay = 1366;
		mode->hsync_start--;
		mode->hsync_end--;
		drm_mode_set_name(mode);
	पूर्ण
पूर्ण

अटल पूर्णांक
drm_gtf_modes_क्रम_range(काष्ठा drm_connector *connector, काष्ठा edid *edid,
			काष्ठा detailed_timing *timing)
अणु
	पूर्णांक i, modes = 0;
	काष्ठा drm_display_mode *newmode;
	काष्ठा drm_device *dev = connector->dev;

	क्रम (i = 0; i < ARRAY_SIZE(extra_modes); i++) अणु
		स्थिर काष्ठा minimode *m = &extra_modes[i];

		newmode = drm_gtf_mode(dev, m->w, m->h, m->r, 0, 0);
		अगर (!newmode)
			वापस modes;

		drm_mode_fixup_1366x768(newmode);
		अगर (!mode_in_range(newmode, edid, timing) ||
		    !valid_inferred_mode(connector, newmode)) अणु
			drm_mode_destroy(dev, newmode);
			जारी;
		पूर्ण

		drm_mode_probed_add(connector, newmode);
		modes++;
	पूर्ण

	वापस modes;
पूर्ण

अटल पूर्णांक
drm_cvt_modes_क्रम_range(काष्ठा drm_connector *connector, काष्ठा edid *edid,
			काष्ठा detailed_timing *timing)
अणु
	पूर्णांक i, modes = 0;
	काष्ठा drm_display_mode *newmode;
	काष्ठा drm_device *dev = connector->dev;
	bool rb = drm_monitor_supports_rb(edid);

	क्रम (i = 0; i < ARRAY_SIZE(extra_modes); i++) अणु
		स्थिर काष्ठा minimode *m = &extra_modes[i];

		newmode = drm_cvt_mode(dev, m->w, m->h, m->r, rb, 0, 0);
		अगर (!newmode)
			वापस modes;

		drm_mode_fixup_1366x768(newmode);
		अगर (!mode_in_range(newmode, edid, timing) ||
		    !valid_inferred_mode(connector, newmode)) अणु
			drm_mode_destroy(dev, newmode);
			जारी;
		पूर्ण

		drm_mode_probed_add(connector, newmode);
		modes++;
	पूर्ण

	वापस modes;
पूर्ण

अटल व्योम
करो_inferred_modes(काष्ठा detailed_timing *timing, व्योम *c)
अणु
	काष्ठा detailed_mode_closure *closure = c;
	काष्ठा detailed_non_pixel *data = &timing->data.other_data;
	काष्ठा detailed_data_monitor_range *range = &data->data.range;

	अगर (!is_display_descriptor((स्थिर u8 *)timing, EDID_DETAIL_MONITOR_RANGE))
		वापस;

	closure->modes += drm_dmt_modes_क्रम_range(closure->connector,
						  closure->edid,
						  timing);

	अगर (!version_greater(closure->edid, 1, 1))
		वापस; /* GTF not defined yet */

	चयन (range->flags) अणु
	हाल 0x02: /* secondary gtf, XXX could करो more */
	हाल 0x00: /* शेष gtf */
		closure->modes += drm_gtf_modes_क्रम_range(closure->connector,
							  closure->edid,
							  timing);
		अवरोध;
	हाल 0x04: /* cvt, only in 1.4+ */
		अगर (!version_greater(closure->edid, 1, 3))
			अवरोध;

		closure->modes += drm_cvt_modes_क्रम_range(closure->connector,
							  closure->edid,
							  timing);
		अवरोध;
	हाल 0x01: /* just the ranges, no क्रमmula */
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
add_inferred_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	काष्ठा detailed_mode_closure closure = अणु
		.connector = connector,
		.edid = edid,
	पूर्ण;

	अगर (version_greater(edid, 1, 0))
		drm_क्रम_each_detailed_block((u8 *)edid, करो_inferred_modes,
					    &closure);

	वापस closure.modes;
पूर्ण

अटल पूर्णांक
drm_est3_modes(काष्ठा drm_connector *connector, काष्ठा detailed_timing *timing)
अणु
	पूर्णांक i, j, m, modes = 0;
	काष्ठा drm_display_mode *mode;
	u8 *est = ((u8 *)timing) + 6;

	क्रम (i = 0; i < 6; i++) अणु
		क्रम (j = 7; j >= 0; j--) अणु
			m = (i * 8) + (7 - j);
			अगर (m >= ARRAY_SIZE(est3_modes))
				अवरोध;
			अगर (est[i] & (1 << j)) अणु
				mode = drm_mode_find_dmt(connector->dev,
							 est3_modes[m].w,
							 est3_modes[m].h,
							 est3_modes[m].r,
							 est3_modes[m].rb);
				अगर (mode) अणु
					drm_mode_probed_add(connector, mode);
					modes++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस modes;
पूर्ण

अटल व्योम
करो_established_modes(काष्ठा detailed_timing *timing, व्योम *c)
अणु
	काष्ठा detailed_mode_closure *closure = c;

	अगर (!is_display_descriptor((स्थिर u8 *)timing, EDID_DETAIL_EST_TIMINGS))
		वापस;

	closure->modes += drm_est3_modes(closure->connector, timing);
पूर्ण

/**
 * add_established_modes - get est. modes from EDID and add them
 * @connector: connector to add mode(s) to
 * @edid: EDID block to scan
 *
 * Each EDID block contains a biपंचांगap of the supported "established modes" list
 * (defined above).  Tease them out and add them to the global modes list.
 */
अटल पूर्णांक
add_established_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	काष्ठा drm_device *dev = connector->dev;
	अचिन्हित दीर्घ est_bits = edid->established_timings.t1 |
		(edid->established_timings.t2 << 8) |
		((edid->established_timings.mfg_rsvd & 0x80) << 9);
	पूर्णांक i, modes = 0;
	काष्ठा detailed_mode_closure closure = अणु
		.connector = connector,
		.edid = edid,
	पूर्ण;

	क्रम (i = 0; i <= EDID_EST_TIMINGS; i++) अणु
		अगर (est_bits & (1<<i)) अणु
			काष्ठा drm_display_mode *newmode;

			newmode = drm_mode_duplicate(dev, &edid_est_modes[i]);
			अगर (newmode) अणु
				drm_mode_probed_add(connector, newmode);
				modes++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (version_greater(edid, 1, 0))
		    drm_क्रम_each_detailed_block((u8 *)edid,
						करो_established_modes, &closure);

	वापस modes + closure.modes;
पूर्ण

अटल व्योम
करो_standard_modes(काष्ठा detailed_timing *timing, व्योम *c)
अणु
	काष्ठा detailed_mode_closure *closure = c;
	काष्ठा detailed_non_pixel *data = &timing->data.other_data;
	काष्ठा drm_connector *connector = closure->connector;
	काष्ठा edid *edid = closure->edid;
	पूर्णांक i;

	अगर (!is_display_descriptor((स्थिर u8 *)timing, EDID_DETAIL_STD_MODES))
		वापस;

	क्रम (i = 0; i < 6; i++) अणु
		काष्ठा std_timing *std = &data->data.timings[i];
		काष्ठा drm_display_mode *newmode;

		newmode = drm_mode_std(connector, edid, std);
		अगर (newmode) अणु
			drm_mode_probed_add(connector, newmode);
			closure->modes++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * add_standard_modes - get std. modes from EDID and add them
 * @connector: connector to add mode(s) to
 * @edid: EDID block to scan
 *
 * Standard modes can be calculated using the appropriate standard (DMT,
 * GTF or CVT. Grab them from @edid and add them to the list.
 */
अटल पूर्णांक
add_standard_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	पूर्णांक i, modes = 0;
	काष्ठा detailed_mode_closure closure = अणु
		.connector = connector,
		.edid = edid,
	पूर्ण;

	क्रम (i = 0; i < EDID_STD_TIMINGS; i++) अणु
		काष्ठा drm_display_mode *newmode;

		newmode = drm_mode_std(connector, edid,
				       &edid->standard_timings[i]);
		अगर (newmode) अणु
			drm_mode_probed_add(connector, newmode);
			modes++;
		पूर्ण
	पूर्ण

	अगर (version_greater(edid, 1, 0))
		drm_क्रम_each_detailed_block((u8 *)edid, करो_standard_modes,
					    &closure);

	/* XXX should also look क्रम standard codes in VTB blocks */

	वापस modes + closure.modes;
पूर्ण

अटल पूर्णांक drm_cvt_modes(काष्ठा drm_connector *connector,
			 काष्ठा detailed_timing *timing)
अणु
	पूर्णांक i, j, modes = 0;
	काष्ठा drm_display_mode *newmode;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा cvt_timing *cvt;
	स्थिर पूर्णांक rates[] = अणु 60, 85, 75, 60, 50 पूर्ण;
	स्थिर u8 empty[3] = अणु 0, 0, 0 पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक width, height;

		cvt = &(timing->data.other_data.data.cvt[i]);

		अगर (!स_भेद(cvt->code, empty, 3))
			जारी;

		height = (cvt->code[0] + ((cvt->code[1] & 0xf0) << 4) + 1) * 2;
		चयन (cvt->code[1] & 0x0c) अणु
		/* शेष - because compiler करोesn't see that we've क्रमागतerated all हालs */
		शेष:
		हाल 0x00:
			width = height * 4 / 3;
			अवरोध;
		हाल 0x04:
			width = height * 16 / 9;
			अवरोध;
		हाल 0x08:
			width = height * 16 / 10;
			अवरोध;
		हाल 0x0c:
			width = height * 15 / 9;
			अवरोध;
		पूर्ण

		क्रम (j = 1; j < 5; j++) अणु
			अगर (cvt->code[2] & (1 << j)) अणु
				newmode = drm_cvt_mode(dev, width, height,
						       rates[j], j == 0,
						       false, false);
				अगर (newmode) अणु
					drm_mode_probed_add(connector, newmode);
					modes++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस modes;
पूर्ण

अटल व्योम
करो_cvt_mode(काष्ठा detailed_timing *timing, व्योम *c)
अणु
	काष्ठा detailed_mode_closure *closure = c;

	अगर (!is_display_descriptor((स्थिर u8 *)timing, EDID_DETAIL_CVT_3BYTE))
		वापस;

	closure->modes += drm_cvt_modes(closure->connector, timing);
पूर्ण

अटल पूर्णांक
add_cvt_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	काष्ठा detailed_mode_closure closure = अणु
		.connector = connector,
		.edid = edid,
	पूर्ण;

	अगर (version_greater(edid, 1, 2))
		drm_क्रम_each_detailed_block((u8 *)edid, करो_cvt_mode, &closure);

	/* XXX should also look क्रम CVT codes in VTB blocks */

	वापस closure.modes;
पूर्ण

अटल व्योम fixup_detailed_cea_mode_घड़ी(काष्ठा drm_display_mode *mode);

अटल व्योम
करो_detailed_mode(काष्ठा detailed_timing *timing, व्योम *c)
अणु
	काष्ठा detailed_mode_closure *closure = c;
	काष्ठा drm_display_mode *newmode;

	अगर (!is_detailed_timing_descriptor((स्थिर u8 *)timing))
		वापस;

	newmode = drm_mode_detailed(closure->connector->dev,
				    closure->edid, timing,
				    closure->quirks);
	अगर (!newmode)
		वापस;

	अगर (closure->preferred)
		newmode->type |= DRM_MODE_TYPE_PREFERRED;

	/*
	 * Detailed modes are limited to 10kHz pixel घड़ी resolution,
	 * so fix up anything that looks like CEA/HDMI mode, but the घड़ी
	 * is just slightly off.
	 */
	fixup_detailed_cea_mode_घड़ी(newmode);

	drm_mode_probed_add(closure->connector, newmode);
	closure->modes++;
	closure->preferred = false;
पूर्ण

/*
 * add_detailed_modes - Add modes from detailed timings
 * @connector: attached connector
 * @edid: EDID block to scan
 * @quirks: quirks to apply
 */
अटल पूर्णांक
add_detailed_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid,
		   u32 quirks)
अणु
	काष्ठा detailed_mode_closure closure = अणु
		.connector = connector,
		.edid = edid,
		.preferred = true,
		.quirks = quirks,
	पूर्ण;

	अगर (closure.preferred && !version_greater(edid, 1, 3))
		closure.preferred =
		    (edid->features & DRM_EDID_FEATURE_PREFERRED_TIMING);

	drm_क्रम_each_detailed_block((u8 *)edid, करो_detailed_mode, &closure);

	वापस closure.modes;
पूर्ण

#घोषणा AUDIO_BLOCK	0x01
#घोषणा VIDEO_BLOCK     0x02
#घोषणा VENDOR_BLOCK    0x03
#घोषणा SPEAKER_BLOCK	0x04
#घोषणा HDR_STATIC_METADATA_BLOCK	0x6
#घोषणा USE_EXTENDED_TAG 0x07
#घोषणा EXT_VIDEO_CAPABILITY_BLOCK 0x00
#घोषणा EXT_VIDEO_DATA_BLOCK_420	0x0E
#घोषणा EXT_VIDEO_CAP_BLOCK_Y420CMDB 0x0F
#घोषणा EDID_BASIC_AUDIO	(1 << 6)
#घोषणा EDID_CEA_YCRCB444	(1 << 5)
#घोषणा EDID_CEA_YCRCB422	(1 << 4)
#घोषणा EDID_CEA_VCDB_QS	(1 << 6)

/*
 * Search EDID क्रम CEA extension block.
 */
स्थिर u8 *drm_find_edid_extension(स्थिर काष्ठा edid *edid,
				  पूर्णांक ext_id, पूर्णांक *ext_index)
अणु
	स्थिर u8 *edid_ext = शून्य;
	पूर्णांक i;

	/* No EDID or EDID extensions */
	अगर (edid == शून्य || edid->extensions == 0)
		वापस शून्य;

	/* Find CEA extension */
	क्रम (i = *ext_index; i < edid->extensions; i++) अणु
		edid_ext = (स्थिर u8 *)edid + EDID_LENGTH * (i + 1);
		अगर (edid_ext[0] == ext_id)
			अवरोध;
	पूर्ण

	अगर (i >= edid->extensions)
		वापस शून्य;

	*ext_index = i + 1;

	वापस edid_ext;
पूर्ण

अटल स्थिर u8 *drm_find_cea_extension(स्थिर काष्ठा edid *edid)
अणु
	स्थिर काष्ठा displayid_block *block;
	काष्ठा displayid_iter iter;
	स्थिर u8 *cea;
	पूर्णांक ext_index = 0;

	/* Look क्रम a top level CEA extension block */
	/* FIXME: make callers iterate through multiple CEA ext blocks? */
	cea = drm_find_edid_extension(edid, CEA_EXT, &ext_index);
	अगर (cea)
		वापस cea;

	/* CEA blocks can also be found embedded in a DisplayID block */
	displayid_iter_edid_begin(edid, &iter);
	displayid_iter_क्रम_each(block, &iter) अणु
		अगर (block->tag == DATA_BLOCK_CTA) अणु
			cea = (स्थिर u8 *)block;
			अवरोध;
		पूर्ण
	पूर्ण
	displayid_iter_end(&iter);

	वापस cea;
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा drm_display_mode *cea_mode_क्रम_vic(u8 vic)
अणु
	BUILD_BUG_ON(1 + ARRAY_SIZE(edid_cea_modes_1) - 1 != 127);
	BUILD_BUG_ON(193 + ARRAY_SIZE(edid_cea_modes_193) - 1 != 219);

	अगर (vic >= 1 && vic < 1 + ARRAY_SIZE(edid_cea_modes_1))
		वापस &edid_cea_modes_1[vic - 1];
	अगर (vic >= 193 && vic < 193 + ARRAY_SIZE(edid_cea_modes_193))
		वापस &edid_cea_modes_193[vic - 193];
	वापस शून्य;
पूर्ण

अटल u8 cea_num_vics(व्योम)
अणु
	वापस 193 + ARRAY_SIZE(edid_cea_modes_193);
पूर्ण

अटल u8 cea_next_vic(u8 vic)
अणु
	अगर (++vic == 1 + ARRAY_SIZE(edid_cea_modes_1))
		vic = 193;
	वापस vic;
पूर्ण

/*
 * Calculate the alternate घड़ी क्रम the CEA mode
 * (60Hz vs. 59.94Hz etc.)
 */
अटल अचिन्हित पूर्णांक
cea_mode_alternate_घड़ी(स्थिर काष्ठा drm_display_mode *cea_mode)
अणु
	अचिन्हित पूर्णांक घड़ी = cea_mode->घड़ी;

	अगर (drm_mode_vrefresh(cea_mode) % 6 != 0)
		वापस घड़ी;

	/*
	 * edid_cea_modes contains the 59.94Hz
	 * variant क्रम 240 and 480 line modes,
	 * and the 60Hz variant otherwise.
	 */
	अगर (cea_mode->vdisplay == 240 || cea_mode->vdisplay == 480)
		घड़ी = DIV_ROUND_CLOSEST(घड़ी * 1001, 1000);
	अन्यथा
		घड़ी = DIV_ROUND_CLOSEST(घड़ी * 1000, 1001);

	वापस घड़ी;
पूर्ण

अटल bool
cea_mode_alternate_timings(u8 vic, काष्ठा drm_display_mode *mode)
अणु
	/*
	 * For certain VICs the spec allows the vertical
	 * front porch to vary by one or two lines.
	 *
	 * cea_modes[] stores the variant with the लघुest
	 * vertical front porch. We can adjust the mode to
	 * get the other variants by simply increasing the
	 * vertical front porch length.
	 */
	BUILD_BUG_ON(cea_mode_क्रम_vic(8)->vtotal != 262 ||
		     cea_mode_क्रम_vic(9)->vtotal != 262 ||
		     cea_mode_क्रम_vic(12)->vtotal != 262 ||
		     cea_mode_क्रम_vic(13)->vtotal != 262 ||
		     cea_mode_क्रम_vic(23)->vtotal != 312 ||
		     cea_mode_क्रम_vic(24)->vtotal != 312 ||
		     cea_mode_क्रम_vic(27)->vtotal != 312 ||
		     cea_mode_क्रम_vic(28)->vtotal != 312);

	अगर (((vic == 8 || vic == 9 ||
	      vic == 12 || vic == 13) && mode->vtotal < 263) ||
	    ((vic == 23 || vic == 24 ||
	      vic == 27 || vic == 28) && mode->vtotal < 314)) अणु
		mode->vsync_start++;
		mode->vsync_end++;
		mode->vtotal++;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u8 drm_match_cea_mode_घड़ी_प्रकारolerance(स्थिर काष्ठा drm_display_mode *to_match,
					     अचिन्हित पूर्णांक घड़ी_प्रकारolerance)
अणु
	अचिन्हित पूर्णांक match_flags = DRM_MODE_MATCH_TIMINGS | DRM_MODE_MATCH_FLAGS;
	u8 vic;

	अगर (!to_match->घड़ी)
		वापस 0;

	अगर (to_match->picture_aspect_ratio)
		match_flags |= DRM_MODE_MATCH_ASPECT_RATIO;

	क्रम (vic = 1; vic < cea_num_vics(); vic = cea_next_vic(vic)) अणु
		काष्ठा drm_display_mode cea_mode = *cea_mode_क्रम_vic(vic);
		अचिन्हित पूर्णांक घड़ी1, घड़ी2;

		/* Check both 60Hz and 59.94Hz */
		घड़ी1 = cea_mode.घड़ी;
		घड़ी2 = cea_mode_alternate_घड़ी(&cea_mode);

		अगर (असल(to_match->घड़ी - घड़ी1) > घड़ी_प्रकारolerance &&
		    असल(to_match->घड़ी - घड़ी2) > घड़ी_प्रकारolerance)
			जारी;

		करो अणु
			अगर (drm_mode_match(to_match, &cea_mode, match_flags))
				वापस vic;
		पूर्ण जबतक (cea_mode_alternate_timings(vic, &cea_mode));
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_match_cea_mode - look क्रम a CEA mode matching given mode
 * @to_match: display mode
 *
 * Return: The CEA Video ID (VIC) of the mode or 0 अगर it isn't a CEA-861
 * mode.
 */
u8 drm_match_cea_mode(स्थिर काष्ठा drm_display_mode *to_match)
अणु
	अचिन्हित पूर्णांक match_flags = DRM_MODE_MATCH_TIMINGS | DRM_MODE_MATCH_FLAGS;
	u8 vic;

	अगर (!to_match->घड़ी)
		वापस 0;

	अगर (to_match->picture_aspect_ratio)
		match_flags |= DRM_MODE_MATCH_ASPECT_RATIO;

	क्रम (vic = 1; vic < cea_num_vics(); vic = cea_next_vic(vic)) अणु
		काष्ठा drm_display_mode cea_mode = *cea_mode_क्रम_vic(vic);
		अचिन्हित पूर्णांक घड़ी1, घड़ी2;

		/* Check both 60Hz and 59.94Hz */
		घड़ी1 = cea_mode.घड़ी;
		घड़ी2 = cea_mode_alternate_घड़ी(&cea_mode);

		अगर (KHZ2PICOS(to_match->घड़ी) != KHZ2PICOS(घड़ी1) &&
		    KHZ2PICOS(to_match->घड़ी) != KHZ2PICOS(घड़ी2))
			जारी;

		करो अणु
			अगर (drm_mode_match(to_match, &cea_mode, match_flags))
				वापस vic;
		पूर्ण जबतक (cea_mode_alternate_timings(vic, &cea_mode));
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_match_cea_mode);

अटल bool drm_valid_cea_vic(u8 vic)
अणु
	वापस cea_mode_क्रम_vic(vic) != शून्य;
पूर्ण

अटल क्रमागत hdmi_picture_aspect drm_get_cea_aspect_ratio(स्थिर u8 video_code)
अणु
	स्थिर काष्ठा drm_display_mode *mode = cea_mode_क्रम_vic(video_code);

	अगर (mode)
		वापस mode->picture_aspect_ratio;

	वापस HDMI_PICTURE_ASPECT_NONE;
पूर्ण

अटल क्रमागत hdmi_picture_aspect drm_get_hdmi_aspect_ratio(स्थिर u8 video_code)
अणु
	वापस edid_4k_modes[video_code].picture_aspect_ratio;
पूर्ण

/*
 * Calculate the alternate घड़ी क्रम HDMI modes (those from the HDMI venकरोr
 * specअगरic block).
 */
अटल अचिन्हित पूर्णांक
hdmi_mode_alternate_घड़ी(स्थिर काष्ठा drm_display_mode *hdmi_mode)
अणु
	वापस cea_mode_alternate_घड़ी(hdmi_mode);
पूर्ण

अटल u8 drm_match_hdmi_mode_घड़ी_प्रकारolerance(स्थिर काष्ठा drm_display_mode *to_match,
					      अचिन्हित पूर्णांक घड़ी_प्रकारolerance)
अणु
	अचिन्हित पूर्णांक match_flags = DRM_MODE_MATCH_TIMINGS | DRM_MODE_MATCH_FLAGS;
	u8 vic;

	अगर (!to_match->घड़ी)
		वापस 0;

	अगर (to_match->picture_aspect_ratio)
		match_flags |= DRM_MODE_MATCH_ASPECT_RATIO;

	क्रम (vic = 1; vic < ARRAY_SIZE(edid_4k_modes); vic++) अणु
		स्थिर काष्ठा drm_display_mode *hdmi_mode = &edid_4k_modes[vic];
		अचिन्हित पूर्णांक घड़ी1, घड़ी2;

		/* Make sure to also match alternate घड़ीs */
		घड़ी1 = hdmi_mode->घड़ी;
		घड़ी2 = hdmi_mode_alternate_घड़ी(hdmi_mode);

		अगर (असल(to_match->घड़ी - घड़ी1) > घड़ी_प्रकारolerance &&
		    असल(to_match->घड़ी - घड़ी2) > घड़ी_प्रकारolerance)
			जारी;

		अगर (drm_mode_match(to_match, hdmi_mode, match_flags))
			वापस vic;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * drm_match_hdmi_mode - look क्रम a HDMI mode matching given mode
 * @to_match: display mode
 *
 * An HDMI mode is one defined in the HDMI venकरोr specअगरic block.
 *
 * Returns the HDMI Video ID (VIC) of the mode or 0 अगर it isn't one.
 */
अटल u8 drm_match_hdmi_mode(स्थिर काष्ठा drm_display_mode *to_match)
अणु
	अचिन्हित पूर्णांक match_flags = DRM_MODE_MATCH_TIMINGS | DRM_MODE_MATCH_FLAGS;
	u8 vic;

	अगर (!to_match->घड़ी)
		वापस 0;

	अगर (to_match->picture_aspect_ratio)
		match_flags |= DRM_MODE_MATCH_ASPECT_RATIO;

	क्रम (vic = 1; vic < ARRAY_SIZE(edid_4k_modes); vic++) अणु
		स्थिर काष्ठा drm_display_mode *hdmi_mode = &edid_4k_modes[vic];
		अचिन्हित पूर्णांक घड़ी1, घड़ी2;

		/* Make sure to also match alternate घड़ीs */
		घड़ी1 = hdmi_mode->घड़ी;
		घड़ी2 = hdmi_mode_alternate_घड़ी(hdmi_mode);

		अगर ((KHZ2PICOS(to_match->घड़ी) == KHZ2PICOS(घड़ी1) ||
		     KHZ2PICOS(to_match->घड़ी) == KHZ2PICOS(घड़ी2)) &&
		    drm_mode_match(to_match, hdmi_mode, match_flags))
			वापस vic;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool drm_valid_hdmi_vic(u8 vic)
अणु
	वापस vic > 0 && vic < ARRAY_SIZE(edid_4k_modes);
पूर्ण

अटल पूर्णांक
add_alternate_cea_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode, *पंचांगp;
	LIST_HEAD(list);
	पूर्णांक modes = 0;

	/* Don't add CEA modes अगर the CEA extension block is missing */
	अगर (!drm_find_cea_extension(edid))
		वापस 0;

	/*
	 * Go through all probed modes and create a new mode
	 * with the alternate घड़ी क्रम certain CEA modes.
	 */
	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		स्थिर काष्ठा drm_display_mode *cea_mode = शून्य;
		काष्ठा drm_display_mode *newmode;
		u8 vic = drm_match_cea_mode(mode);
		अचिन्हित पूर्णांक घड़ी1, घड़ी2;

		अगर (drm_valid_cea_vic(vic)) अणु
			cea_mode = cea_mode_क्रम_vic(vic);
			घड़ी2 = cea_mode_alternate_घड़ी(cea_mode);
		पूर्ण अन्यथा अणु
			vic = drm_match_hdmi_mode(mode);
			अगर (drm_valid_hdmi_vic(vic)) अणु
				cea_mode = &edid_4k_modes[vic];
				घड़ी2 = hdmi_mode_alternate_घड़ी(cea_mode);
			पूर्ण
		पूर्ण

		अगर (!cea_mode)
			जारी;

		घड़ी1 = cea_mode->घड़ी;

		अगर (घड़ी1 == घड़ी2)
			जारी;

		अगर (mode->घड़ी != घड़ी1 && mode->घड़ी != घड़ी2)
			जारी;

		newmode = drm_mode_duplicate(dev, cea_mode);
		अगर (!newmode)
			जारी;

		/* Carry over the stereo flags */
		newmode->flags |= mode->flags & DRM_MODE_FLAG_3D_MASK;

		/*
		 * The current mode could be either variant. Make
		 * sure to pick the "other" घड़ी क्रम the new mode.
		 */
		अगर (mode->घड़ी != घड़ी1)
			newmode->घड़ी = घड़ी1;
		अन्यथा
			newmode->घड़ी = घड़ी2;

		list_add_tail(&newmode->head, &list);
	पूर्ण

	list_क्रम_each_entry_safe(mode, पंचांगp, &list, head) अणु
		list_del(&mode->head);
		drm_mode_probed_add(connector, mode);
		modes++;
	पूर्ण

	वापस modes;
पूर्ण

अटल u8 svd_to_vic(u8 svd)
अणु
	/* 0-6 bit vic, 7th bit native mode indicator */
	अगर ((svd >= 1 &&  svd <= 64) || (svd >= 129 && svd <= 192))
		वापस svd & 127;

	वापस svd;
पूर्ण

अटल काष्ठा drm_display_mode *
drm_display_mode_from_vic_index(काष्ठा drm_connector *connector,
				स्थिर u8 *video_db, u8 video_len,
				u8 video_index)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *newmode;
	u8 vic;

	अगर (video_db == शून्य || video_index >= video_len)
		वापस शून्य;

	/* CEA modes are numbered 1..127 */
	vic = svd_to_vic(video_db[video_index]);
	अगर (!drm_valid_cea_vic(vic))
		वापस शून्य;

	newmode = drm_mode_duplicate(dev, cea_mode_क्रम_vic(vic));
	अगर (!newmode)
		वापस शून्य;

	वापस newmode;
पूर्ण

/*
 * करो_y420vdb_modes - Parse YCBCR 420 only modes
 * @connector: connector corresponding to the HDMI sink
 * @svds: start of the data block of CEA YCBCR 420 VDB
 * @len: length of the CEA YCBCR 420 VDB
 *
 * Parse the CEA-861-F YCBCR 420 Video Data Block (Y420VDB)
 * which contains modes which can be supported in YCBCR 420
 * output क्रमmat only.
 */
अटल पूर्णांक करो_y420vdb_modes(काष्ठा drm_connector *connector,
			    स्थिर u8 *svds, u8 svds_len)
अणु
	पूर्णांक modes = 0, i;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा drm_hdmi_info *hdmi = &info->hdmi;

	क्रम (i = 0; i < svds_len; i++) अणु
		u8 vic = svd_to_vic(svds[i]);
		काष्ठा drm_display_mode *newmode;

		अगर (!drm_valid_cea_vic(vic))
			जारी;

		newmode = drm_mode_duplicate(dev, cea_mode_क्रम_vic(vic));
		अगर (!newmode)
			अवरोध;
		biपंचांगap_set(hdmi->y420_vdb_modes, vic, 1);
		drm_mode_probed_add(connector, newmode);
		modes++;
	पूर्ण

	अगर (modes > 0)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB420;
	वापस modes;
पूर्ण

/*
 * drm_add_cmdb_modes - Add a YCBCR 420 mode पूर्णांकo biपंचांगap
 * @connector: connector corresponding to the HDMI sink
 * @vic: CEA vic क्रम the video mode to be added in the map
 *
 * Makes an entry क्रम a videomode in the YCBCR 420 biपंचांगap
 */
अटल व्योम
drm_add_cmdb_modes(काष्ठा drm_connector *connector, u8 svd)
अणु
	u8 vic = svd_to_vic(svd);
	काष्ठा drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	अगर (!drm_valid_cea_vic(vic))
		वापस;

	biपंचांगap_set(hdmi->y420_cmdb_modes, vic, 1);
पूर्ण

/**
 * drm_display_mode_from_cea_vic() - वापस a mode क्रम CEA VIC
 * @dev: DRM device
 * @video_code: CEA VIC of the mode
 *
 * Creates a new mode matching the specअगरied CEA VIC.
 *
 * Returns: A new drm_display_mode on success or शून्य on failure
 */
काष्ठा drm_display_mode *
drm_display_mode_from_cea_vic(काष्ठा drm_device *dev,
			      u8 video_code)
अणु
	स्थिर काष्ठा drm_display_mode *cea_mode;
	काष्ठा drm_display_mode *newmode;

	cea_mode = cea_mode_क्रम_vic(video_code);
	अगर (!cea_mode)
		वापस शून्य;

	newmode = drm_mode_duplicate(dev, cea_mode);
	अगर (!newmode)
		वापस शून्य;

	वापस newmode;
पूर्ण
EXPORT_SYMBOL(drm_display_mode_from_cea_vic);

अटल पूर्णांक
करो_cea_modes(काष्ठा drm_connector *connector, स्थिर u8 *db, u8 len)
अणु
	पूर्णांक i, modes = 0;
	काष्ठा drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_display_mode_from_vic_index(connector, db, len, i);
		अगर (mode) अणु
			/*
			 * YCBCR420 capability block contains a biपंचांगap which
			 * gives the index of CEA modes from CEA VDB, which
			 * can support YCBCR 420 sampling output also (apart
			 * from RGB/YCBCR444 etc).
			 * For example, अगर the bit 0 in biपंचांगap is set,
			 * first mode in VDB can support YCBCR420 output too.
			 * Add YCBCR420 modes only अगर sink is HDMI 2.0 capable.
			 */
			अगर (i < 64 && hdmi->y420_cmdb_map & (1ULL << i))
				drm_add_cmdb_modes(connector, db[i]);

			drm_mode_probed_add(connector, mode);
			modes++;
		पूर्ण
	पूर्ण

	वापस modes;
पूर्ण

काष्ठा stereo_mandatory_mode अणु
	पूर्णांक width, height, vrefresh;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा stereo_mandatory_mode stereo_mandatory_modes[] = अणु
	अणु 1920, 1080, 24, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM पूर्ण,
	अणु 1920, 1080, 24, DRM_MODE_FLAG_3D_FRAME_PACKING पूर्ण,
	अणु 1920, 1080, 50,
	  DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF पूर्ण,
	अणु 1920, 1080, 60,
	  DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF पूर्ण,
	अणु 1280, 720,  50, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM पूर्ण,
	अणु 1280, 720,  50, DRM_MODE_FLAG_3D_FRAME_PACKING पूर्ण,
	अणु 1280, 720,  60, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM पूर्ण,
	अणु 1280, 720,  60, DRM_MODE_FLAG_3D_FRAME_PACKING पूर्ण
पूर्ण;

अटल bool
stereo_match_mandatory(स्थिर काष्ठा drm_display_mode *mode,
		       स्थिर काष्ठा stereo_mandatory_mode *stereo_mode)
अणु
	अचिन्हित पूर्णांक पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;

	वापस mode->hdisplay == stereo_mode->width &&
	       mode->vdisplay == stereo_mode->height &&
	       पूर्णांकerlaced == (stereo_mode->flags & DRM_MODE_FLAG_INTERLACE) &&
	       drm_mode_vrefresh(mode) == stereo_mode->vrefresh;
पूर्ण

अटल पूर्णांक add_hdmi_mandatory_stereo_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा list_head stereo_modes;
	पूर्णांक modes = 0, i;

	INIT_LIST_HEAD(&stereo_modes);

	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		क्रम (i = 0; i < ARRAY_SIZE(stereo_mandatory_modes); i++) अणु
			स्थिर काष्ठा stereo_mandatory_mode *mandatory;
			काष्ठा drm_display_mode *new_mode;

			अगर (!stereo_match_mandatory(mode,
						    &stereo_mandatory_modes[i]))
				जारी;

			mandatory = &stereo_mandatory_modes[i];
			new_mode = drm_mode_duplicate(dev, mode);
			अगर (!new_mode)
				जारी;

			new_mode->flags |= mandatory->flags;
			list_add_tail(&new_mode->head, &stereo_modes);
			modes++;
		पूर्ण
	पूर्ण

	list_splice_tail(&stereo_modes, &connector->probed_modes);

	वापस modes;
पूर्ण

अटल पूर्णांक add_hdmi_mode(काष्ठा drm_connector *connector, u8 vic)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *newmode;

	अगर (!drm_valid_hdmi_vic(vic)) अणु
		DRM_ERROR("Unknown HDMI VIC: %d\n", vic);
		वापस 0;
	पूर्ण

	newmode = drm_mode_duplicate(dev, &edid_4k_modes[vic]);
	अगर (!newmode)
		वापस 0;

	drm_mode_probed_add(connector, newmode);

	वापस 1;
पूर्ण

अटल पूर्णांक add_3d_काष्ठा_modes(काष्ठा drm_connector *connector, u16 काष्ठाure,
			       स्थिर u8 *video_db, u8 video_len, u8 video_index)
अणु
	काष्ठा drm_display_mode *newmode;
	पूर्णांक modes = 0;

	अगर (काष्ठाure & (1 << 0)) अणु
		newmode = drm_display_mode_from_vic_index(connector, video_db,
							  video_len,
							  video_index);
		अगर (newmode) अणु
			newmode->flags |= DRM_MODE_FLAG_3D_FRAME_PACKING;
			drm_mode_probed_add(connector, newmode);
			modes++;
		पूर्ण
	पूर्ण
	अगर (काष्ठाure & (1 << 6)) अणु
		newmode = drm_display_mode_from_vic_index(connector, video_db,
							  video_len,
							  video_index);
		अगर (newmode) अणु
			newmode->flags |= DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
			drm_mode_probed_add(connector, newmode);
			modes++;
		पूर्ण
	पूर्ण
	अगर (काष्ठाure & (1 << 8)) अणु
		newmode = drm_display_mode_from_vic_index(connector, video_db,
							  video_len,
							  video_index);
		अगर (newmode) अणु
			newmode->flags |= DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;
			drm_mode_probed_add(connector, newmode);
			modes++;
		पूर्ण
	पूर्ण

	वापस modes;
पूर्ण

/*
 * करो_hdmi_vsdb_modes - Parse the HDMI Venकरोr Specअगरic data block
 * @connector: connector corresponding to the HDMI sink
 * @db: start of the CEA venकरोr specअगरic block
 * @len: length of the CEA block payload, ie. one can access up to db[len]
 *
 * Parses the HDMI VSDB looking क्रम modes to add to @connector. This function
 * also adds the stereo 3d modes when applicable.
 */
अटल पूर्णांक
करो_hdmi_vsdb_modes(काष्ठा drm_connector *connector, स्थिर u8 *db, u8 len,
		   स्थिर u8 *video_db, u8 video_len)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;
	पूर्णांक modes = 0, offset = 0, i, multi_present = 0, multi_len;
	u8 vic_len, hdmi_3d_len = 0;
	u16 mask;
	u16 काष्ठाure_all;

	अगर (len < 8)
		जाओ out;

	/* no HDMI_Video_Present */
	अगर (!(db[8] & (1 << 5)))
		जाओ out;

	/* Latency_Fields_Present */
	अगर (db[8] & (1 << 7))
		offset += 2;

	/* I_Latency_Fields_Present */
	अगर (db[8] & (1 << 6))
		offset += 2;

	/* the declared length is not दीर्घ enough क्रम the 2 first bytes
	 * of additional video क्रमmat capabilities */
	अगर (len < (8 + offset + 2))
		जाओ out;

	/* 3D_Present */
	offset++;
	अगर (db[8 + offset] & (1 << 7)) अणु
		modes += add_hdmi_mandatory_stereo_modes(connector);

		/* 3D_Multi_present */
		multi_present = (db[8 + offset] & 0x60) >> 5;
	पूर्ण

	offset++;
	vic_len = db[8 + offset] >> 5;
	hdmi_3d_len = db[8 + offset] & 0x1f;

	क्रम (i = 0; i < vic_len && len >= (9 + offset + i); i++) अणु
		u8 vic;

		vic = db[9 + offset + i];
		modes += add_hdmi_mode(connector, vic);
	पूर्ण
	offset += 1 + vic_len;

	अगर (multi_present == 1)
		multi_len = 2;
	अन्यथा अगर (multi_present == 2)
		multi_len = 4;
	अन्यथा
		multi_len = 0;

	अगर (len < (8 + offset + hdmi_3d_len - 1))
		जाओ out;

	अगर (hdmi_3d_len < multi_len)
		जाओ out;

	अगर (multi_present == 1 || multi_present == 2) अणु
		/* 3D_Structure_ALL */
		काष्ठाure_all = (db[8 + offset] << 8) | db[9 + offset];

		/* check अगर 3D_MASK is present */
		अगर (multi_present == 2)
			mask = (db[10 + offset] << 8) | db[11 + offset];
		अन्यथा
			mask = 0xffff;

		क्रम (i = 0; i < 16; i++) अणु
			अगर (mask & (1 << i))
				modes += add_3d_काष्ठा_modes(connector,
						काष्ठाure_all,
						video_db,
						video_len, i);
		पूर्ण
	पूर्ण

	offset += multi_len;

	क्रम (i = 0; i < (hdmi_3d_len - multi_len); i++) अणु
		पूर्णांक vic_index;
		काष्ठा drm_display_mode *newmode = शून्य;
		अचिन्हित पूर्णांक newflag = 0;
		bool detail_present;

		detail_present = ((db[8 + offset + i] & 0x0f) > 7);

		अगर (detail_present && (i + 1 == hdmi_3d_len - multi_len))
			अवरोध;

		/* 2D_VIC_order_X */
		vic_index = db[8 + offset + i] >> 4;

		/* 3D_Structure_X */
		चयन (db[8 + offset + i] & 0x0f) अणु
		हाल 0:
			newflag = DRM_MODE_FLAG_3D_FRAME_PACKING;
			अवरोध;
		हाल 6:
			newflag = DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
			अवरोध;
		हाल 8:
			/* 3D_Detail_X */
			अगर ((db[9 + offset + i] >> 4) == 1)
				newflag = DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;
			अवरोध;
		पूर्ण

		अगर (newflag != 0) अणु
			newmode = drm_display_mode_from_vic_index(connector,
								  video_db,
								  video_len,
								  vic_index);

			अगर (newmode) अणु
				newmode->flags |= newflag;
				drm_mode_probed_add(connector, newmode);
				modes++;
			पूर्ण
		पूर्ण

		अगर (detail_present)
			i++;
	पूर्ण

out:
	अगर (modes > 0)
		info->has_hdmi_infoframe = true;
	वापस modes;
पूर्ण

अटल पूर्णांक
cea_db_payload_len(स्थिर u8 *db)
अणु
	वापस db[0] & 0x1f;
पूर्ण

अटल पूर्णांक
cea_db_extended_tag(स्थिर u8 *db)
अणु
	वापस db[1];
पूर्ण

अटल पूर्णांक
cea_db_tag(स्थिर u8 *db)
अणु
	वापस db[0] >> 5;
पूर्ण

अटल पूर्णांक
cea_revision(स्थिर u8 *cea)
अणु
	/*
	 * FIXME is this correct क्रम the DispID variant?
	 * The DispID spec करोesn't really specअगरy whether
	 * this is the revision of the CEA extension or
	 * the DispID CEA data block. And the only value
	 * given as an example is 0.
	 */
	वापस cea[1];
पूर्ण

अटल पूर्णांक
cea_db_offsets(स्थिर u8 *cea, पूर्णांक *start, पूर्णांक *end)
अणु
	/* DisplayID CTA extension blocks and top-level CEA EDID
	 * block header definitions dअगरfer in the following bytes:
	 *   1) Byte 2 of the header specअगरies length dअगरferently,
	 *   2) Byte 3 is only present in the CEA top level block.
	 *
	 * The dअगरferent definitions क्रम byte 2 follow.
	 *
	 * DisplayID CTA extension block defines byte 2 as:
	 *   Number of payload bytes
	 *
	 * CEA EDID block defines byte 2 as:
	 *   Byte number (decimal) within this block where the 18-byte
	 *   DTDs begin. If no non-DTD data is present in this extension
	 *   block, the value should be set to 04h (the byte after next).
	 *   If set to 00h, there are no DTDs present in this block and
	 *   no non-DTD data.
	 */
	अगर (cea[0] == DATA_BLOCK_CTA) अणु
		/*
		 * क्रम_each_displayid_db() has alपढ़ोy verअगरied
		 * that these stay within expected bounds.
		 */
		*start = 3;
		*end = *start + cea[2];
	पूर्ण अन्यथा अगर (cea[0] == CEA_EXT) अणु
		/* Data block offset in CEA extension block */
		*start = 4;
		*end = cea[2];
		अगर (*end == 0)
			*end = 127;
		अगर (*end < 4 || *end > 127)
			वापस -दुस्फल;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool cea_db_is_hdmi_vsdb(स्थिर u8 *db)
अणु
	पूर्णांक hdmi_id;

	अगर (cea_db_tag(db) != VENDOR_BLOCK)
		वापस false;

	अगर (cea_db_payload_len(db) < 5)
		वापस false;

	hdmi_id = db[1] | (db[2] << 8) | (db[3] << 16);

	वापस hdmi_id == HDMI_IEEE_OUI;
पूर्ण

अटल bool cea_db_is_hdmi_क्रमum_vsdb(स्थिर u8 *db)
अणु
	अचिन्हित पूर्णांक oui;

	अगर (cea_db_tag(db) != VENDOR_BLOCK)
		वापस false;

	अगर (cea_db_payload_len(db) < 7)
		वापस false;

	oui = db[3] << 16 | db[2] << 8 | db[1];

	वापस oui == HDMI_FORUM_IEEE_OUI;
पूर्ण

अटल bool cea_db_is_vcdb(स्थिर u8 *db)
अणु
	अगर (cea_db_tag(db) != USE_EXTENDED_TAG)
		वापस false;

	अगर (cea_db_payload_len(db) != 2)
		वापस false;

	अगर (cea_db_extended_tag(db) != EXT_VIDEO_CAPABILITY_BLOCK)
		वापस false;

	वापस true;
पूर्ण

अटल bool cea_db_is_y420cmdb(स्थिर u8 *db)
अणु
	अगर (cea_db_tag(db) != USE_EXTENDED_TAG)
		वापस false;

	अगर (!cea_db_payload_len(db))
		वापस false;

	अगर (cea_db_extended_tag(db) != EXT_VIDEO_CAP_BLOCK_Y420CMDB)
		वापस false;

	वापस true;
पूर्ण

अटल bool cea_db_is_y420vdb(स्थिर u8 *db)
अणु
	अगर (cea_db_tag(db) != USE_EXTENDED_TAG)
		वापस false;

	अगर (!cea_db_payload_len(db))
		वापस false;

	अगर (cea_db_extended_tag(db) != EXT_VIDEO_DATA_BLOCK_420)
		वापस false;

	वापस true;
पूर्ण

#घोषणा क्रम_each_cea_db(cea, i, start, end) \
	क्रम ((i) = (start); (i) < (end) && (i) + cea_db_payload_len(&(cea)[(i)]) < (end); (i) += cea_db_payload_len(&(cea)[(i)]) + 1)

अटल व्योम drm_parse_y420cmdb_biपंचांगap(काष्ठा drm_connector *connector,
				      स्थिर u8 *db)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा drm_hdmi_info *hdmi = &info->hdmi;
	u8 map_len = cea_db_payload_len(db) - 1;
	u8 count;
	u64 map = 0;

	अगर (map_len == 0) अणु
		/* All CEA modes support ycbcr420 sampling also.*/
		hdmi->y420_cmdb_map = U64_MAX;
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB420;
		वापस;
	पूर्ण

	/*
	 * This map indicates which of the existing CEA block modes
	 * from VDB can support YCBCR420 output too. So अगर bit=0 is
	 * set, first mode from VDB can support YCBCR420 output too.
	 * We will parse and keep this map, beक्रमe parsing VDB itself
	 * to aव्योम going through the same block again and again.
	 *
	 * Spec is not clear about max possible size of this block.
	 * Clamping max biपंचांगap block size at 8 bytes. Every byte can
	 * address 8 CEA modes, in this way this map can address
	 * 8*8 = first 64 SVDs.
	 */
	अगर (WARN_ON_ONCE(map_len > 8))
		map_len = 8;

	क्रम (count = 0; count < map_len; count++)
		map |= (u64)db[2 + count] << (8 * count);

	अगर (map)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB420;

	hdmi->y420_cmdb_map = map;
पूर्ण

अटल पूर्णांक
add_cea_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	स्थिर u8 *cea = drm_find_cea_extension(edid);
	स्थिर u8 *db, *hdmi = शून्य, *video = शून्य;
	u8 dbl, hdmi_len, video_len = 0;
	पूर्णांक modes = 0;

	अगर (cea && cea_revision(cea) >= 3) अणु
		पूर्णांक i, start, end;

		अगर (cea_db_offsets(cea, &start, &end))
			वापस 0;

		क्रम_each_cea_db(cea, i, start, end) अणु
			db = &cea[i];
			dbl = cea_db_payload_len(db);

			अगर (cea_db_tag(db) == VIDEO_BLOCK) अणु
				video = db + 1;
				video_len = dbl;
				modes += करो_cea_modes(connector, video, dbl);
			पूर्ण अन्यथा अगर (cea_db_is_hdmi_vsdb(db)) अणु
				hdmi = db;
				hdmi_len = dbl;
			पूर्ण अन्यथा अगर (cea_db_is_y420vdb(db)) अणु
				स्थिर u8 *vdb420 = &db[2];

				/* Add 4:2:0(only) modes present in EDID */
				modes += करो_y420vdb_modes(connector,
							  vdb420,
							  dbl - 1);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We parse the HDMI VSDB after having added the cea modes as we will
	 * be patching their flags when the sink supports stereo 3D.
	 */
	अगर (hdmi)
		modes += करो_hdmi_vsdb_modes(connector, hdmi, hdmi_len, video,
					    video_len);

	वापस modes;
पूर्ण

अटल व्योम fixup_detailed_cea_mode_घड़ी(काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा drm_display_mode *cea_mode;
	पूर्णांक घड़ी1, घड़ी2, घड़ी;
	u8 vic;
	स्थिर अक्षर *type;

	/*
	 * allow 5kHz घड़ी dअगरference either way to account क्रम
	 * the 10kHz घड़ी resolution limit of detailed timings.
	 */
	vic = drm_match_cea_mode_घड़ी_प्रकारolerance(mode, 5);
	अगर (drm_valid_cea_vic(vic)) अणु
		type = "CEA";
		cea_mode = cea_mode_क्रम_vic(vic);
		घड़ी1 = cea_mode->घड़ी;
		घड़ी2 = cea_mode_alternate_घड़ी(cea_mode);
	पूर्ण अन्यथा अणु
		vic = drm_match_hdmi_mode_घड़ी_प्रकारolerance(mode, 5);
		अगर (drm_valid_hdmi_vic(vic)) अणु
			type = "HDMI";
			cea_mode = &edid_4k_modes[vic];
			घड़ी1 = cea_mode->घड़ी;
			घड़ी2 = hdmi_mode_alternate_घड़ी(cea_mode);
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण

	/* pick whichever is बंदst */
	अगर (असल(mode->घड़ी - घड़ी1) < असल(mode->घड़ी - घड़ी2))
		घड़ी = घड़ी1;
	अन्यथा
		घड़ी = घड़ी2;

	अगर (mode->घड़ी == घड़ी)
		वापस;

	DRM_DEBUG("detailed mode matches %s VIC %d, adjusting clock %d -> %d\n",
		  type, vic, mode->घड़ी, घड़ी);
	mode->घड़ी = घड़ी;
पूर्ण

अटल bool cea_db_is_hdmi_hdr_metadata_block(स्थिर u8 *db)
अणु
	अगर (cea_db_tag(db) != USE_EXTENDED_TAG)
		वापस false;

	अगर (db[1] != HDR_STATIC_METADATA_BLOCK)
		वापस false;

	अगर (cea_db_payload_len(db) < 3)
		वापस false;

	वापस true;
पूर्ण

अटल uपूर्णांक8_t eotf_supported(स्थिर u8 *edid_ext)
अणु
	वापस edid_ext[2] &
		(BIT(HDMI_EOTF_TRADITIONAL_GAMMA_SDR) |
		 BIT(HDMI_EOTF_TRADITIONAL_GAMMA_HDR) |
		 BIT(HDMI_EOTF_SMPTE_ST2084) |
		 BIT(HDMI_EOTF_BT_2100_HLG));
पूर्ण

अटल uपूर्णांक8_t hdr_metadata_type(स्थिर u8 *edid_ext)
अणु
	वापस edid_ext[3] &
		BIT(HDMI_STATIC_METADATA_TYPE1);
पूर्ण

अटल व्योम
drm_parse_hdr_metadata_block(काष्ठा drm_connector *connector, स्थिर u8 *db)
अणु
	u16 len;

	len = cea_db_payload_len(db);

	connector->hdr_sink_metadata.hdmi_type1.eotf =
						eotf_supported(db);
	connector->hdr_sink_metadata.hdmi_type1.metadata_type =
						hdr_metadata_type(db);

	अगर (len >= 4)
		connector->hdr_sink_metadata.hdmi_type1.max_cll = db[4];
	अगर (len >= 5)
		connector->hdr_sink_metadata.hdmi_type1.max_fall = db[5];
	अगर (len >= 6)
		connector->hdr_sink_metadata.hdmi_type1.min_cll = db[6];
पूर्ण

अटल व्योम
drm_parse_hdmi_vsdb_audio(काष्ठा drm_connector *connector, स्थिर u8 *db)
अणु
	u8 len = cea_db_payload_len(db);

	अगर (len >= 6 && (db[6] & (1 << 7)))
		connector->eld[DRM_ELD_SAD_COUNT_CONN_TYPE] |= DRM_ELD_SUPPORTS_AI;
	अगर (len >= 8) अणु
		connector->latency_present[0] = db[8] >> 7;
		connector->latency_present[1] = (db[8] >> 6) & 1;
	पूर्ण
	अगर (len >= 9)
		connector->video_latency[0] = db[9];
	अगर (len >= 10)
		connector->audio_latency[0] = db[10];
	अगर (len >= 11)
		connector->video_latency[1] = db[11];
	अगर (len >= 12)
		connector->audio_latency[1] = db[12];

	DRM_DEBUG_KMS("HDMI: latency present %d %d, "
		      "video latency %d %d, "
		      "audio latency %d %d\n",
		      connector->latency_present[0],
		      connector->latency_present[1],
		      connector->video_latency[0],
		      connector->video_latency[1],
		      connector->audio_latency[0],
		      connector->audio_latency[1]);
पूर्ण

अटल व्योम
monitor_name(काष्ठा detailed_timing *t, व्योम *data)
अणु
	अगर (!is_display_descriptor((स्थिर u8 *)t, EDID_DETAIL_MONITOR_NAME))
		वापस;

	*(u8 **)data = t->data.other_data.data.str.str;
पूर्ण

अटल पूर्णांक get_monitor_name(काष्ठा edid *edid, अक्षर name[13])
अणु
	अक्षर *edid_name = शून्य;
	पूर्णांक mnl;

	अगर (!edid || !name)
		वापस 0;

	drm_क्रम_each_detailed_block((u8 *)edid, monitor_name, &edid_name);
	क्रम (mnl = 0; edid_name && mnl < 13; mnl++) अणु
		अगर (edid_name[mnl] == 0x0a)
			अवरोध;

		name[mnl] = edid_name[mnl];
	पूर्ण

	वापस mnl;
पूर्ण

/**
 * drm_edid_get_monitor_name - fetch the monitor name from the edid
 * @edid: monitor EDID inक्रमmation
 * @name: poपूर्णांकer to a अक्षरacter array to hold the name of the monitor
 * @bufsize: The size of the name buffer (should be at least 14 अक्षरs.)
 *
 */
व्योम drm_edid_get_monitor_name(काष्ठा edid *edid, अक्षर *name, पूर्णांक bufsize)
अणु
	पूर्णांक name_length;
	अक्षर buf[13];

	अगर (bufsize <= 0)
		वापस;

	name_length = min(get_monitor_name(edid, buf), bufsize - 1);
	स_नकल(name, buf, name_length);
	name[name_length] = '\0';
पूर्ण
EXPORT_SYMBOL(drm_edid_get_monitor_name);

अटल व्योम clear_eld(काष्ठा drm_connector *connector)
अणु
	स_रखो(connector->eld, 0, माप(connector->eld));

	connector->latency_present[0] = false;
	connector->latency_present[1] = false;
	connector->video_latency[0] = 0;
	connector->audio_latency[0] = 0;
	connector->video_latency[1] = 0;
	connector->audio_latency[1] = 0;
पूर्ण

/*
 * drm_edid_to_eld - build ELD from EDID
 * @connector: connector corresponding to the HDMI/DP sink
 * @edid: EDID to parse
 *
 * Fill the ELD (EDID-Like Data) buffer क्रम passing to the audio driver. The
 * HDCP and Port_ID ELD fields are left क्रम the graphics driver to fill in.
 */
अटल व्योम drm_edid_to_eld(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	uपूर्णांक8_t *eld = connector->eld;
	स्थिर u8 *cea;
	स्थिर u8 *db;
	पूर्णांक total_sad_count = 0;
	पूर्णांक mnl;
	पूर्णांक dbl;

	clear_eld(connector);

	अगर (!edid)
		वापस;

	cea = drm_find_cea_extension(edid);
	अगर (!cea) अणु
		DRM_DEBUG_KMS("ELD: no CEA Extension found\n");
		वापस;
	पूर्ण

	mnl = get_monitor_name(edid, &eld[DRM_ELD_MONITOR_NAME_STRING]);
	DRM_DEBUG_KMS("ELD monitor %s\n", &eld[DRM_ELD_MONITOR_NAME_STRING]);

	eld[DRM_ELD_CEA_EDID_VER_MNL] = cea[1] << DRM_ELD_CEA_EDID_VER_SHIFT;
	eld[DRM_ELD_CEA_EDID_VER_MNL] |= mnl;

	eld[DRM_ELD_VER] = DRM_ELD_VER_CEA861D;

	eld[DRM_ELD_MANUFACTURER_NAME0] = edid->mfg_id[0];
	eld[DRM_ELD_MANUFACTURER_NAME1] = edid->mfg_id[1];
	eld[DRM_ELD_PRODUCT_CODE0] = edid->prod_code[0];
	eld[DRM_ELD_PRODUCT_CODE1] = edid->prod_code[1];

	अगर (cea_revision(cea) >= 3) अणु
		पूर्णांक i, start, end;
		पूर्णांक sad_count;

		अगर (cea_db_offsets(cea, &start, &end)) अणु
			start = 0;
			end = 0;
		पूर्ण

		क्रम_each_cea_db(cea, i, start, end) अणु
			db = &cea[i];
			dbl = cea_db_payload_len(db);

			चयन (cea_db_tag(db)) अणु
			हाल AUDIO_BLOCK:
				/* Audio Data Block, contains SADs */
				sad_count = min(dbl / 3, 15 - total_sad_count);
				अगर (sad_count >= 1)
					स_नकल(&eld[DRM_ELD_CEA_SAD(mnl, total_sad_count)],
					       &db[1], sad_count * 3);
				total_sad_count += sad_count;
				अवरोध;
			हाल SPEAKER_BLOCK:
				/* Speaker Allocation Data Block */
				अगर (dbl >= 1)
					eld[DRM_ELD_SPEAKER] = db[1];
				अवरोध;
			हाल VENDOR_BLOCK:
				/* HDMI Venकरोr-Specअगरic Data Block */
				अगर (cea_db_is_hdmi_vsdb(db))
					drm_parse_hdmi_vsdb_audio(connector, db);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	eld[DRM_ELD_SAD_COUNT_CONN_TYPE] |= total_sad_count << DRM_ELD_SAD_COUNT_SHIFT;

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->connector_type == DRM_MODE_CONNECTOR_eDP)
		eld[DRM_ELD_SAD_COUNT_CONN_TYPE] |= DRM_ELD_CONN_TYPE_DP;
	अन्यथा
		eld[DRM_ELD_SAD_COUNT_CONN_TYPE] |= DRM_ELD_CONN_TYPE_HDMI;

	eld[DRM_ELD_BASELINE_ELD_LEN] =
		DIV_ROUND_UP(drm_eld_calc_baseline_block_size(eld), 4);

	DRM_DEBUG_KMS("ELD size %d, SAD count %d\n",
		      drm_eld_size(eld), total_sad_count);
पूर्ण

/**
 * drm_edid_to_sad - extracts SADs from EDID
 * @edid: EDID to parse
 * @sads: poपूर्णांकer that will be set to the extracted SADs
 *
 * Looks क्रम CEA EDID block and extracts SADs (Short Audio Descriptors) from it.
 *
 * Note: The वापसed poपूर्णांकer needs to be मुक्तd using kमुक्त().
 *
 * Return: The number of found SADs or negative number on error.
 */
पूर्णांक drm_edid_to_sad(काष्ठा edid *edid, काष्ठा cea_sad **sads)
अणु
	पूर्णांक count = 0;
	पूर्णांक i, start, end, dbl;
	स्थिर u8 *cea;

	cea = drm_find_cea_extension(edid);
	अगर (!cea) अणु
		DRM_DEBUG_KMS("SAD: no CEA Extension found\n");
		वापस 0;
	पूर्ण

	अगर (cea_revision(cea) < 3) अणु
		DRM_DEBUG_KMS("SAD: wrong CEA revision\n");
		वापस 0;
	पूर्ण

	अगर (cea_db_offsets(cea, &start, &end)) अणु
		DRM_DEBUG_KMS("SAD: invalid data block offsets\n");
		वापस -EPROTO;
	पूर्ण

	क्रम_each_cea_db(cea, i, start, end) अणु
		स्थिर u8 *db = &cea[i];

		अगर (cea_db_tag(db) == AUDIO_BLOCK) अणु
			पूर्णांक j;

			dbl = cea_db_payload_len(db);

			count = dbl / 3; /* SAD is 3B */
			*sads = kसुस्मृति(count, माप(**sads), GFP_KERNEL);
			अगर (!*sads)
				वापस -ENOMEM;
			क्रम (j = 0; j < count; j++) अणु
				स्थिर u8 *sad = &db[1 + j * 3];

				(*sads)[j].क्रमmat = (sad[0] & 0x78) >> 3;
				(*sads)[j].channels = sad[0] & 0x7;
				(*sads)[j].freq = sad[1] & 0x7F;
				(*sads)[j].byte2 = sad[2];
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(drm_edid_to_sad);

/**
 * drm_edid_to_speaker_allocation - extracts Speaker Allocation Data Blocks from EDID
 * @edid: EDID to parse
 * @sadb: poपूर्णांकer to the speaker block
 *
 * Looks क्रम CEA EDID block and extracts the Speaker Allocation Data Block from it.
 *
 * Note: The वापसed poपूर्णांकer needs to be मुक्तd using kमुक्त().
 *
 * Return: The number of found Speaker Allocation Blocks or negative number on
 * error.
 */
पूर्णांक drm_edid_to_speaker_allocation(काष्ठा edid *edid, u8 **sadb)
अणु
	पूर्णांक count = 0;
	पूर्णांक i, start, end, dbl;
	स्थिर u8 *cea;

	cea = drm_find_cea_extension(edid);
	अगर (!cea) अणु
		DRM_DEBUG_KMS("SAD: no CEA Extension found\n");
		वापस 0;
	पूर्ण

	अगर (cea_revision(cea) < 3) अणु
		DRM_DEBUG_KMS("SAD: wrong CEA revision\n");
		वापस 0;
	पूर्ण

	अगर (cea_db_offsets(cea, &start, &end)) अणु
		DRM_DEBUG_KMS("SAD: invalid data block offsets\n");
		वापस -EPROTO;
	पूर्ण

	क्रम_each_cea_db(cea, i, start, end) अणु
		स्थिर u8 *db = &cea[i];

		अगर (cea_db_tag(db) == SPEAKER_BLOCK) अणु
			dbl = cea_db_payload_len(db);

			/* Speaker Allocation Data Block */
			अगर (dbl == 3) अणु
				*sadb = kmemdup(&db[1], dbl, GFP_KERNEL);
				अगर (!*sadb)
					वापस -ENOMEM;
				count = dbl;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(drm_edid_to_speaker_allocation);

/**
 * drm_av_sync_delay - compute the HDMI/DP sink audio-video sync delay
 * @connector: connector associated with the HDMI/DP sink
 * @mode: the display mode
 *
 * Return: The HDMI/DP sink's audio-video sync delay in milliseconds or 0 अगर
 * the sink करोesn't support audio or video.
 */
पूर्णांक drm_av_sync_delay(काष्ठा drm_connector *connector,
		      स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);
	पूर्णांक a, v;

	अगर (!connector->latency_present[0])
		वापस 0;
	अगर (!connector->latency_present[1])
		i = 0;

	a = connector->audio_latency[i];
	v = connector->video_latency[i];

	/*
	 * HDMI/DP sink करोesn't support audio or video?
	 */
	अगर (a == 255 || v == 255)
		वापस 0;

	/*
	 * Convert raw EDID values to millisecond.
	 * Treat unknown latency as 0ms.
	 */
	अगर (a)
		a = min(2 * (a - 1), 500);
	अगर (v)
		v = min(2 * (v - 1), 500);

	वापस max(v - a, 0);
पूर्ण
EXPORT_SYMBOL(drm_av_sync_delay);

/**
 * drm_detect_hdmi_monitor - detect whether monitor is HDMI
 * @edid: monitor EDID inक्रमmation
 *
 * Parse the CEA extension according to CEA-861-B.
 *
 * Drivers that have added the modes parsed from EDID to drm_display_info
 * should use &drm_display_info.is_hdmi instead of calling this function.
 *
 * Return: True अगर the monitor is HDMI, false अगर not or unknown.
 */
bool drm_detect_hdmi_monitor(काष्ठा edid *edid)
अणु
	स्थिर u8 *edid_ext;
	पूर्णांक i;
	पूर्णांक start_offset, end_offset;

	edid_ext = drm_find_cea_extension(edid);
	अगर (!edid_ext)
		वापस false;

	अगर (cea_db_offsets(edid_ext, &start_offset, &end_offset))
		वापस false;

	/*
	 * Because HDMI identअगरier is in Venकरोr Specअगरic Block,
	 * search it from all data blocks of CEA extension.
	 */
	क्रम_each_cea_db(edid_ext, i, start_offset, end_offset) अणु
		अगर (cea_db_is_hdmi_vsdb(&edid_ext[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_detect_hdmi_monitor);

/**
 * drm_detect_monitor_audio - check monitor audio capability
 * @edid: EDID block to scan
 *
 * Monitor should have CEA extension block.
 * If monitor has 'basic audio', but no CEA audio blocks, it's 'basic
 * audio' only. If there is any audio extension block and supported
 * audio क्रमmat, assume at least 'basic audio' support, even if 'basic
 * audio' is not defined in EDID.
 *
 * Return: True अगर the monitor supports audio, false otherwise.
 */
bool drm_detect_monitor_audio(काष्ठा edid *edid)
अणु
	स्थिर u8 *edid_ext;
	पूर्णांक i, j;
	bool has_audio = false;
	पूर्णांक start_offset, end_offset;

	edid_ext = drm_find_cea_extension(edid);
	अगर (!edid_ext)
		जाओ end;

	has_audio = ((edid_ext[3] & EDID_BASIC_AUDIO) != 0);

	अगर (has_audio) अणु
		DRM_DEBUG_KMS("Monitor has basic audio support\n");
		जाओ end;
	पूर्ण

	अगर (cea_db_offsets(edid_ext, &start_offset, &end_offset))
		जाओ end;

	क्रम_each_cea_db(edid_ext, i, start_offset, end_offset) अणु
		अगर (cea_db_tag(&edid_ext[i]) == AUDIO_BLOCK) अणु
			has_audio = true;
			क्रम (j = 1; j < cea_db_payload_len(&edid_ext[i]) + 1; j += 3)
				DRM_DEBUG_KMS("CEA audio format %d\n",
					      (edid_ext[i + j] >> 3) & 0xf);
			जाओ end;
		पूर्ण
	पूर्ण
end:
	वापस has_audio;
पूर्ण
EXPORT_SYMBOL(drm_detect_monitor_audio);


/**
 * drm_शेष_rgb_quant_range - शेष RGB quantization range
 * @mode: display mode
 *
 * Determine the शेष RGB quantization range क्रम the mode,
 * as specअगरied in CEA-861.
 *
 * Return: The शेष RGB quantization range क्रम the mode
 */
क्रमागत hdmi_quantization_range
drm_शेष_rgb_quant_range(स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* All CEA modes other than VIC 1 use limited quantization range. */
	वापस drm_match_cea_mode(mode) > 1 ?
		HDMI_QUANTIZATION_RANGE_LIMITED :
		HDMI_QUANTIZATION_RANGE_FULL;
पूर्ण
EXPORT_SYMBOL(drm_शेष_rgb_quant_range);

अटल व्योम drm_parse_vcdb(काष्ठा drm_connector *connector, स्थिर u8 *db)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;

	DRM_DEBUG_KMS("CEA VCDB 0x%02x\n", db[2]);

	अगर (db[2] & EDID_CEA_VCDB_QS)
		info->rgb_quant_range_selectable = true;
पूर्ण

अटल
व्योम drm_get_max_frl_rate(पूर्णांक max_frl_rate, u8 *max_lanes, u8 *max_rate_per_lane)
अणु
	चयन (max_frl_rate) अणु
	हाल 1:
		*max_lanes = 3;
		*max_rate_per_lane = 3;
		अवरोध;
	हाल 2:
		*max_lanes = 3;
		*max_rate_per_lane = 6;
		अवरोध;
	हाल 3:
		*max_lanes = 4;
		*max_rate_per_lane = 6;
		अवरोध;
	हाल 4:
		*max_lanes = 4;
		*max_rate_per_lane = 8;
		अवरोध;
	हाल 5:
		*max_lanes = 4;
		*max_rate_per_lane = 10;
		अवरोध;
	हाल 6:
		*max_lanes = 4;
		*max_rate_per_lane = 12;
		अवरोध;
	हाल 0:
	शेष:
		*max_lanes = 0;
		*max_rate_per_lane = 0;
	पूर्ण
पूर्ण

अटल व्योम drm_parse_ycbcr420_deep_color_info(काष्ठा drm_connector *connector,
					       स्थिर u8 *db)
अणु
	u8 dc_mask;
	काष्ठा drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	dc_mask = db[7] & DRM_EDID_YCBCR420_DC_MASK;
	hdmi->y420_dc_modes = dc_mask;
पूर्ण

अटल व्योम drm_parse_hdmi_क्रमum_vsdb(काष्ठा drm_connector *connector,
				 स्थिर u8 *hf_vsdb)
अणु
	काष्ठा drm_display_info *display = &connector->display_info;
	काष्ठा drm_hdmi_info *hdmi = &display->hdmi;

	display->has_hdmi_infoframe = true;

	अगर (hf_vsdb[6] & 0x80) अणु
		hdmi->scdc.supported = true;
		अगर (hf_vsdb[6] & 0x40)
			hdmi->scdc.पढ़ो_request = true;
	पूर्ण

	/*
	 * All HDMI 2.0 monitors must support scrambling at rates > 340 MHz.
	 * And as per the spec, three factors confirm this:
	 * * Availability of a HF-VSDB block in EDID (check)
	 * * Non zero Max_TMDS_Char_Rate filed in HF-VSDB (let's check)
	 * * SCDC support available (let's check)
	 * Lets check it out.
	 */

	अगर (hf_vsdb[5]) अणु
		/* max घड़ी is 5000 KHz बार block value */
		u32 max_पंचांगds_घड़ी = hf_vsdb[5] * 5000;
		काष्ठा drm_scdc *scdc = &hdmi->scdc;

		अगर (max_पंचांगds_घड़ी > 340000) अणु
			display->max_पंचांगds_घड़ी = max_पंचांगds_घड़ी;
			DRM_DEBUG_KMS("HF-VSDB: max TMDS clock %d kHz\n",
				display->max_पंचांगds_घड़ी);
		पूर्ण

		अगर (scdc->supported) अणु
			scdc->scrambling.supported = true;

			/* Few sinks support scrambling क्रम घड़ीs < 340M */
			अगर ((hf_vsdb[6] & 0x8))
				scdc->scrambling.low_rates = true;
		पूर्ण
	पूर्ण

	अगर (hf_vsdb[7]) अणु
		u8 max_frl_rate;
		u8 dsc_max_frl_rate;
		u8 dsc_max_slices;
		काष्ठा drm_hdmi_dsc_cap *hdmi_dsc = &hdmi->dsc_cap;

		DRM_DEBUG_KMS("hdmi_21 sink detected. parsing edid\n");
		max_frl_rate = (hf_vsdb[7] & DRM_EDID_MAX_FRL_RATE_MASK) >> 4;
		drm_get_max_frl_rate(max_frl_rate, &hdmi->max_lanes,
				     &hdmi->max_frl_rate_per_lane);
		hdmi_dsc->v_1p2 = hf_vsdb[11] & DRM_EDID_DSC_1P2;

		अगर (hdmi_dsc->v_1p2) अणु
			hdmi_dsc->native_420 = hf_vsdb[11] & DRM_EDID_DSC_NATIVE_420;
			hdmi_dsc->all_bpp = hf_vsdb[11] & DRM_EDID_DSC_ALL_BPP;

			अगर (hf_vsdb[11] & DRM_EDID_DSC_16BPC)
				hdmi_dsc->bpc_supported = 16;
			अन्यथा अगर (hf_vsdb[11] & DRM_EDID_DSC_12BPC)
				hdmi_dsc->bpc_supported = 12;
			अन्यथा अगर (hf_vsdb[11] & DRM_EDID_DSC_10BPC)
				hdmi_dsc->bpc_supported = 10;
			अन्यथा
				hdmi_dsc->bpc_supported = 0;

			dsc_max_frl_rate = (hf_vsdb[12] & DRM_EDID_DSC_MAX_FRL_RATE_MASK) >> 4;
			drm_get_max_frl_rate(dsc_max_frl_rate, &hdmi_dsc->max_lanes,
					     &hdmi_dsc->max_frl_rate_per_lane);
			hdmi_dsc->total_chunk_kbytes = hf_vsdb[13] & DRM_EDID_DSC_TOTAL_CHUNK_KBYTES;

			dsc_max_slices = hf_vsdb[12] & DRM_EDID_DSC_MAX_SLICES;
			चयन (dsc_max_slices) अणु
			हाल 1:
				hdmi_dsc->max_slices = 1;
				hdmi_dsc->clk_per_slice = 340;
				अवरोध;
			हाल 2:
				hdmi_dsc->max_slices = 2;
				hdmi_dsc->clk_per_slice = 340;
				अवरोध;
			हाल 3:
				hdmi_dsc->max_slices = 4;
				hdmi_dsc->clk_per_slice = 340;
				अवरोध;
			हाल 4:
				hdmi_dsc->max_slices = 8;
				hdmi_dsc->clk_per_slice = 340;
				अवरोध;
			हाल 5:
				hdmi_dsc->max_slices = 8;
				hdmi_dsc->clk_per_slice = 400;
				अवरोध;
			हाल 6:
				hdmi_dsc->max_slices = 12;
				hdmi_dsc->clk_per_slice = 400;
				अवरोध;
			हाल 7:
				hdmi_dsc->max_slices = 16;
				hdmi_dsc->clk_per_slice = 400;
				अवरोध;
			हाल 0:
			शेष:
				hdmi_dsc->max_slices = 0;
				hdmi_dsc->clk_per_slice = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	drm_parse_ycbcr420_deep_color_info(connector, hf_vsdb);
पूर्ण

अटल व्योम drm_parse_hdmi_deep_color_info(काष्ठा drm_connector *connector,
					   स्थिर u8 *hdmi)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;
	अचिन्हित पूर्णांक dc_bpc = 0;

	/* HDMI supports at least 8 bpc */
	info->bpc = 8;

	अगर (cea_db_payload_len(hdmi) < 6)
		वापस;

	अगर (hdmi[6] & DRM_EDID_HDMI_DC_30) अणु
		dc_bpc = 10;
		info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_30;
		DRM_DEBUG("%s: HDMI sink does deep color 30.\n",
			  connector->name);
	पूर्ण

	अगर (hdmi[6] & DRM_EDID_HDMI_DC_36) अणु
		dc_bpc = 12;
		info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_36;
		DRM_DEBUG("%s: HDMI sink does deep color 36.\n",
			  connector->name);
	पूर्ण

	अगर (hdmi[6] & DRM_EDID_HDMI_DC_48) अणु
		dc_bpc = 16;
		info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_48;
		DRM_DEBUG("%s: HDMI sink does deep color 48.\n",
			  connector->name);
	पूर्ण

	अगर (dc_bpc == 0) अणु
		DRM_DEBUG("%s: No deep color support on this HDMI sink.\n",
			  connector->name);
		वापस;
	पूर्ण

	DRM_DEBUG("%s: Assigning HDMI sink color depth as %d bpc.\n",
		  connector->name, dc_bpc);
	info->bpc = dc_bpc;

	/*
	 * Deep color support mandates RGB444 support क्रम all video
	 * modes and क्रमbids YCRCB422 support क्रम all video modes per
	 * HDMI 1.3 spec.
	 */
	info->color_क्रमmats = DRM_COLOR_FORMAT_RGB444;

	/* YCRCB444 is optional according to spec. */
	अगर (hdmi[6] & DRM_EDID_HDMI_DC_Y444) अणु
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB444;
		DRM_DEBUG("%s: HDMI sink does YCRCB444 in deep color.\n",
			  connector->name);
	पूर्ण

	/*
	 * Spec says that अगर any deep color mode is supported at all,
	 * then deep color 36 bit must be supported.
	 */
	अगर (!(hdmi[6] & DRM_EDID_HDMI_DC_36)) अणु
		DRM_DEBUG("%s: HDMI sink should do DC_36, but does not!\n",
			  connector->name);
	पूर्ण
पूर्ण

अटल व्योम
drm_parse_hdmi_vsdb_video(काष्ठा drm_connector *connector, स्थिर u8 *db)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;
	u8 len = cea_db_payload_len(db);

	info->is_hdmi = true;

	अगर (len >= 6)
		info->dvi_dual = db[6] & 1;
	अगर (len >= 7)
		info->max_पंचांगds_घड़ी = db[7] * 5000;

	DRM_DEBUG_KMS("HDMI: DVI dual %d, "
		      "max TMDS clock %d kHz\n",
		      info->dvi_dual,
		      info->max_पंचांगds_घड़ी);

	drm_parse_hdmi_deep_color_info(connector, db);
पूर्ण

अटल व्योम drm_parse_cea_ext(काष्ठा drm_connector *connector,
			      स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;
	स्थिर u8 *edid_ext;
	पूर्णांक i, start, end;

	edid_ext = drm_find_cea_extension(edid);
	अगर (!edid_ext)
		वापस;

	info->cea_rev = edid_ext[1];

	/* The existence of a CEA block should imply RGB support */
	info->color_क्रमmats = DRM_COLOR_FORMAT_RGB444;
	अगर (edid_ext[3] & EDID_CEA_YCRCB444)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB444;
	अगर (edid_ext[3] & EDID_CEA_YCRCB422)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB422;

	अगर (cea_db_offsets(edid_ext, &start, &end))
		वापस;

	क्रम_each_cea_db(edid_ext, i, start, end) अणु
		स्थिर u8 *db = &edid_ext[i];

		अगर (cea_db_is_hdmi_vsdb(db))
			drm_parse_hdmi_vsdb_video(connector, db);
		अगर (cea_db_is_hdmi_क्रमum_vsdb(db))
			drm_parse_hdmi_क्रमum_vsdb(connector, db);
		अगर (cea_db_is_y420cmdb(db))
			drm_parse_y420cmdb_biपंचांगap(connector, db);
		अगर (cea_db_is_vcdb(db))
			drm_parse_vcdb(connector, db);
		अगर (cea_db_is_hdmi_hdr_metadata_block(db))
			drm_parse_hdr_metadata_block(connector, db);
	पूर्ण
पूर्ण

अटल
व्योम get_monitor_range(काष्ठा detailed_timing *timing,
		       व्योम *info_monitor_range)
अणु
	काष्ठा drm_monitor_range_info *monitor_range = info_monitor_range;
	स्थिर काष्ठा detailed_non_pixel *data = &timing->data.other_data;
	स्थिर काष्ठा detailed_data_monitor_range *range = &data->data.range;

	अगर (!is_display_descriptor((स्थिर u8 *)timing, EDID_DETAIL_MONITOR_RANGE))
		वापस;

	/*
	 * Check क्रम flag range limits only. If flag == 1 then
	 * no additional timing inक्रमmation provided.
	 * Default GTF, GTF Secondary curve and CVT are not
	 * supported
	 */
	अगर (range->flags != DRM_EDID_RANGE_LIMITS_ONLY_FLAG)
		वापस;

	monitor_range->min_vfreq = range->min_vfreq;
	monitor_range->max_vfreq = range->max_vfreq;
पूर्ण

अटल
व्योम drm_get_monitor_range(काष्ठा drm_connector *connector,
			   स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;

	अगर (!version_greater(edid, 1, 1))
		वापस;

	drm_क्रम_each_detailed_block((u8 *)edid, get_monitor_range,
				    &info->monitor_range);

	DRM_DEBUG_KMS("Supported Monitor Refresh rate range is %d Hz - %d Hz\n",
		      info->monitor_range.min_vfreq,
		      info->monitor_range.max_vfreq);
पूर्ण

/* A connector has no EDID inक्रमmation, so we've got no EDID to compute quirks from. Reset
 * all of the values which would have been set from EDID
 */
व्योम
drm_reset_display_info(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;

	info->width_mm = 0;
	info->height_mm = 0;

	info->bpc = 0;
	info->color_क्रमmats = 0;
	info->cea_rev = 0;
	info->max_पंचांगds_घड़ी = 0;
	info->dvi_dual = false;
	info->is_hdmi = false;
	info->has_hdmi_infoframe = false;
	info->rgb_quant_range_selectable = false;
	स_रखो(&info->hdmi, 0, माप(info->hdmi));

	info->non_desktop = 0;
	स_रखो(&info->monitor_range, 0, माप(info->monitor_range));
पूर्ण

u32 drm_add_display_info(काष्ठा drm_connector *connector, स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_display_info *info = &connector->display_info;

	u32 quirks = edid_get_quirks(edid);

	drm_reset_display_info(connector);

	info->width_mm = edid->width_cm * 10;
	info->height_mm = edid->height_cm * 10;

	info->non_desktop = !!(quirks & EDID_QUIRK_NON_DESKTOP);

	drm_get_monitor_range(connector, edid);

	DRM_DEBUG_KMS("non_desktop set to %d\n", info->non_desktop);

	अगर (edid->revision < 3)
		वापस quirks;

	अगर (!(edid->input & DRM_EDID_INPUT_DIGITAL))
		वापस quirks;

	drm_parse_cea_ext(connector, edid);

	/*
	 * Digital sink with "DFP 1.x compliant TMDS" according to EDID 1.3?
	 *
	 * For such displays, the DFP spec 1.0, section 3.10 "EDID support"
	 * tells us to assume 8 bpc color depth अगर the EDID करोesn't have
	 * extensions which tell otherwise.
	 */
	अगर (info->bpc == 0 && edid->revision == 3 &&
	    edid->input & DRM_EDID_DIGITAL_DFP_1_X) अणु
		info->bpc = 8;
		DRM_DEBUG("%s: Assigning DFP sink color depth as %d bpc.\n",
			  connector->name, info->bpc);
	पूर्ण

	/* Only defined क्रम 1.4 with digital displays */
	अगर (edid->revision < 4)
		वापस quirks;

	चयन (edid->input & DRM_EDID_DIGITAL_DEPTH_MASK) अणु
	हाल DRM_EDID_DIGITAL_DEPTH_6:
		info->bpc = 6;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_8:
		info->bpc = 8;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_10:
		info->bpc = 10;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_12:
		info->bpc = 12;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_14:
		info->bpc = 14;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_16:
		info->bpc = 16;
		अवरोध;
	हाल DRM_EDID_DIGITAL_DEPTH_UNDEF:
	शेष:
		info->bpc = 0;
		अवरोध;
	पूर्ण

	DRM_DEBUG("%s: Assigning EDID-1.4 digital sink color depth as %d bpc.\n",
			  connector->name, info->bpc);

	info->color_क्रमmats |= DRM_COLOR_FORMAT_RGB444;
	अगर (edid->features & DRM_EDID_FEATURE_RGB_YCRCB444)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB444;
	अगर (edid->features & DRM_EDID_FEATURE_RGB_YCRCB422)
		info->color_क्रमmats |= DRM_COLOR_FORMAT_YCRCB422;
	वापस quirks;
पूर्ण

अटल काष्ठा drm_display_mode *drm_mode_displayid_detailed(काष्ठा drm_device *dev,
							    काष्ठा displayid_detailed_timings_1 *timings)
अणु
	काष्ठा drm_display_mode *mode;
	अचिन्हित pixel_घड़ी = (timings->pixel_घड़ी[0] |
				(timings->pixel_घड़ी[1] << 8) |
				(timings->pixel_घड़ी[2] << 16)) + 1;
	अचिन्हित hactive = (timings->hactive[0] | timings->hactive[1] << 8) + 1;
	अचिन्हित hblank = (timings->hblank[0] | timings->hblank[1] << 8) + 1;
	अचिन्हित hsync = (timings->hsync[0] | (timings->hsync[1] & 0x7f) << 8) + 1;
	अचिन्हित hsync_width = (timings->hsw[0] | timings->hsw[1] << 8) + 1;
	अचिन्हित vactive = (timings->vactive[0] | timings->vactive[1] << 8) + 1;
	अचिन्हित vblank = (timings->vblank[0] | timings->vblank[1] << 8) + 1;
	अचिन्हित vsync = (timings->vsync[0] | (timings->vsync[1] & 0x7f) << 8) + 1;
	अचिन्हित vsync_width = (timings->vsw[0] | timings->vsw[1] << 8) + 1;
	bool hsync_positive = (timings->hsync[1] >> 7) & 0x1;
	bool vsync_positive = (timings->vsync[1] >> 7) & 0x1;

	mode = drm_mode_create(dev);
	अगर (!mode)
		वापस शून्य;

	mode->घड़ी = pixel_घड़ी * 10;
	mode->hdisplay = hactive;
	mode->hsync_start = mode->hdisplay + hsync;
	mode->hsync_end = mode->hsync_start + hsync_width;
	mode->htotal = mode->hdisplay + hblank;

	mode->vdisplay = vactive;
	mode->vsync_start = mode->vdisplay + vsync;
	mode->vsync_end = mode->vsync_start + vsync_width;
	mode->vtotal = mode->vdisplay + vblank;

	mode->flags = 0;
	mode->flags |= hsync_positive ? DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= vsync_positive ? DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;
	mode->type = DRM_MODE_TYPE_DRIVER;

	अगर (timings->flags & 0x80)
		mode->type |= DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);

	वापस mode;
पूर्ण

अटल पूर्णांक add_displayid_detailed_1_modes(काष्ठा drm_connector *connector,
					  स्थिर काष्ठा displayid_block *block)
अणु
	काष्ठा displayid_detailed_timing_block *det = (काष्ठा displayid_detailed_timing_block *)block;
	पूर्णांक i;
	पूर्णांक num_timings;
	काष्ठा drm_display_mode *newmode;
	पूर्णांक num_modes = 0;
	/* blocks must be multiple of 20 bytes length */
	अगर (block->num_bytes % 20)
		वापस 0;

	num_timings = block->num_bytes / 20;
	क्रम (i = 0; i < num_timings; i++) अणु
		काष्ठा displayid_detailed_timings_1 *timings = &det->timings[i];

		newmode = drm_mode_displayid_detailed(connector->dev, timings);
		अगर (!newmode)
			जारी;

		drm_mode_probed_add(connector, newmode);
		num_modes++;
	पूर्ण
	वापस num_modes;
पूर्ण

अटल पूर्णांक add_displayid_detailed_modes(काष्ठा drm_connector *connector,
					काष्ठा edid *edid)
अणु
	स्थिर काष्ठा displayid_block *block;
	काष्ठा displayid_iter iter;
	पूर्णांक num_modes = 0;

	displayid_iter_edid_begin(edid, &iter);
	displayid_iter_क्रम_each(block, &iter) अणु
		अगर (block->tag == DATA_BLOCK_TYPE_1_DETAILED_TIMING)
			num_modes += add_displayid_detailed_1_modes(connector, block);
	पूर्ण
	displayid_iter_end(&iter);

	वापस num_modes;
पूर्ण

/**
 * drm_add_edid_modes - add modes from EDID data, अगर available
 * @connector: connector we're probing
 * @edid: EDID data
 *
 * Add the specअगरied modes to the connector's mode list. Also fills out the
 * &drm_display_info काष्ठाure and ELD in @connector with any inक्रमmation which
 * can be derived from the edid.
 *
 * Return: The number of modes added or 0 अगर we couldn't find any.
 */
पूर्णांक drm_add_edid_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid)
अणु
	पूर्णांक num_modes = 0;
	u32 quirks;

	अगर (edid == शून्य) अणु
		clear_eld(connector);
		वापस 0;
	पूर्ण
	अगर (!drm_edid_is_valid(edid)) अणु
		clear_eld(connector);
		drm_warn(connector->dev, "%s: EDID invalid.\n",
			 connector->name);
		वापस 0;
	पूर्ण

	drm_edid_to_eld(connector, edid);

	/*
	 * CEA-861-F adds ycbcr capability map block, क्रम HDMI 2.0 sinks.
	 * To aव्योम multiple parsing of same block, lets parse that map
	 * from sink info, beक्रमe parsing CEA modes.
	 */
	quirks = drm_add_display_info(connector, edid);

	/*
	 * EDID spec says modes should be preferred in this order:
	 * - preferred detailed mode
	 * - other detailed modes from base block
	 * - detailed modes from extension blocks
	 * - CVT 3-byte code modes
	 * - standard timing codes
	 * - established timing codes
	 * - modes inferred from GTF or CVT range inक्रमmation
	 *
	 * We get this pretty much right.
	 *
	 * XXX order क्रम additional mode types in extension blocks?
	 */
	num_modes += add_detailed_modes(connector, edid, quirks);
	num_modes += add_cvt_modes(connector, edid);
	num_modes += add_standard_modes(connector, edid);
	num_modes += add_established_modes(connector, edid);
	num_modes += add_cea_modes(connector, edid);
	num_modes += add_alternate_cea_modes(connector, edid);
	num_modes += add_displayid_detailed_modes(connector, edid);
	अगर (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)
		num_modes += add_inferred_modes(connector, edid);

	अगर (quirks & (EDID_QUIRK_PREFER_LARGE_60 | EDID_QUIRK_PREFER_LARGE_75))
		edid_fixup_preferred(connector, quirks);

	अगर (quirks & EDID_QUIRK_FORCE_6BPC)
		connector->display_info.bpc = 6;

	अगर (quirks & EDID_QUIRK_FORCE_8BPC)
		connector->display_info.bpc = 8;

	अगर (quirks & EDID_QUIRK_FORCE_10BPC)
		connector->display_info.bpc = 10;

	अगर (quirks & EDID_QUIRK_FORCE_12BPC)
		connector->display_info.bpc = 12;

	वापस num_modes;
पूर्ण
EXPORT_SYMBOL(drm_add_edid_modes);

/**
 * drm_add_modes_noedid - add modes क्रम the connectors without EDID
 * @connector: connector we're probing
 * @hdisplay: the horizontal display limit
 * @vdisplay: the vertical display limit
 *
 * Add the specअगरied modes to the connector's mode list. Only when the
 * hdisplay/vdisplay is not beyond the given limit, it will be added.
 *
 * Return: The number of modes added or 0 अगर we couldn't find any.
 */
पूर्णांक drm_add_modes_noedid(काष्ठा drm_connector *connector,
			पूर्णांक hdisplay, पूर्णांक vdisplay)
अणु
	पूर्णांक i, count, num_modes = 0;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_device *dev = connector->dev;

	count = ARRAY_SIZE(drm_dmt_modes);
	अगर (hdisplay < 0)
		hdisplay = 0;
	अगर (vdisplay < 0)
		vdisplay = 0;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर काष्ठा drm_display_mode *ptr = &drm_dmt_modes[i];

		अगर (hdisplay && vdisplay) अणु
			/*
			 * Only when two are valid, they will be used to check
			 * whether the mode should be added to the mode list of
			 * the connector.
			 */
			अगर (ptr->hdisplay > hdisplay ||
					ptr->vdisplay > vdisplay)
				जारी;
		पूर्ण
		अगर (drm_mode_vrefresh(ptr) > 61)
			जारी;
		mode = drm_mode_duplicate(dev, ptr);
		अगर (mode) अणु
			drm_mode_probed_add(connector, mode);
			num_modes++;
		पूर्ण
	पूर्ण
	वापस num_modes;
पूर्ण
EXPORT_SYMBOL(drm_add_modes_noedid);

/**
 * drm_set_preferred_mode - Sets the preferred mode of a connector
 * @connector: connector whose mode list should be processed
 * @hpref: horizontal resolution of preferred mode
 * @vpref: vertical resolution of preferred mode
 *
 * Marks a mode as preferred अगर it matches the resolution specअगरied by @hpref
 * and @vpref.
 */
व्योम drm_set_preferred_mode(काष्ठा drm_connector *connector,
			   पूर्णांक hpref, पूर्णांक vpref)
अणु
	काष्ठा drm_display_mode *mode;

	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		अगर (mode->hdisplay == hpref &&
		    mode->vdisplay == vpref)
			mode->type |= DRM_MODE_TYPE_PREFERRED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_set_preferred_mode);

अटल bool is_hdmi2_sink(स्थिर काष्ठा drm_connector *connector)
अणु
	/*
	 * FIXME: sil-sii8620 करोesn't have a connector around when
	 * we need one, so we have to be prepared क्रम a शून्य connector.
	 */
	अगर (!connector)
		वापस true;

	वापस connector->display_info.hdmi.scdc.supported ||
		connector->display_info.color_क्रमmats & DRM_COLOR_FORMAT_YCRCB420;
पूर्ण

अटल अंतरभूत bool is_eotf_supported(u8 output_eotf, u8 sink_eotf)
अणु
	वापस sink_eotf & BIT(output_eotf);
पूर्ण

/**
 * drm_hdmi_infoframe_set_hdr_metadata() - fill an HDMI DRM infoframe with
 *                                         HDR metadata from userspace
 * @frame: HDMI DRM infoframe
 * @conn_state: Connector state containing HDR metadata
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक
drm_hdmi_infoframe_set_hdr_metadata(काष्ठा hdmi_drm_infoframe *frame,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा hdr_output_metadata *hdr_metadata;
	पूर्णांक err;

	अगर (!frame || !conn_state)
		वापस -EINVAL;

	connector = conn_state->connector;

	अगर (!conn_state->hdr_output_metadata)
		वापस -EINVAL;

	hdr_metadata = conn_state->hdr_output_metadata->data;

	अगर (!hdr_metadata || !connector)
		वापस -EINVAL;

	/* Sink EOTF is Bit map जबतक infoframe is असलolute values */
	अगर (!is_eotf_supported(hdr_metadata->hdmi_metadata_type1.eotf,
	    connector->hdr_sink_metadata.hdmi_type1.eotf)) अणु
		DRM_DEBUG_KMS("EOTF Not Supported\n");
		वापस -EINVAL;
	पूर्ण

	err = hdmi_drm_infoframe_init(frame);
	अगर (err < 0)
		वापस err;

	frame->eotf = hdr_metadata->hdmi_metadata_type1.eotf;
	frame->metadata_type = hdr_metadata->hdmi_metadata_type1.metadata_type;

	BUILD_BUG_ON(माप(frame->display_primaries) !=
		     माप(hdr_metadata->hdmi_metadata_type1.display_primaries));
	BUILD_BUG_ON(माप(frame->white_poपूर्णांक) !=
		     माप(hdr_metadata->hdmi_metadata_type1.white_poपूर्णांक));

	स_नकल(&frame->display_primaries,
	       &hdr_metadata->hdmi_metadata_type1.display_primaries,
	       माप(frame->display_primaries));

	स_नकल(&frame->white_poपूर्णांक,
	       &hdr_metadata->hdmi_metadata_type1.white_poपूर्णांक,
	       माप(frame->white_poपूर्णांक));

	frame->max_display_mastering_luminance =
		hdr_metadata->hdmi_metadata_type1.max_display_mastering_luminance;
	frame->min_display_mastering_luminance =
		hdr_metadata->hdmi_metadata_type1.min_display_mastering_luminance;
	frame->max_fall = hdr_metadata->hdmi_metadata_type1.max_fall;
	frame->max_cll = hdr_metadata->hdmi_metadata_type1.max_cll;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_infoframe_set_hdr_metadata);

अटल u8 drm_mode_hdmi_vic(स्थिर काष्ठा drm_connector *connector,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	bool has_hdmi_infoframe = connector ?
		connector->display_info.has_hdmi_infoframe : false;

	अगर (!has_hdmi_infoframe)
		वापस 0;

	/* No HDMI VIC when संकेतling 3D video क्रमmat */
	अगर (mode->flags & DRM_MODE_FLAG_3D_MASK)
		वापस 0;

	वापस drm_match_hdmi_mode(mode);
पूर्ण

अटल u8 drm_mode_cea_vic(स्थिर काष्ठा drm_connector *connector,
			   स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 vic;

	/*
	 * HDMI spec says अगर a mode is found in HDMI 1.4b 4K modes
	 * we should send its VIC in venकरोr infoframes, अन्यथा send the
	 * VIC in AVI infoframes. Lets check अगर this mode is present in
	 * HDMI 1.4b 4K modes
	 */
	अगर (drm_mode_hdmi_vic(connector, mode))
		वापस 0;

	vic = drm_match_cea_mode(mode);

	/*
	 * HDMI 1.4 VIC range: 1 <= VIC <= 64 (CEA-861-D) but
	 * HDMI 2.0 VIC range: 1 <= VIC <= 107 (CEA-861-F). So we
	 * have to make sure we करोnt अवरोध HDMI 1.4 sinks.
	 */
	अगर (!is_hdmi2_sink(connector) && vic > 64)
		वापस 0;

	वापस vic;
पूर्ण

/**
 * drm_hdmi_avi_infoframe_from_display_mode() - fill an HDMI AVI infoframe with
 *                                              data from a DRM display mode
 * @frame: HDMI AVI infoframe
 * @connector: the connector
 * @mode: DRM display mode
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक
drm_hdmi_avi_infoframe_from_display_mode(काष्ठा hdmi_avi_infoframe *frame,
					 स्थिर काष्ठा drm_connector *connector,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	क्रमागत hdmi_picture_aspect picture_aspect;
	u8 vic, hdmi_vic;

	अगर (!frame || !mode)
		वापस -EINVAL;

	hdmi_avi_infoframe_init(frame);

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		frame->pixel_repeat = 1;

	vic = drm_mode_cea_vic(connector, mode);
	hdmi_vic = drm_mode_hdmi_vic(connector, mode);

	frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;

	/*
	 * As some drivers करोn't support atomic, we can't use connector state.
	 * So just initialize the frame with शेष values, just the same way
	 * as it's करोne with other properties here.
	 */
	frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
	frame->itc = 0;

	/*
	 * Populate picture aspect ratio from either
	 * user input (अगर specअगरied) or from the CEA/HDMI mode lists.
	 */
	picture_aspect = mode->picture_aspect_ratio;
	अगर (picture_aspect == HDMI_PICTURE_ASPECT_NONE) अणु
		अगर (vic)
			picture_aspect = drm_get_cea_aspect_ratio(vic);
		अन्यथा अगर (hdmi_vic)
			picture_aspect = drm_get_hdmi_aspect_ratio(hdmi_vic);
	पूर्ण

	/*
	 * The infoframe can't convey anything but none, 4:3
	 * and 16:9, so अगर the user has asked क्रम anything अन्यथा
	 * we can only satisfy it by specअगरying the right VIC.
	 */
	अगर (picture_aspect > HDMI_PICTURE_ASPECT_16_9) अणु
		अगर (vic) अणु
			अगर (picture_aspect != drm_get_cea_aspect_ratio(vic))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (hdmi_vic) अणु
			अगर (picture_aspect != drm_get_hdmi_aspect_ratio(hdmi_vic))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		picture_aspect = HDMI_PICTURE_ASPECT_NONE;
	पूर्ण

	frame->video_code = vic;
	frame->picture_aspect = picture_aspect;
	frame->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;
	frame->scan_mode = HDMI_SCAN_MODE_UNDERSCAN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_from_display_mode);

/* HDMI Colorspace Spec Definitions */
#घोषणा FULL_COLORIMETRY_MASK		0x1FF
#घोषणा NORMAL_COLORIMETRY_MASK		0x3
#घोषणा EXTENDED_COLORIMETRY_MASK	0x7
#घोषणा EXTENDED_ACE_COLORIMETRY_MASK	0xF

#घोषणा C(x) ((x) << 0)
#घोषणा EC(x) ((x) << 2)
#घोषणा ACE(x) ((x) << 5)

#घोषणा HDMI_COLORIMETRY_NO_DATA		0x0
#घोषणा HDMI_COLORIMETRY_SMPTE_170M_YCC		(C(1) | EC(0) | ACE(0))
#घोषणा HDMI_COLORIMETRY_BT709_YCC		(C(2) | EC(0) | ACE(0))
#घोषणा HDMI_COLORIMETRY_XVYCC_601		(C(3) | EC(0) | ACE(0))
#घोषणा HDMI_COLORIMETRY_XVYCC_709		(C(3) | EC(1) | ACE(0))
#घोषणा HDMI_COLORIMETRY_SYCC_601		(C(3) | EC(2) | ACE(0))
#घोषणा HDMI_COLORIMETRY_OPYCC_601		(C(3) | EC(3) | ACE(0))
#घोषणा HDMI_COLORIMETRY_OPRGB			(C(3) | EC(4) | ACE(0))
#घोषणा HDMI_COLORIMETRY_BT2020_CYCC		(C(3) | EC(5) | ACE(0))
#घोषणा HDMI_COLORIMETRY_BT2020_RGB		(C(3) | EC(6) | ACE(0))
#घोषणा HDMI_COLORIMETRY_BT2020_YCC		(C(3) | EC(6) | ACE(0))
#घोषणा HDMI_COLORIMETRY_DCI_P3_RGB_D65		(C(3) | EC(7) | ACE(0))
#घोषणा HDMI_COLORIMETRY_DCI_P3_RGB_THEATER	(C(3) | EC(7) | ACE(1))

अटल स्थिर u32 hdmi_colorimetry_val[] = अणु
	[DRM_MODE_COLORIMETRY_NO_DATA] = HDMI_COLORIMETRY_NO_DATA,
	[DRM_MODE_COLORIMETRY_SMPTE_170M_YCC] = HDMI_COLORIMETRY_SMPTE_170M_YCC,
	[DRM_MODE_COLORIMETRY_BT709_YCC] = HDMI_COLORIMETRY_BT709_YCC,
	[DRM_MODE_COLORIMETRY_XVYCC_601] = HDMI_COLORIMETRY_XVYCC_601,
	[DRM_MODE_COLORIMETRY_XVYCC_709] = HDMI_COLORIMETRY_XVYCC_709,
	[DRM_MODE_COLORIMETRY_SYCC_601] = HDMI_COLORIMETRY_SYCC_601,
	[DRM_MODE_COLORIMETRY_OPYCC_601] = HDMI_COLORIMETRY_OPYCC_601,
	[DRM_MODE_COLORIMETRY_OPRGB] = HDMI_COLORIMETRY_OPRGB,
	[DRM_MODE_COLORIMETRY_BT2020_CYCC] = HDMI_COLORIMETRY_BT2020_CYCC,
	[DRM_MODE_COLORIMETRY_BT2020_RGB] = HDMI_COLORIMETRY_BT2020_RGB,
	[DRM_MODE_COLORIMETRY_BT2020_YCC] = HDMI_COLORIMETRY_BT2020_YCC,
पूर्ण;

#अघोषित C
#अघोषित EC
#अघोषित ACE

/**
 * drm_hdmi_avi_infoframe_colorspace() - fill the HDMI AVI infoframe
 *                                       colorspace inक्रमmation
 * @frame: HDMI AVI infoframe
 * @conn_state: connector state
 */
व्योम
drm_hdmi_avi_infoframe_colorspace(काष्ठा hdmi_avi_infoframe *frame,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	u32 colorimetry_val;
	u32 colorimetry_index = conn_state->colorspace & FULL_COLORIMETRY_MASK;

	अगर (colorimetry_index >= ARRAY_SIZE(hdmi_colorimetry_val))
		colorimetry_val = HDMI_COLORIMETRY_NO_DATA;
	अन्यथा
		colorimetry_val = hdmi_colorimetry_val[colorimetry_index];

	frame->colorimetry = colorimetry_val & NORMAL_COLORIMETRY_MASK;
	/*
	 * ToDo: Extend it क्रम ACE क्रमmats as well. Modअगरy the infoframe
	 * काष्ठाure and extend it in drivers/video/hdmi
	 */
	frame->extended_colorimetry = (colorimetry_val >> 2) &
					EXTENDED_COLORIMETRY_MASK;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_colorspace);

/**
 * drm_hdmi_avi_infoframe_quant_range() - fill the HDMI AVI infoframe
 *                                        quantization range inक्रमmation
 * @frame: HDMI AVI infoframe
 * @connector: the connector
 * @mode: DRM display mode
 * @rgb_quant_range: RGB quantization range (Q)
 */
व्योम
drm_hdmi_avi_infoframe_quant_range(काष्ठा hdmi_avi_infoframe *frame,
				   स्थिर काष्ठा drm_connector *connector,
				   स्थिर काष्ठा drm_display_mode *mode,
				   क्रमागत hdmi_quantization_range rgb_quant_range)
अणु
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;

	/*
	 * CEA-861:
	 * "A Source shall not send a non-zero Q value that करोes not correspond
	 *  to the शेष RGB Quantization Range क्रम the transmitted Picture
	 *  unless the Sink indicates support क्रम the Q bit in a Video
	 *  Capabilities Data Block."
	 *
	 * HDMI 2.0 recommends sending non-zero Q when it करोes match the
	 * शेष RGB quantization range क्रम the mode, even when QS=0.
	 */
	अगर (info->rgb_quant_range_selectable ||
	    rgb_quant_range == drm_शेष_rgb_quant_range(mode))
		frame->quantization_range = rgb_quant_range;
	अन्यथा
		frame->quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;

	/*
	 * CEA-861-F:
	 * "When transmitting any RGB colorimetry, the Source should set the
	 *  YQ-field to match the RGB Quantization Range being transmitted
	 *  (e.g., when Limited Range RGB, set YQ=0 or when Full Range RGB,
	 *  set YQ=1) and the Sink shall ignore the YQ-field."
	 *
	 * Unक्रमtunate certain sinks (eg. VIZ Model 67/E261VA) get confused
	 * by non-zero YQ when receiving RGB. There करोesn't seem to be any
	 * good way to tell which version of CEA-861 the sink supports, so
	 * we limit non-zero YQ to HDMI 2.0 sinks only as HDMI 2.0 is based
	 * on on CEA-861-F.
	 */
	अगर (!is_hdmi2_sink(connector) ||
	    rgb_quant_range == HDMI_QUANTIZATION_RANGE_LIMITED)
		frame->ycc_quantization_range =
			HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	अन्यथा
		frame->ycc_quantization_range =
			HDMI_YCC_QUANTIZATION_RANGE_FULL;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_quant_range);

/**
 * drm_hdmi_avi_infoframe_bars() - fill the HDMI AVI infoframe
 *                                 bar inक्रमmation
 * @frame: HDMI AVI infoframe
 * @conn_state: connector state
 */
व्योम
drm_hdmi_avi_infoframe_bars(काष्ठा hdmi_avi_infoframe *frame,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	frame->right_bar = conn_state->tv.margins.right;
	frame->left_bar = conn_state->tv.margins.left;
	frame->top_bar = conn_state->tv.margins.top;
	frame->bottom_bar = conn_state->tv.margins.bottom;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_bars);

अटल क्रमागत hdmi_3d_काष्ठाure
s3d_काष्ठाure_from_display_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 layout = mode->flags & DRM_MODE_FLAG_3D_MASK;

	चयन (layout) अणु
	हाल DRM_MODE_FLAG_3D_FRAME_PACKING:
		वापस HDMI_3D_STRUCTURE_FRAME_PACKING;
	हाल DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE:
		वापस HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE;
	हाल DRM_MODE_FLAG_3D_LINE_ALTERNATIVE:
		वापस HDMI_3D_STRUCTURE_LINE_ALTERNATIVE;
	हाल DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL:
		वापस HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL;
	हाल DRM_MODE_FLAG_3D_L_DEPTH:
		वापस HDMI_3D_STRUCTURE_L_DEPTH;
	हाल DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH:
		वापस HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH;
	हाल DRM_MODE_FLAG_3D_TOP_AND_BOTTOM:
		वापस HDMI_3D_STRUCTURE_TOP_AND_BOTTOM;
	हाल DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF:
		वापस HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF;
	शेष:
		वापस HDMI_3D_STRUCTURE_INVALID;
	पूर्ण
पूर्ण

/**
 * drm_hdmi_venकरोr_infoframe_from_display_mode() - fill an HDMI infoframe with
 * data from a DRM display mode
 * @frame: HDMI venकरोr infoframe
 * @connector: the connector
 * @mode: DRM display mode
 *
 * Note that there's is a need to send HDMI venकरोr infoframes only when using a
 * 4k or stereoscopic 3D mode. So when giving any other mode as input this
 * function will वापस -EINVAL, error that can be safely ignored.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक
drm_hdmi_venकरोr_infoframe_from_display_mode(काष्ठा hdmi_venकरोr_infoframe *frame,
					    स्थिर काष्ठा drm_connector *connector,
					    स्थिर काष्ठा drm_display_mode *mode)
अणु
	/*
	 * FIXME: sil-sii8620 करोesn't have a connector around when
	 * we need one, so we have to be prepared क्रम a शून्य connector.
	 */
	bool has_hdmi_infoframe = connector ?
		connector->display_info.has_hdmi_infoframe : false;
	पूर्णांक err;

	अगर (!frame || !mode)
		वापस -EINVAL;

	अगर (!has_hdmi_infoframe)
		वापस -EINVAL;

	err = hdmi_venकरोr_infoframe_init(frame);
	अगर (err < 0)
		वापस err;

	/*
	 * Even अगर it's not असलolutely necessary to send the infoframe
	 * (ie.vic==0 and s3d_काष्ठा==0) we will still send it अगर we
	 * know that the sink can handle it. This is based on a
	 * suggestion in HDMI 2.0 Appendix F. Apparently some sinks
	 * have trouble realizing that they shuld चयन from 3D to 2D
	 * mode अगर the source simply stops sending the infoframe when
	 * it wants to चयन from 3D to 2D.
	 */
	frame->vic = drm_mode_hdmi_vic(connector, mode);
	frame->s3d_काष्ठा = s3d_काष्ठाure_from_display_mode(mode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_venकरोr_infoframe_from_display_mode);

अटल व्योम drm_parse_tiled_block(काष्ठा drm_connector *connector,
				  स्थिर काष्ठा displayid_block *block)
अणु
	स्थिर काष्ठा displayid_tiled_block *tile = (काष्ठा displayid_tiled_block *)block;
	u16 w, h;
	u8 tile_v_loc, tile_h_loc;
	u8 num_v_tile, num_h_tile;
	काष्ठा drm_tile_group *tg;

	w = tile->tile_size[0] | tile->tile_size[1] << 8;
	h = tile->tile_size[2] | tile->tile_size[3] << 8;

	num_v_tile = (tile->topo[0] & 0xf) | (tile->topo[2] & 0x30);
	num_h_tile = (tile->topo[0] >> 4) | ((tile->topo[2] >> 2) & 0x30);
	tile_v_loc = (tile->topo[1] & 0xf) | ((tile->topo[2] & 0x3) << 4);
	tile_h_loc = (tile->topo[1] >> 4) | (((tile->topo[2] >> 2) & 0x3) << 4);

	connector->has_tile = true;
	अगर (tile->tile_cap & 0x80)
		connector->tile_is_single_monitor = true;

	connector->num_h_tile = num_h_tile + 1;
	connector->num_v_tile = num_v_tile + 1;
	connector->tile_h_loc = tile_h_loc;
	connector->tile_v_loc = tile_v_loc;
	connector->tile_h_size = w + 1;
	connector->tile_v_size = h + 1;

	DRM_DEBUG_KMS("tile cap 0x%x\n", tile->tile_cap);
	DRM_DEBUG_KMS("tile_size %d x %d\n", w + 1, h + 1);
	DRM_DEBUG_KMS("topo num tiles %dx%d, location %dx%d\n",
		      num_h_tile + 1, num_v_tile + 1, tile_h_loc, tile_v_loc);
	DRM_DEBUG_KMS("vend %c%c%c\n", tile->topology_id[0], tile->topology_id[1], tile->topology_id[2]);

	tg = drm_mode_get_tile_group(connector->dev, tile->topology_id);
	अगर (!tg)
		tg = drm_mode_create_tile_group(connector->dev, tile->topology_id);
	अगर (!tg)
		वापस;

	अगर (connector->tile_group != tg) अणु
		/* अगर we haven't got a poपूर्णांकer,
		   take the reference, drop ref to old tile group */
		अगर (connector->tile_group)
			drm_mode_put_tile_group(connector->dev, connector->tile_group);
		connector->tile_group = tg;
	पूर्ण अन्यथा अणु
		/* अगर same tile group, then release the ref we just took. */
		drm_mode_put_tile_group(connector->dev, tg);
	पूर्ण
पूर्ण

व्योम drm_update_tile_info(काष्ठा drm_connector *connector,
			  स्थिर काष्ठा edid *edid)
अणु
	स्थिर काष्ठा displayid_block *block;
	काष्ठा displayid_iter iter;

	connector->has_tile = false;

	displayid_iter_edid_begin(edid, &iter);
	displayid_iter_क्रम_each(block, &iter) अणु
		अगर (block->tag == DATA_BLOCK_TILED_DISPLAY)
			drm_parse_tiled_block(connector, block);
	पूर्ण
	displayid_iter_end(&iter);

	अगर (!connector->has_tile && connector->tile_group) अणु
		drm_mode_put_tile_group(connector->dev, connector->tile_group);
		connector->tile_group = शून्य;
	पूर्ण
पूर्ण
