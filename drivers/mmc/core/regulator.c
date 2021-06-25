<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper functions क्रम MMC regulators.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/log2.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/mmc/host.h>

#समावेश "core.h"
#समावेश "host.h"

#अगर_घोषित CONFIG_REGULATOR

/**
 * mmc_ocrbitnum_to_vdd - Convert a OCR bit number to its voltage
 * @vdd_bit:	OCR bit number
 * @min_uV:	minimum voltage value (mV)
 * @max_uV:	maximum voltage value (mV)
 *
 * This function वापसs the voltage range according to the provided OCR
 * bit number. If conversion is not possible a negative त्रुटि_सं value वापसed.
 */
अटल पूर्णांक mmc_ocrbitnum_to_vdd(पूर्णांक vdd_bit, पूर्णांक *min_uV, पूर्णांक *max_uV)
अणु
	पूर्णांक		पंचांगp;

	अगर (!vdd_bit)
		वापस -EINVAL;

	/*
	 * REVISIT mmc_vddrange_to_ocrmask() may have set some
	 * bits this regulator करोesn't quite support ... don't
	 * be too picky, most cards and regulators are OK with
	 * a 0.1V range goof (it's a small error percentage).
	 */
	पंचांगp = vdd_bit - ilog2(MMC_VDD_165_195);
	अगर (पंचांगp == 0) अणु
		*min_uV = 1650 * 1000;
		*max_uV = 1950 * 1000;
	पूर्ण अन्यथा अणु
		*min_uV = 1900 * 1000 + पंचांगp * 100 * 1000;
		*max_uV = *min_uV + 100 * 1000;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mmc_regulator_get_ocrmask - वापस mask of supported voltages
 * @supply: regulator to use
 *
 * This वापसs either a negative त्रुटि_सं, or a mask of voltages that
 * can be provided to MMC/SD/SDIO devices using the specअगरied voltage
 * regulator.  This would normally be called beक्रमe रेजिस्टरing the
 * MMC host adapter.
 */
अटल पूर्णांक mmc_regulator_get_ocrmask(काष्ठा regulator *supply)
अणु
	पूर्णांक			result = 0;
	पूर्णांक			count;
	पूर्णांक			i;
	पूर्णांक			vdd_uV;
	पूर्णांक			vdd_mV;

	count = regulator_count_voltages(supply);
	अगर (count < 0)
		वापस count;

	क्रम (i = 0; i < count; i++) अणु
		vdd_uV = regulator_list_voltage(supply, i);
		अगर (vdd_uV <= 0)
			जारी;

		vdd_mV = vdd_uV / 1000;
		result |= mmc_vddrange_to_ocrmask(vdd_mV, vdd_mV);
	पूर्ण

	अगर (!result) अणु
		vdd_uV = regulator_get_voltage(supply);
		अगर (vdd_uV <= 0)
			वापस vdd_uV;

		vdd_mV = vdd_uV / 1000;
		result = mmc_vddrange_to_ocrmask(vdd_mV, vdd_mV);
	पूर्ण

	वापस result;
पूर्ण

/**
 * mmc_regulator_set_ocr - set regulator to match host->ios voltage
 * @mmc: the host to regulate
 * @supply: regulator to use
 * @vdd_bit: zero क्रम घातer off, अन्यथा a bit number (host->ios.vdd)
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 *
 * MMC host drivers may use this to enable or disable a regulator using
 * a particular supply voltage.  This would normally be called from the
 * set_ios() method.
 */
पूर्णांक mmc_regulator_set_ocr(काष्ठा mmc_host *mmc,
			काष्ठा regulator *supply,
			अचिन्हित लघु vdd_bit)
अणु
	पूर्णांक			result = 0;
	पूर्णांक			min_uV, max_uV;

	अगर (vdd_bit) अणु
		mmc_ocrbitnum_to_vdd(vdd_bit, &min_uV, &max_uV);

		result = regulator_set_voltage(supply, min_uV, max_uV);
		अगर (result == 0 && !mmc->regulator_enabled) अणु
			result = regulator_enable(supply);
			अगर (!result)
				mmc->regulator_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अगर (mmc->regulator_enabled) अणु
		result = regulator_disable(supply);
		अगर (result == 0)
			mmc->regulator_enabled = false;
	पूर्ण

	अगर (result)
		dev_err(mmc_dev(mmc),
			"could not set regulator OCR (%d)\n", result);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_regulator_set_ocr);

अटल पूर्णांक mmc_regulator_set_voltage_अगर_supported(काष्ठा regulator *regulator,
						  पूर्णांक min_uV, पूर्णांक target_uV,
						  पूर्णांक max_uV)
