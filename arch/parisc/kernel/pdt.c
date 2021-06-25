<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Page Deallocation Table (PDT) support
 *
 *    The Page Deallocation Table (PDT) is मुख्यtained by firmware and holds a
 *    list of memory addresses in which memory errors were detected.
 *    The list contains both single-bit (correctable) and द्विगुन-bit
 *    (uncorrectable) errors.
 *
 *    Copyright 2017 by Helge Deller <deller@gmx.de>
 *
 *    possible future enhancements:
 *    - add userspace पूर्णांकerface via procfs or sysfs to clear PDT
 */

#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/initrd.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>

#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>
#समावेश <यंत्र/sections.h>

क्रमागत pdt_access_type अणु
	PDT_NONE,
	PDT_PDC,
	PDT_PAT_NEW,
	PDT_PAT_CELL
पूर्ण;

अटल क्रमागत pdt_access_type pdt_type;

/* PDT poll पूर्णांकerval: 1 minute अगर errors, 5 minutes अगर everything OK. */
#घोषणा PDT_POLL_INTERVAL_DEFAULT	(5*60*HZ)
#घोषणा PDT_POLL_INTERVAL_SHORT		(1*60*HZ)
अटल अचिन्हित दीर्घ pdt_poll_पूर्णांकerval = PDT_POLL_INTERVAL_DEFAULT;

/* global PDT status inक्रमmation */
अटल काष्ठा pdc_mem_retinfo pdt_status;

#घोषणा MAX_PDT_TABLE_SIZE	PAGE_SIZE
#घोषणा MAX_PDT_ENTRIES		(MAX_PDT_TABLE_SIZE / माप(अचिन्हित दीर्घ))
अटल अचिन्हित दीर्घ pdt_entry[MAX_PDT_ENTRIES] __page_aligned_bss;

/*
 * Constants क्रम the pdt_entry क्रमmat:
 * A pdt_entry holds the physical address in bits 0-57, bits 58-61 are
 * reserved, bit 62 is the perm bit and bit 63 is the error_type bit.
 * The perm bit indicates whether the error have been verअगरied as a permanent
 * error (value of 1) or has not been verअगरied, and may be transient (value
 * of 0). The error_type bit indicates whether the error is a single bit error
 * (value of 1) or a multiple bit error.
 * On non-PAT machines phys_addr is encoded in bits 0-59 and error_type in bit
 * 63. Those machines करोn't provide the perm bit.
 */

#घोषणा PDT_ADDR_PHYS_MASK	(pdt_type != PDT_PDC ? ~0x3f : ~0x0f)
#घोषणा PDT_ADDR_PERM_ERR	(pdt_type != PDT_PDC ? 2UL : 0UL)
#घोषणा PDT_ADDR_SINGLE_ERR	1UL

/* report PDT entries via /proc/meminfo */
व्योम arch_report_meminfo(काष्ठा seq_file *m)
अणु
	अगर (pdt_type == PDT_NONE)
		वापस;

	seq_म_लिखो(m, "PDT_max_entries: %7lu\n",
			pdt_status.pdt_size);
	seq_म_लिखो(m, "PDT_cur_entries: %7lu\n",
			pdt_status.pdt_entries);
पूर्ण

अटल पूर्णांक get_info_pat_new(व्योम)
अणु
	काष्ठा pdc_pat_mem_retinfo pat_rinfo;
	पूर्णांक ret;

	/* newer PAT machines like C8000 report info क्रम all cells */
	अगर (is_pdc_pat())
		ret = pdc_pat_mem_pdt_info(&pat_rinfo);
	अन्यथा
		वापस PDC_BAD_PROC;

	pdt_status.pdt_size = pat_rinfo.max_pdt_entries;
	pdt_status.pdt_entries = pat_rinfo.current_pdt_entries;
	pdt_status.pdt_status = 0;
	pdt_status.first_dbe_loc = pat_rinfo.first_dbe_loc;
	pdt_status.good_mem = pat_rinfo.good_mem;

	वापस ret;
पूर्ण

अटल पूर्णांक get_info_pat_cell(व्योम)
अणु
	काष्ठा pdc_pat_mem_cell_pdt_retinfo cell_rinfo;
	पूर्णांक ret;

	/* older PAT machines like rp5470 report cell info only */
	अगर (is_pdc_pat())
		ret = pdc_pat_mem_pdt_cell_info(&cell_rinfo, parisc_cell_num);
	अन्यथा
		वापस PDC_BAD_PROC;

	pdt_status.pdt_size = cell_rinfo.max_pdt_entries;
	pdt_status.pdt_entries = cell_rinfo.current_pdt_entries;
	pdt_status.pdt_status = 0;
	pdt_status.first_dbe_loc = cell_rinfo.first_dbe_loc;
	pdt_status.good_mem = cell_rinfo.good_mem;

	वापस ret;
