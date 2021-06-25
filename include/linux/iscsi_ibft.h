<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2007 Red Hat, Inc.
 *  by Peter Jones <pjones@redhat.com>
 *  Copyright 2007 IBM, Inc.
 *  by Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *  Copyright 2008
 *  by Konrad Rzeszutek <ketuzsezr@darnok.org>
 *
 * This code exposes the iSCSI Boot Format Table to userland via sysfs.
 */

#अगर_अघोषित ISCSI_IBFT_H
#घोषणा ISCSI_IBFT_H

#समावेश <linux/acpi.h>

/*
 * Logical location of iSCSI Boot Format Table.
 * If the value is शून्य there is no iBFT on the machine.
 */
बाह्य काष्ठा acpi_table_ibft *ibft_addr;

/*
 * Routine used to find and reserve the iSCSI Boot Format Table. The
 * mapped address is set in the ibft_addr variable.
 */
#अगर_घोषित CONFIG_ISCSI_IBFT_FIND
अचिन्हित दीर्घ find_ibft_region(अचिन्हित दीर्घ *sizep);
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ find_ibft_region(अचिन्हित दीर्घ *sizep)
अणु
	*sizep = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* ISCSI_IBFT_H */
