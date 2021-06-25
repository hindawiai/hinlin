<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core Source क्रम:
 * Cypress TrueTouch(TM) Standard Product (TTSP) touchscreen drivers.
 * For use with Cypress Txx3xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 *
 * Contact Cypress Semiconductor at www.cypress.com <kev@cypress.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/property.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "cyttsp_core.h"

/* Bootloader number of command keys */
#घोषणा CY_NUM_BL_KEYS		8

/* helpers */
#घोषणा GET_NUM_TOUCHES(x)		((x) & 0x0F)
#घोषणा IS_LARGE_AREA(x)		(((x) & 0x10) >> 4)
#घोषणा IS_BAD_PKT(x)			((x) & 0x20)
#घोषणा IS_VALID_APP(x)			((x) & 0x01)
#घोषणा IS_OPERATIONAL_ERR(x)		((x) & 0x3F)
#घोषणा GET_HSTMODE(reg)		(((reg) & 0x70) >> 4)
#घोषणा GET_BOOTLOADERMODE(reg)		(((reg) & 0x10) >> 4)

#घोषणा CY_REG_BASE			0x00
#घोषणा CY_REG_ACT_DIST			0x1E
#घोषणा CY_REG_ACT_INTRVL		0x1D
#घोषणा CY_REG_TCH_TMOUT		(CY_REG_ACT_INTRVL + 1)
#घोषणा CY_REG_LP_INTRVL		(CY_REG_TCH_TMOUT + 1)
#घोषणा CY_MAXZ				255
#घोषणा CY_DELAY_DFLT			20 /* ms */
#घोषणा CY_DELAY_MAX			500
#घोषणा CY_ACT_DIST_DFLT		0xF8
#घोषणा CY_ACT_DIST_MASK		0x0F
#घोषणा CY_HNDSHK_BIT			0x80
/* device mode bits */
#घोषणा CY_OPERATE_MODE			0x00
#घोषणा CY_SYSINFO_MODE			0x10
/* घातer mode select bits */
#घोषणा CY_SOFT_RESET_MODE		0x01 /* वापस to Bootloader mode */
#घोषणा CY_DEEP_SLEEP_MODE		0x02
#घोषणा CY_LOW_POWER_MODE		0x04

/* Slots management */
#घोषणा CY_MAX_FINGER			4
#घोषणा CY_MAX_ID			16

अटल स्थिर u8 bl_command[] = अणु
	0x00,			/* file offset */
	0xFF,			/* command */
	0xA5,			/* निकास bootloader command */
	0, 1, 2, 3, 4, 5, 6, 7	/* शेष keys */
पूर्ण;

अटल पूर्णांक ttsp_पढ़ो_block_data(काष्ठा cyttsp *ts, u8 command,
				u8 length, व्योम *buf)
अणु
	पूर्णांक error;
	पूर्णांक tries;

	क्रम (tries = 0; tries < CY_NUM_RETRY; tries++) अणु
		error = ts->bus_ops->पढ़ो(ts->dev, ts->xfer_buf, command,
				length, buf);
		अगर (!error)
			वापस 0;

		msleep(CY_DELAY_DFLT);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक ttsp_ग_लिखो_block_data(काष्ठा cyttsp *ts, u8 command,
				 u8 length, व्योम *buf)
अणु
	पूर्णांक error;
	पूर्णांक tries;

	क्रम (tries = 0; tries < CY_NUM_RETRY; tries++) अणु
		error = ts->bus_ops->ग_लिखो(ts->dev, ts->xfer_buf, command,
				length, buf);
		अगर (!error)
			वापस 0;

		msleep(CY_DELAY_DFLT);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक ttsp_send_command(काष्ठा cyttsp *ts, u8 cmd)
अणु
	वापस ttsp_ग_लिखो_block_data(ts, CY_REG_BASE, माप(cmd), &cmd);
पूर्ण

अटल पूर्णांक cyttsp_handshake(काष्ठा cyttsp *ts)
अणु
	अगर (ts->use_hndshk)
		वापस ttsp_send_command(ts,
				ts->xy_data.hst_mode ^ CY_HNDSHK_BIT);

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_load_bl_regs(काष्ठा cyttsp *ts)
अणु
	स_रखो(&ts->bl_data, 0, माप(ts->bl_data));
	ts->bl_data.bl_status = 0x10;

	वापस ttsp_पढ़ो_block_data(ts, CY_REG_BASE,
				    माप(ts->bl_data), &ts->bl_data);
