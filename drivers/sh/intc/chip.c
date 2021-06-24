<शैली गुरु>
/*
 * IRQ chip definitions क्रम INTC IRQs.
 *
 * Copyright (C) 2007, 2008 Magnus Damm
 * Copyright (C) 2009 - 2012 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/पन.स>
#समावेश "internals.h"

व्योम _पूर्णांकc_enable(काष्ठा irq_data *data, अचिन्हित दीर्घ handle)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक cpu;

	क्रम (cpu = 0; cpu < SMP_NR(d, _INTC_ADDR_E(handle)); cpu++) अणु
#अगर_घोषित CONFIG_SMP
		अगर (!cpumask_test_cpu(cpu, irq_data_get_affinity_mask(data)))
			जारी;
#पूर्ण_अगर
		addr = INTC_REG(d, _INTC_ADDR_E(handle), cpu);
		पूर्णांकc_enable_fns[_INTC_MODE(handle)](addr, handle, पूर्णांकc_reg_fns\
						    [_INTC_FN(handle)], irq);
	पूर्ण

	पूर्णांकc_balancing_enable(irq);
पूर्ण

अटल व्योम पूर्णांकc_enable(काष्ठा irq_data *data)
अणु
	_पूर्णांकc_enable(data, (अचिन्हित दीर्घ)irq_data_get_irq_chip_data(data));
पूर्ण

अटल व्योम पूर्णांकc_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित दीर्घ handle = (अचिन्हित दीर्घ)irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक cpu;

	पूर्णांकc_balancing_disable(irq);

	क्रम (cpu = 0; cpu < SMP_NR(d, _INTC_ADDR_D(handle)); cpu++) अणु
#अगर_घोषित CONFIG_SMP
		अगर (!cpumask_test_cpu(cpu, irq_data_get_affinity_mask(data)))
			जारी;
#पूर्ण_अगर
		addr = INTC_REG(d, _INTC_ADDR_D(handle), cpu);
		पूर्णांकc_disable_fns[_INTC_MODE(handle)](addr, handle,पूर्णांकc_reg_fns\
						     [_INTC_FN(handle)], irq);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * This is held with the irq desc lock held, so we करोn't require any
 * additional locking here at the पूर्णांकc desc level. The affinity mask is
 * later tested in the enable/disable paths.
 */
अटल पूर्णांक पूर्णांकc_set_affinity(काष्ठा irq_data *data,
			     स्थिर काष्ठा cpumask *cpumask,
			     bool क्रमce)
अणु
	अगर (!cpumask_पूर्णांकersects(cpumask, cpu_online_mask))
		वापस -1;

	cpumask_copy(irq_data_get_affinity_mask(data), cpumask);

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण
#पूर्ण_अगर

