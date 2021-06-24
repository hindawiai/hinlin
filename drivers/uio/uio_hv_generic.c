<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uio_hv_generic - generic UIO driver क्रम VMBus
 *
 * Copyright (c) 2013-2016 Brocade Communications Systems, Inc.
 * Copyright (c) 2016, Microsoft Corporation.
 *
 * Since the driver करोes not declare any device ids, you must allocate
 * id and bind the device to the driver yourself.  For example:
 *
 * Associate Network GUID with UIO device
 * # echo "f8615163-df3e-46c5-913f-f2d2f965ed0e" \
 *    > /sys/bus/vmbus/drivers/uio_hv_generic/new_id
 * Then rebind
 * # echo -n "ed963694-e847-4b2a-85af-bc9cfc11d6f3" \
 *    > /sys/bus/vmbus/drivers/hv_netvsc/unbind
 * # echo -n "ed963694-e847-4b2a-85af-bc9cfc11d6f3" \
 *    > /sys/bus/vmbus/drivers/uio_hv_generic/bind
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>

#समावेश "../hv/hyperv_vmbus.h"

#घोषणा DRIVER_VERSION	"0.02.1"
#घोषणा DRIVER_AUTHOR	"Stephen Hemminger <sthemmin at microsoft.com>"
#घोषणा DRIVER_DESC	"Generic UIO driver for VMBus devices"

#घोषणा HV_RING_SIZE	 512	/* pages */
#घोषणा SEND_BUFFER_SIZE (16 * 1024 * 1024)
#घोषणा RECV_BUFFER_SIZE (31 * 1024 * 1024)

/*
 * List of resources to be mapped to user space
 * can be extended up to MAX_UIO_MAPS(5) items
 */
क्रमागत hv_uio_map अणु
	TXRX_RING_MAP = 0,
	INT_PAGE_MAP,
	MON_PAGE_MAP,
	RECV_BUF_MAP,
	SEND_BUF_MAP
पूर्ण;

काष्ठा hv_uio_निजी_data अणु
	काष्ठा uio_info info;
	काष्ठा hv_device *device;
	atomic_t refcnt;

	व्योम	*recv_buf;
	u32	recv_gpadl;
	अक्षर	recv_name[32];	/* "recv_4294967295" */

	व्योम	*send_buf;
	u32	send_gpadl;
	अक्षर	send_name[32];
पूर्ण;

/*
 * This is the irqcontrol callback to be रेजिस्टरed to uio_info.
 * It can be used to disable/enable पूर्णांकerrupt from user space processes.
 *
 * @param info
 *  poपूर्णांकer to uio_info.
 * @param irq_state
 *  state value. 1 to enable पूर्णांकerrupt, 0 to disable पूर्णांकerrupt.
 */
अटल पूर्णांक
hv_uio_irqcontrol(काष्ठा uio_info *info, s32 irq_state)
अणु
	काष्ठा hv_uio_निजी_data *pdata = info->priv;
	काष्ठा hv_device *dev = pdata->device;

	dev->channel->inbound.ring_buffer->पूर्णांकerrupt_mask = !irq_state;
	virt_mb();

	वापस 0;
पूर्ण

/*
 * Callback from vmbus_event when something is in inbound ring.
 */
अटल व्योम hv_uio_channel_cb(व्योम *context)
अणु
	काष्ठा vmbus_channel *chan = context;
	काष्ठा hv_device *hv_dev = chan->device_obj;
	काष्ठा hv_uio_निजी_data *pdata = hv_get_drvdata(hv_dev);

	chan->inbound.ring_buffer->पूर्णांकerrupt_mask = 1;
	virt_mb();

	uio_event_notअगरy(&pdata->info);
पूर्ण

/*
 * Callback from vmbus_event when channel is rescinded.
 */
