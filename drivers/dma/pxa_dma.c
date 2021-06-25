<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dma/pxa-dma.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा DCSR(n)		(0x0000 + ((n) << 2))
#घोषणा DALGN(n)	0x00a0
#घोषणा DINT		0x00f0
#घोषणा DDADR(n)	(0x0200 + ((n) << 4))
#घोषणा DSADR(n)	(0x0204 + ((n) << 4))
#घोषणा DTADR(n)	(0x0208 + ((n) << 4))
#घोषणा DCMD(n)		(0x020c + ((n) << 4))

#घोषणा PXA_DCSR_RUN		BIT(31)	/* Run Bit (पढ़ो / ग_लिखो) */
#घोषणा PXA_DCSR_NODESC		BIT(30)	/* No-Descriptor Fetch (पढ़ो / ग_लिखो) */
#घोषणा PXA_DCSR_STOPIRQEN	BIT(29)	/* Stop Interrupt Enable (R/W) */
#घोषणा PXA_DCSR_REQPEND	BIT(8)	/* Request Pending (पढ़ो-only) */
#घोषणा PXA_DCSR_STOPSTATE	BIT(3)	/* Stop State (पढ़ो-only) */
#घोषणा PXA_DCSR_ENDINTR	BIT(2)	/* End Interrupt (पढ़ो / ग_लिखो) */
#घोषणा PXA_DCSR_STARTINTR	BIT(1)	/* Start Interrupt (पढ़ो / ग_लिखो) */
#घोषणा PXA_DCSR_BUSERR		BIT(0)	/* Bus Error Interrupt (पढ़ो / ग_लिखो) */

#घोषणा PXA_DCSR_EORIRQEN	BIT(28)	/* End of Receive IRQ Enable (R/W) */
#घोषणा PXA_DCSR_EORJMPEN	BIT(27)	/* Jump to next descriptor on EOR */
#घोषणा PXA_DCSR_EORSTOPEN	BIT(26)	/* STOP on an EOR */
#घोषणा PXA_DCSR_SETCMPST	BIT(25)	/* Set Descriptor Compare Status */
#घोषणा PXA_DCSR_CLRCMPST	BIT(24)	/* Clear Descriptor Compare Status */
#घोषणा PXA_DCSR_CMPST		BIT(10)	/* The Descriptor Compare Status */
#घोषणा PXA_DCSR_EORINTR	BIT(9)	/* The end of Receive */

#घोषणा DRCMR_MAPVLD	BIT(7)	/* Map Valid (पढ़ो / ग_लिखो) */
#घोषणा DRCMR_CHLNUM	0x1f	/* mask क्रम Channel Number (पढ़ो / ग_लिखो) */

#घोषणा DDADR_DESCADDR	0xfffffff0	/* Address of next descriptor (mask) */
#घोषणा DDADR_STOP	BIT(0)	/* Stop (पढ़ो / ग_लिखो) */

#घोषणा PXA_DCMD_INCSRCADDR	BIT(31)	/* Source Address Increment Setting. */
#घोषणा PXA_DCMD_INCTRGADDR	BIT(30)	/* Target Address Increment Setting. */
#घोषणा PXA_DCMD_FLOWSRC	BIT(29)	/* Flow Control by the source. */
#घोषणा PXA_DCMD_FLOWTRG	BIT(28)	/* Flow Control by the target. */
#घोषणा PXA_DCMD_STARTIRQEN	BIT(22)	/* Start Interrupt Enable */
#घोषणा PXA_DCMD_ENसूचीQEN	BIT(21)	/* End Interrupt Enable */
#घोषणा PXA_DCMD_ENDIAN		BIT(18)	/* Device Endian-ness. */
#घोषणा PXA_DCMD_BURST8		(1 << 16)	/* 8 byte burst */
#घोषणा PXA_DCMD_BURST16	(2 << 16)	/* 16 byte burst */
#घोषणा PXA_DCMD_BURST32	(3 << 16)	/* 32 byte burst */
#घोषणा PXA_DCMD_WIDTH1		(1 << 14)	/* 1 byte width */
#घोषणा PXA_DCMD_WIDTH2		(2 << 14)	/* 2 byte width (HalfWord) */
#घोषणा PXA_DCMD_WIDTH4		(3 << 14)	/* 4 byte width (Word) */
#घोषणा PXA_DCMD_LENGTH		0x01fff		/* length mask (max = 8K - 1) */

#घोषणा PDMA_ALIGNMENT		3
#घोषणा PDMA_MAX_DESC_BYTES	(PXA_DCMD_LENGTH & ~((1 << PDMA_ALIGNMENT) - 1))

काष्ठा pxad_desc_hw अणु
	u32 ddadr;	/* Poपूर्णांकs to the next descriptor + flags */
	u32 dsadr;	/* DSADR value क्रम the current transfer */
	u32 dtadr;	/* DTADR value क्रम the current transfer */
	u32 dcmd;	/* DCMD value क्रम the current transfer */
पूर्ण __aligned(16);

काष्ठा pxad_desc_sw अणु
	काष्ठा virt_dma_desc	vd;		/* Virtual descriptor */
	पूर्णांक			nb_desc;	/* Number of hw. descriptors */
	माप_प्रकार			len;		/* Number of bytes xfered */
	dma_addr_t		first;		/* First descriptor's addr */

	/* At least one descriptor has an src/dst address not multiple of 8 */
	bool			misaligned;
	bool			cyclic;
	काष्ठा dma_pool		*desc_pool;	/* Channel's used allocator */

	काष्ठा pxad_desc_hw	*hw_desc[];	/* DMA coherent descriptors */
पूर्ण;

काष्ठा pxad_phy अणु
	पूर्णांक			idx;
	व्योम __iomem		*base;
	काष्ठा pxad_chan	*vchan;
पूर्ण;

काष्ठा pxad_chan अणु
	काष्ठा virt_dma_chan	vc;		/* Virtual channel */
	u32			drcmr;		/* Requestor of the channel */
	क्रमागत pxad_chan_prio	prio;		/* Required priority of phy */
	/*
	 * At least one desc_sw in submitted or issued transfers on this channel
	 * has one address such as: addr % 8 != 0. This implies the DALGN
	 * setting on the phy.
	 */
	bool			misaligned;
	काष्ठा dma_slave_config	cfg;		/* Runसमय config */

	/* रक्षित by vc->lock */
	काष्ठा pxad_phy		*phy;
	काष्ठा dma_pool		*desc_pool;	/* Descriptors pool */
	dma_cookie_t		bus_error;

	रुको_queue_head_t	wq_state;
पूर्ण;

काष्ठा pxad_device अणु
	काष्ठा dma_device		slave;
	पूर्णांक				nr_chans;
	पूर्णांक				nr_requestors;
	व्योम __iomem			*base;
	काष्ठा pxad_phy			*phys;
	spinlock_t			phy_lock;	/* Phy association */
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry			*dbgfs_root;
	काष्ठा dentry			**dbgfs_chan;
#पूर्ण_अगर
पूर्ण;

#घोषणा tx_to_pxad_desc(tx)					\
	container_of(tx, काष्ठा pxad_desc_sw, async_tx)
#घोषणा to_pxad_chan(dchan)					\
	container_of(dchan, काष्ठा pxad_chan, vc.chan)
