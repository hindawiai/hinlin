<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADXL345/346 Three-Axis Digital Accelerometers
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2009 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/input/adxl34x.h>
#समावेश <linux/module.h>

#समावेश "adxl34x.h"

/* ADXL345/6 Register Map */
#घोषणा DEVID		0x00	/* R   Device ID */
#घोषणा THRESH_TAP	0x1D	/* R/W Tap threshold */
#घोषणा OFSX		0x1E	/* R/W X-axis offset */
#घोषणा OFSY		0x1F	/* R/W Y-axis offset */
#घोषणा OFSZ		0x20	/* R/W Z-axis offset */
#घोषणा DUR		0x21	/* R/W Tap duration */
#घोषणा LATENT		0x22	/* R/W Tap latency */
#घोषणा WINDOW		0x23	/* R/W Tap winकरोw */
#घोषणा THRESH_ACT	0x24	/* R/W Activity threshold */
#घोषणा THRESH_INACT	0x25	/* R/W Inactivity threshold */
#घोषणा TIME_INACT	0x26	/* R/W Inactivity समय */
#घोषणा ACT_INACT_CTL	0x27	/* R/W Axis enable control क्रम activity and */
				/* inactivity detection */
#घोषणा THRESH_FF	0x28	/* R/W Free-fall threshold */
#घोषणा TIME_FF		0x29	/* R/W Free-fall समय */
#घोषणा TAP_AXES	0x2A	/* R/W Axis control क्रम tap/द्विगुन tap */
#घोषणा ACT_TAP_STATUS	0x2B	/* R   Source of tap/द्विगुन tap */
#घोषणा BW_RATE		0x2C	/* R/W Data rate and घातer mode control */
#घोषणा POWER_CTL	0x2D	/* R/W Power saving features control */
#घोषणा INT_ENABLE	0x2E	/* R/W Interrupt enable control */
#घोषणा INT_MAP		0x2F	/* R/W Interrupt mapping control */
#घोषणा INT_SOURCE	0x30	/* R   Source of पूर्णांकerrupts */
#घोषणा DATA_FORMAT	0x31	/* R/W Data क्रमmat control */
#घोषणा DATAX0		0x32	/* R   X-Axis Data 0 */
#घोषणा DATAX1		0x33	/* R   X-Axis Data 1 */
#घोषणा DATAY0		0x34	/* R   Y-Axis Data 0 */
#घोषणा DATAY1		0x35	/* R   Y-Axis Data 1 */
#घोषणा DATAZ0		0x36	/* R   Z-Axis Data 0 */
#घोषणा DATAZ1		0x37	/* R   Z-Axis Data 1 */
#घोषणा FIFO_CTL	0x38	/* R/W FIFO control */
#घोषणा FIFO_STATUS	0x39	/* R   FIFO status */
#घोषणा TAP_SIGN	0x3A	/* R   Sign and source क्रम tap/द्विगुन tap */
/* Orientation ADXL346 only */
#घोषणा ORIENT_CONF	0x3B	/* R/W Orientation configuration */
#घोषणा ORIENT		0x3C	/* R   Orientation status */

/* DEVIDs */
#घोषणा ID_ADXL345	0xE5
#घोषणा ID_ADXL346	0xE6

/* INT_ENABLE/INT_MAP/INT_SOURCE Bits */
#घोषणा DATA_READY	(1 << 7)
#घोषणा SINGLE_TAP	(1 << 6)
#घोषणा DOUBLE_TAP	(1 << 5)
#घोषणा ACTIVITY	(1 << 4)
#घोषणा INACTIVITY	(1 << 3)
#घोषणा FREE_FALL	(1 << 2)
#घोषणा WATERMARK	(1 << 1)
#घोषणा OVERRUN		(1 << 0)

/* ACT_INACT_CONTROL Bits */
#घोषणा ACT_ACDC	(1 << 7)
#घोषणा ACT_X_EN	(1 << 6)
#घोषणा ACT_Y_EN	(1 << 5)
#घोषणा ACT_Z_EN	(1 << 4)
#घोषणा INACT_ACDC	(1 << 3)
#घोषणा INACT_X_EN	(1 << 2)
#घोषणा INACT_Y_EN	(1 << 1)
#घोषणा INACT_Z_EN	(1 << 0)

