<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DIBX000_COMMON_H
#घोषणा DIBX000_COMMON_H

क्रमागत dibx000_i2c_पूर्णांकerface अणु
	DIBX000_I2C_INTERFACE_TUNER = 0,
	DIBX000_I2C_INTERFACE_GPIO_1_2 = 1,
	DIBX000_I2C_INTERFACE_GPIO_3_4 = 2,
	DIBX000_I2C_INTERFACE_GPIO_6_7 = 3
पूर्ण;

काष्ठा dibx000_i2c_master अणु
#घोषणा DIB3000MC 1
#घोषणा DIB7000   2
#घोषणा DIB7000P  11
#घोषणा DIB7000MC 12
#घोषणा DIB8000   13
	u16 device_rev;

	क्रमागत dibx000_i2c_पूर्णांकerface selected_पूर्णांकerface;

/*	काष्ठा i2c_adapter  tuner_i2c_adap; */
	काष्ठा i2c_adapter gated_tuner_i2c_adap;
	काष्ठा i2c_adapter master_i2c_adap_gpio12;
	काष्ठा i2c_adapter master_i2c_adap_gpio34;
	काष्ठा i2c_adapter master_i2c_adap_gpio67;

	काष्ठा i2c_adapter *i2c_adap;
	u8 i2c_addr;

	u16 base_reg;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[34];
	u8 i2c_ग_लिखो_buffer[8];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
पूर्ण;

बाह्य पूर्णांक dibx000_init_i2c_master(काष्ठा dibx000_i2c_master *mst,
					u16 device_rev, काष्ठा i2c_adapter *i2c_adap,
					u8 i2c_addr);
बाह्य काष्ठा i2c_adapter *dibx000_get_i2c_adapter(काष्ठा dibx000_i2c_master
							*mst,
							क्रमागत dibx000_i2c_पूर्णांकerface
							पूर्णांकf, पूर्णांक gating);
बाह्य व्योम dibx000_निकास_i2c_master(काष्ठा dibx000_i2c_master *mst);
बाह्य व्योम dibx000_reset_i2c_master(काष्ठा dibx000_i2c_master *mst);
बाह्य पूर्णांक dibx000_i2c_set_speed(काष्ठा i2c_adapter *i2c_adap, u16 speed);

#घोषणा BAND_LBAND 0x01
#घोषणा BAND_UHF   0x02
#घोषणा BAND_VHF   0x04
#घोषणा BAND_SBAND 0x08
#घोषणा BAND_FM	   0x10
#घोषणा BAND_CBAND 0x20

#घोषणा BAND_OF_FREQUENCY(freq_kHz) ((freq_kHz) <= 170000 ? BAND_CBAND : \
									(freq_kHz) <= 115000 ? BAND_FM : \
									(freq_kHz) <= 250000 ? BAND_VHF : \
									(freq_kHz) <= 863000 ? BAND_UHF : \
									(freq_kHz) <= 2000000 ? BAND_LBAND : BAND_SBAND )

काष्ठा dibx000_agc_config अणु
	/* defines the capabilities of this AGC-setting - using the BAND_-defines */
	u8 band_caps;

	u16 setup;

	u16 inv_gain;
	u16 समय_stabiliz;

	u8 alpha_level;
	u16 thlock;

	u8 wbd_inv;
	u16 wbd_ref;
	u8 wbd_sel;
	u8 wbd_alpha;

	u16 agc1_max;
	u16 agc1_min;
	u16 agc2_max;
	u16 agc2_min;

	u8 agc1_pt1;
	u8 agc1_pt2;
	u8 agc1_pt3;

	u8 agc1_slope1;
	u8 agc1_slope2;

	u8 agc2_pt1;
	u8 agc2_pt2;

	u8 agc2_slope1;
	u8 agc2_slope2;

	u8 alpha_mant;
	u8 alpha_exp;

	u8 beta_mant;
	u8 beta_exp;

	u8 perक्रमm_agc_softsplit;

	काष्ठा अणु
		u16 min;
		u16 max;
		u16 min_thres;
		u16 max_thres;
	पूर्ण split;
पूर्ण;

काष्ठा dibx000_bandwidth_config अणु
	u32 पूर्णांकernal;
	u32 sampling;

	u8 pll_preभाग;
	u8 pll_ratio;
	u8 pll_range;
	u8 pll_reset;
	u8 pll_bypass;

	u8 enable_refभाग;
	u8 bypclk_भाग;
	u8 IO_CLK_en_core;
	u8 ADClkSrc;
	u8 modulo;

	u16 sad_cfg;

	u32 अगरreq;
	u32 timf;

	u32 xtal_hz;
पूर्ण;

क्रमागत dibx000_adc_states अणु
	DIBX000_SLOW_ADC_ON = 0,
	DIBX000_SLOW_ADC_OFF,
	DIBX000_ADC_ON,
	DIBX000_ADC_OFF,
	DIBX000_VBG_ENABLE,
	DIBX000_VBG_DISABLE,
पूर्ण;

#घोषणा BANDWIDTH_TO_KHZ(v)	((v) / 1000)
#घोषणा BANDWIDTH_TO_HZ(v)	((v) * 1000)

/* Chip output mode. */
#घोषणा OUTMODE_HIGH_Z              0
#घोषणा OUTMODE_MPEG2_PAR_GATED_CLK 1
#घोषणा OUTMODE_MPEG2_PAR_CONT_CLK  2
#घोषणा OUTMODE_MPEG2_SERIAL        7
#घोषणा OUTMODE_DIVERSITY           4
#घोषणा OUTMODE_MPEG2_FIFO          5
#घोषणा OUTMODE_ANALOG_ADC          6

