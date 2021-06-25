<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extensible Firmware Interface
 *
 * Based on Extensible Firmware Interface Specअगरication version 0.9
 * April 30, 1999
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2003 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * (c) Copyright 2006 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 *
 * All EFI Runसमय Services are not implemented yet as EFI only
 * supports physical mode addressing on SoftSDV. This is to be fixed
 * in a future version.  --drummond 1999-07-20
 *
 * Implemented EFI runसमय services and भव mode calls.  --davidm
 *
 * Goutham Rao: <goutham.rao@पूर्णांकel.com>
 *	Skip non-WB memory and ignore empty memory ranges.
 */
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/efi.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kregs.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlbflush.h>

#घोषणा EFI_DEBUG	0

#घोषणा ESI_TABLE_GUID					\
    EFI_GUID(0x43EA58DC, 0xCF28, 0x4b06, 0xB3,		\
	     0x91, 0xB7, 0x50, 0x59, 0x34, 0x2B, 0xD4)

अटल अचिन्हित दीर्घ mps_phys = EFI_INVALID_TABLE_ADDR;
अटल __initdata अचिन्हित दीर्घ palo_phys;

अचिन्हित दीर्घ __initdata esi_phys = EFI_INVALID_TABLE_ADDR;
अचिन्हित दीर्घ hcdp_phys = EFI_INVALID_TABLE_ADDR;
अचिन्हित दीर्घ sal_systab_phys = EFI_INVALID_TABLE_ADDR;

अटल स्थिर efi_config_table_type_t arch_tables[] __initस्थिर = अणु
	अणुESI_TABLE_GUID,				&esi_phys,		"ESI"		पूर्ण,
	अणुHCDP_TABLE_GUID,				&hcdp_phys,		"HCDP"		पूर्ण,
	अणुMPS_TABLE_GUID,				&mps_phys,		"MPS"		पूर्ण,
	अणुPROCESSOR_ABSTRACTION_LAYER_OVERWRITE_GUID,	&palo_phys,		"PALO"		पूर्ण,
	अणुSAL_SYSTEM_TABLE_GUID,				&sal_systab_phys,	"SALsystab"	पूर्ण,
	अणुपूर्ण,
पूर्ण;

बाह्य efi_status_t efi_call_phys (व्योम *, ...);

अटल efi_runसमय_services_t *runसमय;
अटल u64 mem_limit = ~0UL, max_addr = ~0UL, min_addr = 0UL;

#घोषणा efi_call_virt(f, args...)	(*(f))(args)

#घोषणा STUB_GET_TIME(prefix, adjust_arg)				       \
अटल efi_status_t							       \
prefix##_get_समय (efi_समय_प्रकार *पंचांग, efi_समय_cap_t *tc)			       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_समय_cap_t *atc = शून्य;					       \
	efi_status_t ret;						       \
									       \
	अगर (tc)								       \
		atc = adjust_arg(tc);					       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix((efi_get_समय_प्रकार *) __va(runसमय->get_समय),    \
				adjust_arg(पंचांग), atc);			       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_SET_TIME(prefix, adjust_arg)				       \
अटल efi_status_t							       \
prefix##_set_समय (efi_समय_प्रकार *पंचांग)					       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_status_t ret;						       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix((efi_set_समय_प्रकार *) __va(runसमय->set_समय),    \
				adjust_arg(पंचांग));			       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_GET_WAKEUP_TIME(prefix, adjust_arg)			       \
अटल efi_status_t							       \
prefix##_get_wakeup_समय (efi_bool_t *enabled, efi_bool_t *pending,	       \
			  efi_समय_प्रकार *पंचांग)				       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_status_t ret;						       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix(					       \
		(efi_get_wakeup_समय_प्रकार *) __va(runसमय->get_wakeup_समय),      \
		adjust_arg(enabled), adjust_arg(pending), adjust_arg(पंचांग));     \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_SET_WAKEUP_TIME(prefix, adjust_arg)			       \
अटल efi_status_t							       \
prefix##_set_wakeup_समय (efi_bool_t enabled, efi_समय_प्रकार *पंचांग)		       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_समय_प्रकार *aपंचांग = शून्य;						       \
	efi_status_t ret;						       \
									       \
	अगर (पंचांग)								       \
		aपंचांग = adjust_arg(पंचांग);					       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix(					       \
		(efi_set_wakeup_समय_प्रकार *) __va(runसमय->set_wakeup_समय),      \
		enabled, aपंचांग);						       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_GET_VARIABLE(prefix, adjust_arg)				       \
अटल efi_status_t							       \
prefix##_get_variable (efi_अक्षर16_t *name, efi_guid_t *venकरोr, u32 *attr,      \
		       अचिन्हित दीर्घ *data_size, व्योम *data)		       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	u32 *aattr = शून्य;						       \
	efi_status_t ret;						       \
									       \
	अगर (attr)							       \
		aattr = adjust_arg(attr);				       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix(					       \
		(efi_get_variable_t *) __va(runसमय->get_variable),	       \
		adjust_arg(name), adjust_arg(venकरोr), aattr,		       \
		adjust_arg(data_size), adjust_arg(data));		       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_GET_NEXT_VARIABLE(prefix, adjust_arg)			       \
अटल efi_status_t							       \
prefix##_get_next_variable (अचिन्हित दीर्घ *name_size, efi_अक्षर16_t *name,      \
			    efi_guid_t *venकरोr)				       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_status_t ret;						       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix(					       \
		(efi_get_next_variable_t *) __va(runसमय->get_next_variable),  \
		adjust_arg(name_size), adjust_arg(name), adjust_arg(venकरोr));  \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_SET_VARIABLE(prefix, adjust_arg)				       \
