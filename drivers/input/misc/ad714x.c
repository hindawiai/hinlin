<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD714X CapTouch Programmable Controller driver supporting AD7142/3/7/8/7A
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/input/ad714x.h>
#समावेश <linux/module.h>
#समावेश "ad714x.h"

#घोषणा AD714X_PWR_CTRL           0x0
#घोषणा AD714X_STG_CAL_EN_REG     0x1
#घोषणा AD714X_AMB_COMP_CTRL0_REG 0x2
#घोषणा AD714X_PARTID_REG         0x17
#घोषणा AD7142_PARTID             0xE620
#घोषणा AD7143_PARTID             0xE630
#घोषणा AD7147_PARTID             0x1470
#घोषणा AD7148_PARTID             0x1480
#घोषणा AD714X_STAGECFG_REG       0x80
#घोषणा AD714X_SYSCFG_REG         0x0

#घोषणा STG_LOW_INT_EN_REG     0x5
#घोषणा STG_HIGH_INT_EN_REG    0x6
#घोषणा STG_COM_INT_EN_REG     0x7
#घोषणा STG_LOW_INT_STA_REG    0x8
#घोषणा STG_HIGH_INT_STA_REG   0x9
#घोषणा STG_COM_INT_STA_REG    0xA

#घोषणा CDC_RESULT_S0          0xB
#घोषणा CDC_RESULT_S1          0xC
#घोषणा CDC_RESULT_S2          0xD
#घोषणा CDC_RESULT_S3          0xE
#घोषणा CDC_RESULT_S4          0xF
#घोषणा CDC_RESULT_S5          0x10
#घोषणा CDC_RESULT_S6          0x11
#घोषणा CDC_RESULT_S7          0x12
#घोषणा CDC_RESULT_S8          0x13
#घोषणा CDC_RESULT_S9          0x14
#घोषणा CDC_RESULT_S10         0x15
#घोषणा CDC_RESULT_S11         0x16

#घोषणा STAGE0_AMBIENT		0xF1
#घोषणा STAGE1_AMBIENT		0x115
#घोषणा STAGE2_AMBIENT		0x139
#घोषणा STAGE3_AMBIENT		0x15D
#घोषणा STAGE4_AMBIENT		0x181
#घोषणा STAGE5_AMBIENT		0x1A5
#घोषणा STAGE6_AMBIENT		0x1C9
#घोषणा STAGE7_AMBIENT		0x1ED
#घोषणा STAGE8_AMBIENT		0x211
#घोषणा STAGE9_AMBIENT		0x234
#घोषणा STAGE10_AMBIENT		0x259
#घोषणा STAGE11_AMBIENT		0x27D

#घोषणा PER_STAGE_REG_NUM      36
#घोषणा STAGE_CFGREG_NUM       8
#घोषणा SYS_CFGREG_NUM         8

/*
 * driver inक्रमmation which will be used to मुख्यtain the software flow
 */
क्रमागत ad714x_device_state अणु IDLE, JITTER, ACTIVE, SPACE पूर्ण;

काष्ठा ad714x_slider_drv अणु
	पूर्णांक highest_stage;
	पूर्णांक असल_pos;
	पूर्णांक flt_pos;
	क्रमागत ad714x_device_state state;
	काष्ठा input_dev *input;
पूर्ण;

काष्ठा ad714x_wheel_drv अणु
	पूर्णांक असल_pos;
	पूर्णांक flt_pos;
	पूर्णांक pre_highest_stage;
	पूर्णांक highest_stage;
	क्रमागत ad714x_device_state state;
	काष्ठा input_dev *input;
पूर्ण;

काष्ठा ad714x_touchpad_drv अणु
	पूर्णांक x_highest_stage;
	पूर्णांक x_flt_pos;
	पूर्णांक x_असल_pos;
	पूर्णांक y_highest_stage;
	पूर्णांक y_flt_pos;
	पूर्णांक y_असल_pos;
	पूर्णांक left_ep;
	पूर्णांक left_ep_val;
	पूर्णांक right_ep;
	पूर्णांक right_ep_val;
	पूर्णांक top_ep;
	पूर्णांक top_ep_val;
	पूर्णांक bottom_ep;
	पूर्णांक bottom_ep_val;
	क्रमागत ad714x_device_state state;
	काष्ठा input_dev *input;
पूर्ण;

काष्ठा ad714x_button_drv अणु
	क्रमागत ad714x_device_state state;
	/*
	 * Unlike slider/wheel/touchpad, all buttons poपूर्णांक to
	 * same input_dev instance
	 */
	काष्ठा input_dev *input;
पूर्ण;

काष्ठा ad714x_driver_data अणु
	काष्ठा ad714x_slider_drv *slider;
	काष्ठा ad714x_wheel_drv *wheel;
	काष्ठा ad714x_touchpad_drv *touchpad;
	काष्ठा ad714x_button_drv *button;
पूर्ण;

/*
 * inक्रमmation to पूर्णांकegrate all things which will be निजी data
 * of spi/i2c device
 */

अटल व्योम ad714x_use_com_पूर्णांक(काष्ठा ad714x_chip *ad714x,
				पूर्णांक start_stage, पूर्णांक end_stage)
अणु
	अचिन्हित लघु data;
	अचिन्हित लघु mask;

	mask = ((1 << (end_stage + 1)) - 1) - ((1 << start_stage) - 1);

	ad714x->पढ़ो(ad714x, STG_COM_INT_EN_REG, &data, 1);
	data |= 1 << end_stage;
	ad714x->ग_लिखो(ad714x, STG_COM_INT_EN_REG, data);

	ad714x->पढ़ो(ad714x, STG_HIGH_INT_EN_REG, &data, 1);
	data &= ~mask;
	ad714x->ग_लिखो(ad714x, STG_HIGH_INT_EN_REG, data);
पूर्ण

