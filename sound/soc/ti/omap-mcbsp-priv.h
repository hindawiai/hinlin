<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OMAP Multi-Channel Buffered Serial Port
 *
 * Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 *          Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#अगर_अघोषित __OMAP_MCBSP_PRIV_H__
#घोषणा __OMAP_MCBSP_PRIV_H__

#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#अगर_घोषित CONFIG_ARCH_OMAP1
#घोषणा mcbsp_omap1()	1
#अन्यथा
#घोषणा mcbsp_omap1()	0
#पूर्ण_अगर

/* McBSP रेजिस्टर numbers. Register address offset = num * reg_step */
क्रमागत अणु
	/* Common रेजिस्टरs */
	OMAP_MCBSP_REG_SPCR2 = 4,
	OMAP_MCBSP_REG_SPCR1,
	OMAP_MCBSP_REG_RCR2,
	OMAP_MCBSP_REG_RCR1,
	OMAP_MCBSP_REG_XCR2,
	OMAP_MCBSP_REG_XCR1,
	OMAP_MCBSP_REG_SRGR2,
	OMAP_MCBSP_REG_SRGR1,
	OMAP_MCBSP_REG_MCR2,
	OMAP_MCBSP_REG_MCR1,
	OMAP_MCBSP_REG_RCERA,
	OMAP_MCBSP_REG_RCERB,
	OMAP_MCBSP_REG_XCERA,
	OMAP_MCBSP_REG_XCERB,
	OMAP_MCBSP_REG_PCR0,
	OMAP_MCBSP_REG_RCERC,
	OMAP_MCBSP_REG_RCERD,
	OMAP_MCBSP_REG_XCERC,
	OMAP_MCBSP_REG_XCERD,
	OMAP_MCBSP_REG_RCERE,
	OMAP_MCBSP_REG_RCERF,
	OMAP_MCBSP_REG_XCERE,
	OMAP_MCBSP_REG_XCERF,
	OMAP_MCBSP_REG_RCERG,
	OMAP_MCBSP_REG_RCERH,
	OMAP_MCBSP_REG_XCERG,
	OMAP_MCBSP_REG_XCERH,

	/* OMAP1-OMAP2420 रेजिस्टरs */
	OMAP_MCBSP_REG_DRR2 = 0,
	OMAP_MCBSP_REG_DRR1,
	OMAP_MCBSP_REG_DXR2,
	OMAP_MCBSP_REG_DXR1,

	/* OMAP2430 and onwards */
	OMAP_MCBSP_REG_DRR = 0,
	OMAP_MCBSP_REG_DXR = 2,
	OMAP_MCBSP_REG_SYSCON =	35,
	OMAP_MCBSP_REG_THRSH2,
	OMAP_MCBSP_REG_THRSH1,
	OMAP_MCBSP_REG_IRQST = 40,
	OMAP_MCBSP_REG_IRQEN,
	OMAP_MCBSP_REG_WAKEUPEN,
	OMAP_MCBSP_REG_XCCR,
	OMAP_MCBSP_REG_RCCR,
	OMAP_MCBSP_REG_XBUFFSTAT,
	OMAP_MCBSP_REG_RBUFFSTAT,
	OMAP_MCBSP_REG_SSELCR,
पूर्ण;

/************************** McBSP SPCR1 bit definitions ***********************/
#घोषणा RRST			BIT(0)
#घोषणा RRDY			BIT(1)
#घोषणा RFULL			BIT(2)
#घोषणा RSYNC_ERR		BIT(3)
#घोषणा RINTM(value)		(((value) & 0x3) << 4)	/* bits 4:5 */
#घोषणा ABIS			BIT(6)
#घोषणा DXENA			BIT(7)
#घोषणा CLKSTP(value)		(((value) & 0x3) << 11)	/* bits 11:12 */
#घोषणा RJUST(value)		(((value) & 0x3) << 13)	/* bits 13:14 */
#घोषणा ALB			BIT(15)
#घोषणा DLB			BIT(15)

