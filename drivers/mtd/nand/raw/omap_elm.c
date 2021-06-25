<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Error Location Module
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 */

#घोषणा DRIVER_NAME	"omap-elm"

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_data/elm.h>

#घोषणा ELM_SYSCONFIG			0x010
#घोषणा ELM_IRQSTATUS			0x018
#घोषणा ELM_IRQENABLE			0x01c
#घोषणा ELM_LOCATION_CONFIG		0x020
#घोषणा ELM_PAGE_CTRL			0x080
#घोषणा ELM_SYNDROME_FRAGMENT_0		0x400
#घोषणा ELM_SYNDROME_FRAGMENT_1		0x404
#घोषणा ELM_SYNDROME_FRAGMENT_2		0x408
#घोषणा ELM_SYNDROME_FRAGMENT_3		0x40c
#घोषणा ELM_SYNDROME_FRAGMENT_4		0x410
#घोषणा ELM_SYNDROME_FRAGMENT_5		0x414
#घोषणा ELM_SYNDROME_FRAGMENT_6		0x418
#घोषणा ELM_LOCATION_STATUS		0x800
#घोषणा ELM_ERROR_LOCATION_0		0x880

/* ELM Interrupt Status Register */
#घोषणा INTR_STATUS_PAGE_VALID		BIT(8)

/* ELM Interrupt Enable Register */
#घोषणा INTR_EN_PAGE_MASK		BIT(8)

/* ELM Location Configuration Register */
#घोषणा ECC_BCH_LEVEL_MASK		0x3

/* ELM syndrome */
#घोषणा ELM_SYNDROME_VALID		BIT(16)

/* ELM_LOCATION_STATUS Register */
#घोषणा ECC_CORRECTABLE_MASK		BIT(8)
#घोषणा ECC_NB_ERRORS_MASK		0x1f

/* ELM_ERROR_LOCATION_0-15 Registers */
#घोषणा ECC_ERROR_LOCATION_MASK		0x1fff

#घोषणा ELM_ECC_SIZE			0x7ff

#घोषणा SYNDROME_FRAGMENT_REG_SIZE	0x40
#घोषणा ERROR_LOCATION_SIZE		0x100

