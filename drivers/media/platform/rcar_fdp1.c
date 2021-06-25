<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Renesas R-Car Fine Display Processor
 *
 * Video क्रमmat converter and frame deपूर्णांकerlacer device.
 *
 * Author: Kieran Bingham, <kieran@bingham.xyz>
 * Copyright (c) 2016 Renesas Electronics Corporation.
 *
 * This code is developed and inspired from the vim2m, rcar_jpu,
 * m2m-deपूर्णांकerlace, and vsp1 drivers.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <media/rcar-fcp.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

अटल अचिन्हित पूर्णांक debug;
module_param(debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "activate debug info");

/* Minimum and maximum frame width/height */
#घोषणा FDP1_MIN_W		80U
#घोषणा FDP1_MIN_H		80U

#घोषणा FDP1_MAX_W		3840U
#घोषणा FDP1_MAX_H		2160U

#घोषणा FDP1_MAX_PLANES		3U
#घोषणा FDP1_MAX_STRIDE		8190U

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा FDP1_CAPTURE		BIT(0)
#घोषणा FDP1_OUTPUT		BIT(1)

#घोषणा DRIVER_NAME		"rcar_fdp1"

/* Number of Job's to have available on the processing queue */
#घोषणा FDP1_NUMBER_JOBS 8

#घोषणा dprपूर्णांकk(fdp1, fmt, arg...) \
	v4l2_dbg(1, debug, &fdp1->v4l2_dev, "%s: " fmt, __func__, ## arg)

/*
 * FDP1 रेजिस्टरs and bits
 */

/* FDP1 start रेजिस्टर - Imm */
#घोषणा FD1_CTL_CMD			0x0000
#घोषणा FD1_CTL_CMD_STRCMD		BIT(0)

/* Sync generator रेजिस्टर - Imm */
#घोषणा FD1_CTL_SGCMD			0x0004
#घोषणा FD1_CTL_SGCMD_SGEN		BIT(0)

/* Register set end रेजिस्टर - Imm */
#घोषणा FD1_CTL_REGEND			0x0008
#घोषणा FD1_CTL_REGEND_REGEND		BIT(0)

/* Channel activation रेजिस्टर - Vupdt */
#घोषणा FD1_CTL_CHACT			0x000c
#घोषणा FD1_CTL_CHACT_SMW		BIT(9)
#घोषणा FD1_CTL_CHACT_WR		BIT(8)
#घोषणा FD1_CTL_CHACT_SMR		BIT(3)
#घोषणा FD1_CTL_CHACT_RD2		BIT(2)
#घोषणा FD1_CTL_CHACT_RD1		BIT(1)
#घोषणा FD1_CTL_CHACT_RD0		BIT(0)

/* Operation Mode Register - Vupdt */
#घोषणा FD1_CTL_OPMODE			0x0010
#घोषणा FD1_CTL_OPMODE_PRG		BIT(4)
#घोषणा FD1_CTL_OPMODE_VIMD_INTERRUPT	(0 << 0)
#घोषणा FD1_CTL_OPMODE_VIMD_BESTEFFORT	(1 << 0)
#घोषणा FD1_CTL_OPMODE_VIMD_NOINTERRUPT	(2 << 0)

#घोषणा FD1_CTL_VPERIOD			0x0014
#घोषणा FD1_CTL_CLKCTRL			0x0018
#घोषणा FD1_CTL_CLKCTRL_CSTP_N		BIT(0)

/* Software reset रेजिस्टर */
#घोषणा FD1_CTL_SRESET			0x001c
#घोषणा FD1_CTL_SRESET_SRST		BIT(0)

/* Control status रेजिस्टर (V-update-status) */
#घोषणा FD1_CTL_STATUS			0x0024
#घोषणा FD1_CTL_STATUS_VINT_CNT_MASK	GENMASK(31, 16)
#घोषणा FD1_CTL_STATUS_VINT_CNT_SHIFT	16
#घोषणा FD1_CTL_STATUS_SGREGSET		BIT(10)
#घोषणा FD1_CTL_STATUS_SGVERR		BIT(9)
#घोषणा FD1_CTL_STATUS_SGFREND		BIT(8)
#घोषणा FD1_CTL_STATUS_BSY		BIT(0)

#घोषणा FD1_CTL_VCYCLE_STAT		0x0028

/* Interrupt enable रेजिस्टर */
#घोषणा FD1_CTL_IRQENB			0x0038
/* Interrupt status रेजिस्टर */
#घोषणा FD1_CTL_IRQSTA			0x003c
/* Interrupt control रेजिस्टर */
#घोषणा FD1_CTL_IRQFSET			0x0040

/* Common IRQ Bit settings */
#घोषणा FD1_CTL_IRQ_VERE		BIT(16)
#घोषणा FD1_CTL_IRQ_VINTE		BIT(4)
#घोषणा FD1_CTL_IRQ_FREE		BIT(0)
#घोषणा FD1_CTL_IRQ_MASK		(FD1_CTL_IRQ_VERE | \
					 FD1_CTL_IRQ_VINTE | \
					 FD1_CTL_IRQ_FREE)

/* RPF */
#घोषणा FD1_RPF_SIZE			0x0060
#घोषणा FD1_RPF_SIZE_MASK		GENMASK(12, 0)
#घोषणा FD1_RPF_SIZE_H_SHIFT		16
#घोषणा FD1_RPF_SIZE_V_SHIFT		0

#घोषणा FD1_RPF_FORMAT			0x0064
#घोषणा FD1_RPF_FORMAT_CIPM		BIT(16)
#घोषणा FD1_RPF_FORMAT_RSPYCS		BIT(13)
#घोषणा FD1_RPF_FORMAT_RSPUVS		BIT(12)
#घोषणा FD1_RPF_FORMAT_CF		BIT(8)

#घोषणा FD1_RPF_PSTRIDE			0x0068
#घोषणा FD1_RPF_PSTRIDE_Y_SHIFT		16
#घोषणा FD1_RPF_PSTRIDE_C_SHIFT		0

/* RPF0 Source Component Y Address रेजिस्टर */
#घोषणा FD1_RPF0_ADDR_Y			0x006c

/* RPF1 Current Picture Registers */
#घोषणा FD1_RPF1_ADDR_Y			0x0078
#घोषणा FD1_RPF1_ADDR_C0		0x007c
#घोषणा FD1_RPF1_ADDR_C1		0x0080

/* RPF2 next picture रेजिस्टर */
#घोषणा FD1_RPF2_ADDR_Y			0x0084

#घोषणा FD1_RPF_SMSK_ADDR		0x0090
#घोषणा FD1_RPF_SWAP			0x0094

/* WPF */
#घोषणा FD1_WPF_FORMAT			0x00c0
#घोषणा FD1_WPF_FORMAT_PDV_SHIFT	24
#घोषणा FD1_WPF_FORMAT_FCNL		BIT(20)
#घोषणा FD1_WPF_FORMAT_WSPYCS		BIT(15)
#घोषणा FD1_WPF_FORMAT_WSPUVS		BIT(14)
#घोषणा FD1_WPF_FORMAT_WRTM_601_16	(0 << 9)
#घोषणा FD1_WPF_FORMAT_WRTM_601_0	(1 << 9)
#घोषणा FD1_WPF_FORMAT_WRTM_709_16	(2 << 9)
#घोषणा FD1_WPF_FORMAT_CSC		BIT(8)

#घोषणा FD1_WPF_RNDCTL			0x00c4
#घोषणा FD1_WPF_RNDCTL_CBRM		BIT(28)
#घोषणा FD1_WPF_RNDCTL_CLMD_NOCLIP	(0 << 12)
#घोषणा FD1_WPF_RNDCTL_CLMD_CLIP_16_235	(1 << 12)
#घोषणा FD1_WPF_RNDCTL_CLMD_CLIP_1_254	(2 << 12)

#घोषणा FD1_WPF_PSTRIDE			0x00c8
#घोषणा FD1_WPF_PSTRIDE_Y_SHIFT		16
#घोषणा FD1_WPF_PSTRIDE_C_SHIFT		0

/* WPF Destination picture */
#घोषणा FD1_WPF_ADDR_Y			0x00cc
#घोषणा FD1_WPF_ADDR_C0			0x00d0
#घोषणा FD1_WPF_ADDR_C1			0x00d4
#घोषणा FD1_WPF_SWAP			0x00d8
#घोषणा FD1_WPF_SWAP_OSWAP_SHIFT	0
#घोषणा FD1_WPF_SWAP_SSWAP_SHIFT	4

/* WPF/RPF Common */
#घोषणा FD1_RWPF_SWAP_BYTE		BIT(0)
#घोषणा FD1_RWPF_SWAP_WORD		BIT(1)
#घोषणा FD1_RWPF_SWAP_LWRD		BIT(2)
#घोषणा FD1_RWPF_SWAP_LLWD		BIT(3)

/* IPC */
#घोषणा FD1_IPC_MODE			0x0100
#घोषणा FD1_IPC_MODE_DLI		BIT(8)
#घोषणा FD1_IPC_MODE_DIM_ADAPT2D3D	(0 << 0)
#घोषणा FD1_IPC_MODE_DIM_FIXED2D	(1 << 0)
#घोषणा FD1_IPC_MODE_DIM_FIXED3D	(2 << 0)
#घोषणा FD1_IPC_MODE_DIM_PREVFIELD	(3 << 0)
#घोषणा FD1_IPC_MODE_DIM_NEXTFIELD	(4 << 0)

#घोषणा FD1_IPC_SMSK_THRESH		0x0104
#घोषणा FD1_IPC_SMSK_THRESH_CONST	0x00010002

#घोषणा FD1_IPC_COMB_DET		0x0108
#घोषणा FD1_IPC_COMB_DET_CONST		0x00200040

#घोषणा FD1_IPC_MOTDEC			0x010c
#घोषणा FD1_IPC_MOTDEC_CONST		0x00008020

/* DLI रेजिस्टरs */
#घोषणा FD1_IPC_DLI_BLEND		0x0120
#घोषणा FD1_IPC_DLI_BLEND_CONST		0x0080ff02

#घोषणा FD1_IPC_DLI_HGAIN		0x0124
#घोषणा FD1_IPC_DLI_HGAIN_CONST		0x001000ff

#घोषणा FD1_IPC_DLI_SPRS		0x0128
#घोषणा FD1_IPC_DLI_SPRS_CONST		0x009004ff

#घोषणा FD1_IPC_DLI_ANGLE		0x012c
#घोषणा FD1_IPC_DLI_ANGLE_CONST		0x0004080c

#घोषणा FD1_IPC_DLI_ISOPIX0		0x0130
#घोषणा FD1_IPC_DLI_ISOPIX0_CONST	0xff10ff10

#घोषणा FD1_IPC_DLI_ISOPIX1		0x0134
#घोषणा FD1_IPC_DLI_ISOPIX1_CONST	0x0000ff10

