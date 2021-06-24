<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम PowerQUICC II
 * (a.k.a. 82xx with CPM, not the 8240 family of chips)
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"
#समावेश "io.h"
#समावेश "fsl-soc.h"

#घोषणा TARGET_CPM2
#घोषणा TARGET_HAS_ETH1
#समावेश "ppcboot.h"

अटल bd_t bd;

काष्ठा cs_range अणु
	u32 csnum;
	u32 base; /* must be zero */
	u32 addr;
	u32 size;
पूर्ण;

काष्ठा pci_range अणु
	u32 flags;
	u32 pci_addr[2];
	u32 phys_addr;
	u32 size[2];
पूर्ण;

काष्ठा cs_range cs_ranges_buf[MAX_PROP_LEN / माप(काष्ठा cs_range)];
काष्ठा pci_range pci_ranges_buf[MAX_PROP_LEN / माप(काष्ठा pci_range)];

/* Dअगरferent versions of u-boot put the BCSR in dअगरferent places, and
 * some करोn't set up the PCI PIC at all, so we assume the device tree is
 * sane and update the BRx रेजिस्टरs appropriately.
 *
 * For any node defined as compatible with fsl,pq2-localbus,
 * #address/#size must be 2/1 क्रम the localbus, and 1/1 क्रम the parent bus.
 * Ranges must be क्रम whole chip selects.
 */
अटल व्योम update_cs_ranges(व्योम)
अणु
	व्योम *bus_node, *parent_node;
	u32 *ctrl_addr;
	अचिन्हित दीर्घ ctrl_size;
	u32 naddr, nsize;
	पूर्णांक len;
	पूर्णांक i;

	bus_node = finddevice("/localbus");
	अगर (!bus_node || !dt_is_compatible(bus_node, "fsl,pq2-localbus"))
		वापस;

	dt_get_reg_क्रमmat(bus_node, &naddr, &nsize);
	अगर (naddr != 2 || nsize != 1)
		जाओ err;

	parent_node = get_parent(bus_node);
	अगर (!parent_node)
		जाओ err;

	dt_get_reg_क्रमmat(parent_node, &naddr, &nsize);
	अगर (naddr != 1 || nsize != 1)
		जाओ err;

	अगर (!dt_xlate_reg(bus_node, 0, (अचिन्हित दीर्घ *)&ctrl_addr,
	                  &ctrl_size))
		जाओ err;

	len = getprop(bus_node, "ranges", cs_ranges_buf, माप(cs_ranges_buf));

	क्रम (i = 0; i < len / माप(काष्ठा cs_range); i++) अणु
		u32 base, option;
		पूर्णांक cs = cs_ranges_buf[i].csnum;
		अगर (cs >= ctrl_size / 8)
			जाओ err;

		अगर (cs_ranges_buf[i].base != 0)
			जाओ err;

		base = in_be32(&ctrl_addr[cs * 2]);

		/* If CS is alपढ़ोy valid, use the existing flags.
		 * Otherwise, guess a sane शेष.
		 */
		अगर (base & 1) अणु
			base &= 0x7fff;
			option = in_be32(&ctrl_addr[cs * 2 + 1]) & 0x7fff;
		पूर्ण अन्यथा अणु
			base = 0x1801;
			option = 0x10;
		पूर्ण

		out_be32(&ctrl_addr[cs * 2], 0);
		out_be32(&ctrl_addr[cs * 2 + 1],
		         option | ~(cs_ranges_buf[i].size - 1));
		out_be32(&ctrl_addr[cs * 2], base | cs_ranges_buf[i].addr);
	पूर्ण

	वापस;

err:
	म_लिखो("Bad /localbus node\r\n");
पूर्ण

/* Older u-boots करोn't set PCI up properly.  Update the hardware to match
 * the device tree.  The prefetch mem region and non-prefetch mem region
 * must be contiguous in the host bus.  As required by the PCI binding,
 * PCI #addr/#size must be 3/2.  The parent bus must be 1/1.  Only
 * 32-bit PCI is supported.  All three region types (prefetchable mem,
 * non-prefetchable mem, and I/O) must be present.
 */
