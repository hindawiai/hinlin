<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car Audio DMAC support
//
// Copyright (C) 2015 Renesas Electronics Corp.
// Copyright (c) 2015 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश <linux/delay.h>
#समावेश <linux/of_dma.h>
#समावेश "rsnd.h"

/*
 * Audio DMAC peri peri रेजिस्टर
 */
#घोषणा PDMASAR		0x00
#घोषणा PDMADAR		0x04
#घोषणा PDMACHCR	0x0c

/* PDMACHCR */
#घोषणा PDMACHCR_DE		(1 << 0)


काष्ठा rsnd_dmaen अणु
	काष्ठा dma_chan		*chan;
	dma_cookie_t		cookie;
	अचिन्हित पूर्णांक		dma_len;
पूर्ण;

काष्ठा rsnd_dmapp अणु
	पूर्णांक			dmapp_id;
	u32			chcr;
पूर्ण;

काष्ठा rsnd_dma अणु
	काष्ठा rsnd_mod		mod;
	काष्ठा rsnd_mod		*mod_from;
	काष्ठा rsnd_mod		*mod_to;
	dma_addr_t		src_addr;
	dma_addr_t		dst_addr;
	जोड़ अणु
		काष्ठा rsnd_dmaen en;
		काष्ठा rsnd_dmapp pp;
	पूर्ण dma;
पूर्ण;

काष्ठा rsnd_dma_ctrl अणु
	व्योम __iomem *base;
	पूर्णांक dmaen_num;
	पूर्णांक dmapp_num;
पूर्ण;

#घोषणा rsnd_priv_to_dmac(p)	((काष्ठा rsnd_dma_ctrl *)(p)->dma)
#घोषणा rsnd_mod_to_dma(_mod) container_of((_mod), काष्ठा rsnd_dma, mod)
#घोषणा rsnd_dma_to_dmaen(dma)	(&(dma)->dma.en)
#घोषणा rsnd_dma_to_dmapp(dma)	(&(dma)->dma.pp)

/* क्रम DEBUG */
अटल काष्ठा rsnd_mod_ops mem_ops = अणु
	.name = "mem",
पूर्ण;

अटल काष्ठा rsnd_mod mem = अणु
पूर्ण;

/*
 *		Audio DMAC
 */
अटल व्योम __rsnd_dmaen_complete(काष्ठा rsnd_mod *mod,
				  काष्ठा rsnd_dai_stream *io)
अणु
	अगर (rsnd_io_is_working(io))
		rsnd_dai_period_elapsed(io);
पूर्ण

अटल व्योम rsnd_dmaen_complete(व्योम *data)
अणु
	काष्ठा rsnd_mod *mod = data;

	rsnd_mod_पूर्णांकerrupt(mod, __rsnd_dmaen_complete);
पूर्ण

अटल काष्ठा dma_chan *rsnd_dmaen_request_channel(काष्ठा rsnd_dai_stream *io,
						   काष्ठा rsnd_mod *mod_from,
						   काष्ठा rsnd_mod *mod_to)
अणु
	अगर ((!mod_from && !mod_to) ||
	    (mod_from && mod_to))
		वापस शून्य;

	अगर (mod_from)
		वापस rsnd_mod_dma_req(io, mod_from);
	अन्यथा
		वापस rsnd_mod_dma_req(io, mod_to);
पूर्ण

