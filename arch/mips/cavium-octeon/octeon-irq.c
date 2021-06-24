<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2016 Cavium, Inc.
 */

#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-ciu2-defs.h>
#समावेश <यंत्र/octeon/cvmx-ciu3-defs.h>

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, octeon_irq_ciu0_en_mirror);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, octeon_irq_ciu1_en_mirror);
अटल DEFINE_PER_CPU(raw_spinlock_t, octeon_irq_ciu_spinlock);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, octeon_irq_ciu3_idt_ip2);

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, octeon_irq_ciu3_idt_ip3);
अटल DEFINE_PER_CPU(काष्ठा octeon_ciu3_info *, octeon_ciu3_info);
#घोषणा CIU3_MBOX_PER_CORE 10

/*
 * The 8 most signअगरicant bits of the पूर्णांकsn identअगरy the पूर्णांकerrupt major block.
 * Each major block might use its own पूर्णांकerrupt करोमुख्य. Thus 256 करोमुख्यs are
 * needed.
 */
#घोषणा MAX_CIU3_DOMAINS		256

प्रकार irq_hw_number_t (*octeon_ciu3_पूर्णांकsn2hw_t)(काष्ठा irq_करोमुख्य *, अचिन्हित पूर्णांक);

/* Inक्रमmation क्रम each ciu3 in the प्रणाली */
काष्ठा octeon_ciu3_info अणु
	u64			ciu3_addr;
	पूर्णांक			node;
	काष्ठा irq_करोमुख्य	*करोमुख्य[MAX_CIU3_DOMAINS];
	octeon_ciu3_पूर्णांकsn2hw_t	पूर्णांकsn2hw[MAX_CIU3_DOMAINS];
पूर्ण;

/* Each ciu3 in the प्रणाली uses its own data (one ciu3 per node) */
अटल काष्ठा octeon_ciu3_info	*octeon_ciu3_info_per_node[4];

काष्ठा octeon_irq_ciu_करोमुख्य_data अणु
	पूर्णांक num_sum;  /* number of sum रेजिस्टरs (2 or 3). */
पूर्ण;

/* Register offsets from ciu3_addr */
#घोषणा CIU3_CONST		0x220
#घोषणा CIU3_IDT_CTL(_idt)	((_idt) * 8 + 0x110000)
#घोषणा CIU3_IDT_PP(_idt, _idx)	((_idt) * 32 + (_idx) * 8 + 0x120000)
#घोषणा CIU3_IDT_IO(_idt)	((_idt) * 8 + 0x130000)
#घोषणा CIU3_DEST_PP_INT(_pp_ip) ((_pp_ip) * 8 + 0x200000)
#घोषणा CIU3_DEST_IO_INT(_io)	((_io) * 8 + 0x210000)
#घोषणा CIU3_ISC_CTL(_पूर्णांकsn)	((_पूर्णांकsn) * 8 + 0x80000000)
#घोषणा CIU3_ISC_W1C(_पूर्णांकsn)	((_पूर्णांकsn) * 8 + 0x90000000)
#घोषणा CIU3_ISC_W1S(_पूर्णांकsn)	((_पूर्णांकsn) * 8 + 0xa0000000)

अटल __पढ़ो_mostly पूर्णांक octeon_irq_ciu_to_irq[8][64];

काष्ठा octeon_ciu_chip_data अणु
	जोड़ अणु
		काष्ठा अणु		/* only used क्रम ciu3 */
			u64 ciu3_addr;
			अचिन्हित पूर्णांक पूर्णांकsn;
		पूर्ण;
		काष्ठा अणु		/* only used क्रम ciu/ciu2 */
			u8 line;
			u8 bit;
		पूर्ण;
	पूर्ण;
	पूर्णांक gpio_line;
	पूर्णांक current_cpu;	/* Next CPU expected to take this irq */
	पूर्णांक ciu_node; /* NUMA node number of the CIU */
पूर्ण;

काष्ठा octeon_core_chip_data अणु
	काष्ठा mutex core_irq_mutex;
	bool current_en;
	bool desired_en;
	u8 bit;
पूर्ण;

#घोषणा MIPS_CORE_IRQ_LINES 8

अटल काष्ठा octeon_core_chip_data octeon_irq_core_chip_data[MIPS_CORE_IRQ_LINES];

अटल पूर्णांक octeon_irq_set_ciu_mapping(पूर्णांक irq, पूर्णांक line, पूर्णांक bit, पूर्णांक gpio_line,
				      काष्ठा irq_chip *chip,
				      irq_flow_handler_t handler)
अणु
	काष्ठा octeon_ciu_chip_data *cd;

	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;

	irq_set_chip_and_handler(irq, chip, handler);

	cd->line = line;
	cd->bit = bit;
	cd->gpio_line = gpio_line;

	irq_set_chip_data(irq, cd);
	octeon_irq_ciu_to_irq[line][bit] = irq;
	वापस 0;
पूर्ण

अटल व्योम octeon_irq_मुक्त_cd(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	काष्ठा octeon_ciu_chip_data *cd = irq_data_get_irq_chip_data(data);

	irq_set_chip_data(irq, शून्य);
	kमुक्त(cd);
पूर्ण

अटल पूर्णांक octeon_irq_क्रमce_ciu_mapping(काष्ठा irq_करोमुख्य *करोमुख्य,
					पूर्णांक irq, पूर्णांक line, पूर्णांक bit)
अणु
	वापस irq_करोमुख्य_associate(करोमुख्य, irq, line << 6 | bit);
पूर्ण

अटल पूर्णांक octeon_coreid_क्रम_cpu(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	वापस cpu_logical_map(cpu);
#अन्यथा
	वापस cvmx_get_core_num();
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक octeon_cpu_क्रम_coreid(पूर्णांक coreid)
अणु
#अगर_घोषित CONFIG_SMP
	वापस cpu_number_map(coreid);
#अन्यथा
	वापस smp_processor_id();
#पूर्ण_अगर
पूर्ण

अटल व्योम octeon_irq_core_ack(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक bit = cd->bit;

	/*
	 * We करोn't need to disable IRQs to make these atomic since
	 * they are alपढ़ोy disabled earlier in the low level
	 * पूर्णांकerrupt code.
	 */
	clear_c0_status(0x100 << bit);
	/* The two user पूर्णांकerrupts must be cleared manually. */
	अगर (bit < 2)
		clear_c0_cause(0x100 << bit);
पूर्ण

अटल व्योम octeon_irq_core_eoi(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);

	/*
	 * We करोn't need to disable IRQs to make these atomic since
	 * they are alपढ़ोy disabled earlier in the low level
	 * पूर्णांकerrupt code.
	 */
	set_c0_status(0x100 << cd->bit);
पूर्ण

अटल व्योम octeon_irq_core_set_enable_local(व्योम *arg)
अणु
	काष्ठा irq_data *data = arg;
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक mask = 0x100 << cd->bit;

	/*
	 * Interrupts are alपढ़ोy disabled, so these are atomic.
	 */
	अगर (cd->desired_en)
		set_c0_status(mask);
	अन्यथा
		clear_c0_status(mask);

पूर्ण

अटल व्योम octeon_irq_core_disable(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);
	cd->desired_en = false;
पूर्ण

अटल व्योम octeon_irq_core_enable(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);
	cd->desired_en = true;
पूर्ण

अटल व्योम octeon_irq_core_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);

	mutex_lock(&cd->core_irq_mutex);
पूर्ण

अटल व्योम octeon_irq_core_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_core_chip_data *cd = irq_data_get_irq_chip_data(data);

	अगर (cd->desired_en != cd->current_en) अणु
		on_each_cpu(octeon_irq_core_set_enable_local, data, 1);

		cd->current_en = cd->desired_en;
	पूर्ण

	mutex_unlock(&cd->core_irq_mutex);
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_core = अणु
	.name = "Core",
	.irq_enable = octeon_irq_core_enable,
	.irq_disable = octeon_irq_core_disable,
	.irq_ack = octeon_irq_core_ack,
	.irq_eoi = octeon_irq_core_eoi,
	.irq_bus_lock = octeon_irq_core_bus_lock,
	.irq_bus_sync_unlock = octeon_irq_core_bus_sync_unlock,

	.irq_cpu_online = octeon_irq_core_eoi,
	.irq_cpu_offline = octeon_irq_core_ack,
	.flags = IRQCHIP_ONOFFLINE_ENABLED,
पूर्ण;

अटल व्योम __init octeon_irq_init_core(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक irq;
	काष्ठा octeon_core_chip_data *cd;

	क्रम (i = 0; i < MIPS_CORE_IRQ_LINES; i++) अणु
		cd = &octeon_irq_core_chip_data[i];
		cd->current_en = false;
		cd->desired_en = false;
		cd->bit = i;
		mutex_init(&cd->core_irq_mutex);

		irq = OCTEON_IRQ_SW0 + i;
		irq_set_chip_data(irq, cd);
		irq_set_chip_and_handler(irq, &octeon_irq_chip_core,
					 handle_percpu_irq);
	पूर्ण
पूर्ण

अटल पूर्णांक next_cpu_क्रम_irq(काष्ठा irq_data *data)
अणु

#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
	काष्ठा cpumask *mask = irq_data_get_affinity_mask(data);
	पूर्णांक weight = cpumask_weight(mask);
	काष्ठा octeon_ciu_chip_data *cd = irq_data_get_irq_chip_data(data);

	अगर (weight > 1) अणु
		cpu = cd->current_cpu;
		क्रम (;;) अणु
			cpu = cpumask_next(cpu, mask);
			अगर (cpu >= nr_cpu_ids) अणु
				cpu = -1;
				जारी;
			पूर्ण अन्यथा अगर (cpumask_test_cpu(cpu, cpu_online_mask)) अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (weight == 1) अणु
		cpu = cpumask_first(mask);
	पूर्ण अन्यथा अणु
		cpu = smp_processor_id();
	पूर्ण
	cd->current_cpu = cpu;
	वापस cpu;
#अन्यथा
	वापस smp_processor_id();
#पूर्ण_अगर
पूर्ण

अटल व्योम octeon_irq_ciu_enable(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);
	अचिन्हित दीर्घ *pen;
	अचिन्हित दीर्घ flags;
	काष्ठा octeon_ciu_chip_data *cd;
	raw_spinlock_t *lock = &per_cpu(octeon_irq_ciu_spinlock, cpu);

	cd = irq_data_get_irq_chip_data(data);

	raw_spin_lock_irqsave(lock, flags);
	अगर (cd->line == 0) अणु
		pen = &per_cpu(octeon_irq_ciu0_en_mirror, cpu);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(coreid * 2), *pen);
	पूर्ण अन्यथा अणु
		pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), *pen);
	पूर्ण
	raw_spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल व्योम octeon_irq_ciu_enable_local(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ *pen;
	अचिन्हित दीर्घ flags;
	काष्ठा octeon_ciu_chip_data *cd;
	raw_spinlock_t *lock = this_cpu_ptr(&octeon_irq_ciu_spinlock);

	cd = irq_data_get_irq_chip_data(data);

	raw_spin_lock_irqsave(lock, flags);
	अगर (cd->line == 0) अणु
		pen = this_cpu_ptr(&octeon_irq_ciu0_en_mirror);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num() * 2), *pen);
	पूर्ण अन्यथा अणु
		pen = this_cpu_ptr(&octeon_irq_ciu1_en_mirror);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(cvmx_get_core_num() * 2 + 1), *pen);
	पूर्ण
	raw_spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल व्योम octeon_irq_ciu_disable_local(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ *pen;
	अचिन्हित दीर्घ flags;
	काष्ठा octeon_ciu_chip_data *cd;
	raw_spinlock_t *lock = this_cpu_ptr(&octeon_irq_ciu_spinlock);

	cd = irq_data_get_irq_chip_data(data);

	raw_spin_lock_irqsave(lock, flags);
	अगर (cd->line == 0) अणु
		pen = this_cpu_ptr(&octeon_irq_ciu0_en_mirror);
		__clear_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num() * 2), *pen);
	पूर्ण अन्यथा अणु
		pen = this_cpu_ptr(&octeon_irq_ciu1_en_mirror);
		__clear_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(cvmx_get_core_num() * 2 + 1), *pen);
	पूर्ण
	raw_spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल व्योम octeon_irq_ciu_disable_all(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *pen;
	पूर्णांक cpu;
	काष्ठा octeon_ciu_chip_data *cd;
	raw_spinlock_t *lock;

	cd = irq_data_get_irq_chip_data(data);

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);
		lock = &per_cpu(octeon_irq_ciu_spinlock, cpu);
		अगर (cd->line == 0)
			pen = &per_cpu(octeon_irq_ciu0_en_mirror, cpu);
		अन्यथा
			pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);

		raw_spin_lock_irqsave(lock, flags);
		__clear_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		अगर (cd->line == 0)
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(coreid * 2), *pen);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), *pen);
		raw_spin_unlock_irqrestore(lock, flags);
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ciu_enable_all(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *pen;
	पूर्णांक cpu;
	काष्ठा octeon_ciu_chip_data *cd;
	raw_spinlock_t *lock;

	cd = irq_data_get_irq_chip_data(data);

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);
		lock = &per_cpu(octeon_irq_ciu_spinlock, cpu);
		अगर (cd->line == 0)
			pen = &per_cpu(octeon_irq_ciu0_en_mirror, cpu);
		अन्यथा
			pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);

		raw_spin_lock_irqsave(lock, flags);
		__set_bit(cd->bit, pen);
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();
		अगर (cd->line == 0)
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(coreid * 2), *pen);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), *pen);
		raw_spin_unlock_irqrestore(lock, flags);
	पूर्ण