अटल व्योम fixup_pci(व्योम)
अणु
	काष्ठा pci_range *mem = शून्य, *mmio = शून्य,
	                 *io = शून्य, *mem_base = शून्य;
	u32 *pci_regs[3];
	u8 *soc_regs;
	पूर्णांक i, len;
	व्योम *node, *parent_node;
	u32 naddr, nsize, mem_घात2, mem_mask;

	node = finddevice("/pci");
	अगर (!node || !dt_is_compatible(node, "fsl,pq2-pci"))
		वापस;

	क्रम (i = 0; i < 3; i++)
		अगर (!dt_xlate_reg(node, i,
		                  (अचिन्हित दीर्घ *)&pci_regs[i], शून्य))
			जाओ err;

	soc_regs = (u8 *)fsl_get_immr();
	अगर (!soc_regs)
		जाओ unhandled;

	dt_get_reg_क्रमmat(node, &naddr, &nsize);
	अगर (naddr != 3 || nsize != 2)
		जाओ err;

	parent_node = get_parent(node);
	अगर (!parent_node)
		जाओ err;

	dt_get_reg_क्रमmat(parent_node, &naddr, &nsize);
	अगर (naddr != 1 || nsize != 1)
		जाओ unhandled;

	len = getprop(node, "ranges", pci_ranges_buf,
	              माप(pci_ranges_buf));

	क्रम (i = 0; i < len / माप(काष्ठा pci_range); i++) अणु
		u32 flags = pci_ranges_buf[i].flags & 0x43000000;

		अगर (flags == 0x42000000)
			mem = &pci_ranges_buf[i];
		अन्यथा अगर (flags == 0x02000000)
			mmio = &pci_ranges_buf[i];
		अन्यथा अगर (flags == 0x01000000)
			io = &pci_ranges_buf[i];
	पूर्ण

	अगर (!mem || !mmio || !io)
		जाओ unhandled;
	अगर (mem->size[1] != mmio->size[1])
		जाओ unhandled;
	अगर (mem->size[1] & (mem->size[1] - 1))
		जाओ unhandled;
	अगर (io->size[1] & (io->size[1] - 1))
		जाओ unhandled;

	अगर (mem->phys_addr + mem->size[1] == mmio->phys_addr)
		mem_base = mem;
	अन्यथा अगर (mmio->phys_addr + mmio->size[1] == mem->phys_addr)
		mem_base = mmio;
	अन्यथा
		जाओ unhandled;

	out_be32(&pci_regs[1][0], mem_base->phys_addr | 1);
	out_be32(&pci_regs[2][0], ~(mem->size[1] + mmio->size[1] - 1));

	out_be32(&pci_regs[1][1], io->phys_addr | 1);
	out_be32(&pci_regs[2][1], ~(io->size[1] - 1));

	out_le32(&pci_regs[0][0], mem->pci_addr[1] >> 12);
	out_le32(&pci_regs[0][2], mem->phys_addr >> 12);
	out_le32(&pci_regs[0][4], (~(mem->size[1] - 1) >> 12) | 0xa0000000);

	out_le32(&pci_regs[0][6], mmio->pci_addr[1] >> 12);
	out_le32(&pci_regs[0][8], mmio->phys_addr >> 12);
	out_le32(&pci_regs[0][10], (~(mmio->size[1] - 1) >> 12) | 0x80000000);

	out_le32(&pci_regs[0][12], io->pci_addr[1] >> 12);
	out_le32(&pci_regs[0][14], io->phys_addr >> 12);
	out_le32(&pci_regs[0][16], (~(io->size[1] - 1) >> 12) | 0xc0000000);

	/* Inbound translation */
	out_le32(&pci_regs[0][58], 0);
	out_le32(&pci_regs[0][60], 0);

	mem_घात2 = 1 << (__ilog2_u32(bd.bi_memsize - 1) + 1);
	mem_mask = ~(mem_घात2 - 1) >> 12;
	out_le32(&pci_regs[0][62], 0xa0000000 | mem_mask);

	/* If PCI is disabled, drive RST high to enable. */
	अगर (!(in_le32(&pci_regs[0][32]) & 1)) अणु
		 /* Tpvrh (Power valid to RST# high) 100 ms */
		udelay(100000);

		out_le32(&pci_regs[0][32], 1);

		/* Trhfa (RST# high to first cfg access) 2^25 घड़ीs */
		udelay(1020000);
	पूर्ण

	/* Enable bus master and memory access */
	out_le32(&pci_regs[0][64], 0x80000004);
	out_le32(&pci_regs[0][65], in_le32(&pci_regs[0][65]) | 6);

	/* Park the bus on PCI, and elevate PCI's arbitration priority,
	 * as required by section 9.6 of the user's manual.
	 */
	out_8(&soc_regs[0x10028], 3);
	out_be32((u32 *)&soc_regs[0x1002c], 0x01236745);

	वापस;

err:
	म_लिखो("Bad PCI node -- using existing firmware setup.\r\n");
	वापस;

unhandled:
	म_लिखो("Unsupported PCI node -- using existing firmware setup.\r\n");
पूर्ण

अटल व्योम pq2_platक्रमm_fixups(व्योम)
अणु
	व्योम *node;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr, bd.bi_enet1addr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 4, bd.bi_busfreq);

	node = finddevice("/soc/cpm");
	अगर (node)
		setprop(node, "clock-frequency", &bd.bi_cpmfreq, 4);

	node = finddevice("/soc/cpm/brg");
	अगर (node)
		setprop(node, "clock-frequency",  &bd.bi_brgfreq, 4);

	update_cs_ranges();
	fixup_pci();
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = pq2_platक्रमm_fixups;
पूर्ण
