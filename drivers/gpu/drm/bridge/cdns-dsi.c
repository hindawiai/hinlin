<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright: 2017 Cadence Design Systems, Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <video/mipi_display.h>

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

#घोषणा IP_CONF				0x0
#घोषणा SP_HS_FIFO_DEPTH(x)		(((x) & GENMASK(30, 26)) >> 26)
#घोषणा SP_LP_FIFO_DEPTH(x)		(((x) & GENMASK(25, 21)) >> 21)
#घोषणा VRS_FIFO_DEPTH(x)		(((x) & GENMASK(20, 16)) >> 16)
#घोषणा सूचीCMD_FIFO_DEPTH(x)		(((x) & GENMASK(15, 13)) >> 13)
#घोषणा SDI_IFACE_32			BIT(12)
#घोषणा INTERNAL_DATAPATH_32		(0 << 10)
#घोषणा INTERNAL_DATAPATH_16		(1 << 10)
#घोषणा INTERNAL_DATAPATH_8		(3 << 10)
#घोषणा INTERNAL_DATAPATH_SIZE		((x) & GENMASK(11, 10))
#घोषणा NUM_IFACE(x)			((((x) & GENMASK(9, 8)) >> 8) + 1)
#घोषणा MAX_LANE_NB(x)			(((x) & GENMASK(7, 6)) >> 6)
#घोषणा RX_FIFO_DEPTH(x)		((x) & GENMASK(5, 0))

#घोषणा MCTL_MAIN_DATA_CTL		0x4
#घोषणा TE_MIPI_POLLING_EN		BIT(25)
#घोषणा TE_HW_POLLING_EN		BIT(24)
#घोषणा DISP_EOT_GEN			BIT(18)
#घोषणा HOST_EOT_GEN			BIT(17)
#घोषणा DISP_GEN_CHECKSUM		BIT(16)
#घोषणा DISP_GEN_ECC			BIT(15)
#घोषणा BTA_EN				BIT(14)
#घोषणा READ_EN				BIT(13)
#घोषणा REG_TE_EN			BIT(12)
#घोषणा IF_TE_EN(x)			BIT(8 + (x))
#घोषणा TVG_SEL				BIT(6)
#घोषणा VID_EN				BIT(5)
#घोषणा IF_VID_SELECT(x)		((x) << 2)
#घोषणा IF_VID_SELECT_MASK		GENMASK(3, 2)
#घोषणा IF_VID_MODE			BIT(1)
#घोषणा LINK_EN				BIT(0)

#घोषणा MCTL_MAIN_PHY_CTL		0x8
#घोषणा HS_INVERT_DAT(x)		BIT(19 + ((x) * 2))
#घोषणा SWAP_PINS_DAT(x)		BIT(18 + ((x) * 2))
#घोषणा HS_INVERT_CLK			BIT(17)
#घोषणा SWAP_PINS_CLK			BIT(16)
#घोषणा HS_SKEWCAL_EN			BIT(15)
#घोषणा WAIT_BURST_TIME(x)		((x) << 10)
#घोषणा DATA_ULPM_EN(x)			BIT(6 + (x))
#घोषणा CLK_ULPM_EN			BIT(5)
#घोषणा CLK_CONTINUOUS			BIT(4)
#घोषणा DATA_LANE_EN(x)			BIT((x) - 1)

#घोषणा MCTL_MAIN_EN			0xc
#घोषणा DATA_FORCE_STOP			BIT(17)
#घोषणा CLK_FORCE_STOP			BIT(16)
#घोषणा IF_EN(x)			BIT(13 + (x))
#घोषणा DATA_LANE_ULPM_REQ(l)		BIT(9 + (l))
#घोषणा CLK_LANE_ULPM_REQ		BIT(8)
#घोषणा DATA_LANE_START(x)		BIT(4 + (x))
#घोषणा CLK_LANE_EN			BIT(3)
#घोषणा PLL_START			BIT(0)

#घोषणा MCTL_DPHY_CFG0			0x10
#घोषणा DPHY_C_RSTB			BIT(20)
#घोषणा DPHY_D_RSTB(x)			GENMASK(15 + (x), 16)
#घोषणा DPHY_PLL_PDN			BIT(10)
#घोषणा DPHY_CMN_PDN			BIT(9)
#घोषणा DPHY_C_PDN			BIT(8)
#घोषणा DPHY_D_PDN(x)			GENMASK(3 + (x), 4)
#घोषणा DPHY_ALL_D_PDN			GENMASK(7, 4)
#घोषणा DPHY_PLL_PSO			BIT(1)
#घोषणा DPHY_CMN_PSO			BIT(0)

#घोषणा MCTL_DPHY_TIMEOUT1		0x14
#घोषणा HSTX_TIMEOUT(x)			((x) << 4)
#घोषणा HSTX_TIMEOUT_MAX		GENMASK(17, 0)
#घोषणा CLK_DIV(x)			(x)
#घोषणा CLK_DIV_MAX			GENMASK(3, 0)

#घोषणा MCTL_DPHY_TIMEOUT2		0x18
#घोषणा LPRX_TIMEOUT(x)			(x)

#घोषणा MCTL_ULPOUT_TIME		0x1c
#घोषणा DATA_LANE_ULPOUT_TIME(x)	((x) << 9)
#घोषणा CLK_LANE_ULPOUT_TIME(x)		(x)

#घोषणा MCTL_3DVIDEO_CTL		0x20
#घोषणा VID_VSYNC_3D_EN			BIT(7)
#घोषणा VID_VSYNC_3D_LR			BIT(5)
#घोषणा VID_VSYNC_3D_SECOND_EN		BIT(4)
#घोषणा VID_VSYNC_3DFORMAT_LINE		(0 << 2)
#घोषणा VID_VSYNC_3DFORMAT_FRAME	(1 << 2)
#घोषणा VID_VSYNC_3DFORMAT_PIXEL	(2 << 2)
#घोषणा VID_VSYNC_3DMODE_OFF		0
#घोषणा VID_VSYNC_3DMODE_PORTRAIT	1
#घोषणा VID_VSYNC_3DMODE_LANDSCAPE	2

#घोषणा MCTL_MAIN_STS			0x24
#घोषणा MCTL_MAIN_STS_CTL		0x130
#घोषणा MCTL_MAIN_STS_CLR		0x150
#घोषणा MCTL_MAIN_STS_FLAG		0x170
#घोषणा HS_SKEWCAL_DONE			BIT(11)
#घोषणा IF_UNTERM_PKT_ERR(x)		BIT(8 + (x))
#घोषणा LPRX_TIMEOUT_ERR		BIT(7)
#घोषणा HSTX_TIMEOUT_ERR		BIT(6)
#घोषणा DATA_LANE_RDY(l)		BIT(2 + (l))
#घोषणा CLK_LANE_RDY			BIT(1)
#घोषणा PLL_LOCKED			BIT(0)

#घोषणा MCTL_DPHY_ERR			0x28
#घोषणा MCTL_DPHY_ERR_CTL1		0x148
#घोषणा MCTL_DPHY_ERR_CLR		0x168
#घोषणा MCTL_DPHY_ERR_FLAG		0x188
#घोषणा ERR_CONT_LP(x, l)		BIT(18 + ((x) * 4) + (l))
#घोषणा ERR_CONTROL(l)			BIT(14 + (l))
#घोषणा ERR_SYNESC(l)			BIT(10 + (l))
#घोषणा ERR_ESC(l)			BIT(6 + (l))

