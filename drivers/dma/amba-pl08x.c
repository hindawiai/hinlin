<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2006 ARM Ltd.
 * Copyright (c) 2010 ST-Ericsson SA
 * Copyirght (c) 2017 Linaro Ltd.
 *
 * Author: Peter Pearse <peter.pearse@arm.com>
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * Documentation: ARM DDI 0196G == PL080
 * Documentation: ARM DDI 0218E == PL081
 * Documentation: S3C6410 User's Manual == PL080S
 *
 * PL080 & PL081 both have 16 sets of DMA संकेतs that can be routed to any
 * channel.
 *
 * The PL080 has 8 channels available क्रम simultaneous use, and the PL081
 * has only two channels. So on these DMA controllers the number of channels
 * and the number of incoming DMA संकेतs are two totally dअगरferent things.
 * It is usually not possible to theoretically handle all physical संकेतs,
 * so a multiplexing scheme with possible denial of use is necessary.
 *
 * The PL080 has a dual bus master, PL081 has a single master.
 *
 * PL080S is a version modअगरied by Samsung and used in S3C64xx SoCs.
 * It dअगरfers in following aspects:
 * - CH_CONFIG रेजिस्टर at dअगरferent offset,
 * - separate CH_CONTROL2 रेजिस्टर क्रम transfer size,
 * - bigger maximum transfer size,
 * - 8-word aligned LLI, instead of 4-word, due to extra CCTL2 word,
 * - no support क्रम peripheral flow control.
 *
 * Memory to peripheral transfer may be visualized as
 *	Get data from memory to DMAC
 *	Until no data left
 *		On burst request from peripheral
 *			Destination burst from DMAC to peripheral
 *			Clear burst request
 *	Raise terminal count पूर्णांकerrupt
 *
 * For peripherals with a FIFO:
 * Source      burst size == half the depth of the peripheral FIFO
 * Destination burst size == the depth of the peripheral FIFO
 *
 * (Bursts are irrelevant क्रम mem to mem transfers - there are no burst
 * संकेतs, the DMA controller will simply facilitate its AHB master.)
 *
 * ASSUMES शेष (little) endianness क्रम DMA transfers
 *
 * The PL08x has two flow control settings:
 *  - DMAC flow control: the transfer size defines the number of transfers
 *    which occur क्रम the current LLI entry, and the DMAC उठाओs TC at the
 *    end of every LLI entry.  Observed behaviour shows the DMAC listening
 *    to both the BREQ and SREQ संकेतs (contrary to करोcumented),
 *    transferring data अगर either is active.  The LBREQ and LSREQ संकेतs
 *    are ignored.
 *
 *  - Peripheral flow control: the transfer size is ignored (and should be
 *    zero).  The data is transferred from the current LLI entry, until
 *    after the final transfer संकेतled by LBREQ or LSREQ.  The DMAC
 *    will then move to the next LLI entry. Unsupported by PL080S.
 */
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/pl08x.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/amba/pl080.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा DRIVER_NAME	"pl08xdmac"

#घोषणा PL80X_DMA_BUSWIDTHS \
	BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED) | \
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)

अटल काष्ठा amba_driver pl08x_amba_driver;
काष्ठा pl08x_driver_data;

/**
 * काष्ठा venकरोr_data - venकरोr-specअगरic config parameters क्रम PL08x derivatives
 * @config_offset: offset to the configuration रेजिस्टर
 * @channels: the number of channels available in this variant
 * @संकेतs: the number of request संकेतs available from the hardware
 * @dualmaster: whether this version supports dual AHB masters or not.
 * @nomadik: whether this variant is a ST Microelectronics Nomadik, where the
 *	channels have Nomadik security extension bits that need to be checked
 *	क्रम permission beक्रमe use and some रेजिस्टरs are missing
 * @pl080s: whether this variant is a Samsung PL080S, which has separate
 *	रेजिस्टर and LLI word क्रम transfer size.
 * @ftdmac020: whether this variant is a Faraday Technology FTDMAC020
 * @max_transfer_size: the maximum single element transfer size क्रम this
 *	PL08x variant.
 */
काष्ठा venकरोr_data अणु
	u8 config_offset;
	u8 channels;
	u8 संकेतs;
	bool dualmaster;
	bool nomadik;
	bool pl080s;
	bool ftdmac020;
	u32 max_transfer_size;
पूर्ण;

/**
 * काष्ठा pl08x_bus_data - inक्रमmation of source or destination
 * busses क्रम a transfer
 * @addr: current address
 * @maxwidth: the maximum width of a transfer on this bus
 * @buswidth: the width of this bus in bytes: 1, 2 or 4
 */
काष्ठा pl08x_bus_data अणु
	dma_addr_t addr;
	u8 maxwidth;
	u8 buswidth;
पूर्ण;

#घोषणा IS_BUS_ALIGNED(bus) IS_ALIGNED((bus)->addr, (bus)->buswidth)

/**
 * काष्ठा pl08x_phy_chan - holder क्रम the physical channels
 * @id: physical index to this channel
 * @base: memory base address क्रम this physical channel
 * @reg_config: configuration address क्रम this physical channel
 * @reg_control: control address क्रम this physical channel
 * @reg_src: transfer source address रेजिस्टर
 * @reg_dst: transfer destination address रेजिस्टर
 * @reg_lli: transfer LLI address रेजिस्टर
 * @reg_busy: अगर the variant has a special per-channel busy रेजिस्टर,
 * this contains a poपूर्णांकer to it
 * @lock: a lock to use when altering an instance of this काष्ठा
 * @serving: the भव channel currently being served by this physical
 * channel
 * @locked: channel unavailable क्रम the प्रणाली, e.g. dedicated to secure
 * world
 * @ftdmac020: channel is on a FTDMAC020
 * @pl080s: channel is on a PL08s
 */
काष्ठा pl08x_phy_chan अणु
	अचिन्हित पूर्णांक id;
	व्योम __iomem *base;
	व्योम __iomem *reg_config;
	व्योम __iomem *reg_control;
	व्योम __iomem *reg_src;
	व्योम __iomem *reg_dst;
	व्योम __iomem *reg_lli;
	व्योम __iomem *reg_busy;
	spinlock_t lock;
	काष्ठा pl08x_dma_chan *serving;
	bool locked;
	bool ftdmac020;
	bool pl080s;
पूर्ण;

/**
 * काष्ठा pl08x_sg - काष्ठाure containing data per sg
 * @src_addr: src address of sg
 * @dst_addr: dst address of sg
 * @len: transfer len in bytes
 * @node: node क्रम txd's dsg_list
 */
काष्ठा pl08x_sg अणु
	dma_addr_t src_addr;
	dma_addr_t dst_addr;
	माप_प्रकार len;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा pl08x_txd - wrapper क्रम काष्ठा dma_async_tx_descriptor
 * @vd: भव DMA descriptor
 * @dsg_list: list of children sg's
 * @llis_bus: DMA memory address (physical) start क्रम the LLIs
 * @llis_va: भव memory address start क्रम the LLIs
 * @cctl: control reg values क्रम current txd
 * @ccfg: config reg values क्रम current txd
 * @करोne: this marks completed descriptors, which should not have their
 *   mux released.
 * @cyclic: indicate cyclic transfers
 */
काष्ठा pl08x_txd अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा list_head dsg_list;
	dma_addr_t llis_bus;
	u32 *llis_va;
	/* Default cctl value क्रम LLIs */
	u32 cctl;
	/*
	 * Settings to be put पूर्णांकo the physical channel when we
	 * trigger this txd.  Other रेजिस्टरs are in llis_va[0].
	 */
	u32 ccfg;
	bool करोne;
	bool cyclic;
पूर्ण;

/**
 * क्रमागत pl08x_dma_chan_state - holds the PL08x specअगरic भव channel
 * states
 * @PL08X_CHAN_IDLE: the channel is idle
 * @PL08X_CHAN_RUNNING: the channel has allocated a physical transport
 * channel and is running a transfer on it
 * @PL08X_CHAN_PAUSED: the channel has allocated a physical transport
 * channel, but the transfer is currently छोड़ोd
 * @PL08X_CHAN_WAITING: the channel is रुकोing क्रम a physical transport
 * channel to become available (only pertains to स_नकल channels)
 */
क्रमागत pl08x_dma_chan_state अणु
	PL08X_CHAN_IDLE,
	PL08X_CHAN_RUNNING,
	PL08X_CHAN_PAUSED,
	PL08X_CHAN_WAITING,
पूर्ण;

/**
 * काष्ठा pl08x_dma_chan - this काष्ठाure wraps a DMA ENGINE channel
 * @vc: wrappped भव channel
 * @phychan: the physical channel utilized by this channel, अगर there is one
 * @name: name of channel
 * @cd: channel platक्रमm data
 * @cfg: slave configuration
 * @at: active transaction on this channel
 * @host: a poपूर्णांकer to the host (पूर्णांकernal use)
 * @state: whether the channel is idle, छोड़ोd, running etc
 * @slave: whether this channel is a device (slave) or क्रम स_नकल
 * @संकेत: the physical DMA request संकेत which this channel is using
 * @mux_use: count of descriptors using this DMA request संकेत setting
 * @रुकोing_at: समय in jअगरfies when this channel moved to रुकोing state
 */
काष्ठा pl08x_dma_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा pl08x_phy_chan *phychan;
	स्थिर अक्षर *name;
	काष्ठा pl08x_channel_data *cd;
	काष्ठा dma_slave_config cfg;
	काष्ठा pl08x_txd *at;
	काष्ठा pl08x_driver_data *host;
	क्रमागत pl08x_dma_chan_state state;
	bool slave;
	पूर्णांक संकेत;
	अचिन्हित mux_use;
	अचिन्हित दीर्घ रुकोing_at;
पूर्ण;

/**
 * काष्ठा pl08x_driver_data - the local state holder क्रम the PL08x
 * @slave: optional slave engine क्रम this instance
 * @स_नकल: स_नकल engine क्रम this instance
 * @has_slave: the PL08x has a slave engine (routed संकेतs)
 * @base: भव memory base (remapped) क्रम the PL08x
 * @adev: the corresponding AMBA (PrimeCell) bus entry
 * @vd: venकरोr data क्रम this PL08x variant
 * @pd: platक्रमm data passed in from the platक्रमm/machine
 * @phy_chans: array of data क्रम the physical channels
 * @pool: a pool क्रम the LLI descriptors
 * @lli_buses: biपंचांगask to or in to LLI poपूर्णांकer selecting AHB port क्रम LLI
 * fetches
 * @mem_buses: set to indicate memory transfers on AHB2.
 * @lli_words: how many words are used in each LLI item क्रम this variant
 */
काष्ठा pl08x_driver_data अणु
	काष्ठा dma_device slave;
	काष्ठा dma_device स_नकल;
	bool has_slave;
	व्योम __iomem *base;
	काष्ठा amba_device *adev;
	स्थिर काष्ठा venकरोr_data *vd;
	काष्ठा pl08x_platक्रमm_data *pd;
	काष्ठा pl08x_phy_chan *phy_chans;
	काष्ठा dma_pool *pool;
	u8 lli_buses;
	u8 mem_buses;
	u8 lli_words;
पूर्ण;

/*
 * PL08X specअगरic defines
 */

/* The order of words in an LLI. */
#घोषणा PL080_LLI_SRC		0
#घोषणा PL080_LLI_DST		1
#घोषणा PL080_LLI_LLI		2
#घोषणा PL080_LLI_CCTL		3
#घोषणा PL080S_LLI_CCTL2	4

/* Total words in an LLI. */
#घोषणा PL080_LLI_WORDS		4
#घोषणा PL080S_LLI_WORDS	8

/*
 * Number of LLIs in each LLI buffer allocated क्रम one transfer
 * (maximum बार we call dma_pool_alloc on this pool without मुक्तing)
 */
#घोषणा MAX_NUM_TSFR_LLIS	512
#घोषणा PL08X_ALIGN		8

अटल अंतरभूत काष्ठा pl08x_dma_chan *to_pl08x_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा pl08x_dma_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा pl08x_txd *to_pl08x_txd(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा pl08x_txd, vd.tx);
पूर्ण

/*
 * Mux handling.
 *
 * This gives us the DMA request input to the PL08x primecell which the
 * peripheral described by the channel data will be routed to, possibly
 * via a board/SoC specअगरic बाह्यal MUX.  One important poपूर्णांक to note
 * here is that this करोes not depend on the physical channel.
 */
अटल पूर्णांक pl08x_request_mux(काष्ठा pl08x_dma_chan *plchan)
अणु
	स्थिर काष्ठा pl08x_platक्रमm_data *pd = plchan->host->pd;
	पूर्णांक ret;

	अगर (plchan->mux_use++ == 0 && pd->get_xfer_संकेत) अणु
		ret = pd->get_xfer_संकेत(plchan->cd);
		अगर (ret < 0) अणु
			plchan->mux_use = 0;
			वापस ret;
		पूर्ण

		plchan->संकेत = ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pl08x_release_mux(काष्ठा pl08x_dma_chan *plchan)
अणु
	स्थिर काष्ठा pl08x_platक्रमm_data *pd = plchan->host->pd;

	अगर (plchan->संकेत >= 0) अणु
		WARN_ON(plchan->mux_use == 0);

		अगर (--plchan->mux_use == 0 && pd->put_xfer_संकेत) अणु
			pd->put_xfer_संकेत(plchan->cd, plchan->संकेत);
			plchan->संकेत = -1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Physical channel handling
 */

/* Whether a certain channel is busy or not */
अटल पूर्णांक pl08x_phy_channel_busy(काष्ठा pl08x_phy_chan *ch)
अणु
	अचिन्हित पूर्णांक val;

	/* If we have a special busy रेजिस्टर, take a लघुcut */
	अगर (ch->reg_busy) अणु
		val = पढ़ोl(ch->reg_busy);
		वापस !!(val & BIT(ch->id));
	पूर्ण
	val = पढ़ोl(ch->reg_config);
	वापस val & PL080_CONFIG_ACTIVE;
