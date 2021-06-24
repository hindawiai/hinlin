<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Helper types to take care of the fact that the DSP card memory
 * is 16 bits, but aligned on a 32 bit PCI boundary
 */

अटल अंतरभूत u16 get_u16(स्थिर u32 __iomem *p)
अणु
	वापस (u16)पढ़ोl(p);
पूर्ण

अटल अंतरभूत व्योम set_u16(u32 __iomem *p, u16 val)
अणु
	ग_लिखोl(val, p);
पूर्ण

अटल अंतरभूत s16 get_s16(स्थिर s32 __iomem *p)
अणु
	वापस (s16)पढ़ोl(p);
पूर्ण

अटल अंतरभूत व्योम set_s16(s32 __iomem *p, s16 val)
अणु
	ग_लिखोl(val, p);
पूर्ण

/*
 * The raw data is stored in a क्रमmat which facilitates rapid
 * processing by the JR3 DSP chip. The raw_channel काष्ठाure shows the
 * क्रमmat क्रम a single channel of data. Each channel takes four,
 * two-byte words.
 *
 * Raw_समय is an अचिन्हित पूर्णांकeger which shows the value of the JR3
 * DSP's पूर्णांकernal घड़ी at the समय the sample was received. The घड़ी
 * runs at 1/10 the JR3 DSP cycle समय. JR3's slowest DSP runs at 10
 * Mhz. At 10 Mhz raw_समय would thereक्रमe घड़ी at 1 Mhz.
 *
 * Raw_data is the raw data received directly from the sensor. The
 * sensor data stream is capable of representing 16 dअगरferent
 * channels. Channel 0 shows the excitation voltage at the sensor. It
 * is used to regulate the voltage over various cable lengths.
 * Channels 1-6 contain the coupled क्रमce data Fx through Mz. Channel
 * 7 contains the sensor's calibration data. The use of channels 8-15
 * varies with dअगरferent sensors.
 */

काष्ठा raw_channel अणु
	u32 raw_समय;
	s32 raw_data;
	s32 reserved[2];
पूर्ण;

/*
 * The क्रमce_array काष्ठाure shows the layout क्रम the decoupled and
 * filtered क्रमce data.
 */
काष्ठा क्रमce_array अणु
	s32 fx;
	s32 fy;
	s32 fz;
	s32 mx;
	s32 my;
	s32 mz;
	s32 v1;
	s32 v2;
पूर्ण;

/*
 * The six_axis_array काष्ठाure shows the layout क्रम the offsets and
 * the full scales.
 */
काष्ठा six_axis_array अणु
	s32 fx;
	s32 fy;
	s32 fz;
	s32 mx;
	s32 my;
	s32 mz;
पूर्ण;

/* VECT_BITS */
/*
 * The vect_bits काष्ठाure shows the layout क्रम indicating
 * which axes to use in computing the vectors. Each bit signअगरies
 * selection of a single axis. The V1x axis bit corresponds to a hex
 * value of 0x0001 and the V2z bit corresponds to a hex value of
 * 0x0020. Example: to specअगरy the axes V1x, V1y, V2x, and V2z the
 * pattern would be 0x002b. Vector 1 शेषs to a क्रमce vector and
 * vector 2 शेषs to a moment vector. It is possible to change one
 * or the other so that two क्रमce vectors or two moment vectors are
 * calculated. Setting the changeV1 bit or the changeV2 bit will
 * change that vector to be the opposite of its शेष. Thereक्रमe to
 * have two क्रमce vectors, set changeV1 to 1.
 */

/* vect_bits appears to be unused at this समय */
क्रमागत अणु
	fx = 0x0001,
	fy = 0x0002,
	fz = 0x0004,
	mx = 0x0008,
	my = 0x0010,
	mz = 0x0020,
	changeV2 = 0x0040,
	changeV1 = 0x0080
पूर्ण;

/* WARNING_BITS */
/*
 * The warning_bits काष्ठाure shows the bit pattern क्रम the warning
 * word. The bit fields are shown from bit 0 (lsb) to bit 15 (msb).
 */

/* XX_NEAR_SET */
/*
 * The xx_near_sat bits signअगरy that the indicated axis has reached or
 * exceeded the near saturation value.
 */

