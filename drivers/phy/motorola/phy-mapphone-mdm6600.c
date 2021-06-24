<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Motorola Mapphone MDM6600 modem GPIO controlled USB PHY driver
 * Copyright (C) 2018 Tony Lindgren <tony@atomide.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा PHY_MDM6600_PHY_DELAY_MS	4000	/* PHY enable 2.2s to 3.5s */
#घोषणा PHY_MDM6600_ENABLED_DELAY_MS	8000	/* 8s more total क्रम MDM6600 */
#घोषणा PHY_MDM6600_WAKE_KICK_MS	600	/* समय on after GPIO toggle */
#घोषणा MDM6600_MODEM_IDLE_DELAY_MS	1000	/* modem after USB suspend */
#घोषणा MDM6600_MODEM_WAKE_DELAY_MS	200	/* modem response after idle */

क्रमागत phy_mdm6600_ctrl_lines अणु
	PHY_MDM6600_ENABLE,			/* USB PHY enable */
	PHY_MDM6600_POWER,			/* Device घातer */
	PHY_MDM6600_RESET,			/* Device reset */
	PHY_MDM6600_NR_CTRL_LINES,
पूर्ण;

क्रमागत phy_mdm6600_booपंचांगode_lines अणु
	PHY_MDM6600_MODE0,			/* out USB mode0 and OOB wake */
	PHY_MDM6600_MODE1,			/* out USB mode1, in OOB wake */
	PHY_MDM6600_NR_MODE_LINES,
पूर्ण;

क्रमागत phy_mdm6600_cmd_lines अणु
	PHY_MDM6600_CMD0,
	PHY_MDM6600_CMD1,
	PHY_MDM6600_CMD2,
	PHY_MDM6600_NR_CMD_LINES,
पूर्ण;

क्रमागत phy_mdm6600_status_lines अणु
	PHY_MDM6600_STATUS0,
	PHY_MDM6600_STATUS1,
	PHY_MDM6600_STATUS2,
	PHY_MDM6600_NR_STATUS_LINES,
पूर्ण;

/*
 * MDM6600 command codes. These are based on Motorola Mapphone Linux
 * kernel tree.
 */
क्रमागत phy_mdm6600_cmd अणु
	PHY_MDM6600_CMD_BP_PANIC_ACK,
	PHY_MDM6600_CMD_DATA_ONLY_BYPASS,	/* Reroute USB to CPCAP PHY */
	PHY_MDM6600_CMD_FULL_BYPASS,		/* Reroute USB to CPCAP PHY */
	PHY_MDM6600_CMD_NO_BYPASS,		/* Request normal USB mode */
	PHY_MDM6600_CMD_BP_SHUTDOWN_REQ,	/* Request device घातer off */
	PHY_MDM6600_CMD_BP_UNKNOWN_5,
	PHY_MDM6600_CMD_BP_UNKNOWN_6,
	PHY_MDM6600_CMD_UNDEFINED,
पूर्ण;

/*
 * MDM6600 status codes. These are based on Motorola Mapphone Linux
 * kernel tree.
 */
क्रमागत phy_mdm6600_status अणु
	PHY_MDM6600_STATUS_PANIC,		/* Seems to be really off */
	PHY_MDM6600_STATUS_PANIC_BUSY_WAIT,
	PHY_MDM6600_STATUS_QC_DLOAD,
	PHY_MDM6600_STATUS_RAM_DOWNLOADER,	/* MDM6600 USB flashing mode */
	PHY_MDM6600_STATUS_PHONE_CODE_AWAKE,	/* MDM6600 normal USB mode */
	PHY_MDM6600_STATUS_PHONE_CODE_ASLEEP,
	PHY_MDM6600_STATUS_SHUTDOWN_ACK,
	PHY_MDM6600_STATUS_UNDEFINED,
पूर्ण;

अटल स्थिर अक्षर * स्थिर
phy_mdm6600_status_name[] = अणु
	"off", "busy", "qc_dl", "ram_dl", "awake",
	"asleep", "shutdown", "undefined",
पूर्ण;

