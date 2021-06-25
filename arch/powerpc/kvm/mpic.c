<शैली गुरु>
/*
 * OpenPIC emulation
 *
 * Copyright (c) 2004 Jocelyn Mayer
 *               2011 Alexander Graf
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/kvm_para.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <kvm/iodev.h>

#घोषणा MAX_CPU     32
#घोषणा MAX_SRC     256
#घोषणा MAX_TMR     4
#घोषणा MAX_IPI     4
#घोषणा MAX_MSI     8
#घोषणा MAX_IRQ     (MAX_SRC + MAX_IPI + MAX_TMR)
#घोषणा VID         0x03	/* MPIC version ID */

/* OpenPIC capability flags */
#घोषणा OPENPIC_FLAG_IDR_CRIT     (1 << 0)
#घोषणा OPENPIC_FLAG_ILR          (2 << 0)

/* OpenPIC address map */
#घोषणा OPENPIC_REG_SIZE             0x40000
#घोषणा OPENPIC_GLB_REG_START        0x0
#घोषणा OPENPIC_GLB_REG_SIZE         0x10F0
#घोषणा OPENPIC_TMR_REG_START        0x10F0
#घोषणा OPENPIC_TMR_REG_SIZE         0x220
#घोषणा OPENPIC_MSI_REG_START        0x1600
#घोषणा OPENPIC_MSI_REG_SIZE         0x200
#घोषणा OPENPIC_SUMMARY_REG_START    0x3800
#घोषणा OPENPIC_SUMMARY_REG_SIZE     0x800
#घोषणा OPENPIC_SRC_REG_START        0x10000
#घोषणा OPENPIC_SRC_REG_SIZE         (MAX_SRC * 0x20)
#घोषणा OPENPIC_CPU_REG_START        0x20000
#घोषणा OPENPIC_CPU_REG_SIZE         (0x100 + ((MAX_CPU - 1) * 0x1000))

काष्ठा fsl_mpic_info अणु
	पूर्णांक max_ext;
पूर्ण;

अटल काष्ठा fsl_mpic_info fsl_mpic_20 = अणु
	.max_ext = 12,
पूर्ण;

अटल काष्ठा fsl_mpic_info fsl_mpic_42 = अणु
	.max_ext = 12,
पूर्ण;

#घोषणा FRR_NIRQ_SHIFT    16
#घोषणा FRR_NCPU_SHIFT     8
#घोषणा FRR_VID_SHIFT      0

#घोषणा VID_REVISION_1_2   2
#घोषणा VID_REVISION_1_3   3

#घोषणा VIR_GENERIC      0x00000000	/* Generic Venकरोr ID */

#घोषणा GCR_RESET        0x80000000
#घोषणा GCR_MODE_PASS    0x00000000
#घोषणा GCR_MODE_MIXED   0x20000000
#घोषणा GCR_MODE_PROXY   0x60000000

#घोषणा TBCR_CI           0x80000000	/* count inhibit */
#घोषणा TCCR_TOG          0x80000000	/* toggles when decrement to zero */

#घोषणा IDR_EP_SHIFT      31
#घोषणा IDR_EP_MASK       (1 << IDR_EP_SHIFT)
#घोषणा IDR_CI0_SHIFT     30
#घोषणा IDR_CI1_SHIFT     29
#घोषणा IDR_P1_SHIFT      1
#घोषणा IDR_P0_SHIFT      0

#घोषणा ILR_INTTGT_MASK   0x000000ff
#घोषणा ILR_INTTGT_INT    0x00
#घोषणा ILR_INTTGT_CINT   0x01	/* critical */
#घोषणा ILR_INTTGT_MCP    0x02	/* machine check */
#घोषणा NUM_OUTPUTS       3

#घोषणा MSIIR_OFFSET       0x140
#घोषणा MSIIR_SRS_SHIFT    29
#घोषणा MSIIR_SRS_MASK     (0x7 << MSIIR_SRS_SHIFT)
#घोषणा MSIIR_IBS_SHIFT    24
#घोषणा MSIIR_IBS_MASK     (0x1f << MSIIR_IBS_SHIFT)

अटल पूर्णांक get_current_cpu(व्योम)
अणु
#अगर defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	काष्ठा kvm_vcpu *vcpu = current->thपढ़ो.kvm_vcpu;
	वापस vcpu ? vcpu->arch.irq_cpu_id : -1;
#अन्यथा
	/* XXX */
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक खोलोpic_cpu_ग_लिखो_पूर्णांकernal(व्योम *opaque, gpa_t addr,
				      u32 val, पूर्णांक idx);
अटल पूर्णांक खोलोpic_cpu_पढ़ो_पूर्णांकernal(व्योम *opaque, gpa_t addr,
				     u32 *ptr, पूर्णांक idx);
अटल अंतरभूत व्योम ग_लिखो_IRQreg_idr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ,
				    uपूर्णांक32_t val);

क्रमागत irq_type अणु
	IRQ_TYPE_NORMAL = 0,
	IRQ_TYPE_FSLINT,	/* FSL पूर्णांकernal पूर्णांकerrupt -- level only */
	IRQ_TYPE_FSLSPECIAL,	/* FSL समयr/IPI पूर्णांकerrupt, edge, no polarity */
पूर्ण;

काष्ठा irq_queue अणु
	/* Round up to the nearest 64 IRQs so that the queue length
	 * won't change when moving between 32 and 64 bit hosts.
	 */
	अचिन्हित दीर्घ queue[BITS_TO_LONGS((MAX_IRQ + 63) & ~63)];
	पूर्णांक next;
	पूर्णांक priority;
पूर्ण;

काष्ठा irq_source अणु
	uपूर्णांक32_t ivpr;		/* IRQ vector/priority रेजिस्टर */
	uपूर्णांक32_t idr;		/* IRQ destination रेजिस्टर */
	uपूर्णांक32_t desपंचांगask;	/* biपंचांगap of CPU destinations */
	पूर्णांक last_cpu;
	पूर्णांक output;		/* IRQ level, e.g. ILR_INTTGT_INT */
	पूर्णांक pending;		/* TRUE अगर IRQ is pending */
	क्रमागत irq_type type;
	bool level:1;		/* level-triggered */
	bool nomask:1;	/* critical पूर्णांकerrupts ignore mask on some FSL MPICs */
पूर्ण;

#घोषणा IVPR_MASK_SHIFT       31
#घोषणा IVPR_MASK_MASK        (1 << IVPR_MASK_SHIFT)
#घोषणा IVPR_ACTIVITY_SHIFT   30
#घोषणा IVPR_ACTIVITY_MASK    (1 << IVPR_ACTIVITY_SHIFT)
#घोषणा IVPR_MODE_SHIFT       29
#घोषणा IVPR_MODE_MASK        (1 << IVPR_MODE_SHIFT)
#घोषणा IVPR_POLARITY_SHIFT   23
#घोषणा IVPR_POLARITY_MASK    (1 << IVPR_POLARITY_SHIFT)
#घोषणा IVPR_SENSE_SHIFT      22
#घोषणा IVPR_SENSE_MASK       (1 << IVPR_SENSE_SHIFT)

#घोषणा IVPR_PRIORITY_MASK     (0xF << 16)
#घोषणा IVPR_PRIORITY(_ivprr_) ((पूर्णांक)(((_ivprr_) & IVPR_PRIORITY_MASK) >> 16))
#घोषणा IVPR_VECTOR(opp, _ivprr_) ((_ivprr_) & (opp)->vector_mask)

/* IDR[EP/CI] are only क्रम FSL MPIC prior to v4.0 */
#घोषणा IDR_EP      0x80000000	/* बाह्यal pin */
#घोषणा IDR_CI      0x40000000	/* critical पूर्णांकerrupt */

काष्ठा irq_dest अणु
	काष्ठा kvm_vcpu *vcpu;

	पूर्णांक32_t ctpr;		/* CPU current task priority */
	काष्ठा irq_queue उठाओd;
	काष्ठा irq_queue servicing;

	/* Count of IRQ sources निश्चितing on non-INT outमाला_दो */
	uपूर्णांक32_t outमाला_दो_active[NUM_OUTPUTS];
पूर्ण;

#घोषणा MAX_MMIO_REGIONS 10

