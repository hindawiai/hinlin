<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Vojtech Pavlik
 */

/*
 * EMU10k1 - SB Live / Audigy - gameport driver क्रम Linux
 */

/*
 */

#समावेश <यंत्र/पन.स>

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/gameport.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("EMU10k1 gameport driver");
MODULE_LICENSE("GPL");

काष्ठा emu अणु
	काष्ठा pci_dev *dev;
	काष्ठा gameport *gameport;
	पूर्णांक io;
	पूर्णांक size;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id emu_tbl[] = अणु

	अणु 0x1102, 0x7002, PCI_ANY_ID, PCI_ANY_ID पूर्ण, /* SB Live gameport */
	अणु 0x1102, 0x7003, PCI_ANY_ID, PCI_ANY_ID पूर्ण, /* Audigy gameport */
	अणु 0x1102, 0x7004, PCI_ANY_ID, PCI_ANY_ID पूर्ण, /* Dell SB Live */
	अणु 0x1102, 0x7005, PCI_ANY_ID, PCI_ANY_ID पूर्ण, /* Audigy LS gameport */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, emu_tbl);

अटल पूर्णांक emu_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा emu *emu;
	काष्ठा gameport *port;
	पूर्णांक error;

	emu = kzalloc(माप(काष्ठा emu), GFP_KERNEL);
	port = gameport_allocate_port();
	अगर (!emu || !port) अणु
		prपूर्णांकk(KERN_ERR "emu10k1-gp: Memory allocation failed\n");
		error = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	error = pci_enable_device(pdev);
	अगर (error)
		जाओ err_out_मुक्त;

	emu->io = pci_resource_start(pdev, 0);
	emu->size = pci_resource_len(pdev, 0);

	emu->dev = pdev;
	emu->gameport = port;

	gameport_set_name(port, "EMU10K1");
	gameport_set_phys(port, "pci%s/gameport0", pci_name(pdev));
	port->dev.parent = &pdev->dev;
	port->io = emu->io;

	अगर (!request_region(emu->io, emu->size, "emu10k1-gp")) अणु
		prपूर्णांकk(KERN_ERR "emu10k1-gp: unable to grab region 0x%x-0x%x\n",
			emu->io, emu->io + emu->size - 1);
		error = -EBUSY;
		जाओ err_out_disable_dev;
	पूर्ण

	pci_set_drvdata(pdev, emu);

	gameport_रेजिस्टर_port(port);

	वापस 0;

 err_out_disable_dev:
	pci_disable_device(pdev);
 err_out_मुक्त:
	gameport_मुक्त_port(port);
	kमुक्त(emu);
	वापस error;
पूर्ण

अटल व्योम emu_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा emu *emu = pci_get_drvdata(pdev);

	gameport_unरेजिस्टर_port(emu->gameport);
	release_region(emu->io, emu->size);
	kमुक्त(emu);

	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver emu_driver = अणु
        .name =         "Emu10k1_gameport",
        .id_table =     emu_tbl,
        .probe =        emu_probe,
	.हटाओ =	emu_हटाओ,
पूर्ण;

module_pci_driver(emu_driver);
