<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/coresight.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/local.h>
#समावेश <यंत्र/virt.h>

#समावेश "coresight-etm4x.h"
#समावेश "coresight-etm-perf.h"

अटल पूर्णांक boot_enable;
module_param(boot_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(boot_enable, "Enable tracing on boot");

#घोषणा PARAM_PM_SAVE_FIRMWARE	  0 /* save self-hosted state as per firmware */
#घोषणा PARAM_PM_SAVE_NEVER	  1 /* never save any state */
#घोषणा PARAM_PM_SAVE_SELF_HOSTED 2 /* save self-hosted state only */

अटल पूर्णांक pm_save_enable = PARAM_PM_SAVE_FIRMWARE;
module_param(pm_save_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(pm_save_enable,
	"Save/restore state on power down: 1 = never, 2 = self-hosted");

अटल काष्ठा eपंचांगv4_drvdata *eपंचांगdrvdata[NR_CPUS];
अटल व्योम eपंचांग4_set_शेष_config(काष्ठा eपंचांगv4_config *config);
अटल पूर्णांक eपंचांग4_set_event_filters(काष्ठा eपंचांगv4_drvdata *drvdata,
				  काष्ठा perf_event *event);
अटल u64 eपंचांग4_get_access_type(काष्ठा eपंचांगv4_config *config);

अटल क्रमागत cpuhp_state hp_online;

काष्ठा eपंचांग4_init_arg अणु
	अचिन्हित पूर्णांक		pid;
	काष्ठा eपंचांगv4_drvdata	*drvdata;
	काष्ठा csdev_access	*csa;
पूर्ण;

/*
 * Check अगर TRCSSPCICRn(i) is implemented क्रम a given instance.
 *
 * TRCSSPCICRn is implemented only अगर :
 *	TRCSSPCICR<n> is present only अगर all of the following are true:
 *		TRCIDR4.NUMSSCC > n.
 *		TRCIDR4.NUMPC > 0b0000 .
 *		TRCSSCSR<n>.PC == 0b1
 */
अटल अंतरभूत bool eपंचांग4x_sspcicrn_present(काष्ठा eपंचांगv4_drvdata *drvdata, पूर्णांक n)
अणु
	वापस (n < drvdata->nr_ss_cmp) &&
	       drvdata->nr_pe &&
	       (drvdata->config.ss_status[n] & TRCSSCSRn_PC);
पूर्ण

u64 eपंचांग4x_sysreg_पढ़ो(u32 offset, bool _relaxed, bool _64bit)
अणु
	u64 res = 0;

	चयन (offset) अणु
	ETM4x_READ_SYSREG_CASES(res)
	शेष :
		pr_warn_ratelimited("etm4x: trying to read unsupported register @%x\n",
			 offset);
	पूर्ण

	अगर (!_relaxed)
		__iormb(res);	/* Imitate the !relaxed I/O helpers */

	वापस res;
पूर्ण

व्योम eपंचांग4x_sysreg_ग_लिखो(u64 val, u32 offset, bool _relaxed, bool _64bit)
अणु
	अगर (!_relaxed)
		__iowmb();	/* Imitate the !relaxed I/O helpers */
	अगर (!_64bit)
		val &= GENMASK(31, 0);

	चयन (offset) अणु
	ETM4x_WRITE_SYSREG_CASES(val)
	शेष :
		pr_warn_ratelimited("etm4x: trying to write to unsupported register @%x\n",
			offset);
	पूर्ण
पूर्ण

अटल u64 ete_sysreg_पढ़ो(u32 offset, bool _relaxed, bool _64bit)
अणु
	u64 res = 0;

	चयन (offset) अणु
	ETE_READ_CASES(res)
	शेष :
		pr_warn_ratelimited("ete: trying to read unsupported register @%x\n",
				    offset);
	पूर्ण

	अगर (!_relaxed)
		__iormb(res);	/* Imitate the !relaxed I/O helpers */

	वापस res;
पूर्ण

अटल व्योम ete_sysreg_ग_लिखो(u64 val, u32 offset, bool _relaxed, bool _64bit)
अणु
	अगर (!_relaxed)
		__iowmb();	/* Imitate the !relaxed I/O helpers */
	अगर (!_64bit)
		val &= GENMASK(31, 0);

	चयन (offset) अणु
	ETE_WRITE_CASES(val)
	शेष :
		pr_warn_ratelimited("ete: trying to write to unsupported register @%x\n",
				    offset);
	पूर्ण
पूर्ण

अटल व्योम eपंचांग_detect_os_lock(काष्ठा eपंचांगv4_drvdata *drvdata,
			       काष्ठा csdev_access *csa)
अणु
	u32 oslsr = eपंचांग4x_relaxed_पढ़ो32(csa, TRCOSLSR);

	drvdata->os_lock_model = ETM_OSLSR_OSLM(oslsr);
पूर्ण

अटल व्योम eपंचांग_ग_लिखो_os_lock(काष्ठा eपंचांगv4_drvdata *drvdata,
			      काष्ठा csdev_access *csa, u32 val)
अणु
	val = !!val;

	चयन (drvdata->os_lock_model) अणु
	हाल ETM_OSLOCK_PRESENT:
		eपंचांग4x_relaxed_ग_लिखो32(csa, val, TRCOSLAR);
		अवरोध;
	हाल ETM_OSLOCK_PE:
		ग_लिखो_sysreg_s(val, SYS_OSLAR_EL1);
		अवरोध;
	शेष:
		pr_warn_once("CPU%d: Unsupported Trace OSLock model: %x\n",
			     smp_processor_id(), drvdata->os_lock_model);
		fallthrough;
	हाल ETM_OSLOCK_NI:
		वापस;
	पूर्ण
	isb();
पूर्ण

अटल अंतरभूत व्योम eपंचांग4_os_unlock_csa(काष्ठा eपंचांगv4_drvdata *drvdata,
				      काष्ठा csdev_access *csa)
अणु
	WARN_ON(drvdata->cpu != smp_processor_id());

	/* Writing 0 to OS Lock unlocks the trace unit रेजिस्टरs */
	eपंचांग_ग_लिखो_os_lock(drvdata, csa, 0x0);
	drvdata->os_unlock = true;
पूर्ण

अटल व्योम eपंचांग4_os_unlock(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	अगर (!WARN_ON(!drvdata->csdev))
		eपंचांग4_os_unlock_csa(drvdata, &drvdata->csdev->access);
पूर्ण

अटल व्योम eपंचांग4_os_lock(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	अगर (WARN_ON(!drvdata->csdev))
		वापस;
	/* Writing 0x1 to OS Lock locks the trace रेजिस्टरs */
	eपंचांग_ग_लिखो_os_lock(drvdata, &drvdata->csdev->access, 0x1);
	drvdata->os_unlock = false;
पूर्ण

अटल व्योम eपंचांग4_cs_lock(काष्ठा eपंचांगv4_drvdata *drvdata,
			 काष्ठा csdev_access *csa)
अणु
	/* Software Lock is only accessible via memory mapped पूर्णांकerface */
	अगर (csa->io_mem)
		CS_LOCK(csa->base);
पूर्ण

अटल व्योम eपंचांग4_cs_unlock(काष्ठा eपंचांगv4_drvdata *drvdata,
			   काष्ठा csdev_access *csa)
अणु
	अगर (csa->io_mem)
		CS_UNLOCK(csa->base);
पूर्ण

अटल पूर्णांक eपंचांग4_cpu_id(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	वापस drvdata->cpu;
पूर्ण

अटल पूर्णांक eपंचांग4_trace_id(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	वापस drvdata->trcid;
पूर्ण

काष्ठा eपंचांग4_enable_arg अणु
	काष्ठा eपंचांगv4_drvdata *drvdata;
	पूर्णांक rc;
पूर्ण;

#अगर_घोषित CONFIG_ETM4X_IMPDEF_FEATURE

#घोषणा HISI_HIP08_AMBA_ID		0x000b6d01
#घोषणा ETM4_AMBA_MASK			0xfffff
#घोषणा HISI_HIP08_CORE_COMMIT_MASK	0x3000
#घोषणा HISI_HIP08_CORE_COMMIT_SHIFT	12
#घोषणा HISI_HIP08_CORE_COMMIT_FULL	0b00
#घोषणा HISI_HIP08_CORE_COMMIT_LVL_1	0b01
#घोषणा HISI_HIP08_CORE_COMMIT_REG	sys_reg(3, 1, 15, 2, 5)

काष्ठा eपंचांग4_arch_features अणु
	व्योम (*arch_callback)(bool enable);
पूर्ण;

अटल bool eपंचांग4_hisi_match_pid(अचिन्हित पूर्णांक id)
अणु
	वापस (id & ETM4_AMBA_MASK) == HISI_HIP08_AMBA_ID;
पूर्ण

अटल व्योम eपंचांग4_hisi_config_core_commit(bool enable)
अणु
	u8 commit = enable ? HISI_HIP08_CORE_COMMIT_LVL_1 :
		    HISI_HIP08_CORE_COMMIT_FULL;
	u64 val;

	/*
	 * bit 12 and 13 of HISI_HIP08_CORE_COMMIT_REG are used together
	 * to set core-commit, 2'b00 means cpu is at full speed, 2'b01,
	 * 2'b10, 2'b11 mean reduce pipeline speed, and 2'b01 means level-1
	 * speed(minimun value). So bit 12 and 13 should be cleared together.
	 */
	val = पढ़ो_sysreg_s(HISI_HIP08_CORE_COMMIT_REG);
	val &= ~HISI_HIP08_CORE_COMMIT_MASK;
	val |= commit << HISI_HIP08_CORE_COMMIT_SHIFT;
	ग_लिखो_sysreg_s(val, HISI_HIP08_CORE_COMMIT_REG);
पूर्ण

अटल काष्ठा eपंचांग4_arch_features eपंचांग4_features[] = अणु
	[ETM4_IMPDEF_HISI_CORE_COMMIT] = अणु
		.arch_callback = eपंचांग4_hisi_config_core_commit,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम eपंचांग4_enable_arch_specअगरic(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	काष्ठा eपंचांग4_arch_features *ftr;
	पूर्णांक bit;

	क्रम_each_set_bit(bit, drvdata->arch_features, ETM4_IMPDEF_FEATURE_MAX) अणु
		ftr = &eपंचांग4_features[bit];

		अगर (ftr->arch_callback)
			ftr->arch_callback(true);
	पूर्ण
पूर्ण

अटल व्योम eपंचांग4_disable_arch_specअगरic(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	काष्ठा eपंचांग4_arch_features *ftr;
	पूर्णांक bit;

	क्रम_each_set_bit(bit, drvdata->arch_features, ETM4_IMPDEF_FEATURE_MAX) अणु
		ftr = &eपंचांग4_features[bit];

		अगर (ftr->arch_callback)
			ftr->arch_callback(false);
	पूर्ण
पूर्ण

अटल व्योम eपंचांग4_check_arch_features(काष्ठा eपंचांगv4_drvdata *drvdata,
				      अचिन्हित पूर्णांक id)
अणु
	अगर (eपंचांग4_hisi_match_pid(id))
		set_bit(ETM4_IMPDEF_HISI_CORE_COMMIT, drvdata->arch_features);
पूर्ण
#अन्यथा
अटल व्योम eपंचांग4_enable_arch_specअगरic(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
पूर्ण

अटल व्योम eपंचांग4_disable_arch_specअगरic(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
पूर्ण

अटल व्योम eपंचांग4_check_arch_features(काष्ठा eपंचांगv4_drvdata *drvdata,
				     अचिन्हित पूर्णांक id)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ETM4X_IMPDEF_FEATURE */

अटल पूर्णांक eपंचांग4_enable_hw(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	पूर्णांक i, rc;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	काष्ठा coresight_device *csdev = drvdata->csdev;
	काष्ठा device *eपंचांग_dev = &csdev->dev;
	काष्ठा csdev_access *csa = &csdev->access;


	eपंचांग4_cs_unlock(drvdata, csa);
	eपंचांग4_enable_arch_specअगरic(drvdata);

	eपंचांग4_os_unlock(drvdata);

	rc = coresight_claim_device_unlocked(csdev);
	अगर (rc)
		जाओ करोne;

	/* Disable the trace unit beक्रमe programming trace रेजिस्टरs */
	eपंचांग4x_relaxed_ग_लिखो32(csa, 0, TRCPRGCTLR);

	/*
	 * If we use प्रणाली inकाष्ठाions, we need to synchronize the
	 * ग_लिखो to the TRCPRGCTLR, beक्रमe accessing the TRCSTATR.
	 * See ARM IHI0064F, section
	 * "4.3.7 Synchronization of register updates"
	 */
	अगर (!csa->io_mem)
		isb();

	/* रुको क्रम TRCSTATR.IDLE to go up */
	अगर (coresight_समयout(csa, TRCSTATR, TRCSTATR_IDLE_BIT, 1))
		dev_err(eपंचांग_dev,
			"timeout while waiting for Idle Trace Status\n");
	अगर (drvdata->nr_pe)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->pe_sel, TRCPROCSELR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->cfg, TRCCONFIGR);
	/* nothing specअगरic implemented */
	eपंचांग4x_relaxed_ग_लिखो32(csa, 0x0, TRCAUXCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->eventctrl0, TRCEVENTCTL0R);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->eventctrl1, TRCEVENTCTL1R);
	अगर (drvdata->stallctl)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->stall_ctrl, TRCSTALLCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->ts_ctrl, TRCTSCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->syncfreq, TRCSYNCPR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->ccctlr, TRCCCCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->bb_ctrl, TRCBBCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, drvdata->trcid, TRCTRACEIDR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->vinst_ctrl, TRCVICTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->viiectlr, TRCVIIECTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->vissctlr, TRCVISSCTLR);
	अगर (drvdata->nr_pe_cmp)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->vipcssctlr, TRCVIPCSSCTLR);
	क्रम (i = 0; i < drvdata->nrseqstate - 1; i++)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->seq_ctrl[i], TRCSEQEVRn(i));
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->seq_rst, TRCSEQRSTEVR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->seq_state, TRCSEQSTR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->ext_inp, TRCEXTINSELR);
	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->cntrldvr[i], TRCCNTRLDVRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->cntr_ctrl[i], TRCCNTCTLRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->cntr_val[i], TRCCNTVRn(i));
	पूर्ण

	/*
	 * Resource selector pair 0 is always implemented and reserved.  As
	 * such start at 2.
	 */
	क्रम (i = 2; i < drvdata->nr_resource * 2; i++)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->res_ctrl[i], TRCRSCTLRn(i));

	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		/* always clear status bit on restart अगर using single-shot */
		अगर (config->ss_ctrl[i] || config->ss_pe_cmp[i])
			config->ss_status[i] &= ~BIT(31);
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->ss_ctrl[i], TRCSSCCRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->ss_status[i], TRCSSCSRn(i));
		अगर (eपंचांग4x_sspcicrn_present(drvdata, i))
			eपंचांग4x_relaxed_ग_लिखो32(csa, config->ss_pe_cmp[i], TRCSSPCICRn(i));
	पूर्ण
	क्रम (i = 0; i < drvdata->nr_addr_cmp; i++) अणु
		eपंचांग4x_relaxed_ग_लिखो64(csa, config->addr_val[i], TRCACVRn(i));
		eपंचांग4x_relaxed_ग_लिखो64(csa, config->addr_acc[i], TRCACATRn(i));
	पूर्ण
	क्रम (i = 0; i < drvdata->numcidc; i++)
		eपंचांग4x_relaxed_ग_लिखो64(csa, config->ctxid_pid[i], TRCCIDCVRn(i));
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->ctxid_mask0, TRCCIDCCTLR0);
	अगर (drvdata->numcidc > 4)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->ctxid_mask1, TRCCIDCCTLR1);

	क्रम (i = 0; i < drvdata->numvmidc; i++)
		eपंचांग4x_relaxed_ग_लिखो64(csa, config->vmid_val[i], TRCVMIDCVRn(i));
	eपंचांग4x_relaxed_ग_लिखो32(csa, config->vmid_mask0, TRCVMIDCCTLR0);
	अगर (drvdata->numvmidc > 4)
		eपंचांग4x_relaxed_ग_लिखो32(csa, config->vmid_mask1, TRCVMIDCCTLR1);

	अगर (!drvdata->skip_घातer_up) अणु
		u32 trcpdcr = eपंचांग4x_relaxed_पढ़ो32(csa, TRCPDCR);

		/*
		 * Request to keep the trace unit घातered and also
		 * emulation of घातerकरोwn
		 */
		eपंचांग4x_relaxed_ग_लिखो32(csa, trcpdcr | TRCPDCR_PU, TRCPDCR);
	पूर्ण

	/*
	 * ETE mandates that the TRCRSR is written to beक्रमe
	 * enabling it.
	 */
	अगर (eपंचांग4x_is_ete(drvdata))
		eपंचांग4x_relaxed_ग_लिखो32(csa, TRCRSR_TA, TRCRSR);

	/* Enable the trace unit */
	eपंचांग4x_relaxed_ग_लिखो32(csa, 1, TRCPRGCTLR);

	/* Synchronize the रेजिस्टर updates क्रम sysreg access */
	अगर (!csa->io_mem)
		isb();

	/* रुको क्रम TRCSTATR.IDLE to go back करोwn to '0' */
	अगर (coresight_समयout(csa, TRCSTATR, TRCSTATR_IDLE_BIT, 0))
		dev_err(eपंचांग_dev,
			"timeout while waiting for Idle Trace Status\n");

	/*
	 * As recommended by section 4.3.7 ("Synchronization when using the
	 * memory-mapped पूर्णांकerface") of ARM IHI 0064D
	 */
	dsb(sy);
	isb();

