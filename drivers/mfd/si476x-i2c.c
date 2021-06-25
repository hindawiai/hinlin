<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mfd/si476x-i2c.c -- Core device driver क्रम si476x MFD
 * device
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */
#समावेश <linux/module.h>

#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/si476x-core.h>

#घोषणा SI476X_MAX_IO_ERRORS		10
#घोषणा SI476X_DRIVER_RDS_FIFO_DEPTH	128

/**
 * si476x_core_config_pinmux() - pin function configuration function
 *
 * @core: Core device काष्ठाure
 *
 * Configure the functions of the pins of the radio chip.
 *
 * The function वापसs zero in हाल of succes or negative error code
 * otherwise.
 */
अटल पूर्णांक si476x_core_config_pinmux(काष्ठा si476x_core *core)
अणु
	पूर्णांक err;
	dev_dbg(&core->client->dev, "Configuring pinmux\n");
	err = si476x_core_cmd_dig_audio_pin_cfg(core,
						core->pinmux.dclk,
						core->pinmux.dfs,
						core->pinmux.करोut,
						core->pinmux.xout);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure digital audio pins(err = %d)\n",
			err);
		वापस err;
	पूर्ण

	err = si476x_core_cmd_zअगर_pin_cfg(core,
					  core->pinmux.iqclk,
					  core->pinmux.iqfs,
					  core->pinmux.iout,
					  core->pinmux.qout);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure ZIF pins(err = %d)\n",
			err);
		वापस err;
	पूर्ण

	err = si476x_core_cmd_ic_link_gpo_ctl_pin_cfg(core,
						      core->pinmux.icin,
						      core->pinmux.icip,
						      core->pinmux.icon,
						      core->pinmux.icop);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure IC-Link/GPO pins(err = %d)\n",
			err);
		वापस err;
	पूर्ण

	err = si476x_core_cmd_ana_audio_pin_cfg(core,
						core->pinmux.lrout);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure analog audio pins(err = %d)\n",
			err);
		वापस err;
	पूर्ण

	err = si476x_core_cmd_पूर्णांकb_pin_cfg(core,
					   core->pinmux.पूर्णांकb,
					   core->pinmux.a1);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure interrupt pins(err = %d)\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम si476x_core_schedule_polling_work(काष्ठा si476x_core *core)
अणु
	schedule_delayed_work(&core->status_monitor,
			      usecs_to_jअगरfies(SI476X_STATUS_POLL_US));
पूर्ण

/**
 * si476x_core_start() - early chip startup function
 * @core: Core device काष्ठाure
 * @soft: When set, this flag क्रमces "soft" startup, where "soft"
 * घातer करोwn is the one करोne by sending appropriate command instead
 * of using reset pin of the tuner
 *
 * Perक्रमm required startup sequence to correctly घातer
 * up the chip and perक्रमm initial configuration. It करोes the
 * following sequence of actions:
 *       1. Claims and enables the घातer supplies VD and VIO1 required
 *          क्रम I2C पूर्णांकerface of the chip operation.
 *       2. Waits क्रम 100us, pulls the reset line up, enables irq,
 *          रुकोs क्रम another 100us as it is specअगरied by the
 *          datasheet.
 *       3. Sends 'POWER_UP' command to the device with all provided
 *          inक्रमmation about घातer-up parameters.
 *       4. Configures, pin multiplexor, disables digital audio and
 *          configures पूर्णांकerrupt sources.
 *
 * The function वापसs zero in हाल of succes or negative error code
 * otherwise.
 */
