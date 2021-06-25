<शैली गुरु>
/*
 * drivers/media/radio/si4713-i2c.h
 *
 * Property and commands definitions क्रम Si4713 radio transmitter chip.
 *
 * Copyright (c) 2008 Instituto Nokia de Tecnologia - INdT
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@nokia.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#अगर_अघोषित SI4713_I2C_H
#घोषणा SI4713_I2C_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/platक्रमm_data/media/si4713.h>

#घोषणा SI4713_PRODUCT_NUMBER		0x0D

/* Command Timeouts */
#घोषणा DEFAULT_TIMEOUT			500
#घोषणा TIMEOUT_SET_PROPERTY		20
#घोषणा TIMEOUT_TX_TUNE_POWER		30000
#घोषणा TIMEOUT_TX_TUNE			110000
#घोषणा TIMEOUT_POWER_UP		200000

/*
 * Command and its arguments definitions
 */
#घोषणा SI4713_PWUP_CTSIEN		(1<<7)
#घोषणा SI4713_PWUP_GPO2OEN		(1<<6)
#घोषणा SI4713_PWUP_PATCH		(1<<5)
#घोषणा SI4713_PWUP_XOSCEN		(1<<4)
#घोषणा SI4713_PWUP_FUNC_TX		0x02
#घोषणा SI4713_PWUP_FUNC_PATCH		0x0F
#घोषणा SI4713_PWUP_OPMOD_ANALOG	0x50
#घोषणा SI4713_PWUP_OPMOD_DIGITAL	0x0F
#घोषणा SI4713_PWUP_NARGS		2
#घोषणा SI4713_PWUP_NRESP		1
#घोषणा SI4713_CMD_POWER_UP		0x01

#घोषणा SI4713_GETREV_NRESP		9
#घोषणा SI4713_CMD_GET_REV		0x10

#घोषणा SI4713_PWDN_NRESP		1
#घोषणा SI4713_CMD_POWER_DOWN		0x11

#घोषणा SI4713_SET_PROP_NARGS		5
#घोषणा SI4713_SET_PROP_NRESP		1
#घोषणा SI4713_CMD_SET_PROPERTY		0x12

#घोषणा SI4713_GET_PROP_NARGS		3
#घोषणा SI4713_GET_PROP_NRESP		4
#घोषणा SI4713_CMD_GET_PROPERTY		0x13

#घोषणा SI4713_GET_STATUS_NRESP		1
#घोषणा SI4713_CMD_GET_INT_STATUS	0x14

#घोषणा SI4713_CMD_PATCH_ARGS		0x15
#घोषणा SI4713_CMD_PATCH_DATA		0x16

#घोषणा SI4713_MAX_FREQ			10800
#घोषणा SI4713_MIN_FREQ			7600
#घोषणा SI4713_TXFREQ_NARGS		3
#घोषणा SI4713_TXFREQ_NRESP		1
#घोषणा SI4713_CMD_TX_TUNE_FREQ		0x30

#घोषणा SI4713_MAX_POWER		120
#घोषणा SI4713_MIN_POWER		88
#घोषणा SI4713_MAX_ANTCAP		191
#घोषणा SI4713_MIN_ANTCAP		0
#घोषणा SI4713_TXPWR_NARGS		4
#घोषणा SI4713_TXPWR_NRESP		1
#घोषणा SI4713_CMD_TX_TUNE_POWER	0x31

#घोषणा SI4713_TXMEA_NARGS		4
#घोषणा SI4713_TXMEA_NRESP		1
#घोषणा SI4713_CMD_TX_TUNE_MEASURE	0x32

#घोषणा SI4713_INTACK_MASK		0x01
#घोषणा SI4713_TXSTATUS_NARGS		1
#घोषणा SI4713_TXSTATUS_NRESP		8
#घोषणा SI4713_CMD_TX_TUNE_STATUS	0x33

#घोषणा SI4713_OVERMOD_BIT		(1 << 2)
#घोषणा SI4713_IALH_BIT			(1 << 1)
#घोषणा SI4713_IALL_BIT			(1 << 0)
#घोषणा SI4713_ASQSTATUS_NARGS		1
#घोषणा SI4713_ASQSTATUS_NRESP		5
#घोषणा SI4713_CMD_TX_ASQ_STATUS	0x34

