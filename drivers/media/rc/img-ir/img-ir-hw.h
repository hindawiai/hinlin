<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ImgTec IR Hardware Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 */

#अगर_अघोषित _IMG_IR_HW_H_
#घोषणा _IMG_IR_HW_H_

#समावेश <linux/kernel.h>
#समावेश <media/rc-core.h>

/* स्थिरants */

#घोषणा IMG_IR_CODETYPE_PULSELEN	0x0	/* Sony */
#घोषणा IMG_IR_CODETYPE_PULSEDIST	0x1	/* NEC, Toshiba, Micom, Sharp */
#घोषणा IMG_IR_CODETYPE_BIPHASE		0x2	/* RC-5/6 */
#घोषणा IMG_IR_CODETYPE_2BITPULSEPOS	0x3	/* RC-MM */


/* Timing inक्रमmation */

/**
 * काष्ठा img_ir_control - Decoder control settings
 * @decoden:	Primary decoder enable
 * @code_type:	Decode type (see IMG_IR_CODETYPE_*)
 * @hdrtog:	Detect header toggle symbol after leader symbol
 * @ldrdec:	Don't discard leader अगर maximum width reached
 * @decodinpol:	Decoder input polarity (1=active high)
 * @bitorien:	Bit orientation (1=MSB first)
 * @d1validsel:	Decoder 2 takes over अगर it detects valid data
 * @bitinv:	Bit inversion चयन (1=करोn't invert)
 * @decodend2:	Secondary decoder enable (no leader symbol)
 * @bitoriend2:	Bit orientation (1=MSB first)
 * @bitinvd2:	Secondary decoder bit inversion चयन (1=करोn't invert)
 */
काष्ठा img_ir_control अणु
	अचिन्हित decoden:1;
	अचिन्हित code_type:2;
	अचिन्हित hdrtog:1;
	अचिन्हित ldrdec:1;
	अचिन्हित decodinpol:1;
	अचिन्हित bitorien:1;
	अचिन्हित d1validsel:1;
	अचिन्हित bitinv:1;
	अचिन्हित decodend2:1;
	अचिन्हित bitoriend2:1;
	अचिन्हित bitinvd2:1;
पूर्ण;

/**
 * काष्ठा img_ir_timing_range - range of timing values
 * @min:	Minimum timing value
 * @max:	Maximum timing value (अगर < @min, this will be set to @min during
 *		preprocessing step, so it is normally not explicitly initialised
 *		and is taken care of by the tolerance)
 */
काष्ठा img_ir_timing_range अणु
	u16 min;
	u16 max;
पूर्ण;

/**
 * काष्ठा img_ir_symbol_timing - timing data क्रम a symbol
 * @pulse:	Timing range क्रम the length of the pulse in this symbol
 * @space:	Timing range क्रम the length of the space in this symbol
 */
काष्ठा img_ir_symbol_timing अणु
	काष्ठा img_ir_timing_range pulse;
	काष्ठा img_ir_timing_range space;
पूर्ण;

/**
 * काष्ठा img_ir_मुक्त_timing - timing data क्रम मुक्त समय symbol
 * @minlen:	Minimum number of bits of data
 * @maxlen:	Maximum number of bits of data
 * @ft_min:	Minimum मुक्त समय after message
 */
काष्ठा img_ir_मुक्त_timing अणु
	/* measured in bits */
	u8 minlen;
	u8 maxlen;
	u16 ft_min;
पूर्ण;

/**
 * काष्ठा img_ir_timings - Timing values.
 * @ldr:	Leader symbol timing data
 * @s00:	Zero symbol timing data क्रम primary decoder
 * @s01:	One symbol timing data क्रम primary decoder
 * @s10:	Zero symbol timing data क्रम secondary (no leader symbol) decoder
 * @s11:	One symbol timing data क्रम secondary (no leader symbol) decoder
 * @ft:		Free समय symbol timing data
 */
काष्ठा img_ir_timings अणु
	काष्ठा img_ir_symbol_timing ldr, s00, s01, s10, s11;
	काष्ठा img_ir_मुक्त_timing ft;
पूर्ण;

/**
 * काष्ठा img_ir_filter - Filter IR events.
 * @data:	Data to match.
 * @mask:	Mask of bits to compare.
 * @minlen:	Additional minimum number of bits.
 * @maxlen:	Additional maximum number of bits.
 */