पूर्णांक si476x_core_start(काष्ठा si476x_core *core, bool soft)
अणु
	काष्ठा i2c_client *client = core->client;
	पूर्णांक err;

	अगर (!soft) अणु
		अगर (gpio_is_valid(core->gpio_reset))
			gpio_set_value_cansleep(core->gpio_reset, 1);

		अगर (client->irq)
			enable_irq(client->irq);

		udelay(100);

		अगर (!client->irq) अणु
			atomic_set(&core->is_alive, 1);
			si476x_core_schedule_polling_work(core);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (client->irq)
			enable_irq(client->irq);
		अन्यथा अणु
			atomic_set(&core->is_alive, 1);
			si476x_core_schedule_polling_work(core);
		पूर्ण
	पूर्ण

	err = si476x_core_cmd_घातer_up(core,
				       &core->घातer_up_parameters);

	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Power up failure(err = %d)\n",
			err);
		जाओ disable_irq;
	पूर्ण

	अगर (client->irq)
		atomic_set(&core->is_alive, 1);

	err = si476x_core_config_pinmux(core);
	अगर (err < 0) अणु
		dev_err(&core->client->dev,
			"Failed to configure pinmux(err = %d)\n",
			err);
		जाओ disable_irq;
	पूर्ण

	अगर (client->irq) अणु
		err = regmap_ग_लिखो(core->regmap,
				   SI476X_PROP_INT_CTL_ENABLE,
				   SI476X_RDSIEN |
				   SI476X_STCIEN |
				   SI476X_CTSIEN);
		अगर (err < 0) अणु
			dev_err(&core->client->dev,
				"Failed to configure interrupt sources"
				"(err = %d)\n", err);
			जाओ disable_irq;
		पूर्ण
	पूर्ण

	वापस 0;

disable_irq:
	अगर (err == -ENODEV)
		atomic_set(&core->is_alive, 0);

	अगर (client->irq)
		disable_irq(client->irq);
	अन्यथा
		cancel_delayed_work_sync(&core->status_monitor);

	अगर (gpio_is_valid(core->gpio_reset))
		gpio_set_value_cansleep(core->gpio_reset, 0);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_start);

/**
 * si476x_core_stop() - chip घातer-करोwn function
 * @core: Core device काष्ठाure
 * @soft: When set, function sends a POWER_DOWN command instead of
 * bringing reset line low
 *
 * Power करोwn the chip by perक्रमming following actions:
 * 1. Disable IRQ or stop the polling worker
 * 2. Send the POWER_DOWN command अगर the घातer करोwn is soft or bring
 *    reset line low अगर not.
 *
 * The function वापसs zero in हाल of succes or negative error code
 * otherwise.
 */
पूर्णांक si476x_core_stop(काष्ठा si476x_core *core, bool soft)
अणु
	पूर्णांक err = 0;
	atomic_set(&core->is_alive, 0);

	अगर (soft) अणु
		/* TODO: This probably shoud be a configurable option,
		 * so it is possible to have the chips keep their
		 * oscillators running
		 */
		काष्ठा si476x_घातer_करोwn_args args = अणु
			.xosc = false,
		पूर्ण;
		err = si476x_core_cmd_घातer_करोwn(core, &args);
	पूर्ण

	/* We couldn't disable those beक्रमe
	 * 'si476x_core_cmd_power_down' since we expect to get CTS
	 * पूर्णांकerrupt */
	अगर (core->client->irq)
		disable_irq(core->client->irq);
	अन्यथा
		cancel_delayed_work_sync(&core->status_monitor);

	अगर (!soft) अणु
		अगर (gpio_is_valid(core->gpio_reset))
			gpio_set_value_cansleep(core->gpio_reset, 0);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_stop);

/**
 * si476x_core_set_घातer_state() - set the level at which the घातer is
 * supplied क्रम the chip.
 * @core: Core device काष्ठाure
 * @next_state: क्रमागत si476x_घातer_state describing घातer state to
 *              चयन to.
 *
 * Switch on all the required घातer supplies
 *
 * This function वापसs 0 in हाल of suvccess and negative error code
 * otherwise.
 */
पूर्णांक si476x_core_set_घातer_state(काष्ठा si476x_core *core,
				क्रमागत si476x_घातer_state next_state)
