<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Hardware Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 *
 * This ties पूर्णांकo the input subप्रणाली using the RC-core. Protocol support is
 * provided in separate modules which provide the parameters and scancode
 * translation functions to set up the hardware decoder and पूर्णांकerpret the
 * resulting input.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <media/rc-core.h>
#समावेश "img-ir.h"

/* Decoders lock (only modअगरied to preprocess them) */
अटल DEFINE_SPINLOCK(img_ir_decoders_lock);

अटल bool img_ir_decoders_preprocessed;
अटल काष्ठा img_ir_decoder *img_ir_decoders[] = अणु
#अगर_घोषित CONFIG_IR_IMG_NEC
	&img_ir_nec,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_JVC
	&img_ir_jvc,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_SONY
	&img_ir_sony,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_SHARP
	&img_ir_sharp,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_SANYO
	&img_ir_sanyo,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_RC5
	&img_ir_rc5,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IR_IMG_RC6
	&img_ir_rc6,
#पूर्ण_अगर
	शून्य
पूर्ण;

#घोषणा IMG_IR_F_FILTER		BIT(RC_FILTER_NORMAL)	/* enable filtering */
#घोषणा IMG_IR_F_WAKE		BIT(RC_FILTER_WAKEUP)	/* enable waking */

/* code type quirks */

#घोषणा IMG_IR_QUIRK_CODE_BROKEN	0x1	/* Decode is broken */
#घोषणा IMG_IR_QUIRK_CODE_LEN_INCR	0x2	/* Bit length needs increment */
/*
 * The decoder generates rapid पूर्णांकerrupts without actually having
 * received any new data after an incomplete IR code is decoded.
 */
#घोषणा IMG_IR_QUIRK_CODE_IRQ		0x4

/* functions क्रम preprocessing timings, ensuring max is set */

अटल व्योम img_ir_timing_preprocess(काष्ठा img_ir_timing_range *range,
				     अचिन्हित पूर्णांक unit)
अणु
	अगर (range->max < range->min)
		range->max = range->min;
	अगर (unit) अणु
		/* multiply by unit and convert to microseconds */
		range->min = (range->min*unit)/1000;
		range->max = (range->max*unit + 999)/1000; /* round up */
	पूर्ण
पूर्ण

अटल व्योम img_ir_symbol_timing_preprocess(काष्ठा img_ir_symbol_timing *timing,
					    अचिन्हित पूर्णांक unit)
अणु
	img_ir_timing_preprocess(&timing->pulse, unit);
	img_ir_timing_preprocess(&timing->space, unit);
पूर्ण

अटल व्योम img_ir_timings_preprocess(काष्ठा img_ir_timings *timings,
				      अचिन्हित पूर्णांक unit)
अणु
	img_ir_symbol_timing_preprocess(&timings->ldr, unit);
	img_ir_symbol_timing_preprocess(&timings->s00, unit);
	img_ir_symbol_timing_preprocess(&timings->s01, unit);
	img_ir_symbol_timing_preprocess(&timings->s10, unit);
	img_ir_symbol_timing_preprocess(&timings->s11, unit);
	/* शेष s10 and s11 to s00 and s01 अगर no leader */
	अगर (unit)
		/* multiply by unit and convert to microseconds (round up) */
		timings->ft.ft_min = (timings->ft.ft_min*unit + 999)/1000;
पूर्ण

/* functions क्रम filling empty fields with शेषs */

अटल व्योम img_ir_timing_शेषs(काष्ठा img_ir_timing_range *range,
				   काष्ठा img_ir_timing_range *शेषs)
अणु
	अगर (!range->min)
		range->min = शेषs->min;
	अगर (!range->max)
		range->max = शेषs->max;
पूर्ण

अटल व्योम img_ir_symbol_timing_शेषs(काष्ठा img_ir_symbol_timing *timing,
					  काष्ठा img_ir_symbol_timing *शेषs)
अणु
	img_ir_timing_शेषs(&timing->pulse, &शेषs->pulse);
	img_ir_timing_शेषs(&timing->space, &शेषs->space);
पूर्ण

अटल व्योम img_ir_timings_शेषs(काष्ठा img_ir_timings *timings,
				    काष्ठा img_ir_timings *शेषs)
अणु
	img_ir_symbol_timing_शेषs(&timings->ldr, &शेषs->ldr);
	img_ir_symbol_timing_शेषs(&timings->s00, &शेषs->s00);
	img_ir_symbol_timing_शेषs(&timings->s01, &शेषs->s01);
	img_ir_symbol_timing_शेषs(&timings->s10, &शेषs->s10);
	img_ir_symbol_timing_शेषs(&timings->s11, &शेषs->s11);
	अगर (!timings->ft.ft_min)
		timings->ft.ft_min = शेषs->ft.ft_min;
पूर्ण

/* functions क्रम converting timings to रेजिस्टर values */

/**
 * img_ir_control() - Convert control काष्ठा to control रेजिस्टर value.
 * @control:	Control data
 *
 * Returns:	The control रेजिस्टर value equivalent of @control.
 */
अटल u32 img_ir_control(स्थिर काष्ठा img_ir_control *control)
अणु
	u32 ctrl = control->code_type << IMG_IR_CODETYPE_SHIFT;
	अगर (control->decoden)
		ctrl |= IMG_IR_DECODEN;
	अगर (control->hdrtog)
		ctrl |= IMG_IR_HDRTOG;
	अगर (control->ldrdec)
		ctrl |= IMG_IR_LDRDEC;
	अगर (control->decodinpol)
		ctrl |= IMG_IR_DECODINPOL;
	अगर (control->bitorien)
		ctrl |= IMG_IR_BITORIEN;
	अगर (control->d1validsel)
		ctrl |= IMG_IR_D1VALIDSEL;
	अगर (control->bitinv)
		ctrl |= IMG_IR_BITINV;
	अगर (control->decodend2)
		ctrl |= IMG_IR_DECODEND2;
	अगर (control->bitoriend2)
		ctrl |= IMG_IR_BITORIEND2;
	अगर (control->bitinvd2)
		ctrl |= IMG_IR_BITINVD2;
	वापस ctrl;
