<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic push-चयन framework
 *
 * Copyright (C) 2006  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/push-चयन.h>

#घोषणा DRV_NAME "push-switch"
#घोषणा DRV_VERSION "0.1.1"

अटल sमाप_प्रकार चयन_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा push_चयन_platक्रमm_info *psw_info = dev->platक्रमm_data;
	वापस प्र_लिखो(buf, "%s\n", psw_info->name);
पूर्ण
अटल DEVICE_ATTR_RO(चयन);

अटल व्योम चयन_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा push_चयन *psw = from_समयr(psw, t, debounce);

	schedule_work(&psw->work);
पूर्ण

अटल व्योम चयन_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा push_चयन *psw = container_of(work, काष्ठा push_चयन, work);
	काष्ठा platक्रमm_device *pdev = psw->pdev;

	psw->state = 0;

	kobject_uevent(&pdev->dev.kobj, KOBJ_CHANGE);
पूर्ण

अटल पूर्णांक चयन_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा push_चयन_platक्रमm_info *psw_info;
	काष्ठा push_चयन *psw;
	पूर्णांक ret, irq;

	psw = kzalloc(माप(काष्ठा push_चयन), GFP_KERNEL);
	अगर (unlikely(!psw))
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (unlikely(irq < 0)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	psw_info = pdev->dev.platक्रमm_data;
	BUG_ON(!psw_info);

	ret = request_irq(irq, psw_info->irq_handler,
			  psw_info->irq_flags,
			  psw_info->name ? psw_info->name : DRV_NAME, pdev);
	अगर (unlikely(ret < 0))
		जाओ err;

	अगर (psw_info->name) अणु
		ret = device_create_file(&pdev->dev, &dev_attr_चयन);
		अगर (unlikely(ret)) अणु
			dev_err(&pdev->dev, "Failed creating device attrs\n");
			ret = -EINVAL;
			जाओ err_irq;
		पूर्ण
	पूर्ण

	INIT_WORK(&psw->work, चयन_work_handler);
	समयr_setup(&psw->debounce, चयन_समयr, 0);

	/* Workqueue API brain-damage */
	psw->pdev = pdev;

	platक्रमm_set_drvdata(pdev, psw);

	वापस 0;

err_irq:
	मुक्त_irq(irq, pdev);
err:
	kमुक्त(psw);
	वापस ret;
पूर्ण

अटल पूर्णांक चयन_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा push_चयन *psw = platक्रमm_get_drvdata(pdev);
	काष्ठा push_चयन_platक्रमm_info *psw_info = pdev->dev.platक्रमm_data;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (psw_info->name)
		device_हटाओ_file(&pdev->dev, &dev_attr_चयन);

	platक्रमm_set_drvdata(pdev, शून्य);
	flush_work(&psw->work);
	del_समयr_sync(&psw->debounce);
	मुक्त_irq(irq, pdev);

	kमुक्त(psw);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver चयन_driver = अणु
	.probe		= चयन_drv_probe,
	.हटाओ		= चयन_drv_हटाओ,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init चयन_init(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE DRV_NAME ": version %s loaded\n", DRV_VERSION);
	वापस platक्रमm_driver_रेजिस्टर(&चयन_driver);
पूर्ण

अटल व्योम __निकास चयन_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&चयन_driver);
पूर्ण
module_init(चयन_init);
module_निकास(चयन_निकास);

MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR("Paul Mundt");
MODULE_LICENSE("GPL v2");
