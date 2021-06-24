<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  tअगरm_core.c - TI FlashMedia driver
 *
 *  Copyright (C) 2006 Alex Dubov <oakad@yahoo.com>
 */

#समावेश <linux/tअगरm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME "tifm_core"
#घोषणा DRIVER_VERSION "0.8"

अटल काष्ठा workqueue_काष्ठा *workqueue;
अटल DEFINE_IDR(tअगरm_adapter_idr);
अटल DEFINE_SPINLOCK(tअगरm_adapter_lock);

अटल स्थिर अक्षर *tअगरm_media_type_name(अचिन्हित अक्षर type, अचिन्हित अक्षर nt)
अणु
	स्थिर अक्षर *card_type_name[3][3] = अणु
		अणु "SmartMedia/xD", "MemoryStick", "MMC/SD" पूर्ण,
		अणु "XD", "MS", "SD"पूर्ण,
		अणु "xd", "ms", "sd"पूर्ण
	पूर्ण;

	अगर (nt > 2 || type < 1 || type > 3)
		वापस शून्य;
	वापस card_type_name[nt][type - 1];
पूर्ण

अटल पूर्णांक tअगरm_dev_match(काष्ठा tअगरm_dev *sock, काष्ठा tअगरm_device_id *id)
अणु
	अगर (sock->type == id->type)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	काष्ठा tअगरm_driver *fm_drv = container_of(drv, काष्ठा tअगरm_driver,
						  driver);
	काष्ठा tअगरm_device_id *ids = fm_drv->id_table;

	अगर (ids) अणु
		जबतक (ids->type) अणु
			अगर (tअगरm_dev_match(sock, ids))
				वापस 1;
			++ids;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);

	अगर (add_uevent_var(env, "TIFM_CARD_TYPE=%s", tअगरm_media_type_name(sock->type, 1)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_device_probe(काष्ठा device *dev)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	काष्ठा tअगरm_driver *drv = container_of(dev->driver, काष्ठा tअगरm_driver,
					       driver);
	पूर्णांक rc = -ENODEV;

	get_device(dev);
	अगर (dev->driver && drv->probe) अणु
		rc = drv->probe(sock);
		अगर (!rc)
			वापस 0;
	पूर्ण
	put_device(dev);
	वापस rc;
पूर्ण

अटल व्योम tअगरm_dummy_event(काष्ठा tअगरm_dev *sock)
अणु
	वापस;
पूर्ण

अटल पूर्णांक tअगरm_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	काष्ठा tअगरm_driver *drv = container_of(dev->driver, काष्ठा tअगरm_driver,
					       driver);

	अगर (dev->driver && drv->हटाओ) अणु
		sock->card_event = tअगरm_dummy_event;
		sock->data_event = tअगरm_dummy_event;
		drv->हटाओ(sock);
		sock->dev.driver = शून्य;
	पूर्ण

	put_device(dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक tअगरm_device_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	काष्ठा tअगरm_driver *drv = container_of(dev->driver, काष्ठा tअगरm_driver,
					       driver);

	अगर (dev->driver && drv->suspend)
		वापस drv->suspend(sock, state);
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_device_resume(काष्ठा device *dev)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	काष्ठा tअगरm_driver *drv = container_of(dev->driver, काष्ठा tअगरm_driver,
					       driver);

	अगर (dev->driver && drv->resume)
		वापस drv->resume(sock);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा tअगरm_device_suspend शून्य
#घोषणा tअगरm_device_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	वापस प्र_लिखो(buf, "%x", sock->type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *tअगरm_dev_attrs[] = अणु
	&dev_attr_type.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(tअगरm_dev);

अटल काष्ठा bus_type tअगरm_bus_type = अणु
	.name      = "tifm",
	.dev_groups = tअगरm_dev_groups,
	.match     = tअगरm_bus_match,
	.uevent    = tअगरm_uevent,
	.probe     = tअगरm_device_probe,
	.हटाओ    = tअगरm_device_हटाओ,
	.suspend   = tअगरm_device_suspend,
	.resume    = tअगरm_device_resume
पूर्ण;

अटल व्योम tअगरm_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा tअगरm_adapter *fm = container_of(dev, काष्ठा tअगरm_adapter, dev);

	kमुक्त(fm);
पूर्ण

अटल काष्ठा class tअगरm_adapter_class = अणु
	.name    = "tifm_adapter",
	.dev_release = tअगरm_मुक्त
पूर्ण;

काष्ठा tअगरm_adapter *tअगरm_alloc_adapter(अचिन्हित पूर्णांक num_sockets,
					काष्ठा device *dev)
अणु
	काष्ठा tअगरm_adapter *fm;

	fm = kzalloc(माप(काष्ठा tअगरm_adapter)
		     + माप(काष्ठा tअगरm_dev*) * num_sockets, GFP_KERNEL);
	अगर (fm) अणु
		fm->dev.class = &tअगरm_adapter_class;
		fm->dev.parent = dev;
		device_initialize(&fm->dev);
		spin_lock_init(&fm->lock);
		fm->num_sockets = num_sockets;
	पूर्ण
	वापस fm;
पूर्ण
EXPORT_SYMBOL(tअगरm_alloc_adapter);

पूर्णांक tअगरm_add_adapter(काष्ठा tअगरm_adapter *fm)
अणु
	पूर्णांक rc;

	idr_preload(GFP_KERNEL);
	spin_lock(&tअगरm_adapter_lock);
	rc = idr_alloc(&tअगरm_adapter_idr, fm, 0, 0, GFP_NOWAIT);
	अगर (rc >= 0)
		fm->id = rc;
	spin_unlock(&tअगरm_adapter_lock);
	idr_preload_end();
	अगर (rc < 0)
		वापस rc;

	dev_set_name(&fm->dev, "tifm%u", fm->id);
	rc = device_add(&fm->dev);
	अगर (rc) अणु
		spin_lock(&tअगरm_adapter_lock);
		idr_हटाओ(&tअगरm_adapter_idr, fm->id);
		spin_unlock(&tअगरm_adapter_lock);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(tअगरm_add_adapter);

व्योम tअगरm_हटाओ_adapter(काष्ठा tअगरm_adapter *fm)
अणु
	अचिन्हित पूर्णांक cnt;

	flush_workqueue(workqueue);
	क्रम (cnt = 0; cnt < fm->num_sockets; ++cnt) अणु
		अगर (fm->sockets[cnt])
			device_unरेजिस्टर(&fm->sockets[cnt]->dev);
	पूर्ण

	spin_lock(&tअगरm_adapter_lock);
	idr_हटाओ(&tअगरm_adapter_idr, fm->id);
	spin_unlock(&tअगरm_adapter_lock);
	device_del(&fm->dev);
पूर्ण
EXPORT_SYMBOL(tअगरm_हटाओ_adapter);

व्योम tअगरm_मुक्त_adapter(काष्ठा tअगरm_adapter *fm)
अणु
	put_device(&fm->dev);
पूर्ण
EXPORT_SYMBOL(tअगरm_मुक्त_adapter);

व्योम tअगरm_मुक्त_device(काष्ठा device *dev)
अणु
	काष्ठा tअगरm_dev *sock = container_of(dev, काष्ठा tअगरm_dev, dev);
	kमुक्त(sock);
पूर्ण
EXPORT_SYMBOL(tअगरm_मुक्त_device);

काष्ठा tअगरm_dev *tअगरm_alloc_device(काष्ठा tअगरm_adapter *fm, अचिन्हित पूर्णांक id,
				   अचिन्हित अक्षर type)
अणु
	काष्ठा tअगरm_dev *sock = शून्य;

	अगर (!tअगरm_media_type_name(type, 0))
		वापस sock;

	sock = kzalloc(माप(काष्ठा tअगरm_dev), GFP_KERNEL);
	अगर (sock) अणु
		spin_lock_init(&sock->lock);
		sock->type = type;
		sock->socket_id = id;
		sock->card_event = tअगरm_dummy_event;
		sock->data_event = tअगरm_dummy_event;

		sock->dev.parent = fm->dev.parent;
		sock->dev.bus = &tअगरm_bus_type;
		sock->dev.dma_mask = fm->dev.parent->dma_mask;
		sock->dev.release = tअगरm_मुक्त_device;

		dev_set_name(&sock->dev, "tifm_%s%u:%u",
			     tअगरm_media_type_name(type, 2), fm->id, id);
		prपूर्णांकk(KERN_INFO DRIVER_NAME
		       ": %s card detected in socket %u:%u\n",
		       tअगरm_media_type_name(type, 0), fm->id, id);
	पूर्ण
	वापस sock;
पूर्ण
EXPORT_SYMBOL(tअगरm_alloc_device);

व्योम tअगरm_eject(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_adapter *fm = dev_get_drvdata(sock->dev.parent);
	fm->eject(fm, sock);
पूर्ण
EXPORT_SYMBOL(tअगरm_eject);

पूर्णांक tअगरm_has_ms_pअगर(काष्ठा tअगरm_dev *sock)
अणु
	काष्ठा tअगरm_adapter *fm = dev_get_drvdata(sock->dev.parent);
	वापस fm->has_ms_pअगर(fm, sock);
पूर्ण
EXPORT_SYMBOL(tअगरm_has_ms_pअगर);

पूर्णांक tअगरm_map_sg(काष्ठा tअगरm_dev *sock, काष्ठा scatterlist *sg, पूर्णांक nents,
		पूर्णांक direction)
अणु
	वापस pci_map_sg(to_pci_dev(sock->dev.parent), sg, nents, direction);
पूर्ण
EXPORT_SYMBOL(tअगरm_map_sg);

व्योम tअगरm_unmap_sg(काष्ठा tअगरm_dev *sock, काष्ठा scatterlist *sg, पूर्णांक nents,
		   पूर्णांक direction)
अणु
	pci_unmap_sg(to_pci_dev(sock->dev.parent), sg, nents, direction);
पूर्ण
EXPORT_SYMBOL(tअगरm_unmap_sg);

व्योम tअगरm_queue_work(काष्ठा work_काष्ठा *work)
अणु
	queue_work(workqueue, work);
पूर्ण
EXPORT_SYMBOL(tअगरm_queue_work);

पूर्णांक tअगरm_रेजिस्टर_driver(काष्ठा tअगरm_driver *drv)
अणु
	drv->driver.bus = &tअगरm_bus_type;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(tअगरm_रेजिस्टर_driver);

व्योम tअगरm_unरेजिस्टर_driver(काष्ठा tअगरm_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(tअगरm_unरेजिस्टर_driver);

अटल पूर्णांक __init tअगरm_init(व्योम)
अणु
	पूर्णांक rc;

	workqueue = create_मुक्तzable_workqueue("tifm");
	अगर (!workqueue)
		वापस -ENOMEM;

	rc = bus_रेजिस्टर(&tअगरm_bus_type);

	अगर (rc)
		जाओ err_out_wq;

	rc = class_रेजिस्टर(&tअगरm_adapter_class);
	अगर (!rc)
		वापस 0;

	bus_unरेजिस्टर(&tअगरm_bus_type);

err_out_wq:
	destroy_workqueue(workqueue);

	वापस rc;
पूर्ण

अटल व्योम __निकास tअगरm_निकास(व्योम)
अणु
	class_unरेजिस्टर(&tअगरm_adapter_class);
	bus_unरेजिस्टर(&tअगरm_bus_type);
	destroy_workqueue(workqueue);
पूर्ण

subsys_initcall(tअगरm_init);
module_निकास(tअगरm_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("TI FlashMedia core driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
