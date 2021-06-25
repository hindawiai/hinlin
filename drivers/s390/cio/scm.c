<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Recognize and मुख्यtain s390 storage class memory.
 *
 * Copyright IBM Corp. 2012
 * Author(s): Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/eadm.h>
#समावेश "chsc.h"

अटल काष्ठा device *scm_root;

#घोषणा to_scm_dev(n) container_of(n, काष्ठा scm_device, dev)
#घोषणा	to_scm_drv(d) container_of(d, काष्ठा scm_driver, drv)

अटल पूर्णांक scmdev_probe(काष्ठा device *dev)
अणु
	काष्ठा scm_device *scmdev = to_scm_dev(dev);
	काष्ठा scm_driver *scmdrv = to_scm_drv(dev->driver);

	वापस scmdrv->probe ? scmdrv->probe(scmdev) : -ENODEV;
पूर्ण

अटल पूर्णांक scmdev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scm_device *scmdev = to_scm_dev(dev);
	काष्ठा scm_driver *scmdrv = to_scm_drv(dev->driver);

	वापस scmdrv->हटाओ ? scmdrv->हटाओ(scmdev) : -ENODEV;
पूर्ण

अटल पूर्णांक scmdev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	वापस add_uevent_var(env, "MODALIAS=scm:scmdev");
पूर्ण

अटल काष्ठा bus_type scm_bus_type = अणु
	.name  = "scm",
	.probe = scmdev_probe,
	.हटाओ = scmdev_हटाओ,
	.uevent = scmdev_uevent,
पूर्ण;

/**
 * scm_driver_रेजिस्टर() - रेजिस्टर a scm driver
 * @scmdrv: driver to be रेजिस्टरed
 */
पूर्णांक scm_driver_रेजिस्टर(काष्ठा scm_driver *scmdrv)
अणु
	काष्ठा device_driver *drv = &scmdrv->drv;

	drv->bus = &scm_bus_type;

	वापस driver_रेजिस्टर(drv);
पूर्ण
EXPORT_SYMBOL_GPL(scm_driver_रेजिस्टर);

/**
 * scm_driver_unरेजिस्टर() - deरेजिस्टर a scm driver
 * @scmdrv: driver to be deरेजिस्टरed
 */
