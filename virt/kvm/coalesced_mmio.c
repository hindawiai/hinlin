<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM coalesced MMIO
 *
 * Copyright (c) 2008 Bull S.A.S.
 * Copyright 2009 Red Hat, Inc. and/or its affiliates.
 *
 *  Author: Laurent Vivier <Laurent.Vivier@bull.net>
 *
 */

#समावेश <kvm/iodev.h>

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/kvm.h>

#समावेश "coalesced_mmio.h"

अटल अंतरभूत काष्ठा kvm_coalesced_mmio_dev *to_mmio(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा kvm_coalesced_mmio_dev, dev);
पूर्ण

अटल पूर्णांक coalesced_mmio_in_range(काष्ठा kvm_coalesced_mmio_dev *dev,
				   gpa_t addr, पूर्णांक len)
अणु
	/* is it in a batchable area ?
	 * (addr,len) is fully included in
	 * (zone->addr, zone->size)
	 */
	अगर (len < 0)
		वापस 0;
	अगर (addr + len < addr)
		वापस 0;
	अगर (addr < dev->zone.addr)
		वापस 0;
	अगर (addr + len > dev->zone.addr + dev->zone.size)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक coalesced_mmio_has_room(काष्ठा kvm_coalesced_mmio_dev *dev, u32 last)
अणु
	काष्ठा kvm_coalesced_mmio_ring *ring;
	अचिन्हित avail;

	/* Are we able to batch it ? */

	/* last is the first मुक्त entry
	 * check अगर we करोn't meet the first used entry
	 * there is always one unused entry in the buffer
	 */
	ring = dev->kvm->coalesced_mmio_ring;
	avail = (ring->first - last - 1) % KVM_COALESCED_MMIO_MAX;
	अगर (avail == 0) अणु
		/* full */
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक coalesced_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_io_device *this, gpa_t addr,
				पूर्णांक len, स्थिर व्योम *val)
अणु
	काष्ठा kvm_coalesced_mmio_dev *dev = to_mmio(this);
	काष्ठा kvm_coalesced_mmio_ring *ring = dev->kvm->coalesced_mmio_ring;
	__u32 insert;

	अगर (!coalesced_mmio_in_range(dev, addr, len))
		वापस -EOPNOTSUPP;

	spin_lock(&dev->kvm->ring_lock);

	insert = READ_ONCE(ring->last);
	अगर (!coalesced_mmio_has_room(dev, insert) ||
	    insert >= KVM_COALESCED_MMIO_MAX) अणु
		spin_unlock(&dev->kvm->ring_lock);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* copy data in first मुक्त entry of the ring */

	ring->coalesced_mmio[insert].phys_addr = addr;
	ring->coalesced_mmio[insert].len = len;
	स_नकल(ring->coalesced_mmio[insert].data, val, len);
	ring->coalesced_mmio[insert].pio = dev->zone.pio;
	smp_wmb();
	ring->last = (insert + 1) % KVM_COALESCED_MMIO_MAX;
	spin_unlock(&dev->kvm->ring_lock);
	वापस 0;
पूर्ण

अटल व्योम coalesced_mmio_deकाष्ठाor(काष्ठा kvm_io_device *this)
अणु
	काष्ठा kvm_coalesced_mmio_dev *dev = to_mmio(this);

	list_del(&dev->list);

	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops coalesced_mmio_ops = अणु
	.ग_लिखो      = coalesced_mmio_ग_लिखो,
	.deकाष्ठाor = coalesced_mmio_deकाष्ठाor,
पूर्ण;

पूर्णांक kvm_coalesced_mmio_init(काष्ठा kvm *kvm)
अणु
	काष्ठा page *page;

	page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!page)
		वापस -ENOMEM;

	kvm->coalesced_mmio_ring = page_address(page);

	/*
	 * We're using this spinlock to sync access to the coalesced ring.
	 * The list करोesn't need its own lock since device registration and
	 * unregistration should only happen when kvm->slots_lock is held.
	 */
	spin_lock_init(&kvm->ring_lock);
	INIT_LIST_HEAD(&kvm->coalesced_zones);

	वापस 0;
पूर्ण

व्योम kvm_coalesced_mmio_मुक्त(काष्ठा kvm *kvm)
अणु
	अगर (kvm->coalesced_mmio_ring)
		मुक्त_page((अचिन्हित दीर्घ)kvm->coalesced_mmio_ring);
पूर्ण

पूर्णांक kvm_vm_ioctl_रेजिस्टर_coalesced_mmio(काष्ठा kvm *kvm,
					 काष्ठा kvm_coalesced_mmio_zone *zone)
अणु
	पूर्णांक ret;
	काष्ठा kvm_coalesced_mmio_dev *dev;

	अगर (zone->pio != 1 && zone->pio != 0)
		वापस -EINVAL;

	dev = kzalloc(माप(काष्ठा kvm_coalesced_mmio_dev),
		      GFP_KERNEL_ACCOUNT);
	अगर (!dev)
		वापस -ENOMEM;

	kvm_iodevice_init(&dev->dev, &coalesced_mmio_ops);
	dev->kvm = kvm;
	dev->zone = *zone;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm,
				zone->pio ? KVM_PIO_BUS : KVM_MMIO_BUS,
				zone->addr, zone->size, &dev->dev);
	अगर (ret < 0)
		जाओ out_मुक्त_dev;
	list_add_tail(&dev->list, &kvm->coalesced_zones);
	mutex_unlock(&kvm->slots_lock);

	वापस 0;

out_मुक्त_dev:
	mutex_unlock(&kvm->slots_lock);
	kमुक्त(dev);

	वापस ret;
पूर्ण

पूर्णांक kvm_vm_ioctl_unरेजिस्टर_coalesced_mmio(काष्ठा kvm *kvm,
					   काष्ठा kvm_coalesced_mmio_zone *zone)
अणु
	काष्ठा kvm_coalesced_mmio_dev *dev, *पंचांगp;
	पूर्णांक r;

	अगर (zone->pio != 1 && zone->pio != 0)
		वापस -EINVAL;

	mutex_lock(&kvm->slots_lock);

	list_क्रम_each_entry_safe(dev, पंचांगp, &kvm->coalesced_zones, list) अणु
		अगर (zone->pio == dev->zone.pio &&
		    coalesced_mmio_in_range(dev, zone->addr, zone->size)) अणु
			r = kvm_io_bus_unरेजिस्टर_dev(kvm,
				zone->pio ? KVM_PIO_BUS : KVM_MMIO_BUS, &dev->dev);
			kvm_iodevice_deकाष्ठाor(&dev->dev);

			/*
			 * On failure, unरेजिस्टर destroys all devices on the
			 * bus _except_ the target device, i.e. coalesced_zones
			 * has been modअगरied.  No need to restart the walk as
			 * there aren't any zones left.
			 */
			अगर (r)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&kvm->slots_lock);

	/*
	 * Ignore the result of kvm_io_bus_unरेजिस्टर_dev(), from userspace's
	 * perspective, the coalesced MMIO is most definitely unरेजिस्टरed.
	 */
	वापस 0;
पूर्ण
