<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम NI general purpose counters
 *
 * Copyright (C) 2006 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * Module: ni_tio
 * Description: National Instruments general purpose counters
 * Author: J.P. Mellor <jpmellor@rose-hulman.edu>,
 *         Herman.Bruyninckx@mech.kuleuven.ac.be,
 *         Wim.Meeussen@mech.kuleuven.ac.be,
 *         Klaas.Gadeyne@mech.kuleuven.ac.be,
 *         Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Updated: Thu Nov 16 09:50:32 EST 2006
 * Status: works
 *
 * This module is not used directly by end-users.  Rather, it
 * is used by other drivers (क्रम example ni_660x and ni_pcimio)
 * to provide support क्रम NI's general purpose counters.  It was
 * originally based on the counter code from ni_660x.c and
 * ni_mio_common.c.
 *
 * References:
 * DAQ 660x Register-Level Programmer Manual  (NI 370505A-01)
 * DAQ 6601/6602 User Manual (NI 322137B-01)
 * 340934b.pdf  DAQ-STC reference manual
 *
 * TODO: Support use of both banks X and Y
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "ni_tio_internal.h"

/*
 * घड़ी sources क्रम ni e and m series boards,
 * get bits with GI_SRC_SEL()
 */
#घोषणा NI_M_TIMEBASE_1_CLK		0x0	/* 20MHz */
#घोषणा NI_M_PFI_CLK(x)			(((x) < 10) ? (1 + (x)) : (0xb + (x)))
#घोषणा NI_M_RTSI_CLK(x)		(((x) == 7) ? 0x1b : (0xb + (x)))
#घोषणा NI_M_TIMEBASE_2_CLK		0x12	/* 100KHz */
#घोषणा NI_M_NEXT_TC_CLK		0x13
#घोषणा NI_M_NEXT_GATE_CLK		0x14	/* Gi_Src_SubSelect=0 */
#घोषणा NI_M_PXI_STAR_TRIGGER_CLK	0x14	/* Gi_Src_SubSelect=1 */
#घोषणा NI_M_PXI10_CLK			0x1d
#घोषणा NI_M_TIMEBASE_3_CLK		0x1e	/* 80MHz, Gi_Src_SubSelect=0 */
#घोषणा NI_M_ANALOG_TRIGGER_OUT_CLK	0x1e	/* Gi_Src_SubSelect=1 */
#घोषणा NI_M_LOGIC_LOW_CLK		0x1f
#घोषणा NI_M_MAX_PFI_CHAN		15
#घोषणा NI_M_MAX_RTSI_CHAN		7

/*
 * घड़ी sources क्रम ni_660x boards,
 * get bits with GI_SRC_SEL()
 */
#घोषणा NI_660X_TIMEBASE_1_CLK		0x0	/* 20MHz */
#घोषणा NI_660X_SRC_PIN_I_CLK		0x1
#घोषणा NI_660X_SRC_PIN_CLK(x)		(0x2 + (x))
#घोषणा NI_660X_NEXT_GATE_CLK		0xa
#घोषणा NI_660X_RTSI_CLK(x)		(0xb + (x))
#घोषणा NI_660X_TIMEBASE_2_CLK		0x12	/* 100KHz */
#घोषणा NI_660X_NEXT_TC_CLK		0x13
#घोषणा NI_660X_TIMEBASE_3_CLK		0x1e	/* 80MHz */
#घोषणा NI_660X_LOGIC_LOW_CLK		0x1f
#घोषणा NI_660X_MAX_SRC_PIN		7
#घोषणा NI_660X_MAX_RTSI_CHAN		6

/* ni m series gate_select */
#घोषणा NI_M_TIMESTAMP_MUX_GATE_SEL	0x0
#घोषणा NI_M_PFI_GATE_SEL(x)		(((x) < 10) ? (1 + (x)) : (0xb + (x)))
#घोषणा NI_M_RTSI_GATE_SEL(x)		(((x) == 7) ? 0x1b : (0xb + (x)))
#घोषणा NI_M_AI_START2_GATE_SEL		0x12
#घोषणा NI_M_PXI_STAR_TRIGGER_GATE_SEL	0x13
#घोषणा NI_M_NEXT_OUT_GATE_SEL		0x14
#घोषणा NI_M_AI_START1_GATE_SEL		0x1c
#घोषणा NI_M_NEXT_SRC_GATE_SEL		0x1d
#घोषणा NI_M_ANALOG_TRIG_OUT_GATE_SEL	0x1e
#घोषणा NI_M_LOGIC_LOW_GATE_SEL		0x1f

/* ni_660x gate select */
#घोषणा NI_660X_SRC_PIN_I_GATE_SEL	0x0
#घोषणा NI_660X_GATE_PIN_I_GATE_SEL	0x1
#घोषणा NI_660X_PIN_GATE_SEL(x)		(0x2 + (x))
#घोषणा NI_660X_NEXT_SRC_GATE_SEL	0xa
#घोषणा NI_660X_RTSI_GATE_SEL(x)	(0xb + (x))
#घोषणा NI_660X_NEXT_OUT_GATE_SEL	0x14
#घोषणा NI_660X_LOGIC_LOW_GATE_SEL	0x1f
#घोषणा NI_660X_MAX_GATE_PIN		7

/* ni_660x second gate select */
#घोषणा NI_660X_SRC_PIN_I_GATE2_SEL	0x0
#घोषणा NI_660X_UD_PIN_I_GATE2_SEL	0x1
#घोषणा NI_660X_UD_PIN_GATE2_SEL(x)	(0x2 + (x))
#घोषणा NI_660X_NEXT_SRC_GATE2_SEL	0xa
#घोषणा NI_660X_RTSI_GATE2_SEL(x)	(0xb + (x))
#घोषणा NI_660X_NEXT_OUT_GATE2_SEL	0x14
#घोषणा NI_660X_SELECTED_GATE2_SEL	0x1e
#घोषणा NI_660X_LOGIC_LOW_GATE2_SEL	0x1f
#घोषणा NI_660X_MAX_UP_DOWN_PIN		7

अटल अंतरभूत अचिन्हित पूर्णांक GI_PRESCALE_X2(क्रमागत ni_gpct_variant variant)
अणु
	चयन (variant) अणु
	हाल ni_gpct_variant_e_series:
	शेष:
		वापस 0;
	हाल ni_gpct_variant_m_series:
		वापस GI_M_PRESCALE_X2;
	हाल ni_gpct_variant_660x:
		वापस GI_660X_PRESCALE_X2;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक GI_PRESCALE_X8(क्रमागत ni_gpct_variant variant)
अणु
	चयन (variant) अणु
	हाल ni_gpct_variant_e_series:
	शेष:
		वापस 0;
	हाल ni_gpct_variant_m_series:
		वापस GI_M_PRESCALE_X8;
	हाल ni_gpct_variant_660x:
		वापस GI_660X_PRESCALE_X8;
	पूर्ण
पूर्ण

अटल bool ni_tio_has_gate2_रेजिस्टरs(स्थिर काष्ठा ni_gpct_device *counter_dev)
अणु
	चयन (counter_dev->variant) अणु
	हाल ni_gpct_variant_e_series:
	शेष:
		वापस false;
	हाल ni_gpct_variant_m_series:
	हाल ni_gpct_variant_660x:
		वापस true;
	पूर्ण
पूर्ण

/**
 * ni_tio_ग_लिखो() - Write a TIO रेजिस्टर using the driver provided callback.
 * @counter: काष्ठा ni_gpct counter.
 * @value: the value to ग_लिखो
 * @reg: the रेजिस्टर to ग_लिखो.
 */
व्योम ni_tio_ग_लिखो(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक value,
		  क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	अगर (reg < NITIO_NUM_REGS)
		counter->counter_dev->ग_लिखो(counter, value, reg);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_ग_लिखो);

/**
 * ni_tio_पढ़ो() - Read a TIO रेजिस्टर using the driver provided callback.
 * @counter: काष्ठा ni_gpct counter.
 * @reg: the रेजिस्टर to पढ़ो.
 */
अचिन्हित पूर्णांक ni_tio_पढ़ो(काष्ठा ni_gpct *counter, क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	अगर (reg < NITIO_NUM_REGS)
		वापस counter->counter_dev->पढ़ो(counter, reg);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_पढ़ो);

