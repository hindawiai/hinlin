<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.0+ */
/*
 * comedi.h
 * header file क्रम COMEDI user API
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998-2001 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDI_H
#घोषणा _COMEDI_H

#घोषणा COMEDI_MAJORVERSION	0
#घोषणा COMEDI_MINORVERSION	7
#घोषणा COMEDI_MICROVERSION	76
#घोषणा VERSION	"0.7.76"

/* comedi's major device number */
#घोषणा COMEDI_MAJOR 98

/*
 * maximum number of minor devices.  This can be increased, although
 * kernel काष्ठाures are currently अटलally allocated, thus you
 * करोn't want this to be much more than you actually use.
 */
#घोषणा COMEDI_NDEVICES 16

/* number of config options in the config काष्ठाure */
#घोषणा COMEDI_NDEVCONFOPTS 32

/*
 * NOTE: 'comedi_config --init-data' is deprecated
 *
 * The following indexes in the config options were used by
 * comedi_config to pass firmware blobs from user space to the
 * comedi drivers. The request_firmware() hotplug पूर्णांकerface is
 * now used by all comedi drivers instead.
 */

/* length of nth chunk of firmware data -*/
#घोषणा COMEDI_DEVCONF_AUX_DATA3_LENGTH		25
#घोषणा COMEDI_DEVCONF_AUX_DATA2_LENGTH		26
#घोषणा COMEDI_DEVCONF_AUX_DATA1_LENGTH		27
#घोषणा COMEDI_DEVCONF_AUX_DATA0_LENGTH		28
/* most signअगरicant 32 bits of poपूर्णांकer address (अगर needed) */
#घोषणा COMEDI_DEVCONF_AUX_DATA_HI		29
/* least signअगरicant 32 bits of poपूर्णांकer address */
#घोषणा COMEDI_DEVCONF_AUX_DATA_LO		30
#घोषणा COMEDI_DEVCONF_AUX_DATA_LENGTH		31	/* total data length */

/* max length of device and driver names */
#घोषणा COMEDI_NAMELEN 20

/* packs and unpacks a channel/range number */

#घोषणा CR_PACK(chan, rng, aref)					\
	((((aref) & 0x3) << 24) | (((rng) & 0xff) << 16) | (chan))
#घोषणा CR_PACK_FLAGS(chan, range, aref, flags)				\
	(CR_PACK(chan, range, aref) | ((flags) & CR_FLAGS_MASK))

#घोषणा CR_CHAN(a)	((a) & 0xffff)
#घोषणा CR_RANGE(a)	(((a) >> 16) & 0xff)
#घोषणा CR_AREF(a)	(((a) >> 24) & 0x03)

#घोषणा CR_FLAGS_MASK	0xfc000000
#घोषणा CR_ALT_FILTER	0x04000000
#घोषणा CR_DITHER	CR_ALT_FILTER
#घोषणा CR_DEGLITCH	CR_ALT_FILTER
#घोषणा CR_ALT_SOURCE	0x08000000
#घोषणा CR_EDGE		0x40000000
#घोषणा CR_INVERT	0x80000000

#घोषणा AREF_GROUND	0x00	/* analog ref = analog ground */
#घोषणा AREF_COMMON	0x01	/* analog ref = analog common */
#घोषणा AREF_DIFF	0x02	/* analog ref = dअगरferential */
#घोषणा AREF_OTHER	0x03	/* analog ref = other (undefined) */

/* counters -- these are arbitrary values */
#घोषणा GPCT_RESET		0x0001
#घोषणा GPCT_SET_SOURCE		0x0002
#घोषणा GPCT_SET_GATE		0x0004
#घोषणा GPCT_SET_सूचीECTION	0x0008
#घोषणा GPCT_SET_OPERATION	0x0010
#घोषणा GPCT_ARM		0x0020
#घोषणा GPCT_DISARM		0x0040
#घोषणा GPCT_GET_INT_CLK_FRQ	0x0080

#घोषणा GPCT_INT_CLOCK		0x0001
#घोषणा GPCT_EXT_PIN		0x0002
#घोषणा GPCT_NO_GATE		0x0004
#घोषणा GPCT_UP			0x0008
#घोषणा GPCT_DOWN		0x0010
#घोषणा GPCT_HWUD		0x0020
#घोषणा GPCT_SIMPLE_EVENT	0x0040
#घोषणा GPCT_SINGLE_PERIOD	0x0080
#घोषणा GPCT_SINGLE_PW		0x0100
#घोषणा GPCT_CONT_PULSE_OUT	0x0200
#घोषणा GPCT_SINGLE_PULSE_OUT	0x0400

/* inकाष्ठाions */

#घोषणा INSN_MASK_WRITE		0x8000000
#घोषणा INSN_MASK_READ		0x4000000
#घोषणा INSN_MASK_SPECIAL	0x2000000

#घोषणा INSN_READ		(0 | INSN_MASK_READ)
#घोषणा INSN_WRITE		(1 | INSN_MASK_WRITE)
#घोषणा INSN_BITS		(2 | INSN_MASK_READ | INSN_MASK_WRITE)
#घोषणा INSN_CONFIG		(3 | INSN_MASK_READ | INSN_MASK_WRITE)
#घोषणा INSN_DEVICE_CONFIG	(INSN_CONFIG | INSN_MASK_SPECIAL)
#घोषणा INSN_GTOD		(4 | INSN_MASK_READ | INSN_MASK_SPECIAL)
#घोषणा INSN_WAIT		(5 | INSN_MASK_WRITE | INSN_MASK_SPECIAL)
#घोषणा INSN_INTTRIG		(6 | INSN_MASK_WRITE | INSN_MASK_SPECIAL)

/* command flags */
/* These flags are used in comedi_cmd काष्ठाures */

#घोषणा CMDF_BOGUS		0x00000001	/* करो the motions */

/* try to use a real-समय पूर्णांकerrupt जबतक perक्रमming command */
#घोषणा CMDF_PRIORITY		0x00000008

/* wake up on end-of-scan events */
#घोषणा CMDF_WAKE_EOS		0x00000020

#घोषणा CMDF_WRITE		0x00000040

#घोषणा CMDF_RAWDATA		0x00000080

/* समयr rounding definitions */
#घोषणा CMDF_ROUND_MASK		0x00030000
#घोषणा CMDF_ROUND_NEAREST	0x00000000
#घोषणा CMDF_ROUND_DOWN		0x00010000
#घोषणा CMDF_ROUND_UP		0x00020000
#घोषणा CMDF_ROUND_UP_NEXT	0x00030000

#घोषणा COMEDI_EV_START		0x00040000
#घोषणा COMEDI_EV_SCAN_BEGIN	0x00080000
#घोषणा COMEDI_EV_CONVERT	0x00100000
#घोषणा COMEDI_EV_SCAN_END	0x00200000
#घोषणा COMEDI_EV_STOP		0x00400000

/* compatibility definitions */
#घोषणा TRIG_BOGUS		CMDF_BOGUS
#घोषणा TRIG_RT			CMDF_PRIORITY
#घोषणा TRIG_WAKE_EOS		CMDF_WAKE_EOS
#घोषणा TRIG_WRITE		CMDF_WRITE
#घोषणा TRIG_ROUND_MASK		CMDF_ROUND_MASK
#घोषणा TRIG_ROUND_NEAREST	CMDF_ROUND_NEAREST
#घोषणा TRIG_ROUND_DOWN		CMDF_ROUND_DOWN
#घोषणा TRIG_ROUND_UP		CMDF_ROUND_UP
#घोषणा TRIG_ROUND_UP_NEXT	CMDF_ROUND_UP_NEXT

/* trigger sources */

#घोषणा TRIG_ANY	0xffffffff
#घोषणा TRIG_INVALID	0x00000000

#घोषणा TRIG_NONE	0x00000001 /* never trigger */
#घोषणा TRIG_NOW	0x00000002 /* trigger now + N ns */
#घोषणा TRIG_FOLLOW	0x00000004 /* trigger on next lower level trig */
#घोषणा TRIG_TIME	0x00000008 /* trigger at समय N ns */
#घोषणा TRIG_TIMER	0x00000010 /* trigger at rate N ns */
#घोषणा TRIG_COUNT	0x00000020 /* trigger when count reaches N */
#घोषणा TRIG_EXT	0x00000040 /* trigger on बाह्यal संकेत N */
#घोषणा TRIG_INT	0x00000080 /* trigger on comedi-पूर्णांकernal संकेत N */
#घोषणा TRIG_OTHER	0x00000100 /* driver defined */

/* subdevice flags */

#घोषणा SDF_BUSY	0x0001	/* device is busy */
#घोषणा SDF_BUSY_OWNER	0x0002	/* device is busy with your job */
#घोषणा SDF_LOCKED	0x0004	/* subdevice is locked */
#घोषणा SDF_LOCK_OWNER	0x0008	/* you own lock */
#घोषणा SDF_MAXDATA	0x0010	/* maxdata depends on channel */
#घोषणा SDF_FLAGS	0x0020	/* flags depend on channel */
#घोषणा SDF_RANGETYPE	0x0040	/* range type depends on channel */
#घोषणा SDF_PWM_COUNTER 0x0080	/* PWM can स्वतःmatically चयन off */
#घोषणा SDF_PWM_HBRIDGE 0x0100	/* PWM is चिन्हित (H-bridge) */
#घोषणा SDF_CMD		0x1000	/* can करो commands (deprecated) */
#घोषणा SDF_SOFT_CALIBRATED	0x2000 /* subdevice uses software calibration */
#घोषणा SDF_CMD_WRITE		0x4000 /* can करो output commands */
#घोषणा SDF_CMD_READ		0x8000 /* can करो input commands */

