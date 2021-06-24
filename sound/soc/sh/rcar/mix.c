<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mix.c
//
// Copyright (c) 2015 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

/*
 *		    CTUn	MIXn
 *		    +------+	+------+
 * [SRC3 / SRC6] -> |CTU n0| ->	[MIX n0| ->
 * [SRC4 / SRC9] -> |CTU n1| ->	[MIX n1| ->
 * [SRC0 / SRC1] -> |CTU n2| ->	[MIX n2| ->
 * [SRC2 / SRC5] -> |CTU n3| ->	[MIX n3| ->
 *		    +------+	+------+
 *
 * ex)
 *	DAI0 : playback = <&src0 &ctu02 &mix0 &dvc0 &ssi0>;
 *	DAI1 : playback = <&src2 &ctu03 &mix0 &dvc0 &ssi0>;
 *
 * MIX Volume
 *	amixer set "MIX",0  100%  // DAI0 Volume
 *	amixer set "MIX",1  100%  // DAI1 Volume
 *
 * Volume Ramp
 *	amixer set "MIX Ramp Up Rate"   "0.125 dB/1 step"
 *	amixer set "MIX Ramp Down Rate" "4 dB/1 step"
 *	amixer set "MIX Ramp" on
 *	aplay xxx.wav &
 *	amixer set "MIX",0  80%  // DAI0 Volume Down
 *	amixer set "MIX",1 100%  // DAI1 Volume Up
 */

#समावेश "rsnd.h"

#घोषणा MIX_NAME_SIZE	16
#घोषणा MIX_NAME "mix"

काष्ठा rsnd_mix अणु
	काष्ठा rsnd_mod mod;
	काष्ठा rsnd_kctrl_cfg_s volumeA; /* MDBAR */
	काष्ठा rsnd_kctrl_cfg_s volumeB; /* MDBBR */
	काष्ठा rsnd_kctrl_cfg_s volumeC; /* MDBCR */
	काष्ठा rsnd_kctrl_cfg_s volumeD; /* MDBDR */
	काष्ठा rsnd_kctrl_cfg_s ren;	/* Ramp Enable */
	काष्ठा rsnd_kctrl_cfg_s rup;	/* Ramp Rate Up */
	काष्ठा rsnd_kctrl_cfg_s rdw;	/* Ramp Rate Down */
	u32 flags;
पूर्ण;

#घोषणा ONCE_KCTRL_INITIALIZED		(1 << 0)
#घोषणा HAS_VOLA			(1 << 1)
#घोषणा HAS_VOLB			(1 << 2)
#घोषणा HAS_VOLC			(1 << 3)
#घोषणा HAS_VOLD			(1 << 4)

#घोषणा VOL_MAX				0x3ff

#घोषणा rsnd_mod_to_mix(_mod)	\
	container_of((_mod), काष्ठा rsnd_mix, mod)

#घोषणा rsnd_mix_get(priv, id) ((काष्ठा rsnd_mix *)(priv->mix) + id)
#घोषणा rsnd_mix_nr(priv) ((priv)->mix_nr)
#घोषणा क्रम_each_rsnd_mix(pos, priv, i)					\
	क्रम ((i) = 0;							\
	     ((i) < rsnd_mix_nr(priv)) &&				\
		     ((pos) = (काष्ठा rsnd_mix *)(priv)->mix + i);	\
	     i++)

अटल व्योम rsnd_mix_activation(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, MIX_SWRSR, 0);
	rsnd_mod_ग_लिखो(mod, MIX_SWRSR, 1);
पूर्ण

अटल व्योम rsnd_mix_halt(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, MIX_MIXIR, 1);
	rsnd_mod_ग_लिखो(mod, MIX_SWRSR, 0);
पूर्ण