अटल व्योम ni_tio_reset_count_and_disarm(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित पूर्णांक cidx = counter->counter_index;

	ni_tio_ग_लिखो(counter, GI_RESET(cidx), NITIO_RESET_REG(cidx));
पूर्ण

अटल पूर्णांक ni_tio_घड़ी_period_ps(स्थिर काष्ठा ni_gpct *counter,
				  अचिन्हित पूर्णांक generic_घड़ी_source,
				  u64 *period_ps)
अणु
	u64 घड़ी_period_ps;

	चयन (generic_घड़ी_source & NI_GPCT_CLOCK_SRC_SELECT_MASK) अणु
	हाल NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		घड़ी_period_ps = 50000;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		घड़ी_period_ps = 10000000;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		घड़ी_period_ps = 12500;
		अवरोध;
	हाल NI_GPCT_PXI10_CLOCK_SRC_BITS:
		घड़ी_period_ps = 100000;
		अवरोध;
	शेष:
		/*
		 * घड़ी period is specअगरied by user with prescaling
		 * alपढ़ोy taken पूर्णांकo account.
		 */
		*period_ps = counter->घड़ी_period_ps;
		वापस 0;
	पूर्ण

	चयन (generic_घड़ी_source & NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK) अणु
	हाल NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS:
		अवरोध;
	हाल NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS:
		घड़ी_period_ps *= 2;
		अवरोध;
	हाल NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS:
		घड़ी_period_ps *= 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	*period_ps = घड़ी_period_ps;
	वापस 0;
पूर्ण

अटल व्योम ni_tio_set_bits_transient(काष्ठा ni_gpct *counter,
				      क्रमागत ni_gpct_रेजिस्टर reg,
				      अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value,
				      अचिन्हित पूर्णांक transient)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित दीर्घ flags;

	अगर (reg < NITIO_NUM_REGS && chip < counter_dev->num_chips) अणु
		अचिन्हित पूर्णांक *regs = counter_dev->regs[chip];

		spin_lock_irqsave(&counter_dev->regs_lock, flags);
		regs[reg] &= ~mask;
		regs[reg] |= (value & mask);
		ni_tio_ग_लिखो(counter, regs[reg] | transient, reg);
		spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
	पूर्ण
पूर्ण

/**
 * ni_tio_set_bits() - Safely ग_लिखो a counter रेजिस्टर.
 * @counter: काष्ठा ni_gpct counter.
 * @reg: the रेजिस्टर to ग_लिखो.
 * @mask: the bits to change.
 * @value: the new bits value.
 *
 * Used to ग_लिखो to, and update the software copy, a रेजिस्टर whose bits may
 * be twiddled in पूर्णांकerrupt context, or whose software copy may be पढ़ो in
 * पूर्णांकerrupt context.
 */
व्योम ni_tio_set_bits(काष्ठा ni_gpct *counter, क्रमागत ni_gpct_रेजिस्टर reg,
		     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	ni_tio_set_bits_transient(counter, reg, mask, value, 0x0);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_set_bits);

/**
 * ni_tio_get_soft_copy() - Safely पढ़ो the software copy of a counter रेजिस्टर.
 * @counter: काष्ठा ni_gpct counter.
 * @reg: the रेजिस्टर to पढ़ो.
 *
 * Used to get the software copy of a रेजिस्टर whose bits might be modअगरied
 * in पूर्णांकerrupt context, or whose software copy might need to be पढ़ो in
 * पूर्णांकerrupt context.
 */
अचिन्हित पूर्णांक ni_tio_get_soft_copy(स्थिर काष्ठा ni_gpct *counter,
				  क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित पूर्णांक value = 0;
	अचिन्हित दीर्घ flags;

	अगर (reg < NITIO_NUM_REGS && chip < counter_dev->num_chips) अणु
		spin_lock_irqsave(&counter_dev->regs_lock, flags);
		value = counter_dev->regs[chip][reg];
		spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
	पूर्ण
	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_get_soft_copy);

अटल अचिन्हित पूर्णांक ni_tio_घड़ी_src_modअगरiers(स्थिर काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक counting_mode_bits =
		ni_tio_get_soft_copy(counter, NITIO_CNT_MODE_REG(cidx));
	अचिन्हित पूर्णांक bits = 0;

	अगर (ni_tio_get_soft_copy(counter, NITIO_INPUT_SEL_REG(cidx)) &
	    GI_SRC_POL_INVERT)
		bits |= NI_GPCT_INVERT_CLOCK_SRC_BIT;
	अगर (counting_mode_bits & GI_PRESCALE_X2(counter_dev->variant))
		bits |= NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS;
	अगर (counting_mode_bits & GI_PRESCALE_X8(counter_dev->variant))
		bits |= NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS;
	वापस bits;
पूर्ण

अटल पूर्णांक ni_m_series_घड़ी_src_select(स्थिर काष्ठा ni_gpct *counter,
					अचिन्हित पूर्णांक *clk_src)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित पूर्णांक second_gate_reg = NITIO_GATE2_REG(cidx);
	अचिन्हित पूर्णांक घड़ी_source = 0;
	अचिन्हित पूर्णांक src;
	अचिन्हित पूर्णांक i;

	src = GI_BITS_TO_SRC(ni_tio_get_soft_copy(counter,
						  NITIO_INPUT_SEL_REG(cidx)));

	चयन (src) अणु
	हाल NI_M_TIMEBASE_1_CLK:
		घड़ी_source = NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_TIMEBASE_2_CLK:
		घड़ी_source = NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_TIMEBASE_3_CLK:
		अगर (counter_dev->regs[chip][second_gate_reg] & GI_SRC_SUBSEL)
			घड़ी_source =
			    NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS;
		अन्यथा
			घड़ी_source = NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_LOGIC_LOW_CLK:
		घड़ी_source = NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_NEXT_GATE_CLK:
		अगर (counter_dev->regs[chip][second_gate_reg] & GI_SRC_SUBSEL)
			घड़ी_source = NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS;
		अन्यथा
			घड़ी_source = NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_PXI10_CLK:
		घड़ी_source = NI_GPCT_PXI10_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_M_NEXT_TC_CLK:
		घड़ी_source = NI_GPCT_NEXT_TC_CLOCK_SRC_BITS;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) अणु
			अगर (src == NI_M_RTSI_CLK(i)) अणु
				घड़ी_source = NI_GPCT_RTSI_CLOCK_SRC_BITS(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) अणु
			अगर (src == NI_M_PFI_CLK(i)) अणु
				घड़ी_source = NI_GPCT_PFI_CLOCK_SRC_BITS(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_PFI_CHAN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	घड़ी_source |= ni_tio_घड़ी_src_modअगरiers(counter);
	*clk_src = घड़ी_source;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_घड़ी_src_select(स्थिर काष्ठा ni_gpct *counter,
				    अचिन्हित पूर्णांक *clk_src)
अणु
	अचिन्हित पूर्णांक घड़ी_source = 0;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक src;
	अचिन्हित पूर्णांक i;

	src = GI_BITS_TO_SRC(ni_tio_get_soft_copy(counter,
						  NITIO_INPUT_SEL_REG(cidx)));

	चयन (src) अणु
	हाल NI_660X_TIMEBASE_1_CLK:
		घड़ी_source = NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_TIMEBASE_2_CLK:
		घड़ी_source = NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_TIMEBASE_3_CLK:
		घड़ी_source = NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_LOGIC_LOW_CLK:
		घड़ी_source = NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_SRC_PIN_I_CLK:
		घड़ी_source = NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_NEXT_GATE_CLK:
		घड़ी_source = NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS;
		अवरोध;
	हाल NI_660X_NEXT_TC_CLK:
		घड़ी_source = NI_GPCT_NEXT_TC_CLOCK_SRC_BITS;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (src == NI_660X_RTSI_CLK(i)) अणु
				घड़ी_source = NI_GPCT_RTSI_CLOCK_SRC_BITS(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_SRC_PIN; ++i) अणु
			अगर (src == NI_660X_SRC_PIN_CLK(i)) अणु
				घड़ी_source =
				    NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_SRC_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	घड़ी_source |= ni_tio_घड़ी_src_modअगरiers(counter);
	*clk_src = घड़ी_source;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_tio_generic_घड़ी_src_select(स्थिर काष्ठा ni_gpct *counter,
					   अचिन्हित पूर्णांक *clk_src)
अणु
	चयन (counter->counter_dev->variant) अणु
	हाल ni_gpct_variant_e_series:
	हाल ni_gpct_variant_m_series:
	शेष:
		वापस ni_m_series_घड़ी_src_select(counter, clk_src);
	हाल ni_gpct_variant_660x:
		वापस ni_660x_घड़ी_src_select(counter, clk_src);
	पूर्ण
पूर्ण

अटल व्योम ni_tio_set_sync_mode(काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अटल स्थिर u64 min_normal_sync_period_ps = 25000;
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक bits = 0;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक clk_src = 0;
	u64 ps = 0;
	पूर्णांक ret;
	bool क्रमce_alt_sync;

	/* only m series and 660x variants have counting mode रेजिस्टरs */
	चयन (counter_dev->variant) अणु
	हाल ni_gpct_variant_e_series:
	शेष:
		वापस;
	हाल ni_gpct_variant_m_series:
		mask = GI_M_ALT_SYNC;
		अवरोध;
	हाल ni_gpct_variant_660x:
		mask = GI_660X_ALT_SYNC;
		अवरोध;
	पूर्ण

	reg = NITIO_CNT_MODE_REG(cidx);
	mode = ni_tio_get_soft_copy(counter, reg);
	चयन (mode & GI_CNT_MODE_MASK) अणु
	हाल GI_CNT_MODE_QUADX1:
	हाल GI_CNT_MODE_QUADX2:
	हाल GI_CNT_MODE_QUADX4:
	हाल GI_CNT_MODE_SYNC_SRC:
		क्रमce_alt_sync = true;
		अवरोध;
	शेष:
		क्रमce_alt_sync = false;
		अवरोध;
	पूर्ण

	ret = ni_tio_generic_घड़ी_src_select(counter, &clk_src);
	अगर (ret)
		वापस;
	ret = ni_tio_घड़ी_period_ps(counter, clk_src, &ps);
	अगर (ret)
		वापस;
	/*
	 * It's not clear what we should करो अगर घड़ी_period is unknown, so we
	 * are not using the alt sync bit in that हाल.
	 */
	अगर (क्रमce_alt_sync || (ps && ps < min_normal_sync_period_ps))
		bits = mask;

	ni_tio_set_bits(counter, reg, mask, bits);
पूर्ण

अटल पूर्णांक ni_tio_set_counter_mode(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक mode_reg_mask;
	अचिन्हित पूर्णांक mode_reg_values;
	अचिन्हित पूर्णांक input_select_bits = 0;
	/* these bits map directly on to the mode रेजिस्टर */
	अटल स्थिर अचिन्हित पूर्णांक mode_reg_direct_mask =
	    NI_GPCT_GATE_ON_BOTH_EDGES_BIT | NI_GPCT_EDGE_GATE_MODE_MASK |
	    NI_GPCT_STOP_MODE_MASK | NI_GPCT_OUTPUT_MODE_MASK |
	    NI_GPCT_HARDWARE_DISARM_MASK | NI_GPCT_LOADING_ON_TC_BIT |
	    NI_GPCT_LOADING_ON_GATE_BIT | NI_GPCT_LOAD_B_SELECT_BIT;

	mode_reg_mask = mode_reg_direct_mask | GI_RELOAD_SRC_SWITCHING;
	mode_reg_values = mode & mode_reg_direct_mask;
	चयन (mode & NI_GPCT_RELOAD_SOURCE_MASK) अणु
	हाल NI_GPCT_RELOAD_SOURCE_FIXED_BITS:
		अवरोध;
	हाल NI_GPCT_RELOAD_SOURCE_SWITCHING_BITS:
		mode_reg_values |= GI_RELOAD_SRC_SWITCHING;
		अवरोध;
	हाल NI_GPCT_RELOAD_SOURCE_GATE_SELECT_BITS:
		input_select_bits |= GI_GATE_SEL_LOAD_SRC;
		mode_reg_mask |= GI_GATING_MODE_MASK;
		mode_reg_values |= GI_LEVEL_GATING;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ni_tio_set_bits(counter, NITIO_MODE_REG(cidx),
			mode_reg_mask, mode_reg_values);

	अगर (ni_tio_counting_mode_रेजिस्टरs_present(counter_dev)) अणु
		अचिन्हित पूर्णांक bits = 0;

		bits |= GI_CNT_MODE(mode >> NI_GPCT_COUNTING_MODE_SHIFT);
		bits |= GI_INDEX_PHASE((mode >> NI_GPCT_INDEX_PHASE_BITSHIFT));
		अगर (mode & NI_GPCT_INDEX_ENABLE_BIT)
			bits |= GI_INDEX_MODE;
		ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx),
				GI_CNT_MODE_MASK | GI_INDEX_PHASE_MASK |
				GI_INDEX_MODE, bits);
		ni_tio_set_sync_mode(counter);
	पूर्ण

	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx), GI_CNT_सूची_MASK,
			GI_CNT_सूची(mode >> NI_GPCT_COUNTING_सूचीECTION_SHIFT));

	अगर (mode & NI_GPCT_OR_GATE_BIT)
		input_select_bits |= GI_OR_GATE;
	अगर (mode & NI_GPCT_INVERT_OUTPUT_BIT)
		input_select_bits |= GI_OUTPUT_POL_INVERT;
	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx),
			GI_GATE_SEL_LOAD_SRC | GI_OR_GATE |
			GI_OUTPUT_POL_INVERT, input_select_bits);

	वापस 0;
