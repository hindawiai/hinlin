<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nosy - Snoop mode driver क्रम TI PCILynx 1394 controllers
 * Copyright (C) 2002-2007 Kristian Hथचgsberg
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h> /* required क्रम linux/रुको.h */
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय64.h>
#समावेश <linux/समयx.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "nosy.h"
#समावेश "nosy-user.h"

#घोषणा TCODE_PHY_PACKET		0x10
#घोषणा PCI_DEVICE_ID_TI_PCILYNX	0x8000

अटल अक्षर driver_name[] = KBUILD_MODNAME;

/* this is the physical layout of a PCL, its size is 128 bytes */
काष्ठा pcl अणु
	__le32 next;
	__le32 async_error_next;
	u32 user_data;
	__le32 pcl_status;
	__le32 reमुख्यing_transfer_count;
	__le32 next_data_buffer;
	काष्ठा अणु
		__le32 control;
		__le32 poपूर्णांकer;
	पूर्ण buffer[13];
पूर्ण;

काष्ठा packet अणु
	अचिन्हित पूर्णांक length;
	अक्षर data[];
पूर्ण;

काष्ठा packet_buffer अणु
	अक्षर *data;
	माप_प्रकार capacity;
	दीर्घ total_packet_count, lost_packet_count;
	atomic_t size;
	काष्ठा packet *head, *tail;
	रुको_queue_head_t रुको;
पूर्ण;

काष्ठा pcilynx अणु
	काष्ठा pci_dev *pci_device;
	__iomem अक्षर *रेजिस्टरs;

	काष्ठा pcl *rcv_start_pcl, *rcv_pcl;
	__le32 *rcv_buffer;

	dma_addr_t rcv_start_pcl_bus, rcv_pcl_bus, rcv_buffer_bus;

	spinlock_t client_list_lock;
	काष्ठा list_head client_list;

	काष्ठा miscdevice misc;
	काष्ठा list_head link;
	काष्ठा kref kref;
पूर्ण;

अटल अंतरभूत काष्ठा pcilynx *
lynx_get(काष्ठा pcilynx *lynx)
अणु
	kref_get(&lynx->kref);

	वापस lynx;
पूर्ण

अटल व्योम
lynx_release(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा pcilynx, kref));
पूर्ण

अटल अंतरभूत व्योम
lynx_put(काष्ठा pcilynx *lynx)
अणु
	kref_put(&lynx->kref, lynx_release);
पूर्ण

काष्ठा client अणु
	काष्ठा pcilynx *lynx;
	u32 tcode_mask;
	काष्ठा packet_buffer buffer;
	काष्ठा list_head link;
पूर्ण;

अटल DEFINE_MUTEX(card_mutex);
अटल LIST_HEAD(card_list);

अटल पूर्णांक
packet_buffer_init(काष्ठा packet_buffer *buffer, माप_प्रकार capacity)
अणु
	buffer->data = kदो_स्मृति(capacity, GFP_KERNEL);
	अगर (buffer->data == शून्य)
		वापस -ENOMEM;
	buffer->head = (काष्ठा packet *) buffer->data;
	buffer->tail = (काष्ठा packet *) buffer->data;
	buffer->capacity = capacity;
	buffer->lost_packet_count = 0;
	atomic_set(&buffer->size, 0);
	init_रुकोqueue_head(&buffer->रुको);

	वापस 0;
पूर्ण

अटल व्योम
packet_buffer_destroy(काष्ठा packet_buffer *buffer)
अणु
	kमुक्त(buffer->data);
पूर्ण

