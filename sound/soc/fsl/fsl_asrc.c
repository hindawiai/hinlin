<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale ASRC ALSA SoC Digital Audio Interface (DAI) driver
//
// Copyright (C) 2014 Freescale Semiconductor, Inc.
//
// Author: Nicolin Chen <nicoleotsuka@gmail.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_asrc.h"

#घोषणा IDEAL_RATIO_DECIMAL_DEPTH 26

#घोषणा pair_err(fmt, ...) \
	dev_err(&asrc->pdev->dev, "Pair %c: " fmt, 'A' + index, ##__VA_ARGS__)

#घोषणा pair_dbg(fmt, ...) \
	dev_dbg(&asrc->pdev->dev, "Pair %c: " fmt, 'A' + index, ##__VA_ARGS__)

/* Corresponding to process_option */
अटल अचिन्हित पूर्णांक supported_asrc_rate[] = अणु
	5512, 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000,
	64000, 88200, 96000, 128000, 176400, 192000,
पूर्ण;

अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_asrc_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(supported_asrc_rate),
	.list = supported_asrc_rate,
पूर्ण;

/*
 * The following tables map the relationship between asrc_inclk/asrc_outclk in
 * fsl_asrc.h and the रेजिस्टरs of ASRCSR
 */
अटल अचिन्हित अक्षर input_clk_map_imx35[ASRC_CLK_MAP_LEN] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
पूर्ण;

अटल अचिन्हित अक्षर output_clk_map_imx35[ASRC_CLK_MAP_LEN] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
पूर्ण;

/* i.MX53 uses the same map क्रम input and output */
अटल अचिन्हित अक्षर input_clk_map_imx53[ASRC_CLK_MAP_LEN] = अणु
/*	0x0  0x1  0x2  0x3  0x4  0x5  0x6  0x7  0x8  0x9  0xa  0xb  0xc  0xd  0xe  0xf */
	0x0, 0x1, 0x2, 0x7, 0x4, 0x5, 0x6, 0x3, 0x8, 0x9, 0xa, 0xb, 0xc, 0xf, 0xe, 0xd,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
पूर्ण;

अटल अचिन्हित अक्षर output_clk_map_imx53[ASRC_CLK_MAP_LEN] = अणु
/*	0x0  0x1  0x2  0x3  0x4  0x5  0x6  0x7  0x8  0x9  0xa  0xb  0xc  0xd  0xe  0xf */
	0x8, 0x9, 0xa, 0x7, 0xc, 0x5, 0x6, 0xb, 0x0, 0x1, 0x2, 0x3, 0x4, 0xf, 0xe, 0xd,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
पूर्ण;

/*
 * i.MX8QM/i.MX8QXP uses the same map क्रम input and output.
 * clk_map_imx8qm[0] is क्रम i.MX8QM asrc0
 * clk_map_imx8qm[1] is क्रम i.MX8QM asrc1
 * clk_map_imx8qxp[0] is क्रम i.MX8QXP asrc0
 * clk_map_imx8qxp[1] is क्रम i.MX8QXP asrc1
 */
अटल अचिन्हित अक्षर clk_map_imx8qm[2][ASRC_CLK_MAP_LEN] = अणु
	अणु
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	पूर्ण,
	अणु
	0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0xb, 0xc, 0xf, 0xf, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	0x4, 0x5, 0x6, 0xf, 0x8, 0x9, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर clk_map_imx8qxp[2][ASRC_CLK_MAP_LEN] = अणु
	अणु
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0xf, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xf, 0xf,
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	पूर्ण,
	अणु
	0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x7, 0x8, 0xf, 0xf, 0x9, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	0xf, 0xf, 0x6, 0xf, 0xf, 0xf, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	पूर्ण,
पूर्ण;

/**
 * fsl_asrc_sel_proc - Select the pre-processing and post-processing options
 * @inrate: input sample rate
 * @outrate: output sample rate
 * @pre_proc: वापस value क्रम pre-processing option
 * @post_proc: वापस value क्रम post-processing option
 *
 * Make sure to exclude following unsupported हालs beक्रमe
 * calling this function:
 * 1) inrate > 8.125 * outrate
 * 2) inrate > 16.125 * outrate
 *
 */
अटल व्योम fsl_asrc_sel_proc(पूर्णांक inrate, पूर्णांक outrate,
			     पूर्णांक *pre_proc, पूर्णांक *post_proc)
अणु
	bool post_proc_cond2;
	bool post_proc_cond0;

	/* select pre_proc between [0, 2] */
	अगर (inrate * 8 > 33 * outrate)
		*pre_proc = 2;
	अन्यथा अगर (inrate * 8 > 15 * outrate) अणु
		अगर (inrate > 152000)
			*pre_proc = 2;
		अन्यथा
			*pre_proc = 1;
	पूर्ण अन्यथा अगर (inrate < 76000)
		*pre_proc = 0;
	अन्यथा अगर (inrate > 152000)
		*pre_proc = 2;
	अन्यथा
		*pre_proc = 1;

	/* Condition क्रम selection of post-processing */
	post_proc_cond2 = (inrate * 15 > outrate * 16 && outrate < 56000) ||
			  (inrate > 56000 && outrate < 56000);
	post_proc_cond0 = inrate * 23 < outrate * 8;

	अगर (post_proc_cond2)
		*post_proc = 2;
	अन्यथा अगर (post_proc_cond0)
		*post_proc = 0;
	अन्यथा
		*post_proc = 1;
पूर्ण

/**
 * fsl_asrc_request_pair - Request ASRC pair
 * @channels: number of channels
 * @pair: poपूर्णांकer to pair
 *
 * It assigns pair by the order of A->C->B because allocation of pair B,
 * within range [ANCA, ANCA+ANCB-1], depends on the channels of pair A
 * जबतक pair A and pair C are comparatively independent.
 */
अटल पूर्णांक fsl_asrc_request_pair(पूर्णांक channels, काष्ठा fsl_asrc_pair *pair)
अणु
	क्रमागत asrc_pair_index index = ASRC_INVALID_PAIR;
	काष्ठा fsl_asrc *asrc = pair->asrc;
	काष्ठा device *dev = &asrc->pdev->dev;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक i, ret = 0;

	spin_lock_irqsave(&asrc->lock, lock_flags);

	क्रम (i = ASRC_PAIR_A; i < ASRC_PAIR_MAX_NUM; i++) अणु
		अगर (asrc->pair[i] != शून्य)
			जारी;

		index = i;

		अगर (i != ASRC_PAIR_B)
			अवरोध;
	पूर्ण

	अगर (index == ASRC_INVALID_PAIR) अणु
		dev_err(dev, "all pairs are busy now\n");
		ret = -EBUSY;
	पूर्ण अन्यथा अगर (asrc->channel_avail < channels) अणु
		dev_err(dev, "can't afford required channels: %d\n", channels);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		asrc->channel_avail -= channels;
		asrc->pair[index] = pair;
		pair->channels = channels;
		pair->index = index;
	पूर्ण

	spin_unlock_irqrestore(&asrc->lock, lock_flags);

	वापस ret;
पूर्ण

/**
 * fsl_asrc_release_pair - Release ASRC pair
 * @pair: pair to release
 *
 * It clears the resource from asrc and releases the occupied channels.
 */
अटल व्योम fsl_asrc_release_pair(काष्ठा fsl_asrc_pair *pair)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;
	अचिन्हित दीर्घ lock_flags;

	/* Make sure the pair is disabled */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), 0);

	spin_lock_irqsave(&asrc->lock, lock_flags);

	asrc->channel_avail += pair->channels;
	asrc->pair[index] = शून्य;
	pair->error = 0;

	spin_unlock_irqrestore(&asrc->lock, lock_flags);
