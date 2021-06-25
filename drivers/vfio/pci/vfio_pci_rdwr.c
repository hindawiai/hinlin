<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO PCI I/O Port & MMIO access
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/vfपन.स>
#समावेश <linux/vgaarb.h>

#समावेश "vfio_pci_private.h"

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा vfio_ioपढ़ो64	ioपढ़ो64
#घोषणा vfio_ioग_लिखो64	ioग_लिखो64
#घोषणा vfio_ioपढ़ो32	ioपढ़ो32
#घोषणा vfio_ioग_लिखो32	ioग_लिखो32
#घोषणा vfio_ioपढ़ो16	ioपढ़ो16
#घोषणा vfio_ioग_लिखो16	ioग_लिखो16
#अन्यथा
#घोषणा vfio_ioपढ़ो64	ioपढ़ो64be
#घोषणा vfio_ioग_लिखो64	ioग_लिखो64be
#घोषणा vfio_ioपढ़ो32	ioपढ़ो32be
#घोषणा vfio_ioग_लिखो32	ioग_लिखो32be
#घोषणा vfio_ioपढ़ो16	ioपढ़ो16be
#घोषणा vfio_ioग_लिखो16	ioग_लिखो16be
#पूर्ण_अगर
#घोषणा vfio_ioपढ़ो8	ioपढ़ो8
#घोषणा vfio_ioग_लिखो8	ioग_लिखो8

#घोषणा VFIO_IOWRITE(size) \
अटल पूर्णांक vfio_pci_ioग_लिखो##size(काष्ठा vfio_pci_device *vdev,		\
			bool test_mem, u##size val, व्योम __iomem *io)	\
अणु									\
	अगर (test_mem) अणु							\
		करोwn_पढ़ो(&vdev->memory_lock);				\
		अगर (!__vfio_pci_memory_enabled(vdev)) अणु			\
			up_पढ़ो(&vdev->memory_lock);			\
			वापस -EIO;					\
		पूर्ण							\
	पूर्ण								\
									\
	vfio_ioग_लिखो##size(val, io);					\
									\
	अगर (test_mem)							\
		up_पढ़ो(&vdev->memory_lock);				\
									\
	वापस 0;							\
पूर्ण

VFIO_IOWRITE(8)
VFIO_IOWRITE(16)
VFIO_IOWRITE(32)
#अगर_घोषित ioग_लिखो64
VFIO_IOWRITE(64)
#पूर्ण_अगर

#घोषणा VFIO_IOREAD(size) \
अटल पूर्णांक vfio_pci_ioपढ़ो##size(काष्ठा vfio_pci_device *vdev,		\
			bool test_mem, u##size *val, व्योम __iomem *io)	\
अणु									\
	अगर (test_mem) अणु							\
		करोwn_पढ़ो(&vdev->memory_lock);				\
		अगर (!__vfio_pci_memory_enabled(vdev)) अणु			\
			up_पढ़ो(&vdev->memory_lock);			\
			वापस -EIO;					\
		पूर्ण							\
	पूर्ण								\
									\
	*val = vfio_ioपढ़ो##size(io);					\
									\
	अगर (test_mem)							\
		up_पढ़ो(&vdev->memory_lock);				\
									\
	वापस 0;							\
पूर्ण

VFIO_IOREAD(8)
VFIO_IOREAD(16)
VFIO_IOREAD(32)

/*
 * Read or ग_लिखो from an __iomem region (MMIO or I/O port) with an excluded
 * range which is inaccessible.  The excluded range drops ग_लिखोs and fills
 * पढ़ोs with -1.  This is पूर्णांकended क्रम handling MSI-X vector tables and
 * leftover space क्रम ROM BARs.
 */
अटल sमाप_प्रकार करो_io_rw(काष्ठा vfio_pci_device *vdev, bool test_mem,
			व्योम __iomem *io, अक्षर __user *buf,
			loff_t off, माप_प्रकार count, माप_प्रकार x_start,
			माप_प्रकार x_end, bool isग_लिखो)
