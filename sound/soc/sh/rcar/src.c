<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car SRC support
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

/*
 * You can use Synchronous Sampling Rate Convert (अगर no DVC)
 *
 *	amixer set "SRC Out Rate" on
 *	aplay xxx.wav &
 *	amixer set "SRC Out Rate" 96000 // convert rate to 96000Hz
 *	amixer set "SRC Out Rate" 22050 // convert rate to 22050Hz
 */

/*
 * you can enable below define अगर you करोn't need
 * SSI पूर्णांकerrupt status debug message when debugging
 * see rsnd_dbg_irq_status()
 *
 * #घोषणा RSND_DEBUG_NO_IRQ_STATUS 1
 */

#समावेश "rsnd.h"

#घोषणा SRC_NAME "src"

/* SCU_SYSTEM_STATUS0/1 */
#घोषणा OUF_SRC(id)	((1 << (id + 16)) | (1 << id))

काष्ठा rsnd_src अणु
	काष्ठा rsnd_mod mod;
	काष्ठा rsnd_mod *dma;
	काष्ठा rsnd_kctrl_cfg_s sen;  /* sync convert enable */
	काष्ठा rsnd_kctrl_cfg_s sync; /* sync convert */
	पूर्णांक irq;
पूर्ण;

#घोषणा RSND_SRC_NAME_SIZE 16

#घोषणा rsnd_src_get(priv, id) ((काष्ठा rsnd_src *)(priv->src) + id)
#घोषणा rsnd_src_nr(priv) ((priv)->src_nr)
#घोषणा rsnd_src_sync_is_enabled(mod) (rsnd_mod_to_src(mod)->sen.val)

#घोषणा rsnd_mod_to_src(_mod)				\
	container_of((_mod), काष्ठा rsnd_src, mod)

#घोषणा क्रम_each_rsnd_src(pos, priv, i)				\
	क्रम ((i) = 0;						\
	     ((i) < rsnd_src_nr(priv)) &&			\
	     ((pos) = (काष्ठा rsnd_src *)(priv)->src + i);	\
	     i++)


/*
 *		image of SRC (Sampling Rate Converter)
 *
 * 96kHz   <-> +-----+	48kHz	+-----+	 48kHz	+-------+
 * 48kHz   <-> | SRC | <------>	| SSI |	<----->	| codec |
 * 44.1kHz <-> +-----+		+-----+		+-------+
 * ...
 *
 */

अटल व्योम rsnd_src_activation(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, SRC_SWRSR, 0);
	rsnd_mod_ग_लिखो(mod, SRC_SWRSR, 1);
पूर्ण

अटल व्योम rsnd_src_halt(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, SRC_SRCIR, 1);
	rsnd_mod_ग_लिखो(mod, SRC_SWRSR, 0);
पूर्ण