अटल व्योम ad714x_use_thr_पूर्णांक(काष्ठा ad714x_chip *ad714x,
				पूर्णांक start_stage, पूर्णांक end_stage)
अणु
	अचिन्हित लघु data;
	अचिन्हित लघु mask;

	mask = ((1 << (end_stage + 1)) - 1) - ((1 << start_stage) - 1);

	ad714x->पढ़ो(ad714x, STG_COM_INT_EN_REG, &data, 1);
	data &= ~(1 << end_stage);
	ad714x->ग_लिखो(ad714x, STG_COM_INT_EN_REG, data);

	ad714x->पढ़ो(ad714x, STG_HIGH_INT_EN_REG, &data, 1);
	data |= mask;
	ad714x->ग_लिखो(ad714x, STG_HIGH_INT_EN_REG, data);
पूर्ण

अटल पूर्णांक ad714x_cal_highest_stage(काष्ठा ad714x_chip *ad714x,
					पूर्णांक start_stage, पूर्णांक end_stage)
अणु
	पूर्णांक max_res = 0;
	पूर्णांक max_idx = 0;
	पूर्णांक i;

	क्रम (i = start_stage; i <= end_stage; i++) अणु
		अगर (ad714x->sensor_val[i] > max_res) अणु
			max_res = ad714x->sensor_val[i];
			max_idx = i;
		पूर्ण
	पूर्ण

	वापस max_idx;
पूर्ण

अटल पूर्णांक ad714x_cal_असल_pos(काष्ठा ad714x_chip *ad714x,
				पूर्णांक start_stage, पूर्णांक end_stage,
				पूर्णांक highest_stage, पूर्णांक max_coord)
अणु
	पूर्णांक a_param, b_param;

	अगर (highest_stage == start_stage) अणु
		a_param = ad714x->sensor_val[start_stage + 1];
		b_param = ad714x->sensor_val[start_stage] +
			ad714x->sensor_val[start_stage + 1];
	पूर्ण अन्यथा अगर (highest_stage == end_stage) अणु
		a_param = ad714x->sensor_val[end_stage] *
			(end_stage - start_stage) +
			ad714x->sensor_val[end_stage - 1] *
			(end_stage - start_stage - 1);
		b_param = ad714x->sensor_val[end_stage] +
			ad714x->sensor_val[end_stage - 1];
	पूर्ण अन्यथा अणु
		a_param = ad714x->sensor_val[highest_stage] *
			(highest_stage - start_stage) +
			ad714x->sensor_val[highest_stage - 1] *
			(highest_stage - start_stage - 1) +
			ad714x->sensor_val[highest_stage + 1] *
			(highest_stage - start_stage + 1);
		b_param = ad714x->sensor_val[highest_stage] +
			ad714x->sensor_val[highest_stage - 1] +
			ad714x->sensor_val[highest_stage + 1];
	पूर्ण

	वापस (max_coord / (end_stage - start_stage)) * a_param / b_param;
पूर्ण

/*
 * One button can connect to multi positive and negative of CDCs
 * Multi-buttons can connect to same positive/negative of one CDC
 */