अटल efi_status_t							       \
prefix##_set_variable (efi_अक्षर16_t *name, efi_guid_t *venकरोr,		       \
		       u32 attr, अचिन्हित दीर्घ data_size,		       \
		       व्योम *data)					       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_status_t ret;						       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix(					       \
		(efi_set_variable_t *) __va(runसमय->set_variable),	       \
		adjust_arg(name), adjust_arg(venकरोr), attr, data_size,	       \
		adjust_arg(data));					       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_GET_NEXT_HIGH_MONO_COUNT(prefix, adjust_arg)		       \
अटल efi_status_t							       \
prefix##_get_next_high_mono_count (u32 *count)				       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_status_t ret;						       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	ret = efi_call_##prefix((efi_get_next_high_mono_count_t *)	       \
				__va(runसमय->get_next_high_mono_count),       \
				adjust_arg(count));			       \
	ia64_load_scratch_fpregs(fr);					       \
	वापस ret;							       \
पूर्ण

#घोषणा STUB_RESET_SYSTEM(prefix, adjust_arg)				       \
अटल व्योम								       \
prefix##_reset_प्रणाली (पूर्णांक reset_type, efi_status_t status,		       \
		       अचिन्हित दीर्घ data_size, efi_अक्षर16_t *data)	       \
अणु									       \
	काष्ठा ia64_fpreg fr[6];					       \
	efi_अक्षर16_t *adata = शून्य;					       \
									       \
	अगर (data)							       \
		adata = adjust_arg(data);				       \
									       \
	ia64_save_scratch_fpregs(fr);					       \
	efi_call_##prefix(						       \
		(efi_reset_प्रणाली_t *) __va(runसमय->reset_प्रणाली),	       \
		reset_type, status, data_size, adata);			       \
	/* should not वापस, but just in हाल... */			       \
	ia64_load_scratch_fpregs(fr);					       \
पूर्ण

#घोषणा phys_ptr(arg)	((__typeof__(arg)) ia64_tpa(arg))

STUB_GET_TIME(phys, phys_ptr)
STUB_SET_TIME(phys, phys_ptr)
STUB_GET_WAKEUP_TIME(phys, phys_ptr)
STUB_SET_WAKEUP_TIME(phys, phys_ptr)
STUB_GET_VARIABLE(phys, phys_ptr)
STUB_GET_NEXT_VARIABLE(phys, phys_ptr)
STUB_SET_VARIABLE(phys, phys_ptr)
STUB_GET_NEXT_HIGH_MONO_COUNT(phys, phys_ptr)
STUB_RESET_SYSTEM(phys, phys_ptr)

#घोषणा id(arg)	arg

STUB_GET_TIME(virt, id)
STUB_SET_TIME(virt, id)
STUB_GET_WAKEUP_TIME(virt, id)
STUB_SET_WAKEUP_TIME(virt, id)
STUB_GET_VARIABLE(virt, id)
STUB_GET_NEXT_VARIABLE(virt, id)
STUB_SET_VARIABLE(virt, id)
STUB_GET_NEXT_HIGH_MONO_COUNT(virt, id)
STUB_RESET_SYSTEM(virt, id)

व्योम
efi_समय_लोofday (काष्ठा बारpec64 *ts)
अणु
	efi_समय_प्रकार पंचांग;

	अगर ((*efi.get_समय)(&पंचांग, शून्य) != EFI_SUCCESS) अणु
		स_रखो(ts, 0, माप(*ts));
		वापस;
	पूर्ण

	ts->tv_sec = स_गढ़ो64(पंचांग.year, पंचांग.month, पंचांग.day,
			    पंचांग.hour, पंचांग.minute, पंचांग.second);
	ts->tv_nsec = पंचांग.nanosecond;
पूर्ण

अटल पूर्णांक
is_memory_available (efi_memory_desc_t *md)
अणु
	अगर (!(md->attribute & EFI_MEMORY_WB))
		वापस 0;

	चयन (md->type) अणु
	      हाल EFI_LOADER_CODE:
	      हाल EFI_LOADER_DATA:
	      हाल EFI_BOOT_SERVICES_CODE:
	      हाल EFI_BOOT_SERVICES_DATA:
	      हाल EFI_CONVENTIONAL_MEMORY:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

प्रकार काष्ठा kern_memdesc अणु
	u64 attribute;
	u64 start;
	u64 num_pages;
पूर्ण kern_memdesc_t;

अटल kern_memdesc_t *kern_memmap;

#घोषणा efi_md_size(md)	(md->num_pages << EFI_PAGE_SHIFT)

अटल अंतरभूत u64
kmd_end(kern_memdesc_t *kmd)
अणु
	वापस (kmd->start + (kmd->num_pages << EFI_PAGE_SHIFT));
पूर्ण

अटल अंतरभूत u64
efi_md_end(efi_memory_desc_t *md)
अणु
	वापस (md->phys_addr + efi_md_size(md));
पूर्ण

अटल अंतरभूत पूर्णांक
efi_wb(efi_memory_desc_t *md)
अणु
	वापस (md->attribute & EFI_MEMORY_WB);
पूर्ण

अटल अंतरभूत पूर्णांक
efi_uc(efi_memory_desc_t *md)
अणु
	वापस (md->attribute & EFI_MEMORY_UC);
पूर्ण

