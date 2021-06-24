<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Firmware-Assisted Dump support on POWERVM platक्रमm.
 *
 * Copyright 2011, Mahesh Salgaonkar, IBM Corporation.
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "rtas fadump: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/fadump-पूर्णांकernal.h>

#समावेश "rtas-fadump.h"

अटल काष्ठा rtas_fadump_mem_काष्ठा fdm;
अटल स्थिर काष्ठा rtas_fadump_mem_काष्ठा *fdm_active;

अटल व्योम rtas_fadump_update_config(काष्ठा fw_dump *fadump_conf,
				      स्थिर काष्ठा rtas_fadump_mem_काष्ठा *fdm)
अणु
	fadump_conf->boot_mem_dest_addr =
		be64_to_cpu(fdm->rmr_region.destination_address);

	fadump_conf->fadumphdr_addr = (fadump_conf->boot_mem_dest_addr +
				       fadump_conf->boot_memory_size);
पूर्ण

/*
 * This function is called in the capture kernel to get configuration details
 * setup in the first kernel and passed to the f/w.
 */
अटल व्योम rtas_fadump_get_config(काष्ठा fw_dump *fadump_conf,
				   स्थिर काष्ठा rtas_fadump_mem_काष्ठा *fdm)
अणु
	fadump_conf->boot_mem_addr[0] =
		be64_to_cpu(fdm->rmr_region.source_address);
	fadump_conf->boot_mem_sz[0] = be64_to_cpu(fdm->rmr_region.source_len);
	fadump_conf->boot_memory_size = fadump_conf->boot_mem_sz[0];

	fadump_conf->boot_mem_top = fadump_conf->boot_memory_size;
	fadump_conf->boot_mem_regs_cnt = 1;

	/*
	 * Start address of reserve dump area (permanent reservation) क्रम
	 * re-रेजिस्टरing FADump after dump capture.
	 */
	fadump_conf->reserve_dump_area_start =
		be64_to_cpu(fdm->cpu_state_data.destination_address);

	rtas_fadump_update_config(fadump_conf, fdm);
पूर्ण

अटल u64 rtas_fadump_init_mem_काष्ठा(काष्ठा fw_dump *fadump_conf)
अणु
	u64 addr = fadump_conf->reserve_dump_area_start;

	स_रखो(&fdm, 0, माप(काष्ठा rtas_fadump_mem_काष्ठा));
	addr = addr & PAGE_MASK;

	fdm.header.dump_क्रमmat_version = cpu_to_be32(0x00000001);
	fdm.header.dump_num_sections = cpu_to_be16(3);
	fdm.header.dump_status_flag = 0;
	fdm.header.offset_first_dump_section =
		cpu_to_be32((u32)दुरत्व(काष्ठा rtas_fadump_mem_काष्ठा,
					  cpu_state_data));

	/*
	 * Fields क्रम disk dump option.
	 * We are not using disk dump option, hence set these fields to 0.
	 */
	fdm.header.dd_block_size = 0;
	fdm.header.dd_block_offset = 0;
	fdm.header.dd_num_blocks = 0;
	fdm.header.dd_offset_disk_path = 0;

	/* set 0 to disable an स्वतःmatic dump-reboot. */
	fdm.header.max_समय_स्वतः = 0;

	/* Kernel dump sections */
	/* cpu state data section. */
	fdm.cpu_state_data.request_flag =
		cpu_to_be32(RTAS_FADUMP_REQUEST_FLAG);
	fdm.cpu_state_data.source_data_type =
		cpu_to_be16(RTAS_FADUMP_CPU_STATE_DATA);
	fdm.cpu_state_data.source_address = 0;
	fdm.cpu_state_data.source_len =
		cpu_to_be64(fadump_conf->cpu_state_data_size);
	fdm.cpu_state_data.destination_address = cpu_to_be64(addr);
	addr += fadump_conf->cpu_state_data_size;

	/* hpte region section */
	fdm.hpte_region.request_flag = cpu_to_be32(RTAS_FADUMP_REQUEST_FLAG);
	fdm.hpte_region.source_data_type =
		cpu_to_be16(RTAS_FADUMP_HPTE_REGION);
	fdm.hpte_region.source_address = 0;
	fdm.hpte_region.source_len =
		cpu_to_be64(fadump_conf->hpte_region_size);
	fdm.hpte_region.destination_address = cpu_to_be64(addr);
	addr += fadump_conf->hpte_region_size;

	/* RMA region section */
	fdm.rmr_region.request_flag = cpu_to_be32(RTAS_FADUMP_REQUEST_FLAG);
	fdm.rmr_region.source_data_type =
		cpu_to_be16(RTAS_FADUMP_REAL_MODE_REGION);
	fdm.rmr_region.source_address = cpu_to_be64(0);
	fdm.rmr_region.source_len = cpu_to_be64(fadump_conf->boot_memory_size);
	fdm.rmr_region.destination_address = cpu_to_be64(addr);
	addr += fadump_conf->boot_memory_size;

	rtas_fadump_update_config(fadump_conf, &fdm);

	वापस addr;
