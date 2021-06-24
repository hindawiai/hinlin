<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_osl.c - OS-dependent functions ($Revision: 83 $)
 *
 *  Copyright (C) 2000       Andrew Henroid
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (c) 2008 Intel Corporation
 *   Author: Matthew Wilcox <willy@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: OSL: " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/lockdep.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kmod.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/nmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/security.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "acpica/accommon.h"
#समावेश "acpica/acnamesp.h"
#समावेश "internal.h"

/* Definitions क्रम ACPI_DEBUG_PRINT() */
#घोषणा _COMPONENT		ACPI_OS_SERVICES
ACPI_MODULE_NAME("osl");

काष्ठा acpi_os_dpc अणु
	acpi_osd_exec_callback function;
	व्योम *context;
	काष्ठा work_काष्ठा work;
पूर्ण;

#अगर_घोषित ENABLE_DEBUGGER
#समावेश <linux/kdb.h>

/* stuff क्रम debugger support */
पूर्णांक acpi_in_debugger;
EXPORT_SYMBOL(acpi_in_debugger);
#पूर्ण_अगर				/*ENABLE_DEBUGGER */

अटल पूर्णांक (*__acpi_os_prepare_sleep)(u8 sleep_state, u32 pm1a_ctrl,
				      u32 pm1b_ctrl);
अटल पूर्णांक (*__acpi_os_prepare_extended_sleep)(u8 sleep_state, u32 val_a,
				      u32 val_b);

अटल acpi_osd_handler acpi_irq_handler;
अटल व्योम *acpi_irq_context;
अटल काष्ठा workqueue_काष्ठा *kacpid_wq;
अटल काष्ठा workqueue_काष्ठा *kacpi_notअगरy_wq;
अटल काष्ठा workqueue_काष्ठा *kacpi_hotplug_wq;
अटल bool acpi_os_initialized;
अचिन्हित पूर्णांक acpi_sci_irq = INVALID_ACPI_IRQ;
bool acpi_permanent_mmap = false;

/*
 * This list of permanent mappings is क्रम memory that may be accessed from
 * पूर्णांकerrupt context, where we can't करो the ioremap().
 */
काष्ठा acpi_ioremap अणु
	काष्ठा list_head list;
	व्योम __iomem *virt;
	acpi_physical_address phys;
	acpi_size size;
	जोड़ अणु
		अचिन्हित दीर्घ refcount;
		काष्ठा rcu_work rwork;
	पूर्ण track;
पूर्ण;

अटल LIST_HEAD(acpi_ioremaps);
अटल DEFINE_MUTEX(acpi_ioremap_lock);
#घोषणा acpi_ioremap_lock_held() lock_is_held(&acpi_ioremap_lock.dep_map)

अटल व्योम __init acpi_request_region (काष्ठा acpi_generic_address *gas,
	अचिन्हित पूर्णांक length, अक्षर *desc)
अणु
	u64 addr;

	/* Handle possible alignment issues */
	स_नकल(&addr, &gas->address, माप(addr));
	अगर (!addr || !length)
		वापस;

	/* Resources are never मुक्तd */
	अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_IO)
		request_region(addr, length, desc);
	अन्यथा अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY)
		request_mem_region(addr, length, desc);
पूर्ण

अटल पूर्णांक __init acpi_reserve_resources(व्योम)
अणु
	acpi_request_region(&acpi_gbl_FADT.xpm1a_event_block, acpi_gbl_FADT.pm1_event_length,
		"ACPI PM1a_EVT_BLK");

	acpi_request_region(&acpi_gbl_FADT.xpm1b_event_block, acpi_gbl_FADT.pm1_event_length,
		"ACPI PM1b_EVT_BLK");

	acpi_request_region(&acpi_gbl_FADT.xpm1a_control_block, acpi_gbl_FADT.pm1_control_length,
		"ACPI PM1a_CNT_BLK");

	acpi_request_region(&acpi_gbl_FADT.xpm1b_control_block, acpi_gbl_FADT.pm1_control_length,
		"ACPI PM1b_CNT_BLK");

	अगर (acpi_gbl_FADT.pm_समयr_length == 4)
		acpi_request_region(&acpi_gbl_FADT.xpm_समयr_block, 4, "ACPI PM_TMR");

	acpi_request_region(&acpi_gbl_FADT.xpm2_control_block, acpi_gbl_FADT.pm2_control_length,
		"ACPI PM2_CNT_BLK");

	/* Length of GPE blocks must be a non-negative multiple of 2 */

	अगर (!(acpi_gbl_FADT.gpe0_block_length & 0x1))
		acpi_request_region(&acpi_gbl_FADT.xgpe0_block,
			       acpi_gbl_FADT.gpe0_block_length, "ACPI GPE0_BLK");

	अगर (!(acpi_gbl_FADT.gpe1_block_length & 0x1))
		acpi_request_region(&acpi_gbl_FADT.xgpe1_block,
			       acpi_gbl_FADT.gpe1_block_length, "ACPI GPE1_BLK");

	वापस 0;
पूर्ण
fs_initcall_sync(acpi_reserve_resources);

व्योम acpi_os_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	बहु_शुरू(args, fmt);
	acpi_os_भ_लिखो(fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(acpi_os_म_लिखो);

व्योम acpi_os_भ_लिखो(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	अटल अक्षर buffer[512];

	भम_लिखो(buffer, fmt, args);

#अगर_घोषित ENABLE_DEBUGGER
	अगर (acpi_in_debugger) अणु
		kdb_म_लिखो("%s", buffer);
	पूर्ण अन्यथा अणु
		अगर (prपूर्णांकk_get_level(buffer))
			prपूर्णांकk("%s", buffer);
		अन्यथा
			prपूर्णांकk(KERN_CONT "%s", buffer);
	पूर्ण
#अन्यथा
	अगर (acpi_debugger_ग_लिखो_log(buffer) < 0) अणु
		अगर (prपूर्णांकk_get_level(buffer))
			prपूर्णांकk("%s", buffer);
		अन्यथा
			prपूर्णांकk(KERN_CONT "%s", buffer);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_KEXEC
अटल अचिन्हित दीर्घ acpi_rsdp;
अटल पूर्णांक __init setup_acpi_rsdp(अक्षर *arg)
अणु
	वापस kम_से_अदीर्घ(arg, 16, &acpi_rsdp);
पूर्ण
early_param("acpi_rsdp", setup_acpi_rsdp);
#पूर्ण_अगर

acpi_physical_address __init acpi_os_get_root_poपूर्णांकer(व्योम)
अणु
	acpi_physical_address pa;

#अगर_घोषित CONFIG_KEXEC
	/*
	 * We may have been provided with an RSDP on the command line,
	 * but अगर a malicious user has करोne so they may be poपूर्णांकing us
	 * at modअगरied ACPI tables that could alter kernel behaviour -
	 * so, we check the lockकरोwn status beक्रमe making use of
	 * it. If we trust it then also stash it in an architecture
	 * specअगरic location (अगर appropriate) so it can be carried
	 * over further kexec()s.
	 */
	अगर (acpi_rsdp && !security_locked_करोwn(LOCKDOWN_ACPI_TABLES)) अणु
		acpi_arch_set_root_poपूर्णांकer(acpi_rsdp);
		वापस acpi_rsdp;
	पूर्ण
#पूर्ण_अगर
	pa = acpi_arch_get_root_poपूर्णांकer();
	अगर (pa)
		वापस pa;

	अगर (efi_enabled(EFI_CONFIG_TABLES)) अणु
		अगर (efi.acpi20 != EFI_INVALID_TABLE_ADDR)
			वापस efi.acpi20;
		अगर (efi.acpi != EFI_INVALID_TABLE_ADDR)
			वापस efi.acpi;
		pr_err(PREFIX "System description tables not found\n");
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_ACPI_LEGACY_TABLES_LOOKUP)) अणु
		acpi_find_root_poपूर्णांकer(&pa);
	पूर्ण

	वापस pa;