/* Sensor रेजिस्टरs */
#घोषणा FD1_IPC_SENSOR_TH0		0x0140
#घोषणा FD1_IPC_SENSOR_TH0_CONST	0x20208080

#घोषणा FD1_IPC_SENSOR_TH1		0x0144
#घोषणा FD1_IPC_SENSOR_TH1_CONST	0

#घोषणा FD1_IPC_SENSOR_CTL0		0x0170
#घोषणा FD1_IPC_SENSOR_CTL0_CONST	0x00002201

#घोषणा FD1_IPC_SENSOR_CTL1		0x0174
#घोषणा FD1_IPC_SENSOR_CTL1_CONST	0

#घोषणा FD1_IPC_SENSOR_CTL2		0x0178
#घोषणा FD1_IPC_SENSOR_CTL2_X_SHIFT	16
#घोषणा FD1_IPC_SENSOR_CTL2_Y_SHIFT	0

#घोषणा FD1_IPC_SENSOR_CTL3		0x017c
#घोषणा FD1_IPC_SENSOR_CTL3_0_SHIFT	16
#घोषणा FD1_IPC_SENSOR_CTL3_1_SHIFT	0

/* Line memory pixel number रेजिस्टर */
#घोषणा FD1_IPC_LMEM			0x01e0
#घोषणा FD1_IPC_LMEM_LINEAR		1024
#घोषणा FD1_IPC_LMEM_TILE		960

/* Internal Data (HW Version) */
#घोषणा FD1_IP_INTDATA			0x0800
#घोषणा FD1_IP_H3_ES1			0x02010101
#घोषणा FD1_IP_M3W			0x02010202
#घोषणा FD1_IP_H3			0x02010203
#घोषणा FD1_IP_M3N			0x02010204
#घोषणा FD1_IP_E3			0x02010205

/* LUTs */
#घोषणा FD1_LUT_DIF_ADJ			0x1000
#घोषणा FD1_LUT_SAD_ADJ			0x1400
#घोषणा FD1_LUT_BLD_GAIN		0x1800
#घोषणा FD1_LUT_DIF_GAIN		0x1c00
#घोषणा FD1_LUT_MDET			0x2000

/**
 * काष्ठा fdp1_fmt - The FDP1 पूर्णांकernal क्रमmat data
 * @fourcc: the fourcc code, to match the V4L2 API
 * @bpp: bits per pixel per plane
 * @num_planes: number of planes
 * @hsub: horizontal subsampling factor
 * @vsub: vertical subsampling factor
 * @fmt: 7-bit क्रमmat code क्रम the fdp1 hardware
 * @swap_yc: the Y and C components are swapped (Y comes beक्रमe C)
 * @swap_uv: the U and V components are swapped (V comes beक्रमe U)
 * @swap: swap रेजिस्टर control
 * @types: types of queue this क्रमmat is applicable to
 */
काष्ठा fdp1_fmt अणु
	u32	fourcc;
	u8	bpp[3];
	u8	num_planes;
	u8	hsub;
	u8	vsub;
	u8	fmt;
	bool	swap_yc;
	bool	swap_uv;
	u8	swap;
	u8	types;
पूर्ण;

अटल स्थिर काष्ठा fdp1_fmt fdp1_क्रमmats[] = अणु
	/* RGB क्रमmats are only supported by the Write Pixel Formatter */

	अणु V4L2_PIX_FMT_RGB332, अणु 8, 0, 0 पूर्ण, 1, 1, 1, 0x00, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_XRGB444, अणु 16, 0, 0 पूर्ण, 1, 1, 1, 0x01, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_XRGB555, अणु 16, 0, 0 पूर्ण, 1, 1, 1, 0x04, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_RGB565, अणु 16, 0, 0 पूर्ण, 1, 1, 1, 0x06, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_ABGR32, अणु 32, 0, 0 पूर्ण, 1, 1, 1, 0x13, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_XBGR32, अणु 32, 0, 0 पूर्ण, 1, 1, 1, 0x13, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_ARGB32, अणु 32, 0, 0 पूर्ण, 1, 1, 1, 0x13, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_XRGB32, अणु 32, 0, 0 पूर्ण, 1, 1, 1, 0x13, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_RGB24, अणु 24, 0, 0 पूर्ण, 1, 1, 1, 0x15, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_BGR24, अणु 24, 0, 0 पूर्ण, 1, 1, 1, 0x18, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_ARGB444, अणु 16, 0, 0 पूर्ण, 1, 1, 1, 0x19, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD,
	  FDP1_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_ARGB555, अणु 16, 0, 0 पूर्ण, 1, 1, 1, 0x1b, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD,
	  FDP1_CAPTURE पूर्ण,

	/* YUV Formats are supported by Read and Write Pixel Formatters */

	अणु V4L2_PIX_FMT_NV16M, अणु 8, 16, 0 पूर्ण, 2, 2, 1, 0x41, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_NV61M, अणु 8, 16, 0 पूर्ण, 2, 2, 1, 0x41, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_NV12M, अणु 8, 16, 0 पूर्ण, 2, 2, 2, 0x42, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_NV21M, अणु 8, 16, 0 पूर्ण, 2, 2, 2, 0x42, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_UYVY, अणु 16, 0, 0 पूर्ण, 1, 2, 1, 0x47, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_VYUY, अणु 16, 0, 0 पूर्ण, 1, 2, 1, 0x47, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YUYV, अणु 16, 0, 0 पूर्ण, 1, 2, 1, 0x47, true, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YVYU, अणु 16, 0, 0 पूर्ण, 1, 2, 1, 0x47, true, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YUV444M, अणु 8, 8, 8 पूर्ण, 3, 1, 1, 0x4a, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YVU444M, अणु 8, 8, 8 पूर्ण, 3, 1, 1, 0x4a, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YUV422M, अणु 8, 8, 8 पूर्ण, 3, 2, 1, 0x4b, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YVU422M, अणु 8, 8, 8 पूर्ण, 3, 2, 1, 0x4b, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YUV420M, अणु 8, 8, 8 पूर्ण, 3, 2, 2, 0x4c, false, false,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_YVU420M, अणु 8, 8, 8 पूर्ण, 3, 2, 2, 0x4c, false, true,
	  FD1_RWPF_SWAP_LLWD | FD1_RWPF_SWAP_LWRD |
	  FD1_RWPF_SWAP_WORD | FD1_RWPF_SWAP_BYTE,
	  FDP1_CAPTURE | FDP1_OUTPUT पूर्ण,
पूर्ण;

अटल पूर्णांक fdp1_fmt_is_rgb(स्थिर काष्ठा fdp1_fmt *fmt)
अणु
	वापस fmt->fmt <= 0x1b; /* Last RGB code */
पूर्ण

/*
 * FDP1 Lookup tables range from 0...255 only
 *
 * Each table must be less than 256 entries, and all tables
 * are padded out to 256 entries by duplicating the last value.
 */
अटल स्थिर u8 fdp1_dअगरf_adj[] = अणु
	0x00, 0x24, 0x43, 0x5e, 0x76, 0x8c, 0x9e, 0xaf,
	0xbd, 0xc9, 0xd4, 0xdd, 0xe4, 0xea, 0xef, 0xf3,
	0xf6, 0xf9, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff,
पूर्ण;

अटल स्थिर u8 fdp1_sad_adj[] = अणु
	0x00, 0x24, 0x43, 0x5e, 0x76, 0x8c, 0x9e, 0xaf,
	0xbd, 0xc9, 0xd4, 0xdd, 0xe4, 0xea, 0xef, 0xf3,
	0xf6, 0xf9, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff,
पूर्ण;

अटल स्थिर u8 fdp1_bld_gain[] = अणु
	0x80,
पूर्ण;

अटल स्थिर u8 fdp1_dअगर_gain[] = अणु
	0x80,
पूर्ण;

अटल स्थिर u8 fdp1_mdet[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
	0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
	0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
पूर्ण;

/* Per-queue, driver-specअगरic निजी data */
काष्ठा fdp1_q_data अणु
	स्थिर काष्ठा fdp1_fmt		*fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane	क्रमmat;

	अचिन्हित पूर्णांक			vsize;
	अचिन्हित पूर्णांक			stride_y;
	अचिन्हित पूर्णांक			stride_c;
पूर्ण;

अटल स्थिर काष्ठा fdp1_fmt *fdp1_find_क्रमmat(u32 pixelक्रमmat)
अणु
	स्थिर काष्ठा fdp1_fmt *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fdp1_क्रमmats); i++) अणु
		fmt = &fdp1_क्रमmats[i];
		अगर (fmt->fourcc == pixelक्रमmat)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत fdp1_deपूर्णांक_mode अणु
	FDP1_PROGRESSIVE = 0, /* Must be zero when !deपूर्णांकerlacing */
	FDP1_ADAPT2D3D,
	FDP1_FIXED2D,
	FDP1_FIXED3D,
	FDP1_PREVFIELD,
	FDP1_NEXTFIELD,
पूर्ण;

#घोषणा FDP1_DEINT_MODE_USES_NEXT(mode) \
	(mode == FDP1_ADAPT2D3D || \
	 mode == FDP1_FIXED3D   || \
	 mode == FDP1_NEXTFIELD)

#घोषणा FDP1_DEINT_MODE_USES_PREV(mode) \
	(mode == FDP1_ADAPT2D3D || \
	 mode == FDP1_FIXED3D   || \
	 mode == FDP1_PREVFIELD)

/*
 * FDP1 operates on potentially 3 fields, which are tracked
 * from the VB buffers using this context काष्ठाure.
 * Will always be a field or a full frame, never two fields.
 */
काष्ठा fdp1_field_buffer अणु
	काष्ठा vb2_v4l2_buffer		*vb;
	dma_addr_t			addrs[3];

	/* Should be NONE:TOP:BOTTOM only */
	क्रमागत v4l2_field			field;

	/* Flag to indicate this is the last field in the vb */
	bool				last_field;

	/* Buffer queue lists */
	काष्ठा list_head		list;
पूर्ण;

काष्ठा fdp1_buffer अणु
	काष्ठा v4l2_m2m_buffer		m2m_buf;
	काष्ठा fdp1_field_buffer	fields[2];
	अचिन्हित पूर्णांक			num_fields;
पूर्ण;

अटल अंतरभूत काष्ठा fdp1_buffer *to_fdp1_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा fdp1_buffer, m2m_buf.vb);
पूर्ण

काष्ठा fdp1_job अणु
	काष्ठा fdp1_field_buffer	*previous;
	काष्ठा fdp1_field_buffer	*active;
	काष्ठा fdp1_field_buffer	*next;
	काष्ठा fdp1_field_buffer	*dst;

	/* A job can only be on one list at a समय */
	काष्ठा list_head		list;
पूर्ण;

