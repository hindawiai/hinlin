<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/media/si476x-core.h -- Common definitions क्रम si476x core
 * device
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#अगर_अघोषित SI476X_CORE_H
#घोषणा SI476X_CORE_H

#समावेश <linux/kfअगरo.h>
#समावेश <linux/atomic.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/mfd/si476x-platक्रमm.h>
#समावेश <linux/mfd/si476x-reports.h>

/* Command Timeouts */
#घोषणा SI476X_DEFAULT_TIMEOUT	100000
#घोषणा SI476X_TIMEOUT_TUNE	700000
#घोषणा SI476X_TIMEOUT_POWER_UP	330000
#घोषणा SI476X_STATUS_POLL_US	0

/* -------------------- si476x-i2c.c ----------------------- */

क्रमागत si476x_freq_supported_chips अणु
	SI476X_CHIP_SI4761 = 1,
	SI476X_CHIP_SI4764,
	SI476X_CHIP_SI4768,
पूर्ण;

क्रमागत si476x_part_revisions अणु
	SI476X_REVISION_A10 = 0,
	SI476X_REVISION_A20 = 1,
	SI476X_REVISION_A30 = 2,
पूर्ण;

क्रमागत si476x_mfd_cells अणु
	SI476X_RADIO_CELL = 0,
	SI476X_CODEC_CELL,
	SI476X_MFD_CELLS,
पूर्ण;

/**
 * क्रमागत si476x_घातer_state - possible घातer state of the si476x
 * device.
 *
 * @SI476X_POWER_DOWN: In this state all regulators are turned off
 * and the reset line is pulled low. The device is completely
 * inactive.
 * @SI476X_POWER_UP_FULL: In this state all the घातer regulators are
 * turned on, reset line pulled high, IRQ line is enabled(polling is
 * active क्रम polling use scenario) and device is turned on with
 * POWER_UP command. The device is पढ़ोy to be used.
 * @SI476X_POWER_INCONSISTENT: This state indicates that previous
 * घातer करोwn was inconsistent, meaning some of the regulators were
 * not turned करोwn and thus use of the device, without घातer-cycling
 * is impossible.
 */
क्रमागत si476x_घातer_state अणु
	SI476X_POWER_DOWN		= 0,
	SI476X_POWER_UP_FULL		= 1,
	SI476X_POWER_INCONSISTENT	= 2,
पूर्ण;

/**
 * काष्ठा si476x_core - पूर्णांकernal data काष्ठाure representing the
 * underlying "core" device which all the MFD cell-devices use.
 *
 * @client: Actual I2C client used to transfer commands to the chip.
 * @chip_id: Last digit of the chip model(E.g. "1" क्रम SI4761)
 * @cells: MFD cell devices created by this driver.
 * @cmd_lock: Mutex used to serialize all the requests to the core
 * device. This filed should not be used directly. Instead
 * si476x_core_lock()/si476x_core_unlock() should be used to get
 * exclusive access to the "core" device.
 * @users: Active users counter(Used by the radio cell)
 * @rds_पढ़ो_queue: Wait queue used to रुको क्रम RDS data.
 * @rds_fअगरo: FIFO in which all the RDS data received from the chip is
 * placed.
 * @rds_fअगरo_drainer: Worker that drains on-chip RDS FIFO.
 * @rds_drainer_is_working: Flag used क्रम launching only one instance
 * of the @rds_fअगरo_drainer.
 * @rds_drainer_status_lock: Lock used to guard access to the
 * @rds_drainer_is_working variable.
 * @command: Wait queue क्रम waपूर्णांकing on the command comapletion.
 * @cts: Clear To Send flag set upon receiving first status with CTS
 * set.
 * @tuning: Wait queue used क्रम waपूर्णांकing क्रम tune/seek comand
 * completion.
 * @stc: Similar to @cts, but क्रम the STC bit of the status value.
 * @घातer_up_parameters: Parameters used as argument क्रम POWER_UP
 * command when the device is started.
 * @state: Current घातer state of the device.
 * @supplues: Structure containing handles to all घातer supplies used
 * by the device (शून्य ones are ignored).
 * @gpio_reset: GPIO pin connectet to the RSTB pin of the chip.
 * @pinmux: Chip's configurable pins configuration.
 * @भागersity_mode: Chips role when functioning in भागersity mode.
 * @status_monitor: Polling worker used in polling use हाल scenarion
 * (when IRQ is not avalible).
 * @revision: Chip's running firmware revision number(Used क्रम correct
 * command set support).
 */