अटल पूर्णांक rsnd_dmaen_stop(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);

	अगर (dmaen->chan)
		dmaengine_terminate_all(dmaen->chan);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dmaen_cleanup(काष्ठा rsnd_mod *mod,
			      काष्ठा rsnd_dai_stream *io,
			      काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);

	/*
	 * DMAEngine release uses mutex lock.
	 * Thus, it shouldn't be called under spinlock.
	 * Let's call it under prepare
	 */
	अगर (dmaen->chan)
		dma_release_channel(dmaen->chan);

	dmaen->chan = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dmaen_prepare(काष्ठा rsnd_mod *mod,
			      काष्ठा rsnd_dai_stream *io,
			      काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	/* maybe suspended */
	अगर (dmaen->chan)
		वापस 0;

	/*
	 * DMAEngine request uses mutex lock.
	 * Thus, it shouldn't be called under spinlock.
	 * Let's call it under prepare
	 */
	dmaen->chan = rsnd_dmaen_request_channel(io,
						 dma->mod_from,
						 dma->mod_to);
	अगर (IS_ERR_OR_शून्य(dmaen->chan)) अणु
		dmaen->chan = शून्य;
		dev_err(dev, "can't get dma channel\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dmaen_start(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	काष्ठा snd_pcm_substream *substream = io->substream;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config cfg = अणुपूर्ण;
	क्रमागत dma_slave_buswidth buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्णांक is_play = rsnd_io_is_play(io);
	पूर्णांक ret;

	/*
	 * in हाल of monaural data writing or पढ़ोing through Audio-DMAC
	 * data is always in Left Justअगरied क्रमmat, so both src and dst
	 * DMA Bus width need to be set equal to physical data width.
	 */
	अगर (rsnd_runसमय_channel_original(io) == 1) अणु
		काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
		पूर्णांक bits = snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat);

		चयन (bits) अणु
		हाल 8:
			buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
			अवरोध;
		हाल 16:
			buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
			अवरोध;
		हाल 32:
			buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
			अवरोध;
		शेष:
			dev_err(dev, "invalid format width %d\n", bits);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	cfg.direction	= is_play ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	cfg.src_addr	= dma->src_addr;
	cfg.dst_addr	= dma->dst_addr;
	cfg.src_addr_width = buswidth;
	cfg.dst_addr_width = buswidth;

	dev_dbg(dev, "%s %pad -> %pad\n",
		rsnd_mod_name(mod),
		&cfg.src_addr, &cfg.dst_addr);

	ret = dmaengine_slave_config(dmaen->chan, &cfg);
	अगर (ret < 0)
		वापस ret;

	desc = dmaengine_prep_dma_cyclic(dmaen->chan,
					 substream->runसमय->dma_addr,
					 snd_pcm_lib_buffer_bytes(substream),
					 snd_pcm_lib_period_bytes(substream),
					 is_play ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!desc) अणु
		dev_err(dev, "dmaengine_prep_slave_sg() fail\n");
		वापस -EIO;
	पूर्ण

	desc->callback		= rsnd_dmaen_complete;
	desc->callback_param	= rsnd_mod_get(dma);

	dmaen->dma_len		= snd_pcm_lib_buffer_bytes(substream);

	dmaen->cookie = dmaengine_submit(desc);
	अगर (dmaen->cookie < 0) अणु
		dev_err(dev, "dmaengine_submit() fail\n");
		वापस -EIO;
	पूर्ण

	dma_async_issue_pending(dmaen->chan);

	वापस 0;
पूर्ण

काष्ठा dma_chan *rsnd_dma_request_channel(काष्ठा device_node *of_node,
					  काष्ठा rsnd_mod *mod, अक्षर *name)
अणु
	काष्ठा dma_chan *chan = शून्य;
	काष्ठा device_node *np;
	पूर्णांक i = 0;

	क्रम_each_child_of_node(of_node, np) अणु
		अगर (i == rsnd_mod_id_raw(mod) && (!chan))
			chan = of_dma_request_slave_channel(np, name);
		i++;
	पूर्ण

	/* It should call of_node_put(), since, it is rsnd_xxx_of_node() */
	of_node_put(of_node);

	वापस chan;
पूर्ण

अटल पूर्णांक rsnd_dmaen_attach(काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_dma *dma,
			   काष्ठा rsnd_mod *mod_from, काष्ठा rsnd_mod *mod_to)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);
	काष्ठा dma_chan *chan;

	/* try to get DMAEngine channel */
	chan = rsnd_dmaen_request_channel(io, mod_from, mod_to);
	अगर (IS_ERR_OR_शून्य(chan)) अणु
		/* Let's follow when -EPROBE_DEFER हाल */
		अगर (PTR_ERR(chan) == -EPROBE_DEFER)
			वापस PTR_ERR(chan);

		/*
		 * DMA failed. try to PIO mode
		 * see
		 *	rsnd_ssi_fallback()
		 *	rsnd_rdai_continuance_probe()
		 */
		वापस -EAGAIN;
	पूर्ण

	/*
	 * use it क्रम IPMMU अगर needed
	 * see
	 *	rsnd_pपुनः_स्मृतिate_pages()
	 */
	io->dmac_dev = chan->device->dev;

	dma_release_channel(chan);

	dmac->dmaen_num++;

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dmaen_poपूर्णांकer(काष्ठा rsnd_mod *mod,
			      काष्ठा rsnd_dai_stream *io,
			      snd_pcm_uframes_t *poपूर्णांकer)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	अचिन्हित पूर्णांक pos = 0;

	status = dmaengine_tx_status(dmaen->chan, dmaen->cookie, &state);
	अगर (status == DMA_IN_PROGRESS || status == DMA_PAUSED) अणु
		अगर (state.residue > 0 && state.residue <= dmaen->dma_len)
			pos = dmaen->dma_len - state.residue;
	पूर्ण
	*poपूर्णांकer = bytes_to_frames(runसमय, pos);

	वापस 0;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_dmaen_ops = अणु
	.name		= "audmac",
	.prepare	= rsnd_dmaen_prepare,
	.cleanup	= rsnd_dmaen_cleanup,
	.start		= rsnd_dmaen_start,
	.stop		= rsnd_dmaen_stop,
	.poपूर्णांकer	= rsnd_dmaen_poपूर्णांकer,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

