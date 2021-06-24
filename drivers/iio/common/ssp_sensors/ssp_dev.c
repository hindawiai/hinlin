<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश "ssp.h"

#घोषणा SSP_WDT_TIME			10000
#घोषणा SSP_LIMIT_RESET_CNT		20
#घोषणा SSP_LIMIT_TIMEOUT_CNT		3

/* It is possible that it is max clk rate क्रम version 1.0 of bootcode */
#घोषणा SSP_BOOT_SPI_HZ	400000

/*
 * These fields can look enigmatic but this काष्ठाure is used मुख्यly to flat
 * some values and depends on command type.
 */
काष्ठा ssp_inकाष्ठाion अणु
	__le32 a;
	__le32 b;
	u8 c;
पूर्ण __attribute__((__packed__));

अटल स्थिर u8 ssp_magnitude_table[] = अणु110, 85, 171, 71, 203, 195, 0, 67,
	208, 56, 175, 244, 206, 213, 0, 92, 250, 0, 55, 48, 189, 252, 171,
	243, 13, 45, 250पूर्ण;

अटल स्थिर काष्ठा ssp_sensorhub_info ssp_rinato_info = अणु
	.fw_name = "ssp_B2.fw",
	.fw_crashed_name = "ssp_crashed.fw",
	.fw_rev = 14052300,
	.mag_table = ssp_magnitude_table,
	.mag_length = ARRAY_SIZE(ssp_magnitude_table),
पूर्ण;

अटल स्थिर काष्ठा ssp_sensorhub_info ssp_thermostat_info = अणु
	.fw_name = "thermostat_B2.fw",
	.fw_crashed_name = "ssp_crashed.fw",
	.fw_rev = 14080600,
	.mag_table = ssp_magnitude_table,
	.mag_length = ARRAY_SIZE(ssp_magnitude_table),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sensorhub_sensor_devs[] = अणु
	अणु
		.name = "ssp-accelerometer",
	पूर्ण,
	अणु
		.name = "ssp-gyroscope",
	पूर्ण,
पूर्ण;

अटल व्योम ssp_toggle_mcu_reset_gpio(काष्ठा ssp_data *data)
अणु
	gpiod_set_value(data->mcu_reset_gpiod, 0);
	usleep_range(1000, 1200);
	gpiod_set_value(data->mcu_reset_gpiod, 1);
	msleep(50);
पूर्ण

अटल व्योम ssp_sync_available_sensors(काष्ठा ssp_data *data)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < SSP_SENSOR_MAX; ++i) अणु
		अगर (data->available_sensors & BIT(i)) अणु
			ret = ssp_enable_sensor(data, i, data->delay_buf[i]);
			अगर (ret < 0) अणु
				dev_err(&data->spi->dev,
					"Sync sensor nr: %d fail\n", i);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = ssp_command(data, SSP_MSG2SSP_AP_MCU_SET_DUMPMODE,
			  data->mcu_dump_mode);
	अगर (ret < 0)
		dev_err(&data->spi->dev,
			"SSP_MSG2SSP_AP_MCU_SET_DUMPMODE failed\n");
पूर्ण

अटल व्योम ssp_enable_mcu(काष्ठा ssp_data *data, bool enable)
अणु
	dev_info(&data->spi->dev, "current shutdown = %d, old = %d\n", enable,
		 data->shut_करोwn);

	अगर (enable && data->shut_करोwn) अणु
		data->shut_करोwn = false;
		enable_irq(data->spi->irq);
		enable_irq_wake(data->spi->irq);
	पूर्ण अन्यथा अगर (!enable && !data->shut_करोwn) अणु
		data->shut_करोwn = true;
		disable_irq(data->spi->irq);
		disable_irq_wake(data->spi->irq);
	पूर्ण अन्यथा अणु
		dev_warn(&data->spi->dev, "current shutdown = %d, old = %d\n",
			 enable, data->shut_करोwn);
	पूर्ण
पूर्ण

/*
 * This function is the first one which communicates with the mcu so it is
 * possible that the first attempt will fail
 */
