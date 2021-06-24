<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  AMD CPU Microcode Update Driver क्रम Linux
 *
 *  This driver allows to upgrade microcode on F10h AMD
 *  CPUs and later.
 *
 *  Copyright (C) 2008-2011 Advanced Micro Devices Inc.
 *	          2013-2018 Borislav Petkov <bp@alien8.de>
 *
 *  Author: Peter Oruba <peter.oruba@amd.com>
 *
 *  Based on work by:
 *  Tigran Aivazian <aivazian.tigran@gmail.com>
 *
 *  early loader:
 *  Copyright (C) 2013 Advanced Micro Devices, Inc.
 *
 *  Author: Jacob Shin <jacob.shin@amd.com>
 *  Fixes: Borislav Petkov <bp@suse.de>
 */
#घोषणा pr_fmt(fmt) "microcode: " fmt

#समावेश <linux/earlycpपन.स>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/initrd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/microcode_amd.h>
#समावेश <यंत्र/microcode.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/msr.h>

अटल काष्ठा equiv_cpu_table अणु
	अचिन्हित पूर्णांक num_entries;
	काष्ठा equiv_cpu_entry *entry;
पूर्ण equiv_table;

/*
 * This poपूर्णांकs to the current valid container of microcode patches which we will
 * save from the initrd/builtin beक्रमe jettisoning its contents. @mc is the
 * microcode patch we found to match.
 */
काष्ठा cont_desc अणु
	काष्ठा microcode_amd *mc;
	u32		     cpuid_1_eax;
	u32		     psize;
	u8		     *data;
	माप_प्रकार		     size;
पूर्ण;

अटल u32 ucode_new_rev;
अटल u8 amd_ucode_patch[PATCH_MAX_SIZE];

/*
 * Microcode patch container file is prepended to the initrd in cpio
 * क्रमmat. See Documentation/x86/microcode.rst
 */
अटल स्थिर अक्षर
ucode_path[] __maybe_unused = "kernel/x86/microcode/AuthenticAMD.bin";

अटल u16 find_equiv_id(काष्ठा equiv_cpu_table *et, u32 sig)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!et || !et->num_entries)
		वापस 0;

	क्रम (i = 0; i < et->num_entries; i++) अणु
		काष्ठा equiv_cpu_entry *e = &et->entry[i];

		अगर (sig == e->installed_cpu)
			वापस e->equiv_cpu;

		e++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check whether there is a valid microcode container file at the beginning
 * of @buf of size @buf_size. Set @early to use this function in the early path.
 */
अटल bool verअगरy_container(स्थिर u8 *buf, माप_प्रकार buf_size, bool early)
अणु
	u32 cont_magic;

	अगर (buf_size <= CONTAINER_HDR_SZ) अणु
		अगर (!early)
			pr_debug("Truncated microcode container header.\n");

		वापस false;
	पूर्ण

	cont_magic = *(स्थिर u32 *)buf;
	अगर (cont_magic != UCODE_MAGIC) अणु
		अगर (!early)
			pr_debug("Invalid magic value (0x%08x).\n", cont_magic);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Check whether there is a valid, non-truncated CPU equivalence table at the
 * beginning of @buf of size @buf_size. Set @early to use this function in the
 * early path.
 */
अटल bool verअगरy_equivalence_table(स्थिर u8 *buf, माप_प्रकार buf_size, bool early)
अणु
	स्थिर u32 *hdr = (स्थिर u32 *)buf;
	u32 cont_type, equiv_tbl_len;

	अगर (!verअगरy_container(buf, buf_size, early))
		वापस false;

	cont_type = hdr[1];
	अगर (cont_type != UCODE_EQUIV_CPU_TABLE_TYPE) अणु
		अगर (!early)
			pr_debug("Wrong microcode container equivalence table type: %u.\n",
			       cont_type);

		वापस false;
	पूर्ण

	buf_size -= CONTAINER_HDR_SZ;

	equiv_tbl_len = hdr[2];
	अगर (equiv_tbl_len < माप(काष्ठा equiv_cpu_entry) ||
	    buf_size < equiv_tbl_len) अणु
		अगर (!early)
			pr_debug("Truncated equivalence table.\n");

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Check whether there is a valid, non-truncated microcode patch section at the
 * beginning of @buf of size @buf_size. Set @early to use this function in the
 * early path.
 *
 * On success, @sh_psize वापसs the patch size according to the section header,
 * to the caller.
 */
