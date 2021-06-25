<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File:	mca_drv.c
 * Purpose:	Generic MCA handling layer
 *
 * Copyright (C) 2004 FUJITSU LIMITED
 * Copyright (C) 2004 Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>
 * Copyright (C) 2005 Silicon Graphics, Inc
 * Copyright (C) 2005 Keith Owens <kaos@sgi.com>
 * Copyright (C) 2006 Russ Anderson <rja@sgi.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/memblock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/mca.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hw_irq.h>

#समावेश "mca_drv.h"

/* max size of SAL error record (शेष) */
अटल पूर्णांक sal_rec_max = 10000;

/* from mca_drv_यंत्र.S */
बाह्य व्योम *mca_handler_bhhook(व्योम);

अटल DEFINE_SPINLOCK(mca_bh_lock);

प्रकार क्रमागत अणु
	MCA_IS_LOCAL  = 0,
	MCA_IS_GLOBAL = 1
पूर्ण mca_type_t;

#घोषणा MAX_PAGE_ISOLATE 1024

अटल काष्ठा page *page_isolate[MAX_PAGE_ISOLATE];
अटल पूर्णांक num_page_isolate = 0;

प्रकार क्रमागत अणु
	ISOLATE_NG,
	ISOLATE_OK,
	ISOLATE_NONE
पूर्ण isolate_status_t;

प्रकार क्रमागत अणु
	MCA_NOT_RECOVERED = 0,
	MCA_RECOVERED	  = 1
पूर्ण recovery_status_t;

/*
 *  This pool keeps poपूर्णांकers to the section part of SAL error record
 */
अटल काष्ठा अणु
	slidx_list_t *buffer; /* section poपूर्णांकer list pool */
	पूर्णांक	     cur_idx; /* Current index of section poपूर्णांकer list pool */
	पूर्णांक	     max_idx; /* Maximum index of section poपूर्णांकer list pool */
पूर्ण slidx_pool;

अटल पूर्णांक
fatal_mca(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[256];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);
	ia64_mca_prपूर्णांकk(KERN_ALERT "MCA: %s\n", buf);

	वापस MCA_NOT_RECOVERED;
पूर्ण

अटल पूर्णांक
mca_recovered(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[256];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);
	ia64_mca_prपूर्णांकk(KERN_INFO "MCA: %s\n", buf);

	वापस MCA_RECOVERED;
पूर्ण

/**
 * mca_page_isolate - isolate a poisoned page in order not to use it later
 * @paddr:	poisoned memory location
 *
 * Return value:
 *	one of isolate_status_t, ISOLATE_OK/NG/NONE.
 */

अटल isolate_status_t
mca_page_isolate(अचिन्हित दीर्घ paddr)
अणु
	पूर्णांक i;
	काष्ठा page *p;

	/* whether physical address is valid or not */
	अगर (!ia64_phys_addr_valid(paddr))
		वापस ISOLATE_NONE;

	अगर (!pfn_valid(paddr >> PAGE_SHIFT))
		वापस ISOLATE_NONE;

	/* convert physical address to physical page number */
	p = pfn_to_page(paddr>>PAGE_SHIFT);

	/* check whether a page number have been alपढ़ोy रेजिस्टरed or not */
	क्रम (i = 0; i < num_page_isolate; i++)
		अगर (page_isolate[i] == p)
			वापस ISOLATE_OK; /* alपढ़ोy listed */

	/* limitation check */
	अगर (num_page_isolate == MAX_PAGE_ISOLATE)
		वापस ISOLATE_NG;

	/* kick pages having attribute 'SLAB' or 'Reserved' */
	अगर (PageSlab(p) || PageReserved(p))
		वापस ISOLATE_NG;

	/* add attribute 'Reserved' and रेजिस्टर the page */
	get_page(p);
	SetPageReserved(p);
	page_isolate[num_page_isolate++] = p;

	वापस ISOLATE_OK;
पूर्ण

/**
 * mca_hanlder_bh - Kill the process which occurred memory पढ़ो error
 * @paddr:	poisoned address received from MCA Handler
 */