#घोषणा to_pxad_dev(dmadev)					\
	container_of(dmadev, काष्ठा pxad_device, slave)
#घोषणा to_pxad_sw_desc(_vd)				\
	container_of((_vd), काष्ठा pxad_desc_sw, vd)

#घोषणा _phy_पढ़ोl_relaxed(phy, _reg)					\
	पढ़ोl_relaxed((phy)->base + _reg((phy)->idx))
#घोषणा phy_पढ़ोl_relaxed(phy, _reg)					\
	(अणु								\
		u32 _v;							\
		_v = पढ़ोl_relaxed((phy)->base + _reg((phy)->idx));	\
		dev_vdbg(&phy->vchan->vc.chan.dev->device,		\
			 "%s(): readl(%s): 0x%08x\n", __func__, #_reg,	\
			  _v);						\
		_v;							\
	पूर्ण)
#घोषणा phy_ग_लिखोl(phy, val, _reg)					\
	करो अणु								\
		ग_लिखोl((val), (phy)->base + _reg((phy)->idx));		\
		dev_vdbg(&phy->vchan->vc.chan.dev->device,		\
			 "%s(): writel(0x%08x, %s)\n",			\
			 __func__, (u32)(val), #_reg);			\
	पूर्ण जबतक (0)
#घोषणा phy_ग_लिखोl_relaxed(phy, val, _reg)				\
	करो अणु								\
		ग_लिखोl_relaxed((val), (phy)->base + _reg((phy)->idx));	\
		dev_vdbg(&phy->vchan->vc.chan.dev->device,		\
			 "%s(): writel_relaxed(0x%08x, %s)\n",		\
			 __func__, (u32)(val), #_reg);			\
	पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक pxad_drcmr(अचिन्हित पूर्णांक line)
अणु
	अगर (line < 64)
		वापस 0x100 + line * 4;
	वापस 0x1000 + line * 4;
पूर्ण

अटल bool pxad_filter_fn(काष्ठा dma_chan *chan, व्योम *param);

/*
 * Debug fs
 */
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक requester_chan_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxad_phy *phy = s->निजी;
	पूर्णांक i;
	u32 drcmr;

	seq_म_लिखो(s, "DMA channel %d requester :\n", phy->idx);
	क्रम (i = 0; i < 70; i++) अणु
		drcmr = पढ़ोl_relaxed(phy->base + pxad_drcmr(i));
		अगर ((drcmr & DRCMR_CHLNUM) == phy->idx)
			seq_म_लिखो(s, "\tRequester %d (MAPVLD=%d)\n", i,
				   !!(drcmr & DRCMR_MAPVLD));
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dbg_burst_from_dcmd(u32 dcmd)
अणु
	पूर्णांक burst = (dcmd >> 16) & 0x3;

	वापस burst ? 4 << burst : 0;
पूर्ण

अटल पूर्णांक is_phys_valid(अचिन्हित दीर्घ addr)
अणु
	वापस pfn_valid(__phys_to_pfn(addr));
पूर्ण

#घोषणा PXA_DCSR_STR(flag) (dcsr & PXA_DCSR_##flag ? #flag" " : "")
#घोषणा PXA_DCMD_STR(flag) (dcmd & PXA_DCMD_##flag ? #flag" " : "")

अटल पूर्णांक descriptors_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxad_phy *phy = s->निजी;
	पूर्णांक i, max_show = 20, burst, width;
	u32 dcmd;
	अचिन्हित दीर्घ phys_desc, ddadr;
	काष्ठा pxad_desc_hw *desc;

	phys_desc = ddadr = _phy_पढ़ोl_relaxed(phy, DDADR);

	seq_म_लिखो(s, "DMA channel %d descriptors :\n", phy->idx);
	seq_म_लिखो(s, "[%03d] First descriptor unknown\n", 0);
	क्रम (i = 1; i < max_show && is_phys_valid(phys_desc); i++) अणु
		desc = phys_to_virt(phys_desc);
		dcmd = desc->dcmd;
		burst = dbg_burst_from_dcmd(dcmd);
		width = (1 << ((dcmd >> 14) & 0x3)) >> 1;

		seq_म_लिखो(s, "[%03d] Desc at %08lx(virt %p)\n",
			   i, phys_desc, desc);
		seq_म_लिखो(s, "\tDDADR = %08x\n", desc->ddadr);
		seq_म_लिखो(s, "\tDSADR = %08x\n", desc->dsadr);
		seq_म_लिखो(s, "\tDTADR = %08x\n", desc->dtadr);
		seq_म_लिखो(s, "\tDCMD  = %08x (%s%s%s%s%s%s%sburst=%d width=%d len=%d)\n",
			   dcmd,
			   PXA_DCMD_STR(INCSRCADDR), PXA_DCMD_STR(INCTRGADDR),
			   PXA_DCMD_STR(FLOWSRC), PXA_DCMD_STR(FLOWTRG),
			   PXA_DCMD_STR(STARTIRQEN), PXA_DCMD_STR(ENसूचीQEN),
			   PXA_DCMD_STR(ENDIAN), burst, width,
			   dcmd & PXA_DCMD_LENGTH);
		phys_desc = desc->ddadr;
	पूर्ण
	अगर (i == max_show)
		seq_म_लिखो(s, "[%03d] Desc at %08lx ... max display reached\n",
			   i, phys_desc);
	अन्यथा
		seq_म_लिखो(s, "[%03d] Desc at %08lx is %s\n",
			   i, phys_desc, phys_desc == DDADR_STOP ?
			   "DDADR_STOP" : "invalid");

	वापस 0;
पूर्ण

अटल पूर्णांक chan_state_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxad_phy *phy = s->निजी;
	u32 dcsr, dcmd;
	पूर्णांक burst, width;
	अटल स्थिर अक्षर * स्थिर str_prio[] = अणु
		"high", "normal", "low", "invalid"
	पूर्ण;

	dcsr = _phy_पढ़ोl_relaxed(phy, DCSR);
	dcmd = _phy_पढ़ोl_relaxed(phy, DCMD);
	burst = dbg_burst_from_dcmd(dcmd);
	width = (1 << ((dcmd >> 14) & 0x3)) >> 1;

	seq_म_लिखो(s, "DMA channel %d\n", phy->idx);
	seq_म_लिखो(s, "\tPriority : %s\n",
			  str_prio[(phy->idx & 0xf) / 4]);
	seq_म_लिखो(s, "\tUnaligned transfer bit: %s\n",
			  _phy_पढ़ोl_relaxed(phy, DALGN) & BIT(phy->idx) ?
			  "yes" : "no");
	seq_म_लिखो(s, "\tDCSR  = %08x (%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s)\n",
		   dcsr, PXA_DCSR_STR(RUN), PXA_DCSR_STR(NODESC),
		   PXA_DCSR_STR(STOPIRQEN), PXA_DCSR_STR(EORIRQEN),
		   PXA_DCSR_STR(EORJMPEN), PXA_DCSR_STR(EORSTOPEN),
		   PXA_DCSR_STR(SETCMPST), PXA_DCSR_STR(CLRCMPST),
		   PXA_DCSR_STR(CMPST), PXA_DCSR_STR(EORINTR),
		   PXA_DCSR_STR(REQPEND), PXA_DCSR_STR(STOPSTATE),
		   PXA_DCSR_STR(ENDINTR), PXA_DCSR_STR(STARTINTR),
		   PXA_DCSR_STR(BUSERR));

	seq_म_लिखो(s, "\tDCMD  = %08x (%s%s%s%s%s%s%sburst=%d width=%d len=%d)\n",
		   dcmd,
		   PXA_DCMD_STR(INCSRCADDR), PXA_DCMD_STR(INCTRGADDR),
		   PXA_DCMD_STR(FLOWSRC), PXA_DCMD_STR(FLOWTRG),
		   PXA_DCMD_STR(STARTIRQEN), PXA_DCMD_STR(ENसूचीQEN),
		   PXA_DCMD_STR(ENDIAN), burst, width, dcmd & PXA_DCMD_LENGTH);
	seq_म_लिखो(s, "\tDSADR = %08x\n", _phy_पढ़ोl_relaxed(phy, DSADR));
	seq_म_लिखो(s, "\tDTADR = %08x\n", _phy_पढ़ोl_relaxed(phy, DTADR));
	seq_म_लिखो(s, "\tDDADR = %08x\n", _phy_पढ़ोl_relaxed(phy, DDADR));

	वापस 0;
पूर्ण

अटल पूर्णांक state_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxad_device *pdev = s->निजी;

	/* basic device status */
	seq_माला_दो(s, "DMA engine status\n");
	seq_म_लिखो(s, "\tChannel number: %d\n", pdev->nr_chans);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(state);
DEFINE_SHOW_ATTRIBUTE(chan_state);
DEFINE_SHOW_ATTRIBUTE(descriptors);
DEFINE_SHOW_ATTRIBUTE(requester_chan);

अटल काष्ठा dentry *pxad_dbg_alloc_chan(काष्ठा pxad_device *pdev,
					     पूर्णांक ch, काष्ठा dentry *chandir)
अणु
	अक्षर chan_name[11];
	काष्ठा dentry *chan;
	व्योम *dt;

	scnम_लिखो(chan_name, माप(chan_name), "%d", ch);
	chan = debugfs_create_dir(chan_name, chandir);
	dt = (व्योम *)&pdev->phys[ch];

	debugfs_create_file("state", 0400, chan, dt, &chan_state_fops);
	debugfs_create_file("descriptors", 0400, chan, dt, &descriptors_fops);
	debugfs_create_file("requesters", 0400, chan, dt, &requester_chan_fops);

	वापस chan;
पूर्ण

अटल व्योम pxad_init_debugfs(काष्ठा pxad_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा dentry *chandir;

	pdev->dbgfs_chan =
		kदो_स्मृति_array(pdev->nr_chans, माप(काष्ठा dentry *),
			      GFP_KERNEL);
	अगर (!pdev->dbgfs_chan)
		वापस;

	pdev->dbgfs_root = debugfs_create_dir(dev_name(pdev->slave.dev), शून्य);

	debugfs_create_file("state", 0400, pdev->dbgfs_root, pdev, &state_fops);

	chandir = debugfs_create_dir("channels", pdev->dbgfs_root);

	क्रम (i = 0; i < pdev->nr_chans; i++)
		pdev->dbgfs_chan[i] = pxad_dbg_alloc_chan(pdev, i, chandir);
पूर्ण

अटल व्योम pxad_cleanup_debugfs(काष्ठा pxad_device *pdev)
अणु
	debugfs_हटाओ_recursive(pdev->dbgfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxad_init_debugfs(काष्ठा pxad_device *pdev) अणुपूर्ण
अटल अंतरभूत व्योम pxad_cleanup_debugfs(काष्ठा pxad_device *pdev) अणुपूर्ण
#पूर्ण_अगर

अटल काष्ठा pxad_phy *lookup_phy(काष्ठा pxad_chan *pchan)
अणु
	पूर्णांक prio, i;
	काष्ठा pxad_device *pdev = to_pxad_dev(pchan->vc.chan.device);
	काष्ठा pxad_phy *phy, *found = शून्य;
	अचिन्हित दीर्घ flags;

	/*
	 * dma channel priorities
	 * ch 0 - 3,  16 - 19  <--> (0)
	 * ch 4 - 7,  20 - 23  <--> (1)
	 * ch 8 - 11, 24 - 27  <--> (2)
	 * ch 12 - 15, 28 - 31  <--> (3)
	 */

	spin_lock_irqsave(&pdev->phy_lock, flags);
	क्रम (prio = pchan->prio; prio >= PXAD_PRIO_HIGHEST; prio--) अणु
		क्रम (i = 0; i < pdev->nr_chans; i++) अणु
			अगर (prio != (i & 0xf) >> 2)
				जारी;
			phy = &pdev->phys[i];
			अगर (!phy->vchan) अणु
				phy->vchan = pchan;
				found = phy;
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
	dev_dbg(&pchan->vc.chan.dev->device,
		"%s(): phy=%p(%d)\n", __func__, found,
		found ? found->idx : -1);

	वापस found;
पूर्ण

अटल व्योम pxad_मुक्त_phy(काष्ठा pxad_chan *chan)
अणु
	काष्ठा pxad_device *pdev = to_pxad_dev(chan->vc.chan.device);
	अचिन्हित दीर्घ flags;
	u32 reg;

	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): freeing\n", __func__);
	अगर (!chan->phy)
		वापस;

	/* clear the channel mapping in DRCMR */
	अगर (chan->drcmr <= pdev->nr_requestors) अणु
		reg = pxad_drcmr(chan->drcmr);
		ग_लिखोl_relaxed(0, chan->phy->base + reg);
	पूर्ण

	spin_lock_irqsave(&pdev->phy_lock, flags);
	chan->phy->vchan = शून्य;
	chan->phy = शून्य;
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
पूर्ण

अटल bool is_chan_running(काष्ठा pxad_chan *chan)
अणु
	u32 dcsr;
	काष्ठा pxad_phy *phy = chan->phy;

	अगर (!phy)
		वापस false;
	dcsr = phy_पढ़ोl_relaxed(phy, DCSR);
	वापस dcsr & PXA_DCSR_RUN;
पूर्ण

अटल bool is_running_chan_misaligned(काष्ठा pxad_chan *chan)
अणु
	u32 dalgn;

	BUG_ON(!chan->phy);
	dalgn = phy_पढ़ोl_relaxed(chan->phy, DALGN);
	वापस dalgn & (BIT(chan->phy->idx));
पूर्ण

अटल व्योम phy_enable(काष्ठा pxad_phy *phy, bool misaligned)
अणु
	काष्ठा pxad_device *pdev;
	u32 reg, dalgn;

	अगर (!phy->vchan)
		वापस;

	dev_dbg(&phy->vchan->vc.chan.dev->device,
		"%s(); phy=%p(%d) misaligned=%d\n", __func__,
		phy, phy->idx, misaligned);

	pdev = to_pxad_dev(phy->vchan->vc.chan.device);
	अगर (phy->vchan->drcmr <= pdev->nr_requestors) अणु
		reg = pxad_drcmr(phy->vchan->drcmr);
		ग_लिखोl_relaxed(DRCMR_MAPVLD | phy->idx, phy->base + reg);
	पूर्ण

	dalgn = phy_पढ़ोl_relaxed(phy, DALGN);
	अगर (misaligned)
		dalgn |= BIT(phy->idx);
	अन्यथा
		dalgn &= ~BIT(phy->idx);
	phy_ग_लिखोl_relaxed(phy, dalgn, DALGN);

	phy_ग_लिखोl(phy, PXA_DCSR_STOPIRQEN | PXA_DCSR_ENDINTR |
		   PXA_DCSR_BUSERR | PXA_DCSR_RUN, DCSR);
पूर्ण

अटल व्योम phy_disable(काष्ठा pxad_phy *phy)
अणु
	u32 dcsr;

	अगर (!phy)
		वापस;

	dcsr = phy_पढ़ोl_relaxed(phy, DCSR);
	dev_dbg(&phy->vchan->vc.chan.dev->device,
		"%s(): phy=%p(%d)\n", __func__, phy, phy->idx);
	phy_ग_लिखोl(phy, dcsr & ~PXA_DCSR_RUN & ~PXA_DCSR_STOPIRQEN, DCSR);
पूर्ण

अटल व्योम pxad_launch_chan(काष्ठा pxad_chan *chan,
				 काष्ठा pxad_desc_sw *desc)
अणु
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): desc=%p\n", __func__, desc);
	अगर (!chan->phy) अणु
		chan->phy = lookup_phy(chan);
		अगर (!chan->phy) अणु
			dev_dbg(&chan->vc.chan.dev->device,
				"%s(): no free dma channel\n", __func__);
			वापस;
		पूर्ण
	पूर्ण
	chan->bus_error = 0;

	/*
	 * Program the descriptor's address पूर्णांकo the DMA controller,
	 * then start the DMA transaction
	 */
	phy_ग_लिखोl(chan->phy, desc->first, DDADR);
	phy_enable(chan->phy, chan->misaligned);
	wake_up(&chan->wq_state);
पूर्ण

अटल व्योम set_updater_desc(काष्ठा pxad_desc_sw *sw_desc,
			     अचिन्हित दीर्घ flags)
अणु
	काष्ठा pxad_desc_hw *updater =
		sw_desc->hw_desc[sw_desc->nb_desc - 1];
	dma_addr_t dma = sw_desc->hw_desc[sw_desc->nb_desc - 2]->ddadr;

	updater->ddadr = DDADR_STOP;
	updater->dsadr = dma;
	updater->dtadr = dma + 8;
	updater->dcmd = PXA_DCMD_WIDTH4 | PXA_DCMD_BURST32 |
		(PXA_DCMD_LENGTH & माप(u32));
	अगर (flags & DMA_PREP_INTERRUPT)
		updater->dcmd |= PXA_DCMD_ENसूचीQEN;
	अगर (sw_desc->cyclic)
		sw_desc->hw_desc[sw_desc->nb_desc - 2]->ddadr = sw_desc->first;
पूर्ण

अटल bool is_desc_completed(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा pxad_desc_sw *sw_desc = to_pxad_sw_desc(vd);
	काष्ठा pxad_desc_hw *updater =
		sw_desc->hw_desc[sw_desc->nb_desc - 1];

	वापस updater->dtadr != (updater->dsadr + 8);
पूर्ण

अटल व्योम pxad_desc_chain(काष्ठा virt_dma_desc *vd1,
				काष्ठा virt_dma_desc *vd2)
अणु
	काष्ठा pxad_desc_sw *desc1 = to_pxad_sw_desc(vd1);
	काष्ठा pxad_desc_sw *desc2 = to_pxad_sw_desc(vd2);
	dma_addr_t dma_to_chain;

	dma_to_chain = desc2->first;
	desc1->hw_desc[desc1->nb_desc - 1]->ddadr = dma_to_chain;
पूर्ण

अटल bool pxad_try_hotchain(काष्ठा virt_dma_chan *vc,
				  काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा virt_dma_desc *vd_last_issued = शून्य;
	काष्ठा pxad_chan *chan = to_pxad_chan(&vc->chan);

	/*
	 * Attempt to hot chain the tx अगर the phy is still running. This is
	 * considered successful only अगर either the channel is still running
	 * after the chaining, or अगर the chained transfer is completed after
	 * having been hot chained.
	 * A change of alignment is not allowed, and क्रमbids hotchaining.
	 */
	अगर (is_chan_running(chan)) अणु
		BUG_ON(list_empty(&vc->desc_issued));

		अगर (!is_running_chan_misaligned(chan) &&
		    to_pxad_sw_desc(vd)->misaligned)
			वापस false;

		vd_last_issued = list_entry(vc->desc_issued.prev,
					    काष्ठा virt_dma_desc, node);
		pxad_desc_chain(vd_last_issued, vd);
		अगर (is_chan_running(chan) || is_desc_completed(vd))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक clear_chan_irq(काष्ठा pxad_phy *phy)
अणु
	u32 dcsr;
	u32 dपूर्णांक = पढ़ोl(phy->base + DINT);

	अगर (!(dपूर्णांक & BIT(phy->idx)))
		वापस PXA_DCSR_RUN;

	/* clear irq */
	dcsr = phy_पढ़ोl_relaxed(phy, DCSR);
	phy_ग_लिखोl(phy, dcsr, DCSR);
	अगर ((dcsr & PXA_DCSR_BUSERR) && (phy->vchan))
		dev_warn(&phy->vchan->vc.chan.dev->device,
			 "%s(chan=%p): PXA_DCSR_BUSERR\n",
			 __func__, &phy->vchan);

	वापस dcsr & ~PXA_DCSR_RUN;
पूर्ण

अटल irqवापस_t pxad_chan_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxad_phy *phy = dev_id;
	काष्ठा pxad_chan *chan = phy->vchan;
	काष्ठा virt_dma_desc *vd, *पंचांगp;
	अचिन्हित पूर्णांक dcsr;
	bool vd_completed;
	dma_cookie_t last_started = 0;

	BUG_ON(!chan);

	dcsr = clear_chan_irq(phy);
	अगर (dcsr & PXA_DCSR_RUN)
		वापस IRQ_NONE;

	spin_lock(&chan->vc.lock);
	list_क्रम_each_entry_safe(vd, पंचांगp, &chan->vc.desc_issued, node) अणु
		vd_completed = is_desc_completed(vd);
		dev_dbg(&chan->vc.chan.dev->device,
			"%s(): checking txd %p[%x]: completed=%d dcsr=0x%x\n",
			__func__, vd, vd->tx.cookie, vd_completed,
			dcsr);
		last_started = vd->tx.cookie;
		अगर (to_pxad_sw_desc(vd)->cyclic) अणु
			vchan_cyclic_callback(vd);
			अवरोध;
		पूर्ण
		अगर (vd_completed) अणु
			list_del(&vd->node);
			vchan_cookie_complete(vd);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (dcsr & PXA_DCSR_BUSERR) अणु
		chan->bus_error = last_started;
		phy_disable(phy);
	पूर्ण

	अगर (!chan->bus_error && dcsr & PXA_DCSR_STOPSTATE) अणु
		dev_dbg(&chan->vc.chan.dev->device,
		"%s(): channel stopped, submitted_empty=%d issued_empty=%d",
			__func__,
			list_empty(&chan->vc.desc_submitted),
			list_empty(&chan->vc.desc_issued));
		phy_ग_लिखोl_relaxed(phy, dcsr & ~PXA_DCSR_STOPIRQEN, DCSR);

		अगर (list_empty(&chan->vc.desc_issued)) अणु
			chan->misaligned =
				!list_empty(&chan->vc.desc_submitted);
		पूर्ण अन्यथा अणु
			vd = list_first_entry(&chan->vc.desc_issued,
					      काष्ठा virt_dma_desc, node);
			pxad_launch_chan(chan, to_pxad_sw_desc(vd));
		पूर्ण
	पूर्ण
	spin_unlock(&chan->vc.lock);
	wake_up(&chan->wq_state);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pxad_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxad_device *pdev = dev_id;
	काष्ठा pxad_phy *phy;
	u32 dपूर्णांक = पढ़ोl(pdev->base + DINT);
	पूर्णांक i, ret = IRQ_NONE;

	जबतक (dपूर्णांक) अणु
		i = __ffs(dपूर्णांक);
		dपूर्णांक &= (dपूर्णांक - 1);
		phy = &pdev->phys[i];
		अगर (pxad_chan_handler(irq, phy) == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pxad_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा pxad_device *pdev = to_pxad_dev(chan->vc.chan.device);

	अगर (chan->desc_pool)
		वापस 1;

	chan->desc_pool = dma_pool_create(dma_chan_name(dchan),
					  pdev->slave.dev,
					  माप(काष्ठा pxad_desc_hw),
					  __alignof__(काष्ठा pxad_desc_hw),
					  0);
	अगर (!chan->desc_pool) अणु
		dev_err(&chan->vc.chan.dev->device,
			"%s(): unable to allocate descriptor pool\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम pxad_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);

	vchan_मुक्त_chan_resources(&chan->vc);
	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;

	chan->drcmr = U32_MAX;
	chan->prio = PXAD_PRIO_LOWEST;
पूर्ण

अटल व्योम pxad_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	पूर्णांक i;
	dma_addr_t dma;
	काष्ठा pxad_desc_sw *sw_desc = to_pxad_sw_desc(vd);

	BUG_ON(sw_desc->nb_desc == 0);
	क्रम (i = sw_desc->nb_desc - 1; i >= 0; i--) अणु
		अगर (i > 0)
			dma = sw_desc->hw_desc[i - 1]->ddadr;
		अन्यथा
			dma = sw_desc->first;
		dma_pool_मुक्त(sw_desc->desc_pool,
			      sw_desc->hw_desc[i], dma);
	पूर्ण
	sw_desc->nb_desc = 0;
	kमुक्त(sw_desc);
पूर्ण

अटल काष्ठा pxad_desc_sw *
pxad_alloc_desc(काष्ठा pxad_chan *chan, अचिन्हित पूर्णांक nb_hw_desc)
अणु
	काष्ठा pxad_desc_sw *sw_desc;
	dma_addr_t dma;
	पूर्णांक i;

	sw_desc = kzalloc(माप(*sw_desc) +
			  nb_hw_desc * माप(काष्ठा pxad_desc_hw *),
			  GFP_NOWAIT);
	अगर (!sw_desc)
		वापस शून्य;
	sw_desc->desc_pool = chan->desc_pool;

	क्रम (i = 0; i < nb_hw_desc; i++) अणु
		sw_desc->hw_desc[i] = dma_pool_alloc(sw_desc->desc_pool,
						     GFP_NOWAIT, &dma);
		अगर (!sw_desc->hw_desc[i]) अणु
			dev_err(&chan->vc.chan.dev->device,
				"%s(): Couldn't allocate the %dth hw_desc from dma_pool %p\n",
				__func__, i, sw_desc->desc_pool);
			जाओ err;
		पूर्ण

		अगर (i == 0)
			sw_desc->first = dma;
		अन्यथा
			sw_desc->hw_desc[i - 1]->ddadr = dma;
		sw_desc->nb_desc++;
	पूर्ण

	वापस sw_desc;
err:
	pxad_मुक्त_desc(&sw_desc->vd);
	वापस शून्य;
पूर्ण

अटल dma_cookie_t pxad_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(tx->chan);
	काष्ठा pxad_chan *chan = to_pxad_chan(&vc->chan);
	काष्ठा virt_dma_desc *vd_chained = शून्य,
		*vd = container_of(tx, काष्ठा virt_dma_desc, tx);
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	set_updater_desc(to_pxad_sw_desc(vd), tx->flags);

	spin_lock_irqsave(&vc->lock, flags);
	cookie = dma_cookie_assign(tx);

	अगर (list_empty(&vc->desc_submitted) && pxad_try_hotchain(vc, vd)) अणु
		list_move_tail(&vd->node, &vc->desc_issued);
		dev_dbg(&chan->vc.chan.dev->device,
			"%s(): txd %p[%x]: submitted (hot linked)\n",
			__func__, vd, cookie);
		जाओ out;
	पूर्ण

	/*
	 * Fallback to placing the tx in the submitted queue
	 */
	अगर (!list_empty(&vc->desc_submitted)) अणु
		vd_chained = list_entry(vc->desc_submitted.prev,
					काष्ठा virt_dma_desc, node);
		/*
		 * Only chain the descriptors अगर no new misalignment is
		 * पूर्णांकroduced. If a new misalignment is chained, let the channel
		 * stop, and be relaunched in misalign mode from the irq
		 * handler.
		 */
		अगर (chan->misaligned || !to_pxad_sw_desc(vd)->misaligned)
			pxad_desc_chain(vd_chained, vd);
		अन्यथा
			vd_chained = शून्य;
	पूर्ण
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): txd %p[%x]: submitted (%s linked)\n",
		__func__, vd, cookie, vd_chained ? "cold" : "not");
	list_move_tail(&vd->node, &vc->desc_submitted);
	chan->misaligned |= to_pxad_sw_desc(vd)->misaligned;

out:
	spin_unlock_irqrestore(&vc->lock, flags);
	वापस cookie;
पूर्ण

अटल व्योम pxad_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा virt_dma_desc *vd_first;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	अगर (list_empty(&chan->vc.desc_submitted))
		जाओ out;

	vd_first = list_first_entry(&chan->vc.desc_submitted,
				    काष्ठा virt_dma_desc, node);
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): txd %p[%x]", __func__, vd_first, vd_first->tx.cookie);

	vchan_issue_pending(&chan->vc);
	अगर (!pxad_try_hotchain(&chan->vc, vd_first))
		pxad_launch_chan(chan, to_pxad_sw_desc(vd_first));
out:
	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल अंतरभूत काष्ठा dma_async_tx_descriptor *
pxad_tx_prep(काष्ठा virt_dma_chan *vc, काष्ठा virt_dma_desc *vd,
		 अचिन्हित दीर्घ tx_flags)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा pxad_chan *chan = container_of(vc, काष्ठा pxad_chan, vc);

	INIT_LIST_HEAD(&vd->node);
	tx = vchan_tx_prep(vc, vd, tx_flags);
	tx->tx_submit = pxad_tx_submit;
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): vc=%p txd=%p[%x] flags=0x%lx\n", __func__,
		vc, vd, vd->tx.cookie,
		tx_flags);

	वापस tx;
पूर्ण

अटल व्योम pxad_get_config(काष्ठा pxad_chan *chan,
			    क्रमागत dma_transfer_direction dir,
			    u32 *dcmd, u32 *dev_src, u32 *dev_dst)
अणु
	u32 maxburst = 0, dev_addr = 0;
	क्रमागत dma_slave_buswidth width = DMA_SLAVE_BUSWIDTH_UNDEFINED;
	काष्ठा pxad_device *pdev = to_pxad_dev(chan->vc.chan.device);

	*dcmd = 0;
	अगर (dir == DMA_DEV_TO_MEM) अणु
		maxburst = chan->cfg.src_maxburst;
		width = chan->cfg.src_addr_width;
		dev_addr = chan->cfg.src_addr;
		*dev_src = dev_addr;
		*dcmd |= PXA_DCMD_INCTRGADDR;
		अगर (chan->drcmr <= pdev->nr_requestors)
			*dcmd |= PXA_DCMD_FLOWSRC;
	पूर्ण
	अगर (dir == DMA_MEM_TO_DEV) अणु
		maxburst = chan->cfg.dst_maxburst;
		width = chan->cfg.dst_addr_width;
		dev_addr = chan->cfg.dst_addr;
		*dev_dst = dev_addr;
		*dcmd |= PXA_DCMD_INCSRCADDR;
		अगर (chan->drcmr <= pdev->nr_requestors)
			*dcmd |= PXA_DCMD_FLOWTRG;
	पूर्ण
	अगर (dir == DMA_MEM_TO_MEM)
		*dcmd |= PXA_DCMD_BURST32 | PXA_DCMD_INCTRGADDR |
			PXA_DCMD_INCSRCADDR;

	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): dev_addr=0x%x maxburst=%d width=%d  dir=%d\n",
		__func__, dev_addr, maxburst, width, dir);

	अगर (width == DMA_SLAVE_BUSWIDTH_1_BYTE)
		*dcmd |= PXA_DCMD_WIDTH1;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_2_BYTES)
		*dcmd |= PXA_DCMD_WIDTH2;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_4_BYTES)
		*dcmd |= PXA_DCMD_WIDTH4;

	अगर (maxburst == 8)
		*dcmd |= PXA_DCMD_BURST8;
	अन्यथा अगर (maxburst == 16)
		*dcmd |= PXA_DCMD_BURST16;
	अन्यथा अगर (maxburst == 32)
		*dcmd |= PXA_DCMD_BURST32;

	/* FIXME: drivers should be ported over to use the filter
	 * function. Once that's करोne, the following two lines can
	 * be हटाओd.
	 */
	अगर (chan->cfg.slave_id)
		chan->drcmr = chan->cfg.slave_id;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pxad_prep_स_नकल(काष्ठा dma_chan *dchan,
		 dma_addr_t dma_dst, dma_addr_t dma_src,
		 माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा pxad_desc_sw *sw_desc;
	काष्ठा pxad_desc_hw *hw_desc;
	u32 dcmd;
	अचिन्हित पूर्णांक i, nb_desc = 0;
	माप_प्रकार copy;

	अगर (!dchan || !len)
		वापस शून्य;

	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): dma_dst=0x%lx dma_src=0x%lx len=%zu flags=%lx\n",
		__func__, (अचिन्हित दीर्घ)dma_dst, (अचिन्हित दीर्घ)dma_src,
		len, flags);
	pxad_get_config(chan, DMA_MEM_TO_MEM, &dcmd, शून्य, शून्य);

	nb_desc = DIV_ROUND_UP(len, PDMA_MAX_DESC_BYTES);
	sw_desc = pxad_alloc_desc(chan, nb_desc + 1);
	अगर (!sw_desc)
		वापस शून्य;
	sw_desc->len = len;

	अगर (!IS_ALIGNED(dma_src, 1 << PDMA_ALIGNMENT) ||
	    !IS_ALIGNED(dma_dst, 1 << PDMA_ALIGNMENT))
		sw_desc->misaligned = true;

	i = 0;
	करो अणु
		hw_desc = sw_desc->hw_desc[i++];
		copy = min_t(माप_प्रकार, len, PDMA_MAX_DESC_BYTES);
		hw_desc->dcmd = dcmd | (PXA_DCMD_LENGTH & copy);
		hw_desc->dsadr = dma_src;
		hw_desc->dtadr = dma_dst;
		len -= copy;
		dma_src += copy;
		dma_dst += copy;
	पूर्ण जबतक (len);
	set_updater_desc(sw_desc, flags);

	वापस pxad_tx_prep(&chan->vc, &sw_desc->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pxad_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
		   अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
		   अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा pxad_desc_sw *sw_desc;
	माप_प्रकार len, avail;
	काष्ठा scatterlist *sg;
	dma_addr_t dma;
	u32 dcmd, dsadr = 0, dtadr = 0;
	अचिन्हित पूर्णांक nb_desc = 0, i, j = 0;

	अगर ((sgl == शून्य) || (sg_len == 0))
		वापस शून्य;

	pxad_get_config(chan, dir, &dcmd, &dsadr, &dtadr);
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): dir=%d flags=%lx\n", __func__, dir, flags);

	क्रम_each_sg(sgl, sg, sg_len, i)
		nb_desc += DIV_ROUND_UP(sg_dma_len(sg), PDMA_MAX_DESC_BYTES);
	sw_desc = pxad_alloc_desc(chan, nb_desc + 1);
	अगर (!sw_desc)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma = sg_dma_address(sg);
		avail = sg_dma_len(sg);
		sw_desc->len += avail;

		करो अणु
			len = min_t(माप_प्रकार, avail, PDMA_MAX_DESC_BYTES);
			अगर (dma & 0x7)
				sw_desc->misaligned = true;

			sw_desc->hw_desc[j]->dcmd =
				dcmd | (PXA_DCMD_LENGTH & len);
			sw_desc->hw_desc[j]->dsadr = dsadr ? dsadr : dma;
			sw_desc->hw_desc[j++]->dtadr = dtadr ? dtadr : dma;

			dma += len;
			avail -= len;
		पूर्ण जबतक (avail);
	पूर्ण
	set_updater_desc(sw_desc, flags);

	वापस pxad_tx_prep(&chan->vc, &sw_desc->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
pxad_prep_dma_cyclic(काष्ठा dma_chan *dchan,
		     dma_addr_t buf_addr, माप_प्रकार len, माप_प्रकार period_len,
		     क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा pxad_desc_sw *sw_desc;
	काष्ठा pxad_desc_hw **phw_desc;
	dma_addr_t dma;
	u32 dcmd, dsadr = 0, dtadr = 0;
	अचिन्हित पूर्णांक nb_desc = 0;

	अगर (!dchan || !len || !period_len)
		वापस शून्य;
	अगर ((dir != DMA_DEV_TO_MEM) && (dir != DMA_MEM_TO_DEV)) अणु
		dev_err(&chan->vc.chan.dev->device,
			"Unsupported direction for cyclic DMA\n");
		वापस शून्य;
	पूर्ण
	/* the buffer length must be a multiple of period_len */
	अगर (len % period_len != 0 || period_len > PDMA_MAX_DESC_BYTES ||
	    !IS_ALIGNED(period_len, 1 << PDMA_ALIGNMENT))
		वापस शून्य;

	pxad_get_config(chan, dir, &dcmd, &dsadr, &dtadr);
	dcmd |= PXA_DCMD_ENसूचीQEN | (PXA_DCMD_LENGTH & period_len);
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): buf_addr=0x%lx len=%zu period=%zu dir=%d flags=%lx\n",
		__func__, (अचिन्हित दीर्घ)buf_addr, len, period_len, dir, flags);

	nb_desc = DIV_ROUND_UP(period_len, PDMA_MAX_DESC_BYTES);
	nb_desc *= DIV_ROUND_UP(len, period_len);
	sw_desc = pxad_alloc_desc(chan, nb_desc + 1);
	अगर (!sw_desc)
		वापस शून्य;
	sw_desc->cyclic = true;
	sw_desc->len = len;

	phw_desc = sw_desc->hw_desc;
	dma = buf_addr;
	करो अणु
		phw_desc[0]->dsadr = dsadr ? dsadr : dma;
		phw_desc[0]->dtadr = dtadr ? dtadr : dma;
		phw_desc[0]->dcmd = dcmd;
		phw_desc++;
		dma += period_len;
		len -= period_len;
	पूर्ण जबतक (len);
	set_updater_desc(sw_desc, flags);

	वापस pxad_tx_prep(&chan->vc, &sw_desc->vd, flags);
