<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car DVC support
//
// Copyright (C) 2014 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

/*
 * Playback Volume
 *	amixer set "DVC Out" 100%
 *
 * Capture Volume
 *	amixer set "DVC In" 100%
 *
 * Playback Mute
 *	amixer set "DVC Out Mute" on
 *
 * Capture Mute
 *	amixer set "DVC In Mute" on
 *
 * Volume Ramp
 *	amixer set "DVC Out Ramp Up Rate"   "0.125 dB/64 steps"
 *	amixer set "DVC Out Ramp Down Rate" "0.125 dB/512 steps"
 *	amixer set "DVC Out Ramp" on
 *	aplay xxx.wav &
 *	amixer set "DVC Out"  80%  // Volume Down
 *	amixer set "DVC Out" 100%  // Volume Up
 */

#समावेश "rsnd.h"

#घोषणा RSND_DVC_NAME_SIZE	16

#घोषणा DVC_NAME "dvc"

काष्ठा rsnd_dvc अणु
	काष्ठा rsnd_mod mod;
	काष्ठा rsnd_kctrl_cfg_m volume;
	काष्ठा rsnd_kctrl_cfg_m mute;
	काष्ठा rsnd_kctrl_cfg_s ren;	/* Ramp Enable */
	काष्ठा rsnd_kctrl_cfg_s rup;	/* Ramp Rate Up */
	काष्ठा rsnd_kctrl_cfg_s rकरोwn;	/* Ramp Rate Down */
पूर्ण;

#घोषणा rsnd_dvc_get(priv, id) ((काष्ठा rsnd_dvc *)(priv->dvc) + id)
#घोषणा rsnd_dvc_nr(priv) ((priv)->dvc_nr)

#घोषणा rsnd_mod_to_dvc(_mod)	\
	container_of((_mod), काष्ठा rsnd_dvc, mod)

#घोषणा क्रम_each_rsnd_dvc(pos, priv, i)				\
	क्रम ((i) = 0;						\
	     ((i) < rsnd_dvc_nr(priv)) &&			\
	     ((pos) = (काष्ठा rsnd_dvc *)(priv)->dvc + i);	\
	     i++)

अटल व्योम rsnd_dvc_activation(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, DVC_SWRSR, 0);
	rsnd_mod_ग_लिखो(mod, DVC_SWRSR, 1);
पूर्ण

अटल व्योम rsnd_dvc_halt(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, DVC_DVUIR, 1);
	rsnd_mod_ग_लिखो(mod, DVC_SWRSR, 0);
पूर्ण

#घोषणा rsnd_dvc_get_vrpdr(dvc) (rsnd_kctrl_vals(dvc->rup) << 8 | \
				 rsnd_kctrl_vals(dvc->rकरोwn))
#घोषणा rsnd_dvc_get_vrdbr(dvc) (0x3ff - (rsnd_kctrl_valm(dvc->volume, 0) >> 13))

