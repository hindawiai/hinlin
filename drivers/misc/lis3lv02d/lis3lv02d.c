<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  lis3lv02d.c - ST LIS3LV02DL accelerometer driver
 *
 *  Copyright (C) 2007-2008 Yan Burman
 *  Copyright (C) 2008 Eric Piel
 *  Copyright (C) 2008-2009 Pavel Machek
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/atomic.h>
#समावेश <linux/of_device.h>
#समावेश "lis3lv02d.h"

#घोषणा DRIVER_NAME     "lis3lv02d"

/* joystick device poll पूर्णांकerval in milliseconds */
#घोषणा MDPS_POLL_INTERVAL 50
#घोषणा MDPS_POLL_MIN	   0
#घोषणा MDPS_POLL_MAX	   2000

#घोषणा LIS3_SYSFS_POWERDOWN_DELAY 5000 /* In milliseconds */

#घोषणा SELFTEST_OK	       0
#घोषणा SELFTEST_FAIL	       -1
#घोषणा SELFTEST_IRQ	       -2

#घोषणा IRQ_LINE0	       0
#घोषणा IRQ_LINE1	       1

/*
 * The sensor can also generate पूर्णांकerrupts (DRDY) but it's pretty poपूर्णांकless
 * because they are generated even अगर the data करो not change. So it's better
 * to keep the पूर्णांकerrupt क्रम the मुक्त-fall event. The values are updated at
 * 40Hz (at the lowest frequency), but as it can be pretty समय consuming on
 * some low processor, we poll the sensor only at 20Hz... enough क्रम the
 * joystick.
 */

#घोषणा LIS3_PWRON_DELAY_WAI_12B	(5000)
#घोषणा LIS3_PWRON_DELAY_WAI_8B		(3000)

/*
 * LIS3LV02D spec says 1024 LSBs corresponds 1 G -> 1LSB is 1000/1024 mG
 * LIS302D spec says: 18 mG / digit
 * LIS3_ACCURACY is used to increase accuracy of the पूर्णांकermediate
 * calculation results.
 */
#घोषणा LIS3_ACCURACY			1024
/* Sensitivity values क्रम -2G +2G scale */
#घोषणा LIS3_SENSITIVITY_12B		((LIS3_ACCURACY * 1000) / 1024)
#घोषणा LIS3_SENSITIVITY_8B		(18 * LIS3_ACCURACY)

/*
 * LIS331DLH spec says 1LSBs corresponds 4G/4096 -> 1LSB is 1000/1024 mG.
 * Below macros defines sensitivity values क्रम +/-2G. Dataout bits क्रम
 * +/-2G range is 12 bits so 4 bits adjusपंचांगent must be करोne to get 12bit
 * data from 16bit value. Currently this driver supports only 2G range.
 */
#घोषणा LIS3DLH_SENSITIVITY_2G		((LIS3_ACCURACY * 1000) / 1024)
#घोषणा SHIFT_ADJ_2G			4

#घोषणा LIS3_DEFAULT_FUZZ_12B		3
#घोषणा LIS3_DEFAULT_FLAT_12B		3
#घोषणा LIS3_DEFAULT_FUZZ_8B		1
#घोषणा LIS3_DEFAULT_FLAT_8B		1

काष्ठा lis3lv02d lis3_dev = अणु
	.misc_रुको   = __WAIT_QUEUE_HEAD_INITIALIZER(lis3_dev.misc_रुको),
पूर्ण;
EXPORT_SYMBOL_GPL(lis3_dev);

/* just like param_set_पूर्णांक() but करोes sanity-check so that it won't poपूर्णांक
 * over the axis array size
 */
