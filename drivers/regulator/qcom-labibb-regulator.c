<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा REG_PERPH_TYPE                  0x04

#घोषणा QCOM_LAB_TYPE			0x24
#घोषणा QCOM_IBB_TYPE			0x20

#घोषणा PMI8998_LAB_REG_BASE		0xde00
#घोषणा PMI8998_IBB_REG_BASE		0xdc00
#घोषणा PMI8998_IBB_LAB_REG_OFFSET	0x200

#घोषणा REG_LABIBB_STATUS1		0x08
 #घोषणा LABIBB_STATUS1_SC_BIT		BIT(6)
 #घोषणा LABIBB_STATUS1_VREG_OK_BIT	BIT(7)

#घोषणा REG_LABIBB_INT_SET_TYPE		0x11
#घोषणा REG_LABIBB_INT_POLARITY_HIGH	0x12
#घोषणा REG_LABIBB_INT_POLARITY_LOW	0x13
#घोषणा REG_LABIBB_INT_LATCHED_CLR	0x14
#घोषणा REG_LABIBB_INT_EN_SET		0x15
#घोषणा REG_LABIBB_INT_EN_CLR		0x16
 #घोषणा LABIBB_INT_VREG_OK		BIT(0)
 #घोषणा LABIBB_INT_VREG_TYPE_LEVEL	0

#घोषणा REG_LABIBB_VOLTAGE		0x41
 #घोषणा LABIBB_VOLTAGE_OVERRIDE_EN	BIT(7)
 #घोषणा LAB_VOLTAGE_SET_MASK		GENMASK(3, 0)
 #घोषणा IBB_VOLTAGE_SET_MASK		GENMASK(5, 0)

#घोषणा REG_LABIBB_ENABLE_CTL		0x46
 #घोषणा LABIBB_CONTROL_ENABLE		BIT(7)

#घोषणा REG_LABIBB_PD_CTL		0x47
 #घोषणा LAB_PD_CTL_MASK		GENMASK(1, 0)
 #घोषणा IBB_PD_CTL_MASK		(BIT(0) | BIT(7))
 #घोषणा LAB_PD_CTL_STRONG_PULL		BIT(0)
 #घोषणा IBB_PD_CTL_HALF_STRENGTH	BIT(0)
 #घोषणा IBB_PD_CTL_EN			BIT(7)

#घोषणा REG_LABIBB_CURRENT_LIMIT	0x4b
 #घोषणा LAB_CURRENT_LIMIT_MASK		GENMASK(2, 0)
 #घोषणा IBB_CURRENT_LIMIT_MASK		GENMASK(4, 0)
 #घोषणा LAB_CURRENT_LIMIT_OVERRIDE_EN	BIT(3)
 #घोषणा LABIBB_CURRENT_LIMIT_EN	BIT(7)

#घोषणा REG_IBB_PWRUP_PWRDN_CTL_1	0x58
 #घोषणा IBB_CTL_1_DISCHARGE_EN		BIT(2)

#घोषणा REG_LABIBB_SOFT_START_CTL	0x5f
#घोषणा REG_LABIBB_SEC_ACCESS		0xd0
 #घोषणा LABIBB_SEC_UNLOCK_CODE		0xa5

#घोषणा LAB_ENABLE_CTL_MASK		BIT(7)
#घोषणा IBB_ENABLE_CTL_MASK		(BIT(7) | BIT(6))

#घोषणा LABIBB_OFF_ON_DELAY		1000
#घोषणा LAB_ENABLE_TIME			(LABIBB_OFF_ON_DELAY * 2)
#घोषणा IBB_ENABLE_TIME			(LABIBB_OFF_ON_DELAY * 10)
#घोषणा LABIBB_POLL_ENABLED_TIME	1000
#घोषणा OCP_RECOVERY_INTERVAL_MS	500
#घोषणा SC_RECOVERY_INTERVAL_MS		250
#घोषणा LABIBB_MAX_OCP_COUNT		4
#घोषणा LABIBB_MAX_SC_COUNT		3
#घोषणा LABIBB_MAX_FATAL_COUNT		2

काष्ठा labibb_current_limits अणु
	u32				uA_min;
	u32				uA_step;
	u8				ovr_val;
पूर्ण;

