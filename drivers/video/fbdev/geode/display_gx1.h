<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/video/geode/display_gx1.h
 *   -- Geode GX1 display controller
 *
 * Copyright (C) 2005 Arcom Control Systems Ltd.
 *
 * Based on AMD's original 2.4 driver:
 *   Copyright (C) 2004 Advanced Micro Devices, Inc.
 */
#अगर_अघोषित __DISPLAY_GX1_H__
#घोषणा __DISPLAY_GX1_H__

अचिन्हित gx1_gx_base(व्योम);
पूर्णांक gx1_frame_buffer_size(व्योम);

बाह्य स्थिर काष्ठा geode_dc_ops gx1_dc_ops;

/* GX1 configuration I/O रेजिस्टरs */

#घोषणा CONFIG_CCR3 0xc3
#  define CONFIG_CCR3_MAPEN 0x10
#घोषणा CONFIG_GCR  0xb8

/* Memory controller रेजिस्टरs */

#घोषणा MC_BANK_CFG		0x08
#  define MC_BCFG_DIMM0_SZ_MASK		0x00000700
#  define MC_BCFG_DIMM0_PG_SZ_MASK	0x00000070
#  define MC_BCFG_DIMM0_PG_SZ_NO_DIMM	0x00000070

#घोषणा MC_GBASE_ADD		0x14
#  define MC_GADD_GBADD_MASK		0x000003ff

/* Display controller रेजिस्टरs */

#घोषणा DC_PAL_ADDRESS		0x70
#घोषणा DC_PAL_DATA		0x74

#घोषणा DC_UNLOCK		0x00
#  define DC_UNLOCK_CODE		0x00004758

#घोषणा DC_GENERAL_CFG		0x04
#  define DC_GCFG_DFLE			0x00000001
#  define DC_GCFG_CURE			0x00000002
#  define DC_GCFG_VCLK_DIV		0x00000004
#  define DC_GCFG_PLNO			0x00000004
#  define DC_GCFG_PPC			0x00000008
#  define DC_GCFG_CMPE			0x00000010
#  define DC_GCFG_DECE			0x00000020
#  define DC_GCFG_DCLK_MASK		0x000000C0
#  define DC_GCFG_DCLK_DIV_1		0x00000080
#  define DC_GCFG_DFHPSL_MASK		0x00000F00
#  define DC_GCFG_DFHPSL_POS			 8
#  define DC_GCFG_DFHPEL_MASK		0x0000F000
#  define DC_GCFG_DFHPEL_POS			12
#  define DC_GCFG_CIM_MASK		0x00030000
#  define DC_GCFG_CIM_POS			16
#  define DC_GCFG_FDTY			0x00040000
#  define DC_GCFG_RTPM			0x00080000
#  define DC_GCFG_DAC_RS_MASK		0x00700000
#  define DC_GCFG_DAC_RS_POS			20
#  define DC_GCFG_CKWR			0x00800000
#  define DC_GCFG_LDBL			0x01000000
#  define DC_GCFG_DIAG			0x02000000
#  define DC_GCFG_CH4S			0x04000000
#  define DC_GCFG_SSLC			0x08000000
#  define DC_GCFG_VIDE			0x10000000
#  define DC_GCFG_VRDY			0x20000000
#  define DC_GCFG_DPCK			0x40000000
#  define DC_GCFG_DDCK			0x80000000

#घोषणा DC_TIMING_CFG		0x08
#  define DC_TCFG_FPPE			0x00000001
#  define DC_TCFG_HSYE			0x00000002
#  define DC_TCFG_VSYE			0x00000004
#  define DC_TCFG_BLKE			0x00000008
#  define DC_TCFG_DDCK			0x00000010
#  define DC_TCFG_TGEN			0x00000020
#  define DC_TCFG_VIEN			0x00000040
#  define DC_TCFG_BLNK			0x00000080
#  define DC_TCFG_CHSP			0x00000100
#  define DC_TCFG_CVSP			0x00000200
#  define DC_TCFG_FHSP			0x00000400
#  define DC_TCFG_FVSP			0x00000800
#  define DC_TCFG_FCEN			0x00001000
#  define DC_TCFG_CDCE			0x00002000
#  define DC_TCFG_PLNR			0x00002000
#  define DC_TCFG_INTL			0x00004000
#  define DC_TCFG_PXDB			0x00008000
#  define DC_TCFG_BKRT			0x00010000
#  define DC_TCFG_PSD_MASK		0x000E0000
#  define DC_TCFG_PSD_POS			17
#  define DC_TCFG_DDCI			0x08000000
#  define DC_TCFG_SENS			0x10000000
#  define DC_TCFG_DNA			0x20000000
#  define DC_TCFG_VNA			0x40000000
#  define DC_TCFG_VINT			0x80000000

#घोषणा DC_OUTPUT_CFG		0x0C
#  define DC_OCFG_8BPP			0x00000001
#  define DC_OCFG_555			0x00000002
#  define DC_OCFG_PCKE			0x00000004
#  define DC_OCFG_FRME			0x00000008
#  define DC_OCFG_DITE			0x00000010
#  define DC_OCFG_2PXE			0x00000020
#  define DC_OCFG_2XCK			0x00000040
#  define DC_OCFG_2IND			0x00000080
#  define DC_OCFG_34ADD			0x00000100
#  define DC_OCFG_FRMS			0x00000200
#  define DC_OCFG_CKSL			0x00000400
#  define DC_OCFG_PRMP			0x00000800
#  define DC_OCFG_PDEL			0x00001000
#  define DC_OCFG_PDEH			0x00002000
#  define DC_OCFG_CFRW			0x00004000
#  define DC_OCFG_DIAG			0x00008000

#घोषणा DC_FB_ST_OFFSET		0x10
#घोषणा DC_CB_ST_OFFSET		0x14
#घोषणा DC_CURS_ST_OFFSET	0x18
#घोषणा DC_ICON_ST_OFFSET	0x1C
#घोषणा DC_VID_ST_OFFSET	0x20
#घोषणा DC_LINE_DELTA		0x24
#घोषणा DC_BUF_SIZE		0x28

#घोषणा DC_H_TIMING_1		0x30
#घोषणा DC_H_TIMING_2		0x34
#घोषणा DC_H_TIMING_3		0x38
#घोषणा DC_FP_H_TIMING		0x3C

#घोषणा DC_V_TIMING_1		0x40
#घोषणा DC_V_TIMING_2		0x44
#घोषणा DC_V_TIMING_3		0x48
#घोषणा DC_FP_V_TIMING		0x4C

#घोषणा DC_CURSOR_X		0x50
#घोषणा DC_ICON_X		0x54
#घोषणा DC_V_LINE_CNT		0x54
#घोषणा DC_CURSOR_Y		0x58
#घोषणा DC_ICON_Y		0x5C
#घोषणा DC_SS_LINE_CMP		0x5C
#घोषणा DC_CURSOR_COLOR		0x60
#घोषणा DC_ICON_COLOR		0x64
#घोषणा DC_BORDER_COLOR		0x68
#घोषणा DC_PAL_ADDRESS		0x70
#घोषणा DC_PAL_DATA		0x74
#घोषणा DC_DFIFO_DIAG		0x78
#घोषणा DC_CFIFO_DIAG		0x7C

#पूर्ण_अगर /* !__DISPLAY_GX1_H__ */