/* TAP_AXES Bits */
#घोषणा SUPPRESS	(1 << 3)
#घोषणा TAP_X_EN	(1 << 2)
#घोषणा TAP_Y_EN	(1 << 1)
#घोषणा TAP_Z_EN	(1 << 0)

/* ACT_TAP_STATUS Bits */
#घोषणा ACT_X_SRC	(1 << 6)
#घोषणा ACT_Y_SRC	(1 << 5)
#घोषणा ACT_Z_SRC	(1 << 4)
#घोषणा ASLEEP		(1 << 3)
#घोषणा TAP_X_SRC	(1 << 2)
#घोषणा TAP_Y_SRC	(1 << 1)
#घोषणा TAP_Z_SRC	(1 << 0)

/* BW_RATE Bits */
#घोषणा LOW_POWER	(1 << 4)
#घोषणा RATE(x)		((x) & 0xF)

/* POWER_CTL Bits */
#घोषणा PCTL_LINK	(1 << 5)
#घोषणा PCTL_AUTO_SLEEP (1 << 4)
#घोषणा PCTL_MEASURE	(1 << 3)
#घोषणा PCTL_SLEEP	(1 << 2)
#घोषणा PCTL_WAKEUP(x)	((x) & 0x3)

/* DATA_FORMAT Bits */
#घोषणा SELF_TEST	(1 << 7)
#घोषणा SPI		(1 << 6)
#घोषणा INT_INVERT	(1 << 5)
#घोषणा FULL_RES	(1 << 3)
#घोषणा JUSTIFY		(1 << 2)
#घोषणा RANGE(x)	((x) & 0x3)
#घोषणा RANGE_PM_2g	0
#घोषणा RANGE_PM_4g	1
#घोषणा RANGE_PM_8g	2
#घोषणा RANGE_PM_16g	3

/*
 * Maximum value our axis may get in full res mode क्रम the input device
 * (चिन्हित 13 bits)
 */
#घोषणा ADXL_FULLRES_MAX_VAL 4096

/*
 * Maximum value our axis may get in fixed res mode क्रम the input device
 * (चिन्हित 10 bits)
 */
#घोषणा ADXL_FIXEDRES_MAX_VAL 512

/* FIFO_CTL Bits */
#घोषणा FIFO_MODE(x)	(((x) & 0x3) << 6)
#घोषणा FIFO_BYPASS	0
#घोषणा FIFO_FIFO	1
#घोषणा FIFO_STREAM	2
#घोषणा FIFO_TRIGGER	3
#घोषणा TRIGGER		(1 << 5)
#घोषणा SAMPLES(x)	((x) & 0x1F)

/* FIFO_STATUS Bits */
#घोषणा FIFO_TRIG	(1 << 7)
#घोषणा ENTRIES(x)	((x) & 0x3F)

/* TAP_SIGN Bits ADXL346 only */
#घोषणा XSIGN		(1 << 6)
#घोषणा YSIGN		(1 << 5)
#घोषणा ZSIGN		(1 << 4)
#घोषणा XTAP		(1 << 3)
#घोषणा YTAP		(1 << 2)
#घोषणा ZTAP		(1 << 1)

/* ORIENT_CONF ADXL346 only */
#घोषणा ORIENT_DEADZONE(x)	(((x) & 0x7) << 4)
#घोषणा ORIENT_DIVISOR(x)	((x) & 0x7)

/* ORIENT ADXL346 only */
#घोषणा ADXL346_2D_VALID		(1 << 6)
#घोषणा ADXL346_2D_ORIENT(x)		(((x) & 0x30) >> 4)
#घोषणा ADXL346_3D_VALID		(1 << 3)
#घोषणा ADXL346_3D_ORIENT(x)		((x) & 0x7)
#घोषणा ADXL346_2D_PORTRAIT_POS		0	/* +X */
#घोषणा ADXL346_2D_PORTRAIT_NEG		1	/* -X */
#घोषणा ADXL346_2D_LANDSCAPE_POS	2	/* +Y */
#घोषणा ADXL346_2D_LANDSCAPE_NEG	3	/* -Y */