/************************** McBSP SPCR2 bit definitions ***********************/
#घोषणा XRST			BIT(0)
#घोषणा XRDY			BIT(1)
#घोषणा XEMPTY			BIT(2)
#घोषणा XSYNC_ERR		BIT(3)
#घोषणा XINTM(value)		(((value) & 0x3) << 4)	/* bits 4:5 */
#घोषणा GRST			BIT(6)
#घोषणा FRST			BIT(7)
#घोषणा SOFT			BIT(8)
#घोषणा FREE			BIT(9)

/************************** McBSP PCR bit definitions *************************/
#घोषणा CLKRP			BIT(0)
#घोषणा CLKXP			BIT(1)
#घोषणा FSRP			BIT(2)
#घोषणा FSXP			BIT(3)
#घोषणा DR_STAT			BIT(4)
#घोषणा DX_STAT			BIT(5)
#घोषणा CLKS_STAT		BIT(6)
#घोषणा SCLKME			BIT(7)
#घोषणा CLKRM			BIT(8)
#घोषणा CLKXM			BIT(9)
#घोषणा FSRM			BIT(10)
#घोषणा FSXM			BIT(11)
#घोषणा RIOEN			BIT(12)
#घोषणा XIOEN			BIT(13)
#घोषणा IDLE_EN			BIT(14)

/************************** McBSP RCR1 bit definitions ************************/
#घोषणा RWDLEN1(value)		(((value) & 0x7) << 5)	/* Bits 5:7 */
#घोषणा RFRLEN1(value)		(((value) & 0x7f) << 8)	/* Bits 8:14 */

/************************** McBSP XCR1 bit definitions ************************/
#घोषणा XWDLEN1(value)		(((value) & 0x7) << 5)	/* Bits 5:7 */
#घोषणा XFRLEN1(value)		(((value) & 0x7f) << 8)	/* Bits 8:14 */

/*************************** McBSP RCR2 bit definitions ***********************/
#घोषणा RDATDLY(value)		((value) & 0x3)		/* Bits 0:1 */
#घोषणा RFIG			BIT(2)
#घोषणा RCOMPAND(value)		(((value) & 0x3) << 3)	/* Bits 3:4 */
#घोषणा RWDLEN2(value)		(((value) & 0x7) << 5)	/* Bits 5:7 */
#घोषणा RFRLEN2(value)		(((value) & 0x7f) << 8)	/* Bits 8:14 */
#घोषणा RPHASE			BIT(15)

/*************************** McBSP XCR2 bit definitions ***********************/
#घोषणा XDATDLY(value)		((value) & 0x3)		/* Bits 0:1 */
#घोषणा XFIG			BIT(2)
#घोषणा XCOMPAND(value)		(((value) & 0x3) << 3)	/* Bits 3:4 */
#घोषणा XWDLEN2(value)		(((value) & 0x7) << 5)	/* Bits 5:7 */
#घोषणा XFRLEN2(value)		(((value) & 0x7f) << 8)	/* Bits 8:14 */
#घोषणा XPHASE			BIT(15)

/************************* McBSP SRGR1 bit definitions ************************/
#घोषणा CLKGDV(value)		((value) & 0x7f)		/* Bits 0:7 */
#घोषणा FWID(value)		(((value) & 0xff) << 8)	/* Bits 8:15 */

/************************* McBSP SRGR2 bit definitions ************************/
#घोषणा FPER(value)		((value) & 0x0fff)	/* Bits 0:11 */
#घोषणा FSGM			BIT(12)
#घोषणा CLKSM			BIT(13)
#घोषणा CLKSP			BIT(14)
#घोषणा GSYNC			BIT(15)

/************************* McBSP MCR1 bit definitions *************************/
#घोषणा RMCM			BIT(0)
#घोषणा RCBLK(value)		(((value) & 0x7) << 2)	/* Bits 2:4 */
#घोषणा RPABLK(value)		(((value) & 0x3) << 5)	/* Bits 5:6 */
#घोषणा RPBBLK(value)		(((value) & 0x3) << 7)	/* Bits 7:8 */

