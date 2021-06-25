<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe driver क्रम Renesas R-Car SoCs
 *  Copyright (C) 2014-2020 Renesas Electronics Europe Ltd
 *
 * Author: Phil Edworthy <phil.edworthy@renesas.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश "pcie-rcar.h"

व्योम rcar_pci_ग_लिखो_reg(काष्ठा rcar_pcie *pcie, u32 val, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl(val, pcie->base + reg);
पूर्ण

u32 rcar_pci_पढ़ो_reg(काष्ठा rcar_pcie *pcie, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(pcie->base + reg);
पूर्ण

व्योम rcar_rmw32(काष्ठा rcar_pcie *pcie, पूर्णांक where, u32 mask, u32 data)
अणु
	अचिन्हित पूर्णांक shअगरt = BITS_PER_BYTE * (where & 3);
	u32 val = rcar_pci_पढ़ो_reg(pcie, where & ~3);

	val &= ~(mask << shअगरt);
	val |= data << shअगरt;
	rcar_pci_ग_लिखो_reg(pcie, val, where & ~3);
पूर्ण

पूर्णांक rcar_pcie_रुको_क्रम_phyrdy(काष्ठा rcar_pcie *pcie)
अणु
	अचिन्हित पूर्णांक समयout = 10;

	जबतक (समयout--) अणु
		अगर (rcar_pci_पढ़ो_reg(pcie, PCIEPHYSR) & PHYRDY)
			वापस 0;

		msleep(5);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक rcar_pcie_रुको_क्रम_dl(काष्ठा rcar_pcie *pcie)
अणु
	अचिन्हित पूर्णांक समयout = 10000;

	जबतक (समयout--) अणु
		अगर ((rcar_pci_पढ़ो_reg(pcie, PCIETSTR) & DATA_LINK_ACTIVE))
			वापस 0;

		udelay(5);
		cpu_relax();
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

व्योम rcar_pcie_set_outbound(काष्ठा rcar_pcie *pcie, पूर्णांक win,
			    काष्ठा resource_entry *winकरोw)
अणु
	/* Setup PCIe address space mappings क्रम each resource */
	काष्ठा resource *res = winकरोw->res;
	resource_माप_प्रकार res_start;
	resource_माप_प्रकार size;
	u32 mask;

	rcar_pci_ग_लिखो_reg(pcie, 0x00000000, PCIEPTCTLR(win));

	/*
	 * The PAMR mask is calculated in units of 128Bytes, which
	 * keeps things pretty simple.
	 */
	size = resource_size(res);
	अगर (size > 128)
		mask = (roundup_घात_of_two(size) / SZ_128) - 1;
	अन्यथा
		mask = 0x0;
	rcar_pci_ग_लिखो_reg(pcie, mask << 7, PCIEPAMR(win));

	अगर (res->flags & IORESOURCE_IO)
		res_start = pci_pio_to_address(res->start) - winकरोw->offset;
	अन्यथा
		res_start = res->start - winकरोw->offset;

	rcar_pci_ग_लिखो_reg(pcie, upper_32_bits(res_start), PCIEPAUR(win));
	rcar_pci_ग_लिखो_reg(pcie, lower_32_bits(res_start) & ~0x7F,
			   PCIEPALR(win));

	/* First resource is क्रम IO */
	mask = PAR_ENABLE;
	अगर (res->flags & IORESOURCE_IO)
		mask |= IO_SPACE;

	rcar_pci_ग_लिखो_reg(pcie, mask, PCIEPTCTLR(win));
पूर्ण

व्योम rcar_pcie_set_inbound(काष्ठा rcar_pcie *pcie, u64 cpu_addr,
			   u64 pci_addr, u64 flags, पूर्णांक idx, bool host)
अणु
	/*
	 * Set up 64-bit inbound regions as the range parser करोesn't
	 * distinguish between 32 and 64-bit types.
	 */
	अगर (host)
		rcar_pci_ग_लिखो_reg(pcie, lower_32_bits(pci_addr),
				   PCIEPRAR(idx));
	rcar_pci_ग_लिखो_reg(pcie, lower_32_bits(cpu_addr), PCIELAR(idx));
	rcar_pci_ग_लिखो_reg(pcie, flags, PCIELAMR(idx));

	अगर (host)
		rcar_pci_ग_लिखो_reg(pcie, upper_32_bits(pci_addr),
				   PCIEPRAR(idx + 1));
	rcar_pci_ग_लिखो_reg(pcie, upper_32_bits(cpu_addr), PCIELAR(idx + 1));
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIELAMR(idx + 1));
पूर्ण
