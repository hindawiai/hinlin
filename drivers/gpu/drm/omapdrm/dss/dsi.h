<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __OMAP_DRM_DSS_DSI_H
#घोषणा __OMAP_DRM_DSS_DSI_H

#समावेश <drm/drm_mipi_dsi.h>

काष्ठा dsi_reg अणु
	u16 module;
	u16 idx;
पूर्ण;

#घोषणा DSI_REG(mod, idx)		((स्थिर काष्ठा dsi_reg) अणु mod, idx पूर्ण)

/* DSI Protocol Engine */

#घोषणा DSI_PROTO			0
#घोषणा DSI_PROTO_SZ			0x200

#घोषणा DSI_REVISION			DSI_REG(DSI_PROTO, 0x0000)
#घोषणा DSI_SYSCONFIG			DSI_REG(DSI_PROTO, 0x0010)
#घोषणा DSI_SYSSTATUS			DSI_REG(DSI_PROTO, 0x0014)
#घोषणा DSI_IRQSTATUS			DSI_REG(DSI_PROTO, 0x0018)
#घोषणा DSI_IRQENABLE			DSI_REG(DSI_PROTO, 0x001C)
#घोषणा DSI_CTRL			DSI_REG(DSI_PROTO, 0x0040)
#घोषणा DSI_GNQ				DSI_REG(DSI_PROTO, 0x0044)
#घोषणा DSI_COMPLEXIO_CFG1		DSI_REG(DSI_PROTO, 0x0048)
#घोषणा DSI_COMPLEXIO_IRQ_STATUS	DSI_REG(DSI_PROTO, 0x004C)
#घोषणा DSI_COMPLEXIO_IRQ_ENABLE	DSI_REG(DSI_PROTO, 0x0050)
#घोषणा DSI_CLK_CTRL			DSI_REG(DSI_PROTO, 0x0054)
#घोषणा DSI_TIMING1			DSI_REG(DSI_PROTO, 0x0058)
#घोषणा DSI_TIMING2			DSI_REG(DSI_PROTO, 0x005C)
#घोषणा DSI_VM_TIMING1			DSI_REG(DSI_PROTO, 0x0060)
#घोषणा DSI_VM_TIMING2			DSI_REG(DSI_PROTO, 0x0064)
#घोषणा DSI_VM_TIMING3			DSI_REG(DSI_PROTO, 0x0068)
#घोषणा DSI_CLK_TIMING			DSI_REG(DSI_PROTO, 0x006C)
#घोषणा DSI_TX_FIFO_VC_SIZE		DSI_REG(DSI_PROTO, 0x0070)
#घोषणा DSI_RX_FIFO_VC_SIZE		DSI_REG(DSI_PROTO, 0x0074)
#घोषणा DSI_COMPLEXIO_CFG2		DSI_REG(DSI_PROTO, 0x0078)
#घोषणा DSI_RX_FIFO_VC_FULLNESS		DSI_REG(DSI_PROTO, 0x007C)
#घोषणा DSI_VM_TIMING4			DSI_REG(DSI_PROTO, 0x0080)
#घोषणा DSI_TX_FIFO_VC_EMPTINESS	DSI_REG(DSI_PROTO, 0x0084)
#घोषणा DSI_VM_TIMING5			DSI_REG(DSI_PROTO, 0x0088)
#घोषणा DSI_VM_TIMING6			DSI_REG(DSI_PROTO, 0x008C)
#घोषणा DSI_VM_TIMING7			DSI_REG(DSI_PROTO, 0x0090)
#घोषणा DSI_STOPCLK_TIMING		DSI_REG(DSI_PROTO, 0x0094)
#घोषणा DSI_VC_CTRL(n)			DSI_REG(DSI_PROTO, 0x0100 + (n * 0x20))
#घोषणा DSI_VC_TE(n)			DSI_REG(DSI_PROTO, 0x0104 + (n * 0x20))
#घोषणा DSI_VC_LONG_PACKET_HEADER(n)	DSI_REG(DSI_PROTO, 0x0108 + (n * 0x20))
#घोषणा DSI_VC_LONG_PACKET_PAYLOAD(n)	DSI_REG(DSI_PROTO, 0x010C + (n * 0x20))
#घोषणा DSI_VC_SHORT_PACKET_HEADER(n)	DSI_REG(DSI_PROTO, 0x0110 + (n * 0x20))
#घोषणा DSI_VC_IRQSTATUS(n)		DSI_REG(DSI_PROTO, 0x0118 + (n * 0x20))
#घोषणा DSI_VC_IRQENABLE(n)		DSI_REG(DSI_PROTO, 0x011C + (n * 0x20))

