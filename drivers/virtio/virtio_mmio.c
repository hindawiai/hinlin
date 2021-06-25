<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio memory mapped device driver
 *
 * Copyright 2011-2014, ARM Ltd.
 *
 * This module allows virtio devices to be used over a भव, memory mapped
 * platक्रमm device.
 *
 * The guest device(s) may be instantiated in one of three equivalent ways:
 *
 * 1. Static platक्रमm device in board's code, eg.:
 *
 *	अटल काष्ठा platक्रमm_device v2m_virtio_device = अणु
 *		.name = "virtio-mmio",
 *		.id = -1,
 *		.num_resources = 2,
 *		.resource = (काष्ठा resource []) अणु
 *			अणु
 *				.start = 0x1001e000,
 *				.end = 0x1001e0ff,
 *				.flags = IORESOURCE_MEM,
 *			पूर्ण, अणु
 *				.start = 42 + 32,
 *				.end = 42 + 32,
 *				.flags = IORESOURCE_IRQ,
 *			पूर्ण,
 *		पूर्ण
 *	पूर्ण;
 *
 * 2. Device Tree node, eg.:
 *
 *		virtio_block@1e000 अणु
 *			compatible = "virtio,mmio";
 *			reg = <0x1e000 0x100>;
 *			पूर्णांकerrupts = <42>;
 *		पूर्ण
 *
 * 3. Kernel module (or command line) parameter. Can be used more than once -
 *    one device will be created क्रम each one. Syntax:
 *
 *		[virtio_mmio.]device=<size>@<baseaddr>:<irq>[:<id>]
 *    where:
 *		<size>     := size (can use standard suffixes like K, M or G)
 *		<baseaddr> := physical base address
 *		<irq>      := पूर्णांकerrupt number (as passed to request_irq())
 *		<id>       := (optional) platक्रमm device id
 *    eg.:
 *		virtio_mmio.device=0x100@0x100b0000:48 \
 *				virtio_mmio.device=1K@0x1001e000:74
 *
 * Based on Virtio PCI driver by Anthony Liguori, copyright IBM Corp. 2007
 */

#घोषणा pr_fmt(fmt) "virtio-mmio: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <uapi/linux/virtio_mmपन.स>
#समावेश <linux/virtio_ring.h>



/* The alignment to use between consumer and producer parts of vring.
 * Currently hardcoded to the page size. */
#घोषणा VIRTIO_MMIO_VRING_ALIGN		PAGE_SIZE



#घोषणा to_virtio_mmio_device(_plat_dev) \
	container_of(_plat_dev, काष्ठा virtio_mmio_device, vdev)

काष्ठा virtio_mmio_device अणु
	काष्ठा virtio_device vdev;
	काष्ठा platक्रमm_device *pdev;

	व्योम __iomem *base;
	अचिन्हित दीर्घ version;

	/* a list of queues so we can dispatch IRQs */
	spinlock_t lock;
	काष्ठा list_head virtqueues;
पूर्ण;

काष्ठा virtio_mmio_vq_info अणु
	/* the actual virtqueue */
	काष्ठा virtqueue *vq;

	/* the list node क्रम the virtqueues list */
	काष्ठा list_head node;
पूर्ण;



/* Configuration पूर्णांकerface */

अटल u64 vm_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	u64 features;

	ग_लिखोl(1, vm_dev->base + VIRTIO_MMIO_DEVICE_FEATURES_SEL);
	features = पढ़ोl(vm_dev->base + VIRTIO_MMIO_DEVICE_FEATURES);
	features <<= 32;

	ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_DEVICE_FEATURES_SEL);
	features |= पढ़ोl(vm_dev->base + VIRTIO_MMIO_DEVICE_FEATURES);

	वापस features;
पूर्ण

अटल पूर्णांक vm_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	/* Give virtio_ring a chance to accept features. */
	vring_transport_features(vdev);

	/* Make sure there are no mixed devices */
	अगर (vm_dev->version == 2 &&
			!__virtio_test_bit(vdev, VIRTIO_F_VERSION_1)) अणु
		dev_err(&vdev->dev, "New virtio-mmio devices (version 2) must provide VIRTIO_F_VERSION_1 feature!\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(1, vm_dev->base + VIRTIO_MMIO_DRIVER_FEATURES_SEL);
	ग_लिखोl((u32)(vdev->features >> 32),
			vm_dev->base + VIRTIO_MMIO_DRIVER_FEATURES);

	ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_DRIVER_FEATURES_SEL);
	ग_लिखोl((u32)vdev->features,
			vm_dev->base + VIRTIO_MMIO_DRIVER_FEATURES);

	वापस 0;
