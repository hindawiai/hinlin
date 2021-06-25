<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <misc/cxl-base.h>

#समावेश "cxl.h"
#समावेश "trace.h"

अटल पूर्णांक afu_control(काष्ठा cxl_afu *afu, u64 command, u64 clear,
		       u64 result, u64 mask, bool enabled)
अणु
	u64 AFU_Cntl;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);
	पूर्णांक rc = 0;

	spin_lock(&afu->afu_cntl_lock);
	pr_devel("AFU command starting: %llx\n", command);

	trace_cxl_afu_ctrl(afu, command);

	AFU_Cntl = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	cxl_p2n_ग_लिखो(afu, CXL_AFU_Cntl_An, (AFU_Cntl & ~clear) | command);

	AFU_Cntl = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	जबतक ((AFU_Cntl & mask) != result) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&afu->dev, "WARNING: AFU control timed out!\n");
			rc = -EBUSY;
			जाओ out;
		पूर्ण

		अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
			afu->enabled = enabled;
			rc = -EIO;
			जाओ out;
		पूर्ण

		pr_devel_ratelimited("AFU control... (0x%016llx)\n",
				     AFU_Cntl | command);
		cpu_relax();
		AFU_Cntl = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	पूर्ण

	अगर (AFU_Cntl & CXL_AFU_Cntl_An_RA) अणु
		/*
		 * Workaround क्रम a bug in the XSL used in the Mellanox CX4
		 * that fails to clear the RA bit after an AFU reset,
		 * preventing subsequent AFU resets from working.
		 */
		cxl_p2n_ग_लिखो(afu, CXL_AFU_Cntl_An, AFU_Cntl & ~CXL_AFU_Cntl_An_RA);
	पूर्ण

	pr_devel("AFU command complete: %llx\n", command);
	afu->enabled = enabled;
out:
	trace_cxl_afu_ctrl_करोne(afu, command, rc);
	spin_unlock(&afu->afu_cntl_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक afu_enable(काष्ठा cxl_afu *afu)
अणु
	pr_devel("AFU enable request\n");

	वापस afu_control(afu, CXL_AFU_Cntl_An_E, 0,
			   CXL_AFU_Cntl_An_ES_Enabled,
			   CXL_AFU_Cntl_An_ES_MASK, true);
पूर्ण

पूर्णांक cxl_afu_disable(काष्ठा cxl_afu *afu)
अणु
	pr_devel("AFU disable request\n");

	वापस afu_control(afu, 0, CXL_AFU_Cntl_An_E,
			   CXL_AFU_Cntl_An_ES_Disabled,
			   CXL_AFU_Cntl_An_ES_MASK, false);
पूर्ण

/* This will disable as well as reset */
अटल पूर्णांक native_afu_reset(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक rc;
	u64 serr;

	pr_devel("AFU reset request\n");

	rc = afu_control(afu, CXL_AFU_Cntl_An_RA, 0,
			   CXL_AFU_Cntl_An_RS_Complete | CXL_AFU_Cntl_An_ES_Disabled,
			   CXL_AFU_Cntl_An_RS_MASK | CXL_AFU_Cntl_An_ES_MASK,
			   false);

	/*
	 * Re-enable any masked पूर्णांकerrupts when the AFU is not
	 * activated to aव्योम side effects after attaching a process
	 * in dedicated mode.
	 */
	अगर (afu->current_mode == 0) अणु
		serr = cxl_p1n_पढ़ो(afu, CXL_PSL_SERR_An);
		serr &= ~CXL_PSL_SERR_An_IRQ_MASKS;
		cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, serr);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक native_afu_check_and_enable(काष्ठा cxl_afu *afu)
अणु
	अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
		WARN(1, "Refusing to enable afu while link down!\n");
		वापस -EIO;
	पूर्ण
	अगर (afu->enabled)
		वापस 0;
	वापस afu_enable(afu);
पूर्ण

पूर्णांक cxl_psl_purge(काष्ठा cxl_afu *afu)
अणु
	u64 PSL_CNTL = cxl_p1n_पढ़ो(afu, CXL_PSL_SCNTL_An);
	u64 AFU_Cntl = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	u64 dsisr, dar;
	u64 start, end;
	u64 trans_fault = 0x0ULL;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);
	पूर्णांक rc = 0;

	trace_cxl_psl_ctrl(afu, CXL_PSL_SCNTL_An_Pc);

	pr_devel("PSL purge request\n");

	अगर (cxl_is_घातer8())
		trans_fault = CXL_PSL_DSISR_TRANS;
	अगर (cxl_is_घातer9())
		trans_fault = CXL_PSL9_DSISR_An_TF;

	अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
		dev_warn(&afu->dev, "PSL Purge called with link down, ignoring\n");
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर ((AFU_Cntl & CXL_AFU_Cntl_An_ES_MASK) != CXL_AFU_Cntl_An_ES_Disabled) अणु
		WARN(1, "psl_purge request while AFU not disabled!\n");
		cxl_afu_disable(afu);
	पूर्ण

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SCNTL_An,
		       PSL_CNTL | CXL_PSL_SCNTL_An_Pc);
	start = local_घड़ी();
	PSL_CNTL = cxl_p1n_पढ़ो(afu, CXL_PSL_SCNTL_An);
	जबतक ((PSL_CNTL &  CXL_PSL_SCNTL_An_Ps_MASK)
			== CXL_PSL_SCNTL_An_Ps_Pending) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&afu->dev, "WARNING: PSL Purge timed out!\n");
			rc = -EBUSY;
			जाओ out;
		पूर्ण
		अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
			rc = -EIO;
			जाओ out;
		पूर्ण

		dsisr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
		pr_devel_ratelimited("PSL purging... PSL_CNTL: 0x%016llx  PSL_DSISR: 0x%016llx\n",
				     PSL_CNTL, dsisr);

		अगर (dsisr & trans_fault) अणु
			dar = cxl_p2n_पढ़ो(afu, CXL_PSL_DAR_An);
			dev_notice(&afu->dev, "PSL purge terminating pending translation, DSISR: 0x%016llx, DAR: 0x%016llx\n",
				   dsisr, dar);
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_AE);
		पूर्ण अन्यथा अगर (dsisr) अणु
			dev_notice(&afu->dev, "PSL purge acknowledging pending non-translation fault, DSISR: 0x%016llx\n",
				   dsisr);
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_A);
		पूर्ण अन्यथा अणु
			cpu_relax();
		पूर्ण
		PSL_CNTL = cxl_p1n_पढ़ो(afu, CXL_PSL_SCNTL_An);
	पूर्ण
	end = local_घड़ी();
	pr_devel("PSL purged in %lld ns\n", end - start);

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SCNTL_An,
		       PSL_CNTL & ~CXL_PSL_SCNTL_An_Pc);
out:
	trace_cxl_psl_ctrl_करोne(afu, CXL_PSL_SCNTL_An_Pc, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक spa_max_procs(पूर्णांक spa_size)
अणु
	/*
	 * From the CAIA:
	 *    end_of_SPA_area = SPA_Base + ((n+4) * 128) + (( ((n*8) + 127) >> 7) * 128) + 255
	 * Most of that junk is really just an overly-complicated way of saying
	 * the last 256 bytes are __aligned(128), so it's really:
	 *    end_of_SPA_area = end_of_PSL_queue_area + __aligned(128) 255
	 * and
	 *    end_of_PSL_queue_area = SPA_Base + ((n+4) * 128) + (n*8) - 1
	 * so
	 *    माप(SPA) = ((n+4) * 128) + (n*8) + __aligned(128) 256
	 * Ignore the alignment (which is safe in this हाल as दीर्घ as we are
	 * careful with our rounding) and solve क्रम n:
	 */
	वापस ((spa_size / 8) - 96) / 17;
पूर्ण

अटल पूर्णांक cxl_alloc_spa(काष्ठा cxl_afu *afu, पूर्णांक mode)
अणु
	अचिन्हित spa_size;

	/* Work out how many pages to allocate */
	afu->native->spa_order = -1;
	करो अणु
		afu->native->spa_order++;
		spa_size = (1 << afu->native->spa_order) * PAGE_SIZE;

		अगर (spa_size > 0x100000) अणु
			dev_warn(&afu->dev, "num_of_processes too large for the SPA, limiting to %i (0x%x)\n",
					afu->native->spa_max_procs, afu->native->spa_size);
			अगर (mode != CXL_MODE_DEDICATED)
				afu->num_procs = afu->native->spa_max_procs;
			अवरोध;
		पूर्ण

		afu->native->spa_size = spa_size;
		afu->native->spa_max_procs = spa_max_procs(afu->native->spa_size);
	पूर्ण जबतक (afu->native->spa_max_procs < afu->num_procs);

	अगर (!(afu->native->spa = (काष्ठा cxl_process_element *)
	      __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, afu->native->spa_order))) अणु
		pr_err("cxl_alloc_spa: Unable to allocate scheduled process area\n");
		वापस -ENOMEM;
	पूर्ण
	pr_devel("spa pages: %i afu->spa_max_procs: %i   afu->num_procs: %i\n",
		 1<<afu->native->spa_order, afu->native->spa_max_procs, afu->num_procs);

	वापस 0;
