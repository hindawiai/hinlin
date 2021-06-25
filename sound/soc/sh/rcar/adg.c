<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Helper routines क्रम R-Car sound ADG.
//
//  Copyright (C) 2013  Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश <linux/clk-provider.h>
#समावेश "rsnd.h"

#घोषणा CLKA	0
#घोषणा CLKB	1
#घोषणा CLKC	2
#घोषणा CLKI	3
#घोषणा CLKMAX	4

#घोषणा CLKOUT	0
#घोषणा CLKOUT1	1
#घोषणा CLKOUT2	2
#घोषणा CLKOUT3	3
#घोषणा CLKOUTMAX 4

#घोषणा BRRx_MASK(x) (0x3FF & x)

अटल काष्ठा rsnd_mod_ops adg_ops = अणु
	.name = "adg",
पूर्ण;

काष्ठा rsnd_adg अणु
	काष्ठा clk *clk[CLKMAX];
	काष्ठा clk *clkout[CLKOUTMAX];
	काष्ठा clk_onecell_data onecell;
	काष्ठा rsnd_mod mod;
	पूर्णांक clk_rate[CLKMAX];
	u32 flags;
	u32 ckr;
	u32 rbga;
	u32 rbgb;

	पूर्णांक rbga_rate_क्रम_441khz; /* RBGA */
	पूर्णांक rbgb_rate_क्रम_48khz;  /* RBGB */
पूर्ण;

#घोषणा LRCLK_ASYNC	(1 << 0)
#घोषणा AUDIO_OUT_48	(1 << 1)

#घोषणा क्रम_each_rsnd_clk(pos, adg, i)		\
	क्रम (i = 0;				\
	     (i < CLKMAX) &&			\
	     ((pos) = adg->clk[i]);		\
	     i++)
#घोषणा क्रम_each_rsnd_clkout(pos, adg, i)	\
	क्रम (i = 0;				\
	     (i < CLKOUTMAX) &&			\
	     ((pos) = adg->clkout[i]);	\
	     i++)
#घोषणा rsnd_priv_to_adg(priv) ((काष्ठा rsnd_adg *)(priv)->adg)

अटल स्थिर अक्षर * स्थिर clk_name[] = अणु
	[CLKA]	= "clk_a",
	[CLKB]	= "clk_b",
	[CLKC]	= "clk_c",
	[CLKI]	= "clk_i",
पूर्ण;

अटल u32 rsnd_adg_calculate_rbgx(अचिन्हित दीर्घ भाग)
अणु
	पूर्णांक i;

	अगर (!भाग)
		वापस 0;

	क्रम (i = 3; i >= 0; i--) अणु
		पूर्णांक ratio = 2 << (i * 2);
		अगर (0 == (भाग % ratio))
			वापस (u32)((i << 8) | ((भाग / ratio) - 1));
	पूर्ण

	वापस ~0;
पूर्ण

