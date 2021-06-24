<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car SRU/SCU/SSIU/SSI support
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
// Based on fsi.c
// Kuninori Morimoto <morimoto.kuninori@renesas.com>

/*
 * Renesas R-Car sound device काष्ठाure
 *
 * Gen1
 *
 * SRU		: Sound Routing Unit
 *  - SRC	: Sampling Rate Converter
 *  - CMD
 *    - CTU	: Channel Count Conversion Unit
 *    - MIX	: Mixer
 *    - DVC	: Digital Volume and Mute Function
 *  - SSI	: Serial Sound Interface
 *
 * Gen2
 *
 * SCU		: Sampling Rate Converter Unit
 *  - SRC	: Sampling Rate Converter
 *  - CMD
 *   - CTU	: Channel Count Conversion Unit
 *   - MIX	: Mixer
 *   - DVC	: Digital Volume and Mute Function
 * SSIU		: Serial Sound Interface Unit
 *  - SSI	: Serial Sound Interface
 */

/*
 *	driver data Image
 *
 * rsnd_priv
 *   |
 *   | ** this depends on Gen1/Gen2
 *   |
 *   +- gen
 *   |
 *   | ** these depend on data path
 *   | ** gen and platक्रमm data control it
 *   |
 *   +- rdai[0]
 *   |   |		 sru     ssiu      ssi
 *   |   +- playback -> [mod] -> [mod] -> [mod] -> ...
 *   |   |
 *   |   |		 sru     ssiu      ssi
 *   |   +- capture  -> [mod] -> [mod] -> [mod] -> ...
 *   |
 *   +- rdai[1]
 *   |   |		 sru     ssiu      ssi
 *   |   +- playback -> [mod] -> [mod] -> [mod] -> ...
 *   |   |
 *   |   |		 sru     ssiu      ssi
 *   |   +- capture  -> [mod] -> [mod] -> [mod] -> ...
 *   ...
 *   |
 *   | ** these control ssi
 *   |
 *   +- ssi
 *   |  |
 *   |  +- ssi[0]
 *   |  +- ssi[1]
 *   |  +- ssi[2]
 *   |  ...
 *   |
 *   | ** these control src
 *   |
 *   +- src
 *      |
 *      +- src[0]
 *      +- src[1]
 *      +- src[2]
 *      ...
 *
 *
 * क्रम_each_rsnd_dai(xx, priv, xx)
 *  rdai[0] => rdai[1] => rdai[2] => ...
 *
 * क्रम_each_rsnd_mod(xx, rdai, xx)
 *  [mod] => [mod] => [mod] => ...
 *
 * rsnd_dai_call(xxx, fn )
 *  [mod]->fn() -> [mod]->fn() -> [mod]->fn()...
 *
 */

/*
 * you can enable below define अगर you करोn't need
 * DAI status debug message when debugging
 * see rsnd_dbg_dai_call()
 *
 * #घोषणा RSND_DEBUG_NO_DAI_CALL 1
 */

#समावेश <linux/pm_runसमय.स>
#समावेश "rsnd.h"

#घोषणा RSND_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RSND_FMTS (SNDRV_PCM_FMTBIT_S8 |\
		   SNDRV_PCM_FMTBIT_S16_LE |\
		   SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा of_device_id rsnd_of_match[] = अणु
	अणु .compatible = "renesas,rcar_sound-gen1", .data = (व्योम *)RSND_GEN1 पूर्ण,
	अणु .compatible = "renesas,rcar_sound-gen2", .data = (व्योम *)RSND_GEN2 पूर्ण,
	अणु .compatible = "renesas,rcar_sound-gen3", .data = (व्योम *)RSND_GEN3 पूर्ण,
	/* Special Handling */
	अणु .compatible = "renesas,rcar_sound-r8a77990", .data = (व्योम *)(RSND_GEN3 | RSND_SOC_E) पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rsnd_of_match);

/*
 *	rsnd_mod functions
 */
व्योम rsnd_mod_make_sure(काष्ठा rsnd_mod *mod, क्रमागत rsnd_mod_type type)
अणु
	अगर (mod->type != type) अणु
		काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
		काष्ठा device *dev = rsnd_priv_to_dev(priv);

		dev_warn(dev, "%s is not your expected module\n",
			 rsnd_mod_name(mod));
	पूर्ण
पूर्ण

काष्ठा dma_chan *rsnd_mod_dma_req(काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_mod *mod)
अणु
	अगर (!mod || !mod->ops || !mod->ops->dma_req)
		वापस शून्य;

	वापस mod->ops->dma_req(io, mod);
पूर्ण

#घोषणा MOD_NAME_NUM   5
#घोषणा MOD_NAME_SIZE 16
अक्षर *rsnd_mod_name(काष्ठा rsnd_mod *mod)
अणु
	अटल अक्षर names[MOD_NAME_NUM][MOD_NAME_SIZE];
	अटल पूर्णांक num;
	अक्षर *name = names[num];

	num++;
	अगर (num >= MOD_NAME_NUM)
		num = 0;

	/*
	 * Let's use same अक्षर to aव्योम poपूर्णांकlessness memory
	 * Thus, rsnd_mod_name() should be used immediately
	 * Don't keep poपूर्णांकer
	 */
	अगर ((mod)->ops->id_sub) अणु
		snम_लिखो(name, MOD_NAME_SIZE, "%s[%d%d]",
			 mod->ops->name,
			 rsnd_mod_id(mod),
			 rsnd_mod_id_sub(mod));
	पूर्ण अन्यथा अणु
		snम_लिखो(name, MOD_NAME_SIZE, "%s[%d]",
			 mod->ops->name,
			 rsnd_mod_id(mod));
	पूर्ण

	वापस name;
पूर्ण

u32 *rsnd_mod_get_status(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 क्रमागत rsnd_mod_type type)
अणु
	वापस &mod->status;
पूर्ण

पूर्णांक rsnd_mod_id_raw(काष्ठा rsnd_mod *mod)
अणु
	वापस mod->id;
पूर्ण

पूर्णांक rsnd_mod_id(काष्ठा rsnd_mod *mod)
अणु
	अगर ((mod)->ops->id)
		वापस (mod)->ops->id(mod);

	वापस rsnd_mod_id_raw(mod);
पूर्ण

पूर्णांक rsnd_mod_id_sub(काष्ठा rsnd_mod *mod)
अणु
	अगर ((mod)->ops->id_sub)
		वापस (mod)->ops->id_sub(mod);

	वापस 0;
पूर्ण

पूर्णांक rsnd_mod_init(काष्ठा rsnd_priv *priv,
		  काष्ठा rsnd_mod *mod,
		  काष्ठा rsnd_mod_ops *ops,
		  काष्ठा clk *clk,
		  क्रमागत rsnd_mod_type type,
		  पूर्णांक id)
अणु
	पूर्णांक ret = clk_prepare(clk);

	अगर (ret)
		वापस ret;

	mod->id		= id;
	mod->ops	= ops;
	mod->type	= type;
	mod->clk	= clk;
	mod->priv	= priv;

	वापस 0;
पूर्ण

व्योम rsnd_mod_quit(काष्ठा rsnd_mod *mod)
अणु
	clk_unprepare(mod->clk);
	mod->clk = शून्य;
पूर्ण

व्योम rsnd_mod_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
			व्योम (*callback)(काष्ठा rsnd_mod *mod,
					 काष्ठा rsnd_dai_stream *io))
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा rsnd_dai *rdai;
	पूर्णांक i;

	क्रम_each_rsnd_dai(rdai, priv, i) अणु
		काष्ठा rsnd_dai_stream *io = &rdai->playback;

		अगर (mod == io->mod[mod->type])
			callback(mod, io);

		io = &rdai->capture;
		अगर (mod == io->mod[mod->type])
			callback(mod, io);
	पूर्ण
