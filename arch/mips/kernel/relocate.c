<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Support क्रम Kernel relocation at boot समय
 *
 * Copyright (C) 2015, Imagination Technologies Ltd.
 * Authors: Matt Redfearn (matt.redfearn@mips.com)
 */
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/समयx.h>
#समावेश <linux/elf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/prपूर्णांकk.h>

#घोषणा RELOCATED(x) ((व्योम *)((दीर्घ)x + offset))

बाह्य u32 _relocation_start[];	/* End kernel image / start relocation table */
बाह्य u32 _relocation_end[];	/* End relocation table */

बाह्य दीर्घ __start___ex_table;	/* Start exception table */
बाह्य दीर्घ __stop___ex_table;	/* End exception table */

बाह्य व्योम __weak plat_fdt_relocated(व्योम *new_location);

/*
 * This function may be defined क्रम a platक्रमm to perक्रमm any post-relocation
 * fixup necessary.
 * Return non-zero to पात relocation
 */
पूर्णांक __weak plat_post_relocation(दीर्घ offset)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 __init get_synci_step(व्योम)
अणु
	u32 res;

	__यंत्र__("rdhwr  %0, $1" : "=r" (res));

	वापस res;
पूर्ण

अटल व्योम __init sync_icache(व्योम *kbase, अचिन्हित दीर्घ kernel_length)
अणु
	व्योम *kend = kbase + kernel_length;
	u32 step = get_synci_step();

	करो अणु
		__यंत्र__ __अस्थिर__(
			"synci  0(%0)"
			: /* no output */
			: "r" (kbase));

		kbase += step;
	पूर्ण जबतक (step && kbase < kend);

	/* Completion barrier */
	__sync();
पूर्ण

अटल व्योम __init apply_r_mips_64_rel(u32 *loc_new, दीर्घ offset)
अणु
	*(u64 *)loc_new += offset;
पूर्ण

अटल व्योम __init apply_r_mips_32_rel(u32 *loc_new, दीर्घ offset)
अणु
	*loc_new += offset;
पूर्ण

अटल पूर्णांक __init apply_r_mips_26_rel(u32 *loc_orig, u32 *loc_new, दीर्घ offset)
अणु
	अचिन्हित दीर्घ target_addr = (*loc_orig) & 0x03ffffff;

	अगर (offset % 4) अणु
		pr_err("Dangerous R_MIPS_26 REL relocation\n");
		वापस -ENOEXEC;
	पूर्ण

	/* Original target address */
	target_addr <<= 2;
	target_addr += (अचिन्हित दीर्घ)loc_orig & 0xf0000000;

	/* Get the new target address */
	target_addr += offset;

	अगर ((target_addr & 0xf0000000) != ((अचिन्हित दीर्घ)loc_new & 0xf0000000)) अणु
		pr_err("R_MIPS_26 REL relocation overflow\n");
		वापस -ENOEXEC;
	पूर्ण

	target_addr -= (अचिन्हित दीर्घ)loc_new & 0xf0000000;
	target_addr >>= 2;

	*loc_new = (*loc_new & ~0x03ffffff) | (target_addr & 0x03ffffff);

	वापस 0;
पूर्ण


अटल व्योम __init apply_r_mips_hi16_rel(u32 *loc_orig, u32 *loc_new,
					 दीर्घ offset)
अणु
	अचिन्हित दीर्घ insn = *loc_orig;
	अचिन्हित दीर्घ target = (insn & 0xffff) << 16; /* high 16bits of target */

	target += offset;

	*loc_new = (insn & ~0xffff) | ((target >> 16) & 0xffff);
पूर्ण

अटल पूर्णांक __init reloc_handler(u32 type, u32 *loc_orig, u32 *loc_new,
				दीर्घ offset)
अणु
	चयन (type) अणु
	हाल R_MIPS_64:
		apply_r_mips_64_rel(loc_new, offset);
		अवरोध;
	हाल R_MIPS_32:
		apply_r_mips_32_rel(loc_new, offset);
		अवरोध;
	हाल R_MIPS_26:
		वापस apply_r_mips_26_rel(loc_orig, loc_new, offset);
	हाल R_MIPS_HI16:
		apply_r_mips_hi16_rel(loc_orig, loc_new, offset);
		अवरोध;
	शेष:
		pr_err("Unhandled relocation type %d at 0x%pK\n", type,
		       loc_orig);
		वापस -ENOEXEC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init करो_relocations(व्योम *kbase_old, व्योम *kbase_new, दीर्घ offset)
अणु
	u32 *r;
	u32 *loc_orig;
	u32 *loc_new;
	पूर्णांक type;
	पूर्णांक res;

	क्रम (r = _relocation_start; r < _relocation_end; r++) अणु
		/* Sentinel क्रम last relocation */
		अगर (*r == 0)
			अवरोध;

		type = (*r >> 24) & 0xff;
		loc_orig = kbase_old + ((*r & 0x00ffffff) << 2);
		loc_new = RELOCATED(loc_orig);

		res = reloc_handler(type, loc_orig, loc_new, offset);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The exception table is filled in by the relocs tool after vmlinux is linked.
 * It must be relocated separately since there will not be any relocation
 * inक्रमmation क्रम it filled in by the linker.
 */
