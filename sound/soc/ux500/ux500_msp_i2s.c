<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Roger Nilsson <roger.xr.nilsson@stericsson.com>,
 *         Sandeep Kaushik <sandeep.kaushik@st.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/asoc-ux500-msp.h>

#समावेश <sound/soc.h>

#समावेश "ux500_msp_i2s.h"

 /* Protocol desciptors */
अटल स्थिर काष्ठा msp_protdesc prot_descs[] = अणु
	अणु /* I2S */
		MSP_SINGLE_PHASE,
		MSP_SINGLE_PHASE,
		MSP_PHASE2_START_MODE_IMEDIATE,
		MSP_PHASE2_START_MODE_IMEDIATE,
		MSP_BTF_MS_BIT_FIRST,
		MSP_BTF_MS_BIT_FIRST,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_ELEM_LEN_32,
		MSP_ELEM_LEN_32,
		MSP_ELEM_LEN_32,
		MSP_ELEM_LEN_32,
		MSP_DELAY_1,
		MSP_DELAY_1,
		MSP_RISING_EDGE,
		MSP_FALLING_EDGE,
		MSP_FSYNC_POL_ACT_LO,
		MSP_FSYNC_POL_ACT_LO,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPRESS_MODE_LINEAR,
		MSP_EXPAND_MODE_LINEAR,
		MSP_FSYNC_IGNORE,
		31,
		15,
		32,
	पूर्ण, अणु /* PCM */
		MSP_DUAL_PHASE,
		MSP_DUAL_PHASE,
		MSP_PHASE2_START_MODE_FSYNC,
		MSP_PHASE2_START_MODE_FSYNC,
		MSP_BTF_MS_BIT_FIRST,
		MSP_BTF_MS_BIT_FIRST,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_ELEM_LEN_16,
		MSP_ELEM_LEN_16,
		MSP_ELEM_LEN_16,
		MSP_ELEM_LEN_16,
		MSP_DELAY_0,
		MSP_DELAY_0,
		MSP_RISING_EDGE,
		MSP_FALLING_EDGE,
		MSP_FSYNC_POL_ACT_HI,
		MSP_FSYNC_POL_ACT_HI,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPRESS_MODE_LINEAR,
		MSP_EXPAND_MODE_LINEAR,
		MSP_FSYNC_IGNORE,
		255,
		0,
		256,
	पूर्ण, अणु /* Companded PCM */
		MSP_SINGLE_PHASE,
		MSP_SINGLE_PHASE,
		MSP_PHASE2_START_MODE_FSYNC,
		MSP_PHASE2_START_MODE_FSYNC,
		MSP_BTF_MS_BIT_FIRST,
		MSP_BTF_MS_BIT_FIRST,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_FRAME_LEN_1,
		MSP_ELEM_LEN_8,
		MSP_ELEM_LEN_8,
		MSP_ELEM_LEN_8,
		MSP_ELEM_LEN_8,
		MSP_DELAY_0,
		MSP_DELAY_0,
		MSP_RISING_EDGE,
		MSP_RISING_EDGE,
		MSP_FSYNC_POL_ACT_HI,
		MSP_FSYNC_POL_ACT_HI,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPRESS_MODE_LINEAR,
		MSP_EXPAND_MODE_LINEAR,
		MSP_FSYNC_IGNORE,
		255,
		0,
		256,
	पूर्ण,
पूर्ण;

अटल व्योम set_prot_desc_tx(काष्ठा ux500_msp *msp,
			काष्ठा msp_protdesc *protdesc,
			क्रमागत msp_data_size data_size)
अणु
	u32 temp_reg = 0;

	temp_reg |= MSP_P2_ENABLE_BIT(protdesc->tx_phase_mode);
	temp_reg |= MSP_P2_START_MODE_BIT(protdesc->tx_phase2_start_mode);
	temp_reg |= MSP_P1_FRAME_LEN_BITS(protdesc->tx_frame_len_1);
	temp_reg |= MSP_P2_FRAME_LEN_BITS(protdesc->tx_frame_len_2);
	अगर (msp->def_elem_len) अणु
		temp_reg |= MSP_P1_ELEM_LEN_BITS(protdesc->tx_elem_len_1);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(protdesc->tx_elem_len_2);
	पूर्ण अन्यथा अणु
		temp_reg |= MSP_P1_ELEM_LEN_BITS(data_size);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(data_size);
	पूर्ण
	temp_reg |= MSP_DATA_DELAY_BITS(protdesc->tx_data_delay);
	temp_reg |= MSP_SET_ENDIANNES_BIT(protdesc->tx_byte_order);
	temp_reg |= MSP_FSYNC_POL(protdesc->tx_fsync_pol);
	temp_reg |= MSP_DATA_WORD_SWAP(protdesc->tx_half_word_swap);
	temp_reg |= MSP_SET_COMPANDING_MODE(protdesc->compression_mode);
	temp_reg |= MSP_SET_FSYNC_IGNORE(protdesc->frame_sync_ignore);

	ग_लिखोl(temp_reg, msp->रेजिस्टरs + MSP_TCF);
पूर्ण

अटल व्योम set_prot_desc_rx(काष्ठा ux500_msp *msp,
			काष्ठा msp_protdesc *protdesc,
			क्रमागत msp_data_size data_size)
अणु
	u32 temp_reg = 0;

	temp_reg |= MSP_P2_ENABLE_BIT(protdesc->rx_phase_mode);
	temp_reg |= MSP_P2_START_MODE_BIT(protdesc->rx_phase2_start_mode);
	temp_reg |= MSP_P1_FRAME_LEN_BITS(protdesc->rx_frame_len_1);
	temp_reg |= MSP_P2_FRAME_LEN_BITS(protdesc->rx_frame_len_2);
	अगर (msp->def_elem_len) अणु
		temp_reg |= MSP_P1_ELEM_LEN_BITS(protdesc->rx_elem_len_1);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(protdesc->rx_elem_len_2);
	पूर्ण अन्यथा अणु
		temp_reg |= MSP_P1_ELEM_LEN_BITS(data_size);
		temp_reg |= MSP_P2_ELEM_LEN_BITS(data_size);
	पूर्ण

	temp_reg |= MSP_DATA_DELAY_BITS(protdesc->rx_data_delay);
	temp_reg |= MSP_SET_ENDIANNES_BIT(protdesc->rx_byte_order);
	temp_reg |= MSP_FSYNC_POL(protdesc->rx_fsync_pol);
	temp_reg |= MSP_DATA_WORD_SWAP(protdesc->rx_half_word_swap);
	temp_reg |= MSP_SET_COMPANDING_MODE(protdesc->expansion_mode);
	temp_reg |= MSP_SET_FSYNC_IGNORE(protdesc->frame_sync_ignore);

	ग_लिखोl(temp_reg, msp->रेजिस्टरs + MSP_RCF);
पूर्ण

अटल पूर्णांक configure_protocol(काष्ठा ux500_msp *msp,
			काष्ठा ux500_msp_config *config)
