<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	scsi_pm.c	Copyright (C) 2010 Alan Stern
 *
 *	SCSI dynamic Power Management
 *		Initial version: Alan Stern <stern@rowland.harvard.edu>
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/export.h>
#समावेश <linux/async.h>
#समावेश <linux/blk-pm.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_host.h>

#समावेश "scsi_priv.h"

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक करो_scsi_suspend(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->suspend ? pm->suspend(dev) : 0;
पूर्ण

अटल पूर्णांक करो_scsi_मुक्तze(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->मुक्तze ? pm->मुक्तze(dev) : 0;
पूर्ण

अटल पूर्णांक करो_scsi_घातeroff(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->घातeroff ? pm->घातeroff(dev) : 0;
पूर्ण

अटल पूर्णांक करो_scsi_resume(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->resume ? pm->resume(dev) : 0;
पूर्ण

अटल पूर्णांक करो_scsi_thaw(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->thaw ? pm->thaw(dev) : 0;
पूर्ण

अटल पूर्णांक करो_scsi_restore(काष्ठा device *dev, स्थिर काष्ठा dev_pm_ops *pm)
अणु
	वापस pm && pm->restore ? pm->restore(dev) : 0;
पूर्ण

अटल पूर्णांक scsi_dev_type_suspend(काष्ठा device *dev,
		पूर्णांक (*cb)(काष्ठा device *, स्थिर काष्ठा dev_pm_ops *))
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक err;

	/* flush pending in-flight resume operations, suspend is synchronous */
	async_synchronize_full_करोमुख्य(&scsi_sd_pm_करोमुख्य);

	err = scsi_device_quiesce(to_scsi_device(dev));
	अगर (err == 0) अणु
		err = cb(dev, pm);
		अगर (err)
			scsi_device_resume(to_scsi_device(dev));
	पूर्ण
	dev_dbg(dev, "scsi suspend: %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक scsi_dev_type_resume(काष्ठा device *dev,
		पूर्णांक (*cb)(काष्ठा device *, स्थिर काष्ठा dev_pm_ops *))
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक err = 0;

	err = cb(dev, pm);
	scsi_device_resume(to_scsi_device(dev));
	dev_dbg(dev, "scsi resume: %d\n", err);

	अगर (err == 0) अणु
		pm_runसमय_disable(dev);
		err = pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);

		/*
		 * Forcibly set runसमय PM status of request queue to "active"
		 * to make sure we can again get requests from the queue
		 * (see also blk_pm_peek_request()).
		 *
		 * The resume hook will correct runसमय PM status of the disk.
		 */
		अगर (!err && scsi_is_sdev_device(dev)) अणु
			काष्ठा scsi_device *sdev = to_scsi_device(dev);

			blk_set_runसमय_active(sdev->request_queue);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
scsi_bus_suspend_common(काष्ठा device *dev,
		पूर्णांक (*cb)(काष्ठा device *, स्थिर काष्ठा dev_pm_ops *))
अणु
	पूर्णांक err = 0;

	अगर (scsi_is_sdev_device(dev)) अणु
		/*
		 * All the high-level SCSI drivers that implement runसमय
		 * PM treat runसमय suspend, प्रणाली suspend, and प्रणाली
		 * hibernate nearly identically. In all हालs the requirements
		 * क्रम runसमय suspension are stricter.
		 */
		अगर (pm_runसमय_suspended(dev))
			वापस 0;

		err = scsi_dev_type_suspend(dev, cb);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम async_sdev_resume(व्योम *dev, async_cookie_t cookie)
अणु
	scsi_dev_type_resume(dev, करो_scsi_resume);
पूर्ण

अटल व्योम async_sdev_thaw(व्योम *dev, async_cookie_t cookie)
अणु
	scsi_dev_type_resume(dev, करो_scsi_thaw);
पूर्ण

अटल व्योम async_sdev_restore(व्योम *dev, async_cookie_t cookie)
अणु
	scsi_dev_type_resume(dev, करो_scsi_restore);
पूर्ण

अटल पूर्णांक scsi_bus_resume_common(काष्ठा device *dev,
		पूर्णांक (*cb)(काष्ठा device *, स्थिर काष्ठा dev_pm_ops *))
अणु
	async_func_t fn;

	अगर (!scsi_is_sdev_device(dev))
		fn = शून्य;
	अन्यथा अगर (cb == करो_scsi_resume)
		fn = async_sdev_resume;
	अन्यथा अगर (cb == करो_scsi_thaw)
		fn = async_sdev_thaw;
	अन्यथा अगर (cb == करो_scsi_restore)
		fn = async_sdev_restore;
	अन्यथा
		fn = शून्य;

	अगर (fn) अणु
		async_schedule_करोमुख्य(fn, dev, &scsi_sd_pm_करोमुख्य);

		/*
		 * If a user has disabled async probing a likely reason
		 * is due to a storage enclosure that करोes not inject
		 * staggered spin-ups.  For safety, make resume
		 * synchronous as well in that हाल.
		 */
		अगर (म_भेदन(scsi_scan_type, "async", 5) != 0)
			async_synchronize_full_करोमुख्य(&scsi_sd_pm_करोमुख्य);
	पूर्ण अन्यथा अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक scsi_bus_prepare(काष्ठा device *dev)
अणु
	अगर (scsi_is_host_device(dev)) अणु
		/* Wait until async scanning is finished */
		scsi_complete_async_scans();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक scsi_bus_suspend(काष्ठा device *dev)
अणु
	वापस scsi_bus_suspend_common(dev, करो_scsi_suspend);
पूर्ण

अटल पूर्णांक scsi_bus_resume(काष्ठा device *dev)
अणु
	वापस scsi_bus_resume_common(dev, करो_scsi_resume);
पूर्ण

अटल पूर्णांक scsi_bus_मुक्तze(काष्ठा device *dev)
अणु
	वापस scsi_bus_suspend_common(dev, करो_scsi_मुक्तze);
पूर्ण

अटल पूर्णांक scsi_bus_thaw(काष्ठा device *dev)
अणु
	वापस scsi_bus_resume_common(dev, करो_scsi_thaw);
पूर्ण

अटल पूर्णांक scsi_bus_घातeroff(काष्ठा device *dev)
अणु
	वापस scsi_bus_suspend_common(dev, करो_scsi_घातeroff);
पूर्ण

अटल पूर्णांक scsi_bus_restore(काष्ठा device *dev)
अणु
	वापस scsi_bus_resume_common(dev, करो_scsi_restore);
पूर्ण

#अन्यथा /* CONFIG_PM_SLEEP */

#घोषणा scsi_bus_prepare		शून्य
#घोषणा scsi_bus_suspend		शून्य
#घोषणा scsi_bus_resume			शून्य
#घोषणा scsi_bus_मुक्तze			शून्य
#घोषणा scsi_bus_thaw			शून्य
#घोषणा scsi_bus_घातeroff		शून्य
#घोषणा scsi_bus_restore		शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक sdev_runसमय_suspend(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	पूर्णांक err = 0;

	err = blk_pre_runसमय_suspend(sdev->request_queue);
	अगर (err)
		वापस err;
	अगर (pm && pm->runसमय_suspend)
		err = pm->runसमय_suspend(dev);
	blk_post_runसमय_suspend(sdev->request_queue, err);

	वापस err;
पूर्ण

अटल पूर्णांक scsi_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;

	dev_dbg(dev, "scsi_runtime_suspend\n");
	अगर (scsi_is_sdev_device(dev))
		err = sdev_runसमय_suspend(dev);

	/* Insert hooks here क्रम tarमाला_लो, hosts, and transport classes */

	वापस err;
पूर्ण

अटल पूर्णांक sdev_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver ? dev->driver->pm : शून्य;
	पूर्णांक err = 0;

	blk_pre_runसमय_resume(sdev->request_queue);
	अगर (pm && pm->runसमय_resume)
		err = pm->runसमय_resume(dev);
	blk_post_runसमय_resume(sdev->request_queue, err);

	वापस err;
पूर्ण

अटल पूर्णांक scsi_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;

	dev_dbg(dev, "scsi_runtime_resume\n");
	अगर (scsi_is_sdev_device(dev))
		err = sdev_runसमय_resume(dev);

	/* Insert hooks here क्रम tarमाला_लो, hosts, and transport classes */

	वापस err;
पूर्ण

अटल पूर्णांक scsi_runसमय_idle(काष्ठा device *dev)
अणु
	dev_dbg(dev, "scsi_runtime_idle\n");

	/* Insert hooks here क्रम tarमाला_लो, hosts, and transport classes */

	अगर (scsi_is_sdev_device(dev)) अणु
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_स्वतःsuspend(dev);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक scsi_स्वतःpm_get_device(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक	err;

	err = pm_runसमय_get_sync(&sdev->sdev_gendev);
	अगर (err < 0 && err !=-EACCES)
		pm_runसमय_put_sync(&sdev->sdev_gendev);
	अन्यथा
		err = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_स्वतःpm_get_device);

व्योम scsi_स्वतःpm_put_device(काष्ठा scsi_device *sdev)
अणु
	pm_runसमय_put_sync(&sdev->sdev_gendev);
पूर्ण
EXPORT_SYMBOL_GPL(scsi_स्वतःpm_put_device);

व्योम scsi_स्वतःpm_get_target(काष्ठा scsi_target *starget)
अणु
	pm_runसमय_get_sync(&starget->dev);
पूर्ण

व्योम scsi_स्वतःpm_put_target(काष्ठा scsi_target *starget)
अणु
	pm_runसमय_put_sync(&starget->dev);
पूर्ण

पूर्णांक scsi_स्वतःpm_get_host(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक	err;

	err = pm_runसमय_get_sync(&shost->shost_gendev);
	अगर (err < 0 && err !=-EACCES)
		pm_runसमय_put_sync(&shost->shost_gendev);
	अन्यथा
		err = 0;
	वापस err;
पूर्ण

व्योम scsi_स्वतःpm_put_host(काष्ठा Scsi_Host *shost)
अणु
	pm_runसमय_put_sync(&shost->shost_gendev);
पूर्ण

स्थिर काष्ठा dev_pm_ops scsi_bus_pm_ops = अणु
	.prepare =		scsi_bus_prepare,
	.suspend =		scsi_bus_suspend,
	.resume =		scsi_bus_resume,
	.मुक्तze =		scsi_bus_मुक्तze,
	.thaw =			scsi_bus_thaw,
	.घातeroff =		scsi_bus_घातeroff,
	.restore =		scsi_bus_restore,
	.runसमय_suspend =	scsi_runसमय_suspend,
	.runसमय_resume =	scsi_runसमय_resume,
	.runसमय_idle =		scsi_runसमय_idle,
पूर्ण;
