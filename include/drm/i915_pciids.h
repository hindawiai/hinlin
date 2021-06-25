<शैली गुरु>
/*
 * Copyright 2013 Intel Corporation
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित _I915_PCIIDS_H
#घोषणा _I915_PCIIDS_H

/*
 * A pci_device_id काष्ठा अणु
 *	__u32 venकरोr, device;
 *      __u32 subvenकरोr, subdevice;
 *	__u32 class, class_mask;
 *	kernel_uदीर्घ_t driver_data;
 * पूर्ण;
 * Don't use C99 here because "class" is reserved and we want to
 * give userspace flexibility.
 */
#घोषणा INTEL_VGA_DEVICE(id, info) अणु		\
	0x8086,	id,				\
	~0, ~0,					\
	0x030000, 0xff0000,			\
	(अचिन्हित दीर्घ) info पूर्ण

#घोषणा INTEL_QUANTA_VGA_DEVICE(info) अणु		\
	0x8086,	0x16a,				\
	0x152d,	0x8990,				\
	0x030000, 0xff0000,			\
	(अचिन्हित दीर्घ) info पूर्ण

#घोषणा INTEL_I810_IDS(info)					\
	INTEL_VGA_DEVICE(0x7121, info), /* I810 */		\
	INTEL_VGA_DEVICE(0x7123, info), /* I810_DC100 */	\
	INTEL_VGA_DEVICE(0x7125, info)  /* I810_E */

#घोषणा INTEL_I815_IDS(info)					\
	INTEL_VGA_DEVICE(0x1132, info)  /* I815*/

#घोषणा INTEL_I830_IDS(info)				\
	INTEL_VGA_DEVICE(0x3577, info)

#घोषणा INTEL_I845G_IDS(info)				\
	INTEL_VGA_DEVICE(0x2562, info)

#घोषणा INTEL_I85X_IDS(info)				\
	INTEL_VGA_DEVICE(0x3582, info), /* I855_GM */ \
	INTEL_VGA_DEVICE(0x358e, info)

#घोषणा INTEL_I865G_IDS(info)				\
	INTEL_VGA_DEVICE(0x2572, info) /* I865_G */

#घोषणा INTEL_I915G_IDS(info)				\
	INTEL_VGA_DEVICE(0x2582, info), /* I915_G */ \
	INTEL_VGA_DEVICE(0x258a, info)  /* E7221_G */

#घोषणा INTEL_I915GM_IDS(info)				\
	INTEL_VGA_DEVICE(0x2592, info) /* I915_GM */

#घोषणा INTEL_I945G_IDS(info)				\
	INTEL_VGA_DEVICE(0x2772, info) /* I945_G */

#घोषणा INTEL_I945GM_IDS(info)				\
	INTEL_VGA_DEVICE(0x27a2, info), /* I945_GM */ \
	INTEL_VGA_DEVICE(0x27ae, info)  /* I945_GME */

#घोषणा INTEL_I965G_IDS(info)				\
	INTEL_VGA_DEVICE(0x2972, info), /* I946_GZ */	\
	INTEL_VGA_DEVICE(0x2982, info),	/* G35_G */	\
	INTEL_VGA_DEVICE(0x2992, info),	/* I965_Q */	\
	INTEL_VGA_DEVICE(0x29a2, info)	/* I965_G */

#घोषणा INTEL_G33_IDS(info)				\
	INTEL_VGA_DEVICE(0x29b2, info), /* Q35_G */ \
	INTEL_VGA_DEVICE(0x29c2, info),	/* G33_G */ \
	INTEL_VGA_DEVICE(0x29d2, info)	/* Q33_G */

#घोषणा INTEL_I965GM_IDS(info)				\
	INTEL_VGA_DEVICE(0x2a02, info),	/* I965_GM */ \
	INTEL_VGA_DEVICE(0x2a12, info)  /* I965_GME */

#घोषणा INTEL_GM45_IDS(info)				\
	INTEL_VGA_DEVICE(0x2a42, info) /* GM45_G */

