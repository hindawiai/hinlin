<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2017 Pengutronix, Uwe Kleine-Kथघnig <kernel@pengutronix.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश "siox.h"

/*
 * The lowest bit in the SIOX status word संकेतs अगर the in-device watchकरोg is
 * ok. If the bit is set, the device is functional.
 *
 * On writing the watchकरोg समयr is reset when this bit toggles.
 */
#घोषणा SIOX_STATUS_WDG			0x01

/*
 * Bits 1 to 3 of the status word पढ़ो as the bitwise negation of what was
 * घड़ीed in beक्रमe. The value घड़ीed in is changed in each cycle and so
 * allows to detect transmit/receive problems.
 */
#घोषणा SIOX_STATUS_COUNTER		0x0e

/*
 * Each Siox-Device has a 4 bit type number that is neither 0 nor 15. This is
 * available in the upper nibble of the पढ़ो status.
 *
 * On ग_लिखो these bits are DC.
 */
#घोषणा SIOX_STATUS_TYPE		0xf0

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/siox.h>

अटल bool siox_is_रेजिस्टरed;

अटल व्योम siox_master_lock(काष्ठा siox_master *smaster)
अणु
	mutex_lock(&smaster->lock);
पूर्ण

अटल व्योम siox_master_unlock(काष्ठा siox_master *smaster)
अणु
	mutex_unlock(&smaster->lock);
पूर्ण

अटल अंतरभूत u8 siox_status_clean(u8 status_पढ़ो, u8 status_written)
अणु
	/*
	 * bits 3:1 of status sample the respective bit in the status
	 * byte written in the previous cycle but inverted. So अगर you wrote the
	 * status word as 0xa beक्रमe (counter = 0b101), it is expected to get
	 * back the counter bits as 0b010.
	 *
	 * So given the last status written this function toggles the there
	 * unset counter bits in the पढ़ो value such that the counter bits in
	 * the वापस value are all zero अगरf the bits were पढ़ो as expected to
	 * simplअगरy error detection.
	 */

	वापस status_पढ़ो ^ (~status_written & 0xe);
पूर्ण

अटल bool siox_device_counter_error(काष्ठा siox_device *sdevice,
				      u8 status_clean)
अणु
	वापस (status_clean & SIOX_STATUS_COUNTER) != 0;
पूर्ण

अटल bool siox_device_type_error(काष्ठा siox_device *sdevice, u8 status_clean)
अणु
	u8 statustype = (status_clean & SIOX_STATUS_TYPE) >> 4;

	/*
	 * If the device knows which value the type bits should have, check
	 * against this value otherwise just rule out the invalid values 0b0000
	 * and 0b1111.
	 */
	अगर (sdevice->statustype) अणु
		अगर (statustype != sdevice->statustype)
			वापस true;
	पूर्ण अन्यथा अणु
		चयन (statustype) अणु
		हाल 0:
		हाल 0xf:
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool siox_device_wdg_error(काष्ठा siox_device *sdevice, u8 status_clean)
अणु
	वापस (status_clean & SIOX_STATUS_WDG) == 0;
पूर्ण

/*
 * If there is a type or counter error the device is called "unsynced".
 */
bool siox_device_synced(काष्ठा siox_device *sdevice)
अणु
	अगर (siox_device_type_error(sdevice, sdevice->status_पढ़ो_clean))
		वापस false;

	वापस !siox_device_counter_error(sdevice, sdevice->status_पढ़ो_clean);

पूर्ण
EXPORT_SYMBOL_GPL(siox_device_synced);

/*
 * A device is called "connected" अगर it is synced and the watchकरोg is not
 * निश्चितed.
 */
bool siox_device_connected(काष्ठा siox_device *sdevice)
अणु
	अगर (!siox_device_synced(sdevice))
		वापस false;

	वापस !siox_device_wdg_error(sdevice, sdevice->status_पढ़ो_clean);
