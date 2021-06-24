<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश "linux/delay.h"
#समावेश "internals.h"

#घोषणा MACRONIX_READ_RETRY_BIT BIT(0)
#घोषणा MACRONIX_NUM_READ_RETRY_MODES 6

#घोषणा ONFI_FEATURE_ADDR_MXIC_PROTECTION 0xA0
#घोषणा MXIC_BLOCK_PROTECTION_ALL_LOCK 0x38
#घोषणा MXIC_BLOCK_PROTECTION_ALL_UNLOCK 0x0

#घोषणा ONFI_FEATURE_ADDR_MXIC_RANDOMIZER 0xB0
#घोषणा MACRONIX_RANDOMIZER_BIT BIT(1)
#घोषणा MACRONIX_RANDOMIZER_ENPGM BIT(0)
#घोषणा MACRONIX_RANDOMIZER_RANDEN BIT(1)
#घोषणा MACRONIX_RANDOMIZER_RANDOPT BIT(2)
#घोषणा MACRONIX_RANDOMIZER_MODE_ENTER	\
	(MACRONIX_RANDOMIZER_ENPGM |	\
	 MACRONIX_RANDOMIZER_RANDEN |	\
	 MACRONIX_RANDOMIZER_RANDOPT)
#घोषणा MACRONIX_RANDOMIZER_MODE_EXIT	\
	(MACRONIX_RANDOMIZER_RANDEN |	\
	 MACRONIX_RANDOMIZER_RANDOPT)

#घोषणा MXIC_CMD_POWER_DOWN 0xB9

काष्ठा nand_onfi_venकरोr_macronix अणु
	u8 reserved;
	u8 reliability_func;
पूर्ण __packed;

अटल पूर्णांक macronix_nand_setup_पढ़ो_retry(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];

	अगर (!chip->parameters.supports_set_get_features ||
	    !test_bit(ONFI_FEATURE_ADDR_READ_RETRY,
		      chip->parameters.set_feature_list))
		वापस -ENOTSUPP;

	feature[0] = mode;
	वापस nand_set_features(chip, ONFI_FEATURE_ADDR_READ_RETRY, feature);
पूर्ण

