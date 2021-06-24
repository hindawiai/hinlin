<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *              GRU KERNEL MCS INSTRUCTIONS
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश "gru.h"
#समावेश "grulib.h"
#समावेश "grutables.h"

/* 10 sec */
#अगर_घोषित CONFIG_IA64
#समावेश <यंत्र/processor.h>
#घोषणा GRU_OPERATION_TIMEOUT	(((cycles_t) local_cpu_data->itc_freq)*10)
#घोषणा CLKS2NSEC(c)		((c) *1000000000 / local_cpu_data->itc_freq)
#अन्यथा
#समावेश <linux/sync_core.h>
#समावेश <यंत्र/tsc.h>
#घोषणा GRU_OPERATION_TIMEOUT	((cycles_t) tsc_khz*10*1000)
#घोषणा CLKS2NSEC(c)		((c) * 1000000 / tsc_khz)
#पूर्ण_अगर

/* Extract the status field from a kernel handle */
#घोषणा GET_MSEG_HANDLE_STATUS(h)	(((*(अचिन्हित दीर्घ *)(h)) >> 16) & 3)

काष्ठा mcs_op_statistic mcs_op_statistics[mcsop_last];

अटल व्योम update_mcs_stats(क्रमागत mcs_op op, अचिन्हित दीर्घ clks)
अणु
	अचिन्हित दीर्घ nsec;

	nsec = CLKS2NSEC(clks);
	atomic_दीर्घ_inc(&mcs_op_statistics[op].count);
	atomic_दीर्घ_add(nsec, &mcs_op_statistics[op].total);
	अगर (mcs_op_statistics[op].max < nsec)
		mcs_op_statistics[op].max = nsec;
पूर्ण

अटल व्योम start_inकाष्ठाion(व्योम *h)
अणु
	अचिन्हित दीर्घ *w0 = h;

	wmb();		/* setting CMD/STATUS bits must be last */
	*w0 = *w0 | 0x20001;
	gru_flush_cache(h);
पूर्ण

अटल व्योम report_inकाष्ठाion_समयout(व्योम *h)
अणु
	अचिन्हित दीर्घ goff = GSEGPOFF((अचिन्हित दीर्घ)h);
	अक्षर *id = "???";

	अगर (TYPE_IS(CCH, goff))
		id = "CCH";
	अन्यथा अगर (TYPE_IS(TGH, goff))
		id = "TGH";
	अन्यथा अगर (TYPE_IS(TFH, goff))
		id = "TFH";

	panic(KERN_ALERT "GRU %p (%s) is malfunctioning\n", h, id);
पूर्ण

अटल पूर्णांक रुको_inकाष्ठाion_complete(व्योम *h, क्रमागत mcs_op opc)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ start_समय = get_cycles();

	जबतक (1) अणु
		cpu_relax();
		status = GET_MSEG_HANDLE_STATUS(h);
		अगर (status != CCHSTATUS_ACTIVE)
			अवरोध;
		अगर (GRU_OPERATION_TIMEOUT < (get_cycles() - start_समय)) अणु
			report_inकाष्ठाion_समयout(h);
			start_समय = get_cycles();
		पूर्ण
	पूर्ण
	अगर (gru_options & OPT_STATS)
		update_mcs_stats(opc, get_cycles() - start_समय);
	वापस status;
पूर्ण

पूर्णांक cch_allocate(काष्ठा gru_context_configuration_handle *cch)
अणु
	पूर्णांक ret;

	cch->opc = CCHOP_ALLOCATE;
	start_inकाष्ठाion(cch);
	ret = रुको_inकाष्ठाion_complete(cch, cchop_allocate);

	/*
	 * Stop speculation पूर्णांकo the GSEG being mapped by the previous ALLOCATE.
	 * The GSEG memory करोes not exist until the ALLOCATE completes.
	 */
	sync_core();
	वापस ret;
पूर्ण

पूर्णांक cch_start(काष्ठा gru_context_configuration_handle *cch)
अणु
	cch->opc = CCHOP_START;
	start_inकाष्ठाion(cch);
	वापस रुको_inकाष्ठाion_complete(cch, cchop_start);
