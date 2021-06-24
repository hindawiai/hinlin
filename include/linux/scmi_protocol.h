<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SCMI Message Protocol driver header
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#अगर_अघोषित _LINUX_SCMI_PROTOCOL_H
#घोषणा _LINUX_SCMI_PROTOCOL_H

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/types.h>

#घोषणा SCMI_MAX_STR_SIZE	16
#घोषणा SCMI_MAX_NUM_RATES	16

/**
 * काष्ठा scmi_revision_info - version inक्रमmation काष्ठाure
 *
 * @major_ver: Major ABI version. Change here implies risk of backward
 *	compatibility अवरोध.
 * @minor_ver: Minor ABI version. Change here implies new feature addition,
 *	or compatible change in ABI.
 * @num_protocols: Number of protocols that are implemented, excluding the
 *	base protocol.
 * @num_agents: Number of agents in the प्रणाली.
 * @impl_ver: A venकरोr-specअगरic implementation version.
 * @venकरोr_id: A venकरोr identअगरier(Null terminated ASCII string)
 * @sub_venकरोr_id: A sub-venकरोr identअगरier(Null terminated ASCII string)
 */
काष्ठा scmi_revision_info अणु
	u16 major_ver;
	u16 minor_ver;
	u8 num_protocols;
	u8 num_agents;
	u32 impl_ver;
	अक्षर venकरोr_id[SCMI_MAX_STR_SIZE];
	अक्षर sub_venकरोr_id[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_घड़ी_info अणु
	अक्षर name[SCMI_MAX_STR_SIZE];
	bool rate_discrete;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक num_rates;
			u64 rates[SCMI_MAX_NUM_RATES];
		पूर्ण list;
		काष्ठा अणु
			u64 min_rate;
			u64 max_rate;
			u64 step_size;
		पूर्ण range;
	पूर्ण;
पूर्ण;

काष्ठा scmi_handle;
काष्ठा scmi_device;
काष्ठा scmi_protocol_handle;

/**
 * काष्ठा scmi_clk_proto_ops - represents the various operations provided
 *	by SCMI Clock Protocol
 *
 * @count_get: get the count of घड़ीs provided by SCMI
 * @info_get: get the inक्रमmation of the specअगरied घड़ी
 * @rate_get: request the current घड़ी rate of a घड़ी
 * @rate_set: set the घड़ी rate of a घड़ी
 * @enable: enables the specअगरied घड़ी
 * @disable: disables the specअगरied घड़ी
 */
काष्ठा scmi_clk_proto_ops अणु
	पूर्णांक (*count_get)(स्थिर काष्ठा scmi_protocol_handle *ph);

	स्थिर काष्ठा scmi_घड़ी_info *(*info_get)
		(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id);
	पूर्णांक (*rate_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id,
			u64 *rate);
	पूर्णांक (*rate_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id,
			u64 rate);
	पूर्णांक (*enable)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id);
	पूर्णांक (*disable)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id);
पूर्ण;

/**
 * काष्ठा scmi_perf_proto_ops - represents the various operations provided
 *	by SCMI Perक्रमmance Protocol
 *
 * @limits_set: sets limits on the perक्रमmance level of a करोमुख्य
 * @limits_get: माला_लो limits on the perक्रमmance level of a करोमुख्य
 * @level_set: sets the perक्रमmance level of a करोमुख्य
 * @level_get: माला_लो the perक्रमmance level of a करोमुख्य
 * @device_करोमुख्य_id: माला_लो the scmi करोमुख्य id क्रम a given device
 * @transition_latency_get: माला_लो the DVFS transition latency क्रम a given device
 * @device_opps_add: adds all the OPPs क्रम a given device
 * @freq_set: sets the frequency क्रम a given device using sustained frequency
 *	to sustained perक्रमmance level mapping
 * @freq_get: माला_लो the frequency क्रम a given device using sustained frequency
 *	to sustained perक्रमmance level mapping
 * @est_घातer_get: माला_लो the estimated घातer cost क्रम a given perक्रमmance करोमुख्य
 *	at a given frequency
 */