पूर्ण
EXPORT_SYMBOL_GPL(siox_device_connected);

अटल व्योम siox_poll(काष्ठा siox_master *smaster)
अणु
	काष्ठा siox_device *sdevice;
	माप_प्रकार i = smaster->रखो_बफ_len;
	अचिन्हित पूर्णांक devno = 0;
	पूर्णांक unsync_error = 0;

	smaster->last_poll = jअगरfies;

	/*
	 * The counter bits change in each second cycle, the watchकरोg bit
	 * toggles each समय.
	 * The counter bits hold values from [0, 6]. 7 would be possible
	 * theoretically but the protocol designer considered that a bad idea
	 * क्रम reasons unknown today. (Maybe that's because then the status पढ़ो
	 * back has only zeros in the counter bits then which might be confused
	 * with a stuck-at-0 error. But क्रम the same reason (with s/0/1/) 0
	 * could be skipped.)
	 */
	अगर (++smaster->status > 0x0d)
		smaster->status = 0;

	स_रखो(smaster->buf, 0, smaster->रखो_बफ_len);

	/* prepare data pushed out to devices in buf[0..रखो_बफ_len) */
	list_क्रम_each_entry(sdevice, &smaster->devices, node) अणु
		काष्ठा siox_driver *sdriver =
			to_siox_driver(sdevice->dev.driver);
		sdevice->status_written = smaster->status;

		i -= sdevice->inbytes;

		/*
		 * If the device or a previous one is unsynced, करोn't pet the
		 * watchकरोg. This is करोne to ensure that the device is kept in
		 * reset when something is wrong.
		 */
		अगर (!siox_device_synced(sdevice))
			unsync_error = 1;

		अगर (sdriver && !unsync_error)
			sdriver->set_data(sdevice, sdevice->status_written,
					  &smaster->buf[i + 1]);
		अन्यथा
			/*
			 * Don't trigger watchकरोg अगर there is no driver or a
			 * sync problem
			 */
			sdevice->status_written &= ~SIOX_STATUS_WDG;

		smaster->buf[i] = sdevice->status_written;

		trace_siox_set_data(smaster, sdevice, devno, i);

		devno++;
	पूर्ण

	smaster->pushpull(smaster, smaster->रखो_बफ_len, smaster->buf,
			  smaster->getbuf_len,
			  smaster->buf + smaster->रखो_बफ_len);

	unsync_error = 0;

	/* पूर्णांकerpret data pulled in from devices in buf[रखो_बफ_len..] */
	devno = 0;
	i = smaster->रखो_बफ_len;
	list_क्रम_each_entry(sdevice, &smaster->devices, node) अणु
		काष्ठा siox_driver *sdriver =
			to_siox_driver(sdevice->dev.driver);
		u8 status = smaster->buf[i + sdevice->outbytes - 1];
		u8 status_clean;
		u8 prev_status_clean = sdevice->status_पढ़ो_clean;
		bool synced = true;
		bool connected = true;

		अगर (!siox_device_synced(sdevice))
			unsync_error = 1;

		/*
		 * If the watchकरोg bit wasn't toggled in this cycle, report the
		 * watchकरोg as active to give a consistent view क्रम drivers and
		 * sysfs consumers.
		 */
		अगर (!sdriver || unsync_error)
			status &= ~SIOX_STATUS_WDG;

		status_clean =
			siox_status_clean(status,
					  sdevice->status_written_lastcycle);

		/* Check counter and type bits */
		अगर (siox_device_counter_error(sdevice, status_clean) ||
		    siox_device_type_error(sdevice, status_clean)) अणु
			bool prev_error;

			synced = false;

			/* only report a new error अगर the last cycle was ok */
			prev_error =
				siox_device_counter_error(sdevice,
							  prev_status_clean) ||
				siox_device_type_error(sdevice,
						       prev_status_clean);

			अगर (!prev_error) अणु
				sdevice->status_errors++;
				sysfs_notअगरy_dirent(sdevice->status_errors_kn);
			पूर्ण
		पूर्ण

		/* If the device is unsynced report the watchकरोg as active */
		अगर (!synced) अणु
			status &= ~SIOX_STATUS_WDG;
			status_clean &= ~SIOX_STATUS_WDG;
		पूर्ण

		अगर (siox_device_wdg_error(sdevice, status_clean))
			connected = false;

		/* The watchकरोg state changed just now */
		अगर ((status_clean ^ prev_status_clean) & SIOX_STATUS_WDG) अणु
			sysfs_notअगरy_dirent(sdevice->watchकरोg_kn);

			अगर (siox_device_wdg_error(sdevice, status_clean)) अणु
				काष्ठा kernfs_node *wd_errs =
					sdevice->watchकरोg_errors_kn;

				sdevice->watchकरोg_errors++;
				sysfs_notअगरy_dirent(wd_errs);
			पूर्ण
		पूर्ण

		अगर (connected != sdevice->connected)
			sysfs_notअगरy_dirent(sdevice->connected_kn);

		sdevice->status_पढ़ो_clean = status_clean;
		sdevice->status_written_lastcycle = sdevice->status_written;
		sdevice->connected = connected;

		trace_siox_get_data(smaster, sdevice, devno, status_clean, i);

		/* only give data पढ़ो to driver अगर the device is connected */
		अगर (sdriver && connected)
			sdriver->get_data(sdevice, &smaster->buf[i]);

		devno++;
		i += sdevice->outbytes;
	पूर्ण
