<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2019 NXP

#समावेश <linux/bitrev.h>
#समावेश <linux/clk.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_iec958.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_xcvr.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_XCVR_CAPDS_SIZE	256

काष्ठा fsl_xcvr_soc_data अणु
	स्थिर अक्षर *fw_name;
पूर्ण;

काष्ठा fsl_xcvr अणु
	स्थिर काष्ठा fsl_xcvr_soc_data *soc_data;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा clk *ipg_clk;
	काष्ठा clk *pll_ipg_clk;
	काष्ठा clk *phy_clk;
	काष्ठा clk *spba_clk;
	काष्ठा reset_control *reset;
	u8 streams;
	u32 mode;
	u32 arc_mode;
	व्योम __iomem *ram_addr;
	काष्ठा snd_dmaengine_dai_dma_data dma_prms_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_prms_tx;
	काष्ठा snd_aes_iec958 rx_iec958;
	काष्ठा snd_aes_iec958 tx_iec958;
	u8 cap_ds[FSL_XCVR_CAPDS_SIZE];
पूर्ण;

अटल स्थिर काष्ठा fsl_xcvr_pll_conf अणु
	u8 mfi;   /* min=0x18, max=0x38 */
	u32 mfn;  /* चिन्हित पूर्णांक, 2's compl., min=0x3FFF0000, max=0x00010000 */
	u32 mfd;  /* अचिन्हित पूर्णांक */
	u32 fout; /* Fout = Fref*(MFI + MFN/MFD), Fref is 24MHz */
पूर्ण fsl_xcvr_pll_cfg[] = अणु
	अणु .mfi = 54, .mfn = 1,  .mfd = 6,   .fout = 1300000000, पूर्ण, /* 1.3 GHz */
	अणु .mfi = 32, .mfn = 96, .mfd = 125, .fout = 786432000, पूर्ण,  /* 8000 Hz */
	अणु .mfi = 30, .mfn = 66, .mfd = 625, .fout = 722534400, पूर्ण,  /* 11025 Hz */
	अणु .mfi = 29, .mfn = 1,  .mfd = 6,   .fout = 700000000, पूर्ण,  /* 700 MHz */
पूर्ण;

/*
 * HDMI2.1 spec defines 6- and 12-channels layout क्रम one bit audio
 * stream. Toकरो: to check how this हाल can be considered below
 */
अटल स्थिर u32 fsl_xcvr_earc_channels[] = अणु 1, 2, 8, 16, 32, पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_xcvr_earc_channels_स्थिरr = अणु
	.count = ARRAY_SIZE(fsl_xcvr_earc_channels),
	.list = fsl_xcvr_earc_channels,
पूर्ण;

अटल स्थिर u32 fsl_xcvr_earc_rates[] = अणु
	32000, 44100, 48000, 64000, 88200, 96000,
	128000, 176400, 192000, 256000, 352800, 384000,
	512000, 705600, 768000, 1024000, 1411200, 1536000,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_xcvr_earc_rates_स्थिरr = अणु
	.count = ARRAY_SIZE(fsl_xcvr_earc_rates),
	.list = fsl_xcvr_earc_rates,
पूर्ण;

अटल स्थिर u32 fsl_xcvr_spdअगर_channels[] = अणु 2, पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_xcvr_spdअगर_channels_स्थिरr = अणु
	.count = ARRAY_SIZE(fsl_xcvr_spdअगर_channels),
	.list = fsl_xcvr_spdअगर_channels,
पूर्ण;

अटल स्थिर u32 fsl_xcvr_spdअगर_rates[] = अणु
	32000, 44100, 48000, 88200, 96000, 176400, 192000,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_xcvr_spdअगर_rates_स्थिरr = अणु
	.count = ARRAY_SIZE(fsl_xcvr_spdअगर_rates),
	.list = fsl_xcvr_spdअगर_rates,
पूर्ण;