पूर्ण

/**
 * img_ir_timing_range_convert() - Convert microsecond range.
 * @out:	Output timing range in घड़ी cycles with a shअगरt.
 * @in:		Input timing range in microseconds.
 * @tolerance:	Tolerance as a fraction of 128 (roughly percent).
 * @घड़ी_hz:	IR घड़ी rate in Hz.
 * @shअगरt:	Shअगरt of output units.
 *
 * Converts min and max from microseconds to IR घड़ी cycles, applies a
 * tolerance, and shअगरts क्रम the रेजिस्टर, rounding in the right direction.
 * Note that in and out can safely be the same object.
 */
अटल व्योम img_ir_timing_range_convert(काष्ठा img_ir_timing_range *out,
					स्थिर काष्ठा img_ir_timing_range *in,
					अचिन्हित पूर्णांक tolerance,
					अचिन्हित दीर्घ घड़ी_hz,
					अचिन्हित पूर्णांक shअगरt)
अणु
	अचिन्हित पूर्णांक min = in->min;
	अचिन्हित पूर्णांक max = in->max;
	/* add a tolerance */
	min = min - (min*tolerance >> 7);
	max = max + (max*tolerance >> 7);
	/* convert from microseconds पूर्णांकo घड़ी cycles */
	min = min*घड़ी_hz / 1000000;
	max = (max*घड़ी_hz + 999999) / 1000000; /* round up */
	/* apply shअगरt and copy to output */
	out->min = min >> shअगरt;
	out->max = (max + ((1 << shअगरt) - 1)) >> shअगरt; /* round up */
पूर्ण

/**
 * img_ir_symbol_timing() - Convert symbol timing काष्ठा to रेजिस्टर value.
 * @timing:	Symbol timing data
 * @tolerance:	Timing tolerance where 0-128 represents 0-100%
 * @घड़ी_hz:	Frequency of source घड़ी in Hz
 * @pd_shअगरt:	Shअगरt to apply to symbol period
 * @w_shअगरt:	Shअगरt to apply to symbol width
 *
 * Returns:	Symbol timing रेजिस्टर value based on arguments.
 */
अटल u32 img_ir_symbol_timing(स्थिर काष्ठा img_ir_symbol_timing *timing,
				अचिन्हित पूर्णांक tolerance,
				अचिन्हित दीर्घ घड़ी_hz,
				अचिन्हित पूर्णांक pd_shअगरt,
				अचिन्हित पूर्णांक w_shअगरt)
अणु
	काष्ठा img_ir_timing_range hw_pulse, hw_period;
	/* we calculate period in hw_period, then convert in place */
	hw_period.min = timing->pulse.min + timing->space.min;
	hw_period.max = timing->pulse.max + timing->space.max;
	img_ir_timing_range_convert(&hw_period, &hw_period,
			tolerance, घड़ी_hz, pd_shअगरt);
	img_ir_timing_range_convert(&hw_pulse, &timing->pulse,
			tolerance, घड़ी_hz, w_shअगरt);
	/* स्थिरruct रेजिस्टर value */
	वापस	(hw_period.max	<< IMG_IR_PD_MAX_SHIFT)	|
		(hw_period.min	<< IMG_IR_PD_MIN_SHIFT)	|
		(hw_pulse.max	<< IMG_IR_W_MAX_SHIFT)	|
		(hw_pulse.min	<< IMG_IR_W_MIN_SHIFT);
पूर्ण

/**
 * img_ir_मुक्त_timing() - Convert मुक्त समय timing काष्ठा to रेजिस्टर value.
 * @timing:	Free symbol timing data
 * @घड़ी_hz:	Source घड़ी frequency in Hz
 *
 * Returns:	Free symbol timing रेजिस्टर value.
 */
अटल u32 img_ir_मुक्त_timing(स्थिर काष्ठा img_ir_मुक्त_timing *timing,
			      अचिन्हित दीर्घ घड़ी_hz)
अणु
	अचिन्हित पूर्णांक minlen, maxlen, ft_min;
	/* minlen is only 5 bits, and round minlen to multiple of 2 */
	अगर (timing->minlen < 30)
		minlen = timing->minlen & -2;
	अन्यथा
		minlen = 30;
	/* maxlen has maximum value of 48, and round maxlen to multiple of 2 */
	अगर (timing->maxlen < 48)
		maxlen = (timing->maxlen + 1) & -2;
	अन्यथा
		maxlen = 48;
	/* convert and shअगरt ft_min, rounding upwards */
	ft_min = (timing->ft_min*घड़ी_hz + 999999) / 1000000;
	ft_min = (ft_min + 7) >> 3;
	/* स्थिरruct रेजिस्टर value */
	वापस	(maxlen << IMG_IR_MAXLEN_SHIFT)	|
		(minlen << IMG_IR_MINLEN_SHIFT)	|
		(ft_min << IMG_IR_FT_MIN_SHIFT);
पूर्ण

/**
 * img_ir_मुक्त_timing_dynamic() - Update मुक्त समय रेजिस्टर value.
 * @st_ft:	Static मुक्त समय रेजिस्टर value from img_ir_मुक्त_timing.
 * @filter:	Current filter which may additionally restrict min/max len.
 *
 * Returns:	Updated मुक्त समय रेजिस्टर value based on the current filter.
 */
