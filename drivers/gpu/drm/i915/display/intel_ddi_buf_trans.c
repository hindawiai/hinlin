<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_ddi.h"
#समावेश "intel_ddi_buf_trans.h"
#समावेश "intel_display_types.h"

/* HDMI/DVI modes ignore everything but the last 2 items. So we share
 * them क्रम both DP and FDI transports, allowing those ports to
 * स्वतःmatically adapt to HDMI connections as well
 */
अटल स्थिर काष्ठा ddi_buf_trans hsw_ddi_translations_dp[] = अणु
	अणु 0x00FFFFFF, 0x0006000E, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x0005000A, 0x0 पूर्ण,
	अणु 0x00C30FFF, 0x00040006, 0x0 पूर्ण,
	अणु 0x80AAAFFF, 0x000B0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x0005000A, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x000C0004, 0x0 पूर्ण,
	अणु 0x80C30FFF, 0x000B0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x00040006, 0x0 पूर्ण,
	अणु 0x80D75FFF, 0x000B0000, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans hsw_ddi_translations_fdi[] = अणु
	अणु 0x00FFFFFF, 0x0007000E, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x000F000A, 0x0 पूर्ण,
	अणु 0x00C30FFF, 0x00060006, 0x0 पूर्ण,
	अणु 0x00AAAFFF, 0x001E0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x000F000A, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x00160004, 0x0 पूर्ण,
	अणु 0x00C30FFF, 0x001E0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x00060006, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x001E0000, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans hsw_ddi_translations_hdmi[] = अणु
					/* Idx	NT mV d	T mV d	db	*/
	अणु 0x00FFFFFF, 0x0006000E, 0x0 पूर्ण,/* 0:	400	400	0	*/
	अणु 0x00E79FFF, 0x000E000C, 0x0 पूर्ण,/* 1:	400	500	2	*/
	अणु 0x00D75FFF, 0x0005000A, 0x0 पूर्ण,/* 2:	400	600	3.5	*/
	अणु 0x00FFFFFF, 0x0005000A, 0x0 पूर्ण,/* 3:	600	600	0	*/
	अणु 0x00E79FFF, 0x001D0007, 0x0 पूर्ण,/* 4:	600	750	2	*/
	अणु 0x00D75FFF, 0x000C0004, 0x0 पूर्ण,/* 5:	600	900	3.5	*/
	अणु 0x00FFFFFF, 0x00040006, 0x0 पूर्ण,/* 6:	800	800	0	*/
	अणु 0x80E79FFF, 0x00030002, 0x0 पूर्ण,/* 7:	800	1000	2	*/
	अणु 0x00FFFFFF, 0x00140005, 0x0 पूर्ण,/* 8:	850	850	0	*/
	अणु 0x00FFFFFF, 0x000C0004, 0x0 पूर्ण,/* 9:	900	900	0	*/
	अणु 0x00FFFFFF, 0x001C0003, 0x0 पूर्ण,/* 10:	950	950	0	*/
	अणु 0x80FFFFFF, 0x00030002, 0x0 पूर्ण,/* 11:	1000	1000	0	*/
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans bdw_ddi_translations_edp[] = अणु
	अणु 0x00FFFFFF, 0x00000012, 0x0 पूर्ण,
	अणु 0x00EBAFFF, 0x00020011, 0x0 पूर्ण,
	अणु 0x00C71FFF, 0x0006000F, 0x0 पूर्ण,
	अणु 0x00AAAFFF, 0x000E000A, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x00020011, 0x0 पूर्ण,
	अणु 0x00DB6FFF, 0x0005000F, 0x0 पूर्ण,
	अणु 0x00BEEFFF, 0x000A000C, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x0005000F, 0x0 पूर्ण,
	अणु 0x00DB6FFF, 0x000A000C, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans bdw_ddi_translations_dp[] = अणु
	अणु 0x00FFFFFF, 0x0007000E, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x000E000A, 0x0 पूर्ण,
	अणु 0x00BEFFFF, 0x00140006, 0x0 पूर्ण,
	अणु 0x80B2CFFF, 0x001B0002, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x000E000A, 0x0 पूर्ण,
	अणु 0x00DB6FFF, 0x00160005, 0x0 पूर्ण,
	अणु 0x80C71FFF, 0x001A0002, 0x0 पूर्ण,
	अणु 0x00F7DFFF, 0x00180004, 0x0 पूर्ण,
	अणु 0x80D75FFF, 0x001B0002, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans bdw_ddi_translations_fdi[] = अणु
	अणु 0x00FFFFFF, 0x0001000E, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x0004000A, 0x0 पूर्ण,
	अणु 0x00C30FFF, 0x00070006, 0x0 पूर्ण,
	अणु 0x00AAAFFF, 0x000C0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x0004000A, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x00090004, 0x0 पूर्ण,
	अणु 0x00C30FFF, 0x000C0000, 0x0 पूर्ण,
	अणु 0x00FFFFFF, 0x00070006, 0x0 पूर्ण,
	अणु 0x00D75FFF, 0x000C0000, 0x0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ddi_buf_trans bdw_ddi_translations_hdmi[] = अणु
					/* Idx	NT mV d	T mV df	db	*/
	अणु 0x00FFFFFF, 0x0007000E, 0x0 पूर्ण,/* 0:	400	400	0	*/
	अणु 0x00D75FFF, 0x000E000A, 0x0 पूर्ण,/* 1:	400	600	3.5	*/
	अणु 0x00BEFFFF, 0x00140006, 0x0 पूर्ण,/* 2:	400	800	6	*/
	अणु 0x00FFFFFF, 0x0009000D, 0x0 पूर्ण,/* 3:	450	450	0	*/
	अणु 0x00FFFFFF, 0x000E000A, 0x0 पूर्ण,/* 4:	600	600	0	*/
	अणु 0x00D7FFFF, 0x00140006, 0x0 पूर्ण,/* 5:	600	800	2.5	*/
	अणु 0x80CB2FFF, 0x001B0002, 0x0 पूर्ण,/* 6:	600	1000	4.5	*/
	अणु 0x00FFFFFF, 0x00140006, 0x0 पूर्ण,/* 7:	800	800	0	*/
	अणु 0x80E79FFF, 0x001B0002, 0x0 पूर्ण,/* 8:	800	1000	2	*/
	अणु 0x80FFFFFF, 0x001B0002, 0x0 पूर्ण,/* 9:	1000	1000	0	*/
पूर्ण;

/* Skylake H and S */
अटल स्थिर काष्ठा ddi_buf_trans skl_ddi_translations_dp[] = अणु
	अणु 0x00002016, 0x000000A0, 0x0 पूर्ण,
	अणु 0x00005012, 0x0000009B, 0x0 पूर्ण,
	अणु 0x00007011, 0x00000088, 0x0 पूर्ण,
	अणु 0x80009010, 0x000000C0, 0x1 पूर्ण,
	अणु 0x00002016, 0x0000009B, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x1 पूर्ण,
	अणु 0x00002016, 0x000000DF, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x1 पूर्ण,
पूर्ण;

/* Skylake U */
अटल स्थिर काष्ठा ddi_buf_trans skl_u_ddi_translations_dp[] = अणु
	अणु 0x0000201B, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000CD, 0x1 पूर्ण,
	अणु 0x80009010, 0x000000C0, 0x1 पूर्ण,
	अणु 0x0000201B, 0x0000009D, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x1 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x1 पूर्ण,
	अणु 0x00002016, 0x00000088, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x1 पूर्ण,
