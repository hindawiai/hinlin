<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright 2007-2010 Red Hat, Inc.
 *  by Peter Jones <pjones@redhat.com>
 *  Copyright 2007 IBM, Inc.
 *  by Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *  Copyright 2008
 *  by Konrad Rzeszutek <ketuzsezr@darnok.org>
 *
 * This code finds the iSCSI Boot Format Table.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/efi.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iscsi_ibft.h>

#समावेश <यंत्र/mmzone.h>

/*
 * Physical location of iSCSI Boot Format Table.
 */
काष्ठा acpi_table_ibft *ibft_addr;
EXPORT_SYMBOL_GPL(ibft_addr);

अटल स्थिर काष्ठा अणु
	अक्षर *sign;
पूर्ण ibft_signs[] = अणु
	अणु "iBFT" पूर्ण,
	अणु "BIFT" पूर्ण,	/* Broadcom iSCSI Offload */
पूर्ण;

#घोषणा IBFT_SIGN_LEN 4
#घोषणा IBFT_START 0x80000 /* 512kB */
#घोषणा IBFT_END 0x100000 /* 1MB */
#घोषणा VGA_MEM 0xA0000 /* VGA buffer */
#घोषणा VGA_SIZE 0x20000 /* 128kB */

अटल पूर्णांक __init find_ibft_in_mem(व्योम)
अणु
	अचिन्हित दीर्घ pos;
	अचिन्हित पूर्णांक len = 0;
	व्योम *virt;
	पूर्णांक i;

	क्रम (pos = IBFT_START; pos < IBFT_END; pos += 16) अणु
		/* The table can't be inside the VGA BIOS reserved space,
		 * so skip that area */
		अगर (pos == VGA_MEM)
			pos += VGA_SIZE;
		virt = isa_bus_to_virt(pos);

		क्रम (i = 0; i < ARRAY_SIZE(ibft_signs); i++) अणु
			अगर (स_भेद(virt, ibft_signs[i].sign, IBFT_SIGN_LEN) ==
			    0) अणु
				अचिन्हित दीर्घ *addr =
				    (अचिन्हित दीर्घ *)isa_bus_to_virt(pos + 4);
				len = *addr;
				/* अगर the length of the table extends past 1M,
				 * the table cannot be valid. */
				अगर (pos + len <= (IBFT_END-1)) अणु
					ibft_addr = (काष्ठा acpi_table_ibft *)virt;
					pr_info("iBFT found at 0x%lx.\n", pos);
					जाओ करोne;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	वापस len;
पूर्ण
/*
 * Routine used to find the iSCSI Boot Format Table. The logical
 * kernel address is set in the ibft_addr global variable.
 */
अचिन्हित दीर्घ __init find_ibft_region(अचिन्हित दीर्घ *sizep)
अणु
	ibft_addr = शून्य;

	/* iBFT 1.03 section 1.4.3.1 mandates that UEFI machines will
	 * only use ACPI क्रम this */

	अगर (!efi_enabled(EFI_BOOT))
		find_ibft_in_mem();

	अगर (ibft_addr) अणु
		*sizep = PAGE_ALIGN(ibft_addr->header.length);
		वापस (u64)virt_to_phys(ibft_addr);
	पूर्ण

	*sizep = 0;
	वापस 0;
पूर्ण