अटल पूर्णांक param_set_axis(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = param_set_पूर्णांक(val, kp);
	अगर (!ret) अणु
		पूर्णांक val = *(पूर्णांक *)kp->arg;
		अगर (val < 0)
			val = -val;
		अगर (!val || val > 3)
			वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_axis = अणु
	.set = param_set_axis,
	.get = param_get_पूर्णांक,
पूर्ण;

#घोषणा param_check_axis(name, p) param_check_पूर्णांक(name, p)

module_param_array_named(axes, lis3_dev.ac.as_array, axis, शून्य, 0644);
MODULE_PARM_DESC(axes, "Axis-mapping for x,y,z directions");

अटल s16 lis3lv02d_पढ़ो_8(काष्ठा lis3lv02d *lis3, पूर्णांक reg)
अणु
	s8 lo;
	अगर (lis3->पढ़ो(lis3, reg, &lo) < 0)
		वापस 0;

	वापस lo;
पूर्ण

अटल s16 lis3lv02d_पढ़ो_12(काष्ठा lis3lv02d *lis3, पूर्णांक reg)
अणु
	u8 lo, hi;

	lis3->पढ़ो(lis3, reg - 1, &lo);
	lis3->पढ़ो(lis3, reg, &hi);
	/* In "12 bit right justified" mode, bit 6, bit 7, bit 8 = bit 5 */
	वापस (s16)((hi << 8) | lo);
पूर्ण

/* 12bits क्रम 2G range, 13 bits क्रम 4G range and 14 bits क्रम 8G range */
अटल s16 lis331dlh_पढ़ो_data(काष्ठा lis3lv02d *lis3, पूर्णांक reg)
अणु
	u8 lo, hi;
	पूर्णांक v;

	lis3->पढ़ो(lis3, reg - 1, &lo);
	lis3->पढ़ो(lis3, reg, &hi);
	v = (पूर्णांक) ((hi << 8) | lo);

	वापस (s16) v >> lis3->shअगरt_adj;
पूर्ण

/**
 * lis3lv02d_get_axis - For the given axis, give the value converted
 * @axis:      1,2,3 - can also be negative
 * @hw_values: raw values वापसed by the hardware
 *
 * Returns the converted value.
 */
अटल अंतरभूत पूर्णांक lis3lv02d_get_axis(s8 axis, पूर्णांक hw_values[3])
अणु
	अगर (axis > 0)
		वापस hw_values[axis - 1];
	अन्यथा
		वापस -hw_values[-axis - 1];
पूर्ण

/**
 * lis3lv02d_get_xyz - Get X, Y and Z axis values from the accelerometer
 * @lis3: poपूर्णांकer to the device काष्ठा
 * @x:    where to store the X axis value
 * @y:    where to store the Y axis value
 * @z:    where to store the Z axis value
 *
 * Note that 40Hz input device can eat up about 10% CPU at 800MHZ
 */
अटल व्योम lis3lv02d_get_xyz(काष्ठा lis3lv02d *lis3, पूर्णांक *x, पूर्णांक *y, पूर्णांक *z)
अणु
	पूर्णांक position[3];
	पूर्णांक i;

	अगर (lis3->blkपढ़ो) अणु
		अगर (lis3->whoami == WAI_12B) अणु
			u16 data[3];
			lis3->blkपढ़ो(lis3, OUTX_L, 6, (u8 *)data);
			क्रम (i = 0; i < 3; i++)
				position[i] = (s16)le16_to_cpu(data[i]);
		पूर्ण अन्यथा अणु
			u8 data[5];
			/* Data: x, dummy, y, dummy, z */
			lis3->blkपढ़ो(lis3, OUTX, 5, data);
			क्रम (i = 0; i < 3; i++)
				position[i] = (s8)data[i * 2];
		पूर्ण
	पूर्ण अन्यथा अणु
		position[0] = lis3->पढ़ो_data(lis3, OUTX);
		position[1] = lis3->पढ़ो_data(lis3, OUTY);
		position[2] = lis3->पढ़ो_data(lis3, OUTZ);
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		position[i] = (position[i] * lis3->scale) / LIS3_ACCURACY;

	*x = lis3lv02d_get_axis(lis3->ac.x, position);
	*y = lis3lv02d_get_axis(lis3->ac.y, position);
	*z = lis3lv02d_get_axis(lis3->ac.z, position);
पूर्ण

/* conversion btw sampling rate and the रेजिस्टर values */
अटल पूर्णांक lis3_12_rates[4] = अणु40, 160, 640, 2560पूर्ण;
अटल पूर्णांक lis3_8_rates[2] = अणु100, 400पूर्ण;
अटल पूर्णांक lis3_3dc_rates[16] = अणु0, 1, 10, 25, 50, 100, 200, 400, 1600, 5000पूर्ण;
अटल पूर्णांक lis3_3dlh_rates[4] = अणु50, 100, 400, 1000पूर्ण;

/* ODR is Output Data Rate */
अटल पूर्णांक lis3lv02d_get_odr_index(काष्ठा lis3lv02d *lis3)
अणु
	u8 ctrl;
	पूर्णांक shअगरt;

	lis3->पढ़ो(lis3, CTRL_REG1, &ctrl);
	ctrl &= lis3->odr_mask;
	shअगरt = ffs(lis3->odr_mask) - 1;
	वापस (ctrl >> shअगरt);
पूर्ण

अटल पूर्णांक lis3lv02d_get_pwron_रुको(काष्ठा lis3lv02d *lis3)
अणु
	पूर्णांक odr_idx = lis3lv02d_get_odr_index(lis3);
	पूर्णांक भाग = lis3->odrs[odr_idx];

	अगर (भाग == 0) अणु
		अगर (odr_idx == 0) अणु
			/* Power-करोwn mode, not sampling no need to sleep */
			वापस 0;
		पूर्ण

		dev_err(&lis3->pdev->dev, "Error unknown odrs-index: %d\n", odr_idx);
		वापस -ENXIO;
	पूर्ण

	/* LIS3 घातer on delay is quite दीर्घ */
	msleep(lis3->pwron_delay / भाग);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_set_odr(काष्ठा lis3lv02d *lis3, पूर्णांक rate)
अणु
	u8 ctrl;
	पूर्णांक i, len, shअगरt;

	अगर (!rate)
		वापस -EINVAL;

	lis3->पढ़ो(lis3, CTRL_REG1, &ctrl);
	ctrl &= ~lis3->odr_mask;
	len = 1 << hweight_दीर्घ(lis3->odr_mask); /* # of possible values */
	shअगरt = ffs(lis3->odr_mask) - 1;

	क्रम (i = 0; i < len; i++)
		अगर (lis3->odrs[i] == rate) अणु
			lis3->ग_लिखो(lis3, CTRL_REG1,
					ctrl | (i << shअगरt));
			वापस 0;
		पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lis3lv02d_selftest(काष्ठा lis3lv02d *lis3, s16 results[3])
अणु
	u8 ctlreg, reg;
	s16 x, y, z;
	u8 selftest;
	पूर्णांक ret;
	u8 ctrl_reg_data;
	अचिन्हित अक्षर irq_cfg;

	mutex_lock(&lis3->mutex);

	irq_cfg = lis3->irq_cfg;
	अगर (lis3->whoami == WAI_8B) अणु
		lis3->data_पढ़ोy_count[IRQ_LINE0] = 0;
		lis3->data_पढ़ोy_count[IRQ_LINE1] = 0;

		/* Change पूर्णांकerrupt cfg to data पढ़ोy क्रम selftest */
		atomic_inc(&lis3->wake_thपढ़ो);
		lis3->irq_cfg = LIS3_IRQ1_DATA_READY | LIS3_IRQ2_DATA_READY;
		lis3->पढ़ो(lis3, CTRL_REG3, &ctrl_reg_data);
		lis3->ग_लिखो(lis3, CTRL_REG3, (ctrl_reg_data &
				~(LIS3_IRQ1_MASK | LIS3_IRQ2_MASK)) |
				(LIS3_IRQ1_DATA_READY | LIS3_IRQ2_DATA_READY));
	पूर्ण

	अगर ((lis3->whoami == WAI_3DC) || (lis3->whoami == WAI_3DLH)) अणु
		ctlreg = CTRL_REG4;
		selftest = CTRL4_ST0;
	पूर्ण अन्यथा अणु
		ctlreg = CTRL_REG1;
		अगर (lis3->whoami == WAI_12B)
			selftest = CTRL1_ST;
		अन्यथा
			selftest = CTRL1_STP;
	पूर्ण

	lis3->पढ़ो(lis3, ctlreg, &reg);
	lis3->ग_लिखो(lis3, ctlreg, (reg | selftest));
	ret = lis3lv02d_get_pwron_रुको(lis3);
	अगर (ret)
		जाओ fail;

	/* Read directly to aव्योम axis remap */
	x = lis3->पढ़ो_data(lis3, OUTX);
	y = lis3->पढ़ो_data(lis3, OUTY);
	z = lis3->पढ़ो_data(lis3, OUTZ);

	/* back to normal settings */
	lis3->ग_लिखो(lis3, ctlreg, reg);
	ret = lis3lv02d_get_pwron_रुको(lis3);
	अगर (ret)
		जाओ fail;

	results[0] = x - lis3->पढ़ो_data(lis3, OUTX);
	results[1] = y - lis3->पढ़ो_data(lis3, OUTY);
	results[2] = z - lis3->पढ़ो_data(lis3, OUTZ);

	ret = 0;

	अगर (lis3->whoami == WAI_8B) अणु
		/* Restore original पूर्णांकerrupt configuration */
		atomic_dec(&lis3->wake_thपढ़ो);
		lis3->ग_लिखो(lis3, CTRL_REG3, ctrl_reg_data);
		lis3->irq_cfg = irq_cfg;

		अगर ((irq_cfg & LIS3_IRQ1_MASK) &&
			lis3->data_पढ़ोy_count[IRQ_LINE0] < 2) अणु
			ret = SELFTEST_IRQ;
			जाओ fail;
		पूर्ण

		अगर ((irq_cfg & LIS3_IRQ2_MASK) &&
			lis3->data_पढ़ोy_count[IRQ_LINE1] < 2) अणु
			ret = SELFTEST_IRQ;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (lis3->pdata) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 3; i++) अणु
			/* Check against selftest acceptance limits */
			अगर ((results[i] < lis3->pdata->st_min_limits[i]) ||
			    (results[i] > lis3->pdata->st_max_limits[i])) अणु
				ret = SELFTEST_FAIL;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	/* test passed */