पूर्ण;

/* Skylake Y */
अटल स्थिर काष्ठा ddi_buf_trans skl_y_ddi_translations_dp[] = अणु
	अणु 0x00000018, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000CD, 0x3 पूर्ण,
	अणु 0x80009010, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00000018, 0x0000009D, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00000018, 0x00000088, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
पूर्ण;

/* Kabylake H and S */
अटल स्थिर काष्ठा ddi_buf_trans kbl_ddi_translations_dp[] = अणु
	अणु 0x00002016, 0x000000A0, 0x0 पूर्ण,
	अणु 0x00005012, 0x0000009B, 0x0 पूर्ण,
	अणु 0x00007011, 0x00000088, 0x0 पूर्ण,
	अणु 0x80009010, 0x000000C0, 0x1 पूर्ण,
	अणु 0x00002016, 0x0000009B, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x1 पूर्ण,
	अणु 0x00002016, 0x00000097, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x1 पूर्ण,
पूर्ण;

/* Kabylake U */
अटल स्थिर काष्ठा ddi_buf_trans kbl_u_ddi_translations_dp[] = अणु
	अणु 0x0000201B, 0x000000A1, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000CD, 0x3 पूर्ण,
	अणु 0x80009010, 0x000000C0, 0x3 पूर्ण,
	अणु 0x0000201B, 0x0000009D, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00002016, 0x0000004F, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
पूर्ण;

/* Kabylake Y */
अटल स्थिर काष्ठा ddi_buf_trans kbl_y_ddi_translations_dp[] = अणु
	अणु 0x00001017, 0x000000A1, 0x0 पूर्ण,
	अणु 0x00005012, 0x00000088, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000CD, 0x3 पूर्ण,
	अणु 0x8000800F, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00001017, 0x0000009D, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
	अणु 0x80007011, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00001017, 0x0000004C, 0x0 पूर्ण,
	अणु 0x80005012, 0x000000C0, 0x3 पूर्ण,
पूर्ण;

/*
 * Skylake/Kabylake H and S
 * eDP 1.4 low vswing translation parameters
 */
अटल स्थिर काष्ठा ddi_buf_trans skl_ddi_translations_edp[] = अणु
	अणु 0x00000018, 0x000000A8, 0x0 पूर्ण,
	अणु 0x00004013, 0x000000A9, 0x0 पूर्ण,
	अणु 0x00007011, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00009010, 0x0000009C, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000A9, 0x0 पूर्ण,
	अणु 0x00006013, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00007011, 0x000000A6, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000AB, 0x0 पूर्ण,
	अणु 0x00007013, 0x0000009F, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000DF, 0x0 पूर्ण,
पूर्ण;

/*
 * Skylake/Kabylake U
 * eDP 1.4 low vswing translation parameters
 */
अटल स्थिर काष्ठा ddi_buf_trans skl_u_ddi_translations_edp[] = अणु
	अणु 0x00000018, 0x000000A8, 0x0 पूर्ण,
	अणु 0x00004013, 0x000000A9, 0x0 पूर्ण,
	अणु 0x00007011, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00009010, 0x0000009C, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000A9, 0x0 पूर्ण,
	अणु 0x00006013, 0x000000A2, 0x0 पूर्ण,
	अणु 0x00007011, 0x000000A6, 0x0 पूर्ण,
	अणु 0x00002016, 0x000000AB, 0x0 पूर्ण,
	अणु 0x00005013, 0x0000009F, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000DF, 0x0 पूर्ण,
पूर्ण;

/*
 * Skylake/Kabylake Y
 * eDP 1.4 low vswing translation parameters
 */
अटल स्थिर काष्ठा ddi_buf_trans skl_y_ddi_translations_edp[] = अणु
	अणु 0x00000018, 0x000000A8, 0x0 पूर्ण,
	अणु 0x00004013, 0x000000AB, 0x0 पूर्ण,
	अणु 0x00007011, 0x000000A4, 0x0 पूर्ण,
	अणु 0x00009010, 0x000000DF, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000AA, 0x0 पूर्ण,
	अणु 0x00006013, 0x000000A4, 0x0 पूर्ण,
	अणु 0x00007011, 0x0000009D, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000A0, 0x0 पूर्ण,
	अणु 0x00006012, 0x000000DF, 0x0 पूर्ण,
	अणु 0x00000018, 0x0000008A, 0x0 पूर्ण,
पूर्ण;

/* Skylake/Kabylake U, H and S */
अटल स्थिर काष्ठा ddi_buf_trans skl_ddi_translations_hdmi[] = अणु
	अणु 0x00000018, 0x000000AC, 0x0 पूर्ण,
	अणु 0x00005012, 0x0000009D, 0x0 पूर्ण,
	अणु 0x00007011, 0x00000088, 0x0 पूर्ण,
	अणु 0x00000018, 0x000000A1, 0x0 पूर्ण,
	अणु 0x00000018, 0x00000098, 0x0 पूर्ण,
	अणु 0x00004013, 0x00000088, 0x0 पूर्ण,
	अणु 0x80006012, 0x000000CD, 0x1 पूर्ण,
	अणु 0x00000018, 0x000000DF, 0x0 पूर्ण,
	अणु 0x80003015, 0x000000CD, 0x1 पूर्ण,	/* Default */
	अणु 0x80003015, 0x000000C0, 0x1 पूर्ण,
	अणु 0x80000018, 0x000000C0, 0x1 पूर्ण,
पूर्ण;

/* Skylake/Kabylake Y */
अटल स्थिर काष्ठा ddi_buf_trans skl_y_ddi_translations_hdmi[] = अणु
	अणु 0x00000018, 0x000000A1, 0x0 पूर्ण,
	अणु 0x00005012, 0x000000DF, 0x0 पूर्ण,
	अणु 0x80007011, 0x000000CB, 0x3 पूर्ण,
	अणु 0x00000018, 0x000000A4, 0x0 पूर्ण,
	अणु 0x00000018, 0x0000009D, 0x0 पूर्ण,
	अणु 0x00004013, 0x00000080, 0x0 पूर्ण,
	अणु 0x80006013, 0x000000C0, 0x3 पूर्ण,
	अणु 0x00000018, 0x0000008A, 0x0 पूर्ण,
	अणु 0x80003015, 0x000000C0, 0x3 पूर्ण,	/* Default */
	अणु 0x80003015, 0x000000C0, 0x3 पूर्ण,
	अणु 0x80000018, 0x000000C0, 0x3 पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा bxt_ddi_buf_trans bxt_ddi_translations_dp[] = अणु
					/* Idx	NT mV dअगरf	db  */
	अणु 52,  0x9A, 0, 128, पूर्ण,	/* 0:	400		0   */
	अणु 78,  0x9A, 0, 85,  पूर्ण,	/* 1:	400		3.5 */
	अणु 104, 0x9A, 0, 64,  पूर्ण,	/* 2:	400		6   */
	अणु 154, 0x9A, 0, 43,  पूर्ण,	/* 3:	400		9.5 */
	अणु 77,  0x9A, 0, 128, पूर्ण,	/* 4:	600		0   */
	अणु 116, 0x9A, 0, 85,  पूर्ण,	/* 5:	600		3.5 */
	अणु 154, 0x9A, 0, 64,  पूर्ण,	/* 6:	600		6   */
	अणु 102, 0x9A, 0, 128, पूर्ण,	/* 7:	800		0   */
	अणु 154, 0x9A, 0, 85,  पूर्ण,	/* 8:	800		3.5 */
	अणु 154, 0x9A, 1, 128, पूर्ण,	/* 9:	1200		0   */
