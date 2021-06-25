<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015, 2016 Cavium, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>

#अगर defined(CONFIG_PCI_HOST_THUNDER_ECAM) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS))

अटल व्योम set_val(u32 v, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक shअगरt = (where & 3) * 8;

	pr_debug("set_val %04x: %08x\n", (अचिन्हित)(where & ~3), v);
	v >>= shअगरt;
	अगर (size == 1)
		v &= 0xff;
	अन्यथा अगर (size == 2)
		v &= 0xffff;
	*val = v;
पूर्ण

अटल पूर्णांक handle_ea_bar(u32 e0, पूर्णांक bar, काष्ठा pci_bus *bus,
			 अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;
	u32 v;

	/* Entries are 16-byte aligned; bits[2,3] select word in entry */
	पूर्णांक where_a = where & 0xc;

	अगर (where_a == 0) अणु
		set_val(e0, where, size, val);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण
	अगर (where_a == 0x4) अणु
		addr = bus->ops->map_bus(bus, devfn, bar); /* BAR 0 */
		अगर (!addr) अणु
			*val = ~0;
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		पूर्ण
		v = पढ़ोl(addr);
		v &= ~0xf;
		v |= 2; /* EA entry-1. Base-L */
		set_val(v, where, size, val);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण
	अगर (where_a == 0x8) अणु
		u32 barl_orig;
		u32 barl_rb;

		addr = bus->ops->map_bus(bus, devfn, bar); /* BAR 0 */
		अगर (!addr) अणु
			*val = ~0;
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		पूर्ण
		barl_orig = पढ़ोl(addr + 0);
		ग_लिखोl(0xffffffff, addr + 0);
		barl_rb = पढ़ोl(addr + 0);
		ग_लिखोl(barl_orig, addr + 0);
		/* zeros in unsettable bits */
		v = ~barl_rb & ~3;
		v |= 0xc; /* EA entry-2. Offset-L */
		set_val(v, where, size, val);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण
	अगर (where_a == 0xc) अणु
		addr = bus->ops->map_bus(bus, devfn, bar + 4); /* BAR 1 */
		अगर (!addr) अणु
			*val = ~0;
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		पूर्ण
		v = पढ़ोl(addr); /* EA entry-3. Base-H */
		set_val(v, where, size, val);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण
	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल पूर्णांक thunder_ecam_p2_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	पूर्णांक where_a = where & ~3;
	व्योम __iomem *addr;
	u32 node_bits;
	u32 v;

	/* EA Base[63:32] may be missing some bits ... */
	चयन (where_a) अणु
	हाल 0xa8:
	हाल 0xbc:
	हाल 0xd0:
	हाल 0xe4:
		अवरोध;
	शेष:
		वापस pci_generic_config_पढ़ो(bus, devfn, where, size, val);
	पूर्ण

	addr = bus->ops->map_bus(bus, devfn, where_a);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	v = पढ़ोl(addr);

	/*
	 * Bit 44 of the 64-bit Base must match the same bit in
	 * the config space access winकरोw.  Since we are working with
	 * the high-order 32 bits, shअगरt everything करोwn by 32 bits.
	 */
	node_bits = upper_32_bits(cfg->res.start) & (1 << 12);

	v |= node_bits;
	set_val(v, where, size, val);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक thunder_ecam_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 v;
	u32 venकरोr_device;
	u32 class_rev;
	व्योम __iomem *addr;
	पूर्णांक cfg_type;
	पूर्णांक where_a = where & ~3;

	addr = bus->ops->map_bus(bus, devfn, 0xc);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	v = पढ़ोl(addr);

	/* Check क्रम non type-00 header */
	cfg_type = (v >> 16) & 0x7f;

	addr = bus->ops->map_bus(bus, devfn, 8);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	class_rev = पढ़ोl(addr);
	अगर (class_rev == 0xffffffff)
		जाओ no_emulation;

	अगर ((class_rev & 0xff) >= 8) अणु
		/* Pass-2 handling */
		अगर (cfg_type)
			जाओ no_emulation;
		वापस thunder_ecam_p2_config_पढ़ो(bus, devfn, where,
						   size, val);
	पूर्ण

	/*
	 * All BARs have fixed addresses specअगरied by the EA
	 * capability; they must वापस zero on पढ़ो.
	 */
	अगर (cfg_type == 0 &&
	    ((where >= 0x10 && where < 0x2c) ||
	     (where >= 0x1a4 && where < 0x1bc))) अणु
		/* BAR or SR-IOV BAR */
		*val = 0;
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	addr = bus->ops->map_bus(bus, devfn, 0);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	venकरोr_device = पढ़ोl(addr);
	अगर (venकरोr_device == 0xffffffff)
		जाओ no_emulation;

	pr_debug("%04x:%04x - Fix pass#: %08x, where: %03x, devfn: %03x\n",
		 venकरोr_device & 0xffff, venकरोr_device >> 16, class_rev,
		 (अचिन्हित) where, devfn);

	/* Check क्रम non type-00 header */
	अगर (cfg_type == 0) अणु
		bool has_msix;
		bool is_nic = (venकरोr_device == 0xa01e177d);
		bool is_tns = (venकरोr_device == 0xa01f177d);

		addr = bus->ops->map_bus(bus, devfn, 0x70);
		अगर (!addr) अणु
			*val = ~0;
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		पूर्ण
		/* E_CAP */
		v = पढ़ोl(addr);
		has_msix = (v & 0xff00) != 0;

		अगर (!has_msix && where_a == 0x70) अणु
			v |= 0xbc00; /* next capability is EA at 0xbc */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xb0) अणु
			addr = bus->ops->map_bus(bus, devfn, where_a);
			अगर (!addr) अणु
				*val = ~0;
				वापस PCIBIOS_DEVICE_NOT_FOUND;
			पूर्ण
			v = पढ़ोl(addr);
			अगर (v & 0xff00)
				pr_err("Bad MSIX cap header: %08x\n", v);
			v |= 0xbc00; /* next capability is EA at 0xbc */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xbc) अणु
			अगर (is_nic)
				v = 0x40014; /* EA last in chain, 4 entries */
			अन्यथा अगर (is_tns)
				v = 0x30014; /* EA last in chain, 3 entries */
			अन्यथा अगर (has_msix)
				v = 0x20014; /* EA last in chain, 2 entries */
			अन्यथा
				v = 0x10014; /* EA last in chain, 1 entry */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a >= 0xc0 && where_a < 0xd0)
			/* EA entry-0. PP=0, BAR0 Size:3 */
			वापस handle_ea_bar(0x80ff0003,
					     0x10, bus, devfn, where,
					     size, val);
		अगर (where_a >= 0xd0 && where_a < 0xe0 && has_msix)
			 /* EA entry-1. PP=0, BAR4 Size:3 */
			वापस handle_ea_bar(0x80ff0043,
					     0x20, bus, devfn, where,
					     size, val);
		अगर (where_a >= 0xe0 && where_a < 0xf0 && is_tns)
			/* EA entry-2. PP=0, BAR2, Size:3 */
			वापस handle_ea_bar(0x80ff0023,
					     0x18, bus, devfn, where,
					     size, val);
		अगर (where_a >= 0xe0 && where_a < 0xf0 && is_nic)
			/* EA entry-2. PP=4, VF_BAR0 (9), Size:3 */
			वापस handle_ea_bar(0x80ff0493,
					     0x1a4, bus, devfn, where,
					     size, val);
		अगर (where_a >= 0xf0 && where_a < 0x100 && is_nic)
			/* EA entry-3. PP=4, VF_BAR4 (d), Size:3 */
			वापस handle_ea_bar(0x80ff04d3,
					     0x1b4, bus, devfn, where,
					     size, val);
	पूर्ण अन्यथा अगर (cfg_type == 1) अणु
		bool is_rsl_bridge = devfn == 0x08;
		bool is_rad_bridge = devfn == 0xa0;
		bool is_zip_bridge = devfn == 0xa8;
		bool is_dfa_bridge = devfn == 0xb0;
		bool is_nic_bridge = devfn == 0x10;

		अगर (where_a == 0x70) अणु
			addr = bus->ops->map_bus(bus, devfn, where_a);
			अगर (!addr) अणु
				*val = ~0;
				वापस PCIBIOS_DEVICE_NOT_FOUND;
			पूर्ण
			v = पढ़ोl(addr);
			अगर (v & 0xff00)
				pr_err("Bad PCIe cap header: %08x\n", v);
			v |= 0xbc00; /* next capability is EA at 0xbc */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xbc) अणु
			अगर (is_nic_bridge)
				v = 0x10014; /* EA last in chain, 1 entry */
			अन्यथा
				v = 0x00014; /* EA last in chain, no entries */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xc0) अणु
			अगर (is_rsl_bridge || is_nic_bridge)
				v = 0x0101; /* subordinate:secondary = 1:1 */
			अन्यथा अगर (is_rad_bridge)
				v = 0x0202; /* subordinate:secondary = 2:2 */
			अन्यथा अगर (is_zip_bridge)
				v = 0x0303; /* subordinate:secondary = 3:3 */
			अन्यथा अगर (is_dfa_bridge)
				v = 0x0404; /* subordinate:secondary = 4:4 */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xc4 && is_nic_bridge) अणु
			/* Enabled, not-Write, SP=ff, PP=05, BEI=6, ES=4 */
			v = 0x80ff0564;
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xc8 && is_nic_bridge) अणु
			v = 0x00000002; /* Base-L 64-bit */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xcc && is_nic_bridge) अणु
			v = 0xfffffffe; /* MaxOffset-L 64-bit */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xd0 && is_nic_bridge) अणु
			v = 0x00008430; /* NIC Base-H */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		अगर (where_a == 0xd4 && is_nic_bridge) अणु
			v = 0x0000000f; /* MaxOffset-H */
			set_val(v, where, size, val);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
	पूर्ण
