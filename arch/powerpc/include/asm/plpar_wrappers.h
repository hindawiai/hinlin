<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PLPAR_WRAPPERS_H
#घोषणा _ASM_POWERPC_PLPAR_WRAPPERS_H

#अगर_घोषित CONFIG_PPC_PSERIES

#समावेश <linux/माला.स>
#समावेश <linux/irqflags.h>

#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/page.h>

अटल अंतरभूत दीर्घ poll_pending(व्योम)
अणु
	वापस plpar_hcall_norets(H_POLL_PENDING);
पूर्ण

अटल अंतरभूत u8 get_cede_latency_hपूर्णांक(व्योम)
अणु
	वापस get_lppaca()->cede_latency_hपूर्णांक;
पूर्ण

अटल अंतरभूत व्योम set_cede_latency_hपूर्णांक(u8 latency_hपूर्णांक)
अणु
	get_lppaca()->cede_latency_hपूर्णांक = latency_hपूर्णांक;
पूर्ण

अटल अंतरभूत दीर्घ cede_processor(व्योम)
अणु
	/*
	 * We cannot call tracepoपूर्णांकs inside RCU idle regions which
	 * means we must not trace H_CEDE.
	 */
	वापस plpar_hcall_norets_notrace(H_CEDE);
पूर्ण

अटल अंतरभूत दीर्घ extended_cede_processor(अचिन्हित दीर्घ latency_hपूर्णांक)
अणु
	दीर्घ rc;
	u8 old_latency_hपूर्णांक = get_cede_latency_hपूर्णांक();

	set_cede_latency_hपूर्णांक(latency_hपूर्णांक);

	rc = cede_processor();
#अगर_घोषित CONFIG_PPC_IRQ_SOFT_MASK_DEBUG
	/* Ensure that H_CEDE वापसs with IRQs on */
	अगर (WARN_ON(!(mfmsr() & MSR_EE)))
		__hard_irq_enable();
#पूर्ण_अगर

	set_cede_latency_hपूर्णांक(old_latency_hपूर्णांक);

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ vpa_call(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cpu,
		अचिन्हित दीर्घ vpa)
अणु
	flags = flags << H_VPA_FUNC_SHIFT;

	वापस plpar_hcall_norets(H_REGISTER_VPA, flags, cpu, vpa);
पूर्ण

अटल अंतरभूत दीर्घ unरेजिस्टर_vpa(अचिन्हित दीर्घ cpu)
अणु
	वापस vpa_call(H_VPA_DEREG_VPA, cpu, 0);
पूर्ण

अटल अंतरभूत दीर्घ रेजिस्टर_vpa(अचिन्हित दीर्घ cpu, अचिन्हित दीर्घ vpa)
अणु
	वापस vpa_call(H_VPA_REG_VPA, cpu, vpa);
पूर्ण

अटल अंतरभूत दीर्घ unरेजिस्टर_slb_shaकरोw(अचिन्हित दीर्घ cpu)
अणु
	वापस vpa_call(H_VPA_DEREG_SLB, cpu, 0);
पूर्ण

अटल अंतरभूत दीर्घ रेजिस्टर_slb_shaकरोw(अचिन्हित दीर्घ cpu, अचिन्हित दीर्घ vpa)
अणु
	वापस vpa_call(H_VPA_REG_SLB, cpu, vpa);
पूर्ण

अटल अंतरभूत दीर्घ unरेजिस्टर_dtl(अचिन्हित दीर्घ cpu)
अणु
	वापस vpa_call(H_VPA_DEREG_DTL, cpu, 0);
पूर्ण

अटल अंतरभूत दीर्घ रेजिस्टर_dtl(अचिन्हित दीर्घ cpu, अचिन्हित दीर्घ vpa)
अणु
	वापस vpa_call(H_VPA_REG_DTL, cpu, vpa);
पूर्ण

बाह्य व्योम vpa_init(पूर्णांक cpu);

अटल अंतरभूत दीर्घ plpar_pte_enter(अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ hpte_group, अचिन्हित दीर्घ hpte_v,
		अचिन्हित दीर्घ hpte_r, अचिन्हित दीर्घ *slot)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_ENTER, retbuf, flags, hpte_group, hpte_v, hpte_r);

	*slot = retbuf[0];

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ plpar_pte_हटाओ(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
		अचिन्हित दीर्घ avpn, अचिन्हित दीर्घ *old_pteh_ret,
		अचिन्हित दीर्घ *old_ptel_ret)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_REMOVE, retbuf, flags, ptex, avpn);

	*old_pteh_ret = retbuf[0];
	*old_ptel_ret = retbuf[1];

	वापस rc;
पूर्ण