काष्ठा scmi_perf_proto_ops अणु
	पूर्णांक (*limits_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			  u32 max_perf, u32 min_perf);
	पूर्णांक (*limits_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			  u32 *max_perf, u32 *min_perf);
	पूर्णांक (*level_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			 u32 level, bool poll);
	पूर्णांक (*level_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			 u32 *level, bool poll);
	पूर्णांक (*device_करोमुख्य_id)(काष्ठा device *dev);
	पूर्णांक (*transition_latency_get)(स्थिर काष्ठा scmi_protocol_handle *ph,
				      काष्ठा device *dev);
	पूर्णांक (*device_opps_add)(स्थिर काष्ठा scmi_protocol_handle *ph,
			       काष्ठा device *dev);
	पूर्णांक (*freq_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			अचिन्हित दीर्घ rate, bool poll);
	पूर्णांक (*freq_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			अचिन्हित दीर्घ *rate, bool poll);
	पूर्णांक (*est_घातer_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			     अचिन्हित दीर्घ *rate, अचिन्हित दीर्घ *घातer);
	bool (*fast_चयन_possible)(स्थिर काष्ठा scmi_protocol_handle *ph,
				     काष्ठा device *dev);
	bool (*घातer_scale_mw_get)(स्थिर काष्ठा scmi_protocol_handle *ph);
पूर्ण;

/**
 * काष्ठा scmi_घातer_proto_ops - represents the various operations provided
 *	by SCMI Power Protocol
 *
 * @num_करोमुख्यs_get: get the count of घातer करोमुख्यs provided by SCMI
 * @name_get: माला_लो the name of a घातer करोमुख्य
 * @state_set: sets the घातer state of a घातer करोमुख्य
 * @state_get: माला_लो the घातer state of a घातer करोमुख्य
 */