पूर्ण

अटल पूर्णांक siox_poll_thपढ़ो(व्योम *data)
अणु
	काष्ठा siox_master *smaster = data;
	चिन्हित दीर्घ समयout = 0;

	get_device(&smaster->dev);

	क्रम (;;) अणु
		अगर (kthपढ़ो_should_stop()) अणु
			put_device(&smaster->dev);
			वापस 0;
		पूर्ण

		siox_master_lock(smaster);

		अगर (smaster->active) अणु
			अचिन्हित दीर्घ next_poll =
				smaster->last_poll + smaster->poll_पूर्णांकerval;
			अगर (समय_is_beक्रमe_eq_jअगरfies(next_poll))
				siox_poll(smaster);

			समयout = smaster->poll_पूर्णांकerval -
				(jअगरfies - smaster->last_poll);
		पूर्ण अन्यथा अणु
			समयout = MAX_SCHEDULE_TIMEOUT;
		पूर्ण

		/*
		 * Set the task to idle जबतक holding the lock. This makes sure
		 * that we करोn't sleep too दीर्घ when the bus is reenabled beक्रमe
		 * schedule_समयout is reached.
		 */
		अगर (समयout > 0)
			set_current_state(TASK_IDLE);

		siox_master_unlock(smaster);

		अगर (समयout > 0)
			schedule_समयout(समयout);

		/*
		 * I'm not clear अगर/why it is important to set the state to
		 * RUNNING again, but it fixes a "करो not call blocking ops when
		 * !TASK_RUNNING;"-warning.
		 */
		set_current_state(TASK_RUNNING);
	पूर्ण
पूर्ण

अटल पूर्णांक __siox_start(काष्ठा siox_master *smaster)
अणु
	अगर (!(smaster->रखो_बफ_len + smaster->getbuf_len))
		वापस -ENODEV;

	अगर (!smaster->buf)
		वापस -ENOMEM;

	अगर (smaster->active)
		वापस 0;

	smaster->active = 1;
	wake_up_process(smaster->poll_thपढ़ो);

	वापस 1;
पूर्ण

अटल पूर्णांक siox_start(काष्ठा siox_master *smaster)
अणु
	पूर्णांक ret;

	siox_master_lock(smaster);
	ret = __siox_start(smaster);
	siox_master_unlock(smaster);

	वापस ret;
पूर्ण

