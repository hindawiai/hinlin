<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    (c) 2020 Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
 */

#अगर_अघोषित __SYSTEM_GLOBAL_H_INCLUDED__
#घोषणा __SYSTEM_GLOBAL_H_INCLUDED__

/*
 * Create a list of HAS and IS properties that defines the प्रणाली
 * Those are common क्रम both ISP2400 and ISP2401
 *
 * The configuration assumes the following
 * - The प्रणाली is hetereogeneous; Multiple cells and devices classes
 * - The cell and device instances are homogeneous, each device type
 *   beदीर्घs to the same class
 * - Device instances supporting a subset of the class capabilities are
 *   allowed
 *
 * We could manage dअगरferent device classes through the क्रमागतerated
 * lists (C) or the use of classes (C++), but that is presently not
 * fully supported
 *
 * N.B. the 3 input क्रमmatters are of 2 dअगरferent classess
 */

/* per-frame parameter handling support */
#घोषणा SH_CSS_ENABLE_PER_FRAME_PARAMS

#घोषणा DMA_DDR_TO_VAMEM_WORKAROUND
#घोषणा DMA_DDR_TO_HMEM_WORKAROUND

/*
 * The दीर्घest allowed (unपूर्णांकeruptible) bus transfer, करोes not
 * take stalling पूर्णांकo account
 */
#घोषणा HIVE_ISP_MAX_BURST_LENGTH	1024

/*
 * Maximum allowed burst length in words क्रम the ISP DMA
 * This value is set to 2 to prevent the ISP DMA from blocking
 * the bus क्रम too दीर्घ; as the input प्रणाली can only buffer
 * 2 lines on Moorefield and Cherrytrail, the input प्रणाली buffers
 * may overflow अगर blocked क्रम too दीर्घ (BZ 2726).
 */
#घोषणा ISP2400_DMA_MAX_BURST_LENGTH	128
#घोषणा ISP2401_DMA_MAX_BURST_LENGTH	2

#समावेश <hive_isp_css_defs.h>
#समावेश <type_support.h>

/* This पूर्णांकerface is deprecated */
#समावेश "hive_types.h"

/*
 * Semi global. "HRT" is accessible from SP, but the HRT types करो not fully apply
 */
#घोषणा HRT_VADDRESS_WIDTH	32

#घोषणा SIZखातापूर्ण_HRT_REG		(HRT_DATA_WIDTH >> 3)
#घोषणा HIVE_ISP_CTRL_DATA_BYTES (HIVE_ISP_CTRL_DATA_WIDTH / 8)

/* The मुख्य bus connecting all devices */
#घोषणा HRT_BUS_WIDTH		HIVE_ISP_CTRL_DATA_WIDTH
#घोषणा HRT_BUS_BYTES		HIVE_ISP_CTRL_DATA_BYTES

प्रकार u32			hrt_bus_align_t;

/*
 * Enumerate the devices, device access through the API is by ID,
 * through the DLI by address. The क्रमागतerator terminators are used
 * to size the wiring arrays and as an exception value.
 */
प्रकार क्रमागत अणु
	DDR0_ID = 0,
	N_DDR_ID
पूर्ण ddr_ID_t;

प्रकार क्रमागत अणु
	ISP0_ID = 0,
	N_ISP_ID
पूर्ण isp_ID_t;

प्रकार क्रमागत अणु
	SP0_ID = 0,
	N_SP_ID
पूर्ण sp_ID_t;

प्रकार क्रमागत अणु
	MMU0_ID = 0,
	MMU1_ID,
	N_MMU_ID
पूर्ण mmu_ID_t;

प्रकार क्रमागत अणु
	DMA0_ID = 0,
	N_DMA_ID
पूर्ण dma_ID_t;

प्रकार क्रमागत अणु
	GDC0_ID = 0,
	GDC1_ID,
	N_GDC_ID
पूर्ण gdc_ID_t;

/* this extra define is needed because we want to use it also
   in the preprocessor, and that करोesn't work with क्रमागतs.
 */