काष्ठा labibb_regulator अणु
	काष्ठा regulator_desc		desc;
	काष्ठा device			*dev;
	काष्ठा regmap			*regmap;
	काष्ठा regulator_dev		*rdev;
	काष्ठा labibb_current_limits	uA_limits;
	काष्ठा delayed_work		ocp_recovery_work;
	काष्ठा delayed_work		sc_recovery_work;
	u16				base;
	u8				type;
	u8				dischg_sel;
	u8				soft_start_sel;
	पूर्णांक				sc_irq;
	पूर्णांक				sc_count;
	पूर्णांक				ocp_irq;
	पूर्णांक				ocp_irq_count;
	पूर्णांक				fatal_count;
पूर्ण;

काष्ठा labibb_regulator_data अणु
	स्थिर अक्षर			*name;
	u8				type;
	u16				base;
	स्थिर काष्ठा regulator_desc	*desc;
पूर्ण;

अटल पूर्णांक qcom_labibb_ocp_hw_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	/* Clear irq latch status to aव्योम spurious event */
	ret = regmap_update_bits(rdev->regmap,
				 vreg->base + REG_LABIBB_INT_LATCHED_CLR,
				 LABIBB_INT_VREG_OK, 1);
	अगर (ret)
		वापस ret;

	/* Enable OCP HW पूर्णांकerrupt */
	वापस regmap_update_bits(rdev->regmap,
				  vreg->base + REG_LABIBB_INT_EN_SET,
				  LABIBB_INT_VREG_OK, 1);
पूर्ण

अटल पूर्णांक qcom_labibb_ocp_hw_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);

	वापस regmap_update_bits(rdev->regmap,
				  vreg->base + REG_LABIBB_INT_EN_CLR,
				  LABIBB_INT_VREG_OK, 1);
पूर्ण

/**
 * qcom_labibb_check_ocp_status - Check the Over-Current Protection status
 * @vreg: Main driver काष्ठाure
 *
 * This function checks the STATUS1 रेजिस्टर क्रम the VREG_OK bit: अगर it is
 * set, then there is no Over-Current event.
 *
 * Returns: Zero अगर there is no over-current, 1 अगर in over-current or
 *          negative number क्रम error
 */
अटल पूर्णांक qcom_labibb_check_ocp_status(काष्ठा labibb_regulator *vreg)
अणु
	u32 cur_status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(vreg->rdev->regmap, vreg->base + REG_LABIBB_STATUS1,
			  &cur_status);
	अगर (ret)
		वापस ret;

	वापस !(cur_status & LABIBB_STATUS1_VREG_OK_BIT);
पूर्ण

/**
 * qcom_labibb_ocp_recovery_worker - Handle OCP event
 * @work: OCP work काष्ठाure
 *
 * This is the worker function to handle the Over Current Protection
 * hardware event; This will check अगर the hardware is still
 * संकेतing an over-current condition and will eventually stop
 * the regulator अगर such condition is still संकेतed after
 * LABIBB_MAX_OCP_COUNT बार.
 *
 * If the driver that is consuming the regulator did not take action
 * क्रम the OCP condition, or the hardware did not stabilize, a cut
 * of the LAB and IBB regulators will be क्रमced (regulators will be
 * disabled).
 *
 * As last, अगर the ग_लिखोs to shut करोwn the LAB/IBB regulators fail
 * क्रम more than LABIBB_MAX_FATAL_COUNT, then a kernel panic will be
 * triggered, as a last resort to protect the hardware from burning;
 * this, however, is expected to never happen, but this is kept to
 * try to further ensure that we protect the hardware at all costs.
 */
अटल व्योम qcom_labibb_ocp_recovery_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा labibb_regulator *vreg;
	स्थिर काष्ठा regulator_ops *ops;
	पूर्णांक ret;

	vreg = container_of(work, काष्ठा labibb_regulator,
			    ocp_recovery_work.work);
	ops = vreg->rdev->desc->ops;

	अगर (vreg->ocp_irq_count >= LABIBB_MAX_OCP_COUNT) अणु
		/*
		 * If we tried to disable the regulator multiple बार but
		 * we kept failing, there's only one last hope to save our
		 * hardware from the death: उठाओ a kernel bug, reboot and
		 * hope that the bootloader kindly saves us. This, though
		 * is करोne only as paranoid checking, because failing the
		 * regmap ग_लिखो to disable the vreg is almost impossible,
		 * since we got here after multiple regmap R/W.
		 */
		BUG_ON(vreg->fatal_count > LABIBB_MAX_FATAL_COUNT);
		dev_err(&vreg->rdev->dev, "LABIBB: CRITICAL: Disabling regulator\n");

		/* Disable the regulator immediately to aव्योम damage */
		ret = ops->disable(vreg->rdev);
		अगर (ret) अणु
			vreg->fatal_count++;
			जाओ reschedule;
		पूर्ण
		enable_irq(vreg->ocp_irq);
		vreg->fatal_count = 0;
		वापस;
	पूर्ण

	ret = qcom_labibb_check_ocp_status(vreg);
	अगर (ret != 0) अणु
		vreg->ocp_irq_count++;
		जाओ reschedule;
	पूर्ण

	ret = qcom_labibb_ocp_hw_enable(vreg->rdev);
	अगर (ret) अणु
		/* We cannot trust it without OCP enabled. */
		dev_err(vreg->dev, "Cannot enable OCP IRQ\n");
		vreg->ocp_irq_count++;
		जाओ reschedule;
	पूर्ण

	enable_irq(vreg->ocp_irq);
	/* Everything went fine: reset the OCP count! */
	vreg->ocp_irq_count = 0;
	वापस;

