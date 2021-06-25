<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Marvell
 *
 * Author: Thomas Petazzoni <thomas.petazzoni@bootlin.com>
 *
 * This file helps PCI controller drivers implement a fake root port
 * PCI bridge when the HW करोesn't provide such a root port PCI
 * bridge.
 *
 * It emulates a PCI bridge by providing a fake PCI configuration
 * space (and optionally a PCIe capability configuration space) in
 * memory. By शेष the पढ़ो/ग_लिखो operations simply पढ़ो and update
 * this fake configuration space in memory. However, PCI controller
 * drivers can provide through the 'struct pci_sw_bridge_ops'
 * काष्ठाure a set of operations to override or complement this
 * शेष behavior.
 */

#समावेश <linux/pci.h>
#समावेश "pci-bridge-emul.h"

#घोषणा PCI_BRIDGE_CONF_END	PCI_STD_HEADER_SIZखातापूर्ण
#घोषणा PCI_CAP_PCIE_SIZखातापूर्ण	(PCI_EXP_SLTSTA2 + 2)
#घोषणा PCI_CAP_PCIE_START	PCI_BRIDGE_CONF_END
#घोषणा PCI_CAP_PCIE_END	(PCI_CAP_PCIE_START + PCI_CAP_PCIE_SIZखातापूर्ण)

/**
 * काष्ठा pci_bridge_reg_behavior - रेजिस्टर bits behaviors
 * @ro:		Read-Only bits
 * @rw:		Read-Write bits
 * @w1c:	Write-1-to-Clear bits
 *
 * Reads and Writes will be filtered by specअगरied behavior. All other bits not
 * declared are assumed 'Reserved' and will वापस 0 on पढ़ोs, per PCIe 5.0:
 * "Reserved रेजिस्टर fields must be पढ़ो only and must वापस 0 (all 0's क्रम
 * multi-bit fields) when पढ़ो".
 */
काष्ठा pci_bridge_reg_behavior अणु
	/* Read-only bits */
	u32 ro;

	/* Read-ग_लिखो bits */
	u32 rw;

	/* Write-1-to-clear bits */
	u32 w1c;
पूर्ण;

