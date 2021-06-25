<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम periodic पूर्णांकerrupts (100 per second) and क्रम getting
 * the current समय from the RTC on Power Macपूर्णांकoshes.
 *
 * We use the decrementer रेजिस्टर क्रम our periodic पूर्णांकerrupts.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996 Paul Mackerras.
 * Copyright (C) 2003-2005 Benjamin Herrenschmidt.
 *
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/smu.h>

#समावेश "pmac.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

/*
 * Calibrate the decrementer frequency with the VIA समयr 1.
 */
#घोषणा VIA_TIMER_FREQ_6	4700000	/* समय 1 frequency * 6 */

/* VIA रेजिस्टरs */
#घोषणा RS		0x200		/* skip between रेजिस्टरs */
#घोषणा T1CL		(4*RS)		/* Timer 1 ctr/latch (low 8 bits) */
#घोषणा T1CH		(5*RS)		/* Timer 1 counter (high 8 bits) */
#घोषणा T1LL		(6*RS)		/* Timer 1 latch (low 8 bits) */
#घोषणा T1LH		(7*RS)		/* Timer 1 latch (high 8 bits) */
#घोषणा ACR		(11*RS)		/* Auxiliary control रेजिस्टर */
#घोषणा IFR		(13*RS)		/* Interrupt flag रेजिस्टर */

/* Bits in ACR */
#घोषणा T1MODE		0xc0		/* Timer 1 mode */
#घोषणा T1MODE_CONT	0x40		/*  continuous पूर्णांकerrupts */

/* Bits in IFR and IER */
#घोषणा T1_INT		0x40		/* Timer 1 पूर्णांकerrupt */

दीर्घ __init pmac_समय_init(व्योम)
अणु
	s32 delta = 0;
#अगर defined(CONFIG_NVRAM) && defined(CONFIG_PPC32)
	पूर्णांक dst;
	
	delta = ((s32)pmac_xpram_पढ़ो(PMAC_XPRAM_MACHINE_LOC + 0x9)) << 16;
	delta |= ((s32)pmac_xpram_पढ़ो(PMAC_XPRAM_MACHINE_LOC + 0xa)) << 8;
	delta |= pmac_xpram_पढ़ो(PMAC_XPRAM_MACHINE_LOC + 0xb);
	अगर (delta & 0x00800000UL)
		delta |= 0xFF000000UL;
	dst = ((pmac_xpram_पढ़ो(PMAC_XPRAM_MACHINE_LOC + 0x8) & 0x80) != 0);
	prपूर्णांकk("GMT Delta read from XPRAM: %d minutes, DST: %s\n", delta/60,
		dst ? "on" : "off");
#पूर्ण_अगर
	वापस delta;
पूर्ण

#अगर_घोषित CONFIG_PMAC_SMU
अटल समय64_t smu_get_समय(व्योम)
अणु
	काष्ठा rtc_समय पंचांग;

	अगर (smu_get_rtc_समय(&पंचांग, 1))
		वापस 0;
	वापस rtc_पंचांग_to_समय64(&पंचांग);
पूर्ण
#पूर्ण_अगर

/* Can't be __init, it's called when suspending and resuming */
समय64_t pmac_get_boot_समय(व्योम)
अणु
	/* Get the समय from the RTC, used only at boot समय */
	चयन (sys_ctrler) अणु
#अगर_घोषित CONFIG_ADB_CUDA
	हाल SYS_CTRLER_CUDA:
		वापस cuda_get_समय();
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	हाल SYS_CTRLER_PMU:
		वापस pmu_get_समय();
#पूर्ण_अगर
#अगर_घोषित CONFIG_PMAC_SMU
	हाल SYS_CTRLER_SMU:
		वापस smu_get_समय();
#पूर्ण_अगर
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम pmac_get_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	/* Get the समय from the RTC, used only at boot समय */
	चयन (sys_ctrler) अणु