reschedule:
	mod_delayed_work(प्रणाली_wq, &vreg->ocp_recovery_work,
			 msecs_to_jअगरfies(OCP_RECOVERY_INTERVAL_MS));
पूर्ण

/**
 * qcom_labibb_ocp_isr - Interrupt routine क्रम OverCurrent Protection
 * @irq:  Interrupt number
 * @chip: Main driver काष्ठाure
 *
 * Over Current Protection (OCP) will संकेत to the client driver
 * that an over-current event has happened and then will schedule
 * a recovery worker.
 *
 * Disabling and eventually re-enabling the regulator is expected
 * to be करोne by the driver, as some hardware may be triggering an
 * over-current condition only at first initialization or it may
 * be expected only क्रम a very brief amount of समय, after which
 * the attached hardware may be expected to stabilize its current
 * draw.
 *
 * Returns: IRQ_HANDLED क्रम success or IRQ_NONE क्रम failure.
 */
अटल irqवापस_t qcom_labibb_ocp_isr(पूर्णांक irq, व्योम *chip)
अणु
	काष्ठा labibb_regulator *vreg = chip;
	स्थिर काष्ठा regulator_ops *ops = vreg->rdev->desc->ops;
	पूर्णांक ret;

	/* If the regulator is not enabled, this is a fake event */
	अगर (!ops->is_enabled(vreg->rdev))
		वापस 0;

	/* If we tried to recover क्रम too many बार it's not getting better */
	अगर (vreg->ocp_irq_count > LABIBB_MAX_OCP_COUNT)
		वापस IRQ_NONE;

	/*
	 * If we (unlikely) can't पढ़ो this रेजिस्टर, to prevent hardware
	 * damage at all costs, we assume that the overcurrent event was
	 * real; Moreover, अगर the status रेजिस्टर is not संकेतing OCP,
	 * it was a spurious event, so it's all ok.
	 */
	ret = qcom_labibb_check_ocp_status(vreg);
	अगर (ret == 0) अणु
		vreg->ocp_irq_count = 0;
		जाओ end;
	पूर्ण
	vreg->ocp_irq_count++;

	/*
	 * Disable the पूर्णांकerrupt temporarily, or it will fire continuously;
	 * we will re-enable it in the recovery worker function.
	 */
	disable_irq_nosync(irq);

	/* Warn the user क्रम overcurrent */
	dev_warn(vreg->dev, "Over-Current interrupt fired!\n");

	/* Disable the पूर्णांकerrupt to aव्योम hogging */
	ret = qcom_labibb_ocp_hw_disable(vreg->rdev);
	अगर (ret)
		जाओ end;

	/* Signal overcurrent event to drivers */
	regulator_notअगरier_call_chain(vreg->rdev,
				      REGULATOR_EVENT_OVER_CURRENT, शून्य);