अटल स्थिर
काष्ठा pci_bridge_reg_behavior pci_regs_behavior[PCI_STD_HEADER_SIZखातापूर्ण / 4] = अणु
	[PCI_VENDOR_ID / 4] = अणु .ro = ~0 पूर्ण,
	[PCI_COMMAND / 4] = अणु
		.rw = (PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
		       PCI_COMMAND_MASTER | PCI_COMMAND_PARITY |
		       PCI_COMMAND_SERR),
		.ro = ((PCI_COMMAND_SPECIAL | PCI_COMMAND_INVALIDATE |
			PCI_COMMAND_VGA_PALETTE | PCI_COMMAND_WAIT |
			PCI_COMMAND_FAST_BACK) |
		       (PCI_STATUS_CAP_LIST | PCI_STATUS_66MHZ |
			PCI_STATUS_FAST_BACK | PCI_STATUS_DEVSEL_MASK) << 16),
		.w1c = PCI_STATUS_ERROR_BITS << 16,
	पूर्ण,
	[PCI_CLASS_REVISION / 4] = अणु .ro = ~0 पूर्ण,

	/*
	 * Cache Line Size रेजिस्टर: implement as पढ़ो-only, we करो not
	 * pretend implementing "Memory Write and Invalidate"
	 * transactions"
	 *
	 * Latency Timer Register: implemented as पढ़ो-only, as "A
	 * bridge that is not capable of a burst transfer of more than
	 * two data phases on its primary पूर्णांकerface is permitted to
	 * hardwire the Latency Timer to a value of 16 or less"
	 *
	 * Header Type: always पढ़ो-only
	 *
	 * BIST रेजिस्टर: implemented as पढ़ो-only, as "A bridge that
	 * करोes not support BIST must implement this रेजिस्टर as a
	 * पढ़ो-only रेजिस्टर that वापसs 0 when पढ़ो"
	 */
	[PCI_CACHE_LINE_SIZE / 4] = अणु .ro = ~0 पूर्ण,

	/*
	 * Base Address रेजिस्टरs not used must be implemented as
	 * पढ़ो-only रेजिस्टरs that वापस 0 when पढ़ो.
	 */
	[PCI_BASE_ADDRESS_0 / 4] = अणु .ro = ~0 पूर्ण,
	[PCI_BASE_ADDRESS_1 / 4] = अणु .ro = ~0 पूर्ण,

	[PCI_PRIMARY_BUS / 4] = अणु
		/* Primary, secondary and subordinate bus are RW */
		.rw = GENMASK(24, 0),
		/* Secondary latency is पढ़ो-only */
		.ro = GENMASK(31, 24),
	पूर्ण,

	[PCI_IO_BASE / 4] = अणु
		/* The high four bits of I/O base/limit are RW */
		.rw = (GENMASK(15, 12) | GENMASK(7, 4)),

		/* The low four bits of I/O base/limit are RO */
		.ro = (((PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK |
			 PCI_STATUS_DEVSEL_MASK) << 16) |
		       GENMASK(11, 8) | GENMASK(3, 0)),

		.w1c = PCI_STATUS_ERROR_BITS << 16,
	पूर्ण,

	[PCI_MEMORY_BASE / 4] = अणु
		/* The high 12-bits of mem base/limit are RW */
		.rw = GENMASK(31, 20) | GENMASK(15, 4),

		/* The low four bits of mem base/limit are RO */
		.ro = GENMASK(19, 16) | GENMASK(3, 0),
	पूर्ण,

	[PCI_PREF_MEMORY_BASE / 4] = अणु
		/* The high 12-bits of pref mem base/limit are RW */
		.rw = GENMASK(31, 20) | GENMASK(15, 4),

		/* The low four bits of pref mem base/limit are RO */
		.ro = GENMASK(19, 16) | GENMASK(3, 0),
	पूर्ण,

	[PCI_PREF_BASE_UPPER32 / 4] = अणु
		.rw = ~0,
	पूर्ण,

	[PCI_PREF_LIMIT_UPPER32 / 4] = अणु
		.rw = ~0,
	पूर्ण,

	[PCI_IO_BASE_UPPER16 / 4] = अणु
		.rw = ~0,
	पूर्ण,

	[PCI_CAPABILITY_LIST / 4] = अणु
		.ro = GENMASK(7, 0),
	पूर्ण,

	[PCI_ROM_ADDRESS1 / 4] = अणु
		.rw = GENMASK(31, 11) | BIT(0),
	पूर्ण,

	/*
	 * Interrupt line (bits 7:0) are RW, पूर्णांकerrupt pin (bits 15:8)
	 * are RO, and bridge control (31:16) are a mix of RW, RO,
	 * reserved and W1C bits
	 */
	[PCI_INTERRUPT_LINE / 4] = अणु
		/* Interrupt line is RW */
		.rw = (GENMASK(7, 0) |
		       ((PCI_BRIDGE_CTL_PARITY |
			 PCI_BRIDGE_CTL_SERR |
			 PCI_BRIDGE_CTL_ISA |
			 PCI_BRIDGE_CTL_VGA |
			 PCI_BRIDGE_CTL_MASTER_ABORT |
			 PCI_BRIDGE_CTL_BUS_RESET |
			 BIT(8) | BIT(9) | BIT(11)) << 16)),

		/* Interrupt pin is RO */
		.ro = (GENMASK(15, 8) | ((PCI_BRIDGE_CTL_FAST_BACK) << 16)),

		.w1c = BIT(10) << 16,
	पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा pci_bridge_reg_behavior pcie_cap_regs_behavior[PCI_CAP_PCIE_SIZखातापूर्ण / 4] = अणु
	[PCI_CAP_LIST_ID / 4] = अणु
		/*
		 * Capability ID, Next Capability Poपूर्णांकer and
		 * Capabilities रेजिस्टर are all पढ़ो-only.
		 */
		.ro = ~0,
	पूर्ण,

	[PCI_EXP_DEVCAP / 4] = अणु
		.ro = ~0,
	पूर्ण,

	[PCI_EXP_DEVCTL / 4] = अणु
		/* Device control रेजिस्टर is RW */
		.rw = GENMASK(15, 0),

		/*
		 * Device status रेजिस्टर has bits 6 and [3:0] W1C, [5:4] RO,
		 * the rest is reserved
		 */
		.w1c = (BIT(6) | GENMASK(3, 0)) << 16,
		.ro = GENMASK(5, 4) << 16,
	पूर्ण,

	[PCI_EXP_LNKCAP / 4] = अणु
		/* All bits are RO, except bit 23 which is reserved */
		.ro = lower_32_bits(~BIT(23)),
	पूर्ण,

	[PCI_EXP_LNKCTL / 4] = अणु
		/*
		 * Link control has bits [15:14], [11:3] and [1:0] RW, the
		 * rest is reserved.
		 *
		 * Link status has bits [13:0] RO, and bits [15:14]
		 * W1C.
		 */
		.rw = GENMASK(15, 14) | GENMASK(11, 3) | GENMASK(1, 0),
		.ro = GENMASK(13, 0) << 16,
		.w1c = GENMASK(15, 14) << 16,
	पूर्ण,

	[PCI_EXP_SLTCAP / 4] = अणु
		.ro = ~0,
	पूर्ण,

	[PCI_EXP_SLTCTL / 4] = अणु
		/*
		 * Slot control has bits [14:0] RW, the rest is
		 * reserved.
		 *
		 * Slot status has bits 8 and [4:0] W1C, bits [7:5] RO, the
		 * rest is reserved.
		 */
		.rw = GENMASK(14, 0),
		.w1c = (PCI_EXP_SLTSTA_ABP | PCI_EXP_SLTSTA_PFD |
			PCI_EXP_SLTSTA_MRLSC | PCI_EXP_SLTSTA_PDC |
			PCI_EXP_SLTSTA_CC | PCI_EXP_SLTSTA_DLLSC) << 16,
		.ro = (PCI_EXP_SLTSTA_MRLSS | PCI_EXP_SLTSTA_PDS |
		       PCI_EXP_SLTSTA_EIS) << 16,
	पूर्ण,

	[PCI_EXP_RTCTL / 4] = अणु
		/*
		 * Root control has bits [4:0] RW, the rest is
		 * reserved.
		 *
		 * Root capabilities has bit 0 RO, the rest is reserved.
		 */
		.rw = (PCI_EXP_RTCTL_SECEE | PCI_EXP_RTCTL_SENFEE |
		       PCI_EXP_RTCTL_SEFEE | PCI_EXP_RTCTL_PMEIE |
		       PCI_EXP_RTCTL_CRSSVE),
		.ro = PCI_EXP_RTCAP_CRSVIS << 16,
	पूर्ण,

	[PCI_EXP_RTSTA / 4] = अणु
		/*
		 * Root status has bits 17 and [15:0] RO, bit 16 W1C, the rest
		 * is reserved.
		 */
		.ro = GENMASK(15, 0) | PCI_EXP_RTSTA_PENDING,
		.w1c = PCI_EXP_RTSTA_PME,
	पूर्ण,