अटल पूर्णांक ssp_check_fwbl(काष्ठा ssp_data *data)
अणु
	पूर्णांक retries = 0;

	जबतक (retries++ < 5) अणु
		data->cur_firm_rev = ssp_get_firmware_rev(data);
		अगर (data->cur_firm_rev == SSP_INVALID_REVISION ||
		    data->cur_firm_rev == SSP_INVALID_REVISION2) अणु
			dev_warn(&data->spi->dev,
				 "Invalid revision, trying %d time\n", retries);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (data->cur_firm_rev == SSP_INVALID_REVISION ||
	    data->cur_firm_rev == SSP_INVALID_REVISION2) अणु
		dev_err(&data->spi->dev, "SSP_INVALID_REVISION\n");
		वापस SSP_FW_DL_STATE_NEED_TO_SCHEDULE;
	पूर्ण

	dev_info(&data->spi->dev,
		 "MCU Firm Rev : Old = %8u, New = %8u\n",
		 data->cur_firm_rev,
		 data->sensorhub_info->fw_rev);

	अगर (data->cur_firm_rev != data->sensorhub_info->fw_rev)
		वापस SSP_FW_DL_STATE_NEED_TO_SCHEDULE;

	वापस SSP_FW_DL_STATE_NONE;
पूर्ण

अटल व्योम ssp_reset_mcu(काष्ठा ssp_data *data)
अणु
	ssp_enable_mcu(data, false);
	ssp_clean_pending_list(data);
	ssp_toggle_mcu_reset_gpio(data);
	ssp_enable_mcu(data, true);
पूर्ण

अटल व्योम ssp_wdt_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssp_data *data = container_of(work, काष्ठा ssp_data, work_wdt);

	dev_err(&data->spi->dev, "%s - Sensor state: 0x%x, RC: %u, CC: %u\n",
		__func__, data->available_sensors, data->reset_cnt,
		data->com_fail_cnt);

	ssp_reset_mcu(data);
	data->com_fail_cnt = 0;
	data->समयout_cnt = 0;
पूर्ण

अटल व्योम ssp_wdt_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा ssp_data *data = from_समयr(data, t, wdt_समयr);

	चयन (data->fw_dl_state) अणु
	हाल SSP_FW_DL_STATE_FAIL:
	हाल SSP_FW_DL_STATE_DOWNLOADING:
	हाल SSP_FW_DL_STATE_SYNC:
		जाओ _mod;
	पूर्ण

	अगर (data->समयout_cnt > SSP_LIMIT_TIMEOUT_CNT ||
	    data->com_fail_cnt > SSP_LIMIT_RESET_CNT)
		queue_work(प्रणाली_घातer_efficient_wq, &data->work_wdt);
_mod:
	mod_समयr(&data->wdt_समयr, jअगरfies + msecs_to_jअगरfies(SSP_WDT_TIME));
पूर्ण

अटल व्योम ssp_enable_wdt_समयr(काष्ठा ssp_data *data)
अणु
	mod_समयr(&data->wdt_समयr, jअगरfies + msecs_to_jअगरfies(SSP_WDT_TIME));
पूर्ण

अटल व्योम ssp_disable_wdt_समयr(काष्ठा ssp_data *data)
अणु
	del_समयr_sync(&data->wdt_समयr);
	cancel_work_sync(&data->work_wdt);
पूर्ण

/**
 * ssp_get_sensor_delay() - माला_लो sensor data acquisition period
 * @data:	sensorhub काष्ठाure
 * @type:	SSP sensor type
 *
 * Returns acquisition period in ms
 */
u32 ssp_get_sensor_delay(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type)
अणु
	वापस data->delay_buf[type];
पूर्ण
EXPORT_SYMBOL(ssp_get_sensor_delay);

/**
 * ssp_enable_sensor() - enables data acquisition क्रम sensor
 * @data:	sensorhub काष्ठाure
 * @type:	SSP sensor type
 * @delay:	delay in ms
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_enable_sensor(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type,
		      u32 delay)
अणु
	पूर्णांक ret;
	काष्ठा ssp_inकाष्ठाion to_send;

	to_send.a = cpu_to_le32(delay);
	to_send.b = cpu_to_le32(data->batch_latency_buf[type]);
	to_send.c = data->batch_opt_buf[type];

	चयन (data->check_status[type]) अणु
	हाल SSP_INITIALIZATION_STATE:
		/* करो calibration step, now just enable */
	हाल SSP_ADD_SENSOR_STATE:
		ret = ssp_send_inकाष्ठाion(data,
					   SSP_MSG2SSP_INST_BYPASS_SENSOR_ADD,
					   type,
					   (u8 *)&to_send, माप(to_send));
		अगर (ret < 0) अणु
			dev_err(&data->spi->dev, "Enabling sensor failed\n");
			data->check_status[type] = SSP_NO_SENSOR_STATE;
			जाओ derror;
		पूर्ण

		data->sensor_enable |= BIT(type);
		data->check_status[type] = SSP_RUNNING_SENSOR_STATE;
		अवरोध;
	हाल SSP_RUNNING_SENSOR_STATE:
		ret = ssp_send_inकाष्ठाion(data,
					   SSP_MSG2SSP_INST_CHANGE_DELAY, type,
					   (u8 *)&to_send, माप(to_send));
		अगर (ret < 0) अणु
			dev_err(&data->spi->dev,
				"Changing sensor delay failed\n");
			जाओ derror;
		पूर्ण
		अवरोध;
	शेष:
		data->check_status[type] = SSP_ADD_SENSOR_STATE;
		अवरोध;
	पूर्ण

	data->delay_buf[type] = delay;

	अगर (atomic_inc_वापस(&data->enable_refcount) == 1)
		ssp_enable_wdt_समयr(data);

	वापस 0;

