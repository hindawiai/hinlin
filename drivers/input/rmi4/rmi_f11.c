<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2015 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश "rmi_driver.h"
#समावेश "rmi_2d_sensor.h"

#घोषणा F11_MAX_NUM_OF_FINGERS		10
#घोषणा F11_MAX_NUM_OF_TOUCH_SHAPES	16

#घोषणा FINGER_STATE_MASK	0x03

#घोषणा F11_CTRL_SENSOR_MAX_X_POS_OFFSET	6
#घोषणा F11_CTRL_SENSOR_MAX_Y_POS_OFFSET	8

#घोषणा DEFAULT_XY_MAX 9999
#घोषणा DEFAULT_MAX_ABS_MT_PRESSURE 255
#घोषणा DEFAULT_MAX_ABS_MT_TOUCH 15
#घोषणा DEFAULT_MAX_ABS_MT_ORIENTATION 1
#घोषणा DEFAULT_MIN_ABS_MT_TRACKING_ID 1
#घोषणा DEFAULT_MAX_ABS_MT_TRACKING_ID 10

/*
 * A note about RMI4 F11 रेजिस्टर काष्ठाure.
 *
 * The properties क्रम a given sensor are described by its query रेजिस्टरs.  The
 * number of query रेजिस्टरs and the layout of their contents are described by
 * the F11 device queries as well as the sensor query inक्रमmation.
 *
 * Similarly, each sensor has control रेजिस्टरs that govern its behavior.  The
 * size and layout of the control रेजिस्टरs क्रम a given sensor can be determined
 * by parsing that sensors query रेजिस्टरs.
 *
 * And in a likewise fashion, each sensor has data रेजिस्टरs where it reports
 * its touch data and other पूर्णांकeresting stuff.  The size and layout of a
 * sensors data रेजिस्टरs must be determined by parsing its query रेजिस्टरs.
 *
 * The लघु story is that we need to पढ़ो and parse a lot of query
 * रेजिस्टरs in order to determine the attributes of a sensor. Then
 * we need to use that data to compute the size of the control and data
 * रेजिस्टरs क्रम sensor.
 *
 * The end result is that we have a number of काष्ठाs that aren't used to
 * directly generate the input events, but their size, location and contents
 * are critical to determining where the data we are पूर्णांकerested in lives.
 *
 * At this समय, the driver करोes not yet comprehend all possible F11
 * configuration options, but it should be sufficient to cover 99% of RMI4 F11
 * devices currently in the field.
 */

/* maximum ABS_MT_POSITION displacement (in mm) */
#घोषणा DMAX 10

/*
 * Writing this to the F11 command रेजिस्टर will cause the sensor to
 * calibrate to the current capacitive state.
 */
#घोषणा RMI_F11_REZERO  0x01

#घोषणा RMI_F11_HAS_QUERY9              (1 << 3)
#घोषणा RMI_F11_HAS_QUERY11             (1 << 4)
#घोषणा RMI_F11_HAS_QUERY12             (1 << 5)
#घोषणा RMI_F11_HAS_QUERY27             (1 << 6)
#घोषणा RMI_F11_HAS_QUERY28             (1 << 7)

/** Defs क्रम Query 1 */

#घोषणा RMI_F11_NR_FINGERS_MASK 0x07
#घोषणा RMI_F11_HAS_REL                 (1 << 3)
#घोषणा RMI_F11_HAS_ABS                 (1 << 4)
#घोषणा RMI_F11_HAS_GESTURES            (1 << 5)
#घोषणा RMI_F11_HAS_SENSITIVITY_ADJ     (1 << 6)
#घोषणा RMI_F11_CONFIGURABLE            (1 << 7)

/** Defs क्रम Query 2, 3, and 4. */
#घोषणा RMI_F11_NR_ELECTRODES_MASK      0x7F

/** Defs क्रम Query 5 */

#घोषणा RMI_F11_ABS_DATA_SIZE_MASK      0x03
#घोषणा RMI_F11_HAS_ANCHORED_FINGER     (1 << 2)
#घोषणा RMI_F11_HAS_ADJ_HYST            (1 << 3)
#घोषणा RMI_F11_HAS_DRIBBLE             (1 << 4)
#घोषणा RMI_F11_HAS_BENDING_CORRECTION  (1 << 5)
#घोषणा RMI_F11_HAS_LARGE_OBJECT_SUPPRESSION    (1 << 6)
#घोषणा RMI_F11_HAS_JITTER_FILTER       (1 << 7)

/** Defs क्रम Query 7 */
#घोषणा RMI_F11_HAS_SINGLE_TAP                  (1 << 0)
#घोषणा RMI_F11_HAS_TAP_AND_HOLD                (1 << 1)
#घोषणा RMI_F11_HAS_DOUBLE_TAP                  (1 << 2)
#घोषणा RMI_F11_HAS_EARLY_TAP                   (1 << 3)
#घोषणा RMI_F11_HAS_FLICK                       (1 << 4)
#घोषणा RMI_F11_HAS_PRESS                       (1 << 5)
#घोषणा RMI_F11_HAS_PINCH                       (1 << 6)
#घोषणा RMI_F11_HAS_CHIRAL                      (1 << 7)

/** Defs क्रम Query 8 */
#घोषणा RMI_F11_HAS_PALM_DET                    (1 << 0)
#घोषणा RMI_F11_HAS_ROTATE                      (1 << 1)
#घोषणा RMI_F11_HAS_TOUCH_SHAPES                (1 << 2)
#घोषणा RMI_F11_HAS_SCROLL_ZONES                (1 << 3)
#घोषणा RMI_F11_HAS_INDIVIDUAL_SCROLL_ZONES     (1 << 4)
#घोषणा RMI_F11_HAS_MF_SCROLL                   (1 << 5)
#घोषणा RMI_F11_HAS_MF_EDGE_MOTION              (1 << 6)
#घोषणा RMI_F11_HAS_MF_SCROLL_INERTIA           (1 << 7)

/** Defs क्रम Query 9. */
#घोषणा RMI_F11_HAS_PEN                         (1 << 0)
#घोषणा RMI_F11_HAS_PROXIMITY                   (1 << 1)
#घोषणा RMI_F11_HAS_PALM_DET_SENSITIVITY        (1 << 2)
#घोषणा RMI_F11_HAS_SUPPRESS_ON_PALM_DETECT     (1 << 3)
#घोषणा RMI_F11_HAS_TWO_PEN_THRESHOLDS          (1 << 4)
#घोषणा RMI_F11_HAS_CONTACT_GEOMETRY            (1 << 5)
#घोषणा RMI_F11_HAS_PEN_HOVER_DISCRIMINATION    (1 << 6)
#घोषणा RMI_F11_HAS_PEN_FILTERS                 (1 << 7)

/** Defs क्रम Query 10. */
#घोषणा RMI_F11_NR_TOUCH_SHAPES_MASK            0x1F

/** Defs क्रम Query 11 */

#घोषणा RMI_F11_HAS_Z_TUNING                    (1 << 0)
#घोषणा RMI_F11_HAS_ALGORITHM_SELECTION         (1 << 1)
#घोषणा RMI_F11_HAS_W_TUNING                    (1 << 2)
#घोषणा RMI_F11_HAS_PITCH_INFO                  (1 << 3)
#घोषणा RMI_F11_HAS_FINGER_SIZE                 (1 << 4)
#घोषणा RMI_F11_HAS_SEGMENTATION_AGGRESSIVENESS (1 << 5)
#घोषणा RMI_F11_HAS_XY_CLIP                     (1 << 6)
#घोषणा RMI_F11_HAS_DRUMMING_FILTER             (1 << 7)

