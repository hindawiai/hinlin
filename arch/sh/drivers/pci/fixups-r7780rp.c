<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/fixups-r7780rp.c
 *
 * Highlander R7780RP-1 PCI fixups
 *
 * Copyright (C) 2003  Lineo uSolutions, Inc.
 * Copyright (C) 2004 - 2006  Paul Mundt
 */
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश "pci-sh4.h"

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	वापस evt2irq(0xa20) + slot;
पूर्ण