अटल काष्ठा dma_chan *rsnd_src_dma_req(काष्ठा rsnd_dai_stream *io,
					 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	पूर्णांक is_play = rsnd_io_is_play(io);

	वापस rsnd_dma_request_channel(rsnd_src_of_node(priv),
					mod,
					is_play ? "rx" : "tx");
पूर्ण

अटल u32 rsnd_src_convert_rate(काष्ठा rsnd_dai_stream *io,
				 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);
	u32 convert_rate;

	अगर (!runसमय)
		वापस 0;

	अगर (!rsnd_src_sync_is_enabled(mod))
		वापस rsnd_io_converted_rate(io);

	convert_rate = src->sync.val;

	अगर (!convert_rate)
		convert_rate = rsnd_io_converted_rate(io);

	अगर (!convert_rate)
		convert_rate = runसमय->rate;

	वापस convert_rate;
पूर्ण

अचिन्हित पूर्णांक rsnd_src_get_rate(काष्ठा rsnd_priv *priv,
			       काष्ठा rsnd_dai_stream *io,
			       पूर्णांक is_in)
अणु
	काष्ठा rsnd_mod *src_mod = rsnd_io_to_mod_src(io);
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	अचिन्हित पूर्णांक rate = 0;
	पूर्णांक is_play = rsnd_io_is_play(io);

	/*
	 * Playback
	 * runसमय_rate -> [SRC] -> convert_rate
	 *
	 * Capture
	 * convert_rate -> [SRC] -> runसमय_rate
	 */

	अगर (is_play == is_in)
		वापस runसमय->rate;

	/*
	 * वापस convert rate अगर SRC is used,
	 * otherwise, वापस runसमय->rate as usual
	 */
	अगर (src_mod)
		rate = rsnd_src_convert_rate(io, src_mod);

	अगर (!rate)
		rate = runसमय->rate;

	वापस rate;
पूर्ण

अटल स्थिर u32 bsdsr_table_pattern1[] = अणु
	0x01800000, /* 6 - 1/6 */
	0x01000000, /* 6 - 1/4 */
	0x00c00000, /* 6 - 1/3 */
	0x00800000, /* 6 - 1/2 */
	0x00600000, /* 6 - 2/3 */
	0x00400000, /* 6 - 1   */
पूर्ण;

अटल स्थिर u32 bsdsr_table_pattern2[] = अणु
	0x02400000, /* 6 - 1/6 */
	0x01800000, /* 6 - 1/4 */
	0x01200000, /* 6 - 1/3 */
	0x00c00000, /* 6 - 1/2 */
	0x00900000, /* 6 - 2/3 */
	0x00600000, /* 6 - 1   */
पूर्ण;

अटल स्थिर u32 bsisr_table[] = अणु
	0x00100060, /* 6 - 1/6 */
	0x00100040, /* 6 - 1/4 */
	0x00100030, /* 6 - 1/3 */
	0x00100020, /* 6 - 1/2 */
	0x00100020, /* 6 - 2/3 */
	0x00100020, /* 6 - 1   */
पूर्ण;

अटल स्थिर u32 chan288888[] = अणु
	0x00000006, /* 1 to 2 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
पूर्ण;

अटल स्थिर u32 chan244888[] = अणु
	0x00000006, /* 1 to 2 */
	0x0000001e, /* 1 to 4 */
	0x0000001e, /* 1 to 4 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
	0x000001fe, /* 1 to 8 */
पूर्ण;

अटल स्थिर u32 chan222222[] = अणु
	0x00000006, /* 1 to 2 */
	0x00000006, /* 1 to 2 */
	0x00000006, /* 1 to 2 */
	0x00000006, /* 1 to 2 */
	0x00000006, /* 1 to 2 */
	0x00000006, /* 1 to 2 */
पूर्ण;

अटल व्योम rsnd_src_set_convert_rate(काष्ठा rsnd_dai_stream *io,
				      काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	पूर्णांक is_play = rsnd_io_is_play(io);
	पूर्णांक use_src = 0;
	u32 fin, fout;
	u32 अगरscr, fsrate, adinr;
	u32 cr, route;
	u32 i_busअगर, o_busअगर, पंचांगp;
	स्थिर u32 *bsdsr_table;
	स्थिर u32 *chptn;
	uपूर्णांक ratio;
	पूर्णांक chan;
	पूर्णांक idx;

	अगर (!runसमय)
		वापस;

	fin  = rsnd_src_get_in_rate(priv, io);
	fout = rsnd_src_get_out_rate(priv, io);

	chan = rsnd_runसमय_channel_original(io);

	/* 6 - 1/6 are very enough ratio क्रम SRC_BSDSR */
	अगर (fin == fout)
		ratio = 0;
	अन्यथा अगर (fin > fout)
		ratio = 100 * fin / fout;
	अन्यथा
		ratio = 100 * fout / fin;

	अगर (ratio > 600) अणु
		dev_err(dev, "FSO/FSI ratio error\n");
		वापस;
	पूर्ण

	use_src = (fin != fout) | rsnd_src_sync_is_enabled(mod);

	/*
	 * SRC_ADINR
	 */
	adinr = rsnd_get_adinr_bit(mod, io) | chan;

	/*
	 * SRC_IFSCR / SRC_IFSVR
	 */
	अगरscr = 0;
	fsrate = 0;
	अगर (use_src) अणु
		u64 n;

		अगरscr = 1;
		n = (u64)0x0400000 * fin;
		करो_भाग(n, fout);
		fsrate = n;
	पूर्ण

	/*
	 * SRC_SRCCR / SRC_ROUTE_MODE0
	 */
	cr	= 0x00011110;
	route	= 0x0;
	अगर (use_src) अणु
		route	= 0x1;

		अगर (rsnd_src_sync_is_enabled(mod)) अणु
			cr |= 0x1;
			route |= rsnd_io_is_play(io) ?
				(0x1 << 24) : (0x1 << 25);
		पूर्ण
	पूर्ण

	/*
	 * SRC_BSDSR / SRC_BSISR
	 *
	 * see
	 *	Combination of Register Setting Related to
	 *	FSO/FSI Ratio and Channel, Latency
	 */
	चयन (rsnd_mod_id(mod)) अणु
	हाल 0:
		chptn		= chan288888;
		bsdsr_table	= bsdsr_table_pattern1;
		अवरोध;
	हाल 1:
	हाल 3:
	हाल 4:
		chptn		= chan244888;
		bsdsr_table	= bsdsr_table_pattern1;
		अवरोध;
	हाल 2:
	हाल 9:
		chptn		= chan222222;
		bsdsr_table	= bsdsr_table_pattern1;
		अवरोध;
	हाल 5:
	हाल 6:
	हाल 7:
	हाल 8:
		chptn		= chan222222;
		bsdsr_table	= bsdsr_table_pattern2;
		अवरोध;
	शेष:
		जाओ convert_rate_err;
	पूर्ण

	/*
	 * E3 need to overग_लिखो
	 */
	अगर (rsnd_is_e3(priv))
		चयन (rsnd_mod_id(mod)) अणु
		हाल 0:
		हाल 4:
			chptn	= chan222222;
		पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(chan222222); idx++)
		अगर (chptn[idx] & (1 << chan))
			अवरोध;

	अगर (chan > 8 ||
	    idx >= ARRAY_SIZE(chan222222))
		जाओ convert_rate_err;

	/* BUSIF_MODE */
	पंचांगp = rsnd_get_busअगर_shअगरt(io, mod);
	i_busअगर = ( is_play ? पंचांगp : 0) | 1;
	o_busअगर = (!is_play ? पंचांगp : 0) | 1;

	rsnd_mod_ग_लिखो(mod, SRC_ROUTE_MODE0, route);

	rsnd_mod_ग_लिखो(mod, SRC_SRCIR, 1);	/* initialize */
	rsnd_mod_ग_लिखो(mod, SRC_ADINR, adinr);
	rsnd_mod_ग_लिखो(mod, SRC_IFSCR, अगरscr);
	rsnd_mod_ग_लिखो(mod, SRC_IFSVR, fsrate);
	rsnd_mod_ग_लिखो(mod, SRC_SRCCR, cr);
	rsnd_mod_ग_लिखो(mod, SRC_BSDSR, bsdsr_table[idx]);
	rsnd_mod_ग_लिखो(mod, SRC_BSISR, bsisr_table[idx]);
	rsnd_mod_ग_लिखो(mod, SRC_SRCIR, 0);	/* cancel initialize */

	rsnd_mod_ग_लिखो(mod, SRC_I_BUSIF_MODE, i_busअगर);
	rsnd_mod_ग_लिखो(mod, SRC_O_BUSIF_MODE, o_busअगर);

	rsnd_mod_ग_लिखो(mod, SRC_BUSIF_DALIGN, rsnd_get_dalign(mod, io));

	rsnd_adg_set_src_बारel_gen2(mod, io, fin, fout);

	वापस;

convert_rate_err:
	dev_err(dev, "unknown BSDSR/BSDIR settings\n");
पूर्ण

अटल पूर्णांक rsnd_src_irq(काष्ठा rsnd_mod *mod,
			काष्ठा rsnd_dai_stream *io,
			काष्ठा rsnd_priv *priv,
			पूर्णांक enable)
अणु
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);
	u32 sys_पूर्णांक_val, पूर्णांक_val, sys_पूर्णांक_mask;
	पूर्णांक irq = src->irq;
	पूर्णांक id = rsnd_mod_id(mod);

	sys_पूर्णांक_val =
	sys_पूर्णांक_mask = OUF_SRC(id);
	पूर्णांक_val = 0x3300;

	/*
	 * IRQ is not supported on non-DT
	 * see
	 *	rsnd_src_probe_()
	 */
	अगर ((irq <= 0) || !enable) अणु
		sys_पूर्णांक_val = 0;
		पूर्णांक_val = 0;
	पूर्ण

	/*
	 * WORKAROUND
	 *
	 * ignore over flow error when rsnd_src_sync_is_enabled()
	 */
	अगर (rsnd_src_sync_is_enabled(mod))
		sys_पूर्णांक_val = sys_पूर्णांक_val & 0xffff;

	rsnd_mod_ग_लिखो(mod, SRC_INT_ENABLE0, पूर्णांक_val);
	rsnd_mod_bset(mod, SCU_SYS_INT_EN0, sys_पूर्णांक_mask, sys_पूर्णांक_val);
	rsnd_mod_bset(mod, SCU_SYS_INT_EN1, sys_पूर्णांक_mask, sys_पूर्णांक_val);

	वापस 0;