पूर्ण

अटल पूर्णांक pxad_config(काष्ठा dma_chan *dchan,
		       काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);

	अगर (!dchan)
		वापस -EINVAL;

	chan->cfg = *cfg;
	वापस 0;
पूर्ण

अटल पूर्णांक pxad_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	काष्ठा pxad_device *pdev = to_pxad_dev(chan->vc.chan.device);
	काष्ठा virt_dma_desc *vd = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा pxad_phy *phy;
	LIST_HEAD(head);

	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): vchan %p: terminate all\n", __func__, &chan->vc);

	spin_lock_irqsave(&chan->vc.lock, flags);
	vchan_get_all_descriptors(&chan->vc, &head);

	list_क्रम_each_entry(vd, &head, node) अणु
		dev_dbg(&chan->vc.chan.dev->device,
			"%s(): cancelling txd %p[%x] (completed=%d)", __func__,
			vd, vd->tx.cookie, is_desc_completed(vd));
	पूर्ण

	phy = chan->phy;
	अगर (phy) अणु
		phy_disable(chan->phy);
		pxad_मुक्त_phy(chan);
		chan->phy = शून्य;
		spin_lock(&pdev->phy_lock);
		phy->vchan = शून्य;
		spin_unlock(&pdev->phy_lock);
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&chan->vc, &head);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pxad_residue(काष्ठा pxad_chan *chan,
				 dma_cookie_t cookie)