/** Defs क्रम Query 12. */

#घोषणा RMI_F11_HAS_GAPLESS_FINGER              (1 << 0)
#घोषणा RMI_F11_HAS_GAPLESS_FINGER_TUNING       (1 << 1)
#घोषणा RMI_F11_HAS_8BIT_W                      (1 << 2)
#घोषणा RMI_F11_HAS_ADJUSTABLE_MAPPING          (1 << 3)
#घोषणा RMI_F11_HAS_INFO2                       (1 << 4)
#घोषणा RMI_F11_HAS_PHYSICAL_PROPS              (1 << 5)
#घोषणा RMI_F11_HAS_FINGER_LIMIT                (1 << 6)
#घोषणा RMI_F11_HAS_LINEAR_COEFF                (1 << 7)

/** Defs क्रम Query 13. */

#घोषणा RMI_F11_JITTER_WINDOW_MASK              0x1F
#घोषणा RMI_F11_JITTER_FILTER_MASK              0x60
#घोषणा RMI_F11_JITTER_FILTER_SHIFT             5

/** Defs क्रम Query 14. */
#घोषणा RMI_F11_LIGHT_CONTROL_MASK              0x03
#घोषणा RMI_F11_IS_CLEAR                        (1 << 2)
#घोषणा RMI_F11_CLICKPAD_PROPS_MASK             0x18
#घोषणा RMI_F11_CLICKPAD_PROPS_SHIFT            3
#घोषणा RMI_F11_MOUSE_BUTTONS_MASK              0x60
#घोषणा RMI_F11_MOUSE_BUTTONS_SHIFT             5
#घोषणा RMI_F11_HAS_ADVANCED_GESTURES           (1 << 7)

#घोषणा RMI_F11_QUERY_SIZE                      4
#घोषणा RMI_F11_QUERY_GESTURE_SIZE              2

#घोषणा F11_LIGHT_CTL_NONE 0x00
#घोषणा F11_LUXPAD	   0x01
#घोषणा F11_DUAL_MODE      0x02

#घोषणा F11_NOT_CLICKPAD     0x00
#घोषणा F11_HINGED_CLICKPAD  0x01
#घोषणा F11_UNIFORM_CLICKPAD 0x02

/**
 * काष्ठा f11_2d_sensor_queries - describes sensor capabilities
 *
 * Query रेजिस्टरs 1 through 4 are always present.
 *
 * @nr_fingers: describes the maximum number of fingers the 2-D sensor
 *	supports.
 * @has_rel: the sensor supports relative motion reporting.
 * @has_असल: the sensor supports असलolute poition reporting.
 * @has_gestures: the sensor supports gesture reporting.
 * @has_sensitivity_adjust: the sensor supports a global sensitivity
 *	adjusपंचांगent.
 * @configurable: the sensor supports various configuration options.
 * @nr_x_electrodes:  the maximum number of electrodes the 2-D sensor
 *	supports on the X axis.
 * @nr_y_electrodes:  the maximum number of electrodes the 2-D sensor
 *	supports on the Y axis.
 * @max_electrodes: the total number of X and Y electrodes that may be
 *	configured.
 *
 * Query 5 is present अगर the has_असल bit is set.
 *
 * @असल_data_size: describes the क्रमmat of data reported by the असलolute
 *	data source.  Only one क्रमmat (the kind used here) is supported at this
 *	समय.
 * @has_anchored_finger: then the sensor supports the high-precision second
 *	finger tracking provided by the manual tracking and motion sensitivity
 *	options.
 * @has_adj_hyst: the dअगरference between the finger release threshold and
 *	the touch threshold.
 * @has_dribble: the sensor supports the generation of dribble पूर्णांकerrupts,
 *	which may be enabled or disabled with the dribble control bit.
 * @has_bending_correction: Bending related data रेजिस्टरs 28 and 36, and
 *	control रेजिस्टर 52..57 are present.
 * @has_large_object_suppression: control रेजिस्टर 58 and data रेजिस्टर 28
 *	exist.
 * @has_jitter_filter: query 13 and control 73..76 exist.
 *
 * Query 6 is present अगर the has_rel it is set.
 *
 * @f11_2d_query6: this रेजिस्टर is reserved.
 *
 * Gesture inक्रमmation queries 7 and 8 are present अगर has_gestures bit is set.
 *
 * @has_single_tap: a basic single-tap gesture is supported.
 * @has_tap_n_hold: tap-and-hold gesture is supported.
 * @has_द्विगुन_tap: द्विगुन-tap gesture is supported.
 * @has_early_tap: early tap is supported and reported as soon as the finger
 *	lअगरts क्रम any tap event that could be पूर्णांकerpreted as either a single
 *	tap or as the first tap of a द्विगुन-tap or tap-and-hold gesture.
 * @has_flick: flick detection is supported.
 * @has_press: press gesture reporting is supported.
 * @has_pinch: pinch gesture detection is supported.
 * @has_chiral: chiral (circular) scrolling  gesture detection is supported.
 * @has_palm_det: the 2-D sensor notअगरies the host whenever a large conductive
 *	object such as a palm or a cheek touches the 2-D sensor.
 * @has_rotate: rotation gesture detection is supported.
 * @has_touch_shapes: TouchShapes are supported.  A TouchShape is a fixed
 *	rectangular area on the sensor that behaves like a capacitive button.
 * @has_scroll_zones: scrolling areas near the sensor edges are supported.
 * @has_inभागidual_scroll_zones: अगर 1, then 4 scroll zones are supported;
 *	अगर 0, then only two are supported.
 * @has_mf_scroll: the multअगरinger_scrolling bit will be set when
 *	more than one finger is involved in a scrolling action.
 * @has_mf_edge_motion: indicates whether multi-finger edge motion gesture
 *	is supported.
 * @has_mf_scroll_inertia: indicates whether multi-finger scroll inertia
 *	feature is supported.
 *
 * Convenience क्रम checking bytes in the gesture info रेजिस्टरs.  This is करोne
 * often enough that we put it here to declutter the conditionals
 *
 * @query7_nonzero: true अगर none of the query 7 bits are set
 * @query8_nonzero: true अगर none of the query 8 bits are set
 *
 * Query 9 is present अगर the has_query9 is set.
 *
 * @has_pen: detection of a stylus is supported and रेजिस्टरs F11_2D_Ctrl20
 *	and F11_2D_Ctrl21 exist.
 * @has_proximity: detection of fingers near the sensor is supported and
 *	रेजिस्टरs F11_2D_Ctrl22 through F11_2D_Ctrl26 exist.
 * @has_palm_det_sensitivity:  the sensor supports the palm detect sensitivity
 *	feature and रेजिस्टर F11_2D_Ctrl27 exists.
 * @has_suppress_on_palm_detect: the device supports the large object detect
 *	suppression feature and रेजिस्टर F11_2D_Ctrl27 exists.
 * @has_two_pen_thresholds: अगर has_pen is also set, then F11_2D_Ctrl35 exists.
 * @has_contact_geometry: the sensor supports the use of contact geometry to
 *	map असलolute X and Y target positions and रेजिस्टरs F11_2D_Data18
 *	through F11_2D_Data27 exist.
 * @has_pen_hover_discrimination: अगर has_pen is also set, then रेजिस्टरs
 *	F11_2D_Data29 through F11_2D_Data31, F11_2D_Ctrl68.*, F11_2D_Ctrl69
 *	and F11_2D_Ctrl72 exist.
 * @has_pen_filters: अगर has_pen is also set, then रेजिस्टरs F11_2D_Ctrl70 and
 *	F11_2D_Ctrl71 exist.
 *
 * Touch shape info (query 10) is present अगर has_touch_shapes is set.
 *
 * @nr_touch_shapes: the total number of touch shapes supported.
 *
 * Query 11 is present अगर the has_query11 bit is set in query 0.
 *
 * @has_z_tuning: अगर set, the sensor supports Z tuning and रेजिस्टरs
 *	F11_2D_Ctrl29 through F11_2D_Ctrl33 exist.
 * @has_algorithm_selection: controls choice of noise suppression algorithm
 * @has_w_tuning: the sensor supports Wx and Wy scaling and रेजिस्टरs
 *	F11_2D_Ctrl36 through F11_2D_Ctrl39 exist.
 * @has_pitch_info: the X and Y pitches of the sensor electrodes can be
 *	configured and रेजिस्टरs F11_2D_Ctrl40 and F11_2D_Ctrl41 exist.
 * @has_finger_size: the शेष finger width settings क्रम the sensor
 *	can be configured and रेजिस्टरs F11_2D_Ctrl42 through F11_2D_Ctrl44
 *	exist.
 * @has_segmentation_aggressiveness: the sensorै s ability to distinguish
 *	multiple objects बंद together can be configured and रेजिस्टर
 *	F11_2D_Ctrl45 exists.
 * @has_XY_clip: the inactive outside borders of the sensor can be
 *	configured and रेजिस्टरs F11_2D_Ctrl46 through F11_2D_Ctrl49 exist.
 * @has_drumming_filter: the sensor can be configured to distinguish
 *	between a fast flick and a quick drumming movement and रेजिस्टरs
 *	F11_2D_Ctrl50 and F11_2D_Ctrl51 exist.
 *
 * Query 12 is present अगर hasQuery12 bit is set.
 *
 * @has_gapless_finger: control रेजिस्टरs relating to gapless finger are
 *	present.
 * @has_gapless_finger_tuning: additional control and data रेजिस्टरs relating
 *	to gapless finger are present.
 * @has_8bit_w: larger W value reporting is supported.
 * @has_adjustable_mapping: TBD
 * @has_info2: the general info query14 is present
 * @has_physical_props: additional queries describing the physical properties
 *	of the sensor are present.
 * @has_finger_limit: indicates that F11 Ctrl 80 exists.
 * @has_linear_coeff_2: indicates that F11 Ctrl 81 exists.
 *
 * Query 13 is present अगर Query 5's has_jitter_filter bit is set.
 *
 * @jitter_winकरोw_size: used by Design Studio 4.
 * @jitter_filter_type: used by Design Studio 4.
 *
 * Query 14 is present अगर query 12's has_general_info2 flag is set.
 *
 * @light_control: Indicates what light/led control features are present,
 *	अगर any.
 * @is_clear: अगर set, this is a clear sensor (indicating direct poपूर्णांकing
 *	application), otherwise it's opaque (indicating indirect poपूर्णांकing).
 * @clickpad_props: specअगरies अगर this is a clickpad, and अगर so what sort of
 *	mechanism it uses
 * @mouse_buttons: specअगरies the number of mouse buttons present (अगर any).
 * @has_advanced_gestures: advanced driver gestures are supported.
 *
 * @x_sensor_size_mm: size of the sensor in millimeters on the X axis.
 * @y_sensor_size_mm: size of the sensor in millimeters on the Y axis.
 */