काष्ठा si476x_core अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	पूर्णांक chip_id;
	काष्ठा mfd_cell cells[SI476X_MFD_CELLS];

	काष्ठा mutex cmd_lock; /* क्रम serializing fm radio operations */
	atomic_t users;

	रुको_queue_head_t  rds_पढ़ो_queue;
	काष्ठा kfअगरo       rds_fअगरo;
	काष्ठा work_काष्ठा rds_fअगरo_drainer;
	bool               rds_drainer_is_working;
	काष्ठा mutex       rds_drainer_status_lock;

	रुको_queue_head_t command;
	atomic_t          cts;

	रुको_queue_head_t tuning;
	atomic_t          stc;

	काष्ठा si476x_घातer_up_args घातer_up_parameters;

	क्रमागत si476x_घातer_state घातer_state;

	काष्ठा regulator_bulk_data supplies[4];

	पूर्णांक gpio_reset;

	काष्ठा si476x_pinmux pinmux;
	क्रमागत si476x_phase_भागersity_mode भागersity_mode;

	atomic_t is_alive;

	काष्ठा delayed_work status_monitor;
#घोषणा SI476X_WORK_TO_CORE(w) container_of(to_delayed_work(w),	\
					    काष्ठा si476x_core,	\
					    status_monitor)

	पूर्णांक revision;

	पूर्णांक rds_fअगरo_depth;
पूर्ण;