अटल व्योम rsnd_dvc_volume_parameter(काष्ठा rsnd_dai_stream *io,
					      काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 val[RSND_MAX_CHANNELS];
	पूर्णांक i;

	/* Enable Ramp */
	अगर (rsnd_kctrl_vals(dvc->ren))
		क्रम (i = 0; i < RSND_MAX_CHANNELS; i++)
			val[i] = rsnd_kctrl_max(dvc->volume);
	अन्यथा
		क्रम (i = 0; i < RSND_MAX_CHANNELS; i++)
			val[i] = rsnd_kctrl_valm(dvc->volume, i);

	/* Enable Digital Volume */
	क्रम (i = 0; i < RSND_MAX_CHANNELS; i++)
		rsnd_mod_ग_लिखो(mod, DVC_VOLxR(i), val[i]);
पूर्ण

अटल व्योम rsnd_dvc_volume_init(काष्ठा rsnd_dai_stream *io,
				 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 adinr = 0;
	u32 dvucr = 0;
	u32 vrctr = 0;
	u32 vrpdr = 0;
	u32 vrdbr = 0;

	adinr = rsnd_get_adinr_bit(mod, io) |
		rsnd_runसमय_channel_after_ctu(io);

	/* Enable Digital Volume, Zero Cross Mute Mode */
	dvucr |= 0x101;

	/* Enable Ramp */
	अगर (rsnd_kctrl_vals(dvc->ren)) अणु
		dvucr |= 0x10;

		/*
		 * FIXME !!
		 * use scale-करोwned Digital Volume
		 * as Volume Ramp
		 * 7F FFFF -> 3FF
		 */
		vrctr = 0xff;
		vrpdr = rsnd_dvc_get_vrpdr(dvc);
		vrdbr = rsnd_dvc_get_vrdbr(dvc);
	पूर्ण

	/* Initialize operation */
	rsnd_mod_ग_लिखो(mod, DVC_DVUIR, 1);

	/* General Inक्रमmation */
	rsnd_mod_ग_लिखो(mod, DVC_ADINR, adinr);
	rsnd_mod_ग_लिखो(mod, DVC_DVUCR, dvucr);

	/* Volume Ramp Parameter */
	rsnd_mod_ग_लिखो(mod, DVC_VRCTR, vrctr);
	rsnd_mod_ग_लिखो(mod, DVC_VRPDR, vrpdr);
	rsnd_mod_ग_लिखो(mod, DVC_VRDBR, vrdbr);

	/* Digital Volume Function Parameter */
	rsnd_dvc_volume_parameter(io, mod);

	/* cancel operation */
	rsnd_mod_ग_लिखो(mod, DVC_DVUIR, 0);
पूर्ण

अटल व्योम rsnd_dvc_volume_update(काष्ठा rsnd_dai_stream *io,
				   काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 zcmcr = 0;
	u32 vrpdr = 0;
	u32 vrdbr = 0;
	पूर्णांक i;

	क्रम (i = 0; i < rsnd_kctrl_size(dvc->mute); i++)
		zcmcr |= (!!rsnd_kctrl_valm(dvc->mute, i)) << i;

	अगर (rsnd_kctrl_vals(dvc->ren)) अणु
		vrpdr = rsnd_dvc_get_vrpdr(dvc);
		vrdbr = rsnd_dvc_get_vrdbr(dvc);
	पूर्ण

	/* Disable DVC Register access */
	rsnd_mod_ग_लिखो(mod, DVC_DVUER, 0);

	/* Zero Cross Mute Function */
	rsnd_mod_ग_लिखो(mod, DVC_ZCMCR, zcmcr);

	/* Volume Ramp Function */
	rsnd_mod_ग_लिखो(mod, DVC_VRPDR, vrpdr);
	rsnd_mod_ग_लिखो(mod, DVC_VRDBR, vrdbr);
	/* add DVC_VRWTR here */

	/* Digital Volume Function Parameter */
	rsnd_dvc_volume_parameter(io, mod);

	/* Enable DVC Register access */
	rsnd_mod_ग_लिखो(mod, DVC_DVUER, 1);
पूर्ण

अटल पूर्णांक rsnd_dvc_probe_(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	वापस rsnd_cmd_attach(io, rsnd_mod_id(mod));
पूर्ण

अटल पूर्णांक rsnd_dvc_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_घातer_on(mod);

	rsnd_dvc_activation(mod);

	rsnd_dvc_volume_init(io, mod);

	rsnd_dvc_volume_update(io, mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dvc_quit(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_dvc_halt(mod);

	rsnd_mod_घातer_off(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_dvc_pcm_new(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	पूर्णांक is_play = rsnd_io_is_play(io);
	पूर्णांक channels = rsnd_rdai_channels_get(rdai);
	पूर्णांक ret;

	/* Volume */
	ret = rsnd_kctrl_new_m(mod, io, rtd,
			is_play ?
			"DVC Out Playback Volume" : "DVC In Capture Volume",
			rsnd_kctrl_accept_anyसमय,
			rsnd_dvc_volume_update,
			&dvc->volume, channels,
			0x00800000 - 1);
	अगर (ret < 0)
		वापस ret;

	/* Mute */
	ret = rsnd_kctrl_new_m(mod, io, rtd,
			is_play ?
			"DVC Out Mute Switch" : "DVC In Mute Switch",
			rsnd_kctrl_accept_anyसमय,
			rsnd_dvc_volume_update,
			&dvc->mute, channels,
			1);
	अगर (ret < 0)
		वापस ret;

	/* Ramp */
	ret = rsnd_kctrl_new_s(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Switch" : "DVC In Ramp Switch",
			rsnd_kctrl_accept_anyसमय,
			rsnd_dvc_volume_update,
			&dvc->ren, 1);
	अगर (ret < 0)
		वापस ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Up Rate" : "DVC In Ramp Up Rate",
			rsnd_kctrl_accept_anyसमय,
			rsnd_dvc_volume_update,
			&dvc->rup,
			volume_ramp_rate,
			VOLUME_RAMP_MAX_DVC);
	अगर (ret < 0)
		वापस ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			is_play ?
			"DVC Out Ramp Down Rate" : "DVC In Ramp Down Rate",
			rsnd_kctrl_accept_anyसमय,
			rsnd_dvc_volume_update,
			&dvc->rकरोwn,
			volume_ramp_rate,
			VOLUME_RAMP_MAX_DVC);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा dma_chan *rsnd_dvc_dma_req(काष्ठा rsnd_dai_stream *io,
					 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);

	वापस rsnd_dma_request_channel(rsnd_dvc_of_node(priv),
					mod, "tx");
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_dvc_ops = अणु
	.name		= DVC_NAME,
	.dma_req	= rsnd_dvc_dma_req,
	.probe		= rsnd_dvc_probe_,
	.init		= rsnd_dvc_init,
	.quit		= rsnd_dvc_quit,
	.pcm_new	= rsnd_dvc_pcm_new,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

काष्ठा rsnd_mod *rsnd_dvc_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_dvc_nr(priv)))
		id = 0;

	वापस rsnd_mod_get(rsnd_dvc_get(priv, id));
पूर्ण

पूर्णांक rsnd_dvc_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_dvc *dvc;
	काष्ठा clk *clk;
	अक्षर name[RSND_DVC_NAME_SIZE];
	पूर्णांक i, nr, ret;

	/* This driver करोesn't support Gen1 at this poपूर्णांक */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	node = rsnd_dvc_of_node(priv);
	अगर (!node)
		वापस 0; /* not used is not error */

	nr = of_get_child_count(node);
	अगर (!nr) अणु
		ret = -EINVAL;
		जाओ rsnd_dvc_probe_करोne;
	पूर्ण

	dvc	= devm_kसुस्मृति(dev, nr, माप(*dvc), GFP_KERNEL);
	अगर (!dvc) अणु
		ret = -ENOMEM;
		जाओ rsnd_dvc_probe_करोne;
	पूर्ण

	priv->dvc_nr	= nr;
	priv->dvc	= dvc;

	i = 0;
	ret = 0;
	क्रम_each_child_of_node(node, np) अणु
		dvc = rsnd_dvc_get(priv, i);

		snम_लिखो(name, RSND_DVC_NAME_SIZE, "%s.%d",
			 DVC_NAME, i);

		clk = devm_clk_get(dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			of_node_put(np);
			जाओ rsnd_dvc_probe_करोne;
		पूर्ण

		ret = rsnd_mod_init(priv, rsnd_mod_get(dvc), &rsnd_dvc_ops,
				    clk, RSND_MOD_DVC, i);
		अगर (ret) अणु
			of_node_put(np);
			जाओ rsnd_dvc_probe_करोne;
		पूर्ण

		i++;
	पूर्ण

rsnd_dvc_probe_करोne:
	of_node_put(node);

	वापस ret;
पूर्ण

व्योम rsnd_dvc_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dvc *dvc;
	पूर्णांक i;

	क्रम_each_rsnd_dvc(dvc, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(dvc));
	पूर्ण
पूर्ण
