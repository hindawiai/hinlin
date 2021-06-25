<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOMMU API क्रम ARM architected SMMUv3 implementations.
 *
 * Copyright (C) 2015 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 *
 * This driver is घातered by bad coffee and bombay mix.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/bitops.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ats.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/amba/bus.h>

#समावेश "arm-smmu-v3.h"

अटल bool disable_bypass = true;
module_param(disable_bypass, bool, 0444);
MODULE_PARM_DESC(disable_bypass,
	"Disable bypass streams such that incoming transactions from devices that are not attached to an iommu domain will report an abort back to the device and will not be allowed to pass through the SMMU.");

अटल bool disable_msipolling;
module_param(disable_msipolling, bool, 0444);
MODULE_PARM_DESC(disable_msipolling,
	"Disable MSI-based polling for CMD_SYNC completion.");

क्रमागत arm_smmu_msi_index अणु
	EVTQ_MSI_INDEX,
	GERROR_MSI_INDEX,
	PRIQ_MSI_INDEX,
	ARM_SMMU_MAX_MSIS,
पूर्ण;

अटल phys_addr_t arm_smmu_msi_cfg[ARM_SMMU_MAX_MSIS][3] = अणु
	[EVTQ_MSI_INDEX] = अणु
		ARM_SMMU_EVTQ_IRQ_CFG0,
		ARM_SMMU_EVTQ_IRQ_CFG1,
		ARM_SMMU_EVTQ_IRQ_CFG2,
	पूर्ण,
	[GERROR_MSI_INDEX] = अणु
		ARM_SMMU_GERROR_IRQ_CFG0,
		ARM_SMMU_GERROR_IRQ_CFG1,
		ARM_SMMU_GERROR_IRQ_CFG2,
	पूर्ण,
	[PRIQ_MSI_INDEX] = अणु
		ARM_SMMU_PRIQ_IRQ_CFG0,
		ARM_SMMU_PRIQ_IRQ_CFG1,
		ARM_SMMU_PRIQ_IRQ_CFG2,
	पूर्ण,
पूर्ण;

काष्ठा arm_smmu_option_prop अणु
	u32 opt;
	स्थिर अक्षर *prop;
पूर्ण;

DEFINE_XARRAY_ALLOC1(arm_smmu_asid_xa);
DEFINE_MUTEX(arm_smmu_asid_lock);

/*
 * Special value used by SVA when a process dies, to quiesce a CD without
 * disabling it.
 */
काष्ठा arm_smmu_ctx_desc quiet_cd = अणु 0 पूर्ण;

अटल काष्ठा arm_smmu_option_prop arm_smmu_options[] = अणु
	अणु ARM_SMMU_OPT_SKIP_PREFETCH, "hisilicon,broken-prefetch-cmd" पूर्ण,
	अणु ARM_SMMU_OPT_PAGE0_REGS_ONLY, "cavium,cn9900-broken-page1-regspace"पूर्ण,
	अणु 0, शून्यपूर्ण,
पूर्ण;

अटल व्योम parse_driver_options(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक i = 0;

	करो अणु
		अगर (of_property_पढ़ो_bool(smmu->dev->of_node,
						arm_smmu_options[i].prop)) अणु
			smmu->options |= arm_smmu_options[i].opt;
			dev_notice(smmu->dev, "option %s\n",
				arm_smmu_options[i].prop);
		पूर्ण
	पूर्ण जबतक (arm_smmu_options[++i].opt);
पूर्ण

/* Low-level queue manipulation functions */
अटल bool queue_has_space(काष्ठा arm_smmu_ll_queue *q, u32 n)
अणु
	u32 space, prod, cons;

	prod = Q_IDX(q, q->prod);
	cons = Q_IDX(q, q->cons);

	अगर (Q_WRP(q, q->prod) == Q_WRP(q, q->cons))
		space = (1 << q->max_n_shअगरt) - (prod - cons);
	अन्यथा
		space = cons - prod;

	वापस space >= n;
पूर्ण

अटल bool queue_full(काष्ठा arm_smmu_ll_queue *q)
अणु
	वापस Q_IDX(q, q->prod) == Q_IDX(q, q->cons) &&
	       Q_WRP(q, q->prod) != Q_WRP(q, q->cons);
पूर्ण

अटल bool queue_empty(काष्ठा arm_smmu_ll_queue *q)
अणु
	वापस Q_IDX(q, q->prod) == Q_IDX(q, q->cons) &&
	       Q_WRP(q, q->prod) == Q_WRP(q, q->cons);
पूर्ण

अटल bool queue_consumed(काष्ठा arm_smmu_ll_queue *q, u32 prod)
अणु
	वापस ((Q_WRP(q, q->cons) == Q_WRP(q, prod)) &&
		(Q_IDX(q, q->cons) > Q_IDX(q, prod))) ||
	       ((Q_WRP(q, q->cons) != Q_WRP(q, prod)) &&
		(Q_IDX(q, q->cons) <= Q_IDX(q, prod)));
पूर्ण

अटल व्योम queue_sync_cons_out(काष्ठा arm_smmu_queue *q)
अणु
	/*
	 * Ensure that all CPU accesses (पढ़ोs and ग_लिखोs) to the queue
	 * are complete beक्रमe we update the cons poपूर्णांकer.
	 */
	__iomb();
	ग_लिखोl_relaxed(q->llq.cons, q->cons_reg);
पूर्ण

अटल व्योम queue_inc_cons(काष्ठा arm_smmu_ll_queue *q)
अणु
	u32 cons = (Q_WRP(q, q->cons) | Q_IDX(q, q->cons)) + 1;
	q->cons = Q_OVF(q->cons) | Q_WRP(q, cons) | Q_IDX(q, cons);
पूर्ण

अटल पूर्णांक queue_sync_prod_in(काष्ठा arm_smmu_queue *q)
अणु
	u32 prod;
	पूर्णांक ret = 0;

	/*
	 * We can't use the _relaxed() variant here, as we must prevent
	 * speculative पढ़ोs of the queue beक्रमe we have determined that
	 * prod has indeed moved.
	 */
	prod = पढ़ोl(q->prod_reg);

	अगर (Q_OVF(prod) != Q_OVF(q->llq.prod))
		ret = -EOVERFLOW;

	q->llq.prod = prod;
	वापस ret;
पूर्ण

अटल u32 queue_inc_prod_n(काष्ठा arm_smmu_ll_queue *q, पूर्णांक n)
अणु
	u32 prod = (Q_WRP(q, q->prod) | Q_IDX(q, q->prod)) + n;
	वापस Q_OVF(q->prod) | Q_WRP(q, prod) | Q_IDX(q, prod);
पूर्ण

अटल व्योम queue_poll_init(काष्ठा arm_smmu_device *smmu,
			    काष्ठा arm_smmu_queue_poll *qp)
अणु
	qp->delay = 1;
	qp->spin_cnt = 0;
	qp->wfe = !!(smmu->features & ARM_SMMU_FEAT_SEV);
	qp->समयout = kसमय_add_us(kसमय_get(), ARM_SMMU_POLL_TIMEOUT_US);
पूर्ण

अटल पूर्णांक queue_poll(काष्ठा arm_smmu_queue_poll *qp)
अणु
	अगर (kसमय_compare(kसमय_get(), qp->समयout) > 0)
		वापस -ETIMEDOUT;

	अगर (qp->wfe) अणु
		wfe();
	पूर्ण अन्यथा अगर (++qp->spin_cnt < ARM_SMMU_POLL_SPIN_COUNT) अणु
		cpu_relax();
	पूर्ण अन्यथा अणु
		udelay(qp->delay);
		qp->delay *= 2;
		qp->spin_cnt = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम queue_ग_लिखो(__le64 *dst, u64 *src, माप_प्रकार n_dwords)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_dwords; ++i)
		*dst++ = cpu_to_le64(*src++);
पूर्ण

अटल व्योम queue_पढ़ो(u64 *dst, __le64 *src, माप_प्रकार n_dwords)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_dwords; ++i)
		*dst++ = le64_to_cpu(*src++);
पूर्ण

अटल पूर्णांक queue_हटाओ_raw(काष्ठा arm_smmu_queue *q, u64 *ent)
अणु
	अगर (queue_empty(&q->llq))
		वापस -EAGAIN;

	queue_पढ़ो(ent, Q_ENT(q, q->llq.cons), q->ent_dwords);
	queue_inc_cons(&q->llq);
	queue_sync_cons_out(q);
	वापस 0;
पूर्ण

/* High-level queue accessors */
अटल पूर्णांक arm_smmu_cmdq_build_cmd(u64 *cmd, काष्ठा arm_smmu_cmdq_ent *ent)
अणु
	स_रखो(cmd, 0, 1 << CMDQ_ENT_SZ_SHIFT);
	cmd[0] |= FIELD_PREP(CMDQ_0_OP, ent->opcode);

	चयन (ent->opcode) अणु
	हाल CMDQ_OP_TLBI_EL2_ALL:
	हाल CMDQ_OP_TLBI_NSNH_ALL:
		अवरोध;
	हाल CMDQ_OP_PREFETCH_CFG:
		cmd[0] |= FIELD_PREP(CMDQ_PREFETCH_0_SID, ent->prefetch.sid);
		अवरोध;
	हाल CMDQ_OP_CFGI_CD:
		cmd[0] |= FIELD_PREP(CMDQ_CFGI_0_SSID, ent->cfgi.ssid);
		fallthrough;
	हाल CMDQ_OP_CFGI_STE:
		cmd[0] |= FIELD_PREP(CMDQ_CFGI_0_SID, ent->cfgi.sid);
		cmd[1] |= FIELD_PREP(CMDQ_CFGI_1_LEAF, ent->cfgi.leaf);
		अवरोध;
	हाल CMDQ_OP_CFGI_CD_ALL:
		cmd[0] |= FIELD_PREP(CMDQ_CFGI_0_SID, ent->cfgi.sid);
		अवरोध;
	हाल CMDQ_OP_CFGI_ALL:
		/* Cover the entire SID range */
		cmd[1] |= FIELD_PREP(CMDQ_CFGI_1_RANGE, 31);
		अवरोध;
	हाल CMDQ_OP_TLBI_NH_VA:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_VMID, ent->tlbi.vmid);
		fallthrough;
	हाल CMDQ_OP_TLBI_EL2_VA:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_NUM, ent->tlbi.num);
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_SCALE, ent->tlbi.scale);
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_ASID, ent->tlbi.asid);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_LEAF, ent->tlbi.leaf);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_TTL, ent->tlbi.ttl);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_TG, ent->tlbi.tg);
		cmd[1] |= ent->tlbi.addr & CMDQ_TLBI_1_VA_MASK;
		अवरोध;
	हाल CMDQ_OP_TLBI_S2_IPA:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_NUM, ent->tlbi.num);
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_SCALE, ent->tlbi.scale);
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_VMID, ent->tlbi.vmid);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_LEAF, ent->tlbi.leaf);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_TTL, ent->tlbi.ttl);
		cmd[1] |= FIELD_PREP(CMDQ_TLBI_1_TG, ent->tlbi.tg);
		cmd[1] |= ent->tlbi.addr & CMDQ_TLBI_1_IPA_MASK;
		अवरोध;
	हाल CMDQ_OP_TLBI_NH_ASID:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_ASID, ent->tlbi.asid);
		fallthrough;
	हाल CMDQ_OP_TLBI_S12_VMALL:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_VMID, ent->tlbi.vmid);
		अवरोध;
	हाल CMDQ_OP_TLBI_EL2_ASID:
		cmd[0] |= FIELD_PREP(CMDQ_TLBI_0_ASID, ent->tlbi.asid);
		अवरोध;
	हाल CMDQ_OP_ATC_INV:
		cmd[0] |= FIELD_PREP(CMDQ_0_SSV, ent->substream_valid);
		cmd[0] |= FIELD_PREP(CMDQ_ATC_0_GLOBAL, ent->atc.global);
		cmd[0] |= FIELD_PREP(CMDQ_ATC_0_SSID, ent->atc.ssid);
		cmd[0] |= FIELD_PREP(CMDQ_ATC_0_SID, ent->atc.sid);
		cmd[1] |= FIELD_PREP(CMDQ_ATC_1_SIZE, ent->atc.size);
		cmd[1] |= ent->atc.addr & CMDQ_ATC_1_ADDR_MASK;
		अवरोध;
	हाल CMDQ_OP_PRI_RESP:
		cmd[0] |= FIELD_PREP(CMDQ_0_SSV, ent->substream_valid);
		cmd[0] |= FIELD_PREP(CMDQ_PRI_0_SSID, ent->pri.ssid);
		cmd[0] |= FIELD_PREP(CMDQ_PRI_0_SID, ent->pri.sid);
		cmd[1] |= FIELD_PREP(CMDQ_PRI_1_GRPID, ent->pri.grpid);
		चयन (ent->pri.resp) अणु
		हाल PRI_RESP_DENY:
		हाल PRI_RESP_FAIL:
		हाल PRI_RESP_SUCC:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		cmd[1] |= FIELD_PREP(CMDQ_PRI_1_RESP, ent->pri.resp);
		अवरोध;
	हाल CMDQ_OP_CMD_SYNC:
		अगर (ent->sync.msiaddr) अणु
			cmd[0] |= FIELD_PREP(CMDQ_SYNC_0_CS, CMDQ_SYNC_0_CS_IRQ);
			cmd[1] |= ent->sync.msiaddr & CMDQ_SYNC_1_MSIADDR_MASK;
		पूर्ण अन्यथा अणु
			cmd[0] |= FIELD_PREP(CMDQ_SYNC_0_CS, CMDQ_SYNC_0_CS_SEV);
		पूर्ण
		cmd[0] |= FIELD_PREP(CMDQ_SYNC_0_MSH, ARM_SMMU_SH_ISH);
		cmd[0] |= FIELD_PREP(CMDQ_SYNC_0_MSIATTR, ARM_SMMU_MEMATTR_OIWB);
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम arm_smmu_cmdq_build_sync_cmd(u64 *cmd, काष्ठा arm_smmu_device *smmu,
					 u32 prod)
अणु
	काष्ठा arm_smmu_queue *q = &smmu->cmdq.q;
	काष्ठा arm_smmu_cmdq_ent ent = अणु
		.opcode = CMDQ_OP_CMD_SYNC,
	पूर्ण;

	/*
	 * Beware that Hi16xx adds an extra 32 bits of goodness to its MSI
	 * payload, so the ग_लिखो will zero the entire command on that platक्रमm.
	 */
	अगर (smmu->options & ARM_SMMU_OPT_MSIPOLL) अणु
		ent.sync.msiaddr = q->base_dma + Q_IDX(&q->llq, prod) *
				   q->ent_dwords * 8;
	पूर्ण

	arm_smmu_cmdq_build_cmd(cmd, &ent);
पूर्ण

अटल व्योम arm_smmu_cmdq_skip_err(काष्ठा arm_smmu_device *smmu)
अणु
	अटल स्थिर अक्षर *cerror_str[] = अणु
		[CMDQ_ERR_CERROR_NONE_IDX]	= "No error",
		[CMDQ_ERR_CERROR_ILL_IDX]	= "Illegal command",
		[CMDQ_ERR_CERROR_ABT_IDX]	= "Abort on command fetch",
		[CMDQ_ERR_CERROR_ATC_INV_IDX]	= "ATC invalidate timeout",
	पूर्ण;

	पूर्णांक i;
	u64 cmd[CMDQ_ENT_DWORDS];
	काष्ठा arm_smmu_queue *q = &smmu->cmdq.q;
	u32 cons = पढ़ोl_relaxed(q->cons_reg);
	u32 idx = FIELD_GET(CMDQ_CONS_ERR, cons);
	काष्ठा arm_smmu_cmdq_ent cmd_sync = अणु
		.opcode = CMDQ_OP_CMD_SYNC,
	पूर्ण;

	dev_err(smmu->dev, "CMDQ error (cons 0x%08x): %s\n", cons,
		idx < ARRAY_SIZE(cerror_str) ?  cerror_str[idx] : "Unknown");

	चयन (idx) अणु
	हाल CMDQ_ERR_CERROR_ABT_IDX:
		dev_err(smmu->dev, "retrying command fetch\n");
	हाल CMDQ_ERR_CERROR_NONE_IDX:
		वापस;
	हाल CMDQ_ERR_CERROR_ATC_INV_IDX:
		/*
		 * ATC Invalidation Completion समयout. CONS is still poपूर्णांकing
		 * at the CMD_SYNC. Attempt to complete other pending commands
		 * by repeating the CMD_SYNC, though we might well end up back
		 * here since the ATC invalidation may still be pending.
		 */
		वापस;
	हाल CMDQ_ERR_CERROR_ILL_IDX:
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * We may have concurrent producers, so we need to be careful
	 * not to touch any of the shaकरोw cmdq state.
	 */
	queue_पढ़ो(cmd, Q_ENT(q, cons), q->ent_dwords);
	dev_err(smmu->dev, "skipping command in error state:\n");
	क्रम (i = 0; i < ARRAY_SIZE(cmd); ++i)
		dev_err(smmu->dev, "\t0x%016llx\n", (अचिन्हित दीर्घ दीर्घ)cmd[i]);

	/* Convert the erroneous command पूर्णांकo a CMD_SYNC */
	अगर (arm_smmu_cmdq_build_cmd(cmd, &cmd_sync)) अणु
		dev_err(smmu->dev, "failed to convert to CMD_SYNC\n");
		वापस;
	पूर्ण

	queue_ग_लिखो(Q_ENT(q, cons), cmd, q->ent_dwords);
पूर्ण

/*
 * Command queue locking.
 * This is a क्रमm of bastardised rwlock with the following major changes:
 *
 * - The only LOCK routines are exclusive_trylock() and shared_lock().
 *   Neither have barrier semantics, and instead provide only a control
 *   dependency.
 *
 * - The UNLOCK routines are supplemented with shared_tryunlock(), which
 *   fails अगर the caller appears to be the last lock holder (yes, this is
 *   racy). All successful UNLOCK routines have RELEASE semantics.
 */
