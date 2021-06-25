<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * S3C24XX DMA handling
 *
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * based on amba-pl08x.c
 *
 * Copyright (c) 2006 ARM Ltd.
 * Copyright (c) 2010 ST-Ericsson SA
 *
 * Author: Peter Pearse <peter.pearse@arm.com>
 * Author: Linus Walleij <linus.walleij@stericsson.com>
 *
 * The DMA controllers in S3C24XX SoCs have a varying number of DMA संकेतs
 * that can be routed to any of the 4 to 8 hardware-channels.
 *
 * Thereक्रमe on these DMA controllers the number of channels
 * and the number of incoming DMA संकेतs are two totally dअगरferent things.
 * It is usually not possible to theoretically handle all physical संकेतs,
 * so a multiplexing scheme with possible denial of use is necessary.
 *
 * Open items:
 * - bursts
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/dma-s3c24xx.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा MAX_DMA_CHANNELS	8

#घोषणा S3C24XX_DISRC			0x00
#घोषणा S3C24XX_DISRCC			0x04
#घोषणा S3C24XX_DISRCC_INC_INCREMENT	0
#घोषणा S3C24XX_DISRCC_INC_FIXED	BIT(0)
#घोषणा S3C24XX_DISRCC_LOC_AHB		0
#घोषणा S3C24XX_DISRCC_LOC_APB		BIT(1)

#घोषणा S3C24XX_DIDST			0x08
#घोषणा S3C24XX_DIDSTC			0x0c
#घोषणा S3C24XX_DIDSTC_INC_INCREMENT	0
#घोषणा S3C24XX_DIDSTC_INC_FIXED	BIT(0)
#घोषणा S3C24XX_DIDSTC_LOC_AHB		0
#घोषणा S3C24XX_DIDSTC_LOC_APB		BIT(1)
#घोषणा S3C24XX_DIDSTC_INT_TC0		0
#घोषणा S3C24XX_DIDSTC_INT_RELOAD	BIT(2)

#घोषणा S3C24XX_DCON			0x10

#घोषणा S3C24XX_DCON_TC_MASK		0xfffff
#घोषणा S3C24XX_DCON_DSZ_BYTE		(0 << 20)
#घोषणा S3C24XX_DCON_DSZ_HALFWORD	(1 << 20)
#घोषणा S3C24XX_DCON_DSZ_WORD		(2 << 20)
#घोषणा S3C24XX_DCON_DSZ_MASK		(3 << 20)
#घोषणा S3C24XX_DCON_DSZ_SHIFT		20
#घोषणा S3C24XX_DCON_AUTORELOAD		0
#घोषणा S3C24XX_DCON_NORELOAD		BIT(22)
#घोषणा S3C24XX_DCON_HWTRIG		BIT(23)
#घोषणा S3C24XX_DCON_HWSRC_SHIFT	24
#घोषणा S3C24XX_DCON_SERV_SINGLE	0
#घोषणा S3C24XX_DCON_SERV_WHOLE		BIT(27)
#घोषणा S3C24XX_DCON_TSZ_UNIT		0
#घोषणा S3C24XX_DCON_TSZ_BURST4		BIT(28)
#घोषणा S3C24XX_DCON_INT		BIT(29)
#घोषणा S3C24XX_DCON_SYNC_PCLK		0
#घोषणा S3C24XX_DCON_SYNC_HCLK		BIT(30)
#घोषणा S3C24XX_DCON_DEMAND		0
#घोषणा S3C24XX_DCON_HANDSHAKE		BIT(31)

#घोषणा S3C24XX_DSTAT			0x14
#घोषणा S3C24XX_DSTAT_STAT_BUSY		BIT(20)
#घोषणा S3C24XX_DSTAT_CURRTC_MASK	0xfffff

#घोषणा S3C24XX_DMASKTRIG		0x20
#घोषणा S3C24XX_DMASKTRIG_SWTRIG	BIT(0)
#घोषणा S3C24XX_DMASKTRIG_ON		BIT(1)
#घोषणा S3C24XX_DMASKTRIG_STOP		BIT(2)

#घोषणा S3C24XX_DMAREQSEL		0x24
#घोषणा S3C24XX_DMAREQSEL_HW		BIT(0)

/*
 * S3C2410, S3C2440 and S3C2442 SoCs cannot select any physical channel
 * क्रम a DMA source. Instead only specअगरic channels are valid.
 * All of these SoCs have 4 physical channels and the number of request
 * source bits is 3. Additionally we also need 1 bit to mark the channel
 * as valid.
 * Thereक्रमe we separate the chansel element of the channel data पूर्णांकo 4
 * parts of 4 bits each, to hold the inक्रमmation अगर the channel is valid
 * and the hw request source to use.
 *
 * Example:
 * SDI is valid on channels 0, 2 and 3 - with varying hw request sources.
 * For it the chansel field would look like
 *
 * ((BIT(3) | 1) << 3 * 4) | // channel 3, with request source 1
 * ((BIT(3) | 2) << 2 * 4) | // channel 2, with request source 2
 * ((BIT(3) | 2) << 0 * 4)   // channel 0, with request source 2
 */
#घोषणा S3C24XX_CHANSEL_WIDTH		4
#घोषणा S3C24XX_CHANSEL_VALID		BIT(3)
#घोषणा S3C24XX_CHANSEL_REQ_MASK	7

/*
 * काष्ठा soc_data - venकरोr-specअगरic config parameters क्रम inभागidual SoCs
 * @stride: spacing between the रेजिस्टरs of each channel
 * @has_reqsel: करोes the controller use the newer requestselection mechanism
 * @has_घड़ीs: are controllable dma-घड़ीs present
 */
काष्ठा soc_data अणु
	पूर्णांक stride;
	bool has_reqsel;
	bool has_घड़ीs;
पूर्ण;

/*
 * क्रमागत s3c24xx_dma_chan_state - holds the भव channel states
 * @S3C24XX_DMA_CHAN_IDLE: the channel is idle
 * @S3C24XX_DMA_CHAN_RUNNING: the channel has allocated a physical transport
 * channel and is running a transfer on it
 * @S3C24XX_DMA_CHAN_WAITING: the channel is रुकोing क्रम a physical transport
 * channel to become available (only pertains to स_नकल channels)
 */
क्रमागत s3c24xx_dma_chan_state अणु
	S3C24XX_DMA_CHAN_IDLE,
	S3C24XX_DMA_CHAN_RUNNING,
	S3C24XX_DMA_CHAN_WAITING,
पूर्ण;

