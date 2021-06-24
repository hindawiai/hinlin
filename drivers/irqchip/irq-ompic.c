<शैली गुरु>
/*
 * Open Multi-Processor Interrupt Controller driver
 *
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * The ompic device handles IPI communication between cores in multi-core
 * OpenRISC प्रणालीs.
 *
 * Registers
 *
 * For each CPU the ompic has 2 रेजिस्टरs. The control रेजिस्टर क्रम sending
 * and acking IPIs and the status रेजिस्टर क्रम receiving IPIs. The रेजिस्टर
 * layouts are as follows:
 *
 *  Control रेजिस्टर
 *  +---------+---------+----------+---------+
 *  | 31      | 30      | 29 .. 16 | 15 .. 0 |
 *  ----------+---------+----------+----------
 *  | IRQ ACK | IRQ GEN | DST CORE | DATA    |
 *  +---------+---------+----------+---------+
 *
 *  Status रेजिस्टर
 *  +----------+-------------+----------+---------+
 *  | 31       | 30          | 29 .. 16 | 15 .. 0 |
 *  -----------+-------------+----------+---------+
 *  | Reserved | IRQ Pending | SRC CORE | DATA    |
 *  +----------+-------------+----------+---------+
 *
 * Architecture
 *
 * - The ompic generates a level पूर्णांकerrupt to the CPU PIC when a message is
 *   पढ़ोy.  Messages are delivered via the memory bus.
 * - The ompic करोes not have any पूर्णांकerrupt input lines.
 * - The ompic is wired to the same irq line on each core.
 * - Devices are wired to the same irq line on each core.
 *
 *   +---------+                         +---------+
 *   | CPU     |                         | CPU     |
 *   |  Core 0 |<==\ (memory access) /==>|  Core 1 |
 *   |  [ PIC ]|   |                 |   |  [ PIC ]|
 *   +----^-^--+   |                 |   +----^-^--+
 *        | |      v                 v        | |
 *   <====|=|=================================|=|==> (memory bus)
 *        | |      ^                  ^       | |
 *  (ipi  | +------|---------+--------|-------|-+ (device irq)
 *   irq  |        |         |        |       |
 *  core0)| +------|---------|--------|-------+ (ipi irq core1)
 *        | |      |         |        |
 *   +----o-o-+    |    +--------+    |
 *   | ompic  |<===/    | Device |<===/
 *   |  IPI   |         +--------+
 *   +--------+*
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश <linux/irqchip.h>

#घोषणा OMPIC_CPUBYTES		8
#घोषणा OMPIC_CTRL(cpu)		(0x0 + (cpu * OMPIC_CPUBYTES))
#घोषणा OMPIC_STAT(cpu)		(0x4 + (cpu * OMPIC_CPUBYTES))

#घोषणा OMPIC_CTRL_IRQ_ACK	(1 << 31)
#घोषणा OMPIC_CTRL_IRQ_GEN	(1 << 30)
#घोषणा OMPIC_CTRL_DST(cpu)	(((cpu) & 0x3fff) << 16)

#घोषणा OMPIC_STAT_IRQ_PENDING	(1 << 30)

#घोषणा OMPIC_DATA(x)		((x) & 0xffff)

DEFINE_PER_CPU(अचिन्हित दीर्घ, ops);

अटल व्योम __iomem *ompic_base;

अटल अंतरभूत u32 ompic_पढ़ोreg(व्योम __iomem *base, loff_t offset)
अणु
	वापस ioपढ़ो32be(base + offset);
पूर्ण

अटल व्योम ompic_ग_लिखोreg(व्योम __iomem *base, loff_t offset, u32 data)
अणु
	ioग_लिखो32be(data, base + offset);
पूर्ण

अटल व्योम ompic_उठाओ_softirq(स्थिर काष्ठा cpumask *mask,
				अचिन्हित पूर्णांक ipi_msg)
अणु
	अचिन्हित पूर्णांक dst_cpu;
	अचिन्हित पूर्णांक src_cpu = smp_processor_id();

	क्रम_each_cpu(dst_cpu, mask) अणु
		set_bit(ipi_msg, &per_cpu(ops, dst_cpu));

		/*
		 * On OpenRISC the atomic set_bit() call implies a memory
		 * barrier.  Otherwise we would need: smp_wmb(); paired
		 * with the पढ़ो in ompic_ipi_handler.
		 */

		ompic_ग_लिखोreg(ompic_base, OMPIC_CTRL(src_cpu),
			       OMPIC_CTRL_IRQ_GEN |
			       OMPIC_CTRL_DST(dst_cpu) |
			       OMPIC_DATA(1));
	पूर्ण
पूर्ण

अटल irqवापस_t ompic_ipi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ *pending_ops = &per_cpu(ops, cpu);
	अचिन्हित दीर्घ ops;

	ompic_ग_लिखोreg(ompic_base, OMPIC_CTRL(cpu), OMPIC_CTRL_IRQ_ACK);
	जबतक ((ops = xchg(pending_ops, 0)) != 0) अणु

		/*
		 * On OpenRISC the atomic xchg() call implies a memory
		 * barrier.  Otherwise we may need an smp_rmb(); paired
		 * with the ग_लिखो in ompic_उठाओ_softirq.
		 */

		करो अणु
			अचिन्हित दीर्घ ipi_msg;

			ipi_msg = __ffs(ops);
			ops &= ~(1UL << ipi_msg);

			handle_IPI(ipi_msg);
		पूर्ण जबतक (ops);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ompic_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	काष्ठा resource res;
	पूर्णांक irq;
	पूर्णांक ret;

	/* Validate the DT */
	अगर (ompic_base) अणु
		pr_err("ompic: duplicate ompic's are not supported");
		वापस -EEXIST;
	पूर्ण

	अगर (of_address_to_resource(node, 0, &res)) अणु
		pr_err("ompic: reg property requires an address and size");
		वापस -EINVAL;
	पूर्ण

	अगर (resource_size(&res) < (num_possible_cpus() * OMPIC_CPUBYTES)) अणु
		pr_err("ompic: reg size, currently %d must be at least %d",
			resource_size(&res),
			(num_possible_cpus() * OMPIC_CPUBYTES));
		वापस -EINVAL;
	पूर्ण

	/* Setup the device */
	ompic_base = ioremap(res.start, resource_size(&res));
	अगर (!ompic_base) अणु
		pr_err("ompic: unable to map registers");
		वापस -ENOMEM;
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		pr_err("ompic: unable to parse device irq");
		ret = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	ret = request_irq(irq, ompic_ipi_handler, IRQF_PERCPU,
				"ompic_ipi", शून्य);
	अगर (ret)
		जाओ out_irq_disp;

	set_smp_cross_call(ompic_उठाओ_softirq);

	वापस 0;

out_irq_disp:
	irq_dispose_mapping(irq);
out_unmap:
	iounmap(ompic_base);
	ompic_base = शून्य;
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(ompic, "openrisc,ompic", ompic_of_init);