पूर्ण;

/*
 * Initialize a pci_bridge_emul काष्ठाure to represent a fake PCI
 * bridge configuration space. The caller needs to have initialized
 * the PCI configuration space with whatever values make sense
 * (typically at least venकरोr, device, revision), the ->ops poपूर्णांकer,
 * and optionally ->data and ->has_pcie.
 */
पूर्णांक pci_bridge_emul_init(काष्ठा pci_bridge_emul *bridge,
			 अचिन्हित पूर्णांक flags)
अणु
	BUILD_BUG_ON(माप(bridge->conf) != PCI_BRIDGE_CONF_END);

	bridge->conf.class_revision |= cpu_to_le32(PCI_CLASS_BRIDGE_PCI << 16);
	bridge->conf.header_type = PCI_HEADER_TYPE_BRIDGE;
	bridge->conf.cache_line_size = 0x10;
	bridge->conf.status = cpu_to_le16(PCI_STATUS_CAP_LIST);
	bridge->pci_regs_behavior = kmemdup(pci_regs_behavior,
					    माप(pci_regs_behavior),
					    GFP_KERNEL);
	अगर (!bridge->pci_regs_behavior)
		वापस -ENOMEM;

	अगर (bridge->has_pcie) अणु
		bridge->conf.capabilities_poपूर्णांकer = PCI_CAP_PCIE_START;
		bridge->pcie_conf.cap_id = PCI_CAP_ID_EXP;
		/* Set PCIe v2, root port, slot support */
		bridge->pcie_conf.cap =
			cpu_to_le16(PCI_EXP_TYPE_ROOT_PORT << 4 | 2 |
				    PCI_EXP_FLAGS_SLOT);
		bridge->pcie_cap_regs_behavior =
			kmemdup(pcie_cap_regs_behavior,
				माप(pcie_cap_regs_behavior),
				GFP_KERNEL);
		अगर (!bridge->pcie_cap_regs_behavior) अणु
			kमुक्त(bridge->pci_regs_behavior);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (flags & PCI_BRIDGE_EMUL_NO_PREFETCHABLE_BAR) अणु
		bridge->pci_regs_behavior[PCI_PREF_MEMORY_BASE / 4].ro = ~0;
		bridge->pci_regs_behavior[PCI_PREF_MEMORY_BASE / 4].rw = 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_bridge_emul_init);

/*
 * Cleanup a pci_bridge_emul काष्ठाure that was previously initialized
 * using pci_bridge_emul_init().
 */
व्योम pci_bridge_emul_cleanup(काष्ठा pci_bridge_emul *bridge)
अणु
	अगर (bridge->has_pcie)
		kमुक्त(bridge->pcie_cap_regs_behavior);
	kमुक्त(bridge->pci_regs_behavior);
पूर्ण
EXPORT_SYMBOL_GPL(pci_bridge_emul_cleanup);

/*
 * Should be called by the PCI controller driver when पढ़ोing the PCI
 * configuration space of the fake bridge. It will call back the
 * ->ops->पढ़ो_base or ->ops->पढ़ो_pcie operations.
 */