पूर्ण

पूर्णांक ni_tio_arm(काष्ठा ni_gpct *counter, bool arm, अचिन्हित पूर्णांक start_trigger)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक transient_bits = 0;

	अगर (arm) अणु
		अचिन्हित पूर्णांक mask = 0;
		अचिन्हित पूर्णांक bits = 0;

		/* only m series and 660x have counting mode रेजिस्टरs */
		चयन (counter_dev->variant) अणु
		हाल ni_gpct_variant_e_series:
		शेष:
			अवरोध;
		हाल ni_gpct_variant_m_series:
			mask = GI_M_HW_ARM_SEL_MASK;
			अवरोध;
		हाल ni_gpct_variant_660x:
			mask = GI_660X_HW_ARM_SEL_MASK;
			अवरोध;
		पूर्ण

		चयन (start_trigger) अणु
		हाल NI_GPCT_ARM_IMMEDIATE:
			transient_bits |= GI_ARM;
			अवरोध;
		हाल NI_GPCT_ARM_PAIRED_IMMEDIATE:
			transient_bits |= GI_ARM | GI_ARM_COPY;
			अवरोध;
		शेष:
			/*
			 * क्रम m series and 660x, pass-through the least
			 * signअगरicant bits so we can figure out what select
			 * later
			 */
			अगर (mask && (start_trigger & NI_GPCT_ARM_UNKNOWN)) अणु
				bits |= GI_HW_ARM_ENA |
					(GI_HW_ARM_SEL(start_trigger) & mask);
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (mask)
			ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx),
					GI_HW_ARM_ENA | mask, bits);
	पूर्ण अन्यथा अणु
		transient_bits |= GI_DISARM;
	पूर्ण
	ni_tio_set_bits_transient(counter, NITIO_CMD_REG(cidx),
				  0, 0, transient_bits);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_arm);