अणु
	काष्ठा virt_dma_desc *vd = शून्य;
	काष्ठा pxad_desc_sw *sw_desc = शून्य;
	काष्ठा pxad_desc_hw *hw_desc = शून्य;
	u32 curr, start, len, end, residue = 0;
	अचिन्हित दीर्घ flags;
	bool passed = false;
	पूर्णांक i;

	/*
	 * If the channel करोes not have a phy poपूर्णांकer anymore, it has alपढ़ोy
	 * been completed. Thereक्रमe, its residue is 0.
	 */
	अगर (!chan->phy)
		वापस 0;

	spin_lock_irqsave(&chan->vc.lock, flags);

	vd = vchan_find_desc(&chan->vc, cookie);
	अगर (!vd)
		जाओ out;

	sw_desc = to_pxad_sw_desc(vd);
	अगर (sw_desc->hw_desc[0]->dcmd & PXA_DCMD_INCSRCADDR)
		curr = phy_पढ़ोl_relaxed(chan->phy, DSADR);
	अन्यथा
		curr = phy_पढ़ोl_relaxed(chan->phy, DTADR);

	/*
	 * curr has to be actually पढ़ो beक्रमe checking descriptor
	 * completion, so that a curr inside a status updater
	 * descriptor implies the following test वापसs true, and
	 * preventing reordering of curr load and the test.
	 */
	rmb();
	अगर (is_desc_completed(vd))
		जाओ out;

	क्रम (i = 0; i < sw_desc->nb_desc - 1; i++) अणु
		hw_desc = sw_desc->hw_desc[i];
		अगर (sw_desc->hw_desc[0]->dcmd & PXA_DCMD_INCSRCADDR)
			start = hw_desc->dsadr;
		अन्यथा
			start = hw_desc->dtadr;
		len = hw_desc->dcmd & PXA_DCMD_LENGTH;
		end = start + len;

		/*
		 * 'passed' will be latched once we found the descriptor
		 * which lies inside the boundaries of the curr
		 * poपूर्णांकer. All descriptors that occur in the list
		 * _after_ we found that partially handled descriptor
		 * are still to be processed and are hence added to the
		 * residual bytes counter.
		 */

		अगर (passed) अणु
			residue += len;
		पूर्ण अन्यथा अगर (curr >= start && curr <= end) अणु
			residue += end - curr;
			passed = true;
		पूर्ण
	पूर्ण
	अगर (!passed)
		residue = sw_desc->len;

