<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPIC समयr wakeup driver
 *
 * Copyright 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/mpic_समयr.h>
#समावेश <यंत्र/mpic.h>

काष्ठा fsl_mpic_समयr_wakeup अणु
	काष्ठा mpic_समयr *समयr;
	काष्ठा work_काष्ठा मुक्त_work;
पूर्ण;

अटल काष्ठा fsl_mpic_समयr_wakeup *fsl_wakeup;
अटल DEFINE_MUTEX(sysfs_lock);

अटल व्योम fsl_मुक्त_resource(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा fsl_mpic_समयr_wakeup *wakeup =
		container_of(ws, काष्ठा fsl_mpic_समयr_wakeup, मुक्त_work);

	mutex_lock(&sysfs_lock);

	अगर (wakeup->समयr) अणु
		disable_irq_wake(wakeup->समयr->irq);
		mpic_मुक्त_समयr(wakeup->समयr);
	पूर्ण

	wakeup->समयr = शून्य;
	mutex_unlock(&sysfs_lock);
पूर्ण

अटल irqवापस_t fsl_mpic_समयr_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_mpic_समयr_wakeup *wakeup = dev_id;

	schedule_work(&wakeup->मुक्त_work);

	वापस wakeup->समयr ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल sमाप_प्रकार fsl_समयr_wakeup_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	समय64_t पूर्णांकerval = 0;

	mutex_lock(&sysfs_lock);
	अगर (fsl_wakeup->समयr) अणु
		mpic_get_reमुख्य_समय(fsl_wakeup->समयr, &पूर्णांकerval);
		पूर्णांकerval++;
	पूर्ण
	mutex_unlock(&sysfs_lock);

	वापस प्र_लिखो(buf, "%lld\n", पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार fsl_समयr_wakeup_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	समय64_t पूर्णांकerval;
	पूर्णांक ret;

	अगर (kम_से_दीर्घl(buf, 0, &पूर्णांकerval))
		वापस -EINVAL;

	mutex_lock(&sysfs_lock);

	अगर (fsl_wakeup->समयr) अणु
		disable_irq_wake(fsl_wakeup->समयr->irq);
		mpic_मुक्त_समयr(fsl_wakeup->समयr);
		fsl_wakeup->समयr = शून्य;
	पूर्ण

	अगर (!पूर्णांकerval) अणु
		mutex_unlock(&sysfs_lock);
		वापस count;
	पूर्ण

	fsl_wakeup->समयr = mpic_request_समयr(fsl_mpic_समयr_irq,
						fsl_wakeup, पूर्णांकerval);
	अगर (!fsl_wakeup->समयr) अणु
		mutex_unlock(&sysfs_lock);
		वापस -EINVAL;
	पूर्ण

	ret = enable_irq_wake(fsl_wakeup->समयr->irq);
	अगर (ret) अणु
		mpic_मुक्त_समयr(fsl_wakeup->समयr);
		fsl_wakeup->समयr = शून्य;
		mutex_unlock(&sysfs_lock);

		वापस ret;
	पूर्ण

	mpic_start_समयr(fsl_wakeup->समयr);

	mutex_unlock(&sysfs_lock);

	वापस count;
पूर्ण

अटल काष्ठा device_attribute mpic_attributes = __ATTR(समयr_wakeup, 0644,
			fsl_समयr_wakeup_show, fsl_समयr_wakeup_store);

अटल पूर्णांक __init fsl_wakeup_sys_init(व्योम)
अणु
	पूर्णांक ret;

	fsl_wakeup = kzalloc(माप(काष्ठा fsl_mpic_समयr_wakeup), GFP_KERNEL);
	अगर (!fsl_wakeup)
		वापस -ENOMEM;

	INIT_WORK(&fsl_wakeup->मुक्त_work, fsl_मुक्त_resource);

	ret = device_create_file(mpic_subsys.dev_root, &mpic_attributes);
	अगर (ret)
		kमुक्त(fsl_wakeup);

	वापस ret;
पूर्ण

अटल व्योम __निकास fsl_wakeup_sys_निकास(व्योम)
अणु
	device_हटाओ_file(mpic_subsys.dev_root, &mpic_attributes);

	mutex_lock(&sysfs_lock);

	अगर (fsl_wakeup->समयr) अणु
		disable_irq_wake(fsl_wakeup->समयr->irq);
		mpic_मुक्त_समयr(fsl_wakeup->समयr);
	पूर्ण

	kमुक्त(fsl_wakeup);

	mutex_unlock(&sysfs_lock);
पूर्ण

module_init(fsl_wakeup_sys_init);
module_निकास(fsl_wakeup_sys_निकास);

MODULE_DESCRIPTION("Freescale MPIC global timer wakeup driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Wang Dongsheng <dongsheng.wang@freescale.com>");