#घोषणा INTEL_G45_IDS(info)				\
	INTEL_VGA_DEVICE(0x2e02, info), /* IGD_E_G */ \
	INTEL_VGA_DEVICE(0x2e12, info), /* Q45_G */ \
	INTEL_VGA_DEVICE(0x2e22, info), /* G45_G */ \
	INTEL_VGA_DEVICE(0x2e32, info), /* G41_G */ \
	INTEL_VGA_DEVICE(0x2e42, info), /* B43_G */ \
	INTEL_VGA_DEVICE(0x2e92, info)	/* B43_G.1 */

#घोषणा INTEL_PINEVIEW_G_IDS(info) \
	INTEL_VGA_DEVICE(0xa001, info)

#घोषणा INTEL_PINEVIEW_M_IDS(info) \
	INTEL_VGA_DEVICE(0xa011, info)

#घोषणा INTEL_IRONLAKE_D_IDS(info) \
	INTEL_VGA_DEVICE(0x0042, info)

#घोषणा INTEL_IRONLAKE_M_IDS(info) \
	INTEL_VGA_DEVICE(0x0046, info)

#घोषणा INTEL_SNB_D_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0102, info), \
	INTEL_VGA_DEVICE(0x010A, info)

#घोषणा INTEL_SNB_D_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0112, info), \
	INTEL_VGA_DEVICE(0x0122, info)

#घोषणा INTEL_SNB_D_IDS(info) \
	INTEL_SNB_D_GT1_IDS(info), \
	INTEL_SNB_D_GT2_IDS(info)

#घोषणा INTEL_SNB_M_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0106, info)

#घोषणा INTEL_SNB_M_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0116, info), \
	INTEL_VGA_DEVICE(0x0126, info)

#घोषणा INTEL_SNB_M_IDS(info) \
	INTEL_SNB_M_GT1_IDS(info), \
	INTEL_SNB_M_GT2_IDS(info)

#घोषणा INTEL_IVB_M_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0156, info) /* GT1 mobile */

#घोषणा INTEL_IVB_M_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0166, info) /* GT2 mobile */

#घोषणा INTEL_IVB_M_IDS(info) \
	INTEL_IVB_M_GT1_IDS(info), \
	INTEL_IVB_M_GT2_IDS(info)

#घोषणा INTEL_IVB_D_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0152, info), /* GT1 desktop */ \
	INTEL_VGA_DEVICE(0x015a, info)  /* GT1 server */

#घोषणा INTEL_IVB_D_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0162, info), /* GT2 desktop */ \
	INTEL_VGA_DEVICE(0x016a, info)  /* GT2 server */

#घोषणा INTEL_IVB_D_IDS(info) \
	INTEL_IVB_D_GT1_IDS(info), \
	INTEL_IVB_D_GT2_IDS(info)

#घोषणा INTEL_IVB_Q_IDS(info) \
	INTEL_QUANTA_VGA_DEVICE(info) /* Quanta transcode */

#घोषणा INTEL_HSW_ULT_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0A02, info), /* ULT GT1 desktop */ \
	INTEL_VGA_DEVICE(0x0A06, info), /* ULT GT1 mobile */ \
	INTEL_VGA_DEVICE(0x0A0A, info), /* ULT GT1 server */ \
	INTEL_VGA_DEVICE(0x0A0B, info)  /* ULT GT1 reserved */

#घोषणा INTEL_HSW_ULX_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x0A0E, info) /* ULX GT1 mobile */

#घोषणा INTEL_HSW_GT1_IDS(info) \
	INTEL_HSW_ULT_GT1_IDS(info), \
	INTEL_HSW_ULX_GT1_IDS(info), \
	INTEL_VGA_DEVICE(0x0402, info), /* GT1 desktop */ \
	INTEL_VGA_DEVICE(0x0406, info), /* GT1 mobile */ \
	INTEL_VGA_DEVICE(0x040A, info), /* GT1 server */ \
	INTEL_VGA_DEVICE(0x040B, info), /* GT1 reserved */ \
	INTEL_VGA_DEVICE(0x040E, info), /* GT1 reserved */ \
	INTEL_VGA_DEVICE(0x0C02, info), /* SDV GT1 desktop */ \
	INTEL_VGA_DEVICE(0x0C06, info), /* SDV GT1 mobile */ \
	INTEL_VGA_DEVICE(0x0C0A, info), /* SDV GT1 server */ \
	INTEL_VGA_DEVICE(0x0C0B, info), /* SDV GT1 reserved */ \
	INTEL_VGA_DEVICE(0x0C0E, info), /* SDV GT1 reserved */ \
	INTEL_VGA_DEVICE(0x0D02, info), /* CRW GT1 desktop */ \
	INTEL_VGA_DEVICE(0x0D06, info), /* CRW GT1 mobile */	\
	INTEL_VGA_DEVICE(0x0D0A, info), /* CRW GT1 server */ \
	INTEL_VGA_DEVICE(0x0D0B, info), /* CRW GT1 reserved */ \
	INTEL_VGA_DEVICE(0x0D0E, info)  /* CRW GT1 reserved */

