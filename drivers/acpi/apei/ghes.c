<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * APEI Generic Hardware Error Source support
 *
 * Generic Hardware Error Source provides a way to report platक्रमm
 * hardware errors (such as that from chipset). It works in so called
 * "Firmware First" mode, that is, hardware errors are reported to
 * firmware firstly, then reported to Linux by firmware. This way,
 * some non-standard hardware error रेजिस्टरs or non-standard hardware
 * link can be checked by firmware to produce more hardware error
 * inक्रमmation क्रम Linux.
 *
 * For more inक्रमmation about Generic Hardware Error Source, please
 * refer to ACPI Specअगरication version 4.0, section 17.3.2.6
 *
 * Copyright 2010,2011 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/arm_sdei.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cper.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/llist.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/pci.h>
#समावेश <linux/pfn.h>
#समावेश <linux/aer.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/uuid.h>
#समावेश <linux/ras.h>
#समावेश <linux/task_work.h>

#समावेश <acpi/actbl1.h>
#समावेश <acpi/ghes.h>
#समावेश <acpi/apei.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <ras/ras_event.h>

#समावेश "apei-internal.h"

#घोषणा GHES_PFX	"GHES: "

#घोषणा GHES_ESTATUS_MAX_SIZE		65536
#घोषणा GHES_ESOURCE_PREALLOC_MAX_SIZE	65536

#घोषणा GHES_ESTATUS_POOL_MIN_ALLOC_ORDER 3

/* This is just an estimation क्रम memory pool allocation */
#घोषणा GHES_ESTATUS_CACHE_AVG_SIZE	512

#घोषणा GHES_ESTATUS_CACHES_SIZE	4

#घोषणा GHES_ESTATUS_IN_CACHE_MAX_NSEC	10000000000ULL
/* Prevent too many caches are allocated because of RCU */
#घोषणा GHES_ESTATUS_CACHE_ALLOCED_MAX	(GHES_ESTATUS_CACHES_SIZE * 3 / 2)

#घोषणा GHES_ESTATUS_CACHE_LEN(estatus_len)			\
	(माप(काष्ठा ghes_estatus_cache) + (estatus_len))
#घोषणा GHES_ESTATUS_FROM_CACHE(estatus_cache)			\
	((काष्ठा acpi_hest_generic_status *)				\
	 ((काष्ठा ghes_estatus_cache *)(estatus_cache) + 1))

#घोषणा GHES_ESTATUS_NODE_LEN(estatus_len)			\
	(माप(काष्ठा ghes_estatus_node) + (estatus_len))
#घोषणा GHES_ESTATUS_FROM_NODE(estatus_node)			\
	((काष्ठा acpi_hest_generic_status *)				\
	 ((काष्ठा ghes_estatus_node *)(estatus_node) + 1))

#घोषणा GHES_VENDOR_ENTRY_LEN(gdata_len)                               \
	(माप(काष्ठा ghes_venकरोr_record_entry) + (gdata_len))
#घोषणा GHES_GDATA_FROM_VENDOR_ENTRY(venकरोr_entry)                     \
	((काष्ठा acpi_hest_generic_data *)                              \
	((काष्ठा ghes_venकरोr_record_entry *)(venकरोr_entry) + 1))

/*
 *  NMI-like notअगरications vary by architecture, beक्रमe the compiler can prune
 *  unused अटल functions it needs a value क्रम these क्रमागतs.
 */
#अगर_अघोषित CONFIG_ARM_SDE_INTERFACE
#घोषणा FIX_APEI_GHES_SDEI_NORMAL	__end_of_fixed_addresses
#घोषणा FIX_APEI_GHES_SDEI_CRITICAL	__end_of_fixed_addresses
#पूर्ण_अगर

अटल अंतरभूत bool is_hest_type_generic_v2(काष्ठा ghes *ghes)
अणु
	वापस ghes->generic->header.type == ACPI_HEST_TYPE_GENERIC_ERROR_V2;
पूर्ण

/*
 * This driver isn't really modular, however क्रम the समय being,
 * continuing to use module_param is the easiest way to reमुख्य
 * compatible with existing boot arg use हालs.
 */
bool ghes_disable;
module_param_named(disable, ghes_disable, bool, 0);

/*
 * All error sources notअगरied with HED (Hardware Error Device) share a
 * single notअगरier callback, so they need to be linked and checked one
 * by one. This holds true क्रम NMI too.
 *
 * RCU is used क्रम these lists, so ghes_list_mutex is only used क्रम
 * list changing, not क्रम traversing.
 */
अटल LIST_HEAD(ghes_hed);
अटल DEFINE_MUTEX(ghes_list_mutex);

/*
 * Because the memory area used to transfer hardware error inक्रमmation
 * from BIOS to Linux can be determined only in NMI, IRQ or समयr
 * handler, but general ioremap can not be used in atomic context, so
 * the fixmap is used instead.
 *
 * This spinlock is used to prevent the fixmap entry from being used
 * simultaneously.
 */
अटल DEFINE_SPINLOCK(ghes_notअगरy_lock_irq);

काष्ठा ghes_venकरोr_record_entry अणु
	काष्ठा work_काष्ठा work;
	पूर्णांक error_severity;
	अक्षर venकरोr_record[];
पूर्ण;

अटल काष्ठा gen_pool *ghes_estatus_pool;
अटल अचिन्हित दीर्घ ghes_estatus_pool_size_request;

अटल काष्ठा ghes_estatus_cache *ghes_estatus_caches[GHES_ESTATUS_CACHES_SIZE];
अटल atomic_t ghes_estatus_cache_alloced;

अटल पूर्णांक ghes_panic_समयout __पढ़ो_mostly = 30;

अटल व्योम __iomem *ghes_map(u64 pfn, क्रमागत fixed_addresses fixmap_idx)
अणु
	phys_addr_t paddr;
	pgprot_t prot;

	paddr = PFN_PHYS(pfn);
	prot = arch_apei_get_mem_attribute(paddr);
	__set_fixmap(fixmap_idx, paddr, prot);

	वापस (व्योम __iomem *) __fix_to_virt(fixmap_idx);
पूर्ण

अटल व्योम ghes_unmap(व्योम __iomem *vaddr, क्रमागत fixed_addresses fixmap_idx)
अणु
	पूर्णांक _idx = virt_to_fix((अचिन्हित दीर्घ)vaddr);

	WARN_ON_ONCE(fixmap_idx != _idx);
	clear_fixmap(fixmap_idx);
पूर्ण

पूर्णांक ghes_estatus_pool_init(पूर्णांक num_ghes)
अणु
	अचिन्हित दीर्घ addr, len;
	पूर्णांक rc;

	ghes_estatus_pool = gen_pool_create(GHES_ESTATUS_POOL_MIN_ALLOC_ORDER, -1);
	अगर (!ghes_estatus_pool)
		वापस -ENOMEM;

	len = GHES_ESTATUS_CACHE_AVG_SIZE * GHES_ESTATUS_CACHE_ALLOCED_MAX;
	len += (num_ghes * GHES_ESOURCE_PREALLOC_MAX_SIZE);

	ghes_estatus_pool_size_request = PAGE_ALIGN(len);
	addr = (अचिन्हित दीर्घ)vदो_स्मृति(PAGE_ALIGN(len));
	अगर (!addr)
		जाओ err_pool_alloc;

	rc = gen_pool_add(ghes_estatus_pool, addr, PAGE_ALIGN(len), -1);
	अगर (rc)
		जाओ err_pool_add;

	वापस 0;