काष्ठा phy_mdm6600 अणु
	काष्ठा device *dev;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा gpio_desc *ctrl_gpios[PHY_MDM6600_NR_CTRL_LINES];
	काष्ठा gpio_descs *mode_gpios;
	काष्ठा gpio_descs *status_gpios;
	काष्ठा gpio_descs *cmd_gpios;
	काष्ठा delayed_work bootup_work;
	काष्ठा delayed_work status_work;
	काष्ठा delayed_work modem_wake_work;
	काष्ठा completion ack;
	bool enabled;				/* mdm6600 phy enabled */
	bool running;				/* mdm6600 boot करोne */
	bool awake;				/* mdm6600 respnds on n_gsm */
	पूर्णांक status;
पूर्ण;

अटल पूर्णांक phy_mdm6600_init(काष्ठा phy *x)
अणु
	काष्ठा phy_mdm6600 *ddata = phy_get_drvdata(x);
	काष्ठा gpio_desc *enable_gpio = ddata->ctrl_gpios[PHY_MDM6600_ENABLE];

	अगर (!ddata->enabled)
		वापस -EPROBE_DEFER;

	gpiod_set_value_cansleep(enable_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_mdm6600_घातer_on(काष्ठा phy *x)
अणु
	काष्ठा phy_mdm6600 *ddata = phy_get_drvdata(x);
	काष्ठा gpio_desc *enable_gpio = ddata->ctrl_gpios[PHY_MDM6600_ENABLE];
	पूर्णांक error;

	अगर (!ddata->enabled)
		वापस -ENODEV;

	error = pinctrl_pm_select_शेष_state(ddata->dev);
	अगर (error)
		dev_warn(ddata->dev, "%s: error with default_state: %i\n",
			 __func__, error);

	gpiod_set_value_cansleep(enable_gpio, 1);

	/* Allow aggressive PM क्रम USB, it's only needed क्रम n_gsm port */
	अगर (pm_runसमय_enabled(&x->dev))
		phy_pm_runसमय_put(x);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_mdm6600_घातer_off(काष्ठा phy *x)
अणु
	काष्ठा phy_mdm6600 *ddata = phy_get_drvdata(x);
	काष्ठा gpio_desc *enable_gpio = ddata->ctrl_gpios[PHY_MDM6600_ENABLE];
	पूर्णांक error;

	अगर (!ddata->enabled)
		वापस -ENODEV;

	/* Paired with phy_pm_runसमय_put() in phy_mdm6600_घातer_on() */
	अगर (pm_runसमय_enabled(&x->dev)) अणु
		error = phy_pm_runसमय_get(x);
		अगर (error < 0 && error != -EINPROGRESS)
			dev_warn(ddata->dev, "%s: phy_pm_runtime_get: %i\n",
				 __func__, error);
	पूर्ण

	gpiod_set_value_cansleep(enable_gpio, 0);

	error = pinctrl_pm_select_sleep_state(ddata->dev);
	अगर (error)
		dev_warn(ddata->dev, "%s: error with sleep_state: %i\n",
			 __func__, error);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops gpio_usb_ops = अणु
	.init = phy_mdm6600_init,
	.घातer_on = phy_mdm6600_घातer_on,
	.घातer_off = phy_mdm6600_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * phy_mdm6600_cmd() - send a command request to mdm6600
 * @ddata: device driver data
 * @val: value of cmd to be set
 *
 * Configures the three command request GPIOs to the specअगरied value.
 */
अटल व्योम phy_mdm6600_cmd(काष्ठा phy_mdm6600 *ddata, पूर्णांक val)
अणु
	DECLARE_BITMAP(values, PHY_MDM6600_NR_CMD_LINES);

	values[0] = val;

	gpiod_set_array_value_cansleep(PHY_MDM6600_NR_CMD_LINES,
				       ddata->cmd_gpios->desc,
				       ddata->cmd_gpios->info, values);
पूर्ण

/**
 * phy_mdm6600_status() - पढ़ो mdm6600 status lines
 * @work: work काष्ठाure
 */
अटल व्योम phy_mdm6600_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा phy_mdm6600 *ddata;
	काष्ठा device *dev;
	DECLARE_BITMAP(values, PHY_MDM6600_NR_STATUS_LINES);
	पूर्णांक error;

	ddata = container_of(work, काष्ठा phy_mdm6600, status_work.work);
	dev = ddata->dev;

	error = gpiod_get_array_value_cansleep(PHY_MDM6600_NR_STATUS_LINES,
					       ddata->status_gpios->desc,
					       ddata->status_gpios->info,
					       values);
	अगर (error)
		वापस;

	ddata->status = values[0] & ((1 << PHY_MDM6600_NR_STATUS_LINES) - 1);

	dev_info(dev, "modem status: %i %s\n",
		 ddata->status,
		 phy_mdm6600_status_name[ddata->status]);
	complete(&ddata->ack);
पूर्ण

अटल irqवापस_t phy_mdm6600_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा phy_mdm6600 *ddata = data;

	schedule_delayed_work(&ddata->status_work, msecs_to_jअगरfies(10));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * phy_mdm6600_wakeirq_thपढ़ो - handle mode1 line OOB wake after booting
 * @irq: पूर्णांकerrupt
 * @data: पूर्णांकerrupt handler data
 *
 * GPIO mode1 is used initially as output to configure the USB boot
 * mode क्रम mdm6600. After booting it is used as input क्रम OOB wake
 * संकेत from mdm6600 to the SoC. Just use it क्रम debug info only
 * क्रम now.
 */
अटल irqवापस_t phy_mdm6600_wakeirq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा phy_mdm6600 *ddata = data;
	काष्ठा gpio_desc *mode_gpio1;
	पूर्णांक error, wakeup;

	mode_gpio1 = ddata->mode_gpios->desc[PHY_MDM6600_MODE1];
	wakeup = gpiod_get_value(mode_gpio1);
	अगर (!wakeup)
		वापस IRQ_NONE;

	dev_dbg(ddata->dev, "OOB wake on mode_gpio1: %i\n", wakeup);
	error = pm_runसमय_get_sync(ddata->dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(ddata->dev);

		वापस IRQ_NONE;
	पूर्ण

	/* Just wake-up and kick the स्वतःsuspend समयr */
	pm_runसमय_mark_last_busy(ddata->dev);
	pm_runसमय_put_स्वतःsuspend(ddata->dev);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * phy_mdm6600_init_irq() - initialize mdm6600 status IRQ lines
 * @ddata: device driver data
 */
अटल व्योम phy_mdm6600_init_irq(काष्ठा phy_mdm6600 *ddata)
अणु
	काष्ठा device *dev = ddata->dev;
	पूर्णांक i, error, irq;

	क्रम (i = PHY_MDM6600_STATUS0;
	     i <= PHY_MDM6600_STATUS2; i++) अणु
		काष्ठा gpio_desc *gpio = ddata->status_gpios->desc[i];

		irq = gpiod_to_irq(gpio);
		अगर (irq <= 0)
			जारी;

		error = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					phy_mdm6600_irq_thपढ़ो,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING |
					IRQF_ONESHOT,
					"mdm6600",
					ddata);
		अगर (error)
			dev_warn(dev, "no modem status irq%i: %i\n",
				 irq, error);
	पूर्ण
पूर्ण

काष्ठा phy_mdm6600_map अणु
	स्थिर अक्षर *name;
	पूर्णांक direction;
पूर्ण;

अटल स्थिर काष्ठा phy_mdm6600_map
phy_mdm6600_ctrl_gpio_map[PHY_MDM6600_NR_CTRL_LINES] = अणु
	अणु "enable", GPIOD_OUT_LOW, पूर्ण,		/* low = phy disabled */
	अणु "power", GPIOD_OUT_LOW, पूर्ण,		/* low = off */
	अणु "reset", GPIOD_OUT_HIGH, पूर्ण,		/* high = reset */
पूर्ण;

/**
 * phy_mdm6600_init_lines() - initialize mdm6600 GPIO lines
 * @ddata: device driver data
 */
अटल पूर्णांक phy_mdm6600_init_lines(काष्ठा phy_mdm6600 *ddata)
अणु
	काष्ठा device *dev = ddata->dev;
	पूर्णांक i;

	/* MDM6600 control lines */
	क्रम (i = 0; i < ARRAY_SIZE(phy_mdm6600_ctrl_gpio_map); i++) अणु
		स्थिर काष्ठा phy_mdm6600_map *map =
			&phy_mdm6600_ctrl_gpio_map[i];
		काष्ठा gpio_desc **gpio = &ddata->ctrl_gpios[i];

		*gpio = devm_gpiod_get(dev, map->name, map->direction);
		अगर (IS_ERR(*gpio)) अणु
			dev_info(dev, "gpio %s error %li\n",
				 map->name, PTR_ERR(*gpio));
			वापस PTR_ERR(*gpio);
		पूर्ण
	पूर्ण

	/* MDM6600 USB start-up mode output lines */
	ddata->mode_gpios = devm_gpiod_get_array(dev, "motorola,mode",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->mode_gpios))
		वापस PTR_ERR(ddata->mode_gpios);

	अगर (ddata->mode_gpios->ndescs != PHY_MDM6600_NR_MODE_LINES)
		वापस -EINVAL;

	/* MDM6600 status input lines */
	ddata->status_gpios = devm_gpiod_get_array(dev, "motorola,status",
						   GPIOD_IN);
	अगर (IS_ERR(ddata->status_gpios))
		वापस PTR_ERR(ddata->status_gpios);

	अगर (ddata->status_gpios->ndescs != PHY_MDM6600_NR_STATUS_LINES)
		वापस -EINVAL;

	/* MDM6600 cmd output lines */
	ddata->cmd_gpios = devm_gpiod_get_array(dev, "motorola,cmd",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->cmd_gpios))
		वापस PTR_ERR(ddata->cmd_gpios);

	अगर (ddata->cmd_gpios->ndescs != PHY_MDM6600_NR_CMD_LINES)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * phy_mdm6600_device_घातer_on() - घातer on mdm6600 device
 * @ddata: device driver data
 *
 * To get the पूर्णांकegrated USB phy in MDM6600 takes some hoops. We must ensure
 * the shared USB booपंचांगode GPIOs are configured, then request modem start-up,
 * reset and घातer-up.. And then we need to recycle the shared USB booपंचांगode
 * GPIOs as they are also used क्रम Out of Band (OOB) wake क्रम the USB and
 * TS 27.010 serial mux.
 */
