<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  icu.c, Interrupt Control Unit routines क्रम the NEC VR4100 series.
 *
 *  Copyright (C) 2001-2002  MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2003-2006  Yoichi Yuasa <yuasa@linux-mips.org>
 */
/*
 * Changes:
 *  MontaVista Software Inc. <source@mvista.com>
 *  - New creation, NEC VR4122 and VR4131 are supported.
 *  - Added support क्रम NEC VR4111 and VR4121.
 *
 *  Yoichi Yuasa <yuasa@linux-mips.org>
 *  - Coped with INTASSIGN of NEC VR4133.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vr41xx/irq.h>
#समावेश <यंत्र/vr41xx/vr41xx.h>

अटल व्योम __iomem *icu1_base;
अटल व्योम __iomem *icu2_base;

अटल अचिन्हित अक्षर sysपूर्णांक1_assign[16] = अणु
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर sysपूर्णांक2_assign[16] = अणु
	2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

#घोषणा ICU1_TYPE1_BASE 0x0b000080UL
#घोषणा ICU2_TYPE1_BASE 0x0b000200UL

#घोषणा ICU1_TYPE2_BASE 0x0f000080UL
#घोषणा ICU2_TYPE2_BASE 0x0f0000a0UL

#घोषणा ICU1_SIZE	0x20
#घोषणा ICU2_SIZE	0x1c

#घोषणा SYSINT1REG	0x00
#घोषणा PIUINTREG	0x02
#घोषणा INTASSIGN0	0x04
#घोषणा INTASSIGN1	0x06
#घोषणा GIUINTLREG	0x08
#घोषणा DSIUINTREG	0x0a
#घोषणा MSYSINT1REG	0x0c
#घोषणा MPIUINTREG	0x0e
#घोषणा MAIUINTREG	0x10
#घोषणा MKIUINTREG	0x12
#घोषणा MMACINTREG	0x12
#घोषणा MGIUINTLREG	0x14
#घोषणा MDSIUINTREG	0x16
#घोषणा NMIREG		0x18
#घोषणा SOFTREG		0x1a
#घोषणा INTASSIGN2	0x1c
#घोषणा INTASSIGN3	0x1e

#घोषणा SYSINT2REG	0x00
#घोषणा GIUINTHREG	0x02
#घोषणा FIRINTREG	0x04
#घोषणा MSYSINT2REG	0x06
#घोषणा MGIUINTHREG	0x08
#घोषणा MFIRINTREG	0x0a
#घोषणा PCIINTREG	0x0c
 #घोषणा PCIINT0	0x0001
#घोषणा SCUINTREG	0x0e
 #घोषणा SCUINT0	0x0001
#घोषणा CSIINTREG	0x10
#घोषणा MPCIINTREG	0x12
#घोषणा MSCUINTREG	0x14
#घोषणा MCSIINTREG	0x16
#घोषणा BCUINTREG	0x18
 #घोषणा BCUINTR	0x0001
#घोषणा MBCUINTREG	0x1a

#घोषणा SYSINT1_IRQ_TO_PIN(x)	((x) - SYSINT1_IRQ_BASE)	/* Pin 0-15 */
#घोषणा SYSINT2_IRQ_TO_PIN(x)	((x) - SYSINT2_IRQ_BASE)	/* Pin 0-15 */

#घोषणा INT_TO_IRQ(x)		((x) + 2)	/* Int0-4 -> IRQ2-6 */

#घोषणा icu1_पढ़ो(offset)		पढ़ोw(icu1_base + (offset))
#घोषणा icu1_ग_लिखो(offset, value)	ग_लिखोw((value), icu1_base + (offset))

#घोषणा icu2_पढ़ो(offset)		पढ़ोw(icu2_base + (offset))
#घोषणा icu2_ग_लिखो(offset, value)	ग_लिखोw((value), icu2_base + (offset))

#घोषणा INTASSIGN_MAX	4
#घोषणा INTASSIGN_MASK	0x0007

