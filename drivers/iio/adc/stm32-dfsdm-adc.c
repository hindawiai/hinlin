<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is the ADC part of the STM32 DFSDM driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Arnaud Pouliquen <arnaud.pouliquen@st.com>.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iio/adc/sपंचांग32-dfsdm-adc.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/hw-consumer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/समयr/sपंचांग32-lptim-trigger.h>
#समावेश <linux/iio/समयr/sपंचांग32-समयr-trigger.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "stm32-dfsdm.h"

#घोषणा DFSDM_DMA_BUFFER_SIZE (4 * PAGE_SIZE)

/* Conversion समयout */
#घोषणा DFSDM_TIMEOUT_US 100000
#घोषणा DFSDM_TIMEOUT (msecs_to_jअगरfies(DFSDM_TIMEOUT_US / 1000))

/* Oversampling attribute शेष */
#घोषणा DFSDM_DEFAULT_OVERSAMPLING  100

/* Oversampling max values */
#घोषणा DFSDM_MAX_INT_OVERSAMPLING 256
#घोषणा DFSDM_MAX_FL_OVERSAMPLING 1024

/* Limit filter output resolution to 31 bits. (i.e. sample range is +/-2^30) */
#घोषणा DFSDM_DATA_MAX BIT(30)
/*
 * Data are output as two's complement data in a 24 bit field.
 * Data from filters are in the range +/-2^(n-1)
 * 2^(n-1) maximum positive value cannot be coded in 2's complement n bits
 * An extra bit is required to aव्योम wrap-around of the binary code क्रम 2^(n-1)
 * So, the resolution of samples from filter is actually limited to 23 bits
 */
#घोषणा DFSDM_DATA_RES 24

/* Filter configuration */
#घोषणा DFSDM_CR1_CFG_MASK (DFSDM_CR1_RCH_MASK | DFSDM_CR1_RCONT_MASK | \
			    DFSDM_CR1_RSYNC_MASK | DFSDM_CR1_JSYNC_MASK | \
			    DFSDM_CR1_JSCAN_MASK)

क्रमागत sd_converter_type अणु
	DFSDM_AUDIO,
	DFSDM_IIO,
पूर्ण;

काष्ठा sपंचांग32_dfsdm_dev_data अणु
	पूर्णांक type;
	पूर्णांक (*init)(काष्ठा device *dev, काष्ठा iio_dev *indio_dev);
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा regmap_config *regmap_cfg;
पूर्ण;

काष्ठा sपंचांग32_dfsdm_adc अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm;
	स्थिर काष्ठा sपंचांग32_dfsdm_dev_data *dev_data;
	अचिन्हित पूर्णांक fl_id;
	अचिन्हित पूर्णांक nconv;
	अचिन्हित दीर्घ smask;

	/* ADC specअगरic */
	अचिन्हित पूर्णांक oversamp;
	काष्ठा iio_hw_consumer *hwc;
	काष्ठा completion completion;
	u32 *buffer;

	/* Audio specअगरic */
	अचिन्हित पूर्णांक spi_freq;  /* SPI bus घड़ी frequency */
	अचिन्हित पूर्णांक sample_freq; /* Sample frequency after filter decimation */
	पूर्णांक (*cb)(स्थिर व्योम *data, माप_प्रकार size, व्योम *cb_priv);
	व्योम *cb_priv;

	/* DMA */
	u8 *rx_buf;
	अचिन्हित पूर्णांक bufi; /* Buffer current position */
	अचिन्हित पूर्णांक buf_sz; /* Buffer size */
	काष्ठा dma_chan	*dma_chan;
	dma_addr_t dma_buf;
पूर्ण;

काष्ठा sपंचांग32_dfsdm_str2field अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	val;
पूर्ण;

/* DFSDM channel serial पूर्णांकerface type */
अटल स्थिर काष्ठा sपंचांग32_dfsdm_str2field sपंचांग32_dfsdm_chan_type[] = अणु
	अणु "SPI_R", 0 पूर्ण, /* SPI with data on rising edge */
	अणु "SPI_F", 1 पूर्ण, /* SPI with data on falling edge */
	अणु "MANCH_R", 2 पूर्ण, /* Manchester codec, rising edge = logic 0 */
	अणु "MANCH_F", 3 पूर्ण, /* Manchester codec, falling edge = logic 1 */
	अणुपूर्ण,
पूर्ण;

/* DFSDM channel घड़ी source */
अटल स्थिर काष्ठा sपंचांग32_dfsdm_str2field sपंचांग32_dfsdm_chan_src[] = अणु
	/* External SPI घड़ी (CLKIN x) */
	अणु "CLKIN", DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL पूर्ण,
	/* Internal SPI घड़ी (CLKOUT) */
	अणु "CLKOUT", DFSDM_CHANNEL_SPI_CLOCK_INTERNAL पूर्ण,
	/* Internal SPI घड़ी भागided by 2 (falling edge) */
	अणु "CLKOUT_F", DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING पूर्ण,
	/* Internal SPI घड़ी भागided by 2 (falling edge) */
	अणु "CLKOUT_R", DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_dfsdm_str2val(स्थिर अक्षर *str,
			       स्थिर काष्ठा sपंचांग32_dfsdm_str2field *list)
अणु
	स्थिर काष्ठा sपंचांग32_dfsdm_str2field *p = list;

	क्रम (p = list; p && p->name; p++)
		अगर (!म_भेद(p->name, str))
			वापस p->val;

	वापस -EINVAL;
पूर्ण

/**
 * काष्ठा sपंचांग32_dfsdm_trig_info - DFSDM trigger info
 * @name:		name of the trigger, corresponding to its source
 * @jextsel:		trigger संकेत selection
 */
काष्ठा sपंचांग32_dfsdm_trig_info अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक jextsel;
पूर्ण;

/* hardware injected trigger enable, edge selection */
क्रमागत sपंचांग32_dfsdm_jexten अणु
	STM32_DFSDM_JEXTEN_DISABLED,
	STM32_DFSDM_JEXTEN_RISING_EDGE,
	STM32_DFSDM_JEXTEN_FALLING_EDGE,
	STM32_DFSDM_EXTEN_BOTH_EDGES,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_dfsdm_trig_info sपंचांग32_dfsdm_trigs[] = अणु
	अणु TIM1_TRGO, 0 पूर्ण,
	अणु TIM1_TRGO2, 1 पूर्ण,
	अणु TIM8_TRGO, 2 पूर्ण,
	अणु TIM8_TRGO2, 3 पूर्ण,
	अणु TIM3_TRGO, 4 पूर्ण,
	अणु TIM4_TRGO, 5 पूर्ण,
	अणु TIM16_OC1, 6 पूर्ण,
	अणु TIM6_TRGO, 7 पूर्ण,
	अणु TIM7_TRGO, 8 पूर्ण,
	अणु LPTIM1_OUT, 26 पूर्ण,
	अणु LPTIM2_OUT, 27 पूर्ण,
	अणु LPTIM3_OUT, 28 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_dfsdm_get_jextsel(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_trigger *trig)
