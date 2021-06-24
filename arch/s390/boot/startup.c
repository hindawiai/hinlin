<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/elf.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/uv.h>
#समावेश "compressed/decompressor.h"
#समावेश "boot.h"

बाह्य अक्षर __boot_data_start[], __boot_data_end[];
बाह्य अक्षर __boot_data_preserved_start[], __boot_data_preserved_end[];
अचिन्हित दीर्घ __bootdata_preserved(__kaslr_offset);
अचिन्हित दीर्घ __bootdata(ident_map_size);

/*
 * Some code and data needs to stay below 2 GB, even when the kernel would be
 * relocated above 2 GB, because it has to use 31 bit addresses.
 * Such code and data is part of the .dma section, and its location is passed
 * over to the decompressed / relocated kernel via the .boot.preserved.data
 * section.
 */
बाह्य अक्षर _sdma[], _edma[];
बाह्य अक्षर _stext_dma[], _etext_dma[];
बाह्य काष्ठा exception_table_entry _start_dma_ex_table[];
बाह्य काष्ठा exception_table_entry _stop_dma_ex_table[];
अचिन्हित दीर्घ __bootdata_preserved(__sdma) = __pa(&_sdma);
अचिन्हित दीर्घ __bootdata_preserved(__edma) = __pa(&_edma);
अचिन्हित दीर्घ __bootdata_preserved(__stext_dma) = __pa(&_stext_dma);
अचिन्हित दीर्घ __bootdata_preserved(__etext_dma) = __pa(&_etext_dma);
काष्ठा exception_table_entry *
	__bootdata_preserved(__start_dma_ex_table) = _start_dma_ex_table;
काष्ठा exception_table_entry *
	__bootdata_preserved(__stop_dma_ex_table) = _stop_dma_ex_table;

पूर्णांक _diag210_dma(काष्ठा diag210 *addr);
पूर्णांक _diag26c_dma(व्योम *req, व्योम *resp, क्रमागत diag26c_sc subcode);
पूर्णांक _diag14_dma(अचिन्हित दीर्घ rx, अचिन्हित दीर्घ ry1, अचिन्हित दीर्घ subcode);
व्योम _diag0c_dma(काष्ठा hypfs_diag0c_entry *entry);
व्योम _diag308_reset_dma(व्योम);
काष्ठा diag_ops __bootdata_preserved(diag_dma_ops) = अणु
	.diag210 = _diag210_dma,
	.diag26c = _diag26c_dma,
	.diag14 = _diag14_dma,
	.diag0c = _diag0c_dma,
	.diag308_reset = _diag308_reset_dma
पूर्ण;
अटल काष्ठा diag210 _diag210_पंचांगp_dma __section(".dma.data");
काष्ठा diag210 *__bootdata_preserved(__diag210_पंचांगp_dma) = &_diag210_पंचांगp_dma;

व्योम error(अक्षर *x)
अणु
	sclp_early_prपूर्णांकk("\n\n");
	sclp_early_prपूर्णांकk(x);
	sclp_early_prपूर्णांकk("\n\n -- System halted");

	disabled_रुको();
पूर्ण

अटल व्योम setup_lpp(व्योम)
अणु
	S390_lowcore.current_pid = 0;
	S390_lowcore.lpp = LPP_MAGIC;
	अगर (test_facility(40))
		lpp(&S390_lowcore.lpp);
पूर्ण

#अगर_घोषित CONFIG_KERNEL_UNCOMPRESSED
अचिन्हित दीर्घ mem_safe_offset(व्योम)
अणु
	वापस vmlinux.शेष_lma + vmlinux.image_size + vmlinux.bss_size;
पूर्ण
#पूर्ण_अगर

अटल व्योम rescue_initrd(अचिन्हित दीर्घ addr)
अणु
	अगर (!IS_ENABLED(CONFIG_BLK_DEV_INITRD))
		वापस;
	अगर (!INITRD_START || !INITRD_SIZE)
		वापस;
	अगर (addr <= INITRD_START)
		वापस;
	स_हटाओ((व्योम *)addr, (व्योम *)INITRD_START, INITRD_SIZE);
	INITRD_START = addr;
पूर्ण

अटल व्योम copy_bootdata(व्योम)
अणु
	अगर (__boot_data_end - __boot_data_start != vmlinux.bootdata_size)
		error(".boot.data section size mismatch");
	स_नकल((व्योम *)vmlinux.bootdata_off, __boot_data_start, vmlinux.bootdata_size);
	अगर (__boot_data_preserved_end - __boot_data_preserved_start != vmlinux.bootdata_preserved_size)
		error(".boot.preserved.data section size mismatch");
	स_नकल((व्योम *)vmlinux.bootdata_preserved_off, __boot_data_preserved_start, vmlinux.bootdata_preserved_size);
पूर्ण

अटल व्योम handle_relocs(अचिन्हित दीर्घ offset)
अणु
	Elf64_Rela *rela_start, *rela_end, *rela;
	पूर्णांक r_type, r_sym, rc;
	Elf64_Addr loc, val;
	Elf64_Sym *dynsym;

	rela_start = (Elf64_Rela *) vmlinux.rela_dyn_start;
	rela_end = (Elf64_Rela *) vmlinux.rela_dyn_end;
	dynsym = (Elf64_Sym *) vmlinux.dynsym_start;
	क्रम (rela = rela_start; rela < rela_end; rela++) अणु
		loc = rela->r_offset + offset;
		val = rela->r_addend;
		r_sym = ELF64_R_SYM(rela->r_info);
		अगर (r_sym) अणु
			अगर (dynsym[r_sym].st_shndx != SHN_UNDEF)
				val += dynsym[r_sym].st_value + offset;
		पूर्ण अन्यथा अणु
			/*
			 * 0 == undefined symbol table index (STN_UNDEF),
			 * used क्रम R_390_RELATIVE, only add KASLR offset
			 */
			val += offset;
		पूर्ण
		r_type = ELF64_R_TYPE(rela->r_info);
		rc = arch_kexec_करो_relocs(r_type, (व्योम *) loc, val, 0);
		अगर (rc)
			error("Unknown relocation type");
	पूर्ण