काष्ठा खोलोpic अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_device *dev;
	काष्ठा kvm_io_device mmio;
	स्थिर काष्ठा mem_reg *mmio_regions[MAX_MMIO_REGIONS];
	पूर्णांक num_mmio_regions;

	gpa_t reg_base;
	spinlock_t lock;

	/* Behavior control */
	काष्ठा fsl_mpic_info *fsl;
	uपूर्णांक32_t model;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t nb_irqs;
	uपूर्णांक32_t vid;
	uपूर्णांक32_t vir;		/* Venकरोr identअगरication रेजिस्टर */
	uपूर्णांक32_t vector_mask;
	uपूर्णांक32_t tfrr_reset;
	uपूर्णांक32_t ivpr_reset;
	uपूर्णांक32_t idr_reset;
	uपूर्णांक32_t brr1;
	uपूर्णांक32_t mpic_mode_mask;

	/* Global रेजिस्टरs */
	uपूर्णांक32_t frr;		/* Feature reporting रेजिस्टर */
	uपूर्णांक32_t gcr;		/* Global configuration रेजिस्टर  */
	uपूर्णांक32_t pir;		/* Processor initialization रेजिस्टर */
	uपूर्णांक32_t spve;		/* Spurious vector रेजिस्टर */
	uपूर्णांक32_t tfrr;		/* Timer frequency reporting रेजिस्टर */
	/* Source रेजिस्टरs */
	काष्ठा irq_source src[MAX_IRQ];
	/* Local रेजिस्टरs per output pin */
	काष्ठा irq_dest dst[MAX_CPU];
	uपूर्णांक32_t nb_cpus;
	/* Timer रेजिस्टरs */
	काष्ठा अणु
		uपूर्णांक32_t tccr;	/* Global समयr current count रेजिस्टर */
		uपूर्णांक32_t tbcr;	/* Global समयr base count रेजिस्टर */
	पूर्ण समयrs[MAX_TMR];
	/* Shared MSI रेजिस्टरs */
	काष्ठा अणु
		uपूर्णांक32_t msir;	/* Shared Message Signaled Interrupt Register */
	पूर्ण msi[MAX_MSI];
	uपूर्णांक32_t max_irq;
	uपूर्णांक32_t irq_ipi0;
	uपूर्णांक32_t irq_tim0;
	uपूर्णांक32_t irq_msi;
पूर्ण;


अटल व्योम mpic_irq_उठाओ(काष्ठा खोलोpic *opp, काष्ठा irq_dest *dst,
			   पूर्णांक output)
अणु
	काष्ठा kvm_पूर्णांकerrupt irq = अणु
		.irq = KVM_INTERRUPT_SET_LEVEL,
	पूर्ण;

	अगर (!dst->vcpu) अणु
		pr_debug("%s: destination cpu %d does not exist\n",
			 __func__, (पूर्णांक)(dst - &opp->dst[0]));
		वापस;
	पूर्ण

	pr_debug("%s: cpu %d output %d\n", __func__, dst->vcpu->arch.irq_cpu_id,
		output);

	अगर (output != ILR_INTTGT_INT)	/* TODO */
		वापस;

	kvm_vcpu_ioctl_पूर्णांकerrupt(dst->vcpu, &irq);
पूर्ण

अटल व्योम mpic_irq_lower(काष्ठा खोलोpic *opp, काष्ठा irq_dest *dst,
			   पूर्णांक output)
अणु
	अगर (!dst->vcpu) अणु
		pr_debug("%s: destination cpu %d does not exist\n",
			 __func__, (पूर्णांक)(dst - &opp->dst[0]));
		वापस;
	पूर्ण

	pr_debug("%s: cpu %d output %d\n", __func__, dst->vcpu->arch.irq_cpu_id,
		output);

	अगर (output != ILR_INTTGT_INT)	/* TODO */
		वापस;

	kvmppc_core_dequeue_बाह्यal(dst->vcpu);
पूर्ण

अटल अंतरभूत व्योम IRQ_setbit(काष्ठा irq_queue *q, पूर्णांक n_IRQ)
अणु
	set_bit(n_IRQ, q->queue);
पूर्ण

अटल अंतरभूत व्योम IRQ_resetbit(काष्ठा irq_queue *q, पूर्णांक n_IRQ)
अणु
	clear_bit(n_IRQ, q->queue);
पूर्ण

अटल व्योम IRQ_check(काष्ठा खोलोpic *opp, काष्ठा irq_queue *q)
अणु
	पूर्णांक irq = -1;
	पूर्णांक next = -1;
	पूर्णांक priority = -1;

	क्रम (;;) अणु
		irq = find_next_bit(q->queue, opp->max_irq, irq + 1);
		अगर (irq == opp->max_irq)
			अवरोध;

		pr_debug("IRQ_check: irq %d set ivpr_pr=%d pr=%d\n",
			irq, IVPR_PRIORITY(opp->src[irq].ivpr), priority);

		अगर (IVPR_PRIORITY(opp->src[irq].ivpr) > priority) अणु
			next = irq;
			priority = IVPR_PRIORITY(opp->src[irq].ivpr);
		पूर्ण
	पूर्ण

	q->next = next;
	q->priority = priority;
पूर्ण

अटल पूर्णांक IRQ_get_next(काष्ठा खोलोpic *opp, काष्ठा irq_queue *q)
अणु
	/* XXX: optimize */
	IRQ_check(opp, q);

	वापस q->next;
पूर्ण

अटल व्योम IRQ_local_pipe(काष्ठा खोलोpic *opp, पूर्णांक n_CPU, पूर्णांक n_IRQ,
			   bool active, bool was_active)
अणु
	काष्ठा irq_dest *dst;
	काष्ठा irq_source *src;
	पूर्णांक priority;

	dst = &opp->dst[n_CPU];
	src = &opp->src[n_IRQ];

	pr_debug("%s: IRQ %d active %d was %d\n",
		__func__, n_IRQ, active, was_active);

	अगर (src->output != ILR_INTTGT_INT) अणु
		pr_debug("%s: output %d irq %d active %d was %d count %d\n",
			__func__, src->output, n_IRQ, active, was_active,
			dst->outमाला_दो_active[src->output]);

		/* On Freescale MPIC, critical पूर्णांकerrupts ignore priority,
		 * IACK, EOI, etc.  Beक्रमe MPIC v4.1 they also ignore
		 * masking.
		 */
		अगर (active) अणु
			अगर (!was_active &&
			    dst->outमाला_दो_active[src->output]++ == 0) अणु
				pr_debug("%s: Raise OpenPIC output %d cpu %d irq %d\n",
					__func__, src->output, n_CPU, n_IRQ);
				mpic_irq_उठाओ(opp, dst, src->output);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (was_active &&
			    --dst->outमाला_दो_active[src->output] == 0) अणु
				pr_debug("%s: Lower OpenPIC output %d cpu %d irq %d\n",
					__func__, src->output, n_CPU, n_IRQ);
				mpic_irq_lower(opp, dst, src->output);
			पूर्ण
		पूर्ण

		वापस;
	पूर्ण

	priority = IVPR_PRIORITY(src->ivpr);

	/* Even अगर the पूर्णांकerrupt करोesn't have enough priority,
	 * it is still उठाओd, in हाल ctpr is lowered later.
	 */
	अगर (active)
		IRQ_setbit(&dst->उठाओd, n_IRQ);
	अन्यथा
		IRQ_resetbit(&dst->उठाओd, n_IRQ);

	IRQ_check(opp, &dst->उठाओd);

	अगर (active && priority <= dst->ctpr) अणु
		pr_debug("%s: IRQ %d priority %d too low for ctpr %d on CPU %d\n",
			__func__, n_IRQ, priority, dst->ctpr, n_CPU);
		active = 0;
	पूर्ण

	अगर (active) अणु
		अगर (IRQ_get_next(opp, &dst->servicing) >= 0 &&
		    priority <= dst->servicing.priority) अणु
			pr_debug("%s: IRQ %d is hidden by servicing IRQ %d on CPU %d\n",
				__func__, n_IRQ, dst->servicing.next, n_CPU);
		पूर्ण अन्यथा अणु
			pr_debug("%s: Raise OpenPIC INT output cpu %d irq %d/%d\n",
				__func__, n_CPU, n_IRQ, dst->उठाओd.next);
			mpic_irq_उठाओ(opp, dst, ILR_INTTGT_INT);
		पूर्ण
	पूर्ण अन्यथा अणु
		IRQ_get_next(opp, &dst->servicing);
		अगर (dst->उठाओd.priority > dst->ctpr &&
		    dst->उठाओd.priority > dst->servicing.priority) अणु
			pr_debug("%s: IRQ %d inactive, IRQ %d prio %d above %d/%d, CPU %d\n",
				__func__, n_IRQ, dst->उठाओd.next,
				dst->उठाओd.priority, dst->ctpr,
				dst->servicing.priority, n_CPU);
			/* IRQ line stays निश्चितed */
		पूर्ण अन्यथा अणु
			pr_debug("%s: IRQ %d inactive, current prio %d/%d, CPU %d\n",
				__func__, n_IRQ, dst->ctpr,
				dst->servicing.priority, n_CPU);
			mpic_irq_lower(opp, dst, ILR_INTTGT_INT);
		पूर्ण
	पूर्ण