अटल अंतरभूत काष्ठा si476x_core *i2c_mfd_cell_to_core(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	वापस i2c_get_clientdata(client);
पूर्ण


/**
 * si476x_core_lock() - lock the core device to get an exclusive access
 * to it.
 */
अटल अंतरभूत व्योम si476x_core_lock(काष्ठा si476x_core *core)
अणु
	mutex_lock(&core->cmd_lock);
पूर्ण

/**
 * si476x_core_unlock() - unlock the core device to relinquish an
 * exclusive access to it.
 */
अटल अंतरभूत व्योम si476x_core_unlock(काष्ठा si476x_core *core)
अणु
	mutex_unlock(&core->cmd_lock);
पूर्ण

/* *_TUNE_FREQ family of commands accept frequency in multiples of
    10kHz */
अटल अंतरभूत u16 hz_to_si476x(काष्ठा si476x_core *core, पूर्णांक freq)
अणु
	u16 result;

	चयन (core->घातer_up_parameters.func) अणु
	शेष:
	हाल SI476X_FUNC_FM_RECEIVER:
		result = freq / 10000;
		अवरोध;
	हाल SI476X_FUNC_AM_RECEIVER:
		result = freq / 1000;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक si476x_to_hz(काष्ठा si476x_core *core, u16 freq)
अणु
	पूर्णांक result;

	चयन (core->घातer_up_parameters.func) अणु
	शेष:
	हाल SI476X_FUNC_FM_RECEIVER:
		result = freq * 10000;
		अवरोध;
	हाल SI476X_FUNC_AM_RECEIVER:
		result = freq * 1000;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/* Since the V4L2_TUNER_CAP_LOW flag is supplied, V4L2 subप्रणाली
 * mesures frequency in 62.5 Hz units */

अटल अंतरभूत पूर्णांक hz_to_v4l2(पूर्णांक freq)
अणु
	वापस (freq * 10) / 625;
पूर्ण

अटल अंतरभूत पूर्णांक v4l2_to_hz(पूर्णांक freq)
अणु
	वापस (freq * 625) / 10;
पूर्ण

अटल अंतरभूत u16 v4l2_to_si476x(काष्ठा si476x_core *core, पूर्णांक freq)
अणु
	वापस hz_to_si476x(core, v4l2_to_hz(freq));
पूर्ण

अटल अंतरभूत पूर्णांक si476x_to_v4l2(काष्ठा si476x_core *core, u16 freq)
अणु
	वापस hz_to_v4l2(si476x_to_hz(core, freq));
पूर्ण



/**
 * काष्ठा si476x_func_info - काष्ठाure containing result of the
 * FUNC_INFO command.
 *
 * @firmware.major: Firmware major number.
 * @firmware.minor[...]: Firmware minor numbers.
 * @patch_id:
 * @func: Mode tuner is working in.
 */
काष्ठा si476x_func_info अणु
	काष्ठा अणु
		u8 major, minor[2];
	पूर्ण firmware;
	u16 patch_id;
	क्रमागत si476x_func func;
पूर्ण;

/**
 * काष्ठा si476x_घातer_करोwn_args - काष्ठाure used to pass parameters
 * to POWER_DOWN command
 *
 * @xosc: true - Power करोwn, but leav oscillator running.
 *        false - Full घातer करोwn.
 */
काष्ठा si476x_घातer_करोwn_args अणु
	bool xosc;
पूर्ण;

/**
 * क्रमागत si476x_tunemode - क्रमागत representing possible tune modes क्रम
 * the chip.
 * @SI476X_TM_VALIDATED_NORMAL_TUNE: Unconditionally stay on the new
 * channel after tune, tune status is valid.
 * @SI476X_TM_INVALIDATED_FAST_TUNE: Unconditionally stay in the new
 * channel after tune, tune status invalid.
 * @SI476X_TM_VALIDATED_AF_TUNE: Jump back to previous channel अगर
 * metric thresholds are not met.
 * @SI476X_TM_VALIDATED_AF_CHECK: Unconditionally jump back to the
 * previous channel.
 */
क्रमागत si476x_tunemode अणु
	SI476X_TM_VALIDATED_NORMAL_TUNE = 0,
	SI476X_TM_INVALIDATED_FAST_TUNE = 1,
	SI476X_TM_VALIDATED_AF_TUNE     = 2,
	SI476X_TM_VALIDATED_AF_CHECK    = 3,
पूर्ण;

/**
 * क्रमागत si476x_smoothmetrics - क्रमागत containing the possible setting fo
 * audio transitioning of the chip
 * @SI476X_SM_INITIALIZE_AUDIO: Initialize audio state to match this
 * new channel
 * @SI476X_SM_TRANSITION_AUDIO: Transition audio state from previous
 * channel values to the new values
 */
क्रमागत si476x_smoothmetrics अणु
	SI476X_SM_INITIALIZE_AUDIO = 0,
	SI476X_SM_TRANSITION_AUDIO = 1,
पूर्ण;

/**
 * काष्ठा si476x_rds_status_report - the काष्ठाure representing the
 * response to 'FM_RD_STATUS' command
 * @rdstpptyपूर्णांक: Traffic program flag(TP) and/or program type(PTY)
 * code has changed.
 * @rdspiपूर्णांक: Program identअगरication(PI) code has changed.
 * @rdssyncपूर्णांक: RDS synchronization has changed.
 * @rdsfअगरoपूर्णांक: RDS was received and the RDS FIFO has at least
 * 'FM_RDS_INTERRUPT_FIFO_COUNT' elements in it.
 * @tpptyvalid: TP flag and PTY code are valid falg.
 * @pivalid: PI code is valid flag.
 * @rdssync: RDS is currently synchronized.
 * @rdsfअगरolost: On or more RDS groups have been lost/discarded flag.
 * @tp: Current channel's TP flag.
 * @pty: Current channel's PTY code.
 * @pi: Current channel's PI code.
 * @rdsfअगरoused: Number of blocks reमुख्यing in the RDS FIFO (0 अगर
 * empty).
 */
काष्ठा si476x_rds_status_report अणु
	bool rdstpptyपूर्णांक, rdspiपूर्णांक, rdssyncपूर्णांक, rdsfअगरoपूर्णांक;
	bool tpptyvalid, pivalid, rdssync, rdsfअगरolost;
	bool tp;

	u8 pty;
	u16 pi;

	u8 rdsfअगरoused;
	u8 ble[4];

	काष्ठा v4l2_rds_data rds[4];
पूर्ण;

काष्ठा si476x_rsq_status_args अणु
	bool primary;
	bool rsqack;
	bool attune;
	bool cancel;
	bool stcack;
पूर्ण;

क्रमागत si476x_injside अणु
	SI476X_INJSIDE_AUTO	= 0,
	SI476X_INJSIDE_LOW	= 1,
	SI476X_INJSIDE_HIGH	= 2,
पूर्ण;

काष्ठा si476x_tune_freq_args अणु
	bool zअगरsr;
	bool hd;
	क्रमागत si476x_injside injside;
	पूर्णांक freq;
	क्रमागत si476x_tunemode tunemode;
	क्रमागत si476x_smoothmetrics smoothmetrics;
	पूर्णांक antcap;
पूर्ण;

पूर्णांक  si476x_core_stop(काष्ठा si476x_core *, bool);
पूर्णांक  si476x_core_start(काष्ठा si476x_core *, bool);
पूर्णांक  si476x_core_set_घातer_state(काष्ठा si476x_core *, क्रमागत si476x_घातer_state);
bool si476x_core_has_am(काष्ठा si476x_core *);
bool si476x_core_has_भागersity(काष्ठा si476x_core *);
bool si476x_core_is_a_secondary_tuner(काष्ठा si476x_core *);
bool si476x_core_is_a_primary_tuner(काष्ठा si476x_core *);
bool si476x_core_is_in_am_receiver_mode(काष्ठा si476x_core *core);
bool si476x_core_is_घातered_up(काष्ठा si476x_core *core);

क्रमागत si476x_i2c_type अणु
	SI476X_I2C_SEND,
	SI476X_I2C_RECV
पूर्ण;

पूर्णांक si476x_core_i2c_xfer(काष्ठा si476x_core *,
			 क्रमागत si476x_i2c_type,
			 अक्षर *, पूर्णांक);


/* -------------------- si476x-cmd.c ----------------------- */

पूर्णांक si476x_core_cmd_func_info(काष्ठा si476x_core *, काष्ठा si476x_func_info *);
पूर्णांक si476x_core_cmd_set_property(काष्ठा si476x_core *, u16, u16);
पूर्णांक si476x_core_cmd_get_property(काष्ठा si476x_core *, u16);
पूर्णांक si476x_core_cmd_dig_audio_pin_cfg(काष्ठा si476x_core *,
				      क्रमागत si476x_dclk_config,
				      क्रमागत si476x_dfs_config,
				      क्रमागत si476x_करोut_config,
				      क्रमागत si476x_xout_config);
पूर्णांक si476x_core_cmd_zअगर_pin_cfg(काष्ठा si476x_core *,
				क्रमागत si476x_iqclk_config,
				क्रमागत si476x_iqfs_config,
				क्रमागत si476x_iout_config,
				क्रमागत si476x_qout_config);
पूर्णांक si476x_core_cmd_ic_link_gpo_ctl_pin_cfg(काष्ठा si476x_core *,
					    क्रमागत si476x_icin_config,
					    क्रमागत si476x_icip_config,
					    क्रमागत si476x_icon_config,
					    क्रमागत si476x_icop_config);
पूर्णांक si476x_core_cmd_ana_audio_pin_cfg(काष्ठा si476x_core *,
				      क्रमागत si476x_lrout_config);
पूर्णांक si476x_core_cmd_पूर्णांकb_pin_cfg(काष्ठा si476x_core *, क्रमागत si476x_पूर्णांकb_config,
				 क्रमागत si476x_a1_config);
पूर्णांक si476x_core_cmd_fm_seek_start(काष्ठा si476x_core *, bool, bool);
पूर्णांक si476x_core_cmd_am_seek_start(काष्ठा si476x_core *, bool, bool);
पूर्णांक si476x_core_cmd_fm_rds_status(काष्ठा si476x_core *, bool, bool, bool,
				  काष्ठा si476x_rds_status_report *);
पूर्णांक si476x_core_cmd_fm_rds_blockcount(काष्ठा si476x_core *, bool,
				      काष्ठा si476x_rds_blockcount_report *);
पूर्णांक si476x_core_cmd_fm_tune_freq(काष्ठा si476x_core *,
				 काष्ठा si476x_tune_freq_args *);
पूर्णांक si476x_core_cmd_am_tune_freq(काष्ठा si476x_core *,
				 काष्ठा si476x_tune_freq_args *);
पूर्णांक si476x_core_cmd_am_rsq_status(काष्ठा si476x_core *,
				  काष्ठा si476x_rsq_status_args *,
				  काष्ठा si476x_rsq_status_report *);
पूर्णांक si476x_core_cmd_fm_rsq_status(काष्ठा si476x_core *,
				  काष्ठा si476x_rsq_status_args *,
				  काष्ठा si476x_rsq_status_report *);
पूर्णांक si476x_core_cmd_घातer_up(काष्ठा si476x_core *,
			     काष्ठा si476x_घातer_up_args *);
पूर्णांक si476x_core_cmd_घातer_करोwn(काष्ठा si476x_core *,
			       काष्ठा si476x_घातer_करोwn_args *);
पूर्णांक si476x_core_cmd_fm_phase_भाग_status(काष्ठा si476x_core *);
पूर्णांक si476x_core_cmd_fm_phase_भागersity(काष्ठा si476x_core *,
				       क्रमागत si476x_phase_भागersity_mode);

पूर्णांक si476x_core_cmd_fm_acf_status(काष्ठा si476x_core *,
				  काष्ठा si476x_acf_status_report *);
पूर्णांक si476x_core_cmd_am_acf_status(काष्ठा si476x_core *,
				  काष्ठा si476x_acf_status_report *);
पूर्णांक si476x_core_cmd_agc_status(काष्ठा si476x_core *,
			       काष्ठा si476x_agc_status_report *);

क्रमागत si476x_घातer_grid_type अणु
	SI476X_POWER_GRID_50HZ = 0,
	SI476X_POWER_GRID_60HZ,
पूर्ण;

/* Properties  */

क्रमागत si476x_पूर्णांकerrupt_flags अणु
	SI476X_STCIEN = (1 << 0),
	SI476X_ACFIEN = (1 << 1),
	SI476X_RDSIEN = (1 << 2),
	SI476X_RSQIEN = (1 << 3),

	SI476X_ERRIEN = (1 << 6),
	SI476X_CTSIEN = (1 << 7),

	SI476X_STCREP = (1 << 8),
	SI476X_ACFREP = (1 << 9),
	SI476X_RDSREP = (1 << 10),
	SI476X_RSQREP = (1 << 11),
पूर्ण;

क्रमागत si476x_rdsपूर्णांक_sources अणु
	SI476X_RDSTPPTY = (1 << 4),
	SI476X_RDSPI    = (1 << 3),
	SI476X_RDSSYNC	= (1 << 1),
	SI476X_RDSRECV	= (1 << 0),
पूर्ण;

क्रमागत si476x_status_response_bits अणु
	SI476X_CTS	  = (1 << 7),
	SI476X_ERR	  = (1 << 6),
	/* Status response क्रम WB receiver */
	SI476X_WB_ASQ_INT = (1 << 4),
	SI476X_RSQ_INT    = (1 << 3),
	/* Status response क्रम FM receiver */
	SI476X_FM_RDS_INT = (1 << 2),
	SI476X_ACF_INT    = (1 << 1),
	SI476X_STC_INT    = (1 << 0),
पूर्ण;

/* -------------------- si476x-prop.c ----------------------- */

क्रमागत si476x_common_receiver_properties अणु
	SI476X_PROP_INT_CTL_ENABLE			= 0x0000,
	SI476X_PROP_DIGITAL_IO_INPUT_SAMPLE_RATE	= 0x0200,
	SI476X_PROP_DIGITAL_IO_INPUT_FORMAT		= 0x0201,
	SI476X_PROP_DIGITAL_IO_OUTPUT_SAMPLE_RATE	= 0x0202,
	SI476X_PROP_DIGITAL_IO_OUTPUT_FORMAT		= 0x0203,

	SI476X_PROP_SEEK_BAND_BOTTOM			= 0x1100,
	SI476X_PROP_SEEK_BAND_TOP			= 0x1101,
	SI476X_PROP_SEEK_FREQUENCY_SPACING		= 0x1102,

	SI476X_PROP_VALID_MAX_TUNE_ERROR		= 0x2000,
	SI476X_PROP_VALID_SNR_THRESHOLD			= 0x2003,
	SI476X_PROP_VALID_RSSI_THRESHOLD		= 0x2004,
पूर्ण;

क्रमागत si476x_am_receiver_properties अणु
	SI476X_PROP_AUDIO_PWR_LINE_FILTER		= 0x0303,
पूर्ण;

क्रमागत si476x_fm_receiver_properties अणु
	SI476X_PROP_AUDIO_DEEMPHASIS			= 0x0302,

	SI476X_PROP_FM_RDS_INTERRUPT_SOURCE		= 0x4000,
	SI476X_PROP_FM_RDS_INTERRUPT_FIFO_COUNT		= 0x4001,
	SI476X_PROP_FM_RDS_CONFIG			= 0x4002,
पूर्ण;

क्रमागत si476x_prop_audio_pwr_line_filter_bits अणु
	SI476X_PROP_PWR_HARMONICS_MASK	= 0x001f,
	SI476X_PROP_PWR_GRID_MASK	= 0x0100,
	SI476X_PROP_PWR_ENABLE_MASK	= 0x0200,
	SI476X_PROP_PWR_GRID_50HZ	= 0x0000,
	SI476X_PROP_PWR_GRID_60HZ	= 0x0100,
पूर्ण;

क्रमागत si476x_prop_fm_rds_config_bits अणु
	SI476X_PROP_RDSEN_MASK	= 0x1,
	SI476X_PROP_RDSEN	= 0x1,
पूर्ण;


काष्ठा regmap *devm_regmap_init_si476x(काष्ठा si476x_core *);

#पूर्ण_अगर	/* SI476X_CORE_H */
