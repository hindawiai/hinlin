<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2013-2014 Freescale Semiconductor, Inc.
 * Copyright 2018 Angelo Dureghello <angelo@sysam.it>
 */
#अगर_अघोषित _FSL_EDMA_COMMON_H_
#घोषणा _FSL_EDMA_COMMON_H_

#समावेश <linux/dma-direction.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "virt-dma.h"

#घोषणा EDMA_CR_EDBG		BIT(1)
#घोषणा EDMA_CR_ERCA		BIT(2)
#घोषणा EDMA_CR_ERGA		BIT(3)
#घोषणा EDMA_CR_HOE		BIT(4)
#घोषणा EDMA_CR_HALT		BIT(5)
#घोषणा EDMA_CR_CLM		BIT(6)
#घोषणा EDMA_CR_EMLM		BIT(7)
#घोषणा EDMA_CR_ECX		BIT(16)
#घोषणा EDMA_CR_CX		BIT(17)

#घोषणा EDMA_SEEI_SEEI(x)	((x) & GENMASK(4, 0))
#घोषणा EDMA_CEEI_CEEI(x)	((x) & GENMASK(4, 0))
#घोषणा EDMA_CINT_CINT(x)	((x) & GENMASK(4, 0))
#घोषणा EDMA_CERR_CERR(x)	((x) & GENMASK(4, 0))

#घोषणा EDMA_TCD_ATTR_DSIZE(x)		(((x) & GENMASK(2, 0)))
#घोषणा EDMA_TCD_ATTR_DMOD(x)		(((x) & GENMASK(4, 0)) << 3)
#घोषणा EDMA_TCD_ATTR_SSIZE(x)		(((x) & GENMASK(2, 0)) << 8)
#घोषणा EDMA_TCD_ATTR_SMOD(x)		(((x) & GENMASK(4, 0)) << 11)
#घोषणा EDMA_TCD_ATTR_DSIZE_8BIT	0
#घोषणा EDMA_TCD_ATTR_DSIZE_16BIT	BIT(0)
#घोषणा EDMA_TCD_ATTR_DSIZE_32BIT	BIT(1)
#घोषणा EDMA_TCD_ATTR_DSIZE_64BIT	(BIT(0) | BIT(1))
#घोषणा EDMA_TCD_ATTR_DSIZE_32BYTE	(BIT(2) | BIT(0))
#घोषणा EDMA_TCD_ATTR_SSIZE_8BIT	0
#घोषणा EDMA_TCD_ATTR_SSIZE_16BIT	(EDMA_TCD_ATTR_DSIZE_16BIT << 8)
#घोषणा EDMA_TCD_ATTR_SSIZE_32BIT	(EDMA_TCD_ATTR_DSIZE_32BIT << 8)
#घोषणा EDMA_TCD_ATTR_SSIZE_64BIT	(EDMA_TCD_ATTR_DSIZE_64BIT << 8)
#घोषणा EDMA_TCD_ATTR_SSIZE_32BYTE	(EDMA_TCD_ATTR_DSIZE_32BYTE << 8)

#घोषणा EDMA_TCD_CITER_CITER(x)		((x) & GENMASK(14, 0))
#घोषणा EDMA_TCD_BITER_BITER(x)		((x) & GENMASK(14, 0))

#घोषणा EDMA_TCD_CSR_START		BIT(0)
#घोषणा EDMA_TCD_CSR_INT_MAJOR		BIT(1)
#घोषणा EDMA_TCD_CSR_INT_HALF		BIT(2)
#घोषणा EDMA_TCD_CSR_D_REQ		BIT(3)
#घोषणा EDMA_TCD_CSR_E_SG		BIT(4)
#घोषणा EDMA_TCD_CSR_E_LINK		BIT(5)
#घोषणा EDMA_TCD_CSR_ACTIVE		BIT(6)
#घोषणा EDMA_TCD_CSR_DONE		BIT(7)

