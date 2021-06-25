<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Firmware-Assisted Dump support on POWER platक्रमm (OPAL).
 *
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "opal fadump: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/mm.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/fadump-पूर्णांकernal.h>

#समावेश "opal-fadump.h"


#अगर_घोषित CONFIG_PRESERVE_FA_DUMP
/*
 * When dump is active but PRESERVE_FA_DUMP is enabled on the kernel,
 * ensure crash data is preserved in hope that the subsequent memory
 * preserving kernel boot is going to process this crash data.
 */
व्योम __init opal_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node)
अणु
	स्थिर काष्ठा opal_fadump_mem_काष्ठा *opal_fdm_active;
	स्थिर __be32 *prop;
	अचिन्हित दीर्घ dn;
	u64 addr = 0;
	s64 ret;

	dn = of_get_flat_dt_subnode_by_name(node, "dump");
	अगर (dn == -FDT_ERR_NOTFOUND)
		वापस;

	/*
	 * Check अगर dump has been initiated on last reboot.
	 */
	prop = of_get_flat_dt_prop(dn, "mpipl-boot", शून्य);
	अगर (!prop)
		वापस;

	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_KERNEL, &addr);
	अगर ((ret != OPAL_SUCCESS) || !addr) अणु
		pr_debug("Could not get Kernel metadata (%lld)\n", ret);
		वापस;
	पूर्ण

	/*
	 * Preserve memory only अगर kernel memory regions are रेजिस्टरed
	 * with f/w क्रम MPIPL.
	 */
	addr = be64_to_cpu(addr);
	pr_debug("Kernel metadata addr: %llx\n", addr);
	opal_fdm_active = (व्योम *)addr;
	अगर (opal_fdm_active->रेजिस्टरed_regions == 0)
		वापस;

	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_BOOT_MEM, &addr);
	अगर ((ret != OPAL_SUCCESS) || !addr) अणु
		pr_err("Failed to get boot memory tag (%lld)\n", ret);
		वापस;
	पूर्ण

	/*
	 * Memory below this address can be used क्रम booting a
	 * capture kernel or petitboot kernel. Preserve everything
	 * above this address क्रम processing crashdump.
	 */
	fadump_conf->boot_mem_top = be64_to_cpu(addr);
	pr_debug("Preserve everything above %llx\n", fadump_conf->boot_mem_top);

	pr_info("Firmware-assisted dump is active.\n");
	fadump_conf->dump_active = 1;
पूर्ण

#अन्यथा /* CONFIG_PRESERVE_FA_DUMP */
अटल स्थिर काष्ठा opal_fadump_mem_काष्ठा *opal_fdm_active;
अटल स्थिर काष्ठा opal_mpipl_fadump *opal_cpu_metadata;
अटल काष्ठा opal_fadump_mem_काष्ठा *opal_fdm;

#अगर_घोषित CONFIG_OPAL_CORE
बाह्य bool kernel_initiated;
#पूर्ण_अगर

अटल पूर्णांक opal_fadump_unरेजिस्टर(काष्ठा fw_dump *fadump_conf);

अटल व्योम opal_fadump_update_config(काष्ठा fw_dump *fadump_conf,
				      स्थिर काष्ठा opal_fadump_mem_काष्ठा *fdm)
अणु
	pr_debug("Boot memory regions count: %d\n", fdm->region_cnt);

	/*
	 * The destination address of the first boot memory region is the
	 * destination address of boot memory regions.
	 */
	fadump_conf->boot_mem_dest_addr = fdm->rgn[0].dest;
	pr_debug("Destination address of boot memory regions: %#016llx\n",
		 fadump_conf->boot_mem_dest_addr);

	fadump_conf->fadumphdr_addr = fdm->fadumphdr_addr;
पूर्ण

/*
 * This function is called in the capture kernel to get configuration details
 * from metadata setup by the first kernel.
 */
अटल व्योम opal_fadump_get_config(काष्ठा fw_dump *fadump_conf,
				   स्थिर काष्ठा opal_fadump_mem_काष्ठा *fdm)