अटल पूर्णांक ni_660x_clk_src(अचिन्हित पूर्णांक घड़ी_source, अचिन्हित पूर्णांक *bits)
अणु
	अचिन्हित पूर्णांक clk_src = घड़ी_source & NI_GPCT_CLOCK_SRC_SELECT_MASK;
	अचिन्हित पूर्णांक ni_660x_घड़ी;
	अचिन्हित पूर्णांक i;

	चयन (clk_src) अणु
	हाल NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_TIMEBASE_1_CLK;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_TIMEBASE_2_CLK;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_TIMEBASE_3_CLK;
		अवरोध;
	हाल NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_LOGIC_LOW_CLK;
		अवरोध;
	हाल NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_SRC_PIN_I_CLK;
		अवरोध;
	हाल NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_NEXT_GATE_CLK;
		अवरोध;
	हाल NI_GPCT_NEXT_TC_CLOCK_SRC_BITS:
		ni_660x_घड़ी = NI_660X_NEXT_TC_CLK;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (clk_src == NI_GPCT_RTSI_CLOCK_SRC_BITS(i)) अणु
				ni_660x_घड़ी = NI_660X_RTSI_CLK(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_SRC_PIN; ++i) अणु
			अगर (clk_src == NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(i)) अणु
				ni_660x_घड़ी = NI_660X_SRC_PIN_CLK(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_SRC_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	*bits = GI_SRC_SEL(ni_660x_घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_m_clk_src(अचिन्हित पूर्णांक घड़ी_source, अचिन्हित पूर्णांक *bits)
अणु
	अचिन्हित पूर्णांक clk_src = घड़ी_source & NI_GPCT_CLOCK_SRC_SELECT_MASK;
	अचिन्हित पूर्णांक ni_m_series_घड़ी;
	अचिन्हित पूर्णांक i;

	चयन (clk_src) अणु
	हाल NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_TIMEBASE_1_CLK;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_TIMEBASE_2_CLK;
		अवरोध;
	हाल NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_TIMEBASE_3_CLK;
		अवरोध;
	हाल NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_LOGIC_LOW_CLK;
		अवरोध;
	हाल NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_NEXT_GATE_CLK;
		अवरोध;
	हाल NI_GPCT_NEXT_TC_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_NEXT_TC_CLK;
		अवरोध;
	हाल NI_GPCT_PXI10_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_PXI10_CLK;
		अवरोध;
	हाल NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_PXI_STAR_TRIGGER_CLK;
		अवरोध;
	हाल NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS:
		ni_m_series_घड़ी = NI_M_ANALOG_TRIGGER_OUT_CLK;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) अणु
			अगर (clk_src == NI_GPCT_RTSI_CLOCK_SRC_BITS(i)) अणु
				ni_m_series_घड़ी = NI_M_RTSI_CLK(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) अणु
			अगर (clk_src == NI_GPCT_PFI_CLOCK_SRC_BITS(i)) अणु
				ni_m_series_घड़ी = NI_M_PFI_CLK(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_PFI_CHAN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	*bits = GI_SRC_SEL(ni_m_series_घड़ी);
	वापस 0;
पूर्ण;

अटल व्योम ni_tio_set_source_subselect(काष्ठा ni_gpct *counter,
					अचिन्हित पूर्णांक घड़ी_source)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित पूर्णांक second_gate_reg = NITIO_GATE2_REG(cidx);

	अगर (counter_dev->variant != ni_gpct_variant_m_series)
		वापस;
	चयन (घड़ी_source & NI_GPCT_CLOCK_SRC_SELECT_MASK) अणु
		/* Gi_Source_Subselect is zero */
	हाल NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
	हाल NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		counter_dev->regs[chip][second_gate_reg] &= ~GI_SRC_SUBSEL;
		अवरोध;
		/* Gi_Source_Subselect is one */
	हाल NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS:
	हाल NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS:
		counter_dev->regs[chip][second_gate_reg] |= GI_SRC_SUBSEL;
		अवरोध;
		/* Gi_Source_Subselect करोesn't matter */
	शेष:
		वापस;
	पूर्ण
	ni_tio_ग_लिखो(counter, counter_dev->regs[chip][second_gate_reg],
		     second_gate_reg);
पूर्ण

अटल पूर्णांक ni_tio_set_घड़ी_src(काष्ठा ni_gpct *counter,
				अचिन्हित पूर्णांक घड़ी_source,
				अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक bits = 0;
	पूर्णांक ret;

	चयन (counter_dev->variant) अणु
	हाल ni_gpct_variant_660x:
		ret = ni_660x_clk_src(घड़ी_source, &bits);
		अवरोध;
	हाल ni_gpct_variant_e_series:
	हाल ni_gpct_variant_m_series:
	शेष:
		ret = ni_m_clk_src(घड़ी_source, &bits);
		अवरोध;
	पूर्ण
	अगर (ret) अणु
		काष्ठा comedi_device *dev = counter_dev->dev;

		dev_err(dev->class_dev, "invalid clock source 0x%x\n",
			घड़ी_source);
		वापस ret;
	पूर्ण

	अगर (घड़ी_source & NI_GPCT_INVERT_CLOCK_SRC_BIT)
		bits |= GI_SRC_POL_INVERT;
	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx),
			GI_SRC_SEL_MASK | GI_SRC_POL_INVERT, bits);
	ni_tio_set_source_subselect(counter, घड़ी_source);

	अगर (ni_tio_counting_mode_रेजिस्टरs_present(counter_dev)) अणु
		bits = 0;
		चयन (घड़ी_source & NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK) अणु
		हाल NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS:
			अवरोध;
		हाल NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS:
			bits |= GI_PRESCALE_X2(counter_dev->variant);
			अवरोध;
		हाल NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS:
			bits |= GI_PRESCALE_X8(counter_dev->variant);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx),
				GI_PRESCALE_X2(counter_dev->variant) |
				GI_PRESCALE_X8(counter_dev->variant), bits);
	पूर्ण
	counter->घड़ी_period_ps = period_ns * 1000;
	ni_tio_set_sync_mode(counter);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_tio_get_घड़ी_src(काष्ठा ni_gpct *counter,
				अचिन्हित पूर्णांक *घड़ी_source,
				अचिन्हित पूर्णांक *period_ns)
अणु
	u64 temp64 = 0;
	पूर्णांक ret;

	ret = ni_tio_generic_घड़ी_src_select(counter, घड़ी_source);
	अगर (ret)
		वापस ret;
	ret = ni_tio_घड़ी_period_ps(counter, *घड़ी_source, &temp64);
	अगर (ret)
		वापस ret;
	करो_भाग(temp64, 1000);	/* ps to ns */
	*period_ns = temp64;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ni_tio_set_gate_raw(काष्ठा ni_gpct *counter,
				       अचिन्हित पूर्णांक gate_source)
अणु
	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(counter->counter_index),
			GI_GATE_SEL_MASK, GI_GATE_SEL(gate_source));
पूर्ण

अटल अंतरभूत व्योम ni_tio_set_gate2_raw(काष्ठा ni_gpct *counter,
					अचिन्हित पूर्णांक gate_source)
अणु
	ni_tio_set_bits(counter, NITIO_GATE2_REG(counter->counter_index),
			GI_GATE2_SEL_MASK, GI_GATE2_SEL(gate_source));
पूर्ण

/* Set the mode bits क्रम gate. */
अटल अंतरभूत व्योम ni_tio_set_gate_mode(काष्ठा ni_gpct *counter,
					अचिन्हित पूर्णांक src)
अणु
	अचिन्हित पूर्णांक mode_bits = 0;

	अगर (CR_CHAN(src) & NI_GPCT_DISABLED_GATE_SELECT) अणु
		/*
		 * Allowing bitwise comparison here to allow non-zero raw
		 * रेजिस्टर value to be used क्रम channel when disabling.
		 */
		mode_bits = GI_GATING_DISABLED;
	पूर्ण अन्यथा अणु
		अगर (src & CR_INVERT)
			mode_bits |= GI_GATE_POL_INVERT;
		अगर (src & CR_EDGE)
			mode_bits |= GI_RISING_EDGE_GATING;
		अन्यथा
			mode_bits |= GI_LEVEL_GATING;
	पूर्ण
	ni_tio_set_bits(counter, NITIO_MODE_REG(counter->counter_index),
			GI_GATE_POL_INVERT | GI_GATING_MODE_MASK,
			mode_bits);
पूर्ण

/*
 * Set the mode bits क्रम gate2.
 *
 * Previously, the code this function represents did not actually ग_लिखो anything
 * to the रेजिस्टर.  Rather, writing to this रेजिस्टर was reserved क्रम the code
 * ni ni_tio_set_gate2_raw.
 */
अटल अंतरभूत व्योम ni_tio_set_gate2_mode(काष्ठा ni_gpct *counter,
					 अचिन्हित पूर्णांक src)