#घोषणा MCTL_DPHY_ERR_CTL2		0x14c
#घोषणा ERR_CONT_LP_EDGE(x, l)		BIT(12 + ((x) * 4) + (l))
#घोषणा ERR_CONTROL_EDGE(l)		BIT(8 + (l))
#घोषणा ERR_SYN_ESC_EDGE(l)		BIT(4 + (l))
#घोषणा ERR_ESC_EDGE(l)			BIT(0 + (l))

#घोषणा MCTL_LANE_STS			0x2c
#घोषणा PPI_C_TX_READY_HS		BIT(18)
#घोषणा DPHY_PLL_LOCK			BIT(17)
#घोषणा PPI_D_RX_ULPS_ESC(x)		(((x) & GENMASK(15, 12)) >> 12)
#घोषणा LANE_STATE_START		0
#घोषणा LANE_STATE_IDLE			1
#घोषणा LANE_STATE_WRITE		2
#घोषणा LANE_STATE_ULPM			3
#घोषणा LANE_STATE_READ			4
#घोषणा DATA_LANE_STATE(l, val)		\
	(((val) >> (2 + 2 * (l) + ((l) ? 1 : 0))) & GENMASK((l) ? 1 : 2, 0))
#घोषणा CLK_LANE_STATE_HS		2
#घोषणा CLK_LANE_STATE(val)		((val) & GENMASK(1, 0))

#घोषणा DSC_MODE_CTL			0x30
#घोषणा DSC_MODE_EN			BIT(0)

#घोषणा DSC_CMD_SEND			0x34
#घोषणा DSC_SEND_PPS			BIT(0)
#घोषणा DSC_EXECUTE_QUEUE		BIT(1)

#घोषणा DSC_PPS_WRDAT			0x38

#घोषणा DSC_MODE_STS			0x3c
#घोषणा DSC_PPS_DONE			BIT(1)
#घोषणा DSC_EXEC_DONE			BIT(2)

#घोषणा CMD_MODE_CTL			0x70
#घोषणा IF_LP_EN(x)			BIT(9 + (x))
#घोषणा IF_VCHAN_ID(x, c)		((c) << ((x) * 2))

#घोषणा CMD_MODE_CTL2			0x74
#घोषणा TE_TIMEOUT(x)			((x) << 11)
#घोषणा FILL_VALUE(x)			((x) << 3)
#घोषणा ARB_IF_WITH_HIGHEST_PRIORITY(x)	((x) << 1)
#घोषणा ARB_ROUND_ROBIN_MODE		BIT(0)

#घोषणा CMD_MODE_STS			0x78
#घोषणा CMD_MODE_STS_CTL		0x134
#घोषणा CMD_MODE_STS_CLR		0x154
#घोषणा CMD_MODE_STS_FLAG		0x174
#घोषणा ERR_IF_UNDERRUN(x)		BIT(4 + (x))
#घोषणा ERR_UNWANTED_READ		BIT(3)
#घोषणा ERR_TE_MISS			BIT(2)
#घोषणा ERR_NO_TE			BIT(1)
#घोषणा CSM_RUNNING			BIT(0)

#घोषणा सूचीECT_CMD_SEND			0x80

#घोषणा सूचीECT_CMD_MAIN_SETTINGS	0x84
#घोषणा TRIGGER_VAL(x)			((x) << 25)
#घोषणा CMD_LP_EN			BIT(24)
#घोषणा CMD_SIZE(x)			((x) << 16)
#घोषणा CMD_VCHAN_ID(x)			((x) << 14)
#घोषणा CMD_DATATYPE(x)			((x) << 8)
#घोषणा CMD_LONG			BIT(3)
#घोषणा WRITE_CMD			0
#घोषणा READ_CMD			1
#घोषणा TE_REQ				4
#घोषणा TRIGGER_REQ			5
#घोषणा BTA_REQ				6

#घोषणा सूचीECT_CMD_STS			0x88
#घोषणा सूचीECT_CMD_STS_CTL		0x138
#घोषणा सूचीECT_CMD_STS_CLR		0x158
#घोषणा सूचीECT_CMD_STS_FLAG		0x178
#घोषणा RCVD_ACK_VAL(val)		((val) >> 16)
#घोषणा RCVD_TRIGGER_VAL(val)		(((val) & GENMASK(14, 11)) >> 11)
#घोषणा READ_COMPLETED_WITH_ERR		BIT(10)
#घोषणा BTA_FINISHED			BIT(9)
#घोषणा BTA_COMPLETED			BIT(8)
#घोषणा TE_RCVD				BIT(7)
#घोषणा TRIGGER_RCVD			BIT(6)
#घोषणा ACK_WITH_ERR_RCVD		BIT(5)
#घोषणा ACK_RCVD			BIT(4)
#घोषणा READ_COMPLETED			BIT(3)
#घोषणा TRIGGER_COMPLETED		BIT(2)
#घोषणा WRITE_COMPLETED			BIT(1)
#घोषणा SENDING_CMD			BIT(0)

#घोषणा सूचीECT_CMD_STOP_READ		0x8c

#घोषणा सूचीECT_CMD_WRDATA		0x90

#घोषणा सूचीECT_CMD_FIFO_RST		0x94

#घोषणा सूचीECT_CMD_RDDATA		0xa0

#घोषणा सूचीECT_CMD_RD_PROPS		0xa4
#घोषणा RD_DCS				BIT(18)
#घोषणा RD_VCHAN_ID(val)		(((val) >> 16) & GENMASK(1, 0))
#घोषणा RD_SIZE(val)			((val) & GENMASK(15, 0))

#घोषणा सूचीECT_CMD_RD_STS		0xa8
#घोषणा सूचीECT_CMD_RD_STS_CTL		0x13c
#घोषणा सूचीECT_CMD_RD_STS_CLR		0x15c
#घोषणा सूचीECT_CMD_RD_STS_FLAG		0x17c
#घोषणा ERR_EOT_WITH_ERR		BIT(8)
#घोषणा ERR_MISSING_EOT			BIT(7)
#घोषणा ERR_WRONG_LENGTH		BIT(6)
#घोषणा ERR_OVERSIZE			BIT(5)
#घोषणा ERR_RECEIVE			BIT(4)
#घोषणा ERR_UNDECODABLE			BIT(3)
#घोषणा ERR_CHECKSUM			BIT(2)
#घोषणा ERR_UNCORRECTABLE		BIT(1)
#घोषणा ERR_FIXED			BIT(0)

