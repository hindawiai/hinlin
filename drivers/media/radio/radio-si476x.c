<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/radio/radio-si476x.c -- V4L2 driver क्रम SI476X chips
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/debugfs.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-device.h>

#समावेश <media/drv-पूर्णांकf/si476x.h>
#समावेश <linux/mfd/si476x-core.h>

#घोषणा FM_FREQ_RANGE_LOW   64000000
#घोषणा FM_FREQ_RANGE_HIGH 108000000

#घोषणा AM_FREQ_RANGE_LOW    520000
#घोषणा AM_FREQ_RANGE_HIGH 30000000

#घोषणा PWRLINEFLTR (1 << 8)

#घोषणा FREQ_MUL (10000000 / 625)

#घोषणा SI476X_PHDIV_STATUS_LINK_LOCKED(status) (0x80 & (status))

#घोषणा DRIVER_NAME "si476x-radio"
#घोषणा DRIVER_CARD "SI476x AM/FM Receiver"

क्रमागत si476x_freq_bands अणु
	SI476X_BAND_FM,
	SI476X_BAND_AM,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band si476x_bands[] = अणु
	[SI476X_BAND_FM] = अणु
		.type		= V4L2_TUNER_RADIO,
		.index		= SI476X_BAND_FM,
		.capability	= V4L2_TUNER_CAP_LOW
		| V4L2_TUNER_CAP_STEREO
		| V4L2_TUNER_CAP_RDS
		| V4L2_TUNER_CAP_RDS_BLOCK_IO
		| V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow	=  64 * FREQ_MUL,
		.rangehigh	= 108 * FREQ_MUL,
		.modulation	= V4L2_BAND_MODULATION_FM,
	पूर्ण,
	[SI476X_BAND_AM] = अणु
		.type		= V4L2_TUNER_RADIO,
		.index		= SI476X_BAND_AM,
		.capability	= V4L2_TUNER_CAP_LOW
		| V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow	= 0.52 * FREQ_MUL,
		.rangehigh	= 30 * FREQ_MUL,
		.modulation	= V4L2_BAND_MODULATION_AM,
	पूर्ण,
पूर्ण;

अटल अंतरभूत bool si476x_radio_freq_is_inside_of_the_band(u32 freq, पूर्णांक band)
अणु
	वापस freq >= si476x_bands[band].rangelow &&
		freq <= si476x_bands[band].rangehigh;
पूर्ण

अटल अंतरभूत bool si476x_radio_range_is_inside_of_the_band(u32 low, u32 high,
							    पूर्णांक band)
अणु
	वापस low  >= si476x_bands[band].rangelow &&
		high <= si476x_bands[band].rangehigh;
पूर्ण

अटल पूर्णांक si476x_radio_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल पूर्णांक si476x_radio_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl);

क्रमागत phase_भागersity_modes_idx अणु
	SI476X_IDX_PHDIV_DISABLED,
	SI476X_IDX_PHDIV_PRIMARY_COMBINING,
	SI476X_IDX_PHDIV_PRIMARY_ANTENNA,
	SI476X_IDX_PHDIV_SECONDARY_ANTENNA,
	SI476X_IDX_PHDIV_SECONDARY_COMBINING,
पूर्ण;

अटल स्थिर अक्षर * स्थिर phase_भागersity_modes[] = अणु
	[SI476X_IDX_PHDIV_DISABLED]		= "Disabled",
	[SI476X_IDX_PHDIV_PRIMARY_COMBINING]	= "Primary with Secondary",
	[SI476X_IDX_PHDIV_PRIMARY_ANTENNA]	= "Primary Antenna",
	[SI476X_IDX_PHDIV_SECONDARY_ANTENNA]	= "Secondary Antenna",
	[SI476X_IDX_PHDIV_SECONDARY_COMBINING]	= "Secondary with Primary",
पूर्ण;

अटल अंतरभूत क्रमागत phase_भागersity_modes_idx
si476x_phase_भागersity_mode_to_idx(क्रमागत si476x_phase_भागersity_mode mode)
अणु
	चयन (mode) अणु
	शेष:
		fallthrough;
	हाल SI476X_PHDIV_DISABLED:
		वापस SI476X_IDX_PHDIV_DISABLED;
	हाल SI476X_PHDIV_PRIMARY_COMBINING:
		वापस SI476X_IDX_PHDIV_PRIMARY_COMBINING;
	हाल SI476X_PHDIV_PRIMARY_ANTENNA:
		वापस SI476X_IDX_PHDIV_PRIMARY_ANTENNA;
	हाल SI476X_PHDIV_SECONDARY_ANTENNA:
		वापस SI476X_IDX_PHDIV_SECONDARY_ANTENNA;
	हाल SI476X_PHDIV_SECONDARY_COMBINING:
		वापस SI476X_IDX_PHDIV_SECONDARY_COMBINING;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत si476x_phase_भागersity_mode
si476x_phase_भागersity_idx_to_mode(क्रमागत phase_भागersity_modes_idx idx)
अणु
	अटल स्थिर पूर्णांक idx_to_value[] = अणु
		[SI476X_IDX_PHDIV_DISABLED]		= SI476X_PHDIV_DISABLED,
		[SI476X_IDX_PHDIV_PRIMARY_COMBINING]	= SI476X_PHDIV_PRIMARY_COMBINING,
		[SI476X_IDX_PHDIV_PRIMARY_ANTENNA]	= SI476X_PHDIV_PRIMARY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDARY_ANTENNA]	= SI476X_PHDIV_SECONDARY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDARY_COMBINING]	= SI476X_PHDIV_SECONDARY_COMBINING,
	पूर्ण;

	वापस idx_to_value[idx];
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops si476x_ctrl_ops = अणु
	.g_अस्थिर_ctrl	= si476x_radio_g_अस्थिर_ctrl,
	.s_ctrl			= si476x_radio_s_ctrl,
पूर्ण;


क्रमागत si476x_ctrl_idx अणु
	SI476X_IDX_RSSI_THRESHOLD,
	SI476X_IDX_SNR_THRESHOLD,
	SI476X_IDX_MAX_TUNE_ERROR,
	SI476X_IDX_HARMONICS_COUNT,
	SI476X_IDX_DIVERSITY_MODE,
	SI476X_IDX_INTERCHIP_LINK,