/* DSIPHY_SCP */

#घोषणा DSI_PHY				1
#घोषणा DSI_PHY_OFFSET			0x200
#घोषणा DSI_PHY_SZ			0x40

#घोषणा DSI_DSIPHY_CFG0			DSI_REG(DSI_PHY, 0x0000)
#घोषणा DSI_DSIPHY_CFG1			DSI_REG(DSI_PHY, 0x0004)
#घोषणा DSI_DSIPHY_CFG2			DSI_REG(DSI_PHY, 0x0008)
#घोषणा DSI_DSIPHY_CFG5			DSI_REG(DSI_PHY, 0x0014)
#घोषणा DSI_DSIPHY_CFG10		DSI_REG(DSI_PHY, 0x0028)

/* DSI_PLL_CTRL_SCP */

#घोषणा DSI_PLL				2
#घोषणा DSI_PLL_OFFSET			0x300
#घोषणा DSI_PLL_SZ			0x20

#घोषणा DSI_PLL_CONTROL			DSI_REG(DSI_PLL, 0x0000)
#घोषणा DSI_PLL_STATUS			DSI_REG(DSI_PLL, 0x0004)
#घोषणा DSI_PLL_GO			DSI_REG(DSI_PLL, 0x0008)
#घोषणा DSI_PLL_CONFIGURATION1		DSI_REG(DSI_PLL, 0x000C)
#घोषणा DSI_PLL_CONFIGURATION2		DSI_REG(DSI_PLL, 0x0010)

/* Global पूर्णांकerrupts */
#घोषणा DSI_IRQ_VC0		(1 << 0)
#घोषणा DSI_IRQ_VC1		(1 << 1)
#घोषणा DSI_IRQ_VC2		(1 << 2)
#घोषणा DSI_IRQ_VC3		(1 << 3)
#घोषणा DSI_IRQ_WAKEUP		(1 << 4)
#घोषणा DSI_IRQ_RESYNC		(1 << 5)
#घोषणा DSI_IRQ_PLL_LOCK	(1 << 7)
#घोषणा DSI_IRQ_PLL_UNLOCK	(1 << 8)
#घोषणा DSI_IRQ_PLL_RECALL	(1 << 9)
#घोषणा DSI_IRQ_COMPLEXIO_ERR	(1 << 10)
#घोषणा DSI_IRQ_HS_TX_TIMEOUT	(1 << 14)
#घोषणा DSI_IRQ_LP_RX_TIMEOUT	(1 << 15)
#घोषणा DSI_IRQ_TE_TRIGGER	(1 << 16)
#घोषणा DSI_IRQ_ACK_TRIGGER	(1 << 17)
#घोषणा DSI_IRQ_SYNC_LOST	(1 << 18)
#घोषणा DSI_IRQ_LDO_POWER_GOOD	(1 << 19)
#घोषणा DSI_IRQ_TA_TIMEOUT	(1 << 20)
#घोषणा DSI_IRQ_ERROR_MASK \
	(DSI_IRQ_HS_TX_TIMEOUT | DSI_IRQ_LP_RX_TIMEOUT | DSI_IRQ_SYNC_LOST | \
	DSI_IRQ_TA_TIMEOUT)
#घोषणा DSI_IRQ_CHANNEL_MASK	0xf