अणु
	पूर्णांक current_uV;

	/*
	 * Check अगर supported first to aव्योम errors since we may try several
	 * संकेत levels during घातer up and करोn't want to show errors.
	 */
	अगर (!regulator_is_supported_voltage(regulator, min_uV, max_uV))
		वापस -EINVAL;

	/*
	 * The voltage is alपढ़ोy set, no need to चयन.
	 * Return 1 to indicate that no चयन happened.
	 */
	current_uV = regulator_get_voltage(regulator);
	अगर (current_uV == target_uV)
		वापस 1;

	वापस regulator_set_voltage_triplet(regulator, min_uV, target_uV,
					     max_uV);
पूर्ण

/**
 * mmc_regulator_set_vqmmc - Set VQMMC as per the ios
 * @mmc: the host to regulate
 * @ios: io bus settings
 *
 * For 3.3V संकेतing, we try to match VQMMC to VMMC as बंदly as possible.
 * That will match the behavior of old boards where VQMMC and VMMC were supplied
 * by the same supply.  The Bus Operating conditions क्रम 3.3V संकेतing in the
 * SD card spec also define VQMMC in terms of VMMC.
 * If this is not possible we'll try the full 2.7-3.6V of the spec.
 *
 * For 1.2V and 1.8V संकेतing we'll try to get as बंद as possible to the
 * requested voltage.  This is definitely a good idea क्रम UHS where there's a
 * separate regulator on the card that's trying to make 1.8V and it's best अगर
 * we match.
 *
 * This function is expected to be used by a controller's
 * start_संकेत_voltage_चयन() function.
 */
पूर्णांक mmc_regulator_set_vqmmc(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा device *dev = mmc_dev(mmc);
	पूर्णांक ret, volt, min_uV, max_uV;

	/* If no vqmmc supply then we can't change the voltage */
	अगर (IS_ERR(mmc->supply.vqmmc))
		वापस -EINVAL;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_120:
		वापस mmc_regulator_set_voltage_अगर_supported(mmc->supply.vqmmc,
						1100000, 1200000, 1300000);
	हाल MMC_SIGNAL_VOLTAGE_180:
		वापस mmc_regulator_set_voltage_अगर_supported(mmc->supply.vqmmc,
						1700000, 1800000, 1950000);
	हाल MMC_SIGNAL_VOLTAGE_330:
		ret = mmc_ocrbitnum_to_vdd(mmc->ios.vdd, &volt, &max_uV);
		अगर (ret < 0)
			वापस ret;

		dev_dbg(dev, "%s: found vmmc voltage range of %d-%duV\n",
			__func__, volt, max_uV);

		min_uV = max(volt - 300000, 2700000);
		max_uV = min(max_uV + 200000, 3600000);

		/*
		 * Due to a limitation in the current implementation of
		 * regulator_set_voltage_triplet() which is taking the lowest
		 * voltage possible अगर below the target, search क्रम a suitable
		 * voltage in two steps and try to stay बंद to vmmc
		 * with a 0.3V tolerance at first.
		 */
		ret = mmc_regulator_set_voltage_अगर_supported(mmc->supply.vqmmc,
							min_uV, volt, max_uV);
		अगर (ret >= 0)
			वापस ret;

		वापस mmc_regulator_set_voltage_अगर_supported(mmc->supply.vqmmc,
						2700000, volt, 3600000);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mmc_regulator_set_vqmmc);

#अन्यथा

अटल अंतरभूत पूर्णांक mmc_regulator_get_ocrmask(काष्ठा regulator *supply)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_REGULATOR */

/**
 * mmc_regulator_get_supply - try to get VMMC and VQMMC regulators क्रम a host
 * @mmc: the host to regulate
 *
 * Returns 0 or त्रुटि_सं. त्रुटि_सं should be handled, it is either a critical error
 * or -EPROBE_DEFER. 0 means no critical error but it करोes not mean all
 * regulators have been found because they all are optional. If you require
 * certain regulators, you need to check separately in your driver अगर they got
 * populated after calling this function.
 */
पूर्णांक mmc_regulator_get_supply(काष्ठा mmc_host *mmc)
अणु
	काष्ठा device *dev = mmc_dev(mmc);
	पूर्णांक ret;

	mmc->supply.vmmc = devm_regulator_get_optional(dev, "vmmc");
	mmc->supply.vqmmc = devm_regulator_get_optional(dev, "vqmmc");

	अगर (IS_ERR(mmc->supply.vmmc)) अणु
		अगर (PTR_ERR(mmc->supply.vmmc) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(dev, "No vmmc regulator found\n");
	पूर्ण अन्यथा अणु
		ret = mmc_regulator_get_ocrmask(mmc->supply.vmmc);
		अगर (ret > 0)
			mmc->ocr_avail = ret;
		अन्यथा
			dev_warn(dev, "Failed getting OCR mask: %d\n", ret);
	पूर्ण

	अगर (IS_ERR(mmc->supply.vqmmc)) अणु
		अगर (PTR_ERR(mmc->supply.vqmmc) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(dev, "No vqmmc regulator found\n");
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_regulator_get_supply);