पूर्ण

/*
 * Enable the irq on the next core in the affinity set क्रम chips that
 * have the EN*_W1अणुS,Cपूर्ण रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_enable_v2(काष्ठा irq_data *data)
अणु
	u64 mask;
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	/*
	 * Called under the desc lock, so these should never get out
	 * of sync.
	 */
	अगर (cd->line == 0) अणु
		पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2;
		set_bit(cd->bit, &per_cpu(octeon_irq_ciu0_en_mirror, cpu));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1S(index), mask);
	पूर्ण अन्यथा अणु
		पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2 + 1;
		set_bit(cd->bit, &per_cpu(octeon_irq_ciu1_en_mirror, cpu));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1S(index), mask);
	पूर्ण
पूर्ण

/*
 * Enable the irq in the sum2 रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_enable_sum2(काष्ठा irq_data *data)
अणु
	u64 mask;
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	पूर्णांक index = octeon_coreid_क्रम_cpu(cpu);
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	cvmx_ग_लिखो_csr(CVMX_CIU_EN2_PPX_IP4_W1S(index), mask);
पूर्ण

/*
 * Disable the irq in the sum2 रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_disable_local_sum2(काष्ठा irq_data *data)
अणु
	u64 mask;
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	पूर्णांक index = octeon_coreid_क्रम_cpu(cpu);
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	cvmx_ग_लिखो_csr(CVMX_CIU_EN2_PPX_IP4_W1C(index), mask);
पूर्ण

अटल व्योम octeon_irq_ciu_ack_sum2(काष्ठा irq_data *data)
अणु
	u64 mask;
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	पूर्णांक index = octeon_coreid_क्रम_cpu(cpu);
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	cvmx_ग_लिखो_csr(CVMX_CIU_SUM2_PPX_IP4(index), mask);
पूर्ण

अटल व्योम octeon_irq_ciu_disable_all_sum2(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	काष्ठा octeon_ciu_chip_data *cd;
	u64 mask;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);

		cvmx_ग_लिखो_csr(CVMX_CIU_EN2_PPX_IP4_W1C(coreid), mask);
	पूर्ण
पूर्ण

/*
 * Enable the irq on the current CPU क्रम chips that
 * have the EN*_W1अणुS,Cपूर्ण रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_enable_local_v2(काष्ठा irq_data *data)
अणु
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	अगर (cd->line == 0) अणु
		पूर्णांक index = cvmx_get_core_num() * 2;
		set_bit(cd->bit, this_cpu_ptr(&octeon_irq_ciu0_en_mirror));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1S(index), mask);
	पूर्ण अन्यथा अणु
		पूर्णांक index = cvmx_get_core_num() * 2 + 1;
		set_bit(cd->bit, this_cpu_ptr(&octeon_irq_ciu1_en_mirror));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1S(index), mask);
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ciu_disable_local_v2(काष्ठा irq_data *data)
अणु
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	अगर (cd->line == 0) अणु
		पूर्णांक index = cvmx_get_core_num() * 2;
		clear_bit(cd->bit, this_cpu_ptr(&octeon_irq_ciu0_en_mirror));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1C(index), mask);
	पूर्ण अन्यथा अणु
		पूर्णांक index = cvmx_get_core_num() * 2 + 1;
		clear_bit(cd->bit, this_cpu_ptr(&octeon_irq_ciu1_en_mirror));
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1C(index), mask);
	पूर्ण
पूर्ण

/*
 * Write to the W1C bit in CVMX_CIU_INTX_SUM0 to clear the irq.
 */
अटल व्योम octeon_irq_ciu_ack(काष्ठा irq_data *data)
अणु
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	अगर (cd->line == 0) अणु
		पूर्णांक index = cvmx_get_core_num() * 2;
		cvmx_ग_लिखो_csr(CVMX_CIU_INTX_SUM0(index), mask);
	पूर्ण अन्यथा अणु
		cvmx_ग_लिखो_csr(CVMX_CIU_INT_SUM1, mask);
	पूर्ण
पूर्ण

/*
 * Disable the irq on the all cores क्रम chips that have the EN*_W1अणुS,Cपूर्ण
 * रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_disable_all_v2(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	अगर (cd->line == 0) अणु
		क्रम_each_online_cpu(cpu) अणु
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2;
			clear_bit(cd->bit,
				&per_cpu(octeon_irq_ciu0_en_mirror, cpu));
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1C(index), mask);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_online_cpu(cpu) अणु
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2 + 1;
			clear_bit(cd->bit,
				&per_cpu(octeon_irq_ciu1_en_mirror, cpu));
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1C(index), mask);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Enable the irq on the all cores क्रम chips that have the EN*_W1अणुS,Cपूर्ण
 * रेजिस्टरs.
 */
अटल व्योम octeon_irq_ciu_enable_all_v2(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	अगर (cd->line == 0) अणु
		क्रम_each_online_cpu(cpu) अणु
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2;
			set_bit(cd->bit,
				&per_cpu(octeon_irq_ciu0_en_mirror, cpu));
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1S(index), mask);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_online_cpu(cpu) अणु
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2 + 1;
			set_bit(cd->bit,
				&per_cpu(octeon_irq_ciu1_en_mirror, cpu));
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1S(index), mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_irq_ciu_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक t)
अणु
	irqd_set_trigger_type(data, t);

	अगर (t & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(data, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_level_irq);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम octeon_irq_gpio_setup(काष्ठा irq_data *data)
अणु
	जोड़ cvmx_gpio_bit_cfgx cfg;
	काष्ठा octeon_ciu_chip_data *cd;
	u32 t = irqd_get_trigger_type(data);

	cd = irq_data_get_irq_chip_data(data);

	cfg.u64 = 0;
	cfg.s.पूर्णांक_en = 1;
	cfg.s.पूर्णांक_type = (t & IRQ_TYPE_EDGE_BOTH) != 0;
	cfg.s.rx_xor = (t & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_EDGE_FALLING)) != 0;

	/* 140 nS glitch filter*/
	cfg.s.fil_cnt = 7;
	cfg.s.fil_sel = 3;

	cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(cd->gpio_line), cfg.u64);
पूर्ण

अटल व्योम octeon_irq_ciu_enable_gpio_v2(काष्ठा irq_data *data)
अणु
	octeon_irq_gpio_setup(data);
	octeon_irq_ciu_enable_v2(data);
पूर्ण

अटल व्योम octeon_irq_ciu_enable_gpio(काष्ठा irq_data *data)
अणु
	octeon_irq_gpio_setup(data);
	octeon_irq_ciu_enable(data);
पूर्ण

अटल पूर्णांक octeon_irq_ciu_gpio_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक t)
अणु
	irqd_set_trigger_type(data, t);
	octeon_irq_gpio_setup(data);

	अगर (t & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(data, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_level_irq);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम octeon_irq_ciu_disable_gpio_v2(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(cd->gpio_line), 0);

	octeon_irq_ciu_disable_all_v2(data);
पूर्ण

अटल व्योम octeon_irq_ciu_disable_gpio(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(cd->gpio_line), 0);

	octeon_irq_ciu_disable_all(data);
पूर्ण

अटल व्योम octeon_irq_ciu_gpio_ack(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_ciu_chip_data *cd;
	u64 mask;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->gpio_line);

	cvmx_ग_लिखो_csr(CVMX_GPIO_INT_CLR, mask);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम octeon_irq_cpu_offline_ciu(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu = smp_processor_id();
	cpumask_t new_affinity;
	काष्ठा cpumask *mask = irq_data_get_affinity_mask(data);

	अगर (!cpumask_test_cpu(cpu, mask))
		वापस;

	अगर (cpumask_weight(mask) > 1) अणु
		/*
		 * It has multi CPU affinity, just हटाओ this CPU
		 * from the affinity set.
		 */
		cpumask_copy(&new_affinity, mask);
		cpumask_clear_cpu(cpu, &new_affinity);
	पूर्ण अन्यथा अणु
		/* Otherwise, put it on lowest numbered online CPU. */
		cpumask_clear(&new_affinity);
		cpumask_set_cpu(cpumask_first(cpu_online_mask), &new_affinity);
	पूर्ण
	irq_set_affinity_locked(data, &new_affinity, false);
पूर्ण

अटल पूर्णांक octeon_irq_ciu_set_affinity(काष्ठा irq_data *data,
				       स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	पूर्णांक cpu;
	bool enable_one = !irqd_irq_disabled(data) && !irqd_irq_masked(data);
	अचिन्हित दीर्घ flags;
	काष्ठा octeon_ciu_chip_data *cd;
	अचिन्हित दीर्घ *pen;
	raw_spinlock_t *lock;

	cd = irq_data_get_irq_chip_data(data);

	/*
	 * For non-v2 CIU, we will allow only single CPU affinity.
	 * This हटाओs the need to करो locking in the .ack/.eoi
	 * functions.
	 */
	अगर (cpumask_weight(dest) != 1)
		वापस -EINVAL;

	अगर (!enable_one)
		वापस 0;


	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);

		lock = &per_cpu(octeon_irq_ciu_spinlock, cpu);
		raw_spin_lock_irqsave(lock, flags);

		अगर (cd->line == 0)
			pen = &per_cpu(octeon_irq_ciu0_en_mirror, cpu);
		अन्यथा
			pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);

		अगर (cpumask_test_cpu(cpu, dest) && enable_one) अणु
			enable_one = false;
			__set_bit(cd->bit, pen);
		पूर्ण अन्यथा अणु
			__clear_bit(cd->bit, pen);
		पूर्ण
		/*
		 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe
		 * enabling the irq.
		 */
		wmb();

		अगर (cd->line == 0)
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0(coreid * 2), *pen);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), *pen);

		raw_spin_unlock_irqrestore(lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set affinity क्रम the irq क्रम chips that have the EN*_W1अणुS,Cपूर्ण
 * रेजिस्टरs.
 */
अटल पूर्णांक octeon_irq_ciu_set_affinity_v2(काष्ठा irq_data *data,
					  स्थिर काष्ठा cpumask *dest,
					  bool क्रमce)
अणु
	पूर्णांक cpu;
	bool enable_one = !irqd_irq_disabled(data) && !irqd_irq_masked(data);
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	अगर (!enable_one)
		वापस 0;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << cd->bit;

	अगर (cd->line == 0) अणु
		क्रम_each_online_cpu(cpu) अणु
			अचिन्हित दीर्घ *pen = &per_cpu(octeon_irq_ciu0_en_mirror, cpu);
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2;
			अगर (cpumask_test_cpu(cpu, dest) && enable_one) अणु
				enable_one = false;
				set_bit(cd->bit, pen);
				cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1S(index), mask);
			पूर्ण अन्यथा अणु
				clear_bit(cd->bit, pen);
				cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0_W1C(index), mask);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_online_cpu(cpu) अणु
			अचिन्हित दीर्घ *pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);
			पूर्णांक index = octeon_coreid_क्रम_cpu(cpu) * 2 + 1;
			अगर (cpumask_test_cpu(cpu, dest) && enable_one) अणु
				enable_one = false;
				set_bit(cd->bit, pen);
				cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1S(index), mask);
			पूर्ण अन्यथा अणु
				clear_bit(cd->bit, pen);
				cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1C(index), mask);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_irq_ciu_set_affinity_sum2(काष्ठा irq_data *data,
					    स्थिर काष्ठा cpumask *dest,
					    bool क्रमce)
