<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2008 Nicolas Schichan <nschichan@मुक्तbox.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_irq.h>


अटल DEFINE_SPINLOCK(ipic_lock);
अटल DEFINE_SPINLOCK(epic_lock);

अटल u32 irq_stat_addr[2];
अटल u32 irq_mask_addr[2];
अटल व्योम (*dispatch_पूर्णांकernal)(पूर्णांक cpu);
अटल पूर्णांक is_ext_irq_cascaded;
अटल अचिन्हित पूर्णांक ext_irq_count;
अटल अचिन्हित पूर्णांक ext_irq_start, ext_irq_end;
अटल अचिन्हित पूर्णांक ext_irq_cfg_reg1, ext_irq_cfg_reg2;
अटल व्योम (*पूर्णांकernal_irq_mask)(काष्ठा irq_data *d);
अटल व्योम (*पूर्णांकernal_irq_unmask)(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *m);


अटल अंतरभूत u32 get_ext_irq_perf_reg(पूर्णांक irq)
अणु
	अगर (irq < 4)
		वापस ext_irq_cfg_reg1;
	वापस ext_irq_cfg_reg2;
पूर्ण

अटल अंतरभूत व्योम handle_पूर्णांकernal(पूर्णांक पूर्णांकbit)
अणु
	अगर (is_ext_irq_cascaded &&
	    पूर्णांकbit >= ext_irq_start && पूर्णांकbit <= ext_irq_end)
		करो_IRQ(पूर्णांकbit - ext_irq_start + IRQ_EXTERNAL_BASE);
	अन्यथा
		करो_IRQ(पूर्णांकbit + IRQ_INTERNAL_BASE);
पूर्ण

अटल अंतरभूत पूर्णांक enable_irq_क्रम_cpu(पूर्णांक cpu, काष्ठा irq_data *d,
				     स्थिर काष्ठा cpumask *m)
अणु
	bool enable = cpu_online(cpu);

#अगर_घोषित CONFIG_SMP
	अगर (m)
		enable &= cpumask_test_cpu(cpu, m);
	अन्यथा अगर (irqd_affinity_was_set(d))
		enable &= cpumask_test_cpu(cpu, irq_data_get_affinity_mask(d));
#पूर्ण_अगर
	वापस enable;
पूर्ण

/*
 * dispatch पूर्णांकernal devices IRQ (uart, enet, watchकरोg, ...). करो not
 * prioritize any पूर्णांकerrupt relatively to another. the अटल counter
 * will resume the loop where it ended the last समय we left this
 * function.
 */

#घोषणा BUILD_IPIC_INTERNAL(width)					\
व्योम __dispatch_पूर्णांकernal_##width(पूर्णांक cpu)				\
अणु									\
	u32 pending[width / 32];					\
	अचिन्हित पूर्णांक src, tgt;						\
	bool irqs_pending = false;					\
	अटल अचिन्हित पूर्णांक i[2];					\
	अचिन्हित पूर्णांक *next = &i[cpu];					\
	अचिन्हित दीर्घ flags;						\
									\
	/* पढ़ो रेजिस्टरs in reverse order */				\
	spin_lock_irqsave(&ipic_lock, flags);				\
	क्रम (src = 0, tgt = (width / 32); src < (width / 32); src++) अणु	\
		u32 val;						\
									\
		val = bcm_पढ़ोl(irq_stat_addr[cpu] + src * माप(u32)); \
		val &= bcm_पढ़ोl(irq_mask_addr[cpu] + src * माप(u32)); \
		pending[--tgt] = val;					\
									\
		अगर (val)						\
			irqs_pending = true;				\
	पूर्ण								\
	spin_unlock_irqrestore(&ipic_lock, flags);			\
									\
	अगर (!irqs_pending)						\
		वापस;							\
									\
	जबतक (1) अणु							\
		अचिन्हित पूर्णांक to_call = *next;				\
									\
		*next = (*next + 1) & (width - 1);			\
		अगर (pending[to_call / 32] & (1 << (to_call & 0x1f))) अणु	\
			handle_पूर्णांकernal(to_call);			\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
पूर्ण									\
									\