करोne:
	eपंचांग4_cs_lock(drvdata, csa);

	dev_dbg(eपंचांग_dev, "cpu: %d enable smp call done: %d\n",
		drvdata->cpu, rc);
	वापस rc;
पूर्ण

अटल व्योम eपंचांग4_enable_hw_smp_call(व्योम *info)
अणु
	काष्ठा eपंचांग4_enable_arg *arg = info;

	अगर (WARN_ON(!arg))
		वापस;
	arg->rc = eपंचांग4_enable_hw(arg->drvdata);
पूर्ण

/*
 * The goal of function eपंचांग4_config_बारtamp_event() is to configure a
 * counter that will tell the tracer to emit a बारtamp packet when it
 * reaches zero.  This is करोne in order to get a more fine grained idea
 * of when inकाष्ठाions are executed so that they can be correlated
 * with execution on other CPUs.
 *
 * To करो this the counter itself is configured to self reload and
 * TRCRSCTLR1 (always true) used to get the counter to decrement.  From
 * there a resource selector is configured with the counter and the
 * बारtamp control रेजिस्टर to use the resource selector to trigger the
 * event that will insert a बारtamp packet in the stream.
 */
अटल पूर्णांक eपंचांग4_config_बारtamp_event(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	पूर्णांक ctridx, ret = -EINVAL;
	पूर्णांक counter, rselector;
	u32 val = 0;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/* No poपूर्णांक in trying अगर we करोn't have at least one counter */
	अगर (!drvdata->nr_cntr)
		जाओ out;

	/* Find a counter that hasn't been initialised */
	क्रम (ctridx = 0; ctridx < drvdata->nr_cntr; ctridx++)
		अगर (config->cntr_val[ctridx] == 0)
			अवरोध;

	/* All the counters have been configured alपढ़ोy, bail out */
	अगर (ctridx == drvdata->nr_cntr) अणु
		pr_debug("%s: no available counter found\n", __func__);
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	/*
	 * Searching क्रम an available resource selector to use, starting at
	 * '2' since every implementation has at least 2 resource selector.
	 * ETMIDR4 gives the number of resource selector _pairs_,
	 * hence multiply by 2.
	 */
	क्रम (rselector = 2; rselector < drvdata->nr_resource * 2; rselector++)
		अगर (!config->res_ctrl[rselector])
			अवरोध;

	अगर (rselector == drvdata->nr_resource * 2) अणु
		pr_debug("%s: no available resource selector found\n",
			 __func__);
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	/* Remember what counter we used */
	counter = 1 << ctridx;

	/*
	 * Initialise original and reload counter value to the smallest
	 * possible value in order to get as much precision as we can.
	 */
	config->cntr_val[ctridx] = 1;
	config->cntrldvr[ctridx] = 1;

	/* Set the trace counter control रेजिस्टर */
	val =  0x1 << 16	|  /* Bit 16, reload counter स्वतःmatically */
	       0x0 << 7		|  /* Select single resource selector */
	       0x1;		   /* Resource selector 1, i.e always true */

	config->cntr_ctrl[ctridx] = val;

	val = 0x2 << 16		| /* Group 0b0010 - Counter and sequencers */
	      counter << 0;	  /* Counter to use */

	config->res_ctrl[rselector] = val;

	val = 0x0 << 7		| /* Select single resource selector */
	      rselector;	  /* Resource selector */

	config->ts_ctrl = val;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग4_parse_event_config(काष्ठा eपंचांगv4_drvdata *drvdata,
				   काष्ठा perf_event *event)
अणु
	पूर्णांक ret = 0;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	काष्ठा perf_event_attr *attr = &event->attr;

	अगर (!attr) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Clear configuration from previous run */
	स_रखो(config, 0, माप(काष्ठा eपंचांगv4_config));

	अगर (attr->exclude_kernel)
		config->mode = ETM_MODE_EXCL_KERN;

	अगर (attr->exclude_user)
		config->mode = ETM_MODE_EXCL_USER;

	/* Always start from the शेष config */
	eपंचांग4_set_शेष_config(config);

	/* Configure filters specअगरied on the perf cmd line, अगर any. */
	ret = eपंचांग4_set_event_filters(drvdata, event);
	अगर (ret)
		जाओ out;

	/* Go from generic option to ETMv4 specअगरics */
	अगर (attr->config & BIT(ETM_OPT_CYCACC)) अणु
		config->cfg |= BIT(4);
		/* TRM: Must program this क्रम cycacc to work */
		config->ccctlr = ETM_CYC_THRESHOLD_DEFAULT;
	पूर्ण
	अगर (attr->config & BIT(ETM_OPT_TS)) अणु
		/*
		 * Configure बारtamps to be emitted at regular पूर्णांकervals in
		 * order to correlate inकाष्ठाions executed on dअगरferent CPUs
		 * (CPU-wide trace scenarios).
		 */
		ret = eपंचांग4_config_बारtamp_event(drvdata);

		/*
		 * No need to go further अगर बारtamp पूर्णांकervals can't
		 * be configured.
		 */
		अगर (ret)
			जाओ out;

		/* bit[11], Global बारtamp tracing bit */
		config->cfg |= BIT(11);
	पूर्ण

	अगर (attr->config & BIT(ETM_OPT_CTXTID))
		/* bit[6], Context ID tracing bit */
		config->cfg |= BIT(ETM4_CFG_BIT_CTXTID);

	/*
	 * If set bit ETM_OPT_CTXTID2 in perf config, this asks to trace VMID
	 * क्रम recording CONTEXTIDR_EL2.  Do not enable VMID tracing अगर the
	 * kernel is not running in EL2.
	 */
	अगर (attr->config & BIT(ETM_OPT_CTXTID2)) अणु
		अगर (!is_kernel_in_hyp_mode()) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		config->cfg |= BIT(ETM4_CFG_BIT_VMID) | BIT(ETM4_CFG_BIT_VMID_OPT);
	पूर्ण

	/* वापस stack - enable अगर selected and supported */
	अगर ((attr->config & BIT(ETM_OPT_RETSTK)) && drvdata->retstack)
		/* bit[12], Return stack enable bit */
		config->cfg |= BIT(12);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग4_enable_perf(काष्ठा coresight_device *csdev,
			    काष्ठा perf_event *event)
अणु
	पूर्णांक ret = 0;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (WARN_ON_ONCE(drvdata->cpu != smp_processor_id())) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Configure the tracer based on the session's specअगरics */
	ret = eपंचांग4_parse_event_config(drvdata, event);
	अगर (ret)
		जाओ out;
	/* And enable it */
	ret = eपंचांग4_enable_hw(drvdata);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग4_enable_sysfs(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा eपंचांग4_enable_arg arg = अणु पूर्ण;
	पूर्णांक ret;

	spin_lock(&drvdata->spinlock);

	/*
	 * Executing eपंचांग4_enable_hw on the cpu whose ETM is being enabled
	 * ensures that रेजिस्टर ग_लिखोs occur when cpu is घातered.
	 */
	arg.drvdata = drvdata;
	ret = smp_call_function_single(drvdata->cpu,
				       eपंचांग4_enable_hw_smp_call, &arg, 1);
	अगर (!ret)
		ret = arg.rc;
	अगर (!ret)
		drvdata->sticky_enable = true;
	spin_unlock(&drvdata->spinlock);

	अगर (!ret)
		dev_dbg(&csdev->dev, "ETM tracing enabled\n");
	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग4_enable(काष्ठा coresight_device *csdev,
		       काष्ठा perf_event *event, u32 mode)
अणु
	पूर्णांक ret;
	u32 val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	val = local_cmpxchg(&drvdata->mode, CS_MODE_DISABLED, mode);

	/* Someone is alपढ़ोy using the tracer */
	अगर (val)
		वापस -EBUSY;

	चयन (mode) अणु
	हाल CS_MODE_SYSFS:
		ret = eपंचांग4_enable_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		ret = eपंचांग4_enable_perf(csdev, event);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	/* The tracer didn't start */
	अगर (ret)
		local_set(&drvdata->mode, CS_MODE_DISABLED);

	वापस ret;
पूर्ण

अटल व्योम eपंचांग4_disable_hw(व्योम *info)
अणु
	u32 control;
	u64 trfcr;
	काष्ठा eपंचांगv4_drvdata *drvdata = info;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	काष्ठा coresight_device *csdev = drvdata->csdev;
	काष्ठा device *eपंचांग_dev = &csdev->dev;
	काष्ठा csdev_access *csa = &csdev->access;
	पूर्णांक i;

	eपंचांग4_cs_unlock(drvdata, csa);
	eपंचांग4_disable_arch_specअगरic(drvdata);

	अगर (!drvdata->skip_घातer_up) अणु
		/* घातer can be हटाओd from the trace unit now */
		control = eपंचांग4x_relaxed_पढ़ो32(csa, TRCPDCR);
		control &= ~TRCPDCR_PU;
		eपंचांग4x_relaxed_ग_लिखो32(csa, control, TRCPDCR);
	पूर्ण

	control = eपंचांग4x_relaxed_पढ़ो32(csa, TRCPRGCTLR);

	/* EN, bit[0] Trace unit enable bit */
	control &= ~0x1;

	/*
	 * If the CPU supports v8.4 Trace filter Control,
	 * set the ETM to trace prohibited region.
	 */
	अगर (drvdata->trfc) अणु
		trfcr = पढ़ो_sysreg_s(SYS_TRFCR_EL1);
		ग_लिखो_sysreg_s(trfcr & ~(TRFCR_ELx_ExTRE | TRFCR_ELx_E0TRE),
			       SYS_TRFCR_EL1);
		isb();
	पूर्ण
	/*
	 * Make sure everything completes beक्रमe disabling, as recommended
	 * by section 7.3.77 ("TRCVICTLR, ViewInst Main Control Register,
	 * SSTATUS") of ARM IHI 0064D
	 */
	dsb(sy);
	isb();
	/* Trace synchronization barrier, is a nop अगर not supported */
	tsb_csync();
	eपंचांग4x_relaxed_ग_लिखो32(csa, control, TRCPRGCTLR);

	/* रुको क्रम TRCSTATR.PMSTABLE to go to '1' */
	अगर (coresight_समयout(csa, TRCSTATR, TRCSTATR_PMSTABLE_BIT, 1))
		dev_err(eपंचांग_dev,
			"timeout while waiting for PM stable Trace Status\n");
	अगर (drvdata->trfc)
		ग_लिखो_sysreg_s(trfcr, SYS_TRFCR_EL1);

	/* पढ़ो the status of the single shot comparators */
	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		config->ss_status[i] =
			eपंचांग4x_relaxed_पढ़ो32(csa, TRCSSCSRn(i));
	पूर्ण

	/* पढ़ो back the current counter values */
	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		config->cntr_val[i] =
			eपंचांग4x_relaxed_पढ़ो32(csa, TRCCNTVRn(i));
	पूर्ण

	coresight_disclaim_device_unlocked(csdev);
	eपंचांग4_cs_lock(drvdata, csa);

	dev_dbg(&drvdata->csdev->dev,
		"cpu: %d disable smp call done\n", drvdata->cpu);
पूर्ण

अटल पूर्णांक eपंचांग4_disable_perf(काष्ठा coresight_device *csdev,
			     काष्ठा perf_event *event)
अणु
	u32 control;
	काष्ठा eपंचांग_filters *filters = event->hw.addr_filters;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (WARN_ON_ONCE(drvdata->cpu != smp_processor_id()))
		वापस -EINVAL;

	eपंचांग4_disable_hw(drvdata);

	/*
	 * Check अगर the start/stop logic was active when the unit was stopped.
	 * That way we can re-enable the start/stop logic when the process is
	 * scheduled again.  Configuration of the start/stop logic happens in
	 * function eपंचांग4_set_event_filters().
	 */
	control = eपंचांग4x_relaxed_पढ़ो32(&csdev->access, TRCVICTLR);
	/* TRCVICTLR::SSSTATUS, bit[9] */
	filters->ssstatus = (control & BIT(9));

	वापस 0;
पूर्ण

अटल व्योम eपंचांग4_disable_sysfs(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * Taking hotplug lock here protects from घड़ीs getting disabled
	 * with tracing being left on (crash scenario) अगर user disable occurs
	 * after cpu online mask indicates the cpu is offline but beक्रमe the
	 * DYING hotplug callback is serviced by the ETM driver.
	 */
	cpus_पढ़ो_lock();
	spin_lock(&drvdata->spinlock);

	/*
	 * Executing eपंचांग4_disable_hw on the cpu whose ETM is being disabled
	 * ensures that रेजिस्टर ग_लिखोs occur when cpu is घातered.
	 */
	smp_call_function_single(drvdata->cpu, eपंचांग4_disable_hw, drvdata, 1);

	spin_unlock(&drvdata->spinlock);
	cpus_पढ़ो_unlock();

	dev_dbg(&csdev->dev, "ETM tracing disabled\n");
पूर्ण

अटल व्योम eपंचांग4_disable(काष्ठा coresight_device *csdev,
			 काष्ठा perf_event *event)
अणु
	u32 mode;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * For as दीर्घ as the tracer isn't disabled another entity can't
	 * change its status.  As such we can पढ़ो the status here without
	 * fearing it will change under us.
	 */
	mode = local_पढ़ो(&drvdata->mode);

	चयन (mode) अणु
	हाल CS_MODE_DISABLED:
		अवरोध;
	हाल CS_MODE_SYSFS:
		eपंचांग4_disable_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		eपंचांग4_disable_perf(csdev, event);
		अवरोध;
	पूर्ण

	अगर (mode)
		local_set(&drvdata->mode, CS_MODE_DISABLED);
पूर्ण

अटल स्थिर काष्ठा coresight_ops_source eपंचांग4_source_ops = अणु
	.cpu_id		= eपंचांग4_cpu_id,
	.trace_id	= eपंचांग4_trace_id,
	.enable		= eपंचांग4_enable,
	.disable	= eपंचांग4_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops eपंचांग4_cs_ops = अणु
	.source_ops	= &eपंचांग4_source_ops,
पूर्ण;

अटल अंतरभूत bool cpu_supports_sysreg_trace(व्योम)
अणु
	u64 dfr0 = पढ़ो_sysreg_s(SYS_ID_AA64DFR0_EL1);

	वापस ((dfr0 >> ID_AA64DFR0_TRACEVER_SHIFT) & 0xfUL) > 0;
पूर्ण

अटल bool eपंचांग4_init_sysreg_access(काष्ठा eपंचांगv4_drvdata *drvdata,
				    काष्ठा csdev_access *csa)
अणु
	u32 devarch;

	अगर (!cpu_supports_sysreg_trace())
		वापस false;

	/*
	 * ETMs implementing sysreg access must implement TRCDEVARCH.
	 */
	devarch = पढ़ो_eपंचांग4x_sysreg_स्थिर_offset(TRCDEVARCH);
	चयन (devarch & ETM_DEVARCH_ID_MASK) अणु
	हाल ETM_DEVARCH_ETMv4x_ARCH:
		*csa = (काष्ठा csdev_access) अणु
			.io_mem	= false,
			.पढ़ो	= eपंचांग4x_sysreg_पढ़ो,
			.ग_लिखो	= eपंचांग4x_sysreg_ग_लिखो,
		पूर्ण;
		अवरोध;
	हाल ETM_DEVARCH_ETE_ARCH:
		*csa = (काष्ठा csdev_access) अणु
			.io_mem	= false,
			.पढ़ो	= ete_sysreg_पढ़ो,
			.ग_लिखो	= ete_sysreg_ग_लिखो,
		पूर्ण;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	drvdata->arch = eपंचांग_devarch_to_arch(devarch);
	वापस true;
पूर्ण

अटल bool eपंचांग4_init_iomem_access(काष्ठा eपंचांगv4_drvdata *drvdata,
				   काष्ठा csdev_access *csa)
अणु
	u32 devarch = पढ़ोl_relaxed(drvdata->base + TRCDEVARCH);
	u32 idr1 = पढ़ोl_relaxed(drvdata->base + TRCIDR1);

	/*
	 * All ETMs must implement TRCDEVARCH to indicate that
	 * the component is an ETMv4. To support any broken
	 * implementations we fall back to TRCIDR1 check, which
	 * is not really reliable.
	 */
	अगर ((devarch & ETM_DEVARCH_ID_MASK) == ETM_DEVARCH_ETMv4x_ARCH) अणु
		drvdata->arch = eपंचांग_devarch_to_arch(devarch);
	पूर्ण अन्यथा अणु
		pr_warn("CPU%d: ETM4x incompatible TRCDEVARCH: %x, falling back to TRCIDR1\n",
			smp_processor_id(), devarch);

		अगर (ETM_TRCIDR1_ARCH_MAJOR(idr1) != ETM_TRCIDR1_ARCH_ETMv4)
			वापस false;
		drvdata->arch = eपंचांग_trcidr_to_arch(idr1);
	पूर्ण

	*csa = CSDEV_ACCESS_IOMEM(drvdata->base);
	वापस true;
पूर्ण

अटल bool eपंचांग4_init_csdev_access(काष्ठा eपंचांगv4_drvdata *drvdata,
				   काष्ठा csdev_access *csa)
अणु
	/*
	 * Always choose the memory mapped io, अगर there is
	 * a memory map to prevent sysreg access on broken
	 * प्रणालीs.
	 */
	अगर (drvdata->base)
		वापस eपंचांग4_init_iomem_access(drvdata, csa);

	अगर (eपंचांग4_init_sysreg_access(drvdata, csa))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम cpu_enable_tracing(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	u64 dfr0 = पढ़ो_sysreg(id_aa64dfr0_el1);
	u64 trfcr;

	अगर (!cpuid_feature_extract_अचिन्हित_field(dfr0, ID_AA64DFR0_TRACE_FILT_SHIFT))
		वापस;

	drvdata->trfc = true;
	/*
	 * If the CPU supports v8.4 SelfHosted Tracing, enable
	 * tracing at the kernel EL and EL0, क्रमcing to use the
	 * भव समय as the बारtamp.
	 */
	trfcr = (TRFCR_ELx_TS_VIRTUAL |
		 TRFCR_ELx_ExTRE |
		 TRFCR_ELx_E0TRE);

	/* If we are running at EL2, allow tracing the CONTEXTIDR_EL2. */
	अगर (is_kernel_in_hyp_mode())
		trfcr |= TRFCR_EL2_CX;

	ग_लिखो_sysreg_s(trfcr, SYS_TRFCR_EL1);
पूर्ण

अटल व्योम eपंचांग4_init_arch_data(व्योम *info)
अणु
	u32 eपंचांगidr0;
	u32 eपंचांगidr2;
	u32 eपंचांगidr3;
	u32 eपंचांगidr4;
	u32 eपंचांगidr5;
	काष्ठा eपंचांग4_init_arg *init_arg = info;
	काष्ठा eपंचांगv4_drvdata *drvdata;
	काष्ठा csdev_access *csa;
	पूर्णांक i;

	drvdata = init_arg->drvdata;
	csa = init_arg->csa;

	/*
	 * If we are unable to detect the access mechanism,
	 * or unable to detect the trace unit type, fail
	 * early.
	 */
	अगर (!eपंचांग4_init_csdev_access(drvdata, csa))
		वापस;

	/* Detect the support क्रम OS Lock beक्रमe we actually use it */
	eपंचांग_detect_os_lock(drvdata, csa);

	/* Make sure all रेजिस्टरs are accessible */
	eपंचांग4_os_unlock_csa(drvdata, csa);
	eपंचांग4_cs_unlock(drvdata, csa);

	eपंचांग4_check_arch_features(drvdata, init_arg->pid);

	/* find all capabilities of the tracing unit */
	eपंचांगidr0 = eपंचांग4x_relaxed_पढ़ो32(csa, TRCIDR0);

	/* INSTP0, bits[2:1] P0 tracing support field */
	अगर (BMVAL(eपंचांगidr0, 1, 1) && BMVAL(eपंचांगidr0, 2, 2))
		drvdata->instrp0 = true;
	अन्यथा
		drvdata->instrp0 = false;

	/* TRCBB, bit[5] Branch broadcast tracing support bit */
	अगर (BMVAL(eपंचांगidr0, 5, 5))
		drvdata->trcbb = true;
	अन्यथा
		drvdata->trcbb = false;

	/* TRCCOND, bit[6] Conditional inकाष्ठाion tracing support bit */
	अगर (BMVAL(eपंचांगidr0, 6, 6))
		drvdata->trccond = true;
	अन्यथा
		drvdata->trccond = false;

	/* TRCCCI, bit[7] Cycle counting inकाष्ठाion bit */
	अगर (BMVAL(eपंचांगidr0, 7, 7))
		drvdata->trccci = true;
	अन्यथा
		drvdata->trccci = false;

	/* RETSTACK, bit[9] Return stack bit */
	अगर (BMVAL(eपंचांगidr0, 9, 9))
		drvdata->retstack = true;
	अन्यथा
		drvdata->retstack = false;

	/* NUMEVENT, bits[11:10] Number of events field */
	drvdata->nr_event = BMVAL(eपंचांगidr0, 10, 11);
	/* QSUPP, bits[16:15] Q element support field */
	drvdata->q_support = BMVAL(eपंचांगidr0, 15, 16);
	/* TSSIZE, bits[28:24] Global बारtamp size field */
	drvdata->ts_size = BMVAL(eपंचांगidr0, 24, 28);

	/* maximum size of resources */
	eपंचांगidr2 = eपंचांग4x_relaxed_पढ़ो32(csa, TRCIDR2);
	/* CIDSIZE, bits[9:5] Indicates the Context ID size */
	drvdata->ctxid_size = BMVAL(eपंचांगidr2, 5, 9);
	/* VMIDSIZE, bits[14:10] Indicates the VMID size */
	drvdata->vmid_size = BMVAL(eपंचांगidr2, 10, 14);
	/* CCSIZE, bits[28:25] size of the cycle counter in bits minus 12 */
	drvdata->ccsize = BMVAL(eपंचांगidr2, 25, 28);

	eपंचांगidr3 = eपंचांग4x_relaxed_पढ़ो32(csa, TRCIDR3);
	/* CCITMIN, bits[11:0] minimum threshold value that can be programmed */
	drvdata->cciपंचांगin = BMVAL(eपंचांगidr3, 0, 11);
	/* EXLEVEL_S, bits[19:16] Secure state inकाष्ठाion tracing */
	drvdata->s_ex_level = BMVAL(eपंचांगidr3, 16, 19);
	drvdata->config.s_ex_level = drvdata->s_ex_level;
	/* EXLEVEL_NS, bits[23:20] Non-secure state inकाष्ठाion tracing */
	drvdata->ns_ex_level = BMVAL(eपंचांगidr3, 20, 23);

	/*
	 * TRCERR, bit[24] whether a trace unit can trace a
	 * प्रणाली error exception.
	 */
	अगर (BMVAL(eपंचांगidr3, 24, 24))
		drvdata->trc_error = true;
	अन्यथा
		drvdata->trc_error = false;

	/* SYNCPR, bit[25] implementation has a fixed synchronization period? */
	अगर (BMVAL(eपंचांगidr3, 25, 25))
		drvdata->syncpr = true;
	अन्यथा
		drvdata->syncpr = false;

	/* STALLCTL, bit[26] is stall control implemented? */
	अगर (BMVAL(eपंचांगidr3, 26, 26))
		drvdata->stallctl = true;
	अन्यथा
		drvdata->stallctl = false;

	/* SYSSTALL, bit[27] implementation can support stall control? */
	अगर (BMVAL(eपंचांगidr3, 27, 27))
		drvdata->sysstall = true;
	अन्यथा
		drvdata->sysstall = false;

	/*
	 * NUMPROC - the number of PEs available क्रम tracing, 5bits
	 *         = TRCIDR3.bits[13:12]bits[30:28]
	 *  bits[4:3] = TRCIDR3.bits[13:12] (since eपंचांग-v4.2, otherwise RES0)
	 *  bits[3:0] = TRCIDR3.bits[30:28]
	 */
	drvdata->nr_pe = (BMVAL(eपंचांगidr3, 12, 13) << 3) | BMVAL(eपंचांगidr3, 28, 30);

	/* NOOVERFLOW, bit[31] is trace overflow prevention supported */
	अगर (BMVAL(eपंचांगidr3, 31, 31))
		drvdata->nooverflow = true;
	अन्यथा
		drvdata->nooverflow = false;

	/* number of resources trace unit supports */
	eपंचांगidr4 = eपंचांग4x_relaxed_पढ़ो32(csa, TRCIDR4);
	/* NUMACPAIRS, bits[0:3] number of addr comparator pairs क्रम tracing */
	drvdata->nr_addr_cmp = BMVAL(eपंचांगidr4, 0, 3);
	/* NUMPC, bits[15:12] number of PE comparator inमाला_दो क्रम tracing */
	drvdata->nr_pe_cmp = BMVAL(eपंचांगidr4, 12, 15);
	/*
	 * NUMRSPAIR, bits[19:16]
	 * The number of resource pairs conveyed by the HW starts at 0, i.e a
	 * value of 0x0 indicate 1 resource pair, 0x1 indicate two and so on.
	 * As such add 1 to the value of NUMRSPAIR क्रम a better representation.
	 *
	 * For ETM v4.3 and later, 0x0 means 0, and no pairs are available -
	 * the शेष TRUE and FALSE resource selectors are omitted.
	 * Otherwise क्रम values 0x1 and above the number is N + 1 as per v4.2.
	 */
	drvdata->nr_resource = BMVAL(eपंचांगidr4, 16, 19);
	अगर ((drvdata->arch < ETM_ARCH_V4_3) || (drvdata->nr_resource > 0))
		drvdata->nr_resource += 1;
	/*
	 * NUMSSCC, bits[23:20] the number of single-shot
	 * comparator control क्रम tracing. Read any status regs as these
	 * also contain RO capability data.
	 */
	drvdata->nr_ss_cmp = BMVAL(eपंचांगidr4, 20, 23);
	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		drvdata->config.ss_status[i] =
			eपंचांग4x_relaxed_पढ़ो32(csa, TRCSSCSRn(i));
	पूर्ण
	/* NUMCIDC, bits[27:24] number of Context ID comparators क्रम tracing */
	drvdata->numcidc = BMVAL(eपंचांगidr4, 24, 27);
	/* NUMVMIDC, bits[31:28] number of VMID comparators क्रम tracing */
	drvdata->numvmidc = BMVAL(eपंचांगidr4, 28, 31);

	eपंचांगidr5 = eपंचांग4x_relaxed_पढ़ो32(csa, TRCIDR5);
	/* NUMEXTIN, bits[8:0] number of बाह्यal inमाला_दो implemented */
	drvdata->nr_ext_inp = BMVAL(eपंचांगidr5, 0, 8);
	/* TRACEIDSIZE, bits[21:16] indicates the trace ID width */
	drvdata->trcid_size = BMVAL(eपंचांगidr5, 16, 21);
	/* ATBTRIG, bit[22] implementation can support ATB triggers? */
	अगर (BMVAL(eपंचांगidr5, 22, 22))
		drvdata->atbtrig = true;
	अन्यथा
		drvdata->atbtrig = false;
	/*
	 * LPOVERRIDE, bit[23] implementation supports
	 * low-घातer state override
	 */
	अगर (BMVAL(eपंचांगidr5, 23, 23) && (!drvdata->skip_घातer_up))
		drvdata->lpoverride = true;
	अन्यथा
		drvdata->lpoverride = false;
	/* NUMSEQSTATE, bits[27:25] number of sequencer states implemented */
	drvdata->nrseqstate = BMVAL(eपंचांगidr5, 25, 27);
	/* NUMCNTR, bits[30:28] number of counters available क्रम tracing */
	drvdata->nr_cntr = BMVAL(eपंचांगidr5, 28, 30);
	eपंचांग4_cs_lock(drvdata, csa);
	cpu_enable_tracing(drvdata);
पूर्ण

अटल अंतरभूत u32 eपंचांग4_get_victlr_access_type(काष्ठा eपंचांगv4_config *config)
अणु
	वापस eपंचांग4_get_access_type(config) << TRCVICTLR_EXLEVEL_SHIFT;
पूर्ण

/* Set ELx trace filter access in the TRCVICTLR रेजिस्टर */
अटल व्योम eपंचांग4_set_victlr_access(काष्ठा eपंचांगv4_config *config)
अणु
	config->vinst_ctrl &= ~TRCVICTLR_EXLEVEL_MASK;
	config->vinst_ctrl |= eपंचांग4_get_victlr_access_type(config);
पूर्ण

अटल व्योम eपंचांग4_set_शेष_config(काष्ठा eपंचांगv4_config *config)
अणु
	/* disable all events tracing */
	config->eventctrl0 = 0x0;
	config->eventctrl1 = 0x0;

	/* disable stalling */
	config->stall_ctrl = 0x0;

	/* enable trace synchronization every 4096 bytes, अगर available */
	config->syncfreq = 0xC;

	/* disable बारtamp event */
	config->ts_ctrl = 0x0;

	/* TRCVICTLR::EVENT = 0x01, select the always on logic */
	config->vinst_ctrl = BIT(0);

	/* TRCVICTLR::EXLEVEL_NS:EXLEVELS: Set kernel / user filtering */
	eपंचांग4_set_victlr_access(config);
पूर्ण

अटल u64 eपंचांग4_get_ns_access_type(काष्ठा eपंचांगv4_config *config)
अणु
	u64 access_type = 0;

	/*
	 * EXLEVEL_NS, क्रम NonSecure Exception levels.
	 * The mask here is a generic value and must be
	 * shअगरted to the corresponding field क्रम the रेजिस्टरs
	 */
	अगर (!is_kernel_in_hyp_mode()) अणु
		/* Stay away from hypervisor mode क्रम non-VHE */
		access_type =  ETM_EXLEVEL_NS_HYP;
		अगर (config->mode & ETM_MODE_EXCL_KERN)
			access_type |= ETM_EXLEVEL_NS_OS;
	पूर्ण अन्यथा अगर (config->mode & ETM_MODE_EXCL_KERN) अणु
		access_type = ETM_EXLEVEL_NS_HYP;
	पूर्ण

	अगर (config->mode & ETM_MODE_EXCL_USER)
		access_type |= ETM_EXLEVEL_NS_APP;

	वापस access_type;
पूर्ण

/*
 * Conकाष्ठा the exception level masks क्रम a given config.
 * This must be shअगरted to the corresponding रेजिस्टर field
 * क्रम usage.
 */
अटल u64 eपंचांग4_get_access_type(काष्ठा eपंचांगv4_config *config)
अणु
	/* All Secure exception levels are excluded from the trace */
	वापस eपंचांग4_get_ns_access_type(config) | (u64)config->s_ex_level;
पूर्ण

अटल u64 eपंचांग4_get_comparator_access_type(काष्ठा eपंचांगv4_config *config)
अणु
	वापस eपंचांग4_get_access_type(config) << TRCACATR_EXLEVEL_SHIFT;
पूर्ण

अटल व्योम eपंचांग4_set_comparator_filter(काष्ठा eपंचांगv4_config *config,
				       u64 start, u64 stop, पूर्णांक comparator)
अणु
	u64 access_type = eपंचांग4_get_comparator_access_type(config);

	/* First half of शेष address comparator */
	config->addr_val[comparator] = start;
	config->addr_acc[comparator] = access_type;
	config->addr_type[comparator] = ETM_ADDR_TYPE_RANGE;

	/* Second half of शेष address comparator */
	config->addr_val[comparator + 1] = stop;
	config->addr_acc[comparator + 1] = access_type;
	config->addr_type[comparator + 1] = ETM_ADDR_TYPE_RANGE;

	/*
	 * Configure the ViewInst function to include this address range
	 * comparator.
	 *
	 * @comparator is भागided by two since it is the index in the
	 * eपंचांगv4_config::addr_val array but रेजिस्टर TRCVIIECTLR deals with
	 * address range comparator _pairs_.
	 *
	 * Thereक्रमe:
	 *	index 0 -> compatator pair 0
	 *	index 2 -> comparator pair 1
	 *	index 4 -> comparator pair 2
	 *	...
	 *	index 14 -> comparator pair 7
	 */
	config->viiectlr |= BIT(comparator / 2);
पूर्ण

अटल व्योम eपंचांग4_set_start_stop_filter(काष्ठा eपंचांगv4_config *config,
				       u64 address, पूर्णांक comparator,
				       क्रमागत eपंचांग_addr_type type)
अणु
	पूर्णांक shअगरt;
	u64 access_type = eपंचांग4_get_comparator_access_type(config);

	/* Configure the comparator */
	config->addr_val[comparator] = address;
	config->addr_acc[comparator] = access_type;
	config->addr_type[comparator] = type;

	/*
	 * Configure ViewInst Start-Stop control रेजिस्टर.
	 * Addresses configured to start tracing go from bit 0 to n-1,
	 * जबतक those configured to stop tracing from 16 to 16 + n-1.
	 */
	shअगरt = (type == ETM_ADDR_TYPE_START ? 0 : 16);
	config->vissctlr |= BIT(shअगरt + comparator);
पूर्ण

अटल व्योम eपंचांग4_set_शेष_filter(काष्ठा eपंचांगv4_config *config)
अणु
	/* Trace everything 'default' filter achieved by no filtering */
	config->viiectlr = 0x0;

	/*
	 * TRCVICTLR::SSSTATUS == 1, the start-stop logic is
	 * in the started state
	 */
	config->vinst_ctrl |= BIT(9);
	config->mode |= ETM_MODE_VIEWINST_STARTSTOP;

	/* No start-stop filtering क्रम ViewInst */
	config->vissctlr = 0x0;
पूर्ण

अटल व्योम eपंचांग4_set_शेष(काष्ठा eपंचांगv4_config *config)
अणु
	अगर (WARN_ON_ONCE(!config))
		वापस;

	/*
	 * Make शेष initialisation trace everything
	 *
	 * This is करोne by a minimum शेष config sufficient to enable
	 * full inकाष्ठाion trace - with a शेष filter क्रम trace all
	 * achieved by having no filtering.
	 */
	eपंचांग4_set_शेष_config(config);
	eपंचांग4_set_शेष_filter(config);
पूर्ण

अटल पूर्णांक eपंचांग4_get_next_comparator(काष्ठा eपंचांगv4_drvdata *drvdata, u32 type)
अणु
	पूर्णांक nr_comparator, index = 0;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/*
	 * nr_addr_cmp holds the number of comparator _pair_, so समय 2
	 * क्रम the total number of comparators.
	 */
	nr_comparator = drvdata->nr_addr_cmp * 2;

	/* Go through the tally of comparators looking क्रम a मुक्त one. */
	जबतक (index < nr_comparator) अणु
		चयन (type) अणु
		हाल ETM_ADDR_TYPE_RANGE:
			अगर (config->addr_type[index] == ETM_ADDR_TYPE_NONE &&
			    config->addr_type[index + 1] == ETM_ADDR_TYPE_NONE)
				वापस index;

			/* Address range comparators go in pairs */
			index += 2;
			अवरोध;
		हाल ETM_ADDR_TYPE_START:
		हाल ETM_ADDR_TYPE_STOP:
			अगर (config->addr_type[index] == ETM_ADDR_TYPE_NONE)
				वापस index;

			/* Start/stop address can have odd indexes */
			index += 1;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* If we are here all the comparators have been used. */
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक eपंचांग4_set_event_filters(काष्ठा eपंचांगv4_drvdata *drvdata,
				  काष्ठा perf_event *event)
अणु
	पूर्णांक i, comparator, ret = 0;
	u64 address;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	काष्ठा eपंचांग_filters *filters = event->hw.addr_filters;

	अगर (!filters)
		जाओ शेष_filter;

	/* Sync events with what Perf got */
	perf_event_addr_filters_sync(event);

	/*
	 * If there are no filters to deal with simply go ahead with
	 * the शेष filter, i.e the entire address range.
	 */
	अगर (!filters->nr_filters)
		जाओ शेष_filter;

	क्रम (i = 0; i < filters->nr_filters; i++) अणु
		काष्ठा eपंचांग_filter *filter = &filters->eपंचांग_filter[i];
		क्रमागत eपंचांग_addr_type type = filter->type;

		/* See अगर a comparator is मुक्त. */
		comparator = eपंचांग4_get_next_comparator(drvdata, type);
		अगर (comparator < 0) अणु
			ret = comparator;
			जाओ out;
		पूर्ण

		चयन (type) अणु
		हाल ETM_ADDR_TYPE_RANGE:
			eपंचांग4_set_comparator_filter(config,
						   filter->start_addr,
						   filter->stop_addr,
						   comparator);
			/*
			 * TRCVICTLR::SSSTATUS == 1, the start-stop logic is
			 * in the started state
			 */
			config->vinst_ctrl |= BIT(9);

			/* No start-stop filtering क्रम ViewInst */
			config->vissctlr = 0x0;
			अवरोध;
		हाल ETM_ADDR_TYPE_START:
		हाल ETM_ADDR_TYPE_STOP:
			/* Get the right start or stop address */
			address = (type == ETM_ADDR_TYPE_START ?
				   filter->start_addr :
				   filter->stop_addr);

			/* Configure comparator */
			eपंचांग4_set_start_stop_filter(config, address,
						   comparator, type);

			/*
			 * If filters::ssstatus == 1, trace acquisition was
			 * started but the process was yanked away beक्रमe the
			 * the stop address was hit.  As such the start/stop
			 * logic needs to be re-started so that tracing can
			 * resume where it left.
			 *
			 * The start/stop logic status when a process is
			 * scheduled out is checked in function
			 * eपंचांग4_disable_perf().
			 */
			अगर (filters->ssstatus)
				config->vinst_ctrl |= BIT(9);

			/* No include/exclude filtering क्रम ViewInst */
			config->viiectlr = 0x0;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	जाओ out;


शेष_filter:
	eपंचांग4_set_शेष_filter(config);

out:
	वापस ret;
पूर्ण

व्योम eपंचांग4_config_trace_mode(काष्ठा eपंचांगv4_config *config)
अणु
	u32 mode;

	mode = config->mode;
	mode &= (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER);

	/* excluding kernel AND user space करोesn't make sense */
	WARN_ON_ONCE(mode == (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER));

	/* nothing to करो अगर neither flags are set */
	अगर (!(mode & ETM_MODE_EXCL_KERN) && !(mode & ETM_MODE_EXCL_USER))
		वापस;

	eपंचांग4_set_victlr_access(config);
पूर्ण

अटल पूर्णांक eपंचांग4_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	अगर (eपंचांगdrvdata[cpu]->boot_enable && !eपंचांगdrvdata[cpu]->sticky_enable)
		coresight_enable(eपंचांगdrvdata[cpu]->csdev);
	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग4_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	spin_lock(&eपंचांगdrvdata[cpu]->spinlock);
	अगर (!eपंचांगdrvdata[cpu]->os_unlock)
		eपंचांग4_os_unlock(eपंचांगdrvdata[cpu]);

	अगर (local_पढ़ो(&eपंचांगdrvdata[cpu]->mode))
		eपंचांग4_enable_hw(eपंचांगdrvdata[cpu]);
	spin_unlock(&eपंचांगdrvdata[cpu]->spinlock);
	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग4_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	spin_lock(&eपंचांगdrvdata[cpu]->spinlock);
	अगर (local_पढ़ो(&eपंचांगdrvdata[cpu]->mode))
		eपंचांग4_disable_hw(eपंचांगdrvdata[cpu]);
	spin_unlock(&eपंचांगdrvdata[cpu]->spinlock);
	वापस 0;
पूर्ण

अटल व्योम eपंचांग4_init_trace_id(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	drvdata->trcid = coresight_get_trace_id(drvdata->cpu);
पूर्ण

अटल पूर्णांक eपंचांग4_cpu_save(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा eपंचांगv4_save_state *state;
	काष्ठा coresight_device *csdev = drvdata->csdev;
	काष्ठा csdev_access *csa;
	काष्ठा device *eपंचांग_dev;

	अगर (WARN_ON(!csdev))
		वापस -ENODEV;

	eपंचांग_dev = &csdev->dev;
	csa = &csdev->access;

	/*
	 * As recommended by 3.4.1 ("The procedure when powering down the PE")
	 * of ARM IHI 0064D
	 */
	dsb(sy);
	isb();

	eपंचांग4_cs_unlock(drvdata, csa);
	/* Lock the OS lock to disable trace and बाह्यal debugger access */
	eपंचांग4_os_lock(drvdata);

	/* रुको क्रम TRCSTATR.PMSTABLE to go up */
	अगर (coresight_समयout(csa, TRCSTATR, TRCSTATR_PMSTABLE_BIT, 1)) अणु
		dev_err(eपंचांग_dev,
			"timeout while waiting for PM Stable Status\n");
		eपंचांग4_os_unlock(drvdata);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	state = drvdata->save_state;

	state->trcprgctlr = eपंचांग4x_पढ़ो32(csa, TRCPRGCTLR);
	अगर (drvdata->nr_pe)
		state->trcprocselr = eपंचांग4x_पढ़ो32(csa, TRCPROCSELR);
	state->trcconfigr = eपंचांग4x_पढ़ो32(csa, TRCCONFIGR);
	state->trcauxctlr = eपंचांग4x_पढ़ो32(csa, TRCAUXCTLR);
	state->trceventctl0r = eपंचांग4x_पढ़ो32(csa, TRCEVENTCTL0R);
	state->trceventctl1r = eपंचांग4x_पढ़ो32(csa, TRCEVENTCTL1R);
	अगर (drvdata->stallctl)
		state->trcstallctlr = eपंचांग4x_पढ़ो32(csa, TRCSTALLCTLR);
	state->trctsctlr = eपंचांग4x_पढ़ो32(csa, TRCTSCTLR);
	state->trcsyncpr = eपंचांग4x_पढ़ो32(csa, TRCSYNCPR);
	state->trcccctlr = eपंचांग4x_पढ़ो32(csa, TRCCCCTLR);
	state->trcbbctlr = eपंचांग4x_पढ़ो32(csa, TRCBBCTLR);
	state->trctraceidr = eपंचांग4x_पढ़ो32(csa, TRCTRACEIDR);
	state->trcqctlr = eपंचांग4x_पढ़ो32(csa, TRCQCTLR);

	state->trcvictlr = eपंचांग4x_पढ़ो32(csa, TRCVICTLR);
	state->trcviiectlr = eपंचांग4x_पढ़ो32(csa, TRCVIIECTLR);
	state->trcvissctlr = eपंचांग4x_पढ़ो32(csa, TRCVISSCTLR);
	अगर (drvdata->nr_pe_cmp)
		state->trcvipcssctlr = eपंचांग4x_पढ़ो32(csa, TRCVIPCSSCTLR);
	state->trcvdctlr = eपंचांग4x_पढ़ो32(csa, TRCVDCTLR);
	state->trcvdsacctlr = eपंचांग4x_पढ़ो32(csa, TRCVDSACCTLR);
	state->trcvdarcctlr = eपंचांग4x_पढ़ो32(csa, TRCVDARCCTLR);

	क्रम (i = 0; i < drvdata->nrseqstate - 1; i++)
		state->trcseqevr[i] = eपंचांग4x_पढ़ो32(csa, TRCSEQEVRn(i));

	state->trcseqrstevr = eपंचांग4x_पढ़ो32(csa, TRCSEQRSTEVR);
	state->trcseqstr = eपंचांग4x_पढ़ो32(csa, TRCSEQSTR);
	state->trcextinselr = eपंचांग4x_पढ़ो32(csa, TRCEXTINSELR);

	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		state->trccntrldvr[i] = eपंचांग4x_पढ़ो32(csa, TRCCNTRLDVRn(i));
		state->trccntctlr[i] = eपंचांग4x_पढ़ो32(csa, TRCCNTCTLRn(i));
		state->trccntvr[i] = eपंचांग4x_पढ़ो32(csa, TRCCNTVRn(i));
	पूर्ण

	क्रम (i = 0; i < drvdata->nr_resource * 2; i++)
		state->trcrsctlr[i] = eपंचांग4x_पढ़ो32(csa, TRCRSCTLRn(i));

	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		state->trcssccr[i] = eपंचांग4x_पढ़ो32(csa, TRCSSCCRn(i));
		state->trcsscsr[i] = eपंचांग4x_पढ़ो32(csa, TRCSSCSRn(i));
		अगर (eपंचांग4x_sspcicrn_present(drvdata, i))
			state->trcsspcicr[i] = eपंचांग4x_पढ़ो32(csa, TRCSSPCICRn(i));
	पूर्ण

	क्रम (i = 0; i < drvdata->nr_addr_cmp * 2; i++) अणु
		state->trcacvr[i] = eपंचांग4x_पढ़ो64(csa, TRCACVRn(i));
		state->trcacatr[i] = eपंचांग4x_पढ़ो64(csa, TRCACATRn(i));
	पूर्ण

	/*
	 * Data trace stream is architecturally prohibited क्रम A profile cores
	 * so we करोn't save (or later restore) trcdvcvr and trcdvcmr - As per
	 * section 1.3.4 ("Possible functional configurations of an ETMv4 trace
	 * unit") of ARM IHI 0064D.
	 */

	क्रम (i = 0; i < drvdata->numcidc; i++)
		state->trccidcvr[i] = eपंचांग4x_पढ़ो64(csa, TRCCIDCVRn(i));

	क्रम (i = 0; i < drvdata->numvmidc; i++)
		state->trcvmidcvr[i] = eपंचांग4x_पढ़ो64(csa, TRCVMIDCVRn(i));

	state->trccidcctlr0 = eपंचांग4x_पढ़ो32(csa, TRCCIDCCTLR0);
	अगर (drvdata->numcidc > 4)
		state->trccidcctlr1 = eपंचांग4x_पढ़ो32(csa, TRCCIDCCTLR1);

	state->trcvmidcctlr0 = eपंचांग4x_पढ़ो32(csa, TRCVMIDCCTLR0);
	अगर (drvdata->numvmidc > 4)
		state->trcvmidcctlr0 = eपंचांग4x_पढ़ो32(csa, TRCVMIDCCTLR1);

	state->trcclaimset = eपंचांग4x_पढ़ो32(csa, TRCCLAIMCLR);

	अगर (!drvdata->skip_घातer_up)
		state->trcpdcr = eपंचांग4x_पढ़ो32(csa, TRCPDCR);

	/* रुको क्रम TRCSTATR.IDLE to go up */
	अगर (coresight_समयout(csa, TRCSTATR, TRCSTATR_IDLE_BIT, 1)) अणु
		dev_err(eपंचांग_dev,
			"timeout while waiting for Idle Trace Status\n");
		eपंचांग4_os_unlock(drvdata);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	drvdata->state_needs_restore = true;

	/*
	 * Power can be हटाओd from the trace unit now. We करो this to
	 * potentially save घातer on प्रणालीs that respect the TRCPDCR_PU
	 * despite requesting software to save/restore state.
	 */
	अगर (!drvdata->skip_घातer_up)
		eपंचांग4x_relaxed_ग_लिखो32(csa, (state->trcpdcr & ~TRCPDCR_PU),
				      TRCPDCR);
out:
	eपंचांग4_cs_lock(drvdata, csa);
	वापस ret;
पूर्ण

अटल व्योम eपंचांग4_cpu_restore(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	पूर्णांक i;
	काष्ठा eपंचांगv4_save_state *state = drvdata->save_state;
	काष्ठा csdev_access पंचांगp_csa = CSDEV_ACCESS_IOMEM(drvdata->base);
	काष्ठा csdev_access *csa = &पंचांगp_csa;

	eपंचांग4_cs_unlock(drvdata, csa);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcclaimset, TRCCLAIMSET);

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcprgctlr, TRCPRGCTLR);
	अगर (drvdata->nr_pe)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcprocselr, TRCPROCSELR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcconfigr, TRCCONFIGR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcauxctlr, TRCAUXCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trceventctl0r, TRCEVENTCTL0R);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trceventctl1r, TRCEVENTCTL1R);
	अगर (drvdata->stallctl)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcstallctlr, TRCSTALLCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trctsctlr, TRCTSCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcsyncpr, TRCSYNCPR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcccctlr, TRCCCCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcbbctlr, TRCBBCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trctraceidr, TRCTRACEIDR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcqctlr, TRCQCTLR);

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvictlr, TRCVICTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcviiectlr, TRCVIIECTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvissctlr, TRCVISSCTLR);
	अगर (drvdata->nr_pe_cmp)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvipcssctlr, TRCVIPCSSCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvdctlr, TRCVDCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvdsacctlr, TRCVDSACCTLR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvdarcctlr, TRCVDARCCTLR);

	क्रम (i = 0; i < drvdata->nrseqstate - 1; i++)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcseqevr[i], TRCSEQEVRn(i));

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcseqrstevr, TRCSEQRSTEVR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcseqstr, TRCSEQSTR);
	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcextinselr, TRCEXTINSELR);

	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trccntrldvr[i], TRCCNTRLDVRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trccntctlr[i], TRCCNTCTLRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trccntvr[i], TRCCNTVRn(i));
	पूर्ण

	क्रम (i = 0; i < drvdata->nr_resource * 2; i++)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcrsctlr[i], TRCRSCTLRn(i));

	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcssccr[i], TRCSSCCRn(i));
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcsscsr[i], TRCSSCSRn(i));
		अगर (eपंचांग4x_sspcicrn_present(drvdata, i))
			eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcsspcicr[i], TRCSSPCICRn(i));
	पूर्ण

	क्रम (i = 0; i < drvdata->nr_addr_cmp * 2; i++) अणु
		eपंचांग4x_relaxed_ग_लिखो64(csa, state->trcacvr[i], TRCACVRn(i));
		eपंचांग4x_relaxed_ग_लिखो64(csa, state->trcacatr[i], TRCACATRn(i));
	पूर्ण

	क्रम (i = 0; i < drvdata->numcidc; i++)
		eपंचांग4x_relaxed_ग_लिखो64(csa, state->trccidcvr[i], TRCCIDCVRn(i));

	क्रम (i = 0; i < drvdata->numvmidc; i++)
		eपंचांग4x_relaxed_ग_लिखो64(csa, state->trcvmidcvr[i], TRCVMIDCVRn(i));

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trccidcctlr0, TRCCIDCCTLR0);
	अगर (drvdata->numcidc > 4)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trccidcctlr1, TRCCIDCCTLR1);

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvmidcctlr0, TRCVMIDCCTLR0);
	अगर (drvdata->numvmidc > 4)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcvmidcctlr0, TRCVMIDCCTLR1);

	eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcclaimset, TRCCLAIMSET);

	अगर (!drvdata->skip_घातer_up)
		eपंचांग4x_relaxed_ग_लिखो32(csa, state->trcpdcr, TRCPDCR);

	drvdata->state_needs_restore = false;

	/*
	 * As recommended by section 4.3.7 ("Synchronization when using the
	 * memory-mapped पूर्णांकerface") of ARM IHI 0064D
	 */
	dsb(sy);
	isb();

	/* Unlock the OS lock to re-enable trace and बाह्यal debug access */
	eपंचांग4_os_unlock(drvdata);
	eपंचांग4_cs_lock(drvdata, csa);