क्रमागत अणु
	fx_near_sat = 0x0001,
	fy_near_sat = 0x0002,
	fz_near_sat = 0x0004,
	mx_near_sat = 0x0008,
	my_near_sat = 0x0010,
	mz_near_sat = 0x0020
पूर्ण;

/* ERROR_BITS */
/* XX_SAT */
/* MEMORY_ERROR */
/* SENSOR_CHANGE */

/*
 * The error_bits काष्ठाure shows the bit pattern क्रम the error word.
 * The bit fields are shown from bit 0 (lsb) to bit 15 (msb). The
 * xx_sat bits signअगरy that the indicated axis has reached or exceeded
 * the saturation value. The memory_error bit indicates that a problem
 * was detected in the on-board RAM during the घातer-up
 * initialization. The sensor_change bit indicates that a sensor other
 * than the one originally plugged in has passed its CRC check. This
 * bit latches, and must be reset by the user.
 *
 */

/* SYSTEM_BUSY */

/*
 * The प्रणाली_busy bit indicates that the JR3 DSP is currently busy
 * and is not calculating क्रमce data. This occurs when a new
 * coordinate transक्रमmation, or new sensor full scale is set by the
 * user. A very fast प्रणाली using the क्रमce data क्रम feedback might
 * become unstable during the approximately 4 ms needed to accomplish
 * these calculations. This bit will also become active when a new
 * sensor is plugged in and the प्रणाली needs to recalculate the
 * calibration CRC.
 */

/* CAL_CRC_BAD */

/*
 * The cal_crc_bad bit indicates that the calibration CRC has not
 * calculated to zero. CRC is लघु क्रम cyclic redundancy code. It is
 * a method क्रम determining the पूर्णांकegrity of messages in data
 * communication. The calibration data stored inside the sensor is
 * transmitted to the JR3 DSP aदीर्घ with the sensor data. The
 * calibration data has a CRC attached to the end of it, to assist in
 * determining the completeness and पूर्णांकegrity of the calibration data
 * received from the sensor. There are two reasons the CRC may not
 * have calculated to zero. The first is that all the calibration data
 * has not yet been received, the second is that the calibration data
 * has been corrupted. A typical sensor transmits the entire contents
 * of its calibration matrix over 30 बार a second. Thereक्रमe, अगर
 * this bit is not zero within a couple of seconds after the sensor
 * has been plugged in, there is a problem with the sensor's
 * calibration data.
 */

/* WATCH_DOG */
/* WATCH_DOG2 */

/*
 * The watch_करोg and watch_करोg2 bits are sensor, not processor, watch
 * करोg bits. Watch_करोg indicates that the sensor data line seems to be
 * acting correctly, जबतक watch_करोg2 indicates that sensor data and
 * घड़ी are being received. It is possible क्रम watch_करोg2 to go off
 * जबतक watch_करोg करोes not. This would indicate an improper घड़ी
 * संकेत, जबतक data is acting correctly. If either watch करोg barks,
 * the sensor data is not being received correctly.
 */

क्रमागत error_bits_t अणु
	fx_sat = 0x0001,
	fy_sat = 0x0002,
	fz_sat = 0x0004,
	mx_sat = 0x0008,
	my_sat = 0x0010,
	mz_sat = 0x0020,
	memory_error = 0x0400,
	sensor_change = 0x0800,
	प्रणाली_busy = 0x1000,
	cal_crc_bad = 0x2000,
	watch_करोg2 = 0x4000,
	watch_करोg = 0x8000
पूर्ण;

/* THRESH_STRUCT */

/*
 * This काष्ठाure shows the layout क्रम a single threshold packet inside of a
 * load envelope. Each load envelope can contain several threshold काष्ठाures.
 * 1. data_address contains the address of the data क्रम that threshold. This
 *    includes filtered, unfiltered, raw, rate, counters, error and warning data
 * 2. threshold is the is the value at which, अगर data is above or below, the
 *    bits will be set ... (pag.24).
 * 3. bit_pattern contains the bits that will be set अगर the threshold value is
 *    met or exceeded.
 */

काष्ठा thresh_काष्ठा अणु
	s32 data_address;
	s32 threshold;
	s32 bit_pattern;
पूर्ण;

/* LE_STRUCT */