काष्ठा img_ir_filter अणु
	u64 data;
	u64 mask;
	u8 minlen;
	u8 maxlen;
पूर्ण;

/**
 * काष्ठा img_ir_timing_regvals - Calculated timing रेजिस्टर values.
 * @ldr:	Leader symbol timing रेजिस्टर value
 * @s00:	Zero symbol timing रेजिस्टर value क्रम primary decoder
 * @s01:	One symbol timing रेजिस्टर value क्रम primary decoder
 * @s10:	Zero symbol timing रेजिस्टर value क्रम secondary decoder
 * @s11:	One symbol timing रेजिस्टर value क्रम secondary decoder
 * @ft:		Free समय symbol timing रेजिस्टर value
 */
काष्ठा img_ir_timing_regvals अणु
	u32 ldr, s00, s01, s10, s11, ft;
पूर्ण;

#घोषणा IMG_IR_SCANCODE		0	/* new scancode */
#घोषणा IMG_IR_REPEATCODE	1	/* repeat the previous code */

/**
 * काष्ठा img_ir_scancode_req - Scancode request data.
 * @protocol:	Protocol code of received message (शेषs to
 *		RC_PROTO_UNKNOWN).
 * @scancode:	Scan code of received message (must be written by
 *		handler अगर IMG_IR_SCANCODE is वापसed).
 * @toggle:	Toggle bit (शेषs to 0).
 */
काष्ठा img_ir_scancode_req अणु
	क्रमागत rc_proto protocol;
	u32 scancode;
	u8 toggle;
पूर्ण;

/**
 * काष्ठा img_ir_decoder - Decoder settings क्रम an IR protocol.
 * @type:	Protocol types biपंचांगap.
 * @tolerance:	Timing tolerance as a percentage (शेष 10%).
 * @unit:	Unit of timings in nanoseconds (शेष 1 us).
 * @timings:	Primary timings
 * @rtimings:	Additional override timings जबतक रुकोing क्रम repeats.
 * @repeat:	Maximum repeat पूर्णांकerval (always in milliseconds).
 * @control:	Control flags.
 *
 * @scancode:	Poपूर्णांकer to function to convert the IR data पूर्णांकo a scancode (it
 *		must be safe to execute in पूर्णांकerrupt context).
 *		Returns IMG_IR_SCANCODE to emit new scancode.
 *		Returns IMG_IR_REPEATCODE to repeat previous code.
 *		Returns -त्रुटि_सं (e.g. -EINVAL) on error.
 * @filter:	Poपूर्णांकer to function to convert scancode filter to raw hardware
 *		filter. The minlen and maxlen fields will have been initialised
 *		to the maximum range.
 */
काष्ठा img_ir_decoder अणु
	/* core description */
	u64				type;
	अचिन्हित पूर्णांक			tolerance;
	अचिन्हित पूर्णांक			unit;
	काष्ठा img_ir_timings		timings;
	काष्ठा img_ir_timings		rtimings;
	अचिन्हित पूर्णांक			repeat;
	काष्ठा img_ir_control		control;

	/* scancode logic */
	पूर्णांक (*scancode)(पूर्णांक len, u64 raw, u64 enabled_protocols,
			काष्ठा img_ir_scancode_req *request);
	पूर्णांक (*filter)(स्थिर काष्ठा rc_scancode_filter *in,
		      काष्ठा img_ir_filter *out, u64 protocols);
पूर्ण;

बाह्य काष्ठा img_ir_decoder img_ir_nec;
बाह्य काष्ठा img_ir_decoder img_ir_jvc;
बाह्य काष्ठा img_ir_decoder img_ir_sony;
बाह्य काष्ठा img_ir_decoder img_ir_sharp;
बाह्य काष्ठा img_ir_decoder img_ir_sanyo;
बाह्य काष्ठा img_ir_decoder img_ir_rc5;
बाह्य काष्ठा img_ir_decoder img_ir_rc6;

/**
 * काष्ठा img_ir_reg_timings - Reg values क्रम decoder timings at घड़ी rate.
 * @ctrl:	Processed control रेजिस्टर value.
 * @timings:	Processed primary timings.
 * @rtimings:	Processed repeat timings.
 */