#घोषणा EDMAMUX_CHCFG_DIS		0x0
#घोषणा EDMAMUX_CHCFG_ENBL		0x80
#घोषणा EDMAMUX_CHCFG_SOURCE(n)		((n) & 0x3F)

#घोषणा DMAMUX_NR	2

#घोषणा FSL_EDMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))
क्रमागत fsl_edma_pm_state अणु
	RUNNING = 0,
	SUSPENDED,
पूर्ण;

काष्ठा fsl_edma_hw_tcd अणु
	__le32	saddr;
	__le16	soff;
	__le16	attr;
	__le32	nbytes;
	__le32	slast;
	__le32	daddr;
	__le16	करोff;
	__le16	citer;
	__le32	dlast_sga;
	__le16	csr;
	__le16	biter;
पूर्ण;

/*
 * These are iomem poपूर्णांकers, क्रम both v32 and v64.
 */
काष्ठा edma_regs अणु
	व्योम __iomem *cr;
	व्योम __iomem *es;
	व्योम __iomem *erqh;
	व्योम __iomem *erql;	/* aka erq on v32 */
	व्योम __iomem *eeih;
	व्योम __iomem *eeil;	/* aka eei on v32 */
	व्योम __iomem *seei;
	व्योम __iomem *ceei;
	व्योम __iomem *serq;
	व्योम __iomem *cerq;
	व्योम __iomem *cपूर्णांक;
	व्योम __iomem *cerr;
	व्योम __iomem *ssrt;
	व्योम __iomem *cdne;
	व्योम __iomem *पूर्णांकh;
	व्योम __iomem *पूर्णांकl;
	व्योम __iomem *errh;
	व्योम __iomem *errl;
	काष्ठा fsl_edma_hw_tcd __iomem *tcd;
पूर्ण;

काष्ठा fsl_edma_sw_tcd अणु
	dma_addr_t			ptcd;
	काष्ठा fsl_edma_hw_tcd		*vtcd;
पूर्ण;

काष्ठा fsl_edma_chan अणु
	काष्ठा virt_dma_chan		vchan;
	क्रमागत dma_status			status;
	क्रमागत fsl_edma_pm_state		pm_state;
	bool				idle;
	u32				slave_id;
	काष्ठा fsl_edma_engine		*edma;
	काष्ठा fsl_edma_desc		*edesc;
	काष्ठा dma_slave_config		cfg;
	u32				attr;
	काष्ठा dma_pool			*tcd_pool;
	dma_addr_t			dma_dev_addr;
	u32				dma_dev_size;
	क्रमागत dma_data_direction		dma_dir;
	अक्षर				chan_name[16];
पूर्ण;

काष्ठा fsl_edma_desc अणु
	काष्ठा virt_dma_desc		vdesc;
	काष्ठा fsl_edma_chan		*echan;
	bool				iscyclic;
	क्रमागत dma_transfer_direction	dirn;
	अचिन्हित पूर्णांक			n_tcds;
	काष्ठा fsl_edma_sw_tcd		tcd[];
पूर्ण;

क्रमागत edma_version अणु
	v1, /* 32ch, Vybrid, mpc57x, etc */
	v2, /* 64ch Coldfire */
	v3, /* 32ch, i.mx7ulp */
पूर्ण;

काष्ठा fsl_edma_drvdata अणु
	क्रमागत edma_version	version;
	u32			dmamuxs;
	bool			has_dmaclk;
	bool			mux_swap;
	पूर्णांक			(*setup_irq)(काष्ठा platक्रमm_device *pdev,
					     काष्ठा fsl_edma_engine *fsl_edma);
पूर्ण;

