<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG Multi-thपढ़ोed DMA Controller (MDC)
 *
 * Copyright (C) 2009,2012,2013 Imagination Technologies Ltd.
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा MDC_MAX_DMA_CHANNELS			32

#घोषणा MDC_GENERAL_CONFIG			0x000
#घोषणा MDC_GENERAL_CONFIG_LIST_IEN		BIT(31)
#घोषणा MDC_GENERAL_CONFIG_IEN			BIT(29)
#घोषणा MDC_GENERAL_CONFIG_LEVEL_INT		BIT(28)
#घोषणा MDC_GENERAL_CONFIG_INC_W		BIT(12)
#घोषणा MDC_GENERAL_CONFIG_INC_R		BIT(8)
#घोषणा MDC_GENERAL_CONFIG_PHYSICAL_W		BIT(7)
#घोषणा MDC_GENERAL_CONFIG_WIDTH_W_SHIFT	4
#घोषणा MDC_GENERAL_CONFIG_WIDTH_W_MASK		0x7
#घोषणा MDC_GENERAL_CONFIG_PHYSICAL_R		BIT(3)
#घोषणा MDC_GENERAL_CONFIG_WIDTH_R_SHIFT	0
#घोषणा MDC_GENERAL_CONFIG_WIDTH_R_MASK		0x7

#घोषणा MDC_READ_PORT_CONFIG			0x004
#घोषणा MDC_READ_PORT_CONFIG_STHREAD_SHIFT	28
#घोषणा MDC_READ_PORT_CONFIG_STHREAD_MASK	0xf
#घोषणा MDC_READ_PORT_CONFIG_RTHREAD_SHIFT	24
#घोषणा MDC_READ_PORT_CONFIG_RTHREAD_MASK	0xf
#घोषणा MDC_READ_PORT_CONFIG_WTHREAD_SHIFT	16
#घोषणा MDC_READ_PORT_CONFIG_WTHREAD_MASK	0xf
#घोषणा MDC_READ_PORT_CONFIG_BURST_SIZE_SHIFT	4
#घोषणा MDC_READ_PORT_CONFIG_BURST_SIZE_MASK	0xff
#घोषणा MDC_READ_PORT_CONFIG_DREQ_ENABLE	BIT(1)

#घोषणा MDC_READ_ADDRESS			0x008

#घोषणा MDC_WRITE_ADDRESS			0x00c

#घोषणा MDC_TRANSFER_SIZE			0x010
#घोषणा MDC_TRANSFER_SIZE_MASK			0xffffff

#घोषणा MDC_LIST_NODE_ADDRESS			0x014

#घोषणा MDC_CMDS_PROCESSED			0x018
#घोषणा MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT	16
#घोषणा MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK	0x3f
#घोषणा MDC_CMDS_PROCESSED_INT_ACTIVE		BIT(8)
#घोषणा MDC_CMDS_PROCESSED_CMDS_DONE_SHIFT	0
#घोषणा MDC_CMDS_PROCESSED_CMDS_DONE_MASK	0x3f

#घोषणा MDC_CONTROL_AND_STATUS			0x01c
#घोषणा MDC_CONTROL_AND_STATUS_CANCEL		BIT(20)
#घोषणा MDC_CONTROL_AND_STATUS_LIST_EN		BIT(4)
#घोषणा MDC_CONTROL_AND_STATUS_EN		BIT(0)

#घोषणा MDC_ACTIVE_TRANSFER_SIZE		0x030

#घोषणा MDC_GLOBAL_CONFIG_A				0x900
#घोषणा MDC_GLOBAL_CONFIG_A_THREAD_ID_WIDTH_SHIFT	16
#घोषणा MDC_GLOBAL_CONFIG_A_THREAD_ID_WIDTH_MASK	0xff
#घोषणा MDC_GLOBAL_CONFIG_A_DMA_CONTEXTS_SHIFT		8
#घोषणा MDC_GLOBAL_CONFIG_A_DMA_CONTEXTS_MASK		0xff
#घोषणा MDC_GLOBAL_CONFIG_A_SYS_DAT_WIDTH_SHIFT		0
#घोषणा MDC_GLOBAL_CONFIG_A_SYS_DAT_WIDTH_MASK		0xff

काष्ठा mdc_hw_list_desc अणु
	u32 gen_conf;
	u32 पढ़ोport_conf;
	u32 पढ़ो_addr;
	u32 ग_लिखो_addr;
	u32 xfer_size;
	u32 node_addr;
	u32 cmds_करोne;
	u32 ctrl_status;
	/*
	 * Not part of the list descriptor, but instead used by the CPU to
	 * traverse the list.
	 */
	काष्ठा mdc_hw_list_desc *next_desc;
पूर्ण;