पूर्ण;

अटल स्थिर काष्ठा bxt_ddi_buf_trans bxt_ddi_translations_edp[] = अणु
					/* Idx	NT mV dअगरf	db  */
	अणु 26, 0, 0, 128, पूर्ण,	/* 0:	200		0   */
	अणु 38, 0, 0, 112, पूर्ण,	/* 1:	200		1.5 */
	अणु 48, 0, 0, 96,  पूर्ण,	/* 2:	200		4   */
	अणु 54, 0, 0, 69,  पूर्ण,	/* 3:	200		6   */
	अणु 32, 0, 0, 128, पूर्ण,	/* 4:	250		0   */
	अणु 48, 0, 0, 104, पूर्ण,	/* 5:	250		1.5 */
	अणु 54, 0, 0, 85,  पूर्ण,	/* 6:	250		4   */
	अणु 43, 0, 0, 128, पूर्ण,	/* 7:	300		0   */
	अणु 54, 0, 0, 101, पूर्ण,	/* 8:	300		1.5 */
	अणु 48, 0, 0, 128, पूर्ण,	/* 9:	300		0   */
पूर्ण;

/* BSpec has 2 recommended values - entries 0 and 8.
 * Using the entry with higher vswing.
 */
अटल स्थिर काष्ठा bxt_ddi_buf_trans bxt_ddi_translations_hdmi[] = अणु
					/* Idx	NT mV dअगरf	db  */
	अणु 52,  0x9A, 0, 128, पूर्ण,	/* 0:	400		0   */
	अणु 52,  0x9A, 0, 85,  पूर्ण,	/* 1:	400		3.5 */
	अणु 52,  0x9A, 0, 64,  पूर्ण,	/* 2:	400		6   */
	अणु 42,  0x9A, 0, 43,  पूर्ण,	/* 3:	400		9.5 */
	अणु 77,  0x9A, 0, 128, पूर्ण,	/* 4:	600		0   */
	अणु 77,  0x9A, 0, 85,  पूर्ण,	/* 5:	600		3.5 */
	अणु 77,  0x9A, 0, 64,  पूर्ण,	/* 6:	600		6   */
	अणु 102, 0x9A, 0, 128, पूर्ण,	/* 7:	800		0   */
	अणु 102, 0x9A, 0, 85,  पूर्ण,	/* 8:	800		3.5 */
	अणु 154, 0x9A, 1, 128, पूर्ण,	/* 9:	1200		0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.85V क्रम DP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_dp_0_85V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x5D, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x6A, 0x38, 0x00, 0x07 पूर्ण,	/* 350   500      3.1   */
	अणु 0xB, 0x7A, 0x32, 0x00, 0x0D पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7C, 0x2D, 0x00, 0x12 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x69, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xB, 0x7A, 0x36, 0x00, 0x09 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7C, 0x30, 0x00, 0x0F पूर्ण,	/* 500   900      5.1   */
	अणु 0xB, 0x7D, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   725      0.9   */
	अणु 0x6, 0x7C, 0x34, 0x00, 0x0B पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7B, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.85V क्रम HDMI */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_hdmi_0_85V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x60, 0x3F, 0x00, 0x00 पूर्ण,	/* 450   450      0.0   */
	अणु 0xB, 0x73, 0x36, 0x00, 0x09 पूर्ण,	/* 450   650      3.2   */
	अणु 0x6, 0x7F, 0x31, 0x00, 0x0E पूर्ण,	/* 450   850      5.5   */
	अणु 0xB, 0x73, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   650      0.0   */
	अणु 0x6, 0x7F, 0x37, 0x00, 0x08 पूर्ण,	/* 650   850      2.3   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 850   850      0.0   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   850      3.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.85V क्रम eDP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_edp_0_85V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x66, 0x3A, 0x00, 0x05 पूर्ण,	/* 384   500      2.3   */
	अणु 0x0, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 153   200      2.3   */
	अणु 0x8, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 192   250      2.3   */
	अणु 0x1, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 230   300      2.3   */
	अणु 0x9, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 269   350      2.3   */
	अणु 0xA, 0x66, 0x3C, 0x00, 0x03 पूर्ण,	/* 446   500      1.0   */
	अणु 0xB, 0x70, 0x3C, 0x00, 0x03 पूर्ण,	/* 460   600      2.3   */
	अणु 0xC, 0x75, 0x3C, 0x00, 0x03 पूर्ण,	/* 537   700      2.3   */
	अणु 0x2, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.95V क्रम DP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_dp_0_95V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x5D, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x6A, 0x38, 0x00, 0x07 पूर्ण,	/* 350   500      3.1   */
	अणु 0xB, 0x7A, 0x32, 0x00, 0x0D पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7C, 0x2D, 0x00, 0x12 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x69, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xB, 0x7A, 0x36, 0x00, 0x09 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7C, 0x30, 0x00, 0x0F पूर्ण,	/* 500   900      5.1   */
	अणु 0xB, 0x7D, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   725      0.9   */
	अणु 0x6, 0x7C, 0x34, 0x00, 0x0B पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7B, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.95V क्रम HDMI */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_hdmi_0_95V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x5C, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
	अणु 0xB, 0x69, 0x37, 0x00, 0x08 पूर्ण,	/* 400   600      3.5   */
	अणु 0x5, 0x76, 0x31, 0x00, 0x0E पूर्ण,	/* 400   800      6.0   */
	अणु 0xA, 0x5E, 0x3F, 0x00, 0x00 पूर्ण,	/* 450   450      0.0   */
	अणु 0xB, 0x69, 0x3F, 0x00, 0x00 पूर्ण,	/* 600   600      0.0   */
	अणु 0xB, 0x79, 0x35, 0x00, 0x0A पूर्ण,	/* 600   850      3.0   */
	अणु 0x6, 0x7D, 0x32, 0x00, 0x0D पूर्ण,	/* 600   1000     4.4   */
	अणु 0x5, 0x76, 0x3F, 0x00, 0x00 पूर्ण,	/* 800   800      0.0   */
	अणु 0x6, 0x7D, 0x39, 0x00, 0x06 पूर्ण,	/* 800   1000     1.9   */
	अणु 0x6, 0x7F, 0x39, 0x00, 0x06 पूर्ण,	/* 850   1050     1.8   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1050  1050     0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 0.95V क्रम eDP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_edp_0_95V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x61, 0x3A, 0x00, 0x05 पूर्ण,	/* 384   500      2.3   */
	अणु 0x0, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 153   200      2.3   */
	अणु 0x8, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 192   250      2.3   */
	अणु 0x1, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 230   300      2.3   */
	अणु 0x9, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 269   350      2.3   */
	अणु 0xA, 0x61, 0x3C, 0x00, 0x03 पूर्ण,	/* 446   500      1.0   */
	अणु 0xB, 0x68, 0x39, 0x00, 0x06 पूर्ण,	/* 460   600      2.3   */
	अणु 0xC, 0x6E, 0x39, 0x00, 0x06 पूर्ण,	/* 537   700      2.3   */
	अणु 0x4, 0x7F, 0x3A, 0x00, 0x05 पूर्ण,	/* 460   600      2.3   */
	अणु 0x2, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 1.05V क्रम DP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_dp_1_05V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x58, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
	अणु 0xB, 0x64, 0x37, 0x00, 0x08 पूर्ण,	/* 400   600      3.5   */
	अणु 0x5, 0x70, 0x31, 0x00, 0x0E पूर्ण,	/* 400   800      6.0   */
	अणु 0x6, 0x7F, 0x2C, 0x00, 0x13 पूर्ण,	/* 400   1050     8.4   */
	अणु 0xB, 0x64, 0x3F, 0x00, 0x00 पूर्ण,	/* 600   600      0.0   */
	अणु 0x5, 0x73, 0x35, 0x00, 0x0A पूर्ण,	/* 600   850      3.0   */
	अणु 0x6, 0x7F, 0x30, 0x00, 0x0F पूर्ण,	/* 550   1050     5.6   */
	अणु 0x5, 0x76, 0x3E, 0x00, 0x01 पूर्ण,	/* 850   900      0.5   */
	अणु 0x6, 0x7F, 0x36, 0x00, 0x09 पूर्ण,	/* 750   1050     2.9   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1050  1050     0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 1.05V क्रम HDMI */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_hdmi_1_05V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x58, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
	अणु 0xB, 0x64, 0x37, 0x00, 0x08 पूर्ण,	/* 400   600      3.5   */
	अणु 0x5, 0x70, 0x31, 0x00, 0x0E पूर्ण,	/* 400   800      6.0   */
	अणु 0xA, 0x5B, 0x3F, 0x00, 0x00 पूर्ण,	/* 450   450      0.0   */
	अणु 0xB, 0x64, 0x3F, 0x00, 0x00 पूर्ण,	/* 600   600      0.0   */
	अणु 0x5, 0x73, 0x35, 0x00, 0x0A पूर्ण,	/* 600   850      3.0   */
	अणु 0x6, 0x7C, 0x32, 0x00, 0x0D पूर्ण,	/* 600   1000     4.4   */
	अणु 0x5, 0x70, 0x3F, 0x00, 0x00 पूर्ण,	/* 800   800      0.0   */
	अणु 0x6, 0x7C, 0x39, 0x00, 0x06 पूर्ण,	/* 800   1000     1.9   */
	अणु 0x6, 0x7F, 0x39, 0x00, 0x06 पूर्ण,	/* 850   1050     1.8   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1050  1050     0.0   */