अटल पूर्णांक fsl_xcvr_arc_mode_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;

	xcvr->arc_mode = snd_soc_क्रमागत_item_to_val(e, item[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_arc_mode_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	ucontrol->value.क्रमागतerated.item[0] = xcvr->arc_mode;

	वापस 0;
पूर्ण

अटल स्थिर u32 fsl_xcvr_phy_arc_cfg[] = अणु
	FSL_XCVR_PHY_CTRL_ARC_MODE_SE_EN, FSL_XCVR_PHY_CTRL_ARC_MODE_CM_EN,
पूर्ण;

अटल स्थिर अक्षर * स्थिर fsl_xcvr_arc_mode[] = अणु "Single Ended", "Common", पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत fsl_xcvr_arc_mode_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(fsl_xcvr_arc_mode), fsl_xcvr_arc_mode);
अटल काष्ठा snd_kcontrol_new fsl_xcvr_arc_mode_kctl =
	SOC_ENUM_EXT("ARC Mode", fsl_xcvr_arc_mode_क्रमागत,
		     fsl_xcvr_arc_mode_get, fsl_xcvr_arc_mode_put);

/* Capabilities data काष्ठाure, bytes */
अटल पूर्णांक fsl_xcvr_type_capds_bytes_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = FSL_XCVR_CAPDS_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_capds_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	स_नकल(ucontrol->value.bytes.data, xcvr->cap_ds, FSL_XCVR_CAPDS_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_capds_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	स_नकल(xcvr->cap_ds, ucontrol->value.bytes.data, FSL_XCVR_CAPDS_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new fsl_xcvr_earc_capds_kctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "Capabilities Data Structure",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = fsl_xcvr_type_capds_bytes_info,
	.get = fsl_xcvr_capds_get,
	.put = fsl_xcvr_capds_put,
पूर्ण;

अटल पूर्णांक fsl_xcvr_activate_ctl(काष्ठा snd_soc_dai *dai, स्थिर अक्षर *name,
				 bool active)
अणु
	काष्ठा snd_soc_card *card = dai->component->card;
	काष्ठा snd_kcontrol *kctl;
	bool enabled;

	kctl = snd_soc_card_get_kcontrol(card, name);
	अगर (kctl == शून्य)
		वापस -ENOENT;

	enabled = ((kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_WRITE) != 0);
	अगर (active == enabled)
		वापस 0; /* nothing to करो */

	अगर (active)
		kctl->vd[0].access |=  SNDRV_CTL_ELEM_ACCESS_WRITE;
	अन्यथा
		kctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_WRITE;

	snd_ctl_notअगरy(card->snd_card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);

	वापस 1;
पूर्ण

अटल पूर्णांक fsl_xcvr_mode_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	काष्ठा snd_soc_card *card = dai->component->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;

	xcvr->mode = snd_soc_क्रमागत_item_to_val(e, item[0]);

	fsl_xcvr_activate_ctl(dai, fsl_xcvr_arc_mode_kctl.name,
			      (xcvr->mode == FSL_XCVR_MODE_ARC));
	fsl_xcvr_activate_ctl(dai, fsl_xcvr_earc_capds_kctl.name,
			      (xcvr->mode == FSL_XCVR_MODE_EARC));
	/* Allow playback क्रम SPDIF only */
	rtd = snd_soc_get_pcm_runसमय(card, card->dai_link);
	rtd->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream_count =
		(xcvr->mode == FSL_XCVR_MODE_SPDIF ? 1 : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_mode_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	ucontrol->value.क्रमागतerated.item[0] = xcvr->mode;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर fsl_xcvr_mode[] = अणु "SPDIF", "ARC RX", "eARC", पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत fsl_xcvr_mode_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(fsl_xcvr_mode), fsl_xcvr_mode);
अटल काष्ठा snd_kcontrol_new fsl_xcvr_mode_kctl =
	SOC_ENUM_EXT("XCVR Mode", fsl_xcvr_mode_क्रमागत,
		     fsl_xcvr_mode_get, fsl_xcvr_mode_put);

/** phy: true => phy, false => pll */
अटल पूर्णांक fsl_xcvr_ai_ग_लिखो(काष्ठा fsl_xcvr *xcvr, u8 reg, u32 data, bool phy)
अणु
	काष्ठा device *dev = &xcvr->pdev->dev;
	u32 val, idx, tidx;
	पूर्णांक ret;

	idx  = BIT(phy ? 26 : 24);
	tidx = BIT(phy ? 27 : 25);

	regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL_CLR, 0xFF);
	regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL_SET, reg);
	regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_WDATA, data);
	regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL_TOG, idx);

	ret = regmap_पढ़ो_poll_समयout(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL, val,
				       (val & idx) == ((val & tidx) >> 1),
				       10, 10000);
	अगर (ret)
		dev_err(dev, "AI timeout: failed to set %s reg 0x%02x=0x%08x\n",
			phy ? "PHY" : "PLL", reg, data);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_xcvr_en_phy_pll(काष्ठा fsl_xcvr *xcvr, u32 freq, bool tx)
अणु
	काष्ठा device *dev = &xcvr->pdev->dev;
	u32 i, भाग = 0, log2;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(fsl_xcvr_pll_cfg); i++) अणु
		अगर (fsl_xcvr_pll_cfg[i].fout % freq == 0) अणु
			भाग = fsl_xcvr_pll_cfg[i].fout / freq;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!भाग || i >= ARRAY_SIZE(fsl_xcvr_pll_cfg))
		वापस -EINVAL;

	log2 = ilog2(भाग);

	/* Release AI पूर्णांकerface from reset */
	ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL_SET,
			   FSL_XCVR_PHY_AI_CTRL_AI_RESETN);
	अगर (ret < 0) अणु
		dev_err(dev, "Error while setting IER0: %d\n", ret);
		वापस ret;
	पूर्ण

	/* PLL: BANDGAP_SET: EN_VBG (enable bandgap) */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_BANDGAP_SET,
			  FSL_XCVR_PLL_BANDGAP_EN_VBG, 0);

	/* PLL: CTRL0: DIV_INTEGER */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0, fsl_xcvr_pll_cfg[i].mfi, 0);
	/* PLL: NUMERATOR: MFN */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_NUM, fsl_xcvr_pll_cfg[i].mfn, 0);
	/* PLL: DENOMINATOR: MFD */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_DEN, fsl_xcvr_pll_cfg[i].mfd, 0);
	/* PLL: CTRL0_SET: HOLD_RING_OFF, POWER_UP */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0_SET,
			  FSL_XCVR_PLL_CTRL0_HROFF | FSL_XCVR_PLL_CTRL0_PWP, 0);
	udelay(25);
	/* PLL: CTRL0: Clear Hold Ring Off */
	fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0_CLR,
			  FSL_XCVR_PLL_CTRL0_HROFF, 0);
	udelay(100);
	अगर (tx) अणु /* TX is enabled क्रम SPDIF only */
		/* PLL: POSTDIV: PDIV0 */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_PDIV,
				  FSL_XCVR_PLL_PDIVx(log2, 0), 0);
		/* PLL: CTRL_SET: CLKMUX0_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0_SET,
				  FSL_XCVR_PLL_CTRL0_CM0_EN, 0);
	पूर्ण अन्यथा अगर (xcvr->mode == FSL_XCVR_MODE_EARC) अणु /* eARC RX */
		/* PLL: POSTDIV: PDIV1 */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_PDIV,
				  FSL_XCVR_PLL_PDIVx(log2, 1), 0);
		/* PLL: CTRL_SET: CLKMUX1_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0_SET,
				  FSL_XCVR_PLL_CTRL0_CM1_EN, 0);
	पूर्ण अन्यथा अणु /* SPDIF / ARC RX */
		/* PLL: POSTDIV: PDIV2 */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_PDIV,
				  FSL_XCVR_PLL_PDIVx(log2, 2), 0);
		/* PLL: CTRL_SET: CLKMUX2_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PLL_CTRL0_SET,
				  FSL_XCVR_PLL_CTRL0_CM2_EN, 0);
	पूर्ण

	अगर (xcvr->mode == FSL_XCVR_MODE_EARC) अणु /* eARC mode */
		/* PHY: CTRL_SET: TX_DIFF_OE, PHY_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL_SET,
				  FSL_XCVR_PHY_CTRL_TSDIFF_OE |
				  FSL_XCVR_PHY_CTRL_PHY_EN, 1);
		/* PHY: CTRL2_SET: EARC_TX_MODE */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL2_SET,
				  FSL_XCVR_PHY_CTRL2_EARC_TXMS, 1);
	पूर्ण अन्यथा अगर (!tx) अणु /* SPDIF / ARC RX mode */
		अगर (xcvr->mode == FSL_XCVR_MODE_SPDIF)
			/* PHY: CTRL_SET: SPDIF_EN */
			fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL_SET,
					  FSL_XCVR_PHY_CTRL_SPDIF_EN, 1);
		अन्यथा	/* PHY: CTRL_SET: ARC RX setup */
			fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL_SET,
					  FSL_XCVR_PHY_CTRL_PHY_EN |
					  FSL_XCVR_PHY_CTRL_RX_CM_EN |
					  fsl_xcvr_phy_arc_cfg[xcvr->arc_mode], 1);
	पूर्ण

	dev_dbg(dev, "PLL Fexp: %u, Fout: %u, mfi: %u, mfn: %u, mfd: %d, div: %u, pdiv0: %u\n",
		freq, fsl_xcvr_pll_cfg[i].fout, fsl_xcvr_pll_cfg[i].mfi,
		fsl_xcvr_pll_cfg[i].mfn, fsl_xcvr_pll_cfg[i].mfd, भाग, log2);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_en_aud_pll(काष्ठा fsl_xcvr *xcvr, u32 freq)