अटल पूर्णांक __siox_stop(काष्ठा siox_master *smaster)
अणु
	अगर (smaster->active) अणु
		काष्ठा siox_device *sdevice;

		smaster->active = 0;

		list_क्रम_each_entry(sdevice, &smaster->devices, node) अणु
			अगर (sdevice->connected)
				sysfs_notअगरy_dirent(sdevice->connected_kn);
			sdevice->connected = false;
		पूर्ण

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक siox_stop(काष्ठा siox_master *smaster)
अणु
	पूर्णांक ret;

	siox_master_lock(smaster);
	ret = __siox_stop(smaster);
	siox_master_unlock(smaster);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);

	वापस प्र_लिखो(buf, "%s\n", sdev->type);
पूर्ण

अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार inbytes_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);

	वापस प्र_लिखो(buf, "%zu\n", sdev->inbytes);
पूर्ण

अटल DEVICE_ATTR_RO(inbytes);

अटल sमाप_प्रकार outbytes_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);

	वापस प्र_लिखो(buf, "%zu\n", sdev->outbytes);
पूर्ण

अटल DEVICE_ATTR_RO(outbytes);

अटल sमाप_प्रकार status_errors_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);
	अचिन्हित पूर्णांक status_errors;

	siox_master_lock(sdev->smaster);

	status_errors = sdev->status_errors;

	siox_master_unlock(sdev->smaster);

	वापस प्र_लिखो(buf, "%u\n", status_errors);
पूर्ण

अटल DEVICE_ATTR_RO(status_errors);

अटल sमाप_प्रकार connected_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);
	bool connected;

	siox_master_lock(sdev->smaster);

	connected = sdev->connected;

	siox_master_unlock(sdev->smaster);

	वापस प्र_लिखो(buf, "%u\n", connected);
पूर्ण

अटल DEVICE_ATTR_RO(connected);

अटल sमाप_प्रकार watchकरोg_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);
	u8 status;

	siox_master_lock(sdev->smaster);

	status = sdev->status_पढ़ो_clean;

	siox_master_unlock(sdev->smaster);

	वापस प्र_लिखो(buf, "%d\n", status & SIOX_STATUS_WDG);
पूर्ण

अटल DEVICE_ATTR_RO(watchकरोg);

अटल sमाप_प्रकार watchकरोg_errors_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_device *sdev = to_siox_device(dev);
	अचिन्हित पूर्णांक watchकरोg_errors;

	siox_master_lock(sdev->smaster);

	watchकरोg_errors = sdev->watchकरोg_errors;

	siox_master_unlock(sdev->smaster);

	वापस प्र_लिखो(buf, "%u\n", watchकरोg_errors);
पूर्ण

अटल DEVICE_ATTR_RO(watchकरोg_errors);

अटल काष्ठा attribute *siox_device_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_inbytes.attr,
	&dev_attr_outbytes.attr,
	&dev_attr_status_errors.attr,
	&dev_attr_connected.attr,
	&dev_attr_watchकरोg.attr,
	&dev_attr_watchकरोg_errors.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(siox_device);

अटल व्योम siox_device_release(काष्ठा device *dev)
अणु
	काष्ठा siox_device *sdevice = to_siox_device(dev);

	kमुक्त(sdevice);
पूर्ण

अटल काष्ठा device_type siox_device_type = अणु
	.groups = siox_device_groups,
	.release = siox_device_release,
पूर्ण;

अटल पूर्णांक siox_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	अगर (dev->type != &siox_device_type)
		वापस 0;

	/* up to now there is only a single driver so keeping this simple */
	वापस 1;
पूर्ण

अटल पूर्णांक siox_probe(काष्ठा device *dev)
अणु
	काष्ठा siox_driver *sdriver = to_siox_driver(dev->driver);
	काष्ठा siox_device *sdevice = to_siox_device(dev);

	वापस sdriver->probe(sdevice);
पूर्ण