पूर्ण

/**
 * fsl_asrc_set_watermarks- configure input and output thresholds
 * @pair: poपूर्णांकer to pair
 * @in: input threshold
 * @out: output threshold
 */
अटल व्योम fsl_asrc_set_watermarks(काष्ठा fsl_asrc_pair *pair, u32 in, u32 out)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;

	regmap_update_bits(asrc->regmap, REG_ASRMCR(index),
			   ASRMCRi_EXTTHRSHi_MASK |
			   ASRMCRi_INFIFO_THRESHOLD_MASK |
			   ASRMCRi_OUTFIFO_THRESHOLD_MASK,
			   ASRMCRi_EXTTHRSHi |
			   ASRMCRi_INFIFO_THRESHOLD(in) |
			   ASRMCRi_OUTFIFO_THRESHOLD(out));
पूर्ण

/**
 * fsl_asrc_cal_asrck_भागisor - Calculate the total भागisor between asrck घड़ी rate and sample rate
 * @pair: poपूर्णांकer to pair
 * @भाग: भागider
 *
 * It follows the क्रमmula clk_rate = samplerate * (2 ^ prescaler) * भागider
 */
अटल u32 fsl_asrc_cal_asrck_भागisor(काष्ठा fsl_asrc_pair *pair, u32 भाग)
अणु
	u32 ps;

	/* Calculate the भागisors: prescaler [2^0, 2^7], भागder [1, 8] */
	क्रम (ps = 0; भाग > 8; ps++)
		भाग >>= 1;

	वापस ((भाग - 1) << ASRCDRi_AxCPi_WIDTH) | ps;
पूर्ण

/**
 * fsl_asrc_set_ideal_ratio - Calculate and set the ratio क्रम Ideal Ratio mode only
 * @pair: poपूर्णांकer to pair
 * @inrate: input rate
 * @outrate: output rate
 *
 * The ratio is a 32-bit fixed poपूर्णांक value with 26 fractional bits.
 */
अटल पूर्णांक fsl_asrc_set_ideal_ratio(काष्ठा fsl_asrc_pair *pair,
				    पूर्णांक inrate, पूर्णांक outrate)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;
	अचिन्हित दीर्घ ratio;
	पूर्णांक i;

	अगर (!outrate) अणु
		pair_err("output rate should not be zero\n");
		वापस -EINVAL;
	पूर्ण

	/* Calculate the पूर्णांकergal part of the ratio */
	ratio = (inrate / outrate) << IDEAL_RATIO_DECIMAL_DEPTH;

	/* ... and then the 26 depth decimal part */
	inrate %= outrate;

	क्रम (i = 1; i <= IDEAL_RATIO_DECIMAL_DEPTH; i++) अणु
		inrate <<= 1;

		अगर (inrate < outrate)
			जारी;

		ratio |= 1 << (IDEAL_RATIO_DECIMAL_DEPTH - i);
		inrate -= outrate;

		अगर (!inrate)
			अवरोध;
	पूर्ण

	regmap_ग_लिखो(asrc->regmap, REG_ASRIDRL(index), ratio);
	regmap_ग_लिखो(asrc->regmap, REG_ASRIDRH(index), ratio >> 24);

	वापस 0;
पूर्ण

/**
 * fsl_asrc_config_pair - Configure the asचिन्हित ASRC pair
 * @pair: poपूर्णांकer to pair
 * @use_ideal_rate: boolean configuration
 *
 * It configures those ASRC रेजिस्टरs according to a configuration instance
 * of काष्ठा asrc_config which includes in/output sample rate, width, channel
 * and घड़ी settings.
 *
 * Note:
 * The ideal ratio configuration can work with a flexible घड़ी rate setting.
 * Using IDEAL_RATIO_RATE gives a faster converting speed but overloads ASRC.
 * For a regular audio playback, the घड़ी rate should not be slower than an
 * घड़ी rate aligning with the output sample rate; For a use हाल requiring
 * faster conversion, set use_ideal_rate to have the faster speed.
 */