अटल व्योम ad714x_button_state_machine(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_button_plat *hw = &ad714x->hw->button[idx];
	काष्ठा ad714x_button_drv *sw = &ad714x->sw->button[idx];

	चयन (sw->state) अणु
	हाल IDLE:
		अगर (((ad714x->h_state & hw->h_mask) == hw->h_mask) &&
		    ((ad714x->l_state & hw->l_mask) == hw->l_mask)) अणु
			dev_dbg(ad714x->dev, "button %d touched\n", idx);
			input_report_key(sw->input, hw->keycode, 1);
			input_sync(sw->input);
			sw->state = ACTIVE;
		पूर्ण
		अवरोध;

	हाल ACTIVE:
		अगर (((ad714x->h_state & hw->h_mask) != hw->h_mask) ||
		    ((ad714x->l_state & hw->l_mask) != hw->l_mask)) अणु
			dev_dbg(ad714x->dev, "button %d released\n", idx);
			input_report_key(sw->input, hw->keycode, 0);
			input_sync(sw->input);
			sw->state = IDLE;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * The response of a sensor is defined by the असलolute number of codes
 * between the current CDC value and the ambient value.
 */
अटल व्योम ad714x_slider_cal_sensor_val(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	पूर्णांक i;

	ad714x->पढ़ो(ad714x, CDC_RESULT_S0 + hw->start_stage,
			&ad714x->adc_reg[hw->start_stage],
			hw->end_stage - hw->start_stage + 1);

	क्रम (i = hw->start_stage; i <= hw->end_stage; i++) अणु
		ad714x->पढ़ो(ad714x, STAGE0_AMBIENT + i * PER_STAGE_REG_NUM,
				&ad714x->amb_reg[i], 1);

		ad714x->sensor_val[i] =
			असल(ad714x->adc_reg[i] - ad714x->amb_reg[i]);
	पूर्ण
पूर्ण

अटल व्योम ad714x_slider_cal_highest_stage(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	काष्ठा ad714x_slider_drv *sw = &ad714x->sw->slider[idx];

	sw->highest_stage = ad714x_cal_highest_stage(ad714x, hw->start_stage,
			hw->end_stage);

	dev_dbg(ad714x->dev, "slider %d highest_stage:%d\n", idx,
		sw->highest_stage);
पूर्ण

/*
 * The क्रमmulae are very straight क्रमward. It uses the sensor with the
 * highest response and the 2 adjacent ones.
 * When Sensor 0 has the highest response, only sensor 0 and sensor 1
 * are used in the calculations. Similarly when the last sensor has the
 * highest response, only the last sensor and the second last sensors
 * are used in the calculations.
 *
 * For i= idx_of_peak_Sensor-1 to i= idx_of_peak_Sensor+1
 *         v += Sensor response(i)*i
 *         w += Sensor response(i)
 * POS=(Number_of_Positions_Wanted/(Number_of_Sensors_Used-1)) *(v/w)
 */
अटल व्योम ad714x_slider_cal_असल_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	काष्ठा ad714x_slider_drv *sw = &ad714x->sw->slider[idx];

	sw->असल_pos = ad714x_cal_असल_pos(ad714x, hw->start_stage, hw->end_stage,
		sw->highest_stage, hw->max_coord);

	dev_dbg(ad714x->dev, "slider %d absolute position:%d\n", idx,
		sw->असल_pos);
पूर्ण

/*
 * To minimise the Impact of the noise on the algorithm, ADI developed a
 * routine that filters the CDC results after they have been पढ़ो by the
 * host processor.
 * The filter used is an Infinite Input Response(IIR) filter implemented
 * in firmware and attenuates the noise on the CDC results after they've
 * been पढ़ो by the host processor.
 * Filtered_CDC_result = (Filtered_CDC_result * (10 - Coefficient) +
 *				Latest_CDC_result * Coefficient)/10
 */
अटल व्योम ad714x_slider_cal_flt_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_drv *sw = &ad714x->sw->slider[idx];

	sw->flt_pos = (sw->flt_pos * (10 - 4) +
			sw->असल_pos * 4)/10;

	dev_dbg(ad714x->dev, "slider %d filter position:%d\n", idx,
		sw->flt_pos);
पूर्ण

अटल व्योम ad714x_slider_use_com_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];

	ad714x_use_com_पूर्णांक(ad714x, hw->start_stage, hw->end_stage);
पूर्ण

अटल व्योम ad714x_slider_use_thr_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];

	ad714x_use_thr_पूर्णांक(ad714x, hw->start_stage, hw->end_stage);
पूर्ण

अटल व्योम ad714x_slider_state_machine(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	काष्ठा ad714x_slider_drv *sw = &ad714x->sw->slider[idx];
	अचिन्हित लघु h_state, c_state;
	अचिन्हित लघु mask;

	mask = ((1 << (hw->end_stage + 1)) - 1) - ((1 << hw->start_stage) - 1);

	h_state = ad714x->h_state & mask;
	c_state = ad714x->c_state & mask;

	चयन (sw->state) अणु
	हाल IDLE:
		अगर (h_state) अणु
			sw->state = JITTER;
			/* In End of Conversion पूर्णांकerrupt mode, the AD714X
			 * continuously generates hardware पूर्णांकerrupts.
			 */
			ad714x_slider_use_com_पूर्णांक(ad714x, idx);
			dev_dbg(ad714x->dev, "slider %d touched\n", idx);
		पूर्ण
		अवरोध;

	हाल JITTER:
		अगर (c_state == mask) अणु
			ad714x_slider_cal_sensor_val(ad714x, idx);
			ad714x_slider_cal_highest_stage(ad714x, idx);
			ad714x_slider_cal_असल_pos(ad714x, idx);
			sw->flt_pos = sw->असल_pos;
			sw->state = ACTIVE;
		पूर्ण
		अवरोध;

	हाल ACTIVE:
		अगर (c_state == mask) अणु
			अगर (h_state) अणु
				ad714x_slider_cal_sensor_val(ad714x, idx);
				ad714x_slider_cal_highest_stage(ad714x, idx);
				ad714x_slider_cal_असल_pos(ad714x, idx);
				ad714x_slider_cal_flt_pos(ad714x, idx);
				input_report_असल(sw->input, ABS_X, sw->flt_pos);
				input_report_key(sw->input, BTN_TOUCH, 1);
			पूर्ण अन्यथा अणु
				/* When the user lअगरts off the sensor, configure
				 * the AD714X back to threshold पूर्णांकerrupt mode.
				 */
				ad714x_slider_use_thr_पूर्णांक(ad714x, idx);
				sw->state = IDLE;
				input_report_key(sw->input, BTN_TOUCH, 0);
				dev_dbg(ad714x->dev, "slider %d released\n",
					idx);
			पूर्ण
			input_sync(sw->input);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * When the scroll wheel is activated, we compute the असलolute position based
 * on the sensor values. To calculate the position, we first determine the
 * sensor that has the greatest response among the 8 sensors that स्थिरitutes
 * the scrollwheel. Then we determined the 2 sensors on either sides of the
 * sensor with the highest response and we apply weights to these sensors.
 */
अटल व्योम ad714x_wheel_cal_highest_stage(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	काष्ठा ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];

	sw->pre_highest_stage = sw->highest_stage;
	sw->highest_stage = ad714x_cal_highest_stage(ad714x, hw->start_stage,
			hw->end_stage);

	dev_dbg(ad714x->dev, "wheel %d highest_stage:%d\n", idx,
		sw->highest_stage);
पूर्ण

अटल व्योम ad714x_wheel_cal_sensor_val(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	पूर्णांक i;

	ad714x->पढ़ो(ad714x, CDC_RESULT_S0 + hw->start_stage,
			&ad714x->adc_reg[hw->start_stage],
			hw->end_stage - hw->start_stage + 1);

	क्रम (i = hw->start_stage; i <= hw->end_stage; i++) अणु
		ad714x->पढ़ो(ad714x, STAGE0_AMBIENT + i * PER_STAGE_REG_NUM,
				&ad714x->amb_reg[i], 1);
		अगर (ad714x->adc_reg[i] > ad714x->amb_reg[i])
			ad714x->sensor_val[i] =
				ad714x->adc_reg[i] - ad714x->amb_reg[i];
		अन्यथा
			ad714x->sensor_val[i] = 0;
	पूर्ण
पूर्ण

/*
 * When the scroll wheel is activated, we compute the असलolute position based
 * on the sensor values. To calculate the position, we first determine the
 * sensor that has the greatest response among the sensors that स्थिरitutes
 * the scrollwheel. Then we determined the sensors on either sides of the
 * sensor with the highest response and we apply weights to these sensors. The
 * result of this computation gives us the mean value.
 */

अटल व्योम ad714x_wheel_cal_असल_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	काष्ठा ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];
	पूर्णांक stage_num = hw->end_stage - hw->start_stage + 1;
	पूर्णांक first_beक्रमe, highest, first_after;
	पूर्णांक a_param, b_param;

	first_beक्रमe = (sw->highest_stage + stage_num - 1) % stage_num;
	highest = sw->highest_stage;
	first_after = (sw->highest_stage + stage_num + 1) % stage_num;

	a_param = ad714x->sensor_val[highest] *
		(highest - hw->start_stage) +
		ad714x->sensor_val[first_beक्रमe] *
		(highest - hw->start_stage - 1) +
		ad714x->sensor_val[first_after] *
		(highest - hw->start_stage + 1);
	b_param = ad714x->sensor_val[highest] +
		ad714x->sensor_val[first_beक्रमe] +
		ad714x->sensor_val[first_after];

	sw->असल_pos = ((hw->max_coord / (hw->end_stage - hw->start_stage)) *
			a_param) / b_param;

	अगर (sw->असल_pos > hw->max_coord)
		sw->असल_pos = hw->max_coord;
	अन्यथा अगर (sw->असल_pos < 0)
		sw->असल_pos = 0;
पूर्ण

अटल व्योम ad714x_wheel_cal_flt_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	काष्ठा ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];
	अगर (((sw->pre_highest_stage == hw->end_stage) &&
			(sw->highest_stage == hw->start_stage)) ||
	    ((sw->pre_highest_stage == hw->start_stage) &&
			(sw->highest_stage == hw->end_stage)))
		sw->flt_pos = sw->असल_pos;
	अन्यथा
		sw->flt_pos = ((sw->flt_pos * 30) + (sw->असल_pos * 71)) / 100;

	अगर (sw->flt_pos > hw->max_coord)
		sw->flt_pos = hw->max_coord;
पूर्ण

अटल व्योम ad714x_wheel_use_com_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];

	ad714x_use_com_पूर्णांक(ad714x, hw->start_stage, hw->end_stage);