#घोषणा INTEL_HSW_ULT_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0A12, info), /* ULT GT2 desktop */ \
	INTEL_VGA_DEVICE(0x0A16, info), /* ULT GT2 mobile */	\
	INTEL_VGA_DEVICE(0x0A1A, info), /* ULT GT2 server */ \
	INTEL_VGA_DEVICE(0x0A1B, info)  /* ULT GT2 reserved */ \

#घोषणा INTEL_HSW_ULX_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x0A1E, info) /* ULX GT2 mobile */ \

#घोषणा INTEL_HSW_GT2_IDS(info) \
	INTEL_HSW_ULT_GT2_IDS(info), \
	INTEL_HSW_ULX_GT2_IDS(info), \
	INTEL_VGA_DEVICE(0x0412, info), /* GT2 desktop */ \
	INTEL_VGA_DEVICE(0x0416, info), /* GT2 mobile */ \
	INTEL_VGA_DEVICE(0x041A, info), /* GT2 server */ \
	INTEL_VGA_DEVICE(0x041B, info), /* GT2 reserved */ \
	INTEL_VGA_DEVICE(0x041E, info), /* GT2 reserved */ \
	INTEL_VGA_DEVICE(0x0C12, info), /* SDV GT2 desktop */ \
	INTEL_VGA_DEVICE(0x0C16, info), /* SDV GT2 mobile */ \
	INTEL_VGA_DEVICE(0x0C1A, info), /* SDV GT2 server */ \
	INTEL_VGA_DEVICE(0x0C1B, info), /* SDV GT2 reserved */ \
	INTEL_VGA_DEVICE(0x0C1E, info), /* SDV GT2 reserved */ \
	INTEL_VGA_DEVICE(0x0D12, info), /* CRW GT2 desktop */ \
	INTEL_VGA_DEVICE(0x0D16, info), /* CRW GT2 mobile */ \
	INTEL_VGA_DEVICE(0x0D1A, info), /* CRW GT2 server */ \
	INTEL_VGA_DEVICE(0x0D1B, info), /* CRW GT2 reserved */ \
	INTEL_VGA_DEVICE(0x0D1E, info)  /* CRW GT2 reserved */

#घोषणा INTEL_HSW_ULT_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x0A22, info), /* ULT GT3 desktop */ \
	INTEL_VGA_DEVICE(0x0A26, info), /* ULT GT3 mobile */ \
	INTEL_VGA_DEVICE(0x0A2A, info), /* ULT GT3 server */ \
	INTEL_VGA_DEVICE(0x0A2B, info), /* ULT GT3 reserved */ \
	INTEL_VGA_DEVICE(0x0A2E, info)  /* ULT GT3 reserved */

#घोषणा INTEL_HSW_GT3_IDS(info) \
	INTEL_HSW_ULT_GT3_IDS(info), \
	INTEL_VGA_DEVICE(0x0422, info), /* GT3 desktop */ \
	INTEL_VGA_DEVICE(0x0426, info), /* GT3 mobile */ \
	INTEL_VGA_DEVICE(0x042A, info), /* GT3 server */ \
	INTEL_VGA_DEVICE(0x042B, info), /* GT3 reserved */ \
	INTEL_VGA_DEVICE(0x042E, info), /* GT3 reserved */ \
	INTEL_VGA_DEVICE(0x0C22, info), /* SDV GT3 desktop */ \
	INTEL_VGA_DEVICE(0x0C26, info), /* SDV GT3 mobile */ \
	INTEL_VGA_DEVICE(0x0C2A, info), /* SDV GT3 server */ \
	INTEL_VGA_DEVICE(0x0C2B, info), /* SDV GT3 reserved */ \
	INTEL_VGA_DEVICE(0x0C2E, info), /* SDV GT3 reserved */ \
	INTEL_VGA_DEVICE(0x0D22, info), /* CRW GT3 desktop */ \
	INTEL_VGA_DEVICE(0x0D26, info), /* CRW GT3 mobile */ \
	INTEL_VGA_DEVICE(0x0D2A, info), /* CRW GT3 server */ \
	INTEL_VGA_DEVICE(0x0D2B, info), /* CRW GT3 reserved */ \
	INTEL_VGA_DEVICE(0x0D2E, info)  /* CRW GT3 reserved */

