<शैली गुरु>
/*
 * Core maple bus functionality
 *
 *  Copyright (C) 2007 - 2009 Adrian McMenamin
 *  Copyright (C) 2001 - 2008 Paul Mundt
 *  Copyright (C) 2000 - 2001 YAEGASHI Takeshi
 *  Copyright (C) 2001 M. R. Brown
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/maple.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach/dma.h>
#समावेश <mach/sysasic.h>

MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk>");
MODULE_DESCRIPTION("Maple bus driver for Dreamcast");
MODULE_LICENSE("GPL v2");

अटल व्योम maple_dma_handler(काष्ठा work_काष्ठा *work);
अटल व्योम maple_vblank_handler(काष्ठा work_काष्ठा *work);

अटल DECLARE_WORK(maple_dma_process, maple_dma_handler);
अटल DECLARE_WORK(maple_vblank_process, maple_vblank_handler);

अटल LIST_HEAD(maple_रुकोq);
अटल LIST_HEAD(maple_sentq);

/* mutex to protect queue of रुकोing packets */
अटल DEFINE_MUTEX(maple_wlist_lock);

अटल काष्ठा maple_driver maple_unsupported_device;
अटल काष्ठा device maple_bus;
अटल पूर्णांक subdevice_map[MAPLE_PORTS];
अटल अचिन्हित दीर्घ *maple_sendbuf, *maple_sendptr, *maple_lastptr;
अटल अचिन्हित दीर्घ maple_pnp_समय;
अटल पूर्णांक started, scanning, fullscan;
अटल काष्ठा kmem_cache *maple_queue_cache;

काष्ठा maple_device_specअगरy अणु
	पूर्णांक port;
	पूर्णांक unit;
पूर्ण;

अटल bool checked[MAPLE_PORTS];
अटल bool empty[MAPLE_PORTS];
अटल काष्ठा maple_device *baseunits[MAPLE_PORTS];

/**
 * maple_driver_रेजिस्टर - रेजिस्टर a maple driver
 * @drv: maple driver to be रेजिस्टरed.
 *
 * Registers the passed in @drv, जबतक updating the bus type.
 * Devices with matching function IDs will be स्वतःmatically probed.
 */
पूर्णांक maple_driver_रेजिस्टर(काष्ठा maple_driver *drv)
अणु
	अगर (!drv)
		वापस -EINVAL;

	drv->drv.bus = &maple_bus_type;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(maple_driver_रेजिस्टर);

/**
 * maple_driver_unरेजिस्टर - unरेजिस्टर a maple driver.
 * @drv: maple driver to unरेजिस्टर.
 *
 * Cleans up after maple_driver_रेजिस्टर(). To be invoked in the निकास
 * path of any module drivers.
 */