पूर्ण

अटल व्योम ad714x_wheel_use_thr_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];

	ad714x_use_thr_पूर्णांक(ad714x, hw->start_stage, hw->end_stage);
पूर्ण

अटल व्योम ad714x_wheel_state_machine(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	काष्ठा ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];
	अचिन्हित लघु h_state, c_state;
	अचिन्हित लघु mask;

	mask = ((1 << (hw->end_stage + 1)) - 1) - ((1 << hw->start_stage) - 1);

	h_state = ad714x->h_state & mask;
	c_state = ad714x->c_state & mask;

	चयन (sw->state) अणु
	हाल IDLE:
		अगर (h_state) अणु
			sw->state = JITTER;
			/* In End of Conversion पूर्णांकerrupt mode, the AD714X
			 * continuously generates hardware पूर्णांकerrupts.
			 */
			ad714x_wheel_use_com_पूर्णांक(ad714x, idx);
			dev_dbg(ad714x->dev, "wheel %d touched\n", idx);
		पूर्ण
		अवरोध;

	हाल JITTER:
		अगर (c_state == mask)	अणु
			ad714x_wheel_cal_sensor_val(ad714x, idx);
			ad714x_wheel_cal_highest_stage(ad714x, idx);
			ad714x_wheel_cal_असल_pos(ad714x, idx);
			sw->flt_pos = sw->असल_pos;
			sw->state = ACTIVE;
		पूर्ण
		अवरोध;

	हाल ACTIVE:
		अगर (c_state == mask) अणु
			अगर (h_state) अणु
				ad714x_wheel_cal_sensor_val(ad714x, idx);
				ad714x_wheel_cal_highest_stage(ad714x, idx);
				ad714x_wheel_cal_असल_pos(ad714x, idx);
				ad714x_wheel_cal_flt_pos(ad714x, idx);
				input_report_असल(sw->input, ABS_WHEEL,
					sw->flt_pos);
				input_report_key(sw->input, BTN_TOUCH, 1);
			पूर्ण अन्यथा अणु
				/* When the user lअगरts off the sensor, configure
				 * the AD714X back to threshold पूर्णांकerrupt mode.
				 */
				ad714x_wheel_use_thr_पूर्णांक(ad714x, idx);
				sw->state = IDLE;
				input_report_key(sw->input, BTN_TOUCH, 0);

				dev_dbg(ad714x->dev, "wheel %d released\n",
					idx);
			पूर्ण
			input_sync(sw->input);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम touchpad_cal_sensor_val(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	पूर्णांक i;

	ad714x->पढ़ो(ad714x, CDC_RESULT_S0 + hw->x_start_stage,
			&ad714x->adc_reg[hw->x_start_stage],
			hw->x_end_stage - hw->x_start_stage + 1);

	क्रम (i = hw->x_start_stage; i <= hw->x_end_stage; i++) अणु
		ad714x->पढ़ो(ad714x, STAGE0_AMBIENT + i * PER_STAGE_REG_NUM,
				&ad714x->amb_reg[i], 1);
		अगर (ad714x->adc_reg[i] > ad714x->amb_reg[i])
			ad714x->sensor_val[i] =
				ad714x->adc_reg[i] - ad714x->amb_reg[i];
		अन्यथा
			ad714x->sensor_val[i] = 0;
	पूर्ण
पूर्ण

अटल व्योम touchpad_cal_highest_stage(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	काष्ठा ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];

	sw->x_highest_stage = ad714x_cal_highest_stage(ad714x,
		hw->x_start_stage, hw->x_end_stage);
	sw->y_highest_stage = ad714x_cal_highest_stage(ad714x,
		hw->y_start_stage, hw->y_end_stage);

	dev_dbg(ad714x->dev,
		"touchpad %d x_highest_stage:%d, y_highest_stage:%d\n",
		idx, sw->x_highest_stage, sw->y_highest_stage);
पूर्ण

/*
 * If 2 fingers are touching the sensor then 2 peaks can be observed in the
 * distribution.
 * The arithmetic करोesn't support to get असलolute coordinates क्रम multi-touch
 * yet.
 */
अटल पूर्णांक touchpad_check_second_peak(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	काष्ठा ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];
	पूर्णांक i;

	क्रम (i = hw->x_start_stage; i < sw->x_highest_stage; i++) अणु
		अगर ((ad714x->sensor_val[i] - ad714x->sensor_val[i + 1])
			> (ad714x->sensor_val[i + 1] / 10))
			वापस 1;
	पूर्ण

	क्रम (i = sw->x_highest_stage; i < hw->x_end_stage; i++) अणु
		अगर ((ad714x->sensor_val[i + 1] - ad714x->sensor_val[i])
			> (ad714x->sensor_val[i] / 10))
			वापस 1;
	पूर्ण

	क्रम (i = hw->y_start_stage; i < sw->y_highest_stage; i++) अणु
		अगर ((ad714x->sensor_val[i] - ad714x->sensor_val[i + 1])
			> (ad714x->sensor_val[i + 1] / 10))
			वापस 1;
	पूर्ण

	क्रम (i = sw->y_highest_stage; i < hw->y_end_stage; i++) अणु
		अगर ((ad714x->sensor_val[i + 1] - ad714x->sensor_val[i])
			> (ad714x->sensor_val[i] / 10))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If only one finger is used to activate the touch pad then only 1 peak will be
 * रेजिस्टरed in the distribution. This peak and the 2 adjacent sensors will be
 * used in the calculation of the असलolute position. This will prevent hand
 * shaकरोws to affect the असलolute position calculation.
 */
अटल व्योम touchpad_cal_असल_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	काष्ठा ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];

	sw->x_असल_pos = ad714x_cal_असल_pos(ad714x, hw->x_start_stage,
			hw->x_end_stage, sw->x_highest_stage, hw->x_max_coord);
	sw->y_असल_pos = ad714x_cal_असल_pos(ad714x, hw->y_start_stage,
			hw->y_end_stage, sw->y_highest_stage, hw->y_max_coord);

	dev_dbg(ad714x->dev, "touchpad %d absolute position:(%d, %d)\n", idx,
			sw->x_असल_pos, sw->y_असल_pos);
