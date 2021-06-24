<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cpcihp_generic.c
 *
 * Generic port I/O CompactPCI driver
 *
 * Copyright 2002 SOMA Networks, Inc.
 * Copyright 2001 Intel San Luis Obispo
 * Copyright 2000,2001 MontaVista Software Inc.
 *
 * This generic CompactPCI hotplug driver should allow using the PCI hotplug
 * mechanism on any CompactPCI board that exposes the #ENUM संकेत as a bit
 * in a प्रणाली रेजिस्टर that can be पढ़ो through standard port I/O.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश "cpci_hotplug.h"

#घोषणा DRIVER_VERSION	"0.1"
#घोषणा DRIVER_AUTHOR	"Scott Murray <scottm@somanetworks.com>"
#घोषणा DRIVER_DESC	"Generic port I/O CompactPCI Hot Plug Driver"

#अगर !defined(MODULE)
#घोषणा MY_NAME	"cpcihp_generic"
#अन्यथा
#घोषणा MY_NAME	THIS_MODULE->name
#पूर्ण_अगर

#घोषणा dbg(क्रमmat, arg...)					\
	करो अणु							\
		अगर (debug)					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n",	\
				MY_NAME, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat "\n", MY_NAME, ## arg)

/* local variables */
अटल bool debug;
अटल अक्षर *bridge;
अटल u8 bridge_busnr;
अटल u8 bridge_slot;
अटल काष्ठा pci_bus *bus;
अटल u8 first_slot;
अटल u8 last_slot;
अटल u16 port;
अटल अचिन्हित पूर्णांक क्रमागत_bit;
अटल u8 क्रमागत_mask;

अटल काष्ठा cpci_hp_controller_ops generic_hpc_ops;
अटल काष्ठा cpci_hp_controller generic_hpc;

अटल पूर्णांक __init validate_parameters(व्योम)
अणु
	अक्षर *str;
	अक्षर *p;
	अचिन्हित दीर्घ पंचांगp;

	अगर (!bridge) अणु
		info("not configured, disabling.");
		वापस -EINVAL;
	पूर्ण
	str = bridge;
	अगर (!*str)
		वापस -EINVAL;

	पंचांगp = simple_म_से_अदीर्घ(str, &p, 16);
	अगर (p == str || पंचांगp > 0xff) अणु
		err("Invalid hotplug bus bridge device bus number");
		वापस -EINVAL;
	पूर्ण
	bridge_busnr = (u8) पंचांगp;
	dbg("bridge_busnr = 0x%02x", bridge_busnr);
	अगर (*p != ':') अणु
		err("Invalid hotplug bus bridge device");
		वापस -EINVAL;
	पूर्ण
	str = p + 1;
	पंचांगp = simple_म_से_अदीर्घ(str, &p, 16);
	अगर (p == str || पंचांगp > 0x1f) अणु
		err("Invalid hotplug bus bridge device slot number");
		वापस -EINVAL;
	पूर्ण
	bridge_slot = (u8) पंचांगp;
	dbg("bridge_slot = 0x%02x", bridge_slot);

	dbg("first_slot = 0x%02x", first_slot);
	dbg("last_slot = 0x%02x", last_slot);
	अगर (!(first_slot && last_slot)) अणु
		err("Need to specify first_slot and last_slot");
		वापस -EINVAL;
	पूर्ण
	अगर (last_slot < first_slot) अणु
		err("first_slot must be less than last_slot");
		वापस -EINVAL;
	पूर्ण

	dbg("port = 0x%04x", port);
	dbg("enum_bit = 0x%02x", क्रमागत_bit);
	अगर (क्रमागत_bit > 7) अणु
		err("Invalid #ENUM bit");
		वापस -EINVAL;
	पूर्ण
	क्रमागत_mask = 1 << क्रमागत_bit;
	वापस 0;
पूर्ण

अटल पूर्णांक query_क्रमागत(व्योम)
अणु
	u8 value;

	value = inb_p(port);
	वापस ((value & क्रमागत_mask) == क्रमागत_mask);
पूर्ण

अटल पूर्णांक __init cpcihp_generic_init(व्योम)
अणु
	पूर्णांक status;
	काष्ठा resource *r;
	काष्ठा pci_dev *dev;

	info(DRIVER_DESC " version: " DRIVER_VERSION);
	status = validate_parameters();
	अगर (status)
		वापस status;

	r = request_region(port, 1, "#ENUM hotswap signal register");
	अगर (!r)
		वापस -EBUSY;

	dev = pci_get_करोमुख्य_bus_and_slot(0, bridge_busnr,
					  PCI_DEVFN(bridge_slot, 0));
	अगर (!dev || dev->hdr_type != PCI_HEADER_TYPE_BRIDGE) अणु
		err("Invalid bridge device %s", bridge);
		pci_dev_put(dev);
		वापस -EINVAL;
	पूर्ण
	bus = dev->subordinate;
	pci_dev_put(dev);

	स_रखो(&generic_hpc, 0, माप(काष्ठा cpci_hp_controller));
	generic_hpc_ops.query_क्रमागत = query_क्रमागत;
	generic_hpc.ops = &generic_hpc_ops;

	status = cpci_hp_रेजिस्टर_controller(&generic_hpc);
	अगर (status != 0) अणु
		err("Could not register cPCI hotplug controller");
		वापस -ENODEV;
	पूर्ण
	dbg("registered controller");

	status = cpci_hp_रेजिस्टर_bus(bus, first_slot, last_slot);
	अगर (status != 0) अणु
		err("Could not register cPCI hotplug bus");
		जाओ init_bus_रेजिस्टर_error;
	पूर्ण
	dbg("registered bus");

	status = cpci_hp_start();
	अगर (status != 0) अणु
		err("Could not started cPCI hotplug system");
		जाओ init_start_error;
	पूर्ण
	dbg("started cpci hp system");
	वापस 0;
init_start_error:
	cpci_hp_unरेजिस्टर_bus(bus);
init_bus_रेजिस्टर_error:
	cpci_hp_unरेजिस्टर_controller(&generic_hpc);
	err("status = %d", status);
	वापस status;

पूर्ण

अटल व्योम __निकास cpcihp_generic_निकास(व्योम)
अणु
	cpci_hp_stop();
	cpci_hp_unरेजिस्टर_bus(bus);
	cpci_hp_unरेजिस्टर_controller(&generic_hpc);
	release_region(port, 1);
पूर्ण

module_init(cpcihp_generic_init);
module_निकास(cpcihp_generic_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debugging mode enabled or not");
module_param(bridge, अक्षरp, 0);
MODULE_PARM_DESC(bridge, "Hotswap bus bridge device, <bus>:<slot> (bus and slot are in hexadecimal)");
module_param(first_slot, byte, 0);
MODULE_PARM_DESC(first_slot, "Hotswap bus first slot number");
module_param(last_slot, byte, 0);
MODULE_PARM_DESC(last_slot, "Hotswap bus last slot number");
module_param_hw(port, uलघु, ioport, 0);
MODULE_PARM_DESC(port, "#ENUM signal I/O port");
module_param(क्रमागत_bit, uपूर्णांक, 0);
MODULE_PARM_DESC(क्रमागत_bit, "#ENUM signal bit (0-7)");
