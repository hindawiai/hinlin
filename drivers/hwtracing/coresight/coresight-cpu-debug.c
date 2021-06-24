<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Linaro Limited. All rights reserved.
 *
 * Author: Leo Yan <leo.yan@linaro.org>
 */
#समावेश <linux/amba/bus.h>
#समावेश <linux/coresight.h>
#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश "coresight-priv.h"

#घोषणा EDPCSR				0x0A0
#घोषणा EDCIDSR				0x0A4
#घोषणा EDVIDSR				0x0A8
#घोषणा EDPCSR_HI			0x0AC
#घोषणा EDOSLAR				0x300
#घोषणा EDPRCR				0x310
#घोषणा EDPRSR				0x314
#घोषणा EDDEVID1			0xFC4
#घोषणा EDDEVID				0xFC8

#घोषणा EDPCSR_PROHIBITED		0xFFFFFFFF

/* bits definition क्रम EDPCSR */
#घोषणा EDPCSR_THUMB			BIT(0)
#घोषणा EDPCSR_ARM_INST_MASK		GENMASK(31, 2)
#घोषणा EDPCSR_THUMB_INST_MASK		GENMASK(31, 1)

/* bits definition क्रम EDPRCR */
#घोषणा EDPRCR_COREPURQ			BIT(3)
#घोषणा EDPRCR_CORENPDRQ		BIT(0)

/* bits definition क्रम EDPRSR */
#घोषणा EDPRSR_DLK			BIT(6)
#घोषणा EDPRSR_PU			BIT(0)

/* bits definition क्रम EDVIDSR */
#घोषणा EDVIDSR_NS			BIT(31)
#घोषणा EDVIDSR_E2			BIT(30)
#घोषणा EDVIDSR_E3			BIT(29)
#घोषणा EDVIDSR_HV			BIT(28)
#घोषणा EDVIDSR_VMID			GENMASK(7, 0)

/*
 * bits definition क्रम EDDEVID1:PSCROffset
 *
 * NOTE: armv8 and armv7 have dअगरferent definition क्रम the रेजिस्टर,
 * so consolidate the bits definition as below:
 *
 * 0b0000 - Sample offset applies based on the inकाष्ठाion state, we
 *          rely on EDDEVID to check अगर EDPCSR is implemented or not
 * 0b0001 - No offset applies.
 * 0b0010 - No offset applies, but करो not use in AArch32 mode
 *
 */
#घोषणा EDDEVID1_PCSR_OFFSET_MASK	GENMASK(3, 0)
#घोषणा EDDEVID1_PCSR_OFFSET_INS_SET	(0x0)
#घोषणा EDDEVID1_PCSR_NO_OFFSET_DIS_AARCH32	(0x2)

/* bits definition क्रम EDDEVID */
#घोषणा EDDEVID_PCSAMPLE_MODE		GENMASK(3, 0)
#घोषणा EDDEVID_IMPL_EDPCSR		(0x1)
#घोषणा EDDEVID_IMPL_EDPCSR_EDCIDSR	(0x2)
#घोषणा EDDEVID_IMPL_FULL		(0x3)

#घोषणा DEBUG_WAIT_SLEEP		1000
#घोषणा DEBUG_WAIT_TIMEOUT		32000

काष्ठा debug_drvdata अणु
	व्योम __iomem	*base;
	काष्ठा device	*dev;
	पूर्णांक		cpu;

	bool		edpcsr_present;
	bool		edcidsr_present;
	bool		edvidsr_present;
	bool		pc_has_offset;

	u32		edpcsr;
	u32		edpcsr_hi;
	u32		edprsr;
	u32		edvidsr;
	u32		edcidsr;
पूर्ण;

अटल DEFINE_MUTEX(debug_lock);
अटल DEFINE_PER_CPU(काष्ठा debug_drvdata *, debug_drvdata);
अटल पूर्णांक debug_count;
अटल काष्ठा dentry *debug_debugfs_dir;