अणु
	/*
	   It is not clear क्रमm the datasheet अगर it is possible to
	   work with device अगर not all घातer करोमुख्यs are operational.
	   So क्रम now the घातer-up policy is "power-up all the things!"
	 */
	पूर्णांक err = 0;

	अगर (core->घातer_state == SI476X_POWER_INCONSISTENT) अणु
		dev_err(&core->client->dev,
			"The device in inconsistent power state\n");
		वापस -EINVAL;
	पूर्ण

	अगर (next_state != core->घातer_state) अणु
		चयन (next_state) अणु
		हाल SI476X_POWER_UP_FULL:
			err = regulator_bulk_enable(ARRAY_SIZE(core->supplies),
						    core->supplies);
			अगर (err < 0) अणु
				core->घातer_state = SI476X_POWER_INCONSISTENT;
				अवरोध;
			पूर्ण
			/*
			 * Startup timing diagram recommends to have a
			 * 100 us delay between enabling of the घातer
			 * supplies and turning the tuner on.
			 */
			udelay(100);

			err = si476x_core_start(core, false);
			अगर (err < 0)
				जाओ disable_regulators;

			core->घातer_state = next_state;
			अवरोध;

		हाल SI476X_POWER_DOWN:
			core->घातer_state = next_state;
			err = si476x_core_stop(core, false);
			अगर (err < 0)
				core->घातer_state = SI476X_POWER_INCONSISTENT;
disable_regulators:
			err = regulator_bulk_disable(ARRAY_SIZE(core->supplies),
						     core->supplies);
			अगर (err < 0)
				core->घातer_state = SI476X_POWER_INCONSISTENT;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_set_घातer_state);

/**
 * si476x_core_report_drainer_stop() - mark the completion of the RDS
 * buffer drain porcess by the worker.
 *
 * @core: Core device काष्ठाure
 */
अटल अंतरभूत व्योम si476x_core_report_drainer_stop(काष्ठा si476x_core *core)
अणु
	mutex_lock(&core->rds_drainer_status_lock);
	core->rds_drainer_is_working = false;
	mutex_unlock(&core->rds_drainer_status_lock);
पूर्ण

/**
 * si476x_core_start_rds_drainer_once() - start RDS drainer worker अगर
 * ther is none working, करो nothing otherwise
 *
 * @core: Dataकाष्ठाure corresponding to the chip.
 */
अटल अंतरभूत व्योम si476x_core_start_rds_drainer_once(काष्ठा si476x_core *core)
अणु
	mutex_lock(&core->rds_drainer_status_lock);
	अगर (!core->rds_drainer_is_working) अणु
		core->rds_drainer_is_working = true;
		schedule_work(&core->rds_fअगरo_drainer);
	पूर्ण
	mutex_unlock(&core->rds_drainer_status_lock);
पूर्ण
/**
 * si476x_drain_rds_fअगरo() - RDS buffer drainer.
 * @work: काष्ठा work_काष्ठा being ppassed to the function by the
 * kernel.
 *
 * Drain the contents of the RDS FIFO of
 */