काष्ठा fsl_edma_engine अणु
	काष्ठा dma_device	dma_dev;
	व्योम __iomem		*membase;
	व्योम __iomem		*muxbase[DMAMUX_NR];
	काष्ठा clk		*muxclk[DMAMUX_NR];
	काष्ठा clk		*dmaclk;
	काष्ठा mutex		fsl_edma_mutex;
	स्थिर काष्ठा fsl_edma_drvdata *drvdata;
	u32			n_chans;
	पूर्णांक			txirq;
	पूर्णांक			errirq;
	bool			big_endian;
	काष्ठा edma_regs	regs;
	काष्ठा fsl_edma_chan	chans[];
पूर्ण;

/*
 * R/W functions क्रम big- or little-endian रेजिस्टरs:
 * The eDMA controller's endian is independent of the CPU core's endian.
 * For the big-endian IP module, the offset क्रम 8-bit or 16-bit रेजिस्टरs
 * should also be swapped opposite to that in little-endian IP.
 */
अटल अंतरभूत u32 edma_पढ़ोl(काष्ठा fsl_edma_engine *edma, व्योम __iomem *addr)
अणु
	अगर (edma->big_endian)
		वापस ioपढ़ो32be(addr);
	अन्यथा
		वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखोb(काष्ठा fsl_edma_engine *edma,
			       u8 val, व्योम __iomem *addr)
अणु
	/* swap the reg offset क्रम these in big-endian mode */
	अगर (edma->big_endian)
		ioग_लिखो8(val, (व्योम __iomem *)((अचिन्हित दीर्घ)addr ^ 0x3));
	अन्यथा
		ioग_लिखो8(val, addr);
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखोw(काष्ठा fsl_edma_engine *edma,
			       u16 val, व्योम __iomem *addr)
अणु
	/* swap the reg offset क्रम these in big-endian mode */
	अगर (edma->big_endian)
		ioग_लिखो16be(val, (व्योम __iomem *)((अचिन्हित दीर्घ)addr ^ 0x2));
	अन्यथा
		ioग_लिखो16(val, addr);
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखोl(काष्ठा fsl_edma_engine *edma,
			       u32 val, व्योम __iomem *addr)
अणु
	अगर (edma->big_endian)
		ioग_लिखो32be(val, addr);
	अन्यथा
		ioग_लिखो32(val, addr);
पूर्ण

अटल अंतरभूत काष्ठा fsl_edma_chan *to_fsl_edma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा fsl_edma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा fsl_edma_desc *to_fsl_edma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा fsl_edma_desc, vdesc);
पूर्ण

व्योम fsl_edma_disable_request(काष्ठा fsl_edma_chan *fsl_chan);
व्योम fsl_edma_chan_mux(काष्ठा fsl_edma_chan *fsl_chan,
			अचिन्हित पूर्णांक slot, bool enable);
व्योम fsl_edma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc);
पूर्णांक fsl_edma_terminate_all(काष्ठा dma_chan *chan);
पूर्णांक fsl_edma_छोड़ो(काष्ठा dma_chan *chan);
पूर्णांक fsl_edma_resume(काष्ठा dma_chan *chan);
पूर्णांक fsl_edma_slave_config(काष्ठा dma_chan *chan,
				 काष्ठा dma_slave_config *cfg);
क्रमागत dma_status fsl_edma_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *txstate);
काष्ठा dma_async_tx_descriptor *fsl_edma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags);
काष्ठा dma_async_tx_descriptor *fsl_edma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context);
व्योम fsl_edma_xfer_desc(काष्ठा fsl_edma_chan *fsl_chan);
व्योम fsl_edma_issue_pending(काष्ठा dma_chan *chan);
पूर्णांक fsl_edma_alloc_chan_resources(काष्ठा dma_chan *chan);
व्योम fsl_edma_मुक्त_chan_resources(काष्ठा dma_chan *chan);
व्योम fsl_edma_cleanup_vchan(काष्ठा dma_device *dmadev);
व्योम fsl_edma_setup_regs(काष्ठा fsl_edma_engine *edma);

#पूर्ण_अगर /* _FSL_EDMA_COMMON_H_ */
