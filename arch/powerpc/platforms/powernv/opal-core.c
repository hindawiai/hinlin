<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Interface क्रम exporting the OPAL ELF core.
 * Heavily inspired from fs/proc/vmcore.c
 *
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "opal core: " fmt

#समावेश <linux/memblock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/crash_core.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/fadump-पूर्णांकernal.h>

#समावेश "opal-fadump.h"

#घोषणा MAX_PT_LOAD_CNT		8

/* NT_AUXV note related info */
#घोषणा AUXV_CNT		1
#घोषणा AUXV_DESC_SZ		(((2 * AUXV_CNT) + 1) * माप(Elf64_Off))

काष्ठा opalcore_config अणु
	u32			num_cpus;
	/* PIR value of crashing CPU */
	u32			crashing_cpu;

	/* CPU state data info from F/W */
	u64			cpu_state_destination_vaddr;
	u64			cpu_state_data_size;
	u64			cpu_state_entry_size;

	/* OPAL memory to be exported as PT_LOAD segments */
	u64			ptload_addr[MAX_PT_LOAD_CNT];
	u64			ptload_size[MAX_PT_LOAD_CNT];
	u64			ptload_cnt;

	/* Poपूर्णांकer to the first PT_LOAD in the ELF core file */
	Elf64_Phdr		*ptload_phdr;

	/* Total size of opalcore file. */
	माप_प्रकार			opalcore_size;

	/* Buffer क्रम all the ELF core headers and the PT_NOTE */
	माप_प्रकार			opalcorebuf_sz;
	अक्षर			*opalcorebuf;

	/* NT_AUXV buffer */
	अक्षर			auxv_buf[AUXV_DESC_SZ];
पूर्ण;

काष्ठा opalcore अणु
	काष्ठा list_head	list;
	u64			paddr;
	माप_प्रकार			size;
	loff_t			offset;
पूर्ण;

अटल LIST_HEAD(opalcore_list);
अटल काष्ठा opalcore_config *oc_conf;
अटल स्थिर काष्ठा opal_mpipl_fadump *opalc_metadata;
अटल स्थिर काष्ठा opal_mpipl_fadump *opalc_cpu_metadata;
अटल काष्ठा kobject *mpipl_kobj;

/*
 * Set crashing CPU's संकेत to SIGUSR1. अगर the kernel is triggered
 * by kernel, संक_इति otherwise.
 */
bool kernel_initiated;

अटल काष्ठा opalcore * __init get_new_element(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा opalcore), GFP_KERNEL);
पूर्ण

अटल अंतरभूत पूर्णांक is_opalcore_usable(व्योम)
अणु
	वापस (oc_conf && oc_conf->opalcorebuf != शून्य) ? 1 : 0;
पूर्ण

अटल Elf64_Word *append_elf64_note(Elf64_Word *buf, अक्षर *name,
				     u32 type, व्योम *data,
				     माप_प्रकार data_len)
अणु
	Elf64_Nhdr *note = (Elf64_Nhdr *)buf;
	Elf64_Word namesz = म_माप(name) + 1;

	note->n_namesz = cpu_to_be32(namesz);
	note->n_descsz = cpu_to_be32(data_len);
	note->n_type   = cpu_to_be32(type);
	buf += DIV_ROUND_UP(माप(*note), माप(Elf64_Word));
	स_नकल(buf, name, namesz);
	buf += DIV_ROUND_UP(namesz, माप(Elf64_Word));
	स_नकल(buf, data, data_len);
	buf += DIV_ROUND_UP(data_len, माप(Elf64_Word));

	वापस buf;
पूर्ण

अटल व्योम fill_prstatus(काष्ठा elf_prstatus *prstatus, पूर्णांक pir,
			  काष्ठा pt_regs *regs)
अणु
	स_रखो(prstatus, 0, माप(काष्ठा elf_prstatus));
	elf_core_copy_kernel_regs(&(prstatus->pr_reg), regs);

	/*
	 * Overload PID with PIR value.
	 * As a PIR value could also be '0', add an offset of '100'
	 * to every PIR to aव्योम misपूर्णांकerpretations in GDB.
	 */
	prstatus->common.pr_pid  = cpu_to_be32(100 + pir);
	prstatus->common.pr_ppid = cpu_to_be32(1);

	/*
	 * Indicate SIGUSR1 क्रम crash initiated from kernel.
	 * संक_इति otherwise.
	 */
	अगर (pir == oc_conf->crashing_cpu) अणु
		लघु sig;

		sig = kernel_initiated ? SIGUSR1 : संक_इति;
		prstatus->common.pr_cursig = cpu_to_be16(sig);
	पूर्ण