अटल u32 img_ir_मुक्त_timing_dynamic(u32 st_ft, काष्ठा img_ir_filter *filter)
अणु
	अचिन्हित पूर्णांक minlen, maxlen, newminlen, newmaxlen;

	/* round minlen, maxlen to multiple of 2 */
	newminlen = filter->minlen & -2;
	newmaxlen = (filter->maxlen + 1) & -2;
	/* extract min/max len from रेजिस्टर */
	minlen = (st_ft & IMG_IR_MINLEN) >> IMG_IR_MINLEN_SHIFT;
	maxlen = (st_ft & IMG_IR_MAXLEN) >> IMG_IR_MAXLEN_SHIFT;
	/* अगर the new values are more restrictive, update the रेजिस्टर value */
	अगर (newminlen > minlen) अणु
		st_ft &= ~IMG_IR_MINLEN;
		st_ft |= newminlen << IMG_IR_MINLEN_SHIFT;
	पूर्ण
	अगर (newmaxlen < maxlen) अणु
		st_ft &= ~IMG_IR_MAXLEN;
		st_ft |= newmaxlen << IMG_IR_MAXLEN_SHIFT;
	पूर्ण
	वापस st_ft;
पूर्ण

/**
 * img_ir_timings_convert() - Convert timings to रेजिस्टर values
 * @regs:	Output timing रेजिस्टर values
 * @timings:	Input timing data
 * @tolerance:	Timing tolerance where 0-128 represents 0-100%
 * @घड़ी_hz:	Source घड़ी frequency in Hz
 */
अटल व्योम img_ir_timings_convert(काष्ठा img_ir_timing_regvals *regs,
				   स्थिर काष्ठा img_ir_timings *timings,
				   अचिन्हित पूर्णांक tolerance,
				   अचिन्हित पूर्णांक घड़ी_hz)
अणु
	/* leader symbol timings are भागided by 16 */
	regs->ldr = img_ir_symbol_timing(&timings->ldr, tolerance, घड़ी_hz,
			4, 4);
	/* other symbol timings, pd fields only are भागided by 2 */
	regs->s00 = img_ir_symbol_timing(&timings->s00, tolerance, घड़ी_hz,
			1, 0);
	regs->s01 = img_ir_symbol_timing(&timings->s01, tolerance, घड़ी_hz,
			1, 0);
	regs->s10 = img_ir_symbol_timing(&timings->s10, tolerance, घड़ी_hz,
			1, 0);
	regs->s11 = img_ir_symbol_timing(&timings->s11, tolerance, घड़ी_hz,
			1, 0);
	regs->ft = img_ir_मुक्त_timing(&timings->ft, घड़ी_hz);
पूर्ण

/**
 * img_ir_decoder_preprocess() - Preprocess timings in decoder.
 * @decoder:	Decoder to be preprocessed.
 *
 * Ensures that the symbol timing ranges are valid with respect to ordering, and
 * करोes some fixed conversion on them.
 */
अटल व्योम img_ir_decoder_preprocess(काष्ठा img_ir_decoder *decoder)
अणु
	/* शेष tolerance */
	अगर (!decoder->tolerance)
		decoder->tolerance = 10; /* percent */
	/* and convert tolerance to fraction out of 128 */
	decoder->tolerance = decoder->tolerance * 128 / 100;

	/* fill in implicit fields */
	img_ir_timings_preprocess(&decoder->timings, decoder->unit);

	/* करो the same क्रम repeat timings अगर applicable */
	अगर (decoder->repeat) अणु
		img_ir_timings_preprocess(&decoder->rtimings, decoder->unit);
		img_ir_timings_शेषs(&decoder->rtimings, &decoder->timings);
	पूर्ण
पूर्ण

/**
 * img_ir_decoder_convert() - Generate पूर्णांकernal timings in decoder.
 * @decoder:	Decoder to be converted to पूर्णांकernal timings.
 * @reg_timings: Timing रेजिस्टर values.
 * @घड़ी_hz:	IR घड़ी rate in Hz.
 *
 * Fills out the repeat timings and timing रेजिस्टर values क्रम a specअगरic घड़ी
 * rate.
 */
अटल व्योम img_ir_decoder_convert(स्थिर काष्ठा img_ir_decoder *decoder,
				   काष्ठा img_ir_reg_timings *reg_timings,
				   अचिन्हित पूर्णांक घड़ी_hz)
अणु
	/* calculate control value */
	reg_timings->ctrl = img_ir_control(&decoder->control);

	/* fill in implicit fields and calculate रेजिस्टर values */
	img_ir_timings_convert(&reg_timings->timings, &decoder->timings,
			       decoder->tolerance, घड़ी_hz);

	/* करो the same क्रम repeat timings अगर applicable */
	अगर (decoder->repeat)
		img_ir_timings_convert(&reg_timings->rtimings,
				       &decoder->rtimings, decoder->tolerance,
				       घड़ी_hz);
पूर्ण

/**
 * img_ir_ग_लिखो_timings() - Write timings to the hardware now
 * @priv:	IR निजी data
 * @regs:	Timing रेजिस्टर values to ग_लिखो
 * @type:	RC filter type (RC_FILTER_*)
 *
 * Write timing रेजिस्टर values @regs to the hardware, taking पूर्णांकo account the
 * current filter which may impose restrictions on the length of the expected
 * data.
 */