fail:
	mutex_unlock(&lis3->mutex);
	वापस ret;
पूर्ण

/*
 * Order of रेजिस्टरs in the list affects to order of the restore process.
 * Perhaps it is a good idea to set पूर्णांकerrupt enable रेजिस्टर as a last one
 * after all other configurations
 */
अटल u8 lis3_wai8_regs[] = अणु FF_WU_CFG_1, FF_WU_THS_1, FF_WU_DURATION_1,
			       FF_WU_CFG_2, FF_WU_THS_2, FF_WU_DURATION_2,
			       CLICK_CFG, CLICK_SRC, CLICK_THSY_X, CLICK_THSZ,
			       CLICK_TIMELIMIT, CLICK_LATENCY, CLICK_WINDOW,
			       CTRL_REG1, CTRL_REG2, CTRL_REG3पूर्ण;

अटल u8 lis3_wai12_regs[] = अणुFF_WU_CFG, FF_WU_THS_L, FF_WU_THS_H,
			       FF_WU_DURATION, DD_CFG, DD_THSI_L, DD_THSI_H,
			       DD_THSE_L, DD_THSE_H,
			       CTRL_REG1, CTRL_REG3, CTRL_REG2पूर्ण;

अटल अंतरभूत व्योम lis3_context_save(काष्ठा lis3lv02d *lis3)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < lis3->regs_size; i++)
		lis3->पढ़ो(lis3, lis3->regs[i], &lis3->reg_cache[i]);
	lis3->regs_stored = true;
पूर्ण

अटल अंतरभूत व्योम lis3_context_restore(काष्ठा lis3lv02d *lis3)
अणु
	पूर्णांक i;
	अगर (lis3->regs_stored)
		क्रम (i = 0; i < lis3->regs_size; i++)
			lis3->ग_लिखो(lis3, lis3->regs[i], lis3->reg_cache[i]);
पूर्ण

व्योम lis3lv02d_घातeroff(काष्ठा lis3lv02d *lis3)
अणु
	अगर (lis3->reg_ctrl)
		lis3_context_save(lis3);
	/* disable X,Y,Z axis and घातer करोwn */
	lis3->ग_लिखो(lis3, CTRL_REG1, 0x00);
	अगर (lis3->reg_ctrl)
		lis3->reg_ctrl(lis3, LIS3_REG_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_घातeroff);

पूर्णांक lis3lv02d_घातeron(काष्ठा lis3lv02d *lis3)
अणु
	पूर्णांक err;
	u8 reg;

	lis3->init(lis3);

	/*
	 * Common configuration
	 * BDU: (12 bits sensors only) LSB and MSB values are not updated until
	 *      both have been पढ़ो. So the value पढ़ो will always be correct.
	 * Set BOOT bit to refresh factory tuning values.
	 */
	अगर (lis3->pdata) अणु
		lis3->पढ़ो(lis3, CTRL_REG2, &reg);
		अगर (lis3->whoami ==  WAI_12B)
			reg |= CTRL2_BDU | CTRL2_BOOT;
		अन्यथा अगर (lis3->whoami ==  WAI_3DLH)
			reg |= CTRL2_BOOT_3DLH;
		अन्यथा
			reg |= CTRL2_BOOT_8B;
		lis3->ग_लिखो(lis3, CTRL_REG2, reg);

		अगर (lis3->whoami ==  WAI_3DLH) अणु
			lis3->पढ़ो(lis3, CTRL_REG4, &reg);
			reg |= CTRL4_BDU;
			lis3->ग_लिखो(lis3, CTRL_REG4, reg);
		पूर्ण
	पूर्ण

	err = lis3lv02d_get_pwron_रुको(lis3);
	अगर (err)
		वापस err;

	अगर (lis3->reg_ctrl)
		lis3_context_restore(lis3);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_घातeron);


अटल व्योम lis3lv02d_joystick_poll(काष्ठा input_dev *input)
अणु
	काष्ठा lis3lv02d *lis3 = input_get_drvdata(input);
	पूर्णांक x, y, z;

	mutex_lock(&lis3->mutex);
	lis3lv02d_get_xyz(lis3, &x, &y, &z);
	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_असल(input, ABS_Z, z);
	input_sync(input);
	mutex_unlock(&lis3->mutex);
पूर्ण

अटल पूर्णांक lis3lv02d_joystick_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा lis3lv02d *lis3 = input_get_drvdata(input);

	अगर (lis3->pm_dev)
		pm_runसमय_get_sync(lis3->pm_dev);

	अगर (lis3->pdata && lis3->whoami == WAI_8B && lis3->idev)
		atomic_set(&lis3->wake_thपढ़ो, 1);
	/*
	 * Update coordinates क्रम the हाल where poll पूर्णांकerval is 0 and
	 * the chip in running purely under पूर्णांकerrupt control
	 */
	lis3lv02d_joystick_poll(input);

	वापस 0;
पूर्ण

अटल व्योम lis3lv02d_joystick_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा lis3lv02d *lis3 = input_get_drvdata(input);

	atomic_set(&lis3->wake_thपढ़ो, 0);
	अगर (lis3->pm_dev)
		pm_runसमय_put(lis3->pm_dev);