पूर्ण;

/* Voltage Swing Programming क्रम VccIO 1.05V क्रम eDP */
अटल स्थिर काष्ठा cnl_ddi_buf_trans cnl_ddi_translations_edp_1_05V[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x5E, 0x3A, 0x00, 0x05 पूर्ण,	/* 384   500      2.3   */
	अणु 0x0, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 153   200      2.3   */
	अणु 0x8, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 192   250      2.3   */
	अणु 0x1, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 230   300      2.3   */
	अणु 0x9, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 269   350      2.3   */
	अणु 0xA, 0x5E, 0x3C, 0x00, 0x03 पूर्ण,	/* 446   500      1.0   */
	अणु 0xB, 0x64, 0x39, 0x00, 0x06 पूर्ण,	/* 460   600      2.3   */
	अणु 0xE, 0x6A, 0x39, 0x00, 0x06 पूर्ण,	/* 537   700      2.3   */
	अणु 0x2, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 400   400      0.0   */
पूर्ण;

/* icl_combo_phy_ddi_translations */
अटल स्थिर काष्ठा cnl_ddi_buf_trans icl_combo_phy_ddi_translations_dp_hbr2[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x37, 0x00, 0x08 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x71, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2B, 0x00, 0x14 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x4C, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x73, 0x34, 0x00, 0x0B पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x6C, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans icl_combo_phy_ddi_translations_edp_hbr2[] = अणु
						/* NT mV Trans mV db    */
	अणु 0x0, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 200   200      0.0   */
	अणु 0x8, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 200   250      1.9   */
	अणु 0x1, 0x7F, 0x33, 0x00, 0x0C पूर्ण,	/* 200   300      3.5   */
	अणु 0x9, 0x7F, 0x31, 0x00, 0x0E पूर्ण,	/* 200   350      4.9   */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 250   250      0.0   */
	अणु 0x1, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 250   300      1.6   */
	अणु 0x9, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 250   350      2.9   */
	अणु 0x1, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 300   300      0.0   */
	अणु 0x9, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 300   350      1.3   */
	अणु 0x9, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans icl_combo_phy_ddi_translations_edp_hbr3[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x37, 0x00, 0x08 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x71, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2B, 0x00, 0x14 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x4C, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x73, 0x34, 0x00, 0x0B पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x6C, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans icl_combo_phy_ddi_translations_hdmi[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x60, 0x3F, 0x00, 0x00 पूर्ण,	/* 450   450      0.0   */
	अणु 0xB, 0x73, 0x36, 0x00, 0x09 पूर्ण,	/* 450   650      3.2   */
	अणु 0x6, 0x7F, 0x31, 0x00, 0x0E पूर्ण,	/* 450   850      5.5   */
	अणु 0xB, 0x73, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   650      0.0   ALS */
	अणु 0x6, 0x7F, 0x37, 0x00, 0x08 पूर्ण,	/* 650   850      2.3   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 850   850      0.0   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   850      3.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans ehl_combo_phy_ddi_translations_dp[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x33, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x47, 0x36, 0x00, 0x09 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x64, 0x34, 0x00, 0x0B पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x30, 0x00, 0x0F पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x46, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x64, 0x38, 0x00, 0x07 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x32, 0x00, 0x0D पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x61, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x38, 0x00, 0x07 पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans jsl_combo_phy_ddi_translations_edp_hbr[] = अणु
						/* NT mV Trans mV db    */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 200   200      0.0   */
	अणु 0x8, 0x7F, 0x38, 0x00, 0x07 पूर्ण,        /* 200   250      1.9   */
	अणु 0x1, 0x7F, 0x33, 0x00, 0x0C पूर्ण,        /* 200   300      3.5   */
	अणु 0xA, 0x35, 0x36, 0x00, 0x09 पूर्ण,        /* 200   350      4.9   */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 250   250      0.0   */
	अणु 0x1, 0x7F, 0x38, 0x00, 0x07 पूर्ण,        /* 250   300      1.6   */
	अणु 0xA, 0x35, 0x35, 0x00, 0x0A पूर्ण,        /* 250   350      2.9   */
	अणु 0x1, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 300   300      0.0   */
	अणु 0xA, 0x35, 0x38, 0x00, 0x07 पूर्ण,        /* 300   350      1.3   */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,        /* 350   350      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans jsl_combo_phy_ddi_translations_edp_hbr2[] = अणु
						/* NT mV Trans mV db    */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 200   200      0.0   */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 200   250      1.9   */
	अणु 0x1, 0x7F, 0x3D, 0x00, 0x02 पूर्ण,        /* 200   300      3.5   */
	अणु 0xA, 0x35, 0x38, 0x00, 0x07 पूर्ण,        /* 200   350      4.9   */
	अणु 0x8, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 250   250      0.0   */
	अणु 0x1, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 250   300      1.6   */
	अणु 0xA, 0x35, 0x3A, 0x00, 0x05 पूर्ण,        /* 250   350      2.9   */
	अणु 0x1, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,        /* 300   300      0.0   */
	अणु 0xA, 0x35, 0x38, 0x00, 0x07 पूर्ण,        /* 300   350      1.3   */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,        /* 350   350      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans dg1_combo_phy_ddi_translations_dp_rbr_hbr[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x32, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x48, 0x35, 0x00, 0x0A पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x63, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2C, 0x00, 0x13 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x43, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x60, 0x36, 0x00, 0x09 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x30, 0x00, 0x0F पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x60, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x37, 0x00, 0x08 पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans dg1_combo_phy_ddi_translations_dp_hbr2_hbr3[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x32, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x48, 0x35, 0x00, 0x0A पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x63, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2C, 0x00, 0x13 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x43, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x60, 0x36, 0x00, 0x09 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x30, 0x00, 0x0F पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x58, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा icl_mg_phy_ddi_buf_trans icl_mg_phy_ddi_translations_rbr_hbr[] = अणु
				/* Voltage swing  pre-emphasis */
	अणु 0x18, 0x00, 0x00 पूर्ण,	/* 0              0   */
	अणु 0x1D, 0x00, 0x05 पूर्ण,	/* 0              1   */
	अणु 0x24, 0x00, 0x0C पूर्ण,	/* 0              2   */
	अणु 0x2B, 0x00, 0x14 पूर्ण,	/* 0              3   */
	अणु 0x21, 0x00, 0x00 पूर्ण,	/* 1              0   */
	अणु 0x2B, 0x00, 0x08 पूर्ण,	/* 1              1   */
	अणु 0x30, 0x00, 0x0F पूर्ण,	/* 1              2   */
	अणु 0x31, 0x00, 0x03 पूर्ण,	/* 2              0   */
	अणु 0x34, 0x00, 0x0B पूर्ण,	/* 2              1   */
	अणु 0x3F, 0x00, 0x00 पूर्ण,	/* 3              0   */
पूर्ण;

अटल स्थिर काष्ठा icl_mg_phy_ddi_buf_trans icl_mg_phy_ddi_translations_hbr2_hbr3[] = अणु
				/* Voltage swing  pre-emphasis */
	अणु 0x18, 0x00, 0x00 पूर्ण,	/* 0              0   */
	अणु 0x1D, 0x00, 0x05 पूर्ण,	/* 0              1   */
	अणु 0x24, 0x00, 0x0C पूर्ण,	/* 0              2   */
	अणु 0x2B, 0x00, 0x14 पूर्ण,	/* 0              3   */
	अणु 0x26, 0x00, 0x00 पूर्ण,	/* 1              0   */
	अणु 0x2C, 0x00, 0x07 पूर्ण,	/* 1              1   */
	अणु 0x33, 0x00, 0x0C पूर्ण,	/* 1              2   */
	अणु 0x2E, 0x00, 0x00 पूर्ण,	/* 2              0   */
	अणु 0x36, 0x00, 0x09 पूर्ण,	/* 2              1   */
	अणु 0x3F, 0x00, 0x00 पूर्ण,	/* 3              0   */
पूर्ण;

अटल स्थिर काष्ठा icl_mg_phy_ddi_buf_trans icl_mg_phy_ddi_translations_hdmi[] = अणु
				/* HDMI Preset	VS	Pre-emph */
	अणु 0x1A, 0x0, 0x0 पूर्ण,	/* 1		400mV	0dB */
	अणु 0x20, 0x0, 0x0 पूर्ण,	/* 2		500mV	0dB */
	अणु 0x29, 0x0, 0x0 पूर्ण,	/* 3		650mV	0dB */
	अणु 0x32, 0x0, 0x0 पूर्ण,	/* 4		800mV	0dB */
	अणु 0x3F, 0x0, 0x0 पूर्ण,	/* 5		1000mV	0dB */
	अणु 0x3A, 0x0, 0x5 पूर्ण,	/* 6		Full	-1.5 dB */
	अणु 0x39, 0x0, 0x6 पूर्ण,	/* 7		Full	-1.8 dB */
	अणु 0x38, 0x0, 0x7 पूर्ण,	/* 8		Full	-2 dB */
	अणु 0x37, 0x0, 0x8 पूर्ण,	/* 9		Full	-2.5 dB */
	अणु 0x36, 0x0, 0x9 पूर्ण,	/* 10		Full	-3 dB */
पूर्ण;

अटल स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans tgl_dkl_phy_dp_ddi_trans[] = अणु
				/* VS	pre-emp	Non-trans mV	Pre-emph dB */
	अणु 0x7, 0x0, 0x00 पूर्ण,	/* 0	0	400mV		0 dB */
	अणु 0x5, 0x0, 0x05 पूर्ण,	/* 0	1	400mV		3.5 dB */
	अणु 0x2, 0x0, 0x0B पूर्ण,	/* 0	2	400mV		6 dB */
	अणु 0x0, 0x0, 0x18 पूर्ण,	/* 0	3	400mV		9.5 dB */
	अणु 0x5, 0x0, 0x00 पूर्ण,	/* 1	0	600mV		0 dB */
	अणु 0x2, 0x0, 0x08 पूर्ण,	/* 1	1	600mV		3.5 dB */
	अणु 0x0, 0x0, 0x14 पूर्ण,	/* 1	2	600mV		6 dB */
	अणु 0x2, 0x0, 0x00 पूर्ण,	/* 2	0	800mV		0 dB */
	अणु 0x0, 0x0, 0x0B पूर्ण,	/* 2	1	800mV		3.5 dB */
	अणु 0x0, 0x0, 0x00 पूर्ण,	/* 3	0	1200mV		0 dB HDMI शेष */
पूर्ण;

अटल स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans tgl_dkl_phy_dp_ddi_trans_hbr2[] = अणु
				/* VS	pre-emp	Non-trans mV	Pre-emph dB */
	अणु 0x7, 0x0, 0x00 पूर्ण,	/* 0	0	400mV		0 dB */
	अणु 0x5, 0x0, 0x05 पूर्ण,	/* 0	1	400mV		3.5 dB */
	अणु 0x2, 0x0, 0x0B पूर्ण,	/* 0	2	400mV		6 dB */
	अणु 0x0, 0x0, 0x19 पूर्ण,	/* 0	3	400mV		9.5 dB */
	अणु 0x5, 0x0, 0x00 पूर्ण,	/* 1	0	600mV		0 dB */
	अणु 0x2, 0x0, 0x08 पूर्ण,	/* 1	1	600mV		3.5 dB */
	अणु 0x0, 0x0, 0x14 पूर्ण,	/* 1	2	600mV		6 dB */
	अणु 0x2, 0x0, 0x00 पूर्ण,	/* 2	0	800mV		0 dB */
	अणु 0x0, 0x0, 0x0B पूर्ण,	/* 2	1	800mV		3.5 dB */
	अणु 0x0, 0x0, 0x00 पूर्ण,	/* 3	0	1200mV		0 dB HDMI शेष */
पूर्ण;

अटल स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans tgl_dkl_phy_hdmi_ddi_trans[] = अणु
				/* HDMI Preset	VS	Pre-emph */
	अणु 0x7, 0x0, 0x0 पूर्ण,	/* 1		400mV	0dB */
	अणु 0x6, 0x0, 0x0 पूर्ण,	/* 2		500mV	0dB */
	अणु 0x4, 0x0, 0x0 पूर्ण,	/* 3		650mV	0dB */
	अणु 0x2, 0x0, 0x0 पूर्ण,	/* 4		800mV	0dB */
	अणु 0x0, 0x0, 0x0 पूर्ण,	/* 5		1000mV	0dB */
	अणु 0x0, 0x0, 0x5 पूर्ण,	/* 6		Full	-1.5 dB */
	अणु 0x0, 0x0, 0x6 पूर्ण,	/* 7		Full	-1.8 dB */
	अणु 0x0, 0x0, 0x7 पूर्ण,	/* 8		Full	-2 dB */
	अणु 0x0, 0x0, 0x8 पूर्ण,	/* 9		Full	-2.5 dB */
	अणु 0x0, 0x0, 0xA पूर्ण,	/* 10		Full	-3 dB */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans tgl_combo_phy_ddi_translations_dp_hbr[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x32, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x37, 0x00, 0x08 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x71, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7D, 0x2B, 0x00, 0x14 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x4C, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x73, 0x34, 0x00, 0x0B पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x6C, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans tgl_combo_phy_ddi_translations_dp_hbr2[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x37, 0x00, 0x08 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x63, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2B, 0x00, 0x14 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x47, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x63, 0x34, 0x00, 0x0B पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x61, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7B, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans tgl_uy_combo_phy_ddi_translations_dp_hbr2[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x36, 0x00, 0x09 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x60, 0x32, 0x00, 0x0D पूर्ण,	/* 350   700      6.0   */
	अणु 0xC, 0x7F, 0x2D, 0x00, 0x12 पूर्ण,	/* 350   900      8.2   */
	अणु 0xC, 0x47, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x6F, 0x36, 0x00, 0x09 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7D, 0x32, 0x00, 0x0D पूर्ण,	/* 500   900      5.1   */
	अणु 0x6, 0x60, 0x3C, 0x00, 0x03 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x34, 0x00, 0x0B पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

/*
 * Cloned the HOBL entry to comply with the voltage and pre-emphasis entries
 * that DisplayPort specअगरication requires
 */
अटल स्थिर काष्ठा cnl_ddi_buf_trans tgl_combo_phy_ddi_translations_edp_hbr2_hobl[] = अणु
						/* VS	pre-emp	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 0	0	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 0	1	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 0	2	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 0	3	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1	0	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1	1	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 1	2	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 2	0	*/
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 2	1	*/
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans rkl_combo_phy_ddi_translations_dp_hbr[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x2F, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x4F, 0x37, 0x00, 0x08 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x63, 0x2F, 0x00, 0x10 पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7D, 0x2A, 0x00, 0x15 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x4C, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x73, 0x34, 0x00, 0x0B पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x6E, 0x3E, 0x00, 0x01 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7F, 0x35, 0x00, 0x0A पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

अटल स्थिर काष्ठा cnl_ddi_buf_trans rkl_combo_phy_ddi_translations_dp_hbr2_hbr3[] = अणु
						/* NT mV Trans mV db    */
	अणु 0xA, 0x35, 0x3F, 0x00, 0x00 पूर्ण,	/* 350   350      0.0   */
	अणु 0xA, 0x50, 0x38, 0x00, 0x07 पूर्ण,	/* 350   500      3.1   */
	अणु 0xC, 0x61, 0x33, 0x00, 0x0C पूर्ण,	/* 350   700      6.0   */
	अणु 0x6, 0x7F, 0x2E, 0x00, 0x11 पूर्ण,	/* 350   900      8.2   */
	अणु 0xA, 0x47, 0x3F, 0x00, 0x00 पूर्ण,	/* 500   500      0.0   */
	अणु 0xC, 0x5F, 0x38, 0x00, 0x07 पूर्ण,	/* 500   700      2.9   */
	अणु 0x6, 0x7F, 0x2F, 0x00, 0x10 पूर्ण,	/* 500   900      5.1   */
	अणु 0xC, 0x5F, 0x3F, 0x00, 0x00 पूर्ण,	/* 650   700      0.6   */
	अणु 0x6, 0x7E, 0x36, 0x00, 0x09 पूर्ण,	/* 600   900      3.5   */
	अणु 0x6, 0x7F, 0x3F, 0x00, 0x00 पूर्ण,	/* 900   900      0.0   */
पूर्ण;

bool is_hobl_buf_trans(स्थिर काष्ठा cnl_ddi_buf_trans *table)
अणु
	वापस table == tgl_combo_phy_ddi_translations_edp_hbr2_hobl;
पूर्ण

अटल स्थिर काष्ठा ddi_buf_trans *
bdw_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_edp);
		वापस bdw_ddi_translations_edp;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_dp);
		वापस bdw_ddi_translations_dp;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ddi_buf_trans *
skl_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_SKL_ULX(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(skl_y_ddi_translations_dp);
		वापस skl_y_ddi_translations_dp;
	पूर्ण अन्यथा अगर (IS_SKL_ULT(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(skl_u_ddi_translations_dp);
		वापस skl_u_ddi_translations_dp;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(skl_ddi_translations_dp);
		वापस skl_ddi_translations_dp;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ddi_buf_trans *
kbl_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_KBL_ULX(dev_priv) ||
	    IS_CFL_ULX(dev_priv) ||
	    IS_CML_ULX(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(kbl_y_ddi_translations_dp);
		वापस kbl_y_ddi_translations_dp;
	पूर्ण अन्यथा अगर (IS_KBL_ULT(dev_priv) ||
		   IS_CFL_ULT(dev_priv) ||
		   IS_CML_ULT(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(kbl_u_ddi_translations_dp);
		वापस kbl_u_ddi_translations_dp;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(kbl_ddi_translations_dp);
		वापस kbl_ddi_translations_dp;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ddi_buf_trans *
skl_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		अगर (IS_SKL_ULX(dev_priv) ||
		    IS_KBL_ULX(dev_priv) ||
		    IS_CFL_ULX(dev_priv) ||
		    IS_CML_ULX(dev_priv)) अणु
			*n_entries = ARRAY_SIZE(skl_y_ddi_translations_edp);
			वापस skl_y_ddi_translations_edp;
		पूर्ण अन्यथा अगर (IS_SKL_ULT(dev_priv) ||
			   IS_KBL_ULT(dev_priv) ||
			   IS_CFL_ULT(dev_priv) ||
			   IS_CML_ULT(dev_priv)) अणु
			*n_entries = ARRAY_SIZE(skl_u_ddi_translations_edp);
			वापस skl_u_ddi_translations_edp;
		पूर्ण अन्यथा अणु
			*n_entries = ARRAY_SIZE(skl_ddi_translations_edp);
			वापस skl_ddi_translations_edp;
		पूर्ण
	पूर्ण

	अगर (IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv))
		वापस kbl_get_buf_trans_dp(encoder, n_entries);
	अन्यथा
		वापस skl_get_buf_trans_dp(encoder, n_entries);
पूर्ण

अटल स्थिर काष्ठा ddi_buf_trans *
skl_get_buf_trans_hdmi(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक *n_entries)
अणु
	अगर (IS_SKL_ULX(dev_priv) ||
	    IS_KBL_ULX(dev_priv) ||
	    IS_CFL_ULX(dev_priv) ||
	    IS_CML_ULX(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(skl_y_ddi_translations_hdmi);
		वापस skl_y_ddi_translations_hdmi;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(skl_ddi_translations_hdmi);
		वापस skl_ddi_translations_hdmi;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_buf_trans_num_entries(क्रमागत port port, पूर्णांक n_entries)
अणु
	/* Only DDIA and DDIE can select the 10th रेजिस्टर with DP */
	अगर (port == PORT_A || port == PORT_E)
		वापस min(n_entries, 10);
	अन्यथा
		वापस min(n_entries, 9);
पूर्ण

स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv)) अणु
		स्थिर काष्ठा ddi_buf_trans *ddi_translations =
			kbl_get_buf_trans_dp(encoder, n_entries);
		*n_entries = skl_buf_trans_num_entries(encoder->port, *n_entries);
		वापस ddi_translations;
	पूर्ण अन्यथा अगर (IS_SKYLAKE(dev_priv)) अणु
		स्थिर काष्ठा ddi_buf_trans *ddi_translations =
			skl_get_buf_trans_dp(encoder, n_entries);
		*n_entries = skl_buf_trans_num_entries(encoder->port, *n_entries);
		वापस ddi_translations;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_dp);
		वापस  bdw_ddi_translations_dp;
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_dp);
		वापस hsw_ddi_translations_dp;
	पूर्ण

	*n_entries = 0;
	वापस शून्य;
पूर्ण

स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_GEN9_BC(dev_priv)) अणु
		स्थिर काष्ठा ddi_buf_trans *ddi_translations =
			skl_get_buf_trans_edp(encoder, n_entries);
		*n_entries = skl_buf_trans_num_entries(encoder->port, *n_entries);
		वापस ddi_translations;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		वापस bdw_get_buf_trans_edp(encoder, n_entries);
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_dp);
		वापस hsw_ddi_translations_dp;
	पूर्ण

	*n_entries = 0;
	वापस शून्य;
पूर्ण

स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_fdi(काष्ठा drm_i915_निजी *dev_priv,
			    पूर्णांक *n_entries)
अणु
	अगर (IS_BROADWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_fdi);
		वापस bdw_ddi_translations_fdi;
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_fdi);
		वापस hsw_ddi_translations_fdi;
	पूर्ण

	*n_entries = 0;
	वापस शून्य;
पूर्ण

स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_GEN9_BC(dev_priv)) अणु
		वापस skl_get_buf_trans_hdmi(dev_priv, n_entries);
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_hdmi);
		वापस bdw_ddi_translations_hdmi;
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_hdmi);
		वापस hsw_ddi_translations_hdmi;
	पूर्ण

	*n_entries = 0;
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा bxt_ddi_buf_trans *
bxt_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(bxt_ddi_translations_dp);
	वापस bxt_ddi_translations_dp;
पूर्ण

अटल स्थिर काष्ठा bxt_ddi_buf_trans *
bxt_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		*n_entries = ARRAY_SIZE(bxt_ddi_translations_edp);
		वापस bxt_ddi_translations_edp;
	पूर्ण

	वापस bxt_get_buf_trans_dp(encoder, n_entries);
पूर्ण

अटल स्थिर काष्ठा bxt_ddi_buf_trans *
bxt_get_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(bxt_ddi_translations_hdmi);
	वापस bxt_ddi_translations_hdmi;
पूर्ण

स्थिर काष्ठा bxt_ddi_buf_trans *
bxt_get_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		  पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस bxt_get_buf_trans_hdmi(encoder, n_entries);
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस bxt_get_buf_trans_edp(encoder, n_entries);
	वापस bxt_get_buf_trans_dp(encoder, n_entries);
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
cnl_get_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 voltage = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	अगर (voltage == VOLTAGE_INFO_0_85V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_hdmi_0_85V);
		वापस cnl_ddi_translations_hdmi_0_85V;
	पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_0_95V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_hdmi_0_95V);
		वापस cnl_ddi_translations_hdmi_0_95V;
	पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_1_05V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_hdmi_1_05V);
		वापस cnl_ddi_translations_hdmi_1_05V;
	पूर्ण अन्यथा अणु
		*n_entries = 1; /* shut up gcc */
		MISSING_CASE(voltage);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
cnl_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 voltage = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	अगर (voltage == VOLTAGE_INFO_0_85V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_dp_0_85V);
		वापस cnl_ddi_translations_dp_0_85V;
	पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_0_95V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_dp_0_95V);
		वापस cnl_ddi_translations_dp_0_95V;
	पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_1_05V) अणु
		*n_entries = ARRAY_SIZE(cnl_ddi_translations_dp_1_05V);
		वापस cnl_ddi_translations_dp_1_05V;
	पूर्ण अन्यथा अणु
		*n_entries = 1; /* shut up gcc */
		MISSING_CASE(voltage);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
