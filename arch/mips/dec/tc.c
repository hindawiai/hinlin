<शैली गुरु>
/*
 *	TURBOchannel architecture calls.
 *
 *	Copyright (c) Harald Koerfgen, 1998
 *	Copyright (c) 2001, 2003, 2005, 2006  Maciej W. Rozycki
 *	Copyright (c) 2005  James Simmons
 *
 *	This file is subject to the terms and conditions of the GNU
 *	General Public License.  See the file "COPYING" in the मुख्य
 *	directory of this archive क्रम more details.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/tc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/paccess.h>

#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/prom.h>
#समावेश <यंत्र/dec/प्रणाली.h>

/*
 * Protected पढ़ो byte from TURBOchannel slot space.
 */
पूर्णांक tc_pपढ़ोb(u8 *valp, व्योम __iomem *addr)
अणु
	वापस get_dbe(*valp, (u8 *)addr);
पूर्ण

/*
 * Get TURBOchannel bus inक्रमmation as specअगरied by the spec, plus
 * the slot space base address and the number of slots.
 */
पूर्णांक __init tc_bus_get_info(काष्ठा tc_bus *tbus)
अणु
	अगर (!dec_tc_bus)
		वापस -ENXIO;

	स_नकल(&tbus->info, rex_gettcinfo(), माप(tbus->info));
	tbus->slot_base = CPHYSADDR((दीर्घ)rex_slot_address(0));

	चयन (mips_machtype) अणु
	हाल MACH_DS5000_200:
		tbus->num_tcslots = 7;
		अवरोध;
	हाल MACH_DS5000_2X0:
	हाल MACH_DS5900:
		tbus->ext_slot_base = 0x20000000;
		tbus->ext_slot_size = 0x20000000;
		fallthrough;
	हाल MACH_DS5000_1XX:
		tbus->num_tcslots = 3;
		अवरोध;
	हाल MACH_DS5000_XX:
		tbus->num_tcslots = 2;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Get the IRQ क्रम the specअगरied slot.
 */
व्योम __init tc_device_get_irq(काष्ठा tc_dev *tdev)
अणु
	चयन (tdev->slot) अणु
	हाल 0:
		tdev->पूर्णांकerrupt = dec_पूर्णांकerrupt[DEC_IRQ_TC0];
		अवरोध;
	हाल 1:
		tdev->पूर्णांकerrupt = dec_पूर्णांकerrupt[DEC_IRQ_TC1];
		अवरोध;
	हाल 2:
		tdev->पूर्णांकerrupt = dec_पूर्णांकerrupt[DEC_IRQ_TC2];
		अवरोध;
	/*
	 * Yuck! DS5000/200 onboard devices
	 */
	हाल 5:
		tdev->पूर्णांकerrupt = dec_पूर्णांकerrupt[DEC_IRQ_TC5];
		अवरोध;
	हाल 6:
		tdev->पूर्णांकerrupt = dec_पूर्णांकerrupt[DEC_IRQ_TC6];
		अवरोध;
	शेष:
		tdev->पूर्णांकerrupt = -1;
		अवरोध;
	पूर्ण
पूर्ण