पूर्ण

अटल irqवापस_t lis302dl_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lis3lv02d *lis3 = data;

	अगर (!test_bit(0, &lis3->misc_खोलोed))
		जाओ out;

	/*
	 * Be careful: on some HP laptops the bios क्रमce DD when on battery and
	 * the lid is बंदd. This leads to पूर्णांकerrupts as soon as a little move
	 * is करोne.
	 */
	atomic_inc(&lis3->count);

	wake_up_पूर्णांकerruptible(&lis3->misc_रुको);
	समाप्त_fasync(&lis3->async_queue, SIGIO, POLL_IN);
out:
	अगर (atomic_पढ़ो(&lis3->wake_thपढ़ो))
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lis302dl_पूर्णांकerrupt_handle_click(काष्ठा lis3lv02d *lis3)
अणु
	काष्ठा input_dev *dev = lis3->idev;
	u8 click_src;

	mutex_lock(&lis3->mutex);
	lis3->पढ़ो(lis3, CLICK_SRC, &click_src);

	अगर (click_src & CLICK_SINGLE_X) अणु
		input_report_key(dev, lis3->mapped_btns[0], 1);
		input_report_key(dev, lis3->mapped_btns[0], 0);
	पूर्ण

	अगर (click_src & CLICK_SINGLE_Y) अणु
		input_report_key(dev, lis3->mapped_btns[1], 1);
		input_report_key(dev, lis3->mapped_btns[1], 0);
	पूर्ण

	अगर (click_src & CLICK_SINGLE_Z) अणु
		input_report_key(dev, lis3->mapped_btns[2], 1);
		input_report_key(dev, lis3->mapped_btns[2], 0);
	पूर्ण
	input_sync(dev);
	mutex_unlock(&lis3->mutex);
पूर्ण

अटल अंतरभूत व्योम lis302dl_data_पढ़ोy(काष्ठा lis3lv02d *lis3, पूर्णांक index)
अणु
	पूर्णांक dummy;

	/* Dummy पढ़ो to ack पूर्णांकerrupt */
	lis3lv02d_get_xyz(lis3, &dummy, &dummy, &dummy);
	lis3->data_पढ़ोy_count[index]++;
पूर्ण