अटल bool
__verअगरy_patch_section(स्थिर u8 *buf, माप_प्रकार buf_size, u32 *sh_psize, bool early)
अणु
	u32 p_type, p_size;
	स्थिर u32 *hdr;

	अगर (buf_size < SECTION_HDR_SIZE) अणु
		अगर (!early)
			pr_debug("Truncated patch section.\n");

		वापस false;
	पूर्ण

	hdr = (स्थिर u32 *)buf;
	p_type = hdr[0];
	p_size = hdr[1];

	अगर (p_type != UCODE_UCODE_TYPE) अणु
		अगर (!early)
			pr_debug("Invalid type field (0x%x) in container file section header.\n",
				p_type);

		वापस false;
	पूर्ण

	अगर (p_size < माप(काष्ठा microcode_header_amd)) अणु
		अगर (!early)
			pr_debug("Patch of size %u too short.\n", p_size);

		वापस false;
	पूर्ण

	*sh_psize = p_size;

	वापस true;
पूर्ण

/*
 * Check whether the passed reमुख्यing file @buf_size is large enough to contain
 * a patch of the indicated @sh_psize (and also whether this size करोes not
 * exceed the per-family maximum). @sh_psize is the size पढ़ो from the section
 * header.
 */
अटल अचिन्हित पूर्णांक __verअगरy_patch_size(u8 family, u32 sh_psize, माप_प्रकार buf_size)
अणु
	u32 max_size;

	अगर (family >= 0x15)
		वापस min_t(u32, sh_psize, buf_size);

#घोषणा F1XH_MPB_MAX_SIZE 2048
#घोषणा F14H_MPB_MAX_SIZE 1824

	चयन (family) अणु
	हाल 0x10 ... 0x12:
		max_size = F1XH_MPB_MAX_SIZE;
		अवरोध;
	हाल 0x14:
		max_size = F14H_MPB_MAX_SIZE;
		अवरोध;
	शेष:
		WARN(1, "%s: WTF family: 0x%x\n", __func__, family);
		वापस 0;
	पूर्ण

	अगर (sh_psize > min_t(u32, buf_size, max_size))
		वापस 0;

	वापस sh_psize;
पूर्ण

/*
 * Verअगरy the patch in @buf.
 *
 * Returns:
 * negative: on error
 * positive: patch is not क्रम this family, skip it
 * 0: success
 */
अटल पूर्णांक
verअगरy_patch(u8 family, स्थिर u8 *buf, माप_प्रकार buf_size, u32 *patch_size, bool early)
अणु
	काष्ठा microcode_header_amd *mc_hdr;
	अचिन्हित पूर्णांक ret;
	u32 sh_psize;
	u16 proc_id;
	u8 patch_fam;

	अगर (!__verअगरy_patch_section(buf, buf_size, &sh_psize, early))
		वापस -1;

	/*
	 * The section header length is not included in this indicated size
	 * but is present in the leftover file length so we need to subtract
	 * it beक्रमe passing this value to the function below.
	 */
	buf_size -= SECTION_HDR_SIZE;

	/*
	 * Check अगर the reमुख्यing buffer is big enough to contain a patch of
	 * size sh_psize, as the section claims.
	 */
	अगर (buf_size < sh_psize) अणु
		अगर (!early)
			pr_debug("Patch of size %u truncated.\n", sh_psize);

		वापस -1;
	पूर्ण

	ret = __verअगरy_patch_size(family, sh_psize, buf_size);
	अगर (!ret) अणु
		अगर (!early)
			pr_debug("Per-family patch size mismatch.\n");
		वापस -1;
	पूर्ण

	*patch_size = sh_psize;

	mc_hdr	= (काष्ठा microcode_header_amd *)(buf + SECTION_HDR_SIZE);
	अगर (mc_hdr->nb_dev_id || mc_hdr->sb_dev_id) अणु
		अगर (!early)
			pr_err("Patch-ID 0x%08x: chipset-specific code unsupported.\n", mc_hdr->patch_id);
		वापस -1;
	पूर्ण

	proc_id	= mc_hdr->processor_rev_id;
	patch_fam = 0xf + (proc_id >> 12);
	अगर (patch_fam != family)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * This scans the ucode blob क्रम the proper container as we can have multiple
 * containers glued together. Returns the equivalence ID from the equivalence
 * table or 0 अगर none found.
 * Returns the amount of bytes consumed जबतक scanning. @desc contains all the
 * data we're going to use in later stages of the application.
 */
