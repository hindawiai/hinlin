<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cell Broadband Engine Perक्रमmance Monitor
 *
 * (C) Copyright IBM Corporation 2001,2006
 *
 * Author:
 *    David Erb (djerb@us.ibm.com)
 *    Kevin Corry (kevcorry@us.ibm.com)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "interrupt.h"

/*
 * When writing to ग_लिखो-only mmio addresses, save a shaकरोw copy. All of the
 * रेजिस्टरs are 32-bit, but stored in the upper-half of a 64-bit field in
 * pmd_regs.
 */

#घोषणा WRITE_WO_MMIO(reg, x)					\
	करो अणु							\
		u32 _x = (x);					\
		काष्ठा cbe_pmd_regs __iomem *pmd_regs;		\
		काष्ठा cbe_pmd_shaकरोw_regs *shaकरोw_regs;	\
		pmd_regs = cbe_get_cpu_pmd_regs(cpu);		\
		shaकरोw_regs = cbe_get_cpu_pmd_shaकरोw_regs(cpu);	\
		out_be64(&(pmd_regs->reg), (((u64)_x) << 32));	\
		shaकरोw_regs->reg = _x;				\
	पूर्ण जबतक (0)

#घोषणा READ_SHADOW_REG(val, reg)				\
	करो अणु							\
		काष्ठा cbe_pmd_shaकरोw_regs *shaकरोw_regs;	\
		shaकरोw_regs = cbe_get_cpu_pmd_shaकरोw_regs(cpu);	\
		(val) = shaकरोw_regs->reg;			\
	पूर्ण जबतक (0)

#घोषणा READ_MMIO_UPPER32(val, reg)				\
	करो अणु							\
		काष्ठा cbe_pmd_regs __iomem *pmd_regs;		\
		pmd_regs = cbe_get_cpu_pmd_regs(cpu);		\
		(val) = (u32)(in_be64(&pmd_regs->reg) >> 32);	\
	पूर्ण जबतक (0)

/*
 * Physical counter रेजिस्टरs.
 * Each physical counter can act as one 32-bit counter or two 16-bit counters.
 */

u32 cbe_पढ़ो_phys_ctr(u32 cpu, u32 phys_ctr)
अणु
	u32 val_in_latch, val = 0;

	अगर (phys_ctr < NR_PHYS_CTRS) अणु
		READ_SHADOW_REG(val_in_latch, counter_value_in_latch);

		/* Read the latch or the actual counter, whichever is newer. */
		अगर (val_in_latch & (1 << phys_ctr)) अणु
			READ_SHADOW_REG(val, pm_ctr[phys_ctr]);
		पूर्ण अन्यथा अणु
			READ_MMIO_UPPER32(val, pm_ctr[phys_ctr]);
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_पढ़ो_phys_ctr);

व्योम cbe_ग_लिखो_phys_ctr(u32 cpu, u32 phys_ctr, u32 val)
अणु
	काष्ठा cbe_pmd_shaकरोw_regs *shaकरोw_regs;
	u32 pm_ctrl;

	अगर (phys_ctr < NR_PHYS_CTRS) अणु
		/* Writing to a counter only ग_लिखोs to a hardware latch.
		 * The new value is not propagated to the actual counter
		 * until the perक्रमmance monitor is enabled.
		 */
		WRITE_WO_MMIO(pm_ctr[phys_ctr], val);

		pm_ctrl = cbe_पढ़ो_pm(cpu, pm_control);
		अगर (pm_ctrl & CBE_PM_ENABLE_PERF_MON) अणु
			/* The counters are alपढ़ोy active, so we need to
			 * reग_लिखो the pm_control रेजिस्टर to "re-enable"
			 * the PMU.
			 */
			cbe_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
		पूर्ण अन्यथा अणु
			shaकरोw_regs = cbe_get_cpu_pmd_shaकरोw_regs(cpu);
			shaकरोw_regs->counter_value_in_latch |= (1 << phys_ctr);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cbe_ग_लिखो_phys_ctr);

/*
 * "Logical" counter रेजिस्टरs.
 * These will पढ़ो/ग_लिखो 16-bits or 32-bits depending on the
 * current size of the counter. Counters 4 - 7 are always 16-bit.
 */

u32 cbe_पढ़ो_ctr(u32 cpu, u32 ctr)
अणु
	u32 val;
	u32 phys_ctr = ctr & (NR_PHYS_CTRS - 1);

	val = cbe_पढ़ो_phys_ctr(cpu, phys_ctr);

	अगर (cbe_get_ctr_size(cpu, phys_ctr) == 16)
		val = (ctr < NR_PHYS_CTRS) ? (val >> 16) : (val & 0xffff);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_पढ़ो_ctr);

