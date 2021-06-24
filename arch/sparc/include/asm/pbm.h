<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * pbm.h: PCI bus module pseuकरो driver software state
 *        Aकरोpted from sparc64 by V. Roganov and G. Raiko
 *
 * Original header:
 * pbm.h: U2P PCI bus module pseuकरो driver software state.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 *
 * To put things पूर्णांकo perspective, consider sparc64 with a few PCI controllers.
 * Each type would have an own काष्ठाure, with instances related one to one.
 * We have only pcic on sparc, but we want to be compatible with sparc64 pbm.h.
 * All three represent dअगरferent असलtractions.
 *   pci_bus  - Linux PCI subप्रणाली view of a PCI bus (including bridged buses)
 *   pbm      - Arch-specअगरic view of a PCI bus (sparc or sparc64)
 *   pcic     - Chip-specअगरic inक्रमmation क्रम PCIC.
 */

#अगर_अघोषित __SPARC_PBM_H
#घोषणा __SPARC_PBM_H

#समावेश <linux/pci.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>

काष्ठा linux_pbm_info अणु
	पूर्णांक		prom_node;
	अक्षर		prom_name[64];
	/* काष्ठा linux_prom_pci_ranges	pbm_ranges[PROMREG_MAX]; */
	/* पूर्णांक		num_pbm_ranges; */

	/* Now things क्रम the actual PCI bus probes. */
	अचिन्हित पूर्णांक	pci_first_busno;	/* Can it be nonzero? */
	काष्ठा pci_bus	*pci_bus;		/* Was अंतरभूत, MJ allocs now */
पूर्ण;

/* PCI devices which are not bridges have this placed in their pci_dev
 * sysdata member.  This makes OBP aware PCI device drivers easier to
 * code.
 */
काष्ठा pcidev_cookie अणु
	काष्ठा linux_pbm_info		*pbm;
	काष्ठा device_node		*prom_node;
पूर्ण;

#पूर्ण_अगर /* !(__SPARC_PBM_H) */