पूर्ण

/*
 * Merge inक्रमmation from several sources पूर्णांकo a single ident_map_size value.
 * "ident_map_size" represents the upper limit of physical memory we may ever
 * reach. It might not be all online memory, but also include standby (offline)
 * memory. "ident_map_size" could be lower then actual standby or even online
 * memory present, due to limiting factors. We should never go above this limit.
 * It is the size of our identity mapping.
 *
 * Consider the following factors:
 * 1. max_physmem_end - end of physical memory online or standby.
 *    Always <= end of the last online memory block (get_mem_detect_end()).
 * 2. CONFIG_MAX_PHYSMEM_BITS - the maximum size of physical memory the
 *    kernel is able to support.
 * 3. "mem=" kernel command line option which limits physical memory usage.
 * 4. OLDMEM_BASE which is a kdump memory limit when the kernel is executed as
 *    crash kernel.
 * 5. "hsa" size which is a memory limit when the kernel is executed during
 *    zfcp/nvme dump.
 */
अटल व्योम setup_ident_map_size(अचिन्हित दीर्घ max_physmem_end)
अणु
	अचिन्हित दीर्घ hsa_size;

	ident_map_size = max_physmem_end;
	अगर (memory_limit)
		ident_map_size = min(ident_map_size, memory_limit);
	ident_map_size = min(ident_map_size, 1UL << MAX_PHYSMEM_BITS);

#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (OLDMEM_BASE) अणु
		kaslr_enabled = 0;
		ident_map_size = min(ident_map_size, OLDMEM_SIZE);
	पूर्ण अन्यथा अगर (ipl_block_valid && is_ipl_block_dump()) अणु
		kaslr_enabled = 0;
		अगर (!sclp_early_get_hsa_size(&hsa_size) && hsa_size)
			ident_map_size = min(ident_map_size, hsa_size);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * This function clears the BSS section of the decompressed Linux kernel and NOT the decompressor's.
 */
अटल व्योम clear_bss_section(व्योम)
अणु
	स_रखो((व्योम *)vmlinux.शेष_lma + vmlinux.image_size, 0, vmlinux.bss_size);
पूर्ण

/*
 * Set vदो_स्मृति area size to an 8th of (potential) physical memory
 * size, unless size has been set by kernel command line parameter.
 */
अटल व्योम setup_vदो_स्मृति_size(व्योम)
अणु
	अचिन्हित दीर्घ size;

	अगर (vदो_स्मृति_size_set)
		वापस;
	size = round_up(ident_map_size / 8, _SEGMENT_SIZE);
	vदो_स्मृति_size = max(size, vदो_स्मृति_size);
पूर्ण

व्योम startup_kernel(व्योम)
अणु
	अचिन्हित दीर्घ अक्रमom_lma;
	अचिन्हित दीर्घ safe_addr;
	व्योम *img;

	setup_lpp();
	store_ipl_parmblock();
	safe_addr = mem_safe_offset();
	safe_addr = पढ़ो_ipl_report(safe_addr);
	uv_query_info();
	rescue_initrd(safe_addr);
	sclp_early_पढ़ो_info();
	setup_boot_command_line();
	parse_boot_command_line();
	setup_ident_map_size(detect_memory());
	setup_vदो_स्मृति_size();

	अक्रमom_lma = __kaslr_offset = 0;
	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && kaslr_enabled) अणु
		अक्रमom_lma = get_अक्रमom_base(safe_addr);
		अगर (अक्रमom_lma) अणु
			__kaslr_offset = अक्रमom_lma - vmlinux.शेष_lma;
			img = (व्योम *)vmlinux.शेष_lma;
			vmlinux.शेष_lma += __kaslr_offset;
			vmlinux.entry += __kaslr_offset;
			vmlinux.bootdata_off += __kaslr_offset;
			vmlinux.bootdata_preserved_off += __kaslr_offset;
			vmlinux.rela_dyn_start += __kaslr_offset;
			vmlinux.rela_dyn_end += __kaslr_offset;
			vmlinux.dynsym_start += __kaslr_offset;
		पूर्ण
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_KERNEL_UNCOMPRESSED)) अणु
		img = decompress_kernel();
		स_हटाओ((व्योम *)vmlinux.शेष_lma, img, vmlinux.image_size);
	पूर्ण अन्यथा अगर (__kaslr_offset)
		स_नकल((व्योम *)vmlinux.शेष_lma, img, vmlinux.image_size);

	clear_bss_section();
	copy_bootdata();
	अगर (IS_ENABLED(CONFIG_RELOCATABLE))
		handle_relocs(__kaslr_offset);

	अगर (__kaslr_offset) अणु
		/*
		 * Save KASLR offset क्रम early dumps, beक्रमe vmcore_info is set.
		 * Mark as uneven to distinguish from real vmcore_info poपूर्णांकer.
		 */
		S390_lowcore.vmcore_info = __kaslr_offset | 0x1UL;
		/* Clear non-relocated kernel */
		अगर (IS_ENABLED(CONFIG_KERNEL_UNCOMPRESSED))
			स_रखो(img, 0, vmlinux.image_size);
	पूर्ण
	vmlinux.entry();
पूर्ण