काष्ठा f11_2d_sensor_queries अणु
	/* query1 */
	u8 nr_fingers;
	bool has_rel;
	bool has_असल;
	bool has_gestures;
	bool has_sensitivity_adjust;
	bool configurable;

	/* query2 */
	u8 nr_x_electrodes;

	/* query3 */
	u8 nr_y_electrodes;

	/* query4 */
	u8 max_electrodes;

	/* query5 */
	u8 असल_data_size;
	bool has_anchored_finger;
	bool has_adj_hyst;
	bool has_dribble;
	bool has_bending_correction;
	bool has_large_object_suppression;
	bool has_jitter_filter;

	u8 f11_2d_query6;

	/* query 7 */
	bool has_single_tap;
	bool has_tap_n_hold;
	bool has_द्विगुन_tap;
	bool has_early_tap;
	bool has_flick;
	bool has_press;
	bool has_pinch;
	bool has_chiral;

	bool query7_nonzero;

	/* query 8 */
	bool has_palm_det;
	bool has_rotate;
	bool has_touch_shapes;
	bool has_scroll_zones;
	bool has_inभागidual_scroll_zones;
	bool has_mf_scroll;
	bool has_mf_edge_motion;
	bool has_mf_scroll_inertia;

	bool query8_nonzero;

	/* Query 9 */
	bool has_pen;
	bool has_proximity;
	bool has_palm_det_sensitivity;
	bool has_suppress_on_palm_detect;
	bool has_two_pen_thresholds;
	bool has_contact_geometry;
	bool has_pen_hover_discrimination;
	bool has_pen_filters;

	/* Query 10 */
	u8 nr_touch_shapes;

	/* Query 11. */
	bool has_z_tuning;
	bool has_algorithm_selection;
	bool has_w_tuning;
	bool has_pitch_info;
	bool has_finger_size;
	bool has_segmentation_aggressiveness;
	bool has_XY_clip;
	bool has_drumming_filter;

	/* Query 12 */
	bool has_gapless_finger;
	bool has_gapless_finger_tuning;
	bool has_8bit_w;
	bool has_adjustable_mapping;
	bool has_info2;
	bool has_physical_props;
	bool has_finger_limit;
	bool has_linear_coeff_2;

	/* Query 13 */
	u8 jitter_winकरोw_size;
	u8 jitter_filter_type;

	/* Query 14 */
	u8 light_control;
	bool is_clear;
	u8 clickpad_props;
	u8 mouse_buttons;
	bool has_advanced_gestures;

	/* Query 15 - 18 */
	u16 x_sensor_size_mm;
	u16 y_sensor_size_mm;
पूर्ण;

/* Defs क्रम Ctrl0. */
#घोषणा RMI_F11_REPORT_MODE_MASK        0x07
#घोषणा RMI_F11_REPORT_MODE_CONTINUOUS  (0 << 0)
#घोषणा RMI_F11_REPORT_MODE_REDUCED     (1 << 0)
#घोषणा RMI_F11_REPORT_MODE_FS_CHANGE   (2 << 0)
#घोषणा RMI_F11_REPORT_MODE_FP_CHANGE   (3 << 0)
#घोषणा RMI_F11_ABS_POS_FILT            (1 << 3)
#घोषणा RMI_F11_REL_POS_FILT            (1 << 4)
#घोषणा RMI_F11_REL_BALLISTICS          (1 << 5)
#घोषणा RMI_F11_DRIBBLE                 (1 << 6)
#घोषणा RMI_F11_REPORT_BEYOND_CLIP      (1 << 7)