अटल माप_प्रकार parse_container(u8 *ucode, माप_प्रकार size, काष्ठा cont_desc *desc)
अणु
	काष्ठा equiv_cpu_table table;
	माप_प्रकार orig_size = size;
	u32 *hdr = (u32 *)ucode;
	u16 eq_id;
	u8 *buf;

	अगर (!verअगरy_equivalence_table(ucode, size, true))
		वापस 0;

	buf = ucode;

	table.entry = (काष्ठा equiv_cpu_entry *)(buf + CONTAINER_HDR_SZ);
	table.num_entries = hdr[2] / माप(काष्ठा equiv_cpu_entry);

	/*
	 * Find the equivalence ID of our CPU in this table. Even अगर this table
	 * करोesn't contain a patch क्रम the CPU, scan through the whole container
	 * so that it can be skipped in हाल there are other containers appended.
	 */
	eq_id = find_equiv_id(&table, desc->cpuid_1_eax);

	buf  += hdr[2] + CONTAINER_HDR_SZ;
	size -= hdr[2] + CONTAINER_HDR_SZ;

	/*
	 * Scan through the rest of the container to find where it ends. We करो
	 * some basic sanity-checking too.
	 */
	जबतक (size > 0) अणु
		काष्ठा microcode_amd *mc;
		u32 patch_size;
		पूर्णांक ret;

		ret = verअगरy_patch(x86_family(desc->cpuid_1_eax), buf, size, &patch_size, true);
		अगर (ret < 0) अणु
			/*
			 * Patch verअगरication failed, skip to the next
			 * container, अगर there's one:
			 */
			जाओ out;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			जाओ skip;
		पूर्ण

		mc = (काष्ठा microcode_amd *)(buf + SECTION_HDR_SIZE);
		अगर (eq_id == mc->hdr.processor_rev_id) अणु
			desc->psize = patch_size;
			desc->mc = mc;
		पूर्ण

skip:
		/* Skip patch section header too: */
		buf  += patch_size + SECTION_HDR_SIZE;
		size -= patch_size + SECTION_HDR_SIZE;
	पूर्ण

	/*
	 * If we have found a patch (desc->mc), it means we're looking at the
	 * container which has a patch क्रम this CPU so वापस 0 to mean, @ucode
	 * alपढ़ोy poपूर्णांकs to the proper container. Otherwise, we वापस the size
	 * we scanned so that we can advance to the next container in the
	 * buffer.
	 */
	अगर (desc->mc) अणु
		desc->data = ucode;
		desc->size = orig_size - size;

		वापस 0;
	पूर्ण

out:
	वापस orig_size - size;
पूर्ण

/*
 * Scan the ucode blob क्रम the proper container as we can have multiple
 * containers glued together.
 */