अणु
	पूर्णांक cpu;
	bool enable_one = !irqd_irq_disabled(data) && !irqd_irq_masked(data);
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	अगर (!enable_one)
		वापस 0;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << cd->bit;

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक index = octeon_coreid_क्रम_cpu(cpu);

		अगर (cpumask_test_cpu(cpu, dest) && enable_one) अणु
			enable_one = false;
			cvmx_ग_लिखो_csr(CVMX_CIU_EN2_PPX_IP4_W1S(index), mask);
		पूर्ण अन्यथा अणु
			cvmx_ग_लिखो_csr(CVMX_CIU_EN2_PPX_IP4_W1C(index), mask);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक edge_startup(काष्ठा irq_data *data)
अणु
	/* ack any pending edge-irq at startup, so there is
	 * an _edge_ to fire on when the event reappears.
	 */
	data->chip->irq_ack(data);
	data->chip->irq_enable(data);
	वापस 0;
पूर्ण

/*
 * Newer octeon chips have support क्रम lockless CIU operation.
 */
अटल काष्ठा irq_chip octeon_irq_chip_ciu_v2 = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable_v2,
	.irq_disable = octeon_irq_ciu_disable_all_v2,
	.irq_mask = octeon_irq_ciu_disable_local_v2,
	.irq_unmask = octeon_irq_ciu_enable_v2,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity_v2,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_v2_edge = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable_v2,
	.irq_disable = octeon_irq_ciu_disable_all_v2,
	.irq_ack = octeon_irq_ciu_ack,
	.irq_mask = octeon_irq_ciu_disable_local_v2,
	.irq_unmask = octeon_irq_ciu_enable_v2,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity_v2,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

/*
 * Newer octeon chips have support क्रम lockless CIU operation.
 */
अटल काष्ठा irq_chip octeon_irq_chip_ciu_sum2 = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable_sum2,
	.irq_disable = octeon_irq_ciu_disable_all_sum2,
	.irq_mask = octeon_irq_ciu_disable_local_sum2,
	.irq_unmask = octeon_irq_ciu_enable_sum2,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity_sum2,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_sum2_edge = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable_sum2,
	.irq_disable = octeon_irq_ciu_disable_all_sum2,
	.irq_ack = octeon_irq_ciu_ack_sum2,
	.irq_mask = octeon_irq_ciu_disable_local_sum2,
	.irq_unmask = octeon_irq_ciu_enable_sum2,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity_sum2,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable,
	.irq_disable = octeon_irq_ciu_disable_all,
	.irq_mask = octeon_irq_ciu_disable_local,
	.irq_unmask = octeon_irq_ciu_enable,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_edge = अणु
	.name = "CIU",
	.irq_enable = octeon_irq_ciu_enable,
	.irq_disable = octeon_irq_ciu_disable_all,
	.irq_ack = octeon_irq_ciu_ack,
	.irq_mask = octeon_irq_ciu_disable_local,
	.irq_unmask = octeon_irq_ciu_enable,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

/* The mbox versions करोn't करो any affinity or round-robin. */
अटल काष्ठा irq_chip octeon_irq_chip_ciu_mbox_v2 = अणु
	.name = "CIU-M",
	.irq_enable = octeon_irq_ciu_enable_all_v2,
	.irq_disable = octeon_irq_ciu_disable_all_v2,
	.irq_ack = octeon_irq_ciu_disable_local_v2,
	.irq_eoi = octeon_irq_ciu_enable_local_v2,

	.irq_cpu_online = octeon_irq_ciu_enable_local_v2,
	.irq_cpu_offline = octeon_irq_ciu_disable_local_v2,
	.flags = IRQCHIP_ONOFFLINE_ENABLED,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_mbox = अणु
	.name = "CIU-M",
	.irq_enable = octeon_irq_ciu_enable_all,
	.irq_disable = octeon_irq_ciu_disable_all,
	.irq_ack = octeon_irq_ciu_disable_local,
	.irq_eoi = octeon_irq_ciu_enable_local,

	.irq_cpu_online = octeon_irq_ciu_enable_local,
	.irq_cpu_offline = octeon_irq_ciu_disable_local,
	.flags = IRQCHIP_ONOFFLINE_ENABLED,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_gpio_v2 = अणु
	.name = "CIU-GPIO",
	.irq_enable = octeon_irq_ciu_enable_gpio_v2,
	.irq_disable = octeon_irq_ciu_disable_gpio_v2,
	.irq_ack = octeon_irq_ciu_gpio_ack,
	.irq_mask = octeon_irq_ciu_disable_local_v2,
	.irq_unmask = octeon_irq_ciu_enable_v2,
	.irq_set_type = octeon_irq_ciu_gpio_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity_v2,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
	.flags = IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_gpio = अणु
	.name = "CIU-GPIO",
	.irq_enable = octeon_irq_ciu_enable_gpio,
	.irq_disable = octeon_irq_ciu_disable_gpio,
	.irq_mask = octeon_irq_ciu_disable_local,
	.irq_unmask = octeon_irq_ciu_enable,
	.irq_ack = octeon_irq_ciu_gpio_ack,
	.irq_set_type = octeon_irq_ciu_gpio_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
	.flags = IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

/*
 * Watchकरोg पूर्णांकerrupts are special.  They are associated with a single
 * core, so we hardwire the affinity to that core.
 */
अटल व्योम octeon_irq_ciu_wd_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *pen;
	पूर्णांक coreid = data->irq - OCTEON_IRQ_WDOG0;	/* Bit 0-63 of EN1 */
	पूर्णांक cpu = octeon_cpu_क्रम_coreid(coreid);
	raw_spinlock_t *lock = &per_cpu(octeon_irq_ciu_spinlock, cpu);

	raw_spin_lock_irqsave(lock, flags);
	pen = &per_cpu(octeon_irq_ciu1_en_mirror, cpu);
	__set_bit(coreid, pen);
	/*
	 * Must be visible to octeon_irq_ipअणु2,3पूर्ण_ciu() beक्रमe enabling
	 * the irq.
	 */
	wmb();
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), *pen);
	raw_spin_unlock_irqrestore(lock, flags);
पूर्ण

/*
 * Watchकरोg पूर्णांकerrupts are special.  They are associated with a single
 * core, so we hardwire the affinity to that core.
 */
अटल व्योम octeon_irq_ciu1_wd_enable_v2(काष्ठा irq_data *data)
अणु
	पूर्णांक coreid = data->irq - OCTEON_IRQ_WDOG0;
	पूर्णांक cpu = octeon_cpu_क्रम_coreid(coreid);

	set_bit(coreid, &per_cpu(octeon_irq_ciu1_en_mirror, cpu));
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1_W1S(coreid * 2 + 1), 1ull << coreid);
पूर्ण


अटल काष्ठा irq_chip octeon_irq_chip_ciu_wd_v2 = अणु
	.name = "CIU-W",
	.irq_enable = octeon_irq_ciu1_wd_enable_v2,
	.irq_disable = octeon_irq_ciu_disable_all_v2,
	.irq_mask = octeon_irq_ciu_disable_local_v2,
	.irq_unmask = octeon_irq_ciu_enable_local_v2,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu_wd = अणु
	.name = "CIU-W",
	.irq_enable = octeon_irq_ciu_wd_enable,
	.irq_disable = octeon_irq_ciu_disable_all,
	.irq_mask = octeon_irq_ciu_disable_local,
	.irq_unmask = octeon_irq_ciu_enable_local,
पूर्ण;

अटल bool octeon_irq_ciu_is_edge(अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक bit)
अणु
	bool edge = false;

	अगर (line == 0)
		चयन (bit) अणु
		हाल 48 ... 49: /* GMX DRP */
		हाल 50: /* IPD_DRP */
		हाल 52 ... 55: /* Timers */
		हाल 58: /* MPI */
			edge = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	अन्यथा /* line == 1 */
		चयन (bit) अणु
		हाल 47: /* PTP */
			edge = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	वापस edge;
पूर्ण

काष्ठा octeon_irq_gpio_करोमुख्य_data अणु
	अचिन्हित पूर्णांक base_hwirq;
पूर्ण;

अटल पूर्णांक octeon_irq_gpio_xlat(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *node,
				स्थिर u32 *पूर्णांकspec,
				अचिन्हित पूर्णांक पूर्णांकsize,
				अचिन्हित दीर्घ *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक pin;
	अचिन्हित पूर्णांक trigger;

	अगर (irq_करोमुख्य_get_of_node(d) != node)
		वापस -EINVAL;

	अगर (पूर्णांकsize < 2)
		वापस -EINVAL;

	pin = पूर्णांकspec[0];
	अगर (pin >= 16)
		वापस -EINVAL;

	trigger = पूर्णांकspec[1];

	चयन (trigger) अणु
	हाल 1:
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल 2:
		type = IRQ_TYPE_EDGE_FALLING;
		अवरोध;
	हाल 4:
		type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल 8:
		type = IRQ_TYPE_LEVEL_LOW;
		अवरोध;
	शेष:
		pr_err("Error: (%pOFn) Invalid irq trigger specification: %x\n",
		       node,
		       trigger);
		type = IRQ_TYPE_LEVEL_LOW;
		अवरोध;
	पूर्ण
	*out_type = type;
	*out_hwirq = pin;

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_irq_ciu_xlat(काष्ठा irq_करोमुख्य *d,
			       काष्ठा device_node *node,
			       स्थिर u32 *पूर्णांकspec,
			       अचिन्हित पूर्णांक पूर्णांकsize,
			       अचिन्हित दीर्घ *out_hwirq,
			       अचिन्हित पूर्णांक *out_type)
अणु
	अचिन्हित पूर्णांक ciu, bit;
	काष्ठा octeon_irq_ciu_करोमुख्य_data *dd = d->host_data;

	ciu = पूर्णांकspec[0];
	bit = पूर्णांकspec[1];

	अगर (ciu >= dd->num_sum || bit > 63)
		वापस -EINVAL;

	*out_hwirq = (ciu << 6) | bit;
	*out_type = 0;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip *octeon_irq_ciu_chip;
अटल काष्ठा irq_chip *octeon_irq_ciu_chip_edge;
अटल काष्ठा irq_chip *octeon_irq_gpio_chip;

अटल पूर्णांक octeon_irq_ciu_map(काष्ठा irq_करोमुख्य *d,
			      अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	पूर्णांक rv;
	अचिन्हित पूर्णांक line = hw >> 6;
	अचिन्हित पूर्णांक bit = hw & 63;
	काष्ठा octeon_irq_ciu_करोमुख्य_data *dd = d->host_data;

	अगर (line >= dd->num_sum || octeon_irq_ciu_to_irq[line][bit] != 0)
		वापस -EINVAL;

	अगर (line == 2) अणु
		अगर (octeon_irq_ciu_is_edge(line, bit))
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				&octeon_irq_chip_ciu_sum2_edge,
				handle_edge_irq);
		अन्यथा
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				&octeon_irq_chip_ciu_sum2,
				handle_level_irq);
	पूर्ण अन्यथा अणु
		अगर (octeon_irq_ciu_is_edge(line, bit))
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				octeon_irq_ciu_chip_edge,
				handle_edge_irq);
		अन्यथा
			rv = octeon_irq_set_ciu_mapping(virq, line, bit, 0,
				octeon_irq_ciu_chip,
				handle_level_irq);
	पूर्ण
	वापस rv;
पूर्ण

अटल पूर्णांक octeon_irq_gpio_map(काष्ठा irq_करोमुख्य *d,
			       अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	काष्ठा octeon_irq_gpio_करोमुख्य_data *gpiod = d->host_data;
	अचिन्हित पूर्णांक line, bit;
	पूर्णांक r;

	line = (hw + gpiod->base_hwirq) >> 6;
	bit = (hw + gpiod->base_hwirq) & 63;
	अगर (line >= ARRAY_SIZE(octeon_irq_ciu_to_irq) ||
		octeon_irq_ciu_to_irq[line][bit] != 0)
		वापस -EINVAL;

	/*
	 * Default to handle_level_irq. If the DT contains a dअगरferent
	 * trigger type, it will call the irq_set_type callback and
	 * the handler माला_लो updated.
	 */
	r = octeon_irq_set_ciu_mapping(virq, line, bit, hw,
				       octeon_irq_gpio_chip, handle_level_irq);
	वापस r;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops octeon_irq_करोमुख्य_ciu_ops = अणु
	.map = octeon_irq_ciu_map,
	.unmap = octeon_irq_मुक्त_cd,
	.xlate = octeon_irq_ciu_xlat,
पूर्ण;

अटल काष्ठा irq_करोमुख्य_ops octeon_irq_करोमुख्य_gpio_ops = अणु
	.map = octeon_irq_gpio_map,
	.unmap = octeon_irq_मुक्त_cd,
	.xlate = octeon_irq_gpio_xlat,
पूर्ण;

अटल व्योम octeon_irq_ip2_ciu(व्योम)
अणु
	स्थिर अचिन्हित दीर्घ core_id = cvmx_get_core_num();
	u64 ciu_sum = cvmx_पढ़ो_csr(CVMX_CIU_INTX_SUM0(core_id * 2));

	ciu_sum &= __this_cpu_पढ़ो(octeon_irq_ciu0_en_mirror);
	अगर (likely(ciu_sum)) अणु
		पूर्णांक bit = fls64(ciu_sum) - 1;
		पूर्णांक irq = octeon_irq_ciu_to_irq[0][bit];
		अगर (likely(irq))
			करो_IRQ(irq);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ip3_ciu(व्योम)
अणु
	u64 ciu_sum = cvmx_पढ़ो_csr(CVMX_CIU_INT_SUM1);

	ciu_sum &= __this_cpu_पढ़ो(octeon_irq_ciu1_en_mirror);
	अगर (likely(ciu_sum)) अणु
		पूर्णांक bit = fls64(ciu_sum) - 1;
		पूर्णांक irq = octeon_irq_ciu_to_irq[1][bit];
		अगर (likely(irq))
			करो_IRQ(irq);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ip4_ciu(व्योम)
अणु
	पूर्णांक coreid = cvmx_get_core_num();
	u64 ciu_sum = cvmx_पढ़ो_csr(CVMX_CIU_SUM2_PPX_IP4(coreid));
	u64 ciu_en = cvmx_पढ़ो_csr(CVMX_CIU_EN2_PPX_IP4(coreid));

	ciu_sum &= ciu_en;
	अगर (likely(ciu_sum)) अणु
		पूर्णांक bit = fls64(ciu_sum) - 1;
		पूर्णांक irq = octeon_irq_ciu_to_irq[2][bit];

		अगर (likely(irq))
			करो_IRQ(irq);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल bool octeon_irq_use_ip4;

अटल व्योम octeon_irq_local_enable_ip4(व्योम *arg)
अणु
	set_c0_status(STATUSF_IP4);
पूर्ण

अटल व्योम octeon_irq_ip4_mask(व्योम)
अणु
	clear_c0_status(STATUSF_IP4);
	spurious_पूर्णांकerrupt();
पूर्ण

अटल व्योम (*octeon_irq_ip2)(व्योम);
अटल व्योम (*octeon_irq_ip3)(व्योम);
अटल व्योम (*octeon_irq_ip4)(व्योम);

व्योम (*octeon_irq_setup_secondary)(व्योम);

व्योम octeon_irq_set_ip4_handler(octeon_irq_ip4_handler_t h)
अणु
	octeon_irq_ip4 = h;
	octeon_irq_use_ip4 = true;
	on_each_cpu(octeon_irq_local_enable_ip4, शून्य, 1);
पूर्ण

अटल व्योम octeon_irq_percpu_enable(व्योम)
अणु
	irq_cpu_online();
पूर्ण

अटल व्योम octeon_irq_init_ciu_percpu(व्योम)
अणु
	पूर्णांक coreid = cvmx_get_core_num();


	__this_cpu_ग_लिखो(octeon_irq_ciu0_en_mirror, 0);
	__this_cpu_ग_लिखो(octeon_irq_ciu1_en_mirror, 0);
	wmb();
	raw_spin_lock_init(this_cpu_ptr(&octeon_irq_ciu_spinlock));
	/*
	 * Disable All CIU Interrupts. The ones we need will be
	 * enabled later.  Read the SUM रेजिस्टर so we know the ग_लिखो
	 * completed.
	 */
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0((coreid * 2)), 0);
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN0((coreid * 2 + 1)), 0);
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1((coreid * 2)), 0);
	cvmx_ग_लिखो_csr(CVMX_CIU_INTX_EN1((coreid * 2 + 1)), 0);
	cvmx_पढ़ो_csr(CVMX_CIU_INTX_SUM0((coreid * 2)));
पूर्ण

अटल व्योम octeon_irq_init_ciu2_percpu(व्योम)
अणु
	u64 regx, ipx;
	पूर्णांक coreid = cvmx_get_core_num();
	u64 base = CVMX_CIU2_EN_PPX_IP2_WRKQ(coreid);

	/*
	 * Disable All CIU2 Interrupts. The ones we need will be
	 * enabled later.  Read the SUM रेजिस्टर so we know the ग_लिखो
	 * completed.
	 *
	 * There are 9 रेजिस्टरs and 3 IPX levels with strides 0x1000
	 * and 0x200 respectivly.  Use loops to clear them.
	 */
	क्रम (regx = 0; regx <= 0x8000; regx += 0x1000) अणु
		क्रम (ipx = 0; ipx <= 0x400; ipx += 0x200)
			cvmx_ग_लिखो_csr(base + regx + ipx, 0);
	पूर्ण

	cvmx_पढ़ो_csr(CVMX_CIU2_SUM_PPX_IP2(coreid));
पूर्ण

अटल व्योम octeon_irq_setup_secondary_ciu(व्योम)
अणु
	octeon_irq_init_ciu_percpu();
	octeon_irq_percpu_enable();

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	अगर (octeon_irq_use_ip4)
		set_c0_status(STATUSF_IP4);
	अन्यथा
		clear_c0_status(STATUSF_IP4);
पूर्ण

अटल व्योम octeon_irq_setup_secondary_ciu2(व्योम)
अणु
	octeon_irq_init_ciu2_percpu();
	octeon_irq_percpu_enable();

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	अगर (octeon_irq_use_ip4)
		set_c0_status(STATUSF_IP4);
	अन्यथा
		clear_c0_status(STATUSF_IP4);
पूर्ण

अटल पूर्णांक __init octeon_irq_init_ciu(
	काष्ठा device_node *ciu_node, काष्ठा device_node *parent)
अणु
	पूर्णांक i, r;
	काष्ठा irq_chip *chip;
	काष्ठा irq_chip *chip_edge;
	काष्ठा irq_chip *chip_mbox;
	काष्ठा irq_chip *chip_wd;
	काष्ठा irq_करोमुख्य *ciu_करोमुख्य = शून्य;
	काष्ठा octeon_irq_ciu_करोमुख्य_data *dd;

	dd = kzalloc(माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	octeon_irq_init_ciu_percpu();
	octeon_irq_setup_secondary = octeon_irq_setup_secondary_ciu;

	octeon_irq_ip2 = octeon_irq_ip2_ciu;
	octeon_irq_ip3 = octeon_irq_ip3_ciu;
	अगर ((OCTEON_IS_OCTEON2() || OCTEON_IS_OCTEON3())
		&& !OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		octeon_irq_ip4 =  octeon_irq_ip4_ciu;
		dd->num_sum = 3;
		octeon_irq_use_ip4 = true;
	पूर्ण अन्यथा अणु
		octeon_irq_ip4 = octeon_irq_ip4_mask;
		dd->num_sum = 2;
		octeon_irq_use_ip4 = false;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN58XX_PASS2_X) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS2_X) ||
	    OCTEON_IS_MODEL(OCTEON_CN52XX_PASS2_X) ||
	    OCTEON_IS_OCTEON2() || OCTEON_IS_OCTEON3()) अणु
		chip = &octeon_irq_chip_ciu_v2;
		chip_edge = &octeon_irq_chip_ciu_v2_edge;
		chip_mbox = &octeon_irq_chip_ciu_mbox_v2;
		chip_wd = &octeon_irq_chip_ciu_wd_v2;
		octeon_irq_gpio_chip = &octeon_irq_chip_ciu_gpio_v2;
	पूर्ण अन्यथा अणु
		chip = &octeon_irq_chip_ciu;
		chip_edge = &octeon_irq_chip_ciu_edge;
		chip_mbox = &octeon_irq_chip_ciu_mbox;
		chip_wd = &octeon_irq_chip_ciu_wd;
		octeon_irq_gpio_chip = &octeon_irq_chip_ciu_gpio;
	पूर्ण
	octeon_irq_ciu_chip = chip;
	octeon_irq_ciu_chip_edge = chip_edge;

	/* Mips पूर्णांकernal */
	octeon_irq_init_core();

	ciu_करोमुख्य = irq_करोमुख्य_add_tree(
		ciu_node, &octeon_irq_करोमुख्य_ciu_ops, dd);
	irq_set_शेष_host(ciu_करोमुख्य);

	/* CIU_0 */
	क्रम (i = 0; i < 16; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_WORKQ0, 0, i + 0);
		अगर (r)
			जाओ err;
	पूर्ण

	r = irq_alloc_desc_at(OCTEON_IRQ_MBOX0, -1);
	अगर (r < 0) अणु
		pr_err("Failed to allocate desc for %s\n", "OCTEON_IRQ_MBOX0");
		जाओ err;
	पूर्ण
	r = octeon_irq_set_ciu_mapping(
		OCTEON_IRQ_MBOX0, 0, 32, 0, chip_mbox, handle_percpu_irq);
	अगर (r)
		जाओ err;
	r = irq_alloc_desc_at(OCTEON_IRQ_MBOX1, -1);
	अगर (r < 0) अणु
		pr_err("Failed to allocate desc for %s\n", "OCTEON_IRQ_MBOX1");
		जाओ err;
	पूर्ण
	r = octeon_irq_set_ciu_mapping(
		OCTEON_IRQ_MBOX1, 0, 33, 0, chip_mbox, handle_percpu_irq);
	अगर (r)
		जाओ err;

	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_PCI_INT0, 0, i + 36);
		अगर (r)
			जाओ err;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_PCI_MSI0, 0, i + 40);
		अगर (r)
			जाओ err;
	पूर्ण

	r = octeon_irq_क्रमce_ciu_mapping(ciu_करोमुख्य, OCTEON_IRQ_TWSI, 0, 45);
	अगर (r)
		जाओ err;

	r = octeon_irq_क्रमce_ciu_mapping(ciu_करोमुख्य, OCTEON_IRQ_RML, 0, 46);
	अगर (r)
		जाओ err;

	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_TIMER0, 0, i + 52);
		अगर (r)
			जाओ err;
	पूर्ण

	r = octeon_irq_क्रमce_ciu_mapping(ciu_करोमुख्य, OCTEON_IRQ_TWSI2, 0, 59);
	अगर (r)
		जाओ err;

	r = irq_alloc_descs(OCTEON_IRQ_WDOG0, OCTEON_IRQ_WDOG0, 16, -1);
	अगर (r < 0) अणु
		pr_err("Failed to allocate desc for %s\n", "OCTEON_IRQ_WDOGx");
		जाओ err;
	पूर्ण
	/* CIU_1 */
	क्रम (i = 0; i < 16; i++) अणु
		r = octeon_irq_set_ciu_mapping(
			i + OCTEON_IRQ_WDOG0, 1, i + 0, 0, chip_wd,
			handle_level_irq);
		अगर (r)
			जाओ err;
	पूर्ण

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	अगर (octeon_irq_use_ip4)
		set_c0_status(STATUSF_IP4);
	अन्यथा
		clear_c0_status(STATUSF_IP4);

	वापस 0;
err:
	वापस r;
पूर्ण

अटल पूर्णांक __init octeon_irq_init_gpio(
	काष्ठा device_node *gpio_node, काष्ठा device_node *parent)
अणु
	काष्ठा octeon_irq_gpio_करोमुख्य_data *gpiod;
	u32 पूर्णांकerrupt_cells;
	अचिन्हित पूर्णांक base_hwirq;
	पूर्णांक r;

	r = of_property_पढ़ो_u32(parent, "#interrupt-cells", &पूर्णांकerrupt_cells);
	अगर (r)
		वापस r;

	अगर (पूर्णांकerrupt_cells == 1) अणु
		u32 v;

		r = of_property_पढ़ो_u32_index(gpio_node, "interrupts", 0, &v);
		अगर (r) अणु
			pr_warn("No \"interrupts\" property.\n");
			वापस r;
		पूर्ण
		base_hwirq = v;
	पूर्ण अन्यथा अगर (पूर्णांकerrupt_cells == 2) अणु
		u32 v0, v1;

		r = of_property_पढ़ो_u32_index(gpio_node, "interrupts", 0, &v0);
		अगर (r) अणु
			pr_warn("No \"interrupts\" property.\n");
			वापस r;
		पूर्ण
		r = of_property_पढ़ो_u32_index(gpio_node, "interrupts", 1, &v1);
		अगर (r) अणु
			pr_warn("No \"interrupts\" property.\n");
			वापस r;
		पूर्ण
		base_hwirq = (v0 << 6) | v1;
	पूर्ण अन्यथा अणु
		pr_warn("Bad \"#interrupt-cells\" property: %u\n",
			पूर्णांकerrupt_cells);
		वापस -EINVAL;
	पूर्ण

	gpiod = kzalloc(माप(*gpiod), GFP_KERNEL);
	अगर (gpiod) अणु
		/* gpio करोमुख्य host_data is the base hwirq number. */
		gpiod->base_hwirq = base_hwirq;
		irq_करोमुख्य_add_linear(
			gpio_node, 16, &octeon_irq_करोमुख्य_gpio_ops, gpiod);
	पूर्ण अन्यथा अणु
		pr_warn("Cannot allocate memory for GPIO irq_domain.\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Clear the OF_POPULATED flag that was set by of_irq_init()
	 * so that all GPIO devices will be probed.
	 */
	of_node_clear_flag(gpio_node, OF_POPULATED);

	वापस 0;
पूर्ण
/*
 * Watchकरोg पूर्णांकerrupts are special.  They are associated with a single
 * core, so we hardwire the affinity to that core.
 */
अटल व्योम octeon_irq_ciu2_wd_enable(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = data->irq - OCTEON_IRQ_WDOG0;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(coreid) +
		(0x1000ull * cd->line);
	cvmx_ग_लिखो_csr(en_addr, mask);

पूर्ण

अटल व्योम octeon_irq_ciu2_enable(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक cpu = next_cpu_क्रम_irq(data);
	पूर्णांक coreid = octeon_coreid_क्रम_cpu(cpu);
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(coreid) +
		(0x1000ull * cd->line);
	cvmx_ग_लिखो_csr(en_addr, mask);
पूर्ण

अटल व्योम octeon_irq_ciu2_enable_local(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = cvmx_get_core_num();
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(coreid) +
		(0x1000ull * cd->line);
	cvmx_ग_लिखो_csr(en_addr, mask);

पूर्ण

अटल व्योम octeon_irq_ciu2_disable_local(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = cvmx_get_core_num();
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C(coreid) +
		(0x1000ull * cd->line);
	cvmx_ग_लिखो_csr(en_addr, mask);

पूर्ण

अटल व्योम octeon_irq_ciu2_ack(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = cvmx_get_core_num();
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	en_addr = CVMX_CIU2_RAW_PPX_IP2_WRKQ(coreid) + (0x1000ull * cd->line);
	cvmx_ग_लिखो_csr(en_addr, mask);

पूर्ण

अटल व्योम octeon_irq_ciu2_disable_all(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << (cd->bit);

	क्रम_each_online_cpu(cpu) अणु
		u64 en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C(
			octeon_coreid_क्रम_cpu(cpu)) + (0x1000ull * cd->line);
		cvmx_ग_लिखो_csr(en_addr, mask);
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ciu2_mbox_enable_all(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	u64 mask;

	mask = 1ull << (data->irq - OCTEON_IRQ_MBOX0);

	क्रम_each_online_cpu(cpu) अणु
		u64 en_addr = CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(
			octeon_coreid_क्रम_cpu(cpu));
		cvmx_ग_लिखो_csr(en_addr, mask);
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ciu2_mbox_disable_all(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	u64 mask;

	mask = 1ull << (data->irq - OCTEON_IRQ_MBOX0);

	क्रम_each_online_cpu(cpu) अणु
		u64 en_addr = CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(
			octeon_coreid_क्रम_cpu(cpu));
		cvmx_ग_लिखो_csr(en_addr, mask);
	पूर्ण
पूर्ण

अटल व्योम octeon_irq_ciu2_mbox_enable_local(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = cvmx_get_core_num();

	mask = 1ull << (data->irq - OCTEON_IRQ_MBOX0);
	en_addr = CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(coreid);
	cvmx_ग_लिखो_csr(en_addr, mask);
पूर्ण

अटल व्योम octeon_irq_ciu2_mbox_disable_local(काष्ठा irq_data *data)
अणु
	u64 mask;
	u64 en_addr;
	पूर्णांक coreid = cvmx_get_core_num();

	mask = 1ull << (data->irq - OCTEON_IRQ_MBOX0);
	en_addr = CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(coreid);
	cvmx_ग_लिखो_csr(en_addr, mask);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक octeon_irq_ciu2_set_affinity(काष्ठा irq_data *data,
					स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	पूर्णांक cpu;
	bool enable_one = !irqd_irq_disabled(data) && !irqd_irq_masked(data);
	u64 mask;
	काष्ठा octeon_ciu_chip_data *cd;

	अगर (!enable_one)
		वापस 0;

	cd = irq_data_get_irq_chip_data(data);
	mask = 1ull << cd->bit;

	क्रम_each_online_cpu(cpu) अणु
		u64 en_addr;
		अगर (cpumask_test_cpu(cpu, dest) && enable_one) अणु
			enable_one = false;
			en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(
				octeon_coreid_क्रम_cpu(cpu)) +
				(0x1000ull * cd->line);
		पूर्ण अन्यथा अणु
			en_addr = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C(
				octeon_coreid_क्रम_cpu(cpu)) +
				(0x1000ull * cd->line);
		पूर्ण
		cvmx_ग_लिखो_csr(en_addr, mask);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम octeon_irq_ciu2_enable_gpio(काष्ठा irq_data *data)
अणु
	octeon_irq_gpio_setup(data);
	octeon_irq_ciu2_enable(data);
पूर्ण

अटल व्योम octeon_irq_ciu2_disable_gpio(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);

	cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(cd->gpio_line), 0);

	octeon_irq_ciu2_disable_all(data);
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_ciu2 = अणु
	.name = "CIU2-E",
	.irq_enable = octeon_irq_ciu2_enable,
	.irq_disable = octeon_irq_ciu2_disable_all,
	.irq_mask = octeon_irq_ciu2_disable_local,
	.irq_unmask = octeon_irq_ciu2_enable,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu2_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu2_edge = अणु
	.name = "CIU2-E",
	.irq_enable = octeon_irq_ciu2_enable,
	.irq_disable = octeon_irq_ciu2_disable_all,
	.irq_ack = octeon_irq_ciu2_ack,
	.irq_mask = octeon_irq_ciu2_disable_local,
	.irq_unmask = octeon_irq_ciu2_enable,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu2_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu2_mbox = अणु
	.name = "CIU2-M",
	.irq_enable = octeon_irq_ciu2_mbox_enable_all,
	.irq_disable = octeon_irq_ciu2_mbox_disable_all,
	.irq_ack = octeon_irq_ciu2_mbox_disable_local,
	.irq_eoi = octeon_irq_ciu2_mbox_enable_local,

	.irq_cpu_online = octeon_irq_ciu2_mbox_enable_local,
	.irq_cpu_offline = octeon_irq_ciu2_mbox_disable_local,
	.flags = IRQCHIP_ONOFFLINE_ENABLED,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu2_wd = अणु
	.name = "CIU2-W",
	.irq_enable = octeon_irq_ciu2_wd_enable,
	.irq_disable = octeon_irq_ciu2_disable_all,
	.irq_mask = octeon_irq_ciu2_disable_local,
	.irq_unmask = octeon_irq_ciu2_enable_local,
पूर्ण;

अटल काष्ठा irq_chip octeon_irq_chip_ciu2_gpio = अणु
	.name = "CIU-GPIO",
	.irq_enable = octeon_irq_ciu2_enable_gpio,
	.irq_disable = octeon_irq_ciu2_disable_gpio,
	.irq_ack = octeon_irq_ciu_gpio_ack,
	.irq_mask = octeon_irq_ciu2_disable_local,
	.irq_unmask = octeon_irq_ciu2_enable,
	.irq_set_type = octeon_irq_ciu_gpio_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu2_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
	.flags = IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल पूर्णांक octeon_irq_ciu2_xlat(काष्ठा irq_करोमुख्य *d,
				काष्ठा device_node *node,
				स्थिर u32 *पूर्णांकspec,
				अचिन्हित पूर्णांक पूर्णांकsize,
				अचिन्हित दीर्घ *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	अचिन्हित पूर्णांक ciu, bit;

	ciu = पूर्णांकspec[0];
	bit = पूर्णांकspec[1];

	*out_hwirq = (ciu << 6) | bit;
	*out_type = 0;

	वापस 0;
पूर्ण

अटल bool octeon_irq_ciu2_is_edge(अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक bit)
अणु
	bool edge = false;

	अगर (line == 3) /* MIO */
		चयन (bit) अणु
		हाल 2:	 /* IPD_DRP */
		हाल 8 ... 11: /* Timers */
		हाल 48: /* PTP */
			edge = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	अन्यथा अगर (line == 6) /* PKT */
		चयन (bit) अणु
		हाल 52 ... 53: /* ILK_DRP */
		हाल 8 ... 12:	/* GMX_DRP */
			edge = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	वापस edge;
पूर्ण

अटल पूर्णांक octeon_irq_ciu2_map(काष्ठा irq_करोमुख्य *d,
			       अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	अचिन्हित पूर्णांक line = hw >> 6;
	अचिन्हित पूर्णांक bit = hw & 63;

	/*
	 * Don't map irq अगर it is reserved क्रम GPIO.
	 * (Line 7 are the GPIO lines.)
	 */
	अगर (line == 7)
		वापस 0;

	अगर (line > 7 || octeon_irq_ciu_to_irq[line][bit] != 0)
		वापस -EINVAL;

	अगर (octeon_irq_ciu2_is_edge(line, bit))
		octeon_irq_set_ciu_mapping(virq, line, bit, 0,
					   &octeon_irq_chip_ciu2_edge,
					   handle_edge_irq);
	अन्यथा
		octeon_irq_set_ciu_mapping(virq, line, bit, 0,
					   &octeon_irq_chip_ciu2,
					   handle_level_irq);

	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops octeon_irq_करोमुख्य_ciu2_ops = अणु
	.map = octeon_irq_ciu2_map,
	.unmap = octeon_irq_मुक्त_cd,
	.xlate = octeon_irq_ciu2_xlat,
पूर्ण;

अटल व्योम octeon_irq_ciu2(व्योम)
अणु
	पूर्णांक line;
	पूर्णांक bit;
	पूर्णांक irq;
	u64 src_reg, src, sum;
	स्थिर अचिन्हित दीर्घ core_id = cvmx_get_core_num();

	sum = cvmx_पढ़ो_csr(CVMX_CIU2_SUM_PPX_IP2(core_id)) & 0xfful;

	अगर (unlikely(!sum))
		जाओ spurious;

	line = fls64(sum) - 1;
	src_reg = CVMX_CIU2_SRC_PPX_IP2_WRKQ(core_id) + (0x1000 * line);
	src = cvmx_पढ़ो_csr(src_reg);

	अगर (unlikely(!src))
		जाओ spurious;

	bit = fls64(src) - 1;
	irq = octeon_irq_ciu_to_irq[line][bit];
	अगर (unlikely(!irq))
		जाओ spurious;

	करो_IRQ(irq);
	जाओ out;

spurious:
	spurious_पूर्णांकerrupt();
out:
	/* CN68XX pass 1.x has an errata that accessing the ACK रेजिस्टरs
		can stop पूर्णांकerrupts from propagating */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		cvmx_पढ़ो_csr(CVMX_CIU2_INTR_CIU_READY);
	अन्यथा
		cvmx_पढ़ो_csr(CVMX_CIU2_ACK_PPX_IP2(core_id));
	वापस;
पूर्ण

अटल व्योम octeon_irq_ciu2_mbox(व्योम)
अणु
	पूर्णांक line;

	स्थिर अचिन्हित दीर्घ core_id = cvmx_get_core_num();
	u64 sum = cvmx_पढ़ो_csr(CVMX_CIU2_SUM_PPX_IP3(core_id)) >> 60;

	अगर (unlikely(!sum))
		जाओ spurious;

	line = fls64(sum) - 1;

	करो_IRQ(OCTEON_IRQ_MBOX0 + line);
	जाओ out;

spurious:
	spurious_पूर्णांकerrupt();
out:
	/* CN68XX pass 1.x has an errata that accessing the ACK रेजिस्टरs
		can stop पूर्णांकerrupts from propagating */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		cvmx_पढ़ो_csr(CVMX_CIU2_INTR_CIU_READY);
	अन्यथा
		cvmx_पढ़ो_csr(CVMX_CIU2_ACK_PPX_IP3(core_id));
	वापस;
पूर्ण

अटल पूर्णांक __init octeon_irq_init_ciu2(
	काष्ठा device_node *ciu_node, काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक i, r;
	काष्ठा irq_करोमुख्य *ciu_करोमुख्य = शून्य;

	octeon_irq_init_ciu2_percpu();
	octeon_irq_setup_secondary = octeon_irq_setup_secondary_ciu2;

	octeon_irq_gpio_chip = &octeon_irq_chip_ciu2_gpio;
	octeon_irq_ip2 = octeon_irq_ciu2;
	octeon_irq_ip3 = octeon_irq_ciu2_mbox;
	octeon_irq_ip4 = octeon_irq_ip4_mask;

	/* Mips पूर्णांकernal */
	octeon_irq_init_core();

	ciu_करोमुख्य = irq_करोमुख्य_add_tree(
		ciu_node, &octeon_irq_करोमुख्य_ciu2_ops, शून्य);
	irq_set_शेष_host(ciu_करोमुख्य);

	/* CUI2 */
	क्रम (i = 0; i < 64; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_WORKQ0, 0, i);
		अगर (r)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < 32; i++) अणु
		r = octeon_irq_set_ciu_mapping(i + OCTEON_IRQ_WDOG0, 1, i, 0,
			&octeon_irq_chip_ciu2_wd, handle_level_irq);
		अगर (r)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_TIMER0, 3, i + 8);
		अगर (r)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_PCI_INT0, 4, i);
		अगर (r)
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		r = octeon_irq_क्रमce_ciu_mapping(
			ciu_करोमुख्य, i + OCTEON_IRQ_PCI_MSI0, 4, i + 8);
		अगर (r)
			जाओ err;
	पूर्ण

	irq_set_chip_and_handler(OCTEON_IRQ_MBOX0, &octeon_irq_chip_ciu2_mbox, handle_percpu_irq);
	irq_set_chip_and_handler(OCTEON_IRQ_MBOX1, &octeon_irq_chip_ciu2_mbox, handle_percpu_irq);
	irq_set_chip_and_handler(OCTEON_IRQ_MBOX2, &octeon_irq_chip_ciu2_mbox, handle_percpu_irq);
	irq_set_chip_and_handler(OCTEON_IRQ_MBOX3, &octeon_irq_chip_ciu2_mbox, handle_percpu_irq);

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	clear_c0_status(STATUSF_IP4);
	वापस 0;
err:
	वापस r;
पूर्ण

काष्ठा octeon_irq_cib_host_data अणु
	raw_spinlock_t lock;
	u64 raw_reg;
	u64 en_reg;
	पूर्णांक max_bits;
पूर्ण;

काष्ठा octeon_irq_cib_chip_data अणु
	काष्ठा octeon_irq_cib_host_data *host_data;
	पूर्णांक bit;
पूर्ण;

अटल व्योम octeon_irq_cib_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	u64 en;
	काष्ठा octeon_irq_cib_chip_data *cd = irq_data_get_irq_chip_data(data);
	काष्ठा octeon_irq_cib_host_data *host_data = cd->host_data;

	raw_spin_lock_irqsave(&host_data->lock, flags);
	en = cvmx_पढ़ो_csr(host_data->en_reg);
	en |= 1ull << cd->bit;
	cvmx_ग_लिखो_csr(host_data->en_reg, en);
	raw_spin_unlock_irqrestore(&host_data->lock, flags);
पूर्ण

अटल व्योम octeon_irq_cib_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	u64 en;
	काष्ठा octeon_irq_cib_chip_data *cd = irq_data_get_irq_chip_data(data);
	काष्ठा octeon_irq_cib_host_data *host_data = cd->host_data;

	raw_spin_lock_irqsave(&host_data->lock, flags);
	en = cvmx_पढ़ो_csr(host_data->en_reg);
	en &= ~(1ull << cd->bit);
	cvmx_ग_लिखो_csr(host_data->en_reg, en);
	raw_spin_unlock_irqrestore(&host_data->lock, flags);
पूर्ण

अटल पूर्णांक octeon_irq_cib_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक t)
अणु
	irqd_set_trigger_type(data, t);
	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_cib = अणु
	.name = "CIB",
	.irq_enable = octeon_irq_cib_enable,
	.irq_disable = octeon_irq_cib_disable,
	.irq_mask = octeon_irq_cib_disable,
	.irq_unmask = octeon_irq_cib_enable,
	.irq_set_type = octeon_irq_cib_set_type,
पूर्ण;

अटल पूर्णांक octeon_irq_cib_xlat(काष्ठा irq_करोमुख्य *d,
				   काष्ठा device_node *node,
				   स्थिर u32 *पूर्णांकspec,
				   अचिन्हित पूर्णांक पूर्णांकsize,
				   अचिन्हित दीर्घ *out_hwirq,
				   अचिन्हित पूर्णांक *out_type)
अणु
	अचिन्हित पूर्णांक type = 0;

	अगर (पूर्णांकsize == 2)
		type = पूर्णांकspec[1];

	चयन (type) अणु
	हाल 0: /* unofficial value, but we might as well let it work. */
	हाल 4: /* official value क्रम level triggering. */
		*out_type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल 1: /* official value क्रम edge triggering. */
		*out_type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	शेष: /* Nothing अन्यथा is acceptable. */
		वापस -EINVAL;
	पूर्ण

	*out_hwirq = पूर्णांकspec[0];

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_irq_cib_map(काष्ठा irq_करोमुख्य *d,
			      अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	काष्ठा octeon_irq_cib_host_data *host_data = d->host_data;
	काष्ठा octeon_irq_cib_chip_data *cd;

	अगर (hw >= host_data->max_bits) अणु
		pr_err("ERROR: %s mapping %u is too big!\n",
		       irq_करोमुख्य_get_of_node(d)->name, (अचिन्हित)hw);
		वापस -EINVAL;
	पूर्ण

	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;

	cd->host_data = host_data;
	cd->bit = hw;

	irq_set_chip_and_handler(virq, &octeon_irq_chip_cib,
				 handle_simple_irq);
	irq_set_chip_data(virq, cd);
	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops octeon_irq_करोमुख्य_cib_ops = अणु
	.map = octeon_irq_cib_map,
	.unmap = octeon_irq_मुक्त_cd,
	.xlate = octeon_irq_cib_xlat,
पूर्ण;

/* Chain to real handler. */
अटल irqवापस_t octeon_irq_cib_handler(पूर्णांक my_irq, व्योम *data)
अणु
	u64 en;
	u64 raw;
	u64 bits;
	पूर्णांक i;
	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *cib_करोमुख्य = data;
	काष्ठा octeon_irq_cib_host_data *host_data = cib_करोमुख्य->host_data;

	en = cvmx_पढ़ो_csr(host_data->en_reg);
	raw = cvmx_पढ़ो_csr(host_data->raw_reg);

	bits = en & raw;

	क्रम (i = 0; i < host_data->max_bits; i++) अणु
		अगर ((bits & 1ull << i) == 0)
			जारी;
		irq = irq_find_mapping(cib_करोमुख्य, i);
		अगर (!irq) अणु
			अचिन्हित दीर्घ flags;

			pr_err("ERROR: CIB bit %d@%llx IRQ unhandled, disabling\n",
				i, host_data->raw_reg);
			raw_spin_lock_irqsave(&host_data->lock, flags);
			en = cvmx_पढ़ो_csr(host_data->en_reg);
			en &= ~(1ull << i);
			cvmx_ग_लिखो_csr(host_data->en_reg, en);
			cvmx_ग_लिखो_csr(host_data->raw_reg, 1ull << i);
			raw_spin_unlock_irqrestore(&host_data->lock, flags);
		पूर्ण अन्यथा अणु
			काष्ठा irq_desc *desc = irq_to_desc(irq);
			काष्ठा irq_data *irq_data = irq_desc_get_irq_data(desc);
			/* If edge, acknowledge the bit we will be sending. */
			अगर (irqd_get_trigger_type(irq_data) &
				IRQ_TYPE_EDGE_BOTH)
				cvmx_ग_लिखो_csr(host_data->raw_reg, 1ull << i);
			generic_handle_irq_desc(desc);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init octeon_irq_init_cib(काष्ठा device_node *ciu_node,
				      काष्ठा device_node *parent)
अणु
	स्थिर __be32 *addr;
	u32 val;
	काष्ठा octeon_irq_cib_host_data *host_data;
	पूर्णांक parent_irq;
	पूर्णांक r;
	काष्ठा irq_करोमुख्य *cib_करोमुख्य;

	parent_irq = irq_of_parse_and_map(ciu_node, 0);
	अगर (!parent_irq) अणु
		pr_err("ERROR: Couldn't acquire parent_irq for %pOFn\n",
			ciu_node);
		वापस -EINVAL;
	पूर्ण

	host_data = kzalloc(माप(*host_data), GFP_KERNEL);
	अगर (!host_data)
		वापस -ENOMEM;
	raw_spin_lock_init(&host_data->lock);

	addr = of_get_address(ciu_node, 0, शून्य, शून्य);
	अगर (!addr) अणु
		pr_err("ERROR: Couldn't acquire reg(0) %pOFn\n", ciu_node);
		वापस -EINVAL;
	पूर्ण
	host_data->raw_reg = (u64)phys_to_virt(
		of_translate_address(ciu_node, addr));

	addr = of_get_address(ciu_node, 1, शून्य, शून्य);
	अगर (!addr) अणु
		pr_err("ERROR: Couldn't acquire reg(1) %pOFn\n", ciu_node);
		वापस -EINVAL;
	पूर्ण
	host_data->en_reg = (u64)phys_to_virt(
		of_translate_address(ciu_node, addr));

	r = of_property_पढ़ो_u32(ciu_node, "cavium,max-bits", &val);
	अगर (r) अणु
		pr_err("ERROR: Couldn't read cavium,max-bits from %pOFn\n",
			ciu_node);
		वापस r;
	पूर्ण
	host_data->max_bits = val;

	cib_करोमुख्य = irq_करोमुख्य_add_linear(ciu_node, host_data->max_bits,
					   &octeon_irq_करोमुख्य_cib_ops,
					   host_data);
	अगर (!cib_करोमुख्य) अणु
		pr_err("ERROR: Couldn't irq_domain_add_linear()\n");
		वापस -ENOMEM;
	पूर्ण

	cvmx_ग_लिखो_csr(host_data->en_reg, 0); /* disable all IRQs */
	cvmx_ग_लिखो_csr(host_data->raw_reg, ~0); /* ack any outstanding */

	r = request_irq(parent_irq, octeon_irq_cib_handler,
			IRQF_NO_THREAD, "cib", cib_करोमुख्य);
	अगर (r) अणु
		pr_err("request_irq cib failed %d\n", r);
		वापस r;
	पूर्ण
	pr_info("CIB interrupt controller probed: %llx %d\n",
		host_data->raw_reg, host_data->max_bits);
	वापस 0;
पूर्ण

पूर्णांक octeon_irq_ciu3_xlat(काष्ठा irq_करोमुख्य *d,
			 काष्ठा device_node *node,
			 स्थिर u32 *पूर्णांकspec,
			 अचिन्हित पूर्णांक पूर्णांकsize,
			 अचिन्हित दीर्घ *out_hwirq,
			 अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info = d->host_data;
	अचिन्हित पूर्णांक hwirq, type, पूर्णांकsn_major;
	जोड़ cvmx_ciu3_iscx_ctl isc;

	अगर (पूर्णांकsize < 2)
		वापस -EINVAL;
	hwirq = पूर्णांकspec[0];
	type = पूर्णांकspec[1];

	अगर (hwirq >= (1 << 20))
		वापस -EINVAL;

	पूर्णांकsn_major = hwirq >> 12;
	चयन (पूर्णांकsn_major) अणु
	हाल 0x04: /* Software handled separately. */
		वापस -EINVAL;
	शेष:
		अवरोध;
	पूर्ण

	isc.u64 =  cvmx_पढ़ो_csr(ciu3_info->ciu3_addr + CIU3_ISC_CTL(hwirq));
	अगर (!isc.s.imp)
		वापस -EINVAL;

	चयन (type) अणु
	हाल 4: /* official value क्रम level triggering. */
		*out_type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल 0: /* unofficial value, but we might as well let it work. */
	हाल 1: /* official value क्रम edge triggering. */
		*out_type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	शेष: /* Nothing अन्यथा is acceptable. */
		वापस -EINVAL;
	पूर्ण

	*out_hwirq = hwirq;

	वापस 0;
पूर्ण

व्योम octeon_irq_ciu3_enable(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	जोड़ cvmx_ciu3_iscx_ctl isc_ctl;
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_ctl_addr;

	काष्ठा octeon_ciu_chip_data *cd;

	cpu = next_cpu_क्रम_irq(data);

	cd = irq_data_get_irq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;
	cvmx_ग_लिखो_csr(cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn), isc_w1c.u64);

	isc_ctl_addr = cd->ciu3_addr + CIU3_ISC_CTL(cd->पूर्णांकsn);
	isc_ctl.u64 = 0;
	isc_ctl.s.en = 1;
	isc_ctl.s.idt = per_cpu(octeon_irq_ciu3_idt_ip2, cpu);
	cvmx_ग_लिखो_csr(isc_ctl_addr, isc_ctl.u64);
	cvmx_पढ़ो_csr(isc_ctl_addr);
पूर्ण

व्योम octeon_irq_ciu3_disable(काष्ठा irq_data *data)
अणु
	u64 isc_ctl_addr;
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;

	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	isc_ctl_addr = cd->ciu3_addr + CIU3_ISC_CTL(cd->पूर्णांकsn);
	cvmx_ग_लिखो_csr(cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn), isc_w1c.u64);
	cvmx_ग_लिखो_csr(isc_ctl_addr, 0);
	cvmx_पढ़ो_csr(isc_ctl_addr);
पूर्ण

व्योम octeon_irq_ciu3_ack(काष्ठा irq_data *data)
अणु
	u64 isc_w1c_addr;
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	काष्ठा octeon_ciu_chip_data *cd;
	u32 trigger_type = irqd_get_trigger_type(data);

	/*
	 * We use a single irq_chip, so we have to करो nothing to ack a
	 * level पूर्णांकerrupt.
	 */
	अगर (!(trigger_type & IRQ_TYPE_EDGE_BOTH))
		वापस;

	cd = irq_data_get_irq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.raw = 1;

	isc_w1c_addr = cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn);
	cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
	cvmx_पढ़ो_csr(isc_w1c_addr);
पूर्ण

व्योम octeon_irq_ciu3_mask(काष्ठा irq_data *data)
अणु
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_w1c_addr;
	काष्ठा octeon_ciu_chip_data *cd;

	cd = irq_data_get_irq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	isc_w1c_addr = cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn);
	cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
	cvmx_पढ़ो_csr(isc_w1c_addr);
पूर्ण

व्योम octeon_irq_ciu3_mask_ack(काष्ठा irq_data *data)
अणु
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_w1c_addr;
	काष्ठा octeon_ciu_chip_data *cd;
	u32 trigger_type = irqd_get_trigger_type(data);

	cd = irq_data_get_irq_chip_data(data);

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;

	/*
	 * We use a single irq_chip, so only ack an edge (!level)
	 * पूर्णांकerrupt.
	 */
	अगर (trigger_type & IRQ_TYPE_EDGE_BOTH)
		isc_w1c.s.raw = 1;

	isc_w1c_addr = cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn);
	cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
	cvmx_पढ़ो_csr(isc_w1c_addr);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक octeon_irq_ciu3_set_affinity(काष्ठा irq_data *data,
					स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	जोड़ cvmx_ciu3_iscx_ctl isc_ctl;
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	u64 isc_ctl_addr;
	पूर्णांक cpu;
	bool enable_one = !irqd_irq_disabled(data) && !irqd_irq_masked(data);
	काष्ठा octeon_ciu_chip_data *cd = irq_data_get_irq_chip_data(data);

	अगर (!cpumask_subset(dest, cpumask_of_node(cd->ciu_node)))
		वापस -EINVAL;

	अगर (!enable_one)
		वापस IRQ_SET_MASK_OK;

	cd = irq_data_get_irq_chip_data(data);
	cpu = cpumask_first(dest);
	अगर (cpu >= nr_cpu_ids)
		cpu = smp_processor_id();
	cd->current_cpu = cpu;

	isc_w1c.u64 = 0;
	isc_w1c.s.en = 1;
	cvmx_ग_लिखो_csr(cd->ciu3_addr + CIU3_ISC_W1C(cd->पूर्णांकsn), isc_w1c.u64);

	isc_ctl_addr = cd->ciu3_addr + CIU3_ISC_CTL(cd->पूर्णांकsn);
	isc_ctl.u64 = 0;
	isc_ctl.s.en = 1;
	isc_ctl.s.idt = per_cpu(octeon_irq_ciu3_idt_ip2, cpu);
	cvmx_ग_लिखो_csr(isc_ctl_addr, isc_ctl.u64);
	cvmx_पढ़ो_csr(isc_ctl_addr);

	वापस IRQ_SET_MASK_OK;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip octeon_irq_chip_ciu3 = अणु
	.name = "CIU3",
	.irq_startup = edge_startup,
	.irq_enable = octeon_irq_ciu3_enable,
	.irq_disable = octeon_irq_ciu3_disable,
	.irq_ack = octeon_irq_ciu3_ack,
	.irq_mask = octeon_irq_ciu3_mask,
	.irq_mask_ack = octeon_irq_ciu3_mask_ack,
	.irq_unmask = octeon_irq_ciu3_enable,
	.irq_set_type = octeon_irq_ciu_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = octeon_irq_ciu3_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#पूर्ण_अगर
पूर्ण;

पूर्णांक octeon_irq_ciu3_mapx(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw, काष्ठा irq_chip *chip)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info = d->host_data;
	काष्ठा octeon_ciu_chip_data *cd = kzalloc_node(माप(*cd), GFP_KERNEL,
						       ciu3_info->node);
	अगर (!cd)
		वापस -ENOMEM;
	cd->पूर्णांकsn = hw;
	cd->current_cpu = -1;
	cd->ciu3_addr = ciu3_info->ciu3_addr;
	cd->ciu_node = ciu3_info->node;
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);
	irq_set_chip_data(virq, cd);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_irq_ciu3_map(काष्ठा irq_करोमुख्य *d,
			       अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	वापस octeon_irq_ciu3_mapx(d, virq, hw, &octeon_irq_chip_ciu3);
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops octeon_dflt_करोमुख्य_ciu3_ops = अणु
	.map = octeon_irq_ciu3_map,
	.unmap = octeon_irq_मुक्त_cd,
	.xlate = octeon_irq_ciu3_xlat,
पूर्ण;

अटल व्योम octeon_irq_ciu3_ip2(व्योम)
अणु
	जोड़ cvmx_ciu3_destx_pp_पूर्णांक dest_pp_पूर्णांक;
	काष्ठा octeon_ciu3_info *ciu3_info;
	u64 ciu3_addr;

	ciu3_info = __this_cpu_पढ़ो(octeon_ciu3_info);
	ciu3_addr = ciu3_info->ciu3_addr;

	dest_pp_पूर्णांक.u64 = cvmx_पढ़ो_csr(ciu3_addr + CIU3_DEST_PP_INT(3 * cvmx_get_local_core_num()));

	अगर (likely(dest_pp_पूर्णांक.s.पूर्णांकr)) अणु
		irq_hw_number_t पूर्णांकsn = dest_pp_पूर्णांक.s.पूर्णांकsn;
		irq_hw_number_t hw;
		काष्ठा irq_करोमुख्य *करोमुख्य;
		/* Get the करोमुख्य to use from the major block */
		पूर्णांक block = पूर्णांकsn >> 12;
		पूर्णांक ret;

		करोमुख्य = ciu3_info->करोमुख्य[block];
		अगर (ciu3_info->पूर्णांकsn2hw[block])
			hw = ciu3_info->पूर्णांकsn2hw[block](करोमुख्य, पूर्णांकsn);
		अन्यथा
			hw = पूर्णांकsn;

		ret = handle_करोमुख्य_irq(करोमुख्य, hw, शून्य);
		अगर (ret < 0) अणु
			जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
			u64 isc_w1c_addr = ciu3_addr + CIU3_ISC_W1C(पूर्णांकsn);

			isc_w1c.u64 = 0;
			isc_w1c.s.en = 1;
			cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
			cvmx_पढ़ो_csr(isc_w1c_addr);
			spurious_पूर्णांकerrupt();
		पूर्ण
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

/*
 * 10 mbox per core starting from zero.
 * Base mbox is core * 10
 */
अटल अचिन्हित पूर्णांक octeon_irq_ciu3_base_mbox_पूर्णांकsn(पूर्णांक core)
अणु
	/* SW (mbox) are 0x04 in bits 12..19 */
	वापस 0x04000 + CIU3_MBOX_PER_CORE * core;
पूर्ण

अटल अचिन्हित पूर्णांक octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_core(पूर्णांक core, अचिन्हित पूर्णांक mbox)
अणु
	वापस octeon_irq_ciu3_base_mbox_पूर्णांकsn(core) + mbox;
पूर्ण

अटल अचिन्हित पूर्णांक octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_cpu(पूर्णांक cpu, अचिन्हित पूर्णांक mbox)
अणु
	पूर्णांक local_core = octeon_coreid_क्रम_cpu(cpu) & 0x3f;

	वापस octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_core(local_core, mbox);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox(व्योम)
अणु
	जोड़ cvmx_ciu3_destx_pp_पूर्णांक dest_pp_पूर्णांक;
	काष्ठा octeon_ciu3_info *ciu3_info;
	u64 ciu3_addr;
	पूर्णांक core = cvmx_get_local_core_num();

	ciu3_info = __this_cpu_पढ़ो(octeon_ciu3_info);
	ciu3_addr = ciu3_info->ciu3_addr;

	dest_pp_पूर्णांक.u64 = cvmx_पढ़ो_csr(ciu3_addr + CIU3_DEST_PP_INT(1 + 3 * core));

	अगर (likely(dest_pp_पूर्णांक.s.पूर्णांकr)) अणु
		irq_hw_number_t पूर्णांकsn = dest_pp_पूर्णांक.s.पूर्णांकsn;
		पूर्णांक mbox = पूर्णांकsn - octeon_irq_ciu3_base_mbox_पूर्णांकsn(core);

		अगर (likely(mbox >= 0 && mbox < CIU3_MBOX_PER_CORE)) अणु
			करो_IRQ(mbox + OCTEON_IRQ_MBOX0);
		पूर्ण अन्यथा अणु
			जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
			u64 isc_w1c_addr = ciu3_addr + CIU3_ISC_W1C(पूर्णांकsn);

			isc_w1c.u64 = 0;
			isc_w1c.s.en = 1;
			cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
			cvmx_पढ़ो_csr(isc_w1c_addr);
			spurious_पूर्णांकerrupt();
		पूर्ण
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

व्योम octeon_ciu3_mbox_send(पूर्णांक cpu, अचिन्हित पूर्णांक mbox)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info;
	अचिन्हित पूर्णांक पूर्णांकsn;
	जोड़ cvmx_ciu3_iscx_w1s isc_w1s;
	u64 isc_w1s_addr;

	अगर (WARN_ON_ONCE(mbox >= CIU3_MBOX_PER_CORE))
		वापस;

	पूर्णांकsn = octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_cpu(cpu, mbox);
	ciu3_info = per_cpu(octeon_ciu3_info, cpu);
	isc_w1s_addr = ciu3_info->ciu3_addr + CIU3_ISC_W1S(पूर्णांकsn);

	isc_w1s.u64 = 0;
	isc_w1s.s.raw = 1;

	cvmx_ग_लिखो_csr(isc_w1s_addr, isc_w1s.u64);
	cvmx_पढ़ो_csr(isc_w1s_addr);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_set_enable(काष्ठा irq_data *data, पूर्णांक cpu, bool en)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info;
	अचिन्हित पूर्णांक पूर्णांकsn;
	u64 isc_ctl_addr, isc_w1c_addr;
	जोड़ cvmx_ciu3_iscx_ctl isc_ctl;
	अचिन्हित पूर्णांक mbox = data->irq - OCTEON_IRQ_MBOX0;

	पूर्णांकsn = octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_cpu(cpu, mbox);
	ciu3_info = per_cpu(octeon_ciu3_info, cpu);
	isc_w1c_addr = ciu3_info->ciu3_addr + CIU3_ISC_W1C(पूर्णांकsn);
	isc_ctl_addr = ciu3_info->ciu3_addr + CIU3_ISC_CTL(पूर्णांकsn);

	isc_ctl.u64 = 0;
	isc_ctl.s.en = 1;

	cvmx_ग_लिखो_csr(isc_w1c_addr, isc_ctl.u64);
	cvmx_ग_लिखो_csr(isc_ctl_addr, 0);
	अगर (en) अणु
		अचिन्हित पूर्णांक idt = per_cpu(octeon_irq_ciu3_idt_ip3, cpu);

		isc_ctl.u64 = 0;
		isc_ctl.s.en = 1;
		isc_ctl.s.idt = idt;
		cvmx_ग_लिखो_csr(isc_ctl_addr, isc_ctl.u64);
	पूर्ण
	cvmx_पढ़ो_csr(isc_ctl_addr);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_enable(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	अचिन्हित पूर्णांक mbox = data->irq - OCTEON_IRQ_MBOX0;

	WARN_ON(mbox >= CIU3_MBOX_PER_CORE);

	क्रम_each_online_cpu(cpu)
		octeon_irq_ciu3_mbox_set_enable(data, cpu, true);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_disable(काष्ठा irq_data *data)
अणु
	पूर्णांक cpu;
	अचिन्हित पूर्णांक mbox = data->irq - OCTEON_IRQ_MBOX0;

	WARN_ON(mbox >= CIU3_MBOX_PER_CORE);

	क्रम_each_online_cpu(cpu)
		octeon_irq_ciu3_mbox_set_enable(data, cpu, false);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_ack(काष्ठा irq_data *data)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info;
	अचिन्हित पूर्णांक पूर्णांकsn;
	u64 isc_w1c_addr;
	जोड़ cvmx_ciu3_iscx_w1c isc_w1c;
	अचिन्हित पूर्णांक mbox = data->irq - OCTEON_IRQ_MBOX0;

	पूर्णांकsn = octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_core(cvmx_get_local_core_num(), mbox);

	isc_w1c.u64 = 0;
	isc_w1c.s.raw = 1;

	ciu3_info = __this_cpu_पढ़ो(octeon_ciu3_info);
	isc_w1c_addr = ciu3_info->ciu3_addr + CIU3_ISC_W1C(पूर्णांकsn);
	cvmx_ग_लिखो_csr(isc_w1c_addr, isc_w1c.u64);
	cvmx_पढ़ो_csr(isc_w1c_addr);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_cpu_online(काष्ठा irq_data *data)
अणु
	octeon_irq_ciu3_mbox_set_enable(data, smp_processor_id(), true);
पूर्ण

अटल व्योम octeon_irq_ciu3_mbox_cpu_offline(काष्ठा irq_data *data)
अणु
	octeon_irq_ciu3_mbox_set_enable(data, smp_processor_id(), false);
पूर्ण

अटल पूर्णांक octeon_irq_ciu3_alloc_resources(काष्ठा octeon_ciu3_info *ciu3_info)
अणु
	u64 b = ciu3_info->ciu3_addr;
	पूर्णांक idt_ip2, idt_ip3, idt_ip4;
	पूर्णांक unused_idt2;
	पूर्णांक core = cvmx_get_local_core_num();
	पूर्णांक i;

	__this_cpu_ग_लिखो(octeon_ciu3_info, ciu3_info);

	/*
	 * 4 idt per core starting from 1 because zero is reserved.
	 * Base idt per core is 4 * core + 1
	 */
	idt_ip2 = core * 4 + 1;
	idt_ip3 = core * 4 + 2;
	idt_ip4 = core * 4 + 3;
	unused_idt2 = core * 4 + 4;
	__this_cpu_ग_लिखो(octeon_irq_ciu3_idt_ip2, idt_ip2);
	__this_cpu_ग_लिखो(octeon_irq_ciu3_idt_ip3, idt_ip3);

	/* ip2 पूर्णांकerrupts क्रम this CPU */
	cvmx_ग_लिखो_csr(b + CIU3_IDT_CTL(idt_ip2), 0);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_PP(idt_ip2, 0), 1ull << core);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_IO(idt_ip2), 0);

	/* ip3 पूर्णांकerrupts क्रम this CPU */
	cvmx_ग_लिखो_csr(b + CIU3_IDT_CTL(idt_ip3), 1);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_PP(idt_ip3, 0), 1ull << core);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_IO(idt_ip3), 0);

	/* ip4 पूर्णांकerrupts क्रम this CPU */
	cvmx_ग_लिखो_csr(b + CIU3_IDT_CTL(idt_ip4), 2);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_PP(idt_ip4, 0), 0);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_IO(idt_ip4), 0);

	cvmx_ग_लिखो_csr(b + CIU3_IDT_CTL(unused_idt2), 0);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_PP(unused_idt2, 0), 0);
	cvmx_ग_लिखो_csr(b + CIU3_IDT_IO(unused_idt2), 0);

	क्रम (i = 0; i < CIU3_MBOX_PER_CORE; i++) अणु
		अचिन्हित पूर्णांक पूर्णांकsn = octeon_irq_ciu3_mbox_पूर्णांकsn_क्रम_core(core, i);

		cvmx_ग_लिखो_csr(b + CIU3_ISC_W1C(पूर्णांकsn), 2);
		cvmx_ग_लिखो_csr(b + CIU3_ISC_CTL(पूर्णांकsn), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम octeon_irq_setup_secondary_ciu3(व्योम)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info;

	ciu3_info = octeon_ciu3_info_per_node[cvmx_get_node_num()];
	octeon_irq_ciu3_alloc_resources(ciu3_info);
	irq_cpu_online();

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	अगर (octeon_irq_use_ip4)
		set_c0_status(STATUSF_IP4);
	अन्यथा
		clear_c0_status(STATUSF_IP4);
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_ciu3_mbox = अणु
	.name = "CIU3-M",
	.irq_enable = octeon_irq_ciu3_mbox_enable,
	.irq_disable = octeon_irq_ciu3_mbox_disable,
	.irq_ack = octeon_irq_ciu3_mbox_ack,

	.irq_cpu_online = octeon_irq_ciu3_mbox_cpu_online,
	.irq_cpu_offline = octeon_irq_ciu3_mbox_cpu_offline,
	.flags = IRQCHIP_ONOFFLINE_ENABLED,
पूर्ण;

अटल पूर्णांक __init octeon_irq_init_ciu3(काष्ठा device_node *ciu_node,
				       काष्ठा device_node *parent)
अणु
	पूर्णांक i;
	पूर्णांक node;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा octeon_ciu3_info *ciu3_info;
	स्थिर __be32 *zero_addr;
	u64 base_addr;
	जोड़ cvmx_ciu3_स्थिर स्थिरs;

	node = 0; /* of_node_to_nid(ciu_node); */
	ciu3_info = kzalloc_node(माप(*ciu3_info), GFP_KERNEL, node);

	अगर (!ciu3_info)
		वापस -ENOMEM;

	zero_addr = of_get_address(ciu_node, 0, शून्य, शून्य);
	अगर (WARN_ON(!zero_addr))
		वापस -EINVAL;

	base_addr = of_translate_address(ciu_node, zero_addr);
	base_addr = (u64)phys_to_virt(base_addr);

	ciu3_info->ciu3_addr = base_addr;
	ciu3_info->node = node;

	स्थिरs.u64 = cvmx_पढ़ो_csr(base_addr + CIU3_CONST);

	octeon_irq_setup_secondary = octeon_irq_setup_secondary_ciu3;

	octeon_irq_ip2 = octeon_irq_ciu3_ip2;
	octeon_irq_ip3 = octeon_irq_ciu3_mbox;
	octeon_irq_ip4 = octeon_irq_ip4_mask;

	अगर (node == cvmx_get_node_num()) अणु
		/* Mips पूर्णांकernal */
		octeon_irq_init_core();

		/* Only करो per CPU things अगर it is the CIU of the boot node. */
		i = irq_alloc_descs_from(OCTEON_IRQ_MBOX0, 8, node);
		WARN_ON(i < 0);

		क्रम (i = 0; i < 8; i++)
			irq_set_chip_and_handler(i + OCTEON_IRQ_MBOX0,
						 &octeon_irq_chip_ciu3_mbox, handle_percpu_irq);
	पूर्ण

	/*
	 * Initialize all करोमुख्यs to use the शेष करोमुख्य. Specअगरic major
	 * blocks will overग_लिखो the शेष करोमुख्य as needed.
	 */
	करोमुख्य = irq_करोमुख्य_add_tree(ciu_node, &octeon_dflt_करोमुख्य_ciu3_ops,
				     ciu3_info);
	क्रम (i = 0; i < MAX_CIU3_DOMAINS; i++)
		ciu3_info->करोमुख्य[i] = करोमुख्य;

	octeon_ciu3_info_per_node[node] = ciu3_info;

	अगर (node == cvmx_get_node_num()) अणु
		/* Only करो per CPU things अगर it is the CIU of the boot node. */
		octeon_irq_ciu3_alloc_resources(ciu3_info);
		अगर (node == 0)
			irq_set_शेष_host(करोमुख्य);

		octeon_irq_use_ip4 = false;
		/* Enable the CIU lines */
		set_c0_status(STATUSF_IP2 | STATUSF_IP3);
		clear_c0_status(STATUSF_IP4);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id ciu_types[] __initdata = अणु
	अणु.compatible = "cavium,octeon-3860-ciu", .data = octeon_irq_init_ciuपूर्ण,
	अणु.compatible = "cavium,octeon-3860-gpio", .data = octeon_irq_init_gpioपूर्ण,
	अणु.compatible = "cavium,octeon-6880-ciu2", .data = octeon_irq_init_ciu2पूर्ण,
	अणु.compatible = "cavium,octeon-7890-ciu3", .data = octeon_irq_init_ciu3पूर्ण,
	अणु.compatible = "cavium,octeon-7130-cib", .data = octeon_irq_init_cibपूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init arch_init_irq(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	/* Set the शेष affinity to the boot cpu. */
	cpumask_clear(irq_शेष_affinity);
	cpumask_set_cpu(smp_processor_id(), irq_शेष_affinity);
#पूर्ण_अगर
	of_irq_init(ciu_types);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित दीर्घ cop0_cause;
	अचिन्हित दीर्घ cop0_status;

	जबतक (1) अणु
		cop0_cause = पढ़ो_c0_cause();
		cop0_status = पढ़ो_c0_status();
		cop0_cause &= cop0_status;
		cop0_cause &= ST0_IM;

		अगर (cop0_cause & STATUSF_IP2)
			octeon_irq_ip2();
		अन्यथा अगर (cop0_cause & STATUSF_IP3)
			octeon_irq_ip3();
		अन्यथा अगर (cop0_cause & STATUSF_IP4)
			octeon_irq_ip4();
		अन्यथा अगर (cop0_cause)
			करो_IRQ(fls(cop0_cause) - 9 + MIPS_CPU_IRQ_BASE);
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

व्योम octeon_fixup_irqs(व्योम)
अणु
	irq_cpu_offline();
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

काष्ठा irq_करोमुख्य *octeon_irq_get_block_करोमुख्य(पूर्णांक node, uपूर्णांक8_t block)
अणु
	काष्ठा octeon_ciu3_info *ciu3_info;

	ciu3_info = octeon_ciu3_info_per_node[node & CVMX_NODE_MASK];
	वापस ciu3_info->करोमुख्य[block];
पूर्ण
EXPORT_SYMBOL(octeon_irq_get_block_करोमुख्य);