cnl_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 voltage = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		अगर (voltage == VOLTAGE_INFO_0_85V) अणु
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_0_85V);
			वापस cnl_ddi_translations_edp_0_85V;
		पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_0_95V) अणु
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_0_95V);
			वापस cnl_ddi_translations_edp_0_95V;
		पूर्ण अन्यथा अगर (voltage == VOLTAGE_INFO_1_05V) अणु
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_1_05V);
			वापस cnl_ddi_translations_edp_1_05V;
		पूर्ण अन्यथा अणु
			*n_entries = 1; /* shut up gcc */
			MISSING_CASE(voltage);
		पूर्ण
		वापस शून्य;
	पूर्ण अन्यथा अणु
		वापस cnl_get_buf_trans_dp(encoder, n_entries);
	पूर्ण
पूर्ण

स्थिर काष्ठा cnl_ddi_buf_trans *
cnl_get_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		  पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस cnl_get_buf_trans_hdmi(encoder, n_entries);
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस cnl_get_buf_trans_edp(encoder, n_entries);
	वापस cnl_get_buf_trans_dp(encoder, n_entries);
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
icl_get_combo_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_hdmi);
	वापस icl_combo_phy_ddi_translations_hdmi;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
icl_get_combo_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hbr2);
	वापस icl_combo_phy_ddi_translations_dp_hbr2;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
