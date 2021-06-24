<शैली गुरु>
/*
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *		Sandeep Nair <sandeep_n@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ti/knav_dma.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#घोषणा REG_MASK		0xffffffff

#घोषणा DMA_LOOPBACK		BIT(31)
#घोषणा DMA_ENABLE		BIT(31)
#घोषणा DMA_TEARDOWN		BIT(30)

#घोषणा DMA_TX_FILT_PSWORDS	BIT(29)
#घोषणा DMA_TX_FILT_EINFO	BIT(30)
#घोषणा DMA_TX_PRIO_SHIFT	0
#घोषणा DMA_RX_PRIO_SHIFT	16
#घोषणा DMA_PRIO_MASK		GENMASK(3, 0)
#घोषणा DMA_PRIO_DEFAULT	0
#घोषणा DMA_RX_TIMEOUT_DEFAULT	17500 /* cycles */
#घोषणा DMA_RX_TIMEOUT_MASK	GENMASK(16, 0)
#घोषणा DMA_RX_TIMEOUT_SHIFT	0

#घोषणा CHAN_HAS_EPIB		BIT(30)
#घोषणा CHAN_HAS_PSINFO		BIT(29)
#घोषणा CHAN_ERR_RETRY		BIT(28)
#घोषणा CHAN_PSINFO_AT_SOP	BIT(25)
#घोषणा CHAN_SOP_OFF_SHIFT	16
#घोषणा CHAN_SOP_OFF_MASK	GENMASK(9, 0)
#घोषणा DESC_TYPE_SHIFT		26
#घोषणा DESC_TYPE_MASK		GENMASK(2, 0)

/*
 * QMGR & QNUM together make up 14 bits with QMGR as the 2 MSb's in the logical
 * navigator cloud mapping scheme.
 * using the 14bit physical queue numbers directly maps पूर्णांकo this scheme.
 */
#घोषणा CHAN_QNUM_MASK		GENMASK(14, 0)
#घोषणा DMA_MAX_QMS		4
#घोषणा DMA_TIMEOUT		1	/* msecs */
#घोषणा DMA_INVALID_ID		0xffff

काष्ठा reg_global अणु
	u32	revision;
	u32	perf_control;
	u32	emulation_control;
	u32	priority_control;
	u32	qm_base_address[DMA_MAX_QMS];
पूर्ण;

काष्ठा reg_chan अणु
	u32	control;
	u32	mode;
	u32	__rsvd[6];
पूर्ण;

काष्ठा reg_tx_sched अणु
	u32	prio;
पूर्ण;

काष्ठा reg_rx_flow अणु
	u32	control;
	u32	tags;
	u32	tag_sel;
	u32	fdq_sel[2];
	u32	thresh[3];
पूर्ण;

काष्ठा knav_dma_pool_device अणु
	काष्ठा device			*dev;
	काष्ठा list_head		list;
पूर्ण;

काष्ठा knav_dma_device अणु
	bool				loopback, enable_all;
	अचिन्हित			tx_priority, rx_priority, rx_समयout;
	अचिन्हित			logical_queue_managers;
	अचिन्हित			qm_base_address[DMA_MAX_QMS];
	काष्ठा reg_global __iomem	*reg_global;
	काष्ठा reg_chan __iomem		*reg_tx_chan;
	काष्ठा reg_rx_flow __iomem	*reg_rx_flow;
	काष्ठा reg_chan __iomem		*reg_rx_chan;
	काष्ठा reg_tx_sched __iomem	*reg_tx_sched;
	अचिन्हित			max_rx_chan, max_tx_chan;
	अचिन्हित			max_rx_flow;
	अक्षर				name[32];
	atomic_t			ref_count;
	काष्ठा list_head		list;
	काष्ठा list_head		chan_list;
	spinlock_t			lock;
पूर्ण;

काष्ठा knav_dma_chan अणु
	क्रमागत dma_transfer_direction	direction;
	काष्ठा knav_dma_device		*dma;
	atomic_t			ref_count;

	/* रेजिस्टरs */
	काष्ठा reg_chan __iomem		*reg_chan;
	काष्ठा reg_tx_sched __iomem	*reg_tx_sched;
	काष्ठा reg_rx_flow __iomem	*reg_rx_flow;

	/* configuration stuff */
	अचिन्हित			channel, flow;
	काष्ठा knav_dma_cfg		cfg;
	काष्ठा list_head		list;
	spinlock_t			lock;
