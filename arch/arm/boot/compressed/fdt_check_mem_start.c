<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/sizes.h>

अटल स्थिर व्योम *get_prop(स्थिर व्योम *fdt, स्थिर अक्षर *node_path,
			    स्थिर अक्षर *property, पूर्णांक minlen)
अणु
	स्थिर व्योम *prop;
	पूर्णांक offset, len;

	offset = fdt_path_offset(fdt, node_path);
	अगर (offset < 0)
		वापस शून्य;

	prop = fdt_getprop(fdt, offset, property, &len);
	अगर (!prop || len < minlen)
		वापस शून्य;

	वापस prop;
पूर्ण

अटल uपूर्णांक32_t get_cells(स्थिर व्योम *fdt, स्थिर अक्षर *name)
अणु
	स्थिर fdt32_t *prop = get_prop(fdt, "/", name, माप(fdt32_t));

	अगर (!prop) अणु
		/* शेष */
		वापस 1;
	पूर्ण

	वापस fdt32_ld(prop);
पूर्ण

अटल uपूर्णांक64_t get_val(स्थिर fdt32_t *cells, uपूर्णांक32_t ncells)
अणु
	uपूर्णांक64_t r;

	r = fdt32_ld(cells);
	अगर (ncells > 1)
		r = (r << 32) | fdt32_ld(cells + 1);

	वापस r;
पूर्ण

/*
 * Check the start of physical memory
 *
 * Traditionally, the start address of physical memory is obtained by masking
 * the program counter.  However, this करोes require that this address is a
 * multiple of 128 MiB, precluding booting Linux on platक्रमms where this
 * requirement is not fulfilled.
 * Hence validate the calculated address against the memory inक्रमmation in the
 * DTB, and, अगर out-of-range, replace it by the real start address.
 * To preserve backwards compatibility (प्रणालीs reserving a block of memory
 * at the start of physical memory, kdump, ...), the traditional method is
 * always used अगर it yields a valid address.
 *
 * Return value: start address of physical memory to use
 */
uपूर्णांक32_t fdt_check_mem_start(uपूर्णांक32_t mem_start, स्थिर व्योम *fdt)
अणु
	uपूर्णांक32_t addr_cells, size_cells, base;
	uपूर्णांक32_t fdt_mem_start = 0xffffffff;
	स्थिर fdt32_t *reg, *endp;
	uपूर्णांक64_t size, end;
	स्थिर अक्षर *type;
	पूर्णांक offset, len;

	अगर (!fdt)
		वापस mem_start;

	अगर (fdt_magic(fdt) != FDT_MAGIC)
		वापस mem_start;

	/* There may be multiple cells on LPAE platक्रमms */
	addr_cells = get_cells(fdt, "#address-cells");
	size_cells = get_cells(fdt, "#size-cells");
	अगर (addr_cells > 2 || size_cells > 2)
		वापस mem_start;

	/* Walk all memory nodes and regions */
	क्रम (offset = fdt_next_node(fdt, -1, शून्य); offset >= 0;
	     offset = fdt_next_node(fdt, offset, शून्य)) अणु
		type = fdt_getprop(fdt, offset, "device_type", शून्य);
		अगर (!type || म_भेद(type, "memory"))
			जारी;

		reg = fdt_getprop(fdt, offset, "linux,usable-memory", &len);
		अगर (!reg)
			reg = fdt_getprop(fdt, offset, "reg", &len);
		अगर (!reg)
			जारी;

		क्रम (endp = reg + (len / माप(fdt32_t));
		     endp - reg >= addr_cells + size_cells;
		     reg += addr_cells + size_cells) अणु
			size = get_val(reg + addr_cells, size_cells);
			अगर (!size)
				जारी;

			अगर (addr_cells > 1 && fdt32_ld(reg)) अणु
				/* Outside 32-bit address space, skipping */
				जारी;
			पूर्ण

			base = fdt32_ld(reg + addr_cells - 1);
			end = base + size;
			अगर (mem_start >= base && mem_start < end) अणु
				/* Calculated address is valid, use it */
				वापस mem_start;
			पूर्ण

			अगर (base < fdt_mem_start)
				fdt_mem_start = base;
		पूर्ण
	पूर्ण

	अगर (fdt_mem_start == 0xffffffff) अणु
		/* No usable memory found, falling back to शेष */
		वापस mem_start;
	पूर्ण

	/*
	 * The calculated address is not usable.
	 * Use the lowest usable physical memory address from the DTB instead,
	 * and make sure this is a multiple of 2 MiB क्रम phys/virt patching.
	 */
	वापस round_up(fdt_mem_start, SZ_2M);
पूर्ण