out:
	spin_unlock_irqrestore(&chan->vc.lock, flags);
	dev_dbg(&chan->vc.chan.dev->device,
		"%s(): txd %p[%x] sw_desc=%p: %d\n",
		__func__, vd, cookie, sw_desc, residue);
	वापस residue;
पूर्ण

अटल क्रमागत dma_status pxad_tx_status(काष्ठा dma_chan *dchan,
				      dma_cookie_t cookie,
				      काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);
	क्रमागत dma_status ret;

	अगर (cookie == chan->bus_error)
		वापस DMA_ERROR;

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (likely(txstate && (ret != DMA_ERROR)))
		dma_set_residue(txstate, pxad_residue(chan, cookie));

	वापस ret;
पूर्ण

अटल व्योम pxad_synchronize(काष्ठा dma_chan *dchan)
अणु
	काष्ठा pxad_chan *chan = to_pxad_chan(dchan);

	रुको_event(chan->wq_state, !is_chan_running(chan));
	vchan_synchronize(&chan->vc);
पूर्ण

अटल व्योम pxad_मुक्त_channels(काष्ठा dma_device *dmadev)
अणु
	काष्ठा pxad_chan *c, *cn;

	list_क्रम_each_entry_safe(c, cn, &dmadev->channels,
				 vc.chan.device_node) अणु
		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
	पूर्ण