अटल व्योम
walk (efi_मुक्तmem_callback_t callback, व्योम *arg, u64 attr)
अणु
	kern_memdesc_t *k;
	u64 start, end, voff;

	voff = (attr == EFI_MEMORY_WB) ? PAGE_OFFSET : __IA64_UNCACHED_OFFSET;
	क्रम (k = kern_memmap; k->start != ~0UL; k++) अणु
		अगर (k->attribute != attr)
			जारी;
		start = PAGE_ALIGN(k->start);
		end = (k->start + (k->num_pages << EFI_PAGE_SHIFT)) & PAGE_MASK;
		अगर (start < end)
			अगर ((*callback)(start + voff, end + voff, arg) < 0)
				वापस;
	पूर्ण
पूर्ण

/*
 * Walk the EFI memory map and call CALLBACK once क्रम each EFI memory
 * descriptor that has memory that is available क्रम OS use.
 */
व्योम
efi_memmap_walk (efi_मुक्तmem_callback_t callback, व्योम *arg)
अणु
	walk(callback, arg, EFI_MEMORY_WB);
पूर्ण

/*
 * Walk the EFI memory map and call CALLBACK once क्रम each EFI memory
 * descriptor that has memory that is available क्रम uncached allocator.
 */
व्योम
efi_memmap_walk_uc (efi_मुक्तmem_callback_t callback, व्योम *arg)
अणु
	walk(callback, arg, EFI_MEMORY_UC);
पूर्ण

/*
 * Look क्रम the PAL_CODE region reported by EFI and map it using an
 * ITR to enable safe PAL calls in भव mode.  See IA-64 Processor
 * Abstraction Layer chapter 11 in ADAG
 */
व्योम *
efi_get_pal_addr (व्योम)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;
	पूर्णांक pal_code_count = 0;
	u64 vaddr, mask;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (md->type != EFI_PAL_CODE)
			जारी;

		अगर (++pal_code_count > 1) अणु
			prपूर्णांकk(KERN_ERR "Too many EFI Pal Code memory ranges, "
			       "dropped @ %llx\n", md->phys_addr);
			जारी;
		पूर्ण
		/*
		 * The only ITLB entry in region 7 that is used is the one
		 * installed by __start().  That entry covers a 64MB range.
		 */
		mask  = ~((1 << KERNEL_TR_PAGE_SHIFT) - 1);
		vaddr = PAGE_OFFSET + md->phys_addr;

		/*
		 * We must check that the PAL mapping won't overlap with the
		 * kernel mapping.
		 *
		 * PAL code is guaranteed to be aligned on a घातer of 2 between
		 * 4k and 256KB and that only one ITR is needed to map it. This
		 * implies that the PAL code is always aligned on its size,
		 * i.e., the बंदst matching page size supported by the TLB.
		 * Thereक्रमe PAL code is guaranteed never to cross a 64MB unless
		 * it is bigger than 64MB (very unlikely!).  So क्रम now the
		 * following test is enough to determine whether or not we need
		 * a dedicated ITR क्रम the PAL code.
		 */
		अगर ((vaddr & mask) == (KERNEL_START & mask)) अणु
			prपूर्णांकk(KERN_INFO "%s: no need to install ITR for PAL code\n",
			       __func__);
			जारी;
		पूर्ण

		अगर (efi_md_size(md) > IA64_GRANULE_SIZE)
			panic("Whoa!  PAL code size bigger than a granule!");

#अगर EFI_DEBUG
		mask  = ~((1 << IA64_GRANULE_SHIFT) - 1);

		prपूर्णांकk(KERN_INFO "CPU %d: mapping PAL code "
			"[0x%llx-0x%llx) into [0x%llx-0x%llx)\n",
			smp_processor_id(), md->phys_addr,
			md->phys_addr + efi_md_size(md),
			vaddr & mask, (vaddr & mask) + IA64_GRANULE_SIZE);
#पूर्ण_अगर
		वापस __va(md->phys_addr);
	पूर्ण
	prपूर्णांकk(KERN_WARNING "%s: no PAL-code memory-descriptor found\n",
	       __func__);
	वापस शून्य;
पूर्ण


अटल u8 __init palo_checksum(u8 *buffer, u32 length)
अणु
	u8 sum = 0;
	u8 *end = buffer + length;

	जबतक (buffer < end)
		sum = (u8) (sum + *(buffer++));

	वापस sum;
पूर्ण

/*
 * Parse and handle PALO table which is published at:
 * http://www.dig64.org/home/DIG64_PALO_R1_0.pdf
 */
अटल व्योम __init handle_palo(अचिन्हित दीर्घ phys_addr)
अणु
	काष्ठा palo_table *palo = __va(phys_addr);
	u8  checksum;

	अगर (म_भेदन(palo->signature, PALO_SIG, माप(PALO_SIG) - 1)) अणु
		prपूर्णांकk(KERN_INFO "PALO signature incorrect.\n");
		वापस;
	पूर्ण

	checksum = palo_checksum((u8 *)palo, palo->length);
	अगर (checksum) अणु
		prपूर्णांकk(KERN_INFO "PALO checksum incorrect.\n");
		वापस;
	पूर्ण

	setup_ptcg_sem(palo->max_tlb_purges, NPTCG_FROM_PALO);
पूर्ण

व्योम
efi_map_pal_code (व्योम)
अणु
	व्योम *pal_vaddr = efi_get_pal_addr ();
	u64 psr;

	अगर (!pal_vaddr)
		वापस;

	/*
	 * Cannot ग_लिखो to CRx with PSR.ic=1
	 */
	psr = ia64_clear_ic();
	ia64_itr(0x1, IA64_TR_PALCODE,
		 GRANULEROUNDDOWN((अचिन्हित दीर्घ) pal_vaddr),
		 pte_val(pfn_pte(__pa(pal_vaddr) >> PAGE_SHIFT, PAGE_KERNEL)),
		 IA64_GRANULE_SHIFT);
	ia64_set_psr(psr);		/* restore psr */