/* Defs क्रम Ctrl1. */
#घोषणा RMI_F11_PALM_DETECT_THRESH_MASK 0x0F
#घोषणा RMI_F11_MOTION_SENSITIVITY_MASK 0x30
#घोषणा RMI_F11_MANUAL_TRACKING         (1 << 6)
#घोषणा RMI_F11_MANUAL_TRACKED_FINGER   (1 << 7)

#घोषणा RMI_F11_DELTA_X_THRESHOLD       2
#घोषणा RMI_F11_DELTA_Y_THRESHOLD       3

#घोषणा RMI_F11_CTRL_REG_COUNT          12

काष्ठा f11_2d_ctrl अणु
	u8              ctrl0_11[RMI_F11_CTRL_REG_COUNT];
	u16             ctrl0_11_address;
पूर्ण;

#घोषणा RMI_F11_ABS_BYTES 5
#घोषणा RMI_F11_REL_BYTES 2

/* Defs क्रम Data 8 */

#घोषणा RMI_F11_SINGLE_TAP              (1 << 0)
#घोषणा RMI_F11_TAP_AND_HOLD            (1 << 1)
#घोषणा RMI_F11_DOUBLE_TAP              (1 << 2)
#घोषणा RMI_F11_EARLY_TAP               (1 << 3)
#घोषणा RMI_F11_FLICK                   (1 << 4)
#घोषणा RMI_F11_PRESS                   (1 << 5)
#घोषणा RMI_F11_PINCH                   (1 << 6)

/* Defs क्रम Data 9 */

#घोषणा RMI_F11_PALM_DETECT                     (1 << 0)
#घोषणा RMI_F11_ROTATE                          (1 << 1)
#घोषणा RMI_F11_SHAPE                           (1 << 2)
#घोषणा RMI_F11_SCROLLZONE                      (1 << 3)
#घोषणा RMI_F11_GESTURE_FINGER_COUNT_MASK       0x70

/** Handy poपूर्णांकers पूर्णांकo our data buffer.
 *
 * @f_state - start of finger state रेजिस्टरs.
 * @असल_pos - start of असलolute position रेजिस्टरs (अगर present).
 * @rel_pos - start of relative data रेजिस्टरs (अगर present).
 * @gest_1  - gesture flags (अगर present).
 * @gest_2  - gesture flags & finger count (अगर present).
 * @pinch   - pinch motion रेजिस्टर (अगर present).
 * @flick   - flick distance X & Y, flick समय (अगर present).
 * @rotate  - rotate motion and finger separation.
 * @multi_scroll - chiral deltas क्रम X and Y (अगर present).
 * @scroll_zones - scroll deltas क्रम 4 regions (अगर present).
 */
काष्ठा f11_2d_data अणु
	u8	*f_state;
	u8	*असल_pos;
	s8	*rel_pos;
	u8	*gest_1;
	u8	*gest_2;
	s8	*pinch;
	u8	*flick;
	u8	*rotate;
	u8	*shapes;
	s8	*multi_scroll;
	s8	*scroll_zones;
पूर्ण;

/** Data pertaining to F11 in general.  For per-sensor data, see काष्ठा
 * f11_2d_sensor.
 *
 * @dev_query - F11 device specअगरic query रेजिस्टरs.
 * @dev_controls - F11 device specअगरic control रेजिस्टरs.
 * @dev_controls_mutex - lock क्रम the control रेजिस्टरs.
 * @rezero_रुको_ms - अगर nonzero, upon resume we will रुको this many
 * milliseconds beक्रमe rezeroing the sensor(s).  This is useful in प्रणालीs with
 * poor electrical behavior on resume, where the initial calibration of the
 * sensor(s) coming out of sleep state may be bogus.
 * @sensors - per sensor data काष्ठाures.
 */
काष्ठा f11_data अणु
	bool has_query9;
	bool has_query11;
	bool has_query12;
	bool has_query27;
	bool has_query28;
	bool has_acm;
	काष्ठा f11_2d_ctrl dev_controls;
	काष्ठा mutex dev_controls_mutex;
	u16 rezero_रुको_ms;
	काष्ठा rmi_2d_sensor sensor;
	काष्ठा f11_2d_sensor_queries sens_query;
	काष्ठा f11_2d_data data;
	काष्ठा rmi_2d_sensor_platक्रमm_data sensor_pdata;
	अचिन्हित दीर्घ *असल_mask;
	अचिन्हित दीर्घ *rel_mask;
पूर्ण;

क्रमागत f11_finger_state अणु
	F11_NO_FINGER	= 0x00,
	F11_PRESENT	= 0x01,
	F11_INACCURATE	= 0x02,
	F11_RESERVED	= 0x03
पूर्ण;

अटल व्योम rmi_f11_rel_pos_report(काष्ठा f11_data *f11, u8 n_finger)
अणु
	काष्ठा rmi_2d_sensor *sensor = &f11->sensor;
	काष्ठा f11_2d_data *data = &f11->data;
	s8 x, y;

	x = data->rel_pos[n_finger * RMI_F11_REL_BYTES];
	y = data->rel_pos[n_finger * RMI_F11_REL_BYTES + 1];

	rmi_2d_sensor_rel_report(sensor, x, y);
पूर्ण

अटल व्योम rmi_f11_असल_pos_process(काष्ठा f11_data *f11,
				   काष्ठा rmi_2d_sensor *sensor,
				   काष्ठा rmi_2d_sensor_असल_object *obj,
				   क्रमागत f11_finger_state finger_state,
				   u8 n_finger)
अणु
	काष्ठा f11_2d_data *data = &f11->data;
	u8 *pos_data = &data->असल_pos[n_finger * RMI_F11_ABS_BYTES];
	पूर्णांक tool_type = MT_TOOL_FINGER;

	चयन (finger_state) अणु
	हाल F11_PRESENT:
		obj->type = RMI_2D_OBJECT_FINGER;
		अवरोध;
	शेष:
		obj->type = RMI_2D_OBJECT_NONE;
	पूर्ण

	obj->mt_tool = tool_type;
	obj->x = (pos_data[0] << 4) | (pos_data[2] & 0x0F);
	obj->y = (pos_data[1] << 4) | (pos_data[2] >> 4);
	obj->z = pos_data[4];
	obj->wx = pos_data[3] & 0x0f;
	obj->wy = pos_data[3] >> 4;

	rmi_2d_sensor_असल_process(sensor, obj, n_finger);
पूर्ण

अटल अंतरभूत u8 rmi_f11_parse_finger_state(स्थिर u8 *f_state, u8 n_finger)
अणु
	वापस (f_state[n_finger / 4] >> (2 * (n_finger % 4))) &
							FINGER_STATE_MASK;
पूर्ण

अटल व्योम rmi_f11_finger_handler(काष्ठा f11_data *f11,
				   काष्ठा rmi_2d_sensor *sensor, पूर्णांक size)