पूर्ण

अटल व्योम attach_spa(काष्ठा cxl_afu *afu)
अणु
	u64 spap;

	afu->native->sw_command_status = (__be64 *)((अक्षर *)afu->native->spa +
					    ((afu->native->spa_max_procs + 3) * 128));

	spap = virt_to_phys(afu->native->spa) & CXL_PSL_SPAP_Addr;
	spap |= ((afu->native->spa_size >> (12 - CXL_PSL_SPAP_Size_Shअगरt)) - 1) & CXL_PSL_SPAP_Size;
	spap |= CXL_PSL_SPAP_V;
	pr_devel("cxl: SPA allocated at 0x%p. Max processes: %i, sw_command_status: 0x%p CXL_PSL_SPAP_An=0x%016llx\n",
		afu->native->spa, afu->native->spa_max_procs,
		afu->native->sw_command_status, spap);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPAP_An, spap);
पूर्ण

अटल अंतरभूत व्योम detach_spa(काष्ठा cxl_afu *afu)
अणु
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPAP_An, 0);
पूर्ण

व्योम cxl_release_spa(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->native->spa) अणु
		मुक्त_pages((अचिन्हित दीर्घ) afu->native->spa,
			afu->native->spa_order);
		afu->native->spa = शून्य;
	पूर्ण
पूर्ण

/*
 * Invalidation of all ERAT entries is no दीर्घer required by CAIA2. Use
 * only क्रम debug.
 */
पूर्णांक cxl_invalidate_all_psl9(काष्ठा cxl *adapter)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);
	u64 ierat;

	pr_devel("CXL adapter - invalidation of all ERAT entries\n");

	/* Invalidates all ERAT entries क्रम Radix or HPT */
	ierat = CXL_XSL9_IERAT_IALL;
	अगर (radix_enabled())
		ierat |= CXL_XSL9_IERAT_INVR;
	cxl_p1_ग_लिखो(adapter, CXL_XSL9_IERAT, ierat);

	जबतक (cxl_p1_पढ़ो(adapter, CXL_XSL9_IERAT) & CXL_XSL9_IERAT_IINPROG) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&adapter->dev,
			"WARNING: CXL adapter invalidation of all ERAT entries timed out!\n");
			वापस -EBUSY;
		पूर्ण
		अगर (!cxl_ops->link_ok(adapter, शून्य))
			वापस -EIO;
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cxl_invalidate_all_psl8(काष्ठा cxl *adapter)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);

	pr_devel("CXL adapter wide TLBIA & SLBIA\n");

	cxl_p1_ग_लिखो(adapter, CXL_PSL_AFUSEL, CXL_PSL_AFUSEL_A);

	cxl_p1_ग_लिखो(adapter, CXL_PSL_TLBIA, CXL_TLB_SLB_IQ_ALL);
	जबतक (cxl_p1_पढ़ो(adapter, CXL_PSL_TLBIA) & CXL_TLB_SLB_P) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&adapter->dev, "WARNING: CXL adapter wide TLBIA timed out!\n");
			वापस -EBUSY;
		पूर्ण
		अगर (!cxl_ops->link_ok(adapter, शून्य))
			वापस -EIO;
		cpu_relax();
	पूर्ण

	cxl_p1_ग_लिखो(adapter, CXL_PSL_SLBIA, CXL_TLB_SLB_IQ_ALL);
	जबतक (cxl_p1_पढ़ो(adapter, CXL_PSL_SLBIA) & CXL_TLB_SLB_P) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&adapter->dev, "WARNING: CXL adapter wide SLBIA timed out!\n");
			वापस -EBUSY;
		पूर्ण
		अगर (!cxl_ops->link_ok(adapter, शून्य))
			वापस -EIO;
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cxl_data_cache_flush(काष्ठा cxl *adapter)
अणु
	u64 reg;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);

	/*
	 * Do a datacache flush only अगर datacache is available.
	 * In हाल of PSL9D datacache असलent hence flush operation.
	 * would समयout.
	 */
	अगर (adapter->native->no_data_cache) अणु
		pr_devel("No PSL data cache. Ignoring cache flush req.\n");
		वापस 0;
	पूर्ण

	pr_devel("Flushing data cache\n");
	reg = cxl_p1_पढ़ो(adapter, CXL_PSL_Control);
	reg |= CXL_PSL_Control_Fr;
	cxl_p1_ग_लिखो(adapter, CXL_PSL_Control, reg);

	reg = cxl_p1_पढ़ो(adapter, CXL_PSL_Control);
	जबतक ((reg & CXL_PSL_Control_Fs_MASK) != CXL_PSL_Control_Fs_Complete) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&adapter->dev, "WARNING: cache flush timed out!\n");
			वापस -EBUSY;
		पूर्ण

		अगर (!cxl_ops->link_ok(adapter, शून्य)) अणु
			dev_warn(&adapter->dev, "WARNING: link down when flushing cache\n");
			वापस -EIO;
		पूर्ण
		cpu_relax();
		reg = cxl_p1_पढ़ो(adapter, CXL_PSL_Control);
	पूर्ण

	reg &= ~CXL_PSL_Control_Fr;
	cxl_p1_ग_लिखो(adapter, CXL_PSL_Control, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक cxl_ग_लिखो_sstp(काष्ठा cxl_afu *afu, u64 sstp0, u64 sstp1)
अणु
	पूर्णांक rc;

	/* 1. Disable SSTP by writing 0 to SSTP1[V] */
	cxl_p2n_ग_लिखो(afu, CXL_SSTP1_An, 0);

	/* 2. Invalidate all SLB entries */
	अगर ((rc = cxl_afu_slbia(afu)))
		वापस rc;

	/* 3. Set SSTP0_An */
	cxl_p2n_ग_लिखो(afu, CXL_SSTP0_An, sstp0);

	/* 4. Set SSTP1_An */
	cxl_p2n_ग_लिखो(afu, CXL_SSTP1_An, sstp1);

	वापस 0;
पूर्ण

/* Using per slice version may improve perक्रमmance here. (ie. SLBIA_An) */
अटल व्योम slb_invalid(काष्ठा cxl_context *ctx)
अणु
	काष्ठा cxl *adapter = ctx->afu->adapter;
	u64 slbia;

	WARN_ON(!mutex_is_locked(&ctx->afu->native->spa_mutex));

	cxl_p1_ग_लिखो(adapter, CXL_PSL_LBISEL,
			((u64)be32_to_cpu(ctx->elem->common.pid) << 32) |
			be32_to_cpu(ctx->elem->lpid));
	cxl_p1_ग_लिखो(adapter, CXL_PSL_SLBIA, CXL_TLB_SLB_IQ_LPIDPID);

	जबतक (1) अणु
		अगर (!cxl_ops->link_ok(adapter, शून्य))
			अवरोध;
		slbia = cxl_p1_पढ़ो(adapter, CXL_PSL_SLBIA);
		अगर (!(slbia & CXL_TLB_SLB_P))
			अवरोध;
		cpu_relax();
	पूर्ण
पूर्ण

अटल पूर्णांक करो_process_element_cmd(काष्ठा cxl_context *ctx,
				  u64 cmd, u64 pe_state)
अणु
	u64 state;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);
	पूर्णांक rc = 0;

	trace_cxl_llcmd(ctx, cmd);

	WARN_ON(!ctx->afu->enabled);

	ctx->elem->software_state = cpu_to_be32(pe_state);
	smp_wmb();
	*(ctx->afu->native->sw_command_status) = cpu_to_be64(cmd | 0 | ctx->pe);
	smp_mb();
	cxl_p1n_ग_लिखो(ctx->afu, CXL_PSL_LLCMD_An, cmd | ctx->pe);
	जबतक (1) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&ctx->afu->dev, "WARNING: Process Element Command timed out!\n");
			rc = -EBUSY;
			जाओ out;
		पूर्ण
		अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu)) अणु
			dev_warn(&ctx->afu->dev, "WARNING: Device link down, aborting Process Element Command!\n");
			rc = -EIO;
			जाओ out;
		पूर्ण
		state = be64_to_cpup(ctx->afu->native->sw_command_status);
		अगर (state == ~0ULL) अणु
			pr_err("cxl: Error adding process element to AFU\n");
			rc = -1;
			जाओ out;
		पूर्ण
		अगर ((state & (CXL_SPA_SW_CMD_MASK | CXL_SPA_SW_STATE_MASK  | CXL_SPA_SW_LINK_MASK)) ==
		    (cmd | (cmd >> 16) | ctx->pe))
			अवरोध;
		/*
		 * The command won't finish in the PSL अगर there are
		 * outstanding DSIs.  Hence we need to yield here in
		 * हाल there are outstanding DSIs that we need to
		 * service.  Tuning possiblity: we could रुको क्रम a
		 * जबतक beक्रमe sched
		 */
		schedule();

	पूर्ण