पूर्ण;

#घोषणा chan_number(ch)	((ch->direction == DMA_MEM_TO_DEV) ? \
			ch->channel : ch->flow)

अटल काष्ठा knav_dma_pool_device *kdev;

अटल bool device_पढ़ोy;
bool knav_dma_device_पढ़ोy(व्योम)
अणु
	वापस device_पढ़ोy;
पूर्ण
EXPORT_SYMBOL_GPL(knav_dma_device_पढ़ोy);

अटल bool check_config(काष्ठा knav_dma_chan *chan, काष्ठा knav_dma_cfg *cfg)
अणु
	अगर (!स_भेद(&chan->cfg, cfg, माप(*cfg)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक chan_start(काष्ठा knav_dma_chan *chan,
			काष्ठा knav_dma_cfg *cfg)
अणु
	u32 v = 0;

	spin_lock(&chan->lock);
	अगर ((chan->direction == DMA_MEM_TO_DEV) && chan->reg_chan) अणु
		अगर (cfg->u.tx.filt_pswords)
			v |= DMA_TX_FILT_PSWORDS;
		अगर (cfg->u.tx.filt_einfo)
			v |= DMA_TX_FILT_EINFO;
		ग_लिखोl_relaxed(v, &chan->reg_chan->mode);
		ग_लिखोl_relaxed(DMA_ENABLE, &chan->reg_chan->control);
	पूर्ण

	अगर (chan->reg_tx_sched)
		ग_लिखोl_relaxed(cfg->u.tx.priority, &chan->reg_tx_sched->prio);

	अगर (chan->reg_rx_flow) अणु
		v = 0;

		अगर (cfg->u.rx.einfo_present)
			v |= CHAN_HAS_EPIB;
		अगर (cfg->u.rx.psinfo_present)
			v |= CHAN_HAS_PSINFO;
		अगर (cfg->u.rx.err_mode == DMA_RETRY)
			v |= CHAN_ERR_RETRY;
		v |= (cfg->u.rx.desc_type & DESC_TYPE_MASK) << DESC_TYPE_SHIFT;
		अगर (cfg->u.rx.psinfo_at_sop)
			v |= CHAN_PSINFO_AT_SOP;
		v |= (cfg->u.rx.sop_offset & CHAN_SOP_OFF_MASK)
			<< CHAN_SOP_OFF_SHIFT;
		v |= cfg->u.rx.dst_q & CHAN_QNUM_MASK;

		ग_लिखोl_relaxed(v, &chan->reg_rx_flow->control);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->tags);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->tag_sel);

		v =  cfg->u.rx.fdq[0] << 16;
		v |=  cfg->u.rx.fdq[1] & CHAN_QNUM_MASK;
		ग_लिखोl_relaxed(v, &chan->reg_rx_flow->fdq_sel[0]);

		v =  cfg->u.rx.fdq[2] << 16;
		v |=  cfg->u.rx.fdq[3] & CHAN_QNUM_MASK;
		ग_लिखोl_relaxed(v, &chan->reg_rx_flow->fdq_sel[1]);

		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[0]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[1]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[2]);
	पूर्ण

	/* Keep a copy of the cfg */
	स_नकल(&chan->cfg, cfg, माप(*cfg));
	spin_unlock(&chan->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक chan_tearकरोwn(काष्ठा knav_dma_chan *chan)
अणु
	अचिन्हित दीर्घ end, value;

	अगर (!chan->reg_chan)
		वापस 0;

	/* indicate tearकरोwn */
	ग_लिखोl_relaxed(DMA_TEARDOWN, &chan->reg_chan->control);

	/* रुको क्रम the dma to shut itself करोwn */
	end = jअगरfies + msecs_to_jअगरfies(DMA_TIMEOUT);
	करो अणु
		value = पढ़ोl_relaxed(&chan->reg_chan->control);
		अगर ((value & DMA_ENABLE) == 0)
			अवरोध;
	पूर्ण जबतक (समय_after(end, jअगरfies));

	अगर (पढ़ोl_relaxed(&chan->reg_chan->control) & DMA_ENABLE) अणु
		dev_err(kdev->dev, "timeout waiting for teardown\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम chan_stop(काष्ठा knav_dma_chan *chan)
अणु
	spin_lock(&chan->lock);
	अगर (chan->reg_rx_flow) अणु
		/* first detach fdqs, starve out the flow */
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->fdq_sel[0]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->fdq_sel[1]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[0]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[1]);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->thresh[2]);
	पूर्ण

	/* tearकरोwn the dma channel */
	chan_tearकरोwn(chan);

	/* then disconnect the completion side */
	अगर (chan->reg_rx_flow) अणु
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->control);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->tags);
		ग_लिखोl_relaxed(0, &chan->reg_rx_flow->tag_sel);
	पूर्ण

	स_रखो(&chan->cfg, 0, माप(काष्ठा knav_dma_cfg));
	spin_unlock(&chan->lock);

	dev_dbg(kdev->dev, "channel stopped\n");