व्योम cbe_ग_लिखो_ctr(u32 cpu, u32 ctr, u32 val)
अणु
	u32 phys_ctr;
	u32 phys_val;

	phys_ctr = ctr & (NR_PHYS_CTRS - 1);

	अगर (cbe_get_ctr_size(cpu, phys_ctr) == 16) अणु
		phys_val = cbe_पढ़ो_phys_ctr(cpu, phys_ctr);

		अगर (ctr < NR_PHYS_CTRS)
			val = (val << 16) | (phys_val & 0xffff);
		अन्यथा
			val = (val & 0xffff) | (phys_val & 0xffff0000);
	पूर्ण

	cbe_ग_लिखो_phys_ctr(cpu, phys_ctr, val);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_ग_लिखो_ctr);

/*
 * Counter-control रेजिस्टरs.
 * Each "logical" counter has a corresponding control रेजिस्टर.
 */

u32 cbe_पढ़ो_pm07_control(u32 cpu, u32 ctr)
अणु
	u32 pm07_control = 0;

	अगर (ctr < NR_CTRS)
		READ_SHADOW_REG(pm07_control, pm07_control[ctr]);

	वापस pm07_control;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_पढ़ो_pm07_control);

व्योम cbe_ग_लिखो_pm07_control(u32 cpu, u32 ctr, u32 val)
अणु
	अगर (ctr < NR_CTRS)
		WRITE_WO_MMIO(pm07_control[ctr], val);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_ग_लिखो_pm07_control);

/*
 * Other PMU control रेजिस्टरs. Most of these are ग_लिखो-only.
 */

u32 cbe_पढ़ो_pm(u32 cpu, क्रमागत pm_reg_name reg)
अणु
	u32 val = 0;

	चयन (reg) अणु
	हाल group_control:
		READ_SHADOW_REG(val, group_control);
		अवरोध;

	हाल debug_bus_control:
		READ_SHADOW_REG(val, debug_bus_control);
		अवरोध;

	हाल trace_address:
		READ_MMIO_UPPER32(val, trace_address);
		अवरोध;

	हाल ext_tr_समयr:
		READ_SHADOW_REG(val, ext_tr_समयr);
		अवरोध;

	हाल pm_status:
		READ_MMIO_UPPER32(val, pm_status);
		अवरोध;

	हाल pm_control:
		READ_SHADOW_REG(val, pm_control);
		अवरोध;

	हाल pm_पूर्णांकerval:
		READ_MMIO_UPPER32(val, pm_पूर्णांकerval);
		अवरोध;

	हाल pm_start_stop:
		READ_SHADOW_REG(val, pm_start_stop);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_पढ़ो_pm);

व्योम cbe_ग_लिखो_pm(u32 cpu, क्रमागत pm_reg_name reg, u32 val)
अणु
	चयन (reg) अणु
	हाल group_control:
		WRITE_WO_MMIO(group_control, val);
		अवरोध;

	हाल debug_bus_control:
		WRITE_WO_MMIO(debug_bus_control, val);
		अवरोध;

	हाल trace_address:
		WRITE_WO_MMIO(trace_address, val);
		अवरोध;

	हाल ext_tr_समयr:
		WRITE_WO_MMIO(ext_tr_समयr, val);
		अवरोध;

	हाल pm_status:
		WRITE_WO_MMIO(pm_status, val);
		अवरोध;

	हाल pm_control:
		WRITE_WO_MMIO(pm_control, val);
		अवरोध;

	हाल pm_पूर्णांकerval:
		WRITE_WO_MMIO(pm_पूर्णांकerval, val);
		अवरोध;

	हाल pm_start_stop:
		WRITE_WO_MMIO(pm_start_stop, val);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cbe_ग_लिखो_pm);

/*
 * Get/set the size of a physical counter to either 16 or 32 bits.
 */

u32 cbe_get_ctr_size(u32 cpu, u32 phys_ctr)
अणु
	u32 pm_ctrl, size = 0;

	अगर (phys_ctr < NR_PHYS_CTRS) अणु
		pm_ctrl = cbe_पढ़ो_pm(cpu, pm_control);
		size = (pm_ctrl & CBE_PM_16BIT_CTR(phys_ctr)) ? 16 : 32;
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_ctr_size);