icl_get_combo_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (crtc_state->port_घड़ी > 540000) अणु
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr3);
		वापस icl_combo_phy_ddi_translations_edp_hbr3;
	पूर्ण अन्यथा अगर (dev_priv->vbt.edp.low_vswing) अणु
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr2);
		वापस icl_combo_phy_ddi_translations_edp_hbr2;
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv) && crtc_state->port_घड़ी > 270000) अणु
		*n_entries = ARRAY_SIZE(dg1_combo_phy_ddi_translations_dp_hbr2_hbr3);
		वापस dg1_combo_phy_ddi_translations_dp_hbr2_hbr3;
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		*n_entries = ARRAY_SIZE(dg1_combo_phy_ddi_translations_dp_rbr_hbr);
		वापस dg1_combo_phy_ddi_translations_dp_rbr_hbr;
	पूर्ण

	वापस icl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

स्थिर काष्ठा cnl_ddi_buf_trans *
icl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस icl_get_combo_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस icl_get_combo_buf_trans_edp(encoder, crtc_state, n_entries);
	अन्यथा
		वापस icl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

अटल स्थिर काष्ठा icl_mg_phy_ddi_buf_trans *
icl_get_mg_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations_hdmi);
	वापस icl_mg_phy_ddi_translations_hdmi;