अटल u32 rsnd_adg_ssi_ws_timing_gen2(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_mod *ssi_mod = rsnd_io_to_mod_ssi(io);
	पूर्णांक id = rsnd_mod_id(ssi_mod);
	पूर्णांक ws = id;

	अगर (rsnd_ssi_is_pin_sharing(io)) अणु
		चयन (id) अणु
		हाल 1:
		हाल 2:
		हाल 9:
			ws = 0;
			अवरोध;
		हाल 4:
			ws = 3;
			अवरोध;
		हाल 8:
			ws = 7;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (0x6 + ws) << 8;
पूर्ण

अटल व्योम __rsnd_adg_get_बारel_ratio(काष्ठा rsnd_priv *priv,
				       काष्ठा rsnd_dai_stream *io,
				       अचिन्हित पूर्णांक target_rate,
				       अचिन्हित पूर्णांक *target_val,
				       अचिन्हित पूर्णांक *target_en)
अणु
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक sel;
	अचिन्हित पूर्णांक val, en;
	अचिन्हित पूर्णांक min, dअगरf;
	अचिन्हित पूर्णांक sel_rate[] = अणु
		adg->clk_rate[CLKA],	/* 0000: CLKA */
		adg->clk_rate[CLKB],	/* 0001: CLKB */
		adg->clk_rate[CLKC],	/* 0010: CLKC */
		adg->rbga_rate_क्रम_441khz,	/* 0011: RBGA */
		adg->rbgb_rate_क्रम_48khz,	/* 0100: RBGB */
	पूर्ण;

	min = ~0;
	val = 0;
	en = 0;
	क्रम (sel = 0; sel < ARRAY_SIZE(sel_rate); sel++) अणु
		पूर्णांक idx = 0;
		पूर्णांक step = 2;
		पूर्णांक भाग;

		अगर (!sel_rate[sel])
			जारी;

		क्रम (भाग = 2; भाग <= 98304; भाग += step) अणु
			dअगरf = असल(target_rate - sel_rate[sel] / भाग);
			अगर (min > dअगरf) अणु
				val = (sel << 8) | idx;
				min = dअगरf;
				en = 1 << (sel + 1); /* fixme */
			पूर्ण

			/*
			 * step of 0_0000 / 0_0001 / 0_1101
			 * are out of order
			 */
			अगर ((idx > 2) && (idx % 2))
				step *= 2;
			अगर (idx == 0x1c) अणु
				भाग += step;
				step *= 2;
			पूर्ण
			idx++;
		पूर्ण
	पूर्ण

	अगर (min == ~0) अणु
		dev_err(dev, "no Input clock\n");
		वापस;
	पूर्ण

	*target_val = val;
	अगर (target_en)
		*target_en = en;
पूर्ण

अटल व्योम rsnd_adg_get_बारel_ratio(काष्ठा rsnd_priv *priv,
				       काष्ठा rsnd_dai_stream *io,
				       अचिन्हित पूर्णांक in_rate,
				       अचिन्हित पूर्णांक out_rate,
				       u32 *in, u32 *out, u32 *en)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	अचिन्हित पूर्णांक target_rate;
	u32 *target_val;
	u32 _in;
	u32 _out;
	u32 _en;

	/* शेष = SSI WS */
	_in =
	_out = rsnd_adg_ssi_ws_timing_gen2(io);

	target_rate = 0;
	target_val = शून्य;
	_en = 0;
	अगर (runसमय->rate != in_rate) अणु
		target_rate = out_rate;
		target_val  = &_out;
	पूर्ण अन्यथा अगर (runसमय->rate != out_rate) अणु
		target_rate = in_rate;
		target_val  = &_in;
	पूर्ण

	अगर (target_rate)
		__rsnd_adg_get_बारel_ratio(priv, io,
					     target_rate,
					     target_val, &_en);

	अगर (in)
		*in = _in;
	अगर (out)
		*out = _out;
	अगर (en)
		*en = _en;
पूर्ण

पूर्णांक rsnd_adg_set_cmd_timsel_gen2(काष्ठा rsnd_mod *cmd_mod,
				 काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(cmd_mod);
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा rsnd_mod *adg_mod = rsnd_mod_get(adg);
	पूर्णांक id = rsnd_mod_id(cmd_mod);
	पूर्णांक shअगरt = (id % 2) ? 16 : 0;
	u32 mask, val;

	rsnd_adg_get_बारel_ratio(priv, io,
				   rsnd_src_get_in_rate(priv, io),
				   rsnd_src_get_out_rate(priv, io),
				   शून्य, &val, शून्य);

	val  = val	<< shअगरt;
	mask = 0x0f1f	<< shअगरt;

	rsnd_mod_bset(adg_mod, CMDOUT_TIMSEL, mask, val);

	वापस 0;
पूर्ण

पूर्णांक rsnd_adg_set_src_बारel_gen2(काष्ठा rsnd_mod *src_mod,
				  काष्ठा rsnd_dai_stream *io,
				  अचिन्हित पूर्णांक in_rate,
				  अचिन्हित पूर्णांक out_rate)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(src_mod);
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा rsnd_mod *adg_mod = rsnd_mod_get(adg);
	u32 in, out;
	u32 mask, en;
	पूर्णांक id = rsnd_mod_id(src_mod);
	पूर्णांक shअगरt = (id % 2) ? 16 : 0;

	rsnd_mod_confirm_src(src_mod);

	rsnd_adg_get_बारel_ratio(priv, io,
				   in_rate, out_rate,
				   &in, &out, &en);

	in   = in	<< shअगरt;
	out  = out	<< shअगरt;
	mask = 0x0f1f	<< shअगरt;

	rsnd_mod_bset(adg_mod, SRCIN_TIMSEL(id / 2),  mask, in);
	rsnd_mod_bset(adg_mod, SRCOUT_TIMSEL(id / 2), mask, out);

	अगर (en)
		rsnd_mod_bset(adg_mod, DIV_EN, en, en);

	वापस 0;
पूर्ण

अटल व्योम rsnd_adg_set_ssi_clk(काष्ठा rsnd_mod *ssi_mod, u32 val)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(ssi_mod);
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा rsnd_mod *adg_mod = rsnd_mod_get(adg);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक id = rsnd_mod_id(ssi_mod);
	पूर्णांक shअगरt = (id % 4) * 8;
	u32 mask = 0xFF << shअगरt;

	rsnd_mod_confirm_ssi(ssi_mod);

	val = val << shअगरt;

	/*
	 * SSI 8 is not connected to ADG.
	 * it works with SSI 7
	 */
	अगर (id == 8)
		वापस;

	rsnd_mod_bset(adg_mod, AUDIO_CLK_SEL(id / 4), mask, val);

	dev_dbg(dev, "AUDIO_CLK_SEL is 0x%x\n", val);
पूर्ण

पूर्णांक rsnd_adg_clk_query(काष्ठा rsnd_priv *priv, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा clk *clk;
	पूर्णांक i;
	पूर्णांक sel_table[] = अणु
		[CLKA] = 0x1,
		[CLKB] = 0x2,
		[CLKC] = 0x3,
		[CLKI] = 0x0,
	पूर्ण;

	/*
	 * find suitable घड़ी from
	 * AUDIO_CLKA/AUDIO_CLKB/AUDIO_CLKC/AUDIO_CLKI.
	 */
	क्रम_each_rsnd_clk(clk, adg, i) अणु
		अगर (rate == adg->clk_rate[i])
			वापस sel_table[i];
	पूर्ण

	/*
	 * find भागided घड़ी from BRGA/BRGB
	 */
	अगर (rate == adg->rbga_rate_क्रम_441khz)
		वापस 0x10;

	अगर (rate == adg->rbgb_rate_क्रम_48khz)
		वापस 0x20;

	वापस -EIO;
पूर्ण

पूर्णांक rsnd_adg_ssi_clk_stop(काष्ठा rsnd_mod *ssi_mod)
अणु
	rsnd_adg_set_ssi_clk(ssi_mod, 0);

	वापस 0;
पूर्ण

पूर्णांक rsnd_adg_ssi_clk_try_start(काष्ठा rsnd_mod *ssi_mod, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(ssi_mod);
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_mod *adg_mod = rsnd_mod_get(adg);
	पूर्णांक data;
	u32 ckr = 0;

	data = rsnd_adg_clk_query(priv, rate);
	अगर (data < 0)
		वापस data;

	rsnd_adg_set_ssi_clk(ssi_mod, data);

	अगर (rsnd_flags_has(adg, LRCLK_ASYNC)) अणु
		अगर (rsnd_flags_has(adg, AUDIO_OUT_48))
			ckr = 0x80000000;
	पूर्ण अन्यथा अणु
		अगर (0 == (rate % 8000))
			ckr = 0x80000000;
	पूर्ण

	rsnd_mod_bset(adg_mod, BRGCKR, 0x80770000, adg->ckr | ckr);
	rsnd_mod_ग_लिखो(adg_mod, BRRA,  adg->rbga);
	rsnd_mod_ग_लिखो(adg_mod, BRRB,  adg->rbgb);

	dev_dbg(dev, "CLKOUT is based on BRG%c (= %dHz)\n",
		(ckr) ? 'B' : 'A',
		(ckr) ?	adg->rbgb_rate_क्रम_48khz :
			adg->rbga_rate_क्रम_441khz);

	वापस 0;
पूर्ण

व्योम rsnd_adg_clk_control(काष्ठा rsnd_priv *priv, पूर्णांक enable)
अणु
	काष्ठा rsnd_adg *adg = rsnd_priv_to_adg(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम_each_rsnd_clk(clk, adg, i) अणु
		अगर (enable) अणु
			पूर्णांक ret = clk_prepare_enable(clk);

			/*
			 * We shouldn't use clk_get_rate() under
			 * atomic context. Let's keep it when
			 * rsnd_adg_clk_enable() was called
			 */
			adg->clk_rate[i] = 0;
			अगर (ret < 0)
				dev_warn(dev, "can't use clk %d\n", i);
			अन्यथा
				adg->clk_rate[i] = clk_get_rate(clk);
		पूर्ण अन्यथा अणु
			अगर (adg->clk_rate[i])
				clk_disable_unprepare(clk);
			adg->clk_rate[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rsnd_adg_get_clkin(काष्ठा rsnd_priv *priv,
			       काष्ठा rsnd_adg *adg)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक i;

	क्रम (i = 0; i < CLKMAX; i++) अणु
		काष्ठा clk *clk = devm_clk_get(dev, clk_name[i]);

		adg->clk[i] = IS_ERR(clk) ? शून्य : clk;
	पूर्ण
पूर्ण

अटल व्योम rsnd_adg_get_clkout(काष्ठा rsnd_priv *priv,
				काष्ठा rsnd_adg *adg)
अणु
	काष्ठा clk *clk;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा property *prop;
	u32 ckr, rbgx, rbga, rbgb;
	u32 rate, भाग;
#घोषणा REQ_SIZE 2
	u32 req_rate[REQ_SIZE] = अणुपूर्ण;
	uपूर्णांक32_t count = 0;
	अचिन्हित दीर्घ req_48kHz_rate, req_441kHz_rate;
	पूर्णांक i, req_size;
	स्थिर अक्षर *parent_clk_name = शून्य;
	अटल स्थिर अक्षर * स्थिर clkout_name[] = अणु
		[CLKOUT]  = "audio_clkout",
		[CLKOUT1] = "audio_clkout1",
		[CLKOUT2] = "audio_clkout2",
		[CLKOUT3] = "audio_clkout3",
	पूर्ण;
	पूर्णांक brg_table[] = अणु
		[CLKA] = 0x0,
		[CLKB] = 0x1,
		[CLKC] = 0x4,
		[CLKI] = 0x2,
	पूर्ण;

	ckr = 0;
	rbga = 2; /* शेष 1/6 */
	rbgb = 2; /* शेष 1/6 */

	/*
	 * ADG supports BRRA/BRRB output only
	 * this means all clkout0/1/2/3 will be same rate
	 */
	prop = of_find_property(np, "clock-frequency", शून्य);
	अगर (!prop)
		जाओ rsnd_adg_get_clkout_end;

	req_size = prop->length / माप(u32);
	अगर (req_size > REQ_SIZE) अणु
		dev_err(dev,
			"too many clock-frequency, use top %d\n", REQ_SIZE);
		req_size = REQ_SIZE;
	पूर्ण

	of_property_पढ़ो_u32_array(np, "clock-frequency", req_rate, req_size);
	req_48kHz_rate = 0;
	req_441kHz_rate = 0;
	क्रम (i = 0; i < req_size; i++) अणु
		अगर (0 == (req_rate[i] % 44100))
			req_441kHz_rate = req_rate[i];
		अगर (0 == (req_rate[i] % 48000))
			req_48kHz_rate = req_rate[i];
	पूर्ण

	अगर (req_rate[0] % 48000 == 0)
		rsnd_flags_set(adg, AUDIO_OUT_48);

	अगर (of_get_property(np, "clkout-lr-asynchronous", शून्य))
		rsnd_flags_set(adg, LRCLK_ASYNC);

	/*
	 * This driver is assuming that AUDIO_CLKA/AUDIO_CLKB/AUDIO_CLKC
	 * have 44.1kHz or 48kHz base घड़ीs क्रम now.
	 *
	 * SSI itself can भागide parent घड़ी by 1/1 - 1/16
	 * see
	 *	rsnd_adg_ssi_clk_try_start()
	 *	rsnd_ssi_master_clk_start()
	 */
	adg->rbga_rate_क्रम_441khz	= 0;
	adg->rbgb_rate_क्रम_48khz	= 0;
	क्रम_each_rsnd_clk(clk, adg, i) अणु
		rate = clk_get_rate(clk);

		अगर (0 == rate) /* not used */
			जारी;

		/* RBGA */
		अगर (!adg->rbga_rate_क्रम_441khz && (0 == rate % 44100)) अणु
			भाग = 6;
			अगर (req_441kHz_rate)
				भाग = rate / req_441kHz_rate;
			rbgx = rsnd_adg_calculate_rbgx(भाग);
			अगर (BRRx_MASK(rbgx) == rbgx) अणु
				rbga = rbgx;
				adg->rbga_rate_क्रम_441khz = rate / भाग;
				ckr |= brg_table[i] << 20;
				अगर (req_441kHz_rate &&
				    !rsnd_flags_has(adg, AUDIO_OUT_48))
					parent_clk_name = __clk_get_name(clk);
			पूर्ण
		पूर्ण

		/* RBGB */
		अगर (!adg->rbgb_rate_क्रम_48khz && (0 == rate % 48000)) अणु
			भाग = 6;
			अगर (req_48kHz_rate)
				भाग = rate / req_48kHz_rate;
			rbgx = rsnd_adg_calculate_rbgx(भाग);
			अगर (BRRx_MASK(rbgx) == rbgx) अणु
				rbgb = rbgx;
				adg->rbgb_rate_क्रम_48khz = rate / भाग;
				ckr |= brg_table[i] << 16;
				अगर (req_48kHz_rate &&
				    rsnd_flags_has(adg, AUDIO_OUT_48))
					parent_clk_name = __clk_get_name(clk);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * ADG supports BRRA/BRRB output only.
	 * this means all clkout0/1/2/3 will be * same rate
	 */

	of_property_पढ़ो_u32(np, "#clock-cells", &count);
	/*
	 * क्रम clkout
	 */
	अगर (!count) अणु
		clk = clk_रेजिस्टर_fixed_rate(dev, clkout_name[CLKOUT],
					      parent_clk_name, 0, req_rate[0]);
		अगर (!IS_ERR(clk)) अणु
			adg->clkout[CLKOUT] = clk;
			of_clk_add_provider(np, of_clk_src_simple_get, clk);
		पूर्ण
	पूर्ण
	/*
	 * क्रम clkout0/1/2/3
	 */
	अन्यथा अणु
		क्रम (i = 0; i < CLKOUTMAX; i++) अणु
			clk = clk_रेजिस्टर_fixed_rate(dev, clkout_name[i],
						      parent_clk_name, 0,
						      req_rate[0]);
			अगर (!IS_ERR(clk))
				adg->clkout[i] = clk;
		पूर्ण
		adg->onecell.clks	= adg->clkout;
		adg->onecell.clk_num	= CLKOUTMAX;
		of_clk_add_provider(np, of_clk_src_onecell_get,
				    &adg->onecell);
	पूर्ण

rsnd_adg_get_clkout_end:
	adg->ckr = ckr;
	adg->rbga = rbga;
	adg->rbgb = rbgb;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम rsnd_adg_clk_dbg_info(काष्ठा rsnd_priv *priv, काष्ठा rsnd_adg *adg)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम_each_rsnd_clk(clk, adg, i)
		dev_dbg(dev, "%s    : %pa : %ld\n",
			clk_name[i], clk, clk_get_rate(clk));

	dev_dbg(dev, "BRGCKR = 0x%08x, BRRA/BRRB = 0x%x/0x%x\n",
		adg->ckr, adg->rbga, adg->rbgb);
	dev_dbg(dev, "BRGA (for 44100 base) = %d\n", adg->rbga_rate_क्रम_441khz);
	dev_dbg(dev, "BRGB (for 48000 base) = %d\n", adg->rbgb_rate_क्रम_48khz);

	/*
	 * Actual CLKOUT will be exchanged in rsnd_adg_ssi_clk_try_start()
	 * by BRGCKR::BRGCKR_31
	 */
	क्रम_each_rsnd_clkout(clk, adg, i)
		dev_dbg(dev, "clkout %d : %pa : %ld\n", i,
			clk, clk_get_rate(clk));
पूर्ण
#अन्यथा
#घोषणा rsnd_adg_clk_dbg_info(priv, adg)
#पूर्ण_अगर

पूर्णांक rsnd_adg_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_adg *adg;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक ret;

	adg = devm_kzalloc(dev, माप(*adg), GFP_KERNEL);
	अगर (!adg)
		वापस -ENOMEM;

	ret = rsnd_mod_init(priv, &adg->mod, &adg_ops,
		      शून्य, 0, 0);
	अगर (ret)
		वापस ret;

	rsnd_adg_get_clkin(priv, adg);
	rsnd_adg_get_clkout(priv, adg);
	rsnd_adg_clk_dbg_info(priv, adg);

	priv->adg = adg;

	rsnd_adg_clk_enable(priv);

	वापस 0;
पूर्ण

व्योम rsnd_adg_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rsnd_adg *adg = priv->adg;
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम_each_rsnd_clkout(clk, adg, i)
		अगर (adg->clkout[i])
			clk_unरेजिस्टर_fixed_rate(adg->clkout[i]);

	of_clk_del_provider(np);

	rsnd_adg_clk_disable(priv);
पूर्ण
