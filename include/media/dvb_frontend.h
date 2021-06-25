<शैली गुरु>
/*
 * dvb_frontend.h
 *
 * The Digital TV Frontend kABI defines a driver-पूर्णांकernal पूर्णांकerface क्रम
 * रेजिस्टरing low-level, hardware specअगरic driver to a hardware independent
 * frontend layer.
 *
 * Copyright (C) 2001 convergence पूर्णांकegrated media GmbH
 * Copyright (C) 2004 convergence GmbH
 *
 * Written by Ralph Metzler
 * Overhauled by Holger Waechtler
 * Kernel I2C stuff by Michael Hunold <hunold@convergence.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *

 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVB_FRONTEND_H_
#घोषणा _DVB_FRONTEND_H_

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

#समावेश <linux/dvb/frontend.h>

#समावेश <media/dvbdev.h>

/*
 * Maximum number of Delivery प्रणालीs per frontend. It
 * should be smaller or equal to 32
 */
#घोषणा MAX_DELSYS	8

/* Helper definitions to be used at frontend drivers */
#घोषणा kHz 1000UL
#घोषणा MHz 1000000UL

/**
 * काष्ठा dvb_frontend_tune_settings - parameters to adjust frontend tuning
 *
 * @min_delay_ms:	minimum delay क्रम tuning, in ms
 * @step_size:		step size between two consecutive frequencies
 * @max_drअगरt:		maximum drअगरt
 *
 * NOTE: step_size is in Hz, क्रम terrestrial/cable or kHz क्रम satellite
 */
काष्ठा dvb_frontend_tune_settings अणु
	पूर्णांक min_delay_ms;
	पूर्णांक step_size;
	पूर्णांक max_drअगरt;
पूर्ण;

काष्ठा dvb_frontend;

/**
 * काष्ठा dvb_tuner_info - Frontend name and min/max ranges/bandwidths
 *
 * @name:		name of the Frontend
 * @frequency_min_hz:	minimal frequency supported in Hz
 * @frequency_max_hz:	maximum frequency supported in Hz
 * @frequency_step_hz:	frequency step in Hz
 * @bandwidth_min:	minimal frontend bandwidth supported
 * @bandwidth_max:	maximum frontend bandwidth supported
 * @bandwidth_step:	frontend bandwidth step
 */
काष्ठा dvb_tuner_info अणु
	अक्षर name[128];

	u32 frequency_min_hz;
	u32 frequency_max_hz;
	u32 frequency_step_hz;

	u32 bandwidth_min;
	u32 bandwidth_max;
	u32 bandwidth_step;
पूर्ण;

/**
 * काष्ठा analog_parameters - Parameters to tune पूर्णांकo an analog/radio channel
 *
 * @frequency:	Frequency used by analog TV tuner (either in 62.5 kHz step,
 *		क्रम TV, or 62.5 Hz क्रम radio)
 * @mode:	Tuner mode, as defined on क्रमागत v4l2_tuner_type
 * @audmode:	Audio mode as defined क्रम the rxsubchans field at videodev2.h,
 *		e. g. V4L2_TUNER_MODE_*
 * @std:	TV standard biपंचांगap as defined at videodev2.h, e. g. V4L2_STD_*
 *
 * Hybrid tuners should be supported by both V4L2 and DVB APIs. This
 * काष्ठा contains the data that are used by the V4L2 side. To aव्योम
 * dependencies from V4L2 headers, all क्रमागतs here are declared as पूर्णांकegers.
 */
काष्ठा analog_parameters अणु
	अचिन्हित पूर्णांक frequency;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक audmode;
	u64 std;
पूर्ण;

/**
 * क्रमागत dvbfe_algo - defines the algorithm used to tune पूर्णांकo a channel
 *
 * @DVBFE_ALGO_HW: Hardware Algorithm -
 *	Devices that support this algorithm करो everything in hardware
 *	and no software support is needed to handle them.
 *	Requesting these devices to LOCK is the only thing required,
 *	device is supposed to करो everything in the hardware.
 *
 * @DVBFE_ALGO_SW: Software Algorithm -
 * These are dumb devices, that require software to करो everything
 *
 * @DVBFE_ALGO_CUSTOM: Customizable Agorithm -
 *	Devices having this algorithm can be customized to have specअगरic
 *	algorithms in the frontend driver, rather than simply करोing a
 *	software zig-zag. In this हाल the zigzag maybe hardware assisted
 *	or it maybe completely करोne in hardware. In all हालs, usage of
 *	this algorithm, in conjunction with the search and track
 *	callbacks, utilizes the driver specअगरic algorithm.
 *
 * @DVBFE_ALGO_RECOVERY: Recovery Algorithm -
 *	These devices have AUTO recovery capabilities from LOCK failure
 */
क्रमागत dvbfe_algo अणु
	DVBFE_ALGO_HW			= BIT(0),
	DVBFE_ALGO_SW			= BIT(1),
	DVBFE_ALGO_CUSTOM		= BIT(2),
	DVBFE_ALGO_RECOVERY		= BIT(31),
पूर्ण;

/**
 * क्रमागत dvbfe_search - search callback possible वापस status
 *
 * @DVBFE_ALGO_SEARCH_SUCCESS:
 *	The frontend search algorithm completed and वापसed successfully
 *
 * @DVBFE_ALGO_SEARCH_ASLEEP:
 *	The frontend search algorithm is sleeping
 *
 * @DVBFE_ALGO_SEARCH_FAILED:
 *	The frontend search क्रम a संकेत failed
 *
 * @DVBFE_ALGO_SEARCH_INVALID:
 *	The frontend search algorithm was probably supplied with invalid
 *	parameters and the search is an invalid one
 *
 * @DVBFE_ALGO_SEARCH_ERROR:
 *	The frontend search algorithm failed due to some error
 *
 * @DVBFE_ALGO_SEARCH_AGAIN:
 *	The frontend search algorithm was requested to search again
 */
क्रमागत dvbfe_search अणु
	DVBFE_ALGO_SEARCH_SUCCESS	= BIT(0),
	DVBFE_ALGO_SEARCH_ASLEEP	= BIT(1),
	DVBFE_ALGO_SEARCH_FAILED	= BIT(2),
	DVBFE_ALGO_SEARCH_INVALID	= BIT(3),
	DVBFE_ALGO_SEARCH_AGAIN		= BIT(4),
	DVBFE_ALGO_SEARCH_ERROR		= BIT(31),
पूर्ण;

/**
 * काष्ठा dvb_tuner_ops - Tuner inक्रमmation and callbacks
 *
 * @info:		embedded &काष्ठा dvb_tuner_info with tuner properties
 * @release:		callback function called when frontend is detached.
 *			drivers should मुक्त any allocated memory.
 * @init:		callback function used to initialize the tuner device.
 * @sleep:		callback function used to put the tuner to sleep.
 * @suspend:		callback function used to inक्रमm that the Kernel will
 *			suspend.
 * @resume:		callback function used to inक्रमm that the Kernel is
 *			resuming from suspend.
 * @set_params:		callback function used to inक्रमm the tuner to tune
 *			पूर्णांकo a digital TV channel. The properties to be used
 *			are stored at &काष्ठा dvb_frontend.dtv_property_cache.
 *			The tuner demod can change the parameters to reflect
 *			the changes needed क्रम the channel to be tuned, and
 *			update statistics. This is the recommended way to set
 *			the tuner parameters and should be used on newer
 *			drivers.
 * @set_analog_params:	callback function used to tune पूर्णांकo an analog TV
 *			channel on hybrid tuners. It passes @analog_parameters
 *			to the driver.
 * @set_config:		callback function used to send some tuner-specअगरic
 *			parameters.
 * @get_frequency:	get the actual tuned frequency
 * @get_bandwidth:	get the bandwidth used by the low pass filters
 * @get_अगर_frequency:	get the Intermediate Frequency, in Hz. For baseband,
 *			should वापस 0.
 * @get_status:		वापसs the frontend lock status
 * @get_rf_strength:	वापसs the RF संकेत strength. Used mostly to support
 *			analog TV and radio. Digital TV should report, instead,
 *			via DVBv5 API (&काष्ठा dvb_frontend.dtv_property_cache).
 * @get_afc:		Used only by analog TV core. Reports the frequency
 *			drअगरt due to AFC.
 * @calc_regs:		callback function used to pass रेजिस्टर data settings
 *			क्रम simple tuners.  Shouldn't be used on newer drivers.
 * @set_frequency:	Set a new frequency. Shouldn't be used on newer drivers.
 * @set_bandwidth:	Set a new frequency. Shouldn't be used on newer drivers.
 *
 * NOTE: frequencies used on @get_frequency and @set_frequency are in Hz क्रम
 * terrestrial/cable or kHz क्रम satellite.
 *
 */
काष्ठा dvb_tuner_ops अणु

	काष्ठा dvb_tuner_info info;

	व्योम (*release)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*init)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*sleep)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*suspend)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*resume)(काष्ठा dvb_frontend *fe);

	/* This is the recommended way to set the tuner */
	पूर्णांक (*set_params)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*set_analog_params)(काष्ठा dvb_frontend *fe, काष्ठा analog_parameters *p);

	पूर्णांक (*set_config)(काष्ठा dvb_frontend *fe, व्योम *priv_cfg);

	पूर्णांक (*get_frequency)(काष्ठा dvb_frontend *fe, u32 *frequency);
	पूर्णांक (*get_bandwidth)(काष्ठा dvb_frontend *fe, u32 *bandwidth);
	पूर्णांक (*get_अगर_frequency)(काष्ठा dvb_frontend *fe, u32 *frequency);