अटल व्योम scan_containers(u8 *ucode, माप_प्रकार size, काष्ठा cont_desc *desc)
अणु
	जबतक (size) अणु
		माप_प्रकार s = parse_container(ucode, size, desc);
		अगर (!s)
			वापस;

		/* catch wraparound */
		अगर (size >= s) अणु
			ucode += s;
			size  -= s;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __apply_microcode_amd(काष्ठा microcode_amd *mc)
अणु
	u32 rev, dummy;

	native_wrmsrl(MSR_AMD64_PATCH_LOADER, (u64)(दीर्घ)&mc->hdr.data_code);

	/* verअगरy patch application was successful */
	native_rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);
	अगर (rev != mc->hdr.patch_id)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Early load occurs beक्रमe we can vदो_स्मृति(). So we look क्रम the microcode
 * patch container file in initrd, traverse equivalent cpu table, look क्रम a
 * matching microcode patch, and update, all in initrd memory in place.
 * When vदो_स्मृति() is available क्रम use later -- on 64-bit during first AP load,
 * and on 32-bit during save_microcode_in_initrd_amd() -- we can call
 * load_microcode_amd() to save equivalent cpu table and microcode patches in
 * kernel heap memory.
 *
 * Returns true अगर container found (sets @desc), false otherwise.
 */
अटल bool
apply_microcode_early_amd(u32 cpuid_1_eax, व्योम *ucode, माप_प्रकार size, bool save_patch)
अणु
	काष्ठा cont_desc desc = अणु 0 पूर्ण;
	u8 (*patch)[PATCH_MAX_SIZE];
	काष्ठा microcode_amd *mc;
	u32 rev, dummy, *new_rev;
	bool ret = false;

#अगर_घोषित CONFIG_X86_32
	new_rev = (u32 *)__pa_nodebug(&ucode_new_rev);
	patch	= (u8 (*)[PATCH_MAX_SIZE])__pa_nodebug(&amd_ucode_patch);
#अन्यथा
	new_rev = &ucode_new_rev;
	patch	= &amd_ucode_patch;
#पूर्ण_अगर

	desc.cpuid_1_eax = cpuid_1_eax;

	scan_containers(ucode, size, &desc);

	mc = desc.mc;
	अगर (!mc)
		वापस ret;

	native_rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);
	अगर (rev >= mc->hdr.patch_id)
		वापस ret;

	अगर (!__apply_microcode_amd(mc)) अणु
		*new_rev = mc->hdr.patch_id;
		ret      = true;

		अगर (save_patch)
			स_नकल(patch, mc, min_t(u32, desc.psize, PATCH_MAX_SIZE));
	पूर्ण

	वापस ret;
पूर्ण

अटल bool get_builtin_microcode(काष्ठा cpio_data *cp, अचिन्हित पूर्णांक family)
अणु
#अगर_घोषित CONFIG_X86_64
	अक्षर fw_name[36] = "amd-ucode/microcode_amd.bin";

	अगर (family >= 0x15)
		snम_लिखो(fw_name, माप(fw_name),
			 "amd-ucode/microcode_amd_fam%.2xh.bin", family);

	वापस get_builtin_firmware(cp, fw_name);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल व्योम __load_ucode_amd(अचिन्हित पूर्णांक cpuid_1_eax, काष्ठा cpio_data *ret)
अणु
	काष्ठा ucode_cpu_info *uci;
	काष्ठा cpio_data cp;
	स्थिर अक्षर *path;
	bool use_pa;

	अगर (IS_ENABLED(CONFIG_X86_32)) अणु
		uci	= (काष्ठा ucode_cpu_info *)__pa_nodebug(ucode_cpu_info);
		path	= (स्थिर अक्षर *)__pa_nodebug(ucode_path);
		use_pa	= true;
	पूर्ण अन्यथा अणु
		uci     = ucode_cpu_info;
		path	= ucode_path;
		use_pa	= false;
	पूर्ण

	अगर (!get_builtin_microcode(&cp, x86_family(cpuid_1_eax)))
		cp = find_microcode_in_initrd(path, use_pa);

	/* Needed in load_microcode_amd() */
	uci->cpu_sig.sig = cpuid_1_eax;

	*ret = cp;
