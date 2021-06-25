<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * crash.c - kernel crash support code.
 * Copyright (C) 2002-2004 Eric Biederman  <ebiederm@xmission.com>
 */

#समावेश <linux/crash_core.h>
#समावेश <linux/utsname.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

#समावेश <crypto/sha1.h>

/* vmcoreinfo stuff */
अचिन्हित अक्षर *vmcoreinfo_data;
माप_प्रकार vmcoreinfo_size;
u32 *vmcoreinfo_note;

/* trusted vmcoreinfo, e.g. we can make a copy in the crash memory */
अटल अचिन्हित अक्षर *vmcoreinfo_data_safecopy;

/*
 * parsing the "crashkernel" commandline
 *
 * this code is पूर्णांकended to be called from architecture specअगरic code
 */


/*
 * This function parses command lines in the क्रमmat
 *
 *   crashkernel=ramsize-range:size[,...][@offset]
 *
 * The function वापसs 0 on success and -EINVAL on failure.
 */
अटल पूर्णांक __init parse_crashkernel_mem(अक्षर *cmdline,
					अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
					अचिन्हित दीर्घ दीर्घ *crash_size,
					अचिन्हित दीर्घ दीर्घ *crash_base)
अणु
	अक्षर *cur = cmdline, *पंचांगp;

	/* क्रम each entry of the comma-separated list */
	करो अणु
		अचिन्हित दीर्घ दीर्घ start, end = ULदीर्घ_उच्च, size;

		/* get the start of the range */
		start = memparse(cur, &पंचांगp);
		अगर (cur == पंचांगp) अणु
			pr_warn("crashkernel: Memory value expected\n");
			वापस -EINVAL;
		पूर्ण
		cur = पंचांगp;
		अगर (*cur != '-') अणु
			pr_warn("crashkernel: '-' expected\n");
			वापस -EINVAL;
		पूर्ण
		cur++;

		/* अगर no ':' is here, than we पढ़ो the end */
		अगर (*cur != ':') अणु
			end = memparse(cur, &पंचांगp);
			अगर (cur == पंचांगp) अणु
				pr_warn("crashkernel: Memory value expected\n");
				वापस -EINVAL;
			पूर्ण
			cur = पंचांगp;
			अगर (end <= start) अणु
				pr_warn("crashkernel: end <= start\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (*cur != ':') अणु
			pr_warn("crashkernel: ':' expected\n");
			वापस -EINVAL;
		पूर्ण
		cur++;

		size = memparse(cur, &पंचांगp);
		अगर (cur == पंचांगp) अणु
			pr_warn("Memory value expected\n");
			वापस -EINVAL;
		पूर्ण
		cur = पंचांगp;
		अगर (size >= प्रणाली_ram) अणु
			pr_warn("crashkernel: invalid size\n");
			वापस -EINVAL;
		पूर्ण

		/* match ? */
		अगर (प्रणाली_ram >= start && प्रणाली_ram < end) अणु
			*crash_size = size;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (*cur++ == ',');

	अगर (*crash_size > 0) अणु
		जबतक (*cur && *cur != ' ' && *cur != '@')
			cur++;
		अगर (*cur == '@') अणु
			cur++;
			*crash_base = memparse(cur, &पंचांगp);
			अगर (cur == पंचांगp) अणु
				pr_warn("Memory value expected after '@'\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		pr_info("crashkernel size resulted in zero bytes\n");

	वापस 0;
पूर्ण

/*
 * That function parses "simple" (old) crashkernel command lines like
 *
 *	crashkernel=size[@offset]
 *
 * It वापसs 0 on success and -EINVAL on failure.
 */
अटल पूर्णांक __init parse_crashkernel_simple(अक्षर *cmdline,
					   अचिन्हित दीर्घ दीर्घ *crash_size,
					   अचिन्हित दीर्घ दीर्घ *crash_base)
अणु
	अक्षर *cur = cmdline;

	*crash_size = memparse(cmdline, &cur);
	अगर (cmdline == cur) अणु
		pr_warn("crashkernel: memory value expected\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*cur == '@')
		*crash_base = memparse(cur+1, &cur);
	अन्यथा अगर (*cur != ' ' && *cur != '\0') अणु
		pr_warn("crashkernel: unrecognized char: %c\n", *cur);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SUFFIX_HIGH 0
#घोषणा SUFFIX_LOW  1
#घोषणा SUFFIX_शून्य 2
अटल __initdata अक्षर *suffix_tbl[] = अणु
	[SUFFIX_HIGH] = ",high",
	[SUFFIX_LOW]  = ",low",
	[SUFFIX_शून्य] = शून्य,
पूर्ण;

/*
 * That function parses "suffix"  crashkernel command lines like
 *
 *	crashkernel=size,[high|low]
 *
 * It वापसs 0 on success and -EINVAL on failure.
 */
अटल पूर्णांक __init parse_crashkernel_suffix(अक्षर *cmdline,
					   अचिन्हित दीर्घ दीर्घ	*crash_size,
					   स्थिर अक्षर *suffix)
अणु
	अक्षर *cur = cmdline;

	*crash_size = memparse(cmdline, &cur);
	अगर (cmdline == cur) अणु
		pr_warn("crashkernel: memory value expected\n");
		वापस -EINVAL;
	पूर्ण

	/* check with suffix */
	अगर (म_भेदन(cur, suffix, म_माप(suffix))) अणु
		pr_warn("crashkernel: unrecognized char: %c\n", *cur);
		वापस -EINVAL;
	पूर्ण
	cur += म_माप(suffix);
	अगर (*cur != ' ' && *cur != '\0') अणु
		pr_warn("crashkernel: unrecognized char: %c\n", *cur);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init अक्षर *get_last_crashkernel(अक्षर *cmdline,
			     स्थिर अक्षर *name,
			     स्थिर अक्षर *suffix)
अणु
	अक्षर *p = cmdline, *ck_cmdline = शून्य;

	/* find crashkernel and use the last one अगर there are more */
	p = म_माला(p, name);
	जबतक (p) अणु
		अक्षर *end_p = म_अक्षर(p, ' ');
		अक्षर *q;

		अगर (!end_p)
			end_p = p + म_माप(p);

		अगर (!suffix) अणु
			पूर्णांक i;

			/* skip the one with any known suffix */
			क्रम (i = 0; suffix_tbl[i]; i++) अणु
				q = end_p - म_माप(suffix_tbl[i]);
				अगर (!म_भेदन(q, suffix_tbl[i],
					     म_माप(suffix_tbl[i])))
					जाओ next;
			पूर्ण
			ck_cmdline = p;
		पूर्ण अन्यथा अणु
			q = end_p - म_माप(suffix);
			अगर (!म_भेदन(q, suffix, म_माप(suffix)))
				ck_cmdline = p;
		पूर्ण
next:
		p = म_माला(p+1, name);
	पूर्ण

	अगर (!ck_cmdline)
		वापस शून्य;

	वापस ck_cmdline;
पूर्ण

अटल पूर्णांक __init __parse_crashkernel(अक्षर *cmdline,
			     अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
			     अचिन्हित दीर्घ दीर्घ *crash_size,
			     अचिन्हित दीर्घ दीर्घ *crash_base,
			     स्थिर अक्षर *name,
			     स्थिर अक्षर *suffix)
अणु
	अक्षर	*first_colon, *first_space;
	अक्षर	*ck_cmdline;

	BUG_ON(!crash_size || !crash_base);
	*crash_size = 0;
	*crash_base = 0;

	ck_cmdline = get_last_crashkernel(cmdline, name, suffix);

	अगर (!ck_cmdline)
		वापस -EINVAL;

	ck_cmdline += म_माप(name);

	अगर (suffix)
		वापस parse_crashkernel_suffix(ck_cmdline, crash_size,
				suffix);
	/*
	 * अगर the commandline contains a ':', then that's the extended
	 * syntax -- अगर not, it must be the classic syntax
	 */
	first_colon = म_अक्षर(ck_cmdline, ':');
	first_space = म_अक्षर(ck_cmdline, ' ');
	अगर (first_colon && (!first_space || first_colon < first_space))
		वापस parse_crashkernel_mem(ck_cmdline, प्रणाली_ram,
				crash_size, crash_base);

	वापस parse_crashkernel_simple(ck_cmdline, crash_size, crash_base);
पूर्ण

/*
 * That function is the entry poपूर्णांक क्रम command line parsing and should be
 * called from the arch-specअगरic code.
 */
पूर्णांक __init parse_crashkernel(अक्षर *cmdline,
			     अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
			     अचिन्हित दीर्घ दीर्घ *crash_size,
			     अचिन्हित दीर्घ दीर्घ *crash_base)
अणु
	वापस __parse_crashkernel(cmdline, प्रणाली_ram, crash_size, crash_base,
					"crashkernel=", शून्य);
पूर्ण

पूर्णांक __init parse_crashkernel_high(अक्षर *cmdline,
			     अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
			     अचिन्हित दीर्घ दीर्घ *crash_size,
			     अचिन्हित दीर्घ दीर्घ *crash_base)
अणु
	वापस __parse_crashkernel(cmdline, प्रणाली_ram, crash_size, crash_base,
				"crashkernel=", suffix_tbl[SUFFIX_HIGH]);
पूर्ण

पूर्णांक __init parse_crashkernel_low(अक्षर *cmdline,
			     अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
			     अचिन्हित दीर्घ दीर्घ *crash_size,
			     अचिन्हित दीर्घ दीर्घ *crash_base)
अणु
	वापस __parse_crashkernel(cmdline, प्रणाली_ram, crash_size, crash_base,
				"crashkernel=", suffix_tbl[SUFFIX_LOW]);
पूर्ण

Elf_Word *append_elf_note(Elf_Word *buf, अक्षर *name, अचिन्हित पूर्णांक type,
			  व्योम *data, माप_प्रकार data_len)
अणु
	काष्ठा elf_note *note = (काष्ठा elf_note *)buf;

	note->n_namesz = म_माप(name) + 1;
	note->n_descsz = data_len;
	note->n_type   = type;
	buf += DIV_ROUND_UP(माप(*note), माप(Elf_Word));
	स_नकल(buf, name, note->n_namesz);
	buf += DIV_ROUND_UP(note->n_namesz, माप(Elf_Word));
	स_नकल(buf, data, data_len);
	buf += DIV_ROUND_UP(data_len, माप(Elf_Word));

	वापस buf;
पूर्ण

व्योम final_note(Elf_Word *buf)
अणु
	स_रखो(buf, 0, माप(काष्ठा elf_note));
पूर्ण

अटल व्योम update_vmcoreinfo_note(व्योम)
अणु
	u32 *buf = vmcoreinfo_note;

	अगर (!vmcoreinfo_size)
		वापस;
	buf = append_elf_note(buf, VMCOREINFO_NOTE_NAME, 0, vmcoreinfo_data,
			      vmcoreinfo_size);
	final_note(buf);
पूर्ण

व्योम crash_update_vmcoreinfo_safecopy(व्योम *ptr)
अणु
	अगर (ptr)
		स_नकल(ptr, vmcoreinfo_data, vmcoreinfo_size);

	vmcoreinfo_data_safecopy = ptr;
पूर्ण

व्योम crash_save_vmcoreinfo(व्योम)
अणु
	अगर (!vmcoreinfo_note)
		वापस;

	/* Use the safe copy to generate vmcoreinfo note अगर have */
	अगर (vmcoreinfo_data_safecopy)
		vmcoreinfo_data = vmcoreinfo_data_safecopy;

	vmcoreinfo_append_str("CRASHTIME=%lld\n", kसमय_get_real_seconds());
	update_vmcoreinfo_note();
पूर्ण

व्योम vmcoreinfo_append_str(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[0x50];
	माप_प्रकार r;

	बहु_शुरू(args, fmt);
	r = vscnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	r = min(r, (माप_प्रकार)VMCOREINFO_BYTES - vmcoreinfo_size);

	स_नकल(&vmcoreinfo_data[vmcoreinfo_size], buf, r);

	vmcoreinfo_size += r;
पूर्ण

/*
 * provide an empty शेष implementation here -- architecture
 * code may override this
 */
व्योम __weak arch_crash_save_vmcoreinfo(व्योम)
अणुपूर्ण

phys_addr_t __weak paddr_vmcoreinfo_note(व्योम)
अणु
	वापस __pa(vmcoreinfo_note);
पूर्ण
EXPORT_SYMBOL(paddr_vmcoreinfo_note);

#घोषणा NOTES_SIZE (&__stop_notes - &__start_notes)
#घोषणा BUILD_ID_MAX SHA1_DIGEST_SIZE
#घोषणा NT_GNU_BUILD_ID 3

काष्ठा elf_note_section अणु
	काष्ठा elf_note	n_hdr;
	u8 n_data[];
पूर्ण;

/*
 * Add build ID from .notes section as generated by the GNU ld(1)
 * or LLVM lld(1) --build-id option.
 */
अटल व्योम add_build_id_vmcoreinfo(व्योम)
अणु
	अक्षर build_id[BUILD_ID_MAX * 2 + 1];
	पूर्णांक n_reमुख्य = NOTES_SIZE;

	जबतक (n_reमुख्य >= माप(काष्ठा elf_note)) अणु
		स्थिर काष्ठा elf_note_section *note_sec =
			&__start_notes + NOTES_SIZE - n_reमुख्य;
		स्थिर u32 n_namesz = note_sec->n_hdr.n_namesz;

		अगर (note_sec->n_hdr.n_type == NT_GNU_BUILD_ID &&
		    n_namesz != 0 &&
		    !म_भेद((अक्षर *)&note_sec->n_data[0], "GNU")) अणु
			अगर (note_sec->n_hdr.n_descsz <= BUILD_ID_MAX) अणु
				स्थिर u32 n_descsz = note_sec->n_hdr.n_descsz;
				स्थिर u8 *s = &note_sec->n_data[n_namesz];

				s = PTR_ALIGN(s, 4);
				bin2hex(build_id, s, n_descsz);
				build_id[2 * n_descsz] = '\0';
				VMCOREINFO_BUILD_ID(build_id);
				वापस;
			पूर्ण
			pr_warn("Build ID is too large to include in vmcoreinfo: %u > %u\n",
				note_sec->n_hdr.n_descsz,
				BUILD_ID_MAX);
			वापस;
		पूर्ण
		n_reमुख्य -= माप(काष्ठा elf_note) +
			ALIGN(note_sec->n_hdr.n_namesz, 4) +
			ALIGN(note_sec->n_hdr.n_descsz, 4);
	पूर्ण
पूर्ण

अटल पूर्णांक __init crash_save_vmcoreinfo_init(व्योम)
अणु
	vmcoreinfo_data = (अचिन्हित अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!vmcoreinfo_data) अणु
		pr_warn("Memory allocation for vmcoreinfo_data failed\n");
		वापस -ENOMEM;
	पूर्ण

	vmcoreinfo_note = alloc_pages_exact(VMCOREINFO_NOTE_SIZE,
						GFP_KERNEL | __GFP_ZERO);
	अगर (!vmcoreinfo_note) अणु
		मुक्त_page((अचिन्हित दीर्घ)vmcoreinfo_data);
		vmcoreinfo_data = शून्य;
		pr_warn("Memory allocation for vmcoreinfo_note failed\n");
		वापस -ENOMEM;
	पूर्ण

	VMCOREINFO_OSRELEASE(init_uts_ns.name.release);
	add_build_id_vmcoreinfo();
	VMCOREINFO_PAGESIZE(PAGE_SIZE);

	VMCOREINFO_SYMBOL(init_uts_ns);
	VMCOREINFO_OFFSET(uts_namespace, name);
	VMCOREINFO_SYMBOL(node_online_map);
#अगर_घोषित CONFIG_MMU
	VMCOREINFO_SYMBOL_ARRAY(swapper_pg_dir);
#पूर्ण_अगर
	VMCOREINFO_SYMBOL(_stext);
	VMCOREINFO_SYMBOL(vmap_area_list);

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
	VMCOREINFO_SYMBOL(mem_map);
	VMCOREINFO_SYMBOL(contig_page_data);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARSEMEM
	VMCOREINFO_SYMBOL_ARRAY(mem_section);
	VMCOREINFO_LENGTH(mem_section, NR_SECTION_ROOTS);
	VMCOREINFO_STRUCT_SIZE(mem_section);
	VMCOREINFO_OFFSET(mem_section, section_mem_map);
	VMCOREINFO_NUMBER(SECTION_SIZE_BITS);
	VMCOREINFO_NUMBER(MAX_PHYSMEM_BITS);
#पूर्ण_अगर
	VMCOREINFO_STRUCT_SIZE(page);
	VMCOREINFO_STRUCT_SIZE(pglist_data);
	VMCOREINFO_STRUCT_SIZE(zone);
	VMCOREINFO_STRUCT_SIZE(मुक्त_area);
	VMCOREINFO_STRUCT_SIZE(list_head);
	VMCOREINFO_SIZE(nodemask_t);
	VMCOREINFO_OFFSET(page, flags);
	VMCOREINFO_OFFSET(page, _refcount);
	VMCOREINFO_OFFSET(page, mapping);
	VMCOREINFO_OFFSET(page, lru);
	VMCOREINFO_OFFSET(page, _mapcount);
	VMCOREINFO_OFFSET(page, निजी);
	VMCOREINFO_OFFSET(page, compound_dtor);
	VMCOREINFO_OFFSET(page, compound_order);
	VMCOREINFO_OFFSET(page, compound_head);
	VMCOREINFO_OFFSET(pglist_data, node_zones);
	VMCOREINFO_OFFSET(pglist_data, nr_zones);
#अगर_घोषित CONFIG_FLAT_NODE_MEM_MAP
	VMCOREINFO_OFFSET(pglist_data, node_mem_map);
#पूर्ण_अगर
	VMCOREINFO_OFFSET(pglist_data, node_start_pfn);
	VMCOREINFO_OFFSET(pglist_data, node_spanned_pages);
	VMCOREINFO_OFFSET(pglist_data, node_id);
	VMCOREINFO_OFFSET(zone, मुक्त_area);
	VMCOREINFO_OFFSET(zone, vm_stat);
	VMCOREINFO_OFFSET(zone, spanned_pages);
	VMCOREINFO_OFFSET(मुक्त_area, मुक्त_list);
	VMCOREINFO_OFFSET(list_head, next);
	VMCOREINFO_OFFSET(list_head, prev);
	VMCOREINFO_OFFSET(vmap_area, बहु_शुरू);
	VMCOREINFO_OFFSET(vmap_area, list);
	VMCOREINFO_LENGTH(zone.मुक्त_area, MAX_ORDER);
	log_buf_vmcoreinfo_setup();
	VMCOREINFO_LENGTH(मुक्त_area.मुक्त_list, MIGRATE_TYPES);
	VMCOREINFO_NUMBER(NR_FREE_PAGES);
	VMCOREINFO_NUMBER(PG_lru);
	VMCOREINFO_NUMBER(PG_निजी);
	VMCOREINFO_NUMBER(PG_swapcache);
	VMCOREINFO_NUMBER(PG_swapbacked);
	VMCOREINFO_NUMBER(PG_slab);
#अगर_घोषित CONFIG_MEMORY_FAILURE
	VMCOREINFO_NUMBER(PG_hwpoison);
#पूर्ण_अगर
	VMCOREINFO_NUMBER(PG_head_mask);
#घोषणा PAGE_BUDDY_MAPCOUNT_VALUE	(~PG_buddy)
	VMCOREINFO_NUMBER(PAGE_BUDDY_MAPCOUNT_VALUE);
#अगर_घोषित CONFIG_HUGETLB_PAGE
	VMCOREINFO_NUMBER(HUGETLB_PAGE_DTOR);
#घोषणा PAGE_OFFLINE_MAPCOUNT_VALUE	(~PG_offline)
	VMCOREINFO_NUMBER(PAGE_OFFLINE_MAPCOUNT_VALUE);
#पूर्ण_अगर

	arch_crash_save_vmcoreinfo();
	update_vmcoreinfo_note();

	वापस 0;
पूर्ण

subsys_initcall(crash_save_vmcoreinfo_init);