पूर्ण

/* Must be called with 'acpi_ioremap_lock' or RCU पढ़ो lock held. */
अटल काष्ठा acpi_ioremap *
acpi_map_lookup(acpi_physical_address phys, acpi_size size)
अणु
	काष्ठा acpi_ioremap *map;

	list_क्रम_each_entry_rcu(map, &acpi_ioremaps, list, acpi_ioremap_lock_held())
		अगर (map->phys <= phys &&
		    phys + size <= map->phys + map->size)
			वापस map;

	वापस शून्य;
पूर्ण

/* Must be called with 'acpi_ioremap_lock' or RCU पढ़ो lock held. */
अटल व्योम __iomem *
acpi_map_vaddr_lookup(acpi_physical_address phys, अचिन्हित पूर्णांक size)
अणु
	काष्ठा acpi_ioremap *map;

	map = acpi_map_lookup(phys, size);
	अगर (map)
		वापस map->virt + (phys - map->phys);

	वापस शून्य;
पूर्ण

व्योम __iomem *acpi_os_get_iomem(acpi_physical_address phys, अचिन्हित पूर्णांक size)
अणु
	काष्ठा acpi_ioremap *map;
	व्योम __iomem *virt = शून्य;

	mutex_lock(&acpi_ioremap_lock);
	map = acpi_map_lookup(phys, size);
	अगर (map) अणु
		virt = map->virt + (phys - map->phys);
		map->track.refcount++;
	पूर्ण
	mutex_unlock(&acpi_ioremap_lock);
	वापस virt;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_os_get_iomem);

/* Must be called with 'acpi_ioremap_lock' or RCU पढ़ो lock held. */
अटल काष्ठा acpi_ioremap *
acpi_map_lookup_virt(व्योम __iomem *virt, acpi_size size)
अणु
	काष्ठा acpi_ioremap *map;

	list_क्रम_each_entry_rcu(map, &acpi_ioremaps, list, acpi_ioremap_lock_held())
		अगर (map->virt <= virt &&
		    virt + size <= map->virt + map->size)
			वापस map;

	वापस शून्य;
पूर्ण

#अगर defined(CONFIG_IA64) || defined(CONFIG_ARM64)
/* ioremap will take care of cache attributes */
#घोषणा should_use_kmap(pfn)   0
#अन्यथा
#घोषणा should_use_kmap(pfn)   page_is_ram(pfn)
#पूर्ण_अगर

अटल व्योम __iomem *acpi_map(acpi_physical_address pg_off, अचिन्हित दीर्घ pg_sz)
अणु
	अचिन्हित दीर्घ pfn;

	pfn = pg_off >> PAGE_SHIFT;
	अगर (should_use_kmap(pfn)) अणु
		अगर (pg_sz > PAGE_SIZE)
			वापस शून्य;
		वापस (व्योम __iomem __क्रमce *)kmap(pfn_to_page(pfn));
	पूर्ण अन्यथा
		वापस acpi_os_ioremap(pg_off, pg_sz);
पूर्ण

अटल व्योम acpi_unmap(acpi_physical_address pg_off, व्योम __iomem *vaddr)
अणु
	अचिन्हित दीर्घ pfn;

	pfn = pg_off >> PAGE_SHIFT;
	अगर (should_use_kmap(pfn))
		kunmap(pfn_to_page(pfn));
	अन्यथा
		iounmap(vaddr);
पूर्ण

/**
 * acpi_os_map_iomem - Get a भव address क्रम a given physical address range.
 * @phys: Start of the physical address range to map.
 * @size: Size of the physical address range to map.
 *
 * Look up the given physical address range in the list of existing ACPI memory
 * mappings.  If found, get a reference to it and वापस a poपूर्णांकer to it (its
 * भव address).  If not found, map it, add it to that list and वापस a
 * poपूर्णांकer to it.
 *
 * During early init (when acpi_permanent_mmap has not been set yet) this
 * routine simply calls __acpi_map_table() to get the job करोne.
 */
व्योम __iomem __ref
*acpi_os_map_iomem(acpi_physical_address phys, acpi_size size)
अणु
	काष्ठा acpi_ioremap *map;
	व्योम __iomem *virt;
	acpi_physical_address pg_off;
	acpi_size pg_sz;

	अगर (phys > अच_दीर्घ_उच्च) अणु
		pr_err("Cannot map memory that high: 0x%llx\n", phys);
		वापस शून्य;
	पूर्ण

	अगर (!acpi_permanent_mmap)
		वापस __acpi_map_table((अचिन्हित दीर्घ)phys, size);

	mutex_lock(&acpi_ioremap_lock);
	/* Check अगर there's a suitable mapping alपढ़ोy. */
	map = acpi_map_lookup(phys, size);
	अगर (map) अणु
		map->track.refcount++;
		जाओ out;
	पूर्ण

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map) अणु
		mutex_unlock(&acpi_ioremap_lock);
		वापस शून्य;
	पूर्ण

	pg_off = round_करोwn(phys, PAGE_SIZE);
	pg_sz = round_up(phys + size, PAGE_SIZE) - pg_off;
	virt = acpi_map(phys, size);
	अगर (!virt) अणु
		mutex_unlock(&acpi_ioremap_lock);
		kमुक्त(map);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&map->list);
	map->virt = (व्योम __iomem __क्रमce *)((अचिन्हित दीर्घ)virt & PAGE_MASK);
	map->phys = pg_off;
	map->size = pg_sz;
	map->track.refcount = 1;

	list_add_tail_rcu(&map->list, &acpi_ioremaps);

out:
	mutex_unlock(&acpi_ioremap_lock);
	वापस map->virt + (phys - map->phys);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_os_map_iomem);

व्योम *__ref acpi_os_map_memory(acpi_physical_address phys, acpi_size size)
अणु
	वापस (व्योम *)acpi_os_map_iomem(phys, size);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_os_map_memory);

अटल व्योम acpi_os_map_हटाओ(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_ioremap *map = container_of(to_rcu_work(work),
						काष्ठा acpi_ioremap,
						track.rwork);

	acpi_unmap(map->phys, map->virt);
	kमुक्त(map);
पूर्ण

/* Must be called with mutex_lock(&acpi_ioremap_lock) */
अटल व्योम acpi_os_drop_map_ref(काष्ठा acpi_ioremap *map)
अणु
	अगर (--map->track.refcount)
		वापस;

	list_del_rcu(&map->list);

	INIT_RCU_WORK(&map->track.rwork, acpi_os_map_हटाओ);
	queue_rcu_work(प्रणाली_wq, &map->track.rwork);
पूर्ण

/**
 * acpi_os_unmap_iomem - Drop a memory mapping reference.
 * @virt: Start of the address range to drop a reference to.
 * @size: Size of the address range to drop a reference to.
 *
 * Look up the given भव address range in the list of existing ACPI memory
 * mappings, drop a reference to it and अगर there are no more active references
 * to it, queue it up क्रम later removal.
 *
 * During early init (when acpi_permanent_mmap has not been set yet) this
 * routine simply calls __acpi_unmap_table() to get the job करोne.  Since
 * __acpi_unmap_table() is an __init function, the __ref annotation is needed
 * here.
 */
व्योम __ref acpi_os_unmap_iomem(व्योम __iomem *virt, acpi_size size)
अणु
	काष्ठा acpi_ioremap *map;

	अगर (!acpi_permanent_mmap) अणु
		__acpi_unmap_table(virt, size);
		वापस;
	पूर्ण

	mutex_lock(&acpi_ioremap_lock);

	map = acpi_map_lookup_virt(virt, size);
	अगर (!map) अणु
		mutex_unlock(&acpi_ioremap_lock);
		WARN(true, PREFIX "%s: bad address %p\n", __func__, virt);
		वापस;
	पूर्ण
	acpi_os_drop_map_ref(map);

	mutex_unlock(&acpi_ioremap_lock);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_os_unmap_iomem);

