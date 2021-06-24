<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2014 Intel Corporation
 *
 * Authors:
 * Jarkko Sakkinen <jarkko.sakkinen@linux.पूर्णांकel.com>
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * TPM chip management routines.
 */

#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/major.h>
#समावेश <linux/tpm_eventlog.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश "tpm.h"

DEFINE_IDR(dev_nums_idr);
अटल DEFINE_MUTEX(idr_lock);

काष्ठा class *tpm_class;
काष्ठा class *tpmrm_class;
dev_t tpm_devt;

अटल पूर्णांक tpm_request_locality(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	अगर (!chip->ops->request_locality)
		वापस 0;

	rc = chip->ops->request_locality(chip, 0);
	अगर (rc < 0)
		वापस rc;

	chip->locality = rc;
	वापस 0;
पूर्ण

अटल व्योम tpm_relinquish_locality(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	अगर (!chip->ops->relinquish_locality)
		वापस;

	rc = chip->ops->relinquish_locality(chip, chip->locality);
	अगर (rc)
		dev_err(&chip->dev, "%s: : error %d\n", __func__, rc);

	chip->locality = -1;
पूर्ण

अटल पूर्णांक tpm_cmd_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	अगर (!chip->ops->cmd_पढ़ोy)
		वापस 0;

	वापस chip->ops->cmd_पढ़ोy(chip);
पूर्ण

अटल पूर्णांक tpm_go_idle(काष्ठा tpm_chip *chip)
अणु
	अगर (!chip->ops->go_idle)
		वापस 0;

	वापस chip->ops->go_idle(chip);
पूर्ण

अटल व्योम tpm_clk_enable(काष्ठा tpm_chip *chip)
अणु
	अगर (chip->ops->clk_enable)
		chip->ops->clk_enable(chip, true);
पूर्ण

अटल व्योम tpm_clk_disable(काष्ठा tpm_chip *chip)
अणु
	अगर (chip->ops->clk_enable)
		chip->ops->clk_enable(chip, false);
पूर्ण

/**
 * tpm_chip_start() - घातer on the TPM
 * @chip:	a TPM chip to use
 *
 * Return:
 * * The response length	- OK
 * * -त्रुटि_सं			- A प्रणाली error
 */
पूर्णांक tpm_chip_start(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक ret;

	tpm_clk_enable(chip);

	अगर (chip->locality == -1) अणु
		ret = tpm_request_locality(chip);
		अगर (ret) अणु
			tpm_clk_disable(chip);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = tpm_cmd_पढ़ोy(chip);
	अगर (ret) अणु
		tpm_relinquish_locality(chip);
		tpm_clk_disable(chip);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_chip_start);

/**
 * tpm_chip_stop() - घातer off the TPM
 * @chip:	a TPM chip to use
 *
 * Return:
 * * The response length	- OK
 * * -त्रुटि_सं			- A प्रणाली error
 */
व्योम tpm_chip_stop(काष्ठा tpm_chip *chip)
अणु
	tpm_go_idle(chip);
	tpm_relinquish_locality(chip);
	tpm_clk_disable(chip);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_chip_stop);

/**
 * tpm_try_get_ops() - Get a ref to the tpm_chip
 * @chip: Chip to ref
 *
 * The caller must alपढ़ोy have some kind of locking to ensure that chip is
 * valid. This function will lock the chip so that the ops member can be
 * accessed safely. The locking prevents tpm_chip_unरेजिस्टर from
 * completing, so it should not be held क्रम दीर्घ periods.
 *
 * Returns -ERRNO अगर the chip could not be got.
 */
पूर्णांक tpm_try_get_ops(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc = -EIO;

	get_device(&chip->dev);

	करोwn_पढ़ो(&chip->ops_sem);
	अगर (!chip->ops)
		जाओ out_ops;

	mutex_lock(&chip->tpm_mutex);
	rc = tpm_chip_start(chip);
	अगर (rc)
		जाओ out_lock;

	वापस 0;
out_lock:
	mutex_unlock(&chip->tpm_mutex);
out_ops:
	up_पढ़ो(&chip->ops_sem);
	put_device(&chip->dev);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_try_get_ops);

/**
 * tpm_put_ops() - Release a ref to the tpm_chip
 * @chip: Chip to put
 *
 * This is the opposite pair to tpm_try_get_ops(). After this वापसs chip may
 * be kमुक्त'd.
 */
व्योम tpm_put_ops(काष्ठा tpm_chip *chip)
अणु
	tpm_chip_stop(chip);
	mutex_unlock(&chip->tpm_mutex);
	up_पढ़ो(&chip->ops_sem);
	put_device(&chip->dev);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_put_ops);

