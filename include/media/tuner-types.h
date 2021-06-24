<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * descriptions क्रम simple tuners.
 */

#अगर_अघोषित __TUNER_TYPES_H__
#घोषणा __TUNER_TYPES_H__

/**
 * क्रमागत param_type - type of the tuner pameters
 *
 * @TUNER_PARAM_TYPE_RADIO:	Tuner params are क्रम FM and/or AM radio
 * @TUNER_PARAM_TYPE_PAL:	Tuner params are क्रम PAL color TV standard
 * @TUNER_PARAM_TYPE_SECAM:	Tuner params are क्रम SECAM color TV standard
 * @TUNER_PARAM_TYPE_NTSC:	Tuner params are क्रम NTSC color TV standard
 * @TUNER_PARAM_TYPE_DIGITAL:	Tuner params are क्रम digital TV
 */
क्रमागत param_type अणु
	TUNER_PARAM_TYPE_RADIO,
	TUNER_PARAM_TYPE_PAL,
	TUNER_PARAM_TYPE_SECAM,
	TUNER_PARAM_TYPE_NTSC,
	TUNER_PARAM_TYPE_DIGITAL,
पूर्ण;

/**
 * काष्ठा tuner_range - define the frequencies supported by the tuner
 *
 * @limit:		Max frequency supported by that range, in 62.5 kHz
 *			(TV) or 62.5 Hz (Radio), as defined by
 *			V4L2_TUNER_CAP_LOW.
 * @config:		Value of the band चयन byte (BB) to setup this mode.
 * @cb:			Value of the CB byte to setup this mode.
 *
 * Please notice that digital tuners like xc3028/xc4000/xc5000 करोn't use
 * those ranges, as they're defined inside the driver. This is used by
 * analog tuners that are compatible with the "Philips way" to setup the
 * tuners. On those devices, the tuner set is करोne via 4 bytes:
 *
 *	#) भागider byte1 (DB1)
 *	#) भागider byte 2 (DB2)
 *	#) Control byte (CB)
 *	#) band चयन byte (BB)
 *
 * Some tuners also have an additional optional Auxiliary byte (AB).
 */
काष्ठा tuner_range अणु
	अचिन्हित लघु limit;
	अचिन्हित अक्षर config;
	अचिन्हित अक्षर cb;
पूर्ण;

/**
 * काष्ठा tuner_params - Parameters to be used to setup the tuner. Those
 *			 are used by drivers/media/tuners/tuner-types.c in
 *			 order to specअगरy the tuner properties. Most of
 *			 the parameters are क्रम tuners based on tda9887 IF-PLL
 *			 multi-standard analog TV/Radio demodulator, with is
 *			 very common on legacy analog tuners.
 *
 * @type:			Type of the tuner parameters, as defined at
 *				क्रमागत param_type. If the tuner supports multiple
 *				standards, an array should be used, with one
 *				row per dअगरferent standard.
 * @cb_first_अगर_lower_freq:	Many Philips-based tuners have a comment in
 *				their datasheet like
 *				"For channel selection involving band
 *				चयनing, and to ensure smooth tuning to the
 *				desired channel without causing unnecessary
 *				अक्षरge pump action, it is recommended to
 *				consider the dअगरference between wanted channel
 *				frequency and the current channel frequency.
 *				Unnecessary अक्षरge pump action will result
 *				in very low tuning voltage which may drive the
 *				oscillator to extreme conditions".
 *				Set cb_first_अगर_lower_freq to 1, अगर this check
 *				is required क्रम this tuner. I tested this क्रम
 *				PAL by first setting the TV frequency to
 *				203 MHz and then चयनing to 96.6 MHz FM
 *				radio. The result was अटल unless the
 *				control byte was sent first.
 * @has_tda9887:		Set to 1 अगर this tuner uses a tda9887
 * @port1_fm_high_sensitivity:	Many Philips tuners use tda9887 PORT1 to select
 *				the FM radio sensitivity. If this setting is 1,
 *				then set PORT1 to 1 to get proper FM reception.
 * @port2_fm_high_sensitivity:	Some Philips tuners use tda9887 PORT2 to select
 *				the FM radio sensitivity. If this setting is 1,
 *				then set PORT2 to 1 to get proper FM reception.
 * @fm_gain_normal:		Some Philips tuners use tda9887 cGainNormal to
 *				select the FM radio sensitivity. If this
 *				setting is 1, e रेजिस्टर will use cGainNormal
 *				instead of cGainLow.
 * @पूर्णांकercarrier_mode:		Most tuners with a tda9887 use QSS mode.
 *				Some (cheaper) tuners use Intercarrier mode.
 *				If this setting is 1, then the tuner needs to
 *				be set to पूर्णांकercarrier mode.
 * @port1_active:		This setting sets the शेष value क्रम PORT1.
 *				0 means inactive, 1 means active. Note: the
 *				actual bit value written to the tda9887 is
 *				inverted. So a 0 here means a 1 in the B6 bit.
 * @port2_active:		This setting sets the शेष value क्रम PORT2.
 *				0 means inactive, 1 means active. Note: the
 *				actual bit value written to the tda9887 is
 *				inverted. So a 0 here means a 1 in the B7 bit.
 * @port1_invert_क्रम_secam_lc:	Someबार PORT1 is inverted when the SECAM-L'
 *				standard is selected. Set this bit to 1 अगर this
 *				is needed.
 * @port2_invert_क्रम_secam_lc:	Someबार PORT2 is inverted when the SECAM-L'
 *				standard is selected. Set this bit to 1 अगर this
 *				is needed.
 * @port1_set_क्रम_fm_mono:	Some cards require PORT1 to be 1 क्रम mono Radio
 *				FM and 0 क्रम stereo.
 * @शेष_pll_gating_18:	Select 18% (or according to datasheet 0%)
 *				L standard PLL gating, vs the driver शेष
 *				of 36%.
 * @radio_अगर:			IF to use in radio mode.  Tuners with a
 *				separate radio IF filter seem to use 10.7,
 *				जबतक those without use 33.3 क्रम PAL/SECAM
 *				tuners and 41.3 क्रम NTSC tuners.
 *				0 = 10.7, 1 = 33.3, 2 = 41.3
 * @शेष_top_low:		Default tda9887 TOP value in dB क्रम the low
 *				band. Default is 0. Range: -16:+15
 * @शेष_top_mid:		Default tda9887 TOP value in dB क्रम the mid
 *				band. Default is 0. Range: -16:+15
 * @शेष_top_high:		Default tda9887 TOP value in dB क्रम the high
 *				band. Default is 0. Range: -16:+15
 * @शेष_top_secam_low:	Default tda9887 TOP value in dB क्रम SECAM-L/L'
 *				क्रम the low band. Default is 0. Several tuners
 *				require a dअगरferent TOP value क्रम the
 *				SECAM-L/L' standards. Range: -16:+15
 * @शेष_top_secam_mid:	Default tda9887 TOP value in dB क्रम SECAM-L/L'
 *				क्रम the mid band. Default is 0. Several tuners
 *				require a dअगरferent TOP value क्रम the
 *				SECAM-L/L' standards. Range: -16:+15
 * @शेष_top_secam_high:	Default tda9887 TOP value in dB क्रम SECAM-L/L'
 *				क्रम the high band. Default is 0. Several tuners
 *				require a dअगरferent TOP value क्रम the
 *				SECAM-L/L' standards. Range: -16:+15
 * @अगरfreq:			Intermediate frequency (IF) used by the tuner
 *				on digital mode.
 * @count:			Size of the ranges array.
 * @ranges:			Array with the frequency ranges supported by
 *				the tuner.
 */