काष्ठा elm_रेजिस्टरs अणु
	u32 elm_irqenable;
	u32 elm_sysconfig;
	u32 elm_location_config;
	u32 elm_page_ctrl;
	u32 elm_syndrome_fragment_6[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_5[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_4[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_3[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_2[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_1[ERROR_VECTOR_MAX];
	u32 elm_syndrome_fragment_0[ERROR_VECTOR_MAX];
पूर्ण;

काष्ठा elm_info अणु
	काष्ठा device *dev;
	व्योम __iomem *elm_base;
	काष्ठा completion elm_completion;
	काष्ठा list_head list;
	क्रमागत bch_ecc bch_type;
	काष्ठा elm_रेजिस्टरs elm_regs;
	पूर्णांक ecc_steps;
	पूर्णांक ecc_syndrome_size;
पूर्ण;

अटल LIST_HEAD(elm_devices);

अटल व्योम elm_ग_लिखो_reg(काष्ठा elm_info *info, पूर्णांक offset, u32 val)
अणु
	ग_लिखोl(val, info->elm_base + offset);
पूर्ण

अटल u32 elm_पढ़ो_reg(काष्ठा elm_info *info, पूर्णांक offset)
अणु
	वापस पढ़ोl(info->elm_base + offset);
पूर्ण

/**
 * elm_config - Configure ELM module
 * @dev:	ELM device
 * @bch_type:	Type of BCH ecc
 * @ecc_steps:	ECC steps to assign to config
 * @ecc_step_size:	ECC step size to assign to config
 * @ecc_syndrome_size:	ECC syndrome size to assign to config
 */
पूर्णांक elm_config(काष्ठा device *dev, क्रमागत bch_ecc bch_type,
	पूर्णांक ecc_steps, पूर्णांक ecc_step_size, पूर्णांक ecc_syndrome_size)
अणु
	u32 reg_val;
	काष्ठा elm_info *info = dev_get_drvdata(dev);

	अगर (!info) अणु
		dev_err(dev, "Unable to configure elm - device not probed?\n");
		वापस -EPROBE_DEFER;
	पूर्ण
	/* ELM cannot detect ECC errors क्रम chunks > 1KB */
	अगर (ecc_step_size > ((ELM_ECC_SIZE + 1) / 2)) अणु
		dev_err(dev, "unsupported config ecc-size=%d\n", ecc_step_size);
		वापस -EINVAL;
	पूर्ण
	/* ELM support 8 error syndrome process */
	अगर (ecc_steps > ERROR_VECTOR_MAX) अणु
		dev_err(dev, "unsupported config ecc-step=%d\n", ecc_steps);
		वापस -EINVAL;
	पूर्ण

	reg_val = (bch_type & ECC_BCH_LEVEL_MASK) | (ELM_ECC_SIZE << 16);
	elm_ग_लिखो_reg(info, ELM_LOCATION_CONFIG, reg_val);
	info->bch_type		= bch_type;
	info->ecc_steps		= ecc_steps;
	info->ecc_syndrome_size	= ecc_syndrome_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(elm_config);

/**
 * elm_configure_page_mode - Enable/Disable page mode
 * @info:	elm info
 * @index:	index number of syndrome fragment vector
 * @enable:	enable/disable flag क्रम page mode
 *
 * Enable page mode क्रम syndrome fragment index
 */
अटल व्योम elm_configure_page_mode(काष्ठा elm_info *info, पूर्णांक index,
		bool enable)
अणु
	u32 reg_val;

	reg_val = elm_पढ़ो_reg(info, ELM_PAGE_CTRL);
	अगर (enable)
		reg_val |= BIT(index);	/* enable page mode */
	अन्यथा
		reg_val &= ~BIT(index);	/* disable page mode */

	elm_ग_लिखो_reg(info, ELM_PAGE_CTRL, reg_val);
पूर्ण

/**
 * elm_load_syndrome - Load ELM syndrome reg
 * @info:	elm info
 * @err_vec:	elm error vectors
 * @ecc:	buffer with calculated ecc
 *
 * Load syndrome fragment रेजिस्टरs with calculated ecc in reverse order.
 */
अटल व्योम elm_load_syndrome(काष्ठा elm_info *info,
		काष्ठा elm_errorvec *err_vec, u8 *ecc)
अणु
	पूर्णांक i, offset;
	u32 val;

	क्रम (i = 0; i < info->ecc_steps; i++) अणु

		/* Check error reported */
		अगर (err_vec[i].error_reported) अणु
			elm_configure_page_mode(info, i, true);
			offset = ELM_SYNDROME_FRAGMENT_0 +
				SYNDROME_FRAGMENT_REG_SIZE * i;
			चयन (info->bch_type) अणु
			हाल BCH8_ECC:
				/* syndrome fragment 0 = ecc[9-12B] */
				val = cpu_to_be32(*(u32 *) &ecc[9]);
				elm_ग_लिखो_reg(info, offset, val);

				/* syndrome fragment 1 = ecc[5-8B] */
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[5]);
				elm_ग_लिखो_reg(info, offset, val);

				/* syndrome fragment 2 = ecc[1-4B] */
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[1]);
				elm_ग_लिखो_reg(info, offset, val);

				/* syndrome fragment 3 = ecc[0B] */
				offset += 4;
				val = ecc[0];
				elm_ग_लिखो_reg(info, offset, val);
				अवरोध;
			हाल BCH4_ECC:
				/* syndrome fragment 0 = ecc[20-52b] bits */
				val = (cpu_to_be32(*(u32 *) &ecc[3]) >> 4) |
					((ecc[2] & 0xf) << 28);
				elm_ग_लिखो_reg(info, offset, val);

				/* syndrome fragment 1 = ecc[0-20b] bits */
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[0]) >> 12;
				elm_ग_लिखो_reg(info, offset, val);
				अवरोध;
			हाल BCH16_ECC:
				val = cpu_to_be32(*(u32 *) &ecc[22]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[18]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[14]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[10]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[6]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[2]);
				elm_ग_लिखो_reg(info, offset, val);
				offset += 4;
				val = cpu_to_be32(*(u32 *) &ecc[0]) >> 16;
				elm_ग_लिखो_reg(info, offset, val);
				अवरोध;
			शेष:
				pr_err("invalid config bch_type\n");
			पूर्ण
		पूर्ण

		/* Update ecc poपूर्णांकer with ecc byte size */
		ecc += info->ecc_syndrome_size;
	पूर्ण
पूर्ण

/**
 * elm_start_processing - start elm syndrome processing
 * @info:	elm info
 * @err_vec:	elm error vectors
 *
 * Set syndrome valid bit क्रम syndrome fragment रेजिस्टरs क्रम which
 * elm syndrome fragment रेजिस्टरs are loaded. This enables elm module
 * to start processing syndrome vectors.
 */
अटल व्योम elm_start_processing(काष्ठा elm_info *info,
		काष्ठा elm_errorvec *err_vec)
अणु
	पूर्णांक i, offset;
	u32 reg_val;

	/*
	 * Set syndrome vector valid, so that ELM module
	 * will process it क्रम vectors error is reported
	 */
	क्रम (i = 0; i < info->ecc_steps; i++) अणु
		अगर (err_vec[i].error_reported) अणु
			offset = ELM_SYNDROME_FRAGMENT_6 +
				SYNDROME_FRAGMENT_REG_SIZE * i;
			reg_val = elm_पढ़ो_reg(info, offset);
			reg_val |= ELM_SYNDROME_VALID;
			elm_ग_लिखो_reg(info, offset, reg_val);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * elm_error_correction - locate correctable error position
 * @info:	elm info
 * @err_vec:	elm error vectors
 *
 * On completion of processing by elm module, error location status
 * रेजिस्टर updated with correctable/uncorrectable error inक्रमmation.
 * In हाल of correctable errors, number of errors located from
 * elm location status रेजिस्टर & पढ़ो the positions from
 * elm error location रेजिस्टर.
 */
अटल व्योम elm_error_correction(काष्ठा elm_info *info,
		काष्ठा elm_errorvec *err_vec)
अणु
	पूर्णांक i, j, errors = 0;
	पूर्णांक offset;
	u32 reg_val;

	क्रम (i = 0; i < info->ecc_steps; i++) अणु

		/* Check error reported */
		अगर (err_vec[i].error_reported) अणु
			offset = ELM_LOCATION_STATUS + ERROR_LOCATION_SIZE * i;
			reg_val = elm_पढ़ो_reg(info, offset);

			/* Check correctable error or not */
			अगर (reg_val & ECC_CORRECTABLE_MASK) अणु
				offset = ELM_ERROR_LOCATION_0 +
					ERROR_LOCATION_SIZE * i;

				/* Read count of correctable errors */
				err_vec[i].error_count = reg_val &
					ECC_NB_ERRORS_MASK;

				/* Update the error locations in error vector */
				क्रम (j = 0; j < err_vec[i].error_count; j++) अणु

					reg_val = elm_पढ़ो_reg(info, offset);
					err_vec[i].error_loc[j] = reg_val &
						ECC_ERROR_LOCATION_MASK;

					/* Update error location रेजिस्टर */
					offset += 4;
				पूर्ण

				errors += err_vec[i].error_count;
			पूर्ण अन्यथा अणु
				err_vec[i].error_uncorrectable = true;
			पूर्ण

			/* Clearing पूर्णांकerrupts क्रम processed error vectors */
			elm_ग_लिखो_reg(info, ELM_IRQSTATUS, BIT(i));

			/* Disable page mode */
			elm_configure_page_mode(info, i, false);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * elm_decode_bch_error_page - Locate error position
 * @dev:	device poपूर्णांकer
 * @ecc_calc:	calculated ECC bytes from GPMC
 * @err_vec:	elm error vectors
 *
 * Called with one or more error reported vectors & vectors with
 * error reported is updated in err_vec[].error_reported
 */
व्योम elm_decode_bch_error_page(काष्ठा device *dev, u8 *ecc_calc,
		काष्ठा elm_errorvec *err_vec)
अणु
	काष्ठा elm_info *info = dev_get_drvdata(dev);
	u32 reg_val;

	/* Enable page mode पूर्णांकerrupt */
	reg_val = elm_पढ़ो_reg(info, ELM_IRQSTATUS);
	elm_ग_लिखो_reg(info, ELM_IRQSTATUS, reg_val & INTR_STATUS_PAGE_VALID);
	elm_ग_लिखो_reg(info, ELM_IRQENABLE, INTR_EN_PAGE_MASK);

	/* Load valid ecc byte to syndrome fragment रेजिस्टर */
	elm_load_syndrome(info, err_vec, ecc_calc);

	/* Enable syndrome processing क्रम which syndrome fragment is updated */
	elm_start_processing(info, err_vec);

	/* Wait क्रम ELM module to finish locating error correction */
	रुको_क्रम_completion(&info->elm_completion);

	/* Disable page mode पूर्णांकerrupt */
	reg_val = elm_पढ़ो_reg(info, ELM_IRQENABLE);
	elm_ग_लिखो_reg(info, ELM_IRQENABLE, reg_val & ~INTR_EN_PAGE_MASK);
	elm_error_correction(info, err_vec);
पूर्ण
EXPORT_SYMBOL(elm_decode_bch_error_page);

अटल irqवापस_t elm_isr(पूर्णांक this_irq, व्योम *dev_id)
अणु
	u32 reg_val;
	काष्ठा elm_info *info = dev_id;

	reg_val = elm_पढ़ो_reg(info, ELM_IRQSTATUS);

	/* All error vectors processed */
	अगर (reg_val & INTR_STATUS_PAGE_VALID) अणु
		elm_ग_लिखो_reg(info, ELM_IRQSTATUS,
				reg_val & INTR_STATUS_PAGE_VALID);
		complete(&info->elm_completion);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक elm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा resource *res, *irq;
	काष्ठा elm_info *info;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "no irq resource defined\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	info->elm_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(info->elm_base))
		वापस PTR_ERR(info->elm_base);

	ret = devm_request_irq(&pdev->dev, irq->start, elm_isr, 0,
			pdev->name, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failure requesting %pr\n", irq);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (pm_runसमय_get_sync(&pdev->dev) < 0) अणु
		ret = -EINVAL;
		pm_runसमय_put_sync(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
		dev_err(&pdev->dev, "can't enable clock\n");
		वापस ret;
	पूर्ण

	init_completion(&info->elm_completion);
	INIT_LIST_HEAD(&info->list);
	list_add(&info->list, &elm_devices);
	platक्रमm_set_drvdata(pdev, info);
	वापस ret;
पूर्ण

अटल पूर्णांक elm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * elm_context_save
 * saves ELM configurations to preserve them across Hardware घातered-करोwn
 */
अटल पूर्णांक elm_context_save(काष्ठा elm_info *info)
अणु
	काष्ठा elm_रेजिस्टरs *regs = &info->elm_regs;
	क्रमागत bch_ecc bch_type = info->bch_type;
	u32 offset = 0, i;

	regs->elm_irqenable       = elm_पढ़ो_reg(info, ELM_IRQENABLE);
	regs->elm_sysconfig       = elm_पढ़ो_reg(info, ELM_SYSCONFIG);
	regs->elm_location_config = elm_पढ़ो_reg(info, ELM_LOCATION_CONFIG);
	regs->elm_page_ctrl       = elm_पढ़ो_reg(info, ELM_PAGE_CTRL);
	क्रम (i = 0; i < ERROR_VECTOR_MAX; i++) अणु
		offset = i * SYNDROME_FRAGMENT_REG_SIZE;
		चयन (bch_type) अणु
		हाल BCH16_ECC:
			regs->elm_syndrome_fragment_6[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_6 + offset);
			regs->elm_syndrome_fragment_5[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_5 + offset);
			regs->elm_syndrome_fragment_4[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_4 + offset);
			fallthrough;
		हाल BCH8_ECC:
			regs->elm_syndrome_fragment_3[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_3 + offset);
			regs->elm_syndrome_fragment_2[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_2 + offset);
			fallthrough;
		हाल BCH4_ECC:
			regs->elm_syndrome_fragment_1[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_1 + offset);
			regs->elm_syndrome_fragment_0[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_0 + offset);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		/* ELM SYNDROME_VALID bit in SYNDROME_FRAGMENT_6[] needs
		 * to be saved क्रम all BCH schemes*/
		regs->elm_syndrome_fragment_6[i] = elm_पढ़ो_reg(info,
					ELM_SYNDROME_FRAGMENT_6 + offset);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * elm_context_restore
 * ग_लिखोs configurations saved duing घातer-करोwn back पूर्णांकo ELM रेजिस्टरs
 */
अटल पूर्णांक elm_context_restore(काष्ठा elm_info *info)
अणु
	काष्ठा elm_रेजिस्टरs *regs = &info->elm_regs;
	क्रमागत bch_ecc bch_type = info->bch_type;
	u32 offset = 0, i;

	elm_ग_लिखो_reg(info, ELM_IRQENABLE,	 regs->elm_irqenable);
	elm_ग_लिखो_reg(info, ELM_SYSCONFIG,	 regs->elm_sysconfig);
	elm_ग_लिखो_reg(info, ELM_LOCATION_CONFIG, regs->elm_location_config);
	elm_ग_लिखो_reg(info, ELM_PAGE_CTRL,	 regs->elm_page_ctrl);
	क्रम (i = 0; i < ERROR_VECTOR_MAX; i++) अणु
		offset = i * SYNDROME_FRAGMENT_REG_SIZE;
		चयन (bch_type) अणु
		हाल BCH16_ECC:
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_6 + offset,
					regs->elm_syndrome_fragment_6[i]);
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_5 + offset,
					regs->elm_syndrome_fragment_5[i]);
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_4 + offset,
					regs->elm_syndrome_fragment_4[i]);
			fallthrough;
		हाल BCH8_ECC:
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_3 + offset,
					regs->elm_syndrome_fragment_3[i]);
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_2 + offset,
					regs->elm_syndrome_fragment_2[i]);
			fallthrough;
		हाल BCH4_ECC:
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_1 + offset,
					regs->elm_syndrome_fragment_1[i]);
			elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_0 + offset,
					regs->elm_syndrome_fragment_0[i]);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		/* ELM_SYNDROME_VALID bit to be set in last to trigger FSM */
		elm_ग_लिखो_reg(info, ELM_SYNDROME_FRAGMENT_6 + offset,
					regs->elm_syndrome_fragment_6[i] &
							 ELM_SYNDROME_VALID);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक elm_suspend(काष्ठा device *dev)
अणु
	काष्ठा elm_info *info = dev_get_drvdata(dev);
	elm_context_save(info);
	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक elm_resume(काष्ठा device *dev)
अणु
	काष्ठा elm_info *info = dev_get_drvdata(dev);
	pm_runसमय_get_sync(dev);
	elm_context_restore(info);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(elm_pm_ops, elm_suspend, elm_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id elm_of_match[] = अणु
	अणु .compatible = "ti,am3352-elm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, elm_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver elm_driver = अणु
	.driver	= अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(elm_of_match),
		.pm	= &elm_pm_ops,
	पूर्ण,
	.probe	= elm_probe,
	.हटाओ	= elm_हटाओ,
पूर्ण;

module_platक्रमm_driver(elm_driver);

MODULE_DESCRIPTION("ELM driver for BCH error correction");
MODULE_AUTHOR("Texas Instruments");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_LICENSE("GPL v2");