err_pool_add:
	vमुक्त((व्योम *)addr);

err_pool_alloc:
	gen_pool_destroy(ghes_estatus_pool);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक map_gen_v2(काष्ठा ghes *ghes)
अणु
	वापस apei_map_generic_address(&ghes->generic_v2->पढ़ो_ack_रेजिस्टर);
पूर्ण

अटल व्योम unmap_gen_v2(काष्ठा ghes *ghes)
अणु
	apei_unmap_generic_address(&ghes->generic_v2->पढ़ो_ack_रेजिस्टर);
पूर्ण

अटल व्योम ghes_ack_error(काष्ठा acpi_hest_generic_v2 *gv2)
अणु
	पूर्णांक rc;
	u64 val = 0;

	rc = apei_पढ़ो(&val, &gv2->पढ़ो_ack_रेजिस्टर);
	अगर (rc)
		वापस;

	val &= gv2->पढ़ो_ack_preserve << gv2->पढ़ो_ack_रेजिस्टर.bit_offset;
	val |= gv2->पढ़ो_ack_ग_लिखो    << gv2->पढ़ो_ack_रेजिस्टर.bit_offset;

	apei_ग_लिखो(val, &gv2->पढ़ो_ack_रेजिस्टर);
पूर्ण

अटल काष्ठा ghes *ghes_new(काष्ठा acpi_hest_generic *generic)
अणु
	काष्ठा ghes *ghes;
	अचिन्हित पूर्णांक error_block_length;
	पूर्णांक rc;

	ghes = kzalloc(माप(*ghes), GFP_KERNEL);
	अगर (!ghes)
		वापस ERR_PTR(-ENOMEM);

	ghes->generic = generic;
	अगर (is_hest_type_generic_v2(ghes)) अणु
		rc = map_gen_v2(ghes);
		अगर (rc)
			जाओ err_मुक्त;
	पूर्ण

	rc = apei_map_generic_address(&generic->error_status_address);
	अगर (rc)
		जाओ err_unmap_पढ़ो_ack_addr;
	error_block_length = generic->error_block_length;
	अगर (error_block_length > GHES_ESTATUS_MAX_SIZE) अणु
		pr_warn(FW_WARN GHES_PFX
			"Error status block length is too long: %u for "
			"generic hardware error source: %d.\n",
			error_block_length, generic->header.source_id);
		error_block_length = GHES_ESTATUS_MAX_SIZE;
	पूर्ण
	ghes->estatus = kदो_स्मृति(error_block_length, GFP_KERNEL);
	अगर (!ghes->estatus) अणु
		rc = -ENOMEM;
		जाओ err_unmap_status_addr;
	पूर्ण

	वापस ghes;

err_unmap_status_addr:
	apei_unmap_generic_address(&generic->error_status_address);
err_unmap_पढ़ो_ack_addr:
	अगर (is_hest_type_generic_v2(ghes))
		unmap_gen_v2(ghes);
err_मुक्त:
	kमुक्त(ghes);
	वापस ERR_PTR(rc);
पूर्ण

अटल व्योम ghes_fini(काष्ठा ghes *ghes)
अणु
	kमुक्त(ghes->estatus);
	apei_unmap_generic_address(&ghes->generic->error_status_address);
	अगर (is_hest_type_generic_v2(ghes))
		unmap_gen_v2(ghes);
पूर्ण

अटल अंतरभूत पूर्णांक ghes_severity(पूर्णांक severity)
अणु
	चयन (severity) अणु
	हाल CPER_SEV_INFORMATIONAL:
		वापस GHES_SEV_NO;
	हाल CPER_SEV_CORRECTED:
		वापस GHES_SEV_CORRECTED;
	हाल CPER_SEV_RECOVERABLE:
		वापस GHES_SEV_RECOVERABLE;
	हाल CPER_SEV_FATAL:
		वापस GHES_SEV_PANIC;
	शेष:
		/* Unknown, go panic */
		वापस GHES_SEV_PANIC;
	पूर्ण
पूर्ण

अटल व्योम ghes_copy_tofrom_phys(व्योम *buffer, u64 paddr, u32 len,
				  पूर्णांक from_phys,
				  क्रमागत fixed_addresses fixmap_idx)
अणु
	व्योम __iomem *vaddr;
	u64 offset;
	u32 trunk;

	जबतक (len > 0) अणु
		offset = paddr - (paddr & PAGE_MASK);
		vaddr = ghes_map(PHYS_PFN(paddr), fixmap_idx);
		trunk = PAGE_SIZE - offset;
		trunk = min(trunk, len);
		अगर (from_phys)
			स_नकल_fromio(buffer, vaddr + offset, trunk);
		अन्यथा
			स_नकल_toio(vaddr + offset, buffer, trunk);
		len -= trunk;
		paddr += trunk;
		buffer += trunk;
		ghes_unmap(vaddr, fixmap_idx);
	पूर्ण
पूर्ण

/* Check the top-level record header has an appropriate size. */
अटल पूर्णांक __ghes_check_estatus(काष्ठा ghes *ghes,
				काष्ठा acpi_hest_generic_status *estatus)
अणु
	u32 len = cper_estatus_len(estatus);

	अगर (len < माप(*estatus)) अणु
		pr_warn_ratelimited(FW_WARN GHES_PFX "Truncated error status block!\n");
		वापस -EIO;
	पूर्ण

	अगर (len > ghes->generic->error_block_length) अणु
		pr_warn_ratelimited(FW_WARN GHES_PFX "Invalid error status block length!\n");
		वापस -EIO;
	पूर्ण

	अगर (cper_estatus_check_header(estatus)) अणु
		pr_warn_ratelimited(FW_WARN GHES_PFX "Invalid CPER header!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Read the CPER block, वापसing its address, and header in estatus. */
अटल पूर्णांक __ghes_peek_estatus(काष्ठा ghes *ghes,
			       काष्ठा acpi_hest_generic_status *estatus,
			       u64 *buf_paddr, क्रमागत fixed_addresses fixmap_idx)
अणु
	काष्ठा acpi_hest_generic *g = ghes->generic;
	पूर्णांक rc;

	rc = apei_पढ़ो(buf_paddr, &g->error_status_address);
	अगर (rc) अणु
		*buf_paddr = 0;
		pr_warn_ratelimited(FW_WARN GHES_PFX
"Failed to read error status block address for hardware error source: %d.\n",
				   g->header.source_id);
		वापस -EIO;
	पूर्ण
	अगर (!*buf_paddr)
		वापस -ENOENT;

	ghes_copy_tofrom_phys(estatus, *buf_paddr, माप(*estatus), 1,
			      fixmap_idx);
	अगर (!estatus->block_status) अणु
		*buf_paddr = 0;
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ghes_पढ़ो_estatus(काष्ठा acpi_hest_generic_status *estatus,
			       u64 buf_paddr, क्रमागत fixed_addresses fixmap_idx,
			       माप_प्रकार buf_len)
अणु
	ghes_copy_tofrom_phys(estatus, buf_paddr, buf_len, 1, fixmap_idx);
	अगर (cper_estatus_check(estatus)) अणु
		pr_warn_ratelimited(FW_WARN GHES_PFX
				    "Failed to read error status block!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ghes_पढ़ो_estatus(काष्ठा ghes *ghes,
			     काष्ठा acpi_hest_generic_status *estatus,
			     u64 *buf_paddr, क्रमागत fixed_addresses fixmap_idx)
अणु
	पूर्णांक rc;

	rc = __ghes_peek_estatus(ghes, estatus, buf_paddr, fixmap_idx);
	अगर (rc)
		वापस rc;

	rc = __ghes_check_estatus(ghes, estatus);
	अगर (rc)
		वापस rc;

	वापस __ghes_पढ़ो_estatus(estatus, *buf_paddr, fixmap_idx,
				   cper_estatus_len(estatus));
पूर्ण

अटल व्योम ghes_clear_estatus(काष्ठा ghes *ghes,
			       काष्ठा acpi_hest_generic_status *estatus,
			       u64 buf_paddr, क्रमागत fixed_addresses fixmap_idx)
अणु
	estatus->block_status = 0;

	अगर (!buf_paddr)
		वापस;

	ghes_copy_tofrom_phys(estatus, buf_paddr,
			      माप(estatus->block_status), 0,
			      fixmap_idx);

	/*
	 * GHESv2 type HEST entries पूर्णांकroduce support क्रम error acknowledgment,
	 * so only acknowledge the error अगर this support is present.
	 */
	अगर (is_hest_type_generic_v2(ghes))
		ghes_ack_error(ghes->generic_v2);
पूर्ण

/*
 * Called as task_work beक्रमe वापसing to user-space.
 * Ensure any queued work has been करोne beक्रमe we वापस to the context that
 * triggered the notअगरication.
 */
अटल व्योम ghes_kick_task_work(काष्ठा callback_head *head)
अणु
	काष्ठा acpi_hest_generic_status *estatus;
	काष्ठा ghes_estatus_node *estatus_node;
	u32 node_len;

	estatus_node = container_of(head, काष्ठा ghes_estatus_node, task_work);
	अगर (IS_ENABLED(CONFIG_ACPI_APEI_MEMORY_FAILURE))
		memory_failure_queue_kick(estatus_node->task_work_cpu);

	estatus = GHES_ESTATUS_FROM_NODE(estatus_node);
	node_len = GHES_ESTATUS_NODE_LEN(cper_estatus_len(estatus));
	gen_pool_मुक्त(ghes_estatus_pool, (अचिन्हित दीर्घ)estatus_node, node_len);
पूर्ण

अटल bool ghes_handle_memory_failure(काष्ठा acpi_hest_generic_data *gdata,
				       पूर्णांक sev)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक flags = -1;
	पूर्णांक sec_sev = ghes_severity(gdata->error_severity);
	काष्ठा cper_sec_mem_err *mem_err = acpi_hest_get_payload(gdata);

	अगर (!IS_ENABLED(CONFIG_ACPI_APEI_MEMORY_FAILURE))
		वापस false;

	अगर (!(mem_err->validation_bits & CPER_MEM_VALID_PA))
		वापस false;

	pfn = mem_err->physical_addr >> PAGE_SHIFT;
	अगर (!pfn_valid(pfn)) अणु
		pr_warn_ratelimited(FW_WARN GHES_PFX
		"Invalid address in generic error data: %#llx\n",
		mem_err->physical_addr);
		वापस false;
	पूर्ण

	/* अगरf following two events can be handled properly by now */
	अगर (sec_sev == GHES_SEV_CORRECTED &&
	    (gdata->flags & CPER_SEC_ERROR_THRESHOLD_EXCEEDED))
		flags = MF_SOFT_OFFLINE;
	अगर (sev == GHES_SEV_RECOVERABLE && sec_sev == GHES_SEV_RECOVERABLE)
		flags = 0;

	अगर (flags != -1) अणु
		memory_failure_queue(pfn, flags);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * PCIe AER errors need to be sent to the AER driver क्रम reporting and
 * recovery. The GHES severities map to the following AER severities and
 * require the following handling:
 *
 * GHES_SEV_CORRECTABLE -> AER_CORRECTABLE
 *     These need to be reported by the AER driver but no recovery is
 *     necessary.
 * GHES_SEV_RECOVERABLE -> AER_NONFATAL
 * GHES_SEV_RECOVERABLE && CPER_SEC_RESET -> AER_FATAL
 *     These both need to be reported and recovered from by the AER driver.
 * GHES_SEV_PANIC करोes not make it to this handling since the kernel must
 *     panic.
 */
अटल व्योम ghes_handle_aer(काष्ठा acpi_hest_generic_data *gdata)
अणु
#अगर_घोषित CONFIG_ACPI_APEI_PCIEAER
	काष्ठा cper_sec_pcie *pcie_err = acpi_hest_get_payload(gdata);

	अगर (pcie_err->validation_bits & CPER_PCIE_VALID_DEVICE_ID &&
	    pcie_err->validation_bits & CPER_PCIE_VALID_AER_INFO) अणु
		अचिन्हित पूर्णांक devfn;
		पूर्णांक aer_severity;

		devfn = PCI_DEVFN(pcie_err->device_id.device,
				  pcie_err->device_id.function);
		aer_severity = cper_severity_to_aer(gdata->error_severity);

		/*
		 * If firmware reset the component to contain
		 * the error, we must reinitialize it beक्रमe
		 * use, so treat it as a fatal AER error.
		 */
		अगर (gdata->flags & CPER_SEC_RESET)
			aer_severity = AER_FATAL;

		aer_recover_queue(pcie_err->device_id.segment,
				  pcie_err->device_id.bus,
				  devfn, aer_severity,
				  (काष्ठा aer_capability_regs *)
				  pcie_err->aer_info);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल BLOCKING_NOTIFIER_HEAD(venकरोr_record_notअगरy_list);

पूर्णांक ghes_रेजिस्टर_venकरोr_record_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&venकरोr_record_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(ghes_रेजिस्टर_venकरोr_record_notअगरier);

व्योम ghes_unरेजिस्टर_venकरोr_record_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&venकरोr_record_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(ghes_unरेजिस्टर_venकरोr_record_notअगरier);

अटल व्योम ghes_venकरोr_record_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ghes_venकरोr_record_entry *entry;
	काष्ठा acpi_hest_generic_data *gdata;
	u32 len;

	entry = container_of(work, काष्ठा ghes_venकरोr_record_entry, work);
	gdata = GHES_GDATA_FROM_VENDOR_ENTRY(entry);

	blocking_notअगरier_call_chain(&venकरोr_record_notअगरy_list,
				     entry->error_severity, gdata);

	len = GHES_VENDOR_ENTRY_LEN(acpi_hest_get_record_size(gdata));
	gen_pool_मुक्त(ghes_estatus_pool, (अचिन्हित दीर्घ)entry, len);
पूर्ण

अटल व्योम ghes_defer_non_standard_event(काष्ठा acpi_hest_generic_data *gdata,
					  पूर्णांक sev)
अणु
	काष्ठा acpi_hest_generic_data *copied_gdata;
	काष्ठा ghes_venकरोr_record_entry *entry;
	u32 len;

	len = GHES_VENDOR_ENTRY_LEN(acpi_hest_get_record_size(gdata));
	entry = (व्योम *)gen_pool_alloc(ghes_estatus_pool, len);
	अगर (!entry)
		वापस;

	copied_gdata = GHES_GDATA_FROM_VENDOR_ENTRY(entry);
	स_नकल(copied_gdata, gdata, acpi_hest_get_record_size(gdata));
	entry->error_severity = sev;

	INIT_WORK(&entry->work, ghes_venकरोr_record_work_func);
	schedule_work(&entry->work);
पूर्ण

अटल bool ghes_करो_proc(काष्ठा ghes *ghes,
			 स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	पूर्णांक sev, sec_sev;
	काष्ठा acpi_hest_generic_data *gdata;
	guid_t *sec_type;
	स्थिर guid_t *fru_id = &guid_null;
	अक्षर *fru_text = "";
	bool queued = false;

	sev = ghes_severity(estatus->error_severity);
	apei_estatus_क्रम_each_section(estatus, gdata) अणु
		sec_type = (guid_t *)gdata->section_type;
		sec_sev = ghes_severity(gdata->error_severity);
		अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_ID)
			fru_id = (guid_t *)gdata->fru_id;

		अगर (gdata->validation_bits & CPER_SEC_VALID_FRU_TEXT)
			fru_text = gdata->fru_text;

		अगर (guid_equal(sec_type, &CPER_SEC_PLATFORM_MEM)) अणु
			काष्ठा cper_sec_mem_err *mem_err = acpi_hest_get_payload(gdata);

			ghes_edac_report_mem_error(sev, mem_err);

			arch_apei_report_mem_error(sev, mem_err);
			queued = ghes_handle_memory_failure(gdata, sev);
		पूर्ण
		अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PCIE)) अणु
			ghes_handle_aer(gdata);
		पूर्ण
		अन्यथा अगर (guid_equal(sec_type, &CPER_SEC_PROC_ARM)) अणु
			काष्ठा cper_sec_proc_arm *err = acpi_hest_get_payload(gdata);

			log_arm_hw_error(err);
		पूर्ण अन्यथा अणु
			व्योम *err = acpi_hest_get_payload(gdata);

			ghes_defer_non_standard_event(gdata, sev);
			log_non_standard_event(sec_type, fru_id, fru_text,
					       sec_sev, err,
					       gdata->error_data_length);
		पूर्ण
	पूर्ण

	वापस queued;
पूर्ण

अटल व्योम __ghes_prपूर्णांक_estatus(स्थिर अक्षर *pfx,
				 स्थिर काष्ठा acpi_hest_generic *generic,
				 स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	अटल atomic_t seqno;
	अचिन्हित पूर्णांक curr_seqno;
	अक्षर pfx_seq[64];

	अगर (pfx == शून्य) अणु
		अगर (ghes_severity(estatus->error_severity) <=
		    GHES_SEV_CORRECTED)
			pfx = KERN_WARNING;
		अन्यथा
			pfx = KERN_ERR;
	पूर्ण
	curr_seqno = atomic_inc_वापस(&seqno);
	snम_लिखो(pfx_seq, माप(pfx_seq), "%s{%u}" HW_ERR, pfx, curr_seqno);
	prपूर्णांकk("%s""Hardware error from APEI Generic Hardware Error Source: %d\n",
	       pfx_seq, generic->header.source_id);
	cper_estatus_prपूर्णांक(pfx_seq, estatus);
पूर्ण

अटल पूर्णांक ghes_prपूर्णांक_estatus(स्थिर अक्षर *pfx,
			      स्थिर काष्ठा acpi_hest_generic *generic,
			      स्थिर काष्ठा acpi_hest_generic_status *estatus)
अणु
	/* Not more than 2 messages every 5 seconds */
	अटल DEFINE_RATELIMIT_STATE(ratelimit_corrected, 5*HZ, 2);
	अटल DEFINE_RATELIMIT_STATE(ratelimit_uncorrected, 5*HZ, 2);
	काष्ठा ratelimit_state *ratelimit;

	अगर (ghes_severity(estatus->error_severity) <= GHES_SEV_CORRECTED)
		ratelimit = &ratelimit_corrected;
	अन्यथा
		ratelimit = &ratelimit_uncorrected;
	अगर (__ratelimit(ratelimit)) अणु
		__ghes_prपूर्णांक_estatus(pfx, generic, estatus);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * GHES error status reporting throttle, to report more kinds of
 * errors, instead of just most frequently occurred errors.
 */
अटल पूर्णांक ghes_estatus_cached(काष्ठा acpi_hest_generic_status *estatus)
अणु
	u32 len;
	पूर्णांक i, cached = 0;
	अचिन्हित दीर्घ दीर्घ now;
	काष्ठा ghes_estatus_cache *cache;
	काष्ठा acpi_hest_generic_status *cache_estatus;

	len = cper_estatus_len(estatus);
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) अणु
		cache = rcu_dereference(ghes_estatus_caches[i]);
		अगर (cache == शून्य)
			जारी;
		अगर (len != cache->estatus_len)
			जारी;
		cache_estatus = GHES_ESTATUS_FROM_CACHE(cache);
		अगर (स_भेद(estatus, cache_estatus, len))
			जारी;
		atomic_inc(&cache->count);
		now = sched_घड़ी();
		अगर (now - cache->समय_in < GHES_ESTATUS_IN_CACHE_MAX_NSEC)
			cached = 1;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस cached;
पूर्ण

अटल काष्ठा ghes_estatus_cache *ghes_estatus_cache_alloc(
	काष्ठा acpi_hest_generic *generic,
	काष्ठा acpi_hest_generic_status *estatus)