#घोषणा INTEL_HSW_IDS(info) \
	INTEL_HSW_GT1_IDS(info), \
	INTEL_HSW_GT2_IDS(info), \
	INTEL_HSW_GT3_IDS(info)

#घोषणा INTEL_VLV_IDS(info) \
	INTEL_VGA_DEVICE(0x0f30, info), \
	INTEL_VGA_DEVICE(0x0f31, info), \
	INTEL_VGA_DEVICE(0x0f32, info), \
	INTEL_VGA_DEVICE(0x0f33, info)

#घोषणा INTEL_BDW_ULT_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x1606, info), /* GT1 ULT */ \
	INTEL_VGA_DEVICE(0x160B, info)  /* GT1 Iris */

#घोषणा INTEL_BDW_ULX_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x160E, info) /* GT1 ULX */

#घोषणा INTEL_BDW_GT1_IDS(info) \
	INTEL_BDW_ULT_GT1_IDS(info), \
	INTEL_BDW_ULX_GT1_IDS(info), \
	INTEL_VGA_DEVICE(0x1602, info), /* GT1 ULT */ \
	INTEL_VGA_DEVICE(0x160A, info), /* GT1 Server */ \
	INTEL_VGA_DEVICE(0x160D, info)  /* GT1 Workstation */

#घोषणा INTEL_BDW_ULT_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x1616, info), /* GT2 ULT */ \
	INTEL_VGA_DEVICE(0x161B, info)  /* GT2 ULT */

#घोषणा INTEL_BDW_ULX_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x161E, info) /* GT2 ULX */

#घोषणा INTEL_BDW_GT2_IDS(info) \
	INTEL_BDW_ULT_GT2_IDS(info), \
	INTEL_BDW_ULX_GT2_IDS(info), \
	INTEL_VGA_DEVICE(0x1612, info), /* GT2 Halo */	\
	INTEL_VGA_DEVICE(0x161A, info), /* GT2 Server */ \
	INTEL_VGA_DEVICE(0x161D, info)  /* GT2 Workstation */

#घोषणा INTEL_BDW_ULT_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x1626, info), /* ULT */ \
	INTEL_VGA_DEVICE(0x162B, info)  /* Iris */ \

#घोषणा INTEL_BDW_ULX_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x162E, info)  /* ULX */

#घोषणा INTEL_BDW_GT3_IDS(info) \
	INTEL_BDW_ULT_GT3_IDS(info), \
	INTEL_BDW_ULX_GT3_IDS(info), \
	INTEL_VGA_DEVICE(0x1622, info), /* ULT */ \
	INTEL_VGA_DEVICE(0x162A, info), /* Server */ \
	INTEL_VGA_DEVICE(0x162D, info)  /* Workstation */

#घोषणा INTEL_BDW_ULT_RSVD_IDS(info) \
	INTEL_VGA_DEVICE(0x1636, info), /* ULT */ \
	INTEL_VGA_DEVICE(0x163B, info)  /* Iris */

#घोषणा INTEL_BDW_ULX_RSVD_IDS(info) \
	INTEL_VGA_DEVICE(0x163E, info) /* ULX */

#घोषणा INTEL_BDW_RSVD_IDS(info) \
	INTEL_BDW_ULT_RSVD_IDS(info), \
	INTEL_BDW_ULX_RSVD_IDS(info), \
	INTEL_VGA_DEVICE(0x1632, info), /* ULT */ \
	INTEL_VGA_DEVICE(0x163A, info), /* Server */ \
	INTEL_VGA_DEVICE(0x163D, info)  /* Workstation */