पूर्ण

अटल u64 rtas_fadump_get_booपंचांगem_min(व्योम)
अणु
	वापस RTAS_FADUMP_MIN_BOOT_MEM;
पूर्ण

अटल पूर्णांक rtas_fadump_रेजिस्टर(काष्ठा fw_dump *fadump_conf)
अणु
	अचिन्हित पूर्णांक रुको_समय;
	पूर्णांक rc, err = -EIO;

	/* TODO: Add upper समय limit क्रम the delay */
	करो अणु
		rc =  rtas_call(fadump_conf->ibm_configure_kernel_dump, 3, 1,
				शून्य, FADUMP_REGISTER, &fdm,
				माप(काष्ठा rtas_fadump_mem_काष्ठा));

		रुको_समय = rtas_busy_delay_समय(rc);
		अगर (रुको_समय)
			mdelay(रुको_समय);

	पूर्ण जबतक (रुको_समय);

	चयन (rc) अणु
	हाल 0:
		pr_info("Registration is successful!\n");
		fadump_conf->dump_रेजिस्टरed = 1;
		err = 0;
		अवरोध;
	हाल -1:
		pr_err("Failed to register. Hardware Error(%d).\n", rc);
		अवरोध;
	हाल -3:
		अगर (!is_fadump_boot_mem_contiguous())
			pr_err("Can't have holes in boot memory area.\n");
		अन्यथा अगर (!is_fadump_reserved_mem_contiguous())
			pr_err("Can't have holes in reserved memory area.\n");

		pr_err("Failed to register. Parameter Error(%d).\n", rc);
		err = -EINVAL;
		अवरोध;
	हाल -9:
		pr_err("Already registered!\n");
		fadump_conf->dump_रेजिस्टरed = 1;
		err = -EEXIST;
		अवरोध;
	शेष:
		pr_err("Failed to register. Unknown Error(%d).\n", rc);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rtas_fadump_unरेजिस्टर(काष्ठा fw_dump *fadump_conf)
अणु
	अचिन्हित पूर्णांक रुको_समय;
	पूर्णांक rc;

	/* TODO: Add upper समय limit क्रम the delay */
	करो अणु
		rc =  rtas_call(fadump_conf->ibm_configure_kernel_dump, 3, 1,
				शून्य, FADUMP_UNREGISTER, &fdm,
				माप(काष्ठा rtas_fadump_mem_काष्ठा));

		रुको_समय = rtas_busy_delay_समय(rc);
		अगर (रुको_समय)
			mdelay(रुको_समय);
	पूर्ण जबतक (रुको_समय);

	अगर (rc) अणु
		pr_err("Failed to un-register - unexpected error(%d).\n", rc);
		वापस -EIO;
	पूर्ण

	fadump_conf->dump_रेजिस्टरed = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक rtas_fadump_invalidate(काष्ठा fw_dump *fadump_conf)
अणु
	अचिन्हित पूर्णांक रुको_समय;
	पूर्णांक rc;

	/* TODO: Add upper समय limit क्रम the delay */
	करो अणु
		rc =  rtas_call(fadump_conf->ibm_configure_kernel_dump, 3, 1,
				शून्य, FADUMP_INVALIDATE, fdm_active,
				माप(काष्ठा rtas_fadump_mem_काष्ठा));

		रुको_समय = rtas_busy_delay_समय(rc);
		अगर (रुको_समय)
			mdelay(रुको_समय);
	पूर्ण जबतक (रुको_समय);

	अगर (rc) अणु
		pr_err("Failed to invalidate - unexpected error (%d).\n", rc);
		वापस -EIO;
	पूर्ण

	fadump_conf->dump_active = 0;
	fdm_active = शून्य;
	वापस 0;
पूर्ण