/**
 * tpm_शेष_chip() - find a TPM chip and get a reference to it
 */
काष्ठा tpm_chip *tpm_शेष_chip(व्योम)
अणु
	काष्ठा tpm_chip *chip, *res = शून्य;
	पूर्णांक chip_num = 0;
	पूर्णांक chip_prev;

	mutex_lock(&idr_lock);

	करो अणु
		chip_prev = chip_num;
		chip = idr_get_next(&dev_nums_idr, &chip_num);
		अगर (chip) अणु
			get_device(&chip->dev);
			res = chip;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (chip_prev != chip_num);

	mutex_unlock(&idr_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_शेष_chip);

/**
 * tpm_find_get_ops() - find and reserve a TPM chip
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 *
 * Finds a TPM chip and reserves its class device and operations. The chip must
 * be released with tpm_put_ops() after use.
 * This function is क्रम पूर्णांकernal use only. It supports existing TPM callers
 * by accepting शून्य, but those callers should be converted to pass in a chip
 * directly.
 *
 * Return:
 * A reserved &काष्ठा tpm_chip instance.
 * %शून्य अगर a chip is not found.
 * %शून्य अगर the chip is not available.
 */
काष्ठा tpm_chip *tpm_find_get_ops(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	अगर (chip) अणु
		अगर (!tpm_try_get_ops(chip))
			वापस chip;
		वापस शून्य;
	पूर्ण

	chip = tpm_शेष_chip();
	अगर (!chip)
		वापस शून्य;
	rc = tpm_try_get_ops(chip);
	/* release additional reference we got from tpm_शेष_chip() */
	put_device(&chip->dev);
	अगर (rc)
		वापस शून्य;
	वापस chip;
पूर्ण

/**
 * tpm_dev_release() - मुक्त chip memory and the device number
 * @dev: the अक्षरacter device क्रम the TPM chip
 *
 * This is used as the release function क्रम the अक्षरacter device.
 */
अटल व्योम tpm_dev_release(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = container_of(dev, काष्ठा tpm_chip, dev);

	mutex_lock(&idr_lock);
	idr_हटाओ(&dev_nums_idr, chip->dev_num);
	mutex_unlock(&idr_lock);

	kमुक्त(chip->log.bios_event_log);
	kमुक्त(chip->work_space.context_buf);
	kमुक्त(chip->work_space.session_buf);
	kमुक्त(chip->allocated_banks);
	kमुक्त(chip);
पूर्ण

अटल व्योम tpm_devs_release(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = container_of(dev, काष्ठा tpm_chip, devs);

	/* release the master device reference */
	put_device(&chip->dev);
पूर्ण

/**
 * tpm_class_shutकरोwn() - prepare the TPM device क्रम loss of घातer.
 * @dev: device to which the chip is associated.
 *
 * Issues a TPM2_Shutकरोwn command prior to loss of घातer, as required by the
 * TPM 2.0 spec. Then, calls bus- and device- specअगरic shutकरोwn code.
 *
 * Return: always 0 (i.e. success)
 */
अटल पूर्णांक tpm_class_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = container_of(dev, काष्ठा tpm_chip, dev);

	करोwn_ग_लिखो(&chip->ops_sem);
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		अगर (!tpm_chip_start(chip)) अणु
			tpm2_shutकरोwn(chip, TPM2_SU_CLEAR);
			tpm_chip_stop(chip);
		पूर्ण
	पूर्ण
	chip->ops = शून्य;
	up_ग_लिखो(&chip->ops_sem);

	वापस 0;
पूर्ण

/**
 * tpm_chip_alloc() - allocate a new काष्ठा tpm_chip instance
 * @pdev: device to which the chip is associated
 *        At this poपूर्णांक pdev mst be initialized, but करोes not have to
 *        be रेजिस्टरed
 * @ops: काष्ठा tpm_class_ops instance
 *
 * Allocates a new काष्ठा tpm_chip instance and assigns a मुक्त
 * device number क्रम it. Must be paired with put_device(&chip->dev).
 */
काष्ठा tpm_chip *tpm_chip_alloc(काष्ठा device *pdev,
				स्थिर काष्ठा tpm_class_ops *ops)
अणु
	काष्ठा tpm_chip *chip;
	पूर्णांक rc;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&chip->tpm_mutex);
	init_rwsem(&chip->ops_sem);

	chip->ops = ops;

	mutex_lock(&idr_lock);
	rc = idr_alloc(&dev_nums_idr, शून्य, 0, TPM_NUM_DEVICES, GFP_KERNEL);
	mutex_unlock(&idr_lock);
	अगर (rc < 0) अणु
		dev_err(pdev, "No available tpm device numbers\n");
		kमुक्त(chip);
		वापस ERR_PTR(rc);
	पूर्ण
	chip->dev_num = rc;

	device_initialize(&chip->dev);
	device_initialize(&chip->devs);

	chip->dev.class = tpm_class;
	chip->dev.class->shutकरोwn_pre = tpm_class_shutकरोwn;
	chip->dev.release = tpm_dev_release;
	chip->dev.parent = pdev;
	chip->dev.groups = chip->groups;

	chip->devs.parent = pdev;
	chip->devs.class = tpmrm_class;
	chip->devs.release = tpm_devs_release;
	/* get extra reference on मुख्य device to hold on
	 * behalf of devs.  This holds the chip काष्ठाure
	 * जबतक cdevs is in use.  The corresponding put
	 * is in the tpm_devs_release (TPM2 only)
	 */
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		get_device(&chip->dev);

	अगर (chip->dev_num == 0)
		chip->dev.devt = MKDEV(MISC_MAJOR, TPM_MINOR);
	अन्यथा
		chip->dev.devt = MKDEV(MAJOR(tpm_devt), chip->dev_num);

	chip->devs.devt =
		MKDEV(MAJOR(tpm_devt), chip->dev_num + TPM_NUM_DEVICES);

	rc = dev_set_name(&chip->dev, "tpm%d", chip->dev_num);
	अगर (rc)
		जाओ out;
	rc = dev_set_name(&chip->devs, "tpmrm%d", chip->dev_num);
	अगर (rc)
		जाओ out;

	अगर (!pdev)
		chip->flags |= TPM_CHIP_FLAG_VIRTUAL;

	cdev_init(&chip->cdev, &tpm_fops);
	cdev_init(&chip->cdevs, &tpmrm_fops);
	chip->cdev.owner = THIS_MODULE;
	chip->cdevs.owner = THIS_MODULE;

	rc = tpm2_init_space(&chip->work_space, TPM2_SPACE_BUFFER_SIZE);
	अगर (rc) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	chip->locality = -1;
	वापस chip;

out:
	put_device(&chip->devs);
	put_device(&chip->dev);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_chip_alloc);

/**
 * tpmm_chip_alloc() - allocate a new काष्ठा tpm_chip instance
 * @pdev: parent device to which the chip is associated
 * @ops: काष्ठा tpm_class_ops instance
 *
 * Same as tpm_chip_alloc except devm is used to करो the put_device
 */
काष्ठा tpm_chip *tpmm_chip_alloc(काष्ठा device *pdev,
				 स्थिर काष्ठा tpm_class_ops *ops)
अणु
	काष्ठा tpm_chip *chip;
	पूर्णांक rc;

	chip = tpm_chip_alloc(pdev, ops);
	अगर (IS_ERR(chip))
		वापस chip;

	rc = devm_add_action_or_reset(pdev,
				      (व्योम (*)(व्योम *)) put_device,
				      &chip->dev);
	अगर (rc)
		वापस ERR_PTR(rc);

	dev_set_drvdata(pdev, chip);

	वापस chip;
पूर्ण
EXPORT_SYMBOL_GPL(tpmm_chip_alloc);

अटल पूर्णांक tpm_add_अक्षर_device(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	rc = cdev_device_add(&chip->cdev, &chip->dev);
	अगर (rc) अणु
		dev_err(&chip->dev,
			"unable to cdev_device_add() %s, major %d, minor %d, err=%d\n",
			dev_name(&chip->dev), MAJOR(chip->dev.devt),
			MINOR(chip->dev.devt), rc);
		वापस rc;
	पूर्ण

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		rc = cdev_device_add(&chip->cdevs, &chip->devs);
		अगर (rc) अणु
			dev_err(&chip->devs,
				"unable to cdev_device_add() %s, major %d, minor %d, err=%d\n",
				dev_name(&chip->devs), MAJOR(chip->devs.devt),
				MINOR(chip->devs.devt), rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Make the chip available. */
	mutex_lock(&idr_lock);
	idr_replace(&dev_nums_idr, chip, chip->dev_num);
	mutex_unlock(&idr_lock);

	वापस rc;
पूर्ण

अटल व्योम tpm_del_अक्षर_device(काष्ठा tpm_chip *chip)
अणु
	cdev_device_del(&chip->cdev, &chip->dev);

	/* Make the chip unavailable. */
	mutex_lock(&idr_lock);
	idr_replace(&dev_nums_idr, शून्य, chip->dev_num);
	mutex_unlock(&idr_lock);

	/* Make the driver uncallable. */
	करोwn_ग_लिखो(&chip->ops_sem);
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		अगर (!tpm_chip_start(chip)) अणु
			tpm2_shutकरोwn(chip, TPM2_SU_CLEAR);
			tpm_chip_stop(chip);
		पूर्ण
	पूर्ण
	chip->ops = शून्य;
	up_ग_लिखो(&chip->ops_sem);
पूर्ण

अटल व्योम tpm_del_legacy_sysfs(काष्ठा tpm_chip *chip)
अणु
	काष्ठा attribute **i;

	अगर (chip->flags & (TPM_CHIP_FLAG_TPM2 | TPM_CHIP_FLAG_VIRTUAL))
		वापस;

	sysfs_हटाओ_link(&chip->dev.parent->kobj, "ppi");

	क्रम (i = chip->groups[0]->attrs; *i != शून्य; ++i)
		sysfs_हटाओ_link(&chip->dev.parent->kobj, (*i)->name);
पूर्ण

/* For compatibility with legacy sysfs paths we provide symlinks from the
 * parent dev directory to selected names within the tpm chip directory. Old
 * kernel versions created these files directly under the parent.
 */
अटल पूर्णांक tpm_add_legacy_sysfs(काष्ठा tpm_chip *chip)
अणु
	काष्ठा attribute **i;
	पूर्णांक rc;

	अगर (chip->flags & (TPM_CHIP_FLAG_TPM2 | TPM_CHIP_FLAG_VIRTUAL))
		वापस 0;

	rc = compat_only_sysfs_link_entry_to_kobj(
		    &chip->dev.parent->kobj, &chip->dev.kobj, "ppi", शून्य);
	अगर (rc && rc != -ENOENT)
		वापस rc;

	/* All the names from tpm-sysfs */
	क्रम (i = chip->groups[0]->attrs; *i != शून्य; ++i) अणु
		rc = compat_only_sysfs_link_entry_to_kobj(
		    &chip->dev.parent->kobj, &chip->dev.kobj, (*i)->name, शून्य);
		अगर (rc) अणु
			tpm_del_legacy_sysfs(chip);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_hwrng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा tpm_chip *chip = container_of(rng, काष्ठा tpm_chip, hwrng);

	वापस tpm_get_अक्रमom(chip, data, max);
पूर्ण

अटल पूर्णांक tpm_add_hwrng(काष्ठा tpm_chip *chip)
अणु
	अगर (!IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		वापस 0;

	snम_लिखो(chip->hwrng_name, माप(chip->hwrng_name),
		 "tpm-rng-%d", chip->dev_num);
	chip->hwrng.name = chip->hwrng_name;
	chip->hwrng.पढ़ो = tpm_hwrng_पढ़ो;
	वापस hwrng_रेजिस्टर(&chip->hwrng);
पूर्ण

अटल पूर्णांक tpm_get_pcr_allocation(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	rc = (chip->flags & TPM_CHIP_FLAG_TPM2) ?
	     tpm2_get_pcr_allocation(chip) :
	     tpm1_get_pcr_allocation(chip);

	अगर (rc > 0)
		वापस -ENODEV;

	वापस rc;
पूर्ण

/*
 * tpm_chip_रेजिस्टर() - create a अक्षरacter device क्रम the TPM chip
 * @chip: TPM chip to use.
 *
 * Creates a अक्षरacter device क्रम the TPM chip and adds sysfs attributes क्रम
 * the device. As the last step this function adds the chip to the list of TPM
 * chips available क्रम in-kernel use.
 *
 * This function should be only called after the chip initialization is
 * complete.
 */
पूर्णांक tpm_chip_रेजिस्टर(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	rc = tpm_chip_start(chip);
	अगर (rc)
		वापस rc;
	rc = tpm_स्वतः_startup(chip);
	अगर (rc) अणु
		tpm_chip_stop(chip);
		वापस rc;
	पूर्ण

	rc = tpm_get_pcr_allocation(chip);
	tpm_chip_stop(chip);
	अगर (rc)
		वापस rc;

	tpm_sysfs_add_device(chip);

	tpm_bios_log_setup(chip);

	tpm_add_ppi(chip);

	rc = tpm_add_hwrng(chip);
	अगर (rc)
		जाओ out_ppi;

	rc = tpm_add_अक्षर_device(chip);
	अगर (rc)
		जाओ out_hwrng;

	rc = tpm_add_legacy_sysfs(chip);
	अगर (rc) अणु
		tpm_chip_unरेजिस्टर(chip);
		वापस rc;
	पूर्ण

	वापस 0;

out_hwrng:
	अगर (IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		hwrng_unरेजिस्टर(&chip->hwrng);
out_ppi:
	tpm_bios_log_tearकरोwn(chip);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_chip_रेजिस्टर);

/*
 * tpm_chip_unरेजिस्टर() - release the TPM driver
 * @chip: TPM chip to use.
 *
 * Takes the chip first away from the list of available TPM chips and then
 * cleans up all the resources reserved by tpm_chip_रेजिस्टर().
 *
 * Once this function वापसs the driver call backs in 'op's will not be
 * running and will no दीर्घer start.
 *
 * NOTE: This function should be only called beक्रमe deinitializing chip
 * resources.
 */
व्योम tpm_chip_unरेजिस्टर(काष्ठा tpm_chip *chip)
अणु
	tpm_del_legacy_sysfs(chip);
	अगर (IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		hwrng_unरेजिस्टर(&chip->hwrng);
	tpm_bios_log_tearकरोwn(chip);
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		cdev_device_del(&chip->cdevs, &chip->devs);
	tpm_del_अक्षर_device(chip);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_chip_unरेजिस्टर);