अणु
	स्थिर u8 *f_state = f11->data.f_state;
	u8 finger_state;
	u8 i;
	पूर्णांक असल_fingers;
	पूर्णांक rel_fingers;
	पूर्णांक असल_size = sensor->nbr_fingers * RMI_F11_ABS_BYTES;

	अगर (sensor->report_असल) अणु
		अगर (असल_size > size)
			असल_fingers = size / RMI_F11_ABS_BYTES;
		अन्यथा
			असल_fingers = sensor->nbr_fingers;

		क्रम (i = 0; i < असल_fingers; i++) अणु
			/* Possible of having 4 fingers per f_state रेजिस्टर */
			finger_state = rmi_f11_parse_finger_state(f_state, i);
			अगर (finger_state == F11_RESERVED) अणु
				pr_err("Invalid finger state[%d]: 0x%02x", i,
					finger_state);
				जारी;
			पूर्ण

			rmi_f11_असल_pos_process(f11, sensor, &sensor->objs[i],
							finger_state, i);
		पूर्ण

		/*
		 * the असलolute part is made in 2 parts to allow the kernel
		 * tracking to take place.
		 */
		अगर (sensor->kernel_tracking)
			input_mt_assign_slots(sensor->input,
					      sensor->tracking_slots,
					      sensor->tracking_pos,
					      sensor->nbr_fingers,
					      sensor->dmax);

		क्रम (i = 0; i < असल_fingers; i++) अणु
			finger_state = rmi_f11_parse_finger_state(f_state, i);
			अगर (finger_state == F11_RESERVED)
				/* no need to send twice the error */
				जारी;

			rmi_2d_sensor_असल_report(sensor, &sensor->objs[i], i);
		पूर्ण

		input_mt_sync_frame(sensor->input);
	पूर्ण अन्यथा अगर (sensor->report_rel) अणु
		अगर ((असल_size + sensor->nbr_fingers * RMI_F11_REL_BYTES) > size)
			rel_fingers = (size - असल_size) / RMI_F11_REL_BYTES;
		अन्यथा
			rel_fingers = sensor->nbr_fingers;

		क्रम (i = 0; i < rel_fingers; i++)
			rmi_f11_rel_pos_report(f11, i);
	पूर्ण

पूर्ण

अटल पूर्णांक f11_2d_स्थिरruct_data(काष्ठा f11_data *f11)
अणु
	काष्ठा rmi_2d_sensor *sensor = &f11->sensor;
	काष्ठा f11_2d_sensor_queries *query = &f11->sens_query;
	काष्ठा f11_2d_data *data = &f11->data;
	पूर्णांक i;

	sensor->nbr_fingers = (query->nr_fingers == 5 ? 10 :
				query->nr_fingers + 1);

	sensor->pkt_size = DIV_ROUND_UP(sensor->nbr_fingers, 4);

	अगर (query->has_असल) अणु
		sensor->pkt_size += (sensor->nbr_fingers * 5);
		sensor->attn_size = sensor->pkt_size;
	पूर्ण

	अगर (query->has_rel)
		sensor->pkt_size +=  (sensor->nbr_fingers * 2);

	/* Check अगर F11_2D_Query7 is non-zero */
	अगर (query->query7_nonzero)
		sensor->pkt_size += माप(u8);

	/* Check अगर F11_2D_Query7 or F11_2D_Query8 is non-zero */
	अगर (query->query7_nonzero || query->query8_nonzero)
		sensor->pkt_size += माप(u8);

	अगर (query->has_pinch || query->has_flick || query->has_rotate) अणु
		sensor->pkt_size += 3;
		अगर (!query->has_flick)
			sensor->pkt_size--;
		अगर (!query->has_rotate)
			sensor->pkt_size--;
	पूर्ण

	अगर (query->has_touch_shapes)
		sensor->pkt_size +=
			DIV_ROUND_UP(query->nr_touch_shapes + 1, 8);

	sensor->data_pkt = devm_kzalloc(&sensor->fn->dev, sensor->pkt_size,
					GFP_KERNEL);
	अगर (!sensor->data_pkt)
		वापस -ENOMEM;

	data->f_state = sensor->data_pkt;
	i = DIV_ROUND_UP(sensor->nbr_fingers, 4);

	अगर (query->has_असल) अणु
		data->असल_pos = &sensor->data_pkt[i];
		i += (sensor->nbr_fingers * RMI_F11_ABS_BYTES);
	पूर्ण

	अगर (query->has_rel) अणु
		data->rel_pos = &sensor->data_pkt[i];
		i += (sensor->nbr_fingers * RMI_F11_REL_BYTES);
	पूर्ण

	अगर (query->query7_nonzero) अणु
		data->gest_1 = &sensor->data_pkt[i];
		i++;
	पूर्ण

	अगर (query->query7_nonzero || query->query8_nonzero) अणु
		data->gest_2 = &sensor->data_pkt[i];
		i++;
	पूर्ण

	अगर (query->has_pinch) अणु
		data->pinch = &sensor->data_pkt[i];
		i++;
	पूर्ण

	अगर (query->has_flick) अणु
		अगर (query->has_pinch) अणु
			data->flick = data->pinch;
			i += 2;
		पूर्ण अन्यथा अणु
			data->flick = &sensor->data_pkt[i];
			i += 3;
		पूर्ण
	पूर्ण

	अगर (query->has_rotate) अणु
		अगर (query->has_flick) अणु
			data->rotate = data->flick + 1;
		पूर्ण अन्यथा अणु
			data->rotate = &sensor->data_pkt[i];
			i += 2;
		पूर्ण
	पूर्ण

	अगर (query->has_touch_shapes)
		data->shapes = &sensor->data_pkt[i];

	वापस 0;
पूर्ण

अटल पूर्णांक f11_पढ़ो_control_regs(काष्ठा rmi_function *fn,
				काष्ठा f11_2d_ctrl *ctrl, u16 ctrl_base_addr) अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक error = 0;

	ctrl->ctrl0_11_address = ctrl_base_addr;
	error = rmi_पढ़ो_block(rmi_dev, ctrl_base_addr, ctrl->ctrl0_11,
				RMI_F11_CTRL_REG_COUNT);
	अगर (error < 0) अणु
		dev_err(&fn->dev, "Failed to read ctrl0, code: %d.\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक f11_ग_लिखो_control_regs(काष्ठा rmi_function *fn,
					काष्ठा f11_2d_sensor_queries *query,
					काष्ठा f11_2d_ctrl *ctrl,
					u16 ctrl_base_addr)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक error;

	error = rmi_ग_लिखो_block(rmi_dev, ctrl_base_addr, ctrl->ctrl0_11,
				RMI_F11_CTRL_REG_COUNT);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f11_get_query_parameters(काष्ठा rmi_device *rmi_dev,
			काष्ठा f11_data *f11,
			काष्ठा f11_2d_sensor_queries *sensor_query,
			u16 query_base_addr)