end:
	/* Schedule the recovery work */
	schedule_delayed_work(&vreg->ocp_recovery_work,
			      msecs_to_jअगरfies(OCP_RECOVERY_INTERVAL_MS));
	अगर (ret)
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_labibb_set_ocp(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);
	अक्षर *ocp_irq_name;
	u32 irq_flags = IRQF_ONESHOT;
	पूर्णांक irq_trig_low, ret;

	/* If there is no OCP पूर्णांकerrupt, there's nothing to set */
	अगर (vreg->ocp_irq <= 0)
		वापस -EINVAL;

	ocp_irq_name = devm_kaप्र_लिखो(vreg->dev, GFP_KERNEL, "%s-over-current",
				      vreg->desc.name);
	अगर (!ocp_irq_name)
		वापस -ENOMEM;

	/* IRQ polarities - LAB: trigger-low, IBB: trigger-high */
	चयन (vreg->type) अणु
	हाल QCOM_LAB_TYPE:
		irq_flags |= IRQF_TRIGGER_LOW;
		irq_trig_low = 1;
		अवरोध;
	हाल QCOM_IBB_TYPE:
		irq_flags |= IRQF_TRIGGER_HIGH;
		irq_trig_low = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Activate OCP HW level पूर्णांकerrupt */
	ret = regmap_update_bits(rdev->regmap,
				 vreg->base + REG_LABIBB_INT_SET_TYPE,
				 LABIBB_INT_VREG_OK,
				 LABIBB_INT_VREG_TYPE_LEVEL);
	अगर (ret)
		वापस ret;

	/* Set OCP पूर्णांकerrupt polarity */
	ret = regmap_update_bits(rdev->regmap,
				 vreg->base + REG_LABIBB_INT_POLARITY_HIGH,
				 LABIBB_INT_VREG_OK, !irq_trig_low);
	अगर (ret)
		वापस ret;
	ret = regmap_update_bits(rdev->regmap,
				 vreg->base + REG_LABIBB_INT_POLARITY_LOW,
				 LABIBB_INT_VREG_OK, irq_trig_low);
	अगर (ret)
		वापस ret;

	ret = qcom_labibb_ocp_hw_enable(rdev);
	अगर (ret)
		वापस ret;

	वापस devm_request_thपढ़ोed_irq(vreg->dev, vreg->ocp_irq, शून्य,
					 qcom_labibb_ocp_isr, irq_flags,
					 ocp_irq_name, vreg);
पूर्ण

/**
 * qcom_labibb_check_sc_status - Check the Short Circuit Protection status
 * @vreg: Main driver काष्ठाure
 *
 * This function checks the STATUS1 रेजिस्टर on both LAB and IBB regulators
 * क्रम the ShortCircuit bit: अगर it is set on *any* of them, then we have
 * experienced a लघु-circuit event.
 *
 * Returns: Zero अगर there is no लघु-circuit, 1 अगर in लघु-circuit or
 *          negative number क्रम error
 */
अटल पूर्णांक qcom_labibb_check_sc_status(काष्ठा labibb_regulator *vreg)
अणु
	u32 ibb_status, ibb_reg, lab_status, lab_reg;
	पूर्णांक ret;

	/* We have to work on both regulators due to PBS... */
	lab_reg = ibb_reg = vreg->base + REG_LABIBB_STATUS1;
	अगर (vreg->type == QCOM_LAB_TYPE)
		ibb_reg -= PMI8998_IBB_LAB_REG_OFFSET;
	अन्यथा
		lab_reg += PMI8998_IBB_LAB_REG_OFFSET;

	ret = regmap_पढ़ो(vreg->rdev->regmap, lab_reg, &lab_status);
	अगर (ret)
		वापस ret;
	ret = regmap_पढ़ो(vreg->rdev->regmap, ibb_reg, &ibb_status);
	अगर (ret)
		वापस ret;

	वापस !!(lab_status & LABIBB_STATUS1_SC_BIT) ||
	       !!(ibb_status & LABIBB_STATUS1_SC_BIT);
पूर्ण

/**
 * qcom_labibb_sc_recovery_worker - Handle Short Circuit event
 * @work: SC work काष्ठाure
 *
 * This is the worker function to handle the Short Circuit Protection
 * hardware event; This will check अगर the hardware is still
 * संकेतing a लघु-circuit condition and will eventually never
 * re-enable the regulator अगर such condition is still संकेतed after
 * LABIBB_MAX_SC_COUNT बार.
 *
 * If the driver that is consuming the regulator did not take action
 * क्रम the SC condition, or the hardware did not stabilize, this
 * worker will stop rescheduling, leaving the regulators disabled
 * as alपढ़ोy करोne by the Portable Batch System (PBS).
 *
 * Returns: IRQ_HANDLED क्रम success or IRQ_NONE क्रम failure.
 */