पूर्ण

अटल स्थिर काष्ठा icl_mg_phy_ddi_buf_trans *
icl_get_mg_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries)
अणु
	अगर (crtc_state->port_घड़ी > 270000) अणु
		*n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations_hbr2_hbr3);
		वापस icl_mg_phy_ddi_translations_hbr2_hbr3;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations_rbr_hbr);
		वापस icl_mg_phy_ddi_translations_rbr_hbr;
	पूर्ण
पूर्ण

स्थिर काष्ठा icl_mg_phy_ddi_buf_trans *
icl_get_mg_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		     पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस icl_get_mg_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा
		वापस icl_get_mg_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
ehl_get_combo_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_hdmi);
	वापस icl_combo_phy_ddi_translations_hdmi;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
ehl_get_combo_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(ehl_combo_phy_ddi_translations_dp);
	वापस ehl_combo_phy_ddi_translations_dp;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
ehl_get_combo_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr2);
		वापस icl_combo_phy_ddi_translations_edp_hbr2;
	पूर्ण

	वापस ehl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

स्थिर काष्ठा cnl_ddi_buf_trans *
ehl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस ehl_get_combo_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस ehl_get_combo_buf_trans_edp(encoder, crtc_state, n_entries);
	अन्यथा
		वापस ehl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
