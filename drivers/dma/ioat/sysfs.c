<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel I/OAT DMA Linux driver
 * Copyright(c) 2004 - 2015 Intel Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pci.h>
#समावेश "dma.h"
#समावेश "registers.h"
#समावेश "hw.h"

#समावेश "../dmaengine.h"

अटल sमाप_प्रकार cap_show(काष्ठा dma_chan *c, अक्षर *page)
अणु
	काष्ठा dma_device *dma = c->device;

	वापस प्र_लिखो(page, "copy%s%s%s%s%s\n",
		       dma_has_cap(DMA_PQ, dma->cap_mask) ? " pq" : "",
		       dma_has_cap(DMA_PQ_VAL, dma->cap_mask) ? " pq_val" : "",
		       dma_has_cap(DMA_XOR, dma->cap_mask) ? " xor" : "",
		       dma_has_cap(DMA_XOR_VAL, dma->cap_mask) ? " xor_val" : "",
		       dma_has_cap(DMA_INTERRUPT, dma->cap_mask) ? " intr" : "");

पूर्ण
काष्ठा ioat_sysfs_entry ioat_cap_attr = __ATTR_RO(cap);

अटल sमाप_प्रकार version_show(काष्ठा dma_chan *c, अक्षर *page)
अणु
	काष्ठा dma_device *dma = c->device;
	काष्ठा ioatdma_device *ioat_dma = to_ioatdma_device(dma);

	वापस प्र_लिखो(page, "%d.%d\n",
		       ioat_dma->version >> 4, ioat_dma->version & 0xf);
पूर्ण
काष्ठा ioat_sysfs_entry ioat_version_attr = __ATTR_RO(version);

अटल sमाप_प्रकार
ioat_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा ioat_sysfs_entry *entry;
	काष्ठा ioatdma_chan *ioat_chan;

	entry = container_of(attr, काष्ठा ioat_sysfs_entry, attr);
	ioat_chan = container_of(kobj, काष्ठा ioatdma_chan, kobj);

	अगर (!entry->show)
		वापस -EIO;
	वापस entry->show(&ioat_chan->dma_chan, page);
पूर्ण

अटल sमाप_प्रकार
ioat_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा ioat_sysfs_entry *entry;
	काष्ठा ioatdma_chan *ioat_chan;

	entry = container_of(attr, काष्ठा ioat_sysfs_entry, attr);
	ioat_chan = container_of(kobj, काष्ठा ioatdma_chan, kobj);

	अगर (!entry->store)
		वापस -EIO;
	वापस entry->store(&ioat_chan->dma_chan, page, count);
पूर्ण

स्थिर काष्ठा sysfs_ops ioat_sysfs_ops = अणु
	.show	= ioat_attr_show,
	.store  = ioat_attr_store,
पूर्ण;

व्योम ioat_kobject_add(काष्ठा ioatdma_device *ioat_dma, काष्ठा kobj_type *type)
अणु
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	काष्ठा dma_chan *c;

	list_क्रम_each_entry(c, &dma->channels, device_node) अणु
		काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
		काष्ठा kobject *parent = &c->dev->device.kobj;
		पूर्णांक err;

		err = kobject_init_and_add(&ioat_chan->kobj, type,
					   parent, "quickdata");
		अगर (err) अणु
			dev_warn(to_dev(ioat_chan),
				 "sysfs init error (%d), continuing...\n", err);
			kobject_put(&ioat_chan->kobj);
			set_bit(IOAT_KOBJ_INIT_FAIL, &ioat_chan->state);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioat_kobject_del(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	काष्ठा dma_chan *c;

	list_क्रम_each_entry(c, &dma->channels, device_node) अणु
		काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

		अगर (!test_bit(IOAT_KOBJ_INIT_FAIL, &ioat_chan->state)) अणु
			kobject_del(&ioat_chan->kobj);
			kobject_put(&ioat_chan->kobj);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ring_size_show(काष्ठा dma_chan *c, अक्षर *page)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

	वापस प्र_लिखो(page, "%d\n", (1 << ioat_chan->alloc_order) & ~1);
पूर्ण
अटल काष्ठा ioat_sysfs_entry ring_size_attr = __ATTR_RO(ring_size);

अटल sमाप_प्रकार ring_active_show(काष्ठा dma_chan *c, अक्षर *page)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

	/* ...taken outside the lock, no need to be precise */
	वापस प्र_लिखो(page, "%d\n", ioat_ring_active(ioat_chan));
पूर्ण
अटल काष्ठा ioat_sysfs_entry ring_active_attr = __ATTR_RO(ring_active);

अटल sमाप_प्रकार पूर्णांकr_coalesce_show(काष्ठा dma_chan *c, अक्षर *page)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

	वापस प्र_लिखो(page, "%d\n", ioat_chan->पूर्णांकr_coalesce);
पूर्ण

अटल sमाप_प्रकार पूर्णांकr_coalesce_store(काष्ठा dma_chan *c, स्थिर अक्षर *page,
माप_प्रकार count)
अणु
	पूर्णांक पूर्णांकr_coalesce = 0;
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

	अगर (माला_पूछो(page, "%du", &पूर्णांकr_coalesce) != -1) अणु
		अगर ((पूर्णांकr_coalesce < 0) ||
		    (पूर्णांकr_coalesce > IOAT_INTRDELAY_MASK))
			वापस -EINVAL;
		ioat_chan->पूर्णांकr_coalesce = पूर्णांकr_coalesce;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा ioat_sysfs_entry पूर्णांकr_coalesce_attr = __ATTR_RW(पूर्णांकr_coalesce);

अटल काष्ठा attribute *ioat_attrs[] = अणु
	&ring_size_attr.attr,
	&ring_active_attr.attr,
	&ioat_cap_attr.attr,
	&ioat_version_attr.attr,
	&पूर्णांकr_coalesce_attr.attr,
	शून्य,
पूर्ण;

काष्ठा kobj_type ioat_ktype = अणु
	.sysfs_ops = &ioat_sysfs_ops,
	.शेष_attrs = ioat_attrs,
पूर्ण;