/* subdevice can be पढ़ो (e.g. analog input) */
#घोषणा SDF_READABLE	0x00010000
/* subdevice can be written (e.g. analog output) */
#घोषणा SDF_WRITABLE	0x00020000
#घोषणा SDF_WRITEABLE	SDF_WRITABLE	/* spelling error in API */
/* subdevice करोes not have बाह्यally visible lines */
#घोषणा SDF_INTERNAL	0x00040000
#घोषणा SDF_GROUND	0x00100000	/* can करो aref=ground */
#घोषणा SDF_COMMON	0x00200000	/* can करो aref=common */
#घोषणा SDF_DIFF	0x00400000	/* can करो aref=dअगरf */
#घोषणा SDF_OTHER	0x00800000	/* can करो aref=other */
#घोषणा SDF_DITHER	0x01000000	/* can करो dithering */
#घोषणा SDF_DEGLITCH	0x02000000	/* can करो deglitching */
#घोषणा SDF_MMAP	0x04000000	/* can करो mmap() */
#घोषणा SDF_RUNNING	0x08000000	/* subdevice is acquiring data */
#घोषणा SDF_LSAMPL	0x10000000	/* subdevice uses 32-bit samples */
#घोषणा SDF_PACKED	0x20000000	/* subdevice can करो packed DIO */

/* subdevice types */

/**
 * क्रमागत comedi_subdevice_type - COMEDI subdevice types
 * @COMEDI_SUBD_UNUSED:		Unused subdevice.
 * @COMEDI_SUBD_AI:		Analog input.
 * @COMEDI_SUBD_AO:		Analog output.
 * @COMEDI_SUBD_DI:		Digital input.
 * @COMEDI_SUBD_DO:		Digital output.
 * @COMEDI_SUBD_DIO:		Digital input/output.
 * @COMEDI_SUBD_COUNTER:	Counter.
 * @COMEDI_SUBD_TIMER:		Timer.
 * @COMEDI_SUBD_MEMORY:		Memory, EEPROM, DPRAM.
 * @COMEDI_SUBD_CALIB:		Calibration DACs.
 * @COMEDI_SUBD_PROC:		Processor, DSP.
 * @COMEDI_SUBD_SERIAL:		Serial I/O.
 * @COMEDI_SUBD_PWM:		Pulse-Width Modulation output.
 */
क्रमागत comedi_subdevice_type अणु
	COMEDI_SUBD_UNUSED,
	COMEDI_SUBD_AI,
	COMEDI_SUBD_AO,
	COMEDI_SUBD_DI,
	COMEDI_SUBD_DO,
	COMEDI_SUBD_DIO,
	COMEDI_SUBD_COUNTER,
	COMEDI_SUBD_TIMER,
	COMEDI_SUBD_MEMORY,
	COMEDI_SUBD_CALIB,
	COMEDI_SUBD_PROC,
	COMEDI_SUBD_SERIAL,
	COMEDI_SUBD_PWM
पूर्ण;

/* configuration inकाष्ठाions */

/**
 * क्रमागत comedi_io_direction - COMEDI I/O directions
 * @COMEDI_INPUT:	Input.
 * @COMEDI_OUTPUT:	Output.
 * @COMEDI_OPENDRAIN:	Open-drain (or खोलो-collector) output.
 *
 * These are used by the %INSN_CONFIG_DIO_QUERY configuration inकाष्ठाion to
 * report a direction.  They may also be used in other places where a direction
 * needs to be specअगरied.
 */
क्रमागत comedi_io_direction अणु
	COMEDI_INPUT = 0,
	COMEDI_OUTPUT = 1,
	COMEDI_OPENDRAIN = 2
पूर्ण;

/**
 * क्रमागत configuration_ids - COMEDI configuration inकाष्ठाion codes
 * @INSN_CONFIG_DIO_INPUT:	Configure digital I/O as input.
 * @INSN_CONFIG_DIO_OUTPUT:	Configure digital I/O as output.
 * @INSN_CONFIG_DIO_OPENDRAIN:	Configure digital I/O as खोलो-drain (or खोलो
 *				collector) output.
 * @INSN_CONFIG_ANALOG_TRIG:	Configure analog trigger.
 * @INSN_CONFIG_ALT_SOURCE:	Configure alternate input source.
 * @INSN_CONFIG_DIGITAL_TRIG:	Configure digital trigger.
 * @INSN_CONFIG_BLOCK_SIZE:	Configure block size क्रम DMA transfers.
 * @INSN_CONFIG_TIMER_1:	Configure भागisor क्रम बाह्यal घड़ी.
 * @INSN_CONFIG_FILTER:		Configure a filter.
 * @INSN_CONFIG_CHANGE_NOTIFY:	Configure change notअगरication क्रम digital
 *				inमाला_दो.  (New drivers should use
 *				%INSN_CONFIG_DIGITAL_TRIG instead.)
 * @INSN_CONFIG_SERIAL_CLOCK:	Configure घड़ी क्रम serial I/O.
 * @INSN_CONFIG_BIसूचीECTIONAL_DATA: Send and receive byte over serial I/O.
 * @INSN_CONFIG_DIO_QUERY:	Query direction of digital I/O channel.
 * @INSN_CONFIG_PWM_OUTPUT:	Configure pulse-width modulator output.
 * @INSN_CONFIG_GET_PWM_OUTPUT:	Get pulse-width modulator output configuration.
 * @INSN_CONFIG_ARM:		Arm a subdevice or channel.
 * @INSN_CONFIG_DISARM:		Disarm a subdevice or channel.
 * @INSN_CONFIG_GET_COUNTER_STATUS: Get counter status.
 * @INSN_CONFIG_RESET:		Reset a subdevice or channel.
 * @INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR: Configure counter/समयr as
 *				single pulse generator.
 * @INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR: Configure counter/समयr as
 *				pulse train generator.
 * @INSN_CONFIG_GPCT_QUADRATURE_ENCODER: Configure counter as a quadrature
 *				encoder.
 * @INSN_CONFIG_SET_GATE_SRC:	Set counter/समयr gate source.
 * @INSN_CONFIG_GET_GATE_SRC:	Get counter/समयr gate source.
 * @INSN_CONFIG_SET_CLOCK_SRC:	Set counter/समयr master घड़ी source.
 * @INSN_CONFIG_GET_CLOCK_SRC:	Get counter/समयr master घड़ी source.
 * @INSN_CONFIG_SET_OTHER_SRC:	Set counter/समयr "other" source.
 * @INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE: Get size (in bytes) of subdevice's
 *				on-board FIFOs used during streaming
 *				input/output.
 * @INSN_CONFIG_SET_COUNTER_MODE: Set counter/समयr mode.
 * @INSN_CONFIG_8254_SET_MODE:	(Deprecated) Same as
 *				%INSN_CONFIG_SET_COUNTER_MODE.
 * @INSN_CONFIG_8254_READ_STATUS: Read status of 8254 counter channel.
 * @INSN_CONFIG_SET_ROUTING:	Set routing क्रम a channel.
 * @INSN_CONFIG_GET_ROUTING:	Get routing क्रम a channel.
 * @INSN_CONFIG_PWM_SET_PERIOD: Set PWM period in nanoseconds.
 * @INSN_CONFIG_PWM_GET_PERIOD: Get PWM period in nanoseconds.
 * @INSN_CONFIG_GET_PWM_STATUS: Get PWM status.
 * @INSN_CONFIG_PWM_SET_H_BRIDGE: Set PWM H bridge duty cycle and polarity क्रम
 *				a relay simultaneously.
 * @INSN_CONFIG_PWM_GET_H_BRIDGE: Get PWM H bridge duty cycle and polarity.
 * @INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS: Get the hardware timing restraपूर्णांकs,
 *				regardless of trigger sources.
 */
क्रमागत configuration_ids अणु
	INSN_CONFIG_DIO_INPUT = COMEDI_INPUT,
	INSN_CONFIG_DIO_OUTPUT = COMEDI_OUTPUT,
	INSN_CONFIG_DIO_OPENDRAIN = COMEDI_OPENDRAIN,
	INSN_CONFIG_ANALOG_TRIG = 16,
/*	INSN_CONFIG_WAVEFORM = 17, */
/*	INSN_CONFIG_TRIG = 18, */
/*	INSN_CONFIG_COUNTER = 19, */
	INSN_CONFIG_ALT_SOURCE = 20,
	INSN_CONFIG_DIGITAL_TRIG = 21,
	INSN_CONFIG_BLOCK_SIZE = 22,
	INSN_CONFIG_TIMER_1 = 23,
	INSN_CONFIG_FILTER = 24,
	INSN_CONFIG_CHANGE_NOTIFY = 25,

	INSN_CONFIG_SERIAL_CLOCK = 26,	/*ALPHA*/
	INSN_CONFIG_BIसूचीECTIONAL_DATA = 27,
	INSN_CONFIG_DIO_QUERY = 28,
	INSN_CONFIG_PWM_OUTPUT = 29,
	INSN_CONFIG_GET_PWM_OUTPUT = 30,
	INSN_CONFIG_ARM = 31,
	INSN_CONFIG_DISARM = 32,
	INSN_CONFIG_GET_COUNTER_STATUS = 33,
	INSN_CONFIG_RESET = 34,
	INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR = 1001,
	INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR = 1002,
	INSN_CONFIG_GPCT_QUADRATURE_ENCODER = 1003,
	INSN_CONFIG_SET_GATE_SRC = 2001,
	INSN_CONFIG_GET_GATE_SRC = 2002,
	INSN_CONFIG_SET_CLOCK_SRC = 2003,
	INSN_CONFIG_GET_CLOCK_SRC = 2004,
	INSN_CONFIG_SET_OTHER_SRC = 2005,
	INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE = 2006,
	INSN_CONFIG_SET_COUNTER_MODE = 4097,
	INSN_CONFIG_8254_SET_MODE = INSN_CONFIG_SET_COUNTER_MODE,
	INSN_CONFIG_8254_READ_STATUS = 4098,
	INSN_CONFIG_SET_ROUTING = 4099,
	INSN_CONFIG_GET_ROUTING = 4109,
	INSN_CONFIG_PWM_SET_PERIOD = 5000,
	INSN_CONFIG_PWM_GET_PERIOD = 5001,
	INSN_CONFIG_GET_PWM_STATUS = 5002,
	INSN_CONFIG_PWM_SET_H_BRIDGE = 5003,
	INSN_CONFIG_PWM_GET_H_BRIDGE = 5004,
	INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS = 5005,
पूर्ण;

/**
 * क्रमागत device_configuration_ids - COMEDI configuration inकाष्ठाion codes global
 * to an entire device.
 * @INSN_DEVICE_CONFIG_TEST_ROUTE:	Validate the possibility of a
 *					globally-named route
 * @INSN_DEVICE_CONFIG_CONNECT_ROUTE:	Connect a globally-named route
 * @INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:Disconnect a globally-named route
 * @INSN_DEVICE_CONFIG_GET_ROUTES:	Get a list of all globally-named routes
 *					that are valid क्रम a particular device.
 */
