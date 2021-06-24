<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VTI CMA3000_D0x Accelerometer driver
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Hemanth V <hemanthv@ti.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/cma3000.h>
#समावेश <linux/module.h>

#समावेश "cma3000_d0x.h"

#घोषणा CMA3000_WHOAMI      0x00
#घोषणा CMA3000_REVID       0x01
#घोषणा CMA3000_CTRL        0x02
#घोषणा CMA3000_STATUS      0x03
#घोषणा CMA3000_RSTR        0x04
#घोषणा CMA3000_INTSTATUS   0x05
#घोषणा CMA3000_DOUTX       0x06
#घोषणा CMA3000_DOUTY       0x07
#घोषणा CMA3000_DOUTZ       0x08
#घोषणा CMA3000_MDTHR       0x09
#घोषणा CMA3000_MDFFTMR     0x0A
#घोषणा CMA3000_FFTHR       0x0B

#घोषणा CMA3000_RANGE2G    (1 << 7)
#घोषणा CMA3000_RANGE8G    (0 << 7)
#घोषणा CMA3000_BUSI2C     (0 << 4)
#घोषणा CMA3000_MODEMASK   (7 << 1)
#घोषणा CMA3000_GRANGEMASK (1 << 7)

#घोषणा CMA3000_STATUS_PERR    1
#घोषणा CMA3000_INTSTATUS_FFDET (1 << 2)

/* Settling समय delay in ms */
#घोषणा CMA3000_SETDELAY    30

/* Delay क्रम clearing पूर्णांकerrupt in us */
#घोषणा CMA3000_INTDELAY    44


/*
 * Bit weights in mg क्रम bit 0, other bits need
 * multiply factor 2^n. Eight bit is the sign bit.
 */
#घोषणा BIT_TO_2G  18
#घोषणा BIT_TO_8G  71

काष्ठा cma3000_accl_data अणु
	स्थिर काष्ठा cma3000_bus_ops *bus_ops;
	स्थिर काष्ठा cma3000_platक्रमm_data *pdata;

	काष्ठा device *dev;
	काष्ठा input_dev *input_dev;

	पूर्णांक bit_to_mg;
	पूर्णांक irq;

	पूर्णांक g_range;
	u8 mode;

	काष्ठा mutex mutex;
	bool खोलोed;
	bool suspended;
पूर्ण;

#घोषणा CMA3000_READ(data, reg, msg) \
	(data->bus_ops->पढ़ो(data->dev, reg, msg))
#घोषणा CMA3000_SET(data, reg, val, msg) \
	((data)->bus_ops->ग_लिखो(data->dev, reg, val, msg))

/*
 * Conversion क्रम each of the eight modes to g, depending
 * on G range i.e 2G or 8G. Some modes always operate in
 * 8G.
 */

अटल पूर्णांक mode_to_mg[8][2] = अणु
	अणु 0, 0 पूर्ण,
	अणु BIT_TO_8G, BIT_TO_2G पूर्ण,
	अणु BIT_TO_8G, BIT_TO_2G पूर्ण,
	अणु BIT_TO_8G, BIT_TO_8G पूर्ण,
	अणु BIT_TO_8G, BIT_TO_8G पूर्ण,
	अणु BIT_TO_8G, BIT_TO_2G पूर्ण,
	अणु BIT_TO_8G, BIT_TO_2G पूर्ण,
	अणु 0, 0पूर्ण,
पूर्ण;

अटल व्योम decode_mg(काष्ठा cma3000_accl_data *data, पूर्णांक *datax,
				पूर्णांक *datay, पूर्णांक *dataz)
अणु
	/* Data in 2's complement, convert to mg */
	*datax = ((s8)*datax) * data->bit_to_mg;
	*datay = ((s8)*datay) * data->bit_to_mg;
	*dataz = ((s8)*dataz) * data->bit_to_mg;
पूर्ण