#घोषणा RTAS_FADUMP_GPR_MASK		0xffffff0000000000
अटल अंतरभूत पूर्णांक rtas_fadump_gpr_index(u64 id)
अणु
	अक्षर str[3];
	पूर्णांक i = -1;

	अगर ((id & RTAS_FADUMP_GPR_MASK) == fadump_str_to_u64("GPR")) अणु
		/* get the digits at the end */
		id &= ~RTAS_FADUMP_GPR_MASK;
		id >>= 24;
		str[2] = '\0';
		str[1] = id & 0xff;
		str[0] = (id >> 8) & 0xff;
		अगर (kstrtoपूर्णांक(str, 10, &i))
			i = -EINVAL;
		अगर (i > 31)
			i = -1;
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम rtas_fadump_set_regval(काष्ठा pt_regs *regs, u64 reg_id, u64 reg_val)
अणु
	पूर्णांक i;

	i = rtas_fadump_gpr_index(reg_id);
	अगर (i >= 0)
		regs->gpr[i] = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("NIA"))
		regs->nip = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("MSR"))
		regs->msr = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("CTR"))
		regs->ctr = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("LR"))
		regs->link = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("XER"))
		regs->xer = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("CR"))
		regs->ccr = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("DAR"))
		regs->dar = (अचिन्हित दीर्घ)reg_val;
	अन्यथा अगर (reg_id == fadump_str_to_u64("DSISR"))
		regs->dsisr = (अचिन्हित दीर्घ)reg_val;
पूर्ण

अटल काष्ठा rtas_fadump_reg_entry*
rtas_fadump_पढ़ो_regs(काष्ठा rtas_fadump_reg_entry *reg_entry,
		      काष्ठा pt_regs *regs)
अणु
	स_रखो(regs, 0, माप(काष्ठा pt_regs));

	जबतक (be64_to_cpu(reg_entry->reg_id) != fadump_str_to_u64("CPUEND")) अणु
		rtas_fadump_set_regval(regs, be64_to_cpu(reg_entry->reg_id),
				       be64_to_cpu(reg_entry->reg_value));
		reg_entry++;
	पूर्ण
	reg_entry++;
	वापस reg_entry;
पूर्ण

/*
 * Read CPU state dump data and convert it पूर्णांकo ELF notes.
 * The CPU dump starts with magic number "REGSAVE". NumCpusOffset should be
 * used to access the data to allow क्रम additional fields to be added without
 * affecting compatibility. Each list of रेजिस्टरs क्रम a CPU starts with
 * "CPUSTRT" and ends with "CPUEND". Each रेजिस्टर entry is of 16 bytes,
 * 8 Byte ASCII identअगरier and 8 Byte रेजिस्टर value. The रेजिस्टर entry
 * with identअगरier "CPUSTRT" and "CPUEND" contains 4 byte cpu id as part
 * of रेजिस्टर value. For more details refer to PAPR करोcument.
 *
 * Only क्रम the crashing cpu we ignore the CPU dump data and get exact
 * state from fadump crash info काष्ठाure populated by first kernel at the
 * समय of crash.
 */
अटल पूर्णांक __init rtas_fadump_build_cpu_notes(काष्ठा fw_dump *fadump_conf)
अणु
	काष्ठा rtas_fadump_reg_save_area_header *reg_header;
	काष्ठा fadump_crash_info_header *fdh = शून्य;
	काष्ठा rtas_fadump_reg_entry *reg_entry;
	u32 num_cpus, *note_buf;
	पूर्णांक i, rc = 0, cpu = 0;
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ addr;
	व्योम *vaddr;

	addr = be64_to_cpu(fdm_active->cpu_state_data.destination_address);
	vaddr = __va(addr);

	reg_header = vaddr;
	अगर (be64_to_cpu(reg_header->magic_number) !=
	    fadump_str_to_u64("REGSAVE")) अणु
		pr_err("Unable to read register save area.\n");
		वापस -ENOENT;
	पूर्ण

	pr_debug("--------CPU State Data------------\n");
	pr_debug("Magic Number: %llx\n", be64_to_cpu(reg_header->magic_number));
	pr_debug("NumCpuOffset: %x\n", be32_to_cpu(reg_header->num_cpu_offset));

	vaddr += be32_to_cpu(reg_header->num_cpu_offset);
	num_cpus = be32_to_cpu(*((__be32 *)(vaddr)));
	pr_debug("NumCpus     : %u\n", num_cpus);
	vaddr += माप(u32);
	reg_entry = (काष्ठा rtas_fadump_reg_entry *)vaddr;

	rc = fadump_setup_cpu_notes_buf(num_cpus);
	अगर (rc != 0)
		वापस rc;

	note_buf = (u32 *)fadump_conf->cpu_notes_buf_vaddr;

	अगर (fadump_conf->fadumphdr_addr)
		fdh = __va(fadump_conf->fadumphdr_addr);

	क्रम (i = 0; i < num_cpus; i++) अणु
		अगर (be64_to_cpu(reg_entry->reg_id) !=
		    fadump_str_to_u64("CPUSTRT")) अणु
			pr_err("Unable to read CPU state data\n");
			rc = -ENOENT;
			जाओ error_out;
		पूर्ण
		/* Lower 4 bytes of reg_value contains logical cpu id */
		cpu = (be64_to_cpu(reg_entry->reg_value) &
		       RTAS_FADUMP_CPU_ID_MASK);
		अगर (fdh && !cpumask_test_cpu(cpu, &fdh->online_mask)) अणु
			RTAS_FADUMP_SKIP_TO_NEXT_CPU(reg_entry);
			जारी;
		पूर्ण
		pr_debug("Reading register data for cpu %d...\n", cpu);
		अगर (fdh && fdh->crashing_cpu == cpu) अणु
			regs = fdh->regs;
			note_buf = fadump_regs_to_elf_notes(note_buf, &regs);
			RTAS_FADUMP_SKIP_TO_NEXT_CPU(reg_entry);
		पूर्ण अन्यथा अणु
			reg_entry++;
			reg_entry = rtas_fadump_पढ़ो_regs(reg_entry, &regs);
			note_buf = fadump_regs_to_elf_notes(note_buf, &regs);
		पूर्ण
	पूर्ण
	final_note(note_buf);

	अगर (fdh) अणु
		pr_debug("Updating elfcore header (%llx) with cpu notes\n",
			 fdh->elfcorehdr_addr);
		fadump_update_elfcore_header(__va(fdh->elfcorehdr_addr));
	पूर्ण
	वापस 0;