पूर्ण

व्योम __init load_ucode_amd_bsp(अचिन्हित पूर्णांक cpuid_1_eax)
अणु
	काष्ठा cpio_data cp = अणु पूर्ण;

	__load_ucode_amd(cpuid_1_eax, &cp);
	अगर (!(cp.data && cp.size))
		वापस;

	apply_microcode_early_amd(cpuid_1_eax, cp.data, cp.size, true);
पूर्ण

व्योम load_ucode_amd_ap(अचिन्हित पूर्णांक cpuid_1_eax)
अणु
	काष्ठा microcode_amd *mc;
	काष्ठा cpio_data cp;
	u32 *new_rev, rev, dummy;

	अगर (IS_ENABLED(CONFIG_X86_32)) अणु
		mc	= (काष्ठा microcode_amd *)__pa_nodebug(amd_ucode_patch);
		new_rev = (u32 *)__pa_nodebug(&ucode_new_rev);
	पूर्ण अन्यथा अणु
		mc	= (काष्ठा microcode_amd *)amd_ucode_patch;
		new_rev = &ucode_new_rev;
	पूर्ण

	native_rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);

	/* Check whether we have saved a new patch alपढ़ोy: */
	अगर (*new_rev && rev < mc->hdr.patch_id) अणु
		अगर (!__apply_microcode_amd(mc)) अणु
			*new_rev = mc->hdr.patch_id;
			वापस;
		पूर्ण
	पूर्ण

	__load_ucode_amd(cpuid_1_eax, &cp);
	अगर (!(cp.data && cp.size))
		वापस;

	apply_microcode_early_amd(cpuid_1_eax, cp.data, cp.size, false);
पूर्ण

अटल क्रमागत ucode_state
load_microcode_amd(bool save, u8 family, स्थिर u8 *data, माप_प्रकार size);

पूर्णांक __init save_microcode_in_initrd_amd(अचिन्हित पूर्णांक cpuid_1_eax)
अणु
	काष्ठा cont_desc desc = अणु 0 पूर्ण;
	क्रमागत ucode_state ret;
	काष्ठा cpio_data cp;

	cp = find_microcode_in_initrd(ucode_path, false);
	अगर (!(cp.data && cp.size))
		वापस -EINVAL;

	desc.cpuid_1_eax = cpuid_1_eax;

	scan_containers(cp.data, cp.size, &desc);
	अगर (!desc.mc)
		वापस -EINVAL;

	ret = load_microcode_amd(true, x86_family(cpuid_1_eax), desc.data, desc.size);
	अगर (ret > UCODE_UPDATED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम reload_ucode_amd(व्योम)
अणु
	काष्ठा microcode_amd *mc;
	u32 rev, dummy __always_unused;

	mc = (काष्ठा microcode_amd *)amd_ucode_patch;

	rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);

	अगर (rev < mc->hdr.patch_id) अणु
		अगर (!__apply_microcode_amd(mc)) अणु
			ucode_new_rev = mc->hdr.patch_id;
			pr_info("reload patch_level=0x%08x\n", ucode_new_rev);
		पूर्ण
	पूर्ण