काष्ठा img_ir_reg_timings अणु
	u32				ctrl;
	काष्ठा img_ir_timing_regvals	timings;
	काष्ठा img_ir_timing_regvals	rtimings;
पूर्ण;

काष्ठा img_ir_priv;

#अगर_घोषित CONFIG_IR_IMG_HW

क्रमागत img_ir_mode अणु
	IMG_IR_M_NORMAL,
	IMG_IR_M_REPEATING,
#अगर_घोषित CONFIG_PM_SLEEP
	IMG_IR_M_WAKE,
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा img_ir_priv_hw - Private driver data क्रम hardware decoder.
 * @ct_quirks:		Quirk bits क्रम each code type.
 * @rdev:		Remote control device
 * @clk_nb:		Notअगरier block क्रम घड़ी notअगरy events.
 * @end_समयr:		Timer until repeat समयout.
 * @suspend_समयr:	Timer to re-enable protocol.
 * @decoder:		Current decoder settings.
 * @enabled_protocols:	Currently enabled protocols.
 * @clk_hz:		Current core घड़ी rate in Hz.
 * @reg_timings:	Timing reg values क्रम decoder at घड़ी rate.
 * @flags:		IMG_IR_F_*.
 * @filters:		HW filters (derived from scancode filters).
 * @mode:		Current decode mode.
 * @stopping:		Indicates that decoder is being taken करोwn and समयrs
 *			should not be restarted.
 * @suspend_irqen:	Saved IRQ enable mask over suspend.
 * @quirk_suspend_irq:	Saved IRQ enable mask over quirk suspend समयr.
 */
काष्ठा img_ir_priv_hw अणु
	अचिन्हित पूर्णांक			ct_quirks[4];
	काष्ठा rc_dev			*rdev;
	काष्ठा notअगरier_block		clk_nb;
	काष्ठा समयr_list		end_समयr;
	काष्ठा समयr_list		suspend_समयr;
	स्थिर काष्ठा img_ir_decoder	*decoder;
	u64				enabled_protocols;
	अचिन्हित दीर्घ			clk_hz;
	काष्ठा img_ir_reg_timings	reg_timings;
	अचिन्हित पूर्णांक			flags;
	काष्ठा img_ir_filter		filters[RC_FILTER_MAX];

	क्रमागत img_ir_mode		mode;
	bool				stopping;
	u32				suspend_irqen;
	u32				quirk_suspend_irq;
पूर्ण;

अटल अंतरभूत bool img_ir_hw_enabled(काष्ठा img_ir_priv_hw *hw)
अणु
	वापस hw->rdev;
पूर्ण;

व्योम img_ir_isr_hw(काष्ठा img_ir_priv *priv, u32 irq_status);
व्योम img_ir_setup_hw(काष्ठा img_ir_priv *priv);
पूर्णांक img_ir_probe_hw(काष्ठा img_ir_priv *priv);
व्योम img_ir_हटाओ_hw(काष्ठा img_ir_priv *priv);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक img_ir_suspend(काष्ठा device *dev);
पूर्णांक img_ir_resume(काष्ठा device *dev);
#अन्यथा
#घोषणा img_ir_suspend शून्य
#घोषणा img_ir_resume शून्य
#पूर्ण_अगर

#अन्यथा

काष्ठा img_ir_priv_hw अणु
पूर्ण;

अटल अंतरभूत bool img_ir_hw_enabled(काष्ठा img_ir_priv_hw *hw)
अणु
	वापस false;
पूर्ण;
अटल अंतरभूत व्योम img_ir_isr_hw(काष्ठा img_ir_priv *priv, u32 irq_status)
अणु
पूर्ण
अटल अंतरभूत व्योम img_ir_setup_hw(काष्ठा img_ir_priv *priv)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक img_ir_probe_hw(काष्ठा img_ir_priv *priv)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम img_ir_हटाओ_hw(काष्ठा img_ir_priv *priv)
अणु
पूर्ण

#घोषणा img_ir_suspend शून्य
#घोषणा img_ir_resume शून्य

#पूर्ण_अगर /* CONFIG_IR_IMG_HW */

#पूर्ण_अगर /* _IMG_IR_HW_H_ */