पूर्ण

/*
 * pl08x_ग_लिखो_lli() - Write an LLI पूर्णांकo the DMA controller.
 *
 * The PL08x derivatives support linked lists, but the first item of the
 * list containing the source, destination, control word and next LLI is
 * ignored. Instead the driver has to ग_लिखो those values directly पूर्णांकo the
 * SRC, DST, LLI and control रेजिस्टरs. On FTDMAC020 also the SIZE
 * रेजिस्टर need to be set up क्रम the first transfer.
 */
अटल व्योम pl08x_ग_लिखो_lli(काष्ठा pl08x_driver_data *pl08x,
		काष्ठा pl08x_phy_chan *phychan, स्थिर u32 *lli, u32 ccfg)
अणु
	अगर (pl08x->vd->pl080s)
		dev_vdbg(&pl08x->adev->dev,
			"WRITE channel %d: csrc=0x%08x, cdst=0x%08x, "
			"clli=0x%08x, cctl=0x%08x, cctl2=0x%08x, ccfg=0x%08x\n",
			phychan->id, lli[PL080_LLI_SRC], lli[PL080_LLI_DST],
			lli[PL080_LLI_LLI], lli[PL080_LLI_CCTL],
			lli[PL080S_LLI_CCTL2], ccfg);
	अन्यथा
		dev_vdbg(&pl08x->adev->dev,
			"WRITE channel %d: csrc=0x%08x, cdst=0x%08x, "
			"clli=0x%08x, cctl=0x%08x, ccfg=0x%08x\n",
			phychan->id, lli[PL080_LLI_SRC], lli[PL080_LLI_DST],
			lli[PL080_LLI_LLI], lli[PL080_LLI_CCTL], ccfg);

	ग_लिखोl_relaxed(lli[PL080_LLI_SRC], phychan->reg_src);
	ग_लिखोl_relaxed(lli[PL080_LLI_DST], phychan->reg_dst);
	ग_लिखोl_relaxed(lli[PL080_LLI_LLI], phychan->reg_lli);

	/*
	 * The FTMAC020 has a dअगरferent layout in the CCTL word of the LLI
	 * and the CCTL रेजिस्टर which is split in CSR and SIZE रेजिस्टरs.
	 * Convert the LLI item CCTL पूर्णांकo the proper values to ग_लिखो पूर्णांकo
	 * the CSR and SIZE रेजिस्टरs.
	 */
	अगर (phychan->ftdmac020) अणु
		u32 llictl = lli[PL080_LLI_CCTL];
		u32 val = 0;

		/* Write the transfer size (12 bits) to the size रेजिस्टर */
		ग_लिखोl_relaxed(llictl & FTDMAC020_LLI_TRANSFER_SIZE_MASK,
			       phychan->base + FTDMAC020_CH_SIZE);
		/*
		 * Then ग_लिखो the control bits 28..16 to the control रेजिस्टर
		 * by shuffleing the bits around to where they are in the
		 * मुख्य रेजिस्टर. The mapping is as follows:
		 * Bit 28: TC_MSK - mask on all except last LLI
		 * Bit 27..25: SRC_WIDTH
		 * Bit 24..22: DST_WIDTH
		 * Bit 21..20: SRCAD_CTRL
		 * Bit 19..17: DSTAD_CTRL
		 * Bit 17: SRC_SEL
		 * Bit 16: DST_SEL
		 */
		अगर (llictl & FTDMAC020_LLI_TC_MSK)
			val |= FTDMAC020_CH_CSR_TC_MSK;
		val |= ((llictl  & FTDMAC020_LLI_SRC_WIDTH_MSK) >>
			(FTDMAC020_LLI_SRC_WIDTH_SHIFT -
			 FTDMAC020_CH_CSR_SRC_WIDTH_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_DST_WIDTH_MSK) >>
			(FTDMAC020_LLI_DST_WIDTH_SHIFT -
			 FTDMAC020_CH_CSR_DST_WIDTH_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_SRCAD_CTL_MSK) >>
			(FTDMAC020_LLI_SRCAD_CTL_SHIFT -
			 FTDMAC020_CH_CSR_SRCAD_CTL_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_DSTAD_CTL_MSK) >>
			(FTDMAC020_LLI_DSTAD_CTL_SHIFT -
			 FTDMAC020_CH_CSR_DSTAD_CTL_SHIFT));
		अगर (llictl & FTDMAC020_LLI_SRC_SEL)
			val |= FTDMAC020_CH_CSR_SRC_SEL;
		अगर (llictl & FTDMAC020_LLI_DST_SEL)
			val |= FTDMAC020_CH_CSR_DST_SEL;

		/*
		 * Set up the bits that exist in the CSR but are not
		 * part the LLI, i.e. only माला_लो written to the control
		 * रेजिस्टर right here.
		 *
		 * FIXME: करो not just handle स_नकल, also handle slave DMA.
		 */
		चयन (pl08x->pd->स_नकल_burst_size) अणु
		शेष:
		हाल PL08X_BURST_SZ_1:
			val |= PL080_BSIZE_1 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_4:
			val |= PL080_BSIZE_4 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_8:
			val |= PL080_BSIZE_8 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_16:
			val |= PL080_BSIZE_16 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_32:
			val |= PL080_BSIZE_32 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_64:
			val |= PL080_BSIZE_64 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_128:
			val |= PL080_BSIZE_128 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		हाल PL08X_BURST_SZ_256:
			val |= PL080_BSIZE_256 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			अवरोध;
		पूर्ण

		/* Protection flags */
		अगर (pl08x->pd->स_नकल_prot_buff)
			val |= FTDMAC020_CH_CSR_PROT2;
		अगर (pl08x->pd->स_नकल_prot_cache)
			val |= FTDMAC020_CH_CSR_PROT3;
		/* We are the kernel, so we are in privileged mode */
		val |= FTDMAC020_CH_CSR_PROT1;

		ग_लिखोl_relaxed(val, phychan->reg_control);
	पूर्ण अन्यथा अणु
		/* Bits are just identical */
		ग_लिखोl_relaxed(lli[PL080_LLI_CCTL], phychan->reg_control);
	पूर्ण

	/* Second control word on the PL080s */
	अगर (pl08x->vd->pl080s)
		ग_लिखोl_relaxed(lli[PL080S_LLI_CCTL2],
				phychan->base + PL080S_CH_CONTROL2);

	ग_लिखोl(ccfg, phychan->reg_config);
पूर्ण

/*
 * Set the initial DMA रेजिस्टर values i.e. those क्रम the first LLI
 * The next LLI poपूर्णांकer and the configuration पूर्णांकerrupt bit have
 * been set when the LLIs were स्थिरructed.  Poke them पूर्णांकo the hardware
 * and start the transfer.
 */
अटल व्योम pl08x_start_next_txd(काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_phy_chan *phychan = plchan->phychan;
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&plchan->vc);
	काष्ठा pl08x_txd *txd = to_pl08x_txd(&vd->tx);
	u32 val;

	list_del(&txd->vd.node);

	plchan->at = txd;

	/* Wait क्रम channel inactive */
	जबतक (pl08x_phy_channel_busy(phychan))
		cpu_relax();

	pl08x_ग_लिखो_lli(pl08x, phychan, &txd->llis_va[0], txd->ccfg);

	/* Enable the DMA channel */
	/* Do not access config रेजिस्टर until channel shows as disabled */
	जबतक (पढ़ोl(pl08x->base + PL080_EN_CHAN) & BIT(phychan->id))
		cpu_relax();

	/* Do not access config रेजिस्टर until channel shows as inactive */
	अगर (phychan->ftdmac020) अणु
		val = पढ़ोl(phychan->reg_config);
		जबतक (val & FTDMAC020_CH_CFG_BUSY)
			val = पढ़ोl(phychan->reg_config);

		val = पढ़ोl(phychan->reg_control);
		जबतक (val & FTDMAC020_CH_CSR_EN)
			val = पढ़ोl(phychan->reg_control);

		ग_लिखोl(val | FTDMAC020_CH_CSR_EN,
		       phychan->reg_control);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(phychan->reg_config);
		जबतक ((val & PL080_CONFIG_ACTIVE) ||
		       (val & PL080_CONFIG_ENABLE))
			val = पढ़ोl(phychan->reg_config);

		ग_लिखोl(val | PL080_CONFIG_ENABLE, phychan->reg_config);
	पूर्ण
पूर्ण

/*
 * Pause the channel by setting the HALT bit.
 *
 * For M->P transfers, छोड़ो the DMAC first and then stop the peripheral -
 * the FIFO can only drain अगर the peripheral is still requesting data.
 * (note: this can still समयout अगर the DMAC FIFO never drains of data.)
 *
 * For P->M transfers, disable the peripheral first to stop it filling
 * the DMAC FIFO, and then छोड़ो the DMAC.
 */
अटल व्योम pl08x_छोड़ो_phy_chan(काष्ठा pl08x_phy_chan *ch)
अणु
	u32 val;
	पूर्णांक समयout;

	अगर (ch->ftdmac020) अणु
		/* Use the enable bit on the FTDMAC020 */
		val = पढ़ोl(ch->reg_control);
		val &= ~FTDMAC020_CH_CSR_EN;
		ग_लिखोl(val, ch->reg_control);
		वापस;
	पूर्ण

	/* Set the HALT bit and रुको क्रम the FIFO to drain */
	val = पढ़ोl(ch->reg_config);
	val |= PL080_CONFIG_HALT;
	ग_लिखोl(val, ch->reg_config);

	/* Wait क्रम channel inactive */
	क्रम (समयout = 1000; समयout; समयout--) अणु
		अगर (!pl08x_phy_channel_busy(ch))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (pl08x_phy_channel_busy(ch))
		pr_err("pl08x: channel%u timeout waiting for pause\n", ch->id);
पूर्ण

अटल व्योम pl08x_resume_phy_chan(काष्ठा pl08x_phy_chan *ch)
अणु
	u32 val;

	/* Use the enable bit on the FTDMAC020 */
	अगर (ch->ftdmac020) अणु
		val = पढ़ोl(ch->reg_control);
		val |= FTDMAC020_CH_CSR_EN;
		ग_लिखोl(val, ch->reg_control);
		वापस;
	पूर्ण

	/* Clear the HALT bit */
	val = पढ़ोl(ch->reg_config);
	val &= ~PL080_CONFIG_HALT;
	ग_लिखोl(val, ch->reg_config);
पूर्ण

/*
 * pl08x_terminate_phy_chan() stops the channel, clears the FIFO and
 * clears any pending पूर्णांकerrupt status.  This should not be used क्रम
 * an on-going transfer, but as a method of shutting करोwn a channel
 * (eg, when it's no दीर्घer used) or terminating a transfer.
 */
अटल व्योम pl08x_terminate_phy_chan(काष्ठा pl08x_driver_data *pl08x,
	काष्ठा pl08x_phy_chan *ch)
अणु
	u32 val;

	/* The layout क्रम the FTDMAC020 is dअगरferent */
	अगर (ch->ftdmac020) अणु
		/* Disable all पूर्णांकerrupts */
		val = पढ़ोl(ch->reg_config);
		val |= (FTDMAC020_CH_CFG_INT_ABT_MASK |
			FTDMAC020_CH_CFG_INT_ERR_MASK |
			FTDMAC020_CH_CFG_INT_TC_MASK);
		ग_लिखोl(val, ch->reg_config);

		/* Abort and disable channel */
		val = पढ़ोl(ch->reg_control);
		val &= ~FTDMAC020_CH_CSR_EN;
		val |= FTDMAC020_CH_CSR_ABT;
		ग_लिखोl(val, ch->reg_control);

		/* Clear ABT and ERR पूर्णांकerrupt flags */
		ग_लिखोl(BIT(ch->id) | BIT(ch->id + 16),
		       pl08x->base + PL080_ERR_CLEAR);
		ग_लिखोl(BIT(ch->id), pl08x->base + PL080_TC_CLEAR);

		वापस;
	पूर्ण

	val = पढ़ोl(ch->reg_config);
	val &= ~(PL080_CONFIG_ENABLE | PL080_CONFIG_ERR_IRQ_MASK |
		 PL080_CONFIG_TC_IRQ_MASK);
	ग_लिखोl(val, ch->reg_config);

	ग_लिखोl(BIT(ch->id), pl08x->base + PL080_ERR_CLEAR);
	ग_लिखोl(BIT(ch->id), pl08x->base + PL080_TC_CLEAR);
पूर्ण

अटल u32 get_bytes_in_phy_channel(काष्ठा pl08x_phy_chan *ch)
अणु
	u32 val;
	u32 bytes;

	अगर (ch->ftdmac020) अणु
		bytes = पढ़ोl(ch->base + FTDMAC020_CH_SIZE);

		val = पढ़ोl(ch->reg_control);
		val &= FTDMAC020_CH_CSR_SRC_WIDTH_MSK;
		val >>= FTDMAC020_CH_CSR_SRC_WIDTH_SHIFT;
	पूर्ण अन्यथा अगर (ch->pl080s) अणु
		val = पढ़ोl(ch->base + PL080S_CH_CONTROL2);
		bytes = val & PL080S_CONTROL_TRANSFER_SIZE_MASK;

		val = पढ़ोl(ch->reg_control);
		val &= PL080_CONTROL_SWIDTH_MASK;
		val >>= PL080_CONTROL_SWIDTH_SHIFT;
	पूर्ण अन्यथा अणु
		/* Plain PL08x */
		val = पढ़ोl(ch->reg_control);
		bytes = val & PL080_CONTROL_TRANSFER_SIZE_MASK;

		val &= PL080_CONTROL_SWIDTH_MASK;
		val >>= PL080_CONTROL_SWIDTH_SHIFT;
	पूर्ण

	चयन (val) अणु
	हाल PL080_WIDTH_8BIT:
		अवरोध;
	हाल PL080_WIDTH_16BIT:
		bytes *= 2;
		अवरोध;
	हाल PL080_WIDTH_32BIT:
		bytes *= 4;
		अवरोध;
	पूर्ण
	वापस bytes;
पूर्ण

अटल u32 get_bytes_in_lli(काष्ठा pl08x_phy_chan *ch, स्थिर u32 *llis_va)
अणु
	u32 val;
	u32 bytes;

	अगर (ch->ftdmac020) अणु
		val = llis_va[PL080_LLI_CCTL];
		bytes = val & FTDMAC020_LLI_TRANSFER_SIZE_MASK;

		val = llis_va[PL080_LLI_CCTL];
		val &= FTDMAC020_LLI_SRC_WIDTH_MSK;
		val >>= FTDMAC020_LLI_SRC_WIDTH_SHIFT;
	पूर्ण अन्यथा अगर (ch->pl080s) अणु
		val = llis_va[PL080S_LLI_CCTL2];
		bytes = val & PL080S_CONTROL_TRANSFER_SIZE_MASK;

		val = llis_va[PL080_LLI_CCTL];
		val &= PL080_CONTROL_SWIDTH_MASK;
		val >>= PL080_CONTROL_SWIDTH_SHIFT;
	पूर्ण अन्यथा अणु
		/* Plain PL08x */
		val = llis_va[PL080_LLI_CCTL];
		bytes = val & PL080_CONTROL_TRANSFER_SIZE_MASK;

		val &= PL080_CONTROL_SWIDTH_MASK;
		val >>= PL080_CONTROL_SWIDTH_SHIFT;
	पूर्ण

	चयन (val) अणु
	हाल PL080_WIDTH_8BIT:
		अवरोध;
	हाल PL080_WIDTH_16BIT:
		bytes *= 2;
		अवरोध;
	हाल PL080_WIDTH_32BIT:
		bytes *= 4;
		अवरोध;
	पूर्ण
	वापस bytes;
पूर्ण

/* The channel should be छोड़ोd when calling this */
अटल u32 pl08x_getbytes_chan(काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	स्थिर u32 *llis_va, *llis_va_limit;
	काष्ठा pl08x_phy_chan *ch;
	dma_addr_t llis_bus;
	काष्ठा pl08x_txd *txd;
	u32 llis_max_words;
	माप_प्रकार bytes;
	u32 clli;

	ch = plchan->phychan;
	txd = plchan->at;

	अगर (!ch || !txd)
		वापस 0;

	/*
	 * Follow the LLIs to get the number of reमुख्यing
	 * bytes in the currently active transaction.
	 */
	clli = पढ़ोl(ch->reg_lli) & ~PL080_LLI_LM_AHB2;

	/* First get the reमुख्यing bytes in the active transfer */
	bytes = get_bytes_in_phy_channel(ch);

	अगर (!clli)
		वापस bytes;

	llis_va = txd->llis_va;
	llis_bus = txd->llis_bus;

	llis_max_words = pl08x->lli_words * MAX_NUM_TSFR_LLIS;
	BUG_ON(clli < llis_bus || clli >= llis_bus +
						माप(u32) * llis_max_words);

	/*
	 * Locate the next LLI - as this is an array,
	 * it's simple maths to find.
	 */
	llis_va += (clli - llis_bus) / माप(u32);

	llis_va_limit = llis_va + llis_max_words;

	क्रम (; llis_va < llis_va_limit; llis_va += pl08x->lli_words) अणु
		bytes += get_bytes_in_lli(ch, llis_va);

		/*
		 * A LLI poपूर्णांकer going backward terminates the LLI list
		 */
		अगर (llis_va[PL080_LLI_LLI] <= clli)
			अवरोध;
	पूर्ण

	वापस bytes;
पूर्ण

/*
 * Allocate a physical channel क्रम a भव channel
 *
 * Try to locate a physical channel to be used क्रम this transfer. If all
 * are taken वापस शून्य and the requester will have to cope by using
 * some fallback PIO mode or retrying later.
 */
अटल काष्ठा pl08x_phy_chan *
pl08x_get_phy_channel(काष्ठा pl08x_driver_data *pl08x,
		      काष्ठा pl08x_dma_chan *virt_chan)
अणु
	काष्ठा pl08x_phy_chan *ch = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < pl08x->vd->channels; i++) अणु
		ch = &pl08x->phy_chans[i];

		spin_lock_irqsave(&ch->lock, flags);

		अगर (!ch->locked && !ch->serving) अणु
			ch->serving = virt_chan;
			spin_unlock_irqrestore(&ch->lock, flags);
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण

	अगर (i == pl08x->vd->channels) अणु
		/* No physical channel available, cope with it */
		वापस शून्य;
	पूर्ण

	वापस ch;
पूर्ण

/* Mark the physical channel as मुक्त.  Note, this ग_लिखो is atomic. */
अटल अंतरभूत व्योम pl08x_put_phy_channel(काष्ठा pl08x_driver_data *pl08x,
					 काष्ठा pl08x_phy_chan *ch)
अणु
	ch->serving = शून्य;
पूर्ण

/*
 * Try to allocate a physical channel.  When successful, assign it to
 * this भव channel, and initiate the next descriptor.  The
 * भव channel lock must be held at this poपूर्णांक.
 */
अटल व्योम pl08x_phy_alloc_and_start(काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_phy_chan *ch;

	ch = pl08x_get_phy_channel(pl08x, plchan);
	अगर (!ch) अणु
		dev_dbg(&pl08x->adev->dev, "no physical channel available for xfer on %s\n", plchan->name);
		plchan->state = PL08X_CHAN_WAITING;
		plchan->रुकोing_at = jअगरfies;
		वापस;
	पूर्ण

	dev_dbg(&pl08x->adev->dev, "allocated physical channel %d for xfer on %s\n",
		ch->id, plchan->name);

	plchan->phychan = ch;
	plchan->state = PL08X_CHAN_RUNNING;
	pl08x_start_next_txd(plchan);
पूर्ण

अटल व्योम pl08x_phy_reassign_start(काष्ठा pl08x_phy_chan *ch,
	काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_driver_data *pl08x = plchan->host;

	dev_dbg(&pl08x->adev->dev, "reassigned physical channel %d for xfer on %s\n",
		ch->id, plchan->name);

	/*
	 * We करो this without taking the lock; we're really only concerned
	 * about whether this poपूर्णांकer is शून्य or not, and we're guaranteed
	 * that this will only be called when it _alपढ़ोy_ is non-शून्य.
	 */
	ch->serving = plchan;
	plchan->phychan = ch;
	plchan->state = PL08X_CHAN_RUNNING;
	pl08x_start_next_txd(plchan);
पूर्ण

/*
 * Free a physical DMA channel, potentially पुनः_स्मृतिating it to another
 * भव channel अगर we have any pending.
 */
अटल व्योम pl08x_phy_मुक्त(काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_dma_chan *p, *next;
	अचिन्हित दीर्घ रुकोing_at;
 retry:
	next = शून्य;
	रुकोing_at = jअगरfies;

	/*
	 * Find a रुकोing भव channel क्रम the next transfer.
	 * To be fair, समय when each channel reached रुकोing state is compared
	 * to select channel that is रुकोing क्रम the दीर्घest समय.
	 */
	list_क्रम_each_entry(p, &pl08x->स_नकल.channels, vc.chan.device_node)
		अगर (p->state == PL08X_CHAN_WAITING &&
		    p->रुकोing_at <= रुकोing_at) अणु
			next = p;
			रुकोing_at = p->रुकोing_at;
		पूर्ण

	अगर (!next && pl08x->has_slave) अणु
		list_क्रम_each_entry(p, &pl08x->slave.channels, vc.chan.device_node)
			अगर (p->state == PL08X_CHAN_WAITING &&
			    p->रुकोing_at <= रुकोing_at) अणु
				next = p;
				रुकोing_at = p->रुकोing_at;
			पूर्ण
	पूर्ण

	/* Ensure that the physical channel is stopped */
	pl08x_terminate_phy_chan(pl08x, plchan->phychan);

	अगर (next) अणु
		bool success;

		/*
		 * Eww.  We know this isn't going to deadlock
		 * but lockdep probably करोesn't.
		 */
		spin_lock(&next->vc.lock);
		/* Re-check the state now that we have the lock */
		success = next->state == PL08X_CHAN_WAITING;
		अगर (success)
			pl08x_phy_reassign_start(plchan->phychan, next);
		spin_unlock(&next->vc.lock);

		/* If the state changed, try to find another channel */
		अगर (!success)
			जाओ retry;
	पूर्ण अन्यथा अणु
		/* No more jobs, so मुक्त up the physical channel */
		pl08x_put_phy_channel(pl08x, plchan->phychan);
	पूर्ण

	plchan->phychan = शून्य;
	plchan->state = PL08X_CHAN_IDLE;
पूर्ण

/*
 * LLI handling
 */

अटल अंतरभूत अचिन्हित पूर्णांक
pl08x_get_bytes_क्रम_lli(काष्ठा pl08x_driver_data *pl08x,
			u32 cctl,
			bool source)
अणु
	u32 val;

	अगर (pl08x->vd->ftdmac020) अणु
		अगर (source)
			val = (cctl & FTDMAC020_LLI_SRC_WIDTH_MSK) >>
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
		अन्यथा
			val = (cctl & FTDMAC020_LLI_DST_WIDTH_MSK) >>
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
	पूर्ण अन्यथा अणु
		अगर (source)
			val = (cctl & PL080_CONTROL_SWIDTH_MASK) >>
				PL080_CONTROL_SWIDTH_SHIFT;
		अन्यथा
			val = (cctl & PL080_CONTROL_DWIDTH_MASK) >>
				PL080_CONTROL_DWIDTH_SHIFT;
	पूर्ण

	चयन (val) अणु
	हाल PL080_WIDTH_8BIT:
		वापस 1;
	हाल PL080_WIDTH_16BIT:
		वापस 2;
	हाल PL080_WIDTH_32BIT:
		वापस 4;
	शेष:
		अवरोध;
	पूर्ण
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत u32 pl08x_lli_control_bits(काष्ठा pl08x_driver_data *pl08x,
					 u32 cctl,
					 u8 srcwidth, u8 dstwidth,
					 माप_प्रकार tsize)
अणु
	u32 retbits = cctl;

	/*
	 * Remove all src, dst and transfer size bits, then set the
	 * width and size according to the parameters. The bit offsets
	 * are dअगरferent in the FTDMAC020 so we need to accound क्रम this.
	 */
	अगर (pl08x->vd->ftdmac020) अणु
		retbits &= ~FTDMAC020_LLI_DST_WIDTH_MSK;
		retbits &= ~FTDMAC020_LLI_SRC_WIDTH_MSK;
		retbits &= ~FTDMAC020_LLI_TRANSFER_SIZE_MASK;

		चयन (srcwidth) अणु
		हाल 1:
			retbits |= PL080_WIDTH_8BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			अवरोध;
		हाल 2:
			retbits |= PL080_WIDTH_16BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			अवरोध;
		हाल 4:
			retbits |= PL080_WIDTH_32BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		चयन (dstwidth) अणु
		हाल 1:
			retbits |= PL080_WIDTH_8BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			अवरोध;
		हाल 2:
			retbits |= PL080_WIDTH_16BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			अवरोध;
		हाल 4:
			retbits |= PL080_WIDTH_32BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		tsize &= FTDMAC020_LLI_TRANSFER_SIZE_MASK;
		retbits |= tsize << FTDMAC020_LLI_TRANSFER_SIZE_SHIFT;
	पूर्ण अन्यथा अणु
		retbits &= ~PL080_CONTROL_DWIDTH_MASK;
		retbits &= ~PL080_CONTROL_SWIDTH_MASK;
		retbits &= ~PL080_CONTROL_TRANSFER_SIZE_MASK;

		चयन (srcwidth) अणु
		हाल 1:
			retbits |= PL080_WIDTH_8BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			अवरोध;
		हाल 2:
			retbits |= PL080_WIDTH_16BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			अवरोध;
		हाल 4:
			retbits |= PL080_WIDTH_32BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		चयन (dstwidth) अणु
		हाल 1:
			retbits |= PL080_WIDTH_8BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			अवरोध;
		हाल 2:
			retbits |= PL080_WIDTH_16BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			अवरोध;
		हाल 4:
			retbits |= PL080_WIDTH_32BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण

		tsize &= PL080_CONTROL_TRANSFER_SIZE_MASK;
		retbits |= tsize << PL080_CONTROL_TRANSFER_SIZE_SHIFT;
	पूर्ण

	वापस retbits;
पूर्ण

काष्ठा pl08x_lli_build_data अणु
	काष्ठा pl08x_txd *txd;
	काष्ठा pl08x_bus_data srcbus;
	काष्ठा pl08x_bus_data dstbus;
	माप_प्रकार reमुख्यder;
	u32 lli_bus;
पूर्ण;

/*
 * Autoselect a master bus to use क्रम the transfer. Slave will be the chosen as
 * victim in हाल src & dest are not similarly aligned. i.e. If after aligning
 * masters address with width requirements of transfer (by sending few byte by
 * byte data), slave is still not aligned, then its width will be reduced to
 * BYTE.
 * - prefers the destination bus अगर both available
 * - prefers bus with fixed address (i.e. peripheral)
 */
अटल व्योम pl08x_choose_master_bus(काष्ठा pl08x_driver_data *pl08x,
				    काष्ठा pl08x_lli_build_data *bd,
				    काष्ठा pl08x_bus_data **mbus,
				    काष्ठा pl08x_bus_data **sbus,
				    u32 cctl)
अणु
	bool dst_incr;
	bool src_incr;

	/*
	 * The FTDMAC020 only supports memory-to-memory transfer, so
	 * source and destination always increase.
	 */
	अगर (pl08x->vd->ftdmac020) अणु
		dst_incr = true;
		src_incr = true;
	पूर्ण अन्यथा अणु
		dst_incr = !!(cctl & PL080_CONTROL_DST_INCR);
		src_incr = !!(cctl & PL080_CONTROL_SRC_INCR);
	पूर्ण

	/*
	 * If either bus is not advancing, i.e. it is a peripheral, that
	 * one becomes master
	 */
	अगर (!dst_incr) अणु
		*mbus = &bd->dstbus;
		*sbus = &bd->srcbus;
	पूर्ण अन्यथा अगर (!src_incr) अणु
		*mbus = &bd->srcbus;
		*sbus = &bd->dstbus;
	पूर्ण अन्यथा अणु
		अगर (bd->dstbus.buswidth >= bd->srcbus.buswidth) अणु
			*mbus = &bd->dstbus;
			*sbus = &bd->srcbus;
		पूर्ण अन्यथा अणु
			*mbus = &bd->srcbus;
			*sbus = &bd->dstbus;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Fills in one LLI क्रम a certain transfer descriptor and advance the counter
 */
अटल व्योम pl08x_fill_lli_क्रम_desc(काष्ठा pl08x_driver_data *pl08x,
				    काष्ठा pl08x_lli_build_data *bd,
				    पूर्णांक num_llis, पूर्णांक len, u32 cctl, u32 cctl2)
अणु
	u32 offset = num_llis * pl08x->lli_words;
	u32 *llis_va = bd->txd->llis_va + offset;
	dma_addr_t llis_bus = bd->txd->llis_bus;

	BUG_ON(num_llis >= MAX_NUM_TSFR_LLIS);

	/* Advance the offset to next LLI. */
	offset += pl08x->lli_words;

	llis_va[PL080_LLI_SRC] = bd->srcbus.addr;
	llis_va[PL080_LLI_DST] = bd->dstbus.addr;
	llis_va[PL080_LLI_LLI] = (llis_bus + माप(u32) * offset);
	llis_va[PL080_LLI_LLI] |= bd->lli_bus;
	llis_va[PL080_LLI_CCTL] = cctl;
	अगर (pl08x->vd->pl080s)
		llis_va[PL080S_LLI_CCTL2] = cctl2;

	अगर (pl08x->vd->ftdmac020) अणु
		/* FIXME: only स_नकल so far so both increase */
		bd->srcbus.addr += len;
		bd->dstbus.addr += len;
	पूर्ण अन्यथा अणु
		अगर (cctl & PL080_CONTROL_SRC_INCR)
			bd->srcbus.addr += len;
		अगर (cctl & PL080_CONTROL_DST_INCR)
			bd->dstbus.addr += len;
	पूर्ण

	BUG_ON(bd->reमुख्यder < len);

	bd->reमुख्यder -= len;
पूर्ण

अटल अंतरभूत व्योम prep_byte_width_lli(काष्ठा pl08x_driver_data *pl08x,
			काष्ठा pl08x_lli_build_data *bd, u32 *cctl, u32 len,
			पूर्णांक num_llis, माप_प्रकार *total_bytes)
अणु
	*cctl = pl08x_lli_control_bits(pl08x, *cctl, 1, 1, len);
	pl08x_fill_lli_क्रम_desc(pl08x, bd, num_llis, len, *cctl, len);
	(*total_bytes) += len;
पूर्ण

#अगर 1
अटल व्योम pl08x_dump_lli(काष्ठा pl08x_driver_data *pl08x,
			   स्थिर u32 *llis_va, पूर्णांक num_llis)
अणु
	पूर्णांक i;

	अगर (pl08x->vd->pl080s) अणु
		dev_vdbg(&pl08x->adev->dev,
			"%-3s %-9s  %-10s %-10s %-10s %-10s %s\n",
			"lli", "", "csrc", "cdst", "clli", "cctl", "cctl2");
		क्रम (i = 0; i < num_llis; i++) अणु
			dev_vdbg(&pl08x->adev->dev,
				"%3d @%p: 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
				i, llis_va, llis_va[PL080_LLI_SRC],
				llis_va[PL080_LLI_DST], llis_va[PL080_LLI_LLI],
				llis_va[PL080_LLI_CCTL],
				llis_va[PL080S_LLI_CCTL2]);
			llis_va += pl08x->lli_words;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_vdbg(&pl08x->adev->dev,
			"%-3s %-9s  %-10s %-10s %-10s %s\n",
			"lli", "", "csrc", "cdst", "clli", "cctl");
		क्रम (i = 0; i < num_llis; i++) अणु
			dev_vdbg(&pl08x->adev->dev,
				"%3d @%p: 0x%08x 0x%08x 0x%08x 0x%08x\n",
				i, llis_va, llis_va[PL080_LLI_SRC],
				llis_va[PL080_LLI_DST], llis_va[PL080_LLI_LLI],
				llis_va[PL080_LLI_CCTL]);
			llis_va += pl08x->lli_words;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pl08x_dump_lli(काष्ठा pl08x_driver_data *pl08x,
				  स्थिर u32 *llis_va, पूर्णांक num_llis) अणुपूर्ण
#पूर्ण_अगर

/*
 * This fills in the table of LLIs क्रम the transfer descriptor
 * Note that we assume we never have to change the burst sizes
 * Return 0 क्रम error
 */
अटल पूर्णांक pl08x_fill_llis_क्रम_desc(काष्ठा pl08x_driver_data *pl08x,
			      काष्ठा pl08x_txd *txd)
अणु
	काष्ठा pl08x_bus_data *mbus, *sbus;
	काष्ठा pl08x_lli_build_data bd;
	पूर्णांक num_llis = 0;
	u32 cctl, early_bytes = 0;
	माप_प्रकार max_bytes_per_lli, total_bytes;
	u32 *llis_va, *last_lli;
	काष्ठा pl08x_sg *dsg;

	txd->llis_va = dma_pool_alloc(pl08x->pool, GFP_NOWAIT, &txd->llis_bus);
	अगर (!txd->llis_va) अणु
		dev_err(&pl08x->adev->dev, "%s no memory for llis\n", __func__);
		वापस 0;
	पूर्ण

	bd.txd = txd;
	bd.lli_bus = (pl08x->lli_buses & PL08X_AHB2) ? PL080_LLI_LM_AHB2 : 0;
	cctl = txd->cctl;

	/* Find maximum width of the source bus */
	bd.srcbus.maxwidth = pl08x_get_bytes_क्रम_lli(pl08x, cctl, true);

	/* Find maximum width of the destination bus */
	bd.dstbus.maxwidth = pl08x_get_bytes_क्रम_lli(pl08x, cctl, false);

	list_क्रम_each_entry(dsg, &txd->dsg_list, node) अणु
		total_bytes = 0;
		cctl = txd->cctl;

		bd.srcbus.addr = dsg->src_addr;
		bd.dstbus.addr = dsg->dst_addr;
		bd.reमुख्यder = dsg->len;
		bd.srcbus.buswidth = bd.srcbus.maxwidth;
		bd.dstbus.buswidth = bd.dstbus.maxwidth;

		pl08x_choose_master_bus(pl08x, &bd, &mbus, &sbus, cctl);

		dev_vdbg(&pl08x->adev->dev,
			"src=0x%08llx%s/%u dst=0x%08llx%s/%u len=%zu\n",
			(u64)bd.srcbus.addr,
			cctl & PL080_CONTROL_SRC_INCR ? "+" : "",
			bd.srcbus.buswidth,
			(u64)bd.dstbus.addr,
			cctl & PL080_CONTROL_DST_INCR ? "+" : "",
			bd.dstbus.buswidth,
			bd.reमुख्यder);
		dev_vdbg(&pl08x->adev->dev, "mbus=%s sbus=%s\n",
			mbus == &bd.srcbus ? "src" : "dst",
			sbus == &bd.srcbus ? "src" : "dst");

		/*
		 * Zero length is only allowed अगर all these requirements are
		 * met:
		 * - flow controller is peripheral.
		 * - src.addr is aligned to src.width
		 * - dst.addr is aligned to dst.width
		 *
		 * sg_len == 1 should be true, as there can be two हालs here:
		 *
		 * - Memory addresses are contiguous and are not scattered.
		 *   Here, Only one sg will be passed by user driver, with
		 *   memory address and zero length. We pass this to controller
		 *   and after the transfer it will receive the last burst
		 *   request from peripheral and so transfer finishes.
		 *
		 * - Memory addresses are scattered and are not contiguous.
		 *   Here, Obviously as DMA controller करोesn't know when a lli's
		 *   transfer माला_लो over, it can't load next lli. So in this
		 *   हाल, there has to be an assumption that only one lli is
		 *   supported. Thus, we can't have scattered addresses.
		 */
		अगर (!bd.reमुख्यder) अणु
			u32 fc;

			/* FTDMAC020 only करोes memory-to-memory */
			अगर (pl08x->vd->ftdmac020)
				fc = PL080_FLOW_MEM2MEM;
			अन्यथा
				fc = (txd->ccfg & PL080_CONFIG_FLOW_CONTROL_MASK) >>
					PL080_CONFIG_FLOW_CONTROL_SHIFT;
			अगर (!((fc >= PL080_FLOW_SRC2DST_DST) &&
					(fc <= PL080_FLOW_SRC2DST_SRC))) अणु
				dev_err(&pl08x->adev->dev, "%s sg len can't be zero",
					__func__);
				वापस 0;
			पूर्ण

			अगर (!IS_BUS_ALIGNED(&bd.srcbus) ||
				!IS_BUS_ALIGNED(&bd.dstbus)) अणु
				dev_err(&pl08x->adev->dev,
					"%s src & dst address must be aligned to src"
					" & dst width if peripheral is flow controller",
					__func__);
				वापस 0;
			पूर्ण

			cctl = pl08x_lli_control_bits(pl08x, cctl,
					bd.srcbus.buswidth, bd.dstbus.buswidth,
					0);
			pl08x_fill_lli_क्रम_desc(pl08x, &bd, num_llis++,
					0, cctl, 0);
			अवरोध;
		पूर्ण

		/*
		 * Send byte by byte क्रम following हालs
		 * - Less than a bus width available
		 * - until master bus is aligned
		 */
		अगर (bd.reमुख्यder < mbus->buswidth)
			early_bytes = bd.reमुख्यder;
		अन्यथा अगर (!IS_BUS_ALIGNED(mbus)) अणु
			early_bytes = mbus->buswidth -
				(mbus->addr & (mbus->buswidth - 1));
			अगर ((bd.reमुख्यder - early_bytes) < mbus->buswidth)
				early_bytes = bd.reमुख्यder;
		पूर्ण

		अगर (early_bytes) अणु
			dev_vdbg(&pl08x->adev->dev,
				"%s byte width LLIs (remain 0x%08zx)\n",
				__func__, bd.reमुख्यder);
			prep_byte_width_lli(pl08x, &bd, &cctl, early_bytes,
				num_llis++, &total_bytes);
		पूर्ण

		अगर (bd.reमुख्यder) अणु
			/*
			 * Master now aligned
			 * - अगर slave is not then we must set its width करोwn
			 */
			अगर (!IS_BUS_ALIGNED(sbus)) अणु
				dev_dbg(&pl08x->adev->dev,
					"%s set down bus width to one byte\n",
					__func__);

				sbus->buswidth = 1;
			पूर्ण

			/*
			 * Bytes transferred = tsize * src width, not
			 * MIN(buswidths)
			 */
			max_bytes_per_lli = bd.srcbus.buswidth *
						pl08x->vd->max_transfer_size;
			dev_vdbg(&pl08x->adev->dev,
				"%s max bytes per lli = %zu\n",
				__func__, max_bytes_per_lli);

			/*
			 * Make largest possible LLIs until less than one bus
			 * width left
			 */
			जबतक (bd.reमुख्यder > (mbus->buswidth - 1)) अणु
				माप_प्रकार lli_len, tsize, width;

				/*
				 * If enough left try to send max possible,
				 * otherwise try to send the reमुख्यder
				 */
				lli_len = min(bd.reमुख्यder, max_bytes_per_lli);

				/*
				 * Check against maximum bus alignment:
				 * Calculate actual transfer size in relation to
				 * bus width an get a maximum reमुख्यder of the
				 * highest bus width - 1
				 */
				width = max(mbus->buswidth, sbus->buswidth);
				lli_len = (lli_len / width) * width;
				tsize = lli_len / bd.srcbus.buswidth;

				dev_vdbg(&pl08x->adev->dev,
					"%s fill lli with single lli chunk of "
					"size 0x%08zx (remainder 0x%08zx)\n",
					__func__, lli_len, bd.reमुख्यder);

				cctl = pl08x_lli_control_bits(pl08x, cctl,
					bd.srcbus.buswidth, bd.dstbus.buswidth,
					tsize);
				pl08x_fill_lli_क्रम_desc(pl08x, &bd, num_llis++,
						lli_len, cctl, tsize);
				total_bytes += lli_len;
			पूर्ण

			/*
			 * Send any odd bytes
			 */
			अगर (bd.reमुख्यder) अणु
				dev_vdbg(&pl08x->adev->dev,
					"%s align with boundary, send odd bytes (remain %zu)\n",
					__func__, bd.reमुख्यder);
				prep_byte_width_lli(pl08x, &bd, &cctl,
					bd.reमुख्यder, num_llis++, &total_bytes);
			पूर्ण
		पूर्ण

		अगर (total_bytes != dsg->len) अणु
			dev_err(&pl08x->adev->dev,
				"%s size of encoded lli:s don't match total txd, transferred 0x%08zx from size 0x%08zx\n",
				__func__, total_bytes, dsg->len);
			वापस 0;
		पूर्ण

		अगर (num_llis >= MAX_NUM_TSFR_LLIS) अणु
			dev_err(&pl08x->adev->dev,
				"%s need to increase MAX_NUM_TSFR_LLIS from 0x%08x\n",
				__func__, MAX_NUM_TSFR_LLIS);
			वापस 0;
		पूर्ण
	पूर्ण

	llis_va = txd->llis_va;
	last_lli = llis_va + (num_llis - 1) * pl08x->lli_words;

	अगर (txd->cyclic) अणु
		/* Link back to the first LLI. */
		last_lli[PL080_LLI_LLI] = txd->llis_bus | bd.lli_bus;
	पूर्ण अन्यथा अणु
		/* The final LLI terminates the LLI. */
		last_lli[PL080_LLI_LLI] = 0;
		/* The final LLI element shall also fire an पूर्णांकerrupt. */
		अगर (pl08x->vd->ftdmac020)
			last_lli[PL080_LLI_CCTL] &= ~FTDMAC020_LLI_TC_MSK;
		अन्यथा
			last_lli[PL080_LLI_CCTL] |= PL080_CONTROL_TC_IRQ_EN;
	पूर्ण

	pl08x_dump_lli(pl08x, llis_va, num_llis);

	वापस num_llis;
पूर्ण

अटल व्योम pl08x_मुक्त_txd(काष्ठा pl08x_driver_data *pl08x,
			   काष्ठा pl08x_txd *txd)
अणु
	काष्ठा pl08x_sg *dsg, *_dsg;

	अगर (txd->llis_va)
		dma_pool_मुक्त(pl08x->pool, txd->llis_va, txd->llis_bus);

	list_क्रम_each_entry_safe(dsg, _dsg, &txd->dsg_list, node) अणु
		list_del(&dsg->node);
		kमुक्त(dsg);
	पूर्ण

	kमुक्त(txd);
पूर्ण

अटल व्योम pl08x_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा pl08x_txd *txd = to_pl08x_txd(&vd->tx);
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(vd->tx.chan);

	dma_descriptor_unmap(&vd->tx);
	अगर (!txd->करोne)
		pl08x_release_mux(plchan);

	pl08x_मुक्त_txd(plchan->host, txd);
पूर्ण

अटल व्योम pl08x_मुक्त_txd_list(काष्ठा pl08x_driver_data *pl08x,
				काष्ठा pl08x_dma_chan *plchan)
अणु
	LIST_HEAD(head);

	vchan_get_all_descriptors(&plchan->vc, &head);
	vchan_dma_desc_मुक्त_list(&plchan->vc, &head);
पूर्ण

/*
 * The DMA ENGINE API
 */
अटल व्योम pl08x_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	/* Ensure all queued descriptors are मुक्तd */
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *pl08x_prep_dma_पूर्णांकerrupt(
		काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_async_tx_descriptor *retval = शून्य;

	वापस retval;
पूर्ण

/*
 * Code accessing dma_async_is_complete() in a tight loop may give problems.
 * If slaves are relying on पूर्णांकerrupts to संकेत completion this function
 * must not be called with पूर्णांकerrupts disabled.
 */
अटल क्रमागत dma_status pl08x_dma_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	/*
	 * There's no point calculating the residue if there's
	 * no txstate to store the value.
	 */
	अगर (!txstate) अणु
		अगर (plchan->state == PL08X_CHAN_PAUSED)
			ret = DMA_PAUSED;
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&plchan->vc.lock, flags);
	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret != DMA_COMPLETE) अणु
		vd = vchan_find_desc(&plchan->vc, cookie);
		अगर (vd) अणु
			/* On the issued list, so hasn't been processed yet */
			काष्ठा pl08x_txd *txd = to_pl08x_txd(&vd->tx);
			काष्ठा pl08x_sg *dsg;

			list_क्रम_each_entry(dsg, &txd->dsg_list, node)
				bytes += dsg->len;
		पूर्ण अन्यथा अणु
			bytes = pl08x_getbytes_chan(plchan);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	/*
	 * This cookie not complete yet
	 * Get number of bytes left in the active transactions and queue
	 */
	dma_set_residue(txstate, bytes);

	अगर (plchan->state == PL08X_CHAN_PAUSED && ret == DMA_IN_PROGRESS)
		ret = DMA_PAUSED;

	/* Whether रुकोing or running, we're in progress */
	वापस ret;
पूर्ण

/* PrimeCell DMA extension */
काष्ठा burst_table अणु
	u32 burstwords;
	u32 reg;
पूर्ण;

अटल स्थिर काष्ठा burst_table burst_sizes[] = अणु
	अणु
		.burstwords = 256,
		.reg = PL080_BSIZE_256,
	पूर्ण,
	अणु
		.burstwords = 128,
		.reg = PL080_BSIZE_128,
	पूर्ण,
	अणु
		.burstwords = 64,
		.reg = PL080_BSIZE_64,
	पूर्ण,
	अणु
		.burstwords = 32,
		.reg = PL080_BSIZE_32,
	पूर्ण,
	अणु
		.burstwords = 16,
		.reg = PL080_BSIZE_16,
	पूर्ण,
	अणु
		.burstwords = 8,
		.reg = PL080_BSIZE_8,
	पूर्ण,
	अणु
		.burstwords = 4,
		.reg = PL080_BSIZE_4,
	पूर्ण,
	अणु
		.burstwords = 0,
		.reg = PL080_BSIZE_1,
	पूर्ण,
पूर्ण;

/*
 * Given the source and destination available bus masks, select which
 * will be routed to each port.  We try to have source and destination
 * on separate ports, but always respect the allowable settings.
 */
अटल u32 pl08x_select_bus(bool ftdmac020, u8 src, u8 dst)
अणु
	u32 cctl = 0;
	u32 dst_ahb2;
	u32 src_ahb2;

	/* The FTDMAC020 use dअगरferent bits to indicate src/dst bus */
	अगर (ftdmac020) अणु
		dst_ahb2 = FTDMAC020_LLI_DST_SEL;
		src_ahb2 = FTDMAC020_LLI_SRC_SEL;
	पूर्ण अन्यथा अणु
		dst_ahb2 = PL080_CONTROL_DST_AHB2;
		src_ahb2 = PL080_CONTROL_SRC_AHB2;
	पूर्ण

	अगर (!(dst & PL08X_AHB1) || ((dst & PL08X_AHB2) && (src & PL08X_AHB1)))
		cctl |= dst_ahb2;
	अगर (!(src & PL08X_AHB1) || ((src & PL08X_AHB2) && !(dst & PL08X_AHB2)))
		cctl |= src_ahb2;

	वापस cctl;
पूर्ण

अटल u32 pl08x_cctl(u32 cctl)
अणु
	cctl &= ~(PL080_CONTROL_SRC_AHB2 | PL080_CONTROL_DST_AHB2 |
		  PL080_CONTROL_SRC_INCR | PL080_CONTROL_DST_INCR |
		  PL080_CONTROL_PROT_MASK);

	/* Access the cell in privileged mode, non-bufferable, non-cacheable */
	वापस cctl | PL080_CONTROL_PROT_SYS;
पूर्ण

अटल u32 pl08x_width(क्रमागत dma_slave_buswidth width)
अणु
	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		वापस PL080_WIDTH_8BIT;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		वापस PL080_WIDTH_16BIT;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		वापस PL080_WIDTH_32BIT;
	शेष:
		वापस ~0;
	पूर्ण
पूर्ण

अटल u32 pl08x_burst(u32 maxburst)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(burst_sizes); i++)
		अगर (burst_sizes[i].burstwords <= maxburst)
			अवरोध;

	वापस burst_sizes[i].reg;
पूर्ण

अटल u32 pl08x_get_cctl(काष्ठा pl08x_dma_chan *plchan,
	क्रमागत dma_slave_buswidth addr_width, u32 maxburst)
अणु
	u32 width, burst, cctl = 0;

	width = pl08x_width(addr_width);
	अगर (width == ~0)
		वापस ~0;

	cctl |= width << PL080_CONTROL_SWIDTH_SHIFT;
	cctl |= width << PL080_CONTROL_DWIDTH_SHIFT;

	/*
	 * If this channel will only request single transfers, set this
	 * करोwn to ONE element.  Also select one element अगर no maxburst
	 * is specअगरied.
	 */
	अगर (plchan->cd->single)
		maxburst = 1;

	burst = pl08x_burst(maxburst);
	cctl |= burst << PL080_CONTROL_SB_SIZE_SHIFT;
	cctl |= burst << PL080_CONTROL_DB_SIZE_SHIFT;

	वापस pl08x_cctl(cctl);
पूर्ण

/*
 * Slave transactions callback to the slave device to allow
 * synchronization of slave DMA संकेतs with the DMAC enable
 */
अटल व्योम pl08x_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&plchan->vc.lock, flags);
	अगर (vchan_issue_pending(&plchan->vc)) अणु
		अगर (!plchan->phychan && plchan->state != PL08X_CHAN_WAITING)
			pl08x_phy_alloc_and_start(plchan);
	पूर्ण
	spin_unlock_irqrestore(&plchan->vc.lock, flags);
पूर्ण

अटल काष्ठा pl08x_txd *pl08x_get_txd(काष्ठा pl08x_dma_chan *plchan)
अणु
	काष्ठा pl08x_txd *txd = kzalloc(माप(*txd), GFP_NOWAIT);

	अगर (txd)
		INIT_LIST_HEAD(&txd->dsg_list);
	वापस txd;
पूर्ण

अटल u32 pl08x_स_नकल_cctl(काष्ठा pl08x_driver_data *pl08x)
अणु
	u32 cctl = 0;

	/* Conjure cctl */
	चयन (pl08x->pd->स_नकल_burst_size) अणु
	शेष:
		dev_err(&pl08x->adev->dev,
			"illegal burst size for memcpy, set to 1\n");
		fallthrough;
	हाल PL08X_BURST_SZ_1:
		cctl |= PL080_BSIZE_1 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_1 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_4:
		cctl |= PL080_BSIZE_4 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_4 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_8:
		cctl |= PL080_BSIZE_8 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_8 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_16:
		cctl |= PL080_BSIZE_16 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_16 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_32:
		cctl |= PL080_BSIZE_32 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_32 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_64:
		cctl |= PL080_BSIZE_64 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_64 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_128:
		cctl |= PL080_BSIZE_128 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_128 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	हाल PL08X_BURST_SZ_256:
		cctl |= PL080_BSIZE_256 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_256 << PL080_CONTROL_DB_SIZE_SHIFT;
		अवरोध;
	पूर्ण

	चयन (pl08x->pd->स_नकल_bus_width) अणु
	शेष:
		dev_err(&pl08x->adev->dev,
			"illegal bus width for memcpy, set to 8 bits\n");
		fallthrough;
	हाल PL08X_BUS_WIDTH_8_BITS:
		cctl |= PL080_WIDTH_8BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_8BIT << PL080_CONTROL_DWIDTH_SHIFT;
		अवरोध;
	हाल PL08X_BUS_WIDTH_16_BITS:
		cctl |= PL080_WIDTH_16BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_16BIT << PL080_CONTROL_DWIDTH_SHIFT;
		अवरोध;
	हाल PL08X_BUS_WIDTH_32_BITS:
		cctl |= PL080_WIDTH_32BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_32BIT << PL080_CONTROL_DWIDTH_SHIFT;
		अवरोध;
	पूर्ण

	/* Protection flags */
	अगर (pl08x->pd->स_नकल_prot_buff)
		cctl |= PL080_CONTROL_PROT_BUFF;
	अगर (pl08x->pd->स_नकल_prot_cache)
		cctl |= PL080_CONTROL_PROT_CACHE;

	/* We are the kernel, so we are in privileged mode */
	cctl |= PL080_CONTROL_PROT_SYS;

	/* Both to be incremented or the code will अवरोध */
	cctl |= PL080_CONTROL_SRC_INCR | PL080_CONTROL_DST_INCR;

	अगर (pl08x->vd->dualmaster)
		cctl |= pl08x_select_bus(false,
					 pl08x->mem_buses,
					 pl08x->mem_buses);

	वापस cctl;
पूर्ण

अटल u32 pl08x_ftdmac020_स_नकल_cctl(काष्ठा pl08x_driver_data *pl08x)
अणु
	u32 cctl = 0;

	/* Conjure cctl */
	चयन (pl08x->pd->स_नकल_bus_width) अणु
	शेष:
		dev_err(&pl08x->adev->dev,
			"illegal bus width for memcpy, set to 8 bits\n");
		fallthrough;
	हाल PL08X_BUS_WIDTH_8_BITS:
		cctl |= PL080_WIDTH_8BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_8BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		अवरोध;
	हाल PL08X_BUS_WIDTH_16_BITS:
		cctl |= PL080_WIDTH_16BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_16BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		अवरोध;
	हाल PL08X_BUS_WIDTH_32_BITS:
		cctl |= PL080_WIDTH_32BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_32BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		अवरोध;
	पूर्ण

	/*
	 * By शेष mask the TC IRQ on all LLIs, it will be unmasked on
	 * the last LLI item by other code.
	 */
	cctl |= FTDMAC020_LLI_TC_MSK;

	/*
	 * Both to be incremented so leave bits FTDMAC020_LLI_SRCAD_CTL
	 * and FTDMAC020_LLI_DSTAD_CTL as zero
	 */
	अगर (pl08x->vd->dualmaster)
		cctl |= pl08x_select_bus(true,
					 pl08x->mem_buses,
					 pl08x->mem_buses);

	वापस cctl;
पूर्ण

/*
 * Initialize a descriptor to be used by स_नकल submit
 */
अटल काष्ठा dma_async_tx_descriptor *pl08x_prep_dma_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_txd *txd;
	काष्ठा pl08x_sg *dsg;
	पूर्णांक ret;

	txd = pl08x_get_txd(plchan);
	अगर (!txd) अणु
		dev_err(&pl08x->adev->dev,
			"%s no memory for descriptor\n", __func__);
		वापस शून्य;
	पूर्ण

	dsg = kzalloc(माप(काष्ठा pl08x_sg), GFP_NOWAIT);
	अगर (!dsg) अणु
		pl08x_मुक्त_txd(pl08x, txd);
		वापस शून्य;
	पूर्ण
	list_add_tail(&dsg->node, &txd->dsg_list);

	dsg->src_addr = src;
	dsg->dst_addr = dest;
	dsg->len = len;
	अगर (pl08x->vd->ftdmac020) अणु
		/* Writing CCFG zero ENABLES all पूर्णांकerrupts */
		txd->ccfg = 0;
		txd->cctl = pl08x_ftdmac020_स_नकल_cctl(pl08x);
	पूर्ण अन्यथा अणु
		txd->ccfg = PL080_CONFIG_ERR_IRQ_MASK |
			PL080_CONFIG_TC_IRQ_MASK |
			PL080_FLOW_MEM2MEM << PL080_CONFIG_FLOW_CONTROL_SHIFT;
		txd->cctl = pl08x_स_नकल_cctl(pl08x);
	पूर्ण

	ret = pl08x_fill_llis_क्रम_desc(plchan->host, txd);
	अगर (!ret) अणु
		pl08x_मुक्त_txd(pl08x, txd);
		वापस शून्य;
	पूर्ण

	वापस vchan_tx_prep(&plchan->vc, &txd->vd, flags);
पूर्ण

अटल काष्ठा pl08x_txd *pl08x_init_txd(
		काष्ठा dma_chan *chan,
		क्रमागत dma_transfer_direction direction,
		dma_addr_t *slave_addr)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_txd *txd;
	क्रमागत dma_slave_buswidth addr_width;
	पूर्णांक ret, पंचांगp;
	u8 src_buses, dst_buses;
	u32 maxburst, cctl;

	txd = pl08x_get_txd(plchan);
	अगर (!txd) अणु
		dev_err(&pl08x->adev->dev, "%s no txd\n", __func__);
		वापस शून्य;
	पूर्ण

	/*
	 * Set up addresses, the PrimeCell configured address
	 * will take precedence since this may configure the
	 * channel target address dynamically at runसमय.
	 */
	अगर (direction == DMA_MEM_TO_DEV) अणु
		cctl = PL080_CONTROL_SRC_INCR;
		*slave_addr = plchan->cfg.dst_addr;
		addr_width = plchan->cfg.dst_addr_width;
		maxburst = plchan->cfg.dst_maxburst;
		src_buses = pl08x->mem_buses;
		dst_buses = plchan->cd->periph_buses;
	पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM) अणु
		cctl = PL080_CONTROL_DST_INCR;
		*slave_addr = plchan->cfg.src_addr;
		addr_width = plchan->cfg.src_addr_width;
		maxburst = plchan->cfg.src_maxburst;
		src_buses = plchan->cd->periph_buses;
		dst_buses = pl08x->mem_buses;
	पूर्ण अन्यथा अणु
		pl08x_मुक्त_txd(pl08x, txd);
		dev_err(&pl08x->adev->dev,
			"%s direction unsupported\n", __func__);
		वापस शून्य;
	पूर्ण

	cctl |= pl08x_get_cctl(plchan, addr_width, maxburst);
	अगर (cctl == ~0) अणु
		pl08x_मुक्त_txd(pl08x, txd);
		dev_err(&pl08x->adev->dev,
			"DMA slave configuration botched?\n");
		वापस शून्य;
	पूर्ण

	txd->cctl = cctl | pl08x_select_bus(false, src_buses, dst_buses);

	अगर (plchan->cfg.device_fc)
		पंचांगp = (direction == DMA_MEM_TO_DEV) ? PL080_FLOW_MEM2PER_PER :
			PL080_FLOW_PER2MEM_PER;
	अन्यथा
		पंचांगp = (direction == DMA_MEM_TO_DEV) ? PL080_FLOW_MEM2PER :
			PL080_FLOW_PER2MEM;

	txd->ccfg = PL080_CONFIG_ERR_IRQ_MASK |
		PL080_CONFIG_TC_IRQ_MASK |
		पंचांगp << PL080_CONFIG_FLOW_CONTROL_SHIFT;

	ret = pl08x_request_mux(plchan);
	अगर (ret < 0) अणु
		pl08x_मुक्त_txd(pl08x, txd);
		dev_dbg(&pl08x->adev->dev,
			"unable to mux for transfer on %s due to platform restrictions\n",
			plchan->name);
		वापस शून्य;
	पूर्ण

	dev_dbg(&pl08x->adev->dev, "allocated DMA request signal %d for xfer on %s\n",
		 plchan->संकेत, plchan->name);

	/* Assign the flow control संकेत to this channel */
	अगर (direction == DMA_MEM_TO_DEV)
		txd->ccfg |= plchan->संकेत << PL080_CONFIG_DST_SEL_SHIFT;
	अन्यथा
		txd->ccfg |= plchan->संकेत << PL080_CONFIG_SRC_SEL_SHIFT;

	वापस txd;
पूर्ण

अटल पूर्णांक pl08x_tx_add_sg(काष्ठा pl08x_txd *txd,
			   क्रमागत dma_transfer_direction direction,
			   dma_addr_t slave_addr,
			   dma_addr_t buf_addr,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा pl08x_sg *dsg;

	dsg = kzalloc(माप(काष्ठा pl08x_sg), GFP_NOWAIT);
	अगर (!dsg)
		वापस -ENOMEM;

	list_add_tail(&dsg->node, &txd->dsg_list);

	dsg->len = len;
	अगर (direction == DMA_MEM_TO_DEV) अणु
		dsg->src_addr = buf_addr;
		dsg->dst_addr = slave_addr;
	पूर्ण अन्यथा अणु
		dsg->src_addr = slave_addr;
		dsg->dst_addr = buf_addr;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *pl08x_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_txd *txd;
	काष्ठा scatterlist *sg;
	पूर्णांक ret, पंचांगp;
	dma_addr_t slave_addr;

	dev_dbg(&pl08x->adev->dev, "%s prepare transaction of %d bytes from %s\n",
			__func__, sg_dma_len(sgl), plchan->name);

	txd = pl08x_init_txd(chan, direction, &slave_addr);
	अगर (!txd)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, पंचांगp) अणु
		ret = pl08x_tx_add_sg(txd, direction, slave_addr,
				      sg_dma_address(sg),
				      sg_dma_len(sg));
		अगर (ret) अणु
			pl08x_release_mux(plchan);
			pl08x_मुक्त_txd(pl08x, txd);
			dev_err(&pl08x->adev->dev, "%s no mem for pl080 sg\n",
					__func__);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ret = pl08x_fill_llis_क्रम_desc(plchan->host, txd);
	अगर (!ret) अणु
		pl08x_release_mux(plchan);
		pl08x_मुक्त_txd(pl08x, txd);
		वापस शून्य;
	पूर्ण

	वापस vchan_tx_prep(&plchan->vc, &txd->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *pl08x_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	काष्ठा pl08x_txd *txd;
	पूर्णांक ret, पंचांगp;
	dma_addr_t slave_addr;

	dev_dbg(&pl08x->adev->dev,
		"%s prepare cyclic transaction of %zd/%zd bytes %s %s\n",
		__func__, period_len, buf_len,
		direction == DMA_MEM_TO_DEV ? "to" : "from",
		plchan->name);

	txd = pl08x_init_txd(chan, direction, &slave_addr);
	अगर (!txd)
		वापस शून्य;

	txd->cyclic = true;
	txd->cctl |= PL080_CONTROL_TC_IRQ_EN;
	क्रम (पंचांगp = 0; पंचांगp < buf_len; पंचांगp += period_len) अणु
		ret = pl08x_tx_add_sg(txd, direction, slave_addr,
				      buf_addr + पंचांगp, period_len);
		अगर (ret) अणु
			pl08x_release_mux(plchan);
			pl08x_मुक्त_txd(pl08x, txd);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ret = pl08x_fill_llis_क्रम_desc(plchan->host, txd);
	अगर (!ret) अणु
		pl08x_release_mux(plchan);
		pl08x_मुक्त_txd(pl08x, txd);
		वापस शून्य;
	पूर्ण

	वापस vchan_tx_prep(&plchan->vc, &txd->vd, flags);
पूर्ण

अटल पूर्णांक pl08x_config(काष्ठा dma_chan *chan,
			काष्ठा dma_slave_config *config)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;

	अगर (!plchan->slave)
		वापस -EINVAL;

	/* Reject definitely invalid configurations */
	अगर (config->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    config->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस -EINVAL;

	अगर (config->device_fc && pl08x->vd->pl080s) अणु
		dev_err(&pl08x->adev->dev,
			"%s: PL080S does not support peripheral flow control\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	plchan->cfg = *config;

	वापस 0;
पूर्ण

अटल पूर्णांक pl08x_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	काष्ठा pl08x_driver_data *pl08x = plchan->host;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&plchan->vc.lock, flags);
	अगर (!plchan->phychan && !plchan->at) अणु
		spin_unlock_irqrestore(&plchan->vc.lock, flags);
		वापस 0;
	पूर्ण

	plchan->state = PL08X_CHAN_IDLE;

	अगर (plchan->phychan) अणु
		/*
		 * Mark physical channel as मुक्त and मुक्त any slave
		 * संकेत
		 */
		pl08x_phy_मुक्त(plchan);
	पूर्ण
	/* Dequeue jobs and मुक्त LLIs */
	अगर (plchan->at) अणु
		vchan_terminate_vdesc(&plchan->at->vd);
		plchan->at = शून्य;
	पूर्ण
	/* Dequeue jobs not yet fired as well */
	pl08x_मुक्त_txd_list(pl08x, plchan);

	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pl08x_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);

	vchan_synchronize(&plchan->vc);
पूर्ण

अटल पूर्णांक pl08x_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	अचिन्हित दीर्घ flags;

	/*
	 * Anything succeeds on channels with no physical allocation and
	 * no queued transfers.
	 */
	spin_lock_irqsave(&plchan->vc.lock, flags);
	अगर (!plchan->phychan && !plchan->at) अणु
		spin_unlock_irqrestore(&plchan->vc.lock, flags);
		वापस 0;
	पूर्ण

	pl08x_छोड़ो_phy_chan(plchan->phychan);
	plchan->state = PL08X_CHAN_PAUSED;

	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pl08x_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);
	अचिन्हित दीर्घ flags;

	/*
	 * Anything succeeds on channels with no physical allocation and
	 * no queued transfers.
	 */
	spin_lock_irqsave(&plchan->vc.lock, flags);
	अगर (!plchan->phychan && !plchan->at) अणु
		spin_unlock_irqrestore(&plchan->vc.lock, flags);
		वापस 0;
	पूर्ण

	pl08x_resume_phy_chan(plchan->phychan);
	plchan->state = PL08X_CHAN_RUNNING;

	spin_unlock_irqrestore(&plchan->vc.lock, flags);

	वापस 0;
पूर्ण

bool pl08x_filter_id(काष्ठा dma_chan *chan, व्योम *chan_id)
अणु
	काष्ठा pl08x_dma_chan *plchan;
	अक्षर *name = chan_id;

	/* Reject channels क्रम devices not bound to this driver */
	अगर (chan->device->dev->driver != &pl08x_amba_driver.drv)
		वापस false;

	plchan = to_pl08x_chan(chan);

	/* Check that the channel is not taken! */
	अगर (!म_भेद(plchan->name, name))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(pl08x_filter_id);

अटल bool pl08x_filter_fn(काष्ठा dma_chan *chan, व्योम *chan_id)
अणु
	काष्ठा pl08x_dma_chan *plchan = to_pl08x_chan(chan);

	वापस plchan->cd == chan_id;
पूर्ण

/*
 * Just check that the device is there and active
 * TODO: turn this bit on/off depending on the number of physical channels
 * actually used, अगर it is zero... well shut it off. That will save some
 * घातer. Cut the घड़ी at the same समय.
 */
अटल व्योम pl08x_ensure_on(काष्ठा pl08x_driver_data *pl08x)
अणु
	/* The Nomadik variant करोes not have the config रेजिस्टर */
	अगर (pl08x->vd->nomadik)
		वापस;
	/* The FTDMAC020 variant करोes this in another रेजिस्टर */
	अगर (pl08x->vd->ftdmac020) अणु
		ग_लिखोl(PL080_CONFIG_ENABLE, pl08x->base + FTDMAC020_CSR);
		वापस;
	पूर्ण
	ग_लिखोl(PL080_CONFIG_ENABLE, pl08x->base + PL080_CONFIG);
पूर्ण

अटल irqवापस_t pl08x_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा pl08x_driver_data *pl08x = dev;
	u32 mask = 0, err, tc, i;

	/* check & clear - ERR & TC पूर्णांकerrupts */
	err = पढ़ोl(pl08x->base + PL080_ERR_STATUS);
	अगर (err) अणु
		dev_err(&pl08x->adev->dev, "%s error interrupt, register value 0x%08x\n",
			__func__, err);
		ग_लिखोl(err, pl08x->base + PL080_ERR_CLEAR);
	पूर्ण
	tc = पढ़ोl(pl08x->base + PL080_TC_STATUS);
	अगर (tc)
		ग_लिखोl(tc, pl08x->base + PL080_TC_CLEAR);

	अगर (!err && !tc)
		वापस IRQ_NONE;

	क्रम (i = 0; i < pl08x->vd->channels; i++) अणु
		अगर ((BIT(i) & err) || (BIT(i) & tc)) अणु
			/* Locate physical channel */
			काष्ठा pl08x_phy_chan *phychan = &pl08x->phy_chans[i];
			काष्ठा pl08x_dma_chan *plchan = phychan->serving;
			काष्ठा pl08x_txd *tx;

			अगर (!plchan) अणु
				dev_err(&pl08x->adev->dev,
					"%s Error TC interrupt on unused channel: 0x%08x\n",
					__func__, i);
				जारी;
			पूर्ण

			spin_lock(&plchan->vc.lock);
			tx = plchan->at;
			अगर (tx && tx->cyclic) अणु
				vchan_cyclic_callback(&tx->vd);
			पूर्ण अन्यथा अगर (tx) अणु
				plchan->at = शून्य;
				/*
				 * This descriptor is करोne, release its mux
				 * reservation.
				 */
				pl08x_release_mux(plchan);
				tx->करोne = true;
				vchan_cookie_complete(&tx->vd);

				/*
				 * And start the next descriptor (अगर any),
				 * otherwise मुक्त this channel.
				 */
				अगर (vchan_next_desc(&plchan->vc))
					pl08x_start_next_txd(plchan);
				अन्यथा
					pl08x_phy_मुक्त(plchan);
			पूर्ण
			spin_unlock(&plchan->vc.lock);

			mask |= BIT(i);
		पूर्ण
	पूर्ण

	वापस mask ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम pl08x_dma_slave_init(काष्ठा pl08x_dma_chan *chan)
अणु
	chan->slave = true;
	chan->name = chan->cd->bus_id;
	chan->cfg.src_addr = chan->cd->addr;
	chan->cfg.dst_addr = chan->cd->addr;
पूर्ण

/*
 * Initialise the DMAC स_नकल/slave channels.
 * Make a local wrapper to hold required data
 */
अटल पूर्णांक pl08x_dma_init_भव_channels(काष्ठा pl08x_driver_data *pl08x,
		काष्ठा dma_device *dmadev, अचिन्हित पूर्णांक channels, bool slave)
अणु
	काष्ठा pl08x_dma_chan *chan;
	पूर्णांक i;

	INIT_LIST_HEAD(&dmadev->channels);

	/*
	 * Register as many many स_नकल as we have physical channels,
	 * we won't always be able to use all but the code will have
	 * to cope with that situation.
	 */
	क्रम (i = 0; i < channels; i++) अणु
		chan = kzalloc(माप(*chan), GFP_KERNEL);
		अगर (!chan)
			वापस -ENOMEM;

		chan->host = pl08x;
		chan->state = PL08X_CHAN_IDLE;
		chan->संकेत = -1;

		अगर (slave) अणु
			chan->cd = &pl08x->pd->slave_channels[i];
			/*
			 * Some implementations have muxed संकेतs, whereas some
			 * use a mux in front of the संकेतs and need dynamic
			 * assignment of संकेतs.
			 */
			chan->संकेत = i;
			pl08x_dma_slave_init(chan);
		पूर्ण अन्यथा अणु
			chan->cd = kzalloc(माप(*chan->cd), GFP_KERNEL);
			अगर (!chan->cd) अणु
				kमुक्त(chan);
				वापस -ENOMEM;
			पूर्ण
			chan->cd->bus_id = "memcpy";
			chan->cd->periph_buses = pl08x->pd->mem_buses;
			chan->name = kaप्र_लिखो(GFP_KERNEL, "memcpy%d", i);
			अगर (!chan->name) अणु
				kमुक्त(chan->cd);
				kमुक्त(chan);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		dev_dbg(&pl08x->adev->dev,
			 "initialize virtual channel \"%s\"\n",
			 chan->name);

		chan->vc.desc_मुक्त = pl08x_desc_मुक्त;
		vchan_init(&chan->vc, dmadev);
	पूर्ण
	dev_info(&pl08x->adev->dev, "initialized %d virtual %s channels\n",
		 i, slave ? "slave" : "memcpy");
	वापस i;
पूर्ण

अटल व्योम pl08x_मुक्त_भव_channels(काष्ठा dma_device *dmadev)
अणु
	काष्ठा pl08x_dma_chan *chan = शून्य;
	काष्ठा pl08x_dma_chan *next;

	list_क्रम_each_entry_safe(chan,
				 next, &dmadev->channels, vc.chan.device_node) अणु
		list_del(&chan->vc.chan.device_node);
		kमुक्त(chan);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर अक्षर *pl08x_state_str(क्रमागत pl08x_dma_chan_state state)
अणु
	चयन (state) अणु
	हाल PL08X_CHAN_IDLE:
		वापस "idle";
	हाल PL08X_CHAN_RUNNING:
		वापस "running";
	हाल PL08X_CHAN_PAUSED:
		वापस "paused";
	हाल PL08X_CHAN_WAITING:
		वापस "waiting";
	शेष:
		अवरोध;
	पूर्ण
	वापस "UNKNOWN STATE";
पूर्ण

अटल पूर्णांक pl08x_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा pl08x_driver_data *pl08x = s->निजी;
	काष्ठा pl08x_dma_chan *chan;
	काष्ठा pl08x_phy_chan *ch;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	seq_म_लिखो(s, "PL08x physical channels:\n");
	seq_म_लिखो(s, "CHANNEL:\tUSER:\n");
	seq_म_लिखो(s, "--------\t-----\n");
	क्रम (i = 0; i < pl08x->vd->channels; i++) अणु
		काष्ठा pl08x_dma_chan *virt_chan;

		ch = &pl08x->phy_chans[i];

		spin_lock_irqsave(&ch->lock, flags);
		virt_chan = ch->serving;

		seq_म_लिखो(s, "%d\t\t%s%s\n",
			   ch->id,
			   virt_chan ? virt_chan->name : "(none)",
			   ch->locked ? " LOCKED" : "");

		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण

	seq_म_लिखो(s, "\nPL08x virtual memcpy channels:\n");
	seq_म_लिखो(s, "CHANNEL:\tSTATE:\n");
	seq_म_लिखो(s, "--------\t------\n");
	list_क्रम_each_entry(chan, &pl08x->स_नकल.channels, vc.chan.device_node) अणु
		seq_म_लिखो(s, "%s\t\t%s\n", chan->name,
			   pl08x_state_str(chan->state));
	पूर्ण

	अगर (pl08x->has_slave) अणु
		seq_म_लिखो(s, "\nPL08x virtual slave channels:\n");
		seq_म_लिखो(s, "CHANNEL:\tSTATE:\n");
		seq_म_लिखो(s, "--------\t------\n");
		list_क्रम_each_entry(chan, &pl08x->slave.channels,
				    vc.chan.device_node) अणु
			seq_म_लिखो(s, "%s\t\t%s\n", chan->name,
				   pl08x_state_str(chan->state));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pl08x_debugfs);

अटल व्योम init_pl08x_debugfs(काष्ठा pl08x_driver_data *pl08x)
अणु
	/* Expose a simple debugfs पूर्णांकerface to view all घड़ीs */
	debugfs_create_file(dev_name(&pl08x->adev->dev), S_IFREG | S_IRUGO,
			    शून्य, pl08x, &pl08x_debugfs_fops);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम init_pl08x_debugfs(काष्ठा pl08x_driver_data *pl08x)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल काष्ठा dma_chan *pl08x_find_chan_id(काष्ठा pl08x_driver_data *pl08x,
					 u32 id)
अणु
	काष्ठा pl08x_dma_chan *chan;

	/* Trying to get a slave channel from something with no slave support */
	अगर (!pl08x->has_slave)
		वापस शून्य;

	list_क्रम_each_entry(chan, &pl08x->slave.channels, vc.chan.device_node) अणु
		अगर (chan->संकेत == id)
			वापस &chan->vc.chan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_chan *pl08x_of_xlate(काष्ठा of_phandle_args *dma_spec,
				       काष्ठा of_dma *ofdma)
अणु
	काष्ठा pl08x_driver_data *pl08x = ofdma->of_dma_data;
	काष्ठा dma_chan *dma_chan;
	काष्ठा pl08x_dma_chan *plchan;

	अगर (!pl08x)
		वापस शून्य;

	अगर (dma_spec->args_count != 2) अणु
		dev_err(&pl08x->adev->dev,
			"DMA channel translation requires two cells\n");
		वापस शून्य;
	पूर्ण

	dma_chan = pl08x_find_chan_id(pl08x, dma_spec->args[0]);
	अगर (!dma_chan) अणु
		dev_err(&pl08x->adev->dev,
			"DMA slave channel not found\n");
		वापस शून्य;
	पूर्ण

	plchan = to_pl08x_chan(dma_chan);
	dev_dbg(&pl08x->adev->dev,
		"translated channel for signal %d\n",
		dma_spec->args[0]);

	/* Augment channel data क्रम applicable AHB buses */
	plchan->cd->periph_buses = dma_spec->args[1];
	वापस dma_get_slave_channel(dma_chan);
पूर्ण

अटल पूर्णांक pl08x_of_probe(काष्ठा amba_device *adev,
			  काष्ठा pl08x_driver_data *pl08x,
			  काष्ठा device_node *np)