पूर्ण

अटल Elf64_Word *auxv_to_elf64_notes(Elf64_Word *buf,
				       u64 opal_boot_entry)
अणु
	Elf64_Off *bufp = (Elf64_Off *)oc_conf->auxv_buf;
	पूर्णांक idx = 0;

	स_रखो(bufp, 0, AUXV_DESC_SZ);

	/* Entry poपूर्णांक of OPAL */
	bufp[idx++] = cpu_to_be64(AT_ENTRY);
	bufp[idx++] = cpu_to_be64(opal_boot_entry);

	/* end of vector */
	bufp[idx++] = cpu_to_be64(AT_शून्य);

	buf = append_elf64_note(buf, CRASH_CORE_NOTE_NAME, NT_AUXV,
				oc_conf->auxv_buf, AUXV_DESC_SZ);
	वापस buf;
पूर्ण

/*
 * Read from the ELF header and then the crash dump.
 * Returns number of bytes पढ़ो on success, -त्रुटि_सं on failure.
 */
अटल sमाप_प्रकार पढ़ो_opalcore(काष्ठा file *file, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr, अक्षर *to,
			     loff_t pos, माप_प्रकार count)
अणु
	काष्ठा opalcore *m;
	sमाप_प्रकार tsz, avail;
	loff_t tpos = pos;

	अगर (pos >= oc_conf->opalcore_size)
		वापस 0;

	/* Adjust count अगर it goes beyond opalcore size */
	avail = oc_conf->opalcore_size - pos;
	अगर (count > avail)
		count = avail;

	अगर (count == 0)
		वापस 0;

	/* Read ELF core header and/or PT_NOTE segment */
	अगर (tpos < oc_conf->opalcorebuf_sz) अणु
		tsz = min_t(माप_प्रकार, oc_conf->opalcorebuf_sz - tpos, count);
		स_नकल(to, oc_conf->opalcorebuf + tpos, tsz);
		to += tsz;
		tpos += tsz;
		count -= tsz;
	पूर्ण

	list_क्रम_each_entry(m, &opalcore_list, list) अणु
		/* nothing more to पढ़ो here */
		अगर (count == 0)
			अवरोध;

		अगर (tpos < m->offset + m->size) अणु
			व्योम *addr;

			tsz = min_t(माप_प्रकार, m->offset + m->size - tpos, count);
			addr = (व्योम *)(m->paddr + tpos - m->offset);
			स_नकल(to, __va(addr), tsz);
			to += tsz;
			tpos += tsz;
			count -= tsz;
		पूर्ण
	पूर्ण

	वापस (tpos - pos);
पूर्ण

अटल काष्ठा bin_attribute opal_core_attr = अणु
	.attr = अणु.name = "core", .mode = 0400पूर्ण,
	.पढ़ो = पढ़ो_opalcore
पूर्ण;

/*
 * Read CPU state dump data and convert it पूर्णांकo ELF notes.
 *
 * Each रेजिस्टर entry is of 16 bytes, A numerical identअगरier aदीर्घ with
 * a GPR/SPR flag in the first 8 bytes and the रेजिस्टर value in the next
 * 8 bytes. For more details refer to F/W करोcumentation.
 */
