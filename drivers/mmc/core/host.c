<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/core/host.c
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright (C) 2007-2008 Pierre Ossman
 *  Copyright (C) 2010 Linus Walleij
 *
 *  MMC host class device management
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/idr.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/export.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "core.h"
#समावेश "crypto.h"
#समावेश "host.h"
#समावेश "slot-gpio.h"
#समावेश "pwrseq.h"
#समावेश "sdio_ops.h"

#घोषणा cls_dev_to_mmc_host(d)	container_of(d, काष्ठा mmc_host, class_dev)

अटल DEFINE_IDA(mmc_host_ida);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mmc_host_class_prepare(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *host = cls_dev_to_mmc_host(dev);

	/*
	 * It's safe to access the bus_ops poपूर्णांकer, as both userspace and the
	 * workqueue क्रम detecting cards are frozen at this poपूर्णांक.
	 */
	अगर (!host->bus_ops)
		वापस 0;

	/* Validate conditions क्रम प्रणाली suspend. */
	अगर (host->bus_ops->pre_suspend)
		वापस host->bus_ops->pre_suspend(host);

	वापस 0;
पूर्ण

अटल व्योम mmc_host_class_complete(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *host = cls_dev_to_mmc_host(dev);

	_mmc_detect_change(host, 0, false);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mmc_host_class_dev_pm_ops = अणु
	.prepare = mmc_host_class_prepare,
	.complete = mmc_host_class_complete,
पूर्ण;

#घोषणा MMC_HOST_CLASS_DEV_PM_OPS (&mmc_host_class_dev_pm_ops)
#अन्यथा
#घोषणा MMC_HOST_CLASS_DEV_PM_OPS शून्य
#पूर्ण_अगर

अटल व्योम mmc_host_classdev_release(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *host = cls_dev_to_mmc_host(dev);
	wakeup_source_unरेजिस्टर(host->ws);
	ida_simple_हटाओ(&mmc_host_ida, host->index);
	kमुक्त(host);
पूर्ण

अटल काष्ठा class mmc_host_class = अणु
	.name		= "mmc_host",
	.dev_release	= mmc_host_classdev_release,
	.pm		= MMC_HOST_CLASS_DEV_PM_OPS,
पूर्ण;

पूर्णांक mmc_रेजिस्टर_host_class(व्योम)
अणु
	वापस class_रेजिस्टर(&mmc_host_class);
पूर्ण

व्योम mmc_unरेजिस्टर_host_class(व्योम)
अणु
	class_unरेजिस्टर(&mmc_host_class);
पूर्ण

व्योम mmc_retune_enable(काष्ठा mmc_host *host)
अणु
	host->can_retune = 1;
	अगर (host->retune_period)
		mod_समयr(&host->retune_समयr,
			  jअगरfies + host->retune_period * HZ);
पूर्ण

/*
 * Pause re-tuning क्रम a small set of operations.  The छोड़ो begins after the
 * next command and after first करोing re-tuning.
 */
व्योम mmc_retune_छोड़ो(काष्ठा mmc_host *host)
अणु
	अगर (!host->retune_छोड़ोd) अणु
		host->retune_छोड़ोd = 1;
		mmc_retune_needed(host);
		mmc_retune_hold(host);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mmc_retune_छोड़ो);

व्योम mmc_retune_unछोड़ो(काष्ठा mmc_host *host)
अणु
	अगर (host->retune_छोड़ोd) अणु
		host->retune_छोड़ोd = 0;
		mmc_retune_release(host);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mmc_retune_unछोड़ो);

व्योम mmc_retune_disable(काष्ठा mmc_host *host)
अणु
	mmc_retune_unछोड़ो(host);
	host->can_retune = 0;
	del_समयr_sync(&host->retune_समयr);
	host->retune_now = 0;
	host->need_retune = 0;
पूर्ण

व्योम mmc_retune_समयr_stop(काष्ठा mmc_host *host)
अणु
	del_समयr_sync(&host->retune_समयr);
पूर्ण
EXPORT_SYMBOL(mmc_retune_समयr_stop);

व्योम mmc_retune_hold(काष्ठा mmc_host *host)
अणु
	अगर (!host->hold_retune)
		host->retune_now = 1;
	host->hold_retune += 1;
पूर्ण

व्योम mmc_retune_release(काष्ठा mmc_host *host)
अणु
	अगर (host->hold_retune)
		host->hold_retune -= 1;
	अन्यथा
		WARN_ON(1);
पूर्ण
EXPORT_SYMBOL(mmc_retune_release);

पूर्णांक mmc_retune(काष्ठा mmc_host *host)
अणु
	bool वापस_to_hs400 = false;
	पूर्णांक err;

	अगर (host->retune_now)
		host->retune_now = 0;
	अन्यथा
		वापस 0;

	अगर (!host->need_retune || host->करोing_retune || !host->card)
		वापस 0;

	host->need_retune = 0;

	host->करोing_retune = 1;

	अगर (host->ios.timing == MMC_TIMING_MMC_HS400) अणु
		err = mmc_hs400_to_hs200(host->card);
		अगर (err)
			जाओ out;

		वापस_to_hs400 = true;
	पूर्ण

	err = mmc_execute_tuning(host->card);
	अगर (err)
		जाओ out;

	अगर (वापस_to_hs400)
		err = mmc_hs200_to_hs400(host->card);
out:
	host->करोing_retune = 0;

	वापस err;
पूर्ण

अटल व्योम mmc_retune_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mmc_host *host = from_समयr(host, t, retune_समयr);

	mmc_retune_needed(host);
पूर्ण

अटल व्योम mmc_of_parse_timing_phase(काष्ठा device *dev, स्थिर अक्षर *prop,
				      काष्ठा mmc_clk_phase *phase)
अणु
	पूर्णांक degrees[2] = अणु0पूर्ण;
	पूर्णांक rc;

	rc = device_property_पढ़ो_u32_array(dev, prop, degrees, 2);
	phase->valid = !rc;
	अगर (phase->valid) अणु
		phase->in_deg = degrees[0];
		phase->out_deg = degrees[1];
	पूर्ण
पूर्ण

व्योम
mmc_of_parse_clk_phase(काष्ठा mmc_host *host, काष्ठा mmc_clk_phase_map *map)
अणु
	काष्ठा device *dev = host->parent;

	mmc_of_parse_timing_phase(dev, "clk-phase-legacy",
				  &map->phase[MMC_TIMING_LEGACY]);
	mmc_of_parse_timing_phase(dev, "clk-phase-mmc-hs",
				  &map->phase[MMC_TIMING_MMC_HS]);
	mmc_of_parse_timing_phase(dev, "clk-phase-sd-hs",
				  &map->phase[MMC_TIMING_SD_HS]);
	mmc_of_parse_timing_phase(dev, "clk-phase-uhs-sdr12",
				  &map->phase[MMC_TIMING_UHS_SDR12]);
	mmc_of_parse_timing_phase(dev, "clk-phase-uhs-sdr25",
				  &map->phase[MMC_TIMING_UHS_SDR25]);
	mmc_of_parse_timing_phase(dev, "clk-phase-uhs-sdr50",
				  &map->phase[MMC_TIMING_UHS_SDR50]);
	mmc_of_parse_timing_phase(dev, "clk-phase-uhs-sdr104",
				  &map->phase[MMC_TIMING_UHS_SDR104]);
	mmc_of_parse_timing_phase(dev, "clk-phase-uhs-ddr50",
				  &map->phase[MMC_TIMING_UHS_DDR50]);
	mmc_of_parse_timing_phase(dev, "clk-phase-mmc-ddr52",
				  &map->phase[MMC_TIMING_MMC_DDR52]);
	mmc_of_parse_timing_phase(dev, "clk-phase-mmc-hs200",
				  &map->phase[MMC_TIMING_MMC_HS200]);
	mmc_of_parse_timing_phase(dev, "clk-phase-mmc-hs400",
				  &map->phase[MMC_TIMING_MMC_HS400]);
पूर्ण
EXPORT_SYMBOL(mmc_of_parse_clk_phase);

/**
 * mmc_of_parse() - parse host's device properties
 * @host: host whose properties should be parsed.
 *
 * To keep the rest of the MMC subप्रणाली unaware of whether DT has been
 * used to to instantiate and configure this host instance or not, we
 * parse the properties and set respective generic mmc-host flags and
 * parameters.
 */
पूर्णांक mmc_of_parse(काष्ठा mmc_host *host)
अणु
	काष्ठा device *dev = host->parent;
	u32 bus_width, drv_type, cd_debounce_delay_ms;
	पूर्णांक ret;

	अगर (!dev || !dev_fwnode(dev))
		वापस 0;

	/* "bus-width" is translated to MMC_CAP_*_BIT_DATA flags */
	अगर (device_property_पढ़ो_u32(dev, "bus-width", &bus_width) < 0) अणु
		dev_dbg(host->parent,
			"\"bus-width\" property is missing, assuming 1 bit.\n");
		bus_width = 1;
	पूर्ण

	चयन (bus_width) अणु
	हाल 8:
		host->caps |= MMC_CAP_8_BIT_DATA;
		fallthrough;	/* Hosts capable of 8-bit can also करो 4 bits */
	हाल 4:
		host->caps |= MMC_CAP_4_BIT_DATA;
		अवरोध;
	हाल 1:
		अवरोध;
	शेष:
		dev_err(host->parent,
			"Invalid \"bus-width\" value %u!\n", bus_width);
		वापस -EINVAL;
	पूर्ण

	/* f_max is obtained from the optional "max-frequency" property */
	device_property_पढ़ो_u32(dev, "max-frequency", &host->f_max);

	/*
	 * Configure CD and WP pins. They are both by शेष active low to
	 * match the SDHCI spec. If GPIOs are provided क्रम CD and / or WP, the
	 * mmc-gpio helpers are used to attach, configure and use them. If
	 * polarity inversion is specअगरied in DT, one of MMC_CAP2_CD_ACTIVE_HIGH
	 * and MMC_CAP2_RO_ACTIVE_HIGH capability-2 flags is set. If the
	 * "broken-cd" property is provided, the MMC_CAP_NEEDS_POLL capability
	 * is set. If the "non-removable" property is found, the
	 * MMC_CAP_NONREMOVABLE capability is set and no card-detection
	 * configuration is perक्रमmed.
	 */

	/* Parse Card Detection */

	अगर (device_property_पढ़ो_bool(dev, "non-removable")) अणु
		host->caps |= MMC_CAP_NONREMOVABLE;
	पूर्ण अन्यथा अणु
		अगर (device_property_पढ़ो_bool(dev, "cd-inverted"))
			host->caps2 |= MMC_CAP2_CD_ACTIVE_HIGH;

		अगर (device_property_पढ़ो_u32(dev, "cd-debounce-delay-ms",
					     &cd_debounce_delay_ms))
			cd_debounce_delay_ms = 200;

		अगर (device_property_पढ़ो_bool(dev, "broken-cd"))
			host->caps |= MMC_CAP_NEEDS_POLL;

		ret = mmc_gpiod_request_cd(host, "cd", 0, false,
					   cd_debounce_delay_ms * 1000);
		अगर (!ret)
			dev_info(host->parent, "Got CD GPIO\n");
		अन्यथा अगर (ret != -ENOENT && ret != -ENOSYS)
			वापस ret;
	पूर्ण

	/* Parse Write Protection */

	अगर (device_property_पढ़ो_bool(dev, "wp-inverted"))
		host->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;

	ret = mmc_gpiod_request_ro(host, "wp", 0, 0);
	अगर (!ret)
		dev_info(host->parent, "Got WP GPIO\n");
	अन्यथा अगर (ret != -ENOENT && ret != -ENOSYS)
		वापस ret;

	अगर (device_property_पढ़ो_bool(dev, "disable-wp"))
		host->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;

	अगर (device_property_पढ़ो_bool(dev, "cap-sd-highspeed"))
		host->caps |= MMC_CAP_SD_HIGHSPEED;
	अगर (device_property_पढ़ो_bool(dev, "cap-mmc-highspeed"))
		host->caps |= MMC_CAP_MMC_HIGHSPEED;
	अगर (device_property_पढ़ो_bool(dev, "sd-uhs-sdr12"))
		host->caps |= MMC_CAP_UHS_SDR12;
	अगर (device_property_पढ़ो_bool(dev, "sd-uhs-sdr25"))
		host->caps |= MMC_CAP_UHS_SDR25;
	अगर (device_property_पढ़ो_bool(dev, "sd-uhs-sdr50"))
		host->caps |= MMC_CAP_UHS_SDR50;
	अगर (device_property_पढ़ो_bool(dev, "sd-uhs-sdr104"))
		host->caps |= MMC_CAP_UHS_SDR104;
	अगर (device_property_पढ़ो_bool(dev, "sd-uhs-ddr50"))
		host->caps |= MMC_CAP_UHS_DDR50;
	अगर (device_property_पढ़ो_bool(dev, "cap-power-off-card"))
		host->caps |= MMC_CAP_POWER_OFF_CARD;
	अगर (device_property_पढ़ो_bool(dev, "cap-mmc-hw-reset"))
		host->caps |= MMC_CAP_HW_RESET;
	अगर (device_property_पढ़ो_bool(dev, "cap-sdio-irq"))
		host->caps |= MMC_CAP_SDIO_IRQ;
	अगर (device_property_पढ़ो_bool(dev, "full-pwr-cycle"))
		host->caps2 |= MMC_CAP2_FULL_PWR_CYCLE;
	अगर (device_property_पढ़ो_bool(dev, "full-pwr-cycle-in-suspend"))
		host->caps2 |= MMC_CAP2_FULL_PWR_CYCLE_IN_SUSPEND;
	अगर (device_property_पढ़ो_bool(dev, "keep-power-in-suspend"))
		host->pm_caps |= MMC_PM_KEEP_POWER;
	अगर (device_property_पढ़ो_bool(dev, "wakeup-source") ||
	    device_property_पढ़ो_bool(dev, "enable-sdio-wakeup")) /* legacy */
		host->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;
	अगर (device_property_पढ़ो_bool(dev, "mmc-ddr-3_3v"))
		host->caps |= MMC_CAP_3_3V_DDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-ddr-1_8v"))
		host->caps |= MMC_CAP_1_8V_DDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-ddr-1_2v"))
		host->caps |= MMC_CAP_1_2V_DDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-hs200-1_8v"))
		host->caps2 |= MMC_CAP2_HS200_1_8V_SDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-hs200-1_2v"))
		host->caps2 |= MMC_CAP2_HS200_1_2V_SDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-hs400-1_8v"))
		host->caps2 |= MMC_CAP2_HS400_1_8V | MMC_CAP2_HS200_1_8V_SDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-hs400-1_2v"))
		host->caps2 |= MMC_CAP2_HS400_1_2V | MMC_CAP2_HS200_1_2V_SDR;
	अगर (device_property_पढ़ो_bool(dev, "mmc-hs400-enhanced-strobe"))
		host->caps2 |= MMC_CAP2_HS400_ES;
	अगर (device_property_पढ़ो_bool(dev, "no-sdio"))
		host->caps2 |= MMC_CAP2_NO_SDIO;
	अगर (device_property_पढ़ो_bool(dev, "no-sd"))
		host->caps2 |= MMC_CAP2_NO_SD;
	अगर (device_property_पढ़ो_bool(dev, "no-mmc"))
		host->caps2 |= MMC_CAP2_NO_MMC;

	/* Must be after "non-removable" check */
	अगर (device_property_पढ़ो_u32(dev, "fixed-emmc-driver-type", &drv_type) == 0) अणु
		अगर (host->caps & MMC_CAP_NONREMOVABLE)
			host->fixed_drv_type = drv_type;
		अन्यथा
			dev_err(host->parent,
				"can't use fixed driver type, media is removable\n");
	पूर्ण

	host->dsr_req = !device_property_पढ़ो_u32(dev, "dsr", &host->dsr);
	अगर (host->dsr_req && (host->dsr & ~0xffff)) अणु
		dev_err(host->parent,
			"device tree specified broken value for DSR: 0x%x, ignoring\n",
			host->dsr);
		host->dsr_req = 0;
	पूर्ण

	device_property_पढ़ो_u32(dev, "post-power-on-delay-ms",
				 &host->ios.घातer_delay_ms);

	वापस mmc_pwrseq_alloc(host);
पूर्ण

EXPORT_SYMBOL(mmc_of_parse);

/**
 * mmc_of_parse_voltage - वापस mask of supported voltages
 * @host: host whose properties should be parsed.
 * @mask: mask of voltages available क्रम MMC/SD/SDIO
 *
 * Parse the "voltage-ranges" property, वापसing zero अगर it is not
 * found, negative त्रुटि_सं अगर the voltage-range specअगरication is invalid,
 * or one अगर the voltage-range is specअगरied and successfully parsed.
 */
पूर्णांक mmc_of_parse_voltage(काष्ठा mmc_host *host, u32 *mask)
अणु
	स्थिर अक्षर *prop = "voltage-ranges";
	काष्ठा device *dev = host->parent;
	u32 *voltage_ranges;
	पूर्णांक num_ranges, i;
	पूर्णांक ret;

	अगर (!device_property_present(dev, prop)) अणु
		dev_dbg(dev, "%s unspecified\n", prop);
		वापस 0;
	पूर्ण

	ret = device_property_count_u32(dev, prop);
	अगर (ret < 0)
		वापस ret;

	num_ranges = ret / 2;
	अगर (!num_ranges) अणु
		dev_err(dev, "%s empty\n", prop);
		वापस -EINVAL;
	पूर्ण

	voltage_ranges = kसुस्मृति(2 * num_ranges, माप(*voltage_ranges), GFP_KERNEL);
	अगर (!voltage_ranges)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32_array(dev, prop, voltage_ranges, 2 * num_ranges);
	अगर (ret) अणु
		kमुक्त(voltage_ranges);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num_ranges; i++) अणु
		स्थिर पूर्णांक j = i * 2;
		u32 ocr_mask;

		ocr_mask = mmc_vddrange_to_ocrmask(voltage_ranges[j + 0],
						   voltage_ranges[j + 1]);
		अगर (!ocr_mask) अणु
			dev_err(dev, "range #%d in %s is invalid\n", i, prop);
			kमुक्त(voltage_ranges);
			वापस -EINVAL;
		पूर्ण
		*mask |= ocr_mask;
	पूर्ण

	kमुक्त(voltage_ranges);

	वापस 1;