अटल व्योम img_ir_ग_लिखो_timings(काष्ठा img_ir_priv *priv,
				 काष्ठा img_ir_timing_regvals *regs,
				 क्रमागत rc_filter_type type)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;

	/* filter may be more restrictive to minlen, maxlen */
	u32 ft = regs->ft;
	अगर (hw->flags & BIT(type))
		ft = img_ir_मुक्त_timing_dynamic(regs->ft, &hw->filters[type]);
	/* ग_लिखो to रेजिस्टरs */
	img_ir_ग_लिखो(priv, IMG_IR_LEAD_SYMB_TIMING, regs->ldr);
	img_ir_ग_लिखो(priv, IMG_IR_S00_SYMB_TIMING, regs->s00);
	img_ir_ग_लिखो(priv, IMG_IR_S01_SYMB_TIMING, regs->s01);
	img_ir_ग_लिखो(priv, IMG_IR_S10_SYMB_TIMING, regs->s10);
	img_ir_ग_लिखो(priv, IMG_IR_S11_SYMB_TIMING, regs->s11);
	img_ir_ग_लिखो(priv, IMG_IR_FREE_SYMB_TIMING, ft);
	dev_dbg(priv->dev, "timings: ldr=%#x, s=[%#x, %#x, %#x, %#x], ft=%#x\n",
		regs->ldr, regs->s00, regs->s01, regs->s10, regs->s11, ft);
पूर्ण

अटल व्योम img_ir_ग_लिखो_filter(काष्ठा img_ir_priv *priv,
				काष्ठा img_ir_filter *filter)
अणु
	अगर (filter) अणु
		dev_dbg(priv->dev, "IR filter=%016llx & %016llx\n",
			(अचिन्हित दीर्घ दीर्घ)filter->data,
			(अचिन्हित दीर्घ दीर्घ)filter->mask);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_DATA_LW, (u32)filter->data);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_DATA_UP, (u32)(filter->data
									>> 32));
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_MASK_LW, (u32)filter->mask);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_MASK_UP, (u32)(filter->mask
									>> 32));
	पूर्ण अन्यथा अणु
		dev_dbg(priv->dev, "IR clearing filter\n");
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_MASK_LW, 0);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_MSG_MASK_UP, 0);
	पूर्ण
पूर्ण

/* caller must have lock */
अटल व्योम _img_ir_set_filter(काष्ठा img_ir_priv *priv,
			       काष्ठा img_ir_filter *filter)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	u32 irq_en, irq_on;

	irq_en = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
	अगर (filter) अणु
		/* Only use the match पूर्णांकerrupt */
		hw->filters[RC_FILTER_NORMAL] = *filter;
		hw->flags |= IMG_IR_F_FILTER;
		irq_on = IMG_IR_IRQ_DATA_MATCH;
		irq_en &= ~(IMG_IR_IRQ_DATA_VALID | IMG_IR_IRQ_DATA2_VALID);
	पूर्ण अन्यथा अणु
		/* Only use the valid पूर्णांकerrupt */
		hw->flags &= ~IMG_IR_F_FILTER;
		irq_en &= ~IMG_IR_IRQ_DATA_MATCH;
		irq_on = IMG_IR_IRQ_DATA_VALID | IMG_IR_IRQ_DATA2_VALID;
	पूर्ण
	irq_en |= irq_on;

	img_ir_ग_लिखो_filter(priv, filter);
	/* clear any पूर्णांकerrupts we're enabling so we don't handle old ones */
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_CLEAR, irq_on);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, irq_en);
पूर्ण

/* caller must have lock */
अटल व्योम _img_ir_set_wake_filter(काष्ठा img_ir_priv *priv,
				    काष्ठा img_ir_filter *filter)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	अगर (filter) अणु
		/* Enable wake, and copy filter क्रम later */
		hw->filters[RC_FILTER_WAKEUP] = *filter;
		hw->flags |= IMG_IR_F_WAKE;
	पूर्ण अन्यथा अणु
		/* Disable wake */
		hw->flags &= ~IMG_IR_F_WAKE;
	पूर्ण
पूर्ण

/* Callback क्रम setting scancode filter */
अटल पूर्णांक img_ir_set_filter(काष्ठा rc_dev *dev, क्रमागत rc_filter_type type,
			     काष्ठा rc_scancode_filter *sc_filter)
अणु
	काष्ठा img_ir_priv *priv = dev->priv;
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	काष्ठा img_ir_filter filter, *filter_ptr = &filter;
	पूर्णांक ret = 0;

	dev_dbg(priv->dev, "IR scancode %sfilter=%08x & %08x\n",
		type == RC_FILTER_WAKEUP ? "wake " : "",
		sc_filter->data,
		sc_filter->mask);

	spin_lock_irq(&priv->lock);

	/* filtering can always be disabled */
	अगर (!sc_filter->mask) अणु
		filter_ptr = शून्य;
		जाओ set_unlock;
	पूर्ण

	/* current decoder must support scancode filtering */
	अगर (!hw->decoder || !hw->decoder->filter) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	/* convert scancode filter to raw filter */
	filter.minlen = 0;
	filter.maxlen = ~0;
	अगर (type == RC_FILTER_NORMAL) अणु
		/* guess scancode from protocol */
		ret = hw->decoder->filter(sc_filter, &filter,
					  dev->enabled_protocols);
	पूर्ण अन्यथा अणु
		/* क्रम wakeup user provided exact protocol variant */
		ret = hw->decoder->filter(sc_filter, &filter,
					  1ULL << dev->wakeup_protocol);
	पूर्ण
	अगर (ret)
		जाओ unlock;
	dev_dbg(priv->dev, "IR raw %sfilter=%016llx & %016llx\n",
		type == RC_FILTER_WAKEUP ? "wake " : "",
		(अचिन्हित दीर्घ दीर्घ)filter.data,
		(अचिन्हित दीर्घ दीर्घ)filter.mask);

set_unlock:
	/* apply raw filters */
	चयन (type) अणु
	हाल RC_FILTER_NORMAL:
		_img_ir_set_filter(priv, filter_ptr);
		अवरोध;
	हाल RC_FILTER_WAKEUP:
		_img_ir_set_wake_filter(priv, filter_ptr);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