पूर्ण

अटल पूर्णांक cyttsp_निकास_bl_mode(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;
	u8 bl_cmd[माप(bl_command)];

	स_नकल(bl_cmd, bl_command, माप(bl_command));
	अगर (ts->bl_keys)
		स_नकल(&bl_cmd[माप(bl_command) - CY_NUM_BL_KEYS],
			ts->bl_keys, CY_NUM_BL_KEYS);

	error = ttsp_ग_लिखो_block_data(ts, CY_REG_BASE,
				      माप(bl_cmd), bl_cmd);
	अगर (error)
		वापस error;

	/* रुको क्रम TTSP Device to complete the operation */
	msleep(CY_DELAY_DFLT);

	error = cyttsp_load_bl_regs(ts);
	अगर (error)
		वापस error;

	अगर (GET_BOOTLOADERMODE(ts->bl_data.bl_status))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_set_operational_mode(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;

	error = ttsp_send_command(ts, CY_OPERATE_MODE);
	अगर (error)
		वापस error;

	/* रुको क्रम TTSP Device to complete चयन to Operational mode */
	error = ttsp_पढ़ो_block_data(ts, CY_REG_BASE,
				     माप(ts->xy_data), &ts->xy_data);
	अगर (error)
		वापस error;

	error = cyttsp_handshake(ts);
	अगर (error)
		वापस error;

	वापस ts->xy_data.act_dist == CY_ACT_DIST_DFLT ? -EIO : 0;
पूर्ण

अटल पूर्णांक cyttsp_set_sysinfo_mode(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;

	स_रखो(&ts->sysinfo_data, 0, माप(ts->sysinfo_data));

	/* चयन to sysinfo mode */
	error = ttsp_send_command(ts, CY_SYSINFO_MODE);
	अगर (error)
		वापस error;

	/* पढ़ो sysinfo रेजिस्टरs */
	msleep(CY_DELAY_DFLT);
	error = ttsp_पढ़ो_block_data(ts, CY_REG_BASE, माप(ts->sysinfo_data),
				      &ts->sysinfo_data);
	अगर (error)
		वापस error;

	error = cyttsp_handshake(ts);
	अगर (error)
		वापस error;

	अगर (!ts->sysinfo_data.tts_verh && !ts->sysinfo_data.tts_verl)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_set_sysinfo_regs(काष्ठा cyttsp *ts)
अणु
	पूर्णांक retval = 0;

	अगर (ts->act_पूर्णांकrvl != CY_ACT_INTRVL_DFLT ||
	    ts->tch_पंचांगout != CY_TCH_TMOUT_DFLT ||
	    ts->lp_पूर्णांकrvl != CY_LP_INTRVL_DFLT) अणु

		u8 पूर्णांकrvl_ray[] = अणु
			ts->act_पूर्णांकrvl,
			ts->tch_पंचांगout,
			ts->lp_पूर्णांकrvl
		पूर्ण;

		/* set पूर्णांकrvl रेजिस्टरs */
		retval = ttsp_ग_लिखो_block_data(ts, CY_REG_ACT_INTRVL,
					माप(पूर्णांकrvl_ray), पूर्णांकrvl_ray);
		msleep(CY_DELAY_DFLT);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम cyttsp_hard_reset(काष्ठा cyttsp *ts)
अणु
	अगर (ts->reset_gpio) अणु
		/*
		 * According to the CY8CTMA340 datasheet page 21, the बाह्यal
		 * reset pulse width should be >= 1 ms. The datasheet करोes not
		 * specअगरy how दीर्घ we have to रुको after reset but a venकरोr
		 * tree specअगरies 5 ms here.
		 */
		gpiod_set_value_cansleep(ts->reset_gpio, 1);
		usleep_range(1000, 2000);
		gpiod_set_value_cansleep(ts->reset_gpio, 0);
		usleep_range(5000, 6000);
	पूर्ण
पूर्ण

अटल पूर्णांक cyttsp_soft_reset(काष्ठा cyttsp *ts)
अणु
	पूर्णांक retval;

	/* रुको क्रम पूर्णांकerrupt to set पढ़ोy completion */
	reinit_completion(&ts->bl_पढ़ोy);
	ts->state = CY_BL_STATE;

	enable_irq(ts->irq);

	retval = ttsp_send_command(ts, CY_SOFT_RESET_MODE);
	अगर (retval) अणु
		dev_err(ts->dev, "failed to send soft reset\n");
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ts->bl_पढ़ोy,
			msecs_to_jअगरfies(CY_DELAY_DFLT * CY_DELAY_MAX))) अणु
		dev_err(ts->dev, "timeout waiting for soft reset\n");
		retval = -EIO;
	पूर्ण

out:
	ts->state = CY_IDLE_STATE;
	disable_irq(ts->irq);
	वापस retval;
पूर्ण

अटल पूर्णांक cyttsp_act_dist_setup(काष्ठा cyttsp *ts)
अणु
	u8 act_dist_setup = ts->act_dist;

	/* Init gesture; active distance setup */
	वापस ttsp_ग_लिखो_block_data(ts, CY_REG_ACT_DIST,
				माप(act_dist_setup), &act_dist_setup);
पूर्ण

अटल व्योम cyttsp_extract_track_ids(काष्ठा cyttsp_xydata *xy_data, पूर्णांक *ids)
अणु
	ids[0] = xy_data->touch12_id >> 4;
	ids[1] = xy_data->touch12_id & 0xF;
	ids[2] = xy_data->touch34_id >> 4;
	ids[3] = xy_data->touch34_id & 0xF;
पूर्ण

अटल स्थिर काष्ठा cyttsp_tch *cyttsp_get_tch(काष्ठा cyttsp_xydata *xy_data,
					       पूर्णांक idx)
अणु
	चयन (idx) अणु
	हाल 0:
		वापस &xy_data->tch1;
	हाल 1:
		वापस &xy_data->tch2;
	हाल 2:
		वापस &xy_data->tch3;
	हाल 3:
		वापस &xy_data->tch4;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम cyttsp_report_tchdata(काष्ठा cyttsp *ts)
अणु
	काष्ठा cyttsp_xydata *xy_data = &ts->xy_data;
	काष्ठा input_dev *input = ts->input;
	पूर्णांक num_tch = GET_NUM_TOUCHES(xy_data->tt_stat);
	स्थिर काष्ठा cyttsp_tch *tch;
	पूर्णांक ids[CY_MAX_ID];
	पूर्णांक i;
	DECLARE_BITMAP(used, CY_MAX_ID);

	अगर (IS_LARGE_AREA(xy_data->tt_stat) == 1) अणु
		/* terminate all active tracks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Large area detected\n", __func__);
	पूर्ण अन्यथा अगर (num_tch > CY_MAX_FINGER) अणु
		/* terminate all active tracks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Num touch error detected\n", __func__);
	पूर्ण अन्यथा अगर (IS_BAD_PKT(xy_data->tt_mode)) अणु
		/* terminate all active tracks */
		num_tch = 0;
		dev_dbg(ts->dev, "%s: Invalid buffer detected\n", __func__);
	पूर्ण

	cyttsp_extract_track_ids(xy_data, ids);

	biपंचांगap_zero(used, CY_MAX_ID);

	क्रम (i = 0; i < num_tch; i++) अणु
		tch = cyttsp_get_tch(xy_data, i);

		input_mt_slot(input, ids[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, be16_to_cpu(tch->x));
		input_report_असल(input, ABS_MT_POSITION_Y, be16_to_cpu(tch->y));
		input_report_असल(input, ABS_MT_TOUCH_MAJOR, tch->z);

		__set_bit(ids[i], used);
	पूर्ण

	क्रम (i = 0; i < CY_MAX_ID; i++) अणु
		अगर (test_bit(i, used))
			जारी;

		input_mt_slot(input, i);
		input_mt_report_slot_inactive(input);
	पूर्ण

	input_sync(input);
पूर्ण

अटल irqवापस_t cyttsp_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा cyttsp *ts = handle;
	पूर्णांक error;

	अगर (unlikely(ts->state == CY_BL_STATE)) अणु
		complete(&ts->bl_पढ़ोy);
		जाओ out;
	पूर्ण

	/* Get touch data from CYTTSP device */
	error = ttsp_पढ़ो_block_data(ts, CY_REG_BASE,
				 माप(काष्ठा cyttsp_xydata), &ts->xy_data);
	अगर (error)
		जाओ out;

	/* provide flow control handshake */
	error = cyttsp_handshake(ts);
	अगर (error)
		जाओ out;

	अगर (unlikely(ts->state == CY_IDLE_STATE))
		जाओ out;

	अगर (GET_BOOTLOADERMODE(ts->xy_data.tt_mode)) अणु
		/*
		 * TTSP device has reset back to bootloader mode.
		 * Restore to operational mode.
		 */
		error = cyttsp_निकास_bl_mode(ts);
		अगर (error) अणु
			dev_err(ts->dev,
				"Could not return to operational mode, err: %d\n",
				error);
			ts->state = CY_IDLE_STATE;
		पूर्ण
	पूर्ण अन्यथा अणु
		cyttsp_report_tchdata(ts);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cyttsp_घातer_on(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;

	error = cyttsp_soft_reset(ts);
	अगर (error)
		वापस error;

	error = cyttsp_load_bl_regs(ts);
	अगर (error)
		वापस error;

	अगर (GET_BOOTLOADERMODE(ts->bl_data.bl_status) &&
	    IS_VALID_APP(ts->bl_data.bl_status)) अणु
		error = cyttsp_निकास_bl_mode(ts);
		अगर (error) अणु
			dev_err(ts->dev, "failed to exit bootloader mode\n");
			वापस error;
		पूर्ण
	पूर्ण

	अगर (GET_HSTMODE(ts->bl_data.bl_file) != CY_OPERATE_MODE ||
	    IS_OPERATIONAL_ERR(ts->bl_data.bl_status)) अणु
		वापस -ENODEV;
	पूर्ण

	error = cyttsp_set_sysinfo_mode(ts);
	अगर (error)
		वापस error;

	error = cyttsp_set_sysinfo_regs(ts);
	अगर (error)
		वापस error;

	error = cyttsp_set_operational_mode(ts);
	अगर (error)
		वापस error;

	/* init active distance */
	error = cyttsp_act_dist_setup(ts);
	अगर (error)
		वापस error;

	ts->state = CY_ACTIVE_STATE;

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_enable(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;

	/*
	 * The device firmware can wake on an I2C or SPI memory slave
	 * address match. So just पढ़ोing a रेजिस्टर is sufficient to
	 * wake up the device. The first पढ़ो attempt will fail but it
	 * will wake it up making the second पढ़ो attempt successful.
	 */
	error = ttsp_पढ़ो_block_data(ts, CY_REG_BASE,
				     माप(ts->xy_data), &ts->xy_data);
	अगर (error)
		वापस error;

	अगर (GET_HSTMODE(ts->xy_data.hst_mode))
		वापस -EIO;

	enable_irq(ts->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_disable(काष्ठा cyttsp *ts)
अणु
	पूर्णांक error;

	error = ttsp_send_command(ts, CY_LOW_POWER_MODE);
	अगर (error)
		वापस error;

	disable_irq(ts->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cyttsp_suspend(काष्ठा device *dev)
अणु
	काष्ठा cyttsp *ts = dev_get_drvdata(dev);
	पूर्णांक retval = 0;

	mutex_lock(&ts->input->mutex);

	अगर (input_device_enabled(ts->input)) अणु
		retval = cyttsp_disable(ts);
		अगर (retval == 0)
			ts->suspended = true;
	पूर्ण

	mutex_unlock(&ts->input->mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक __maybe_unused cyttsp_resume(काष्ठा device *dev)
अणु
	काष्ठा cyttsp *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->input->mutex);

	अगर (input_device_enabled(ts->input))
		cyttsp_enable(ts);

	ts->suspended = false;

	mutex_unlock(&ts->input->mutex);

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(cyttsp_pm_ops, cyttsp_suspend, cyttsp_resume);
EXPORT_SYMBOL_GPL(cyttsp_pm_ops);

अटल पूर्णांक cyttsp_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा cyttsp *ts = input_get_drvdata(dev);
	पूर्णांक retval = 0;

	अगर (!ts->suspended)
		retval = cyttsp_enable(ts);

	वापस retval;
पूर्ण

अटल व्योम cyttsp_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा cyttsp *ts = input_get_drvdata(dev);

	अगर (!ts->suspended)
		cyttsp_disable(ts);
पूर्ण

अटल पूर्णांक cyttsp_parse_properties(काष्ठा cyttsp *ts)
अणु
	काष्ठा device *dev = ts->dev;
	u32 dt_value;
	पूर्णांक ret;

	ts->bl_keys = devm_kzalloc(dev, CY_NUM_BL_KEYS, GFP_KERNEL);
	अगर (!ts->bl_keys)
		वापस -ENOMEM;

	/* Set some शेष values */
	ts->use_hndshk = false;
	ts->act_dist = CY_ACT_DIST_DFLT;
	ts->act_पूर्णांकrvl = CY_ACT_INTRVL_DFLT;
	ts->tch_पंचांगout = CY_TCH_TMOUT_DFLT;
	ts->lp_पूर्णांकrvl = CY_LP_INTRVL_DFLT;

	ret = device_property_पढ़ो_u8_array(dev, "bootloader-key",
					    ts->bl_keys, CY_NUM_BL_KEYS);
	अगर (ret) अणु
		dev_err(dev,
			"bootloader-key property could not be retrieved\n");
		वापस ret;
	पूर्ण

	ts->use_hndshk = device_property_present(dev, "use-handshake");

	अगर (!device_property_पढ़ो_u32(dev, "active-distance", &dt_value)) अणु
		अगर (dt_value > 15) अणु
			dev_err(dev, "active-distance (%u) must be [0-15]\n",
				dt_value);
			वापस -EINVAL;
		पूर्ण
		ts->act_dist &= ~CY_ACT_DIST_MASK;
		ts->act_dist |= dt_value;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(dev, "active-interval-ms", &dt_value)) अणु
		अगर (dt_value > 255) अणु
			dev_err(dev, "active-interval-ms (%u) must be [0-255]\n",
				dt_value);
			वापस -EINVAL;
		पूर्ण
		ts->act_पूर्णांकrvl = dt_value;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(dev, "lowpower-interval-ms", &dt_value)) अणु
		अगर (dt_value > 2550) अणु
			dev_err(dev, "lowpower-interval-ms (%u) must be [0-2550]\n",
				dt_value);
			वापस -EINVAL;
		पूर्ण
		/* Register value is expressed in 0.01s / bit */
		ts->lp_पूर्णांकrvl = dt_value / 10;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(dev, "touch-timeout-ms", &dt_value)) अणु
		अगर (dt_value > 2550) अणु
			dev_err(dev, "touch-timeout-ms (%u) must be [0-2550]\n",
				dt_value);
			वापस -EINVAL;
		पूर्ण
		/* Register value is expressed in 0.01s / bit */
		ts->tch_पंचांगout = dt_value / 10;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cyttsp *cyttsp_probe(स्थिर काष्ठा cyttsp_bus_ops *bus_ops,
			    काष्ठा device *dev, पूर्णांक irq, माप_प्रकार xfer_buf_size)
अणु
	काष्ठा cyttsp *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	ts = devm_kzalloc(dev, माप(*ts) + xfer_buf_size, GFP_KERNEL);
	अगर (!ts)
		वापस ERR_PTR(-ENOMEM);

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev)
		वापस ERR_PTR(-ENOMEM);

	ts->dev = dev;
	ts->input = input_dev;
	ts->bus_ops = bus_ops;
	ts->irq = irq;

	ts->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		dev_err(dev, "Failed to request reset gpio, error %d\n", error);
		वापस ERR_PTR(error);
	पूर्ण

	error = cyttsp_parse_properties(ts);
	अगर (error)
		वापस ERR_PTR(error);

	init_completion(&ts->bl_पढ़ोy);

	input_dev->name = "Cypress TTSP TouchScreen";
	input_dev->id.bustype = bus_ops->bustype;
	input_dev->dev.parent = ts->dev;

	input_dev->खोलो = cyttsp_खोलो;
	input_dev->बंद = cyttsp_बंद;

	input_set_drvdata(input_dev, ts);

	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	/* One byte क्रम width 0..255 so this is the limit */
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);

	touchscreen_parse_properties(input_dev, true, शून्य);

	error = input_mt_init_slots(input_dev, CY_MAX_ID, INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(dev, "Unable to init MT slots.\n");
		वापस ERR_PTR(error);
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, ts->irq, शून्य, cyttsp_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
					  IRQF_NO_AUTOEN,
					  "cyttsp", ts);
	अगर (error) अणु
		dev_err(ts->dev, "failed to request IRQ %d, err: %d\n",
			ts->irq, error);
		वापस ERR_PTR(error);
	पूर्ण

	cyttsp_hard_reset(ts);

	error = cyttsp_घातer_on(ts);
	अगर (error)
		वापस ERR_PTR(error);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(ts->dev, "failed to register input device: %d\n",
			error);
		वापस ERR_PTR(error);
	पूर्ण

	वापस ts;
पूर्ण
EXPORT_SYMBOL_GPL(cyttsp_probe);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard touchscreen driver core");
MODULE_AUTHOR("Cypress");