/**
 * acpi_os_unmap_memory - Drop a memory mapping reference.
 * @virt: Start of the address range to drop a reference to.
 * @size: Size of the address range to drop a reference to.
 */
व्योम __ref acpi_os_unmap_memory(व्योम *virt, acpi_size size)
अणु
	acpi_os_unmap_iomem((व्योम __iomem *)virt, size);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_os_unmap_memory);

व्योम __iomem *acpi_os_map_generic_address(काष्ठा acpi_generic_address *gas)
अणु
	u64 addr;

	अगर (gas->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY)
		वापस शून्य;

	/* Handle possible alignment issues */
	स_नकल(&addr, &gas->address, माप(addr));
	अगर (!addr || !gas->bit_width)
		वापस शून्य;

	वापस acpi_os_map_iomem(addr, gas->bit_width / 8);
पूर्ण
EXPORT_SYMBOL(acpi_os_map_generic_address);

व्योम acpi_os_unmap_generic_address(काष्ठा acpi_generic_address *gas)
अणु
	u64 addr;
	काष्ठा acpi_ioremap *map;

	अगर (gas->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY)
		वापस;

	/* Handle possible alignment issues */
	स_नकल(&addr, &gas->address, माप(addr));
	अगर (!addr || !gas->bit_width)
		वापस;

	mutex_lock(&acpi_ioremap_lock);

	map = acpi_map_lookup(addr, gas->bit_width / 8);
	अगर (!map) अणु
		mutex_unlock(&acpi_ioremap_lock);
		वापस;
	पूर्ण
	acpi_os_drop_map_ref(map);

	mutex_unlock(&acpi_ioremap_lock);
पूर्ण
EXPORT_SYMBOL(acpi_os_unmap_generic_address);

#अगर_घोषित ACPI_FUTURE_USAGE
acpi_status
acpi_os_get_physical_address(व्योम *virt, acpi_physical_address * phys)
अणु
	अगर (!phys || !virt)
		वापस AE_BAD_PARAMETER;

	*phys = virt_to_phys(virt);

	वापस AE_OK;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_REV_OVERRIDE_POSSIBLE
अटल bool acpi_rev_override;

पूर्णांक __init acpi_rev_override_setup(अक्षर *str)
अणु
	acpi_rev_override = true;
	वापस 1;
पूर्ण
__setup("acpi_rev_override", acpi_rev_override_setup);
#अन्यथा
#घोषणा acpi_rev_override	false
#पूर्ण_अगर

#घोषणा ACPI_MAX_OVERRIDE_LEN 100

अटल अक्षर acpi_os_name[ACPI_MAX_OVERRIDE_LEN];

acpi_status
acpi_os_predefined_override(स्थिर काष्ठा acpi_predefined_names *init_val,
			    acpi_string *new_val)
अणु
	अगर (!init_val || !new_val)
		वापस AE_BAD_PARAMETER;

	*new_val = शून्य;
	अगर (!स_भेद(init_val->name, "_OS_", 4) && म_माप(acpi_os_name)) अणु
		pr_info("Overriding _OS definition to '%s'\n", acpi_os_name);
		*new_val = acpi_os_name;
	पूर्ण

	अगर (!स_भेद(init_val->name, "_REV", 4) && acpi_rev_override) अणु
		pr_info("Overriding _REV return value to 5\n");
		*new_val = (अक्षर *)5;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल irqवापस_t acpi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 handled;

	handled = (*acpi_irq_handler) (acpi_irq_context);

	अगर (handled) अणु
		acpi_irq_handled++;
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		acpi_irq_not_handled++;
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

acpi_status
acpi_os_install_पूर्णांकerrupt_handler(u32 gsi, acpi_osd_handler handler,
				  व्योम *context)
अणु
	अचिन्हित पूर्णांक irq;

	acpi_irq_stats_init();

	/*
	 * ACPI पूर्णांकerrupts dअगरferent from the SCI in our copy of the FADT are
	 * not supported.
	 */
	अगर (gsi != acpi_gbl_FADT.sci_पूर्णांकerrupt)
		वापस AE_BAD_PARAMETER;

	अगर (acpi_irq_handler)
		वापस AE_ALREADY_ACQUIRED;

	अगर (acpi_gsi_to_irq(gsi, &irq) < 0) अणु
		pr_err("SCI (ACPI GSI %d) not registered\n", gsi);
		वापस AE_OK;
	पूर्ण

	acpi_irq_handler = handler;
	acpi_irq_context = context;
	अगर (request_irq(irq, acpi_irq, IRQF_SHARED, "acpi", acpi_irq)) अणु
		pr_err("SCI (IRQ%d) allocation failed\n", irq);
		acpi_irq_handler = शून्य;
		वापस AE_NOT_ACQUIRED;
	पूर्ण
	acpi_sci_irq = irq;

	वापस AE_OK;
पूर्ण

acpi_status acpi_os_हटाओ_पूर्णांकerrupt_handler(u32 gsi, acpi_osd_handler handler)
अणु
	अगर (gsi != acpi_gbl_FADT.sci_पूर्णांकerrupt || !acpi_sci_irq_valid())
		वापस AE_BAD_PARAMETER;

	मुक्त_irq(acpi_sci_irq, acpi_irq);
	acpi_irq_handler = शून्य;
	acpi_sci_irq = INVALID_ACPI_IRQ;

	वापस AE_OK;
पूर्ण

/*
 * Running in पूर्णांकerpreter thपढ़ो context, safe to sleep
 */

व्योम acpi_os_sleep(u64 ms)
अणु
	msleep(ms);
पूर्ण

व्योम acpi_os_stall(u32 us)
अणु
	जबतक (us) अणु
		u32 delay = 1000;

		अगर (delay > us)
			delay = us;
		udelay(delay);
		touch_nmi_watchकरोg();
		us -= delay;
	पूर्ण
पूर्ण

/*
 * Support ACPI 3.0 AML Timer opeअक्रम. Returns a 64-bit मुक्त-running,
 * monotonically increasing समयr with 100ns granularity. Do not use
 * kसमय_get() to implement this function because this function may get
 * called after समयkeeping has been suspended. Note: calling this function
 * after समयkeeping has been suspended may lead to unexpected results
 * because when समयkeeping is suspended the jअगरfies counter is not
 * incremented. See also समयkeeping_suspend().
 */
u64 acpi_os_get_समयr(व्योम)
अणु
	वापस (get_jअगरfies_64() - INITIAL_JIFFIES) *
		(ACPI_100NSEC_PER_SEC / HZ);