out:
	trace_cxl_llcmd_करोne(ctx, cmd, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक add_process_element(काष्ठा cxl_context *ctx)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&ctx->afu->native->spa_mutex);
	pr_devel("%s Adding pe: %i started\n", __func__, ctx->pe);
	अगर (!(rc = करो_process_element_cmd(ctx, CXL_SPA_SW_CMD_ADD, CXL_PE_SOFTWARE_STATE_V)))
		ctx->pe_inserted = true;
	pr_devel("%s Adding pe: %i finished\n", __func__, ctx->pe);
	mutex_unlock(&ctx->afu->native->spa_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक terminate_process_element(काष्ठा cxl_context *ctx)
अणु
	पूर्णांक rc = 0;

	/* fast path terminate अगर it's alपढ़ोy invalid */
	अगर (!(ctx->elem->software_state & cpu_to_be32(CXL_PE_SOFTWARE_STATE_V)))
		वापस rc;

	mutex_lock(&ctx->afu->native->spa_mutex);
	pr_devel("%s Terminate pe: %i started\n", __func__, ctx->pe);
	/* We could be asked to terminate when the hw is करोwn. That
	 * should always succeed: it's not running अगर the hw has gone
	 * away and is being reset.
	 */
	अगर (cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		rc = करो_process_element_cmd(ctx, CXL_SPA_SW_CMD_TERMINATE,
					    CXL_PE_SOFTWARE_STATE_V | CXL_PE_SOFTWARE_STATE_T);
	ctx->elem->software_state = 0;	/* Remove Valid bit */
	pr_devel("%s Terminate pe: %i finished\n", __func__, ctx->pe);
	mutex_unlock(&ctx->afu->native->spa_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक हटाओ_process_element(काष्ठा cxl_context *ctx)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&ctx->afu->native->spa_mutex);
	pr_devel("%s Remove pe: %i started\n", __func__, ctx->pe);

	/* We could be asked to हटाओ when the hw is करोwn. Again, अगर
	 * the hw is करोwn, the PE is gone, so we succeed.
	 */
	अगर (cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		rc = करो_process_element_cmd(ctx, CXL_SPA_SW_CMD_REMOVE, 0);

	अगर (!rc)
		ctx->pe_inserted = false;
	अगर (cxl_is_घातer8())
		slb_invalid(ctx);
	pr_devel("%s Remove pe: %i finished\n", __func__, ctx->pe);
	mutex_unlock(&ctx->afu->native->spa_mutex);

	वापस rc;
पूर्ण

व्योम cxl_assign_psn_space(काष्ठा cxl_context *ctx)
अणु
	अगर (!ctx->afu->pp_size || ctx->master) अणु
		ctx->psn_phys = ctx->afu->psn_phys;
		ctx->psn_size = ctx->afu->adapter->ps_size;
	पूर्ण अन्यथा अणु
		ctx->psn_phys = ctx->afu->psn_phys +
			(ctx->afu->native->pp_offset + ctx->afu->pp_size * ctx->pe);
		ctx->psn_size = ctx->afu->pp_size;
	पूर्ण
पूर्ण

अटल पूर्णांक activate_afu_directed(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक rc;

	dev_info(&afu->dev, "Activating AFU directed mode\n");

	afu->num_procs = afu->max_procs_भवised;
	अगर (afu->native->spa == शून्य) अणु
		अगर (cxl_alloc_spa(afu, CXL_MODE_सूचीECTED))
			वापस -ENOMEM;
	पूर्ण
	attach_spa(afu);

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SCNTL_An, CXL_PSL_SCNTL_An_PM_AFU);
	अगर (cxl_is_घातer8())
		cxl_p1n_ग_लिखो(afu, CXL_PSL_AMOR_An, 0xFFFFFFFFFFFFFFFFULL);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_ID_An, CXL_PSL_ID_An_F | CXL_PSL_ID_An_L);

	afu->current_mode = CXL_MODE_सूचीECTED;

	अगर ((rc = cxl_अक्षरdev_m_afu_add(afu)))
		वापस rc;

	अगर ((rc = cxl_sysfs_afu_m_add(afu)))
		जाओ err;

	अगर ((rc = cxl_अक्षरdev_s_afu_add(afu)))
		जाओ err1;

	वापस 0;
err1:
	cxl_sysfs_afu_m_हटाओ(afu);
err:
	cxl_अक्षरdev_afu_हटाओ(afu);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
#घोषणा set_endian(sr) ((sr) |= CXL_PSL_SR_An_LE)
#अन्यथा
#घोषणा set_endian(sr) ((sr) &= ~(CXL_PSL_SR_An_LE))
#पूर्ण_अगर

u64 cxl_calculate_sr(bool master, bool kernel, bool real_mode, bool p9)
अणु
	u64 sr = 0;

	set_endian(sr);
	अगर (master)
		sr |= CXL_PSL_SR_An_MP;
	अगर (mfspr(SPRN_LPCR) & LPCR_TC)
		sr |= CXL_PSL_SR_An_TC;

	अगर (kernel) अणु
		अगर (!real_mode)
			sr |= CXL_PSL_SR_An_R;
		sr |= (mfmsr() & MSR_SF) | CXL_PSL_SR_An_HV;
	पूर्ण अन्यथा अणु
		sr |= CXL_PSL_SR_An_PR | CXL_PSL_SR_An_R;
		अगर (radix_enabled())
			sr |= CXL_PSL_SR_An_HV;
		अन्यथा
			sr &= ~(CXL_PSL_SR_An_HV);
		अगर (!test_tsk_thपढ़ो_flag(current, TIF_32BIT))
			sr |= CXL_PSL_SR_An_SF;
	पूर्ण
	अगर (p9) अणु
		अगर (radix_enabled())
			sr |= CXL_PSL_SR_An_XLAT_ror;
		अन्यथा
			sr |= CXL_PSL_SR_An_XLAT_hpt;
	पूर्ण
	वापस sr;
पूर्ण

अटल u64 calculate_sr(काष्ठा cxl_context *ctx)
अणु
	वापस cxl_calculate_sr(ctx->master, ctx->kernel, false,
				cxl_is_घातer9());
पूर्ण

अटल व्योम update_ivtes_directed(काष्ठा cxl_context *ctx)
अणु
	bool need_update = (ctx->status == STARTED);
	पूर्णांक r;

	अगर (need_update) अणु
		WARN_ON(terminate_process_element(ctx));
		WARN_ON(हटाओ_process_element(ctx));
	पूर्ण

	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		ctx->elem->ivte_offsets[r] = cpu_to_be16(ctx->irqs.offset[r]);
		ctx->elem->ivte_ranges[r] = cpu_to_be16(ctx->irqs.range[r]);
	पूर्ण

	/*
	 * Theoretically we could use the update llcmd, instead of a
	 * terminate/हटाओ/add (or अगर an atomic update was required we could
	 * करो a suspend/update/resume), however it seems there might be issues
	 * with the update llcmd on some cards (including those using an XSL on
	 * an ASIC) so क्रम now it's safest to go with the commands that are
	 * known to work. In the future अगर we come across a situation where the
	 * card may be perक्रमming transactions using the same PE जबतक we are
	 * करोing this update we might need to revisit this.
	 */
	अगर (need_update)
		WARN_ON(add_process_element(ctx));
पूर्ण

अटल पूर्णांक process_element_entry_psl9(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	u32 pid;
	पूर्णांक rc;

	cxl_assign_psn_space(ctx);

	ctx->elem->ctxसमय = 0; /* disable */
	ctx->elem->lpid = cpu_to_be32(mfspr(SPRN_LPID));
	ctx->elem->haurp = 0; /* disable */

	अगर (ctx->kernel)
		pid = 0;
	अन्यथा अणु
		अगर (ctx->mm == शून्य) अणु
			pr_devel("%s: unable to get mm for pe=%d pid=%i\n",
				__func__, ctx->pe, pid_nr(ctx->pid));
			वापस -EINVAL;
		पूर्ण
		pid = ctx->mm->context.id;
	पूर्ण

	/* Assign a unique TIDR (thपढ़ो id) क्रम the current thपढ़ो */
	अगर (!(ctx->tidr) && (ctx->assign_tidr)) अणु
		rc = set_thपढ़ो_tidr(current);
		अगर (rc)
			वापस -ENODEV;
		ctx->tidr = current->thपढ़ो.tidr;
		pr_devel("%s: current tidr: %d\n", __func__, ctx->tidr);
	पूर्ण

	ctx->elem->common.tid = cpu_to_be32(ctx->tidr);
	ctx->elem->common.pid = cpu_to_be32(pid);

	ctx->elem->sr = cpu_to_be64(calculate_sr(ctx));

	ctx->elem->common.csrp = 0; /* disable */

	cxl_prefault(ctx, wed);

	/*
	 * Ensure we have the multiplexed PSL पूर्णांकerrupt set up to take faults
	 * क्रम kernel contexts that may not have allocated any AFU IRQs at all:
	 */
	अगर (ctx->irqs.range[0] == 0) अणु
		ctx->irqs.offset[0] = ctx->afu->native->psl_hwirq;
		ctx->irqs.range[0] = 1;
	पूर्ण

	ctx->elem->common.amr = cpu_to_be64(amr);
	ctx->elem->common.wed = cpu_to_be64(wed);

	वापस 0;
पूर्ण

पूर्णांक cxl_attach_afu_directed_psl9(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	पूर्णांक result;

	/* fill the process element entry */
	result = process_element_entry_psl9(ctx, wed, amr);
	अगर (result)
		वापस result;

	update_ivtes_directed(ctx);

	/* first guy needs to enable */
	result = cxl_ops->afu_check_and_enable(ctx->afu);
	अगर (result)
		वापस result;

	वापस add_process_element(ctx);
पूर्ण

पूर्णांक cxl_attach_afu_directed_psl8(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	u32 pid;
	पूर्णांक result;

	cxl_assign_psn_space(ctx);

	ctx->elem->ctxसमय = 0; /* disable */
	ctx->elem->lpid = cpu_to_be32(mfspr(SPRN_LPID));
	ctx->elem->haurp = 0; /* disable */
	ctx->elem->u.sdr = cpu_to_be64(mfspr(SPRN_SDR1));

	pid = current->pid;
	अगर (ctx->kernel)
		pid = 0;
	ctx->elem->common.tid = 0;
	ctx->elem->common.pid = cpu_to_be32(pid);

	ctx->elem->sr = cpu_to_be64(calculate_sr(ctx));

	ctx->elem->common.csrp = 0; /* disable */
	ctx->elem->common.u.psl8.aurp0 = 0; /* disable */
	ctx->elem->common.u.psl8.aurp1 = 0; /* disable */

	cxl_prefault(ctx, wed);

	ctx->elem->common.u.psl8.sstp0 = cpu_to_be64(ctx->sstp0);
	ctx->elem->common.u.psl8.sstp1 = cpu_to_be64(ctx->sstp1);

	/*
	 * Ensure we have the multiplexed PSL पूर्णांकerrupt set up to take faults
	 * क्रम kernel contexts that may not have allocated any AFU IRQs at all:
	 */
	अगर (ctx->irqs.range[0] == 0) अणु
		ctx->irqs.offset[0] = ctx->afu->native->psl_hwirq;
		ctx->irqs.range[0] = 1;
	पूर्ण

	update_ivtes_directed(ctx);

	ctx->elem->common.amr = cpu_to_be64(amr);
	ctx->elem->common.wed = cpu_to_be64(wed);

	/* first guy needs to enable */
	अगर ((result = cxl_ops->afu_check_and_enable(ctx->afu)))
		वापस result;

	वापस add_process_element(ctx);
पूर्ण

अटल पूर्णांक deactivate_afu_directed(काष्ठा cxl_afu *afu)
अणु
	dev_info(&afu->dev, "Deactivating AFU directed mode\n");

	afu->current_mode = 0;
	afu->num_procs = 0;

	cxl_sysfs_afu_m_हटाओ(afu);
	cxl_अक्षरdev_afu_हटाओ(afu);

	/*
	 * The CAIA section 2.2.1 indicates that the procedure क्रम starting and
	 * stopping an AFU in AFU directed mode is AFU specअगरic, which is not
	 * ideal since this code is generic and with one exception has no
	 * knowledge of the AFU. This is in contrast to the procedure क्रम
	 * disabling a dedicated process AFU, which is करोcumented to just
	 * require a reset. The architecture करोes indicate that both an AFU
	 * reset and an AFU disable should result in the AFU being disabled and
	 * we करो both followed by a PSL purge क्रम safety.
	 *
	 * Notably we used to have some issues with the disable sequence on PSL
	 * cards, which is why we ended up using this heavy weight procedure in
	 * the first place, however a bug was discovered that had rendered the
	 * disable operation ineffective, so it is conceivable that was the
	 * sole explanation क्रम those dअगरficulties. Careful regression testing
	 * is recommended अगर anyone attempts to हटाओ or reorder these
	 * operations.
	 *
	 * The XSL on the Mellanox CX4 behaves a little dअगरferently from the
	 * PSL based cards and will समय out an AFU reset अगर the AFU is still
	 * enabled. That card is special in that we करो have a means to identअगरy
	 * it from this code, so in that हाल we skip the reset and just use a
	 * disable/purge to aव्योम the समयout and corresponding noise in the
	 * kernel log.
	 */
	अगर (afu->adapter->native->sl_ops->needs_reset_beक्रमe_disable)
		cxl_ops->afu_reset(afu);
	cxl_afu_disable(afu);
	cxl_psl_purge(afu);

	वापस 0;
पूर्ण

पूर्णांक cxl_activate_dedicated_process_psl9(काष्ठा cxl_afu *afu)
अणु
	dev_info(&afu->dev, "Activating dedicated process mode\n");

	/*
	 * If XSL is set to dedicated mode (Set in PSL_SCNTL reg), the
	 * XSL and AFU are programmed to work with a single context.
	 * The context inक्रमmation should be configured in the SPA area
	 * index 0 (so PSL_SPAP must be configured beक्रमe enabling the
	 * AFU).
	 */
	afu->num_procs = 1;
	अगर (afu->native->spa == शून्य) अणु
		अगर (cxl_alloc_spa(afu, CXL_MODE_DEDICATED))
			वापस -ENOMEM;
	पूर्ण
	attach_spa(afu);

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SCNTL_An, CXL_PSL_SCNTL_An_PM_Process);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_ID_An, CXL_PSL_ID_An_F | CXL_PSL_ID_An_L);

	afu->current_mode = CXL_MODE_DEDICATED;

	वापस cxl_अक्षरdev_d_afu_add(afu);
पूर्ण

पूर्णांक cxl_activate_dedicated_process_psl8(काष्ठा cxl_afu *afu)
अणु
	dev_info(&afu->dev, "Activating dedicated process mode\n");

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SCNTL_An, CXL_PSL_SCNTL_An_PM_Process);

	cxl_p1n_ग_लिखो(afu, CXL_PSL_CtxTime_An, 0); /* disable */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPAP_An, 0);    /* disable */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_AMOR_An, 0xFFFFFFFFFFFFFFFFULL);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_LPID_An, mfspr(SPRN_LPID));
	cxl_p1n_ग_लिखो(afu, CXL_HAURP_An, 0);       /* disable */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SDR_An, mfspr(SPRN_SDR1));

	cxl_p2n_ग_लिखो(afu, CXL_CSRP_An, 0);        /* disable */
	cxl_p2n_ग_लिखो(afu, CXL_AURP0_An, 0);       /* disable */
	cxl_p2n_ग_लिखो(afu, CXL_AURP1_An, 0);       /* disable */

	afu->current_mode = CXL_MODE_DEDICATED;
	afu->num_procs = 1;

	वापस cxl_अक्षरdev_d_afu_add(afu);