अटल पूर्णांक fsl_asrc_config_pair(काष्ठा fsl_asrc_pair *pair, bool use_ideal_rate)
अणु
	काष्ठा fsl_asrc_pair_priv *pair_priv = pair->निजी;
	काष्ठा asrc_config *config = pair_priv->config;
	काष्ठा fsl_asrc *asrc = pair->asrc;
	काष्ठा fsl_asrc_priv *asrc_priv = asrc->निजी;
	क्रमागत asrc_pair_index index = pair->index;
	क्रमागत asrc_word_width input_word_width;
	क्रमागत asrc_word_width output_word_width;
	u32 inrate, outrate, inभाग, outभाग;
	u32 clk_index[2], भाग[2], rem[2];
	u64 clk_rate;
	पूर्णांक in, out, channels;
	पूर्णांक pre_proc, post_proc;
	काष्ठा clk *clk;
	bool ideal;

	अगर (!config) अणु
		pair_err("invalid pair config\n");
		वापस -EINVAL;
	पूर्ण

	/* Validate channels */
	अगर (config->channel_num < 1 || config->channel_num > 10) अणु
		pair_err("does not support %d channels\n", config->channel_num);
		वापस -EINVAL;
	पूर्ण

	चयन (snd_pcm_क्रमmat_width(config->input_क्रमmat)) अणु
	हाल 8:
		input_word_width = ASRC_WIDTH_8_BIT;
		अवरोध;
	हाल 16:
		input_word_width = ASRC_WIDTH_16_BIT;
		अवरोध;
	हाल 24:
		input_word_width = ASRC_WIDTH_24_BIT;
		अवरोध;
	शेष:
		pair_err("does not support this input format, %d\n",
			 config->input_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	चयन (snd_pcm_क्रमmat_width(config->output_क्रमmat)) अणु
	हाल 16:
		output_word_width = ASRC_WIDTH_16_BIT;
		अवरोध;
	हाल 24:
		output_word_width = ASRC_WIDTH_24_BIT;
		अवरोध;
	शेष:
		pair_err("does not support this output format, %d\n",
			 config->output_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	inrate = config->input_sample_rate;
	outrate = config->output_sample_rate;
	ideal = config->inclk == INCLK_NONE;

	/* Validate input and output sample rates */
	क्रम (in = 0; in < ARRAY_SIZE(supported_asrc_rate); in++)
		अगर (inrate == supported_asrc_rate[in])
			अवरोध;

	अगर (in == ARRAY_SIZE(supported_asrc_rate)) अणु
		pair_err("unsupported input sample rate: %dHz\n", inrate);
		वापस -EINVAL;
	पूर्ण

	क्रम (out = 0; out < ARRAY_SIZE(supported_asrc_rate); out++)
		अगर (outrate == supported_asrc_rate[out])
			अवरोध;

	अगर (out == ARRAY_SIZE(supported_asrc_rate)) अणु
		pair_err("unsupported output sample rate: %dHz\n", outrate);
		वापस -EINVAL;
	पूर्ण

	अगर ((outrate >= 5512 && outrate <= 30000) &&
	    (outrate > 24 * inrate || inrate > 8 * outrate)) अणु
		pair_err("exceed supported ratio range [1/24, 8] क्रम \
				inrate/outrate: %d/%d\न", inrate, outrate);
		वापस -EINVAL;
	पूर्ण

	/* Validate input and output घड़ी sources */
	clk_index[IN] = asrc_priv->clk_map[IN][config->inclk];
	clk_index[OUT] = asrc_priv->clk_map[OUT][config->outclk];

	/* We only have output घड़ी क्रम ideal ratio mode */
	clk = asrc_priv->asrck_clk[clk_index[ideal ? OUT : IN]];

	clk_rate = clk_get_rate(clk);
	rem[IN] = करो_भाग(clk_rate, inrate);
	भाग[IN] = (u32)clk_rate;

	/*
	 * The भागider range is [1, 1024], defined by the hardware. For non-
	 * ideal ratio configuration, घड़ी rate has to be strictly aligned
	 * with the sample rate. For ideal ratio configuration, घड़ी rates
	 * only result in dअगरferent converting speeds. So reमुख्यder करोes not
	 * matter, as दीर्घ as we keep the भागider within its valid range.
	 */
	अगर (भाग[IN] == 0 || (!ideal && (भाग[IN] > 1024 || rem[IN] != 0))) अणु
		pair_err("failed to support input sample rate %dHz by asrck_%x\n",
				inrate, clk_index[ideal ? OUT : IN]);
		वापस -EINVAL;
	पूर्ण

	भाग[IN] = min_t(u32, 1024, भाग[IN]);

	clk = asrc_priv->asrck_clk[clk_index[OUT]];
	clk_rate = clk_get_rate(clk);
	अगर (ideal && use_ideal_rate)
		rem[OUT] = करो_भाग(clk_rate, IDEAL_RATIO_RATE);
	अन्यथा
		rem[OUT] = करो_भाग(clk_rate, outrate);
	भाग[OUT] = clk_rate;

	/* Output भागider has the same limitation as the input one */
	अगर (भाग[OUT] == 0 || (!ideal && (भाग[OUT] > 1024 || rem[OUT] != 0))) अणु
		pair_err("failed to support output sample rate %dHz by asrck_%x\n",
				outrate, clk_index[OUT]);
		वापस -EINVAL;
	पूर्ण

	भाग[OUT] = min_t(u32, 1024, भाग[OUT]);

	/* Set the channel number */
	channels = config->channel_num;

	अगर (asrc_priv->soc->channel_bits < 4)
		channels /= 2;

	/* Update channels क्रम current pair */
	regmap_update_bits(asrc->regmap, REG_ASRCNCR,
			   ASRCNCR_ANCi_MASK(index, asrc_priv->soc->channel_bits),
			   ASRCNCR_ANCi(index, channels, asrc_priv->soc->channel_bits));

	/* Default setting: Automatic selection क्रम processing mode */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ATSi_MASK(index), ASRCTR_ATS(index));
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_USRi_MASK(index), 0);

	/* Set the input and output घड़ी sources */
	regmap_update_bits(asrc->regmap, REG_ASRCSR,
			   ASRCSR_AICSi_MASK(index) | ASRCSR_AOCSi_MASK(index),
			   ASRCSR_AICS(index, clk_index[IN]) |
			   ASRCSR_AOCS(index, clk_index[OUT]));

	/* Calculate the input घड़ी भागisors */
	inभाग = fsl_asrc_cal_asrck_भागisor(pair, भाग[IN]);
	outभाग = fsl_asrc_cal_asrck_भागisor(pair, भाग[OUT]);

	/* Suppose inभाग and outभाग includes prescaler, so add its MASK too */
	regmap_update_bits(asrc->regmap, REG_ASRCDR(index),
			   ASRCDRi_AOCPi_MASK(index) | ASRCDRi_AICPi_MASK(index) |
			   ASRCDRi_AOCDi_MASK(index) | ASRCDRi_AICDi_MASK(index),
			   ASRCDRi_AOCP(index, outभाग) | ASRCDRi_AICP(index, inभाग));

	/* Implement word_width configurations */
	regmap_update_bits(asrc->regmap, REG_ASRMCR1(index),
			   ASRMCR1i_OW16_MASK | ASRMCR1i_IWD_MASK,
			   ASRMCR1i_OW16(output_word_width) |
			   ASRMCR1i_IWD(input_word_width));

	/* Enable BUFFER STALL */
	regmap_update_bits(asrc->regmap, REG_ASRMCR(index),
			   ASRMCRi_BUFSTALLi_MASK, ASRMCRi_BUFSTALLi);

	/* Set शेष thresholds क्रम input and output FIFO */
	fsl_asrc_set_watermarks(pair, ASRC_INPUTFIFO_THRESHOLD,
				ASRC_INPUTFIFO_THRESHOLD);

	/* Configure the following only क्रम Ideal Ratio mode */
	अगर (!ideal)
		वापस 0;

	/* Clear ASTSx bit to use Ideal Ratio mode */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ATSi_MASK(index), 0);

	/* Enable Ideal Ratio mode */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_IDRi_MASK(index) | ASRCTR_USRi_MASK(index),
			   ASRCTR_IDR(index) | ASRCTR_USR(index));

	fsl_asrc_sel_proc(inrate, outrate, &pre_proc, &post_proc);

	/* Apply configurations क्रम pre- and post-processing */
	regmap_update_bits(asrc->regmap, REG_ASRCFG,
			   ASRCFG_PREMODi_MASK(index) |	ASRCFG_POSTMODi_MASK(index),
			   ASRCFG_PREMOD(index, pre_proc) |
			   ASRCFG_POSTMOD(index, post_proc));

	वापस fsl_asrc_set_ideal_ratio(pair, inrate, outrate);