#घोषणा VID_MAIN_CTL			0xb0
#घोषणा VID_IGNORE_MISS_VSYNC		BIT(31)
#घोषणा VID_FIELD_SW			BIT(28)
#घोषणा VID_INTERLACED_EN		BIT(27)
#घोषणा RECOVERY_MODE(x)		((x) << 25)
#घोषणा RECOVERY_MODE_NEXT_HSYNC	0
#घोषणा RECOVERY_MODE_NEXT_STOP_POINT	2
#घोषणा RECOVERY_MODE_NEXT_VSYNC	3
#घोषणा REG_BLKEOL_MODE(x)		((x) << 23)
#घोषणा REG_BLKLINE_MODE(x)		((x) << 21)
#घोषणा REG_BLK_MODE_शून्य_PKT		0
#घोषणा REG_BLK_MODE_BLANKING_PKT	1
#घोषणा REG_BLK_MODE_LP			2
#घोषणा SYNC_PULSE_HORIZONTAL		BIT(20)
#घोषणा SYNC_PULSE_ACTIVE		BIT(19)
#घोषणा BURST_MODE			BIT(18)
#घोषणा VID_PIXEL_MODE_MASK		GENMASK(17, 14)
#घोषणा VID_PIXEL_MODE_RGB565		(0 << 14)
#घोषणा VID_PIXEL_MODE_RGB666_PACKED	(1 << 14)
#घोषणा VID_PIXEL_MODE_RGB666		(2 << 14)
#घोषणा VID_PIXEL_MODE_RGB888		(3 << 14)
#घोषणा VID_PIXEL_MODE_RGB101010	(4 << 14)
#घोषणा VID_PIXEL_MODE_RGB121212	(5 << 14)
#घोषणा VID_PIXEL_MODE_YUV420		(8 << 14)
#घोषणा VID_PIXEL_MODE_YUV422_PACKED	(9 << 14)
#घोषणा VID_PIXEL_MODE_YUV422		(10 << 14)
#घोषणा VID_PIXEL_MODE_YUV422_24B	(11 << 14)
#घोषणा VID_PIXEL_MODE_DSC_COMP		(12 << 14)
#घोषणा VID_DATATYPE(x)			((x) << 8)
#घोषणा VID_VIRTCHAN_ID(अगरace, x)	((x) << (4 + (अगरace) * 2))
#घोषणा STOP_MODE(x)			((x) << 2)
#घोषणा START_MODE(x)			(x)

#घोषणा VID_VSIZE1			0xb4
#घोषणा VFP_LEN(x)			((x) << 12)
#घोषणा VBP_LEN(x)			((x) << 6)
#घोषणा VSA_LEN(x)			(x)

#घोषणा VID_VSIZE2			0xb8
#घोषणा VACT_LEN(x)			(x)

#घोषणा VID_HSIZE1			0xc0
#घोषणा HBP_LEN(x)			((x) << 16)
#घोषणा HSA_LEN(x)			(x)

#घोषणा VID_HSIZE2			0xc4
#घोषणा HFP_LEN(x)			((x) << 16)
#घोषणा HACT_LEN(x)			(x)

#घोषणा VID_BLKSIZE1			0xcc
#घोषणा BLK_EOL_PKT_LEN(x)		((x) << 15)
#घोषणा BLK_LINE_EVENT_PKT_LEN(x)	(x)

#घोषणा VID_BLKSIZE2			0xd0
#घोषणा BLK_LINE_PULSE_PKT_LEN(x)	(x)

#घोषणा VID_PKT_TIME			0xd8
#घोषणा BLK_EOL_DURATION(x)		(x)

#घोषणा VID_DPHY_TIME			0xdc
#घोषणा REG_WAKEUP_TIME(x)		((x) << 17)
#घोषणा REG_LINE_DURATION(x)		(x)

#घोषणा VID_ERR_COLOR1			0xe0
#घोषणा COL_GREEN(x)			((x) << 12)
#घोषणा COL_RED(x)			(x)

#घोषणा VID_ERR_COLOR2			0xe4
#घोषणा PAD_VAL(x)			((x) << 12)
#घोषणा COL_BLUE(x)			(x)

#घोषणा VID_VPOS			0xe8
#घोषणा LINE_VAL(val)			(((val) & GENMASK(14, 2)) >> 2)
#घोषणा LINE_POS(val)			((val) & GENMASK(1, 0))

#घोषणा VID_HPOS			0xec
#घोषणा HORIZ_VAL(val)			(((val) & GENMASK(17, 3)) >> 3)
#घोषणा HORIZ_POS(val)			((val) & GENMASK(2, 0))

#घोषणा VID_MODE_STS			0xf0
#घोषणा VID_MODE_STS_CTL		0x140
#घोषणा VID_MODE_STS_CLR		0x160
#घोषणा VID_MODE_STS_FLAG		0x180
#घोषणा VSG_RECOVERY			BIT(10)
#घोषणा ERR_VRS_WRONG_LEN		BIT(9)
#घोषणा ERR_LONG_READ			BIT(8)
#घोषणा ERR_LINE_WRITE			BIT(7)
#घोषणा ERR_BURST_WRITE			BIT(6)
#घोषणा ERR_SMALL_HEIGHT		BIT(5)
#घोषणा ERR_SMALL_LEN			BIT(4)
#घोषणा ERR_MISSING_VSYNC		BIT(3)
#घोषणा ERR_MISSING_HSYNC		BIT(2)
#घोषणा ERR_MISSING_DATA		BIT(1)
#घोषणा VSG_RUNNING			BIT(0)

#घोषणा VID_VCA_SETTING1		0xf4
#घोषणा BURST_LP			BIT(16)
#घोषणा MAX_BURST_LIMIT(x)		(x)

#घोषणा VID_VCA_SETTING2		0xf8
#घोषणा MAX_LINE_LIMIT(x)		((x) << 16)
#घोषणा EXACT_BURST_LIMIT(x)		(x)

#घोषणा TVG_CTL				0xfc
#घोषणा TVG_STRIPE_SIZE(x)		((x) << 5)
#घोषणा TVG_MODE_MASK			GENMASK(4, 3)
#घोषणा TVG_MODE_SINGLE_COLOR		(0 << 3)
#घोषणा TVG_MODE_VSTRIPES		(2 << 3)
#घोषणा TVG_MODE_HSTRIPES		(3 << 3)
#घोषणा TVG_STOPMODE_MASK		GENMASK(2, 1)
#घोषणा TVG_STOPMODE_खातापूर्ण		(0 << 1)
#घोषणा TVG_STOPMODE_EOL		(1 << 1)
#घोषणा TVG_STOPMODE_NOW		(2 << 1)
#घोषणा TVG_RUN				BIT(0)

#घोषणा TVG_IMG_SIZE			0x100
#घोषणा TVG_NBLINES(x)			((x) << 16)
#घोषणा TVG_LINE_SIZE(x)		(x)

#घोषणा TVG_COLOR1			0x104
#घोषणा TVG_COL1_GREEN(x)		((x) << 12)
#घोषणा TVG_COL1_RED(x)			(x)

#घोषणा TVG_COLOR1_BIS			0x108
#घोषणा TVG_COL1_BLUE(x)		(x)

#घोषणा TVG_COLOR2			0x10c
#घोषणा TVG_COL2_GREEN(x)		((x) << 12)
#घोषणा TVG_COL2_RED(x)			(x)

#घोषणा TVG_COLOR2_BIS			0x110
#घोषणा TVG_COL2_BLUE(x)		(x)

#घोषणा TVG_STS				0x114
#घोषणा TVG_STS_CTL			0x144
#घोषणा TVG_STS_CLR			0x164
#घोषणा TVG_STS_FLAG			0x184
#घोषणा TVG_STS_RUNNING			BIT(0)

#घोषणा STS_CTL_EDGE(e)			((e) << 16)

#घोषणा DPHY_LANES_MAP			0x198
#घोषणा DAT_REMAP_CFG(b, l)		((l) << ((b) * 8))

#घोषणा DPI_IRQ_EN			0x1a0
#घोषणा DPI_IRQ_CLR			0x1a4
#घोषणा DPI_IRQ_STS			0x1a8
#घोषणा PIXEL_BUF_OVERFLOW		BIT(0)