अटल व्योम qcom_labibb_sc_recovery_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा labibb_regulator *vreg;
	स्थिर काष्ठा regulator_ops *ops;
	u32 lab_reg, ibb_reg, lab_val, ibb_val, val;
	bool pbs_cut = false;
	पूर्णांक i, sc, ret;

	vreg = container_of(work, काष्ठा labibb_regulator,
			    sc_recovery_work.work);
	ops = vreg->rdev->desc->ops;

	/*
	 * If we tried to check the regulator status multiple बार but we
	 * kept failing, then just bail out, as the Portable Batch System
	 * (PBS) will disable the vregs क्रम us, preventing hardware damage.
	 */
	अगर (vreg->fatal_count > LABIBB_MAX_FATAL_COUNT)
		वापस;

	/* Too many लघु-circuit events. Throw in the towel. */
	अगर (vreg->sc_count > LABIBB_MAX_SC_COUNT)
		वापस;

	/*
	 * The Portable Batch System (PBS) स्वतःmatically disables LAB
	 * and IBB when a लघु-circuit event is detected, so we have to
	 * check and work on both of them at the same समय.
	 */
	lab_reg = ibb_reg = vreg->base + REG_LABIBB_ENABLE_CTL;
	अगर (vreg->type == QCOM_LAB_TYPE)
		ibb_reg -= PMI8998_IBB_LAB_REG_OFFSET;
	अन्यथा
		lab_reg += PMI8998_IBB_LAB_REG_OFFSET;

	sc = qcom_labibb_check_sc_status(vreg);
	अगर (sc)
		जाओ reschedule;

	क्रम (i = 0; i < LABIBB_MAX_SC_COUNT; i++) अणु
		ret = regmap_पढ़ो(vreg->regmap, lab_reg, &lab_val);
		अगर (ret) अणु
			vreg->fatal_count++;
			जाओ reschedule;
		पूर्ण

		ret = regmap_पढ़ो(vreg->regmap, ibb_reg, &ibb_val);
		अगर (ret) अणु
			vreg->fatal_count++;
			जाओ reschedule;
		पूर्ण
		val = lab_val & ibb_val;

		अगर (!(val & LABIBB_CONTROL_ENABLE)) अणु
			pbs_cut = true;
			अवरोध;
		पूर्ण
		usleep_range(5000, 6000);
	पूर्ण
	अगर (pbs_cut)
		जाओ reschedule;


	/*
	 * If we have reached this poपूर्णांक, we either have successfully
	 * recovered from the SC condition or we had a spurious SC IRQ,
	 * which means that we can re-enable the regulators, अगर they
	 * have ever been disabled by the PBS.
	 */
	ret = ops->enable(vreg->rdev);
	अगर (ret)
		जाओ reschedule;

	/* Everything went fine: reset the OCP count! */
	vreg->sc_count = 0;
	enable_irq(vreg->sc_irq);
	वापस;

reschedule:
	/*
	 * Now that we have करोne basic handling of the लघु-circuit,
	 * reschedule this worker in the regular प्रणाली workqueue, as
	 * taking action is not truly urgent anymore.
	 */
	vreg->sc_count++;
	mod_delayed_work(प्रणाली_wq, &vreg->sc_recovery_work,
			 msecs_to_jअगरfies(SC_RECOVERY_INTERVAL_MS));
पूर्ण

/**
 * qcom_labibb_sc_isr - Interrupt routine क्रम Short Circuit Protection
 * @irq:  Interrupt number
 * @chip: Main driver काष्ठाure
 *
 * Short Circuit Protection (SCP) will संकेत to the client driver
 * that a regulation-out event has happened and then will schedule
 * a recovery worker.
 *
 * The LAB and IBB regulators will be स्वतःmatically disabled by the
 * Portable Batch System (PBS) and they will be enabled again by
 * the worker function अगर the hardware stops संकेतing the लघु
 * circuit event.
 *
 * Returns: IRQ_HANDLED क्रम success or IRQ_NONE क्रम failure.
 */