derror:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ssp_enable_sensor);

/**
 * ssp_change_delay() - changes data acquisition क्रम sensor
 * @data:	sensorhub काष्ठाure
 * @type:	SSP sensor type
 * @delay:	delay in ms
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_change_delay(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type,
		     u32 delay)
अणु
	पूर्णांक ret;
	काष्ठा ssp_inकाष्ठाion to_send;

	to_send.a = cpu_to_le32(delay);
	to_send.b = cpu_to_le32(data->batch_latency_buf[type]);
	to_send.c = data->batch_opt_buf[type];

	ret = ssp_send_inकाष्ठाion(data, SSP_MSG2SSP_INST_CHANGE_DELAY, type,
				   (u8 *)&to_send, माप(to_send));
	अगर (ret < 0) अणु
		dev_err(&data->spi->dev, "Changing sensor delay failed\n");
		वापस ret;
	पूर्ण

	data->delay_buf[type] = delay;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ssp_change_delay);

/**
 * ssp_disable_sensor() - disables sensor
 *
 * @data:	sensorhub काष्ठाure
 * @type:	SSP sensor type
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_disable_sensor(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type)
अणु
	पूर्णांक ret;
	__le32 command;

	अगर (data->sensor_enable & BIT(type)) अणु
		command = cpu_to_le32(data->delay_buf[type]);

		ret = ssp_send_inकाष्ठाion(data,
					   SSP_MSG2SSP_INST_BYPASS_SENSOR_RM,
					   type, (u8 *)&command,
					   माप(command));
		अगर (ret < 0) अणु
			dev_err(&data->spi->dev, "Remove sensor fail\n");
			वापस ret;
		पूर्ण

		data->sensor_enable &= ~BIT(type);
	पूर्ण

	data->check_status[type] = SSP_ADD_SENSOR_STATE;

	अगर (atomic_dec_and_test(&data->enable_refcount))
		ssp_disable_wdt_समयr(data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ssp_disable_sensor);

अटल irqवापस_t ssp_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ssp_data *data = dev_id;

	/*
	 * This wrapper is करोne to preserve error path क्रम ssp_irq_msg, also
	 * it is defined in dअगरferent file.
	 */
	ssp_irq_msg(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ssp_initialize_mcu(काष्ठा ssp_data *data)
अणु
	पूर्णांक ret;

	ssp_clean_pending_list(data);

	ret = ssp_get_chipid(data);
	अगर (ret != SSP_DEVICE_ID) अणु
		dev_err(&data->spi->dev, "%s - MCU %s ret = %d\n", __func__,
			ret < 0 ? "is not working" : "identification failed",
			ret);
		वापस ret < 0 ? ret : -ENODEV;
	पूर्ण

	dev_info(&data->spi->dev, "MCU device ID = %d\n", ret);

	/*
	 * needs clarअगरication, क्रम now करो not want to export all transfer
	 * methods to sensors' drivers
	 */
	ret = ssp_set_magnetic_matrix(data);
	अगर (ret < 0) अणु
		dev_err(&data->spi->dev,
			"%s - ssp_set_magnetic_matrix failed\n", __func__);
		वापस ret;
	पूर्ण

	data->available_sensors = ssp_get_sensor_scanning_info(data);
	अगर (data->available_sensors == 0) अणु
		dev_err(&data->spi->dev,
			"%s - ssp_get_sensor_scanning_info failed\n", __func__);
		वापस -EIO;
	पूर्ण

	data->cur_firm_rev = ssp_get_firmware_rev(data);
	dev_info(&data->spi->dev, "MCU Firm Rev : New = %8u\n",
		 data->cur_firm_rev);

	वापस ssp_command(data, SSP_MSG2SSP_AP_MCU_DUMP_CHECK, 0);
पूर्ण

/*
 * sensorhub can request its reinitialization as some brutal and rare error
 * handling. It can be requested from the MCU.
 */
अटल व्योम ssp_refresh_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssp_data *data = container_of((काष्ठा delayed_work *)work,
					     काष्ठा ssp_data, work_refresh);

	dev_info(&data->spi->dev, "refreshing\n");

	data->reset_cnt++;

	अगर (ssp_initialize_mcu(data) >= 0) अणु
		ssp_sync_available_sensors(data);
		अगर (data->last_ap_state != 0)
			ssp_command(data, data->last_ap_state, 0);

		अगर (data->last_resume_state != 0)
			ssp_command(data, data->last_resume_state, 0);

		data->समयout_cnt = 0;
		data->com_fail_cnt = 0;
	पूर्ण
पूर्ण

पूर्णांक ssp_queue_ssp_refresh_task(काष्ठा ssp_data *data, अचिन्हित पूर्णांक delay)
अणु
	cancel_delayed_work_sync(&data->work_refresh);

	वापस queue_delayed_work(प्रणाली_घातer_efficient_wq,
				  &data->work_refresh,
				  msecs_to_jअगरfies(delay));
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ssp_of_match[] = अणु
	अणु
		.compatible	= "samsung,sensorhub-rinato",
		.data		= &ssp_rinato_info,
	पूर्ण, अणु
		.compatible	= "samsung,sensorhub-thermostat",
		.data		= &ssp_thermostat_info,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ssp_of_match);

