<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/input/adxl34x.h
 *
 * Digital Accelerometer अक्षरacteristics are highly application specअगरic
 * and may vary between boards and models. The platक्रमm_data क्रम the
 * device's "struct device" holds this inक्रमmation.
 *
 * Copyright 2009 Analog Devices Inc.
 */

#अगर_अघोषित __LINUX_INPUT_ADXL34X_H__
#घोषणा __LINUX_INPUT_ADXL34X_H__

#समावेश <linux/input.h>

काष्ठा adxl34x_platक्रमm_data अणु

	/*
	 * X,Y,Z Axis Offset:
	 * offer user offset adjusपंचांगents in twoscompliment
	 * क्रमm with a scale factor of 15.6 mg/LSB (i.e. 0x7F = +2 g)
	 */

	s8 x_axis_offset;
	s8 y_axis_offset;
	s8 z_axis_offset;

	/*
	 * TAP_X/Y/Z Enable: Setting TAP_X, Y, or Z Enable enables X,
	 * Y, or Z participation in Tap detection. A '0' excludes the
	 * selected axis from participation in Tap detection.
	 * Setting the SUPPRESS bit suppresses Double Tap detection अगर
	 * acceleration greater than tap_threshold is present during the
	 * tap_latency period, i.e. after the first tap but beक्रमe the
	 * खोलोing of the second tap winकरोw.
	 */

#घोषणा ADXL_SUPPRESS	(1 << 3)
#घोषणा ADXL_TAP_X_EN	(1 << 2)
#घोषणा ADXL_TAP_Y_EN	(1 << 1)
#घोषणा ADXL_TAP_Z_EN	(1 << 0)

	u8 tap_axis_control;

	/*
	 * tap_threshold:
	 * holds the threshold value क्रम tap detection/पूर्णांकerrupts.
	 * The data क्रमmat is अचिन्हित. The scale factor is 62.5 mg/LSB
	 * (i.e. 0xFF = +16 g). A zero value may result in undesirable
	 * behavior अगर Tap/Double Tap is enabled.
	 */

	u8 tap_threshold;

	/*
	 * tap_duration:
	 * is an अचिन्हित समय value representing the maximum
	 * समय that an event must be above the tap_threshold threshold
	 * to qualअगरy as a tap event. The scale factor is 625 us/LSB. A zero
	 * value will prevent Tap/Double Tap functions from working.
	 */

	u8 tap_duration;

	/*
	 * tap_latency:
	 * is an अचिन्हित समय value representing the रुको समय
	 * from the detection of a tap event to the खोलोing of the समय
	 * winकरोw tap_winकरोw क्रम a possible second tap event. The scale
	 * factor is 1.25 ms/LSB. A zero value will disable the Double Tap
	 * function.
	 */

	u8 tap_latency;

	/*
	 * tap_winकरोw:
	 * is an अचिन्हित समय value representing the amount
	 * of समय after the expiration of tap_latency during which a second
	 * tap can begin. The scale factor is 1.25 ms/LSB. A zero value will
	 * disable the Double Tap function.
	 */

	u8 tap_winकरोw;

	/*
	 * act_axis_control:
	 * X/Y/Z Enable: A '1' enables X, Y, or Z participation in activity
	 * or inactivity detection. A '0' excludes the selected axis from
	 * participation. If all of the axes are excluded, the function is
	 * disabled.
	 * AC/DC: A '0' = DC coupled operation and a '1' = AC coupled
	 * operation. In DC coupled operation, the current acceleration is
	 * compared with activity_threshold and inactivity_threshold directly
	 * to determine whether activity or inactivity is detected. In AC
	 * coupled operation क्रम activity detection, the acceleration value
	 * at the start of activity detection is taken as a reference value.
	 * New samples of acceleration are then compared to this
	 * reference value and अगर the magnitude of the dअगरference exceeds
	 * activity_threshold the device will trigger an activity पूर्णांकerrupt. In
	 * AC coupled operation क्रम inactivity detection, a reference value
	 * is used again क्रम comparison and is updated whenever the
	 * device exceeds the inactivity threshold. Once the reference
	 * value is selected, the device compares the magnitude of the
	 * dअगरference between the reference value and the current
	 * acceleration with inactivity_threshold. If the dअगरference is below
	 * inactivity_threshold क्रम a total of inactivity_समय, the device is
	 * considered inactive and the inactivity पूर्णांकerrupt is triggered.
	 */