पूर्ण

अटल पूर्णांक pxad_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा pxad_device *pdev = platक्रमm_get_drvdata(op);

	pxad_cleanup_debugfs(pdev);
	pxad_मुक्त_channels(&pdev->slave);
	वापस 0;
पूर्ण

अटल पूर्णांक pxad_init_phys(काष्ठा platक्रमm_device *op,
			  काष्ठा pxad_device *pdev,
			  अचिन्हित पूर्णांक nb_phy_chans)
अणु
	पूर्णांक irq0, irq, nr_irq = 0, i, ret;
	काष्ठा pxad_phy *phy;

	irq0 = platक्रमm_get_irq(op, 0);
	अगर (irq0 < 0)
		वापस irq0;

	pdev->phys = devm_kसुस्मृति(&op->dev, nb_phy_chans,
				  माप(pdev->phys[0]), GFP_KERNEL);
	अगर (!pdev->phys)
		वापस -ENOMEM;

	क्रम (i = 0; i < nb_phy_chans; i++)
		अगर (platक्रमm_get_irq(op, i) > 0)
			nr_irq++;

	क्रम (i = 0; i < nb_phy_chans; i++) अणु
		phy = &pdev->phys[i];
		phy->base = pdev->base;
		phy->idx = i;
		irq = platक्रमm_get_irq(op, i);
		अगर ((nr_irq > 1) && (irq > 0))
			ret = devm_request_irq(&op->dev, irq,
					       pxad_chan_handler,
					       IRQF_SHARED, "pxa-dma", phy);
		अगर ((nr_irq == 1) && (i == 0))
			ret = devm_request_irq(&op->dev, irq0,
					       pxad_पूर्णांक_handler,
					       IRQF_SHARED, "pxa-dma", pdev);
		अगर (ret) अणु
			dev_err(pdev->slave.dev,
				"%s(): can't request irq %d:%d\n", __func__,
				irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pxad_dt_ids[] = अणु
	अणु .compatible = "marvell,pdma-1.0", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxad_dt_ids);