पूर्ण

अटल व्योम vm_get(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	व्योम __iomem *base = vm_dev->base + VIRTIO_MMIO_CONFIG;
	u8 b;
	__le16 w;
	__le32 l;

	अगर (vm_dev->version == 1) अणु
		u8 *ptr = buf;
		पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			ptr[i] = पढ़ोb(base + offset + i);
		वापस;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		b = पढ़ोb(base + offset);
		स_नकल(buf, &b, माप b);
		अवरोध;
	हाल 2:
		w = cpu_to_le16(पढ़ोw(base + offset));
		स_नकल(buf, &w, माप w);
		अवरोध;
	हाल 4:
		l = cpu_to_le32(पढ़ोl(base + offset));
		स_नकल(buf, &l, माप l);
		अवरोध;
	हाल 8:
		l = cpu_to_le32(पढ़ोl(base + offset));
		स_नकल(buf, &l, माप l);
		l = cpu_to_le32(ioपढ़ो32(base + offset + माप l));
		स_नकल(buf + माप l, &l, माप l);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम vm_set(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   स्थिर व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	व्योम __iomem *base = vm_dev->base + VIRTIO_MMIO_CONFIG;
	u8 b;
	__le16 w;
	__le32 l;

	अगर (vm_dev->version == 1) अणु
		स्थिर u8 *ptr = buf;
		पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			ग_लिखोb(ptr[i], base + offset + i);

		वापस;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		स_नकल(&b, buf, माप b);
		ग_लिखोb(b, base + offset);
		अवरोध;
	हाल 2:
		स_नकल(&w, buf, माप w);
		ग_लिखोw(le16_to_cpu(w), base + offset);
		अवरोध;
	हाल 4:
		स_नकल(&l, buf, माप l);
		ग_लिखोl(le32_to_cpu(l), base + offset);
		अवरोध;
	हाल 8:
		स_नकल(&l, buf, माप l);
		ग_लिखोl(le32_to_cpu(l), base + offset);
		स_नकल(&l, buf + माप l, माप l);
		ग_लिखोl(le32_to_cpu(l), base + offset + माप l);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल u32 vm_generation(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	अगर (vm_dev->version == 1)
		वापस 0;
	अन्यथा
		वापस पढ़ोl(vm_dev->base + VIRTIO_MMIO_CONFIG_GENERATION);
पूर्ण

अटल u8 vm_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	वापस पढ़ोl(vm_dev->base + VIRTIO_MMIO_STATUS) & 0xff;
पूर्ण

अटल व्योम vm_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	/* We should never be setting status to 0. */
	BUG_ON(status == 0);

	ग_लिखोl(status, vm_dev->base + VIRTIO_MMIO_STATUS);
पूर्ण

अटल व्योम vm_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	/* 0 status means a reset. */
	ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_STATUS);
पूर्ण



/* Transport पूर्णांकerface */

/* the notअगरy function used when creating a virt queue */
अटल bool vm_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vq->vdev);

	/* We ग_लिखो the queue's selector पूर्णांकo the notअगरication रेजिस्टर to
	 * संकेत the other end */
	ग_लिखोl(vq->index, vm_dev->base + VIRTIO_MMIO_QUEUE_NOTIFY);
	वापस true;
पूर्ण

/* Notअगरy all virtqueues on an पूर्णांकerrupt. */
अटल irqवापस_t vm_पूर्णांकerrupt(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा virtio_mmio_device *vm_dev = opaque;
	काष्ठा virtio_mmio_vq_info *info;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ flags;
	irqवापस_t ret = IRQ_NONE;

	/* Read and acknowledge पूर्णांकerrupts */
	status = पढ़ोl(vm_dev->base + VIRTIO_MMIO_INTERRUPT_STATUS);
	ग_लिखोl(status, vm_dev->base + VIRTIO_MMIO_INTERRUPT_ACK);

	अगर (unlikely(status & VIRTIO_MMIO_INT_CONFIG)) अणु
		virtio_config_changed(&vm_dev->vdev);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (likely(status & VIRTIO_MMIO_INT_VRING)) अणु
		spin_lock_irqsave(&vm_dev->lock, flags);
		list_क्रम_each_entry(info, &vm_dev->virtqueues, node)
			ret |= vring_पूर्णांकerrupt(irq, info->vq);
		spin_unlock_irqrestore(&vm_dev->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण



अटल व्योम vm_del_vq(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vq->vdev);
	काष्ठा virtio_mmio_vq_info *info = vq->priv;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index = vq->index;

	spin_lock_irqsave(&vm_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vm_dev->lock, flags);

	/* Select and deactivate the queue */
	ग_लिखोl(index, vm_dev->base + VIRTIO_MMIO_QUEUE_SEL);
	अगर (vm_dev->version == 1) अणु
		ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
		WARN_ON(पढ़ोl(vm_dev->base + VIRTIO_MMIO_QUEUE_READY));
	पूर्ण

	vring_del_virtqueue(vq);

	kमुक्त(info);
पूर्ण

अटल व्योम vm_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	काष्ठा virtqueue *vq, *n;

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list)
		vm_del_vq(vq);

	मुक्त_irq(platक्रमm_get_irq(vm_dev->pdev, 0), vm_dev);
पूर्ण

अटल काष्ठा virtqueue *vm_setup_vq(काष्ठा virtio_device *vdev, अचिन्हित index,
				  व्योम (*callback)(काष्ठा virtqueue *vq),
				  स्थिर अक्षर *name, bool ctx)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	काष्ठा virtio_mmio_vq_info *info;
	काष्ठा virtqueue *vq;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक num;
	पूर्णांक err;

	अगर (!name)
		वापस शून्य;

	/* Select the queue we're पूर्णांकerested in */
	ग_लिखोl(index, vm_dev->base + VIRTIO_MMIO_QUEUE_SEL);

	/* Queue shouldn't alपढ़ोy be set up. */
	अगर (पढ़ोl(vm_dev->base + (vm_dev->version == 1 ?
			VIRTIO_MMIO_QUEUE_PFN : VIRTIO_MMIO_QUEUE_READY))) अणु
		err = -ENOENT;
		जाओ error_available;
	पूर्ण

	/* Allocate and fill out our active queue description */
	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ error_kदो_स्मृति;
	पूर्ण

	num = पढ़ोl(vm_dev->base + VIRTIO_MMIO_QUEUE_NUM_MAX);
	अगर (num == 0) अणु
		err = -ENOENT;
		जाओ error_new_virtqueue;
	पूर्ण

	/* Create the vring */
	vq = vring_create_virtqueue(index, num, VIRTIO_MMIO_VRING_ALIGN, vdev,
				 true, true, ctx, vm_notअगरy, callback, name);
	अगर (!vq) अणु
		err = -ENOMEM;
		जाओ error_new_virtqueue;
	पूर्ण

	/* Activate the queue */
	ग_लिखोl(virtqueue_get_vring_size(vq), vm_dev->base + VIRTIO_MMIO_QUEUE_NUM);
	अगर (vm_dev->version == 1) अणु
		u64 q_pfn = virtqueue_get_desc_addr(vq) >> PAGE_SHIFT;

		/*
		 * virtio-mmio v1 uses a 32bit QUEUE PFN. If we have something
		 * that करोesn't fit in 32bit, fail the setup rather than
		 * pretending to be successful.
		 */
		अगर (q_pfn >> 32) अणु
			dev_err(&vdev->dev,
				"platform bug: legacy virtio-mmio must not be used with RAM above 0x%llxGB\n",
				0x1ULL << (32 + PAGE_SHIFT - 30));
			err = -E2BIG;
			जाओ error_bad_pfn;
		पूर्ण

		ग_लिखोl(PAGE_SIZE, vm_dev->base + VIRTIO_MMIO_QUEUE_ALIGN);
		ग_लिखोl(q_pfn, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	पूर्ण अन्यथा अणु
		u64 addr;

		addr = virtqueue_get_desc_addr(vq);
		ग_लिखोl((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_DESC_LOW);
		ग_लिखोl((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_DESC_HIGH);

		addr = virtqueue_get_avail_addr(vq);
		ग_लिखोl((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_AVAIL_LOW);
		ग_लिखोl((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_AVAIL_HIGH);

		addr = virtqueue_get_used_addr(vq);
		ग_लिखोl((u32)addr, vm_dev->base + VIRTIO_MMIO_QUEUE_USED_LOW);
		ग_लिखोl((u32)(addr >> 32),
				vm_dev->base + VIRTIO_MMIO_QUEUE_USED_HIGH);

		ग_लिखोl(1, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
	पूर्ण

	vq->priv = info;
	info->vq = vq;

	spin_lock_irqsave(&vm_dev->lock, flags);
	list_add(&info->node, &vm_dev->virtqueues);
	spin_unlock_irqrestore(&vm_dev->lock, flags);

	वापस vq;

error_bad_pfn:
	vring_del_virtqueue(vq);
error_new_virtqueue:
	अगर (vm_dev->version == 1) अणु
		ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
		WARN_ON(पढ़ोl(vm_dev->base + VIRTIO_MMIO_QUEUE_READY));
	पूर्ण
	kमुक्त(info);
error_kदो_स्मृति:
error_available:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक vm_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		       काष्ठा virtqueue *vqs[],
		       vq_callback_t *callbacks[],
		       स्थिर अक्षर * स्थिर names[],
		       स्थिर bool *ctx,
		       काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	पूर्णांक irq = platक्रमm_get_irq(vm_dev->pdev, 0);
	पूर्णांक i, err, queue_idx = 0;

	अगर (irq < 0)
		वापस irq;

	err = request_irq(irq, vm_पूर्णांकerrupt, IRQF_SHARED,
			dev_name(&vdev->dev), vm_dev);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		vqs[i] = vm_setup_vq(vdev, queue_idx++, callbacks[i], names[i],
				     ctx ? ctx[i] : false);
		अगर (IS_ERR(vqs[i])) अणु
			vm_del_vqs(vdev);
			वापस PTR_ERR(vqs[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *vm_bus_name(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	वापस vm_dev->pdev->name;
पूर्ण

अटल bool vm_get_shm_region(काष्ठा virtio_device *vdev,
			      काष्ठा virtio_shm_region *region, u8 id)
अणु
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	u64 len, addr;

	/* Select the region we're पूर्णांकerested in */
	ग_लिखोl(id, vm_dev->base + VIRTIO_MMIO_SHM_SEL);

	/* Read the region size */
	len = (u64) पढ़ोl(vm_dev->base + VIRTIO_MMIO_SHM_LEN_LOW);
	len |= (u64) पढ़ोl(vm_dev->base + VIRTIO_MMIO_SHM_LEN_HIGH) << 32;

	region->len = len;

	/* Check अगर region length is -1. If that's the हाल, the shared memory
	 * region करोes not exist and there is no need to proceed further.
	 */
	अगर (len == ~(u64)0)
		वापस false;

	/* Read the region base address */
	addr = (u64) पढ़ोl(vm_dev->base + VIRTIO_MMIO_SHM_BASE_LOW);
	addr |= (u64) पढ़ोl(vm_dev->base + VIRTIO_MMIO_SHM_BASE_HIGH) << 32;

	region->addr = addr;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_mmio_config_ops = अणु
	.get		= vm_get,
	.set		= vm_set,
	.generation	= vm_generation,
	.get_status	= vm_get_status,
	.set_status	= vm_set_status,
	.reset		= vm_reset,
	.find_vqs	= vm_find_vqs,
	.del_vqs	= vm_del_vqs,
	.get_features	= vm_get_features,
	.finalize_features = vm_finalize_features,
	.bus_name	= vm_bus_name,
	.get_shm_region = vm_get_shm_region,
पूर्ण;


अटल व्योम virtio_mmio_release_dev(काष्ठा device *_d)
अणु
	काष्ठा virtio_device *vdev =
			container_of(_d, काष्ठा virtio_device, dev);
	काष्ठा virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);
	काष्ठा platक्रमm_device *pdev = vm_dev->pdev;

	devm_kमुक्त(&pdev->dev, vm_dev);
पूर्ण

/* Platक्रमm device */

अटल पूर्णांक virtio_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev;
	अचिन्हित दीर्घ magic;
	पूर्णांक rc;

	vm_dev = devm_kzalloc(&pdev->dev, माप(*vm_dev), GFP_KERNEL);
	अगर (!vm_dev)
		वापस -ENOMEM;

	vm_dev->vdev.dev.parent = &pdev->dev;
	vm_dev->vdev.dev.release = virtio_mmio_release_dev;
	vm_dev->vdev.config = &virtio_mmio_config_ops;
	vm_dev->pdev = pdev;
	INIT_LIST_HEAD(&vm_dev->virtqueues);
	spin_lock_init(&vm_dev->lock);

	vm_dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vm_dev->base))
		वापस PTR_ERR(vm_dev->base);

	/* Check magic value */
	magic = पढ़ोl(vm_dev->base + VIRTIO_MMIO_MAGIC_VALUE);
	अगर (magic != ('v' | 'i' << 8 | 'r' << 16 | 't' << 24)) अणु
		dev_warn(&pdev->dev, "Wrong magic value 0x%08lx!\n", magic);
		वापस -ENODEV;
	पूर्ण

	/* Check device version */
	vm_dev->version = पढ़ोl(vm_dev->base + VIRTIO_MMIO_VERSION);
	अगर (vm_dev->version < 1 || vm_dev->version > 2) अणु
		dev_err(&pdev->dev, "Version %ld not supported!\n",
				vm_dev->version);
		वापस -ENXIO;
	पूर्ण

	vm_dev->vdev.id.device = पढ़ोl(vm_dev->base + VIRTIO_MMIO_DEVICE_ID);
	अगर (vm_dev->vdev.id.device == 0) अणु
		/*
		 * virtio-mmio device with an ID 0 is a (dummy) placeholder
		 * with no function. End probing now with no error reported.
		 */
		वापस -ENODEV;
	पूर्ण
	vm_dev->vdev.id.venकरोr = पढ़ोl(vm_dev->base + VIRTIO_MMIO_VENDOR_ID);

	अगर (vm_dev->version == 1) अणु
		ग_लिखोl(PAGE_SIZE, vm_dev->base + VIRTIO_MMIO_GUEST_PAGE_SIZE);

		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
		/*
		 * In the legacy हाल, ensure our coherently-allocated virtio
		 * ring will be at an address expressable as a 32-bit PFN.
		 */
		अगर (!rc)
			dma_set_coherent_mask(&pdev->dev,
					      DMA_BIT_MASK(32 + PAGE_SHIFT));
	पूर्ण अन्यथा अणु
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	पूर्ण
	अगर (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc)
		dev_warn(&pdev->dev, "Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.\n");

	platक्रमm_set_drvdata(pdev, vm_dev);

	rc = रेजिस्टर_virtio_device(&vm_dev->vdev);
	अगर (rc)
		put_device(&vm_dev->vdev.dev);

	वापस rc;
पूर्ण

अटल पूर्णांक virtio_mmio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_mmio_device *vm_dev = platक्रमm_get_drvdata(pdev);
	unरेजिस्टर_virtio_device(&vm_dev->vdev);

	वापस 0;
पूर्ण



/* Devices list parameter */

#अगर defined(CONFIG_VIRTIO_MMIO_CMDLINE_DEVICES)

अटल काष्ठा device vm_cmdline_parent = अणु
	.init_name = "virtio-mmio-cmdline",
पूर्ण;

अटल पूर्णांक vm_cmdline_parent_रेजिस्टरed;
अटल पूर्णांक vm_cmdline_id;

अटल पूर्णांक vm_cmdline_set(स्थिर अक्षर *device,
		स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक err;
	काष्ठा resource resources[2] = अणुपूर्ण;
	अक्षर *str;
	दीर्घ दीर्घ पूर्णांक base, size;
	अचिन्हित पूर्णांक irq;
	पूर्णांक processed, consumed = 0;
	काष्ठा platक्रमm_device *pdev;

	/* Consume "size" part of the command line parameter */
	size = memparse(device, &str);

	/* Get "@<base>:<irq>[:<id>]" chunks */
	processed = माला_पूछो(str, "@%lli:%u%n:%d%n",
			&base, &irq, &consumed,
			&vm_cmdline_id, &consumed);

	/*
	 * माला_पूछो() must process at least 2 chunks; also there
	 * must be no extra अक्षरacters after the last chunk, so
	 * str[consumed] must be '\0'
	 */
	अगर (processed < 2 || str[consumed] || irq == 0)
		वापस -EINVAL;

	resources[0].flags = IORESOURCE_MEM;
	resources[0].start = base;
	resources[0].end = base + size - 1;

	resources[1].flags = IORESOURCE_IRQ;
	resources[1].start = resources[1].end = irq;

	अगर (!vm_cmdline_parent_रेजिस्टरed) अणु
		err = device_रेजिस्टर(&vm_cmdline_parent);
		अगर (err) अणु
			pr_err("Failed to register parent device!\n");
			वापस err;
		पूर्ण
		vm_cmdline_parent_रेजिस्टरed = 1;
	पूर्ण

	pr_info("Registering device virtio-mmio.%d at 0x%llx-0x%llx, IRQ %d.\n",
		       vm_cmdline_id,
		       (अचिन्हित दीर्घ दीर्घ)resources[0].start,
		       (अचिन्हित दीर्घ दीर्घ)resources[0].end,
		       (पूर्णांक)resources[1].start);

	pdev = platक्रमm_device_रेजिस्टर_resndata(&vm_cmdline_parent,
			"virtio-mmio", vm_cmdline_id++,
			resources, ARRAY_SIZE(resources), शून्य, 0);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

अटल पूर्णांक vm_cmdline_get_device(काष्ठा device *dev, व्योम *data)
अणु
	अक्षर *buffer = data;
	अचिन्हित पूर्णांक len = म_माप(buffer);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	snम_लिखो(buffer + len, PAGE_SIZE - len, "0x%llx@0x%llx:%llu:%d\n",
			pdev->resource[0].end - pdev->resource[0].start + 1ULL,
			(अचिन्हित दीर्घ दीर्घ)pdev->resource[0].start,
			(अचिन्हित दीर्घ दीर्घ)pdev->resource[1].start,
			pdev->id);
	वापस 0;
पूर्ण

अटल पूर्णांक vm_cmdline_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	buffer[0] = '\0';
	device_क्रम_each_child(&vm_cmdline_parent, buffer,
			vm_cmdline_get_device);
	वापस म_माप(buffer) + 1;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops vm_cmdline_param_ops = अणु
	.set = vm_cmdline_set,
	.get = vm_cmdline_get,
पूर्ण;

device_param_cb(device, &vm_cmdline_param_ops, शून्य, S_IRUSR);

अटल पूर्णांक vm_unरेजिस्टर_cmdline_device(काष्ठा device *dev,
		व्योम *data)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));

	वापस 0;
पूर्ण

अटल व्योम vm_unरेजिस्टर_cmdline_devices(व्योम)
अणु
	अगर (vm_cmdline_parent_रेजिस्टरed) अणु
		device_क्रम_each_child(&vm_cmdline_parent, शून्य,
				vm_unरेजिस्टर_cmdline_device);
		device_unरेजिस्टर(&vm_cmdline_parent);
		vm_cmdline_parent_रेजिस्टरed = 0;
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम vm_unरेजिस्टर_cmdline_devices(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

/* Platक्रमm driver */

अटल स्थिर काष्ठा of_device_id virtio_mmio_match[] = अणु
	अणु .compatible = "virtio,mmio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, virtio_mmio_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id virtio_mmio_acpi_match[] = अणु
	अणु "LNRO0005", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, virtio_mmio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver virtio_mmio_driver = अणु
	.probe		= virtio_mmio_probe,
	.हटाओ		= virtio_mmio_हटाओ,
	.driver		= अणु
		.name	= "virtio-mmio",
		.of_match_table	= virtio_mmio_match,
		.acpi_match_table = ACPI_PTR(virtio_mmio_acpi_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init virtio_mmio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&virtio_mmio_driver);
पूर्ण

अटल व्योम __निकास virtio_mmio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&virtio_mmio_driver);
	vm_unरेजिस्टर_cmdline_devices();
पूर्ण

module_init(virtio_mmio_init);
module_निकास(virtio_mmio_निकास);

MODULE_AUTHOR("Pawel Moll <pawel.moll@arm.com>");
MODULE_DESCRIPTION("Platform bus driver for memory mapped virtio devices");
MODULE_LICENSE("GPL");