पूर्ण

acpi_status acpi_os_पढ़ो_port(acpi_io_address port, u32 * value, u32 width)
अणु
	u32 dummy;

	अगर (!value)
		value = &dummy;

	*value = 0;
	अगर (width <= 8) अणु
		*(u8 *) value = inb(port);
	पूर्ण अन्यथा अगर (width <= 16) अणु
		*(u16 *) value = inw(port);
	पूर्ण अन्यथा अगर (width <= 32) अणु
		*(u32 *) value = inl(port);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	वापस AE_OK;
पूर्ण

EXPORT_SYMBOL(acpi_os_पढ़ो_port);

acpi_status acpi_os_ग_लिखो_port(acpi_io_address port, u32 value, u32 width)
अणु
	अगर (width <= 8) अणु
		outb(value, port);
	पूर्ण अन्यथा अगर (width <= 16) अणु
		outw(value, port);
	पूर्ण अन्यथा अगर (width <= 32) अणु
		outl(value, port);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	वापस AE_OK;
पूर्ण

EXPORT_SYMBOL(acpi_os_ग_लिखो_port);

पूर्णांक acpi_os_पढ़ो_iomem(व्योम __iomem *virt_addr, u64 *value, u32 width)
अणु

	चयन (width) अणु
	हाल 8:
		*(u8 *) value = पढ़ोb(virt_addr);
		अवरोध;
	हाल 16:
		*(u16 *) value = पढ़ोw(virt_addr);
		अवरोध;
	हाल 32:
		*(u32 *) value = पढ़ोl(virt_addr);
		अवरोध;
	हाल 64:
		*(u64 *) value = पढ़ोq(virt_addr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

acpi_status
acpi_os_पढ़ो_memory(acpi_physical_address phys_addr, u64 *value, u32 width)
अणु
	व्योम __iomem *virt_addr;
	अचिन्हित पूर्णांक size = width / 8;
	bool unmap = false;
	u64 dummy;
	पूर्णांक error;

	rcu_पढ़ो_lock();
	virt_addr = acpi_map_vaddr_lookup(phys_addr, size);
	अगर (!virt_addr) अणु
		rcu_पढ़ो_unlock();
		virt_addr = acpi_os_ioremap(phys_addr, size);
		अगर (!virt_addr)
			वापस AE_BAD_ADDRESS;
		unmap = true;
	पूर्ण

	अगर (!value)
		value = &dummy;

	error = acpi_os_पढ़ो_iomem(virt_addr, value, width);
	BUG_ON(error);

	अगर (unmap)
		iounmap(virt_addr);
	अन्यथा
		rcu_पढ़ो_unlock();

	वापस AE_OK;
पूर्ण

acpi_status
acpi_os_ग_लिखो_memory(acpi_physical_address phys_addr, u64 value, u32 width)
अणु
	व्योम __iomem *virt_addr;
	अचिन्हित पूर्णांक size = width / 8;
	bool unmap = false;

	rcu_पढ़ो_lock();
	virt_addr = acpi_map_vaddr_lookup(phys_addr, size);
	अगर (!virt_addr) अणु
		rcu_पढ़ो_unlock();
		virt_addr = acpi_os_ioremap(phys_addr, size);
		अगर (!virt_addr)
			वापस AE_BAD_ADDRESS;
		unmap = true;
	पूर्ण

	चयन (width) अणु
	हाल 8:
		ग_लिखोb(value, virt_addr);
		अवरोध;
	हाल 16:
		ग_लिखोw(value, virt_addr);
		अवरोध;
	हाल 32:
		ग_लिखोl(value, virt_addr);
		अवरोध;
	हाल 64:
		ग_लिखोq(value, virt_addr);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (unmap)
		iounmap(virt_addr);
	अन्यथा
		rcu_पढ़ो_unlock();

	वापस AE_OK;
पूर्ण

#अगर_घोषित CONFIG_PCI
acpi_status
acpi_os_पढ़ो_pci_configuration(काष्ठा acpi_pci_id * pci_id, u32 reg,
			       u64 *value, u32 width)
अणु
	पूर्णांक result, size;
	u32 value32;

	अगर (!value)
		वापस AE_BAD_PARAMETER;

	चयन (width) अणु
	हाल 8:
		size = 1;
		अवरोध;
	हाल 16:
		size = 2;
		अवरोध;
	हाल 32:
		size = 4;
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण

	result = raw_pci_पढ़ो(pci_id->segment, pci_id->bus,
				PCI_DEVFN(pci_id->device, pci_id->function),
				reg, size, &value32);
	*value = value32;

	वापस (result ? AE_ERROR : AE_OK);
पूर्ण

acpi_status
acpi_os_ग_लिखो_pci_configuration(काष्ठा acpi_pci_id * pci_id, u32 reg,
				u64 value, u32 width)
अणु
	पूर्णांक result, size;

	चयन (width) अणु
	हाल 8:
		size = 1;
		अवरोध;
	हाल 16:
		size = 2;
		अवरोध;
	हाल 32:
		size = 4;
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण

	result = raw_pci_ग_लिखो(pci_id->segment, pci_id->bus,
				PCI_DEVFN(pci_id->device, pci_id->function),
				reg, size, value);

	वापस (result ? AE_ERROR : AE_OK);
पूर्ण
#पूर्ण_अगर

अटल व्योम acpi_os_execute_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_os_dpc *dpc = container_of(work, काष्ठा acpi_os_dpc, work);

	dpc->function(dpc->context);
	kमुक्त(dpc);
पूर्ण

#अगर_घोषित CONFIG_ACPI_DEBUGGER
अटल काष्ठा acpi_debugger acpi_debugger;
अटल bool acpi_debugger_initialized;

पूर्णांक acpi_रेजिस्टर_debugger(काष्ठा module *owner,
			   स्थिर काष्ठा acpi_debugger_ops *ops)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&acpi_debugger.lock);
	अगर (acpi_debugger.ops) अणु
		ret = -EBUSY;
		जाओ err_lock;
	पूर्ण

	acpi_debugger.owner = owner;
	acpi_debugger.ops = ops;

err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(acpi_रेजिस्टर_debugger);

व्योम acpi_unरेजिस्टर_debugger(स्थिर काष्ठा acpi_debugger_ops *ops)
अणु
	mutex_lock(&acpi_debugger.lock);
	अगर (ops == acpi_debugger.ops) अणु
		acpi_debugger.ops = शून्य;
		acpi_debugger.owner = शून्य;
	पूर्ण
	mutex_unlock(&acpi_debugger.lock);
पूर्ण
EXPORT_SYMBOL(acpi_unरेजिस्टर_debugger);

पूर्णांक acpi_debugger_create_thपढ़ो(acpi_osd_exec_callback function, व्योम *context)
अणु
	पूर्णांक ret;
	पूर्णांक (*func)(acpi_osd_exec_callback, व्योम *);
	काष्ठा module *owner;

	अगर (!acpi_debugger_initialized)
		वापस -ENODEV;
	mutex_lock(&acpi_debugger.lock);
	अगर (!acpi_debugger.ops) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	अगर (!try_module_get(acpi_debugger.owner)) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	func = acpi_debugger.ops->create_thपढ़ो;
	owner = acpi_debugger.owner;
	mutex_unlock(&acpi_debugger.lock);

	ret = func(function, context);

	mutex_lock(&acpi_debugger.lock);
	module_put(owner);
