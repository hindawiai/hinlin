<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  FM801 gameport driver क्रम Linux
 *
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>

#घोषणा PCI_VENDOR_ID_FORTEMEDIA	0x1319
#घोषणा PCI_DEVICE_ID_FM801_GP	0x0802

#घोषणा HAVE_COOKED

काष्ठा fm801_gp अणु
	काष्ठा gameport *gameport;
	काष्ठा resource *res_port;
पूर्ण;

#अगर_घोषित HAVE_COOKED
अटल पूर्णांक fm801_gp_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	अचिन्हित लघु w;

	w = inw(gameport->io + 2);
	*buttons = (~w >> 14) & 0x03;
	axes[0] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gameport->io + 4);
	axes[1] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gameport->io + 6);
	*buttons |= ((~w >> 14) & 0x03) << 2;
	axes[2] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gameport->io + 8);
	axes[3] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	outw(0xff, gameport->io); /* reset */

        वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fm801_gp_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	चयन (mode) अणु
#अगर_घोषित HAVE_COOKED
	हाल GAMEPORT_MODE_COOKED:
		वापस 0;
#पूर्ण_अगर
	हाल GAMEPORT_MODE_RAW:
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm801_gp_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fm801_gp *gp;
	काष्ठा gameport *port;
	पूर्णांक error;

	gp = kzalloc(माप(काष्ठा fm801_gp), GFP_KERNEL);
	port = gameport_allocate_port();
	अगर (!gp || !port) अणु
		prपूर्णांकk(KERN_ERR "fm801-gp: Memory allocation failed\n");
		error = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	error = pci_enable_device(pci);
	अगर (error)
		जाओ err_out_मुक्त;

	port->खोलो = fm801_gp_खोलो;
#अगर_घोषित HAVE_COOKED
	port->cooked_पढ़ो = fm801_gp_cooked_पढ़ो;
#पूर्ण_अगर
	gameport_set_name(port, "FM801");
	gameport_set_phys(port, "pci%s/gameport0", pci_name(pci));
	port->dev.parent = &pci->dev;
	port->io = pci_resource_start(pci, 0);

	gp->gameport = port;
	gp->res_port = request_region(port->io, 0x10, "FM801 GP");
	अगर (!gp->res_port) अणु
		prपूर्णांकk(KERN_DEBUG "fm801-gp: unable to grab region 0x%x-0x%x\n",
			port->io, port->io + 0x0f);
		error = -EBUSY;
		जाओ err_out_disable_dev;
	पूर्ण

	pci_set_drvdata(pci, gp);

	outb(0x60, port->io + 0x0d); /* enable joystick 1 and 2 */
	gameport_रेजिस्टर_port(port);

	वापस 0;

 err_out_disable_dev:
	pci_disable_device(pci);
 err_out_मुक्त:
	gameport_मुक्त_port(port);
	kमुक्त(gp);
	वापस error;
पूर्ण

अटल व्योम fm801_gp_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा fm801_gp *gp = pci_get_drvdata(pci);

	gameport_unरेजिस्टर_port(gp->gameport);
	release_resource(gp->res_port);
	kमुक्त(gp);

	pci_disable_device(pci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id fm801_gp_id_table[] = अणु
	अणु PCI_VENDOR_ID_FORTEMEDIA, PCI_DEVICE_ID_FM801_GP, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0  पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, fm801_gp_id_table);

अटल काष्ठा pci_driver fm801_gp_driver = अणु
	.name =		"FM801_gameport",
	.id_table =	fm801_gp_id_table,
	.probe =	fm801_gp_probe,
	.हटाओ =	fm801_gp_हटाओ,
पूर्ण;

module_pci_driver(fm801_gp_driver);

MODULE_DESCRIPTION("FM801 gameport driver");
MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_LICENSE("GPL");