व्योम cbe_set_ctr_size(u32 cpu, u32 phys_ctr, u32 ctr_size)
अणु
	u32 pm_ctrl;

	अगर (phys_ctr < NR_PHYS_CTRS) अणु
		pm_ctrl = cbe_पढ़ो_pm(cpu, pm_control);
		चयन (ctr_size) अणु
		हाल 16:
			pm_ctrl |= CBE_PM_16BIT_CTR(phys_ctr);
			अवरोध;

		हाल 32:
			pm_ctrl &= ~CBE_PM_16BIT_CTR(phys_ctr);
			अवरोध;
		पूर्ण
		cbe_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cbe_set_ctr_size);

/*
 * Enable/disable the entire perक्रमmance monitoring unit.
 * When we enable the PMU, all pending ग_लिखोs to counters get committed.
 */

व्योम cbe_enable_pm(u32 cpu)
अणु
	काष्ठा cbe_pmd_shaकरोw_regs *shaकरोw_regs;
	u32 pm_ctrl;

	shaकरोw_regs = cbe_get_cpu_pmd_shaकरोw_regs(cpu);
	shaकरोw_regs->counter_value_in_latch = 0;

	pm_ctrl = cbe_पढ़ो_pm(cpu, pm_control) | CBE_PM_ENABLE_PERF_MON;
	cbe_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_enable_pm);

व्योम cbe_disable_pm(u32 cpu)
अणु
	u32 pm_ctrl;
	pm_ctrl = cbe_पढ़ो_pm(cpu, pm_control) & ~CBE_PM_ENABLE_PERF_MON;
	cbe_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_disable_pm);

/*
 * Reading from the trace_buffer.
 * The trace buffer is two 64-bit रेजिस्टरs. Reading from
 * the second half स्वतःmatically increments the trace_address.
 */

व्योम cbe_पढ़ो_trace_buffer(u32 cpu, u64 *buf)
अणु
	काष्ठा cbe_pmd_regs __iomem *pmd_regs = cbe_get_cpu_pmd_regs(cpu);

	*buf++ = in_be64(&pmd_regs->trace_buffer_0_63);
	*buf++ = in_be64(&pmd_regs->trace_buffer_64_127);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_पढ़ो_trace_buffer);

/*
 * Enabling/disabling पूर्णांकerrupts क्रम the entire perक्रमmance monitoring unit.
 */

u32 cbe_get_and_clear_pm_पूर्णांकerrupts(u32 cpu)
अणु
	/* Reading pm_status clears the पूर्णांकerrupt bits. */
	वापस cbe_पढ़ो_pm(cpu, pm_status);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_get_and_clear_pm_पूर्णांकerrupts);

व्योम cbe_enable_pm_पूर्णांकerrupts(u32 cpu, u32 thपढ़ो, u32 mask)
अणु
	/* Set which node and thपढ़ो will handle the next पूर्णांकerrupt. */
	iic_set_पूर्णांकerrupt_routing(cpu, thपढ़ो, 0);

	/* Enable the पूर्णांकerrupt bits in the pm_status रेजिस्टर. */
	अगर (mask)
		cbe_ग_लिखो_pm(cpu, pm_status, mask);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_enable_pm_पूर्णांकerrupts);

व्योम cbe_disable_pm_पूर्णांकerrupts(u32 cpu)
अणु
	cbe_get_and_clear_pm_पूर्णांकerrupts(cpu);
	cbe_ग_लिखो_pm(cpu, pm_status, 0);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_disable_pm_पूर्णांकerrupts);

अटल irqवापस_t cbe_pm_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	perf_irq(get_irq_regs());
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init cbe_init_pm_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq;
	पूर्णांक rc, node;

	क्रम_each_online_node(node) अणु
		irq = irq_create_mapping(शून्य, IIC_IRQ_IOEX_PMI |
					       (node << IIC_IRQ_NODE_SHIFT));
		अगर (!irq) अणु
			prपूर्णांकk("ERROR: Unable to allocate irq for node %d\n",
			       node);
			वापस -EINVAL;
		पूर्ण

		rc = request_irq(irq, cbe_pm_irq,
				 0, "cbe-pmu-0", शून्य);
		अगर (rc) अणु
			prपूर्णांकk("ERROR: Request for irq on node %d failed\n",
			       node);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
machine_arch_initcall(cell, cbe_init_pm_irq);

व्योम cbe_sync_irq(पूर्णांक node)
अणु
	अचिन्हित पूर्णांक irq;

	irq = irq_find_mapping(शून्य,
			       IIC_IRQ_IOEX_PMI
			       | (node << IIC_IRQ_NODE_SHIFT));

	अगर (!irq) अणु
		prपूर्णांकk(KERN_WARNING "ERROR, unable to get existing irq %d " \
		"for node %d\n", irq, node);
		वापस;
	पूर्ण

	synchronize_irq(irq);
पूर्ण
EXPORT_SYMBOL_GPL(cbe_sync_irq);