err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण

sमाप_प्रकार acpi_debugger_ग_लिखो_log(स्थिर अक्षर *msg)
अणु
	sमाप_प्रकार ret;
	sमाप_प्रकार (*func)(स्थिर अक्षर *);
	काष्ठा module *owner;

	अगर (!acpi_debugger_initialized)
		वापस -ENODEV;
	mutex_lock(&acpi_debugger.lock);
	अगर (!acpi_debugger.ops) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	अगर (!try_module_get(acpi_debugger.owner)) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	func = acpi_debugger.ops->ग_लिखो_log;
	owner = acpi_debugger.owner;
	mutex_unlock(&acpi_debugger.lock);

	ret = func(msg);

	mutex_lock(&acpi_debugger.lock);
	module_put(owner);
err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण

sमाप_प्रकार acpi_debugger_पढ़ो_cmd(अक्षर *buffer, माप_प्रकार buffer_length)
अणु
	sमाप_प्रकार ret;
	sमाप_प्रकार (*func)(अक्षर *, माप_प्रकार);
	काष्ठा module *owner;

	अगर (!acpi_debugger_initialized)
		वापस -ENODEV;
	mutex_lock(&acpi_debugger.lock);
	अगर (!acpi_debugger.ops) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	अगर (!try_module_get(acpi_debugger.owner)) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	func = acpi_debugger.ops->पढ़ो_cmd;
	owner = acpi_debugger.owner;
	mutex_unlock(&acpi_debugger.lock);

	ret = func(buffer, buffer_length);

	mutex_lock(&acpi_debugger.lock);
	module_put(owner);
err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण

पूर्णांक acpi_debugger_रुको_command_पढ़ोy(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक (*func)(bool, अक्षर *, माप_प्रकार);
	काष्ठा module *owner;

	अगर (!acpi_debugger_initialized)
		वापस -ENODEV;
	mutex_lock(&acpi_debugger.lock);
	अगर (!acpi_debugger.ops) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	अगर (!try_module_get(acpi_debugger.owner)) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	func = acpi_debugger.ops->रुको_command_पढ़ोy;
	owner = acpi_debugger.owner;
	mutex_unlock(&acpi_debugger.lock);

	ret = func(acpi_gbl_method_executing,
		   acpi_gbl_db_line_buf, ACPI_DB_LINE_BUFFER_SIZE);

	mutex_lock(&acpi_debugger.lock);
	module_put(owner);
err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण

पूर्णांक acpi_debugger_notअगरy_command_complete(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक (*func)(व्योम);
	काष्ठा module *owner;

	अगर (!acpi_debugger_initialized)
		वापस -ENODEV;
	mutex_lock(&acpi_debugger.lock);
	अगर (!acpi_debugger.ops) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	अगर (!try_module_get(acpi_debugger.owner)) अणु
		ret = -ENODEV;
		जाओ err_lock;
	पूर्ण
	func = acpi_debugger.ops->notअगरy_command_complete;
	owner = acpi_debugger.owner;
	mutex_unlock(&acpi_debugger.lock);

	ret = func();

	mutex_lock(&acpi_debugger.lock);
	module_put(owner);
err_lock:
	mutex_unlock(&acpi_debugger.lock);
	वापस ret;
पूर्ण

पूर्णांक __init acpi_debugger_init(व्योम)
अणु
	mutex_init(&acpi_debugger.lock);
	acpi_debugger_initialized = true;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_execute
 *
 * PARAMETERS:  Type               - Type of the callback
 *              Function           - Function to be executed
 *              Context            - Function parameters
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Depending on type, either queues function क्रम deferred execution or
 *              immediately executes function on a separate thपढ़ो.
 *
 ******************************************************************************/

acpi_status acpi_os_execute(acpi_execute_type type,
			    acpi_osd_exec_callback function, व्योम *context)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_os_dpc *dpc;
	काष्ठा workqueue_काष्ठा *queue;
	पूर्णांक ret;
	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Scheduling function [%p(%p)] for deferred execution.\n",
			  function, context));

	अगर (type == OSL_DEBUGGER_MAIN_THREAD) अणु
		ret = acpi_debugger_create_thपढ़ो(function, context);
		अगर (ret) अणु
			pr_err("Kernel thread creation failed\n");
			status = AE_ERROR;
		पूर्ण
		जाओ out_thपढ़ो;
	पूर्ण

	/*
	 * Allocate/initialize DPC काष्ठाure.  Note that this memory will be
	 * मुक्तd by the callee.  The kernel handles the work_काष्ठा list  in a
	 * way that allows us to also मुक्त its memory inside the callee.
	 * Because we may want to schedule several tasks with dअगरferent
	 * parameters we can't use the approach some kernel code uses of
	 * having a अटल work_काष्ठा.
	 */

	dpc = kzalloc(माप(काष्ठा acpi_os_dpc), GFP_ATOMIC);
	अगर (!dpc)
		वापस AE_NO_MEMORY;

	dpc->function = function;
	dpc->context = context;

	/*
	 * To prevent lockdep from complaining unnecessarily, make sure that
	 * there is a dअगरferent अटल lockdep key क्रम each workqueue by using
	 * INIT_WORK() क्रम each of them separately.
	 */
	अगर (type == OSL_NOTIFY_HANDLER) अणु
		queue = kacpi_notअगरy_wq;
		INIT_WORK(&dpc->work, acpi_os_execute_deferred);
	पूर्ण अन्यथा अगर (type == OSL_GPE_HANDLER) अणु
		queue = kacpid_wq;
		INIT_WORK(&dpc->work, acpi_os_execute_deferred);
	पूर्ण अन्यथा अणु
		pr_err("Unsupported os_execute type %d.\n", type);
		status = AE_ERROR;
	पूर्ण

	अगर (ACPI_FAILURE(status))
		जाओ err_workqueue;

	/*
	 * On some machines, a software-initiated SMI causes corruption unless
	 * the SMI runs on CPU 0.  An SMI can be initiated by any AML, but
	 * typically it's करोne in GPE-related methods that are run via
	 * workqueues, so we can aव्योम the known corruption हालs by always
	 * queueing on CPU 0.
	 */
	ret = queue_work_on(0, queue, &dpc->work);
	अगर (!ret) अणु
		pr_err("Unable to queue work\n");
		status = AE_ERROR;
	पूर्ण
err_workqueue:
	अगर (ACPI_FAILURE(status))
		kमुक्त(dpc);
out_thपढ़ो:
	वापस status;
पूर्ण
EXPORT_SYMBOL(acpi_os_execute);

व्योम acpi_os_रुको_events_complete(व्योम)
अणु
	/*
	 * Make sure the GPE handler or the fixed event handler is not used
	 * on another CPU after removal.
	 */
	अगर (acpi_sci_irq_valid())
		synchronize_hardirq(acpi_sci_irq);
	flush_workqueue(kacpid_wq);
	flush_workqueue(kacpi_notअगरy_wq);
पूर्ण
EXPORT_SYMBOL(acpi_os_रुको_events_complete);

काष्ठा acpi_hp_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा acpi_device *adev;
	u32 src;
पूर्ण;

अटल व्योम acpi_hotplug_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_hp_work *hpw = container_of(work, काष्ठा acpi_hp_work, work);

	acpi_os_रुको_events_complete();
	acpi_device_hotplug(hpw->adev, hpw->src);
	kमुक्त(hpw);
पूर्ण