अणु
	काष्ठा pl08x_platक्रमm_data *pd;
	काष्ठा pl08x_channel_data *chanp = शून्य;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	pd = devm_kzalloc(&adev->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	/* Eligible bus masters क्रम fetching LLIs */
	अगर (of_property_पढ़ो_bool(np, "lli-bus-interface-ahb1"))
		pd->lli_buses |= PL08X_AHB1;
	अगर (of_property_पढ़ो_bool(np, "lli-bus-interface-ahb2"))
		pd->lli_buses |= PL08X_AHB2;
	अगर (!pd->lli_buses) अणु
		dev_info(&adev->dev, "no bus masters for LLIs stated, assume all\n");
		pd->lli_buses |= PL08X_AHB1 | PL08X_AHB2;
	पूर्ण

	/* Eligible bus masters क्रम memory access */
	अगर (of_property_पढ़ो_bool(np, "mem-bus-interface-ahb1"))
		pd->mem_buses |= PL08X_AHB1;
	अगर (of_property_पढ़ो_bool(np, "mem-bus-interface-ahb2"))
		pd->mem_buses |= PL08X_AHB2;
	अगर (!pd->mem_buses) अणु
		dev_info(&adev->dev, "no bus masters for memory stated, assume all\n");
		pd->mem_buses |= PL08X_AHB1 | PL08X_AHB2;
	पूर्ण

	/* Parse the स_नकल channel properties */
	ret = of_property_पढ़ो_u32(np, "memcpy-burst-size", &val);
	अगर (ret) अणु
		dev_info(&adev->dev, "no memcpy burst size specified, using 1 byte\n");
		val = 1;
	पूर्ण
	चयन (val) अणु
	शेष:
		dev_err(&adev->dev, "illegal burst size for memcpy, set to 1\n");
		fallthrough;
	हाल 1:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_1;
		अवरोध;
	हाल 4:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_4;
		अवरोध;
	हाल 8:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_8;
		अवरोध;
	हाल 16:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_16;
		अवरोध;
	हाल 32:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_32;
		अवरोध;
	हाल 64:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_64;
		अवरोध;
	हाल 128:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_128;
		अवरोध;
	हाल 256:
		pd->स_नकल_burst_size = PL08X_BURST_SZ_256;
		अवरोध;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "memcpy-bus-width", &val);
	अगर (ret) अणु
		dev_info(&adev->dev, "no memcpy bus width specified, using 8 bits\n");
		val = 8;
	पूर्ण
	चयन (val) अणु
	शेष:
		dev_err(&adev->dev, "illegal bus width for memcpy, set to 8 bits\n");
		fallthrough;
	हाल 8:
		pd->स_नकल_bus_width = PL08X_BUS_WIDTH_8_BITS;
		अवरोध;
	हाल 16:
		pd->स_नकल_bus_width = PL08X_BUS_WIDTH_16_BITS;
		अवरोध;
	हाल 32:
		pd->स_नकल_bus_width = PL08X_BUS_WIDTH_32_BITS;
		अवरोध;
	पूर्ण

	/*
	 * Allocate channel data क्रम all possible slave channels (one
	 * क्रम each possible संकेत), channels will then be allocated
	 * क्रम a device and have it's AHB पूर्णांकerfaces set up at
	 * translation समय.
	 */
	अगर (pl08x->vd->संकेतs) अणु
		chanp = devm_kसुस्मृति(&adev->dev,
				     pl08x->vd->संकेतs,
				     माप(काष्ठा pl08x_channel_data),
				     GFP_KERNEL);
		अगर (!chanp)
			वापस -ENOMEM;

		pd->slave_channels = chanp;
		क्रम (i = 0; i < pl08x->vd->संकेतs; i++) अणु
			/*
			 * chanp->periph_buses will be asचिन्हित at translation
			 */
			chanp->bus_id = kaप्र_लिखो(GFP_KERNEL, "slave%d", i);
			chanp++;
		पूर्ण
		pd->num_slave_channels = pl08x->vd->संकेतs;
	पूर्ण

	pl08x->pd = pd;

	वापस of_dma_controller_रेजिस्टर(adev->dev.of_node, pl08x_of_xlate,
					  pl08x);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pl08x_of_probe(काष्ठा amba_device *adev,
				 काष्ठा pl08x_driver_data *pl08x,
				 काष्ठा device_node *np)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pl08x_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा pl08x_driver_data *pl08x;
	काष्ठा venकरोr_data *vd = id->data;
	काष्ठा device_node *np = adev->dev.of_node;
	u32 tsfr_size;
	पूर्णांक ret = 0;
	पूर्णांक i;

	ret = amba_request_regions(adev, शून्य);
	अगर (ret)
		वापस ret;

	/* Ensure that we can करो DMA */
	ret = dma_set_mask_and_coherent(&adev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ out_no_pl08x;

	/* Create the driver state holder */
	pl08x = kzalloc(माप(*pl08x), GFP_KERNEL);
	अगर (!pl08x) अणु
		ret = -ENOMEM;
		जाओ out_no_pl08x;
	पूर्ण

	/* Assign useful poपूर्णांकers to the driver state */
	pl08x->adev = adev;
	pl08x->vd = vd;

	pl08x->base = ioremap(adev->res.start, resource_size(&adev->res));
	अगर (!pl08x->base) अणु
		ret = -ENOMEM;
		जाओ out_no_ioremap;
	पूर्ण

	अगर (vd->ftdmac020) अणु
		u32 val;

		val = पढ़ोl(pl08x->base + FTDMAC020_REVISION);
		dev_info(&pl08x->adev->dev, "FTDMAC020 %d.%d rel %d\n",
			 (val >> 16) & 0xff, (val >> 8) & 0xff, val & 0xff);
		val = पढ़ोl(pl08x->base + FTDMAC020_FEATURE);
		dev_info(&pl08x->adev->dev, "FTDMAC020 %d channels, "
			 "%s built-in bridge, %s, %s linked lists\n",
			 (val >> 12) & 0x0f,
			 (val & BIT(10)) ? "no" : "has",
			 (val & BIT(9)) ? "AHB0 and AHB1" : "AHB0",
			 (val & BIT(8)) ? "supports" : "does not support");

		/* Venकरोr data from feature रेजिस्टर */
		अगर (!(val & BIT(8)))
			dev_warn(&pl08x->adev->dev,
				 "linked lists not supported, required\n");
		vd->channels = (val >> 12) & 0x0f;
		vd->dualmaster = !!(val & BIT(9));
	पूर्ण

	/* Initialize स_नकल engine */
	dma_cap_set(DMA_MEMCPY, pl08x->स_नकल.cap_mask);
	pl08x->स_नकल.dev = &adev->dev;
	pl08x->स_नकल.device_मुक्त_chan_resources = pl08x_मुक्त_chan_resources;
	pl08x->स_नकल.device_prep_dma_स_नकल = pl08x_prep_dma_स_नकल;
	pl08x->स_नकल.device_prep_dma_पूर्णांकerrupt = pl08x_prep_dma_पूर्णांकerrupt;
	pl08x->स_नकल.device_tx_status = pl08x_dma_tx_status;
	pl08x->स_नकल.device_issue_pending = pl08x_issue_pending;
	pl08x->स_नकल.device_config = pl08x_config;
	pl08x->स_नकल.device_छोड़ो = pl08x_छोड़ो;
	pl08x->स_नकल.device_resume = pl08x_resume;
	pl08x->स_नकल.device_terminate_all = pl08x_terminate_all;
	pl08x->स_नकल.device_synchronize = pl08x_synchronize;
	pl08x->स_नकल.src_addr_widths = PL80X_DMA_BUSWIDTHS;
	pl08x->स_नकल.dst_addr_widths = PL80X_DMA_BUSWIDTHS;
	pl08x->स_नकल.directions = BIT(DMA_MEM_TO_MEM);
	pl08x->स_नकल.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	अगर (vd->ftdmac020)
		pl08x->स_नकल.copy_align = DMAENGINE_ALIGN_4_BYTES;


	/*
	 * Initialize slave engine, अगर the block has no संकेतs, that means
	 * we have no slave support.
	 */
	अगर (vd->संकेतs) अणु
		pl08x->has_slave = true;
		dma_cap_set(DMA_SLAVE, pl08x->slave.cap_mask);
		dma_cap_set(DMA_CYCLIC, pl08x->slave.cap_mask);
		pl08x->slave.dev = &adev->dev;
		pl08x->slave.device_मुक्त_chan_resources =
			pl08x_मुक्त_chan_resources;
		pl08x->slave.device_prep_dma_पूर्णांकerrupt =
			pl08x_prep_dma_पूर्णांकerrupt;
		pl08x->slave.device_tx_status = pl08x_dma_tx_status;
		pl08x->slave.device_issue_pending = pl08x_issue_pending;
		pl08x->slave.device_prep_slave_sg = pl08x_prep_slave_sg;
		pl08x->slave.device_prep_dma_cyclic = pl08x_prep_dma_cyclic;
		pl08x->slave.device_config = pl08x_config;
		pl08x->slave.device_छोड़ो = pl08x_छोड़ो;
		pl08x->slave.device_resume = pl08x_resume;
		pl08x->slave.device_terminate_all = pl08x_terminate_all;
		pl08x->slave.device_synchronize = pl08x_synchronize;
		pl08x->slave.src_addr_widths = PL80X_DMA_BUSWIDTHS;
		pl08x->slave.dst_addr_widths = PL80X_DMA_BUSWIDTHS;
		pl08x->slave.directions =
			BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
		pl08x->slave.residue_granularity =
			DMA_RESIDUE_GRANULARITY_SEGMENT;
	पूर्ण

	/* Get the platक्रमm data */
	pl08x->pd = dev_get_platdata(&adev->dev);
	अगर (!pl08x->pd) अणु
		अगर (np) अणु
			ret = pl08x_of_probe(adev, pl08x, np);
			अगर (ret)
				जाओ out_no_platdata;
		पूर्ण अन्यथा अणु
			dev_err(&adev->dev, "no platform data supplied\n");
			ret = -EINVAL;
			जाओ out_no_platdata;
		पूर्ण
	पूर्ण अन्यथा अणु
		pl08x->slave.filter.map = pl08x->pd->slave_map;
		pl08x->slave.filter.mapcnt = pl08x->pd->slave_map_len;
		pl08x->slave.filter.fn = pl08x_filter_fn;
	पूर्ण

	/* By शेष, AHB1 only.  If dualmaster, from platक्रमm */
	pl08x->lli_buses = PL08X_AHB1;
	pl08x->mem_buses = PL08X_AHB1;
	अगर (pl08x->vd->dualmaster) अणु
		pl08x->lli_buses = pl08x->pd->lli_buses;
		pl08x->mem_buses = pl08x->pd->mem_buses;
	पूर्ण

	अगर (vd->pl080s)
		pl08x->lli_words = PL080S_LLI_WORDS;
	अन्यथा
		pl08x->lli_words = PL080_LLI_WORDS;
	tsfr_size = MAX_NUM_TSFR_LLIS * pl08x->lli_words * माप(u32);

	/* A DMA memory pool क्रम LLIs, align on 1-byte boundary */
	pl08x->pool = dma_pool_create(DRIVER_NAME, &pl08x->adev->dev,
						tsfr_size, PL08X_ALIGN, 0);
	अगर (!pl08x->pool) अणु
		ret = -ENOMEM;
		जाओ out_no_lli_pool;
	पूर्ण

	/* Turn on the PL08x */
	pl08x_ensure_on(pl08x);

	/* Clear any pending पूर्णांकerrupts */
	अगर (vd->ftdmac020)
		/* This variant has error IRQs in bits 16-19 */
		ग_लिखोl(0x0000FFFF, pl08x->base + PL080_ERR_CLEAR);
	अन्यथा
		ग_लिखोl(0x000000FF, pl08x->base + PL080_ERR_CLEAR);
	ग_लिखोl(0x000000FF, pl08x->base + PL080_TC_CLEAR);

	/* Attach the पूर्णांकerrupt handler */
	ret = request_irq(adev->irq[0], pl08x_irq, 0, DRIVER_NAME, pl08x);
	अगर (ret) अणु
		dev_err(&adev->dev, "%s failed to request interrupt %d\n",
			__func__, adev->irq[0]);
		जाओ out_no_irq;
	पूर्ण

	/* Initialize physical channels */
	pl08x->phy_chans = kzalloc((vd->channels * माप(*pl08x->phy_chans)),
			GFP_KERNEL);
	अगर (!pl08x->phy_chans) अणु
		ret = -ENOMEM;
		जाओ out_no_phychans;
	पूर्ण

	क्रम (i = 0; i < vd->channels; i++) अणु
		काष्ठा pl08x_phy_chan *ch = &pl08x->phy_chans[i];

		ch->id = i;
		ch->base = pl08x->base + PL080_Cx_BASE(i);
		अगर (vd->ftdmac020) अणु
			/* FTDMA020 has a special channel busy रेजिस्टर */
			ch->reg_busy = ch->base + FTDMAC020_CH_BUSY;
			ch->reg_config = ch->base + FTDMAC020_CH_CFG;
			ch->reg_control = ch->base + FTDMAC020_CH_CSR;
			ch->reg_src = ch->base + FTDMAC020_CH_SRC_ADDR;
			ch->reg_dst = ch->base + FTDMAC020_CH_DST_ADDR;
			ch->reg_lli = ch->base + FTDMAC020_CH_LLP;
			ch->ftdmac020 = true;
		पूर्ण अन्यथा अणु
			ch->reg_config = ch->base + vd->config_offset;
			ch->reg_control = ch->base + PL080_CH_CONTROL;
			ch->reg_src = ch->base + PL080_CH_SRC_ADDR;
			ch->reg_dst = ch->base + PL080_CH_DST_ADDR;
			ch->reg_lli = ch->base + PL080_CH_LLI;
		पूर्ण
		अगर (vd->pl080s)
			ch->pl080s = true;

		spin_lock_init(&ch->lock);

		/*
		 * Nomadik variants can have channels that are locked
		 * करोwn क्रम the secure world only. Lock up these channels
		 * by perpetually serving a dummy भव channel.
		 */
		अगर (vd->nomadik) अणु
			u32 val;

			val = पढ़ोl(ch->reg_config);
			अगर (val & (PL080N_CONFIG_ITPROT | PL080N_CONFIG_SECPROT)) अणु
				dev_info(&adev->dev, "physical channel %d reserved for secure access only\n", i);
				ch->locked = true;
			पूर्ण
		पूर्ण

		dev_dbg(&adev->dev, "physical channel %d is %s\n",
			i, pl08x_phy_channel_busy(ch) ? "BUSY" : "FREE");
	पूर्ण

	/* Register as many स_नकल channels as there are physical channels */
	ret = pl08x_dma_init_भव_channels(pl08x, &pl08x->स_नकल,
					      pl08x->vd->channels, false);
	अगर (ret <= 0) अणु
		dev_warn(&pl08x->adev->dev,
			 "%s failed to enumerate memcpy channels - %d\n",
			 __func__, ret);
		जाओ out_no_स_नकल;
	पूर्ण

	/* Register slave channels */
	अगर (pl08x->has_slave) अणु
		ret = pl08x_dma_init_भव_channels(pl08x, &pl08x->slave,
					pl08x->pd->num_slave_channels, true);
		अगर (ret < 0) अणु
			dev_warn(&pl08x->adev->dev,
				 "%s failed to enumerate slave channels - %d\n",
				 __func__, ret);
			जाओ out_no_slave;
		पूर्ण
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&pl08x->स_नकल);
	अगर (ret) अणु
		dev_warn(&pl08x->adev->dev,
			"%s failed to register memcpy as an async device - %d\n",
			__func__, ret);
		जाओ out_no_स_नकल_reg;
	पूर्ण

	अगर (pl08x->has_slave) अणु
		ret = dma_async_device_रेजिस्टर(&pl08x->slave);
		अगर (ret) अणु
			dev_warn(&pl08x->adev->dev,
			"%s failed to register slave as an async device - %d\n",
			__func__, ret);
			जाओ out_no_slave_reg;
		पूर्ण
	पूर्ण

	amba_set_drvdata(adev, pl08x);
	init_pl08x_debugfs(pl08x);
	dev_info(&pl08x->adev->dev, "DMA: PL%03x%s rev%u at 0x%08llx irq %d\n",
		 amba_part(adev), pl08x->vd->pl080s ? "s" : "", amba_rev(adev),
		 (अचिन्हित दीर्घ दीर्घ)adev->res.start, adev->irq[0]);

	वापस 0;

out_no_slave_reg:
	dma_async_device_unरेजिस्टर(&pl08x->स_नकल);
out_no_स_नकल_reg:
	अगर (pl08x->has_slave)
		pl08x_मुक्त_भव_channels(&pl08x->slave);
out_no_slave:
	pl08x_मुक्त_भव_channels(&pl08x->स_नकल);
out_no_स_नकल:
	kमुक्त(pl08x->phy_chans);
out_no_phychans:
	मुक्त_irq(adev->irq[0], pl08x);
out_no_irq:
	dma_pool_destroy(pl08x->pool);
out_no_lli_pool:
out_no_platdata:
	iounmap(pl08x->base);
out_no_ioremap:
	kमुक्त(pl08x);
out_no_pl08x:
	amba_release_regions(adev);
	वापस ret;
पूर्ण

/* PL080 has 8 channels and the PL080 have just 2 */
अटल काष्ठा venकरोr_data venकरोr_pl080 = अणु
	.config_offset = PL080_CH_CONFIG,
	.channels = 8,
	.संकेतs = 16,
	.dualmaster = true,
	.max_transfer_size = PL080_CONTROL_TRANSFER_SIZE_MASK,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_nomadik = अणु
	.config_offset = PL080_CH_CONFIG,
	.channels = 8,
	.संकेतs = 32,
	.dualmaster = true,
	.nomadik = true,
	.max_transfer_size = PL080_CONTROL_TRANSFER_SIZE_MASK,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_pl080s = अणु
	.config_offset = PL080S_CH_CONFIG,
	.channels = 8,
	.संकेतs = 32,
	.pl080s = true,
	.max_transfer_size = PL080S_CONTROL_TRANSFER_SIZE_MASK,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_pl081 = अणु
	.config_offset = PL080_CH_CONFIG,
	.channels = 2,
	.संकेतs = 16,
	.dualmaster = false,
	.max_transfer_size = PL080_CONTROL_TRANSFER_SIZE_MASK,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_ftdmac020 = अणु
	.config_offset = PL080_CH_CONFIG,
	.ftdmac020 = true,
	.max_transfer_size = PL080_CONTROL_TRANSFER_SIZE_MASK,
पूर्ण;

अटल स्थिर काष्ठा amba_id pl08x_ids[] = अणु
	/* Samsung PL080S variant */
	अणु
		.id	= 0x0a141080,
		.mask	= 0xffffffff,
		.data	= &venकरोr_pl080s,
	पूर्ण,
	/* PL080 */
	अणु
		.id	= 0x00041080,
		.mask	= 0x000fffff,
		.data	= &venकरोr_pl080,
	पूर्ण,
	/* PL081 */
	अणु
		.id	= 0x00041081,
		.mask	= 0x000fffff,
		.data	= &venकरोr_pl081,
	पूर्ण,
	/* Nomadik 8815 PL080 variant */
	अणु
		.id	= 0x00280080,
		.mask	= 0x00ffffff,
		.data	= &venकरोr_nomadik,
	पूर्ण,
	/* Faraday Technology FTDMAC020 */
	अणु
		.id	= 0x0003b080,
		.mask	= 0x000fffff,
		.data	= &venकरोr_ftdmac020,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl08x_ids);

अटल काष्ठा amba_driver pl08x_amba_driver = अणु
	.drv.name	= DRIVER_NAME,
	.id_table	= pl08x_ids,
	.probe		= pl08x_probe,
पूर्ण;

अटल पूर्णांक __init pl08x_init(व्योम)
अणु
	पूर्णांक retval;
	retval = amba_driver_रेजिस्टर(&pl08x_amba_driver);
	अगर (retval)
		prपूर्णांकk(KERN_WARNING DRIVER_NAME
		       "failed to register as an AMBA device (%d)\n",
		       retval);
	वापस retval;
पूर्ण
subsys_initcall(pl08x_init);