अणु
	पूर्णांक query_size;
	पूर्णांक rc;
	u8 query_buf[RMI_F11_QUERY_SIZE];
	bool has_query36 = false;

	rc = rmi_पढ़ो_block(rmi_dev, query_base_addr, query_buf,
				RMI_F11_QUERY_SIZE);
	अगर (rc < 0)
		वापस rc;

	sensor_query->nr_fingers = query_buf[0] & RMI_F11_NR_FINGERS_MASK;
	sensor_query->has_rel = !!(query_buf[0] & RMI_F11_HAS_REL);
	sensor_query->has_असल = !!(query_buf[0] & RMI_F11_HAS_ABS);
	sensor_query->has_gestures = !!(query_buf[0] & RMI_F11_HAS_GESTURES);
	sensor_query->has_sensitivity_adjust =
		!!(query_buf[0] & RMI_F11_HAS_SENSITIVITY_ADJ);
	sensor_query->configurable = !!(query_buf[0] & RMI_F11_CONFIGURABLE);

	sensor_query->nr_x_electrodes =
				query_buf[1] & RMI_F11_NR_ELECTRODES_MASK;
	sensor_query->nr_y_electrodes =
				query_buf[2] & RMI_F11_NR_ELECTRODES_MASK;
	sensor_query->max_electrodes =
				query_buf[3] & RMI_F11_NR_ELECTRODES_MASK;

	query_size = RMI_F11_QUERY_SIZE;

	अगर (sensor_query->has_असल) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->असल_data_size =
			query_buf[0] & RMI_F11_ABS_DATA_SIZE_MASK;
		sensor_query->has_anchored_finger =
			!!(query_buf[0] & RMI_F11_HAS_ANCHORED_FINGER);
		sensor_query->has_adj_hyst =
			!!(query_buf[0] & RMI_F11_HAS_ADJ_HYST);
		sensor_query->has_dribble =
			!!(query_buf[0] & RMI_F11_HAS_DRIBBLE);
		sensor_query->has_bending_correction =
			!!(query_buf[0] & RMI_F11_HAS_BENDING_CORRECTION);
		sensor_query->has_large_object_suppression =
			!!(query_buf[0] & RMI_F11_HAS_LARGE_OBJECT_SUPPRESSION);
		sensor_query->has_jitter_filter =
			!!(query_buf[0] & RMI_F11_HAS_JITTER_FILTER);
		query_size++;
	पूर्ण

	अगर (sensor_query->has_rel) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size,
					&sensor_query->f11_2d_query6);
		अगर (rc < 0)
			वापस rc;
		query_size++;
	पूर्ण

	अगर (sensor_query->has_gestures) अणु
		rc = rmi_पढ़ो_block(rmi_dev, query_base_addr + query_size,
					query_buf, RMI_F11_QUERY_GESTURE_SIZE);
		अगर (rc < 0)
			वापस rc;

		sensor_query->has_single_tap =
			!!(query_buf[0] & RMI_F11_HAS_SINGLE_TAP);
		sensor_query->has_tap_n_hold =
			!!(query_buf[0] & RMI_F11_HAS_TAP_AND_HOLD);
		sensor_query->has_द्विगुन_tap =
			!!(query_buf[0] & RMI_F11_HAS_DOUBLE_TAP);
		sensor_query->has_early_tap =
			!!(query_buf[0] & RMI_F11_HAS_EARLY_TAP);
		sensor_query->has_flick =
			!!(query_buf[0] & RMI_F11_HAS_FLICK);
		sensor_query->has_press =
			!!(query_buf[0] & RMI_F11_HAS_PRESS);
		sensor_query->has_pinch =
			!!(query_buf[0] & RMI_F11_HAS_PINCH);
		sensor_query->has_chiral =
			!!(query_buf[0] & RMI_F11_HAS_CHIRAL);

		/* query 8 */
		sensor_query->has_palm_det =
			!!(query_buf[1] & RMI_F11_HAS_PALM_DET);
		sensor_query->has_rotate =
			!!(query_buf[1] & RMI_F11_HAS_ROTATE);
		sensor_query->has_touch_shapes =
			!!(query_buf[1] & RMI_F11_HAS_TOUCH_SHAPES);
		sensor_query->has_scroll_zones =
			!!(query_buf[1] & RMI_F11_HAS_SCROLL_ZONES);
		sensor_query->has_inभागidual_scroll_zones =
			!!(query_buf[1] & RMI_F11_HAS_INDIVIDUAL_SCROLL_ZONES);
		sensor_query->has_mf_scroll =
			!!(query_buf[1] & RMI_F11_HAS_MF_SCROLL);
		sensor_query->has_mf_edge_motion =
			!!(query_buf[1] & RMI_F11_HAS_MF_EDGE_MOTION);
		sensor_query->has_mf_scroll_inertia =
			!!(query_buf[1] & RMI_F11_HAS_MF_SCROLL_INERTIA);

		sensor_query->query7_nonzero = !!(query_buf[0]);
		sensor_query->query8_nonzero = !!(query_buf[1]);

		query_size += 2;
	पूर्ण

	अगर (f11->has_query9) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->has_pen =
			!!(query_buf[0] & RMI_F11_HAS_PEN);
		sensor_query->has_proximity =
			!!(query_buf[0] & RMI_F11_HAS_PROXIMITY);
		sensor_query->has_palm_det_sensitivity =
			!!(query_buf[0] & RMI_F11_HAS_PALM_DET_SENSITIVITY);
		sensor_query->has_suppress_on_palm_detect =
			!!(query_buf[0] & RMI_F11_HAS_SUPPRESS_ON_PALM_DETECT);
		sensor_query->has_two_pen_thresholds =
			!!(query_buf[0] & RMI_F11_HAS_TWO_PEN_THRESHOLDS);
		sensor_query->has_contact_geometry =
			!!(query_buf[0] & RMI_F11_HAS_CONTACT_GEOMETRY);
		sensor_query->has_pen_hover_discrimination =
			!!(query_buf[0] & RMI_F11_HAS_PEN_HOVER_DISCRIMINATION);
		sensor_query->has_pen_filters =
			!!(query_buf[0] & RMI_F11_HAS_PEN_FILTERS);

		query_size++;
	पूर्ण

	अगर (sensor_query->has_touch_shapes) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->nr_touch_shapes = query_buf[0] &
				RMI_F11_NR_TOUCH_SHAPES_MASK;

		query_size++;
	पूर्ण

	अगर (f11->has_query11) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->has_z_tuning =
			!!(query_buf[0] & RMI_F11_HAS_Z_TUNING);
		sensor_query->has_algorithm_selection =
			!!(query_buf[0] & RMI_F11_HAS_ALGORITHM_SELECTION);
		sensor_query->has_w_tuning =
			!!(query_buf[0] & RMI_F11_HAS_W_TUNING);
		sensor_query->has_pitch_info =
			!!(query_buf[0] & RMI_F11_HAS_PITCH_INFO);
		sensor_query->has_finger_size =
			!!(query_buf[0] & RMI_F11_HAS_FINGER_SIZE);
		sensor_query->has_segmentation_aggressiveness =
			!!(query_buf[0] &
				RMI_F11_HAS_SEGMENTATION_AGGRESSIVENESS);
		sensor_query->has_XY_clip =
			!!(query_buf[0] & RMI_F11_HAS_XY_CLIP);
		sensor_query->has_drumming_filter =
			!!(query_buf[0] & RMI_F11_HAS_DRUMMING_FILTER);

		query_size++;
	पूर्ण

	अगर (f11->has_query12) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->has_gapless_finger =
			!!(query_buf[0] & RMI_F11_HAS_GAPLESS_FINGER);
		sensor_query->has_gapless_finger_tuning =
			!!(query_buf[0] & RMI_F11_HAS_GAPLESS_FINGER_TUNING);
		sensor_query->has_8bit_w =
			!!(query_buf[0] & RMI_F11_HAS_8BIT_W);
		sensor_query->has_adjustable_mapping =
			!!(query_buf[0] & RMI_F11_HAS_ADJUSTABLE_MAPPING);
		sensor_query->has_info2 =
			!!(query_buf[0] & RMI_F11_HAS_INFO2);
		sensor_query->has_physical_props =
			!!(query_buf[0] & RMI_F11_HAS_PHYSICAL_PROPS);
		sensor_query->has_finger_limit =
			!!(query_buf[0] & RMI_F11_HAS_FINGER_LIMIT);
		sensor_query->has_linear_coeff_2 =
			!!(query_buf[0] & RMI_F11_HAS_LINEAR_COEFF);

		query_size++;
	पूर्ण

	अगर (sensor_query->has_jitter_filter) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->jitter_winकरोw_size = query_buf[0] &
			RMI_F11_JITTER_WINDOW_MASK;
		sensor_query->jitter_filter_type = (query_buf[0] &
			RMI_F11_JITTER_FILTER_MASK) >>
			RMI_F11_JITTER_FILTER_SHIFT;

		query_size++;
	पूर्ण

	अगर (sensor_query->has_info2) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size, query_buf);
		अगर (rc < 0)
			वापस rc;

		sensor_query->light_control =
			query_buf[0] & RMI_F11_LIGHT_CONTROL_MASK;
		sensor_query->is_clear =
			!!(query_buf[0] & RMI_F11_IS_CLEAR);
		sensor_query->clickpad_props =
			(query_buf[0] & RMI_F11_CLICKPAD_PROPS_MASK) >>
			RMI_F11_CLICKPAD_PROPS_SHIFT;
		sensor_query->mouse_buttons =
			(query_buf[0] & RMI_F11_MOUSE_BUTTONS_MASK) >>
			RMI_F11_MOUSE_BUTTONS_SHIFT;
		sensor_query->has_advanced_gestures =
			!!(query_buf[0] & RMI_F11_HAS_ADVANCED_GESTURES);

		query_size++;
	पूर्ण

	अगर (sensor_query->has_physical_props) अणु
		rc = rmi_पढ़ो_block(rmi_dev, query_base_addr
			+ query_size, query_buf, 4);
		अगर (rc < 0)
			वापस rc;

		sensor_query->x_sensor_size_mm =
			(query_buf[0] | (query_buf[1] << 8)) / 10;
		sensor_query->y_sensor_size_mm =
			(query_buf[2] | (query_buf[3] << 8)) / 10;

		/*
		 * query 15 - 18 contain the size of the sensor
		 * and query 19 - 26 contain bezel dimensions
		 */
		query_size += 12;
	पूर्ण

	अगर (f11->has_query27)
		++query_size;

	अगर (f11->has_query28) अणु
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size,
				query_buf);
		अगर (rc < 0)
			वापस rc;

		has_query36 = !!(query_buf[0] & BIT(6));
	पूर्ण

	अगर (has_query36) अणु
		query_size += 2;
		rc = rmi_पढ़ो(rmi_dev, query_base_addr + query_size,
				query_buf);
		अगर (rc < 0)
			वापस rc;

		अगर (!!(query_buf[0] & BIT(5)))
			f11->has_acm = true;
	पूर्ण

	वापस query_size;