अणु
	sमाप_प्रकार करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार fillable, filled;

		अगर (off < x_start)
			fillable = min(count, (माप_प्रकार)(x_start - off));
		अन्यथा अगर (off >= x_end)
			fillable = count;
		अन्यथा
			fillable = 0;

		अगर (fillable >= 4 && !(off % 4)) अणु
			u32 val;

			अगर (isग_लिखो) अणु
				अगर (copy_from_user(&val, buf, 4))
					वापस -EFAULT;

				ret = vfio_pci_ioग_लिखो32(vdev, test_mem,
							 val, io + off);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				ret = vfio_pci_ioपढ़ो32(vdev, test_mem,
							&val, io + off);
				अगर (ret)
					वापस ret;

				अगर (copy_to_user(buf, &val, 4))
					वापस -EFAULT;
			पूर्ण

			filled = 4;
		पूर्ण अन्यथा अगर (fillable >= 2 && !(off % 2)) अणु
			u16 val;

			अगर (isग_लिखो) अणु
				अगर (copy_from_user(&val, buf, 2))
					वापस -EFAULT;

				ret = vfio_pci_ioग_लिखो16(vdev, test_mem,
							 val, io + off);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				ret = vfio_pci_ioपढ़ो16(vdev, test_mem,
							&val, io + off);
				अगर (ret)
					वापस ret;

				अगर (copy_to_user(buf, &val, 2))
					वापस -EFAULT;
			पूर्ण

			filled = 2;
		पूर्ण अन्यथा अगर (fillable) अणु
			u8 val;

			अगर (isग_लिखो) अणु
				अगर (copy_from_user(&val, buf, 1))
					वापस -EFAULT;

				ret = vfio_pci_ioग_लिखो8(vdev, test_mem,
							val, io + off);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				ret = vfio_pci_ioपढ़ो8(vdev, test_mem,
						       &val, io + off);
				अगर (ret)
					वापस ret;

				अगर (copy_to_user(buf, &val, 1))
					वापस -EFAULT;
			पूर्ण

			filled = 1;
		पूर्ण अन्यथा अणु
			/* Fill पढ़ोs with -1, drop ग_लिखोs */
			filled = min(count, (माप_प्रकार)(x_end - off));
			अगर (!isग_लिखो) अणु
				u8 val = 0xFF;
				माप_प्रकार i;

				क्रम (i = 0; i < filled; i++)
					अगर (copy_to_user(buf + i, &val, 1))
						वापस -EFAULT;
			पूर्ण
		पूर्ण

		count -= filled;
		करोne += filled;
		off += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
पूर्ण

अटल पूर्णांक vfio_pci_setup_barmap(काष्ठा vfio_pci_device *vdev, पूर्णांक bar)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक ret;
	व्योम __iomem *io;

	अगर (vdev->barmap[bar])
		वापस 0;

	ret = pci_request_selected_regions(pdev, 1 << bar, "vfio");
	अगर (ret)
		वापस ret;

	io = pci_iomap(pdev, bar, 0);
	अगर (!io) अणु
		pci_release_selected_regions(pdev, 1 << bar);
		वापस -ENOMEM;
	पूर्ण

	vdev->barmap[bar] = io;

	वापस 0;
पूर्ण

sमाप_प्रकार vfio_pci_bar_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	पूर्णांक bar = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	माप_प्रकार x_start = 0, x_end = 0;
	resource_माप_प्रकार end;
	व्योम __iomem *io;
	काष्ठा resource *res = &vdev->pdev->resource[bar];
	sमाप_प्रकार करोne;

	अगर (pci_resource_start(pdev, bar))
		end = pci_resource_len(pdev, bar);
	अन्यथा अगर (bar == PCI_ROM_RESOURCE &&
		 pdev->resource[bar].flags & IORESOURCE_ROM_SHADOW)
		end = 0x20000;
	अन्यथा
		वापस -EINVAL;

	अगर (pos >= end)
		वापस -EINVAL;

	count = min(count, (माप_प्रकार)(end - pos));

	अगर (bar == PCI_ROM_RESOURCE) अणु
		/*
		 * The ROM can fill less space than the BAR, so we start the
		 * excluded range at the end of the actual ROM.  This makes
		 * filling large ROM BARs much faster.
		 */
		io = pci_map_rom(pdev, &x_start);
		अगर (!io) अणु
			करोne = -ENOMEM;
			जाओ out;
		पूर्ण
		x_end = end;
	पूर्ण अन्यथा अणु
		पूर्णांक ret = vfio_pci_setup_barmap(vdev, bar);
		अगर (ret) अणु
			करोne = ret;
			जाओ out;
		पूर्ण

		io = vdev->barmap[bar];
	पूर्ण

	अगर (bar == vdev->msix_bar) अणु
		x_start = vdev->msix_offset;
		x_end = vdev->msix_offset + vdev->msix_size;
	पूर्ण

	करोne = करो_io_rw(vdev, res->flags & IORESOURCE_MEM, io, buf, pos,
			count, x_start, x_end, isग_लिखो);

	अगर (करोne >= 0)
		*ppos += करोne;

	अगर (bar == PCI_ROM_RESOURCE)
		pci_unmap_rom(pdev, io);