पूर्ण

व्योम cxl_update_dedicated_ivtes_psl9(काष्ठा cxl_context *ctx)
अणु
	पूर्णांक r;

	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		ctx->elem->ivte_offsets[r] = cpu_to_be16(ctx->irqs.offset[r]);
		ctx->elem->ivte_ranges[r] = cpu_to_be16(ctx->irqs.range[r]);
	पूर्ण
पूर्ण

व्योम cxl_update_dedicated_ivtes_psl8(काष्ठा cxl_context *ctx)
अणु
	काष्ठा cxl_afu *afu = ctx->afu;

	cxl_p1n_ग_लिखो(afu, CXL_PSL_IVTE_Offset_An,
		       (((u64)ctx->irqs.offset[0] & 0xffff) << 48) |
		       (((u64)ctx->irqs.offset[1] & 0xffff) << 32) |
		       (((u64)ctx->irqs.offset[2] & 0xffff) << 16) |
			((u64)ctx->irqs.offset[3] & 0xffff));
	cxl_p1n_ग_लिखो(afu, CXL_PSL_IVTE_Limit_An, (u64)
		       (((u64)ctx->irqs.range[0] & 0xffff) << 48) |
		       (((u64)ctx->irqs.range[1] & 0xffff) << 32) |
		       (((u64)ctx->irqs.range[2] & 0xffff) << 16) |
			((u64)ctx->irqs.range[3] & 0xffff));