/* Virtual channel पूर्णांकerrupts */
#घोषणा DSI_VC_IRQ_CS		(1 << 0)
#घोषणा DSI_VC_IRQ_ECC_CORR	(1 << 1)
#घोषणा DSI_VC_IRQ_PACKET_SENT	(1 << 2)
#घोषणा DSI_VC_IRQ_FIFO_TX_OVF	(1 << 3)
#घोषणा DSI_VC_IRQ_FIFO_RX_OVF	(1 << 4)
#घोषणा DSI_VC_IRQ_BTA		(1 << 5)
#घोषणा DSI_VC_IRQ_ECC_NO_CORR	(1 << 6)
#घोषणा DSI_VC_IRQ_FIFO_TX_UDF	(1 << 7)
#घोषणा DSI_VC_IRQ_PP_BUSY_CHANGE (1 << 8)
#घोषणा DSI_VC_IRQ_ERROR_MASK \
	(DSI_VC_IRQ_CS | DSI_VC_IRQ_ECC_CORR | DSI_VC_IRQ_FIFO_TX_OVF | \
	DSI_VC_IRQ_FIFO_RX_OVF | DSI_VC_IRQ_ECC_NO_CORR | \
	DSI_VC_IRQ_FIFO_TX_UDF)

/* ComplexIO पूर्णांकerrupts */
#घोषणा DSI_CIO_IRQ_ERRSYNCESC1		(1 << 0)
#घोषणा DSI_CIO_IRQ_ERRSYNCESC2		(1 << 1)
#घोषणा DSI_CIO_IRQ_ERRSYNCESC3		(1 << 2)
#घोषणा DSI_CIO_IRQ_ERRSYNCESC4		(1 << 3)
#घोषणा DSI_CIO_IRQ_ERRSYNCESC5		(1 << 4)
#घोषणा DSI_CIO_IRQ_ERRESC1		(1 << 5)
#घोषणा DSI_CIO_IRQ_ERRESC2		(1 << 6)
#घोषणा DSI_CIO_IRQ_ERRESC3		(1 << 7)
#घोषणा DSI_CIO_IRQ_ERRESC4		(1 << 8)
#घोषणा DSI_CIO_IRQ_ERRESC5		(1 << 9)
#घोषणा DSI_CIO_IRQ_ERRCONTROL1		(1 << 10)
#घोषणा DSI_CIO_IRQ_ERRCONTROL2		(1 << 11)
#घोषणा DSI_CIO_IRQ_ERRCONTROL3		(1 << 12)
#घोषणा DSI_CIO_IRQ_ERRCONTROL4		(1 << 13)
#घोषणा DSI_CIO_IRQ_ERRCONTROL5		(1 << 14)
#घोषणा DSI_CIO_IRQ_STATEULPS1		(1 << 15)
#घोषणा DSI_CIO_IRQ_STATEULPS2		(1 << 16)
#घोषणा DSI_CIO_IRQ_STATEULPS3		(1 << 17)
#घोषणा DSI_CIO_IRQ_STATEULPS4		(1 << 18)
#घोषणा DSI_CIO_IRQ_STATEULPS5		(1 << 19)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP0_1	(1 << 20)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP1_1	(1 << 21)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP0_2	(1 << 22)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP1_2	(1 << 23)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP0_3	(1 << 24)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP1_3	(1 << 25)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP0_4	(1 << 26)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP1_4	(1 << 27)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP0_5	(1 << 28)
#घोषणा DSI_CIO_IRQ_ERRCONTENTIONLP1_5	(1 << 29)
#घोषणा DSI_CIO_IRQ_ULPSACTIVENOT_ALL0	(1 << 30)
#घोषणा DSI_CIO_IRQ_ULPSACTIVENOT_ALL1	(1 << 31)
#घोषणा DSI_CIO_IRQ_ERROR_MASK \
	(DSI_CIO_IRQ_ERRSYNCESC1 | DSI_CIO_IRQ_ERRSYNCESC2 | \
	 DSI_CIO_IRQ_ERRSYNCESC3 | DSI_CIO_IRQ_ERRSYNCESC4 | \
	 DSI_CIO_IRQ_ERRSYNCESC5 | \
	 DSI_CIO_IRQ_ERRESC1 | DSI_CIO_IRQ_ERRESC2 | \
	 DSI_CIO_IRQ_ERRESC3 | DSI_CIO_IRQ_ERRESC4 | \
	 DSI_CIO_IRQ_ERRESC5 | \
	 DSI_CIO_IRQ_ERRCONTROL1 | DSI_CIO_IRQ_ERRCONTROL2 | \
	 DSI_CIO_IRQ_ERRCONTROL3 | DSI_CIO_IRQ_ERRCONTROL4 | \
	 DSI_CIO_IRQ_ERRCONTROL5 | \
	 DSI_CIO_IRQ_ERRCONTENTIONLP0_1 | DSI_CIO_IRQ_ERRCONTENTIONLP1_1 | \
	 DSI_CIO_IRQ_ERRCONTENTIONLP0_2 | DSI_CIO_IRQ_ERRCONTENTIONLP1_2 | \
	 DSI_CIO_IRQ_ERRCONTENTIONLP0_3 | DSI_CIO_IRQ_ERRCONTENTIONLP1_3 | \
	 DSI_CIO_IRQ_ERRCONTENTIONLP0_4 | DSI_CIO_IRQ_ERRCONTENTIONLP1_4 | \
	 DSI_CIO_IRQ_ERRCONTENTIONLP0_5 | DSI_CIO_IRQ_ERRCONTENTIONLP1_5)