#घोषणा INPUT_MODE_OFF                0x11
#घोषणा INPUT_MODE_DIVERSITY          0x12
#घोषणा INPUT_MODE_MPEG               0x13

क्रमागत frontend_tune_state अणु
	CT_TUNER_START = 10,
	CT_TUNER_STEP_0,
	CT_TUNER_STEP_1,
	CT_TUNER_STEP_2,
	CT_TUNER_STEP_3,
	CT_TUNER_STEP_4,
	CT_TUNER_STEP_5,
	CT_TUNER_STEP_6,
	CT_TUNER_STEP_7,
	CT_TUNER_STOP,

	CT_AGC_START = 20,
	CT_AGC_STEP_0,
	CT_AGC_STEP_1,
	CT_AGC_STEP_2,
	CT_AGC_STEP_3,
	CT_AGC_STEP_4,
	CT_AGC_STOP,

	CT_DEMOD_START = 30,
	CT_DEMOD_STEP_1,
	CT_DEMOD_STEP_2,
	CT_DEMOD_STEP_3,
	CT_DEMOD_STEP_4,
	CT_DEMOD_STEP_5,
	CT_DEMOD_STEP_6,
	CT_DEMOD_STEP_7,
	CT_DEMOD_STEP_8,
	CT_DEMOD_STEP_9,
	CT_DEMOD_STEP_10,
	CT_DEMOD_STEP_11,
	CT_DEMOD_SEARCH_NEXT = 51,
	CT_DEMOD_STEP_LOCKED,
	CT_DEMOD_STOP,

	CT_DONE = 100,
	CT_SHUTDOWN,

पूर्ण;

काष्ठा dvb_frontend_parametersContext अणु
#घोषणा CHANNEL_STATUS_PARAMETERS_UNKNOWN   0x01
#घोषणा CHANNEL_STATUS_PARAMETERS_SET       0x02
	u8 status;
	u32 tune_समय_estimation[2];
	s32 tps_available;
	u16 tps[9];
पूर्ण;

#घोषणा FE_STATUS_TUNE_FAILED          0
#घोषणा FE_STATUS_TUNE_TIMED_OUT      -1
#घोषणा FE_STATUS_TUNE_TIME_TOO_SHORT -2
#घोषणा FE_STATUS_TUNE_PENDING        -3
#घोषणा FE_STATUS_STD_SUCCESS         -4
#घोषणा FE_STATUS_FFT_SUCCESS         -5
#घोषणा FE_STATUS_DEMOD_SUCCESS       -6
#घोषणा FE_STATUS_LOCKED              -7
#घोषणा FE_STATUS_DATA_LOCKED         -8

#घोषणा FE_CALLBACK_TIME_NEVER 0xffffffff

#घोषणा DATA_BUS_ACCESS_MODE_8BIT                 0x01
#घोषणा DATA_BUS_ACCESS_MODE_16BIT                0x02
#घोषणा DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT 0x10

काष्ठा dibGPIOFunction अणु
#घोषणा BOARD_GPIO_COMPONENT_BUS_ADAPTER 1
#घोषणा BOARD_GPIO_COMPONENT_DEMOD       2
	u8 component;

#घोषणा BOARD_GPIO_FUNCTION_BOARD_ON      1
#घोषणा BOARD_GPIO_FUNCTION_BOARD_OFF     2
#घोषणा BOARD_GPIO_FUNCTION_COMPONENT_ON  3
#घोषणा BOARD_GPIO_FUNCTION_COMPONENT_OFF 4
#घोषणा BOARD_GPIO_FUNCTION_SUBBAND_PWM   5
#घोषणा BOARD_GPIO_FUNCTION_SUBBAND_GPIO   6
	u8 function;

/* mask, direction and value are used specअगरy which GPIO to change GPIO0
 * is LSB and possible GPIO31 is MSB.  The same bit-position as in the
 * mask is used क्रम the direction and the value. Direction == 1 is OUT,
 * 0 == IN. For direction "OUT" value is either 1 or 0, क्रम direction IN
 * value has no meaning.
 *
 * In हाल of BOARD_GPIO_FUNCTION_PWM mask is giving the GPIO to be
 * used to करो the PWM. Direction gives the PWModulator to be used.
 * Value gives the PWM value in device-dependent scale.
 */
	u32 mask;
	u32 direction;
	u32 value;
पूर्ण;

#घोषणा MAX_NB_SUBBANDS   8
काष्ठा dibSubbandSelection अणु
	u8  size; /* Actual number of subbands. */
	काष्ठा अणु
		u16 f_mhz;
		काष्ठा dibGPIOFunction gpio;
	पूर्ण subband[MAX_NB_SUBBANDS];
पूर्ण;

#घोषणा DEMOD_TIMF_SET    0x00
#घोषणा DEMOD_TIMF_GET    0x01
#घोषणा DEMOD_TIMF_UPDATE 0x02

#घोषणा MPEG_ON_DIBTX		1
#घोषणा DIV_ON_DIBTX		2
#घोषणा ADC_ON_DIBTX		3
#घोषणा DEMOUT_ON_HOSTBUS	4
#घोषणा DIBTX_ON_HOSTBUS	5
#घोषणा MPEG_ON_HOSTBUS		6

#पूर्ण_अगर