काष्ठा mdc_tx_desc अणु
	काष्ठा mdc_chan *chan;
	काष्ठा virt_dma_desc vd;
	dma_addr_t list_phys;
	काष्ठा mdc_hw_list_desc *list;
	bool cyclic;
	bool cmd_loaded;
	अचिन्हित पूर्णांक list_len;
	अचिन्हित पूर्णांक list_period_len;
	माप_प्रकार list_xfer_size;
	अचिन्हित पूर्णांक list_cmds_करोne;
पूर्ण;

काष्ठा mdc_chan अणु
	काष्ठा mdc_dma *mdma;
	काष्ठा virt_dma_chan vc;
	काष्ठा dma_slave_config config;
	काष्ठा mdc_tx_desc *desc;
	पूर्णांक irq;
	अचिन्हित पूर्णांक periph;
	अचिन्हित पूर्णांक thपढ़ो;
	अचिन्हित पूर्णांक chan_nr;
पूर्ण;

काष्ठा mdc_dma_soc_data अणु
	व्योम (*enable_chan)(काष्ठा mdc_chan *mchan);
	व्योम (*disable_chan)(काष्ठा mdc_chan *mchan);
पूर्ण;

काष्ठा mdc_dma अणु
	काष्ठा dma_device dma_dev;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा dma_pool *desc_pool;
	काष्ठा regmap *periph_regs;
	spinlock_t lock;
	अचिन्हित पूर्णांक nr_thपढ़ोs;
	अचिन्हित पूर्णांक nr_channels;
	अचिन्हित पूर्णांक bus_width;
	अचिन्हित पूर्णांक max_burst_mult;
	अचिन्हित पूर्णांक max_xfer_size;
	स्थिर काष्ठा mdc_dma_soc_data *soc;
	काष्ठा mdc_chan channels[MDC_MAX_DMA_CHANNELS];
पूर्ण;

अटल अंतरभूत u32 mdc_पढ़ोl(काष्ठा mdc_dma *mdma, u32 reg)
अणु
	वापस पढ़ोl(mdma->regs + reg);
पूर्ण

अटल अंतरभूत व्योम mdc_ग_लिखोl(काष्ठा mdc_dma *mdma, u32 val, u32 reg)
अणु
	ग_लिखोl(val, mdma->regs + reg);
पूर्ण

अटल अंतरभूत u32 mdc_chan_पढ़ोl(काष्ठा mdc_chan *mchan, u32 reg)
अणु
	वापस mdc_पढ़ोl(mchan->mdma, mchan->chan_nr * 0x040 + reg);
पूर्ण

अटल अंतरभूत व्योम mdc_chan_ग_लिखोl(काष्ठा mdc_chan *mchan, u32 val, u32 reg)
अणु
	mdc_ग_लिखोl(mchan->mdma, val, mchan->chan_nr * 0x040 + reg);
पूर्ण

अटल अंतरभूत काष्ठा mdc_chan *to_mdc_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(to_virt_chan(c), काष्ठा mdc_chan, vc);
पूर्ण

अटल अंतरभूत काष्ठा mdc_tx_desc *to_mdc_desc(काष्ठा dma_async_tx_descriptor *t)
अणु
	काष्ठा virt_dma_desc *vdesc = container_of(t, काष्ठा virt_dma_desc, tx);

	वापस container_of(vdesc, काष्ठा mdc_tx_desc, vd);
पूर्ण

अटल अंतरभूत काष्ठा device *mdma2dev(काष्ठा mdc_dma *mdma)
अणु
	वापस mdma->dma_dev.dev;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक to_mdc_width(अचिन्हित पूर्णांक bytes)
अणु
	वापस ffs(bytes) - 1;
पूर्ण

अटल अंतरभूत व्योम mdc_set_पढ़ो_width(काष्ठा mdc_hw_list_desc *ldesc,
				      अचिन्हित पूर्णांक bytes)
अणु
	ldesc->gen_conf |= to_mdc_width(bytes) <<
		MDC_GENERAL_CONFIG_WIDTH_R_SHIFT;
पूर्ण

अटल अंतरभूत व्योम mdc_set_ग_लिखो_width(काष्ठा mdc_hw_list_desc *ldesc,
				       अचिन्हित पूर्णांक bytes)
अणु
	ldesc->gen_conf |= to_mdc_width(bytes) <<
		MDC_GENERAL_CONFIG_WIDTH_W_SHIFT;
पूर्ण

अटल व्योम mdc_list_desc_config(काष्ठा mdc_chan *mchan,
				 काष्ठा mdc_hw_list_desc *ldesc,
				 क्रमागत dma_transfer_direction dir,
				 dma_addr_t src, dma_addr_t dst, माप_प्रकार len)