अटल काष्ठा ssp_data *ssp_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा ssp_data *data;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा of_device_id *match;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->mcu_ap_gpiod = devm_gpiod_get(dev, "mcu-ap", GPIOD_IN);
	अगर (IS_ERR(data->mcu_ap_gpiod))
		वापस शून्य;

	data->ap_mcu_gpiod = devm_gpiod_get(dev, "ap-mcu", GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->ap_mcu_gpiod))
		वापस शून्य;

	data->mcu_reset_gpiod = devm_gpiod_get(dev, "mcu-reset",
					       GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->mcu_reset_gpiod))
		वापस शून्य;

	match = of_match_node(ssp_of_match, node);
	अगर (!match)
		वापस शून्य;

	data->sensorhub_info = match->data;

	dev_set_drvdata(dev, data);

	वापस data;
पूर्ण
#अन्यथा
अटल काष्ठा ssp_data *ssp_parse_dt(काष्ठा device *pdev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * ssp_रेजिस्टर_consumer() - रेजिस्टरs iio consumer in ssp framework
 *
 * @indio_dev:	consumer iio device
 * @type:	ssp sensor type
 */
व्योम ssp_रेजिस्टर_consumer(काष्ठा iio_dev *indio_dev, क्रमागत ssp_sensor_type type)
अणु
	काष्ठा ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	data->sensor_devs[type] = indio_dev;
पूर्ण
EXPORT_SYMBOL(ssp_रेजिस्टर_consumer);

अटल पूर्णांक ssp_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret, i;
	काष्ठा ssp_data *data;

	data = ssp_parse_dt(&spi->dev);
	अगर (!data) अणु
		dev_err(&spi->dev, "Failed to find platform data\n");
		वापस -ENODEV;
	पूर्ण

	ret = mfd_add_devices(&spi->dev, PLATFORM_DEVID_NONE,
			      sensorhub_sensor_devs,
			      ARRAY_SIZE(sensorhub_sensor_devs), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "mfd add devices fail\n");
		वापस ret;
	पूर्ण

	spi->mode = SPI_MODE_1;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Failed to setup spi\n");
		वापस ret;
	पूर्ण

	data->fw_dl_state = SSP_FW_DL_STATE_NONE;
	data->spi = spi;
	spi_set_drvdata(spi, data);

	mutex_init(&data->comm_lock);

	क्रम (i = 0; i < SSP_SENSOR_MAX; ++i) अणु
		data->delay_buf[i] = SSP_DEFAULT_POLLING_DELAY;
		data->batch_latency_buf[i] = 0;
		data->batch_opt_buf[i] = 0;
		data->check_status[i] = SSP_INITIALIZATION_STATE;
	पूर्ण

	data->delay_buf[SSP_BIO_HRM_LIB] = 100;

	data->समय_syncing = true;

	mutex_init(&data->pending_lock);
	INIT_LIST_HEAD(&data->pending_list);

	atomic_set(&data->enable_refcount, 0);

	INIT_WORK(&data->work_wdt, ssp_wdt_work_func);
	INIT_DELAYED_WORK(&data->work_refresh, ssp_refresh_task);

	समयr_setup(&data->wdt_समयr, ssp_wdt_समयr_func, 0);

	ret = request_thपढ़ोed_irq(data->spi->irq, शून्य,
				   ssp_irq_thपढ़ो_fn,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "SSP_Int", data);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Irq request fail\n");
		जाओ err_setup_irq;
	पूर्ण

	/* Let's start with enabled one so irq balance could be ok */
	data->shut_करोwn = false;

	/* just to aव्योम unbalanced irq set wake up */
	enable_irq_wake(data->spi->irq);

	data->fw_dl_state = ssp_check_fwbl(data);
	अगर (data->fw_dl_state == SSP_FW_DL_STATE_NONE) अणु
		ret = ssp_initialize_mcu(data);
		अगर (ret < 0) अणु
			dev_err(&spi->dev, "Initialize_mcu failed\n");
			जाओ err_पढ़ो_reg;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "Firmware version not supported\n");
		ret = -EPERM;
		जाओ err_पढ़ो_reg;
	पूर्ण

	वापस 0;