पूर्ण

पूर्णांक cxl_attach_dedicated_process_psl9(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	काष्ठा cxl_afu *afu = ctx->afu;
	पूर्णांक result;

	/* fill the process element entry */
	result = process_element_entry_psl9(ctx, wed, amr);
	अगर (result)
		वापस result;

	अगर (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes)
		afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);

	ctx->elem->software_state = cpu_to_be32(CXL_PE_SOFTWARE_STATE_V);
	/*
	 * Ideally we should करो a wmb() here to make sure the changes to the
	 * PE are visible to the card beक्रमe we call afu_enable.
	 * On ppc64 though all mmios are preceded by a 'sync' inकाष्ठाion hence
	 * we करोnt करोnt need one here.
	 */

	result = cxl_ops->afu_reset(afu);
	अगर (result)
		वापस result;

	वापस afu_enable(afu);
पूर्ण

पूर्णांक cxl_attach_dedicated_process_psl8(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	काष्ठा cxl_afu *afu = ctx->afu;
	u64 pid;
	पूर्णांक rc;

	pid = (u64)current->pid << 32;
	अगर (ctx->kernel)
		pid = 0;
	cxl_p2n_ग_लिखो(afu, CXL_PSL_PID_TID_An, pid);

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SR_An, calculate_sr(ctx));

	अगर ((rc = cxl_ग_लिखो_sstp(afu, ctx->sstp0, ctx->sstp1)))
		वापस rc;

	cxl_prefault(ctx, wed);

	अगर (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes)
		afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);

	cxl_p2n_ग_लिखो(afu, CXL_PSL_AMR_An, amr);

	/* master only context क्रम dedicated */
	cxl_assign_psn_space(ctx);

	अगर ((rc = cxl_ops->afu_reset(afu)))
		वापस rc;

	cxl_p2n_ग_लिखो(afu, CXL_PSL_WED_An, wed);

	वापस afu_enable(afu);
पूर्ण

अटल पूर्णांक deactivate_dedicated_process(काष्ठा cxl_afu *afu)
अणु
	dev_info(&afu->dev, "Deactivating dedicated process mode\n");

	afu->current_mode = 0;
	afu->num_procs = 0;

	cxl_अक्षरdev_afu_हटाओ(afu);

	वापस 0;
पूर्ण

अटल पूर्णांक native_afu_deactivate_mode(काष्ठा cxl_afu *afu, पूर्णांक mode)
अणु
	अगर (mode == CXL_MODE_सूचीECTED)
		वापस deactivate_afu_directed(afu);
	अगर (mode == CXL_MODE_DEDICATED)
		वापस deactivate_dedicated_process(afu);
	वापस 0;
पूर्ण

अटल पूर्णांक native_afu_activate_mode(काष्ठा cxl_afu *afu, पूर्णांक mode)
अणु
	अगर (!mode)
		वापस 0;
	अगर (!(mode & afu->modes_supported))
		वापस -EINVAL;

	अगर (!cxl_ops->link_ok(afu->adapter, afu)) अणु
		WARN(1, "Device link is down, refusing to activate!\n");
		वापस -EIO;
	पूर्ण

	अगर (mode == CXL_MODE_सूचीECTED)
		वापस activate_afu_directed(afu);
	अगर ((mode == CXL_MODE_DEDICATED) &&
	    (afu->adapter->native->sl_ops->activate_dedicated_process))
		वापस afu->adapter->native->sl_ops->activate_dedicated_process(afu);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक native_attach_process(काष्ठा cxl_context *ctx, bool kernel,
				u64 wed, u64 amr)
अणु
	अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu)) अणु
		WARN(1, "Device link is down, refusing to attach process!\n");
		वापस -EIO;
	पूर्ण

	ctx->kernel = kernel;
	अगर ((ctx->afu->current_mode == CXL_MODE_सूचीECTED) &&
	    (ctx->afu->adapter->native->sl_ops->attach_afu_directed))
		वापस ctx->afu->adapter->native->sl_ops->attach_afu_directed(ctx, wed, amr);

	अगर ((ctx->afu->current_mode == CXL_MODE_DEDICATED) &&
	    (ctx->afu->adapter->native->sl_ops->attach_dedicated_process))
		वापस ctx->afu->adapter->native->sl_ops->attach_dedicated_process(ctx, wed, amr);

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक detach_process_native_dedicated(काष्ठा cxl_context *ctx)
अणु
	/*
	 * The CAIA section 2.1.1 indicates that we need to करो an AFU reset to
	 * stop the AFU in dedicated mode (we thereक्रमe करो not make that
	 * optional like we करो in the afu directed path). It करोes not indicate
	 * that we need to करो an explicit disable (which should occur
	 * implicitly as part of the reset) or purge, but we करो these as well
	 * to be on the safe side.
	 *
	 * Notably we used to have some issues with the disable sequence
	 * (beक्रमe the sequence was spelled out in the architecture) which is
	 * why we were so heavy weight in the first place, however a bug was
	 * discovered that had rendered the disable operation ineffective, so
	 * it is conceivable that was the sole explanation क्रम those
	 * dअगरficulties. Poपूर्णांक is, we should be careful and करो some regression
	 * testing अगर we ever attempt to हटाओ any part of this procedure.
	 */
	cxl_ops->afu_reset(ctx->afu);
	cxl_afu_disable(ctx->afu);
	cxl_psl_purge(ctx->afu);
	वापस 0;