अटल पूर्णांक macronix_nand_अक्रमomizer_check_enable(काष्ठा nand_chip *chip)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];
	पूर्णांक ret;

	ret = nand_get_features(chip, ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
				feature);
	अगर (ret < 0)
		वापस ret;

	अगर (feature[0])
		वापस feature[0];

	feature[0] = MACRONIX_RANDOMIZER_MODE_ENTER;
	ret = nand_set_features(chip, ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
				feature);
	अगर (ret < 0)
		वापस ret;

	/* RANDEN and RANDOPT OTP bits are programmed */
	feature[0] = 0x0;
	ret = nand_prog_page_op(chip, 0, 0, feature, 1);
	अगर (ret < 0)
		वापस ret;

	ret = nand_get_features(chip, ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
				feature);
	अगर (ret < 0)
		वापस ret;

	feature[0] &= MACRONIX_RANDOMIZER_MODE_EXIT;
	ret = nand_set_features(chip, ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
				feature);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम macronix_nand_onfi_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_parameters *p = &chip->parameters;
	काष्ठा nand_onfi_venकरोr_macronix *mxic;
	काष्ठा device_node *dn = nand_get_flash_node(chip);
	पूर्णांक अक्रम_otp = 0;
	पूर्णांक ret;

	अगर (!p->onfi)
		वापस;

	अगर (of_find_property(dn, "mxic,enable-randomizer-otp", शून्य))
		अक्रम_otp = 1;

	mxic = (काष्ठा nand_onfi_venकरोr_macronix *)p->onfi->venकरोr;
	/* Subpage ग_लिखो is prohibited in अक्रमomizer operम_से_पn */
	अगर (अक्रम_otp && chip->options & न_अंकD_NO_SUBPAGE_WRITE &&
	    mxic->reliability_func & MACRONIX_RANDOMIZER_BIT) अणु
		अगर (p->supports_set_get_features) अणु
			biपंचांगap_set(p->set_feature_list,
				   ONFI_FEATURE_ADDR_MXIC_RANDOMIZER, 1);
			biपंचांगap_set(p->get_feature_list,
				   ONFI_FEATURE_ADDR_MXIC_RANDOMIZER, 1);
			ret = macronix_nand_अक्रमomizer_check_enable(chip);
			अगर (ret < 0) अणु
				biपंचांगap_clear(p->set_feature_list,
					     ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
					     1);
				biपंचांगap_clear(p->get_feature_list,
					     ONFI_FEATURE_ADDR_MXIC_RANDOMIZER,
					     1);
				pr_info("Macronix NAND randomizer failed\n");
			पूर्ण अन्यथा अणु
				pr_info("Macronix NAND randomizer enabled\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((mxic->reliability_func & MACRONIX_READ_RETRY_BIT) == 0)
		वापस;

	chip->पढ़ो_retries = MACRONIX_NUM_READ_RETRY_MODES;
	chip->ops.setup_पढ़ो_retry = macronix_nand_setup_पढ़ो_retry;

	अगर (p->supports_set_get_features) अणु
		biपंचांगap_set(p->set_feature_list,
			   ONFI_FEATURE_ADDR_READ_RETRY, 1);
		biपंचांगap_set(p->get_feature_list,
			   ONFI_FEATURE_ADDR_READ_RETRY, 1);
	पूर्ण
पूर्ण

/*
 * Macronix AC series करोes not support using SET/GET_FEATURES to change
 * the timings unlike what is declared in the parameter page. Unflag
 * this feature to aव्योम unnecessary करोwnturns.
 */
अटल व्योम macronix_nand_fix_broken_get_timings(काष्ठा nand_chip *chip)
अणु
	पूर्णांक i;
	अटल स्थिर अक्षर * स्थिर broken_get_timings[] = अणु
		"MX30LF1G18AC",
		"MX30LF1G28AC",
		"MX30LF2G18AC",
		"MX30LF2G28AC",
		"MX30LF4G18AC",
		"MX30LF4G28AC",
		"MX60LF8G18AC",
		"MX30UF1G18AC",
		"MX30UF1G16AC",
		"MX30UF2G18AC",
		"MX30UF2G16AC",
		"MX30UF4G18AC",
		"MX30UF4G16AC",
		"MX30UF4G28AC",
	पूर्ण;

	अगर (!chip->parameters.supports_set_get_features)
		वापस;

	i = match_string(broken_get_timings, ARRAY_SIZE(broken_get_timings),
			 chip->parameters.model);
	अगर (i < 0)
		वापस;

	biपंचांगap_clear(chip->parameters.get_feature_list,
		     ONFI_FEATURE_ADDR_TIMING_MODE, 1);
	biपंचांगap_clear(chip->parameters.set_feature_list,
		     ONFI_FEATURE_ADDR_TIMING_MODE, 1);
पूर्ण

/*
 * Macronix न_अंकD supports Block Protection by Protectoin(PT) pin;
 * active high at घातer-on which protects the entire chip even the #WP is
 * disabled. Lock/unlock protection area can be partition according to
 * protection bits, i.e. upper 1/2 locked, upper 1/4 locked and so on.
 */
अटल पूर्णांक mxic_nand_lock(काष्ठा nand_chip *chip, loff_t ofs, uपूर्णांक64_t len)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];
	पूर्णांक ret;

	feature[0] = MXIC_BLOCK_PROTECTION_ALL_LOCK;
	nand_select_target(chip, 0);
	ret = nand_set_features(chip, ONFI_FEATURE_ADDR_MXIC_PROTECTION,
				feature);
	nand_deselect_target(chip);
	अगर (ret)
		pr_err("%s all blocks failed\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक mxic_nand_unlock(काष्ठा nand_chip *chip, loff_t ofs, uपूर्णांक64_t len)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];
	पूर्णांक ret;

	feature[0] = MXIC_BLOCK_PROTECTION_ALL_UNLOCK;
	nand_select_target(chip, 0);
	ret = nand_set_features(chip, ONFI_FEATURE_ADDR_MXIC_PROTECTION,
				feature);
	nand_deselect_target(chip);
	अगर (ret)
		pr_err("%s all blocks failed\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम macronix_nand_block_protection_support(काष्ठा nand_chip *chip)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];
	पूर्णांक ret;

	biपंचांगap_set(chip->parameters.get_feature_list,
		   ONFI_FEATURE_ADDR_MXIC_PROTECTION, 1);

	feature[0] = MXIC_BLOCK_PROTECTION_ALL_UNLOCK;
	nand_select_target(chip, 0);
	ret = nand_get_features(chip, ONFI_FEATURE_ADDR_MXIC_PROTECTION,
				feature);
	nand_deselect_target(chip);
	अगर (ret || feature[0] != MXIC_BLOCK_PROTECTION_ALL_LOCK) अणु
		अगर (ret)
			pr_err("Block protection check failed\n");

		biपंचांगap_clear(chip->parameters.get_feature_list,
			     ONFI_FEATURE_ADDR_MXIC_PROTECTION, 1);
		वापस;
	पूर्ण

	biपंचांगap_set(chip->parameters.set_feature_list,
		   ONFI_FEATURE_ADDR_MXIC_PROTECTION, 1);

	chip->ops.lock_area = mxic_nand_lock;
	chip->ops.unlock_area = mxic_nand_unlock;
पूर्ण

अटल पूर्णांक nand_घातer_करोwn_op(काष्ठा nand_chip *chip)
अणु
	पूर्णांक ret;

	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(MXIC_CMD_POWER_DOWN, 0),
		पूर्ण;

		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		ret = nand_exec_op(chip, &op);
		अगर (ret)
			वापस ret;

	पूर्ण अन्यथा अणु
		chip->legacy.cmdfunc(chip, MXIC_CMD_POWER_DOWN, -1, -1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxic_nand_suspend(काष्ठा nand_chip *chip)
अणु
	पूर्णांक ret;

	nand_select_target(chip, 0);
	ret = nand_घातer_करोwn_op(chip);
	अगर (ret < 0)
		pr_err("Suspending MXIC NAND chip failed (%d)\n", ret);
	nand_deselect_target(chip);

	वापस ret;
पूर्ण

अटल व्योम mxic_nand_resume(काष्ठा nand_chip *chip)
अणु
	/*
	 * Toggle #CS pin to resume न_अंकD device and करोn't care
	 * of the others CLE, #WE, #RE pins status.
	 * A न_अंकD controller ensure it is able to निश्चित/de-निश्चित #CS
	 * by sending any byte over the न_अंकD bus.
	 * i.e.,
	 * न_अंकD घातer करोwn command or reset command w/o R/B# status checking.
	 */
	nand_select_target(chip, 0);
	nand_घातer_करोwn_op(chip);
	/* The minimum of a recovery समय tRDP is 35 us */
	usleep_range(35, 100);
	nand_deselect_target(chip);
पूर्ण

अटल व्योम macronix_nand_deep_घातer_करोwn_support(काष्ठा nand_chip *chip)
अणु
	पूर्णांक i;
	अटल स्थिर अक्षर * स्थिर deep_घातer_करोwn_dev[] = अणु
		"MX30UF1G28AD",
		"MX30UF2G28AD",
		"MX30UF4G28AD",
	पूर्ण;

	i = match_string(deep_घातer_करोwn_dev, ARRAY_SIZE(deep_घातer_करोwn_dev),
			 chip->parameters.model);
	अगर (i < 0)
		वापस;

	chip->ops.suspend = mxic_nand_suspend;
	chip->ops.resume = mxic_nand_resume;
पूर्ण

अटल पूर्णांक macronix_nand_init(काष्ठा nand_chip *chip)
अणु
	अगर (nand_is_slc(chip))
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE;

	macronix_nand_fix_broken_get_timings(chip);
	macronix_nand_onfi_init(chip);
	macronix_nand_block_protection_support(chip);
	macronix_nand_deep_घातer_करोwn_support(chip);

	वापस 0;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops macronix_nand_manuf_ops = अणु
	.init = macronix_nand_init,
पूर्ण;