unlock:
	spin_unlock_irq(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक img_ir_set_normal_filter(काष्ठा rc_dev *dev,
				    काष्ठा rc_scancode_filter *sc_filter)
अणु
	वापस img_ir_set_filter(dev, RC_FILTER_NORMAL, sc_filter);
पूर्ण

अटल पूर्णांक img_ir_set_wakeup_filter(काष्ठा rc_dev *dev,
				    काष्ठा rc_scancode_filter *sc_filter)
अणु
	वापस img_ir_set_filter(dev, RC_FILTER_WAKEUP, sc_filter);
पूर्ण

/**
 * img_ir_set_decoder() - Set the current decoder.
 * @priv:	IR निजी data.
 * @decoder:	Decoder to use with immediate effect.
 * @proto:	Protocol biपंचांगap (or 0 to use decoder->type).
 */
अटल व्योम img_ir_set_decoder(काष्ठा img_ir_priv *priv,
			       स्थिर काष्ठा img_ir_decoder *decoder,
			       u64 proto)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	काष्ठा rc_dev *rdev = hw->rdev;
	u32 ir_status, irq_en;
	spin_lock_irq(&priv->lock);

	/*
	 * First record that the protocol is being stopped so that the end समयr
	 * isn't restarted while we're trying to stop it.
	 */
	hw->stopping = true;

	/*
	 * Release the lock to stop the end समयr, since the end समयr handler
	 * acquires the lock and we करोn't want to deadlock रुकोing क्रम it.
	 */
	spin_unlock_irq(&priv->lock);
	del_समयr_sync(&hw->end_समयr);
	del_समयr_sync(&hw->suspend_समयr);
	spin_lock_irq(&priv->lock);

	hw->stopping = false;

	/* चयन off and disable पूर्णांकerrupts */
	img_ir_ग_लिखो(priv, IMG_IR_CONTROL, 0);
	irq_en = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, irq_en & IMG_IR_IRQ_EDGE);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_ALL & ~IMG_IR_IRQ_EDGE);

	/* ack any data alपढ़ोy detected */
	ir_status = img_ir_पढ़ो(priv, IMG_IR_STATUS);
	अगर (ir_status & (IMG_IR_RXDVAL | IMG_IR_RXDVALD2)) अणु
		ir_status &= ~(IMG_IR_RXDVAL | IMG_IR_RXDVALD2);
		img_ir_ग_लिखो(priv, IMG_IR_STATUS, ir_status);
	पूर्ण

	/* always पढ़ो data to clear buffer अगर IR wakes the device */
	img_ir_पढ़ो(priv, IMG_IR_DATA_LW);
	img_ir_पढ़ो(priv, IMG_IR_DATA_UP);

	/* चयन back to normal mode */
	hw->mode = IMG_IR_M_NORMAL;

	/* clear the wakeup scancode filter */
	rdev->scancode_wakeup_filter.data = 0;
	rdev->scancode_wakeup_filter.mask = 0;
	rdev->wakeup_protocol = RC_PROTO_UNKNOWN;

	/* clear raw filters */
	_img_ir_set_filter(priv, शून्य);
	_img_ir_set_wake_filter(priv, शून्य);

	/* clear the enabled protocols */
	hw->enabled_protocols = 0;

	/* चयन decoder */
	hw->decoder = decoder;
	अगर (!decoder)
		जाओ unlock;

	/* set the enabled protocols */
	अगर (!proto)
		proto = decoder->type;
	hw->enabled_protocols = proto;

	/* ग_लिखो the new timings */
	img_ir_decoder_convert(decoder, &hw->reg_timings, hw->clk_hz);
	img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings, RC_FILTER_NORMAL);

	/* set up and enable */
	img_ir_ग_लिखो(priv, IMG_IR_CONTROL, hw->reg_timings.ctrl);


unlock:
	spin_unlock_irq(&priv->lock);
पूर्ण

/**
 * img_ir_decoder_compatible() - Find whether a decoder will work with a device.
 * @priv:	IR निजी data.
 * @dec:	Decoder to check.
 *
 * Returns:	true अगर @dec is compatible with the device @priv refers to.
 */
अटल bool img_ir_decoder_compatible(काष्ठा img_ir_priv *priv,
				      स्थिर काष्ठा img_ir_decoder *dec)
अणु
	अचिन्हित पूर्णांक ct;

	/* करोn't accept decoders using code types which aren't supported */
	ct = dec->control.code_type;
	अगर (priv->hw.ct_quirks[ct] & IMG_IR_QUIRK_CODE_BROKEN)
		वापस false;

	वापस true;
पूर्ण

/**
 * img_ir_allowed_protos() - Get allowed protocols from global decoder list.
 * @priv:	IR निजी data.
 *
 * Returns:	Mask of protocols supported by the device @priv refers to.
 */
अटल u64 img_ir_allowed_protos(काष्ठा img_ir_priv *priv)
अणु
	u64 protos = 0;
	काष्ठा img_ir_decoder **decp;

	क्रम (decp = img_ir_decoders; *decp; ++decp) अणु
		स्थिर काष्ठा img_ir_decoder *dec = *decp;
		अगर (img_ir_decoder_compatible(priv, dec))
			protos |= dec->type;
	पूर्ण
	वापस protos;
पूर्ण

/* Callback क्रम changing protocol using sysfs */
अटल पूर्णांक img_ir_change_protocol(काष्ठा rc_dev *dev, u64 *ir_type)
अणु
	काष्ठा img_ir_priv *priv = dev->priv;
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	काष्ठा rc_dev *rdev = hw->rdev;
	काष्ठा img_ir_decoder **decp;
	u64 wakeup_protocols;

	अगर (!*ir_type) अणु
		/* disable all protocols */
		img_ir_set_decoder(priv, शून्य, 0);
		जाओ success;
	पूर्ण
	क्रम (decp = img_ir_decoders; *decp; ++decp) अणु
		स्थिर काष्ठा img_ir_decoder *dec = *decp;
		अगर (!img_ir_decoder_compatible(priv, dec))
			जारी;
		अगर (*ir_type & dec->type) अणु
			*ir_type &= dec->type;
			img_ir_set_decoder(priv, dec, *ir_type);
			जाओ success;
		पूर्ण
	पूर्ण
	वापस -EINVAL;