पूर्ण

/**
 * fsl_asrc_start_pair - Start the asचिन्हित ASRC pair
 * @pair: poपूर्णांकer to pair
 *
 * It enables the asचिन्हित pair and makes it stopped at the stall level.
 */
अटल व्योम fsl_asrc_start_pair(काष्ठा fsl_asrc_pair *pair)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;
	पूर्णांक reg, retry = 10, i;

	/* Enable the current pair */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), ASRCTR_ASRCE(index));

	/* Wait क्रम status of initialization */
	करो अणु
		udelay(5);
		regmap_पढ़ो(asrc->regmap, REG_ASRCFG, &reg);
		reg &= ASRCFG_INIRQi_MASK(index);
	पूर्ण जबतक (!reg && --retry);

	/* Make the input fअगरo to ASRC STALL level */
	regmap_पढ़ो(asrc->regmap, REG_ASRCNCR, &reg);
	क्रम (i = 0; i < pair->channels * 4; i++)
		regmap_ग_लिखो(asrc->regmap, REG_ASRDI(index), 0);

	/* Enable overload पूर्णांकerrupt */
	regmap_ग_लिखो(asrc->regmap, REG_ASRIER, ASRIER_AOLIE);
पूर्ण

/**
 * fsl_asrc_stop_pair - Stop the asचिन्हित ASRC pair
 * @pair: poपूर्णांकer to pair
 */
अटल व्योम fsl_asrc_stop_pair(काष्ठा fsl_asrc_pair *pair)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;

	/* Stop the current pair */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), 0);
पूर्ण

/**
 * fsl_asrc_get_dma_channel- Get DMA channel according to the pair and direction.
 * @pair: poपूर्णांकer to pair
 * @dir: DMA direction
 */
अटल काष्ठा dma_chan *fsl_asrc_get_dma_channel(काष्ठा fsl_asrc_pair *pair,
						 bool dir)
अणु
	काष्ठा fsl_asrc *asrc = pair->asrc;
	क्रमागत asrc_pair_index index = pair->index;
	अक्षर name[4];

	प्र_लिखो(name, "%cx%c", dir == IN ? 'r' : 't', index + 'a');

	वापस dma_request_slave_channel(&asrc->pdev->dev, name);
पूर्ण

अटल पूर्णांक fsl_asrc_dai_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_asrc *asrc = snd_soc_dai_get_drvdata(dai);
	काष्ठा fsl_asrc_priv *asrc_priv = asrc->निजी;

	/* Odd channel number is not valid क्रम older ASRC (channel_bits==3) */
	अगर (asrc_priv->soc->channel_bits == 3)
		snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS, 2);


	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &fsl_asrc_rate_स्थिरraपूर्णांकs);
पूर्ण

/* Select proper घड़ी source क्रम पूर्णांकernal ratio mode */
अटल व्योम fsl_asrc_select_clk(काष्ठा fsl_asrc_priv *asrc_priv,
				काष्ठा fsl_asrc_pair *pair,
				पूर्णांक in_rate,
				पूर्णांक out_rate)
अणु
	काष्ठा fsl_asrc_pair_priv *pair_priv = pair->निजी;
	काष्ठा asrc_config *config = pair_priv->config;
	पूर्णांक rate[2], select_clk[2]; /* Array size 2 means IN and OUT */
	पूर्णांक clk_rate, clk_index;
	पूर्णांक i, j;

	rate[IN] = in_rate;
	rate[OUT] = out_rate;

	/* Select proper घड़ी source क्रम पूर्णांकernal ratio mode */
	क्रम (j = 0; j < 2; j++) अणु
		क्रम (i = 0; i < ASRC_CLK_MAP_LEN; i++) अणु
			clk_index = asrc_priv->clk_map[j][i];
			clk_rate = clk_get_rate(asrc_priv->asrck_clk[clk_index]);
			/* Only match a perfect घड़ी source with no reमुख्यder */
			अगर (clk_rate != 0 && (clk_rate / rate[j]) <= 1024 &&
			    (clk_rate % rate[j]) == 0)
				अवरोध;
		पूर्ण

		select_clk[j] = i;
	पूर्ण

	/* Switch to ideal ratio mode अगर there is no proper घड़ी source */
	अगर (select_clk[IN] == ASRC_CLK_MAP_LEN || select_clk[OUT] == ASRC_CLK_MAP_LEN) अणु
		select_clk[IN] = INCLK_NONE;
		select_clk[OUT] = OUTCLK_ASRCK1_CLK;
	पूर्ण

	config->inclk = select_clk[IN];
	config->outclk = select_clk[OUT];