पूर्ण
अटल u16 __find_equiv_id(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
	वापस find_equiv_id(&equiv_table, uci->cpu_sig.sig);
पूर्ण

/*
 * a small, trivial cache of per-family ucode patches
 */
अटल काष्ठा ucode_patch *cache_find_patch(u16 equiv_cpu)
अणु
	काष्ठा ucode_patch *p;

	list_क्रम_each_entry(p, &microcode_cache, plist)
		अगर (p->equiv_cpu == equiv_cpu)
			वापस p;
	वापस शून्य;
पूर्ण

अटल व्योम update_cache(काष्ठा ucode_patch *new_patch)
अणु
	काष्ठा ucode_patch *p;

	list_क्रम_each_entry(p, &microcode_cache, plist) अणु
		अगर (p->equiv_cpu == new_patch->equiv_cpu) अणु
			अगर (p->patch_id >= new_patch->patch_id) अणु
				/* we alपढ़ोy have the latest patch */
				kमुक्त(new_patch->data);
				kमुक्त(new_patch);
				वापस;
			पूर्ण

			list_replace(&p->plist, &new_patch->plist);
			kमुक्त(p->data);
			kमुक्त(p);
			वापस;
		पूर्ण
	पूर्ण
	/* no patch found, add it */
	list_add_tail(&new_patch->plist, &microcode_cache);
पूर्ण

अटल व्योम मुक्त_cache(व्योम)
अणु
	काष्ठा ucode_patch *p, *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &microcode_cache, plist) अणु
		__list_del(p->plist.prev, p->plist.next);
		kमुक्त(p->data);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल काष्ठा ucode_patch *find_patch(अचिन्हित पूर्णांक cpu)
अणु
	u16 equiv_id;

	equiv_id = __find_equiv_id(cpu);
	अगर (!equiv_id)
		वापस शून्य;

	वापस cache_find_patch(equiv_id);
पूर्ण

अटल पूर्णांक collect_cpu_info_amd(पूर्णांक cpu, काष्ठा cpu_signature *csig)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
	काष्ठा ucode_patch *p;

	csig->sig = cpuid_eax(0x00000001);
	csig->rev = c->microcode;

	/*
	 * a patch could have been loaded early, set uci->mc so that
	 * mc_bp_resume() can call apply_microcode()
	 */
	p = find_patch(cpu);
	अगर (p && (p->patch_id == csig->rev))
		uci->mc = p->data;

	pr_info("CPU%d: patch_level=0x%08x\n", cpu, csig->rev);

	वापस 0;
पूर्ण