पूर्ण

अटल व्योम rsnd_src_status_clear(काष्ठा rsnd_mod *mod)
अणु
	u32 val = OUF_SRC(rsnd_mod_id(mod));

	rsnd_mod_ग_लिखो(mod, SCU_SYS_STATUS0, val);
	rsnd_mod_ग_लिखो(mod, SCU_SYS_STATUS1, val);
पूर्ण

अटल bool rsnd_src_error_occurred(काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	u32 val0, val1;
	u32 status0, status1;
	bool ret = false;

	val0 = val1 = OUF_SRC(rsnd_mod_id(mod));

	/*
	 * WORKAROUND
	 *
	 * ignore over flow error when rsnd_src_sync_is_enabled()
	 */
	अगर (rsnd_src_sync_is_enabled(mod))
		val0 = val0 & 0xffff;

	status0 = rsnd_mod_पढ़ो(mod, SCU_SYS_STATUS0);
	status1 = rsnd_mod_पढ़ो(mod, SCU_SYS_STATUS1);
	अगर ((status0 & val0) || (status1 & val1)) अणु
		rsnd_dbg_irq_status(dev, "%s err status : 0x%08x, 0x%08x\n",
			rsnd_mod_name(mod), status0, status1);

		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_src_start(काष्ठा rsnd_mod *mod,
			  काष्ठा rsnd_dai_stream *io,
			  काष्ठा rsnd_priv *priv)
अणु
	u32 val;

	/*
	 * WORKAROUND
	 *
	 * Enable SRC output अगर you want to use sync convert together with DVC
	 */
	val = (rsnd_io_to_mod_dvc(io) && !rsnd_src_sync_is_enabled(mod)) ?
		0x01 : 0x11;

	rsnd_mod_ग_लिखो(mod, SRC_CTRL, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_src_stop(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_ग_लिखो(mod, SRC_CTRL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_src_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);

	/* reset sync convert_rate */
	src->sync.val = 0;

	rsnd_mod_घातer_on(mod);

	rsnd_src_activation(mod);

	rsnd_src_set_convert_rate(io, mod);

	rsnd_src_status_clear(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_src_quit(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);

	rsnd_src_halt(mod);

	rsnd_mod_घातer_off(mod);

	/* reset sync convert_rate */
	src->sync.val = 0;

	वापस 0;
पूर्ण

अटल व्योम __rsnd_src_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
				 काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	bool stop = false;

	spin_lock(&priv->lock);

	/* ignore all हालs अगर not working */
	अगर (!rsnd_io_is_working(io))
		जाओ rsnd_src_पूर्णांकerrupt_out;

	अगर (rsnd_src_error_occurred(mod))
		stop = true;

	rsnd_src_status_clear(mod);
rsnd_src_पूर्णांकerrupt_out:

	spin_unlock(&priv->lock);

	अगर (stop)
		snd_pcm_stop_xrun(io->substream);
पूर्ण

अटल irqवापस_t rsnd_src_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rsnd_mod *mod = data;

	rsnd_mod_पूर्णांकerrupt(mod, __rsnd_src_पूर्णांकerrupt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rsnd_src_probe_(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक irq = src->irq;
	पूर्णांक ret;

	अगर (irq > 0) अणु
		/*
		 * IRQ is not supported on non-DT
		 * see
		 *	rsnd_src_irq()
		 */
		ret = devm_request_irq(dev, irq,
				       rsnd_src_पूर्णांकerrupt,
				       IRQF_SHARED,
				       dev_name(dev), mod);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = rsnd_dma_attach(io, mod, &src->dma);

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_src_pcm_new(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा rsnd_src *src = rsnd_mod_to_src(mod);
	पूर्णांक ret;

	/*
	 * enable SRC sync convert अगर possible
	 */

	/*
	 * It can't use SRC Synchronous convert
	 * when Capture अगर it uses CMD
	 */
	अगर (rsnd_io_to_mod_cmd(io) && !rsnd_io_is_play(io))
		वापस 0;

	/*
	 * enable sync convert
	 */
	ret = rsnd_kctrl_new_s(mod, io, rtd,
			       rsnd_io_is_play(io) ?
			       "SRC Out Rate Switch" :
			       "SRC In Rate Switch",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_src_set_convert_rate,
			       &src->sen, 1);
	अगर (ret < 0)
		वापस ret;

	ret = rsnd_kctrl_new_s(mod, io, rtd,
			       rsnd_io_is_play(io) ?
			       "SRC Out Rate" :
			       "SRC In Rate",
			       rsnd_kctrl_accept_runसमय,
			       rsnd_src_set_convert_rate,
			       &src->sync, 192000);

	वापस ret;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_src_ops = अणु
	.name		= SRC_NAME,
	.dma_req	= rsnd_src_dma_req,
	.probe		= rsnd_src_probe_,
	.init		= rsnd_src_init,
	.quit		= rsnd_src_quit,
	.start		= rsnd_src_start,
	.stop		= rsnd_src_stop,
	.irq		= rsnd_src_irq,
	.pcm_new	= rsnd_src_pcm_new,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

काष्ठा rsnd_mod *rsnd_src_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_src_nr(priv)))
		id = 0;

	वापस rsnd_mod_get(rsnd_src_get(priv, id));
पूर्ण

पूर्णांक rsnd_src_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_src *src;
	काष्ठा clk *clk;
	अक्षर name[RSND_SRC_NAME_SIZE];
	पूर्णांक i, nr, ret;

	/* This driver करोesn't support Gen1 at this poपूर्णांक */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	node = rsnd_src_of_node(priv);
	अगर (!node)
		वापस 0; /* not used is not error */

	nr = of_get_child_count(node);
	अगर (!nr) अणु
		ret = -EINVAL;
		जाओ rsnd_src_probe_करोne;
	पूर्ण

	src	= devm_kसुस्मृति(dev, nr, माप(*src), GFP_KERNEL);
	अगर (!src) अणु
		ret = -ENOMEM;
		जाओ rsnd_src_probe_करोne;
	पूर्ण

	priv->src_nr	= nr;
	priv->src	= src;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		अगर (!of_device_is_available(np))
			जाओ skip;

		src = rsnd_src_get(priv, i);

		snम_लिखो(name, RSND_SRC_NAME_SIZE, "%s.%d",
			 SRC_NAME, i);

		src->irq = irq_of_parse_and_map(np, 0);
		अगर (!src->irq) अणु
			ret = -EINVAL;
			of_node_put(np);
			जाओ rsnd_src_probe_करोne;
		पूर्ण

		clk = devm_clk_get(dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			of_node_put(np);
			जाओ rsnd_src_probe_करोne;
		पूर्ण

		ret = rsnd_mod_init(priv, rsnd_mod_get(src),
				    &rsnd_src_ops, clk, RSND_MOD_SRC, i);
		अगर (ret) अणु
			of_node_put(np);
			जाओ rsnd_src_probe_करोne;
		पूर्ण

skip:
		i++;
	पूर्ण

	ret = 0;

rsnd_src_probe_करोne:
	of_node_put(node);

	वापस ret;
पूर्ण

व्योम rsnd_src_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_src *src;
	पूर्णांक i;

	क्रम_each_rsnd_src(src, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(src));
	पूर्ण
पूर्ण