क्रमागत omap_dss_dsi_mode अणु
	OMAP_DSS_DSI_CMD_MODE = 0,
	OMAP_DSS_DSI_VIDEO_MODE,
पूर्ण;

क्रमागत omap_dss_dsi_trans_mode अणु
	/* Sync Pulses: both sync start and end packets sent */
	OMAP_DSS_DSI_PULSE_MODE,
	/* Sync Events: only sync start packets sent */
	OMAP_DSS_DSI_EVENT_MODE,
	/* Burst: only sync start packets sent, pixels are समय compressed */
	OMAP_DSS_DSI_BURST_MODE,
पूर्ण;

काष्ठा omap_dss_dsi_videomode_timings अणु
	अचिन्हित दीर्घ hsclk;

	अचिन्हित पूर्णांक ndl;
	अचिन्हित पूर्णांक bitspp;

	/* pixels */
	u16 hact;
	/* lines */
	u16 vact;

	/* DSI video mode blanking data */
	/* Unit: byte घड़ी cycles */
	u16 hss;
	u16 hsa;
	u16 hse;
	u16 hfp;
	u16 hbp;
	/* Unit: line घड़ीs */
	u16 vsa;
	u16 vfp;
	u16 vbp;

	/* DSI blanking modes */
	पूर्णांक blanking_mode;
	पूर्णांक hsa_blanking_mode;
	पूर्णांक hbp_blanking_mode;
	पूर्णांक hfp_blanking_mode;

	क्रमागत omap_dss_dsi_trans_mode trans_mode;

	पूर्णांक winकरोw_sync;
पूर्ण;

काष्ठा omap_dss_dsi_config अणु
	क्रमागत omap_dss_dsi_mode mode;
	क्रमागत mipi_dsi_pixel_क्रमmat pixel_क्रमmat;
	स्थिर काष्ठा videomode *vm;

	अचिन्हित दीर्घ hs_clk_min, hs_clk_max;
	अचिन्हित दीर्घ lp_clk_min, lp_clk_max;

	क्रमागत omap_dss_dsi_trans_mode trans_mode;
पूर्ण;

/* DSI PLL HSDIV indices */
#घोषणा HSDIV_DISPC	0
#घोषणा HSDIV_DSI	1

#घोषणा DSI_MAX_NR_ISRS                2
#घोषणा DSI_MAX_NR_LANES	5

क्रमागत dsi_model अणु
	DSI_MODEL_OMAP3,
	DSI_MODEL_OMAP4,
	DSI_MODEL_OMAP5,
पूर्ण;