अटल क्रमागत ucode_state apply_microcode_amd(पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	काष्ठा microcode_amd *mc_amd;
	काष्ठा ucode_cpu_info *uci;
	काष्ठा ucode_patch *p;
	क्रमागत ucode_state ret;
	u32 rev, dummy __always_unused;

	BUG_ON(raw_smp_processor_id() != cpu);

	uci = ucode_cpu_info + cpu;

	p = find_patch(cpu);
	अगर (!p)
		वापस UCODE_NFOUND;

	mc_amd  = p->data;
	uci->mc = p->data;

	rdmsr(MSR_AMD64_PATCH_LEVEL, rev, dummy);

	/* need to apply patch? */
	अगर (rev >= mc_amd->hdr.patch_id) अणु
		ret = UCODE_OK;
		जाओ out;
	पूर्ण

	अगर (__apply_microcode_amd(mc_amd)) अणु
		pr_err("CPU%d: update failed for patch_level=0x%08x\n",
			cpu, mc_amd->hdr.patch_id);
		वापस UCODE_ERROR;
	पूर्ण

	rev = mc_amd->hdr.patch_id;
	ret = UCODE_UPDATED;

	pr_info("CPU%d: new patch_level=0x%08x\n", cpu, rev);

out:
	uci->cpu_sig.rev = rev;
	c->microcode	 = rev;

	/* Update boot_cpu_data's revision too, if we're on the BSP: */
	अगर (c->cpu_index == boot_cpu_data.cpu_index)
		boot_cpu_data.microcode = rev;

	वापस ret;
पूर्ण

अटल माप_प्रकार install_equiv_cpu_table(स्थिर u8 *buf, माप_प्रकार buf_size)
अणु
	u32 equiv_tbl_len;
	स्थिर u32 *hdr;

	अगर (!verअगरy_equivalence_table(buf, buf_size, false))
		वापस 0;

	hdr = (स्थिर u32 *)buf;
	equiv_tbl_len = hdr[2];

	equiv_table.entry = vदो_स्मृति(equiv_tbl_len);
	अगर (!equiv_table.entry) अणु
		pr_err("failed to allocate equivalent CPU table\n");
		वापस 0;
	पूर्ण

	स_नकल(equiv_table.entry, buf + CONTAINER_HDR_SZ, equiv_tbl_len);
	equiv_table.num_entries = equiv_tbl_len / माप(काष्ठा equiv_cpu_entry);

	/* add header length */
	वापस equiv_tbl_len + CONTAINER_HDR_SZ;
पूर्ण

अटल व्योम मुक्त_equiv_cpu_table(व्योम)
अणु
	vमुक्त(equiv_table.entry);
	स_रखो(&equiv_table, 0, माप(equiv_table));
पूर्ण

अटल व्योम cleanup(व्योम)
अणु
	मुक्त_equiv_cpu_table();
	मुक्त_cache();
पूर्ण

/*
 * Return a non-negative value even अगर some of the checks failed so that
 * we can skip over the next patch. If we वापस a negative value, we
 * संकेत a grave error like a memory allocation has failed and the
 * driver cannot जारी functioning normally. In such हालs, we tear
 * करोwn everything we've used up so far and निकास.
 */
अटल पूर्णांक verअगरy_and_add_patch(u8 family, u8 *fw, अचिन्हित पूर्णांक leftover,
				अचिन्हित पूर्णांक *patch_size)
अणु
	काष्ठा microcode_header_amd *mc_hdr;
	काष्ठा ucode_patch *patch;
	u16 proc_id;
	पूर्णांक ret;

	ret = verअगरy_patch(family, fw, leftover, patch_size, false);
	अगर (ret)
		वापस ret;

	patch = kzalloc(माप(*patch), GFP_KERNEL);
	अगर (!patch) अणु
		pr_err("Patch allocation failure.\n");
		वापस -EINVAL;
	पूर्ण

	patch->data = kmemdup(fw + SECTION_HDR_SIZE, *patch_size, GFP_KERNEL);
	अगर (!patch->data) अणु
		pr_err("Patch data allocation failure.\n");
		kमुक्त(patch);
		वापस -EINVAL;
	पूर्ण

	mc_hdr      = (काष्ठा microcode_header_amd *)(fw + SECTION_HDR_SIZE);
	proc_id     = mc_hdr->processor_rev_id;

	INIT_LIST_HEAD(&patch->plist);
	patch->patch_id  = mc_hdr->patch_id;
	patch->equiv_cpu = proc_id;

	pr_debug("%s: Added patch_id: 0x%08x, proc_id: 0x%04x\n",
		 __func__, patch->patch_id, proc_id);

	/* ... and add to cache. */
	update_cache(patch);

	वापस 0;
पूर्ण

अटल क्रमागत ucode_state __load_microcode_amd(u8 family, स्थिर u8 *data,
					     माप_प्रकार size)
अणु
	u8 *fw = (u8 *)data;
	माप_प्रकार offset;

	offset = install_equiv_cpu_table(data, size);
	अगर (!offset)
		वापस UCODE_ERROR;

	fw   += offset;
	size -= offset;

	अगर (*(u32 *)fw != UCODE_UCODE_TYPE) अणु
		pr_err("invalid type field in container file section header\n");
		मुक्त_equiv_cpu_table();
		वापस UCODE_ERROR;
	पूर्ण

	जबतक (size > 0) अणु
		अचिन्हित पूर्णांक crnt_size = 0;
		पूर्णांक ret;

		ret = verअगरy_and_add_patch(family, fw, size, &crnt_size);
		अगर (ret < 0)
			वापस UCODE_ERROR;

		fw   +=  crnt_size + SECTION_HDR_SIZE;
		size -= (crnt_size + SECTION_HDR_SIZE);
	पूर्ण

	वापस UCODE_OK;
पूर्ण

अटल क्रमागत ucode_state
load_microcode_amd(bool save, u8 family, स्थिर u8 *data, माप_प्रकार size)
अणु
	काष्ठा ucode_patch *p;
	क्रमागत ucode_state ret;

	/* मुक्त old equiv table */
	मुक्त_equiv_cpu_table();

	ret = __load_microcode_amd(family, data, size);
	अगर (ret != UCODE_OK) अणु
		cleanup();
		वापस ret;
	पूर्ण

	p = find_patch(0);
	अगर (!p) अणु
		वापस ret;
	पूर्ण अन्यथा अणु
		अगर (boot_cpu_data.microcode >= p->patch_id)
			वापस ret;

		ret = UCODE_NEW;
	पूर्ण

	/* save BSP's matching patch क्रम early load */
	अगर (!save)
		वापस ret;

	स_रखो(amd_ucode_patch, 0, PATCH_MAX_SIZE);
	स_नकल(amd_ucode_patch, p->data, min_t(u32, ksize(p->data), PATCH_MAX_SIZE));

	वापस ret;
पूर्ण

/*
 * AMD microcode firmware naming convention, up to family 15h they are in
 * the legacy file:
 *
 *    amd-ucode/microcode_amd.bin
 *
 * This legacy file is always smaller than 2K in size.
 *
 * Beginning with family 15h, they are in family-specअगरic firmware files:
 *
 *    amd-ucode/microcode_amd_fam15h.bin
 *    amd-ucode/microcode_amd_fam16h.bin
 *    ...
 *
 * These might be larger than 2K.
 */
अटल क्रमागत ucode_state request_microcode_amd(पूर्णांक cpu, काष्ठा device *device,
					      bool refresh_fw)
अणु
	अक्षर fw_name[36] = "amd-ucode/microcode_amd.bin";
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	bool bsp = c->cpu_index == boot_cpu_data.cpu_index;
	क्रमागत ucode_state ret = UCODE_NFOUND;
	स्थिर काष्ठा firmware *fw;

	/* reload ucode container only on the boot cpu */
	अगर (!refresh_fw || !bsp)
		वापस UCODE_OK;

	अगर (c->x86 >= 0x15)
		snम_लिखो(fw_name, माप(fw_name), "amd-ucode/microcode_amd_fam%.2xh.bin", c->x86);

	अगर (request_firmware_direct(&fw, (स्थिर अक्षर *)fw_name, device)) अणु
		pr_debug("failed to load file %s\n", fw_name);
		जाओ out;
	पूर्ण

	ret = UCODE_ERROR;
	अगर (!verअगरy_container(fw->data, fw->size, false))
		जाओ fw_release;

	ret = load_microcode_amd(bsp, c->x86, fw->data, fw->size);

 fw_release:
	release_firmware(fw);

 out:
	वापस ret;
पूर्ण

अटल क्रमागत ucode_state
request_microcode_user(पूर्णांक cpu, स्थिर व्योम __user *buf, माप_प्रकार size)
अणु
	वापस UCODE_ERROR;
पूर्ण

अटल व्योम microcode_fini_cpu_amd(पूर्णांक cpu)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;

	uci->mc = शून्य;
पूर्ण

अटल काष्ठा microcode_ops microcode_amd_ops = अणु
	.request_microcode_user           = request_microcode_user,
	.request_microcode_fw             = request_microcode_amd,
	.collect_cpu_info                 = collect_cpu_info_amd,
	.apply_microcode                  = apply_microcode_amd,
	.microcode_fini_cpu               = microcode_fini_cpu_amd,
पूर्ण;

काष्ठा microcode_ops * __init init_amd_microcode(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86_venकरोr != X86_VENDOR_AMD || c->x86 < 0x10) अणु
		pr_warn("AMD CPU family 0x%x not supported\n", c->x86);
		वापस शून्य;
	पूर्ण

	अगर (ucode_new_rev)
		pr_info_once("microcode updated early to new patch_level=0x%08x\n",
			     ucode_new_rev);

	वापस &microcode_amd_ops;
पूर्ण

व्योम __निकास निकास_amd_microcode(व्योम)
अणु
	cleanup();
पूर्ण