अटल Elf64_Word * __init opalcore_append_cpu_notes(Elf64_Word *buf)
अणु
	u32 thपढ़ो_pir, size_per_thपढ़ो, regs_offset, regs_cnt, reg_esize;
	काष्ठा hdat_fadump_thपढ़ो_hdr *thdr;
	काष्ठा elf_prstatus prstatus;
	Elf64_Word *first_cpu_note;
	काष्ठा pt_regs regs;
	अक्षर *bufp;
	पूर्णांक i;

	size_per_thपढ़ो = oc_conf->cpu_state_entry_size;
	bufp = __va(oc_conf->cpu_state_destination_vaddr);

	/*
	 * Offset क्रम रेजिस्टर entries, entry size and रेजिस्टरs count is
	 * duplicated in every thपढ़ो header in keeping with HDAT क्रमmat.
	 * Use these values from the first thपढ़ो header.
	 */
	thdr = (काष्ठा hdat_fadump_thपढ़ो_hdr *)bufp;
	regs_offset = (दुरत्व(काष्ठा hdat_fadump_thपढ़ो_hdr, offset) +
		       be32_to_cpu(thdr->offset));
	reg_esize = be32_to_cpu(thdr->esize);
	regs_cnt  = be32_to_cpu(thdr->ecnt);

	pr_debug("--------CPU State Data------------\n");
	pr_debug("NumCpus     : %u\n", oc_conf->num_cpus);
	pr_debug("\tOffset: %u, Entry size: %u, Cnt: %u\n",
		 regs_offset, reg_esize, regs_cnt);

	/*
	 * Skip past the first CPU note. Fill this note with the
	 * crashing CPU's prstatus.
	 */
	first_cpu_note = buf;
	buf = append_elf64_note(buf, CRASH_CORE_NOTE_NAME, NT_PRSTATUS,
				&prstatus, माप(prstatus));

	क्रम (i = 0; i < oc_conf->num_cpus; i++, bufp += size_per_thपढ़ो) अणु
		thdr = (काष्ठा hdat_fadump_thपढ़ो_hdr *)bufp;
		thपढ़ो_pir = be32_to_cpu(thdr->pir);

		pr_debug("[%04d] PIR: 0x%x, core state: 0x%02x\n",
			 i, thपढ़ो_pir, thdr->core_state);

		/*
		 * Register state data of MAX cores is provided by firmware,
		 * but some of this cores may not be active. So, जबतक
		 * processing रेजिस्टर state data, check core state and
		 * skip thपढ़ोs that beदीर्घ to inactive cores.
		 */
		अगर (thdr->core_state == HDAT_FADUMP_CORE_INACTIVE)
			जारी;

		opal_fadump_पढ़ो_regs((bufp + regs_offset), regs_cnt,
				      reg_esize, false, &regs);

		pr_debug("PIR 0x%x - R1 : 0x%llx, NIP : 0x%llx\n", thपढ़ो_pir,
			 be64_to_cpu(regs.gpr[1]), be64_to_cpu(regs.nip));
		fill_prstatus(&prstatus, thपढ़ो_pir, &regs);

		अगर (thपढ़ो_pir != oc_conf->crashing_cpu) अणु
			buf = append_elf64_note(buf, CRASH_CORE_NOTE_NAME,
						NT_PRSTATUS, &prstatus,
						माप(prstatus));
		पूर्ण अन्यथा अणु
			/*
			 * Add crashing CPU as the first NT_PRSTATUS note क्रम
			 * GDB to process the core file appropriately.
			 */
			append_elf64_note(first_cpu_note, CRASH_CORE_NOTE_NAME,
					  NT_PRSTATUS, &prstatus,
					  माप(prstatus));
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक __init create_opalcore(व्योम)
अणु
	u64 opal_boot_entry, opal_base_addr, paddr;
	u32 hdr_size, cpu_notes_size, count;
	काष्ठा device_node *dn;
	काष्ठा opalcore *new;
	loff_t opalcore_off;
	काष्ठा page *page;
	Elf64_Phdr *phdr;
	Elf64_Ehdr *elf;
	पूर्णांक i, ret;
	अक्षर *bufp;

	/* Get size of header & CPU notes क्रम OPAL core */
	hdr_size = (माप(Elf64_Ehdr) +
		    ((oc_conf->ptload_cnt + 1) * माप(Elf64_Phdr)));
	cpu_notes_size = ((oc_conf->num_cpus * (CRASH_CORE_NOTE_HEAD_BYTES +
			  CRASH_CORE_NOTE_NAME_BYTES +
			  CRASH_CORE_NOTE_DESC_BYTES)) +
			  (CRASH_CORE_NOTE_HEAD_BYTES +
			  CRASH_CORE_NOTE_NAME_BYTES + AUXV_DESC_SZ));

	/* Allocate buffer to setup OPAL core */
	oc_conf->opalcorebuf_sz = PAGE_ALIGN(hdr_size + cpu_notes_size);
	oc_conf->opalcorebuf = alloc_pages_exact(oc_conf->opalcorebuf_sz,
						 GFP_KERNEL | __GFP_ZERO);
	अगर (!oc_conf->opalcorebuf) अणु
		pr_err("Not enough memory to setup OPAL core (size: %lu)\n",
		       oc_conf->opalcorebuf_sz);
		oc_conf->opalcorebuf_sz = 0;
		वापस -ENOMEM;
	पूर्ण
	count = oc_conf->opalcorebuf_sz / PAGE_SIZE;
	page = virt_to_page(oc_conf->opalcorebuf);
	क्रम (i = 0; i < count; i++)
		mark_page_reserved(page + i);

	pr_debug("opalcorebuf = 0x%llx\n", (u64)oc_conf->opalcorebuf);

	/* Read OPAL related device-tree entries */
	dn = of_find_node_by_name(शून्य, "ibm,opal");
	अगर (dn) अणु
		ret = of_property_पढ़ो_u64(dn, "opal-base-address",
					   &opal_base_addr);
		pr_debug("opal-base-address: %llx\n", opal_base_addr);
		ret |= of_property_पढ़ो_u64(dn, "opal-boot-address",
					    &opal_boot_entry);
		pr_debug("opal-boot-address: %llx\n", opal_boot_entry);
	पूर्ण
	अगर (!dn || ret)
		pr_warn("WARNING: Failed to read OPAL base & entry values\n");

	/* Use count to keep track of the program headers */
	count = 0;

	bufp = oc_conf->opalcorebuf;
	elf = (Elf64_Ehdr *)bufp;
	bufp += माप(Elf64_Ehdr);
	स_नकल(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELFDATA2MSB;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;
	स_रखो(elf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	elf->e_type = cpu_to_be16(ET_CORE);
	elf->e_machine = cpu_to_be16(ELF_ARCH);
	elf->e_version = cpu_to_be32(EV_CURRENT);
	elf->e_entry = 0;
	elf->e_phoff = cpu_to_be64(माप(Elf64_Ehdr));
	elf->e_shoff = 0;
	elf->e_flags = 0;

	elf->e_ehsize = cpu_to_be16(माप(Elf64_Ehdr));
	elf->e_phentsize = cpu_to_be16(माप(Elf64_Phdr));
	elf->e_phnum = 0;
	elf->e_shentsize = 0;
	elf->e_shnum = 0;
	elf->e_shstrndx = 0;

	phdr = (Elf64_Phdr *)bufp;
	bufp += माप(Elf64_Phdr);
	phdr->p_type	= cpu_to_be32(PT_NOTE);
	phdr->p_flags	= 0;
	phdr->p_align	= 0;
	phdr->p_paddr	= phdr->p_vaddr = 0;
	phdr->p_offset	= cpu_to_be64(hdr_size);
	phdr->p_filesz	= phdr->p_memsz = cpu_to_be64(cpu_notes_size);
	count++;

	opalcore_off = oc_conf->opalcorebuf_sz;
	oc_conf->ptload_phdr  = (Elf64_Phdr *)bufp;
	paddr = 0;
	क्रम (i = 0; i < oc_conf->ptload_cnt; i++) अणु
		phdr = (Elf64_Phdr *)bufp;
		bufp += माप(Elf64_Phdr);
		phdr->p_type	= cpu_to_be32(PT_LOAD);
		phdr->p_flags	= cpu_to_be32(PF_R|PF_W|PF_X);
		phdr->p_align	= 0;

		new = get_new_element();
		अगर (!new)
			वापस -ENOMEM;
		new->paddr  = oc_conf->ptload_addr[i];
		new->size   = oc_conf->ptload_size[i];
		new->offset = opalcore_off;
		list_add_tail(&new->list, &opalcore_list);

		phdr->p_paddr	= cpu_to_be64(paddr);
		phdr->p_vaddr	= cpu_to_be64(opal_base_addr + paddr);
		phdr->p_filesz	= phdr->p_memsz  =
			cpu_to_be64(oc_conf->ptload_size[i]);
		phdr->p_offset	= cpu_to_be64(opalcore_off);

		count++;
		opalcore_off += oc_conf->ptload_size[i];
		paddr += oc_conf->ptload_size[i];
	पूर्ण

	elf->e_phnum = cpu_to_be16(count);

	bufp = (अक्षर *)opalcore_append_cpu_notes((Elf64_Word *)bufp);
	bufp = (अक्षर *)auxv_to_elf64_notes((Elf64_Word *)bufp, opal_boot_entry);

	oc_conf->opalcore_size = opalcore_off;
	वापस 0;
पूर्ण

अटल व्योम opalcore_cleanup(व्योम)
अणु
	अगर (oc_conf == शून्य)
		वापस;

	/* Remove OPAL core sysfs file */
	sysfs_हटाओ_bin_file(mpipl_kobj, &opal_core_attr);
	oc_conf->ptload_phdr = शून्य;
	oc_conf->ptload_cnt = 0;

	/* मुक्त the buffer used क्रम setting up OPAL core */
	अगर (oc_conf->opalcorebuf) अणु
		व्योम *end = (व्योम *)((u64)oc_conf->opalcorebuf +
				     oc_conf->opalcorebuf_sz);

		मुक्त_reserved_area(oc_conf->opalcorebuf, end, -1, शून्य);
		oc_conf->opalcorebuf = शून्य;
		oc_conf->opalcorebuf_sz = 0;
	पूर्ण

	kमुक्त(oc_conf);
	oc_conf = शून्य;
पूर्ण
__निकासcall(opalcore_cleanup);

अटल व्योम __init opalcore_config_init(व्योम)
अणु
	u32 idx, cpu_data_version;
	काष्ठा device_node *np;
	स्थिर __be32 *prop;
	u64 addr = 0;
	पूर्णांक i, ret;

	np = of_find_node_by_path("/ibm,opal/dump");
	अगर (np == शून्य)
		वापस;

	अगर (!of_device_is_compatible(np, "ibm,opal-dump")) अणु
		pr_warn("Support missing for this f/w version!\n");
		वापस;
	पूर्ण

	/* Check अगर dump has been initiated on last reboot */
	prop = of_get_property(np, "mpipl-boot", शून्य);
	अगर (!prop) अणु
		of_node_put(np);
		वापस;
	पूर्ण

	/* Get OPAL metadata */
	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_OPAL, &addr);
	अगर ((ret != OPAL_SUCCESS) || !addr) अणु
		pr_err("Failed to get OPAL metadata (%d)\n", ret);
		जाओ error_out;
	पूर्ण

	addr = be64_to_cpu(addr);
	pr_debug("OPAL metadata addr: %llx\n", addr);
	opalc_metadata = __va(addr);

	/* Get OPAL CPU metadata */
	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_CPU, &addr);
	अगर ((ret != OPAL_SUCCESS) || !addr) अणु
		pr_err("Failed to get OPAL CPU metadata (%d)\n", ret);
		जाओ error_out;
	पूर्ण

	addr = be64_to_cpu(addr);
	pr_debug("CPU metadata addr: %llx\n", addr);
	opalc_cpu_metadata = __va(addr);

	/* Allocate memory क्रम config buffer */
	oc_conf = kzalloc(माप(काष्ठा opalcore_config), GFP_KERNEL);
	अगर (oc_conf == शून्य)
		जाओ error_out;

	/* Parse OPAL metadata */
	अगर (opalc_metadata->version != OPAL_MPIPL_VERSION) अणु
		pr_warn("Supported OPAL metadata version: %u, found: %u!\n",
			OPAL_MPIPL_VERSION, opalc_metadata->version);
		pr_warn("WARNING: F/W using newer OPAL metadata format!!\n");
	पूर्ण

	oc_conf->ptload_cnt = 0;
	idx = be32_to_cpu(opalc_metadata->region_cnt);
	अगर (idx > MAX_PT_LOAD_CNT) अणु
		pr_warn("WARNING: OPAL regions count (%d) adjusted to limit (%d)",
			idx, MAX_PT_LOAD_CNT);
		idx = MAX_PT_LOAD_CNT;
	पूर्ण
	क्रम (i = 0; i < idx; i++) अणु
		oc_conf->ptload_addr[oc_conf->ptload_cnt] =
				be64_to_cpu(opalc_metadata->region[i].dest);
		oc_conf->ptload_size[oc_conf->ptload_cnt++] =
				be64_to_cpu(opalc_metadata->region[i].size);
	पूर्ण
	oc_conf->ptload_cnt = i;
	oc_conf->crashing_cpu = be32_to_cpu(opalc_metadata->crashing_pir);

	अगर (!oc_conf->ptload_cnt) अणु
		pr_err("OPAL memory regions not found\n");
		जाओ error_out;
	पूर्ण

	/* Parse OPAL CPU metadata */
	cpu_data_version = be32_to_cpu(opalc_cpu_metadata->cpu_data_version);
	अगर (cpu_data_version != HDAT_FADUMP_CPU_DATA_VER) अणु
		pr_warn("Supported CPU data version: %u, found: %u!\n",
			HDAT_FADUMP_CPU_DATA_VER, cpu_data_version);
		pr_warn("WARNING: F/W using newer CPU state data format!!\n");
	पूर्ण

	addr = be64_to_cpu(opalc_cpu_metadata->region[0].dest);
	अगर (!addr) अणु
		pr_err("CPU state data not found!\n");
		जाओ error_out;
	पूर्ण
	oc_conf->cpu_state_destination_vaddr = (u64)__va(addr);

	oc_conf->cpu_state_data_size =
			be64_to_cpu(opalc_cpu_metadata->region[0].size);
	oc_conf->cpu_state_entry_size =
			be32_to_cpu(opalc_cpu_metadata->cpu_data_size);

	अगर ((oc_conf->cpu_state_entry_size == 0) ||
	    (oc_conf->cpu_state_entry_size > oc_conf->cpu_state_data_size)) अणु
		pr_err("CPU state data is invalid.\n");
		जाओ error_out;
	पूर्ण
	oc_conf->num_cpus = (oc_conf->cpu_state_data_size /
			     oc_conf->cpu_state_entry_size);

	of_node_put(np);
	वापस;