अटल काष्ठा dma_chan *pxad_dma_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा pxad_device *d = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;

	chan = dma_get_any_slave_channel(&d->slave);
	अगर (!chan)
		वापस शून्य;

	to_pxad_chan(chan)->drcmr = dma_spec->args[0];
	to_pxad_chan(chan)->prio = dma_spec->args[1];

	वापस chan;
पूर्ण

अटल पूर्णांक pxad_init_dmadev(काष्ठा platक्रमm_device *op,
			    काष्ठा pxad_device *pdev,
			    अचिन्हित पूर्णांक nr_phy_chans,
			    अचिन्हित पूर्णांक nr_requestors)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	काष्ठा pxad_chan *c;

	pdev->nr_chans = nr_phy_chans;
	pdev->nr_requestors = nr_requestors;
	INIT_LIST_HEAD(&pdev->slave.channels);
	pdev->slave.device_alloc_chan_resources = pxad_alloc_chan_resources;
	pdev->slave.device_मुक्त_chan_resources = pxad_मुक्त_chan_resources;
	pdev->slave.device_tx_status = pxad_tx_status;
	pdev->slave.device_issue_pending = pxad_issue_pending;
	pdev->slave.device_config = pxad_config;
	pdev->slave.device_synchronize = pxad_synchronize;
	pdev->slave.device_terminate_all = pxad_terminate_all;

	अगर (op->dev.coherent_dma_mask)
		dma_set_mask(&op->dev, op->dev.coherent_dma_mask);
	अन्यथा
		dma_set_mask(&op->dev, DMA_BIT_MASK(32));

	ret = pxad_init_phys(op, pdev, nr_phy_chans);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_phy_chans; i++) अणु
		c = devm_kzalloc(&op->dev, माप(*c), GFP_KERNEL);
		अगर (!c)
			वापस -ENOMEM;

		c->drcmr = U32_MAX;
		c->prio = PXAD_PRIO_LOWEST;
		c->vc.desc_मुक्त = pxad_मुक्त_desc;
		vchan_init(&c->vc, &pdev->slave);
		init_रुकोqueue_head(&c->wq_state);
	पूर्ण

	वापस dmaenginem_async_device_रेजिस्टर(&pdev->slave);
