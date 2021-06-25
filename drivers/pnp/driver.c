<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * driver.c - device id matching, driver model, etc.
 *
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/pnp.h>
#समावेश "base.h"

अटल पूर्णांक compare_func(स्थिर अक्षर *ida, स्थिर अक्षर *idb)
अणु
	पूर्णांक i;

	/* we only need to compare the last 4 अक्षरs */
	क्रम (i = 3; i < 7; i++) अणु
		अगर (ida[i] != 'X' &&
		    idb[i] != 'X' && बड़े(ida[i]) != बड़े(idb[i]))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक compare_pnp_id(काष्ठा pnp_id *pos, स्थिर अक्षर *id)
अणु
	अगर (!pos || !id || (म_माप(id) != 7))
		वापस 0;
	अगर (स_भेद(id, "ANYDEVS", 7) == 0)
		वापस 1;
	जबतक (pos) अणु
		अगर (स_भेद(pos->id, id, 3) == 0)
			अगर (compare_func(pos->id, id) == 1)
				वापस 1;
		pos = pos->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pnp_device_id *match_device(काष्ठा pnp_driver *drv,
						काष्ठा pnp_dev *dev)
अणु
	स्थिर काष्ठा pnp_device_id *drv_id = drv->id_table;

	अगर (!drv_id)
		वापस शून्य;

	जबतक (*drv_id->id) अणु
		अगर (compare_pnp_id(dev->id, drv_id->id))
			वापस drv_id;
		drv_id++;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक pnp_device_attach(काष्ठा pnp_dev *pnp_dev)
अणु
	mutex_lock(&pnp_lock);
	अगर (pnp_dev->status != PNP_READY) अणु
		mutex_unlock(&pnp_lock);
		वापस -EBUSY;
	पूर्ण
	pnp_dev->status = PNP_ATTACHED;
	mutex_unlock(&pnp_lock);
	वापस 0;
पूर्ण

व्योम pnp_device_detach(काष्ठा pnp_dev *pnp_dev)
अणु
	mutex_lock(&pnp_lock);
	अगर (pnp_dev->status == PNP_ATTACHED)
		pnp_dev->status = PNP_READY;
	mutex_unlock(&pnp_lock);
पूर्ण

अटल पूर्णांक pnp_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error;
	काष्ठा pnp_driver *pnp_drv;
	काष्ठा pnp_dev *pnp_dev;
	स्थिर काष्ठा pnp_device_id *dev_id = शून्य;
	pnp_dev = to_pnp_dev(dev);
	pnp_drv = to_pnp_driver(dev->driver);

	error = pnp_device_attach(pnp_dev);
	अगर (error < 0)
		वापस error;

	अगर (pnp_dev->active == 0) अणु
		अगर (!(pnp_drv->flags & PNP_DRIVER_RES_DO_NOT_CHANGE)) अणु
			error = pnp_activate_dev(pnp_dev);
			अगर (error < 0)
				वापस error;
		पूर्ण
	पूर्ण अन्यथा अगर ((pnp_drv->flags & PNP_DRIVER_RES_DISABLE)
		   == PNP_DRIVER_RES_DISABLE) अणु
		error = pnp_disable_dev(pnp_dev);
		अगर (error < 0)
			वापस error;
	पूर्ण
	error = 0;
	अगर (pnp_drv->probe) अणु
		dev_id = match_device(pnp_drv, pnp_dev);
		अगर (dev_id != शून्य)
			error = pnp_drv->probe(pnp_dev, dev_id);
	पूर्ण
	अगर (error >= 0) अणु
		pnp_dev->driver = pnp_drv;
		error = 0;
	पूर्ण अन्यथा
		जाओ fail;

	वापस error;

fail:
	pnp_device_detach(pnp_dev);
	वापस error;
पूर्ण

अटल पूर्णांक pnp_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pnp_dev *pnp_dev = to_pnp_dev(dev);
	काष्ठा pnp_driver *drv = pnp_dev->driver;

	अगर (drv) अणु
		अगर (drv->हटाओ)
			drv->हटाओ(pnp_dev);
		pnp_dev->driver = शून्य;
	पूर्ण

	अगर (pnp_dev->active &&
	    (!drv || !(drv->flags & PNP_DRIVER_RES_DO_NOT_CHANGE)))
		pnp_disable_dev(pnp_dev);

	pnp_device_detach(pnp_dev);
	वापस 0;
पूर्ण

अटल व्योम pnp_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा pnp_dev *pnp_dev = to_pnp_dev(dev);
	काष्ठा pnp_driver *drv = pnp_dev->driver;

	अगर (drv && drv->shutकरोwn)
		drv->shutकरोwn(pnp_dev);
पूर्ण