अणु
	/*
	 * The GI_GATE2_MODE bit was previously set in the code that also sets
	 * the gate2 source.
	 * We'll set mode bits _after_ source bits now, and thus, this function
	 * will effectively enable the second gate after all bits are set.
	 */
	अचिन्हित पूर्णांक mode_bits = GI_GATE2_MODE;

	अगर (CR_CHAN(src) & NI_GPCT_DISABLED_GATE_SELECT)
		/*
		 * Allowing bitwise comparison here to allow non-zero raw
		 * रेजिस्टर value to be used क्रम channel when disabling.
		 */
		mode_bits = GI_GATING_DISABLED;
	अगर (src & CR_INVERT)
		mode_bits |= GI_GATE2_POL_INVERT;

	ni_tio_set_bits(counter, NITIO_GATE2_REG(counter->counter_index),
			GI_GATE2_POL_INVERT | GI_GATE2_MODE, mode_bits);
पूर्ण

अटल पूर्णांक ni_660x_set_gate(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate_source)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(gate_source);
	अचिन्हित पूर्णांक gate_sel;
	अचिन्हित पूर्णांक i;

	चयन (chan) अणु
	हाल NI_GPCT_NEXT_SOURCE_GATE_SELECT:
		gate_sel = NI_660X_NEXT_SRC_GATE_SEL;
		अवरोध;
	हाल NI_GPCT_NEXT_OUT_GATE_SELECT:
	हाल NI_GPCT_LOGIC_LOW_GATE_SELECT:
	हाल NI_GPCT_SOURCE_PIN_i_GATE_SELECT:
	हाल NI_GPCT_GATE_PIN_i_GATE_SELECT:
		gate_sel = chan & 0x1f;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (chan == NI_GPCT_RTSI_GATE_SELECT(i)) अणु
				gate_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_GATE_PIN; ++i) अणु
			अगर (chan == NI_GPCT_GATE_PIN_GATE_SELECT(i)) अणु
				gate_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_GATE_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	ni_tio_set_gate_raw(counter, gate_sel);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_m_set_gate(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate_source)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(gate_source);
	अचिन्हित पूर्णांक gate_sel;
	अचिन्हित पूर्णांक i;

	चयन (chan) अणु
	हाल NI_GPCT_TIMESTAMP_MUX_GATE_SELECT:
	हाल NI_GPCT_AI_START2_GATE_SELECT:
	हाल NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT:
	हाल NI_GPCT_NEXT_OUT_GATE_SELECT:
	हाल NI_GPCT_AI_START1_GATE_SELECT:
	हाल NI_GPCT_NEXT_SOURCE_GATE_SELECT:
	हाल NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT:
	हाल NI_GPCT_LOGIC_LOW_GATE_SELECT:
		gate_sel = chan & 0x1f;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) अणु
			अगर (chan == NI_GPCT_RTSI_GATE_SELECT(i)) अणु
				gate_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) अणु
			अगर (chan == NI_GPCT_PFI_GATE_SELECT(i)) अणु
				gate_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_PFI_CHAN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	ni_tio_set_gate_raw(counter, gate_sel);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_set_gate2(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate_source)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(gate_source);
	अचिन्हित पूर्णांक gate2_sel;
	अचिन्हित पूर्णांक i;

	चयन (chan) अणु
	हाल NI_GPCT_SOURCE_PIN_i_GATE_SELECT:
	हाल NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT:
	हाल NI_GPCT_SELECTED_GATE_GATE_SELECT:
	हाल NI_GPCT_NEXT_OUT_GATE_SELECT:
	हाल NI_GPCT_LOGIC_LOW_GATE_SELECT:
		gate2_sel = chan & 0x1f;
		अवरोध;
	हाल NI_GPCT_NEXT_SOURCE_GATE_SELECT:
		gate2_sel = NI_660X_NEXT_SRC_GATE2_SEL;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (chan == NI_GPCT_RTSI_GATE_SELECT(i)) अणु
				gate2_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_UP_DOWN_PIN; ++i) अणु
			अगर (chan == NI_GPCT_UP_DOWN_PIN_GATE_SELECT(i)) अणु
				gate2_sel = chan & 0x1f;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_UP_DOWN_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	ni_tio_set_gate2_raw(counter, gate2_sel);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_m_set_gate2(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate_source)
अणु
	/*
	 * FIXME: We करोn't know what the m-series second gate codes are,
	 * so we'll just pass the bits through क्रम now.
	 */
	ni_tio_set_gate2_raw(counter, gate_source);
	वापस 0;
पूर्ण

पूर्णांक ni_tio_set_gate_src_raw(काष्ठा ni_gpct *counter,
			    अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक src)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;

	चयन (gate) अणु
	हाल 0:
		/* 1.  start by disabling gate */
		ni_tio_set_gate_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		ni_tio_set_gate_raw(counter, src);
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate_mode(counter, src);
		अवरोध;
	हाल 1:
		अगर (!ni_tio_has_gate2_रेजिस्टरs(counter_dev))
			वापस -EINVAL;

		/* 1.  start by disabling gate */
		ni_tio_set_gate2_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		ni_tio_set_gate2_raw(counter, src);
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate2_mode(counter, src);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_set_gate_src_raw);

पूर्णांक ni_tio_set_gate_src(काष्ठा ni_gpct *counter,
			अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक src)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	/*
	 * mask off disable flag.  This high bit still passes CR_CHAN.
	 * Doing this allows one to both set the gate as disabled, but also
	 * change the route value of the gate.
	 */
	पूर्णांक chan = CR_CHAN(src) & (~NI_GPCT_DISABLED_GATE_SELECT);
	पूर्णांक ret;

	चयन (gate) अणु
	हाल 0:
		/* 1.  start by disabling gate */
		ni_tio_set_gate_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		चयन (counter_dev->variant) अणु
		हाल ni_gpct_variant_e_series:
		हाल ni_gpct_variant_m_series:
			ret = ni_m_set_gate(counter, chan);
			अवरोध;
		हाल ni_gpct_variant_660x:
			ret = ni_660x_set_gate(counter, chan);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (ret)
			वापस ret;
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate_mode(counter, src);
		अवरोध;
	हाल 1:
		अगर (!ni_tio_has_gate2_रेजिस्टरs(counter_dev))
			वापस -EINVAL;

		/* 1.  start by disabling gate */
		ni_tio_set_gate2_mode(counter, NI_GPCT_DISABLED_GATE_SELECT);
		/* 2.  set the requested gate source */
		चयन (counter_dev->variant) अणु
		हाल ni_gpct_variant_m_series:
			ret = ni_m_set_gate2(counter, chan);
			अवरोध;
		हाल ni_gpct_variant_660x:
			ret = ni_660x_set_gate2(counter, chan);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (ret)
			वापस ret;
		/* 3.  reenable & set mode to starts things back up */
		ni_tio_set_gate2_mode(counter, src);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_set_gate_src);

