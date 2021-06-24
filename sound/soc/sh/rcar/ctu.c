<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ctu.c
//
// Copyright (c) 2015 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश "rsnd.h"

#घोषणा CTU_NAME_SIZE	16
#घोषणा CTU_NAME "ctu"

/*
 * User needs to setup CTU by amixer, and its settings are
 * based on below रेजिस्टरs
 *
 * CTUn_CPMDR : amixser set "CTU Pass"
 * CTUn_SV0xR : amixser set "CTU SV0"
 * CTUn_SV1xR : amixser set "CTU SV1"
 * CTUn_SV2xR : amixser set "CTU SV2"
 * CTUn_SV3xR : amixser set "CTU SV3"
 *
 * [CTU Pass]
 * 0000: शेष
 * 0001: Connect input data of channel 0
 * 0010: Connect input data of channel 1
 * 0011: Connect input data of channel 2
 * 0100: Connect input data of channel 3
 * 0101: Connect input data of channel 4
 * 0110: Connect input data of channel 5
 * 0111: Connect input data of channel 6
 * 1000: Connect input data of channel 7
 * 1001: Connect calculated data by scale values of matrix row 0
 * 1010: Connect calculated data by scale values of matrix row 1
 * 1011: Connect calculated data by scale values of matrix row 2
 * 1100: Connect calculated data by scale values of matrix row 3
 *
 * [CTU SVx]
 * [Output0] = [SV00, SV01, SV02, SV03, SV04, SV05, SV06, SV07]
 * [Output1] = [SV10, SV11, SV12, SV13, SV14, SV15, SV16, SV17]
 * [Output2] = [SV20, SV21, SV22, SV23, SV24, SV25, SV26, SV27]
 * [Output3] = [SV30, SV31, SV32, SV33, SV34, SV35, SV36, SV37]
 * [Output4] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output5] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output6] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 * [Output7] = [ 0,   0,    0,    0,    0,    0,    0,    0   ]
 *
 * [SVxx]
 * Plus					Minus
 * value	समय		dB	value		समय		dB
 * -----------------------------------------------------------------------
 * H'7F_FFFF	2		6	H'80_0000	2		6
 * ...
 * H'40_0000	1		0	H'C0_0000	1		0
 * ...
 * H'00_0001	2.38 x 10^-7	-132
 * H'00_0000	0		Mute	H'FF_FFFF	2.38 x 10^-7	-132
 *
 *
 * Ex) Input ch -> Output ch
 *	1ch     ->  0ch
 *	0ch     ->  1ch
 *
 *	amixer set "CTU Reset" on
 *	amixer set "CTU Pass" 9,10
 *	amixer set "CTU SV0" 0,4194304
 *	amixer set "CTU SV1" 4194304,0
 * or
 *	amixer set "CTU Reset" on
 *	amixer set "CTU Pass" 2,1
 */

काष्ठा rsnd_ctu अणु
	काष्ठा rsnd_mod mod;
	काष्ठा rsnd_kctrl_cfg_m pass;
	काष्ठा rsnd_kctrl_cfg_m sv[4];
	काष्ठा rsnd_kctrl_cfg_s reset;
	पूर्णांक channels;
	u32 flags;
पूर्ण;

#घोषणा KCTRL_INITIALIZED	(1 << 0)

#घोषणा rsnd_ctu_nr(priv) ((priv)->ctu_nr)
#घोषणा क्रम_each_rsnd_ctu(pos, priv, i)					\
	क्रम ((i) = 0;							\
	     ((i) < rsnd_ctu_nr(priv)) &&				\
		     ((pos) = (काष्ठा rsnd_ctu *)(priv)->ctu + i);	\
	     i++)

#घोषणा rsnd_mod_to_ctu(_mod)	\
	container_of((_mod), काष्ठा rsnd_ctu, mod)

#घोषणा rsnd_ctu_get(priv, id) ((काष्ठा rsnd_ctu *)(priv->ctu) + id)