क्रमागत device_config_route_ids अणु
	INSN_DEVICE_CONFIG_TEST_ROUTE = 0,
	INSN_DEVICE_CONFIG_CONNECT_ROUTE = 1,
	INSN_DEVICE_CONFIG_DISCONNECT_ROUTE = 2,
	INSN_DEVICE_CONFIG_GET_ROUTES = 3,
पूर्ण;

/**
 * क्रमागत comedi_digital_trig_op - operations क्रम configuring a digital trigger
 * @COMEDI_DIGITAL_TRIG_DISABLE:	Return digital trigger to its शेष,
 *					inactive, unconfigured state.
 * @COMEDI_DIGITAL_TRIG_ENABLE_EDGES:	Set rising and/or falling edge inमाला_दो
 *					that each can fire the trigger.
 * @COMEDI_DIGITAL_TRIG_ENABLE_LEVELS:	Set a combination of high and/or low
 *					level inमाला_दो that can fire the trigger.
 *
 * These are used with the %INSN_CONFIG_DIGITAL_TRIG configuration inकाष्ठाion.
 * The data क्रम the configuration inकाष्ठाion is as follows...
 *
 *   data[%0] = %INSN_CONFIG_DIGITAL_TRIG
 *
 *   data[%1] = trigger ID
 *
 *   data[%2] = configuration operation
 *
 *   data[%3] = configuration parameter 1
 *
 *   data[%4] = configuration parameter 2
 *
 *   data[%5] = configuration parameter 3
 *
 * The trigger ID (data[%1]) is used to dअगरferentiate multiple digital triggers
 * beदीर्घing to the same subdevice.  The configuration operation (data[%2]) is
 * one of the क्रमागत comedi_digital_trig_op values.  The configuration
 * parameters (data[%3], data[%4], and data[%5]) depend on the operation; they
 * are not used with %COMEDI_DIGITAL_TRIG_DISABLE.
 *
 * For %COMEDI_DIGITAL_TRIG_ENABLE_EDGES and %COMEDI_DIGITAL_TRIG_ENABLE_LEVELS,
 * configuration parameter 1 (data[%3]) contains a "left-shift" value that
 * specअगरies the input corresponding to bit 0 of configuration parameters 2
 * and 3.  This is useful अगर the trigger has more than 32 inमाला_दो.
 *
 * For %COMEDI_DIGITAL_TRIG_ENABLE_EDGES, configuration parameter 2 (data[%4])
 * specअगरies which of up to 32 inमाला_दो have rising-edge sensitivity, and
 * configuration parameter 3 (data[%5]) specअगरies which of up to 32 inमाला_दो
 * have falling-edge sensitivity that can fire the trigger.
 *
 * For %COMEDI_DIGITAL_TRIG_ENABLE_LEVELS, configuration parameter 2 (data[%4])
 * specअगरies which of up to 32 inमाला_दो must be at a high level, and
 * configuration parameter 3 (data[%5]) specअगरies which of up to 32 inमाला_दो
 * must be at a low level क्रम the trigger to fire.
 *
 * Some sequences of %INSN_CONFIG_DIGITAL_TRIG inकाष्ठाions may have a (partly)
 * accumulative effect, depending on the low-level driver.  This is useful
 * when setting up a trigger that has more than 32 inमाला_दो, or has a combination
 * of edge- and level-triggered inमाला_दो.
 */
क्रमागत comedi_digital_trig_op अणु
	COMEDI_DIGITAL_TRIG_DISABLE = 0,
	COMEDI_DIGITAL_TRIG_ENABLE_EDGES = 1,
	COMEDI_DIGITAL_TRIG_ENABLE_LEVELS = 2
पूर्ण;

/**
 * क्रमागत comedi_support_level - support level क्रम a COMEDI feature
 * @COMEDI_UNKNOWN_SUPPORT:	Unspecअगरied support क्रम feature.
 * @COMEDI_SUPPORTED:		Feature is supported.
 * @COMEDI_UNSUPPORTED:		Feature is unsupported.
 */
क्रमागत comedi_support_level अणु
	COMEDI_UNKNOWN_SUPPORT = 0,
	COMEDI_SUPPORTED,
	COMEDI_UNSUPPORTED
पूर्ण;

/**
 * क्रमागत comedi_counter_status_flags - counter status bits
 * @COMEDI_COUNTER_ARMED:		Counter is armed.
 * @COMEDI_COUNTER_COUNTING:		Counter is counting.
 * @COMEDI_COUNTER_TERMINAL_COUNT:	Counter reached terminal count.
 *
 * These bitwise values are used by the %INSN_CONFIG_GET_COUNTER_STATUS
 * configuration inकाष्ठाion to report the status of a counter.
 */
क्रमागत comedi_counter_status_flags अणु
	COMEDI_COUNTER_ARMED = 0x1,
	COMEDI_COUNTER_COUNTING = 0x2,
	COMEDI_COUNTER_TERMINAL_COUNT = 0x4,
पूर्ण;

/* ioctls */

#घोषणा CIO 'd'
#घोषणा COMEDI_DEVCONFIG _IOW(CIO, 0, काष्ठा comedi_devconfig)
#घोषणा COMEDI_DEVINFO _IOR(CIO, 1, काष्ठा comedi_devinfo)
#घोषणा COMEDI_SUBDINFO _IOR(CIO, 2, काष्ठा comedi_subdinfo)
#घोषणा COMEDI_CHANINFO _IOR(CIO, 3, काष्ठा comedi_chaninfo)
/* _IOWR(CIO, 4, ...) is reserved */
#घोषणा COMEDI_LOCK _IO(CIO, 5)
#घोषणा COMEDI_UNLOCK _IO(CIO, 6)
#घोषणा COMEDI_CANCEL _IO(CIO, 7)
#घोषणा COMEDI_RANGEINFO _IOR(CIO, 8, काष्ठा comedi_rangeinfo)
#घोषणा COMEDI_CMD _IOR(CIO, 9, काष्ठा comedi_cmd)
#घोषणा COMEDI_CMDTEST _IOR(CIO, 10, काष्ठा comedi_cmd)
#घोषणा COMEDI_INSNLIST _IOR(CIO, 11, काष्ठा comedi_insnlist)
#घोषणा COMEDI_INSN _IOR(CIO, 12, काष्ठा comedi_insn)
#घोषणा COMEDI_BUFCONFIG _IOR(CIO, 13, काष्ठा comedi_bufconfig)
#घोषणा COMEDI_BUFINFO _IOWR(CIO, 14, काष्ठा comedi_bufinfo)
#घोषणा COMEDI_POLL _IO(CIO, 15)
#घोषणा COMEDI_SETRSUBD _IO(CIO, 16)
#घोषणा COMEDI_SETWSUBD _IO(CIO, 17)

/* काष्ठाures */

/**
 * काष्ठा comedi_insn - COMEDI inकाष्ठाion
 * @insn:	COMEDI inकाष्ठाion type (%INSN_xxx).
 * @n:		Length of @data[].
 * @data:	Poपूर्णांकer to data array operated on by the inकाष्ठाion.
 * @subdev:	Subdevice index.
 * @chanspec:	A packed "chanspec" value consisting of channel number,
 *		analog range index, analog reference type, and flags.
 * @unused:	Reserved क्रम future use.
 *
 * This is used with the %COMEDI_INSN ioctl, and indirectly with the
 * %COMEDI_INSNLIST ioctl.
 */
काष्ठा comedi_insn अणु
	अचिन्हित पूर्णांक insn;
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक __user *data;
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक chanspec;
	अचिन्हित पूर्णांक unused[3];
पूर्ण;

/**
 * काष्ठा comedi_insnlist - list of COMEDI inकाष्ठाions
 * @n_insns:	Number of COMEDI inकाष्ठाions.
 * @insns:	Poपूर्णांकer to array COMEDI inकाष्ठाions.
 *
 * This is used with the %COMEDI_INSNLIST ioctl.
 */
काष्ठा comedi_insnlist अणु
	अचिन्हित पूर्णांक n_insns;
	काष्ठा comedi_insn __user *insns;
पूर्ण;

/**
 * काष्ठा comedi_cmd - COMEDI asynchronous acquisition command details
 * @subdev:		Subdevice index.
 * @flags:		Command flags (%CMDF_xxx).
 * @start_src:		"Start acquisition" trigger source (%TRIG_xxx).
 * @start_arg:		"Start acquisition" trigger argument.
 * @scan_begin_src:	"Scan begin" trigger source.
 * @scan_begin_arg:	"Scan begin" trigger argument.
 * @convert_src:	"Convert" trigger source.
 * @convert_arg:	"Convert" trigger argument.
 * @scan_end_src:	"Scan end" trigger source.
 * @scan_end_arg:	"Scan end" trigger argument.
 * @stop_src:		"Stop acquisition" trigger source.
 * @stop_arg:		"Stop acquisition" trigger argument.
 * @chanlist:		Poपूर्णांकer to array of "chanspec" values, containing a
 *			sequence of channel numbers packed with analog range
 *			index, etc.
 * @chanlist_len:	Number of channels in sequence.
 * @data:		Poपूर्णांकer to miscellaneous set-up data (not used).
 * @data_len:		Length of miscellaneous set-up data.
 *
 * This is used with the %COMEDI_CMD or %COMEDI_CMDTEST ioctl to set-up
 * or validate an asynchronous acquisition command.  The ioctl may modअगरy
 * the &काष्ठा comedi_cmd and copy it back to the caller.
 *
 * Optional command @flags values that can be ORed together...
 *
 * %CMDF_BOGUS - makes %COMEDI_CMD ioctl वापस error %EAGAIN instead of
 * starting the command.
 *
 * %CMDF_PRIORITY - requests "hard real-time" processing (which is not
 * supported in this version of COMEDI).
 *
 * %CMDF_WAKE_EOS - requests the command makes data available क्रम पढ़ोing
 * after every "scan" period.
 *
 * %CMDF_WRITE - marks the command as being in the "write" (to device)
 * direction.  This करोes not need to be specअगरied by the caller unless the
 * subdevice supports commands in either direction.
 *
 * %CMDF_RAWDATA - prevents the command from "munging" the data between the
 * COMEDI sample क्रमmat and the raw hardware sample क्रमmat.
 *
 * %CMDF_ROUND_NEAREST - requests timing periods to be rounded to nearest
 * supported values.
 *
 * %CMDF_ROUND_DOWN - requests timing periods to be rounded करोwn to supported
 * values (frequencies rounded up).
 *
 * %CMDF_ROUND_UP - requests timing periods to be rounded up to supported
 * values (frequencies rounded करोwn).
 *
 * Trigger source values क्रम @start_src, @scan_begin_src, @convert_src,
 * @scan_end_src, and @stop_src...
 *
 * %TRIG_ANY - "all ones" value used to test which trigger sources are
 * supported.
 *
 * %TRIG_INVALID - "all zeroes" value used to indicate that all requested
 * trigger sources are invalid.
 *
 * %TRIG_NONE - never trigger (often used as a @stop_src value).
 *
 * %TRIG_NOW - trigger after '_arg' nanoseconds.
 *
 * %TRIG_FOLLOW - trigger follows another event.
 *
 * %TRIG_TIMER - trigger every '_arg' nanoseconds.
 *
 * %TRIG_COUNT - trigger when count '_arg' is reached.
 *
 * %TRIG_EXT - trigger on बाह्यal संकेत specअगरied by '_arg'.
 *
 * %TRIG_INT - trigger on पूर्णांकernal, software trigger specअगरied by '_arg'.
 *
 * %TRIG_OTHER - trigger on other, driver-defined संकेत specअगरied by '_arg'.
 */