/*
 * काष्ठा s3c24xx_sg - काष्ठाure containing data per sg
 * @src_addr: src address of sg
 * @dst_addr: dst address of sg
 * @len: transfer len in bytes
 * @node: node क्रम txd's dsg_list
 */
काष्ठा s3c24xx_sg अणु
	dma_addr_t src_addr;
	dma_addr_t dst_addr;
	माप_प्रकार len;
	काष्ठा list_head node;
पूर्ण;

/*
 * काष्ठा s3c24xx_txd - wrapper क्रम काष्ठा dma_async_tx_descriptor
 * @vd: भव DMA descriptor
 * @dsg_list: list of children sg's
 * @at: sg currently being transfered
 * @width: transfer width
 * @disrcc: value क्रम source control रेजिस्टर
 * @didstc: value क्रम destination control रेजिस्टर
 * @dcon: base value क्रम dcon रेजिस्टर
 * @cyclic: indicate cyclic transfer
 */
काष्ठा s3c24xx_txd अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा list_head dsg_list;
	काष्ठा list_head *at;
	u8 width;
	u32 disrcc;
	u32 didstc;
	u32 dcon;
	bool cyclic;
पूर्ण;

काष्ठा s3c24xx_dma_chan;

/*
 * काष्ठा s3c24xx_dma_phy - holder क्रम the physical channels
 * @id: physical index to this channel
 * @valid: करोes the channel have all required elements
 * @base: भव memory base (remapped) क्रम the this channel
 * @irq: पूर्णांकerrupt क्रम this channel
 * @clk: घड़ी क्रम this channel
 * @lock: a lock to use when altering an instance of this काष्ठा
 * @serving: भव channel currently being served by this physicalchannel
 * @host: a poपूर्णांकer to the host (पूर्णांकernal use)
 */
काष्ठा s3c24xx_dma_phy अणु
	अचिन्हित पूर्णांक			id;
	bool				valid;
	व्योम __iomem			*base;
	पूर्णांक				irq;
	काष्ठा clk			*clk;
	spinlock_t			lock;
	काष्ठा s3c24xx_dma_chan		*serving;
	काष्ठा s3c24xx_dma_engine	*host;
पूर्ण;

/*
 * काष्ठा s3c24xx_dma_chan - this काष्ठाure wraps a DMA ENGINE channel
 * @id: the id of the channel
 * @name: name of the channel
 * @vc: wrappped भव channel
 * @phy: the physical channel utilized by this channel, अगर there is one
 * @runसमय_addr: address क्रम RX/TX according to the runसमय config
 * @at: active transaction on this channel
 * @lock: a lock क्रम this channel data
 * @host: a poपूर्णांकer to the host (पूर्णांकernal use)
 * @state: whether the channel is idle, running etc
 * @slave: whether this channel is a device (slave) or क्रम स_नकल
 */
काष्ठा s3c24xx_dma_chan अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	काष्ठा virt_dma_chan vc;
	काष्ठा s3c24xx_dma_phy *phy;
	काष्ठा dma_slave_config cfg;
	काष्ठा s3c24xx_txd *at;
	काष्ठा s3c24xx_dma_engine *host;
	क्रमागत s3c24xx_dma_chan_state state;
	bool slave;
पूर्ण;

/*
 * काष्ठा s3c24xx_dma_engine - the local state holder क्रम the S3C24XX
 * @pdev: the corresponding platक्रमm device
 * @pdata: platक्रमm data passed in from the platक्रमm/machine
 * @base: भव memory base (remapped)
 * @slave: slave engine क्रम this instance
 * @स_नकल: स_नकल engine क्रम this instance
 * @phy_chans: array of data क्रम the physical channels
 */
काष्ठा s3c24xx_dma_engine अणु
	काष्ठा platक्रमm_device			*pdev;
	स्थिर काष्ठा s3c24xx_dma_platdata	*pdata;
	काष्ठा soc_data				*sdata;
	व्योम __iomem				*base;
	काष्ठा dma_device			slave;
	काष्ठा dma_device			स_नकल;
	काष्ठा s3c24xx_dma_phy			*phy_chans;
पूर्ण;

/*
 * Physical channel handling
 */

/*
 * Check whether a certain channel is busy or not.
 */
अटल पूर्णांक s3c24xx_dma_phy_busy(काष्ठा s3c24xx_dma_phy *phy)
अणु
	अचिन्हित पूर्णांक val = पढ़ोl(phy->base + S3C24XX_DSTAT);
	वापस val & S3C24XX_DSTAT_STAT_BUSY;
पूर्ण

अटल bool s3c24xx_dma_phy_valid(काष्ठा s3c24xx_dma_chan *s3cchan,
				  काष्ठा s3c24xx_dma_phy *phy)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = s3cdma->pdata;
	काष्ठा s3c24xx_dma_channel *cdata = &pdata->channels[s3cchan->id];
	पूर्णांक phyvalid;

	/* every phy is valid क्रम memcopy channels */
	अगर (!s3cchan->slave)
		वापस true;

	/* On newer variants all phys can be used क्रम all भव channels */
	अगर (s3cdma->sdata->has_reqsel)
		वापस true;

	phyvalid = (cdata->chansel >> (phy->id * S3C24XX_CHANSEL_WIDTH));
	वापस (phyvalid & S3C24XX_CHANSEL_VALID) ? true : false;
पूर्ण

/*
 * Allocate a physical channel क्रम a भव channel
 *
 * Try to locate a physical channel to be used क्रम this transfer. If all
 * are taken वापस शून्य and the requester will have to cope by using
 * some fallback PIO mode or retrying later.
 */
अटल
काष्ठा s3c24xx_dma_phy *s3c24xx_dma_get_phy(काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	काष्ठा s3c24xx_dma_phy *phy = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < s3cdma->pdata->num_phy_channels; i++) अणु
		phy = &s3cdma->phy_chans[i];

		अगर (!phy->valid)
			जारी;

		अगर (!s3c24xx_dma_phy_valid(s3cchan, phy))
			जारी;

		spin_lock_irqsave(&phy->lock, flags);

		अगर (!phy->serving) अणु
			phy->serving = s3cchan;
			spin_unlock_irqrestore(&phy->lock, flags);
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&phy->lock, flags);
	पूर्ण

	/* No physical channel available, cope with it */
	अगर (i == s3cdma->pdata->num_phy_channels) अणु
		dev_warn(&s3cdma->pdev->dev, "no phy channel available\n");
		वापस शून्य;
	पूर्ण

	/* start the phy घड़ी */
	अगर (s3cdma->sdata->has_घड़ीs) अणु
		ret = clk_enable(phy->clk);
		अगर (ret) अणु
			dev_err(&s3cdma->pdev->dev, "could not enable clock for channel %d, err %d\n",
				phy->id, ret);
			phy->serving = शून्य;
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस phy;
पूर्ण