पूर्ण

/* update pic state because रेजिस्टरs क्रम n_IRQ have changed value */
अटल व्योम खोलोpic_update_irq(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ)
अणु
	काष्ठा irq_source *src;
	bool active, was_active;
	पूर्णांक i;

	src = &opp->src[n_IRQ];
	active = src->pending;

	अगर ((src->ivpr & IVPR_MASK_MASK) && !src->nomask) अणु
		/* Interrupt source is disabled */
		pr_debug("%s: IRQ %d is disabled\n", __func__, n_IRQ);
		active = false;
	पूर्ण

	was_active = !!(src->ivpr & IVPR_ACTIVITY_MASK);

	/*
	 * We करोn't have a similar check क्रम alपढ़ोy-active because
	 * ctpr may have changed and we need to withdraw the पूर्णांकerrupt.
	 */
	अगर (!active && !was_active) अणु
		pr_debug("%s: IRQ %d is already inactive\n", __func__, n_IRQ);
		वापस;
	पूर्ण

	अगर (active)
		src->ivpr |= IVPR_ACTIVITY_MASK;
	अन्यथा
		src->ivpr &= ~IVPR_ACTIVITY_MASK;

	अगर (src->desपंचांगask == 0) अणु
		/* No target */
		pr_debug("%s: IRQ %d has no target\n", __func__, n_IRQ);
		वापस;
	पूर्ण

	अगर (src->desपंचांगask == (1 << src->last_cpu)) अणु
		/* Only one CPU is allowed to receive this IRQ */
		IRQ_local_pipe(opp, src->last_cpu, n_IRQ, active, was_active);
	पूर्ण अन्यथा अगर (!(src->ivpr & IVPR_MODE_MASK)) अणु
		/* Directed delivery mode */
		क्रम (i = 0; i < opp->nb_cpus; i++) अणु
			अगर (src->desपंचांगask & (1 << i)) अणु
				IRQ_local_pipe(opp, i, n_IRQ, active,
					       was_active);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Distributed delivery mode */
		क्रम (i = src->last_cpu + 1; i != src->last_cpu; i++) अणु
			अगर (i == opp->nb_cpus)
				i = 0;

			अगर (src->desपंचांगask & (1 << i)) अणु
				IRQ_local_pipe(opp, i, n_IRQ, active,
					       was_active);
				src->last_cpu = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम खोलोpic_set_irq(व्योम *opaque, पूर्णांक n_IRQ, पूर्णांक level)
अणु
	काष्ठा खोलोpic *opp = opaque;
	काष्ठा irq_source *src;

	अगर (n_IRQ >= MAX_IRQ) अणु
		WARN_ONCE(1, "%s: IRQ %d out of range\n", __func__, n_IRQ);
		वापस;
	पूर्ण

	src = &opp->src[n_IRQ];
	pr_debug("openpic: set irq %d = %d ivpr=0x%08x\n",
		n_IRQ, level, src->ivpr);
	अगर (src->level) अणु
		/* level-sensitive irq */
		src->pending = level;
		खोलोpic_update_irq(opp, n_IRQ);
	पूर्ण अन्यथा अणु
		/* edge-sensitive irq */
		अगर (level) अणु
			src->pending = 1;
			खोलोpic_update_irq(opp, n_IRQ);
		पूर्ण

		अगर (src->output != ILR_INTTGT_INT) अणु
			/* Edge-triggered पूर्णांकerrupts shouldn't be used
			 * with non-INT delivery, but just in हाल,
			 * try to make it करो something sane rather than
			 * cause an पूर्णांकerrupt storm.  This is बंद to
			 * what you'd probably see happen in real hardware.
			 */
			src->pending = 0;
			खोलोpic_update_irq(opp, n_IRQ);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम खोलोpic_reset(काष्ठा खोलोpic *opp)
अणु
	पूर्णांक i;

	opp->gcr = GCR_RESET;
	/* Initialise controller रेजिस्टरs */
	opp->frr = ((opp->nb_irqs - 1) << FRR_NIRQ_SHIFT) |
	    (opp->vid << FRR_VID_SHIFT);

	opp->pir = 0;
	opp->spve = -1 & opp->vector_mask;
	opp->tfrr = opp->tfrr_reset;
	/* Initialise IRQ sources */
	क्रम (i = 0; i < opp->max_irq; i++) अणु
		opp->src[i].ivpr = opp->ivpr_reset;

		चयन (opp->src[i].type) अणु
		हाल IRQ_TYPE_NORMAL:
			opp->src[i].level =
			    !!(opp->ivpr_reset & IVPR_SENSE_MASK);
			अवरोध;

		हाल IRQ_TYPE_FSLINT:
			opp->src[i].ivpr |= IVPR_POLARITY_MASK;
			अवरोध;

		हाल IRQ_TYPE_FSLSPECIAL:
			अवरोध;
		पूर्ण

		ग_लिखो_IRQreg_idr(opp, i, opp->idr_reset);
	पूर्ण
	/* Initialise IRQ destinations */
	क्रम (i = 0; i < MAX_CPU; i++) अणु
		opp->dst[i].ctpr = 15;
		स_रखो(&opp->dst[i].उठाओd, 0, माप(काष्ठा irq_queue));
		opp->dst[i].उठाओd.next = -1;
		स_रखो(&opp->dst[i].servicing, 0, माप(काष्ठा irq_queue));
		opp->dst[i].servicing.next = -1;
	पूर्ण
	/* Initialise समयrs */
	क्रम (i = 0; i < MAX_TMR; i++) अणु
		opp->समयrs[i].tccr = 0;
		opp->समयrs[i].tbcr = TBCR_CI;
	पूर्ण
	/* Go out of RESET state */
	opp->gcr = 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_IRQreg_idr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ)
अणु
	वापस opp->src[n_IRQ].idr;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_IRQreg_ilr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ)
अणु
	अगर (opp->flags & OPENPIC_FLAG_ILR)
		वापस opp->src[n_IRQ].output;

	वापस 0xffffffff;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_IRQreg_ivpr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ)
अणु
	वापस opp->src[n_IRQ].ivpr;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_IRQreg_idr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ,
				    uपूर्णांक32_t val)
अणु
	काष्ठा irq_source *src = &opp->src[n_IRQ];
	uपूर्णांक32_t normal_mask = (1UL << opp->nb_cpus) - 1;
	uपूर्णांक32_t crit_mask = 0;
	uपूर्णांक32_t mask = normal_mask;
	पूर्णांक crit_shअगरt = IDR_EP_SHIFT - opp->nb_cpus;
	पूर्णांक i;

	अगर (opp->flags & OPENPIC_FLAG_IDR_CRIT) अणु
		crit_mask = mask << crit_shअगरt;
		mask |= crit_mask | IDR_EP;
	पूर्ण

	src->idr = val & mask;
	pr_debug("Set IDR %d to 0x%08x\n", n_IRQ, src->idr);

	अगर (opp->flags & OPENPIC_FLAG_IDR_CRIT) अणु
		अगर (src->idr & crit_mask) अणु
			अगर (src->idr & normal_mask) अणु
				pr_debug("%s: IRQ configured for multiple output types, using critical\n",
					__func__);
			पूर्ण

			src->output = ILR_INTTGT_CINT;
			src->nomask = true;
			src->desपंचांगask = 0;

			क्रम (i = 0; i < opp->nb_cpus; i++) अणु
				पूर्णांक n_ci = IDR_CI0_SHIFT - i;

				अगर (src->idr & (1UL << n_ci))
					src->desपंचांगask |= 1UL << i;
			पूर्ण
		पूर्ण अन्यथा अणु
			src->output = ILR_INTTGT_INT;
			src->nomask = false;
			src->desपंचांगask = src->idr & normal_mask;
		पूर्ण
	पूर्ण अन्यथा अणु
		src->desपंचांगask = src->idr;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_IRQreg_ilr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ,
				    uपूर्णांक32_t val)
