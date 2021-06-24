<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Operating System Services (OSS) chip handling
 *	Written by Joshua M. Thompson (funaho@jurai.org)
 *
 *
 *	This chip is used in the IIfx in place of VIA #2. It acts like a fancy
 *	VIA chip with prorammable पूर्णांकerrupt levels.
 *
 * 990502 (jmt) - Major reग_लिखो क्रम new पूर्णांकerrupt architecture as well as some
 *		  recent insights पूर्णांकo OSS operational details.
 * 990610 (jmt) - Now taking full advantage of the OSS. Interrupts are mapped
 *		  to mostly match the A/UX पूर्णांकerrupt scheme supported on the
 *		  VIA side. Also added support क्रम enabling the ISM irq again
 *		  since we now have a functional IOP manager.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>
#समावेश <यंत्र/mac_oss.h>

पूर्णांक oss_present;
अस्थिर काष्ठा mac_oss *oss;

/*
 * Initialize the OSS
 */

व्योम __init oss_init(व्योम)
अणु
	पूर्णांक i;

	अगर (macपूर्णांकosh_config->ident != MAC_MODEL_IIFX)
		वापस;

	oss = (काष्ठा mac_oss *) OSS_BASE;
	pr_debug("OSS detected at %p", oss);
	oss_present = 1;

	/* Disable all पूर्णांकerrupts. Unlike a VIA it looks like we    */
	/* करो this by setting the source's पूर्णांकerrupt level to zero. */

	क्रम (i = 0; i < OSS_NUM_SOURCES; i++)
		oss->irq_level[i] = 0;
पूर्ण

/*
 * Handle OSS पूर्णांकerrupts.
 * XXX how करो you clear a pending IRQ? is it even necessary?
 */

अटल व्योम oss_iopism_irq(काष्ठा irq_desc *desc)
अणु
	generic_handle_irq(IRQ_MAC_ADB);
पूर्ण

अटल व्योम oss_scsi_irq(काष्ठा irq_desc *desc)
अणु
	generic_handle_irq(IRQ_MAC_SCSI);
पूर्ण

अटल व्योम oss_nubus_irq(काष्ठा irq_desc *desc)
अणु
	u16 events, irq_bit;
	पूर्णांक irq_num;

	events = oss->irq_pending & OSS_IP_NUBUS;
	irq_num = NUBUS_SOURCE_BASE + 5;
	irq_bit = OSS_IP_NUBUS5;
	करो अणु
		अगर (events & irq_bit) अणु
			events &= ~irq_bit;
			generic_handle_irq(irq_num);
		पूर्ण
		--irq_num;
		irq_bit >>= 1;
	पूर्ण जबतक (events);
पूर्ण

अटल व्योम oss_iopscc_irq(काष्ठा irq_desc *desc)
अणु
	generic_handle_irq(IRQ_MAC_SCC);
पूर्ण

/*
 * Register the OSS and NuBus पूर्णांकerrupt dispatchers.
 *
 * This IRQ mapping is laid out with two things in mind: first, we try to keep
 * things on their own levels to aव्योम having to करो द्विगुन-dispatches. Second,
 * the levels match as बंदly as possible the alternate IRQ mapping mode (aka
 * "A/UX mode") available on some VIA machines.
 */

#घोषणा OSS_IRQLEV_IOPISM    IRQ_AUTO_1
#घोषणा OSS_IRQLEV_SCSI      IRQ_AUTO_2
#घोषणा OSS_IRQLEV_NUBUS     IRQ_AUTO_3
#घोषणा OSS_IRQLEV_IOPSCC    IRQ_AUTO_4
#घोषणा OSS_IRQLEV_VIA1      IRQ_AUTO_6

व्योम __init oss_रेजिस्टर_पूर्णांकerrupts(व्योम)
अणु
	irq_set_chained_handler(OSS_IRQLEV_IOPISM, oss_iopism_irq);
	irq_set_chained_handler(OSS_IRQLEV_SCSI,   oss_scsi_irq);
	irq_set_chained_handler(OSS_IRQLEV_NUBUS,  oss_nubus_irq);
	irq_set_chained_handler(OSS_IRQLEV_IOPSCC, oss_iopscc_irq);
	irq_set_chained_handler(OSS_IRQLEV_VIA1,   via1_irq);

	/* OSS_VIA1 माला_लो enabled here because it has no machspec पूर्णांकerrupt. */
	oss->irq_level[OSS_VIA1] = OSS_IRQLEV_VIA1;
पूर्ण

/*
 * Enable an OSS पूर्णांकerrupt
 *
 * It looks messy but it's rather straightक्रमward. The चयन() statement
 * just maps the machspec पूर्णांकerrupt numbers to the right OSS पूर्णांकerrupt
 * source (अगर the OSS handles that पूर्णांकerrupt) and then sets the पूर्णांकerrupt
 * level क्रम that source to nonzero, thus enabling the पूर्णांकerrupt.
 */

व्योम oss_irq_enable(पूर्णांक irq) अणु
	चयन(irq) अणु
		हाल IRQ_MAC_SCC:
			oss->irq_level[OSS_IOPSCC] = OSS_IRQLEV_IOPSCC;
			वापस;
		हाल IRQ_MAC_ADB:
			oss->irq_level[OSS_IOPISM] = OSS_IRQLEV_IOPISM;
			वापस;
		हाल IRQ_MAC_SCSI:
			oss->irq_level[OSS_SCSI] = OSS_IRQLEV_SCSI;
			वापस;
		हाल IRQ_NUBUS_9:
		हाल IRQ_NUBUS_A:
		हाल IRQ_NUBUS_B:
		हाल IRQ_NUBUS_C:
		हाल IRQ_NUBUS_D:
		हाल IRQ_NUBUS_E:
			irq -= NUBUS_SOURCE_BASE;
			oss->irq_level[irq] = OSS_IRQLEV_NUBUS;
			वापस;
	पूर्ण

	अगर (IRQ_SRC(irq) == 1)
		via_irq_enable(irq);
पूर्ण

/*
 * Disable an OSS पूर्णांकerrupt
 *
 * Same as above except we set the source's पूर्णांकerrupt level to zero,
 * to disable the पूर्णांकerrupt.
 */

व्योम oss_irq_disable(पूर्णांक irq) अणु
	चयन(irq) अणु
		हाल IRQ_MAC_SCC:
			oss->irq_level[OSS_IOPSCC] = 0;
			वापस;
		हाल IRQ_MAC_ADB:
			oss->irq_level[OSS_IOPISM] = 0;
			वापस;
		हाल IRQ_MAC_SCSI:
			oss->irq_level[OSS_SCSI] = 0;
			वापस;
		हाल IRQ_NUBUS_9:
		हाल IRQ_NUBUS_A:
		हाल IRQ_NUBUS_B:
		हाल IRQ_NUBUS_C:
		हाल IRQ_NUBUS_D:
		हाल IRQ_NUBUS_E:
			irq -= NUBUS_SOURCE_BASE;
			oss->irq_level[irq] = 0;
			वापस;
	पूर्ण

	अगर (IRQ_SRC(irq) == 1)
		via_irq_disable(irq);
पूर्ण