पूर्ण

अटल व्योम touchpad_cal_flt_pos(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];

	sw->x_flt_pos = (sw->x_flt_pos * (10 - 4) +
			sw->x_असल_pos * 4)/10;
	sw->y_flt_pos = (sw->y_flt_pos * (10 - 4) +
			sw->y_असल_pos * 4)/10;

	dev_dbg(ad714x->dev, "touchpad %d filter position:(%d, %d)\n",
			idx, sw->x_flt_pos, sw->y_flt_pos);
पूर्ण

/*
 * To prevent distortion from showing in the असलolute position, it is
 * necessary to detect the end poपूर्णांकs. When endpoपूर्णांकs are detected, the
 * driver stops updating the status variables with असलolute positions.
 * End poपूर्णांकs are detected on the 4 edges of the touchpad sensor. The
 * method to detect them is the same क्रम all 4.
 * To detect the end poपूर्णांकs, the firmware computes the dअगरference in
 * percent between the sensor on the edge and the adjacent one. The
 * dअगरference is calculated in percent in order to make the end poपूर्णांक
 * detection independent of the pressure.
 */

#घोषणा LEFT_END_POINT_DETECTION_LEVEL                  550
#घोषणा RIGHT_END_POINT_DETECTION_LEVEL                 750
#घोषणा LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL         850
#घोषणा TOP_END_POINT_DETECTION_LEVEL                   550
#घोषणा BOTTOM_END_POINT_DETECTION_LEVEL                950
#घोषणा TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL         700
अटल पूर्णांक touchpad_check_endpoपूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	काष्ठा ad714x_touchpad_drv *sw  = &ad714x->sw->touchpad[idx];
	पूर्णांक percent_sensor_dअगरf;

	/* left endpoपूर्णांक detect */
	percent_sensor_dअगरf = (ad714x->sensor_val[hw->x_start_stage] -
			ad714x->sensor_val[hw->x_start_stage + 1]) * 100 /
			ad714x->sensor_val[hw->x_start_stage + 1];
	अगर (!sw->left_ep) अणु
		अगर (percent_sensor_dअगरf >= LEFT_END_POINT_DETECTION_LEVEL)  अणु
			sw->left_ep = 1;
			sw->left_ep_val =
				ad714x->sensor_val[hw->x_start_stage + 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((percent_sensor_dअगरf < LEFT_END_POINT_DETECTION_LEVEL) &&
		    (ad714x->sensor_val[hw->x_start_stage + 1] >
		     LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL + sw->left_ep_val))
			sw->left_ep = 0;
	पूर्ण

	/* right endpoपूर्णांक detect */
	percent_sensor_dअगरf = (ad714x->sensor_val[hw->x_end_stage] -
			ad714x->sensor_val[hw->x_end_stage - 1]) * 100 /
			ad714x->sensor_val[hw->x_end_stage - 1];
	अगर (!sw->right_ep) अणु
		अगर (percent_sensor_dअगरf >= RIGHT_END_POINT_DETECTION_LEVEL)  अणु
			sw->right_ep = 1;
			sw->right_ep_val =
				ad714x->sensor_val[hw->x_end_stage - 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((percent_sensor_dअगरf < RIGHT_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->x_end_stage - 1] >
		LEFT_RIGHT_END_POINT_DEAVTIVALION_LEVEL + sw->right_ep_val))
			sw->right_ep = 0;
	पूर्ण

	/* top endpoपूर्णांक detect */
	percent_sensor_dअगरf = (ad714x->sensor_val[hw->y_start_stage] -
			ad714x->sensor_val[hw->y_start_stage + 1]) * 100 /
			ad714x->sensor_val[hw->y_start_stage + 1];
	अगर (!sw->top_ep) अणु
		अगर (percent_sensor_dअगरf >= TOP_END_POINT_DETECTION_LEVEL)  अणु
			sw->top_ep = 1;
			sw->top_ep_val =
				ad714x->sensor_val[hw->y_start_stage + 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((percent_sensor_dअगरf < TOP_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->y_start_stage + 1] >
		TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL + sw->top_ep_val))
			sw->top_ep = 0;
	पूर्ण

	/* bottom endpoपूर्णांक detect */
	percent_sensor_dअगरf = (ad714x->sensor_val[hw->y_end_stage] -
		ad714x->sensor_val[hw->y_end_stage - 1]) * 100 /
		ad714x->sensor_val[hw->y_end_stage - 1];
	अगर (!sw->bottom_ep) अणु
		अगर (percent_sensor_dअगरf >= BOTTOM_END_POINT_DETECTION_LEVEL)  अणु
			sw->bottom_ep = 1;
			sw->bottom_ep_val =
				ad714x->sensor_val[hw->y_end_stage - 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((percent_sensor_dअगरf < BOTTOM_END_POINT_DETECTION_LEVEL) &&
		(ad714x->sensor_val[hw->y_end_stage - 1] >
		 TOP_BOTTOM_END_POINT_DEAVTIVALION_LEVEL + sw->bottom_ep_val))
			sw->bottom_ep = 0;
	पूर्ण

	वापस sw->left_ep || sw->right_ep || sw->top_ep || sw->bottom_ep;
पूर्ण

अटल व्योम touchpad_use_com_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];

	ad714x_use_com_पूर्णांक(ad714x, hw->x_start_stage, hw->x_end_stage);
पूर्ण

अटल व्योम touchpad_use_thr_पूर्णांक(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];

	ad714x_use_thr_पूर्णांक(ad714x, hw->x_start_stage, hw->x_end_stage);
	ad714x_use_thr_पूर्णांक(ad714x, hw->y_start_stage, hw->y_end_stage);
पूर्ण

अटल व्योम ad714x_touchpad_state_machine(काष्ठा ad714x_chip *ad714x, पूर्णांक idx)
अणु
	काष्ठा ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	काष्ठा ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];
	अचिन्हित लघु h_state, c_state;
	अचिन्हित लघु mask;

	mask = (((1 << (hw->x_end_stage + 1)) - 1) -
		((1 << hw->x_start_stage) - 1)) +
		(((1 << (hw->y_end_stage + 1)) - 1) -
		((1 << hw->y_start_stage) - 1));

	h_state = ad714x->h_state & mask;
	c_state = ad714x->c_state & mask;

	चयन (sw->state) अणु
	हाल IDLE:
		अगर (h_state) अणु
			sw->state = JITTER;
			/* In End of Conversion पूर्णांकerrupt mode, the AD714X
			 * continuously generates hardware पूर्णांकerrupts.
			 */
			touchpad_use_com_पूर्णांक(ad714x, idx);
			dev_dbg(ad714x->dev, "touchpad %d touched\n", idx);
		पूर्ण
		अवरोध;

	हाल JITTER:
		अगर (c_state == mask) अणु
			touchpad_cal_sensor_val(ad714x, idx);
			touchpad_cal_highest_stage(ad714x, idx);
			अगर ((!touchpad_check_second_peak(ad714x, idx)) &&
				(!touchpad_check_endpoपूर्णांक(ad714x, idx))) अणु
				dev_dbg(ad714x->dev,
					"touchpad%d, 2 fingers or endpoint\n",
					idx);
				touchpad_cal_असल_pos(ad714x, idx);
				sw->x_flt_pos = sw->x_असल_pos;
				sw->y_flt_pos = sw->y_असल_pos;
				sw->state = ACTIVE;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ACTIVE:
		अगर (c_state == mask) अणु
			अगर (h_state) अणु
				touchpad_cal_sensor_val(ad714x, idx);
				touchpad_cal_highest_stage(ad714x, idx);
				अगर ((!touchpad_check_second_peak(ad714x, idx))
				  && (!touchpad_check_endpoपूर्णांक(ad714x, idx))) अणु
					touchpad_cal_असल_pos(ad714x, idx);
					touchpad_cal_flt_pos(ad714x, idx);
					input_report_असल(sw->input, ABS_X,
						sw->x_flt_pos);
					input_report_असल(sw->input, ABS_Y,
						sw->y_flt_pos);
					input_report_key(sw->input, BTN_TOUCH,
						1);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* When the user lअगरts off the sensor, configure
				 * the AD714X back to threshold पूर्णांकerrupt mode.
				 */
				touchpad_use_thr_पूर्णांक(ad714x, idx);
				sw->state = IDLE;
				input_report_key(sw->input, BTN_TOUCH, 0);
				dev_dbg(ad714x->dev, "touchpad %d released\n",
					idx);
			पूर्ण
			input_sync(sw->input);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ad714x_hw_detect(काष्ठा ad714x_chip *ad714x)
