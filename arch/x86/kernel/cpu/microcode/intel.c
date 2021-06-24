<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Intel CPU Microcode Update Driver क्रम Linux
 *
 * Copyright (C) 2000-2006 Tigran Aivazian <aivazian.tigran@gmail.com>
 *		 2006 Shaohua Li <shaohua.li@पूर्णांकel.com>
 *
 * Intel CPU microcode early update क्रम Linux
 *
 * Copyright (C) 2012 Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *		      H Peter Anvin" <hpa@zytor.com>
 */

/*
 * This needs to be beक्रमe all headers so that pr_debug in prपूर्णांकk.h करोesn't turn
 * prपूर्णांकk calls पूर्णांकo no_prपूर्णांकk().
 *
 *#घोषणा DEBUG
 */
#घोषणा pr_fmt(fmt) "microcode: " fmt

#समावेश <linux/earlycpपन.स>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/initrd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/uपन.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/microcode_पूर्णांकel.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/msr.h>

अटल स्थिर अक्षर ucode_path[] = "kernel/x86/microcode/GenuineIntel.bin";

/* Current microcode patch used in early patching on the APs. */
अटल काष्ठा microcode_पूर्णांकel *पूर्णांकel_ucode_patch;

/* last level cache size per core */
अटल पूर्णांक llc_size_per_core;

अटल अंतरभूत bool cpu_signatures_match(अचिन्हित पूर्णांक s1, अचिन्हित पूर्णांक p1,
					अचिन्हित पूर्णांक s2, अचिन्हित पूर्णांक p2)
अणु
	अगर (s1 != s2)
		वापस false;

	/* Processor flags are either both 0 ... */
	अगर (!p1 && !p2)
		वापस true;

	/* ... or they पूर्णांकersect. */
	वापस p1 & p2;
पूर्ण

/*
 * Returns 1 अगर update has been found, 0 otherwise.
 */
अटल पूर्णांक find_matching_signature(व्योम *mc, अचिन्हित पूर्णांक csig, पूर्णांक cpf)
अणु
	काष्ठा microcode_header_पूर्णांकel *mc_hdr = mc;
	काष्ठा extended_sigtable *ext_hdr;
	काष्ठा extended_signature *ext_sig;
	पूर्णांक i;

	अगर (cpu_signatures_match(csig, cpf, mc_hdr->sig, mc_hdr->pf))
		वापस 1;

	/* Look क्रम ext. headers: */
	अगर (get_totalsize(mc_hdr) <= get_datasize(mc_hdr) + MC_HEADER_SIZE)
		वापस 0;

	ext_hdr = mc + get_datasize(mc_hdr) + MC_HEADER_SIZE;
	ext_sig = (व्योम *)ext_hdr + EXT_HEADER_SIZE;

	क्रम (i = 0; i < ext_hdr->count; i++) अणु
		अगर (cpu_signatures_match(csig, cpf, ext_sig->sig, ext_sig->pf))
			वापस 1;
		ext_sig++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns 1 अगर update has been found, 0 otherwise.
 */
अटल पूर्णांक has_newer_microcode(व्योम *mc, अचिन्हित पूर्णांक csig, पूर्णांक cpf, पूर्णांक new_rev)
अणु
	काष्ठा microcode_header_पूर्णांकel *mc_hdr = mc;

	अगर (mc_hdr->rev <= new_rev)
		वापस 0;

	वापस find_matching_signature(mc, csig, cpf);
पूर्ण