अटल व्योम arm_smmu_cmdq_shared_lock(काष्ठा arm_smmu_cmdq *cmdq)
अणु
	पूर्णांक val;

	/*
	 * We can try to aव्योम the cmpxchg() loop by simply incrementing the
	 * lock counter. When held in exclusive state, the lock counter is set
	 * to पूर्णांक_न्यून so these increments won't hurt as the value will reमुख्य
	 * negative.
	 */
	अगर (atomic_fetch_inc_relaxed(&cmdq->lock) >= 0)
		वापस;

	करो अणु
		val = atomic_cond_पढ़ो_relaxed(&cmdq->lock, VAL >= 0);
	पूर्ण जबतक (atomic_cmpxchg_relaxed(&cmdq->lock, val, val + 1) != val);
पूर्ण

अटल व्योम arm_smmu_cmdq_shared_unlock(काष्ठा arm_smmu_cmdq *cmdq)
अणु
	(व्योम)atomic_dec_वापस_release(&cmdq->lock);
पूर्ण

अटल bool arm_smmu_cmdq_shared_tryunlock(काष्ठा arm_smmu_cmdq *cmdq)
अणु
	अगर (atomic_पढ़ो(&cmdq->lock) == 1)
		वापस false;

	arm_smmu_cmdq_shared_unlock(cmdq);
	वापस true;
पूर्ण

#घोषणा arm_smmu_cmdq_exclusive_trylock_irqsave(cmdq, flags)		\
(अणु									\
	bool __ret;							\
	local_irq_save(flags);						\
	__ret = !atomic_cmpxchg_relaxed(&cmdq->lock, 0, पूर्णांक_न्यून);	\
	अगर (!__ret)							\
		local_irq_restore(flags);				\
	__ret;								\
पूर्ण)

#घोषणा arm_smmu_cmdq_exclusive_unlock_irqrestore(cmdq, flags)		\
(अणु									\
	atomic_set_release(&cmdq->lock, 0);				\
	local_irq_restore(flags);					\
पूर्ण)


/*
 * Command queue insertion.
 * This is made fiddly by our attempts to achieve some sort of scalability
 * since there is one queue shared amongst all of the CPUs in the प्रणाली.  If
 * you like mixed-size concurrency, dependency ordering and relaxed atomics,
 * then you'll *love* this monstrosity.
 *
 * The basic idea is to split the queue up पूर्णांकo ranges of commands that are
 * owned by a given CPU; the owner may not have written all of the commands
 * itself, but is responsible क्रम advancing the hardware prod poपूर्णांकer when
 * the समय comes. The algorithm is roughly:
 *
 * 	1. Allocate some space in the queue. At this poपूर्णांक we also discover
 *	   whether the head of the queue is currently owned by another CPU,
 *	   or whether we are the owner.
 *
 *	2. Write our commands पूर्णांकo our allocated slots in the queue.
 *
 *	3. Mark our slots as valid in arm_smmu_cmdq.valid_map.
 *
 *	4. If we are an owner:
 *		a. Wait क्रम the previous owner to finish.
 *		b. Mark the queue head as unowned, which tells us the range
 *		   that we are responsible क्रम publishing.
 *		c. Wait क्रम all commands in our owned range to become valid.
 *		d. Advance the hardware prod poपूर्णांकer.
 *		e. Tell the next owner we've finished.
 *
 *	5. If we are inserting a CMD_SYNC (we may or may not have been an
 *	   owner), then we need to stick around until it has completed:
 *		a. If we have MSIs, the SMMU can ग_लिखो back पूर्णांकo the CMD_SYNC
 *		   to clear the first 4 bytes.
 *		b. Otherwise, we spin रुकोing क्रम the hardware cons poपूर्णांकer to
 *		   advance past our command.
 *
 * The devil is in the details, particularly the use of locking क्रम handling
 * SYNC completion and मुक्तing up space in the queue beक्रमe we think that it is
 * full.
 */
अटल व्योम __arm_smmu_cmdq_poll_set_valid_map(काष्ठा arm_smmu_cmdq *cmdq,
					       u32 sprod, u32 eprod, bool set)
अणु
	u32 swidx, sbidx, ewidx, ebidx;
	काष्ठा arm_smmu_ll_queue llq = अणु
		.max_n_shअगरt	= cmdq->q.llq.max_n_shअगरt,
		.prod		= sprod,
	पूर्ण;

	ewidx = BIT_WORD(Q_IDX(&llq, eprod));
	ebidx = Q_IDX(&llq, eprod) % BITS_PER_LONG;

	जबतक (llq.prod != eprod) अणु
		अचिन्हित दीर्घ mask;
		atomic_दीर्घ_t *ptr;
		u32 limit = BITS_PER_LONG;

		swidx = BIT_WORD(Q_IDX(&llq, llq.prod));
		sbidx = Q_IDX(&llq, llq.prod) % BITS_PER_LONG;

		ptr = &cmdq->valid_map[swidx];

		अगर ((swidx == ewidx) && (sbidx < ebidx))
			limit = ebidx;

		mask = GENMASK(limit - 1, sbidx);

		/*
		 * The valid bit is the inverse of the wrap bit. This means
		 * that a zero-initialised queue is invalid and, after marking
		 * all entries as valid, they become invalid again when we
		 * wrap.
		 */
		अगर (set) अणु
			atomic_दीर्घ_xor(mask, ptr);
		पूर्ण अन्यथा अणु /* Poll */
			अचिन्हित दीर्घ valid;

			valid = (अच_दीर्घ_उच्च + !!Q_WRP(&llq, llq.prod)) & mask;
			atomic_दीर्घ_cond_पढ़ो_relaxed(ptr, (VAL & mask) == valid);
		पूर्ण

		llq.prod = queue_inc_prod_n(&llq, limit - sbidx);
	पूर्ण
पूर्ण

/* Mark all entries in the range [sprod, eprod) as valid */
अटल व्योम arm_smmu_cmdq_set_valid_map(काष्ठा arm_smmu_cmdq *cmdq,
					u32 sprod, u32 eprod)
अणु
	__arm_smmu_cmdq_poll_set_valid_map(cmdq, sprod, eprod, true);
पूर्ण

/* Wait क्रम all entries in the range [sprod, eprod) to become valid */
अटल व्योम arm_smmu_cmdq_poll_valid_map(काष्ठा arm_smmu_cmdq *cmdq,
					 u32 sprod, u32 eprod)
अणु
	__arm_smmu_cmdq_poll_set_valid_map(cmdq, sprod, eprod, false);
पूर्ण

/* Wait क्रम the command queue to become non-full */
अटल पूर्णांक arm_smmu_cmdq_poll_until_not_full(काष्ठा arm_smmu_device *smmu,
					     काष्ठा arm_smmu_ll_queue *llq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा arm_smmu_queue_poll qp;
	काष्ठा arm_smmu_cmdq *cmdq = &smmu->cmdq;
	पूर्णांक ret = 0;

	/*
	 * Try to update our copy of cons by grabbing exclusive cmdq access. If
	 * that fails, spin until somebody अन्यथा updates it क्रम us.
	 */
	अगर (arm_smmu_cmdq_exclusive_trylock_irqsave(cmdq, flags)) अणु
		WRITE_ONCE(cmdq->q.llq.cons, पढ़ोl_relaxed(cmdq->q.cons_reg));
		arm_smmu_cmdq_exclusive_unlock_irqrestore(cmdq, flags);
		llq->val = READ_ONCE(cmdq->q.llq.val);
		वापस 0;
	पूर्ण

	queue_poll_init(smmu, &qp);
	करो अणु
		llq->val = READ_ONCE(smmu->cmdq.q.llq.val);
		अगर (!queue_full(llq))
			अवरोध;

		ret = queue_poll(&qp);
	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

/*
 * Wait until the SMMU संकेतs a CMD_SYNC completion MSI.
 * Must be called with the cmdq lock held in some capacity.
 */
अटल पूर्णांक __arm_smmu_cmdq_poll_until_msi(काष्ठा arm_smmu_device *smmu,
					  काष्ठा arm_smmu_ll_queue *llq)
अणु
	पूर्णांक ret = 0;
	काष्ठा arm_smmu_queue_poll qp;
	काष्ठा arm_smmu_cmdq *cmdq = &smmu->cmdq;
	u32 *cmd = (u32 *)(Q_ENT(&cmdq->q, llq->prod));

	queue_poll_init(smmu, &qp);

	/*
	 * The MSI won't generate an event, since it's being written back
	 * पूर्णांकo the command queue.
	 */
	qp.wfe = false;
	smp_cond_load_relaxed(cmd, !VAL || (ret = queue_poll(&qp)));
	llq->cons = ret ? llq->prod : queue_inc_prod_n(llq, 1);
	वापस ret;
पूर्ण

/*
 * Wait until the SMMU cons index passes llq->prod.
 * Must be called with the cmdq lock held in some capacity.
 */
अटल पूर्णांक __arm_smmu_cmdq_poll_until_consumed(काष्ठा arm_smmu_device *smmu,
					       काष्ठा arm_smmu_ll_queue *llq)
अणु
	काष्ठा arm_smmu_queue_poll qp;
	काष्ठा arm_smmu_cmdq *cmdq = &smmu->cmdq;
	u32 prod = llq->prod;
	पूर्णांक ret = 0;

	queue_poll_init(smmu, &qp);
	llq->val = READ_ONCE(smmu->cmdq.q.llq.val);
	करो अणु
		अगर (queue_consumed(llq, prod))
			अवरोध;

		ret = queue_poll(&qp);

		/*
		 * This needs to be a पढ़ोl() so that our subsequent call
		 * to arm_smmu_cmdq_shared_tryunlock() can fail accurately.
		 *
		 * Specअगरically, we need to ensure that we observe all
		 * shared_lock()s by other CMD_SYNCs that share our owner,
		 * so that a failing call to tryunlock() means that we're
		 * the last one out and thereक्रमe we can safely advance
		 * cmdq->q.llq.cons. Roughly speaking:
		 *
		 * CPU 0		CPU1			CPU2 (us)
		 *
		 * अगर (sync)
		 * 	shared_lock();
		 *
		 * dma_wmb();
		 * set_valid_map();
		 *
		 * 			अगर (owner) अणु
		 *				poll_valid_map();
		 *				<control dependency>
		 *				ग_लिखोl(prod_reg);
		 *
		 *						पढ़ोl(cons_reg);
		 *						tryunlock();
		 *
		 * Requires us to see CPU 0's shared_lock() acquisition.
		 */
		llq->cons = पढ़ोl(cmdq->q.cons_reg);
	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_cmdq_poll_until_sync(काष्ठा arm_smmu_device *smmu,
					 काष्ठा arm_smmu_ll_queue *llq)
अणु
	अगर (smmu->options & ARM_SMMU_OPT_MSIPOLL)
		वापस __arm_smmu_cmdq_poll_until_msi(smmu, llq);

	वापस __arm_smmu_cmdq_poll_until_consumed(smmu, llq);
पूर्ण

अटल व्योम arm_smmu_cmdq_ग_लिखो_entries(काष्ठा arm_smmu_cmdq *cmdq, u64 *cmds,
					u32 prod, पूर्णांक n)
अणु
	पूर्णांक i;
	काष्ठा arm_smmu_ll_queue llq = अणु
		.max_n_shअगरt	= cmdq->q.llq.max_n_shअगरt,
		.prod		= prod,
	पूर्ण;

	क्रम (i = 0; i < n; ++i) अणु
		u64 *cmd = &cmds[i * CMDQ_ENT_DWORDS];

		prod = queue_inc_prod_n(&llq, i);
		queue_ग_लिखो(Q_ENT(&cmdq->q, prod), cmd, CMDQ_ENT_DWORDS);
	पूर्ण
पूर्ण

/*
 * This is the actual insertion function, and provides the following
 * ordering guarantees to callers:
 *
 * - There is a dma_wmb() beक्रमe publishing any commands to the queue.
 *   This can be relied upon to order prior ग_लिखोs to data काष्ठाures
 *   in memory (such as a CD or an STE) beक्रमe the command.
 *
 * - On completion of a CMD_SYNC, there is a control dependency.
 *   This can be relied upon to order subsequent ग_लिखोs to memory (e.g.
 *   मुक्तing an IOVA) after completion of the CMD_SYNC.
 *
 * - Command insertion is totally ordered, so अगर two CPUs each race to
 *   insert their own list of commands then all of the commands from one
 *   CPU will appear beक्रमe any of the commands from the other CPU.
 */
अटल पूर्णांक arm_smmu_cmdq_issue_cmdlist(काष्ठा arm_smmu_device *smmu,
				       u64 *cmds, पूर्णांक n, bool sync)
अणु
	u64 cmd_sync[CMDQ_ENT_DWORDS];
	u32 prod;
	अचिन्हित दीर्घ flags;
	bool owner;
	काष्ठा arm_smmu_cmdq *cmdq = &smmu->cmdq;
	काष्ठा arm_smmu_ll_queue llq = अणु
		.max_n_shअगरt = cmdq->q.llq.max_n_shअगरt,
	पूर्ण, head = llq;
	पूर्णांक ret = 0;

	/* 1. Allocate some space in the queue */
	local_irq_save(flags);
	llq.val = READ_ONCE(cmdq->q.llq.val);
	करो अणु
		u64 old;

		जबतक (!queue_has_space(&llq, n + sync)) अणु
			local_irq_restore(flags);
			अगर (arm_smmu_cmdq_poll_until_not_full(smmu, &llq))
				dev_err_ratelimited(smmu->dev, "CMDQ timeout\n");
			local_irq_save(flags);
		पूर्ण

		head.cons = llq.cons;
		head.prod = queue_inc_prod_n(&llq, n + sync) |
					     CMDQ_PROD_OWNED_FLAG;

		old = cmpxchg_relaxed(&cmdq->q.llq.val, llq.val, head.val);
		अगर (old == llq.val)
			अवरोध;

		llq.val = old;
	पूर्ण जबतक (1);
	owner = !(llq.prod & CMDQ_PROD_OWNED_FLAG);
	head.prod &= ~CMDQ_PROD_OWNED_FLAG;
	llq.prod &= ~CMDQ_PROD_OWNED_FLAG;

	/*
	 * 2. Write our commands पूर्णांकo the queue
	 * Dependency ordering from the cmpxchg() loop above.
	 */
	arm_smmu_cmdq_ग_लिखो_entries(cmdq, cmds, llq.prod, n);
	अगर (sync) अणु
		prod = queue_inc_prod_n(&llq, n);
		arm_smmu_cmdq_build_sync_cmd(cmd_sync, smmu, prod);
		queue_ग_लिखो(Q_ENT(&cmdq->q, prod), cmd_sync, CMDQ_ENT_DWORDS);

		/*
		 * In order to determine completion of our CMD_SYNC, we must
		 * ensure that the queue can't wrap twice without us noticing.
		 * We achieve that by taking the cmdq lock as shared beक्रमe
		 * marking our slot as valid.
		 */
		arm_smmu_cmdq_shared_lock(cmdq);
	पूर्ण

	/* 3. Mark our slots as valid, ensuring commands are visible first */
	dma_wmb();
	arm_smmu_cmdq_set_valid_map(cmdq, llq.prod, head.prod);

	/* 4. If we are the owner, take control of the SMMU hardware */
	अगर (owner) अणु
		/* a. Wait क्रम previous owner to finish */
		atomic_cond_पढ़ो_relaxed(&cmdq->owner_prod, VAL == llq.prod);

		/* b. Stop gathering work by clearing the owned flag */
		prod = atomic_fetch_andnot_relaxed(CMDQ_PROD_OWNED_FLAG,
						   &cmdq->q.llq.atomic.prod);
		prod &= ~CMDQ_PROD_OWNED_FLAG;

		/*
		 * c. Wait क्रम any gathered work to be written to the queue.
		 * Note that we पढ़ो our own entries so that we have the control
		 * dependency required by (d).
		 */
		arm_smmu_cmdq_poll_valid_map(cmdq, llq.prod, prod);

		/*
		 * d. Advance the hardware prod poपूर्णांकer
		 * Control dependency ordering from the entries becoming valid.
		 */
		ग_लिखोl_relaxed(prod, cmdq->q.prod_reg);

		/*
		 * e. Tell the next owner we're करोne
		 * Make sure we've updated the hardware first, so that we don't
		 * race to update prod and potentially move it backwards.
		 */
		atomic_set_release(&cmdq->owner_prod, prod);
	पूर्ण

	/* 5. If we are inserting a CMD_SYNC, we must रुको क्रम it to complete */
	अगर (sync) अणु
		llq.prod = queue_inc_prod_n(&llq, n);
		ret = arm_smmu_cmdq_poll_until_sync(smmu, &llq);
		अगर (ret) अणु
			dev_err_ratelimited(smmu->dev,
					    "CMD_SYNC timeout at 0x%08x [hwprod 0x%08x, hwcons 0x%08x]\n",
					    llq.prod,
					    पढ़ोl_relaxed(cmdq->q.prod_reg),
					    पढ़ोl_relaxed(cmdq->q.cons_reg));
		पूर्ण

		/*
		 * Try to unlock the cmdq lock. This will fail अगर we're the last
		 * पढ़ोer, in which हाल we can safely update cmdq->q.llq.cons
		 */
		अगर (!arm_smmu_cmdq_shared_tryunlock(cmdq)) अणु
			WRITE_ONCE(cmdq->q.llq.cons, llq.cons);
			arm_smmu_cmdq_shared_unlock(cmdq);
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_cmdq_issue_cmd(काष्ठा arm_smmu_device *smmu,
				   काष्ठा arm_smmu_cmdq_ent *ent)
अणु
	u64 cmd[CMDQ_ENT_DWORDS];

	अगर (arm_smmu_cmdq_build_cmd(cmd, ent)) अणु
		dev_warn(smmu->dev, "ignoring unknown CMDQ opcode 0x%x\n",
			 ent->opcode);
		वापस -EINVAL;
	पूर्ण

	वापस arm_smmu_cmdq_issue_cmdlist(smmu, cmd, 1, false);
पूर्ण

अटल पूर्णांक arm_smmu_cmdq_issue_sync(काष्ठा arm_smmu_device *smmu)
अणु
	वापस arm_smmu_cmdq_issue_cmdlist(smmu, शून्य, 0, true);
पूर्ण

अटल व्योम arm_smmu_cmdq_batch_add(काष्ठा arm_smmu_device *smmu,
				    काष्ठा arm_smmu_cmdq_batch *cmds,
				    काष्ठा arm_smmu_cmdq_ent *cmd)
अणु
	अगर (cmds->num == CMDQ_BATCH_ENTRIES) अणु
		arm_smmu_cmdq_issue_cmdlist(smmu, cmds->cmds, cmds->num, false);
		cmds->num = 0;
	पूर्ण
	arm_smmu_cmdq_build_cmd(&cmds->cmds[cmds->num * CMDQ_ENT_DWORDS], cmd);
	cmds->num++;
पूर्ण

अटल पूर्णांक arm_smmu_cmdq_batch_submit(काष्ठा arm_smmu_device *smmu,
				      काष्ठा arm_smmu_cmdq_batch *cmds)
अणु
	वापस arm_smmu_cmdq_issue_cmdlist(smmu, cmds->cmds, cmds->num, true);
पूर्ण

/* Context descriptor manipulation functions */
व्योम arm_smmu_tlb_inv_asid(काष्ठा arm_smmu_device *smmu, u16 asid)
अणु
	काष्ठा arm_smmu_cmdq_ent cmd = अणु
		.opcode	= smmu->features & ARM_SMMU_FEAT_E2H ?
			CMDQ_OP_TLBI_EL2_ASID : CMDQ_OP_TLBI_NH_ASID,
		.tlbi.asid = asid,
	पूर्ण;

	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);