अटल व्योम si476x_core_drain_rds_fअगरo(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;

	काष्ठा si476x_core *core = container_of(work, काष्ठा si476x_core,
						rds_fअगरo_drainer);

	काष्ठा si476x_rds_status_report report;

	si476x_core_lock(core);
	err = si476x_core_cmd_fm_rds_status(core, true, false, false, &report);
	अगर (!err) अणु
		पूर्णांक i = report.rdsfअगरoused;
		dev_dbg(&core->client->dev,
			"%d elements in RDS FIFO. Draining.\n", i);
		क्रम (; i > 0; --i) अणु
			err = si476x_core_cmd_fm_rds_status(core, false, false,
							    (i == 1), &report);
			अगर (err < 0)
				जाओ unlock;

			kfअगरo_in(&core->rds_fअगरo, report.rds,
				 माप(report.rds));
			dev_dbg(&core->client->dev, "RDS data:\n %*ph\n",
				(पूर्णांक)माप(report.rds), report.rds);
		पूर्ण
		dev_dbg(&core->client->dev, "Drrrrained!\n");
		wake_up_पूर्णांकerruptible(&core->rds_पढ़ो_queue);
	पूर्ण

unlock:
	si476x_core_unlock(core);
	si476x_core_report_drainer_stop(core);
पूर्ण

/**
 * si476x_core_pronounce_dead()
 *
 * @core: Core device काष्ठाure
 *
 * Mark the device as being dead and wake up all potentially रुकोing
 * thपढ़ोs of execution.
 *
 */
अटल व्योम si476x_core_pronounce_dead(काष्ठा si476x_core *core)
अणु
	dev_info(&core->client->dev, "Core device is dead.\n");

	atomic_set(&core->is_alive, 0);

	/* Wake up al possible रुकोing processes */
	wake_up_पूर्णांकerruptible(&core->rds_पढ़ो_queue);

	atomic_set(&core->cts, 1);
	wake_up(&core->command);

	atomic_set(&core->stc, 1);
	wake_up(&core->tuning);
पूर्ण

/**
 * si476x_core_i2c_xfer()
 *
 * @core: Core device काष्ठाure
 * @type: Transfer type
 * @buf: Transfer buffer क्रम/with data
 * @count: Transfer buffer size
 *
 * Perfrom and I2C transfer(either पढ़ो or ग_लिखो) and keep a counter
 * of I/O errors. If the error counter rises above the threshold
 * pronounce device dead.
 *
 * The function वापसs zero on succes or negative error code on
 * failure.
 */
पूर्णांक si476x_core_i2c_xfer(काष्ठा si476x_core *core,
		    क्रमागत si476x_i2c_type type,
		    अक्षर *buf, पूर्णांक count)
अणु
	अटल पूर्णांक io_errors_count;
	पूर्णांक err;
	अगर (type == SI476X_I2C_SEND)
		err = i2c_master_send(core->client, buf, count);
	अन्यथा
		err = i2c_master_recv(core->client, buf, count);

	अगर (err < 0) अणु
		अगर (io_errors_count++ > SI476X_MAX_IO_ERRORS)
			si476x_core_pronounce_dead(core);
	पूर्ण अन्यथा अणु
		io_errors_count = 0;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_i2c_xfer);

/**
 * si476x_get_status()
 * @core: Core device काष्ठाure
 *
 * Get the status byte of the core device by berक्रमming one byte I2C
 * पढ़ो.
 *
 * The function वापसs a status value or a negative error code on
 * error.
 */
अटल पूर्णांक si476x_core_get_status(काष्ठा si476x_core *core)
अणु
	u8 response;
	पूर्णांक err = si476x_core_i2c_xfer(core, SI476X_I2C_RECV,
				  &response, माप(response));

	वापस (err < 0) ? err : response;
पूर्ण

/**
 * si476x_get_and_संकेत_status() - IRQ dispatcher
 * @core: Core device काष्ठाure
 *
 * Dispatch the arrived पूर्णांकerrupt request based on the value of the
 * status byte reported by the tuner.
 *
 */
अटल व्योम si476x_core_get_and_संकेत_status(काष्ठा si476x_core *core)
अणु
	पूर्णांक status = si476x_core_get_status(core);
	अगर (status < 0) अणु
		dev_err(&core->client->dev, "Failed to get status\n");
		वापस;
	पूर्ण

	अगर (status & SI476X_CTS) अणु
		/* Unक्रमtunately completions could not be used क्रम
		 * संकेतling CTS since this flag cannot be cleared
		 * in status byte, and thereक्रमe once it becomes true
		 * multiple calls to 'complete' would cause the
		 * commands following the current one to be completed
		 * beक्रमe they actually are */
		dev_dbg(&core->client->dev, "[interrupt] CTSINT\n");
		atomic_set(&core->cts, 1);
		wake_up(&core->command);
	पूर्ण

	अगर (status & SI476X_FM_RDS_INT) अणु
		dev_dbg(&core->client->dev, "[interrupt] RDSINT\n");
		si476x_core_start_rds_drainer_once(core);
	पूर्ण

	अगर (status & SI476X_STC_INT) अणु
		dev_dbg(&core->client->dev, "[interrupt] STCINT\n");
		atomic_set(&core->stc, 1);
		wake_up(&core->tuning);
	पूर्ण
पूर्ण