पूर्ण

अटल पूर्णांक eपंचांग4_cpu_pm_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd,
			      व्योम *v)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (!eपंचांगdrvdata[cpu])
		वापस NOTIFY_OK;

	drvdata = eपंचांगdrvdata[cpu];

	अगर (!drvdata->save_state)
		वापस NOTIFY_OK;

	अगर (WARN_ON_ONCE(drvdata->cpu != cpu))
		वापस NOTIFY_BAD;

	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		/* save the state अगर self-hosted coresight is in use */
		अगर (local_पढ़ो(&drvdata->mode))
			अगर (eपंचांग4_cpu_save(drvdata))
				वापस NOTIFY_BAD;
		अवरोध;
	हाल CPU_PM_EXIT:
	हाल CPU_PM_ENTER_FAILED:
		अगर (drvdata->state_needs_restore)
			eपंचांग4_cpu_restore(drvdata);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block eपंचांग4_cpu_pm_nb = अणु
	.notअगरier_call = eपंचांग4_cpu_pm_notअगरy,
पूर्ण;

/* Setup PM. Deals with error conditions and counts */
अटल पूर्णांक __init eपंचांग4_pm_setup(व्योम)
अणु
	पूर्णांक ret;

	ret = cpu_pm_रेजिस्टर_notअगरier(&eपंचांग4_cpu_pm_nb);
	अगर (ret)
		वापस ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ARM_CORESIGHT_STARTING,
					"arm/coresight4:starting",
					eपंचांग4_starting_cpu, eपंचांग4_dying_cpu);

	अगर (ret)
		जाओ unरेजिस्टर_notअगरier;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"arm/coresight4:online",
					eपंचांग4_online_cpu, शून्य);

	/* HP dyn state ID वापसed in ret on success */
	अगर (ret > 0) अणु
		hp_online = ret;
		वापस 0;
	पूर्ण

	/* failed dyn state - हटाओ others */
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_STARTING);