अटल पूर्णांक ni_tio_set_other_src(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक index,
				अचिन्हित पूर्णांक source)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित पूर्णांक abz_reg, shअगरt, mask;

	अगर (counter_dev->variant != ni_gpct_variant_m_series)
		वापस -EINVAL;

	abz_reg = NITIO_ABZ_REG(cidx);

	/* allow क्रम new device-global names */
	अगर (index == NI_GPCT_SOURCE_ENCODER_A ||
	    (index >= NI_CtrA(0) && index <= NI_CtrA(-1))) अणु
		shअगरt = 10;
	पूर्ण अन्यथा अगर (index == NI_GPCT_SOURCE_ENCODER_B ||
	    (index >= NI_CtrB(0) && index <= NI_CtrB(-1))) अणु
		shअगरt = 5;
	पूर्ण अन्यथा अगर (index == NI_GPCT_SOURCE_ENCODER_Z ||
	    (index >= NI_CtrZ(0) && index <= NI_CtrZ(-1))) अणु
		shअगरt = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mask = 0x1f << shअगरt;
	अगर (source > 0x1f)
		source = 0x1f;	/* Disable gate */

	counter_dev->regs[chip][abz_reg] &= ~mask;
	counter_dev->regs[chip][abz_reg] |= (source << shअगरt) & mask;
	ni_tio_ग_लिखो(counter, counter_dev->regs[chip][abz_reg], abz_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_tio_get_other_src(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक index,
				अचिन्हित पूर्णांक *source)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक abz_reg, shअगरt, mask;

	अगर (counter_dev->variant != ni_gpct_variant_m_series)
		/* A,B,Z only valid क्रम m-series */
		वापस -EINVAL;

	abz_reg = NITIO_ABZ_REG(cidx);

	/* allow क्रम new device-global names */
	अगर (index == NI_GPCT_SOURCE_ENCODER_A ||
	    (index >= NI_CtrA(0) && index <= NI_CtrA(-1))) अणु
		shअगरt = 10;
	पूर्ण अन्यथा अगर (index == NI_GPCT_SOURCE_ENCODER_B ||
	    (index >= NI_CtrB(0) && index <= NI_CtrB(-1))) अणु
		shअगरt = 5;
	पूर्ण अन्यथा अगर (index == NI_GPCT_SOURCE_ENCODER_Z ||
	    (index >= NI_CtrZ(0) && index <= NI_CtrZ(-1))) अणु
		shअगरt = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mask = 0x1f;

	*source = (ni_tio_get_soft_copy(counter, abz_reg) >> shअगरt) & mask;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_gate_to_generic_gate(अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक *src)
अणु
	अचिन्हित पूर्णांक source;
	अचिन्हित पूर्णांक i;

	चयन (gate) अणु
	हाल NI_660X_SRC_PIN_I_GATE_SEL:
		source = NI_GPCT_SOURCE_PIN_i_GATE_SELECT;
		अवरोध;
	हाल NI_660X_GATE_PIN_I_GATE_SEL:
		source = NI_GPCT_GATE_PIN_i_GATE_SELECT;
		अवरोध;
	हाल NI_660X_NEXT_SRC_GATE_SEL:
		source = NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		अवरोध;
	हाल NI_660X_NEXT_OUT_GATE_SEL:
		source = NI_GPCT_NEXT_OUT_GATE_SELECT;
		अवरोध;
	हाल NI_660X_LOGIC_LOW_GATE_SEL:
		source = NI_GPCT_LOGIC_LOW_GATE_SELECT;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (gate == NI_660X_RTSI_GATE_SEL(i)) अणु
				source = NI_GPCT_RTSI_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_GATE_PIN; ++i) अणु
			अगर (gate == NI_660X_PIN_GATE_SEL(i)) अणु
				source = NI_GPCT_GATE_PIN_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_GATE_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	*src = source;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_m_gate_to_generic_gate(अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक *src)
अणु
	अचिन्हित पूर्णांक source;
	अचिन्हित पूर्णांक i;

	चयन (gate) अणु
	हाल NI_M_TIMESTAMP_MUX_GATE_SEL:
		source = NI_GPCT_TIMESTAMP_MUX_GATE_SELECT;
		अवरोध;
	हाल NI_M_AI_START2_GATE_SEL:
		source = NI_GPCT_AI_START2_GATE_SELECT;
		अवरोध;
	हाल NI_M_PXI_STAR_TRIGGER_GATE_SEL:
		source = NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT;
		अवरोध;
	हाल NI_M_NEXT_OUT_GATE_SEL:
		source = NI_GPCT_NEXT_OUT_GATE_SELECT;
		अवरोध;
	हाल NI_M_AI_START1_GATE_SEL:
		source = NI_GPCT_AI_START1_GATE_SELECT;
		अवरोध;
	हाल NI_M_NEXT_SRC_GATE_SEL:
		source = NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		अवरोध;
	हाल NI_M_ANALOG_TRIG_OUT_GATE_SEL:
		source = NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT;
		अवरोध;
	हाल NI_M_LOGIC_LOW_GATE_SEL:
		source = NI_GPCT_LOGIC_LOW_GATE_SELECT;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) अणु
			अगर (gate == NI_M_RTSI_GATE_SEL(i)) अणु
				source = NI_GPCT_RTSI_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) अणु
			अगर (gate == NI_M_PFI_GATE_SEL(i)) अणु
				source = NI_GPCT_PFI_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_M_MAX_PFI_CHAN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	*src = source;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_gate2_to_generic_gate(अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक *src)
अणु
	अचिन्हित पूर्णांक source;
	अचिन्हित पूर्णांक i;

	चयन (gate) अणु
	हाल NI_660X_SRC_PIN_I_GATE2_SEL:
		source = NI_GPCT_SOURCE_PIN_i_GATE_SELECT;
		अवरोध;
	हाल NI_660X_UD_PIN_I_GATE2_SEL:
		source = NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT;
		अवरोध;
	हाल NI_660X_NEXT_SRC_GATE2_SEL:
		source = NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		अवरोध;
	हाल NI_660X_NEXT_OUT_GATE2_SEL:
		source = NI_GPCT_NEXT_OUT_GATE_SELECT;
		अवरोध;
	हाल NI_660X_SELECTED_GATE2_SEL:
		source = NI_GPCT_SELECTED_GATE_GATE_SELECT;
		अवरोध;
	हाल NI_660X_LOGIC_LOW_GATE2_SEL:
		source = NI_GPCT_LOGIC_LOW_GATE_SELECT;
		अवरोध;
	शेष:
		क्रम (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) अणु
			अगर (gate == NI_660X_RTSI_GATE2_SEL(i)) अणु
				source = NI_GPCT_RTSI_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_RTSI_CHAN)
			अवरोध;
		क्रम (i = 0; i <= NI_660X_MAX_UP_DOWN_PIN; ++i) अणु
			अगर (gate == NI_660X_UD_PIN_GATE2_SEL(i)) अणु
				source = NI_GPCT_UP_DOWN_PIN_GATE_SELECT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i <= NI_660X_MAX_UP_DOWN_PIN)
			अवरोध;
		वापस -EINVAL;
	पूर्ण
	*src = source;
	वापस 0;
पूर्ण

