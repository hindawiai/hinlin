<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car CMD support
//
// Copyright (C) 2015 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश "rsnd.h"

काष्ठा rsnd_cmd अणु
	काष्ठा rsnd_mod mod;
पूर्ण;

#घोषणा CMD_NAME "cmd"

#घोषणा rsnd_cmd_nr(priv) ((priv)->cmd_nr)
#घोषणा क्रम_each_rsnd_cmd(pos, priv, i)					\
	क्रम ((i) = 0;							\
	     ((i) < rsnd_cmd_nr(priv)) &&				\
		     ((pos) = (काष्ठा rsnd_cmd *)(priv)->cmd + i);	\
	     i++)

अटल पूर्णांक rsnd_cmd_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_mod *dvc = rsnd_io_to_mod_dvc(io);
	काष्ठा rsnd_mod *mix = rsnd_io_to_mod_mix(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	u32 data;
	अटल स्थिर u32 path[] = अणु
		[1] = 1 << 0,
		[5] = 1 << 8,
		[6] = 1 << 12,
		[9] = 1 << 15,
	पूर्ण;

	अगर (!mix && !dvc)
		वापस 0;

	अगर (ARRAY_SIZE(path) < rsnd_mod_id(mod) + 1)
		वापस -ENXIO;

	अगर (mix) अणु
		काष्ठा rsnd_dai *rdai;
		पूर्णांक i;

		/*
		 * it is assuming that पूर्णांकegrater is well understanding about
		 * data path. Here करोesn't check impossible connection,
		 * like src2 + src5
		 */
		data = 0;
		क्रम_each_rsnd_dai(rdai, priv, i) अणु
			काष्ठा rsnd_dai_stream *tio = &rdai->playback;
			काष्ठा rsnd_mod *src = rsnd_io_to_mod_src(tio);

			अगर (mix == rsnd_io_to_mod_mix(tio))
				data |= path[rsnd_mod_id(src)];

			tio = &rdai->capture;
			src = rsnd_io_to_mod_src(tio);
			अगर (mix == rsnd_io_to_mod_mix(tio))
				data |= path[rsnd_mod_id(src)];
		पूर्ण

	पूर्ण अन्यथा अणु
		काष्ठा rsnd_mod *src = rsnd_io_to_mod_src(io);

		अटल स्थिर u8 cmd_हाल[] = अणु
			[0] = 0x3,
			[1] = 0x3,
			[2] = 0x4,
			[3] = 0x1,
			[4] = 0x2,
			[5] = 0x4,
			[6] = 0x1,
			[9] = 0x2,
		पूर्ण;

		अगर (unlikely(!src))
			वापस -EIO;

		data = path[rsnd_mod_id(src)] |
			cmd_हाल[rsnd_mod_id(src)] << 16;
	पूर्ण

	dev_dbg(dev, "ctu/mix path = 0x%08x\n", data);

	rsnd_mod_ग_लिखो(mod, CMD_ROUTE_SLCT, data);
	rsnd_mod_ग_लिखो(mod, CMD_BUSIF_MODE, rsnd_get_busअगर_shअगरt(io, mod) | 1);
	rsnd_mod_ग_लिखो(mod, CMD_BUSIF_DALIGN, rsnd_get_dalign(mod, io));

	rsnd_adg_set_cmd_timsel_gen2(mod, io);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_cmd_start(काष्ठा rsnd_mod *mod,
			  काष्ठा rsnd_dai_stream *io,
			  काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_ग_लिखो(mod, CMD_CTRL, 0x10);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_cmd_stop(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	rsnd_mod_ग_लिखो(mod, CMD_CTRL, 0);

	वापस 0;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_cmd_ops = अणु
	.name		= CMD_NAME,
	.init		= rsnd_cmd_init,
	.start		= rsnd_cmd_start,
	.stop		= rsnd_cmd_stop,
	.get_status	= rsnd_mod_get_status,
पूर्ण;

अटल काष्ठा rsnd_mod *rsnd_cmd_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_cmd_nr(priv)))
		id = 0;

	वापस rsnd_mod_get((काष्ठा rsnd_cmd *)(priv->cmd) + id);
पूर्ण
पूर्णांक rsnd_cmd_attach(काष्ठा rsnd_dai_stream *io, पूर्णांक id)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा rsnd_mod *mod = rsnd_cmd_mod_get(priv, id);

	वापस rsnd_dai_connect(mod, io, mod->type);
पूर्ण

पूर्णांक rsnd_cmd_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_cmd *cmd;
	पूर्णांक i, nr;

	/* This driver करोesn't support Gen1 at this poपूर्णांक */
	अगर (rsnd_is_gen1(priv))
		वापस 0;

	/* same number as DVC */
	nr = priv->dvc_nr;
	अगर (!nr)
		वापस 0;

	cmd = devm_kसुस्मृति(dev, nr, माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	priv->cmd_nr	= nr;
	priv->cmd	= cmd;

	क्रम_each_rsnd_cmd(cmd, priv, i) अणु
		पूर्णांक ret = rsnd_mod_init(priv, rsnd_mod_get(cmd),
					&rsnd_cmd_ops, शून्य,
					RSND_MOD_CMD, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rsnd_cmd_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_cmd *cmd;
	पूर्णांक i;

	क्रम_each_rsnd_cmd(cmd, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(cmd));
	पूर्ण
पूर्ण
