<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#अगर_अघोषित _CORESIGHT_TMC_H
#घोषणा _CORESIGHT_TMC_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>

#घोषणा TMC_RSZ			0x004
#घोषणा TMC_STS			0x00c
#घोषणा TMC_RRD			0x010
#घोषणा TMC_RRP			0x014
#घोषणा TMC_RWP			0x018
#घोषणा TMC_TRG			0x01c
#घोषणा TMC_CTL			0x020
#घोषणा TMC_RWD			0x024
#घोषणा TMC_MODE		0x028
#घोषणा TMC_LBUFLEVEL		0x02c
#घोषणा TMC_CBUFLEVEL		0x030
#घोषणा TMC_BUFWM		0x034
#घोषणा TMC_RRPHI		0x038
#घोषणा TMC_RWPHI		0x03c
#घोषणा TMC_AXICTL		0x110
#घोषणा TMC_DBALO		0x118
#घोषणा TMC_DBAHI		0x11c
#घोषणा TMC_FFSR		0x300
#घोषणा TMC_FFCR		0x304
#घोषणा TMC_PSCR		0x308
#घोषणा TMC_ITMISCOP0		0xee0
#घोषणा TMC_ITTRFLIN		0xee8
#घोषणा TMC_ITATBDATA0		0xeec
#घोषणा TMC_ITATBCTR2		0xef0
#घोषणा TMC_ITATBCTR1		0xef4
#घोषणा TMC_ITATBCTR0		0xef8
#घोषणा TMC_AUTHSTATUS		0xfb8

/* रेजिस्टर description */
/* TMC_CTL - 0x020 */
#घोषणा TMC_CTL_CAPT_EN		BIT(0)
/* TMC_STS - 0x00C */
#घोषणा TMC_STS_TMCREADY_BIT	2
#घोषणा TMC_STS_FULL		BIT(0)
#घोषणा TMC_STS_TRIGGERED	BIT(1)
#घोषणा TMC_STS_MEMERR		BIT(5)
/*
 * TMC_AXICTL - 0x110
 *
 * TMC AXICTL क्रमmat क्रम SoC-400
 *	Bits [0-1]	: ProtCtrlBit0-1
 *	Bits [2-5]	: CacheCtrlBits 0-3 (AXCACHE)
 *	Bit  6		: Reserved
 *	Bit  7		: ScatterGatherMode
 *	Bits [8-11]	: WrBurstLen
 *	Bits [12-31]	: Reserved.
 * TMC AXICTL क्रमmat क्रम SoC-600, as above except:
 *	Bits [2-5]	: AXI WCACHE
 *	Bits [16-19]	: AXI RCACHE
 *	Bits [20-31]	: Reserved
 */
#घोषणा TMC_AXICTL_CLEAR_MASK 0xfbf
#घोषणा TMC_AXICTL_ARCACHE_MASK (0xf << 16)

#घोषणा TMC_AXICTL_PROT_CTL_B0	BIT(0)
#घोषणा TMC_AXICTL_PROT_CTL_B1	BIT(1)
#घोषणा TMC_AXICTL_SCT_GAT_MODE	BIT(7)
#घोषणा TMC_AXICTL_WR_BURST_16	0xF00
/* Write-back Read and Write-allocate */
#घोषणा TMC_AXICTL_AXCACHE_OS	(0xf << 2)
#घोषणा TMC_AXICTL_ARCACHE_OS	(0xf << 16)

/* TMC_FFCR - 0x304 */
#घोषणा TMC_FFCR_FLUSHMAN_BIT	6
#घोषणा TMC_FFCR_EN_FMT		BIT(0)
#घोषणा TMC_FFCR_EN_TI		BIT(1)
#घोषणा TMC_FFCR_FON_FLIN	BIT(4)
#घोषणा TMC_FFCR_FON_TRIG_EVT	BIT(5)
#घोषणा TMC_FFCR_TRIGON_TRIGIN	BIT(8)
#घोषणा TMC_FFCR_STOP_ON_FLUSH	BIT(12)


#घोषणा TMC_DEVID_NOSCAT	BIT(24)

#घोषणा TMC_DEVID_AXIAW_VALID	BIT(16)
#घोषणा TMC_DEVID_AXIAW_SHIFT	17
#घोषणा TMC_DEVID_AXIAW_MASK	0x7f