अणु
	पूर्णांक alloced;
	u32 len, cache_len;
	काष्ठा ghes_estatus_cache *cache;
	काष्ठा acpi_hest_generic_status *cache_estatus;

	alloced = atomic_add_वापस(1, &ghes_estatus_cache_alloced);
	अगर (alloced > GHES_ESTATUS_CACHE_ALLOCED_MAX) अणु
		atomic_dec(&ghes_estatus_cache_alloced);
		वापस शून्य;
	पूर्ण
	len = cper_estatus_len(estatus);
	cache_len = GHES_ESTATUS_CACHE_LEN(len);
	cache = (व्योम *)gen_pool_alloc(ghes_estatus_pool, cache_len);
	अगर (!cache) अणु
		atomic_dec(&ghes_estatus_cache_alloced);
		वापस शून्य;
	पूर्ण
	cache_estatus = GHES_ESTATUS_FROM_CACHE(cache);
	स_नकल(cache_estatus, estatus, len);
	cache->estatus_len = len;
	atomic_set(&cache->count, 0);
	cache->generic = generic;
	cache->समय_in = sched_घड़ी();
	वापस cache;
पूर्ण

अटल व्योम ghes_estatus_cache_मुक्त(काष्ठा ghes_estatus_cache *cache)
अणु
	u32 len;

	len = cper_estatus_len(GHES_ESTATUS_FROM_CACHE(cache));
	len = GHES_ESTATUS_CACHE_LEN(len);
	gen_pool_मुक्त(ghes_estatus_pool, (अचिन्हित दीर्घ)cache, len);
	atomic_dec(&ghes_estatus_cache_alloced);
पूर्ण

अटल व्योम ghes_estatus_cache_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ghes_estatus_cache *cache;

	cache = container_of(head, काष्ठा ghes_estatus_cache, rcu);
	ghes_estatus_cache_मुक्त(cache);
पूर्ण

अटल व्योम ghes_estatus_cache_add(
	काष्ठा acpi_hest_generic *generic,
	काष्ठा acpi_hest_generic_status *estatus)
अणु
	पूर्णांक i, slot = -1, count;
	अचिन्हित दीर्घ दीर्घ now, duration, period, max_period = 0;
	काष्ठा ghes_estatus_cache *cache, *slot_cache = शून्य, *new_cache;

	new_cache = ghes_estatus_cache_alloc(generic, estatus);
	अगर (new_cache == शून्य)
		वापस;
	rcu_पढ़ो_lock();
	now = sched_घड़ी();
	क्रम (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) अणु
		cache = rcu_dereference(ghes_estatus_caches[i]);
		अगर (cache == शून्य) अणु
			slot = i;
			slot_cache = शून्य;
			अवरोध;
		पूर्ण
		duration = now - cache->समय_in;
		अगर (duration >= GHES_ESTATUS_IN_CACHE_MAX_NSEC) अणु
			slot = i;
			slot_cache = cache;
			अवरोध;
		पूर्ण
		count = atomic_पढ़ो(&cache->count);
		period = duration;
		करो_भाग(period, (count + 1));
		अगर (period > max_period) अणु
			max_period = period;
			slot = i;
			slot_cache = cache;
		पूर्ण
	पूर्ण
	/* new_cache must be put पूर्णांकo array after its contents are written */
	smp_wmb();
	अगर (slot != -1 && cmpxchg(ghes_estatus_caches + slot,
				  slot_cache, new_cache) == slot_cache) अणु
		अगर (slot_cache)
			call_rcu(&slot_cache->rcu, ghes_estatus_cache_rcu_मुक्त);
	पूर्ण अन्यथा
		ghes_estatus_cache_मुक्त(new_cache);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __ghes_panic(काष्ठा ghes *ghes,
			 काष्ठा acpi_hest_generic_status *estatus,
			 u64 buf_paddr, क्रमागत fixed_addresses fixmap_idx)
अणु
	__ghes_prपूर्णांक_estatus(KERN_EMERG, ghes->generic, estatus);

	ghes_clear_estatus(ghes, estatus, buf_paddr, fixmap_idx);

	/* reboot to log the error! */
	अगर (!panic_समयout)
		panic_समयout = ghes_panic_समयout;
	panic("Fatal hardware error!");
पूर्ण

अटल पूर्णांक ghes_proc(काष्ठा ghes *ghes)
अणु
	काष्ठा acpi_hest_generic_status *estatus = ghes->estatus;
	u64 buf_paddr;
	पूर्णांक rc;

	rc = ghes_पढ़ो_estatus(ghes, estatus, &buf_paddr, FIX_APEI_GHES_IRQ);
	अगर (rc)
		जाओ out;

	अगर (ghes_severity(estatus->error_severity) >= GHES_SEV_PANIC)
		__ghes_panic(ghes, estatus, buf_paddr, FIX_APEI_GHES_IRQ);

	अगर (!ghes_estatus_cached(estatus)) अणु
		अगर (ghes_prपूर्णांक_estatus(शून्य, ghes->generic, estatus))
			ghes_estatus_cache_add(ghes->generic, estatus);
	पूर्ण
	ghes_करो_proc(ghes, estatus);

out:
	ghes_clear_estatus(ghes, estatus, buf_paddr, FIX_APEI_GHES_IRQ);

	वापस rc;
पूर्ण

अटल व्योम ghes_add_समयr(काष्ठा ghes *ghes)
अणु
	काष्ठा acpi_hest_generic *g = ghes->generic;
	अचिन्हित दीर्घ expire;

	अगर (!g->notअगरy.poll_पूर्णांकerval) अणु
		pr_warn(FW_WARN GHES_PFX "Poll interval is 0 for generic hardware error source: %d, disabled.\n",
			g->header.source_id);
		वापस;
	पूर्ण
	expire = jअगरfies + msecs_to_jअगरfies(g->notअगरy.poll_पूर्णांकerval);
	ghes->समयr.expires = round_jअगरfies_relative(expire);
	add_समयr(&ghes->समयr);
पूर्ण

अटल व्योम ghes_poll_func(काष्ठा समयr_list *t)
अणु
	काष्ठा ghes *ghes = from_समयr(ghes, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ghes_notअगरy_lock_irq, flags);
	ghes_proc(ghes);
	spin_unlock_irqrestore(&ghes_notअगरy_lock_irq, flags);
	अगर (!(ghes->flags & GHES_EXITING))
		ghes_add_समयr(ghes);
पूर्ण

अटल irqवापस_t ghes_irq_func(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ghes *ghes = data;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&ghes_notअगरy_lock_irq, flags);
	rc = ghes_proc(ghes);
	spin_unlock_irqrestore(&ghes_notअगरy_lock_irq, flags);
	अगर (rc)
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ghes_notअगरy_hed(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *data)
अणु
	काष्ठा ghes *ghes;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = NOTIFY_DONE;

	spin_lock_irqsave(&ghes_notअगरy_lock_irq, flags);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ghes, &ghes_hed, list) अणु
		अगर (!ghes_proc(ghes))
			ret = NOTIFY_OK;
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock_irqrestore(&ghes_notअगरy_lock_irq, flags);

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block ghes_notअगरier_hed = अणु
	.notअगरier_call = ghes_notअगरy_hed,
पूर्ण;