काष्ठा comedi_cmd अणु
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक flags;

	अचिन्हित पूर्णांक start_src;
	अचिन्हित पूर्णांक start_arg;

	अचिन्हित पूर्णांक scan_begin_src;
	अचिन्हित पूर्णांक scan_begin_arg;

	अचिन्हित पूर्णांक convert_src;
	अचिन्हित पूर्णांक convert_arg;

	अचिन्हित पूर्णांक scan_end_src;
	अचिन्हित पूर्णांक scan_end_arg;

	अचिन्हित पूर्णांक stop_src;
	अचिन्हित पूर्णांक stop_arg;

	अचिन्हित पूर्णांक *chanlist;
	अचिन्हित पूर्णांक chanlist_len;

	लघु __user *data;
	अचिन्हित पूर्णांक data_len;
पूर्ण;

/**
 * काष्ठा comedi_chaninfo - used to retrieve per-channel inक्रमmation
 * @subdev:		Subdevice index.
 * @maxdata_list:	Optional poपूर्णांकer to per-channel maximum data values.
 * @flaglist:		Optional poपूर्णांकer to per-channel flags.
 * @rangelist:		Optional poपूर्णांकer to per-channel range types.
 * @unused:		Reserved क्रम future use.
 *
 * This is used with the %COMEDI_CHANINFO ioctl to get per-channel inक्रमmation
 * क्रम the subdevice.  Use of this requires knowledge of the number of channels
 * and subdevice flags obtained using the %COMEDI_SUBDINFO ioctl.
 *
 * The @maxdata_list member must be %शून्य unless the %SDF_MAXDATA subdevice
 * flag is set.  The @flaglist member must be %शून्य unless the %SDF_FLAGS
 * subdevice flag is set.  The @rangelist member must be %शून्य unless the
 * %SDF_RANGETYPE subdevice flag is set.  Otherwise, the arrays they poपूर्णांक to
 * must be at least as दीर्घ as the number of channels.
 */
काष्ठा comedi_chaninfo अणु
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक __user *maxdata_list;
	अचिन्हित पूर्णांक __user *flaglist;
	अचिन्हित पूर्णांक __user *rangelist;
	अचिन्हित पूर्णांक unused[4];
पूर्ण;

/**
 * काष्ठा comedi_rangeinfo - used to retrieve the range table क्रम a channel
 * @range_type:		Encodes subdevice index (bits 27:24), channel index
 *			(bits 23:16) and range table length (bits 15:0).
 * @range_ptr:		Poपूर्णांकer to array of @काष्ठा comedi_krange to be filled
 *			in with the range table क्रम the channel or subdevice.
 *
 * This is used with the %COMEDI_RANGEINFO ioctl to retrieve the range table
 * क्रम a specअगरic channel (अगर the subdevice has the %SDF_RANGETYPE flag set to
 * indicate that the range table depends on the channel), or क्रम the subdevice
 * as a whole (अगर the %SDF_RANGETYPE flag is clear, indicating the range table
 * is shared by all channels).
 *
 * The @range_type value is an input to the ioctl and comes from a previous
 * use of the %COMEDI_SUBDINFO ioctl (अगर the %SDF_RANGETYPE flag is clear),
 * or the %COMEDI_CHANINFO ioctl (अगर the %SDF_RANGETYPE flag is set).
 */
काष्ठा comedi_rangeinfo अणु
	अचिन्हित पूर्णांक range_type;
	व्योम __user *range_ptr;
पूर्ण;

/**
 * काष्ठा comedi_krange - describes a range in a range table
 * @min:	Minimum value in millionths (1e-6) of a unit.
 * @max:	Maximum value in millionths (1e-6) of a unit.
 * @flags:	Indicates the units (in bits 7:0) OR'ed with optional flags.
 *
 * A range table is associated with a single channel, or with all channels in a
 * subdevice, and a list of one or more ranges.  A %काष्ठा comedi_krange
 * describes the physical range of units क्रम one of those ranges.  Sample
 * values in COMEDI are अचिन्हित from %0 up to some 'maxdata' value.  The
 * mapping from sample values to physical units is assumed to be nomimally
 * linear (क्रम the purpose of describing the range), with sample value %0
 * mapping to @min, and the 'maxdata' sample value mapping to @max.
 *
 * The currently defined units are %UNIT_volt (%0), %UNIT_mA (%1), and
 * %UNIT_none (%2).  The @min and @max values are the physical range multiplied
 * by 1e6, so a @max value of %1000000 (with %UNIT_volt) represents a maximal
 * value of 1 volt.
 *
 * The only defined flag value is %RF_EXTERNAL (%0x100), indicating that the
 * range needs to be multiplied by an बाह्यal reference.
 */
काष्ठा comedi_krange अणु
	पूर्णांक min;
	पूर्णांक max;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * काष्ठा comedi_subdinfo - used to retrieve inक्रमmation about a subdevice
 * @type:		Type of subdevice from &क्रमागत comedi_subdevice_type.
 * @n_chan:		Number of channels the subdevice supports.
 * @subd_flags:		A mixture of अटल and dynamic flags describing
 *			aspects of the subdevice and its current state.
 * @समयr_type:		Timer type.  Always set to %5 ("nanosecond timer").
 * @len_chanlist:	Maximum length of a channel list अगर the subdevice
 *			supports asynchronous acquisition commands.
 * @maxdata:		Maximum sample value क्रम all channels अगर the
 *			%SDF_MAXDATA subdevice flag is clear.
 * @flags:		Channel flags क्रम all channels अगर the %SDF_FLAGS
 *			subdevice flag is clear.
 * @range_type:		The range type क्रम all channels अगर the %SDF_RANGETYPE
 *			subdevice flag is clear.  Encodes the subdevice index
 *			(bits 27:24), a dummy channel index %0 (bits 23:16),
 *			and the range table length (bits 15:0).
 * @settling_समय_0:	Not used.
 * @insn_bits_support:	Set to %COMEDI_SUPPORTED अगर the subdevice supports the
 *			%INSN_BITS inकाष्ठाion, or to %COMEDI_UNSUPPORTED अगर it
 *			करोes not.
 * @unused:		Reserved क्रम future use.
 *
 * This is used with the %COMEDI_SUBDINFO ioctl which copies an array of
 * &काष्ठा comedi_subdinfo back to user space, with one element per subdevice.
 * Use of this requires knowledge of the number of subdevices obtained from
 * the %COMEDI_DEVINFO ioctl.
 *
 * These are the @subd_flags values that may be ORed together...
 *
 * %SDF_BUSY - the subdevice is busy processing an asynchronous command or a
 * synchronous inकाष्ठाion.
 *
 * %SDF_BUSY_OWNER - the subdevice is busy processing an asynchronous
 * acquisition command started on the current file object (the file object
 * issuing the %COMEDI_SUBDINFO ioctl).
 *
 * %SDF_LOCKED - the subdevice is locked by a %COMEDI_LOCK ioctl.
 *
 * %SDF_LOCK_OWNER - the subdevice is locked by a %COMEDI_LOCK ioctl from the
 * current file object.
 *
 * %SDF_MAXDATA - maximum sample values are channel-specअगरic.
 *
 * %SDF_FLAGS - channel flags are channel-specअगरic.
 *
 * %SDF_RANGETYPE - range types are channel-specअगरic.
 *
 * %SDF_PWM_COUNTER - PWM can चयन off स्वतःmatically.
 *
 * %SDF_PWM_HBRIDGE - or PWM is चिन्हित (H-bridge).
 *
 * %SDF_CMD - the subdevice supports asynchronous commands.
 *
 * %SDF_SOFT_CALIBRATED - the subdevice uses software calibration.
 *
 * %SDF_CMD_WRITE - the subdevice supports asynchronous commands in the output
 * ("write") direction.
 *
 * %SDF_CMD_READ - the subdevice supports asynchronous commands in the input
 * ("read") direction.
 *
 * %SDF_READABLE - the subdevice is पढ़ोable (e.g. analog input).
 *
 * %SDF_WRITABLE (aliased as %SDF_WRITEABLE) - the subdevice is writable (e.g.
 * analog output).
 *
 * %SDF_INTERNAL - the subdevice has no बाह्यally visible lines.
 *
 * %SDF_GROUND - the subdevice can use ground as an analog reference.
 *
 * %SDF_COMMON - the subdevice can use a common analog reference.
 *
 * %SDF_DIFF - the subdevice can use dअगरferential inमाला_दो (or outमाला_दो).
 *
 * %SDF_OTHER - the subdevice can use some other analog reference.
 *
 * %SDF_DITHER - the subdevice can करो dithering.
 *
 * %SDF_DEGLITCH - the subdevice can करो deglitching.
 *
 * %SDF_MMAP - this is never set.
 *
 * %SDF_RUNNING - an asynchronous command is still running.
 *
 * %SDF_LSAMPL - the subdevice uses "long" (32-bit) samples (क्रम asynchronous
 * command data).
 *
 * %SDF_PACKED - the subdevice packs several DIO samples पूर्णांकo a single sample
 * (क्रम asynchronous command data).
 *
 * No "channel flags" (@flags) values are currently defined.
 */