#घोषणा ADXL_ACT_ACDC		(1 << 7)
#घोषणा ADXL_ACT_X_EN		(1 << 6)
#घोषणा ADXL_ACT_Y_EN		(1 << 5)
#घोषणा ADXL_ACT_Z_EN		(1 << 4)
#घोषणा ADXL_INACT_ACDC		(1 << 3)
#घोषणा ADXL_INACT_X_EN		(1 << 2)
#घोषणा ADXL_INACT_Y_EN		(1 << 1)
#घोषणा ADXL_INACT_Z_EN		(1 << 0)

	u8 act_axis_control;

	/*
	 * activity_threshold:
	 * holds the threshold value क्रम activity detection.
	 * The data क्रमmat is अचिन्हित. The scale factor is
	 * 62.5 mg/LSB. A zero value may result in undesirable behavior अगर
	 * Activity पूर्णांकerrupt is enabled.
	 */

	u8 activity_threshold;

	/*
	 * inactivity_threshold:
	 * holds the threshold value क्रम inactivity
	 * detection. The data क्रमmat is अचिन्हित. The scale
	 * factor is 62.5 mg/LSB. A zero value may result in undesirable
	 * behavior अगर Inactivity पूर्णांकerrupt is enabled.
	 */

	u8 inactivity_threshold;

	/*
	 * inactivity_समय:
	 * is an अचिन्हित समय value representing the
	 * amount of समय that acceleration must be below the value in
	 * inactivity_threshold क्रम inactivity to be declared. The scale factor
	 * is 1 second/LSB. Unlike the other पूर्णांकerrupt functions, which
	 * operate on unfiltered data, the inactivity function operates on the
	 * filtered output data. At least one output sample must be
	 * generated क्रम the inactivity पूर्णांकerrupt to be triggered. This will
	 * result in the function appearing un-responsive अगर the
	 * inactivity_समय रेजिस्टर is set with a value less than the समय
	 * स्थिरant of the Output Data Rate. A zero value will result in an
	 * पूर्णांकerrupt when the output data is below inactivity_threshold.
	 */

	u8 inactivity_समय;

	/*
	 * मुक्त_fall_threshold:
	 * holds the threshold value क्रम Free-Fall detection.
	 * The data क्रमmat is अचिन्हित. The root-sum-square(RSS) value
	 * of all axes is calculated and compared to the value in
	 * मुक्त_fall_threshold to determine अगर a मुक्त fall event may be
	 * occurring.  The scale factor is 62.5 mg/LSB. A zero value may
	 * result in undesirable behavior अगर Free-Fall पूर्णांकerrupt is
	 * enabled. Values between 300 and 600 mg (0x05 to 0x09) are
	 * recommended.
	 */

	u8 मुक्त_fall_threshold;

	/*
	 * मुक्त_fall_समय:
	 * is an अचिन्हित समय value representing the minimum
	 * समय that the RSS value of all axes must be less than
	 * मुक्त_fall_threshold to generate a Free-Fall पूर्णांकerrupt. The
	 * scale factor is 5 ms/LSB. A zero value may result in
	 * undesirable behavior अगर Free-Fall पूर्णांकerrupt is enabled.
	 * Values between 100 to 350 ms (0x14 to 0x46) are recommended.
	 */

	u8 मुक्त_fall_समय;

	/*
	 * data_rate:
	 * Selects device bandwidth and output data rate.
	 * RATE = 3200 Hz / (2^(15 - x)). Default value is 0x0A, or 100 Hz
	 * Output Data Rate. An Output Data Rate should be selected that
	 * is appropriate क्रम the communication protocol and frequency
	 * selected. Selecting too high of an Output Data Rate with a low
	 * communication speed will result in samples being discarded.
	 */

	u8 data_rate;

	/*
	 * data_range:
	 * FULL_RES: When this bit is set with the device is
	 * in Full-Resolution Mode, where the output resolution increases
	 * with RANGE to मुख्यtain a 4 mg/LSB scale factor. When this
	 * bit is cleared the device is in 10-bit Mode and RANGE determine the
	 * maximum g-Range and scale factor.
	 */

#घोषणा ADXL_FULL_RES		(1 << 3)
#घोषणा ADXL_RANGE_PM_2g	0
#घोषणा ADXL_RANGE_PM_4g	1
#घोषणा ADXL_RANGE_PM_8g	2
#घोषणा ADXL_RANGE_PM_16g	3

	u8 data_range;

	/*
	 * low_घातer_mode:
	 * A '0' = Normal operation and a '1' = Reduced
	 * घातer operation with somewhat higher noise.
	 */

	u8 low_घातer_mode;

	/*
	 * घातer_mode:
	 * LINK: A '1' with both the activity and inactivity functions
	 * enabled will delay the start of the activity function until
	 * inactivity is detected. Once activity is detected, inactivity
	 * detection will begin and prevent the detection of activity. This
	 * bit serially links the activity and inactivity functions. When '0'
	 * the inactivity and activity functions are concurrent. Additional
	 * inक्रमmation can be found in the ADXL34x datasheet's Application
	 * section under Link Mode.
	 * AUTO_SLEEP: A '1' sets the ADXL34x to चयन to Sleep Mode
	 * when inactivity (acceleration has been below inactivity_threshold
	 * क्रम at least inactivity_समय) is detected and the LINK bit is set.
	 * A '0' disables स्वतःmatic चयनing to Sleep Mode. See the
	 * Sleep Bit section of the ADXL34x datasheet क्रम more inक्रमmation.
	 */