अटल पूर्णांक
packet_buffer_get(काष्ठा client *client, अक्षर __user *data, माप_प्रकार user_length)
अणु
	काष्ठा packet_buffer *buffer = &client->buffer;
	माप_प्रकार length;
	अक्षर *end;

	अगर (रुको_event_पूर्णांकerruptible(buffer->रुको,
				     atomic_पढ़ो(&buffer->size) > 0) ||
				     list_empty(&client->lynx->link))
		वापस -ERESTARTSYS;

	अगर (atomic_पढ़ो(&buffer->size) == 0)
		वापस -ENODEV;

	/* FIXME: Check length <= user_length. */

	end = buffer->data + buffer->capacity;
	length = buffer->head->length;

	अगर (&buffer->head->data[length] < end) अणु
		अगर (copy_to_user(data, buffer->head->data, length))
			वापस -EFAULT;
		buffer->head = (काष्ठा packet *) &buffer->head->data[length];
	पूर्ण अन्यथा अणु
		माप_प्रकार split = end - buffer->head->data;

		अगर (copy_to_user(data, buffer->head->data, split))
			वापस -EFAULT;
		अगर (copy_to_user(data + split, buffer->data, length - split))
			वापस -EFAULT;
		buffer->head = (काष्ठा packet *) &buffer->data[length - split];
	पूर्ण

	/*
	 * Decrease buffer->size as the last thing, since this is what
	 * keeps the पूर्णांकerrupt from overwriting the packet we are
	 * retrieving from the buffer.
	 */
	atomic_sub(माप(काष्ठा packet) + length, &buffer->size);

	वापस length;
पूर्ण

अटल व्योम
packet_buffer_put(काष्ठा packet_buffer *buffer, व्योम *data, माप_प्रकार length)
अणु
	अक्षर *end;

	buffer->total_packet_count++;

	अगर (buffer->capacity <
	    atomic_पढ़ो(&buffer->size) + माप(काष्ठा packet) + length) अणु
		buffer->lost_packet_count++;
		वापस;
	पूर्ण

	end = buffer->data + buffer->capacity;
	buffer->tail->length = length;

	अगर (&buffer->tail->data[length] < end) अणु
		स_नकल(buffer->tail->data, data, length);
		buffer->tail = (काष्ठा packet *) &buffer->tail->data[length];
	पूर्ण अन्यथा अणु
		माप_प्रकार split = end - buffer->tail->data;

		स_नकल(buffer->tail->data, data, split);
		स_नकल(buffer->data, data + split, length - split);
		buffer->tail = (काष्ठा packet *) &buffer->data[length - split];
	पूर्ण

	/* Finally, adjust buffer size and wake up userspace पढ़ोer. */

	atomic_add(माप(काष्ठा packet) + length, &buffer->size);
	wake_up_पूर्णांकerruptible(&buffer->रुको);
पूर्ण