काष्ठा tuner_params अणु
	क्रमागत param_type type;

	अचिन्हित पूर्णांक cb_first_अगर_lower_freq:1;
	अचिन्हित पूर्णांक has_tda9887:1;
	अचिन्हित पूर्णांक port1_fm_high_sensitivity:1;
	अचिन्हित पूर्णांक port2_fm_high_sensitivity:1;
	अचिन्हित पूर्णांक fm_gain_normal:1;
	अचिन्हित पूर्णांक पूर्णांकercarrier_mode:1;
	अचिन्हित पूर्णांक port1_active:1;
	अचिन्हित पूर्णांक port2_active:1;
	अचिन्हित पूर्णांक port1_invert_क्रम_secam_lc:1;
	अचिन्हित पूर्णांक port2_invert_क्रम_secam_lc:1;
	अचिन्हित पूर्णांक port1_set_क्रम_fm_mono:1;
	अचिन्हित पूर्णांक शेष_pll_gating_18:1;
	अचिन्हित पूर्णांक radio_अगर:2;
	चिन्हित पूर्णांक शेष_top_low:5;
	चिन्हित पूर्णांक शेष_top_mid:5;
	चिन्हित पूर्णांक शेष_top_high:5;
	चिन्हित पूर्णांक शेष_top_secam_low:5;
	चिन्हित पूर्णांक शेष_top_secam_mid:5;
	चिन्हित पूर्णांक शेष_top_secam_high:5;

	u16 अगरfreq;

	अचिन्हित पूर्णांक count;
	काष्ठा tuner_range *ranges;
पूर्ण;

/**
 * काष्ठा tunertype - describes the known tuners.
 *
 * @name:	string with the tuner's name.
 * @count:	size of &काष्ठा tuner_params array.
 * @params:	poपूर्णांकer to &काष्ठा tuner_params array.
 *
 * @min:	minimal tuner frequency, in 62.5 kHz step.
 *		should be multiplied to 16 to convert to MHz.
 * @max:	minimal tuner frequency, in 62.5 kHz step.
 *		Should be multiplied to 16 to convert to MHz.
 * @stepsize:	frequency step, in Hz.
 * @initdata:	optional byte sequence to initialize the tuner.
 * @sleepdata:	optional byte sequence to घातer करोwn the tuner.
 */
काष्ठा tunertype अणु
	अक्षर *name;
	अचिन्हित पूर्णांक count;
	काष्ठा tuner_params *params;

	u16 min;
	u16 max;
	u32 stepsize;

	u8 *initdata;
	u8 *sleepdata;
पूर्ण;

बाह्य काष्ठा tunertype tuners[];
बाह्य अचिन्हित स्थिर पूर्णांक tuner_count;

#पूर्ण_अगर