अणु
	काष्ठा device *dev = &xcvr->pdev->dev;
	पूर्णांक ret;

	clk_disable_unprepare(xcvr->phy_clk);
	ret = clk_set_rate(xcvr->phy_clk, freq);
	अगर (ret < 0) अणु
		dev_err(dev, "Error while setting AUD PLL rate: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(xcvr->phy_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to start PHY clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Release AI पूर्णांकerface from reset */
	ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_PHY_AI_CTRL_SET,
			   FSL_XCVR_PHY_AI_CTRL_AI_RESETN);
	अगर (ret < 0) अणु
		dev_err(dev, "Error while setting IER0: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (xcvr->mode == FSL_XCVR_MODE_EARC) अणु /* eARC mode */
		/* PHY: CTRL_SET: TX_DIFF_OE, PHY_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL_SET,
				  FSL_XCVR_PHY_CTRL_TSDIFF_OE |
				  FSL_XCVR_PHY_CTRL_PHY_EN, 1);
		/* PHY: CTRL2_SET: EARC_TX_MODE */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL2_SET,
				  FSL_XCVR_PHY_CTRL2_EARC_TXMS, 1);
	पूर्ण अन्यथा अणु /* SPDIF mode */
		/* PHY: CTRL_SET: TX_CLK_AUD_SS | SPDIF_EN */
		fsl_xcvr_ai_ग_लिखो(xcvr, FSL_XCVR_PHY_CTRL_SET,
				  FSL_XCVR_PHY_CTRL_TX_CLK_AUD_SS |
				  FSL_XCVR_PHY_CTRL_SPDIF_EN, 1);
	पूर्ण

	dev_dbg(dev, "PLL Fexp: %u\n", freq);

	वापस 0;
पूर्ण

#घोषणा FSL_XCVR_SPDIF_RX_FREQ	175000000
अटल पूर्णांक fsl_xcvr_prepare(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 m_ctl = 0, v_ctl = 0;
	u32 r = substream->runसमय->rate, ch = substream->runसमय->channels;
	u32 fout = 32 * r * ch * 10 * 2;
	पूर्णांक ret = 0;

	चयन (xcvr->mode) अणु
	हाल FSL_XCVR_MODE_SPDIF:
	हाल FSL_XCVR_MODE_ARC:
		अगर (tx) अणु
			ret = fsl_xcvr_en_aud_pll(xcvr, fout);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to set TX freq %u: %d\n",
					fout, ret);
				वापस ret;
			पूर्ण

			ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_TX_DPTH_CTRL_SET,
					   FSL_XCVR_TX_DPTH_CTRL_FRM_FMT);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to set TX_DPTH: %d\n", ret);
				वापस ret;
			पूर्ण

			/**
			 * set SPDIF MODE - this flag is used to gate
			 * SPDIF output, useless क्रम SPDIF RX
			 */
			m_ctl |= FSL_XCVR_EXT_CTRL_SPDIF_MODE;
			v_ctl |= FSL_XCVR_EXT_CTRL_SPDIF_MODE;
		पूर्ण अन्यथा अणु
			/**
			 * Clear RX FIFO, flip RX FIFO bits,
			 * disable eARC related HW mode detects
			 */
			ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_RX_DPTH_CTRL_SET,
					   FSL_XCVR_RX_DPTH_CTRL_STORE_FMT |
					   FSL_XCVR_RX_DPTH_CTRL_CLR_RX_FIFO |
					   FSL_XCVR_RX_DPTH_CTRL_COMP |
					   FSL_XCVR_RX_DPTH_CTRL_LAYB_CTRL);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to set RX_DPTH: %d\n", ret);
				वापस ret;
			पूर्ण

			ret = fsl_xcvr_en_phy_pll(xcvr, FSL_XCVR_SPDIF_RX_FREQ, tx);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to set RX freq %u: %d\n",
					FSL_XCVR_SPDIF_RX_FREQ, ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FSL_XCVR_MODE_EARC:
		अगर (!tx) अणु
			/** Clear RX FIFO, flip RX FIFO bits */
			ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_RX_DPTH_CTRL_SET,
					   FSL_XCVR_RX_DPTH_CTRL_STORE_FMT |
					   FSL_XCVR_RX_DPTH_CTRL_CLR_RX_FIFO);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to set RX_DPTH: %d\n", ret);
				वापस ret;
			पूर्ण

			/** Enable eARC related HW mode detects */
			ret = regmap_ग_लिखो(xcvr->regmap, FSL_XCVR_RX_DPTH_CTRL_CLR,
					   FSL_XCVR_RX_DPTH_CTRL_COMP |
					   FSL_XCVR_RX_DPTH_CTRL_LAYB_CTRL);
			अगर (ret < 0) अणु
				dev_err(dai->dev, "Failed to clr TX_DPTH: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		/* clear CMDC RESET */
		m_ctl |= FSL_XCVR_EXT_CTRL_CMDC_RESET(tx);
		/* set TX_RX_MODE */
		m_ctl |= FSL_XCVR_EXT_CTRL_TX_RX_MODE;
		v_ctl |= (tx ? FSL_XCVR_EXT_CTRL_TX_RX_MODE : 0);
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_IER0,
				 FSL_XCVR_IRQ_EARC_ALL, FSL_XCVR_IRQ_EARC_ALL);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Error while setting IER0: %d\n", ret);
		वापस ret;
	पूर्ण

	/* clear DPATH RESET */
	m_ctl |= FSL_XCVR_EXT_CTRL_DPTH_RESET(tx);
	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL, m_ctl, v_ctl);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Error while setting EXT_CTRL: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_स्थिरr(स्थिर काष्ठा snd_pcm_substream *substream,
			   स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *channels,
			   स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *rates)