काष्ठा fdp1_dev अणु
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा video_device		vfd;

	काष्ठा mutex			dev_mutex;
	spinlock_t			irqlock;
	spinlock_t			device_process_lock;

	व्योम __iomem			*regs;
	अचिन्हित पूर्णांक			irq;
	काष्ठा device			*dev;

	/* Job Queues */
	काष्ठा fdp1_job			jobs[FDP1_NUMBER_JOBS];
	काष्ठा list_head		मुक्त_job_list;
	काष्ठा list_head		queued_job_list;
	काष्ठा list_head		hw_job_list;

	अचिन्हित पूर्णांक			clk_rate;

	काष्ठा rcar_fcp_device		*fcp;
	काष्ठा v4l2_m2m_dev		*m2m_dev;
पूर्ण;

काष्ठा fdp1_ctx अणु
	काष्ठा v4l2_fh			fh;
	काष्ठा fdp1_dev			*fdp1;

	काष्ठा v4l2_ctrl_handler	hdl;
	अचिन्हित पूर्णांक			sequence;

	/* Processed buffers in this transaction */
	u8				num_processed;

	/* Transaction length (i.e. how many buffers per transaction) */
	u32				translen;

	/* Abort requested by m2m */
	पूर्णांक				पातing;

	/* Deपूर्णांकerlace processing mode */
	क्रमागत fdp1_deपूर्णांक_mode		deपूर्णांक_mode;

	/*
	 * Adaptive 2D/3D mode uses a shared mask
	 * This is allocated at streamon, अगर the ADAPT2D3D mode
	 * is requested
	 */
	अचिन्हित पूर्णांक			smsk_size;
	dma_addr_t			smsk_addr[2];
	व्योम				*smsk_cpu;

	/* Capture pipeline, can specअगरy an alpha value
	 * क्रम supported क्रमmats. 0-255 only
	 */
	अचिन्हित अक्षर			alpha;

	/* Source and destination queue data */
	काष्ठा fdp1_q_data		out_q; /* HW Source */
	काष्ठा fdp1_q_data		cap_q; /* HW Destination */

	/*
	 * Field Queues
	 * Interlaced fields are used on 3 occasions, and tracked in this list.
	 *
	 * V4L2 Buffers are tracked inside the fdp1_buffer
	 * and released when the last 'field' completes
	 */
	काष्ठा list_head		fields_queue;
	अचिन्हित पूर्णांक			buffers_queued;

	/*
	 * For de-पूर्णांकerlacing we need to track our previous buffer
	 * जबतक preparing our job lists.
	 */
	काष्ठा fdp1_field_buffer	*previous;
पूर्ण;

अटल अंतरभूत काष्ठा fdp1_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा fdp1_ctx, fh);
पूर्ण

अटल काष्ठा fdp1_q_data *get_q_data(काष्ठा fdp1_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->out_q;
	अन्यथा
		वापस &ctx->cap_q;
पूर्ण

/*
 * list_हटाओ_job: Take the first item off the specअगरied job list
 *
 * Returns: poपूर्णांकer to a job, or शून्य अगर the list is empty.
 */
अटल काष्ठा fdp1_job *list_हटाओ_job(काष्ठा fdp1_dev *fdp1,
					 काष्ठा list_head *list)
अणु
	काष्ठा fdp1_job *job;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fdp1->irqlock, flags);
	job = list_first_entry_or_null(list, काष्ठा fdp1_job, list);
	अगर (job)
		list_del(&job->list);
	spin_unlock_irqrestore(&fdp1->irqlock, flags);

	वापस job;
पूर्ण

/*
 * list_add_job: Add a job to the specअगरied job list
 *
 * Returns: व्योम - always succeeds
 */
अटल व्योम list_add_job(काष्ठा fdp1_dev *fdp1,
			 काष्ठा list_head *list,
			 काष्ठा fdp1_job *job)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fdp1->irqlock, flags);
	list_add_tail(&job->list, list);
	spin_unlock_irqrestore(&fdp1->irqlock, flags);
पूर्ण

अटल काष्ठा fdp1_job *fdp1_job_alloc(काष्ठा fdp1_dev *fdp1)
अणु
	वापस list_हटाओ_job(fdp1, &fdp1->मुक्त_job_list);
पूर्ण

अटल व्योम fdp1_job_मुक्त(काष्ठा fdp1_dev *fdp1, काष्ठा fdp1_job *job)
अणु
	/* Ensure that all residue from previous jobs is gone */
	स_रखो(job, 0, माप(काष्ठा fdp1_job));

	list_add_job(fdp1, &fdp1->मुक्त_job_list, job);
पूर्ण

अटल व्योम queue_job(काष्ठा fdp1_dev *fdp1, काष्ठा fdp1_job *job)
अणु
	list_add_job(fdp1, &fdp1->queued_job_list, job);
पूर्ण

अटल काष्ठा fdp1_job *get_queued_job(काष्ठा fdp1_dev *fdp1)
अणु
	वापस list_हटाओ_job(fdp1, &fdp1->queued_job_list);
पूर्ण

अटल व्योम queue_hw_job(काष्ठा fdp1_dev *fdp1, काष्ठा fdp1_job *job)
अणु
	list_add_job(fdp1, &fdp1->hw_job_list, job);
पूर्ण

अटल काष्ठा fdp1_job *get_hw_queued_job(काष्ठा fdp1_dev *fdp1)
अणु
	वापस list_हटाओ_job(fdp1, &fdp1->hw_job_list);
पूर्ण

/*
 * Buffer lists handling
 */
अटल व्योम fdp1_field_complete(काष्ठा fdp1_ctx *ctx,
				काष्ठा fdp1_field_buffer *fbuf)
अणु
	/* job->previous may be on the first field */
	अगर (!fbuf)
		वापस;

	अगर (fbuf->last_field)
		v4l2_m2m_buf_करोne(fbuf->vb, VB2_BUF_STATE_DONE);
पूर्ण

अटल व्योम fdp1_queue_field(काष्ठा fdp1_ctx *ctx,
			     काष्ठा fdp1_field_buffer *fbuf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
	list_add_tail(&fbuf->list, &ctx->fields_queue);
	spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);

	ctx->buffers_queued++;
पूर्ण

अटल काष्ठा fdp1_field_buffer *fdp1_dequeue_field(काष्ठा fdp1_ctx *ctx)
अणु
	काष्ठा fdp1_field_buffer *fbuf;
	अचिन्हित दीर्घ flags;

	ctx->buffers_queued--;

	spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
	fbuf = list_first_entry_or_null(&ctx->fields_queue,
					काष्ठा fdp1_field_buffer, list);
	अगर (fbuf)
		list_del(&fbuf->list);
	spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);

	वापस fbuf;
पूर्ण

/*
 * Return the next field in the queue - or शून्य,
 * without removing the item from the list
 */
अटल काष्ठा fdp1_field_buffer *fdp1_peek_queued_field(काष्ठा fdp1_ctx *ctx)
अणु
	काष्ठा fdp1_field_buffer *fbuf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
	fbuf = list_first_entry_or_null(&ctx->fields_queue,
					काष्ठा fdp1_field_buffer, list);
	spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);

	वापस fbuf;
पूर्ण

अटल u32 fdp1_पढ़ो(काष्ठा fdp1_dev *fdp1, अचिन्हित पूर्णांक reg)
अणु
	u32 value = ioपढ़ो32(fdp1->regs + reg);

	अगर (debug >= 2)
		dprपूर्णांकk(fdp1, "Read 0x%08x from 0x%04x\n", value, reg);

	वापस value;
पूर्ण

अटल व्योम fdp1_ग_लिखो(काष्ठा fdp1_dev *fdp1, u32 val, अचिन्हित पूर्णांक reg)
अणु
	अगर (debug >= 2)
		dprपूर्णांकk(fdp1, "Write 0x%08x to 0x%04x\n", val, reg);

	ioग_लिखो32(val, fdp1->regs + reg);
पूर्ण

/* IPC रेजिस्टरs are to be programmed with स्थिरant values */
अटल व्योम fdp1_set_ipc_dli(काष्ठा fdp1_ctx *ctx)
अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;

	fdp1_ग_लिखो(fdp1, FD1_IPC_SMSK_THRESH_CONST,	FD1_IPC_SMSK_THRESH);
	fdp1_ग_लिखो(fdp1, FD1_IPC_COMB_DET_CONST,	FD1_IPC_COMB_DET);
	fdp1_ग_लिखो(fdp1, FD1_IPC_MOTDEC_CONST,	FD1_IPC_MOTDEC);

	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_BLEND_CONST,	FD1_IPC_DLI_BLEND);
	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_HGAIN_CONST,	FD1_IPC_DLI_HGAIN);
	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_SPRS_CONST,	FD1_IPC_DLI_SPRS);
	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_ANGLE_CONST,	FD1_IPC_DLI_ANGLE);
	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_ISOPIX0_CONST,	FD1_IPC_DLI_ISOPIX0);
	fdp1_ग_लिखो(fdp1, FD1_IPC_DLI_ISOPIX1_CONST,	FD1_IPC_DLI_ISOPIX1);
पूर्ण


अटल व्योम fdp1_set_ipc_sensor(काष्ठा fdp1_ctx *ctx)
अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	काष्ठा fdp1_q_data *src_q_data = &ctx->out_q;
	अचिन्हित पूर्णांक x0, x1;
	अचिन्हित पूर्णांक hsize = src_q_data->क्रमmat.width;
	अचिन्हित पूर्णांक vsize = src_q_data->क्रमmat.height;

	x0 = hsize / 3;
	x1 = 2 * hsize / 3;

	fdp1_ग_लिखो(fdp1, FD1_IPC_SENSOR_TH0_CONST, FD1_IPC_SENSOR_TH0);
	fdp1_ग_लिखो(fdp1, FD1_IPC_SENSOR_TH1_CONST, FD1_IPC_SENSOR_TH1);
	fdp1_ग_लिखो(fdp1, FD1_IPC_SENSOR_CTL0_CONST, FD1_IPC_SENSOR_CTL0);
	fdp1_ग_लिखो(fdp1, FD1_IPC_SENSOR_CTL1_CONST, FD1_IPC_SENSOR_CTL1);

	fdp1_ग_लिखो(fdp1, ((hsize - 1) << FD1_IPC_SENSOR_CTL2_X_SHIFT) |
			 ((vsize - 1) << FD1_IPC_SENSOR_CTL2_Y_SHIFT),
			 FD1_IPC_SENSOR_CTL2);

	fdp1_ग_लिखो(fdp1, (x0 << FD1_IPC_SENSOR_CTL3_0_SHIFT) |
			 (x1 << FD1_IPC_SENSOR_CTL3_1_SHIFT),
			 FD1_IPC_SENSOR_CTL3);
पूर्ण

/*
 * fdp1_ग_लिखो_lut: Write a padded LUT to the hw
 *
 * FDP1 uses स्थिरant data क्रम de-पूर्णांकerlacing processing,
 * with large tables. These hardware tables are all 256 bytes
 * दीर्घ, however they often contain repeated data at the end.
 *
 * The last byte of the table is written to all reमुख्यing entries.
 */