/*
 * Mark the physical channel as मुक्त.
 *
 * This drops the link between the physical and भव channel.
 */
अटल अंतरभूत व्योम s3c24xx_dma_put_phy(काष्ठा s3c24xx_dma_phy *phy)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = phy->host;

	अगर (s3cdma->sdata->has_घड़ीs)
		clk_disable(phy->clk);

	phy->serving = शून्य;
पूर्ण

/*
 * Stops the channel by writing the stop bit.
 * This should not be used क्रम an on-going transfer, but as a method of
 * shutting करोwn a channel (eg, when it's no दीर्घer used) or terminating a
 * transfer.
 */
अटल व्योम s3c24xx_dma_terminate_phy(काष्ठा s3c24xx_dma_phy *phy)
अणु
	ग_लिखोl(S3C24XX_DMASKTRIG_STOP, phy->base + S3C24XX_DMASKTRIG);
पूर्ण

/*
 * Virtual channel handling
 */

अटल अंतरभूत
काष्ठा s3c24xx_dma_chan *to_s3c24xx_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा s3c24xx_dma_chan, vc.chan);
पूर्ण

अटल u32 s3c24xx_dma_getbytes_chan(काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_phy *phy = s3cchan->phy;
	काष्ठा s3c24xx_txd *txd = s3cchan->at;
	u32 tc = पढ़ोl(phy->base + S3C24XX_DSTAT) & S3C24XX_DSTAT_CURRTC_MASK;

	वापस tc * txd->width;
पूर्ण

अटल पूर्णांक s3c24xx_dma_set_runसमय_config(काष्ठा dma_chan *chan,
				  काष्ठा dma_slave_config *config)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* Reject definitely invalid configurations */
	अगर (config->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    config->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस -EINVAL;

	spin_lock_irqsave(&s3cchan->vc.lock, flags);

	अगर (!s3cchan->slave) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	s3cchan->cfg = *config;

out:
	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);
	वापस ret;
पूर्ण

/*
 * Transfer handling
 */

अटल अंतरभूत
काष्ठा s3c24xx_txd *to_s3c24xx_txd(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा s3c24xx_txd, vd.tx);
पूर्ण

अटल काष्ठा s3c24xx_txd *s3c24xx_dma_get_txd(व्योम)
अणु
	काष्ठा s3c24xx_txd *txd = kzalloc(माप(*txd), GFP_NOWAIT);

	अगर (txd) अणु
		INIT_LIST_HEAD(&txd->dsg_list);
		txd->dcon = S3C24XX_DCON_INT | S3C24XX_DCON_NORELOAD;
	पूर्ण

	वापस txd;
पूर्ण

अटल व्योम s3c24xx_dma_मुक्त_txd(काष्ठा s3c24xx_txd *txd)
अणु
	काष्ठा s3c24xx_sg *dsg, *_dsg;

	list_क्रम_each_entry_safe(dsg, _dsg, &txd->dsg_list, node) अणु
		list_del(&dsg->node);
		kमुक्त(dsg);
	पूर्ण

	kमुक्त(txd);
पूर्ण

अटल व्योम s3c24xx_dma_start_next_sg(काष्ठा s3c24xx_dma_chan *s3cchan,
				       काष्ठा s3c24xx_txd *txd)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	काष्ठा s3c24xx_dma_phy *phy = s3cchan->phy;
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = s3cdma->pdata;
	काष्ठा s3c24xx_sg *dsg = list_entry(txd->at, काष्ठा s3c24xx_sg, node);
	u32 dcon = txd->dcon;
	u32 val;

	/* transfer-size and -count from len and width */
	चयन (txd->width) अणु
	हाल 1:
		dcon |= S3C24XX_DCON_DSZ_BYTE | dsg->len;
		अवरोध;
	हाल 2:
		dcon |= S3C24XX_DCON_DSZ_HALFWORD | (dsg->len / 2);
		अवरोध;
	हाल 4:
		dcon |= S3C24XX_DCON_DSZ_WORD | (dsg->len / 4);
		अवरोध;
	पूर्ण

	अगर (s3cchan->slave) अणु
		काष्ठा s3c24xx_dma_channel *cdata =
					&pdata->channels[s3cchan->id];

		अगर (s3cdma->sdata->has_reqsel) अणु
			ग_लिखोl_relaxed((cdata->chansel << 1) |
							S3C24XX_DMAREQSEL_HW,
					phy->base + S3C24XX_DMAREQSEL);
		पूर्ण अन्यथा अणु
			पूर्णांक csel = cdata->chansel >> (phy->id *
							S3C24XX_CHANSEL_WIDTH);

			csel &= S3C24XX_CHANSEL_REQ_MASK;
			dcon |= csel << S3C24XX_DCON_HWSRC_SHIFT;
			dcon |= S3C24XX_DCON_HWTRIG;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (s3cdma->sdata->has_reqsel)
			ग_लिखोl_relaxed(0, phy->base + S3C24XX_DMAREQSEL);
	पूर्ण

	ग_लिखोl_relaxed(dsg->src_addr, phy->base + S3C24XX_DISRC);
	ग_लिखोl_relaxed(txd->disrcc, phy->base + S3C24XX_DISRCC);
	ग_लिखोl_relaxed(dsg->dst_addr, phy->base + S3C24XX_DIDST);
	ग_लिखोl_relaxed(txd->didstc, phy->base + S3C24XX_DIDSTC);
	ग_लिखोl_relaxed(dcon, phy->base + S3C24XX_DCON);

	val = पढ़ोl_relaxed(phy->base + S3C24XX_DMASKTRIG);
	val &= ~S3C24XX_DMASKTRIG_STOP;
	val |= S3C24XX_DMASKTRIG_ON;

	/* trigger the dma operation क्रम स_नकल transfers */
	अगर (!s3cchan->slave)
		val |= S3C24XX_DMASKTRIG_SWTRIG;

	ग_लिखोl(val, phy->base + S3C24XX_DMASKTRIG);
पूर्ण

/*
 * Set the initial DMA रेजिस्टर values and start first sg.
 */
अटल व्योम s3c24xx_dma_start_next_txd(काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_phy *phy = s3cchan->phy;
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&s3cchan->vc);
	काष्ठा s3c24xx_txd *txd = to_s3c24xx_txd(&vd->tx);

	list_del(&txd->vd.node);

	s3cchan->at = txd;

	/* Wait क्रम channel inactive */
	जबतक (s3c24xx_dma_phy_busy(phy))
		cpu_relax();

	/* poपूर्णांक to the first element of the sg list */
	txd->at = txd->dsg_list.next;
	s3c24xx_dma_start_next_sg(s3cchan, txd);
पूर्ण

/*
 * Try to allocate a physical channel.  When successful, assign it to
 * this भव channel, and initiate the next descriptor.  The
 * भव channel lock must be held at this poपूर्णांक.
 */
अटल व्योम s3c24xx_dma_phy_alloc_and_start(काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	काष्ठा s3c24xx_dma_phy *phy;

	phy = s3c24xx_dma_get_phy(s3cchan);
	अगर (!phy) अणु
		dev_dbg(&s3cdma->pdev->dev, "no physical channel available for xfer on %s\n",
			s3cchan->name);
		s3cchan->state = S3C24XX_DMA_CHAN_WAITING;
		वापस;
	पूर्ण

	dev_dbg(&s3cdma->pdev->dev, "allocated physical channel %d for xfer on %s\n",
		phy->id, s3cchan->name);

	s3cchan->phy = phy;
	s3cchan->state = S3C24XX_DMA_CHAN_RUNNING;

	s3c24xx_dma_start_next_txd(s3cchan);
पूर्ण

अटल व्योम s3c24xx_dma_phy_reassign_start(काष्ठा s3c24xx_dma_phy *phy,
	काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;

	dev_dbg(&s3cdma->pdev->dev, "reassigned physical channel %d for xfer on %s\n",
		phy->id, s3cchan->name);

	/*
	 * We करो this without taking the lock; we're really only concerned
	 * about whether this poपूर्णांकer is शून्य or not, and we're guaranteed
	 * that this will only be called when it _alपढ़ोy_ is non-शून्य.
	 */
	phy->serving = s3cchan;
	s3cchan->phy = phy;
	s3cchan->state = S3C24XX_DMA_CHAN_RUNNING;
	s3c24xx_dma_start_next_txd(s3cchan);
पूर्ण

/*
 * Free a physical DMA channel, potentially पुनः_स्मृतिating it to another
 * भव channel अगर we have any pending.
 */
अटल व्योम s3c24xx_dma_phy_मुक्त(काष्ठा s3c24xx_dma_chan *s3cchan)
अणु
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	काष्ठा s3c24xx_dma_chan *p, *next;

retry:
	next = शून्य;

	/* Find a रुकोing भव channel क्रम the next transfer. */
	list_क्रम_each_entry(p, &s3cdma->स_नकल.channels, vc.chan.device_node)
		अगर (p->state == S3C24XX_DMA_CHAN_WAITING) अणु
			next = p;
			अवरोध;
		पूर्ण

	अगर (!next) अणु
		list_क्रम_each_entry(p, &s3cdma->slave.channels,
				    vc.chan.device_node)
			अगर (p->state == S3C24XX_DMA_CHAN_WAITING &&
				      s3c24xx_dma_phy_valid(p, s3cchan->phy)) अणु
				next = p;
				अवरोध;
			पूर्ण
	पूर्ण

	/* Ensure that the physical channel is stopped */
	s3c24xx_dma_terminate_phy(s3cchan->phy);

	अगर (next) अणु
		bool success;

		/*
		 * Eww.  We know this isn't going to deadlock
		 * but lockdep probably करोesn't.
		 */
		spin_lock(&next->vc.lock);
		/* Re-check the state now that we have the lock */
		success = next->state == S3C24XX_DMA_CHAN_WAITING;
		अगर (success)
			s3c24xx_dma_phy_reassign_start(s3cchan->phy, next);
		spin_unlock(&next->vc.lock);

		/* If the state changed, try to find another channel */
		अगर (!success)
			जाओ retry;
	पूर्ण अन्यथा अणु
		/* No more jobs, so मुक्त up the physical channel */
		s3c24xx_dma_put_phy(s3cchan->phy);
	पूर्ण

	s3cchan->phy = शून्य;
	s3cchan->state = S3C24XX_DMA_CHAN_IDLE;
पूर्ण

अटल व्योम s3c24xx_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा s3c24xx_txd *txd = to_s3c24xx_txd(&vd->tx);
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(vd->tx.chan);

	अगर (!s3cchan->slave)
		dma_descriptor_unmap(&vd->tx);

	s3c24xx_dma_मुक्त_txd(txd);
पूर्ण

अटल irqवापस_t s3c24xx_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा s3c24xx_dma_phy *phy = data;
	काष्ठा s3c24xx_dma_chan *s3cchan = phy->serving;
	काष्ठा s3c24xx_txd *txd;

	dev_dbg(&phy->host->pdev->dev, "interrupt on channel %d\n", phy->id);

	/*
	 * Interrupts happen to notअगरy the completion of a transfer and the
	 * channel should have moved पूर्णांकo its stop state alपढ़ोy on its own.
	 * Thereक्रमe पूर्णांकerrupts on channels not bound to a भव channel
	 * should never happen. Nevertheless send a terminate command to the
	 * channel अगर the unlikely हाल happens.
	 */
	अगर (unlikely(!s3cchan)) अणु
		dev_err(&phy->host->pdev->dev, "interrupt on unused channel %d\n",
			phy->id);

		s3c24xx_dma_terminate_phy(phy);

		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&s3cchan->vc.lock);
	txd = s3cchan->at;
	अगर (txd) अणु
		/* when more sg's are in this txd, start the next one */
		अगर (!list_is_last(txd->at, &txd->dsg_list)) अणु
			txd->at = txd->at->next;
			अगर (txd->cyclic)
				vchan_cyclic_callback(&txd->vd);
			s3c24xx_dma_start_next_sg(s3cchan, txd);
		पूर्ण अन्यथा अगर (!txd->cyclic) अणु
			s3cchan->at = शून्य;
			vchan_cookie_complete(&txd->vd);

			/*
			 * And start the next descriptor (अगर any),
			 * otherwise मुक्त this channel.
			 */
			अगर (vchan_next_desc(&s3cchan->vc))
				s3c24xx_dma_start_next_txd(s3cchan);
			अन्यथा
				s3c24xx_dma_phy_मुक्त(s3cchan);
		पूर्ण अन्यथा अणु
			vchan_cyclic_callback(&txd->vd);

			/* Cyclic: reset at beginning */
			txd->at = txd->dsg_list.next;
			s3c24xx_dma_start_next_sg(s3cchan, txd);
		पूर्ण
	पूर्ण
	spin_unlock(&s3cchan->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * The DMA ENGINE API
 */

अटल पूर्णांक s3c24xx_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	LIST_HEAD(head);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&s3cchan->vc.lock, flags);

	अगर (!s3cchan->phy && !s3cchan->at) अणु
		dev_err(&s3cdma->pdev->dev, "trying to terminate already stopped channel %d\n",
			s3cchan->id);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	s3cchan->state = S3C24XX_DMA_CHAN_IDLE;

	/* Mark physical channel as मुक्त */
	अगर (s3cchan->phy)
		s3c24xx_dma_phy_मुक्त(s3cchan);

	/* Dequeue current job */
	अगर (s3cchan->at) अणु
		vchan_terminate_vdesc(&s3cchan->at->vd);
		s3cchan->at = शून्य;
	पूर्ण

	/* Dequeue jobs not yet fired as well */

	vchan_get_all_descriptors(&s3cchan->vc, &head);

	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&s3cchan->vc, &head);

	वापस 0;

unlock:
	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम s3c24xx_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);

	vchan_synchronize(&s3cchan->vc);
पूर्ण

अटल व्योम s3c24xx_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	/* Ensure all queued descriptors are मुक्तd */
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल क्रमागत dma_status s3c24xx_dma_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	काष्ठा s3c24xx_txd *txd;
	काष्ठा s3c24xx_sg *dsg;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	माप_प्रकार bytes = 0;

	spin_lock_irqsave(&s3cchan->vc.lock, flags);
	ret = dma_cookie_status(chan, cookie, txstate);

	/*
	 * There's no point calculating the residue if there's
	 * no txstate to store the value.
	 */
	अगर (ret == DMA_COMPLETE || !txstate) अणु
		spin_unlock_irqrestore(&s3cchan->vc.lock, flags);
		वापस ret;
	पूर्ण

	vd = vchan_find_desc(&s3cchan->vc, cookie);
	अगर (vd) अणु
		/* On the issued list, so hasn't been processed yet */
		txd = to_s3c24xx_txd(&vd->tx);

		list_क्रम_each_entry(dsg, &txd->dsg_list, node)
			bytes += dsg->len;
	पूर्ण अन्यथा अणु
		/*
		 * Currently running, so sum over the pending sg's and
		 * the currently active one.
		 */
		txd = s3cchan->at;

		dsg = list_entry(txd->at, काष्ठा s3c24xx_sg, node);
		list_क्रम_each_entry_from(dsg, &txd->dsg_list, node)
			bytes += dsg->len;

		bytes += s3c24xx_dma_getbytes_chan(s3cchan);
	पूर्ण
	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);

	/*
	 * This cookie not complete yet
	 * Get number of bytes left in the active transactions and queue
	 */
	dma_set_residue(txstate, bytes);

	/* Whether रुकोing or running, we're in progress */
	वापस ret;
पूर्ण

/*
 * Initialize a descriptor to be used by स_नकल submit
 */
अटल काष्ठा dma_async_tx_descriptor *s3c24xx_dma_prep_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	काष्ठा s3c24xx_txd *txd;
	काष्ठा s3c24xx_sg *dsg;
	पूर्णांक src_mod, dest_mod;

	dev_dbg(&s3cdma->pdev->dev, "prepare memcpy of %zu bytes from %s\n",
			len, s3cchan->name);

	अगर ((len & S3C24XX_DCON_TC_MASK) != len) अणु
		dev_err(&s3cdma->pdev->dev, "memcpy size %zu to large\n", len);
		वापस शून्य;
	पूर्ण

	txd = s3c24xx_dma_get_txd();
	अगर (!txd)
		वापस शून्य;

	dsg = kzalloc(माप(*dsg), GFP_NOWAIT);
	अगर (!dsg) अणु
		s3c24xx_dma_मुक्त_txd(txd);
		वापस शून्य;
	पूर्ण
	list_add_tail(&dsg->node, &txd->dsg_list);

	dsg->src_addr = src;
	dsg->dst_addr = dest;
	dsg->len = len;

	/*
	 * Determine a suitable transfer width.
	 * The DMA controller cannot fetch/store inक्रमmation which is not
	 * naturally aligned on the bus, i.e., a 4 byte fetch must start at
	 * an address भागisible by 4 - more generally addr % width must be 0.
	 */
	src_mod = src % 4;
	dest_mod = dest % 4;
	चयन (len % 4) अणु
	हाल 0:
		txd->width = (src_mod == 0 && dest_mod == 0) ? 4 : 1;
		अवरोध;
	हाल 2:
		txd->width = ((src_mod == 2 || src_mod == 0) &&
			      (dest_mod == 2 || dest_mod == 0)) ? 2 : 1;
		अवरोध;
	शेष:
		txd->width = 1;
		अवरोध;
	पूर्ण

	txd->disrcc = S3C24XX_DISRCC_LOC_AHB | S3C24XX_DISRCC_INC_INCREMENT;
	txd->didstc = S3C24XX_DIDSTC_LOC_AHB | S3C24XX_DIDSTC_INC_INCREMENT;
	txd->dcon |= S3C24XX_DCON_DEMAND | S3C24XX_DCON_SYNC_HCLK |
		     S3C24XX_DCON_SERV_WHOLE;

	वापस vchan_tx_prep(&s3cchan->vc, &txd->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *s3c24xx_dma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t addr, माप_प्रकार size, माप_प्रकार period,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = s3cdma->pdata;
	काष्ठा s3c24xx_dma_channel *cdata = &pdata->channels[s3cchan->id];
	काष्ठा s3c24xx_txd *txd;
	काष्ठा s3c24xx_sg *dsg;
	अचिन्हित sg_len;
	dma_addr_t slave_addr;
	u32 hwcfg = 0;
	पूर्णांक i;

	dev_dbg(&s3cdma->pdev->dev,
		"prepare cyclic transaction of %zu bytes with period %zu from %s\n",
		size, period, s3cchan->name);

	अगर (!is_slave_direction(direction)) अणु
		dev_err(&s3cdma->pdev->dev,
			"direction %d unsupported\n", direction);
		वापस शून्य;
	पूर्ण

	txd = s3c24xx_dma_get_txd();
	अगर (!txd)
		वापस शून्य;

	txd->cyclic = 1;

	अगर (cdata->handshake)
		txd->dcon |= S3C24XX_DCON_HANDSHAKE;

	चयन (cdata->bus) अणु
	हाल S3C24XX_DMA_APB:
		txd->dcon |= S3C24XX_DCON_SYNC_PCLK;
		hwcfg |= S3C24XX_DISRCC_LOC_APB;
		अवरोध;
	हाल S3C24XX_DMA_AHB:
		txd->dcon |= S3C24XX_DCON_SYNC_HCLK;
		hwcfg |= S3C24XX_DISRCC_LOC_AHB;
		अवरोध;
	पूर्ण

	/*
	 * Always assume our peripheral desपूर्णांकation is a fixed
	 * address in memory.
	 */
	hwcfg |= S3C24XX_DISRCC_INC_FIXED;

	/*
	 * Inभागidual dma operations are requested by the slave,
	 * so serve only single atomic operations (S3C24XX_DCON_SERV_SINGLE).
	 */
	txd->dcon |= S3C24XX_DCON_SERV_SINGLE;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		txd->disrcc = S3C24XX_DISRCC_LOC_AHB |
			      S3C24XX_DISRCC_INC_INCREMENT;
		txd->didstc = hwcfg;
		slave_addr = s3cchan->cfg.dst_addr;
		txd->width = s3cchan->cfg.dst_addr_width;
	पूर्ण अन्यथा अणु
		txd->disrcc = hwcfg;
		txd->didstc = S3C24XX_DIDSTC_LOC_AHB |
			      S3C24XX_DIDSTC_INC_INCREMENT;
		slave_addr = s3cchan->cfg.src_addr;
		txd->width = s3cchan->cfg.src_addr_width;
	पूर्ण

	sg_len = size / period;

	क्रम (i = 0; i < sg_len; i++) अणु
		dsg = kzalloc(माप(*dsg), GFP_NOWAIT);
		अगर (!dsg) अणु
			s3c24xx_dma_मुक्त_txd(txd);
			वापस शून्य;
		पूर्ण
		list_add_tail(&dsg->node, &txd->dsg_list);

		dsg->len = period;
		/* Check last period length */
		अगर (i == sg_len - 1)
			dsg->len = size - period * i;
		अगर (direction == DMA_MEM_TO_DEV) अणु
			dsg->src_addr = addr + period * i;
			dsg->dst_addr = slave_addr;
		पूर्ण अन्यथा अणु /* DMA_DEV_TO_MEM */
			dsg->src_addr = slave_addr;
			dsg->dst_addr = addr + period * i;
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&s3cchan->vc, &txd->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *s3c24xx_dma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	काष्ठा s3c24xx_dma_engine *s3cdma = s3cchan->host;
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = s3cdma->pdata;
	काष्ठा s3c24xx_dma_channel *cdata = &pdata->channels[s3cchan->id];
	काष्ठा s3c24xx_txd *txd;
	काष्ठा s3c24xx_sg *dsg;
	काष्ठा scatterlist *sg;
	dma_addr_t slave_addr;
	u32 hwcfg = 0;
	पूर्णांक पंचांगp;

	dev_dbg(&s3cdma->pdev->dev, "prepare transaction of %d bytes from %s\n",
			sg_dma_len(sgl), s3cchan->name);

	txd = s3c24xx_dma_get_txd();
	अगर (!txd)
		वापस शून्य;

	अगर (cdata->handshake)
		txd->dcon |= S3C24XX_DCON_HANDSHAKE;

	चयन (cdata->bus) अणु
	हाल S3C24XX_DMA_APB:
		txd->dcon |= S3C24XX_DCON_SYNC_PCLK;
		hwcfg |= S3C24XX_DISRCC_LOC_APB;
		अवरोध;
	हाल S3C24XX_DMA_AHB:
		txd->dcon |= S3C24XX_DCON_SYNC_HCLK;
		hwcfg |= S3C24XX_DISRCC_LOC_AHB;
		अवरोध;
	पूर्ण

	/*
	 * Always assume our peripheral desपूर्णांकation is a fixed
	 * address in memory.
	 */
	hwcfg |= S3C24XX_DISRCC_INC_FIXED;

	/*
	 * Inभागidual dma operations are requested by the slave,
	 * so serve only single atomic operations (S3C24XX_DCON_SERV_SINGLE).
	 */
	txd->dcon |= S3C24XX_DCON_SERV_SINGLE;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		txd->disrcc = S3C24XX_DISRCC_LOC_AHB |
			      S3C24XX_DISRCC_INC_INCREMENT;
		txd->didstc = hwcfg;
		slave_addr = s3cchan->cfg.dst_addr;
		txd->width = s3cchan->cfg.dst_addr_width;
	पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM) अणु
		txd->disrcc = hwcfg;
		txd->didstc = S3C24XX_DIDSTC_LOC_AHB |
			      S3C24XX_DIDSTC_INC_INCREMENT;
		slave_addr = s3cchan->cfg.src_addr;
		txd->width = s3cchan->cfg.src_addr_width;
	पूर्ण अन्यथा अणु
		s3c24xx_dma_मुक्त_txd(txd);
		dev_err(&s3cdma->pdev->dev,
			"direction %d unsupported\n", direction);
		वापस शून्य;
	पूर्ण

	क्रम_each_sg(sgl, sg, sg_len, पंचांगp) अणु
		dsg = kzalloc(माप(*dsg), GFP_NOWAIT);
		अगर (!dsg) अणु
			s3c24xx_dma_मुक्त_txd(txd);
			वापस शून्य;
		पूर्ण
		list_add_tail(&dsg->node, &txd->dsg_list);

		dsg->len = sg_dma_len(sg);
		अगर (direction == DMA_MEM_TO_DEV) अणु
			dsg->src_addr = sg_dma_address(sg);
			dsg->dst_addr = slave_addr;
		पूर्ण अन्यथा अणु /* DMA_DEV_TO_MEM */
			dsg->src_addr = slave_addr;
			dsg->dst_addr = sg_dma_address(sg);
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&s3cchan->vc, &txd->vd, flags);
पूर्ण

/*
 * Slave transactions callback to the slave device to allow
 * synchronization of slave DMA संकेतs with the DMAC enable
 */
अटल व्योम s3c24xx_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s3cchan->vc.lock, flags);
	अगर (vchan_issue_pending(&s3cchan->vc)) अणु
		अगर (!s3cchan->phy && s3cchan->state != S3C24XX_DMA_CHAN_WAITING)
			s3c24xx_dma_phy_alloc_and_start(s3cchan);
	पूर्ण
	spin_unlock_irqrestore(&s3cchan->vc.lock, flags);
पूर्ण

/*
 * Bringup and tearकरोwn
 */

/*
 * Initialise the DMAC स_नकल/slave channels.
 * Make a local wrapper to hold required data
 */
अटल पूर्णांक s3c24xx_dma_init_भव_channels(काष्ठा s3c24xx_dma_engine *s3cdma,
		काष्ठा dma_device *dmadev, अचिन्हित पूर्णांक channels, bool slave)
अणु
	काष्ठा s3c24xx_dma_chan *chan;
	पूर्णांक i;

	INIT_LIST_HEAD(&dmadev->channels);

	/*
	 * Register as many many स_नकल as we have physical channels,
	 * we won't always be able to use all but the code will have
	 * to cope with that situation.
	 */
	क्रम (i = 0; i < channels; i++) अणु
		chan = devm_kzalloc(dmadev->dev, माप(*chan), GFP_KERNEL);
		अगर (!chan)
			वापस -ENOMEM;

		chan->id = i;
		chan->host = s3cdma;
		chan->state = S3C24XX_DMA_CHAN_IDLE;

		अगर (slave) अणु
			chan->slave = true;
			chan->name = kaप्र_लिखो(GFP_KERNEL, "slave%d", i);
			अगर (!chan->name)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			chan->name = kaप्र_लिखो(GFP_KERNEL, "memcpy%d", i);
			अगर (!chan->name)
				वापस -ENOMEM;
		पूर्ण
		dev_dbg(dmadev->dev,
			 "initialize virtual channel \"%s\"\n",
			 chan->name);

		chan->vc.desc_मुक्त = s3c24xx_dma_desc_मुक्त;
		vchan_init(&chan->vc, dmadev);
	पूर्ण
	dev_info(dmadev->dev, "initialized %d virtual %s channels\n",
		 i, slave ? "slave" : "memcpy");
	वापस i;