error_out:
	pr_err("Could not export /sys/firmware/opal/core\n");
	opalcore_cleanup();
	of_node_put(np);
पूर्ण

अटल sमाप_प्रकार release_core_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक input = -1;

	अगर (kstrtoपूर्णांक(buf, 0, &input))
		वापस -EINVAL;

	अगर (input == 1) अणु
		अगर (oc_conf == शून्य) अणु
			pr_err("'/sys/firmware/opal/core' file not accessible!\n");
			वापस -EPERM;
		पूर्ण

		/*
		 * Take away '/sys/firmware/opal/core' and release all memory
		 * used क्रम exporting this file.
		 */
		opalcore_cleanup();
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute opalcore_rel_attr = __ATTR_WO(release_core);

अटल काष्ठा attribute *mpipl_attr[] = अणु
	&opalcore_rel_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *mpipl_bin_attr[] = अणु
	&opal_core_attr,
	शून्य,

पूर्ण;

अटल काष्ठा attribute_group mpipl_group = अणु
	.attrs = mpipl_attr,
	.bin_attrs =  mpipl_bin_attr,
पूर्ण;

अटल पूर्णांक __init opalcore_init(व्योम)
अणु
	पूर्णांक rc = -1;

	opalcore_config_init();

	अगर (oc_conf == शून्य)
		वापस rc;

	create_opalcore();

	/*
	 * If oc_conf->opalcorebuf= is set in the 2nd kernel,
	 * then capture the dump.
	 */
	अगर (!(is_opalcore_usable())) अणु
		pr_err("Failed to export /sys/firmware/opal/mpipl/core\n");
		opalcore_cleanup();
		वापस rc;
	पूर्ण

	/* Set OPAL core file size */
	opal_core_attr.size = oc_conf->opalcore_size;

	mpipl_kobj = kobject_create_and_add("mpipl", opal_kobj);
	अगर (!mpipl_kobj) अणु
		pr_err("unable to create mpipl kobject\n");
		वापस -ENOMEM;
	पूर्ण

	/* Export OPAL core sysfs file */
	rc = sysfs_create_group(mpipl_kobj, &mpipl_group);
	अगर (rc) अणु
		pr_err("mpipl sysfs group creation failed (%d)", rc);
		opalcore_cleanup();
		वापस rc;
	पूर्ण
	/* The /sys/firmware/opal/core is moved to /sys/firmware/opal/mpipl/
	 * directory, need to create symlink at old location to मुख्यtain
	 * backward compatibility.
	 */
	rc = compat_only_sysfs_link_entry_to_kobj(opal_kobj, mpipl_kobj,
						  "core", शून्य);
	अगर (rc) अणु
		pr_err("unable to create core symlink (%d)\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
fs_initcall(opalcore_init);