out:
	वापस करोne;
पूर्ण

sमाप_प्रकार vfio_pci_vga_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	पूर्णांक ret;
	loff_t off, pos = *ppos & VFIO_PCI_OFFSET_MASK;
	व्योम __iomem *iomem = शून्य;
	अचिन्हित पूर्णांक rsrc;
	bool is_ioport;
	sमाप_प्रकार करोne;

	अगर (!vdev->has_vga)
		वापस -EINVAL;

	अगर (pos > 0xbfffful)
		वापस -EINVAL;

	चयन ((u32)pos) अणु
	हाल 0xa0000 ... 0xbffff:
		count = min(count, (माप_प्रकार)(0xc0000 - pos));
		iomem = ioremap(0xa0000, 0xbffff - 0xa0000 + 1);
		off = pos - 0xa0000;
		rsrc = VGA_RSRC_LEGACY_MEM;
		is_ioport = false;
		अवरोध;
	हाल 0x3b0 ... 0x3bb:
		count = min(count, (माप_प्रकार)(0x3bc - pos));
		iomem = ioport_map(0x3b0, 0x3bb - 0x3b0 + 1);
		off = pos - 0x3b0;
		rsrc = VGA_RSRC_LEGACY_IO;
		is_ioport = true;
		अवरोध;
	हाल 0x3c0 ... 0x3df:
		count = min(count, (माप_प्रकार)(0x3e0 - pos));
		iomem = ioport_map(0x3c0, 0x3df - 0x3c0 + 1);
		off = pos - 0x3c0;
		rsrc = VGA_RSRC_LEGACY_IO;
		is_ioport = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!iomem)
		वापस -ENOMEM;

	ret = vga_get_पूर्णांकerruptible(vdev->pdev, rsrc);
	अगर (ret) अणु
		is_ioport ? ioport_unmap(iomem) : iounmap(iomem);
		वापस ret;
	पूर्ण

	/*
	 * VGA MMIO is a legacy, non-BAR resource that hopefully allows
	 * probing, so we करोn't currently worry about access in relation
	 * to the memory enable bit in the command रेजिस्टर.
	 */
	करोne = करो_io_rw(vdev, false, iomem, buf, off, count, 0, 0, isग_लिखो);

	vga_put(vdev->pdev, rsrc);

	is_ioport ? ioport_unmap(iomem) : iounmap(iomem);

	अगर (करोne >= 0)
		*ppos += करोne;

	वापस करोne;
पूर्ण

अटल व्योम vfio_pci_ioeventfd_करो_ग_लिखो(काष्ठा vfio_pci_ioeventfd *ioeventfd,
					bool test_mem)
अणु
	चयन (ioeventfd->count) अणु
	हाल 1:
		vfio_pci_ioग_लिखो8(ioeventfd->vdev, test_mem,
				  ioeventfd->data, ioeventfd->addr);
		अवरोध;
	हाल 2:
		vfio_pci_ioग_लिखो16(ioeventfd->vdev, test_mem,
				   ioeventfd->data, ioeventfd->addr);
		अवरोध;
	हाल 4:
		vfio_pci_ioग_लिखो32(ioeventfd->vdev, test_mem,
				   ioeventfd->data, ioeventfd->addr);
		अवरोध;