पूर्ण

अटल व्योम arm_smmu_sync_cd(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
			     पूर्णांक ssid, bool leaf)
अणु
	माप_प्रकार i;
	अचिन्हित दीर्घ flags;
	काष्ठा arm_smmu_master *master;
	काष्ठा arm_smmu_cmdq_batch cmds = अणुपूर्ण;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_cmdq_ent cmd = अणु
		.opcode	= CMDQ_OP_CFGI_CD,
		.cfgi	= अणु
			.ssid	= ssid,
			.leaf	= leaf,
		पूर्ण,
	पूर्ण;

	spin_lock_irqsave(&smmu_करोमुख्य->devices_lock, flags);
	list_क्रम_each_entry(master, &smmu_करोमुख्य->devices, करोमुख्य_head) अणु
		क्रम (i = 0; i < master->num_streams; i++) अणु
			cmd.cfgi.sid = master->streams[i].id;
			arm_smmu_cmdq_batch_add(smmu, &cmds, &cmd);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&smmu_करोमुख्य->devices_lock, flags);

	arm_smmu_cmdq_batch_submit(smmu, &cmds);
पूर्ण

अटल पूर्णांक arm_smmu_alloc_cd_leaf_table(काष्ठा arm_smmu_device *smmu,
					काष्ठा arm_smmu_l1_ctx_desc *l1_desc)
अणु
	माप_प्रकार size = CTXDESC_L2_ENTRIES * (CTXDESC_CD_DWORDS << 3);

	l1_desc->l2ptr = dmam_alloc_coherent(smmu->dev, size,
					     &l1_desc->l2ptr_dma, GFP_KERNEL);
	अगर (!l1_desc->l2ptr) अणु
		dev_warn(smmu->dev,
			 "failed to allocate context descriptor table\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_cd_l1_desc(__le64 *dst,
				      काष्ठा arm_smmu_l1_ctx_desc *l1_desc)
अणु
	u64 val = (l1_desc->l2ptr_dma & CTXDESC_L1_DESC_L2PTR_MASK) |
		  CTXDESC_L1_DESC_V;

	/* See comment in arm_smmu_ग_लिखो_ctx_desc() */
	WRITE_ONCE(*dst, cpu_to_le64(val));
पूर्ण

अटल __le64 *arm_smmu_get_cd_ptr(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				   u32 ssid)
अणु
	__le64 *l1ptr;
	अचिन्हित पूर्णांक idx;
	काष्ठा arm_smmu_l1_ctx_desc *l1_desc;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_ctx_desc_cfg *cdcfg = &smmu_करोमुख्य->s1_cfg.cdcfg;

	अगर (smmu_करोमुख्य->s1_cfg.s1fmt == STRTAB_STE_0_S1FMT_LINEAR)
		वापस cdcfg->cdtab + ssid * CTXDESC_CD_DWORDS;

	idx = ssid >> CTXDESC_SPLIT;
	l1_desc = &cdcfg->l1_desc[idx];
	अगर (!l1_desc->l2ptr) अणु
		अगर (arm_smmu_alloc_cd_leaf_table(smmu, l1_desc))
			वापस शून्य;

		l1ptr = cdcfg->cdtab + idx * CTXDESC_L1_DESC_DWORDS;
		arm_smmu_ग_लिखो_cd_l1_desc(l1ptr, l1_desc);
		/* An invalid L1CD can be cached */
		arm_smmu_sync_cd(smmu_करोमुख्य, ssid, false);
	पूर्ण
	idx = ssid & (CTXDESC_L2_ENTRIES - 1);
	वापस l1_desc->l2ptr + idx * CTXDESC_CD_DWORDS;
पूर्ण

पूर्णांक arm_smmu_ग_लिखो_ctx_desc(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य, पूर्णांक ssid,
			    काष्ठा arm_smmu_ctx_desc *cd)
अणु
	/*
	 * This function handles the following हालs:
	 *
	 * (1) Install primary CD, क्रम normal DMA traffic (SSID = 0).
	 * (2) Install a secondary CD, क्रम SID+SSID traffic.
	 * (3) Update ASID of a CD. Atomically ग_लिखो the first 64 bits of the
	 *     CD, then invalidate the old entry and mappings.
	 * (4) Quiesce the context without clearing the valid bit. Disable
	 *     translation, and ignore any translation fault.
	 * (5) Remove a secondary CD.
	 */
	u64 val;
	bool cd_live;
	__le64 *cdptr;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	अगर (WARN_ON(ssid >= (1 << smmu_करोमुख्य->s1_cfg.s1cdmax)))
		वापस -E2BIG;

	cdptr = arm_smmu_get_cd_ptr(smmu_करोमुख्य, ssid);
	अगर (!cdptr)
		वापस -ENOMEM;

	val = le64_to_cpu(cdptr[0]);
	cd_live = !!(val & CTXDESC_CD_0_V);

	अगर (!cd) अणु /* (5) */
		val = 0;
	पूर्ण अन्यथा अगर (cd == &quiet_cd) अणु /* (4) */
		val |= CTXDESC_CD_0_TCR_EPD0;
	पूर्ण अन्यथा अगर (cd_live) अणु /* (3) */
		val &= ~CTXDESC_CD_0_ASID;
		val |= FIELD_PREP(CTXDESC_CD_0_ASID, cd->asid);
		/*
		 * Until CD+TLB invalidation, both ASIDs may be used क्रम tagging
		 * this substream's traffic
		 */
	पूर्ण अन्यथा अणु /* (1) and (2) */
		cdptr[1] = cpu_to_le64(cd->ttbr & CTXDESC_CD_1_TTB0_MASK);
		cdptr[2] = 0;
		cdptr[3] = cpu_to_le64(cd->mair);

		/*
		 * STE is live, and the SMMU might पढ़ो dwords of this CD in any
		 * order. Ensure that it observes valid values beक्रमe पढ़ोing
		 * V=1.
		 */
		arm_smmu_sync_cd(smmu_करोमुख्य, ssid, true);

		val = cd->tcr |
#अगर_घोषित __BIG_ENDIAN
			CTXDESC_CD_0_ENDI |
#पूर्ण_अगर
			CTXDESC_CD_0_R | CTXDESC_CD_0_A |
			(cd->mm ? 0 : CTXDESC_CD_0_ASET) |
			CTXDESC_CD_0_AA64 |
			FIELD_PREP(CTXDESC_CD_0_ASID, cd->asid) |
			CTXDESC_CD_0_V;

		/* STALL_MODEL==0b10 && CD.S==0 is ILLEGAL */
		अगर (smmu->features & ARM_SMMU_FEAT_STALL_FORCE)
			val |= CTXDESC_CD_0_S;
	पूर्ण

	/*
	 * The SMMU accesses 64-bit values atomically. See IHI0070Ca 3.21.3
	 * "Configuration structures and configuration invalidation completion"
	 *
	 *   The size of single-copy atomic पढ़ोs made by the SMMU is
	 *   IMPLEMENTATION DEFINED but must be at least 64 bits. Any single
	 *   field within an aligned 64-bit span of a काष्ठाure can be altered
	 *   without first making the काष्ठाure invalid.
	 */
	WRITE_ONCE(cdptr[0], cpu_to_le64(val));
	arm_smmu_sync_cd(smmu_करोमुख्य, ssid, true);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_alloc_cd_tables(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	पूर्णांक ret;
	माप_प्रकार l1size;
	माप_प्रकार max_contexts;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_s1_cfg *cfg = &smmu_करोमुख्य->s1_cfg;
	काष्ठा arm_smmu_ctx_desc_cfg *cdcfg = &cfg->cdcfg;

	max_contexts = 1 << cfg->s1cdmax;

	अगर (!(smmu->features & ARM_SMMU_FEAT_2_LVL_CDTAB) ||
	    max_contexts <= CTXDESC_L2_ENTRIES) अणु
		cfg->s1fmt = STRTAB_STE_0_S1FMT_LINEAR;
		cdcfg->num_l1_ents = max_contexts;

		l1size = max_contexts * (CTXDESC_CD_DWORDS << 3);
	पूर्ण अन्यथा अणु
		cfg->s1fmt = STRTAB_STE_0_S1FMT_64K_L2;
		cdcfg->num_l1_ents = DIV_ROUND_UP(max_contexts,
						  CTXDESC_L2_ENTRIES);

		cdcfg->l1_desc = devm_kसुस्मृति(smmu->dev, cdcfg->num_l1_ents,
					      माप(*cdcfg->l1_desc),
					      GFP_KERNEL);
		अगर (!cdcfg->l1_desc)
			वापस -ENOMEM;

		l1size = cdcfg->num_l1_ents * (CTXDESC_L1_DESC_DWORDS << 3);
	पूर्ण

	cdcfg->cdtab = dmam_alloc_coherent(smmu->dev, l1size, &cdcfg->cdtab_dma,
					   GFP_KERNEL);
	अगर (!cdcfg->cdtab) अणु
		dev_warn(smmu->dev, "failed to allocate context descriptor\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_l1;
	पूर्ण

	वापस 0;

err_मुक्त_l1:
	अगर (cdcfg->l1_desc) अणु
		devm_kमुक्त(smmu->dev, cdcfg->l1_desc);
		cdcfg->l1_desc = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम arm_smmu_मुक्त_cd_tables(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	पूर्णांक i;
	माप_प्रकार size, l1size;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_ctx_desc_cfg *cdcfg = &smmu_करोमुख्य->s1_cfg.cdcfg;

	अगर (cdcfg->l1_desc) अणु
		size = CTXDESC_L2_ENTRIES * (CTXDESC_CD_DWORDS << 3);

		क्रम (i = 0; i < cdcfg->num_l1_ents; i++) अणु
			अगर (!cdcfg->l1_desc[i].l2ptr)
				जारी;

			dmam_मुक्त_coherent(smmu->dev, size,
					   cdcfg->l1_desc[i].l2ptr,
					   cdcfg->l1_desc[i].l2ptr_dma);
		पूर्ण
		devm_kमुक्त(smmu->dev, cdcfg->l1_desc);
		cdcfg->l1_desc = शून्य;

		l1size = cdcfg->num_l1_ents * (CTXDESC_L1_DESC_DWORDS << 3);
	पूर्ण अन्यथा अणु
		l1size = cdcfg->num_l1_ents * (CTXDESC_CD_DWORDS << 3);
	पूर्ण

	dmam_मुक्त_coherent(smmu->dev, l1size, cdcfg->cdtab, cdcfg->cdtab_dma);
	cdcfg->cdtab_dma = 0;
	cdcfg->cdtab = शून्य;
पूर्ण

bool arm_smmu_मुक्त_asid(काष्ठा arm_smmu_ctx_desc *cd)
अणु
	bool मुक्त;
	काष्ठा arm_smmu_ctx_desc *old_cd;

	अगर (!cd->asid)
		वापस false;

	मुक्त = refcount_dec_and_test(&cd->refs);
	अगर (मुक्त) अणु
		old_cd = xa_erase(&arm_smmu_asid_xa, cd->asid);
		WARN_ON(old_cd != cd);
	पूर्ण
	वापस मुक्त;
पूर्ण

/* Stream table manipulation functions */
अटल व्योम
arm_smmu_ग_लिखो_strtab_l1_desc(__le64 *dst, काष्ठा arm_smmu_strtab_l1_desc *desc)
अणु
	u64 val = 0;

	val |= FIELD_PREP(STRTAB_L1_DESC_SPAN, desc->span);
	val |= desc->l2ptr_dma & STRTAB_L1_DESC_L2PTR_MASK;

	/* See comment in arm_smmu_ग_लिखो_ctx_desc() */
	WRITE_ONCE(*dst, cpu_to_le64(val));
पूर्ण

अटल व्योम arm_smmu_sync_ste_क्रम_sid(काष्ठा arm_smmu_device *smmu, u32 sid)
अणु
	काष्ठा arm_smmu_cmdq_ent cmd = अणु
		.opcode	= CMDQ_OP_CFGI_STE,
		.cfgi	= अणु
			.sid	= sid,
			.leaf	= true,
		पूर्ण,
	पूर्ण;

	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_strtab_ent(काष्ठा arm_smmu_master *master, u32 sid,
				      __le64 *dst)
अणु
	/*
	 * This is hideously complicated, but we only really care about
	 * three हालs at the moment:
	 *
	 * 1. Invalid (all zero) -> bypass/fault (init)
	 * 2. Bypass/fault -> translation/bypass (attach)
	 * 3. Translation/bypass -> bypass/fault (detach)
	 *
	 * Given that we can't update the STE atomically and the SMMU
	 * करोesn't पढ़ो the thing in a defined order, that leaves us
	 * with the following मुख्यtenance requirements:
	 *
	 * 1. Update Config, वापस (init समय STEs aren't live)
	 * 2. Write everything apart from dword 0, sync, ग_लिखो dword 0, sync
	 * 3. Update Config, sync
	 */
	u64 val = le64_to_cpu(dst[0]);
	bool ste_live = false;
	काष्ठा arm_smmu_device *smmu = शून्य;
	काष्ठा arm_smmu_s1_cfg *s1_cfg = शून्य;
	काष्ठा arm_smmu_s2_cfg *s2_cfg = शून्य;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = शून्य;
	काष्ठा arm_smmu_cmdq_ent prefetch_cmd = अणु
		.opcode		= CMDQ_OP_PREFETCH_CFG,
		.prefetch	= अणु
			.sid	= sid,
		पूर्ण,
	पूर्ण;

	अगर (master) अणु
		smmu_करोमुख्य = master->करोमुख्य;
		smmu = master->smmu;
	पूर्ण

	अगर (smmu_करोमुख्य) अणु
		चयन (smmu_करोमुख्य->stage) अणु
		हाल ARM_SMMU_DOMAIN_S1:
			s1_cfg = &smmu_करोमुख्य->s1_cfg;
			अवरोध;
		हाल ARM_SMMU_DOMAIN_S2:
		हाल ARM_SMMU_DOMAIN_NESTED:
			s2_cfg = &smmu_करोमुख्य->s2_cfg;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (val & STRTAB_STE_0_V) अणु
		चयन (FIELD_GET(STRTAB_STE_0_CFG, val)) अणु
		हाल STRTAB_STE_0_CFG_BYPASS:
			अवरोध;
		हाल STRTAB_STE_0_CFG_S1_TRANS:
		हाल STRTAB_STE_0_CFG_S2_TRANS:
			ste_live = true;
			अवरोध;
		हाल STRTAB_STE_0_CFG_ABORT:
			BUG_ON(!disable_bypass);
			अवरोध;
		शेष:
			BUG(); /* STE corruption */
		पूर्ण
	पूर्ण

	/* Nuke the existing STE_0 value, as we're going to reग_लिखो it */
	val = STRTAB_STE_0_V;

	/* Bypass/fault */
	अगर (!smmu_करोमुख्य || !(s1_cfg || s2_cfg)) अणु
		अगर (!smmu_करोमुख्य && disable_bypass)
			val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_ABORT);
		अन्यथा
			val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_BYPASS);

		dst[0] = cpu_to_le64(val);
		dst[1] = cpu_to_le64(FIELD_PREP(STRTAB_STE_1_SHCFG,
						STRTAB_STE_1_SHCFG_INCOMING));
		dst[2] = 0; /* Nuke the VMID */
		/*
		 * The SMMU can perक्रमm negative caching, so we must sync
		 * the STE regardless of whether the old value was live.
		 */
		अगर (smmu)
			arm_smmu_sync_ste_क्रम_sid(smmu, sid);
		वापस;
	पूर्ण

	अगर (s1_cfg) अणु
		u64 strw = smmu->features & ARM_SMMU_FEAT_E2H ?
			STRTAB_STE_1_STRW_EL2 : STRTAB_STE_1_STRW_NSEL1;

		BUG_ON(ste_live);
		dst[1] = cpu_to_le64(
			 FIELD_PREP(STRTAB_STE_1_S1DSS, STRTAB_STE_1_S1DSS_SSID0) |
			 FIELD_PREP(STRTAB_STE_1_S1CIR, STRTAB_STE_1_S1C_CACHE_WBRA) |
			 FIELD_PREP(STRTAB_STE_1_S1COR, STRTAB_STE_1_S1C_CACHE_WBRA) |
			 FIELD_PREP(STRTAB_STE_1_S1CSH, ARM_SMMU_SH_ISH) |
			 FIELD_PREP(STRTAB_STE_1_STRW, strw));

		अगर (smmu->features & ARM_SMMU_FEAT_STALLS &&
		   !(smmu->features & ARM_SMMU_FEAT_STALL_FORCE))
			dst[1] |= cpu_to_le64(STRTAB_STE_1_S1STALLD);

		val |= (s1_cfg->cdcfg.cdtab_dma & STRTAB_STE_0_S1CTXPTR_MASK) |
			FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_S1_TRANS) |
			FIELD_PREP(STRTAB_STE_0_S1CDMAX, s1_cfg->s1cdmax) |
			FIELD_PREP(STRTAB_STE_0_S1FMT, s1_cfg->s1fmt);
	पूर्ण

	अगर (s2_cfg) अणु
		BUG_ON(ste_live);
		dst[2] = cpu_to_le64(
			 FIELD_PREP(STRTAB_STE_2_S2VMID, s2_cfg->vmid) |
			 FIELD_PREP(STRTAB_STE_2_VTCR, s2_cfg->vtcr) |
#अगर_घोषित __BIG_ENDIAN
			 STRTAB_STE_2_S2ENDI |
#पूर्ण_अगर
			 STRTAB_STE_2_S2PTW | STRTAB_STE_2_S2AA64 |
			 STRTAB_STE_2_S2R);

		dst[3] = cpu_to_le64(s2_cfg->vttbr & STRTAB_STE_3_S2TTB_MASK);

		val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_S2_TRANS);
	पूर्ण

	अगर (master->ats_enabled)
		dst[1] |= cpu_to_le64(FIELD_PREP(STRTAB_STE_1_EATS,
						 STRTAB_STE_1_EATS_TRANS));

	arm_smmu_sync_ste_क्रम_sid(smmu, sid);
	/* See comment in arm_smmu_ग_लिखो_ctx_desc() */
	WRITE_ONCE(dst[0], cpu_to_le64(val));
	arm_smmu_sync_ste_क्रम_sid(smmu, sid);

	/* It's likely that we'll want to use the new STE soon */
	अगर (!(smmu->options & ARM_SMMU_OPT_SKIP_PREFETCH))
		arm_smmu_cmdq_issue_cmd(smmu, &prefetch_cmd);