अणु
	अचिन्हित दीर्घ base, size, last_end, hole_size;
	पूर्णांक i;

	अगर (!fadump_conf->dump_active)
		वापस;

	last_end = 0;
	hole_size = 0;
	fadump_conf->boot_memory_size = 0;

	pr_debug("Boot memory regions:\n");
	क्रम (i = 0; i < fdm->region_cnt; i++) अणु
		base = fdm->rgn[i].src;
		size = fdm->rgn[i].size;
		pr_debug("\t[%03d] base: 0x%lx, size: 0x%lx\n", i, base, size);

		fadump_conf->boot_mem_addr[i] = base;
		fadump_conf->boot_mem_sz[i] = size;
		fadump_conf->boot_memory_size += size;
		hole_size += (base - last_end);

		last_end = base + size;
	पूर्ण

	/*
	 * Start address of reserve dump area (permanent reservation) क्रम
	 * re-रेजिस्टरing FADump after dump capture.
	 */
	fadump_conf->reserve_dump_area_start = fdm->rgn[0].dest;

	/*
	 * Rarely, but it can so happen that प्रणाली crashes beक्रमe all
	 * boot memory regions are रेजिस्टरed क्रम MPIPL. In such
	 * हालs, warn that the vmcore may not be accurate and proceed
	 * anyway as that is the best bet considering मुक्त pages, cache
	 * pages, user pages, etc are usually filtered out.
	 *
	 * Hope the memory that could not be preserved only has pages
	 * that are usually filtered out जबतक saving the vmcore.
	 */
	अगर (fdm->region_cnt > fdm->रेजिस्टरed_regions) अणु
		pr_warn("Not all memory regions were saved!!!\n");
		pr_warn("  Unsaved memory regions:\n");
		i = fdm->रेजिस्टरed_regions;
		जबतक (i < fdm->region_cnt) अणु
			pr_warn("\t[%03d] base: 0x%llx, size: 0x%llx\n",
				i, fdm->rgn[i].src, fdm->rgn[i].size);
			i++;
		पूर्ण

		pr_warn("If the unsaved regions only contain pages that are filtered out (eg. free/user pages), the vmcore should still be usable.\n");
		pr_warn("WARNING: If the unsaved regions contain kernel pages, the vmcore will be corrupted.\n");
	पूर्ण

	fadump_conf->boot_mem_top = (fadump_conf->boot_memory_size + hole_size);
	fadump_conf->boot_mem_regs_cnt = fdm->region_cnt;
	opal_fadump_update_config(fadump_conf, fdm);
पूर्ण

/* Initialize kernel metadata */
अटल व्योम opal_fadump_init_metadata(काष्ठा opal_fadump_mem_काष्ठा *fdm)
अणु
	fdm->version = OPAL_FADUMP_VERSION;
	fdm->region_cnt = 0;
	fdm->रेजिस्टरed_regions = 0;
	fdm->fadumphdr_addr = 0;
पूर्ण

अटल u64 opal_fadump_init_mem_काष्ठा(काष्ठा fw_dump *fadump_conf)
अणु
	u64 addr = fadump_conf->reserve_dump_area_start;
	पूर्णांक i;

	opal_fdm = __va(fadump_conf->kernel_metadata);
	opal_fadump_init_metadata(opal_fdm);

	/* Boot memory regions */
	क्रम (i = 0; i < fadump_conf->boot_mem_regs_cnt; i++) अणु
		opal_fdm->rgn[i].src	= fadump_conf->boot_mem_addr[i];
		opal_fdm->rgn[i].dest	= addr;
		opal_fdm->rgn[i].size	= fadump_conf->boot_mem_sz[i];

		opal_fdm->region_cnt++;
		addr += fadump_conf->boot_mem_sz[i];
	पूर्ण

	/*
	 * Kernel metadata is passed to f/w and retrieved in capture kerenl.
	 * So, use it to save fadump header address instead of calculating it.
	 */
	opal_fdm->fadumphdr_addr = (opal_fdm->rgn[0].dest +
				    fadump_conf->boot_memory_size);

	opal_fadump_update_config(fadump_conf, opal_fdm);

	वापस addr;
पूर्ण

अटल u64 opal_fadump_get_metadata_size(व्योम)
अणु
	वापस PAGE_ALIGN(माप(काष्ठा opal_fadump_mem_काष्ठा));