अणु
	पूर्णांक i;

	/* lookup triggers रेजिस्टरed by sपंचांग32 समयr trigger driver */
	क्रम (i = 0; sपंचांग32_dfsdm_trigs[i].name; i++) अणु
		/**
		 * Checking both sपंचांग32 समयr trigger type and trig name
		 * should be safe against arbitrary trigger names.
		 */
		अगर ((is_sपंचांग32_समयr_trigger(trig) ||
		     is_sपंचांग32_lptim_trigger(trig)) &&
		    !म_भेद(sपंचांग32_dfsdm_trigs[i].name, trig->name)) अणु
			वापस sपंचांग32_dfsdm_trigs[i].jextsel;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_compute_osrs(काष्ठा sपंचांग32_dfsdm_filter *fl,
				    अचिन्हित पूर्णांक fast, अचिन्हित पूर्णांक oversamp)
अणु
	अचिन्हित पूर्णांक i, d, fosr, iosr;
	u64 res, max;
	पूर्णांक bits, shअगरt;
	अचिन्हित पूर्णांक m = 1;	/* multiplication factor */
	अचिन्हित पूर्णांक p = fl->क्रमd;	/* filter order (क्रमd) */
	काष्ठा sपंचांग32_dfsdm_filter_osr *flo = &fl->flo[fast];

	pr_debug("Requested oversampling: %d\n", oversamp);
	/*
	 * This function tries to compute filter oversampling and पूर्णांकegrator
	 * oversampling, base on oversampling ratio requested by user.
	 *
	 * Decimation d depends on the filter order and the oversampling ratios.
	 * क्रमd: filter order
	 * fosr: filter over sampling ratio
	 * iosr: पूर्णांकegrator over sampling ratio
	 */
	अगर (fl->क्रमd == DFSDM_FASTSINC_ORDER) अणु
		m = 2;
		p = 2;
	पूर्ण

	/*
	 * Look क्रम filter and पूर्णांकegrator oversampling ratios which allows
	 * to maximize data output resolution.
	 */
	क्रम (fosr = 1; fosr <= DFSDM_MAX_FL_OVERSAMPLING; fosr++) अणु
		क्रम (iosr = 1; iosr <= DFSDM_MAX_INT_OVERSAMPLING; iosr++) अणु
			अगर (fast)
				d = fosr * iosr;
			अन्यथा अगर (fl->क्रमd == DFSDM_FASTSINC_ORDER)
				d = fosr * (iosr + 3) + 2;
			अन्यथा
				d = fosr * (iosr - 1 + p) + p;

			अगर (d > oversamp)
				अवरोध;
			अन्यथा अगर (d != oversamp)
				जारी;
			/*
			 * Check resolution (limited to चिन्हित 32 bits)
			 *   res <= 2^31
			 * Sincx filters:
			 *   res = m * fosr^p x iosr (with m=1, p=क्रमd)
			 * FastSinc filter
			 *   res = m * fosr^p x iosr (with m=2, p=2)
			 */
			res = fosr;
			क्रम (i = p - 1; i > 0; i--) अणु
				res = res * (u64)fosr;
				अगर (res > DFSDM_DATA_MAX)
					अवरोध;
			पूर्ण
			अगर (res > DFSDM_DATA_MAX)
				जारी;

			res = res * (u64)m * (u64)iosr;
			अगर (res > DFSDM_DATA_MAX)
				जारी;

			अगर (res >= flo->res) अणु
				flo->res = res;
				flo->fosr = fosr;
				flo->iosr = iosr;

				bits = fls(flo->res);
				/* 8 LBSs in data रेजिस्टर contain chan info */
				max = flo->res << 8;

				/* अगर resolution is not a घातer of two */
				अगर (flo->res > BIT(bits - 1))
					bits++;
				अन्यथा
					max--;

				shअगरt = DFSDM_DATA_RES - bits;
				/*
				 * Compute right/left shअगरt
				 * Right shअगरt is perक्रमmed by hardware
				 * when transferring samples to data रेजिस्टर.
				 * Left shअगरt is करोne by software on buffer
				 */
				अगर (shअगरt > 0) अणु
					/* Resolution is lower than 24 bits */
					flo->rshअगरt = 0;
					flo->lshअगरt = shअगरt;
				पूर्ण अन्यथा अणु
					/*
					 * If resolution is 24 bits or more,
					 * max positive value may be ambiguous
					 * (equal to max negative value as sign
					 * bit is dropped).
					 * Reduce resolution to 23 bits (rshअगरt)
					 * to keep the sign on bit 23 and treat
					 * saturation beक्रमe rescaling on 24
					 * bits (lshअगरt).
					 */
					flo->rshअगरt = 1 - shअगरt;
					flo->lshअगरt = 1;
					max >>= flo->rshअगरt;
				पूर्ण
				flo->max = (s32)max;
				flo->bits = bits;

				pr_debug("fast %d, fosr %d, iosr %d, res 0x%llx/%d bits, rshift %d, lshift %d\n",
					 fast, flo->fosr, flo->iosr,
					 flo->res, bits, flo->rshअगरt,
					 flo->lshअगरt);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!flo->res)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_compute_all_osrs(काष्ठा iio_dev *indio_dev,
					अचिन्हित पूर्णांक oversamp)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा sपंचांग32_dfsdm_filter *fl = &adc->dfsdm->fl_list[adc->fl_id];
	पूर्णांक ret0, ret1;

	स_रखो(&fl->flo[0], 0, माप(fl->flo[0]));
	स_रखो(&fl->flo[1], 0, माप(fl->flo[1]));

	ret0 = sपंचांग32_dfsdm_compute_osrs(fl, 0, oversamp);
	ret1 = sपंचांग32_dfsdm_compute_osrs(fl, 1, oversamp);
	अगर (ret0 < 0 && ret1 < 0) अणु
		dev_err(&indio_dev->dev,
			"Filter parameters not found: errors %d/%d\n",
			ret0, ret1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_start_channel(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	स्थिर काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक bit;
	पूर्णांक ret;

	क्रम_each_set_bit(bit, &adc->smask, माप(adc->smask) * BITS_PER_BYTE) अणु
		chan = indio_dev->channels + bit;
		ret = regmap_update_bits(regmap, DFSDM_CHCFGR1(chan->channel),
					 DFSDM_CHCFGR1_CHEN_MASK,
					 DFSDM_CHCFGR1_CHEN(1));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_dfsdm_stop_channel(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	स्थिर काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक bit;

	क्रम_each_set_bit(bit, &adc->smask, माप(adc->smask) * BITS_PER_BYTE) अणु
		chan = indio_dev->channels + bit;
		regmap_update_bits(regmap, DFSDM_CHCFGR1(chan->channel),
				   DFSDM_CHCFGR1_CHEN_MASK,
				   DFSDM_CHCFGR1_CHEN(0));
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_chan_configure(काष्ठा sपंचांग32_dfsdm *dfsdm,
				      काष्ठा sपंचांग32_dfsdm_channel *ch)
अणु
	अचिन्हित पूर्णांक id = ch->id;
	काष्ठा regmap *regmap = dfsdm->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				 DFSDM_CHCFGR1_SITP_MASK,
				 DFSDM_CHCFGR1_SITP(ch->type));
	अगर (ret < 0)
		वापस ret;
	ret = regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				 DFSDM_CHCFGR1_SPICKSEL_MASK,
				 DFSDM_CHCFGR1_SPICKSEL(ch->src));
	अगर (ret < 0)
		वापस ret;
	वापस regmap_update_bits(regmap, DFSDM_CHCFGR1(id),
				  DFSDM_CHCFGR1_CHINSEL_MASK,
				  DFSDM_CHCFGR1_CHINSEL(ch->alt_si));
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_start_filter(काष्ठा sपंचांग32_dfsdm_adc *adc,
				    अचिन्हित पूर्णांक fl_id,
				    काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = adc->dfsdm;
	पूर्णांक ret;

	/* Enable filter */
	ret = regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
				 DFSDM_CR1_DFEN_MASK, DFSDM_CR1_DFEN(1));
	अगर (ret < 0)
		वापस ret;

	/* Nothing more to करो क्रम injected (scan mode/triggered) conversions */
	अगर (adc->nconv > 1 || trig)
		वापस 0;

	/* Software start (single or continuous) regular conversion */
	वापस regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
				  DFSDM_CR1_RSWSTART_MASK,
				  DFSDM_CR1_RSWSTART(1));