पूर्ण

अटल पूर्णांक fsl_asrc_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_asrc *asrc = snd_soc_dai_get_drvdata(dai);
	काष्ठा fsl_asrc_priv *asrc_priv = asrc->निजी;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;
	काष्ठा fsl_asrc_pair_priv *pair_priv = pair->निजी;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	काष्ठा asrc_config config;
	पूर्णांक ret;

	ret = fsl_asrc_request_pair(channels, pair);
	अगर (ret) अणु
		dev_err(dai->dev, "fail to request asrc pair\n");
		वापस ret;
	पूर्ण

	pair_priv->config = &config;

	config.pair = pair->index;
	config.channel_num = channels;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		config.input_क्रमmat   = params_क्रमmat(params);
		config.output_क्रमmat  = asrc->asrc_क्रमmat;
		config.input_sample_rate  = rate;
		config.output_sample_rate = asrc->asrc_rate;
	पूर्ण अन्यथा अणु
		config.input_क्रमmat   = asrc->asrc_क्रमmat;
		config.output_क्रमmat  = params_क्रमmat(params);
		config.input_sample_rate  = asrc->asrc_rate;
		config.output_sample_rate = rate;
	पूर्ण

	fsl_asrc_select_clk(asrc_priv, pair,
			    config.input_sample_rate,
			    config.output_sample_rate);

	ret = fsl_asrc_config_pair(pair, false);
	अगर (ret) अणु
		dev_err(dai->dev, "fail to config asrc pair\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;

	अगर (pair)
		fsl_asrc_release_pair(pair);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *pair = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		fsl_asrc_start_pair(pair);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		fsl_asrc_stop_pair(pair);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_asrc_dai_ops = अणु
	.startup      = fsl_asrc_dai_startup,
	.hw_params    = fsl_asrc_dai_hw_params,
	.hw_मुक्त      = fsl_asrc_dai_hw_मुक्त,
	.trigger      = fsl_asrc_dai_trigger,
पूर्ण;

अटल पूर्णांक fsl_asrc_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_asrc *asrc = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &asrc->dma_params_tx,
				  &asrc->dma_params_rx);

	वापस 0;
पूर्ण

#घोषणा FSL_ASRC_FORMATS	(SNDRV_PCM_FMTBIT_S24_LE | \
				 SNDRV_PCM_FMTBIT_S16_LE | \
				 SNDRV_PCM_FMTBIT_S24_3LE)

अटल काष्ठा snd_soc_dai_driver fsl_asrc_dai = अणु
	.probe = fsl_asrc_dai_probe,
	.playback = अणु
		.stream_name = "ASRC-Playback",
		.channels_min = 1,
		.channels_max = 10,
		.rate_min = 5512,
		.rate_max = 192000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_ASRC_FORMATS |
			   SNDRV_PCM_FMTBIT_S8,
	पूर्ण,
	.capture = अणु
		.stream_name = "ASRC-Capture",
		.channels_min = 1,
		.channels_max = 10,
		.rate_min = 5512,
		.rate_max = 192000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_ASRC_FORMATS,
	पूर्ण,
	.ops = &fsl_asrc_dai_ops,
पूर्ण;