#अगर_घोषित ioग_लिखो64
	हाल 8:
		vfio_pci_ioग_लिखो64(ioeventfd->vdev, test_mem,
				   ioeventfd->data, ioeventfd->addr);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_pci_ioeventfd_handler(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_pci_ioeventfd *ioeventfd = opaque;
	काष्ठा vfio_pci_device *vdev = ioeventfd->vdev;

	अगर (ioeventfd->test_mem) अणु
		अगर (!करोwn_पढ़ो_trylock(&vdev->memory_lock))
			वापस 1; /* Lock contended, use thपढ़ो */
		अगर (!__vfio_pci_memory_enabled(vdev)) अणु
			up_पढ़ो(&vdev->memory_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	vfio_pci_ioeventfd_करो_ग_लिखो(ioeventfd, false);

	अगर (ioeventfd->test_mem)
		up_पढ़ो(&vdev->memory_lock);

	वापस 0;
पूर्ण

अटल व्योम vfio_pci_ioeventfd_thपढ़ो(व्योम *opaque, व्योम *unused)
अणु
	काष्ठा vfio_pci_ioeventfd *ioeventfd = opaque;

	vfio_pci_ioeventfd_करो_ग_लिखो(ioeventfd, ioeventfd->test_mem);
पूर्ण

दीर्घ vfio_pci_ioeventfd(काष्ठा vfio_pci_device *vdev, loff_t offset,
			uपूर्णांक64_t data, पूर्णांक count, पूर्णांक fd)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	loff_t pos = offset & VFIO_PCI_OFFSET_MASK;
	पूर्णांक ret, bar = VFIO_PCI_OFFSET_TO_INDEX(offset);
	काष्ठा vfio_pci_ioeventfd *ioeventfd;

	/* Only support ioeventfds पूर्णांकo BARs */
	अगर (bar > VFIO_PCI_BAR5_REGION_INDEX)
		वापस -EINVAL;

	अगर (pos + count > pci_resource_len(pdev, bar))
		वापस -EINVAL;

	/* Disallow ioeventfds working around MSI-X table ग_लिखोs */
	अगर (bar == vdev->msix_bar &&
	    !(pos + count <= vdev->msix_offset ||
	      pos >= vdev->msix_offset + vdev->msix_size))
		वापस -EINVAL;

#अगर_अघोषित ioग_लिखो64
	अगर (count == 8)
		वापस -EINVAL;
#पूर्ण_अगर

	ret = vfio_pci_setup_barmap(vdev, bar);
	अगर (ret)
		वापस ret;

	mutex_lock(&vdev->ioeventfds_lock);

	list_क्रम_each_entry(ioeventfd, &vdev->ioeventfds_list, next) अणु
		अगर (ioeventfd->pos == pos && ioeventfd->bar == bar &&
		    ioeventfd->data == data && ioeventfd->count == count) अणु
			अगर (fd == -1) अणु
				vfio_virqfd_disable(&ioeventfd->virqfd);
				list_del(&ioeventfd->next);
				vdev->ioeventfds_nr--;
				kमुक्त(ioeventfd);
				ret = 0;
			पूर्ण अन्यथा
				ret = -EEXIST;

			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (fd < 0) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (vdev->ioeventfds_nr >= VFIO_PCI_IOEVENTFD_MAX) अणु
		ret = -ENOSPC;
		जाओ out_unlock;
	पूर्ण

	ioeventfd = kzalloc(माप(*ioeventfd), GFP_KERNEL);
	अगर (!ioeventfd) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	ioeventfd->vdev = vdev;
	ioeventfd->addr = vdev->barmap[bar] + pos;
	ioeventfd->data = data;
	ioeventfd->pos = pos;
	ioeventfd->bar = bar;
	ioeventfd->count = count;
	ioeventfd->test_mem = vdev->pdev->resource[bar].flags & IORESOURCE_MEM;

	ret = vfio_virqfd_enable(ioeventfd, vfio_pci_ioeventfd_handler,
				 vfio_pci_ioeventfd_thपढ़ो, शून्य,
				 &ioeventfd->virqfd, fd);
	अगर (ret) अणु
		kमुक्त(ioeventfd);
		जाओ out_unlock;
	पूर्ण

	list_add(&ioeventfd->next, &vdev->ioeventfds_list);
	vdev->ioeventfds_nr++;

out_unlock:
	mutex_unlock(&vdev->ioeventfds_lock);

	वापस ret;
पूर्ण