jsl_get_combo_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_hdmi);
	वापस icl_combo_phy_ddi_translations_hdmi;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
jsl_get_combo_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hbr2);
	वापस icl_combo_phy_ddi_translations_dp_hbr2;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
jsl_get_combo_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dev_priv->vbt.edp.low_vswing) अणु
		अगर (crtc_state->port_घड़ी > 270000) अणु
			*n_entries = ARRAY_SIZE(jsl_combo_phy_ddi_translations_edp_hbr2);
			वापस jsl_combo_phy_ddi_translations_edp_hbr2;
		पूर्ण अन्यथा अणु
			*n_entries = ARRAY_SIZE(jsl_combo_phy_ddi_translations_edp_hbr);
			वापस jsl_combo_phy_ddi_translations_edp_hbr;
		पूर्ण
	पूर्ण

	वापस jsl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

स्थिर काष्ठा cnl_ddi_buf_trans *
jsl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस jsl_get_combo_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस jsl_get_combo_buf_trans_edp(encoder, crtc_state, n_entries);
	अन्यथा
		वापस jsl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
tgl_get_combo_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_hdmi);
	वापस icl_combo_phy_ddi_translations_hdmi;
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
tgl_get_combo_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (crtc_state->port_घड़ी > 270000) अणु
		अगर (IS_ROCKETLAKE(dev_priv)) अणु
			*n_entries = ARRAY_SIZE(rkl_combo_phy_ddi_translations_dp_hbr2_hbr3);
			वापस rkl_combo_phy_ddi_translations_dp_hbr2_hbr3;
		पूर्ण अन्यथा अगर (IS_TGL_U(dev_priv) || IS_TGL_Y(dev_priv)) अणु
			*n_entries = ARRAY_SIZE(tgl_uy_combo_phy_ddi_translations_dp_hbr2);
			वापस tgl_uy_combo_phy_ddi_translations_dp_hbr2;
		पूर्ण अन्यथा अणु
			*n_entries = ARRAY_SIZE(tgl_combo_phy_ddi_translations_dp_hbr2);
			वापस tgl_combo_phy_ddi_translations_dp_hbr2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IS_ROCKETLAKE(dev_priv)) अणु
			*n_entries = ARRAY_SIZE(rkl_combo_phy_ddi_translations_dp_hbr);
			वापस rkl_combo_phy_ddi_translations_dp_hbr;
		पूर्ण अन्यथा अणु
			*n_entries = ARRAY_SIZE(tgl_combo_phy_ddi_translations_dp_hbr);
			वापस tgl_combo_phy_ddi_translations_dp_hbr;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cnl_ddi_buf_trans *
tgl_get_combo_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    पूर्णांक *n_entries)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	अगर (crtc_state->port_घड़ी > 540000) अणु
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr3);
		वापस icl_combo_phy_ddi_translations_edp_hbr3;
	पूर्ण अन्यथा अगर (dev_priv->vbt.edp.hobl && !पूर्णांकel_dp->hobl_failed) अणु
		*n_entries = ARRAY_SIZE(tgl_combo_phy_ddi_translations_edp_hbr2_hobl);
		वापस tgl_combo_phy_ddi_translations_edp_hbr2_hobl;
	पूर्ण अन्यथा अगर (dev_priv->vbt.edp.low_vswing) अणु
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr2);
		वापस icl_combo_phy_ddi_translations_edp_hbr2;
	पूर्ण

	वापस tgl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

स्थिर काष्ठा cnl_ddi_buf_trans *
tgl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस tgl_get_combo_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		वापस tgl_get_combo_buf_trans_edp(encoder, crtc_state, n_entries);
	अन्यथा
		वापस tgl_get_combo_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

अटल स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans *
tgl_get_dkl_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   पूर्णांक *n_entries)
अणु
	*n_entries = ARRAY_SIZE(tgl_dkl_phy_hdmi_ddi_trans);
	वापस tgl_dkl_phy_hdmi_ddi_trans;
पूर्ण

अटल स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans *
tgl_get_dkl_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 पूर्णांक *n_entries)
अणु
	अगर (crtc_state->port_घड़ी > 270000) अणु
		*n_entries = ARRAY_SIZE(tgl_dkl_phy_dp_ddi_trans_hbr2);
		वापस tgl_dkl_phy_dp_ddi_trans_hbr2;
	पूर्ण अन्यथा अणु
		*n_entries = ARRAY_SIZE(tgl_dkl_phy_dp_ddi_trans);
		वापस tgl_dkl_phy_dp_ddi_trans;
	पूर्ण
पूर्ण

स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans *
tgl_get_dkl_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      पूर्णांक *n_entries)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		वापस tgl_get_dkl_buf_trans_hdmi(encoder, crtc_state, n_entries);
	अन्यथा
		वापस tgl_get_dkl_buf_trans_dp(encoder, crtc_state, n_entries);
पूर्ण

पूर्णांक पूर्णांकel_ddi_hdmi_num_entries(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक *शेष_entry)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	पूर्णांक n_entries;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
			tgl_get_combo_buf_trans_hdmi(encoder, crtc_state, &n_entries);
		अन्यथा
			tgl_get_dkl_buf_trans_hdmi(encoder, crtc_state, &n_entries);
		*शेष_entry = n_entries - 1;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
			icl_get_combo_buf_trans_hdmi(encoder, crtc_state, &n_entries);
		अन्यथा
			icl_get_mg_buf_trans_hdmi(encoder, crtc_state, &n_entries);
		*शेष_entry = n_entries - 1;
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		cnl_get_buf_trans_hdmi(encoder, &n_entries);
		*शेष_entry = n_entries - 1;
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		bxt_get_buf_trans_hdmi(encoder, &n_entries);
		*शेष_entry = n_entries - 1;
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		पूर्णांकel_ddi_get_buf_trans_hdmi(encoder, &n_entries);
		*शेष_entry = 8;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		पूर्णांकel_ddi_get_buf_trans_hdmi(encoder, &n_entries);
		*शेष_entry = 7;
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		पूर्णांकel_ddi_get_buf_trans_hdmi(encoder, &n_entries);
		*शेष_entry = 6;
	पूर्ण अन्यथा अणु
		drm_WARN(&dev_priv->drm, 1, "ddi translation table missing\n");
		वापस 0;
	पूर्ण

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, n_entries == 0))
		वापस 0;

	वापस n_entries;
पूर्ण