#घोषणा N_GDC_ID_CPP 2

प्रकार क्रमागत अणु
	VAMEM0_ID = 0,
	VAMEM1_ID,
	VAMEM2_ID,
	N_VAMEM_ID
पूर्ण vamem_ID_t;

प्रकार क्रमागत अणु
	BAMEM0_ID = 0,
	N_BAMEM_ID
पूर्ण bamem_ID_t;

प्रकार क्रमागत अणु
	HMEM0_ID = 0,
	N_HMEM_ID
पूर्ण hmem_ID_t;

प्रकार क्रमागत अणु
	IRQ0_ID = 0,	/* GP IRQ block */
	IRQ1_ID,	/* Input क्रमmatter */
	IRQ2_ID,	/* input प्रणाली */
	IRQ3_ID,	/* input selector */
	N_IRQ_ID
पूर्ण irq_ID_t;

प्रकार क्रमागत अणु
	FIFO_MONITOR0_ID = 0,
	N_FIFO_MONITOR_ID
पूर्ण fअगरo_monitor_ID_t;

प्रकार क्रमागत अणु
	GP_DEVICE0_ID = 0,
	N_GP_DEVICE_ID
पूर्ण gp_device_ID_t;

प्रकार क्रमागत अणु
	GP_TIMER0_ID = 0,
	GP_TIMER1_ID,
	GP_TIMER2_ID,
	GP_TIMER3_ID,
	GP_TIMER4_ID,
	GP_TIMER5_ID,
	GP_TIMER6_ID,
	GP_TIMER7_ID,
	N_GP_TIMER_ID
पूर्ण gp_समयr_ID_t;

प्रकार क्रमागत अणु
	GPIO0_ID = 0,
	N_GPIO_ID
पूर्ण gpio_ID_t;

प्रकार क्रमागत अणु
	TIMED_CTRL0_ID = 0,
	N_TIMED_CTRL_ID
पूर्ण समयd_ctrl_ID_t;

प्रकार क्रमागत अणु
	INPUT_FORMATTER0_ID = 0,
	INPUT_FORMATTER1_ID,
	INPUT_FORMATTER2_ID,
	INPUT_FORMATTER3_ID,
	N_INPUT_FORMATTER_ID
पूर्ण input_क्रमmatter_ID_t;

/* The IF RST is outside the IF */
#घोषणा INPUT_FORMATTER0_SRST_OFFSET	0x0824
#घोषणा INPUT_FORMATTER1_SRST_OFFSET	0x0624
#घोषणा INPUT_FORMATTER2_SRST_OFFSET	0x0424
#घोषणा INPUT_FORMATTER3_SRST_OFFSET	0x0224

#घोषणा INPUT_FORMATTER0_SRST_MASK		0x0001
#घोषणा INPUT_FORMATTER1_SRST_MASK		0x0002
#घोषणा INPUT_FORMATTER2_SRST_MASK		0x0004
#घोषणा INPUT_FORMATTER3_SRST_MASK		0x0008

प्रकार क्रमागत अणु
	INPUT_SYSTEM0_ID = 0,
	N_INPUT_SYSTEM_ID
पूर्ण input_प्रणाली_ID_t;

प्रकार क्रमागत अणु
	RX0_ID = 0,
	N_RX_ID
पूर्ण rx_ID_t;

क्रमागत mipi_port_id अणु
	MIPI_PORT0_ID = 0,
	MIPI_PORT1_ID,
	MIPI_PORT2_ID,
	N_MIPI_PORT_ID
पूर्ण;

#घोषणा	N_RX_CHANNEL_ID		4

/* Generic port क्रमागतeration with an पूर्णांकernal port type ID */
प्रकार क्रमागत अणु
	CSI_PORT0_ID = 0,
	CSI_PORT1_ID,
	CSI_PORT2_ID,
	TPG_PORT0_ID,
	PRBS_PORT0_ID,
	FIFO_PORT0_ID,
	MEMORY_PORT0_ID,
	N_INPUT_PORT_ID