#घोषणा TMC_AUTH_NSID_MASK	GENMASK(1, 0)

क्रमागत पंचांगc_config_type अणु
	TMC_CONFIG_TYPE_ETB,
	TMC_CONFIG_TYPE_ETR,
	TMC_CONFIG_TYPE_ETF,
पूर्ण;

क्रमागत पंचांगc_mode अणु
	TMC_MODE_CIRCULAR_BUFFER,
	TMC_MODE_SOFTWARE_FIFO,
	TMC_MODE_HARDWARE_FIFO,
पूर्ण;

क्रमागत पंचांगc_mem_पूर्णांकf_width अणु
	TMC_MEM_INTF_WIDTH_32BITS	= 1,
	TMC_MEM_INTF_WIDTH_64BITS	= 2,
	TMC_MEM_INTF_WIDTH_128BITS	= 4,
	TMC_MEM_INTF_WIDTH_256BITS	= 8,
पूर्ण;

/* TMC ETR Capability bit definitions */
#घोषणा TMC_ETR_SG			(0x1U << 0)
/* ETR has separate पढ़ो/ग_लिखो cache encodings */
#घोषणा TMC_ETR_AXI_ARCACHE		(0x1U << 1)
/*
 * TMC_ETR_SAVE_RESTORE - Values of RRP/RWP/STS.Full are
 * retained when TMC leaves Disabled state, allowing us to जारी
 * the tracing from a poपूर्णांक where we stopped. This also implies that
 * the RRP/RWP/STS.Full should always be programmed to the correct
 * value. Unक्रमtunately this is not advertised by the hardware,
 * so we have to rely on PID of the IP to detect the functionality.
 */
#घोषणा TMC_ETR_SAVE_RESTORE		(0x1U << 2)

/* Coresight SoC-600 TMC-ETR unadvertised capabilities */
#घोषणा CORESIGHT_SOC_600_ETR_CAPS	\
	(TMC_ETR_SAVE_RESTORE | TMC_ETR_AXI_ARCACHE)

क्रमागत etr_mode अणु
	ETR_MODE_FLAT,		/* Uses contiguous flat buffer */
	ETR_MODE_ETR_SG,	/* Uses in-built TMC ETR SG mechanism */
	ETR_MODE_CATU,		/* Use SG mechanism in CATU */
पूर्ण;

काष्ठा etr_buf_operations;

/**
 * काष्ठा etr_buf - Details of the buffer used by ETR
 * refcount	; Number of sources currently using this etr_buf.
 * @mode	: Mode of the ETR buffer, contiguous, Scatter Gather etc.
 * @full	: Trace data overflow
 * @size	: Size of the buffer.
 * @hwaddr	: Address to be programmed in the TMC:DBAअणुLO,HIपूर्ण
 * @offset	: Offset of the trace data in the buffer क्रम consumption.
 * @len		: Available trace data @buf (may round up to the beginning).
 * @ops		: ETR buffer operations क्रम the mode.
 * @निजी	: Backend specअगरic inक्रमmation क्रम the buf
 */
काष्ठा etr_buf अणु
	refcount_t			refcount;
	क्रमागत etr_mode			mode;
	bool				full;
	sमाप_प्रकार				size;
	dma_addr_t			hwaddr;
	अचिन्हित दीर्घ			offset;
	s64				len;
	स्थिर काष्ठा etr_buf_operations	*ops;
	व्योम				*निजी;
पूर्ण;

/**
 * काष्ठा पंचांगc_drvdata - specअगरics associated to an TMC component
 * @base:	memory mapped base address क्रम this component.
 * @csdev:	component vitals needed by the framework.
 * @miscdev:	specअगरics to handle "/dev/xyz.tmc" entry.
 * @spinlock:	only one at a समय pls.
 * @pid:	Process ID of the process being monitored by the session
 *		that is using this component.
 * @buf:	Snapshot of the trace data क्रम ETF/ETB.
 * @etr_buf:	details of buffer used in TMC-ETR
 * @len:	size of the available trace क्रम ETF/ETB.
 * @size:	trace buffer size क्रम this TMC (common क्रम all modes).
 * @mode:	how this TMC is being used.
 * @config_type: TMC variant, must be of type @पंचांगc_config_type.
 * @memwidth:	width of the memory पूर्णांकerface databus, in bytes.
 * @trigger_cntr: amount of words to store after a trigger.
 * @etr_caps:	Biपंचांगask of capabilities of the TMC ETR, inferred from the
 *		device configuration रेजिस्टर (DEVID)
 * @idr:	Holds etr_bufs allocated क्रम this ETR.
 * @idr_mutex:	Access serialisation क्रम idr.
 * @sysfs_buf:	SYSFS buffer क्रम ETR.
 * @perf_buf:	PERF buffer क्रम ETR.
 */
