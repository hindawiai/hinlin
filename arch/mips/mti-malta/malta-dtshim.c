<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/malta.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/page.h>

#घोषणा ROCIT_REG_BASE			0x1f403000
#घोषणा ROCIT_CONFIG_GEN1		(ROCIT_REG_BASE + 0x04)
#घोषणा  ROCIT_CONFIG_GEN1_MEMMAP_SHIFT	8
#घोषणा  ROCIT_CONFIG_GEN1_MEMMAP_MASK	(0xf << 8)

अटल अचिन्हित अक्षर fdt_buf[16 << 10] __initdata;

/* determined physical memory size, not overridden by command line args	 */
बाह्य अचिन्हित दीर्घ physical_memsize;

क्रमागत mem_map अणु
	MEM_MAP_V1 = 0,
	MEM_MAP_V2,
पूर्ण;

#घोषणा MAX_MEM_ARRAY_ENTRIES 2

अटल __init पूर्णांक malta_scon(व्योम)
अणु
	पूर्णांक scon = MIPS_REVISION_SCONID;

	अगर (scon != MIPS_REVISION_SCON_OTHER)
		वापस scon;

	चयन (MIPS_REVISION_CORID) अणु
	हाल MIPS_REVISION_CORID_QED_RM5261:
	हाल MIPS_REVISION_CORID_CORE_LV:
	हाल MIPS_REVISION_CORID_CORE_FPGA:
	हाल MIPS_REVISION_CORID_CORE_FPGAR2:
		वापस MIPS_REVISION_SCON_GT64120;

	हाल MIPS_REVISION_CORID_CORE_EMUL_BON:
	हाल MIPS_REVISION_CORID_BONITO64:
	हाल MIPS_REVISION_CORID_CORE_20K:
		वापस MIPS_REVISION_SCON_BONITO;

	हाल MIPS_REVISION_CORID_CORE_MSC:
	हाल MIPS_REVISION_CORID_CORE_FPGA2:
	हाल MIPS_REVISION_CORID_CORE_24K:
		वापस MIPS_REVISION_SCON_SOCIT;

	हाल MIPS_REVISION_CORID_CORE_FPGA3:
	हाल MIPS_REVISION_CORID_CORE_FPGA4:
	हाल MIPS_REVISION_CORID_CORE_FPGA5:
	हाल MIPS_REVISION_CORID_CORE_EMUL_MSC:
	शेष:
		वापस MIPS_REVISION_SCON_ROCIT;
	पूर्ण
पूर्ण

अटल अचिन्हित __init gen_fdt_mem_array(__be32 *mem_array, अचिन्हित दीर्घ size,
					 क्रमागत mem_map map)
अणु
	अचिन्हित दीर्घ size_preio;
	अचिन्हित entries;

	entries = 1;
	mem_array[0] = cpu_to_be32(PHYS_OFFSET);
	अगर (IS_ENABLED(CONFIG_EVA)) अणु
		/*
		 * The current Malta EVA configuration is "special" in that it
		 * always makes use of addresses in the upper half of the 32 bit
		 * physical address map, which gives it a contiguous region of
		 * DDR but limits it to 2GB.
		 */
		mem_array[1] = cpu_to_be32(size);
		जाओ करोne;
	पूर्ण

	size_preio = min_t(अचिन्हित दीर्घ, size, SZ_256M);
	mem_array[1] = cpu_to_be32(size_preio);
	size -= size_preio;
	अगर (!size)
		जाओ करोne;

	अगर (map == MEM_MAP_V2) अणु
		/*
		 * We have a flat 32 bit physical memory map with DDR filling
		 * all 4GB of the memory map, apart from the I/O region which
		 * obscures 256MB from 0x10000000-0x1fffffff.
		 *
		 * Thereक्रमe we discard the 256MB behind the I/O region.
		 */
		अगर (size <= SZ_256M)
			जाओ करोne;
		size -= SZ_256M;

		/* Make use of the memory following the I/O region */
		entries++;
		mem_array[2] = cpu_to_be32(PHYS_OFFSET + SZ_512M);
		mem_array[3] = cpu_to_be32(size);
	पूर्ण अन्यथा अणु
		/*
		 * We have a 32 bit physical memory map with a 2GB DDR region
		 * aliased in the upper & lower halves of it. The I/O region
		 * obscures 256MB from 0x10000000-0x1fffffff in the low alias
		 * but the DDR it obscures is accessible via the high alias.
		 *
		 * Simply access everything beyond the lowest 256MB of DDR using
		 * the high alias.
		 */
		entries++;
		mem_array[2] = cpu_to_be32(PHYS_OFFSET + SZ_2G + SZ_256M);
		mem_array[3] = cpu_to_be32(size);
	पूर्ण