अटल bool debug_enable;
module_param_named(enable, debug_enable, bool, 0600);
MODULE_PARM_DESC(enable, "Control to enable coresight CPU debug functionality");

अटल व्योम debug_os_unlock(काष्ठा debug_drvdata *drvdata)
अणु
	/* Unlocks the debug रेजिस्टरs */
	ग_लिखोl_relaxed(0x0, drvdata->base + EDOSLAR);

	/* Make sure the रेजिस्टरs are unlocked beक्रमe accessing */
	wmb();
पूर्ण

/*
 * According to ARM DDI 0487A.k, beक्रमe access बाह्यal debug
 * रेजिस्टरs should firstly check the access permission; अगर any
 * below condition has been met then cannot access debug
 * रेजिस्टरs to aव्योम lockup issue:
 *
 * - CPU घातer करोमुख्य is घातered off;
 * - The OS Double Lock is locked;
 *
 * By checking EDPRSR can get to know अगर meet these conditions.
 */
अटल bool debug_access_permitted(काष्ठा debug_drvdata *drvdata)
अणु
	/* CPU is घातered off */
	अगर (!(drvdata->edprsr & EDPRSR_PU))
		वापस false;

	/* The OS Double Lock is locked */
	अगर (drvdata->edprsr & EDPRSR_DLK)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम debug_क्रमce_cpu_घातered_up(काष्ठा debug_drvdata *drvdata)
अणु
	u32 edprcr;

try_again:

	/*
	 * Send request to घातer management controller and निश्चित
	 * DBGPWRUPREQ संकेत; अगर घातer management controller has
	 * sane implementation, it should enable CPU घातer करोमुख्य
	 * in हाल CPU is in low घातer state.
	 */
	edprcr = पढ़ोl_relaxed(drvdata->base + EDPRCR);
	edprcr |= EDPRCR_COREPURQ;
	ग_लिखोl_relaxed(edprcr, drvdata->base + EDPRCR);

	/* Wait क्रम CPU to be घातered up (समयout~=32ms) */
	अगर (पढ़ोx_poll_समयout_atomic(पढ़ोl_relaxed, drvdata->base + EDPRSR,
			drvdata->edprsr, (drvdata->edprsr & EDPRSR_PU),
			DEBUG_WAIT_SLEEP, DEBUG_WAIT_TIMEOUT)) अणु
		/*
		 * Unक्रमtunately the CPU cannot be घातered up, so वापस
		 * back and later has no permission to access other
		 * रेजिस्टरs. For this हाल, should disable CPU low घातer
		 * states to ensure CPU घातer करोमुख्य is enabled!
		 */
		dev_err(drvdata->dev, "%s: power up request for CPU%d failed\n",
			__func__, drvdata->cpu);
		वापस;
	पूर्ण

	/*
	 * At this poपूर्णांक the CPU is घातered up, so set the no घातerकरोwn
	 * request bit so we करोn't lose घातer and emulate घातer करोwn.
	 */
	edprcr = पढ़ोl_relaxed(drvdata->base + EDPRCR);
	edprcr |= EDPRCR_COREPURQ | EDPRCR_CORENPDRQ;
	ग_लिखोl_relaxed(edprcr, drvdata->base + EDPRCR);

	drvdata->edprsr = पढ़ोl_relaxed(drvdata->base + EDPRSR);

	/* The core घातer करोमुख्य got चयनed off on use, try again */
	अगर (unlikely(!(drvdata->edprsr & EDPRSR_PU)))
		जाओ try_again;
पूर्ण