पूर्ण

पूर्णांक cch_पूर्णांकerrupt(काष्ठा gru_context_configuration_handle *cch)
अणु
	cch->opc = CCHOP_INTERRUPT;
	start_inकाष्ठाion(cch);
	वापस रुको_inकाष्ठाion_complete(cch, cchop_पूर्णांकerrupt);
पूर्ण

पूर्णांक cch_deallocate(काष्ठा gru_context_configuration_handle *cch)
अणु
	पूर्णांक ret;

	cch->opc = CCHOP_DEALLOCATE;
	start_inकाष्ठाion(cch);
	ret = रुको_inकाष्ठाion_complete(cch, cchop_deallocate);

	/*
	 * Stop speculation पूर्णांकo the GSEG being unmapped by the previous
	 * DEALLOCATE.
	 */
	sync_core();
	वापस ret;
पूर्ण

पूर्णांक cch_पूर्णांकerrupt_sync(काष्ठा gru_context_configuration_handle
				     *cch)
अणु
	cch->opc = CCHOP_INTERRUPT_SYNC;
	start_inकाष्ठाion(cch);
	वापस रुको_inकाष्ठाion_complete(cch, cchop_पूर्णांकerrupt_sync);
पूर्ण

पूर्णांक tgh_invalidate(काष्ठा gru_tlb_global_handle *tgh,
				 अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ vaddrmask,
				 पूर्णांक asid, पूर्णांक pagesize, पूर्णांक global, पूर्णांक n,
				 अचिन्हित लघु ctxbiपंचांगap)
अणु
	tgh->vaddr = vaddr;
	tgh->asid = asid;
	tgh->pagesize = pagesize;
	tgh->n = n;
	tgh->global = global;
	tgh->vaddrmask = vaddrmask;
	tgh->ctxbiपंचांगap = ctxbiपंचांगap;
	tgh->opc = TGHOP_TLBINV;
	start_inकाष्ठाion(tgh);
	वापस रुको_inकाष्ठाion_complete(tgh, tghop_invalidate);
पूर्ण

पूर्णांक tfh_ग_लिखो_only(काष्ठा gru_tlb_fault_handle *tfh,
				  अचिन्हित दीर्घ paddr, पूर्णांक gaa,
				  अचिन्हित दीर्घ vaddr, पूर्णांक asid, पूर्णांक dirty,
				  पूर्णांक pagesize)
अणु
	tfh->fillasid = asid;
	tfh->fillvaddr = vaddr;
	tfh->pfn = paddr >> GRU_PADDR_SHIFT;
	tfh->gaa = gaa;
	tfh->dirty = dirty;
	tfh->pagesize = pagesize;
	tfh->opc = TFHOP_WRITE_ONLY;
	start_inकाष्ठाion(tfh);
	वापस रुको_inकाष्ठाion_complete(tfh, tfhop_ग_लिखो_only);
पूर्ण

व्योम tfh_ग_लिखो_restart(काष्ठा gru_tlb_fault_handle *tfh,
				     अचिन्हित दीर्घ paddr, पूर्णांक gaa,
				     अचिन्हित दीर्घ vaddr, पूर्णांक asid, पूर्णांक dirty,
				     पूर्णांक pagesize)
अणु
	tfh->fillasid = asid;
	tfh->fillvaddr = vaddr;
	tfh->pfn = paddr >> GRU_PADDR_SHIFT;
	tfh->gaa = gaa;
	tfh->dirty = dirty;
	tfh->pagesize = pagesize;
	tfh->opc = TFHOP_WRITE_RESTART;
	start_inकाष्ठाion(tfh);
पूर्ण

व्योम tfh_user_polling_mode(काष्ठा gru_tlb_fault_handle *tfh)
अणु
	tfh->opc = TFHOP_USER_POLLING_MODE;
	start_inकाष्ठाion(tfh);
पूर्ण

व्योम tfh_exception(काष्ठा gru_tlb_fault_handle *tfh)
अणु
	tfh->opc = TFHOP_EXCEPTION;
	start_inकाष्ठाion(tfh);
पूर्ण