पूर्ण

अटल व्योम sपंचांग32_dfsdm_stop_filter(काष्ठा sपंचांग32_dfsdm *dfsdm,
				    अचिन्हित पूर्णांक fl_id)
अणु
	/* Disable conversion */
	regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
			   DFSDM_CR1_DFEN_MASK, DFSDM_CR1_DFEN(0));
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_filter_set_trig(काष्ठा iio_dev *indio_dev,
				       अचिन्हित पूर्णांक fl_id,
				       काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	u32 jextsel = 0, jexten = STM32_DFSDM_JEXTEN_DISABLED;
	पूर्णांक ret;

	अगर (trig) अणु
		ret = sपंचांग32_dfsdm_get_jextsel(indio_dev, trig);
		अगर (ret < 0)
			वापस ret;

		/* set trigger source and polarity (शेष to rising edge) */
		jextsel = ret;
		jexten = STM32_DFSDM_JEXTEN_RISING_EDGE;
	पूर्ण

	ret = regmap_update_bits(regmap, DFSDM_CR1(fl_id),
				 DFSDM_CR1_JEXTSEL_MASK | DFSDM_CR1_JEXTEN_MASK,
				 DFSDM_CR1_JEXTSEL(jextsel) |
				 DFSDM_CR1_JEXTEN(jexten));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_channels_configure(काष्ठा iio_dev *indio_dev,
					  अचिन्हित पूर्णांक fl_id,
					  काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	काष्ठा sपंचांग32_dfsdm_filter *fl = &adc->dfsdm->fl_list[fl_id];
	काष्ठा sपंचांग32_dfsdm_filter_osr *flo = &fl->flo[0];
	स्थिर काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक bit;
	पूर्णांक ret;

	fl->fast = 0;

	/*
	 * In continuous mode, use fast mode configuration,
	 * अगर it provides a better resolution.
	 */
	अगर (adc->nconv == 1 && !trig &&
	    (indio_dev->currenपंचांगode & INDIO_BUFFER_SOFTWARE)) अणु
		अगर (fl->flo[1].res >= fl->flo[0].res) अणु
			fl->fast = 1;
			flo = &fl->flo[1];
		पूर्ण
	पूर्ण

	अगर (!flo->res)
		वापस -EINVAL;

	dev_dbg(&indio_dev->dev, "Samples actual resolution: %d bits",
		min(flo->bits, (u32)DFSDM_DATA_RES - 1));

	क्रम_each_set_bit(bit, &adc->smask,
			 माप(adc->smask) * BITS_PER_BYTE) अणु
		chan = indio_dev->channels + bit;

		ret = regmap_update_bits(regmap,
					 DFSDM_CHCFGR2(chan->channel),
					 DFSDM_CHCFGR2_DTRBS_MASK,
					 DFSDM_CHCFGR2_DTRBS(flo->rshअगरt));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_filter_configure(काष्ठा iio_dev *indio_dev,
					अचिन्हित पूर्णांक fl_id,
					काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	काष्ठा sपंचांग32_dfsdm_filter *fl = &adc->dfsdm->fl_list[fl_id];
	काष्ठा sपंचांग32_dfsdm_filter_osr *flo = &fl->flo[fl->fast];
	u32 cr1;
	स्थिर काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक bit, jchg = 0;
	पूर्णांक ret;

	/* Average पूर्णांकegrator oversampling */
	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_IOSR_MASK,
				 DFSDM_FCR_IOSR(flo->iosr - 1));
	अगर (ret)
		वापस ret;

	/* Filter order and Oversampling */
	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_FOSR_MASK,
				 DFSDM_FCR_FOSR(flo->fosr - 1));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(regmap, DFSDM_FCR(fl_id), DFSDM_FCR_FORD_MASK,
				 DFSDM_FCR_FORD(fl->क्रमd));
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_dfsdm_filter_set_trig(indio_dev, fl_id, trig);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(regmap, DFSDM_CR1(fl_id),
				 DFSDM_CR1_FAST_MASK,
				 DFSDM_CR1_FAST(fl->fast));
	अगर (ret)
		वापस ret;

	/*
	 * DFSDM modes configuration W.R.T audio/iio type modes
	 * ----------------------------------------------------------------
	 * Modes         | regular |  regular     | injected | injected   |
	 *               |         |  continuous  |          | + scan     |
	 * --------------|---------|--------------|----------|------------|
	 * single conv   |    x    |              |          |            |
	 * (1 chan)      |         |              |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 1 Audio chan	 |         | sample freq  |          |            |
	 *               |         | or sync_mode |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 1 IIO chan	 |         | sample freq  | trigger  |            |
	 *               |         | or sync_mode |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 2+ IIO chans  |         |              |          | trigger or |
	 *               |         |              |          | sync_mode  |
	 * ----------------------------------------------------------------
	 */
	अगर (adc->nconv == 1 && !trig) अणु
		bit = __ffs(adc->smask);
		chan = indio_dev->channels + bit;

		/* Use regular conversion क्रम single channel without trigger */
		cr1 = DFSDM_CR1_RCH(chan->channel);

		/* Continuous conversions triggered by SPI clk in buffer mode */
		अगर (indio_dev->currenपंचांगode & INDIO_BUFFER_SOFTWARE)
			cr1 |= DFSDM_CR1_RCONT(1);

		cr1 |= DFSDM_CR1_RSYNC(fl->sync_mode);
	पूर्ण अन्यथा अणु
		/* Use injected conversion क्रम multiple channels */
		क्रम_each_set_bit(bit, &adc->smask,
				 माप(adc->smask) * BITS_PER_BYTE) अणु
			chan = indio_dev->channels + bit;
			jchg |= BIT(chan->channel);
		पूर्ण
		ret = regmap_ग_लिखो(regmap, DFSDM_JCHGR(fl_id), jchg);
		अगर (ret < 0)
			वापस ret;

		/* Use scan mode क्रम multiple channels */
		cr1 = DFSDM_CR1_JSCAN((adc->nconv > 1) ? 1 : 0);

		/*
		 * Continuous conversions not supported in injected mode,
		 * either use:
		 * - conversions in sync with filter 0
		 * - triggered conversions
		 */
		अगर (!fl->sync_mode && !trig)
			वापस -EINVAL;
		cr1 |= DFSDM_CR1_JSYNC(fl->sync_mode);
	पूर्ण

	वापस regmap_update_bits(regmap, DFSDM_CR1(fl_id), DFSDM_CR1_CFG_MASK,
				  cr1);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_channel_parse_of(काष्ठा sपंचांग32_dfsdm *dfsdm,
					काष्ठा iio_dev *indio_dev,
					काष्ठा iio_chan_spec *ch)
अणु
	काष्ठा sपंचांग32_dfsdm_channel *df_ch;
	स्थिर अक्षर *of_str;
	पूर्णांक chan_idx = ch->scan_index;
	पूर्णांक ret, val;

	ret = of_property_पढ़ो_u32_index(indio_dev->dev.of_node,
					 "st,adc-channels", chan_idx,
					 &ch->channel);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev,
			" Error parsing 'st,adc-channels' for idx %d\n",
			chan_idx);
		वापस ret;
	पूर्ण
	अगर (ch->channel >= dfsdm->num_chs) अणु
		dev_err(&indio_dev->dev,
			" Error bad channel number %d (max = %d)\n",
			ch->channel, dfsdm->num_chs);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_string_index(indio_dev->dev.of_node,
					    "st,adc-channel-names", chan_idx,
					    &ch->datasheet_name);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev,
			" Error parsing 'st,adc-channel-names' for idx %d\n",
			chan_idx);
		वापस ret;
	पूर्ण

	df_ch =  &dfsdm->ch_list[ch->channel];
	df_ch->id = ch->channel;

	ret = of_property_पढ़ो_string_index(indio_dev->dev.of_node,
					    "st,adc-channel-types", chan_idx,
					    &of_str);
	अगर (!ret) अणु
		val = sपंचांग32_dfsdm_str2val(of_str, sपंचांग32_dfsdm_chan_type);
		अगर (val < 0)
			वापस val;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण
	df_ch->type = val;

	ret = of_property_पढ़ो_string_index(indio_dev->dev.of_node,
					    "st,adc-channel-clk-src", chan_idx,
					    &of_str);
	अगर (!ret) अणु
		val = sपंचांग32_dfsdm_str2val(of_str, sपंचांग32_dfsdm_chan_src);
		अगर (val < 0)
			वापस val;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण
	df_ch->src = val;

	ret = of_property_पढ़ो_u32_index(indio_dev->dev.of_node,
					 "st,adc-alt-channel", chan_idx,
					 &df_ch->alt_si);
	अगर (ret < 0)
		df_ch->alt_si = 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dfsdm_adc_audio_get_spiclk(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t priv,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अक्षर *buf)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", adc->spi_freq);