#घोषणा ADXL346_3D_FRONT		3	/* +X */
#घोषणा ADXL346_3D_BACK			4	/* -X */
#घोषणा ADXL346_3D_RIGHT		2	/* +Y */
#घोषणा ADXL346_3D_LEFT			5	/* -Y */
#घोषणा ADXL346_3D_TOP			1	/* +Z */
#घोषणा ADXL346_3D_BOTTOM		6	/* -Z */

#अघोषित ADXL_DEBUG

#घोषणा ADXL_X_AXIS			0
#घोषणा ADXL_Y_AXIS			1
#घोषणा ADXL_Z_AXIS			2

#घोषणा AC_READ(ac, reg)	((ac)->bops->पढ़ो((ac)->dev, reg))
#घोषणा AC_WRITE(ac, reg, val)	((ac)->bops->ग_लिखो((ac)->dev, reg, val))

काष्ठा axis_triple अणु
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक z;
पूर्ण;

काष्ठा adxl34x अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input;
	काष्ठा mutex mutex;	/* reentrant protection क्रम काष्ठा */
	काष्ठा adxl34x_platक्रमm_data pdata;
	काष्ठा axis_triple swcal;
	काष्ठा axis_triple hwcal;
	काष्ठा axis_triple saved;
	अक्षर phys[32];
	अचिन्हित orient2d_saved;
	अचिन्हित orient3d_saved;
	bool disabled;	/* P: mutex */
	bool खोलोed;	/* P: mutex */
	bool suspended;	/* P: mutex */
	bool fअगरo_delay;
	पूर्णांक irq;
	अचिन्हित model;
	अचिन्हित पूर्णांक_mask;

	स्थिर काष्ठा adxl34x_bus_ops *bops;
पूर्ण;

अटल स्थिर काष्ठा adxl34x_platक्रमm_data adxl34x_शेष_init = अणु
	.tap_threshold = 35,
	.tap_duration = 3,
	.tap_latency = 20,
	.tap_winकरोw = 20,
	.tap_axis_control = ADXL_TAP_X_EN | ADXL_TAP_Y_EN | ADXL_TAP_Z_EN,
	.act_axis_control = 0xFF,
	.activity_threshold = 6,
	.inactivity_threshold = 4,
	.inactivity_समय = 3,
	.मुक्त_fall_threshold = 8,
	.मुक्त_fall_समय = 0x20,
	.data_rate = 8,
	.data_range = ADXL_FULL_RES,

	.ev_type = EV_ABS,
	.ev_code_x = ABS_X,	/* EV_REL */
	.ev_code_y = ABS_Y,	/* EV_REL */
	.ev_code_z = ABS_Z,	/* EV_REL */

	.ev_code_tap = अणुBTN_TOUCH, BTN_TOUCH, BTN_TOUCHपूर्ण, /* EV_KEY अणुx,y,zपूर्ण */
	.घातer_mode = ADXL_AUTO_SLEEP | ADXL_LINK,
	.fअगरo_mode = ADXL_FIFO_STREAM,
	.watermark = 0,
पूर्ण;

अटल व्योम adxl34x_get_triple(काष्ठा adxl34x *ac, काष्ठा axis_triple *axis)
अणु
	लघु buf[3];

	ac->bops->पढ़ो_block(ac->dev, DATAX0, DATAZ1 - DATAX0 + 1, buf);

	mutex_lock(&ac->mutex);
	ac->saved.x = (s16) le16_to_cpu(buf[0]);
	axis->x = ac->saved.x;

	ac->saved.y = (s16) le16_to_cpu(buf[1]);
	axis->y = ac->saved.y;

	ac->saved.z = (s16) le16_to_cpu(buf[2]);
	axis->z = ac->saved.z;
	mutex_unlock(&ac->mutex);
पूर्ण

अटल व्योम adxl34x_service_ev_fअगरo(काष्ठा adxl34x *ac)
अणु
	काष्ठा adxl34x_platक्रमm_data *pdata = &ac->pdata;
	काष्ठा axis_triple axis;

	adxl34x_get_triple(ac, &axis);

	input_event(ac->input, pdata->ev_type, pdata->ev_code_x,
		    axis.x - ac->swcal.x);
	input_event(ac->input, pdata->ev_type, pdata->ev_code_y,
		    axis.y - ac->swcal.y);
	input_event(ac->input, pdata->ev_type, pdata->ev_code_z,
		    axis.z - ac->swcal.z);