व्योम maple_driver_unरेजिस्टर(काष्ठा maple_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(maple_driver_unरेजिस्टर);

/* set hardware रेजिस्टरs to enable next round of dma */
अटल व्योम maple_dma_reset(व्योम)
अणु
	__raw_ग_लिखोl(MAPLE_MAGIC, MAPLE_RESET);
	/* set trig type to 0 क्रम software trigger, 1 क्रम hardware (VBLANK) */
	__raw_ग_लिखोl(1, MAPLE_TRIGTYPE);
	/*
	* Maple प्रणाली रेजिस्टर
	* bits 31 - 16	समयout in units of 20nsec
	* bit 12	hard trigger - set 0 to keep responding to VBLANK
	* bits 9 - 8	set 00 क्रम 2 Mbps, 01 क्रम 1 Mbps
	* bits 3 - 0	delay (in 1.3ms) between VBLANK and start of DMA
	* max delay is 11
	*/
	__raw_ग_लिखोl(MAPLE_2MBPS | MAPLE_TIMEOUT(0xFFFF), MAPLE_SPEED);
	__raw_ग_लिखोl(virt_to_phys(maple_sendbuf), MAPLE_DMAADDR);
	__raw_ग_लिखोl(1, MAPLE_ENABLE);
पूर्ण

/**
 * maple_अ_लोond_callback - setup handling MAPLE_COMMAND_GETCOND
 * @dev: device responding
 * @callback: handler callback
 * @पूर्णांकerval: पूर्णांकerval in jअगरfies between callbacks
 * @function: the function code क्रम the device
 */
व्योम maple_अ_लोond_callback(काष्ठा maple_device *dev,
			व्योम (*callback) (काष्ठा mapleq *mq),
			अचिन्हित दीर्घ पूर्णांकerval, अचिन्हित दीर्घ function)
अणु
	dev->callback = callback;
	dev->पूर्णांकerval = पूर्णांकerval;
	dev->function = cpu_to_be32(function);
	dev->when = jअगरfies;
पूर्ण
EXPORT_SYMBOL_GPL(maple_अ_लोond_callback);

अटल पूर्णांक maple_dma_करोne(व्योम)
अणु
	वापस (__raw_पढ़ोl(MAPLE_STATE) & 1) == 0;
पूर्ण

अटल व्योम maple_release_device(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev;
	काष्ठा mapleq *mq;

	mdev = to_maple_dev(dev);
	mq = mdev->mq;
	kmem_cache_मुक्त(maple_queue_cache, mq->recvbuf);
	kमुक्त(mq);
	kमुक्त(mdev);
पूर्ण

/**
 * maple_add_packet - add a single inकाष्ठाion to the maple bus queue
 * @mdev: maple device
 * @function: function on device being queried
 * @command: maple command to add
 * @length: length of command string (in 32 bit words)
 * @data: reमुख्यder of command string
 */
पूर्णांक maple_add_packet(काष्ठा maple_device *mdev, u32 function, u32 command,
	माप_प्रकार length, व्योम *data)
अणु
	पूर्णांक ret = 0;
	व्योम *sendbuf = शून्य;

	अगर (length) अणु
		sendbuf = kसुस्मृति(length, 4, GFP_KERNEL);
		अगर (!sendbuf) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		((__be32 *)sendbuf)[0] = cpu_to_be32(function);
	पूर्ण

	mdev->mq->command = command;
	mdev->mq->length = length;
	अगर (length > 1)
		स_नकल(sendbuf + 4, data, (length - 1) * 4);
	mdev->mq->sendbuf = sendbuf;

	mutex_lock(&maple_wlist_lock);
	list_add_tail(&mdev->mq->list, &maple_रुकोq);
	mutex_unlock(&maple_wlist_lock);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(maple_add_packet);

अटल काष्ठा mapleq *maple_allocq(काष्ठा maple_device *mdev)
अणु
	काष्ठा mapleq *mq;

	mq = kzalloc(माप(*mq), GFP_KERNEL);
	अगर (!mq)
		जाओ failed_nomem;

	INIT_LIST_HEAD(&mq->list);
	mq->dev = mdev;
	mq->recvbuf = kmem_cache_zalloc(maple_queue_cache, GFP_KERNEL);
	अगर (!mq->recvbuf)
		जाओ failed_p2;
	mq->recvbuf->buf = &((mq->recvbuf->bufx)[0]);

	वापस mq;

failed_p2:
	kमुक्त(mq);
failed_nomem:
	dev_err(&mdev->dev, "could not allocate memory for device (%d, %d)\n",
		mdev->port, mdev->unit);
	वापस शून्य;
पूर्ण

अटल काष्ठा maple_device *maple_alloc_dev(पूर्णांक port, पूर्णांक unit)
अणु
	काष्ठा maple_device *mdev;

	/* zero this out to aव्योम kobj subप्रणाली
	* thinking it has alपढ़ोy been रेजिस्टरed */

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस शून्य;

	mdev->port = port;
	mdev->unit = unit;

	mdev->mq = maple_allocq(mdev);

	अगर (!mdev->mq) अणु
		kमुक्त(mdev);
		वापस शून्य;
	पूर्ण
	mdev->dev.bus = &maple_bus_type;
	mdev->dev.parent = &maple_bus;
	init_रुकोqueue_head(&mdev->maple_रुको);
	वापस mdev;
पूर्ण

अटल व्योम maple_मुक्त_dev(काष्ठा maple_device *mdev)
अणु
	kmem_cache_मुक्त(maple_queue_cache, mdev->mq->recvbuf);
	kमुक्त(mdev->mq);
	kमुक्त(mdev);
पूर्ण

/* process the command queue पूर्णांकo a maple command block
 * terminating command has bit 32 of first दीर्घ set to 0
 */
अटल व्योम maple_build_block(काष्ठा mapleq *mq)
अणु
	पूर्णांक port, unit, from, to, len;
	अचिन्हित दीर्घ *lsendbuf = mq->sendbuf;

	port = mq->dev->port & 3;
	unit = mq->dev->unit;
	len = mq->length;
	from = port << 6;
	to = (port << 6) | (unit > 0 ? (1 << (unit - 1)) & 0x1f : 0x20);

	*maple_lastptr &= 0x7fffffff;
	maple_lastptr = maple_sendptr;

	*maple_sendptr++ = (port << 16) | len | 0x80000000;
	*maple_sendptr++ = virt_to_phys(mq->recvbuf->buf);
	*maple_sendptr++ =
	    mq->command | (to << 8) | (from << 16) | (len << 24);
	जबतक (len-- > 0)
		*maple_sendptr++ = *lsendbuf++;
पूर्ण

/* build up command queue */
अटल व्योम maple_send(व्योम)
अणु
	पूर्णांक i, maple_packets = 0;
	काष्ठा mapleq *mq, *nmq;

	अगर (!maple_dma_करोne())
		वापस;

	/* disable DMA */
	__raw_ग_लिखोl(0, MAPLE_ENABLE);

	अगर (!list_empty(&maple_sentq))
		जाओ finish;

	mutex_lock(&maple_wlist_lock);
	अगर (list_empty(&maple_रुकोq)) अणु
		mutex_unlock(&maple_wlist_lock);
		जाओ finish;
	पूर्ण

	maple_lastptr = maple_sendbuf;
	maple_sendptr = maple_sendbuf;

	list_क्रम_each_entry_safe(mq, nmq, &maple_रुकोq, list) अणु
		maple_build_block(mq);
		list_del_init(&mq->list);
		list_add_tail(&mq->list, &maple_sentq);
		अगर (maple_packets++ > MAPLE_MAXPACKETS)
			अवरोध;
	पूर्ण
	mutex_unlock(&maple_wlist_lock);
	अगर (maple_packets > 0) अणु
		क्रम (i = 0; i < (1 << MAPLE_DMA_PAGES); i++)
			__flush_purge_region(maple_sendbuf + i * PAGE_SIZE,
					PAGE_SIZE);
	पूर्ण

finish:
	maple_dma_reset();
पूर्ण

/* check अगर there is a driver रेजिस्टरed likely to match this device */
अटल पूर्णांक maple_check_matching_driver(काष्ठा device_driver *driver,
					व्योम *devptr)
अणु
	काष्ठा maple_driver *maple_drv;
	काष्ठा maple_device *mdev;

	mdev = devptr;
	maple_drv = to_maple_driver(driver);
	अगर (mdev->devinfo.function & cpu_to_be32(maple_drv->function))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम maple_detach_driver(काष्ठा maple_device *mdev)
अणु
	device_unरेजिस्टर(&mdev->dev);
पूर्ण

/* process initial MAPLE_COMMAND_DEVINFO क्रम each device or port */
अटल व्योम maple_attach_driver(काष्ठा maple_device *mdev)
अणु
	अक्षर *p, *recvbuf;
	अचिन्हित दीर्घ function;
	पूर्णांक matched, error;

	recvbuf = mdev->mq->recvbuf->buf;
	/* copy the data as inभागidual elements in
	* हाल of memory optimisation */
	स_नकल(&mdev->devinfo.function, recvbuf + 4, 4);
	स_नकल(&mdev->devinfo.function_data[0], recvbuf + 8, 12);
	स_नकल(&mdev->devinfo.area_code, recvbuf + 20, 1);
	स_नकल(&mdev->devinfo.connector_direction, recvbuf + 21, 1);
	स_नकल(&mdev->devinfo.product_name[0], recvbuf + 22, 30);
	स_नकल(&mdev->devinfo.standby_घातer, recvbuf + 112, 2);
	स_नकल(&mdev->devinfo.max_घातer, recvbuf + 114, 2);
	स_नकल(mdev->product_name, mdev->devinfo.product_name, 30);
	mdev->product_name[30] = '\0';
	स_नकल(mdev->product_licence, mdev->devinfo.product_licence, 60);
	mdev->product_licence[60] = '\0';

	क्रम (p = mdev->product_name + 29; mdev->product_name <= p; p--)
		अगर (*p == ' ')
			*p = '\0';
		अन्यथा
			अवरोध;
	क्रम (p = mdev->product_licence + 59; mdev->product_licence <= p; p--)
		अगर (*p == ' ')
			*p = '\0';
		अन्यथा
			अवरोध;

	function = be32_to_cpu(mdev->devinfo.function);

	dev_info(&mdev->dev, "detected %s: function 0x%lX: at (%d, %d)\n",
		mdev->product_name, function, mdev->port, mdev->unit);

	अगर (function > 0x200) अणु
		/* Do this silently - as not a real device */
		function = 0;
		mdev->driver = &maple_unsupported_device;
		dev_set_name(&mdev->dev, "%d:0.port", mdev->port);
	पूर्ण अन्यथा अणु
		matched =
			bus_क्रम_each_drv(&maple_bus_type, शून्य, mdev,
				maple_check_matching_driver);

		अगर (matched == 0) अणु
			/* Driver करोes not exist yet */
			dev_info(&mdev->dev, "no driver found\n");
			mdev->driver = &maple_unsupported_device;
		पूर्ण
		dev_set_name(&mdev->dev, "%d:0%d.%lX", mdev->port,
			     mdev->unit, function);
	पूर्ण

	mdev->function = function;
	mdev->dev.release = &maple_release_device;

	atomic_set(&mdev->busy, 0);
	error = device_रेजिस्टर(&mdev->dev);
	अगर (error) अणु
		dev_warn(&mdev->dev, "could not register device at"
			" (%d, %d), with error 0x%X\n", mdev->unit,
			mdev->port, error);
		maple_मुक्त_dev(mdev);
		mdev = शून्य;
		वापस;
	पूर्ण
पूर्ण

/*
 * अगर device has been रेजिस्टरed क्रम the given
 * port and unit then वापस 1 - allows identअगरication
 * of which devices need to be attached or detached
 */
अटल पूर्णांक check_maple_device(काष्ठा device *device, व्योम *portptr)
अणु
	काष्ठा maple_device_specअगरy *ds;
	काष्ठा maple_device *mdev;

	ds = portptr;
	mdev = to_maple_dev(device);
	अगर (mdev->port == ds->port && mdev->unit == ds->unit)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_maple_commands(काष्ठा device *device, व्योम *ignored)
अणु
	पूर्णांक add;
	काष्ठा maple_device *mdev = to_maple_dev(device);
	अगर (mdev->पूर्णांकerval > 0 && atomic_पढ़ो(&mdev->busy) == 0 &&
		समय_after(jअगरfies, mdev->when)) अणु
		/* bounce अगर we cannot add */
		add = maple_add_packet(mdev,
			be32_to_cpu(mdev->devinfo.function),
			MAPLE_COMMAND_GETCOND, 1, शून्य);
		अगर (!add)
			mdev->when = jअगरfies + mdev->पूर्णांकerval;
	पूर्ण अन्यथा अणु
		अगर (समय_after(jअगरfies, maple_pnp_समय))
			/* Ensure we करोn't have block पढ़ोs and devinfo
			* calls पूर्णांकerfering with one another - so flag the
			* device as busy */
			अगर (atomic_पढ़ो(&mdev->busy) == 0) अणु
				atomic_set(&mdev->busy, 1);
				maple_add_packet(mdev, 0,
					MAPLE_COMMAND_DEVINFO, 0, शून्य);
			पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* VBLANK bottom half - implemented via workqueue */
अटल व्योम maple_vblank_handler(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक x, locking;
	काष्ठा maple_device *mdev;

	अगर (!maple_dma_करोne())
		वापस;

	__raw_ग_लिखोl(0, MAPLE_ENABLE);

	अगर (!list_empty(&maple_sentq))
		जाओ finish;

	/*
	* Set up essential commands - to fetch data and
	* check devices are still present
	*/
	bus_क्रम_each_dev(&maple_bus_type, शून्य, शून्य,
		setup_maple_commands);

	अगर (समय_after(jअगरfies, maple_pnp_समय)) अणु
		/*
		* Scan the empty ports - bus is flakey and may have
		* mis-reported emptyness
		*/
		क्रम (x = 0; x < MAPLE_PORTS; x++) अणु
			अगर (checked[x] && empty[x]) अणु
				mdev = baseunits[x];
				अगर (!mdev)
					अवरोध;
				atomic_set(&mdev->busy, 1);
				locking = maple_add_packet(mdev, 0,
					MAPLE_COMMAND_DEVINFO, 0, शून्य);
				अगर (!locking)
					अवरोध;
				पूर्ण
			पूर्ण

		maple_pnp_समय = jअगरfies + MAPLE_PNP_INTERVAL;
	पूर्ण

finish:
	maple_send();
पूर्ण

/* handle devices added via hotplugs - placing them on queue क्रम DEVINFO */
अटल व्योम maple_map_subunits(काष्ठा maple_device *mdev, पूर्णांक submask)
अणु
	पूर्णांक retval, k, devcheck;
	काष्ठा maple_device *mdev_add;
	काष्ठा maple_device_specअगरy ds;

	ds.port = mdev->port;
	क्रम (k = 0; k < 5; k++) अणु
		ds.unit = k + 1;
		retval =
		    bus_क्रम_each_dev(&maple_bus_type, शून्य, &ds,
				     check_maple_device);
		अगर (retval) अणु
			submask = submask >> 1;
			जारी;
		पूर्ण
		devcheck = submask & 0x01;
		अगर (devcheck) अणु
			mdev_add = maple_alloc_dev(mdev->port, k + 1);
			अगर (!mdev_add)
				वापस;
			atomic_set(&mdev_add->busy, 1);
			maple_add_packet(mdev_add, 0, MAPLE_COMMAND_DEVINFO,
				0, शून्य);
			/* mark that we are checking sub devices */
			scanning = 1;
		पूर्ण
		submask = submask >> 1;
	पूर्ण
पूर्ण

/* mark a device as हटाओd */
अटल व्योम maple_clean_submap(काष्ठा maple_device *mdev)
अणु
	पूर्णांक समाप्तbit;

	समाप्तbit = (mdev->unit > 0 ? (1 << (mdev->unit - 1)) & 0x1f : 0x20);
	समाप्तbit = ~समाप्तbit;
	समाप्तbit &= 0xFF;
	subdevice_map[mdev->port] = subdevice_map[mdev->port] & समाप्तbit;
पूर्ण

/* handle empty port or hotplug removal */
अटल व्योम maple_response_none(काष्ठा maple_device *mdev)
अणु
	maple_clean_submap(mdev);

	अगर (likely(mdev->unit != 0)) अणु
		/*
		* Block devices play up
		* and give the impression they have
		* been हटाओd even when still in place or
		* trip the mtd layer when they have
		* really gone - this code traps that eventuality
		* and ensures we aren't overloaded with useless
		* error messages
		*/
		अगर (mdev->can_unload) अणु
			अगर (!mdev->can_unload(mdev)) अणु
				atomic_set(&mdev->busy, 2);
				wake_up(&mdev->maple_रुको);
				वापस;
			पूर्ण
		पूर्ण

		dev_info(&mdev->dev, "detaching device at (%d, %d)\n",
			mdev->port, mdev->unit);
		maple_detach_driver(mdev);
		वापस;
	पूर्ण अन्यथा अणु
		अगर (!started || !fullscan) अणु
			अगर (checked[mdev->port] == false) अणु
				checked[mdev->port] = true;
				empty[mdev->port] = true;
				dev_info(&mdev->dev, "no devices"
					" to port %d\n", mdev->port);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण
	/* Some hardware devices generate false detach messages on unit 0 */
	atomic_set(&mdev->busy, 0);
पूर्ण

/* preprocess hotplugs or scans */
अटल व्योम maple_response_devinfo(काष्ठा maple_device *mdev,
				   अक्षर *recvbuf)
अणु
	अक्षर submask;
	अगर (!started || (scanning == 2) || !fullscan) अणु
		अगर ((mdev->unit == 0) && (checked[mdev->port] == false)) अणु
			checked[mdev->port] = true;
			maple_attach_driver(mdev);
		पूर्ण अन्यथा अणु
			अगर (mdev->unit != 0)
				maple_attach_driver(mdev);
			अगर (mdev->unit == 0) अणु
				empty[mdev->port] = false;
				maple_attach_driver(mdev);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (mdev->unit == 0) अणु
		submask = recvbuf[2] & 0x1F;
		अगर (submask ^ subdevice_map[mdev->port]) अणु
			maple_map_subunits(mdev, submask);
			subdevice_map[mdev->port] = submask;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम maple_response_fileerr(काष्ठा maple_device *mdev, व्योम *recvbuf)
अणु
	अगर (mdev->fileerr_handler) अणु
		mdev->fileerr_handler(mdev, recvbuf);
		वापस;
	पूर्ण अन्यथा
		dev_warn(&mdev->dev, "device at (%d, %d) reports"
			"file error 0x%X\n", mdev->port, mdev->unit,
			((पूर्णांक *)recvbuf)[1]);
पूर्ण

अटल व्योम maple_port_rescan(व्योम)
अणु
	पूर्णांक i;
	काष्ठा maple_device *mdev;

	fullscan = 1;
	क्रम (i = 0; i < MAPLE_PORTS; i++) अणु
		अगर (checked[i] == false) अणु
			fullscan = 0;
			mdev = baseunits[i];
			maple_add_packet(mdev, 0, MAPLE_COMMAND_DEVINFO,
				0, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

/* maple dma end bottom half - implemented via workqueue */
अटल व्योम maple_dma_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mapleq *mq, *nmq;
	काष्ठा maple_device *mdev;
	अक्षर *recvbuf;
	क्रमागत maple_code code;

	अगर (!maple_dma_करोne())
		वापस;
	__raw_ग_लिखोl(0, MAPLE_ENABLE);
	अगर (!list_empty(&maple_sentq)) अणु
		list_क्रम_each_entry_safe(mq, nmq, &maple_sentq, list) अणु
			mdev = mq->dev;
			recvbuf = mq->recvbuf->buf;
			__flush_invalidate_region(sh_cacheop_vaddr(recvbuf),
					0x400);
			code = recvbuf[0];
			kमुक्त(mq->sendbuf);
			list_del_init(&mq->list);
			चयन (code) अणु
			हाल MAPLE_RESPONSE_NONE:
				maple_response_none(mdev);
				अवरोध;

			हाल MAPLE_RESPONSE_DEVINFO:
				maple_response_devinfo(mdev, recvbuf);
				atomic_set(&mdev->busy, 0);
				अवरोध;

			हाल MAPLE_RESPONSE_DATATRF:
				अगर (mdev->callback)
					mdev->callback(mq);
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->maple_रुको);
				अवरोध;

			हाल MAPLE_RESPONSE_खाताERR:
				maple_response_fileerr(mdev, recvbuf);
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->maple_रुको);
				अवरोध;

			हाल MAPLE_RESPONSE_AGAIN:
			हाल MAPLE_RESPONSE_BADCMD:
			हाल MAPLE_RESPONSE_BADFUNC:
				dev_warn(&mdev->dev, "non-fatal error"
					" 0x%X at (%d, %d)\n", code,
					mdev->port, mdev->unit);
				atomic_set(&mdev->busy, 0);
				अवरोध;

			हाल MAPLE_RESPONSE_ALLINFO:
				dev_notice(&mdev->dev, "extended"
				" device information request for (%d, %d)"
				" but call is not supported\n", mdev->port,
				mdev->unit);
				atomic_set(&mdev->busy, 0);
				अवरोध;

			हाल MAPLE_RESPONSE_OK:
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->maple_रुको);
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		/* अगर scanning is 1 then we have subdevices to check */
		अगर (scanning == 1) अणु
			maple_send();
			scanning = 2;
		पूर्ण अन्यथा
			scanning = 0;
		/*check अगर we have actually tested all ports yet */
		अगर (!fullscan)
			maple_port_rescan();
		/* mark that we have been through the first scan */
		started = 1;
	पूर्ण
	maple_send();
पूर्ण

अटल irqवापस_t maple_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Load everything पूर्णांकo the bottom half */
	schedule_work(&maple_dma_process);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t maple_vblank_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	schedule_work(&maple_vblank_process);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक maple_set_dma_पूर्णांकerrupt_handler(व्योम)
अणु
	वापस request_irq(HW_EVENT_MAPLE_DMA, maple_dma_पूर्णांकerrupt,
		IRQF_SHARED, "maple bus DMA", &maple_unsupported_device);
पूर्ण

अटल पूर्णांक maple_set_vblank_पूर्णांकerrupt_handler(व्योम)
अणु
	वापस request_irq(HW_EVENT_VSYNC, maple_vblank_पूर्णांकerrupt,
		IRQF_SHARED, "maple bus VBLANK", &maple_unsupported_device);
पूर्ण

अटल पूर्णांक maple_get_dma_buffer(व्योम)
अणु
	maple_sendbuf =
	    (व्योम *) __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
				      MAPLE_DMA_PAGES);
	अगर (!maple_sendbuf)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक maple_match_bus_driver(काष्ठा device *devptr,
				  काष्ठा device_driver *drvptr)