#घोषणा SI4713_RDSBUFF_MODE_MASK	0x87
#घोषणा SI4713_RDSBUFF_NARGS		7
#घोषणा SI4713_RDSBUFF_NRESP		6
#घोषणा SI4713_CMD_TX_RDS_BUFF		0x35

#घोषणा SI4713_RDSPS_PSID_MASK		0x1F
#घोषणा SI4713_RDSPS_NARGS		5
#घोषणा SI4713_RDSPS_NRESP		1
#घोषणा SI4713_CMD_TX_RDS_PS		0x36

#घोषणा SI4713_CMD_GPO_CTL		0x80
#घोषणा SI4713_CMD_GPO_SET		0x81

/*
 * Bits from status response
 */
#घोषणा SI4713_CTS			(1<<7)
#घोषणा SI4713_ERR			(1<<6)
#घोषणा SI4713_RDS_INT			(1<<2)
#घोषणा SI4713_ASQ_INT			(1<<1)
#घोषणा SI4713_STC_INT			(1<<0)

/*
 * Property definitions
 */
#घोषणा SI4713_GPO_IEN			0x0001
#घोषणा SI4713_DIG_INPUT_FORMAT		0x0101
#घोषणा SI4713_DIG_INPUT_SAMPLE_RATE	0x0103
#घोषणा SI4713_REFCLK_FREQ		0x0201
#घोषणा SI4713_REFCLK_PRESCALE		0x0202
#घोषणा SI4713_TX_COMPONENT_ENABLE	0x2100
#घोषणा SI4713_TX_AUDIO_DEVIATION	0x2101
#घोषणा SI4713_TX_PILOT_DEVIATION	0x2102
#घोषणा SI4713_TX_RDS_DEVIATION		0x2103
#घोषणा SI4713_TX_LINE_INPUT_LEVEL	0x2104
#घोषणा SI4713_TX_LINE_INPUT_MUTE	0x2105
#घोषणा SI4713_TX_PREEMPHASIS		0x2106
#घोषणा SI4713_TX_PILOT_FREQUENCY	0x2107
#घोषणा SI4713_TX_ACOMP_ENABLE		0x2200
#घोषणा SI4713_TX_ACOMP_THRESHOLD	0x2201
#घोषणा SI4713_TX_ACOMP_ATTACK_TIME	0x2202
#घोषणा SI4713_TX_ACOMP_RELEASE_TIME	0x2203
#घोषणा SI4713_TX_ACOMP_GAIN		0x2204
#घोषणा SI4713_TX_LIMITER_RELEASE_TIME	0x2205
#घोषणा SI4713_TX_ASQ_INTERRUPT_SOURCE	0x2300
#घोषणा SI4713_TX_ASQ_LEVEL_LOW		0x2301
#घोषणा SI4713_TX_ASQ_DURATION_LOW	0x2302
#घोषणा SI4713_TX_ASQ_LEVEL_HIGH	0x2303
#घोषणा SI4713_TX_ASQ_DURATION_HIGH	0x2304
#घोषणा SI4713_TX_RDS_INTERRUPT_SOURCE	0x2C00
#घोषणा SI4713_TX_RDS_PI		0x2C01
#घोषणा SI4713_TX_RDS_PS_MIX		0x2C02
#घोषणा SI4713_TX_RDS_PS_MISC		0x2C03
#घोषणा SI4713_TX_RDS_PS_REPEAT_COUNT	0x2C04
#घोषणा SI4713_TX_RDS_PS_MESSAGE_COUNT	0x2C05
#घोषणा SI4713_TX_RDS_PS_AF		0x2C06
#घोषणा SI4713_TX_RDS_FIFO_SIZE		0x2C07

#घोषणा PREEMPHASIS_USA			75
#घोषणा PREEMPHASIS_EU			50
#घोषणा PREEMPHASIS_DISABLED		0
#घोषणा FMPE_USA			0x00
#घोषणा FMPE_EU				0x01
#घोषणा FMPE_DISABLED			0x02

#घोषणा POWER_UP			0x01
#घोषणा POWER_DOWN			0x00