अटल व्योम debug_पढ़ो_regs(काष्ठा debug_drvdata *drvdata)
अणु
	u32 save_edprcr;

	CS_UNLOCK(drvdata->base);

	/* Unlock os lock */
	debug_os_unlock(drvdata);

	/* Save EDPRCR रेजिस्टर */
	save_edprcr = पढ़ोl_relaxed(drvdata->base + EDPRCR);

	/*
	 * Ensure CPU घातer करोमुख्य is enabled to let रेजिस्टरs
	 * are accessiable.
	 */
	debug_क्रमce_cpu_घातered_up(drvdata);

	अगर (!debug_access_permitted(drvdata))
		जाओ out;

	drvdata->edpcsr = पढ़ोl_relaxed(drvdata->base + EDPCSR);

	/*
	 * As described in ARM DDI 0487A.k, अगर the processing
	 * element (PE) is in debug state, or sample-based
	 * profiling is prohibited, EDPCSR पढ़ोs as 0xFFFFFFFF;
	 * EDCIDSR, EDVIDSR and EDPCSR_HI रेजिस्टरs also become
	 * UNKNOWN state. So directly bail out क्रम this हाल.
	 */
	अगर (drvdata->edpcsr == EDPCSR_PROHIBITED)
		जाओ out;

	/*
	 * A पढ़ो of the EDPCSR normally has the side-effect of
	 * indirectly writing to EDCIDSR, EDVIDSR and EDPCSR_HI;
	 * at this poपूर्णांक it's safe to पढ़ो value from them.
	 */
	अगर (IS_ENABLED(CONFIG_64BIT))
		drvdata->edpcsr_hi = पढ़ोl_relaxed(drvdata->base + EDPCSR_HI);

	अगर (drvdata->edcidsr_present)
		drvdata->edcidsr = पढ़ोl_relaxed(drvdata->base + EDCIDSR);

	अगर (drvdata->edvidsr_present)
		drvdata->edvidsr = पढ़ोl_relaxed(drvdata->base + EDVIDSR);

out:
	/* Restore EDPRCR रेजिस्टर */
	ग_लिखोl_relaxed(save_edprcr, drvdata->base + EDPRCR);

	CS_LOCK(drvdata->base);
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल अचिन्हित दीर्घ debug_adjust_pc(काष्ठा debug_drvdata *drvdata)
अणु
	वापस (अचिन्हित दीर्घ)drvdata->edpcsr_hi << 32 |
	       (अचिन्हित दीर्घ)drvdata->edpcsr;
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ debug_adjust_pc(काष्ठा debug_drvdata *drvdata)
अणु
	अचिन्हित दीर्घ arm_inst_offset = 0, thumb_inst_offset = 0;
	अचिन्हित दीर्घ pc;

	pc = (अचिन्हित दीर्घ)drvdata->edpcsr;

	अगर (drvdata->pc_has_offset) अणु
		arm_inst_offset = 8;
		thumb_inst_offset = 4;
	पूर्ण

	/* Handle thumb inकाष्ठाion */
	अगर (pc & EDPCSR_THUMB) अणु
		pc = (pc & EDPCSR_THUMB_INST_MASK) - thumb_inst_offset;
		वापस pc;
	पूर्ण

	/*
	 * Handle arm inकाष्ठाion offset, अगर the arm inकाष्ठाion
	 * is not 4 byte alignment then it's possible the हाल
	 * क्रम implementation defined; keep original value क्रम this
	 * हाल and prपूर्णांक info क्रम notice.
	 */
	अगर (pc & BIT(1))
		dev_emerg(drvdata->dev,
			  "Instruction offset is implementation defined\n");
	अन्यथा
		pc = (pc & EDPCSR_ARM_INST_MASK) - arm_inst_offset;

	वापस pc;
पूर्ण
#पूर्ण_अगर