अटल काष्ठा ucode_patch *memdup_patch(व्योम *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा ucode_patch *p;

	p = kzalloc(माप(काष्ठा ucode_patch), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	p->data = kmemdup(data, size, GFP_KERNEL);
	अगर (!p->data) अणु
		kमुक्त(p);
		वापस शून्य;
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम save_microcode_patch(काष्ठा ucode_cpu_info *uci, व्योम *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा microcode_header_पूर्णांकel *mc_hdr, *mc_saved_hdr;
	काष्ठा ucode_patch *iter, *पंचांगp, *p = शून्य;
	bool prev_found = false;
	अचिन्हित पूर्णांक sig, pf;

	mc_hdr = (काष्ठा microcode_header_पूर्णांकel *)data;

	list_क्रम_each_entry_safe(iter, पंचांगp, &microcode_cache, plist) अणु
		mc_saved_hdr = (काष्ठा microcode_header_पूर्णांकel *)iter->data;
		sig	     = mc_saved_hdr->sig;
		pf	     = mc_saved_hdr->pf;

		अगर (find_matching_signature(data, sig, pf)) अणु
			prev_found = true;

			अगर (mc_hdr->rev <= mc_saved_hdr->rev)
				जारी;

			p = memdup_patch(data, size);
			अगर (!p)
				pr_err("Error allocating buffer %p\n", data);
			अन्यथा अणु
				list_replace(&iter->plist, &p->plist);
				kमुक्त(iter->data);
				kमुक्त(iter);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * There weren't any previous patches found in the list cache; save the
	 * newly found.
	 */
	अगर (!prev_found) अणु
		p = memdup_patch(data, size);
		अगर (!p)
			pr_err("Error allocating buffer for %p\n", data);
		अन्यथा
			list_add_tail(&p->plist, &microcode_cache);
	पूर्ण

	अगर (!p)
		वापस;

	अगर (!find_matching_signature(p->data, uci->cpu_sig.sig, uci->cpu_sig.pf))
		वापस;

	/*
	 * Save क्रम early loading. On 32-bit, that needs to be a physical
	 * address as the APs are running from physical addresses, beक्रमe
	 * paging has been enabled.
	 */
	अगर (IS_ENABLED(CONFIG_X86_32))
		पूर्णांकel_ucode_patch = (काष्ठा microcode_पूर्णांकel *)__pa_nodebug(p->data);
	अन्यथा
		पूर्णांकel_ucode_patch = p->data;
पूर्ण

अटल पूर्णांक microcode_sanity_check(व्योम *mc, पूर्णांक prपूर्णांक_err)
अणु
	अचिन्हित दीर्घ total_size, data_size, ext_table_size;
	काष्ठा microcode_header_पूर्णांकel *mc_header = mc;
	काष्ठा extended_sigtable *ext_header = शून्य;
	u32 sum, orig_sum, ext_sigcount = 0, i;
	काष्ठा extended_signature *ext_sig;

	total_size = get_totalsize(mc_header);
	data_size = get_datasize(mc_header);

	अगर (data_size + MC_HEADER_SIZE > total_size) अणु
		अगर (prपूर्णांक_err)
			pr_err("Error: bad microcode data file size.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mc_header->ldrver != 1 || mc_header->hdrver != 1) अणु
		अगर (prपूर्णांक_err)
			pr_err("Error: invalid/unknown microcode update format.\n");
		वापस -EINVAL;
	पूर्ण

	ext_table_size = total_size - (MC_HEADER_SIZE + data_size);
	अगर (ext_table_size) अणु
		u32 ext_table_sum = 0;
		u32 *ext_tablep;

		अगर ((ext_table_size < EXT_HEADER_SIZE)
		 || ((ext_table_size - EXT_HEADER_SIZE) % EXT_SIGNATURE_SIZE)) अणु
			अगर (prपूर्णांक_err)
				pr_err("Error: truncated extended signature table.\n");
			वापस -EINVAL;
		पूर्ण

		ext_header = mc + MC_HEADER_SIZE + data_size;
		अगर (ext_table_size != exttable_size(ext_header)) अणु
			अगर (prपूर्णांक_err)
				pr_err("Error: extended signature table size mismatch.\n");
			वापस -EFAULT;
		पूर्ण

		ext_sigcount = ext_header->count;

		/*
		 * Check extended table checksum: the sum of all dwords that
		 * comprise a valid table must be 0.
		 */
		ext_tablep = (u32 *)ext_header;

		i = ext_table_size / माप(u32);
		जबतक (i--)
			ext_table_sum += ext_tablep[i];

		अगर (ext_table_sum) अणु
			अगर (prपूर्णांक_err)
				pr_warn("Bad extended signature table checksum, aborting.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the checksum of update data and header. The checksum of
	 * valid update data and header including the extended signature table
	 * must be 0.
	 */
	orig_sum = 0;
	i = (MC_HEADER_SIZE + data_size) / माप(u32);
	जबतक (i--)
		orig_sum += ((u32 *)mc)[i];

	अगर (orig_sum) अणु
		अगर (prपूर्णांक_err)
			pr_err("Bad microcode data checksum, aborting.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!ext_table_size)
		वापस 0;

	/*
	 * Check extended signature checksum: 0 => valid.
	 */
	क्रम (i = 0; i < ext_sigcount; i++) अणु
		ext_sig = (व्योम *)ext_header + EXT_HEADER_SIZE +
			  EXT_SIGNATURE_SIZE * i;

		sum = (mc_header->sig + mc_header->pf + mc_header->cksum) -
		      (ext_sig->sig + ext_sig->pf + ext_sig->cksum);
		अगर (sum) अणु
			अगर (prपूर्णांक_err)
				pr_err("Bad extended signature checksum, aborting.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Get microcode matching with BSP's model. Only CPUs with the same model as
 * BSP can stay in the platक्रमm.
 */
अटल काष्ठा microcode_पूर्णांकel *
scan_microcode(व्योम *data, माप_प्रकार size, काष्ठा ucode_cpu_info *uci, bool save)
अणु
	काष्ठा microcode_header_पूर्णांकel *mc_header;
	काष्ठा microcode_पूर्णांकel *patch = शून्य;
	अचिन्हित पूर्णांक mc_size;

	जबतक (size) अणु
		अगर (size < माप(काष्ठा microcode_header_पूर्णांकel))
			अवरोध;

		mc_header = (काष्ठा microcode_header_पूर्णांकel *)data;

		mc_size = get_totalsize(mc_header);
		अगर (!mc_size ||
		    mc_size > size ||
		    microcode_sanity_check(data, 0) < 0)
			अवरोध;

		size -= mc_size;

		अगर (!find_matching_signature(data, uci->cpu_sig.sig,
					     uci->cpu_sig.pf)) अणु
			data += mc_size;
			जारी;
		पूर्ण

		अगर (save) अणु
			save_microcode_patch(uci, data, mc_size);
			जाओ next;
		पूर्ण


		अगर (!patch) अणु
			अगर (!has_newer_microcode(data,
						 uci->cpu_sig.sig,
						 uci->cpu_sig.pf,
						 uci->cpu_sig.rev))
				जाओ next;

		पूर्ण अन्यथा अणु
			काष्ठा microcode_header_पूर्णांकel *phdr = &patch->hdr;

			अगर (!has_newer_microcode(data,
						 phdr->sig,
						 phdr->pf,
						 phdr->rev))
				जाओ next;
		पूर्ण

		/* We have a newer patch, save it. */
		patch = data;

next:
		data += mc_size;
	पूर्ण

	अगर (size)
		वापस शून्य;

	वापस patch;
पूर्ण

अटल पूर्णांक collect_cpu_info_early(काष्ठा ucode_cpu_info *uci)
अणु
	अचिन्हित पूर्णांक val[2];
	अचिन्हित पूर्णांक family, model;
	काष्ठा cpu_signature csig = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	स_रखो(uci, 0, माप(*uci));

	eax = 0x00000001;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	csig.sig = eax;

	family = x86_family(eax);
	model  = x86_model(eax);

	अगर ((model >= 5) || (family > 6)) अणु
		/* get processor flags from MSR 0x17 */
		native_rdmsr(MSR_IA32_PLATFORM_ID, val[0], val[1]);
		csig.pf = 1 << ((val[1] >> 18) & 7);
	पूर्ण

	csig.rev = पूर्णांकel_get_microcode_revision();

	uci->cpu_sig = csig;
	uci->valid = 1;

	वापस 0;
पूर्ण

अटल व्योम show_saved_mc(व्योम)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i = 0, j;
	अचिन्हित पूर्णांक sig, pf, rev, total_size, data_size, date;
	काष्ठा ucode_cpu_info uci;
	काष्ठा ucode_patch *p;

	अगर (list_empty(&microcode_cache)) अणु
		pr_debug("no microcode data saved.\n");
		वापस;
	पूर्ण

	collect_cpu_info_early(&uci);

	sig	= uci.cpu_sig.sig;
	pf	= uci.cpu_sig.pf;
	rev	= uci.cpu_sig.rev;
	pr_debug("CPU: sig=0x%x, pf=0x%x, rev=0x%x\n", sig, pf, rev);

	list_क्रम_each_entry(p, &microcode_cache, plist) अणु
		काष्ठा microcode_header_पूर्णांकel *mc_saved_header;
		काष्ठा extended_sigtable *ext_header;
		काष्ठा extended_signature *ext_sig;
		पूर्णांक ext_sigcount;

		mc_saved_header = (काष्ठा microcode_header_पूर्णांकel *)p->data;

		sig	= mc_saved_header->sig;
		pf	= mc_saved_header->pf;
		rev	= mc_saved_header->rev;
		date	= mc_saved_header->date;

		total_size	= get_totalsize(mc_saved_header);
		data_size	= get_datasize(mc_saved_header);

		pr_debug("mc_saved[%d]: sig=0x%x, pf=0x%x, rev=0x%x, total size=0x%x, date = %04x-%02x-%02x\n",
			 i++, sig, pf, rev, total_size,
			 date & 0xffff,
			 date >> 24,
			 (date >> 16) & 0xff);

		/* Look क्रम ext. headers: */
		अगर (total_size <= data_size + MC_HEADER_SIZE)
			जारी;

		ext_header = (व्योम *)mc_saved_header + data_size + MC_HEADER_SIZE;
		ext_sigcount = ext_header->count;
		ext_sig = (व्योम *)ext_header + EXT_HEADER_SIZE;

		क्रम (j = 0; j < ext_sigcount; j++) अणु
			sig = ext_sig->sig;
			pf = ext_sig->pf;

			pr_debug("\tExtended[%d]: sig=0x%x, pf=0x%x\n",
				 j, sig, pf);

			ext_sig++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Save this microcode patch. It will be loaded early when a CPU is
 * hot-added or resumes.
 */
अटल व्योम save_mc_क्रम_early(काष्ठा ucode_cpu_info *uci, u8 *mc, अचिन्हित पूर्णांक size)
अणु
	/* Synchronization during CPU hotplug. */
	अटल DEFINE_MUTEX(x86_cpu_microcode_mutex);

	mutex_lock(&x86_cpu_microcode_mutex);

	save_microcode_patch(uci, mc, size);
	show_saved_mc();

	mutex_unlock(&x86_cpu_microcode_mutex);
पूर्ण

अटल bool load_builtin_पूर्णांकel_microcode(काष्ठा cpio_data *cp)
अणु
	अचिन्हित पूर्णांक eax = 1, ebx, ecx = 0, edx;
	अक्षर name[30];

	अगर (IS_ENABLED(CONFIG_X86_32))
		वापस false;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	प्र_लिखो(name, "intel-ucode/%02x-%02x-%02x",
		      x86_family(eax), x86_model(eax), x86_stepping(eax));

	वापस get_builtin_firmware(cp, name);
पूर्ण

/*
 * Prपूर्णांक ucode update info.
 */
अटल व्योम
prपूर्णांक_ucode_info(काष्ठा ucode_cpu_info *uci, अचिन्हित पूर्णांक date)
अणु
	pr_info_once("microcode updated early to revision 0x%x, date = %04x-%02x-%02x\n",
		     uci->cpu_sig.rev,
		     date & 0xffff,
		     date >> 24,
		     (date >> 16) & 0xff);
पूर्ण

#अगर_घोषित CONFIG_X86_32

अटल पूर्णांक delay_ucode_info;
अटल पूर्णांक current_mc_date;

/*
 * Prपूर्णांक early updated ucode info after prपूर्णांकk works. This is delayed info dump.
 */
व्योम show_ucode_info_early(व्योम)
अणु
	काष्ठा ucode_cpu_info uci;

	अगर (delay_ucode_info) अणु
		collect_cpu_info_early(&uci);
		prपूर्णांक_ucode_info(&uci, current_mc_date);
		delay_ucode_info = 0;
	पूर्ण
पूर्ण

/*
 * At this poपूर्णांक, we can not call prपूर्णांकk() yet. Delay prपूर्णांकing microcode info in
 * show_ucode_info_early() until prपूर्णांकk() works.
 */
अटल व्योम prपूर्णांक_ucode(काष्ठा ucode_cpu_info *uci)
अणु
	काष्ठा microcode_पूर्णांकel *mc;
	पूर्णांक *delay_ucode_info_p;
	पूर्णांक *current_mc_date_p;

	mc = uci->mc;
	अगर (!mc)
		वापस;

	delay_ucode_info_p = (पूर्णांक *)__pa_nodebug(&delay_ucode_info);
	current_mc_date_p = (पूर्णांक *)__pa_nodebug(&current_mc_date);

	*delay_ucode_info_p = 1;
	*current_mc_date_p = mc->hdr.date;
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम prपूर्णांक_ucode(काष्ठा ucode_cpu_info *uci)
अणु
	काष्ठा microcode_पूर्णांकel *mc;

	mc = uci->mc;
	अगर (!mc)
		वापस;

	prपूर्णांक_ucode_info(uci, mc->hdr.date);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक apply_microcode_early(काष्ठा ucode_cpu_info *uci, bool early)
अणु
	काष्ठा microcode_पूर्णांकel *mc;
	u32 rev;

	mc = uci->mc;
	अगर (!mc)
		वापस 0;

	/*
	 * Save us the MSR ग_लिखो below - which is a particular expensive
	 * operation - when the other hyperthपढ़ो has updated the microcode
	 * alपढ़ोy.
	 */
	rev = पूर्णांकel_get_microcode_revision();
	अगर (rev >= mc->hdr.rev) अणु
		uci->cpu_sig.rev = rev;
		वापस UCODE_OK;
	पूर्ण

	/*
	 * Writeback and invalidate caches beक्रमe updating microcode to aव्योम
	 * पूर्णांकernal issues depending on what the microcode is updating.
	 */
	native_wbinvd();

	/* ग_लिखो microcode via MSR 0x79 */
	native_wrmsrl(MSR_IA32_UCODE_WRITE, (अचिन्हित दीर्घ)mc->bits);

	rev = पूर्णांकel_get_microcode_revision();
	अगर (rev != mc->hdr.rev)
		वापस -1;

	uci->cpu_sig.rev = rev;

	अगर (early)
		prपूर्णांक_ucode(uci);
	अन्यथा
		prपूर्णांक_ucode_info(uci, mc->hdr.date);

	वापस 0;
पूर्ण

पूर्णांक __init save_microcode_in_initrd_पूर्णांकel(व्योम)
अणु
	काष्ठा ucode_cpu_info uci;
	काष्ठा cpio_data cp;

	/*
	 * initrd is going away, clear patch ptr. We will scan the microcode one
	 * last समय beक्रमe jettisoning and save a patch, अगर found. Then we will
	 * update that poपूर्णांकer too, with a stable patch address to use when
	 * resuming the cores.
	 */
	पूर्णांकel_ucode_patch = शून्य;

	अगर (!load_builtin_पूर्णांकel_microcode(&cp))
		cp = find_microcode_in_initrd(ucode_path, false);

	अगर (!(cp.data && cp.size))
		वापस 0;

	collect_cpu_info_early(&uci);

	scan_microcode(cp.data, cp.size, &uci, true);

	show_saved_mc();

	वापस 0;
पूर्ण

/*
 * @res_patch, output: a poपूर्णांकer to the patch we found.
 */
अटल काष्ठा microcode_पूर्णांकel *__load_ucode_पूर्णांकel(काष्ठा ucode_cpu_info *uci)
अणु
	अटल स्थिर अक्षर *path;
	काष्ठा cpio_data cp;
	bool use_pa;

	अगर (IS_ENABLED(CONFIG_X86_32)) अणु
		path	  = (स्थिर अक्षर *)__pa_nodebug(ucode_path);
		use_pa	  = true;
	पूर्ण अन्यथा अणु
		path	  = ucode_path;
		use_pa	  = false;
	पूर्ण

	/* try built-in microcode first */
	अगर (!load_builtin_पूर्णांकel_microcode(&cp))
		cp = find_microcode_in_initrd(path, use_pa);

	अगर (!(cp.data && cp.size))
		वापस शून्य;

	collect_cpu_info_early(uci);

	वापस scan_microcode(cp.data, cp.size, uci, false);
पूर्ण

व्योम __init load_ucode_पूर्णांकel_bsp(व्योम)
अणु
	काष्ठा microcode_पूर्णांकel *patch;
	काष्ठा ucode_cpu_info uci;

	patch = __load_ucode_पूर्णांकel(&uci);
	अगर (!patch)
		वापस;

	uci.mc = patch;

	apply_microcode_early(&uci, true);
पूर्ण

व्योम load_ucode_पूर्णांकel_ap(व्योम)
अणु
	काष्ठा microcode_पूर्णांकel *patch, **iup;
	काष्ठा ucode_cpu_info uci;

	अगर (IS_ENABLED(CONFIG_X86_32))
		iup = (काष्ठा microcode_पूर्णांकel **) __pa_nodebug(&पूर्णांकel_ucode_patch);
	अन्यथा
		iup = &पूर्णांकel_ucode_patch;

reget:
	अगर (!*iup) अणु
		patch = __load_ucode_पूर्णांकel(&uci);
		अगर (!patch)
			वापस;

		*iup = patch;
	पूर्ण

	uci.mc = *iup;

	अगर (apply_microcode_early(&uci, true)) अणु
		/* Mixed-silicon प्रणाली? Try to refetch the proper patch: */
		*iup = शून्य;

		जाओ reget;
	पूर्ण
पूर्ण

अटल काष्ठा microcode_पूर्णांकel *find_patch(काष्ठा ucode_cpu_info *uci)
अणु
	काष्ठा microcode_header_पूर्णांकel *phdr;
	काष्ठा ucode_patch *iter, *पंचांगp;

	list_क्रम_each_entry_safe(iter, पंचांगp, &microcode_cache, plist) अणु

		phdr = (काष्ठा microcode_header_पूर्णांकel *)iter->data;

		अगर (phdr->rev <= uci->cpu_sig.rev)
			जारी;

		अगर (!find_matching_signature(phdr,
					     uci->cpu_sig.sig,
					     uci->cpu_sig.pf))
			जारी;

		वापस iter->data;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम reload_ucode_पूर्णांकel(व्योम)
अणु
	काष्ठा microcode_पूर्णांकel *p;
	काष्ठा ucode_cpu_info uci;

	collect_cpu_info_early(&uci);

	p = find_patch(&uci);
	अगर (!p)
		वापस;

	uci.mc = p;

	apply_microcode_early(&uci, false);
पूर्ण

अटल पूर्णांक collect_cpu_info(पूर्णांक cpu_num, काष्ठा cpu_signature *csig)
अणु
	अटल काष्ठा cpu_signature prev;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu_num);
	अचिन्हित पूर्णांक val[2];

	स_रखो(csig, 0, माप(*csig));

	csig->sig = cpuid_eax(0x00000001);

	अगर ((c->x86_model >= 5) || (c->x86 > 6)) अणु
		/* get processor flags from MSR 0x17 */
		rdmsr(MSR_IA32_PLATFORM_ID, val[0], val[1]);
		csig->pf = 1 << ((val[1] >> 18) & 7);
	पूर्ण

	csig->rev = c->microcode;

	/* No extra locking on prev, races are harmless. */
	अगर (csig->sig != prev.sig || csig->pf != prev.pf || csig->rev != prev.rev) अणु
		pr_info("sig=0x%x, pf=0x%x, revision=0x%x\n",
			csig->sig, csig->pf, csig->rev);
		prev = *csig;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत ucode_state apply_microcode_पूर्णांकel(पूर्णांक cpu)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	bool bsp = c->cpu_index == boot_cpu_data.cpu_index;
	काष्ठा microcode_पूर्णांकel *mc;
	क्रमागत ucode_state ret;
	अटल पूर्णांक prev_rev;
	u32 rev;

	/* We should bind the task to the CPU */
	अगर (WARN_ON(raw_smp_processor_id() != cpu))
		वापस UCODE_ERROR;

	/* Look क्रम a newer patch in our cache: */
	mc = find_patch(uci);
	अगर (!mc) अणु
		mc = uci->mc;
		अगर (!mc)
			वापस UCODE_NFOUND;
	पूर्ण

	/*
	 * Save us the MSR ग_लिखो below - which is a particular expensive
	 * operation - when the other hyperthपढ़ो has updated the microcode
	 * alपढ़ोy.
	 */
	rev = पूर्णांकel_get_microcode_revision();
	अगर (rev >= mc->hdr.rev) अणु
		ret = UCODE_OK;
		जाओ out;
	पूर्ण

	/*
	 * Writeback and invalidate caches beक्रमe updating microcode to aव्योम
	 * पूर्णांकernal issues depending on what the microcode is updating.
	 */
	native_wbinvd();

	/* ग_लिखो microcode via MSR 0x79 */
	wrmsrl(MSR_IA32_UCODE_WRITE, (अचिन्हित दीर्घ)mc->bits);

	rev = पूर्णांकel_get_microcode_revision();

	अगर (rev != mc->hdr.rev) अणु
		pr_err("CPU%d update to revision 0x%x failed\n",
		       cpu, mc->hdr.rev);
		वापस UCODE_ERROR;
	पूर्ण

	अगर (bsp && rev != prev_rev) अणु
		pr_info("updated to revision 0x%x, date = %04x-%02x-%02x\n",
			rev,
			mc->hdr.date & 0xffff,
			mc->hdr.date >> 24,
			(mc->hdr.date >> 16) & 0xff);
		prev_rev = rev;
	पूर्ण

	ret = UCODE_UPDATED;

out:
	uci->cpu_sig.rev = rev;
	c->microcode	 = rev;

	/* Update boot_cpu_data's revision too, if we're on the BSP: */
	अगर (bsp)
		boot_cpu_data.microcode = rev;

	वापस ret;
पूर्ण

अटल क्रमागत ucode_state generic_load_microcode(पूर्णांक cpu, काष्ठा iov_iter *iter)
अणु
	काष्ठा ucode_cpu_info *uci = ucode_cpu_info + cpu;
	अचिन्हित पूर्णांक curr_mc_size = 0, new_mc_size = 0;
	क्रमागत ucode_state ret = UCODE_OK;
	पूर्णांक new_rev = uci->cpu_sig.rev;
	u8 *new_mc = शून्य, *mc = शून्य;
	अचिन्हित पूर्णांक csig, cpf;

	जबतक (iov_iter_count(iter)) अणु
		काष्ठा microcode_header_पूर्णांकel mc_header;
		अचिन्हित पूर्णांक mc_size, data_size;
		u8 *data;

		अगर (!copy_from_iter_full(&mc_header, माप(mc_header), iter)) अणु
			pr_err("error! Truncated or inaccessible header in microcode data file\n");
			अवरोध;
		पूर्ण

		mc_size = get_totalsize(&mc_header);
		अगर (mc_size < माप(mc_header)) अणु
			pr_err("error! Bad data in microcode data file (totalsize too small)\n");
			अवरोध;
		पूर्ण
		data_size = mc_size - माप(mc_header);
		अगर (data_size > iov_iter_count(iter)) अणु
			pr_err("error! Bad data in microcode data file (truncated file?)\n");
			अवरोध;
		पूर्ण

		/* For perक्रमmance reasons, reuse mc area when possible */
		अगर (!mc || mc_size > curr_mc_size) अणु
			vमुक्त(mc);
			mc = vदो_स्मृति(mc_size);
			अगर (!mc)
				अवरोध;
			curr_mc_size = mc_size;
		पूर्ण

		स_नकल(mc, &mc_header, माप(mc_header));
		data = mc + माप(mc_header);
		अगर (!copy_from_iter_full(data, data_size, iter) ||
		    microcode_sanity_check(mc, 1) < 0) अणु
			अवरोध;
		पूर्ण

		csig = uci->cpu_sig.sig;
		cpf = uci->cpu_sig.pf;
		अगर (has_newer_microcode(mc, csig, cpf, new_rev)) अणु
			vमुक्त(new_mc);
			new_rev = mc_header.rev;
			new_mc  = mc;
			new_mc_size = mc_size;
			mc = शून्य;	/* trigger new vदो_स्मृति */
			ret = UCODE_NEW;
		पूर्ण
	पूर्ण

	vमुक्त(mc);

	अगर (iov_iter_count(iter)) अणु
		vमुक्त(new_mc);
		वापस UCODE_ERROR;
	पूर्ण

	अगर (!new_mc)
		वापस UCODE_NFOUND;

	vमुक्त(uci->mc);
	uci->mc = (काष्ठा microcode_पूर्णांकel *)new_mc;

	/*
	 * If early loading microcode is supported, save this mc पूर्णांकo
	 * permanent memory. So it will be loaded early when a CPU is hot added
	 * or resumes.
	 */
	save_mc_क्रम_early(uci, new_mc, new_mc_size);

	pr_debug("CPU%d found a matching microcode update with version 0x%x (current=0x%x)\n",
		 cpu, new_rev, uci->cpu_sig.rev);

	वापस ret;
पूर्ण

अटल bool is_blacklisted(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	/*
	 * Late loading on model 79 with microcode revision less than 0x0b000021
	 * and LLC size per core bigger than 2.5MB may result in a प्रणाली hang.
	 * This behavior is करोcumented in item BDF90, #334165 (Intel Xeon
	 * Processor E7-8800/4800 v4 Product Family).
	 */
	अगर (c->x86 == 6 &&
	    c->x86_model == INTEL_FAM6_BROADWELL_X &&
	    c->x86_stepping == 0x01 &&
	    llc_size_per_core > 2621440 &&
	    c->microcode < 0x0b000021) अणु
		pr_err_once("Erratum BDF90: late loading with revision < 0x0b000021 (0x%x) disabled.\n", c->microcode);
		pr_err_once("Please consider either early loading through initrd/built-in or a potential BIOS update.\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत ucode_state request_microcode_fw(पूर्णांक cpu, काष्ठा device *device,
					     bool refresh_fw)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	स्थिर काष्ठा firmware *firmware;
	काष्ठा iov_iter iter;
	क्रमागत ucode_state ret;
	काष्ठा kvec kvec;
	अक्षर name[30];

	अगर (is_blacklisted(cpu))
		वापस UCODE_NFOUND;

	प्र_लिखो(name, "intel-ucode/%02x-%02x-%02x",
		c->x86, c->x86_model, c->x86_stepping);

	अगर (request_firmware_direct(&firmware, name, device)) अणु
		pr_debug("data file %s load failed\n", name);
		वापस UCODE_NFOUND;
	पूर्ण

	kvec.iov_base = (व्योम *)firmware->data;
	kvec.iov_len = firmware->size;
	iov_iter_kvec(&iter, WRITE, &kvec, 1, firmware->size);
	ret = generic_load_microcode(cpu, &iter);

	release_firmware(firmware);

	वापस ret;
पूर्ण

अटल क्रमागत ucode_state
request_microcode_user(पूर्णांक cpu, स्थिर व्योम __user *buf, माप_प्रकार size)
अणु
	काष्ठा iov_iter iter;
	काष्ठा iovec iov;

	अगर (is_blacklisted(cpu))
		वापस UCODE_NFOUND;

	iov.iov_base = (व्योम __user *)buf;
	iov.iov_len = size;
	iov_iter_init(&iter, WRITE, &iov, 1, size);

	वापस generic_load_microcode(cpu, &iter);
पूर्ण

अटल काष्ठा microcode_ops microcode_पूर्णांकel_ops = अणु
	.request_microcode_user		  = request_microcode_user,
	.request_microcode_fw             = request_microcode_fw,
	.collect_cpu_info                 = collect_cpu_info,
	.apply_microcode                  = apply_microcode_पूर्णांकel,
पूर्ण;

अटल पूर्णांक __init calc_llc_size_per_core(काष्ठा cpuinfo_x86 *c)
अणु
	u64 llc_size = c->x86_cache_size * 1024ULL;

	करो_भाग(llc_size, c->x86_max_cores);

	वापस (पूर्णांक)llc_size;
पूर्ण

काष्ठा microcode_ops * __init init_पूर्णांकel_microcode(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर (c->x86_venकरोr != X86_VENDOR_INTEL || c->x86 < 6 ||
	    cpu_has(c, X86_FEATURE_IA64)) अणु
		pr_err("Intel CPU family 0x%x not supported\n", c->x86);
		वापस शून्य;
	पूर्ण

	llc_size_per_core = calc_llc_size_per_core(c);

	वापस &microcode_पूर्णांकel_ops;
पूर्ण