अणु
	काष्ठा maple_driver *maple_drv = to_maple_driver(drvptr);
	काष्ठा maple_device *maple_dev = to_maple_dev(devptr);

	/* Trap empty port हाल */
	अगर (maple_dev->devinfo.function == 0xFFFFFFFF)
		वापस 0;
	अन्यथा अगर (maple_dev->devinfo.function &
		 cpu_to_be32(maple_drv->function))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक maple_bus_uevent(काष्ठा device *dev,
			    काष्ठा kobj_uevent_env *env)
अणु
	वापस 0;
पूर्ण

अटल व्योम maple_bus_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा maple_driver maple_unsupported_device = अणु
	.drv = अणु
		.name = "maple_unsupported_device",
		.bus = &maple_bus_type,
	पूर्ण,
पूर्ण;
/*
 * maple_bus_type - core maple bus काष्ठाure
 */
काष्ठा bus_type maple_bus_type = अणु
	.name = "maple",
	.match = maple_match_bus_driver,
	.uevent = maple_bus_uevent,
पूर्ण;
EXPORT_SYMBOL_GPL(maple_bus_type);

अटल काष्ठा device maple_bus = अणु
	.init_name = "maple",
	.release = maple_bus_release,
पूर्ण;

अटल पूर्णांक __init maple_bus_init(व्योम)
अणु
	पूर्णांक retval, i;
	काष्ठा maple_device *mdev[MAPLE_PORTS];

	__raw_ग_लिखोl(0, MAPLE_ENABLE);

	retval = device_रेजिस्टर(&maple_bus);
	अगर (retval)
		जाओ cleanup;

	retval = bus_रेजिस्टर(&maple_bus_type);
	अगर (retval)
		जाओ cleanup_device;

	retval = driver_रेजिस्टर(&maple_unsupported_device.drv);
	अगर (retval)
		जाओ cleanup_bus;

	/* allocate memory क्रम maple bus dma */
	retval = maple_get_dma_buffer();
	अगर (retval) अणु
		dev_err(&maple_bus, "failed to allocate DMA buffers\n");
		जाओ cleanup_basic;
	पूर्ण

	/* set up DMA पूर्णांकerrupt handler */
	retval = maple_set_dma_पूर्णांकerrupt_handler();
	अगर (retval) अणु
		dev_err(&maple_bus, "bus failed to grab maple "
			"DMA IRQ\n");
		जाओ cleanup_dma;
	पूर्ण

	/* set up VBLANK पूर्णांकerrupt handler */
	retval = maple_set_vblank_पूर्णांकerrupt_handler();
	अगर (retval) अणु
		dev_err(&maple_bus, "bus failed to grab VBLANK IRQ\n");
		जाओ cleanup_irq;
	पूर्ण

	maple_queue_cache = KMEM_CACHE(maple_buffer, SLAB_HWCACHE_ALIGN);

	अगर (!maple_queue_cache)
		जाओ cleanup_bothirqs;

	INIT_LIST_HEAD(&maple_रुकोq);
	INIT_LIST_HEAD(&maple_sentq);

	/* setup maple ports */
	क्रम (i = 0; i < MAPLE_PORTS; i++) अणु
		checked[i] = false;
		empty[i] = false;
		mdev[i] = maple_alloc_dev(i, 0);
		अगर (!mdev[i]) अणु
			जबतक (i-- > 0)
				maple_मुक्त_dev(mdev[i]);
			जाओ cleanup_cache;
		पूर्ण
		baseunits[i] = mdev[i];
		atomic_set(&mdev[i]->busy, 1);
		maple_add_packet(mdev[i], 0, MAPLE_COMMAND_DEVINFO, 0, शून्य);
		subdevice_map[i] = 0;
	पूर्ण

	maple_pnp_समय = jअगरfies + HZ;
	/* prepare initial queue */
	maple_send();
	dev_info(&maple_bus, "bus core now registered\n");

	वापस 0;

cleanup_cache:
	kmem_cache_destroy(maple_queue_cache);

cleanup_bothirqs:
	मुक्त_irq(HW_EVENT_VSYNC, 0);

cleanup_irq:
	मुक्त_irq(HW_EVENT_MAPLE_DMA, 0);

cleanup_dma:
	मुक्त_pages((अचिन्हित दीर्घ) maple_sendbuf, MAPLE_DMA_PAGES);

cleanup_basic:
	driver_unरेजिस्टर(&maple_unsupported_device.drv);

cleanup_bus:
	bus_unरेजिस्टर(&maple_bus_type);

cleanup_device:
	device_unरेजिस्टर(&maple_bus);

cleanup:
	prपूर्णांकk(KERN_ERR "Maple bus registration failed\n");
	वापस retval;
पूर्ण
/* Push init to later to ensure hardware माला_लो detected */
fs_initcall(maple_bus_init);