अटल व्योम debug_dump_regs(काष्ठा debug_drvdata *drvdata)
अणु
	काष्ठा device *dev = drvdata->dev;
	अचिन्हित दीर्घ pc;

	dev_emerg(dev, " EDPRSR:  %08x (Power:%s DLK:%s)\n",
		  drvdata->edprsr,
		  drvdata->edprsr & EDPRSR_PU ? "On" : "Off",
		  drvdata->edprsr & EDPRSR_DLK ? "Lock" : "Unlock");

	अगर (!debug_access_permitted(drvdata)) अणु
		dev_emerg(dev, "No permission to access debug registers!\n");
		वापस;
	पूर्ण

	अगर (drvdata->edpcsr == EDPCSR_PROHIBITED) अणु
		dev_emerg(dev, "CPU is in Debug state or profiling is prohibited!\n");
		वापस;
	पूर्ण

	pc = debug_adjust_pc(drvdata);
	dev_emerg(dev, " EDPCSR:  %pS\n", (व्योम *)pc);

	अगर (drvdata->edcidsr_present)
		dev_emerg(dev, " EDCIDSR: %08x\n", drvdata->edcidsr);

	अगर (drvdata->edvidsr_present)
		dev_emerg(dev, " EDVIDSR: %08x (State:%s Mode:%s Width:%dbits VMID:%x)\n",
			  drvdata->edvidsr,
			  drvdata->edvidsr & EDVIDSR_NS ?
			  "Non-secure" : "Secure",
			  drvdata->edvidsr & EDVIDSR_E3 ? "EL3" :
				(drvdata->edvidsr & EDVIDSR_E2 ?
				 "EL2" : "EL1/0"),
			  drvdata->edvidsr & EDVIDSR_HV ? 64 : 32,
			  drvdata->edvidsr & (u32)EDVIDSR_VMID);
पूर्ण

अटल व्योम debug_init_arch_data(व्योम *info)
अणु
	काष्ठा debug_drvdata *drvdata = info;
	u32 mode, pcsr_offset;
	u32 eddevid, eddevid1;

	CS_UNLOCK(drvdata->base);

	/* Read device info */
	eddevid  = पढ़ोl_relaxed(drvdata->base + EDDEVID);
	eddevid1 = पढ़ोl_relaxed(drvdata->base + EDDEVID1);

	CS_LOCK(drvdata->base);

	/* Parse implementation feature */
	mode = eddevid & EDDEVID_PCSAMPLE_MODE;
	pcsr_offset = eddevid1 & EDDEVID1_PCSR_OFFSET_MASK;

	drvdata->edpcsr_present  = false;
	drvdata->edcidsr_present = false;
	drvdata->edvidsr_present = false;
	drvdata->pc_has_offset   = false;

	चयन (mode) अणु
	हाल EDDEVID_IMPL_FULL:
		drvdata->edvidsr_present = true;
		fallthrough;
	हाल EDDEVID_IMPL_EDPCSR_EDCIDSR:
		drvdata->edcidsr_present = true;
		fallthrough;
	हाल EDDEVID_IMPL_EDPCSR:
		/*
		 * In ARM DDI 0487A.k, the EDDEVID1.PCSROffset is used to
		 * define अगर has the offset क्रम PC sampling value; अगर पढ़ो
		 * back EDDEVID1.PCSROffset == 0x2, then this means the debug
		 * module करोes not sample the inकाष्ठाion set state when
		 * armv8 CPU in AArch32 state.
		 */
		drvdata->edpcsr_present =
			((IS_ENABLED(CONFIG_64BIT) && pcsr_offset != 0) ||
			 (pcsr_offset != EDDEVID1_PCSR_NO_OFFSET_DIS_AARCH32));

		drvdata->pc_has_offset =
			(pcsr_offset == EDDEVID1_PCSR_OFFSET_INS_SET);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Dump out inक्रमmation on panic.
 */
अटल पूर्णांक debug_notअगरier_call(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ v, व्योम *p)
अणु
	पूर्णांक cpu;
	काष्ठा debug_drvdata *drvdata;

	mutex_lock(&debug_lock);

	/* Bail out अगर the functionality is disabled */
	अगर (!debug_enable)
		जाओ skip_dump;

	pr_emerg("ARM external debug module:\n");

	क्रम_each_possible_cpu(cpu) अणु
		drvdata = per_cpu(debug_drvdata, cpu);
		अगर (!drvdata)
			जारी;

		dev_emerg(drvdata->dev, "CPU[%d]:\n", drvdata->cpu);

		debug_पढ़ो_regs(drvdata);
		debug_dump_regs(drvdata);
	पूर्ण

skip_dump:
	mutex_unlock(&debug_lock);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block debug_notअगरier = अणु
	.notअगरier_call = debug_notअगरier_call,
पूर्ण;

अटल पूर्णांक debug_enable_func(व्योम)
अणु
	काष्ठा debug_drvdata *drvdata;
	पूर्णांक cpu, ret = 0;
	cpumask_t mask;

	/*
	 * Use cpumask to track which debug घातer करोमुख्यs have
	 * been घातered on and use it to handle failure हाल.
	 */
	cpumask_clear(&mask);

	क्रम_each_possible_cpu(cpu) अणु
		drvdata = per_cpu(debug_drvdata, cpu);
		अगर (!drvdata)
			जारी;

		ret = pm_runसमय_get_sync(drvdata->dev);
		अगर (ret < 0)
			जाओ err;
		अन्यथा
			cpumask_set_cpu(cpu, &mask);
	पूर्ण

	वापस 0;

err:
	/*
	 * If pm_runसमय_get_sync() has failed, need rollback on
	 * all the other CPUs that have been enabled beक्रमe that.
	 */
	क्रम_each_cpu(cpu, &mask) अणु
		drvdata = per_cpu(debug_drvdata, cpu);
		pm_runसमय_put_noidle(drvdata->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक debug_disable_func(व्योम)
अणु
	काष्ठा debug_drvdata *drvdata;
	पूर्णांक cpu, ret, err = 0;

	/*
	 * Disable debug घातer करोमुख्यs, records the error and keep
	 * circling through all other CPUs when an error has been
	 * encountered.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		drvdata = per_cpu(debug_drvdata, cpu);
		अगर (!drvdata)
			जारी;

		ret = pm_runसमय_put(drvdata->dev);
		अगर (ret < 0)
			err = ret;
	पूर्ण

	वापस err;
पूर्ण

अटल sमाप_प्रकार debug_func_knob_ग_लिखो(काष्ठा file *f,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8_from_user(buf, count, 2, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&debug_lock);

	अगर (val == debug_enable)
		जाओ out;

	अगर (val)
		ret = debug_enable_func();
	अन्यथा
		ret = debug_disable_func();

	अगर (ret) अणु
		pr_err("%s: unable to %s debug function: %d\n",
		       __func__, val ? "enable" : "disable", ret);
		जाओ err;
	पूर्ण

	debug_enable = val;
out:
	ret = count;
err:
	mutex_unlock(&debug_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार debug_func_knob_पढ़ो(काष्ठा file *f,
		अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	अक्षर buf[3];

	mutex_lock(&debug_lock);
	snम_लिखो(buf, माप(buf), "%d\n", debug_enable);
	mutex_unlock(&debug_lock);

	ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, माप(buf));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_func_knob_fops = अणु
	.खोलो	= simple_खोलो,
	.पढ़ो	= debug_func_knob_पढ़ो,
	.ग_लिखो	= debug_func_knob_ग_लिखो,
पूर्ण;

अटल पूर्णांक debug_func_init(व्योम)
अणु
	पूर्णांक ret;

	/* Create debugfs node */
	debug_debugfs_dir = debugfs_create_dir("coresight_cpu_debug", शून्य);
	debugfs_create_file("enable", 0644, debug_debugfs_dir, शून्य,
			    &debug_func_knob_fops);

	/* Register function to be called क्रम panic */
	ret = atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					     &debug_notअगरier);
	अगर (ret) अणु
		pr_err("%s: unable to register notifier: %d\n",
		       __func__, ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	debugfs_हटाओ_recursive(debug_debugfs_dir);
	वापस ret;
पूर्ण

अटल व्योम debug_func_निकास(व्योम)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &debug_notअगरier);
	debugfs_हटाओ_recursive(debug_debugfs_dir);
पूर्ण

अटल पूर्णांक debug_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा debug_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	पूर्णांक ret;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->cpu = coresight_get_cpu(dev);
	अगर (drvdata->cpu < 0)
		वापस drvdata->cpu;

	अगर (per_cpu(debug_drvdata, drvdata->cpu)) अणु
		dev_err(dev, "CPU%d drvdata has already been initialized\n",
			drvdata->cpu);
		वापस -EBUSY;
	पूर्ण

	drvdata->dev = &adev->dev;
	amba_set_drvdata(adev, drvdata);

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drvdata->base = base;

	get_online_cpus();
	per_cpu(debug_drvdata, drvdata->cpu) = drvdata;
	ret = smp_call_function_single(drvdata->cpu, debug_init_arch_data,
				       drvdata, 1);
	put_online_cpus();

	अगर (ret) अणु
		dev_err(dev, "CPU%d debug arch init failed\n", drvdata->cpu);
		जाओ err;
	पूर्ण

	अगर (!drvdata->edpcsr_present) अणु
		dev_err(dev, "CPU%d sample-based profiling isn't implemented\n",
			drvdata->cpu);
		ret = -ENXIO;
		जाओ err;
	पूर्ण

	अगर (!debug_count++) अणु
		ret = debug_func_init();
		अगर (ret)
			जाओ err_func_init;
	पूर्ण

	mutex_lock(&debug_lock);
	/* Turn off debug घातer करोमुख्य अगर debugging is disabled */
	अगर (!debug_enable)
		pm_runसमय_put(dev);
	mutex_unlock(&debug_lock);

	dev_info(dev, "Coresight debug-CPU%d initialized\n", drvdata->cpu);
	वापस 0;

err_func_init:
	debug_count--;
err:
	per_cpu(debug_drvdata, drvdata->cpu) = शून्य;
	वापस ret;
पूर्ण

अटल व्योम debug_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा debug_drvdata *drvdata = amba_get_drvdata(adev);

	per_cpu(debug_drvdata, drvdata->cpu) = शून्य;

	mutex_lock(&debug_lock);
	/* Turn off debug घातer करोमुख्य beक्रमe rmmod the module */
	अगर (debug_enable)
		pm_runसमय_put(dev);
	mutex_unlock(&debug_lock);

	अगर (!--debug_count)
		debug_func_निकास();
पूर्ण

अटल स्थिर काष्ठा amba_cs_uci_id uci_id_debug[] = अणु
	अणु
		/*  CPU Debug UCI data */
		.devarch	= 0x47706a15,
		.devarch_mask	= 0xfff0ffff,
		.devtype	= 0x00000015,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा amba_id debug_ids[] = अणु
	CS_AMBA_ID(0x000bbd03),				/* Cortex-A53 */
	CS_AMBA_ID(0x000bbd07),				/* Cortex-A57 */
	CS_AMBA_ID(0x000bbd08),				/* Cortex-A72 */
	CS_AMBA_ID(0x000bbd09),				/* Cortex-A73 */
	CS_AMBA_UCI_ID(0x000f0205, uci_id_debug),	/* Qualcomm Kryo */
	CS_AMBA_UCI_ID(0x000f0211, uci_id_debug),	/* Qualcomm Kryo */
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, debug_ids);

अटल काष्ठा amba_driver debug_driver = अणु
	.drv = अणु
		.name   = "coresight-cpu-debug",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= debug_probe,
	.हटाओ		= debug_हटाओ,
	.id_table	= debug_ids,
पूर्ण;

module_amba_driver(debug_driver);

MODULE_AUTHOR("Leo Yan <leo.yan@linaro.org>");
MODULE_DESCRIPTION("ARM Coresight CPU Debug Driver");
MODULE_LICENSE("GPL");