पूर्ण

अटल व्योम dma_hw_enable_all(काष्ठा knav_dma_device *dma)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dma->max_tx_chan; i++) अणु
		ग_लिखोl_relaxed(0, &dma->reg_tx_chan[i].mode);
		ग_लिखोl_relaxed(DMA_ENABLE, &dma->reg_tx_chan[i].control);
	पूर्ण
पूर्ण


अटल व्योम knav_dma_hw_init(काष्ठा knav_dma_device *dma)
अणु
	अचिन्हित v;
	पूर्णांक i;

	spin_lock(&dma->lock);
	v  = dma->loopback ? DMA_LOOPBACK : 0;
	ग_लिखोl_relaxed(v, &dma->reg_global->emulation_control);

	v = पढ़ोl_relaxed(&dma->reg_global->perf_control);
	v |= ((dma->rx_समयout & DMA_RX_TIMEOUT_MASK) << DMA_RX_TIMEOUT_SHIFT);
	ग_लिखोl_relaxed(v, &dma->reg_global->perf_control);

	v = ((dma->tx_priority << DMA_TX_PRIO_SHIFT) |
	     (dma->rx_priority << DMA_RX_PRIO_SHIFT));

	ग_लिखोl_relaxed(v, &dma->reg_global->priority_control);

	/* Always enable all Rx channels. Rx paths are managed using flows */
	क्रम (i = 0; i < dma->max_rx_chan; i++)
		ग_लिखोl_relaxed(DMA_ENABLE, &dma->reg_rx_chan[i].control);

	क्रम (i = 0; i < dma->logical_queue_managers; i++)
		ग_लिखोl_relaxed(dma->qm_base_address[i],
			       &dma->reg_global->qm_base_address[i]);
	spin_unlock(&dma->lock);
पूर्ण

अटल व्योम knav_dma_hw_destroy(काष्ठा knav_dma_device *dma)
अणु
	पूर्णांक i;
	अचिन्हित v;

	spin_lock(&dma->lock);
	v = ~DMA_ENABLE & REG_MASK;

	क्रम (i = 0; i < dma->max_rx_chan; i++)
		ग_लिखोl_relaxed(v, &dma->reg_rx_chan[i].control);

	क्रम (i = 0; i < dma->max_tx_chan; i++)
		ग_लिखोl_relaxed(v, &dma->reg_tx_chan[i].control);
	spin_unlock(&dma->lock);
पूर्ण

अटल व्योम dma_debug_show_channels(काष्ठा seq_file *s,
					काष्ठा knav_dma_chan *chan)
अणु
	पूर्णांक i;

	seq_म_लिखो(s, "\t%s %d:\t",
		((chan->direction == DMA_MEM_TO_DEV) ? "tx chan" : "rx flow"),
		chan_number(chan));

	अगर (chan->direction == DMA_MEM_TO_DEV) अणु
		seq_म_लिखो(s, "einfo - %d, pswords - %d, priority - %d\n",
			chan->cfg.u.tx.filt_einfo,
			chan->cfg.u.tx.filt_pswords,
			chan->cfg.u.tx.priority);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, "einfo - %d, psinfo - %d, desc_type - %d\n",
			chan->cfg.u.rx.einfo_present,
			chan->cfg.u.rx.psinfo_present,
			chan->cfg.u.rx.desc_type);
		seq_म_लिखो(s, "\t\t\tdst_q: [%d], thresh: %d fdq: ",
			chan->cfg.u.rx.dst_q,
			chan->cfg.u.rx.thresh);
		क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN; i++)
			seq_म_लिखो(s, "[%d]", chan->cfg.u.rx.fdq[i]);
		seq_म_लिखो(s, "\n");
	पूर्ण