अटल अंतरभूत व्योम
reg_ग_लिखो(काष्ठा pcilynx *lynx, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, lynx->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत u32
reg_पढ़ो(काष्ठा pcilynx *lynx, पूर्णांक offset)
अणु
	वापस पढ़ोl(lynx->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत व्योम
reg_set_bits(काष्ठा pcilynx *lynx, पूर्णांक offset, u32 mask)
अणु
	reg_ग_लिखो(lynx, offset, (reg_पढ़ो(lynx, offset) | mask));
पूर्ण

/*
 * Maybe the pcl programs could be set up to just append data instead
 * of using a whole packet.
 */
अटल अंतरभूत व्योम
run_pcl(काष्ठा pcilynx *lynx, dma_addr_t pcl_bus,
			   पूर्णांक dmachan)
अणु
	reg_ग_लिखो(lynx, DMA0_CURRENT_PCL + dmachan * 0x20, pcl_bus);
	reg_ग_लिखो(lynx, DMA0_CHAN_CTRL + dmachan * 0x20,
		  DMA_CHAN_CTRL_ENABLE | DMA_CHAN_CTRL_LINK);
पूर्ण

अटल पूर्णांक
set_phy_reg(काष्ठा pcilynx *lynx, पूर्णांक addr, पूर्णांक val)
अणु
	अगर (addr > 15) अणु
		dev_err(&lynx->pci_device->dev,
			"PHY register address %d out of range\n", addr);
		वापस -1;
	पूर्ण
	अगर (val > 0xff) अणु
		dev_err(&lynx->pci_device->dev,
			"PHY register value %d out of range\n", val);
		वापस -1;
	पूर्ण
	reg_ग_लिखो(lynx, LINK_PHY, LINK_PHY_WRITE |
		  LINK_PHY_ADDR(addr) | LINK_PHY_WDATA(val));

	वापस 0;
पूर्ण

अटल पूर्णांक
nosy_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	काष्ठा client *client;
	काष्ठा pcilynx *पंचांगp, *lynx = शून्य;

	mutex_lock(&card_mutex);
	list_क्रम_each_entry(पंचांगp, &card_list, link)
		अगर (पंचांगp->misc.minor == minor) अणु
			lynx = lynx_get(पंचांगp);
			अवरोध;
		पूर्ण
	mutex_unlock(&card_mutex);
	अगर (lynx == शून्य)
		वापस -ENODEV;

	client = kदो_स्मृति(माप *client, GFP_KERNEL);
	अगर (client == शून्य)
		जाओ fail;

	client->tcode_mask = ~0;
	client->lynx = lynx;
	INIT_LIST_HEAD(&client->link);

	अगर (packet_buffer_init(&client->buffer, 128 * 1024) < 0)
		जाओ fail;

	file->निजी_data = client;

	वापस stream_खोलो(inode, file);
fail:
	kमुक्त(client);
	lynx_put(lynx);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक
nosy_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा client *client = file->निजी_data;
	काष्ठा pcilynx *lynx = client->lynx;

	spin_lock_irq(&lynx->client_list_lock);
	list_del_init(&client->link);
	spin_unlock_irq(&lynx->client_list_lock);

	packet_buffer_destroy(&client->buffer);
	kमुक्त(client);
	lynx_put(lynx);

	वापस 0;
पूर्ण

अटल __poll_t
nosy_poll(काष्ठा file *file, poll_table *pt)
अणु
	काष्ठा client *client = file->निजी_data;
	__poll_t ret = 0;

	poll_रुको(file, &client->buffer.रुको, pt);

	अगर (atomic_पढ़ो(&client->buffer.size) > 0)
		ret = EPOLLIN | EPOLLRDNORM;

	अगर (list_empty(&client->lynx->link))
		ret |= EPOLLHUP;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
nosy_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा client *client = file->निजी_data;

	वापस packet_buffer_get(client, buffer, count);
पूर्ण

अटल दीर्घ
nosy_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा client *client = file->निजी_data;
	spinlock_t *client_list_lock = &client->lynx->client_list_lock;
	काष्ठा nosy_stats stats;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल NOSY_IOC_GET_STATS:
		spin_lock_irq(client_list_lock);
		stats.total_packet_count = client->buffer.total_packet_count;
		stats.lost_packet_count  = client->buffer.lost_packet_count;
		spin_unlock_irq(client_list_lock);

		अगर (copy_to_user((व्योम __user *) arg, &stats, माप stats))
			वापस -EFAULT;
		अन्यथा
			वापस 0;

	हाल NOSY_IOC_START:
		ret = -EBUSY;
		spin_lock_irq(client_list_lock);
		अगर (list_empty(&client->link)) अणु
			list_add_tail(&client->link, &client->lynx->client_list);
			ret = 0;
		पूर्ण
		spin_unlock_irq(client_list_lock);

		वापस ret;

	हाल NOSY_IOC_STOP:
		spin_lock_irq(client_list_lock);
		list_del_init(&client->link);
		spin_unlock_irq(client_list_lock);

		वापस 0;

	हाल NOSY_IOC_FILTER:
		spin_lock_irq(client_list_lock);
		client->tcode_mask = arg;
		spin_unlock_irq(client_list_lock);

		वापस 0;

	शेष:
		वापस -EINVAL;
		/* Flush buffer, configure filter. */
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations nosy_ops = अणु
	.owner =		THIS_MODULE,
	.पढ़ो =			nosy_पढ़ो,
	.unlocked_ioctl =	nosy_ioctl,
	.poll =			nosy_poll,
	.खोलो =			nosy_खोलो,
	.release =		nosy_release,
पूर्ण;

#घोषणा PHY_PACKET_SIZE 12 /* 1 payload, 1 inverse, 1 ack = 3 quadlets */

अटल व्योम
packet_irq_handler(काष्ठा pcilynx *lynx)
अणु
	काष्ठा client *client;
	u32 tcode_mask, tcode, बारtamp;
	माप_प्रकार length;
	काष्ठा बारpec64 ts64;

	/* FIXME: Also report rcv_speed. */

	length = __le32_to_cpu(lynx->rcv_pcl->pcl_status) & 0x00001fff;
	tcode  = __le32_to_cpu(lynx->rcv_buffer[1]) >> 4 & 0xf;

	kसमय_get_real_ts64(&ts64);
	बारtamp = ts64.tv_nsec / NSEC_PER_USEC;
	lynx->rcv_buffer[0] = (__क्रमce __le32)बारtamp;

	अगर (length == PHY_PACKET_SIZE)
		tcode_mask = 1 << TCODE_PHY_PACKET;
	अन्यथा
		tcode_mask = 1 << tcode;

	spin_lock(&lynx->client_list_lock);

	list_क्रम_each_entry(client, &lynx->client_list, link)
		अगर (client->tcode_mask & tcode_mask)
			packet_buffer_put(&client->buffer,
					  lynx->rcv_buffer, length + 4);

	spin_unlock(&lynx->client_list_lock);
पूर्ण

अटल व्योम
bus_reset_irq_handler(काष्ठा pcilynx *lynx)
अणु
	काष्ठा client *client;
	काष्ठा बारpec64 ts64;
	u32    बारtamp;

	kसमय_get_real_ts64(&ts64);
	बारtamp = ts64.tv_nsec / NSEC_PER_USEC;

	spin_lock(&lynx->client_list_lock);

	list_क्रम_each_entry(client, &lynx->client_list, link)
		packet_buffer_put(&client->buffer, &बारtamp, 4);

	spin_unlock(&lynx->client_list_lock);
पूर्ण

अटल irqवापस_t
irq_handler(पूर्णांक irq, व्योम *device)
अणु
	काष्ठा pcilynx *lynx = device;
	u32 pci_पूर्णांक_status;

	pci_पूर्णांक_status = reg_पढ़ो(lynx, PCI_INT_STATUS);

	अगर (pci_पूर्णांक_status == ~0)
		/* Card was ejected. */
		वापस IRQ_NONE;

	अगर ((pci_पूर्णांक_status & PCI_INT_INT_PEND) == 0)
		/* Not our पूर्णांकerrupt, bail out quickly. */
		वापस IRQ_NONE;

	अगर ((pci_पूर्णांक_status & PCI_INT_P1394_INT) != 0) अणु
		u32 link_पूर्णांक_status;

		link_पूर्णांक_status = reg_पढ़ो(lynx, LINK_INT_STATUS);
		reg_ग_लिखो(lynx, LINK_INT_STATUS, link_पूर्णांक_status);

		अगर ((link_पूर्णांक_status & LINK_INT_PHY_BUSRESET) > 0)
			bus_reset_irq_handler(lynx);
	पूर्ण

	/* Clear the PCI_INT_STATUS रेजिस्टर only after clearing the
	 * LINK_INT_STATUS रेजिस्टर; otherwise the PCI_INT_P1394 will
	 * be set again immediately. */

	reg_ग_लिखो(lynx, PCI_INT_STATUS, pci_पूर्णांक_status);

	अगर ((pci_पूर्णांक_status & PCI_INT_DMA0_HLT) > 0) अणु
		packet_irq_handler(lynx);
		run_pcl(lynx, lynx->rcv_start_pcl_bus, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
हटाओ_card(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcilynx *lynx = pci_get_drvdata(dev);
	काष्ठा client *client;

	mutex_lock(&card_mutex);
	list_del_init(&lynx->link);
	misc_deरेजिस्टर(&lynx->misc);
	mutex_unlock(&card_mutex);

	reg_ग_लिखो(lynx, PCI_INT_ENABLE, 0);
	मुक्त_irq(lynx->pci_device->irq, lynx);

	spin_lock_irq(&lynx->client_list_lock);
	list_क्रम_each_entry(client, &lynx->client_list, link)
		wake_up_पूर्णांकerruptible(&client->buffer.रुको);
	spin_unlock_irq(&lynx->client_list_lock);

	pci_मुक्त_consistent(lynx->pci_device, माप(काष्ठा pcl),
			    lynx->rcv_start_pcl, lynx->rcv_start_pcl_bus);
	pci_मुक्त_consistent(lynx->pci_device, माप(काष्ठा pcl),
			    lynx->rcv_pcl, lynx->rcv_pcl_bus);
	pci_मुक्त_consistent(lynx->pci_device, PAGE_SIZE,
			    lynx->rcv_buffer, lynx->rcv_buffer_bus);

	iounmap(lynx->रेजिस्टरs);
	pci_disable_device(dev);
	lynx_put(lynx);
पूर्ण

#घोषणा RCV_BUFFER_SIZE (16 * 1024)

अटल पूर्णांक
add_card(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *unused)
अणु
	काष्ठा pcilynx *lynx;
	u32 p, end;
	पूर्णांक ret, i;

	अगर (pci_set_dma_mask(dev, DMA_BIT_MASK(32))) अणु
		dev_err(&dev->dev,
		    "DMA address limits not supported for PCILynx hardware\n");
		वापस -ENXIO;
	पूर्ण
	अगर (pci_enable_device(dev)) अणु
		dev_err(&dev->dev, "Failed to enable PCILynx hardware\n");
		वापस -ENXIO;
	पूर्ण
	pci_set_master(dev);

	lynx = kzalloc(माप *lynx, GFP_KERNEL);
	अगर (lynx == शून्य) अणु
		dev_err(&dev->dev, "Failed to allocate control structure\n");
		ret = -ENOMEM;
		जाओ fail_disable;
	पूर्ण
	lynx->pci_device = dev;
	pci_set_drvdata(dev, lynx);

	spin_lock_init(&lynx->client_list_lock);
	INIT_LIST_HEAD(&lynx->client_list);
	kref_init(&lynx->kref);

	lynx->रेजिस्टरs = ioremap(pci_resource_start(dev, 0),
					  PCILYNX_MAX_REGISTER);
	अगर (lynx->रेजिस्टरs == शून्य) अणु
		dev_err(&dev->dev, "Failed to map registers\n");
		ret = -ENOMEM;
		जाओ fail_deallocate_lynx;
	पूर्ण

	lynx->rcv_start_pcl = pci_alloc_consistent(lynx->pci_device,
				माप(काष्ठा pcl), &lynx->rcv_start_pcl_bus);
	lynx->rcv_pcl = pci_alloc_consistent(lynx->pci_device,
				माप(काष्ठा pcl), &lynx->rcv_pcl_bus);
	lynx->rcv_buffer = pci_alloc_consistent(lynx->pci_device,
				RCV_BUFFER_SIZE, &lynx->rcv_buffer_bus);
	अगर (lynx->rcv_start_pcl == शून्य ||
	    lynx->rcv_pcl == शून्य ||
	    lynx->rcv_buffer == शून्य) अणु
		dev_err(&dev->dev, "Failed to allocate receive buffer\n");
		ret = -ENOMEM;
		जाओ fail_deallocate_buffers;
	पूर्ण
	lynx->rcv_start_pcl->next	= cpu_to_le32(lynx->rcv_pcl_bus);
	lynx->rcv_pcl->next		= cpu_to_le32(PCL_NEXT_INVALID);
	lynx->rcv_pcl->async_error_next	= cpu_to_le32(PCL_NEXT_INVALID);

	lynx->rcv_pcl->buffer[0].control =
			cpu_to_le32(PCL_CMD_RCV | PCL_BIGENDIAN | 2044);
	lynx->rcv_pcl->buffer[0].poपूर्णांकer =
			cpu_to_le32(lynx->rcv_buffer_bus + 4);
	p = lynx->rcv_buffer_bus + 2048;
	end = lynx->rcv_buffer_bus + RCV_BUFFER_SIZE;
	क्रम (i = 1; p < end; i++, p += 2048) अणु
		lynx->rcv_pcl->buffer[i].control =
			cpu_to_le32(PCL_CMD_RCV | PCL_BIGENDIAN | 2048);
		lynx->rcv_pcl->buffer[i].poपूर्णांकer = cpu_to_le32(p);
	पूर्ण
	lynx->rcv_pcl->buffer[i - 1].control |= cpu_to_le32(PCL_LAST_BUFF);

	reg_set_bits(lynx, MISC_CONTROL, MISC_CONTROL_SWRESET);
	/* Fix buggy cards with स्वतःboot pin not tied low: */
	reg_ग_लिखो(lynx, DMA0_CHAN_CTRL, 0);
	reg_ग_लिखो(lynx, DMA_GLOBAL_REGISTER, 0x00 << 24);

#अगर 0
	/* now, looking क्रम PHY रेजिस्टर set */
	अगर ((get_phy_reg(lynx, 2) & 0xe0) == 0xe0) अणु
		lynx->phyic.reg_1394a = 1;
		PRINT(KERN_INFO, lynx->id,
		      "found 1394a conform PHY (using extended register set)");
		lynx->phyic.venकरोr = get_phy_venकरोrid(lynx);
		lynx->phyic.product = get_phy_productid(lynx);
	पूर्ण अन्यथा अणु
		lynx->phyic.reg_1394a = 0;
		PRINT(KERN_INFO, lynx->id, "found old 1394 PHY");
	पूर्ण
#पूर्ण_अगर

	/* Setup the general receive FIFO max size. */
	reg_ग_लिखो(lynx, FIFO_SIZES, 255);

	reg_set_bits(lynx, PCI_INT_ENABLE, PCI_INT_DMA_ALL);

	reg_ग_लिखो(lynx, LINK_INT_ENABLE,
		  LINK_INT_PHY_TIME_OUT | LINK_INT_PHY_REG_RCVD |
		  LINK_INT_PHY_BUSRESET | LINK_INT_IT_STUCK |
		  LINK_INT_AT_STUCK | LINK_INT_SNTRJ |
		  LINK_INT_TC_ERR | LINK_INT_GRF_OVER_FLOW |
		  LINK_INT_ITF_UNDER_FLOW | LINK_INT_ATF_UNDER_FLOW);

	/* Disable the L flag in self ID packets. */
	set_phy_reg(lynx, 4, 0);

	/* Put this baby पूर्णांकo snoop mode */
	reg_set_bits(lynx, LINK_CONTROL, LINK_CONTROL_SNOOP_ENABLE);

	run_pcl(lynx, lynx->rcv_start_pcl_bus, 0);

	अगर (request_irq(dev->irq, irq_handler, IRQF_SHARED,
			driver_name, lynx)) अणु
		dev_err(&dev->dev,
			"Failed to allocate shared interrupt %d\n", dev->irq);
		ret = -EIO;
		जाओ fail_deallocate_buffers;
	पूर्ण

	lynx->misc.parent = &dev->dev;
	lynx->misc.minor = MISC_DYNAMIC_MINOR;
	lynx->misc.name = "nosy";
	lynx->misc.fops = &nosy_ops;

	mutex_lock(&card_mutex);
	ret = misc_रेजिस्टर(&lynx->misc);
	अगर (ret) अणु
		dev_err(&dev->dev, "Failed to register misc char device\n");
		mutex_unlock(&card_mutex);
		जाओ fail_मुक्त_irq;
	पूर्ण
	list_add_tail(&lynx->link, &card_list);
	mutex_unlock(&card_mutex);

	dev_info(&dev->dev,
		 "Initialized PCILynx IEEE1394 card, irq=%d\n", dev->irq);

	वापस 0;

fail_मुक्त_irq:
	reg_ग_लिखो(lynx, PCI_INT_ENABLE, 0);
	मुक्त_irq(lynx->pci_device->irq, lynx);

fail_deallocate_buffers:
	अगर (lynx->rcv_start_pcl)
		pci_मुक्त_consistent(lynx->pci_device, माप(काष्ठा pcl),
				lynx->rcv_start_pcl, lynx->rcv_start_pcl_bus);
	अगर (lynx->rcv_pcl)
		pci_मुक्त_consistent(lynx->pci_device, माप(काष्ठा pcl),
				lynx->rcv_pcl, lynx->rcv_pcl_bus);
	अगर (lynx->rcv_buffer)
		pci_मुक्त_consistent(lynx->pci_device, PAGE_SIZE,
				lynx->rcv_buffer, lynx->rcv_buffer_bus);
	iounmap(lynx->रेजिस्टरs);

fail_deallocate_lynx:
	kमुक्त(lynx);

fail_disable:
	pci_disable_device(dev);

	वापस ret;
पूर्ण

अटल काष्ठा pci_device_id pci_table[] = अणु
	अणु
		.venकरोr =    PCI_VENDOR_ID_TI,
		.device =    PCI_DEVICE_ID_TI_PCILYNX,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_table);

अटल काष्ठा pci_driver lynx_pci_driver = अणु
	.name =		driver_name,
	.id_table =	pci_table,
	.probe =	add_card,
	.हटाओ =	हटाओ_card,
पूर्ण;

module_pci_driver(lynx_pci_driver);

MODULE_AUTHOR("Kristian Hoegsberg");
MODULE_DESCRIPTION("Snoop mode driver for TI pcilynx 1394 controllers");
MODULE_LICENSE("GPL");