व्योम
mca_handler_bh(अचिन्हित दीर्घ paddr, व्योम *iip, अचिन्हित दीर्घ ipsr)
अणु
	ia64_mlogbuf_dump();
	prपूर्णांकk(KERN_ERR "OS_MCA: process [cpu %d, pid: %d, uid: %d, "
		"iip: %p, psr: 0x%lx,paddr: 0x%lx](%s) encounters MCA.\n",
	       raw_smp_processor_id(), current->pid,
		from_kuid(&init_user_ns, current_uid()),
		iip, ipsr, paddr, current->comm);

	spin_lock(&mca_bh_lock);
	चयन (mca_page_isolate(paddr)) अणु
	हाल ISOLATE_OK:
		prपूर्णांकk(KERN_DEBUG "Page isolation: ( %lx ) success.\n", paddr);
		अवरोध;
	हाल ISOLATE_NG:
		prपूर्णांकk(KERN_CRIT "Page isolation: ( %lx ) failure.\n", paddr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock(&mca_bh_lock);

	/* This process is about to be समाप्तed itself */
	करो_निकास(SIGKILL);
पूर्ण

/**
 * mca_make_peidx - Make index of processor error section
 * @slpi:	poपूर्णांकer to record of processor error section
 * @peidx:	poपूर्णांकer to index of processor error section
 */

अटल व्योम
mca_make_peidx(sal_log_processor_info_t *slpi, peidx_table_t *peidx)
अणु
	/*
	 * calculate the start address of
	 *   "struct cpuid_info" and "sal_processor_static_info_t".
	 */
	u64 total_check_num = slpi->valid.num_cache_check
				+ slpi->valid.num_tlb_check
				+ slpi->valid.num_bus_check
				+ slpi->valid.num_reg_file_check
				+ slpi->valid.num_ms_check;
	u64 head_size =	माप(sal_log_mod_error_info_t) * total_check_num
			+ माप(sal_log_processor_info_t);
	u64 mid_size  = slpi->valid.cpuid_info * माप(काष्ठा sal_cpuid_info);

	peidx_head(peidx)   = slpi;
	peidx_mid(peidx)    = (काष्ठा sal_cpuid_info *)
		(slpi->valid.cpuid_info ? ((अक्षर*)slpi + head_size) : शून्य);
	peidx_bottom(peidx) = (sal_processor_अटल_info_t *)
		(slpi->valid.psi_अटल_काष्ठा ?
			((अक्षर*)slpi + head_size + mid_size) : शून्य);
पूर्ण

/**
 * mca_make_slidx -  Make index of SAL error record
 * @buffer:	poपूर्णांकer to SAL error record
 * @slidx:	poपूर्णांकer to index of SAL error record
 *
 * Return value:
 *	1 अगर record has platक्रमm error / 0 अगर not
 */
#घोषणा LOG_INDEX_ADD_SECT_PTR(sect, ptr) \
	अणुslidx_list_t *hl = &slidx_pool.buffer[slidx_pool.cur_idx]; \
	hl->hdr = ptr; \
	list_add(&hl->list, &(sect)); \
	slidx_pool.cur_idx = (slidx_pool.cur_idx + 1)%slidx_pool.max_idx; पूर्ण

अटल पूर्णांक
mca_make_slidx(व्योम *buffer, slidx_table_t *slidx)
अणु
	पूर्णांक platक्रमm_err = 0;
	पूर्णांक record_len = ((sal_log_record_header_t*)buffer)->len;
	u32 ercd_pos;
	पूर्णांक sects;
	sal_log_section_hdr_t *sp;

	/*
	 * Initialize index referring current record
	 */
	INIT_LIST_HEAD(&(slidx->proc_err));
	INIT_LIST_HEAD(&(slidx->mem_dev_err));
	INIT_LIST_HEAD(&(slidx->sel_dev_err));
	INIT_LIST_HEAD(&(slidx->pci_bus_err));
	INIT_LIST_HEAD(&(slidx->smbios_dev_err));
	INIT_LIST_HEAD(&(slidx->pci_comp_err));
	INIT_LIST_HEAD(&(slidx->plat_specअगरic_err));
	INIT_LIST_HEAD(&(slidx->host_ctlr_err));
	INIT_LIST_HEAD(&(slidx->plat_bus_err));
	INIT_LIST_HEAD(&(slidx->unsupported));

	/*
	 * Extract a Record Header
	 */
	slidx->header = buffer;

	/*
	 * Extract each section records
	 * (arranged from "int ia64_log_platform_info_print()")
	 */
	क्रम (ercd_pos = माप(sal_log_record_header_t), sects = 0;
		ercd_pos < record_len; ercd_pos += sp->len, sects++) अणु
		sp = (sal_log_section_hdr_t *)((अक्षर*)buffer + ercd_pos);
		अगर (!efi_guidcmp(sp->guid, SAL_PROC_DEV_ERR_SECT_GUID)) अणु
			LOG_INDEX_ADD_SECT_PTR(slidx->proc_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_MEM_DEV_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->mem_dev_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_SEL_DEV_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->sel_dev_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_PCI_BUS_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->pci_bus_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_SMBIOS_DEV_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->smbios_dev_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_PCI_COMP_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->pci_comp_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_SPECIFIC_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->plat_specअगरic_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_HOST_CTLR_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->host_ctlr_err, sp);
		पूर्ण अन्यथा अगर (!efi_guidcmp(sp->guid,
				SAL_PLAT_BUS_ERR_SECT_GUID)) अणु
			platक्रमm_err = 1;
			LOG_INDEX_ADD_SECT_PTR(slidx->plat_bus_err, sp);
		पूर्ण अन्यथा अणु
			LOG_INDEX_ADD_SECT_PTR(slidx->unsupported, sp);
		पूर्ण
	पूर्ण
	slidx->n_sections = sects;

	वापस platक्रमm_err;
पूर्ण

/**
 * init_record_index_pools - Initialize pool of lists क्रम SAL record index
 *
 * Return value:
 *	0 on Success / -ENOMEM on Failure
 */
अटल पूर्णांक
init_record_index_pools(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rec_max_size;  /* Maximum size of SAL error records */
	पूर्णांक sect_min_size; /* Minimum size of SAL error sections */
	/* minimum size table of each section */
	अटल पूर्णांक sal_log_sect_min_sizes[] = अणु
		माप(sal_log_processor_info_t)
		+ माप(sal_processor_अटल_info_t),
		माप(sal_log_mem_dev_err_info_t),
		माप(sal_log_sel_dev_err_info_t),
		माप(sal_log_pci_bus_err_info_t),
		माप(sal_log_smbios_dev_err_info_t),
		माप(sal_log_pci_comp_err_info_t),
		माप(sal_log_plat_specअगरic_err_info_t),
		माप(sal_log_host_ctlr_err_info_t),
		माप(sal_log_plat_bus_err_info_t),
	पूर्ण;

	/*
	 * MCA handler cannot allocate new memory on flight,
	 * so we pपुनः_स्मृतिate enough memory to handle a SAL record.
	 *
	 * Initialize a handling set of slidx_pool:
	 *   1. Pick up the max size of SAL error records
	 *   2. Pick up the min size of SAL error sections
	 *   3. Allocate the pool as enough to 2 SAL records
	 *     (now we can estimate the maxinum of section in a record.)
	 */

	/* - 1 - */
	rec_max_size = sal_rec_max;

	/* - 2 - */
	sect_min_size = sal_log_sect_min_sizes[0];
	क्रम (i = 1; i < माप sal_log_sect_min_sizes/माप(माप_प्रकार); i++)
		अगर (sect_min_size > sal_log_sect_min_sizes[i])
			sect_min_size = sal_log_sect_min_sizes[i];

	/* - 3 - */
	slidx_pool.max_idx = (rec_max_size/sect_min_size) * 2 + 1;
	slidx_pool.buffer =
		kदो_स्मृति_array(slidx_pool.max_idx, माप(slidx_list_t),
			      GFP_KERNEL);

	वापस slidx_pool.buffer ? 0 : -ENOMEM;
पूर्ण


/*****************************************************************************
 * Recovery functions                                                        *
 *****************************************************************************/

/**
 * is_mca_global - Check whether this MCA is global or not
 * @peidx:	poपूर्णांकer of index of processor error section
 * @pbci:	poपूर्णांकer to pal_bus_check_info_t
 * @sos:	poपूर्णांकer to hand off काष्ठा between SAL and OS
 *
 * Return value:
 *	MCA_IS_LOCAL / MCA_IS_GLOBAL
 */

अटल mca_type_t
is_mca_global(peidx_table_t *peidx, pal_bus_check_info_t *pbci,
	      काष्ठा ia64_sal_os_state *sos)
अणु
	pal_processor_state_info_t *psp =
		(pal_processor_state_info_t*)peidx_psp(peidx);

	/*
	 * PAL can request a rendezvous, अगर the MCA has a global scope.
	 * If "rz_always" flag is set, SAL requests MCA rendezvous
	 * in spite of global MCA.
	 * Thereक्रमe it is local MCA when rendezvous has not been requested.
	 * Failed to rendezvous, the प्रणाली must be करोwn.
	 */
	चयन (sos->rv_rc) अणु
		हाल -1: /* SAL rendezvous unsuccessful */
			वापस MCA_IS_GLOBAL;
		हाल  0: /* SAL rendezvous not required */
			वापस MCA_IS_LOCAL;
		हाल  1: /* SAL rendezvous successful पूर्णांक */
		हाल  2: /* SAL rendezvous successful पूर्णांक with init */
		शेष:
			अवरोध;
	पूर्ण

	/*
	 * If One or more Cache/TLB/Reg_File/Uarch_Check is here,
	 * it would be a local MCA. (i.e. processor पूर्णांकernal error)
	 */
	अगर (psp->tc || psp->cc || psp->rc || psp->uc)
		वापस MCA_IS_LOCAL;
	
	/*
	 * Bus_Check काष्ठाure with Bus_Check.ib (पूर्णांकernal bus error) flag set
	 * would be a global MCA. (e.g. a प्रणाली bus address parity error)
	 */
	अगर (!pbci || pbci->ib)
		वापस MCA_IS_GLOBAL;

	/*
	 * Bus_Check काष्ठाure with Bus_Check.eb (बाह्यal bus error) flag set
	 * could be either a local MCA or a global MCA.
	 *
	 * Referring Bus_Check.bsi:
	 *   0: Unknown/unclassअगरied
	 *   1: BERR#
	 *   2: BINIT#
	 *   3: Hard Fail
	 * (FIXME: Are these SGI specअगरic or generic bsi values?)
	 */
	अगर (pbci->eb)
		चयन (pbci->bsi) अणु
			हाल 0:
				/* e.g. a load from poisoned memory */
				वापस MCA_IS_LOCAL;
			हाल 1:
			हाल 2:
			हाल 3:
				वापस MCA_IS_GLOBAL;
		पूर्ण

	वापस MCA_IS_GLOBAL;
पूर्ण

/**
 * get_target_identअगरier - Get the valid Cache or Bus check target identअगरier.
 * @peidx:	poपूर्णांकer of index of processor error section
 *
 * Return value:
 *	target address on Success / 0 on Failure
 */
अटल u64
get_target_identअगरier(peidx_table_t *peidx)
अणु
	u64 target_address = 0;
	sal_log_mod_error_info_t *smei;
	pal_cache_check_info_t *pcci;
	पूर्णांक i, level = 9;

	/*
	 * Look through the cache checks क्रम a valid target identअगरier
	 * If more than one valid target identअगरier, वापस the one
	 * with the lowest cache level.
	 */
	क्रम (i = 0; i < peidx_cache_check_num(peidx); i++) अणु
		smei = (sal_log_mod_error_info_t *)peidx_cache_check(peidx, i);
		अगर (smei->valid.target_identअगरier && smei->target_identअगरier) अणु
			pcci = (pal_cache_check_info_t *)&(smei->check_info);
			अगर (!target_address || (pcci->level < level)) अणु
				target_address = smei->target_identअगरier;
				level = pcci->level;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (target_address)
		वापस target_address;

	/*
	 * Look at the bus check क्रम a valid target identअगरier
	 */
	smei = peidx_bus_check(peidx, 0);
	अगर (smei && smei->valid.target_identअगरier)
		वापस smei->target_identअगरier;

	वापस 0;
पूर्ण

/**
 * recover_from_पढ़ो_error - Try to recover the errors which type are "read"s.
 * @slidx:	poपूर्णांकer of index of SAL error record
 * @peidx:	poपूर्णांकer of index of processor error section
 * @pbci:	poपूर्णांकer of pal_bus_check_info
 * @sos:	poपूर्णांकer to hand off काष्ठा between SAL and OS
 *
 * Return value:
 *	1 on Success / 0 on Failure
 */

अटल पूर्णांक
recover_from_पढ़ो_error(slidx_table_t *slidx,
			peidx_table_t *peidx, pal_bus_check_info_t *pbci,
			काष्ठा ia64_sal_os_state *sos)
अणु
	u64 target_identअगरier;
	काष्ठा pal_min_state_area *pmsa;
	काष्ठा ia64_psr *psr1, *psr2;
	ia64_fptr_t *mca_hdlr_bh = (ia64_fptr_t*)mca_handler_bhhook;

	/* Is target address valid? */
	target_identअगरier = get_target_identअगरier(peidx);
	अगर (!target_identअगरier)
		वापस fatal_mca("target address not valid");

	/*
	 * cpu पढ़ो or memory-mapped io पढ़ो
	 *
	 *    offending process  affected process  OS MCA करो
	 *     kernel mode        kernel mode       करोwn प्रणाली
	 *     kernel mode        user   mode       समाप्त the process
	 *     user   mode        kernel mode       करोwn प्रणाली (*)
	 *     user   mode        user   mode       समाप्त the process
	 *
	 * (*) You could terminate offending user-mode process
	 *    अगर (pbci->pv && pbci->pl != 0) *and* अगर you sure
	 *    the process not have any locks of kernel.
	 */

	/* Is minstate valid? */
	अगर (!peidx_bottom(peidx) || !(peidx_bottom(peidx)->valid.minstate))
		वापस fatal_mca("minstate not valid");
	psr1 =(काष्ठा ia64_psr *)&(peidx_minstate_area(peidx)->pmsa_ipsr);
	psr2 =(काष्ठा ia64_psr *)&(peidx_minstate_area(peidx)->pmsa_xpsr);

	/*
	 *  Check the privilege level of पूर्णांकerrupted context.
	 *   If it is user-mode, then terminate affected process.
	 */

	pmsa = sos->pal_min_state;
	अगर (psr1->cpl != 0 ||
	   ((psr2->cpl != 0) && mca_recover_range(pmsa->pmsa_iip))) अणु
		/*
		 *  setup क्रम resume to bottom half of MCA,
		 * "mca_handler_bhhook"
		 */
		/* pass to bhhook as argument (gr8, ...) */
		pmsa->pmsa_gr[8-1] = target_identअगरier;
		pmsa->pmsa_gr[9-1] = pmsa->pmsa_iip;
		pmsa->pmsa_gr[10-1] = pmsa->pmsa_ipsr;
		/* set पूर्णांकerrupted वापस address (but no use) */
		pmsa->pmsa_br0 = pmsa->pmsa_iip;
		/* change resume address to bottom half */
		pmsa->pmsa_iip = mca_hdlr_bh->fp;
		pmsa->pmsa_gr[1-1] = mca_hdlr_bh->gp;
		/* set cpl with kernel mode */
		psr2 = (काष्ठा ia64_psr *)&pmsa->pmsa_ipsr;
		psr2->cpl = 0;
		psr2->ri  = 0;
		psr2->bn  = 1;
		psr2->i  = 0;

		वापस mca_recovered("user memory corruption. "
				"kill affected process - recovered.");
	पूर्ण

	वापस fatal_mca("kernel context not recovered, iip 0x%lx\n",
			 pmsa->pmsa_iip);
पूर्ण

/**
 * recover_from_platक्रमm_error - Recover from platक्रमm error.
 * @slidx:	poपूर्णांकer of index of SAL error record
 * @peidx:	poपूर्णांकer of index of processor error section
 * @pbci:	poपूर्णांकer of pal_bus_check_info
 * @sos:	poपूर्णांकer to hand off काष्ठा between SAL and OS
 *
 * Return value:
 *	1 on Success / 0 on Failure
 */

अटल पूर्णांक
recover_from_platक्रमm_error(slidx_table_t *slidx, peidx_table_t *peidx,
			    pal_bus_check_info_t *pbci,
			    काष्ठा ia64_sal_os_state *sos)
अणु
	पूर्णांक status = 0;
	pal_processor_state_info_t *psp =
		(pal_processor_state_info_t*)peidx_psp(peidx);

	अगर (psp->bc && pbci->eb && pbci->bsi == 0) अणु
		चयन(pbci->type) अणु
		हाल 1: /* partial पढ़ो */
		हाल 3: /* full line(cpu) पढ़ो */
		हाल 9: /* I/O space पढ़ो */
			status = recover_from_पढ़ो_error(slidx, peidx, pbci,
							 sos);
			अवरोध;
		हाल 0: /* unknown */
		हाल 2: /* partial ग_लिखो */
		हाल 4: /* full line ग_लिखो */
		हाल 5: /* implicit or explicit ग_लिखो-back operation */
		हाल 6: /* snoop probe */
		हाल 7: /* incoming or outgoing ptc.g */
		हाल 8: /* ग_लिखो coalescing transactions */
		हाल 10: /* I/O space ग_लिखो */
		हाल 11: /* पूर्णांकer-processor पूर्णांकerrupt message(IPI) */
		हाल 12: /* पूर्णांकerrupt acknowledge or
				बाह्यal task priority cycle */
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (psp->cc && !psp->bc) अणु	/* Cache error */
		status = recover_from_पढ़ो_error(slidx, peidx, pbci, sos);
	पूर्ण

	वापस status;
पूर्ण

/*
 * recover_from_tlb_check
 * @peidx:	poपूर्णांकer of index of processor error section
 *
 * Return value:
 *	1 on Success / 0 on Failure
 */
अटल पूर्णांक
recover_from_tlb_check(peidx_table_t *peidx)
अणु
	sal_log_mod_error_info_t *smei;
	pal_tlb_check_info_t *ptci;

	smei = (sal_log_mod_error_info_t *)peidx_tlb_check(peidx, 0);
	ptci = (pal_tlb_check_info_t *)&(smei->check_info);

	/*
	 * Look क्रम signature of a duplicate TLB DTC entry, which is
	 * a SW bug and always fatal.
	 */
	अगर (ptci->op == PAL_TLB_CHECK_OP_PURGE
	    && !(ptci->itr || ptci->dtc || ptci->itc))
		वापस fatal_mca("Duplicate TLB entry");

	वापस mca_recovered("TLB check recovered");
पूर्ण

/**
 * recover_from_processor_error
 * @platक्रमm:	whether there are some platक्रमm error section or not
 * @slidx:	poपूर्णांकer of index of SAL error record
 * @peidx:	poपूर्णांकer of index of processor error section
 * @pbci:	poपूर्णांकer of pal_bus_check_info
 * @sos:	poपूर्णांकer to hand off काष्ठा between SAL and OS
 *
 * Return value:
 *	1 on Success / 0 on Failure
 */

अटल पूर्णांक
recover_from_processor_error(पूर्णांक platक्रमm, slidx_table_t *slidx,
			     peidx_table_t *peidx, pal_bus_check_info_t *pbci,
			     काष्ठा ia64_sal_os_state *sos)
अणु
	pal_processor_state_info_t *psp =
		(pal_processor_state_info_t*)peidx_psp(peidx);

	/*
	 * Processor recovery status must key off of the PAL recovery
	 * status in the Processor State Parameter.
	 */

	/*
	 * The machine check is corrected.
	 */
	अगर (psp->cm == 1)
		वापस mca_recovered("machine check is already corrected.");

	/*
	 * The error was not contained.  Software must be reset.
	 */
	अगर (psp->us || psp->ci == 0)
		वापस fatal_mca("error not contained");

	/*
	 * Look क्रम recoverable TLB check
	 */
	अगर (psp->tc && !(psp->cc || psp->bc || psp->rc || psp->uc))
		वापस recover_from_tlb_check(peidx);

	/*
	 * The cache check and bus check bits have four possible states
	 *   cc bc
	 *    1  1	Memory error, attempt recovery
	 *    1  0	Cache error, attempt recovery
	 *    0  1	I/O error, attempt recovery
	 *    0  0	Other error type, not recovered
	 */
	अगर (psp->cc == 0 && (psp->bc == 0 || pbci == शून्य))
		वापस fatal_mca("No cache or bus check");

	/*
	 * Cannot handle more than one bus check.
	 */
	अगर (peidx_bus_check_num(peidx) > 1)
		वापस fatal_mca("Too many bus checks");

	अगर (pbci->ib)
		वापस fatal_mca("Internal Bus error");
	अगर (pbci->eb && pbci->bsi > 0)
		वापस fatal_mca("External bus check fatal status");

	/*
	 * This is a local MCA and estimated as a recoverable error.
	 */
	अगर (platक्रमm)
		वापस recover_from_platक्रमm_error(slidx, peidx, pbci, sos);

	/*
	 * On account of strange SAL error record, we cannot recover.
	 */
	वापस fatal_mca("Strange SAL record");
पूर्ण

/**
 * mca_try_to_recover - Try to recover from MCA
 * @rec:	poपूर्णांकer to a SAL error record
 * @sos:	poपूर्णांकer to hand off काष्ठा between SAL and OS
 *
 * Return value:
 *	1 on Success / 0 on Failure
 */

अटल पूर्णांक
mca_try_to_recover(व्योम *rec, काष्ठा ia64_sal_os_state *sos)
अणु
	पूर्णांक platक्रमm_err;
	पूर्णांक n_proc_err;
	slidx_table_t slidx;
	peidx_table_t peidx;
	pal_bus_check_info_t pbci;

	/* Make index of SAL error record */
	platक्रमm_err = mca_make_slidx(rec, &slidx);

	/* Count processor error sections */
	n_proc_err = slidx_count(&slidx, proc_err);

	 /* Now, OS can recover when there is one processor error section */
	अगर (n_proc_err > 1)
		वापस fatal_mca("Too Many Errors");
	अन्यथा अगर (n_proc_err == 0)
		/* Weird SAL record ... We can't करो anything */
		वापस fatal_mca("Weird SAL record");

	/* Make index of processor error section */
	mca_make_peidx((sal_log_processor_info_t*)
		slidx_first_entry(&slidx.proc_err)->hdr, &peidx);

	/* Extract Processor BUS_CHECK[0] */
	*((u64*)&pbci) = peidx_check_info(&peidx, bus_check, 0);

	/* Check whether MCA is global or not */
	अगर (is_mca_global(&peidx, &pbci, sos))
		वापस fatal_mca("global MCA");
	
	/* Try to recover a processor error */
	वापस recover_from_processor_error(platक्रमm_err, &slidx, &peidx,
					    &pbci, sos);
पूर्ण

/*
 * =============================================================================
 */

पूर्णांक __init mca_बाह्यal_handler_init(व्योम)
अणु
	अगर (init_record_index_pools())
		वापस -ENOMEM;

	/* रेजिस्टर बाह्यal mca handlers */
	अगर (ia64_reg_MCA_extension(mca_try_to_recover)) अणु	
		prपूर्णांकk(KERN_ERR "ia64_reg_MCA_extension failed.\n");
		kमुक्त(slidx_pool.buffer);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास mca_बाह्यal_handler_निकास(व्योम)
अणु
	/* unरेजिस्टर बाह्यal mca handlers */
	ia64_unreg_MCA_extension();
	kमुक्त(slidx_pool.buffer);
पूर्ण

module_init(mca_बाह्यal_handler_init);
module_निकास(mca_बाह्यal_handler_निकास);

module_param(sal_rec_max, पूर्णांक, 0644);
MODULE_PARM_DESC(sal_rec_max, "Max size of SAL error record");

MODULE_DESCRIPTION("ia64 platform dependent mca handler driver");
MODULE_LICENSE("GPL");
