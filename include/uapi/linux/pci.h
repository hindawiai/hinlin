<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	pci.h
 *
 *	PCI defines and function prototypes
 *	Copyright 1994, Drew Eckhardt
 *	Copyright 1997--1999 Martin Mares <mj@ucw.cz>
 *
 *	For more inक्रमmation, please consult the following manuals (look at
 *	http://www.pcisig.com/ क्रम how to get them):
 *
 *	PCI BIOS Specअगरication
 *	PCI Local Bus Specअगरication
 *	PCI to PCI Bridge Specअगरication
 *	PCI System Design Guide
 */

#अगर_अघोषित _UAPILINUX_PCI_H
#घोषणा _UAPILINUX_PCI_H

#समावेश <linux/pci_regs.h>	/* The pci रेजिस्टर defines */

/*
 * The PCI पूर्णांकerface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *	7:3 = slot
 *	2:0 = function
 */
#घोषणा PCI_DEVFN(slot, func)	((((slot) & 0x1f) << 3) | ((func) & 0x07))
#घोषणा PCI_SLOT(devfn)		(((devfn) >> 3) & 0x1f)
#घोषणा PCI_FUNC(devfn)		((devfn) & 0x07)

/* Ioctls क्रम /proc/bus/pci/X/Y nodes. */
#घोषणा PCIIOC_BASE		('P' << 24 | 'C' << 16 | 'I' << 8)
#घोषणा PCIIOC_CONTROLLER	(PCIIOC_BASE | 0x00)	/* Get controller क्रम PCI device. */
#घोषणा PCIIOC_MMAP_IS_IO	(PCIIOC_BASE | 0x01)	/* Set mmap state to I/O space. */
#घोषणा PCIIOC_MMAP_IS_MEM	(PCIIOC_BASE | 0x02)	/* Set mmap state to MEM space. */
#घोषणा PCIIOC_WRITE_COMBINE	(PCIIOC_BASE | 0x03)	/* Enable/disable ग_लिखो-combining. */

#पूर्ण_अगर /* _UAPILINUX_PCI_H */