अणु
	अचिन्हित लघु data;

	ad714x->पढ़ो(ad714x, AD714X_PARTID_REG, &data, 1);
	चयन (data & 0xFFF0) अणु
	हाल AD7142_PARTID:
		ad714x->product = 0x7142;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7142 captouch, rev:%d\n",
				ad714x->version);
		वापस 0;

	हाल AD7143_PARTID:
		ad714x->product = 0x7143;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7143 captouch, rev:%d\n",
				ad714x->version);
		वापस 0;

	हाल AD7147_PARTID:
		ad714x->product = 0x7147;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7147(A) captouch, rev:%d\n",
				ad714x->version);
		वापस 0;

	हाल AD7148_PARTID:
		ad714x->product = 0x7148;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7148 captouch, rev:%d\n",
				ad714x->version);
		वापस 0;

	शेष:
		dev_err(ad714x->dev,
			"fail to detect AD714X captouch, read ID is %04x\n",
			data);
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल व्योम ad714x_hw_init(काष्ठा ad714x_chip *ad714x)
अणु
	पूर्णांक i, j;
	अचिन्हित लघु reg_base;
	अचिन्हित लघु data;

	/* configuration CDC and पूर्णांकerrupts */

	क्रम (i = 0; i < STAGE_NUM; i++) अणु
		reg_base = AD714X_STAGECFG_REG + i * STAGE_CFGREG_NUM;
		क्रम (j = 0; j < STAGE_CFGREG_NUM; j++)
			ad714x->ग_लिखो(ad714x, reg_base + j,
					ad714x->hw->stage_cfg_reg[i][j]);
	पूर्ण

	क्रम (i = 0; i < SYS_CFGREG_NUM; i++)
		ad714x->ग_लिखो(ad714x, AD714X_SYSCFG_REG + i,
			ad714x->hw->sys_cfg_reg[i]);
	क्रम (i = 0; i < SYS_CFGREG_NUM; i++)
		ad714x->पढ़ो(ad714x, AD714X_SYSCFG_REG + i, &data, 1);

	ad714x->ग_लिखो(ad714x, AD714X_STG_CAL_EN_REG, 0xFFF);

	/* clear all पूर्णांकerrupts */
	ad714x->पढ़ो(ad714x, STG_LOW_INT_STA_REG, &ad714x->l_state, 3);