काष्ठा पंचांगc_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा coresight_device	*csdev;
	काष्ठा miscdevice	miscdev;
	spinlock_t		spinlock;
	pid_t			pid;
	bool			पढ़ोing;
	जोड़ अणु
		अक्षर		*buf;		/* TMC ETB */
		काष्ठा etr_buf	*etr_buf;	/* TMC ETR */
	पूर्ण;
	u32			len;
	u32			size;
	u32			mode;
	क्रमागत पंचांगc_config_type	config_type;
	क्रमागत पंचांगc_mem_पूर्णांकf_width	memwidth;
	u32			trigger_cntr;
	u32			etr_caps;
	काष्ठा idr		idr;
	काष्ठा mutex		idr_mutex;
	काष्ठा etr_buf		*sysfs_buf;
	काष्ठा etr_buf		*perf_buf;
पूर्ण;

काष्ठा etr_buf_operations अणु
	पूर्णांक (*alloc)(काष्ठा पंचांगc_drvdata *drvdata, काष्ठा etr_buf *etr_buf,
		     पूर्णांक node, व्योम **pages);
	व्योम (*sync)(काष्ठा etr_buf *etr_buf, u64 rrp, u64 rwp);
	sमाप_प्रकार (*get_data)(काष्ठा etr_buf *etr_buf, u64 offset, माप_प्रकार len,
			    अक्षर **bufpp);
	व्योम (*मुक्त)(काष्ठा etr_buf *etr_buf);
पूर्ण;

/**
 * काष्ठा पंचांगc_pages - Collection of pages used क्रम SG.
 * @nr_pages:		Number of pages in the list.
 * @daddrs:		Array of DMA'able page address.
 * @pages:		Array pages क्रम the buffer.
 */
काष्ठा पंचांगc_pages अणु
	पूर्णांक nr_pages;
	dma_addr_t	*daddrs;
	काष्ठा page	**pages;
पूर्ण;

/*
 * काष्ठा पंचांगc_sg_table - Generic SG table क्रम TMC
 * @dev:		Device क्रम DMA allocations
 * @table_vaddr:	Contiguous Virtual address क्रम PageTable
 * @data_vaddr:		Contiguous Virtual address क्रम Data Buffer
 * @table_daddr:	DMA address of the PageTable base
 * @node:		Node क्रम Page allocations
 * @table_pages:	List of pages & dma address क्रम Table
 * @data_pages:		List of pages & dma address क्रम Data
 */
काष्ठा पंचांगc_sg_table अणु
	काष्ठा device *dev;
	व्योम *table_vaddr;
	व्योम *data_vaddr;
	dma_addr_t table_daddr;
	पूर्णांक node;
	काष्ठा पंचांगc_pages table_pages;
	काष्ठा पंचांगc_pages data_pages;
पूर्ण;

/* Generic functions */
व्योम पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(काष्ठा पंचांगc_drvdata *drvdata);
व्योम पंचांगc_flush_and_stop(काष्ठा पंचांगc_drvdata *drvdata);
व्योम पंचांगc_enable_hw(काष्ठा पंचांगc_drvdata *drvdata);
व्योम पंचांगc_disable_hw(काष्ठा पंचांगc_drvdata *drvdata);
u32 पंचांगc_get_memwidth_mask(काष्ठा पंचांगc_drvdata *drvdata);

/* ETB/ETF functions */
पूर्णांक पंचांगc_पढ़ो_prepare_etb(काष्ठा पंचांगc_drvdata *drvdata);
पूर्णांक पंचांगc_पढ़ो_unprepare_etb(काष्ठा पंचांगc_drvdata *drvdata);
बाह्य स्थिर काष्ठा coresight_ops पंचांगc_etb_cs_ops;
बाह्य स्थिर काष्ठा coresight_ops पंचांगc_etf_cs_ops;