पूर्ण

व्योम __init
efi_init (व्योम)
अणु
	स्थिर efi_प्रणाली_table_t *efi_systab;
	व्योम *efi_map_start, *efi_map_end;
	u64 efi_desc_size;
	अक्षर *cp;

	set_bit(EFI_BOOT, &efi.flags);
	set_bit(EFI_64BIT, &efi.flags);

	/*
	 * It's too early to be able to use the standard kernel command line
	 * support...
	 */
	क्रम (cp = boot_command_line; *cp; ) अणु
		अगर (स_भेद(cp, "mem=", 4) == 0) अणु
			mem_limit = memparse(cp + 4, &cp);
		पूर्ण अन्यथा अगर (स_भेद(cp, "max_addr=", 9) == 0) अणु
			max_addr = GRANULEROUNDDOWN(memparse(cp + 9, &cp));
		पूर्ण अन्यथा अगर (स_भेद(cp, "min_addr=", 9) == 0) अणु
			min_addr = GRANULEROUNDDOWN(memparse(cp + 9, &cp));
		पूर्ण अन्यथा अणु
			जबतक (*cp != ' ' && *cp)
				++cp;
			जबतक (*cp == ' ')
				++cp;
		पूर्ण
	पूर्ण
	अगर (min_addr != 0UL)
		prपूर्णांकk(KERN_INFO "Ignoring memory below %lluMB\n",
		       min_addr >> 20);
	अगर (max_addr != ~0UL)
		prपूर्णांकk(KERN_INFO "Ignoring memory above %lluMB\n",
		       max_addr >> 20);

	efi_systab = __va(ia64_boot_param->efi_systab);

	/*
	 * Verअगरy the EFI Table
	 */
	अगर (efi_systab == शून्य)
		panic("Whoa! Can't find EFI system table.\n");
	अगर (efi_systab_check_header(&efi_systab->hdr, 1))
		panic("Whoa! EFI system table signature incorrect\n");

	efi_systab_report_header(&efi_systab->hdr, efi_systab->fw_venकरोr);

	palo_phys      = EFI_INVALID_TABLE_ADDR;

	अगर (efi_config_parse_tables(__va(efi_systab->tables),
				    efi_systab->nr_tables,
				    arch_tables) != 0)
		वापस;

	अगर (palo_phys != EFI_INVALID_TABLE_ADDR)
		handle_palo(palo_phys);

	runसमय = __va(efi_systab->runसमय);
	efi.get_समय = phys_get_समय;
	efi.set_समय = phys_set_समय;
	efi.get_wakeup_समय = phys_get_wakeup_समय;
	efi.set_wakeup_समय = phys_set_wakeup_समय;
	efi.get_variable = phys_get_variable;
	efi.get_next_variable = phys_get_next_variable;
	efi.set_variable = phys_set_variable;
	efi.get_next_high_mono_count = phys_get_next_high_mono_count;
	efi.reset_प्रणाली = phys_reset_प्रणाली;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

#अगर EFI_DEBUG
	/* prपूर्णांक EFI memory map: */
	अणु
		efi_memory_desc_t *md;
		व्योम *p;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0, p = efi_map_start; p < efi_map_end;
		     ++i, p += efi_desc_size)
		अणु
			स्थिर अक्षर *unit;
			अचिन्हित दीर्घ size;
			अक्षर buf[64];

			md = p;
			size = md->num_pages << EFI_PAGE_SHIFT;

			अगर ((size >> 40) > 0) अणु
				size >>= 40;
				unit = "TB";
			पूर्ण अन्यथा अगर ((size >> 30) > 0) अणु
				size >>= 30;
				unit = "GB";
			पूर्ण अन्यथा अगर ((size >> 20) > 0) अणु
				size >>= 20;
				unit = "MB";
			पूर्ण अन्यथा अणु
				size >>= 10;
				unit = "KB";
			पूर्ण

			prपूर्णांकk("mem%02d: %s "
			       "range=[0x%016llx-0x%016llx) (%4lu%s)\n",
			       i, efi_md_typeattr_क्रमmat(buf, माप(buf), md),
			       md->phys_addr,
			       md->phys_addr + efi_md_size(md), size, unit);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	efi_map_pal_code();
	efi_enter_भव_mode();
पूर्ण

व्योम
efi_enter_भव_mode (व्योम)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	efi_status_t status;
	u64 efi_desc_size;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (md->attribute & EFI_MEMORY_RUNTIME) अणु
			/*
			 * Some descriptors have multiple bits set, so the
			 * order of the tests is relevant.
			 */
			अगर (md->attribute & EFI_MEMORY_WB) अणु
				md->virt_addr = (u64) __va(md->phys_addr);
			पूर्ण अन्यथा अगर (md->attribute & EFI_MEMORY_UC) अणु
				md->virt_addr = (u64) ioremap(md->phys_addr, 0);
			पूर्ण अन्यथा अगर (md->attribute & EFI_MEMORY_WC) अणु
#अगर 0
				md->virt_addr = ia64_remap(md->phys_addr,
							   (_PAGE_A |
							    _PAGE_P |
							    _PAGE_D |
							    _PAGE_MA_WC |
							    _PAGE_PL_0 |
							    _PAGE_AR_RW));
#अन्यथा
				prपूर्णांकk(KERN_INFO "EFI_MEMORY_WC mapping\n");
				md->virt_addr = (u64) ioremap(md->phys_addr, 0);
#पूर्ण_अगर
			पूर्ण अन्यथा अगर (md->attribute & EFI_MEMORY_WT) अणु
