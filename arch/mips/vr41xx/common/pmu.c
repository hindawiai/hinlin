<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pmu.c, Power Management Unit routines क्रम NEC VR4100 series.
 *
 *  Copyright (C) 2003-2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/reboot.h>

#घोषणा PMU_TYPE1_BASE	0x0b0000a0UL
#घोषणा PMU_TYPE1_SIZE	0x0eUL

#घोषणा PMU_TYPE2_BASE	0x0f0000c0UL
#घोषणा PMU_TYPE2_SIZE	0x10UL

#घोषणा PMUCNT2REG	0x06
 #घोषणा SOFTRST	0x0010

अटल व्योम __iomem *pmu_base;

#घोषणा pmu_पढ़ो(offset)		पढ़ोw(pmu_base + (offset))
#घोषणा pmu_ग_लिखो(offset, value)	ग_लिखोw((value), pmu_base + (offset))

अटल व्योम __cpuidle vr41xx_cpu_रुको(व्योम)
अणु
	local_irq_disable();
	अगर (!need_resched())
		/*
		 * "standby" sets IE bit of the CP0_STATUS to 1.
		 */
		__यंत्र__("standby;\n");
	अन्यथा
		local_irq_enable();
पूर्ण

अटल अंतरभूत व्योम software_reset(व्योम)
अणु
	uपूर्णांक16_t pmucnt2;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		pmucnt2 = pmu_पढ़ो(PMUCNT2REG);
		pmucnt2 |= SOFTRST;
		pmu_ग_लिखो(PMUCNT2REG, pmucnt2);
		अवरोध;
	शेष:
		set_c0_status(ST0_BEV | ST0_ERL);
		change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
		__flush_cache_all();
		ग_लिखो_c0_wired(0);
		__यंत्र__("jr	%0"::"r"(0xbfc00000));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vr41xx_restart(अक्षर *command)
अणु
	local_irq_disable();
	software_reset();
	जबतक (1) ;
पूर्ण

अटल व्योम vr41xx_halt(व्योम)
अणु
	local_irq_disable();
	prपूर्णांकk(KERN_NOTICE "\nYou can turn off the power supply\n");
	__यंत्र__("hibernate;\n");
पूर्ण

अटल पूर्णांक __init vr41xx_pmu_init(व्योम)
अणु
	अचिन्हित दीर्घ start, size;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		start = PMU_TYPE1_BASE;
		size = PMU_TYPE1_SIZE;
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		start = PMU_TYPE2_BASE;
		size = PMU_TYPE2_SIZE;
		अवरोध;
	शेष:
		prपूर्णांकk("Unexpected CPU of NEC VR4100 series\n");
		वापस -ENODEV;
	पूर्ण

	अगर (request_mem_region(start, size, "PMU") == शून्य)
		वापस -EBUSY;

	pmu_base = ioremap(start, size);
	अगर (pmu_base == शून्य) अणु
		release_mem_region(start, size);
		वापस -EBUSY;
	पूर्ण

	cpu_रुको = vr41xx_cpu_रुको;
	_machine_restart = vr41xx_restart;
	_machine_halt = vr41xx_halt;
	pm_घातer_off = vr41xx_halt;

	वापस 0;
पूर्ण

core_initcall(vr41xx_pmu_init);