व्योम scm_driver_unरेजिस्टर(काष्ठा scm_driver *scmdrv)
अणु
	driver_unरेजिस्टर(&scmdrv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(scm_driver_unरेजिस्टर);

व्योम scm_irq_handler(काष्ठा aob *aob, blk_status_t error)
अणु
	काष्ठा aob_rq_header *aobrq = (व्योम *) aob->request.data;
	काष्ठा scm_device *scmdev = aobrq->scmdev;
	काष्ठा scm_driver *scmdrv = to_scm_drv(scmdev->dev.driver);

	scmdrv->handler(scmdev, aobrq->data, error);
पूर्ण
EXPORT_SYMBOL_GPL(scm_irq_handler);

#घोषणा scm_attr(name)							\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev,				\
	       काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा scm_device *scmdev = to_scm_dev(dev);			\
	पूर्णांक ret;							\
									\
	device_lock(dev);						\
	ret = प्र_लिखो(buf, "%u\n", scmdev->attrs.name);			\
	device_unlock(dev);						\
									\
	वापस ret;							\
पूर्ण									\
अटल DEVICE_ATTR(name, S_IRUGO, show_##name, शून्य);

scm_attr(persistence);
scm_attr(oper_state);
scm_attr(data_state);
scm_attr(rank);
scm_attr(release);
scm_attr(res_id);

अटल काष्ठा attribute *scmdev_attrs[] = अणु
	&dev_attr_persistence.attr,
	&dev_attr_oper_state.attr,
	&dev_attr_data_state.attr,
	&dev_attr_rank.attr,
	&dev_attr_release.attr,
	&dev_attr_res_id.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group scmdev_attr_group = अणु
	.attrs = scmdev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *scmdev_attr_groups[] = अणु
	&scmdev_attr_group,
	शून्य,
पूर्ण;

अटल व्योम scmdev_release(काष्ठा device *dev)
अणु
	काष्ठा scm_device *scmdev = to_scm_dev(dev);

	kमुक्त(scmdev);
पूर्ण

अटल व्योम scmdev_setup(काष्ठा scm_device *scmdev, काष्ठा sale *sale,
			 अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक max_blk_count)
अणु
	dev_set_name(&scmdev->dev, "%016llx", (अचिन्हित दीर्घ दीर्घ) sale->sa);
	scmdev->nr_max_block = max_blk_count;
	scmdev->address = sale->sa;
	scmdev->size = 1UL << size;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.persistence = sale->p;
	scmdev->attrs.oper_state = sale->op_state;
	scmdev->attrs.data_state = sale->data_state;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.release = sale->r;
	scmdev->attrs.res_id = sale->rid;
	scmdev->dev.parent = scm_root;
	scmdev->dev.bus = &scm_bus_type;
	scmdev->dev.release = scmdev_release;
	scmdev->dev.groups = scmdev_attr_groups;
पूर्ण

/*
 * Check क्रम state-changes, notअगरy the driver and userspace.
 */
अटल व्योम scmdev_update(काष्ठा scm_device *scmdev, काष्ठा sale *sale)
अणु
	काष्ठा scm_driver *scmdrv;
	bool changed;

	device_lock(&scmdev->dev);
	changed = scmdev->attrs.rank != sale->rank ||
		  scmdev->attrs.oper_state != sale->op_state;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.oper_state = sale->op_state;
	अगर (!scmdev->dev.driver)
		जाओ out;
	scmdrv = to_scm_drv(scmdev->dev.driver);
	अगर (changed && scmdrv->notअगरy)
		scmdrv->notअगरy(scmdev, SCM_CHANGE);
out:
	device_unlock(&scmdev->dev);
	अगर (changed)
		kobject_uevent(&scmdev->dev.kobj, KOBJ_CHANGE);
पूर्ण

अटल पूर्णांक check_address(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा scm_device *scmdev = to_scm_dev(dev);
	स्थिर काष्ठा sale *sale = data;

	वापस scmdev->address == sale->sa;
पूर्ण

अटल काष्ठा scm_device *scmdev_find(काष्ठा sale *sale)
अणु
	काष्ठा device *dev;

	dev = bus_find_device(&scm_bus_type, शून्य, sale, check_address);

	वापस dev ? to_scm_dev(dev) : शून्य;
पूर्ण

अटल पूर्णांक scm_add(काष्ठा chsc_scm_info *scm_info, माप_प्रकार num)
अणु
	काष्ठा sale *sale, *scmal = scm_info->scmal;
	काष्ठा scm_device *scmdev;
	पूर्णांक ret;

	क्रम (sale = scmal; sale < scmal + num; sale++) अणु
		scmdev = scmdev_find(sale);
		अगर (scmdev) अणु
			scmdev_update(scmdev, sale);
			/* Release reference from scm_find(). */
			put_device(&scmdev->dev);
			जारी;
		पूर्ण
		scmdev = kzalloc(माप(*scmdev), GFP_KERNEL);
		अगर (!scmdev)
			वापस -ENODEV;
		scmdev_setup(scmdev, sale, scm_info->is, scm_info->mbc);
		ret = device_रेजिस्टर(&scmdev->dev);
		अगर (ret) अणु
			/* Release reference from device_initialize(). */
			put_device(&scmdev->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक scm_update_inक्रमmation(व्योम)
अणु
	काष्ठा chsc_scm_info *scm_info;
	u64 token = 0;
	माप_प्रकार num;
	पूर्णांक ret;

	scm_info = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!scm_info)
		वापस -ENOMEM;

	करो अणु
		ret = chsc_scm_info(scm_info, token);
		अगर (ret)
			अवरोध;

		num = (scm_info->response.length -
		       (दुरत्व(काष्ठा chsc_scm_info, scmal) -
			दुरत्व(काष्ठा chsc_scm_info, response))
		      ) / माप(काष्ठा sale);

		ret = scm_add(scm_info, num);
		अगर (ret)
			अवरोध;

		token = scm_info->restok;
	पूर्ण जबतक (token);

	मुक्त_page((अचिन्हित दीर्घ)scm_info);

	वापस ret;
पूर्ण

अटल पूर्णांक scm_dev_avail(काष्ठा device *dev, व्योम *unused)
अणु
	काष्ठा scm_driver *scmdrv = to_scm_drv(dev->driver);
	काष्ठा scm_device *scmdev = to_scm_dev(dev);

	अगर (dev->driver && scmdrv->notअगरy)
		scmdrv->notअगरy(scmdev, SCM_AVAIL);

	वापस 0;
पूर्ण

पूर्णांक scm_process_availability_inक्रमmation(व्योम)
अणु
	वापस bus_क्रम_each_dev(&scm_bus_type, शून्य, शून्य, scm_dev_avail);
पूर्ण

अटल पूर्णांक __init scm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&scm_bus_type);
	अगर (ret)
		वापस ret;

	scm_root = root_device_रेजिस्टर("scm");
	अगर (IS_ERR(scm_root)) अणु
		bus_unरेजिस्टर(&scm_bus_type);
		वापस PTR_ERR(scm_root);
	पूर्ण

	scm_update_inक्रमmation();
	वापस 0;
पूर्ण
subsys_initcall_sync(scm_init);