पूर्ण

अटल व्योम adxl34x_report_key_single(काष्ठा input_dev *input, पूर्णांक key)
अणु
	input_report_key(input, key, true);
	input_sync(input);
	input_report_key(input, key, false);
पूर्ण

अटल व्योम adxl34x_send_key_events(काष्ठा adxl34x *ac,
		काष्ठा adxl34x_platक्रमm_data *pdata, पूर्णांक status, पूर्णांक press)
अणु
	पूर्णांक i;

	क्रम (i = ADXL_X_AXIS; i <= ADXL_Z_AXIS; i++) अणु
		अगर (status & (1 << (ADXL_Z_AXIS - i)))
			input_report_key(ac->input,
					 pdata->ev_code_tap[i], press);
	पूर्ण
पूर्ण

अटल व्योम adxl34x_करो_tap(काष्ठा adxl34x *ac,
		काष्ठा adxl34x_platक्रमm_data *pdata, पूर्णांक status)
अणु
	adxl34x_send_key_events(ac, pdata, status, true);
	input_sync(ac->input);
	adxl34x_send_key_events(ac, pdata, status, false);
पूर्ण

अटल irqवापस_t adxl34x_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा adxl34x *ac = handle;
	काष्ठा adxl34x_platक्रमm_data *pdata = &ac->pdata;
	पूर्णांक पूर्णांक_stat, tap_stat, samples, orient, orient_code;

	/*
	 * ACT_TAP_STATUS should be पढ़ो beक्रमe clearing the पूर्णांकerrupt
	 * Aव्योम पढ़ोing ACT_TAP_STATUS in हाल TAP detection is disabled
	 */

	अगर (pdata->tap_axis_control & (TAP_X_EN | TAP_Y_EN | TAP_Z_EN))
		tap_stat = AC_READ(ac, ACT_TAP_STATUS);
	अन्यथा
		tap_stat = 0;

	पूर्णांक_stat = AC_READ(ac, INT_SOURCE);

	अगर (पूर्णांक_stat & FREE_FALL)
		adxl34x_report_key_single(ac->input, pdata->ev_code_ff);

	अगर (पूर्णांक_stat & OVERRUN)
		dev_dbg(ac->dev, "OVERRUN\n");

	अगर (पूर्णांक_stat & (SINGLE_TAP | DOUBLE_TAP)) अणु
		adxl34x_करो_tap(ac, pdata, tap_stat);

		अगर (पूर्णांक_stat & DOUBLE_TAP)
			adxl34x_करो_tap(ac, pdata, tap_stat);
	पूर्ण

	अगर (pdata->ev_code_act_inactivity) अणु
		अगर (पूर्णांक_stat & ACTIVITY)
			input_report_key(ac->input,
					 pdata->ev_code_act_inactivity, 1);
		अगर (पूर्णांक_stat & INACTIVITY)
			input_report_key(ac->input,
					 pdata->ev_code_act_inactivity, 0);
	पूर्ण

	/*
	 * ORIENTATION SENSING ADXL346 only
	 */
	अगर (pdata->orientation_enable) अणु
		orient = AC_READ(ac, ORIENT);
		अगर ((pdata->orientation_enable & ADXL_EN_ORIENTATION_2D) &&
		    (orient & ADXL346_2D_VALID)) अणु

			orient_code = ADXL346_2D_ORIENT(orient);
			/* Report orientation only when it changes */
			अगर (ac->orient2d_saved != orient_code) अणु
				ac->orient2d_saved = orient_code;
				adxl34x_report_key_single(ac->input,
					pdata->ev_codes_orient_2d[orient_code]);
			पूर्ण
		पूर्ण

		अगर ((pdata->orientation_enable & ADXL_EN_ORIENTATION_3D) &&
		    (orient & ADXL346_3D_VALID)) अणु

			orient_code = ADXL346_3D_ORIENT(orient) - 1;
			/* Report orientation only when it changes */
			अगर (ac->orient3d_saved != orient_code) अणु
				ac->orient3d_saved = orient_code;
				adxl34x_report_key_single(ac->input,
					pdata->ev_codes_orient_3d[orient_code]);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_stat & (DATA_READY | WATERMARK)) अणु

		अगर (pdata->fअगरo_mode)
			samples = ENTRIES(AC_READ(ac, FIFO_STATUS)) + 1;
		अन्यथा
			samples = 1;

		क्रम (; samples > 0; samples--) अणु
			adxl34x_service_ev_fअगरo(ac);
			/*
			 * To ensure that the FIFO has
			 * completely popped, there must be at least 5 us between
			 * the end of पढ़ोing the data रेजिस्टरs, signअगरied by the
			 * transition to रेजिस्टर 0x38 from 0x37 or the CS pin
			 * going high, and the start of new पढ़ोs of the FIFO or
			 * पढ़ोing the FIFO_STATUS रेजिस्टर. For SPI operation at
			 * 1.5 MHz or lower, the रेजिस्टर addressing portion of the
			 * transmission is sufficient delay to ensure the FIFO has
			 * completely popped. It is necessary क्रम SPI operation
			 * greater than 1.5 MHz to de-निश्चित the CS pin to ensure a
			 * total of 5 us, which is at most 3.4 us at 5 MHz
			 * operation.
			 */
			अगर (ac->fअगरo_delay && (samples > 1))
				udelay(3);
		पूर्ण
	पूर्ण

	input_sync(ac->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __adxl34x_disable(काष्ठा adxl34x *ac)
अणु
	/*
	 * A '0' places the ADXL34x पूर्णांकo standby mode
	 * with minimum घातer consumption.
	 */
	AC_WRITE(ac, POWER_CTL, 0);
पूर्ण

अटल व्योम __adxl34x_enable(काष्ठा adxl34x *ac)
अणु
	AC_WRITE(ac, POWER_CTL, ac->pdata.घातer_mode | PCTL_MEASURE);
पूर्ण

व्योम adxl34x_suspend(काष्ठा adxl34x *ac)
अणु
	mutex_lock(&ac->mutex);

	अगर (!ac->suspended && !ac->disabled && ac->खोलोed)
		__adxl34x_disable(ac);

	ac->suspended = true;

	mutex_unlock(&ac->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(adxl34x_suspend);

व्योम adxl34x_resume(काष्ठा adxl34x *ac)
अणु
	mutex_lock(&ac->mutex);

	अगर (ac->suspended && !ac->disabled && ac->खोलोed)
		__adxl34x_enable(ac);

	ac->suspended = false;

	mutex_unlock(&ac->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(adxl34x_resume);

अटल sमाप_प्रकार adxl34x_disable_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ac->disabled);
पूर्ण

अटल sमाप_प्रकार adxl34x_disable_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ac->mutex);

	अगर (!ac->suspended && ac->खोलोed) अणु
		अगर (val) अणु
			अगर (!ac->disabled)
				__adxl34x_disable(ac);
		पूर्ण अन्यथा अणु
			अगर (ac->disabled)
				__adxl34x_enable(ac);
		पूर्ण
	पूर्ण

	ac->disabled = !!val;

	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(disable, 0664, adxl34x_disable_show, adxl34x_disable_store);

अटल sमाप_प्रकार adxl34x_calibrate_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	sमाप_प्रकार count;

	mutex_lock(&ac->mutex);
	count = प्र_लिखो(buf, "%d,%d,%d\n",
			ac->hwcal.x * 4 + ac->swcal.x,
			ac->hwcal.y * 4 + ac->swcal.y,
			ac->hwcal.z * 4 + ac->swcal.z);
	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adxl34x_calibrate_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);

	/*
	 * Hardware offset calibration has a resolution of 15.6 mg/LSB.
	 * We use HW calibration and handle the reमुख्यing bits in SW. (4mg/LSB)
	 */

	mutex_lock(&ac->mutex);
	ac->hwcal.x -= (ac->saved.x / 4);
	ac->swcal.x = ac->saved.x % 4;

	ac->hwcal.y -= (ac->saved.y / 4);
	ac->swcal.y = ac->saved.y % 4;

	ac->hwcal.z -= (ac->saved.z / 4);
	ac->swcal.z = ac->saved.z % 4;

	AC_WRITE(ac, OFSX, (s8) ac->hwcal.x);
	AC_WRITE(ac, OFSY, (s8) ac->hwcal.y);
	AC_WRITE(ac, OFSZ, (s8) ac->hwcal.z);
	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(calibrate, 0664,
		   adxl34x_calibrate_show, adxl34x_calibrate_store);