पूर्ण

अटल व्योम native_update_ivtes(काष्ठा cxl_context *ctx)
अणु
	अगर (ctx->afu->current_mode == CXL_MODE_सूचीECTED)
		वापस update_ivtes_directed(ctx);
	अगर ((ctx->afu->current_mode == CXL_MODE_DEDICATED) &&
	    (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes))
		वापस ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);
	WARN(1, "native_update_ivtes: Bad mode\n");
पूर्ण

अटल अंतरभूत पूर्णांक detach_process_native_afu_directed(काष्ठा cxl_context *ctx)
अणु
	अगर (!ctx->pe_inserted)
		वापस 0;
	अगर (terminate_process_element(ctx))
		वापस -1;
	अगर (हटाओ_process_element(ctx))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक native_detach_process(काष्ठा cxl_context *ctx)
अणु
	trace_cxl_detach(ctx);

	अगर (ctx->afu->current_mode == CXL_MODE_DEDICATED)
		वापस detach_process_native_dedicated(ctx);

	वापस detach_process_native_afu_directed(ctx);
पूर्ण

अटल पूर्णांक native_get_irq_info(काष्ठा cxl_afu *afu, काष्ठा cxl_irq_info *info)
अणु
	/* If the adapter has gone away, we can't get any meaningful
	 * inक्रमmation.
	 */
	अगर (!cxl_ops->link_ok(afu->adapter, afu))
		वापस -EIO;

	info->dsisr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	info->dar = cxl_p2n_पढ़ो(afu, CXL_PSL_DAR_An);
	अगर (cxl_is_घातer8())
		info->dsr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSR_An);
	info->afu_err = cxl_p2n_पढ़ो(afu, CXL_AFU_ERR_An);
	info->errstat = cxl_p2n_पढ़ो(afu, CXL_PSL_ErrStat_An);
	info->proc_handle = 0;

	वापस 0;
पूर्ण

व्योम cxl_native_irq_dump_regs_psl9(काष्ठा cxl_context *ctx)
अणु
	u64 fir1, serr;

	fir1 = cxl_p1_पढ़ो(ctx->afu->adapter, CXL_PSL9_FIR1);

	dev_crit(&ctx->afu->dev, "PSL_FIR1: 0x%016llx\n", fir1);
	अगर (ctx->afu->adapter->native->sl_ops->रेजिस्टर_serr_irq) अणु
		serr = cxl_p1n_पढ़ो(ctx->afu, CXL_PSL_SERR_An);
		cxl_afu_decode_psl_serr(ctx->afu, serr);
	पूर्ण
पूर्ण

व्योम cxl_native_irq_dump_regs_psl8(काष्ठा cxl_context *ctx)
अणु
	u64 fir1, fir2, fir_slice, serr, afu_debug;

	fir1 = cxl_p1_पढ़ो(ctx->afu->adapter, CXL_PSL_FIR1);
	fir2 = cxl_p1_पढ़ो(ctx->afu->adapter, CXL_PSL_FIR2);
	fir_slice = cxl_p1n_पढ़ो(ctx->afu, CXL_PSL_FIR_SLICE_An);
	afu_debug = cxl_p1n_पढ़ो(ctx->afu, CXL_AFU_DEBUG_An);

	dev_crit(&ctx->afu->dev, "PSL_FIR1: 0x%016llx\n", fir1);
	dev_crit(&ctx->afu->dev, "PSL_FIR2: 0x%016llx\n", fir2);
	अगर (ctx->afu->adapter->native->sl_ops->रेजिस्टर_serr_irq) अणु
		serr = cxl_p1n_पढ़ो(ctx->afu, CXL_PSL_SERR_An);
		cxl_afu_decode_psl_serr(ctx->afu, serr);
	पूर्ण
	dev_crit(&ctx->afu->dev, "PSL_FIR_SLICE_An: 0x%016llx\n", fir_slice);
	dev_crit(&ctx->afu->dev, "CXL_PSL_AFU_DEBUG_An: 0x%016llx\n", afu_debug);
पूर्ण

अटल irqवापस_t native_handle_psl_slice_error(काष्ठा cxl_context *ctx,
						u64 dsisr, u64 errstat)
अणु

	dev_crit(&ctx->afu->dev, "PSL ERROR STATUS: 0x%016llx\n", errstat);

	अगर (ctx->afu->adapter->native->sl_ops->psl_irq_dump_रेजिस्टरs)
		ctx->afu->adapter->native->sl_ops->psl_irq_dump_रेजिस्टरs(ctx);

	अगर (ctx->afu->adapter->native->sl_ops->debugfs_stop_trace) अणु
		dev_crit(&ctx->afu->dev, "STOPPING CXL TRACE\n");
		ctx->afu->adapter->native->sl_ops->debugfs_stop_trace(ctx->afu->adapter);
	पूर्ण

	वापस cxl_ops->ack_irq(ctx, 0, errstat);
पूर्ण

अटल bool cxl_is_translation_fault(काष्ठा cxl_afu *afu, u64 dsisr)
अणु
	अगर ((cxl_is_घातer8()) && (dsisr & CXL_PSL_DSISR_TRANS))
		वापस true;

	अगर ((cxl_is_घातer9()) && (dsisr & CXL_PSL9_DSISR_An_TF))
		वापस true;

	वापस false;
पूर्ण

