<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Static Memory Controller
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>

#समावेश <mach/hardware.h>
#समावेश <mach/smemc.h>

#अगर_घोषित CONFIG_PM
अटल अचिन्हित दीर्घ msc[2];
अटल अचिन्हित दीर्घ sxcnfg, memclkcfg;
अटल अचिन्हित दीर्घ csadrcfg[4];

अटल पूर्णांक pxa3xx_smemc_suspend(व्योम)
अणु
	msc[0] = __raw_पढ़ोl(MSC0);
	msc[1] = __raw_पढ़ोl(MSC1);
	sxcnfg = __raw_पढ़ोl(SXCNFG);
	memclkcfg = __raw_पढ़ोl(MEMCLKCFG);
	csadrcfg[0] = __raw_पढ़ोl(CSADRCFG0);
	csadrcfg[1] = __raw_पढ़ोl(CSADRCFG1);
	csadrcfg[2] = __raw_पढ़ोl(CSADRCFG2);
	csadrcfg[3] = __raw_पढ़ोl(CSADRCFG3);

	वापस 0;
पूर्ण

अटल व्योम pxa3xx_smemc_resume(व्योम)
अणु
	__raw_ग_लिखोl(msc[0], MSC0);
	__raw_ग_लिखोl(msc[1], MSC1);
	__raw_ग_लिखोl(sxcnfg, SXCNFG);
	__raw_ग_लिखोl(memclkcfg, MEMCLKCFG);
	__raw_ग_लिखोl(csadrcfg[0], CSADRCFG0);
	__raw_ग_लिखोl(csadrcfg[1], CSADRCFG1);
	__raw_ग_लिखोl(csadrcfg[2], CSADRCFG2);
	__raw_ग_लिखोl(csadrcfg[3], CSADRCFG3);
	/* CSMSADRCFG wakes up in its शेष state (0), so we need to set it */
	__raw_ग_लिखोl(0x2, CSMSADRCFG);
पूर्ण

अटल काष्ठा syscore_ops smemc_syscore_ops = अणु
	.suspend	= pxa3xx_smemc_suspend,
	.resume		= pxa3xx_smemc_resume,
पूर्ण;

अटल पूर्णांक __init smemc_init(व्योम)
अणु
	अगर (cpu_is_pxa3xx()) अणु
		/*
		 * The only करोcumentation we have on the
		 * Chip Select Configuration Register (CSMSADRCFG) is that
		 * it must be programmed to 0x2.
		 * Moreover, in the bit definitions, the second bit
		 * (CSMSADRCFG[1]) is called "SETALWAYS".
		 * Other bits are reserved in this रेजिस्टर.
		 */
		__raw_ग_लिखोl(0x2, CSMSADRCFG);

		रेजिस्टर_syscore_ops(&smemc_syscore_ops);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(smemc_init);
#पूर्ण_अगर