अटल पूर्णांक ni_m_gate2_to_generic_gate(अचिन्हित पूर्णांक gate, अचिन्हित पूर्णांक *src)
अणु
	/*
	 * FIXME: the second gate sources क्रम the m series are unकरोcumented,
	 * so we just वापस the raw bits क्रम now.
	 */
	*src = gate;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ni_tio_get_gate_mode(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित पूर्णांक mode = ni_tio_get_soft_copy(counter,
				NITIO_MODE_REG(counter->counter_index));
	अचिन्हित पूर्णांक ret = 0;

	अगर ((mode & GI_GATING_MODE_MASK) == GI_GATING_DISABLED)
		ret |= NI_GPCT_DISABLED_GATE_SELECT;
	अगर (mode & GI_GATE_POL_INVERT)
		ret |= CR_INVERT;
	अगर ((mode & GI_GATING_MODE_MASK) != GI_LEVEL_GATING)
		ret |= CR_EDGE;

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ni_tio_get_gate2_mode(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित पूर्णांक mode = ni_tio_get_soft_copy(counter,
				NITIO_GATE2_REG(counter->counter_index));
	अचिन्हित पूर्णांक ret = 0;

	अगर (!(mode & GI_GATE2_MODE))
		ret |= NI_GPCT_DISABLED_GATE_SELECT;
	अगर (mode & GI_GATE2_POL_INVERT)
		ret |= CR_INVERT;

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ni_tio_get_gate_val(काष्ठा ni_gpct *counter)
अणु
	वापस GI_BITS_TO_GATE(ni_tio_get_soft_copy(counter,
		NITIO_INPUT_SEL_REG(counter->counter_index)));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ni_tio_get_gate2_val(काष्ठा ni_gpct *counter)
अणु
	वापस GI_BITS_TO_GATE2(ni_tio_get_soft_copy(counter,
		NITIO_GATE2_REG(counter->counter_index)));
पूर्ण

अटल पूर्णांक ni_tio_get_gate_src(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate_index,
			       अचिन्हित पूर्णांक *gate_source)
अणु
	अचिन्हित पूर्णांक gate;
	पूर्णांक ret;

	चयन (gate_index) अणु
	हाल 0:
		gate = ni_tio_get_gate_val(counter);
		चयन (counter->counter_dev->variant) अणु
		हाल ni_gpct_variant_e_series:
		हाल ni_gpct_variant_m_series:
		शेष:
			ret = ni_m_gate_to_generic_gate(gate, gate_source);
			अवरोध;
		हाल ni_gpct_variant_660x:
			ret = ni_660x_gate_to_generic_gate(gate, gate_source);
			अवरोध;
		पूर्ण
		अगर (ret)
			वापस ret;
		*gate_source |= ni_tio_get_gate_mode(counter);
		अवरोध;
	हाल 1:
		gate = ni_tio_get_gate2_val(counter);
		चयन (counter->counter_dev->variant) अणु
		हाल ni_gpct_variant_e_series:
		हाल ni_gpct_variant_m_series:
		शेष:
			ret = ni_m_gate2_to_generic_gate(gate, gate_source);
			अवरोध;
		हाल ni_gpct_variant_660x:
			ret = ni_660x_gate2_to_generic_gate(gate, gate_source);
			अवरोध;
		पूर्ण
		अगर (ret)
			वापस ret;
		*gate_source |= ni_tio_get_gate2_mode(counter);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_tio_get_gate_src_raw(काष्ठा ni_gpct *counter,
				   अचिन्हित पूर्णांक gate_index,
				   अचिन्हित पूर्णांक *gate_source)
अणु
	चयन (gate_index) अणु
	हाल 0:
		*gate_source = ni_tio_get_gate_mode(counter)
			     | ni_tio_get_gate_val(counter);
		अवरोध;
	हाल 1:
		*gate_source = ni_tio_get_gate2_mode(counter)
			     | ni_tio_get_gate2_val(counter);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ni_tio_insn_config(काष्ठा comedi_device *dev,
		       काष्ठा comedi_subdevice *s,
		       काष्ठा comedi_insn *insn,
		       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret = 0;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_COUNTER_MODE:
		ret = ni_tio_set_counter_mode(counter, data[1]);
		अवरोध;
	हाल INSN_CONFIG_ARM:
		ret = ni_tio_arm(counter, true, data[1]);
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		ret = ni_tio_arm(counter, false, 0);
		अवरोध;
	हाल INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		status = ni_tio_पढ़ो(counter, NITIO_SHARED_STATUS_REG(cidx));
		अगर (status & GI_ARMED(cidx)) अणु
			data[1] |= COMEDI_COUNTER_ARMED;
			अगर (status & GI_COUNTING(cidx))
				data[1] |= COMEDI_COUNTER_COUNTING;
		पूर्ण
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING;
		अवरोध;
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		ret = ni_tio_set_घड़ी_src(counter, data[1], data[2]);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		ret = ni_tio_get_घड़ी_src(counter, &data[1], &data[2]);
		अवरोध;
	हाल INSN_CONFIG_SET_GATE_SRC:
		ret = ni_tio_set_gate_src(counter, data[1], data[2]);
		अवरोध;
	हाल INSN_CONFIG_GET_GATE_SRC:
		ret = ni_tio_get_gate_src(counter, data[1], &data[2]);
		अवरोध;
	हाल INSN_CONFIG_SET_OTHER_SRC:
		ret = ni_tio_set_other_src(counter, data[1], data[2]);
		अवरोध;
	हाल INSN_CONFIG_RESET:
		ni_tio_reset_count_and_disarm(counter);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret ? ret : insn->n;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_insn_config);

/**
 * Retrieves the रेजिस्टर value of the current source of the output selector क्रम
 * the given destination.
 *
 * If the terminal क्रम the destination is not alपढ़ोy configured as an output,
 * this function वापसs -EINVAL as error.
 *
 * Return: the रेजिस्टर value of the destination output selector;
 *         -EINVAL अगर terminal is not configured क्रम output.
 */
पूर्णांक ni_tio_get_routing(काष्ठा ni_gpct_device *counter_dev, अचिन्हित पूर्णांक dest)
अणु
	/* we need to know the actual counter below... */
	पूर्णांक ctr_index = (dest - NI_COUNTER_NAMES_BASE) % NI_MAX_COUNTERS;
	काष्ठा ni_gpct *counter = &counter_dev->counters[ctr_index];
	पूर्णांक ret = 1;
	अचिन्हित पूर्णांक reg;

	अगर (dest >= NI_CtrA(0) && dest <= NI_CtrZ(-1)) अणु
		ret = ni_tio_get_other_src(counter, dest, &reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrGate(0) && dest <= NI_CtrGate(-1)) अणु
		ret = ni_tio_get_gate_src_raw(counter, 0, &reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrAux(0) && dest <= NI_CtrAux(-1)) अणु
		ret = ni_tio_get_gate_src_raw(counter, 1, &reg);
	/*
	 * This हाल is not possible through this पूर्णांकerface.  A user must use
	 * INSN_CONFIG_SET_CLOCK_SRC instead.
	 * पूर्ण अन्यथा अगर (dest >= NI_CtrSource(0) && dest <= NI_CtrSource(-1)) अणु
	 *	ret = ni_tio_set_घड़ी_src(counter, &reg, &period_ns);
	 */
	पूर्ण

	अगर (ret)
		वापस -EINVAL;

	वापस reg;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_get_routing);

/**
 * Sets the रेजिस्टर value of the selector MUX क्रम the given destination.
 * @counter_dev:Poपूर्णांकer to general counter device.
 * @destination:Device-global identअगरier of route destination.
 * @रेजिस्टर_value:
 *		The first several bits of this value should store the desired
 *		value to ग_लिखो to the रेजिस्टर.  All other bits are क्रम
 *		transmitting inक्रमmation that modअगरy the mode of the particular
 *		destination/gate.  These mode bits might include a bitwise or of
 *		CR_INVERT and CR_EDGE.  Note that the calling function should
 *		have alपढ़ोy validated the correctness of this value.
 */
पूर्णांक ni_tio_set_routing(काष्ठा ni_gpct_device *counter_dev, अचिन्हित पूर्णांक dest,
		       अचिन्हित पूर्णांक reg)
अणु
	/* we need to know the actual counter below... */
	पूर्णांक ctr_index = (dest - NI_COUNTER_NAMES_BASE) % NI_MAX_COUNTERS;
	काष्ठा ni_gpct *counter = &counter_dev->counters[ctr_index];
	पूर्णांक ret;

	अगर (dest >= NI_CtrA(0) && dest <= NI_CtrZ(-1)) अणु
		ret = ni_tio_set_other_src(counter, dest, reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrGate(0) && dest <= NI_CtrGate(-1)) अणु
		ret = ni_tio_set_gate_src_raw(counter, 0, reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrAux(0) && dest <= NI_CtrAux(-1)) अणु
		ret = ni_tio_set_gate_src_raw(counter, 1, reg);
	/*
	 * This हाल is not possible through this पूर्णांकerface.  A user must use
	 * INSN_CONFIG_SET_CLOCK_SRC instead.
	 * पूर्ण अन्यथा अगर (dest >= NI_CtrSource(0) && dest <= NI_CtrSource(-1)) अणु
	 *	ret = ni_tio_set_घड़ी_src(counter, reg, period_ns);
	 */
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_set_routing);

/**
 * Sets the given destination MUX to its शेष value or disable it.
 *
 * Return: 0 अगर successful; -EINVAL अगर terminal is unknown.
 */
पूर्णांक ni_tio_unset_routing(काष्ठा ni_gpct_device *counter_dev, अचिन्हित पूर्णांक dest)
अणु
	अगर (dest >= NI_GATES_NAMES_BASE && dest <= NI_GATES_NAMES_MAX)
		/* Disable gate (via mode bits) and set to शेष 0-value */
		वापस ni_tio_set_routing(counter_dev, dest,
					  NI_GPCT_DISABLED_GATE_SELECT);
	/*
	 * This हाल is not possible through this पूर्णांकerface.  A user must use
	 * INSN_CONFIG_SET_CLOCK_SRC instead.
	 * अगर (dest >= NI_CtrSource(0) && dest <= NI_CtrSource(-1))
	 *	वापस ni_tio_set_घड़ी_src(counter, reg, period_ns);
	 */

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_unset_routing);

