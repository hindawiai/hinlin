<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cmu.c, Clock Mask Unit routines क्रम the NEC VR4100 series.
 *
 *  Copyright (C) 2001-2002  MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2003-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
/*
 * Changes:
 *  MontaVista Software Inc. <source@mvista.com>
 *  - New creation, NEC VR4122 and VR4131 are supported.
 *  - Added support क्रम NEC VR4111 and VR4121.
 *
 *  Yoichi Yuasa <yuasa@linux-mips.org>
 *  - Added support क्रम NEC VR4133.
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vr41xx/vr41xx.h>

#घोषणा CMU_TYPE1_BASE	0x0b000060UL
#घोषणा CMU_TYPE1_SIZE	0x4

#घोषणा CMU_TYPE2_BASE	0x0f000060UL
#घोषणा CMU_TYPE2_SIZE	0x4

#घोषणा CMU_TYPE3_BASE	0x0f000060UL
#घोषणा CMU_TYPE3_SIZE	0x8

#घोषणा CMUCLKMSK	0x0
 #घोषणा MSKPIU		0x0001
 #घोषणा MSKSIU		0x0002
 #घोषणा MSKAIU		0x0004
 #घोषणा MSKKIU		0x0008
 #घोषणा MSKFIR		0x0010
 #घोषणा MSKDSIU	0x0820
 #घोषणा MSKCSI		0x0040
 #घोषणा MSKPCIU	0x0080
 #घोषणा MSKSSIU	0x0100
 #घोषणा MSKSHSP	0x0200
 #घोषणा MSKFFIR	0x0400
 #घोषणा MSKSCSI	0x1000
 #घोषणा MSKPPCIU	0x2000
#घोषणा CMUCLKMSK2	0x4
 #घोषणा MSKCEU		0x0001
 #घोषणा MSKMAC0	0x0002
 #घोषणा MSKMAC1	0x0004

अटल व्योम __iomem *cmu_base;
अटल uपूर्णांक16_t cmuclkmsk, cmuclkmsk2;
अटल DEFINE_SPINLOCK(cmu_lock);

#घोषणा cmu_पढ़ो(offset)		पढ़ोw(cmu_base + (offset))
#घोषणा cmu_ग_लिखो(offset, value)	ग_लिखोw((value), cmu_base + (offset))

व्योम vr41xx_supply_घड़ी(vr41xx_घड़ी_प्रकार घड़ी)
अणु
	spin_lock_irq(&cmu_lock);

	चयन (घड़ी) अणु
	हाल PIU_CLOCK:
		cmuclkmsk |= MSKPIU;
		अवरोध;
	हाल SIU_CLOCK:
		cmuclkmsk |= MSKSIU | MSKSSIU;
		अवरोध;
	हाल AIU_CLOCK:
		cmuclkmsk |= MSKAIU;
		अवरोध;
	हाल KIU_CLOCK:
		cmuclkmsk |= MSKKIU;
		अवरोध;
	हाल FIR_CLOCK:
		cmuclkmsk |= MSKFIR | MSKFFIR;
		अवरोध;
	हाल DSIU_CLOCK:
		अगर (current_cpu_type() == CPU_VR4111 ||
		    current_cpu_type() == CPU_VR4121)
			cmuclkmsk |= MSKDSIU;
		अन्यथा
			cmuclkmsk |= MSKSIU | MSKDSIU;
		अवरोध;
	हाल CSI_CLOCK:
		cmuclkmsk |= MSKCSI | MSKSCSI;
		अवरोध;
	हाल PCIU_CLOCK:
		cmuclkmsk |= MSKPCIU;
		अवरोध;
	हाल HSP_CLOCK:
		cmuclkmsk |= MSKSHSP;
		अवरोध;
	हाल PCI_CLOCK:
		cmuclkmsk |= MSKPPCIU;
		अवरोध;
	हाल CEU_CLOCK:
		cmuclkmsk2 |= MSKCEU;
		अवरोध;
	हाल ETHER0_CLOCK:
		cmuclkmsk2 |= MSKMAC0;
		अवरोध;
	हाल ETHER1_CLOCK:
		cmuclkmsk2 |= MSKMAC1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (घड़ी == CEU_CLOCK || घड़ी == ETHER0_CLOCK ||
	    घड़ी == ETHER1_CLOCK)
		cmu_ग_लिखो(CMUCLKMSK2, cmuclkmsk2);
	अन्यथा
		cmu_ग_लिखो(CMUCLKMSK, cmuclkmsk);

	spin_unlock_irq(&cmu_lock);
पूर्ण

EXPORT_SYMBOL_GPL(vr41xx_supply_घड़ी);

व्योम vr41xx_mask_घड़ी(vr41xx_घड़ी_प्रकार घड़ी)
अणु
	spin_lock_irq(&cmu_lock);

	चयन (घड़ी) अणु
	हाल PIU_CLOCK:
		cmuclkmsk &= ~MSKPIU;
		अवरोध;
	हाल SIU_CLOCK:
		अगर (current_cpu_type() == CPU_VR4111 ||
		    current_cpu_type() == CPU_VR4121) अणु
			cmuclkmsk &= ~(MSKSIU | MSKSSIU);
		पूर्ण अन्यथा अणु
			अगर (cmuclkmsk & MSKDSIU)
				cmuclkmsk &= ~MSKSSIU;
			अन्यथा
				cmuclkmsk &= ~(MSKSIU | MSKSSIU);
		पूर्ण
		अवरोध;
	हाल AIU_CLOCK:
		cmuclkmsk &= ~MSKAIU;
		अवरोध;
	हाल KIU_CLOCK:
		cmuclkmsk &= ~MSKKIU;
		अवरोध;
	हाल FIR_CLOCK:
		cmuclkmsk &= ~(MSKFIR | MSKFFIR);
		अवरोध;
	हाल DSIU_CLOCK:
		अगर (current_cpu_type() == CPU_VR4111 ||
		    current_cpu_type() == CPU_VR4121) अणु
			cmuclkmsk &= ~MSKDSIU;
		पूर्ण अन्यथा अणु
			अगर (cmuclkmsk & MSKSSIU)
				cmuclkmsk &= ~MSKDSIU;
			अन्यथा
				cmuclkmsk &= ~(MSKSIU | MSKDSIU);
		पूर्ण
		अवरोध;
	हाल CSI_CLOCK:
		cmuclkmsk &= ~(MSKCSI | MSKSCSI);
		अवरोध;
	हाल PCIU_CLOCK:
		cmuclkmsk &= ~MSKPCIU;
		अवरोध;
	हाल HSP_CLOCK:
		cmuclkmsk &= ~MSKSHSP;
		अवरोध;
	हाल PCI_CLOCK:
		cmuclkmsk &= ~MSKPPCIU;
		अवरोध;
	हाल CEU_CLOCK:
		cmuclkmsk2 &= ~MSKCEU;
		अवरोध;
	हाल ETHER0_CLOCK:
		cmuclkmsk2 &= ~MSKMAC0;
		अवरोध;
	हाल ETHER1_CLOCK:
		cmuclkmsk2 &= ~MSKMAC1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (घड़ी == CEU_CLOCK || घड़ी == ETHER0_CLOCK ||
	    घड़ी == ETHER1_CLOCK)
		cmu_ग_लिखो(CMUCLKMSK2, cmuclkmsk2);
	अन्यथा
		cmu_ग_लिखो(CMUCLKMSK, cmuclkmsk);

	spin_unlock_irq(&cmu_lock);
पूर्ण

EXPORT_SYMBOL_GPL(vr41xx_mask_घड़ी);

अटल पूर्णांक __init vr41xx_cmu_init(व्योम)
अणु
	अचिन्हित दीर्घ start, size;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		start = CMU_TYPE1_BASE;
		size = CMU_TYPE1_SIZE;
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
		start = CMU_TYPE2_BASE;
		size = CMU_TYPE2_SIZE;
		अवरोध;
	हाल CPU_VR4133:
		start = CMU_TYPE3_BASE;
		size = CMU_TYPE3_SIZE;
		अवरोध;
	शेष:
		panic("Unexpected CPU of NEC VR4100 series");
		अवरोध;
	पूर्ण

	अगर (request_mem_region(start, size, "CMU") == शून्य)
		वापस -EBUSY;

	cmu_base = ioremap(start, size);
	अगर (cmu_base == शून्य) अणु
		release_mem_region(start, size);
		वापस -EBUSY;
	पूर्ण

	cmuclkmsk = cmu_पढ़ो(CMUCLKMSK);
	अगर (current_cpu_type() == CPU_VR4133)
		cmuclkmsk2 = cmu_पढ़ो(CMUCLKMSK2);

	spin_lock_init(&cmu_lock);

	वापस 0;
पूर्ण

core_initcall(vr41xx_cmu_init);