अटल sमाप_प्रकार adxl34x_rate_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", RATE(ac->pdata.data_rate));
पूर्ण

अटल sमाप_प्रकार adxl34x_rate_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	अचिन्हित अक्षर val;
	पूर्णांक error;

	error = kstrtou8(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ac->mutex);

	ac->pdata.data_rate = RATE(val);
	AC_WRITE(ac, BW_RATE,
		 ac->pdata.data_rate |
			(ac->pdata.low_घातer_mode ? LOW_POWER : 0));

	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(rate, 0664, adxl34x_rate_show, adxl34x_rate_store);

अटल sमाप_प्रकार adxl34x_स्वतःsleep_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n",
		ac->pdata.घातer_mode & (PCTL_AUTO_SLEEP | PCTL_LINK) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार adxl34x_स्वतःsleep_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ac->mutex);

	अगर (val)
		ac->pdata.घातer_mode |= (PCTL_AUTO_SLEEP | PCTL_LINK);
	अन्यथा
		ac->pdata.घातer_mode &= ~(PCTL_AUTO_SLEEP | PCTL_LINK);

	अगर (!ac->disabled && !ac->suspended && ac->खोलोed)
		AC_WRITE(ac, POWER_CTL, ac->pdata.घातer_mode | PCTL_MEASURE);

	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(स्वतःsleep, 0664,
		   adxl34x_स्वतःsleep_show, adxl34x_स्वतःsleep_store);