#घोषणा INTEL_BDW_IDS(info) \
	INTEL_BDW_GT1_IDS(info), \
	INTEL_BDW_GT2_IDS(info), \
	INTEL_BDW_GT3_IDS(info), \
	INTEL_BDW_RSVD_IDS(info)

#घोषणा INTEL_CHV_IDS(info) \
	INTEL_VGA_DEVICE(0x22b0, info), \
	INTEL_VGA_DEVICE(0x22b1, info), \
	INTEL_VGA_DEVICE(0x22b2, info), \
	INTEL_VGA_DEVICE(0x22b3, info)

#घोषणा INTEL_SKL_ULT_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x1906, info), /* ULT GT1 */ \
	INTEL_VGA_DEVICE(0x1913, info)  /* ULT GT1.5 */

#घोषणा INTEL_SKL_ULX_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x190E, info), /* ULX GT1 */ \
	INTEL_VGA_DEVICE(0x1915, info)  /* ULX GT1.5 */

#घोषणा INTEL_SKL_GT1_IDS(info)	\
	INTEL_SKL_ULT_GT1_IDS(info), \
	INTEL_SKL_ULX_GT1_IDS(info), \
	INTEL_VGA_DEVICE(0x1902, info), /* DT  GT1 */ \
	INTEL_VGA_DEVICE(0x190A, info), /* SRV GT1 */ \
	INTEL_VGA_DEVICE(0x190B, info), /* Halo GT1 */ \
	INTEL_VGA_DEVICE(0x1917, info)  /* DT  GT1.5 */

#घोषणा INTEL_SKL_ULT_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x1916, info), /* ULT GT2 */ \
	INTEL_VGA_DEVICE(0x1921, info)  /* ULT GT2F */

#घोषणा INTEL_SKL_ULX_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x191E, info) /* ULX GT2 */

#घोषणा INTEL_SKL_GT2_IDS(info)	\
	INTEL_SKL_ULT_GT2_IDS(info), \
	INTEL_SKL_ULX_GT2_IDS(info), \
	INTEL_VGA_DEVICE(0x1912, info), /* DT  GT2 */ \
	INTEL_VGA_DEVICE(0x191A, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x191B, info), /* Halo GT2 */ \
	INTEL_VGA_DEVICE(0x191D, info)  /* WKS GT2 */

#घोषणा INTEL_SKL_ULT_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x1923, info), /* ULT GT3 */ \
	INTEL_VGA_DEVICE(0x1926, info), /* ULT GT3e */ \
	INTEL_VGA_DEVICE(0x1927, info)  /* ULT GT3e */

#घोषणा INTEL_SKL_GT3_IDS(info) \
	INTEL_SKL_ULT_GT3_IDS(info), \
	INTEL_VGA_DEVICE(0x192A, info), /* SRV GT3 */ \
	INTEL_VGA_DEVICE(0x192B, info), /* Halo GT3e */ \
	INTEL_VGA_DEVICE(0x192D, info)  /* SRV GT3e */

#घोषणा INTEL_SKL_GT4_IDS(info) \
	INTEL_VGA_DEVICE(0x1932, info), /* DT GT4 */ \
	INTEL_VGA_DEVICE(0x193A, info), /* SRV GT4e */ \
	INTEL_VGA_DEVICE(0x193B, info), /* Halo GT4e */ \
	INTEL_VGA_DEVICE(0x193D, info) /* WKS GT4e */

#घोषणा INTEL_SKL_IDS(info)	 \
	INTEL_SKL_GT1_IDS(info), \
	INTEL_SKL_GT2_IDS(info), \
	INTEL_SKL_GT3_IDS(info), \
	INTEL_SKL_GT4_IDS(info)

#घोषणा INTEL_BXT_IDS(info) \
	INTEL_VGA_DEVICE(0x0A84, info), \
	INTEL_VGA_DEVICE(0x1A84, info), \
	INTEL_VGA_DEVICE(0x1A85, info), \
	INTEL_VGA_DEVICE(0x5A84, info), /* APL HD Graphics 505 */ \
	INTEL_VGA_DEVICE(0x5A85, info)  /* APL HD Graphics 500 */

#घोषणा INTEL_GLK_IDS(info) \
	INTEL_VGA_DEVICE(0x3184, info), \
	INTEL_VGA_DEVICE(0x3185, info)