पूर्ण

अटल पूर्णांक rmi_f11_initialize(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा f11_data *f11;
	काष्ठा f11_2d_ctrl *ctrl;
	u8 query_offset;
	u16 query_base_addr;
	u16 control_base_addr;
	u16 max_x_pos, max_y_pos;
	पूर्णांक rc;
	स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
				rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_2d_sensor *sensor;
	u8 buf;
	पूर्णांक mask_size;

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Initializing F11 values.\n");

	mask_size = BITS_TO_LONGS(drvdata->irq_count) * माप(अचिन्हित दीर्घ);

	/*
	** init instance data, fill in values and create any sysfs files
	*/
	f11 = devm_kzalloc(&fn->dev, माप(काष्ठा f11_data) + mask_size * 2,
			GFP_KERNEL);
	अगर (!f11)
		वापस -ENOMEM;

	अगर (fn->dev.of_node) अणु
		rc = rmi_2d_sensor_of_probe(&fn->dev, &f11->sensor_pdata);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		f11->sensor_pdata = pdata->sensor_pdata;
	पूर्ण

	f11->rezero_रुको_ms = f11->sensor_pdata.rezero_रुको;

	f11->असल_mask = (अचिन्हित दीर्घ *)((अक्षर *)f11
			+ माप(काष्ठा f11_data));
	f11->rel_mask = (अचिन्हित दीर्घ *)((अक्षर *)f11
			+ माप(काष्ठा f11_data) + mask_size);

	set_bit(fn->irq_pos, f11->असल_mask);
	set_bit(fn->irq_pos + 1, f11->rel_mask);

	query_base_addr = fn->fd.query_base_addr;
	control_base_addr = fn->fd.control_base_addr;

	rc = rmi_पढ़ो(rmi_dev, query_base_addr, &buf);
	अगर (rc < 0)
		वापस rc;

	f11->has_query9 = !!(buf & RMI_F11_HAS_QUERY9);
	f11->has_query11 = !!(buf & RMI_F11_HAS_QUERY11);
	f11->has_query12 = !!(buf & RMI_F11_HAS_QUERY12);
	f11->has_query27 = !!(buf & RMI_F11_HAS_QUERY27);
	f11->has_query28 = !!(buf & RMI_F11_HAS_QUERY28);

	query_offset = (query_base_addr + 1);
	sensor = &f11->sensor;
	sensor->fn = fn;

	rc = rmi_f11_get_query_parameters(rmi_dev, f11,
			&f11->sens_query, query_offset);
	अगर (rc < 0)
		वापस rc;
	query_offset += rc;

	rc = f11_पढ़ो_control_regs(fn, &f11->dev_controls,
			control_base_addr);
	अगर (rc < 0) अणु
		dev_err(&fn->dev,
			"Failed to read F11 control params.\n");
		वापस rc;
	पूर्ण

	अगर (f11->sens_query.has_info2) अणु
		अगर (f11->sens_query.is_clear)
			f11->sensor.sensor_type = rmi_sensor_touchscreen;
		अन्यथा
			f11->sensor.sensor_type = rmi_sensor_touchpad;
	पूर्ण

	sensor->report_असल = f11->sens_query.has_असल;

	sensor->axis_align =
		f11->sensor_pdata.axis_align;

	sensor->topbuttonpad = f11->sensor_pdata.topbuttonpad;
	sensor->kernel_tracking = f11->sensor_pdata.kernel_tracking;
	sensor->dmax = f11->sensor_pdata.dmax;
	sensor->dribble = f11->sensor_pdata.dribble;
	sensor->palm_detect = f11->sensor_pdata.palm_detect;

	अगर (f11->sens_query.has_physical_props) अणु
		sensor->x_mm = f11->sens_query.x_sensor_size_mm;
		sensor->y_mm = f11->sens_query.y_sensor_size_mm;
	पूर्ण अन्यथा अणु
		sensor->x_mm = f11->sensor_pdata.x_mm;
		sensor->y_mm = f11->sensor_pdata.y_mm;
	पूर्ण

	अगर (sensor->sensor_type == rmi_sensor_शेष)
		sensor->sensor_type =
			f11->sensor_pdata.sensor_type;

	sensor->report_असल = sensor->report_असल
		&& !(f11->sensor_pdata.disable_report_mask
			& RMI_F11_DISABLE_ABS_REPORT);

	अगर (!sensor->report_असल)
		/*
		 * If device करोesn't have असल or अगर it has been disables
		 * fallback to reporting rel data.
		 */
		sensor->report_rel = f11->sens_query.has_rel;

	rc = rmi_पढ़ो_block(rmi_dev,
		control_base_addr + F11_CTRL_SENSOR_MAX_X_POS_OFFSET,
		(u8 *)&max_x_pos, माप(max_x_pos));
	अगर (rc < 0)
		वापस rc;

	rc = rmi_पढ़ो_block(rmi_dev,
		control_base_addr + F11_CTRL_SENSOR_MAX_Y_POS_OFFSET,
		(u8 *)&max_y_pos, माप(max_y_pos));
	अगर (rc < 0)
		वापस rc;

	sensor->max_x = max_x_pos;
	sensor->max_y = max_y_pos;

	rc = f11_2d_स्थिरruct_data(f11);
	अगर (rc < 0)
		वापस rc;

	अगर (f11->has_acm)
		f11->sensor.attn_size += f11->sensor.nbr_fingers * 2;

	/* allocate the in-kernel tracking buffers */
	sensor->tracking_pos = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers, माप(काष्ठा input_mt_pos),
			GFP_KERNEL);
	sensor->tracking_slots = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers, माप(पूर्णांक), GFP_KERNEL);
	sensor->objs = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers,
			माप(काष्ठा rmi_2d_sensor_असल_object),
			GFP_KERNEL);
	अगर (!sensor->tracking_pos || !sensor->tracking_slots || !sensor->objs)
		वापस -ENOMEM;

	ctrl = &f11->dev_controls;
	अगर (sensor->axis_align.delta_x_threshold)
		ctrl->ctrl0_11[RMI_F11_DELTA_X_THRESHOLD] =
			sensor->axis_align.delta_x_threshold;

	अगर (sensor->axis_align.delta_y_threshold)
		ctrl->ctrl0_11[RMI_F11_DELTA_Y_THRESHOLD] =
			sensor->axis_align.delta_y_threshold;

	/*
	 * If distance threshold values are set, चयन to reduced reporting
	 * mode so they actually get used by the controller.
	 */
	अगर (sensor->axis_align.delta_x_threshold ||
	    sensor->axis_align.delta_y_threshold) अणु
		ctrl->ctrl0_11[0] &= ~RMI_F11_REPORT_MODE_MASK;
		ctrl->ctrl0_11[0] |= RMI_F11_REPORT_MODE_REDUCED;
	पूर्ण

	अगर (f11->sens_query.has_dribble) अणु
		चयन (sensor->dribble) अणु
		हाल RMI_REG_STATE_OFF:
			ctrl->ctrl0_11[0] &= ~BIT(6);
			अवरोध;
		हाल RMI_REG_STATE_ON:
			ctrl->ctrl0_11[0] |= BIT(6);
			अवरोध;
		हाल RMI_REG_STATE_DEFAULT:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (f11->sens_query.has_palm_det) अणु
		चयन (sensor->palm_detect) अणु
		हाल RMI_REG_STATE_OFF:
			ctrl->ctrl0_11[11] &= ~BIT(0);
			अवरोध;
		हाल RMI_REG_STATE_ON:
			ctrl->ctrl0_11[11] |= BIT(0);
			अवरोध;
		हाल RMI_REG_STATE_DEFAULT:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	rc = f11_ग_लिखो_control_regs(fn, &f11->sens_query,
			   &f11->dev_controls, fn->fd.control_base_addr);
	अगर (rc)
		dev_warn(&fn->dev, "Failed to write control registers\n");

	mutex_init(&f11->dev_controls_mutex);

	dev_set_drvdata(&fn->dev, f11);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f11_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा f11_data *f11 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_driver *drv = fn->rmi_dev->driver;
	काष्ठा rmi_2d_sensor *sensor = &f11->sensor;
	पूर्णांक rc;

	अगर (!sensor->report_असल)
		drv->clear_irq_bits(fn->rmi_dev, f11->असल_mask);
	अन्यथा
		drv->set_irq_bits(fn->rmi_dev, f11->असल_mask);

	अगर (!sensor->report_rel)
		drv->clear_irq_bits(fn->rmi_dev, f11->rel_mask);
	अन्यथा
		drv->set_irq_bits(fn->rmi_dev, f11->rel_mask);

	rc = f11_ग_लिखो_control_regs(fn, &f11->sens_query,
			   &f11->dev_controls, fn->fd.query_base_addr);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल irqवापस_t rmi_f11_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f11_data *f11 = dev_get_drvdata(&fn->dev);
	u16 data_base_addr = fn->fd.data_base_addr;
	पूर्णांक error;
	पूर्णांक valid_bytes = f11->sensor.pkt_size;

	अगर (drvdata->attn_data.data) अणु
		/*
		 * The valid data in the attention report is less then
		 * expected. Only process the complete fingers.
		 */
		अगर (f11->sensor.attn_size > drvdata->attn_data.size)
			valid_bytes = drvdata->attn_data.size;
		अन्यथा
			valid_bytes = f11->sensor.attn_size;
		स_नकल(f11->sensor.data_pkt, drvdata->attn_data.data,
			valid_bytes);
		drvdata->attn_data.data += valid_bytes;
		drvdata->attn_data.size -= valid_bytes;
	पूर्ण अन्यथा अणु
		error = rmi_पढ़ो_block(rmi_dev,
				data_base_addr, f11->sensor.data_pkt,
				f11->sensor.pkt_size);
		अगर (error < 0)
			वापस IRQ_RETVAL(error);
	पूर्ण

	rmi_f11_finger_handler(f11, &f11->sensor, valid_bytes);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_f11_resume(काष्ठा rmi_function *fn)
अणु
	काष्ठा f11_data *f11 = dev_get_drvdata(&fn->dev);
	पूर्णांक error;

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Resuming...\n");
	अगर (!f11->rezero_रुको_ms)
		वापस 0;

	mdelay(f11->rezero_रुको_ms);

	error = rmi_ग_लिखो(fn->rmi_dev, fn->fd.command_base_addr,
				RMI_F11_REZERO);
	अगर (error) अणु
		dev_err(&fn->dev,
			"%s: failed to issue rezero command, error = %d.",
			__func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f11_probe(काष्ठा rmi_function *fn)
अणु
	पूर्णांक error;
	काष्ठा f11_data *f11;

	error = rmi_f11_initialize(fn);
	अगर (error)
		वापस error;

	f11 = dev_get_drvdata(&fn->dev);
	error = rmi_2d_sensor_configure_input(fn, &f11->sensor);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

काष्ठा rmi_function_handler rmi_f11_handler = अणु
	.driver = अणु
		.name	= "rmi4_f11",
	पूर्ण,
	.func		= 0x11,
	.probe		= rmi_f11_probe,
	.config		= rmi_f11_config,
	.attention	= rmi_f11_attention,
	.resume		= rmi_f11_resume,
पूर्ण;