unरेजिस्टर_notअगरier:
	cpu_pm_unरेजिस्टर_notअगरier(&eपंचांग4_cpu_pm_nb);
	वापस ret;
पूर्ण

अटल व्योम eपंचांग4_pm_clear(व्योम)
अणु
	cpu_pm_unरेजिस्टर_notअगरier(&eपंचांग4_cpu_pm_nb);
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_STARTING);
	अगर (hp_online) अणु
		cpuhp_हटाओ_state_nocalls(hp_online);
		hp_online = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक eपंचांग4_probe(काष्ठा device *dev, व्योम __iomem *base, u32 eपंचांग_pid)
अणु
	पूर्णांक ret;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा eपंचांगv4_drvdata *drvdata;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;
	काष्ठा eपंचांग4_init_arg init_arg = अणु 0 पूर्ण;
	u8 major, minor;
	अक्षर *type_name;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	dev_set_drvdata(dev, drvdata);

	अगर (pm_save_enable == PARAM_PM_SAVE_FIRMWARE)
		pm_save_enable = coresight_loses_context_with_cpu(dev) ?
			       PARAM_PM_SAVE_SELF_HOSTED : PARAM_PM_SAVE_NEVER;

	अगर (pm_save_enable != PARAM_PM_SAVE_NEVER) अणु
		drvdata->save_state = devm_kदो_स्मृति(dev,
				माप(काष्ठा eपंचांगv4_save_state), GFP_KERNEL);
		अगर (!drvdata->save_state)
			वापस -ENOMEM;
	पूर्ण

	drvdata->base = base;

	spin_lock_init(&drvdata->spinlock);

	drvdata->cpu = coresight_get_cpu(dev);
	अगर (drvdata->cpu < 0)
		वापस drvdata->cpu;

	init_arg.drvdata = drvdata;
	init_arg.csa = &desc.access;
	init_arg.pid = eपंचांग_pid;

	अगर (smp_call_function_single(drvdata->cpu,
				eपंचांग4_init_arch_data,  &init_arg, 1))
		dev_err(dev, "ETM arch init failed\n");

	अगर (!drvdata->arch)
		वापस -EINVAL;

	/* TRCPDCR is not accessible with प्रणाली inकाष्ठाions. */
	अगर (!desc.access.io_mem ||
	    fwnode_property_present(dev_fwnode(dev), "qcom,skip-power-up"))
		drvdata->skip_घातer_up = true;

	major = ETM_ARCH_MAJOR_VERSION(drvdata->arch);
	minor = ETM_ARCH_MINOR_VERSION(drvdata->arch);

	अगर (eपंचांग4x_is_ete(drvdata)) अणु
		type_name = "ete";
		/* ETE v1 has major version == 0b101. Adjust this क्रम logging.*/
		major -= 4;
	पूर्ण अन्यथा अणु
		type_name = "etm";
	पूर्ण

	desc.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				   "%s%d", type_name, drvdata->cpu);
	अगर (!desc.name)
		वापस -ENOMEM;

	eपंचांग4_init_trace_id(drvdata);
	eपंचांग4_set_शेष(&drvdata->config);

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	dev->platक्रमm_data = pdata;

	desc.type = CORESIGHT_DEV_TYPE_SOURCE;
	desc.subtype.source_subtype = CORESIGHT_DEV_SUBTYPE_SOURCE_PROC;
	desc.ops = &eपंचांग4_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.groups = coresight_eपंचांगv4_groups;
	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev))
		वापस PTR_ERR(drvdata->csdev);

	ret = eपंचांग_perf_symlink(drvdata->csdev, true);
	अगर (ret) अणु
		coresight_unरेजिस्टर(drvdata->csdev);
		वापस ret;
	पूर्ण

	eपंचांगdrvdata[drvdata->cpu] = drvdata;

	dev_info(&drvdata->csdev->dev, "CPU%d: %s v%d.%d initialized\n",
		 drvdata->cpu, type_name, major, minor);

	अगर (boot_enable) अणु
		coresight_enable(drvdata->csdev);
		drvdata->boot_enable = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग4_probe_amba(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा resource *res = &adev->res;
	पूर्णांक ret;

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ret = eपंचांग4_probe(dev, base, id->id);
	अगर (!ret)
		pm_runसमय_put(&adev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग4_probe_platक्रमm_dev(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/*
	 * System रेजिस्टर based devices could match the
	 * HW by पढ़ोing appropriate रेजिस्टरs on the HW
	 * and thus we could skip the PID.
	 */
	ret = eपंचांग4_probe(&pdev->dev, शून्य, 0);

	pm_runसमय_put(&pdev->dev);
	वापस ret;
पूर्ण

अटल काष्ठा amba_cs_uci_id uci_id_eपंचांग4[] = अणु
	अणु
		/*  ETMv4 UCI data */
		.devarch	= ETM_DEVARCH_ETMv4x_ARCH,
		.devarch_mask	= ETM_DEVARCH_ID_MASK,
		.devtype	= 0x00000013,
	पूर्ण
पूर्ण;

अटल व्योम clear_eपंचांगdrvdata(व्योम *info)
अणु
	पूर्णांक cpu = *(पूर्णांक *)info;

	eपंचांगdrvdata[cpu] = शून्य;
पूर्ण

अटल पूर्णांक __निकास eपंचांग4_हटाओ_dev(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	eपंचांग_perf_symlink(drvdata->csdev, false);
	/*
	 * Taking hotplug lock here to aव्योम racing between eपंचांग4_हटाओ_dev()
	 * and CPU hotplug call backs.
	 */
	cpus_पढ़ो_lock();
	/*
	 * The पढ़ोers क्रम eपंचांगdrvdata[] are CPU hotplug call backs
	 * and PM notअगरication call backs. Change eपंचांगdrvdata[i] on
	 * CPU i ensures these call backs has consistent view
	 * inside one call back function.
	 */
	अगर (smp_call_function_single(drvdata->cpu, clear_eपंचांगdrvdata, &drvdata->cpu, 1))
		eपंचांगdrvdata[drvdata->cpu] = शून्य;

	cpus_पढ़ो_unlock();

	coresight_unरेजिस्टर(drvdata->csdev);

	वापस 0;
पूर्ण

अटल व्योम __निकास eपंचांग4_हटाओ_amba(काष्ठा amba_device *adev)
अणु
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	अगर (drvdata)
		eपंचांग4_हटाओ_dev(drvdata);
पूर्ण

अटल पूर्णांक __निकास eपंचांग4_हटाओ_platक्रमm_dev(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(&pdev->dev);

	अगर (drvdata)
		ret = eपंचांग4_हटाओ_dev(drvdata);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा amba_id eपंचांग4_ids[] = अणु
	CS_AMBA_ID(0x000bb95d),			/* Cortex-A53 */
	CS_AMBA_ID(0x000bb95e),			/* Cortex-A57 */
	CS_AMBA_ID(0x000bb95a),			/* Cortex-A72 */
	CS_AMBA_ID(0x000bb959),			/* Cortex-A73 */
	CS_AMBA_UCI_ID(0x000bb9da, uci_id_eपंचांग4),/* Cortex-A35 */
	CS_AMBA_UCI_ID(0x000bbd05, uci_id_eपंचांग4),/* Cortex-A55 */
	CS_AMBA_UCI_ID(0x000bbd0a, uci_id_eपंचांग4),/* Cortex-A75 */
	CS_AMBA_UCI_ID(0x000bbd0c, uci_id_eपंचांग4),/* Neoverse N1 */
	CS_AMBA_UCI_ID(0x000bbd41, uci_id_eपंचांग4),/* Cortex-A78 */
	CS_AMBA_UCI_ID(0x000f0205, uci_id_eपंचांग4),/* Qualcomm Kryo */
	CS_AMBA_UCI_ID(0x000f0211, uci_id_eपंचांग4),/* Qualcomm Kryo */
	CS_AMBA_UCI_ID(0x000bb802, uci_id_eपंचांग4),/* Qualcomm Kryo 385 Cortex-A55 */
	CS_AMBA_UCI_ID(0x000bb803, uci_id_eपंचांग4),/* Qualcomm Kryo 385 Cortex-A75 */
	CS_AMBA_UCI_ID(0x000bb805, uci_id_eपंचांग4),/* Qualcomm Kryo 4XX Cortex-A55 */
	CS_AMBA_UCI_ID(0x000bb804, uci_id_eपंचांग4),/* Qualcomm Kryo 4XX Cortex-A76 */
	CS_AMBA_UCI_ID(0x000cc0af, uci_id_eपंचांग4),/* Marvell ThunderX2 */
	CS_AMBA_UCI_ID(0x000b6d01, uci_id_eपंचांग4),/* HiSilicon-Hip08 */
	CS_AMBA_UCI_ID(0x000b6d02, uci_id_eपंचांग4),/* HiSilicon-Hip09 */
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, eपंचांग4_ids);

अटल काष्ठा amba_driver eपंचांग4x_amba_driver = अणु
	.drv = अणु
		.name   = "coresight-etm4x",
		.owner  = THIS_MODULE,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= eपंचांग4_probe_amba,
	.हटाओ         = eपंचांग4_हटाओ_amba,
	.id_table	= eपंचांग4_ids,
पूर्ण;

अटल स्थिर काष्ठा of_device_id eपंचांग4_sysreg_match[] = अणु
	अणु .compatible	= "arm,coresight-etm4x-sysreg" पूर्ण,
	अणु .compatible	= "arm,embedded-trace-extension" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver eपंचांग4_platक्रमm_driver = अणु
	.probe		= eपंचांग4_probe_platक्रमm_dev,
	.हटाओ		= eपंचांग4_हटाओ_platक्रमm_dev,
	.driver			= अणु
		.name			= "coresight-etm4x",
		.of_match_table		= eपंचांग4_sysreg_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init eपंचांग4x_init(व्योम)
अणु
	पूर्णांक ret;

	ret = eपंचांग4_pm_setup();

	/* eपंचांग4_pm_setup() करोes its own cleanup - निकास on error */
	अगर (ret)
		वापस ret;

	ret = amba_driver_रेजिस्टर(&eपंचांग4x_amba_driver);
	अगर (ret) अणु
		pr_err("Error registering etm4x AMBA driver\n");
		जाओ clear_pm;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&eपंचांग4_platक्रमm_driver);
	अगर (!ret)
		वापस 0;

	pr_err("Error registering etm4x platform driver\n");
	amba_driver_unरेजिस्टर(&eपंचांग4x_amba_driver);

clear_pm:
	eपंचांग4_pm_clear();
	वापस ret;
पूर्ण

अटल व्योम __निकास eपंचांग4x_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&eपंचांग4x_amba_driver);
	platक्रमm_driver_unरेजिस्टर(&eपंचांग4_platक्रमm_driver);
	eपंचांग4_pm_clear();
पूर्ण

module_init(eपंचांग4x_init);
module_निकास(eपंचांग4x_निकास);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight Program Flow Trace v4.x driver");
MODULE_LICENSE("GPL v2");
