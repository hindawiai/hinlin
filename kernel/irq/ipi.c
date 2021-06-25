<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Imagination Technologies Ltd
 * Author: Qais Yousef <qais.yousef@imgtec.com>
 *
 * This file contains driver APIs to the IPI subप्रणाली.
 */

#घोषणा pr_fmt(fmt) "genirq/ipi: " fmt

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>

/**
 * irq_reserve_ipi() - Setup an IPI to destination cpumask
 * @करोमुख्य:	IPI करोमुख्य
 * @dest:	cpumask of cpus which can receive the IPI
 *
 * Allocate a virq that can be used to send IPI to any CPU in dest mask.
 *
 * On success it'll वापस linux irq number and error code on failure
 */
पूर्णांक irq_reserve_ipi(काष्ठा irq_करोमुख्य *करोमुख्य,
			     स्थिर काष्ठा cpumask *dest)
अणु
	अचिन्हित पूर्णांक nr_irqs, offset;
	काष्ठा irq_data *data;
	पूर्णांक virq, i;

	अगर (!करोमुख्य ||!irq_करोमुख्य_is_ipi(करोमुख्य)) अणु
		pr_warn("Reservation on a non IPI domain\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cpumask_subset(dest, cpu_possible_mask)) अणु
		pr_warn("Reservation is not in possible_cpu_mask\n");
		वापस -EINVAL;
	पूर्ण

	nr_irqs = cpumask_weight(dest);
	अगर (!nr_irqs) अणु
		pr_warn("Reservation for empty destination mask\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq_करोमुख्य_is_ipi_single(करोमुख्य)) अणु
		/*
		 * If the underlying implementation uses a single HW irq on
		 * all cpus then we only need a single Linux irq number क्रम
		 * it. We have no restrictions vs. the destination mask. The
		 * underlying implementation can deal with holes nicely.
		 */
		nr_irqs = 1;
		offset = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक next;

		/*
		 * The IPI requires a separate HW irq on each CPU. We require
		 * that the destination mask is consecutive. If an
		 * implementation needs to support holes, it can reserve
		 * several IPI ranges.
		 */
		offset = cpumask_first(dest);
		/*
		 * Find a hole and अगर found look क्रम another set bit after the
		 * hole. For now we करोn't support this scenario.
		 */
		next = cpumask_next_zero(offset, dest);
		अगर (next < nr_cpu_ids)
			next = cpumask_next(next, dest);
		अगर (next < nr_cpu_ids) अणु
			pr_warn("Destination mask has holes\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	virq = irq_करोमुख्य_alloc_descs(-1, nr_irqs, 0, NUMA_NO_NODE, शून्य);
	अगर (virq <= 0) अणु
		pr_warn("Can't reserve IPI, failed to alloc descs\n");
		वापस -ENOMEM;
	पूर्ण

	virq = __irq_करोमुख्य_alloc_irqs(करोमुख्य, virq, nr_irqs, NUMA_NO_NODE,
				       (व्योम *) dest, true, शून्य);

	अगर (virq <= 0) अणु
		pr_warn("Can't reserve IPI, failed to alloc hw irqs\n");
		जाओ मुक्त_descs;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		data = irq_get_irq_data(virq + i);
		cpumask_copy(data->common->affinity, dest);
		data->common->ipi_offset = offset;
		irq_set_status_flags(virq + i, IRQ_NO_BALANCING);
	पूर्ण
	वापस virq;

मुक्त_descs:
	irq_मुक्त_descs(virq, nr_irqs);
	वापस -EBUSY;
पूर्ण

/**
 * irq_destroy_ipi() - unreserve an IPI that was previously allocated
 * @irq:	linux irq number to be destroyed
 * @dest:	cpumask of cpus which should have the IPI हटाओd
 *
 * The IPIs allocated with irq_reserve_ipi() are वापसed to the प्रणाली
 * destroying all virqs associated with them.
 *
 * Return 0 on success or error code on failure.
 */
पूर्णांक irq_destroy_ipi(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *dest)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	काष्ठा cpumask *ipimask = data ? irq_data_get_affinity_mask(data) : शून्य;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक nr_irqs;

	अगर (!irq || !data || !ipimask)
		वापस -EINVAL;

	करोमुख्य = data->करोमुख्य;
	अगर (WARN_ON(करोमुख्य == शून्य))
		वापस -EINVAL;

	अगर (!irq_करोमुख्य_is_ipi(करोमुख्य)) अणु
		pr_warn("Trying to destroy a non IPI domain!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(!cpumask_subset(dest, ipimask)))
		/*
		 * Must be destroying a subset of CPUs to which this IPI
		 * was set up to target
		 */
		वापस -EINVAL;

	अगर (irq_करोमुख्य_is_ipi_per_cpu(करोमुख्य)) अणु
		irq = irq + cpumask_first(dest) - data->common->ipi_offset;
		nr_irqs = cpumask_weight(dest);
	पूर्ण अन्यथा अणु
		nr_irqs = 1;
	पूर्ण

	irq_करोमुख्य_मुक्त_irqs(irq, nr_irqs);
	वापस 0;
पूर्ण

/**
 * ipi_get_hwirq - Get the hwirq associated with an IPI to a cpu
 * @irq:	linux irq number
 * @cpu:	the target cpu
 *
 * When dealing with coprocessors IPI, we need to inक्रमm the coprocessor of
 * the hwirq it needs to use to receive and send IPIs.
 *
 * Returns hwirq value on success and INVALID_HWIRQ on failure.
 */
irq_hw_number_t ipi_get_hwirq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	काष्ठा cpumask *ipimask = data ? irq_data_get_affinity_mask(data) : शून्य;

	अगर (!data || !ipimask || cpu >= nr_cpu_ids)
		वापस INVALID_HWIRQ;

	अगर (!cpumask_test_cpu(cpu, ipimask))
		वापस INVALID_HWIRQ;

	/*
	 * Get the real hardware irq number अगर the underlying implementation
	 * uses a separate irq per cpu. If the underlying implementation uses
	 * a single hardware irq क्रम all cpus then the IPI send mechanism
	 * needs to take care of the cpu destinations.
	 */
	अगर (irq_करोमुख्य_is_ipi_per_cpu(data->करोमुख्य))
		data = irq_get_irq_data(irq + cpu - data->common->ipi_offset);

	वापस data ? irqd_to_hwirq(data) : INVALID_HWIRQ;
पूर्ण
EXPORT_SYMBOL_GPL(ipi_get_hwirq);

अटल पूर्णांक ipi_send_verअगरy(काष्ठा irq_chip *chip, काष्ठा irq_data *data,
			   स्थिर काष्ठा cpumask *dest, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpumask *ipimask = irq_data_get_affinity_mask(data);

	अगर (!chip || !ipimask)
		वापस -EINVAL;

	अगर (!chip->ipi_send_single && !chip->ipi_send_mask)
		वापस -EINVAL;

	अगर (cpu >= nr_cpu_ids)
		वापस -EINVAL;

	अगर (dest) अणु
		अगर (!cpumask_subset(dest, ipimask))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!cpumask_test_cpu(cpu, ipimask))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * __ipi_send_single - send an IPI to a target Linux SMP CPU
 * @desc:	poपूर्णांकer to irq_desc of the IRQ
 * @cpu:	destination CPU, must in the destination mask passed to
 *		irq_reserve_ipi()
 *
 * This function is क्रम architecture or core code to speed up IPI sending. Not
 * usable from driver code.
 *
 * Returns zero on success and negative error number on failure.
 */
पूर्णांक __ipi_send_single(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);

#अगर_घोषित DEBUG
	/*
	 * Minimise the overhead by omitting the checks क्रम Linux SMP IPIs.
	 * Since the callers should be arch or core code which is generally
	 * trusted, only check क्रम errors when debugging.
	 */
	अगर (WARN_ON_ONCE(ipi_send_verअगरy(chip, data, शून्य, cpu)))
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (!chip->ipi_send_single) अणु
		chip->ipi_send_mask(data, cpumask_of(cpu));
		वापस 0;
	पूर्ण

	/* FIXME: Store this inक्रमmation in irqdata flags */
	अगर (irq_करोमुख्य_is_ipi_per_cpu(data->करोमुख्य) &&
	    cpu != data->common->ipi_offset) अणु
		/* use the correct data क्रम that cpu */
		अचिन्हित irq = data->irq + cpu - data->common->ipi_offset;

		data = irq_get_irq_data(irq);
	पूर्ण
	chip->ipi_send_single(data, cpu);
	वापस 0;
पूर्ण

/**
 * ipi_send_mask - send an IPI to target Linux SMP CPU(s)
 * @desc:	poपूर्णांकer to irq_desc of the IRQ
 * @dest:	dest CPU(s), must be a subset of the mask passed to
 *		irq_reserve_ipi()
 *
 * This function is क्रम architecture or core code to speed up IPI sending. Not
 * usable from driver code.
 *
 * Returns zero on success and negative error number on failure.
 */
पूर्णांक __ipi_send_mask(काष्ठा irq_desc *desc, स्थिर काष्ठा cpumask *dest)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	अचिन्हित पूर्णांक cpu;

#अगर_घोषित DEBUG
	/*
	 * Minimise the overhead by omitting the checks क्रम Linux SMP IPIs.
	 * Since the callers should be arch or core code which is generally
	 * trusted, only check क्रम errors when debugging.
	 */
	अगर (WARN_ON_ONCE(ipi_send_verअगरy(chip, data, dest, 0)))
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (chip->ipi_send_mask) अणु
		chip->ipi_send_mask(data, dest);
		वापस 0;
	पूर्ण

	अगर (irq_करोमुख्य_is_ipi_per_cpu(data->करोमुख्य)) अणु
		अचिन्हित पूर्णांक base = data->irq;

		क्रम_each_cpu(cpu, dest) अणु
			अचिन्हित irq = base + cpu - data->common->ipi_offset;

			data = irq_get_irq_data(irq);
			chip->ipi_send_single(data, cpu);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_cpu(cpu, dest)
			chip->ipi_send_single(data, cpu);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ipi_send_single - Send an IPI to a single CPU
 * @virq:	linux irq number from irq_reserve_ipi()
 * @cpu:	destination CPU, must in the destination mask passed to
 *		irq_reserve_ipi()
 *
 * Returns zero on success and negative error number on failure.
 */
पूर्णांक ipi_send_single(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(virq);
	काष्ठा irq_data *data = desc ? irq_desc_get_irq_data(desc) : शून्य;
	काष्ठा irq_chip *chip = data ? irq_data_get_irq_chip(data) : शून्य;

	अगर (WARN_ON_ONCE(ipi_send_verअगरy(chip, data, शून्य, cpu)))
		वापस -EINVAL;

	वापस __ipi_send_single(desc, cpu);
पूर्ण
EXPORT_SYMBOL_GPL(ipi_send_single);

/**
 * ipi_send_mask - Send an IPI to target CPU(s)
 * @virq:	linux irq number from irq_reserve_ipi()
 * @dest:	dest CPU(s), must be a subset of the mask passed to
 *		irq_reserve_ipi()
 *
 * Returns zero on success and negative error number on failure.
 */
पूर्णांक ipi_send_mask(अचिन्हित पूर्णांक virq, स्थिर काष्ठा cpumask *dest)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(virq);
	काष्ठा irq_data *data = desc ? irq_desc_get_irq_data(desc) : शून्य;
	काष्ठा irq_chip *chip = data ? irq_data_get_irq_chip(data) : शून्य;

	अगर (WARN_ON_ONCE(ipi_send_verअगरy(chip, data, dest, 0)))
		वापस -EINVAL;

	वापस __ipi_send_mask(desc, dest);
पूर्ण
EXPORT_SYMBOL_GPL(ipi_send_mask);