अटल व्योम fdp1_ग_लिखो_lut(काष्ठा fdp1_dev *fdp1, स्थिर u8 *lut,
			   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित पूर्णांक i;
	u8 pad;

	/* Tables larger than the hw are clipped */
	len = min(len, 256u);

	क्रम (i = 0; i < len; i++)
		fdp1_ग_लिखो(fdp1, lut[i], base + (i*4));

	/* Tables are padded with the last entry */
	pad = lut[i-1];

	क्रम (; i < 256; i++)
		fdp1_ग_लिखो(fdp1, pad, base + (i*4));
पूर्ण

अटल व्योम fdp1_set_lut(काष्ठा fdp1_dev *fdp1)
अणु
	fdp1_ग_लिखो_lut(fdp1, fdp1_dअगरf_adj, ARRAY_SIZE(fdp1_dअगरf_adj),
			FD1_LUT_DIF_ADJ);
	fdp1_ग_लिखो_lut(fdp1, fdp1_sad_adj,  ARRAY_SIZE(fdp1_sad_adj),
			FD1_LUT_SAD_ADJ);
	fdp1_ग_लिखो_lut(fdp1, fdp1_bld_gain, ARRAY_SIZE(fdp1_bld_gain),
			FD1_LUT_BLD_GAIN);
	fdp1_ग_लिखो_lut(fdp1, fdp1_dअगर_gain, ARRAY_SIZE(fdp1_dअगर_gain),
			FD1_LUT_DIF_GAIN);
	fdp1_ग_लिखो_lut(fdp1, fdp1_mdet, ARRAY_SIZE(fdp1_mdet),
			FD1_LUT_MDET);
पूर्ण

अटल व्योम fdp1_configure_rpf(काष्ठा fdp1_ctx *ctx,
			       काष्ठा fdp1_job *job)
अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	u32 picture_size;
	u32 pstride;
	u32 क्रमmat;
	u32 smsk_addr;

	काष्ठा fdp1_q_data *q_data = &ctx->out_q;

	/* Picture size is common to Source and Destination frames */
	picture_size = (q_data->क्रमmat.width << FD1_RPF_SIZE_H_SHIFT)
		     | (q_data->vsize << FD1_RPF_SIZE_V_SHIFT);

	/* Strides */
	pstride = q_data->stride_y << FD1_RPF_PSTRIDE_Y_SHIFT;
	अगर (q_data->क्रमmat.num_planes > 1)
		pstride |= q_data->stride_c << FD1_RPF_PSTRIDE_C_SHIFT;

	/* Format control */
	क्रमmat = q_data->fmt->fmt;
	अगर (q_data->fmt->swap_yc)
		क्रमmat |= FD1_RPF_FORMAT_RSPYCS;

	अगर (q_data->fmt->swap_uv)
		क्रमmat |= FD1_RPF_FORMAT_RSPUVS;

	अगर (job->active->field == V4L2_FIELD_BOTTOM) अणु
		क्रमmat |= FD1_RPF_FORMAT_CF; /* Set क्रम Bottom field */
		smsk_addr = ctx->smsk_addr[0];
	पूर्ण अन्यथा अणु
		smsk_addr = ctx->smsk_addr[1];
	पूर्ण

	/* Deपूर्णांक mode is non-zero when deपूर्णांकerlacing */
	अगर (ctx->deपूर्णांक_mode)
		क्रमmat |= FD1_RPF_FORMAT_CIPM;

	fdp1_ग_लिखो(fdp1, क्रमmat, FD1_RPF_FORMAT);
	fdp1_ग_लिखो(fdp1, q_data->fmt->swap, FD1_RPF_SWAP);
	fdp1_ग_लिखो(fdp1, picture_size, FD1_RPF_SIZE);
	fdp1_ग_लिखो(fdp1, pstride, FD1_RPF_PSTRIDE);
	fdp1_ग_लिखो(fdp1, smsk_addr, FD1_RPF_SMSK_ADDR);

	/* Previous Field Channel (CH0) */
	अगर (job->previous)
		fdp1_ग_लिखो(fdp1, job->previous->addrs[0], FD1_RPF0_ADDR_Y);

	/* Current Field Channel (CH1) */
	fdp1_ग_लिखो(fdp1, job->active->addrs[0], FD1_RPF1_ADDR_Y);
	fdp1_ग_लिखो(fdp1, job->active->addrs[1], FD1_RPF1_ADDR_C0);
	fdp1_ग_लिखो(fdp1, job->active->addrs[2], FD1_RPF1_ADDR_C1);

	/* Next Field  Channel (CH2) */
	अगर (job->next)
		fdp1_ग_लिखो(fdp1, job->next->addrs[0], FD1_RPF2_ADDR_Y);
पूर्ण

अटल व्योम fdp1_configure_wpf(काष्ठा fdp1_ctx *ctx,
			       काष्ठा fdp1_job *job)
अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	काष्ठा fdp1_q_data *src_q_data = &ctx->out_q;
	काष्ठा fdp1_q_data *q_data = &ctx->cap_q;
	u32 pstride;
	u32 क्रमmat;
	u32 swap;
	u32 rndctl;

	pstride = q_data->क्रमmat.plane_fmt[0].bytesperline
		<< FD1_WPF_PSTRIDE_Y_SHIFT;

	अगर (q_data->क्रमmat.num_planes > 1)
		pstride |= q_data->क्रमmat.plane_fmt[1].bytesperline
			<< FD1_WPF_PSTRIDE_C_SHIFT;

	क्रमmat = q_data->fmt->fmt; /* Output Format Code */

	अगर (q_data->fmt->swap_yc)
		क्रमmat |= FD1_WPF_FORMAT_WSPYCS;

	अगर (q_data->fmt->swap_uv)
		क्रमmat |= FD1_WPF_FORMAT_WSPUVS;

	अगर (fdp1_fmt_is_rgb(q_data->fmt)) अणु
		/* Enable Colour Space conversion */
		क्रमmat |= FD1_WPF_FORMAT_CSC;

		/* Set WRTM */
		अगर (src_q_data->क्रमmat.ycbcr_enc == V4L2_YCBCR_ENC_709)
			क्रमmat |= FD1_WPF_FORMAT_WRTM_709_16;
		अन्यथा अगर (src_q_data->क्रमmat.quantization ==
				V4L2_QUANTIZATION_FULL_RANGE)
			क्रमmat |= FD1_WPF_FORMAT_WRTM_601_0;
		अन्यथा
			क्रमmat |= FD1_WPF_FORMAT_WRTM_601_16;
	पूर्ण

	/* Set an alpha value पूर्णांकo the Pad Value */
	क्रमmat |= ctx->alpha << FD1_WPF_FORMAT_PDV_SHIFT;

	/* Determine picture rounding and clipping */
	rndctl = FD1_WPF_RNDCTL_CBRM; /* Rounding Off */
	rndctl |= FD1_WPF_RNDCTL_CLMD_NOCLIP;

	/* WPF Swap needs both ISWAP and OSWAP setting */
	swap = q_data->fmt->swap << FD1_WPF_SWAP_OSWAP_SHIFT;
	swap |= src_q_data->fmt->swap << FD1_WPF_SWAP_SSWAP_SHIFT;

	fdp1_ग_लिखो(fdp1, क्रमmat, FD1_WPF_FORMAT);
	fdp1_ग_लिखो(fdp1, rndctl, FD1_WPF_RNDCTL);
	fdp1_ग_लिखो(fdp1, swap, FD1_WPF_SWAP);
	fdp1_ग_लिखो(fdp1, pstride, FD1_WPF_PSTRIDE);

	fdp1_ग_लिखो(fdp1, job->dst->addrs[0], FD1_WPF_ADDR_Y);
	fdp1_ग_लिखो(fdp1, job->dst->addrs[1], FD1_WPF_ADDR_C0);
	fdp1_ग_लिखो(fdp1, job->dst->addrs[2], FD1_WPF_ADDR_C1);
पूर्ण

अटल व्योम fdp1_configure_deपूर्णांक_mode(काष्ठा fdp1_ctx *ctx,
				      काष्ठा fdp1_job *job)
अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	u32 opmode = FD1_CTL_OPMODE_VIMD_NOINTERRUPT;
	u32 ipcmode = FD1_IPC_MODE_DLI; /* Always set */
	u32 channels = FD1_CTL_CHACT_WR | FD1_CTL_CHACT_RD1; /* Always on */

	/* De-पूर्णांकerlacing Mode */
	चयन (ctx->deपूर्णांक_mode) अणु
	शेष:
	हाल FDP1_PROGRESSIVE:
		dprपूर्णांकk(fdp1, "Progressive Mode\n");
		opmode |= FD1_CTL_OPMODE_PRG;
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		अवरोध;
	हाल FDP1_ADAPT2D3D:
		dprपूर्णांकk(fdp1, "Adapt2D3D Mode\n");
		अगर (ctx->sequence == 0 || ctx->पातing)
			ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		अन्यथा
			ipcmode |= FD1_IPC_MODE_DIM_ADAPT2D3D;

		अगर (ctx->sequence > 1) अणु
			channels |= FD1_CTL_CHACT_SMW;
			channels |= FD1_CTL_CHACT_RD0 | FD1_CTL_CHACT_RD2;
		पूर्ण

		अगर (ctx->sequence > 2)
			channels |= FD1_CTL_CHACT_SMR;

		अवरोध;
	हाल FDP1_FIXED3D:
		dprपूर्णांकk(fdp1, "Fixed 3D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED3D;
		/* Except क्रम first and last frame, enable all channels */
		अगर (!(ctx->sequence == 0 || ctx->पातing))
			channels |= FD1_CTL_CHACT_RD0 | FD1_CTL_CHACT_RD2;
		अवरोध;
	हाल FDP1_FIXED2D:
		dprपूर्णांकk(fdp1, "Fixed 2D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		/* No extra channels enabled */
		अवरोध;
	हाल FDP1_PREVFIELD:
		dprपूर्णांकk(fdp1, "Previous Field Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_PREVFIELD;
		channels |= FD1_CTL_CHACT_RD0; /* Previous */
		अवरोध;
	हाल FDP1_NEXTFIELD:
		dprपूर्णांकk(fdp1, "Next Field Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_NEXTFIELD;
		channels |= FD1_CTL_CHACT_RD2; /* Next */
		अवरोध;
	पूर्ण

	fdp1_ग_लिखो(fdp1, channels,	FD1_CTL_CHACT);
	fdp1_ग_लिखो(fdp1, opmode,	FD1_CTL_OPMODE);
	fdp1_ग_लिखो(fdp1, ipcmode,	FD1_IPC_MODE);
पूर्ण

/*
 * fdp1_device_process() - Run the hardware
 *
 * Configure and start the hardware to generate a single frame
 * of output given our input parameters.
 */
अटल पूर्णांक fdp1_device_process(काष्ठा fdp1_ctx *ctx)

अणु
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	काष्ठा fdp1_job *job;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fdp1->device_process_lock, flags);

	/* Get a job to process */
	job = get_queued_job(fdp1);
	अगर (!job) अणु
		/*
		 * VINT can call us to see अगर we can queue another job.
		 * If we have no work to करो, we simply वापस.
		 */
		spin_unlock_irqrestore(&fdp1->device_process_lock, flags);
		वापस 0;
	पूर्ण

	/* First Frame only? ... */
	fdp1_ग_लिखो(fdp1, FD1_CTL_CLKCTRL_CSTP_N, FD1_CTL_CLKCTRL);

	/* Set the mode, and configuration */
	fdp1_configure_deपूर्णांक_mode(ctx, job);

	/* DLI Static Configuration */
	fdp1_set_ipc_dli(ctx);

	/* Sensor Configuration */
	fdp1_set_ipc_sensor(ctx);

	/* Setup the source picture */
	fdp1_configure_rpf(ctx, job);

	/* Setup the destination picture */
	fdp1_configure_wpf(ctx, job);

	/* Line Memory Pixel Number Register क्रम linear access */
	fdp1_ग_लिखो(fdp1, FD1_IPC_LMEM_LINEAR, FD1_IPC_LMEM);

	/* Enable Interrupts */
	fdp1_ग_लिखो(fdp1, FD1_CTL_IRQ_MASK, FD1_CTL_IRQENB);

	/* Finally, the Immediate Registers */

	/* This job is now in the HW queue */
	queue_hw_job(fdp1, job);

	/* Start the command */
	fdp1_ग_लिखो(fdp1, FD1_CTL_CMD_STRCMD, FD1_CTL_CMD);

	/* Registers will update to HW at next VINT */
	fdp1_ग_लिखो(fdp1, FD1_CTL_REGEND_REGEND, FD1_CTL_REGEND);

	/* Enable VINT Generator */
	fdp1_ग_लिखो(fdp1, FD1_CTL_SGCMD_SGEN, FD1_CTL_SGCMD);

	spin_unlock_irqrestore(&fdp1->device_process_lock, flags);

	वापस 0;
पूर्ण

/*
 * mem2mem callbacks
 */

/*
 * job_पढ़ोy() - check whether an instance is पढ़ोy to be scheduled to run
 */
अटल पूर्णांक fdp1_m2m_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा fdp1_ctx *ctx = priv;
	काष्ठा fdp1_q_data *src_q_data = &ctx->out_q;
	पूर्णांक srcbufs = 1;
	पूर्णांक dstbufs = 1;

	dprपूर्णांकk(ctx->fdp1, "+ Src: %d : Dst: %d\n",
		v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx),
		v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx));

	/* One output buffer is required क्रम each field */
	अगर (V4L2_FIELD_HAS_BOTH(src_q_data->क्रमmat.field))
		dstbufs = 2;

	अगर (v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) < srcbufs
	    || v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) < dstbufs) अणु
		dprपूर्णांकk(ctx->fdp1, "Not enough buffers available\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम fdp1_m2m_job_पात(व्योम *priv)
अणु
	काष्ठा fdp1_ctx *ctx = priv;

	dprपूर्णांकk(ctx->fdp1, "+\n");

	/* Will cancel the transaction in the next पूर्णांकerrupt handler */
	ctx->पातing = 1;

	/* Immediate पात sequence */
	fdp1_ग_लिखो(ctx->fdp1, 0, FD1_CTL_SGCMD);
	fdp1_ग_लिखो(ctx->fdp1, FD1_CTL_SRESET_SRST, FD1_CTL_SRESET);
पूर्ण

/*
 * fdp1_prepare_job: Prepare and queue a new job क्रम a single action of work
 *
 * Prepare the next field, (or frame in progressive) and an output
 * buffer क्रम the hardware to perक्रमm a single operation.
 */
अटल काष्ठा fdp1_job *fdp1_prepare_job(काष्ठा fdp1_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा fdp1_buffer *fbuf;
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	काष्ठा fdp1_job *job;
	अचिन्हित पूर्णांक buffers_required = 1;

	dprपूर्णांकk(fdp1, "+\n");

	अगर (FDP1_DEINT_MODE_USES_NEXT(ctx->deपूर्णांक_mode))
		buffers_required = 2;

	अगर (ctx->buffers_queued < buffers_required)
		वापस शून्य;

	job = fdp1_job_alloc(fdp1);
	अगर (!job) अणु
		dprपूर्णांकk(fdp1, "No free jobs currently available\n");
		वापस शून्य;
	पूर्ण

	job->active = fdp1_dequeue_field(ctx);
	अगर (!job->active) अणु
		/* Buffer check should prevent this ever happening */
		dprपूर्णांकk(fdp1, "No input buffers currently available\n");

		fdp1_job_मुक्त(fdp1, job);
		वापस शून्य;
	पूर्ण

	dprपूर्णांकk(fdp1, "+ Buffer en-route...\n");

	/* Source buffers have been prepared on our buffer_queue
	 * Prepare our Output buffer
	 */
	vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	fbuf = to_fdp1_buffer(vbuf);
	job->dst = &fbuf->fields[0];

	job->active->vb->sequence = ctx->sequence;
	job->dst->vb->sequence = ctx->sequence;
	ctx->sequence++;

	अगर (FDP1_DEINT_MODE_USES_PREV(ctx->deपूर्णांक_mode)) अणु
		job->previous = ctx->previous;

		/* Active buffer becomes the next job's previous buffer */
		ctx->previous = job->active;
	पूर्ण

	अगर (FDP1_DEINT_MODE_USES_NEXT(ctx->deपूर्णांक_mode)) अणु
		/* Must be called after 'active' is dequeued */
		job->next = fdp1_peek_queued_field(ctx);
	पूर्ण

	/* Transfer बारtamps and flags from src->dst */

	job->dst->vb->vb2_buf.बारtamp = job->active->vb->vb2_buf.बारtamp;

	job->dst->vb->flags = job->active->vb->flags &
				V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	/* Ideally, the frame-end function will just 'check' to see
	 * अगर there are more jobs instead
	 */
	ctx->translen++;

	/* Finally, Put this job on the processing queue */
	queue_job(fdp1, job);

	dprपूर्णांकk(fdp1, "Job Queued translen = %d\n", ctx->translen);

	वापस job;
पूर्ण

/* fdp1_m2m_device_run() - prepares and starts the device क्रम an M2M task
 *
 * A single input buffer is taken and serialised पूर्णांकo our fdp1_buffer
 * queue. The queue is then processed to create as many jobs as possible
 * from our available input.
 */
अटल व्योम fdp1_m2m_device_run(व्योम *priv)
अणु
	काष्ठा fdp1_ctx *ctx = priv;
	काष्ठा fdp1_dev *fdp1 = ctx->fdp1;
	काष्ठा vb2_v4l2_buffer *src_vb;
	काष्ठा fdp1_buffer *buf;
	अचिन्हित पूर्णांक i;

	dprपूर्णांकk(fdp1, "+\n");

	ctx->translen = 0;

	/* Get our incoming buffer of either one or two fields, or one frame */
	src_vb = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
	buf = to_fdp1_buffer(src_vb);

	क्रम (i = 0; i < buf->num_fields; i++) अणु
		काष्ठा fdp1_field_buffer *fbuf = &buf->fields[i];

		fdp1_queue_field(ctx, fbuf);
		dprपूर्णांकk(fdp1, "Queued Buffer [%d] last_field:%d\n",
			i, fbuf->last_field);
	पूर्ण

	/* Queue as many jobs as our data provides क्रम */
	जबतक (fdp1_prepare_job(ctx))
		;

	अगर (ctx->translen == 0) अणु
		dprपूर्णांकk(fdp1, "No jobs were processed. M2M action complete\n");
		v4l2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
		वापस;
	पूर्ण

	/* Kick the job processing action */
	fdp1_device_process(ctx);
पूर्ण

/*
 * device_frame_end:
 *
 * Handles the M2M level after a buffer completion event.
 */
अटल व्योम device_frame_end(काष्ठा fdp1_dev *fdp1,
			     क्रमागत vb2_buffer_state state)
अणु
	काष्ठा fdp1_ctx *ctx;
	अचिन्हित दीर्घ flags;
	काष्ठा fdp1_job *job = get_hw_queued_job(fdp1);

	dprपूर्णांकk(fdp1, "+\n");

	ctx = v4l2_m2m_get_curr_priv(fdp1->m2m_dev);

	अगर (ctx == शून्य) अणु
		v4l2_err(&fdp1->v4l2_dev,
			"Instance released before the end of transaction\n");
		वापस;
	पूर्ण

	ctx->num_processed++;

	/*
	 * fdp1_field_complete will call buf_करोne only when the last vb2_buffer
	 * reference is complete
	 */
	अगर (FDP1_DEINT_MODE_USES_PREV(ctx->deपूर्णांक_mode))
		fdp1_field_complete(ctx, job->previous);
	अन्यथा
		fdp1_field_complete(ctx, job->active);

	spin_lock_irqsave(&fdp1->irqlock, flags);
	v4l2_m2m_buf_करोne(job->dst->vb, state);
	job->dst = शून्य;
	spin_unlock_irqrestore(&fdp1->irqlock, flags);

	/* Move this job back to the मुक्त job list */
	fdp1_job_मुक्त(fdp1, job);

	dprपूर्णांकk(fdp1, "curr_ctx->num_processed %d curr_ctx->translen %d\n",
		ctx->num_processed, ctx->translen);

	अगर (ctx->num_processed == ctx->translen ||
			ctx->पातing) अणु
		dprपूर्णांकk(ctx->fdp1, "Finishing transaction\n");
		ctx->num_processed = 0;
		v4l2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
	पूर्ण अन्यथा अणु
		/*
		 * For pipelined perक्रमmance support, this would
		 * be called from a VINT handler
		 */
		fdp1_device_process(ctx);
	पूर्ण
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक fdp1_vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, DRIVER_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", DRIVER_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक fdp1_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	अचिन्हित पूर्णांक i, num;

	num = 0;

	क्रम (i = 0; i < ARRAY_SIZE(fdp1_क्रमmats); ++i) अणु
		अगर (fdp1_क्रमmats[i].types & type) अणु
			अगर (num == f->index)
				अवरोध;
			++num;
		पूर्ण
	पूर्ण

	/* Format not found */
	अगर (i >= ARRAY_SIZE(fdp1_क्रमmats))
		वापस -EINVAL;

	/* Format found */
	f->pixelक्रमmat = fdp1_क्रमmats[i].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक fdp1_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	वापस fdp1_क्रमागत_fmt(f, FDP1_CAPTURE);
पूर्ण

अटल पूर्णांक fdp1_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस fdp1_क्रमागत_fmt(f, FDP1_OUTPUT);
पूर्ण

अटल पूर्णांक fdp1_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fdp1_q_data *q_data;
	काष्ठा fdp1_ctx *ctx = fh_to_ctx(priv);

	अगर (!v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	f->fmt.pix_mp = q_data->क्रमmat;

	वापस 0;
पूर्ण

अटल व्योम fdp1_compute_stride(काष्ठा v4l2_pix_क्रमmat_mplane *pix,
				स्थिर काष्ठा fdp1_fmt *fmt)
अणु
	अचिन्हित पूर्णांक i;

	/* Compute and clamp the stride and image size. */
	क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, fmt->num_planes, 2U); ++i) अणु
		अचिन्हित पूर्णांक hsub = i > 0 ? fmt->hsub : 1;
		अचिन्हित पूर्णांक vsub = i > 0 ? fmt->vsub : 1;
		 /* From VSP : TODO: Confirm alignment limits क्रम FDP1 */
		अचिन्हित पूर्णांक align = 128;
		अचिन्हित पूर्णांक bpl;

		bpl = clamp_t(अचिन्हित पूर्णांक, pix->plane_fmt[i].bytesperline,
			      pix->width / hsub * fmt->bpp[i] / 8,
			      round_करोwn(FDP1_MAX_STRIDE, align));

		pix->plane_fmt[i].bytesperline = round_up(bpl, align);
		pix->plane_fmt[i].sizeimage = pix->plane_fmt[i].bytesperline
					    * pix->height / vsub;

	पूर्ण

	अगर (fmt->num_planes == 3) अणु
		/* The two chroma planes must have the same stride. */
		pix->plane_fmt[2].bytesperline = pix->plane_fmt[1].bytesperline;
		pix->plane_fmt[2].sizeimage = pix->plane_fmt[1].sizeimage;

	पूर्ण
पूर्ण

अटल व्योम fdp1_try_fmt_output(काष्ठा fdp1_ctx *ctx,
				स्थिर काष्ठा fdp1_fmt **fmtinfo,
				काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	स्थिर काष्ठा fdp1_fmt *fmt;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;

	/* Validate the pixel क्रमmat to ensure the output queue supports it. */
	fmt = fdp1_find_क्रमmat(pix->pixelक्रमmat);
	अगर (!fmt || !(fmt->types & FDP1_OUTPUT))
		fmt = fdp1_find_क्रमmat(V4L2_PIX_FMT_YUYV);

	अगर (fmtinfo)
		*fmtinfo = fmt;

	pix->pixelक्रमmat = fmt->fourcc;
	pix->num_planes = fmt->num_planes;

	/*
	 * Progressive video and all पूर्णांकerlaced field orders are acceptable.
	 * Default to V4L2_FIELD_INTERLACED.
	 */
	अगर (pix->field != V4L2_FIELD_NONE &&
	    pix->field != V4L2_FIELD_ALTERNATE &&
	    !V4L2_FIELD_HAS_BOTH(pix->field))
		pix->field = V4L2_FIELD_INTERLACED;

	/*
	 * The deपूर्णांकerlacer करोesn't care about the colorspace, accept all values
	 * and शेष to V4L2_COLORSPACE_SMPTE170M. The YUV to RGB conversion
	 * at the output of the deपूर्णांकerlacer supports a subset of encodings and
	 * quantization methods and will only be available when the colorspace
	 * allows it.
	 */
	अगर (pix->colorspace == V4L2_COLORSPACE_DEFAULT)
		pix->colorspace = V4L2_COLORSPACE_SMPTE170M;

	/*
	 * Align the width and height क्रम YUV 4:2:2 and 4:2:0 क्रमmats and clamp
	 * them to the supported frame size range. The height boundary are
	 * related to the full frame, भागide them by two when the क्रमmat passes
	 * fields in separate buffers.
	 */
	width = round_करोwn(pix->width, fmt->hsub);
	pix->width = clamp(width, FDP1_MIN_W, FDP1_MAX_W);

	height = round_करोwn(pix->height, fmt->vsub);
	अगर (pix->field == V4L2_FIELD_ALTERNATE)
		pix->height = clamp(height, FDP1_MIN_H / 2, FDP1_MAX_H / 2);
	अन्यथा
		pix->height = clamp(height, FDP1_MIN_H, FDP1_MAX_H);

	fdp1_compute_stride(pix, fmt);
पूर्ण

अटल व्योम fdp1_try_fmt_capture(काष्ठा fdp1_ctx *ctx,
				 स्थिर काष्ठा fdp1_fmt **fmtinfo,
				 काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	काष्ठा fdp1_q_data *src_data = &ctx->out_q;
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
	स्थिर काष्ठा fdp1_fmt *fmt;
	bool allow_rgb;

	/*
	 * Validate the pixel क्रमmat. We can only accept RGB output क्रमmats अगर
	 * the input encoding and quantization are compatible with the क्रमmat
	 * conversions supported by the hardware. The supported combinations are
	 *
	 * V4L2_YCBCR_ENC_601 + V4L2_QUANTIZATION_LIM_RANGE
	 * V4L2_YCBCR_ENC_601 + V4L2_QUANTIZATION_FULL_RANGE
	 * V4L2_YCBCR_ENC_709 + V4L2_QUANTIZATION_LIM_RANGE
	 */
	colorspace = src_data->क्रमmat.colorspace;

	ycbcr_enc = src_data->क्रमmat.ycbcr_enc;
	अगर (ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
		ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(colorspace);

	quantization = src_data->क्रमmat.quantization;
	अगर (quantization == V4L2_QUANTIZATION_DEFAULT)
		quantization = V4L2_MAP_QUANTIZATION_DEFAULT(false, colorspace,
							     ycbcr_enc);

	allow_rgb = ycbcr_enc == V4L2_YCBCR_ENC_601 ||
		    (ycbcr_enc == V4L2_YCBCR_ENC_709 &&
		     quantization == V4L2_QUANTIZATION_LIM_RANGE);

	fmt = fdp1_find_क्रमmat(pix->pixelक्रमmat);
	अगर (!fmt || (!allow_rgb && fdp1_fmt_is_rgb(fmt)))
		fmt = fdp1_find_क्रमmat(V4L2_PIX_FMT_YUYV);

	अगर (fmtinfo)
		*fmtinfo = fmt;

	pix->pixelक्रमmat = fmt->fourcc;
	pix->num_planes = fmt->num_planes;
	pix->field = V4L2_FIELD_NONE;

	/*
	 * The colorspace on the capture queue is copied from the output queue
	 * as the hardware can't change the colorspace. It can convert YCbCr to
	 * RGB though, in which हाल the encoding and quantization are set to
	 * शेष values as anything अन्यथा wouldn't make sense.
	 */
	pix->colorspace = src_data->क्रमmat.colorspace;
	pix->xfer_func = src_data->क्रमmat.xfer_func;

	अगर (fdp1_fmt_is_rgb(fmt)) अणु
		pix->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
		pix->quantization = V4L2_QUANTIZATION_DEFAULT;
	पूर्ण अन्यथा अणु
		pix->ycbcr_enc = src_data->क्रमmat.ycbcr_enc;
		pix->quantization = src_data->क्रमmat.quantization;
	पूर्ण

	/*
	 * The frame width is identical to the output queue, and the height is
	 * either द्विगुनd or identical depending on whether the output queue
	 * field order contains one or two fields per frame.
	 */
	pix->width = src_data->क्रमmat.width;
	अगर (src_data->क्रमmat.field == V4L2_FIELD_ALTERNATE)
		pix->height = 2 * src_data->क्रमmat.height;
	अन्यथा
		pix->height = src_data->क्रमmat.height;

	fdp1_compute_stride(pix, fmt);
पूर्ण

अटल पूर्णांक fdp1_try_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fdp1_ctx *ctx = fh_to_ctx(priv);

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fdp1_try_fmt_output(ctx, शून्य, &f->fmt.pix_mp);
	अन्यथा
		fdp1_try_fmt_capture(ctx, शून्य, &f->fmt.pix_mp);

	dprपूर्णांकk(ctx->fdp1, "Try %s format: %4.4s (0x%08x) %ux%u field %u\n",
		V4L2_TYPE_IS_OUTPUT(f->type) ? "output" : "capture",
		(अक्षर *)&f->fmt.pix_mp.pixelक्रमmat, f->fmt.pix_mp.pixelक्रमmat,
		f->fmt.pix_mp.width, f->fmt.pix_mp.height, f->fmt.pix_mp.field);

	वापस 0;
पूर्ण

अटल व्योम fdp1_set_क्रमmat(काष्ठा fdp1_ctx *ctx,
			    काष्ठा v4l2_pix_क्रमmat_mplane *pix,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा fdp1_q_data *q_data = get_q_data(ctx, type);
	स्थिर काष्ठा fdp1_fmt *fmtinfo;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fdp1_try_fmt_output(ctx, &fmtinfo, pix);
	अन्यथा
		fdp1_try_fmt_capture(ctx, &fmtinfo, pix);

	q_data->fmt = fmtinfo;
	q_data->क्रमmat = *pix;

	q_data->vsize = pix->height;
	अगर (pix->field != V4L2_FIELD_NONE)
		q_data->vsize /= 2;

	q_data->stride_y = pix->plane_fmt[0].bytesperline;
	q_data->stride_c = pix->plane_fmt[1].bytesperline;

	/* Adjust strides क्रम पूर्णांकerleaved buffers */
	अगर (pix->field == V4L2_FIELD_INTERLACED ||
	    pix->field == V4L2_FIELD_INTERLACED_TB ||
	    pix->field == V4L2_FIELD_INTERLACED_BT) अणु
		q_data->stride_y *= 2;
		q_data->stride_c *= 2;
	पूर्ण

	/* Propagate the क्रमmat from the output node to the capture node. */
	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		काष्ठा fdp1_q_data *dst_data = &ctx->cap_q;

		/*
		 * Copy the क्रमmat, clear the per-plane bytes per line and image
		 * size, override the field and द्विगुन the height अगर needed.
		 */
		dst_data->क्रमmat = q_data->क्रमmat;
		स_रखो(dst_data->क्रमmat.plane_fmt, 0,
		       माप(dst_data->क्रमmat.plane_fmt));

		dst_data->क्रमmat.field = V4L2_FIELD_NONE;
		अगर (pix->field == V4L2_FIELD_ALTERNATE)
			dst_data->क्रमmat.height *= 2;

		fdp1_try_fmt_capture(ctx, &dst_data->fmt, &dst_data->क्रमmat);

		dst_data->vsize = dst_data->क्रमmat.height;
		dst_data->stride_y = dst_data->क्रमmat.plane_fmt[0].bytesperline;
		dst_data->stride_c = dst_data->क्रमmat.plane_fmt[1].bytesperline;
	पूर्ण
पूर्ण

अटल पूर्णांक fdp1_s_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा fdp1_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	काष्ठा vb2_queue *vq = v4l2_m2m_get_vq(m2m_ctx, f->type);

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->fdp1->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	fdp1_set_क्रमmat(ctx, &f->fmt.pix_mp, f->type);

	dprपूर्णांकk(ctx->fdp1, "Set %s format: %4.4s (0x%08x) %ux%u field %u\n",
		V4L2_TYPE_IS_OUTPUT(f->type) ? "output" : "capture",
		(अक्षर *)&f->fmt.pix_mp.pixelक्रमmat, f->fmt.pix_mp.pixelक्रमmat,
		f->fmt.pix_mp.width, f->fmt.pix_mp.height, f->fmt.pix_mp.field);

	वापस 0;
पूर्ण

अटल पूर्णांक fdp1_g_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fdp1_ctx *ctx =
		container_of(ctrl->handler, काष्ठा fdp1_ctx, hdl);
	काष्ठा fdp1_q_data *src_q_data = &ctx->out_q;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		अगर (V4L2_FIELD_HAS_BOTH(src_q_data->क्रमmat.field))
			ctrl->val = 2;
		अन्यथा
			ctrl->val = 1;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक fdp1_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fdp1_ctx *ctx =
		container_of(ctrl->handler, काष्ठा fdp1_ctx, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ALPHA_COMPONENT:
		ctx->alpha = ctrl->val;
		अवरोध;

	हाल V4L2_CID_DEINTERLACING_MODE:
		ctx->deपूर्णांक_mode = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fdp1_ctrl_ops = अणु
	.s_ctrl = fdp1_s_ctrl,
	.g_अस्थिर_ctrl = fdp1_g_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर fdp1_ctrl_deपूर्णांक_menu[] = अणु
	"Progressive",
	"Adaptive 2D/3D",
	"Fixed 2D",
	"Fixed 3D",
	"Previous field",
	"Next field",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops fdp1_ioctl_ops = अणु
	.vidioc_querycap	= fdp1_vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= fdp1_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= fdp1_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mplane	= fdp1_g_fmt,
	.vidioc_g_fmt_vid_out_mplane	= fdp1_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= fdp1_try_fmt,
	.vidioc_try_fmt_vid_out_mplane	= fdp1_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane	= fdp1_s_fmt,
	.vidioc_s_fmt_vid_out_mplane	= fdp1_s_fmt,

	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf		= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf		= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs	= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,

	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/*
 * Queue operations
 */

अटल पूर्णांक fdp1_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_ctxs[])
अणु
	काष्ठा fdp1_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा fdp1_q_data *q_data;
	अचिन्हित पूर्णांक i;

	q_data = get_q_data(ctx, vq->type);

	अगर (*nplanes) अणु
		अगर (*nplanes > FDP1_MAX_PLANES)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	*nplanes = q_data->क्रमmat.num_planes;

	क्रम (i = 0; i < *nplanes; i++)
		sizes[i] = q_data->क्रमmat.plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण

अटल व्योम fdp1_buf_prepare_field(काष्ठा fdp1_q_data *q_data,
				   काष्ठा vb2_v4l2_buffer *vbuf,
				   अचिन्हित पूर्णांक field_num)
अणु
	काष्ठा fdp1_buffer *buf = to_fdp1_buffer(vbuf);
	काष्ठा fdp1_field_buffer *fbuf = &buf->fields[field_num];
	अचिन्हित पूर्णांक num_fields;
	अचिन्हित पूर्णांक i;

	num_fields = V4L2_FIELD_HAS_BOTH(vbuf->field) ? 2 : 1;

	fbuf->vb = vbuf;
	fbuf->last_field = (field_num + 1) == num_fields;

	क्रम (i = 0; i < vbuf->vb2_buf.num_planes; ++i)
		fbuf->addrs[i] = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, i);

	चयन (vbuf->field) अणु
	हाल V4L2_FIELD_INTERLACED:
		/*
		 * Interlaced means bottom-top क्रम 60Hz TV standards (NTSC) and
		 * top-bottom क्रम 50Hz. As TV standards are not applicable to
		 * the mem-to-mem API, use the height as a heuristic.
		 */
		fbuf->field = (q_data->क्रमmat.height < 576) == field_num
			    ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_SEQ_TB:
		fbuf->field = field_num ? V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_BT:
	हाल V4L2_FIELD_SEQ_BT:
		fbuf->field = field_num ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM;
		अवरोध;
	शेष:
		fbuf->field = vbuf->field;
		अवरोध;
	पूर्ण

	/* Buffer is completed */
	अगर (!field_num)
		वापस;

	/* Adjust buffer addresses क्रम second field */
	चयन (vbuf->field) अणु
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
		क्रम (i = 0; i < vbuf->vb2_buf.num_planes; i++)
			fbuf->addrs[i] +=
				(i == 0 ? q_data->stride_y : q_data->stride_c);
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		क्रम (i = 0; i < vbuf->vb2_buf.num_planes; i++)
			fbuf->addrs[i] += q_data->vsize *
				(i == 0 ? q_data->stride_y : q_data->stride_c);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fdp1_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा fdp1_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा fdp1_q_data *q_data = get_q_data(ctx, vb->vb2_queue->type);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा fdp1_buffer *buf = to_fdp1_buffer(vbuf);
	अचिन्हित पूर्णांक i;

	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		bool field_valid = true;

		/* Validate the buffer field. */
		चयन (q_data->क्रमmat.field) अणु
		हाल V4L2_FIELD_NONE:
			अगर (vbuf->field != V4L2_FIELD_NONE)
				field_valid = false;
			अवरोध;

		हाल V4L2_FIELD_ALTERNATE:
			अगर (vbuf->field != V4L2_FIELD_TOP &&
			    vbuf->field != V4L2_FIELD_BOTTOM)
				field_valid = false;
			अवरोध;

		हाल V4L2_FIELD_INTERLACED:
		हाल V4L2_FIELD_SEQ_TB:
		हाल V4L2_FIELD_SEQ_BT:
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
			अगर (vbuf->field != q_data->क्रमmat.field)
				field_valid = false;
			अवरोध;
		पूर्ण

		अगर (!field_valid) अणु
			dprपूर्णांकk(ctx->fdp1,
				"buffer field %u invalid for format field %u\n",
				vbuf->field, q_data->क्रमmat.field);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		vbuf->field = V4L2_FIELD_NONE;
	पूर्ण

	/* Validate the planes sizes. */
	क्रम (i = 0; i < q_data->क्रमmat.num_planes; i++) अणु
		अचिन्हित दीर्घ size = q_data->क्रमmat.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < size) अणु
			dprपूर्णांकk(ctx->fdp1,
				"data will not fit into plane [%u/%u] (%lu < %lu)\n",
				i, q_data->क्रमmat.num_planes,
				vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण

		/* We have known size क्रमmats all around */
		vb2_set_plane_payload(vb, i, size);
	पूर्ण

	buf->num_fields = V4L2_FIELD_HAS_BOTH(vbuf->field) ? 2 : 1;
	क्रम (i = 0; i < buf->num_fields; ++i)
		fdp1_buf_prepare_field(q_data, vbuf, i);

	वापस 0;
पूर्ण

अटल व्योम fdp1_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा fdp1_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक fdp1_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा fdp1_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा fdp1_q_data *q_data = get_q_data(ctx, q->type);

	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		/*
		 * Force our deपूर्णांक_mode when we are progressive,
		 * ignoring any setting on the device from the user,
		 * Otherwise, lock in the requested de-पूर्णांकerlace mode.
		 */
		अगर (q_data->क्रमmat.field == V4L2_FIELD_NONE)
			ctx->deपूर्णांक_mode = FDP1_PROGRESSIVE;

		अगर (ctx->deपूर्णांक_mode == FDP1_ADAPT2D3D) अणु
			u32 stride;
			dma_addr_t smsk_base;
			स्थिर u32 bpp = 2; /* bytes per pixel */

			stride = round_up(q_data->क्रमmat.width, 8);

			ctx->smsk_size = bpp * stride * q_data->vsize;

			ctx->smsk_cpu = dma_alloc_coherent(ctx->fdp1->dev,
				ctx->smsk_size, &smsk_base, GFP_KERNEL);

			अगर (ctx->smsk_cpu == शून्य) अणु
				dprपूर्णांकk(ctx->fdp1, "Failed to alloc smsk\n");
				वापस -ENOMEM;
			पूर्ण

			ctx->smsk_addr[0] = smsk_base;
			ctx->smsk_addr[1] = smsk_base + (ctx->smsk_size/2);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fdp1_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा fdp1_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (vbuf == शून्य)
			अवरोध;
		spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
		v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);
	पूर्ण

	/* Empty Output queues */
	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		/* Empty our पूर्णांकernal queues */
		काष्ठा fdp1_field_buffer *fbuf;

		/* Free any queued buffers */
		fbuf = fdp1_dequeue_field(ctx);
		जबतक (fbuf != शून्य) अणु
			fdp1_field_complete(ctx, fbuf);
			fbuf = fdp1_dequeue_field(ctx);
		पूर्ण

		/* Free smsk_data */
		अगर (ctx->smsk_cpu) अणु
			dma_मुक्त_coherent(ctx->fdp1->dev, ctx->smsk_size,
					  ctx->smsk_cpu, ctx->smsk_addr[0]);
			ctx->smsk_addr[0] = ctx->smsk_addr[1] = 0;
			ctx->smsk_cpu = शून्य;
		पूर्ण

		WARN(!list_empty(&ctx->fields_queue),
		     "Buffer queue not empty");
	पूर्ण अन्यथा अणु
		/* Empty Capture queues (Jobs) */
		काष्ठा fdp1_job *job;

		job = get_queued_job(ctx->fdp1);
		जबतक (job) अणु
			अगर (FDP1_DEINT_MODE_USES_PREV(ctx->deपूर्णांक_mode))
				fdp1_field_complete(ctx, job->previous);
			अन्यथा
				fdp1_field_complete(ctx, job->active);

			v4l2_m2m_buf_करोne(job->dst->vb, VB2_BUF_STATE_ERROR);
			job->dst = शून्य;

			job = get_queued_job(ctx->fdp1);
		पूर्ण

		/* Free any held buffer in the ctx */
		fdp1_field_complete(ctx, ctx->previous);

		WARN(!list_empty(&ctx->fdp1->queued_job_list),
		     "Queued Job List not empty");

		WARN(!list_empty(&ctx->fdp1->hw_job_list),
		     "HW Job list not empty");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops fdp1_qops = अणु
	.queue_setup	 = fdp1_queue_setup,
	.buf_prepare	 = fdp1_buf_prepare,
	.buf_queue	 = fdp1_buf_queue,
	.start_streaming = fdp1_start_streaming,
	.stop_streaming  = fdp1_stop_streaming,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा fdp1_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा fdp1_buffer);
	src_vq->ops = &fdp1_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->fdp1->dev_mutex;
	src_vq->dev = ctx->fdp1->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा fdp1_buffer);
	dst_vq->ops = &fdp1_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->fdp1->dev_mutex;
	dst_vq->dev = ctx->fdp1->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * File operations
 */
अटल पूर्णांक fdp1_खोलो(काष्ठा file *file)
अणु
	काष्ठा fdp1_dev *fdp1 = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat_mplane क्रमmat;
	काष्ठा fdp1_ctx *ctx = शून्य;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&fdp1->dev_mutex))
		वापस -ERESTARTSYS;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->fdp1 = fdp1;

	/* Initialise Queues */
	INIT_LIST_HEAD(&ctx->fields_queue);

	ctx->translen = 1;
	ctx->sequence = 0;

	/* Initialise controls */

	v4l2_ctrl_handler_init(&ctx->hdl, 3);
	v4l2_ctrl_new_std_menu_items(&ctx->hdl, &fdp1_ctrl_ops,
				     V4L2_CID_DEINTERLACING_MODE,
				     FDP1_NEXTFIELD, BIT(0), FDP1_FIXED3D,
				     fdp1_ctrl_deपूर्णांक_menu);

	ctrl = v4l2_ctrl_new_std(&ctx->hdl, &fdp1_ctrl_ops,
				 V4L2_CID_MIN_BUFFERS_FOR_CAPTURE, 1, 2, 1, 1);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_new_std(&ctx->hdl, &fdp1_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	अगर (ctx->hdl.error) अणु
		ret = ctx->hdl.error;
		v4l2_ctrl_handler_मुक्त(&ctx->hdl);
		kमुक्त(ctx);
		जाओ करोne;
	पूर्ण

	ctx->fh.ctrl_handler = &ctx->hdl;
	v4l2_ctrl_handler_setup(&ctx->hdl);

	/* Configure शेष parameters. */
	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	fdp1_set_क्रमmat(ctx, &क्रमmat, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(fdp1->m2m_dev, ctx, &queue_init);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_मुक्त(&ctx->hdl);
		kमुक्त(ctx);
		जाओ करोne;
	पूर्ण

	/* Perक्रमm any घातer management required */
	pm_runसमय_get_sync(fdp1->dev);

	v4l2_fh_add(&ctx->fh);

	dprपूर्णांकk(fdp1, "Created instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

करोne:
	mutex_unlock(&fdp1->dev_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक fdp1_release(काष्ठा file *file)
अणु
	काष्ठा fdp1_dev *fdp1 = video_drvdata(file);
	काष्ठा fdp1_ctx *ctx = fh_to_ctx(file->निजी_data);

	dprपूर्णांकk(fdp1, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->hdl);
	mutex_lock(&fdp1->dev_mutex);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&fdp1->dev_mutex);
	kमुक्त(ctx);

	pm_runसमय_put(fdp1->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations fdp1_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fdp1_खोलो,
	.release	= fdp1_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device fdp1_videodev = अणु
	.name		= DRIVER_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &fdp1_fops,
	.device_caps	= V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING,
	.ioctl_ops	= &fdp1_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= fdp1_m2m_device_run,
	.job_पढ़ोy	= fdp1_m2m_job_पढ़ोy,
	.job_पात	= fdp1_m2m_job_पात,
पूर्ण;

अटल irqवापस_t fdp1_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fdp1_dev *fdp1 = dev_id;
	u32 पूर्णांक_status;
	u32 ctl_status;
	u32 vपूर्णांक_cnt;
	u32 cycles;

	पूर्णांक_status = fdp1_पढ़ो(fdp1, FD1_CTL_IRQSTA);
	cycles = fdp1_पढ़ो(fdp1, FD1_CTL_VCYCLE_STAT);
	ctl_status = fdp1_पढ़ो(fdp1, FD1_CTL_STATUS);
	vपूर्णांक_cnt = (ctl_status & FD1_CTL_STATUS_VINT_CNT_MASK) >>
			FD1_CTL_STATUS_VINT_CNT_SHIFT;

	/* Clear पूर्णांकerrupts */
	fdp1_ग_लिखो(fdp1, ~(पूर्णांक_status) & FD1_CTL_IRQ_MASK, FD1_CTL_IRQSTA);

	अगर (debug >= 2) अणु
		dprपूर्णांकk(fdp1, "IRQ: 0x%x %s%s%s\n", पूर्णांक_status,
			पूर्णांक_status & FD1_CTL_IRQ_VERE ? "[Error]" : "[!E]",
			पूर्णांक_status & FD1_CTL_IRQ_VINTE ? "[VSync]" : "[!V]",
			पूर्णांक_status & FD1_CTL_IRQ_FREE ? "[FrameEnd]" : "[!F]");

		dprपूर्णांकk(fdp1, "CycleStatus = %d (%dms)\n",
			cycles, cycles/(fdp1->clk_rate/1000));

		dprपूर्णांकk(fdp1,
			"Control Status = 0x%08x : VINT_CNT = %d %s:%s:%s:%s\n",
			ctl_status, vपूर्णांक_cnt,
			ctl_status & FD1_CTL_STATUS_SGREGSET ? "RegSet" : "",
			ctl_status & FD1_CTL_STATUS_SGVERR ? "Vsync Error" : "",
			ctl_status & FD1_CTL_STATUS_SGFREND ? "FrameEnd" : "",
			ctl_status & FD1_CTL_STATUS_BSY ? "Busy" : "");
		dprपूर्णांकk(fdp1, "***********************************\n");
	पूर्ण

	/* Spurious पूर्णांकerrupt */
	अगर (!(FD1_CTL_IRQ_MASK & पूर्णांक_status))
		वापस IRQ_NONE;

	/* Work completed, release the frame */
	अगर (FD1_CTL_IRQ_VERE & पूर्णांक_status)
		device_frame_end(fdp1, VB2_BUF_STATE_ERROR);
	अन्यथा अगर (FD1_CTL_IRQ_FREE & पूर्णांक_status)
		device_frame_end(fdp1, VB2_BUF_STATE_DONE);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fdp1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fdp1_dev *fdp1;
	काष्ठा video_device *vfd;
	काष्ठा device_node *fcp_node;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	पूर्णांक ret;
	पूर्णांक hw_version;

	fdp1 = devm_kzalloc(&pdev->dev, माप(*fdp1), GFP_KERNEL);
	अगर (!fdp1)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&fdp1->मुक्त_job_list);
	INIT_LIST_HEAD(&fdp1->queued_job_list);
	INIT_LIST_HEAD(&fdp1->hw_job_list);

	/* Initialise the jobs on the मुक्त list */
	क्रम (i = 0; i < ARRAY_SIZE(fdp1->jobs); i++)
		list_add(&fdp1->jobs[i].list, &fdp1->मुक्त_job_list);

	mutex_init(&fdp1->dev_mutex);

	spin_lock_init(&fdp1->irqlock);
	spin_lock_init(&fdp1->device_process_lock);
	fdp1->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, fdp1);

	/* Memory-mapped रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fdp1->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fdp1->regs))
		वापस PTR_ERR(fdp1->regs);

	/* Interrupt service routine registration */
	fdp1->irq = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot find IRQ\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, fdp1->irq, fdp1_irq_handler, 0,
			       dev_name(&pdev->dev), fdp1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", fdp1->irq);
		वापस ret;
	पूर्ण

	/* FCP */
	fcp_node = of_parse_phandle(pdev->dev.of_node, "renesas,fcp", 0);
	अगर (fcp_node) अणु
		fdp1->fcp = rcar_fcp_get(fcp_node);
		of_node_put(fcp_node);
		अगर (IS_ERR(fdp1->fcp)) अणु
			dev_dbg(&pdev->dev, "FCP not found (%ld)\n",
				PTR_ERR(fdp1->fcp));
			वापस PTR_ERR(fdp1->fcp);
		पूर्ण
	पूर्ण

	/* Determine our घड़ी rate */
	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	fdp1->clk_rate = clk_get_rate(clk);
	clk_put(clk);

	/* V4L2 device registration */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &fdp1->v4l2_dev);
	अगर (ret) अणु
		v4l2_err(&fdp1->v4l2_dev, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	/* M2M registration */
	fdp1->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(fdp1->m2m_dev)) अणु
		v4l2_err(&fdp1->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(fdp1->m2m_dev);
		जाओ unreg_dev;
	पूर्ण

	/* Video registration */
	fdp1->vfd = fdp1_videodev;
	vfd = &fdp1->vfd;
	vfd->lock = &fdp1->dev_mutex;
	vfd->v4l2_dev = &fdp1->v4l2_dev;
	video_set_drvdata(vfd, fdp1);
	strscpy(vfd->name, fdp1_videodev.name, माप(vfd->name));

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&fdp1->v4l2_dev, "Failed to register video device\n");
		जाओ release_m2m;
	पूर्ण

	v4l2_info(&fdp1->v4l2_dev, "Device registered as /dev/video%d\n",
		  vfd->num);

	/* Power up the cells to पढ़ो HW */
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(fdp1->dev);

	hw_version = fdp1_पढ़ो(fdp1, FD1_IP_INTDATA);
	चयन (hw_version) अणु
	हाल FD1_IP_H3_ES1:
		dprपूर्णांकk(fdp1, "FDP1 Version R-Car H3 ES1\n");
		अवरोध;
	हाल FD1_IP_M3W:
		dprपूर्णांकk(fdp1, "FDP1 Version R-Car M3-W\n");
		अवरोध;
	हाल FD1_IP_H3:
		dprपूर्णांकk(fdp1, "FDP1 Version R-Car H3\n");
		अवरोध;
	हाल FD1_IP_M3N:
		dprपूर्णांकk(fdp1, "FDP1 Version R-Car M3-N\n");
		अवरोध;
	हाल FD1_IP_E3:
		dprपूर्णांकk(fdp1, "FDP1 Version R-Car E3\n");
		अवरोध;
	शेष:
		dev_err(fdp1->dev, "FDP1 Unidentifiable (0x%08x)\n",
			hw_version);
	पूर्ण

	/* Allow the hw to sleep until an खोलो call माला_दो it to use */
	pm_runसमय_put(fdp1->dev);

	वापस 0;

release_m2m:
	v4l2_m2m_release(fdp1->m2m_dev);

unreg_dev:
	v4l2_device_unरेजिस्टर(&fdp1->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक fdp1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fdp1_dev *fdp1 = platक्रमm_get_drvdata(pdev);

	v4l2_m2m_release(fdp1->m2m_dev);
	video_unरेजिस्टर_device(&fdp1->vfd);
	v4l2_device_unरेजिस्टर(&fdp1->v4l2_dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fdp1_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fdp1_dev *fdp1 = dev_get_drvdata(dev);

	rcar_fcp_disable(fdp1->fcp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fdp1_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fdp1_dev *fdp1 = dev_get_drvdata(dev);

	/* Program in the अटल LUTs */
	fdp1_set_lut(fdp1);

	वापस rcar_fcp_enable(fdp1->fcp);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fdp1_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fdp1_pm_runसमय_suspend,
			   fdp1_pm_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id fdp1_dt_ids[] = अणु
	अणु .compatible = "renesas,fdp1" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fdp1_dt_ids);

अटल काष्ठा platक्रमm_driver fdp1_pdrv = अणु
	.probe		= fdp1_probe,
	.हटाओ		= fdp1_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = fdp1_dt_ids,
		.pm	= &fdp1_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fdp1_pdrv);

MODULE_DESCRIPTION("Renesas R-Car Fine Display Processor Driver");
MODULE_AUTHOR("Kieran Bingham <kieran@bingham.xyz>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