पूर्ण

अटल व्योम arm_smmu_init_bypass_stes(__le64 *strtab, अचिन्हित पूर्णांक nent)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nent; ++i) अणु
		arm_smmu_ग_लिखो_strtab_ent(शून्य, -1, strtab);
		strtab += STRTAB_STE_DWORDS;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_init_l2_strtab(काष्ठा arm_smmu_device *smmu, u32 sid)
अणु
	माप_प्रकार size;
	व्योम *strtab;
	काष्ठा arm_smmu_strtab_cfg *cfg = &smmu->strtab_cfg;
	काष्ठा arm_smmu_strtab_l1_desc *desc = &cfg->l1_desc[sid >> STRTAB_SPLIT];

	अगर (desc->l2ptr)
		वापस 0;

	size = 1 << (STRTAB_SPLIT + ilog2(STRTAB_STE_DWORDS) + 3);
	strtab = &cfg->strtab[(sid >> STRTAB_SPLIT) * STRTAB_L1_DESC_DWORDS];

	desc->span = STRTAB_SPLIT + 1;
	desc->l2ptr = dmam_alloc_coherent(smmu->dev, size, &desc->l2ptr_dma,
					  GFP_KERNEL);
	अगर (!desc->l2ptr) अणु
		dev_err(smmu->dev,
			"failed to allocate l2 stream table for SID %u\n",
			sid);
		वापस -ENOMEM;
	पूर्ण

	arm_smmu_init_bypass_stes(desc->l2ptr, 1 << STRTAB_SPLIT);
	arm_smmu_ग_लिखो_strtab_l1_desc(strtab, desc);
	वापस 0;
पूर्ण

__maybe_unused
अटल काष्ठा arm_smmu_master *
arm_smmu_find_master(काष्ठा arm_smmu_device *smmu, u32 sid)
अणु
	काष्ठा rb_node *node;
	काष्ठा arm_smmu_stream *stream;

	lockdep_निश्चित_held(&smmu->streams_mutex);

	node = smmu->streams.rb_node;
	जबतक (node) अणु
		stream = rb_entry(node, काष्ठा arm_smmu_stream, node);
		अगर (stream->id < sid)
			node = node->rb_right;
		अन्यथा अगर (stream->id > sid)
			node = node->rb_left;
		अन्यथा
			वापस stream->master;
	पूर्ण

	वापस शून्य;
पूर्ण

/* IRQ and event handlers */
अटल irqवापस_t arm_smmu_evtq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक i;
	काष्ठा arm_smmu_device *smmu = dev;
	काष्ठा arm_smmu_queue *q = &smmu->evtq.q;
	काष्ठा arm_smmu_ll_queue *llq = &q->llq;
	u64 evt[EVTQ_ENT_DWORDS];

	करो अणु
		जबतक (!queue_हटाओ_raw(q, evt)) अणु
			u8 id = FIELD_GET(EVTQ_0_ID, evt[0]);

			dev_info(smmu->dev, "event 0x%02x received:\n", id);
			क्रम (i = 0; i < ARRAY_SIZE(evt); ++i)
				dev_info(smmu->dev, "\t0x%016llx\n",
					 (अचिन्हित दीर्घ दीर्घ)evt[i]);

		पूर्ण

		/*
		 * Not much we can करो on overflow, so scream and pretend we're
		 * trying harder.
		 */
		अगर (queue_sync_prod_in(q) == -EOVERFLOW)
			dev_err(smmu->dev, "EVTQ overflow detected -- events lost\n");
	पूर्ण जबतक (!queue_empty(llq));

	/* Sync our overflow flag, as we believe we're up to speed */
	llq->cons = Q_OVF(llq->prod) | Q_WRP(llq, llq->cons) |
		    Q_IDX(llq, llq->cons);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arm_smmu_handle_ppr(काष्ठा arm_smmu_device *smmu, u64 *evt)
अणु
	u32 sid, ssid;
	u16 grpid;
	bool ssv, last;

	sid = FIELD_GET(PRIQ_0_SID, evt[0]);
	ssv = FIELD_GET(PRIQ_0_SSID_V, evt[0]);
	ssid = ssv ? FIELD_GET(PRIQ_0_SSID, evt[0]) : 0;
	last = FIELD_GET(PRIQ_0_PRG_LAST, evt[0]);
	grpid = FIELD_GET(PRIQ_1_PRG_IDX, evt[1]);

	dev_info(smmu->dev, "unexpected PRI request received:\n");
	dev_info(smmu->dev,
		 "\tsid 0x%08x.0x%05x: [%u%s] %sprivileged %s%s%s access at iova 0x%016llx\n",
		 sid, ssid, grpid, last ? "L" : "",
		 evt[0] & PRIQ_0_PERM_PRIV ? "" : "un",
		 evt[0] & PRIQ_0_PERM_READ ? "R" : "",
		 evt[0] & PRIQ_0_PERM_WRITE ? "W" : "",
		 evt[0] & PRIQ_0_PERM_EXEC ? "X" : "",
		 evt[1] & PRIQ_1_ADDR_MASK);

	अगर (last) अणु
		काष्ठा arm_smmu_cmdq_ent cmd = अणु
			.opcode			= CMDQ_OP_PRI_RESP,
			.substream_valid	= ssv,
			.pri			= अणु
				.sid	= sid,
				.ssid	= ssid,
				.grpid	= grpid,
				.resp	= PRI_RESP_DENY,
			पूर्ण,
		पूर्ण;

		arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	पूर्ण
पूर्ण

अटल irqवापस_t arm_smmu_priq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा arm_smmu_device *smmu = dev;
	काष्ठा arm_smmu_queue *q = &smmu->priq.q;
	काष्ठा arm_smmu_ll_queue *llq = &q->llq;
	u64 evt[PRIQ_ENT_DWORDS];

	करो अणु
		जबतक (!queue_हटाओ_raw(q, evt))
			arm_smmu_handle_ppr(smmu, evt);

		अगर (queue_sync_prod_in(q) == -EOVERFLOW)
			dev_err(smmu->dev, "PRIQ overflow detected -- requests lost\n");
	पूर्ण जबतक (!queue_empty(llq));

	/* Sync our overflow flag, as we believe we're up to speed */
	llq->cons = Q_OVF(llq->prod) | Q_WRP(llq, llq->cons) |
		      Q_IDX(llq, llq->cons);
	queue_sync_cons_out(q);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक arm_smmu_device_disable(काष्ठा arm_smmu_device *smmu);