#घोषणा DPI_CFG				0x1ac
#घोषणा DPI_CFG_FIFO_DEPTH(x)		((x) >> 16)
#घोषणा DPI_CFG_FIFO_LEVEL(x)		((x) & GENMASK(15, 0))

#घोषणा TEST_GENERIC			0x1f0
#घोषणा TEST_STATUS(x)			((x) >> 16)
#घोषणा TEST_CTRL(x)			(x)

#घोषणा ID_REG				0x1fc
#घोषणा REV_VENDOR_ID(x)		(((x) & GENMASK(31, 20)) >> 20)
#घोषणा REV_PRODUCT_ID(x)		(((x) & GENMASK(19, 12)) >> 12)
#घोषणा REV_HW(x)			(((x) & GENMASK(11, 8)) >> 8)
#घोषणा REV_MAJOR(x)			(((x) & GENMASK(7, 4)) >> 4)
#घोषणा REV_MINOR(x)			((x) & GENMASK(3, 0))

#घोषणा DSI_OUTPUT_PORT			0
#घोषणा DSI_INPUT_PORT(inputid)		(1 + (inputid))

#घोषणा DSI_HBP_FRAME_OVERHEAD		12
#घोषणा DSI_HSA_FRAME_OVERHEAD		14
#घोषणा DSI_HFP_FRAME_OVERHEAD		6
#घोषणा DSI_HSS_VSS_VSE_FRAME_OVERHEAD	4
#घोषणा DSI_BLANKING_FRAME_OVERHEAD	6
#घोषणा DSI_शून्य_FRAME_OVERHEAD		6
#घोषणा DSI_EOT_PKT_SIZE		4

काष्ठा cdns_dsi_output अणु
	काष्ठा mipi_dsi_device *dev;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	जोड़ phy_configure_opts phy_opts;
पूर्ण;

क्रमागत cdns_dsi_input_id अणु
	CDNS_SDI_INPUT,
	CDNS_DPI_INPUT,
	CDNS_DSC_INPUT,
पूर्ण;

काष्ठा cdns_dsi_cfg अणु
	अचिन्हित पूर्णांक hfp;
	अचिन्हित पूर्णांक hsa;
	अचिन्हित पूर्णांक hbp;
	अचिन्हित पूर्णांक hact;
	अचिन्हित पूर्णांक htotal;
पूर्ण;

काष्ठा cdns_dsi_input अणु
	क्रमागत cdns_dsi_input_id id;
	काष्ठा drm_bridge bridge;
पूर्ण;

काष्ठा cdns_dsi अणु
	काष्ठा mipi_dsi_host base;
	व्योम __iomem *regs;
	काष्ठा cdns_dsi_input input;
	काष्ठा cdns_dsi_output output;
	अचिन्हित पूर्णांक direct_cmd_fअगरo_depth;
	अचिन्हित पूर्णांक rx_fअगरo_depth;
	काष्ठा completion direct_cmd_comp;
	काष्ठा clk *dsi_p_clk;
	काष्ठा reset_control *dsi_p_rst;
	काष्ठा clk *dsi_sys_clk;
	bool link_initialized;
	काष्ठा phy *dphy;
पूर्ण;

अटल अंतरभूत काष्ठा cdns_dsi *input_to_dsi(काष्ठा cdns_dsi_input *input)
अणु
	वापस container_of(input, काष्ठा cdns_dsi, input);
पूर्ण

अटल अंतरभूत काष्ठा cdns_dsi *to_cdns_dsi(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा cdns_dsi, base);
पूर्ण

अटल अंतरभूत काष्ठा cdns_dsi_input *
bridge_to_cdns_dsi_input(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा cdns_dsi_input, bridge);
पूर्ण

अटल अचिन्हित पूर्णांक mode_to_dpi_hfp(स्थिर काष्ठा drm_display_mode *mode,
				    bool mode_valid_check)
अणु
	अगर (mode_valid_check)
		वापस mode->hsync_start - mode->hdisplay;

	वापस mode->crtc_hsync_start - mode->crtc_hdisplay;
पूर्ण

अटल अचिन्हित पूर्णांक dpi_to_dsi_timing(अचिन्हित पूर्णांक dpi_timing,
				      अचिन्हित पूर्णांक dpi_bpp,
				      अचिन्हित पूर्णांक dsi_pkt_overhead)
अणु
	अचिन्हित पूर्णांक dsi_timing = DIV_ROUND_UP(dpi_timing * dpi_bpp, 8);

	अगर (dsi_timing < dsi_pkt_overhead)
		dsi_timing = 0;
	अन्यथा
		dsi_timing -= dsi_pkt_overhead;

	वापस dsi_timing;
पूर्ण

अटल पूर्णांक cdns_dsi_mode2cfg(काष्ठा cdns_dsi *dsi,
			     स्थिर काष्ठा drm_display_mode *mode,
			     काष्ठा cdns_dsi_cfg *dsi_cfg,
			     bool mode_valid_check)
अणु
	काष्ठा cdns_dsi_output *output = &dsi->output;
	अचिन्हित पूर्णांक पंचांगp;
	bool sync_pulse = false;
	पूर्णांक bpp;

	स_रखो(dsi_cfg, 0, माप(*dsi_cfg));

	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		sync_pulse = true;

	bpp = mipi_dsi_pixel_क्रमmat_to_bpp(output->dev->क्रमmat);

	अगर (mode_valid_check)
		पंचांगp = mode->htotal -
		      (sync_pulse ? mode->hsync_end : mode->hsync_start);
	अन्यथा
		पंचांगp = mode->crtc_htotal -
		      (sync_pulse ?
		       mode->crtc_hsync_end : mode->crtc_hsync_start);

	dsi_cfg->hbp = dpi_to_dsi_timing(पंचांगp, bpp, DSI_HBP_FRAME_OVERHEAD);

	अगर (sync_pulse) अणु
		अगर (mode_valid_check)
			पंचांगp = mode->hsync_end - mode->hsync_start;
		अन्यथा
			पंचांगp = mode->crtc_hsync_end - mode->crtc_hsync_start;

		dsi_cfg->hsa = dpi_to_dsi_timing(पंचांगp, bpp,
						 DSI_HSA_FRAME_OVERHEAD);
	पूर्ण

	dsi_cfg->hact = dpi_to_dsi_timing(mode_valid_check ?
					  mode->hdisplay : mode->crtc_hdisplay,
					  bpp, 0);
	dsi_cfg->hfp = dpi_to_dsi_timing(mode_to_dpi_hfp(mode, mode_valid_check),
					 bpp, DSI_HFP_FRAME_OVERHEAD);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dsi_adjust_phy_config(काष्ठा cdns_dsi *dsi,
			      काष्ठा cdns_dsi_cfg *dsi_cfg,
			      काष्ठा phy_configure_opts_mipi_dphy *phy_cfg,
			      स्थिर काष्ठा drm_display_mode *mode,
			      bool mode_valid_check)
