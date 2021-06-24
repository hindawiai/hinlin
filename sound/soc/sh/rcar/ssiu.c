<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car SSIU support
//
// Copyright (c) 2015 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश "rsnd.h"

#घोषणा SSIU_NAME "ssiu"

काष्ठा rsnd_ssiu अणु
	काष्ठा rsnd_mod mod;
	u32 busअगर_status[8]; /* क्रम BUSIF0 - BUSIF7 */
	अचिन्हित पूर्णांक usrcnt;
	पूर्णांक id;
	पूर्णांक id_sub;
पूर्ण;

/* SSI_MODE */
#घोषणा TDM_EXT		(1 << 0)
#घोषणा TDM_SPLIT	(1 << 8)

#घोषणा rsnd_ssiu_nr(priv) ((priv)->ssiu_nr)
#घोषणा rsnd_mod_to_ssiu(_mod) container_of((_mod), काष्ठा rsnd_ssiu, mod)
#घोषणा क्रम_each_rsnd_ssiu(pos, priv, i)				\
	क्रम (i = 0;							\
	     (i < rsnd_ssiu_nr(priv)) &&				\
		     ((pos) = ((काष्ठा rsnd_ssiu *)(priv)->ssiu + i));	\
	     i++)

/*
 *	SSI	Gen2		Gen3
 *	0	BUSIF0-3	BUSIF0-7
 *	1	BUSIF0-3	BUSIF0-7
 *	2	BUSIF0-3	BUSIF0-7
 *	3	BUSIF0		BUSIF0-7
 *	4	BUSIF0		BUSIF0-7
 *	5	BUSIF0		BUSIF0
 *	6	BUSIF0		BUSIF0
 *	7	BUSIF0		BUSIF0
 *	8	BUSIF0		BUSIF0
 *	9	BUSIF0-3	BUSIF0-7
 *	total	22		52
 */
अटल स्थिर पूर्णांक gen2_id[] = अणु 0, 4,  8, 12, 13, 14, 15, 16, 17, 18 पूर्ण;
अटल स्थिर पूर्णांक gen3_id[] = अणु 0, 8, 16, 24, 32, 40, 41, 42, 43, 44 पूर्ण;

अटल u32 *rsnd_ssiu_get_status(काष्ठा rsnd_mod *mod,
				 काष्ठा rsnd_dai_stream *io,
				 क्रमागत rsnd_mod_type type)
अणु
	काष्ठा rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);
	पूर्णांक busअगर = rsnd_mod_id_sub(mod);

	वापस &ssiu->busअगर_status[busअगर];
पूर्ण

