<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Based on Ocelot Linux port, which is
 * Copyright 2001 MontaVista Software Inc.
 * Author: jsun@mvista.com or jsun@junsun.net
 *
 * Copyright 2003 ICT CAS
 * Author: Michael Guo <guoyi@ict.ac.cn>
 *
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */
#समावेश <linux/export.h>
#समावेश <linux/pci_ids.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <loongson.h>
#समावेश <boot_param.h>
#समावेश <builtin_dtbs.h>
#समावेश <workarounds.h>

#घोषणा HOST_BRIDGE_CONFIG_ADDR	((व्योम __iomem *)TO_UNCAC(0x1a000000))

u32 cpu_घड़ी_freq;
EXPORT_SYMBOL(cpu_घड़ी_freq);
काष्ठा efi_memory_map_loongson *loongson_memmap;
काष्ठा loongson_प्रणाली_configuration loongson_sysconf;

काष्ठा board_devices *eboard;
काष्ठा पूर्णांकerface_info *eपूर्णांकer;
काष्ठा loongson_special_attribute *especial;

u64 loongson_chipcfg[MAX_PACKAGES] = अणु0xffffffffbfc00180पूर्ण;
u64 loongson_chiptemp[MAX_PACKAGES];
u64 loongson_freqctrl[MAX_PACKAGES];

अचिन्हित दीर्घ दीर्घ smp_group[4];

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "Generic Loongson64 System";
पूर्ण


व्योम __init prom_dtb_init_env(व्योम)
अणु
	अगर ((fw_arg2 < CKSEG0 || fw_arg2 > CKSEG1)
		&& (fw_arg2 < XKPHYS || fw_arg2 > XKSEG))

		loongson_fdt_blob = __dtb_loongson64_2core_2k1000_begin;
	अन्यथा
		loongson_fdt_blob = (व्योम *)fw_arg2;
पूर्ण

