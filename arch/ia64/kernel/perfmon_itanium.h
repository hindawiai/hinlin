<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file contains the Itanium PMU रेजिस्टर description tables
 * and pmc checker.
 *
 * Copyright (C) 2002-2003  Hewlett Packard Co
 *               Stephane Eranian <eranian@hpl.hp.com>
 */
अटल पूर्णांक pfm_ita_pmc_check(काष्ठा task_काष्ठा *task, pfm_context_t *ctx, अचिन्हित पूर्णांक cnum, अचिन्हित दीर्घ *val, काष्ठा pt_regs *regs);

अटल pfm_reg_desc_t pfm_ita_pmc_desc[PMU_MAX_PMCS]=अणु
/* pmc0  */ अणु PFM_REG_CONTROL , 0, 0x1UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc1  */ अणु PFM_REG_CONTROL , 0, 0x0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc2  */ अणु PFM_REG_CONTROL , 0, 0x0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc3  */ अणु PFM_REG_CONTROL , 0, 0x0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc4  */ अणु PFM_REG_COUNTING, 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(4),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc5  */ अणु PFM_REG_COUNTING, 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(5),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc6  */ अणु PFM_REG_COUNTING, 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(6),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc7  */ अणु PFM_REG_COUNTING, 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(7),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc8  */ अणु PFM_REG_CONFIG  , 0, 0xf00000003ffffff8UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc9  */ अणु PFM_REG_CONFIG  , 0, 0xf00000003ffffff8UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc10 */ अणु PFM_REG_MONITOR , 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(0)|RDEP(1),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc11 */ अणु PFM_REG_MONITOR , 6, 0x0000000010000000UL, -1UL, शून्य, pfm_ita_pmc_check, अणुRDEP(2)|RDEP(3)|RDEP(17),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc12 */ अणु PFM_REG_MONITOR , 6, 0x0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmc13 */ अणु PFM_REG_CONFIG  , 0, 0x0003ffff00000001UL, -1UL, शून्य, pfm_ita_pmc_check, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणु0UL,0UL, 0UL, 0ULपूर्णपूर्ण,
	    अणु PFM_REG_END     , 0, 0x0UL, -1UL, शून्य, शून्य, अणु0,पूर्ण, अणु0,पूर्णपूर्ण, /* end marker */
पूर्ण;

अटल pfm_reg_desc_t pfm_ita_pmd_desc[PMU_MAX_PMDS]=अणु
/* pmd0  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(1),0UL, 0UL, 0ULपूर्ण, अणुRDEP(10),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd1  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(0),0UL, 0UL, 0ULपूर्ण, अणुRDEP(10),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd2  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(3)|RDEP(17),0UL, 0UL, 0ULपूर्ण, अणुRDEP(11),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd3  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(2)|RDEP(17),0UL, 0UL, 0ULपूर्ण, अणुRDEP(11),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd4  */ अणु PFM_REG_COUNTING, 0, 0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणुRDEP(4),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd5  */ अणु PFM_REG_COUNTING, 0, 0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणुRDEP(5),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd6  */ अणु PFM_REG_COUNTING, 0, 0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणुRDEP(6),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd7  */ अणु PFM_REG_COUNTING, 0, 0UL, -1UL, शून्य, शून्य, अणु0UL,0UL, 0UL, 0ULपूर्ण, अणुRDEP(7),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd8  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd9  */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd10 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd11 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd12 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(13)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd13 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(14)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd14 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(15)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd15 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(16),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd16 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(8)|RDEP(9)|RDEP(10)|RDEP(11)|RDEP(12)|RDEP(13)|RDEP(14)|RDEP(15),0UL, 0UL, 0ULपूर्ण, अणुRDEP(12),0UL, 0UL, 0ULपूर्णपूर्ण,
/* pmd17 */ अणु PFM_REG_BUFFER  , 0, 0UL, -1UL, शून्य, शून्य, अणुRDEP(2)|RDEP(3),0UL, 0UL, 0ULपूर्ण, अणुRDEP(11),0UL, 0UL, 0ULपूर्णपूर्ण,
	    अणु PFM_REG_END     , 0, 0UL, -1UL, शून्य, शून्य, अणु0,पूर्ण, अणु0,पूर्णपूर्ण, /* end marker */
पूर्ण;

अटल पूर्णांक
pfm_ita_pmc_check(काष्ठा task_काष्ठा *task, pfm_context_t *ctx, अचिन्हित पूर्णांक cnum, अचिन्हित दीर्घ *val, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;
	पूर्णांक is_loaded;

	/* sanitfy check */
	अगर (ctx == शून्य) वापस -EINVAL;

	is_loaded = ctx->ctx_state == PFM_CTX_LOADED || ctx->ctx_state == PFM_CTX_MASKED;

	/*
	 * we must clear the (inकाष्ठाion) debug रेजिस्टरs अगर pmc13.ta bit is cleared
	 * beक्रमe they are written (fl_using_dbreg==0) to aव्योम picking up stale inक्रमmation.
	 */
	अगर (cnum == 13 && is_loaded && ((*val & 0x1) == 0UL) && ctx->ctx_fl_using_dbreg == 0) अणु

		DPRINT(("pmc[%d]=0x%lx has active pmc13.ta cleared, clearing ibr\n", cnum, *val));

		/* करोn't mix debug with perfmon */
		अगर (task && (task->thपढ़ो.flags & IA64_THREAD_DBG_VALID) != 0) वापस -EINVAL;

		/*
		 * a count of 0 will mark the debug रेजिस्टरs as in use and also
		 * ensure that they are properly cleared.
		 */
		ret = pfm_ग_लिखो_ibr_dbr(1, ctx, शून्य, 0, regs);
		अगर (ret) वापस ret;
	पूर्ण

	/*
	 * we must clear the (data) debug रेजिस्टरs अगर pmc11.pt bit is cleared
	 * beक्रमe they are written (fl_using_dbreg==0) to aव्योम picking up stale inक्रमmation.
	 */
	अगर (cnum == 11 && is_loaded && ((*val >> 28)& 0x1) == 0 && ctx->ctx_fl_using_dbreg == 0) अणु

		DPRINT(("pmc[%d]=0x%lx has active pmc11.pt cleared, clearing dbr\n", cnum, *val));

		/* करोn't mix debug with perfmon */
		अगर (task && (task->thपढ़ो.flags & IA64_THREAD_DBG_VALID) != 0) वापस -EINVAL;

		/*
		 * a count of 0 will mark the debug रेजिस्टरs as in use and also
		 * ensure that they are properly cleared.
		 */
		ret = pfm_ग_लिखो_ibr_dbr(0, ctx, शून्य, 0, regs);
		अगर (ret) वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * impl_pmcs, impl_pmds are computed at runसमय to minimize errors!
 */
अटल pmu_config_t pmu_conf_ita=अणु
	.pmu_name      = "Itanium",
	.pmu_family    = 0x7,
	.ovfl_val      = (1UL << 32) - 1,
	.pmd_desc      = pfm_ita_pmd_desc,
	.pmc_desc      = pfm_ita_pmc_desc,
	.num_ibrs      = 8,
	.num_dbrs      = 8,
	.use_rr_dbregs = 1, /* debug रेजिस्टर are use क्रम range retrictions */
पूर्ण;