काष्ठा comedi_subdinfo अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक n_chan;
	अचिन्हित पूर्णांक subd_flags;
	अचिन्हित पूर्णांक समयr_type;
	अचिन्हित पूर्णांक len_chanlist;
	अचिन्हित पूर्णांक maxdata;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक range_type;
	अचिन्हित पूर्णांक settling_समय_0;
	अचिन्हित पूर्णांक insn_bits_support;
	अचिन्हित पूर्णांक unused[8];
पूर्ण;

/**
 * काष्ठा comedi_devinfo - used to retrieve inक्रमmation about a COMEDI device
 * @version_code:	COMEDI version code.
 * @n_subdevs:		Number of subdevices the device has.
 * @driver_name:	Null-terminated COMEDI driver name.
 * @board_name:		Null-terminated COMEDI board name.
 * @पढ़ो_subdevice:	Index of the current "read" subdevice (%-1 अगर none).
 * @ग_लिखो_subdevice:	Index of the current "write" subdevice (%-1 अगर none).
 * @unused:		Reserved क्रम future use.
 *
 * This is used with the %COMEDI_DEVINFO ioctl to get basic inक्रमmation about
 * the device.
 */
काष्ठा comedi_devinfo अणु
	अचिन्हित पूर्णांक version_code;
	अचिन्हित पूर्णांक n_subdevs;
	अक्षर driver_name[COMEDI_NAMELEN];
	अक्षर board_name[COMEDI_NAMELEN];
	पूर्णांक पढ़ो_subdevice;
	पूर्णांक ग_लिखो_subdevice;
	पूर्णांक unused[30];
पूर्ण;

/**
 * काष्ठा comedi_devconfig - used to configure a legacy COMEDI device
 * @board_name:		Null-terminated string specअगरying the type of board
 *			to configure.
 * @options:		An array of पूर्णांकeger configuration options.
 *
 * This is used with the %COMEDI_DEVCONFIG ioctl to configure a "legacy" COMEDI
 * device, such as an ISA card.  Not all COMEDI drivers support this.  Those
 * that करो either expect the specअगरied board name to match one of a list of
 * names रेजिस्टरed with the COMEDI core, or expect the specअगरied board name
 * to match the COMEDI driver name itself.  The configuration options are
 * handled in a driver-specअगरic manner.
 */
काष्ठा comedi_devconfig अणु
	अक्षर board_name[COMEDI_NAMELEN];
	पूर्णांक options[COMEDI_NDEVCONFOPTS];
पूर्ण;

/**
 * काष्ठा comedi_bufconfig - used to set or get buffer size क्रम a subdevice
 * @subdevice:		Subdevice index.
 * @flags:		Not used.
 * @maximum_size:	Maximum allowed buffer size.
 * @size:		Buffer size.
 * @unused:		Reserved क्रम future use.
 *
 * This is used with the %COMEDI_BUFCONFIG ioctl to get or configure the
 * maximum buffer size and current buffer size क्रम a COMEDI subdevice that
 * supports asynchronous commands.  If the subdevice करोes not support
 * asynchronous commands, @maximum_size and @size are ignored and set to 0.
 *
 * On ioctl input, non-zero values of @maximum_size and @size specअगरy a
 * new maximum size and new current size (in bytes), respectively.  These
 * will by rounded up to a multiple of %PAGE_SIZE.  Specअगरying a new maximum
 * size requires admin capabilities.
 *
 * On ioctl output, @maximum_size and @size and set to the current maximum
 * buffer size and current buffer size, respectively.
 */
काष्ठा comedi_bufconfig अणु
	अचिन्हित पूर्णांक subdevice;
	अचिन्हित पूर्णांक flags;

	अचिन्हित पूर्णांक maximum_size;
	अचिन्हित पूर्णांक size;

	अचिन्हित पूर्णांक unused[4];
पूर्ण;

/**
 * काष्ठा comedi_bufinfo - used to manipulate buffer position क्रम a subdevice
 * @subdevice:		Subdevice index.
 * @bytes_पढ़ो:		Specअगरy amount to advance पढ़ो position क्रम an
 *			asynchronous command in the input ("read") direction.
 * @buf_ग_लिखो_ptr:	Current ग_लिखो position (index) within the buffer.
 * @buf_पढ़ो_ptr:	Current पढ़ो position (index) within the buffer.
 * @buf_ग_लिखो_count:	Total amount written, modulo 2^32.
 * @buf_पढ़ो_count:	Total amount पढ़ो, modulo 2^32.
 * @bytes_written:	Specअगरy amount to advance ग_लिखो position क्रम an
 *			asynchronous command in the output ("write") direction.
 * @unused:		Reserved क्रम future use.
 *
 * This is used with the %COMEDI_BUFINFO ioctl to optionally advance the
 * current पढ़ो or ग_लिखो position in an asynchronous acquisition data buffer,
 * and to get the current पढ़ो and ग_लिखो positions in the buffer.
 */
काष्ठा comedi_bufinfo अणु
	अचिन्हित पूर्णांक subdevice;
	अचिन्हित पूर्णांक bytes_पढ़ो;

	अचिन्हित पूर्णांक buf_ग_लिखो_ptr;
	अचिन्हित पूर्णांक buf_पढ़ो_ptr;
	अचिन्हित पूर्णांक buf_ग_लिखो_count;
	अचिन्हित पूर्णांक buf_पढ़ो_count;

	अचिन्हित पूर्णांक bytes_written;

	अचिन्हित पूर्णांक unused[4];
पूर्ण;

/* range stuff */

#घोषणा __RANGE(a, b)	((((a) & 0xffff) << 16) | ((b) & 0xffff))

#घोषणा RANGE_OFFSET(a)		(((a) >> 16) & 0xffff)
#घोषणा RANGE_LENGTH(b)		((b) & 0xffff)

#घोषणा RF_UNIT(flags)		((flags) & 0xff)
#घोषणा RF_EXTERNAL		0x100

#घोषणा UNIT_volt		0
#घोषणा UNIT_mA			1
#घोषणा UNIT_none		2

#घोषणा COMEDI_MIN_SPEED	0xffffffffu

/**********************************************************/
/* everything after this line is ALPHA */
/**********************************************************/

/*
 * 8254 specअगरic configuration.
 *
 * It supports two config commands:
 *
 * 0 ID: INSN_CONFIG_SET_COUNTER_MODE
 * 1 8254 Mode
 * I8254_MODE0, I8254_MODE1, ..., I8254_MODE5
 * OR'ed with:
 * I8254_BCD, I8254_BINARY
 *
 * 0 ID: INSN_CONFIG_8254_READ_STATUS
 * 1 <-- Status byte वापसed here.
 * B7 = Output
 * B6 = शून्य Count
 * B5 - B0 Current mode.
 */

क्रमागत i8254_mode अणु
	I8254_MODE0 = (0 << 1),	/* Interrupt on terminal count */
	I8254_MODE1 = (1 << 1),	/* Hardware retriggerable one-shot */
	I8254_MODE2 = (2 << 1),	/* Rate generator */
	I8254_MODE3 = (3 << 1),	/* Square wave mode */
	I8254_MODE4 = (4 << 1),	/* Software triggered strobe */
	/* Hardware triggered strobe (retriggerable) */
	I8254_MODE5 = (5 << 1),
	/* Use binary-coded decimal instead of binary (pretty useless) */
	I8254_BCD = 1,
	I8254_BINARY = 0
पूर्ण;

/* *** BEGIN GLOBALLY-NAMED NI TERMINALS/SIGNALS *** */

/*
 * Common National Instruments Terminal/Signal names.
 * Some of these have no NI_ prefix as they are useful क्रम non-NI hardware, such
 * as those that utilize the PXI/RTSI trigger lines.
 *
 * NOTE ABOUT THE CHOICE OF NAMES HERE AND THE CAMELSCRIPT:
 *   The choice to use CamelScript and the exact names below is क्रम
 *   मुख्यtainability, clarity, similarity to manufacturer's करोcumentation,
 *   _and_ a mitigation क्रम confusion that has plagued the use of these drivers
 *   क्रम years!
 *
 *   More detail:
 *   There have been signअगरicant confusions over the past many years क्रम users
 *   when trying to understand how to connect to/from संकेतs and terminals on
 *   NI hardware using comedi.  The major reason क्रम this is that the actual
 *   रेजिस्टर values were exposed and required to be used by users.  Several
 *   major reasons exist why this caused major confusion क्रम users:
 *   1) The रेजिस्टर values are _NOT_ in user करोcumentation, but rather in
 *     arcane locations, such as a few रेजिस्टर programming manuals that are
 *     increasingly hard to find and the NI MHDDK (comments in example code).
 *     There is no one place to find the various valid values of the रेजिस्टरs.
 *   2) The रेजिस्टर values are _NOT_ completely consistent.  There is no way to
 *     gain any sense of पूर्णांकuition of which values, or even क्रमागतs one should use
 *     क्रम various रेजिस्टरs.  There was some attempt in prior use of comedi to
 *     name क्रमागतs such that a user might know which क्रमागतs should be used क्रम
 *     varying purposes, but the end-user had to gain a knowledge of रेजिस्टर
 *     values to correctly wield this approach.
 *   3) The names क्रम संकेतs and रेजिस्टरs found in the various रेजिस्टर level
 *     programming manuals and venकरोr-provided करोcumentation are _not_ even
 *     बंद to the same names that are in the end-user करोcumentation.
 *
 *   Similar, albeit less, confusion plagued NI's previous version of their own
 *   drivers.  Earlier than 2003, NI greatly simplअगरied the situation क्रम users
 *   by releasing a new API that असलtracted the names of संकेतs/terminals to a
 *   common and पूर्णांकuitive set of names.
 *
 *   The names below mirror the names chosen and well करोcumented by NI.  These
 *   names are exposed to the user via the comedilib user library.  By keeping
 *   the names below, in spite of the use of CamelScript, मुख्यtenance will be
 *   greatly eased and confusion क्रम users _and_ comedi developers will be
 *   greatly reduced.
 */