पूर्णांक pci_bridge_emul_conf_पढ़ो(काष्ठा pci_bridge_emul *bridge, पूर्णांक where,
			      पूर्णांक size, u32 *value)
अणु
	पूर्णांक ret;
	पूर्णांक reg = where & ~3;
	pci_bridge_emul_पढ़ो_status_t (*पढ़ो_op)(काष्ठा pci_bridge_emul *bridge,
						 पूर्णांक reg, u32 *value);
	__le32 *cfgspace;
	स्थिर काष्ठा pci_bridge_reg_behavior *behavior;

	अगर (bridge->has_pcie && reg >= PCI_CAP_PCIE_END) अणु
		*value = 0;
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	अगर (!bridge->has_pcie && reg >= PCI_BRIDGE_CONF_END) अणु
		*value = 0;
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	अगर (bridge->has_pcie && reg >= PCI_CAP_PCIE_START) अणु
		reg -= PCI_CAP_PCIE_START;
		पढ़ो_op = bridge->ops->पढ़ो_pcie;
		cfgspace = (__le32 *) &bridge->pcie_conf;
		behavior = bridge->pcie_cap_regs_behavior;
	पूर्ण अन्यथा अणु
		पढ़ो_op = bridge->ops->पढ़ो_base;
		cfgspace = (__le32 *) &bridge->conf;
		behavior = bridge->pci_regs_behavior;
	पूर्ण

	अगर (पढ़ो_op)
		ret = पढ़ो_op(bridge, reg, value);
	अन्यथा
		ret = PCI_BRIDGE_EMUL_NOT_HANDLED;

	अगर (ret == PCI_BRIDGE_EMUL_NOT_HANDLED)
		*value = le32_to_cpu(cfgspace[reg / 4]);

	/*
	 * Make sure we never वापस any reserved bit with a value
	 * dअगरferent from 0.
	 */
	*value &= behavior[reg / 4].ro | behavior[reg / 4].rw |
		  behavior[reg / 4].w1c;

	अगर (size == 1)
		*value = (*value >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*value = (*value >> (8 * (where & 3))) & 0xffff;
	अन्यथा अगर (size != 4)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_bridge_emul_conf_पढ़ो);

/*
 * Should be called by the PCI controller driver when writing the PCI
 * configuration space of the fake bridge. It will call back the
 * ->ops->ग_लिखो_base or ->ops->ग_लिखो_pcie operations.
 */
पूर्णांक pci_bridge_emul_conf_ग_लिखो(काष्ठा pci_bridge_emul *bridge, पूर्णांक where,
			       पूर्णांक size, u32 value)
अणु
	पूर्णांक reg = where & ~3;
	पूर्णांक mask, ret, old, new, shअगरt;
	व्योम (*ग_लिखो_op)(काष्ठा pci_bridge_emul *bridge, पूर्णांक reg,
			 u32 old, u32 new, u32 mask);
	__le32 *cfgspace;
	स्थिर काष्ठा pci_bridge_reg_behavior *behavior;

	अगर (bridge->has_pcie && reg >= PCI_CAP_PCIE_END)
		वापस PCIBIOS_SUCCESSFUL;

	अगर (!bridge->has_pcie && reg >= PCI_BRIDGE_CONF_END)
		वापस PCIBIOS_SUCCESSFUL;

	shअगरt = (where & 0x3) * 8;

	अगर (size == 4)
		mask = 0xffffffff;
	अन्यथा अगर (size == 2)
		mask = 0xffff << shअगरt;
	अन्यथा अगर (size == 1)
		mask = 0xff << shअगरt;
	अन्यथा
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	ret = pci_bridge_emul_conf_पढ़ो(bridge, reg, 4, &old);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	अगर (bridge->has_pcie && reg >= PCI_CAP_PCIE_START) अणु
		reg -= PCI_CAP_PCIE_START;
		ग_लिखो_op = bridge->ops->ग_लिखो_pcie;
		cfgspace = (__le32 *) &bridge->pcie_conf;
		behavior = bridge->pcie_cap_regs_behavior;
	पूर्ण अन्यथा अणु
		ग_लिखो_op = bridge->ops->ग_लिखो_base;
		cfgspace = (__le32 *) &bridge->conf;
		behavior = bridge->pci_regs_behavior;
	पूर्ण

	/* Keep all bits, except the RW bits */
	new = old & (~mask | ~behavior[reg / 4].rw);

	/* Update the value of the RW bits */
	new |= (value << shअगरt) & (behavior[reg / 4].rw & mask);

	/* Clear the W1C bits */
	new &= ~((value << shअगरt) & (behavior[reg / 4].w1c & mask));

	cfgspace[reg / 4] = cpu_to_le32(new);

	अगर (ग_लिखो_op)
		ग_लिखो_op(bridge, reg, old, new, mask);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_bridge_emul_conf_ग_लिखो);