अणु
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(rt, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					 channels);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(rt, 0, SNDRV_PCM_HW_PARAM_RATE,
					 rates);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_startup(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक ret = 0;

	अगर (xcvr->streams & BIT(substream->stream)) अणु
		dev_err(dai->dev, "%sX busy\n", tx ? "T" : "R");
		वापस -EBUSY;
	पूर्ण

	चयन (xcvr->mode) अणु
	हाल FSL_XCVR_MODE_SPDIF:
	हाल FSL_XCVR_MODE_ARC:
		ret = fsl_xcvr_स्थिरr(substream, &fsl_xcvr_spdअगर_channels_स्थिरr,
				      &fsl_xcvr_spdअगर_rates_स्थिरr);
		अवरोध;
	हाल FSL_XCVR_MODE_EARC:
		ret = fsl_xcvr_स्थिरr(substream, &fsl_xcvr_earc_channels_स्थिरr,
				      &fsl_xcvr_earc_rates_स्थिरr);
		अवरोध;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	xcvr->streams |= BIT(substream->stream);

	/* Disable XCVR controls अगर there is stream started */
	fsl_xcvr_activate_ctl(dai, fsl_xcvr_mode_kctl.name, false);
	fsl_xcvr_activate_ctl(dai, fsl_xcvr_arc_mode_kctl.name, false);
	fsl_xcvr_activate_ctl(dai, fsl_xcvr_earc_capds_kctl.name, false);

	वापस 0;
पूर्ण

अटल व्योम fsl_xcvr_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 mask = 0, val = 0;
	पूर्णांक ret;

	xcvr->streams &= ~BIT(substream->stream);

	/* Enable XCVR controls अगर there is no stream started */
	अगर (!xcvr->streams) अणु
		fsl_xcvr_activate_ctl(dai, fsl_xcvr_mode_kctl.name, true);
		fsl_xcvr_activate_ctl(dai, fsl_xcvr_arc_mode_kctl.name,
				      (xcvr->mode == FSL_XCVR_MODE_ARC));
		fsl_xcvr_activate_ctl(dai, fsl_xcvr_earc_capds_kctl.name,
				      (xcvr->mode == FSL_XCVR_MODE_EARC));

		ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_IER0,
					 FSL_XCVR_IRQ_EARC_ALL, 0);
		अगर (ret < 0) अणु
			dev_err(dai->dev, "Failed to set IER0: %d\n", ret);
			वापस;
		पूर्ण

		/* clear SPDIF MODE */
		अगर (xcvr->mode == FSL_XCVR_MODE_SPDIF)
			mask |= FSL_XCVR_EXT_CTRL_SPDIF_MODE;
	पूर्ण

	अगर (xcvr->mode == FSL_XCVR_MODE_EARC) अणु
		/* set CMDC RESET */
		mask |= FSL_XCVR_EXT_CTRL_CMDC_RESET(tx);
		val  |= FSL_XCVR_EXT_CTRL_CMDC_RESET(tx);
	पूर्ण

	/* set DPATH RESET */
	mask |= FSL_XCVR_EXT_CTRL_DPTH_RESET(tx);
	val  |= FSL_XCVR_EXT_CTRL_DPTH_RESET(tx);

	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL, mask, val);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Err setting DPATH RESET: %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_xcvr_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (tx) अणु
			चयन (xcvr->mode) अणु
			हाल FSL_XCVR_MODE_EARC:
				/* set isr_cmdc_tx_en, w1c */
				ret = regmap_ग_लिखो(xcvr->regmap,
						   FSL_XCVR_ISR_SET,
						   FSL_XCVR_ISR_CMDC_TX_EN);
				अगर (ret < 0) अणु
					dev_err(dai->dev, "err updating isr %d\n", ret);
					वापस ret;
				पूर्ण
				fallthrough;
			हाल FSL_XCVR_MODE_SPDIF:
				ret = regmap_ग_लिखो(xcvr->regmap,
					 FSL_XCVR_TX_DPTH_CTRL_SET,
					 FSL_XCVR_TX_DPTH_CTRL_STRT_DATA_TX);
				अगर (ret < 0) अणु
					dev_err(dai->dev, "Failed to start DATA_TX: %d\n", ret);
					वापस ret;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		/* enable DMA RD/WR */
		ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
					 FSL_XCVR_EXT_CTRL_DMA_DIS(tx), 0);
		अगर (ret < 0) अणु
			dev_err(dai->dev, "Failed to enable DMA: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* disable DMA RD/WR */
		ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
					 FSL_XCVR_EXT_CTRL_DMA_DIS(tx),
					 FSL_XCVR_EXT_CTRL_DMA_DIS(tx));
		अगर (ret < 0) अणु
			dev_err(dai->dev, "Failed to disable DMA: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (tx) अणु
			चयन (xcvr->mode) अणु
			हाल FSL_XCVR_MODE_SPDIF:
				ret = regmap_ग_लिखो(xcvr->regmap,
					 FSL_XCVR_TX_DPTH_CTRL_CLR,
					 FSL_XCVR_TX_DPTH_CTRL_STRT_DATA_TX);
				अगर (ret < 0) अणु
					dev_err(dai->dev, "Failed to stop DATA_TX: %d\n", ret);
					वापस ret;
				पूर्ण
				fallthrough;
			हाल FSL_XCVR_MODE_EARC:
				/* clear ISR_CMDC_TX_EN, W1C */
				ret = regmap_ग_लिखो(xcvr->regmap,
						   FSL_XCVR_ISR_CLR,
						   FSL_XCVR_ISR_CMDC_TX_EN);
				अगर (ret < 0) अणु
					dev_err(dai->dev,
						"Err updating ISR %d\n", ret);
					वापस ret;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_load_firmware(काष्ठा fsl_xcvr *xcvr)
अणु
	काष्ठा device *dev = &xcvr->pdev->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0, rem, off, out, page = 0, size = FSL_XCVR_REG_OFFSET;
	u32 mask, val;

	ret = request_firmware(&fw, xcvr->soc_data->fw_name, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to request firmware.\n");
		वापस ret;
	पूर्ण

	rem = fw->size;

	/* RAM is 20KiB = 16KiB code + 4KiB data => max 10 pages 2KiB each */
	अगर (rem > 16384) अणु
		dev_err(dev, "FW size %d is bigger than 16KiB.\n", rem);
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	क्रम (page = 0; page < 10; page++) अणु
		ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
					 FSL_XCVR_EXT_CTRL_PAGE_MASK,
					 FSL_XCVR_EXT_CTRL_PAGE(page));
		अगर (ret < 0) अणु
			dev_err(dev, "FW: failed to set page %d, err=%d\n",
				page, ret);
			जाओ err_firmware;
		पूर्ण

		off = page * size;
		out = min(rem, size);
		/* IPG घड़ी is assumed to be running, otherwise it will hang */
		अगर (out > 0) अणु
			/* ग_लिखो firmware पूर्णांकo code memory */
			स_नकल_toio(xcvr->ram_addr, fw->data + off, out);
			rem -= out;
			अगर (rem == 0) अणु
				/* last part of firmware written */
				/* clean reमुख्यing part of code memory page */
				स_रखो_io(xcvr->ram_addr + out, 0, size - out);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* clean current page, including data memory */
			स_रखो_io(xcvr->ram_addr, 0, size);
		पूर्ण
	पूर्ण;

err_firmware:
	release_firmware(fw);
	अगर (ret < 0)
		वापस ret;

	/* configure watermarks */
	mask = FSL_XCVR_EXT_CTRL_RX_FWM_MASK | FSL_XCVR_EXT_CTRL_TX_FWM_MASK;
	val  = FSL_XCVR_EXT_CTRL_RX_FWM(FSL_XCVR_FIFO_WMK_RX);
	val |= FSL_XCVR_EXT_CTRL_TX_FWM(FSL_XCVR_FIFO_WMK_TX);
	/* disable DMA RD/WR */
	mask |= FSL_XCVR_EXT_CTRL_DMA_RD_DIS | FSL_XCVR_EXT_CTRL_DMA_WR_DIS;
	val  |= FSL_XCVR_EXT_CTRL_DMA_RD_DIS | FSL_XCVR_EXT_CTRL_DMA_WR_DIS;
	/* Data RAM is 4KiB, last two pages: 8 and 9. Select page 8. */
	mask |= FSL_XCVR_EXT_CTRL_PAGE_MASK;
	val  |= FSL_XCVR_EXT_CTRL_PAGE(8);

	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL, mask, val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set watermarks: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Store Capabilities Data Structure पूर्णांकo Data RAM */
	स_नकल_toio(xcvr->ram_addr + FSL_XCVR_CAP_DATA_STR, xcvr->cap_ds,
		    FSL_XCVR_CAPDS_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_type_iec958_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_type_iec958_bytes_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = माप_field(काष्ठा snd_aes_iec958, status);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_rx_cs_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	स_नकल(ucontrol->value.iec958.status, xcvr->rx_iec958.status, 24);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_tx_cs_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	स_नकल(ucontrol->value.iec958.status, xcvr->tx_iec958.status, 24);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_xcvr_tx_cs_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	स_नकल(xcvr->tx_iec958.status, ucontrol->value.iec958.status, 24);

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new fsl_xcvr_rx_ctls[] = अणु
	/* Channel status controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = fsl_xcvr_type_iec958_info,
		.get = fsl_xcvr_rx_cs_get,
	पूर्ण,
	/* Capture channel status, bytes */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "Capture Channel Status",
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = fsl_xcvr_type_iec958_bytes_info,
		.get = fsl_xcvr_rx_cs_get,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_kcontrol_new fsl_xcvr_tx_ctls[] = अणु
	/* Channel status controller */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = fsl_xcvr_type_iec958_info,
		.get = fsl_xcvr_tx_cs_get,
		.put = fsl_xcvr_tx_cs_put,
	पूर्ण,
	/* Playback channel status, bytes */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "Playback Channel Status",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = fsl_xcvr_type_iec958_bytes_info,
		.get = fsl_xcvr_tx_cs_get,
		.put = fsl_xcvr_tx_cs_put,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_xcvr_dai_ops = अणु
	.prepare = fsl_xcvr_prepare,
	.startup = fsl_xcvr_startup,
	.shutकरोwn = fsl_xcvr_shutकरोwn,
	.trigger = fsl_xcvr_trigger,
पूर्ण;

अटल पूर्णांक fsl_xcvr_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_xcvr *xcvr = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &xcvr->dma_prms_tx, &xcvr->dma_prms_rx);

	snd_soc_add_dai_controls(dai, &fsl_xcvr_mode_kctl, 1);
	snd_soc_add_dai_controls(dai, &fsl_xcvr_arc_mode_kctl, 1);
	snd_soc_add_dai_controls(dai, &fsl_xcvr_earc_capds_kctl, 1);
	snd_soc_add_dai_controls(dai, fsl_xcvr_tx_ctls,
				 ARRAY_SIZE(fsl_xcvr_tx_ctls));
	snd_soc_add_dai_controls(dai, fsl_xcvr_rx_ctls,
				 ARRAY_SIZE(fsl_xcvr_rx_ctls));
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_xcvr_dai = अणु
	.probe  = fsl_xcvr_dai_probe,
	.ops = &fsl_xcvr_dai_ops,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 32000,
		.rate_max = 1536000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 32000,
		.rate_max = 1536000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_xcvr_comp = अणु
	.name = "fsl-xcvr-dai",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष fsl_xcvr_reg_शेषs[] = अणु
	अणु FSL_XCVR_VERSION,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_CTRL,	0xF8204040 पूर्ण,
	अणु FSL_XCVR_EXT_STATUS,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_IER0,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_IER1,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_ISR,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_ISR_SET,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_ISR_CLR,	0x00000000 पूर्ण,
	अणु FSL_XCVR_EXT_ISR_TOG,	0x00000000 पूर्ण,
	अणु FSL_XCVR_IER,		0x00000000 पूर्ण,
	अणु FSL_XCVR_ISR,		0x00000000 पूर्ण,
	अणु FSL_XCVR_ISR_SET,	0x00000000 पूर्ण,
	अणु FSL_XCVR_ISR_CLR,	0x00000000 पूर्ण,
	अणु FSL_XCVR_ISR_TOG,	0x00000000 पूर्ण,
	अणु FSL_XCVR_RX_DPTH_CTRL,	0x00002C89 पूर्ण,
	अणु FSL_XCVR_RX_DPTH_CTRL_SET,	0x00002C89 पूर्ण,
	अणु FSL_XCVR_RX_DPTH_CTRL_CLR,	0x00002C89 पूर्ण,
	अणु FSL_XCVR_RX_DPTH_CTRL_TOG,	0x00002C89 पूर्ण,
	अणु FSL_XCVR_TX_DPTH_CTRL,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_DPTH_CTRL_SET,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_DPTH_CTRL_CLR,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_DPTH_CTRL_TOG,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_0,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_1,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_2,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_3,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_4,	0x00000000 पूर्ण,
	अणु FSL_XCVR_TX_CS_DATA_5,	0x00000000 पूर्ण,
	अणु FSL_XCVR_DEBUG_REG_0,		0x00000000 पूर्ण,
	अणु FSL_XCVR_DEBUG_REG_1,		0x00000000 पूर्ण,
पूर्ण;

अटल bool fsl_xcvr_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FSL_XCVR_VERSION:
	हाल FSL_XCVR_EXT_CTRL:
	हाल FSL_XCVR_EXT_STATUS:
	हाल FSL_XCVR_EXT_IER0:
	हाल FSL_XCVR_EXT_IER1:
	हाल FSL_XCVR_EXT_ISR:
	हाल FSL_XCVR_EXT_ISR_SET:
	हाल FSL_XCVR_EXT_ISR_CLR:
	हाल FSL_XCVR_EXT_ISR_TOG:
	हाल FSL_XCVR_IER:
	हाल FSL_XCVR_ISR:
	हाल FSL_XCVR_ISR_SET:
	हाल FSL_XCVR_ISR_CLR:
	हाल FSL_XCVR_ISR_TOG:
	हाल FSL_XCVR_PHY_AI_CTRL:
	हाल FSL_XCVR_PHY_AI_CTRL_SET:
	हाल FSL_XCVR_PHY_AI_CTRL_CLR:
	हाल FSL_XCVR_PHY_AI_CTRL_TOG:
	हाल FSL_XCVR_PHY_AI_RDATA:
	हाल FSL_XCVR_CLK_CTRL:
	हाल FSL_XCVR_RX_DPTH_CTRL:
	हाल FSL_XCVR_RX_DPTH_CTRL_SET:
	हाल FSL_XCVR_RX_DPTH_CTRL_CLR:
	हाल FSL_XCVR_RX_DPTH_CTRL_TOG:
	हाल FSL_XCVR_TX_DPTH_CTRL:
	हाल FSL_XCVR_TX_DPTH_CTRL_SET:
	हाल FSL_XCVR_TX_DPTH_CTRL_CLR:
	हाल FSL_XCVR_TX_DPTH_CTRL_TOG:
	हाल FSL_XCVR_TX_CS_DATA_0:
	हाल FSL_XCVR_TX_CS_DATA_1:
	हाल FSL_XCVR_TX_CS_DATA_2:
	हाल FSL_XCVR_TX_CS_DATA_3:
	हाल FSL_XCVR_TX_CS_DATA_4:
	हाल FSL_XCVR_TX_CS_DATA_5:
	हाल FSL_XCVR_DEBUG_REG_0:
	हाल FSL_XCVR_DEBUG_REG_1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_xcvr_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FSL_XCVR_EXT_CTRL:
	हाल FSL_XCVR_EXT_IER0:
	हाल FSL_XCVR_EXT_IER1:
	हाल FSL_XCVR_EXT_ISR:
	हाल FSL_XCVR_EXT_ISR_SET:
	हाल FSL_XCVR_EXT_ISR_CLR:
	हाल FSL_XCVR_EXT_ISR_TOG:
	हाल FSL_XCVR_IER:
	हाल FSL_XCVR_ISR_SET:
	हाल FSL_XCVR_ISR_CLR:
	हाल FSL_XCVR_ISR_TOG:
	हाल FSL_XCVR_PHY_AI_CTRL:
	हाल FSL_XCVR_PHY_AI_CTRL_SET:
	हाल FSL_XCVR_PHY_AI_CTRL_CLR:
	हाल FSL_XCVR_PHY_AI_CTRL_TOG:
	हाल FSL_XCVR_PHY_AI_WDATA:
	हाल FSL_XCVR_CLK_CTRL:
	हाल FSL_XCVR_RX_DPTH_CTRL:
	हाल FSL_XCVR_RX_DPTH_CTRL_SET:
	हाल FSL_XCVR_RX_DPTH_CTRL_CLR:
	हाल FSL_XCVR_RX_DPTH_CTRL_TOG:
	हाल FSL_XCVR_TX_DPTH_CTRL_SET:
	हाल FSL_XCVR_TX_DPTH_CTRL_CLR:
	हाल FSL_XCVR_TX_DPTH_CTRL_TOG:
	हाल FSL_XCVR_TX_CS_DATA_0:
	हाल FSL_XCVR_TX_CS_DATA_1:
	हाल FSL_XCVR_TX_CS_DATA_2:
	हाल FSL_XCVR_TX_CS_DATA_3:
	हाल FSL_XCVR_TX_CS_DATA_4:
	हाल FSL_XCVR_TX_CS_DATA_5:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_xcvr_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस fsl_xcvr_पढ़ोable_reg(dev, reg);
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_xcvr_regmap_cfg = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = FSL_XCVR_MAX_REG,
	.reg_शेषs = fsl_xcvr_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_xcvr_reg_शेषs),
	.पढ़ोable_reg = fsl_xcvr_पढ़ोable_reg,
	.अस्थिर_reg = fsl_xcvr_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_xcvr_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल irqवापस_t irq0_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_xcvr *xcvr = (काष्ठा fsl_xcvr *)devid;
	काष्ठा device *dev = &xcvr->pdev->dev;
	काष्ठा regmap *regmap = xcvr->regmap;
	व्योम __iomem *reg_ctrl, *reg_buff;
	u32 isr, isr_clr = 0, val, i;

	regmap_पढ़ो(regmap, FSL_XCVR_EXT_ISR, &isr);

	अगर (isr & FSL_XCVR_IRQ_NEW_CS) अणु
		dev_dbg(dev, "Received new CS block\n");
		isr_clr |= FSL_XCVR_IRQ_NEW_CS;
		/* Data RAM is 4KiB, last two pages: 8 and 9. Select page 8. */
		regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
				   FSL_XCVR_EXT_CTRL_PAGE_MASK,
				   FSL_XCVR_EXT_CTRL_PAGE(8));

		/* Find updated CS buffer */
		reg_ctrl = xcvr->ram_addr + FSL_XCVR_RX_CS_CTRL_0;
		reg_buff = xcvr->ram_addr + FSL_XCVR_RX_CS_BUFF_0;
		स_नकल_fromio(&val, reg_ctrl, माप(val));
		अगर (!val) अणु
			reg_ctrl = xcvr->ram_addr + FSL_XCVR_RX_CS_CTRL_1;
			reg_buff = xcvr->ram_addr + FSL_XCVR_RX_CS_BUFF_1;
			स_नकल_fromio(&val, reg_ctrl, माप(val));
		पूर्ण

		अगर (val) अणु
			/* copy CS buffer */
			स_नकल_fromio(&xcvr->rx_iec958.status, reg_buff,
				      माप(xcvr->rx_iec958.status));
			क्रम (i = 0; i < 6; i++) अणु
				val = *(u32 *)(xcvr->rx_iec958.status + i*4);
				*(u32 *)(xcvr->rx_iec958.status + i*4) =
					bitrev32(val);
			पूर्ण
			/* clear CS control रेजिस्टर */
			स_रखो_io(reg_ctrl, 0, माप(val));
		पूर्ण
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_NEW_UD) अणु
		dev_dbg(dev, "Received new UD block\n");
		isr_clr |= FSL_XCVR_IRQ_NEW_UD;
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_MUTE) अणु
		dev_dbg(dev, "HW mute bit detected\n");
		isr_clr |= FSL_XCVR_IRQ_MUTE;
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_FIFO_UOFL_ERR) अणु
		dev_dbg(dev, "RX/TX FIFO full/empty\n");
		isr_clr |= FSL_XCVR_IRQ_FIFO_UOFL_ERR;
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_ARC_MODE) अणु
		dev_dbg(dev, "CMDC SM falls out of eARC mode\n");
		isr_clr |= FSL_XCVR_IRQ_ARC_MODE;
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_DMA_RD_REQ) अणु
		dev_dbg(dev, "DMA read request\n");
		isr_clr |= FSL_XCVR_IRQ_DMA_RD_REQ;
	पूर्ण
	अगर (isr & FSL_XCVR_IRQ_DMA_WR_REQ) अणु
		dev_dbg(dev, "DMA write request\n");
		isr_clr |= FSL_XCVR_IRQ_DMA_WR_REQ;
	पूर्ण

	अगर (isr_clr) अणु
		regmap_ग_लिखो(regmap, FSL_XCVR_EXT_ISR_CLR, isr_clr);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा fsl_xcvr_soc_data fsl_xcvr_imx8mp_data = अणु
	.fw_name = "imx/xcvr/xcvr-imx8mp.bin",
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_xcvr_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8mp-xcvr", .data = &fsl_xcvr_imx8mp_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_xcvr_dt_ids);