/*
 * Base of असलtracted NI names.
 * The first 16 bits of *_arg are reserved क्रम channel selection.
 * Since we only actually need the first 4 or 5 bits क्रम all रेजिस्टर values on
 * NI select रेजिस्टरs anyways, we'll identअगरy all values >= (1<<15) as being an
 * असलtracted NI संकेत/terminal name.
 * These values are also used/वापसed by INSN_DEVICE_CONFIG_TEST_ROUTE,
 * INSN_DEVICE_CONFIG_CONNECT_ROUTE, INSN_DEVICE_CONFIG_DISCONNECT_ROUTE,
 * and INSN_DEVICE_CONFIG_GET_ROUTES.
 */
#घोषणा NI_NAMES_BASE	0x8000u

#घोषणा _TERM_N(base, n, x)	((base) + ((x) & ((n) - 1)))

/*
 * not necessarily all allowed 64 PFIs are valid--certainly not क्रम all devices
 */
#घोषणा NI_PFI(x)		_TERM_N(NI_NAMES_BASE, 64, x)
/* 8 trigger lines by standard, Some devices cannot talk to all eight. */
#घोषणा TRIGGER_LINE(x)		_TERM_N(NI_PFI(-1) + 1, 8, x)
/* 4 RTSI shared MUXes to route संकेतs to/from TRIGGER_LINES on NI hardware */
#घोषणा NI_RTSI_BRD(x)		_TERM_N(TRIGGER_LINE(-1) + 1, 4, x)

/* *** Counter/समयr names : 8 counters max *** */
#घोषणा NI_MAX_COUNTERS		8
#घोषणा NI_COUNTER_NAMES_BASE	(NI_RTSI_BRD(-1)  + 1)
#घोषणा NI_CtrSource(x)	      _TERM_N(NI_COUNTER_NAMES_BASE, NI_MAX_COUNTERS, x)
/* Gate, Aux, A,B,Z are all treated, at बार as gates */
#घोषणा NI_GATES_NAMES_BASE	(NI_CtrSource(-1) + 1)
#घोषणा NI_CtrGate(x)		_TERM_N(NI_GATES_NAMES_BASE, NI_MAX_COUNTERS, x)
#घोषणा NI_CtrAux(x)		_TERM_N(NI_CtrGate(-1)  + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_CtrA(x)		_TERM_N(NI_CtrAux(-1)   + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_CtrB(x)		_TERM_N(NI_CtrA(-1)     + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_CtrZ(x)		_TERM_N(NI_CtrB(-1)     + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_GATES_NAMES_MAX	NI_CtrZ(-1)
#घोषणा NI_CtrArmStartTrigger(x) _TERM_N(NI_CtrZ(-1)    + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_CtrInternalOutput(x) \
		      _TERM_N(NI_CtrArmStartTrigger(-1) + 1, NI_MAX_COUNTERS, x)
/** बाह्यal pin(s) labeled conveniently as Ctr<i>Out. */
#घोषणा NI_CtrOut(x)   _TERM_N(NI_CtrInternalOutput(-1) + 1, NI_MAX_COUNTERS, x)
/** For Buffered sampling of ctr -- x series capability. */
#घोषणा NI_CtrSampleClock(x)	_TERM_N(NI_CtrOut(-1)   + 1, NI_MAX_COUNTERS, x)
#घोषणा NI_COUNTER_NAMES_MAX	NI_CtrSampleClock(-1)

क्रमागत ni_common_संकेत_names अणु
	/* PXI_Star: this is a non-NI-specअगरic संकेत */
	PXI_Star = NI_COUNTER_NAMES_MAX + 1,
	PXI_Clk10,
	PXIe_Clk100,
	NI_AI_SampleClock,
	NI_AI_SampleClockTimebase,
	NI_AI_StartTrigger,
	NI_AI_ReferenceTrigger,
	NI_AI_ConvertClock,
	NI_AI_ConvertClockTimebase,
	NI_AI_PauseTrigger,
	NI_AI_HoldCompleteEvent,
	NI_AI_HoldComplete,
	NI_AI_ExternalMUXClock,
	NI_AI_STOP, /* pulse संकेत that occurs when a update is finished(?) */
	NI_AO_SampleClock,
	NI_AO_SampleClockTimebase,
	NI_AO_StartTrigger,
	NI_AO_PauseTrigger,
	NI_DI_SampleClock,
	NI_DI_SampleClockTimebase,
	NI_DI_StartTrigger,
	NI_DI_ReferenceTrigger,
	NI_DI_PauseTrigger,
	NI_DI_InputBufferFull,
	NI_DI_ReadyForStartEvent,
	NI_DI_ReadyForTransferEventBurst,
	NI_DI_ReadyForTransferEventPipelined,
	NI_DO_SampleClock,
	NI_DO_SampleClockTimebase,
	NI_DO_StartTrigger,
	NI_DO_PauseTrigger,
	NI_DO_OutputBufferFull,
	NI_DO_DataActiveEvent,
	NI_DO_ReadyForStartEvent,
	NI_DO_ReadyForTransferEvent,
	NI_MasterTimebase,
	NI_20MHzTimebase,
	NI_80MHzTimebase,
	NI_100MHzTimebase,
	NI_200MHzTimebase,
	NI_100kHzTimebase,
	NI_10MHzRefClock,
	NI_FrequencyOutput,
	NI_ChangeDetectionEvent,
	NI_AnalogComparisonEvent,
	NI_WatchकरोgExpiredEvent,
	NI_WatchकरोgExpirationTrigger,
	NI_SCXI_Trig1,
	NI_LogicLow,
	NI_LogicHigh,
	NI_ExternalStrobe,
	NI_PFI_DO,
	NI_CaseGround,
	/* special पूर्णांकernal संकेत used as variable source क्रम RTSI bus: */
	NI_RGOUT0,

	/* just a name to make the next more convenient, regardless of above */
	_NI_NAMES_MAX_PLUS_1,
	NI_NUM_NAMES = _NI_NAMES_MAX_PLUS_1 - NI_NAMES_BASE,
पूर्ण;

/* *** END GLOBALLY-NAMED NI TERMINALS/SIGNALS *** */

#घोषणा NI_USUAL_PFI_SELECT(x)	(((x) < 10) ? (0x1 + (x)) : (0xb + (x)))
#घोषणा NI_USUAL_RTSI_SELECT(x)	(((x) < 7) ? (0xb + (x)) : 0x1b)

/*
 * mode bits क्रम NI general-purpose counters, set with
 * INSN_CONFIG_SET_COUNTER_MODE
 */
#घोषणा NI_GPCT_COUNTING_MODE_SHIFT 16
#घोषणा NI_GPCT_INDEX_PHASE_BITSHIFT 20
#घोषणा NI_GPCT_COUNTING_सूचीECTION_SHIFT 24
क्रमागत ni_gpct_mode_bits अणु
	NI_GPCT_GATE_ON_BOTH_EDGES_BIT = 0x4,
	NI_GPCT_EDGE_GATE_MODE_MASK = 0x18,
	NI_GPCT_EDGE_GATE_STARTS_STOPS_BITS = 0x0,
	NI_GPCT_EDGE_GATE_STOPS_STARTS_BITS = 0x8,
	NI_GPCT_EDGE_GATE_STARTS_BITS = 0x10,
	NI_GPCT_EDGE_GATE_NO_STARTS_NO_STOPS_BITS = 0x18,
	NI_GPCT_STOP_MODE_MASK = 0x60,
	NI_GPCT_STOP_ON_GATE_BITS = 0x00,
	NI_GPCT_STOP_ON_GATE_OR_TC_BITS = 0x20,
	NI_GPCT_STOP_ON_GATE_OR_SECOND_TC_BITS = 0x40,
	NI_GPCT_LOAD_B_SELECT_BIT = 0x80,
	NI_GPCT_OUTPUT_MODE_MASK = 0x300,
	NI_GPCT_OUTPUT_TC_PULSE_BITS = 0x100,
	NI_GPCT_OUTPUT_TC_TOGGLE_BITS = 0x200,
	NI_GPCT_OUTPUT_TC_OR_GATE_TOGGLE_BITS = 0x300,
	NI_GPCT_HARDWARE_DISARM_MASK = 0xc00,
	NI_GPCT_NO_HARDWARE_DISARM_BITS = 0x000,
	NI_GPCT_DISARM_AT_TC_BITS = 0x400,
	NI_GPCT_DISARM_AT_GATE_BITS = 0x800,
	NI_GPCT_DISARM_AT_TC_OR_GATE_BITS = 0xc00,
	NI_GPCT_LOADING_ON_TC_BIT = 0x1000,
	NI_GPCT_LOADING_ON_GATE_BIT = 0x4000,
	NI_GPCT_COUNTING_MODE_MASK = 0x7 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_NORMAL_BITS =
		0x0 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_QUADRATURE_X1_BITS =
		0x1 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_QUADRATURE_X2_BITS =
		0x2 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_QUADRATURE_X4_BITS =
		0x3 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_TWO_PULSE_BITS =
		0x4 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_COUNTING_MODE_SYNC_SOURCE_BITS =
		0x6 << NI_GPCT_COUNTING_MODE_SHIFT,
	NI_GPCT_INDEX_PHASE_MASK = 0x3 << NI_GPCT_INDEX_PHASE_BITSHIFT,
	NI_GPCT_INDEX_PHASE_LOW_A_LOW_B_BITS =
		0x0 << NI_GPCT_INDEX_PHASE_BITSHIFT,
	NI_GPCT_INDEX_PHASE_LOW_A_HIGH_B_BITS =
		0x1 << NI_GPCT_INDEX_PHASE_BITSHIFT,
	NI_GPCT_INDEX_PHASE_HIGH_A_LOW_B_BITS =
		0x2 << NI_GPCT_INDEX_PHASE_BITSHIFT,
	NI_GPCT_INDEX_PHASE_HIGH_A_HIGH_B_BITS =
		0x3 << NI_GPCT_INDEX_PHASE_BITSHIFT,
	NI_GPCT_INDEX_ENABLE_BIT = 0x400000,
	NI_GPCT_COUNTING_सूचीECTION_MASK =
		0x3 << NI_GPCT_COUNTING_सूचीECTION_SHIFT,
	NI_GPCT_COUNTING_सूचीECTION_DOWN_BITS =
		0x00 << NI_GPCT_COUNTING_सूचीECTION_SHIFT,
	NI_GPCT_COUNTING_सूचीECTION_UP_BITS =
		0x1 << NI_GPCT_COUNTING_सूचीECTION_SHIFT,
	NI_GPCT_COUNTING_सूचीECTION_HW_UP_DOWN_BITS =
		0x2 << NI_GPCT_COUNTING_सूचीECTION_SHIFT,
	NI_GPCT_COUNTING_सूचीECTION_HW_GATE_BITS =
		0x3 << NI_GPCT_COUNTING_सूचीECTION_SHIFT,
	NI_GPCT_RELOAD_SOURCE_MASK = 0xc000000,
	NI_GPCT_RELOAD_SOURCE_FIXED_BITS = 0x0,
	NI_GPCT_RELOAD_SOURCE_SWITCHING_BITS = 0x4000000,
	NI_GPCT_RELOAD_SOURCE_GATE_SELECT_BITS = 0x8000000,
	NI_GPCT_OR_GATE_BIT = 0x10000000,
	NI_GPCT_INVERT_OUTPUT_BIT = 0x20000000