/*
 * Layout of a load enveloped packet. Four thresholds are showed ... क्रम more
 * see manual (pag.25)
 * 1. latch_bits is a bit pattern that show which bits the user wants to latch.
 *    The latched bits will not be reset once the threshold which set them is
 *    no दीर्घer true. In that हाल the user must reset them using the reset_bit
 *    command.
 * 2. number_of_xx_thresholds specअगरy how many GE/LE threshold there are.
 */
काष्ठा le_काष्ठा अणु
	s32 latch_bits;
	s32 number_of_ge_thresholds;
	s32 number_of_le_thresholds;
	काष्ठा thresh_काष्ठा thresholds[4];
	s32 reserved;
पूर्ण;

/* LINK_TYPES */
/*
 * Link types is an क्रमागतerated value showing the dअगरferent possible transक्रमm
 * link types.
 * 0 - end transक्रमm packet
 * 1 - translate aदीर्घ X axis (TX)
 * 2 - translate aदीर्घ Y axis (TY)
 * 3 - translate aदीर्घ Z axis (TZ)
 * 4 - rotate about X axis (RX)
 * 5 - rotate about Y axis (RY)
 * 6 - rotate about Z axis (RZ)
 * 7 - negate all axes (NEG)
 */

क्रमागत link_types अणु
	end_x_क्रमm,
	tx,
	ty,
	tz,
	rx,
	ry,
	rz,
	neg
पूर्ण;

/* TRANSFORM */
/* Structure used to describe a transक्रमm. */
काष्ठा पूर्णांकern_transक्रमm अणु
	काष्ठा अणु
		u32 link_type;
		s32 link_amount;
	पूर्ण link[8];
पूर्ण;

/*
 * JR3 क्रमce/torque sensor data definition. For more inक्रमmation see sensor
 * and hardware manuals.
 */