sमाप_प्रकार पंचांगc_etb_get_sysfs_trace(काष्ठा पंचांगc_drvdata *drvdata,
				loff_t pos, माप_प्रकार len, अक्षर **bufpp);
/* ETR functions */
पूर्णांक पंचांगc_पढ़ो_prepare_etr(काष्ठा पंचांगc_drvdata *drvdata);
पूर्णांक पंचांगc_पढ़ो_unprepare_etr(काष्ठा पंचांगc_drvdata *drvdata);
व्योम पंचांगc_etr_disable_hw(काष्ठा पंचांगc_drvdata *drvdata);
बाह्य स्थिर काष्ठा coresight_ops पंचांगc_etr_cs_ops;
sमाप_प्रकार पंचांगc_etr_get_sysfs_trace(काष्ठा पंचांगc_drvdata *drvdata,
				loff_t pos, माप_प्रकार len, अक्षर **bufpp);


#घोषणा TMC_REG_PAIR(name, lo_off, hi_off)				\
अटल अंतरभूत u64							\
पंचांगc_पढ़ो_##name(काष्ठा पंचांगc_drvdata *drvdata)				\
अणु									\
	वापस coresight_पढ़ो_reg_pair(drvdata->base, lo_off, hi_off);	\
पूर्ण									\
अटल अंतरभूत व्योम							\
पंचांगc_ग_लिखो_##name(काष्ठा पंचांगc_drvdata *drvdata, u64 val)			\
अणु									\
	coresight_ग_लिखो_reg_pair(drvdata->base, val, lo_off, hi_off);	\
पूर्ण

TMC_REG_PAIR(rrp, TMC_RRP, TMC_RRPHI)
TMC_REG_PAIR(rwp, TMC_RWP, TMC_RWPHI)
TMC_REG_PAIR(dba, TMC_DBALO, TMC_DBAHI)

/* Initialise the caps from unadvertised अटल capabilities of the device */
अटल अंतरभूत व्योम पंचांगc_etr_init_caps(काष्ठा पंचांगc_drvdata *drvdata, u32 dev_caps)
अणु
	WARN_ON(drvdata->etr_caps);
	drvdata->etr_caps = dev_caps;
पूर्ण

अटल अंतरभूत व्योम पंचांगc_etr_set_cap(काष्ठा पंचांगc_drvdata *drvdata, u32 cap)
अणु
	drvdata->etr_caps |= cap;
पूर्ण

अटल अंतरभूत bool पंचांगc_etr_has_cap(काष्ठा पंचांगc_drvdata *drvdata, u32 cap)
अणु
	वापस !!(drvdata->etr_caps & cap);
पूर्ण

काष्ठा पंचांगc_sg_table *पंचांगc_alloc_sg_table(काष्ठा device *dev,
					पूर्णांक node,
					पूर्णांक nr_tpages,
					पूर्णांक nr_dpages,
					व्योम **pages);
व्योम पंचांगc_मुक्त_sg_table(काष्ठा पंचांगc_sg_table *sg_table);
व्योम पंचांगc_sg_table_sync_table(काष्ठा पंचांगc_sg_table *sg_table);
व्योम पंचांगc_sg_table_sync_data_range(काष्ठा पंचांगc_sg_table *table,
				  u64 offset, u64 size);
sमाप_प्रकार पंचांगc_sg_table_get_data(काष्ठा पंचांगc_sg_table *sg_table,
			      u64 offset, माप_प्रकार len, अक्षर **bufpp);
अटल अंतरभूत अचिन्हित दीर्घ
पंचांगc_sg_table_buf_size(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	वापस sg_table->data_pages.nr_pages << PAGE_SHIFT;
पूर्ण

काष्ठा coresight_device *पंचांगc_etr_get_catu_device(काष्ठा पंचांगc_drvdata *drvdata);

व्योम पंचांगc_etr_set_catu_ops(स्थिर काष्ठा etr_buf_operations *catu);
व्योम पंचांगc_etr_हटाओ_catu_ops(व्योम);

#पूर्ण_अगर