अटल bool fsl_asrc_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ASRCTR:
	हाल REG_ASRIER:
	हाल REG_ASRCNCR:
	हाल REG_ASRCFG:
	हाल REG_ASRCSR:
	हाल REG_ASRCDR1:
	हाल REG_ASRCDR2:
	हाल REG_ASRSTR:
	हाल REG_ASRPM1:
	हाल REG_ASRPM2:
	हाल REG_ASRPM3:
	हाल REG_ASRPM4:
	हाल REG_ASRPM5:
	हाल REG_ASRTFR1:
	हाल REG_ASRCCR:
	हाल REG_ASRDOA:
	हाल REG_ASRDOB:
	हाल REG_ASRDOC:
	हाल REG_ASRIDRHA:
	हाल REG_ASRIDRLA:
	हाल REG_ASRIDRHB:
	हाल REG_ASRIDRLB:
	हाल REG_ASRIDRHC:
	हाल REG_ASRIDRLC:
	हाल REG_ASR76K:
	हाल REG_ASR56K:
	हाल REG_ASRMCRA:
	हाल REG_ASRFSTA:
	हाल REG_ASRMCRB:
	हाल REG_ASRFSTB:
	हाल REG_ASRMCRC:
	हाल REG_ASRFSTC:
	हाल REG_ASRMCR1A:
	हाल REG_ASRMCR1B:
	हाल REG_ASRMCR1C:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_asrc_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ASRSTR:
	हाल REG_ASRDIA:
	हाल REG_ASRDIB:
	हाल REG_ASRDIC:
	हाल REG_ASRDOA:
	हाल REG_ASRDOB:
	हाल REG_ASRDOC:
	हाल REG_ASRFSTA:
	हाल REG_ASRFSTB:
	हाल REG_ASRFSTC:
	हाल REG_ASRCFG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_asrc_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ASRCTR:
	हाल REG_ASRIER:
	हाल REG_ASRCNCR:
	हाल REG_ASRCFG:
	हाल REG_ASRCSR:
	हाल REG_ASRCDR1:
	हाल REG_ASRCDR2:
	हाल REG_ASRSTR:
	हाल REG_ASRPM1:
	हाल REG_ASRPM2:
	हाल REG_ASRPM3:
	हाल REG_ASRPM4:
	हाल REG_ASRPM5:
	हाल REG_ASRTFR1:
	हाल REG_ASRCCR:
	हाल REG_ASRDIA:
	हाल REG_ASRDIB:
	हाल REG_ASRDIC:
	हाल REG_ASRIDRHA:
	हाल REG_ASRIDRLA:
	हाल REG_ASRIDRHB:
	हाल REG_ASRIDRLB:
	हाल REG_ASRIDRHC:
	हाल REG_ASRIDRLC:
	हाल REG_ASR76K:
	हाल REG_ASR56K:
	हाल REG_ASRMCRA:
	हाल REG_ASRMCRB:
	हाल REG_ASRMCRC:
	हाल REG_ASRMCR1A:
	हाल REG_ASRMCR1B:
	हाल REG_ASRMCR1C:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा reg_शेष fsl_asrc_reg[] = अणु
	अणु REG_ASRCTR, 0x0000 पूर्ण, अणु REG_ASRIER, 0x0000 पूर्ण,
	अणु REG_ASRCNCR, 0x0000 पूर्ण, अणु REG_ASRCFG, 0x0000 पूर्ण,
	अणु REG_ASRCSR, 0x0000 पूर्ण, अणु REG_ASRCDR1, 0x0000 पूर्ण,
	अणु REG_ASRCDR2, 0x0000 पूर्ण, अणु REG_ASRSTR, 0x0000 पूर्ण,
	अणु REG_ASRRA, 0x0000 पूर्ण, अणु REG_ASRRB, 0x0000 पूर्ण,
	अणु REG_ASRRC, 0x0000 पूर्ण, अणु REG_ASRPM1, 0x0000 पूर्ण,
	अणु REG_ASRPM2, 0x0000 पूर्ण, अणु REG_ASRPM3, 0x0000 पूर्ण,
	अणु REG_ASRPM4, 0x0000 पूर्ण, अणु REG_ASRPM5, 0x0000 पूर्ण,
	अणु REG_ASRTFR1, 0x0000 पूर्ण, अणु REG_ASRCCR, 0x0000 पूर्ण,
	अणु REG_ASRDIA, 0x0000 पूर्ण, अणु REG_ASRDOA, 0x0000 पूर्ण,
	अणु REG_ASRDIB, 0x0000 पूर्ण, अणु REG_ASRDOB, 0x0000 पूर्ण,
	अणु REG_ASRDIC, 0x0000 पूर्ण, अणु REG_ASRDOC, 0x0000 पूर्ण,
	अणु REG_ASRIDRHA, 0x0000 पूर्ण, अणु REG_ASRIDRLA, 0x0000 पूर्ण,
	अणु REG_ASRIDRHB, 0x0000 पूर्ण, अणु REG_ASRIDRLB, 0x0000 पूर्ण,
	अणु REG_ASRIDRHC, 0x0000 पूर्ण, अणु REG_ASRIDRLC, 0x0000 पूर्ण,
	अणु REG_ASR76K, 0x0A47 पूर्ण, अणु REG_ASR56K, 0x0DF3 पूर्ण,
	अणु REG_ASRMCRA, 0x0000 पूर्ण, अणु REG_ASRFSTA, 0x0000 पूर्ण,
	अणु REG_ASRMCRB, 0x0000 पूर्ण, अणु REG_ASRFSTB, 0x0000 पूर्ण,
	अणु REG_ASRMCRC, 0x0000 पूर्ण, अणु REG_ASRFSTC, 0x0000 पूर्ण,
	अणु REG_ASRMCR1A, 0x0000 पूर्ण, अणु REG_ASRMCR1B, 0x0000 पूर्ण,
	अणु REG_ASRMCR1C, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config fsl_asrc_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = REG_ASRMCR1C,
	.reg_शेषs = fsl_asrc_reg,
	.num_reg_शेषs = ARRAY_SIZE(fsl_asrc_reg),
	.पढ़ोable_reg = fsl_asrc_पढ़ोable_reg,
	.अस्थिर_reg = fsl_asrc_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_asrc_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

/**
 * fsl_asrc_init - Initialize ASRC रेजिस्टरs with a शेष configuration
 * @asrc: ASRC context
 */
अटल पूर्णांक fsl_asrc_init(काष्ठा fsl_asrc *asrc)
अणु
	अचिन्हित दीर्घ ipg_rate;

	/* Halt ASRC पूर्णांकernal FP when input FIFO needs data क्रम pair A, B, C */
	regmap_ग_लिखो(asrc->regmap, REG_ASRCTR, ASRCTR_ASRCEN);

	/* Disable पूर्णांकerrupt by शेष */
	regmap_ग_लिखो(asrc->regmap, REG_ASRIER, 0x0);

	/* Apply recommended settings क्रम parameters from Reference Manual */
	regmap_ग_लिखो(asrc->regmap, REG_ASRPM1, 0x7fffff);
	regmap_ग_लिखो(asrc->regmap, REG_ASRPM2, 0x255555);
	regmap_ग_लिखो(asrc->regmap, REG_ASRPM3, 0xff7280);
	regmap_ग_लिखो(asrc->regmap, REG_ASRPM4, 0xff7280);
	regmap_ग_लिखो(asrc->regmap, REG_ASRPM5, 0xff7280);

	/* Base address क्रम task queue FIFO. Set to 0x7C */
	regmap_update_bits(asrc->regmap, REG_ASRTFR1,
			   ASRTFR1_TF_BASE_MASK, ASRTFR1_TF_BASE(0xfc));

	/*
	 * Set the period of the 76KHz and 56KHz sampling घड़ीs based on
	 * the ASRC processing घड़ी.
	 * On iMX6, ipg_clk = 133MHz, REG_ASR76K = 0x06D6, REG_ASR56K = 0x0947
	 */
	ipg_rate = clk_get_rate(asrc->ipg_clk);
	regmap_ग_लिखो(asrc->regmap, REG_ASR76K, ipg_rate / 76000);
	वापस regmap_ग_लिखो(asrc->regmap, REG_ASR56K, ipg_rate / 56000);
पूर्ण

/**
 * fsl_asrc_isr- Interrupt handler क्रम ASRC
 * @irq: irq number
 * @dev_id: ASRC context
 */