अणु
	काष्ठा msp_protdesc *protdesc;
	क्रमागत msp_data_size data_size;
	u32 temp_reg = 0;

	data_size = config->data_size;
	msp->def_elem_len = config->def_elem_len;
	अगर (config->शेष_protdesc == 1) अणु
		अगर (config->protocol >= MSP_INVALID_PROTOCOL) अणु
			dev_err(msp->dev, "%s: ERROR: Invalid protocol!\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		protdesc =
		    (काष्ठा msp_protdesc *)&prot_descs[config->protocol];
	पूर्ण अन्यथा अणु
		protdesc = (काष्ठा msp_protdesc *)&config->protdesc;
	पूर्ण

	अगर (data_size < MSP_DATA_BITS_DEFAULT || data_size > MSP_DATA_BITS_32) अणु
		dev_err(msp->dev,
			"%s: ERROR: Invalid data-size requested (data_size = %d)!\n",
			__func__, data_size);
		वापस -EINVAL;
	पूर्ण

	अगर (config->direction & MSP_सूची_TX)
		set_prot_desc_tx(msp, protdesc, data_size);
	अगर (config->direction & MSP_सूची_RX)
		set_prot_desc_rx(msp, protdesc, data_size);

	/* The code below should not be separated. */
	temp_reg = पढ़ोl(msp->रेजिस्टरs + MSP_GCR) & ~TX_CLK_POL_RISING;
	temp_reg |= MSP_TX_CLKPOL_BIT(~protdesc->tx_clk_pol);
	ग_लिखोl(temp_reg, msp->रेजिस्टरs + MSP_GCR);
	temp_reg = पढ़ोl(msp->रेजिस्टरs + MSP_GCR) & ~RX_CLK_POL_RISING;
	temp_reg |= MSP_RX_CLKPOL_BIT(protdesc->rx_clk_pol);
	ग_लिखोl(temp_reg, msp->रेजिस्टरs + MSP_GCR);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_bitclk(काष्ठा ux500_msp *msp, काष्ठा ux500_msp_config *config)
अणु
	u32 reg_val_GCR;
	u32 frame_per = 0;
	u32 sck_भाग = 0;
	u32 frame_width = 0;
	u32 temp_reg = 0;
	काष्ठा msp_protdesc *protdesc = शून्य;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR & ~SRG_ENABLE, msp->रेजिस्टरs + MSP_GCR);

	अगर (config->शेष_protdesc)
		protdesc =
			(काष्ठा msp_protdesc *)&prot_descs[config->protocol];
	अन्यथा
		protdesc = (काष्ठा msp_protdesc *)&config->protdesc;

	चयन (config->protocol) अणु
	हाल MSP_PCM_PROTOCOL:
	हाल MSP_PCM_COMPAND_PROTOCOL:
		frame_width = protdesc->frame_width;
		sck_भाग = config->f_inअ_दोlk / (config->frame_freq *
			(protdesc->घड़ीs_per_frame));
		frame_per = protdesc->frame_period;
		अवरोध;
	हाल MSP_I2S_PROTOCOL:
		frame_width = protdesc->frame_width;
		sck_भाग = config->f_inअ_दोlk / (config->frame_freq *
			(protdesc->घड़ीs_per_frame));
		frame_per = protdesc->frame_period;
		अवरोध;
	शेष:
		dev_err(msp->dev, "%s: ERROR: Unknown protocol (%d)!\n",
			__func__,
			config->protocol);
		वापस -EINVAL;
	पूर्ण

	temp_reg = (sck_भाग - 1) & SCK_DIV_MASK;
	temp_reg |= FRAME_WIDTH_BITS(frame_width);
	temp_reg |= FRAME_PERIOD_BITS(frame_per);
	ग_लिखोl(temp_reg, msp->रेजिस्टरs + MSP_SRG);

	msp->f_bitclk = (config->f_inअ_दोlk)/(sck_भाग + 1);

	/* Enable bit-घड़ी */
	udelay(100);
	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR | SRG_ENABLE, msp->रेजिस्टरs + MSP_GCR);
	udelay(100);

	वापस 0;
पूर्ण

अटल पूर्णांक configure_multichannel(काष्ठा ux500_msp *msp,
				काष्ठा ux500_msp_config *config)