क्रमागत dsi_lane_function अणु
	DSI_LANE_UNUSED	= 0,
	DSI_LANE_CLK,
	DSI_LANE_DATA1,
	DSI_LANE_DATA2,
	DSI_LANE_DATA3,
	DSI_LANE_DATA4,
पूर्ण;

काष्ठा dsi_lane_config अणु
	क्रमागत dsi_lane_function function;
	u8 polarity;
पूर्ण;

प्रकार व्योम (*omap_dsi_isr_t) (व्योम *arg, u32 mask);

काष्ठा dsi_isr_data अणु
	omap_dsi_isr_t	isr;
	व्योम		*arg;
	u32		mask;
पूर्ण;

क्रमागत fअगरo_size अणु
	DSI_FIFO_SIZE_0		= 0,
	DSI_FIFO_SIZE_32	= 1,
	DSI_FIFO_SIZE_64	= 2,
	DSI_FIFO_SIZE_96	= 3,
	DSI_FIFO_SIZE_128	= 4,
पूर्ण;

क्रमागत dsi_vc_source अणु
	DSI_VC_SOURCE_L4 = 0,
	DSI_VC_SOURCE_VP,
पूर्ण;

काष्ठा dsi_irq_stats अणु
	अचिन्हित दीर्घ last_reset;
	अचिन्हित पूर्णांक irq_count;
	अचिन्हित पूर्णांक dsi_irqs[32];
	अचिन्हित पूर्णांक vc_irqs[4][32];
	अचिन्हित पूर्णांक cio_irqs[32];
पूर्ण;

काष्ठा dsi_isr_tables अणु
	काष्ठा dsi_isr_data isr_table[DSI_MAX_NR_ISRS];
	काष्ठा dsi_isr_data isr_table_vc[4][DSI_MAX_NR_ISRS];
	काष्ठा dsi_isr_data isr_table_cio[DSI_MAX_NR_ISRS];
पूर्ण;

काष्ठा dsi_lp_घड़ी_info अणु
	अचिन्हित दीर्घ lp_clk;
	u16 lp_clk_भाग;
पूर्ण;

काष्ठा dsi_clk_calc_ctx अणु
	काष्ठा dsi_data *dsi;
	काष्ठा dss_pll *pll;

	/* inमाला_दो */

	स्थिर काष्ठा omap_dss_dsi_config *config;

	अचिन्हित दीर्घ req_pck_min, req_pck_nom, req_pck_max;

	/* outमाला_दो */

	काष्ठा dss_pll_घड़ी_info dsi_cinfo;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	काष्ठा dsi_lp_घड़ी_info lp_cinfo;

	काष्ठा videomode vm;
	काष्ठा omap_dss_dsi_videomode_timings dsi_vm;
पूर्ण;

काष्ठा dsi_module_id_data अणु
	u32 address;
	पूर्णांक id;
पूर्ण;

क्रमागत dsi_quirks अणु
	DSI_QUIRK_PLL_PWR_BUG = (1 << 0),	/* DSI-PLL घातer command 0x3 is not working */
	DSI_QUIRK_DCS_CMD_CONFIG_VC = (1 << 1),
	DSI_QUIRK_VC_OCP_WIDTH = (1 << 2),
	DSI_QUIRK_REVERSE_TXCLKESC = (1 << 3),
	DSI_QUIRK_GNQ = (1 << 4),
	DSI_QUIRK_PHY_DCC = (1 << 5),
पूर्ण;

काष्ठा dsi_of_data अणु
	क्रमागत dsi_model model;
	स्थिर काष्ठा dss_pll_hw *pll_hw;
	स्थिर काष्ठा dsi_module_id_data *modules;
	अचिन्हित पूर्णांक max_fck_freq;
	अचिन्हित पूर्णांक max_pll_lpभाग;
	क्रमागत dsi_quirks quirks;
पूर्ण;

