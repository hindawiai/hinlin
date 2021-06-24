<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Functions क्रम setting up and using a MPC106 northbridge
 * Extracted from arch/घातerpc/platक्रमms/घातermac/pci.c.
 *
 * Copyright (C) 2003 Benjamin Herrenschmuidt (benh@kernel.crashing.org)
 * Copyright (C) 1997 Paul Mackerras (paulus@samba.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/grackle.h>

#घोषणा GRACKLE_CFA(b, d, o)	(0x80 | ((b) << 8) | ((d) << 16) \
				 | (((o) & ~3) << 24))

#घोषणा GRACKLE_PICR1_STG		0x00000040
#घोषणा GRACKLE_PICR1_LOOPSNOOP		0x00000010

/* N.B. this is called beक्रमe bridges is initialized, so we can't
   use grackle_pcibios_अणुपढ़ो,ग_लिखोपूर्ण_config_dword. */
अटल अंतरभूत व्योम grackle_set_stg(काष्ठा pci_controller* bp, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val;

	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	val = in_le32(bp->cfg_data);
	val = enable? (val | GRACKLE_PICR1_STG) :
		(val & ~GRACKLE_PICR1_STG);
	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	out_le32(bp->cfg_data, val);
	(व्योम)in_le32(bp->cfg_data);
पूर्ण

अटल अंतरभूत व्योम grackle_set_loop_snoop(काष्ठा pci_controller *bp, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val;

	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	val = in_le32(bp->cfg_data);
	val = enable? (val | GRACKLE_PICR1_LOOPSNOOP) :
		(val & ~GRACKLE_PICR1_LOOPSNOOP);
	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	out_le32(bp->cfg_data, val);
	(व्योम)in_le32(bp->cfg_data);
पूर्ण

व्योम __init setup_grackle(काष्ठा pci_controller *hose)
अणु
	setup_indirect_pci(hose, 0xfec00000, 0xfee00000, 0);
	अगर (of_machine_is_compatible("PowerMac1,1"))
		pci_add_flags(PCI_REASSIGN_ALL_BUS);
	अगर (of_machine_is_compatible("AAPL,PowerBook1998"))
		grackle_set_loop_snoop(hose, 1);
#अगर 0	/* Disabled क्रम now, HW problems ??? */
	grackle_set_stg(hose, 1);
#पूर्ण_अगर
पूर्ण
