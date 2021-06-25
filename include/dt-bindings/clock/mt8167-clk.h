<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Copyright (c) 2020 BayLibre, SAS.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 *         Fabien Parent <fparent@baylibre.com>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_MT8167_H
#घोषणा _DT_BINDINGS_CLK_MT8167_H

/* MT8167 is based on MT8516 */
#समावेश <dt-bindings/घड़ी/mt8516-clk.h>

/* APMIXEDSYS */

#घोषणा CLK_APMIXED_TVDPLL		(CLK_APMIXED_NR_CLK + 0)
#घोषणा CLK_APMIXED_LVDSPLL		(CLK_APMIXED_NR_CLK + 1)
#घोषणा CLK_APMIXED_HDMI_REF		(CLK_APMIXED_NR_CLK + 2)
#घोषणा MT8167_CLK_APMIXED_NR_CLK	(CLK_APMIXED_NR_CLK + 3)

/* TOPCKGEN */

#घोषणा CLK_TOP_DSI0_LNTC_DSICK		(CLK_TOP_NR_CLK + 0)
#घोषणा CLK_TOP_VPLL_DPIX		(CLK_TOP_NR_CLK + 1)
#घोषणा CLK_TOP_LVDSTX_CLKDIG_CTS	(CLK_TOP_NR_CLK + 2)
#घोषणा CLK_TOP_HDMTX_CLKDIG_CTS	(CLK_TOP_NR_CLK + 3)
#घोषणा CLK_TOP_LVDSPLL			(CLK_TOP_NR_CLK + 4)
#घोषणा CLK_TOP_LVDSPLL_D2		(CLK_TOP_NR_CLK + 5)
#घोषणा CLK_TOP_LVDSPLL_D4		(CLK_TOP_NR_CLK + 6)
#घोषणा CLK_TOP_LVDSPLL_D8		(CLK_TOP_NR_CLK + 7)
#घोषणा CLK_TOP_MIPI_26M		(CLK_TOP_NR_CLK + 8)
#घोषणा CLK_TOP_TVDPLL			(CLK_TOP_NR_CLK + 9)
#घोषणा CLK_TOP_TVDPLL_D2		(CLK_TOP_NR_CLK + 10)
#घोषणा CLK_TOP_TVDPLL_D4		(CLK_TOP_NR_CLK + 11)
#घोषणा CLK_TOP_TVDPLL_D8		(CLK_TOP_NR_CLK + 12)
#घोषणा CLK_TOP_TVDPLL_D16		(CLK_TOP_NR_CLK + 13)
#घोषणा CLK_TOP_PWM_MM			(CLK_TOP_NR_CLK + 14)
#घोषणा CLK_TOP_CAM_MM			(CLK_TOP_NR_CLK + 15)
#घोषणा CLK_TOP_MFG_MM			(CLK_TOP_NR_CLK + 16)
#घोषणा CLK_TOP_SPM_52M			(CLK_TOP_NR_CLK + 17)
#घोषणा CLK_TOP_MIPI_26M_DBG		(CLK_TOP_NR_CLK + 18)
#घोषणा CLK_TOP_SCAM_MM			(CLK_TOP_NR_CLK + 19)
#घोषणा CLK_TOP_SMI_MM			(CLK_TOP_NR_CLK + 20)
#घोषणा CLK_TOP_26M_HDMI_SIFM		(CLK_TOP_NR_CLK + 21)
#घोषणा CLK_TOP_26M_CEC			(CLK_TOP_NR_CLK + 22)
#घोषणा CLK_TOP_32K_CEC			(CLK_TOP_NR_CLK + 23)
#घोषणा CLK_TOP_GCPU_B			(CLK_TOP_NR_CLK + 24)
#घोषणा CLK_TOP_RG_VDEC			(CLK_TOP_NR_CLK + 25)
#घोषणा CLK_TOP_RG_FDPI0		(CLK_TOP_NR_CLK + 26)
#घोषणा CLK_TOP_RG_FDPI1		(CLK_TOP_NR_CLK + 27)
#घोषणा CLK_TOP_RG_AXI_MFG		(CLK_TOP_NR_CLK + 28)
#घोषणा CLK_TOP_RG_SLOW_MFG		(CLK_TOP_NR_CLK + 29)
#घोषणा CLK_TOP_GFMUX_EMI1X_SEL		(CLK_TOP_NR_CLK + 30)
#घोषणा CLK_TOP_CSW_MUX_MFG_SEL		(CLK_TOP_NR_CLK + 31)
#घोषणा CLK_TOP_CAMTG_MM_SEL		(CLK_TOP_NR_CLK + 32)
#घोषणा CLK_TOP_PWM_MM_SEL		(CLK_TOP_NR_CLK + 33)
#घोषणा CLK_TOP_SPM_52M_SEL		(CLK_TOP_NR_CLK + 34)
#घोषणा CLK_TOP_MFG_MM_SEL		(CLK_TOP_NR_CLK + 35)
#घोषणा CLK_TOP_SMI_MM_SEL		(CLK_TOP_NR_CLK + 36)
#घोषणा CLK_TOP_SCAM_MM_SEL		(CLK_TOP_NR_CLK + 37)
#घोषणा CLK_TOP_VDEC_MM_SEL		(CLK_TOP_NR_CLK + 38)
#घोषणा CLK_TOP_DPI0_MM_SEL		(CLK_TOP_NR_CLK + 39)
#घोषणा CLK_TOP_DPI1_MM_SEL		(CLK_TOP_NR_CLK + 40)
#घोषणा CLK_TOP_AXI_MFG_IN_SEL		(CLK_TOP_NR_CLK + 41)
#घोषणा CLK_TOP_SLOW_MFG_SEL		(CLK_TOP_NR_CLK + 42)
#घोषणा MT8167_CLK_TOP_NR_CLK		(CLK_TOP_NR_CLK + 43)