/************************* McBSP MCR2 bit definitions *************************/
#घोषणा XMCM(value)		((value) & 0x3)		/* Bits 0:1 */
#घोषणा XCBLK(value)		(((value) & 0x7) << 2)	/* Bits 2:4 */
#घोषणा XPABLK(value)		(((value) & 0x3) << 5)	/* Bits 5:6 */
#घोषणा XPBBLK(value)		(((value) & 0x3) << 7)	/* Bits 7:8 */

/*********************** McBSP XCCR bit definitions *************************/
#घोषणा XDISABLE		BIT(0)
#घोषणा XDMAEN			BIT(3)
#घोषणा DILB			BIT(5)
#घोषणा XFULL_CYCLE		BIT(11)
#घोषणा DXENDLY(value)		(((value) & 0x3) << 12)	/* Bits 12:13 */
#घोषणा PPCONNECT		BIT(14)
#घोषणा EXTCLKGATE		BIT(15)

/********************** McBSP RCCR bit definitions *************************/
#घोषणा RDISABLE		BIT(0)
#घोषणा RDMAEN			BIT(3)
#घोषणा RFULL_CYCLE		BIT(11)

/********************** McBSP SYSCONFIG bit definitions ********************/
#घोषणा SOFTRST			BIT(1)
#घोषणा ENAWAKEUP		BIT(2)
#घोषणा SIDLEMODE(value)	(((value) & 0x3) << 3)
#घोषणा CLOCKACTIVITY(value)	(((value) & 0x3) << 8)

/********************** McBSP DMA operating modes **************************/
#घोषणा MCBSP_DMA_MODE_ELEMENT		0
#घोषणा MCBSP_DMA_MODE_THRESHOLD	1

/********************** McBSP WAKEUPEN/IRQST/IRQEN bit definitions *********/
#घोषणा RSYNCERREN		BIT(0)
#घोषणा RFSREN			BIT(1)
#घोषणा Rखातापूर्णEN			BIT(2)
#घोषणा RRDYEN			BIT(3)
#घोषणा RUNDFLEN		BIT(4)
#घोषणा ROVFLEN			BIT(5)
#घोषणा XSYNCERREN		BIT(7)
#घोषणा XFSXEN			BIT(8)
#घोषणा Xखातापूर्णEN			BIT(9)
#घोषणा XRDYEN			BIT(10)
#घोषणा XUNDFLEN		BIT(11)
#घोषणा XOVFLEN			BIT(12)
#घोषणा XEMPTYखातापूर्णEN		BIT(14)

/* Clock संकेत muxing options */
#घोषणा CLKR_SRC_CLKR		0 /* CLKR संकेत is from the CLKR pin */
#घोषणा CLKR_SRC_CLKX		1 /* CLKR संकेत is from the CLKX pin */
#घोषणा FSR_SRC_FSR		2 /* FSR संकेत is from the FSR pin */
#घोषणा FSR_SRC_FSX		3 /* FSR संकेत is from the FSX pin */

/* McBSP functional घड़ी sources */
#घोषणा MCBSP_CLKS_PRCM_SRC	0
#घोषणा MCBSP_CLKS_PAD_SRC	1

/* we करोn't करो multichannel क्रम now */
काष्ठा omap_mcbsp_reg_cfg अणु
	u16 spcr2;
	u16 spcr1;
	u16 rcr2;
	u16 rcr1;
	u16 xcr2;
	u16 xcr1;
	u16 srgr2;
	u16 srgr1;
	u16 mcr2;
	u16 mcr1;
	u16 pcr0;
	u16 rcerc;
	u16 rcerd;
	u16 xcerc;
	u16 xcerd;
	u16 rcere;
	u16 rcerf;
	u16 xcere;
	u16 xcerf;
	u16 rcerg;
	u16 rcerh;
	u16 xcerg;
	u16 xcerh;
	u16 xccr;
	u16 rccr;