पूर्ण input_port_ID_t;

प्रकार क्रमागत अणु
	CAPTURE_UNIT0_ID = 0,
	CAPTURE_UNIT1_ID,
	CAPTURE_UNIT2_ID,
	ACQUISITION_UNIT0_ID,
	DMA_UNIT0_ID,
	CTRL_UNIT0_ID,
	GPREGS_UNIT0_ID,
	FIFO_UNIT0_ID,
	IRQ_UNIT0_ID,
	N_SUB_SYSTEM_ID
पूर्ण sub_प्रणाली_ID_t;

#घोषणा	N_CAPTURE_UNIT_ID		3
#घोषणा	N_ACQUISITION_UNIT_ID		1
#घोषणा	N_CTRL_UNIT_ID			1


क्रमागत ia_css_isp_memories अणु
	IA_CSS_ISP_PMEM0 = 0,
	IA_CSS_ISP_DMEM0,
	IA_CSS_ISP_VMEM0,
	IA_CSS_ISP_VAMEM0,
	IA_CSS_ISP_VAMEM1,
	IA_CSS_ISP_VAMEM2,
	IA_CSS_ISP_HMEM0,
	IA_CSS_SP_DMEM0,
	IA_CSS_DDR,
	N_IA_CSS_MEMORIES
पूर्ण;

#घोषणा IA_CSS_NUM_MEMORIES 9
/* For driver compatibility */
#घोषणा N_IA_CSS_ISP_MEMORIES   IA_CSS_NUM_MEMORIES
#घोषणा IA_CSS_NUM_ISP_MEMORIES IA_CSS_NUM_MEMORIES

/*
 * ISP2401 specअगरic क्रमागतs
 */

प्रकार क्रमागत अणु
	ISYS_IRQ0_ID = 0,	/* port a */
	ISYS_IRQ1_ID,	/* port b */
	ISYS_IRQ2_ID,	/* port c */
	N_ISYS_IRQ_ID
पूर्ण isys_irq_ID_t;


/*
 * Input-buffer Controller.
 */
प्रकार क्रमागत अणु
	IBUF_CTRL0_ID = 0,	/* map to ISYS2401_IBUF_CNTRL_A */
	IBUF_CTRL1_ID,		/* map to ISYS2401_IBUF_CNTRL_B */
	IBUF_CTRL2_ID,		/* map ISYS2401_IBUF_CNTRL_C */
	N_IBUF_CTRL_ID
पूर्ण ibuf_ctrl_ID_t;
/* end of Input-buffer Controller */

/*
 * Stream2MMIO.
 */
प्रकार क्रमागत अणु
	STREAM2MMIO0_ID = 0,	/* map to ISYS2401_S2M_A */
	STREAM2MMIO1_ID,	/* map to ISYS2401_S2M_B */
	STREAM2MMIO2_ID,	/* map to ISYS2401_S2M_C */
	N_STREAM2MMIO_ID
पूर्ण stream2mmio_ID_t;

प्रकार क्रमागत अणु
	/*
	 * Stream2MMIO 0 has 8 SIDs that are indexed by
	 * [STREAM2MMIO_SID0_ID...STREAM2MMIO_SID7_ID].
	 *
	 * Stream2MMIO 1 has 4 SIDs that are indexed by
	 * [STREAM2MMIO_SID0_ID...TREAM2MMIO_SID3_ID].
	 *
	 * Stream2MMIO 2 has 4 SIDs that are indexed by
	 * [STREAM2MMIO_SID0_ID...STREAM2MMIO_SID3_ID].
	 */
	STREAM2MMIO_SID0_ID = 0,
	STREAM2MMIO_SID1_ID,
	STREAM2MMIO_SID2_ID,
	STREAM2MMIO_SID3_ID,
	STREAM2MMIO_SID4_ID,
	STREAM2MMIO_SID5_ID,
	STREAM2MMIO_SID6_ID,
	STREAM2MMIO_SID7_ID,
	N_STREAM2MMIO_SID_ID