अटल पूर्णांक phy_mdm6600_device_घातer_on(काष्ठा phy_mdm6600 *ddata)
अणु
	काष्ठा gpio_desc *mode_gpio0, *mode_gpio1, *reset_gpio, *घातer_gpio;
	पूर्णांक error = 0, wakeirq;

	mode_gpio0 = ddata->mode_gpios->desc[PHY_MDM6600_MODE0];
	mode_gpio1 = ddata->mode_gpios->desc[PHY_MDM6600_MODE1];
	reset_gpio = ddata->ctrl_gpios[PHY_MDM6600_RESET];
	घातer_gpio = ddata->ctrl_gpios[PHY_MDM6600_POWER];

	/*
	 * Shared GPIOs must be low क्रम normal USB mode. After booting
	 * they are used क्रम OOB wake संकेतing. These can be also used
	 * to configure USB flashing mode later on based on a module
	 * parameter.
	 */
	gpiod_set_value_cansleep(mode_gpio0, 0);
	gpiod_set_value_cansleep(mode_gpio1, 0);

	/* Request start-up mode */
	phy_mdm6600_cmd(ddata, PHY_MDM6600_CMD_NO_BYPASS);

	/* Request a reset first */
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(100);

	/* Toggle घातer GPIO to request mdm6600 to start */
	gpiod_set_value_cansleep(घातer_gpio, 1);
	msleep(100);
	gpiod_set_value_cansleep(घातer_gpio, 0);

	/*
	 * Looks like the USB PHY needs between 2.2 to 4 seconds.
	 * If we try to use it beक्रमe that, we will get L3 errors
	 * from omap-usb-host trying to access the PHY. See also
	 * phy_mdm6600_init() क्रम -EPROBE_DEFER.
	 */
	msleep(PHY_MDM6600_PHY_DELAY_MS);
	ddata->enabled = true;

	/* Booting up the rest of MDM6600 will take total about 8 seconds */
	dev_info(ddata->dev, "Waiting for power up request to complete..\n");
	अगर (रुको_क्रम_completion_समयout(&ddata->ack,
			msecs_to_jअगरfies(PHY_MDM6600_ENABLED_DELAY_MS))) अणु
		अगर (ddata->status > PHY_MDM6600_STATUS_PANIC &&
		    ddata->status < PHY_MDM6600_STATUS_SHUTDOWN_ACK)
			dev_info(ddata->dev, "Powered up OK\n");
	पूर्ण अन्यथा अणु
		ddata->enabled = false;
		error = -ETIMEDOUT;
		dev_err(ddata->dev, "Timed out powering up\n");
	पूर्ण

	/* Reconfigure mode1 GPIO as input क्रम OOB wake */
	gpiod_direction_input(mode_gpio1);

	wakeirq = gpiod_to_irq(mode_gpio1);
	अगर (wakeirq <= 0)
		वापस wakeirq;

	error = devm_request_thपढ़ोed_irq(ddata->dev, wakeirq, शून्य,
					  phy_mdm6600_wakeirq_thपढ़ो,
					  IRQF_TRIGGER_RISING |
					  IRQF_TRIGGER_FALLING |
					  IRQF_ONESHOT,
					  "mdm6600-wake",
					  ddata);
	अगर (error)
		dev_warn(ddata->dev, "no modem wakeirq irq%i: %i\n",
			 wakeirq, error);

	ddata->running = true;

	वापस error;