/*
 *		Audio DMAC peri peri
 */
अटल स्थिर u8 gen2_id_table_ssiu[] = अणु
	/* SSI00 ~ SSI07 */
	0x00, 0x01, 0x02, 0x03, 0x39, 0x3a, 0x3b, 0x3c,
	/* SSI10 ~ SSI17 */
	0x04, 0x05, 0x06, 0x07, 0x3d, 0x3e, 0x3f, 0x40,
	/* SSI20 ~ SSI27 */
	0x08, 0x09, 0x0a, 0x0b, 0x41, 0x42, 0x43, 0x44,
	/* SSI30 ~ SSI37 */
	0x0c, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
	/* SSI40 ~ SSI47 */
	0x0d, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52,
	/* SSI5 */
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI6 */
	0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI7 */
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI8 */
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* SSI90 ~ SSI97 */
	0x12, 0x13, 0x14, 0x15, 0x53, 0x54, 0x55, 0x56,
पूर्ण;
अटल स्थिर u8 gen2_id_table_scu[] = अणु
	0x2d, /* SCU_SRCI0 */
	0x2e, /* SCU_SRCI1 */
	0x2f, /* SCU_SRCI2 */
	0x30, /* SCU_SRCI3 */
	0x31, /* SCU_SRCI4 */
	0x32, /* SCU_SRCI5 */
	0x33, /* SCU_SRCI6 */
	0x34, /* SCU_SRCI7 */
	0x35, /* SCU_SRCI8 */
	0x36, /* SCU_SRCI9 */
पूर्ण;
अटल स्थिर u8 gen2_id_table_cmd[] = अणु
	0x37, /* SCU_CMD0 */
	0x38, /* SCU_CMD1 */
पूर्ण;