पूर्ण stream2mmio_sid_ID_t;
/* end of Stream2MMIO */

/**
 * Input System 2401: CSI-MIPI recevier.
 */
प्रकार क्रमागत अणु
	CSI_RX_BACKEND0_ID = 0,	/* map to ISYS2401_MIPI_BE_A */
	CSI_RX_BACKEND1_ID,		/* map to ISYS2401_MIPI_BE_B */
	CSI_RX_BACKEND2_ID,		/* map to ISYS2401_MIPI_BE_C */
	N_CSI_RX_BACKEND_ID
पूर्ण csi_rx_backend_ID_t;

प्रकार क्रमागत अणु
	CSI_RX_FRONTEND0_ID = 0,	/* map to ISYS2401_CSI_RX_A */
	CSI_RX_FRONTEND1_ID,		/* map to ISYS2401_CSI_RX_B */
	CSI_RX_FRONTEND2_ID,		/* map to ISYS2401_CSI_RX_C */
#घोषणा N_CSI_RX_FRONTEND_ID (CSI_RX_FRONTEND2_ID + 1)
पूर्ण csi_rx_frontend_ID_t;

प्रकार क्रमागत अणु
	CSI_RX_DLANE0_ID = 0,		/* map to DLANE0 in CSI RX */
	CSI_RX_DLANE1_ID,		/* map to DLANE1 in CSI RX */
	CSI_RX_DLANE2_ID,		/* map to DLANE2 in CSI RX */
	CSI_RX_DLANE3_ID,		/* map to DLANE3 in CSI RX */
	N_CSI_RX_DLANE_ID
पूर्ण csi_rx_fe_dlane_ID_t;
/* end of CSI-MIPI receiver */

प्रकार क्रमागत अणु
	ISYS2401_DMA0_ID = 0,
	N_ISYS2401_DMA_ID
पूर्ण isys2401_dma_ID_t;

/**
 * Pixel-generator. ("system_global.h")
 */
प्रकार क्रमागत अणु
	PIXELGEN0_ID = 0,
	PIXELGEN1_ID,
	PIXELGEN2_ID,
	N_PIXELGEN_ID
पूर्ण pixelgen_ID_t;
/* end of pixel-generator. ("system_global.h") */

प्रकार क्रमागत अणु
	INPUT_SYSTEM_CSI_PORT0_ID = 0,
	INPUT_SYSTEM_CSI_PORT1_ID,
	INPUT_SYSTEM_CSI_PORT2_ID,

	INPUT_SYSTEM_PIXELGEN_PORT0_ID,
	INPUT_SYSTEM_PIXELGEN_PORT1_ID,
	INPUT_SYSTEM_PIXELGEN_PORT2_ID,

	N_INPUT_SYSTEM_INPUT_PORT_ID
पूर्ण input_प्रणाली_input_port_ID_t;

#घोषणा N_INPUT_SYSTEM_CSI_PORT	3

प्रकार क्रमागत अणु
	ISYS2401_DMA_CHANNEL_0 = 0,
	ISYS2401_DMA_CHANNEL_1,
	ISYS2401_DMA_CHANNEL_2,
	ISYS2401_DMA_CHANNEL_3,
	ISYS2401_DMA_CHANNEL_4,
	ISYS2401_DMA_CHANNEL_5,
	ISYS2401_DMA_CHANNEL_6,
	ISYS2401_DMA_CHANNEL_7,
	ISYS2401_DMA_CHANNEL_8,
	ISYS2401_DMA_CHANNEL_9,
	ISYS2401_DMA_CHANNEL_10,
	ISYS2401_DMA_CHANNEL_11,
	N_ISYS2401_DMA_CHANNEL
पूर्ण isys2401_dma_channel;

#पूर्ण_अगर /* __SYSTEM_GLOBAL_H_INCLUDED__ */