अणु
	काष्ठा mdc_dma *mdma = mchan->mdma;
	अचिन्हित पूर्णांक max_burst, burst_size;

	ldesc->gen_conf = MDC_GENERAL_CONFIG_IEN | MDC_GENERAL_CONFIG_LIST_IEN |
		MDC_GENERAL_CONFIG_LEVEL_INT | MDC_GENERAL_CONFIG_PHYSICAL_W |
		MDC_GENERAL_CONFIG_PHYSICAL_R;
	ldesc->पढ़ोport_conf =
		(mchan->thपढ़ो << MDC_READ_PORT_CONFIG_STHREAD_SHIFT) |
		(mchan->thपढ़ो << MDC_READ_PORT_CONFIG_RTHREAD_SHIFT) |
		(mchan->thपढ़ो << MDC_READ_PORT_CONFIG_WTHREAD_SHIFT);
	ldesc->पढ़ो_addr = src;
	ldesc->ग_लिखो_addr = dst;
	ldesc->xfer_size = len - 1;
	ldesc->node_addr = 0;
	ldesc->cmds_करोne = 0;
	ldesc->ctrl_status = MDC_CONTROL_AND_STATUS_LIST_EN |
		MDC_CONTROL_AND_STATUS_EN;
	ldesc->next_desc = शून्य;

	अगर (IS_ALIGNED(dst, mdma->bus_width) &&
	    IS_ALIGNED(src, mdma->bus_width))
		max_burst = mdma->bus_width * mdma->max_burst_mult;
	अन्यथा
		max_burst = mdma->bus_width * (mdma->max_burst_mult - 1);

	अगर (dir == DMA_MEM_TO_DEV) अणु
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_R;
		ldesc->पढ़ोport_conf |= MDC_READ_PORT_CONFIG_DREQ_ENABLE;
		mdc_set_पढ़ो_width(ldesc, mdma->bus_width);
		mdc_set_ग_लिखो_width(ldesc, mchan->config.dst_addr_width);
		burst_size = min(max_burst, mchan->config.dst_maxburst *
				 mchan->config.dst_addr_width);
	पूर्ण अन्यथा अगर (dir == DMA_DEV_TO_MEM) अणु
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_W;
		ldesc->पढ़ोport_conf |= MDC_READ_PORT_CONFIG_DREQ_ENABLE;
		mdc_set_पढ़ो_width(ldesc, mchan->config.src_addr_width);
		mdc_set_ग_लिखो_width(ldesc, mdma->bus_width);
		burst_size = min(max_burst, mchan->config.src_maxburst *
				 mchan->config.src_addr_width);
	पूर्ण अन्यथा अणु
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_R |
			MDC_GENERAL_CONFIG_INC_W;
		mdc_set_पढ़ो_width(ldesc, mdma->bus_width);
		mdc_set_ग_लिखो_width(ldesc, mdma->bus_width);
		burst_size = max_burst;
	पूर्ण
	ldesc->पढ़ोport_conf |= (burst_size - 1) <<
		MDC_READ_PORT_CONFIG_BURST_SIZE_SHIFT;
पूर्ण

अटल व्योम mdc_list_desc_मुक्त(काष्ठा mdc_tx_desc *mdesc)
अणु
	काष्ठा mdc_dma *mdma = mdesc->chan->mdma;
	काष्ठा mdc_hw_list_desc *curr, *next;
	dma_addr_t curr_phys, next_phys;

	curr = mdesc->list;
	curr_phys = mdesc->list_phys;
	जबतक (curr) अणु
		next = curr->next_desc;
		next_phys = curr->node_addr;
		dma_pool_मुक्त(mdma->desc_pool, curr, curr_phys);
		curr = next;
		curr_phys = next_phys;
	पूर्ण
पूर्ण

अटल व्योम mdc_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा mdc_tx_desc *mdesc = to_mdc_desc(&vd->tx);

	mdc_list_desc_मुक्त(mdesc);
	kमुक्त(mdesc);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mdc_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src, माप_प्रकार len,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा mdc_dma *mdma = mchan->mdma;
	काष्ठा mdc_tx_desc *mdesc;
	काष्ठा mdc_hw_list_desc *curr, *prev = शून्य;
	dma_addr_t curr_phys;

	अगर (!len)
		वापस शून्य;

	mdesc = kzalloc(माप(*mdesc), GFP_NOWAIT);
	अगर (!mdesc)
		वापस शून्य;
	mdesc->chan = mchan;
	mdesc->list_xfer_size = len;

	जबतक (len > 0) अणु
		माप_प्रकार xfer_size;

		curr = dma_pool_alloc(mdma->desc_pool, GFP_NOWAIT, &curr_phys);
		अगर (!curr)
			जाओ मुक्त_desc;

		अगर (prev) अणु
			prev->node_addr = curr_phys;
			prev->next_desc = curr;
		पूर्ण अन्यथा अणु
			mdesc->list_phys = curr_phys;
			mdesc->list = curr;
		पूर्ण

		xfer_size = min_t(माप_प्रकार, mdma->max_xfer_size, len);

		mdc_list_desc_config(mchan, curr, DMA_MEM_TO_MEM, src, dest,
				     xfer_size);

		prev = curr;

		mdesc->list_len++;
		src += xfer_size;
		dest += xfer_size;
		len -= xfer_size;
	पूर्ण

	वापस vchan_tx_prep(&mchan->vc, &mdesc->vd, flags);