अणु
	काष्ठा msp_protdesc *protdesc;
	काष्ठा msp_multichannel_config *mcfg;
	u32 reg_val_MCR;

	अगर (config->शेष_protdesc == 1) अणु
		अगर (config->protocol >= MSP_INVALID_PROTOCOL) अणु
			dev_err(msp->dev,
				"%s: ERROR: Invalid protocol (%d)!\n",
				__func__, config->protocol);
			वापस -EINVAL;
		पूर्ण
		protdesc = (काष्ठा msp_protdesc *)
				&prot_descs[config->protocol];
	पूर्ण अन्यथा अणु
		protdesc = (काष्ठा msp_protdesc *)&config->protdesc;
	पूर्ण

	mcfg = &config->multichannel_config;
	अगर (mcfg->tx_multichannel_enable) अणु
		अगर (protdesc->tx_phase_mode == MSP_SINGLE_PHASE) अणु
			reg_val_MCR = पढ़ोl(msp->रेजिस्टरs + MSP_MCR);
			ग_लिखोl(reg_val_MCR | (mcfg->tx_multichannel_enable ?
						1 << TMCEN_BIT : 0),
				msp->रेजिस्टरs + MSP_MCR);
			ग_लिखोl(mcfg->tx_channel_0_enable,
				msp->रेजिस्टरs + MSP_TCE0);
			ग_लिखोl(mcfg->tx_channel_1_enable,
				msp->रेजिस्टरs + MSP_TCE1);
			ग_लिखोl(mcfg->tx_channel_2_enable,
				msp->रेजिस्टरs + MSP_TCE2);
			ग_लिखोl(mcfg->tx_channel_3_enable,
				msp->रेजिस्टरs + MSP_TCE3);
		पूर्ण अन्यथा अणु
			dev_err(msp->dev,
				"%s: ERROR: Only single-phase supported (TX-mode: %d)!\n",
				__func__, protdesc->tx_phase_mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (mcfg->rx_multichannel_enable) अणु
		अगर (protdesc->rx_phase_mode == MSP_SINGLE_PHASE) अणु
			reg_val_MCR = पढ़ोl(msp->रेजिस्टरs + MSP_MCR);
			ग_लिखोl(reg_val_MCR | (mcfg->rx_multichannel_enable ?
						1 << RMCEN_BIT : 0),
				msp->रेजिस्टरs + MSP_MCR);
			ग_लिखोl(mcfg->rx_channel_0_enable,
					msp->रेजिस्टरs + MSP_RCE0);
			ग_लिखोl(mcfg->rx_channel_1_enable,
					msp->रेजिस्टरs + MSP_RCE1);
			ग_लिखोl(mcfg->rx_channel_2_enable,
					msp->रेजिस्टरs + MSP_RCE2);
			ग_लिखोl(mcfg->rx_channel_3_enable,
					msp->रेजिस्टरs + MSP_RCE3);
		पूर्ण अन्यथा अणु
			dev_err(msp->dev,
				"%s: ERROR: Only single-phase supported (RX-mode: %d)!\n",
				__func__, protdesc->rx_phase_mode);
			वापस -EINVAL;
		पूर्ण
		अगर (mcfg->rx_comparison_enable_mode) अणु
			reg_val_MCR = पढ़ोl(msp->रेजिस्टरs + MSP_MCR);
			ग_लिखोl(reg_val_MCR |
				(mcfg->rx_comparison_enable_mode << RCMPM_BIT),
				msp->रेजिस्टरs + MSP_MCR);

			ग_लिखोl(mcfg->comparison_mask,
					msp->रेजिस्टरs + MSP_RCM);
			ग_लिखोl(mcfg->comparison_value,
					msp->रेजिस्टरs + MSP_RCV);

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enable_msp(काष्ठा ux500_msp *msp, काष्ठा ux500_msp_config *config)
अणु
	पूर्णांक status = 0;
	u32 reg_val_DMACR, reg_val_GCR;

	/* Configure msp with protocol dependent settings */
	configure_protocol(msp, config);
	setup_bitclk(msp, config);
	अगर (config->multichannel_configured == 1) अणु
		status = configure_multichannel(msp, config);
		अगर (status)
			dev_warn(msp->dev,
				"%s: WARN: configure_multichannel failed (%d)!\n",
				__func__, status);
	पूर्ण

	/* Make sure the correct DMA-directions are configured */
	अगर ((config->direction & MSP_सूची_RX) &&
			!msp->capture_dma_data.dma_cfg) अणु
		dev_err(msp->dev, "%s: ERROR: MSP RX-mode is not configured!",
			__func__);
		वापस -EINVAL;
	पूर्ण
	अगर ((config->direction == MSP_सूची_TX) &&
			!msp->playback_dma_data.dma_cfg) अणु
		dev_err(msp->dev, "%s: ERROR: MSP TX-mode is not configured!",
			__func__);
		वापस -EINVAL;
	पूर्ण

	reg_val_DMACR = पढ़ोl(msp->रेजिस्टरs + MSP_DMACR);
	अगर (config->direction & MSP_सूची_RX)
		reg_val_DMACR |= RX_DMA_ENABLE;
	अगर (config->direction & MSP_सूची_TX)
		reg_val_DMACR |= TX_DMA_ENABLE;
	ग_लिखोl(reg_val_DMACR, msp->रेजिस्टरs + MSP_DMACR);

	ग_लिखोl(config->iodelay, msp->रेजिस्टरs + MSP_IODLY);

	/* Enable frame generation logic */
	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR | FRAME_GEN_ENABLE, msp->रेजिस्टरs + MSP_GCR);

	वापस status;
पूर्ण