#घोषणा INTEL_KBL_ULT_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x5906, info), /* ULT GT1 */ \
	INTEL_VGA_DEVICE(0x5913, info)  /* ULT GT1.5 */

#घोषणा INTEL_KBL_ULX_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x590E, info), /* ULX GT1 */ \
	INTEL_VGA_DEVICE(0x5915, info)  /* ULX GT1.5 */

#घोषणा INTEL_KBL_GT1_IDS(info)	\
	INTEL_KBL_ULT_GT1_IDS(info), \
	INTEL_KBL_ULX_GT1_IDS(info), \
	INTEL_VGA_DEVICE(0x5902, info), /* DT  GT1 */ \
	INTEL_VGA_DEVICE(0x5908, info), /* Halo GT1 */ \
	INTEL_VGA_DEVICE(0x590A, info), /* SRV GT1 */ \
	INTEL_VGA_DEVICE(0x590B, info) /* Halo GT1 */

#घोषणा INTEL_KBL_ULT_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x5916, info), /* ULT GT2 */ \
	INTEL_VGA_DEVICE(0x5921, info)  /* ULT GT2F */

#घोषणा INTEL_KBL_ULX_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x591E, info)  /* ULX GT2 */

#घोषणा INTEL_KBL_GT2_IDS(info)	\
	INTEL_KBL_ULT_GT2_IDS(info), \
	INTEL_KBL_ULX_GT2_IDS(info), \
	INTEL_VGA_DEVICE(0x5912, info), /* DT  GT2 */ \
	INTEL_VGA_DEVICE(0x5917, info), /* Mobile GT2 */ \
	INTEL_VGA_DEVICE(0x591A, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x591B, info), /* Halo GT2 */ \
	INTEL_VGA_DEVICE(0x591D, info) /* WKS GT2 */

#घोषणा INTEL_KBL_ULT_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x5926, info) /* ULT GT3 */

#घोषणा INTEL_KBL_GT3_IDS(info) \
	INTEL_KBL_ULT_GT3_IDS(info), \
	INTEL_VGA_DEVICE(0x5923, info), /* ULT GT3 */ \
	INTEL_VGA_DEVICE(0x5927, info) /* ULT GT3 */

#घोषणा INTEL_KBL_GT4_IDS(info) \
	INTEL_VGA_DEVICE(0x593B, info) /* Halo GT4 */

/* AML/KBL Y GT2 */
#घोषणा INTEL_AML_KBL_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x591C, info),  /* ULX GT2 */ \
	INTEL_VGA_DEVICE(0x87C0, info) /* ULX GT2 */

/* AML/CFL Y GT2 */
#घोषणा INTEL_AML_CFL_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x87CA, info)

/* CML GT1 */
#घोषणा INTEL_CML_GT1_IDS(info)	\
	INTEL_VGA_DEVICE(0x9BA2, info), \
	INTEL_VGA_DEVICE(0x9BA4, info), \
	INTEL_VGA_DEVICE(0x9BA5, info), \
	INTEL_VGA_DEVICE(0x9BA8, info)

#घोषणा INTEL_CML_U_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x9B21, info), \
	INTEL_VGA_DEVICE(0x9BAA, info), \
	INTEL_VGA_DEVICE(0x9BAC, info)

/* CML GT2 */
#घोषणा INTEL_CML_GT2_IDS(info)	\
	INTEL_VGA_DEVICE(0x9BC2, info), \
	INTEL_VGA_DEVICE(0x9BC4, info), \
	INTEL_VGA_DEVICE(0x9BC5, info), \
	INTEL_VGA_DEVICE(0x9BC6, info), \
	INTEL_VGA_DEVICE(0x9BC8, info), \
	INTEL_VGA_DEVICE(0x9BE6, info), \
	INTEL_VGA_DEVICE(0x9BF6, info)

#घोषणा INTEL_CML_U_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x9B41, info), \
	INTEL_VGA_DEVICE(0x9BCA, info), \
	INTEL_VGA_DEVICE(0x9BCC, info)

#घोषणा INTEL_KBL_IDS(info) \
	INTEL_KBL_GT1_IDS(info), \
	INTEL_KBL_GT2_IDS(info), \
	INTEL_KBL_GT3_IDS(info), \
	INTEL_KBL_GT4_IDS(info), \
	INTEL_AML_KBL_GT2_IDS(info)