पूर्ण
EXPORT_SYMBOL(mmc_of_parse_voltage);

/**
 * mmc_first_nonreserved_index() - get the first index that is not reserved
 */
अटल पूर्णांक mmc_first_nonreserved_index(व्योम)
अणु
	पूर्णांक max;

	max = of_alias_get_highest_id("mmc");
	अगर (max < 0)
		वापस 0;

	वापस max + 1;
पूर्ण

/**
 *	mmc_alloc_host - initialise the per-host काष्ठाure.
 *	@extra: माप निजी data काष्ठाure
 *	@dev: poपूर्णांकer to host device model काष्ठाure
 *
 *	Initialise the per-host काष्ठाure.
 */
काष्ठा mmc_host *mmc_alloc_host(पूर्णांक extra, काष्ठा device *dev)
अणु
	पूर्णांक err;
	काष्ठा mmc_host *host;
	पूर्णांक alias_id, min_idx, max_idx;

	host = kzalloc(माप(काष्ठा mmc_host) + extra, GFP_KERNEL);
	अगर (!host)
		वापस शून्य;

	/* scanning will be enabled when we're पढ़ोy */
	host->rescan_disable = 1;

	alias_id = of_alias_get_id(dev->of_node, "mmc");
	अगर (alias_id >= 0) अणु
		min_idx = alias_id;
		max_idx = alias_id + 1;
	पूर्ण अन्यथा अणु
		min_idx = mmc_first_nonreserved_index();
		max_idx = 0;
	पूर्ण

	err = ida_simple_get(&mmc_host_ida, min_idx, max_idx, GFP_KERNEL);
	अगर (err < 0) अणु
		kमुक्त(host);
		वापस शून्य;
	पूर्ण

	host->index = err;

	dev_set_name(&host->class_dev, "mmc%d", host->index);
	host->ws = wakeup_source_रेजिस्टर(शून्य, dev_name(&host->class_dev));

	host->parent = dev;
	host->class_dev.parent = dev;
	host->class_dev.class = &mmc_host_class;
	device_initialize(&host->class_dev);
	device_enable_async_suspend(&host->class_dev);

	अगर (mmc_gpio_alloc(host)) अणु
		put_device(&host->class_dev);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&host->lock);
	init_रुकोqueue_head(&host->wq);
	INIT_DELAYED_WORK(&host->detect, mmc_rescan);
	INIT_DELAYED_WORK(&host->sdio_irq_work, sdio_irq_work);
	समयr_setup(&host->retune_समयr, mmc_retune_समयr, 0);

	/*
	 * By शेष, hosts करो not support SGIO or large requests.
	 * They have to set these according to their abilities.
	 */
	host->max_segs = 1;
	host->max_seg_size = PAGE_SIZE;

	host->max_req_size = PAGE_SIZE;
	host->max_blk_size = 512;
	host->max_blk_count = PAGE_SIZE / 512;

	host->fixed_drv_type = -EINVAL;
	host->ios.घातer_delay_ms = 10;
	host->ios.घातer_mode = MMC_POWER_UNDEFINED;

	वापस host;