अटल irqवापस_t arm_smmu_gerror_handler(पूर्णांक irq, व्योम *dev)
अणु
	u32 gerror, gerrorn, active;
	काष्ठा arm_smmu_device *smmu = dev;

	gerror = पढ़ोl_relaxed(smmu->base + ARM_SMMU_GERROR);
	gerrorn = पढ़ोl_relaxed(smmu->base + ARM_SMMU_GERRORN);

	active = gerror ^ gerrorn;
	अगर (!(active & GERROR_ERR_MASK))
		वापस IRQ_NONE; /* No errors pending */

	dev_warn(smmu->dev,
		 "unexpected global error reported (0x%08x), this could be serious\n",
		 active);

	अगर (active & GERROR_SFM_ERR) अणु
		dev_err(smmu->dev, "device has entered Service Failure Mode!\n");
		arm_smmu_device_disable(smmu);
	पूर्ण

	अगर (active & GERROR_MSI_GERROR_ABT_ERR)
		dev_warn(smmu->dev, "GERROR MSI write aborted\n");

	अगर (active & GERROR_MSI_PRIQ_ABT_ERR)
		dev_warn(smmu->dev, "PRIQ MSI write aborted\n");

	अगर (active & GERROR_MSI_EVTQ_ABT_ERR)
		dev_warn(smmu->dev, "EVTQ MSI write aborted\n");

	अगर (active & GERROR_MSI_CMDQ_ABT_ERR)
		dev_warn(smmu->dev, "CMDQ MSI write aborted\n");

	अगर (active & GERROR_PRIQ_ABT_ERR)
		dev_err(smmu->dev, "PRIQ write aborted -- events may have been lost\n");

	अगर (active & GERROR_EVTQ_ABT_ERR)
		dev_err(smmu->dev, "EVTQ write aborted -- events may have been lost\n");

	अगर (active & GERROR_CMDQ_ERR)
		arm_smmu_cmdq_skip_err(smmu);

	ग_लिखोl(gerror, smmu->base + ARM_SMMU_GERRORN);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arm_smmu_combined_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा arm_smmu_device *smmu = dev;

	arm_smmu_evtq_thपढ़ो(irq, dev);
	अगर (smmu->features & ARM_SMMU_FEAT_PRI)
		arm_smmu_priq_thपढ़ो(irq, dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arm_smmu_combined_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	arm_smmu_gerror_handler(irq, dev);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम
arm_smmu_atc_inv_to_cmd(पूर्णांक ssid, अचिन्हित दीर्घ iova, माप_प्रकार size,
			काष्ठा arm_smmu_cmdq_ent *cmd)
अणु
	माप_प्रकार log2_span;
	माप_प्रकार span_mask;
	/* ATC invalidates are always on 4096-bytes pages */
	माप_प्रकार inval_grain_shअगरt = 12;
	अचिन्हित दीर्घ page_start, page_end;

	/*
	 * ATS and PASID:
	 *
	 * If substream_valid is clear, the PCIe TLP is sent without a PASID
	 * prefix. In that हाल all ATC entries within the address range are
	 * invalidated, including those that were requested with a PASID! There
	 * is no way to invalidate only entries without PASID.
	 *
	 * When using STRTAB_STE_1_S1DSS_SSID0 (reserving CD 0 क्रम non-PASID
	 * traffic), translation requests without PASID create ATC entries
	 * without PASID, which must be invalidated with substream_valid clear.
	 * This has the unpleasant side-effect of invalidating all PASID-tagged
	 * ATC entries within the address range.
	 */
	*cmd = (काष्ठा arm_smmu_cmdq_ent) अणु
		.opcode			= CMDQ_OP_ATC_INV,
		.substream_valid	= !!ssid,
		.atc.ssid		= ssid,
	पूर्ण;

	अगर (!size) अणु
		cmd->atc.size = ATC_INV_SIZE_ALL;
		वापस;
	पूर्ण

	page_start	= iova >> inval_grain_shअगरt;
	page_end	= (iova + size - 1) >> inval_grain_shअगरt;

	/*
	 * In an ATS Invalidate Request, the address must be aligned on the
	 * range size, which must be a घातer of two number of page sizes. We
	 * thus have to choose between grossly over-invalidating the region, or
	 * splitting the invalidation पूर्णांकo multiple commands. For simplicity
	 * we'll go with the first solution, but should refine it in the future
	 * अगर multiple commands are shown to be more efficient.
	 *
	 * Find the smallest घातer of two that covers the range. The most
	 * signअगरicant dअगरfering bit between the start and end addresses,
	 * fls(start ^ end), indicates the required span. For example:
	 *
	 * We want to invalidate pages [8; 11]. This is alपढ़ोy the ideal range:
	 *		x = 0b1000 ^ 0b1011 = 0b11
	 *		span = 1 << fls(x) = 4
	 *
	 * To invalidate pages [7; 10], we need to invalidate [0; 15]:
	 *		x = 0b0111 ^ 0b1010 = 0b1101
	 *		span = 1 << fls(x) = 16
	 */
	log2_span	= fls_दीर्घ(page_start ^ page_end);
	span_mask	= (1ULL << log2_span) - 1;

	page_start	&= ~span_mask;

	cmd->atc.addr	= page_start << inval_grain_shअगरt;
	cmd->atc.size	= log2_span;
पूर्ण

अटल पूर्णांक arm_smmu_atc_inv_master(काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक i;
	काष्ठा arm_smmu_cmdq_ent cmd;

	arm_smmu_atc_inv_to_cmd(0, 0, 0, &cmd);

	क्रम (i = 0; i < master->num_streams; i++) अणु
		cmd.atc.sid = master->streams[i].id;
		arm_smmu_cmdq_issue_cmd(master->smmu, &cmd);
	पूर्ण

	वापस arm_smmu_cmdq_issue_sync(master->smmu);
पूर्ण

पूर्णांक arm_smmu_atc_inv_करोमुख्य(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य, पूर्णांक ssid,
			    अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा arm_smmu_cmdq_ent cmd;
	काष्ठा arm_smmu_master *master;
	काष्ठा arm_smmu_cmdq_batch cmds = अणुपूर्ण;

	अगर (!(smmu_करोमुख्य->smmu->features & ARM_SMMU_FEAT_ATS))
		वापस 0;

	/*
	 * Ensure that we've completed prior invalidation of the मुख्य TLBs
	 * beक्रमe we पढ़ो 'nr_ats_masters' in हाल of a concurrent call to
	 * arm_smmu_enable_ats():
	 *
	 *	// unmap()			// arm_smmu_enable_ats()
	 *	TLBI+SYNC			atomic_inc(&nr_ats_masters);
	 *	smp_mb();			[...]
	 *	atomic_पढ़ो(&nr_ats_masters);	pci_enable_ats() // ग_लिखोl()
	 *
	 * Ensures that we always see the incremented 'nr_ats_masters' count अगर
	 * ATS was enabled at the PCI device beक्रमe completion of the TLBI.
	 */
	smp_mb();
	अगर (!atomic_पढ़ो(&smmu_करोमुख्य->nr_ats_masters))
		वापस 0;

	arm_smmu_atc_inv_to_cmd(ssid, iova, size, &cmd);

	spin_lock_irqsave(&smmu_करोमुख्य->devices_lock, flags);
	list_क्रम_each_entry(master, &smmu_करोमुख्य->devices, करोमुख्य_head) अणु
		अगर (!master->ats_enabled)
			जारी;

		क्रम (i = 0; i < master->num_streams; i++) अणु
			cmd.atc.sid = master->streams[i].id;
			arm_smmu_cmdq_batch_add(smmu_करोमुख्य->smmu, &cmds, &cmd);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&smmu_करोमुख्य->devices_lock, flags);

	वापस arm_smmu_cmdq_batch_submit(smmu_करोमुख्य->smmu, &cmds);
पूर्ण

/* IO_PGTABLE API */
अटल व्योम arm_smmu_tlb_inv_context(व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_cmdq_ent cmd;

	/*
	 * NOTE: when io-pgtable is in non-strict mode, we may get here with
	 * PTEs previously cleared by unmaps on the current CPU not yet visible
	 * to the SMMU. We are relying on the dma_wmb() implicit during cmd
	 * insertion to guarantee those are observed beक्रमe the TLBI. Do be
	 * careful, 007.
	 */
	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1) अणु
		arm_smmu_tlb_inv_asid(smmu, smmu_करोमुख्य->s1_cfg.cd.asid);
	पूर्ण अन्यथा अणु
		cmd.opcode	= CMDQ_OP_TLBI_S12_VMALL;
		cmd.tlbi.vmid	= smmu_करोमुख्य->s2_cfg.vmid;
		arm_smmu_cmdq_issue_cmd(smmu, &cmd);
		arm_smmu_cmdq_issue_sync(smmu);
	पूर्ण
	arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, 0, 0, 0);
पूर्ण

अटल व्योम __arm_smmu_tlb_inv_range(काष्ठा arm_smmu_cmdq_ent *cmd,
				     अचिन्हित दीर्घ iova, माप_प्रकार size,
				     माप_प्रकार granule,
				     काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	अचिन्हित दीर्घ end = iova + size, num_pages = 0, tg = 0;
	माप_प्रकार inv_range = granule;
	काष्ठा arm_smmu_cmdq_batch cmds = अणुपूर्ण;

	अगर (!size)
		वापस;

	अगर (smmu->features & ARM_SMMU_FEAT_RANGE_INV) अणु
		/* Get the leaf page size */
		tg = __ffs(smmu_करोमुख्य->करोमुख्य.pgsize_biपंचांगap);

		/* Convert page size of 12,14,16 (log2) to 1,2,3 */
		cmd->tlbi.tg = (tg - 10) / 2;

		/* Determine what level the granule is at */
		cmd->tlbi.ttl = 4 - ((ilog2(granule) - 3) / (tg - 3));

		num_pages = size >> tg;
	पूर्ण

	जबतक (iova < end) अणु
		अगर (smmu->features & ARM_SMMU_FEAT_RANGE_INV) अणु
			/*
			 * On each iteration of the loop, the range is 5 bits
			 * worth of the aligned size reमुख्यing.
			 * The range in pages is:
			 *
			 * range = (num_pages & (0x1f << __ffs(num_pages)))
			 */
			अचिन्हित दीर्घ scale, num;

			/* Determine the घातer of 2 multiple number of pages */
			scale = __ffs(num_pages);
			cmd->tlbi.scale = scale;

			/* Determine how many chunks of 2^scale size we have */
			num = (num_pages >> scale) & CMDQ_TLBI_RANGE_NUM_MAX;
			cmd->tlbi.num = num - 1;

			/* range is num * 2^scale * pgsize */
			inv_range = num << (scale + tg);

			/* Clear out the lower order bits क्रम the next iteration */
			num_pages -= num << scale;
		पूर्ण

		cmd->tlbi.addr = iova;
		arm_smmu_cmdq_batch_add(smmu, &cmds, cmd);
		iova += inv_range;
	पूर्ण
	arm_smmu_cmdq_batch_submit(smmu, &cmds);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_range_करोमुख्य(अचिन्हित दीर्घ iova, माप_प्रकार size,
					  माप_प्रकार granule, bool leaf,
					  काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	काष्ठा arm_smmu_cmdq_ent cmd = अणु
		.tlbi = अणु
			.leaf	= leaf,
		पूर्ण,
	पूर्ण;

	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1) अणु
		cmd.opcode	= smmu_करोमुख्य->smmu->features & ARM_SMMU_FEAT_E2H ?
				  CMDQ_OP_TLBI_EL2_VA : CMDQ_OP_TLBI_NH_VA;
		cmd.tlbi.asid	= smmu_करोमुख्य->s1_cfg.cd.asid;
	पूर्ण अन्यथा अणु
		cmd.opcode	= CMDQ_OP_TLBI_S2_IPA;
		cmd.tlbi.vmid	= smmu_करोमुख्य->s2_cfg.vmid;
	पूर्ण
	__arm_smmu_tlb_inv_range(&cmd, iova, size, granule, smmu_करोमुख्य);

	/*
	 * Unक्रमtunately, this can't be leaf-only since we may have
	 * zapped an entire table.
	 */
	arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, 0, iova, size);
पूर्ण

व्योम arm_smmu_tlb_inv_range_asid(अचिन्हित दीर्घ iova, माप_प्रकार size, पूर्णांक asid,
				 माप_प्रकार granule, bool leaf,
				 काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	काष्ठा arm_smmu_cmdq_ent cmd = अणु
		.opcode	= smmu_करोमुख्य->smmu->features & ARM_SMMU_FEAT_E2H ?
			  CMDQ_OP_TLBI_EL2_VA : CMDQ_OP_TLBI_NH_VA,
		.tlbi = अणु
			.asid	= asid,
			.leaf	= leaf,
		पूर्ण,
	पूर्ण;

	__arm_smmu_tlb_inv_range(&cmd, iova, size, granule, smmu_करोमुख्य);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_page_nosync(काष्ठा iommu_iotlb_gather *gather,
					 अचिन्हित दीर्घ iova, माप_प्रकार granule,
					 व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा iommu_करोमुख्य *करोमुख्य = &smmu_करोमुख्य->करोमुख्य;

	iommu_iotlb_gather_add_page(करोमुख्य, gather, iova, granule);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_walk(अचिन्हित दीर्घ iova, माप_प्रकार size,
				  माप_प्रकार granule, व्योम *cookie)
अणु
	arm_smmu_tlb_inv_range_करोमुख्य(iova, size, granule, false, cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops arm_smmu_flush_ops = अणु
	.tlb_flush_all	= arm_smmu_tlb_inv_context,
	.tlb_flush_walk = arm_smmu_tlb_inv_walk,
	.tlb_add_page	= arm_smmu_tlb_inv_page_nosync,
पूर्ण;

/* IOMMU API */
अटल bool arm_smmu_capable(क्रमागत iommu_cap cap)
अणु
	चयन (cap) अणु
	हाल IOMMU_CAP_CACHE_COHERENCY:
		वापस true;
	हाल IOMMU_CAP_NOEXEC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा iommu_करोमुख्य *arm_smmu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED &&
	    type != IOMMU_DOMAIN_DMA &&
	    type != IOMMU_DOMAIN_IDENTITY)
		वापस शून्य;

	/*
	 * Allocate the करोमुख्य and initialise some of its data काष्ठाures.
	 * We can't really do anything meaningful until we've added a
	 * master.
	 */
	smmu_करोमुख्य = kzalloc(माप(*smmu_करोमुख्य), GFP_KERNEL);
	अगर (!smmu_करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&smmu_करोमुख्य->करोमुख्य)) अणु
		kमुक्त(smmu_करोमुख्य);
		वापस शून्य;
	पूर्ण

	mutex_init(&smmu_करोमुख्य->init_mutex);
	INIT_LIST_HEAD(&smmu_करोमुख्य->devices);
	spin_lock_init(&smmu_करोमुख्य->devices_lock);
	INIT_LIST_HEAD(&smmu_करोमुख्य->mmu_notअगरiers);

	वापस &smmu_करोमुख्य->करोमुख्य;
पूर्ण

अटल पूर्णांक arm_smmu_biपंचांगap_alloc(अचिन्हित दीर्घ *map, पूर्णांक span)
अणु
	पूर्णांक idx, size = 1 << span;

	करो अणु
		idx = find_first_zero_bit(map, size);
		अगर (idx == size)
			वापस -ENOSPC;
	पूर्ण जबतक (test_and_set_bit(idx, map));

	वापस idx;
पूर्ण

अटल व्योम arm_smmu_biपंचांगap_मुक्त(अचिन्हित दीर्घ *map, पूर्णांक idx)
अणु
	clear_bit(idx, map);
पूर्ण

अटल व्योम arm_smmu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	iommu_put_dma_cookie(करोमुख्य);
	मुक्त_io_pgtable_ops(smmu_करोमुख्य->pgtbl_ops);

	/* Free the CD and ASID, अगर we allocated them */
	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1) अणु
		काष्ठा arm_smmu_s1_cfg *cfg = &smmu_करोमुख्य->s1_cfg;

		/* Prevent SVA from touching the CD जबतक we're मुक्तing it */
		mutex_lock(&arm_smmu_asid_lock);
		अगर (cfg->cdcfg.cdtab)
			arm_smmu_मुक्त_cd_tables(smmu_करोमुख्य);
		arm_smmu_मुक्त_asid(&cfg->cd);
		mutex_unlock(&arm_smmu_asid_lock);
	पूर्ण अन्यथा अणु
		काष्ठा arm_smmu_s2_cfg *cfg = &smmu_करोमुख्य->s2_cfg;
		अगर (cfg->vmid)
			arm_smmu_biपंचांगap_मुक्त(smmu->vmid_map, cfg->vmid);
	पूर्ण

	kमुक्त(smmu_करोमुख्य);
पूर्ण

अटल पूर्णांक arm_smmu_करोमुख्य_finalise_s1(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				       काष्ठा arm_smmu_master *master,
				       काष्ठा io_pgtable_cfg *pgtbl_cfg)
अणु
	पूर्णांक ret;
	u32 asid;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_s1_cfg *cfg = &smmu_करोमुख्य->s1_cfg;
	typeof(&pgtbl_cfg->arm_lpae_s1_cfg.tcr) tcr = &pgtbl_cfg->arm_lpae_s1_cfg.tcr;

	refcount_set(&cfg->cd.refs, 1);

	/* Prevent SVA from modअगरying the ASID until it is written to the CD */
	mutex_lock(&arm_smmu_asid_lock);
	ret = xa_alloc(&arm_smmu_asid_xa, &asid, &cfg->cd,
		       XA_LIMIT(1, (1 << smmu->asid_bits) - 1), GFP_KERNEL);
	अगर (ret)
		जाओ out_unlock;

	cfg->s1cdmax = master->ssid_bits;

	ret = arm_smmu_alloc_cd_tables(smmu_करोमुख्य);
	अगर (ret)
		जाओ out_मुक्त_asid;

	cfg->cd.asid	= (u16)asid;
	cfg->cd.ttbr	= pgtbl_cfg->arm_lpae_s1_cfg.ttbr;
	cfg->cd.tcr	= FIELD_PREP(CTXDESC_CD_0_TCR_T0SZ, tcr->tsz) |
			  FIELD_PREP(CTXDESC_CD_0_TCR_TG0, tcr->tg) |
			  FIELD_PREP(CTXDESC_CD_0_TCR_IRGN0, tcr->irgn) |
			  FIELD_PREP(CTXDESC_CD_0_TCR_ORGN0, tcr->orgn) |
			  FIELD_PREP(CTXDESC_CD_0_TCR_SH0, tcr->sh) |
			  FIELD_PREP(CTXDESC_CD_0_TCR_IPS, tcr->ips) |
			  CTXDESC_CD_0_TCR_EPD1 | CTXDESC_CD_0_AA64;
	cfg->cd.mair	= pgtbl_cfg->arm_lpae_s1_cfg.mair;

	/*
	 * Note that this will end up calling arm_smmu_sync_cd() beक्रमe
	 * the master has been added to the devices list क्रम this करोमुख्य.
	 * This isn't an issue because the STE hasn't been installed yet.
	 */
	ret = arm_smmu_ग_लिखो_ctx_desc(smmu_करोमुख्य, 0, &cfg->cd);
	अगर (ret)
		जाओ out_मुक्त_cd_tables;

	mutex_unlock(&arm_smmu_asid_lock);
	वापस 0;

out_मुक्त_cd_tables:
	arm_smmu_मुक्त_cd_tables(smmu_करोमुख्य);
out_मुक्त_asid:
	arm_smmu_मुक्त_asid(&cfg->cd);
out_unlock:
	mutex_unlock(&arm_smmu_asid_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_करोमुख्य_finalise_s2(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				       काष्ठा arm_smmu_master *master,
				       काष्ठा io_pgtable_cfg *pgtbl_cfg)
अणु
	पूर्णांक vmid;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_s2_cfg *cfg = &smmu_करोमुख्य->s2_cfg;
	typeof(&pgtbl_cfg->arm_lpae_s2_cfg.vtcr) vtcr;

	vmid = arm_smmu_biपंचांगap_alloc(smmu->vmid_map, smmu->vmid_bits);
	अगर (vmid < 0)
		वापस vmid;

	vtcr = &pgtbl_cfg->arm_lpae_s2_cfg.vtcr;
	cfg->vmid	= (u16)vmid;
	cfg->vttbr	= pgtbl_cfg->arm_lpae_s2_cfg.vttbr;
	cfg->vtcr	= FIELD_PREP(STRTAB_STE_2_VTCR_S2T0SZ, vtcr->tsz) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2SL0, vtcr->sl) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2IR0, vtcr->irgn) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2OR0, vtcr->orgn) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2SH0, vtcr->sh) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2TG, vtcr->tg) |
			  FIELD_PREP(STRTAB_STE_2_VTCR_S2PS, vtcr->ps);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_करोमुख्य_finalise(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ ias, oas;
	क्रमागत io_pgtable_fmt fmt;
	काष्ठा io_pgtable_cfg pgtbl_cfg;
	काष्ठा io_pgtable_ops *pgtbl_ops;
	पूर्णांक (*finalise_stage_fn)(काष्ठा arm_smmu_करोमुख्य *,
				 काष्ठा arm_smmu_master *,
				 काष्ठा io_pgtable_cfg *);
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	अगर (करोमुख्य->type == IOMMU_DOMAIN_IDENTITY) अणु
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_BYPASS;
		वापस 0;
	पूर्ण

	/* Restrict the stage to what we can actually support */
	अगर (!(smmu->features & ARM_SMMU_FEAT_TRANS_S1))
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_S2;
	अगर (!(smmu->features & ARM_SMMU_FEAT_TRANS_S2))
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_S1;

	चयन (smmu_करोमुख्य->stage) अणु
	हाल ARM_SMMU_DOMAIN_S1:
		ias = (smmu->features & ARM_SMMU_FEAT_VAX) ? 52 : 48;
		ias = min_t(अचिन्हित दीर्घ, ias, VA_BITS);
		oas = smmu->ias;
		fmt = ARM_64_LPAE_S1;
		finalise_stage_fn = arm_smmu_करोमुख्य_finalise_s1;
		अवरोध;
	हाल ARM_SMMU_DOMAIN_NESTED:
	हाल ARM_SMMU_DOMAIN_S2:
		ias = smmu->ias;
		oas = smmu->oas;
		fmt = ARM_64_LPAE_S2;
		finalise_stage_fn = arm_smmu_करोमुख्य_finalise_s2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pgtbl_cfg = (काष्ठा io_pgtable_cfg) अणु
		.pgsize_biपंचांगap	= smmu->pgsize_biपंचांगap,
		.ias		= ias,
		.oas		= oas,
		.coherent_walk	= smmu->features & ARM_SMMU_FEAT_COHERENCY,
		.tlb		= &arm_smmu_flush_ops,
		.iommu_dev	= smmu->dev,
	पूर्ण;

	अगर (!iommu_get_dma_strict(करोमुख्य))
		pgtbl_cfg.quirks |= IO_PGTABLE_QUIRK_NON_STRICT;

	pgtbl_ops = alloc_io_pgtable_ops(fmt, &pgtbl_cfg, smmu_करोमुख्य);
	अगर (!pgtbl_ops)
		वापस -ENOMEM;

	करोमुख्य->pgsize_biपंचांगap = pgtbl_cfg.pgsize_biपंचांगap;
	करोमुख्य->geometry.aperture_end = (1UL << pgtbl_cfg.ias) - 1;
	करोमुख्य->geometry.क्रमce_aperture = true;

	ret = finalise_stage_fn(smmu_करोमुख्य, master, &pgtbl_cfg);
	अगर (ret < 0) अणु
		मुक्त_io_pgtable_ops(pgtbl_ops);
		वापस ret;
	पूर्ण

	smmu_करोमुख्य->pgtbl_ops = pgtbl_ops;
	वापस 0;
पूर्ण

अटल __le64 *arm_smmu_get_step_क्रम_sid(काष्ठा arm_smmu_device *smmu, u32 sid)
अणु
	__le64 *step;
	काष्ठा arm_smmu_strtab_cfg *cfg = &smmu->strtab_cfg;

	अगर (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB) अणु
		काष्ठा arm_smmu_strtab_l1_desc *l1_desc;
		पूर्णांक idx;

		/* Two-level walk */
		idx = (sid >> STRTAB_SPLIT) * STRTAB_L1_DESC_DWORDS;
		l1_desc = &cfg->l1_desc[idx];
		idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
		step = &l1_desc->l2ptr[idx];
	पूर्ण अन्यथा अणु
		/* Simple linear lookup */
		step = &cfg->strtab[sid * STRTAB_STE_DWORDS];
	पूर्ण

	वापस step;
पूर्ण

अटल व्योम arm_smmu_install_ste_क्रम_dev(काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक i, j;
	काष्ठा arm_smmu_device *smmu = master->smmu;

	क्रम (i = 0; i < master->num_streams; ++i) अणु
		u32 sid = master->streams[i].id;
		__le64 *step = arm_smmu_get_step_क्रम_sid(smmu, sid);

		/* Bridged PCI devices may end up with duplicated IDs */
		क्रम (j = 0; j < i; j++)
			अगर (master->streams[j].id == sid)
				अवरोध;
		अगर (j < i)
			जारी;

		arm_smmu_ग_लिखो_strtab_ent(master, sid, step);
	पूर्ण
पूर्ण

अटल bool arm_smmu_ats_supported(काष्ठा arm_smmu_master *master)
अणु
	काष्ठा device *dev = master->dev;
	काष्ठा arm_smmu_device *smmu = master->smmu;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!(smmu->features & ARM_SMMU_FEAT_ATS))
		वापस false;

	अगर (!(fwspec->flags & IOMMU_FWSPEC_PCI_RC_ATS))
		वापस false;

	वापस dev_is_pci(dev) && pci_ats_supported(to_pci_dev(dev));
पूर्ण

अटल व्योम arm_smmu_enable_ats(काष्ठा arm_smmu_master *master)
अणु
	माप_प्रकार stu;
	काष्ठा pci_dev *pdev;
	काष्ठा arm_smmu_device *smmu = master->smmu;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = master->करोमुख्य;

	/* Don't enable ATS at the endpoint if it's not enabled in the STE */
	अगर (!master->ats_enabled)
		वापस;

	/* Smallest Translation Unit: log2 of the smallest supported granule */
	stu = __ffs(smmu->pgsize_biपंचांगap);
	pdev = to_pci_dev(master->dev);

	atomic_inc(&smmu_करोमुख्य->nr_ats_masters);
	arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, 0, 0, 0);
	अगर (pci_enable_ats(pdev, stu))
		dev_err(master->dev, "Failed to enable ATS (STU %zu)\n", stu);
पूर्ण

अटल व्योम arm_smmu_disable_ats(काष्ठा arm_smmu_master *master)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = master->करोमुख्य;

	अगर (!master->ats_enabled)
		वापस;

	pci_disable_ats(to_pci_dev(master->dev));
	/*
	 * Ensure ATS is disabled at the endpoपूर्णांक beक्रमe we issue the
	 * ATC invalidation via the SMMU.
	 */
	wmb();
	arm_smmu_atc_inv_master(master);
	atomic_dec(&smmu_करोमुख्य->nr_ats_masters);
पूर्ण