अणु
	काष्ठा cdns_dsi_output *output = &dsi->output;
	अचिन्हित दीर्घ दीर्घ dlane_bps;
	अचिन्हित दीर्घ adj_dsi_htotal;
	अचिन्हित दीर्घ dsi_htotal;
	अचिन्हित दीर्घ dpi_htotal;
	अचिन्हित दीर्घ dpi_hz;
	अचिन्हित पूर्णांक dsi_hfp_ext;
	अचिन्हित पूर्णांक lanes = output->dev->lanes;

	dsi_htotal = dsi_cfg->hbp + DSI_HBP_FRAME_OVERHEAD;
	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		dsi_htotal += dsi_cfg->hsa + DSI_HSA_FRAME_OVERHEAD;

	dsi_htotal += dsi_cfg->hact;
	dsi_htotal += dsi_cfg->hfp + DSI_HFP_FRAME_OVERHEAD;

	/*
	 * Make sure DSI htotal is aligned on a lane boundary when calculating
	 * the expected data rate. This is करोne by extending HFP in हाल of
	 * misalignment.
	 */
	adj_dsi_htotal = dsi_htotal;
	अगर (dsi_htotal % lanes)
		adj_dsi_htotal += lanes - (dsi_htotal % lanes);

	dpi_hz = (mode_valid_check ? mode->घड़ी : mode->crtc_घड़ी) * 1000;
	dlane_bps = (अचिन्हित दीर्घ दीर्घ)dpi_hz * adj_dsi_htotal;

	/* data rate in bytes/sec is not an पूर्णांकeger, refuse the mode. */
	dpi_htotal = mode_valid_check ? mode->htotal : mode->crtc_htotal;
	अगर (करो_भाग(dlane_bps, lanes * dpi_htotal))
		वापस -EINVAL;

	/* data rate was in bytes/sec, convert to bits/sec. */
	phy_cfg->hs_clk_rate = dlane_bps * 8;

	dsi_hfp_ext = adj_dsi_htotal - dsi_htotal;
	dsi_cfg->hfp += dsi_hfp_ext;
	dsi_cfg->htotal = dsi_htotal + dsi_hfp_ext;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dsi_check_conf(काष्ठा cdns_dsi *dsi,
			       स्थिर काष्ठा drm_display_mode *mode,
			       काष्ठा cdns_dsi_cfg *dsi_cfg,
			       bool mode_valid_check)