पूर्ण;
अटल काष्ठा v4l2_ctrl_config si476x_ctrls[] = अणु

	/*
	 * SI476X during its station seeking(or tuning) process uses several
	 * parameters to determine अगर "the station" is valid:
	 *
	 *	- Signal's SNR(in dBuV) must be lower than
	 *	#V4L2_CID_SI476X_SNR_THRESHOLD
	 *	- Signal's RSSI(in dBuV) must be greater than
	 *	#V4L2_CID_SI476X_RSSI_THRESHOLD
	 *	- Signal's frequency deviation(in units of 2ppm) must not be
	 *	more than #V4L2_CID_SI476X_MAX_TUNE_ERROR
	 */
	[SI476X_IDX_RSSI_THRESHOLD] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_RSSI_THRESHOLD,
		.name	= "Valid RSSI Threshold",
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.min	= -128,
		.max	= 127,
		.step	= 1,
	पूर्ण,
	[SI476X_IDX_SNR_THRESHOLD] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_SNR_THRESHOLD,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Valid SNR Threshold",
		.min	= -128,
		.max	= 127,
		.step	= 1,
	पूर्ण,
	[SI476X_IDX_MAX_TUNE_ERROR] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_MAX_TUNE_ERROR,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Max Tune Errors",
		.min	= 0,
		.max	= 126 * 2,
		.step	= 2,
	पूर्ण,

	/*
	 * #V4L2_CID_SI476X_HARMONICS_COUNT -- number of harmonics
	 * built-in घातer-line noise supression filter is to reject
	 * during AM-mode operation.
	 */
	[SI476X_IDX_HARMONICS_COUNT] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_HARMONICS_COUNT,
		.type	= V4L2_CTRL_TYPE_INTEGER,

		.name	= "Count of Harmonics to Reject",
		.min	= 0,
		.max	= 20,
		.step	= 1,
	पूर्ण,

	/*
	 * #V4L2_CID_SI476X_DIVERSITY_MODE -- configuration which
	 * two tuners working in भागersity mode are to work in.
	 *
	 *  - #SI476X_IDX_PHDIV_DISABLED भागersity mode disabled
	 *  - #SI476X_IDX_PHDIV_PRIMARY_COMBINING भागersity mode is
	 *  on, primary tuner's antenna is the मुख्य one.
	 *  - #SI476X_IDX_PHDIV_PRIMARY_ANTENNA भागersity mode is
	 *  off, primary tuner's antenna is the मुख्य one.
	 *  - #SI476X_IDX_PHDIV_SECONDARY_ANTENNA भागersity mode is
	 *  off, secondary tuner's antenna is the मुख्य one.
	 *  - #SI476X_IDX_PHDIV_SECONDARY_COMBINING भागersity mode is
	 *  on, secondary tuner's antenna is the मुख्य one.
	 */
	[SI476X_IDX_DIVERSITY_MODE] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_DIVERSITY_MODE,
		.type	= V4L2_CTRL_TYPE_MENU,
		.name	= "Phase Diversity Mode",
		.qmenu	= phase_भागersity_modes,
		.min	= 0,
		.max	= ARRAY_SIZE(phase_भागersity_modes) - 1,
	पूर्ण,

	/*
	 * #V4L2_CID_SI476X_INTERCHIP_LINK -- पूर्णांकer-chip link in
	 * भागersity mode indicator. Allows user to determine अगर two
	 * chips working in भागersity mode have established a link
	 * between each other and अगर the प्रणाली as a whole uses
	 * संकेतs from both antennas to receive FM radio.
	 */
	[SI476X_IDX_INTERCHIP_LINK] = अणु
		.ops	= &si476x_ctrl_ops,
		.id	= V4L2_CID_SI476X_INTERCHIP_LINK,
		.type	= V4L2_CTRL_TYPE_BOOLEAN,
		.flags  = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_VOLATILE,
		.name	= "Inter-Chip Link",
		.min	= 0,
		.max	= 1,
		.step	= 1,
	पूर्ण,
पूर्ण;

काष्ठा si476x_radio;

/**
 * काष्ठा si476x_radio_ops - vtable of tuner functions
 *
 * This table holds poपूर्णांकers to functions implementing particular
 * operations depending on the mode in which the tuner chip was
 * configured to start. If the function is not supported
 * corresponding element is set to #शून्य.
 *
 * @tune_freq: Tune chip to a specअगरic frequency
 * @seek_start: Star station seeking
 * @rsq_status: Get Received Signal Quality(RSQ) status
 * @rds_blckcnt: Get received RDS blocks count
 * @phase_भागersity: Change phase भागersity mode of the tuner
 * @phase_भाग_status: Get phase भागersity mode status
 * @acf_status: Get the status of Automatically Controlled
 * Features(ACF)
 * @agc_status: Get Automatic Gain Control(AGC) status
 */
काष्ठा si476x_radio_ops अणु
	पूर्णांक (*tune_freq)(काष्ठा si476x_core *, काष्ठा si476x_tune_freq_args *);
	पूर्णांक (*seek_start)(काष्ठा si476x_core *, bool, bool);
	पूर्णांक (*rsq_status)(काष्ठा si476x_core *, काष्ठा si476x_rsq_status_args *,
			  काष्ठा si476x_rsq_status_report *);
	पूर्णांक (*rds_blckcnt)(काष्ठा si476x_core *, bool,
			   काष्ठा si476x_rds_blockcount_report *);

	पूर्णांक (*phase_भागersity)(काष्ठा si476x_core *,
			       क्रमागत si476x_phase_भागersity_mode);
	पूर्णांक (*phase_भाग_status)(काष्ठा si476x_core *);
	पूर्णांक (*acf_status)(काष्ठा si476x_core *,
			  काष्ठा si476x_acf_status_report *);
	पूर्णांक (*agc_status)(काष्ठा si476x_core *,
			  काष्ठा si476x_agc_status_report *);
पूर्ण;

/**
 * काष्ठा si476x_radio - radio device
 *
 * @v4l2dev: Poपूर्णांकer to V4L2 device created by V4L2 subप्रणाली
 * @videodev: Poपूर्णांकer to video device created by V4L2 subप्रणाली
 * @ctrl_handler: V4L2 controls handler
 * @core: Poपूर्णांकer to underlying core device
 * @ops: Vtable of functions. See काष्ठा si476x_radio_ops क्रम details
 * @debugfs: poपूर्णांकer to &strucd dentry क्रम debugfs
 * @audmode: audio mode, as defined क्रम the rxsubchans field
 *	     at videodev2.h
 *
 * core काष्ठाure is the radio device is being used
 */
काष्ठा si476x_radio अणु
	काष्ठा v4l2_device v4l2dev;
	काष्ठा video_device videodev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा si476x_core  *core;
	/* This field should not be accesses unless core lock is held */
	स्थिर काष्ठा si476x_radio_ops *ops;

	काष्ठा dentry	*debugfs;
	u32 audmode;