अटल irqवापस_t cma3000_thपढ़ो_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cma3000_accl_data *data = dev_id;
	पूर्णांक datax, datay, dataz, पूर्णांकr_status;
	u8 ctrl, mode, range;

	पूर्णांकr_status = CMA3000_READ(data, CMA3000_INTSTATUS, "interrupt status");
	अगर (पूर्णांकr_status < 0)
		वापस IRQ_NONE;

	/* Check अगर मुक्त fall is detected, report immediately */
	अगर (पूर्णांकr_status & CMA3000_INTSTATUS_FFDET) अणु
		input_report_असल(data->input_dev, ABS_MISC, 1);
		input_sync(data->input_dev);
	पूर्ण अन्यथा अणु
		input_report_असल(data->input_dev, ABS_MISC, 0);
	पूर्ण

	datax = CMA3000_READ(data, CMA3000_DOUTX, "X");
	datay = CMA3000_READ(data, CMA3000_DOUTY, "Y");
	dataz = CMA3000_READ(data, CMA3000_DOUTZ, "Z");

	ctrl = CMA3000_READ(data, CMA3000_CTRL, "ctrl");
	mode = (ctrl & CMA3000_MODEMASK) >> 1;
	range = (ctrl & CMA3000_GRANGEMASK) >> 7;

	data->bit_to_mg = mode_to_mg[mode][range];

	/* Interrupt not क्रम this device */
	अगर (data->bit_to_mg == 0)
		वापस IRQ_NONE;

	/* Decode रेजिस्टर values to milli g */
	decode_mg(data, &datax, &datay, &dataz);

	input_report_असल(data->input_dev, ABS_X, datax);
	input_report_असल(data->input_dev, ABS_Y, datay);
	input_report_असल(data->input_dev, ABS_Z, dataz);
	input_sync(data->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cma3000_reset(काष्ठा cma3000_accl_data *data)
अणु
	पूर्णांक val;

	/* Reset sequence */
	CMA3000_SET(data, CMA3000_RSTR, 0x02, "Reset");
	CMA3000_SET(data, CMA3000_RSTR, 0x0A, "Reset");
	CMA3000_SET(data, CMA3000_RSTR, 0x04, "Reset");

	/* Settling समय delay */
	mdelay(10);

	val = CMA3000_READ(data, CMA3000_STATUS, "Status");
	अगर (val < 0) अणु
		dev_err(data->dev, "Reset failed\n");
		वापस val;
	पूर्ण

	अगर (val & CMA3000_STATUS_PERR) अणु
		dev_err(data->dev, "Parity Error\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cma3000_घातeron(काष्ठा cma3000_accl_data *data)
अणु
	स्थिर काष्ठा cma3000_platक्रमm_data *pdata = data->pdata;
	u8 ctrl = 0;
	पूर्णांक ret;

	अगर (data->g_range == CMARANGE_2G) अणु
		ctrl = (data->mode << 1) | CMA3000_RANGE2G;
	पूर्ण अन्यथा अगर (data->g_range == CMARANGE_8G) अणु
		ctrl = (data->mode << 1) | CMA3000_RANGE8G;
	पूर्ण अन्यथा अणु
		dev_info(data->dev,
			 "Invalid G range specified, assuming 8G\n");
		ctrl = (data->mode << 1) | CMA3000_RANGE8G;
	पूर्ण

	ctrl |= data->bus_ops->ctrl_mod;

	CMA3000_SET(data, CMA3000_MDTHR, pdata->mdthr,
		    "Motion Detect Threshold");
	CMA3000_SET(data, CMA3000_MDFFTMR, pdata->mdffपंचांगr,
		    "Time register");
	CMA3000_SET(data, CMA3000_FFTHR, pdata->ffthr,
		    "Free fall threshold");
	ret = CMA3000_SET(data, CMA3000_CTRL, ctrl, "Mode setting");
	अगर (ret < 0)
		वापस -EIO;

	msleep(CMA3000_SETDELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक cma3000_घातeroff(काष्ठा cma3000_accl_data *data)
अणु
	पूर्णांक ret;

	ret = CMA3000_SET(data, CMA3000_CTRL, CMAMODE_POFF, "Mode setting");
	msleep(CMA3000_SETDELAY);

	वापस ret;
पूर्ण

अटल पूर्णांक cma3000_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा cma3000_accl_data *data = input_get_drvdata(input_dev);

	mutex_lock(&data->mutex);

	अगर (!data->suspended)
		cma3000_घातeron(data);

	data->खोलोed = true;

	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल व्योम cma3000_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा cma3000_accl_data *data = input_get_drvdata(input_dev);

	mutex_lock(&data->mutex);

	अगर (!data->suspended)
		cma3000_घातeroff(data);

	data->खोलोed = false;

	mutex_unlock(&data->mutex);
पूर्ण

व्योम cma3000_suspend(काष्ठा cma3000_accl_data *data)
अणु
	mutex_lock(&data->mutex);

	अगर (!data->suspended && data->खोलोed)
		cma3000_घातeroff(data);

	data->suspended = true;

	mutex_unlock(&data->mutex);
पूर्ण
EXPORT_SYMBOL(cma3000_suspend);


व्योम cma3000_resume(काष्ठा cma3000_accl_data *data)
अणु
	mutex_lock(&data->mutex);

	अगर (data->suspended && data->खोलोed)
		cma3000_घातeron(data);

	data->suspended = false;

	mutex_unlock(&data->mutex);
पूर्ण
EXPORT_SYMBOL(cma3000_resume);

काष्ठा cma3000_accl_data *cma3000_init(काष्ठा device *dev, पूर्णांक irq,
				       स्थिर काष्ठा cma3000_bus_ops *bops)
अणु
	स्थिर काष्ठा cma3000_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा cma3000_accl_data *data;
	काष्ठा input_dev *input_dev;
	पूर्णांक rev;
	पूर्णांक error;

	अगर (!pdata) अणु
		dev_err(dev, "platform data not found\n");
		error = -EINVAL;
		जाओ err_out;
	पूर्ण


	/* अगर no IRQ वापस error */
	अगर (irq == 0) अणु
		error = -EINVAL;
		जाओ err_out;
	पूर्ण

	data = kzalloc(माप(काष्ठा cma3000_accl_data), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!data || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	data->dev = dev;
	data->input_dev = input_dev;
	data->bus_ops = bops;
	data->pdata = pdata;
	data->irq = irq;
	mutex_init(&data->mutex);

	data->mode = pdata->mode;
	अगर (data->mode > CMAMODE_POFF) अणु
		data->mode = CMAMODE_MOTDET;
		dev_warn(dev,
			 "Invalid mode specified, assuming Motion Detect\n");
	पूर्ण

	data->g_range = pdata->g_range;
	अगर (data->g_range != CMARANGE_2G && data->g_range != CMARANGE_8G) अणु
		dev_info(dev,
			 "Invalid G range specified, assuming 8G\n");
		data->g_range = CMARANGE_8G;
	पूर्ण

	input_dev->name = "cma3000-accelerometer";
	input_dev->id.bustype = bops->bustype;
	input_dev->खोलो = cma3000_खोलो;
	input_dev->बंद = cma3000_बंद;

	 __set_bit(EV_ABS, input_dev->evbit);

	input_set_असल_params(input_dev, ABS_X,
			-data->g_range, data->g_range, pdata->fuzz_x, 0);
	input_set_असल_params(input_dev, ABS_Y,
			-data->g_range, data->g_range, pdata->fuzz_y, 0);
	input_set_असल_params(input_dev, ABS_Z,
			-data->g_range, data->g_range, pdata->fuzz_z, 0);
	input_set_असल_params(input_dev, ABS_MISC, 0, 1, 0, 0);

	input_set_drvdata(input_dev, data);

	error = cma3000_reset(data);
	अगर (error)
		जाओ err_मुक्त_mem;

	rev = CMA3000_READ(data, CMA3000_REVID, "Revid");
	अगर (rev < 0) अणु
		error = rev;
		जाओ err_मुक्त_mem;
	पूर्ण

	pr_info("CMA3000 Accelerometer: Revision %x\n", rev);

	error = request_thपढ़ोed_irq(irq, शून्य, cma3000_thपढ़ो_irq,
				     pdata->irqflags | IRQF_ONESHOT,
				     "cma3000_d0x", data);
	अगर (error) अणु
		dev_err(dev, "request_threaded_irq failed\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	error = input_रेजिस्टर_device(data->input_dev);
	अगर (error) अणु
		dev_err(dev, "Unable to register input device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	वापस data;

err_मुक्त_irq:
	मुक्त_irq(irq, data);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(data);
err_out:
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL(cma3000_init);

व्योम cma3000_निकास(काष्ठा cma3000_accl_data *data)
अणु
	मुक्त_irq(data->irq, data);
	input_unरेजिस्टर_device(data->input_dev);
	kमुक्त(data);
पूर्ण
EXPORT_SYMBOL(cma3000_निकास);

MODULE_DESCRIPTION("CMA3000-D0x Accelerometer Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hemanth V <hemanthv@ti.com>");