no_emulation:
	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, val);
पूर्ण

अटल पूर्णांक thunder_ecam_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	/*
	 * All BARs have fixed addresses; ignore BAR ग_लिखोs so they
	 * करोn't get corrupted.
	 */
	अगर ((where >= 0x10 && where < 0x2c) ||
	    (where >= 0x1a4 && where < 0x1bc))
		/* BAR or SR-IOV BAR */
		वापस PCIBIOS_SUCCESSFUL;

	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, val);
पूर्ण

स्थिर काष्ठा pci_ecam_ops pci_thunder_ecam_ops = अणु
	.pci_ops	= अणु
		.map_bus        = pci_ecam_map_bus,
		.पढ़ो           = thunder_ecam_config_पढ़ो,
		.ग_लिखो          = thunder_ecam_config_ग_लिखो,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PCI_HOST_THUNDER_ECAM

अटल स्थिर काष्ठा of_device_id thunder_ecam_of_match[] = अणु
	अणु
		.compatible = "cavium,pci-host-thunder-ecam",
		.data = &pci_thunder_ecam_ops,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver thunder_ecam_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = thunder_ecam_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = pci_host_common_probe,
पूर्ण;
builtin_platक्रमm_driver(thunder_ecam_driver);

#पूर्ण_अगर
#पूर्ण_अगर