पूर्ण

/**
 * phy_mdm6600_device_घातer_off() - घातer off mdm6600 device
 * @ddata: device driver data
 */
अटल व्योम phy_mdm6600_device_घातer_off(काष्ठा phy_mdm6600 *ddata)
अणु
	काष्ठा gpio_desc *reset_gpio =
		ddata->ctrl_gpios[PHY_MDM6600_RESET];

	ddata->enabled = false;
	phy_mdm6600_cmd(ddata, PHY_MDM6600_CMD_BP_SHUTDOWN_REQ);
	msleep(100);

	gpiod_set_value_cansleep(reset_gpio, 1);

	dev_info(ddata->dev, "Waiting for power down request to complete.. ");
	अगर (रुको_क्रम_completion_समयout(&ddata->ack,
					msecs_to_jअगरfies(5000))) अणु
		अगर (ddata->status == PHY_MDM6600_STATUS_PANIC)
			dev_info(ddata->dev, "Powered down OK\n");
	पूर्ण अन्यथा अणु
		dev_err(ddata->dev, "Timed out powering down\n");
	पूर्ण
पूर्ण

अटल व्योम phy_mdm6600_deferred_घातer_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा phy_mdm6600 *ddata;
	पूर्णांक error;

	ddata = container_of(work, काष्ठा phy_mdm6600, bootup_work.work);

	error = phy_mdm6600_device_घातer_on(ddata);
	अगर (error)
		dev_err(ddata->dev, "Device not functional\n");