/*
 * Handlers क्रम CPER records may not be NMI safe. For example,
 * memory_failure_queue() takes spinlocks and calls schedule_work_on().
 * In any NMI-like handler, memory from ghes_estatus_pool is used to save
 * estatus, and added to the ghes_estatus_llist. irq_work_queue() causes
 * ghes_proc_in_irq() to run in IRQ context where each estatus in
 * ghes_estatus_llist is processed.
 *
 * Memory from the ghes_estatus_pool is also used with the ghes_estatus_cache
 * to suppress frequent messages.
 */
अटल काष्ठा llist_head ghes_estatus_llist;
अटल काष्ठा irq_work ghes_proc_irq_work;

अटल व्योम ghes_proc_in_irq(काष्ठा irq_work *irq_work)
अणु
	काष्ठा llist_node *llnode, *next;
	काष्ठा ghes_estatus_node *estatus_node;
	काष्ठा acpi_hest_generic *generic;
	काष्ठा acpi_hest_generic_status *estatus;
	bool task_work_pending;
	u32 len, node_len;
	पूर्णांक ret;

	llnode = llist_del_all(&ghes_estatus_llist);
	/*
	 * Because the समय order of estatus in list is reversed,
	 * revert it back to proper order.
	 */
	llnode = llist_reverse_order(llnode);
	जबतक (llnode) अणु
		next = llnode->next;
		estatus_node = llist_entry(llnode, काष्ठा ghes_estatus_node,
					   llnode);
		estatus = GHES_ESTATUS_FROM_NODE(estatus_node);
		len = cper_estatus_len(estatus);
		node_len = GHES_ESTATUS_NODE_LEN(len);
		task_work_pending = ghes_करो_proc(estatus_node->ghes, estatus);
		अगर (!ghes_estatus_cached(estatus)) अणु
			generic = estatus_node->generic;
			अगर (ghes_prपूर्णांक_estatus(शून्य, generic, estatus))
				ghes_estatus_cache_add(generic, estatus);
		पूर्ण

		अगर (task_work_pending && current->mm != &init_mm) अणु
			estatus_node->task_work.func = ghes_kick_task_work;
			estatus_node->task_work_cpu = smp_processor_id();
			ret = task_work_add(current, &estatus_node->task_work,
					    TWA_RESUME);
			अगर (ret)
				estatus_node->task_work.func = शून्य;
		पूर्ण

		अगर (!estatus_node->task_work.func)
			gen_pool_मुक्त(ghes_estatus_pool,
				      (अचिन्हित दीर्घ)estatus_node, node_len);

		llnode = next;
	पूर्ण
पूर्ण

अटल व्योम ghes_prपूर्णांक_queued_estatus(व्योम)
अणु
	काष्ठा llist_node *llnode;
	काष्ठा ghes_estatus_node *estatus_node;
	काष्ठा acpi_hest_generic *generic;
	काष्ठा acpi_hest_generic_status *estatus;

	llnode = llist_del_all(&ghes_estatus_llist);
	/*
	 * Because the समय order of estatus in list is reversed,
	 * revert it back to proper order.
	 */
	llnode = llist_reverse_order(llnode);
	जबतक (llnode) अणु
		estatus_node = llist_entry(llnode, काष्ठा ghes_estatus_node,
					   llnode);
		estatus = GHES_ESTATUS_FROM_NODE(estatus_node);
		generic = estatus_node->generic;
		ghes_prपूर्णांक_estatus(शून्य, generic, estatus);
		llnode = llnode->next;
	पूर्ण
पूर्ण

अटल पूर्णांक ghes_in_nmi_queue_one_entry(काष्ठा ghes *ghes,
				       क्रमागत fixed_addresses fixmap_idx)
अणु
	काष्ठा acpi_hest_generic_status *estatus, पंचांगp_header;
	काष्ठा ghes_estatus_node *estatus_node;
	u32 len, node_len;
	u64 buf_paddr;
	पूर्णांक sev, rc;

	अगर (!IS_ENABLED(CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG))
		वापस -EOPNOTSUPP;

	rc = __ghes_peek_estatus(ghes, &पंचांगp_header, &buf_paddr, fixmap_idx);
	अगर (rc) अणु
		ghes_clear_estatus(ghes, &पंचांगp_header, buf_paddr, fixmap_idx);
		वापस rc;
	पूर्ण

	rc = __ghes_check_estatus(ghes, &पंचांगp_header);
	अगर (rc) अणु
		ghes_clear_estatus(ghes, &पंचांगp_header, buf_paddr, fixmap_idx);
		वापस rc;
	पूर्ण

	len = cper_estatus_len(&पंचांगp_header);
	node_len = GHES_ESTATUS_NODE_LEN(len);
	estatus_node = (व्योम *)gen_pool_alloc(ghes_estatus_pool, node_len);
	अगर (!estatus_node)
		वापस -ENOMEM;

	estatus_node->ghes = ghes;
	estatus_node->generic = ghes->generic;
	estatus_node->task_work.func = शून्य;
	estatus = GHES_ESTATUS_FROM_NODE(estatus_node);

	अगर (__ghes_पढ़ो_estatus(estatus, buf_paddr, fixmap_idx, len)) अणु
		ghes_clear_estatus(ghes, estatus, buf_paddr, fixmap_idx);
		rc = -ENOENT;
		जाओ no_work;
	पूर्ण

	sev = ghes_severity(estatus->error_severity);
	अगर (sev >= GHES_SEV_PANIC) अणु
		ghes_prपूर्णांक_queued_estatus();
		__ghes_panic(ghes, estatus, buf_paddr, fixmap_idx);
	पूर्ण

	ghes_clear_estatus(ghes, &पंचांगp_header, buf_paddr, fixmap_idx);

	/* This error has been reported beक्रमe, करोn't process it again. */
	अगर (ghes_estatus_cached(estatus))
		जाओ no_work;

	llist_add(&estatus_node->llnode, &ghes_estatus_llist);

	वापस rc;

no_work:
	gen_pool_मुक्त(ghes_estatus_pool, (अचिन्हित दीर्घ)estatus_node,
		      node_len);

	वापस rc;
पूर्ण

अटल पूर्णांक ghes_in_nmi_spool_from_list(काष्ठा list_head *rcu_list,
				       क्रमागत fixed_addresses fixmap_idx)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा ghes *ghes;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ghes, rcu_list, list) अणु
		अगर (!ghes_in_nmi_queue_one_entry(ghes, fixmap_idx))
			ret = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (IS_ENABLED(CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG) && !ret)
		irq_work_queue(&ghes_proc_irq_work);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI_APEI_SEA
अटल LIST_HEAD(ghes_sea);

/*
 * Return 0 only अगर one of the SEA error sources successfully reported an error
 * record sent from the firmware.
 */
पूर्णांक ghes_notअगरy_sea(व्योम)
अणु
	अटल DEFINE_RAW_SPINLOCK(ghes_notअगरy_lock_sea);
	पूर्णांक rv;

	raw_spin_lock(&ghes_notअगरy_lock_sea);
	rv = ghes_in_nmi_spool_from_list(&ghes_sea, FIX_APEI_GHES_SEA);
	raw_spin_unlock(&ghes_notअगरy_lock_sea);

	वापस rv;
पूर्ण