पूर्ण

अटल व्योम report_mem_err(अचिन्हित दीर्घ pde)
अणु
	काष्ठा pdc_pat_mem_phys_mem_location loc;
	अचिन्हित दीर्घ addr;
	अक्षर dimm_txt[32];

	addr = pde & PDT_ADDR_PHYS_MASK;

	/* show DIMM slot description on PAT machines */
	अगर (is_pdc_pat()) अणु
		pdc_pat_mem_get_dimm_phys_location(&loc, addr);
		प्र_लिखो(dimm_txt, "DIMM slot %02x, ", loc.dimm_slot);
	पूर्ण अन्यथा
		dimm_txt[0] = 0;

	pr_warn("PDT: BAD MEMORY at 0x%08lx, %s%s%s-bit error.\n",
		addr, dimm_txt,
		pde & PDT_ADDR_PERM_ERR ? "permanent ":"",
		pde & PDT_ADDR_SINGLE_ERR ? "single":"multi");
पूर्ण


/*
 * pdc_pdt_init()
 *
 * Initialize kernel PDT काष्ठाures, पढ़ो initial PDT table from firmware,
 * report all current PDT entries and mark bad memory with memblock_reserve()
 * to aव्योम that the kernel will use broken memory areas.
 *
 */
व्योम __init pdc_pdt_init(व्योम)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ entries;
	काष्ठा pdc_mem_पढ़ो_pdt pdt_पढ़ो_ret;

	pdt_type = PDT_PAT_NEW;
	ret = get_info_pat_new();

	अगर (ret != PDC_OK) अणु
		pdt_type = PDT_PAT_CELL;
		ret = get_info_pat_cell();
	पूर्ण

	अगर (ret != PDC_OK) अणु
		pdt_type = PDT_PDC;
		/* non-PAT machines provide the standard PDC call */
		ret = pdc_mem_pdt_info(&pdt_status);
	पूर्ण

	अगर (ret != PDC_OK) अणु
		pdt_type = PDT_NONE;
		pr_info("PDT: Firmware does not provide any page deallocation"
			" information.\n");
		वापस;
	पूर्ण

	entries = pdt_status.pdt_entries;
	अगर (WARN_ON(entries > MAX_PDT_ENTRIES))
		entries = pdt_status.pdt_entries = MAX_PDT_ENTRIES;

	pr_info("PDT: type %s, size %lu, entries %lu, status %lu, dbe_loc 0x%lx,"
		" good_mem %lu MB\n",
			pdt_type == PDT_PDC ? __stringअगरy(PDT_PDC) :
			pdt_type == PDT_PAT_CELL ? __stringअगरy(PDT_PAT_CELL)
						 : __stringअगरy(PDT_PAT_NEW),
			pdt_status.pdt_size, pdt_status.pdt_entries,
			pdt_status.pdt_status, pdt_status.first_dbe_loc,
			pdt_status.good_mem / 1024 / 1024);

	अगर (entries == 0) अणु
		pr_info("PDT: Firmware reports all memory OK.\n");
		वापस;
	पूर्ण

	अगर (pdt_status.first_dbe_loc &&
		pdt_status.first_dbe_loc <= __pa((अचिन्हित दीर्घ)&_end))
		pr_crit("CRITICAL: Bad memory inside kernel image memory area!\n");

	pr_warn("PDT: Firmware reports %lu entries of faulty memory:\n",
		entries);

	अगर (pdt_type == PDT_PDC)
		ret = pdc_mem_pdt_पढ़ो_entries(&pdt_पढ़ो_ret, pdt_entry);
	अन्यथा अणु
#अगर_घोषित CONFIG_64BIT
		काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo pat_pret;

		अगर (pdt_type == PDT_PAT_CELL)
			ret = pdc_pat_mem_पढ़ो_cell_pdt(&pat_pret, pdt_entry,
				MAX_PDT_ENTRIES);
		अन्यथा
			ret = pdc_pat_mem_पढ़ो_pd_pdt(&pat_pret, pdt_entry,
				MAX_PDT_TABLE_SIZE, 0);
#अन्यथा
		ret = PDC_BAD_PROC;
#पूर्ण_अगर
	पूर्ण

	अगर (ret != PDC_OK) अणु
		pdt_type = PDT_NONE;
		pr_warn("PDT: Get PDT entries failed with %d\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < pdt_status.pdt_entries; i++) अणु
		अचिन्हित दीर्घ addr;

		report_mem_err(pdt_entry[i]);

		addr = pdt_entry[i] & PDT_ADDR_PHYS_MASK;
		अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) &&
			addr >= initrd_start && addr < initrd_end)
			pr_crit("CRITICAL: initrd possibly broken "
				"due to bad memory!\n");

		/* mark memory page bad */
		memblock_reserve(pdt_entry[i] & PAGE_MASK, PAGE_SIZE);
		num_poisoned_pages_inc();
	पूर्ण