अटल पूर्णांक siox_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा siox_driver *sdriver =
		container_of(dev->driver, काष्ठा siox_driver, driver);
	काष्ठा siox_device *sdevice = to_siox_device(dev);

	अगर (sdriver->हटाओ)
		sdriver->हटाओ(sdevice);

	वापस 0;
पूर्ण

अटल व्योम siox_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा siox_device *sdevice = to_siox_device(dev);
	काष्ठा siox_driver *sdriver;

	अगर (!dev->driver)
		वापस;

	sdriver = container_of(dev->driver, काष्ठा siox_driver, driver);
	अगर (sdriver->shutकरोwn)
		sdriver->shutकरोwn(sdevice);
पूर्ण

अटल काष्ठा bus_type siox_bus_type = अणु
	.name = "siox",
	.match = siox_match,
	.probe = siox_probe,
	.हटाओ = siox_हटाओ,
	.shutकरोwn = siox_shutकरोwn,
पूर्ण;

अटल sमाप_प्रकार active_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);

	वापस प्र_लिखो(buf, "%d\n", smaster->active);
पूर्ण

अटल sमाप_प्रकार active_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);
	पूर्णांक ret;
	पूर्णांक active;

	ret = kstrtoपूर्णांक(buf, 0, &active);
	अगर (ret < 0)
		वापस ret;

	अगर (active)
		ret = siox_start(smaster);
	अन्यथा
		ret = siox_stop(smaster);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(active);

अटल काष्ठा siox_device *siox_device_add(काष्ठा siox_master *smaster,
					   स्थिर अक्षर *type, माप_प्रकार inbytes,
					   माप_प्रकार outbytes, u8 statustype);

अटल sमाप_प्रकार device_add_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);
	पूर्णांक ret;
	अक्षर type[20] = "";
	माप_प्रकार inbytes = 0, outbytes = 0;
	u8 statustype = 0;

	ret = माला_पूछो(buf, "%19s %zu %zu %hhu", type, &inbytes,
		     &outbytes, &statustype);
	अगर (ret != 3 && ret != 4)
		वापस -EINVAL;

	अगर (म_भेद(type, "siox-12x8") || inbytes != 2 || outbytes != 4)
		वापस -EINVAL;

	siox_device_add(smaster, "siox-12x8", inbytes, outbytes, statustype);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(device_add);

अटल व्योम siox_device_हटाओ(काष्ठा siox_master *smaster);

अटल sमाप_प्रकार device_हटाओ_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);

	/* XXX? require to ग_लिखो <type> <inbytes> <outbytes> */
	siox_device_हटाओ(smaster);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(device_हटाओ);

अटल sमाप_प्रकार poll_पूर्णांकerval_ns_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);

	वापस प्र_लिखो(buf, "%lld\n", jअगरfies_to_nsecs(smaster->poll_पूर्णांकerval));
पूर्ण

