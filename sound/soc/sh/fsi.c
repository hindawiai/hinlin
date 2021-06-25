<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Fअगरo-attached Serial Interface (FSI) support क्रम SH7724
//
// Copyright (C) 2009 Renesas Solutions Corp.
// Kuninori Morimoto <morimoto.kuninori@renesas.com>
//
// Based on ssi.c
// Copyright (c) 2007 Manuel Lauss <mano@roarinelk.homelinux.net>

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/sh_fsi.h>

/* PortA/PortB रेजिस्टर */
#घोषणा REG_DO_FMT	0x0000
#घोषणा REG_DOFF_CTL	0x0004
#घोषणा REG_DOFF_ST	0x0008
#घोषणा REG_DI_FMT	0x000C
#घोषणा REG_DIFF_CTL	0x0010
#घोषणा REG_DIFF_ST	0x0014
#घोषणा REG_CKG1	0x0018
#घोषणा REG_CKG2	0x001C
#घोषणा REG_DIDT	0x0020
#घोषणा REG_DODT	0x0024
#घोषणा REG_MUTE_ST	0x0028
#घोषणा REG_OUT_DMAC	0x002C
#घोषणा REG_OUT_SEL	0x0030
#घोषणा REG_IN_DMAC	0x0038

/* master रेजिस्टर */
#घोषणा MST_CLK_RST	0x0210
#घोषणा MST_SOFT_RST	0x0214
#घोषणा MST_FIFO_SZ	0x0218

/* core रेजिस्टर (depend on FSI version) */
#घोषणा A_MST_CTLR	0x0180
#घोषणा B_MST_CTLR	0x01A0
#घोषणा CPU_INT_ST	0x01F4
#घोषणा CPU_IEMSK	0x01F8
#घोषणा CPU_IMSK	0x01FC
#घोषणा INT_ST		0x0200
#घोषणा IEMSK		0x0204
#घोषणा IMSK		0x0208

/* DO_FMT */
/* DI_FMT */
#घोषणा CR_BWS_MASK	(0x3 << 20) /* FSI2 */
#घोषणा CR_BWS_24	(0x0 << 20) /* FSI2 */
#घोषणा CR_BWS_16	(0x1 << 20) /* FSI2 */
#घोषणा CR_BWS_20	(0x2 << 20) /* FSI2 */

#घोषणा CR_DTMD_PCM		(0x0 << 8) /* FSI2 */
#घोषणा CR_DTMD_SPDIF_PCM	(0x1 << 8) /* FSI2 */
#घोषणा CR_DTMD_SPDIF_STREAM	(0x2 << 8) /* FSI2 */

#घोषणा CR_MONO		(0x0 << 4)
#घोषणा CR_MONO_D	(0x1 << 4)
#घोषणा CR_PCM		(0x2 << 4)
#घोषणा CR_I2S		(0x3 << 4)
#घोषणा CR_TDM		(0x4 << 4)
#घोषणा CR_TDM_D	(0x5 << 4)

/* OUT_DMAC */
/* IN_DMAC */
#घोषणा VDMD_MASK	(0x3 << 4)
#घोषणा VDMD_FRONT	(0x0 << 4) /* Package in front */
#घोषणा VDMD_BACK	(0x1 << 4) /* Package in back */
#घोषणा VDMD_STREAM	(0x2 << 4) /* Stream mode(16bit * 2) */

#घोषणा DMA_ON		(0x1 << 0)

/* DOFF_CTL */
/* DIFF_CTL */
#घोषणा IRQ_HALF	0x00100000
#घोषणा FIFO_CLR	0x00000001

/* DOFF_ST */
#घोषणा ERR_OVER	0x00000010
#घोषणा ERR_UNDER	0x00000001
#घोषणा ST_ERR		(ERR_OVER | ERR_UNDER)

/* CKG1 */
#घोषणा ACKMD_MASK	0x00007000
#घोषणा BPFMD_MASK	0x00000700
#घोषणा DIMD		(1 << 4)
#घोषणा DOMD		(1 << 0)

/* A/B MST_CTLR */
#घोषणा BP	(1 << 4)	/* Fix the संकेत of Biphase output */
#घोषणा SE	(1 << 0)	/* Fix the master घड़ी */

/* CLK_RST */
#घोषणा CRB	(1 << 4)
#घोषणा CRA	(1 << 0)

/* IO SHIFT / MACRO */
#घोषणा BI_SHIFT	12
#घोषणा BO_SHIFT	8
#घोषणा AI_SHIFT	4
#घोषणा AO_SHIFT	0
#घोषणा AB_IO(param, shअगरt)	(param << shअगरt)

/* SOFT_RST */
#घोषणा PBSR		(1 << 12) /* Port B Software Reset */
#घोषणा PASR		(1 <<  8) /* Port A Software Reset */
#घोषणा IR		(1 <<  4) /* Interrupt Reset */
#घोषणा FSISR		(1 <<  0) /* Software Reset */

/* OUT_SEL (FSI2) */
#घोषणा DMMD		(1 << 4) /* SPDIF output timing 0: Biphase only */
				 /*			1: Biphase and serial */

/* FIFO_SZ */
#घोषणा FIFO_SZ_MASK	0x7

#घोषणा FSI_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा FSI_FMTS (SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S16_LE)

/*
 * bus options
 *
 * 0x000000BA
 *
 * A : sample widtht 16bit setting
 * B : sample widtht 24bit setting
 */

#घोषणा SHIFT_16DATA		0
#घोषणा SHIFT_24DATA		4

#घोषणा PACKAGE_24BITBUS_BACK		0
#घोषणा PACKAGE_24BITBUS_FRONT		1
#घोषणा PACKAGE_16BITBUS_STREAM		2

#घोषणा BUSOP_SET(s, a)	((a) << SHIFT_ ## s ## DATA)
#घोषणा BUSOP_GET(s, a)	(((a) >> SHIFT_ ## s ## DATA) & 0xF)

/*
 * FSI driver use below type name क्रम variable
 *
 * xxx_num	: number of data
 * xxx_pos	: position of data
 * xxx_capa	: capacity of data
 */

/*
 *	period/frame/sample image
 *
 * ex) PCM (2ch)
 *
 * period pos					   period pos
 *   [n]					     [n + 1]
 *   |<-------------------- period--------------------->|
 * ==|============================================ ... =|==
 *   |							|
 *   ||<-----  frame ----->|<------ frame ----->|  ...	|
 *   |+--------------------+--------------------+- ...	|
 *   ||[ sample ][ sample ]|[ sample ][ sample ]|  ...	|
 *   |+--------------------+--------------------+- ...	|
 * ==|============================================ ... =|==
 */

/*
 *	FSI FIFO image
 *
 *	|	     |
 *	|	     |
 *	| [ sample ] |
 *	| [ sample ] |
 *	| [ sample ] |
 *	| [ sample ] |
 *		--> go to codecs
 */

/*
 *	FSI घड़ी
 *
 * FSIxCLK [CPG] (ick) ------->	|
 *				|-> FSI_DIV (भाग)-> FSI2
 * FSIxCK [बाह्यal] (xck) --->	|
 */

/*
 *		काष्ठा
 */

काष्ठा fsi_stream_handler;
काष्ठा fsi_stream अणु

	/*
	 * these are initialized by fsi_stream_init()
	 */
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक fअगरo_sample_capa;	/* sample capacity of FSI FIFO */
	पूर्णांक buff_sample_capa;	/* sample capacity of ALSA buffer */
	पूर्णांक buff_sample_pos;	/* sample position of ALSA buffer */
	पूर्णांक period_samples;	/* sample number / 1 period */
	पूर्णांक period_pos;		/* current period position */
	पूर्णांक sample_width;	/* sample width */
	पूर्णांक uerr_num;
	पूर्णांक oerr_num;

	/*
	 * bus options
	 */
	u32 bus_option;

	/*
	 * thse are initialized by fsi_handler_init()
	 */
	काष्ठा fsi_stream_handler *handler;
	काष्ठा fsi_priv		*priv;

	/*
	 * these are क्रम DMAEngine
	 */
	काष्ठा dma_chan		*chan;
	पूर्णांक			dma_id;
पूर्ण;