error_out:
	fadump_मुक्त_cpu_notes_buf();
	वापस rc;

पूर्ण

/*
 * Validate and process the dump data stored by firmware beक्रमe exporting
 * it through '/proc/vmcore'.
 */
अटल पूर्णांक __init rtas_fadump_process(काष्ठा fw_dump *fadump_conf)
अणु
	काष्ठा fadump_crash_info_header *fdh;
	पूर्णांक rc = 0;

	अगर (!fdm_active || !fadump_conf->fadumphdr_addr)
		वापस -EINVAL;

	/* Check अगर the dump data is valid. */
	अगर ((be16_to_cpu(fdm_active->header.dump_status_flag) ==
			RTAS_FADUMP_ERROR_FLAG) ||
			(fdm_active->cpu_state_data.error_flags != 0) ||
			(fdm_active->rmr_region.error_flags != 0)) अणु
		pr_err("Dump taken by platform is not valid\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((fdm_active->rmr_region.bytes_dumped !=
			fdm_active->rmr_region.source_len) ||
			!fdm_active->cpu_state_data.bytes_dumped) अणु
		pr_err("Dump taken by platform is incomplete\n");
		वापस -EINVAL;
	पूर्ण

	/* Validate the fadump crash info header */
	fdh = __va(fadump_conf->fadumphdr_addr);
	अगर (fdh->magic_number != FADUMP_CRASH_INFO_MAGIC) अणु
		pr_err("Crash info header is not valid.\n");
		वापस -EINVAL;
	पूर्ण

	rc = rtas_fadump_build_cpu_notes(fadump_conf);
	अगर (rc)
		वापस rc;

	/*
	 * We are करोne validating dump info and elfcore header is now पढ़ोy
	 * to be exported. set elfcorehdr_addr so that vmcore module will
	 * export the elfcore header through '/proc/vmcore'.
	 */
	elfcorehdr_addr = fdh->elfcorehdr_addr;

	वापस 0;
पूर्ण

अटल व्योम rtas_fadump_region_show(काष्ठा fw_dump *fadump_conf,
				    काष्ठा seq_file *m)