/* plpar_pte_हटाओ_raw can be called in real mode. It calls plpar_hcall_raw */
अटल अंतरभूत दीर्घ plpar_pte_हटाओ_raw(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
		अचिन्हित दीर्घ avpn, अचिन्हित दीर्घ *old_pteh_ret,
		अचिन्हित दीर्घ *old_ptel_ret)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall_raw(H_REMOVE, retbuf, flags, ptex, avpn);

	*old_pteh_ret = retbuf[0];
	*old_ptel_ret = retbuf[1];

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ plpar_pte_पढ़ो(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
		अचिन्हित दीर्घ *old_pteh_ret, अचिन्हित दीर्घ *old_ptel_ret)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_READ, retbuf, flags, ptex);

	*old_pteh_ret = retbuf[0];
	*old_ptel_ret = retbuf[1];

	वापस rc;
पूर्ण

/* plpar_pte_पढ़ो_raw can be called in real mode. It calls plpar_hcall_raw */
अटल अंतरभूत दीर्घ plpar_pte_पढ़ो_raw(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
		अचिन्हित दीर्घ *old_pteh_ret, अचिन्हित दीर्घ *old_ptel_ret)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall_raw(H_READ, retbuf, flags, ptex);

	*old_pteh_ret = retbuf[0];
	*old_ptel_ret = retbuf[1];

	वापस rc;
पूर्ण

/*
 * ptes must be 8*माप(अचिन्हित दीर्घ)
 */
अटल अंतरभूत दीर्घ plpar_pte_पढ़ो_4(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
				    अचिन्हित दीर्घ *ptes)

अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	rc = plpar_hcall9(H_READ, retbuf, flags | H_READ_4, ptex);

	स_नकल(ptes, retbuf, 8*माप(अचिन्हित दीर्घ));

	वापस rc;
पूर्ण

/*
 * plpar_pte_पढ़ो_4_raw can be called in real mode.
 * ptes must be 8*माप(अचिन्हित दीर्घ)
 */
अटल अंतरभूत दीर्घ plpar_pte_पढ़ो_4_raw(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
					अचिन्हित दीर्घ *ptes)

अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	rc = plpar_hcall9_raw(H_READ, retbuf, flags | H_READ_4, ptex);

	स_नकल(ptes, retbuf, 8*माप(अचिन्हित दीर्घ));

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ plpar_pte_protect(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
		अचिन्हित दीर्घ avpn)
अणु
	वापस plpar_hcall_norets(H_PROTECT, flags, ptex, avpn);
पूर्ण

अटल अंतरभूत दीर्घ plpar_resize_hpt_prepare(अचिन्हित दीर्घ flags,
					    अचिन्हित दीर्घ shअगरt)
अणु
	वापस plpar_hcall_norets(H_RESIZE_HPT_PREPARE, flags, shअगरt);
पूर्ण

अटल अंतरभूत दीर्घ plpar_resize_hpt_commit(अचिन्हित दीर्घ flags,
					   अचिन्हित दीर्घ shअगरt)
अणु
	वापस plpar_hcall_norets(H_RESIZE_HPT_COMMIT, flags, shअगरt);
पूर्ण

अटल अंतरभूत दीर्घ plpar_tce_get(अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ *tce_ret)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	rc = plpar_hcall(H_GET_TCE, retbuf, liobn, ioba);

	*tce_ret = retbuf[0];

	वापस rc;
पूर्ण

अटल अंतरभूत दीर्घ plpar_tce_put(अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tceval)
अणु
	वापस plpar_hcall_norets(H_PUT_TCE, liobn, ioba, tceval);
पूर्ण

अटल अंतरभूत दीर्घ plpar_tce_put_indirect(अचिन्हित दीर्घ liobn,
		अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ page, अचिन्हित दीर्घ count)
अणु
	वापस plpar_hcall_norets(H_PUT_TCE_INसूचीECT, liobn, ioba, page, count);
पूर्ण

अटल अंतरभूत दीर्घ plpar_tce_stuff(अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tceval, अचिन्हित दीर्घ count)
अणु
	वापस plpar_hcall_norets(H_STUFF_TCE, liobn, ioba, tceval, count);
पूर्ण

/* Set various resource mode parameters */
अटल अंतरभूत दीर्घ plpar_set_mode(अचिन्हित दीर्घ mflags, अचिन्हित दीर्घ resource,
		अचिन्हित दीर्घ value1, अचिन्हित दीर्घ value2)
अणु
	वापस plpar_hcall_norets(H_SET_MODE, mflags, resource, value1, value2);
पूर्ण

/*
 * Enable relocation on exceptions on this partition
 *
 * Note: this call has a partition wide scope and can take a जबतक to complete.
 * If it वापसs H_LONG_BUSY_* it should be retried periodically until it
 * वापसs H_SUCCESS.
 */
अटल अंतरभूत दीर्घ enable_reloc_on_exceptions(व्योम)
अणु
	/* mflags = 3: Exceptions at 0xC000000000004000 */
	वापस plpar_set_mode(3, H_SET_MODE_RESOURCE_ADDR_TRANS_MODE, 0, 0);
पूर्ण

/*
 * Disable relocation on exceptions on this partition
 *
 * Note: this call has a partition wide scope and can take a जबतक to complete.
 * If it वापसs H_LONG_BUSY_* it should be retried periodically until it
 * वापसs H_SUCCESS.
 */