पूर्ण

अटल irqवापस_t ad714x_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ad714x_chip *ad714x = data;
	पूर्णांक i;

	mutex_lock(&ad714x->mutex);

	ad714x->पढ़ो(ad714x, STG_LOW_INT_STA_REG, &ad714x->l_state, 3);

	क्रम (i = 0; i < ad714x->hw->button_num; i++)
		ad714x_button_state_machine(ad714x, i);
	क्रम (i = 0; i < ad714x->hw->slider_num; i++)
		ad714x_slider_state_machine(ad714x, i);
	क्रम (i = 0; i < ad714x->hw->wheel_num; i++)
		ad714x_wheel_state_machine(ad714x, i);
	क्रम (i = 0; i < ad714x->hw->touchpad_num; i++)
		ad714x_touchpad_state_machine(ad714x, i);

	mutex_unlock(&ad714x->mutex);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा ad714x_chip *ad714x_probe(काष्ठा device *dev, u16 bus_type, पूर्णांक irq,
				 ad714x_पढ़ो_t पढ़ो, ad714x_ग_लिखो_t ग_लिखो)
अणु
	पूर्णांक i;
	पूर्णांक error;
	काष्ठा input_dev *input;

	काष्ठा ad714x_platक्रमm_data *plat_data = dev_get_platdata(dev);
	काष्ठा ad714x_chip *ad714x;
	व्योम *drv_mem;
	अचिन्हित दीर्घ irqflags;

	काष्ठा ad714x_button_drv *bt_drv;
	काष्ठा ad714x_slider_drv *sd_drv;
	काष्ठा ad714x_wheel_drv *wl_drv;
	काष्ठा ad714x_touchpad_drv *tp_drv;


	अगर (irq <= 0) अणु
		dev_err(dev, "IRQ not configured!\n");
		error = -EINVAL;
		वापस ERR_PTR(error);
	पूर्ण

	अगर (dev_get_platdata(dev) == शून्य) अणु
		dev_err(dev, "platform data for ad714x doesn't exist\n");
		error = -EINVAL;
		वापस ERR_PTR(error);
	पूर्ण

	ad714x = devm_kzalloc(dev, माप(*ad714x) + माप(*ad714x->sw) +
				   माप(*sd_drv) * plat_data->slider_num +
				   माप(*wl_drv) * plat_data->wheel_num +
				   माप(*tp_drv) * plat_data->touchpad_num +
				   माप(*bt_drv) * plat_data->button_num,
			      GFP_KERNEL);
	अगर (!ad714x) अणु
		error = -ENOMEM;
		वापस ERR_PTR(error);
	पूर्ण
	ad714x->hw = plat_data;

	drv_mem = ad714x + 1;
	ad714x->sw = drv_mem;
	drv_mem += माप(*ad714x->sw);
	ad714x->sw->slider = sd_drv = drv_mem;
	drv_mem += माप(*sd_drv) * ad714x->hw->slider_num;
	ad714x->sw->wheel = wl_drv = drv_mem;
	drv_mem += माप(*wl_drv) * ad714x->hw->wheel_num;
	ad714x->sw->touchpad = tp_drv = drv_mem;
	drv_mem += माप(*tp_drv) * ad714x->hw->touchpad_num;
	ad714x->sw->button = bt_drv = drv_mem;
	drv_mem += माप(*bt_drv) * ad714x->hw->button_num;

	ad714x->पढ़ो = पढ़ो;
	ad714x->ग_लिखो = ग_लिखो;
	ad714x->irq = irq;
	ad714x->dev = dev;

	error = ad714x_hw_detect(ad714x);
	अगर (error)
		वापस ERR_PTR(error);

	/* initialize and request sw/hw resources */

	ad714x_hw_init(ad714x);
	mutex_init(&ad714x->mutex);

	/* a slider uses one input_dev instance */
	अगर (ad714x->hw->slider_num > 0) अणु
		काष्ठा ad714x_slider_plat *sd_plat = ad714x->hw->slider;

		क्रम (i = 0; i < ad714x->hw->slider_num; i++) अणु
			input = devm_input_allocate_device(dev);
			अगर (!input)
				वापस ERR_PTR(-ENOMEM);

			__set_bit(EV_ABS, input->evbit);
			__set_bit(EV_KEY, input->evbit);
			__set_bit(ABS_X, input->असलbit);
			__set_bit(BTN_TOUCH, input->keybit);
			input_set_असल_params(input,
				ABS_X, 0, sd_plat->max_coord, 0, 0);

			input->id.bustype = bus_type;
			input->id.product = ad714x->product;
			input->id.version = ad714x->version;
			input->name = "ad714x_captouch_slider";
			input->dev.parent = dev;

			error = input_रेजिस्टर_device(input);
			अगर (error)
				वापस ERR_PTR(error);

			sd_drv[i].input = input;
		पूर्ण
	पूर्ण

	/* a wheel uses one input_dev instance */
	अगर (ad714x->hw->wheel_num > 0) अणु
		काष्ठा ad714x_wheel_plat *wl_plat = ad714x->hw->wheel;

		क्रम (i = 0; i < ad714x->hw->wheel_num; i++) अणु
			input = devm_input_allocate_device(dev);
			अगर (!input)
				वापस ERR_PTR(-ENOMEM);

			__set_bit(EV_KEY, input->evbit);
			__set_bit(EV_ABS, input->evbit);
			__set_bit(ABS_WHEEL, input->असलbit);
			__set_bit(BTN_TOUCH, input->keybit);
			input_set_असल_params(input,
				ABS_WHEEL, 0, wl_plat->max_coord, 0, 0);

			input->id.bustype = bus_type;
			input->id.product = ad714x->product;
			input->id.version = ad714x->version;
			input->name = "ad714x_captouch_wheel";
			input->dev.parent = dev;

			error = input_रेजिस्टर_device(input);
			अगर (error)
				वापस ERR_PTR(error);

			wl_drv[i].input = input;
		पूर्ण
	पूर्ण

	/* a touchpad uses one input_dev instance */
	अगर (ad714x->hw->touchpad_num > 0) अणु
		काष्ठा ad714x_touchpad_plat *tp_plat = ad714x->hw->touchpad;

		क्रम (i = 0; i < ad714x->hw->touchpad_num; i++) अणु
			input = devm_input_allocate_device(dev);
			अगर (!input)
				वापस ERR_PTR(-ENOMEM);

			__set_bit(EV_ABS, input->evbit);
			__set_bit(EV_KEY, input->evbit);
			__set_bit(ABS_X, input->असलbit);
			__set_bit(ABS_Y, input->असलbit);
			__set_bit(BTN_TOUCH, input->keybit);
			input_set_असल_params(input,
				ABS_X, 0, tp_plat->x_max_coord, 0, 0);
			input_set_असल_params(input,
				ABS_Y, 0, tp_plat->y_max_coord, 0, 0);

			input->id.bustype = bus_type;
			input->id.product = ad714x->product;
			input->id.version = ad714x->version;
			input->name = "ad714x_captouch_pad";
			input->dev.parent = dev;

			error = input_रेजिस्टर_device(input);
			अगर (error)
				वापस ERR_PTR(error);

			tp_drv[i].input = input;
		पूर्ण
	पूर्ण

	/* all buttons use one input node */
	अगर (ad714x->hw->button_num > 0) अणु
		काष्ठा ad714x_button_plat *bt_plat = ad714x->hw->button;

		input = devm_input_allocate_device(dev);
		अगर (!input) अणु
			error = -ENOMEM;
			वापस ERR_PTR(error);
		पूर्ण

		__set_bit(EV_KEY, input->evbit);
		क्रम (i = 0; i < ad714x->hw->button_num; i++) अणु
			bt_drv[i].input = input;
			__set_bit(bt_plat[i].keycode, input->keybit);
		पूर्ण

		input->id.bustype = bus_type;
		input->id.product = ad714x->product;
		input->id.version = ad714x->version;
		input->name = "ad714x_captouch_button";
		input->dev.parent = dev;

		error = input_रेजिस्टर_device(input);
		अगर (error)
			वापस ERR_PTR(error);
	पूर्ण

	irqflags = plat_data->irqflags ?: IRQF_TRIGGER_FALLING;
	irqflags |= IRQF_ONESHOT;

	error = devm_request_thपढ़ोed_irq(dev, ad714x->irq, शून्य,
					  ad714x_पूर्णांकerrupt_thपढ़ो,
					  irqflags, "ad714x_captouch", ad714x);
	अगर (error) अणु
		dev_err(dev, "can't allocate irq %d\n", ad714x->irq);
		वापस ERR_PTR(error);
	पूर्ण

	वापस ad714x;