पूर्ण

पूर्णांक rsnd_io_is_working(काष्ठा rsnd_dai_stream *io)
अणु
	/* see rsnd_dai_stream_init/quit() */
	अगर (io->substream)
		वापस snd_pcm_running(io->substream);

	वापस 0;
पूर्ण

पूर्णांक rsnd_runसमय_channel_original_with_params(काष्ठा rsnd_dai_stream *io,
					      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);

	/*
	 * params will be added when refine
	 * see
	 *	__rsnd_soc_hw_rule_rate()
	 *	__rsnd_soc_hw_rule_channels()
	 */
	अगर (params)
		वापस params_channels(params);
	अन्यथा
		वापस runसमय->channels;
पूर्ण

पूर्णांक rsnd_runसमय_channel_after_ctu_with_params(काष्ठा rsnd_dai_stream *io,
					       काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक chan = rsnd_runसमय_channel_original_with_params(io, params);
	काष्ठा rsnd_mod *ctu_mod = rsnd_io_to_mod_ctu(io);

	अगर (ctu_mod) अणु
		u32 converted_chan = rsnd_io_converted_chan(io);

		/*
		 * !! Note !!
		 *
		 * converted_chan will be used क्रम CTU,
		 * or TDM Split mode.
		 * User shouldn't use CTU with TDM Split mode.
		 */
		अगर (rsnd_runसमय_is_tdm_split(io)) अणु
			काष्ठा device *dev = rsnd_priv_to_dev(rsnd_io_to_priv(io));

			dev_err(dev, "CTU and TDM Split should be used\n");
		पूर्ण

		अगर (converted_chan)
			वापस converted_chan;
	पूर्ण

	वापस chan;
पूर्ण

पूर्णांक rsnd_channel_normalization(पूर्णांक chan)
अणु
	अगर (WARN_ON((chan > 8) || (chan < 0)))
		वापस 0;

	/* TDM Extend Mode needs 8ch */
	अगर (chan == 6)
		chan = 8;

	वापस chan;
पूर्ण

पूर्णांक rsnd_runसमय_channel_क्रम_ssi_with_params(काष्ठा rsnd_dai_stream *io,
					     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	पूर्णांक chan = rsnd_io_is_play(io) ?
		rsnd_runसमय_channel_after_ctu_with_params(io, params) :
		rsnd_runसमय_channel_original_with_params(io, params);

	/* Use Multi SSI */
	अगर (rsnd_runसमय_is_multi_ssi(io))
		chan /= rsnd_rdai_ssi_lane_get(rdai);

	वापस rsnd_channel_normalization(chan);
पूर्ण

पूर्णांक rsnd_runसमय_is_multi_ssi(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	पूर्णांक lane = rsnd_rdai_ssi_lane_get(rdai);
	पूर्णांक chan = rsnd_io_is_play(io) ?
		rsnd_runसमय_channel_after_ctu(io) :
		rsnd_runसमय_channel_original(io);

	वापस (chan > 2) && (lane > 1);
पूर्ण

पूर्णांक rsnd_runसमय_is_tdm(काष्ठा rsnd_dai_stream *io)
अणु
	वापस rsnd_runसमय_channel_क्रम_ssi(io) >= 6;
पूर्ण

पूर्णांक rsnd_runसमय_is_tdm_split(काष्ठा rsnd_dai_stream *io)
अणु
	वापस !!rsnd_flags_has(io, RSND_STREAM_TDM_SPLIT);
पूर्ण

/*
 *	ADINR function
 */
u32 rsnd_get_adinr_bit(काष्ठा rsnd_mod *mod, काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	चयन (snd_pcm_क्रमmat_width(runसमय->क्रमmat)) अणु
	हाल 8:
		वापस 16 << 16;
	हाल 16:
		वापस 8 << 16;
	हाल 24:
		वापस 0 << 16;
	पूर्ण

	dev_warn(dev, "not supported sample bits\n");

	वापस 0;
पूर्ण

/*
 *	DALIGN function
 */
u32 rsnd_get_dalign(काष्ठा rsnd_mod *mod, काष्ठा rsnd_dai_stream *io)
अणु
	अटल स्थिर u32 dalign_values[8] = अणु
		0x76543210, 0x00000032, 0x00007654, 0x00000076,
		0xfedcba98, 0x000000ba, 0x0000fedc, 0x000000fe,
	पूर्ण;
	पूर्णांक id = 0;
	काष्ठा rsnd_mod *ssiu = rsnd_io_to_mod_ssiu(io);
	काष्ठा rsnd_mod *target;
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	u32 dalign;

	/*
	 * *Hardware* L/R and *Software* L/R are inverted क्रम 16bit data.
	 *	    31..16 15...0
	 *	HW: [L ch] [R ch]
	 *	SW: [R ch] [L ch]
	 * We need to care about inversion timing to control
	 * Playback/Capture correctly.
	 * The poपूर्णांक is [DVC] needs *Hardware* L/R, [MEM] needs *Software* L/R
	 *
	 * sL/R : software L/R
	 * hL/R : hardware L/R
	 * (*)  : conversion timing
	 *
	 * Playback
	 *	     sL/R (*) hL/R     hL/R     hL/R      hL/R     hL/R
	 *	[MEM] -> [SRC] -> [DVC] -> [CMD] -> [SSIU] -> [SSI] -> codec
	 *
	 * Capture
	 *	     hL/R     hL/R      hL/R     hL/R     hL/R (*) sL/R
	 *	codec -> [SSI] -> [SSIU] -> [SRC] -> [DVC] -> [CMD] -> [MEM]
	 */
	अगर (rsnd_io_is_play(io)) अणु
		काष्ठा rsnd_mod *src = rsnd_io_to_mod_src(io);

		target = src ? src : ssiu;
	पूर्ण अन्यथा अणु
		काष्ठा rsnd_mod *cmd = rsnd_io_to_mod_cmd(io);

		target = cmd ? cmd : ssiu;
	पूर्ण

	अगर (mod == ssiu)
		id = rsnd_mod_id_sub(mod);

	dalign = dalign_values[id];

	अगर (mod == target && snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16) अणु
		/* Target mod needs inverted DALIGN when 16bit */
		dalign = (dalign & 0xf0f0f0f0) >> 4 |
			 (dalign & 0x0f0f0f0f) << 4;
	पूर्ण

	वापस dalign;
पूर्ण

u32 rsnd_get_busअगर_shअगरt(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_mod *mod)
अणु
	क्रमागत rsnd_mod_type playback_mods[] = अणु
		RSND_MOD_SRC,
		RSND_MOD_CMD,
		RSND_MOD_SSIU,
	पूर्ण;
	क्रमागत rsnd_mod_type capture_mods[] = अणु
		RSND_MOD_CMD,
		RSND_MOD_SRC,
		RSND_MOD_SSIU,
	पूर्ण;
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_mod *पंचांगod = शून्य;
	क्रमागत rsnd_mod_type *mods =
		rsnd_io_is_play(io) ?
		playback_mods : capture_mods;
	पूर्णांक i;

	/*
	 * This is needed क्रम 24bit data
	 * We need to shअगरt 8bit
	 *
	 * Linux 24bit data is located as 0x00******
	 * HW    24bit data is located as 0x******00
	 *
	 */
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) != 24)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(playback_mods); i++) अणु
		पंचांगod = rsnd_io_to_mod(io, mods[i]);
		अगर (पंचांगod)
			अवरोध;
	पूर्ण

	अगर (पंचांगod != mod)
		वापस 0;

	अगर (rsnd_io_is_play(io))
		वापस  (0 << 20) | /* shअगरt to Left */
			(8 << 16);  /* 8bit */
	अन्यथा
		वापस  (1 << 20) | /* shअगरt to Right */
			(8 << 16);  /* 8bit */
पूर्ण

/*
 *	rsnd_dai functions
 */
काष्ठा rsnd_mod *rsnd_mod_next(पूर्णांक *iterator,
			       काष्ठा rsnd_dai_stream *io,
			       क्रमागत rsnd_mod_type *array,
			       पूर्णांक array_size)
अणु
	पूर्णांक max = array ? array_size : RSND_MOD_MAX;

	क्रम (; *iterator < max; (*iterator)++) अणु
		क्रमागत rsnd_mod_type type = (array) ? array[*iterator] : *iterator;
		काष्ठा rsnd_mod *mod = rsnd_io_to_mod(io, type);

		अगर (mod)
			वापस mod;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत rsnd_mod_type rsnd_mod_sequence[][RSND_MOD_MAX] = अणु
	अणु
		/* CAPTURE */
		RSND_MOD_AUDMAPP,
		RSND_MOD_AUDMA,
		RSND_MOD_DVC,
		RSND_MOD_MIX,
		RSND_MOD_CTU,
		RSND_MOD_CMD,
		RSND_MOD_SRC,
		RSND_MOD_SSIU,
		RSND_MOD_SSIM3,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM1,
		RSND_MOD_SSIP,
		RSND_MOD_SSI,
	पूर्ण, अणु
		/* PLAYBACK */
		RSND_MOD_AUDMAPP,
		RSND_MOD_AUDMA,
		RSND_MOD_SSIM3,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM1,
		RSND_MOD_SSIP,
		RSND_MOD_SSI,
		RSND_MOD_SSIU,
		RSND_MOD_DVC,
		RSND_MOD_MIX,
		RSND_MOD_CTU,
		RSND_MOD_CMD,
		RSND_MOD_SRC,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rsnd_status_update(u32 *status,
			      पूर्णांक shअगरt, पूर्णांक add, पूर्णांक timing)
अणु
	u32 mask	= 0xF << shअगरt;
	u8 val		= (*status >> shअगरt) & 0xF;
	u8 next_val	= (val + add) & 0xF;
	पूर्णांक func_call	= (val == timing);

	अगर (next_val == 0xF) /* underflow हाल */
		func_call = 0;
	अन्यथा
		*status = (*status & ~mask) + (next_val << shअगरt);

	वापस func_call;
पूर्ण

#घोषणा rsnd_dai_call(fn, io, param...)					\
(अणु									\
	काष्ठा device *dev = rsnd_priv_to_dev(rsnd_io_to_priv(io));	\
	काष्ठा rsnd_mod *mod;						\
	पूर्णांक is_play = rsnd_io_is_play(io);				\
	पूर्णांक ret = 0, i;							\
	क्रमागत rsnd_mod_type *types = rsnd_mod_sequence[is_play];		\
	क्रम_each_rsnd_mod_arrays(i, mod, io, types, RSND_MOD_MAX) अणु	\
		पूर्णांक पंचांगp = 0;						\
		u32 *status = mod->ops->get_status(mod, io, types[i]);	\
		पूर्णांक func_call = rsnd_status_update(status,		\
						__rsnd_mod_shअगरt_##fn,	\
						__rsnd_mod_add_##fn,	\
						__rsnd_mod_call_##fn);	\
		rsnd_dbg_dai_call(dev, "%s\t0x%08x %s\n",		\
			rsnd_mod_name(mod), *status,	\
			(func_call && (mod)->ops->fn) ? #fn : "");	\
		अगर (func_call && (mod)->ops->fn)			\
			पंचांगp = (mod)->ops->fn(mod, io, param);		\
		अगर (पंचांगp && (पंचांगp != -EPROBE_DEFER))			\
			dev_err(dev, "%s : %s error %d\n",		\
				rsnd_mod_name(mod), #fn, पंचांगp);		\
		ret |= पंचांगp;						\
	पूर्ण								\
	ret;								\
पूर्ण)

पूर्णांक rsnd_dai_connect(काष्ठा rsnd_mod *mod,
		     काष्ठा rsnd_dai_stream *io,
		     क्रमागत rsnd_mod_type type)
अणु
	काष्ठा rsnd_priv *priv;
	काष्ठा device *dev;

	अगर (!mod)
		वापस -EIO;

	अगर (io->mod[type] == mod)
		वापस 0;

	अगर (io->mod[type])
		वापस -EINVAL;

	priv = rsnd_mod_to_priv(mod);
	dev = rsnd_priv_to_dev(priv);

	io->mod[type] = mod;

	dev_dbg(dev, "%s is connected to io (%s)\n",
		rsnd_mod_name(mod),
		rsnd_io_is_play(io) ? "Playback" : "Capture");

	वापस 0;
पूर्ण

अटल व्योम rsnd_dai_disconnect(काष्ठा rsnd_mod *mod,
				काष्ठा rsnd_dai_stream *io,
				क्रमागत rsnd_mod_type type)
अणु
	io->mod[type] = शून्य;
पूर्ण

पूर्णांक rsnd_rdai_channels_ctrl(काष्ठा rsnd_dai *rdai,
			    पूर्णांक max_channels)
अणु
	अगर (max_channels > 0)
		rdai->max_channels = max_channels;

	वापस rdai->max_channels;
पूर्ण

पूर्णांक rsnd_rdai_ssi_lane_ctrl(काष्ठा rsnd_dai *rdai,
			    पूर्णांक ssi_lane)
अणु
	अगर (ssi_lane > 0)
		rdai->ssi_lane = ssi_lane;

	वापस rdai->ssi_lane;
पूर्ण

पूर्णांक rsnd_rdai_width_ctrl(काष्ठा rsnd_dai *rdai, पूर्णांक width)
अणु
	अगर (width > 0)
		rdai->chan_width = width;

	वापस rdai->chan_width;
पूर्ण

काष्ठा rsnd_dai *rsnd_rdai_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर ((id < 0) || (id >= rsnd_rdai_nr(priv)))
		वापस शून्य;

	वापस priv->rdai + id;
पूर्ण

अटल काष्ठा snd_soc_dai_driver
*rsnd_daidrv_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर ((id < 0) || (id >= rsnd_rdai_nr(priv)))
		वापस शून्य;

	वापस priv->daidrv + id;
पूर्ण

#घोषणा rsnd_dai_to_priv(dai) snd_soc_dai_get_drvdata(dai)
अटल काष्ठा rsnd_dai *rsnd_dai_to_rdai(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_priv *priv = rsnd_dai_to_priv(dai);

	वापस rsnd_rdai_get(priv, dai->id);
पूर्ण

/*
 *	rsnd_soc_dai functions
 */
व्योम rsnd_dai_period_elapsed(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा snd_pcm_substream *substream = io->substream;

	/*
	 * this function should be called...
	 *
	 * - अगर rsnd_dai_poपूर्णांकer_update() वापसs true
	 * - without spin lock
	 */

	snd_pcm_period_elapsed(substream);
पूर्ण

अटल व्योम rsnd_dai_stream_init(काष्ठा rsnd_dai_stream *io,
				काष्ठा snd_pcm_substream *substream)
अणु
	io->substream		= substream;
पूर्ण

अटल व्योम rsnd_dai_stream_quit(काष्ठा rsnd_dai_stream *io)
अणु
	io->substream		= शून्य;
पूर्ण

अटल
काष्ठा snd_soc_dai *rsnd_substream_to_dai(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	वापस  asoc_rtd_to_cpu(rtd, 0);
पूर्ण

अटल
काष्ठा rsnd_dai_stream *rsnd_rdai_to_io(काष्ठा rsnd_dai *rdai,
					काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस &rdai->playback;
	अन्यथा
		वापस &rdai->capture;
पूर्ण

अटल पूर्णांक rsnd_soc_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_priv *priv = rsnd_dai_to_priv(dai);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ret = rsnd_dai_call(init, io, priv);
		अगर (ret < 0)
			जाओ dai_trigger_end;

		ret = rsnd_dai_call(start, io, priv);
		अगर (ret < 0)
			जाओ dai_trigger_end;

		ret = rsnd_dai_call(irq, io, priv, 1);
		अगर (ret < 0)
			जाओ dai_trigger_end;

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ret = rsnd_dai_call(irq, io, priv, 0);

		ret |= rsnd_dai_call(stop, io, priv);

		ret |= rsnd_dai_call(quit, io, priv);

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

dai_trigger_end:
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_soc_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);

	/* set घड़ी master क्रम audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rdai->clk_master = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		rdai->clk_master = 1; /* cpu is master */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set क्रमmat */
	rdai->bit_clk_inv = 0;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		rdai->sys_delay = 0;
		rdai->data_alignment = 0;
		rdai->frm_clk_inv = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_DSP_B:
		rdai->sys_delay = 1;
		rdai->data_alignment = 0;
		rdai->frm_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		rdai->sys_delay = 1;
		rdai->data_alignment = 1;
		rdai->frm_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		rdai->sys_delay = 0;
		rdai->data_alignment = 0;
		rdai->frm_clk_inv = 1;
		अवरोध;
	पूर्ण

	/* set घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_IF:
		rdai->frm_clk_inv = !rdai->frm_clk_inv;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		rdai->bit_clk_inv = !rdai->bit_clk_inv;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		rdai->bit_clk_inv = !rdai->bit_clk_inv;
		rdai->frm_clk_inv = !rdai->frm_clk_inv;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_soc_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				     u32 tx_mask, u32 rx_mask,
				     पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा rsnd_priv *priv = rsnd_dai_to_priv(dai);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	चयन (slot_width) अणु
	हाल 16:
	हाल 24:
	हाल 32:
		अवरोध;
	शेष:
		/* use शेष */
		slot_width = 32;
	पूर्ण

	चयन (slots) अणु
	हाल 2:
		/* TDM Split Mode */
	हाल 6:
	हाल 8:
		/* TDM Extend Mode */
		rsnd_rdai_channels_set(rdai, slots);
		rsnd_rdai_ssi_lane_set(rdai, 1);
		rsnd_rdai_width_set(rdai, slot_width);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported TDM slots (%d)\n", slots);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rsnd_soc_hw_channels_list[] = अणु
	2, 6, 8,
पूर्ण;

अटल अचिन्हित पूर्णांक rsnd_soc_hw_rate_list[] = अणु
	  8000,
	 11025,
	 16000,
	 22050,
	 32000,
	 44100,
	 48000,
	 64000,
	 88200,
	 96000,
	176400,
	192000,
पूर्ण;

अटल पूर्णांक rsnd_soc_hw_rule(काष्ठा rsnd_dai *rdai,
			    अचिन्हित पूर्णांक *list, पूर्णांक list_num,
			    काष्ठा snd_पूर्णांकerval *baseline, काष्ठा snd_पूर्णांकerval *iv)
अणु
	काष्ठा snd_पूर्णांकerval p;
	अचिन्हित पूर्णांक rate;
	पूर्णांक i;

	snd_पूर्णांकerval_any(&p);
	p.min = अच_पूर्णांक_उच्च;
	p.max = 0;

	क्रम (i = 0; i < list_num; i++) अणु

		अगर (!snd_पूर्णांकerval_test(iv, list[i]))
			जारी;

		rate = rsnd_ssi_clk_query(rdai,
					  baseline->min, list[i], शून्य);
		अगर (rate > 0) अणु
			p.min = min(p.min, list[i]);
			p.max = max(p.max, list[i]);
		पूर्ण

		rate = rsnd_ssi_clk_query(rdai,
					  baseline->max, list[i], शून्य);
		अगर (rate > 0) अणु
			p.min = min(p.min, list[i]);
			p.max = max(p.max, list[i]);
		पूर्ण
	पूर्ण

	वापस snd_पूर्णांकerval_refine(iv, &p);
पूर्ण

अटल पूर्णांक rsnd_soc_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *ic_ = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *ir = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval ic;
	काष्ठा rsnd_dai_stream *io = rule->निजी;
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);

	/*
	 * possible sampling rate limitation is same as
	 * 2ch अगर it supports multi ssi
	 * and same as 8ch अगर TDM 6ch (see rsnd_ssi_config_init())
	 */
	ic = *ic_;
	ic.min =
	ic.max = rsnd_runसमय_channel_क्रम_ssi_with_params(io, params);

	वापस rsnd_soc_hw_rule(rdai, rsnd_soc_hw_rate_list,
				ARRAY_SIZE(rsnd_soc_hw_rate_list),
				&ic, ir);
पूर्ण

अटल पूर्णांक rsnd_soc_hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *ic_ = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *ir = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval ic;
	काष्ठा rsnd_dai_stream *io = rule->निजी;
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);

	/*
	 * possible sampling rate limitation is same as
	 * 2ch अगर it supports multi ssi
	 * and same as 8ch अगर TDM 6ch (see rsnd_ssi_config_init())
	 */
	ic = *ic_;
	ic.min =
	ic.max = rsnd_runसमय_channel_क्रम_ssi_with_params(io, params);

	वापस rsnd_soc_hw_rule(rdai, rsnd_soc_hw_channels_list,
				ARRAY_SIZE(rsnd_soc_hw_channels_list),
				ir, &ic);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware rsnd_pcm_hardware = अणु
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

अटल पूर्णांक rsnd_soc_dai_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *स्थिरraपूर्णांक = &rdai->स्थिरraपूर्णांक;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक max_channels = rsnd_rdai_channels_get(rdai);
	पूर्णांक i;

	rsnd_dai_stream_init(io, substream);

	/*
	 * Channel Limitation
	 * It depends on Platक्रमm design
	 */
	स्थिरraपूर्णांक->list	= rsnd_soc_hw_channels_list;
	स्थिरraपूर्णांक->count	= 0;
	स्थिरraपूर्णांक->mask	= 0;

	क्रम (i = 0; i < ARRAY_SIZE(rsnd_soc_hw_channels_list); i++) अणु
		अगर (rsnd_soc_hw_channels_list[i] > max_channels)
			अवरोध;
		स्थिरraपूर्णांक->count = i + 1;
	पूर्ण

	snd_soc_set_runसमय_hwparams(substream, &rsnd_pcm_hardware);

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS, स्थिरraपूर्णांक);

	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
				      SNDRV_PCM_HW_PARAM_PERIODS);

	/*
	 * Sampling Rate / Channel Limitation
	 * It depends on Clock Master Mode
	 */
	अगर (rsnd_rdai_is_clk_master(rdai)) अणु
		पूर्णांक is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

		snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				    rsnd_soc_hw_rule_rate,
				    is_play ? &rdai->playback : &rdai->capture,
				    SNDRV_PCM_HW_PARAM_CHANNELS, -1);
		snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				    rsnd_soc_hw_rule_channels,
				    is_play ? &rdai->playback : &rdai->capture,
				    SNDRV_PCM_HW_PARAM_RATE, -1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rsnd_soc_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);

	/*
	 * call rsnd_dai_call without spinlock
	 */
	rsnd_dai_call(cleanup, io, priv);

	rsnd_dai_stream_quit(io);
पूर्ण

अटल पूर्णांक rsnd_soc_dai_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_priv *priv = rsnd_dai_to_priv(dai);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);

	वापस rsnd_dai_call(prepare, io, priv);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rsnd_soc_dai_ops = अणु
	.startup	= rsnd_soc_dai_startup,
	.shutकरोwn	= rsnd_soc_dai_shutकरोwn,
	.trigger	= rsnd_soc_dai_trigger,
	.set_fmt	= rsnd_soc_dai_set_fmt,
	.set_tdm_slot	= rsnd_soc_set_dai_tdm_slot,
	.prepare	= rsnd_soc_dai_prepare,