acpi_status acpi_hotplug_schedule(काष्ठा acpi_device *adev, u32 src)
अणु
	काष्ठा acpi_hp_work *hpw;

	acpi_handle_debug(adev->handle,
			  "Scheduling hotplug event %u for deferred handling\n",
			   src);

	hpw = kदो_स्मृति(माप(*hpw), GFP_KERNEL);
	अगर (!hpw)
		वापस AE_NO_MEMORY;

	INIT_WORK(&hpw->work, acpi_hotplug_work_fn);
	hpw->adev = adev;
	hpw->src = src;
	/*
	 * We can't run hotplug code in kacpid_wq/kacpid_notअगरy_wq etc., because
	 * the hotplug code may call driver .हटाओ() functions, which may
	 * invoke flush_scheduled_work()/acpi_os_रुको_events_complete() to flush
	 * these workqueues.
	 */
	अगर (!queue_work(kacpi_hotplug_wq, &hpw->work)) अणु
		kमुक्त(hpw);
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

bool acpi_queue_hotplug_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(kacpi_hotplug_wq, work);
पूर्ण

acpi_status
acpi_os_create_semaphore(u32 max_units, u32 initial_units, acpi_handle * handle)
अणु
	काष्ठा semaphore *sem = शून्य;

	sem = acpi_os_allocate_zeroed(माप(काष्ठा semaphore));
	अगर (!sem)
		वापस AE_NO_MEMORY;

	sema_init(sem, initial_units);

	*handle = (acpi_handle *) sem;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Creating semaphore[%p|%d].\n",
			  *handle, initial_units));

	वापस AE_OK;
पूर्ण

/*
 * TODO: A better way to delete semaphores?  Linux करोesn't have a
 * 'delete_semaphore()' function -- may result in an invalid
 * poपूर्णांकer dereference क्रम non-synchronized consumers.	Should
 * we at least check क्रम blocked thपढ़ोs and संकेत/cancel them?
 */

acpi_status acpi_os_delete_semaphore(acpi_handle handle)
अणु
	काष्ठा semaphore *sem = (काष्ठा semaphore *)handle;

	अगर (!sem)
		वापस AE_BAD_PARAMETER;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Deleting semaphore[%p].\n", handle));

	BUG_ON(!list_empty(&sem->रुको_list));
	kमुक्त(sem);
	sem = शून्य;

	वापस AE_OK;
पूर्ण

/*
 * TODO: Support क्रम units > 1?
 */
acpi_status acpi_os_रुको_semaphore(acpi_handle handle, u32 units, u16 समयout)
अणु
	acpi_status status = AE_OK;
	काष्ठा semaphore *sem = (काष्ठा semaphore *)handle;
	दीर्घ jअगरfies;
	पूर्णांक ret = 0;

	अगर (!acpi_os_initialized)
		वापस AE_OK;

	अगर (!sem || (units < 1))
		वापस AE_BAD_PARAMETER;

	अगर (units > 1)
		वापस AE_SUPPORT;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Waiting for semaphore[%p|%d|%d]\n",
			  handle, units, समयout));

	अगर (समयout == ACPI_WAIT_FOREVER)
		jअगरfies = MAX_SCHEDULE_TIMEOUT;
	अन्यथा
		jअगरfies = msecs_to_jअगरfies(समयout);

	ret = करोwn_समयout(sem, jअगरfies);
	अगर (ret)
		status = AE_TIME;

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_MUTEX,
				  "Failed to acquire semaphore[%p|%d|%d], %s",
				  handle, units, समयout,
				  acpi_क्रमmat_exception(status)));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_MUTEX,
				  "Acquired semaphore[%p|%d|%d]", handle,
				  units, समयout));
	पूर्ण

	वापस status;
पूर्ण

/*
 * TODO: Support क्रम units > 1?
 */
acpi_status acpi_os_संकेत_semaphore(acpi_handle handle, u32 units)
अणु
	काष्ठा semaphore *sem = (काष्ठा semaphore *)handle;

	अगर (!acpi_os_initialized)
		वापस AE_OK;

	अगर (!sem || (units < 1))
		वापस AE_BAD_PARAMETER;

	अगर (units > 1)
		वापस AE_SUPPORT;

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Signaling semaphore[%p|%d]\n", handle,
			  units));

	up(sem);

	वापस AE_OK;
पूर्ण

acpi_status acpi_os_get_line(अक्षर *buffer, u32 buffer_length, u32 *bytes_पढ़ो)
अणु
#अगर_घोषित ENABLE_DEBUGGER
	अगर (acpi_in_debugger) अणु
		u32 अक्षरs;

		kdb_पढ़ो(buffer, buffer_length);

		/* हटाओ the CR kdb includes */
		अक्षरs = म_माप(buffer) - 1;
		buffer[अक्षरs] = '\0';
	पूर्ण
#अन्यथा
	पूर्णांक ret;

	ret = acpi_debugger_पढ़ो_cmd(buffer, buffer_length);
	अगर (ret < 0)
		वापस AE_ERROR;
	अगर (bytes_पढ़ो)
		*bytes_पढ़ो = ret;
#पूर्ण_अगर

	वापस AE_OK;
पूर्ण
EXPORT_SYMBOL(acpi_os_get_line);