काष्ठा scmi_घातer_proto_ops अणु
	पूर्णांक (*num_करोमुख्यs_get)(स्थिर काष्ठा scmi_protocol_handle *ph);
	अक्षर *(*name_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
#घोषणा SCMI_POWER_STATE_TYPE_SHIFT	30
#घोषणा SCMI_POWER_STATE_ID_MASK	(BIT(28) - 1)
#घोषणा SCMI_POWER_STATE_PARAM(type, id) \
	((((type) & BIT(0)) << SCMI_POWER_STATE_TYPE_SHIFT) | \
		((id) & SCMI_POWER_STATE_ID_MASK))
#घोषणा SCMI_POWER_STATE_GENERIC_ON	SCMI_POWER_STATE_PARAM(0, 0)
#घोषणा SCMI_POWER_STATE_GENERIC_OFF	SCMI_POWER_STATE_PARAM(1, 0)
	पूर्णांक (*state_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			 u32 state);
	पूर्णांक (*state_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			 u32 *state);
पूर्ण;

/**
 * scmi_sensor_पढ़ोing  - represent a बारtamped पढ़ो
 *
 * Used by @पढ़ोing_get_बारtamped method.
 *
 * @value: The चिन्हित value sensor पढ़ो.
 * @बारtamp: An अचिन्हित बारtamp क्रम the sensor पढ़ो, as provided by
 *	       SCMI platक्रमm. Set to zero when not available.
 */
काष्ठा scmi_sensor_पढ़ोing अणु
	दीर्घ दीर्घ value;
	अचिन्हित दीर्घ दीर्घ बारtamp;
पूर्ण;

/**
 * scmi_range_attrs  - specअगरies a sensor or axis values' range
 * @min_range: The minimum value which can be represented by the sensor/axis.
 * @max_range: The maximum value which can be represented by the sensor/axis.
 */
काष्ठा scmi_range_attrs अणु
	दीर्घ दीर्घ min_range;
	दीर्घ दीर्घ max_range;
पूर्ण;

/**
 * scmi_sensor_axis_info  - describes one sensor axes
 * @id: The axes ID.
 * @type: Axes type. Chosen amongst one of @क्रमागत scmi_sensor_class.
 * @scale: Power-of-10 multiplier applied to the axis unit.
 * @name: शून्य-terminated string representing axes name as advertised by
 *	  SCMI platक्रमm.
 * @extended_attrs: Flag to indicate the presence of additional extended
 *		    attributes क्रम this axes.
 * @resolution: Extended attribute representing the resolution of the axes.
 *		Set to 0 अगर not reported by this axes.
 * @exponent: Extended attribute representing the घातer-of-10 multiplier that
 *	      is applied to the resolution field. Set to 0 अगर not reported by
 *	      this axes.
 * @attrs: Extended attributes representing minimum and maximum values
 *	   measurable by this axes. Set to 0 अगर not reported by this sensor.
 */
काष्ठा scmi_sensor_axis_info अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक type;
	पूर्णांक scale;
	अक्षर name[SCMI_MAX_STR_SIZE];
	bool extended_attrs;
	अचिन्हित पूर्णांक resolution;
	पूर्णांक exponent;
	काष्ठा scmi_range_attrs attrs;
पूर्ण;

/**
 * scmi_sensor_पूर्णांकervals_info  - describes number and type of available update
 * पूर्णांकervals
 * @segmented: Flag क्रम segmented पूर्णांकervals' representation. When True there
 *	       will be exactly 3 पूर्णांकervals in @desc, with each entry
 *	       representing a member of a segment in this order:
 *	       अणुlowest update पूर्णांकerval, highest update पूर्णांकerval, step sizeपूर्ण
 * @count: Number of पूर्णांकervals described in @desc.
 * @desc: Array of @count पूर्णांकerval descriptor biपंचांगask represented as detailed in
 *	  the SCMI specअगरication: it can be accessed using the accompanying
 *	  macros.
 * @pपुनः_स्मृति_pool: A minimal pपुनः_स्मृतिated pool of desc entries used to aव्योम
 *		   lesser-than-64-bytes dynamic allocation क्रम small @count
 *		   values.
 */
काष्ठा scmi_sensor_पूर्णांकervals_info अणु
	bool segmented;
	अचिन्हित पूर्णांक count;
#घोषणा SCMI_SENS_INTVL_SEGMENT_LOW	0
#घोषणा SCMI_SENS_INTVL_SEGMENT_HIGH	1
#घोषणा SCMI_SENS_INTVL_SEGMENT_STEP	2
	अचिन्हित पूर्णांक *desc;
#घोषणा SCMI_SENS_INTVL_GET_SECS(x)		FIELD_GET(GENMASK(20, 5), (x))
#घोषणा SCMI_SENS_INTVL_GET_EXP(x)					\
	(अणु								\
		पूर्णांक __चिन्हित_exp = FIELD_GET(GENMASK(4, 0), (x));	\
									\
		अगर (__चिन्हित_exp & BIT(4))				\
			__चिन्हित_exp |= GENMASK(31, 5);			\
		__चिन्हित_exp;						\
	पूर्ण)
#घोषणा SCMI_MAX_PREALLOC_POOL			16
	अचिन्हित पूर्णांक pपुनः_स्मृति_pool[SCMI_MAX_PREALLOC_POOL];
पूर्ण;

/**
 * काष्ठा scmi_sensor_info - represents inक्रमmation related to one of the
 * available sensors.
 * @id: Sensor ID.
 * @type: Sensor type. Chosen amongst one of @क्रमागत scmi_sensor_class.
 * @scale: Power-of-10 multiplier applied to the sensor unit.
 * @num_trip_poपूर्णांकs: Number of maximum configurable trip poपूर्णांकs.
 * @async: Flag क्रम asynchronous पढ़ो support.
 * @update: Flag क्रम continuouos update notअगरication support.
 * @बारtamped: Flag क्रम बारtamped पढ़ो support.
 * @tstamp_scale: Power-of-10 multiplier applied to the sensor बारtamps to
 *		  represent it in seconds.
 * @num_axis: Number of supported axis अगर any. Reported as 0 क्रम scalar sensors.
 * @axis: Poपूर्णांकer to an array of @num_axis descriptors.
 * @पूर्णांकervals: Descriptor of available update पूर्णांकervals.
 * @sensor_config: A biपंचांगask reporting the current sensor configuration as
 *		   detailed in the SCMI specअगरication: it can accessed and
 *		   modअगरied through the accompanying macros.
 * @name: शून्य-terminated string representing sensor name as advertised by
 *	  SCMI platक्रमm.
 * @extended_scalar_attrs: Flag to indicate the presence of additional extended
 *			   attributes क्रम this sensor.
 * @sensor_घातer: Extended attribute representing the average घातer
 *		  consumed by the sensor in microwatts (uW) when it is active.
 *		  Reported here only क्रम scalar sensors.
 *		  Set to 0 अगर not reported by this sensor.
 * @resolution: Extended attribute representing the resolution of the sensor.
 *		Reported here only क्रम scalar sensors.
 *		Set to 0 अगर not reported by this sensor.
 * @exponent: Extended attribute representing the घातer-of-10 multiplier that is
 *	      applied to the resolution field.
 *	      Reported here only क्रम scalar sensors.
 *	      Set to 0 अगर not reported by this sensor.
 * @scalar_attrs: Extended attributes representing minimum and maximum
 *		  measurable values by this sensor.
 *		  Reported here only क्रम scalar sensors.
 *		  Set to 0 अगर not reported by this sensor.
 */
काष्ठा scmi_sensor_info अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक type;
	पूर्णांक scale;
	अचिन्हित पूर्णांक num_trip_poपूर्णांकs;
	bool async;
	bool update;
	bool बारtamped;
	पूर्णांक tstamp_scale;
	अचिन्हित पूर्णांक num_axis;
	काष्ठा scmi_sensor_axis_info *axis;
	काष्ठा scmi_sensor_पूर्णांकervals_info पूर्णांकervals;
	अचिन्हित पूर्णांक sensor_config;
#घोषणा SCMI_SENS_CFG_UPDATE_SECS_MASK		GENMASK(31, 16)
#घोषणा SCMI_SENS_CFG_GET_UPDATE_SECS(x)				\
	FIELD_GET(SCMI_SENS_CFG_UPDATE_SECS_MASK, (x))

#घोषणा SCMI_SENS_CFG_UPDATE_EXP_MASK		GENMASK(15, 11)
#घोषणा SCMI_SENS_CFG_GET_UPDATE_EXP(x)					\
	(अणु								\
		पूर्णांक __चिन्हित_exp =					\
			FIELD_GET(SCMI_SENS_CFG_UPDATE_EXP_MASK, (x));	\
									\
		अगर (__चिन्हित_exp & BIT(4))				\
			__चिन्हित_exp |= GENMASK(31, 5);			\
		__चिन्हित_exp;						\
	पूर्ण)

#घोषणा SCMI_SENS_CFG_ROUND_MASK		GENMASK(10, 9)
#घोषणा SCMI_SENS_CFG_ROUND_AUTO		2
#घोषणा SCMI_SENS_CFG_ROUND_UP			1
#घोषणा SCMI_SENS_CFG_ROUND_DOWN		0

#घोषणा SCMI_SENS_CFG_TSTAMP_ENABLED_MASK	BIT(1)
#घोषणा SCMI_SENS_CFG_TSTAMP_ENABLE		1
#घोषणा SCMI_SENS_CFG_TSTAMP_DISABLE		0
#घोषणा SCMI_SENS_CFG_IS_TSTAMP_ENABLED(x)				\
	FIELD_GET(SCMI_SENS_CFG_TSTAMP_ENABLED_MASK, (x))

#घोषणा SCMI_SENS_CFG_SENSOR_ENABLED_MASK	BIT(0)
#घोषणा SCMI_SENS_CFG_SENSOR_ENABLE		1
#घोषणा SCMI_SENS_CFG_SENSOR_DISABLE		0
	अक्षर name[SCMI_MAX_STR_SIZE];
#घोषणा SCMI_SENS_CFG_IS_ENABLED(x)		FIELD_GET(BIT(0), (x))
	bool extended_scalar_attrs;
	अचिन्हित पूर्णांक sensor_घातer;
	अचिन्हित पूर्णांक resolution;
	पूर्णांक exponent;
	काष्ठा scmi_range_attrs scalar_attrs;
पूर्ण;

/*
 * Partial list from Distributed Management Task Force (DMTF) specअगरication:
 * DSP0249 (Platक्रमm Level Data Model specअगरication)
 */
क्रमागत scmi_sensor_class अणु
	NONE = 0x0,
	UNSPEC = 0x1,
	TEMPERATURE_C = 0x2,
	TEMPERATURE_F = 0x3,
	TEMPERATURE_K = 0x4,
	VOLTAGE = 0x5,
	CURRENT = 0x6,
	POWER = 0x7,
	ENERGY = 0x8,
	CHARGE = 0x9,
	VOLTAMPERE = 0xA,
	NITS = 0xB,
	LUMENS = 0xC,
	LUX = 0xD,
	CANDELAS = 0xE,
	KPA = 0xF,
	PSI = 0x10,
	NEWTON = 0x11,
	CFM = 0x12,
	RPM = 0x13,
	HERTZ = 0x14,
	SECS = 0x15,
	MINS = 0x16,
	HOURS = 0x17,
	DAYS = 0x18,
	WEEKS = 0x19,
	MILS = 0x1A,
	INCHES = 0x1B,
	FEET = 0x1C,
	CUBIC_INCHES = 0x1D,
	CUBIC_FEET = 0x1E,
	METERS = 0x1F,
	CUBIC_CM = 0x20,
	CUBIC_METERS = 0x21,
	LITERS = 0x22,
	FLUID_OUNCES = 0x23,
	RADIANS = 0x24,
	STERADIANS = 0x25,
	REVOLUTIONS = 0x26,
	CYCLES = 0x27,
	GRAVITIES = 0x28,
	OUNCES = 0x29,
	POUNDS = 0x2A,
	FOOT_POUNDS = 0x2B,
	OUNCE_INCHES = 0x2C,
	GAUSS = 0x2D,
	GILBERTS = 0x2E,
	HENRIES = 0x2F,
	FARADS = 0x30,
	OHMS = 0x31,
	SIEMENS = 0x32,
	MOLES = 0x33,
	BECQUERELS = 0x34,
	PPM = 0x35,
	DECIBELS = 0x36,
	DBA = 0x37,
	DBC = 0x38,
	GRAYS = 0x39,
	SIEVERTS = 0x3A,
	COLOR_TEMP_K = 0x3B,
	BITS = 0x3C,
	BYTES = 0x3D,
	WORDS = 0x3E,
	DWORDS = 0x3F,
	QWORDS = 0x40,
	PERCENTAGE = 0x41,
	PASCALS = 0x42,
	COUNTS = 0x43,
	GRAMS = 0x44,
	NEWTON_METERS = 0x45,
	HITS = 0x46,
	MISSES = 0x47,
	RETRIES = 0x48,
	OVERRUNS = 0x49,
	UNDERRUNS = 0x4A,
	COLLISIONS = 0x4B,
	PACKETS = 0x4C,
	MESSAGES = 0x4D,
	CHARS = 0x4E,
	ERRORS = 0x4F,
	CORRECTED_ERRS = 0x50,
	UNCORRECTABLE_ERRS = 0x51,
	SQ_MILS = 0x52,
	SQ_INCHES = 0x53,
	SQ_FEET = 0x54,
	SQ_CM = 0x55,
	SQ_METERS = 0x56,
	RADIANS_SEC = 0x57,
	BPM = 0x58,
	METERS_SEC_SQUARED = 0x59,
	METERS_SEC = 0x5A,
	CUBIC_METERS_SEC = 0x5B,
	MM_MERCURY = 0x5C,
	RADIANS_SEC_SQUARED = 0x5D,
	OEM_UNIT = 0xFF
पूर्ण;

/**
 * काष्ठा scmi_sensor_proto_ops - represents the various operations provided
 *	by SCMI Sensor Protocol
 *
 * @count_get: get the count of sensors provided by SCMI
 * @info_get: get the inक्रमmation of the specअगरied sensor
 * @trip_poपूर्णांक_config: selects and configures a trip-poपूर्णांक of पूर्णांकerest
 * @पढ़ोing_get: माला_लो the current value of the sensor
 * @पढ़ोing_get_बारtamped: माला_लो the current value and बारtamp, when
 *			     available, of the sensor. (as of v3.0 spec)
 *			     Supports multi-axis sensors क्रम sensors which
 *			     supports it and अगर the @पढ़ोing array size of
 *			     @count entry equals the sensor num_axis
 * @config_get: Get sensor current configuration
 * @config_set: Set sensor current configuration
 */
काष्ठा scmi_sensor_proto_ops अणु
	पूर्णांक (*count_get)(स्थिर काष्ठा scmi_protocol_handle *ph);
	स्थिर काष्ठा scmi_sensor_info *(*info_get)
		(स्थिर काष्ठा scmi_protocol_handle *ph, u32 sensor_id);
	पूर्णांक (*trip_poपूर्णांक_config)(स्थिर काष्ठा scmi_protocol_handle *ph,
				 u32 sensor_id, u8 trip_id, u64 trip_value);
	पूर्णांक (*पढ़ोing_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 sensor_id,
			   u64 *value);
	पूर्णांक (*पढ़ोing_get_बारtamped)(स्थिर काष्ठा scmi_protocol_handle *ph,
				       u32 sensor_id, u8 count,
				       काष्ठा scmi_sensor_पढ़ोing *पढ़ोings);
	पूर्णांक (*config_get)(स्थिर काष्ठा scmi_protocol_handle *ph,
			  u32 sensor_id, u32 *sensor_config);
	पूर्णांक (*config_set)(स्थिर काष्ठा scmi_protocol_handle *ph,
			  u32 sensor_id, u32 sensor_config);
पूर्ण;

/**
 * काष्ठा scmi_reset_proto_ops - represents the various operations provided
 *	by SCMI Reset Protocol
 *
 * @num_करोमुख्यs_get: get the count of reset करोमुख्यs provided by SCMI
 * @name_get: माला_लो the name of a reset करोमुख्य
 * @latency_get: माला_लो the reset latency क्रम the specअगरied reset करोमुख्य
 * @reset: resets the specअगरied reset करोमुख्य
 * @निश्चित: explicitly निश्चित reset संकेत of the specअगरied reset करोमुख्य
 * @deनिश्चित: explicitly deनिश्चित reset संकेत of the specअगरied reset करोमुख्य
 */
काष्ठा scmi_reset_proto_ops अणु
	पूर्णांक (*num_करोमुख्यs_get)(स्थिर काष्ठा scmi_protocol_handle *ph);
	अक्षर *(*name_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
	पूर्णांक (*latency_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
	पूर्णांक (*reset)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
	पूर्णांक (*निश्चित)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
	पूर्णांक (*deनिश्चित)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य);
पूर्ण;

/**
 * काष्ठा scmi_voltage_info - describe one available SCMI Voltage Doमुख्य
 *
 * @id: the करोमुख्य ID as advertised by the platक्रमm
 * @segmented: defines the layout of the entries of array @levels_uv.
 *	       - when True the entries are to be पूर्णांकerpreted as triplets,
 *	         each defining a segment representing a range of equally
 *	         space voltages: <lowest_volts>, <highest_volt>, <step_uV>
 *	       - when False the entries simply represent a single discrete
 *	         supported voltage level
 * @negative_volts_allowed: True अगर any of the entries of @levels_uv represent
 *			    a negative voltage.
 * @attributes: represents Voltage Doमुख्य advertised attributes
 * @name: name asचिन्हित to the Voltage Doमुख्य by platक्रमm
 * @num_levels: number of total entries in @levels_uv.
 * @levels_uv: array of entries describing the available voltage levels क्रम
 *	       this करोमुख्य.
 */
काष्ठा scmi_voltage_info अणु
	अचिन्हित पूर्णांक id;
	bool segmented;
	bool negative_volts_allowed;
	अचिन्हित पूर्णांक attributes;
	अक्षर name[SCMI_MAX_STR_SIZE];
	अचिन्हित पूर्णांक num_levels;
#घोषणा SCMI_VOLTAGE_SEGMENT_LOW	0
#घोषणा SCMI_VOLTAGE_SEGMENT_HIGH	1
#घोषणा SCMI_VOLTAGE_SEGMENT_STEP	2
	पूर्णांक *levels_uv;
पूर्ण;

/**
 * काष्ठा scmi_voltage_proto_ops - represents the various operations provided
 * by SCMI Voltage Protocol
 *
 * @num_करोमुख्यs_get: get the count of voltage करोमुख्यs provided by SCMI
 * @info_get: get the inक्रमmation of the specअगरied करोमुख्य
 * @config_set: set the config क्रम the specअगरied करोमुख्य
 * @config_get: get the config of the specअगरied करोमुख्य
 * @level_set: set the voltage level क्रम the specअगरied करोमुख्य
 * @level_get: get the voltage level of the specअगरied करोमुख्य
 */
काष्ठा scmi_voltage_proto_ops अणु
	पूर्णांक (*num_करोमुख्यs_get)(स्थिर काष्ठा scmi_protocol_handle *ph);
	स्थिर काष्ठा scmi_voltage_info __must_check *(*info_get)
		(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id);
	पूर्णांक (*config_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id,
			  u32 config);
#घोषणा	SCMI_VOLTAGE_ARCH_STATE_OFF		0x0
#घोषणा	SCMI_VOLTAGE_ARCH_STATE_ON		0x7
	पूर्णांक (*config_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id,
			  u32 *config);
	पूर्णांक (*level_set)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id,
			 u32 flags, s32 volt_uV);
	पूर्णांक (*level_get)(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य_id,
			 s32 *volt_uV);
पूर्ण;

/**
 * काष्ठा scmi_notअगरy_ops  - represents notअगरications' operations provided by
 * SCMI core
 * @devm_event_notअगरier_रेजिस्टर: Managed registration of a notअगरier_block क्रम
 *				  the requested event
 * @devm_event_notअगरier_unरेजिस्टर: Managed unregistration of a notअगरier_block
 *				    क्रम the requested event
 * @event_notअगरier_रेजिस्टर: Register a notअगरier_block क्रम the requested event
 * @event_notअगरier_unरेजिस्टर: Unरेजिस्टर a notअगरier_block क्रम the requested
 *			       event
 *
 * A user can रेजिस्टर/unरेजिस्टर its own notअगरier_block against the wanted
 * platक्रमm instance regarding the desired event identअगरied by the
 * tuple: (proto_id, evt_id, src_id) using the provided रेजिस्टर/unरेजिस्टर
 * पूर्णांकerface where:
 *
 * @sdev: The scmi_device to use when calling the devres managed ops devm_
 * @handle: The handle identअगरying the platक्रमm instance to use, when not
 *	    calling the managed ops devm_
 * @proto_id: The protocol ID as in SCMI Specअगरication
 * @evt_id: The message ID of the desired event as in SCMI Specअगरication
 * @src_id: A poपूर्णांकer to the desired source ID अगर dअगरferent sources are
 *	    possible क्रम the protocol (like करोमुख्य_id, sensor_id...etc)
 *
 * @src_id can be provided as शून्य अगर it simply करोes NOT make sense क्रम
 * the protocol at hand, OR अगर the user is explicitly पूर्णांकerested in
 * receiving notअगरications from ANY existent source associated to the
 * specअगरied proto_id / evt_id.
 *
 * Received notअगरications are finally delivered to the रेजिस्टरed users,
 * invoking the callback provided with the notअगरier_block *nb as follows:
 *
 *	पूर्णांक user_cb(nb, evt_id, report)
 *
 * with:
 *
 * @nb: The notअगरier block provided by the user
 * @evt_id: The message ID of the delivered event
 * @report: A custom काष्ठा describing the specअगरic event delivered
 */
काष्ठा scmi_notअगरy_ops अणु
	पूर्णांक (*devm_event_notअगरier_रेजिस्टर)(काष्ठा scmi_device *sdev,
					    u8 proto_id, u8 evt_id,
					    स्थिर u32 *src_id,
					    काष्ठा notअगरier_block *nb);
	पूर्णांक (*devm_event_notअगरier_unरेजिस्टर)(काष्ठा scmi_device *sdev,
					      u8 proto_id, u8 evt_id,
					      स्थिर u32 *src_id,
					      काष्ठा notअगरier_block *nb);
	पूर्णांक (*event_notअगरier_रेजिस्टर)(स्थिर काष्ठा scmi_handle *handle,
				       u8 proto_id, u8 evt_id,
				       स्थिर u32 *src_id,
				       काष्ठा notअगरier_block *nb);
	पूर्णांक (*event_notअगरier_unरेजिस्टर)(स्थिर काष्ठा scmi_handle *handle,
					 u8 proto_id, u8 evt_id,
					 स्थिर u32 *src_id,
					 काष्ठा notअगरier_block *nb);
पूर्ण;

/**
 * काष्ठा scmi_handle - Handle वापसed to ARM SCMI clients क्रम usage.
 *
 * @dev: poपूर्णांकer to the SCMI device
 * @version: poपूर्णांकer to the काष्ठाure containing SCMI version inक्रमmation
 * @devm_protocol_get: devres managed method to acquire a protocol and get specअगरic
 *		       operations and a dedicated protocol handler
 * @devm_protocol_put: devres managed method to release a protocol
 * @notअगरy_ops: poपूर्णांकer to set of notअगरications related operations
 */
काष्ठा scmi_handle अणु
	काष्ठा device *dev;
	काष्ठा scmi_revision_info *version;

	स्थिर व्योम __must_check *
		(*devm_protocol_get)(काष्ठा scmi_device *sdev, u8 proto,
				     काष्ठा scmi_protocol_handle **ph);
	व्योम (*devm_protocol_put)(काष्ठा scmi_device *sdev, u8 proto);

	स्थिर काष्ठा scmi_notअगरy_ops *notअगरy_ops;
पूर्ण;

क्रमागत scmi_std_protocol अणु
	SCMI_PROTOCOL_BASE = 0x10,
	SCMI_PROTOCOL_POWER = 0x11,
	SCMI_PROTOCOL_SYSTEM = 0x12,
	SCMI_PROTOCOL_PERF = 0x13,
	SCMI_PROTOCOL_CLOCK = 0x14,
	SCMI_PROTOCOL_SENSOR = 0x15,
	SCMI_PROTOCOL_RESET = 0x16,
	SCMI_PROTOCOL_VOLTAGE = 0x17,
पूर्ण;

क्रमागत scmi_प्रणाली_events अणु
	SCMI_SYSTEM_SHUTDOWN,
	SCMI_SYSTEM_COLDRESET,
	SCMI_SYSTEM_WARMRESET,
	SCMI_SYSTEM_POWERUP,
	SCMI_SYSTEM_SUSPEND,
	SCMI_SYSTEM_MAX
पूर्ण;

काष्ठा scmi_device अणु
	u32 id;
	u8 protocol_id;
	स्थिर अक्षर *name;
	काष्ठा device dev;
	काष्ठा scmi_handle *handle;
पूर्ण;

#घोषणा to_scmi_dev(d) container_of(d, काष्ठा scmi_device, dev)

काष्ठा scmi_device *
scmi_device_create(काष्ठा device_node *np, काष्ठा device *parent, पूर्णांक protocol,
		   स्थिर अक्षर *name);
व्योम scmi_device_destroy(काष्ठा scmi_device *scmi_dev);

काष्ठा scmi_device_id अणु
	u8 protocol_id;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा scmi_driver अणु
	स्थिर अक्षर *name;
	पूर्णांक (*probe)(काष्ठा scmi_device *sdev);
	व्योम (*हटाओ)(काष्ठा scmi_device *sdev);
	स्थिर काष्ठा scmi_device_id *id_table;

	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_scmi_driver(d) container_of(d, काष्ठा scmi_driver, driver)

#अगर IS_REACHABLE(CONFIG_ARM_SCMI_PROTOCOL)
पूर्णांक scmi_driver_रेजिस्टर(काष्ठा scmi_driver *driver,
			 काष्ठा module *owner, स्थिर अक्षर *mod_name);
व्योम scmi_driver_unरेजिस्टर(काष्ठा scmi_driver *driver);
#अन्यथा
अटल अंतरभूत पूर्णांक
scmi_driver_रेजिस्टर(काष्ठा scmi_driver *driver, काष्ठा module *owner,
		     स्थिर अक्षर *mod_name)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम scmi_driver_unरेजिस्टर(काष्ठा scmi_driver *driver) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ARM_SCMI_PROTOCOL */

#घोषणा scmi_रेजिस्टर(driver) \
	scmi_driver_रेजिस्टर(driver, THIS_MODULE, KBUILD_MODNAME)
#घोषणा scmi_unरेजिस्टर(driver) \
	scmi_driver_unरेजिस्टर(driver)

/**
 * module_scmi_driver() - Helper macro क्रम रेजिस्टरing a scmi driver
 * @__scmi_driver: scmi_driver काष्ठाure
 *
 * Helper macro क्रम scmi drivers to set up proper module init / निकास
 * functions.  Replaces module_init() and module_निकास() and keeps people from
 * prपूर्णांकing poपूर्णांकless things to the kernel log when their driver is loaded.
 */
#घोषणा module_scmi_driver(__scmi_driver)	\
	module_driver(__scmi_driver, scmi_रेजिस्टर, scmi_unरेजिस्टर)

/**
 * module_scmi_protocol() - Helper macro क्रम रेजिस्टरing a scmi protocol
 * @__scmi_protocol: scmi_protocol काष्ठाure
 *
 * Helper macro क्रम scmi drivers to set up proper module init / निकास
 * functions.  Replaces module_init() and module_निकास() and keeps people from
 * prपूर्णांकing poपूर्णांकless things to the kernel log when their driver is loaded.
 */
#घोषणा module_scmi_protocol(__scmi_protocol)	\
	module_driver(__scmi_protocol,		\
		      scmi_protocol_रेजिस्टर, scmi_protocol_unरेजिस्टर)

काष्ठा scmi_protocol;
पूर्णांक scmi_protocol_रेजिस्टर(स्थिर काष्ठा scmi_protocol *proto);
व्योम scmi_protocol_unरेजिस्टर(स्थिर काष्ठा scmi_protocol *proto);

/* SCMI Notअगरication API - Custom Event Reports */
क्रमागत scmi_notअगरication_events अणु
	SCMI_EVENT_POWER_STATE_CHANGED = 0x0,
	SCMI_EVENT_PERFORMANCE_LIMITS_CHANGED = 0x0,
	SCMI_EVENT_PERFORMANCE_LEVEL_CHANGED = 0x1,
	SCMI_EVENT_SENSOR_TRIP_POINT_EVENT = 0x0,
	SCMI_EVENT_SENSOR_UPDATE = 0x1,
	SCMI_EVENT_RESET_ISSUED = 0x0,
	SCMI_EVENT_BASE_ERROR_EVENT = 0x0,
	SCMI_EVENT_SYSTEM_POWER_STATE_NOTIFIER = 0x0,
पूर्ण;

काष्ठा scmi_घातer_state_changed_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	करोमुख्य_id;
	अचिन्हित पूर्णांक	घातer_state;
पूर्ण;

काष्ठा scmi_प्रणाली_घातer_state_notअगरier_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	प्रणाली_state;
पूर्ण;

काष्ठा scmi_perf_limits_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	करोमुख्य_id;
	अचिन्हित पूर्णांक	range_max;
	अचिन्हित पूर्णांक	range_min;
पूर्ण;

काष्ठा scmi_perf_level_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	करोमुख्य_id;
	अचिन्हित पूर्णांक	perक्रमmance_level;
पूर्ण;

काष्ठा scmi_sensor_trip_poपूर्णांक_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	sensor_id;
	अचिन्हित पूर्णांक	trip_poपूर्णांक_desc;
पूर्ण;

काष्ठा scmi_sensor_update_report अणु
	kसमय_प्रकार				बारtamp;
	अचिन्हित पूर्णांक			agent_id;
	अचिन्हित पूर्णांक			sensor_id;
	अचिन्हित पूर्णांक			पढ़ोings_count;
	काष्ठा scmi_sensor_पढ़ोing	पढ़ोings[];
पूर्ण;

काष्ठा scmi_reset_issued_report अणु
	kसमय_प्रकार		बारtamp;
	अचिन्हित पूर्णांक	agent_id;
	अचिन्हित पूर्णांक	करोमुख्य_id;
	अचिन्हित पूर्णांक	reset_state;
पूर्ण;

काष्ठा scmi_base_error_report अणु
	kसमय_प्रकार			बारtamp;
	अचिन्हित पूर्णांक		agent_id;
	bool			fatal;
	अचिन्हित पूर्णांक		cmd_count;
	अचिन्हित दीर्घ दीर्घ	reports[];
पूर्ण;

#पूर्ण_अगर /* _LINUX_SCMI_PROTOCOL_H */