पूर्ण

अटल व्योम dma_debug_show_devices(काष्ठा seq_file *s,
					काष्ठा knav_dma_device *dma)
अणु
	काष्ठा knav_dma_chan *chan;

	list_क्रम_each_entry(chan, &dma->chan_list, list) अणु
		अगर (atomic_पढ़ो(&chan->ref_count))
			dma_debug_show_channels(s, chan);
	पूर्ण
पूर्ण

अटल पूर्णांक knav_dma_debug_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा knav_dma_device *dma;

	list_क्रम_each_entry(dma, &kdev->list, list) अणु
		अगर (atomic_पढ़ो(&dma->ref_count)) अणु
			seq_म_लिखो(s, "%s : max_tx_chan: (%d), max_rx_flows: (%d)\n",
			dma->name, dma->max_tx_chan, dma->max_rx_flow);
			dma_debug_show_devices(s, dma);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(knav_dma_debug);

अटल पूर्णांक of_channel_match_helper(काष्ठा device_node *np, स्थिर अक्षर *name,
					स्थिर अक्षर **dma_instance)
अणु
	काष्ठा of_phandle_args args;
	काष्ठा device_node *dma_node;
	पूर्णांक index;

	dma_node = of_parse_phandle(np, "ti,navigator-dmas", 0);
	अगर (!dma_node)
		वापस -ENODEV;

	*dma_instance = dma_node->name;
	index = of_property_match_string(np, "ti,navigator-dma-names", name);
	अगर (index < 0) अणु
		dev_err(kdev->dev, "No 'ti,navigator-dma-names' property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_parse_phandle_with_fixed_args(np, "ti,navigator-dmas",
					1, index, &args)) अणु
		dev_err(kdev->dev, "Missing the phandle args name %s\n", name);
		वापस -ENODEV;
	पूर्ण

	अगर (args.args[0] < 0) अणु
		dev_err(kdev->dev, "Missing args for %s\n", name);
		वापस -ENODEV;
	पूर्ण

	वापस args.args[0];
पूर्ण

/**
 * knav_dma_खोलो_channel() - try to setup an exclusive slave channel
 * @dev:	poपूर्णांकer to client device काष्ठाure
 * @name:	slave channel name
 * @config:	dma configuration parameters
 *
 * Returns poपूर्णांकer to appropriate DMA channel on success or error.
 */
व्योम *knav_dma_खोलो_channel(काष्ठा device *dev, स्थिर अक्षर *name,
					काष्ठा knav_dma_cfg *config)