irqवापस_t cxl_fail_irq_psl(काष्ठा cxl_afu *afu, काष्ठा cxl_irq_info *irq_info)
अणु
	अगर (cxl_is_translation_fault(afu, irq_info->dsisr))
		cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_AE);
	अन्यथा
		cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_A);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t native_irq_multiplexed(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl_afu *afu = data;
	काष्ठा cxl_context *ctx;
	काष्ठा cxl_irq_info irq_info;
	u64 phreg = cxl_p2n_पढ़ो(afu, CXL_PSL_PEHandle_An);
	पूर्णांक ph, ret = IRQ_HANDLED, res;

	/* check अगर eeh kicked in जबतक the पूर्णांकerrupt was in flight */
	अगर (unlikely(phreg == ~0ULL)) अणु
		dev_warn(&afu->dev,
			 "Ignoring slice interrupt(%d) due to fenced card",
			 irq);
		वापस IRQ_HANDLED;
	पूर्ण
	/* Mask the pe-handle from रेजिस्टर value */
	ph = phreg & 0xffff;
	अगर ((res = native_get_irq_info(afu, &irq_info))) अणु
		WARN(1, "Unable to get CXL IRQ Info: %i\n", res);
		अगर (afu->adapter->native->sl_ops->fail_irq)
			वापस afu->adapter->native->sl_ops->fail_irq(afu, &irq_info);
		वापस ret;
	पूर्ण

	rcu_पढ़ो_lock();
	ctx = idr_find(&afu->contexts_idr, ph);
	अगर (ctx) अणु
		अगर (afu->adapter->native->sl_ops->handle_पूर्णांकerrupt)
			ret = afu->adapter->native->sl_ops->handle_पूर्णांकerrupt(irq, ctx, &irq_info);
		rcu_पढ़ो_unlock();
		वापस ret;
	पूर्ण
	rcu_पढ़ो_unlock();

	WARN(1, "Unable to demultiplex CXL PSL IRQ for PE %i DSISR %016llx DAR"
		" %016llx\n(Possible AFU HW issue - was a term/remove acked"
		" with outstanding transactions?)\n", ph, irq_info.dsisr,
		irq_info.dar);
	अगर (afu->adapter->native->sl_ops->fail_irq)
		ret = afu->adapter->native->sl_ops->fail_irq(afu, &irq_info);
	वापस ret;
पूर्ण

अटल व्योम native_irq_रुको(काष्ठा cxl_context *ctx)
अणु
	u64 dsisr;
	पूर्णांक समयout = 1000;
	पूर्णांक ph;

	/*
	 * Wait until no further पूर्णांकerrupts are presented by the PSL
	 * क्रम this context.
	 */
	जबतक (समयout--) अणु
		ph = cxl_p2n_पढ़ो(ctx->afu, CXL_PSL_PEHandle_An) & 0xffff;
		अगर (ph != ctx->pe)
			वापस;
		dsisr = cxl_p2n_पढ़ो(ctx->afu, CXL_PSL_DSISR_An);
		अगर (cxl_is_घातer8() &&
		   ((dsisr & CXL_PSL_DSISR_PENDING) == 0))
			वापस;
		अगर (cxl_is_घातer9() &&
		   ((dsisr & CXL_PSL9_DSISR_PENDING) == 0))
			वापस;
		/*
		 * We are रुकोing क्रम the workqueue to process our
		 * irq, so need to let that run here.
		 */
		msleep(1);
	पूर्ण

	dev_warn(&ctx->afu->dev, "WARNING: waiting on DSI for PE %i"
		 " DSISR %016llx!\n", ph, dsisr);
	वापस;
पूर्ण

अटल irqवापस_t native_slice_irq_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl_afu *afu = data;
	u64 errstat, serr, afu_error, dsisr;
	u64 fir_slice, afu_debug, irq_mask;

	/*
	 * slice err पूर्णांकerrupt is only used with full PSL (no XSL)
	 */
	serr = cxl_p1n_पढ़ो(afu, CXL_PSL_SERR_An);
	errstat = cxl_p2n_पढ़ो(afu, CXL_PSL_ErrStat_An);
	afu_error = cxl_p2n_पढ़ो(afu, CXL_AFU_ERR_An);
	dsisr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	cxl_afu_decode_psl_serr(afu, serr);

	अगर (cxl_is_घातer8()) अणु
		fir_slice = cxl_p1n_पढ़ो(afu, CXL_PSL_FIR_SLICE_An);
		afu_debug = cxl_p1n_पढ़ो(afu, CXL_AFU_DEBUG_An);
		dev_crit(&afu->dev, "PSL_FIR_SLICE_An: 0x%016llx\n", fir_slice);
		dev_crit(&afu->dev, "CXL_PSL_AFU_DEBUG_An: 0x%016llx\n", afu_debug);
	पूर्ण
	dev_crit(&afu->dev, "CXL_PSL_ErrStat_An: 0x%016llx\n", errstat);
	dev_crit(&afu->dev, "AFU_ERR_An: 0x%.16llx\n", afu_error);
	dev_crit(&afu->dev, "PSL_DSISR_An: 0x%.16llx\n", dsisr);

	/* mask off the IRQ so it won't retrigger until the AFU is reset */
	irq_mask = (serr & CXL_PSL_SERR_An_IRQS) >> 32;
	serr |= irq_mask;
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, serr);
	dev_info(&afu->dev, "Further such interrupts will be masked until the AFU is reset\n");

	वापस IRQ_HANDLED;
पूर्ण

व्योम cxl_native_err_irq_dump_regs_psl9(काष्ठा cxl *adapter)
अणु
	u64 fir1;

	fir1 = cxl_p1_पढ़ो(adapter, CXL_PSL9_FIR1);
	dev_crit(&adapter->dev, "PSL_FIR: 0x%016llx\n", fir1);
पूर्ण

व्योम cxl_native_err_irq_dump_regs_psl8(काष्ठा cxl *adapter)
अणु
	u64 fir1, fir2;

	fir1 = cxl_p1_पढ़ो(adapter, CXL_PSL_FIR1);
	fir2 = cxl_p1_पढ़ो(adapter, CXL_PSL_FIR2);
	dev_crit(&adapter->dev,
		 "PSL_FIR1: 0x%016llx\nPSL_FIR2: 0x%016llx\n",
		 fir1, fir2);
पूर्ण

अटल irqवापस_t native_irq_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl *adapter = data;
	u64 err_ivte;

	WARN(1, "CXL ERROR interrupt %i\n", irq);

	err_ivte = cxl_p1_पढ़ो(adapter, CXL_PSL_ErrIVTE);
	dev_crit(&adapter->dev, "PSL_ErrIVTE: 0x%016llx\n", err_ivte);

	अगर (adapter->native->sl_ops->debugfs_stop_trace) अणु
		dev_crit(&adapter->dev, "STOPPING CXL TRACE\n");
		adapter->native->sl_ops->debugfs_stop_trace(adapter);
	पूर्ण

	अगर (adapter->native->sl_ops->err_irq_dump_रेजिस्टरs)
		adapter->native->sl_ops->err_irq_dump_रेजिस्टरs(adapter);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक cxl_native_रेजिस्टर_psl_err_irq(काष्ठा cxl *adapter)
अणु
	पूर्णांक rc;

	adapter->irq_name = kaप्र_लिखो(GFP_KERNEL, "cxl-%s-err",
				      dev_name(&adapter->dev));
	अगर (!adapter->irq_name)
		वापस -ENOMEM;

	अगर ((rc = cxl_रेजिस्टर_one_irq(adapter, native_irq_err, adapter,
				       &adapter->native->err_hwirq,
				       &adapter->native->err_virq,
				       adapter->irq_name))) अणु
		kमुक्त(adapter->irq_name);
		adapter->irq_name = शून्य;
		वापस rc;
	पूर्ण

	cxl_p1_ग_लिखो(adapter, CXL_PSL_ErrIVTE, adapter->native->err_hwirq & 0xffff);

	वापस 0;
पूर्ण

व्योम cxl_native_release_psl_err_irq(काष्ठा cxl *adapter)
अणु
	अगर (adapter->native->err_virq == 0 ||
	    adapter->native->err_virq !=
	    irq_find_mapping(शून्य, adapter->native->err_hwirq))
		वापस;

	cxl_p1_ग_लिखो(adapter, CXL_PSL_ErrIVTE, 0x0000000000000000);
	cxl_unmap_irq(adapter->native->err_virq, adapter);
	cxl_ops->release_one_irq(adapter, adapter->native->err_hwirq);
	kमुक्त(adapter->irq_name);
	adapter->native->err_virq = 0;
पूर्ण

पूर्णांक cxl_native_रेजिस्टर_serr_irq(काष्ठा cxl_afu *afu)
अणु
	u64 serr;
	पूर्णांक rc;

	afu->err_irq_name = kaप्र_लिखो(GFP_KERNEL, "cxl-%s-err",
				      dev_name(&afu->dev));
	अगर (!afu->err_irq_name)
		वापस -ENOMEM;

	अगर ((rc = cxl_रेजिस्टर_one_irq(afu->adapter, native_slice_irq_err, afu,
				       &afu->serr_hwirq,
				       &afu->serr_virq, afu->err_irq_name))) अणु
		kमुक्त(afu->err_irq_name);
		afu->err_irq_name = शून्य;
		वापस rc;
	पूर्ण

	serr = cxl_p1n_पढ़ो(afu, CXL_PSL_SERR_An);
	अगर (cxl_is_घातer8())
		serr = (serr & 0x00ffffffffff0000ULL) | (afu->serr_hwirq & 0xffff);
	अगर (cxl_is_घातer9()) अणु
		/*
		 * By शेष, all errors are masked. So करोn't set all masks.
		 * Slice errors will be transfered.
		 */
		serr = (serr & ~0xff0000007fffffffULL) | (afu->serr_hwirq & 0xffff);
	पूर्ण
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, serr);

	वापस 0;
पूर्ण

व्योम cxl_native_release_serr_irq(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->serr_virq == 0 ||
	    afu->serr_virq != irq_find_mapping(शून्य, afu->serr_hwirq))
		वापस;

	cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, 0x0000000000000000);
	cxl_unmap_irq(afu->serr_virq, afu);
	cxl_ops->release_one_irq(afu->adapter, afu->serr_hwirq);
	kमुक्त(afu->err_irq_name);
	afu->serr_virq = 0;
