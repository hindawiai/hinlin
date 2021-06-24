<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale QUICC Engine USB Host Controller Driver
 *
 * Copyright (c) Freescale Semicondutor, Inc. 2006.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) Logic Product Development, Inc. 2007
 *               Peter Barada <peterb@logicpd.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "fhci.h"

व्योम fhci_dbg_isr(काष्ठा fhci_hcd *fhci, पूर्णांक usb_er)
अणु
	पूर्णांक i;

	अगर (usb_er == -1) अणु
		fhci->usb_irq_stat[12]++;
		वापस;
	पूर्ण

	क्रम (i = 0; i < 12; ++i) अणु
		अगर (usb_er & (1 << i))
			fhci->usb_irq_stat[i]++;
	पूर्ण
पूर्ण

अटल पूर्णांक fhci_dfs_regs_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा fhci_hcd *fhci = s->निजी;
	काष्ठा qe_usb_ctlr __iomem *regs = fhci->regs;

	seq_म_लिखो(s,
		"mode: 0x%x\n" "addr: 0x%x\n"
		"command: 0x%x\n" "ep0: 0x%x\n"
		"event: 0x%x\n" "mask: 0x%x\n"
		"status: 0x%x\n" "SOF timer: %d\n"
		"frame number: %d\n"
		"lines status: 0x%x\n",
		in_8(&regs->usb_usmod), in_8(&regs->usb_usadr),
		in_8(&regs->usb_uscom), in_be16(&regs->usb_usep[0]),
		in_be16(&regs->usb_usber), in_be16(&regs->usb_usbmr),
		in_8(&regs->usb_usbs), in_be16(&regs->usb_ussft),
		in_be16(&regs->usb_usfrn),
		fhci_ioports_check_bus_state(fhci));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fhci_dfs_regs);

अटल पूर्णांक fhci_dfs_irq_stat_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा fhci_hcd *fhci = s->निजी;
	पूर्णांक *usb_irq_stat = fhci->usb_irq_stat;

	seq_म_लिखो(s,
		"RXB: %d\n" "TXB: %d\n" "BSY: %d\n"
		"SOF: %d\n" "TXE0: %d\n" "TXE1: %d\n"
		"TXE2: %d\n" "TXE3: %d\n" "IDLE: %d\n"
		"RESET: %d\n" "SFT: %d\n" "MSF: %d\n"
		"IDLE_ONLY: %d\n",
		usb_irq_stat[0], usb_irq_stat[1], usb_irq_stat[2],
		usb_irq_stat[3], usb_irq_stat[4], usb_irq_stat[5],
		usb_irq_stat[6], usb_irq_stat[7], usb_irq_stat[8],
		usb_irq_stat[9], usb_irq_stat[10], usb_irq_stat[11],
		usb_irq_stat[12]);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fhci_dfs_irq_stat);

व्योम fhci_dfs_create(काष्ठा fhci_hcd *fhci)
अणु
	काष्ठा device *dev = fhci_to_hcd(fhci)->self.controller;

	fhci->dfs_root = debugfs_create_dir(dev_name(dev), usb_debug_root);

	debugfs_create_file("regs", S_IFREG | S_IRUGO, fhci->dfs_root, fhci,
			    &fhci_dfs_regs_fops);
	debugfs_create_file("irq_stat", S_IFREG | S_IRUGO, fhci->dfs_root, fhci,
			    &fhci_dfs_irq_stat_fops);
पूर्ण

व्योम fhci_dfs_destroy(काष्ठा fhci_hcd *fhci)
अणु
	debugfs_हटाओ_recursive(fhci->dfs_root);
पूर्ण