अटल व्योम __पूर्णांकernal_irq_mask_##width(काष्ठा irq_data *d)		\
अणु									\
	u32 val;							\
	अचिन्हित irq = d->irq - IRQ_INTERNAL_BASE;			\
	अचिन्हित reg = (irq / 32) ^ (width/32 - 1);			\
	अचिन्हित bit = irq & 0x1f;					\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक cpu;							\
									\
	spin_lock_irqsave(&ipic_lock, flags);				\
	क्रम_each_present_cpu(cpu) अणु					\
		अगर (!irq_mask_addr[cpu])				\
			अवरोध;						\
									\
		val = bcm_पढ़ोl(irq_mask_addr[cpu] + reg * माप(u32));\
		val &= ~(1 << bit);					\
		bcm_ग_लिखोl(val, irq_mask_addr[cpu] + reg * माप(u32));\
	पूर्ण								\
	spin_unlock_irqrestore(&ipic_lock, flags);			\
पूर्ण									\
									\
अटल व्योम __पूर्णांकernal_irq_unmask_##width(काष्ठा irq_data *d,		\
					  स्थिर काष्ठा cpumask *m)	\
अणु									\
	u32 val;							\
	अचिन्हित irq = d->irq - IRQ_INTERNAL_BASE;			\
	अचिन्हित reg = (irq / 32) ^ (width/32 - 1);			\
	अचिन्हित bit = irq & 0x1f;					\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक cpu;							\
									\
	spin_lock_irqsave(&ipic_lock, flags);				\
	क्रम_each_present_cpu(cpu) अणु					\
		अगर (!irq_mask_addr[cpu])				\
			अवरोध;						\
									\
		val = bcm_पढ़ोl(irq_mask_addr[cpu] + reg * माप(u32));\
		अगर (enable_irq_क्रम_cpu(cpu, d, m))			\
			val |= (1 << bit);				\
		अन्यथा							\
			val &= ~(1 << bit);				\
		bcm_ग_लिखोl(val, irq_mask_addr[cpu] + reg * माप(u32));\
	पूर्ण								\
	spin_unlock_irqrestore(&ipic_lock, flags);			\
पूर्ण

BUILD_IPIC_INTERNAL(32);
BUILD_IPIC_INTERNAL(64);

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	u32 cause;

	करो अणु
		cause = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;

		अगर (!cause)
			अवरोध;

		अगर (cause & CAUSEF_IP7)
			करो_IRQ(7);
		अगर (cause & CAUSEF_IP0)
			करो_IRQ(0);
		अगर (cause & CAUSEF_IP1)
			करो_IRQ(1);
		अगर (cause & CAUSEF_IP2)
			dispatch_पूर्णांकernal(0);
		अगर (is_ext_irq_cascaded) अणु
			अगर (cause & CAUSEF_IP3)
				dispatch_पूर्णांकernal(1);
		पूर्ण अन्यथा अणु
			अगर (cause & CAUSEF_IP3)
				करो_IRQ(IRQ_EXT_0);
			अगर (cause & CAUSEF_IP4)
				करो_IRQ(IRQ_EXT_1);
			अगर (cause & CAUSEF_IP5)
				करो_IRQ(IRQ_EXT_2);
			अगर (cause & CAUSEF_IP6)
				करो_IRQ(IRQ_EXT_3);
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

/*
 * पूर्णांकernal IRQs operations: only mask/unmask on PERF irq mask
 * रेजिस्टर.
 */
अटल व्योम bcm63xx_पूर्णांकernal_irq_mask(काष्ठा irq_data *d)
अणु
	पूर्णांकernal_irq_mask(d);
पूर्ण

अटल व्योम bcm63xx_पूर्णांकernal_irq_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांकernal_irq_unmask(d, शून्य);
पूर्ण

/*
 * बाह्यal IRQs operations: mask/unmask and clear on PERF बाह्यal
 * irq control रेजिस्टर.
 */
अटल व्योम bcm63xx_बाह्यal_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - IRQ_EXTERNAL_BASE;
	u32 reg, regaddr;
	अचिन्हित दीर्घ flags;

	regaddr = get_ext_irq_perf_reg(irq);
	spin_lock_irqsave(&epic_lock, flags);
	reg = bcm_perf_पढ़ोl(regaddr);

	अगर (BCMCPU_IS_6348())
		reg &= ~EXTIRQ_CFG_MASK_6348(irq % 4);
	अन्यथा
		reg &= ~EXTIRQ_CFG_MASK(irq % 4);

	bcm_perf_ग_लिखोl(reg, regaddr);
	spin_unlock_irqrestore(&epic_lock, flags);

	अगर (is_ext_irq_cascaded)
		पूर्णांकernal_irq_mask(irq_get_irq_data(irq + ext_irq_start));
पूर्ण

अटल व्योम bcm63xx_बाह्यal_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - IRQ_EXTERNAL_BASE;
	u32 reg, regaddr;
	अचिन्हित दीर्घ flags;

	regaddr = get_ext_irq_perf_reg(irq);
	spin_lock_irqsave(&epic_lock, flags);
	reg = bcm_perf_पढ़ोl(regaddr);

	अगर (BCMCPU_IS_6348())
		reg |= EXTIRQ_CFG_MASK_6348(irq % 4);
	अन्यथा
		reg |= EXTIRQ_CFG_MASK(irq % 4);

	bcm_perf_ग_लिखोl(reg, regaddr);
	spin_unlock_irqrestore(&epic_lock, flags);

	अगर (is_ext_irq_cascaded)
		पूर्णांकernal_irq_unmask(irq_get_irq_data(irq + ext_irq_start),
				    शून्य);
पूर्ण

अटल व्योम bcm63xx_बाह्यal_irq_clear(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq - IRQ_EXTERNAL_BASE;
	u32 reg, regaddr;
	अचिन्हित दीर्घ flags;

	regaddr = get_ext_irq_perf_reg(irq);
	spin_lock_irqsave(&epic_lock, flags);
	reg = bcm_perf_पढ़ोl(regaddr);

	अगर (BCMCPU_IS_6348())
		reg |= EXTIRQ_CFG_CLEAR_6348(irq % 4);
	अन्यथा
		reg |= EXTIRQ_CFG_CLEAR(irq % 4);

	bcm_perf_ग_लिखोl(reg, regaddr);
	spin_unlock_irqrestore(&epic_lock, flags);
पूर्ण

अटल पूर्णांक bcm63xx_बाह्यal_irq_set_type(काष्ठा irq_data *d,
					 अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक irq = d->irq - IRQ_EXTERNAL_BASE;
	u32 reg, regaddr;
	पूर्णांक levअन्यथाnse, sense, bothedge;
	अचिन्हित दीर्घ flags;

	flow_type &= IRQ_TYPE_SENSE_MASK;

	अगर (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_LEVEL_LOW;

	levअन्यथाnse = sense = bothedge = 0;
	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		bothedge = 1;
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		sense = 1;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		levअन्यथाnse = 1;
		sense = 1;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		levअन्यथाnse = 1;
		अवरोध;

	शेष:
		pr_err("bogus flow type combination given !\n");
		वापस -EINVAL;
	पूर्ण

	regaddr = get_ext_irq_perf_reg(irq);
	spin_lock_irqsave(&epic_lock, flags);
	reg = bcm_perf_पढ़ोl(regaddr);
	irq %= 4;

	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM6348_CPU_ID:
		अगर (levअन्यथाnse)
			reg |= EXTIRQ_CFG_LEVELSENSE_6348(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_LEVELSENSE_6348(irq);
		अगर (sense)
			reg |= EXTIRQ_CFG_SENSE_6348(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_SENSE_6348(irq);
		अगर (bothedge)
			reg |= EXTIRQ_CFG_BOTHEDGE_6348(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_BOTHEDGE_6348(irq);
		अवरोध;

	हाल BCM3368_CPU_ID:
	हाल BCM6328_CPU_ID:
	हाल BCM6338_CPU_ID:
	हाल BCM6345_CPU_ID:
	हाल BCM6358_CPU_ID:
	हाल BCM6362_CPU_ID:
	हाल BCM6368_CPU_ID:
		अगर (levअन्यथाnse)
			reg |= EXTIRQ_CFG_LEVELSENSE(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_LEVELSENSE(irq);
		अगर (sense)
			reg |= EXTIRQ_CFG_SENSE(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_SENSE(irq);
		अगर (bothedge)
			reg |= EXTIRQ_CFG_BOTHEDGE(irq);
		अन्यथा
			reg &= ~EXTIRQ_CFG_BOTHEDGE(irq);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	bcm_perf_ग_लिखोl(reg, regaddr);
	spin_unlock_irqrestore(&epic_lock, flags);

	irqd_set_trigger_type(d, flow_type);
	अगर (flow_type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_edge_irq);

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक bcm63xx_पूर्णांकernal_set_affinity(काष्ठा irq_data *data,
					 स्थिर काष्ठा cpumask *dest,
					 bool क्रमce)
अणु
	अगर (!irqd_irq_disabled(data))
		पूर्णांकernal_irq_unmask(data, dest);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip bcm63xx_पूर्णांकernal_irq_chip = अणु
	.name		= "bcm63xx_ipic",
	.irq_mask	= bcm63xx_पूर्णांकernal_irq_mask,
	.irq_unmask	= bcm63xx_पूर्णांकernal_irq_unmask,
पूर्ण;

अटल काष्ठा irq_chip bcm63xx_बाह्यal_irq_chip = अणु
	.name		= "bcm63xx_epic",
	.irq_ack	= bcm63xx_बाह्यal_irq_clear,

	.irq_mask	= bcm63xx_बाह्यal_irq_mask,
	.irq_unmask	= bcm63xx_बाह्यal_irq_unmask,

	.irq_set_type	= bcm63xx_बाह्यal_irq_set_type,
पूर्ण;

अटल व्योम bcm63xx_init_irq(व्योम)
अणु
	पूर्णांक irq_bits;

	irq_stat_addr[0] = bcm63xx_regset_address(RSET_PERF);
	irq_mask_addr[0] = bcm63xx_regset_address(RSET_PERF);
	irq_stat_addr[1] = bcm63xx_regset_address(RSET_PERF);
	irq_mask_addr[1] = bcm63xx_regset_address(RSET_PERF);

	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM3368_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_3368_REG;
		irq_mask_addr[0] += PERF_IRQMASK_3368_REG;
		irq_stat_addr[1] = 0;
		irq_mask_addr[1] = 0;
		irq_bits = 32;
		ext_irq_count = 4;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_3368;
		अवरोध;
	हाल BCM6328_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6328_REG(0);
		irq_mask_addr[0] += PERF_IRQMASK_6328_REG(0);
		irq_stat_addr[1] += PERF_IRQSTAT_6328_REG(1);
		irq_mask_addr[1] += PERF_IRQMASK_6328_REG(1);
		irq_bits = 64;
		ext_irq_count = 4;
		is_ext_irq_cascaded = 1;
		ext_irq_start = BCM_6328_EXT_IRQ0 - IRQ_INTERNAL_BASE;
		ext_irq_end = BCM_6328_EXT_IRQ3 - IRQ_INTERNAL_BASE;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6328;
		अवरोध;
	हाल BCM6338_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6338_REG;
		irq_mask_addr[0] += PERF_IRQMASK_6338_REG;
		irq_stat_addr[1] = 0;
		irq_mask_addr[1] = 0;
		irq_bits = 32;
		ext_irq_count = 4;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6338;
		अवरोध;
	हाल BCM6345_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6345_REG;
		irq_mask_addr[0] += PERF_IRQMASK_6345_REG;
		irq_stat_addr[1] = 0;
		irq_mask_addr[1] = 0;
		irq_bits = 32;
		ext_irq_count = 4;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6345;
		अवरोध;
	हाल BCM6348_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6348_REG;
		irq_mask_addr[0] += PERF_IRQMASK_6348_REG;
		irq_stat_addr[1] = 0;
		irq_mask_addr[1] = 0;
		irq_bits = 32;
		ext_irq_count = 4;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6348;
		अवरोध;
	हाल BCM6358_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6358_REG(0);
		irq_mask_addr[0] += PERF_IRQMASK_6358_REG(0);
		irq_stat_addr[1] += PERF_IRQSTAT_6358_REG(1);
		irq_mask_addr[1] += PERF_IRQMASK_6358_REG(1);
		irq_bits = 32;
		ext_irq_count = 4;
		is_ext_irq_cascaded = 1;
		ext_irq_start = BCM_6358_EXT_IRQ0 - IRQ_INTERNAL_BASE;
		ext_irq_end = BCM_6358_EXT_IRQ3 - IRQ_INTERNAL_BASE;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6358;
		अवरोध;
	हाल BCM6362_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6362_REG(0);
		irq_mask_addr[0] += PERF_IRQMASK_6362_REG(0);
		irq_stat_addr[1] += PERF_IRQSTAT_6362_REG(1);
		irq_mask_addr[1] += PERF_IRQMASK_6362_REG(1);
		irq_bits = 64;
		ext_irq_count = 4;
		is_ext_irq_cascaded = 1;
		ext_irq_start = BCM_6362_EXT_IRQ0 - IRQ_INTERNAL_BASE;
		ext_irq_end = BCM_6362_EXT_IRQ3 - IRQ_INTERNAL_BASE;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6362;
		अवरोध;
	हाल BCM6368_CPU_ID:
		irq_stat_addr[0] += PERF_IRQSTAT_6368_REG(0);
		irq_mask_addr[0] += PERF_IRQMASK_6368_REG(0);
		irq_stat_addr[1] += PERF_IRQSTAT_6368_REG(1);
		irq_mask_addr[1] += PERF_IRQMASK_6368_REG(1);
		irq_bits = 64;
		ext_irq_count = 6;
		is_ext_irq_cascaded = 1;
		ext_irq_start = BCM_6368_EXT_IRQ0 - IRQ_INTERNAL_BASE;
		ext_irq_end = BCM_6368_EXT_IRQ5 - IRQ_INTERNAL_BASE;
		ext_irq_cfg_reg1 = PERF_EXTIRQ_CFG_REG_6368;
		ext_irq_cfg_reg2 = PERF_EXTIRQ_CFG_REG2_6368;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (irq_bits == 32) अणु
		dispatch_पूर्णांकernal = __dispatch_पूर्णांकernal_32;
		पूर्णांकernal_irq_mask = __पूर्णांकernal_irq_mask_32;
		पूर्णांकernal_irq_unmask = __पूर्णांकernal_irq_unmask_32;
	पूर्ण अन्यथा अणु
		dispatch_पूर्णांकernal = __dispatch_पूर्णांकernal_64;
		पूर्णांकernal_irq_mask = __पूर्णांकernal_irq_mask_64;
		पूर्णांकernal_irq_unmask = __पूर्णांकernal_irq_unmask_64;
	पूर्ण
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	पूर्णांक i, irq;

	bcm63xx_init_irq();
	mips_cpu_irq_init();
	क्रम (i = IRQ_INTERNAL_BASE; i < NR_IRQS; ++i)
		irq_set_chip_and_handler(i, &bcm63xx_पूर्णांकernal_irq_chip,
					 handle_level_irq);

	क्रम (i = IRQ_EXTERNAL_BASE; i < IRQ_EXTERNAL_BASE + ext_irq_count; ++i)
		irq_set_chip_and_handler(i, &bcm63xx_बाह्यal_irq_chip,
					 handle_edge_irq);

	अगर (!is_ext_irq_cascaded) अणु
		क्रम (i = 3; i < 3 + ext_irq_count; ++i) अणु
			irq = MIPS_CPU_IRQ_BASE + i;
			अगर (request_irq(irq, no_action, IRQF_NO_THREAD,
					"cascade_extirq", शून्य)) अणु
				pr_err("Failed to request irq %d (cascade_extirq)\n",
				       irq);
			पूर्ण
		पूर्ण
	पूर्ण

	irq = MIPS_CPU_IRQ_BASE + 2;
	अगर (request_irq(irq, no_action, IRQF_NO_THREAD,	"cascade_ip2", शून्य))
		pr_err("Failed to request irq %d (cascade_ip2)\n", irq);
#अगर_घोषित CONFIG_SMP
	अगर (is_ext_irq_cascaded) अणु
		irq = MIPS_CPU_IRQ_BASE + 3;
		अगर (request_irq(irq, no_action,	IRQF_NO_THREAD, "cascade_ip3",
				शून्य))
			pr_err("Failed to request irq %d (cascade_ip3)\n", irq);
		bcm63xx_पूर्णांकernal_irq_chip.irq_set_affinity =
			bcm63xx_पूर्णांकernal_set_affinity;

		cpumask_clear(irq_शेष_affinity);
		cpumask_set_cpu(smp_processor_id(), irq_शेष_affinity);
	पूर्ण
#पूर्ण_अगर
पूर्ण