अटल पूर्णांक __init relocate_exception_table(दीर्घ offset)
अणु
	अचिन्हित दीर्घ *etable_start, *etable_end, *e;

	etable_start = RELOCATED(&__start___ex_table);
	etable_end = RELOCATED(&__stop___ex_table);

	क्रम (e = etable_start; e < etable_end; e++)
		*e += offset;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RANDOMIZE_BASE

अटल अंतरभूत __init अचिन्हित दीर्घ rotate_xor(अचिन्हित दीर्घ hash,
					      स्थिर व्योम *area, माप_प्रकार size)
अणु
	स्थिर typeof(hash) *ptr = PTR_ALIGN(area, माप(hash));
	माप_प्रकार dअगरf, i;

	dअगरf = (व्योम *)ptr - area;
	अगर (unlikely(size < dअगरf + माप(hash)))
		वापस hash;

	size = ALIGN_DOWN(size - dअगरf, माप(hash));

	क्रम (i = 0; i < size / माप(hash); i++) अणु
		/* Rotate by odd number of bits and XOR. */
		hash = (hash << ((माप(hash) * 8) - 7)) | (hash >> 7);
		hash ^= ptr[i];
	पूर्ण

	वापस hash;
पूर्ण

अटल अंतरभूत __init अचिन्हित दीर्घ get_अक्रमom_boot(व्योम)
अणु
	अचिन्हित दीर्घ entropy = अक्रमom_get_entropy();
	अचिन्हित दीर्घ hash = 0;

	/* Attempt to create a simple but unpredictable starting entropy. */
	hash = rotate_xor(hash, linux_banner, म_माप(linux_banner));

	/* Add in any runसमय entropy we can get */
	hash = rotate_xor(hash, &entropy, माप(entropy));

#अगर defined(CONFIG_USE_OF)
	/* Get any additional entropy passed in device tree */
	अगर (initial_boot_params) अणु
		पूर्णांक node, len;
		u64 *prop;

		node = fdt_path_offset(initial_boot_params, "/chosen");
		अगर (node >= 0) अणु
			prop = fdt_getprop_w(initial_boot_params, node,
					     "kaslr-seed", &len);
			अगर (prop && (len == माप(u64)))
				hash = rotate_xor(hash, prop, माप(*prop));
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_USE_OF */

	वापस hash;
पूर्ण

अटल अंतरभूत __init bool kaslr_disabled(व्योम)
अणु
	अक्षर *str;

#अगर defined(CONFIG_CMDLINE_BOOL)
	स्थिर अक्षर *builtin_cmdline = CONFIG_CMDLINE;

	str = म_माला(builtin_cmdline, "nokaslr");
	अगर (str == builtin_cmdline ||
	    (str > builtin_cmdline && *(str - 1) == ' '))
		वापस true;
#पूर्ण_अगर
	str = म_माला(arcs_cmdline, "nokaslr");
	अगर (str == arcs_cmdline || (str > arcs_cmdline && *(str - 1) == ' '))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम __init *determine_relocation_address(व्योम)
अणु
	/* Choose a new address क्रम the kernel */
	अचिन्हित दीर्घ kernel_length;
	व्योम *dest = &_text;
	अचिन्हित दीर्घ offset;

	अगर (kaslr_disabled())
		वापस dest;

	kernel_length = (दीर्घ)_end - (दीर्घ)(&_text);

	offset = get_अक्रमom_boot() << 16;
	offset &= (CONFIG_RANDOMIZE_BASE_MAX_OFFSET - 1);
	अगर (offset < kernel_length)
		offset += ALIGN(kernel_length, 0xffff);

	वापस RELOCATED(dest);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __init *determine_relocation_address(व्योम)
अणु
	/*
	 * Choose a new address क्रम the kernel
	 * For now we'll hard code the destination
	 */
	वापस (व्योम *)0xffffffff81000000;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __init relocation_addr_valid(व्योम *loc_new)
अणु
	अगर ((अचिन्हित दीर्घ)loc_new & 0x0000ffff) अणु
		/* Inappropriately aligned new location */
		वापस 0;
	पूर्ण
	अगर ((अचिन्हित दीर्घ)loc_new < (अचिन्हित दीर्घ)&_end) अणु
		/* New location overlaps original kernel */
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम __init update_kaslr_offset(अचिन्हित दीर्घ *addr, दीर्घ offset)
अणु
	अचिन्हित दीर्घ *new_addr = (अचिन्हित दीर्घ *)RELOCATED(addr);

	*new_addr = (अचिन्हित दीर्घ)offset;
पूर्ण