मुक्त_desc:
	mdc_desc_मुक्त(&mdesc->vd);

	वापस शून्य;
पूर्ण

अटल पूर्णांक mdc_check_slave_width(काष्ठा mdc_chan *mchan,
				 क्रमागत dma_transfer_direction dir)
अणु
	क्रमागत dma_slave_buswidth width;

	अगर (dir == DMA_MEM_TO_DEV)
		width = mchan->config.dst_addr_width;
	अन्यथा
		width = mchan->config.src_addr_width;

	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (width > mchan->mdma->bus_width)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mdc_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction dir,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा mdc_dma *mdma = mchan->mdma;
	काष्ठा mdc_tx_desc *mdesc;
	काष्ठा mdc_hw_list_desc *curr, *prev = शून्य;
	dma_addr_t curr_phys;

	अगर (!buf_len && !period_len)
		वापस शून्य;

	अगर (!is_slave_direction(dir))
		वापस शून्य;

	अगर (mdc_check_slave_width(mchan, dir) < 0)
		वापस शून्य;

	mdesc = kzalloc(माप(*mdesc), GFP_NOWAIT);
	अगर (!mdesc)
		वापस शून्य;
	mdesc->chan = mchan;
	mdesc->cyclic = true;
	mdesc->list_xfer_size = buf_len;
	mdesc->list_period_len = DIV_ROUND_UP(period_len,
					      mdma->max_xfer_size);

	जबतक (buf_len > 0) अणु
		माप_प्रकार reमुख्यder = min(period_len, buf_len);

		जबतक (reमुख्यder > 0) अणु
			माप_प्रकार xfer_size;

			curr = dma_pool_alloc(mdma->desc_pool, GFP_NOWAIT,
					      &curr_phys);
			अगर (!curr)
				जाओ मुक्त_desc;

			अगर (!prev) अणु
				mdesc->list_phys = curr_phys;
				mdesc->list = curr;
			पूर्ण अन्यथा अणु
				prev->node_addr = curr_phys;
				prev->next_desc = curr;
			पूर्ण

			xfer_size = min_t(माप_प्रकार, mdma->max_xfer_size,
					  reमुख्यder);

			अगर (dir == DMA_MEM_TO_DEV) अणु
				mdc_list_desc_config(mchan, curr, dir,
						     buf_addr,
						     mchan->config.dst_addr,
						     xfer_size);
			पूर्ण अन्यथा अणु
				mdc_list_desc_config(mchan, curr, dir,
						     mchan->config.src_addr,
						     buf_addr,
						     xfer_size);
			पूर्ण

			prev = curr;

			mdesc->list_len++;
			buf_addr += xfer_size;
			buf_len -= xfer_size;
			reमुख्यder -= xfer_size;
		पूर्ण
	पूर्ण
	prev->node_addr = mdesc->list_phys;

	वापस vchan_tx_prep(&mchan->vc, &mdesc->vd, flags);

मुक्त_desc:
	mdc_desc_मुक्त(&mdesc->vd);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mdc_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
	अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा mdc_dma *mdma = mchan->mdma;
	काष्ठा mdc_tx_desc *mdesc;
	काष्ठा scatterlist *sg;
	काष्ठा mdc_hw_list_desc *curr, *prev = शून्य;
	dma_addr_t curr_phys;
	अचिन्हित पूर्णांक i;

	अगर (!sgl)
		वापस शून्य;

	अगर (!is_slave_direction(dir))
		वापस शून्य;

	अगर (mdc_check_slave_width(mchan, dir) < 0)
		वापस शून्य;

	mdesc = kzalloc(माप(*mdesc), GFP_NOWAIT);
	अगर (!mdesc)
		वापस शून्य;
	mdesc->chan = mchan;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma_addr_t buf = sg_dma_address(sg);
		माप_प्रकार buf_len = sg_dma_len(sg);

		जबतक (buf_len > 0) अणु
			माप_प्रकार xfer_size;

			curr = dma_pool_alloc(mdma->desc_pool, GFP_NOWAIT,
					      &curr_phys);
			अगर (!curr)
				जाओ मुक्त_desc;

			अगर (!prev) अणु
				mdesc->list_phys = curr_phys;
				mdesc->list = curr;
			पूर्ण अन्यथा अणु
				prev->node_addr = curr_phys;
				prev->next_desc = curr;
			पूर्ण

			xfer_size = min_t(माप_प्रकार, mdma->max_xfer_size,
					  buf_len);

			अगर (dir == DMA_MEM_TO_DEV) अणु
				mdc_list_desc_config(mchan, curr, dir, buf,
						     mchan->config.dst_addr,
						     xfer_size);
			पूर्ण अन्यथा अणु
				mdc_list_desc_config(mchan, curr, dir,
						     mchan->config.src_addr,
						     buf, xfer_size);
			पूर्ण

			prev = curr;

			mdesc->list_len++;
			mdesc->list_xfer_size += xfer_size;
			buf += xfer_size;
			buf_len -= xfer_size;
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&mchan->vc, &mdesc->vd, flags);