अटल irqवापस_t qcom_labibb_sc_isr(पूर्णांक irq, व्योम *chip)
अणु
	काष्ठा labibb_regulator *vreg = chip;

	अगर (vreg->sc_count > LABIBB_MAX_SC_COUNT)
		वापस IRQ_NONE;

	/* Warn the user क्रम लघु circuit */
	dev_warn(vreg->dev, "Short-Circuit interrupt fired!\n");

	/*
	 * Disable the पूर्णांकerrupt temporarily, or it will fire continuously;
	 * we will re-enable it in the recovery worker function.
	 */
	disable_irq_nosync(irq);

	/* Signal out of regulation event to drivers */
	regulator_notअगरier_call_chain(vreg->rdev,
				      REGULATOR_EVENT_REGULATION_OUT, शून्य);

	/* Schedule the लघु-circuit handling as high-priority work */
	mod_delayed_work(प्रणाली_highpri_wq, &vreg->sc_recovery_work,
			 msecs_to_jअगरfies(SC_RECOVERY_INTERVAL_MS));
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक qcom_labibb_set_current_limit(काष्ठा regulator_dev *rdev,
					 पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);
	काष्ठा regulator_desc *desc = &vreg->desc;
	काष्ठा labibb_current_limits *lim = &vreg->uA_limits;
	u32 mask, val;
	पूर्णांक i, ret, sel = -1;

	अगर (min_uA < lim->uA_min || max_uA < lim->uA_min)
		वापस -EINVAL;

	क्रम (i = 0; i < desc->n_current_limits; i++) अणु
		पूर्णांक uA_limit = (lim->uA_step * i) + lim->uA_min;

		अगर (max_uA >= uA_limit && min_uA <= uA_limit)
			sel = i;
	पूर्ण
	अगर (sel < 0)
		वापस -EINVAL;

	/* Current limit setting needs secure access */
	ret = regmap_ग_लिखो(vreg->regmap, vreg->base + REG_LABIBB_SEC_ACCESS,
			   LABIBB_SEC_UNLOCK_CODE);
	अगर (ret)
		वापस ret;

	mask = desc->csel_mask | lim->ovr_val;
	mask |= LABIBB_CURRENT_LIMIT_EN;
	val = (u32)sel | lim->ovr_val;
	val |= LABIBB_CURRENT_LIMIT_EN;

	वापस regmap_update_bits(vreg->regmap, desc->csel_reg, mask, val);
पूर्ण

अटल पूर्णांक qcom_labibb_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);
	काष्ठा regulator_desc *desc = &vreg->desc;
	काष्ठा labibb_current_limits *lim = &vreg->uA_limits;
	अचिन्हित पूर्णांक cur_step;
	पूर्णांक ret;

	ret = regmap_पढ़ो(vreg->regmap, desc->csel_reg, &cur_step);
	अगर (ret)
		वापस ret;
	cur_step &= desc->csel_mask;

	वापस (cur_step * lim->uA_step) + lim->uA_min;
पूर्ण