अटल व्योम पूर्णांकc_mask_ack(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित दीर्घ handle = पूर्णांकc_get_ack_handle(irq);
	व्योम __iomem *addr;

	पूर्णांकc_disable(data);

	/* पढ़ो रेजिस्टर and ग_लिखो zero only to the associated bit */
	अगर (handle) अणु
		अचिन्हित पूर्णांक value;

		addr = (व्योम __iomem *)INTC_REG(d, _INTC_ADDR_D(handle), 0);
		value = पूर्णांकc_set_field_from_handle(0, 1, handle);

		चयन (_INTC_FN(handle)) अणु
		हाल REG_FN_MODIFY_BASE + 0:	/* 8bit */
			__raw_पढ़ोb(addr);
			__raw_ग_लिखोb(0xff ^ value, addr);
			अवरोध;
		हाल REG_FN_MODIFY_BASE + 1:	/* 16bit */
			__raw_पढ़ोw(addr);
			__raw_ग_लिखोw(0xffff ^ value, addr);
			अवरोध;
		हाल REG_FN_MODIFY_BASE + 3:	/* 32bit */
			__raw_पढ़ोl(addr);
			__raw_ग_लिखोl(0xffffffff ^ value, addr);
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा पूर्णांकc_handle_पूर्णांक *पूर्णांकc_find_irq(काष्ठा पूर्णांकc_handle_पूर्णांक *hp,
					     अचिन्हित पूर्णांक nr_hp,
					     अचिन्हित पूर्णांक irq)
अणु
	काष्ठा पूर्णांकc_handle_पूर्णांक key;

	key.irq = irq;
	key.handle = 0;

	वापस द्वा_खोज(&key, hp, nr_hp, माप(*hp), पूर्णांकc_handle_पूर्णांक_cmp);
पूर्ण

पूर्णांक पूर्णांकc_set_priority(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक prio)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	काष्ठा पूर्णांकc_handle_पूर्णांक *ihp;

	अगर (!पूर्णांकc_get_prio_level(irq) || prio <= 1)
		वापस -EINVAL;

	ihp = पूर्णांकc_find_irq(d->prio, d->nr_prio, irq);
	अगर (ihp) अणु
		अगर (prio >= (1 << _INTC_WIDTH(ihp->handle)))
			वापस -EINVAL;

		पूर्णांकc_set_prio_level(irq, prio);

		/*
		 * only set secondary masking method directly
		 * primary masking method is using पूर्णांकc_prio_level[irq]
		 * priority level will be set during next enable()
		 */
		अगर (_INTC_FN(ihp->handle) != REG_FN_ERR)
			_पूर्णांकc_enable(data, ihp->handle);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा SENSE_VALID_FLAG 0x80
#घोषणा VALID(x) (x | SENSE_VALID_FLAG)

अटल अचिन्हित अक्षर पूर्णांकc_irq_sense_table[IRQ_TYPE_SENSE_MASK + 1] = अणु
	[IRQ_TYPE_EDGE_FALLING] = VALID(0),
	[IRQ_TYPE_EDGE_RISING] = VALID(1),
	[IRQ_TYPE_LEVEL_LOW] = VALID(2),
	/* SH7706, SH7707 and SH7709 करो not support high level triggered */
#अगर !defined(CONFIG_CPU_SUBTYPE_SH7706) && \
    !defined(CONFIG_CPU_SUBTYPE_SH7707) && \
    !defined(CONFIG_CPU_SUBTYPE_SH7709)
	[IRQ_TYPE_LEVEL_HIGH] = VALID(3),
#पूर्ण_अगर
#अगर defined(CONFIG_ARM) /* all recent SH-Mobile / R-Mobile ARM support this */
	[IRQ_TYPE_EDGE_BOTH] = VALID(4),
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक पूर्णांकc_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);
	अचिन्हित अक्षर value = पूर्णांकc_irq_sense_table[type & IRQ_TYPE_SENSE_MASK];
	काष्ठा पूर्णांकc_handle_पूर्णांक *ihp;
	अचिन्हित दीर्घ addr;

	अगर (!value)
		वापस -EINVAL;

	value &= ~SENSE_VALID_FLAG;

	ihp = पूर्णांकc_find_irq(d->sense, d->nr_sense, irq);
	अगर (ihp) अणु
		/* PINT has 2-bit sense रेजिस्टरs, should fail on EDGE_BOTH */
		अगर (value >= (1 << _INTC_WIDTH(ihp->handle)))
			वापस -EINVAL;

		addr = INTC_REG(d, _INTC_ADDR_E(ihp->handle), 0);
		पूर्णांकc_reg_fns[_INTC_FN(ihp->handle)](addr, ihp->handle, value);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा irq_chip पूर्णांकc_irq_chip	= अणु
	.irq_mask		= पूर्णांकc_disable,
	.irq_unmask		= पूर्णांकc_enable,
	.irq_mask_ack		= पूर्णांकc_mask_ack,
	.irq_enable		= पूर्णांकc_enable,
	.irq_disable		= पूर्णांकc_disable,
	.irq_set_type		= पूर्णांकc_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= पूर्णांकc_set_affinity,
#पूर्ण_अगर
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;