पूर्ण
EXPORT_SYMBOL(ad714x_probe);

#अगर_घोषित CONFIG_PM
पूर्णांक ad714x_disable(काष्ठा ad714x_chip *ad714x)
अणु
	अचिन्हित लघु data;

	dev_dbg(ad714x->dev, "%s enter\n", __func__);

	mutex_lock(&ad714x->mutex);

	data = ad714x->hw->sys_cfg_reg[AD714X_PWR_CTRL] | 0x3;
	ad714x->ग_लिखो(ad714x, AD714X_PWR_CTRL, data);

	mutex_unlock(&ad714x->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ad714x_disable);

पूर्णांक ad714x_enable(काष्ठा ad714x_chip *ad714x)
अणु
	dev_dbg(ad714x->dev, "%s enter\n", __func__);

	mutex_lock(&ad714x->mutex);

	/* resume to non-shutकरोwn mode */

	ad714x->ग_लिखो(ad714x, AD714X_PWR_CTRL,
			ad714x->hw->sys_cfg_reg[AD714X_PWR_CTRL]);

	/* make sure the पूर्णांकerrupt output line is not low level after resume,
	 * otherwise we will get no chance to enter falling-edge irq again
	 */

	ad714x->पढ़ो(ad714x, STG_LOW_INT_STA_REG, &ad714x->l_state, 3);

	mutex_unlock(&ad714x->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ad714x_enable);
#पूर्ण_अगर

MODULE_DESCRIPTION("Analog Devices AD714X Capacitance Touch Sensor Driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