#घोषणा TUNER_STATUS_LOCKED 1
#घोषणा TUNER_STATUS_STEREO 2
	पूर्णांक (*get_status)(काष्ठा dvb_frontend *fe, u32 *status);
	पूर्णांक (*get_rf_strength)(काष्ठा dvb_frontend *fe, u16 *strength);
	पूर्णांक (*get_afc)(काष्ठा dvb_frontend *fe, s32 *afc);

	/*
	 * This is support क्रम demods like the mt352 - fills out the supplied
	 * buffer with what to ग_लिखो.
	 *
	 * Don't use on newer drivers.
	 */
	पूर्णांक (*calc_regs)(काष्ठा dvb_frontend *fe, u8 *buf, पूर्णांक buf_len);

	/*
	 * These are provided separately from set_params in order to
	 * facilitate silicon tuners which require sophisticated tuning loops,
	 * controlling each parameter separately.
	 *
	 * Don't use on newer drivers.
	 */
	पूर्णांक (*set_frequency)(काष्ठा dvb_frontend *fe, u32 frequency);
	पूर्णांक (*set_bandwidth)(काष्ठा dvb_frontend *fe, u32 bandwidth);
पूर्ण;

/**
 * काष्ठा analog_demod_info - Inक्रमmation काष्ठा क्रम analog TV part of the demod
 *
 * @name:	Name of the analog TV demodulator
 */
काष्ठा analog_demod_info अणु
	अक्षर *name;
पूर्ण;

/**
 * काष्ठा analog_demod_ops  - Demodulation inक्रमmation and callbacks क्रम
 *			      analog TV and radio
 *
 * @info:		poपूर्णांकer to काष्ठा analog_demod_info
 * @set_params:		callback function used to inक्रमm the demod to set the
 *			demodulator parameters needed to decode an analog or
 *			radio channel. The properties are passed via
 *			&काष्ठा analog_params.
 * @has_संकेत:		वापसs 0xffff अगर has संकेत, or 0 अगर it करोesn't.
 * @get_afc:		Used only by analog TV core. Reports the frequency
 *			drअगरt due to AFC.
 * @tuner_status:	callback function that वापसs tuner status bits, e. g.
 *			%TUNER_STATUS_LOCKED and %TUNER_STATUS_STEREO.
 * @standby:		set the tuner to standby mode.
 * @release:		callback function called when frontend is detached.
 *			drivers should मुक्त any allocated memory.
 * @i2c_gate_ctrl:	controls the I2C gate. Newer drivers should use I2C
 *			mux support instead.
 * @set_config:		callback function used to send some tuner-specअगरic
 *			parameters.
 */
काष्ठा analog_demod_ops अणु

	काष्ठा analog_demod_info info;

	व्योम (*set_params)(काष्ठा dvb_frontend *fe,
			   काष्ठा analog_parameters *params);
	पूर्णांक  (*has_संकेत)(काष्ठा dvb_frontend *fe, u16 *संकेत);
	पूर्णांक  (*get_afc)(काष्ठा dvb_frontend *fe, s32 *afc);
	व्योम (*tuner_status)(काष्ठा dvb_frontend *fe);
	व्योम (*standby)(काष्ठा dvb_frontend *fe);
	व्योम (*release)(काष्ठा dvb_frontend *fe);
	पूर्णांक  (*i2c_gate_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक enable);

	/** This is to allow setting tuner-specअगरic configuration */
	पूर्णांक (*set_config)(काष्ठा dvb_frontend *fe, व्योम *priv_cfg);
पूर्ण;

काष्ठा dtv_frontend_properties;

/**
 * काष्ठा dvb_frontend_पूर्णांकernal_info - Frontend properties and capabilities
 *
 * @name:			Name of the frontend
 * @frequency_min_hz:		Minimal frequency supported by the frontend.
 * @frequency_max_hz:		Minimal frequency supported by the frontend.
 * @frequency_stepsize_hz:	All frequencies are multiple of this value.
 * @frequency_tolerance_hz:	Frequency tolerance.
 * @symbol_rate_min:		Minimal symbol rate, in bauds
 *				(क्रम Cable/Satellite प्रणालीs).
 * @symbol_rate_max:		Maximal symbol rate, in bauds
 *				(क्रम Cable/Satellite प्रणालीs).
 * @symbol_rate_tolerance:	Maximal symbol rate tolerance, in ppm
 *				(क्रम Cable/Satellite प्रणालीs).
 * @caps:			Capabilities supported by the frontend,
 *				as specअगरied in &क्रमागत fe_caps.
 */
काष्ठा dvb_frontend_पूर्णांकernal_info अणु
	अक्षर	name[128];
	u32	frequency_min_hz;
	u32	frequency_max_hz;
	u32	frequency_stepsize_hz;
	u32	frequency_tolerance_hz;
	u32	symbol_rate_min;
	u32	symbol_rate_max;
	u32	symbol_rate_tolerance;
	क्रमागत fe_caps caps;
पूर्ण;