अटल व्योम flush_fअगरo_rx(काष्ठा ux500_msp *msp)
अणु
	u32 reg_val_GCR, reg_val_FLR;
	u32 limit = 32;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR | RX_ENABLE, msp->रेजिस्टरs + MSP_GCR);

	reg_val_FLR = पढ़ोl(msp->रेजिस्टरs + MSP_FLR);
	जबतक (!(reg_val_FLR & RX_FIFO_EMPTY) && limit--) अणु
		पढ़ोl(msp->रेजिस्टरs + MSP_DR);
		reg_val_FLR = पढ़ोl(msp->रेजिस्टरs + MSP_FLR);
	पूर्ण

	ग_लिखोl(reg_val_GCR, msp->रेजिस्टरs + MSP_GCR);
पूर्ण

अटल व्योम flush_fअगरo_tx(काष्ठा ux500_msp *msp)
अणु
	u32 reg_val_GCR, reg_val_FLR;
	u32 limit = 32;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR | TX_ENABLE, msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(MSP_ITCR_ITEN | MSP_ITCR_TESTFIFO, msp->रेजिस्टरs + MSP_ITCR);

	reg_val_FLR = पढ़ोl(msp->रेजिस्टरs + MSP_FLR);
	जबतक (!(reg_val_FLR & TX_FIFO_EMPTY) && limit--) अणु
		पढ़ोl(msp->रेजिस्टरs + MSP_TSTDR);
		reg_val_FLR = पढ़ोl(msp->रेजिस्टरs + MSP_FLR);
	पूर्ण
	ग_लिखोl(0x0, msp->रेजिस्टरs + MSP_ITCR);
	ग_लिखोl(reg_val_GCR, msp->रेजिस्टरs + MSP_GCR);
पूर्ण

पूर्णांक ux500_msp_i2s_खोलो(काष्ठा ux500_msp *msp,
		काष्ठा ux500_msp_config *config)
अणु
	u32 old_reg, new_reg, mask;
	पूर्णांक res;
	अचिन्हित पूर्णांक tx_sel, rx_sel, tx_busy, rx_busy;

	अगर (in_पूर्णांकerrupt()) अणु
		dev_err(msp->dev,
			"%s: ERROR: Open called in interrupt context!\n",
			__func__);
		वापस -1;
	पूर्ण

	tx_sel = (config->direction & MSP_सूची_TX) > 0;
	rx_sel = (config->direction & MSP_सूची_RX) > 0;
	अगर (!tx_sel && !rx_sel) अणु
		dev_err(msp->dev, "%s: Error: No direction selected!\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	tx_busy = (msp->dir_busy & MSP_सूची_TX) > 0;
	rx_busy = (msp->dir_busy & MSP_सूची_RX) > 0;
	अगर (tx_busy && tx_sel) अणु
		dev_err(msp->dev, "%s: Error: TX is in use!\n", __func__);
		वापस -EBUSY;
	पूर्ण
	अगर (rx_busy && rx_sel) अणु
		dev_err(msp->dev, "%s: Error: RX is in use!\n", __func__);
		वापस -EBUSY;
	पूर्ण

	msp->dir_busy |= (tx_sel ? MSP_सूची_TX : 0) | (rx_sel ? MSP_सूची_RX : 0);

	/* First करो the global config रेजिस्टर */
	mask = RX_CLK_SEL_MASK | TX_CLK_SEL_MASK | RX_FSYNC_MASK |
	    TX_FSYNC_MASK | RX_SYNC_SEL_MASK | TX_SYNC_SEL_MASK |
	    RX_FIFO_ENABLE_MASK | TX_FIFO_ENABLE_MASK | SRG_CLK_SEL_MASK |
	    LOOPBACK_MASK | TX_EXTRA_DELAY_MASK;

	new_reg = (config->tx_clk_sel | config->rx_clk_sel |
		config->rx_fsync_pol | config->tx_fsync_pol |
		config->rx_fsync_sel | config->tx_fsync_sel |
		config->rx_fअगरo_config | config->tx_fअगरo_config |
		config->srg_clk_sel | config->loopback_enable |
		config->tx_data_enable);

	old_reg = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	old_reg &= ~mask;
	new_reg |= old_reg;
	ग_लिखोl(new_reg, msp->रेजिस्टरs + MSP_GCR);

	res = enable_msp(msp, config);
	अगर (res < 0) अणु
		dev_err(msp->dev, "%s: ERROR: enable_msp failed (%d)!\n",
			__func__, res);
		वापस -EBUSY;
	पूर्ण
	अगर (config->loopback_enable & 0x80)
		msp->loopback_enable = 1;

	/* Flush FIFOs */
	flush_fअगरo_tx(msp);
	flush_fअगरo_rx(msp);

	msp->msp_state = MSP_STATE_CONFIGURED;
	वापस 0;
पूर्ण

अटल व्योम disable_msp_rx(काष्ठा ux500_msp *msp)
अणु
	u32 reg_val_GCR, reg_val_DMACR, reg_val_IMSC;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR & ~RX_ENABLE, msp->रेजिस्टरs + MSP_GCR);
	reg_val_DMACR = पढ़ोl(msp->रेजिस्टरs + MSP_DMACR);
	ग_लिखोl(reg_val_DMACR & ~RX_DMA_ENABLE, msp->रेजिस्टरs + MSP_DMACR);
	reg_val_IMSC = पढ़ोl(msp->रेजिस्टरs + MSP_IMSC);
	ग_लिखोl(reg_val_IMSC &
			~(RX_SERVICE_INT | RX_OVERRUN_ERROR_INT),
			msp->रेजिस्टरs + MSP_IMSC);

	msp->dir_busy &= ~MSP_सूची_RX;