पूर्ण;

अटल अंतरभूत काष्ठा si476x_radio *
v4l2_dev_to_radio(काष्ठा v4l2_device *d)
अणु
	वापस container_of(d, काष्ठा si476x_radio, v4l2dev);
पूर्ण

अटल अंतरभूत काष्ठा si476x_radio *
v4l2_ctrl_handler_to_radio(काष्ठा v4l2_ctrl_handler *d)
अणु
	वापस container_of(d, काष्ठा si476x_radio, ctrl_handler);
पूर्ण

/*
 * si476x_vidioc_querycap - query device capabilities
 */
अटल पूर्णांक si476x_radio_querycap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_capability *capability)
अणु
	काष्ठा si476x_radio *radio = video_drvdata(file);

	strscpy(capability->driver, radio->v4l2dev.name,
		माप(capability->driver));
	strscpy(capability->card,   DRIVER_CARD, माप(capability->card));
	snम_लिखो(capability->bus_info, माप(capability->bus_info),
		 "platform:%s", radio->v4l2dev.name);
	वापस 0;
पूर्ण

अटल पूर्णांक si476x_radio_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency_band *band)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	अगर (band->tuner != 0)
		वापस -EINVAL;

	चयन (radio->core->chip_id) अणु
		/* AM/FM tuners -- all bands are supported */
	हाल SI476X_CHIP_SI4761:
	हाल SI476X_CHIP_SI4764:
		अगर (band->index < ARRAY_SIZE(si476x_bands)) अणु
			*band = si476x_bands[band->index];
			err = 0;
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अवरोध;
		/* FM companion tuner chips -- only FM bands are
		 * supported */
	हाल SI476X_CHIP_SI4768:
		अगर (band->index == SI476X_BAND_FM) अणु
			*band = si476x_bands[band->index];
			err = 0;
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *tuner)
अणु
	पूर्णांक err;
	काष्ठा si476x_rsq_status_report report;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	काष्ठा si476x_rsq_status_args args = अणु
		.primary	= false,
		.rsqack		= false,
		.attune		= false,
		.cancel		= false,
		.stcack		= false,
	पूर्ण;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	tuner->type       = V4L2_TUNER_RADIO;
	tuner->capability = V4L2_TUNER_CAP_LOW /* Measure frequencies
						 * in multiples of
						 * 62.5 Hz */
		| V4L2_TUNER_CAP_STEREO
		| V4L2_TUNER_CAP_HWSEEK_BOUNDED
		| V4L2_TUNER_CAP_HWSEEK_WRAP
		| V4L2_TUNER_CAP_HWSEEK_PROG_LIM;

	si476x_core_lock(radio->core);

	अगर (si476x_core_is_a_secondary_tuner(radio->core)) अणु
		strscpy(tuner->name, "FM (secondary)", माप(tuner->name));
		tuner->rxsubchans = 0;
		tuner->rangelow = si476x_bands[SI476X_BAND_FM].rangelow;
	पूर्ण अन्यथा अगर (si476x_core_has_am(radio->core)) अणु
		अगर (si476x_core_is_a_primary_tuner(radio->core))
			strscpy(tuner->name, "AM/FM (primary)",
				माप(tuner->name));
		अन्यथा
			strscpy(tuner->name, "AM/FM", माप(tuner->name));

		tuner->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO
			| V4L2_TUNER_SUB_RDS;
		tuner->capability |= V4L2_TUNER_CAP_RDS
			| V4L2_TUNER_CAP_RDS_BLOCK_IO
			| V4L2_TUNER_CAP_FREQ_BANDS;

		tuner->rangelow = si476x_bands[SI476X_BAND_AM].rangelow;
	पूर्ण अन्यथा अणु
		strscpy(tuner->name, "FM", माप(tuner->name));
		tuner->rxsubchans = V4L2_TUNER_SUB_RDS;
		tuner->capability |= V4L2_TUNER_CAP_RDS
			| V4L2_TUNER_CAP_RDS_BLOCK_IO
			| V4L2_TUNER_CAP_FREQ_BANDS;
		tuner->rangelow = si476x_bands[SI476X_BAND_FM].rangelow;
	पूर्ण

	tuner->audmode = radio->audmode;

	tuner->afc = 1;
	tuner->rangehigh = si476x_bands[SI476X_BAND_FM].rangehigh;

	err = radio->ops->rsq_status(radio->core,
				     &args, &report);
	अगर (err < 0) अणु
		tuner->संकेत = 0;
	पूर्ण अन्यथा अणु
		/*
		 * tuner->संकेत value range: 0x0000 .. 0xFFFF,
		 * report.rssi: -128 .. 127
		 */
		tuner->संकेत = (report.rssi + 128) * 257;
	पूर्ण
	si476x_core_unlock(radio->core);

	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा si476x_radio *radio = video_drvdata(file);

	अगर (tuner->index != 0)
		वापस -EINVAL;

	अगर (tuner->audmode == V4L2_TUNER_MODE_MONO ||
	    tuner->audmode == V4L2_TUNER_MODE_STEREO)
		radio->audmode = tuner->audmode;
	अन्यथा
		radio->audmode = V4L2_TUNER_MODE_STEREO;

	वापस 0;
पूर्ण

अटल पूर्णांक si476x_radio_init_vtable(काष्ठा si476x_radio *radio,
				    क्रमागत si476x_func func)
अणु
	अटल स्थिर काष्ठा si476x_radio_ops fm_ops = अणु
		.tune_freq		= si476x_core_cmd_fm_tune_freq,
		.seek_start		= si476x_core_cmd_fm_seek_start,
		.rsq_status		= si476x_core_cmd_fm_rsq_status,
		.rds_blckcnt		= si476x_core_cmd_fm_rds_blockcount,
		.phase_भागersity	= si476x_core_cmd_fm_phase_भागersity,
		.phase_भाग_status	= si476x_core_cmd_fm_phase_भाग_status,
		.acf_status		= si476x_core_cmd_fm_acf_status,
		.agc_status		= si476x_core_cmd_agc_status,
	पूर्ण;

	अटल स्थिर काष्ठा si476x_radio_ops am_ops = अणु
		.tune_freq		= si476x_core_cmd_am_tune_freq,
		.seek_start		= si476x_core_cmd_am_seek_start,
		.rsq_status		= si476x_core_cmd_am_rsq_status,
		.rds_blckcnt		= शून्य,
		.phase_भागersity	= शून्य,
		.phase_भाग_status	= शून्य,
		.acf_status		= si476x_core_cmd_am_acf_status,
		.agc_status		= शून्य,
	पूर्ण;

	चयन (func) अणु
	हाल SI476X_FUNC_FM_RECEIVER:
		radio->ops = &fm_ops;
		वापस 0;

	हाल SI476X_FUNC_AM_RECEIVER:
		radio->ops = &am_ops;
		वापस 0;
	शेष:
		WARN(1, "Unexpected tuner function value\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si476x_radio_pretune(काष्ठा si476x_radio *radio,
				क्रमागत si476x_func func)