पूर्ण;

काष्ठा omap_mcbsp_st_data;

काष्ठा omap_mcbsp अणु
	काष्ठा device *dev;
	काष्ठा clk *fclk;
	spinlock_t lock;
	अचिन्हित दीर्घ phys_base;
	अचिन्हित दीर्घ phys_dma_base;
	व्योम __iomem *io_base;
	u8 id;
	/*
	 * Flags indicating is the bus alपढ़ोy activated and configured by
	 * another substream
	 */
	पूर्णांक active;
	पूर्णांक configured;
	u8 मुक्त;

	पूर्णांक irq;
	पूर्णांक rx_irq;
	पूर्णांक tx_irq;

	/* Protect the field .मुक्त, जबतक checking अगर the mcbsp is in use */
	काष्ठा omap_mcbsp_platक्रमm_data *pdata;
	काष्ठा omap_mcbsp_st_data *st_data;
	काष्ठा omap_mcbsp_reg_cfg cfg_regs;
	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
	अचिन्हित पूर्णांक dma_req[2];
	पूर्णांक dma_op_mode;
	u16 max_tx_thres;
	u16 max_rx_thres;
	व्योम *reg_cache;
	पूर्णांक reg_cache_size;

	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक in_freq;
	अचिन्हित पूर्णांक latency[2];
	पूर्णांक clk_भाग;
	पूर्णांक wlen;

	काष्ठा pm_qos_request pm_qos_req;
पूर्ण;

अटल अंतरभूत व्योम omap_mcbsp_ग_लिखो(काष्ठा omap_mcbsp *mcbsp, u16 reg, u32 val)
अणु
	व्योम __iomem *addr = mcbsp->io_base + reg * mcbsp->pdata->reg_step;

	अगर (mcbsp->pdata->reg_size == 2) अणु
		((u16 *)mcbsp->reg_cache)[reg] = (u16)val;
		ग_लिखोw_relaxed((u16)val, addr);
	पूर्ण अन्यथा अणु
		((u32 *)mcbsp->reg_cache)[reg] = val;
		ग_लिखोl_relaxed(val, addr);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक omap_mcbsp_पढ़ो(काष्ठा omap_mcbsp *mcbsp, u16 reg,
				  bool from_cache)
अणु
	व्योम __iomem *addr = mcbsp->io_base + reg * mcbsp->pdata->reg_step;

	अगर (mcbsp->pdata->reg_size == 2) अणु
		वापस !from_cache ? पढ़ोw_relaxed(addr) :
				     ((u16 *)mcbsp->reg_cache)[reg];
	पूर्ण अन्यथा अणु
		वापस !from_cache ? पढ़ोl_relaxed(addr) :
				     ((u32 *)mcbsp->reg_cache)[reg];
	पूर्ण
पूर्ण

#घोषणा MCBSP_READ(mcbsp, reg) \
		omap_mcbsp_पढ़ो(mcbsp, OMAP_MCBSP_REG_##reg, 0)
#घोषणा MCBSP_WRITE(mcbsp, reg, val) \
		omap_mcbsp_ग_लिखो(mcbsp, OMAP_MCBSP_REG_##reg, val)
#घोषणा MCBSP_READ_CACHE(mcbsp, reg) \
		omap_mcbsp_पढ़ो(mcbsp, OMAP_MCBSP_REG_##reg, 1)


/* Sidetone specअगरic API */
पूर्णांक omap_mcbsp_st_init(काष्ठा platक्रमm_device *pdev);
व्योम omap_mcbsp_st_cleanup(काष्ठा platक्रमm_device *pdev);

पूर्णांक omap_mcbsp_st_start(काष्ठा omap_mcbsp *mcbsp);
पूर्णांक omap_mcbsp_st_stop(काष्ठा omap_mcbsp *mcbsp);

#पूर्ण_अगर /* __OMAP_MCBSP_PRIV_H__ */
