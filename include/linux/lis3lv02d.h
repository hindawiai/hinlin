<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIS3LV02D_H_
#घोषणा __LIS3LV02D_H_

/**
 * काष्ठा lis3lv02d_platक्रमm_data - lis3 chip family platक्रमm data
 * @click_flags:	Click detection unit configuration
 * @click_thresh_x:	Click detection unit x axis threshold
 * @click_thresh_y:	Click detection unit y axis threshold
 * @click_thresh_z:	Click detection unit z axis threshold
 * @click_समय_limit:	Click detection unit समय parameter
 * @click_latency:	Click detection unit latency parameter
 * @click_winकरोw:	Click detection unit winकरोw parameter
 * @irq_cfg:		On chip irq source and type configuration (click /
 *			data available / wake up, खोलो drain, polarity)
 * @irq_flags1:		Additional irq triggering flags क्रम irq channel 0
 * @irq_flags2:		Additional irq triggering flags क्रम irq channel 1
 * @duration1:		Wake up unit 1 duration parameter
 * @duration2:		Wake up unit 2 duration parameter
 * @wakeup_flags:	Wake up unit 1 flags
 * @wakeup_thresh:	Wake up unit 1 threshold value
 * @wakeup_flags2:	Wake up unit 2 flags
 * @wakeup_thresh2:	Wake up unit 2 threshold value
 * @hipass_ctrl:	High pass filter control (enable / disable, cut off
 *			frequency)
 * @axis_x:		Sensor orientation remapping क्रम x-axis
 * @axis_y:		Sensor orientation remapping क्रम y-axis
 * @axis_z:		Sensor orientation remapping क्रम z-axis
 * @driver_features:	Enable bits क्रम dअगरferent features. Disabled by शेष
 * @शेष_rate:	Default sampling rate. 0 means reset शेष
 * @setup_resources:	Interrupt line setup call back function
 * @release_resources:	Interrupt line release call back function
 * @st_min_limits[3]:	Selftest acceptance minimum values
 * @st_max_limits[3]:	Selftest acceptance maximum values
 * @irq2:		Irq line 2 number
 *
 * Platक्रमm data is used to setup the sensor chip. Meaning of the dअगरferent
 * chip features can be found from the data sheet. It is खुलाly available
 * at www.st.com web pages. Currently the platक्रमm data is used
 * only क्रम the 8 bit device. The 8 bit device has two wake up / मुक्त fall
 * detection units and click detection unit. There are plenty of ways to
 * configure the chip which makes is quite hard to explain deeper meaning of
 * the fields here. Behaviour of the detection blocks varies heavily depending
 * on the configuration. For example, पूर्णांकerrupt detection block can use high
 * pass filtered data which makes it react to the changes in the acceleration.
 * Irq_flags can be used to enable पूर्णांकerrupt detection on the both edges.
 * With proper chip configuration this produces पूर्णांकerrupt when some trigger
 * starts and when it goes away.
 */

काष्ठा lis3lv02d_platक्रमm_data अणु
	/* please note: the 'click' feature is only supported क्रम
	 * LIS[32]02DL variants of the chip and will be ignored क्रम
	 * others */
#घोषणा LIS3_CLICK_SINGLE_X	(1 << 0)
#घोषणा LIS3_CLICK_DOUBLE_X	(1 << 1)
#घोषणा LIS3_CLICK_SINGLE_Y	(1 << 2)
#घोषणा LIS3_CLICK_DOUBLE_Y	(1 << 3)
#घोषणा LIS3_CLICK_SINGLE_Z	(1 << 4)
#घोषणा LIS3_CLICK_DOUBLE_Z	(1 << 5)
	अचिन्हित अक्षर click_flags;
	अचिन्हित अक्षर click_thresh_x;
	अचिन्हित अक्षर click_thresh_y;
	अचिन्हित अक्षर click_thresh_z;
	अचिन्हित अक्षर click_समय_limit;
	अचिन्हित अक्षर click_latency;
	अचिन्हित अक्षर click_winकरोw;