अटल व्योम si476x_core_poll_loop(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा si476x_core *core = SI476X_WORK_TO_CORE(work);

	si476x_core_get_and_संकेत_status(core);

	अगर (atomic_पढ़ो(&core->is_alive))
		si476x_core_schedule_polling_work(core);
पूर्ण

अटल irqवापस_t si476x_core_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा si476x_core *core = dev;

	si476x_core_get_and_संकेत_status(core);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * si476x_firmware_version_to_revision()
 * @core: Core device काष्ठाure
 * @func: Selects the boot function of the device:
 *         *_BOOTLOADER  - Boot loader
 *         *_FM_RECEIVER - FM receiver
 *         *_AM_RECEIVER - AM receiver
 *         *_WB_RECEIVER - Weatherband receiver
 * @major:  Firmware major number
 * @minor1: Firmware first minor number
 * @minor2: Firmware second minor number
 *
 * Convert a chip's firmware version number पूर्णांकo an offset that later
 * will be used to as offset in "vtable" of tuner functions
 *
 * This function वापसs a positive offset in हाल of success and a -1
 * in हाल of failure.
 */
अटल पूर्णांक si476x_core_fwver_to_revision(काष्ठा si476x_core *core,
					 पूर्णांक func, पूर्णांक major,
					 पूर्णांक minor1, पूर्णांक minor2)
अणु
	चयन (func) अणु
	हाल SI476X_FUNC_FM_RECEIVER:
		चयन (major) अणु
		हाल 5:
			वापस SI476X_REVISION_A10;
		हाल 8:
			वापस SI476X_REVISION_A20;
		हाल 10:
			वापस SI476X_REVISION_A30;
		शेष:
			जाओ unknown_revision;
		पूर्ण
	हाल SI476X_FUNC_AM_RECEIVER:
		चयन (major) अणु
		हाल 5:
			वापस SI476X_REVISION_A10;
		हाल 7:
			वापस SI476X_REVISION_A20;
		हाल 9:
			वापस SI476X_REVISION_A30;
		शेष:
			जाओ unknown_revision;
		पूर्ण
	हाल SI476X_FUNC_WB_RECEIVER:
		चयन (major) अणु
		हाल 3:
			वापस SI476X_REVISION_A10;
		हाल 5:
			वापस SI476X_REVISION_A20;
		हाल 7:
			वापस SI476X_REVISION_A30;
		शेष:
			जाओ unknown_revision;
		पूर्ण
	हाल SI476X_FUNC_BOOTLOADER:
	शेष:		/* FALLTHROUGH */
		BUG();
		वापस -1;
	पूर्ण

unknown_revision:
	dev_err(&core->client->dev,
		"Unsupported version of the firmware: %d.%d.%d, "
		"reverting to A10 compatible functions\n",
		major, minor1, minor2);

	वापस SI476X_REVISION_A10;
पूर्ण

/**
 * si476x_get_revision_info()
 * @core: Core device काष्ठाure
 *
 * Get the firmware version number of the device. It is करोne in
 * following three steps:
 *    1. Power-up the device
 *    2. Send the 'FUNC_INFO' command
 *    3. Powering the device करोwn.
 *
 * The function वापस zero on success and a negative error code on
 * failure.
 */
अटल पूर्णांक si476x_core_get_revision_info(काष्ठा si476x_core *core)
अणु
	पूर्णांक rval;
	काष्ठा si476x_func_info info;

	si476x_core_lock(core);
	rval = si476x_core_set_घातer_state(core, SI476X_POWER_UP_FULL);
	अगर (rval < 0)
		जाओ निकास;

	rval = si476x_core_cmd_func_info(core, &info);
	अगर (rval < 0)
		जाओ घातer_करोwn;

	core->revision = si476x_core_fwver_to_revision(core, info.func,
						       info.firmware.major,
						       info.firmware.minor[0],
						       info.firmware.minor[1]);
घातer_करोwn:
	si476x_core_set_घातer_state(core, SI476X_POWER_DOWN);
निकास:
	si476x_core_unlock(core);

	वापस rval;
पूर्ण

bool si476x_core_has_am(काष्ठा si476x_core *core)
अणु
	वापस core->chip_id == SI476X_CHIP_SI4761 ||
		core->chip_id == SI476X_CHIP_SI4764;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_has_am);