#घोषणा rsnd_mix_get_vol(mix, X) \
	rsnd_flags_has(mix, HAS_VOL##X) ? \
		(VOL_MAX - rsnd_kctrl_vals(mix->volume##X)) : 0
अटल व्योम rsnd_mix_volume_parameter(काष्ठा rsnd_dai_stream *io,
				      काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_mix *mix = rsnd_mod_to_mix(mod);
	u32 volA = rsnd_mix_get_vol(mix, A);
	u32 volB = rsnd_mix_get_vol(mix, B);
	u32 volC = rsnd_mix_get_vol(mix, C);
	u32 volD = rsnd_mix_get_vol(mix, D);

	dev_dbg(dev, "MIX A/B/C/D = %02x/%02x/%02x/%02x\n",
		volA, volB, volC, volD);

	rsnd_mod_ग_लिखो(mod, MIX_MDBAR, volA);
	rsnd_mod_ग_लिखो(mod, MIX_MDBBR, volB);
	rsnd_mod_ग_लिखो(mod, MIX_MDBCR, volC);
	rsnd_mod_ग_लिखो(mod, MIX_MDBDR, volD);
पूर्ण

अटल व्योम rsnd_mix_volume_init(काष्ठा rsnd_dai_stream *io,
				 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_mix *mix = rsnd_mod_to_mix(mod);

	rsnd_mod_ग_लिखो(mod, MIX_MIXIR, 1);

	/* General Inक्रमmation */
	rsnd_mod_ग_लिखो(mod, MIX_ADINR, rsnd_runसमय_channel_after_ctu(io));

	/* volume step */
	rsnd_mod_ग_लिखो(mod, MIX_MIXMR, rsnd_kctrl_vals(mix->ren));
	rsnd_mod_ग_लिखो(mod, MIX_MVPDR, rsnd_kctrl_vals(mix->rup) << 8 |
				       rsnd_kctrl_vals(mix->rdw));

	/* common volume parameter */
	rsnd_mix_volume_parameter(io, mod);

	rsnd_mod_ग_लिखो(mod, MIX_MIXIR, 0);
पूर्ण

अटल व्योम rsnd_mix_volume_update(काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_mod *mod)
अणु
	/* Disable MIX dB setting */
	rsnd_mod_ग_लिखो(mod, MIX_MDBER, 0);

	/* common volume parameter */
	rsnd_mix_volume_parameter(io, mod);

	/* Enable MIX dB setting */
	rsnd_mod_ग_लिखो(mod, MIX_MDBER, 1);
पूर्ण

अटल पूर्णांक rsnd_mix_probe_(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	वापस rsnd_cmd_attach(io, rsnd_mod_id(mod));
पूर्ण

अटल पूर्णांक rsnd_mix_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_घातer_on(mod);

	rsnd_mix_activation(mod);

	rsnd_mix_volume_init(io, mod);

	rsnd_mix_volume_update(io, mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_mix_quit(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mix_halt(mod);

	rsnd_mod_घातer_off(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_mix_pcm_new(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_mix *mix = rsnd_mod_to_mix(mod);
	काष्ठा rsnd_mod *src_mod = rsnd_io_to_mod_src(io);
	काष्ठा rsnd_kctrl_cfg_s *volume;
	पूर्णांक ret;

	चयन (rsnd_mod_id(src_mod)) अणु
	हाल 3:
	हाल 6:	/* MDBAR */
		volume = &mix->volumeA;
		rsnd_flags_set(mix, HAS_VOLA);
		अवरोध;
	हाल 4:
	हाल 9:	/* MDBBR */
		volume = &mix->volumeB;
		rsnd_flags_set(mix, HAS_VOLB);
		अवरोध;
	हाल 0:
	हाल 1:	/* MDBCR */
		volume = &mix->volumeC;
		rsnd_flags_set(mix, HAS_VOLC);
		अवरोध;
	हाल 2:
	हाल 5:	/* MDBDR */
		volume = &mix->volumeD;
		rsnd_flags_set(mix, HAS_VOLD);
		अवरोध;
	शेष:
		dev_err(dev, "unknown SRC is connected\n");
		वापस -EINVAL;
	पूर्ण

	/* Volume */
	ret = rsnd_kctrl_new_s(mod, io, rtd,
			       "MIX Playback Volume",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_mix_volume_update,
			       volume, VOL_MAX);
	अगर (ret < 0)
		वापस ret;
	rsnd_kctrl_vals(*volume) = VOL_MAX;

	अगर (rsnd_flags_has(mix, ONCE_KCTRL_INITIALIZED))
		वापस ret;

	/* Ramp */
	ret = rsnd_kctrl_new_s(mod, io, rtd,
			       "MIX Ramp Switch",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_mix_volume_update,
			       &mix->ren, 1);
	अगर (ret < 0)
		वापस ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			       "MIX Ramp Up Rate",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_mix_volume_update,
			       &mix->rup,
			       volume_ramp_rate,
			       VOLUME_RAMP_MAX_MIX);
	अगर (ret < 0)
		वापस ret;

	ret = rsnd_kctrl_new_e(mod, io, rtd,
			       "MIX Ramp Down Rate",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_mix_volume_update,
			       &mix->rdw,
			       volume_ramp_rate,
			       VOLUME_RAMP_MAX_MIX);

	rsnd_flags_set(mix, ONCE_KCTRL_INITIALIZED);

	वापस ret;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_mix_ops = अणु
	.name		= MIX_NAME,
	.probe		= rsnd_mix_probe_,
	.init		= rsnd_mix_init,
	.quit		= rsnd_mix_quit,
	.pcm_new	= rsnd_mix_pcm_new,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

काष्ठा rsnd_mod *rsnd_mix_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_mix_nr(priv)))
		id = 0;

	वापस rsnd_mod_get(rsnd_mix_get(priv, id));
पूर्ण

पूर्णांक rsnd_mix_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_mix *mix;
	काष्ठा clk *clk;
	अक्षर name[MIX_NAME_SIZE];
	पूर्णांक i, nr, ret;

	/* This driver करोesn't support Gen1 at this poपूर्णांक */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	node = rsnd_mix_of_node(priv);
	अगर (!node)
		वापस 0; /* not used is not error */

	nr = of_get_child_count(node);
	अगर (!nr) अणु
		ret = -EINVAL;
		जाओ rsnd_mix_probe_करोne;
	पूर्ण

	mix	= devm_kसुस्मृति(dev, nr, माप(*mix), GFP_KERNEL);
	अगर (!mix) अणु
		ret = -ENOMEM;
		जाओ rsnd_mix_probe_करोne;
	पूर्ण

	priv->mix_nr	= nr;
	priv->mix	= mix;

	i = 0;
	ret = 0;
	क्रम_each_child_of_node(node, np) अणु
		mix = rsnd_mix_get(priv, i);

		snम_लिखो(name, MIX_NAME_SIZE, "%s.%d",
			 MIX_NAME, i);

		clk = devm_clk_get(dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			of_node_put(np);
			जाओ rsnd_mix_probe_करोne;
		पूर्ण

		ret = rsnd_mod_init(priv, rsnd_mod_get(mix), &rsnd_mix_ops,
				    clk, RSND_MOD_MIX, i);
		अगर (ret) अणु
			of_node_put(np);
			जाओ rsnd_mix_probe_करोne;
		पूर्ण

		i++;
	पूर्ण

rsnd_mix_probe_करोne:
	of_node_put(node);

	वापस ret;
पूर्ण

व्योम rsnd_mix_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_mix *mix;
	पूर्णांक i;

	क्रम_each_rsnd_mix(mix, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(mix));
	पूर्ण
पूर्ण