काष्ठा jr3_sensor अणु
	/*
	 * Raw_channels is the area used to store the raw data coming from
	 * the sensor.
	 */

	काष्ठा raw_channel raw_channels[16];	/* offset 0x0000 */

	/*
	 * Copyright is a null terminated ASCII string containing the JR3
	 * copyright notice.
	 */

	u32 copyright[0x0018];	/* offset 0x0040 */
	s32 reserved1[0x0008];	/* offset 0x0058 */

	/*
	 * Shunts contains the sensor shunt पढ़ोings. Some JR3 sensors have
	 * the ability to have their gains adjusted. This allows the
	 * hardware full scales to be adjusted to potentially allow
	 * better resolution or dynamic range. For sensors that have
	 * this ability, the gain of each sensor channel is measured at
	 * the समय of calibration using a shunt resistor. The shunt
	 * resistor is placed across one arm of the resistor bridge, and
	 * the resulting change in the output of that channel is
	 * measured. This measurement is called the shunt पढ़ोing, and
	 * is recorded here. If the user has changed the gain of the //
	 * sensor, and made new shunt measurements, those shunt
	 * measurements can be placed here. The JR3 DSP will then scale
	 * the calibration matrix such so that the gains are again
	 * proper क्रम the indicated shunt पढ़ोings. If shunts is 0, then
	 * the sensor cannot have its gain changed. For details on
	 * changing the sensor gain, and making shunts पढ़ोings, please
	 * see the sensor manual. To make these values take effect the
	 * user must call either command (5) use transक्रमm # (pg. 33) or
	 * command (10) set new full scales (pg. 38).
	 */

	काष्ठा six_axis_array shunts;		/* offset 0x0060 */
	s32 reserved2[2];			/* offset 0x0066 */

	/*
	 * Default_FS contains the full scale that is used अगर the user करोes
	 * not set a full scale.
	 */

	काष्ठा six_axis_array शेष_FS;	/* offset 0x0068 */
	s32 reserved3;				/* offset 0x006e */

	/*
	 * Load_envelope_num is the load envelope number that is currently
	 * in use. This value is set by the user after one of the load
	 * envelopes has been initialized.
	 */

	s32 load_envelope_num;			/* offset 0x006f */

	/* Min_full_scale is the recommend minimum full scale. */

	/*
	 * These values in conjunction with max_full_scale (pg. 9) helps
	 * determine the appropriate value क्रम setting the full scales. The
	 * software allows the user to set the sensor full scale to an
	 * arbitrary value. But setting the full scales has some hazards. If
	 * the full scale is set too low, the data will saturate
	 * prematurely, and dynamic range will be lost. If the full scale is
	 * set too high, then resolution is lost as the data is shअगरted to
	 * the right and the least signअगरicant bits are lost. Thereक्रमe the
	 * maximum full scale is the maximum value at which no resolution is
	 * lost, and the minimum full scale is the value at which the data
	 * will not saturate prematurely. These values are calculated
	 * whenever a new coordinate transक्रमmation is calculated. It is
	 * possible क्रम the recommended maximum to be less than the
	 * recommended minimum. This comes about primarily when using
	 * coordinate translations. If this is the हाल, it means that any
	 * full scale selection will be a compromise between dynamic range
	 * and resolution. It is usually recommended to compromise in favor
	 * of resolution which means that the recommend maximum full scale
	 * should be chosen.
	 *
	 * WARNING: Be sure that the full scale is no less than 0.4% of the
	 * recommended minimum full scale. Full scales below this value will
	 * cause erroneous results.
	 */

	काष्ठा six_axis_array min_full_scale;	/* offset 0x0070 */
	s32 reserved4;				/* offset 0x0076 */

	/*
	 * Transक्रमm_num is the transक्रमm number that is currently in use.
	 * This value is set by the JR3 DSP after the user has used command
	 * (5) use transक्रमm # (pg. 33).
	 */

	s32 transक्रमm_num;			/* offset 0x0077 */

	/*
	 * Max_full_scale is the recommended maximum full scale.
	 * See min_full_scale (pg. 9) क्रम more details.
	 */

	काष्ठा six_axis_array max_full_scale;	/* offset 0x0078 */
	s32 reserved5;				/* offset 0x007e */

	/*
	 * Peak_address is the address of the data which will be monitored
	 * by the peak routine. This value is set by the user. The peak
	 * routine will monitor any 8 contiguous addresses क्रम peak values.
	 * (ex. to watch filter3 data क्रम peaks, set this value to 0x00a8).
	 */

	s32 peak_address;			/* offset 0x007f */

	/*
	 * Full_scale is the sensor full scales which are currently in use.
	 * Decoupled and filtered data is scaled so that +/- 16384 is equal
	 * to the full scales. The engineering units used are indicated by
	 * the units value discussed on page 16. The full scales क्रम Fx, Fy,
	 * Fz, Mx, My and Mz can be written by the user prior to calling
	 * command (10) set new full scales (pg. 38). The full scales क्रम V1
	 * and V2 are set whenever the full scales are changed or when the
	 * axes used to calculate the vectors are changed. The full scale of
	 * V1 and V2 will always be equal to the largest full scale of the
	 * axes used क्रम each vector respectively.
	 */

	काष्ठा क्रमce_array full_scale;		/* offset 0x0080 */

	/*
	 * Offsets contains the sensor offsets. These values are subtracted from
	 * the sensor data to obtain the decoupled data. The offsets are set a
	 * few seconds (< 10) after the calibration data has been received.
	 * They are set so that the output data will be zero. These values
	 * can be written as well as पढ़ो. The JR3 DSP will use the values
	 * written here within 2 ms of being written. To set future
	 * decoupled data to zero, add these values to the current decoupled
	 * data values and place the sum here. The JR3 DSP will change these
	 * values when a new transक्रमm is applied. So अगर the offsets are
	 * such that FX is 5 and all other values are zero, after rotating
	 * about Z by 90 degrees, FY would be 5 and all others would be zero.
	 */

	काष्ठा six_axis_array offsets;		/* offset 0x0088 */

	/*
	 * Offset_num is the number of the offset currently in use. This
	 * value is set by the JR3 DSP after the user has executed the use
	 * offset # command (pg. 34). It can vary between 0 and 15.
	 */

	s32 offset_num;				/* offset 0x008e */

	/*
	 * Vect_axes is a bit map showing which of the axes are being used
	 * in the vector calculations. This value is set by the JR3 DSP
	 * after the user has executed the set vector axes command (pg. 37).
	 */

	u32 vect_axes;				/* offset 0x008f */

	/*
	 * Filter0 is the decoupled, unfiltered data from the JR3 sensor.
	 * This data has had the offsets हटाओd.
	 *
	 * These क्रमce_arrays hold the filtered data. The decoupled data is
	 * passed through cascaded low pass filters. Each succeeding filter
	 * has a cutoff frequency of 1/4 of the preceding filter. The cutoff
	 * frequency of filter1 is 1/16 of the sample rate from the sensor.
	 * For a typical sensor with a sample rate of 8 kHz, the cutoff
	 * frequency of filter1 would be 500 Hz. The following filters would
	 * cutoff at 125 Hz, 31.25 Hz, 7.813 Hz, 1.953 Hz and 0.4883 Hz.
	 */

	काष्ठा क्रमce_array filter[7];		/*
						 * offset 0x0090,
						 * offset 0x0098,
						 * offset 0x00a0,
						 * offset 0x00a8,
						 * offset 0x00b0,
						 * offset 0x00b8,
						 * offset 0x00c0
						 */

	/*
	 * Rate_data is the calculated rate data. It is a first derivative
	 * calculation. It is calculated at a frequency specअगरied by the
	 * variable rate_भागisor (pg. 12). The data on which the rate is
	 * calculated is specअगरied by the variable rate_address (pg. 12).
	 */

	काष्ठा क्रमce_array rate_data;		/* offset 0x00c8 */

	/*
	 * Minimum_data & maximum_data are the minimum and maximum (peak)
	 * data values. The JR3 DSP can monitor any 8 contiguous data items
	 * क्रम minimums and maximums at full sensor bandwidth. This area is
	 * only updated at user request. This is करोne so that the user करोes
	 * not miss any peaks. To पढ़ो the data, use either the पढ़ो peaks
	 * command (pg. 40), or the पढ़ो and reset peaks command (pg. 39).
	 * The address of the data to watch क्रम peaks is stored in the
	 * variable peak_address (pg. 10). Peak data is lost when executing
	 * a coordinate transक्रमmation or a full scale change. Peak data is
	 * also lost when plugging in a new sensor.
	 */

	काष्ठा क्रमce_array minimum_data;	/* offset 0x00d0 */
	काष्ठा क्रमce_array maximum_data;	/* offset 0x00d8 */

	/*
	 * Near_sat_value & sat_value contain the value used to determine अगर
	 * the raw sensor is saturated. Because of decoupling and offset
	 * removal, it is dअगरficult to tell from the processed data अगर the
	 * sensor is saturated. These values, in conjunction with the error
	 * and warning words (pg. 14), provide this critical inक्रमmation.
	 * These two values may be set by the host processor. These values
	 * are positive चिन्हित values, since the saturation logic uses the
	 * असलolute values of the raw data. The near_sat_value शेषs to
	 * approximately 80% of the ADC's full scale, which is 26214, जबतक
	 * sat_value शेषs to the ADC's full scale:
	 *
	 *   sat_value = 32768 - 2^(16 - ADC bits)
	 */

	s32 near_sat_value;			/* offset 0x00e0 */
	s32 sat_value;				/* offset 0x00e1 */

	/*
	 * Rate_address, rate_भागisor & rate_count contain the data used to
	 * control the calculations of the rates. Rate_address is the
	 * address of the data used क्रम the rate calculation. The JR3 DSP
	 * will calculate rates क्रम any 8 contiguous values (ex. to
	 * calculate rates क्रम filter3 data set rate_address to 0x00a8).
	 * Rate_भागisor is how often the rate is calculated. If rate_भागisor
	 * is 1, the rates are calculated at full sensor bandwidth. If
	 * rate_भागisor is 200, rates are calculated every 200 samples.
	 * Rate_भागisor can be any value between 1 and 65536. Set
	 * rate_भागisor to 0 to calculate rates every 65536 samples.
	 * Rate_count starts at zero and counts until it equals
	 * rate_भागisor, at which poपूर्णांक the rates are calculated, and
	 * rate_count is reset to 0. When setting a new rate भागisor, it is
	 * a good idea to set rate_count to one less than rate भागisor. This
	 * will minimize the समय necessary to start the rate calculations.
	 */

	s32 rate_address;			/* offset 0x00e2 */
	u32 rate_भागisor;			/* offset 0x00e3 */
	u32 rate_count;				/* offset 0x00e4 */

	/*
	 * Command_word2 through command_word0 are the locations used to
	 * send commands to the JR3 DSP. Their usage varies with the command
	 * and is detailed later in the Command Definitions section (pg.
	 * 29). In general the user places values पूर्णांकo various memory
	 * locations, and then places the command word पूर्णांकo command_word0.
	 * The JR3 DSP will process the command and place a 0 पूर्णांकo
	 * command_word0 to indicate successful completion. Alternatively
	 * the JR3 DSP will place a negative number पूर्णांकo command_word0 to
	 * indicate an error condition. Please note the command locations
	 * are numbered backwards. (I.E. command_word2 comes beक्रमe
	 * command_word1).
	 */

	s32 command_word2;			/* offset 0x00e5 */
	s32 command_word1;			/* offset 0x00e6 */
	s32 command_word0;			/* offset 0x00e7 */

	/*
	 * Count1 through count6 are अचिन्हित counters which are incremented
	 * every समय the matching filters are calculated. Filter1 is
	 * calculated at the sensor data bandwidth. So this counter would
	 * increment at 8 kHz क्रम a typical sensor. The rest of the counters
	 * are incremented at 1/4 the पूर्णांकerval of the counter immediately
	 * preceding it, so they would count at 2 kHz, 500 Hz, 125 Hz etc.
	 * These counters can be used to रुको क्रम data. Each समय the
	 * counter changes, the corresponding data set can be sampled, and
	 * this will insure that the user माला_लो each sample, once, and only
	 * once.
	 */

	u32 count1;				/* offset 0x00e8 */
	u32 count2;				/* offset 0x00e9 */
	u32 count3;				/* offset 0x00ea */
	u32 count4;				/* offset 0x00eb */
	u32 count5;				/* offset 0x00ec */
	u32 count6;				/* offset 0x00ed */

	/*
	 * Error_count is a running count of data reception errors. If this
	 * counter is changing rapidly, it probably indicates a bad sensor
	 * cable connection or other hardware problem. In most installations
	 * error_count should not change at all. But it is possible in an
	 * extremely noisy environment to experience occasional errors even
	 * without a hardware problem. If the sensor is well grounded, this
	 * is probably unaव्योमable in these environments. On the occasions
	 * where this counter counts a bad sample, that sample is ignored.
	 */

	u32 error_count;			/* offset 0x00ee */

	/*
	 * Count_x is a counter which is incremented every समय the JR3 DSP
	 * searches its job queues and finds nothing to करो. It indicates the
	 * amount of idle समय the JR3 DSP has available. It can also be
	 * used to determine अगर the JR3 DSP is alive. See the Perक्रमmance
	 * Issues section on pg. 49 क्रम more details.
	 */

	u32 count_x;				/* offset 0x00ef */

	/*
	 * Warnings & errors contain the warning and error bits
	 * respectively. The क्रमmat of these two words is discussed on page
	 * 21 under the headings warnings_bits and error_bits.
	 */

	u32 warnings;				/* offset 0x00f0 */
	u32 errors;				/* offset 0x00f1 */

	/*
	 * Threshold_bits is a word containing the bits that are set by the
	 * load envelopes. See load_envelopes (pg. 17) and thresh_काष्ठा
	 * (pg. 23) क्रम more details.
	 */

	s32 threshold_bits;			/* offset 0x00f2 */

	/*
	 * Last_crc is the value that shows the actual calculated CRC. CRC
	 * is लघु क्रम cyclic redundancy code. It should be zero. See the
	 * description क्रम cal_crc_bad (pg. 21) क्रम more inक्रमmation.
	 */

	s32 last_CRC;				/* offset 0x00f3 */

	/*
	 * EEProm_ver_no contains the version number of the sensor EEProm.
	 * EEProm version numbers can vary between 0 and 255.
	 * Software_ver_no contains the software version number. Version
	 * 3.02 would be stored as 302.
	 */

	s32 eeprom_ver_no;			/* offset 0x00f4 */
	s32 software_ver_no;			/* offset 0x00f5 */

	/*
	 * Software_day & software_year are the release date of the software
	 * the JR3 DSP is currently running. Day is the day of the year,
	 * with January 1 being 1, and December 31, being 365 क्रम non leap
	 * years.
	 */

	s32 software_day;			/* offset 0x00f6 */
	s32 software_year;			/* offset 0x00f7 */

	/*
	 * Serial_no & model_no are the two values which uniquely identअगरy a
	 * sensor. This model number करोes not directly correspond to the JR3
	 * model number, but it will provide a unique identअगरier क्रम
	 * dअगरferent sensor configurations.
	 */

	u32 serial_no;				/* offset 0x00f8 */
	u32 model_no;				/* offset 0x00f9 */

	/*
	 * Cal_day & cal_year are the sensor calibration date. Day is the
	 * day of the year, with January 1 being 1, and December 31, being
	 * 366 क्रम leap years.
	 */

	s32 cal_day;				/* offset 0x00fa */
	s32 cal_year;				/* offset 0x00fb */

	/*
	 * Units is an क्रमागतerated पढ़ो only value defining the engineering
	 * units used in the sensor full scale. The meanings of particular
	 * values are discussed in the section detailing the क्रमce_units
	 * काष्ठाure on page 22. The engineering units are setto customer
	 * specअगरications during sensor manufacture and cannot be changed by
	 * writing to Units.
	 *
	 * Bits contains the number of bits of resolution of the ADC
	 * currently in use.
	 *
	 * Channels is a bit field showing which channels the current sensor
	 * is capable of sending. If bit 0 is active, this sensor can send
	 * channel 0, अगर bit 13 is active, this sensor can send channel 13,
	 * etc. This bit can be active, even अगर the sensor is not currently
	 * sending this channel. Some sensors are configurable as to which
	 * channels to send, and this field only contains inक्रमmation on the
	 * channels available to send, not on the current configuration. To
	 * find which channels are currently being sent, monitor the
	 * Raw_समय fields (pg. 19) in the raw_channels array (pg. 7). If
	 * the समय is changing periodically, then that channel is being
	 * received.
	 */

	u32 units;				/* offset 0x00fc */
	s32 bits;				/* offset 0x00fd */
	s32 channels;				/* offset 0x00fe */

	/*
	 * Thickness specअगरies the overall thickness of the sensor from
	 * flange to flange. The engineering units क्रम this value are
	 * contained in units (pg. 16). The sensor calibration is relative
	 * to the center of the sensor. This value allows easy coordinate
	 * transक्रमmation from the center of the sensor to either flange.
	 */

	s32 thickness;				/* offset 0x00ff */

	/*
	 * Load_envelopes is a table containing the load envelope
	 * descriptions. There are 16 possible load envelope slots in the
	 * table. The slots are on 16 word boundaries and are numbered 0-15.
	 * Each load envelope needs to start at the beginning of a slot but
	 * need not be fully contained in that slot. That is to say that a
	 * single load envelope can be larger than a single slot. The
	 * software has been tested and ran satisfactorily with 50
	 * thresholds active. A single load envelope this large would take
	 * up 5 of the 16 slots. The load envelope data is laid out in an
	 * order that is most efficient क्रम the JR3 DSP. The काष्ठाure is
	 * detailed later in the section showing the definition of the
	 * le_काष्ठा काष्ठाure (pg. 23).
	 */

	काष्ठा le_काष्ठा load_envelopes[0x10];	/* offset 0x0100 */

	/*
	 * Transक्रमms is a table containing the transक्रमm descriptions.
	 * There are 16 possible transक्रमm slots in the table. The slots are
	 * on 16 word boundaries and are numbered 0-15. Each transक्रमm needs
	 * to start at the beginning of a slot but need not be fully
	 * contained in that slot. That is to say that a single transक्रमm
	 * can be larger than a single slot. A transक्रमm is 2 * no of links
	 * + 1 words in length. So a single slot can contain a transक्रमm
	 * with 7 links. Two slots can contain a transक्रमm that is 15 links.
	 * The layout is detailed later in the section showing the
	 * definition of the transक्रमm काष्ठाure (pg. 26).
	 */

	काष्ठा पूर्णांकern_transक्रमm transक्रमms[0x10];	/* offset 0x0200 */
पूर्ण;

काष्ठा jr3_block अणु
	u32 program_lo[0x4000];		/*  0x00000 - 0x10000 */
	काष्ठा jr3_sensor sensor;	/*  0x10000 - 0x10c00 */
	अक्षर pad2[0x30000 - 0x00c00];	/*  0x10c00 - 0x40000 */
	u32 program_hi[0x8000];		/*  0x40000 - 0x60000 */
	u32 reset;			/*  0x60000 - 0x60004 */
	अक्षर pad3[0x20000 - 0x00004];	/*  0x60004 - 0x80000 */
पूर्ण;