अटल u32 rsnd_dmapp_get_id(काष्ठा rsnd_dai_stream *io,
			     काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_mod *ssi = rsnd_io_to_mod_ssi(io);
	काष्ठा rsnd_mod *ssiu = rsnd_io_to_mod_ssiu(io);
	काष्ठा rsnd_mod *src = rsnd_io_to_mod_src(io);
	काष्ठा rsnd_mod *dvc = rsnd_io_to_mod_dvc(io);
	स्थिर u8 *entry = शून्य;
	पूर्णांक id = 255;
	पूर्णांक size = 0;

	अगर ((mod == ssi) ||
	    (mod == ssiu)) अणु
		पूर्णांक busअगर = rsnd_mod_id_sub(ssiu);

		entry = gen2_id_table_ssiu;
		size = ARRAY_SIZE(gen2_id_table_ssiu);
		id = (rsnd_mod_id(mod) * 8) + busअगर;
	पूर्ण अन्यथा अगर (mod == src) अणु
		entry = gen2_id_table_scu;
		size = ARRAY_SIZE(gen2_id_table_scu);
		id = rsnd_mod_id(mod);
	पूर्ण अन्यथा अगर (mod == dvc) अणु
		entry = gen2_id_table_cmd;
		size = ARRAY_SIZE(gen2_id_table_cmd);
		id = rsnd_mod_id(mod);
	पूर्ण

	अगर ((!entry) || (size <= id)) अणु
		काष्ठा device *dev = rsnd_priv_to_dev(rsnd_io_to_priv(io));

		dev_err(dev, "unknown connection (%s)\n", rsnd_mod_name(mod));

		/* use non-prohibited SRS number as error */
		वापस 0x00; /* SSI00 */
	पूर्ण

	वापस entry[id];
पूर्ण

अटल u32 rsnd_dmapp_get_chcr(काष्ठा rsnd_dai_stream *io,
			       काष्ठा rsnd_mod *mod_from,
			       काष्ठा rsnd_mod *mod_to)
अणु
	वापस	(rsnd_dmapp_get_id(io, mod_from) << 24) +
		(rsnd_dmapp_get_id(io, mod_to) << 16);
पूर्ण

#घोषणा rsnd_dmapp_addr(dmac, dma, reg) \
	(dmac->base + 0x20 + reg + \
	 (0x10 * rsnd_dma_to_dmapp(dma)->dmapp_id))
अटल व्योम rsnd_dmapp_ग_लिखो(काष्ठा rsnd_dma *dma, u32 data, u32 reg)
अणु
	काष्ठा rsnd_mod *mod = rsnd_mod_get(dma);
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	dev_dbg(dev, "w 0x%px : %08x\n", rsnd_dmapp_addr(dmac, dma, reg), data);

	ioग_लिखो32(data, rsnd_dmapp_addr(dmac, dma, reg));
पूर्ण

अटल u32 rsnd_dmapp_पढ़ो(काष्ठा rsnd_dma *dma, u32 reg)
अणु
	काष्ठा rsnd_mod *mod = rsnd_mod_get(dma);
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);

	वापस ioपढ़ो32(rsnd_dmapp_addr(dmac, dma, reg));
पूर्ण

अटल व्योम rsnd_dmapp_bset(काष्ठा rsnd_dma *dma, u32 data, u32 mask, u32 reg)
अणु
	काष्ठा rsnd_mod *mod = rsnd_mod_get(dma);
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);
	व्योम __iomem *addr = rsnd_dmapp_addr(dmac, dma, reg);
	u32 val = ioपढ़ो32(addr);

	val &= ~mask;
	val |= (data & mask);

	ioग_लिखो32(val, addr);
पूर्ण