अणु
	काष्ठा knav_dma_chan *chan;
	काष्ठा knav_dma_device *dma;
	bool found = false;
	पूर्णांक chan_num = -1;
	स्थिर अक्षर *instance;

	अगर (!kdev) अणु
		pr_err("keystone-navigator-dma driver not registered\n");
		वापस (व्योम *)-EINVAL;
	पूर्ण

	chan_num = of_channel_match_helper(dev->of_node, name, &instance);
	अगर (chan_num < 0) अणु
		dev_err(kdev->dev, "No DMA instance with name %s\n", name);
		वापस (व्योम *)-EINVAL;
	पूर्ण

	dev_dbg(kdev->dev, "initializing %s channel %d from DMA %s\n",
		  config->direction == DMA_MEM_TO_DEV ? "transmit" :
		  config->direction == DMA_DEV_TO_MEM ? "receive"  :
		  "unknown", chan_num, instance);

	अगर (config->direction != DMA_MEM_TO_DEV &&
	    config->direction != DMA_DEV_TO_MEM) अणु
		dev_err(kdev->dev, "bad direction\n");
		वापस (व्योम *)-EINVAL;
	पूर्ण

	/* Look क्रम correct dma instance */
	list_क्रम_each_entry(dma, &kdev->list, list) अणु
		अगर (!म_भेद(dma->name, instance)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		dev_err(kdev->dev, "No DMA instance with name %s\n", instance);
		वापस (व्योम *)-EINVAL;
	पूर्ण

	/* Look क्रम correct dma channel from dma instance */
	found = false;
	list_क्रम_each_entry(chan, &dma->chan_list, list) अणु
		अगर (config->direction == DMA_MEM_TO_DEV) अणु
			अगर (chan->channel == chan_num) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chan->flow == chan_num) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		dev_err(kdev->dev, "channel %d is not in DMA %s\n",
				chan_num, instance);
		वापस (व्योम *)-EINVAL;
	पूर्ण

	अगर (atomic_पढ़ो(&chan->ref_count) >= 1) अणु
		अगर (!check_config(chan, config)) अणु
			dev_err(kdev->dev, "channel %d config miss-match\n",
				chan_num);
			वापस (व्योम *)-EINVAL;
		पूर्ण
	पूर्ण

	अगर (atomic_inc_वापस(&chan->dma->ref_count) <= 1)
		knav_dma_hw_init(chan->dma);

	अगर (atomic_inc_वापस(&chan->ref_count) <= 1)
		chan_start(chan, config);

	dev_dbg(kdev->dev, "channel %d opened from DMA %s\n",
				chan_num, instance);

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(knav_dma_खोलो_channel);

/**
 * knav_dma_बंद_channel()	- Destroy a dma channel
 *
 * @channel:	dma channel handle
 *
 */
व्योम knav_dma_बंद_channel(व्योम *channel)
अणु
	काष्ठा knav_dma_chan *chan = channel;

	अगर (!kdev) अणु
		pr_err("keystone-navigator-dma driver not registered\n");
		वापस;
	पूर्ण

	अगर (atomic_dec_वापस(&chan->ref_count) <= 0)
		chan_stop(chan);

	अगर (atomic_dec_वापस(&chan->dma->ref_count) <= 0)
		knav_dma_hw_destroy(chan->dma);

	dev_dbg(kdev->dev, "channel %d or flow %d closed from DMA %s\n",
			chan->channel, chan->flow, chan->dma->name);
पूर्ण
EXPORT_SYMBOL_GPL(knav_dma_बंद_channel);

अटल व्योम __iomem *pktdma_get_regs(काष्ठा knav_dma_device *dma,
				काष्ठा device_node *node,
				अचिन्हित index, resource_माप_प्रकार *_size)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	ret = of_address_to_resource(node, index, &res);
	अगर (ret) अणु
		dev_err(dev, "Can't translate of node(%pOFn) address for index(%d)\n",
			node, index);
		वापस ERR_PTR(ret);
	पूर्ण

	regs = devm_ioremap_resource(kdev->dev, &res);
	अगर (IS_ERR(regs))
		dev_err(dev, "Failed to map register base for index(%d) node(%pOFn)\n",
			index, node);
	अगर (_size)
		*_size = resource_size(&res);

	वापस regs;
पूर्ण

अटल पूर्णांक pktdma_init_rx_chan(काष्ठा knav_dma_chan *chan, u32 flow)
अणु
	काष्ठा knav_dma_device *dma = chan->dma;

	chan->flow = flow;
	chan->reg_rx_flow = dma->reg_rx_flow + flow;
	chan->channel = DMA_INVALID_ID;
	dev_dbg(kdev->dev, "rx flow(%d) (%p)\n", chan->flow, chan->reg_rx_flow);

	वापस 0;
पूर्ण