करोne:
	BUG_ON(entries > MAX_MEM_ARRAY_ENTRIES);
	वापस entries;
पूर्ण

अटल व्योम __init append_memory(व्योम *fdt, पूर्णांक root_off)
अणु
	__be32 mem_array[2 * MAX_MEM_ARRAY_ENTRIES];
	अचिन्हित दीर्घ memsize;
	अचिन्हित mem_entries;
	पूर्णांक i, err, mem_off;
	क्रमागत mem_map mem_map;
	u32 config;
	अक्षर *var, param_name[10], *var_names[] = अणु
		"ememsize", "memsize",
	पूर्ण;

	/* अगर a memory node alपढ़ोy exists, leave it alone */
	mem_off = fdt_path_offset(fdt, "/memory");
	अगर (mem_off >= 0)
		वापस;

	/* find memory size from the bootloader environment */
	क्रम (i = 0; i < ARRAY_SIZE(var_names); i++) अणु
		var = fw_दो_पर्या(var_names[i]);
		अगर (!var)
			जारी;

		err = kम_से_अदीर्घ(var, 0, &physical_memsize);
		अगर (!err)
			अवरोध;

		pr_warn("Failed to read the '%s' env variable '%s'\n",
			var_names[i], var);
	पूर्ण

	अगर (!physical_memsize) अणु
		pr_warn("The bootloader didn't provide memsize: defaulting to 32MB\n");
		physical_memsize = 32 << 20;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)) अणु
		/*
		 * SOC-it swaps, or perhaps करोesn't swap, when DMA'ing
		 * the last word of physical memory.
		 */
		physical_memsize -= PAGE_SIZE;
	पूर्ण

	/* शेष to using all available RAM */
	memsize = physical_memsize;

	/* allow the user to override the usable memory */
	क्रम (i = 0; i < ARRAY_SIZE(var_names); i++) अणु
		snम_लिखो(param_name, माप(param_name), "%s=", var_names[i]);
		var = म_माला(arcs_cmdline, param_name);
		अगर (!var)
			जारी;

		memsize = memparse(var + म_माप(param_name), शून्य);
	पूर्ण

	/* अगर the user says there's more RAM than we thought, believe them */
	physical_memsize = max_t(अचिन्हित दीर्घ, physical_memsize, memsize);

	/* detect the memory map in use */
	अगर (malta_scon() == MIPS_REVISION_SCON_ROCIT) अणु
		/* ROCit has a रेजिस्टर indicating the memory map in use */
		config = पढ़ोl((व्योम __iomem *)CKSEG1ADDR(ROCIT_CONFIG_GEN1));
		mem_map = config & ROCIT_CONFIG_GEN1_MEMMAP_MASK;
		mem_map >>= ROCIT_CONFIG_GEN1_MEMMAP_SHIFT;
	पूर्ण अन्यथा अणु
		/* अगर not using ROCit, presume the v1 memory map */
		mem_map = MEM_MAP_V1;
	पूर्ण
	अगर (mem_map > MEM_MAP_V2)
		panic("Unsupported physical memory map v%u detected",
		      (अचिन्हित पूर्णांक)mem_map);

	/* append memory to the DT */
	mem_off = fdt_add_subnode(fdt, root_off, "memory");
	अगर (mem_off < 0)
		panic("Unable to add memory node to DT: %d", mem_off);

	err = fdt_setprop_string(fdt, mem_off, "device_type", "memory");
	अगर (err)
		panic("Unable to set memory node device_type: %d", err);

	mem_entries = gen_fdt_mem_array(mem_array, physical_memsize, mem_map);
	err = fdt_setprop(fdt, mem_off, "reg", mem_array,
			  mem_entries * 2 * माप(mem_array[0]));
	अगर (err)
		panic("Unable to set memory regs property: %d", err);

	mem_entries = gen_fdt_mem_array(mem_array, memsize, mem_map);
	err = fdt_setprop(fdt, mem_off, "linux,usable-memory", mem_array,
			  mem_entries * 2 * माप(mem_array[0]));
	अगर (err)
		panic("Unable to set linux,usable-memory property: %d", err);