पूर्ण;

अटल व्योम rsnd_parse_tdm_split_mode(काष्ठा rsnd_priv *priv,
				      काष्ठा rsnd_dai_stream *io,
				      काष्ठा device_node *dai_np)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *ssiu_np = rsnd_ssiu_of_node(priv);
	काष्ठा device_node *np;
	पूर्णांक is_play = rsnd_io_is_play(io);
	पूर्णांक i;

	अगर (!ssiu_np)
		वापस;

	/*
	 * This driver assumes that it is TDM Split mode
	 * अगर it includes ssiu node
	 */
	क्रम (i = 0;; i++) अणु
		काष्ठा device_node *node = is_play ?
			of_parse_phandle(dai_np, "playback", i) :
			of_parse_phandle(dai_np, "capture",  i);

		अगर (!node)
			अवरोध;

		क्रम_each_child_of_node(ssiu_np, np) अणु
			अगर (np == node) अणु
				rsnd_flags_set(io, RSND_STREAM_TDM_SPLIT);
				dev_dbg(dev, "%s is part of TDM Split\n", io->name);
			पूर्ण
		पूर्ण

		of_node_put(node);
	पूर्ण

	of_node_put(ssiu_np);
पूर्ण

अटल व्योम rsnd_parse_connect_simple(काष्ठा rsnd_priv *priv,
				      काष्ठा rsnd_dai_stream *io,
				      काष्ठा device_node *dai_np)