अटल पूर्णांक qcom_labibb_set_soft_start(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा labibb_regulator *vreg = rdev_get_drvdata(rdev);
	u32 val = 0;

	अगर (vreg->type == QCOM_IBB_TYPE)
		val = vreg->dischg_sel;
	अन्यथा
		val = vreg->soft_start_sel;

	वापस regmap_ग_लिखो(rdev->regmap, rdev->desc->soft_start_reg, val);
पूर्ण

अटल पूर्णांक qcom_labibb_get_table_sel(स्थिर पूर्णांक *table, पूर्णांक sz, u32 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sz; i++)
		अगर (table[i] == value)
			वापस i;
	वापस -EINVAL;
पूर्ण

/* IBB disअक्षरge resistor values in KOhms */
अटल स्थिर पूर्णांक dischg_resistor_values[] = अणु 300, 64, 32, 16 पूर्ण;

/* Soft start समय in microseconds */
अटल स्थिर पूर्णांक soft_start_values[] = अणु 200, 400, 600, 800 पूर्ण;

अटल पूर्णांक qcom_labibb_of_parse_cb(काष्ठा device_node *np,
				   स्थिर काष्ठा regulator_desc *desc,
				   काष्ठा regulator_config *config)
अणु
	काष्ठा labibb_regulator *vreg = config->driver_data;
	u32 dischg_kohms, soft_start_समय;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "qcom,discharge-resistor-kohms",
				       &dischg_kohms);
	अगर (ret)
		dischg_kohms = 300;

	ret = qcom_labibb_get_table_sel(dischg_resistor_values,
					ARRAY_SIZE(dischg_resistor_values),
					dischg_kohms);
	अगर (ret < 0)
		वापस ret;
	vreg->dischg_sel = (u8)ret;

	ret = of_property_पढ़ो_u32(np, "qcom,soft-start-us",
				   &soft_start_समय);
	अगर (ret)
		soft_start_समय = 200;

	ret = qcom_labibb_get_table_sel(soft_start_values,
					ARRAY_SIZE(soft_start_values),
					soft_start_समय);
	अगर (ret < 0)
		वापस ret;
	vreg->soft_start_sel = (u8)ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops qcom_labibb_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
	.set_pull_करोwn		= regulator_set_pull_करोwn_regmap,
	.set_current_limit	= qcom_labibb_set_current_limit,
	.get_current_limit	= qcom_labibb_get_current_limit,
	.set_soft_start		= qcom_labibb_set_soft_start,
	.set_over_current_protection = qcom_labibb_set_ocp,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8998_lab_desc = अणु
	.enable_mask		= LAB_ENABLE_CTL_MASK,
	.enable_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_ENABLE_CTL),
	.enable_val		= LABIBB_CONTROL_ENABLE,
	.enable_समय		= LAB_ENABLE_TIME,
	.poll_enabled_समय	= LABIBB_POLL_ENABLED_TIME,
	.soft_start_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_SOFT_START_CTL),
	.pull_करोwn_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_PD_CTL),
	.pull_करोwn_mask		= LAB_PD_CTL_MASK,
	.pull_करोwn_val_on	= LAB_PD_CTL_STRONG_PULL,
	.vsel_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_VOLTAGE),
	.vsel_mask		= LAB_VOLTAGE_SET_MASK,
	.apply_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_VOLTAGE),
	.apply_bit		= LABIBB_VOLTAGE_OVERRIDE_EN,
	.csel_reg		= (PMI8998_LAB_REG_BASE + REG_LABIBB_CURRENT_LIMIT),
	.csel_mask		= LAB_CURRENT_LIMIT_MASK,
	.n_current_limits	= 8,
	.off_on_delay		= LABIBB_OFF_ON_DELAY,
	.owner			= THIS_MODULE,
	.type			= REGULATOR_VOLTAGE,
	.min_uV			= 4600000,
	.uV_step		= 100000,
	.n_voltages		= 16,
	.ops			= &qcom_labibb_ops,
	.of_parse_cb		= qcom_labibb_of_parse_cb,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8998_ibb_desc = अणु
	.enable_mask		= IBB_ENABLE_CTL_MASK,
	.enable_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_ENABLE_CTL),
	.enable_val		= LABIBB_CONTROL_ENABLE,
	.enable_समय		= IBB_ENABLE_TIME,
	.poll_enabled_समय	= LABIBB_POLL_ENABLED_TIME,
	.soft_start_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_SOFT_START_CTL),
	.active_disअक्षरge_off	= 0,
	.active_disअक्षरge_on	= IBB_CTL_1_DISCHARGE_EN,
	.active_disअक्षरge_mask	= IBB_CTL_1_DISCHARGE_EN,
	.active_disअक्षरge_reg	= (PMI8998_IBB_REG_BASE + REG_IBB_PWRUP_PWRDN_CTL_1),
	.pull_करोwn_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_PD_CTL),
	.pull_करोwn_mask		= IBB_PD_CTL_MASK,
	.pull_करोwn_val_on	= IBB_PD_CTL_HALF_STRENGTH | IBB_PD_CTL_EN,
	.vsel_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_VOLTAGE),
	.vsel_mask		= IBB_VOLTAGE_SET_MASK,
	.apply_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_VOLTAGE),
	.apply_bit		= LABIBB_VOLTAGE_OVERRIDE_EN,
	.csel_reg		= (PMI8998_IBB_REG_BASE + REG_LABIBB_CURRENT_LIMIT),
	.csel_mask		= IBB_CURRENT_LIMIT_MASK,
	.n_current_limits	= 32,
	.off_on_delay		= LABIBB_OFF_ON_DELAY,
	.owner			= THIS_MODULE,
	.type			= REGULATOR_VOLTAGE,
	.min_uV			= 1400000,
	.uV_step		= 100000,
	.n_voltages		= 64,
	.ops			= &qcom_labibb_ops,
	.of_parse_cb		= qcom_labibb_of_parse_cb,
पूर्ण;

अटल स्थिर काष्ठा labibb_regulator_data pmi8998_labibb_data[] = अणु
	अणु"lab", QCOM_LAB_TYPE, PMI8998_LAB_REG_BASE, &pmi8998_lab_descपूर्ण,
	अणु"ibb", QCOM_IBB_TYPE, PMI8998_IBB_REG_BASE, &pmi8998_ibb_descपूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_labibb_match[] = अणु
	अणु .compatible = "qcom,pmi8998-lab-ibb", .data = &pmi8998_labibb_dataपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_labibb_match);