मुक्त_desc:
	mdc_desc_मुक्त(&mdesc->vd);

	वापस शून्य;
पूर्ण

अटल व्योम mdc_issue_desc(काष्ठा mdc_chan *mchan)
अणु
	काष्ठा mdc_dma *mdma = mchan->mdma;
	काष्ठा virt_dma_desc *vd;
	काष्ठा mdc_tx_desc *mdesc;
	u32 val;

	vd = vchan_next_desc(&mchan->vc);
	अगर (!vd)
		वापस;

	list_del(&vd->node);

	mdesc = to_mdc_desc(&vd->tx);
	mchan->desc = mdesc;

	dev_dbg(mdma2dev(mdma), "Issuing descriptor on channel %d\n",
		mchan->chan_nr);

	mdma->soc->enable_chan(mchan);

	val = mdc_chan_पढ़ोl(mchan, MDC_GENERAL_CONFIG);
	val |= MDC_GENERAL_CONFIG_LIST_IEN | MDC_GENERAL_CONFIG_IEN |
		MDC_GENERAL_CONFIG_LEVEL_INT | MDC_GENERAL_CONFIG_PHYSICAL_W |
		MDC_GENERAL_CONFIG_PHYSICAL_R;
	mdc_chan_ग_लिखोl(mchan, val, MDC_GENERAL_CONFIG);
	val = (mchan->thपढ़ो << MDC_READ_PORT_CONFIG_STHREAD_SHIFT) |
		(mchan->thपढ़ो << MDC_READ_PORT_CONFIG_RTHREAD_SHIFT) |
		(mchan->thपढ़ो << MDC_READ_PORT_CONFIG_WTHREAD_SHIFT);
	mdc_chan_ग_लिखोl(mchan, val, MDC_READ_PORT_CONFIG);
	mdc_chan_ग_लिखोl(mchan, mdesc->list_phys, MDC_LIST_NODE_ADDRESS);
	val = mdc_chan_पढ़ोl(mchan, MDC_CONTROL_AND_STATUS);
	val |= MDC_CONTROL_AND_STATUS_LIST_EN;
	mdc_chan_ग_लिखोl(mchan, val, MDC_CONTROL_AND_STATUS);
पूर्ण

अटल व्योम mdc_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	अगर (vchan_issue_pending(&mchan->vc) && !mchan->desc)
		mdc_issue_desc(mchan);
	spin_unlock_irqrestore(&mchan->vc.lock, flags);
पूर्ण