#घोषणा ADXL_LINK	(1 << 5)
#घोषणा ADXL_AUTO_SLEEP	(1 << 4)

	u8 घातer_mode;

	/*
	 * fअगरo_mode:
	 * BYPASS The FIFO is bypassed
	 * FIFO   FIFO collects up to 32 values then stops collecting data
	 * STREAM FIFO holds the last 32 data values. Once full, the FIFO's
	 *        oldest data is lost as it is replaced with newer data
	 *
	 * DEFAULT should be ADXL_FIFO_STREAM
	 */

#घोषणा ADXL_FIFO_BYPASS	0
#घोषणा ADXL_FIFO_FIFO		1
#घोषणा ADXL_FIFO_STREAM	2

	u8 fअगरo_mode;

	/*
	 * watermark:
	 * The Watermark feature can be used to reduce the पूर्णांकerrupt load
	 * of the प्रणाली. The FIFO fills up to the value stored in watermark
	 * [1..32] and then generates an पूर्णांकerrupt.
	 * A '0' disables the watermark feature.
	 */

	u8 watermark;

	/*
	 * When acceleration measurements are received from the ADXL34x
	 * events are sent to the event subप्रणाली. The following settings
	 * select the event type and event code क्रम new x, y and z axis data
	 * respectively.
	 */
	u32 ev_type;	/* EV_ABS or EV_REL */

	u32 ev_code_x;	/* ABS_X,Y,Z or REL_X,Y,Z */
	u32 ev_code_y;	/* ABS_X,Y,Z or REL_X,Y,Z */
	u32 ev_code_z;	/* ABS_X,Y,Z or REL_X,Y,Z */

	/*
	 * A valid BTN or KEY Code; use tap_axis_control to disable
	 * event reporting
	 */

	u32 ev_code_tap[3];	/* EV_KEY अणुX-Axis, Y-Axis, Z-Axisपूर्ण */

	/*
	 * A valid BTN or KEY Code क्रम Free-Fall or Activity enables
	 * input event reporting. A '0' disables the Free-Fall or
	 * Activity reporting.
	 */

	u32 ev_code_ff;	/* EV_KEY */
	u32 ev_code_act_inactivity;	/* EV_KEY */

	/*
	 * Use ADXL34x INT2 pin instead of INT1 pin क्रम पूर्णांकerrupt output
	 */
	u8 use_पूर्णांक2;

	/*
	 * ADXL346 only ORIENTATION SENSING feature
	 * The orientation function of the ADXL346 reports both 2-D and
	 * 3-D orientation concurrently.
	 */

#घोषणा ADXL_EN_ORIENTATION_2D		1
#घोषणा ADXL_EN_ORIENTATION_3D		2
#घोषणा ADXL_EN_ORIENTATION_2D_3D	3

	u8 orientation_enable;

	/*
	 * The width of the deadzone region between two or more
	 * orientation positions is determined by setting the Deadzone
	 * value. The deadzone region size can be specअगरied with a
	 * resolution of 3.6deg. The deadzone angle represents the total
	 * angle where the orientation is considered invalid.
	 */

#घोषणा ADXL_DEADZONE_ANGLE_0p0		0	/* !!!0.0 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_3p6		1	/* 3.6 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_7p2		2	/* 7.2 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_10p8	3	/* 10.8 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_14p4	4	/* 14.4 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_18p0	5	/* 18.0 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_21p6	6	/* 21.6 [deg] */
#घोषणा ADXL_DEADZONE_ANGLE_25p2	7	/* 25.2 [deg] */

	u8 deadzone_angle;

	/*
	 * To eliminate most human motion such as walking or shaking,
	 * a Divisor value should be selected to effectively limit the
	 * orientation bandwidth. Set the depth of the filter used to
	 * low-pass filter the measured acceleration क्रम stable
	 * orientation sensing
	 */

#घोषणा ADXL_LP_FILTER_DIVISOR_2	0
#घोषणा ADXL_LP_FILTER_DIVISOR_4	1
#घोषणा ADXL_LP_FILTER_DIVISOR_8	2
#घोषणा ADXL_LP_FILTER_DIVISOR_16	3
#घोषणा ADXL_LP_FILTER_DIVISOR_32	4
#घोषणा ADXL_LP_FILTER_DIVISOR_64	5
#घोषणा ADXL_LP_FILTER_DIVISOR_128	6
#घोषणा ADXL_LP_FILTER_DIVISOR_256	7

	u8 भागisor_length;

	u32 ev_codes_orient_2d[4];	/* EV_KEY अणु+X, -X, +Y, -Yपूर्ण */
	u32 ev_codes_orient_3d[6];	/* EV_KEY अणु+Z, +Y, +X, -X, -Y, -Zपूर्ण */
पूर्ण;
#पूर्ण_अगर