अटल व्योम ghes_sea_add(काष्ठा ghes *ghes)
अणु
	mutex_lock(&ghes_list_mutex);
	list_add_rcu(&ghes->list, &ghes_sea);
	mutex_unlock(&ghes_list_mutex);
पूर्ण

अटल व्योम ghes_sea_हटाओ(काष्ठा ghes *ghes)
अणु
	mutex_lock(&ghes_list_mutex);
	list_del_rcu(&ghes->list);
	mutex_unlock(&ghes_list_mutex);
	synchronize_rcu();
पूर्ण
#अन्यथा /* CONFIG_ACPI_APEI_SEA */
अटल अंतरभूत व्योम ghes_sea_add(काष्ठा ghes *ghes) अणु पूर्ण
अटल अंतरभूत व्योम ghes_sea_हटाओ(काष्ठा ghes *ghes) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_APEI_SEA */

#अगर_घोषित CONFIG_HAVE_ACPI_APEI_NMI
/*
 * NMI may be triggered on any CPU, so ghes_in_nmi is used क्रम
 * having only one concurrent पढ़ोer.
 */
अटल atomic_t ghes_in_nmi = ATOMIC_INIT(0);

अटल LIST_HEAD(ghes_nmi);

अटल पूर्णांक ghes_notअगरy_nmi(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	अटल DEFINE_RAW_SPINLOCK(ghes_notअगरy_lock_nmi);
	पूर्णांक ret = NMI_DONE;

	अगर (!atomic_add_unless(&ghes_in_nmi, 1, 1))
		वापस ret;

	raw_spin_lock(&ghes_notअगरy_lock_nmi);
	अगर (!ghes_in_nmi_spool_from_list(&ghes_nmi, FIX_APEI_GHES_NMI))
		ret = NMI_HANDLED;
	raw_spin_unlock(&ghes_notअगरy_lock_nmi);

	atomic_dec(&ghes_in_nmi);
	वापस ret;
पूर्ण

अटल व्योम ghes_nmi_add(काष्ठा ghes *ghes)
अणु
	mutex_lock(&ghes_list_mutex);
	अगर (list_empty(&ghes_nmi))
		रेजिस्टर_nmi_handler(NMI_LOCAL, ghes_notअगरy_nmi, 0, "ghes");
	list_add_rcu(&ghes->list, &ghes_nmi);
	mutex_unlock(&ghes_list_mutex);
पूर्ण

अटल व्योम ghes_nmi_हटाओ(काष्ठा ghes *ghes)
अणु
	mutex_lock(&ghes_list_mutex);
	list_del_rcu(&ghes->list);
	अगर (list_empty(&ghes_nmi))
		unरेजिस्टर_nmi_handler(NMI_LOCAL, "ghes");
	mutex_unlock(&ghes_list_mutex);
	/*
	 * To synchronize with NMI handler, ghes can only be
	 * मुक्तd after NMI handler finishes.
	 */
	synchronize_rcu();
पूर्ण
#अन्यथा /* CONFIG_HAVE_ACPI_APEI_NMI */
अटल अंतरभूत व्योम ghes_nmi_add(काष्ठा ghes *ghes) अणु पूर्ण
अटल अंतरभूत व्योम ghes_nmi_हटाओ(काष्ठा ghes *ghes) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ACPI_APEI_NMI */

अटल व्योम ghes_nmi_init_cxt(व्योम)
अणु
	init_irq_work(&ghes_proc_irq_work, ghes_proc_in_irq);
पूर्ण

अटल पूर्णांक __ghes_sdei_callback(काष्ठा ghes *ghes,
				क्रमागत fixed_addresses fixmap_idx)
अणु
	अगर (!ghes_in_nmi_queue_one_entry(ghes, fixmap_idx)) अणु
		irq_work_queue(&ghes_proc_irq_work);

		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ghes_sdei_normal_callback(u32 event_num, काष्ठा pt_regs *regs,
				      व्योम *arg)
अणु
	अटल DEFINE_RAW_SPINLOCK(ghes_notअगरy_lock_sdei_normal);
	काष्ठा ghes *ghes = arg;
	पूर्णांक err;

	raw_spin_lock(&ghes_notअगरy_lock_sdei_normal);
	err = __ghes_sdei_callback(ghes, FIX_APEI_GHES_SDEI_NORMAL);
	raw_spin_unlock(&ghes_notअगरy_lock_sdei_normal);

	वापस err;
पूर्ण

अटल पूर्णांक ghes_sdei_critical_callback(u32 event_num, काष्ठा pt_regs *regs,
				       व्योम *arg)
अणु
	अटल DEFINE_RAW_SPINLOCK(ghes_notअगरy_lock_sdei_critical);
	काष्ठा ghes *ghes = arg;
	पूर्णांक err;

	raw_spin_lock(&ghes_notअगरy_lock_sdei_critical);
	err = __ghes_sdei_callback(ghes, FIX_APEI_GHES_SDEI_CRITICAL);
	raw_spin_unlock(&ghes_notअगरy_lock_sdei_critical);

	वापस err;
पूर्ण

अटल पूर्णांक apei_sdei_रेजिस्टर_ghes(काष्ठा ghes *ghes)
अणु
	अगर (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE))
		वापस -EOPNOTSUPP;

	वापस sdei_रेजिस्टर_ghes(ghes, ghes_sdei_normal_callback,
				 ghes_sdei_critical_callback);
पूर्ण

अटल पूर्णांक apei_sdei_unरेजिस्टर_ghes(काष्ठा ghes *ghes)
अणु
	अगर (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE))
		वापस -EOPNOTSUPP;

	वापस sdei_unरेजिस्टर_ghes(ghes);
पूर्ण