अटल पूर्णांक rsnd_dmapp_stop(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	पूर्णांक i;

	rsnd_dmapp_bset(dma, 0,  PDMACHCR_DE, PDMACHCR);

	क्रम (i = 0; i < 1024; i++) अणु
		अगर (0 == (rsnd_dmapp_पढ़ो(dma, PDMACHCR) & PDMACHCR_DE))
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक rsnd_dmapp_start(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dma *dma = rsnd_mod_to_dma(mod);
	काष्ठा rsnd_dmapp *dmapp = rsnd_dma_to_dmapp(dma);

	rsnd_dmapp_ग_लिखो(dma, dma->src_addr,	PDMASAR);
	rsnd_dmapp_ग_लिखो(dma, dma->dst_addr,	PDMADAR);
	rsnd_dmapp_ग_लिखो(dma, dmapp->chcr,	PDMACHCR);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dmapp_attach(काष्ठा rsnd_dai_stream *io,
			     काष्ठा rsnd_dma *dma,
			     काष्ठा rsnd_mod *mod_from, काष्ठा rsnd_mod *mod_to)
अणु
	काष्ठा rsnd_dmapp *dmapp = rsnd_dma_to_dmapp(dma);
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	dmapp->dmapp_id = dmac->dmapp_num;
	dmapp->chcr = rsnd_dmapp_get_chcr(io, mod_from, mod_to) | PDMACHCR_DE;

	dmac->dmapp_num++;

	dev_dbg(dev, "id/src/dst/chcr = %d/%pad/%pad/%08x\n",
		dmapp->dmapp_id, &dma->src_addr, &dma->dst_addr, dmapp->chcr);

	वापस 0;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_dmapp_ops = अणु
	.name		= "audmac-pp",
	.start		= rsnd_dmapp_start,
	.stop		= rsnd_dmapp_stop,
	.quit		= rsnd_dmapp_stop,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

/*
 *		Common DMAC Interface
 */

/*
 *	DMA पढ़ो/ग_लिखो रेजिस्टर offset
 *
 *	RSND_xxx_I_N	क्रम Audio DMAC input
 *	RSND_xxx_O_N	क्रम Audio DMAC output
 *	RSND_xxx_I_P	क्रम Audio DMAC peri peri input
 *	RSND_xxx_O_P	क्रम Audio DMAC peri peri output
 *
 *	ex) R-Car H2 हाल
 *	      mod        / DMAC in    / DMAC out   / DMAC PP in / DMAC pp out
 *	SSI : 0xec541000 / 0xec241008 / 0xec24100c
 *	SSIU: 0xec541000 / 0xec100000 / 0xec100000 / 0xec400000 / 0xec400000
 *	SCU : 0xec500000 / 0xec000000 / 0xec004000 / 0xec300000 / 0xec304000
 *	CMD : 0xec500000 /            / 0xec008000                0xec308000
 */
#घोषणा RDMA_SSI_I_N(addr, i)	(addr ##_reg - 0x00300000 + (0x40 * i) + 0x8)
#घोषणा RDMA_SSI_O_N(addr, i)	(addr ##_reg - 0x00300000 + (0x40 * i) + 0xc)

#घोषणा RDMA_SSIU_I_N(addr, i, j) (addr ##_reg - 0x00441000 + (0x1000 * (i)) + (((j) / 4) * 0xA000) + (((j) % 4) * 0x400) - (0x4000 * ((i) / 9) * ((j) / 4)))
#घोषणा RDMA_SSIU_O_N(addr, i, j) RDMA_SSIU_I_N(addr, i, j)

#घोषणा RDMA_SSIU_I_P(addr, i, j) (addr ##_reg - 0x00141000 + (0x1000 * (i)) + (((j) / 4) * 0xA000) + (((j) % 4) * 0x400) - (0x4000 * ((i) / 9) * ((j) / 4)))
#घोषणा RDMA_SSIU_O_P(addr, i, j) RDMA_SSIU_I_P(addr, i, j)

#घोषणा RDMA_SRC_I_N(addr, i)	(addr ##_reg - 0x00500000 + (0x400 * i))
#घोषणा RDMA_SRC_O_N(addr, i)	(addr ##_reg - 0x004fc000 + (0x400 * i))

#घोषणा RDMA_SRC_I_P(addr, i)	(addr ##_reg - 0x00200000 + (0x400 * i))
#घोषणा RDMA_SRC_O_P(addr, i)	(addr ##_reg - 0x001fc000 + (0x400 * i))

#घोषणा RDMA_CMD_O_N(addr, i)	(addr ##_reg - 0x004f8000 + (0x400 * i))
#घोषणा RDMA_CMD_O_P(addr, i)	(addr ##_reg - 0x001f8000 + (0x400 * i))

अटल dma_addr_t
rsnd_gen2_dma_addr(काष्ठा rsnd_dai_stream *io,
		   काष्ठा rsnd_mod *mod,
		   पूर्णांक is_play, पूर्णांक is_from)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	phys_addr_t ssi_reg = rsnd_gen_get_phy_addr(priv, RSND_GEN2_SSI);
	phys_addr_t src_reg = rsnd_gen_get_phy_addr(priv, RSND_GEN2_SCU);
	पूर्णांक is_ssi = !!(rsnd_io_to_mod_ssi(io) == mod) ||
		     !!(rsnd_io_to_mod_ssiu(io) == mod);
	पूर्णांक use_src = !!rsnd_io_to_mod_src(io);
	पूर्णांक use_cmd = !!rsnd_io_to_mod_dvc(io) ||
		      !!rsnd_io_to_mod_mix(io) ||
		      !!rsnd_io_to_mod_ctu(io);
	पूर्णांक id = rsnd_mod_id(mod);
	पूर्णांक busअगर = rsnd_mod_id_sub(rsnd_io_to_mod_ssiu(io));
	काष्ठा dma_addr अणु
		dma_addr_t out_addr;
		dma_addr_t in_addr;
	पूर्ण dma_addrs[3][2][3] = अणु
		/* SRC */
		/* Capture */
		अणुअणुअणु 0,				0 पूर्ण,
		  अणु RDMA_SRC_O_N(src, id),	RDMA_SRC_I_P(src, id) पूर्ण,
		  अणु RDMA_CMD_O_N(src, id),	RDMA_SRC_I_P(src, id) पूर्ण पूर्ण,
		 /* Playback */
		 अणुअणु 0,				0, पूर्ण,
		  अणु RDMA_SRC_O_P(src, id),	RDMA_SRC_I_N(src, id) पूर्ण,
		  अणु RDMA_CMD_O_P(src, id),	RDMA_SRC_I_N(src, id) पूर्ण पूर्ण
		पूर्ण,
		/* SSI */
		/* Capture */
		अणुअणुअणु RDMA_SSI_O_N(ssi, id),		0 पूर्ण,
		  अणु RDMA_SSIU_O_P(ssi, id, busअगर),	0 पूर्ण,
		  अणु RDMA_SSIU_O_P(ssi, id, busअगर),	0 पूर्ण पूर्ण,
		 /* Playback */
		 अणुअणु 0,			RDMA_SSI_I_N(ssi, id) पूर्ण,
		  अणु 0,			RDMA_SSIU_I_P(ssi, id, busअगर) पूर्ण,
		  अणु 0,			RDMA_SSIU_I_P(ssi, id, busअगर) पूर्ण पूर्ण
		पूर्ण,
		/* SSIU */
		/* Capture */
		अणुअणुअणु RDMA_SSIU_O_N(ssi, id, busअगर),	0 पूर्ण,
		  अणु RDMA_SSIU_O_P(ssi, id, busअगर),	0 पूर्ण,
		  अणु RDMA_SSIU_O_P(ssi, id, busअगर),	0 पूर्ण पूर्ण,
		 /* Playback */
		 अणुअणु 0,			RDMA_SSIU_I_N(ssi, id, busअगर) पूर्ण,
		  अणु 0,			RDMA_SSIU_I_P(ssi, id, busअगर) पूर्ण,
		  अणु 0,			RDMA_SSIU_I_P(ssi, id, busअगर) पूर्ण पूर्ण पूर्ण,
	पूर्ण;

	/*
	 * FIXME
	 *
	 * We can't support SSI9-4/5/6/7, because its address is
	 * out of calculation rule
	 */
	अगर ((id == 9) && (busअगर >= 4))
		dev_err(dev, "This driver doesn't support SSI%d-%d, so far",
			id, busअगर);

	/* it shouldn't happen */
	अगर (use_cmd && !use_src)
		dev_err(dev, "DVC is selected without SRC\n");

	/* use SSIU or SSI ? */
	अगर (is_ssi && rsnd_ssi_use_busअगर(io))
		is_ssi++;

	वापस (is_from) ?
		dma_addrs[is_ssi][is_play][use_src + use_cmd].out_addr :
		dma_addrs[is_ssi][is_play][use_src + use_cmd].in_addr;
पूर्ण

अटल dma_addr_t rsnd_dma_addr(काष्ठा rsnd_dai_stream *io,
				काष्ठा rsnd_mod *mod,
				पूर्णांक is_play, पूर्णांक is_from)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);

	/*
	 * gen1 uses शेष DMA addr
	 */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	अगर (!mod)
		वापस 0;

	वापस rsnd_gen2_dma_addr(io, mod, is_play, is_from);
पूर्ण

#घोषणा MOD_MAX (RSND_MOD_MAX + 1) /* +Memory */
अटल व्योम rsnd_dma_of_path(काष्ठा rsnd_mod *this,
			     काष्ठा rsnd_dai_stream *io,
			     पूर्णांक is_play,
			     काष्ठा rsnd_mod **mod_from,
			     काष्ठा rsnd_mod **mod_to)
अणु
	काष्ठा rsnd_mod *ssi;
	काष्ठा rsnd_mod *src = rsnd_io_to_mod_src(io);
	काष्ठा rsnd_mod *ctu = rsnd_io_to_mod_ctu(io);
	काष्ठा rsnd_mod *mix = rsnd_io_to_mod_mix(io);
	काष्ठा rsnd_mod *dvc = rsnd_io_to_mod_dvc(io);
	काष्ठा rsnd_mod *mod[MOD_MAX];
	काष्ठा rsnd_mod *mod_start, *mod_end;
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(this);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक nr, i, idx;

	/*
	 * It should use "rcar_sound,ssiu" on DT.
	 * But, we need to keep compatibility क्रम old version.
	 *
	 * If it has "rcar_sound.ssiu", it will be used.
	 * If not, "rcar_sound.ssi" will be used.
	 * see
	 *	rsnd_ssiu_dma_req()
	 *	rsnd_ssi_dma_req()
	 */
	अगर (rsnd_ssiu_of_node(priv)) अणु
		काष्ठा rsnd_mod *ssiu = rsnd_io_to_mod_ssiu(io);

		/* use SSIU */
		ssi = ssiu;
		अगर (this == rsnd_io_to_mod_ssi(io))
			this = ssiu;
	पूर्ण अन्यथा अणु
		/* keep compatible, use SSI */
		ssi = rsnd_io_to_mod_ssi(io);
	पूर्ण

	अगर (!ssi)
		वापस;

	nr = 0;
	क्रम (i = 0; i < MOD_MAX; i++) अणु
		mod[i] = शून्य;
		nr += !!rsnd_io_to_mod(io, i);
	पूर्ण

	/*
	 * [S] -*-> [E]
	 * [S] -*-> SRC -o-> [E]
	 * [S] -*-> SRC -> DVC -o-> [E]
	 * [S] -*-> SRC -> CTU -> MIX -> DVC -o-> [E]
	 *
	 * playback	[S] = mem
	 *		[E] = SSI
	 *
	 * capture	[S] = SSI
	 *		[E] = mem
	 *
	 * -*->		Audio DMAC
	 * -o->		Audio DMAC peri peri
	 */
	mod_start	= (is_play) ? शून्य : ssi;
	mod_end		= (is_play) ? ssi  : शून्य;

	idx = 0;
	mod[idx++] = mod_start;
	क्रम (i = 1; i < nr; i++) अणु
		अगर (src) अणु
			mod[idx++] = src;
			src = शून्य;
		पूर्ण अन्यथा अगर (ctu) अणु
			mod[idx++] = ctu;
			ctu = शून्य;
		पूर्ण अन्यथा अगर (mix) अणु
			mod[idx++] = mix;
			mix = शून्य;
		पूर्ण अन्यथा अगर (dvc) अणु
			mod[idx++] = dvc;
			dvc = शून्य;
		पूर्ण
	पूर्ण
	mod[idx] = mod_end;

	/*
	 *		| SSI | SRC |
	 * -------------+-----+-----+
	 *  is_play	|  o  |  *  |
	 * !is_play	|  *  |  o  |
	 */
	अगर ((this == ssi) == (is_play)) अणु
		*mod_from	= mod[idx - 1];
		*mod_to		= mod[idx];
	पूर्ण अन्यथा अणु
		*mod_from	= mod[0];
		*mod_to		= mod[1];
	पूर्ण

	dev_dbg(dev, "module connection (this is %s)\n", rsnd_mod_name(this));
	क्रम (i = 0; i <= idx; i++) अणु
		dev_dbg(dev, "  %s%s\n",
			rsnd_mod_name(mod[i] ? mod[i] : &mem),
			(mod[i] == *mod_from) ? " from" :
			(mod[i] == *mod_to)   ? " to" : "");
	पूर्ण
पूर्ण

अटल पूर्णांक rsnd_dma_alloc(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_mod *mod,
			  काष्ठा rsnd_mod **dma_mod)
अणु
	काष्ठा rsnd_mod *mod_from = शून्य;
	काष्ठा rsnd_mod *mod_to = शून्य;
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_dma *dma;
	काष्ठा rsnd_mod_ops *ops;
	क्रमागत rsnd_mod_type type;
	पूर्णांक (*attach)(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_dma *dma,
		      काष्ठा rsnd_mod *mod_from, काष्ठा rsnd_mod *mod_to);
	पूर्णांक is_play = rsnd_io_is_play(io);
	पूर्णांक ret, dma_id;

	/*
	 * DMA failed. try to PIO mode
	 * see
	 *	rsnd_ssi_fallback()
	 *	rsnd_rdai_continuance_probe()
	 */
	अगर (!dmac)
		वापस -EAGAIN;

	rsnd_dma_of_path(mod, io, is_play, &mod_from, &mod_to);

	/* क्रम Gen2 or later */
	अगर (mod_from && mod_to) अणु
		ops	= &rsnd_dmapp_ops;
		attach	= rsnd_dmapp_attach;
		dma_id	= dmac->dmapp_num;
		type	= RSND_MOD_AUDMAPP;
	पूर्ण अन्यथा अणु
		ops	= &rsnd_dmaen_ops;
		attach	= rsnd_dmaen_attach;
		dma_id	= dmac->dmaen_num;
		type	= RSND_MOD_AUDMA;
	पूर्ण

	/* क्रम Gen1, overग_लिखो */
	अगर (rsnd_is_gen1(priv)) अणु
		ops	= &rsnd_dmaen_ops;
		attach	= rsnd_dmaen_attach;
		dma_id	= dmac->dmaen_num;
		type	= RSND_MOD_AUDMA;
	पूर्ण

	dma = devm_kzalloc(dev, माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस -ENOMEM;

	*dma_mod = rsnd_mod_get(dma);

	ret = rsnd_mod_init(priv, *dma_mod, ops, शून्य,
			    type, dma_id);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "%s %s -> %s\n",
		rsnd_mod_name(*dma_mod),
		rsnd_mod_name(mod_from ? mod_from : &mem),
		rsnd_mod_name(mod_to   ? mod_to   : &mem));

	ret = attach(io, dma, mod_from, mod_to);
	अगर (ret < 0)
		वापस ret;

	dma->src_addr = rsnd_dma_addr(io, mod_from, is_play, 1);
	dma->dst_addr = rsnd_dma_addr(io, mod_to,   is_play, 0);
	dma->mod_from = mod_from;
	dma->mod_to   = mod_to;

	वापस 0;
पूर्ण

पूर्णांक rsnd_dma_attach(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_mod *mod,
		    काष्ठा rsnd_mod **dma_mod)
अणु
	अगर (!(*dma_mod)) अणु
		पूर्णांक ret = rsnd_dma_alloc(io, mod, dma_mod);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस rsnd_dai_connect(*dma_mod, io, (*dma_mod)->type);
पूर्ण

पूर्णांक rsnd_dma_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा platक्रमm_device *pdev = rsnd_priv_to_pdev(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_dma_ctrl *dmac;
	काष्ठा resource *res;

	/*
	 * क्रम Gen1
	 */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	/*
	 * क्रम Gen2 or later
	 */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "audmapp");
	dmac = devm_kzalloc(dev, माप(*dmac), GFP_KERNEL);
	अगर (!dmac || !res) अणु
		dev_err(dev, "dma allocate failed\n");
		वापस 0; /* it will be PIO mode */
	पूर्ण

	dmac->dmapp_num = 0;
	dmac->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dmac->base))
		वापस PTR_ERR(dmac->base);

	priv->dma = dmac;

	/* dummy mem mod क्रम debug */
	वापस rsnd_mod_init(शून्य, &mem, &mem_ops, शून्य, 0, 0);
पूर्ण