पूर्ण

अटल पूर्णांक dfsdm_adc_set_samp_freq(काष्ठा iio_dev *indio_dev,
				   अचिन्हित पूर्णांक sample_freq,
				   अचिन्हित पूर्णांक spi_freq)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक oversamp;
	पूर्णांक ret;

	oversamp = DIV_ROUND_CLOSEST(spi_freq, sample_freq);
	अगर (spi_freq % sample_freq)
		dev_dbg(&indio_dev->dev,
			"Rate not accurate. requested (%u), actual (%u)\n",
			sample_freq, spi_freq / oversamp);

	ret = sपंचांग32_dfsdm_compute_all_osrs(indio_dev, oversamp);
	अगर (ret < 0)
		वापस ret;

	adc->sample_freq = spi_freq / oversamp;
	adc->oversamp = oversamp;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dfsdm_adc_audio_set_spiclk(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t priv,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा sपंचांग32_dfsdm_channel *ch = &adc->dfsdm->ch_list[chan->channel];
	अचिन्हित पूर्णांक sample_freq = adc->sample_freq;
	अचिन्हित पूर्णांक spi_freq;
	पूर्णांक ret;

	dev_err(&indio_dev->dev, "enter %s\n", __func__);
	/* If DFSDM is master on SPI, SPI freq can not be updated */
	अगर (ch->src != DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL)
		वापस -EPERM;

	ret = kstrtoपूर्णांक(buf, 0, &spi_freq);
	अगर (ret)
		वापस ret;

	अगर (!spi_freq)
		वापस -EINVAL;

	अगर (sample_freq) अणु
		ret = dfsdm_adc_set_samp_freq(indio_dev, sample_freq, spi_freq);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	adc->spi_freq = spi_freq;

	वापस len;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_start_conv(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	पूर्णांक ret;

	ret = sपंचांग32_dfsdm_channels_configure(indio_dev, adc->fl_id, trig);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32_dfsdm_start_channel(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32_dfsdm_filter_configure(indio_dev, adc->fl_id, trig);
	अगर (ret < 0)
		जाओ stop_channels;

	ret = sपंचांग32_dfsdm_start_filter(adc, adc->fl_id, trig);
	अगर (ret < 0)
		जाओ filter_unconfigure;

	वापस 0;

filter_unconfigure:
	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_CFG_MASK, 0);
stop_channels:
	sपंचांग32_dfsdm_stop_channel(indio_dev);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_dfsdm_stop_conv(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;

	sपंचांग32_dfsdm_stop_filter(adc->dfsdm, adc->fl_id);

	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_CFG_MASK, 0);

	sपंचांग32_dfsdm_stop_channel(indio_dev);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_set_watermark(काष्ठा iio_dev *indio_dev,
				     अचिन्हित पूर्णांक val)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक watermark = DFSDM_DMA_BUFFER_SIZE / 2;
	अचिन्हित पूर्णांक rx_buf_sz = DFSDM_DMA_BUFFER_SIZE;

	/*
	 * DMA cyclic transfers are used, buffer is split पूर्णांकo two periods.
	 * There should be :
	 * - always one buffer (period) DMA is working on
	 * - one buffer (period) driver pushed to ASoC side.
	 */
	watermark = min(watermark, val * (अचिन्हित पूर्णांक)(माप(u32)));
	adc->buf_sz = min(rx_buf_sz, watermark * 2 * adc->nconv);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांग32_dfsdm_adc_dma_residue(काष्ठा sपंचांग32_dfsdm_adc *adc)
अणु
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(adc->dma_chan,
				     adc->dma_chan->cookie,
				     &state);
	अगर (status == DMA_IN_PROGRESS) अणु
		/* Residue is size in bytes from end of buffer */
		अचिन्हित पूर्णांक i = adc->buf_sz - state.residue;
		अचिन्हित पूर्णांक size;

		/* Return available bytes */
		अगर (i >= adc->bufi)
			size = i - adc->bufi;
		अन्यथा
			size = adc->buf_sz + i - adc->bufi;

		वापस size;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_dfsdm_process_data(काष्ठा sपंचांग32_dfsdm_adc *adc,
					    s32 *buffer)
अणु
	काष्ठा sपंचांग32_dfsdm_filter *fl = &adc->dfsdm->fl_list[adc->fl_id];
	काष्ठा sपंचांग32_dfsdm_filter_osr *flo = &fl->flo[fl->fast];
	अचिन्हित पूर्णांक i = adc->nconv;
	s32 *ptr = buffer;

	जबतक (i--) अणु
		/* Mask 8 LSB that contains the channel ID */
		*ptr &= 0xFFFFFF00;
		/* Convert 2^(n-1) sample to 2^(n-1)-1 to aव्योम wrap-around */
		अगर (*ptr > flo->max)
			*ptr -= 1;
		/*
		 * Samples from filter are retrieved with 23 bits resolution
		 * or less. Shअगरt left to align MSB on 24 bits.
		 */
		*ptr <<= flo->lshअगरt;

		ptr++;
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_dfsdm_dma_buffer_करोne(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	पूर्णांक available = sपंचांग32_dfsdm_adc_dma_residue(adc);
	माप_प्रकार old_pos;

	/*
	 * FIXME: In Kernel पूर्णांकerface करोes not support cyclic DMA buffer,and
	 * offers only an पूर्णांकerface to push data samples per samples.
	 * For this reason IIO buffer पूर्णांकerface is not used and पूर्णांकerface is
	 * bypassed using a निजी callback रेजिस्टरed by ASoC.
	 * This should be a temporary solution रुकोing a cyclic DMA engine
	 * support in IIO.
	 */

	dev_dbg(&indio_dev->dev, "pos = %d, available = %d\n",
		adc->bufi, available);
	old_pos = adc->bufi;

	जबतक (available >= indio_dev->scan_bytes) अणु
		s32 *buffer = (s32 *)&adc->rx_buf[adc->bufi];

		sपंचांग32_dfsdm_process_data(adc, buffer);

		available -= indio_dev->scan_bytes;
		adc->bufi += indio_dev->scan_bytes;
		अगर (adc->bufi >= adc->buf_sz) अणु
			अगर (adc->cb)
				adc->cb(&adc->rx_buf[old_pos],
					 adc->buf_sz - old_pos, adc->cb_priv);
			adc->bufi = 0;
			old_pos = 0;
		पूर्ण
		/*
		 * In DMA mode the trigger services of IIO are not used
		 * (e.g. no call to iio_trigger_poll).
		 * Calling irq handler associated to the hardware trigger is not
		 * relevant as the conversions have alपढ़ोy been करोne. Data
		 * transfers are perक्रमmed directly in DMA callback instead.
		 * This implementation aव्योमs to call trigger irq handler that
		 * may sleep, in an atomic context (DMA irq handler context).
		 */
		अगर (adc->dev_data->type == DFSDM_IIO)
			iio_push_to_buffers(indio_dev, buffer);
	पूर्ण
	अगर (adc->cb)
		adc->cb(&adc->rx_buf[old_pos], adc->bufi - old_pos,
			adc->cb_priv);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_adc_dma_start(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	/*
	 * The DFSDM supports half-word transfers. However, क्रम 16 bits record,
	 * 4 bytes buswidth is kept, to aव्योम losing samples LSBs when left
	 * shअगरt is required.
	 */
	काष्ठा dma_slave_config config = अणु
		.src_addr = (dma_addr_t)adc->dfsdm->phys_base,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
	पूर्ण;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (!adc->dma_chan)
		वापस -EINVAL;

	dev_dbg(&indio_dev->dev, "size=%d watermark=%d\n",
		adc->buf_sz, adc->buf_sz / 2);

	अगर (adc->nconv == 1 && !indio_dev->trig)
		config.src_addr += DFSDM_RDATAR(adc->fl_id);
	अन्यथा
		config.src_addr += DFSDM_JDATAR(adc->fl_id);
	ret = dmaengine_slave_config(adc->dma_chan, &config);
	अगर (ret)
		वापस ret;

	/* Prepare a DMA cyclic transaction */
	desc = dmaengine_prep_dma_cyclic(adc->dma_chan,
					 adc->dma_buf,
					 adc->buf_sz, adc->buf_sz / 2,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	अगर (!desc)
		वापस -EBUSY;

	desc->callback = sपंचांग32_dfsdm_dma_buffer_करोne;
	desc->callback_param = indio_dev;

	cookie = dmaengine_submit(desc);
	ret = dma_submit_error(cookie);
	अगर (ret)
		जाओ err_stop_dma;

	/* Issue pending DMA requests */
	dma_async_issue_pending(adc->dma_chan);

	अगर (adc->nconv == 1 && !indio_dev->trig) अणु
		/* Enable regular DMA transfer*/
		ret = regmap_update_bits(adc->dfsdm->regmap,
					 DFSDM_CR1(adc->fl_id),
					 DFSDM_CR1_RDMAEN_MASK,
					 DFSDM_CR1_RDMAEN_MASK);
	पूर्ण अन्यथा अणु
		/* Enable injected DMA transfer*/
		ret = regmap_update_bits(adc->dfsdm->regmap,
					 DFSDM_CR1(adc->fl_id),
					 DFSDM_CR1_JDMAEN_MASK,
					 DFSDM_CR1_JDMAEN_MASK);
	पूर्ण

	अगर (ret < 0)
		जाओ err_stop_dma;

	वापस 0;

err_stop_dma:
	dmaengine_terminate_all(adc->dma_chan);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_dfsdm_adc_dma_stop(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	अगर (!adc->dma_chan)
		वापस;

	regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RDMAEN_MASK | DFSDM_CR1_JDMAEN_MASK, 0);
	dmaengine_terminate_all(adc->dma_chan);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_update_scan_mode(काष्ठा iio_dev *indio_dev,
					स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	adc->nconv = biपंचांगap_weight(scan_mask, indio_dev->masklength);
	adc->smask = *scan_mask;

	dev_dbg(&indio_dev->dev, "nconv=%d mask=%lx\n", adc->nconv, *scan_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Reset adc buffer index */
	adc->bufi = 0;

	अगर (adc->hwc) अणु
		ret = iio_hw_consumer_enable(adc->hwc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = sपंचांग32_dfsdm_start_dfsdm(adc->dfsdm);
	अगर (ret < 0)
		जाओ err_stop_hwc;

	ret = sपंचांग32_dfsdm_adc_dma_start(indio_dev);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Can't start DMA\n");
		जाओ stop_dfsdm;
	पूर्ण

	ret = sपंचांग32_dfsdm_start_conv(indio_dev, indio_dev->trig);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Can't start conversion\n");
		जाओ err_stop_dma;
	पूर्ण

	वापस 0;

err_stop_dma:
	sपंचांग32_dfsdm_adc_dma_stop(indio_dev);
stop_dfsdm:
	sपंचांग32_dfsdm_stop_dfsdm(adc->dfsdm);
err_stop_hwc:
	अगर (adc->hwc)
		iio_hw_consumer_disable(adc->hwc);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	sपंचांग32_dfsdm_stop_conv(indio_dev);

	sपंचांग32_dfsdm_adc_dma_stop(indio_dev);

	sपंचांग32_dfsdm_stop_dfsdm(adc->dfsdm);

	अगर (adc->hwc)
		iio_hw_consumer_disable(adc->hwc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops sपंचांग32_dfsdm_buffer_setup_ops = अणु
	.postenable = &sपंचांग32_dfsdm_postenable,
	.predisable = &sपंचांग32_dfsdm_predisable,
पूर्ण;

/**
 * sपंचांग32_dfsdm_get_buff_cb() - रेजिस्टर a callback that will be called when
 *                             DMA transfer period is achieved.
 *
 * @iio_dev: Handle to IIO device.
 * @cb: Poपूर्णांकer to callback function:
 *      - data: poपूर्णांकer to data buffer
 *      - size: size in byte of the data buffer
 *      - निजी: poपूर्णांकer to consumer निजी काष्ठाure.
 * @निजी: Poपूर्णांकer to consumer निजी काष्ठाure.
 */
पूर्णांक sपंचांग32_dfsdm_get_buff_cb(काष्ठा iio_dev *iio_dev,
			    पूर्णांक (*cb)(स्थिर व्योम *data, माप_प्रकार size,
				      व्योम *निजी),
			    व्योम *निजी)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc;

	अगर (!iio_dev)
		वापस -EINVAL;
	adc = iio_priv(iio_dev);

	adc->cb = cb;
	adc->cb_priv = निजी;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग32_dfsdm_get_buff_cb);

/**
 * sपंचांग32_dfsdm_release_buff_cb - unरेजिस्टर buffer callback
 *
 * @iio_dev: Handle to IIO device.
 */
पूर्णांक sपंचांग32_dfsdm_release_buff_cb(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc;

	अगर (!iio_dev)
		वापस -EINVAL;
	adc = iio_priv(iio_dev);

	adc->cb = शून्य;
	adc->cb_priv = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग32_dfsdm_release_buff_cb);

अटल पूर्णांक sपंचांग32_dfsdm_single_conv(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *res)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	दीर्घ समयout;
	पूर्णांक ret;

	reinit_completion(&adc->completion);

	adc->buffer = res;

	ret = sपंचांग32_dfsdm_start_dfsdm(adc->dfsdm);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
				 DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(1));
	अगर (ret < 0)
		जाओ stop_dfsdm;

	adc->nconv = 1;
	adc->smask = BIT(chan->scan_index);
	ret = sपंचांग32_dfsdm_start_conv(indio_dev, शून्य);
	अगर (ret < 0) अणु
		regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
				   DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(0));
		जाओ stop_dfsdm;
	पूर्ण

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&adc->completion,
							    DFSDM_TIMEOUT);

	/* Mask IRQ क्रम regular conversion achievement*/
	regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
			   DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(0));

	अगर (समयout == 0)
		ret = -ETIMEDOUT;
	अन्यथा अगर (समयout < 0)
		ret = समयout;
	अन्यथा
		ret = IIO_VAL_INT;

	sपंचांग32_dfsdm_stop_conv(indio_dev);

	sपंचांग32_dfsdm_process_data(adc, res);

stop_dfsdm:
	sपंचांग32_dfsdm_stop_dfsdm(adc->dfsdm);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा sपंचांग32_dfsdm_channel *ch = &adc->dfsdm->ch_list[chan->channel];
	अचिन्हित पूर्णांक spi_freq;
	पूर्णांक ret = -EINVAL;

	चयन (ch->src) अणु
	हाल DFSDM_CHANNEL_SPI_CLOCK_INTERNAL:
		spi_freq = adc->dfsdm->spi_master_freq;
		अवरोध;
	हाल DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING:
	हाल DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING:
		spi_freq = adc->dfsdm->spi_master_freq / 2;
		अवरोध;
	शेष:
		spi_freq = adc->spi_freq;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = sपंचांग32_dfsdm_compute_all_osrs(indio_dev, val);
		अगर (!ret) अणु
			dev_dbg(&indio_dev->dev,
				"Sampling rate changed from (%u) to (%u)\n",
				adc->sample_freq, spi_freq / val);
			adc->oversamp = val;
			adc->sample_freq = spi_freq / val;
		पूर्ण
		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (!val)
			वापस -EINVAL;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = dfsdm_adc_set_samp_freq(indio_dev, val, spi_freq);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
				पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = iio_hw_consumer_enable(adc->hwc);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev,
				"%s: IIO enable failed (channel %d)\n",
				__func__, chan->channel);
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण
		ret = sपंचांग32_dfsdm_single_conv(indio_dev, chan, val);
		iio_hw_consumer_disable(adc->hwc);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev,
				"%s: Conversion failed (channel %d)\n",
				__func__, chan->channel);
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण
		iio_device_release_direct_mode(indio_dev);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = adc->oversamp;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = adc->sample_freq;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_validate_trigger(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_trigger *trig)
अणु
	वापस sपंचांग32_dfsdm_get_jextsel(indio_dev, trig) < 0 ? -EINVAL : 0;
पूर्ण

अटल स्थिर काष्ठा iio_info sपंचांग32_dfsdm_info_audio = अणु
	.hwfअगरo_set_watermark = sपंचांग32_dfsdm_set_watermark,
	.पढ़ो_raw = sपंचांग32_dfsdm_पढ़ो_raw,
	.ग_लिखो_raw = sपंचांग32_dfsdm_ग_लिखो_raw,
	.update_scan_mode = sपंचांग32_dfsdm_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_info sपंचांग32_dfsdm_info_adc = अणु
	.hwfअगरo_set_watermark = sपंचांग32_dfsdm_set_watermark,
	.पढ़ो_raw = sपंचांग32_dfsdm_पढ़ो_raw,
	.ग_लिखो_raw = sपंचांग32_dfsdm_ग_लिखो_raw,
	.update_scan_mode = sपंचांग32_dfsdm_update_scan_mode,
	.validate_trigger = sपंचांग32_dfsdm_validate_trigger,
पूर्ण;

अटल irqवापस_t sपंचांग32_dfsdm_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा iio_dev *indio_dev = arg;
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->dfsdm->regmap;
	अचिन्हित पूर्णांक status, पूर्णांक_en;

	regmap_पढ़ो(regmap, DFSDM_ISR(adc->fl_id), &status);
	regmap_पढ़ो(regmap, DFSDM_CR2(adc->fl_id), &पूर्णांक_en);

	अगर (status & DFSDM_ISR_REOCF_MASK) अणु
		/* Read the data रेजिस्टर clean the IRQ status */
		regmap_पढ़ो(regmap, DFSDM_RDATAR(adc->fl_id), adc->buffer);
		complete(&adc->completion);
	पूर्ण

	अगर (status & DFSDM_ISR_ROVRF_MASK) अणु
		अगर (पूर्णांक_en & DFSDM_CR2_ROVRIE_MASK)
			dev_warn(&indio_dev->dev, "Overrun detected\n");
		regmap_update_bits(regmap, DFSDM_ICR(adc->fl_id),
				   DFSDM_ICR_CLRROVRF_MASK,
				   DFSDM_ICR_CLRROVRF_MASK);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Define बाह्यal info क्रम SPI Frequency and audio sampling rate that can be
 * configured by ASoC driver through consumer.h API
 */
अटल स्थिर काष्ठा iio_chan_spec_ext_info dfsdm_adc_audio_ext_info[] = अणु
	/* spi_clk_freq : घड़ी freq on SPI/manchester bus used by channel */
	अणु
		.name = "spi_clk_freq",
		.shared = IIO_SHARED_BY_TYPE,
		.पढ़ो = dfsdm_adc_audio_get_spiclk,
		.ग_लिखो = dfsdm_adc_audio_set_spiclk,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम sपंचांग32_dfsdm_dma_release(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	अगर (adc->dma_chan) अणु
		dma_मुक्त_coherent(adc->dma_chan->device->dev,
				  DFSDM_DMA_BUFFER_SIZE,
				  adc->rx_buf, adc->dma_buf);
		dma_release_channel(adc->dma_chan);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_dma_request(काष्ठा device *dev,
				   काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	adc->dma_chan = dma_request_chan(dev, "rx");
	अगर (IS_ERR(adc->dma_chan)) अणु
		पूर्णांक ret = PTR_ERR(adc->dma_chan);

		adc->dma_chan = शून्य;
		वापस ret;
	पूर्ण

	adc->rx_buf = dma_alloc_coherent(adc->dma_chan->device->dev,
					 DFSDM_DMA_BUFFER_SIZE,
					 &adc->dma_buf, GFP_KERNEL);
	अगर (!adc->rx_buf) अणु
		dma_release_channel(adc->dma_chan);
		वापस -ENOMEM;
	पूर्ण

	indio_dev->modes |= INDIO_BUFFER_SOFTWARE;
	indio_dev->setup_ops = &sपंचांग32_dfsdm_buffer_setup_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_adc_chan_init_one(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_chan_spec *ch)
अणु
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = sपंचांग32_dfsdm_channel_parse_of(adc->dfsdm, indio_dev, ch);
	अगर (ret < 0)
		वापस ret;

	ch->type = IIO_VOLTAGE;
	ch->indexed = 1;

	/*
	 * IIO_CHAN_INFO_RAW: used to compute regular conversion
	 * IIO_CHAN_INFO_OVERSAMPLING_RATIO: used to set oversampling
	 */
	ch->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	ch->info_mask_shared_by_all = BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO) |
					BIT(IIO_CHAN_INFO_SAMP_FREQ);

	अगर (adc->dev_data->type == DFSDM_AUDIO) अणु
		ch->ext_info = dfsdm_adc_audio_ext_info;
	पूर्ण अन्यथा अणु
		ch->scan_type.shअगरt = 8;
	पूर्ण
	ch->scan_type.sign = 's';
	ch->scan_type.realbits = 24;
	ch->scan_type.storagebits = 32;

	वापस sपंचांग32_dfsdm_chan_configure(adc->dfsdm,
					  &adc->dfsdm->ch_list[ch->channel]);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_audio_init(काष्ठा device *dev, काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_chan_spec *ch;
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	काष्ठा sपंचांग32_dfsdm_channel *d_ch;
	पूर्णांक ret;

	ch = devm_kzalloc(&indio_dev->dev, माप(*ch), GFP_KERNEL);
	अगर (!ch)
		वापस -ENOMEM;

	ch->scan_index = 0;

	ret = sपंचांग32_dfsdm_adc_chan_init_one(indio_dev, ch);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Channels init failed\n");
		वापस ret;
	पूर्ण
	ch->info_mask_separate = BIT(IIO_CHAN_INFO_SAMP_FREQ);

	d_ch = &adc->dfsdm->ch_list[ch->channel];
	अगर (d_ch->src != DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL)
		adc->spi_freq = adc->dfsdm->spi_master_freq;

	indio_dev->num_channels = 1;
	indio_dev->channels = ch;

	वापस sपंचांग32_dfsdm_dma_request(dev, indio_dev);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_adc_init(काष्ठा device *dev, काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_chan_spec *ch;
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	पूर्णांक num_ch;
	पूर्णांक ret, chan_idx;

	adc->oversamp = DFSDM_DEFAULT_OVERSAMPLING;
	ret = sपंचांग32_dfsdm_compute_all_osrs(indio_dev, adc->oversamp);
	अगर (ret < 0)
		वापस ret;

	num_ch = of_property_count_u32_elems(indio_dev->dev.of_node,
					     "st,adc-channels");
	अगर (num_ch < 0 || num_ch > adc->dfsdm->num_chs) अणु
		dev_err(&indio_dev->dev, "Bad st,adc-channels\n");
		वापस num_ch < 0 ? num_ch : -EINVAL;
	पूर्ण

	/* Bind to SD modulator IIO device */
	adc->hwc = devm_iio_hw_consumer_alloc(&indio_dev->dev);
	अगर (IS_ERR(adc->hwc))
		वापस -EPROBE_DEFER;

	ch = devm_kसुस्मृति(&indio_dev->dev, num_ch, माप(*ch),
			  GFP_KERNEL);
	अगर (!ch)
		वापस -ENOMEM;

	क्रम (chan_idx = 0; chan_idx < num_ch; chan_idx++) अणु
		ch[chan_idx].scan_index = chan_idx;
		ret = sपंचांग32_dfsdm_adc_chan_init_one(indio_dev, &ch[chan_idx]);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev, "Channels init failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	indio_dev->num_channels = num_ch;
	indio_dev->channels = ch;

	init_completion(&adc->completion);

	/* Optionally request DMA */
	ret = sपंचांग32_dfsdm_dma_request(dev, indio_dev);
	अगर (ret) अणु
		अगर (ret != -ENODEV)
			वापस dev_err_probe(dev, ret,
					     "DMA channel request failed with\n");

		dev_dbg(dev, "No DMA support\n");
		वापस 0;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 &iio_pollfunc_store_समय, शून्य,
					 &sपंचांग32_dfsdm_buffer_setup_ops);
	अगर (ret) अणु
		sपंचांग32_dfsdm_dma_release(indio_dev);
		dev_err(&indio_dev->dev, "buffer setup failed\n");
		वापस ret;
	पूर्ण

	/* lpसमयr/समयr hardware triggers */
	indio_dev->modes |= INDIO_HARDWARE_TRIGGERED;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_dfsdm_dev_data sपंचांग32h7_dfsdm_adc_data = अणु
	.type = DFSDM_IIO,
	.init = sपंचांग32_dfsdm_adc_init,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_dfsdm_dev_data sपंचांग32h7_dfsdm_audio_data = अणु
	.type = DFSDM_AUDIO,
	.init = sपंचांग32_dfsdm_audio_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dfsdm_adc_match[] = अणु
	अणु
		.compatible = "st,stm32-dfsdm-adc",
		.data = &sपंचांग32h7_dfsdm_adc_data,
	पूर्ण,
	अणु
		.compatible = "st,stm32-dfsdm-dmic",
		.data = &sपंचांग32h7_dfsdm_audio_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_dfsdm_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_dfsdm_adc *adc;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा sपंचांग32_dfsdm_dev_data *dev_data;
	काष्ठा iio_dev *iio;
	अक्षर *name;
	पूर्णांक ret, irq, val;

	dev_data = of_device_get_match_data(dev);
	iio = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!iio) अणु
		dev_err(dev, "%s: Failed to allocate IIO\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(iio);
	adc->dfsdm = dev_get_drvdata(dev->parent);

	iio->dev.of_node = np;
	iio->modes = INDIO_सूचीECT_MODE;

	platक्रमm_set_drvdata(pdev, iio);

	ret = of_property_पढ़ो_u32(dev->of_node, "reg", &adc->fl_id);
	अगर (ret != 0 || adc->fl_id >= adc->dfsdm->num_fls) अणु
		dev_err(dev, "Missing or bad reg property\n");
		वापस -EINVAL;
	पूर्ण

	name = devm_kzalloc(dev, माप("dfsdm-adc0"), GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	अगर (dev_data->type == DFSDM_AUDIO) अणु
		iio->info = &sपंचांग32_dfsdm_info_audio;
		snम_लिखो(name, माप("dfsdm-pdm0"), "dfsdm-pdm%d", adc->fl_id);
	पूर्ण अन्यथा अणु
		iio->info = &sपंचांग32_dfsdm_info_adc;
		snम_लिखो(name, माप("dfsdm-adc0"), "dfsdm-adc%d", adc->fl_id);
	पूर्ण
	iio->name = name;

	/*
	 * In a first step IRQs generated क्रम channels are not treated.
	 * So IRQ associated to filter instance 0 is dedicated to the Filter 0.
	 */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, sपंचांग32_dfsdm_irq,
			       0, pdev->name, iio);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request IRQ\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "st,filter-order", &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set filter order\n");
		वापस ret;
	पूर्ण

	adc->dfsdm->fl_list[adc->fl_id].क्रमd = val;

	ret = of_property_पढ़ो_u32(dev->of_node, "st,filter0-sync", &val);
	अगर (!ret)
		adc->dfsdm->fl_list[adc->fl_id].sync_mode = val;

	adc->dev_data = dev_data;
	ret = dev_data->init(dev, iio);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(iio);
	अगर (ret < 0)
		जाओ err_cleanup;

	अगर (dev_data->type == DFSDM_AUDIO) अणु
		ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to find an audio DAI\n");
			जाओ err_unरेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर:
	iio_device_unरेजिस्टर(iio);
err_cleanup:
	sपंचांग32_dfsdm_dma_release(iio);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);

	अगर (adc->dev_data->type == DFSDM_AUDIO)
		of_platक्रमm_depopulate(&pdev->dev);
	iio_device_unरेजिस्टर(indio_dev);
	sपंचांग32_dfsdm_dma_release(indio_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	अगर (iio_buffer_enabled(indio_dev))
		sपंचांग32_dfsdm_predisable(indio_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_dfsdm_adc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा iio_chan_spec *chan;
	काष्ठा sपंचांग32_dfsdm_channel *ch;
	पूर्णांक i, ret;

	/* restore channels configuration */
	क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
		chan = indio_dev->channels + i;
		ch = &adc->dfsdm->ch_list[chan->channel];
		ret = sपंचांग32_dfsdm_chan_configure(adc->dfsdm, ch);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (iio_buffer_enabled(indio_dev))
		sपंचांग32_dfsdm_postenable(indio_dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_dfsdm_adc_pm_ops,
			 sपंचांग32_dfsdm_adc_suspend, sपंचांग32_dfsdm_adc_resume);

अटल काष्ठा platक्रमm_driver sपंचांग32_dfsdm_adc_driver = अणु
	.driver = अणु
		.name = "stm32-dfsdm-adc",
		.of_match_table = sपंचांग32_dfsdm_adc_match,
		.pm = &sपंचांग32_dfsdm_adc_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_dfsdm_adc_probe,
	.हटाओ = sपंचांग32_dfsdm_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_dfsdm_adc_driver);

MODULE_DESCRIPTION("STM32 sigma delta ADC");
MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_LICENSE("GPL v2");