अटल पूर्णांक fsl_xcvr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fsl_xcvr *xcvr;
	काष्ठा resource *rx_res, *tx_res;
	व्योम __iomem *regs;
	पूर्णांक ret, irq;

	xcvr = devm_kzalloc(dev, माप(*xcvr), GFP_KERNEL);
	अगर (!xcvr)
		वापस -ENOMEM;

	xcvr->pdev = pdev;
	xcvr->soc_data = of_device_get_match_data(&pdev->dev);

	xcvr->ipg_clk = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(xcvr->ipg_clk)) अणु
		dev_err(dev, "failed to get ipg clock\n");
		वापस PTR_ERR(xcvr->ipg_clk);
	पूर्ण

	xcvr->phy_clk = devm_clk_get(dev, "phy");
	अगर (IS_ERR(xcvr->phy_clk)) अणु
		dev_err(dev, "failed to get phy clock\n");
		वापस PTR_ERR(xcvr->phy_clk);
	पूर्ण

	xcvr->spba_clk = devm_clk_get(dev, "spba");
	अगर (IS_ERR(xcvr->spba_clk)) अणु
		dev_err(dev, "failed to get spba clock\n");
		वापस PTR_ERR(xcvr->spba_clk);
	पूर्ण

	xcvr->pll_ipg_clk = devm_clk_get(dev, "pll_ipg");
	अगर (IS_ERR(xcvr->pll_ipg_clk)) अणु
		dev_err(dev, "failed to get pll_ipg clock\n");
		वापस PTR_ERR(xcvr->pll_ipg_clk);
	पूर्ण

	xcvr->ram_addr = devm_platक्रमm_ioremap_resource_byname(pdev, "ram");
	अगर (IS_ERR(xcvr->ram_addr))
		वापस PTR_ERR(xcvr->ram_addr);

	regs = devm_platक्रमm_ioremap_resource_byname(pdev, "regs");
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	xcvr->regmap = devm_regmap_init_mmio_clk(dev, शून्य, regs,
						 &fsl_xcvr_regmap_cfg);
	अगर (IS_ERR(xcvr->regmap)) अणु
		dev_err(dev, "failed to init XCVR regmap: %ld\n",
			PTR_ERR(xcvr->regmap));
		वापस PTR_ERR(xcvr->regmap);
	पूर्ण

	xcvr->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(xcvr->reset)) अणु
		dev_err(dev, "failed to get XCVR reset control\n");
		वापस PTR_ERR(xcvr->reset);
	पूर्ण

	/* get IRQs */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "no irq[0]: %d\n", irq);
		वापस irq;
	पूर्ण

	ret = devm_request_irq(dev, irq, irq0_isr, 0, pdev->name, xcvr);
	अगर (ret) अणु
		dev_err(dev, "failed to claim IRQ0: %i\n", ret);
		वापस ret;
	पूर्ण

	rx_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rxfifo");
	tx_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "txfifo");
	xcvr->dma_prms_rx.chan_name = "rx";
	xcvr->dma_prms_tx.chan_name = "tx";
	xcvr->dma_prms_rx.addr = rx_res->start;
	xcvr->dma_prms_tx.addr = tx_res->start;
	xcvr->dma_prms_rx.maxburst = FSL_XCVR_MAXBURST_RX;
	xcvr->dma_prms_tx.maxburst = FSL_XCVR_MAXBURST_TX;

	platक्रमm_set_drvdata(pdev, xcvr);
	pm_runसमय_enable(dev);
	regcache_cache_only(xcvr->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &fsl_xcvr_comp,
					      &fsl_xcvr_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to register component %s\n",
			fsl_xcvr_comp.name);
		वापस ret;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev, शून्य, 0);
	अगर (ret)
		dev_err(dev, "failed to pcm register\n");

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक fsl_xcvr_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_xcvr *xcvr = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Assert M0+ reset */
	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
				 FSL_XCVR_EXT_CTRL_CORE_RESET,
				 FSL_XCVR_EXT_CTRL_CORE_RESET);
	अगर (ret < 0)
		dev_err(dev, "Failed to assert M0+ core: %d\n", ret);

	regcache_cache_only(xcvr->regmap, true);

	clk_disable_unprepare(xcvr->spba_clk);
	clk_disable_unprepare(xcvr->phy_clk);
	clk_disable_unprepare(xcvr->pll_ipg_clk);
	clk_disable_unprepare(xcvr->ipg_clk);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक fsl_xcvr_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_xcvr *xcvr = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = reset_control_निश्चित(xcvr->reset);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to assert M0+ reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(xcvr->ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to start IPG clock.\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(xcvr->pll_ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to start PLL IPG clock.\n");
		जाओ stop_ipg_clk;
	पूर्ण

	ret = clk_prepare_enable(xcvr->phy_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to start PHY clock: %d\n", ret);
		जाओ stop_pll_ipg_clk;
	पूर्ण

	ret = clk_prepare_enable(xcvr->spba_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to start SPBA clock.\n");
		जाओ stop_phy_clk;
	पूर्ण

	regcache_cache_only(xcvr->regmap, false);
	regcache_mark_dirty(xcvr->regmap);
	ret = regcache_sync(xcvr->regmap);

	अगर (ret) अणु
		dev_err(dev, "failed to sync regcache.\n");
		जाओ stop_spba_clk;
	पूर्ण

	ret = reset_control_deनिश्चित(xcvr->reset);
	अगर (ret) अणु
		dev_err(dev, "failed to deassert M0+ reset.\n");
		जाओ stop_spba_clk;
	पूर्ण

	ret = fsl_xcvr_load_firmware(xcvr);
	अगर (ret) अणु
		dev_err(dev, "failed to load firmware.\n");
		जाओ stop_spba_clk;
	पूर्ण

	/* Release M0+ reset */
	ret = regmap_update_bits(xcvr->regmap, FSL_XCVR_EXT_CTRL,
				 FSL_XCVR_EXT_CTRL_CORE_RESET, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "M0+ core release failed: %d\n", ret);
		जाओ stop_spba_clk;
	पूर्ण

	/* Let M0+ core complete firmware initialization */
	msleep(50);

	वापस 0;

stop_spba_clk:
	clk_disable_unprepare(xcvr->spba_clk);
stop_phy_clk:
	clk_disable_unprepare(xcvr->phy_clk);
stop_pll_ipg_clk:
	clk_disable_unprepare(xcvr->pll_ipg_clk);
stop_ipg_clk:
	clk_disable_unprepare(xcvr->ipg_clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_xcvr_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_xcvr_runसमय_suspend,
			   fsl_xcvr_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_xcvr_driver = अणु
	.probe = fsl_xcvr_probe,
	.driver = अणु
		.name = "fsl,imx8mp-audio-xcvr",
		.pm = &fsl_xcvr_pm_ops,
		.of_match_table = fsl_xcvr_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_xcvr_driver);

MODULE_AUTHOR("Viorel Suman <viorel.suman@nxp.com>");
MODULE_DESCRIPTION("NXP Audio Transceiver (XCVR) driver");
MODULE_LICENSE("GPL v2");