पूर्ण

अटल व्योम disable_msp_tx(काष्ठा ux500_msp *msp)
अणु
	u32 reg_val_GCR, reg_val_DMACR, reg_val_IMSC;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	ग_लिखोl(reg_val_GCR & ~TX_ENABLE, msp->रेजिस्टरs + MSP_GCR);
	reg_val_DMACR = पढ़ोl(msp->रेजिस्टरs + MSP_DMACR);
	ग_लिखोl(reg_val_DMACR & ~TX_DMA_ENABLE, msp->रेजिस्टरs + MSP_DMACR);
	reg_val_IMSC = पढ़ोl(msp->रेजिस्टरs + MSP_IMSC);
	ग_लिखोl(reg_val_IMSC &
			~(TX_SERVICE_INT | TX_UNDERRUN_ERR_INT),
			msp->रेजिस्टरs + MSP_IMSC);

	msp->dir_busy &= ~MSP_सूची_TX;
पूर्ण

अटल पूर्णांक disable_msp(काष्ठा ux500_msp *msp, अचिन्हित पूर्णांक dir)
अणु
	u32 reg_val_GCR;
	अचिन्हित पूर्णांक disable_tx, disable_rx;

	reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
	disable_tx = dir & MSP_सूची_TX;
	disable_rx = dir & MSP_सूची_TX;
	अगर (disable_tx && disable_rx) अणु
		reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
		ग_लिखोl(reg_val_GCR | LOOPBACK_MASK,
				msp->रेजिस्टरs + MSP_GCR);

		/* Flush TX-FIFO */
		flush_fअगरo_tx(msp);

		/* Disable TX-channel */
		ग_लिखोl((पढ़ोl(msp->रेजिस्टरs + MSP_GCR) &
			       (~TX_ENABLE)), msp->रेजिस्टरs + MSP_GCR);

		/* Flush RX-FIFO */
		flush_fअगरo_rx(msp);

		/* Disable Loopback and Receive channel */
		ग_लिखोl((पढ़ोl(msp->रेजिस्टरs + MSP_GCR) &
				(~(RX_ENABLE | LOOPBACK_MASK))),
				msp->रेजिस्टरs + MSP_GCR);

		disable_msp_tx(msp);
		disable_msp_rx(msp);
	पूर्ण अन्यथा अगर (disable_tx)
		disable_msp_tx(msp);
	अन्यथा अगर (disable_rx)
		disable_msp_rx(msp);

	वापस 0;
पूर्ण