काष्ठा dsi_data अणु
	काष्ठा device *dev;
	व्योम __iomem *proto_base;
	व्योम __iomem *phy_base;
	व्योम __iomem *pll_base;

	स्थिर काष्ठा dsi_of_data *data;
	पूर्णांक module_id;

	पूर्णांक irq;

	bool is_enabled;

	काष्ठा clk *dss_clk;
	काष्ठा regmap *syscon;
	काष्ठा dss_device *dss;

	काष्ठा mipi_dsi_host host;

	काष्ठा dispc_घड़ी_info user_dispc_cinfo;
	काष्ठा dss_pll_घड़ी_info user_dsi_cinfo;

	काष्ठा dsi_lp_घड़ी_info user_lp_cinfo;
	काष्ठा dsi_lp_घड़ी_info current_lp_cinfo;

	काष्ठा dss_pll pll;

	bool vdds_dsi_enabled;
	काष्ठा regulator *vdds_dsi_reg;

	काष्ठा mipi_dsi_device *dsidev;

	काष्ठा अणु
		क्रमागत dsi_vc_source source;
		क्रमागत fअगरo_size tx_fअगरo_size;
		क्रमागत fअगरo_size rx_fअगरo_size;
	पूर्ण vc[4];

	काष्ठा mutex lock;
	काष्ठा semaphore bus_lock;

	spinlock_t irq_lock;
	काष्ठा dsi_isr_tables isr_tables;
	/* space क्रम a copy used by the पूर्णांकerrupt handler */
	काष्ठा dsi_isr_tables isr_tables_copy;

	पूर्णांक update_vc;
#अगर_घोषित DSI_PERF_MEASURE
	अचिन्हित पूर्णांक update_bytes;
#पूर्ण_अगर

	/* बाह्यal TE GPIO */
	काष्ठा gpio_desc *te_gpio;
	पूर्णांक te_irq;
	काष्ठा delayed_work te_समयout_work;
	atomic_t करो_ext_te_update;

	bool te_enabled;
	bool अगरace_enabled;
	bool video_enabled;

	काष्ठा delayed_work frameकरोne_समयout_work;

#अगर_घोषित DSI_CATCH_MISSING_TE
	काष्ठा समयr_list te_समयr;
#पूर्ण_अगर

	अचिन्हित दीर्घ cache_req_pck;
	अचिन्हित दीर्घ cache_clk_freq;
	काष्ठा dss_pll_घड़ी_info cache_cinfo;

	u32		errors;
	spinlock_t	errors_lock;
#अगर_घोषित DSI_PERF_MEASURE
	kसमय_प्रकार perf_setup_समय;
	kसमय_प्रकार perf_start_समय;
#पूर्ण_अगर
	पूर्णांक debug_पढ़ो;
	पूर्णांक debug_ग_लिखो;
	काष्ठा अणु
		काष्ठा dss_debugfs_entry *irqs;
		काष्ठा dss_debugfs_entry *regs;
		काष्ठा dss_debugfs_entry *clks;
	पूर्ण debugfs;

#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
	spinlock_t irq_stats_lock;
	काष्ठा dsi_irq_stats irq_stats;
#पूर्ण_अगर

	अचिन्हित पूर्णांक num_lanes_supported;
	अचिन्हित पूर्णांक line_buffer_size;

	काष्ठा dsi_lane_config lanes[DSI_MAX_NR_LANES];
	अचिन्हित पूर्णांक num_lanes_used;

	अचिन्हित पूर्णांक scp_clk_refcount;

	काष्ठा omap_dss_dsi_config config;

	काष्ठा dss_lcd_mgr_config mgr_config;
	काष्ठा videomode vm;
	क्रमागत mipi_dsi_pixel_क्रमmat pix_fmt;
	क्रमागत omap_dss_dsi_mode mode;
	काष्ठा omap_dss_dsi_videomode_timings vm_timings;

	काष्ठा omap_dss_device output;
	काष्ठा drm_bridge bridge;

	काष्ठा delayed_work dsi_disable_work;
पूर्ण;

काष्ठा dsi_packet_sent_handler_data अणु
	काष्ठा dsi_data *dsi;
	काष्ठा completion *completion;
पूर्ण;

#पूर्ण_अगर /* __OMAP_DRM_DSS_DSI_H */