/**
 * काष्ठा dvb_frontend_ops - Demodulation inक्रमmation and callbacks क्रम
 *			      ditialt TV
 *
 * @info:		embedded &काष्ठा dvb_tuner_info with tuner properties
 * @delsys:		Delivery प्रणालीs supported by the frontend
 * @detach:		callback function called when frontend is detached.
 *			drivers should clean up, but not yet मुक्त the &काष्ठा
 *			dvb_frontend allocation.
 * @release:		callback function called when frontend is पढ़ोy to be
 *			मुक्तd.
 *			drivers should मुक्त any allocated memory.
 * @release_sec:	callback function requesting that the Satellite Equipment
 *			Control (SEC) driver to release and मुक्त any memory
 *			allocated by the driver.
 * @init:		callback function used to initialize the tuner device.
 * @sleep:		callback function used to put the tuner to sleep.
 * @ग_लिखो:		callback function used by some demod legacy drivers to
 *			allow other drivers to ग_लिखो data पूर्णांकo their रेजिस्टरs.
 *			Should not be used on new drivers.
 * @tune:		callback function used by demod drivers that use
 *			@DVBFE_ALGO_HW to tune पूर्णांकo a frequency.
 * @get_frontend_algo:	वापसs the desired hardware algorithm.
 * @set_frontend:	callback function used to inक्रमm the demod to set the
 *			parameters क्रम demodulating a digital TV channel.
 *			The properties to be used are stored at &काष्ठा
 *			dvb_frontend.dtv_property_cache. The demod can change
 *			the parameters to reflect the changes needed क्रम the
 *			channel to be decoded, and update statistics.
 * @get_tune_settings:	callback function
 * @get_frontend:	callback function used to inक्रमm the parameters
 *			actuall in use. The properties to be used are stored at
 *			&काष्ठा dvb_frontend.dtv_property_cache and update
 *			statistics. Please notice that it should not वापस
 *			an error code अगर the statistics are not available
 *			because the demog is not locked.
 * @पढ़ो_status:	वापसs the locking status of the frontend.
 * @पढ़ो_ber:		legacy callback function to वापस the bit error rate.
 *			Newer drivers should provide such info via DVBv5 API,
 *			e. g. @set_frontend;/@get_frontend, implementing this
 *			callback only अगर DVBv3 API compatibility is wanted.
 * @पढ़ो_संकेत_strength: legacy callback function to वापस the संकेत
 *			strength. Newer drivers should provide such info via
 *			DVBv5 API, e. g. @set_frontend/@get_frontend,
 *			implementing this callback only अगर DVBv3 API
 *			compatibility is wanted.
 * @पढ़ो_snr:		legacy callback function to वापस the Signal/Noise
 *			rate. Newer drivers should provide such info via
 *			DVBv5 API, e. g. @set_frontend/@get_frontend,
 *			implementing this callback only अगर DVBv3 API
 *			compatibility is wanted.
 * @पढ़ो_ucblocks:	legacy callback function to वापस the Uncorrected Error
 *			Blocks. Newer drivers should provide such info via
 *			DVBv5 API, e. g. @set_frontend/@get_frontend,
 *			implementing this callback only अगर DVBv3 API
 *			compatibility is wanted.
 * @diseqc_reset_overload: callback function to implement the
 *			FE_DISEQC_RESET_OVERLOAD() ioctl (only Satellite)
 * @diseqc_send_master_cmd: callback function to implement the
 *			FE_DISEQC_SEND_MASTER_CMD() ioctl (only Satellite).
 * @diseqc_recv_slave_reply: callback function to implement the
 *			FE_DISEQC_RECV_SLAVE_REPLY() ioctl (only Satellite)
 * @diseqc_send_burst:	callback function to implement the
 *			FE_DISEQC_SEND_BURST() ioctl (only Satellite).
 * @set_tone:		callback function to implement the
 *			FE_SET_TONE() ioctl (only Satellite).
 * @set_voltage:	callback function to implement the
 *			FE_SET_VOLTAGE() ioctl (only Satellite).
 * @enable_high_lnb_voltage: callback function to implement the
 *			FE_ENABLE_HIGH_LNB_VOLTAGE() ioctl (only Satellite).
 * @dishnetwork_send_legacy_command: callback function to implement the
 *			FE_DISHNETWORK_SEND_LEGACY_CMD() ioctl (only Satellite).
 *			Drivers should not use this, except when the DVB
 *			core emulation fails to provide proper support (e.g.
 *			अगर @set_voltage takes more than 8ms to work), and
 *			when backward compatibility with this legacy API is
 *			required.
 * @i2c_gate_ctrl:	controls the I2C gate. Newer drivers should use I2C
 *			mux support instead.
 * @ts_bus_ctrl:	callback function used to take control of the TS bus.
 * @set_lna:		callback function to घातer on/off/स्वतः the LNA.
 * @search:		callback function used on some custom algo search algos.
 * @tuner_ops:		poपूर्णांकer to &काष्ठा dvb_tuner_ops
 * @analog_ops:		poपूर्णांकer to &काष्ठा analog_demod_ops
 */