#घोषणा MAX_RDS_PTY			31
#घोषणा MAX_RDS_DEVIATION		90000

/*
 * PSNAME is known to be defined as 8 अक्षरacter sized (RDS Spec).
 * However, there is receivers which scroll PSNAME 8xN sized.
 */
#घोषणा MAX_RDS_PS_NAME			96

/*
 * MAX_RDS_RADIO_TEXT is known to be defined as 32 (2A group) or 64 (2B group)
 * अक्षरacter sized (RDS Spec).
 * However, there is receivers which scroll them as well.
 */
#घोषणा MAX_RDS_RADIO_TEXT		384

#घोषणा MAX_LIMITER_RELEASE_TIME	102390
#घोषणा MAX_LIMITER_DEVIATION		90000

#घोषणा MAX_PILOT_DEVIATION		90000
#घोषणा MAX_PILOT_FREQUENCY		19000

#घोषणा MAX_ACOMP_RELEASE_TIME		1000000
#घोषणा MAX_ACOMP_ATTACK_TIME		5000
#घोषणा MAX_ACOMP_THRESHOLD		0
#घोषणा MIN_ACOMP_THRESHOLD		(-40)
#घोषणा MAX_ACOMP_GAIN			20

/*
 * si4713_device - निजी data
 */
काष्ठा si4713_device अणु
	/* v4l2_subdev and i2c reference (v4l2_subdev priv data) */
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	/* निजी data काष्ठाures */
	काष्ठा अणु /* si4713 control cluster */
		/* This is one big cluster since the mute control
		 * घातers off the device and after unmuting again all
		 * controls need to be set at once. The only way of करोing
		 * that is by making it one big cluster. */
		काष्ठा v4l2_ctrl *mute;
		काष्ठा v4l2_ctrl *rds_ps_name;
		काष्ठा v4l2_ctrl *rds_radio_text;
		काष्ठा v4l2_ctrl *rds_pi;
		काष्ठा v4l2_ctrl *rds_deviation;
		काष्ठा v4l2_ctrl *rds_pty;
		काष्ठा v4l2_ctrl *rds_compressed;
		काष्ठा v4l2_ctrl *rds_art_head;
		काष्ठा v4l2_ctrl *rds_stereo;
		काष्ठा v4l2_ctrl *rds_ta;
		काष्ठा v4l2_ctrl *rds_tp;
		काष्ठा v4l2_ctrl *rds_ms;
		काष्ठा v4l2_ctrl *rds_dyn_pty;
		काष्ठा v4l2_ctrl *rds_alt_freqs_enable;
		काष्ठा v4l2_ctrl *rds_alt_freqs;
		काष्ठा v4l2_ctrl *compression_enabled;
		काष्ठा v4l2_ctrl *compression_threshold;
		काष्ठा v4l2_ctrl *compression_gain;
		काष्ठा v4l2_ctrl *compression_attack_समय;
		काष्ठा v4l2_ctrl *compression_release_समय;
		काष्ठा v4l2_ctrl *pilot_tone_enabled;
		काष्ठा v4l2_ctrl *pilot_tone_freq;
		काष्ठा v4l2_ctrl *pilot_tone_deviation;
		काष्ठा v4l2_ctrl *limiter_enabled;
		काष्ठा v4l2_ctrl *limiter_deviation;
		काष्ठा v4l2_ctrl *limiter_release_समय;
		काष्ठा v4l2_ctrl *tune_preemphasis;
		काष्ठा v4l2_ctrl *tune_pwr_level;
		काष्ठा v4l2_ctrl *tune_ant_cap;
	पूर्ण;
	काष्ठा completion work;
	काष्ठा regulator *vdd;
	काष्ठा regulator *vio;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा platक्रमm_device *pd;
	u32 घातer_state;
	u32 rds_enabled;
	u32 frequency;
	u32 preemphasis;
	u32 stereo;
	u32 tune_rnl;
पूर्ण;

काष्ठा radio_si4713_platक्रमm_data अणु
	काष्ठा i2c_client *subdev;
पूर्ण;
#पूर्ण_अगर /* अगरndef SI4713_I2C_H */