काष्ठा fsi_clk अणु
	/* see [FSI घड़ी] */
	काष्ठा clk *own;
	काष्ठा clk *xck;
	काष्ठा clk *ick;
	काष्ठा clk *भाग;
	पूर्णांक (*set_rate)(काष्ठा device *dev,
			काष्ठा fsi_priv *fsi);

	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा fsi_priv अणु
	व्योम __iomem *base;
	phys_addr_t phys;
	काष्ठा fsi_master *master;

	काष्ठा fsi_stream playback;
	काष्ठा fsi_stream capture;

	काष्ठा fsi_clk घड़ी;

	u32 fmt;

	पूर्णांक chan_num:16;
	अचिन्हित पूर्णांक clk_master:1;
	अचिन्हित पूर्णांक clk_cpg:1;
	अचिन्हित पूर्णांक spdअगर:1;
	अचिन्हित पूर्णांक enable_stream:1;
	अचिन्हित पूर्णांक bit_clk_inv:1;
	अचिन्हित पूर्णांक lr_clk_inv:1;
पूर्ण;

काष्ठा fsi_stream_handler अणु
	पूर्णांक (*init)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io);
	पूर्णांक (*quit)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io);
	पूर्णांक (*probe)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io, काष्ठा device *dev);
	पूर्णांक (*transfer)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io);
	पूर्णांक (*हटाओ)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io);
	पूर्णांक (*start_stop)(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io,
			   पूर्णांक enable);
पूर्ण;
#घोषणा fsi_stream_handler_call(io, func, args...)	\
	(!(io) ? -ENODEV :				\
	 !((io)->handler->func) ? 0 :			\
	 (io)->handler->func(args))

काष्ठा fsi_core अणु
	पूर्णांक ver;

	u32 पूर्णांक_st;
	u32 iemsk;
	u32 imsk;
	u32 a_mclk;
	u32 b_mclk;
पूर्ण;

काष्ठा fsi_master अणु
	व्योम __iomem *base;
	काष्ठा fsi_priv fsia;
	काष्ठा fsi_priv fsib;
	स्थिर काष्ठा fsi_core *core;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत पूर्णांक fsi_stream_is_play(काष्ठा fsi_priv *fsi,
				     काष्ठा fsi_stream *io)
अणु
	वापस &fsi->playback == io;
पूर्ण


/*
 *		basic पढ़ो ग_लिखो function
 */

अटल व्योम __fsi_reg_ग_लिखो(u32 __iomem *reg, u32 data)
अणु
	/* valid data area is 24bit */
	data &= 0x00ffffff;

	__raw_ग_लिखोl(data, reg);
पूर्ण

अटल u32 __fsi_reg_पढ़ो(u32 __iomem *reg)
अणु
	वापस __raw_पढ़ोl(reg);
पूर्ण

अटल व्योम __fsi_reg_mask_set(u32 __iomem *reg, u32 mask, u32 data)
अणु
	u32 val = __fsi_reg_पढ़ो(reg);

	val &= ~mask;
	val |= data & mask;

	__fsi_reg_ग_लिखो(reg, val);
पूर्ण