अणु
	अगर (opp->flags & OPENPIC_FLAG_ILR) अणु
		काष्ठा irq_source *src = &opp->src[n_IRQ];

		src->output = val & ILR_INTTGT_MASK;
		pr_debug("Set ILR %d to 0x%08x, output %d\n", n_IRQ, src->idr,
			src->output);

		/* TODO: on MPIC v4.0 only, set nomask क्रम non-INT */
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_IRQreg_ivpr(काष्ठा खोलोpic *opp, पूर्णांक n_IRQ,
				     uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t mask;

	/* NOTE when implementing newer FSL MPIC models: starting with v4.0,
	 * the polarity bit is पढ़ो-only on पूर्णांकernal पूर्णांकerrupts.
	 */
	mask = IVPR_MASK_MASK | IVPR_PRIORITY_MASK | IVPR_SENSE_MASK |
	    IVPR_POLARITY_MASK | opp->vector_mask;

	/* ACTIVITY bit is पढ़ो-only */
	opp->src[n_IRQ].ivpr =
	    (opp->src[n_IRQ].ivpr & IVPR_ACTIVITY_MASK) | (val & mask);

	/* For FSL पूर्णांकernal पूर्णांकerrupts, The sense bit is reserved and zero,
	 * and the पूर्णांकerrupt is always level-triggered.  Timers and IPIs
	 * have no sense or polarity bits, and are edge-triggered.
	 */
	चयन (opp->src[n_IRQ].type) अणु
	हाल IRQ_TYPE_NORMAL:
		opp->src[n_IRQ].level =
		    !!(opp->src[n_IRQ].ivpr & IVPR_SENSE_MASK);
		अवरोध;

	हाल IRQ_TYPE_FSLINT:
		opp->src[n_IRQ].ivpr &= ~IVPR_SENSE_MASK;
		अवरोध;

	हाल IRQ_TYPE_FSLSPECIAL:
		opp->src[n_IRQ].ivpr &= ~(IVPR_POLARITY_MASK | IVPR_SENSE_MASK);
		अवरोध;
	पूर्ण

	खोलोpic_update_irq(opp, n_IRQ);
	pr_debug("Set IVPR %d to 0x%08x -> 0x%08x\n", n_IRQ, val,
		opp->src[n_IRQ].ivpr);
पूर्ण

अटल व्योम खोलोpic_gcr_ग_लिखो(काष्ठा खोलोpic *opp, uपूर्णांक64_t val)
अणु
	अगर (val & GCR_RESET) अणु
		खोलोpic_reset(opp);
		वापस;
	पूर्ण

	opp->gcr &= ~opp->mpic_mode_mask;
	opp->gcr |= val & opp->mpic_mode_mask;
पूर्ण

अटल पूर्णांक खोलोpic_gbl_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	काष्ठा खोलोpic *opp = opaque;
	पूर्णांक err = 0;

	pr_debug("%s: addr %#llx <= %08x\n", __func__, addr, val);
	अगर (addr & 0xF)
		वापस 0;

	चयन (addr) अणु
	हाल 0x00:	/* Block Revision Register1 (BRR1) is Reaकरोnly */
		अवरोध;
	हाल 0x40:
	हाल 0x50:
	हाल 0x60:
	हाल 0x70:
	हाल 0x80:
	हाल 0x90:
	हाल 0xA0:
	हाल 0xB0:
		err = खोलोpic_cpu_ग_लिखो_पूर्णांकernal(opp, addr, val,
						 get_current_cpu());
		अवरोध;
	हाल 0x1000:		/* FRR */
		अवरोध;
	हाल 0x1020:		/* GCR */
		खोलोpic_gcr_ग_लिखो(opp, val);
		अवरोध;
	हाल 0x1080:		/* VIR */
		अवरोध;
	हाल 0x1090:		/* PIR */
		/*
		 * This रेजिस्टर is used to reset a CPU core --
		 * let userspace handle it.
		 */
		err = -ENXIO;
		अवरोध;
	हाल 0x10A0:		/* IPI_IVPR */
	हाल 0x10B0:
	हाल 0x10C0:
	हाल 0x10D0: अणु
		पूर्णांक idx;
		idx = (addr - 0x10A0) >> 4;
		ग_लिखो_IRQreg_ivpr(opp, opp->irq_ipi0 + idx, val);
		अवरोध;
	पूर्ण
	हाल 0x10E0:		/* SPVE */
		opp->spve = val & opp->vector_mask;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक खोलोpic_gbl_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	काष्ठा खोलोpic *opp = opaque;
	u32 retval;
	पूर्णांक err = 0;

	pr_debug("%s: addr %#llx\n", __func__, addr);
	retval = 0xFFFFFFFF;
	अगर (addr & 0xF)
		जाओ out;

	चयन (addr) अणु
	हाल 0x1000:		/* FRR */
		retval = opp->frr;
		retval |= (opp->nb_cpus - 1) << FRR_NCPU_SHIFT;
		अवरोध;
	हाल 0x1020:		/* GCR */
		retval = opp->gcr;
		अवरोध;
	हाल 0x1080:		/* VIR */
		retval = opp->vir;
		अवरोध;
	हाल 0x1090:		/* PIR */
		retval = 0x00000000;
		अवरोध;
	हाल 0x00:		/* Block Revision Register1 (BRR1) */
		retval = opp->brr1;
		अवरोध;
	हाल 0x40:
	हाल 0x50:
	हाल 0x60:
	हाल 0x70:
	हाल 0x80:
	हाल 0x90:
	हाल 0xA0:
	हाल 0xB0:
		err = खोलोpic_cpu_पढ़ो_पूर्णांकernal(opp, addr,
			&retval, get_current_cpu());
		अवरोध;
	हाल 0x10A0:		/* IPI_IVPR */
	हाल 0x10B0:
	हाल 0x10C0:
	हाल 0x10D0:
		अणु
			पूर्णांक idx;
			idx = (addr - 0x10A0) >> 4;
			retval = पढ़ो_IRQreg_ivpr(opp, opp->irq_ipi0 + idx);
		पूर्ण
		अवरोध;
	हाल 0x10E0:		/* SPVE */
		retval = opp->spve;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	pr_debug("%s: => 0x%08x\n", __func__, retval);
	*ptr = retval;
	वापस err;
पूर्ण

अटल पूर्णांक खोलोpic_पंचांगr_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	काष्ठा खोलोpic *opp = opaque;
	पूर्णांक idx;

	addr += 0x10f0;

	pr_debug("%s: addr %#llx <= %08x\n", __func__, addr, val);
	अगर (addr & 0xF)
		वापस 0;

	अगर (addr == 0x10f0) अणु
		/* TFRR */
		opp->tfrr = val;
		वापस 0;
	पूर्ण

	idx = (addr >> 6) & 0x3;
	addr = addr & 0x30;

	चयन (addr & 0x30) अणु
	हाल 0x00:		/* TCCR */
		अवरोध;
	हाल 0x10:		/* TBCR */
		अगर ((opp->समयrs[idx].tccr & TCCR_TOG) != 0 &&
		    (val & TBCR_CI) == 0 &&
		    (opp->समयrs[idx].tbcr & TBCR_CI) != 0)
			opp->समयrs[idx].tccr &= ~TCCR_TOG;

		opp->समयrs[idx].tbcr = val;
		अवरोध;
	हाल 0x20:		/* TVPR */
		ग_लिखो_IRQreg_ivpr(opp, opp->irq_tim0 + idx, val);
		अवरोध;
	हाल 0x30:		/* TDR */
		ग_लिखो_IRQreg_idr(opp, opp->irq_tim0 + idx, val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_पंचांगr_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	काष्ठा खोलोpic *opp = opaque;
	uपूर्णांक32_t retval = -1;
	पूर्णांक idx;

	pr_debug("%s: addr %#llx\n", __func__, addr);
	अगर (addr & 0xF)
		जाओ out;

	idx = (addr >> 6) & 0x3;
	अगर (addr == 0x0) अणु
		/* TFRR */
		retval = opp->tfrr;
		जाओ out;
	पूर्ण

	चयन (addr & 0x30) अणु
	हाल 0x00:		/* TCCR */
		retval = opp->समयrs[idx].tccr;
		अवरोध;
	हाल 0x10:		/* TBCR */
		retval = opp->समयrs[idx].tbcr;
		अवरोध;
	हाल 0x20:		/* TIPV */
		retval = पढ़ो_IRQreg_ivpr(opp, opp->irq_tim0 + idx);
		अवरोध;
	हाल 0x30:		/* TIDE (TIDR) */
		retval = पढ़ो_IRQreg_idr(opp, opp->irq_tim0 + idx);
		अवरोध;
	पूर्ण

out:
	pr_debug("%s: => 0x%08x\n", __func__, retval);
	*ptr = retval;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_src_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	काष्ठा खोलोpic *opp = opaque;
	पूर्णांक idx;

	pr_debug("%s: addr %#llx <= %08x\n", __func__, addr, val);

	addr = addr & 0xffff;
	idx = addr >> 5;

	चयन (addr & 0x1f) अणु
	हाल 0x00:
		ग_लिखो_IRQreg_ivpr(opp, idx, val);
		अवरोध;
	हाल 0x10:
		ग_लिखो_IRQreg_idr(opp, idx, val);
		अवरोध;
	हाल 0x18:
		ग_लिखो_IRQreg_ilr(opp, idx, val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_src_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	काष्ठा खोलोpic *opp = opaque;
	uपूर्णांक32_t retval;
	पूर्णांक idx;

	pr_debug("%s: addr %#llx\n", __func__, addr);
	retval = 0xFFFFFFFF;

	addr = addr & 0xffff;
	idx = addr >> 5;

	चयन (addr & 0x1f) अणु
	हाल 0x00:
		retval = पढ़ो_IRQreg_ivpr(opp, idx);
		अवरोध;
	हाल 0x10:
		retval = पढ़ो_IRQreg_idr(opp, idx);
		अवरोध;
	हाल 0x18:
		retval = पढ़ो_IRQreg_ilr(opp, idx);
		अवरोध;
	पूर्ण

	pr_debug("%s: => 0x%08x\n", __func__, retval);
	*ptr = retval;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_msi_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	काष्ठा खोलोpic *opp = opaque;
	पूर्णांक idx = opp->irq_msi;
	पूर्णांक srs, ibs;

	pr_debug("%s: addr %#llx <= 0x%08x\n", __func__, addr, val);
	अगर (addr & 0xF)
		वापस 0;

	चयन (addr) अणु
	हाल MSIIR_OFFSET:
		srs = val >> MSIIR_SRS_SHIFT;
		idx += srs;
		ibs = (val & MSIIR_IBS_MASK) >> MSIIR_IBS_SHIFT;
		opp->msi[srs].msir |= 1 << ibs;
		खोलोpic_set_irq(opp, idx, 1);
		अवरोध;
	शेष:
		/* most रेजिस्टरs are पढ़ो-only, thus ignored */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_msi_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	काष्ठा खोलोpic *opp = opaque;
	uपूर्णांक32_t r = 0;
	पूर्णांक i, srs;

	pr_debug("%s: addr %#llx\n", __func__, addr);
	अगर (addr & 0xF)
		वापस -ENXIO;

	srs = addr >> 4;

	चयन (addr) अणु
	हाल 0x00:
	हाल 0x10:
	हाल 0x20:
	हाल 0x30:
	हाल 0x40:
	हाल 0x50:
	हाल 0x60:
	हाल 0x70:		/* MSIRs */
		r = opp->msi[srs].msir;
		/* Clear on पढ़ो */
		opp->msi[srs].msir = 0;
		खोलोpic_set_irq(opp, opp->irq_msi + srs, 0);
		अवरोध;
	हाल 0x120:		/* MSISR */
		क्रम (i = 0; i < MAX_MSI; i++)
			r |= (opp->msi[i].msir ? 1 : 0) << i;
		अवरोध;
	पूर्ण

	pr_debug("%s: => 0x%08x\n", __func__, r);
	*ptr = r;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_summary_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	uपूर्णांक32_t r = 0;

	pr_debug("%s: addr %#llx\n", __func__, addr);

	/* TODO: EISR/EIMR */

	*ptr = r;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_summary_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	pr_debug("%s: addr %#llx <= 0x%08x\n", __func__, addr, val);

	/* TODO: EISR/EIMR */
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_cpu_ग_लिखो_पूर्णांकernal(व्योम *opaque, gpa_t addr,
				      u32 val, पूर्णांक idx)
अणु
	काष्ठा खोलोpic *opp = opaque;
	काष्ठा irq_source *src;
	काष्ठा irq_dest *dst;
	पूर्णांक s_IRQ, n_IRQ;

	pr_debug("%s: cpu %d addr %#llx <= 0x%08x\n", __func__, idx,
		addr, val);

	अगर (idx < 0)
		वापस 0;

	अगर (addr & 0xF)
		वापस 0;

	dst = &opp->dst[idx];
	addr &= 0xFF0;
	चयन (addr) अणु
	हाल 0x40:		/* IPIDR */
	हाल 0x50:
	हाल 0x60:
	हाल 0x70:
		idx = (addr - 0x40) >> 4;
		/* we use IDE as mask which CPUs to deliver the IPI to still. */
		opp->src[opp->irq_ipi0 + idx].desपंचांगask |= val;
		खोलोpic_set_irq(opp, opp->irq_ipi0 + idx, 1);
		खोलोpic_set_irq(opp, opp->irq_ipi0 + idx, 0);
		अवरोध;
	हाल 0x80:		/* CTPR */
		dst->ctpr = val & 0x0000000F;

		pr_debug("%s: set CPU %d ctpr to %d, raised %d servicing %d\n",
			__func__, idx, dst->ctpr, dst->उठाओd.priority,
			dst->servicing.priority);

		अगर (dst->उठाओd.priority <= dst->ctpr) अणु
			pr_debug("%s: Lower OpenPIC INT output cpu %d due to ctpr\n",
				__func__, idx);
			mpic_irq_lower(opp, dst, ILR_INTTGT_INT);
		पूर्ण अन्यथा अगर (dst->उठाओd.priority > dst->servicing.priority) अणु
			pr_debug("%s: Raise OpenPIC INT output cpu %d irq %d\n",
				__func__, idx, dst->उठाओd.next);
			mpic_irq_उठाओ(opp, dst, ILR_INTTGT_INT);
		पूर्ण

		अवरोध;
	हाल 0x90:		/* WHOAMI */
		/* Read-only रेजिस्टर */
		अवरोध;
	हाल 0xA0:		/* IACK */
		/* Read-only रेजिस्टर */
		अवरोध;
	हाल 0xB0: अणु		/* EOI */
		पूर्णांक notअगरy_eoi;

		pr_debug("EOI\n");
		s_IRQ = IRQ_get_next(opp, &dst->servicing);

		अगर (s_IRQ < 0) अणु
			pr_debug("%s: EOI with no interrupt in service\n",
				__func__);
			अवरोध;
		पूर्ण

		IRQ_resetbit(&dst->servicing, s_IRQ);
		/* Notअगरy listeners that the IRQ is over */
		notअगरy_eoi = s_IRQ;
		/* Set up next servicing IRQ */
		s_IRQ = IRQ_get_next(opp, &dst->servicing);
		/* Check queued पूर्णांकerrupts. */
		n_IRQ = IRQ_get_next(opp, &dst->उठाओd);
		src = &opp->src[n_IRQ];
		अगर (n_IRQ != -1 &&
		    (s_IRQ == -1 ||
		     IVPR_PRIORITY(src->ivpr) > dst->servicing.priority)) अणु
			pr_debug("Raise OpenPIC INT output cpu %d irq %d\n",
				idx, n_IRQ);
			mpic_irq_उठाओ(opp, dst, ILR_INTTGT_INT);
		पूर्ण

		spin_unlock(&opp->lock);
		kvm_notअगरy_acked_irq(opp->kvm, 0, notअगरy_eoi);
		spin_lock(&opp->lock);

		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_cpu_ग_लिखो(व्योम *opaque, gpa_t addr, u32 val)
अणु
	काष्ठा खोलोpic *opp = opaque;

	वापस खोलोpic_cpu_ग_लिखो_पूर्णांकernal(opp, addr, val,
					 (addr & 0x1f000) >> 12);
पूर्ण

अटल uपूर्णांक32_t खोलोpic_iack(काष्ठा खोलोpic *opp, काष्ठा irq_dest *dst,
			     पूर्णांक cpu)
अणु
	काष्ठा irq_source *src;
	पूर्णांक retval, irq;

	pr_debug("Lower OpenPIC INT output\n");
	mpic_irq_lower(opp, dst, ILR_INTTGT_INT);

	irq = IRQ_get_next(opp, &dst->उठाओd);
	pr_debug("IACK: irq=%d\n", irq);

	अगर (irq == -1)
		/* No more पूर्णांकerrupt pending */
		वापस opp->spve;

	src = &opp->src[irq];
	अगर (!(src->ivpr & IVPR_ACTIVITY_MASK) ||
	    !(IVPR_PRIORITY(src->ivpr) > dst->ctpr)) अणु
		pr_err("%s: bad raised IRQ %d ctpr %d ivpr 0x%08x\n",
			__func__, irq, dst->ctpr, src->ivpr);
		खोलोpic_update_irq(opp, irq);
		retval = opp->spve;
	पूर्ण अन्यथा अणु
		/* IRQ enter servicing state */
		IRQ_setbit(&dst->servicing, irq);
		retval = IVPR_VECTOR(opp, src->ivpr);
	पूर्ण

	अगर (!src->level) अणु
		/* edge-sensitive IRQ */
		src->ivpr &= ~IVPR_ACTIVITY_MASK;
		src->pending = 0;
		IRQ_resetbit(&dst->उठाओd, irq);
	पूर्ण

	अगर ((irq >= opp->irq_ipi0) && (irq < (opp->irq_ipi0 + MAX_IPI))) अणु
		src->desपंचांगask &= ~(1 << cpu);
		अगर (src->desपंचांगask && !src->level) अणु
			/* trigger on CPUs that didn't know about it yet */
			खोलोpic_set_irq(opp, irq, 1);
			खोलोpic_set_irq(opp, irq, 0);
			/* अगर all CPUs knew about it, set active bit again */
			src->ivpr |= IVPR_ACTIVITY_MASK;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

व्योम kvmppc_mpic_set_epr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा खोलोpic *opp = vcpu->arch.mpic;
	पूर्णांक cpu = vcpu->arch.irq_cpu_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&opp->lock, flags);

	अगर ((opp->gcr & opp->mpic_mode_mask) == GCR_MODE_PROXY)
		kvmppc_set_epr(vcpu, खोलोpic_iack(opp, &opp->dst[cpu], cpu));

	spin_unlock_irqrestore(&opp->lock, flags);
पूर्ण

अटल पूर्णांक खोलोpic_cpu_पढ़ो_पूर्णांकernal(व्योम *opaque, gpa_t addr,
				     u32 *ptr, पूर्णांक idx)
अणु
	काष्ठा खोलोpic *opp = opaque;
	काष्ठा irq_dest *dst;
	uपूर्णांक32_t retval;

	pr_debug("%s: cpu %d addr %#llx\n", __func__, idx, addr);
	retval = 0xFFFFFFFF;

	अगर (idx < 0)
		जाओ out;

	अगर (addr & 0xF)
		जाओ out;

	dst = &opp->dst[idx];
	addr &= 0xFF0;
	चयन (addr) अणु
	हाल 0x80:		/* CTPR */
		retval = dst->ctpr;
		अवरोध;
	हाल 0x90:		/* WHOAMI */
		retval = idx;
		अवरोध;
	हाल 0xA0:		/* IACK */
		retval = खोलोpic_iack(opp, dst, idx);
		अवरोध;
	हाल 0xB0:		/* EOI */
		retval = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	pr_debug("%s: => 0x%08x\n", __func__, retval);

out:
	*ptr = retval;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलोpic_cpu_पढ़ो(व्योम *opaque, gpa_t addr, u32 *ptr)
अणु
	काष्ठा खोलोpic *opp = opaque;

	वापस खोलोpic_cpu_पढ़ो_पूर्णांकernal(opp, addr, ptr,
					 (addr & 0x1f000) >> 12);
पूर्ण

काष्ठा mem_reg अणु
	पूर्णांक (*पढ़ो)(व्योम *opaque, gpa_t addr, u32 *ptr);
	पूर्णांक (*ग_लिखो)(व्योम *opaque, gpa_t addr, u32 val);
	gpa_t start_addr;
	पूर्णांक size;
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_gbl_mmio = अणु
	.ग_लिखो = खोलोpic_gbl_ग_लिखो,
	.पढ़ो = खोलोpic_gbl_पढ़ो,
	.start_addr = OPENPIC_GLB_REG_START,
	.size = OPENPIC_GLB_REG_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_पंचांगr_mmio = अणु
	.ग_लिखो = खोलोpic_पंचांगr_ग_लिखो,
	.पढ़ो = खोलोpic_पंचांगr_पढ़ो,
	.start_addr = OPENPIC_TMR_REG_START,
	.size = OPENPIC_TMR_REG_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_cpu_mmio = अणु
	.ग_लिखो = खोलोpic_cpu_ग_लिखो,
	.पढ़ो = खोलोpic_cpu_पढ़ो,
	.start_addr = OPENPIC_CPU_REG_START,
	.size = OPENPIC_CPU_REG_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_src_mmio = अणु
	.ग_लिखो = खोलोpic_src_ग_लिखो,
	.पढ़ो = खोलोpic_src_पढ़ो,
	.start_addr = OPENPIC_SRC_REG_START,
	.size = OPENPIC_SRC_REG_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_msi_mmio = अणु
	.पढ़ो = खोलोpic_msi_पढ़ो,
	.ग_लिखो = खोलोpic_msi_ग_लिखो,
	.start_addr = OPENPIC_MSI_REG_START,
	.size = OPENPIC_MSI_REG_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mem_reg खोलोpic_summary_mmio = अणु
	.पढ़ो = खोलोpic_summary_पढ़ो,
	.ग_लिखो = खोलोpic_summary_ग_लिखो,
	.start_addr = OPENPIC_SUMMARY_REG_START,
	.size = OPENPIC_SUMMARY_REG_SIZE,
पूर्ण;

अटल व्योम add_mmio_region(काष्ठा खोलोpic *opp, स्थिर काष्ठा mem_reg *mr)
अणु
	अगर (opp->num_mmio_regions >= MAX_MMIO_REGIONS) अणु
		WARN(1, "kvm mpic: too many mmio regions\n");
		वापस;
	पूर्ण

	opp->mmio_regions[opp->num_mmio_regions++] = mr;
पूर्ण

अटल व्योम fsl_common_init(काष्ठा खोलोpic *opp)
अणु
	पूर्णांक i;
	पूर्णांक virq = MAX_SRC;

	add_mmio_region(opp, &खोलोpic_msi_mmio);
	add_mmio_region(opp, &खोलोpic_summary_mmio);

	opp->vid = VID_REVISION_1_2;
	opp->vir = VIR_GENERIC;
	opp->vector_mask = 0xFFFF;
	opp->tfrr_reset = 0;
	opp->ivpr_reset = IVPR_MASK_MASK;
	opp->idr_reset = 1 << 0;
	opp->max_irq = MAX_IRQ;

	opp->irq_ipi0 = virq;
	virq += MAX_IPI;
	opp->irq_tim0 = virq;
	virq += MAX_TMR;

	BUG_ON(virq > MAX_IRQ);

	opp->irq_msi = 224;

	क्रम (i = 0; i < opp->fsl->max_ext; i++)
		opp->src[i].level = false;

	/* Internal पूर्णांकerrupts, including message and MSI */
	क्रम (i = 16; i < MAX_SRC; i++) अणु
		opp->src[i].type = IRQ_TYPE_FSLINT;
		opp->src[i].level = true;
	पूर्ण

	/* समयrs and IPIs */
	क्रम (i = MAX_SRC; i < virq; i++) अणु
		opp->src[i].type = IRQ_TYPE_FSLSPECIAL;
		opp->src[i].level = false;
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_mpic_पढ़ो_पूर्णांकernal(काष्ठा खोलोpic *opp, gpa_t addr, u32 *ptr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < opp->num_mmio_regions; i++) अणु
		स्थिर काष्ठा mem_reg *mr = opp->mmio_regions[i];

		अगर (mr->start_addr > addr || addr >= mr->start_addr + mr->size)
			जारी;

		वापस mr->पढ़ो(opp, addr - mr->start_addr, ptr);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvm_mpic_ग_लिखो_पूर्णांकernal(काष्ठा खोलोpic *opp, gpa_t addr, u32 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < opp->num_mmio_regions; i++) अणु
		स्थिर काष्ठा mem_reg *mr = opp->mmio_regions[i];

		अगर (mr->start_addr > addr || addr >= mr->start_addr + mr->size)
			जारी;

		वापस mr->ग_लिखो(opp, addr - mr->start_addr, val);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvm_mpic_पढ़ो(काष्ठा kvm_vcpu *vcpu,
			 काष्ठा kvm_io_device *this,
			 gpa_t addr, पूर्णांक len, व्योम *ptr)
अणु
	काष्ठा खोलोpic *opp = container_of(this, काष्ठा खोलोpic, mmio);
	पूर्णांक ret;
	जोड़ अणु
		u32 val;
		u8 bytes[4];
	पूर्ण u;

	अगर (addr & (len - 1)) अणु
		pr_debug("%s: bad alignment %llx/%d\n",
			 __func__, addr, len);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&opp->lock);
	ret = kvm_mpic_पढ़ो_पूर्णांकernal(opp, addr - opp->reg_base, &u.val);
	spin_unlock_irq(&opp->lock);

	/*
	 * Technically only 32-bit accesses are allowed, but be nice to
	 * people dumping रेजिस्टरs a byte at a समय -- it works in real
	 * hardware (पढ़ोs only, not ग_लिखोs).
	 */
	अगर (len == 4) अणु
		*(u32 *)ptr = u.val;
		pr_debug("%s: addr %llx ret %d len 4 val %x\n",
			 __func__, addr, ret, u.val);
	पूर्ण अन्यथा अगर (len == 1) अणु
		*(u8 *)ptr = u.bytes[addr & 3];
		pr_debug("%s: addr %llx ret %d len 1 val %x\n",
			 __func__, addr, ret, u.bytes[addr & 3]);
	पूर्ण अन्यथा अणु
		pr_debug("%s: bad length %d\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_mpic_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
			  काष्ठा kvm_io_device *this,
			  gpa_t addr, पूर्णांक len, स्थिर व्योम *ptr)
अणु
	काष्ठा खोलोpic *opp = container_of(this, काष्ठा खोलोpic, mmio);
	पूर्णांक ret;

	अगर (len != 4) अणु
		pr_debug("%s: bad length %d\n", __func__, len);
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (addr & 3) अणु
		pr_debug("%s: bad alignment %llx/%d\n", __func__, addr, len);
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_irq(&opp->lock);
	ret = kvm_mpic_ग_लिखो_पूर्णांकernal(opp, addr - opp->reg_base,
				      *(स्थिर u32 *)ptr);
	spin_unlock_irq(&opp->lock);

	pr_debug("%s: addr %llx ret %d val %x\n",
		 __func__, addr, ret, *(स्थिर u32 *)ptr);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops mpic_mmio_ops = अणु
	.पढ़ो = kvm_mpic_पढ़ो,
	.ग_लिखो = kvm_mpic_ग_लिखो,
पूर्ण;

अटल व्योम map_mmio(काष्ठा खोलोpic *opp)
अणु
	kvm_iodevice_init(&opp->mmio, &mpic_mmio_ops);

	kvm_io_bus_रेजिस्टर_dev(opp->kvm, KVM_MMIO_BUS,
				opp->reg_base, OPENPIC_REG_SIZE,
				&opp->mmio);
पूर्ण

अटल व्योम unmap_mmio(काष्ठा खोलोpic *opp)
अणु
	kvm_io_bus_unरेजिस्टर_dev(opp->kvm, KVM_MMIO_BUS, &opp->mmio);
पूर्ण

अटल पूर्णांक set_base_addr(काष्ठा खोलोpic *opp, काष्ठा kvm_device_attr *attr)
अणु
	u64 base;

	अगर (copy_from_user(&base, (u64 __user *)(दीर्घ)attr->addr, माप(u64)))
		वापस -EFAULT;

	अगर (base & 0x3ffff) अणु
		pr_debug("kvm mpic %s: KVM_DEV_MPIC_BASE_ADDR %08llx not aligned\n",
			 __func__, base);
		वापस -EINVAL;
	पूर्ण

	अगर (base == opp->reg_base)
		वापस 0;

	mutex_lock(&opp->kvm->slots_lock);

	unmap_mmio(opp);
	opp->reg_base = base;

	pr_debug("kvm mpic %s: KVM_DEV_MPIC_BASE_ADDR %08llx\n",
		 __func__, base);

	अगर (base == 0)
		जाओ out;

	map_mmio(opp);

out:
	mutex_unlock(&opp->kvm->slots_lock);
	वापस 0;
पूर्ण

#घोषणा ATTR_SET		0
#घोषणा ATTR_GET		1

अटल पूर्णांक access_reg(काष्ठा खोलोpic *opp, gpa_t addr, u32 *val, पूर्णांक type)
अणु
	पूर्णांक ret;

	अगर (addr & 3)
		वापस -ENXIO;

	spin_lock_irq(&opp->lock);

	अगर (type == ATTR_SET)
		ret = kvm_mpic_ग_लिखो_पूर्णांकernal(opp, addr, *val);
	अन्यथा
		ret = kvm_mpic_पढ़ो_पूर्णांकernal(opp, addr, val);

	spin_unlock_irq(&opp->lock);

	pr_debug("%s: type %d addr %llx val %x\n", __func__, type, addr, *val);

	वापस ret;
पूर्ण

अटल पूर्णांक mpic_set_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा खोलोpic *opp = dev->निजी;
	u32 attr32;

	चयन (attr->group) अणु
	हाल KVM_DEV_MPIC_GRP_MISC:
		चयन (attr->attr) अणु
		हाल KVM_DEV_MPIC_BASE_ADDR:
			वापस set_base_addr(opp, attr);
		पूर्ण

		अवरोध;

	हाल KVM_DEV_MPIC_GRP_REGISTER:
		अगर (get_user(attr32, (u32 __user *)(दीर्घ)attr->addr))
			वापस -EFAULT;

		वापस access_reg(opp, attr->attr, &attr32, ATTR_SET);

	हाल KVM_DEV_MPIC_GRP_IRQ_ACTIVE:
		अगर (attr->attr > MAX_SRC)
			वापस -EINVAL;

		अगर (get_user(attr32, (u32 __user *)(दीर्घ)attr->addr))
			वापस -EFAULT;

		अगर (attr32 != 0 && attr32 != 1)
			वापस -EINVAL;

		spin_lock_irq(&opp->lock);
		खोलोpic_set_irq(opp, attr->attr, attr32);
		spin_unlock_irq(&opp->lock);
		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक mpic_get_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा खोलोpic *opp = dev->निजी;
	u64 attr64;
	u32 attr32;
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_MPIC_GRP_MISC:
		चयन (attr->attr) अणु
		हाल KVM_DEV_MPIC_BASE_ADDR:
			mutex_lock(&opp->kvm->slots_lock);
			attr64 = opp->reg_base;
			mutex_unlock(&opp->kvm->slots_lock);

			अगर (copy_to_user((u64 __user *)(दीर्घ)attr->addr,
					 &attr64, माप(u64)))
				वापस -EFAULT;

			वापस 0;
		पूर्ण

		अवरोध;

	हाल KVM_DEV_MPIC_GRP_REGISTER:
		ret = access_reg(opp, attr->attr, &attr32, ATTR_GET);
		अगर (ret)
			वापस ret;

		अगर (put_user(attr32, (u32 __user *)(दीर्घ)attr->addr))
			वापस -EFAULT;

		वापस 0;

	हाल KVM_DEV_MPIC_GRP_IRQ_ACTIVE:
		अगर (attr->attr > MAX_SRC)
			वापस -EINVAL;

		spin_lock_irq(&opp->lock);
		attr32 = opp->src[attr->attr].pending;
		spin_unlock_irq(&opp->lock);

		अगर (put_user(attr32, (u32 __user *)(दीर्घ)attr->addr))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक mpic_has_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_MPIC_GRP_MISC:
		चयन (attr->attr) अणु
		हाल KVM_DEV_MPIC_BASE_ADDR:
			वापस 0;
		पूर्ण

		अवरोध;

	हाल KVM_DEV_MPIC_GRP_REGISTER:
		वापस 0;

	हाल KVM_DEV_MPIC_GRP_IRQ_ACTIVE:
		अगर (attr->attr > MAX_SRC)
			अवरोध;

		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल व्योम mpic_destroy(काष्ठा kvm_device *dev)
अणु
	काष्ठा खोलोpic *opp = dev->निजी;

	dev->kvm->arch.mpic = शून्य;
	kमुक्त(opp);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक mpic_set_शेष_irq_routing(काष्ठा खोलोpic *opp)
अणु
	काष्ठा kvm_irq_routing_entry *routing;

	/* Create a nop शेष map, so that dereferencing it still works */
	routing = kzalloc((माप(*routing)), GFP_KERNEL);
	अगर (!routing)
		वापस -ENOMEM;

	kvm_set_irq_routing(opp->kvm, routing, 0, 0);

	kमुक्त(routing);
	वापस 0;
पूर्ण

अटल पूर्णांक mpic_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा खोलोpic *opp;
	पूर्णांक ret;

	/* We only support one MPIC at a समय क्रम now */
	अगर (dev->kvm->arch.mpic)
		वापस -EINVAL;

	opp = kzalloc(माप(काष्ठा खोलोpic), GFP_KERNEL);
	अगर (!opp)
		वापस -ENOMEM;

	dev->निजी = opp;
	opp->kvm = dev->kvm;
	opp->dev = dev;
	opp->model = type;
	spin_lock_init(&opp->lock);

	add_mmio_region(opp, &खोलोpic_gbl_mmio);
	add_mmio_region(opp, &खोलोpic_पंचांगr_mmio);
	add_mmio_region(opp, &खोलोpic_src_mmio);
	add_mmio_region(opp, &खोलोpic_cpu_mmio);

	चयन (opp->model) अणु
	हाल KVM_DEV_TYPE_FSL_MPIC_20:
		opp->fsl = &fsl_mpic_20;
		opp->brr1 = 0x00400200;
		opp->flags |= OPENPIC_FLAG_IDR_CRIT;
		opp->nb_irqs = 80;
		opp->mpic_mode_mask = GCR_MODE_MIXED;

		fsl_common_init(opp);

		अवरोध;

	हाल KVM_DEV_TYPE_FSL_MPIC_42:
		opp->fsl = &fsl_mpic_42;
		opp->brr1 = 0x00400402;
		opp->flags |= OPENPIC_FLAG_ILR;
		opp->nb_irqs = 196;
		opp->mpic_mode_mask = GCR_MODE_PROXY;

		fsl_common_init(opp);

		अवरोध;

	शेष:
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = mpic_set_शेष_irq_routing(opp);
	अगर (ret)
		जाओ err;

	खोलोpic_reset(opp);

	smp_wmb();
	dev->kvm->arch.mpic = opp;

	वापस 0;

err:
	kमुक्त(opp);
	वापस ret;
पूर्ण

काष्ठा kvm_device_ops kvm_mpic_ops = अणु
	.name = "kvm-mpic",
	.create = mpic_create,
	.destroy = mpic_destroy,
	.set_attr = mpic_set_attr,
	.get_attr = mpic_get_attr,
	.has_attr = mpic_has_attr,
पूर्ण;

पूर्णांक kvmppc_mpic_connect_vcpu(काष्ठा kvm_device *dev, काष्ठा kvm_vcpu *vcpu,
			     u32 cpu)
अणु
	काष्ठा खोलोpic *opp = dev->निजी;
	पूर्णांक ret = 0;

	अगर (dev->ops != &kvm_mpic_ops)
		वापस -EPERM;
	अगर (opp->kvm != vcpu->kvm)
		वापस -EPERM;
	अगर (cpu < 0 || cpu >= MAX_CPU)
		वापस -EPERM;

	spin_lock_irq(&opp->lock);

	अगर (opp->dst[cpu].vcpu) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण
	अगर (vcpu->arch.irq_type) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	opp->dst[cpu].vcpu = vcpu;
	opp->nb_cpus = max(opp->nb_cpus, cpu + 1);

	vcpu->arch.mpic = opp;
	vcpu->arch.irq_cpu_id = cpu;
	vcpu->arch.irq_type = KVMPPC_IRQ_MPIC;

	/* This might need to be changed अगर GCR माला_लो extended */
	अगर (opp->mpic_mode_mask == GCR_MODE_PROXY)
		vcpu->arch.epr_flags |= KVMPPC_EPR_KERNEL;

out:
	spin_unlock_irq(&opp->lock);
	वापस ret;
पूर्ण

/*
 * This should only happen immediately beक्रमe the mpic is destroyed,
 * so we shouldn't need to worry about anything still trying to
 * access the vcpu poपूर्णांकer.
 */
व्योम kvmppc_mpic_disconnect_vcpu(काष्ठा खोलोpic *opp, काष्ठा kvm_vcpu *vcpu)
अणु
	BUG_ON(!opp->dst[vcpu->arch.irq_cpu_id].vcpu);

	opp->dst[vcpu->arch.irq_cpu_id].vcpu = शून्य;
पूर्ण

/*
 * Return value:
 *  < 0   Interrupt was ignored (masked or not delivered क्रम other reasons)
 *  = 0   Interrupt was coalesced (previous irq is still pending)
 *  > 0   Number of CPUs पूर्णांकerrupt was delivered to
 */
अटल पूर्णांक mpic_set_irq(काष्ठा kvm_kernel_irq_routing_entry *e,
			काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			bool line_status)
अणु
	u32 irq = e->irqchip.pin;
	काष्ठा खोलोpic *opp = kvm->arch.mpic;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&opp->lock, flags);
	खोलोpic_set_irq(opp, irq, level);
	spin_unlock_irqrestore(&opp->lock, flags);

	/* All code paths we care about करोn't check क्रम the वापस value */
	वापस 0;