err_पढ़ो_reg:
	मुक्त_irq(data->spi->irq, data);
err_setup_irq:
	mutex_destroy(&data->pending_lock);
	mutex_destroy(&data->comm_lock);

	dev_err(&spi->dev, "Probe failed!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ssp_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ssp_data *data = spi_get_drvdata(spi);

	अगर (ssp_command(data, SSP_MSG2SSP_AP_STATUS_SHUTDOWN, 0) < 0)
		dev_err(&data->spi->dev,
			"SSP_MSG2SSP_AP_STATUS_SHUTDOWN failed\n");

	ssp_enable_mcu(data, false);
	ssp_disable_wdt_समयr(data);

	ssp_clean_pending_list(data);

	मुक्त_irq(data->spi->irq, data);

	del_समयr_sync(&data->wdt_समयr);
	cancel_work_sync(&data->work_wdt);

	mutex_destroy(&data->comm_lock);
	mutex_destroy(&data->pending_lock);

	mfd_हटाओ_devices(&spi->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ssp_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ssp_data *data = spi_get_drvdata(to_spi_device(dev));

	data->last_resume_state = SSP_MSG2SSP_AP_STATUS_SUSPEND;

	अगर (atomic_पढ़ो(&data->enable_refcount) > 0)
		ssp_disable_wdt_समयr(data);

	ret = ssp_command(data, SSP_MSG2SSP_AP_STATUS_SUSPEND, 0);
	अगर (ret < 0) अणु
		dev_err(&data->spi->dev,
			"%s SSP_MSG2SSP_AP_STATUS_SUSPEND failed\n", __func__);

		ssp_enable_wdt_समयr(data);
		वापस ret;
	पूर्ण

	data->समय_syncing = false;
	disable_irq(data->spi->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक ssp_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ssp_data *data = spi_get_drvdata(to_spi_device(dev));

	enable_irq(data->spi->irq);

	अगर (atomic_पढ़ो(&data->enable_refcount) > 0)
		ssp_enable_wdt_समयr(data);

	ret = ssp_command(data, SSP_MSG2SSP_AP_STATUS_RESUME, 0);
	अगर (ret < 0) अणु
		dev_err(&data->spi->dev,
			"%s SSP_MSG2SSP_AP_STATUS_RESUME failed\n", __func__);
		ssp_disable_wdt_समयr(data);
		वापस ret;
	पूर्ण

	/* बारyncing is set by MCU */
	data->last_resume_state = SSP_MSG2SSP_AP_STATUS_RESUME;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops ssp_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ssp_suspend, ssp_resume)
पूर्ण;

अटल काष्ठा spi_driver ssp_driver = अणु
	.probe = ssp_probe,
	.हटाओ = ssp_हटाओ,
	.driver = अणु
		.pm = &ssp_pm_ops,
		.of_match_table = of_match_ptr(ssp_of_match),
		.name = "sensorhub"
	पूर्ण,
पूर्ण;

module_spi_driver(ssp_driver);

MODULE_DESCRIPTION("ssp sensorhub driver");
MODULE_AUTHOR("Samsung Electronics");
MODULE_LICENSE("GPL");
