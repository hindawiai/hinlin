<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs.h>
#समावेश <linux/rwsem.h>
#समावेश "kpc_dma_driver.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matt.Sickler@daktronics.com");

#घोषणा KPC_DMA_CHAR_MAJOR    UNNAMED_MAJOR
#घोषणा KPC_DMA_NUM_MINORS    BIT(MINORBITS)
अटल DEFINE_MUTEX(kpc_dma_mtx);
अटल पूर्णांक asचिन्हित_major_num;
अटल LIST_HEAD(kpc_dma_list);

/**********  kpc_dma_list list management  **********/
काष्ठा kpc_dma_device *kpc_dma_lookup_device(पूर्णांक minor)
अणु
	काष्ठा kpc_dma_device *c;

	mutex_lock(&kpc_dma_mtx);
	list_क्रम_each_entry(c, &kpc_dma_list, list) अणु
		अगर (c->pldev->id == minor)
			जाओ out;
	पूर्ण
	c = शून्य; // not-found हाल
out:
	mutex_unlock(&kpc_dma_mtx);
	वापस c;
पूर्ण

अटल व्योम kpc_dma_add_device(काष्ठा kpc_dma_device *ldev)
अणु
	mutex_lock(&kpc_dma_mtx);
	list_add(&ldev->list, &kpc_dma_list);
	mutex_unlock(&kpc_dma_mtx);
पूर्ण

अटल व्योम kpc_dma_del_device(काष्ठा kpc_dma_device *ldev)
अणु
	mutex_lock(&kpc_dma_mtx);
	list_del(&ldev->list);
	mutex_unlock(&kpc_dma_mtx);
पूर्ण

/**********  SysFS Attributes **********/
अटल sमाप_प्रकार  engine_regs_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kpc_dma_device *ldev;
	काष्ठा platक्रमm_device *pldev = to_platक्रमm_device(dev);

	अगर (!pldev)
		वापस 0;
	ldev = platक्रमm_get_drvdata(pldev);
	अगर (!ldev)
		वापस 0;

	वापस scnम_लिखो(buf, PAGE_SIZE,
		"EngineControlStatus      = 0x%08x\n"
		"RegNextDescPtr           = 0x%08x\n"
		"RegSWDescPtr             = 0x%08x\n"
		"RegCompletedDescPtr      = 0x%08x\n"
		"desc_pool_first          = %p\n"
		"desc_pool_last           = %p\n"
		"desc_next                = %p\n"
		"desc_completed           = %p\n",
		पढ़ोl(ldev->eng_regs + 1),
		पढ़ोl(ldev->eng_regs + 2),
		पढ़ोl(ldev->eng_regs + 3),
		पढ़ोl(ldev->eng_regs + 4),
		ldev->desc_pool_first,
		ldev->desc_pool_last,
		ldev->desc_next,
		ldev->desc_completed
	);
पूर्ण
अटल DEVICE_ATTR_RO(engine_regs);

अटल स्थिर काष्ठा attribute *ndd_attr_list[] = अणु
	&dev_attr_engine_regs.attr,
	शून्य,
पूर्ण;

अटल काष्ठा class *kpc_dma_class;