पूर्ण

/*
 * USB suspend माला_दो mdm6600 पूर्णांकo low घातer mode. For any n_gsm using apps,
 * we need to keep the modem awake by kicking it's mode0 GPIO. This will
 * keep the modem awake क्रम about 1.2 seconds. When no n_gsm apps are using
 * the modem, runसमय PM स्वतः mode can be enabled so modem can enter low
 * घातer mode.
 */
अटल व्योम phy_mdm6600_wake_modem(काष्ठा phy_mdm6600 *ddata)
अणु
	काष्ठा gpio_desc *mode_gpio0;

	mode_gpio0 = ddata->mode_gpios->desc[PHY_MDM6600_MODE0];
	gpiod_set_value_cansleep(mode_gpio0, 1);
	usleep_range(5, 15);
	gpiod_set_value_cansleep(mode_gpio0, 0);
	अगर (ddata->awake)
		usleep_range(5, 15);
	अन्यथा
		msleep(MDM6600_MODEM_WAKE_DELAY_MS);
पूर्ण

अटल व्योम phy_mdm6600_modem_wake(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा phy_mdm6600 *ddata;

	ddata = container_of(work, काष्ठा phy_mdm6600, modem_wake_work.work);
	phy_mdm6600_wake_modem(ddata);

	/*
	 * The modem करोes not always stay awake 1.2 seconds after toggling
	 * the wake GPIO, and someबार it idles after about some 600 ms
	 * making ग_लिखोs समय out.
	 */
	schedule_delayed_work(&ddata->modem_wake_work,
			      msecs_to_jअगरfies(PHY_MDM6600_WAKE_KICK_MS));
पूर्ण

अटल पूर्णांक __maybe_unused phy_mdm6600_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा phy_mdm6600 *ddata = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&ddata->modem_wake_work);
	ddata->awake = false;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused phy_mdm6600_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा phy_mdm6600 *ddata = dev_get_drvdata(dev);

	phy_mdm6600_modem_wake(&ddata->modem_wake_work.work);
	ddata->awake = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops phy_mdm6600_pm_ops = अणु
	SET_RUNTIME_PM_OPS(phy_mdm6600_runसमय_suspend,
			   phy_mdm6600_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id phy_mdm6600_id_table[] = अणु
	अणु .compatible = "motorola,mapphone-mdm6600", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_mdm6600_id_table);