अटल sमाप_प्रकार poll_पूर्णांकerval_ns_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);
	पूर्णांक ret;
	u64 val;

	ret = kstrtou64(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	siox_master_lock(smaster);

	smaster->poll_पूर्णांकerval = nsecs_to_jअगरfies(val);

	siox_master_unlock(smaster);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(poll_पूर्णांकerval_ns);

अटल काष्ठा attribute *siox_master_attrs[] = अणु
	&dev_attr_active.attr,
	&dev_attr_device_add.attr,
	&dev_attr_device_हटाओ.attr,
	&dev_attr_poll_पूर्णांकerval_ns.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(siox_master);

अटल व्योम siox_master_release(काष्ठा device *dev)
अणु
	काष्ठा siox_master *smaster = to_siox_master(dev);

	kमुक्त(smaster);
पूर्ण

अटल काष्ठा device_type siox_master_type = अणु
	.groups = siox_master_groups,
	.release = siox_master_release,
पूर्ण;

काष्ठा siox_master *siox_master_alloc(काष्ठा device *dev,
				      माप_प्रकार size)
अणु
	काष्ठा siox_master *smaster;

	अगर (!dev)
		वापस शून्य;

	smaster = kzalloc(माप(*smaster) + size, GFP_KERNEL);
	अगर (!smaster)
		वापस शून्य;

	device_initialize(&smaster->dev);

	smaster->busno = -1;
	smaster->dev.bus = &siox_bus_type;
	smaster->dev.type = &siox_master_type;
	smaster->dev.parent = dev;
	smaster->poll_पूर्णांकerval = DIV_ROUND_UP(HZ, 40);

	dev_set_drvdata(&smaster->dev, &smaster[1]);

	वापस smaster;
पूर्ण
EXPORT_SYMBOL_GPL(siox_master_alloc);

पूर्णांक siox_master_रेजिस्टर(काष्ठा siox_master *smaster)
अणु
	पूर्णांक ret;

	अगर (!siox_is_रेजिस्टरed)
		वापस -EPROBE_DEFER;

	अगर (!smaster->pushpull)
		वापस -EINVAL;

	dev_set_name(&smaster->dev, "siox-%d", smaster->busno);

	mutex_init(&smaster->lock);
	INIT_LIST_HEAD(&smaster->devices);

	smaster->last_poll = jअगरfies;
	smaster->poll_thपढ़ो = kthपढ़ो_run(siox_poll_thपढ़ो, smaster,
					   "siox-%d", smaster->busno);
	अगर (IS_ERR(smaster->poll_thपढ़ो)) अणु
		smaster->active = 0;
		वापस PTR_ERR(smaster->poll_thपढ़ो);
	पूर्ण

	ret = device_add(&smaster->dev);
	अगर (ret)
		kthपढ़ो_stop(smaster->poll_thपढ़ो);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(siox_master_रेजिस्टर);

व्योम siox_master_unरेजिस्टर(काष्ठा siox_master *smaster)
अणु
	/* हटाओ device */
	device_del(&smaster->dev);

	siox_master_lock(smaster);

	__siox_stop(smaster);

	जबतक (smaster->num_devices) अणु
		काष्ठा siox_device *sdevice;

		sdevice = container_of(smaster->devices.prev,
				       काष्ठा siox_device, node);
		list_del(&sdevice->node);
		smaster->num_devices--;

		siox_master_unlock(smaster);

		device_unरेजिस्टर(&sdevice->dev);

		siox_master_lock(smaster);
	पूर्ण

	siox_master_unlock(smaster);

	put_device(&smaster->dev);
पूर्ण
EXPORT_SYMBOL_GPL(siox_master_unरेजिस्टर);

अटल काष्ठा siox_device *siox_device_add(काष्ठा siox_master *smaster,
					   स्थिर अक्षर *type, माप_प्रकार inbytes,
					   माप_प्रकार outbytes, u8 statustype)
अणु
	काष्ठा siox_device *sdevice;
	पूर्णांक ret;
	माप_प्रकार buf_len;

	sdevice = kzalloc(माप(*sdevice), GFP_KERNEL);
	अगर (!sdevice)
		वापस ERR_PTR(-ENOMEM);

	sdevice->type = type;
	sdevice->inbytes = inbytes;
	sdevice->outbytes = outbytes;
	sdevice->statustype = statustype;

	sdevice->smaster = smaster;
	sdevice->dev.parent = &smaster->dev;
	sdevice->dev.bus = &siox_bus_type;
	sdevice->dev.type = &siox_device_type;

	siox_master_lock(smaster);

	dev_set_name(&sdevice->dev, "siox-%d-%d",
		     smaster->busno, smaster->num_devices);

	buf_len = smaster->रखो_बफ_len + inbytes +
		smaster->getbuf_len + outbytes;
	अगर (smaster->buf_len < buf_len) अणु
		u8 *buf = kपुनः_स्मृति(smaster->buf, buf_len, GFP_KERNEL);

		अगर (!buf) अणु
			dev_err(&smaster->dev,
				"failed to realloc buffer to %zu\n", buf_len);
			ret = -ENOMEM;
			जाओ err_buf_alloc;
		पूर्ण

		smaster->buf_len = buf_len;
		smaster->buf = buf;
	पूर्ण

	ret = device_रेजिस्टर(&sdevice->dev);
	अगर (ret) अणु
		dev_err(&smaster->dev, "failed to register device: %d\n", ret);

		जाओ err_device_रेजिस्टर;
	पूर्ण

	smaster->num_devices++;
	list_add_tail(&sdevice->node, &smaster->devices);

	smaster->रखो_बफ_len += sdevice->inbytes;
	smaster->getbuf_len += sdevice->outbytes;

	sdevice->status_errors_kn = sysfs_get_dirent(sdevice->dev.kobj.sd,
						     "status_errors");
	sdevice->watchकरोg_kn = sysfs_get_dirent(sdevice->dev.kobj.sd,
						"watchdog");
	sdevice->watchकरोg_errors_kn = sysfs_get_dirent(sdevice->dev.kobj.sd,
						       "watchdog_errors");
	sdevice->connected_kn = sysfs_get_dirent(sdevice->dev.kobj.sd,
						 "connected");

	siox_master_unlock(smaster);

	वापस sdevice;

err_device_रेजिस्टर:
	/* करोn't care to make the buffer smaller again */

err_buf_alloc:
	siox_master_unlock(smaster);

	kमुक्त(sdevice);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम siox_device_हटाओ(काष्ठा siox_master *smaster)
अणु
	काष्ठा siox_device *sdevice;

	siox_master_lock(smaster);

	अगर (!smaster->num_devices) अणु
		siox_master_unlock(smaster);
		वापस;
	पूर्ण

	sdevice = container_of(smaster->devices.prev, काष्ठा siox_device, node);
	list_del(&sdevice->node);
	smaster->num_devices--;

	smaster->रखो_बफ_len -= sdevice->inbytes;
	smaster->getbuf_len -= sdevice->outbytes;

	अगर (!smaster->num_devices)
		__siox_stop(smaster);

	siox_master_unlock(smaster);

	/*
	 * This must be करोne without holding the master lock because we're
	 * called from device_हटाओ_store which also holds a sysfs mutex.
	 * device_unरेजिस्टर tries to aquire the same lock.
	 */
	device_unरेजिस्टर(&sdevice->dev);
पूर्ण

पूर्णांक __siox_driver_रेजिस्टर(काष्ठा siox_driver *sdriver, काष्ठा module *owner)
अणु
	पूर्णांक ret;

	अगर (unlikely(!siox_is_रेजिस्टरed))
		वापस -EPROBE_DEFER;

	अगर (!sdriver->probe ||
	    (!sdriver->set_data && !sdriver->get_data)) अणु
		pr_err("Driver %s doesn't provide needed callbacks\n",
		       sdriver->driver.name);
		वापस -EINVAL;
	पूर्ण

	sdriver->driver.owner = owner;
	sdriver->driver.bus = &siox_bus_type;

	ret = driver_रेजिस्टर(&sdriver->driver);
	अगर (ret)
		pr_err("Failed to register siox driver %s (%d)\n",
		       sdriver->driver.name, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__siox_driver_रेजिस्टर);

अटल पूर्णांक __init siox_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&siox_bus_type);
	अगर (ret) अणु
		pr_err("Registration of SIOX bus type failed: %d\n", ret);
		वापस ret;
	पूर्ण

	siox_is_रेजिस्टरed = true;

	वापस 0;
पूर्ण
subsys_initcall(siox_init);

अटल व्योम __निकास siox_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&siox_bus_type);
पूर्ण
module_निकास(siox_निकास);

MODULE_AUTHOR("Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>");
MODULE_DESCRIPTION("Eckelmann SIOX driver core");
MODULE_LICENSE("GPL v2");