अटल क्रमागत dma_status mdc_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा mdc_tx_desc *mdesc;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes = 0;
	पूर्णांक ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	अगर (!txstate)
		वापस ret;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	vd = vchan_find_desc(&mchan->vc, cookie);
	अगर (vd) अणु
		mdesc = to_mdc_desc(&vd->tx);
		bytes = mdesc->list_xfer_size;
	पूर्ण अन्यथा अगर (mchan->desc && mchan->desc->vd.tx.cookie == cookie) अणु
		काष्ठा mdc_hw_list_desc *ldesc;
		u32 val1, val2, करोne, processed, residue;
		पूर्णांक i, cmds;

		mdesc = mchan->desc;

		/*
		 * Determine the number of commands that haven't been
		 * processed (handled by the IRQ handler) yet.
		 */
		करो अणु
			val1 = mdc_chan_पढ़ोl(mchan, MDC_CMDS_PROCESSED) &
				~MDC_CMDS_PROCESSED_INT_ACTIVE;
			residue = mdc_chan_पढ़ोl(mchan,
						 MDC_ACTIVE_TRANSFER_SIZE);
			val2 = mdc_chan_पढ़ोl(mchan, MDC_CMDS_PROCESSED) &
				~MDC_CMDS_PROCESSED_INT_ACTIVE;
		पूर्ण जबतक (val1 != val2);

		करोne = (val1 >> MDC_CMDS_PROCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_DONE_MASK;
		processed = (val1 >> MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK;
		cmds = (करोne - processed) %
			(MDC_CMDS_PROCESSED_CMDS_DONE_MASK + 1);

		/*
		 * If the command loaded event hasn't been processed yet, then
		 * the dअगरference above includes an extra command.
		 */
		अगर (!mdesc->cmd_loaded)
			cmds--;
		अन्यथा
			cmds += mdesc->list_cmds_करोne;

		bytes = mdesc->list_xfer_size;
		ldesc = mdesc->list;
		क्रम (i = 0; i < cmds; i++) अणु
			bytes -= ldesc->xfer_size + 1;
			ldesc = ldesc->next_desc;
		पूर्ण
		अगर (ldesc) अणु
			अगर (residue != MDC_TRANSFER_SIZE_MASK)
				bytes -= ldesc->xfer_size - residue;
			अन्यथा
				bytes -= ldesc->xfer_size + 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mchan->vc.lock, flags);

	dma_set_residue(txstate, bytes);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक mdc_get_new_events(काष्ठा mdc_chan *mchan)
अणु
	u32 val, processed, करोne1, करोne2;
	अचिन्हित पूर्णांक ret;

	val = mdc_chan_पढ़ोl(mchan, MDC_CMDS_PROCESSED);
	processed = (val >> MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT) &
				MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK;
	/*
	 * CMDS_DONE may have incremented between पढ़ोing CMDS_PROCESSED
	 * and clearing INT_ACTIVE.  Re-पढ़ो CMDS_PROCESSED to ensure we
	 * didn't miss a command completion.
	 */
	करो अणु
		val = mdc_chan_पढ़ोl(mchan, MDC_CMDS_PROCESSED);

		करोne1 = (val >> MDC_CMDS_PROCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_DONE_MASK;

		val &= ~((MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK <<
			  MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT) |
			 MDC_CMDS_PROCESSED_INT_ACTIVE);

		val |= करोne1 << MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT;

		mdc_chan_ग_लिखोl(mchan, val, MDC_CMDS_PROCESSED);

		val = mdc_chan_पढ़ोl(mchan, MDC_CMDS_PROCESSED);

		करोne2 = (val >> MDC_CMDS_PROCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_DONE_MASK;
	पूर्ण जबतक (करोne1 != करोne2);

	अगर (करोne1 >= processed)
		ret = करोne1 - processed;
	अन्यथा
		ret = ((MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK + 1) -
			processed) + करोne1;

	वापस ret;
पूर्ण

अटल पूर्णांक mdc_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&mchan->vc.lock, flags);

	mdc_chan_ग_लिखोl(mchan, MDC_CONTROL_AND_STATUS_CANCEL,
			MDC_CONTROL_AND_STATUS);

	अगर (mchan->desc) अणु
		vchan_terminate_vdesc(&mchan->desc->vd);
		mchan->desc = शून्य;
	पूर्ण
	vchan_get_all_descriptors(&mchan->vc, &head);

	mdc_get_new_events(mchan);

	spin_unlock_irqrestore(&mchan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&mchan->vc, &head);

	वापस 0;
पूर्ण

अटल व्योम mdc_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);

	vchan_synchronize(&mchan->vc);
पूर्ण

अटल पूर्णांक mdc_slave_config(काष्ठा dma_chan *chan,
			    काष्ठा dma_slave_config *config)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	mchan->config = *config;
	spin_unlock_irqrestore(&mchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mdc_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा device *dev = mdma2dev(mchan->mdma);

	वापस pm_runसमय_get_sync(dev);
पूर्ण

अटल व्योम mdc_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mdc_chan *mchan = to_mdc_chan(chan);
	काष्ठा mdc_dma *mdma = mchan->mdma;
	काष्ठा device *dev = mdma2dev(mdma);

	mdc_terminate_all(chan);
	mdma->soc->disable_chan(mchan);
	pm_runसमय_put(dev);
पूर्ण

अटल irqवापस_t mdc_chan_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mdc_chan *mchan = (काष्ठा mdc_chan *)dev_id;
	काष्ठा mdc_tx_desc *mdesc;
	अचिन्हित पूर्णांक i, new_events;

	spin_lock(&mchan->vc.lock);

	dev_dbg(mdma2dev(mchan->mdma), "IRQ on channel %d\n", mchan->chan_nr);

	new_events = mdc_get_new_events(mchan);

	अगर (!new_events)
		जाओ out;

	mdesc = mchan->desc;
	अगर (!mdesc) अणु
		dev_warn(mdma2dev(mchan->mdma),
			 "IRQ with no active descriptor on channel %d\n",
			 mchan->chan_nr);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < new_events; i++) अणु
		/*
		 * The first पूर्णांकerrupt in a transfer indicates that the
		 * command list has been loaded, not that a command has
		 * been completed.
		 */
		अगर (!mdesc->cmd_loaded) अणु
			mdesc->cmd_loaded = true;
			जारी;
		पूर्ण

		mdesc->list_cmds_करोne++;
		अगर (mdesc->cyclic) अणु
			mdesc->list_cmds_करोne %= mdesc->list_len;
			अगर (mdesc->list_cmds_करोne % mdesc->list_period_len == 0)
				vchan_cyclic_callback(&mdesc->vd);
		पूर्ण अन्यथा अगर (mdesc->list_cmds_करोne == mdesc->list_len) अणु
			mchan->desc = शून्य;
			vchan_cookie_complete(&mdesc->vd);
			mdc_issue_desc(mchan);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&mchan->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा dma_chan *mdc_of_xlate(काष्ठा of_phandle_args *dma_spec,
				     काष्ठा of_dma *ofdma)
अणु
	काष्ठा mdc_dma *mdma = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;

	अगर (dma_spec->args_count != 3)
		वापस शून्य;

	list_क्रम_each_entry(chan, &mdma->dma_dev.channels, device_node) अणु
		काष्ठा mdc_chan *mchan = to_mdc_chan(chan);

		अगर (!(dma_spec->args[1] & BIT(mchan->chan_nr)))
			जारी;
		अगर (dma_get_slave_channel(chan)) अणु
			mchan->periph = dma_spec->args[0];
			mchan->thपढ़ो = dma_spec->args[2];
			वापस chan;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा PISTACHIO_CR_PERIPH_DMA_ROUTE(ch)	(0x120 + 0x4 * ((ch) / 4))
#घोषणा PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(ch) (8 * ((ch) % 4))
#घोषणा PISTACHIO_CR_PERIPH_DMA_ROUTE_MASK	0x3f

अटल व्योम pistachio_mdc_enable_chan(काष्ठा mdc_chan *mchan)
अणु
	काष्ठा mdc_dma *mdma = mchan->mdma;

	regmap_update_bits(mdma->periph_regs,
			   PISTACHIO_CR_PERIPH_DMA_ROUTE(mchan->chan_nr),
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_MASK <<
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(mchan->chan_nr),
			   mchan->periph <<
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(mchan->chan_nr));
पूर्ण

अटल व्योम pistachio_mdc_disable_chan(काष्ठा mdc_chan *mchan)
अणु
	काष्ठा mdc_dma *mdma = mchan->mdma;

	regmap_update_bits(mdma->periph_regs,
			   PISTACHIO_CR_PERIPH_DMA_ROUTE(mchan->chan_nr),
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_MASK <<
			   PISTACHIO_CR_PERIPH_DMA_ROUTE_SHIFT(mchan->chan_nr),
			   0);
पूर्ण

अटल स्थिर काष्ठा mdc_dma_soc_data pistachio_mdc_data = अणु
	.enable_chan = pistachio_mdc_enable_chan,
	.disable_chan = pistachio_mdc_disable_chan,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mdc_dma_of_match[] = अणु
	अणु .compatible = "img,pistachio-mdc-dma", .data = &pistachio_mdc_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mdc_dma_of_match);