अणु
	काष्ठा cdns_dsi_output *output = &dsi->output;
	काष्ठा phy_configure_opts_mipi_dphy *phy_cfg = &output->phy_opts.mipi_dphy;
	अचिन्हित दीर्घ dsi_hss_hsa_hse_hbp;
	अचिन्हित पूर्णांक nlanes = output->dev->lanes;
	पूर्णांक ret;

	ret = cdns_dsi_mode2cfg(dsi, mode, dsi_cfg, mode_valid_check);
	अगर (ret)
		वापस ret;

	phy_mipi_dphy_get_शेष_config(mode->crtc_घड़ी * 1000,
					 mipi_dsi_pixel_क्रमmat_to_bpp(output->dev->क्रमmat),
					 nlanes, phy_cfg);

	ret = cdns_dsi_adjust_phy_config(dsi, dsi_cfg, phy_cfg, mode, mode_valid_check);
	अगर (ret)
		वापस ret;

	ret = phy_validate(dsi->dphy, PHY_MODE_MIPI_DPHY, 0, &output->phy_opts);
	अगर (ret)
		वापस ret;

	dsi_hss_hsa_hse_hbp = dsi_cfg->hbp + DSI_HBP_FRAME_OVERHEAD;
	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		dsi_hss_hsa_hse_hbp += dsi_cfg->hsa + DSI_HSA_FRAME_OVERHEAD;

	/*
	 * Make sure DPI(HFP) > DSI(HSS+HSA+HSE+HBP) to guarantee that the FIFO
	 * is empty beक्रमe we start a receiving a new line on the DPI
	 * पूर्णांकerface.
	 */
	अगर ((u64)phy_cfg->hs_clk_rate *
	    mode_to_dpi_hfp(mode, mode_valid_check) * nlanes <
	    (u64)dsi_hss_hsa_hse_hbp *
	    (mode_valid_check ? mode->घड़ी : mode->crtc_घड़ी) * 1000)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dsi_bridge_attach(काष्ठा drm_bridge *bridge,
				  क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	काष्ठा cdns_dsi *dsi = input_to_dsi(input);
	काष्ठा cdns_dsi_output *output = &dsi->output;

	अगर (!drm_core_check_feature(bridge->dev, DRIVER_ATOMIC)) अणु
		dev_err(dsi->base.dev,
			"cdns-dsi driver is only compatible with DRM devices supporting atomic updates");
		वापस -ENOTSUPP;
	पूर्ण

	वापस drm_bridge_attach(bridge->encoder, output->bridge, bridge,
				 flags);
पूर्ण

अटल क्रमागत drm_mode_status
cdns_dsi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			   स्थिर काष्ठा drm_display_info *info,
			   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	काष्ठा cdns_dsi *dsi = input_to_dsi(input);
	काष्ठा cdns_dsi_output *output = &dsi->output;
	काष्ठा cdns_dsi_cfg dsi_cfg;
	पूर्णांक bpp, ret;

	/*
	 * VFP_DSI should be less than VFP_DPI and VFP_DSI should be at
	 * least 1.
	 */
	अगर (mode->vtotal - mode->vsync_end < 2)
		वापस MODE_V_ILLEGAL;

	/* VSA_DSI = VSA_DPI and must be at least 2. */
	अगर (mode->vsync_end - mode->vsync_start < 2)
		वापस MODE_V_ILLEGAL;

	/* HACT must be 32-bits aligned. */
	bpp = mipi_dsi_pixel_क्रमmat_to_bpp(output->dev->क्रमmat);
	अगर ((mode->hdisplay * bpp) % 32)
		वापस MODE_H_ILLEGAL;

	ret = cdns_dsi_check_conf(dsi, mode, &dsi_cfg, true);
	अगर (ret)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

अटल व्योम cdns_dsi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	काष्ठा cdns_dsi *dsi = input_to_dsi(input);
	u32 val;

	val = पढ़ोl(dsi->regs + MCTL_MAIN_DATA_CTL);
	val &= ~(IF_VID_SELECT_MASK | IF_VID_MODE | VID_EN | HOST_EOT_GEN |
		 DISP_EOT_GEN);
	ग_लिखोl(val, dsi->regs + MCTL_MAIN_DATA_CTL);

	val = पढ़ोl(dsi->regs + MCTL_MAIN_EN) & ~IF_EN(input->id);
	ग_लिखोl(val, dsi->regs + MCTL_MAIN_EN);
	pm_runसमय_put(dsi->base.dev);
पूर्ण

अटल व्योम cdns_dsi_hs_init(काष्ठा cdns_dsi *dsi)
अणु
	काष्ठा cdns_dsi_output *output = &dsi->output;
	u32 status;

	/*
	 * Power all पूर्णांकernal DPHY blocks करोwn and मुख्यtain their reset line
	 * निश्चितed beक्रमe changing the DPHY config.
	 */
	ग_लिखोl(DPHY_CMN_PSO | DPHY_PLL_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN |
	       DPHY_CMN_PDN | DPHY_PLL_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);

	phy_init(dsi->dphy);
	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configure(dsi->dphy, &output->phy_opts);
	phy_घातer_on(dsi->dphy);

	/* Activate the PLL and रुको until it's locked. */
	ग_लिखोl(PLL_LOCKED, dsi->regs + MCTL_MAIN_STS_CLR);
	ग_लिखोl(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);
	WARN_ON_ONCE(पढ़ोl_poll_समयout(dsi->regs + MCTL_MAIN_STS, status,
					status & PLL_LOCKED, 100, 100));
	/* De-निश्चित data and घड़ी reset lines. */
	ग_लिखोl(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN |
	       DPHY_D_RSTB(output->dev->lanes) | DPHY_C_RSTB,
	       dsi->regs + MCTL_DPHY_CFG0);
पूर्ण

अटल व्योम cdns_dsi_init_link(काष्ठा cdns_dsi *dsi)
अणु
	काष्ठा cdns_dsi_output *output = &dsi->output;
	अचिन्हित दीर्घ sysclk_period, ulpout;
	u32 val;
	पूर्णांक i;

	अगर (dsi->link_initialized)
		वापस;

	val = 0;
	क्रम (i = 1; i < output->dev->lanes; i++)
		val |= DATA_LANE_EN(i);

	अगर (!(output->dev->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		val |= CLK_CONTINUOUS;

	ग_लिखोl(val, dsi->regs + MCTL_MAIN_PHY_CTL);

	/* ULPOUT should be set to 1ms and is expressed in sysclk cycles. */
	sysclk_period = NSEC_PER_SEC / clk_get_rate(dsi->dsi_sys_clk);
	ulpout = DIV_ROUND_UP(NSEC_PER_MSEC, sysclk_period);
	ग_लिखोl(CLK_LANE_ULPOUT_TIME(ulpout) | DATA_LANE_ULPOUT_TIME(ulpout),
	       dsi->regs + MCTL_ULPOUT_TIME);

	ग_लिखोl(LINK_EN, dsi->regs + MCTL_MAIN_DATA_CTL);

	val = CLK_LANE_EN | PLL_START;
	क्रम (i = 0; i < output->dev->lanes; i++)
		val |= DATA_LANE_START(i);

	ग_लिखोl(val, dsi->regs + MCTL_MAIN_EN);

	dsi->link_initialized = true;
पूर्ण

अटल व्योम cdns_dsi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	काष्ठा cdns_dsi *dsi = input_to_dsi(input);
	काष्ठा cdns_dsi_output *output = &dsi->output;
	काष्ठा drm_display_mode *mode;
	काष्ठा phy_configure_opts_mipi_dphy *phy_cfg = &output->phy_opts.mipi_dphy;
	अचिन्हित दीर्घ tx_byte_period;
	काष्ठा cdns_dsi_cfg dsi_cfg;
	u32 पंचांगp, reg_wakeup, भाग;
	पूर्णांक nlanes;

	अगर (WARN_ON(pm_runसमय_get_sync(dsi->base.dev) < 0))
		वापस;

	mode = &bridge->encoder->crtc->state->adjusted_mode;
	nlanes = output->dev->lanes;

	WARN_ON_ONCE(cdns_dsi_check_conf(dsi, mode, &dsi_cfg, false));

	cdns_dsi_hs_init(dsi);
	cdns_dsi_init_link(dsi);

	ग_लिखोl(HBP_LEN(dsi_cfg.hbp) | HSA_LEN(dsi_cfg.hsa),
	       dsi->regs + VID_HSIZE1);
	ग_लिखोl(HFP_LEN(dsi_cfg.hfp) | HACT_LEN(dsi_cfg.hact),
	       dsi->regs + VID_HSIZE2);

	ग_लिखोl(VBP_LEN(mode->crtc_vtotal - mode->crtc_vsync_end - 1) |
	       VFP_LEN(mode->crtc_vsync_start - mode->crtc_vdisplay) |
	       VSA_LEN(mode->crtc_vsync_end - mode->crtc_vsync_start + 1),
	       dsi->regs + VID_VSIZE1);
	ग_लिखोl(mode->crtc_vdisplay, dsi->regs + VID_VSIZE2);

	पंचांगp = dsi_cfg.htotal -
	      (dsi_cfg.hsa + DSI_BLANKING_FRAME_OVERHEAD +
	       DSI_HSA_FRAME_OVERHEAD);
	ग_लिखोl(BLK_LINE_PULSE_PKT_LEN(पंचांगp), dsi->regs + VID_BLKSIZE2);
	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		ग_लिखोl(MAX_LINE_LIMIT(पंचांगp - DSI_शून्य_FRAME_OVERHEAD),
		       dsi->regs + VID_VCA_SETTING2);

	पंचांगp = dsi_cfg.htotal -
	      (DSI_HSS_VSS_VSE_FRAME_OVERHEAD + DSI_BLANKING_FRAME_OVERHEAD);
	ग_लिखोl(BLK_LINE_EVENT_PKT_LEN(पंचांगp), dsi->regs + VID_BLKSIZE1);
	अगर (!(output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE))
		ग_लिखोl(MAX_LINE_LIMIT(पंचांगp - DSI_शून्य_FRAME_OVERHEAD),
		       dsi->regs + VID_VCA_SETTING2);

	पंचांगp = DIV_ROUND_UP(dsi_cfg.htotal, nlanes) -
	      DIV_ROUND_UP(dsi_cfg.hsa, nlanes);

	अगर (!(output->dev->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		पंचांगp -= DIV_ROUND_UP(DSI_EOT_PKT_SIZE, nlanes);

	tx_byte_period = DIV_ROUND_DOWN_ULL((u64)NSEC_PER_SEC * 8,
					    phy_cfg->hs_clk_rate);
	reg_wakeup = (phy_cfg->hs_prepare + phy_cfg->hs_zero) / tx_byte_period;
	ग_लिखोl(REG_WAKEUP_TIME(reg_wakeup) | REG_LINE_DURATION(पंचांगp),
	       dsi->regs + VID_DPHY_TIME);

	/*
	 * HSTX and LPRX समयouts are both expressed in TX byte clk cycles and
	 * both should be set to at least the समय it takes to transmit a
	 * frame.
	 */
	पंचांगp = NSEC_PER_SEC / drm_mode_vrefresh(mode);
	पंचांगp /= tx_byte_period;

	क्रम (भाग = 0; भाग <= CLK_DIV_MAX; भाग++) अणु
		अगर (पंचांगp <= HSTX_TIMEOUT_MAX)
			अवरोध;

		पंचांगp >>= 1;
	पूर्ण

	अगर (पंचांगp > HSTX_TIMEOUT_MAX)
		पंचांगp = HSTX_TIMEOUT_MAX;

	ग_लिखोl(CLK_DIV(भाग) | HSTX_TIMEOUT(पंचांगp),
	       dsi->regs + MCTL_DPHY_TIMEOUT1);

	ग_लिखोl(LPRX_TIMEOUT(पंचांगp), dsi->regs + MCTL_DPHY_TIMEOUT2);

	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		चयन (output->dev->क्रमmat) अणु
		हाल MIPI_DSI_FMT_RGB888:
			पंचांगp = VID_PIXEL_MODE_RGB888 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_24);
			अवरोध;

		हाल MIPI_DSI_FMT_RGB666:
			पंचांगp = VID_PIXEL_MODE_RGB666 |
			      VID_DATATYPE(MIPI_DSI_PIXEL_STREAM_3BYTE_18);
			अवरोध;

		हाल MIPI_DSI_FMT_RGB666_PACKED:
			पंचांगp = VID_PIXEL_MODE_RGB666_PACKED |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_18);
			अवरोध;

		हाल MIPI_DSI_FMT_RGB565:
			पंचांगp = VID_PIXEL_MODE_RGB565 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEL_STREAM_16);
			अवरोध;

		शेष:
			dev_err(dsi->base.dev, "Unsupported DSI format\n");
			वापस;
		पूर्ण

		अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
			पंचांगp |= SYNC_PULSE_ACTIVE | SYNC_PULSE_HORIZONTAL;

		पंचांगp |= REG_BLKLINE_MODE(REG_BLK_MODE_BLANKING_PKT) |
		       REG_BLKEOL_MODE(REG_BLK_MODE_BLANKING_PKT) |
		       RECOVERY_MODE(RECOVERY_MODE_NEXT_HSYNC) |
		       VID_IGNORE_MISS_VSYNC;

		ग_लिखोl(पंचांगp, dsi->regs + VID_MAIN_CTL);
	पूर्ण

	पंचांगp = पढ़ोl(dsi->regs + MCTL_MAIN_DATA_CTL);
	पंचांगp &= ~(IF_VID_SELECT_MASK | HOST_EOT_GEN | IF_VID_MODE);

	अगर (!(output->dev->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		पंचांगp |= HOST_EOT_GEN;

	अगर (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO)
		पंचांगp |= IF_VID_MODE | IF_VID_SELECT(input->id) | VID_EN;

	ग_लिखोl(पंचांगp, dsi->regs + MCTL_MAIN_DATA_CTL);

	पंचांगp = पढ़ोl(dsi->regs + MCTL_MAIN_EN) | IF_EN(input->id);
	ग_लिखोl(पंचांगp, dsi->regs + MCTL_MAIN_EN);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs cdns_dsi_bridge_funcs = अणु
	.attach = cdns_dsi_bridge_attach,
	.mode_valid = cdns_dsi_bridge_mode_valid,
	.disable = cdns_dsi_bridge_disable,
	.enable = cdns_dsi_bridge_enable,
पूर्ण;

अटल पूर्णांक cdns_dsi_attach(काष्ठा mipi_dsi_host *host,
			   काष्ठा mipi_dsi_device *dev)
अणु
	काष्ठा cdns_dsi *dsi = to_cdns_dsi(host);
	काष्ठा cdns_dsi_output *output = &dsi->output;
	काष्ठा cdns_dsi_input *input = &dsi->input;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	काष्ठा device_node *np;
	पूर्णांक ret;

	/*
	 * We currently करो not support connecting several DSI devices to the
	 * same host. In order to support that we'd need the DRM bridge
	 * framework to allow dynamic reconfiguration of the bridge chain.
	 */
	अगर (output->dev)
		वापस -EBUSY;

	/* We करो not support burst mode yet. */
	अगर (dev->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		वापस -ENOTSUPP;

	/*
	 * The host <-> device link might be described using an OF-graph
	 * representation, in this हाल we extract the device of_node from
	 * this representation, otherwise we use dsidev->dev.of_node which
	 * should have been filled by the core.
	 */
	np = of_graph_get_remote_node(dsi->base.dev->of_node, DSI_OUTPUT_PORT,
				      dev->channel);
	अगर (!np)
		np = of_node_get(dev->dev.of_node);

	panel = of_drm_find_panel(np);
	अगर (!IS_ERR(panel)) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_DSI);
	पूर्ण अन्यथा अणु
		bridge = of_drm_find_bridge(dev->dev.of_node);
		अगर (!bridge)
			bridge = ERR_PTR(-EINVAL);
	पूर्ण

	of_node_put(np);

	अगर (IS_ERR(bridge)) अणु
		ret = PTR_ERR(bridge);
		dev_err(host->dev, "failed to add DSI device %s (err = %d)",
			dev->name, ret);
		वापस ret;
	पूर्ण

	output->dev = dev;
	output->bridge = bridge;
	output->panel = panel;

	/*
	 * The DSI output has been properly configured, we can now safely
	 * रेजिस्टर the input to the bridge framework so that it can take place
	 * in a display pipeline.
	 */
	drm_bridge_add(&input->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dsi_detach(काष्ठा mipi_dsi_host *host,
			   काष्ठा mipi_dsi_device *dev)
अणु
	काष्ठा cdns_dsi *dsi = to_cdns_dsi(host);
	काष्ठा cdns_dsi_output *output = &dsi->output;
	काष्ठा cdns_dsi_input *input = &dsi->input;

	drm_bridge_हटाओ(&input->bridge);
	अगर (output->panel)
		drm_panel_bridge_हटाओ(output->bridge);

	वापस 0;
पूर्ण

अटल irqवापस_t cdns_dsi_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns_dsi *dsi = data;
	irqवापस_t ret = IRQ_NONE;
	u32 flag, ctl;

	flag = पढ़ोl(dsi->regs + सूचीECT_CMD_STS_FLAG);
	अगर (flag) अणु
		ctl = पढ़ोl(dsi->regs + सूचीECT_CMD_STS_CTL);
		ctl &= ~flag;
		ग_लिखोl(ctl, dsi->regs + सूचीECT_CMD_STS_CTL);
		complete(&dsi->direct_cmd_comp);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cdns_dsi_transfer(काष्ठा mipi_dsi_host *host,
				 स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा cdns_dsi *dsi = to_cdns_dsi(host);
	u32 cmd, sts, val, रुको = WRITE_COMPLETED, ctl = 0;
	काष्ठा mipi_dsi_packet packet;
	पूर्णांक ret, i, tx_len, rx_len;

	ret = pm_runसमय_get_sync(host->dev);
	अगर (ret < 0)
		वापस ret;

	cdns_dsi_init_link(dsi);

	ret = mipi_dsi_create_packet(&packet, msg);
	अगर (ret)
		जाओ out;

	tx_len = msg->tx_buf ? msg->tx_len : 0;
	rx_len = msg->rx_buf ? msg->rx_len : 0;

	/* For पढ़ो operations, the maximum TX len is 2. */
	अगर (rx_len && tx_len > 2) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	/* TX len is limited by the CMD FIFO depth. */
	अगर (tx_len > dsi->direct_cmd_fअगरo_depth) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	/* RX len is limited by the RX FIFO depth. */
	अगर (rx_len > dsi->rx_fअगरo_depth) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	cmd = CMD_SIZE(tx_len) | CMD_VCHAN_ID(msg->channel) |
	      CMD_DATATYPE(msg->type);

	अगर (msg->flags & MIPI_DSI_MSG_USE_LPM)
		cmd |= CMD_LP_EN;

	अगर (mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type))
		cmd |= CMD_LONG;

	अगर (rx_len) अणु
		cmd |= READ_CMD;
		रुको = READ_COMPLETED_WITH_ERR | READ_COMPLETED;
		ctl = READ_EN | BTA_EN;
	पूर्ण अन्यथा अगर (msg->flags & MIPI_DSI_MSG_REQ_ACK) अणु
		cmd |= BTA_REQ;
		रुको = ACK_WITH_ERR_RCVD | ACK_RCVD;
		ctl = BTA_EN;
	पूर्ण

	ग_लिखोl(पढ़ोl(dsi->regs + MCTL_MAIN_DATA_CTL) | ctl,
	       dsi->regs + MCTL_MAIN_DATA_CTL);

	ग_लिखोl(cmd, dsi->regs + सूचीECT_CMD_MAIN_SETTINGS);

	क्रम (i = 0; i < tx_len; i += 4) अणु
		स्थिर u8 *buf = msg->tx_buf;
		पूर्णांक j;

		val = 0;
		क्रम (j = 0; j < 4 && j + i < tx_len; j++)
			val |= (u32)buf[i + j] << (8 * j);

		ग_लिखोl(val, dsi->regs + सूचीECT_CMD_WRDATA);
	पूर्ण

	/* Clear status flags beक्रमe sending the command. */
	ग_लिखोl(रुको, dsi->regs + सूचीECT_CMD_STS_CLR);
	ग_लिखोl(रुको, dsi->regs + सूचीECT_CMD_STS_CTL);
	reinit_completion(&dsi->direct_cmd_comp);
	ग_लिखोl(0, dsi->regs + सूचीECT_CMD_SEND);

	रुको_क्रम_completion_समयout(&dsi->direct_cmd_comp,
				    msecs_to_jअगरfies(1000));

	sts = पढ़ोl(dsi->regs + सूचीECT_CMD_STS);
	ग_लिखोl(रुको, dsi->regs + सूचीECT_CMD_STS_CLR);
	ग_लिखोl(0, dsi->regs + सूचीECT_CMD_STS_CTL);

	ग_लिखोl(पढ़ोl(dsi->regs + MCTL_MAIN_DATA_CTL) & ~ctl,
	       dsi->regs + MCTL_MAIN_DATA_CTL);

	/* We did not receive the events we were रुकोing क्रम. */
	अगर (!(sts & रुको)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* 'READ' or 'WRITE with ACK' failed. */
	अगर (sts & (READ_COMPLETED_WITH_ERR | ACK_WITH_ERR_RCVD)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < rx_len; i += 4) अणु
		u8 *buf = msg->rx_buf;
		पूर्णांक j;

		val = पढ़ोl(dsi->regs + सूचीECT_CMD_RDDATA);
		क्रम (j = 0; j < 4 && j + i < rx_len; j++)
			buf[i + j] = val >> (8 * j);
	पूर्ण

out:
	pm_runसमय_put(host->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops cdns_dsi_ops = अणु
	.attach = cdns_dsi_attach,
	.detach = cdns_dsi_detach,
	.transfer = cdns_dsi_transfer,
पूर्ण;

अटल पूर्णांक __maybe_unused cdns_dsi_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns_dsi *dsi = dev_get_drvdata(dev);

	reset_control_deनिश्चित(dsi->dsi_p_rst);
	clk_prepare_enable(dsi->dsi_p_clk);
	clk_prepare_enable(dsi->dsi_sys_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cdns_dsi_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns_dsi *dsi = dev_get_drvdata(dev);

	clk_disable_unprepare(dsi->dsi_sys_clk);
	clk_disable_unprepare(dsi->dsi_p_clk);
	reset_control_निश्चित(dsi->dsi_p_rst);
	dsi->link_initialized = false;
	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(cdns_dsi_pm_ops, cdns_dsi_suspend, cdns_dsi_resume,
			    शून्य);

अटल पूर्णांक cdns_dsi_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_dsi *dsi;
	काष्ठा cdns_dsi_input *input;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	u32 val;

	dsi = devm_kzalloc(&pdev->dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dsi);

	input = &dsi->input;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dsi->regs))
		वापस PTR_ERR(dsi->regs);

	dsi->dsi_p_clk = devm_clk_get(&pdev->dev, "dsi_p_clk");
	अगर (IS_ERR(dsi->dsi_p_clk))
		वापस PTR_ERR(dsi->dsi_p_clk);

	dsi->dsi_p_rst = devm_reset_control_get_optional_exclusive(&pdev->dev,
								"dsi_p_rst");
	अगर (IS_ERR(dsi->dsi_p_rst))
		वापस PTR_ERR(dsi->dsi_p_rst);

	dsi->dsi_sys_clk = devm_clk_get(&pdev->dev, "dsi_sys_clk");
	अगर (IS_ERR(dsi->dsi_sys_clk))
		वापस PTR_ERR(dsi->dsi_sys_clk);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	dsi->dphy = devm_phy_get(&pdev->dev, "dphy");
	अगर (IS_ERR(dsi->dphy))
		वापस PTR_ERR(dsi->dphy);

	ret = clk_prepare_enable(dsi->dsi_p_clk);
	अगर (ret)
		वापस ret;

	val = पढ़ोl(dsi->regs + ID_REG);
	अगर (REV_VENDOR_ID(val) != 0xcad) अणु
		dev_err(&pdev->dev, "invalid vendor id\n");
		ret = -EINVAL;
		जाओ err_disable_pclk;
	पूर्ण

	val = पढ़ोl(dsi->regs + IP_CONF);
	dsi->direct_cmd_fअगरo_depth = 1 << (सूचीCMD_FIFO_DEPTH(val) + 2);
	dsi->rx_fअगरo_depth = RX_FIFO_DEPTH(val);
	init_completion(&dsi->direct_cmd_comp);

	ग_लिखोl(0, dsi->regs + MCTL_MAIN_DATA_CTL);
	ग_लिखोl(0, dsi->regs + MCTL_MAIN_EN);
	ग_लिखोl(0, dsi->regs + MCTL_MAIN_PHY_CTL);

	/*
	 * We only support the DPI input, so क्रमce input->id to
	 * CDNS_DPI_INPUT.
	 */
	input->id = CDNS_DPI_INPUT;
	input->bridge.funcs = &cdns_dsi_bridge_funcs;
	input->bridge.of_node = pdev->dev.of_node;

	/* Mask all पूर्णांकerrupts beक्रमe रेजिस्टरing the IRQ handler. */
	ग_लिखोl(0, dsi->regs + MCTL_MAIN_STS_CTL);
	ग_लिखोl(0, dsi->regs + MCTL_DPHY_ERR_CTL1);
	ग_लिखोl(0, dsi->regs + CMD_MODE_STS_CTL);
	ग_लिखोl(0, dsi->regs + सूचीECT_CMD_STS_CTL);
	ग_लिखोl(0, dsi->regs + सूचीECT_CMD_RD_STS_CTL);
	ग_लिखोl(0, dsi->regs + VID_MODE_STS_CTL);
	ग_लिखोl(0, dsi->regs + TVG_STS_CTL);
	ग_लिखोl(0, dsi->regs + DPI_IRQ_EN);
	ret = devm_request_irq(&pdev->dev, irq, cdns_dsi_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), dsi);
	अगर (ret)
		जाओ err_disable_pclk;

	pm_runसमय_enable(&pdev->dev);
	dsi->base.dev = &pdev->dev;
	dsi->base.ops = &cdns_dsi_ops;

	ret = mipi_dsi_host_रेजिस्टर(&dsi->base);
	अगर (ret)
		जाओ err_disable_runसमय_pm;

	clk_disable_unprepare(dsi->dsi_p_clk);

	वापस 0;

err_disable_runसमय_pm:
	pm_runसमय_disable(&pdev->dev);

err_disable_pclk:
	clk_disable_unprepare(dsi->dsi_p_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_dsi_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_dsi *dsi = platक्रमm_get_drvdata(pdev);

	mipi_dsi_host_unरेजिस्टर(&dsi->base);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cdns_dsi_of_match[] = अणु
	अणु .compatible = "cdns,dsi" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver cdns_dsi_platक्रमm_driver = अणु
	.probe  = cdns_dsi_drm_probe,
	.हटाओ = cdns_dsi_drm_हटाओ,
	.driver = अणु
		.name   = "cdns-dsi",
		.of_match_table = cdns_dsi_of_match,
		.pm = &cdns_dsi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cdns_dsi_platक्रमm_driver);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@bootlin.com>");
MODULE_DESCRIPTION("Cadence DSI driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cdns-dsi");