अटल sमाप_प्रकार adxl34x_position_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	sमाप_प्रकार count;

	mutex_lock(&ac->mutex);
	count = प्र_लिखो(buf, "(%d, %d, %d)\n",
			ac->saved.x, ac->saved.y, ac->saved.z);
	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(position, S_IRUGO, adxl34x_position_show, शून्य);

#अगर_घोषित ADXL_DEBUG
अटल sमाप_प्रकार adxl34x_ग_लिखो_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adxl34x *ac = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	/*
	 * This allows basic ADXL रेजिस्टर ग_लिखो access क्रम debug purposes.
	 */
	error = kstrtouपूर्णांक(buf, 16, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ac->mutex);
	AC_WRITE(ac, val >> 8, val & 0xFF);
	mutex_unlock(&ac->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(ग_लिखो, 0664, शून्य, adxl34x_ग_लिखो_store);
#पूर्ण_अगर

अटल काष्ठा attribute *adxl34x_attributes[] = अणु
	&dev_attr_disable.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_rate.attr,
	&dev_attr_स्वतःsleep.attr,
	&dev_attr_position.attr,
#अगर_घोषित ADXL_DEBUG
	&dev_attr_ग_लिखो.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adxl34x_attr_group = अणु
	.attrs = adxl34x_attributes,
पूर्ण;

अटल पूर्णांक adxl34x_input_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा adxl34x *ac = input_get_drvdata(input);

	mutex_lock(&ac->mutex);

	अगर (!ac->suspended && !ac->disabled)
		__adxl34x_enable(ac);

	ac->खोलोed = true;

	mutex_unlock(&ac->mutex);

	वापस 0;
पूर्ण

अटल व्योम adxl34x_input_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा adxl34x *ac = input_get_drvdata(input);

	mutex_lock(&ac->mutex);

	अगर (!ac->suspended && !ac->disabled)
		__adxl34x_disable(ac);

	ac->खोलोed = false;

	mutex_unlock(&ac->mutex);
पूर्ण

काष्ठा adxl34x *adxl34x_probe(काष्ठा device *dev, पूर्णांक irq,
			      bool fअगरo_delay_शेष,
			      स्थिर काष्ठा adxl34x_bus_ops *bops)
अणु
	काष्ठा adxl34x *ac;
	काष्ठा input_dev *input_dev;
	स्थिर काष्ठा adxl34x_platक्रमm_data *pdata;
	पूर्णांक err, range, i;
	पूर्णांक revid;

	अगर (!irq) अणु
		dev_err(dev, "no IRQ?\n");
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	ac = kzalloc(माप(*ac), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!ac || !input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	ac->fअगरo_delay = fअगरo_delay_शेष;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		dev_dbg(dev,
			"No platform data: Using default initialization\n");
		pdata = &adxl34x_शेष_init;
	पूर्ण

	ac->pdata = *pdata;
	pdata = &ac->pdata;

	ac->input = input_dev;
	ac->dev = dev;
	ac->irq = irq;
	ac->bops = bops;

	mutex_init(&ac->mutex);

	input_dev->name = "ADXL34x accelerometer";
	revid = AC_READ(ac, DEVID);

	चयन (revid) अणु
	हाल ID_ADXL345:
		ac->model = 345;
		अवरोध;
	हाल ID_ADXL346:
		ac->model = 346;
		अवरोध;
	शेष:
		dev_err(dev, "Failed to probe %s\n", input_dev->name);
		err = -ENODEV;
		जाओ err_मुक्त_mem;
	पूर्ण

	snम_लिखो(ac->phys, माप(ac->phys), "%s/input0", dev_name(dev));

	input_dev->phys = ac->phys;
	input_dev->dev.parent = dev;
	input_dev->id.product = ac->model;
	input_dev->id.bustype = bops->bustype;
	input_dev->खोलो = adxl34x_input_खोलो;
	input_dev->बंद = adxl34x_input_बंद;

	input_set_drvdata(input_dev, ac);

	__set_bit(ac->pdata.ev_type, input_dev->evbit);

	अगर (ac->pdata.ev_type == EV_REL) अणु
		__set_bit(REL_X, input_dev->relbit);
		__set_bit(REL_Y, input_dev->relbit);
		__set_bit(REL_Z, input_dev->relbit);
	पूर्ण अन्यथा अणु
		/* EV_ABS */
		__set_bit(ABS_X, input_dev->असलbit);
		__set_bit(ABS_Y, input_dev->असलbit);
		__set_bit(ABS_Z, input_dev->असलbit);

		अगर (pdata->data_range & FULL_RES)
			range = ADXL_FULLRES_MAX_VAL;	/* Signed 13-bit */
		अन्यथा
			range = ADXL_FIXEDRES_MAX_VAL;	/* Signed 10-bit */

		input_set_असल_params(input_dev, ABS_X, -range, range, 3, 3);
		input_set_असल_params(input_dev, ABS_Y, -range, range, 3, 3);
		input_set_असल_params(input_dev, ABS_Z, -range, range, 3, 3);
	पूर्ण

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(pdata->ev_code_tap[ADXL_X_AXIS], input_dev->keybit);
	__set_bit(pdata->ev_code_tap[ADXL_Y_AXIS], input_dev->keybit);
	__set_bit(pdata->ev_code_tap[ADXL_Z_AXIS], input_dev->keybit);

	अगर (pdata->ev_code_ff) अणु
		ac->पूर्णांक_mask = FREE_FALL;
		__set_bit(pdata->ev_code_ff, input_dev->keybit);
	पूर्ण

	अगर (pdata->ev_code_act_inactivity)
		__set_bit(pdata->ev_code_act_inactivity, input_dev->keybit);

	ac->पूर्णांक_mask |= ACTIVITY | INACTIVITY;

	अगर (pdata->watermark) अणु
		ac->पूर्णांक_mask |= WATERMARK;
		अगर (FIFO_MODE(pdata->fअगरo_mode) == FIFO_BYPASS)
			ac->pdata.fअगरo_mode |= FIFO_STREAM;
	पूर्ण अन्यथा अणु
		ac->पूर्णांक_mask |= DATA_READY;
	पूर्ण

	अगर (pdata->tap_axis_control & (TAP_X_EN | TAP_Y_EN | TAP_Z_EN))
		ac->पूर्णांक_mask |= SINGLE_TAP | DOUBLE_TAP;

	अगर (FIFO_MODE(pdata->fअगरo_mode) == FIFO_BYPASS)
		ac->fअगरo_delay = false;

	AC_WRITE(ac, POWER_CTL, 0);

	err = request_thपढ़ोed_irq(ac->irq, शून्य, adxl34x_irq,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   dev_name(dev), ac);
	अगर (err) अणु
		dev_err(dev, "irq %d busy?\n", ac->irq);
		जाओ err_मुक्त_mem;
	पूर्ण

	err = sysfs_create_group(&dev->kobj, &adxl34x_attr_group);
	अगर (err)
		जाओ err_मुक्त_irq;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ err_हटाओ_attr;

	AC_WRITE(ac, OFSX, pdata->x_axis_offset);
	ac->hwcal.x = pdata->x_axis_offset;
	AC_WRITE(ac, OFSY, pdata->y_axis_offset);
	ac->hwcal.y = pdata->y_axis_offset;
	AC_WRITE(ac, OFSZ, pdata->z_axis_offset);
	ac->hwcal.z = pdata->z_axis_offset;
	AC_WRITE(ac, THRESH_TAP, pdata->tap_threshold);
	AC_WRITE(ac, DUR, pdata->tap_duration);
	AC_WRITE(ac, LATENT, pdata->tap_latency);
	AC_WRITE(ac, WINDOW, pdata->tap_winकरोw);
	AC_WRITE(ac, THRESH_ACT, pdata->activity_threshold);
	AC_WRITE(ac, THRESH_INACT, pdata->inactivity_threshold);
	AC_WRITE(ac, TIME_INACT, pdata->inactivity_समय);
	AC_WRITE(ac, THRESH_FF, pdata->मुक्त_fall_threshold);
	AC_WRITE(ac, TIME_FF, pdata->मुक्त_fall_समय);
	AC_WRITE(ac, TAP_AXES, pdata->tap_axis_control);
	AC_WRITE(ac, ACT_INACT_CTL, pdata->act_axis_control);
	AC_WRITE(ac, BW_RATE, RATE(ac->pdata.data_rate) |
		 (pdata->low_घातer_mode ? LOW_POWER : 0));
	AC_WRITE(ac, DATA_FORMAT, pdata->data_range);
	AC_WRITE(ac, FIFO_CTL, FIFO_MODE(pdata->fअगरo_mode) |
			SAMPLES(pdata->watermark));

	अगर (pdata->use_पूर्णांक2) अणु
		/* Map all INTs to INT2 */
		AC_WRITE(ac, INT_MAP, ac->पूर्णांक_mask | OVERRUN);
	पूर्ण अन्यथा अणु
		/* Map all INTs to INT1 */
		AC_WRITE(ac, INT_MAP, 0);
	पूर्ण

	अगर (ac->model == 346 && ac->pdata.orientation_enable) अणु
		AC_WRITE(ac, ORIENT_CONF,
			ORIENT_DEADZONE(ac->pdata.deadzone_angle) |
			ORIENT_DIVISOR(ac->pdata.भागisor_length));

		ac->orient2d_saved = 1234;
		ac->orient3d_saved = 1234;

		अगर (pdata->orientation_enable & ADXL_EN_ORIENTATION_3D)
			क्रम (i = 0; i < ARRAY_SIZE(pdata->ev_codes_orient_3d); i++)
				__set_bit(pdata->ev_codes_orient_3d[i],
					  input_dev->keybit);

		अगर (pdata->orientation_enable & ADXL_EN_ORIENTATION_2D)
			क्रम (i = 0; i < ARRAY_SIZE(pdata->ev_codes_orient_2d); i++)
				__set_bit(pdata->ev_codes_orient_2d[i],
					  input_dev->keybit);
	पूर्ण अन्यथा अणु
		ac->pdata.orientation_enable = 0;
	पूर्ण

	AC_WRITE(ac, INT_ENABLE, ac->पूर्णांक_mask | OVERRUN);

	ac->pdata.घातer_mode &= (PCTL_AUTO_SLEEP | PCTL_LINK);

	वापस ac;

 err_हटाओ_attr:
	sysfs_हटाओ_group(&dev->kobj, &adxl34x_attr_group);
 err_मुक्त_irq:
	मुक्त_irq(ac->irq, ac);
 err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(ac);
 err_out:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(adxl34x_probe);

पूर्णांक adxl34x_हटाओ(काष्ठा adxl34x *ac)
अणु
	sysfs_हटाओ_group(&ac->dev->kobj, &adxl34x_attr_group);
	मुक्त_irq(ac->irq, ac);
	input_unरेजिस्टर_device(ac->input);
	dev_dbg(ac->dev, "unregistered accelerometer\n");
	kमुक्त(ac);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adxl34x_हटाओ);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("ADXL345/346 Three-Axis Digital Accelerometer Driver");
MODULE_LICENSE("GPL");