success:
	/*
	 * Only allow matching wakeup protocols क्रम now, and only अगर filtering
	 * is supported.
	 */
	wakeup_protocols = *ir_type;
	अगर (!hw->decoder || !hw->decoder->filter)
		wakeup_protocols = 0;
	rdev->allowed_wakeup_protocols = wakeup_protocols;
	वापस 0;
पूर्ण

/* Changes ir-core protocol device attribute */
अटल व्योम img_ir_set_protocol(काष्ठा img_ir_priv *priv, u64 proto)
अणु
	काष्ठा rc_dev *rdev = priv->hw.rdev;

	mutex_lock(&rdev->lock);
	rdev->enabled_protocols = proto;
	rdev->allowed_wakeup_protocols = proto;
	mutex_unlock(&rdev->lock);
पूर्ण

/* Set up IR decoders */
अटल व्योम img_ir_init_decoders(व्योम)
अणु
	काष्ठा img_ir_decoder **decp;

	spin_lock(&img_ir_decoders_lock);
	अगर (!img_ir_decoders_preprocessed) अणु
		क्रम (decp = img_ir_decoders; *decp; ++decp)
			img_ir_decoder_preprocess(*decp);
		img_ir_decoders_preprocessed = true;
	पूर्ण
	spin_unlock(&img_ir_decoders_lock);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * img_ir_enable_wake() - Switch to wake mode.
 * @priv:	IR निजी data.
 *
 * Returns:	non-zero अगर the IR can wake the प्रणाली.
 */
अटल पूर्णांक img_ir_enable_wake(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	पूर्णांक ret = 0;

	spin_lock_irq(&priv->lock);
	अगर (hw->flags & IMG_IR_F_WAKE) अणु
		/* पूर्णांकerrupt only on a match */
		hw->suspend_irqen = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, IMG_IR_IRQ_DATA_MATCH);
		img_ir_ग_लिखो_filter(priv, &hw->filters[RC_FILTER_WAKEUP]);
		img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings,
				     RC_FILTER_WAKEUP);
		hw->mode = IMG_IR_M_WAKE;
		ret = 1;
	पूर्ण
	spin_unlock_irq(&priv->lock);
	वापस ret;
पूर्ण

/**
 * img_ir_disable_wake() - Switch out of wake mode.
 * @priv:	IR निजी data
 *
 * Returns:	1 अगर the hardware should be allowed to wake from a sleep state.
 *		0 otherwise.
 */
