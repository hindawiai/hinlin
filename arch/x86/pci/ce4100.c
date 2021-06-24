<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright(c) 2010 Intel Corporation. All rights reserved.
 *
 *  Contact Inक्रमmation:
 *    Intel Corporation
 *    2200 Mission College Blvd.
 *    Santa Clara, CA  97052
 *
 * This provides access methods क्रम PCI रेजिस्टरs that mis-behave on
 * the CE4100. Each रेजिस्टर can be asचिन्हित a निजी init, पढ़ो and
 * ग_लिखो routine. The exception to this is the bridge device.  The
 * bridge device is the only device on bus zero (0) that requires any
 * fixup so it is a special हाल ATM
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ce4100.h>
#समावेश <यंत्र/pci_x86.h>

काष्ठा sim_reg अणु
	u32 value;
	u32 mask;
पूर्ण;

काष्ठा sim_dev_reg अणु
	पूर्णांक dev_func;
	पूर्णांक reg;
	व्योम (*init)(काष्ठा sim_dev_reg *reg);
	व्योम (*पढ़ो)(काष्ठा sim_dev_reg *reg, u32 *value);
	व्योम (*ग_लिखो)(काष्ठा sim_dev_reg *reg, u32 value);
	काष्ठा sim_reg sim_reg;
पूर्ण;

काष्ठा sim_reg_op अणु
	व्योम (*init)(काष्ठा sim_dev_reg *reg);
	व्योम (*पढ़ो)(काष्ठा sim_dev_reg *reg, u32 value);
	व्योम (*ग_लिखो)(काष्ठा sim_dev_reg *reg, u32 value);
पूर्ण;

#घोषणा MB (1024 * 1024)
#घोषणा KB (1024)
#घोषणा SIZE_TO_MASK(size) (~(size - 1))

#घोषणा DEFINE_REG(device, func, offset, size, init_op, पढ़ो_op, ग_लिखो_op)\
अणु PCI_DEVFN(device, func), offset, init_op, पढ़ो_op, ग_लिखो_op,\
	अणु0, SIZE_TO_MASK(size)पूर्ण पूर्ण,

/*
 * All पढ़ो/ग_लिखो functions are called with pci_config_lock held.
 */
अटल व्योम reg_init(काष्ठा sim_dev_reg *reg)
अणु
	pci_direct_conf1.पढ़ो(0, 1, reg->dev_func, reg->reg, 4,
			      &reg->sim_reg.value);
पूर्ण

अटल व्योम reg_पढ़ो(काष्ठा sim_dev_reg *reg, u32 *value)
अणु
	*value = reg->sim_reg.value;
पूर्ण

अटल व्योम reg_ग_लिखो(काष्ठा sim_dev_reg *reg, u32 value)
अणु
	reg->sim_reg.value = (value & reg->sim_reg.mask) |
		(reg->sim_reg.value & ~reg->sim_reg.mask);
पूर्ण

अटल व्योम sata_reg_init(काष्ठा sim_dev_reg *reg)
अणु
	pci_direct_conf1.पढ़ो(0, 1, PCI_DEVFN(14, 0), 0x10, 4,
			      &reg->sim_reg.value);
	reg->sim_reg.value += 0x400;
पूर्ण

अटल व्योम ehci_reg_पढ़ो(काष्ठा sim_dev_reg *reg, u32 *value)
अणु
	reg_पढ़ो(reg, value);
	अगर (*value != reg->sim_reg.mask)
		*value |= 0x100;
पूर्ण

व्योम sata_revid_init(काष्ठा sim_dev_reg *reg)
अणु
	reg->sim_reg.value = 0x01060100;
	reg->sim_reg.mask = 0;
पूर्ण

अटल व्योम sata_revid_पढ़ो(काष्ठा sim_dev_reg *reg, u32 *value)
अणु
	reg_पढ़ो(reg, value);
पूर्ण

अटल व्योम reg_noirq_पढ़ो(काष्ठा sim_dev_reg *reg, u32 *value)
अणु
	/* क्रमce पूर्णांकerrupt pin value to 0 */
	*value = reg->sim_reg.value & 0xfff00ff;
पूर्ण