#घोषणा LIS3_IRQ1_DISABLE	(0 << 0)
#घोषणा LIS3_IRQ1_FF_WU_1	(1 << 0)
#घोषणा LIS3_IRQ1_FF_WU_2	(2 << 0)
#घोषणा LIS3_IRQ1_FF_WU_12	(3 << 0)
#घोषणा LIS3_IRQ1_DATA_READY	(4 << 0)
#घोषणा LIS3_IRQ1_CLICK		(7 << 0)
#घोषणा LIS3_IRQ1_MASK		(7 << 0)
#घोषणा LIS3_IRQ2_DISABLE	(0 << 3)
#घोषणा LIS3_IRQ2_FF_WU_1	(1 << 3)
#घोषणा LIS3_IRQ2_FF_WU_2	(2 << 3)
#घोषणा LIS3_IRQ2_FF_WU_12	(3 << 3)
#घोषणा LIS3_IRQ2_DATA_READY	(4 << 3)
#घोषणा LIS3_IRQ2_CLICK		(7 << 3)
#घोषणा LIS3_IRQ2_MASK		(7 << 3)
#घोषणा LIS3_IRQ_OPEN_DRAIN	(1 << 6)
#घोषणा LIS3_IRQ_ACTIVE_LOW	(1 << 7)
	अचिन्हित अक्षर irq_cfg;
	अचिन्हित अक्षर irq_flags1; /* Additional irq edge / level flags */
	अचिन्हित अक्षर irq_flags2; /* Additional irq edge / level flags */
	अचिन्हित अक्षर duration1;
	अचिन्हित अक्षर duration2;
#घोषणा LIS3_WAKEUP_X_LO	(1 << 0)
#घोषणा LIS3_WAKEUP_X_HI	(1 << 1)
#घोषणा LIS3_WAKEUP_Y_LO	(1 << 2)
#घोषणा LIS3_WAKEUP_Y_HI	(1 << 3)
#घोषणा LIS3_WAKEUP_Z_LO	(1 << 4)
#घोषणा LIS3_WAKEUP_Z_HI	(1 << 5)
	अचिन्हित अक्षर wakeup_flags;
	अचिन्हित अक्षर wakeup_thresh;
	अचिन्हित अक्षर wakeup_flags2;
	अचिन्हित अक्षर wakeup_thresh2;
#घोषणा LIS3_HIPASS_CUTFF_8HZ   0
#घोषणा LIS3_HIPASS_CUTFF_4HZ   1
#घोषणा LIS3_HIPASS_CUTFF_2HZ   2
#घोषणा LIS3_HIPASS_CUTFF_1HZ   3
#घोषणा LIS3_HIPASS1_DISABLE    (1 << 2)
#घोषणा LIS3_HIPASS2_DISABLE    (1 << 3)
	अचिन्हित अक्षर hipass_ctrl;
#घोषणा LIS3_NO_MAP		0
#घोषणा LIS3_DEV_X		1
#घोषणा LIS3_DEV_Y		2
#घोषणा LIS3_DEV_Z		3
#घोषणा LIS3_INV_DEV_X	       -1
#घोषणा LIS3_INV_DEV_Y	       -2
#घोषणा LIS3_INV_DEV_Z	       -3
	s8 axis_x;
	s8 axis_y;
	s8 axis_z;
#घोषणा LIS3_USE_BLOCK_READ	0x02
	u16 driver_features;
	पूर्णांक शेष_rate;
	पूर्णांक (*setup_resources)(व्योम);
	पूर्णांक (*release_resources)(व्योम);
	/* Limits क्रम selftest are specअगरied in chip data sheet */
	s16 st_min_limits[3]; /* min pass limit x, y, z */
	s16 st_max_limits[3]; /* max pass limit x, y, z */
	पूर्णांक irq2;
पूर्ण;

#पूर्ण_अगर /* __LIS3LV02D_H_ */