अटल पूर्णांक pnp_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा pnp_dev *pnp_dev = to_pnp_dev(dev);
	काष्ठा pnp_driver *pnp_drv = to_pnp_driver(drv);

	अगर (match_device(pnp_drv, pnp_dev) == शून्य)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक __pnp_bus_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा pnp_dev *pnp_dev = to_pnp_dev(dev);
	काष्ठा pnp_driver *pnp_drv = pnp_dev->driver;
	पूर्णांक error;

	अगर (!pnp_drv)
		वापस 0;

	अगर (pnp_drv->driver.pm && pnp_drv->driver.pm->suspend) अणु
		error = pnp_drv->driver.pm->suspend(dev);
		suspend_report_result(pnp_drv->driver.pm->suspend, error);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_drv->suspend) अणु
		error = pnp_drv->suspend(pnp_dev, state);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_can_disable(pnp_dev)) अणु
		error = pnp_stop_dev(pnp_dev);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_can_suspend(pnp_dev))
		pnp_dev->protocol->suspend(pnp_dev, state);
	वापस 0;
पूर्ण

अटल पूर्णांक pnp_bus_suspend(काष्ठा device *dev)
अणु
	वापस __pnp_bus_suspend(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक pnp_bus_मुक्तze(काष्ठा device *dev)
अणु
	वापस __pnp_bus_suspend(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक pnp_bus_घातeroff(काष्ठा device *dev)
अणु
	वापस __pnp_bus_suspend(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक pnp_bus_resume(काष्ठा device *dev)
अणु
	काष्ठा pnp_dev *pnp_dev = to_pnp_dev(dev);
	काष्ठा pnp_driver *pnp_drv = pnp_dev->driver;
	पूर्णांक error;

	अगर (!pnp_drv)
		वापस 0;

	अगर (pnp_dev->protocol->resume) अणु
		error = pnp_dev->protocol->resume(pnp_dev);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_can_ग_लिखो(pnp_dev)) अणु
		error = pnp_start_dev(pnp_dev);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_drv->driver.pm && pnp_drv->driver.pm->resume) अणु
		error = pnp_drv->driver.pm->resume(dev);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (pnp_drv->resume) अणु
		error = pnp_drv->resume(pnp_dev);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pnp_bus_dev_pm_ops = अणु
	/* Suspend callbacks */
	.suspend = pnp_bus_suspend,
	.resume = pnp_bus_resume,
	/* Hibernate callbacks */
	.मुक्तze = pnp_bus_मुक्तze,
	.thaw = pnp_bus_resume,
	.घातeroff = pnp_bus_घातeroff,
	.restore = pnp_bus_resume,
पूर्ण;

काष्ठा bus_type pnp_bus_type = अणु
	.name    = "pnp",
	.match   = pnp_bus_match,
	.probe   = pnp_device_probe,
	.हटाओ  = pnp_device_हटाओ,
	.shutकरोwn = pnp_device_shutकरोwn,
	.pm	 = &pnp_bus_dev_pm_ops,
	.dev_groups = pnp_dev_groups,
पूर्ण;

पूर्णांक pnp_रेजिस्टर_driver(काष्ठा pnp_driver *drv)
अणु
	drv->driver.name = drv->name;
	drv->driver.bus = &pnp_bus_type;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण

व्योम pnp_unरेजिस्टर_driver(काष्ठा pnp_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण

/**
 * pnp_add_id - adds an EISA id to the specअगरied device
 * @dev: poपूर्णांकer to the desired device
 * @id: poपूर्णांकer to an EISA id string
 */
काष्ठा pnp_id *pnp_add_id(काष्ठा pnp_dev *dev, स्थिर अक्षर *id)
अणु
	काष्ठा pnp_id *dev_id, *ptr;

	dev_id = kzalloc(माप(काष्ठा pnp_id), GFP_KERNEL);
	अगर (!dev_id)
		वापस शून्य;

	dev_id->id[0] = id[0];
	dev_id->id[1] = id[1];
	dev_id->id[2] = id[2];
	dev_id->id[3] = छोटे(id[3]);
	dev_id->id[4] = छोटे(id[4]);
	dev_id->id[5] = छोटे(id[5]);
	dev_id->id[6] = छोटे(id[6]);
	dev_id->id[7] = '\0';

	dev_id->next = शून्य;
	ptr = dev->id;
	जबतक (ptr && ptr->next)
		ptr = ptr->next;
	अगर (ptr)
		ptr->next = dev_id;
	अन्यथा
		dev->id = dev_id;

	वापस dev_id;
पूर्ण

EXPORT_SYMBOL(pnp_रेजिस्टर_driver);
EXPORT_SYMBOL(pnp_unरेजिस्टर_driver);
EXPORT_SYMBOL(pnp_device_attach);
EXPORT_SYMBOL(pnp_device_detach);