/* CFL S */
#घोषणा INTEL_CFL_S_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x3E90, info), /* SRV GT1 */ \
	INTEL_VGA_DEVICE(0x3E93, info), /* SRV GT1 */ \
	INTEL_VGA_DEVICE(0x3E99, info)  /* SRV GT1 */

#घोषणा INTEL_CFL_S_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x3E91, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x3E92, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x3E96, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x3E98, info), /* SRV GT2 */ \
	INTEL_VGA_DEVICE(0x3E9A, info)  /* SRV GT2 */

/* CFL H */
#घोषणा INTEL_CFL_H_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x3E9C, info)

#घोषणा INTEL_CFL_H_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x3E94, info),  /* Halo GT2 */ \
	INTEL_VGA_DEVICE(0x3E9B, info) /* Halo GT2 */

/* CFL U GT2 */
#घोषणा INTEL_CFL_U_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x3EA9, info)

/* CFL U GT3 */
#घोषणा INTEL_CFL_U_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x3EA5, info), /* ULT GT3 */ \
	INTEL_VGA_DEVICE(0x3EA6, info), /* ULT GT3 */ \
	INTEL_VGA_DEVICE(0x3EA7, info), /* ULT GT3 */ \
	INTEL_VGA_DEVICE(0x3EA8, info)  /* ULT GT3 */

/* WHL/CFL U GT1 */
#घोषणा INTEL_WHL_U_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x3EA1, info), \
	INTEL_VGA_DEVICE(0x3EA4, info)

/* WHL/CFL U GT2 */
#घोषणा INTEL_WHL_U_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x3EA0, info), \
	INTEL_VGA_DEVICE(0x3EA3, info)

/* WHL/CFL U GT3 */
#घोषणा INTEL_WHL_U_GT3_IDS(info) \
	INTEL_VGA_DEVICE(0x3EA2, info)

#घोषणा INTEL_CFL_IDS(info)	   \
	INTEL_CFL_S_GT1_IDS(info), \
	INTEL_CFL_S_GT2_IDS(info), \
	INTEL_CFL_H_GT1_IDS(info), \
	INTEL_CFL_H_GT2_IDS(info), \
	INTEL_CFL_U_GT2_IDS(info), \
	INTEL_CFL_U_GT3_IDS(info), \
	INTEL_WHL_U_GT1_IDS(info), \
	INTEL_WHL_U_GT2_IDS(info), \
	INTEL_WHL_U_GT3_IDS(info), \
	INTEL_AML_CFL_GT2_IDS(info), \
	INTEL_CML_GT1_IDS(info), \
	INTEL_CML_GT2_IDS(info), \
	INTEL_CML_U_GT1_IDS(info), \
	INTEL_CML_U_GT2_IDS(info)

/* CNL */
#घोषणा INTEL_CNL_PORT_F_IDS(info) \
	INTEL_VGA_DEVICE(0x5A44, info), \
	INTEL_VGA_DEVICE(0x5A4C, info), \
	INTEL_VGA_DEVICE(0x5A54, info), \
	INTEL_VGA_DEVICE(0x5A5C, info)

#घोषणा INTEL_CNL_IDS(info) \
	INTEL_CNL_PORT_F_IDS(info), \
	INTEL_VGA_DEVICE(0x5A40, info), \
	INTEL_VGA_DEVICE(0x5A41, info), \
	INTEL_VGA_DEVICE(0x5A42, info), \
	INTEL_VGA_DEVICE(0x5A49, info), \
	INTEL_VGA_DEVICE(0x5A4A, info), \
	INTEL_VGA_DEVICE(0x5A50, info), \
	INTEL_VGA_DEVICE(0x5A51, info), \
	INTEL_VGA_DEVICE(0x5A52, info), \
	INTEL_VGA_DEVICE(0x5A59, info), \
	INTEL_VGA_DEVICE(0x5A5A, info)