पूर्ण;

/*
 * Bits क्रम setting a घड़ी source with
 * INSN_CONFIG_SET_CLOCK_SRC when using NI general-purpose counters.
 */
क्रमागत ni_gpct_घड़ी_source_bits अणु
	NI_GPCT_CLOCK_SRC_SELECT_MASK = 0x3f,
	NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS = 0x0,
	NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS = 0x1,
	NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS = 0x2,
	NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS = 0x3,
	NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS = 0x4,
	NI_GPCT_NEXT_TC_CLOCK_SRC_BITS = 0x5,
	/* NI 660x-specअगरic */
	NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS = 0x6,
	NI_GPCT_PXI10_CLOCK_SRC_BITS = 0x7,
	NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS = 0x8,
	NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS = 0x9,
	NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK = 0x30000000,
	NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS = 0x0,
	/* भागide source by 2 */
	NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS = 0x10000000,
	/* भागide source by 8 */
	NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS = 0x20000000,
	NI_GPCT_INVERT_CLOCK_SRC_BIT = 0x80000000
पूर्ण;

/* NI 660x-specअगरic */
#घोषणा NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(x)	(0x10 + (x))

#घोषणा NI_GPCT_RTSI_CLOCK_SRC_BITS(x)		(0x18 + (x))

/* no pfi on NI 660x */
#घोषणा NI_GPCT_PFI_CLOCK_SRC_BITS(x)		(0x20 + (x))

/*
 * Possibilities क्रम setting a gate source with
 * INSN_CONFIG_SET_GATE_SRC when using NI general-purpose counters.
 * May be bitwise-or'd with CR_EDGE or CR_INVERT.
 */
क्रमागत ni_gpct_gate_select अणु
	/* m-series gates */
	NI_GPCT_TIMESTAMP_MUX_GATE_SELECT = 0x0,
	NI_GPCT_AI_START2_GATE_SELECT = 0x12,
	NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT = 0x13,
	NI_GPCT_NEXT_OUT_GATE_SELECT = 0x14,
	NI_GPCT_AI_START1_GATE_SELECT = 0x1c,
	NI_GPCT_NEXT_SOURCE_GATE_SELECT = 0x1d,
	NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT = 0x1e,
	NI_GPCT_LOGIC_LOW_GATE_SELECT = 0x1f,
	/* more gates क्रम 660x */
	NI_GPCT_SOURCE_PIN_i_GATE_SELECT = 0x100,
	NI_GPCT_GATE_PIN_i_GATE_SELECT = 0x101,
	/* more gates क्रम 660x "second gate" */
	NI_GPCT_UP_DOWN_PIN_i_GATE_SELECT = 0x201,
	NI_GPCT_SELECTED_GATE_GATE_SELECT = 0x21e,
	/*
	 * m-series "second gate" sources are unknown,
	 * we should add them here with an offset of 0x300 when
	 * known.
	 */
	NI_GPCT_DISABLED_GATE_SELECT = 0x8000,
पूर्ण;

#घोषणा NI_GPCT_GATE_PIN_GATE_SELECT(x)		(0x102 + (x))
#घोषणा NI_GPCT_RTSI_GATE_SELECT(x)		NI_USUAL_RTSI_SELECT(x)
#घोषणा NI_GPCT_PFI_GATE_SELECT(x)		NI_USUAL_PFI_SELECT(x)
#घोषणा NI_GPCT_UP_DOWN_PIN_GATE_SELECT(x)	(0x202 + (x))

/*
 * Possibilities क्रम setting a source with
 * INSN_CONFIG_SET_OTHER_SRC when using NI general-purpose counters.
 */
क्रमागत ni_gpct_other_index अणु
	NI_GPCT_SOURCE_ENCODER_A,
	NI_GPCT_SOURCE_ENCODER_B,
	NI_GPCT_SOURCE_ENCODER_Z
पूर्ण;

क्रमागत ni_gpct_other_select अणु
	/* m-series gates */
	/* Still unknown, probably only need NI_GPCT_PFI_OTHER_SELECT */
	NI_GPCT_DISABLED_OTHER_SELECT = 0x8000,
पूर्ण;

#घोषणा NI_GPCT_PFI_OTHER_SELECT(x)	NI_USUAL_PFI_SELECT(x)

/*
 * start sources क्रम ni general-purpose counters क्रम use with
 * INSN_CONFIG_ARM
 */
क्रमागत ni_gpct_arm_source अणु
	NI_GPCT_ARM_IMMEDIATE = 0x0,
	/*
	 * Start both the counter and the adjacent paired counter simultaneously
	 */
	NI_GPCT_ARM_PAIRED_IMMEDIATE = 0x1,
	/*
	 * If the NI_GPCT_HW_ARM bit is set, we will pass the least signअगरicant
	 * bits (3 bits क्रम 660x or 5 bits क्रम m-series) through to the
	 * hardware. To select a hardware trigger, pass the appropriate select
	 * bit, e.g.,
	 * NI_GPCT_HW_ARM | NI_GPCT_AI_START1_GATE_SELECT or
	 * NI_GPCT_HW_ARM | NI_GPCT_PFI_GATE_SELECT(pfi_number)
	 */
	NI_GPCT_HW_ARM = 0x1000,
	NI_GPCT_ARM_UNKNOWN = NI_GPCT_HW_ARM,	/* क्रम backward compatibility */
पूर्ण;

/* digital filtering options क्रम ni 660x क्रम use with INSN_CONFIG_FILTER. */
क्रमागत ni_gpct_filter_select अणु
	NI_GPCT_FILTER_OFF = 0x0,
	NI_GPCT_FILTER_TIMEBASE_3_SYNC = 0x1,
	NI_GPCT_FILTER_100x_TIMEBASE_1 = 0x2,
	NI_GPCT_FILTER_20x_TIMEBASE_1 = 0x3,
	NI_GPCT_FILTER_10x_TIMEBASE_1 = 0x4,
	NI_GPCT_FILTER_2x_TIMEBASE_1 = 0x5,
	NI_GPCT_FILTER_2x_TIMEBASE_3 = 0x6
पूर्ण;

/*
 * PFI digital filtering options क्रम ni m-series क्रम use with
 * INSN_CONFIG_FILTER.
 */
क्रमागत ni_pfi_filter_select अणु
	NI_PFI_FILTER_OFF = 0x0,
	NI_PFI_FILTER_125ns = 0x1,
	NI_PFI_FILTER_6425ns = 0x2,
	NI_PFI_FILTER_2550us = 0x3
पूर्ण;

/* master घड़ी sources क्रम ni mio boards and INSN_CONFIG_SET_CLOCK_SRC */
क्रमागत ni_mio_घड़ी_source अणु
	NI_MIO_INTERNAL_CLOCK = 0,
	/*
	 * Doesn't work क्रम m-series, use NI_MIO_PLL_RTSI_CLOCK()
	 * the NI_MIO_PLL_* sources are m-series only
	 */
	NI_MIO_RTSI_CLOCK = 1,
	NI_MIO_PLL_PXI_STAR_TRIGGER_CLOCK = 2,
	NI_MIO_PLL_PXI10_CLOCK = 3,
	NI_MIO_PLL_RTSI0_CLOCK = 4
पूर्ण;

#घोषणा NI_MIO_PLL_RTSI_CLOCK(x)	(NI_MIO_PLL_RTSI0_CLOCK + (x))

/*
 * Signals which can be routed to an NI RTSI pin with INSN_CONFIG_SET_ROUTING.
 * The numbers asचिन्हित are not arbitrary, they correspond to the bits required
 * to program the board.
 */
क्रमागत ni_rtsi_routing अणु
	NI_RTSI_OUTPUT_ADR_START1 = 0,
	NI_RTSI_OUTPUT_ADR_START2 = 1,
	NI_RTSI_OUTPUT_SCLKG = 2,
	NI_RTSI_OUTPUT_DACUPDN = 3,
	NI_RTSI_OUTPUT_DA_START1 = 4,
	NI_RTSI_OUTPUT_G_SRC0 = 5,
	NI_RTSI_OUTPUT_G_GATE0 = 6,
	NI_RTSI_OUTPUT_RGOUT0 = 7,
	NI_RTSI_OUTPUT_RTSI_BRD_0 = 8,
	/* Pre-m-series always have RTSI घड़ी on line 7 */
	NI_RTSI_OUTPUT_RTSI_OSC = 12
पूर्ण;

#घोषणा NI_RTSI_OUTPUT_RTSI_BRD(x)	(NI_RTSI_OUTPUT_RTSI_BRD_0 + (x))

/*
 * Signals which can be routed to an NI PFI pin on an m-series board with
 * INSN_CONFIG_SET_ROUTING.  These numbers are also वापसed by
 * INSN_CONFIG_GET_ROUTING on pre-m-series boards, even though their routing
 * cannot be changed.  The numbers asचिन्हित are not arbitrary, they correspond
 * to the bits required to program the board.
 */