अटल पूर्णांक img_ir_disable_wake(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	पूर्णांक ret = 0;

	spin_lock_irq(&priv->lock);
	अगर (hw->flags & IMG_IR_F_WAKE) अणु
		/* restore normal filtering */
		अगर (hw->flags & IMG_IR_F_FILTER) अणु
			img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE,
				     (hw->suspend_irqen & IMG_IR_IRQ_EDGE) |
				     IMG_IR_IRQ_DATA_MATCH);
			img_ir_ग_लिखो_filter(priv,
					    &hw->filters[RC_FILTER_NORMAL]);
		पूर्ण अन्यथा अणु
			img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE,
				     (hw->suspend_irqen & IMG_IR_IRQ_EDGE) |
				     IMG_IR_IRQ_DATA_VALID |
				     IMG_IR_IRQ_DATA2_VALID);
			img_ir_ग_लिखो_filter(priv, शून्य);
		पूर्ण
		img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings,
				     RC_FILTER_NORMAL);
		hw->mode = IMG_IR_M_NORMAL;
		ret = 1;
	पूर्ण
	spin_unlock_irq(&priv->lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/* lock must be held */
अटल व्योम img_ir_begin_repeat(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	अगर (hw->mode == IMG_IR_M_NORMAL) अणु
		/* चयन to repeat timings */
		img_ir_ग_लिखो(priv, IMG_IR_CONTROL, 0);
		hw->mode = IMG_IR_M_REPEATING;
		img_ir_ग_लिखो_timings(priv, &hw->reg_timings.rtimings,
				     RC_FILTER_NORMAL);
		img_ir_ग_लिखो(priv, IMG_IR_CONTROL, hw->reg_timings.ctrl);
	पूर्ण
पूर्ण

/* lock must be held */
अटल व्योम img_ir_end_repeat(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	अगर (hw->mode == IMG_IR_M_REPEATING) अणु
		/* चयन to normal timings */
		img_ir_ग_लिखो(priv, IMG_IR_CONTROL, 0);
		hw->mode = IMG_IR_M_NORMAL;
		img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings,
				     RC_FILTER_NORMAL);
		img_ir_ग_लिखो(priv, IMG_IR_CONTROL, hw->reg_timings.ctrl);
	पूर्ण
पूर्ण

/* lock must be held */
अटल व्योम img_ir_handle_data(काष्ठा img_ir_priv *priv, u32 len, u64 raw)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	स्थिर काष्ठा img_ir_decoder *dec = hw->decoder;
	पूर्णांक ret = IMG_IR_SCANCODE;
	काष्ठा img_ir_scancode_req request;

	request.protocol = RC_PROTO_UNKNOWN;
	request.toggle   = 0;

	अगर (dec->scancode)
		ret = dec->scancode(len, raw, hw->enabled_protocols, &request);
	अन्यथा अगर (len >= 32)
		request.scancode = (u32)raw;
	अन्यथा अगर (len < 32)
		request.scancode = (u32)raw & ((1 << len)-1);
	dev_dbg(priv->dev, "data (%u bits) = %#llx\n",
		len, (अचिन्हित दीर्घ दीर्घ)raw);
	अगर (ret == IMG_IR_SCANCODE) अणु
		dev_dbg(priv->dev, "decoded scan code %#x, toggle %u\n",
			request.scancode, request.toggle);
		rc_keyकरोwn(hw->rdev, request.protocol, request.scancode,
			   request.toggle);
		img_ir_end_repeat(priv);
	पूर्ण अन्यथा अगर (ret == IMG_IR_REPEATCODE) अणु
		अगर (hw->mode == IMG_IR_M_REPEATING) अणु
			dev_dbg(priv->dev, "decoded repeat code\n");
			rc_repeat(hw->rdev);
		पूर्ण अन्यथा अणु
			dev_dbg(priv->dev, "decoded unexpected repeat code, ignoring\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(priv->dev, "decode failed (%d)\n", ret);
		वापस;
	पूर्ण


	/* we mustn't update the end समयr जबतक trying to stop it */
	अगर (dec->repeat && !hw->stopping) अणु
		अचिन्हित दीर्घ पूर्णांकerval;

		img_ir_begin_repeat(priv);

		/* update समयr, but allowing क्रम 1/8th tolerance */
		पूर्णांकerval = dec->repeat + (dec->repeat >> 3);
		mod_समयr(&hw->end_समयr,
			  jअगरfies + msecs_to_jअगरfies(पूर्णांकerval));
	पूर्ण
पूर्ण

/* समयr function to end रुकोing क्रम repeat. */
अटल व्योम img_ir_end_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा img_ir_priv *priv = from_समयr(priv, t, hw.end_समयr);

	spin_lock_irq(&priv->lock);
	img_ir_end_repeat(priv);
	spin_unlock_irq(&priv->lock);
पूर्ण

/*
 * Timer function to re-enable the current protocol after it had been
 * cleared when invalid पूर्णांकerrupts were generated due to a quirk in the
 * img-ir decoder.
 */
अटल व्योम img_ir_suspend_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा img_ir_priv *priv = from_समयr(priv, t, hw.suspend_समयr);

	spin_lock_irq(&priv->lock);
	/*
	 * Don't overग_लिखो enabled valid/match IRQs अगर they have alपढ़ोy been
	 * changed by e.g. a filter change.
	 */
	अगर ((priv->hw.quirk_suspend_irq & IMG_IR_IRQ_EDGE) ==
				img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE))
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE,
					priv->hw.quirk_suspend_irq);
	/* enable */
	img_ir_ग_लिखो(priv, IMG_IR_CONTROL, priv->hw.reg_timings.ctrl);
	spin_unlock_irq(&priv->lock);
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
अटल व्योम img_ir_change_frequency(काष्ठा img_ir_priv *priv,
				    काष्ठा clk_notअगरier_data *change)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;

	dev_dbg(priv->dev, "clk changed %lu HZ -> %lu HZ\n",
		change->old_rate, change->new_rate);

	spin_lock_irq(&priv->lock);
	अगर (hw->clk_hz == change->new_rate)
		जाओ unlock;
	hw->clk_hz = change->new_rate;
	/* refresh current timings */
	अगर (hw->decoder) अणु
		img_ir_decoder_convert(hw->decoder, &hw->reg_timings,
				       hw->clk_hz);
		चयन (hw->mode) अणु
		हाल IMG_IR_M_NORMAL:
			img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings,
					     RC_FILTER_NORMAL);
			अवरोध;
		हाल IMG_IR_M_REPEATING:
			img_ir_ग_लिखो_timings(priv, &hw->reg_timings.rtimings,
					     RC_FILTER_NORMAL);
			अवरोध;
#अगर_घोषित CONFIG_PM_SLEEP
		हाल IMG_IR_M_WAKE:
			img_ir_ग_लिखो_timings(priv, &hw->reg_timings.timings,
					     RC_FILTER_WAKEUP);
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
unlock:
	spin_unlock_irq(&priv->lock);
पूर्ण

अटल पूर्णांक img_ir_clk_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ action,
			     व्योम *data)
अणु
	काष्ठा img_ir_priv *priv = container_of(self, काष्ठा img_ir_priv,
						hw.clk_nb);
	चयन (action) अणु
	हाल POST_RATE_CHANGE:
		img_ir_change_frequency(priv, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMMON_CLK */

/* called with priv->lock held */
व्योम img_ir_isr_hw(काष्ठा img_ir_priv *priv, u32 irq_status)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	u32 ir_status, len, lw, up;
	अचिन्हित पूर्णांक ct;

	/* use the current decoder */
	अगर (!hw->decoder)
		वापस;

	ct = hw->decoder->control.code_type;

	ir_status = img_ir_पढ़ो(priv, IMG_IR_STATUS);
	अगर (!(ir_status & (IMG_IR_RXDVAL | IMG_IR_RXDVALD2))) अणु
		अगर (!(priv->hw.ct_quirks[ct] & IMG_IR_QUIRK_CODE_IRQ) ||
				hw->stopping)
			वापस;
		/*
		 * The below functionality is added as a work around to stop
		 * multiple Interrupts generated when an incomplete IR code is
		 * received by the decoder.
		 * The decoder generates rapid पूर्णांकerrupts without actually
		 * having received any new data. After a single पूर्णांकerrupt it's
		 * expected to clear up, but instead multiple पूर्णांकerrupts are
		 * rapidly generated. only way to get out of this loop is to
		 * reset the control रेजिस्टर after a लघु delay.
		 */
		img_ir_ग_लिखो(priv, IMG_IR_CONTROL, 0);
		hw->quirk_suspend_irq = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
		img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE,
			     hw->quirk_suspend_irq & IMG_IR_IRQ_EDGE);

		/* Timer activated to re-enable the protocol. */
		mod_समयr(&hw->suspend_समयr,
			  jअगरfies + msecs_to_jअगरfies(5));
		वापस;
	पूर्ण
	ir_status &= ~(IMG_IR_RXDVAL | IMG_IR_RXDVALD2);
	img_ir_ग_लिखो(priv, IMG_IR_STATUS, ir_status);

	len = (ir_status & IMG_IR_RXDLEN) >> IMG_IR_RXDLEN_SHIFT;
	/* some versions report wrong length क्रम certain code types */
	अगर (hw->ct_quirks[ct] & IMG_IR_QUIRK_CODE_LEN_INCR)
		++len;

	lw = img_ir_पढ़ो(priv, IMG_IR_DATA_LW);
	up = img_ir_पढ़ो(priv, IMG_IR_DATA_UP);
	img_ir_handle_data(priv, len, (u64)up << 32 | lw);