अटल irqवापस_t fsl_asrc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_asrc *asrc = (काष्ठा fsl_asrc *)dev_id;
	काष्ठा device *dev = &asrc->pdev->dev;
	क्रमागत asrc_pair_index index;
	u32 status;

	regmap_पढ़ो(asrc->regmap, REG_ASRSTR, &status);

	/* Clean overload error */
	regmap_ग_लिखो(asrc->regmap, REG_ASRSTR, ASRSTR_AOLE);

	/*
	 * We here use dev_dbg() क्रम all exceptions because ASRC itself करोes
	 * not care अगर FIFO overflowed or underrun जबतक a warning in the
	 * पूर्णांकerrupt would result a ridged conversion.
	 */
	क्रम (index = ASRC_PAIR_A; index < ASRC_PAIR_MAX_NUM; index++) अणु
		अगर (!asrc->pair[index])
			जारी;

		अगर (status & ASRSTR_ATQOL) अणु
			asrc->pair[index]->error |= ASRC_TASK_Q_OVERLOAD;
			dev_dbg(dev, "ASRC Task Queue FIFO overload\n");
		पूर्ण

		अगर (status & ASRSTR_AOOL(index)) अणु
			asrc->pair[index]->error |= ASRC_OUTPUT_TASK_OVERLOAD;
			pair_dbg("Output Task Overload\n");
		पूर्ण

		अगर (status & ASRSTR_AIOL(index)) अणु
			asrc->pair[index]->error |= ASRC_INPUT_TASK_OVERLOAD;
			pair_dbg("Input Task Overload\n");
		पूर्ण

		अगर (status & ASRSTR_AODO(index)) अणु
			asrc->pair[index]->error |= ASRC_OUTPUT_BUFFER_OVERFLOW;
			pair_dbg("Output Data Buffer has overflowed\n");
		पूर्ण

		अगर (status & ASRSTR_AIDU(index)) अणु
			asrc->pair[index]->error |= ASRC_INPUT_BUFFER_UNDERRUN;
			pair_dbg("Input Data Buffer has underflowed\n");
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_asrc_get_fअगरo_addr(u8 dir, क्रमागत asrc_pair_index index)
अणु
	वापस REG_ASRDx(dir, index);
पूर्ण

अटल पूर्णांक fsl_asrc_runसमय_resume(काष्ठा device *dev);
अटल पूर्णांक fsl_asrc_runसमय_suspend(काष्ठा device *dev);

अटल पूर्णांक fsl_asrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_asrc_priv *asrc_priv;
	काष्ठा fsl_asrc *asrc;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक irq, ret, i;
	u32 map_idx;
	अक्षर पंचांगp[16];
	u32 width;

	asrc = devm_kzalloc(&pdev->dev, माप(*asrc), GFP_KERNEL);
	अगर (!asrc)
		वापस -ENOMEM;

	asrc_priv = devm_kzalloc(&pdev->dev, माप(*asrc_priv), GFP_KERNEL);
	अगर (!asrc_priv)
		वापस -ENOMEM;

	asrc->pdev = pdev;
	asrc->निजी = asrc_priv;

	/* Get the addresses and IRQ */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	asrc->paddr = res->start;

	asrc->regmap = devm_regmap_init_mmio(&pdev->dev, regs, &fsl_asrc_regmap_config);
	अगर (IS_ERR(asrc->regmap)) अणु
		dev_err(&pdev->dev, "failed to init regmap\n");
		वापस PTR_ERR(asrc->regmap);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, fsl_asrc_isr, 0,
			       dev_name(&pdev->dev), asrc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim irq %u: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	asrc->mem_clk = devm_clk_get(&pdev->dev, "mem");
	अगर (IS_ERR(asrc->mem_clk)) अणु
		dev_err(&pdev->dev, "failed to get mem clock\n");
		वापस PTR_ERR(asrc->mem_clk);
	पूर्ण

	asrc->ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(asrc->ipg_clk)) अणु
		dev_err(&pdev->dev, "failed to get ipg clock\n");
		वापस PTR_ERR(asrc->ipg_clk);
	पूर्ण

	asrc->spba_clk = devm_clk_get(&pdev->dev, "spba");
	अगर (IS_ERR(asrc->spba_clk))
		dev_warn(&pdev->dev, "failed to get spba clock\n");

	क्रम (i = 0; i < ASRC_CLK_MAX_NUM; i++) अणु
		प्र_लिखो(पंचांगp, "asrck_%x", i);
		asrc_priv->asrck_clk[i] = devm_clk_get(&pdev->dev, पंचांगp);
		अगर (IS_ERR(asrc_priv->asrck_clk[i])) अणु
			dev_err(&pdev->dev, "failed to get %s clock\n", पंचांगp);
			वापस PTR_ERR(asrc_priv->asrck_clk[i]);
		पूर्ण
	पूर्ण

	asrc_priv->soc = of_device_get_match_data(&pdev->dev);
	asrc->use_edma = asrc_priv->soc->use_edma;
	asrc->get_dma_channel = fsl_asrc_get_dma_channel;
	asrc->request_pair = fsl_asrc_request_pair;
	asrc->release_pair = fsl_asrc_release_pair;
	asrc->get_fअगरo_addr = fsl_asrc_get_fअगरo_addr;
	asrc->pair_priv_size = माप(काष्ठा fsl_asrc_pair_priv);

	अगर (of_device_is_compatible(np, "fsl,imx35-asrc")) अणु
		asrc_priv->clk_map[IN] = input_clk_map_imx35;
		asrc_priv->clk_map[OUT] = output_clk_map_imx35;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx53-asrc")) अणु
		asrc_priv->clk_map[IN] = input_clk_map_imx53;
		asrc_priv->clk_map[OUT] = output_clk_map_imx53;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx8qm-asrc") ||
		   of_device_is_compatible(np, "fsl,imx8qxp-asrc")) अणु
		ret = of_property_पढ़ो_u32(np, "fsl,asrc-clk-map", &map_idx);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to get clk map index\n");
			वापस ret;
		पूर्ण

		अगर (map_idx > 1) अणु
			dev_err(&pdev->dev, "unsupported clk map index\n");
			वापस -EINVAL;
		पूर्ण
		अगर (of_device_is_compatible(np, "fsl,imx8qm-asrc")) अणु
			asrc_priv->clk_map[IN] = clk_map_imx8qm[map_idx];
			asrc_priv->clk_map[OUT] = clk_map_imx8qm[map_idx];
		पूर्ण अन्यथा अणु
			asrc_priv->clk_map[IN] = clk_map_imx8qxp[map_idx];
			asrc_priv->clk_map[OUT] = clk_map_imx8qxp[map_idx];
		पूर्ण
	पूर्ण

	asrc->channel_avail = 10;

	ret = of_property_पढ़ो_u32(np, "fsl,asrc-rate",
				   &asrc->asrc_rate);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get output rate\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "fsl,asrc-format", &asrc->asrc_क्रमmat);
	अगर (ret) अणु
		ret = of_property_पढ़ो_u32(np, "fsl,asrc-width", &width);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to decide output format\n");
			वापस ret;
		पूर्ण

		चयन (width) अणु
		हाल 16:
			asrc->asrc_क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
			अवरोध;
		हाल 24:
			asrc->asrc_क्रमmat = SNDRV_PCM_FORMAT_S24_LE;
			अवरोध;
		शेष:
			dev_warn(&pdev->dev,
				 "unsupported width, use default S24_LE\n");
			asrc->asrc_क्रमmat = SNDRV_PCM_FORMAT_S24_LE;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!(FSL_ASRC_FORMATS & (1ULL << asrc->asrc_क्रमmat))) अणु
		dev_warn(&pdev->dev, "unsupported width, use default S24_LE\n");
		asrc->asrc_क्रमmat = SNDRV_PCM_FORMAT_S24_LE;
	पूर्ण

	platक्रमm_set_drvdata(pdev, asrc);
	spin_lock_init(&asrc->lock);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = fsl_asrc_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_pm_get_sync;
	पूर्ण

	ret = fsl_asrc_init(asrc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init asrc %d\n", ret);
		जाओ err_pm_get_sync;
	पूर्ण

	ret = pm_runसमय_put_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ err_pm_get_sync;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_asrc_component,
					      &fsl_asrc_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register ASoC DAI\n");
		जाओ err_pm_get_sync;
	पूर्ण

	वापस 0;

err_pm_get_sync:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_asrc_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_asrc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_asrc_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asrc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_asrc *asrc = dev_get_drvdata(dev);
	काष्ठा fsl_asrc_priv *asrc_priv = asrc->निजी;
	पूर्णांक i, ret;
	u32 asrctr;

	ret = clk_prepare_enable(asrc->mem_clk);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(asrc->ipg_clk);
	अगर (ret)
		जाओ disable_mem_clk;
	अगर (!IS_ERR(asrc->spba_clk)) अणु
		ret = clk_prepare_enable(asrc->spba_clk);
		अगर (ret)
			जाओ disable_ipg_clk;
	पूर्ण
	क्रम (i = 0; i < ASRC_CLK_MAX_NUM; i++) अणु
		ret = clk_prepare_enable(asrc_priv->asrck_clk[i]);
		अगर (ret)
			जाओ disable_asrck_clk;
	पूर्ण

	/* Stop all pairs provisionally */
	regmap_पढ़ो(asrc->regmap, REG_ASRCTR, &asrctr);
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_ALL_MASK, 0);

	/* Restore all रेजिस्टरs */
	regcache_cache_only(asrc->regmap, false);
	regcache_mark_dirty(asrc->regmap);
	regcache_sync(asrc->regmap);

	regmap_update_bits(asrc->regmap, REG_ASRCFG,
			   ASRCFG_NDPRi_ALL_MASK | ASRCFG_POSTMODi_ALL_MASK |
			   ASRCFG_PREMODi_ALL_MASK, asrc_priv->regcache_cfg);

	/* Restart enabled pairs */
	regmap_update_bits(asrc->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_ALL_MASK, asrctr);

	वापस 0;

