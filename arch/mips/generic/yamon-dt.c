<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#घोषणा pr_fmt(fmt) "yamon-dt: " fmt

#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/yamon-dt.h>

#घोषणा MAX_MEM_ARRAY_ENTRIES	2

__init पूर्णांक yamon_dt_append_cmdline(व्योम *fdt)
अणु
	पूर्णांक err, chosen_off;

	/* find or add chosen node */
	chosen_off = fdt_path_offset(fdt, "/chosen");
	अगर (chosen_off == -FDT_ERR_NOTFOUND)
		chosen_off = fdt_add_subnode(fdt, 0, "chosen");
	अगर (chosen_off < 0) अणु
		pr_err("Unable to find or add DT chosen node: %d\n",
		       chosen_off);
		वापस chosen_off;
	पूर्ण

	err = fdt_setprop_string(fdt, chosen_off, "bootargs", fw_अ_लोmdline());
	अगर (err) अणु
		pr_err("Unable to set bootargs property: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक __init gen_fdt_mem_array(
					स्थिर काष्ठा yamon_mem_region *regions,
					__be32 *mem_array,
					अचिन्हित पूर्णांक max_entries,
					अचिन्हित दीर्घ memsize)
अणु
	स्थिर काष्ठा yamon_mem_region *mr;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक entries = 0;

	क्रम (mr = regions; mr->size && memsize; ++mr) अणु
		अगर (entries >= max_entries) अणु
			pr_warn("Number of regions exceeds max %u\n",
				max_entries);
			अवरोध;
		पूर्ण

		/* How much of the reमुख्यing RAM fits in the next region? */
		size = min_t(अचिन्हित दीर्घ, memsize, mr->size);
		memsize -= size;

		/* Emit a memory region */
		*(mem_array++) = cpu_to_be32(mr->start);
		*(mem_array++) = cpu_to_be32(size);
		++entries;

		/* Discard the next mr->discard bytes */
		memsize -= min_t(अचिन्हित दीर्घ, memsize, mr->discard);
	पूर्ण
	वापस entries;
पूर्ण

__init पूर्णांक yamon_dt_append_memory(व्योम *fdt,
				  स्थिर काष्ठा yamon_mem_region *regions)