bool si476x_core_has_भागersity(काष्ठा si476x_core *core)
अणु
	वापस core->chip_id == SI476X_CHIP_SI4764;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_has_भागersity);

bool si476x_core_is_a_secondary_tuner(काष्ठा si476x_core *core)
अणु
	वापस si476x_core_has_भागersity(core) &&
		(core->भागersity_mode == SI476X_PHDIV_SECONDARY_ANTENNA ||
		 core->भागersity_mode == SI476X_PHDIV_SECONDARY_COMBINING);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_is_a_secondary_tuner);

bool si476x_core_is_a_primary_tuner(काष्ठा si476x_core *core)
अणु
	वापस si476x_core_has_भागersity(core) &&
		(core->भागersity_mode == SI476X_PHDIV_PRIMARY_ANTENNA ||
		 core->भागersity_mode == SI476X_PHDIV_PRIMARY_COMBINING);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_is_a_primary_tuner);

bool si476x_core_is_in_am_receiver_mode(काष्ठा si476x_core *core)
अणु
	वापस si476x_core_has_am(core) &&
		(core->घातer_up_parameters.func == SI476X_FUNC_AM_RECEIVER);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_is_in_am_receiver_mode);

bool si476x_core_is_घातered_up(काष्ठा si476x_core *core)
अणु
	वापस core->घातer_state == SI476X_POWER_UP_FULL;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_is_घातered_up);

अटल पूर्णांक si476x_core_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक rval;
	काष्ठा si476x_core          *core;
	काष्ठा si476x_platक्रमm_data *pdata;
	काष्ठा mfd_cell *cell;
	पूर्णांक              cell_num;

	core = devm_kzalloc(&client->dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->client = client;

	core->regmap = devm_regmap_init_si476x(core);
	अगर (IS_ERR(core->regmap)) अणु
		rval = PTR_ERR(core->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n",
			rval);
		वापस rval;
	पूर्ण

	i2c_set_clientdata(client, core);

	atomic_set(&core->is_alive, 0);
	core->घातer_state = SI476X_POWER_DOWN;

	pdata = dev_get_platdata(&client->dev);
	अगर (pdata) अणु
		स_नकल(&core->घातer_up_parameters,
		       &pdata->घातer_up_parameters,
		       माप(core->घातer_up_parameters));

		core->gpio_reset = -1;
		अगर (gpio_is_valid(pdata->gpio_reset)) अणु
			rval = gpio_request(pdata->gpio_reset, "si476x reset");
			अगर (rval) अणु
				dev_err(&client->dev,
					"Failed to request gpio: %d\n", rval);
				वापस rval;
			पूर्ण
			core->gpio_reset = pdata->gpio_reset;
			gpio_direction_output(core->gpio_reset, 0);
		पूर्ण

		core->भागersity_mode = pdata->भागersity_mode;
		स_नकल(&core->pinmux, &pdata->pinmux,
		       माप(काष्ठा si476x_pinmux));
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "No platform data provided\n");
		वापस -EINVAL;
	पूर्ण

	core->supplies[0].supply = "vd";
	core->supplies[1].supply = "va";
	core->supplies[2].supply = "vio1";
	core->supplies[3].supply = "vio2";

	rval = devm_regulator_bulk_get(&client->dev,
				       ARRAY_SIZE(core->supplies),
				       core->supplies);
	अगर (rval) अणु
		dev_err(&client->dev, "Failed to get all of the regulators\n");
		जाओ मुक्त_gpio;
	पूर्ण

	mutex_init(&core->cmd_lock);
	init_रुकोqueue_head(&core->command);
	init_रुकोqueue_head(&core->tuning);

	rval = kfअगरo_alloc(&core->rds_fअगरo,
			   SI476X_DRIVER_RDS_FIFO_DEPTH *
			   माप(काष्ठा v4l2_rds_data),
			   GFP_KERNEL);
	अगर (rval) अणु
		dev_err(&client->dev, "Could not allocate the FIFO\n");
		जाओ मुक्त_gpio;
	पूर्ण
	mutex_init(&core->rds_drainer_status_lock);
	init_रुकोqueue_head(&core->rds_पढ़ो_queue);
	INIT_WORK(&core->rds_fअगरo_drainer, si476x_core_drain_rds_fअगरo);

	अगर (client->irq) अणु
		rval = devm_request_thपढ़ोed_irq(&client->dev,
						 client->irq, शून्य,
						 si476x_core_पूर्णांकerrupt,
						 IRQF_TRIGGER_FALLING |
						 IRQF_ONESHOT,
						 client->name, core);
		अगर (rval < 0) अणु
			dev_err(&client->dev, "Could not request IRQ %d\n",
				client->irq);
			जाओ मुक्त_kfअगरo;
		पूर्ण
		disable_irq(client->irq);
		dev_dbg(&client->dev, "IRQ requested.\n");

		core->rds_fअगरo_depth = 20;
	पूर्ण अन्यथा अणु
		INIT_DELAYED_WORK(&core->status_monitor,
				  si476x_core_poll_loop);
		dev_info(&client->dev,
			 "No IRQ number specified, will use polling\n");

		core->rds_fअगरo_depth = 5;
	पूर्ण

	core->chip_id = id->driver_data;

	rval = si476x_core_get_revision_info(core);
	अगर (rval < 0) अणु
		rval = -ENODEV;
		जाओ मुक्त_kfअगरo;
	पूर्ण

	cell_num = 0;

	cell = &core->cells[SI476X_RADIO_CELL];
	cell->name = "si476x-radio";
	cell_num++;