अटल व्योम hv_uio_rescind(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_device *hv_dev = channel->primary_channel->device_obj;
	काष्ठा hv_uio_निजी_data *pdata = hv_get_drvdata(hv_dev);

	/*
	 * Turn off the पूर्णांकerrupt file handle
	 * Next पढ़ो क्रम event will वापस -EIO
	 */
	pdata->info.irq = 0;

	/* Wake up पढ़ोer */
	uio_event_notअगरy(&pdata->info);
पूर्ण

/* Sysfs API to allow mmap of the ring buffers
 * The ring buffer is allocated as contiguous memory by vmbus_खोलो
 */
अटल पूर्णांक hv_uio_ring_mmap(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *attr,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vmbus_channel *channel
		= container_of(kobj, काष्ठा vmbus_channel, kobj);
	व्योम *ring_buffer = page_address(channel->ringbuffer_page);

	अगर (channel->state != CHANNEL_OPENED_STATE)
		वापस -ENODEV;

	वापस vm_iomap_memory(vma, virt_to_phys(ring_buffer),
			       channel->ringbuffer_pagecount << PAGE_SHIFT);
पूर्ण

अटल स्थिर काष्ठा bin_attribute ring_buffer_bin_attr = अणु
	.attr = अणु
		.name = "ring",
		.mode = 0600,
	पूर्ण,
	.size = 2 * HV_RING_SIZE * PAGE_SIZE,
	.mmap = hv_uio_ring_mmap,
पूर्ण;

/* Callback from VMBUS subप्रणाली when new channel created. */
अटल व्योम
hv_uio_new_channel(काष्ठा vmbus_channel *new_sc)
अणु
	काष्ठा hv_device *hv_dev = new_sc->primary_channel->device_obj;
	काष्ठा device *device = &hv_dev->device;
	स्थिर माप_प्रकार ring_bytes = HV_RING_SIZE * PAGE_SIZE;
	पूर्णांक ret;

	/* Create host communication ring */
	ret = vmbus_खोलो(new_sc, ring_bytes, ring_bytes, शून्य, 0,
			 hv_uio_channel_cb, new_sc);
	अगर (ret) अणु
		dev_err(device, "vmbus_open subchannel failed: %d\n", ret);
		वापस;
	पूर्ण

	/* Disable पूर्णांकerrupts on sub channel */
	new_sc->inbound.ring_buffer->पूर्णांकerrupt_mask = 1;
	set_channel_पढ़ो_mode(new_sc, HV_CALL_ISR);

	ret = sysfs_create_bin_file(&new_sc->kobj, &ring_buffer_bin_attr);
	अगर (ret) अणु
		dev_err(device, "sysfs create ring bin file failed; %d\n", ret);
		vmbus_बंद(new_sc);
	पूर्ण
पूर्ण

/* मुक्त the reserved buffers क्रम send and receive */
अटल व्योम
hv_uio_cleanup(काष्ठा hv_device *dev, काष्ठा hv_uio_निजी_data *pdata)
अणु
	अगर (pdata->send_gpadl) अणु
		vmbus_tearकरोwn_gpadl(dev->channel, pdata->send_gpadl);
		pdata->send_gpadl = 0;
		vमुक्त(pdata->send_buf);
	पूर्ण

	अगर (pdata->recv_gpadl) अणु
		vmbus_tearकरोwn_gpadl(dev->channel, pdata->recv_gpadl);
		pdata->recv_gpadl = 0;
		vमुक्त(pdata->recv_buf);
	पूर्ण
पूर्ण

/* VMBus primary channel is खोलोed on first use */
अटल पूर्णांक
hv_uio_खोलो(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा hv_uio_निजी_data *pdata
		= container_of(info, काष्ठा hv_uio_निजी_data, info);
	काष्ठा hv_device *dev = pdata->device;
	पूर्णांक ret;

	अगर (atomic_inc_वापस(&pdata->refcnt) != 1)
		वापस 0;

	vmbus_set_chn_rescind_callback(dev->channel, hv_uio_rescind);
	vmbus_set_sc_create_callback(dev->channel, hv_uio_new_channel);

	ret = vmbus_connect_ring(dev->channel,
				 hv_uio_channel_cb, dev->channel);
	अगर (ret == 0)
		dev->channel->inbound.ring_buffer->पूर्णांकerrupt_mask = 1;
	अन्यथा
		atomic_dec(&pdata->refcnt);

	वापस ret;
पूर्ण

/* VMBus primary channel is बंदd on last बंद */
अटल पूर्णांक
hv_uio_release(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा hv_uio_निजी_data *pdata
		= container_of(info, काष्ठा hv_uio_निजी_data, info);
	काष्ठा hv_device *dev = pdata->device;
	पूर्णांक ret = 0;

	अगर (atomic_dec_and_test(&pdata->refcnt))
		ret = vmbus_disconnect_ring(dev->channel);

	वापस ret;
पूर्ण

अटल पूर्णांक
hv_uio_probe(काष्ठा hv_device *dev,
	     स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा vmbus_channel *channel = dev->channel;
	काष्ठा hv_uio_निजी_data *pdata;
	व्योम *ring_buffer;
	पूर्णांक ret;

	/* Communicating with host has to be via shared memory not hypercall */
	अगर (!channel->offermsg.monitor_allocated) अणु
		dev_err(&dev->device, "vmbus channel requires hypercall\n");
		वापस -ENOTSUPP;
	पूर्ण

	pdata = devm_kzalloc(&dev->device, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	ret = vmbus_alloc_ring(channel, HV_RING_SIZE * PAGE_SIZE,
			       HV_RING_SIZE * PAGE_SIZE);
	अगर (ret)
		वापस ret;

	set_channel_पढ़ो_mode(channel, HV_CALL_ISR);

	/* Fill general uio info */
	pdata->info.name = "uio_hv_generic";
	pdata->info.version = DRIVER_VERSION;
	pdata->info.irqcontrol = hv_uio_irqcontrol;
	pdata->info.खोलो = hv_uio_खोलो;
	pdata->info.release = hv_uio_release;
	pdata->info.irq = UIO_IRQ_CUSTOM;
	atomic_set(&pdata->refcnt, 0);

	/* mem resources */
	pdata->info.mem[TXRX_RING_MAP].name = "txrx_rings";
	ring_buffer = page_address(channel->ringbuffer_page);
	pdata->info.mem[TXRX_RING_MAP].addr
		= (uपूर्णांकptr_t)virt_to_phys(ring_buffer);
	pdata->info.mem[TXRX_RING_MAP].size
		= channel->ringbuffer_pagecount << PAGE_SHIFT;
	pdata->info.mem[TXRX_RING_MAP].memtype = UIO_MEM_IOVA;

	pdata->info.mem[INT_PAGE_MAP].name = "int_page";
	pdata->info.mem[INT_PAGE_MAP].addr
		= (uपूर्णांकptr_t)vmbus_connection.पूर्णांक_page;
	pdata->info.mem[INT_PAGE_MAP].size = PAGE_SIZE;
	pdata->info.mem[INT_PAGE_MAP].memtype = UIO_MEM_LOGICAL;

	pdata->info.mem[MON_PAGE_MAP].name = "monitor_page";
	pdata->info.mem[MON_PAGE_MAP].addr
		= (uपूर्णांकptr_t)vmbus_connection.monitor_pages[1];
	pdata->info.mem[MON_PAGE_MAP].size = PAGE_SIZE;
	pdata->info.mem[MON_PAGE_MAP].memtype = UIO_MEM_LOGICAL;

	pdata->recv_buf = vzalloc(RECV_BUFFER_SIZE);
	अगर (pdata->recv_buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail_मुक्त_ring;
	पूर्ण

	ret = vmbus_establish_gpadl(channel, pdata->recv_buf,
				    RECV_BUFFER_SIZE, &pdata->recv_gpadl);
	अगर (ret) अणु
		vमुक्त(pdata->recv_buf);
		जाओ fail_बंद;
	पूर्ण

	/* put Global Physical Address Label in name */
	snम_लिखो(pdata->recv_name, माप(pdata->recv_name),
		 "recv:%u", pdata->recv_gpadl);
	pdata->info.mem[RECV_BUF_MAP].name = pdata->recv_name;
	pdata->info.mem[RECV_BUF_MAP].addr
		= (uपूर्णांकptr_t)pdata->recv_buf;
	pdata->info.mem[RECV_BUF_MAP].size = RECV_BUFFER_SIZE;
	pdata->info.mem[RECV_BUF_MAP].memtype = UIO_MEM_VIRTUAL;

	pdata->send_buf = vzalloc(SEND_BUFFER_SIZE);
	अगर (pdata->send_buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail_बंद;
	पूर्ण

	ret = vmbus_establish_gpadl(channel, pdata->send_buf,
				    SEND_BUFFER_SIZE, &pdata->send_gpadl);
	अगर (ret) अणु
		vमुक्त(pdata->send_buf);
		जाओ fail_बंद;
	पूर्ण

	snम_लिखो(pdata->send_name, माप(pdata->send_name),
		 "send:%u", pdata->send_gpadl);
	pdata->info.mem[SEND_BUF_MAP].name = pdata->send_name;
	pdata->info.mem[SEND_BUF_MAP].addr
		= (uपूर्णांकptr_t)pdata->send_buf;
	pdata->info.mem[SEND_BUF_MAP].size = SEND_BUFFER_SIZE;
	pdata->info.mem[SEND_BUF_MAP].memtype = UIO_MEM_VIRTUAL;

	pdata->info.priv = pdata;
	pdata->device = dev;

	ret = uio_रेजिस्टर_device(&dev->device, &pdata->info);
	अगर (ret) अणु
		dev_err(&dev->device, "hv_uio register failed\n");
		जाओ fail_बंद;
	पूर्ण

	ret = sysfs_create_bin_file(&channel->kobj, &ring_buffer_bin_attr);
	अगर (ret)
		dev_notice(&dev->device,
			   "sysfs create ring bin file failed; %d\n", ret);

	hv_set_drvdata(dev, pdata);

	वापस 0;

fail_बंद:
	hv_uio_cleanup(dev, pdata);
fail_मुक्त_ring:
	vmbus_मुक्त_ring(dev->channel);

	वापस ret;
पूर्ण

अटल पूर्णांक
hv_uio_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा hv_uio_निजी_data *pdata = hv_get_drvdata(dev);

	अगर (!pdata)
		वापस 0;

	sysfs_हटाओ_bin_file(&dev->channel->kobj, &ring_buffer_bin_attr);
	uio_unरेजिस्टर_device(&pdata->info);
	hv_uio_cleanup(dev, pdata);

	vmbus_मुक्त_ring(dev->channel);
	वापस 0;
पूर्ण

अटल काष्ठा hv_driver hv_uio_drv = अणु
	.name = "uio_hv_generic",
	.id_table = शून्य, /* only dynamic id's */
	.probe = hv_uio_probe,
	.हटाओ = hv_uio_हटाओ,
पूर्ण;

अटल पूर्णांक __init
hyperv_module_init(व्योम)
अणु
	वापस vmbus_driver_रेजिस्टर(&hv_uio_drv);
पूर्ण

अटल व्योम __निकास
hyperv_module_निकास(व्योम)
अणु
	vmbus_driver_unरेजिस्टर(&hv_uio_drv);
पूर्ण

module_init(hyperv_module_init);
module_निकास(hyperv_module_निकास);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