पूर्ण

अटल पूर्णांक opal_fadump_setup_metadata(काष्ठा fw_dump *fadump_conf)
अणु
	पूर्णांक err = 0;
	s64 ret;

	/*
	 * Use the last page(s) in FADump memory reservation क्रम
	 * kernel metadata.
	 */
	fadump_conf->kernel_metadata = (fadump_conf->reserve_dump_area_start +
					fadump_conf->reserve_dump_area_size -
					opal_fadump_get_metadata_size());
	pr_info("Kernel metadata addr: %llx\n", fadump_conf->kernel_metadata);

	/* Initialize kernel metadata beक्रमe रेजिस्टरing the address with f/w */
	opal_fdm = __va(fadump_conf->kernel_metadata);
	opal_fadump_init_metadata(opal_fdm);

	/*
	 * Register metadata address with f/w. Can be retrieved in
	 * the capture kernel.
	 */
	ret = opal_mpipl_रेजिस्टर_tag(OPAL_MPIPL_TAG_KERNEL,
				      fadump_conf->kernel_metadata);
	अगर (ret != OPAL_SUCCESS) अणु
		pr_err("Failed to set kernel metadata tag!\n");
		err = -EPERM;
	पूर्ण

	/*
	 * Register boot memory top address with f/w. Should be retrieved
	 * by a kernel that पूर्णांकends to preserve crash'ed kernel's memory.
	 */
	ret = opal_mpipl_रेजिस्टर_tag(OPAL_MPIPL_TAG_BOOT_MEM,
				      fadump_conf->boot_mem_top);
	अगर (ret != OPAL_SUCCESS) अणु
		pr_err("Failed to set boot memory tag!\n");
		err = -EPERM;
	पूर्ण

	वापस err;
पूर्ण

अटल u64 opal_fadump_get_booपंचांगem_min(व्योम)
अणु
	वापस OPAL_FADUMP_MIN_BOOT_MEM;
पूर्ण

अटल पूर्णांक opal_fadump_रेजिस्टर(काष्ठा fw_dump *fadump_conf)
अणु
	s64 rc = OPAL_PARAMETER;
	पूर्णांक i, err = -EIO;

	क्रम (i = 0; i < opal_fdm->region_cnt; i++) अणु
		rc = opal_mpipl_update(OPAL_MPIPL_ADD_RANGE,
				       opal_fdm->rgn[i].src,
				       opal_fdm->rgn[i].dest,
				       opal_fdm->rgn[i].size);
		अगर (rc != OPAL_SUCCESS)
			अवरोध;

		opal_fdm->रेजिस्टरed_regions++;
	पूर्ण

	चयन (rc) अणु
	हाल OPAL_SUCCESS:
		pr_info("Registration is successful!\n");
		fadump_conf->dump_रेजिस्टरed = 1;
		err = 0;
		अवरोध;
	हाल OPAL_RESOURCE:
		/* If MAX regions limit in f/w is hit, warn and proceed. */
		pr_warn("%d regions could not be registered for MPIPL as MAX limit is reached!\n",
			(opal_fdm->region_cnt - opal_fdm->रेजिस्टरed_regions));
		fadump_conf->dump_रेजिस्टरed = 1;
		err = 0;
		अवरोध;
	हाल OPAL_PARAMETER:
		pr_err("Failed to register. Parameter Error(%lld).\n", rc);
		अवरोध;
	हाल OPAL_HARDWARE:
		pr_err("Support not available.\n");
		fadump_conf->fadump_supported = 0;
		fadump_conf->fadump_enabled = 0;
		अवरोध;
	शेष:
		pr_err("Failed to register. Unknown Error(%lld).\n", rc);
		अवरोध;
	पूर्ण

	/*
	 * If some regions were रेजिस्टरed beक्रमe OPAL_MPIPL_ADD_RANGE
	 * OPAL call failed, unरेजिस्टर all regions.
	 */
	अगर ((err < 0) && (opal_fdm->रेजिस्टरed_regions > 0))
		opal_fadump_unरेजिस्टर(fadump_conf);

	वापस err;
पूर्ण