अटल irqवापस_t lis302dl_पूर्णांकerrupt_thपढ़ो1_8b(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lis3lv02d *lis3 = data;
	u8 irq_cfg = lis3->irq_cfg & LIS3_IRQ1_MASK;

	अगर (irq_cfg == LIS3_IRQ1_CLICK)
		lis302dl_पूर्णांकerrupt_handle_click(lis3);
	अन्यथा अगर (unlikely(irq_cfg == LIS3_IRQ1_DATA_READY))
		lis302dl_data_पढ़ोy(lis3, IRQ_LINE0);
	अन्यथा
		lis3lv02d_joystick_poll(lis3->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lis302dl_पूर्णांकerrupt_thपढ़ो2_8b(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lis3lv02d *lis3 = data;
	u8 irq_cfg = lis3->irq_cfg & LIS3_IRQ2_MASK;

	अगर (irq_cfg == LIS3_IRQ2_CLICK)
		lis302dl_पूर्णांकerrupt_handle_click(lis3);
	अन्यथा अगर (unlikely(irq_cfg == LIS3_IRQ2_DATA_READY))
		lis302dl_data_पढ़ोy(lis3, IRQ_LINE1);
	अन्यथा
		lis3lv02d_joystick_poll(lis3->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lis3lv02d_misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा lis3lv02d *lis3 = container_of(file->निजी_data,
					      काष्ठा lis3lv02d, miscdev);

	अगर (test_and_set_bit(0, &lis3->misc_खोलोed))
		वापस -EBUSY; /* alपढ़ोy खोलो */

	अगर (lis3->pm_dev)
		pm_runसमय_get_sync(lis3->pm_dev);

	atomic_set(&lis3->count, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_misc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा lis3lv02d *lis3 = container_of(file->निजी_data,
					      काष्ठा lis3lv02d, miscdev);

	clear_bit(0, &lis3->misc_खोलोed); /* release the device */
	अगर (lis3->pm_dev)
		pm_runसमय_put(lis3->pm_dev);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार lis3lv02d_misc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा lis3lv02d *lis3 = container_of(file->निजी_data,
					      काष्ठा lis3lv02d, miscdev);

	DECLARE_WAITQUEUE(रुको, current);
	u32 data;
	अचिन्हित अक्षर byte_data;
	sमाप_प्रकार retval = 1;

	अगर (count < 1)
		वापस -EINVAL;

	add_रुको_queue(&lis3->misc_रुको, &रुको);
	जबतक (true) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		data = atomic_xchg(&lis3->count, 0);
		अगर (data)
			अवरोध;

		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ out;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			जाओ out;
		पूर्ण

		schedule();
	पूर्ण

	अगर (data < 255)
		byte_data = data;
	अन्यथा
		byte_data = 255;

	/* make sure we are not going पूर्णांकo copy_to_user() with
	 * TASK_INTERRUPTIBLE state */
	set_current_state(TASK_RUNNING);
	अगर (copy_to_user(buf, &byte_data, माप(byte_data)))
		retval = -EFAULT;

out:
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&lis3->misc_रुको, &रुको);

	वापस retval;
पूर्ण

अटल __poll_t lis3lv02d_misc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा lis3lv02d *lis3 = container_of(file->निजी_data,
					      काष्ठा lis3lv02d, miscdev);

	poll_रुको(file, &lis3->misc_रुको, रुको);
	अगर (atomic_पढ़ो(&lis3->count))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_misc_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा lis3lv02d *lis3 = container_of(file->निजी_data,
					      काष्ठा lis3lv02d, miscdev);

	वापस fasync_helper(fd, file, on, &lis3->async_queue);
पूर्ण

अटल स्थिर काष्ठा file_operations lis3lv02d_misc_fops = अणु
	.owner   = THIS_MODULE,
	.llseek  = no_llseek,
	.पढ़ो    = lis3lv02d_misc_पढ़ो,
	.खोलो    = lis3lv02d_misc_खोलो,
	.release = lis3lv02d_misc_release,
	.poll    = lis3lv02d_misc_poll,
	.fasync  = lis3lv02d_misc_fasync,
पूर्ण;

पूर्णांक lis3lv02d_joystick_enable(काष्ठा lis3lv02d *lis3)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक err;
	पूर्णांक max_val, fuzz, flat;
	पूर्णांक btns[] = अणुBTN_X, BTN_Y, BTN_Zपूर्ण;

	अगर (lis3->idev)
		वापस -EINVAL;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name       = "ST LIS3LV02DL Accelerometer";
	input_dev->phys       = DRIVER_NAME "/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr  = 0;
	input_dev->dev.parent = &lis3->pdev->dev;

	input_dev->खोलो = lis3lv02d_joystick_खोलो;
	input_dev->बंद = lis3lv02d_joystick_बंद;

	max_val = (lis3->mdps_max_val * lis3->scale) / LIS3_ACCURACY;
	अगर (lis3->whoami == WAI_12B) अणु
		fuzz = LIS3_DEFAULT_FUZZ_12B;
		flat = LIS3_DEFAULT_FLAT_12B;
	पूर्ण अन्यथा अणु
		fuzz = LIS3_DEFAULT_FUZZ_8B;
		flat = LIS3_DEFAULT_FLAT_8B;
	पूर्ण
	fuzz = (fuzz * lis3->scale) / LIS3_ACCURACY;
	flat = (flat * lis3->scale) / LIS3_ACCURACY;

	input_set_असल_params(input_dev, ABS_X, -max_val, max_val, fuzz, flat);
	input_set_असल_params(input_dev, ABS_Y, -max_val, max_val, fuzz, flat);
	input_set_असल_params(input_dev, ABS_Z, -max_val, max_val, fuzz, flat);

	input_set_drvdata(input_dev, lis3);
	lis3->idev = input_dev;

	err = input_setup_polling(input_dev, lis3lv02d_joystick_poll);
	अगर (err)
		जाओ err_मुक्त_input;

	input_set_poll_पूर्णांकerval(input_dev, MDPS_POLL_INTERVAL);
	input_set_min_poll_पूर्णांकerval(input_dev, MDPS_POLL_MIN);
	input_set_max_poll_पूर्णांकerval(input_dev, MDPS_POLL_MAX);

	lis3->mapped_btns[0] = lis3lv02d_get_axis(असल(lis3->ac.x), btns);
	lis3->mapped_btns[1] = lis3lv02d_get_axis(असल(lis3->ac.y), btns);
	lis3->mapped_btns[2] = lis3lv02d_get_axis(असल(lis3->ac.z), btns);

	err = input_रेजिस्टर_device(lis3->idev);
	अगर (err)
		जाओ err_मुक्त_input;

	वापस 0;

err_मुक्त_input:
	input_मुक्त_device(input_dev);
	lis3->idev = शून्य;
	वापस err;

पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_joystick_enable);

व्योम lis3lv02d_joystick_disable(काष्ठा lis3lv02d *lis3)
अणु
	अगर (lis3->irq)
		मुक्त_irq(lis3->irq, lis3);
	अगर (lis3->pdata && lis3->pdata->irq2)
		मुक्त_irq(lis3->pdata->irq2, lis3);

	अगर (!lis3->idev)
		वापस;

	अगर (lis3->irq)
		misc_deरेजिस्टर(&lis3->miscdev);
	input_unरेजिस्टर_device(lis3->idev);
	lis3->idev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_joystick_disable);

/* Sysfs stuff */
अटल व्योम lis3lv02d_sysfs_घातeron(काष्ठा lis3lv02d *lis3)
अणु
	/*
	 * SYSFS functions are fast visitors so put-call
	 * immediately after the get-call. However, keep
	 * chip running क्रम a जबतक and schedule delayed
	 * suspend. This way periodic sysfs calls करोesn't
	 * suffer from relatively दीर्घ घातer up समय.
	 */

	अगर (lis3->pm_dev) अणु
		pm_runसमय_get_sync(lis3->pm_dev);
		pm_runसमय_put_noidle(lis3->pm_dev);
		pm_schedule_suspend(lis3->pm_dev, LIS3_SYSFS_POWERDOWN_DELAY);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार lis3lv02d_selftest_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lis3lv02d *lis3 = dev_get_drvdata(dev);
	s16 values[3];

	अटल स्थिर अक्षर ok[] = "OK";
	अटल स्थिर अक्षर fail[] = "FAIL";
	अटल स्थिर अक्षर irq[] = "FAIL_IRQ";
	स्थिर अक्षर *res;

	lis3lv02d_sysfs_घातeron(lis3);
	चयन (lis3lv02d_selftest(lis3, values)) अणु
	हाल SELFTEST_FAIL:
		res = fail;
		अवरोध;
	हाल SELFTEST_IRQ:
		res = irq;
		अवरोध;
	हाल SELFTEST_OK:
	शेष:
		res = ok;
		अवरोध;
	पूर्ण
	वापस प्र_लिखो(buf, "%s %d %d %d\n", res,
		values[0], values[1], values[2]);
पूर्ण

अटल sमाप_प्रकार lis3lv02d_position_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lis3lv02d *lis3 = dev_get_drvdata(dev);
	पूर्णांक x, y, z;

	lis3lv02d_sysfs_घातeron(lis3);
	mutex_lock(&lis3->mutex);
	lis3lv02d_get_xyz(lis3, &x, &y, &z);
	mutex_unlock(&lis3->mutex);
	वापस प्र_लिखो(buf, "(%d,%d,%d)\n", x, y, z);
पूर्ण

अटल sमाप_प्रकार lis3lv02d_rate_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lis3lv02d *lis3 = dev_get_drvdata(dev);
	पूर्णांक odr_idx;

	lis3lv02d_sysfs_घातeron(lis3);

	odr_idx = lis3lv02d_get_odr_index(lis3);
	वापस प्र_लिखो(buf, "%d\n", lis3->odrs[odr_idx]);
पूर्ण

अटल sमाप_प्रकार lis3lv02d_rate_set(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा lis3lv02d *lis3 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &rate);
	अगर (ret)
		वापस ret;

	lis3lv02d_sysfs_घातeron(lis3);
	अगर (lis3lv02d_set_odr(lis3, rate))
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(selftest, S_IRUSR, lis3lv02d_selftest_show, शून्य);
अटल DEVICE_ATTR(position, S_IRUGO, lis3lv02d_position_show, शून्य);
अटल DEVICE_ATTR(rate, S_IRUGO | S_IWUSR, lis3lv02d_rate_show,
					    lis3lv02d_rate_set);

अटल काष्ठा attribute *lis3lv02d_attributes[] = अणु
	&dev_attr_selftest.attr,
	&dev_attr_position.attr,
	&dev_attr_rate.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lis3lv02d_attribute_group = अणु
	.attrs = lis3lv02d_attributes
पूर्ण;


अटल पूर्णांक lis3lv02d_add_fs(काष्ठा lis3lv02d *lis3)
अणु
	lis3->pdev = platक्रमm_device_रेजिस्टर_simple(DRIVER_NAME, -1, शून्य, 0);
	अगर (IS_ERR(lis3->pdev))
		वापस PTR_ERR(lis3->pdev);

	platक्रमm_set_drvdata(lis3->pdev, lis3);
	वापस sysfs_create_group(&lis3->pdev->dev.kobj, &lis3lv02d_attribute_group);
पूर्ण

पूर्णांक lis3lv02d_हटाओ_fs(काष्ठा lis3lv02d *lis3)
अणु
	sysfs_हटाओ_group(&lis3->pdev->dev.kobj, &lis3lv02d_attribute_group);
	platक्रमm_device_unरेजिस्टर(lis3->pdev);
	अगर (lis3->pm_dev) अणु
		/* Barrier after the sysfs हटाओ */
		pm_runसमय_barrier(lis3->pm_dev);

		/* SYSFS may have left chip running. Turn off अगर necessary */
		अगर (!pm_runसमय_suspended(lis3->pm_dev))
			lis3lv02d_घातeroff(lis3);

		pm_runसमय_disable(lis3->pm_dev);
		pm_runसमय_set_suspended(lis3->pm_dev);
	पूर्ण
	kमुक्त(lis3->reg_cache);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_हटाओ_fs);

अटल व्योम lis3lv02d_8b_configure(काष्ठा lis3lv02d *lis3,
				काष्ठा lis3lv02d_platक्रमm_data *p)
अणु
	पूर्णांक err;
	पूर्णांक ctrl2 = p->hipass_ctrl;

	अगर (p->click_flags) अणु
		lis3->ग_लिखो(lis3, CLICK_CFG, p->click_flags);
		lis3->ग_लिखो(lis3, CLICK_TIMELIMIT, p->click_समय_limit);
		lis3->ग_लिखो(lis3, CLICK_LATENCY, p->click_latency);
		lis3->ग_लिखो(lis3, CLICK_WINDOW, p->click_winकरोw);
		lis3->ग_लिखो(lis3, CLICK_THSZ, p->click_thresh_z & 0xf);
		lis3->ग_लिखो(lis3, CLICK_THSY_X,
			(p->click_thresh_x & 0xf) |
			(p->click_thresh_y << 4));

		अगर (lis3->idev) अणु
			input_set_capability(lis3->idev, EV_KEY, BTN_X);
			input_set_capability(lis3->idev, EV_KEY, BTN_Y);
			input_set_capability(lis3->idev, EV_KEY, BTN_Z);
		पूर्ण
	पूर्ण

	अगर (p->wakeup_flags) अणु
		lis3->ग_लिखो(lis3, FF_WU_CFG_1, p->wakeup_flags);
		lis3->ग_लिखो(lis3, FF_WU_THS_1, p->wakeup_thresh & 0x7f);
		/* pdata value + 1 to keep this backward compatible*/
		lis3->ग_लिखो(lis3, FF_WU_DURATION_1, p->duration1 + 1);
		ctrl2 ^= HP_FF_WU1; /* Xor to keep compatible with old pdata*/
	पूर्ण

	अगर (p->wakeup_flags2) अणु
		lis3->ग_लिखो(lis3, FF_WU_CFG_2, p->wakeup_flags2);
		lis3->ग_लिखो(lis3, FF_WU_THS_2, p->wakeup_thresh2 & 0x7f);
		/* pdata value + 1 to keep this backward compatible*/
		lis3->ग_लिखो(lis3, FF_WU_DURATION_2, p->duration2 + 1);
		ctrl2 ^= HP_FF_WU2; /* Xor to keep compatible with old pdata*/
	पूर्ण
	/* Configure hipass filters */
	lis3->ग_लिखो(lis3, CTRL_REG2, ctrl2);

	अगर (p->irq2) अणु
		err = request_thपढ़ोed_irq(p->irq2,
					शून्य,
					lis302dl_पूर्णांकerrupt_thपढ़ो2_8b,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT |
					(p->irq_flags2 & IRQF_TRIGGER_MASK),
					DRIVER_NAME, lis3);
		अगर (err < 0)
			pr_err("No second IRQ. Limited functionality\n");
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
पूर्णांक lis3lv02d_init_dt(काष्ठा lis3lv02d *lis3)
अणु
	काष्ठा lis3lv02d_platक्रमm_data *pdata;
	काष्ठा device_node *np = lis3->of_node;
	u32 val;
	s32 sval;

	अगर (!lis3->of_node)
		वापस 0;

	pdata = kzalloc(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	अगर (of_get_property(np, "st,click-single-x", शून्य))
		pdata->click_flags |= LIS3_CLICK_SINGLE_X;
	अगर (of_get_property(np, "st,click-double-x", शून्य))
		pdata->click_flags |= LIS3_CLICK_DOUBLE_X;

	अगर (of_get_property(np, "st,click-single-y", शून्य))
		pdata->click_flags |= LIS3_CLICK_SINGLE_Y;
	अगर (of_get_property(np, "st,click-double-y", शून्य))
		pdata->click_flags |= LIS3_CLICK_DOUBLE_Y;

	अगर (of_get_property(np, "st,click-single-z", शून्य))
		pdata->click_flags |= LIS3_CLICK_SINGLE_Z;
	अगर (of_get_property(np, "st,click-double-z", शून्य))
		pdata->click_flags |= LIS3_CLICK_DOUBLE_Z;

	अगर (!of_property_पढ़ो_u32(np, "st,click-threshold-x", &val))
		pdata->click_thresh_x = val;
	अगर (!of_property_पढ़ो_u32(np, "st,click-threshold-y", &val))
		pdata->click_thresh_y = val;
	अगर (!of_property_पढ़ो_u32(np, "st,click-threshold-z", &val))
		pdata->click_thresh_z = val;

	अगर (!of_property_पढ़ो_u32(np, "st,click-time-limit", &val))
		pdata->click_समय_limit = val;
	अगर (!of_property_पढ़ो_u32(np, "st,click-latency", &val))
		pdata->click_latency = val;
	अगर (!of_property_पढ़ो_u32(np, "st,click-window", &val))
		pdata->click_winकरोw = val;

	अगर (of_get_property(np, "st,irq1-disable", शून्य))
		pdata->irq_cfg |= LIS3_IRQ1_DISABLE;
	अगर (of_get_property(np, "st,irq1-ff-wu-1", शून्य))
		pdata->irq_cfg |= LIS3_IRQ1_FF_WU_1;
	अगर (of_get_property(np, "st,irq1-ff-wu-2", शून्य))
		pdata->irq_cfg |= LIS3_IRQ1_FF_WU_2;
	अगर (of_get_property(np, "st,irq1-data-ready", शून्य))
		pdata->irq_cfg |= LIS3_IRQ1_DATA_READY;
	अगर (of_get_property(np, "st,irq1-click", शून्य))
		pdata->irq_cfg |= LIS3_IRQ1_CLICK;

	अगर (of_get_property(np, "st,irq2-disable", शून्य))
		pdata->irq_cfg |= LIS3_IRQ2_DISABLE;
	अगर (of_get_property(np, "st,irq2-ff-wu-1", शून्य))
		pdata->irq_cfg |= LIS3_IRQ2_FF_WU_1;
	अगर (of_get_property(np, "st,irq2-ff-wu-2", शून्य))
		pdata->irq_cfg |= LIS3_IRQ2_FF_WU_2;
	अगर (of_get_property(np, "st,irq2-data-ready", शून्य))
		pdata->irq_cfg |= LIS3_IRQ2_DATA_READY;
	अगर (of_get_property(np, "st,irq2-click", शून्य))
		pdata->irq_cfg |= LIS3_IRQ2_CLICK;

	अगर (of_get_property(np, "st,irq-open-drain", शून्य))
		pdata->irq_cfg |= LIS3_IRQ_OPEN_DRAIN;
	अगर (of_get_property(np, "st,irq-active-low", शून्य))
		pdata->irq_cfg |= LIS3_IRQ_ACTIVE_LOW;

	अगर (!of_property_पढ़ो_u32(np, "st,wu-duration-1", &val))
		pdata->duration1 = val;
	अगर (!of_property_पढ़ो_u32(np, "st,wu-duration-2", &val))
		pdata->duration2 = val;

	अगर (of_get_property(np, "st,wakeup-x-lo", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_X_LO;
	अगर (of_get_property(np, "st,wakeup-x-hi", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_X_HI;
	अगर (of_get_property(np, "st,wakeup-y-lo", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_Y_LO;
	अगर (of_get_property(np, "st,wakeup-y-hi", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_Y_HI;
	अगर (of_get_property(np, "st,wakeup-z-lo", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_Z_LO;
	अगर (of_get_property(np, "st,wakeup-z-hi", शून्य))
		pdata->wakeup_flags |= LIS3_WAKEUP_Z_HI;
	अगर (of_get_property(np, "st,wakeup-threshold", &val))
		pdata->wakeup_thresh = val;

	अगर (of_get_property(np, "st,wakeup2-x-lo", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_X_LO;
	अगर (of_get_property(np, "st,wakeup2-x-hi", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_X_HI;
	अगर (of_get_property(np, "st,wakeup2-y-lo", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_Y_LO;
	अगर (of_get_property(np, "st,wakeup2-y-hi", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_Y_HI;
	अगर (of_get_property(np, "st,wakeup2-z-lo", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_Z_LO;
	अगर (of_get_property(np, "st,wakeup2-z-hi", शून्य))
		pdata->wakeup_flags2 |= LIS3_WAKEUP_Z_HI;
	अगर (of_get_property(np, "st,wakeup2-threshold", &val))
		pdata->wakeup_thresh2 = val;

	अगर (!of_property_पढ़ो_u32(np, "st,highpass-cutoff-hz", &val)) अणु
		चयन (val) अणु
		हाल 1:
			pdata->hipass_ctrl = LIS3_HIPASS_CUTFF_1HZ;
			अवरोध;
		हाल 2:
			pdata->hipass_ctrl = LIS3_HIPASS_CUTFF_2HZ;
			अवरोध;
		हाल 4:
			pdata->hipass_ctrl = LIS3_HIPASS_CUTFF_4HZ;
			अवरोध;
		हाल 8:
			pdata->hipass_ctrl = LIS3_HIPASS_CUTFF_8HZ;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (of_get_property(np, "st,hipass1-disable", शून्य))
		pdata->hipass_ctrl |= LIS3_HIPASS1_DISABLE;
	अगर (of_get_property(np, "st,hipass2-disable", शून्य))
		pdata->hipass_ctrl |= LIS3_HIPASS2_DISABLE;

	अगर (of_property_पढ़ो_s32(np, "st,axis-x", &sval) == 0)
		pdata->axis_x = sval;
	अगर (of_property_पढ़ो_s32(np, "st,axis-y", &sval) == 0)
		pdata->axis_y = sval;
	अगर (of_property_पढ़ो_s32(np, "st,axis-z", &sval) == 0)
		pdata->axis_z = sval;

	अगर (of_get_property(np, "st,default-rate", शून्य))
		pdata->शेष_rate = val;

	अगर (of_property_पढ़ो_s32(np, "st,min-limit-x", &sval) == 0)
		pdata->st_min_limits[0] = sval;
	अगर (of_property_पढ़ो_s32(np, "st,min-limit-y", &sval) == 0)
		pdata->st_min_limits[1] = sval;
	अगर (of_property_पढ़ो_s32(np, "st,min-limit-z", &sval) == 0)
		pdata->st_min_limits[2] = sval;

	अगर (of_property_पढ़ो_s32(np, "st,max-limit-x", &sval) == 0)
		pdata->st_max_limits[0] = sval;
	अगर (of_property_पढ़ो_s32(np, "st,max-limit-y", &sval) == 0)
		pdata->st_max_limits[1] = sval;
	अगर (of_property_पढ़ो_s32(np, "st,max-limit-z", &sval) == 0)
		pdata->st_max_limits[2] = sval;


	lis3->pdata = pdata;

	वापस 0;
पूर्ण

#अन्यथा
पूर्णांक lis3lv02d_init_dt(काष्ठा lis3lv02d *lis3)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(lis3lv02d_init_dt);

/*
 * Initialise the accelerometer and the various subप्रणालीs.
 * Should be rather independent of the bus प्रणाली.
 */
पूर्णांक lis3lv02d_init_device(काष्ठा lis3lv02d *lis3)
अणु
	पूर्णांक err;
	irq_handler_t thपढ़ो_fn;
	पूर्णांक irq_flags = 0;

	lis3->whoami = lis3lv02d_पढ़ो_8(lis3, WHO_AM_I);

	चयन (lis3->whoami) अणु
	हाल WAI_12B:
		pr_info("12 bits sensor found\n");
		lis3->पढ़ो_data = lis3lv02d_पढ़ो_12;
		lis3->mdps_max_val = 2048;
		lis3->pwron_delay = LIS3_PWRON_DELAY_WAI_12B;
		lis3->odrs = lis3_12_rates;
		lis3->odr_mask = CTRL1_DF0 | CTRL1_DF1;
		lis3->scale = LIS3_SENSITIVITY_12B;
		lis3->regs = lis3_wai12_regs;
		lis3->regs_size = ARRAY_SIZE(lis3_wai12_regs);
		अवरोध;
	हाल WAI_8B:
		pr_info("8 bits sensor found\n");
		lis3->पढ़ो_data = lis3lv02d_पढ़ो_8;
		lis3->mdps_max_val = 128;
		lis3->pwron_delay = LIS3_PWRON_DELAY_WAI_8B;
		lis3->odrs = lis3_8_rates;
		lis3->odr_mask = CTRL1_DR;
		lis3->scale = LIS3_SENSITIVITY_8B;
		lis3->regs = lis3_wai8_regs;
		lis3->regs_size = ARRAY_SIZE(lis3_wai8_regs);
		अवरोध;
	हाल WAI_3DC:
		pr_info("8 bits 3DC sensor found\n");
		lis3->पढ़ो_data = lis3lv02d_पढ़ो_8;
		lis3->mdps_max_val = 128;
		lis3->pwron_delay = LIS3_PWRON_DELAY_WAI_8B;
		lis3->odrs = lis3_3dc_rates;
		lis3->odr_mask = CTRL1_ODR0|CTRL1_ODR1|CTRL1_ODR2|CTRL1_ODR3;
		lis3->scale = LIS3_SENSITIVITY_8B;
		अवरोध;
	हाल WAI_3DLH:
		pr_info("16 bits lis331dlh sensor found\n");
		lis3->पढ़ो_data = lis331dlh_पढ़ो_data;
		lis3->mdps_max_val = 2048; /* 12 bits क्रम 2G */
		lis3->shअगरt_adj = SHIFT_ADJ_2G;
		lis3->pwron_delay = LIS3_PWRON_DELAY_WAI_8B;
		lis3->odrs = lis3_3dlh_rates;
		lis3->odr_mask = CTRL1_DR0 | CTRL1_DR1;
		lis3->scale = LIS3DLH_SENSITIVITY_2G;
		अवरोध;
	शेष:
		pr_err("unknown sensor type 0x%X\n", lis3->whoami);
		वापस -ENODEV;
	पूर्ण

	lis3->reg_cache = kzalloc(max(माप(lis3_wai8_regs),
				     माप(lis3_wai12_regs)), GFP_KERNEL);

	अगर (lis3->reg_cache == शून्य)
		वापस -ENOMEM;

	mutex_init(&lis3->mutex);
	atomic_set(&lis3->wake_thपढ़ो, 0);

	lis3lv02d_add_fs(lis3);
	err = lis3lv02d_घातeron(lis3);
	अगर (err) अणु
		lis3lv02d_हटाओ_fs(lis3);
		वापस err;
	पूर्ण

	अगर (lis3->pm_dev) अणु
		pm_runसमय_set_active(lis3->pm_dev);
		pm_runसमय_enable(lis3->pm_dev);
	पूर्ण

	अगर (lis3lv02d_joystick_enable(lis3))
		pr_err("joystick initialization failed\n");

	/* passing in platक्रमm specअगरic data is purely optional and only
	 * used by the SPI transport layer at the moment */
	अगर (lis3->pdata) अणु
		काष्ठा lis3lv02d_platक्रमm_data *p = lis3->pdata;

		अगर (lis3->whoami == WAI_8B)
			lis3lv02d_8b_configure(lis3, p);

		irq_flags = p->irq_flags1 & IRQF_TRIGGER_MASK;

		lis3->irq_cfg = p->irq_cfg;
		अगर (p->irq_cfg)
			lis3->ग_लिखो(lis3, CTRL_REG3, p->irq_cfg);

		अगर (p->शेष_rate)
			lis3lv02d_set_odr(lis3, p->शेष_rate);
	पूर्ण

	/* bail अगर we did not get an IRQ from the bus layer */
	अगर (!lis3->irq) अणु
		pr_debug("No IRQ. Disabling /dev/freefall\n");
		जाओ out;
	पूर्ण

	/*
	 * The sensor can generate पूर्णांकerrupts क्रम मुक्त-fall and direction
	 * detection (distinguishable with FF_WU_SRC and DD_SRC) but to keep
	 * the things simple and _fast_ we activate it only क्रम मुक्त-fall, so
	 * no need to पढ़ो रेजिस्टर (very slow with ACPI). For the same reason,
	 * we क्रमbid shared पूर्णांकerrupts.
	 *
	 * IRQF_TRIGGER_RISING seems poपूर्णांकless on HP laptops because the
	 * io-apic is not configurable (and generates a warning) but I keep it
	 * in हाल of support क्रम other hardware.
	 */
	अगर (lis3->pdata && lis3->whoami == WAI_8B)
		thपढ़ो_fn = lis302dl_पूर्णांकerrupt_thपढ़ो1_8b;
	अन्यथा
		thपढ़ो_fn = शून्य;

	err = request_thपढ़ोed_irq(lis3->irq, lis302dl_पूर्णांकerrupt,
				thपढ़ो_fn,
				IRQF_TRIGGER_RISING | IRQF_ONESHOT |
				irq_flags,
				DRIVER_NAME, lis3);

	अगर (err < 0) अणु
		pr_err("Cannot get IRQ\n");
		जाओ out;
	पूर्ण

	lis3->miscdev.minor	= MISC_DYNAMIC_MINOR;
	lis3->miscdev.name	= "freefall";
	lis3->miscdev.fops	= &lis3lv02d_misc_fops;

	अगर (misc_रेजिस्टर(&lis3->miscdev))
		pr_err("misc_register failed\n");
out:
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lis3lv02d_init_device);

MODULE_DESCRIPTION("ST LIS3LV02Dx three-axis digital accelerometer driver");
MODULE_AUTHOR("Yan Burman, Eric Piel, Pavel Machek");
MODULE_LICENSE("GPL");