/* ICL */
#घोषणा INTEL_ICL_PORT_F_IDS(info) \
	INTEL_VGA_DEVICE(0x8A50, info), \
	INTEL_VGA_DEVICE(0x8A52, info), \
	INTEL_VGA_DEVICE(0x8A53, info), \
	INTEL_VGA_DEVICE(0x8A54, info), \
	INTEL_VGA_DEVICE(0x8A56, info), \
	INTEL_VGA_DEVICE(0x8A57, info), \
	INTEL_VGA_DEVICE(0x8A58, info),	\
	INTEL_VGA_DEVICE(0x8A59, info),	\
	INTEL_VGA_DEVICE(0x8A5A, info), \
	INTEL_VGA_DEVICE(0x8A5B, info), \
	INTEL_VGA_DEVICE(0x8A5C, info), \
	INTEL_VGA_DEVICE(0x8A70, info), \
	INTEL_VGA_DEVICE(0x8A71, info)

#घोषणा INTEL_ICL_11_IDS(info) \
	INTEL_ICL_PORT_F_IDS(info), \
	INTEL_VGA_DEVICE(0x8A51, info), \
	INTEL_VGA_DEVICE(0x8A5D, info)

/* EHL */
#घोषणा INTEL_EHL_IDS(info) \
	INTEL_VGA_DEVICE(0x4541, info), \
	INTEL_VGA_DEVICE(0x4551, info), \
	INTEL_VGA_DEVICE(0x4555, info), \
	INTEL_VGA_DEVICE(0x4557, info), \
	INTEL_VGA_DEVICE(0x4571, info)

/* JSL */
#घोषणा INTEL_JSL_IDS(info) \
	INTEL_VGA_DEVICE(0x4E51, info), \
	INTEL_VGA_DEVICE(0x4E55, info), \
	INTEL_VGA_DEVICE(0x4E57, info), \
	INTEL_VGA_DEVICE(0x4E61, info), \
	INTEL_VGA_DEVICE(0x4E71, info)

/* TGL */
#घोषणा INTEL_TGL_12_GT1_IDS(info) \
	INTEL_VGA_DEVICE(0x9A60, info), \
	INTEL_VGA_DEVICE(0x9A68, info), \
	INTEL_VGA_DEVICE(0x9A70, info)

#घोषणा INTEL_TGL_12_GT2_IDS(info) \
	INTEL_VGA_DEVICE(0x9A40, info), \
	INTEL_VGA_DEVICE(0x9A49, info), \
	INTEL_VGA_DEVICE(0x9A59, info), \
	INTEL_VGA_DEVICE(0x9A78, info), \
	INTEL_VGA_DEVICE(0x9AC0, info), \
	INTEL_VGA_DEVICE(0x9AC9, info), \
	INTEL_VGA_DEVICE(0x9AD9, info), \
	INTEL_VGA_DEVICE(0x9AF8, info)

#घोषणा INTEL_TGL_12_IDS(info) \
	INTEL_TGL_12_GT1_IDS(info), \
	INTEL_TGL_12_GT2_IDS(info)

/* RKL */
#घोषणा INTEL_RKL_IDS(info) \
	INTEL_VGA_DEVICE(0x4C80, info), \
	INTEL_VGA_DEVICE(0x4C8A, info), \
	INTEL_VGA_DEVICE(0x4C8B, info), \
	INTEL_VGA_DEVICE(0x4C8C, info), \
	INTEL_VGA_DEVICE(0x4C90, info), \
	INTEL_VGA_DEVICE(0x4C9A, info)

/* DG1 */
#घोषणा INTEL_DG1_IDS(info) \
	INTEL_VGA_DEVICE(0x4905, info), \
	INTEL_VGA_DEVICE(0x4906, info), \
	INTEL_VGA_DEVICE(0x4907, info), \
	INTEL_VGA_DEVICE(0x4908, info)

/* ADL-S */
#घोषणा INTEL_ADLS_IDS(info) \
	INTEL_VGA_DEVICE(0x4680, info), \
	INTEL_VGA_DEVICE(0x4681, info), \
	INTEL_VGA_DEVICE(0x4682, info), \
	INTEL_VGA_DEVICE(0x4683, info), \
	INTEL_VGA_DEVICE(0x4690, info), \
	INTEL_VGA_DEVICE(0x4691, info), \
	INTEL_VGA_DEVICE(0x4692, info), \
	INTEL_VGA_DEVICE(0x4693, info)

#पूर्ण_अगर /* _I915_PCIIDS_H */