#अगर 0
				md->virt_addr = ia64_remap(md->phys_addr,
							   (_PAGE_A |
							    _PAGE_P |
							    _PAGE_D |
							    _PAGE_MA_WT |
							    _PAGE_PL_0 |
							    _PAGE_AR_RW));
#अन्यथा
				prपूर्णांकk(KERN_INFO "EFI_MEMORY_WT mapping\n");
				md->virt_addr = (u64) ioremap(md->phys_addr, 0);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण

	status = efi_call_phys(__va(runसमय->set_भव_address_map),
			       ia64_boot_param->efi_memmap_size,
			       efi_desc_size,
			       ia64_boot_param->efi_memdesc_version,
			       ia64_boot_param->efi_memmap);
	अगर (status != EFI_SUCCESS) अणु
		prपूर्णांकk(KERN_WARNING "warning: unable to switch EFI into "
		       "virtual mode (status=%lu)\n", status);
		वापस;
	पूर्ण

	set_bit(EFI_RUNTIME_SERVICES, &efi.flags);

	/*
	 * Now that EFI is in भव mode, we call the EFI functions more
	 * efficiently:
	 */
	efi.get_समय = virt_get_समय;
	efi.set_समय = virt_set_समय;
	efi.get_wakeup_समय = virt_get_wakeup_समय;
	efi.set_wakeup_समय = virt_set_wakeup_समय;
	efi.get_variable = virt_get_variable;
	efi.get_next_variable = virt_get_next_variable;
	efi.set_variable = virt_set_variable;
	efi.get_next_high_mono_count = virt_get_next_high_mono_count;
	efi.reset_प्रणाली = virt_reset_प्रणाली;
पूर्ण

/*
 * Walk the EFI memory map looking क्रम the I/O port range.  There can only be
 * one entry of this type, other I/O port ranges should be described via ACPI.
 */
u64
efi_get_iobase (व्योम)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (md->type == EFI_MEMORY_MAPPED_IO_PORT_SPACE) अणु
			अगर (md->attribute & EFI_MEMORY_UC)
				वापस md->phys_addr;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा kern_memdesc *
kern_memory_descriptor (अचिन्हित दीर्घ phys_addr)
अणु
	काष्ठा kern_memdesc *md;

	क्रम (md = kern_memmap; md->start != ~0UL; md++) अणु
		अगर (phys_addr - md->start < (md->num_pages << EFI_PAGE_SHIFT))
			 वापस md;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल efi_memory_desc_t *
efi_memory_descriptor (अचिन्हित दीर्घ phys_addr)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;

		अगर (phys_addr - md->phys_addr < efi_md_size(md))
			 वापस md;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