/**********  Platक्रमm Driver Functions  **********/
अटल
पूर्णांक  kpc_dma_probe(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा resource *r = शून्य;
	पूर्णांक rv = 0;
	dev_t dev;

	काष्ठा kpc_dma_device *ldev = kzalloc(माप(*ldev), GFP_KERNEL);

	अगर (!ldev) अणु
		dev_err(&pldev->dev, "%s: unable to kzalloc space for kpc_dma_device\n", __func__);
		rv = -ENOMEM;
		जाओ err_rv;
	पूर्ण

	INIT_LIST_HEAD(&ldev->list);

	ldev->pldev = pldev;
	platक्रमm_set_drvdata(pldev, ldev);
	atomic_set(&ldev->खोलो_count, 1);

	mutex_init(&ldev->sem);
	lock_engine(ldev);

	// Get Engine regs resource
	r = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&ldev->pldev->dev, "%s: didn't get the engine regs resource!\n", __func__);
		rv = -ENXIO;
		जाओ err_kमुक्त;
	पूर्ण
	ldev->eng_regs = ioremap(r->start, resource_size(r));
	अगर (!ldev->eng_regs) अणु
		dev_err(&ldev->pldev->dev, "%s: failed to ioremap engine regs!\n", __func__);
		rv = -ENXIO;
		जाओ err_kमुक्त;
	पूर्ण

	r = platक्रमm_get_resource(pldev, IORESOURCE_IRQ, 0);
	अगर (!r) अणु
		dev_err(&ldev->pldev->dev, "%s: didn't get the IRQ resource!\n", __func__);
		rv = -ENXIO;
		जाओ err_kमुक्त;
	पूर्ण
	ldev->irq = r->start;

	// Setup miscdev काष्ठा
	dev = MKDEV(asचिन्हित_major_num, pldev->id);
	ldev->kpc_dma_dev = device_create(kpc_dma_class, &pldev->dev, dev, ldev,
					  "kpc_dma%d", pldev->id);
	अगर (IS_ERR(ldev->kpc_dma_dev)) अणु
		rv = PTR_ERR(ldev->kpc_dma_dev);
		dev_err(&ldev->pldev->dev, "%s: device_create failed: %d\n", __func__, rv);
		जाओ err_kमुक्त;
	पूर्ण

	// Setup the DMA engine
	rv = setup_dma_engine(ldev, 30);
	अगर (rv) अणु
		dev_err(&ldev->pldev->dev, "%s: failed to setup_dma_engine: %d\n", __func__, rv);
		जाओ err_misc_dereg;
	पूर्ण

	// Setup the sysfs files
	rv = sysfs_create_files(&(ldev->pldev->dev.kobj), ndd_attr_list);
	अगर (rv) अणु
		dev_err(&ldev->pldev->dev, "%s: Failed to add sysfs files: %d\n", __func__, rv);
		जाओ err_destroy_eng;
	पूर्ण

	kpc_dma_add_device(ldev);

	वापस 0;

 err_destroy_eng:
	destroy_dma_engine(ldev);
 err_misc_dereg:
	device_destroy(kpc_dma_class, dev);
 err_kमुक्त:
	kमुक्त(ldev);
 err_rv:
	वापस rv;
पूर्ण

अटल
पूर्णांक  kpc_dma_हटाओ(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा kpc_dma_device *ldev = platक्रमm_get_drvdata(pldev);

	अगर (!ldev)
		वापस -ENXIO;

	lock_engine(ldev);
	sysfs_हटाओ_files(&(ldev->pldev->dev.kobj), ndd_attr_list);
	destroy_dma_engine(ldev);
	kpc_dma_del_device(ldev);
	device_destroy(kpc_dma_class, MKDEV(asचिन्हित_major_num, ldev->pldev->id));
	kमुक्त(ldev);

	वापस 0;
पूर्ण

/**********  Driver Functions  **********/
अटल काष्ठा platक्रमm_driver kpc_dma_plat_driver_i = अणु
	.probe        = kpc_dma_probe,
	.हटाओ       = kpc_dma_हटाओ,
	.driver = अणु
		.name   = KP_DRIVER_NAME_DMA_CONTROLLER,
	पूर्ण,
पूर्ण;

अटल
पूर्णांक __init kpc_dma_driver_init(व्योम)
अणु
	पूर्णांक err;

	err = __रेजिस्टर_chrdev(KPC_DMA_CHAR_MAJOR, 0, KPC_DMA_NUM_MINORS,
				"kpc_dma", &kpc_dma_fops);
	अगर (err < 0) अणु
		pr_err("Can't allocate a major number (%d) for kpc_dma (err = %d)\n",
		       KPC_DMA_CHAR_MAJOR, err);
		जाओ fail_chrdev_रेजिस्टर;
	पूर्ण
	asचिन्हित_major_num = err;

	kpc_dma_class = class_create(THIS_MODULE, "kpc_dma");
	err = PTR_ERR(kpc_dma_class);
	अगर (IS_ERR(kpc_dma_class)) अणु
		pr_err("Can't create class kpc_dma (err = %d)\n", err);
		जाओ fail_class_create;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&kpc_dma_plat_driver_i);
	अगर (err) अणु
		pr_err("Can't register platform driver for kpc_dma (err = %d)\n", err);
		जाओ fail_platdriver_रेजिस्टर;
	पूर्ण

	वापस err;

fail_platdriver_रेजिस्टर:
	class_destroy(kpc_dma_class);
fail_class_create:
	__unरेजिस्टर_chrdev(KPC_DMA_CHAR_MAJOR, 0, KPC_DMA_NUM_MINORS, "kpc_dma");
fail_chrdev_रेजिस्टर:
	वापस err;
पूर्ण
module_init(kpc_dma_driver_init);

अटल
व्योम __निकास kpc_dma_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&kpc_dma_plat_driver_i);
	class_destroy(kpc_dma_class);
	__unरेजिस्टर_chrdev(KPC_DMA_CHAR_MAJOR, 0, KPC_DMA_NUM_MINORS, "kpc_dma");
पूर्ण
module_निकास(kpc_dma_driver_निकास);