अणु
	पूर्णांक retval;

	काष्ठा si476x_tune_freq_args args = अणु
		.zअगरsr		= false,
		.hd		= false,
		.injside	= SI476X_INJSIDE_AUTO,
		.tunemode	= SI476X_TM_VALIDATED_NORMAL_TUNE,
		.smoothmetrics	= SI476X_SM_INITIALIZE_AUDIO,
		.antcap		= 0,
	पूर्ण;

	चयन (func) अणु
	हाल SI476X_FUNC_FM_RECEIVER:
		args.freq = v4l2_to_si476x(radio->core,
					   92 * FREQ_MUL);
		retval = radio->ops->tune_freq(radio->core, &args);
		अवरोध;
	हाल SI476X_FUNC_AM_RECEIVER:
		args.freq = v4l2_to_si476x(radio->core,
					   0.6 * FREQ_MUL);
		retval = radio->ops->tune_freq(radio->core, &args);
		अवरोध;
	शेष:
		WARN(1, "Unexpected tuner function value\n");
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण
अटल पूर्णांक si476x_radio_करो_post_घातerup_init(काष्ठा si476x_radio *radio,
					     क्रमागत si476x_func func)
अणु
	पूर्णांक err;

	/* regcache_mark_dirty(radio->core->regmap); */
	err = regcache_sync_region(radio->core->regmap,
				   SI476X_PROP_DIGITAL_IO_INPUT_SAMPLE_RATE,
				   SI476X_PROP_DIGITAL_IO_OUTPUT_FORMAT);
	अगर (err < 0)
		वापस err;

	err = regcache_sync_region(radio->core->regmap,
				   SI476X_PROP_AUDIO_DEEMPHASIS,
				   SI476X_PROP_AUDIO_PWR_LINE_FILTER);
	अगर (err < 0)
		वापस err;

	err = regcache_sync_region(radio->core->regmap,
				   SI476X_PROP_INT_CTL_ENABLE,
				   SI476X_PROP_INT_CTL_ENABLE);
	अगर (err < 0)
		वापस err;

	/*
	 * Is there any poपूर्णांक in restoring SNR and the like
	 * when चयनing between AM/FM?
	 */
	err = regcache_sync_region(radio->core->regmap,
				   SI476X_PROP_VALID_MAX_TUNE_ERROR,
				   SI476X_PROP_VALID_MAX_TUNE_ERROR);
	अगर (err < 0)
		वापस err;

	err = regcache_sync_region(radio->core->regmap,
				   SI476X_PROP_VALID_SNR_THRESHOLD,
				   SI476X_PROP_VALID_RSSI_THRESHOLD);
	अगर (err < 0)
		वापस err;

	अगर (func == SI476X_FUNC_FM_RECEIVER) अणु
		अगर (si476x_core_has_भागersity(radio->core)) अणु
			err = si476x_core_cmd_fm_phase_भागersity(radio->core,
								 radio->core->भागersity_mode);
			अगर (err < 0)
				वापस err;
		पूर्ण

		err = regcache_sync_region(radio->core->regmap,
					   SI476X_PROP_FM_RDS_INTERRUPT_SOURCE,
					   SI476X_PROP_FM_RDS_CONFIG);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस si476x_radio_init_vtable(radio, func);

पूर्ण

अटल पूर्णांक si476x_radio_change_func(काष्ठा si476x_radio *radio,
				    क्रमागत si476x_func func)
अणु
	पूर्णांक err;
	bool soft;
	/*
	 * Since घातer/up करोwn is a very समय consuming operation,
	 * try to aव्योम करोing it अगर the requested mode matches the one
	 * the tuner is in
	 */
	अगर (func == radio->core->घातer_up_parameters.func)
		वापस 0;

	soft = true;
	err = si476x_core_stop(radio->core, soft);
	अगर (err < 0) अणु
		/*
		 * OK, अगर the chip करोes not want to play nice let's
		 * try to reset it in more brutal way
		 */
		soft = false;
		err = si476x_core_stop(radio->core, soft);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/*
	  Set the desired radio tuner function
	 */
	radio->core->घातer_up_parameters.func = func;

	err = si476x_core_start(radio->core, soft);
	अगर (err < 0)
		वापस err;

	/*
	 * No need to करो the rest of manipulations क्रम the bootlader
	 * mode
	 */
	अगर (func != SI476X_FUNC_FM_RECEIVER &&
	    func != SI476X_FUNC_AM_RECEIVER)
		वापस err;

	वापस si476x_radio_करो_post_घातerup_init(radio, func);
पूर्ण

अटल पूर्णांक si476x_radio_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	अगर (f->tuner != 0 ||
	    f->type  != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	si476x_core_lock(radio->core);

	अगर (radio->ops->rsq_status) अणु
		काष्ठा si476x_rsq_status_report report;
		काष्ठा si476x_rsq_status_args   args = अणु
			.primary	= false,
			.rsqack		= false,
			.attune		= true,
			.cancel		= false,
			.stcack		= false,
		पूर्ण;

		err = radio->ops->rsq_status(radio->core, &args, &report);
		अगर (!err)
			f->frequency = si476x_to_v4l2(radio->core,
						      report.पढ़ोfreq);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	si476x_core_unlock(radio->core);

	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_s_frequency(काष्ठा file *file, व्योम *priv,
				    स्थिर काष्ठा v4l2_frequency *f)
अणु
	पूर्णांक err;
	u32 freq = f->frequency;
	काष्ठा si476x_tune_freq_args args;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	स्थिर u32 midrange = (si476x_bands[SI476X_BAND_AM].rangehigh +
			      si476x_bands[SI476X_BAND_FM].rangelow) / 2;
	स्थिर पूर्णांक band = (freq > midrange) ?
		SI476X_BAND_FM : SI476X_BAND_AM;
	स्थिर क्रमागत si476x_func func = (band == SI476X_BAND_AM) ?
		SI476X_FUNC_AM_RECEIVER : SI476X_FUNC_FM_RECEIVER;

	अगर (f->tuner != 0 ||
	    f->type  != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	si476x_core_lock(radio->core);

	freq = clamp(freq,
		     si476x_bands[band].rangelow,
		     si476x_bands[band].rangehigh);

	अगर (si476x_radio_freq_is_inside_of_the_band(freq,
						    SI476X_BAND_AM) &&
	    (!si476x_core_has_am(radio->core) ||
	     si476x_core_is_a_secondary_tuner(radio->core))) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = si476x_radio_change_func(radio, func);
	अगर (err < 0)
		जाओ unlock;

	args.zअगरsr		= false;
	args.hd			= false;
	args.injside		= SI476X_INJSIDE_AUTO;
	args.freq		= v4l2_to_si476x(radio->core, freq);
	args.tunemode		= SI476X_TM_VALIDATED_NORMAL_TUNE;
	args.smoothmetrics	= SI476X_SM_INITIALIZE_AUDIO;
	args.antcap		= 0;

	err = radio->ops->tune_freq(radio->core, &args);

unlock:
	si476x_core_unlock(radio->core);
	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
				       स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	पूर्णांक err;
	क्रमागत si476x_func func;
	u32 rangelow = seek->rangelow, rangehigh = seek->rangehigh;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EAGAIN;

	अगर (seek->tuner != 0 ||
	    seek->type  != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	si476x_core_lock(radio->core);

	अगर (!rangelow) अणु
		err = regmap_पढ़ो(radio->core->regmap,
				  SI476X_PROP_SEEK_BAND_BOTTOM,
				  &rangelow);
		अगर (err)
			जाओ unlock;
		rangelow = si476x_to_v4l2(radio->core, rangelow);
	पूर्ण
	अगर (!rangehigh) अणु
		err = regmap_पढ़ो(radio->core->regmap,
				  SI476X_PROP_SEEK_BAND_TOP,
				  &rangehigh);
		अगर (err)
			जाओ unlock;
		rangehigh = si476x_to_v4l2(radio->core, rangehigh);
	पूर्ण

	अगर (rangelow > rangehigh) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (si476x_radio_range_is_inside_of_the_band(rangelow, rangehigh,
						     SI476X_BAND_FM)) अणु
		func = SI476X_FUNC_FM_RECEIVER;

	पूर्ण अन्यथा अगर (si476x_core_has_am(radio->core) &&
		   si476x_radio_range_is_inside_of_the_band(rangelow, rangehigh,
							    SI476X_BAND_AM)) अणु
		func = SI476X_FUNC_AM_RECEIVER;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = si476x_radio_change_func(radio, func);
	अगर (err < 0)
		जाओ unlock;

	अगर (seek->rangehigh) अणु
		err = regmap_ग_लिखो(radio->core->regmap,
				   SI476X_PROP_SEEK_BAND_TOP,
				   v4l2_to_si476x(radio->core,
						  seek->rangehigh));
		अगर (err)
			जाओ unlock;
	पूर्ण
	अगर (seek->rangelow) अणु
		err = regmap_ग_लिखो(radio->core->regmap,
				   SI476X_PROP_SEEK_BAND_BOTTOM,
				   v4l2_to_si476x(radio->core,
						  seek->rangelow));
		अगर (err)
			जाओ unlock;
	पूर्ण
	अगर (seek->spacing) अणु
		err = regmap_ग_लिखो(radio->core->regmap,
				     SI476X_PROP_SEEK_FREQUENCY_SPACING,
				     v4l2_to_si476x(radio->core,
						    seek->spacing));
		अगर (err)
			जाओ unlock;
	पूर्ण

	err = radio->ops->seek_start(radio->core,
				     seek->seek_upward,
				     seek->wrap_around);
unlock:
	si476x_core_unlock(radio->core);



	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	पूर्णांक retval;
	काष्ठा si476x_radio *radio = v4l2_ctrl_handler_to_radio(ctrl->handler);

	si476x_core_lock(radio->core);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_SI476X_INTERCHIP_LINK:
		अगर (si476x_core_has_भागersity(radio->core)) अणु
			अगर (radio->ops->phase_भागersity) अणु
				retval = radio->ops->phase_भाग_status(radio->core);
				अगर (retval < 0)
					अवरोध;

				ctrl->val = !!SI476X_PHDIV_STATUS_LINK_LOCKED(retval);
				retval = 0;
				अवरोध;
			पूर्ण अन्यथा अणु
				retval = -ENOTTY;
				अवरोध;
			पूर्ण
		पूर्ण
		retval = -EINVAL;
		अवरोध;
	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण
	si476x_core_unlock(radio->core);
	वापस retval;

पूर्ण

अटल पूर्णांक si476x_radio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	पूर्णांक retval;
	क्रमागत si476x_phase_भागersity_mode mode;
	काष्ठा si476x_radio *radio = v4l2_ctrl_handler_to_radio(ctrl->handler);

	si476x_core_lock(radio->core);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_SI476X_HARMONICS_COUNT:
		retval = regmap_update_bits(radio->core->regmap,
					    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
					    SI476X_PROP_PWR_HARMONICS_MASK,
					    ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		चयन (ctrl->val) अणु
		हाल V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_ENABLE_MASK,
						    0);
			अवरोध;
		हाल V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_GRID_MASK,
						    SI476X_PROP_PWR_GRID_50HZ);
			अवरोध;
		हाल V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_GRID_MASK,
						    SI476X_PROP_PWR_GRID_60HZ);
			अवरोध;
		शेष:
			retval = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_SI476X_RSSI_THRESHOLD:
		retval = regmap_ग_लिखो(radio->core->regmap,
				      SI476X_PROP_VALID_RSSI_THRESHOLD,
				      ctrl->val);
		अवरोध;
	हाल V4L2_CID_SI476X_SNR_THRESHOLD:
		retval = regmap_ग_लिखो(radio->core->regmap,
				      SI476X_PROP_VALID_SNR_THRESHOLD,
				      ctrl->val);
		अवरोध;
	हाल V4L2_CID_SI476X_MAX_TUNE_ERROR:
		retval = regmap_ग_लिखो(radio->core->regmap,
				      SI476X_PROP_VALID_MAX_TUNE_ERROR,
				      ctrl->val);
		अवरोध;
	हाल V4L2_CID_RDS_RECEPTION:
		/*
		 * It looks like RDS related properties are
		 * inaccessible when tuner is in AM mode, so cache the
		 * changes
		 */
		अगर (si476x_core_is_in_am_receiver_mode(radio->core))
			regcache_cache_only(radio->core->regmap, true);

		अगर (ctrl->val) अणु
			retval = regmap_ग_लिखो(radio->core->regmap,
					      SI476X_PROP_FM_RDS_INTERRUPT_FIFO_COUNT,
					      radio->core->rds_fअगरo_depth);
			अगर (retval < 0)
				अवरोध;

			अगर (radio->core->client->irq) अणु
				retval = regmap_ग_लिखो(radio->core->regmap,
						      SI476X_PROP_FM_RDS_INTERRUPT_SOURCE,
						      SI476X_RDSRECV);
				अगर (retval < 0)
					अवरोध;
			पूर्ण

			/* Drain RDS FIFO beक्रमe enabling RDS processing */
			retval = si476x_core_cmd_fm_rds_status(radio->core,
							       false,
							       true,
							       true,
							       शून्य);
			अगर (retval < 0)
				अवरोध;

			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_FM_RDS_CONFIG,
						    SI476X_PROP_RDSEN_MASK,
						    SI476X_PROP_RDSEN);
		पूर्ण अन्यथा अणु
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_FM_RDS_CONFIG,
						    SI476X_PROP_RDSEN_MASK,
						    !SI476X_PROP_RDSEN);
		पूर्ण

		अगर (si476x_core_is_in_am_receiver_mode(radio->core))
			regcache_cache_only(radio->core->regmap, false);
		अवरोध;
	हाल V4L2_CID_TUNE_DEEMPHASIS:
		retval = regmap_ग_लिखो(radio->core->regmap,
				      SI476X_PROP_AUDIO_DEEMPHASIS,
				      ctrl->val);
		अवरोध;

	हाल V4L2_CID_SI476X_DIVERSITY_MODE:
		mode = si476x_phase_भागersity_idx_to_mode(ctrl->val);

		अगर (mode == radio->core->भागersity_mode) अणु
			retval = 0;
			अवरोध;
		पूर्ण

		अगर (si476x_core_is_in_am_receiver_mode(radio->core)) अणु
			/*
			 * Diversity cannot be configured जबतक tuner
			 * is in AM mode so save the changes and carry on.
			 */
			radio->core->भागersity_mode = mode;
			retval = 0;
		पूर्ण अन्यथा अणु
			retval = radio->ops->phase_भागersity(radio->core, mode);
			अगर (!retval)
				radio->core->भागersity_mode = mode;
		पूर्ण
		अवरोध;

	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण

	si476x_core_unlock(radio->core);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक si476x_radio_g_रेजिस्टर(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक value;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	si476x_core_lock(radio->core);
	reg->size = 2;
	err = regmap_पढ़ो(radio->core->regmap,
			  (अचिन्हित पूर्णांक)reg->reg, &value);
	reg->val = value;
	si476x_core_unlock(radio->core);

	वापस err;
पूर्ण
अटल पूर्णांक si476x_radio_s_रेजिस्टर(काष्ठा file *file, व्योम *fh,
				   स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु

	पूर्णांक err;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	si476x_core_lock(radio->core);
	err = regmap_ग_लिखो(radio->core->regmap,
			   (अचिन्हित पूर्णांक)reg->reg,
			   (अचिन्हित पूर्णांक)reg->val);
	si476x_core_unlock(radio->core);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक si476x_radio_fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा si476x_radio *radio = video_drvdata(file);
	पूर्णांक err;

	err = v4l2_fh_खोलो(file);
	अगर (err)
		वापस err;

	अगर (v4l2_fh_is_singular_file(file)) अणु
		si476x_core_lock(radio->core);
		err = si476x_core_set_घातer_state(radio->core,
						  SI476X_POWER_UP_FULL);
		अगर (err < 0)
			जाओ करोne;

		err = si476x_radio_करो_post_घातerup_init(radio,
							radio->core->घातer_up_parameters.func);
		अगर (err < 0)
			जाओ घातer_करोwn;

		err = si476x_radio_pretune(radio,
					   radio->core->घातer_up_parameters.func);
		अगर (err < 0)
			जाओ घातer_करोwn;

		si476x_core_unlock(radio->core);
		/*Must be करोne after si476x_core_unlock to prevent a deadlock*/
		v4l2_ctrl_handler_setup(&radio->ctrl_handler);
	पूर्ण

	वापस err;

घातer_करोwn:
	si476x_core_set_घातer_state(radio->core,
				    SI476X_POWER_DOWN);
करोne:
	si476x_core_unlock(radio->core);
	v4l2_fh_release(file);

	वापस err;
पूर्ण

अटल पूर्णांक si476x_radio_fops_release(काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = video_drvdata(file);

	अगर (v4l2_fh_is_singular_file(file) &&
	    atomic_पढ़ो(&radio->core->is_alive))
		si476x_core_set_घातer_state(radio->core,
					    SI476X_POWER_DOWN);

	err = v4l2_fh_release(file);

	वापस err;
पूर्ण

अटल sमाप_प्रकार si476x_radio_fops_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार      rval;
	माप_प्रकार       fअगरo_len;
	अचिन्हित पूर्णांक copied;

	काष्ठा si476x_radio *radio = video_drvdata(file);

	/* block अगर no new data available */
	अगर (kfअगरo_is_empty(&radio->core->rds_fअगरo)) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;

		rval = रुको_event_पूर्णांकerruptible(radio->core->rds_पढ़ो_queue,
						(!kfअगरo_is_empty(&radio->core->rds_fअगरo) ||
						 !atomic_पढ़ो(&radio->core->is_alive)));
		अगर (rval < 0)
			वापस -EINTR;

		अगर (!atomic_पढ़ो(&radio->core->is_alive))
			वापस -ENODEV;
	पूर्ण

	fअगरo_len = kfअगरo_len(&radio->core->rds_fअगरo);

	अगर (kfअगरo_to_user(&radio->core->rds_fअगरo, buf,
			  min(fअगरo_len, count),
			  &copied) != 0) अणु
		dev_warn(&radio->videodev.dev,
			 "Error during FIFO to userspace copy\n");
		rval = -EIO;
	पूर्ण अन्यथा अणु
		rval = (sमाप_प्रकार)copied;
	पूर्ण

	वापस rval;
पूर्ण

अटल __poll_t si476x_radio_fops_poll(काष्ठा file *file,
				काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा si476x_radio *radio = video_drvdata(file);
	__poll_t req_events = poll_requested_events(pts);
	__poll_t err = v4l2_ctrl_poll(file, pts);

	अगर (req_events & (EPOLLIN | EPOLLRDNORM)) अणु
		अगर (atomic_पढ़ो(&radio->core->is_alive))
			poll_रुको(file, &radio->core->rds_पढ़ो_queue, pts);

		अगर (!atomic_पढ़ो(&radio->core->is_alive))
			err = EPOLLHUP;

		अगर (!kfअगरo_is_empty(&radio->core->rds_fअगरo))
			err = EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations si476x_fops = अणु
	.owner			= THIS_MODULE,
	.पढ़ो			= si476x_radio_fops_पढ़ो,
	.poll			= si476x_radio_fops_poll,
	.unlocked_ioctl		= video_ioctl2,
	.खोलो			= si476x_radio_fops_खोलो,
	.release		= si476x_radio_fops_release,
पूर्ण;


अटल स्थिर काष्ठा v4l2_ioctl_ops si4761_ioctl_ops = अणु
	.vidioc_querycap		= si476x_radio_querycap,
	.vidioc_g_tuner			= si476x_radio_g_tuner,
	.vidioc_s_tuner			= si476x_radio_s_tuner,

	.vidioc_g_frequency		= si476x_radio_g_frequency,
	.vidioc_s_frequency		= si476x_radio_s_frequency,
	.vidioc_s_hw_freq_seek		= si476x_radio_s_hw_freq_seek,
	.vidioc_क्रमागत_freq_bands		= si476x_radio_क्रमागत_freq_bands,

	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर		= si476x_radio_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर		= si476x_radio_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;


अटल स्थिर काष्ठा video_device si476x_viddev_ढाँचा = अणु
	.fops			= &si476x_fops,
	.name			= DRIVER_NAME,
	.release		= video_device_release_empty,
पूर्ण;



अटल sमाप_प्रकार si476x_radio_पढ़ो_acf_blob(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = file->निजी_data;
	काष्ठा si476x_acf_status_report report;

	si476x_core_lock(radio->core);
	अगर (radio->ops->acf_status)
		err = radio->ops->acf_status(radio->core, &report);
	अन्यथा
		err = -ENOENT;
	si476x_core_unlock(radio->core);

	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, &report,
				       माप(report));
पूर्ण

अटल स्थिर काष्ठा file_operations radio_acf_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो	= si476x_radio_पढ़ो_acf_blob,
पूर्ण;

अटल sमाप_प्रकार si476x_radio_पढ़ो_rds_blckcnt_blob(काष्ठा file *file,
						  अक्षर __user *user_buf,
						  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = file->निजी_data;
	काष्ठा si476x_rds_blockcount_report report;

	si476x_core_lock(radio->core);
	अगर (radio->ops->rds_blckcnt)
		err = radio->ops->rds_blckcnt(radio->core, true,
					       &report);
	अन्यथा
		err = -ENOENT;
	si476x_core_unlock(radio->core);

	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, &report,
				       माप(report));
पूर्ण

अटल स्थिर काष्ठा file_operations radio_rds_blckcnt_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो	= si476x_radio_पढ़ो_rds_blckcnt_blob,
पूर्ण;

अटल sमाप_प्रकार si476x_radio_पढ़ो_agc_blob(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = file->निजी_data;
	काष्ठा si476x_agc_status_report report;

	si476x_core_lock(radio->core);
	अगर (radio->ops->rds_blckcnt)
		err = radio->ops->agc_status(radio->core, &report);
	अन्यथा
		err = -ENOENT;
	si476x_core_unlock(radio->core);

	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, &report,
				       माप(report));
पूर्ण

अटल स्थिर काष्ठा file_operations radio_agc_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो	= si476x_radio_पढ़ो_agc_blob,
पूर्ण;

अटल sमाप_प्रकार si476x_radio_पढ़ो_rsq_blob(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = file->निजी_data;
	काष्ठा si476x_rsq_status_report report;
	काष्ठा si476x_rsq_status_args args = अणु
		.primary	= false,
		.rsqack		= false,
		.attune		= false,
		.cancel		= false,
		.stcack		= false,
	पूर्ण;

	si476x_core_lock(radio->core);
	अगर (radio->ops->rds_blckcnt)
		err = radio->ops->rsq_status(radio->core, &args, &report);
	अन्यथा
		err = -ENOENT;
	si476x_core_unlock(radio->core);

	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, &report,
				       माप(report));
पूर्ण

अटल स्थिर काष्ठा file_operations radio_rsq_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो	= si476x_radio_पढ़ो_rsq_blob,
पूर्ण;

अटल sमाप_प्रकार si476x_radio_पढ़ो_rsq_primary_blob(काष्ठा file *file,
						  अक्षर __user *user_buf,
						  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा si476x_radio *radio = file->निजी_data;
	काष्ठा si476x_rsq_status_report report;
	काष्ठा si476x_rsq_status_args args = अणु
		.primary	= true,
		.rsqack		= false,
		.attune		= false,
		.cancel		= false,
		.stcack		= false,
	पूर्ण;

	si476x_core_lock(radio->core);
	अगर (radio->ops->rds_blckcnt)
		err = radio->ops->rsq_status(radio->core, &args, &report);
	अन्यथा
		err = -ENOENT;
	si476x_core_unlock(radio->core);

	अगर (err < 0)
		वापस err;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, &report,
				       माप(report));
पूर्ण

अटल स्थिर काष्ठा file_operations radio_rsq_primary_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो	= si476x_radio_पढ़ो_rsq_primary_blob,
पूर्ण;


अटल व्योम si476x_radio_init_debugfs(काष्ठा si476x_radio *radio)
अणु
	radio->debugfs = debugfs_create_dir(dev_name(radio->v4l2dev.dev), शून्य);

	debugfs_create_file("acf", S_IRUGO, radio->debugfs, radio,
			    &radio_acf_fops);

	debugfs_create_file("rds_blckcnt", S_IRUGO, radio->debugfs, radio,
			    &radio_rds_blckcnt_fops);

	debugfs_create_file("agc", S_IRUGO, radio->debugfs, radio,
			    &radio_agc_fops);

	debugfs_create_file("rsq", S_IRUGO, radio->debugfs, radio,
			    &radio_rsq_fops);

	debugfs_create_file("rsq_primary", S_IRUGO, radio->debugfs, radio,
			    &radio_rsq_primary_fops);
पूर्ण


अटल पूर्णांक si476x_radio_add_new_custom(काष्ठा si476x_radio *radio,
				       क्रमागत si476x_ctrl_idx idx)
अणु
	पूर्णांक rval;
	काष्ठा v4l2_ctrl *ctrl;

	ctrl = v4l2_ctrl_new_custom(&radio->ctrl_handler,
				    &si476x_ctrls[idx],
				    शून्य);
	rval = radio->ctrl_handler.error;
	अगर (ctrl == शून्य && rval)
		dev_err(radio->v4l2dev.dev,
			"Could not initialize '%s' control %d\n",
			si476x_ctrls[idx].name, rval);

	वापस rval;
पूर्ण

अटल पूर्णांक si476x_radio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rval;
	काष्ठा si476x_radio *radio;
	काष्ठा v4l2_ctrl *ctrl;

	अटल atomic_t instance = ATOMIC_INIT(0);

	radio = devm_kzalloc(&pdev->dev, माप(*radio), GFP_KERNEL);
	अगर (!radio)
		वापस -ENOMEM;

	radio->core = i2c_mfd_cell_to_core(&pdev->dev);

	v4l2_device_set_name(&radio->v4l2dev, DRIVER_NAME, &instance);

	rval = v4l2_device_रेजिस्टर(&pdev->dev, &radio->v4l2dev);
	अगर (rval) अणु
		dev_err(&pdev->dev, "Cannot register v4l2_device.\n");
		वापस rval;
	पूर्ण

	स_नकल(&radio->videodev, &si476x_viddev_ढाँचा,
	       माप(काष्ठा video_device));

	radio->videodev.v4l2_dev  = &radio->v4l2dev;
	radio->videodev.ioctl_ops = &si4761_ioctl_ops;
	radio->videodev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
				      V4L2_CAP_HW_FREQ_SEEK;

	si476x_core_lock(radio->core);
	अगर (!si476x_core_is_a_secondary_tuner(radio->core))
		radio->videodev.device_caps |= V4L2_CAP_RDS_CAPTURE |
					       V4L2_CAP_READWRITE;
	si476x_core_unlock(radio->core);

	video_set_drvdata(&radio->videodev, radio);
	platक्रमm_set_drvdata(pdev, radio);


	radio->v4l2dev.ctrl_handler = &radio->ctrl_handler;
	v4l2_ctrl_handler_init(&radio->ctrl_handler,
			       1 + ARRAY_SIZE(si476x_ctrls));

	अगर (si476x_core_has_am(radio->core)) अणु
		ctrl = v4l2_ctrl_new_std_menu(&radio->ctrl_handler,
					      &si476x_ctrl_ops,
					      V4L2_CID_POWER_LINE_FREQUENCY,
					      V4L2_CID_POWER_LINE_FREQUENCY_60HZ,
					      0, 0);
		rval = radio->ctrl_handler.error;
		अगर (ctrl == शून्य && rval) अणु
			dev_err(&pdev->dev, "Could not initialize V4L2_CID_POWER_LINE_FREQUENCY control %d\n",
				rval);
			जाओ निकास;
		पूर्ण

		rval = si476x_radio_add_new_custom(radio,
						   SI476X_IDX_HARMONICS_COUNT);
		अगर (rval < 0)
			जाओ निकास;
	पूर्ण

	rval = si476x_radio_add_new_custom(radio, SI476X_IDX_RSSI_THRESHOLD);
	अगर (rval < 0)
		जाओ निकास;

	rval = si476x_radio_add_new_custom(radio, SI476X_IDX_SNR_THRESHOLD);
	अगर (rval < 0)
		जाओ निकास;

	rval = si476x_radio_add_new_custom(radio, SI476X_IDX_MAX_TUNE_ERROR);
	अगर (rval < 0)
		जाओ निकास;

	ctrl = v4l2_ctrl_new_std_menu(&radio->ctrl_handler,
				      &si476x_ctrl_ops,
				      V4L2_CID_TUNE_DEEMPHASIS,
				      V4L2_DEEMPHASIS_75_uS, 0, 0);
	rval = radio->ctrl_handler.error;
	अगर (ctrl == शून्य && rval) अणु
		dev_err(&pdev->dev, "Could not initialize V4L2_CID_TUNE_DEEMPHASIS control %d\n",
			rval);
		जाओ निकास;
	पूर्ण

	ctrl = v4l2_ctrl_new_std(&radio->ctrl_handler, &si476x_ctrl_ops,
				 V4L2_CID_RDS_RECEPTION,
				 0, 1, 1, 1);
	rval = radio->ctrl_handler.error;
	अगर (ctrl == शून्य && rval) अणु
		dev_err(&pdev->dev, "Could not initialize V4L2_CID_RDS_RECEPTION control %d\n",
			rval);
		जाओ निकास;
	पूर्ण

	अगर (si476x_core_has_भागersity(radio->core)) अणु
		si476x_ctrls[SI476X_IDX_DIVERSITY_MODE].def =
			si476x_phase_भागersity_mode_to_idx(radio->core->भागersity_mode);
		rval = si476x_radio_add_new_custom(radio, SI476X_IDX_DIVERSITY_MODE);
		अगर (rval < 0)
			जाओ निकास;

		rval = si476x_radio_add_new_custom(radio, SI476X_IDX_INTERCHIP_LINK);
		अगर (rval < 0)
			जाओ निकास;
	पूर्ण

	/* रेजिस्टर video device */
	rval = video_रेजिस्टर_device(&radio->videodev, VFL_TYPE_RADIO, -1);
	अगर (rval < 0) अणु
		dev_err(&pdev->dev, "Could not register video device\n");
		जाओ निकास;
	पूर्ण

	si476x_radio_init_debugfs(radio);

	वापस 0;
निकास:
	v4l2_ctrl_handler_मुक्त(radio->videodev.ctrl_handler);
	वापस rval;
पूर्ण

अटल पूर्णांक si476x_radio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा si476x_radio *radio = platक्रमm_get_drvdata(pdev);

	v4l2_ctrl_handler_मुक्त(radio->videodev.ctrl_handler);
	video_unरेजिस्टर_device(&radio->videodev);
	v4l2_device_unरेजिस्टर(&radio->v4l2dev);
	debugfs_हटाओ_recursive(radio->debugfs);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:si476x-radio");

अटल काष्ठा platक्रमm_driver si476x_radio_driver = अणु
	.driver		= अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe		= si476x_radio_probe,
	.हटाओ		= si476x_radio_हटाओ,
पूर्ण;
module_platक्रमm_driver(si476x_radio_driver);

MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("Driver for Si4761/64/68 AM/FM Radio MFD Cell");
MODULE_LICENSE("GPL");