अणु
	स्थिर काष्ठा rtas_fadump_section *cpu_data_section;
	स्थिर काष्ठा rtas_fadump_mem_काष्ठा *fdm_ptr;

	अगर (fdm_active)
		fdm_ptr = fdm_active;
	अन्यथा
		fdm_ptr = &fdm;

	cpu_data_section = &(fdm_ptr->cpu_state_data);
	seq_म_लिखो(m, "CPU :[%#016llx-%#016llx] %#llx bytes, Dumped: %#llx\n",
		   be64_to_cpu(cpu_data_section->destination_address),
		   be64_to_cpu(cpu_data_section->destination_address) +
		   be64_to_cpu(cpu_data_section->source_len) - 1,
		   be64_to_cpu(cpu_data_section->source_len),
		   be64_to_cpu(cpu_data_section->bytes_dumped));

	seq_म_लिखो(m, "HPTE:[%#016llx-%#016llx] %#llx bytes, Dumped: %#llx\n",
		   be64_to_cpu(fdm_ptr->hpte_region.destination_address),
		   be64_to_cpu(fdm_ptr->hpte_region.destination_address) +
		   be64_to_cpu(fdm_ptr->hpte_region.source_len) - 1,
		   be64_to_cpu(fdm_ptr->hpte_region.source_len),
		   be64_to_cpu(fdm_ptr->hpte_region.bytes_dumped));

	seq_म_लिखो(m, "DUMP: Src: %#016llx, Dest: %#016llx, ",
		   be64_to_cpu(fdm_ptr->rmr_region.source_address),
		   be64_to_cpu(fdm_ptr->rmr_region.destination_address));
	seq_म_लिखो(m, "Size: %#llx, Dumped: %#llx bytes\n",
		   be64_to_cpu(fdm_ptr->rmr_region.source_len),
		   be64_to_cpu(fdm_ptr->rmr_region.bytes_dumped));

	/* Dump is active. Show reserved area start address. */
	अगर (fdm_active) अणु
		seq_म_लिखो(m, "\nMemory above %#016lx is reserved for saving crash dump\n",
			   fadump_conf->reserve_dump_area_start);
	पूर्ण
पूर्ण

अटल व्योम rtas_fadump_trigger(काष्ठा fadump_crash_info_header *fdh,
				स्थिर अक्षर *msg)
अणु
	/* Call ibm,os-term rtas call to trigger firmware assisted dump */
	rtas_os_term((अक्षर *)msg);
पूर्ण

अटल काष्ठा fadump_ops rtas_fadump_ops = अणु
	.fadump_init_mem_काष्ठा		= rtas_fadump_init_mem_काष्ठा,
	.fadump_get_booपंचांगem_min		= rtas_fadump_get_booपंचांगem_min,
	.fadump_रेजिस्टर		= rtas_fadump_रेजिस्टर,
	.fadump_unरेजिस्टर		= rtas_fadump_unरेजिस्टर,
	.fadump_invalidate		= rtas_fadump_invalidate,
	.fadump_process			= rtas_fadump_process,
	.fadump_region_show		= rtas_fadump_region_show,
	.fadump_trigger			= rtas_fadump_trigger,
पूर्ण;

व्योम __init rtas_fadump_dt_scan(काष्ठा fw_dump *fadump_conf, u64 node)
अणु
	पूर्णांक i, size, num_sections;
	स्थिर __be32 *sections;
	स्थिर __be32 *token;

	/*
	 * Check अगर Firmware Assisted dump is supported. अगर yes, check
	 * अगर dump has been initiated on last reboot.
	 */
	token = of_get_flat_dt_prop(node, "ibm,configure-kernel-dump", शून्य);
	अगर (!token)
		वापस;

	fadump_conf->ibm_configure_kernel_dump = be32_to_cpu(*token);
	fadump_conf->ops		= &rtas_fadump_ops;
	fadump_conf->fadump_supported	= 1;

	/* Firmware supports 64-bit value क्रम size, align it to pagesize. */
	fadump_conf->max_copy_size = ALIGN_DOWN(U64_MAX, PAGE_SIZE);

	/*
	 * The 'ibm,kernel-dump' rtas node is present only अगर there is
	 * dump data रुकोing क्रम us.
	 */
	fdm_active = of_get_flat_dt_prop(node, "ibm,kernel-dump", शून्य);
	अगर (fdm_active) अणु
		pr_info("Firmware-assisted dump is active.\n");
		fadump_conf->dump_active = 1;
		rtas_fadump_get_config(fadump_conf, (व्योम *)__pa(fdm_active));
	पूर्ण

	/* Get the sizes required to store dump data क्रम the firmware provided
	 * dump sections.
	 * For each dump section type supported, a 32bit cell which defines
	 * the ID of a supported section followed by two 32 bit cells which
	 * gives the size of the section in bytes.
	 */
	sections = of_get_flat_dt_prop(node, "ibm,configure-kernel-dump-sizes",
					&size);

	अगर (!sections)
		वापस;

	num_sections = size / (3 * माप(u32));

	क्रम (i = 0; i < num_sections; i++, sections += 3) अणु
		u32 type = (u32)of_पढ़ो_number(sections, 1);

		चयन (type) अणु
		हाल RTAS_FADUMP_CPU_STATE_DATA:
			fadump_conf->cpu_state_data_size =
					of_पढ़ो_uदीर्घ(&sections[1], 2);
			अवरोध;
		हाल RTAS_FADUMP_HPTE_REGION:
			fadump_conf->hpte_region_size =
					of_पढ़ो_uदीर्घ(&sections[1], 2);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