अटल अंतरभूत दीर्घ disable_reloc_on_exceptions(व्योम) अणु
	वापस plpar_set_mode(0, H_SET_MODE_RESOURCE_ADDR_TRANS_MODE, 0, 0);
पूर्ण

/*
 * Take exceptions in big endian mode on this partition
 *
 * Note: this call has a partition wide scope and can take a जबतक to complete.
 * If it वापसs H_LONG_BUSY_* it should be retried periodically until it
 * वापसs H_SUCCESS.
 */
अटल अंतरभूत दीर्घ enable_big_endian_exceptions(व्योम)
अणु
	/* mflags = 0: big endian exceptions */
	वापस plpar_set_mode(0, H_SET_MODE_RESOURCE_LE, 0, 0);
पूर्ण

/*
 * Take exceptions in little endian mode on this partition
 *
 * Note: this call has a partition wide scope and can take a जबतक to complete.
 * If it वापसs H_LONG_BUSY_* it should be retried periodically until it
 * वापसs H_SUCCESS.
 */
अटल अंतरभूत दीर्घ enable_little_endian_exceptions(व्योम)
अणु
	/* mflags = 1: little endian exceptions */
	वापस plpar_set_mode(1, H_SET_MODE_RESOURCE_LE, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ plpar_set_ciabr(अचिन्हित दीर्घ ciabr)
अणु
	वापस plpar_set_mode(0, H_SET_MODE_RESOURCE_SET_CIABR, ciabr, 0);
पूर्ण

अटल अंतरभूत दीर्घ plpar_set_watchpoपूर्णांक0(अचिन्हित दीर्घ dawr0, अचिन्हित दीर्घ dawrx0)
अणु
	वापस plpar_set_mode(0, H_SET_MODE_RESOURCE_SET_DAWR0, dawr0, dawrx0);
पूर्ण

अटल अंतरभूत दीर्घ plpar_set_watchpoपूर्णांक1(अचिन्हित दीर्घ dawr1, अचिन्हित दीर्घ dawrx1)
अणु
	वापस plpar_set_mode(0, H_SET_MODE_RESOURCE_SET_DAWR1, dawr1, dawrx1);
पूर्ण

अटल अंतरभूत दीर्घ plpar_संकेत_sys_reset(दीर्घ cpu)
अणु
	वापस plpar_hcall_norets(H_SIGNAL_SYS_RESET, cpu);
पूर्ण

अटल अंतरभूत दीर्घ plpar_get_cpu_अक्षरacteristics(काष्ठा h_cpu_अक्षर_result *p)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	rc = plpar_hcall(H_GET_CPU_CHARACTERISTICS, retbuf);
	अगर (rc == H_SUCCESS) अणु
		p->अक्षरacter = retbuf[0];
		p->behaviour = retbuf[1];
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Wrapper to H_RPT_INVALIDATE hcall that handles वापस values appropriately
 *
 * - Returns H_SUCCESS on success
 * - For H_BUSY वापस value, we retry the hcall.
 * - For any other hcall failures, attempt a full flush once beक्रमe
 *   resorting to BUG().
 *
 * Note: This hcall is expected to fail only very rarely. The correct
 * error recovery of समाप्तing the process/guest will be eventually
 * needed.
 */
अटल अंतरभूत दीर्घ pseries_rpt_invalidate(u32 pid, u64 target, u64 type,
					  u64 page_sizes, u64 start, u64 end)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ all;

	जबतक (true) अणु
		rc = plpar_hcall_norets(H_RPT_INVALIDATE, pid, target, type,
					page_sizes, start, end);
		अगर (rc == H_BUSY) अणु
			cpu_relax();
			जारी;
		पूर्ण अन्यथा अगर (rc == H_SUCCESS)
			वापस rc;

		/* Flush request failed, try with a full flush once */
		अगर (type & H_RPTI_TYPE_NESTED)
			all = H_RPTI_TYPE_NESTED | H_RPTI_TYPE_NESTED_ALL;
		अन्यथा
			all = H_RPTI_TYPE_ALL;
retry:
		rc = plpar_hcall_norets(H_RPT_INVALIDATE, pid, target,
					all, page_sizes, 0, -1UL);
		अगर (rc == H_BUSY) अणु
			cpu_relax();
			जाओ retry;
		पूर्ण अन्यथा अगर (rc == H_SUCCESS)
			वापस rc;

		BUG();
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_PPC_PSERIES */

अटल अंतरभूत दीर्घ plpar_set_ciabr(अचिन्हित दीर्घ ciabr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ plpar_pte_पढ़ो_4(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ ptex,
				    अचिन्हित दीर्घ *ptes)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ pseries_rpt_invalidate(u32 pid, u64 target, u64 type,
					  u64 page_sizes, u64 start, u64 end)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

#पूर्ण_अगर /* _ASM_POWERPC_PLPAR_WRAPPERS_H */