#अगर_घोषित CONFIG_SND_SOC_SI476X
	अगर ((core->chip_id == SI476X_CHIP_SI4761 ||
	     core->chip_id == SI476X_CHIP_SI4764)	&&
	    core->pinmux.dclk == SI476X_DCLK_DAUDIO     &&
	    core->pinmux.dfs  == SI476X_DFS_DAUDIO      &&
	    core->pinmux.करोut == SI476X_DOUT_I2S_OUTPUT &&
	    core->pinmux.xout == SI476X_XOUT_TRISTATE) अणु
		cell = &core->cells[SI476X_CODEC_CELL];
		cell->name          = "si476x-codec";
		cell_num++;
	पूर्ण
#पूर्ण_अगर
	rval = mfd_add_devices(&client->dev,
			       (client->adapter->nr << 8) + client->addr,
			       core->cells, cell_num,
			       शून्य, 0, शून्य);
	अगर (!rval)
		वापस 0;

मुक्त_kfअगरo:
	kfअगरo_मुक्त(&core->rds_fअगरo);

मुक्त_gpio:
	अगर (gpio_is_valid(core->gpio_reset))
		gpio_मुक्त(core->gpio_reset);

	वापस rval;
पूर्ण

अटल पूर्णांक si476x_core_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा si476x_core *core = i2c_get_clientdata(client);

	si476x_core_pronounce_dead(core);
	mfd_हटाओ_devices(&client->dev);

	अगर (client->irq)
		disable_irq(client->irq);
	अन्यथा
		cancel_delayed_work_sync(&core->status_monitor);

	kfअगरo_मुक्त(&core->rds_fअगरo);

	अगर (gpio_is_valid(core->gpio_reset))
		gpio_मुक्त(core->gpio_reset);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id si476x_id[] = अणु
	अणु "si4761", SI476X_CHIP_SI4761 पूर्ण,
	अणु "si4764", SI476X_CHIP_SI4764 पूर्ण,
	अणु "si4768", SI476X_CHIP_SI4768 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si476x_id);

अटल काष्ठा i2c_driver si476x_core_driver = अणु
	.driver		= अणु
		.name	= "si476x-core",
	पूर्ण,
	.probe		= si476x_core_probe,
	.हटाओ         = si476x_core_हटाओ,
	.id_table       = si476x_id,
पूर्ण;
module_i2c_driver(si476x_core_driver);


MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("Si4761/64/68 AM/FM MFD core device driver");
MODULE_LICENSE("GPL");