अणु
	अगर (!rsnd_io_to_mod_ssi(io))
		वापस;

	rsnd_parse_tdm_split_mode(priv, io, dai_np);
पूर्ण

अटल व्योम rsnd_parse_connect_graph(काष्ठा rsnd_priv *priv,
				     काष्ठा rsnd_dai_stream *io,
				     काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *remote_node;

	अगर (!rsnd_io_to_mod_ssi(io))
		वापस;

	remote_node = of_graph_get_remote_port_parent(endpoपूर्णांक);

	/* HDMI0 */
	अगर (म_माला(remote_node->full_name, "hdmi@fead0000")) अणु
		rsnd_flags_set(io, RSND_STREAM_HDMI0);
		dev_dbg(dev, "%s connected to HDMI0\n", io->name);
	पूर्ण

	/* HDMI1 */
	अगर (म_माला(remote_node->full_name, "hdmi@feae0000")) अणु
		rsnd_flags_set(io, RSND_STREAM_HDMI1);
		dev_dbg(dev, "%s connected to HDMI1\n", io->name);
	पूर्ण

	rsnd_parse_tdm_split_mode(priv, io, endpoपूर्णांक);

	of_node_put(remote_node);
पूर्ण

व्योम rsnd_parse_connect_common(काष्ठा rsnd_dai *rdai,
		काष्ठा rsnd_mod* (*mod_get)(काष्ठा rsnd_priv *priv, पूर्णांक id),
		काष्ठा device_node *node,
		काष्ठा device_node *playback,
		काष्ठा device_node *capture)
अणु
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा device_node *np;
	पूर्णांक i;

	अगर (!node)
		वापस;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		काष्ठा rsnd_mod *mod = mod_get(priv, i);

		अगर (np == playback)
			rsnd_dai_connect(mod, &rdai->playback, mod->type);
		अगर (np == capture)
			rsnd_dai_connect(mod, &rdai->capture, mod->type);
		i++;
	पूर्ण

	of_node_put(node);
पूर्ण

अटल काष्ठा device_node *rsnd_dai_of_node(काष्ठा rsnd_priv *priv,
					    पूर्णांक *is_graph)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *dai_node;
	काष्ठा device_node *ret;

	*is_graph = 0;

	/*
	 * parse both previous dai (= rcar_sound,dai), and
	 * graph dai (= ports/port)
	 */
	dai_node = of_get_child_by_name(np, RSND_NODE_DAI);
	अगर (dai_node) अणु
		ret = dai_node;
		जाओ of_node_compatible;
	पूर्ण

	ret = np;

	dai_node = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (dai_node)
		जाओ of_node_graph;

	वापस शून्य;

of_node_graph:
	*is_graph = 1;
of_node_compatible:
	of_node_put(dai_node);

	वापस ret;
पूर्ण


#घोषणा PREALLOC_BUFFER		(32 * 1024)
#घोषणा PREALLOC_BUFFER_MAX	(32 * 1024)

अटल पूर्णांक rsnd_pपुनः_स्मृतिate_pages(काष्ठा snd_soc_pcm_runसमय *rtd,
				  काष्ठा rsnd_dai_stream *io,
				  पूर्णांक stream)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा snd_pcm_substream *substream;

	/*
	 * use Audio-DMAC dev अगर we can use IPMMU
	 * see
	 *	rsnd_dmaen_attach()
	 */
	अगर (io->dmac_dev)
		dev = io->dmac_dev;

	क्रम (substream = rtd->pcm->streams[stream].substream;
	     substream;
	     substream = substream->next) अणु
		snd_pcm_set_managed_buffer(substream,
					   SNDRV_DMA_TYPE_DEV,
					   dev,
					   PREALLOC_BUFFER, PREALLOC_BUFFER_MAX);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	पूर्णांक ret;

	ret = rsnd_dai_call(pcm_new, &rdai->playback, rtd);
	अगर (ret)
		वापस ret;

	ret = rsnd_dai_call(pcm_new, &rdai->capture, rtd);
	अगर (ret)
		वापस ret;

	ret = rsnd_pपुनः_स्मृतिate_pages(rtd, &rdai->playback,
				     SNDRV_PCM_STREAM_PLAYBACK);
	अगर (ret)
		वापस ret;

	ret = rsnd_pपुनः_स्मृतिate_pages(rtd, &rdai->capture,
				     SNDRV_PCM_STREAM_CAPTURE);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम __rsnd_dai_probe(काष्ठा rsnd_priv *priv,
			     काष्ठा device_node *dai_np,
			     पूर्णांक dai_i)
अणु
	काष्ठा rsnd_dai_stream *io_playback;
	काष्ठा rsnd_dai_stream *io_capture;
	काष्ठा snd_soc_dai_driver *drv;
	काष्ठा rsnd_dai *rdai;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक io_i;

	rdai		= rsnd_rdai_get(priv, dai_i);
	drv		= rsnd_daidrv_get(priv, dai_i);
	io_playback	= &rdai->playback;
	io_capture	= &rdai->capture;

	snम_लिखो(rdai->name, RSND_DAI_NAME_SIZE, "rsnd-dai.%d", dai_i);

	rdai->priv	= priv;
	drv->name	= rdai->name;
	drv->ops	= &rsnd_soc_dai_ops;
	drv->pcm_new	= rsnd_pcm_new;

	snम_लिखो(io_playback->name, RSND_DAI_NAME_SIZE,
		 "DAI%d Playback", dai_i);
	drv->playback.rates		= RSND_RATES;
	drv->playback.क्रमmats		= RSND_FMTS;
	drv->playback.channels_min	= 2;
	drv->playback.channels_max	= 8;
	drv->playback.stream_name	= io_playback->name;

	snम_लिखो(io_capture->name, RSND_DAI_NAME_SIZE,
		 "DAI%d Capture", dai_i);
	drv->capture.rates		= RSND_RATES;
	drv->capture.क्रमmats		= RSND_FMTS;
	drv->capture.channels_min	= 2;
	drv->capture.channels_max	= 8;
	drv->capture.stream_name	= io_capture->name;

	io_playback->rdai		= rdai;
	io_capture->rdai		= rdai;
	rsnd_rdai_channels_set(rdai, 2); /* शेष 2ch */
	rsnd_rdai_ssi_lane_set(rdai, 1); /* शेष 1lane */
	rsnd_rdai_width_set(rdai, 32);   /* शेष 32bit width */

	क्रम (io_i = 0;; io_i++) अणु
		काष्ठा device_node *playback = of_parse_phandle(dai_np, "playback", io_i);
		काष्ठा device_node *capture  = of_parse_phandle(dai_np, "capture", io_i);

		अगर (!playback && !capture)
			अवरोध;

		rsnd_parse_connect_ssi(rdai, playback, capture);
		rsnd_parse_connect_ssiu(rdai, playback, capture);
		rsnd_parse_connect_src(rdai, playback, capture);
		rsnd_parse_connect_ctu(rdai, playback, capture);
		rsnd_parse_connect_mix(rdai, playback, capture);
		rsnd_parse_connect_dvc(rdai, playback, capture);

		of_node_put(playback);
		of_node_put(capture);
	पूर्ण

	अगर (rsnd_ssi_is_pin_sharing(io_capture) ||
	    rsnd_ssi_is_pin_sharing(io_playback)) अणु
		/* should have symmetric_rate अगर pin sharing */
		drv->symmetric_rate = 1;
	पूर्ण

	dev_dbg(dev, "%s (%s/%s)\n", rdai->name,
		rsnd_io_to_mod_ssi(io_playback) ? "play"    : " -- ",
		rsnd_io_to_mod_ssi(io_capture) ? "capture" : "  --   ");
पूर्ण

अटल पूर्णांक rsnd_dai_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *dai_node;
	काष्ठा device_node *dai_np;
	काष्ठा snd_soc_dai_driver *rdrv;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_dai *rdai;
	पूर्णांक nr;
	पूर्णांक is_graph;
	पूर्णांक dai_i;

	dai_node = rsnd_dai_of_node(priv, &is_graph);
	अगर (is_graph)
		nr = of_graph_get_endpoपूर्णांक_count(dai_node);
	अन्यथा
		nr = of_get_child_count(dai_node);

	अगर (!nr)
		वापस -EINVAL;

	rdrv = devm_kसुस्मृति(dev, nr, माप(*rdrv), GFP_KERNEL);
	rdai = devm_kसुस्मृति(dev, nr, माप(*rdai), GFP_KERNEL);
	अगर (!rdrv || !rdai)
		वापस -ENOMEM;

	priv->rdai_nr	= nr;
	priv->daidrv	= rdrv;
	priv->rdai	= rdai;

	/*
	 * parse all dai
	 */
	dai_i = 0;
	अगर (is_graph) अणु
		क्रम_each_endpoपूर्णांक_of_node(dai_node, dai_np) अणु
			__rsnd_dai_probe(priv, dai_np, dai_i);
			अगर (rsnd_is_gen3(priv)) अणु
				rdai = rsnd_rdai_get(priv, dai_i);

				rsnd_parse_connect_graph(priv, &rdai->playback, dai_np);
				rsnd_parse_connect_graph(priv, &rdai->capture,  dai_np);
			पूर्ण
			dai_i++;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_child_of_node(dai_node, dai_np) अणु
			__rsnd_dai_probe(priv, dai_np, dai_i);
			अगर (rsnd_is_gen3(priv)) अणु
				rdai = rsnd_rdai_get(priv, dai_i);

				rsnd_parse_connect_simple(priv, &rdai->playback, dai_np);
				rsnd_parse_connect_simple(priv, &rdai->capture,  dai_np);
			पूर्ण
			dai_i++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *		pcm ops
 */
अटल पूर्णांक rsnd_hw_params(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_soc_dai *dai = rsnd_substream_to_dai(substream);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);

	/*
	 * rsnd assumes that it might be used under DPCM अगर user want to use
	 * channel / rate convert. Then, rsnd should be FE.
	 * And then, this function will be called *after* BE settings.
	 * this means, each BE alपढ़ोy has fixuped hw_params.
	 * see
	 *	dpcm_fe_dai_hw_params()
	 *	dpcm_be_dai_hw_params()
	 */
	io->converted_rate = 0;
	io->converted_chan = 0;
	अगर (fe->dai_link->dynamic) अणु
		काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
		काष्ठा device *dev = rsnd_priv_to_dev(priv);
		काष्ठा snd_soc_dpcm *dpcm;
		पूर्णांक stream = substream->stream;

		क्रम_each_dpcm_be(fe, stream, dpcm) अणु
			काष्ठा snd_pcm_hw_params *be_params = &dpcm->hw_params;

			अगर (params_channels(hw_params) != params_channels(be_params))
				io->converted_chan = params_channels(be_params);
			अगर (params_rate(hw_params) != params_rate(be_params))
				io->converted_rate = params_rate(be_params);
		पूर्ण
		अगर (io->converted_chan)
			dev_dbg(dev, "convert channels = %d\n", io->converted_chan);
		अगर (io->converted_rate) अणु
			/*
			 * SRC supports convert rates from params_rate(hw_params)/k_करोwn
			 * to params_rate(hw_params)*k_up, where k_up is always 6, and
			 * k_करोwn depends on number of channels and SRC unit.
			 * So all SRC units can upsample audio up to 6 बार regardless
			 * its number of channels. And all SRC units can करोwnsample
			 * 2 channel audio up to 6 बार too.
			 */
			पूर्णांक k_up = 6;
			पूर्णांक k_करोwn = 6;
			पूर्णांक channel;
			काष्ठा rsnd_mod *src_mod = rsnd_io_to_mod_src(io);

			dev_dbg(dev, "convert rate     = %d\n", io->converted_rate);

			channel = io->converted_chan ? io->converted_chan :
				  params_channels(hw_params);

			चयन (rsnd_mod_id(src_mod)) अणु
			/*
			 * SRC0 can करोwnsample 4, 6 and 8 channel audio up to 4 बार.
			 * SRC1, SRC3 and SRC4 can करोwnsample 4 channel audio
			 * up to 4 बार.
			 * SRC1, SRC3 and SRC4 can करोwnsample 6 and 8 channel audio
			 * no more than twice.
			 */
			हाल 1:
			हाल 3:
			हाल 4:
				अगर (channel > 4) अणु
					k_करोwn = 2;
					अवरोध;
				पूर्ण
				fallthrough;
			हाल 0:
				अगर (channel > 2)
					k_करोwn = 4;
				अवरोध;

			/* Other SRC units करो not support more than 2 channels */
			शेष:
				अगर (channel > 2)
					वापस -EINVAL;
			पूर्ण

			अगर (params_rate(hw_params) > io->converted_rate * k_करोwn) अणु
				hw_param_पूर्णांकerval(hw_params, SNDRV_PCM_HW_PARAM_RATE)->min =
					io->converted_rate * k_करोwn;
				hw_param_पूर्णांकerval(hw_params, SNDRV_PCM_HW_PARAM_RATE)->max =
					io->converted_rate * k_करोwn;
				hw_params->cmask |= SNDRV_PCM_HW_PARAM_RATE;
			पूर्ण अन्यथा अगर (params_rate(hw_params) * k_up < io->converted_rate) अणु
				hw_param_पूर्णांकerval(hw_params, SNDRV_PCM_HW_PARAM_RATE)->min =
					(io->converted_rate + k_up - 1) / k_up;
				hw_param_पूर्णांकerval(hw_params, SNDRV_PCM_HW_PARAM_RATE)->max =
					(io->converted_rate + k_up - 1) / k_up;
				hw_params->cmask |= SNDRV_PCM_HW_PARAM_RATE;
			पूर्ण

			/*
			 * TBD: Max SRC input and output rates also depend on number
			 * of channels and SRC unit:
			 * SRC1, SRC3 and SRC4 करो not support more than 128kHz
			 * क्रम 6 channel and 96kHz क्रम 8 channel audio.
			 * Perhaps this function should वापस EINVAL अगर the input or
			 * the output rate exceeds the limitation.
			 */
		पूर्ण
	पूर्ण

	वापस rsnd_dai_call(hw_params, io, substream, hw_params);
पूर्ण

अटल पूर्णांक rsnd_hw_मुक्त(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_dai *dai = rsnd_substream_to_dai(substream);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);

	वापस rsnd_dai_call(hw_मुक्त, io, substream);
पूर्ण

अटल snd_pcm_uframes_t rsnd_poपूर्णांकer(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_dai *dai = rsnd_substream_to_dai(substream);
	काष्ठा rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	काष्ठा rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	snd_pcm_uframes_t poपूर्णांकer = 0;

	rsnd_dai_call(poपूर्णांकer, io, &poपूर्णांकer);

	वापस poपूर्णांकer;
पूर्ण

/*
 *		snd_kcontrol
 */
अटल पूर्णांक rsnd_kctrl_info(काष्ठा snd_kcontrol *kctrl,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा rsnd_kctrl_cfg *cfg = snd_kcontrol_chip(kctrl);

	अगर (cfg->texts) अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
		uinfo->count = cfg->size;
		uinfo->value.क्रमागतerated.items = cfg->max;
		अगर (uinfo->value.क्रमागतerated.item >= cfg->max)
			uinfo->value.क्रमागतerated.item = cfg->max - 1;
		strscpy(uinfo->value.क्रमागतerated.name,
			cfg->texts[uinfo->value.क्रमागतerated.item],
			माप(uinfo->value.क्रमागतerated.name));
	पूर्ण अन्यथा अणु
		uinfo->count = cfg->size;
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = cfg->max;
		uinfo->type = (cfg->max == 1) ?
			SNDRV_CTL_ELEM_TYPE_BOOLEAN :
			SNDRV_CTL_ELEM_TYPE_INTEGER;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_kctrl_get(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा rsnd_kctrl_cfg *cfg = snd_kcontrol_chip(kctrl);
	पूर्णांक i;

	क्रम (i = 0; i < cfg->size; i++)
		अगर (cfg->texts)
			uc->value.क्रमागतerated.item[i] = cfg->val[i];
		अन्यथा
			uc->value.पूर्णांकeger.value[i] = cfg->val[i];

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_kctrl_put(काष्ठा snd_kcontrol *kctrl,
			  काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा rsnd_kctrl_cfg *cfg = snd_kcontrol_chip(kctrl);
	पूर्णांक i, change = 0;

	अगर (!cfg->accept(cfg->io))
		वापस 0;

	क्रम (i = 0; i < cfg->size; i++) अणु
		अगर (cfg->texts) अणु
			change |= (uc->value.क्रमागतerated.item[i] != cfg->val[i]);
			cfg->val[i] = uc->value.क्रमागतerated.item[i];
		पूर्ण अन्यथा अणु
			change |= (uc->value.पूर्णांकeger.value[i] != cfg->val[i]);
			cfg->val[i] = uc->value.पूर्णांकeger.value[i];
		पूर्ण
	पूर्ण

	अगर (change && cfg->update)
		cfg->update(cfg->io, cfg->mod);

	वापस change;
पूर्ण

पूर्णांक rsnd_kctrl_accept_anyसमय(काष्ठा rsnd_dai_stream *io)
अणु
	वापस 1;
पूर्ण

पूर्णांक rsnd_kctrl_accept_runसमय(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	अगर (!runसमय) अणु
		dev_warn(dev, "Can't update kctrl when idle\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

काष्ठा rsnd_kctrl_cfg *rsnd_kctrl_init_m(काष्ठा rsnd_kctrl_cfg_m *cfg)
अणु
	cfg->cfg.val = cfg->val;

	वापस &cfg->cfg;
पूर्ण

काष्ठा rsnd_kctrl_cfg *rsnd_kctrl_init_s(काष्ठा rsnd_kctrl_cfg_s *cfg)
अणु
	cfg->cfg.val = &cfg->val;

	वापस &cfg->cfg;
पूर्ण

स्थिर अक्षर * स्थिर volume_ramp_rate[] = अणु
	"128 dB/1 step",	 /* 00000 */
	"64 dB/1 step",		 /* 00001 */
	"32 dB/1 step",		 /* 00010 */
	"16 dB/1 step",		 /* 00011 */
	"8 dB/1 step",		 /* 00100 */
	"4 dB/1 step",		 /* 00101 */
	"2 dB/1 step",		 /* 00110 */
	"1 dB/1 step",		 /* 00111 */
	"0.5 dB/1 step",	 /* 01000 */
	"0.25 dB/1 step",	 /* 01001 */
	"0.125 dB/1 step",	 /* 01010 = VOLUME_RAMP_MAX_MIX */
	"0.125 dB/2 steps",	 /* 01011 */
	"0.125 dB/4 steps",	 /* 01100 */
	"0.125 dB/8 steps",	 /* 01101 */
	"0.125 dB/16 steps",	 /* 01110 */
	"0.125 dB/32 steps",	 /* 01111 */
	"0.125 dB/64 steps",	 /* 10000 */
	"0.125 dB/128 steps",	 /* 10001 */
	"0.125 dB/256 steps",	 /* 10010 */
	"0.125 dB/512 steps",	 /* 10011 */
	"0.125 dB/1024 steps",	 /* 10100 */
	"0.125 dB/2048 steps",	 /* 10101 */
	"0.125 dB/4096 steps",	 /* 10110 */
	"0.125 dB/8192 steps",	 /* 10111 = VOLUME_RAMP_MAX_DVC */
पूर्ण;

पूर्णांक rsnd_kctrl_new(काष्ठा rsnd_mod *mod,
		   काष्ठा rsnd_dai_stream *io,
		   काष्ठा snd_soc_pcm_runसमय *rtd,
		   स्थिर अचिन्हित अक्षर *name,
		   पूर्णांक (*accept)(काष्ठा rsnd_dai_stream *io),
		   व्योम (*update)(काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_mod *mod),
		   काष्ठा rsnd_kctrl_cfg *cfg,
		   स्थिर अक्षर * स्थिर *texts,
		   पूर्णांक size,
		   u32 max)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_kcontrol *kctrl;
	काष्ठा snd_kcontrol_new knew = अणु
		.अगरace		= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name		= name,
		.info		= rsnd_kctrl_info,
		.index		= rtd->num,
		.get		= rsnd_kctrl_get,
		.put		= rsnd_kctrl_put,
	पूर्ण;
	पूर्णांक ret;

	/*
	 * 1) Aव्योम duplicate रेजिस्टर क्रम DVC with MIX हाल
	 * 2) Allow duplicate रेजिस्टर क्रम MIX
	 * 3) re-रेजिस्टर अगर card was rebinded
	 */
	list_क्रम_each_entry(kctrl, &card->controls, list) अणु
		काष्ठा rsnd_kctrl_cfg *c = kctrl->निजी_data;

		अगर (c == cfg)
			वापस 0;
	पूर्ण

	अगर (size > RSND_MAX_CHANNELS)
		वापस -EINVAL;

	kctrl = snd_ctl_new1(&knew, cfg);
	अगर (!kctrl)
		वापस -ENOMEM;

	ret = snd_ctl_add(card, kctrl);
	अगर (ret < 0)
		वापस ret;

	cfg->texts	= texts;
	cfg->max	= max;
	cfg->size	= size;
	cfg->accept	= accept;
	cfg->update	= update;
	cfg->card	= card;
	cfg->kctrl	= kctrl;
	cfg->io		= io;
	cfg->mod	= mod;

	वापस 0;
पूर्ण

/*
 *		snd_soc_component
 */
अटल स्थिर काष्ठा snd_soc_component_driver rsnd_soc_component = अणु
	.name		= "rsnd",
	.hw_params	= rsnd_hw_params,
	.hw_मुक्त	= rsnd_hw_मुक्त,
	.poपूर्णांकer	= rsnd_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक rsnd_rdai_continuance_probe(काष्ठा rsnd_priv *priv,
				       काष्ठा rsnd_dai_stream *io)
अणु
	पूर्णांक ret;

	ret = rsnd_dai_call(probe, io, priv);
	अगर (ret == -EAGAIN) अणु
		काष्ठा rsnd_mod *ssi_mod = rsnd_io_to_mod_ssi(io);
		काष्ठा rsnd_mod *mod;
		पूर्णांक i;

		/*
		 * Fallback to PIO mode
		 */

		/*
		 * call "remove" क्रम SSI/SRC/DVC
		 * SSI will be चयन to PIO mode अगर it was DMA mode
		 * see
		 *	rsnd_dma_init()
		 *	rsnd_ssi_fallback()
		 */
		rsnd_dai_call(हटाओ, io, priv);

		/*
		 * हटाओ all mod from io
		 * and, re connect ssi
		 */
		क्रम_each_rsnd_mod(i, mod, io)
			rsnd_dai_disconnect(mod, io, i);
		rsnd_dai_connect(ssi_mod, io, RSND_MOD_SSI);

		/*
		 * fallback
		 */
		rsnd_dai_call(fallback, io, priv);

		/*
		 * retry to "probe".
		 * DAI has SSI which is PIO mode only now.
		 */
		ret = rsnd_dai_call(probe, io, priv);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *	rsnd probe
 */
अटल पूर्णांक rsnd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rsnd_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rsnd_dai *rdai;
	पूर्णांक (*probe_func[])(काष्ठा rsnd_priv *priv) = अणु
		rsnd_gen_probe,
		rsnd_dma_probe,
		rsnd_ssi_probe,
		rsnd_ssiu_probe,
		rsnd_src_probe,
		rsnd_ctu_probe,
		rsnd_mix_probe,
		rsnd_dvc_probe,
		rsnd_cmd_probe,
		rsnd_adg_probe,
		rsnd_dai_probe,
	पूर्ण;
	पूर्णांक ret, i;

	/*
	 *	init priv data
	 */
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENODEV;

	priv->pdev	= pdev;
	priv->flags	= (अचिन्हित दीर्घ)of_device_get_match_data(dev);
	spin_lock_init(&priv->lock);

	/*
	 *	init each module
	 */
	क्रम (i = 0; i < ARRAY_SIZE(probe_func); i++) अणु
		ret = probe_func[i](priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_rsnd_dai(rdai, priv, i) अणु
		ret = rsnd_rdai_continuance_probe(priv, &rdai->playback);
		अगर (ret)
			जाओ निकास_snd_probe;

		ret = rsnd_rdai_continuance_probe(priv, &rdai->capture);
		अगर (ret)
			जाओ निकास_snd_probe;
	पूर्ण

	dev_set_drvdata(dev, priv);

	/*
	 *	asoc रेजिस्टर
	 */
	ret = devm_snd_soc_रेजिस्टर_component(dev, &rsnd_soc_component,
					 priv->daidrv, rsnd_rdai_nr(priv));
	अगर (ret < 0) अणु
		dev_err(dev, "cannot snd dai register\n");
		जाओ निकास_snd_probe;
	पूर्ण

	pm_runसमय_enable(dev);

	dev_info(dev, "probed\n");
	वापस ret;

निकास_snd_probe:
	क्रम_each_rsnd_dai(rdai, priv, i) अणु
		rsnd_dai_call(हटाओ, &rdai->playback, priv);
		rsnd_dai_call(हटाओ, &rdai->capture, priv);
	पूर्ण

	/*
	 * adg is very special mod which can't use rsnd_dai_call(हटाओ),
	 * and it रेजिस्टरs ADG घड़ी on probe.
	 * It should be unरेजिस्टर अगर probe failed.
	 * Mainly it is assuming -EPROBE_DEFER हाल
	 */
	rsnd_adg_हटाओ(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rsnd_priv *priv = dev_get_drvdata(&pdev->dev);
	काष्ठा rsnd_dai *rdai;
	व्योम (*हटाओ_func[])(काष्ठा rsnd_priv *priv) = अणु
		rsnd_ssi_हटाओ,
		rsnd_ssiu_हटाओ,
		rsnd_src_हटाओ,
		rsnd_ctu_हटाओ,
		rsnd_mix_हटाओ,
		rsnd_dvc_हटाओ,
		rsnd_cmd_हटाओ,
		rsnd_adg_हटाओ,
	पूर्ण;
	पूर्णांक ret = 0, i;

	pm_runसमय_disable(&pdev->dev);

	क्रम_each_rsnd_dai(rdai, priv, i) अणु
		ret |= rsnd_dai_call(हटाओ, &rdai->playback, priv);
		ret |= rsnd_dai_call(हटाओ, &rdai->capture, priv);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(हटाओ_func); i++)
		हटाओ_func[i](priv);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rsnd_suspend(काष्ठा device *dev)
अणु
	काष्ठा rsnd_priv *priv = dev_get_drvdata(dev);

	rsnd_adg_clk_disable(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rsnd_resume(काष्ठा device *dev)
अणु
	काष्ठा rsnd_priv *priv = dev_get_drvdata(dev);

	rsnd_adg_clk_enable(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rsnd_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rsnd_suspend, rsnd_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver rsnd_driver = अणु
	.driver	= अणु
		.name	= "rcar_sound",
		.pm	= &rsnd_pm_ops,
		.of_match_table = rsnd_of_match,
	पूर्ण,
	.probe		= rsnd_probe,
	.हटाओ		= rsnd_हटाओ,
पूर्ण;
module_platक्रमm_driver(rsnd_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car audio driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_ALIAS("platform:rcar-pcm-audio");