पूर्ण

पूर्णांक kvm_set_msi(काष्ठा kvm_kernel_irq_routing_entry *e,
		काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level, bool line_status)
अणु
	काष्ठा खोलोpic *opp = kvm->arch.mpic;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&opp->lock, flags);

	/*
	 * XXX We ignore the target address क्रम now, as we only support
	 *     a single MSI bank.
	 */
	खोलोpic_msi_ग_लिखो(kvm->arch.mpic, MSIIR_OFFSET, e->msi.data);
	spin_unlock_irqrestore(&opp->lock, flags);

	/* All code paths we care about करोn't check क्रम the वापस value */
	वापस 0;
पूर्ण

पूर्णांक kvm_set_routing_entry(काष्ठा kvm *kvm,
			  काष्ठा kvm_kernel_irq_routing_entry *e,
			  स्थिर काष्ठा kvm_irq_routing_entry *ue)
अणु
	पूर्णांक r = -EINVAL;

	चयन (ue->type) अणु
	हाल KVM_IRQ_ROUTING_IRQCHIP:
		e->set = mpic_set_irq;
		e->irqchip.irqchip = ue->u.irqchip.irqchip;
		e->irqchip.pin = ue->u.irqchip.pin;
		अगर (e->irqchip.pin >= KVM_IRQCHIP_NUM_PINS)
			जाओ out;
		अवरोध;
	हाल KVM_IRQ_ROUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.address_lo = ue->u.msi.address_lo;
		e->msi.address_hi = ue->u.msi.address_hi;
		e->msi.data = ue->u.msi.data;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	r = 0;
out:
	वापस r;
पूर्ण