अटल काष्ठा sim_dev_reg bus1_fixups[] = अणु
	DEFINE_REG(2, 0, 0x10, (16*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(2, 0, 0x14, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(2, 1, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(3, 0, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(4, 0, 0x10, (128*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(4, 1, 0x10, (128*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(6, 0, 0x10, (512*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(6, 1, 0x10, (512*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(6, 2, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(8, 0, 0x10, (1*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(8, 1, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(8, 2, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(9, 0, 0x10 , (1*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(9, 0, 0x14, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(10, 0, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(10, 0, 0x14, (256*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 0, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 0, 0x14, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 1, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 2, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 2, 0x14, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 2, 0x18, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 3, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 3, 0x14, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 4, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 5, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 6, 0x10, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 7, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(11, 7, 0x3c, 256, reg_init, reg_noirq_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(12, 0, 0x10, (128*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(12, 0, 0x14, (256), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(12, 1, 0x10, (1024), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(13, 0, 0x10, (32*KB), reg_init, ehci_reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(13, 1, 0x10, (32*KB), reg_init, ehci_reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x8,  0, sata_revid_init, sata_revid_पढ़ो, 0)
	DEFINE_REG(14, 0, 0x10, 0, reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x14, 0, reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x18, 0, reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x1C, 0, reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x20, 0, reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(14, 0, 0x24, (0x200), sata_reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(15, 0, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(15, 0, 0x14, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(16, 0, 0x10, (64*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(16, 0, 0x14, (64*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(16, 0, 0x18, (64*MB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(16, 0, 0x3c, 256, reg_init, reg_noirq_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(17, 0, 0x10, (128*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(18, 0, 0x10, (1*KB), reg_init, reg_पढ़ो, reg_ग_लिखो)
	DEFINE_REG(18, 0, 0x3c, 256, reg_init, reg_noirq_पढ़ो, reg_ग_लिखो)
पूर्ण;

अटल व्योम __init init_sim_regs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bus1_fixups); i++) अणु
		अगर (bus1_fixups[i].init)
			bus1_fixups[i].init(&bus1_fixups[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम extract_bytes(u32 *value, पूर्णांक reg, पूर्णांक len)
अणु
	uपूर्णांक32_t mask;

	*value >>= ((reg & 3) * 8);
	mask = 0xFFFFFFFF >> ((4 - len) * 8);
	*value &= mask;
पूर्ण

पूर्णांक bridge_पढ़ो(अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	u32 av_bridge_base, av_bridge_limit;
	पूर्णांक retval = 0;

	चयन (reg) अणु
	/* Make BARs appear to not request any memory. */
	हाल PCI_BASE_ADDRESS_0:
	हाल PCI_BASE_ADDRESS_0 + 1:
	हाल PCI_BASE_ADDRESS_0 + 2:
	हाल PCI_BASE_ADDRESS_0 + 3:
		*value = 0;
		अवरोध;

		/* Since subordinate bus number रेजिस्टर is hardwired
		 * to zero and पढ़ो only, so करो the simulation.
		 */
	हाल PCI_PRIMARY_BUS:
		अगर (len == 4)
			*value = 0x00010100;
		अवरोध;

	हाल PCI_SUBORDINATE_BUS:
		*value = 1;
		अवरोध;

	हाल PCI_MEMORY_BASE:
	हाल PCI_MEMORY_LIMIT:
		/* Get the A/V bridge base address. */
		pci_direct_conf1.पढ़ो(0, 0, devfn,
				PCI_BASE_ADDRESS_0, 4, &av_bridge_base);

		av_bridge_limit = av_bridge_base + (512*MB - 1);
		av_bridge_limit >>= 16;
		av_bridge_limit &= 0xFFF0;

		av_bridge_base >>= 16;
		av_bridge_base &= 0xFFF0;

		अगर (reg == PCI_MEMORY_LIMIT)
			*value = av_bridge_limit;
		अन्यथा अगर (len == 2)
			*value = av_bridge_base;
		अन्यथा
			*value = (av_bridge_limit << 16) | av_bridge_base;
		अवरोध;
		/* Make prefetchable memory limit smaller than prefetchable
		 * memory base, so not claim prefetchable memory space.
		 */
	हाल PCI_PREF_MEMORY_BASE:
		*value = 0xFFF0;
		अवरोध;
	हाल PCI_PREF_MEMORY_LIMIT:
		*value = 0x0;
		अवरोध;
		/* Make IO limit smaller than IO base, so not claim IO space. */
	हाल PCI_IO_BASE:
		*value = 0xF0;
		अवरोध;
	हाल PCI_IO_LIMIT:
		*value = 0;
		अवरोध;
	शेष:
		retval = 1;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक ce4100_bus1_पढ़ो(अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bus1_fixups); i++) अणु
		अगर (bus1_fixups[i].dev_func == devfn &&
		    bus1_fixups[i].reg == (reg & ~3) &&
		    bus1_fixups[i].पढ़ो) अणु

			raw_spin_lock_irqsave(&pci_config_lock, flags);
			bus1_fixups[i].पढ़ो(&(bus1_fixups[i]), value);
			raw_spin_unlock_irqrestore(&pci_config_lock, flags);
			extract_bytes(value, reg, len);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक ce4100_conf_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			    अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	WARN_ON(seg);

	अगर (bus == 1 && !ce4100_bus1_पढ़ो(devfn, reg, len, value))
		वापस 0;

	अगर (bus == 0 && (PCI_DEVFN(1, 0) == devfn) &&
	    !bridge_पढ़ो(devfn, reg, len, value))
		वापस 0;

	वापस pci_direct_conf1.पढ़ो(seg, bus, devfn, reg, len, value);
पूर्ण

अटल पूर्णांक ce4100_bus1_ग_लिखो(अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bus1_fixups); i++) अणु
		अगर (bus1_fixups[i].dev_func == devfn &&
		    bus1_fixups[i].reg == (reg & ~3) &&
		    bus1_fixups[i].ग_लिखो) अणु

			raw_spin_lock_irqsave(&pci_config_lock, flags);
			bus1_fixups[i].ग_लिखो(&(bus1_fixups[i]), value);
			raw_spin_unlock_irqrestore(&pci_config_lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक ce4100_conf_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			     अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	WARN_ON(seg);

	अगर (bus == 1 && !ce4100_bus1_ग_लिखो(devfn, reg, len, value))
		वापस 0;

	/* Discard ग_लिखोs to A/V bridge BAR. */
	अगर (bus == 0 && PCI_DEVFN(1, 0) == devfn &&
	    ((reg & ~3) == PCI_BASE_ADDRESS_0))
		वापस 0;

	वापस pci_direct_conf1.ग_लिखो(seg, bus, devfn, reg, len, value);
पूर्ण

अटल स्थिर काष्ठा pci_raw_ops ce4100_pci_conf = अणु
	.पढ़ो	= ce4100_conf_पढ़ो,
	.ग_लिखो	= ce4100_conf_ग_लिखो,
पूर्ण;

पूर्णांक __init ce4100_pci_init(व्योम)
अणु
	init_sim_regs();
	raw_pci_ops = &ce4100_pci_conf;
	/* Indicate caller that it should invoke pci_legacy_init() */
	वापस 1;
पूर्ण