अटल पूर्णांक qcom_labibb_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा labibb_regulator *vreg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_config cfg = अणुपूर्ण;
	काष्ठा device_node *reg_node;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा labibb_regulator_data *reg_data;
	काष्ठा regmap *reg_regmap;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	reg_regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!reg_regmap) अणु
		dev_err(&pdev->dev, "Couldn't get parent's regmap\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_device(qcom_labibb_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	क्रम (reg_data = match->data; reg_data->name; reg_data++) अणु
		अक्षर *sc_irq_name;
		पूर्णांक irq = 0;

		/* Validate अगर the type of regulator is indeed
		 * what's mentioned in DT.
		 */
		ret = regmap_पढ़ो(reg_regmap, reg_data->base + REG_PERPH_TYPE,
				  &type);
		अगर (ret < 0) अणु
			dev_err(dev,
				"Peripheral type read failed ret=%d\n",
				ret);
			वापस -EINVAL;
		पूर्ण

		अगर (WARN_ON((type != QCOM_LAB_TYPE) && (type != QCOM_IBB_TYPE)) ||
		    WARN_ON(type != reg_data->type))
			वापस -EINVAL;

		vreg  = devm_kzalloc(&pdev->dev, माप(*vreg),
					   GFP_KERNEL);
		अगर (!vreg)
			वापस -ENOMEM;

		sc_irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					     "%s-short-circuit",
					     reg_data->name);
		अगर (!sc_irq_name)
			वापस -ENOMEM;

		reg_node = of_get_child_by_name(pdev->dev.of_node,
						reg_data->name);
		अगर (!reg_node)
			वापस -EINVAL;

		/* The Short Circuit पूर्णांकerrupt is critical */
		irq = of_irq_get_byname(reg_node, "sc-err");
		अगर (irq <= 0) अणु
			अगर (irq == 0)
				irq = -EINVAL;

			वापस dev_err_probe(vreg->dev, irq,
					     "Short-circuit irq not found.\n");
		पूर्ण
		vreg->sc_irq = irq;

		/* OverCurrent Protection IRQ is optional */
		irq = of_irq_get_byname(reg_node, "ocp");
		vreg->ocp_irq = irq;
		vreg->ocp_irq_count = 0;
		of_node_put(reg_node);

		vreg->regmap = reg_regmap;
		vreg->dev = dev;
		vreg->base = reg_data->base;
		vreg->type = reg_data->type;
		INIT_DELAYED_WORK(&vreg->sc_recovery_work,
				  qcom_labibb_sc_recovery_worker);

		अगर (vreg->ocp_irq > 0)
			INIT_DELAYED_WORK(&vreg->ocp_recovery_work,
					  qcom_labibb_ocp_recovery_worker);

		चयन (vreg->type) अणु
		हाल QCOM_LAB_TYPE:
			/* LAB Limits: 200-1600mA */
			vreg->uA_limits.uA_min  = 200000;
			vreg->uA_limits.uA_step = 200000;
			vreg->uA_limits.ovr_val = LAB_CURRENT_LIMIT_OVERRIDE_EN;
			अवरोध;
		हाल QCOM_IBB_TYPE:
			/* IBB Limits: 0-1550mA */
			vreg->uA_limits.uA_min  = 0;
			vreg->uA_limits.uA_step = 50000;
			vreg->uA_limits.ovr_val = 0; /* No override bit */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		स_नकल(&vreg->desc, reg_data->desc, माप(vreg->desc));
		vreg->desc.of_match = reg_data->name;
		vreg->desc.name = reg_data->name;

		cfg.dev = vreg->dev;
		cfg.driver_data = vreg;
		cfg.regmap = vreg->regmap;

		vreg->rdev = devm_regulator_रेजिस्टर(vreg->dev, &vreg->desc,
							&cfg);

		अगर (IS_ERR(vreg->rdev)) अणु
			dev_err(dev, "qcom_labibb: error registering %s : %d\n",
					reg_data->name, ret);
			वापस PTR_ERR(vreg->rdev);
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(vreg->dev, vreg->sc_irq, शून्य,
						qcom_labibb_sc_isr,
						IRQF_ONESHOT |
						IRQF_TRIGGER_RISING,
						sc_irq_name, vreg);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_labibb_regulator_driver = अणु
	.driver	= अणु
		.name = "qcom-lab-ibb-regulator",
		.of_match_table	= qcom_labibb_match,
	पूर्ण,
	.probe = qcom_labibb_regulator_probe,
पूर्ण;
module_platक्रमm_driver(qcom_labibb_regulator_driver);

MODULE_DESCRIPTION("Qualcomm labibb driver");
MODULE_AUTHOR("Nisha Kumari <nishakumari@codeaurora.org>");
MODULE_AUTHOR("Sumit Semwal <sumit.semwal@linaro.org>");
MODULE_LICENSE("GPL v2");