काष्ठा dvb_frontend_ops अणु
	काष्ठा dvb_frontend_पूर्णांकernal_info info;

	u8 delsys[MAX_DELSYS];

	व्योम (*detach)(काष्ठा dvb_frontend *fe);
	व्योम (*release)(काष्ठा dvb_frontend* fe);
	व्योम (*release_sec)(काष्ठा dvb_frontend* fe);

	पूर्णांक (*init)(काष्ठा dvb_frontend* fe);
	पूर्णांक (*sleep)(काष्ठा dvb_frontend* fe);

	पूर्णांक (*ग_लिखो)(काष्ठा dvb_frontend* fe, स्थिर u8 buf[], पूर्णांक len);

	/* अगर this is set, it overrides the शेष swzigzag */
	पूर्णांक (*tune)(काष्ठा dvb_frontend* fe,
		    bool re_tune,
		    अचिन्हित पूर्णांक mode_flags,
		    अचिन्हित पूर्णांक *delay,
		    क्रमागत fe_status *status);

	/* get frontend tuning algorithm from the module */
	क्रमागत dvbfe_algo (*get_frontend_algo)(काष्ठा dvb_frontend *fe);

	/* these two are only used क्रम the swzigzag code */
	पूर्णांक (*set_frontend)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*get_tune_settings)(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* settings);

	पूर्णांक (*get_frontend)(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *props);

	पूर्णांक (*पढ़ो_status)(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);
	पूर्णांक (*पढ़ो_ber)(काष्ठा dvb_frontend* fe, u32* ber);
	पूर्णांक (*पढ़ो_संकेत_strength)(काष्ठा dvb_frontend* fe, u16* strength);
	पूर्णांक (*पढ़ो_snr)(काष्ठा dvb_frontend* fe, u16* snr);
	पूर्णांक (*पढ़ो_ucblocks)(काष्ठा dvb_frontend* fe, u32* ucblocks);

	पूर्णांक (*diseqc_reset_overload)(काष्ठा dvb_frontend* fe);
	पूर्णांक (*diseqc_send_master_cmd)(काष्ठा dvb_frontend* fe, काष्ठा dvb_diseqc_master_cmd* cmd);
	पूर्णांक (*diseqc_recv_slave_reply)(काष्ठा dvb_frontend* fe, काष्ठा dvb_diseqc_slave_reply* reply);
	पूर्णांक (*diseqc_send_burst)(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_sec_mini_cmd minicmd);
	पूर्णांक (*set_tone)(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone);
	पूर्णांक (*set_voltage)(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*enable_high_lnb_voltage)(काष्ठा dvb_frontend* fe, दीर्घ arg);
	पूर्णांक (*dishnetwork_send_legacy_command)(काष्ठा dvb_frontend* fe, अचिन्हित दीर्घ cmd);
	पूर्णांक (*i2c_gate_ctrl)(काष्ठा dvb_frontend* fe, पूर्णांक enable);
	पूर्णांक (*ts_bus_ctrl)(काष्ठा dvb_frontend* fe, पूर्णांक acquire);
	पूर्णांक (*set_lna)(काष्ठा dvb_frontend *);

	/*
	 * These callbacks are क्रम devices that implement their own
	 * tuning algorithms, rather than a simple swzigzag
	 */
	क्रमागत dvbfe_search (*search)(काष्ठा dvb_frontend *fe);

	काष्ठा dvb_tuner_ops tuner_ops;
	काष्ठा analog_demod_ops analog_ops;
पूर्ण;

#अगर_घोषित __DVB_CORE__
#घोषणा MAX_EVENT 8