अटल पूर्णांक pktdma_init_tx_chan(काष्ठा knav_dma_chan *chan, u32 channel)
अणु
	काष्ठा knav_dma_device *dma = chan->dma;

	chan->channel = channel;
	chan->reg_chan = dma->reg_tx_chan + channel;
	chan->reg_tx_sched = dma->reg_tx_sched + channel;
	chan->flow = DMA_INVALID_ID;
	dev_dbg(kdev->dev, "tx channel(%d) (%p)\n", chan->channel, chan->reg_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक pktdma_init_chan(काष्ठा knav_dma_device *dma,
				क्रमागत dma_transfer_direction dir,
				अचिन्हित chan_num)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा knav_dma_chan *chan;
	पूर्णांक ret = -EINVAL;

	chan = devm_kzalloc(dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&chan->list);
	chan->dma	= dma;
	chan->direction	= DMA_TRANS_NONE;
	atomic_set(&chan->ref_count, 0);
	spin_lock_init(&chan->lock);

	अगर (dir == DMA_MEM_TO_DEV) अणु
		chan->direction = dir;
		ret = pktdma_init_tx_chan(chan, chan_num);
	पूर्ण अन्यथा अगर (dir == DMA_DEV_TO_MEM) अणु
		chan->direction = dir;
		ret = pktdma_init_rx_chan(chan, chan_num);
	पूर्ण अन्यथा अणु
		dev_err(dev, "channel(%d) direction unknown\n", chan_num);
	पूर्ण

	list_add_tail(&chan->list, &dma->chan_list);

	वापस ret;
पूर्ण

अटल पूर्णांक dma_init(काष्ठा device_node *cloud, काष्ठा device_node *dma_node)
अणु
	अचिन्हित max_tx_chan, max_rx_chan, max_rx_flow, max_tx_sched;
	काष्ठा device_node *node = dma_node;
	काष्ठा knav_dma_device *dma;
	पूर्णांक ret, len, num_chan = 0;
	resource_माप_प्रकार size;
	u32 समयout;
	u32 i;

	dma = devm_kzalloc(kdev->dev, माप(*dma), GFP_KERNEL);
	अगर (!dma) अणु
		dev_err(kdev->dev, "could not allocate driver mem\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&dma->list);
	INIT_LIST_HEAD(&dma->chan_list);

	अगर (!of_find_property(cloud, "ti,navigator-cloud-address", &len)) अणु
		dev_err(kdev->dev, "unspecified navigator cloud addresses\n");
		वापस -ENODEV;
	पूर्ण

	dma->logical_queue_managers = len / माप(u32);
	अगर (dma->logical_queue_managers > DMA_MAX_QMS) अणु
		dev_warn(kdev->dev, "too many queue mgrs(>%d) rest ignored\n",
			 dma->logical_queue_managers);
		dma->logical_queue_managers = DMA_MAX_QMS;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(cloud, "ti,navigator-cloud-address",
					dma->qm_base_address,
					dma->logical_queue_managers);
	अगर (ret) अणु
		dev_err(kdev->dev, "invalid navigator cloud addresses\n");
		वापस -ENODEV;
	पूर्ण

	dma->reg_global	 = pktdma_get_regs(dma, node, 0, &size);
	अगर (!dma->reg_global)
		वापस -ENODEV;
	अगर (size < माप(काष्ठा reg_global)) अणु
		dev_err(kdev->dev, "bad size %pa for global regs\n", &size);
		वापस -ENODEV;
	पूर्ण

	dma->reg_tx_chan = pktdma_get_regs(dma, node, 1, &size);
	अगर (!dma->reg_tx_chan)
		वापस -ENODEV;

	max_tx_chan = size / माप(काष्ठा reg_chan);
	dma->reg_rx_chan = pktdma_get_regs(dma, node, 2, &size);
	अगर (!dma->reg_rx_chan)
		वापस -ENODEV;

	max_rx_chan = size / माप(काष्ठा reg_chan);
	dma->reg_tx_sched = pktdma_get_regs(dma, node, 3, &size);
	अगर (!dma->reg_tx_sched)
		वापस -ENODEV;

	max_tx_sched = size / माप(काष्ठा reg_tx_sched);
	dma->reg_rx_flow = pktdma_get_regs(dma, node, 4, &size);
	अगर (!dma->reg_rx_flow)
		वापस -ENODEV;

	max_rx_flow = size / माप(काष्ठा reg_rx_flow);
	dma->rx_priority = DMA_PRIO_DEFAULT;
	dma->tx_priority = DMA_PRIO_DEFAULT;

	dma->enable_all	= (of_get_property(node, "ti,enable-all", शून्य) != शून्य);
	dma->loopback	= (of_get_property(node, "ti,loop-back",  शून्य) != शून्य);

	ret = of_property_पढ़ो_u32(node, "ti,rx-retry-timeout", &समयout);
	अगर (ret < 0) अणु
		dev_dbg(kdev->dev, "unspecified rx timeout using value %d\n",
			DMA_RX_TIMEOUT_DEFAULT);
		समयout = DMA_RX_TIMEOUT_DEFAULT;
	पूर्ण

	dma->rx_समयout = समयout;
	dma->max_rx_chan = max_rx_chan;
	dma->max_rx_flow = max_rx_flow;
	dma->max_tx_chan = min(max_tx_chan, max_tx_sched);
	atomic_set(&dma->ref_count, 0);
	म_नकल(dma->name, node->name);
	spin_lock_init(&dma->lock);

	क्रम (i = 0; i < dma->max_tx_chan; i++) अणु
		अगर (pktdma_init_chan(dma, DMA_MEM_TO_DEV, i) >= 0)
			num_chan++;
	पूर्ण

	क्रम (i = 0; i < dma->max_rx_flow; i++) अणु
		अगर (pktdma_init_chan(dma, DMA_DEV_TO_MEM, i) >= 0)
			num_chan++;
	पूर्ण

	list_add_tail(&dma->list, &kdev->list);

	/*
	 * For DSP software useहालs or userpace transport software, setup all
	 * the DMA hardware resources.
	 */
	अगर (dma->enable_all) अणु
		atomic_inc(&dma->ref_count);
		knav_dma_hw_init(dma);
		dma_hw_enable_all(dma);
	पूर्ण

	dev_info(kdev->dev, "DMA %s registered %d logical channels, flows %d, tx chans: %d, rx chans: %d%s\n",
		dma->name, num_chan, dma->max_rx_flow,
		dma->max_tx_chan, dma->max_rx_chan,
		dma->loopback ? ", loopback" : "");

	वापस 0;
पूर्ण

अटल पूर्णांक knav_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *child;
	पूर्णांक ret = 0;

	अगर (!node) अणु
		dev_err(&pdev->dev, "could not find device info\n");
		वापस -EINVAL;
	पूर्ण

	kdev = devm_kzalloc(dev,
			माप(काष्ठा knav_dma_pool_device), GFP_KERNEL);
	अगर (!kdev) अणु
		dev_err(dev, "could not allocate driver mem\n");
		वापस -ENOMEM;
	पूर्ण

	kdev->dev = dev;
	INIT_LIST_HEAD(&kdev->list);

	pm_runसमय_enable(kdev->dev);
	ret = pm_runसमय_get_sync(kdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(kdev->dev);
		dev_err(kdev->dev, "unable to enable pktdma, err %d\n", ret);
		जाओ err_pm_disable;
	पूर्ण

	/* Initialise all packet dmas */
	क्रम_each_child_of_node(node, child) अणु
		ret = dma_init(node, child);
		अगर (ret) अणु
			of_node_put(child);
			dev_err(&pdev->dev, "init failed with %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (list_empty(&kdev->list)) अणु
		dev_err(dev, "no valid dma instance\n");
		ret = -ENODEV;
		जाओ err_put_sync;
	पूर्ण

	debugfs_create_file("knav_dma", S_IFREG | S_IRUGO, शून्य, शून्य,
			    &knav_dma_debug_fops);

	device_पढ़ोy = true;
	वापस ret;

err_put_sync:
	pm_runसमय_put_sync(kdev->dev);
err_pm_disable:
	pm_runसमय_disable(kdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक knav_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा knav_dma_device *dma;

	list_क्रम_each_entry(dma, &kdev->list, list) अणु
		अगर (atomic_dec_वापस(&dma->ref_count) == 0)
			knav_dma_hw_destroy(dma);
	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "ti,keystone-navigator-dma", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_match);

अटल काष्ठा platक्रमm_driver knav_dma_driver = अणु
	.probe	= knav_dma_probe,
	.हटाओ	= knav_dma_हटाओ,
	.driver = अणु
		.name		= "keystone-navigator-dma",
		.of_match_table	= of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(knav_dma_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI Keystone Navigator Packet DMA driver");
MODULE_AUTHOR("Sandeep Nair <sandeep_n@ti.com>");
MODULE_AUTHOR("Santosh Shilimkar <santosh.shilimkar@ti.com>");