क्रमागत ni_pfi_routing अणु
	NI_PFI_OUTPUT_PFI_DEFAULT = 0,
	NI_PFI_OUTPUT_AI_START1 = 1,
	NI_PFI_OUTPUT_AI_START2 = 2,
	NI_PFI_OUTPUT_AI_CONVERT = 3,
	NI_PFI_OUTPUT_G_SRC1 = 4,
	NI_PFI_OUTPUT_G_GATE1 = 5,
	NI_PFI_OUTPUT_AO_UPDATE_N = 6,
	NI_PFI_OUTPUT_AO_START1 = 7,
	NI_PFI_OUTPUT_AI_START_PULSE = 8,
	NI_PFI_OUTPUT_G_SRC0 = 9,
	NI_PFI_OUTPUT_G_GATE0 = 10,
	NI_PFI_OUTPUT_EXT_STROBE = 11,
	NI_PFI_OUTPUT_AI_EXT_MUX_CLK = 12,
	NI_PFI_OUTPUT_GOUT0 = 13,
	NI_PFI_OUTPUT_GOUT1 = 14,
	NI_PFI_OUTPUT_FREQ_OUT = 15,
	NI_PFI_OUTPUT_PFI_DO = 16,
	NI_PFI_OUTPUT_I_ATRIG = 17,
	NI_PFI_OUTPUT_RTSI0 = 18,
	NI_PFI_OUTPUT_PXI_STAR_TRIGGER_IN = 26,
	NI_PFI_OUTPUT_SCXI_TRIG1 = 27,
	NI_PFI_OUTPUT_DIO_CHANGE_DETECT_RTSI = 28,
	NI_PFI_OUTPUT_CDI_SAMPLE = 29,
	NI_PFI_OUTPUT_CDO_UPDATE = 30
पूर्ण;

#घोषणा NI_PFI_OUTPUT_RTSI(x)		(NI_PFI_OUTPUT_RTSI0 + (x))

/*
 * Signals which can be routed to output on a NI PFI pin on a 660x board
 * with INSN_CONFIG_SET_ROUTING.  The numbers asचिन्हित are
 * not arbitrary, they correspond to the bits required
 * to program the board.  Lines 0 to 7 can only be set to
 * NI_660X_PFI_OUTPUT_DIO.  Lines 32 to 39 can only be set to
 * NI_660X_PFI_OUTPUT_COUNTER.
 */
क्रमागत ni_660x_pfi_routing अणु
	NI_660X_PFI_OUTPUT_COUNTER = 1,	/* counter */
	NI_660X_PFI_OUTPUT_DIO = 2,	/* अटल digital output */
पूर्ण;

/*
 * NI External Trigger lines.  These values are not arbitrary, but are related
 * to the bits required to program the board (offset by 1 क्रम historical
 * reasons).
 */
#घोषणा NI_EXT_PFI(x)			(NI_USUAL_PFI_SELECT(x) - 1)
#घोषणा NI_EXT_RTSI(x)			(NI_USUAL_RTSI_SELECT(x) - 1)

/*
 * Clock sources क्रम CDIO subdevice on NI m-series boards.  Used as the
 * scan_begin_arg क्रम a comedi_command. These sources may also be bitwise-or'd
 * with CR_INVERT to change polarity.
 */
क्रमागत ni_m_series_cdio_scan_begin_src अणु
	NI_CDIO_SCAN_BEGIN_SRC_GROUND = 0,
	NI_CDIO_SCAN_BEGIN_SRC_AI_START = 18,
	NI_CDIO_SCAN_BEGIN_SRC_AI_CONVERT = 19,
	NI_CDIO_SCAN_BEGIN_SRC_PXI_STAR_TRIGGER = 20,
	NI_CDIO_SCAN_BEGIN_SRC_G0_OUT = 28,
	NI_CDIO_SCAN_BEGIN_SRC_G1_OUT = 29,
	NI_CDIO_SCAN_BEGIN_SRC_ANALOG_TRIGGER = 30,
	NI_CDIO_SCAN_BEGIN_SRC_AO_UPDATE = 31,
	NI_CDIO_SCAN_BEGIN_SRC_FREQ_OUT = 32,
	NI_CDIO_SCAN_BEGIN_SRC_DIO_CHANGE_DETECT_IRQ = 33
पूर्ण;

#घोषणा NI_CDIO_SCAN_BEGIN_SRC_PFI(x)	NI_USUAL_PFI_SELECT(x)
#घोषणा NI_CDIO_SCAN_BEGIN_SRC_RTSI(x)	NI_USUAL_RTSI_SELECT(x)

/*
 * scan_begin_src क्रम scan_begin_arg==TRIG_EXT with analog output command on NI
 * boards.  These scan begin sources can also be bitwise-or'd with CR_INVERT to
 * change polarity.
 */
#घोषणा NI_AO_SCAN_BEGIN_SRC_PFI(x)	NI_USUAL_PFI_SELECT(x)
#घोषणा NI_AO_SCAN_BEGIN_SRC_RTSI(x)	NI_USUAL_RTSI_SELECT(x)

/*
 * Bits क्रम setting a घड़ी source with
 * INSN_CONFIG_SET_CLOCK_SRC when using NI frequency output subdevice.
 */
क्रमागत ni_freq_out_घड़ी_source_bits अणु
	NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC,	/* 10 MHz */
	NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC	/* 100 KHz */
पूर्ण;

/*
 * Values क्रम setting a घड़ी source with INSN_CONFIG_SET_CLOCK_SRC क्रम
 * 8254 counter subdevices on Amplicon DIO boards (amplc_dio200 driver).
 */
क्रमागत amplc_dio_घड़ी_source अणु
	/*
	 * Per channel बाह्यal घड़ी
	 * input/output pin (pin is only an
	 * input when घड़ी source set to this value,
	 * otherwise it is an output)
	 */
	AMPLC_DIO_CLK_CLKN,
	AMPLC_DIO_CLK_10MHZ,	/* 10 MHz पूर्णांकernal घड़ी */
	AMPLC_DIO_CLK_1MHZ,	/* 1 MHz पूर्णांकernal घड़ी */
	AMPLC_DIO_CLK_100KHZ,	/* 100 kHz पूर्णांकernal घड़ी */
	AMPLC_DIO_CLK_10KHZ,	/* 10 kHz पूर्णांकernal घड़ी */
	AMPLC_DIO_CLK_1KHZ,	/* 1 kHz पूर्णांकernal घड़ी */
	/*
	 * Output of preceding counter channel
	 * (क्रम channel 0, preceding counter
	 * channel is channel 2 on preceding
	 * counter subdevice, क्रम first counter
	 * subdevice, preceding counter
	 * subdevice is the last counter
	 * subdevice)
	 */
	AMPLC_DIO_CLK_OUTNM1,
	AMPLC_DIO_CLK_EXT,	/* per chip बाह्यal input pin */
	/* the following are "enhanced" घड़ी sources क्रम PCIe models */
	AMPLC_DIO_CLK_VCC,	/* घड़ी input HIGH */
	AMPLC_DIO_CLK_GND,	/* घड़ी input LOW */
	AMPLC_DIO_CLK_PAT_PRESENT, /* "pattern present" संकेत */
	AMPLC_DIO_CLK_20MHZ	/* 20 MHz पूर्णांकernal घड़ी */
पूर्ण;

/*
 * Values क्रम setting a घड़ी source with INSN_CONFIG_SET_CLOCK_SRC क्रम
 * समयr subdevice on some Amplicon DIO PCIe boards (amplc_dio200 driver).
 */
क्रमागत amplc_dio_ts_घड़ी_src अणु
	AMPLC_DIO_TS_CLK_1GHZ,	/* 1 ns period with 20 ns granularity */
	AMPLC_DIO_TS_CLK_1MHZ,	/* 1 us period */
	AMPLC_DIO_TS_CLK_1KHZ	/* 1 ms period */
पूर्ण;

/*
 * Values क्रम setting a gate source with INSN_CONFIG_SET_GATE_SRC क्रम
 * 8254 counter subdevices on Amplicon DIO boards (amplc_dio200 driver).
 */
क्रमागत amplc_dio_gate_source अणु
	AMPLC_DIO_GAT_VCC,	/* पूर्णांकernal high logic level */
	AMPLC_DIO_GAT_GND,	/* पूर्णांकernal low logic level */
	AMPLC_DIO_GAT_GATN,	/* per channel बाह्यal gate input */
	/*
	 * negated output of counter channel minus 2
	 * (क्रम channels 0 or 1, channel minus 2 is channel 1 or 2 on
	 * the preceding counter subdevice, क्रम the first counter subdevice
	 * the preceding counter subdevice is the last counter subdevice)
	 */
	AMPLC_DIO_GAT_NOUTNM2,
	AMPLC_DIO_GAT_RESERVED4,
	AMPLC_DIO_GAT_RESERVED5,
	AMPLC_DIO_GAT_RESERVED6,
	AMPLC_DIO_GAT_RESERVED7,
	/* the following are "enhanced" gate sources क्रम PCIe models */
	AMPLC_DIO_GAT_NGATN = 6, /* negated per channel gate input */
	/* non-negated output of counter channel minus 2 */
	AMPLC_DIO_GAT_OUTNM2,
	AMPLC_DIO_GAT_PAT_PRESENT, /* "pattern present" संकेत */
	AMPLC_DIO_GAT_PAT_OCCURRED, /* "pattern occurred" latched */
	AMPLC_DIO_GAT_PAT_GONE,	/* "pattern gone away" latched */
	AMPLC_DIO_GAT_NPAT_PRESENT, /* negated "pattern present" */
	AMPLC_DIO_GAT_NPAT_OCCURRED, /* negated "pattern occurred" */
	AMPLC_DIO_GAT_NPAT_GONE	/* negated "pattern gone away" */
पूर्ण;

/*
 * Values क्रम setting a घड़ी source with INSN_CONFIG_SET_CLOCK_SRC क्रम
 * the counter subdevice on the Kolter Electronic PCI-Counter board
 * (ke_counter driver).
 */
क्रमागत ke_counter_घड़ी_source अणु
	KE_CLK_20MHZ,	/* पूर्णांकernal 20MHz (शेष) */
	KE_CLK_4MHZ,	/* पूर्णांकernal 4MHz (option) */
	KE_CLK_EXT	/* बाह्यal घड़ी on pin 21 of D-Sub */
पूर्ण;

#पूर्ण_अगर /* _COMEDI_H */
