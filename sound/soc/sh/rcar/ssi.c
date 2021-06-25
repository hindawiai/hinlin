<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car SSIU/SSI support
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
// Based on fsi.c
// Kuninori Morimoto <morimoto.kuninori@renesas.com>

/*
 * you can enable below define अगर you करोn't need
 * SSI पूर्णांकerrupt status debug message when debugging
 * see rsnd_dbg_irq_status()
 *
 * #घोषणा RSND_DEBUG_NO_IRQ_STATUS 1
 */

#समावेश <sound/simple_card_utils.h>
#समावेश <linux/delay.h>
#समावेश "rsnd.h"
#घोषणा RSND_SSI_NAME_SIZE 16

/*
 * SSICR
 */
#घोषणा	FORCE		(1u << 31)	/* Fixed */
#घोषणा	DMEN		(1u << 28)	/* DMA Enable */
#घोषणा	UIEN		(1u << 27)	/* Underflow Interrupt Enable */
#घोषणा	OIEN		(1u << 26)	/* Overflow Interrupt Enable */
#घोषणा	IIEN		(1u << 25)	/* Idle Mode Interrupt Enable */
#घोषणा	DIEN		(1u << 24)	/* Data Interrupt Enable */
#घोषणा	CHNL_4		(1u << 22)	/* Channels */
#घोषणा	CHNL_6		(2u << 22)	/* Channels */
#घोषणा	CHNL_8		(3u << 22)	/* Channels */
#घोषणा DWL_MASK	(7u << 19)	/* Data Word Length mask */
#घोषणा	DWL_8		(0u << 19)	/* Data Word Length */
#घोषणा	DWL_16		(1u << 19)	/* Data Word Length */
#घोषणा	DWL_18		(2u << 19)	/* Data Word Length */
#घोषणा	DWL_20		(3u << 19)	/* Data Word Length */
#घोषणा	DWL_22		(4u << 19)	/* Data Word Length */
#घोषणा	DWL_24		(5u << 19)	/* Data Word Length */
#घोषणा	DWL_32		(6u << 19)	/* Data Word Length */

/*
 * System word length
 */
#घोषणा	SWL_16		(1 << 16)	/* R/W System Word Length */
#घोषणा	SWL_24		(2 << 16)	/* R/W System Word Length */
#घोषणा	SWL_32		(3 << 16)	/* R/W System Word Length */

#घोषणा	SCKD		(1 << 15)	/* Serial Bit Clock Direction */
#घोषणा	SWSD		(1 << 14)	/* Serial WS Direction */
#घोषणा	SCKP		(1 << 13)	/* Serial Bit Clock Polarity */
#घोषणा	SWSP		(1 << 12)	/* Serial WS Polarity */
#घोषणा	SDTA		(1 << 10)	/* Serial Data Alignment */
#घोषणा	PDTA		(1 <<  9)	/* Parallel Data Alignment */
#घोषणा	DEL		(1 <<  8)	/* Serial Data Delay */
#घोषणा	CKDV(v)		(v <<  4)	/* Serial Clock Division Ratio */
#घोषणा	TRMD		(1 <<  1)	/* Transmit/Receive Mode Select */
#घोषणा	EN		(1 <<  0)	/* SSI Module Enable */

/*
 * SSISR
 */
#घोषणा	UIRQ		(1 << 27)	/* Underflow Error Interrupt Status */
#घोषणा	OIRQ		(1 << 26)	/* Overflow Error Interrupt Status */
#घोषणा	IIRQ		(1 << 25)	/* Idle Mode Interrupt Status */
#घोषणा	सूचीQ		(1 << 24)	/* Data Interrupt Status Flag */

/*
 * SSIWSR
 */
#घोषणा CONT		(1 << 8)	/* WS Continue Function */
#घोषणा WS_MODE		(1 << 0)	/* WS Mode */

#घोषणा SSI_NAME "ssi"

काष्ठा rsnd_ssi अणु
	काष्ठा rsnd_mod mod;

	u32 flags;
	u32 cr_own;
	u32 cr_clk;
	u32 cr_mode;
	u32 cr_en;
	u32 wsr;
	पूर्णांक chan;
	पूर्णांक rate;
	पूर्णांक irq;
	अचिन्हित पूर्णांक usrcnt;

	/* क्रम PIO */
	पूर्णांक byte_pos;
	पूर्णांक byte_per_period;
	पूर्णांक next_period_byte;
पूर्ण;

/* flags */
#घोषणा RSND_SSI_CLK_PIN_SHARE		(1 << 0)
#घोषणा RSND_SSI_NO_BUSIF		(1 << 1) /* SSI+DMA without BUSIF */
#घोषणा RSND_SSI_PROBED			(1 << 2)

#घोषणा क्रम_each_rsnd_ssi(pos, priv, i)					\
	क्रम (i = 0;							\
	     (i < rsnd_ssi_nr(priv)) &&					\
		((pos) = ((काष्ठा rsnd_ssi *)(priv)->ssi + i));		\
	     i++)

#घोषणा rsnd_ssi_get(priv, id) ((काष्ठा rsnd_ssi *)(priv->ssi) + id)
#घोषणा rsnd_ssi_nr(priv) ((priv)->ssi_nr)
#घोषणा rsnd_mod_to_ssi(_mod) container_of((_mod), काष्ठा rsnd_ssi, mod)
#घोषणा rsnd_ssi_is_parent(ssi, io) ((ssi) == rsnd_io_to_mod_ssip(io))
#घोषणा rsnd_ssi_is_multi_secondary(mod, io)				\
	(rsnd_ssi_multi_secondaries(io) & (1 << rsnd_mod_id(mod)))