व्योम __init prom_lefi_init_env(व्योम)
अणु
	काष्ठा boot_params *boot_p;
	काष्ठा loongson_params *loongson_p;
	काष्ठा प्रणाली_loongson *esys;
	काष्ठा efi_cpuinfo_loongson *ecpu;
	काष्ठा irq_source_routing_table *eirq_source;
	u32 id;
	u16 venकरोr, device;

	/* firmware arguments are initialized in head.S */
	boot_p = (काष्ठा boot_params *)fw_arg2;
	loongson_p = &(boot_p->efi.smbios.lp);

	esys = (काष्ठा प्रणाली_loongson *)
		((u64)loongson_p + loongson_p->प्रणाली_offset);
	ecpu = (काष्ठा efi_cpuinfo_loongson *)
		((u64)loongson_p + loongson_p->cpu_offset);
	eboard = (काष्ठा board_devices *)
		((u64)loongson_p + loongson_p->boarddev_table_offset);
	eपूर्णांकer = (काष्ठा पूर्णांकerface_info *)
		((u64)loongson_p + loongson_p->पूर्णांकerface_offset);
	especial = (काष्ठा loongson_special_attribute *)
		((u64)loongson_p + loongson_p->special_offset);
	eirq_source = (काष्ठा irq_source_routing_table *)
		((u64)loongson_p + loongson_p->irq_offset);
	loongson_memmap = (काष्ठा efi_memory_map_loongson *)
		((u64)loongson_p + loongson_p->memory_offset);

	cpu_घड़ी_freq = ecpu->cpu_घड़ी_freq;
	loongson_sysconf.cputype = ecpu->cputype;
	चयन (ecpu->cputype) अणु
	हाल Legacy_3A:
	हाल Loongson_3A:
		loongson_sysconf.cores_per_node = 4;
		loongson_sysconf.cores_per_package = 4;
		smp_group[0] = 0x900000003ff01000;
		smp_group[1] = 0x900010003ff01000;
		smp_group[2] = 0x900020003ff01000;
		smp_group[3] = 0x900030003ff01000;
		loongson_chipcfg[0] = 0x900000001fe00180;
		loongson_chipcfg[1] = 0x900010001fe00180;
		loongson_chipcfg[2] = 0x900020001fe00180;
		loongson_chipcfg[3] = 0x900030001fe00180;
		loongson_chiptemp[0] = 0x900000001fe0019c;
		loongson_chiptemp[1] = 0x900010001fe0019c;
		loongson_chiptemp[2] = 0x900020001fe0019c;
		loongson_chiptemp[3] = 0x900030001fe0019c;
		loongson_freqctrl[0] = 0x900000001fe001d0;
		loongson_freqctrl[1] = 0x900010001fe001d0;
		loongson_freqctrl[2] = 0x900020001fe001d0;
		loongson_freqctrl[3] = 0x900030001fe001d0;
		loongson_sysconf.workarounds = WORKAROUND_CPUFREQ;
		अवरोध;
	हाल Legacy_3B:
	हाल Loongson_3B:
		loongson_sysconf.cores_per_node = 4; /* One chip has 2 nodes */
		loongson_sysconf.cores_per_package = 8;
		smp_group[0] = 0x900000003ff01000;
		smp_group[1] = 0x900010003ff05000;
		smp_group[2] = 0x900020003ff09000;
		smp_group[3] = 0x900030003ff0d000;
		loongson_chipcfg[0] = 0x900000001fe00180;
		loongson_chipcfg[1] = 0x900020001fe00180;
		loongson_chipcfg[2] = 0x900040001fe00180;
		loongson_chipcfg[3] = 0x900060001fe00180;
		loongson_chiptemp[0] = 0x900000001fe0019c;
		loongson_chiptemp[1] = 0x900020001fe0019c;
		loongson_chiptemp[2] = 0x900040001fe0019c;
		loongson_chiptemp[3] = 0x900060001fe0019c;
		loongson_freqctrl[0] = 0x900000001fe001d0;
		loongson_freqctrl[1] = 0x900020001fe001d0;
		loongson_freqctrl[2] = 0x900040001fe001d0;
		loongson_freqctrl[3] = 0x900060001fe001d0;
		loongson_sysconf.workarounds = WORKAROUND_CPUHOTPLUG;
		अवरोध;
	शेष:
		loongson_sysconf.cores_per_node = 1;
		loongson_sysconf.cores_per_package = 1;
		loongson_chipcfg[0] = 0x900000001fe00180;
	पूर्ण

	loongson_sysconf.nr_cpus = ecpu->nr_cpus;
	loongson_sysconf.boot_cpu_id = ecpu->cpu_startup_core_id;
	loongson_sysconf.reserved_cpus_mask = ecpu->reserved_cores_mask;
	अगर (ecpu->nr_cpus > NR_CPUS || ecpu->nr_cpus == 0)
		loongson_sysconf.nr_cpus = NR_CPUS;
	loongson_sysconf.nr_nodes = (loongson_sysconf.nr_cpus +
		loongson_sysconf.cores_per_node - 1) /
		loongson_sysconf.cores_per_node;

	loongson_sysconf.dma_mask_bits = eirq_source->dma_mask_bits;
	अगर (loongson_sysconf.dma_mask_bits < 32 ||
		loongson_sysconf.dma_mask_bits > 64)
		loongson_sysconf.dma_mask_bits = 32;

	loongson_sysconf.restart_addr = boot_p->reset_प्रणाली.ResetWarm;
	loongson_sysconf.घातeroff_addr = boot_p->reset_प्रणाली.Shutकरोwn;
	loongson_sysconf.suspend_addr = boot_p->reset_प्रणाली.DoSuspend;

	loongson_sysconf.vgabios_addr = boot_p->efi.smbios.vga_bios;
	pr_debug("Shutdown Addr: %llx, Restart Addr: %llx, VBIOS Addr: %llx\n",
		loongson_sysconf.घातeroff_addr, loongson_sysconf.restart_addr,
		loongson_sysconf.vgabios_addr);

	loongson_sysconf.workarounds |= esys->workarounds;

	pr_info("CpuClock = %u\n", cpu_घड़ी_freq);

	/* Read the ID of PCI host bridge to detect bridge type */
	id = पढ़ोl(HOST_BRIDGE_CONFIG_ADDR);
	venकरोr = id & 0xffff;
	device = (id >> 16) & 0xffff;

	चयन (venकरोr) अणु
	हाल PCI_VENDOR_ID_LOONGSON:
		pr_info("The bridge chip is LS7A\n");
		loongson_sysconf.bridgetype = LS7A;
		loongson_sysconf.early_config = ls7a_early_config;
		अवरोध;
	हाल PCI_VENDOR_ID_AMD:
	हाल PCI_VENDOR_ID_ATI:
		pr_info("The bridge chip is RS780E or SR5690\n");
		loongson_sysconf.bridgetype = RS780E;
		loongson_sysconf.early_config = rs780e_early_config;
		अवरोध;
	शेष:
		pr_info("The bridge chip is VIRTUAL\n");
		loongson_sysconf.bridgetype = VIRTUAL;
		loongson_sysconf.early_config = भव_early_config;
		loongson_fdt_blob = __dtb_loongson64v_4core_virtio_begin;
		अवरोध;
	पूर्ण

	अगर ((पढ़ो_c0_prid() & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64C) अणु
		चयन (पढ़ो_c0_prid() & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON3A_R1:
		हाल PRID_REV_LOONGSON3A_R2_0:
		हाल PRID_REV_LOONGSON3A_R2_1:
		हाल PRID_REV_LOONGSON3A_R3_0:
		हाल PRID_REV_LOONGSON3A_R3_1:
			चयन (loongson_sysconf.bridgetype) अणु
			हाल LS7A:
				loongson_fdt_blob = __dtb_loongson64c_4core_ls7a_begin;
				अवरोध;
			हाल RS780E:
				loongson_fdt_blob = __dtb_loongson64c_4core_rs780e_begin;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल PRID_REV_LOONGSON3B_R1:
		हाल PRID_REV_LOONGSON3B_R2:
			अगर (loongson_sysconf.bridgetype == RS780E)
				loongson_fdt_blob = __dtb_loongson64c_8core_rs780e_begin;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((पढ़ो_c0_prid() & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64G) अणु
		अगर (loongson_sysconf.bridgetype == LS7A)
			loongson_fdt_blob = __dtb_loongson64g_4core_ls7a_begin;
	पूर्ण

	अगर (!loongson_fdt_blob)
		pr_err("Failed to determine built-in Loongson64 dtb\n");
पूर्ण