अटल अंतरभूत uपूर्णांक16_t icu1_set(uपूर्णांक8_t offset, uपूर्णांक16_t set)
अणु
	uपूर्णांक16_t data;

	data = icu1_पढ़ो(offset);
	data |= set;
	icu1_ग_लिखो(offset, data);

	वापस data;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t icu1_clear(uपूर्णांक8_t offset, uपूर्णांक16_t clear)
अणु
	uपूर्णांक16_t data;

	data = icu1_पढ़ो(offset);
	data &= ~clear;
	icu1_ग_लिखो(offset, data);

	वापस data;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t icu2_set(uपूर्णांक8_t offset, uपूर्णांक16_t set)
अणु
	uपूर्णांक16_t data;

	data = icu2_पढ़ो(offset);
	data |= set;
	icu2_ग_लिखो(offset, data);

	वापस data;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t icu2_clear(uपूर्णांक8_t offset, uपूर्णांक16_t clear)
अणु
	uपूर्णांक16_t data;

	data = icu2_पढ़ो(offset);
	data &= ~clear;
	icu2_ग_लिखो(offset, data);

	वापस data;
पूर्ण

व्योम vr41xx_enable_piuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(PIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_set(MPIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_piuपूर्णांक);

व्योम vr41xx_disable_piuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(PIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_clear(MPIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_piuपूर्णांक);

व्योम vr41xx_enable_aiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(AIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_set(MAIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_aiuपूर्णांक);

व्योम vr41xx_disable_aiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(AIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_clear(MAIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_aiuपूर्णांक);

व्योम vr41xx_enable_kiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(KIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_set(MKIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_kiuपूर्णांक);

व्योम vr41xx_disable_kiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(KIU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4111 ||
	    current_cpu_type() == CPU_VR4121) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu1_clear(MKIUINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_kiuपूर्णांक);

व्योम vr41xx_enable_macपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(ETHERNET_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu1_set(MMACINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_macपूर्णांक);

व्योम vr41xx_disable_macपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(ETHERNET_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu1_clear(MMACINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_macपूर्णांक);

व्योम vr41xx_enable_dsiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(DSIU_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu1_set(MDSIUINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_dsiuपूर्णांक);

व्योम vr41xx_disable_dsiuपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(DSIU_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu1_clear(MDSIUINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_dsiuपूर्णांक);

व्योम vr41xx_enable_firपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(FIR_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu2_set(MFIRINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_firपूर्णांक);

व्योम vr41xx_disable_firपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(FIR_IRQ);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	icu2_clear(MFIRINTREG, mask);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_firपूर्णांक);

व्योम vr41xx_enable_pciपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(PCI_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MPCIINTREG, PCIINT0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_pciपूर्णांक);

व्योम vr41xx_disable_pciपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(PCI_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MPCIINTREG, 0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_pciपूर्णांक);

व्योम vr41xx_enable_scuपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(SCU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MSCUINTREG, SCUINT0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_scuपूर्णांक);

व्योम vr41xx_disable_scuपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(SCU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MSCUINTREG, 0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_scuपूर्णांक);

व्योम vr41xx_enable_csiपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(CSI_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_set(MCSIINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_csiपूर्णांक);

व्योम vr41xx_disable_csiपूर्णांक(uपूर्णांक16_t mask)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(CSI_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_clear(MCSIINTREG, mask);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_csiपूर्णांक);

व्योम vr41xx_enable_bcuपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(BCU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MBCUINTREG, BCUINTR);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_enable_bcuपूर्णांक);

व्योम vr41xx_disable_bcuपूर्णांक(व्योम)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(BCU_IRQ);
	अचिन्हित दीर्घ flags;

	अगर (current_cpu_type() == CPU_VR4122 ||
	    current_cpu_type() == CPU_VR4131 ||
	    current_cpu_type() == CPU_VR4133) अणु
		raw_spin_lock_irqsave(&desc->lock, flags);
		icu2_ग_लिखो(MBCUINTREG, 0);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vr41xx_disable_bcuपूर्णांक);

अटल व्योम disable_sysपूर्णांक1_irq(काष्ठा irq_data *d)
अणु
	icu1_clear(MSYSINT1REG, 1 << SYSINT1_IRQ_TO_PIN(d->irq));
पूर्ण

अटल व्योम enable_sysपूर्णांक1_irq(काष्ठा irq_data *d)
अणु
	icu1_set(MSYSINT1REG, 1 << SYSINT1_IRQ_TO_PIN(d->irq));
पूर्ण

अटल काष्ठा irq_chip sysपूर्णांक1_irq_type = अणु
	.name		= "SYSINT1",
	.irq_mask	= disable_sysपूर्णांक1_irq,
	.irq_unmask	= enable_sysपूर्णांक1_irq,
पूर्ण;

अटल व्योम disable_sysपूर्णांक2_irq(काष्ठा irq_data *d)
अणु
	icu2_clear(MSYSINT2REG, 1 << SYSINT2_IRQ_TO_PIN(d->irq));
पूर्ण

अटल व्योम enable_sysपूर्णांक2_irq(काष्ठा irq_data *d)
अणु
	icu2_set(MSYSINT2REG, 1 << SYSINT2_IRQ_TO_PIN(d->irq));
पूर्ण

अटल काष्ठा irq_chip sysपूर्णांक2_irq_type = अणु
	.name		= "SYSINT2",
	.irq_mask	= disable_sysपूर्णांक2_irq,
	.irq_unmask	= enable_sysपूर्णांक2_irq,
पूर्ण;

अटल अंतरभूत पूर्णांक set_sysपूर्णांक1_assign(अचिन्हित पूर्णांक irq, अचिन्हित अक्षर assign)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	uपूर्णांक16_t पूर्णांकassign0, पूर्णांकassign1;
	अचिन्हित पूर्णांक pin;

	pin = SYSINT1_IRQ_TO_PIN(irq);

	raw_spin_lock_irq(&desc->lock);

	पूर्णांकassign0 = icu1_पढ़ो(INTASSIGN0);
	पूर्णांकassign1 = icu1_पढ़ो(INTASSIGN1);

	चयन (pin) अणु
	हाल 0:
		पूर्णांकassign0 &= ~INTASSIGN_MASK;
		पूर्णांकassign0 |= (uपूर्णांक16_t)assign;
		अवरोध;
	हाल 1:
		पूर्णांकassign0 &= ~(INTASSIGN_MASK << 3);
		पूर्णांकassign0 |= (uपूर्णांक16_t)assign << 3;
		अवरोध;
	हाल 2:
		पूर्णांकassign0 &= ~(INTASSIGN_MASK << 6);
		पूर्णांकassign0 |= (uपूर्णांक16_t)assign << 6;
		अवरोध;
	हाल 3:
		पूर्णांकassign0 &= ~(INTASSIGN_MASK << 9);
		पूर्णांकassign0 |= (uपूर्णांक16_t)assign << 9;
		अवरोध;
	हाल 8:
		पूर्णांकassign0 &= ~(INTASSIGN_MASK << 12);
		पूर्णांकassign0 |= (uपूर्णांक16_t)assign << 12;
		अवरोध;
	हाल 9:
		पूर्णांकassign1 &= ~INTASSIGN_MASK;
		पूर्णांकassign1 |= (uपूर्णांक16_t)assign;
		अवरोध;
	हाल 11:
		पूर्णांकassign1 &= ~(INTASSIGN_MASK << 6);
		पूर्णांकassign1 |= (uपूर्णांक16_t)assign << 6;
		अवरोध;
	हाल 12:
		पूर्णांकassign1 &= ~(INTASSIGN_MASK << 9);
		पूर्णांकassign1 |= (uपूर्णांक16_t)assign << 9;
		अवरोध;
	शेष:
		raw_spin_unlock_irq(&desc->lock);
		वापस -EINVAL;
	पूर्ण

	sysपूर्णांक1_assign[pin] = assign;
	icu1_ग_लिखो(INTASSIGN0, पूर्णांकassign0);
	icu1_ग_लिखो(INTASSIGN1, पूर्णांकassign1);

	raw_spin_unlock_irq(&desc->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_sysपूर्णांक2_assign(अचिन्हित पूर्णांक irq, अचिन्हित अक्षर assign)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	uपूर्णांक16_t पूर्णांकassign2, पूर्णांकassign3;
	अचिन्हित पूर्णांक pin;

	pin = SYSINT2_IRQ_TO_PIN(irq);

	raw_spin_lock_irq(&desc->lock);

	पूर्णांकassign2 = icu1_पढ़ो(INTASSIGN2);
	पूर्णांकassign3 = icu1_पढ़ो(INTASSIGN3);

	चयन (pin) अणु
	हाल 0:
		पूर्णांकassign2 &= ~INTASSIGN_MASK;
		पूर्णांकassign2 |= (uपूर्णांक16_t)assign;
		अवरोध;
	हाल 1:
		पूर्णांकassign2 &= ~(INTASSIGN_MASK << 3);
		पूर्णांकassign2 |= (uपूर्णांक16_t)assign << 3;
		अवरोध;
	हाल 3:
		पूर्णांकassign2 &= ~(INTASSIGN_MASK << 6);
		पूर्णांकassign2 |= (uपूर्णांक16_t)assign << 6;
		अवरोध;
	हाल 4:
		पूर्णांकassign2 &= ~(INTASSIGN_MASK << 9);
		पूर्णांकassign2 |= (uपूर्णांक16_t)assign << 9;
		अवरोध;
	हाल 5:
		पूर्णांकassign2 &= ~(INTASSIGN_MASK << 12);
		पूर्णांकassign2 |= (uपूर्णांक16_t)assign << 12;
		अवरोध;
	हाल 6:
		पूर्णांकassign3 &= ~INTASSIGN_MASK;
		पूर्णांकassign3 |= (uपूर्णांक16_t)assign;
		अवरोध;
	हाल 7:
		पूर्णांकassign3 &= ~(INTASSIGN_MASK << 3);
		पूर्णांकassign3 |= (uपूर्णांक16_t)assign << 3;
		अवरोध;
	हाल 8:
		पूर्णांकassign3 &= ~(INTASSIGN_MASK << 6);
		पूर्णांकassign3 |= (uपूर्णांक16_t)assign << 6;
		अवरोध;
	हाल 9:
		पूर्णांकassign3 &= ~(INTASSIGN_MASK << 9);
		पूर्णांकassign3 |= (uपूर्णांक16_t)assign << 9;
		अवरोध;
	हाल 10:
		पूर्णांकassign3 &= ~(INTASSIGN_MASK << 12);
		पूर्णांकassign3 |= (uपूर्णांक16_t)assign << 12;
		अवरोध;
	शेष:
		raw_spin_unlock_irq(&desc->lock);
		वापस -EINVAL;
	पूर्ण

	sysपूर्णांक2_assign[pin] = assign;
	icu1_ग_लिखो(INTASSIGN2, पूर्णांकassign2);
	icu1_ग_लिखो(INTASSIGN3, पूर्णांकassign3);

	raw_spin_unlock_irq(&desc->lock);

	वापस 0;
पूर्ण

पूर्णांक vr41xx_set_पूर्णांकassign(अचिन्हित पूर्णांक irq, अचिन्हित अक्षर पूर्णांकassign)
अणु
	पूर्णांक retval = -EINVAL;

	अगर (current_cpu_type() != CPU_VR4133)
		वापस -EINVAL;

	अगर (पूर्णांकassign > INTASSIGN_MAX)
		वापस -EINVAL;

	अगर (irq >= SYSINT1_IRQ_BASE && irq <= SYSINT1_IRQ_LAST)
		retval = set_sysपूर्णांक1_assign(irq, पूर्णांकassign);
	अन्यथा अगर (irq >= SYSINT2_IRQ_BASE && irq <= SYSINT2_IRQ_LAST)
		retval = set_sysपूर्णांक2_assign(irq, पूर्णांकassign);

	वापस retval;
पूर्ण

EXPORT_SYMBOL(vr41xx_set_पूर्णांकassign);

अटल पूर्णांक icu_get_irq(अचिन्हित पूर्णांक irq)
अणु
	uपूर्णांक16_t pend1, pend2;
	uपूर्णांक16_t mask1, mask2;
	पूर्णांक i;

	pend1 = icu1_पढ़ो(SYSINT1REG);
	mask1 = icu1_पढ़ो(MSYSINT1REG);

	pend2 = icu2_पढ़ो(SYSINT2REG);
	mask2 = icu2_पढ़ो(MSYSINT2REG);

	mask1 &= pend1;
	mask2 &= pend2;

	अगर (mask1) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (irq == INT_TO_IRQ(sysपूर्णांक1_assign[i]) && (mask1 & (1 << i)))
				वापस SYSINT1_IRQ(i);
		पूर्ण
	पूर्ण

	अगर (mask2) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (irq == INT_TO_IRQ(sysपूर्णांक2_assign[i]) && (mask2 & (1 << i)))
				वापस SYSINT2_IRQ(i);
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_ERR "spurious ICU interrupt: %04x,%04x\n", pend1, pend2);

	atomic_inc(&irq_err_count);

	वापस -1;
पूर्ण

अटल पूर्णांक __init vr41xx_icu_init(व्योम)
अणु
	अचिन्हित दीर्घ icu1_start, icu2_start;
	पूर्णांक i;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		icu1_start = ICU1_TYPE1_BASE;
		icu2_start = ICU2_TYPE1_BASE;
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		icu1_start = ICU1_TYPE2_BASE;
		icu2_start = ICU2_TYPE2_BASE;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "ICU: Unexpected CPU of NEC VR4100 series\n");
		वापस -ENODEV;
	पूर्ण

	अगर (request_mem_region(icu1_start, ICU1_SIZE, "ICU") == शून्य)
		वापस -EBUSY;

	अगर (request_mem_region(icu2_start, ICU2_SIZE, "ICU") == शून्य) अणु
		release_mem_region(icu1_start, ICU1_SIZE);
		वापस -EBUSY;
	पूर्ण

	icu1_base = ioremap(icu1_start, ICU1_SIZE);
	अगर (icu1_base == शून्य) अणु
		release_mem_region(icu1_start, ICU1_SIZE);
		release_mem_region(icu2_start, ICU2_SIZE);
		वापस -ENOMEM;
	पूर्ण

	icu2_base = ioremap(icu2_start, ICU2_SIZE);
	अगर (icu2_base == शून्य) अणु
		iounmap(icu1_base);
		release_mem_region(icu1_start, ICU1_SIZE);
		release_mem_region(icu2_start, ICU2_SIZE);
		वापस -ENOMEM;
	पूर्ण

	icu1_ग_लिखो(MSYSINT1REG, 0);
	icu1_ग_लिखो(MGIUINTLREG, 0xffff);

	icu2_ग_लिखो(MSYSINT2REG, 0);
	icu2_ग_लिखो(MGIUINTHREG, 0xffff);

	क्रम (i = SYSINT1_IRQ_BASE; i <= SYSINT1_IRQ_LAST; i++)
		irq_set_chip_and_handler(i, &sysपूर्णांक1_irq_type,
					 handle_level_irq);

	क्रम (i = SYSINT2_IRQ_BASE; i <= SYSINT2_IRQ_LAST; i++)
		irq_set_chip_and_handler(i, &sysपूर्णांक2_irq_type,
					 handle_level_irq);

	cascade_irq(INT0_IRQ, icu_get_irq);
	cascade_irq(INT1_IRQ, icu_get_irq);
	cascade_irq(INT2_IRQ, icu_get_irq);
	cascade_irq(INT3_IRQ, icu_get_irq);
	cascade_irq(INT4_IRQ, icu_get_irq);

	वापस 0;
पूर्ण

core_initcall(vr41xx_icu_init);