अटल पूर्णांक opal_fadump_unरेजिस्टर(काष्ठा fw_dump *fadump_conf)
अणु
	s64 rc;

	rc = opal_mpipl_update(OPAL_MPIPL_REMOVE_ALL, 0, 0, 0);
	अगर (rc) अणु
		pr_err("Failed to un-register - unexpected Error(%lld).\n", rc);
		वापस -EIO;
	पूर्ण

	opal_fdm->रेजिस्टरed_regions = 0;
	fadump_conf->dump_रेजिस्टरed = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक opal_fadump_invalidate(काष्ठा fw_dump *fadump_conf)
अणु
	s64 rc;

	rc = opal_mpipl_update(OPAL_MPIPL_FREE_PRESERVED_MEMORY, 0, 0, 0);
	अगर (rc) अणु
		pr_err("Failed to invalidate - unexpected Error(%lld).\n", rc);
		वापस -EIO;
	पूर्ण

	fadump_conf->dump_active = 0;
	opal_fdm_active = शून्य;
	वापस 0;
पूर्ण

अटल व्योम opal_fadump_cleanup(काष्ठा fw_dump *fadump_conf)
अणु
	s64 ret;

	ret = opal_mpipl_रेजिस्टर_tag(OPAL_MPIPL_TAG_KERNEL, 0);
	अगर (ret != OPAL_SUCCESS)
		pr_warn("Could not reset (%llu) kernel metadata tag!\n", ret);
पूर्ण

/*
 * Verअगरy अगर CPU state data is available. If available, करो a bit of sanity
 * checking beक्रमe processing this data.
 */