अटल पूर्णांक ghes_probe(काष्ठा platक्रमm_device *ghes_dev)
अणु
	काष्ठा acpi_hest_generic *generic;
	काष्ठा ghes *ghes = शून्य;
	अचिन्हित दीर्घ flags;

	पूर्णांक rc = -EINVAL;

	generic = *(काष्ठा acpi_hest_generic **)ghes_dev->dev.platक्रमm_data;
	अगर (!generic->enabled)
		वापस -ENODEV;

	चयन (generic->notअगरy.type) अणु
	हाल ACPI_HEST_NOTIFY_POLLED:
	हाल ACPI_HEST_NOTIFY_EXTERNAL:
	हाल ACPI_HEST_NOTIFY_SCI:
	हाल ACPI_HEST_NOTIFY_GSIV:
	हाल ACPI_HEST_NOTIFY_GPIO:
		अवरोध;

	हाल ACPI_HEST_NOTIFY_SEA:
		अगर (!IS_ENABLED(CONFIG_ACPI_APEI_SEA)) अणु
			pr_warn(GHES_PFX "Generic hardware error source: %d notified via SEA is not supported\n",
				generic->header.source_id);
			rc = -ENOTSUPP;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल ACPI_HEST_NOTIFY_NMI:
		अगर (!IS_ENABLED(CONFIG_HAVE_ACPI_APEI_NMI)) अणु
			pr_warn(GHES_PFX "Generic hardware error source: %d notified via NMI interrupt is not supported!\n",
				generic->header.source_id);
			जाओ err;
		पूर्ण
		अवरोध;
	हाल ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED:
		अगर (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE)) अणु
			pr_warn(GHES_PFX "Generic hardware error source: %d notified via SDE Interface is not supported!\n",
				generic->header.source_id);
			जाओ err;
		पूर्ण
		अवरोध;
	हाल ACPI_HEST_NOTIFY_LOCAL:
		pr_warn(GHES_PFX "Generic hardware error source: %d notified via local interrupt is not supported!\n",
			generic->header.source_id);
		जाओ err;
	शेष:
		pr_warn(FW_WARN GHES_PFX "Unknown notification type: %u for generic hardware error source: %d\n",
			generic->notअगरy.type, generic->header.source_id);
		जाओ err;
	पूर्ण

	rc = -EIO;
	अगर (generic->error_block_length <
	    माप(काष्ठा acpi_hest_generic_status)) अणु
		pr_warn(FW_BUG GHES_PFX "Invalid error block length: %u for generic hardware error source: %d\n",
			generic->error_block_length, generic->header.source_id);
		जाओ err;
	पूर्ण
	ghes = ghes_new(generic);
	अगर (IS_ERR(ghes)) अणु
		rc = PTR_ERR(ghes);
		ghes = शून्य;
		जाओ err;
	पूर्ण

	चयन (generic->notअगरy.type) अणु
	हाल ACPI_HEST_NOTIFY_POLLED:
		समयr_setup(&ghes->समयr, ghes_poll_func, 0);
		ghes_add_समयr(ghes);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_EXTERNAL:
		/* External पूर्णांकerrupt vector is GSI */
		rc = acpi_gsi_to_irq(generic->notअगरy.vector, &ghes->irq);
		अगर (rc) अणु
			pr_err(GHES_PFX "Failed to map GSI to IRQ for generic hardware error source: %d\n",
			       generic->header.source_id);
			जाओ err;
		पूर्ण
		rc = request_irq(ghes->irq, ghes_irq_func, IRQF_SHARED,
				 "GHES IRQ", ghes);
		अगर (rc) अणु
			pr_err(GHES_PFX "Failed to register IRQ for generic hardware error source: %d\n",
			       generic->header.source_id);
			जाओ err;
		पूर्ण
		अवरोध;

	हाल ACPI_HEST_NOTIFY_SCI:
	हाल ACPI_HEST_NOTIFY_GSIV:
	हाल ACPI_HEST_NOTIFY_GPIO:
		mutex_lock(&ghes_list_mutex);
		अगर (list_empty(&ghes_hed))
			रेजिस्टर_acpi_hed_notअगरier(&ghes_notअगरier_hed);
		list_add_rcu(&ghes->list, &ghes_hed);
		mutex_unlock(&ghes_list_mutex);
		अवरोध;

	हाल ACPI_HEST_NOTIFY_SEA:
		ghes_sea_add(ghes);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_NMI:
		ghes_nmi_add(ghes);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED:
		rc = apei_sdei_रेजिस्टर_ghes(ghes);
		अगर (rc)
			जाओ err;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	platक्रमm_set_drvdata(ghes_dev, ghes);

	ghes_edac_रेजिस्टर(ghes, &ghes_dev->dev);

	/* Handle any pending errors right away */
	spin_lock_irqsave(&ghes_notअगरy_lock_irq, flags);
	ghes_proc(ghes);
	spin_unlock_irqrestore(&ghes_notअगरy_lock_irq, flags);

	वापस 0;

err:
	अगर (ghes) अणु
		ghes_fini(ghes);
		kमुक्त(ghes);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक ghes_हटाओ(काष्ठा platक्रमm_device *ghes_dev)
अणु
	पूर्णांक rc;
	काष्ठा ghes *ghes;
	काष्ठा acpi_hest_generic *generic;

	ghes = platक्रमm_get_drvdata(ghes_dev);
	generic = ghes->generic;

	ghes->flags |= GHES_EXITING;
	चयन (generic->notअगरy.type) अणु
	हाल ACPI_HEST_NOTIFY_POLLED:
		del_समयr_sync(&ghes->समयr);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_EXTERNAL:
		मुक्त_irq(ghes->irq, ghes);
		अवरोध;

	हाल ACPI_HEST_NOTIFY_SCI:
	हाल ACPI_HEST_NOTIFY_GSIV:
	हाल ACPI_HEST_NOTIFY_GPIO:
		mutex_lock(&ghes_list_mutex);
		list_del_rcu(&ghes->list);
		अगर (list_empty(&ghes_hed))
			unरेजिस्टर_acpi_hed_notअगरier(&ghes_notअगरier_hed);
		mutex_unlock(&ghes_list_mutex);
		synchronize_rcu();
		अवरोध;

	हाल ACPI_HEST_NOTIFY_SEA:
		ghes_sea_हटाओ(ghes);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_NMI:
		ghes_nmi_हटाओ(ghes);
		अवरोध;
	हाल ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED:
		rc = apei_sdei_unरेजिस्टर_ghes(ghes);
		अगर (rc)
			वापस rc;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	ghes_fini(ghes);

	ghes_edac_unरेजिस्टर(ghes);

	kमुक्त(ghes);

	platक्रमm_set_drvdata(ghes_dev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ghes_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "GHES",
	पूर्ण,
	.probe		= ghes_probe,
	.हटाओ		= ghes_हटाओ,
पूर्ण;

अटल पूर्णांक __init ghes_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (acpi_disabled)
		वापस -ENODEV;

	चयन (hest_disable) अणु
	हाल HEST_NOT_FOUND:
		वापस -ENODEV;
	हाल HEST_DISABLED:
		pr_info(GHES_PFX "HEST is not enabled!\n");
		वापस -EINVAL;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ghes_disable) अणु
		pr_info(GHES_PFX "GHES is not enabled!\n");
		वापस -EINVAL;
	पूर्ण

	ghes_nmi_init_cxt();

	rc = platक्रमm_driver_रेजिस्टर(&ghes_platक्रमm_driver);
	अगर (rc)
		जाओ err;

	rc = apei_osc_setup();
	अगर (rc == 0 && osc_sb_apei_support_acked)
		pr_info(GHES_PFX "APEI firmware first mode is enabled by APEI bit and WHEA _OSC.\n");
	अन्यथा अगर (rc == 0 && !osc_sb_apei_support_acked)
		pr_info(GHES_PFX "APEI firmware first mode is enabled by WHEA _OSC.\n");
	अन्यथा अगर (rc && osc_sb_apei_support_acked)
		pr_info(GHES_PFX "APEI firmware first mode is enabled by APEI bit.\n");
	अन्यथा
		pr_info(GHES_PFX "Failed to enable APEI firmware first mode.\n");

	वापस 0;
err:
	वापस rc;
पूर्ण
device_initcall(ghes_init);