efi_memmap_पूर्णांकersects (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;
	अचिन्हित दीर्घ end;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	end = phys_addr + size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (md->phys_addr < end && efi_md_end(md) > phys_addr)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
efi_mem_type (अचिन्हित दीर्घ phys_addr)
अणु
	efi_memory_desc_t *md = efi_memory_descriptor(phys_addr);

	अगर (md)
		वापस md->type;
	वापस -EINVAL;
पूर्ण

u64
efi_mem_attributes (अचिन्हित दीर्घ phys_addr)
अणु
	efi_memory_desc_t *md = efi_memory_descriptor(phys_addr);

	अगर (md)
		वापस md->attribute;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(efi_mem_attributes);

u64
efi_mem_attribute (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end = phys_addr + size;
	efi_memory_desc_t *md = efi_memory_descriptor(phys_addr);
	u64 attr;

	अगर (!md)
		वापस 0;

	/*
	 * EFI_MEMORY_RUNTIME is not a memory attribute; it just tells
	 * the kernel that firmware needs this region mapped.
	 */
	attr = md->attribute & ~EFI_MEMORY_RUNTIME;
	करो अणु
		अचिन्हित दीर्घ md_end = efi_md_end(md);

		अगर (end <= md_end)
			वापस attr;

		md = efi_memory_descriptor(md_end);
		अगर (!md || (md->attribute & ~EFI_MEMORY_RUNTIME) != attr)
			वापस 0;
	पूर्ण जबतक (md);
	वापस 0;	/* never reached */
पूर्ण

u64
kern_mem_attribute (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end = phys_addr + size;
	काष्ठा kern_memdesc *md;
	u64 attr;

	/*
	 * This is a hack क्रम ioremap calls beक्रमe we set up kern_memmap.
	 * Maybe we should करो efi_memmap_init() earlier instead.
	 */
	अगर (!kern_memmap) अणु
		attr = efi_mem_attribute(phys_addr, size);
		अगर (attr & EFI_MEMORY_WB)
			वापस EFI_MEMORY_WB;
		वापस 0;
	पूर्ण

	md = kern_memory_descriptor(phys_addr);
	अगर (!md)
		वापस 0;

	attr = md->attribute;
	करो अणु
		अचिन्हित दीर्घ md_end = kmd_end(md);

		अगर (end <= md_end)
			वापस attr;

		md = kern_memory_descriptor(md_end);
		अगर (!md || md->attribute != attr)
			वापस 0;
	पूर्ण जबतक (md);
	वापस 0;	/* never reached */
पूर्ण

पूर्णांक
valid_phys_addr_range (phys_addr_t phys_addr, अचिन्हित दीर्घ size)
अणु
	u64 attr;

	/*
	 * /dev/mem पढ़ोs and ग_लिखोs use copy_to_user(), which implicitly
	 * uses a granule-sized kernel identity mapping.  It's really
	 * only safe to करो this क्रम regions in kern_memmap.  For more
	 * details, see Documentation/ia64/aliasing.rst.
	 */
	attr = kern_mem_attribute(phys_addr, size);
	अगर (attr & EFI_MEMORY_WB || attr & EFI_MEMORY_UC)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक
valid_mmap_phys_addr_range (अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ phys_addr = pfn << PAGE_SHIFT;
	u64 attr;

	attr = efi_mem_attribute(phys_addr, size);

	/*
	 * /dev/mem mmap uses normal user pages, so we करोn't need the entire
	 * granule, but the entire region we're mapping must support the same
	 * attribute.
	 */
	अगर (attr & EFI_MEMORY_WB || attr & EFI_MEMORY_UC)
		वापस 1;

	/*
	 * Intel firmware करोesn't tell us about all the MMIO regions, so
	 * in general we have to allow mmap requests.  But अगर EFI *करोes*
	 * tell us about anything inside this region, we should deny it.
	 * The user can always map a smaller region to aव्योम the overlap.
	 */
	अगर (efi_memmap_पूर्णांकersects(phys_addr, size))
		वापस 0;

	वापस 1;
पूर्ण

pgprot_t
phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size,
		     pgprot_t vma_prot)
अणु
	अचिन्हित दीर्घ phys_addr = pfn << PAGE_SHIFT;
	u64 attr;

	/*
	 * For /dev/mem mmap, we use user mappings, but अगर the region is
	 * in kern_memmap (and hence may be covered by a kernel mapping),
	 * we must use the same attribute as the kernel mapping.
	 */
	attr = kern_mem_attribute(phys_addr, size);
	अगर (attr & EFI_MEMORY_WB)
		वापस pgprot_cacheable(vma_prot);
	अन्यथा अगर (attr & EFI_MEMORY_UC)
		वापस pgprot_noncached(vma_prot);

	/*
	 * Some chipsets करोn't support UC access to memory.  If
	 * WB is supported, we prefer that.
	 */
	अगर (efi_mem_attribute(phys_addr, size) & EFI_MEMORY_WB)
		वापस pgprot_cacheable(vma_prot);

	वापस pgprot_noncached(vma_prot);
पूर्ण

पूर्णांक __init
efi_uart_console_only(व्योम)
अणु
	efi_status_t status;
	अक्षर *s, name[] = "ConOut";
	efi_guid_t guid = EFI_GLOBAL_VARIABLE_GUID;
	efi_अक्षर16_t *utf16, name_utf16[32];
	अचिन्हित अक्षर data[1024];
	अचिन्हित दीर्घ size = माप(data);
	काष्ठा efi_generic_dev_path *hdr, *end_addr;
	पूर्णांक uart = 0;

	/* Convert to UTF-16 */
	utf16 = name_utf16;
	s = name;
	जबतक (*s)
		*utf16++ = *s++ & 0x7f;
	*utf16 = 0;

	status = efi.get_variable(name_utf16, &guid, शून्य, &size, data);
	अगर (status != EFI_SUCCESS) अणु
		prपूर्णांकk(KERN_ERR "No EFI %s variable?\n", name);
		वापस 0;
	पूर्ण

	hdr = (काष्ठा efi_generic_dev_path *) data;
	end_addr = (काष्ठा efi_generic_dev_path *) ((u8 *) data + size);
	जबतक (hdr < end_addr) अणु
		अगर (hdr->type == EFI_DEV_MSG &&
		    hdr->sub_type == EFI_DEV_MSG_UART)
			uart = 1;
		अन्यथा अगर (hdr->type == EFI_DEV_END_PATH ||
			  hdr->type == EFI_DEV_END_PATH2) अणु
			अगर (!uart)
				वापस 0;
			अगर (hdr->sub_type == EFI_DEV_END_ENTIRE)
				वापस 1;
			uart = 0;
		पूर्ण
		hdr = (काष्ठा efi_generic_dev_path *)((u8 *) hdr + hdr->length);
	पूर्ण
	prपूर्णांकk(KERN_ERR "Malformed %s value\n", name);
	वापस 0;
पूर्ण

/*
 * Look क्रम the first granule aligned memory descriptor memory
 * that is big enough to hold EFI memory map. Make sure this
 * descriptor is at least granule sized so it करोes not get trimmed
 */
काष्ठा kern_memdesc *
find_memmap_space (व्योम)
अणु
	u64	contig_low=0, contig_high=0;
	u64	as = 0, ae;
	व्योम *efi_map_start, *efi_map_end, *p, *q;
	efi_memory_desc_t *md, *pmd = शून्य, *check_md;
	u64	space_needed, efi_desc_size;
	अचिन्हित दीर्घ total_mem = 0;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	/*
	 * Worst हाल: we need 3 kernel descriptors क्रम each efi descriptor
	 * (अगर every entry has a WB part in the middle, and UC head and tail),
	 * plus one क्रम the end marker.
	 */
	space_needed = माप(kern_memdesc_t) *
		(3 * (ia64_boot_param->efi_memmap_size/efi_desc_size) + 1);

	क्रम (p = efi_map_start; p < efi_map_end; pmd = md, p += efi_desc_size) अणु
		md = p;
		अगर (!efi_wb(md)) अणु
			जारी;
		पूर्ण
		अगर (pmd == शून्य || !efi_wb(pmd) ||
		    efi_md_end(pmd) != md->phys_addr) अणु
			contig_low = GRANULEROUNDUP(md->phys_addr);
			contig_high = efi_md_end(md);
			क्रम (q = p + efi_desc_size; q < efi_map_end;
			     q += efi_desc_size) अणु
				check_md = q;
				अगर (!efi_wb(check_md))
					अवरोध;
				अगर (contig_high != check_md->phys_addr)
					अवरोध;
				contig_high = efi_md_end(check_md);
			पूर्ण
			contig_high = GRANULEROUNDDOWN(contig_high);
		पूर्ण
		अगर (!is_memory_available(md) || md->type == EFI_LOADER_DATA)
			जारी;

		/* Round ends inward to granule boundaries */
		as = max(contig_low, md->phys_addr);
		ae = min(contig_high, efi_md_end(md));

		/* keep within max_addr= and min_addr= command line arg */
		as = max(as, min_addr);
		ae = min(ae, max_addr);
		अगर (ae <= as)
			जारी;

		/* aव्योम going over mem= command line arg */
		अगर (total_mem + (ae - as) > mem_limit)
			ae -= total_mem + (ae - as) - mem_limit;

		अगर (ae <= as)
			जारी;

		अगर (ae - as > space_needed)
			अवरोध;
	पूर्ण
	अगर (p >= efi_map_end)
		panic("Can't allocate space for kernel memory descriptors");

	वापस __va(as);
पूर्ण

/*
 * Walk the EFI memory map and gather all memory available क्रम kernel
 * to use.  We can allocate partial granules only अगर the unavailable
 * parts exist, and are WB.
 */
अचिन्हित दीर्घ
efi_memmap_init(u64 *s, u64 *e)
अणु
	काष्ठा kern_memdesc *k, *prev = शून्य;
	u64	contig_low=0, contig_high=0;
	u64	as, ae, lim;
	व्योम *efi_map_start, *efi_map_end, *p, *q;
	efi_memory_desc_t *md, *pmd = शून्य, *check_md;
	u64	efi_desc_size;
	अचिन्हित दीर्घ total_mem = 0;

	k = kern_memmap = find_memmap_space();

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; pmd = md, p += efi_desc_size) अणु
		md = p;
		अगर (!efi_wb(md)) अणु
			अगर (efi_uc(md) &&
			    (md->type == EFI_CONVENTIONAL_MEMORY ||
			     md->type == EFI_BOOT_SERVICES_DATA)) अणु
				k->attribute = EFI_MEMORY_UC;
				k->start = md->phys_addr;
				k->num_pages = md->num_pages;
				k++;
			पूर्ण
			जारी;
		पूर्ण
		अगर (pmd == शून्य || !efi_wb(pmd) ||
		    efi_md_end(pmd) != md->phys_addr) अणु
			contig_low = GRANULEROUNDUP(md->phys_addr);
			contig_high = efi_md_end(md);
			क्रम (q = p + efi_desc_size; q < efi_map_end;
			     q += efi_desc_size) अणु
				check_md = q;
				अगर (!efi_wb(check_md))
					अवरोध;
				अगर (contig_high != check_md->phys_addr)
					अवरोध;
				contig_high = efi_md_end(check_md);
			पूर्ण
			contig_high = GRANULEROUNDDOWN(contig_high);
		पूर्ण
		अगर (!is_memory_available(md))
			जारी;

		/*
		 * Round ends inward to granule boundaries
		 * Give trimmings to uncached allocator
		 */
		अगर (md->phys_addr < contig_low) अणु
			lim = min(efi_md_end(md), contig_low);
			अगर (efi_uc(md)) अणु
				अगर (k > kern_memmap &&
				    (k-1)->attribute == EFI_MEMORY_UC &&
				    kmd_end(k-1) == md->phys_addr) अणु
					(k-1)->num_pages +=
						(lim - md->phys_addr)
						>> EFI_PAGE_SHIFT;
				पूर्ण अन्यथा अणु
					k->attribute = EFI_MEMORY_UC;
					k->start = md->phys_addr;
					k->num_pages = (lim - md->phys_addr)
						>> EFI_PAGE_SHIFT;
					k++;
				पूर्ण
			पूर्ण
			as = contig_low;
		पूर्ण अन्यथा
			as = md->phys_addr;

		अगर (efi_md_end(md) > contig_high) अणु
			lim = max(md->phys_addr, contig_high);
			अगर (efi_uc(md)) अणु
				अगर (lim == md->phys_addr && k > kern_memmap &&
				    (k-1)->attribute == EFI_MEMORY_UC &&
				    kmd_end(k-1) == md->phys_addr) अणु
					(k-1)->num_pages += md->num_pages;
				पूर्ण अन्यथा अणु
					k->attribute = EFI_MEMORY_UC;
					k->start = lim;
					k->num_pages = (efi_md_end(md) - lim)
						>> EFI_PAGE_SHIFT;
					k++;
				पूर्ण
			पूर्ण
			ae = contig_high;
		पूर्ण अन्यथा
			ae = efi_md_end(md);

		/* keep within max_addr= and min_addr= command line arg */
		as = max(as, min_addr);
		ae = min(ae, max_addr);
		अगर (ae <= as)
			जारी;

		/* aव्योम going over mem= command line arg */
		अगर (total_mem + (ae - as) > mem_limit)
			ae -= total_mem + (ae - as) - mem_limit;

		अगर (ae <= as)
			जारी;
		अगर (prev && kmd_end(prev) == md->phys_addr) अणु
			prev->num_pages += (ae - as) >> EFI_PAGE_SHIFT;
			total_mem += ae - as;
			जारी;
		पूर्ण
		k->attribute = EFI_MEMORY_WB;
		k->start = as;
		k->num_pages = (ae - as) >> EFI_PAGE_SHIFT;
		total_mem += ae - as;
		prev = k++;
	पूर्ण
	k->start = ~0L; /* end-marker */

	/* reserve the memory we are using क्रम kern_memmap */
	*s = (u64)kern_memmap;
	*e = (u64)++k;

	वापस total_mem;
पूर्ण

व्योम
efi_initialize_iomem_resources(काष्ठा resource *code_resource,
			       काष्ठा resource *data_resource,
			       काष्ठा resource *bss_resource)
अणु
	काष्ठा resource *res;
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;
	अक्षर *name;
	अचिन्हित दीर्घ flags, desc;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	res = शून्य;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;

		अगर (md->num_pages == 0) /* should not happen */
			जारी;

		flags = IORESOURCE_MEM | IORESOURCE_BUSY;
		desc = IORES_DESC_NONE;

		चयन (md->type) अणु

			हाल EFI_MEMORY_MAPPED_IO:
			हाल EFI_MEMORY_MAPPED_IO_PORT_SPACE:
				जारी;

			हाल EFI_LOADER_CODE:
			हाल EFI_LOADER_DATA:
			हाल EFI_BOOT_SERVICES_DATA:
			हाल EFI_BOOT_SERVICES_CODE:
			हाल EFI_CONVENTIONAL_MEMORY:
				अगर (md->attribute & EFI_MEMORY_WP) अणु
					name = "System ROM";
					flags |= IORESOURCE_READONLY;
				पूर्ण अन्यथा अगर (md->attribute == EFI_MEMORY_UC) अणु
					name = "Uncached RAM";
				पूर्ण अन्यथा अणु
					name = "System RAM";
					flags |= IORESOURCE_SYSRAM;
				पूर्ण
				अवरोध;

			हाल EFI_ACPI_MEMORY_NVS:
				name = "ACPI Non-volatile Storage";
				desc = IORES_DESC_ACPI_NV_STORAGE;
				अवरोध;

			हाल EFI_UNUSABLE_MEMORY:
				name = "reserved";
				flags |= IORESOURCE_DISABLED;
				अवरोध;

			हाल EFI_PERSISTENT_MEMORY:
				name = "Persistent Memory";
				desc = IORES_DESC_PERSISTENT_MEMORY;
				अवरोध;

			हाल EFI_RESERVED_TYPE:
			हाल EFI_RUNTIME_SERVICES_CODE:
			हाल EFI_RUNTIME_SERVICES_DATA:
			हाल EFI_ACPI_RECLAIM_MEMORY:
			शेष:
				name = "reserved";
				अवरोध;
		पूर्ण

		अगर ((res = kzalloc(माप(काष्ठा resource),
				   GFP_KERNEL)) == शून्य) अणु
			prपूर्णांकk(KERN_ERR
			       "failed to allocate resource for iomem\n");
			वापस;
		पूर्ण

		res->name = name;
		res->start = md->phys_addr;
		res->end = md->phys_addr + efi_md_size(md) - 1;
		res->flags = flags;
		res->desc = desc;

		अगर (insert_resource(&iomem_resource, res) < 0)
			kमुक्त(res);
		अन्यथा अणु
			/*
			 * We करोn't know which region contains
			 * kernel data so we try it repeatedly and
			 * let the resource manager test it.
			 */
			insert_resource(res, code_resource);
			insert_resource(res, data_resource);
			insert_resource(res, bss_resource);
#अगर_घोषित CONFIG_KEXEC
                        insert_resource(res, &efi_memmap_res);
                        insert_resource(res, &boot_param_res);
			अगर (crashk_res.end > crashk_res.start)
				insert_resource(res, &crashk_res);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KEXEC
/* find a block of memory aligned to 64M exclude reserved regions
   rsvd_regions are sorted
 */
अचिन्हित दीर्घ __init
kdump_find_rsvd_region (अचिन्हित दीर्घ size, काष्ठा rsvd_region *r, पूर्णांक n)
अणु
	पूर्णांक i;
	u64 start, end;
	u64 alignment = 1UL << _PAGE_SIZE_64M;
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (!efi_wb(md))
			जारी;
		start = ALIGN(md->phys_addr, alignment);
		end = efi_md_end(md);
		क्रम (i = 0; i < n; i++) अणु
			अगर (__pa(r[i].start) >= start && __pa(r[i].end) < end) अणु
				अगर (__pa(r[i].start) > start + size)
					वापस start;
				start = ALIGN(__pa(r[i].end), alignment);
				अगर (i < n-1 &&
				    __pa(r[i+1].start) < start + size)
					जारी;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (end > start + size)
			वापस start;
	पूर्ण

	prपूर्णांकk(KERN_WARNING
	       "Cannot reserve 0x%lx byte of memory for crashdump\n", size);
	वापस ~0UL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRASH_DUMP
/* locate the size find a the descriptor at a certain address */
अचिन्हित दीर्घ __init
vmcore_find_descriptor_size (अचिन्हित दीर्घ address)
अणु
	व्योम *efi_map_start, *efi_map_end, *p;
	efi_memory_desc_t *md;
	u64 efi_desc_size;
	अचिन्हित दीर्घ ret = 0;

	efi_map_start = __va(ia64_boot_param->efi_memmap);
	efi_map_end   = efi_map_start + ia64_boot_param->efi_memmap_size;
	efi_desc_size = ia64_boot_param->efi_memdesc_size;

	क्रम (p = efi_map_start; p < efi_map_end; p += efi_desc_size) अणु
		md = p;
		अगर (efi_wb(md) && md->type == EFI_LOADER_DATA
		    && md->phys_addr == address) अणु
			ret = efi_md_size(md);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		prपूर्णांकk(KERN_WARNING "Cannot locate EFI vmcore descriptor\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर

अक्षर *efi_systab_show_arch(अक्षर *str)
अणु
	अगर (mps_phys != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "MPS=0x%lx\n", mps_phys);
	अगर (hcdp_phys != EFI_INVALID_TABLE_ADDR)
		str += प्र_लिखो(str, "HCDP=0x%lx\n", hcdp_phys);
	वापस str;
पूर्ण