/* MFGCFG */

#घोषणा CLK_MFG_BAXI			0
#घोषणा CLK_MFG_BMEM			1
#घोषणा CLK_MFG_BG3D			2
#घोषणा CLK_MFG_B26M			3
#घोषणा CLK_MFG_NR_CLK			4

/* MMSYS */

#घोषणा CLK_MM_SMI_COMMON		0
#घोषणा CLK_MM_SMI_LARB0		1
#घोषणा CLK_MM_CAM_MDP			2
#घोषणा CLK_MM_MDP_RDMA			3
#घोषणा CLK_MM_MDP_RSZ0			4
#घोषणा CLK_MM_MDP_RSZ1			5
#घोषणा CLK_MM_MDP_TDSHP		6
#घोषणा CLK_MM_MDP_WDMA			7
#घोषणा CLK_MM_MDP_WROT			8
#घोषणा CLK_MM_FAKE_ENG			9
#घोषणा CLK_MM_DISP_OVL0		10
#घोषणा CLK_MM_DISP_RDMA0		11
#घोषणा CLK_MM_DISP_RDMA1		12
#घोषणा CLK_MM_DISP_WDMA		13
#घोषणा CLK_MM_DISP_COLOR		14
#घोषणा CLK_MM_DISP_CCORR		15
#घोषणा CLK_MM_DISP_AAL			16
#घोषणा CLK_MM_DISP_GAMMA		17
#घोषणा CLK_MM_DISP_DITHER		18
#घोषणा CLK_MM_DISP_UFOE		19
#घोषणा CLK_MM_DISP_PWM_MM		20
#घोषणा CLK_MM_DISP_PWM_26M		21
#घोषणा CLK_MM_DSI_ENGINE		22
#घोषणा CLK_MM_DSI_DIGITAL		23
#घोषणा CLK_MM_DPI0_ENGINE		24
#घोषणा CLK_MM_DPI0_PXL			25
#घोषणा CLK_MM_LVDS_PXL			26
#घोषणा CLK_MM_LVDS_CTS			27
#घोषणा CLK_MM_DPI1_ENGINE		28
#घोषणा CLK_MM_DPI1_PXL			29
#घोषणा CLK_MM_HDMI_PXL			30
#घोषणा CLK_MM_HDMI_SPDIF		31
#घोषणा CLK_MM_HDMI_ADSP_BCK		32
#घोषणा CLK_MM_HDMI_PLL			33
#घोषणा CLK_MM_NR_CLK			34

/* IMGSYS */

#घोषणा CLK_IMG_LARB1_SMI		0
#घोषणा CLK_IMG_CAM_SMI			1
#घोषणा CLK_IMG_CAM_CAM			2
#घोषणा CLK_IMG_SEN_TG			3
#घोषणा CLK_IMG_SEN_CAM			4
#घोषणा CLK_IMG_VENC			5
#घोषणा CLK_IMG_NR_CLK			6

/* VDECSYS */

#घोषणा CLK_VDEC_CKEN			0
#घोषणा CLK_VDEC_LARB1_CKEN		1
#घोषणा CLK_VDEC_NR_CLK			2

#पूर्ण_अगर /* _DT_BINDINGS_CLK_MT8167_H */