अटल पूर्णांक arm_smmu_enable_pasid(काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक ret;
	पूर्णांक features;
	पूर्णांक num_pasids;
	काष्ठा pci_dev *pdev;

	अगर (!dev_is_pci(master->dev))
		वापस -ENODEV;

	pdev = to_pci_dev(master->dev);

	features = pci_pasid_features(pdev);
	अगर (features < 0)
		वापस features;

	num_pasids = pci_max_pasids(pdev);
	अगर (num_pasids <= 0)
		वापस num_pasids;

	ret = pci_enable_pasid(pdev, features);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to enable PASID\n");
		वापस ret;
	पूर्ण

	master->ssid_bits = min_t(u8, ilog2(num_pasids),
				  master->smmu->ssid_bits);
	वापस 0;
पूर्ण

अटल व्योम arm_smmu_disable_pasid(काष्ठा arm_smmu_master *master)
अणु
	काष्ठा pci_dev *pdev;

	अगर (!dev_is_pci(master->dev))
		वापस;

	pdev = to_pci_dev(master->dev);

	अगर (!pdev->pasid_enabled)
		वापस;

	master->ssid_bits = 0;
	pci_disable_pasid(pdev);
पूर्ण

अटल व्योम arm_smmu_detach_dev(काष्ठा arm_smmu_master *master)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = master->करोमुख्य;

	अगर (!smmu_करोमुख्य)
		वापस;

	arm_smmu_disable_ats(master);

	spin_lock_irqsave(&smmu_करोमुख्य->devices_lock, flags);
	list_del(&master->करोमुख्य_head);
	spin_unlock_irqrestore(&smmu_करोमुख्य->devices_lock, flags);

	master->करोमुख्य = शून्य;
	master->ats_enabled = false;
	arm_smmu_install_ste_क्रम_dev(master);
पूर्ण

अटल पूर्णांक arm_smmu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_device *smmu;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_master *master;

	अगर (!fwspec)
		वापस -ENOENT;

	master = dev_iommu_priv_get(dev);
	smmu = master->smmu;

	/*
	 * Checking that SVA is disabled ensures that this device isn't bound to
	 * any mm, and can be safely detached from its old करोमुख्य. Bonds cannot
	 * be हटाओd concurrently since we're holding the group mutex.
	 */
	अगर (arm_smmu_master_sva_enabled(master)) अणु
		dev_err(dev, "cannot attach - SVA enabled\n");
		वापस -EBUSY;
	पूर्ण

	arm_smmu_detach_dev(master);

	mutex_lock(&smmu_करोमुख्य->init_mutex);

	अगर (!smmu_करोमुख्य->smmu) अणु
		smmu_करोमुख्य->smmu = smmu;
		ret = arm_smmu_करोमुख्य_finalise(करोमुख्य, master);
		अगर (ret) अणु
			smmu_करोमुख्य->smmu = शून्य;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (smmu_करोमुख्य->smmu != smmu) अणु
		dev_err(dev,
			"cannot attach to SMMU %s (upstream of %s)\n",
			dev_name(smmu_करोमुख्य->smmu->dev),
			dev_name(smmu->dev));
		ret = -ENXIO;
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1 &&
		   master->ssid_bits != smmu_करोमुख्य->s1_cfg.s1cdmax) अणु
		dev_err(dev,
			"cannot attach to incompatible domain (%u SSID bits != %u)\n",
			smmu_करोमुख्य->s1_cfg.s1cdmax, master->ssid_bits);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	master->करोमुख्य = smmu_करोमुख्य;

	अगर (smmu_करोमुख्य->stage != ARM_SMMU_DOMAIN_BYPASS)
		master->ats_enabled = arm_smmu_ats_supported(master);

	arm_smmu_install_ste_क्रम_dev(master);

	spin_lock_irqsave(&smmu_करोमुख्य->devices_lock, flags);
	list_add(&master->करोमुख्य_head, &smmu_करोमुख्य->devices);
	spin_unlock_irqrestore(&smmu_करोमुख्य->devices_lock, flags);

	arm_smmu_enable_ats(master);

out_unlock:
	mutex_unlock(&smmu_करोमुख्य->init_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा io_pgtable_ops *ops = to_smmu_करोमुख्य(करोमुख्य)->pgtbl_ops;

	अगर (!ops)
		वापस -ENODEV;

	वापस ops->map(ops, iova, paddr, size, prot, gfp);
पूर्ण

अटल माप_प्रकार arm_smmu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			     माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable_ops *ops = smmu_करोमुख्य->pgtbl_ops;

	अगर (!ops)
		वापस 0;

	वापस ops->unmap(ops, iova, size, gather);
पूर्ण

अटल व्योम arm_smmu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);

	अगर (smmu_करोमुख्य->smmu)
		arm_smmu_tlb_inv_context(smmu_करोमुख्य);
पूर्ण

अटल व्योम arm_smmu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);

	अगर (!gather->pgsize)
		वापस;

	arm_smmu_tlb_inv_range_करोमुख्य(gather->start,
				      gather->end - gather->start + 1,
				      gather->pgsize, true, smmu_करोमुख्य);
पूर्ण

अटल phys_addr_t
arm_smmu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t iova)
अणु
	काष्ठा io_pgtable_ops *ops = to_smmu_करोमुख्य(करोमुख्य)->pgtbl_ops;

	अगर (करोमुख्य->type == IOMMU_DOMAIN_IDENTITY)
		वापस iova;

	अगर (!ops)
		वापस 0;

	वापस ops->iova_to_phys(ops, iova);
पूर्ण

अटल काष्ठा platक्रमm_driver arm_smmu_driver;

अटल
काष्ठा arm_smmu_device *arm_smmu_get_by_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev = driver_find_device_by_fwnode(&arm_smmu_driver.driver,
							  fwnode);
	put_device(dev);
	वापस dev ? dev_get_drvdata(dev) : शून्य;
पूर्ण

अटल bool arm_smmu_sid_in_range(काष्ठा arm_smmu_device *smmu, u32 sid)
अणु
	अचिन्हित दीर्घ limit = smmu->strtab_cfg.num_l1_ents;

	अगर (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB)
		limit *= 1UL << STRTAB_SPLIT;

	वापस sid < limit;
पूर्ण

अटल पूर्णांक arm_smmu_insert_master(काष्ठा arm_smmu_device *smmu,
				  काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा arm_smmu_stream *new_stream, *cur_stream;
	काष्ठा rb_node **new_node, *parent_node = शून्य;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(master->dev);

	master->streams = kसुस्मृति(fwspec->num_ids, माप(*master->streams),
				  GFP_KERNEL);
	अगर (!master->streams)
		वापस -ENOMEM;
	master->num_streams = fwspec->num_ids;

	mutex_lock(&smmu->streams_mutex);
	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		u32 sid = fwspec->ids[i];

		new_stream = &master->streams[i];
		new_stream->id = sid;
		new_stream->master = master;

		/*
		 * Check the SIDs are in range of the SMMU and our stream table
		 */
		अगर (!arm_smmu_sid_in_range(smmu, sid)) अणु
			ret = -दुस्फल;
			अवरोध;
		पूर्ण

		/* Ensure l2 strtab is initialised */
		अगर (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB) अणु
			ret = arm_smmu_init_l2_strtab(smmu, sid);
			अगर (ret)
				अवरोध;
		पूर्ण

		/* Insert पूर्णांकo SID tree */
		new_node = &(smmu->streams.rb_node);
		जबतक (*new_node) अणु
			cur_stream = rb_entry(*new_node, काष्ठा arm_smmu_stream,
					      node);
			parent_node = *new_node;
			अगर (cur_stream->id > new_stream->id) अणु
				new_node = &((*new_node)->rb_left);
			पूर्ण अन्यथा अगर (cur_stream->id < new_stream->id) अणु
				new_node = &((*new_node)->rb_right);
			पूर्ण अन्यथा अणु
				dev_warn(master->dev,
					 "stream %u already in tree\n",
					 cur_stream->id);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret)
			अवरोध;

		rb_link_node(&new_stream->node, parent_node, new_node);
		rb_insert_color(&new_stream->node, &smmu->streams);
	पूर्ण

	अगर (ret) अणु
		क्रम (i--; i >= 0; i--)
			rb_erase(&master->streams[i].node, &smmu->streams);
		kमुक्त(master->streams);
	पूर्ण
	mutex_unlock(&smmu->streams_mutex);

	वापस ret;
पूर्ण

अटल व्योम arm_smmu_हटाओ_master(काष्ठा arm_smmu_master *master)
अणु
	पूर्णांक i;
	काष्ठा arm_smmu_device *smmu = master->smmu;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(master->dev);

	अगर (!smmu || !master->streams)
		वापस;

	mutex_lock(&smmu->streams_mutex);
	क्रम (i = 0; i < fwspec->num_ids; i++)
		rb_erase(&master->streams[i].node, &smmu->streams);
	mutex_unlock(&smmu->streams_mutex);

	kमुक्त(master->streams);
पूर्ण

अटल काष्ठा iommu_ops arm_smmu_ops;

अटल काष्ठा iommu_device *arm_smmu_probe_device(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा arm_smmu_device *smmu;
	काष्ठा arm_smmu_master *master;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &arm_smmu_ops)
		वापस ERR_PTR(-ENODEV);

	अगर (WARN_ON_ONCE(dev_iommu_priv_get(dev)))
		वापस ERR_PTR(-EBUSY);

	smmu = arm_smmu_get_by_fwnode(fwspec->iommu_fwnode);
	अगर (!smmu)
		वापस ERR_PTR(-ENODEV);

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस ERR_PTR(-ENOMEM);

	master->dev = dev;
	master->smmu = smmu;
	INIT_LIST_HEAD(&master->bonds);
	dev_iommu_priv_set(dev, master);

	ret = arm_smmu_insert_master(smmu, master);
	अगर (ret)
		जाओ err_मुक्त_master;

	device_property_पढ़ो_u32(dev, "pasid-num-bits", &master->ssid_bits);
	master->ssid_bits = min(smmu->ssid_bits, master->ssid_bits);

	/*
	 * Note that PASID must be enabled beक्रमe, and disabled after ATS:
	 * PCI Express Base 4.0r1.0 - 10.5.1.3 ATS Control Register
	 *
	 *   Behavior is undefined अगर this bit is Set and the value of the PASID
	 *   Enable, Execute Requested Enable, or Privileged Mode Requested bits
	 *   are changed.
	 */
	arm_smmu_enable_pasid(master);

	अगर (!(smmu->features & ARM_SMMU_FEAT_2_LVL_CDTAB))
		master->ssid_bits = min_t(u8, master->ssid_bits,
					  CTXDESC_LINEAR_CDMAX);

	वापस &smmu->iommu;

err_मुक्त_master:
	kमुक्त(master);
	dev_iommu_priv_set(dev, शून्य);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम arm_smmu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_master *master;

	अगर (!fwspec || fwspec->ops != &arm_smmu_ops)
		वापस;

	master = dev_iommu_priv_get(dev);
	WARN_ON(arm_smmu_master_sva_enabled(master));
	arm_smmu_detach_dev(master);
	arm_smmu_disable_pasid(master);
	arm_smmu_हटाओ_master(master);
	kमुक्त(master);
	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल काष्ठा iommu_group *arm_smmu_device_group(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;

	/*
	 * We करोn't support devices sharing stream IDs other than PCI RID
	 * aliases, since the necessary ID-to-device lookup becomes rather
	 * impractical given a potential sparse 32-bit stream ID space.
	 */
	अगर (dev_is_pci(dev))
		group = pci_device_group(dev);
	अन्यथा
		group = generic_device_group(dev);

	वापस group;
पूर्ण

अटल पूर्णांक arm_smmu_enable_nesting(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	पूर्णांक ret = 0;

	mutex_lock(&smmu_करोमुख्य->init_mutex);
	अगर (smmu_करोमुख्य->smmu)
		ret = -EPERM;
	अन्यथा
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_NESTED;
	mutex_unlock(&smmu_करोमुख्य->init_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	वापस iommu_fwspec_add_ids(dev, args->args, 1);
पूर्ण

अटल व्योम arm_smmu_get_resv_regions(काष्ठा device *dev,
				      काष्ठा list_head *head)
अणु
	काष्ठा iommu_resv_region *region;
	पूर्णांक prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	region = iommu_alloc_resv_region(MSI_IOVA_BASE, MSI_IOVA_LENGTH,
					 prot, IOMMU_RESV_SW_MSI);
	अगर (!region)
		वापस;

	list_add_tail(&region->list, head);

	iommu_dma_get_resv_regions(dev, head);
पूर्ण

अटल bool arm_smmu_dev_has_feature(काष्ठा device *dev,
				     क्रमागत iommu_dev_features feat)
अणु
	काष्ठा arm_smmu_master *master = dev_iommu_priv_get(dev);

	अगर (!master)
		वापस false;

	चयन (feat) अणु
	हाल IOMMU_DEV_FEAT_SVA:
		वापस arm_smmu_master_sva_supported(master);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool arm_smmu_dev_feature_enabled(काष्ठा device *dev,
					 क्रमागत iommu_dev_features feat)
अणु
	काष्ठा arm_smmu_master *master = dev_iommu_priv_get(dev);

	अगर (!master)
		वापस false;

	चयन (feat) अणु
	हाल IOMMU_DEV_FEAT_SVA:
		वापस arm_smmu_master_sva_enabled(master);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_dev_enable_feature(काष्ठा device *dev,
				       क्रमागत iommu_dev_features feat)
अणु
	अगर (!arm_smmu_dev_has_feature(dev, feat))
		वापस -ENODEV;

	अगर (arm_smmu_dev_feature_enabled(dev, feat))
		वापस -EBUSY;

	चयन (feat) अणु
	हाल IOMMU_DEV_FEAT_SVA:
		वापस arm_smmu_master_enable_sva(dev_iommu_priv_get(dev));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_dev_disable_feature(काष्ठा device *dev,
					क्रमागत iommu_dev_features feat)
अणु
	अगर (!arm_smmu_dev_feature_enabled(dev, feat))
		वापस -EINVAL;

	चयन (feat) अणु
	हाल IOMMU_DEV_FEAT_SVA:
		वापस arm_smmu_master_disable_sva(dev_iommu_priv_get(dev));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा iommu_ops arm_smmu_ops = अणु
	.capable		= arm_smmu_capable,
	.करोमुख्य_alloc		= arm_smmu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त		= arm_smmu_करोमुख्य_मुक्त,
	.attach_dev		= arm_smmu_attach_dev,
	.map			= arm_smmu_map,
	.unmap			= arm_smmu_unmap,
	.flush_iotlb_all	= arm_smmu_flush_iotlb_all,
	.iotlb_sync		= arm_smmu_iotlb_sync,
	.iova_to_phys		= arm_smmu_iova_to_phys,
	.probe_device		= arm_smmu_probe_device,
	.release_device		= arm_smmu_release_device,
	.device_group		= arm_smmu_device_group,
	.enable_nesting		= arm_smmu_enable_nesting,
	.of_xlate		= arm_smmu_of_xlate,
	.get_resv_regions	= arm_smmu_get_resv_regions,
	.put_resv_regions	= generic_iommu_put_resv_regions,
	.dev_has_feat		= arm_smmu_dev_has_feature,
	.dev_feat_enabled	= arm_smmu_dev_feature_enabled,
	.dev_enable_feat	= arm_smmu_dev_enable_feature,
	.dev_disable_feat	= arm_smmu_dev_disable_feature,
	.sva_bind		= arm_smmu_sva_bind,
	.sva_unbind		= arm_smmu_sva_unbind,
	.sva_get_pasid		= arm_smmu_sva_get_pasid,
	.pgsize_biपंचांगap		= -1UL, /* Restricted during device attach */
	.owner			= THIS_MODULE,
पूर्ण;

/* Probing and initialisation functions */
अटल पूर्णांक arm_smmu_init_one_queue(काष्ठा arm_smmu_device *smmu,
				   काष्ठा arm_smmu_queue *q,
				   व्योम __iomem *page,
				   अचिन्हित दीर्घ prod_off,
				   अचिन्हित दीर्घ cons_off,
				   माप_प्रकार dwords, स्थिर अक्षर *name)
अणु
	माप_प्रकार qsz;

	करो अणु
		qsz = ((1 << q->llq.max_n_shअगरt) * dwords) << 3;
		q->base = dmam_alloc_coherent(smmu->dev, qsz, &q->base_dma,
					      GFP_KERNEL);
		अगर (q->base || qsz < PAGE_SIZE)
			अवरोध;

		q->llq.max_n_shअगरt--;
	पूर्ण जबतक (1);

	अगर (!q->base) अणु
		dev_err(smmu->dev,
			"failed to allocate queue (0x%zx bytes) for %s\n",
			qsz, name);
		वापस -ENOMEM;
	पूर्ण

	अगर (!WARN_ON(q->base_dma & (qsz - 1))) अणु
		dev_info(smmu->dev, "allocated %u entries for %s\n",
			 1 << q->llq.max_n_shअगरt, name);
	पूर्ण

	q->prod_reg	= page + prod_off;
	q->cons_reg	= page + cons_off;
	q->ent_dwords	= dwords;

	q->q_base  = Q_BASE_RWA;
	q->q_base |= q->base_dma & Q_BASE_ADDR_MASK;
	q->q_base |= FIELD_PREP(Q_BASE_LOG2SIZE, q->llq.max_n_shअगरt);

	q->llq.prod = q->llq.cons = 0;
	वापस 0;
पूर्ण

अटल व्योम arm_smmu_cmdq_मुक्त_biपंचांगap(व्योम *data)
अणु
	अचिन्हित दीर्घ *biपंचांगap = data;
	biपंचांगap_मुक्त(biपंचांगap);
पूर्ण

अटल पूर्णांक arm_smmu_cmdq_init(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret = 0;
	काष्ठा arm_smmu_cmdq *cmdq = &smmu->cmdq;
	अचिन्हित पूर्णांक nents = 1 << cmdq->q.llq.max_n_shअगरt;
	atomic_दीर्घ_t *biपंचांगap;

	atomic_set(&cmdq->owner_prod, 0);
	atomic_set(&cmdq->lock, 0);

	biपंचांगap = (atomic_दीर्घ_t *)biपंचांगap_zalloc(nents, GFP_KERNEL);
	अगर (!biपंचांगap) अणु
		dev_err(smmu->dev, "failed to allocate cmdq bitmap\n");
		ret = -ENOMEM;
	पूर्ण अन्यथा अणु
		cmdq->valid_map = biपंचांगap;
		devm_add_action(smmu->dev, arm_smmu_cmdq_मुक्त_biपंचांगap, biपंचांगap);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_init_queues(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret;

	/* cmdq */
	ret = arm_smmu_init_one_queue(smmu, &smmu->cmdq.q, smmu->base,
				      ARM_SMMU_CMDQ_PROD, ARM_SMMU_CMDQ_CONS,
				      CMDQ_ENT_DWORDS, "cmdq");
	अगर (ret)
		वापस ret;

	ret = arm_smmu_cmdq_init(smmu);
	अगर (ret)
		वापस ret;

	/* evtq */
	ret = arm_smmu_init_one_queue(smmu, &smmu->evtq.q, smmu->page1,
				      ARM_SMMU_EVTQ_PROD, ARM_SMMU_EVTQ_CONS,
				      EVTQ_ENT_DWORDS, "evtq");
	अगर (ret)
		वापस ret;

	/* priq */
	अगर (!(smmu->features & ARM_SMMU_FEAT_PRI))
		वापस 0;

	वापस arm_smmu_init_one_queue(smmu, &smmu->priq.q, smmu->page1,
				       ARM_SMMU_PRIQ_PROD, ARM_SMMU_PRIQ_CONS,
				       PRIQ_ENT_DWORDS, "priq");
पूर्ण

अटल पूर्णांक arm_smmu_init_l1_strtab(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा arm_smmu_strtab_cfg *cfg = &smmu->strtab_cfg;
	माप_प्रकार size = माप(*cfg->l1_desc) * cfg->num_l1_ents;
	व्योम *strtab = smmu->strtab_cfg.strtab;

	cfg->l1_desc = devm_kzalloc(smmu->dev, size, GFP_KERNEL);
	अगर (!cfg->l1_desc) अणु
		dev_err(smmu->dev, "failed to allocate l1 stream table desc\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < cfg->num_l1_ents; ++i) अणु
		arm_smmu_ग_लिखो_strtab_l1_desc(strtab, &cfg->l1_desc[i]);
		strtab += STRTAB_L1_DESC_DWORDS << 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_init_strtab_2lvl(काष्ठा arm_smmu_device *smmu)
अणु
	व्योम *strtab;
	u64 reg;
	u32 size, l1size;
	काष्ठा arm_smmu_strtab_cfg *cfg = &smmu->strtab_cfg;

	/* Calculate the L1 size, capped to the SIDSIZE. */
	size = STRTAB_L1_SZ_SHIFT - (ilog2(STRTAB_L1_DESC_DWORDS) + 3);
	size = min(size, smmu->sid_bits - STRTAB_SPLIT);
	cfg->num_l1_ents = 1 << size;

	size += STRTAB_SPLIT;
	अगर (size < smmu->sid_bits)
		dev_warn(smmu->dev,
			 "2-level strtab only covers %u/%u bits of SID\n",
			 size, smmu->sid_bits);

	l1size = cfg->num_l1_ents * (STRTAB_L1_DESC_DWORDS << 3);
	strtab = dmam_alloc_coherent(smmu->dev, l1size, &cfg->strtab_dma,
				     GFP_KERNEL);
	अगर (!strtab) अणु
		dev_err(smmu->dev,
			"failed to allocate l1 stream table (%u bytes)\n",
			l1size);
		वापस -ENOMEM;
	पूर्ण
	cfg->strtab = strtab;

	/* Configure strtab_base_cfg क्रम 2 levels */
	reg  = FIELD_PREP(STRTAB_BASE_CFG_FMT, STRTAB_BASE_CFG_FMT_2LVL);
	reg |= FIELD_PREP(STRTAB_BASE_CFG_LOG2SIZE, size);
	reg |= FIELD_PREP(STRTAB_BASE_CFG_SPLIT, STRTAB_SPLIT);
	cfg->strtab_base_cfg = reg;

	वापस arm_smmu_init_l1_strtab(smmu);
पूर्ण

अटल पूर्णांक arm_smmu_init_strtab_linear(काष्ठा arm_smmu_device *smmu)
अणु
	व्योम *strtab;
	u64 reg;
	u32 size;
	काष्ठा arm_smmu_strtab_cfg *cfg = &smmu->strtab_cfg;

	size = (1 << smmu->sid_bits) * (STRTAB_STE_DWORDS << 3);
	strtab = dmam_alloc_coherent(smmu->dev, size, &cfg->strtab_dma,
				     GFP_KERNEL);
	अगर (!strtab) अणु
		dev_err(smmu->dev,
			"failed to allocate linear stream table (%u bytes)\n",
			size);
		वापस -ENOMEM;
	पूर्ण
	cfg->strtab = strtab;
	cfg->num_l1_ents = 1 << smmu->sid_bits;

	/* Configure strtab_base_cfg क्रम a linear table covering all SIDs */
	reg  = FIELD_PREP(STRTAB_BASE_CFG_FMT, STRTAB_BASE_CFG_FMT_LINEAR);
	reg |= FIELD_PREP(STRTAB_BASE_CFG_LOG2SIZE, smmu->sid_bits);
	cfg->strtab_base_cfg = reg;

	arm_smmu_init_bypass_stes(strtab, cfg->num_l1_ents);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_init_strtab(काष्ठा arm_smmu_device *smmu)
अणु
	u64 reg;
	पूर्णांक ret;

	अगर (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB)
		ret = arm_smmu_init_strtab_2lvl(smmu);
	अन्यथा
		ret = arm_smmu_init_strtab_linear(smmu);

	अगर (ret)
		वापस ret;

	/* Set the strtab base address */
	reg  = smmu->strtab_cfg.strtab_dma & STRTAB_BASE_ADDR_MASK;
	reg |= STRTAB_BASE_RA;
	smmu->strtab_cfg.strtab_base = reg;

	/* Allocate the first VMID क्रम stage-2 bypass STEs */
	set_bit(0, smmu->vmid_map);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_init_काष्ठाures(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret;

	mutex_init(&smmu->streams_mutex);
	smmu->streams = RB_ROOT;

	ret = arm_smmu_init_queues(smmu);
	अगर (ret)
		वापस ret;

	वापस arm_smmu_init_strtab(smmu);
पूर्ण

अटल पूर्णांक arm_smmu_ग_लिखो_reg_sync(काष्ठा arm_smmu_device *smmu, u32 val,
				   अचिन्हित पूर्णांक reg_off, अचिन्हित पूर्णांक ack_off)
अणु
	u32 reg;

	ग_लिखोl_relaxed(val, smmu->base + reg_off);
	वापस पढ़ोl_relaxed_poll_समयout(smmu->base + ack_off, reg, reg == val,
					  1, ARM_SMMU_POLL_TIMEOUT_US);
पूर्ण

/* GBPA is "special" */
अटल पूर्णांक arm_smmu_update_gbpa(काष्ठा arm_smmu_device *smmu, u32 set, u32 clr)
अणु
	पूर्णांक ret;
	u32 reg, __iomem *gbpa = smmu->base + ARM_SMMU_GBPA;

	ret = पढ़ोl_relaxed_poll_समयout(gbpa, reg, !(reg & GBPA_UPDATE),
					 1, ARM_SMMU_POLL_TIMEOUT_US);
	अगर (ret)
		वापस ret;

	reg &= ~clr;
	reg |= set;
	ग_लिखोl_relaxed(reg | GBPA_UPDATE, gbpa);
	ret = पढ़ोl_relaxed_poll_समयout(gbpa, reg, !(reg & GBPA_UPDATE),
					 1, ARM_SMMU_POLL_TIMEOUT_US);

	अगर (ret)
		dev_err(smmu->dev, "GBPA not responding to update\n");
	वापस ret;
पूर्ण

अटल व्योम arm_smmu_मुक्त_msis(व्योम *data)
अणु
	काष्ठा device *dev = data;
	platक्रमm_msi_करोमुख्य_मुक्त_irqs(dev);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_msi_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	phys_addr_t करोorbell;
	काष्ठा device *dev = msi_desc_to_dev(desc);
	काष्ठा arm_smmu_device *smmu = dev_get_drvdata(dev);
	phys_addr_t *cfg = arm_smmu_msi_cfg[desc->platक्रमm.msi_index];

	करोorbell = (((u64)msg->address_hi) << 32) | msg->address_lo;
	करोorbell &= MSI_CFG0_ADDR_MASK;

	ग_लिखोq_relaxed(करोorbell, smmu->base + cfg[0]);
	ग_लिखोl_relaxed(msg->data, smmu->base + cfg[1]);
	ग_लिखोl_relaxed(ARM_SMMU_MEMATTR_DEVICE_nGnRE, smmu->base + cfg[2]);
पूर्ण

अटल व्योम arm_smmu_setup_msis(काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा msi_desc *desc;
	पूर्णांक ret, nvec = ARM_SMMU_MAX_MSIS;
	काष्ठा device *dev = smmu->dev;

	/* Clear the MSI address regs */
	ग_लिखोq_relaxed(0, smmu->base + ARM_SMMU_GERROR_IRQ_CFG0);
	ग_लिखोq_relaxed(0, smmu->base + ARM_SMMU_EVTQ_IRQ_CFG0);

	अगर (smmu->features & ARM_SMMU_FEAT_PRI)
		ग_लिखोq_relaxed(0, smmu->base + ARM_SMMU_PRIQ_IRQ_CFG0);
	अन्यथा
		nvec--;

	अगर (!(smmu->features & ARM_SMMU_FEAT_MSI))
		वापस;

	अगर (!dev->msi_करोमुख्य) अणु
		dev_info(smmu->dev, "msi_domain absent - falling back to wired irqs\n");
		वापस;
	पूर्ण

	/* Allocate MSIs क्रम evtq, gerror and priq. Ignore cmdq */
	ret = platक्रमm_msi_करोमुख्य_alloc_irqs(dev, nvec, arm_smmu_ग_लिखो_msi_msg);
	अगर (ret) अणु
		dev_warn(dev, "failed to allocate MSIs - falling back to wired irqs\n");
		वापस;
	पूर्ण

	क्रम_each_msi_entry(desc, dev) अणु
		चयन (desc->platक्रमm.msi_index) अणु
		हाल EVTQ_MSI_INDEX:
			smmu->evtq.q.irq = desc->irq;
			अवरोध;
		हाल GERROR_MSI_INDEX:
			smmu->gerr_irq = desc->irq;
			अवरोध;
		हाल PRIQ_MSI_INDEX:
			smmu->priq.q.irq = desc->irq;
			अवरोध;
		शेष:	/* Unknown */
			जारी;
		पूर्ण
	पूर्ण

	/* Add callback to मुक्त MSIs on tearकरोwn */
	devm_add_action(dev, arm_smmu_मुक्त_msis, dev);
पूर्ण

अटल व्योम arm_smmu_setup_unique_irqs(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक irq, ret;

	arm_smmu_setup_msis(smmu);

	/* Request पूर्णांकerrupt lines */
	irq = smmu->evtq.q.irq;
	अगर (irq) अणु
		ret = devm_request_thपढ़ोed_irq(smmu->dev, irq, शून्य,
						arm_smmu_evtq_thपढ़ो,
						IRQF_ONESHOT,
						"arm-smmu-v3-evtq", smmu);
		अगर (ret < 0)
			dev_warn(smmu->dev, "failed to enable evtq irq\n");
	पूर्ण अन्यथा अणु
		dev_warn(smmu->dev, "no evtq irq - events will not be reported!\n");
	पूर्ण

	irq = smmu->gerr_irq;
	अगर (irq) अणु
		ret = devm_request_irq(smmu->dev, irq, arm_smmu_gerror_handler,
				       0, "arm-smmu-v3-gerror", smmu);
		अगर (ret < 0)
			dev_warn(smmu->dev, "failed to enable gerror irq\n");
	पूर्ण अन्यथा अणु
		dev_warn(smmu->dev, "no gerr irq - errors will not be reported!\n");
	पूर्ण

	अगर (smmu->features & ARM_SMMU_FEAT_PRI) अणु
		irq = smmu->priq.q.irq;
		अगर (irq) अणु
			ret = devm_request_thपढ़ोed_irq(smmu->dev, irq, शून्य,
							arm_smmu_priq_thपढ़ो,
							IRQF_ONESHOT,
							"arm-smmu-v3-priq",
							smmu);
			अगर (ret < 0)
				dev_warn(smmu->dev,
					 "failed to enable priq irq\n");
		पूर्ण अन्यथा अणु
			dev_warn(smmu->dev, "no priq irq - PRI will be broken\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_setup_irqs(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret, irq;
	u32 irqen_flags = IRQ_CTRL_EVTQ_IRQEN | IRQ_CTRL_GERROR_IRQEN;

	/* Disable IRQs first */
	ret = arm_smmu_ग_लिखो_reg_sync(smmu, 0, ARM_SMMU_IRQ_CTRL,
				      ARM_SMMU_IRQ_CTRLACK);
	अगर (ret) अणु
		dev_err(smmu->dev, "failed to disable irqs\n");
		वापस ret;
	पूर्ण

	irq = smmu->combined_irq;
	अगर (irq) अणु
		/*
		 * Cavium ThunderX2 implementation करोesn't support unique irq
		 * lines. Use a single irq line क्रम all the SMMUv3 पूर्णांकerrupts.
		 */
		ret = devm_request_thपढ़ोed_irq(smmu->dev, irq,
					arm_smmu_combined_irq_handler,
					arm_smmu_combined_irq_thपढ़ो,
					IRQF_ONESHOT,
					"arm-smmu-v3-combined-irq", smmu);
		अगर (ret < 0)
			dev_warn(smmu->dev, "failed to enable combined irq\n");
	पूर्ण अन्यथा
		arm_smmu_setup_unique_irqs(smmu);

	अगर (smmu->features & ARM_SMMU_FEAT_PRI)
		irqen_flags |= IRQ_CTRL_PRIQ_IRQEN;

	/* Enable पूर्णांकerrupt generation on the SMMU */
	ret = arm_smmu_ग_लिखो_reg_sync(smmu, irqen_flags,
				      ARM_SMMU_IRQ_CTRL, ARM_SMMU_IRQ_CTRLACK);
	अगर (ret)
		dev_warn(smmu->dev, "failed to enable irqs\n");

	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_device_disable(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret;

	ret = arm_smmu_ग_लिखो_reg_sync(smmu, 0, ARM_SMMU_CR0, ARM_SMMU_CR0ACK);
	अगर (ret)
		dev_err(smmu->dev, "failed to clear cr0\n");

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_device_reset(काष्ठा arm_smmu_device *smmu, bool bypass)
अणु
	पूर्णांक ret;
	u32 reg, enables;
	काष्ठा arm_smmu_cmdq_ent cmd;

	/* Clear CR0 and sync (disables SMMU and queue processing) */
	reg = पढ़ोl_relaxed(smmu->base + ARM_SMMU_CR0);
	अगर (reg & CR0_SMMUEN) अणु
		dev_warn(smmu->dev, "SMMU currently enabled! Resetting...\n");
		WARN_ON(is_kdump_kernel() && !disable_bypass);
		arm_smmu_update_gbpa(smmu, GBPA_ABORT, 0);
	पूर्ण

	ret = arm_smmu_device_disable(smmu);
	अगर (ret)
		वापस ret;

	/* CR1 (table and queue memory attributes) */
	reg = FIELD_PREP(CR1_TABLE_SH, ARM_SMMU_SH_ISH) |
	      FIELD_PREP(CR1_TABLE_OC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_TABLE_IC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_QUEUE_SH, ARM_SMMU_SH_ISH) |
	      FIELD_PREP(CR1_QUEUE_OC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_QUEUE_IC, CR1_CACHE_WB);
	ग_लिखोl_relaxed(reg, smmu->base + ARM_SMMU_CR1);

	/* CR2 (अक्रमom crap) */
	reg = CR2_PTM | CR2_RECINVSID;

	अगर (smmu->features & ARM_SMMU_FEAT_E2H)
		reg |= CR2_E2H;

	ग_लिखोl_relaxed(reg, smmu->base + ARM_SMMU_CR2);

	/* Stream table */
	ग_लिखोq_relaxed(smmu->strtab_cfg.strtab_base,
		       smmu->base + ARM_SMMU_STRTAB_BASE);
	ग_लिखोl_relaxed(smmu->strtab_cfg.strtab_base_cfg,
		       smmu->base + ARM_SMMU_STRTAB_BASE_CFG);

	/* Command queue */
	ग_लिखोq_relaxed(smmu->cmdq.q.q_base, smmu->base + ARM_SMMU_CMDQ_BASE);
	ग_लिखोl_relaxed(smmu->cmdq.q.llq.prod, smmu->base + ARM_SMMU_CMDQ_PROD);
	ग_लिखोl_relaxed(smmu->cmdq.q.llq.cons, smmu->base + ARM_SMMU_CMDQ_CONS);

	enables = CR0_CMDQEN;
	ret = arm_smmu_ग_लिखो_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	अगर (ret) अणु
		dev_err(smmu->dev, "failed to enable command queue\n");
		वापस ret;
	पूर्ण

	/* Invalidate any cached configuration */
	cmd.opcode = CMDQ_OP_CFGI_ALL;
	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);

	/* Invalidate any stale TLB entries */
	अगर (smmu->features & ARM_SMMU_FEAT_HYP) अणु
		cmd.opcode = CMDQ_OP_TLBI_EL2_ALL;
		arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	पूर्ण

	cmd.opcode = CMDQ_OP_TLBI_NSNH_ALL;
	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);

	/* Event queue */
	ग_लिखोq_relaxed(smmu->evtq.q.q_base, smmu->base + ARM_SMMU_EVTQ_BASE);
	ग_लिखोl_relaxed(smmu->evtq.q.llq.prod, smmu->page1 + ARM_SMMU_EVTQ_PROD);
	ग_लिखोl_relaxed(smmu->evtq.q.llq.cons, smmu->page1 + ARM_SMMU_EVTQ_CONS);

	enables |= CR0_EVTQEN;
	ret = arm_smmu_ग_लिखो_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	अगर (ret) अणु
		dev_err(smmu->dev, "failed to enable event queue\n");
		वापस ret;
	पूर्ण

	/* PRI queue */
	अगर (smmu->features & ARM_SMMU_FEAT_PRI) अणु
		ग_लिखोq_relaxed(smmu->priq.q.q_base,
			       smmu->base + ARM_SMMU_PRIQ_BASE);
		ग_लिखोl_relaxed(smmu->priq.q.llq.prod,
			       smmu->page1 + ARM_SMMU_PRIQ_PROD);
		ग_लिखोl_relaxed(smmu->priq.q.llq.cons,
			       smmu->page1 + ARM_SMMU_PRIQ_CONS);

		enables |= CR0_PRIQEN;
		ret = arm_smmu_ग_लिखो_reg_sync(smmu, enables, ARM_SMMU_CR0,
					      ARM_SMMU_CR0ACK);
		अगर (ret) अणु
			dev_err(smmu->dev, "failed to enable PRI queue\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smmu->features & ARM_SMMU_FEAT_ATS) अणु
		enables |= CR0_ATSCHK;
		ret = arm_smmu_ग_लिखो_reg_sync(smmu, enables, ARM_SMMU_CR0,
					      ARM_SMMU_CR0ACK);
		अगर (ret) अणु
			dev_err(smmu->dev, "failed to enable ATS check\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = arm_smmu_setup_irqs(smmu);
	अगर (ret) अणु
		dev_err(smmu->dev, "failed to setup irqs\n");
		वापस ret;
	पूर्ण

	अगर (is_kdump_kernel())
		enables &= ~(CR0_EVTQEN | CR0_PRIQEN);

	/* Enable the SMMU पूर्णांकerface, or ensure bypass */
	अगर (!bypass || disable_bypass) अणु
		enables |= CR0_SMMUEN;
	पूर्ण अन्यथा अणु
		ret = arm_smmu_update_gbpa(smmu, 0, GBPA_ABORT);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = arm_smmu_ग_लिखो_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	अगर (ret) अणु
		dev_err(smmu->dev, "failed to enable SMMU interface\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_device_hw_probe(काष्ठा arm_smmu_device *smmu)
अणु
	u32 reg;
	bool coherent = smmu->features & ARM_SMMU_FEAT_COHERENCY;

	/* IDR0 */
	reg = पढ़ोl_relaxed(smmu->base + ARM_SMMU_IDR0);

	/* 2-level काष्ठाures */
	अगर (FIELD_GET(IDR0_ST_LVL, reg) == IDR0_ST_LVL_2LVL)
		smmu->features |= ARM_SMMU_FEAT_2_LVL_STRTAB;

	अगर (reg & IDR0_CD2L)
		smmu->features |= ARM_SMMU_FEAT_2_LVL_CDTAB;

	/*
	 * Translation table endianness.
	 * We currently require the same endianness as the CPU, but this
	 * could be changed later by adding a new IO_PGTABLE_QUIRK.
	 */
	चयन (FIELD_GET(IDR0_TTENDIAN, reg)) अणु
	हाल IDR0_TTENDIAN_MIXED:
		smmu->features |= ARM_SMMU_FEAT_TT_LE | ARM_SMMU_FEAT_TT_BE;
		अवरोध;
#अगर_घोषित __BIG_ENDIAN
	हाल IDR0_TTENDIAN_BE:
		smmu->features |= ARM_SMMU_FEAT_TT_BE;
		अवरोध;
#अन्यथा
	हाल IDR0_TTENDIAN_LE:
		smmu->features |= ARM_SMMU_FEAT_TT_LE;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dev_err(smmu->dev, "unknown/unsupported TT endianness!\n");
		वापस -ENXIO;
	पूर्ण

	/* Boolean feature flags */
	अगर (IS_ENABLED(CONFIG_PCI_PRI) && reg & IDR0_PRI)
		smmu->features |= ARM_SMMU_FEAT_PRI;

	अगर (IS_ENABLED(CONFIG_PCI_ATS) && reg & IDR0_ATS)
		smmu->features |= ARM_SMMU_FEAT_ATS;

	अगर (reg & IDR0_SEV)
		smmu->features |= ARM_SMMU_FEAT_SEV;

	अगर (reg & IDR0_MSI) अणु
		smmu->features |= ARM_SMMU_FEAT_MSI;
		अगर (coherent && !disable_msipolling)
			smmu->options |= ARM_SMMU_OPT_MSIPOLL;
	पूर्ण

	अगर (reg & IDR0_HYP) अणु
		smmu->features |= ARM_SMMU_FEAT_HYP;
		अगर (cpus_have_cap(ARM64_HAS_VIRT_HOST_EXTN))
			smmu->features |= ARM_SMMU_FEAT_E2H;
	पूर्ण

	/*
	 * The coherency feature as set by FW is used in preference to the ID
	 * रेजिस्टर, but warn on mismatch.
	 */
	अगर (!!(reg & IDR0_COHACC) != coherent)
		dev_warn(smmu->dev, "IDR0.COHACC overridden by FW configuration (%s)\n",
			 coherent ? "true" : "false");

	चयन (FIELD_GET(IDR0_STALL_MODEL, reg)) अणु
	हाल IDR0_STALL_MODEL_FORCE:
		smmu->features |= ARM_SMMU_FEAT_STALL_FORCE;
		fallthrough;
	हाल IDR0_STALL_MODEL_STALL:
		smmu->features |= ARM_SMMU_FEAT_STALLS;
	पूर्ण

	अगर (reg & IDR0_S1P)
		smmu->features |= ARM_SMMU_FEAT_TRANS_S1;

	अगर (reg & IDR0_S2P)
		smmu->features |= ARM_SMMU_FEAT_TRANS_S2;

	अगर (!(reg & (IDR0_S1P | IDR0_S2P))) अणु
		dev_err(smmu->dev, "no translation support!\n");
		वापस -ENXIO;
	पूर्ण

	/* We only support the AArch64 table क्रमmat at present */
	चयन (FIELD_GET(IDR0_TTF, reg)) अणु
	हाल IDR0_TTF_AARCH32_64:
		smmu->ias = 40;
		fallthrough;
	हाल IDR0_TTF_AARCH64:
		अवरोध;
	शेष:
		dev_err(smmu->dev, "AArch64 table format not supported!\n");
		वापस -ENXIO;
	पूर्ण

	/* ASID/VMID sizes */
	smmu->asid_bits = reg & IDR0_ASID16 ? 16 : 8;
	smmu->vmid_bits = reg & IDR0_VMID16 ? 16 : 8;

	/* IDR1 */
	reg = पढ़ोl_relaxed(smmu->base + ARM_SMMU_IDR1);
	अगर (reg & (IDR1_TABLES_PRESET | IDR1_QUEUES_PRESET | IDR1_REL)) अणु
		dev_err(smmu->dev, "embedded implementation not supported\n");
		वापस -ENXIO;
	पूर्ण

	/* Queue sizes, capped to ensure natural alignment */
	smmu->cmdq.q.llq.max_n_shअगरt = min_t(u32, CMDQ_MAX_SZ_SHIFT,
					     FIELD_GET(IDR1_CMDQS, reg));
	अगर (smmu->cmdq.q.llq.max_n_shअगरt <= ilog2(CMDQ_BATCH_ENTRIES)) अणु
		/*
		 * We करोn't support splitting up batches, so one batch of
		 * commands plus an extra sync needs to fit inside the command
		 * queue. There's also no way we can handle the weird alignment
		 * restrictions on the base poपूर्णांकer क्रम a unit-length queue.
		 */
		dev_err(smmu->dev, "command queue size <= %d entries not supported\n",
			CMDQ_BATCH_ENTRIES);
		वापस -ENXIO;
	पूर्ण

	smmu->evtq.q.llq.max_n_shअगरt = min_t(u32, EVTQ_MAX_SZ_SHIFT,
					     FIELD_GET(IDR1_EVTQS, reg));
	smmu->priq.q.llq.max_n_shअगरt = min_t(u32, PRIQ_MAX_SZ_SHIFT,
					     FIELD_GET(IDR1_PRIQS, reg));

	/* SID/SSID sizes */
	smmu->ssid_bits = FIELD_GET(IDR1_SSIDSIZE, reg);
	smmu->sid_bits = FIELD_GET(IDR1_SIDSIZE, reg);

	/*
	 * If the SMMU supports fewer bits than would fill a single L2 stream
	 * table, use a linear table instead.
	 */
	अगर (smmu->sid_bits <= STRTAB_SPLIT)
		smmu->features &= ~ARM_SMMU_FEAT_2_LVL_STRTAB;

	/* IDR3 */
	reg = पढ़ोl_relaxed(smmu->base + ARM_SMMU_IDR3);
	अगर (FIELD_GET(IDR3_RIL, reg))
		smmu->features |= ARM_SMMU_FEAT_RANGE_INV;

	/* IDR5 */
	reg = पढ़ोl_relaxed(smmu->base + ARM_SMMU_IDR5);

	/* Maximum number of outstanding stalls */
	smmu->evtq.max_stalls = FIELD_GET(IDR5_STALL_MAX, reg);

	/* Page sizes */
	अगर (reg & IDR5_GRAN64K)
		smmu->pgsize_biपंचांगap |= SZ_64K | SZ_512M;
	अगर (reg & IDR5_GRAN16K)
		smmu->pgsize_biपंचांगap |= SZ_16K | SZ_32M;
	अगर (reg & IDR5_GRAN4K)
		smmu->pgsize_biपंचांगap |= SZ_4K | SZ_2M | SZ_1G;

	/* Input address size */
	अगर (FIELD_GET(IDR5_VAX, reg) == IDR5_VAX_52_BIT)
		smmu->features |= ARM_SMMU_FEAT_VAX;

	/* Output address size */
	चयन (FIELD_GET(IDR5_OAS, reg)) अणु
	हाल IDR5_OAS_32_BIT:
		smmu->oas = 32;
		अवरोध;
	हाल IDR5_OAS_36_BIT:
		smmu->oas = 36;
		अवरोध;
	हाल IDR5_OAS_40_BIT:
		smmu->oas = 40;
		अवरोध;
	हाल IDR5_OAS_42_BIT:
		smmu->oas = 42;
		अवरोध;
	हाल IDR5_OAS_44_BIT:
		smmu->oas = 44;
		अवरोध;
	हाल IDR5_OAS_52_BIT:
		smmu->oas = 52;
		smmu->pgsize_biपंचांगap |= 1ULL << 42; /* 4TB */
		अवरोध;
	शेष:
		dev_info(smmu->dev,
			"unknown output address size. Truncating to 48-bit\n");
		fallthrough;
	हाल IDR5_OAS_48_BIT:
		smmu->oas = 48;
	पूर्ण

	अगर (arm_smmu_ops.pgsize_biपंचांगap == -1UL)
		arm_smmu_ops.pgsize_biपंचांगap = smmu->pgsize_biपंचांगap;
	अन्यथा
		arm_smmu_ops.pgsize_biपंचांगap |= smmu->pgsize_biपंचांगap;

	/* Set the DMA mask क्रम our table walker */
	अगर (dma_set_mask_and_coherent(smmu->dev, DMA_BIT_MASK(smmu->oas)))
		dev_warn(smmu->dev,
			 "failed to set DMA mask for table walker\n");

	smmu->ias = max(smmu->ias, smmu->oas);

	अगर (arm_smmu_sva_supported(smmu))
		smmu->features |= ARM_SMMU_FEAT_SVA;

	dev_info(smmu->dev, "ias %lu-bit, oas %lu-bit (features 0x%08x)\n",
		 smmu->ias, smmu->oas, smmu->features);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल व्योम acpi_smmu_get_options(u32 model, काष्ठा arm_smmu_device *smmu)
अणु
	चयन (model) अणु
	हाल ACPI_IORT_SMMU_V3_CAVIUM_CN99XX:
		smmu->options |= ARM_SMMU_OPT_PAGE0_REGS_ONLY;
		अवरोध;
	हाल ACPI_IORT_SMMU_V3_HISILICON_HI161X:
		smmu->options |= ARM_SMMU_OPT_SKIP_PREFETCH;
		अवरोध;
	पूर्ण

	dev_notice(smmu->dev, "option mask 0x%x\n", smmu->options);
पूर्ण

अटल पूर्णांक arm_smmu_device_acpi_probe(काष्ठा platक्रमm_device *pdev,
				      काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा acpi_iort_smmu_v3 *iort_smmu;
	काष्ठा device *dev = smmu->dev;
	काष्ठा acpi_iort_node *node;

	node = *(काष्ठा acpi_iort_node **)dev_get_platdata(dev);

	/* Retrieve SMMUv3 specअगरic data */
	iort_smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;

	acpi_smmu_get_options(iort_smmu->model, smmu);

	अगर (iort_smmu->flags & ACPI_IORT_SMMU_V3_COHACC_OVERRIDE)
		smmu->features |= ARM_SMMU_FEAT_COHERENCY;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक arm_smmu_device_acpi_probe(काष्ठा platक्रमm_device *pdev,
					     काष्ठा arm_smmu_device *smmu)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक arm_smmu_device_dt_probe(काष्ठा platक्रमm_device *pdev,
				    काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा device *dev = &pdev->dev;
	u32 cells;
	पूर्णांक ret = -EINVAL;

	अगर (of_property_पढ़ो_u32(dev->of_node, "#iommu-cells", &cells))
		dev_err(dev, "missing #iommu-cells property\n");
	अन्यथा अगर (cells != 1)
		dev_err(dev, "invalid #iommu-cells value (%d)\n", cells);
	अन्यथा
		ret = 0;

	parse_driver_options(smmu);

	अगर (of_dma_is_coherent(dev->of_node))
		smmu->features |= ARM_SMMU_FEAT_COHERENCY;

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ arm_smmu_resource_size(काष्ठा arm_smmu_device *smmu)
अणु
	अगर (smmu->options & ARM_SMMU_OPT_PAGE0_REGS_ONLY)
		वापस SZ_64K;
	अन्यथा
		वापस SZ_128K;
पूर्ण

अटल पूर्णांक arm_smmu_set_bus_ops(काष्ठा iommu_ops *ops)
अणु
	पूर्णांक err;

#अगर_घोषित CONFIG_PCI
	अगर (pci_bus_type.iommu_ops != ops) अणु
		err = bus_set_iommu(&pci_bus_type, ops);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_AMBA
	अगर (amba_bustype.iommu_ops != ops) अणु
		err = bus_set_iommu(&amba_bustype, ops);
		अगर (err)
			जाओ err_reset_pci_ops;
	पूर्ण
#पूर्ण_अगर
	अगर (platक्रमm_bus_type.iommu_ops != ops) अणु
		err = bus_set_iommu(&platक्रमm_bus_type, ops);
		अगर (err)
			जाओ err_reset_amba_ops;
	पूर्ण

	वापस 0;

err_reset_amba_ops:
#अगर_घोषित CONFIG_ARM_AMBA
	bus_set_iommu(&amba_bustype, शून्य);
#पूर्ण_अगर
err_reset_pci_ops: __maybe_unused;
#अगर_घोषित CONFIG_PCI
	bus_set_iommu(&pci_bus_type, शून्य);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __iomem *arm_smmu_ioremap(काष्ठा device *dev, resource_माप_प्रकार start,
				      resource_माप_प्रकार size)
अणु
	काष्ठा resource res = DEFINE_RES_MEM(start, size);

	वापस devm_ioremap_resource(dev, &res);
पूर्ण

अटल पूर्णांक arm_smmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, ret;
	काष्ठा resource *res;
	resource_माप_प्रकार ioaddr;
	काष्ठा arm_smmu_device *smmu;
	काष्ठा device *dev = &pdev->dev;
	bool bypass;

	smmu = devm_kzalloc(dev, माप(*smmu), GFP_KERNEL);
	अगर (!smmu) अणु
		dev_err(dev, "failed to allocate arm_smmu_device\n");
		वापस -ENOMEM;
	पूर्ण
	smmu->dev = dev;

	अगर (dev->of_node) अणु
		ret = arm_smmu_device_dt_probe(pdev, smmu);
	पूर्ण अन्यथा अणु
		ret = arm_smmu_device_acpi_probe(pdev, smmu);
		अगर (ret == -ENODEV)
			वापस ret;
	पूर्ण

	/* Set bypass mode according to firmware probing result */
	bypass = !!ret;

	/* Base address */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (resource_size(res) < arm_smmu_resource_size(smmu)) अणु
		dev_err(dev, "MMIO region too small (%pr)\n", res);
		वापस -EINVAL;
	पूर्ण
	ioaddr = res->start;

	/*
	 * Don't map the IMPLEMENTATION DEFINED regions, since they may contain
	 * the PMCG रेजिस्टरs which are reserved by the PMU driver.
	 */
	smmu->base = arm_smmu_ioremap(dev, ioaddr, ARM_SMMU_REG_SZ);
	अगर (IS_ERR(smmu->base))
		वापस PTR_ERR(smmu->base);

	अगर (arm_smmu_resource_size(smmu) > SZ_64K) अणु
		smmu->page1 = arm_smmu_ioremap(dev, ioaddr + SZ_64K,
					       ARM_SMMU_REG_SZ);
		अगर (IS_ERR(smmu->page1))
			वापस PTR_ERR(smmu->page1);
	पूर्ण अन्यथा अणु
		smmu->page1 = smmu->base;
	पूर्ण

	/* Interrupt lines */

	irq = platक्रमm_get_irq_byname_optional(pdev, "combined");
	अगर (irq > 0)
		smmu->combined_irq = irq;
	अन्यथा अणु
		irq = platक्रमm_get_irq_byname_optional(pdev, "eventq");
		अगर (irq > 0)
			smmu->evtq.q.irq = irq;

		irq = platक्रमm_get_irq_byname_optional(pdev, "priq");
		अगर (irq > 0)
			smmu->priq.q.irq = irq;

		irq = platक्रमm_get_irq_byname_optional(pdev, "gerror");
		अगर (irq > 0)
			smmu->gerr_irq = irq;
	पूर्ण
	/* Probe the h/w */
	ret = arm_smmu_device_hw_probe(smmu);
	अगर (ret)
		वापस ret;

	/* Initialise in-memory data काष्ठाures */
	ret = arm_smmu_init_काष्ठाures(smmu);
	अगर (ret)
		वापस ret;

	/* Record our निजी device काष्ठाure */
	platक्रमm_set_drvdata(pdev, smmu);

	/* Reset the device */
	ret = arm_smmu_device_reset(smmu, bypass);
	अगर (ret)
		वापस ret;

	/* And we're up. Go go go! */
	ret = iommu_device_sysfs_add(&smmu->iommu, dev, शून्य,
				     "smmu3.%pa", &ioaddr);
	अगर (ret)
		वापस ret;

	ret = iommu_device_रेजिस्टर(&smmu->iommu, &arm_smmu_ops, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register iommu\n");
		वापस ret;
	पूर्ण

	वापस arm_smmu_set_bus_ops(&arm_smmu_ops);
पूर्ण

अटल पूर्णांक arm_smmu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_smmu_device *smmu = platक्रमm_get_drvdata(pdev);

	arm_smmu_set_bus_ops(शून्य);
	iommu_device_unरेजिस्टर(&smmu->iommu);
	iommu_device_sysfs_हटाओ(&smmu->iommu);
	arm_smmu_device_disable(smmu);

	वापस 0;
पूर्ण

अटल व्योम arm_smmu_device_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	arm_smmu_device_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id arm_smmu_of_match[] = अणु
	अणु .compatible = "arm,smmu-v3", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_smmu_of_match);

अटल व्योम arm_smmu_driver_unरेजिस्टर(काष्ठा platक्रमm_driver *drv)
अणु
	arm_smmu_sva_notअगरier_synchronize();
	platक्रमm_driver_unरेजिस्टर(drv);
पूर्ण

अटल काष्ठा platक्रमm_driver arm_smmu_driver = अणु
	.driver	= अणु
		.name			= "arm-smmu-v3",
		.of_match_table		= arm_smmu_of_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe	= arm_smmu_device_probe,
	.हटाओ	= arm_smmu_device_हटाओ,
	.shutकरोwn = arm_smmu_device_shutकरोwn,
पूर्ण;
module_driver(arm_smmu_driver, platक्रमm_driver_रेजिस्टर,
	      arm_smmu_driver_unरेजिस्टर);

MODULE_DESCRIPTION("IOMMU API for ARM architected SMMUv3 implementations");
MODULE_AUTHOR("Will Deacon <will@kernel.org>");
MODULE_ALIAS("platform:arm-smmu-v3");
MODULE_LICENSE("GPL v2");