अटल व्योम rsnd_ctu_activation(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, CTU_SWRSR, 0);
	rsnd_mod_ग_लिखो(mod, CTU_SWRSR, 1);
पूर्ण

अटल व्योम rsnd_ctu_halt(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, CTU_CTUIR, 1);
	rsnd_mod_ग_लिखो(mod, CTU_SWRSR, 0);
पूर्ण

अटल पूर्णांक rsnd_ctu_probe_(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   काष्ठा rsnd_priv *priv)
अणु
	वापस rsnd_cmd_attach(io, rsnd_mod_id(mod));
पूर्ण

अटल व्योम rsnd_ctu_value_init(काष्ठा rsnd_dai_stream *io,
			       काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);
	u32 cpmdr = 0;
	u32 scmdr = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < RSND_MAX_CHANNELS; i++) अणु
		u32 val = rsnd_kctrl_valm(ctu->pass, i);

		cpmdr |= val << (28 - (i * 4));

		अगर ((val > 0x8) && (scmdr < (val - 0x8)))
			scmdr = val - 0x8;
	पूर्ण

	rsnd_mod_ग_लिखो(mod, CTU_CTUIR, 1);

	rsnd_mod_ग_लिखो(mod, CTU_ADINR, rsnd_runसमय_channel_original(io));

	rsnd_mod_ग_लिखो(mod, CTU_CPMDR, cpmdr);

	rsnd_mod_ग_लिखो(mod, CTU_SCMDR, scmdr);

	क्रम (i = 0; i < 4; i++) अणु

		अगर (i >= scmdr)
			अवरोध;

		क्रम (j = 0; j < RSND_MAX_CHANNELS; j++)
			rsnd_mod_ग_लिखो(mod, CTU_SVxxR(i, j), rsnd_kctrl_valm(ctu->sv[i], j));
	पूर्ण

	rsnd_mod_ग_लिखो(mod, CTU_CTUIR, 0);
पूर्ण

अटल व्योम rsnd_ctu_value_reset(काष्ठा rsnd_dai_stream *io,
				 काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);
	पूर्णांक i;

	अगर (!rsnd_kctrl_vals(ctu->reset))
		वापस;

	क्रम (i = 0; i < RSND_MAX_CHANNELS; i++) अणु
		rsnd_kctrl_valm(ctu->pass, i) = 0;
		rsnd_kctrl_valm(ctu->sv[0],  i) = 0;
		rsnd_kctrl_valm(ctu->sv[1],  i) = 0;
		rsnd_kctrl_valm(ctu->sv[2],  i) = 0;
		rsnd_kctrl_valm(ctu->sv[3],  i) = 0;
	पूर्ण
	rsnd_kctrl_vals(ctu->reset) = 0;
पूर्ण