अणु
	अचिन्हित दीर्घ phys_memsize, memsize;
	__be32 mem_array[2 * MAX_MEM_ARRAY_ENTRIES];
	अचिन्हित पूर्णांक mem_entries;
	पूर्णांक i, err, mem_off;
	अक्षर *var, param_name[10], *var_names[] = अणु
		"ememsize", "memsize",
	पूर्ण;

	/* find memory size from the bootloader environment */
	क्रम (i = 0; i < ARRAY_SIZE(var_names); i++) अणु
		var = fw_दो_पर्या(var_names[i]);
		अगर (!var)
			जारी;

		err = kम_से_अदीर्घ(var, 0, &phys_memsize);
		अगर (!err)
			अवरोध;

		pr_warn("Failed to read the '%s' env variable '%s'\n",
			var_names[i], var);
	पूर्ण

	अगर (!phys_memsize) अणु
		pr_warn("The bootloader didn't provide memsize: defaulting to 32MB\n");
		phys_memsize = 32 << 20;
	पूर्ण

	/* शेष to using all available RAM */
	memsize = phys_memsize;

	/* allow the user to override the usable memory */
	क्रम (i = 0; i < ARRAY_SIZE(var_names); i++) अणु
		snम_लिखो(param_name, माप(param_name), "%s=", var_names[i]);
		var = म_माला(arcs_cmdline, param_name);
		अगर (!var)
			जारी;

		memsize = memparse(var + म_माप(param_name), शून्य);
	पूर्ण

	/* अगर the user says there's more RAM than we thought, believe them */
	phys_memsize = max_t(अचिन्हित दीर्घ, phys_memsize, memsize);

	/* find or add a memory node */
	mem_off = fdt_path_offset(fdt, "/memory");
	अगर (mem_off == -FDT_ERR_NOTFOUND)
		mem_off = fdt_add_subnode(fdt, 0, "memory");
	अगर (mem_off < 0) अणु
		pr_err("Unable to find or add memory DT node: %d\n", mem_off);
		वापस mem_off;
	पूर्ण

	err = fdt_setprop_string(fdt, mem_off, "device_type", "memory");
	अगर (err) अणु
		pr_err("Unable to set memory node device_type: %d\n", err);
		वापस err;
	पूर्ण

	mem_entries = gen_fdt_mem_array(regions, mem_array,
					MAX_MEM_ARRAY_ENTRIES, phys_memsize);
	err = fdt_setprop(fdt, mem_off, "reg",
			  mem_array, mem_entries * 2 * माप(mem_array[0]));
	अगर (err) अणु
		pr_err("Unable to set memory regs property: %d\n", err);
		वापस err;
	पूर्ण

	mem_entries = gen_fdt_mem_array(regions, mem_array,
					MAX_MEM_ARRAY_ENTRIES, memsize);
	err = fdt_setprop(fdt, mem_off, "linux,usable-memory",
			  mem_array, mem_entries * 2 * माप(mem_array[0]));
	अगर (err) अणु
		pr_err("Unable to set linux,usable-memory property: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

__init पूर्णांक yamon_dt_serial_config(व्योम *fdt)
अणु
	स्थिर अक्षर *yamontty, *mode_var;
	अक्षर mode_var_name[9], path[20], parity;
	अचिन्हित पूर्णांक uart, baud, stop_bits;
	bool hw_flow;
	पूर्णांक chosen_off, err;

	yamontty = fw_दो_पर्या("yamontty");
	अगर (!yamontty || !म_भेद(yamontty, "tty0")) अणु
		uart = 0;
	पूर्ण अन्यथा अगर (!म_भेद(yamontty, "tty1")) अणु
		uart = 1;
	पूर्ण अन्यथा अणु
		pr_warn("yamontty environment variable '%s' invalid\n",
			yamontty);
		uart = 0;
	पूर्ण

	baud = stop_bits = 0;
	parity = 0;
	hw_flow = false;

	snम_लिखो(mode_var_name, माप(mode_var_name), "modetty%u", uart);
	mode_var = fw_दो_पर्या(mode_var_name);
	अगर (mode_var) अणु
		जबतक (mode_var[0] >= '0' && mode_var[0] <= '9') अणु
			baud *= 10;
			baud += mode_var[0] - '0';
			mode_var++;
		पूर्ण
		अगर (mode_var[0] == ',')
			mode_var++;
		अगर (mode_var[0])
			parity = mode_var[0];
		अगर (mode_var[0] == ',')
			mode_var++;
		अगर (mode_var[0])
			stop_bits = mode_var[0] - '0';
		अगर (mode_var[0] == ',')
			mode_var++;
		अगर (!म_भेद(mode_var, "hw"))
			hw_flow = true;
	पूर्ण

	अगर (!baud)
		baud = 38400;

	अगर (parity != 'e' && parity != 'n' && parity != 'o')
		parity = 'n';

	अगर (stop_bits != 7 && stop_bits != 8)
		stop_bits = 8;

	WARN_ON(snम_लिखो(path, माप(path), "serial%u:%u%c%u%s",
			 uart, baud, parity, stop_bits,
			 hw_flow ? "r" : "") >= माप(path));

	/* find or add chosen node */
	chosen_off = fdt_path_offset(fdt, "/chosen");
	अगर (chosen_off == -FDT_ERR_NOTFOUND)
		chosen_off = fdt_add_subnode(fdt, 0, "chosen");
	अगर (chosen_off < 0) अणु
		pr_err("Unable to find or add DT chosen node: %d\n",
		       chosen_off);
		वापस chosen_off;
	पूर्ण

	err = fdt_setprop_string(fdt, chosen_off, "stdout-path", path);
	अगर (err) अणु
		pr_err("Unable to set stdout-path property: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