अटल पूर्णांक phy_mdm6600_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_mdm6600 *ddata;
	पूर्णांक error;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&ddata->bootup_work,
			  phy_mdm6600_deferred_घातer_on);
	INIT_DELAYED_WORK(&ddata->status_work, phy_mdm6600_status);
	INIT_DELAYED_WORK(&ddata->modem_wake_work, phy_mdm6600_modem_wake);
	init_completion(&ddata->ack);

	ddata->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ddata);

	/* Active state selected in phy_mdm6600_घातer_on() */
	error = pinctrl_pm_select_sleep_state(ddata->dev);
	अगर (error)
		dev_warn(ddata->dev, "%s: error with sleep_state: %i\n",
			 __func__, error);

	error = phy_mdm6600_init_lines(ddata);
	अगर (error)
		वापस error;

	phy_mdm6600_init_irq(ddata);
	schedule_delayed_work(&ddata->bootup_work, 0);

	/*
	 * See phy_mdm6600_device_घातer_on(). We should be able
	 * to हटाओ this eventually when ohci-platक्रमm can deal
	 * with -EPROBE_DEFER.
	 */
	msleep(PHY_MDM6600_PHY_DELAY_MS + 500);

	/*
	 * Enable PM runसमय only after PHY has been घातered up properly.
	 * It is currently only needed after USB suspends mdm6600 and n_gsm
	 * needs to access the device. We करोn't want to करो this earlier as
	 * gpio mode0 pin द्विगुनs as mdm6600 wake-up gpio.
	 */
	pm_runसमय_use_स्वतःsuspend(ddata->dev);
	pm_runसमय_set_स्वतःsuspend_delay(ddata->dev,
					 MDM6600_MODEM_IDLE_DELAY_MS);
	pm_runसमय_enable(ddata->dev);
	error = pm_runसमय_get_sync(ddata->dev);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "failed to wake modem: %i\n", error);
		pm_runसमय_put_noidle(ddata->dev);
		जाओ cleanup;
	पूर्ण

	ddata->generic_phy = devm_phy_create(ddata->dev, शून्य, &gpio_usb_ops);
	अगर (IS_ERR(ddata->generic_phy)) अणु
		error = PTR_ERR(ddata->generic_phy);
		जाओ idle;
	पूर्ण

	phy_set_drvdata(ddata->generic_phy, ddata);

	ddata->phy_provider =
		devm_of_phy_provider_रेजिस्टर(ddata->dev,
					      of_phy_simple_xlate);
	अगर (IS_ERR(ddata->phy_provider))
		error = PTR_ERR(ddata->phy_provider);

idle:
	pm_runसमय_mark_last_busy(ddata->dev);
	pm_runसमय_put_स्वतःsuspend(ddata->dev);

cleanup:
	अगर (error < 0)
		phy_mdm6600_device_घातer_off(ddata);

	वापस error;
पूर्ण

अटल पूर्णांक phy_mdm6600_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_mdm6600 *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा gpio_desc *reset_gpio = ddata->ctrl_gpios[PHY_MDM6600_RESET];

	pm_runसमय_करोnt_use_स्वतःsuspend(ddata->dev);
	pm_runसमय_put_sync(ddata->dev);
	pm_runसमय_disable(ddata->dev);

	अगर (!ddata->running)
		रुको_क्रम_completion_समयout(&ddata->ack,
			msecs_to_jअगरfies(PHY_MDM6600_ENABLED_DELAY_MS));

	gpiod_set_value_cansleep(reset_gpio, 1);
	phy_mdm6600_device_घातer_off(ddata);

	cancel_delayed_work_sync(&ddata->modem_wake_work);
	cancel_delayed_work_sync(&ddata->bootup_work);
	cancel_delayed_work_sync(&ddata->status_work);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver phy_mdm6600_driver = अणु
	.probe = phy_mdm6600_probe,
	.हटाओ = phy_mdm6600_हटाओ,
	.driver = अणु
		.name = "phy-mapphone-mdm6600",
		.pm = &phy_mdm6600_pm_ops,
		.of_match_table = of_match_ptr(phy_mdm6600_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(phy_mdm6600_driver);

MODULE_ALIAS("platform:gpio_usb");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("mdm6600 gpio usb phy driver");
MODULE_LICENSE("GPL v2");