अटल पूर्णांक rsnd_ssiu_init(काष्ठा rsnd_mod *mod,
			  काष्ठा rsnd_dai_stream *io,
			  काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	u32 ssis = rsnd_ssi_multi_secondaries_runसमय(io);
	पूर्णांक use_busअगर = rsnd_ssi_use_busअगर(io);
	पूर्णांक id = rsnd_mod_id(mod);
	पूर्णांक is_clk_master = rsnd_rdai_is_clk_master(rdai);
	u32 val1, val2;
	पूर्णांक i;

	/* clear status */
	चयन (id) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		क्रम (i = 0; i < 4; i++)
			rsnd_mod_ग_लिखो(mod, SSI_SYS_STATUS(i * 2), 0xf << (id * 4));
		अवरोध;
	हाल 9:
		क्रम (i = 0; i < 4; i++)
			rsnd_mod_ग_लिखो(mod, SSI_SYS_STATUS((i * 2) + 1), 0xf << 4);
		अवरोध;
	पूर्ण

	/*
	 * SSI_MODE0
	 */
	rsnd_mod_bset(mod, SSI_MODE0, (1 << id), !use_busअगर << id);

	/*
	 * SSI_MODE1 / SSI_MODE2
	 *
	 * FIXME
	 * sharing/multi with SSI0 are मुख्यly supported
	 */
	val1 = rsnd_mod_पढ़ो(mod, SSI_MODE1);
	val2 = rsnd_mod_पढ़ो(mod, SSI_MODE2);
	अगर (rsnd_ssi_is_pin_sharing(io)) अणु

		ssis |= (1 << id);

	पूर्ण अन्यथा अगर (ssis) अणु
		/*
		 * Multi SSI
		 *
		 * set synchronized bit here
		 */

		/* SSI4 is synchronized with SSI3 */
		अगर (ssis & (1 << 4))
			val1 |= (1 << 20);
		/* SSI012 are synchronized */
		अगर (ssis == 0x0006)
			val1 |= (1 << 4);
		/* SSI0129 are synchronized */
		अगर (ssis == 0x0206)
			val2 |= (1 << 4);
	पूर्ण

	/* SSI1 is sharing pin with SSI0 */
	अगर (ssis & (1 << 1))
		val1 |= is_clk_master ? 0x2 : 0x1;

	/* SSI2 is sharing pin with SSI0 */
	अगर (ssis & (1 << 2))
		val1 |= is_clk_master ?	0x2 << 2 :
					0x1 << 2;
	/* SSI4 is sharing pin with SSI3 */
	अगर (ssis & (1 << 4))
		val1 |= is_clk_master ? 0x2 << 16 :
					0x1 << 16;
	/* SSI9 is sharing pin with SSI0 */
	अगर (ssis & (1 << 9))
		val2 |= is_clk_master ? 0x2 : 0x1;

	rsnd_mod_bset(mod, SSI_MODE1, 0x0013001f, val1);
	rsnd_mod_bset(mod, SSI_MODE2, 0x00000017, val2);

	वापस 0;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_ssiu_ops_gen1 = अणु
	.name		= SSIU_NAME,
	.init		= rsnd_ssiu_init,
	.get_status	= rsnd_ssiu_get_status,
पूर्ण;

अटल पूर्णांक rsnd_ssiu_init_gen2(काष्ठा rsnd_mod *mod,
			       काष्ठा rsnd_dai_stream *io,
			       काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);
	u32 has_hdmi0 = rsnd_flags_has(io, RSND_STREAM_HDMI0);
	u32 has_hdmi1 = rsnd_flags_has(io, RSND_STREAM_HDMI1);
	पूर्णांक ret;
	u32 mode = 0;

	ret = rsnd_ssiu_init(mod, io, priv);
	अगर (ret < 0)
		वापस ret;

	ssiu->usrcnt++;

	/*
	 * TDM Extend/Split Mode
	 * see
	 *	rsnd_ssi_config_init()
	 */
	अगर (rsnd_runसमय_is_tdm(io))
		mode = TDM_EXT;
	अन्यथा अगर (rsnd_runसमय_is_tdm_split(io))
		mode = TDM_SPLIT;

	rsnd_mod_ग_लिखो(mod, SSI_MODE, mode);

	अगर (rsnd_ssi_use_busअगर(io)) अणु
		पूर्णांक id = rsnd_mod_id(mod);
		पूर्णांक busअगर = rsnd_mod_id_sub(mod);
		क्रमागत rsnd_reg adinr_reg, mode_reg, dalign_reg;

		अगर ((id == 9) && (busअगर >= 4)) अणु
			adinr_reg = SSI9_BUSIF_ADINR(busअगर);
			mode_reg = SSI9_BUSIF_MODE(busअगर);
			dalign_reg = SSI9_BUSIF_DALIGN(busअगर);
		पूर्ण अन्यथा अणु
			adinr_reg = SSI_BUSIF_ADINR(busअगर);
			mode_reg = SSI_BUSIF_MODE(busअगर);
			dalign_reg = SSI_BUSIF_DALIGN(busअगर);
		पूर्ण

		rsnd_mod_ग_लिखो(mod, adinr_reg,
			       rsnd_get_adinr_bit(mod, io) |
			       (rsnd_io_is_play(io) ?
				rsnd_runसमय_channel_after_ctu(io) :
				rsnd_runसमय_channel_original(io)));
		rsnd_mod_ग_लिखो(mod, mode_reg,
			       rsnd_get_busअगर_shअगरt(io, mod) | 1);
		rsnd_mod_ग_लिखो(mod, dalign_reg,
			       rsnd_get_dalign(mod, io));
	पूर्ण

	अगर (has_hdmi0 || has_hdmi1) अणु
		क्रमागत rsnd_mod_type rsnd_ssi_array[] = अणु
			RSND_MOD_SSIM1,
			RSND_MOD_SSIM2,
			RSND_MOD_SSIM3,
		पूर्ण;
		काष्ठा rsnd_mod *ssi_mod = rsnd_io_to_mod_ssi(io);
		काष्ठा rsnd_mod *pos;
		u32 val;
		पूर्णांक i;

		i = rsnd_mod_id(ssi_mod);

		/* output all same SSI as शेष */
		val =	i << 16 |
			i << 20 |
			i << 24 |
			i << 28 |
			i;

		क्रम_each_rsnd_mod_array(i, pos, io, rsnd_ssi_array) अणु
			पूर्णांक shअगरt = (i * 4) + 20;

			val	= (val & ~(0xF << shअगरt)) |
				rsnd_mod_id(pos) << shअगरt;
		पूर्ण

		अगर (has_hdmi0)
			rsnd_mod_ग_लिखो(mod, HDMI0_SEL, val);
		अगर (has_hdmi1)
			rsnd_mod_ग_लिखो(mod, HDMI1_SEL, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssiu_start_gen2(काष्ठा rsnd_mod *mod,
				काष्ठा rsnd_dai_stream *io,
				काष्ठा rsnd_priv *priv)
अणु
	पूर्णांक busअगर = rsnd_mod_id_sub(mod);

	अगर (!rsnd_ssi_use_busअगर(io))
		वापस 0;

	rsnd_mod_bset(mod, SSI_CTRL, 1 << (busअगर * 4), 1 << (busअगर * 4));

	अगर (rsnd_ssi_multi_secondaries_runसमय(io))
		rsnd_mod_ग_लिखो(mod, SSI_CONTROL, 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssiu_stop_gen2(काष्ठा rsnd_mod *mod,
			       काष्ठा rsnd_dai_stream *io,
			       काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);
	पूर्णांक busअगर = rsnd_mod_id_sub(mod);

	अगर (!rsnd_ssi_use_busअगर(io))
		वापस 0;

	rsnd_mod_bset(mod, SSI_CTRL, 1 << (busअगर * 4), 0);

	अगर (--ssiu->usrcnt)
		वापस 0;

	अगर (rsnd_ssi_multi_secondaries_runसमय(io))
		rsnd_mod_ग_लिखो(mod, SSI_CONTROL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssiu_id(काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);

	/* see rsnd_ssiu_probe() */
	वापस ssiu->id;
पूर्ण

अटल पूर्णांक rsnd_ssiu_id_sub(काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);

	/* see rsnd_ssiu_probe() */
	वापस ssiu->id_sub;
पूर्ण

अटल काष्ठा dma_chan *rsnd_ssiu_dma_req(काष्ठा rsnd_dai_stream *io,
					  काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	पूर्णांक is_play = rsnd_io_is_play(io);
	अक्षर *name;

	/*
	 * It should use "rcar_sound,ssiu" on DT.
	 * But, we need to keep compatibility क्रम old version.
	 *
	 * If it has "rcar_sound.ssiu", it will be used.
	 * If not, "rcar_sound.ssi" will be used.
	 * see
	 *	rsnd_ssi_dma_req()
	 *	rsnd_dma_of_path()
	 */

	name = is_play ? "rx" : "tx";

	वापस rsnd_dma_request_channel(rsnd_ssiu_of_node(priv),
					mod, name);
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_ssiu_ops_gen2 = अणु
	.name		= SSIU_NAME,
	.dma_req	= rsnd_ssiu_dma_req,
	.init		= rsnd_ssiu_init_gen2,
	.start		= rsnd_ssiu_start_gen2,
	.stop		= rsnd_ssiu_stop_gen2,
	.get_status	= rsnd_ssiu_get_status,
पूर्ण;

अटल काष्ठा rsnd_mod *rsnd_ssiu_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_ssiu_nr(priv)))
		id = 0;

	वापस rsnd_mod_get((काष्ठा rsnd_ssiu *)(priv->ssiu) + id);
पूर्ण

अटल व्योम rsnd_parse_connect_ssiu_compatible(काष्ठा rsnd_priv *priv,
					       काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_mod *ssi_mod = rsnd_io_to_mod_ssi(io);
	काष्ठा rsnd_ssiu *ssiu;
	पूर्णांक i;

	अगर (!ssi_mod)
		वापस;

	/* select BUSIF0 */
	क्रम_each_rsnd_ssiu(ssiu, priv, i) अणु
		काष्ठा rsnd_mod *mod = rsnd_mod_get(ssiu);

		अगर ((rsnd_mod_id(ssi_mod) == rsnd_mod_id(mod)) &&
		    (rsnd_mod_id_sub(mod) == 0)) अणु
			rsnd_dai_connect(mod, io, mod->type);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rsnd_parse_connect_ssiu(काष्ठा rsnd_dai *rdai,
			     काष्ठा device_node *playback,
			     काष्ठा device_node *capture)
अणु
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा device_node *node = rsnd_ssiu_of_node(priv);
	काष्ठा rsnd_dai_stream *io_p = &rdai->playback;
	काष्ठा rsnd_dai_stream *io_c = &rdai->capture;

	/* use rcar_sound,ssiu अगर exist */
	अगर (node) अणु
		काष्ठा device_node *np;
		पूर्णांक i = 0;

		क्रम_each_child_of_node(node, np) अणु
			काष्ठा rsnd_mod *mod = rsnd_ssiu_mod_get(priv, i);

			अगर (np == playback)
				rsnd_dai_connect(mod, io_p, mod->type);
			अगर (np == capture)
				rsnd_dai_connect(mod, io_c, mod->type);
			i++;
		पूर्ण

		of_node_put(node);
	पूर्ण

	/* Keep DT compatibility */
	अगर (!rsnd_io_to_mod_ssiu(io_p))
		rsnd_parse_connect_ssiu_compatible(priv, io_p);
	अगर (!rsnd_io_to_mod_ssiu(io_c))
		rsnd_parse_connect_ssiu_compatible(priv, io_c);
पूर्ण

पूर्णांक rsnd_ssiu_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *node;
	काष्ठा rsnd_ssiu *ssiu;
	काष्ठा rsnd_mod_ops *ops;
	स्थिर पूर्णांक *list = शून्य;
	पूर्णांक i, nr;

	/*
	 * Keep DT compatibility.
	 * अगर it has "rcar_sound,ssiu", use it.
	 * अगर not, use "rcar_sound,ssi"
	 * see
	 *	rsnd_ssiu_bufsअगर_to_id()
	 */
	node = rsnd_ssiu_of_node(priv);
	अगर (node)
		nr = of_get_child_count(node);
	अन्यथा
		nr = priv->ssi_nr;

	ssiu	= devm_kसुस्मृति(dev, nr, माप(*ssiu), GFP_KERNEL);
	अगर (!ssiu)
		वापस -ENOMEM;

	priv->ssiu	= ssiu;
	priv->ssiu_nr	= nr;

	अगर (rsnd_is_gen1(priv))
		ops = &rsnd_ssiu_ops_gen1;
	अन्यथा
		ops = &rsnd_ssiu_ops_gen2;

	/* Keep compatibility */
	nr = 0;
	अगर ((node) &&
	    (ops == &rsnd_ssiu_ops_gen2)) अणु
		ops->id		= rsnd_ssiu_id;
		ops->id_sub	= rsnd_ssiu_id_sub;

		अगर (rsnd_is_gen2(priv)) अणु
			list	= gen2_id;
			nr	= ARRAY_SIZE(gen2_id);
		पूर्ण अन्यथा अगर (rsnd_is_gen3(priv)) अणु
			list	= gen3_id;
			nr	= ARRAY_SIZE(gen3_id);
		पूर्ण अन्यथा अणु
			dev_err(dev, "unknown SSIU\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	क्रम_each_rsnd_ssiu(ssiu, priv, i) अणु
		पूर्णांक ret;

		अगर (node) अणु
			पूर्णांक j;

			/*
			 * see
			 *	rsnd_ssiu_get_id()
			 *	rsnd_ssiu_get_id_sub()
			 */
			क्रम (j = 0; j < nr; j++) अणु
				अगर (list[j] > i)
					अवरोध;
				ssiu->id	= j;
				ssiu->id_sub	= i - list[ssiu->id];
			पूर्ण
		पूर्ण अन्यथा अणु
			ssiu->id = i;
		पूर्ण

		ret = rsnd_mod_init(priv, rsnd_mod_get(ssiu),
				    ops, शून्य, RSND_MOD_SSIU, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rsnd_ssiu_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssiu *ssiu;
	पूर्णांक i;

	क्रम_each_rsnd_ssiu(ssiu, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(ssiu));
	पूर्ण
पूर्ण