#अगर defined(CONFIG_USE_OF)
व्योम __weak *plat_get_fdt(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

व्योम *__init relocate_kernel(व्योम)
अणु
	व्योम *loc_new;
	अचिन्हित दीर्घ kernel_length;
	अचिन्हित दीर्घ bss_length;
	दीर्घ offset = 0;
	पूर्णांक res = 1;
	/* Default to original kernel entry poपूर्णांक */
	व्योम *kernel_entry = start_kernel;
	व्योम *fdt = शून्य;

	/* Get the command line */
	fw_init_cmdline();
#अगर defined(CONFIG_USE_OF)
	/* Deal with the device tree */
	fdt = plat_get_fdt();
	early_init_dt_scan(fdt);
	अगर (boot_command_line[0]) अणु
		/* Boot command line was passed in device tree */
		strlcpy(arcs_cmdline, boot_command_line, COMMAND_LINE_SIZE);
	पूर्ण
#पूर्ण_अगर /* CONFIG_USE_OF */

	kernel_length = (दीर्घ)(&_relocation_start) - (दीर्घ)(&_text);
	bss_length = (दीर्घ)&__bss_stop - (दीर्घ)&__bss_start;

	loc_new = determine_relocation_address();

	/* Sanity check relocation address */
	अगर (relocation_addr_valid(loc_new))
		offset = (अचिन्हित दीर्घ)loc_new - (अचिन्हित दीर्घ)(&_text);

	/* Reset the command line now so we करोn't end up with a duplicate */
	arcs_cmdline[0] = '\0';

	अगर (offset) अणु
		व्योम (*fdt_relocated_)(व्योम *) = शून्य;
#अगर defined(CONFIG_USE_OF)
		अचिन्हित दीर्घ fdt_phys = virt_to_phys(fdt);

		/*
		 * If built-in dtb is used then it will have been relocated
		 * during kernel _text relocation. If appended DTB is used
		 * then it will not be relocated, but it should reमुख्य
		 * पूर्णांकact in the original location. If dtb is loaded by
		 * the bootloader then it may need to be moved अगर it crosses
		 * the target memory area
		 */

		अगर (fdt_phys >= virt_to_phys(RELOCATED(&_text)) &&
			fdt_phys <= virt_to_phys(RELOCATED(&_end))) अणु
			व्योम *fdt_relocated =
				RELOCATED(ALIGN((दीर्घ)&_end, PAGE_SIZE));
			स_नकल(fdt_relocated, fdt, fdt_totalsize(fdt));
			fdt = fdt_relocated;
			fdt_relocated_ = RELOCATED(&plat_fdt_relocated);
		पूर्ण
#पूर्ण_अगर /* CONFIG_USE_OF */

		/* Copy the kernel to it's new location */
		स_नकल(loc_new, &_text, kernel_length);

		/* Perक्रमm relocations on the new kernel */
		res = करो_relocations(&_text, loc_new, offset);
		अगर (res < 0)
			जाओ out;

		/* Sync the caches पढ़ोy क्रम execution of new kernel */
		sync_icache(loc_new, kernel_length);

		res = relocate_exception_table(offset);
		अगर (res < 0)
			जाओ out;

		/*
		 * The original .bss has alपढ़ोy been cleared, and
		 * some variables such as command line parameters
		 * stored to it so make a copy in the new location.
		 */
		स_नकल(RELOCATED(&__bss_start), &__bss_start, bss_length);

		/*
		 * If fdt was stored outside of the kernel image and
		 * had to be moved then update platक्रमm's state data
		 * with the new fdt location
		 */
		अगर (fdt_relocated_)
			fdt_relocated_(fdt);

		/*
		 * Last chance क्रम the platक्रमm to पात relocation.
		 * This may also be used by the platक्रमm to perक्रमm any
		 * initialisation required now that the new kernel is
		 * resident in memory and पढ़ोy to be executed.
		 */
		अगर (plat_post_relocation(offset))
			जाओ out;

		/* The current thपढ़ो is now within the relocated image */
		__current_thपढ़ो_info = RELOCATED(&init_thपढ़ो_जोड़);

		/* Return the new kernel's entry poपूर्णांक */
		kernel_entry = RELOCATED(start_kernel);

		/* Error may occur beक्रमe, so keep it at last */
		update_kaslr_offset(&__kaslr_offset, offset);
	पूर्ण
out:
	वापस kernel_entry;
पूर्ण

/*
 * Show relocation inक्रमmation on panic.
 */
अटल व्योम show_kernel_relocation(स्थिर अक्षर *level)
अणु
	अगर (__kaslr_offset > 0) अणु
		prपूर्णांकk(level);
		pr_cont("Kernel relocated by 0x%pK\n", (व्योम *)__kaslr_offset);
		pr_cont(" .text @ 0x%pK\n", _text);
		pr_cont(" .data @ 0x%pK\n", _sdata);
		pr_cont(" .bss  @ 0x%pK\n", __bss_start);
	पूर्ण
पूर्ण

अटल पूर्णांक kernel_location_notअगरier_fn(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ v, व्योम *p)
अणु
	show_kernel_relocation(KERN_EMERG);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block kernel_location_notअगरier = अणु
	.notअगरier_call = kernel_location_notअगरier_fn
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_kernel_offset_dumper(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &kernel_location_notअगरier);
	वापस 0;
पूर्ण
__initcall(रेजिस्टर_kernel_offset_dumper);
