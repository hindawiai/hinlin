<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2016 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __DAX_PRIVATE_H__
#घोषणा __DAX_PRIVATE_H__

#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>

/* निजी routines between core files */
काष्ठा dax_device;
काष्ठा dax_device *inode_dax(काष्ठा inode *inode);
काष्ठा inode *dax_inode(काष्ठा dax_device *dax_dev);
पूर्णांक dax_bus_init(व्योम);
व्योम dax_bus_निकास(व्योम);

/**
 * काष्ठा dax_region - mapping infraकाष्ठाure क्रम dax devices
 * @id: kernel-wide unique region क्रम a memory range
 * @target_node: effective numa node अगर this memory range is onlined
 * @kref: to pin जबतक other agents have a need to करो lookups
 * @dev: parent device backing this region
 * @align: allocation and mapping alignment क्रम child dax devices
 * @ida: instance id allocator
 * @res: resource tree to track instance allocations
 * @seed: allow userspace to find the first unbound seed device
 * @youngest: allow userspace to find the most recently created device
 */
काष्ठा dax_region अणु
	पूर्णांक id;
	पूर्णांक target_node;
	काष्ठा kref kref;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक align;
	काष्ठा ida ida;
	काष्ठा resource res;
	काष्ठा device *seed;
	काष्ठा device *youngest;
पूर्ण;

काष्ठा dax_mapping अणु
	काष्ठा device dev;
	पूर्णांक range_id;
	पूर्णांक id;
पूर्ण;

/**
 * काष्ठा dev_dax - instance data क्रम a subभागision of a dax region, and
 * data जबतक the device is activated in the driver.
 * @region - parent region
 * @dax_dev - core dax functionality
 * @target_node: effective numa node अगर dev_dax memory range is onlined
 * @id: ida allocated id
 * @ida: mapping id allocator
 * @dev - device core
 * @pgmap - pgmap क्रम memmap setup / lअगरeसमय (driver owned)
 * @nr_range: size of @ranges
 * @ranges: resource-span + pgoff tuples क्रम the instance
 */
काष्ठा dev_dax अणु
	काष्ठा dax_region *region;
	काष्ठा dax_device *dax_dev;
	अचिन्हित पूर्णांक align;
	पूर्णांक target_node;
	पूर्णांक id;
	काष्ठा ida ida;
	काष्ठा device dev;
	काष्ठा dev_pagemap *pgmap;
	पूर्णांक nr_range;
	काष्ठा dev_dax_range अणु
		अचिन्हित दीर्घ pgoff;
		काष्ठा range range;
		काष्ठा dax_mapping *mapping;
	पूर्ण *ranges;
पूर्ण;

अटल अंतरभूत काष्ठा dev_dax *to_dev_dax(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा dev_dax, dev);
पूर्ण

अटल अंतरभूत काष्ठा dax_mapping *to_dax_mapping(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा dax_mapping, dev);
पूर्ण

phys_addr_t dax_pgoff_to_phys(काष्ठा dev_dax *dev_dax, pgoff_t pgoff, अचिन्हित दीर्घ size);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत bool dax_align_valid(अचिन्हित दीर्घ align)
अणु
	अगर (align == PUD_SIZE && IS_ENABLED(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD))
		वापस true;
	अगर (align == PMD_SIZE && has_transparent_hugepage())
		वापस true;
	अगर (align == PAGE_SIZE)
		वापस true;
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool dax_align_valid(अचिन्हित दीर्घ align)
अणु
	वापस align == PAGE_SIZE;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर
