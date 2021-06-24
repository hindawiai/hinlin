<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tboot.c: मुख्य implementation of helper functions used by kernel क्रम
 *          runसमय support of Intel(R) Trusted Execution Technology
 *
 * Copyright (c) 2006-2009, Intel Corporation
 */

#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/init_task.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/dmar.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pfn.h>
#समावेश <linux/mm.h>
#समावेश <linux/tboot.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/पन.स>

#समावेश "../realmode/rm/wakeup.h"

/* Global poपूर्णांकer to shared data; शून्य means no measured launch. */
अटल काष्ठा tboot *tboot __पढ़ो_mostly;

/* समयout क्रम APs (in secs) to enter रुको-क्रम-SIPI state during shutकरोwn */
#घोषणा AP_WAIT_TIMEOUT		1

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"tboot: " fmt

अटल u8 tboot_uuid[16] __initdata = TBOOT_UUID;

bool tboot_enabled(व्योम)
अणु
	वापस tboot != शून्य;
पूर्ण

/* noअंतरभूत to prevent gcc from warning about dereferencing स्थिरant fixaddr */
अटल noअंतरभूत __init bool check_tboot_version(व्योम)
अणु
	अगर (स_भेद(&tboot_uuid, &tboot->uuid, माप(tboot->uuid))) अणु
		pr_warn("tboot at 0x%llx is invalid\n", boot_params.tboot_addr);
		वापस false;
	पूर्ण

	अगर (tboot->version < 5) अणु
		pr_warn("tboot version is invalid: %u\n", tboot->version);
		वापस false;
	पूर्ण

	pr_info("found shared page at phys addr 0x%llx:\n",
		boot_params.tboot_addr);
	pr_debug("version: %d\n", tboot->version);
	pr_debug("log_addr: 0x%08x\n", tboot->log_addr);
	pr_debug("shutdown_entry: 0x%x\n", tboot->shutकरोwn_entry);
	pr_debug("tboot_base: 0x%08x\n", tboot->tboot_base);
	pr_debug("tboot_size: 0x%x\n", tboot->tboot_size);

	वापस true;
पूर्ण

व्योम __init tboot_probe(व्योम)
अणु
	/* Look क्रम valid page-aligned address क्रम shared page. */
	अगर (!boot_params.tboot_addr)
		वापस;
	/*
	 * also verअगरy that it is mapped as we expect it beक्रमe calling
	 * set_fixmap(), to reduce chance of garbage value causing crash
	 */
	अगर (!e820__mapped_any(boot_params.tboot_addr,
			     boot_params.tboot_addr, E820_TYPE_RESERVED)) अणु
		pr_warn("non-0 tboot_addr but it is not of type E820_TYPE_RESERVED\n");
		वापस;
	पूर्ण

	/* Map and check क्रम tboot UUID. */
	set_fixmap(FIX_TBOOT_BASE, boot_params.tboot_addr);
	tboot = (व्योम *)fix_to_virt(FIX_TBOOT_BASE);
	अगर (!check_tboot_version())
		tboot = शून्य;
पूर्ण

अटल pgd_t *tboot_pg_dir;
अटल काष्ठा mm_काष्ठा tboot_mm = अणु
	.mm_rb          = RB_ROOT,
	.pgd            = swapper_pg_dir,
	.mm_users       = ATOMIC_INIT(2),
	.mm_count       = ATOMIC_INIT(1),
	.ग_लिखो_protect_seq = SEQCNT_ZERO(tboot_mm.ग_लिखो_protect_seq),
	MMAP_LOCK_INITIALIZER(init_mm)
	.page_table_lock =  __SPIN_LOCK_UNLOCKED(init_mm.page_table_lock),
	.mmlist         = LIST_HEAD_INIT(init_mm.mmlist),
पूर्ण;

अटल अंतरभूत व्योम चयन_to_tboot_pt(व्योम)
अणु
	ग_लिखो_cr3(virt_to_phys(tboot_pg_dir));
पूर्ण

अटल पूर्णांक map_tboot_page(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ pfn,
			  pgprot_t prot)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(&tboot_mm, vaddr);
	p4d = p4d_alloc(&tboot_mm, pgd, vaddr);
	अगर (!p4d)
		वापस -1;
	pud = pud_alloc(&tboot_mm, p4d, vaddr);
	अगर (!pud)
		वापस -1;
	pmd = pmd_alloc(&tboot_mm, pud, vaddr);
	अगर (!pmd)
		वापस -1;
	pte = pte_alloc_map(&tboot_mm, pmd, vaddr);
	अगर (!pte)
		वापस -1;
	set_pte_at(&tboot_mm, vaddr, pte, pfn_pte(pfn, prot));
	pte_unmap(pte);

	/*
	 * PTI poisons low addresses in the kernel page tables in the
	 * name of making them unusable क्रम userspace.  To execute
	 * code at such a low address, the poison must be cleared.
	 *
	 * Note: 'pgd' actually माला_लो set in p4d_alloc() _or_
	 * pud_alloc() depending on 4/5-level paging.
	 */
	pgd->pgd &= ~_PAGE_NX;

	वापस 0;
पूर्ण

अटल पूर्णांक map_tboot_pages(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ start_pfn,
			   अचिन्हित दीर्घ nr)
अणु
	/* Reuse the original kernel mapping */
	tboot_pg_dir = pgd_alloc(&tboot_mm);
	अगर (!tboot_pg_dir)
		वापस -1;

	क्रम (; nr > 0; nr--, vaddr += PAGE_SIZE, start_pfn++) अणु
		अगर (map_tboot_page(vaddr, start_pfn, PAGE_KERNEL_EXEC))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tboot_create_trampoline(व्योम)
अणु
	u32 map_base, map_size;

	/* Create identity map क्रम tboot shutकरोwn code. */
	map_base = PFN_DOWN(tboot->tboot_base);
	map_size = PFN_UP(tboot->tboot_size);
	अगर (map_tboot_pages(map_base << PAGE_SHIFT, map_base, map_size))
		panic("tboot: Error mapping tboot pages (mfns) @ 0x%x, 0x%x\n",
		      map_base, map_size);
पूर्ण

#अगर_घोषित CONFIG_ACPI_SLEEP

अटल व्योम add_mac_region(phys_addr_t start, अचिन्हित दीर्घ size)
अणु
	काष्ठा tboot_mac_region *mr;
	phys_addr_t end = start + size;

	अगर (tboot->num_mac_regions >= MAX_TB_MAC_REGIONS)
		panic("tboot: Too many MAC regions\n");

	अगर (start && size) अणु
		mr = &tboot->mac_regions[tboot->num_mac_regions++];
		mr->start = round_करोwn(start, PAGE_SIZE);
		mr->size  = round_up(end, PAGE_SIZE) - mr->start;
	पूर्ण
पूर्ण

अटल पूर्णांक tboot_setup_sleep(व्योम)
अणु
	पूर्णांक i;

	tboot->num_mac_regions = 0;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		अगर ((e820_table->entries[i].type != E820_TYPE_RAM)
		 && (e820_table->entries[i].type != E820_TYPE_RESERVED_KERN))
			जारी;

		add_mac_region(e820_table->entries[i].addr, e820_table->entries[i].size);
	पूर्ण

	tboot->acpi_sinfo.kernel_s3_resume_vector =
		real_mode_header->wakeup_start;

	वापस 0;
पूर्ण

#अन्यथा /* no CONFIG_ACPI_SLEEP */

अटल पूर्णांक tboot_setup_sleep(व्योम)
अणु
	/* S3 shutकरोwn requested, but S3 not supported by the kernel... */
	BUG();
	वापस -1;
पूर्ण

#पूर्ण_अगर

व्योम tboot_shutकरोwn(u32 shutकरोwn_type)
अणु
	व्योम (*shutकरोwn)(व्योम);

	अगर (!tboot_enabled())
		वापस;

	/*
	 * अगर we're being called beक्रमe the 1:1 mapping is set up then just
	 * वापस and let the normal shutकरोwn happen; this should only be
	 * due to very early panic()
	 */
	अगर (!tboot_pg_dir)
		वापस;

	/* अगर this is S3 then set regions to MAC */
	अगर (shutकरोwn_type == TB_SHUTDOWN_S3)
		अगर (tboot_setup_sleep())
			वापस;

	tboot->shutकरोwn_type = shutकरोwn_type;

	चयन_to_tboot_pt();

	shutकरोwn = (व्योम(*)(व्योम))(अचिन्हित दीर्घ)tboot->shutकरोwn_entry;
	shutकरोwn();

	/* should not reach here */
	जबतक (1)
		halt();
पूर्ण

अटल व्योम tboot_copy_fadt(स्थिर काष्ठा acpi_table_fadt *fadt)
अणु
#घोषणा TB_COPY_GAS(tbg, g)			\
	tbg.space_id     = g.space_id;		\
	tbg.bit_width    = g.bit_width;		\
	tbg.bit_offset   = g.bit_offset;	\
	tbg.access_width = g.access_width;	\
	tbg.address      = g.address;

	TB_COPY_GAS(tboot->acpi_sinfo.pm1a_cnt_blk, fadt->xpm1a_control_block);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1b_cnt_blk, fadt->xpm1b_control_block);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1a_evt_blk, fadt->xpm1a_event_block);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1b_evt_blk, fadt->xpm1b_event_block);

	/*
	 * We need phys addr of waking vector, but can't use virt_to_phys() on
	 * &acpi_gbl_FACS because it is ioremap'ed, so calc from FACS phys
	 * addr.
	 */
	tboot->acpi_sinfo.wakeup_vector = fadt->facs +
		दुरत्व(काष्ठा acpi_table_facs, firmware_waking_vector);
पूर्ण

अटल पूर्णांक tboot_sleep(u8 sleep_state, u32 pm1a_control, u32 pm1b_control)
अणु
	अटल u32 acpi_shutकरोwn_map[ACPI_S_STATE_COUNT] = अणु
		/* S0,1,2: */ -1, -1, -1,
		/* S3: */ TB_SHUTDOWN_S3,
		/* S4: */ TB_SHUTDOWN_S4,
		/* S5: */ TB_SHUTDOWN_S5 पूर्ण;

	अगर (!tboot_enabled())
		वापस 0;

	tboot_copy_fadt(&acpi_gbl_FADT);
	tboot->acpi_sinfo.pm1a_cnt_val = pm1a_control;
	tboot->acpi_sinfo.pm1b_cnt_val = pm1b_control;
	/* we always use the 32b wakeup vector */
	tboot->acpi_sinfo.vector_width = 32;

	अगर (sleep_state >= ACPI_S_STATE_COUNT ||
	    acpi_shutकरोwn_map[sleep_state] == -1) अणु
		pr_warn("unsupported sleep state 0x%x\n", sleep_state);
		वापस -1;
	पूर्ण

	tboot_shutकरोwn(acpi_shutकरोwn_map[sleep_state]);
	वापस 0;
पूर्ण

अटल पूर्णांक tboot_extended_sleep(u8 sleep_state, u32 val_a, u32 val_b)
अणु
	अगर (!tboot_enabled())
		वापस 0;

	pr_warn("tboot is not able to suspend on platforms with reduced hardware sleep (ACPIv5)");
	वापस -ENODEV;
पूर्ण

अटल atomic_t ap_wfs_count;

अटल पूर्णांक tboot_रुको_क्रम_aps(पूर्णांक num_aps)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = AP_WAIT_TIMEOUT*HZ;
	जबतक (atomic_पढ़ो((atomic_t *)&tboot->num_in_wfs) != num_aps &&
	       समयout) अणु
		mdelay(1);
		समयout--;
	पूर्ण

	अगर (समयout)
		pr_warn("tboot wait for APs timeout\n");

	वापस !(atomic_पढ़ो((atomic_t *)&tboot->num_in_wfs) == num_aps);
पूर्ण

अटल पूर्णांक tboot_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	atomic_inc(&ap_wfs_count);
	अगर (num_online_cpus() == 1) अणु
		अगर (tboot_रुको_क्रम_aps(atomic_पढ़ो(&ap_wfs_count)))
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा TBOOT_LOG_UUID	अणु 0x26, 0x25, 0x19, 0xc0, 0x30, 0x6b, 0xb4, 0x4d, \
			  0x4c, 0x84, 0xa3, 0xe9, 0x53, 0xb8, 0x81, 0x74 पूर्ण

#घोषणा TBOOT_SERIAL_LOG_ADDR	0x60000
#घोषणा TBOOT_SERIAL_LOG_SIZE	0x08000
#घोषणा LOG_MAX_SIZE_OFF	16
#घोषणा LOG_BUF_OFF		24

अटल uपूर्णांक8_t tboot_log_uuid[16] = TBOOT_LOG_UUID;

अटल sमाप_प्रकार tboot_log_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	व्योम __iomem *log_base;
	u8 log_uuid[16];
	u32 max_size;
	व्योम *kbuf;
	पूर्णांक ret = -EFAULT;

	log_base = ioremap(TBOOT_SERIAL_LOG_ADDR, TBOOT_SERIAL_LOG_SIZE);
	अगर (!log_base)
		वापस ret;

	स_नकल_fromio(log_uuid, log_base, माप(log_uuid));
	अगर (स_भेद(&tboot_log_uuid, log_uuid, माप(log_uuid)))
		जाओ err_iounmap;

	max_size = पढ़ोl(log_base + LOG_MAX_SIZE_OFF);
	अगर (*ppos >= max_size) अणु
		ret = 0;
		जाओ err_iounmap;
	पूर्ण

	अगर (*ppos + count > max_size)
		count = max_size - *ppos;

	kbuf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!kbuf) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	स_नकल_fromio(kbuf, log_base + LOG_BUF_OFF + *ppos, count);
	अगर (copy_to_user(user_buf, kbuf, count))
		जाओ err_kमुक्त;

	*ppos += count;

	ret = count;

err_kमुक्त:
	kमुक्त(kbuf);