अटल अचिन्हित पूर्णांक ni_tio_पढ़ो_sw_save_reg(काष्ठा comedi_device *dev,
					    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक val;

	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx), GI_SAVE_TRACE, 0);
	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx),
			GI_SAVE_TRACE, GI_SAVE_TRACE);

	/*
	 * The count करोesn't get latched until the next घड़ी edge, so it is
	 * possible the count may change (once) जबतक we are पढ़ोing. Since
	 * the पढ़ो of the SW_Save_Reg isn't atomic (apparently even when it's
	 * a 32 bit रेजिस्टर according to 660x करोcs), we need to पढ़ो twice
	 * and make sure the पढ़ोing hasn't changed. If it has, a third पढ़ो
	 * will be correct since the count value will definitely have latched
	 * by then.
	 */
	val = ni_tio_पढ़ो(counter, NITIO_SW_SAVE_REG(cidx));
	अगर (val != ni_tio_पढ़ो(counter, NITIO_SW_SAVE_REG(cidx)))
		val = ni_tio_पढ़ो(counter, NITIO_SW_SAVE_REG(cidx));

	वापस val;
पूर्ण

पूर्णांक ni_tio_insn_पढ़ो(काष्ठा comedi_device *dev,
		     काष्ठा comedi_subdevice *s,
		     काष्ठा comedi_insn *insn,
		     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक channel = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		चयन (channel) अणु
		हाल 0:
			data[i] = ni_tio_पढ़ो_sw_save_reg(dev, s);
			अवरोध;
		हाल 1:
			data[i] =
			    counter_dev->regs[chip][NITIO_LOADA_REG(cidx)];
			अवरोध;
		हाल 2:
			data[i] =
			    counter_dev->regs[chip][NITIO_LOADB_REG(cidx)];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस insn->n;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_insn_पढ़ो);

अटल अचिन्हित पूर्णांक ni_tio_next_load_रेजिस्टर(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक bits = ni_tio_पढ़ो(counter, NITIO_SHARED_STATUS_REG(cidx));

	वापस (bits & GI_NEXT_LOAD_SRC(cidx))
			? NITIO_LOADB_REG(cidx)
			: NITIO_LOADA_REG(cidx);
पूर्ण

पूर्णांक ni_tio_insn_ग_लिखो(काष्ठा comedi_device *dev,
		      काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_insn *insn,
		      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक channel = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;
	अचिन्हित पूर्णांक load_reg;
	अचिन्हित पूर्णांक load_val;

	अगर (insn->n < 1)
		वापस 0;
	load_val = data[insn->n - 1];
	चयन (channel) अणु
	हाल 0:
		/*
		 * Unsafe अगर counter is armed.
		 * Should probably check status and वापस -EBUSY अगर armed.
		 */

		/*
		 * Don't disturb load source select, just use whichever
		 * load रेजिस्टर is alपढ़ोy selected.
		 */
		load_reg = ni_tio_next_load_रेजिस्टर(counter);
		ni_tio_ग_लिखो(counter, load_val, load_reg);
		ni_tio_set_bits_transient(counter, NITIO_CMD_REG(cidx),
					  0, 0, GI_LOAD);
		/* restore load reg */
		ni_tio_ग_लिखो(counter, counter_dev->regs[chip][load_reg],
			     load_reg);
		अवरोध;
	हाल 1:
		counter_dev->regs[chip][NITIO_LOADA_REG(cidx)] = load_val;
		ni_tio_ग_लिखो(counter, load_val, NITIO_LOADA_REG(cidx));
		अवरोध;
	हाल 2:
		counter_dev->regs[chip][NITIO_LOADB_REG(cidx)] = load_val;
		ni_tio_ग_लिखो(counter, load_val, NITIO_LOADB_REG(cidx));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस insn->n;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_insn_ग_लिखो);

व्योम ni_tio_init_counter(काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक chip = counter->chip_index;

	ni_tio_reset_count_and_disarm(counter);

	/* initialize counter रेजिस्टरs */
	counter_dev->regs[chip][NITIO_AUTO_INC_REG(cidx)] = 0x0;
	ni_tio_ग_लिखो(counter, 0x0, NITIO_AUTO_INC_REG(cidx));

	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx),
			~0, GI_SYNC_GATE);

	ni_tio_set_bits(counter, NITIO_MODE_REG(cidx), ~0, 0);

	counter_dev->regs[chip][NITIO_LOADA_REG(cidx)] = 0x0;
	ni_tio_ग_लिखो(counter, 0x0, NITIO_LOADA_REG(cidx));

	counter_dev->regs[chip][NITIO_LOADB_REG(cidx)] = 0x0;
	ni_tio_ग_लिखो(counter, 0x0, NITIO_LOADB_REG(cidx));

	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx), ~0, 0);

	अगर (ni_tio_counting_mode_रेजिस्टरs_present(counter_dev))
		ni_tio_set_bits(counter, NITIO_CNT_MODE_REG(cidx), ~0, 0);

	अगर (ni_tio_has_gate2_रेजिस्टरs(counter_dev)) अणु
		counter_dev->regs[chip][NITIO_GATE2_REG(cidx)] = 0x0;
		ni_tio_ग_लिखो(counter, 0x0, NITIO_GATE2_REG(cidx));
	पूर्ण

	ni_tio_set_bits(counter, NITIO_DMA_CFG_REG(cidx), ~0, 0x0);

	ni_tio_set_bits(counter, NITIO_INT_ENA_REG(cidx), ~0, 0x0);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_init_counter);

काष्ठा ni_gpct_device *
ni_gpct_device_स्थिरruct(काष्ठा comedi_device *dev,
			 व्योम (*ग_लिखो)(काष्ठा ni_gpct *counter,
				       अचिन्हित पूर्णांक value,
				       क्रमागत ni_gpct_रेजिस्टर reg),
			 अचिन्हित पूर्णांक (*पढ़ो)(काष्ठा ni_gpct *counter,
					      क्रमागत ni_gpct_रेजिस्टर reg),
			 क्रमागत ni_gpct_variant variant,
			 अचिन्हित पूर्णांक num_counters,
			 अचिन्हित पूर्णांक counters_per_chip,
			 स्थिर काष्ठा ni_route_tables *routing_tables)
अणु
	काष्ठा ni_gpct_device *counter_dev;
	काष्ठा ni_gpct *counter;
	अचिन्हित पूर्णांक i;

	अगर (num_counters == 0 || counters_per_chip == 0)
		वापस शून्य;

	counter_dev = kzalloc(माप(*counter_dev), GFP_KERNEL);
	अगर (!counter_dev)
		वापस शून्य;

	counter_dev->dev = dev;
	counter_dev->ग_लिखो = ग_लिखो;
	counter_dev->पढ़ो = पढ़ो;
	counter_dev->variant = variant;
	counter_dev->routing_tables = routing_tables;

	spin_lock_init(&counter_dev->regs_lock);

	counter_dev->num_counters = num_counters;
	counter_dev->num_chips = DIV_ROUND_UP(num_counters, counters_per_chip);

	counter_dev->counters = kसुस्मृति(num_counters, माप(*counter),
					GFP_KERNEL);
	counter_dev->regs = kसुस्मृति(counter_dev->num_chips,
				    माप(*counter_dev->regs), GFP_KERNEL);
	अगर (!counter_dev->regs || !counter_dev->counters) अणु
		kमुक्त(counter_dev->regs);
		kमुक्त(counter_dev->counters);
		kमुक्त(counter_dev);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < num_counters; ++i) अणु
		counter = &counter_dev->counters[i];
		counter->counter_dev = counter_dev;
		counter->chip_index = i / counters_per_chip;
		counter->counter_index = i % counters_per_chip;
		spin_lock_init(&counter->lock);
	पूर्ण

	वापस counter_dev;
पूर्ण
EXPORT_SYMBOL_GPL(ni_gpct_device_स्थिरruct);

व्योम ni_gpct_device_destroy(काष्ठा ni_gpct_device *counter_dev)
अणु
	अगर (!counter_dev)
		वापस;
	kमुक्त(counter_dev->regs);
	kमुक्त(counter_dev->counters);
	kमुक्त(counter_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ni_gpct_device_destroy);

अटल पूर्णांक __init ni_tio_init_module(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(ni_tio_init_module);

अटल व्योम __निकास ni_tio_cleanup_module(व्योम)
अणु
पूर्ण
module_निकास(ni_tio_cleanup_module);

MODULE_AUTHOR("Comedi <comedi@comedi.org>");
MODULE_DESCRIPTION("Comedi support for NI general-purpose counters");
MODULE_LICENSE("GPL");
