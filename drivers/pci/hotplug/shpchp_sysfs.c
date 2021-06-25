<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Compaq Hot Plug Controller Driver
 *
 * Copyright (c) 1995,2001 Compaq Computer Corporation
 * Copyright (c) 2001,2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (c) 2001 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <greg@kroah.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "shpchp.h"


/* A few routines that create sysfs entries क्रम the hot plug controller */

अटल sमाप_प्रकार show_ctrl(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev;
	अक्षर *out = buf;
	पूर्णांक index, busnr;
	काष्ठा resource *res;
	काष्ठा pci_bus *bus;

	pdev = to_pci_dev(dev);
	bus = pdev->subordinate;

	out += प्र_लिखो(buf, "Free resources: memory\n");
	pci_bus_क्रम_each_resource(bus, res, index) अणु
		अगर (res && (res->flags & IORESOURCE_MEM) &&
				!(res->flags & IORESOURCE_PREFETCH)) अणु
			out += प्र_लिखो(out, "start = %8.8llx, length = %8.8llx\n",
				       (अचिन्हित दीर्घ दीर्घ)res->start,
				       (अचिन्हित दीर्घ दीर्घ)resource_size(res));
		पूर्ण
	पूर्ण
	out += प्र_लिखो(out, "Free resources: prefetchable memory\n");
	pci_bus_क्रम_each_resource(bus, res, index) अणु
		अगर (res && (res->flags & IORESOURCE_MEM) &&
			       (res->flags & IORESOURCE_PREFETCH)) अणु
			out += प्र_लिखो(out, "start = %8.8llx, length = %8.8llx\n",
				       (अचिन्हित दीर्घ दीर्घ)res->start,
				       (अचिन्हित दीर्घ दीर्घ)resource_size(res));
		पूर्ण
	पूर्ण
	out += प्र_लिखो(out, "Free resources: IO\n");
	pci_bus_क्रम_each_resource(bus, res, index) अणु
		अगर (res && (res->flags & IORESOURCE_IO)) अणु
			out += प्र_लिखो(out, "start = %8.8llx, length = %8.8llx\n",
				       (अचिन्हित दीर्घ दीर्घ)res->start,
				       (अचिन्हित दीर्घ दीर्घ)resource_size(res));
		पूर्ण
	पूर्ण
	out += प्र_लिखो(out, "Free resources: bus numbers\n");
	क्रम (busnr = bus->busn_res.start; busnr <= bus->busn_res.end; busnr++) अणु
		अगर (!pci_find_bus(pci_करोमुख्य_nr(bus), busnr))
			अवरोध;
	पूर्ण
	अगर (busnr < bus->busn_res.end)
		out += प्र_लिखो(out, "start = %8.8x, length = %8.8x\n",
				busnr, (पूर्णांक)(bus->busn_res.end - busnr));

	वापस out - buf;
पूर्ण
अटल DEVICE_ATTR(ctrl, S_IRUGO, show_ctrl, शून्य);

पूर्णांक shpchp_create_ctrl_files(काष्ठा controller *ctrl)
अणु
	वापस device_create_file(&ctrl->pci_dev->dev, &dev_attr_ctrl);
पूर्ण

व्योम shpchp_हटाओ_ctrl_files(काष्ठा controller *ctrl)
अणु
	device_हटाओ_file(&ctrl->pci_dev->dev, &dev_attr_ctrl);
पूर्ण