पूर्ण

अटल व्योम s3c24xx_dma_मुक्त_भव_channels(काष्ठा dma_device *dmadev)
अणु
	काष्ठा s3c24xx_dma_chan *chan = शून्य;
	काष्ठा s3c24xx_dma_chan *next;

	list_क्रम_each_entry_safe(chan,
				 next, &dmadev->channels, vc.chan.device_node) अणु
		list_del(&chan->vc.chan.device_node);
		tasklet_समाप्त(&chan->vc.task);
	पूर्ण
पूर्ण

/* s3c2410, s3c2440 and s3c2442 have a 0x40 stride without separate घड़ीs */
अटल काष्ठा soc_data soc_s3c2410 = अणु
	.stride = 0x40,
	.has_reqsel = false,
	.has_घड़ीs = false,
पूर्ण;

/* s3c2412 and s3c2413 have a 0x40 stride and dmareqsel mechanism */
अटल काष्ठा soc_data soc_s3c2412 = अणु
	.stride = 0x40,
	.has_reqsel = true,
	.has_घड़ीs = true,
पूर्ण;

/* s3c2443 and following have a 0x100 stride and dmareqsel mechanism */
अटल काष्ठा soc_data soc_s3c2443 = अणु
	.stride = 0x100,
	.has_reqsel = true,
	.has_घड़ीs = true,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c24xx_dma_driver_ids[] = अणु
	अणु
		.name		= "s3c2410-dma",
		.driver_data	= (kernel_uदीर्घ_t)&soc_s3c2410,
	पूर्ण, अणु
		.name		= "s3c2412-dma",
		.driver_data	= (kernel_uदीर्घ_t)&soc_s3c2412,
	पूर्ण, अणु
		.name		= "s3c2443-dma",
		.driver_data	= (kernel_uदीर्घ_t)&soc_s3c2443,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा soc_data *s3c24xx_dma_get_soc_data(काष्ठा platक्रमm_device *pdev)
अणु
	वापस (काष्ठा soc_data *)
			 platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक s3c24xx_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा s3c24xx_dma_engine *s3cdma;
	काष्ठा soc_data *sdata;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "platform data missing\n");
		वापस -ENODEV;
	पूर्ण

	/* Basic sanity check */
	अगर (pdata->num_phy_channels > MAX_DMA_CHANNELS) अणु
		dev_err(&pdev->dev, "too many dma channels %d, max %d\n",
			pdata->num_phy_channels, MAX_DMA_CHANNELS);
		वापस -EINVAL;
	पूर्ण

	sdata = s3c24xx_dma_get_soc_data(pdev);
	अगर (!sdata)
		वापस -EINVAL;

	s3cdma = devm_kzalloc(&pdev->dev, माप(*s3cdma), GFP_KERNEL);
	अगर (!s3cdma)
		वापस -ENOMEM;

	s3cdma->pdev = pdev;
	s3cdma->pdata = pdata;
	s3cdma->sdata = sdata;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	s3cdma->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(s3cdma->base))
		वापस PTR_ERR(s3cdma->base);

	s3cdma->phy_chans = devm_kसुस्मृति(&pdev->dev,
					      pdata->num_phy_channels,
					      माप(काष्ठा s3c24xx_dma_phy),
					      GFP_KERNEL);
	अगर (!s3cdma->phy_chans)
		वापस -ENOMEM;

	/* acquire irqs and घड़ीs क्रम all physical channels */
	क्रम (i = 0; i < pdata->num_phy_channels; i++) अणु
		काष्ठा s3c24xx_dma_phy *phy = &s3cdma->phy_chans[i];
		अक्षर clk_name[6];

		phy->id = i;
		phy->base = s3cdma->base + (i * sdata->stride);
		phy->host = s3cdma;

		phy->irq = platक्रमm_get_irq(pdev, i);
		अगर (phy->irq < 0)
			जारी;

		ret = devm_request_irq(&pdev->dev, phy->irq, s3c24xx_dma_irq,
				       0, pdev->name, phy);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Unable to request irq for channel %d, error %d\n",
				i, ret);
			जारी;
		पूर्ण

		अगर (sdata->has_घड़ीs) अणु
			प्र_लिखो(clk_name, "dma.%d", i);
			phy->clk = devm_clk_get(&pdev->dev, clk_name);
			अगर (IS_ERR(phy->clk) && sdata->has_घड़ीs) अणु
				dev_err(&pdev->dev, "unable to acquire clock for channel %d, error %lu\n",
					i, PTR_ERR(phy->clk));
				जारी;
			पूर्ण

			ret = clk_prepare(phy->clk);
			अगर (ret) अणु
				dev_err(&pdev->dev, "clock for phy %d failed, error %d\n",
					i, ret);
				जारी;
			पूर्ण
		पूर्ण

		spin_lock_init(&phy->lock);
		phy->valid = true;

		dev_dbg(&pdev->dev, "physical channel %d is %s\n",
			i, s3c24xx_dma_phy_busy(phy) ? "BUSY" : "FREE");
	पूर्ण

	/* Initialize स_नकल engine */
	dma_cap_set(DMA_MEMCPY, s3cdma->स_नकल.cap_mask);
	dma_cap_set(DMA_PRIVATE, s3cdma->स_नकल.cap_mask);
	s3cdma->स_नकल.dev = &pdev->dev;
	s3cdma->स_नकल.device_मुक्त_chan_resources =
					s3c24xx_dma_मुक्त_chan_resources;
	s3cdma->स_नकल.device_prep_dma_स_नकल = s3c24xx_dma_prep_स_नकल;
	s3cdma->स_नकल.device_tx_status = s3c24xx_dma_tx_status;
	s3cdma->स_नकल.device_issue_pending = s3c24xx_dma_issue_pending;
	s3cdma->स_नकल.device_config = s3c24xx_dma_set_runसमय_config;
	s3cdma->स_नकल.device_terminate_all = s3c24xx_dma_terminate_all;
	s3cdma->स_नकल.device_synchronize = s3c24xx_dma_synchronize;

	/* Initialize slave engine क्रम SoC पूर्णांकernal dedicated peripherals */
	dma_cap_set(DMA_SLAVE, s3cdma->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, s3cdma->slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, s3cdma->slave.cap_mask);
	s3cdma->slave.dev = &pdev->dev;
	s3cdma->slave.device_मुक्त_chan_resources =
					s3c24xx_dma_मुक्त_chan_resources;
	s3cdma->slave.device_tx_status = s3c24xx_dma_tx_status;
	s3cdma->slave.device_issue_pending = s3c24xx_dma_issue_pending;
	s3cdma->slave.device_prep_slave_sg = s3c24xx_dma_prep_slave_sg;
	s3cdma->slave.device_prep_dma_cyclic = s3c24xx_dma_prep_dma_cyclic;
	s3cdma->slave.device_config = s3c24xx_dma_set_runसमय_config;
	s3cdma->slave.device_terminate_all = s3c24xx_dma_terminate_all;
	s3cdma->slave.device_synchronize = s3c24xx_dma_synchronize;
	s3cdma->slave.filter.map = pdata->slave_map;
	s3cdma->slave.filter.mapcnt = pdata->slavecnt;
	s3cdma->slave.filter.fn = s3c24xx_dma_filter;

	/* Register as many स_नकल channels as there are physical channels */
	ret = s3c24xx_dma_init_भव_channels(s3cdma, &s3cdma->स_नकल,
						pdata->num_phy_channels, false);
	अगर (ret <= 0) अणु
		dev_warn(&pdev->dev,
			 "%s failed to enumerate memcpy channels - %d\n",
			 __func__, ret);
		जाओ err_स_नकल;
	पूर्ण

	/* Register slave channels */
	ret = s3c24xx_dma_init_भव_channels(s3cdma, &s3cdma->slave,
				pdata->num_channels, true);
	अगर (ret <= 0) अणु
		dev_warn(&pdev->dev,
			"%s failed to enumerate slave channels - %d\n",
				__func__, ret);
		जाओ err_slave;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&s3cdma->स_नकल);
	अगर (ret) अणु
		dev_warn(&pdev->dev,
			"%s failed to register memcpy as an async device - %d\n",
			__func__, ret);
		जाओ err_स_नकल_reg;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&s3cdma->slave);
	अगर (ret) अणु
		dev_warn(&pdev->dev,
			"%s failed to register slave as an async device - %d\n",
			__func__, ret);
		जाओ err_slave_reg;
	पूर्ण

	platक्रमm_set_drvdata(pdev, s3cdma);
	dev_info(&pdev->dev, "Loaded dma driver with %d physical channels\n",
		 pdata->num_phy_channels);

	वापस 0;

err_slave_reg:
	dma_async_device_unरेजिस्टर(&s3cdma->स_नकल);
err_स_नकल_reg:
	s3c24xx_dma_मुक्त_भव_channels(&s3cdma->slave);
err_slave:
	s3c24xx_dma_मुक्त_भव_channels(&s3cdma->स_नकल);
err_स_नकल:
	अगर (sdata->has_घड़ीs)
		क्रम (i = 0; i < pdata->num_phy_channels; i++) अणु
			काष्ठा s3c24xx_dma_phy *phy = &s3cdma->phy_chans[i];
			अगर (phy->valid)
				clk_unprepare(phy->clk);
		पूर्ण

	वापस ret;
पूर्ण

अटल व्योम s3c24xx_dma_मुक्त_irq(काष्ठा platक्रमm_device *pdev,
				काष्ठा s3c24xx_dma_engine *s3cdma)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s3cdma->pdata->num_phy_channels; i++) अणु
		काष्ठा s3c24xx_dma_phy *phy = &s3cdma->phy_chans[i];

		devm_मुक्त_irq(&pdev->dev, phy->irq, phy);
	पूर्ण
पूर्ण

अटल पूर्णांक s3c24xx_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा s3c24xx_dma_platdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा s3c24xx_dma_engine *s3cdma = platक्रमm_get_drvdata(pdev);
	काष्ठा soc_data *sdata = s3c24xx_dma_get_soc_data(pdev);
	पूर्णांक i;

	dma_async_device_unरेजिस्टर(&s3cdma->slave);
	dma_async_device_unरेजिस्टर(&s3cdma->स_नकल);

	s3c24xx_dma_मुक्त_irq(pdev, s3cdma);

	s3c24xx_dma_मुक्त_भव_channels(&s3cdma->slave);
	s3c24xx_dma_मुक्त_भव_channels(&s3cdma->स_नकल);

	अगर (sdata->has_घड़ीs)
		क्रम (i = 0; i < pdata->num_phy_channels; i++) अणु
			काष्ठा s3c24xx_dma_phy *phy = &s3cdma->phy_chans[i];
			अगर (phy->valid)
				clk_unprepare(phy->clk);
		पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c24xx_dma_driver = अणु
	.driver		= अणु
		.name	= "s3c24xx-dma",
	पूर्ण,
	.id_table	= s3c24xx_dma_driver_ids,
	.probe		= s3c24xx_dma_probe,
	.हटाओ		= s3c24xx_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(s3c24xx_dma_driver);

bool s3c24xx_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा s3c24xx_dma_chan *s3cchan;

	अगर (chan->device->dev->driver != &s3c24xx_dma_driver.driver)
		वापस false;

	s3cchan = to_s3c24xx_dma_chan(chan);

	वापस s3cchan->id == (uपूर्णांकptr_t)param;
पूर्ण
EXPORT_SYMBOL(s3c24xx_dma_filter);

MODULE_DESCRIPTION("S3C24XX DMA Driver");
MODULE_AUTHOR("Heiko Stuebner");
MODULE_LICENSE("GPL v2");
