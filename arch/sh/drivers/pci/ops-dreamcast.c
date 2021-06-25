<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI operations क्रम the Sega Dreamcast
 *
 * Copyright (C) 2001, 2002  M. R. Brown
 * Copyright (C) 2002, 2003  Paul Mundt
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <mach/pci.h>

/*
 * The !gapspci_config_access हाल really shouldn't happen, ever, unless
 * someone implicitly messes around with the last devfn value.. otherwise we
 * only support a single device anyways, and अगर we didn't have a BBA, we
 * wouldn't make it terribly far through the PCI setup anyways.
 *
 * Also, we could very easily support both Type 0 and Type 1 configurations
 * here, but since it करोesn't seem that there is any such implementation in
 * existence, we करोn't bother.
 *
 * I suppose अगर someone actually माला_लो around to ripping the chip out of
 * the BBA and hanging some more devices off of it, then this might be
 * something to take पूर्णांकo consideration. However, due to the cost of the BBA,
 * and the general lack of activity by DC hardware hackers, this करोesn't seem
 * likely to happen anyसमय soon.
 */
अटल पूर्णांक gapspci_config_access(अचिन्हित अक्षर bus, अचिन्हित पूर्णांक devfn)
अणु
	वापस (bus == 0) && (devfn == 0);
पूर्ण

/*
 * We can also actually पढ़ो and ग_लिखो in b/w/l sizes! Thankfully this part
 * was at least करोne right, and we करोn't have to करो the stupid masking and
 * shअगरting that we करो on the 7751! Small wonders never cease to amaze.
 */
अटल पूर्णांक gapspci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	*val = 0xffffffff;

	अगर (!gapspci_config_access(bus->number, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1: *val = inb(GAPSPCI_BBA_CONFIG+where); अवरोध;
	हाल 2: *val = inw(GAPSPCI_BBA_CONFIG+where); अवरोध;
	हाल 4: *val = inl(GAPSPCI_BBA_CONFIG+where); अवरोध;
	पूर्ण

        वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक gapspci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अगर (!gapspci_config_access(bus->number, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1: outb(( u8)val, GAPSPCI_BBA_CONFIG+where); अवरोध;
	हाल 2: outw((u16)val, GAPSPCI_BBA_CONFIG+where); अवरोध;
	हाल 4: outl((u32)val, GAPSPCI_BBA_CONFIG+where); अवरोध;
	पूर्ण

        वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops gapspci_pci_ops = अणु
	.पढ़ो	= gapspci_पढ़ो,
	.ग_लिखो	= gapspci_ग_लिखो,
पूर्ण;