/* Used only पूर्णांकernally at dvb_frontend.c */
काष्ठा dvb_fe_events अणु
	काष्ठा dvb_frontend_event events[MAX_EVENT];
	पूर्णांक			  eventw;
	पूर्णांक			  eventr;
	पूर्णांक			  overflow;
	रुको_queue_head_t	  रुको_queue;
	काष्ठा mutex		  mtx;
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा dtv_frontend_properties - contains a list of properties that are
 *				    specअगरic to a digital TV standard.
 *
 * @frequency:		frequency in Hz क्रम terrestrial/cable or in kHz क्रम
 *			Satellite
 * @modulation:		Frontend modulation type
 * @voltage:		SEC voltage (only Satellite)
 * @sectone:		SEC tone mode (only Satellite)
 * @inversion:		Spectral inversion
 * @fec_inner:		Forward error correction inner Code Rate
 * @transmission_mode:	Transmission Mode
 * @bandwidth_hz:	Bandwidth, in Hz. A zero value means that userspace
 *			wants to स्वतःdetect.
 * @guard_पूर्णांकerval:	Guard Interval
 * @hierarchy:		Hierarchy
 * @symbol_rate:	Symbol Rate
 * @code_rate_HP:	high priority stream code rate
 * @code_rate_LP:	low priority stream code rate
 * @pilot:		Enable/disable/स्वतःdetect pilot tones
 * @rolloff:		Rolloff factor (alpha)
 * @delivery_प्रणाली:	FE delivery प्रणाली (e. g. digital TV standard)
 * @पूर्णांकerleaving:	पूर्णांकerleaving
 * @isdbt_partial_reception: ISDB-T partial reception (only ISDB standard)
 * @isdbt_sb_mode:	ISDB-T Sound Broadcast (SB) mode (only ISDB standard)
 * @isdbt_sb_subchannel:	ISDB-T SB subchannel (only ISDB standard)
 * @isdbt_sb_segment_idx:	ISDB-T SB segment index (only ISDB standard)
 * @isdbt_sb_segment_count:	ISDB-T SB segment count (only ISDB standard)
 * @isdbt_layer_enabled:	ISDB Layer enabled (only ISDB standard)
 * @layer:		ISDB per-layer data (only ISDB standard)
 * @layer.segment_count: Segment Count;
 * @layer.fec:		per layer code rate;
 * @layer.modulation:	per layer modulation;
 * @layer.पूर्णांकerleaving:	 per layer पूर्णांकerleaving.
 * @stream_id:		If dअगरferent than zero, enable substream filtering, अगर
 *			hardware supports (DVB-S2 and DVB-T2).
 * @scrambling_sequence_index:	Carries the index of the DVB-S2 physical layer
 *				scrambling sequence.
 * @atscmh_fic_ver:	Version number of the FIC (Fast Inक्रमmation Channel)
 *			संकेतing data (only ATSC-M/H)
 * @atscmh_parade_id:	Parade identअगरication number (only ATSC-M/H)
 * @atscmh_nog:		Number of MH groups per MH subframe क्रम a designated
 *			parade (only ATSC-M/H)
 * @atscmh_tnog:	Total number of MH groups including all MH groups
 *			beदीर्घing to all MH parades in one MH subframe
 *			(only ATSC-M/H)
 * @atscmh_sgn:		Start group number (only ATSC-M/H)
 * @atscmh_prc:		Parade repetition cycle (only ATSC-M/H)
 * @atscmh_rs_frame_mode:	Reed Solomon (RS) frame mode (only ATSC-M/H)
 * @atscmh_rs_frame_ensemble:	RS frame ensemble (only ATSC-M/H)
 * @atscmh_rs_code_mode_pri:	RS code mode pri (only ATSC-M/H)
 * @atscmh_rs_code_mode_sec:	RS code mode sec (only ATSC-M/H)
 * @atscmh_sccc_block_mode:	Series Concatenated Convolutional Code (SCCC)
 *				Block Mode (only ATSC-M/H)
 * @atscmh_sccc_code_mode_a:	SCCC code mode A (only ATSC-M/H)
 * @atscmh_sccc_code_mode_b:	SCCC code mode B (only ATSC-M/H)
 * @atscmh_sccc_code_mode_c:	SCCC code mode C (only ATSC-M/H)
 * @atscmh_sccc_code_mode_d:	SCCC code mode D (only ATSC-M/H)
 * @lna:		Power ON/OFF/AUTO the Linear Now-noise Amplअगरier (LNA)
 * @strength:		DVBv5 API statistics: Signal Strength
 * @cnr:		DVBv5 API statistics: Signal to Noise ratio of the
 *			(मुख्य) carrier
 * @pre_bit_error:	DVBv5 API statistics: pre-Viterbi bit error count
 * @pre_bit_count:	DVBv5 API statistics: pre-Viterbi bit count
 * @post_bit_error:	DVBv5 API statistics: post-Viterbi bit error count
 * @post_bit_count:	DVBv5 API statistics: post-Viterbi bit count
 * @block_error:	DVBv5 API statistics: block error count
 * @block_count:	DVBv5 API statistics: block count
 *
 * NOTE: derivated statistics like Uncorrected Error blocks (UCE) are
 * calculated on userspace.
 *
 * Only a subset of the properties are needed क्रम a given delivery प्रणाली.
 * For more info, consult the media_api.hपंचांगl with the करोcumentation of the
 * Userspace API.
 */
काष्ठा dtv_frontend_properties अणु
	u32			frequency;
	क्रमागत fe_modulation	modulation;

	क्रमागत fe_sec_voltage	voltage;
	क्रमागत fe_sec_tone_mode	sectone;
	क्रमागत fe_spectral_inversion inversion;
	क्रमागत fe_code_rate	fec_inner;
	क्रमागत fe_transmit_mode	transmission_mode;
	u32			bandwidth_hz;	/* 0 = AUTO */
	क्रमागत fe_guard_पूर्णांकerval	guard_पूर्णांकerval;
	क्रमागत fe_hierarchy	hierarchy;
	u32			symbol_rate;
	क्रमागत fe_code_rate	code_rate_HP;
	क्रमागत fe_code_rate	code_rate_LP;

	क्रमागत fe_pilot		pilot;
	क्रमागत fe_rolloff		rolloff;

	क्रमागत fe_delivery_प्रणाली	delivery_प्रणाली;

	क्रमागत fe_पूर्णांकerleaving	पूर्णांकerleaving;

	/* ISDB-T specअगरics */
	u8			isdbt_partial_reception;
	u8			isdbt_sb_mode;
	u8			isdbt_sb_subchannel;
	u32			isdbt_sb_segment_idx;
	u32			isdbt_sb_segment_count;
	u8			isdbt_layer_enabled;
	काष्ठा अणु
	    u8			segment_count;
	    क्रमागत fe_code_rate	fec;
	    क्रमागत fe_modulation	modulation;
	    u8			पूर्णांकerleaving;
	पूर्ण layer[3];

	/* Multistream specअगरics */
	u32			stream_id;

	/* Physical Layer Scrambling specअगरics */
	u32			scrambling_sequence_index;

	/* ATSC-MH specअगरics */
	u8			atscmh_fic_ver;
	u8			atscmh_parade_id;
	u8			atscmh_nog;
	u8			atscmh_tnog;
	u8			atscmh_sgn;
	u8			atscmh_prc;

	u8			atscmh_rs_frame_mode;
	u8			atscmh_rs_frame_ensemble;
	u8			atscmh_rs_code_mode_pri;
	u8			atscmh_rs_code_mode_sec;
	u8			atscmh_sccc_block_mode;
	u8			atscmh_sccc_code_mode_a;
	u8			atscmh_sccc_code_mode_b;
	u8			atscmh_sccc_code_mode_c;
	u8			atscmh_sccc_code_mode_d;

	u32			lna;

	/* statistics data */
	काष्ठा dtv_fe_stats	strength;
	काष्ठा dtv_fe_stats	cnr;
	काष्ठा dtv_fe_stats	pre_bit_error;
	काष्ठा dtv_fe_stats	pre_bit_count;
	काष्ठा dtv_fe_stats	post_bit_error;
	काष्ठा dtv_fe_stats	post_bit_count;
	काष्ठा dtv_fe_stats	block_error;
	काष्ठा dtv_fe_stats	block_count;
पूर्ण;

#घोषणा DVB_FE_NO_EXIT  0
#घोषणा DVB_FE_NORMAL_EXIT      1
#घोषणा DVB_FE_DEVICE_REMOVED   2
#घोषणा DVB_FE_DEVICE_RESUME    3

/**
 * काष्ठा dvb_frontend - Frontend काष्ठाure to be used on drivers.
 *
 * @refcount:		refcount to keep track of &काष्ठा dvb_frontend
 *			references
 * @ops:		embedded &काष्ठा dvb_frontend_ops
 * @dvb:		poपूर्णांकer to &काष्ठा dvb_adapter
 * @demodulator_priv:	demod निजी data
 * @tuner_priv:		tuner निजी data
 * @frontend_priv:	frontend निजी data
 * @sec_priv:		SEC निजी data
 * @analog_demod_priv:	Analog demod निजी data
 * @dtv_property_cache:	embedded &काष्ठा dtv_frontend_properties
 * @callback:		callback function used on some drivers to call
 *			either the tuner or the demodulator.
 * @id:			Frontend ID
 * @निकास:		Used to inक्रमm the DVB core that the frontend
 *			thपढ़ो should निकास (usually, means that the hardware
 *			got disconnected.
 */

काष्ठा dvb_frontend अणु
	काष्ठा kref refcount;
	काष्ठा dvb_frontend_ops ops;
	काष्ठा dvb_adapter *dvb;
	व्योम *demodulator_priv;
	व्योम *tuner_priv;
	व्योम *frontend_priv;
	व्योम *sec_priv;
	व्योम *analog_demod_priv;
	काष्ठा dtv_frontend_properties dtv_property_cache;
#घोषणा DVB_FRONTEND_COMPONENT_TUNER 0
#घोषणा DVB_FRONTEND_COMPONENT_DEMOD 1
	पूर्णांक (*callback)(व्योम *adapter_priv, पूर्णांक component, पूर्णांक cmd, पूर्णांक arg);
	पूर्णांक id;
	अचिन्हित पूर्णांक निकास;
पूर्ण;

/**
 * dvb_रेजिस्टर_frontend() - Registers a DVB frontend at the adapter
 *
 * @dvb: poपूर्णांकer to &काष्ठा dvb_adapter
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * Allocate and initialize the निजी data needed by the frontend core to
 * manage the frontend and calls dvb_रेजिस्टर_device() to रेजिस्टर a new
 * frontend. It also cleans the property cache that stores the frontend
 * parameters and selects the first available delivery प्रणाली.
 */
पूर्णांक dvb_रेजिस्टर_frontend(काष्ठा dvb_adapter *dvb,
				 काष्ठा dvb_frontend *fe);