#घोषणा rsnd_ssi_is_run_mods(mod, io) \
	(rsnd_ssi_run_mods(io) & (1 << rsnd_mod_id(mod)))
#घोषणा rsnd_ssi_can_output_clk(mod) (!__rsnd_ssi_is_pin_sharing(mod))

अटल पूर्णांक rsnd_ssi_is_dma_mode(काष्ठा rsnd_mod *mod);

पूर्णांक rsnd_ssi_use_busअगर(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_mod *mod = rsnd_io_to_mod_ssi(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	पूर्णांक use_busअगर = 0;

	अगर (!rsnd_ssi_is_dma_mode(mod))
		वापस 0;

	अगर (!(rsnd_flags_has(ssi, RSND_SSI_NO_BUSIF)))
		use_busअगर = 1;
	अगर (rsnd_io_to_mod_src(io))
		use_busअगर = 1;

	वापस use_busअगर;
पूर्ण

अटल व्योम rsnd_ssi_status_clear(काष्ठा rsnd_mod *mod)
अणु
	rsnd_mod_ग_लिखो(mod, SSISR, 0);
पूर्ण

अटल u32 rsnd_ssi_status_get(काष्ठा rsnd_mod *mod)
अणु
	वापस rsnd_mod_पढ़ो(mod, SSISR);
पूर्ण

अटल व्योम rsnd_ssi_status_check(काष्ठा rsnd_mod *mod,
				  u32 bit)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	u32 status;
	पूर्णांक i;

	क्रम (i = 0; i < 1024; i++) अणु
		status = rsnd_ssi_status_get(mod);
		अगर (status & bit)
			वापस;

		udelay(5);
	पूर्ण

	dev_warn(dev, "%s status check failed\n", rsnd_mod_name(mod));
पूर्ण

अटल u32 rsnd_ssi_multi_secondaries(काष्ठा rsnd_dai_stream *io)
अणु
	क्रमागत rsnd_mod_type types[] = अणु
		RSND_MOD_SSIM1,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM3,
	पूर्ण;
	पूर्णांक i, mask;

	mask = 0;
	क्रम (i = 0; i < ARRAY_SIZE(types); i++) अणु
		काष्ठा rsnd_mod *mod = rsnd_io_to_mod(io, types[i]);

		अगर (!mod)
			जारी;

		mask |= 1 << rsnd_mod_id(mod);
	पूर्ण

	वापस mask;
पूर्ण

अटल u32 rsnd_ssi_run_mods(काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_mod *ssi_mod = rsnd_io_to_mod_ssi(io);
	काष्ठा rsnd_mod *ssi_parent_mod = rsnd_io_to_mod_ssip(io);
	u32 mods;

	mods = rsnd_ssi_multi_secondaries_runसमय(io) |
		1 << rsnd_mod_id(ssi_mod);

	अगर (ssi_parent_mod)
		mods |= 1 << rsnd_mod_id(ssi_parent_mod);

	वापस mods;
पूर्ण

u32 rsnd_ssi_multi_secondaries_runसमय(काष्ठा rsnd_dai_stream *io)
अणु
	अगर (rsnd_runसमय_is_multi_ssi(io))
		वापस rsnd_ssi_multi_secondaries(io);

	वापस 0;
पूर्ण

अटल u32 rsnd_rdai_width_to_swl(काष्ठा rsnd_dai *rdai)
अणु
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक width = rsnd_rdai_width_get(rdai);

	चयन (width) अणु
	हाल 32: वापस SWL_32;
	हाल 24: वापस SWL_24;
	हाल 16: वापस SWL_16;
	पूर्ण

	dev_err(dev, "unsupported slot width value: %d\n", width);
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक rsnd_ssi_clk_query(काष्ठा rsnd_dai *rdai,
		       पूर्णांक param1, पूर्णांक param2, पूर्णांक *idx)
अणु
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	पूर्णांक ssi_clk_mul_table[] = अणु
		1, 2, 4, 8, 16, 6, 12,
	पूर्ण;
	पूर्णांक j, ret;
	अचिन्हित पूर्णांक मुख्य_rate;
	पूर्णांक width = rsnd_rdai_width_get(rdai);

	क्रम (j = 0; j < ARRAY_SIZE(ssi_clk_mul_table); j++) अणु

		/*
		 * It will set SSIWSR.CONT here, but SSICR.CKDV = 000
		 * with it is not allowed. (SSIWSR.WS_MODE with
		 * SSICR.CKDV = 000 is not allowed either).
		 * Skip it. See SSICR.CKDV
		 */
		अगर (j == 0)
			जारी;

		मुख्य_rate = width * param1 * param2 * ssi_clk_mul_table[j];

		ret = rsnd_adg_clk_query(priv, मुख्य_rate);
		अगर (ret < 0)
			जारी;

		अगर (idx)
			*idx = j;

		वापस मुख्य_rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_master_clk_start(काष्ठा rsnd_mod *mod,
				     काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	पूर्णांक chan = rsnd_runसमय_channel_क्रम_ssi(io);
	पूर्णांक idx, ret;
	अचिन्हित पूर्णांक मुख्य_rate;
	अचिन्हित पूर्णांक rate = rsnd_io_is_play(io) ?
		rsnd_src_get_out_rate(priv, io) :
		rsnd_src_get_in_rate(priv, io);

	अगर (!rsnd_rdai_is_clk_master(rdai))
		वापस 0;

	अगर (!rsnd_ssi_can_output_clk(mod))
		वापस 0;

	अगर (rsnd_ssi_is_multi_secondary(mod, io))
		वापस 0;

	अगर (rsnd_runसमय_is_tdm_split(io))
		chan = rsnd_io_converted_chan(io);

	chan = rsnd_channel_normalization(chan);

	अगर (ssi->usrcnt > 0) अणु
		अगर (ssi->rate != rate) अणु
			dev_err(dev, "SSI parent/child should use same rate\n");
			वापस -EINVAL;
		पूर्ण

		अगर (ssi->chan != chan) अणु
			dev_err(dev, "SSI parent/child should use same chan\n");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	मुख्य_rate = rsnd_ssi_clk_query(rdai, rate, chan, &idx);
	अगर (!मुख्य_rate) अणु
		dev_err(dev, "unsupported clock rate\n");
		वापस -EIO;
	पूर्ण

	ret = rsnd_adg_ssi_clk_try_start(mod, मुख्य_rate);
	अगर (ret < 0)
		वापस ret;

	/*
	 * SSI घड़ी will be output contiguously
	 * by below settings.
	 * This means, rsnd_ssi_master_clk_start()
	 * and rsnd_ssi_रेजिस्टर_setup() are necessary
	 * क्रम SSI parent
	 *
	 * SSICR  : FORCE, SCKD, SWSD
	 * SSIWSR : CONT
	 */
	ssi->cr_clk = FORCE | rsnd_rdai_width_to_swl(rdai) |
			SCKD | SWSD | CKDV(idx);
	ssi->wsr = CONT;
	ssi->rate = rate;
	ssi->chan = chan;

	dev_dbg(dev, "%s outputs %d chan %u Hz\n",
		rsnd_mod_name(mod), chan, rate);

	वापस 0;
पूर्ण

अटल व्योम rsnd_ssi_master_clk_stop(काष्ठा rsnd_mod *mod,
				     काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	अगर (!rsnd_rdai_is_clk_master(rdai))
		वापस;

	अगर (!rsnd_ssi_can_output_clk(mod))
		वापस;

	अगर (ssi->usrcnt > 1)
		वापस;

	ssi->cr_clk	= 0;
	ssi->rate	= 0;
	ssi->chan	= 0;

	rsnd_adg_ssi_clk_stop(mod);
पूर्ण

/* enable busअगर buffer over/under run पूर्णांकerrupt. */
#घोषणा rsnd_ssi_busअगर_err_irq_enable(mod)  rsnd_ssi_busअगर_err_irq_ctrl(mod, 1)
#घोषणा rsnd_ssi_busअगर_err_irq_disable(mod) rsnd_ssi_busअगर_err_irq_ctrl(mod, 0)
अटल व्योम rsnd_ssi_busअगर_err_irq_ctrl(काष्ठा rsnd_mod *mod, पूर्णांक enable)
अणु
	u32 sys_पूर्णांक_enable = 0;
	पूर्णांक id = rsnd_mod_id(mod);
	पूर्णांक i;

	चयन (id) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		क्रम (i = 0; i < 4; i++) अणु
			sys_पूर्णांक_enable = rsnd_mod_पढ़ो(mod, SSI_SYS_INT_ENABLE(i * 2));
			अगर (enable)
				sys_पूर्णांक_enable |= 0xf << (id * 4);
			अन्यथा
				sys_पूर्णांक_enable &= ~(0xf << (id * 4));
			rsnd_mod_ग_लिखो(mod,
				       SSI_SYS_INT_ENABLE(i * 2),
				       sys_पूर्णांक_enable);
		पूर्ण
		अवरोध;
	हाल 9:
		क्रम (i = 0; i < 4; i++) अणु
			sys_पूर्णांक_enable = rsnd_mod_पढ़ो(mod, SSI_SYS_INT_ENABLE((i * 2) + 1));
			अगर (enable)
				sys_पूर्णांक_enable |= 0xf << 4;
			अन्यथा
				sys_पूर्णांक_enable &= ~(0xf << 4);
			rsnd_mod_ग_लिखो(mod,
				       SSI_SYS_INT_ENABLE((i * 2) + 1),
				       sys_पूर्णांक_enable);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल bool rsnd_ssi_busअगर_err_status_clear(काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	u32 status;
	bool stop = false;
	पूर्णांक id = rsnd_mod_id(mod);
	पूर्णांक i;

	चयन (id) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		क्रम (i = 0; i < 4; i++) अणु
			status = rsnd_mod_पढ़ो(mod, SSI_SYS_STATUS(i * 2));
			status &= 0xf << (id * 4);

			अगर (status) अणु
				rsnd_dbg_irq_status(dev, "%s err status : 0x%08x\n",
						    rsnd_mod_name(mod), status);
				rsnd_mod_ग_लिखो(mod,
					       SSI_SYS_STATUS(i * 2),
					       0xf << (id * 4));
				stop = true;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 9:
		क्रम (i = 0; i < 4; i++) अणु
			status = rsnd_mod_पढ़ो(mod, SSI_SYS_STATUS((i * 2) + 1));
			status &= 0xf << 4;

			अगर (status) अणु
				rsnd_dbg_irq_status(dev, "%s err status : 0x%08x\n",
						    rsnd_mod_name(mod), status);
				rsnd_mod_ग_लिखो(mod,
					       SSI_SYS_STATUS((i * 2) + 1),
					       0xf << 4);
				stop = true;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस stop;
पूर्ण

अटल व्योम rsnd_ssi_config_init(काष्ठा rsnd_mod *mod,
				काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	u32 cr_own	= ssi->cr_own;
	u32 cr_mode	= ssi->cr_mode;
	u32 wsr		= ssi->wsr;
	पूर्णांक width;
	पूर्णांक is_tdm, is_tdm_split;

	is_tdm		= rsnd_runसमय_is_tdm(io);
	is_tdm_split	= rsnd_runसमय_is_tdm_split(io);

	अगर (is_tdm)
		dev_dbg(dev, "TDM mode\n");
	अगर (is_tdm_split)
		dev_dbg(dev, "TDM Split mode\n");

	cr_own |= FORCE | rsnd_rdai_width_to_swl(rdai);

	अगर (rdai->bit_clk_inv)
		cr_own |= SCKP;
	अगर (rdai->frm_clk_inv && !is_tdm)
		cr_own |= SWSP;
	अगर (rdai->data_alignment)
		cr_own |= SDTA;
	अगर (rdai->sys_delay)
		cr_own |= DEL;

	/*
	 * TDM Mode
	 * see
	 *	rsnd_ssiu_init_gen2()
	 */
	अगर (is_tdm || is_tdm_split) अणु
		wsr	|= WS_MODE;
		cr_own	|= CHNL_8;
	पूर्ण

	/*
	 * We shouldn't exchange SWSP after running.
	 * This means, parent needs to care it.
	 */
	अगर (rsnd_ssi_is_parent(mod, io))
		जाओ init_end;

	अगर (rsnd_io_is_play(io))
		cr_own |= TRMD;

	cr_own &= ~DWL_MASK;
	width = snd_pcm_क्रमmat_width(runसमय->क्रमmat);
	अगर (is_tdm_split) अणु
		/*
		 * The SWL and DWL bits in SSICR should be fixed at 32-bit
		 * setting when TDM split mode.
		 * see datasheet
		 *	Operation :: TDM Format Split Function (TDM Split Mode)
		 */
		width = 32;
	पूर्ण

	चयन (width) अणु
	हाल 8:
		cr_own |= DWL_8;
		अवरोध;
	हाल 16:
		cr_own |= DWL_16;
		अवरोध;
	हाल 24:
		cr_own |= DWL_24;
		अवरोध;
	हाल 32:
		cr_own |= DWL_32;
		अवरोध;
	पूर्ण

	अगर (rsnd_ssi_is_dma_mode(mod)) अणु
		cr_mode = UIEN | OIEN |	/* over/under run */
			  DMEN;		/* DMA : enable DMA */
	पूर्ण अन्यथा अणु
		cr_mode = DIEN;		/* PIO : enable Data पूर्णांकerrupt */
	पूर्ण

	/* enable busअगर buffer over/under run पूर्णांकerrupt. */
	अगर (is_tdm || is_tdm_split)
		rsnd_ssi_busअगर_err_irq_enable(mod);

init_end:
	ssi->cr_own	= cr_own;
	ssi->cr_mode	= cr_mode;
	ssi->wsr	= wsr;
पूर्ण

अटल व्योम rsnd_ssi_रेजिस्टर_setup(काष्ठा rsnd_mod *mod)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	rsnd_mod_ग_लिखो(mod, SSIWSR,	ssi->wsr);
	rsnd_mod_ग_लिखो(mod, SSICR,	ssi->cr_own	|
					ssi->cr_clk	|
					ssi->cr_mode	|
					ssi->cr_en);
पूर्ण

/*
 *	SSI mod common functions
 */
अटल पूर्णांक rsnd_ssi_init(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	पूर्णांक ret;

	अगर (!rsnd_ssi_is_run_mods(mod, io))
		वापस 0;

	ret = rsnd_ssi_master_clk_start(mod, io);
	अगर (ret < 0)
		वापस ret;

	ssi->usrcnt++;

	rsnd_mod_घातer_on(mod);

	rsnd_ssi_config_init(mod, io);

	rsnd_ssi_रेजिस्टर_setup(mod);

	/* clear error status */
	rsnd_ssi_status_clear(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_quit(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक is_tdm, is_tdm_split;

	is_tdm		= rsnd_runसमय_is_tdm(io);
	is_tdm_split	= rsnd_runसमय_is_tdm_split(io);

	अगर (!rsnd_ssi_is_run_mods(mod, io))
		वापस 0;

	अगर (!ssi->usrcnt) अणु
		dev_err(dev, "%s usrcnt error\n", rsnd_mod_name(mod));
		वापस -EIO;
	पूर्ण

	rsnd_ssi_master_clk_stop(mod, io);

	rsnd_mod_घातer_off(mod);

	ssi->usrcnt--;

	अगर (!ssi->usrcnt) अणु
		ssi->cr_own	= 0;
		ssi->cr_mode	= 0;
		ssi->wsr	= 0;
	पूर्ण

	/* disable busअगर buffer over/under run पूर्णांकerrupt. */
	अगर (is_tdm || is_tdm_split)
		rsnd_ssi_busअगर_err_irq_disable(mod);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_hw_params(काष्ठा rsnd_mod *mod,
			      काष्ठा rsnd_dai_stream *io,
			      काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	अचिन्हित पूर्णांक fmt_width = snd_pcm_क्रमmat_width(params_क्रमmat(params));

	अगर (fmt_width > rdai->chan_width) अणु
		काष्ठा rsnd_priv *priv = rsnd_io_to_priv(io);
		काष्ठा device *dev = rsnd_priv_to_dev(priv);

		dev_err(dev, "invalid combination of slot-width and format-data-width\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_start(काष्ठा rsnd_mod *mod,
			  काष्ठा rsnd_dai_stream *io,
			  काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	अगर (!rsnd_ssi_is_run_mods(mod, io))
		वापस 0;

	/*
	 * EN will be set via SSIU :: SSI_CONTROL
	 * अगर Multi channel mode
	 */
	अगर (rsnd_ssi_multi_secondaries_runसमय(io))
		वापस 0;

	/*
	 * EN is क्रम data output.
	 * SSI parent EN is not needed.
	 */
	अगर (rsnd_ssi_is_parent(mod, io))
		वापस 0;

	ssi->cr_en = EN;

	rsnd_mod_ग_लिखो(mod, SSICR,	ssi->cr_own	|
					ssi->cr_clk	|
					ssi->cr_mode	|
					ssi->cr_en);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_stop(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	u32 cr;

	अगर (!rsnd_ssi_is_run_mods(mod, io))
		वापस 0;

	अगर (rsnd_ssi_is_parent(mod, io))
		वापस 0;

	cr  =	ssi->cr_own	|
		ssi->cr_clk;

	/*
	 * disable all IRQ,
	 * Playback: Wait all data was sent
	 * Capture:  It might not receave data. Do nothing
	 */
	अगर (rsnd_io_is_play(io)) अणु
		rsnd_mod_ग_लिखो(mod, SSICR, cr | ssi->cr_en);
		rsnd_ssi_status_check(mod, सूचीQ);
	पूर्ण

	/* In multi-SSI mode, stop is perक्रमmed by setting ssi0129 in
	 * SSI_CONTROL to 0 (in rsnd_ssio_stop_gen2). Do nothing here.
	 */
	अगर (rsnd_ssi_multi_secondaries_runसमय(io))
		वापस 0;

	/*
	 * disable SSI,
	 * and, रुको idle state
	 */
	rsnd_mod_ग_लिखो(mod, SSICR, cr);	/* disabled all */
	rsnd_ssi_status_check(mod, IIRQ);

	ssi->cr_en = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_irq(काष्ठा rsnd_mod *mod,
			काष्ठा rsnd_dai_stream *io,
			काष्ठा rsnd_priv *priv,
			पूर्णांक enable)
अणु
	u32 val = 0;
	पूर्णांक is_tdm, is_tdm_split;
	पूर्णांक id = rsnd_mod_id(mod);

	is_tdm		= rsnd_runसमय_is_tdm(io);
	is_tdm_split	= rsnd_runसमय_is_tdm_split(io);

	अगर (rsnd_is_gen1(priv))
		वापस 0;

	अगर (rsnd_ssi_is_parent(mod, io))
		वापस 0;

	अगर (!rsnd_ssi_is_run_mods(mod, io))
		वापस 0;

	अगर (enable)
		val = rsnd_ssi_is_dma_mode(mod) ? 0x0e000000 : 0x0f000000;

	अगर (is_tdm || is_tdm_split) अणु
		चयन (id) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 9:
			val |= 0x0000ff00;
			अवरोध;
		पूर्ण
	पूर्ण

	rsnd_mod_ग_लिखो(mod, SSI_INT_ENABLE, val);

	वापस 0;
पूर्ण

अटल bool rsnd_ssi_pio_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
				   काष्ठा rsnd_dai_stream *io);
अटल व्योम __rsnd_ssi_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
				 काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	पूर्णांक is_dma = rsnd_ssi_is_dma_mode(mod);
	u32 status;
	bool elapsed = false;
	bool stop = false;
	पूर्णांक is_tdm, is_tdm_split;

	is_tdm		= rsnd_runसमय_is_tdm(io);
	is_tdm_split	= rsnd_runसमय_is_tdm_split(io);

	spin_lock(&priv->lock);

	/* ignore all हालs अगर not working */
	अगर (!rsnd_io_is_working(io))
		जाओ rsnd_ssi_पूर्णांकerrupt_out;

	status = rsnd_ssi_status_get(mod);

	/* PIO only */
	अगर (!is_dma && (status & सूचीQ))
		elapsed = rsnd_ssi_pio_पूर्णांकerrupt(mod, io);

	/* DMA only */
	अगर (is_dma && (status & (UIRQ | OIRQ))) अणु
		rsnd_dbg_irq_status(dev, "%s err status : 0x%08x\n",
			rsnd_mod_name(mod), status);

		stop = true;
	पूर्ण

	अगर (is_tdm || is_tdm_split)
		stop |= rsnd_ssi_busअगर_err_status_clear(mod);

	rsnd_ssi_status_clear(mod);
rsnd_ssi_पूर्णांकerrupt_out:
	spin_unlock(&priv->lock);

	अगर (elapsed)
		rsnd_dai_period_elapsed(io);

	अगर (stop)
		snd_pcm_stop_xrun(io->substream);

पूर्ण

अटल irqवापस_t rsnd_ssi_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rsnd_mod *mod = data;

	rsnd_mod_पूर्णांकerrupt(mod, __rsnd_ssi_पूर्णांकerrupt);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 *rsnd_ssi_get_status(काष्ठा rsnd_mod *mod,
				काष्ठा rsnd_dai_stream *io,
				क्रमागत rsnd_mod_type type)
अणु
	/*
	 * SSIP (= SSI parent) needs to be special, otherwise,
	 * 2nd SSI might करोesn't start. see also rsnd_mod_call()
	 *
	 * We can't include parent SSI status on SSI, because we don't know
	 * how many SSI requests parent SSI. Thus, it is localed on "io" now.
	 * ex) trouble हाल
	 *	Playback: SSI0
	 *	Capture : SSI1 (needs SSI0)
	 *
	 * 1) start Capture  ->	SSI0/SSI1 are started.
	 * 2) start Playback ->	SSI0 करोesn't work, because it is alपढ़ोy
	 *			marked as "started" on 1)
	 *
	 * OTOH, using each mod's status is good क्रम MUX हाल.
	 * It करोesn't need to start in 2nd start
	 * ex)
	 *	IO-0: SRC0 -> CTU1 -+-> MUX -> DVC -> SSIU -> SSI0
	 *			    |
	 *	IO-1: SRC1 -> CTU2 -+
	 *
	 * 1) start IO-0 ->	start SSI0
	 * 2) start IO-1 ->	SSI0 करोesn't need to start, because it is
	 *			alपढ़ोy started on 1)
	 */
	अगर (type == RSND_MOD_SSIP)
		वापस &io->parent_ssi_status;

	वापस rsnd_mod_get_status(mod, io, type);
पूर्ण

/*
 *		SSI PIO
 */
अटल व्योम rsnd_ssi_parent_attach(काष्ठा rsnd_mod *mod,
				   काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);

	अगर (!__rsnd_ssi_is_pin_sharing(mod))
		वापस;

	अगर (!rsnd_rdai_is_clk_master(rdai))
		वापस;

	अगर (rsnd_ssi_is_multi_secondary(mod, io))
		वापस;

	चयन (rsnd_mod_id(mod)) अणु
	हाल 1:
	हाल 2:
	हाल 9:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 0), io, RSND_MOD_SSIP);
		अवरोध;
	हाल 4:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 3), io, RSND_MOD_SSIP);
		अवरोध;
	हाल 8:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 7), io, RSND_MOD_SSIP);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rsnd_ssi_pcm_new(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	/*
	 * rsnd_rdai_is_clk_master() will be enabled after set_fmt,
	 * and, pcm_new will be called after it.
	 * This function reuse pcm_new at this poपूर्णांक.
	 */
	rsnd_ssi_parent_attach(mod, io);

	वापस 0;
पूर्ण

अटल पूर्णांक rsnd_ssi_common_probe(काष्ठा rsnd_mod *mod,
				 काष्ठा rsnd_dai_stream *io,
				 काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	पूर्णांक ret = 0;

	/*
	 * SSIP/SSIU/IRQ are not needed on
	 * SSI Multi secondaries
	 */
	अगर (rsnd_ssi_is_multi_secondary(mod, io))
		वापस 0;

	/*
	 * It can't judge ssi parent at this poपूर्णांक
	 * see rsnd_ssi_pcm_new()
	 */

	/*
	 * SSI might be called again as PIO fallback
	 * It is easy to manual handling क्रम IRQ request/मुक्त
	 *
	 * OTOH, this function might be called many बार अगर platक्रमm is
	 * using MIX. It needs xxx_attach() many बार on xxx_probe().
	 * Because of it, we can't control .probe/.हटाओ calling count by
	 * mod->status.
	 * But it करोn't need to call request_irq() many बार.
	 * Let's control it by RSND_SSI_PROBED flag.
	 */
	अगर (!rsnd_flags_has(ssi, RSND_SSI_PROBED)) अणु
		ret = request_irq(ssi->irq,
				  rsnd_ssi_पूर्णांकerrupt,
				  IRQF_SHARED,
				  dev_name(dev), mod);

		rsnd_flags_set(ssi, RSND_SSI_PROBED);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_ssi_common_हटाओ(काष्ठा rsnd_mod *mod,
				  काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	काष्ठा rsnd_mod *pure_ssi_mod = rsnd_io_to_mod_ssi(io);

	/* Do nothing अगर non SSI (= SSI parent, multi SSI) mod */
	अगर (pure_ssi_mod != mod)
		वापस 0;

	/* PIO will request IRQ again */
	अगर (rsnd_flags_has(ssi, RSND_SSI_PROBED)) अणु
		मुक्त_irq(ssi->irq, mod);

		rsnd_flags_del(ssi, RSND_SSI_PROBED);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	SSI PIO functions
 */
अटल bool rsnd_ssi_pio_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
				   काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	u32 *buf = (u32 *)(runसमय->dma_area + ssi->byte_pos);
	पूर्णांक shअगरt = 0;
	पूर्णांक byte_pos;
	bool elapsed = false;

	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 24)
		shअगरt = 8;

	/*
	 * 8/16/32 data can be assesse to TDR/RDR रेजिस्टर
	 * directly as 32bit data
	 * see rsnd_ssi_init()
	 */
	अगर (rsnd_io_is_play(io))
		rsnd_mod_ग_लिखो(mod, SSITDR, (*buf) << shअगरt);
	अन्यथा
		*buf = (rsnd_mod_पढ़ो(mod, SSIRDR) >> shअगरt);

	byte_pos = ssi->byte_pos + माप(*buf);

	अगर (byte_pos >= ssi->next_period_byte) अणु
		पूर्णांक period_pos = byte_pos / ssi->byte_per_period;

		अगर (period_pos >= runसमय->periods) अणु
			byte_pos = 0;
			period_pos = 0;
		पूर्ण

		ssi->next_period_byte = (period_pos + 1) * ssi->byte_per_period;

		elapsed = true;
	पूर्ण

	WRITE_ONCE(ssi->byte_pos, byte_pos);

	वापस elapsed;
पूर्ण

अटल पूर्णांक rsnd_ssi_pio_init(काष्ठा rsnd_mod *mod,
			     काष्ठा rsnd_dai_stream *io,
			     काष्ठा rsnd_priv *priv)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	अगर (!rsnd_ssi_is_parent(mod, io)) अणु
		ssi->byte_pos		= 0;
		ssi->byte_per_period	= runसमय->period_size *
					  runसमय->channels *
					  samples_to_bytes(runसमय, 1);
		ssi->next_period_byte	= ssi->byte_per_period;
	पूर्ण

	वापस rsnd_ssi_init(mod, io, priv);
पूर्ण

अटल पूर्णांक rsnd_ssi_pio_poपूर्णांकer(काष्ठा rsnd_mod *mod,
			    काष्ठा rsnd_dai_stream *io,
			    snd_pcm_uframes_t *poपूर्णांकer)
अणु
	काष्ठा rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	काष्ठा snd_pcm_runसमय *runसमय = rsnd_io_to_runसमय(io);

	*poपूर्णांकer = bytes_to_frames(runसमय, READ_ONCE(ssi->byte_pos));

	वापस 0;
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_ssi_pio_ops = अणु
	.name		= SSI_NAME,
	.probe		= rsnd_ssi_common_probe,
	.हटाओ		= rsnd_ssi_common_हटाओ,
	.init		= rsnd_ssi_pio_init,
	.quit		= rsnd_ssi_quit,
	.start		= rsnd_ssi_start,
	.stop		= rsnd_ssi_stop,
	.irq		= rsnd_ssi_irq,
	.poपूर्णांकer	= rsnd_ssi_pio_poपूर्णांकer,
	.pcm_new	= rsnd_ssi_pcm_new,
	.hw_params	= rsnd_ssi_hw_params,
	.get_status	= rsnd_ssi_get_status,
पूर्ण;

अटल पूर्णांक rsnd_ssi_dma_probe(काष्ठा rsnd_mod *mod,
			      काष्ठा rsnd_dai_stream *io,
			      काष्ठा rsnd_priv *priv)
अणु
	पूर्णांक ret;

	/*
	 * SSIP/SSIU/IRQ/DMA are not needed on
	 * SSI Multi secondaries
	 */
	अगर (rsnd_ssi_is_multi_secondary(mod, io))
		वापस 0;

	ret = rsnd_ssi_common_probe(mod, io, priv);
	अगर (ret)
		वापस ret;

	/* SSI probe might be called many बार in MUX multi path */
	ret = rsnd_dma_attach(io, mod, &io->dma);

	वापस ret;
पूर्ण

अटल पूर्णांक rsnd_ssi_fallback(काष्ठा rsnd_mod *mod,
			     काष्ठा rsnd_dai_stream *io,
			     काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);

	/*
	 * fallback to PIO
	 *
	 * SSI .probe might be called again.
	 * see
	 *	rsnd_rdai_continuance_probe()
	 */
	mod->ops = &rsnd_ssi_pio_ops;

	dev_info(dev, "%s fallback to PIO mode\n", rsnd_mod_name(mod));

	वापस 0;
पूर्ण

अटल काष्ठा dma_chan *rsnd_ssi_dma_req(काष्ठा rsnd_dai_stream *io,
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
	 *	rsnd_ssiu_dma_req()
	 *	rsnd_dma_of_path()
	 */

	अगर (rsnd_ssi_use_busअगर(io))
		name = is_play ? "rxu" : "txu";
	अन्यथा
		name = is_play ? "rx" : "tx";

	वापस rsnd_dma_request_channel(rsnd_ssi_of_node(priv),
					mod, name);
पूर्ण

अटल काष्ठा rsnd_mod_ops rsnd_ssi_dma_ops = अणु
	.name		= SSI_NAME,
	.dma_req	= rsnd_ssi_dma_req,
	.probe		= rsnd_ssi_dma_probe,
	.हटाओ		= rsnd_ssi_common_हटाओ,
	.init		= rsnd_ssi_init,
	.quit		= rsnd_ssi_quit,
	.start		= rsnd_ssi_start,
	.stop		= rsnd_ssi_stop,
	.irq		= rsnd_ssi_irq,
	.pcm_new	= rsnd_ssi_pcm_new,
	.fallback	= rsnd_ssi_fallback,
	.hw_params	= rsnd_ssi_hw_params,
	.get_status	= rsnd_ssi_get_status,
पूर्ण;

अटल पूर्णांक rsnd_ssi_is_dma_mode(काष्ठा rsnd_mod *mod)
अणु
	वापस mod->ops == &rsnd_ssi_dma_ops;
पूर्ण

/*
 *		ssi mod function
 */
अटल व्योम rsnd_ssi_connect(काष्ठा rsnd_mod *mod,
			     काष्ठा rsnd_dai_stream *io)
अणु
	काष्ठा rsnd_dai *rdai = rsnd_io_to_rdai(io);
	क्रमागत rsnd_mod_type types[] = अणु
		RSND_MOD_SSI,
		RSND_MOD_SSIM1,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM3,
	पूर्ण;
	क्रमागत rsnd_mod_type type;
	पूर्णांक i;

	/* try SSI -> SSIM1 -> SSIM2 -> SSIM3 */
	क्रम (i = 0; i < ARRAY_SIZE(types); i++) अणु
		type = types[i];
		अगर (!rsnd_io_to_mod(io, type)) अणु
			rsnd_dai_connect(mod, io, type);
			rsnd_rdai_channels_set(rdai, (i + 1) * 2);
			rsnd_rdai_ssi_lane_set(rdai, (i + 1));
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rsnd_parse_connect_ssi(काष्ठा rsnd_dai *rdai,
			    काष्ठा device_node *playback,
			    काष्ठा device_node *capture)
अणु
	काष्ठा rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	पूर्णांक i;

	node = rsnd_ssi_of_node(priv);
	अगर (!node)
		वापस;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		काष्ठा rsnd_mod *mod = rsnd_ssi_mod_get(priv, i);

		अगर (np == playback)
			rsnd_ssi_connect(mod, &rdai->playback);
		अगर (np == capture)
			rsnd_ssi_connect(mod, &rdai->capture);
		i++;
	पूर्ण

	of_node_put(node);
पूर्ण

काष्ठा rsnd_mod *rsnd_ssi_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id)
अणु
	अगर (WARN_ON(id < 0 || id >= rsnd_ssi_nr(priv)))
		id = 0;

	वापस rsnd_mod_get(rsnd_ssi_get(priv, id));
पूर्ण

पूर्णांक __rsnd_ssi_is_pin_sharing(काष्ठा rsnd_mod *mod)
अणु
	अगर (!mod)
		वापस 0;

	वापस !!(rsnd_flags_has(rsnd_mod_to_ssi(mod), RSND_SSI_CLK_PIN_SHARE));
पूर्ण

पूर्णांक rsnd_ssi_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device_node *node;
	काष्ठा device_node *np;
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_mod_ops *ops;
	काष्ठा clk *clk;
	काष्ठा rsnd_ssi *ssi;
	अक्षर name[RSND_SSI_NAME_SIZE];
	पूर्णांक i, nr, ret;

	node = rsnd_ssi_of_node(priv);
	अगर (!node)
		वापस -EINVAL;

	nr = of_get_child_count(node);
	अगर (!nr) अणु
		ret = -EINVAL;
		जाओ rsnd_ssi_probe_करोne;
	पूर्ण

	ssi	= devm_kसुस्मृति(dev, nr, माप(*ssi), GFP_KERNEL);
	अगर (!ssi) अणु
		ret = -ENOMEM;
		जाओ rsnd_ssi_probe_करोne;
	पूर्ण

	priv->ssi	= ssi;
	priv->ssi_nr	= nr;

	i = 0;
	क्रम_each_child_of_node(node, np) अणु
		अगर (!of_device_is_available(np))
			जाओ skip;

		ssi = rsnd_ssi_get(priv, i);

		snम_लिखो(name, RSND_SSI_NAME_SIZE, "%s.%d",
			 SSI_NAME, i);

		clk = devm_clk_get(dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			of_node_put(np);
			जाओ rsnd_ssi_probe_करोne;
		पूर्ण

		अगर (of_get_property(np, "shared-pin", शून्य))
			rsnd_flags_set(ssi, RSND_SSI_CLK_PIN_SHARE);

		अगर (of_get_property(np, "no-busif", शून्य))
			rsnd_flags_set(ssi, RSND_SSI_NO_BUSIF);

		ssi->irq = irq_of_parse_and_map(np, 0);
		अगर (!ssi->irq) अणु
			ret = -EINVAL;
			of_node_put(np);
			जाओ rsnd_ssi_probe_करोne;
		पूर्ण

		अगर (of_property_पढ़ो_bool(np, "pio-transfer"))
			ops = &rsnd_ssi_pio_ops;
		अन्यथा
			ops = &rsnd_ssi_dma_ops;

		ret = rsnd_mod_init(priv, rsnd_mod_get(ssi), ops, clk,
				    RSND_MOD_SSI, i);
		अगर (ret) अणु
			of_node_put(np);
			जाओ rsnd_ssi_probe_करोne;
		पूर्ण
skip:
		i++;
	पूर्ण

	ret = 0;

rsnd_ssi_probe_करोne:
	of_node_put(node);

	वापस ret;
पूर्ण

व्योम rsnd_ssi_हटाओ(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा rsnd_ssi *ssi;
	पूर्णांक i;

	क्रम_each_rsnd_ssi(ssi, priv, i) अणु
		rsnd_mod_quit(rsnd_mod_get(ssi));
	पूर्ण
पूर्ण