पूर्णांक ux500_msp_i2s_trigger(काष्ठा ux500_msp *msp, पूर्णांक cmd, पूर्णांक direction)
अणु
	u32 reg_val_GCR, enable_bit;

	अगर (msp->msp_state == MSP_STATE_IDLE) अणु
		dev_err(msp->dev, "%s: ERROR: MSP is not configured!\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
			enable_bit = TX_ENABLE;
		अन्यथा
			enable_bit = RX_ENABLE;
		reg_val_GCR = पढ़ोl(msp->रेजिस्टरs + MSP_GCR);
		ग_लिखोl(reg_val_GCR | enable_bit, msp->रेजिस्टरs + MSP_GCR);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
			disable_msp_tx(msp);
		अन्यथा
			disable_msp_rx(msp);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ux500_msp_i2s_बंद(काष्ठा ux500_msp *msp, अचिन्हित पूर्णांक dir)
अणु
	पूर्णांक status = 0;

	dev_dbg(msp->dev, "%s: Enter (dir = 0x%01x).\n", __func__, dir);

	status = disable_msp(msp, dir);
	अगर (msp->dir_busy == 0) अणु
		/* disable sample rate and frame generators */
		msp->msp_state = MSP_STATE_IDLE;
		ग_लिखोl((पढ़ोl(msp->रेजिस्टरs + MSP_GCR) &
			       (~(FRAME_GEN_ENABLE | SRG_ENABLE))),
			      msp->रेजिस्टरs + MSP_GCR);

		ग_लिखोl(0, msp->रेजिस्टरs + MSP_GCR);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_TCF);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCF);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_DMACR);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_SRG);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_MCR);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCM);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCV);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_TCE0);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_TCE1);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_TCE2);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_TCE3);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCE0);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCE1);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCE2);
		ग_लिखोl(0, msp->रेजिस्टरs + MSP_RCE3);
	पूर्ण

	वापस status;

पूर्ण

अटल पूर्णांक ux500_msp_i2s_of_init_msp(काष्ठा platक्रमm_device *pdev,
				काष्ठा ux500_msp *msp,
				काष्ठा msp_i2s_platक्रमm_data **platक्रमm_data)
अणु
	काष्ठा msp_i2s_platक्रमm_data *pdata;

	*platक्रमm_data = devm_kzalloc(&pdev->dev,
				     माप(काष्ठा msp_i2s_platक्रमm_data),
				     GFP_KERNEL);
	pdata = *platक्रमm_data;
	अगर (!pdata)
		वापस -ENOMEM;

	msp->playback_dma_data.dma_cfg = devm_kzalloc(&pdev->dev,
					माप(काष्ठा stedma40_chan_cfg),
					GFP_KERNEL);
	अगर (!msp->playback_dma_data.dma_cfg)
		वापस -ENOMEM;

	msp->capture_dma_data.dma_cfg = devm_kzalloc(&pdev->dev,
					माप(काष्ठा stedma40_chan_cfg),
					GFP_KERNEL);
	अगर (!msp->capture_dma_data.dma_cfg)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक ux500_msp_i2s_init_msp(काष्ठा platक्रमm_device *pdev,
			काष्ठा ux500_msp **msp_p,
			काष्ठा msp_i2s_platक्रमm_data *platक्रमm_data)
अणु
	काष्ठा resource *res = शून्य;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ux500_msp *msp;
	पूर्णांक ret;

	*msp_p = devm_kzalloc(&pdev->dev, माप(काष्ठा ux500_msp), GFP_KERNEL);
	msp = *msp_p;
	अगर (!msp)
		वापस -ENOMEM;

	अगर (!platक्रमm_data) अणु
		अगर (np) अणु
			ret = ux500_msp_i2s_of_init_msp(pdev, msp,
							&platक्रमm_data);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		msp->playback_dma_data.dma_cfg = platक्रमm_data->msp_i2s_dma_tx;
		msp->capture_dma_data.dma_cfg = platक्रमm_data->msp_i2s_dma_rx;
		msp->id = platक्रमm_data->id;
	पूर्ण

	msp->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "%s: ERROR: Unable to get resource!\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	msp->playback_dma_data.tx_rx_addr = res->start + MSP_DR;
	msp->capture_dma_data.tx_rx_addr = res->start + MSP_DR;

	msp->रेजिस्टरs = devm_ioremap(&pdev->dev, res->start,
				      resource_size(res));
	अगर (msp->रेजिस्टरs == शून्य) अणु
		dev_err(&pdev->dev, "%s: ERROR: ioremap failed!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	msp->msp_state = MSP_STATE_IDLE;
	msp->loopback_enable = 0;

	वापस 0;
पूर्ण

व्योम ux500_msp_i2s_cleanup_msp(काष्ठा platक्रमm_device *pdev,
			काष्ठा ux500_msp *msp)
अणु
	dev_dbg(msp->dev, "%s: Enter (id = %d).\n", __func__, msp->id);
पूर्ण

MODULE_LICENSE("GPL v2");