अटल पूर्णांक img_mdc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mdc_dma *mdma = dev_get_drvdata(dev);

	clk_disable_unprepare(mdma->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक img_mdc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mdc_dma *mdma = dev_get_drvdata(dev);

	वापस clk_prepare_enable(mdma->clk);
पूर्ण

अटल पूर्णांक mdc_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdc_dma *mdma;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	u32 val;
	पूर्णांक ret;

	mdma = devm_kzalloc(&pdev->dev, माप(*mdma), GFP_KERNEL);
	अगर (!mdma)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, mdma);

	mdma->soc = of_device_get_match_data(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mdma->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mdma->regs))
		वापस PTR_ERR(mdma->regs);

	mdma->periph_regs = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							    "img,cr-periph");
	अगर (IS_ERR(mdma->periph_regs))
		वापस PTR_ERR(mdma->periph_regs);

	mdma->clk = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(mdma->clk))
		वापस PTR_ERR(mdma->clk);

	dma_cap_zero(mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PRIVATE, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_MEMCPY, mdma->dma_dev.cap_mask);

	val = mdc_पढ़ोl(mdma, MDC_GLOBAL_CONFIG_A);
	mdma->nr_channels = (val >> MDC_GLOBAL_CONFIG_A_DMA_CONTEXTS_SHIFT) &
		MDC_GLOBAL_CONFIG_A_DMA_CONTEXTS_MASK;
	mdma->nr_thपढ़ोs =
		1 << ((val >> MDC_GLOBAL_CONFIG_A_THREAD_ID_WIDTH_SHIFT) &
		      MDC_GLOBAL_CONFIG_A_THREAD_ID_WIDTH_MASK);
	mdma->bus_width =
		(1 << ((val >> MDC_GLOBAL_CONFIG_A_SYS_DAT_WIDTH_SHIFT) &
		       MDC_GLOBAL_CONFIG_A_SYS_DAT_WIDTH_MASK)) / 8;
	/*
	 * Although transfer sizes of up to MDC_TRANSFER_SIZE_MASK + 1 bytes
	 * are supported, this makes it possible क्रम the value reported in
	 * MDC_ACTIVE_TRANSFER_SIZE to be ambiguous - an active transfer size
	 * of MDC_TRANSFER_SIZE_MASK may indicate either that 0 bytes or
	 * MDC_TRANSFER_SIZE_MASK + 1 bytes are reमुख्यing.  To eliminate this
	 * ambiguity, restrict transfer sizes to one bus-width less than the
	 * actual maximum.
	 */
	mdma->max_xfer_size = MDC_TRANSFER_SIZE_MASK + 1 - mdma->bus_width;

	of_property_पढ़ो_u32(pdev->dev.of_node, "dma-channels",
			     &mdma->nr_channels);
	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "img,max-burst-multiplier",
				   &mdma->max_burst_mult);
	अगर (ret)
		वापस ret;

	mdma->dma_dev.dev = &pdev->dev;
	mdma->dma_dev.device_prep_slave_sg = mdc_prep_slave_sg;
	mdma->dma_dev.device_prep_dma_cyclic = mdc_prep_dma_cyclic;
	mdma->dma_dev.device_prep_dma_स_नकल = mdc_prep_dma_स_नकल;
	mdma->dma_dev.device_alloc_chan_resources = mdc_alloc_chan_resources;
	mdma->dma_dev.device_मुक्त_chan_resources = mdc_मुक्त_chan_resources;
	mdma->dma_dev.device_tx_status = mdc_tx_status;
	mdma->dma_dev.device_issue_pending = mdc_issue_pending;
	mdma->dma_dev.device_terminate_all = mdc_terminate_all;
	mdma->dma_dev.device_synchronize = mdc_synchronize;
	mdma->dma_dev.device_config = mdc_slave_config;

	mdma->dma_dev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mdma->dma_dev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	क्रम (i = 1; i <= mdma->bus_width; i <<= 1) अणु
		mdma->dma_dev.src_addr_widths |= BIT(i);
		mdma->dma_dev.dst_addr_widths |= BIT(i);
	पूर्ण

	INIT_LIST_HEAD(&mdma->dma_dev.channels);
	क्रम (i = 0; i < mdma->nr_channels; i++) अणु
		काष्ठा mdc_chan *mchan = &mdma->channels[i];

		mchan->mdma = mdma;
		mchan->chan_nr = i;
		mchan->irq = platक्रमm_get_irq(pdev, i);
		अगर (mchan->irq < 0)
			वापस mchan->irq;

		ret = devm_request_irq(&pdev->dev, mchan->irq, mdc_chan_irq,
				       IRQ_TYPE_LEVEL_HIGH,
				       dev_name(&pdev->dev), mchan);
		अगर (ret < 0)
			वापस ret;

		mchan->vc.desc_मुक्त = mdc_desc_मुक्त;
		vchan_init(&mchan->vc, &mdma->dma_dev);
	पूर्ण

	mdma->desc_pool = dmam_pool_create(dev_name(&pdev->dev), &pdev->dev,
					   माप(काष्ठा mdc_hw_list_desc),
					   4, 0);
	अगर (!mdma->desc_pool)
		वापस -ENOMEM;

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_mdc_runसमय_resume(&pdev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&mdma->dma_dev);
	अगर (ret)
		जाओ suspend;

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, mdc_of_xlate, mdma);
	अगर (ret)
		जाओ unरेजिस्टर;

	dev_info(&pdev->dev, "MDC with %u channels and %u threads\n",
		 mdma->nr_channels, mdma->nr_thपढ़ोs);

	वापस 0;