disable_asrck_clk:
	क्रम (i--; i >= 0; i--)
		clk_disable_unprepare(asrc_priv->asrck_clk[i]);
	अगर (!IS_ERR(asrc->spba_clk))
		clk_disable_unprepare(asrc->spba_clk);
disable_ipg_clk:
	clk_disable_unprepare(asrc->ipg_clk);
disable_mem_clk:
	clk_disable_unprepare(asrc->mem_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_asrc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_asrc *asrc = dev_get_drvdata(dev);
	काष्ठा fsl_asrc_priv *asrc_priv = asrc->निजी;
	पूर्णांक i;

	regmap_पढ़ो(asrc->regmap, REG_ASRCFG,
		    &asrc_priv->regcache_cfg);

	regcache_cache_only(asrc->regmap, true);

	क्रम (i = 0; i < ASRC_CLK_MAX_NUM; i++)
		clk_disable_unprepare(asrc_priv->asrck_clk[i]);
	अगर (!IS_ERR(asrc->spba_clk))
		clk_disable_unprepare(asrc->spba_clk);
	clk_disable_unprepare(asrc->ipg_clk);
	clk_disable_unprepare(asrc->mem_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_asrc_pm = अणु
	SET_RUNTIME_PM_OPS(fsl_asrc_runसमय_suspend, fsl_asrc_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा fsl_asrc_soc_data fsl_asrc_imx35_data = अणु
	.use_edma = false,
	.channel_bits = 3,
पूर्ण;

अटल स्थिर काष्ठा fsl_asrc_soc_data fsl_asrc_imx53_data = अणु
	.use_edma = false,
	.channel_bits = 4,
पूर्ण;

अटल स्थिर काष्ठा fsl_asrc_soc_data fsl_asrc_imx8qm_data = अणु
	.use_edma = true,
	.channel_bits = 4,
पूर्ण;

अटल स्थिर काष्ठा fsl_asrc_soc_data fsl_asrc_imx8qxp_data = अणु
	.use_edma = true,
	.channel_bits = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_asrc_ids[] = अणु
	अणु .compatible = "fsl,imx35-asrc", .data = &fsl_asrc_imx35_data पूर्ण,
	अणु .compatible = "fsl,imx53-asrc", .data = &fsl_asrc_imx53_data पूर्ण,
	अणु .compatible = "fsl,imx8qm-asrc", .data = &fsl_asrc_imx8qm_data पूर्ण,
	अणु .compatible = "fsl,imx8qxp-asrc", .data = &fsl_asrc_imx8qxp_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_asrc_ids);

अटल काष्ठा platक्रमm_driver fsl_asrc_driver = अणु
	.probe = fsl_asrc_probe,
	.हटाओ = fsl_asrc_हटाओ,
	.driver = अणु
		.name = "fsl-asrc",
		.of_match_table = fsl_asrc_ids,
		.pm = &fsl_asrc_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_asrc_driver);

MODULE_DESCRIPTION("Freescale ASRC ASoC driver");
MODULE_AUTHOR("Nicolin Chen <nicoleotsuka@gmail.com>");
MODULE_ALIAS("platform:fsl-asrc");
MODULE_LICENSE("GPL v2");