पूर्ण


/*
 * This is the PDT kernel thपढ़ो मुख्य loop.
 */

अटल पूर्णांक pdt_मुख्यloop(व्योम *unused)
अणु
	काष्ठा pdc_mem_पढ़ो_pdt pdt_पढ़ो_ret;
	काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo pat_pret __maybe_unused;
	अचिन्हित दीर्घ old_num_entries;
	अचिन्हित दीर्घ *bad_mem_ptr;
	पूर्णांक num, ret;

	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		old_num_entries = pdt_status.pdt_entries;

		schedule_समयout(pdt_poll_पूर्णांकerval);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Do we have new PDT entries? */
		चयन (pdt_type) अणु
		हाल PDT_PAT_NEW:
			ret = get_info_pat_new();
			अवरोध;
		हाल PDT_PAT_CELL:
			ret = get_info_pat_cell();
			अवरोध;
		शेष:
			ret = pdc_mem_pdt_info(&pdt_status);
			अवरोध;
		पूर्ण

		अगर (ret != PDC_OK) अणु
			pr_warn("PDT: unexpected failure %d\n", ret);
			वापस -EINVAL;
		पूर्ण

		/* अगर no new PDT entries, just रुको again */
		num = pdt_status.pdt_entries - old_num_entries;
		अगर (num <= 0)
			जारी;

		/* decrease poll पूर्णांकerval in हाल we found memory errors */
		अगर (pdt_status.pdt_entries &&
			pdt_poll_पूर्णांकerval == PDT_POLL_INTERVAL_DEFAULT)
			pdt_poll_पूर्णांकerval = PDT_POLL_INTERVAL_SHORT;

		/* limit entries to get */
		अगर (num > MAX_PDT_ENTRIES) अणु
			num = MAX_PDT_ENTRIES;
			pdt_status.pdt_entries = old_num_entries + num;
		पूर्ण

		/* get new entries */
		चयन (pdt_type) अणु
#अगर_घोषित CONFIG_64BIT
		हाल PDT_PAT_CELL:
			अगर (pdt_status.pdt_entries > MAX_PDT_ENTRIES) अणु
				pr_crit("PDT: too many entries.\n");
				वापस -ENOMEM;
			पूर्ण
			ret = pdc_pat_mem_पढ़ो_cell_pdt(&pat_pret, pdt_entry,
				MAX_PDT_ENTRIES);
			bad_mem_ptr = &pdt_entry[old_num_entries];
			अवरोध;
		हाल PDT_PAT_NEW:
			ret = pdc_pat_mem_पढ़ो_pd_pdt(&pat_pret,
				pdt_entry,
				num * माप(अचिन्हित दीर्घ),
				old_num_entries * माप(अचिन्हित दीर्घ));
			bad_mem_ptr = &pdt_entry[0];
			अवरोध;
#पूर्ण_अगर
		शेष:
			ret = pdc_mem_pdt_पढ़ो_entries(&pdt_पढ़ो_ret,
				pdt_entry);
			bad_mem_ptr = &pdt_entry[old_num_entries];
			अवरोध;
		पूर्ण

		/* report and mark memory broken */
		जबतक (num--) अणु
			अचिन्हित दीर्घ pde = *bad_mem_ptr++;

			report_mem_err(pde);

#अगर_घोषित CONFIG_MEMORY_FAILURE
			अगर ((pde & PDT_ADDR_PERM_ERR) ||
			    ((pde & PDT_ADDR_SINGLE_ERR) == 0))
				memory_failure(pde >> PAGE_SHIFT, 0);
			अन्यथा
				soft_offline_page(pde >> PAGE_SHIFT, 0);
#अन्यथा
			pr_crit("PDT: memory error at 0x%lx ignored.\n"
				"Rebuild kernel with CONFIG_MEMORY_FAILURE=y "
				"for real handling.\n",
				pde & PDT_ADDR_PHYS_MASK);
#पूर्ण_अगर

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक __init pdt_initcall(व्योम)
अणु
	काष्ठा task_काष्ठा *kpdtd_task;

	अगर (pdt_type == PDT_NONE)
		वापस -ENODEV;

	kpdtd_task = kthपढ़ो_create(pdt_मुख्यloop, शून्य, "kpdtd");
	अगर (IS_ERR(kpdtd_task))
		वापस PTR_ERR(kpdtd_task);

	wake_up_process(kpdtd_task);

	वापस 0;
पूर्ण

late_initcall(pdt_initcall);
