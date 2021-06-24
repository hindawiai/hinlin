<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/console.c
 *
 * Architecture-specअगरic specअगरic support क्रम VGA device on 
 * non-0 I/O hose
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/vt.h>
#समावेश <यंत्र/vga.h>
#समावेश <यंत्र/machvec.h>

#समावेश "pci_impl.h"

#अगर_घोषित CONFIG_VGA_HOSE

काष्ठा pci_controller *pci_vga_hose;
अटल काष्ठा resource alpha_vga = अणु
	.name	= "alpha-vga+",
	.flags	= IORESOURCE_IO,
	.start	= 0x3C0,
	.end	= 0x3DF
पूर्ण;

अटल काष्ठा pci_controller * __init 
शेष_vga_hose_select(काष्ठा pci_controller *h1, काष्ठा pci_controller *h2)
अणु
	अगर (h2->index < h1->index)
		वापस h2;

	वापस h1;
पूर्ण

व्योम __init 
locate_and_init_vga(व्योम *(*sel_func)(व्योम *, व्योम *))
अणु
	काष्ठा pci_controller *hose = शून्य;
	काष्ठा pci_dev *dev = शून्य;

	/* Default the select function */
	अगर (!sel_func) sel_func = (व्योम *)शेष_vga_hose_select;

	/* Find the console VGA device */
	क्रम(dev=शून्य; (dev=pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, dev));) अणु
		अगर (!hose)
			hose = dev->sysdata;
		अन्यथा
			hose = sel_func(hose, dev->sysdata);
	पूर्ण

	/* Did we alपढ़ोy initialize the correct one? Is there one? */
	अगर (!hose || (conचयनp == &vga_con && pci_vga_hose == hose))
		वापस;

	/* Create a new VGA ioport resource WRT the hose it is on. */
	alpha_vga.start += hose->io_space->start;
	alpha_vga.end += hose->io_space->start;
	request_resource(hose->io_space, &alpha_vga);

	/* Set the VGA hose and init the new console. */
	pci_vga_hose = hose;
	console_lock();
	करो_take_over_console(&vga_con, 0, MAX_NR_CONSOLES-1, 1);
	console_unlock();
पूर्ण

व्योम __init
find_console_vga_hose(व्योम)
अणु
	u64 *pu64 = (u64 *)((u64)hwrpb + hwrpb->ctbt_offset);

	अगर (pu64[7] == 3) अणु	/* TERM_TYPE == graphics */
		काष्ठा pci_controller *hose;
		पूर्णांक h = (pu64[30] >> 24) & 0xff;	/* console hose # */

		/*
		 * Our hose numbering DOES match the console's, so find
		 * the right one...
		 */
		क्रम (hose = hose_head; hose; hose = hose->next) अणु
			अगर (hose->index == h) अवरोध;
		पूर्ण

		अगर (hose) अणु
			prपूर्णांकk("Console graphics on hose %d\n", h);
			pci_vga_hose = hose;
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर
