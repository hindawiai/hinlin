<शैली गुरु>
/*
 * Versatile Express Serial Power Controller (SPC) support
 *
 * Copyright (C) 2013 ARM Ltd.
 *
 * Authors: Sudeep KarkadaNagesha <sudeep.karkadanagesha@arm.com>
 *          Achin Gupta           <achin.gupta@arm.com>
 *          Lorenzo Pieralisi     <lorenzo.pieralisi@arm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/semaphore.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "spc.h"

#घोषणा SPCLOG "vexpress-spc: "

#घोषणा PERF_LVL_A15		0x00
#घोषणा PERF_REQ_A15		0x04
#घोषणा PERF_LVL_A7		0x08
#घोषणा PERF_REQ_A7		0x0c
#घोषणा COMMS			0x10
#घोषणा COMMS_REQ		0x14
#घोषणा PWC_STATUS		0x18
#घोषणा PWC_FLAG		0x1c

/* SPC wake-up IRQs status and mask */
#घोषणा WAKE_INT_MASK		0x24
#घोषणा WAKE_INT_RAW		0x28
#घोषणा WAKE_INT_STAT		0x2c
/* SPC घातer करोwn रेजिस्टरs */
#घोषणा A15_PWRDN_EN		0x30
#घोषणा A7_PWRDN_EN		0x34
/* SPC per-CPU mailboxes */
#घोषणा A15_BX_ADDR0		0x68
#घोषणा A7_BX_ADDR0		0x78

/* SPC CPU/cluster reset statue */
#घोषणा STANDBYWFI_STAT		0x3c
#घोषणा STANDBYWFI_STAT_A15_CPU_MASK(cpu)	(1 << (cpu))
#घोषणा STANDBYWFI_STAT_A7_CPU_MASK(cpu)	(1 << (3 + (cpu)))

/* SPC प्रणाली config पूर्णांकerface रेजिस्टरs */
#घोषणा SYSCFG_WDATA		0x70
#घोषणा SYSCFG_RDATA		0x74

/* A15/A7 OPP भव रेजिस्टर base */
#घोषणा A15_PERFVAL_BASE	0xC10
#घोषणा A7_PERFVAL_BASE		0xC30

/* Config पूर्णांकerface control bits */
#घोषणा SYSCFG_START		BIT(31)
#घोषणा SYSCFG_SCC		(6 << 20)
#घोषणा SYSCFG_STAT		(14 << 20)

/* wake-up पूर्णांकerrupt masks */
#घोषणा GBL_WAKEUP_INT_MSK	(0x3 << 10)

/* TC2 अटल dual-cluster configuration */
#घोषणा MAX_CLUSTERS		2

/*
 * Even though the SPC takes max 3-5 ms to complete any OPP/COMMS
 * operation, the operation could start just beक्रमe jअगरfie is about
 * to be incremented. So setting समयout value of 20ms = 2jअगरfies@100Hz
 */
#घोषणा TIMEOUT_US	20000

#घोषणा MAX_OPPS	8
#घोषणा CA15_DVFS	0
#घोषणा CA7_DVFS	1
#घोषणा SPC_SYS_CFG	2
#घोषणा STAT_COMPLETE(type)	((1 << 0) << (type << 2))
#घोषणा STAT_ERR(type)		((1 << 1) << (type << 2))
#घोषणा RESPONSE_MASK(type)	(STAT_COMPLETE(type) | STAT_ERR(type))

काष्ठा ve_spc_opp अणु
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ u_volt;
पूर्ण;

काष्ठा ve_spc_drvdata अणु
	व्योम __iomem *baseaddr;
	/*
	 * A15s cluster identअगरier
	 * It corresponds to A15 processors MPIDR[15:8] bitfield
	 */
	u32 a15_clusid;
	uपूर्णांक32_t cur_rsp_mask;
	uपूर्णांक32_t cur_rsp_stat;
	काष्ठा semaphore sem;
	काष्ठा completion करोne;
	काष्ठा ve_spc_opp *opps[MAX_CLUSTERS];
	पूर्णांक num_opps[MAX_CLUSTERS];
पूर्ण;

अटल काष्ठा ve_spc_drvdata *info;

अटल अंतरभूत bool cluster_is_a15(u32 cluster)
अणु
	वापस cluster == info->a15_clusid;
पूर्ण

/**
 * ve_spc_global_wakeup_irq()
 *
 * Function to set/clear global wakeup IRQs. Not रक्षित by locking since
 * it might be used in code paths where normal cacheable locks are not
 * working. Locking must be provided by the caller to ensure atomicity.
 *
 * @set: अगर true, global wake-up IRQs are set, अगर false they are cleared
 */
व्योम ve_spc_global_wakeup_irq(bool set)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(info->baseaddr + WAKE_INT_MASK);

	अगर (set)
		reg |= GBL_WAKEUP_INT_MSK;
	अन्यथा
		reg &= ~GBL_WAKEUP_INT_MSK;

	ग_लिखोl_relaxed(reg, info->baseaddr + WAKE_INT_MASK);
पूर्ण

/**
 * ve_spc_cpu_wakeup_irq()
 *
 * Function to set/clear per-CPU wake-up IRQs. Not रक्षित by locking since
 * it might be used in code paths where normal cacheable locks are not
 * working. Locking must be provided by the caller to ensure atomicity.
 *
 * @cluster: mpidr[15:8] bitfield describing cluster affinity level
 * @cpu: mpidr[7:0] bitfield describing cpu affinity level
 * @set: अगर true, wake-up IRQs are set, अगर false they are cleared
 */
व्योम ve_spc_cpu_wakeup_irq(u32 cluster, u32 cpu, bool set)
अणु
	u32 mask, reg;

	अगर (cluster >= MAX_CLUSTERS)
		वापस;

	mask = BIT(cpu);

	अगर (!cluster_is_a15(cluster))
		mask <<= 4;

	reg = पढ़ोl_relaxed(info->baseaddr + WAKE_INT_MASK);

	अगर (set)
		reg |= mask;
	अन्यथा
		reg &= ~mask;

	ग_लिखोl_relaxed(reg, info->baseaddr + WAKE_INT_MASK);
पूर्ण

/**
 * ve_spc_set_resume_addr() - set the jump address used क्रम warm boot
 *
 * @cluster: mpidr[15:8] bitfield describing cluster affinity level
 * @cpu: mpidr[7:0] bitfield describing cpu affinity level
 * @addr: physical resume address
 */
व्योम ve_spc_set_resume_addr(u32 cluster, u32 cpu, u32 addr)
अणु
	व्योम __iomem *baseaddr;

	अगर (cluster >= MAX_CLUSTERS)
		वापस;

	अगर (cluster_is_a15(cluster))
		baseaddr = info->baseaddr + A15_BX_ADDR0 + (cpu << 2);
	अन्यथा
		baseaddr = info->baseaddr + A7_BX_ADDR0 + (cpu << 2);

	ग_लिखोl_relaxed(addr, baseaddr);
पूर्ण

/**
 * ve_spc_घातerकरोwn()
 *
 * Function to enable/disable cluster घातerकरोwn. Not रक्षित by locking
 * since it might be used in code paths where normal cacheable locks are not
 * working. Locking must be provided by the caller to ensure atomicity.
 *
 * @cluster: mpidr[15:8] bitfield describing cluster affinity level
 * @enable: अगर true enables घातerकरोwn, अगर false disables it
 */
व्योम ve_spc_घातerकरोwn(u32 cluster, bool enable)
अणु
	u32 pwdrn_reg;

	अगर (cluster >= MAX_CLUSTERS)
		वापस;

	pwdrn_reg = cluster_is_a15(cluster) ? A15_PWRDN_EN : A7_PWRDN_EN;
	ग_लिखोl_relaxed(enable, info->baseaddr + pwdrn_reg);
पूर्ण

अटल u32 standbywfi_cpu_mask(u32 cpu, u32 cluster)
अणु
	वापस cluster_is_a15(cluster) ?
		  STANDBYWFI_STAT_A15_CPU_MASK(cpu)
		: STANDBYWFI_STAT_A7_CPU_MASK(cpu);
पूर्ण

/**
 * ve_spc_cpu_in_wfi(u32 cpu, u32 cluster)
 *
 * @cpu: mpidr[7:0] bitfield describing CPU affinity level within cluster
 * @cluster: mpidr[15:8] bitfield describing cluster affinity level
 *
 * @वापस: non-zero अगर and only अगर the specअगरied CPU is in WFI
 *
 * Take care when पूर्णांकerpreting the result of this function: a CPU might
 * be in WFI temporarily due to idle, and is not necessarily safely
 * parked.
 */
पूर्णांक ve_spc_cpu_in_wfi(u32 cpu, u32 cluster)
अणु
	पूर्णांक ret;
	u32 mask = standbywfi_cpu_mask(cpu, cluster);

	अगर (cluster >= MAX_CLUSTERS)
		वापस 1;

	ret = पढ़ोl_relaxed(info->baseaddr + STANDBYWFI_STAT);

	pr_debug("%s: PCFGREG[0x%X] = 0x%08X, mask = 0x%X\n",
		 __func__, STANDBYWFI_STAT, ret, mask);

	वापस ret & mask;
पूर्ण

अटल पूर्णांक ve_spc_get_perक्रमmance(पूर्णांक cluster, u32 *freq)
अणु
	काष्ठा ve_spc_opp *opps = info->opps[cluster];
	u32 perf_cfg_reg = 0;
	u32 perf;

	perf_cfg_reg = cluster_is_a15(cluster) ? PERF_LVL_A15 : PERF_LVL_A7;

	perf = पढ़ोl_relaxed(info->baseaddr + perf_cfg_reg);
	अगर (perf >= info->num_opps[cluster])
		वापस -EINVAL;

	opps += perf;
	*freq = opps->freq;

	वापस 0;
पूर्ण

/* find बंदst match to given frequency in OPP table */
अटल पूर्णांक ve_spc_round_perक्रमmance(पूर्णांक cluster, u32 freq)
अणु
	पूर्णांक idx, max_opp = info->num_opps[cluster];
	काष्ठा ve_spc_opp *opps = info->opps[cluster];
	u32 fmin = 0, fmax = ~0, fपंचांगp;

	freq /= 1000; /* OPP entries in kHz */
	क्रम (idx = 0; idx < max_opp; idx++, opps++) अणु
		fपंचांगp = opps->freq;
		अगर (fपंचांगp >= freq) अणु
			अगर (fपंचांगp <= fmax)
				fmax = fपंचांगp;
		पूर्ण अन्यथा अणु
			अगर (fपंचांगp >= fmin)
				fmin = fपंचांगp;
		पूर्ण
	पूर्ण
	अगर (fmax != ~0)
		वापस fmax * 1000;
	अन्यथा
		वापस fmin * 1000;
पूर्ण

अटल पूर्णांक ve_spc_find_perक्रमmance_index(पूर्णांक cluster, u32 freq)
अणु
	पूर्णांक idx, max_opp = info->num_opps[cluster];
	काष्ठा ve_spc_opp *opps = info->opps[cluster];

	क्रम (idx = 0; idx < max_opp; idx++, opps++)
		अगर (opps->freq == freq)
			अवरोध;
	वापस (idx == max_opp) ? -EINVAL : idx;
पूर्ण

अटल पूर्णांक ve_spc_रुकोक्रमcompletion(पूर्णांक req_type)
अणु
	पूर्णांक ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&info->करोne, usecs_to_jअगरfies(TIMEOUT_US));
	अगर (ret == 0)
		ret = -ETIMEDOUT;
	अन्यथा अगर (ret > 0)
		ret = info->cur_rsp_stat & STAT_COMPLETE(req_type) ? 0 : -EIO;
	वापस ret;
पूर्ण

अटल पूर्णांक ve_spc_set_perक्रमmance(पूर्णांक cluster, u32 freq)
अणु
	u32 perf_cfg_reg;
	पूर्णांक ret, perf, req_type;

	अगर (cluster_is_a15(cluster)) अणु
		req_type = CA15_DVFS;
		perf_cfg_reg = PERF_LVL_A15;
	पूर्ण अन्यथा अणु
		req_type = CA7_DVFS;
		perf_cfg_reg = PERF_LVL_A7;
	पूर्ण

	perf = ve_spc_find_perक्रमmance_index(cluster, freq);

	अगर (perf < 0)
		वापस perf;

	अगर (करोwn_समयout(&info->sem, usecs_to_jअगरfies(TIMEOUT_US)))
		वापस -ETIME;

	init_completion(&info->करोne);
	info->cur_rsp_mask = RESPONSE_MASK(req_type);

	ग_लिखोl(perf, info->baseaddr + perf_cfg_reg);
	ret = ve_spc_रुकोक्रमcompletion(req_type);

	info->cur_rsp_mask = 0;
	up(&info->sem);

	वापस ret;
पूर्ण

अटल पूर्णांक ve_spc_पढ़ो_sys_cfg(पूर्णांक func, पूर्णांक offset, uपूर्णांक32_t *data)
अणु
	पूर्णांक ret;

	अगर (करोwn_समयout(&info->sem, usecs_to_jअगरfies(TIMEOUT_US)))
		वापस -ETIME;

	init_completion(&info->करोne);
	info->cur_rsp_mask = RESPONSE_MASK(SPC_SYS_CFG);

	/* Set the control value */
	ग_लिखोl(SYSCFG_START | func | offset >> 2, info->baseaddr + COMMS);
	ret = ve_spc_रुकोक्रमcompletion(SPC_SYS_CFG);

	अगर (ret == 0)
		*data = पढ़ोl(info->baseaddr + SYSCFG_RDATA);

	info->cur_rsp_mask = 0;
	up(&info->sem);

	वापस ret;
पूर्ण

अटल irqवापस_t ve_spc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ve_spc_drvdata *drv_data = data;
	uपूर्णांक32_t status = पढ़ोl_relaxed(drv_data->baseaddr + PWC_STATUS);

	अगर (info->cur_rsp_mask & status) अणु
		info->cur_rsp_stat = status;
		complete(&drv_data->करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 *  +--------------------------+
 *  | 31      20 | 19        0 |
 *  +--------------------------+
 *  |   m_volt   |  freq(kHz)  |
 *  +--------------------------+
 */
#घोषणा MULT_FACTOR	20
#घोषणा VOLT_SHIFT	20
#घोषणा FREQ_MASK	(0xFFFFF)
अटल पूर्णांक ve_spc_populate_opps(uपूर्णांक32_t cluster)
अणु
	uपूर्णांक32_t data = 0, off, ret, idx;
	काष्ठा ve_spc_opp *opps;

	opps = kसुस्मृति(MAX_OPPS, माप(*opps), GFP_KERNEL);
	अगर (!opps)
		वापस -ENOMEM;

	info->opps[cluster] = opps;

	off = cluster_is_a15(cluster) ? A15_PERFVAL_BASE : A7_PERFVAL_BASE;
	क्रम (idx = 0; idx < MAX_OPPS; idx++, off += 4, opps++) अणु
		ret = ve_spc_पढ़ो_sys_cfg(SYSCFG_SCC, off, &data);
		अगर (!ret) अणु
			opps->freq = (data & FREQ_MASK) * MULT_FACTOR;
			opps->u_volt = (data >> VOLT_SHIFT) * 1000;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	info->num_opps[cluster] = idx;

	वापस ret;
पूर्ण

अटल पूर्णांक ve_init_opp_table(काष्ठा device *cpu_dev)
अणु
	पूर्णांक cluster;
	पूर्णांक idx, ret = 0, max_opp;
	काष्ठा ve_spc_opp *opps;

	cluster = topology_physical_package_id(cpu_dev->id);
	cluster = cluster < 0 ? 0 : cluster;

	max_opp = info->num_opps[cluster];
	opps = info->opps[cluster];

	क्रम (idx = 0; idx < max_opp; idx++, opps++) अणु
		ret = dev_pm_opp_add(cpu_dev, opps->freq * 1000, opps->u_volt);
		अगर (ret) अणु
			dev_warn(cpu_dev, "failed to add opp %lu %lu\n",
				 opps->freq, opps->u_volt);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __init ve_spc_init(व्योम __iomem *baseaddr, u32 a15_clusid, पूर्णांक irq)
अणु
	पूर्णांक ret;
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->baseaddr = baseaddr;
	info->a15_clusid = a15_clusid;

	अगर (irq <= 0) अणु
		pr_err(SPCLOG "Invalid IRQ %d\n", irq);
		kमुक्त(info);
		वापस -EINVAL;
	पूर्ण

	init_completion(&info->करोne);

	पढ़ोl_relaxed(info->baseaddr + PWC_STATUS);

	ret = request_irq(irq, ve_spc_irq_handler, IRQF_TRIGGER_HIGH
				| IRQF_ONESHOT, "vexpress-spc", info);
	अगर (ret) अणु
		pr_err(SPCLOG "IRQ %d request failed\n", irq);
		kमुक्त(info);
		वापस -ENODEV;
	पूर्ण

	sema_init(&info->sem, 1);
	/*
	 * Multi-cluster प्रणालीs may need this data when non-coherent, during
	 * cluster घातer-up/घातer-करोwn. Make sure driver info reaches मुख्य
	 * memory.
	 */
	sync_cache_w(info);
	sync_cache_w(&info);

	वापस 0;
पूर्ण

काष्ठा clk_spc अणु
	काष्ठा clk_hw hw;
	पूर्णांक cluster;
पूर्ण;

#घोषणा to_clk_spc(spc) container_of(spc, काष्ठा clk_spc, hw)
अटल अचिन्हित दीर्घ spc_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_spc *spc = to_clk_spc(hw);
	u32 freq;

	अगर (ve_spc_get_perक्रमmance(spc->cluster, &freq))
		वापस -EIO;

	वापस freq * 1000;
पूर्ण

अटल दीर्घ spc_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_spc *spc = to_clk_spc(hw);

	वापस ve_spc_round_perक्रमmance(spc->cluster, drate);
पूर्ण

अटल पूर्णांक spc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_spc *spc = to_clk_spc(hw);

	वापस ve_spc_set_perक्रमmance(spc->cluster, rate / 1000);
पूर्ण

अटल काष्ठा clk_ops clk_spc_ops = अणु
	.recalc_rate = spc_recalc_rate,
	.round_rate = spc_round_rate,
	.set_rate = spc_set_rate,
पूर्ण;

अटल काष्ठा clk *ve_spc_clk_रेजिस्टर(काष्ठा device *cpu_dev)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_spc *spc;

	spc = kzalloc(माप(*spc), GFP_KERNEL);
	अगर (!spc)
		वापस ERR_PTR(-ENOMEM);

	spc->hw.init = &init;
	spc->cluster = topology_physical_package_id(cpu_dev->id);

	spc->cluster = spc->cluster < 0 ? 0 : spc->cluster;

	init.name = dev_name(cpu_dev);
	init.ops = &clk_spc_ops;
	init.flags = CLK_GET_RATE_NOCACHE;
	init.num_parents = 0;

	वापस devm_clk_रेजिस्टर(cpu_dev, &spc->hw);
पूर्ण

अटल पूर्णांक __init ve_spc_clk_init(व्योम)
अणु
	पूर्णांक cpu, cluster;
	काष्ठा clk *clk;
	bool init_opp_table[MAX_CLUSTERS] = अणु false पूर्ण;

	अगर (!info)
		वापस 0; /* Continue only अगर SPC is initialised */

	अगर (ve_spc_populate_opps(0) || ve_spc_populate_opps(1)) अणु
		pr_err("failed to build OPP table\n");
		वापस -ENODEV;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *cpu_dev = get_cpu_device(cpu);
		अगर (!cpu_dev) अणु
			pr_warn("failed to get cpu%d device\n", cpu);
			जारी;
		पूर्ण
		clk = ve_spc_clk_रेजिस्टर(cpu_dev);
		अगर (IS_ERR(clk)) अणु
			pr_warn("failed to register cpu%d clock\n", cpu);
			जारी;
		पूर्ण
		अगर (clk_रेजिस्टर_clkdev(clk, शून्य, dev_name(cpu_dev))) अणु
			pr_warn("failed to register cpu%d clock lookup\n", cpu);
			जारी;
		पूर्ण

		cluster = topology_physical_package_id(cpu_dev->id);
		अगर (init_opp_table[cluster])
			जारी;

		अगर (ve_init_opp_table(cpu_dev))
			pr_warn("failed to initialise cpu%d opp table\n", cpu);
		अन्यथा अगर (dev_pm_opp_set_sharing_cpus(cpu_dev,
			 topology_core_cpumask(cpu_dev->id)))
			pr_warn("failed to mark OPPs shared for cpu%d\n", cpu);
		अन्यथा
			init_opp_table[cluster] = true;
	पूर्ण

	platक्रमm_device_रेजिस्टर_simple("vexpress-spc-cpufreq", -1, शून्य, 0);
	वापस 0;
पूर्ण
device_initcall(ve_spc_clk_init);