पूर्ण

EXPORT_SYMBOL(mmc_alloc_host);

/**
 *	mmc_add_host - initialise host hardware
 *	@host: mmc host
 *
 *	Register the host with the driver model. The host must be
 *	prepared to start servicing requests beक्रमe this function
 *	completes.
 */
पूर्णांक mmc_add_host(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	WARN_ON((host->caps & MMC_CAP_SDIO_IRQ) &&
		!host->ops->enable_sdio_irq);

	err = device_add(&host->class_dev);
	अगर (err)
		वापस err;

	led_trigger_रेजिस्टर_simple(dev_name(&host->class_dev), &host->led);

#अगर_घोषित CONFIG_DEBUG_FS
	mmc_add_host_debugfs(host);
#पूर्ण_अगर

	mmc_start_host(host);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(mmc_add_host);

/**
 *	mmc_हटाओ_host - हटाओ host hardware
 *	@host: mmc host
 *
 *	Unरेजिस्टर and हटाओ all cards associated with this host,
 *	and घातer करोwn the MMC bus. No new requests will be issued
 *	after this function has वापसed.
 */
व्योम mmc_हटाओ_host(काष्ठा mmc_host *host)
अणु
	mmc_stop_host(host);

#अगर_घोषित CONFIG_DEBUG_FS
	mmc_हटाओ_host_debugfs(host);
#पूर्ण_अगर

	device_del(&host->class_dev);

	led_trigger_unरेजिस्टर_simple(host->led);
पूर्ण

EXPORT_SYMBOL(mmc_हटाओ_host);

/**
 *	mmc_मुक्त_host - मुक्त the host काष्ठाure
 *	@host: mmc host
 *
 *	Free the host once all references to it have been dropped.
 */
व्योम mmc_मुक्त_host(काष्ठा mmc_host *host)
अणु
	mmc_pwrseq_मुक्त(host);
	put_device(&host->class_dev);
पूर्ण

EXPORT_SYMBOL(mmc_मुक्त_host);