अटल bool __init is_opal_fadump_cpu_data_valid(काष्ठा fw_dump *fadump_conf)
अणु
	अगर (!opal_cpu_metadata)
		वापस false;

	fadump_conf->cpu_state_data_version =
		be32_to_cpu(opal_cpu_metadata->cpu_data_version);
	fadump_conf->cpu_state_entry_size =
		be32_to_cpu(opal_cpu_metadata->cpu_data_size);
	fadump_conf->cpu_state_dest_vaddr =
		(u64)__va(be64_to_cpu(opal_cpu_metadata->region[0].dest));
	fadump_conf->cpu_state_data_size =
		be64_to_cpu(opal_cpu_metadata->region[0].size);

	अगर (fadump_conf->cpu_state_data_version != HDAT_FADUMP_CPU_DATA_VER) अणु
		pr_warn("Supported CPU state data version: %u, found: %d!\n",
			HDAT_FADUMP_CPU_DATA_VER,
			fadump_conf->cpu_state_data_version);
		pr_warn("WARNING: F/W using newer CPU state data format!!\n");
	पूर्ण

	अगर ((fadump_conf->cpu_state_dest_vaddr == 0) ||
	    (fadump_conf->cpu_state_entry_size == 0) ||
	    (fadump_conf->cpu_state_entry_size >
	     fadump_conf->cpu_state_data_size)) अणु
		pr_err("CPU state data is invalid. Ignoring!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Convert CPU state data saved at the समय of crash पूर्णांकo ELF notes.
 *
 * While the crashing CPU's रेजिस्टर data is saved by the kernel, CPU state
 * data क्रम all CPUs is saved by f/w. In CPU state data provided by f/w,
 * each रेजिस्टर entry is of 16 bytes, a numerical identअगरier aदीर्घ with
 * a GPR/SPR flag in the first 8 bytes and the रेजिस्टर value in the next
 * 8 bytes. For more details refer to F/W करोcumentation. If this data is
 * missing or in unsupported क्रमmat, append crashing CPU's रेजिस्टर data
 * saved by the kernel in the PT_NOTE, to have something to work with in
 * the vmcore file.
 */
अटल पूर्णांक __init
opal_fadump_build_cpu_notes(काष्ठा fw_dump *fadump_conf,
			    काष्ठा fadump_crash_info_header *fdh)
अणु
	u32 thपढ़ो_pir, size_per_thपढ़ो, regs_offset, regs_cnt, reg_esize;
	काष्ठा hdat_fadump_thपढ़ो_hdr *thdr;
	bool is_cpu_data_valid = false;
	u32 num_cpus = 1, *note_buf;
	काष्ठा pt_regs regs;
	अक्षर *bufp;
	पूर्णांक rc, i;

	अगर (is_opal_fadump_cpu_data_valid(fadump_conf)) अणु
		size_per_thपढ़ो = fadump_conf->cpu_state_entry_size;
		num_cpus = (fadump_conf->cpu_state_data_size / size_per_thपढ़ो);
		bufp = __va(fadump_conf->cpu_state_dest_vaddr);
		is_cpu_data_valid = true;
	पूर्ण

	rc = fadump_setup_cpu_notes_buf(num_cpus);
	अगर (rc != 0)
		वापस rc;

	note_buf = (u32 *)fadump_conf->cpu_notes_buf_vaddr;
	अगर (!is_cpu_data_valid)
		जाओ out;

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
	pr_debug("NumCpus     : %u\n", num_cpus);
	pr_debug("\tOffset: %u, Entry size: %u, Cnt: %u\n",
		 regs_offset, reg_esize, regs_cnt);

	क्रम (i = 0; i < num_cpus; i++, bufp += size_per_thपढ़ो) अणु
		thdr = (काष्ठा hdat_fadump_thपढ़ो_hdr *)bufp;

		thपढ़ो_pir = be32_to_cpu(thdr->pir);
		pr_debug("[%04d] PIR: 0x%x, core state: 0x%02x\n",
			 i, thपढ़ो_pir, thdr->core_state);

		/*
		 * If this is kernel initiated crash, crashing_cpu would be set
		 * appropriately and रेजिस्टर data of the crashing CPU saved by
		 * crashing kernel. Add this saved रेजिस्टर data of crashing CPU
		 * to elf notes and populate the pt_regs क्रम the reमुख्यing CPUs
		 * from रेजिस्टर state data provided by firmware.
		 */
		अगर (fdh->crashing_cpu == thपढ़ो_pir) अणु
			note_buf = fadump_regs_to_elf_notes(note_buf,
							    &fdh->regs);
			pr_debug("Crashing CPU PIR: 0x%x - R1 : 0x%lx, NIP : 0x%lx\n",
				 fdh->crashing_cpu, fdh->regs.gpr[1],
				 fdh->regs.nip);
			जारी;
		पूर्ण

		/*
		 * Register state data of MAX cores is provided by firmware,
		 * but some of this cores may not be active. So, जबतक
		 * processing रेजिस्टर state data, check core state and
		 * skip thपढ़ोs that beदीर्घ to inactive cores.
		 */
		अगर (thdr->core_state == HDAT_FADUMP_CORE_INACTIVE)
			जारी;

		opal_fadump_पढ़ो_regs((bufp + regs_offset), regs_cnt,
				      reg_esize, true, &regs);
		note_buf = fadump_regs_to_elf_notes(note_buf, &regs);
		pr_debug("CPU PIR: 0x%x - R1 : 0x%lx, NIP : 0x%lx\n",
			 thपढ़ो_pir, regs.gpr[1], regs.nip);
	पूर्ण

out:
	/*
	 * CPU state data is invalid/unsupported. Try appending crashing CPU's
	 * रेजिस्टर data, अगर it is saved by the kernel.
	 */
	अगर (fadump_conf->cpu_notes_buf_vaddr == (u64)note_buf) अणु
		अगर (fdh->crashing_cpu == FADUMP_CPU_UNKNOWN) अणु
			fadump_मुक्त_cpu_notes_buf();
			वापस -ENODEV;
		पूर्ण

		pr_warn("WARNING: appending only crashing CPU's register data\n");
		note_buf = fadump_regs_to_elf_notes(note_buf, &(fdh->regs));
	पूर्ण

	final_note(note_buf);

	pr_debug("Updating elfcore header (%llx) with cpu notes\n",
		 fdh->elfcorehdr_addr);
	fadump_update_elfcore_header(__va(fdh->elfcorehdr_addr));
	वापस 0;
पूर्ण

अटल पूर्णांक __init opal_fadump_process(काष्ठा fw_dump *fadump_conf)
अणु
	काष्ठा fadump_crash_info_header *fdh;
	पूर्णांक rc = -EINVAL;

	अगर (!opal_fdm_active || !fadump_conf->fadumphdr_addr)
		वापस rc;

	/* Validate the fadump crash info header */
	fdh = __va(fadump_conf->fadumphdr_addr);
	अगर (fdh->magic_number != FADUMP_CRASH_INFO_MAGIC) अणु
		pr_err("Crash info header is not valid.\n");
		वापस rc;
	पूर्ण

#अगर_घोषित CONFIG_OPAL_CORE
	/*
	 * If this is a kernel initiated crash, crashing_cpu would be set
	 * appropriately and रेजिस्टर data of the crashing CPU saved by
	 * crashing kernel. Add this saved रेजिस्टर data of crashing CPU
	 * to elf notes and populate the pt_regs क्रम the reमुख्यing CPUs
	 * from रेजिस्टर state data provided by firmware.
	 */
	अगर (fdh->crashing_cpu != FADUMP_CPU_UNKNOWN)
		kernel_initiated = true;
#पूर्ण_अगर

	rc = opal_fadump_build_cpu_notes(fadump_conf, fdh);
	अगर (rc)
		वापस rc;

	/*
	 * We are करोne validating dump info and elfcore header is now पढ़ोy
	 * to be exported. set elfcorehdr_addr so that vmcore module will
	 * export the elfcore header through '/proc/vmcore'.
	 */
	elfcorehdr_addr = fdh->elfcorehdr_addr;

	वापस rc;
पूर्ण

अटल व्योम opal_fadump_region_show(काष्ठा fw_dump *fadump_conf,
				    काष्ठा seq_file *m)
अणु
	स्थिर काष्ठा opal_fadump_mem_काष्ठा *fdm_ptr;
	u64 dumped_bytes = 0;
	पूर्णांक i;

	अगर (fadump_conf->dump_active)
		fdm_ptr = opal_fdm_active;
	अन्यथा
		fdm_ptr = opal_fdm;

	क्रम (i = 0; i < fdm_ptr->region_cnt; i++) अणु
		/*
		 * Only regions that are रेजिस्टरed क्रम MPIPL
		 * would have dump data.
		 */
		अगर ((fadump_conf->dump_active) &&
		    (i < fdm_ptr->रेजिस्टरed_regions))
			dumped_bytes = fdm_ptr->rgn[i].size;

		seq_म_लिखो(m, "DUMP: Src: %#016llx, Dest: %#016llx, ",
			   fdm_ptr->rgn[i].src, fdm_ptr->rgn[i].dest);
		seq_म_लिखो(m, "Size: %#llx, Dumped: %#llx bytes\n",
			   fdm_ptr->rgn[i].size, dumped_bytes);
	पूर्ण

	/* Dump is active. Show reserved area start address. */
	अगर (fadump_conf->dump_active) अणु
		seq_म_लिखो(m, "\nMemory above %#016lx is reserved for saving crash dump\n",
			   fadump_conf->reserve_dump_area_start);
	पूर्ण
पूर्ण

अटल व्योम opal_fadump_trigger(काष्ठा fadump_crash_info_header *fdh,
				स्थिर अक्षर *msg)
अणु
	पूर्णांक rc;

	/*
	 * Unlike on pSeries platक्रमm, logical CPU number is not provided
	 * with architected रेजिस्टर state data. So, store the crashing
	 * CPU's PIR instead to plug the appropriate रेजिस्टर data क्रम
	 * crashing CPU in the vmcore file.
	 */
	fdh->crashing_cpu = (u32)mfspr(SPRN_PIR);

	rc = opal_cec_reboot2(OPAL_REBOOT_MPIPL, msg);
	अगर (rc == OPAL_UNSUPPORTED) अणु
		pr_emerg("Reboot type %d not supported.\n",
			 OPAL_REBOOT_MPIPL);
	पूर्ण अन्यथा अगर (rc == OPAL_HARDWARE)
		pr_emerg("No backend support for MPIPL!\n");
पूर्ण

अटल काष्ठा fadump_ops opal_fadump_ops = अणु
	.fadump_init_mem_काष्ठा		= opal_fadump_init_mem_काष्ठा,
	.fadump_get_metadata_size	= opal_fadump_get_metadata_size,
	.fadump_setup_metadata		= opal_fadump_setup_metadata,
	.fadump_get_booपंचांगem_min		= opal_fadump_get_booपंचांगem_min,
	.fadump_रेजिस्टर		= opal_fadump_रेजिस्टर,
	.fadump_unरेजिस्टर		= opal_fadump_unरेजिस्टर,
	.fadump_invalidate		= opal_fadump_invalidate,
	.fadump_cleanup			= opal_fadump_cleanup,
	.fadump_process			= opal_fadump_process,
	.fadump_region_show		= opal_fadump_region_show,
	.fadump_trigger			= opal_fadump_trigger,
पूर्ण;

व्योम __init opal_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node)
अणु
	स्थिर __be32 *prop;
	अचिन्हित दीर्घ dn;
	u64 addr = 0;
	पूर्णांक i, len;
	s64 ret;

	/*
	 * Check अगर Firmware-Assisted Dump is supported. अगर yes, check
	 * अगर dump has been initiated on last reboot.
	 */
	dn = of_get_flat_dt_subnode_by_name(node, "dump");
	अगर (dn == -FDT_ERR_NOTFOUND) अणु
		pr_debug("FADump support is missing!\n");
		वापस;
	पूर्ण

	अगर (!of_flat_dt_is_compatible(dn, "ibm,opal-dump")) अणु
		pr_err("Support missing for this f/w version!\n");
		वापस;
	पूर्ण

	prop = of_get_flat_dt_prop(dn, "fw-load-area", &len);
	अगर (prop) अणु
		/*
		 * Each f/w load area is an (address,size) pair,
		 * 2 cells each, totalling 4 cells per range.
		 */
		क्रम (i = 0; i < len / (माप(*prop) * 4); i++) अणु
			u64 base, end;

			base = of_पढ़ो_number(prop + (i * 4) + 0, 2);
			end = base;
			end += of_पढ़ो_number(prop + (i * 4) + 2, 2);
			अगर (end > OPAL_FADUMP_MIN_BOOT_MEM) अणु
				pr_err("F/W load area: 0x%llx-0x%llx\n",
				       base, end);
				pr_err("F/W version not supported!\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	fadump_conf->ops		= &opal_fadump_ops;
	fadump_conf->fadump_supported	= 1;

	/*
	 * Firmware supports 32-bit field क्रम size. Align it to PAGE_SIZE
	 * and request firmware to copy multiple kernel boot memory regions.
	 */
	fadump_conf->max_copy_size = ALIGN_DOWN(U32_MAX, PAGE_SIZE);

	/*
	 * Check अगर dump has been initiated on last reboot.
	 */
	prop = of_get_flat_dt_prop(dn, "mpipl-boot", शून्य);
	अगर (!prop)
		वापस;

	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_KERNEL, &addr);
	अगर ((ret != OPAL_SUCCESS) || !addr) अणु
		pr_err("Failed to get Kernel metadata (%lld)\n", ret);
		वापस;
	पूर्ण

	addr = be64_to_cpu(addr);
	pr_debug("Kernel metadata addr: %llx\n", addr);

	opal_fdm_active = __va(addr);
	अगर (opal_fdm_active->version != OPAL_FADUMP_VERSION) अणु
		pr_warn("Supported kernel metadata version: %u, found: %d!\n",
			OPAL_FADUMP_VERSION, opal_fdm_active->version);
		pr_warn("WARNING: Kernel metadata format mismatch identified! Core file maybe corrupted..\n");
	पूर्ण

	/* Kernel regions not रेजिस्टरed with f/w क्रम MPIPL */
	अगर (opal_fdm_active->रेजिस्टरed_regions == 0) अणु
		opal_fdm_active = शून्य;
		वापस;
	पूर्ण

	ret = opal_mpipl_query_tag(OPAL_MPIPL_TAG_CPU, &addr);
	अगर (addr) अणु
		addr = be64_to_cpu(addr);
		pr_debug("CPU metadata addr: %llx\n", addr);
		opal_cpu_metadata = __va(addr);
	पूर्ण

	pr_info("Firmware-assisted dump is active.\n");
	fadump_conf->dump_active = 1;
	opal_fadump_get_config(fadump_conf, opal_fdm_active);
पूर्ण
#पूर्ण_अगर /* !CONFIG_PRESERVE_FA_DUMP */