पूर्ण

अटल व्योम __init हटाओ_gic(व्योम *fdt)
अणु
	पूर्णांक err, gic_off, i8259_off, cpu_off;
	व्योम __iomem *biu_base;
	uपूर्णांक32_t cpu_phandle, sc_cfg;

	/* अगर we have a CM which reports a GIC is present, leave the DT alone */
	err = mips_cm_probe();
	अगर (!err && (पढ़ो_gcr_gic_status() & CM_GCR_GIC_STATUS_EX))
		वापस;

	अगर (malta_scon() == MIPS_REVISION_SCON_ROCIT) अणु
		/*
		 * On प्रणालीs using the RocIT प्रणाली controller a GIC may be
		 * present without a CM. Detect whether that is the हाल.
		 */
		biu_base = ioremap(MSC01_BIU_REG_BASE,
				MSC01_BIU_ADDRSPACE_SZ);
		sc_cfg = __raw_पढ़ोl(biu_base + MSC01_SC_CFG_OFS);
		अगर (sc_cfg & MSC01_SC_CFG_GICPRES_MSK) अणु
			/* enable the GIC at the प्रणाली controller level */
			sc_cfg |= BIT(MSC01_SC_CFG_GICENA_SHF);
			__raw_ग_लिखोl(sc_cfg, biu_base + MSC01_SC_CFG_OFS);
			वापस;
		पूर्ण
	पूर्ण

	gic_off = fdt_node_offset_by_compatible(fdt, -1, "mti,gic");
	अगर (gic_off < 0) अणु
		pr_warn("malta-dtshim: unable to find DT GIC node: %d\n",
			gic_off);
		वापस;
	पूर्ण

	err = fdt_nop_node(fdt, gic_off);
	अगर (err)
		pr_warn("malta-dtshim: unable to nop GIC node\n");

	i8259_off = fdt_node_offset_by_compatible(fdt, -1, "intel,i8259");
	अगर (i8259_off < 0) अणु
		pr_warn("malta-dtshim: unable to find DT i8259 node: %d\n",
			i8259_off);
		वापस;
	पूर्ण

	cpu_off = fdt_node_offset_by_compatible(fdt, -1,
			"mti,cpu-interrupt-controller");
	अगर (cpu_off < 0) अणु
		pr_warn("malta-dtshim: unable to find CPU intc node: %d\n",
			cpu_off);
		वापस;
	पूर्ण

	cpu_phandle = fdt_get_phandle(fdt, cpu_off);
	अगर (!cpu_phandle) अणु
		pr_warn("malta-dtshim: unable to get CPU intc phandle\n");
		वापस;
	पूर्ण

	err = fdt_setprop_u32(fdt, i8259_off, "interrupt-parent", cpu_phandle);
	अगर (err) अणु
		pr_warn("malta-dtshim: unable to set i8259 interrupt-parent: %d\n",
			err);
		वापस;
	पूर्ण

	err = fdt_setprop_u32(fdt, i8259_off, "interrupts", 2);
	अगर (err) अणु
		pr_warn("malta-dtshim: unable to set i8259 interrupts: %d\n",
			err);
		वापस;
	पूर्ण
पूर्ण

व्योम __init *malta_dt_shim(व्योम *fdt)
अणु
	पूर्णांक root_off, len, err;
	स्थिर अक्षर *compat;

	अगर (fdt_check_header(fdt))
		panic("Corrupt DT");

	err = fdt_खोलो_पूर्णांकo(fdt, fdt_buf, माप(fdt_buf));
	अगर (err)
		panic("Unable to open FDT: %d", err);

	root_off = fdt_path_offset(fdt_buf, "/");
	अगर (root_off < 0)
		panic("No / node in DT");

	compat = fdt_getprop(fdt_buf, root_off, "compatible", &len);
	अगर (!compat)
		panic("No root compatible property in DT: %d", len);

	/* अगर this isn't Malta, leave the DT alone */
	अगर (म_भेदन(compat, "mti,malta", len))
		वापस fdt;

	append_memory(fdt_buf, root_off);
	हटाओ_gic(fdt_buf);

	err = fdt_pack(fdt_buf);
	अगर (err)
		panic("Unable to pack FDT: %d\n", err);

	वापस fdt_buf;
पूर्ण