/**
 * dvb_unरेजिस्टर_frontend() - Unरेजिस्टरs a DVB frontend
 *
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * Stops the frontend kthपढ़ो, calls dvb_unरेजिस्टर_device() and मुक्तs the
 * निजी frontend data allocated by dvb_रेजिस्टर_frontend().
 *
 * NOTE: This function करोesn't मुक्तs the memory allocated by the demod,
 * by the SEC driver and by the tuner. In order to मुक्त it, an explicit call to
 * dvb_frontend_detach() is needed, after calling this function.
 */
पूर्णांक dvb_unरेजिस्टर_frontend(काष्ठा dvb_frontend *fe);

/**
 * dvb_frontend_detach() - Detaches and मुक्तs frontend specअगरic data
 *
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * This function should be called after dvb_unरेजिस्टर_frontend(). It
 * calls the SEC, tuner and demod release functions:
 * &dvb_frontend_ops.release_sec, &dvb_frontend_ops.tuner_ops.release,
 * &dvb_frontend_ops.analog_ops.release and &dvb_frontend_ops.release.
 *
 * If the driver is compiled with %CONFIG_MEDIA_ATTACH, it also decreases
 * the module reference count, needed to allow userspace to हटाओ the
 * previously used DVB frontend modules.
 */
व्योम dvb_frontend_detach(काष्ठा dvb_frontend *fe);

/**
 * dvb_frontend_suspend() - Suspends a Digital TV frontend
 *
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * This function prepares a Digital TV frontend to suspend.
 *
 * In order to prepare the tuner to suspend, अगर
 * &dvb_frontend_ops.tuner_ops.suspend\(\) is available, it calls it. Otherwise,
 * it will call &dvb_frontend_ops.tuner_ops.sleep\(\), अगर available.
 *
 * It will also call &dvb_frontend_ops.sleep\(\) to put the demod to suspend.
 *
 * The drivers should also call dvb_frontend_suspend\(\) as part of their
 * handler क्रम the &device_driver.suspend\(\).
 */
पूर्णांक dvb_frontend_suspend(काष्ठा dvb_frontend *fe);

/**
 * dvb_frontend_resume() - Resumes a Digital TV frontend
 *
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * This function resumes the usual operation of the tuner after resume.
 *
 * In order to resume the frontend, it calls the demod &dvb_frontend_ops.init\(\).
 *
 * If &dvb_frontend_ops.tuner_ops.resume\(\) is available, It, it calls it.
 * Otherwise,t will call &dvb_frontend_ops.tuner_ops.init\(\), अगर available.
 *
 * Once tuner and demods are resumed, it will enक्रमce that the SEC voltage and
 * tone are restored to their previous values and wake up the frontend's
 * kthपढ़ो in order to retune the frontend.
 *
 * The drivers should also call dvb_frontend_resume() as part of their
 * handler क्रम the &device_driver.resume\(\).
 */
पूर्णांक dvb_frontend_resume(काष्ठा dvb_frontend *fe);

/**
 * dvb_frontend_reinitialise() - क्रमces a reinitialisation at the frontend
 *
 * @fe: poपूर्णांकer to &काष्ठा dvb_frontend
 *
 * Calls &dvb_frontend_ops.init\(\) and &dvb_frontend_ops.tuner_ops.init\(\),
 * and resets SEC tone and voltage (क्रम Satellite प्रणालीs).
 *
 * NOTE: Currently, this function is used only by one driver (budget-av).
 * It seems to be due to address some special issue with that specअगरic
 * frontend.
 */
व्योम dvb_frontend_reinitialise(काष्ठा dvb_frontend *fe);

/**
 * dvb_frontend_sleep_until() - Sleep क्रम the amount of समय given by
 *                      add_usec parameter
 *
 * @wakeसमय: poपूर्णांकer to &काष्ठा kसमय_प्रकार
 * @add_usec: समय to sleep, in microseconds
 *
 * This function is used to measure the समय required क्रम the
 * FE_DISHNETWORK_SEND_LEGACY_CMD() ioctl to work. It needs to be as precise
 * as possible, as it affects the detection of the dish tone command at the
 * satellite subप्रणाली.
 *
 * Its used पूर्णांकernally by the DVB frontend core, in order to emulate
 * FE_DISHNETWORK_SEND_LEGACY_CMD() using the &dvb_frontend_ops.set_voltage\(\)
 * callback.
 *
 * NOTE: it should not be used at the drivers, as the emulation क्रम the
 * legacy callback is provided by the Kernel. The only situation where this
 * should be at the drivers is when there are some bugs at the hardware that
 * would prevent the core emulation to work. On such हालs, the driver would
 * be writing a &dvb_frontend_ops.dishnetwork_send_legacy_command\(\) and
 * calling this function directly.
 */
व्योम dvb_frontend_sleep_until(kसमय_प्रकार *wakeसमय, u32 add_usec);

#पूर्ण_अगर