अटल पूर्णांक rsnd_ctu_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_घातer_on(mod);

	rsnd_ctu_activation(mod);

	rsnd_ctu_value_init(io, mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ctu_quit(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_ctu_halt(mod);

	rsnd_mod_घातer_off(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ctu_pcm_new(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);
	पूर्णांक ret;

	अगर (rsnd_flags_has(ctu, KCTRL_INITIALIZED))
		वापस 0;

	/* CTU Pass */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU Pass",
			       rsnd_kctrl_accept_anyसमय,
			       शून्य,
			       &ctu->pass, RSND_MAX_CHANNELS,
			       0xC);
	अगर (ret < 0)
		वापस ret;

	/* ROW0 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV0",
			       rsnd_kctrl_accept_anyसमय,
			       शून्य,
			       &ctu->sv[0], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	अगर (ret < 0)
		वापस ret;

	/* ROW1 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV1",
			       rsnd_kctrl_accept_anyसमय,
			       शून्य,
			       &ctu->sv[1], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	अगर (ret < 0)
		वापस ret;

	/* ROW2 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV2",
			       rsnd_kctrl_accept_anyसमय,
			       शून्य,
			       &ctu->sv[2], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	अगर (ret < 0)
		वापस ret;

	/* ROW3 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV3",
			       rsnd_kctrl_accept_anyसमय,
			       शून्य,
			       &ctu->sv[3], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	अगर (ret < 0)
		वापस ret;

	/* Reset */
	ret = rsnd_kctrl_new_s(mod, io, rtd, "CTU Reset",
			       rsnd_kctrl_accept_anyसमय,
			       rsnd_ctu_value_reset,
			       &ctu->reset, 1);

	rsnd_flags_set(ctu, KCTRL_INITIALIZED);

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_ctu_id(काष्ठा rsnd_mod *mod)
अणु
	/*
	 * ctu00: -> 0, ctu01: -> 0, ctu02: -> 0, ctu03: -> 0
	 * ctu10: -> 1, ctu11: -> 1, ctu12: -> 1, ctu13: -> 1
	 */
	वापस mod->id / 4;
पूर्ण

अटल पूर्णांक rsnd_ctu_id_sub(काष्ठा rsnd_mod *mod)
अणु
	/*
	 * ctu00: -> 0, ctu01: -> 1, ctu02: -> 2, ctu03: -> 3
	 * ctu10: -> 0, ctu11: -> 1, ctu12: -> 2, ctu13: -> 3
	 */
	वापस mod->id % 4;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_ctu_ops = अणु
	.name		= CTU_NAME,
	.probe		= rsnd_ctu_probe_,
	.init		= rsnd_ctu_init,
	.quit		= rsnd_ctu_quit,
	.pcm_new	= rsnd_ctu_pcm_new,
	.get_status	= rsnd_mod_get_status,
	.id		= rsnd_ctu_id,
	.id_sub		= rsnd_ctu_id_sub,
	.id_cmd		= rsnd_mod_id_raw,
पूर्ण;

काष्ठा rsnd_mod *rsnd_ctu_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_ctu_nr(priv)))
		id = 0;

	वापस rsnd_mod_get(rsnd_ctu_get(priv, id));
पूर्ण

पूर्णांक rsnd_ctu_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_ctu *ctu;
	काष्ठा clk *clk;
	अक्षर name[CTU_NAME_SIZE];
	पूर्णांक i, nr, ret;

	/* This driver करोesn't support Gen1 at this poपूर्णांक */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	node = rsnd_ctu_of_node(priv);
	अगर (!node)
		वापस 0; /* not used is not error */

	nr = of_get_child_count(node);
	अगर (!nr) अणु
		ret = -EINVAL;
		जाओ rsnd_ctu_probe_करोne;
	पूर्ण

	ctu = devm_kसुस्मृति(dev, nr, माप(*ctu), GFP_KERNEL);
	अगर (!ctu) अणु
		ret = -ENOMEM;
		जाओ rsnd_ctu_probe_करोne;
	पूर्ण

	priv->ctu_nr	= nr;
	priv->ctu	= ctu;

	i = 0;
	ret = 0;
	क्रम_each_child_of_node(node, np) अणु
		ctu = rsnd_ctu_get(priv, i);

		/*
		 * CTU00, CTU01, CTU02, CTU03 => CTU0
		 * CTU10, CTU11, CTU12, CTU13 => CTU1
		 */
		snम_लिखो(name, CTU_NAME_SIZE, "%s.%d",
			 CTU_NAME, i / 4);

		clk = devm_clk_get(dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			of_node_put(np);
			जाओ rsnd_ctu_probe_करोne;
		पूर्ण

		ret = rsnd_mod_init(priv, rsnd_mod_get(ctu), &rsnd_ctu_ops,
				    clk, RSND_MOD_CTU, i);
		अगर (ret) अणु
			of_node_put(np);
			जाओ rsnd_ctu_probe_करोne;
		पूर्ण

		i++;
	पूर्ण


rsnd_ctu_probe_करोne:
	of_node_put(node);

	वापस ret;
पूर्ण

व्योम rsnd_ctu_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ctu *ctu;
	पूर्णांक i;

	क्रम_each_rsnd_ctu(ctu, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(ctu));
	पूर्ण
पूर्ण