पूर्ण

अटल पूर्णांक pxad_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा pxad_device *pdev;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा dma_slave_map *slave_map = शून्य;
	काष्ठा mmp_dma_platdata *pdata = dev_get_platdata(&op->dev);
	काष्ठा resource *iores;
	पूर्णांक ret, dma_channels = 0, nb_requestors = 0, slave_map_cnt = 0;
	स्थिर क्रमागत dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE   | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES;

	pdev = devm_kzalloc(&op->dev, माप(*pdev), GFP_KERNEL);
	अगर (!pdev)
		वापस -ENOMEM;

	spin_lock_init(&pdev->phy_lock);

	iores = platक्रमm_get_resource(op, IORESOURCE_MEM, 0);
	pdev->base = devm_ioremap_resource(&op->dev, iores);
	अगर (IS_ERR(pdev->base))
		वापस PTR_ERR(pdev->base);

	of_id = of_match_device(pxad_dt_ids, &op->dev);
	अगर (of_id) अणु
		of_property_पढ़ो_u32(op->dev.of_node, "#dma-channels",
				     &dma_channels);
		ret = of_property_पढ़ो_u32(op->dev.of_node, "#dma-requests",
					   &nb_requestors);
		अगर (ret) अणु
			dev_warn(pdev->slave.dev,
				 "#dma-requests set to default 32 as missing in OF: %d",
				 ret);
			nb_requestors = 32;
		पूर्ण
	पूर्ण अन्यथा अगर (pdata && pdata->dma_channels) अणु
		dma_channels = pdata->dma_channels;
		nb_requestors = pdata->nb_requestors;
		slave_map = pdata->slave_map;
		slave_map_cnt = pdata->slave_map_cnt;
	पूर्ण अन्यथा अणु
		dma_channels = 32;	/* शेष 32 channel */
	पूर्ण

	dma_cap_set(DMA_SLAVE, pdev->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, pdev->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, pdev->slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, pdev->slave.cap_mask);
	pdev->slave.device_prep_dma_स_नकल = pxad_prep_स_नकल;
	pdev->slave.device_prep_slave_sg = pxad_prep_slave_sg;
	pdev->slave.device_prep_dma_cyclic = pxad_prep_dma_cyclic;
	pdev->slave.filter.map = slave_map;
	pdev->slave.filter.mapcnt = slave_map_cnt;
	pdev->slave.filter.fn = pxad_filter_fn;

	pdev->slave.copy_align = PDMA_ALIGNMENT;
	pdev->slave.src_addr_widths = widths;
	pdev->slave.dst_addr_widths = widths;
	pdev->slave.directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	pdev->slave.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	pdev->slave.descriptor_reuse = true;

	pdev->slave.dev = &op->dev;
	ret = pxad_init_dmadev(op, pdev, dma_channels, nb_requestors);
	अगर (ret) अणु
		dev_err(pdev->slave.dev, "unable to register\n");
		वापस ret;
	पूर्ण

	अगर (op->dev.of_node) अणु
		/* Device-tree DMA controller registration */
		ret = of_dma_controller_रेजिस्टर(op->dev.of_node,
						 pxad_dma_xlate, pdev);
		अगर (ret < 0) अणु
			dev_err(pdev->slave.dev,
				"of_dma_controller_register failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(op, pdev);
	pxad_init_debugfs(pdev);
	dev_info(pdev->slave.dev, "initialized %d channels on %d requestors\n",
		 dma_channels, nb_requestors);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id pxad_id_table[] = अणु
	अणु "pxa-dma", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pxad_driver = अणु
	.driver		= अणु
		.name	= "pxa-dma",
		.of_match_table = pxad_dt_ids,
	पूर्ण,
	.id_table	= pxad_id_table,
	.probe		= pxad_probe,
	.हटाओ		= pxad_हटाओ,
पूर्ण;

अटल bool pxad_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा pxad_chan *c = to_pxad_chan(chan);
	काष्ठा pxad_param *p = param;

	अगर (chan->device->dev->driver != &pxad_driver.driver)
		वापस false;

	c->drcmr = p->drcmr;
	c->prio = p->prio;

	वापस true;
पूर्ण

module_platक्रमm_driver(pxad_driver);

MODULE_DESCRIPTION("Marvell PXA Peripheral DMA Driver");
MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_LICENSE("GPL v2");