unरेजिस्टर:
	dma_async_device_unरेजिस्टर(&mdma->dma_dev);
suspend:
	अगर (!pm_runसमय_enabled(&pdev->dev))
		img_mdc_runसमय_suspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mdc_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdc_dma *mdma = platक्रमm_get_drvdata(pdev);
	काष्ठा mdc_chan *mchan, *next;

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&mdma->dma_dev);

	list_क्रम_each_entry_safe(mchan, next, &mdma->dma_dev.channels,
				 vc.chan.device_node) अणु
		list_del(&mchan->vc.chan.device_node);

		devm_मुक्त_irq(&pdev->dev, mchan->irq, mchan);

		tasklet_समाप्त(&mchan->vc.task);
	पूर्ण

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_mdc_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_mdc_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा mdc_dma *mdma = dev_get_drvdata(dev);
	पूर्णांक i;

	/* Check that all channels are idle */
	क्रम (i = 0; i < mdma->nr_channels; i++) अणु
		काष्ठा mdc_chan *mchan = &mdma->channels[i];

		अगर (unlikely(mchan->desc))
			वापस -EBUSY;
	पूर्ण

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक img_mdc_resume_early(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops img_mdc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_mdc_runसमय_suspend,
			   img_mdc_runसमय_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(img_mdc_suspend_late,
				     img_mdc_resume_early)
पूर्ण;

अटल काष्ठा platक्रमm_driver mdc_dma_driver = अणु
	.driver = अणु
		.name = "img-mdc-dma",
		.pm = &img_mdc_pm_ops,
		.of_match_table = of_match_ptr(mdc_dma_of_match),
	पूर्ण,
	.probe = mdc_dma_probe,
	.हटाओ = mdc_dma_हटाओ,
पूर्ण;
module_platक्रमm_driver(mdc_dma_driver);

MODULE_DESCRIPTION("IMG Multi-threaded DMA Controller (MDC) driver");
MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_LICENSE("GPL v2");