acpi_status acpi_os_रुको_command_पढ़ोy(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_debugger_रुको_command_पढ़ोy();
	अगर (ret < 0)
		वापस AE_ERROR;
	वापस AE_OK;
पूर्ण

acpi_status acpi_os_notअगरy_command_complete(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_debugger_notअगरy_command_complete();
	अगर (ret < 0)
		वापस AE_ERROR;
	वापस AE_OK;
पूर्ण

acpi_status acpi_os_संकेत(u32 function, व्योम *info)
अणु
	चयन (function) अणु
	हाल ACPI_SIGNAL_FATAL:
		pr_err("Fatal opcode executed\n");
		अवरोध;
	हाल ACPI_SIGNAL_BREAKPOINT:
		/*
		 * AML Breakpoपूर्णांक
		 * ACPI spec. says to treat it as a NOP unless
		 * you are debugging.  So अगर/when we पूर्णांकegrate
		 * AML debugger पूर्णांकo the kernel debugger its
		 * hook will go here.  But until then it is
		 * not useful to prपूर्णांक anything on अवरोधpoपूर्णांकs.
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक __init acpi_os_name_setup(अक्षर *str)
अणु
	अक्षर *p = acpi_os_name;
	पूर्णांक count = ACPI_MAX_OVERRIDE_LEN - 1;

	अगर (!str || !*str)
		वापस 0;

	क्रम (; count-- && *str; str++) अणु
		अगर (है_अक्षर_अंक(*str) || *str == ' ' || *str == ':')
			*p++ = *str;
		अन्यथा अगर (*str == '\'' || *str == '"')
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण
	*p = 0;

	वापस 1;

पूर्ण

__setup("acpi_os_name=", acpi_os_name_setup);

/*
 * Disable the स्वतः-serialization of named objects creation methods.
 *
 * This feature is enabled by शेष.  It marks the AML control methods
 * that contain the opcodes to create named objects as "Serialized".
 */
अटल पूर्णांक __init acpi_no_स्वतः_serialize_setup(अक्षर *str)
अणु
	acpi_gbl_स्वतः_serialize_methods = FALSE;
	pr_info("Auto-serialization disabled\n");

	वापस 1;
पूर्ण

__setup("acpi_no_auto_serialize", acpi_no_स्वतः_serialize_setup);

/* Check of resource पूर्णांकerference between native drivers and ACPI
 * OperationRegions (SystemIO and System Memory only).
 * IO ports and memory declared in ACPI might be used by the ACPI subप्रणाली
 * in arbitrary AML code and can पूर्णांकerfere with legacy drivers.
 * acpi_enक्रमce_resources= can be set to:
 *
 *   - strict (शेष) (2)
 *     -> further driver trying to access the resources will not load
 *   - lax              (1)
 *     -> further driver trying to access the resources will load, but you
 *     get a प्रणाली message that something might go wrong...
 *
 *   - no               (0)
 *     -> ACPI Operation Region resources will not be रेजिस्टरed
 *
 */
#घोषणा ENFORCE_RESOURCES_STRICT 2
#घोषणा ENFORCE_RESOURCES_LAX    1
#घोषणा ENFORCE_RESOURCES_NO     0

अटल अचिन्हित पूर्णांक acpi_enक्रमce_resources = ENFORCE_RESOURCES_STRICT;

अटल पूर्णांक __init acpi_enक्रमce_resources_setup(अक्षर *str)
अणु
	अगर (str == शून्य || *str == '\0')
		वापस 0;

	अगर (!म_भेद("strict", str))
		acpi_enक्रमce_resources = ENFORCE_RESOURCES_STRICT;
	अन्यथा अगर (!म_भेद("lax", str))
		acpi_enक्रमce_resources = ENFORCE_RESOURCES_LAX;
	अन्यथा अगर (!म_भेद("no", str))
		acpi_enक्रमce_resources = ENFORCE_RESOURCES_NO;

	वापस 1;
पूर्ण

__setup("acpi_enforce_resources=", acpi_enक्रमce_resources_setup);

/* Check क्रम resource conflicts between ACPI OperationRegions and native
 * drivers */
पूर्णांक acpi_check_resource_conflict(स्थिर काष्ठा resource *res)
अणु
	acpi_adr_space_type space_id;

	अगर (acpi_enक्रमce_resources == ENFORCE_RESOURCES_NO)
		वापस 0;

	अगर (res->flags & IORESOURCE_IO)
		space_id = ACPI_ADR_SPACE_SYSTEM_IO;
	अन्यथा अगर (res->flags & IORESOURCE_MEM)
		space_id = ACPI_ADR_SPACE_SYSTEM_MEMORY;
	अन्यथा
		वापस 0;

	अगर (!acpi_check_address_range(space_id, res->start, resource_size(res), 1))
		वापस 0;

	pr_info("Resource conflict; ACPI support missing from driver?\n");

	अगर (acpi_enक्रमce_resources == ENFORCE_RESOURCES_STRICT)
		वापस -EBUSY;

	अगर (acpi_enक्रमce_resources == ENFORCE_RESOURCES_LAX)
		pr_notice("Resource conflict: System may be unstable or behave erratically\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_check_resource_conflict);

पूर्णांक acpi_check_region(resource_माप_प्रकार start, resource_माप_प्रकार n,
		      स्थिर अक्षर *name)
अणु
	काष्ठा resource res = अणु
		.start = start,
		.end   = start + n - 1,
		.name  = name,
		.flags = IORESOURCE_IO,
	पूर्ण;

	वापस acpi_check_resource_conflict(&res);
पूर्ण
EXPORT_SYMBOL(acpi_check_region);

अटल acpi_status acpi_deactivate_mem_region(acpi_handle handle, u32 level,
					      व्योम *_res, व्योम **वापस_value)
अणु
	काष्ठा acpi_mem_space_context **mem_ctx;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *region_obj2;
	जोड़ acpi_opeअक्रम_object *region_obj;
	काष्ठा resource *res = _res;
	acpi_status status;

	region_obj = acpi_ns_get_attached_object(handle);
	अगर (!region_obj)
		वापस AE_OK;

	handler_obj = region_obj->region.handler;
	अगर (!handler_obj)
		वापस AE_OK;

	अगर (region_obj->region.space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY)
		वापस AE_OK;

	अगर (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE))
		वापस AE_OK;

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	अगर (!region_obj2)
		वापस AE_OK;

	mem_ctx = (व्योम *)&region_obj2->extra.region_context;

	अगर (!(mem_ctx[0]->address >= res->start &&
	      mem_ctx[0]->address < res->end))
		वापस AE_OK;

	status = handler_obj->address_space.setup(region_obj,
						  ACPI_REGION_DEACTIVATE,
						  शून्य, (व्योम **)mem_ctx);
	अगर (ACPI_SUCCESS(status))
		region_obj->region.flags &= ~(AOPOBJ_SETUP_COMPLETE);

	वापस status;
पूर्ण

/**
 * acpi_release_memory - Release any mappings करोne to a memory region
 * @handle: Handle to namespace node
 * @res: Memory resource
 * @level: A level that terminates the search
 *
 * Walks through @handle and unmaps all SystemMemory Operation Regions that
 * overlap with @res and that have alपढ़ोy been activated (mapped).
 *
 * This is a helper that allows drivers to place special requirements on memory
 * region that may overlap with operation regions, primarily allowing them to
 * safely map the region as non-cached memory.
 *
 * The unmapped Operation Regions will be स्वतःmatically remapped next समय they
 * are called, so the drivers करो not need to करो anything अन्यथा.
 */
acpi_status acpi_release_memory(acpi_handle handle, काष्ठा resource *res,
				u32 level)
अणु
	acpi_status status;

	अगर (!(res->flags & IORESOURCE_MEM))
		वापस AE_TYPE;

	status = acpi_walk_namespace(ACPI_TYPE_REGION, handle, level,
				     acpi_deactivate_mem_region, शून्य,
				     res, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस status;

	/*
	 * Wait क्रम all of the mappings queued up क्रम removal by
	 * acpi_deactivate_mem_region() to actually go away.
	 */
	synchronize_rcu();
	rcu_barrier();
	flush_scheduled_work();

	वापस AE_OK;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_release_memory);

/*
 * Let drivers know whether the resource checks are effective
 */
पूर्णांक acpi_resources_are_enक्रमced(व्योम)
अणु
	वापस acpi_enक्रमce_resources == ENFORCE_RESOURCES_STRICT;
पूर्ण
EXPORT_SYMBOL(acpi_resources_are_enक्रमced);

/*
 * Deallocate the memory क्रम a spinlock.
 */
व्योम acpi_os_delete_lock(acpi_spinlock handle)
अणु
	ACPI_FREE(handle);
पूर्ण

/*
 * Acquire a spinlock.
 *
 * handle is a poपूर्णांकer to the spinlock_t.
 */

acpi_cpu_flags acpi_os_acquire_lock(acpi_spinlock lockp)
	__acquires(lockp)
अणु
	acpi_cpu_flags flags;
	spin_lock_irqsave(lockp, flags);
	वापस flags;
पूर्ण

/*
 * Release a spinlock. See above.
 */

व्योम acpi_os_release_lock(acpi_spinlock lockp, acpi_cpu_flags flags)
	__releases(lockp)
अणु
	spin_unlock_irqrestore(lockp, flags);
पूर्ण

#अगर_अघोषित ACPI_USE_LOCAL_CACHE

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_create_cache
 *
 * PARAMETERS:  name      - Ascii name क्रम the cache
 *              size      - Size of each cached object
 *              depth     - Maximum depth of the cache (in objects) <ignored>
 *              cache     - Where the new cache object is वापसed
 *
 * RETURN:      status
 *
 * DESCRIPTION: Create a cache object
 *
 ******************************************************************************/

acpi_status
acpi_os_create_cache(अक्षर *name, u16 size, u16 depth, acpi_cache_t ** cache)
अणु
	*cache = kmem_cache_create(name, size, 0, 0, शून्य);
	अगर (*cache == शून्य)
		वापस AE_ERROR;
	अन्यथा
		वापस AE_OK;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_purge_cache
 *
 * PARAMETERS:  Cache           - Handle to cache object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Free all objects within the requested cache.
 *
 ******************************************************************************/

acpi_status acpi_os_purge_cache(acpi_cache_t * cache)
अणु
	kmem_cache_shrink(cache);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_delete_cache
 *
 * PARAMETERS:  Cache           - Handle to cache object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Free all objects within the requested cache and delete the
 *              cache object.
 *
 ******************************************************************************/

acpi_status acpi_os_delete_cache(acpi_cache_t * cache)
अणु
	kmem_cache_destroy(cache);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_release_object
 *
 * PARAMETERS:  Cache       - Handle to cache object
 *              Object      - The object to be released
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release an object to the specअगरied cache.  If cache is full,
 *              the object is deleted.
 *
 ******************************************************************************/

acpi_status acpi_os_release_object(acpi_cache_t * cache, व्योम *object)
अणु
	kmem_cache_मुक्त(cache, object);
	वापस (AE_OK);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init acpi_no_अटल_ssdt_setup(अक्षर *s)
अणु
	acpi_gbl_disable_ssdt_table_install = TRUE;
	pr_info("Static SSDT installation disabled\n");

	वापस 0;
पूर्ण

early_param("acpi_no_static_ssdt", acpi_no_अटल_ssdt_setup);

अटल पूर्णांक __init acpi_disable_वापस_repair(अक्षर *s)
अणु
	pr_notice("Predefined validation mechanism disabled\n");
	acpi_gbl_disable_स्वतः_repair = TRUE;

	वापस 1;
पूर्ण

__setup("acpica_no_return_repair", acpi_disable_वापस_repair);

acpi_status __init acpi_os_initialize(व्योम)
अणु
	acpi_os_map_generic_address(&acpi_gbl_FADT.xpm1a_event_block);
	acpi_os_map_generic_address(&acpi_gbl_FADT.xpm1b_event_block);

	acpi_gbl_xgpe0_block_logical_address =
		(अचिन्हित दीर्घ)acpi_os_map_generic_address(&acpi_gbl_FADT.xgpe0_block);
	acpi_gbl_xgpe1_block_logical_address =
		(अचिन्हित दीर्घ)acpi_os_map_generic_address(&acpi_gbl_FADT.xgpe1_block);

	अगर (acpi_gbl_FADT.flags & ACPI_FADT_RESET_REGISTER) अणु
		/*
		 * Use acpi_os_map_generic_address to pre-map the reset
		 * रेजिस्टर अगर it's in प्रणाली memory.
		 */
		व्योम *rv;

		rv = acpi_os_map_generic_address(&acpi_gbl_FADT.reset_रेजिस्टर);
		pr_debug("%s: Reset register mapping %s\n", __func__,
			 rv ? "successful" : "failed");
	पूर्ण
	acpi_os_initialized = true;

	वापस AE_OK;
पूर्ण

acpi_status __init acpi_os_initialize1(व्योम)
अणु
	kacpid_wq = alloc_workqueue("kacpid", 0, 1);
	kacpi_notअगरy_wq = alloc_workqueue("kacpi_notify", 0, 1);
	kacpi_hotplug_wq = alloc_ordered_workqueue("kacpi_hotplug", 0);
	BUG_ON(!kacpid_wq);
	BUG_ON(!kacpi_notअगरy_wq);
	BUG_ON(!kacpi_hotplug_wq);
	acpi_osi_init();
	वापस AE_OK;
पूर्ण

acpi_status acpi_os_terminate(व्योम)
अणु
	अगर (acpi_irq_handler) अणु
		acpi_os_हटाओ_पूर्णांकerrupt_handler(acpi_gbl_FADT.sci_पूर्णांकerrupt,
						 acpi_irq_handler);
	पूर्ण

	acpi_os_unmap_generic_address(&acpi_gbl_FADT.xgpe1_block);
	acpi_os_unmap_generic_address(&acpi_gbl_FADT.xgpe0_block);
	acpi_gbl_xgpe0_block_logical_address = 0UL;
	acpi_gbl_xgpe1_block_logical_address = 0UL;

	acpi_os_unmap_generic_address(&acpi_gbl_FADT.xpm1b_event_block);
	acpi_os_unmap_generic_address(&acpi_gbl_FADT.xpm1a_event_block);

	अगर (acpi_gbl_FADT.flags & ACPI_FADT_RESET_REGISTER)
		acpi_os_unmap_generic_address(&acpi_gbl_FADT.reset_रेजिस्टर);

	destroy_workqueue(kacpid_wq);
	destroy_workqueue(kacpi_notअगरy_wq);
	destroy_workqueue(kacpi_hotplug_wq);

	वापस AE_OK;
पूर्ण

acpi_status acpi_os_prepare_sleep(u8 sleep_state, u32 pm1a_control,
				  u32 pm1b_control)
अणु
	पूर्णांक rc = 0;
	अगर (__acpi_os_prepare_sleep)
		rc = __acpi_os_prepare_sleep(sleep_state,
					     pm1a_control, pm1b_control);
	अगर (rc < 0)
		वापस AE_ERROR;
	अन्यथा अगर (rc > 0)
		वापस AE_CTRL_TERMINATE;

	वापस AE_OK;
पूर्ण

व्योम acpi_os_set_prepare_sleep(पूर्णांक (*func)(u8 sleep_state,
			       u32 pm1a_ctrl, u32 pm1b_ctrl))
अणु
	__acpi_os_prepare_sleep = func;
पूर्ण

#अगर (ACPI_REDUCED_HARDWARE)
acpi_status acpi_os_prepare_extended_sleep(u8 sleep_state, u32 val_a,
				  u32 val_b)
अणु
	पूर्णांक rc = 0;
	अगर (__acpi_os_prepare_extended_sleep)
		rc = __acpi_os_prepare_extended_sleep(sleep_state,
					     val_a, val_b);
	अगर (rc < 0)
		वापस AE_ERROR;
	अन्यथा अगर (rc > 0)
		वापस AE_CTRL_TERMINATE;

	वापस AE_OK;
पूर्ण
#अन्यथा
acpi_status acpi_os_prepare_extended_sleep(u8 sleep_state, u32 val_a,
				  u32 val_b)
अणु
	वापस AE_OK;
पूर्ण
#पूर्ण_अगर

व्योम acpi_os_set_prepare_extended_sleep(पूर्णांक (*func)(u8 sleep_state,
			       u32 val_a, u32 val_b))
अणु
	__acpi_os_prepare_extended_sleep = func;
पूर्ण

acpi_status acpi_os_enter_sleep(u8 sleep_state,
				u32 reg_a_value, u32 reg_b_value)
अणु
	acpi_status status;

	अगर (acpi_gbl_reduced_hardware)
		status = acpi_os_prepare_extended_sleep(sleep_state,
							reg_a_value,
							reg_b_value);
	अन्यथा
		status = acpi_os_prepare_sleep(sleep_state,
					       reg_a_value, reg_b_value);
	वापस status;
पूर्ण