पूर्ण

व्योम img_ir_setup_hw(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_decoder **decp;

	अगर (!priv->hw.rdev)
		वापस;

	/* Use the first available decoder (or disable stuff अगर शून्य) */
	क्रम (decp = img_ir_decoders; *decp; ++decp) अणु
		स्थिर काष्ठा img_ir_decoder *dec = *decp;
		अगर (img_ir_decoder_compatible(priv, dec)) अणु
			img_ir_set_protocol(priv, dec->type);
			img_ir_set_decoder(priv, dec, 0);
			वापस;
		पूर्ण
	पूर्ण
	img_ir_set_decoder(priv, शून्य, 0);
पूर्ण

/**
 * img_ir_probe_hw_caps() - Probe capabilities of the hardware.
 * @priv:	IR निजी data.
 */
अटल व्योम img_ir_probe_hw_caps(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	/*
	 * When a version of the block becomes available without these quirks,
	 * they'll have to depend on the core revision.
	 */
	hw->ct_quirks[IMG_IR_CODETYPE_PULSELEN]
		|= IMG_IR_QUIRK_CODE_LEN_INCR;
	hw->ct_quirks[IMG_IR_CODETYPE_BIPHASE]
		|= IMG_IR_QUIRK_CODE_IRQ;
	hw->ct_quirks[IMG_IR_CODETYPE_2BITPULSEPOS]
		|= IMG_IR_QUIRK_CODE_BROKEN;
पूर्ण

पूर्णांक img_ir_probe_hw(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	काष्ठा rc_dev *rdev;
	पूर्णांक error;

	/* Ensure hardware decoders have been preprocessed */
	img_ir_init_decoders();

	/* Probe hardware capabilities */
	img_ir_probe_hw_caps(priv);

	/* Set up the end समयr */
	समयr_setup(&hw->end_समयr, img_ir_end_समयr, 0);
	समयr_setup(&hw->suspend_समयr, img_ir_suspend_समयr, 0);

	/* Register a घड़ी notअगरier */
	अगर (!IS_ERR(priv->clk)) अणु
		hw->clk_hz = clk_get_rate(priv->clk);
#अगर_घोषित CONFIG_COMMON_CLK
		hw->clk_nb.notअगरier_call = img_ir_clk_notअगरy;
		error = clk_notअगरier_रेजिस्टर(priv->clk, &hw->clk_nb);
		अगर (error)
			dev_warn(priv->dev,
				 "failed to register clock notifier\n");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		hw->clk_hz = 32768;
	पूर्ण

	/* Allocate hardware decoder */
	hw->rdev = rdev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!rdev) अणु
		dev_err(priv->dev, "cannot allocate input device\n");
		error = -ENOMEM;
		जाओ err_alloc_rc;
	पूर्ण
	rdev->priv = priv;
	rdev->map_name = RC_MAP_EMPTY;
	rdev->allowed_protocols = img_ir_allowed_protos(priv);
	rdev->device_name = "IMG Infrared Decoder";
	rdev->s_filter = img_ir_set_normal_filter;
	rdev->s_wakeup_filter = img_ir_set_wakeup_filter;

	/* Register hardware decoder */
	error = rc_रेजिस्टर_device(rdev);
	अगर (error) अणु
		dev_err(priv->dev, "failed to register IR input device\n");
		जाओ err_रेजिस्टर_rc;
	पूर्ण

	/*
	 * Set this after rc_रेजिस्टर_device as no protocols have been
	 * रेजिस्टरed yet.
	 */
	rdev->change_protocol = img_ir_change_protocol;

	device_init_wakeup(priv->dev, 1);

	वापस 0;

err_रेजिस्टर_rc:
	img_ir_set_decoder(priv, शून्य, 0);
	hw->rdev = शून्य;
	rc_मुक्त_device(rdev);
err_alloc_rc:
#अगर_घोषित CONFIG_COMMON_CLK
	अगर (!IS_ERR(priv->clk))
		clk_notअगरier_unरेजिस्टर(priv->clk, &hw->clk_nb);
#पूर्ण_अगर
	वापस error;
पूर्ण

व्योम img_ir_हटाओ_hw(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_hw *hw = &priv->hw;
	काष्ठा rc_dev *rdev = hw->rdev;
	अगर (!rdev)
		वापस;
	img_ir_set_decoder(priv, शून्य, 0);
	hw->rdev = शून्य;
	rc_unरेजिस्टर_device(rdev);
#अगर_घोषित CONFIG_COMMON_CLK
	अगर (!IS_ERR(priv->clk))
		clk_notअगरier_unरेजिस्टर(priv->clk, &hw->clk_nb);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक img_ir_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_ir_priv *priv = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev) && img_ir_enable_wake(priv))
		enable_irq_wake(priv->irq);
	वापस 0;
पूर्ण

पूर्णांक img_ir_resume(काष्ठा device *dev)
अणु
	काष्ठा img_ir_priv *priv = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev) && img_ir_disable_wake(priv))
		disable_irq_wake(priv->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PM_SLEEP */