#घोषणा fsi_reg_ग_लिखो(p, r, d)\
	__fsi_reg_ग_लिखो((p->base + REG_##r), d)

#घोषणा fsi_reg_पढ़ो(p, r)\
	__fsi_reg_पढ़ो((p->base + REG_##r))

#घोषणा fsi_reg_mask_set(p, r, m, d)\
	__fsi_reg_mask_set((p->base + REG_##r), m, d)

#घोषणा fsi_master_पढ़ो(p, r) _fsi_master_पढ़ो(p, MST_##r)
#घोषणा fsi_core_पढ़ो(p, r)   _fsi_master_पढ़ो(p, p->core->r)
अटल u32 _fsi_master_पढ़ो(काष्ठा fsi_master *master, u32 reg)
अणु
	u32 ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->lock, flags);
	ret = __fsi_reg_पढ़ो(master->base + reg);
	spin_unlock_irqrestore(&master->lock, flags);

	वापस ret;
पूर्ण

#घोषणा fsi_master_mask_set(p, r, m, d) _fsi_master_mask_set(p, MST_##r, m, d)
#घोषणा fsi_core_mask_set(p, r, m, d)  _fsi_master_mask_set(p, p->core->r, m, d)
अटल व्योम _fsi_master_mask_set(काष्ठा fsi_master *master,
			       u32 reg, u32 mask, u32 data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->lock, flags);
	__fsi_reg_mask_set(master->base + reg, mask, data);
	spin_unlock_irqrestore(&master->lock, flags);
पूर्ण

/*
 *		basic function
 */
अटल पूर्णांक fsi_version(काष्ठा fsi_master *master)
अणु
	वापस master->core->ver;
पूर्ण

अटल काष्ठा fsi_master *fsi_get_master(काष्ठा fsi_priv *fsi)
अणु
	वापस fsi->master;
पूर्ण

अटल पूर्णांक fsi_is_clk_master(काष्ठा fsi_priv *fsi)
अणु
	वापस fsi->clk_master;
पूर्ण

अटल पूर्णांक fsi_is_port_a(काष्ठा fsi_priv *fsi)
अणु
	वापस fsi->master->base == fsi->base;
पूर्ण

अटल पूर्णांक fsi_is_spdअगर(काष्ठा fsi_priv *fsi)
अणु
	वापस fsi->spdअगर;
पूर्ण

अटल पूर्णांक fsi_is_enable_stream(काष्ठा fsi_priv *fsi)
अणु
	वापस fsi->enable_stream;
पूर्ण

अटल पूर्णांक fsi_is_play(काष्ठा snd_pcm_substream *substream)
अणु
	वापस substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
पूर्ण

अटल काष्ठा snd_soc_dai *fsi_get_dai(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	वापस  asoc_rtd_to_cpu(rtd, 0);
पूर्ण

अटल काष्ठा fsi_priv *fsi_get_priv_frm_dai(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsi_master *master = snd_soc_dai_get_drvdata(dai);

	अगर (dai->id == 0)
		वापस &master->fsia;
	अन्यथा
		वापस &master->fsib;
पूर्ण

अटल काष्ठा fsi_priv *fsi_get_priv(काष्ठा snd_pcm_substream *substream)
अणु
	वापस fsi_get_priv_frm_dai(fsi_get_dai(substream));
पूर्ण

अटल u32 fsi_get_port_shअगरt(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);
	पूर्णांक is_porta = fsi_is_port_a(fsi);
	u32 shअगरt;

	अगर (is_porta)
		shअगरt = is_play ? AO_SHIFT : AI_SHIFT;
	अन्यथा
		shअगरt = is_play ? BO_SHIFT : BI_SHIFT;

	वापस shअगरt;
पूर्ण

अटल पूर्णांक fsi_frame2sample(काष्ठा fsi_priv *fsi, पूर्णांक frames)
अणु
	वापस frames * fsi->chan_num;
पूर्ण

अटल पूर्णांक fsi_sample2frame(काष्ठा fsi_priv *fsi, पूर्णांक samples)
अणु
	वापस samples / fsi->chan_num;
पूर्ण

अटल पूर्णांक fsi_get_current_fअगरo_samples(काष्ठा fsi_priv *fsi,
					काष्ठा fsi_stream *io)
अणु
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);
	u32 status;
	पूर्णांक frames;

	status = is_play ?
		fsi_reg_पढ़ो(fsi, DOFF_ST) :
		fsi_reg_पढ़ो(fsi, DIFF_ST);

	frames = 0x1ff & (status >> 8);

	वापस fsi_frame2sample(fsi, frames);
पूर्ण

अटल व्योम fsi_count_fअगरo_err(काष्ठा fsi_priv *fsi)
अणु
	u32 ostatus = fsi_reg_पढ़ो(fsi, DOFF_ST);
	u32 istatus = fsi_reg_पढ़ो(fsi, DIFF_ST);

	अगर (ostatus & ERR_OVER)
		fsi->playback.oerr_num++;

	अगर (ostatus & ERR_UNDER)
		fsi->playback.uerr_num++;

	अगर (istatus & ERR_OVER)
		fsi->capture.oerr_num++;

	अगर (istatus & ERR_UNDER)
		fsi->capture.uerr_num++;

	fsi_reg_ग_लिखो(fsi, DOFF_ST, 0);
	fsi_reg_ग_लिखो(fsi, DIFF_ST, 0);
पूर्ण

/*
 *		fsi_stream_xx() function
 */
अटल अंतरभूत काष्ठा fsi_stream *fsi_stream_get(काष्ठा fsi_priv *fsi,
					काष्ठा snd_pcm_substream *substream)
अणु
	वापस fsi_is_play(substream) ? &fsi->playback : &fsi->capture;
पूर्ण

अटल पूर्णांक fsi_stream_is_working(काष्ठा fsi_priv *fsi,
				 काष्ठा fsi_stream *io)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&master->lock, flags);
	ret = !!(io->substream && io->substream->runसमय);
	spin_unlock_irqrestore(&master->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा fsi_priv *fsi_stream_to_priv(काष्ठा fsi_stream *io)
अणु
	वापस io->priv;
पूर्ण

अटल व्योम fsi_stream_init(काष्ठा fsi_priv *fsi,
			    काष्ठा fsi_stream *io,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->lock, flags);
	io->substream	= substream;
	io->buff_sample_capa	= fsi_frame2sample(fsi, runसमय->buffer_size);
	io->buff_sample_pos	= 0;
	io->period_samples	= fsi_frame2sample(fsi, runसमय->period_size);
	io->period_pos		= 0;
	io->sample_width	= samples_to_bytes(runसमय, 1);
	io->bus_option		= 0;
	io->oerr_num	= -1; /* ignore 1st err */
	io->uerr_num	= -1; /* ignore 1st err */
	fsi_stream_handler_call(io, init, fsi, io);
	spin_unlock_irqrestore(&master->lock, flags);
पूर्ण

अटल व्योम fsi_stream_quit(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	काष्ठा snd_soc_dai *dai = fsi_get_dai(io->substream);
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->lock, flags);

	अगर (io->oerr_num > 0)
		dev_err(dai->dev, "over_run = %d\n", io->oerr_num);

	अगर (io->uerr_num > 0)
		dev_err(dai->dev, "under_run = %d\n", io->uerr_num);

	fsi_stream_handler_call(io, quit, fsi, io);
	io->substream	= शून्य;
	io->buff_sample_capa	= 0;
	io->buff_sample_pos	= 0;
	io->period_samples	= 0;
	io->period_pos		= 0;
	io->sample_width	= 0;
	io->bus_option		= 0;
	io->oerr_num	= 0;
	io->uerr_num	= 0;
	spin_unlock_irqrestore(&master->lock, flags);
पूर्ण

अटल पूर्णांक fsi_stream_transfer(काष्ठा fsi_stream *io)
अणु
	काष्ठा fsi_priv *fsi = fsi_stream_to_priv(io);
	अगर (!fsi)
		वापस -EIO;

	वापस fsi_stream_handler_call(io, transfer, fsi, io);
पूर्ण

#घोषणा fsi_stream_start(fsi, io)\
	fsi_stream_handler_call(io, start_stop, fsi, io, 1)

#घोषणा fsi_stream_stop(fsi, io)\
	fsi_stream_handler_call(io, start_stop, fsi, io, 0)

अटल पूर्णांक fsi_stream_probe(काष्ठा fsi_priv *fsi, काष्ठा device *dev)
अणु
	काष्ठा fsi_stream *io;
	पूर्णांक ret1, ret2;

	io = &fsi->playback;
	ret1 = fsi_stream_handler_call(io, probe, fsi, io, dev);

	io = &fsi->capture;
	ret2 = fsi_stream_handler_call(io, probe, fsi, io, dev);

	अगर (ret1 < 0)
		वापस ret1;
	अगर (ret2 < 0)
		वापस ret2;

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_stream_हटाओ(काष्ठा fsi_priv *fsi)
अणु
	काष्ठा fsi_stream *io;
	पूर्णांक ret1, ret2;

	io = &fsi->playback;
	ret1 = fsi_stream_handler_call(io, हटाओ, fsi, io);

	io = &fsi->capture;
	ret2 = fsi_stream_handler_call(io, हटाओ, fsi, io);

	अगर (ret1 < 0)
		वापस ret1;
	अगर (ret2 < 0)
		वापस ret2;

	वापस 0;
पूर्ण

/*
 *	क्रमmat/bus/dma setting
 */
अटल व्योम fsi_क्रमmat_bus_setup(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io,
				 u32 bus, काष्ठा device *dev)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);
	u32 fmt = fsi->fmt;

	अगर (fsi_version(master) >= 2) अणु
		u32 dma = 0;

		/*
		 * FSI2 needs DMA/Bus setting
		 */
		चयन (bus) अणु
		हाल PACKAGE_24BITBUS_FRONT:
			fmt |= CR_BWS_24;
			dma |= VDMD_FRONT;
			dev_dbg(dev, "24bit bus / package in front\n");
			अवरोध;
		हाल PACKAGE_16BITBUS_STREAM:
			fmt |= CR_BWS_16;
			dma |= VDMD_STREAM;
			dev_dbg(dev, "16bit bus / stream mode\n");
			अवरोध;
		हाल PACKAGE_24BITBUS_BACK:
		शेष:
			fmt |= CR_BWS_24;
			dma |= VDMD_BACK;
			dev_dbg(dev, "24bit bus / package in back\n");
			अवरोध;
		पूर्ण

		अगर (is_play)
			fsi_reg_ग_लिखो(fsi, OUT_DMAC,	dma);
		अन्यथा
			fsi_reg_ग_लिखो(fsi, IN_DMAC,	dma);
	पूर्ण

	अगर (is_play)
		fsi_reg_ग_लिखो(fsi, DO_FMT, fmt);
	अन्यथा
		fsi_reg_ग_लिखो(fsi, DI_FMT, fmt);
पूर्ण

/*
 *		irq function
 */

अटल व्योम fsi_irq_enable(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	u32 data = AB_IO(1, fsi_get_port_shअगरt(fsi, io));
	काष्ठा fsi_master *master = fsi_get_master(fsi);

	fsi_core_mask_set(master, imsk,  data, data);
	fsi_core_mask_set(master, iemsk, data, data);
पूर्ण

अटल व्योम fsi_irq_disable(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	u32 data = AB_IO(1, fsi_get_port_shअगरt(fsi, io));
	काष्ठा fsi_master *master = fsi_get_master(fsi);

	fsi_core_mask_set(master, imsk,  data, 0);
	fsi_core_mask_set(master, iemsk, data, 0);
पूर्ण

अटल u32 fsi_irq_get_status(काष्ठा fsi_master *master)
अणु
	वापस fsi_core_पढ़ो(master, पूर्णांक_st);
पूर्ण

अटल व्योम fsi_irq_clear_status(काष्ठा fsi_priv *fsi)
अणु
	u32 data = 0;
	काष्ठा fsi_master *master = fsi_get_master(fsi);

	data |= AB_IO(1, fsi_get_port_shअगरt(fsi, &fsi->playback));
	data |= AB_IO(1, fsi_get_port_shअगरt(fsi, &fsi->capture));

	/* clear पूर्णांकerrupt factor */
	fsi_core_mask_set(master, पूर्णांक_st, data, 0);
पूर्ण

/*
 *		SPDIF master घड़ी function
 *
 * These functions are used later FSI2
 */
अटल व्योम fsi_spdअगर_clk_ctrl(काष्ठा fsi_priv *fsi, पूर्णांक enable)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	u32 mask, val;

	mask = BP | SE;
	val = enable ? mask : 0;

	fsi_is_port_a(fsi) ?
		fsi_core_mask_set(master, a_mclk, mask, val) :
		fsi_core_mask_set(master, b_mclk, mask, val);
पूर्ण

/*
 *		घड़ी function
 */
अटल पूर्णांक fsi_clk_init(काष्ठा device *dev,
			काष्ठा fsi_priv *fsi,
			पूर्णांक xck,
			पूर्णांक ick,
			पूर्णांक भाग,
			पूर्णांक (*set_rate)(काष्ठा device *dev,
					काष्ठा fsi_priv *fsi))
अणु
	काष्ठा fsi_clk *घड़ी = &fsi->घड़ी;
	पूर्णांक is_porta = fsi_is_port_a(fsi);

	घड़ी->xck	= शून्य;
	घड़ी->ick	= शून्य;
	घड़ी->भाग	= शून्य;
	घड़ी->rate	= 0;
	घड़ी->count	= 0;
	घड़ी->set_rate	= set_rate;

	घड़ी->own = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(घड़ी->own))
		वापस -EINVAL;

	/* बाह्यal घड़ी */
	अगर (xck) अणु
		घड़ी->xck = devm_clk_get(dev, is_porta ? "xcka" : "xckb");
		अगर (IS_ERR(घड़ी->xck)) अणु
			dev_err(dev, "can't get xck clock\n");
			वापस -EINVAL;
		पूर्ण
		अगर (घड़ी->xck == घड़ी->own) अणु
			dev_err(dev, "cpu doesn't support xck clock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* FSIACLK/FSIBCLK */
	अगर (ick) अणु
		घड़ी->ick = devm_clk_get(dev,  is_porta ? "icka" : "ickb");
		अगर (IS_ERR(घड़ी->ick)) अणु
			dev_err(dev, "can't get ick clock\n");
			वापस -EINVAL;
		पूर्ण
		अगर (घड़ी->ick == घड़ी->own) अणु
			dev_err(dev, "cpu doesn't support ick clock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* FSI-DIV */
	अगर (भाग) अणु
		घड़ी->भाग = devm_clk_get(dev,  is_porta ? "diva" : "divb");
		अगर (IS_ERR(घड़ी->भाग)) अणु
			dev_err(dev, "can't get div clock\n");
			वापस -EINVAL;
		पूर्ण
		अगर (घड़ी->भाग == घड़ी->own) अणु
			dev_err(dev, "cpu doesn't support div clock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा fsi_clk_invalid(fsi) fsi_clk_valid(fsi, 0)
अटल व्योम fsi_clk_valid(काष्ठा fsi_priv *fsi, अचिन्हित दीर्घ rate)
अणु
	fsi->घड़ी.rate = rate;
पूर्ण

अटल पूर्णांक fsi_clk_is_valid(काष्ठा fsi_priv *fsi)
अणु
	वापस	fsi->घड़ी.set_rate &&
		fsi->घड़ी.rate;
पूर्ण

अटल पूर्णांक fsi_clk_enable(काष्ठा device *dev,
			  काष्ठा fsi_priv *fsi)
अणु
	काष्ठा fsi_clk *घड़ी = &fsi->घड़ी;
	पूर्णांक ret = -EINVAL;

	अगर (!fsi_clk_is_valid(fsi))
		वापस ret;

	अगर (0 == घड़ी->count) अणु
		ret = घड़ी->set_rate(dev, fsi);
		अगर (ret < 0) अणु
			fsi_clk_invalid(fsi);
			वापस ret;
		पूर्ण

		clk_enable(घड़ी->xck);
		clk_enable(घड़ी->ick);
		clk_enable(घड़ी->भाग);

		घड़ी->count++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsi_clk_disable(काष्ठा device *dev,
			    काष्ठा fsi_priv *fsi)
अणु
	काष्ठा fsi_clk *घड़ी = &fsi->घड़ी;

	अगर (!fsi_clk_is_valid(fsi))
		वापस -EINVAL;

	अगर (1 == घड़ी->count--) अणु
		clk_disable(घड़ी->xck);
		clk_disable(घड़ी->ick);
		clk_disable(घड़ी->भाग);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_clk_set_ackbpf(काष्ठा device *dev,
			      काष्ठा fsi_priv *fsi,
			      पूर्णांक ackmd, पूर्णांक bpfmd)
अणु
	u32 data = 0;

	/* check ackmd/bpfmd relationship */
	अगर (bpfmd > ackmd) अणु
		dev_err(dev, "unsupported rate (%d/%d)\n", ackmd, bpfmd);
		वापस -EINVAL;
	पूर्ण

	/*  ACKMD */
	चयन (ackmd) अणु
	हाल 512:
		data |= (0x0 << 12);
		अवरोध;
	हाल 256:
		data |= (0x1 << 12);
		अवरोध;
	हाल 128:
		data |= (0x2 << 12);
		अवरोध;
	हाल 64:
		data |= (0x3 << 12);
		अवरोध;
	हाल 32:
		data |= (0x4 << 12);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported ackmd (%d)\n", ackmd);
		वापस -EINVAL;
	पूर्ण

	/* BPFMD */
	चयन (bpfmd) अणु
	हाल 32:
		data |= (0x0 << 8);
		अवरोध;
	हाल 64:
		data |= (0x1 << 8);
		अवरोध;
	हाल 128:
		data |= (0x2 << 8);
		अवरोध;
	हाल 256:
		data |= (0x3 << 8);
		अवरोध;
	हाल 512:
		data |= (0x4 << 8);
		अवरोध;
	हाल 16:
		data |= (0x7 << 8);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported bpfmd (%d)\n", bpfmd);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "ACKMD/BPFMD = %d/%d\n", ackmd, bpfmd);

	fsi_reg_mask_set(fsi, CKG1, (ACKMD_MASK | BPFMD_MASK) , data);
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_clk_set_rate_बाह्यal(काष्ठा device *dev,
				     काष्ठा fsi_priv *fsi)
अणु
	काष्ठा clk *xck = fsi->घड़ी.xck;
	काष्ठा clk *ick = fsi->घड़ी.ick;
	अचिन्हित दीर्घ rate = fsi->घड़ी.rate;
	अचिन्हित दीर्घ xrate;
	पूर्णांक ackmd, bpfmd;
	पूर्णांक ret = 0;

	/* check घड़ी rate */
	xrate = clk_get_rate(xck);
	अगर (xrate % rate) अणु
		dev_err(dev, "unsupported clock rate\n");
		वापस -EINVAL;
	पूर्ण

	clk_set_parent(ick, xck);
	clk_set_rate(ick, xrate);

	bpfmd = fsi->chan_num * 32;
	ackmd = xrate / rate;

	dev_dbg(dev, "external/rate = %ld/%ld\n", xrate, rate);

	ret = fsi_clk_set_ackbpf(dev, fsi, ackmd, bpfmd);
	अगर (ret < 0)
		dev_err(dev, "%s failed", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक fsi_clk_set_rate_cpg(काष्ठा device *dev,
				काष्ठा fsi_priv *fsi)
अणु
	काष्ठा clk *ick = fsi->घड़ी.ick;
	काष्ठा clk *भाग = fsi->घड़ी.भाग;
	अचिन्हित दीर्घ rate = fsi->घड़ी.rate;
	अचिन्हित दीर्घ target = 0; /* 12288000 or 11289600 */
	अचिन्हित दीर्घ actual, cout;
	अचिन्हित दीर्घ dअगरf, min;
	अचिन्हित दीर्घ best_cout, best_act;
	पूर्णांक adj;
	पूर्णांक ackmd, bpfmd;
	पूर्णांक ret = -EINVAL;

	अगर (!(12288000 % rate))
		target = 12288000;
	अगर (!(11289600 % rate))
		target = 11289600;
	अगर (!target) अणु
		dev_err(dev, "unsupported rate\n");
		वापस ret;
	पूर्ण

	bpfmd = fsi->chan_num * 32;
	ackmd = target / rate;
	ret = fsi_clk_set_ackbpf(dev, fsi, ackmd, bpfmd);
	अगर (ret < 0) अणु
		dev_err(dev, "%s failed", __func__);
		वापस ret;
	पूर्ण

	/*
	 * The घड़ी flow is
	 *
	 * [CPG] = cout => [FSI_DIV] = audio => [FSI] => [codec]
	 *
	 * But, it needs to find best match of CPG and FSI_DIV
	 * combination, since it is dअगरficult to generate correct
	 * frequency of audio घड़ी from ick घड़ी only.
	 * Because ick is created from its parent घड़ी.
	 *
	 * target	= rate x [512/256/128/64]fs
	 * cout		= round(target x adjusपंचांगent)
	 * actual	= cout / adjusपंचांगent (by FSI-DIV) ~= target
	 * audio	= actual
	 */
	min = ~0;
	best_cout = 0;
	best_act = 0;
	क्रम (adj = 1; adj < 0xffff; adj++) अणु

		cout = target * adj;
		अगर (cout > 100000000) /* max घड़ी = 100MHz */
			अवरोध;

		/* cout/actual audio घड़ी */
		cout	= clk_round_rate(ick, cout);
		actual	= cout / adj;

		/* find best frequency */
		dअगरf = असल(actual - target);
		अगर (dअगरf < min) अणु
			min		= dअगरf;
			best_cout	= cout;
			best_act	= actual;
		पूर्ण
	पूर्ण

	ret = clk_set_rate(ick, best_cout);
	अगर (ret < 0) अणु
		dev_err(dev, "ick clock failed\n");
		वापस -EIO;
	पूर्ण

	ret = clk_set_rate(भाग, clk_round_rate(भाग, best_act));
	अगर (ret < 0) अणु
		dev_err(dev, "div clock failed\n");
		वापस -EIO;
	पूर्ण

	dev_dbg(dev, "ick/div = %ld/%ld\n",
		clk_get_rate(ick), clk_get_rate(भाग));

	वापस ret;
पूर्ण

अटल व्योम fsi_poपूर्णांकer_update(काष्ठा fsi_stream *io, पूर्णांक size)
अणु
	io->buff_sample_pos += size;

	अगर (io->buff_sample_pos >=
	    io->period_samples * (io->period_pos + 1)) अणु
		काष्ठा snd_pcm_substream *substream = io->substream;
		काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

		io->period_pos++;

		अगर (io->period_pos >= runसमय->periods) अणु
			io->buff_sample_pos = 0;
			io->period_pos = 0;
		पूर्ण

		snd_pcm_period_elapsed(substream);
	पूर्ण
पूर्ण

/*
 *		pio data transfer handler
 */
अटल व्योम fsi_pio_push16(काष्ठा fsi_priv *fsi, u8 *_buf, पूर्णांक samples)
अणु
	पूर्णांक i;

	अगर (fsi_is_enable_stream(fsi)) अणु
		/*
		 * stream mode
		 * see
		 *	fsi_pio_push_init()
		 */
		u32 *buf = (u32 *)_buf;

		क्रम (i = 0; i < samples / 2; i++)
			fsi_reg_ग_लिखो(fsi, DODT, buf[i]);
	पूर्ण अन्यथा अणु
		/* normal mode */
		u16 *buf = (u16 *)_buf;

		क्रम (i = 0; i < samples; i++)
			fsi_reg_ग_लिखो(fsi, DODT, ((u32)*(buf + i) << 8));
	पूर्ण
पूर्ण

अटल व्योम fsi_pio_pop16(काष्ठा fsi_priv *fsi, u8 *_buf, पूर्णांक samples)
अणु
	u16 *buf = (u16 *)_buf;
	पूर्णांक i;

	क्रम (i = 0; i < samples; i++)
		*(buf + i) = (u16)(fsi_reg_पढ़ो(fsi, DIDT) >> 8);
पूर्ण

अटल व्योम fsi_pio_push32(काष्ठा fsi_priv *fsi, u8 *_buf, पूर्णांक samples)
अणु
	u32 *buf = (u32 *)_buf;
	पूर्णांक i;

	क्रम (i = 0; i < samples; i++)
		fsi_reg_ग_लिखो(fsi, DODT, *(buf + i));
पूर्ण

अटल व्योम fsi_pio_pop32(काष्ठा fsi_priv *fsi, u8 *_buf, पूर्णांक samples)
अणु
	u32 *buf = (u32 *)_buf;
	पूर्णांक i;

	क्रम (i = 0; i < samples; i++)
		*(buf + i) = fsi_reg_पढ़ो(fsi, DIDT);
पूर्ण

अटल u8 *fsi_pio_get_area(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = io->substream->runसमय;

	वापस runसमय->dma_area +
		samples_to_bytes(runसमय, io->buff_sample_pos);
पूर्ण

अटल पूर्णांक fsi_pio_transfer(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io,
		व्योम (*run16)(काष्ठा fsi_priv *fsi, u8 *buf, पूर्णांक samples),
		व्योम (*run32)(काष्ठा fsi_priv *fsi, u8 *buf, पूर्णांक samples),
		पूर्णांक samples)
अणु
	u8 *buf;

	अगर (!fsi_stream_is_working(fsi, io))
		वापस -EINVAL;

	buf = fsi_pio_get_area(fsi, io);

	चयन (io->sample_width) अणु
	हाल 2:
		run16(fsi, buf, samples);
		अवरोध;
	हाल 4:
		run32(fsi, buf, samples);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	fsi_poपूर्णांकer_update(io, samples);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_pio_pop(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	पूर्णांक sample_residues;	/* samples in FSI fअगरo */
	पूर्णांक sample_space;	/* ALSA मुक्त samples space */
	पूर्णांक samples;

	sample_residues	= fsi_get_current_fअगरo_samples(fsi, io);
	sample_space	= io->buff_sample_capa - io->buff_sample_pos;

	samples = min(sample_residues, sample_space);

	वापस fsi_pio_transfer(fsi, io,
				  fsi_pio_pop16,
				  fsi_pio_pop32,
				  samples);
पूर्ण

अटल पूर्णांक fsi_pio_push(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	पूर्णांक sample_residues;	/* ALSA residue samples */
	पूर्णांक sample_space;	/* FSI fअगरo मुक्त samples space */
	पूर्णांक samples;

	sample_residues	= io->buff_sample_capa - io->buff_sample_pos;
	sample_space	= io->fअगरo_sample_capa -
		fsi_get_current_fअगरo_samples(fsi, io);

	samples = min(sample_residues, sample_space);

	वापस fsi_pio_transfer(fsi, io,
				  fsi_pio_push16,
				  fsi_pio_push32,
				  samples);
पूर्ण

अटल पूर्णांक fsi_pio_start_stop(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io,
			       पूर्णांक enable)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	u32 clk  = fsi_is_port_a(fsi) ? CRA  : CRB;

	अगर (enable)
		fsi_irq_enable(fsi, io);
	अन्यथा
		fsi_irq_disable(fsi, io);

	अगर (fsi_is_clk_master(fsi))
		fsi_master_mask_set(master, CLK_RST, clk, (enable) ? clk : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_pio_push_init(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	/*
	 * we can use 16bit stream mode
	 * when "playback" and "16bit data"
	 * and platक्रमm allows "stream mode"
	 * see
	 *	fsi_pio_push16()
	 */
	अगर (fsi_is_enable_stream(fsi))
		io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
				 BUSOP_SET(16, PACKAGE_16BITBUS_STREAM);
	अन्यथा
		io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
				 BUSOP_SET(16, PACKAGE_24BITBUS_BACK);
	वापस 0;
पूर्ण

अटल पूर्णांक fsi_pio_pop_init(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	/*
	 * always 24bit bus, package back when "capture"
	 */
	io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
			 BUSOP_SET(16, PACKAGE_24BITBUS_BACK);
	वापस 0;
पूर्ण

अटल काष्ठा fsi_stream_handler fsi_pio_push_handler = अणु
	.init		= fsi_pio_push_init,
	.transfer	= fsi_pio_push,
	.start_stop	= fsi_pio_start_stop,
पूर्ण;

अटल काष्ठा fsi_stream_handler fsi_pio_pop_handler = अणु
	.init		= fsi_pio_pop_init,
	.transfer	= fsi_pio_pop,
	.start_stop	= fsi_pio_start_stop,
पूर्ण;

अटल irqवापस_t fsi_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fsi_master *master = data;
	u32 पूर्णांक_st = fsi_irq_get_status(master);

	/* clear irq status */
	fsi_master_mask_set(master, SOFT_RST, IR, 0);
	fsi_master_mask_set(master, SOFT_RST, IR, IR);

	अगर (पूर्णांक_st & AB_IO(1, AO_SHIFT))
		fsi_stream_transfer(&master->fsia.playback);
	अगर (पूर्णांक_st & AB_IO(1, BO_SHIFT))
		fsi_stream_transfer(&master->fsib.playback);
	अगर (पूर्णांक_st & AB_IO(1, AI_SHIFT))
		fsi_stream_transfer(&master->fsia.capture);
	अगर (पूर्णांक_st & AB_IO(1, BI_SHIFT))
		fsi_stream_transfer(&master->fsib.capture);

	fsi_count_fअगरo_err(&master->fsia);
	fsi_count_fअगरo_err(&master->fsib);

	fsi_irq_clear_status(&master->fsia);
	fsi_irq_clear_status(&master->fsib);

	वापस IRQ_HANDLED;
पूर्ण

/*
 *		dma data transfer handler
 */
अटल पूर्णांक fsi_dma_init(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	/*
	 * 24bit data : 24bit bus / package in back
	 * 16bit data : 16bit bus / stream mode
	 */
	io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
			 BUSOP_SET(16, PACKAGE_16BITBUS_STREAM);

	वापस 0;
पूर्ण

अटल व्योम fsi_dma_complete(व्योम *data)
अणु
	काष्ठा fsi_stream *io = (काष्ठा fsi_stream *)data;
	काष्ठा fsi_priv *fsi = fsi_stream_to_priv(io);

	fsi_poपूर्णांकer_update(io, io->period_samples);

	fsi_count_fअगरo_err(fsi);
पूर्ण

अटल पूर्णांक fsi_dma_transfer(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	काष्ठा snd_soc_dai *dai = fsi_get_dai(io->substream);
	काष्ठा snd_pcm_substream *substream = io->substream;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);
	क्रमागत dma_transfer_direction dir;
	पूर्णांक ret = -EIO;

	अगर (is_play)
		dir = DMA_MEM_TO_DEV;
	अन्यथा
		dir = DMA_DEV_TO_MEM;

	desc = dmaengine_prep_dma_cyclic(io->chan,
					 substream->runसमय->dma_addr,
					 snd_pcm_lib_buffer_bytes(substream),
					 snd_pcm_lib_period_bytes(substream),
					 dir,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(dai->dev, "dmaengine_prep_dma_cyclic() fail\n");
		जाओ fsi_dma_transfer_err;
	पूर्ण

	desc->callback		= fsi_dma_complete;
	desc->callback_param	= io;

	अगर (dmaengine_submit(desc) < 0) अणु
		dev_err(dai->dev, "tx_submit() fail\n");
		जाओ fsi_dma_transfer_err;
	पूर्ण

	dma_async_issue_pending(io->chan);

	/*
	 * FIXME
	 *
	 * In DMAEngine हाल, codec and FSI cannot be started simultaneously
	 * since FSI is using the scheduler work queue.
	 * Thereक्रमe, in capture हाल, probably FSI FIFO will have got
	 * overflow error in this poपूर्णांक.
	 * in that हाल, DMA cannot start transfer until error was cleared.
	 */
	अगर (!is_play) अणु
		अगर (ERR_OVER & fsi_reg_पढ़ो(fsi, DIFF_ST)) अणु
			fsi_reg_mask_set(fsi, DIFF_CTL, FIFO_CLR, FIFO_CLR);
			fsi_reg_ग_लिखो(fsi, DIFF_ST, 0);
		पूर्ण
	पूर्ण

	ret = 0;

fsi_dma_transfer_err:
	वापस ret;
पूर्ण

अटल पूर्णांक fsi_dma_push_start_stop(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io,
				 पूर्णांक start)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	u32 clk  = fsi_is_port_a(fsi) ? CRA  : CRB;
	u32 enable = start ? DMA_ON : 0;

	fsi_reg_mask_set(fsi, OUT_DMAC, DMA_ON, enable);

	dmaengine_terminate_all(io->chan);

	अगर (fsi_is_clk_master(fsi))
		fsi_master_mask_set(master, CLK_RST, clk, (enable) ? clk : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_dma_probe(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io, काष्ठा device *dev)
अणु
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);

#अगर_घोषित CONFIG_SUPERH
	dma_cap_mask_t mask;
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	io->chan = dma_request_channel(mask, shdma_chan_filter,
				       (व्योम *)io->dma_id);
#अन्यथा
	io->chan = dma_request_slave_channel(dev, is_play ? "tx" : "rx");
#पूर्ण_अगर
	अगर (io->chan) अणु
		काष्ठा dma_slave_config cfg = अणुपूर्ण;
		पूर्णांक ret;

		अगर (is_play) अणु
			cfg.dst_addr		= fsi->phys + REG_DODT;
			cfg.dst_addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.direction		= DMA_MEM_TO_DEV;
		पूर्ण अन्यथा अणु
			cfg.src_addr		= fsi->phys + REG_DIDT;
			cfg.src_addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.direction		= DMA_DEV_TO_MEM;
		पूर्ण

		ret = dmaengine_slave_config(io->chan, &cfg);
		अगर (ret < 0) अणु
			dma_release_channel(io->chan);
			io->chan = शून्य;
		पूर्ण
	पूर्ण

	अगर (!io->chan) अणु

		/* चयन to PIO handler */
		अगर (is_play)
			fsi->playback.handler	= &fsi_pio_push_handler;
		अन्यथा
			fsi->capture.handler	= &fsi_pio_pop_handler;

		dev_info(dev, "switch handler (dma => pio)\n");

		/* probe again */
		वापस fsi_stream_probe(fsi, dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_dma_हटाओ(काष्ठा fsi_priv *fsi, काष्ठा fsi_stream *io)
अणु
	fsi_stream_stop(fsi, io);

	अगर (io->chan)
		dma_release_channel(io->chan);

	io->chan = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा fsi_stream_handler fsi_dma_push_handler = अणु
	.init		= fsi_dma_init,
	.probe		= fsi_dma_probe,
	.transfer	= fsi_dma_transfer,
	.हटाओ		= fsi_dma_हटाओ,
	.start_stop	= fsi_dma_push_start_stop,
पूर्ण;

/*
 *		dai ops
 */
अटल व्योम fsi_fअगरo_init(काष्ठा fsi_priv *fsi,
			  काष्ठा fsi_stream *io,
			  काष्ठा device *dev)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);
	पूर्णांक is_play = fsi_stream_is_play(fsi, io);
	u32 shअगरt, i;
	पूर्णांक frame_capa;

	/* get on-chip RAM capacity */
	shअगरt = fsi_master_पढ़ो(master, FIFO_SZ);
	shअगरt >>= fsi_get_port_shअगरt(fsi, io);
	shअगरt &= FIFO_SZ_MASK;
	frame_capa = 256 << shअगरt;
	dev_dbg(dev, "fifo = %d words\n", frame_capa);

	/*
	 * The maximum number of sample data varies depending
	 * on the number of channels selected क्रम the क्रमmat.
	 *
	 * FIFOs are used in 4-channel units in 3-channel mode
	 * and in 8-channel units in 5- to 7-channel mode
	 * meaning that more FIFOs than the required size of DPRAM
	 * are used.
	 *
	 * ex) अगर 256 words of DP-RAM is connected
	 * 1 channel:  256 (256 x 1 = 256)
	 * 2 channels: 128 (128 x 2 = 256)
	 * 3 channels:  64 ( 64 x 3 = 192)
	 * 4 channels:  64 ( 64 x 4 = 256)
	 * 5 channels:  32 ( 32 x 5 = 160)
	 * 6 channels:  32 ( 32 x 6 = 192)
	 * 7 channels:  32 ( 32 x 7 = 224)
	 * 8 channels:  32 ( 32 x 8 = 256)
	 */
	क्रम (i = 1; i < fsi->chan_num; i <<= 1)
		frame_capa >>= 1;
	dev_dbg(dev, "%d channel %d store\n",
		fsi->chan_num, frame_capa);

	io->fअगरo_sample_capa = fsi_frame2sample(fsi, frame_capa);

	/*
	 * set पूर्णांकerrupt generation factor
	 * clear FIFO
	 */
	अगर (is_play) अणु
		fsi_reg_ग_लिखो(fsi,	DOFF_CTL, IRQ_HALF);
		fsi_reg_mask_set(fsi,	DOFF_CTL, FIFO_CLR, FIFO_CLR);
	पूर्ण अन्यथा अणु
		fsi_reg_ग_लिखो(fsi,	DIFF_CTL, IRQ_HALF);
		fsi_reg_mask_set(fsi,	DIFF_CTL, FIFO_CLR, FIFO_CLR);
	पूर्ण
पूर्ण

अटल पूर्णांक fsi_hw_startup(काष्ठा fsi_priv *fsi,
			  काष्ठा fsi_stream *io,
			  काष्ठा device *dev)
अणु
	u32 data = 0;

	/* घड़ी setting */
	अगर (fsi_is_clk_master(fsi))
		data = DIMD | DOMD;

	fsi_reg_mask_set(fsi, CKG1, (DIMD | DOMD), data);

	/* घड़ी inversion (CKG2) */
	data = 0;
	अगर (fsi->bit_clk_inv)
		data |= (1 << 0);
	अगर (fsi->lr_clk_inv)
		data |= (1 << 4);
	अगर (fsi_is_clk_master(fsi))
		data <<= 8;
	fsi_reg_ग_लिखो(fsi, CKG2, data);

	/* spdअगर ? */
	अगर (fsi_is_spdअगर(fsi)) अणु
		fsi_spdअगर_clk_ctrl(fsi, 1);
		fsi_reg_mask_set(fsi, OUT_SEL, DMMD, DMMD);
	पूर्ण

	/*
	 * get bus settings
	 */
	data = 0;
	चयन (io->sample_width) अणु
	हाल 2:
		data = BUSOP_GET(16, io->bus_option);
		अवरोध;
	हाल 4:
		data = BUSOP_GET(24, io->bus_option);
		अवरोध;
	पूर्ण
	fsi_क्रमmat_bus_setup(fsi, io, data, dev);

	/* irq clear */
	fsi_irq_disable(fsi, io);
	fsi_irq_clear_status(fsi);

	/* fअगरo init */
	fsi_fअगरo_init(fsi, io, dev);

	/* start master घड़ी */
	अगर (fsi_is_clk_master(fsi))
		वापस fsi_clk_enable(dev, fsi);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_hw_shutकरोwn(काष्ठा fsi_priv *fsi,
			    काष्ठा device *dev)
अणु
	/* stop master घड़ी */
	अगर (fsi_is_clk_master(fsi))
		वापस fsi_clk_disable(dev, fsi);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_dai_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv(substream);

	fsi_clk_invalid(fsi);

	वापस 0;
पूर्ण

अटल व्योम fsi_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv(substream);

	fsi_clk_invalid(fsi);
पूर्ण

अटल पूर्णांक fsi_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv(substream);
	काष्ठा fsi_stream *io = fsi_stream_get(fsi, substream);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		fsi_stream_init(fsi, io, substream);
		अगर (!ret)
			ret = fsi_hw_startup(fsi, io, dai->dev);
		अगर (!ret)
			ret = fsi_stream_start(fsi, io);
		अगर (!ret)
			ret = fsi_stream_transfer(io);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (!ret)
			ret = fsi_hw_shutकरोwn(fsi, dai->dev);
		fsi_stream_stop(fsi, io);
		fsi_stream_quit(fsi, io);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsi_set_fmt_dai(काष्ठा fsi_priv *fsi, अचिन्हित पूर्णांक fmt)
अणु
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		fsi->fmt = CR_I2S;
		fsi->chan_num = 2;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		fsi->fmt = CR_PCM;
		fsi->chan_num = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_set_fmt_spdअगर(काष्ठा fsi_priv *fsi)
अणु
	काष्ठा fsi_master *master = fsi_get_master(fsi);

	अगर (fsi_version(master) < 2)
		वापस -EINVAL;

	fsi->fmt = CR_DTMD_SPDIF_PCM | CR_PCM;
	fsi->chan_num = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv_frm_dai(dai);
	पूर्णांक ret;

	/* set घड़ी master audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		fsi->clk_master = 1; /* cpu is master */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_IF:
		fsi->bit_clk_inv = 0;
		fsi->lr_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		fsi->bit_clk_inv = 1;
		fsi->lr_clk_inv = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		fsi->bit_clk_inv = 1;
		fsi->lr_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
	शेष:
		fsi->bit_clk_inv = 0;
		fsi->lr_clk_inv = 0;
		अवरोध;
	पूर्ण

	अगर (fsi_is_clk_master(fsi)) अणु
		अगर (fsi->clk_cpg)
			fsi_clk_init(dai->dev, fsi, 0, 1, 1,
				     fsi_clk_set_rate_cpg);
		अन्यथा
			fsi_clk_init(dai->dev, fsi, 1, 1, 0,
				     fsi_clk_set_rate_बाह्यal);
	पूर्ण

	/* set क्रमmat */
	अगर (fsi_is_spdअगर(fsi))
		ret = fsi_set_fmt_spdअगर(fsi);
	अन्यथा
		ret = fsi_set_fmt_dai(fsi, fmt & SND_SOC_DAIFMT_FORMAT_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक fsi_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv(substream);

	अगर (fsi_is_clk_master(fsi))
		fsi_clk_valid(fsi, params_rate(params));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsi_dai_ops = अणु
	.startup	= fsi_dai_startup,
	.shutकरोwn	= fsi_dai_shutकरोwn,
	.trigger	= fsi_dai_trigger,
	.set_fmt	= fsi_dai_set_fmt,
	.hw_params	= fsi_dai_hw_params,
पूर्ण;

/*
 *		pcm ops
 */

अटल स्थिर काष्ठा snd_pcm_hardware fsi_pcm_hardware = अणु
	.info =		SNDRV_PCM_INFO_INTERLEAVED	|
			SNDRV_PCM_INFO_MMAP		|
			SNDRV_PCM_INFO_MMAP_VALID,
	.buffer_bytes_max	= 64 * 1024,
	.period_bytes_min	= 32,
	.period_bytes_max	= 8192,
	.periods_min		= 1,
	.periods_max		= 32,
	.fअगरo_size		= 256,
पूर्ण;

अटल पूर्णांक fsi_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret = 0;

	snd_soc_set_runसमय_hwparams(substream, &fsi_pcm_hardware);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t fsi_poपूर्णांकer(काष्ठा snd_soc_component *component,
				     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fsi_priv *fsi = fsi_get_priv(substream);
	काष्ठा fsi_stream *io = fsi_stream_get(fsi, substream);

	वापस fsi_sample2frame(fsi, io->buff_sample_pos);
पूर्ण

/*
 *		snd_soc_component
 */

#घोषणा PREALLOC_BUFFER		(32 * 1024)
#घोषणा PREALLOC_BUFFER_MAX	(32 * 1024)

अटल पूर्णांक fsi_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_pcm_set_managed_buffer_all(
		rtd->pcm,
		SNDRV_DMA_TYPE_DEV,
		rtd->card->snd_card->dev,
		PREALLOC_BUFFER, PREALLOC_BUFFER_MAX);
	वापस 0;
पूर्ण

/*
 *		alsa काष्ठा
 */

अटल काष्ठा snd_soc_dai_driver fsi_soc_dai[] = अणु
	अणु
		.name			= "fsia-dai",
		.playback = अणु
			.rates		= FSI_RATES,
			.क्रमmats	= FSI_FMTS,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.capture = अणु
			.rates		= FSI_RATES,
			.क्रमmats	= FSI_FMTS,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.ops = &fsi_dai_ops,
	पूर्ण,
	अणु
		.name			= "fsib-dai",
		.playback = अणु
			.rates		= FSI_RATES,
			.क्रमmats	= FSI_FMTS,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.capture = अणु
			.rates		= FSI_RATES,
			.क्रमmats	= FSI_FMTS,
			.channels_min	= 2,
			.channels_max	= 2,
		पूर्ण,
		.ops = &fsi_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsi_soc_component = अणु
	.name		= "fsi",
	.खोलो		= fsi_pcm_खोलो,
	.poपूर्णांकer	= fsi_poपूर्णांकer,
	.pcm_स्थिरruct	= fsi_pcm_new,
पूर्ण;

/*
 *		platक्रमm function
 */
अटल व्योम fsi_of_parse(अक्षर *name,
			 काष्ठा device_node *np,
			 काष्ठा sh_fsi_port_info *info,
			 काष्ठा device *dev)
अणु
	पूर्णांक i;
	अक्षर prop[128];
	अचिन्हित दीर्घ flags = 0;
	काष्ठा अणु
		अक्षर *name;
		अचिन्हित पूर्णांक val;
	पूर्ण of_parse_property[] = अणु
		अणु "spdif-connection",		SH_FSI_FMT_SPDIF पूर्ण,
		अणु "stream-mode-support",	SH_FSI_ENABLE_STREAM_MODE पूर्ण,
		अणु "use-internal-clock",		SH_FSI_CLK_CPG पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(of_parse_property); i++) अणु
		प्र_लिखो(prop, "%s,%s", name, of_parse_property[i].name);
		अगर (of_get_property(np, prop, शून्य))
			flags |= of_parse_property[i].val;
	पूर्ण
	info->flags = flags;

	dev_dbg(dev, "%s flags : %lx\n", name, info->flags);
पूर्ण

अटल व्योम fsi_port_info_init(काष्ठा fsi_priv *fsi,
			       काष्ठा sh_fsi_port_info *info)
अणु
	अगर (info->flags & SH_FSI_FMT_SPDIF)
		fsi->spdअगर = 1;

	अगर (info->flags & SH_FSI_CLK_CPG)
		fsi->clk_cpg = 1;

	अगर (info->flags & SH_FSI_ENABLE_STREAM_MODE)
		fsi->enable_stream = 1;
पूर्ण

अटल व्योम fsi_handler_init(काष्ठा fsi_priv *fsi,
			     काष्ठा sh_fsi_port_info *info)
अणु
	fsi->playback.handler	= &fsi_pio_push_handler; /* शेष PIO */
	fsi->playback.priv	= fsi;
	fsi->capture.handler	= &fsi_pio_pop_handler;  /* शेष PIO */
	fsi->capture.priv	= fsi;

	अगर (info->tx_id) अणु
		fsi->playback.dma_id  = info->tx_id;
		fsi->playback.handler = &fsi_dma_push_handler;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fsi_core fsi1_core = अणु
	.ver	= 1,

	/* Interrupt */
	.पूर्णांक_st	= INT_ST,
	.iemsk	= IEMSK,
	.imsk	= IMSK,
पूर्ण;

अटल स्थिर काष्ठा fsi_core fsi2_core = अणु
	.ver	= 2,

	/* Interrupt */
	.पूर्णांक_st	= CPU_INT_ST,
	.iemsk	= CPU_IEMSK,
	.imsk	= CPU_IMSK,
	.a_mclk	= A_MST_CTLR,
	.b_mclk	= B_MST_CTLR,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsi_of_match[] = अणु
	अणु .compatible = "renesas,sh_fsi",	.data = &fsi1_coreपूर्ण,
	अणु .compatible = "renesas,sh_fsi2",	.data = &fsi2_coreपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsi_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id fsi_id_table[] = अणु
	अणु "sh_fsi",	(kernel_uदीर्घ_t)&fsi1_core पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, fsi_id_table);

अटल पूर्णांक fsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master *master;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sh_fsi_platक्रमm_info info;
	स्थिर काष्ठा fsi_core *core;
	काष्ठा fsi_priv *fsi;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	स_रखो(&info, 0, माप(info));

	core = शून्य;
	अगर (np) अणु
		core = of_device_get_match_data(&pdev->dev);
		fsi_of_parse("fsia", np, &info.port_a, &pdev->dev);
		fsi_of_parse("fsib", np, &info.port_b, &pdev->dev);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा platक्रमm_device_id	*id_entry = pdev->id_entry;
		अगर (id_entry)
			core = (काष्ठा fsi_core *)id_entry->driver_data;

		अगर (pdev->dev.platक्रमm_data)
			स_नकल(&info, pdev->dev.platक्रमm_data, माप(info));
	पूर्ण

	अगर (!core) अणु
		dev_err(&pdev->dev, "unknown fsi device\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!res || (पूर्णांक)irq <= 0) अणु
		dev_err(&pdev->dev, "Not enough FSI platform resources.\n");
		वापस -ENODEV;
	पूर्ण

	master = devm_kzalloc(&pdev->dev, माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!master->base) अणु
		dev_err(&pdev->dev, "Unable to ioremap FSI registers.\n");
		वापस -ENXIO;
	पूर्ण

	/* master setting */
	master->core		= core;
	spin_lock_init(&master->lock);

	/* FSI A setting */
	fsi		= &master->fsia;
	fsi->base	= master->base;
	fsi->phys	= res->start;
	fsi->master	= master;
	fsi_port_info_init(fsi, &info.port_a);
	fsi_handler_init(fsi, &info.port_a);
	ret = fsi_stream_probe(fsi, &pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "FSIA stream probe failed\n");
		वापस ret;
	पूर्ण

	/* FSI B setting */
	fsi		= &master->fsib;
	fsi->base	= master->base + 0x40;
	fsi->phys	= res->start + 0x40;
	fsi->master	= master;
	fsi_port_info_init(fsi, &info.port_b);
	fsi_handler_init(fsi, &info.port_b);
	ret = fsi_stream_probe(fsi, &pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "FSIB stream probe failed\n");
		जाओ निकास_fsia;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	dev_set_drvdata(&pdev->dev, master);

	ret = devm_request_irq(&pdev->dev, irq, &fsi_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request err\n");
		जाओ निकास_fsib;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsi_soc_component,
				    fsi_soc_dai, ARRAY_SIZE(fsi_soc_dai));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot snd component register\n");
		जाओ निकास_fsib;
	पूर्ण

	वापस ret;

निकास_fsib:
	pm_runसमय_disable(&pdev->dev);
	fsi_stream_हटाओ(&master->fsib);
निकास_fsia:
	fsi_stream_हटाओ(&master->fsia);

	वापस ret;
पूर्ण

अटल पूर्णांक fsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master *master;

	master = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);

	fsi_stream_हटाओ(&master->fsia);
	fsi_stream_हटाओ(&master->fsib);

	वापस 0;
पूर्ण

अटल व्योम __fsi_suspend(काष्ठा fsi_priv *fsi,
			  काष्ठा fsi_stream *io,
			  काष्ठा device *dev)
अणु
	अगर (!fsi_stream_is_working(fsi, io))
		वापस;

	fsi_stream_stop(fsi, io);
	fsi_hw_shutकरोwn(fsi, dev);
पूर्ण

अटल व्योम __fsi_resume(काष्ठा fsi_priv *fsi,
			 काष्ठा fsi_stream *io,
			 काष्ठा device *dev)
अणु
	अगर (!fsi_stream_is_working(fsi, io))
		वापस;

	fsi_hw_startup(fsi, io, dev);
	fsi_stream_start(fsi, io);
पूर्ण

अटल पूर्णांक fsi_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsi_master *master = dev_get_drvdata(dev);
	काष्ठा fsi_priv *fsia = &master->fsia;
	काष्ठा fsi_priv *fsib = &master->fsib;

	__fsi_suspend(fsia, &fsia->playback, dev);
	__fsi_suspend(fsia, &fsia->capture, dev);

	__fsi_suspend(fsib, &fsib->playback, dev);
	__fsi_suspend(fsib, &fsib->capture, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_resume(काष्ठा device *dev)
अणु
	काष्ठा fsi_master *master = dev_get_drvdata(dev);
	काष्ठा fsi_priv *fsia = &master->fsia;
	काष्ठा fsi_priv *fsib = &master->fsib;

	__fsi_resume(fsia, &fsia->playback, dev);
	__fsi_resume(fsia, &fsia->capture, dev);

	__fsi_resume(fsib, &fsib->playback, dev);
	__fsi_resume(fsib, &fsib->capture, dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsi_pm_ops = अणु
	.suspend		= fsi_suspend,
	.resume			= fsi_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsi_driver = अणु
	.driver 	= अणु
		.name	= "fsi-pcm-audio",
		.pm	= &fsi_pm_ops,
		.of_match_table = fsi_of_match,
	पूर्ण,
	.probe		= fsi_probe,
	.हटाओ		= fsi_हटाओ,
	.id_table	= fsi_id_table,
पूर्ण;

module_platक्रमm_driver(fsi_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SuperH onchip FSI audio driver");
MODULE_AUTHOR("Kuninori Morimoto <morimoto.kuninori@renesas.com>");
MODULE_ALIAS("platform:fsi-pcm-audio");