पूर्ण

पूर्णांक cxl_native_रेजिस्टर_psl_irq(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक rc;

	afu->psl_irq_name = kaप्र_लिखो(GFP_KERNEL, "cxl-%s",
				      dev_name(&afu->dev));
	अगर (!afu->psl_irq_name)
		वापस -ENOMEM;

	अगर ((rc = cxl_रेजिस्टर_one_irq(afu->adapter, native_irq_multiplexed,
				    afu, &afu->native->psl_hwirq, &afu->native->psl_virq,
				    afu->psl_irq_name))) अणु
		kमुक्त(afu->psl_irq_name);
		afu->psl_irq_name = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

व्योम cxl_native_release_psl_irq(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->native->psl_virq == 0 ||
	    afu->native->psl_virq !=
	    irq_find_mapping(शून्य, afu->native->psl_hwirq))
		वापस;

	cxl_unmap_irq(afu->native->psl_virq, afu);
	cxl_ops->release_one_irq(afu->adapter, afu->native->psl_hwirq);
	kमुक्त(afu->psl_irq_name);
	afu->native->psl_virq = 0;
पूर्ण

अटल व्योम recover_psl_err(काष्ठा cxl_afu *afu, u64 errstat)
अणु
	u64 dsisr;

	pr_devel("RECOVERING FROM PSL ERROR... (0x%016llx)\n", errstat);

	/* Clear PSL_DSISR[PE] */
	dsisr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	cxl_p2n_ग_लिखो(afu, CXL_PSL_DSISR_An, dsisr & ~CXL_PSL_DSISR_An_PE);

	/* Write 1s to clear error status bits */
	cxl_p2n_ग_लिखो(afu, CXL_PSL_ErrStat_An, errstat);
पूर्ण

अटल पूर्णांक native_ack_irq(काष्ठा cxl_context *ctx, u64 tfc, u64 psl_reset_mask)
अणु
	trace_cxl_psl_irq_ack(ctx, tfc);
	अगर (tfc)
		cxl_p2n_ग_लिखो(ctx->afu, CXL_PSL_TFC_An, tfc);
	अगर (psl_reset_mask)
		recover_psl_err(ctx->afu, psl_reset_mask);

	वापस 0;
पूर्ण

पूर्णांक cxl_check_error(काष्ठा cxl_afu *afu)
अणु
	वापस (cxl_p1n_पढ़ो(afu, CXL_PSL_SCNTL_An) == ~0ULL);
पूर्ण

अटल bool native_support_attributes(स्थिर अक्षर *attr_name,
				      क्रमागत cxl_attrs type)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक native_afu_cr_पढ़ो64(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u64 *out)
अणु
	अगर (unlikely(!cxl_ops->link_ok(afu->adapter, afu)))
		वापस -EIO;
	अगर (unlikely(off >= afu->crs_len))
		वापस -दुस्फल;
	*out = in_le64(afu->native->afu_desc_mmio + afu->crs_offset +
		(cr * afu->crs_len) + off);
	वापस 0;
पूर्ण

अटल पूर्णांक native_afu_cr_पढ़ो32(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u32 *out)
अणु
	अगर (unlikely(!cxl_ops->link_ok(afu->adapter, afu)))
		वापस -EIO;
	अगर (unlikely(off >= afu->crs_len))
		वापस -दुस्फल;
	*out = in_le32(afu->native->afu_desc_mmio + afu->crs_offset +
		(cr * afu->crs_len) + off);
	वापस 0;
पूर्ण

अटल पूर्णांक native_afu_cr_पढ़ो16(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u16 *out)
अणु
	u64 aligned_off = off & ~0x3L;
	u32 val;
	पूर्णांक rc;

	rc = native_afu_cr_पढ़ो32(afu, cr, aligned_off, &val);
	अगर (!rc)
		*out = (val >> ((off & 0x3) * 8)) & 0xffff;
	वापस rc;
पूर्ण

अटल पूर्णांक native_afu_cr_पढ़ो8(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u8 *out)
अणु
	u64 aligned_off = off & ~0x3L;
	u32 val;
	पूर्णांक rc;

	rc = native_afu_cr_पढ़ो32(afu, cr, aligned_off, &val);
	अगर (!rc)
		*out = (val >> ((off & 0x3) * 8)) & 0xff;
	वापस rc;
पूर्ण

अटल पूर्णांक native_afu_cr_ग_लिखो32(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u32 in)
अणु
	अगर (unlikely(!cxl_ops->link_ok(afu->adapter, afu)))
		वापस -EIO;
	अगर (unlikely(off >= afu->crs_len))
		वापस -दुस्फल;
	out_le32(afu->native->afu_desc_mmio + afu->crs_offset +
		(cr * afu->crs_len) + off, in);
	वापस 0;
पूर्ण

अटल पूर्णांक native_afu_cr_ग_लिखो16(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u16 in)
अणु
	u64 aligned_off = off & ~0x3L;
	u32 val32, mask, shअगरt;
	पूर्णांक rc;

	rc = native_afu_cr_पढ़ो32(afu, cr, aligned_off, &val32);
	अगर (rc)
		वापस rc;
	shअगरt = (off & 0x3) * 8;
	WARN_ON(shअगरt == 24);
	mask = 0xffff << shअगरt;
	val32 = (val32 & ~mask) | (in << shअगरt);

	rc = native_afu_cr_ग_लिखो32(afu, cr, aligned_off, val32);
	वापस rc;
पूर्ण

अटल पूर्णांक native_afu_cr_ग_लिखो8(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u8 in)
अणु
	u64 aligned_off = off & ~0x3L;
	u32 val32, mask, shअगरt;
	पूर्णांक rc;

	rc = native_afu_cr_पढ़ो32(afu, cr, aligned_off, &val32);
	अगर (rc)
		वापस rc;
	shअगरt = (off & 0x3) * 8;
	mask = 0xff << shअगरt;
	val32 = (val32 & ~mask) | (in << shअगरt);

	rc = native_afu_cr_ग_लिखो32(afu, cr, aligned_off, val32);
	वापस rc;
पूर्ण

स्थिर काष्ठा cxl_backend_ops cxl_native_ops = अणु
	.module = THIS_MODULE,
	.adapter_reset = cxl_pci_reset,
	.alloc_one_irq = cxl_pci_alloc_one_irq,
	.release_one_irq = cxl_pci_release_one_irq,
	.alloc_irq_ranges = cxl_pci_alloc_irq_ranges,
	.release_irq_ranges = cxl_pci_release_irq_ranges,
	.setup_irq = cxl_pci_setup_irq,
	.handle_psl_slice_error = native_handle_psl_slice_error,
	.psl_पूर्णांकerrupt = शून्य,
	.ack_irq = native_ack_irq,
	.irq_रुको = native_irq_रुको,
	.attach_process = native_attach_process,
	.detach_process = native_detach_process,
	.update_ivtes = native_update_ivtes,
	.support_attributes = native_support_attributes,
	.link_ok = cxl_adapter_link_ok,
	.release_afu = cxl_pci_release_afu,
	.afu_पढ़ो_err_buffer = cxl_pci_afu_पढ़ो_err_buffer,
	.afu_check_and_enable = native_afu_check_and_enable,
	.afu_activate_mode = native_afu_activate_mode,
	.afu_deactivate_mode = native_afu_deactivate_mode,
	.afu_reset = native_afu_reset,
	.afu_cr_पढ़ो8 = native_afu_cr_पढ़ो8,
	.afu_cr_पढ़ो16 = native_afu_cr_पढ़ो16,
	.afu_cr_पढ़ो32 = native_afu_cr_पढ़ो32,
	.afu_cr_पढ़ो64 = native_afu_cr_पढ़ो64,
	.afu_cr_ग_लिखो8 = native_afu_cr_ग_लिखो8,
	.afu_cr_ग_लिखो16 = native_afu_cr_ग_लिखो16,
	.afu_cr_ग_लिखो32 = native_afu_cr_ग_लिखो32,
	.पढ़ो_adapter_vpd = cxl_pci_पढ़ो_adapter_vpd,
पूर्ण;