err_iounmap:
	iounmap(log_base);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations tboot_log_fops = अणु
	.पढ़ो	= tboot_log_पढ़ो,
	.llseek	= शेष_llseek,
पूर्ण;

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल __init पूर्णांक tboot_late_init(व्योम)
अणु
	अगर (!tboot_enabled())
		वापस 0;

	tboot_create_trampoline();

	atomic_set(&ap_wfs_count, 0);
	cpuhp_setup_state(CPUHP_AP_X86_TBOOT_DYING, "x86/tboot:dying", शून्य,
			  tboot_dying_cpu);
#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_create_file("tboot_log", S_IRUSR,
			arch_debugfs_dir, शून्य, &tboot_log_fops);
#पूर्ण_अगर

	acpi_os_set_prepare_sleep(&tboot_sleep);
	acpi_os_set_prepare_extended_sleep(&tboot_extended_sleep);
	वापस 0;
पूर्ण

late_initcall(tboot_late_init);

/*
 * TXT configuration रेजिस्टरs (offsets from TXT_अणुPUB, PRIVपूर्ण_CONFIG_REGS_BASE)
 */

#घोषणा TXT_PUB_CONFIG_REGS_BASE       0xfed30000
#घोषणा TXT_PRIV_CONFIG_REGS_BASE      0xfed20000

/* # pages क्रम each config regs space - used by fixmap */
#घोषणा NR_TXT_CONFIG_PAGES     ((TXT_PUB_CONFIG_REGS_BASE -                \
				  TXT_PRIV_CONFIG_REGS_BASE) >> PAGE_SHIFT)

/* offsets from pub/priv config space */
#घोषणा TXTCR_HEAP_BASE             0x0300
#घोषणा TXTCR_HEAP_SIZE             0x0308

#घोषणा SHA1_SIZE      20

काष्ठा sha1_hash अणु
	u8 hash[SHA1_SIZE];
पूर्ण;

काष्ठा sinit_mle_data अणु
	u32               version;             /* currently 6 */
	काष्ठा sha1_hash  bios_acm_id;
	u32               edx_senter_flags;
	u64               mseg_valid;
	काष्ठा sha1_hash  sinit_hash;
	काष्ठा sha1_hash  mle_hash;
	काष्ठा sha1_hash  sपंचांग_hash;
	काष्ठा sha1_hash  lcp_policy_hash;
	u32               lcp_policy_control;
	u32               rlp_wakeup_addr;
	u32               reserved;
	u32               num_mdrs;
	u32               mdrs_off;
	u32               num_vtd_dmars;
	u32               vtd_dmars_off;
पूर्ण __packed;

काष्ठा acpi_table_header *tboot_get_dmar_table(काष्ठा acpi_table_header *dmar_tbl)
अणु
	व्योम *heap_base, *heap_ptr, *config;

	अगर (!tboot_enabled())
		वापस dmar_tbl;

	/*
	 * ACPI tables may not be DMA रक्षित by tboot, so use DMAR copy
	 * SINIT saved in SinitMleData in TXT heap (which is DMA रक्षित)
	 */

	/* map config space in order to get heap addr */
	config = ioremap(TXT_PUB_CONFIG_REGS_BASE, NR_TXT_CONFIG_PAGES *
			 PAGE_SIZE);
	अगर (!config)
		वापस शून्य;

	/* now map TXT heap */
	heap_base = ioremap(*(u64 *)(config + TXTCR_HEAP_BASE),
			    *(u64 *)(config + TXTCR_HEAP_SIZE));
	iounmap(config);
	अगर (!heap_base)
		वापस शून्य;

	/* walk heap to SinitMleData */
	/* skip BiosData */
	heap_ptr = heap_base + *(u64 *)heap_base;
	/* skip OsMleData */
	heap_ptr += *(u64 *)heap_ptr;
	/* skip OsSinitData */
	heap_ptr += *(u64 *)heap_ptr;
	/* now poपूर्णांकs to SinitMleDataSize; set to SinitMleData */
	heap_ptr += माप(u64);
	/* get addr of DMAR table */
	dmar_tbl = (काष्ठा acpi_table_header *)(heap_ptr +
		   ((काष्ठा sinit_mle_data *)heap_ptr)->vtd_dmars_off -
		   माप(u64));

	/* करोn't unmap heap because dmar.c needs access to this */

	वापस dmar_tbl;
पूर्ण

पूर्णांक tboot_क्रमce_iommu(व्योम)
अणु
	अगर (!tboot_enabled())
		वापस 0;

	अगर (no_iommu || dmar_disabled)
		pr_warn("Forcing Intel-IOMMU to enabled\n");

	dmar_disabled = 0;
	no_iommu = 0;

	वापस 1;
पूर्ण