#अगर_घोषित CONFIG_ADB_CUDA
	हाल SYS_CTRLER_CUDA:
		rtc_समय64_to_पंचांग(cuda_get_समय(), पंचांग);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	हाल SYS_CTRLER_PMU:
		rtc_समय64_to_पंचांग(pmu_get_समय(), पंचांग);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PMAC_SMU
	हाल SYS_CTRLER_SMU:
		smu_get_rtc_समय(पंचांग, 1);
		अवरोध;
#पूर्ण_अगर
	शेष:
		;
	पूर्ण
पूर्ण

पूर्णांक pmac_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	चयन (sys_ctrler) अणु
#अगर_घोषित CONFIG_ADB_CUDA
	हाल SYS_CTRLER_CUDA:
		वापस cuda_set_rtc_समय(पंचांग);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	हाल SYS_CTRLER_PMU:
		वापस pmu_set_rtc_समय(पंचांग);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PMAC_SMU
	हाल SYS_CTRLER_SMU:
		वापस smu_set_rtc_समय(पंचांग, 1);
#पूर्ण_अगर
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC32
/*
 * Calibrate the decrementer रेजिस्टर using VIA समयr 1.
 * This is used both on घातermacs and CHRP machines.
 */
अटल पूर्णांक __init via_calibrate_decr(व्योम)
अणु
	काष्ठा device_node *vias;
	अस्थिर अचिन्हित अक्षर __iomem *via;
	पूर्णांक count = VIA_TIMER_FREQ_6 / 100;
	अचिन्हित पूर्णांक dstart, dend;
	काष्ठा resource rsrc;

	vias = of_find_node_by_name(शून्य, "via-cuda");
	अगर (vias == शून्य)
		vias = of_find_node_by_name(शून्य, "via-pmu");
	अगर (vias == शून्य)
		vias = of_find_node_by_name(शून्य, "via");
	अगर (vias == शून्य || of_address_to_resource(vias, 0, &rsrc)) अणु
	        of_node_put(vias);
		वापस 0;
	पूर्ण
	of_node_put(vias);
	via = ioremap(rsrc.start, resource_size(&rsrc));
	अगर (via == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to map VIA for timer calibration !\n");
		वापस 0;
	पूर्ण

	/* set समयr 1 क्रम continuous पूर्णांकerrupts */
	out_8(&via[ACR], (via[ACR] & ~T1MODE) | T1MODE_CONT);
	/* set the counter to a small value */
	out_8(&via[T1CH], 2);
	/* set the latch to `count' */
	out_8(&via[T1LL], count);
	out_8(&via[T1LH], count >> 8);
	/* रुको until it hits 0 */
	जबतक ((in_8(&via[IFR]) & T1_INT) == 0)
		;
	dstart = get_dec();
	/* clear the पूर्णांकerrupt & रुको until it hits 0 again */
	in_8(&via[T1CL]);
	जबतक ((in_8(&via[IFR]) & T1_INT) == 0)
		;
	dend = get_dec();

	ppc_tb_freq = (dstart - dend) * 100 / 6;

	iounmap(via);

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * Query the OF and get the decr frequency.
 */
व्योम __init pmac_calibrate_decr(व्योम)
अणु
	generic_calibrate_decr();

#अगर_घोषित CONFIG_PPC32
	/* We assume MacRISC2 machines have correct device-tree
	 * calibration. That's better since the VIA itself seems
	 * to be slightly off. --BenH
	 */
	अगर (!of_machine_is_compatible("MacRISC2") &&
	    !of_machine_is_compatible("MacRISC3") &&
	    !of_machine_is_compatible("MacRISC4"))
		अगर (via_calibrate_decr())
			वापस;

	/* Special हाल: QuickSilver G4s seem to have a badly calibrated
	 * समयbase-frequency in OF, VIA is much better on these. We should
	 * probably implement calibration based on the KL समयr on these
	 * machines anyway... -BenH
	 */
	अगर (of_machine_is_compatible("PowerMac3,5"))
		अगर (via_calibrate_decr())
			वापस;
#पूर्ण_अगर
पूर्ण
