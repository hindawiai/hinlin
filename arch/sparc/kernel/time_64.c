<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* समय.c: UltraSparc समयr and TOD घड़ी support.
 *
 * Copyright (C) 1997, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998 Eddie C. Dost   (ecd@skynet.be)
 *
 * Based largely on code which is:
 *
 * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/profile.h>
#समावेश <linux/bcd.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rtc/m48t59.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "entry.h"
#समावेश "kernel.h"

DEFINE_SPINLOCK(rtc_lock);

#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (in_lock_functions(pc))
		वापस regs->u_regs[UREG_RETPC];
	वापस pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);
#पूर्ण_अगर

अटल व्योम tick_disable_protection(व्योम)
अणु
	/* Set things up so user can access tick रेजिस्टर क्रम profiling
	 * purposes.  Also workaround BB_ERRATA_1 by करोing a dummy
	 * पढ़ो back of %tick after writing it.
	 */
	__यंत्र__ __अस्थिर__(
	"	ba,pt	%%xcc, 1f\n"
	"	 nop\n"
	"	.align	64\n"
	"1:	rd	%%tick, %%g2\n"
	"	add	%%g2, 6, %%g2\n"
	"	andn	%%g2, %0, %%g2\n"
	"	wrpr	%%g2, 0, %%tick\n"
	"	rdpr	%%tick, %%g0"
	: /* no outमाला_दो */
	: "r" (TICK_PRIV_BIT)
	: "g2");
पूर्ण

अटल व्योम tick_disable_irq(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	ba,pt	%%xcc, 1f\n"
	"	 nop\n"
	"	.align	64\n"
	"1:	wr	%0, 0x0, %%tick_cmpr\n"
	"	rd	%%tick_cmpr, %%g0"
	: /* no outमाला_दो */
	: "r" (TICKCMP_IRQ_BIT));
पूर्ण

अटल व्योम tick_init_tick(व्योम)
अणु
	tick_disable_protection();
	tick_disable_irq();
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ tick_get_tick(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__("rd	%%tick, %0\n\t"
			     "mov	%0, %0"
			     : "=r" (ret));

	वापस ret & ~TICK_PRIV_BIT;
पूर्ण

अटल पूर्णांक tick_add_compare(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ orig_tick, new_tick, new_compare;

	__यंत्र__ __अस्थिर__("rd	%%tick, %0"
			     : "=r" (orig_tick));

	orig_tick &= ~TICKCMP_IRQ_BIT;

	/* Workaround क्रम Spitfire Errata (#54 I think??), I discovered
	 * this via Sun BugID 4008234, mentioned in Solaris-2.5.1 patch
	 * number 103640.
	 *
	 * On Blackbird ग_लिखोs to %tick_cmpr can fail, the
	 * workaround seems to be to execute the wr inकाष्ठाion
	 * at the start of an I-cache line, and perक्रमm a dummy
	 * पढ़ो back from %tick_cmpr right after writing to it. -DaveM
	 */
	__यंत्र__ __अस्थिर__("ba,pt	%%xcc, 1f\n\t"
			     " add	%1, %2, %0\n\t"
			     ".align	64\n"
			     "1:\n\t"
			     "wr	%0, 0, %%tick_cmpr\n\t"
			     "rd	%%tick_cmpr, %%g0\n\t"
			     : "=r" (new_compare)
			     : "r" (orig_tick), "r" (adj));

	__यंत्र__ __अस्थिर__("rd	%%tick, %0"
			     : "=r" (new_tick));
	new_tick &= ~TICKCMP_IRQ_BIT;

	वापस ((दीर्घ)(new_tick - (orig_tick+adj))) > 0L;
पूर्ण

अटल अचिन्हित दीर्घ tick_add_tick(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ new_tick;

	/* Also need to handle Blackbird bug here too. */
	__यंत्र__ __अस्थिर__("rd	%%tick, %0\n\t"
			     "add	%0, %1, %0\n\t"
			     "wrpr	%0, 0, %%tick\n\t"
			     : "=&r" (new_tick)
			     : "r" (adj));

	वापस new_tick;
पूर्ण

/* Searches क्रम cpu घड़ी frequency with given cpuid in OpenBoot tree */
अटल अचिन्हित दीर्घ cpuid_to_freq(phandle node, पूर्णांक cpuid)
अणु
	bool is_cpu_node = false;
	अचिन्हित दीर्घ freq = 0;
	अक्षर type[128];

	अगर (!node)
		वापस freq;

	अगर (prom_getproperty(node, "device_type", type, माप(type)) != -1)
		is_cpu_node = (म_भेद(type, "cpu") == 0);

	/* try upa-portid then cpuid to get cpuid, see prom_64.c */
	अगर (is_cpu_node && (prom_getपूर्णांक(node, "upa-portid") == cpuid ||
			    prom_getपूर्णांक(node, "cpuid") == cpuid))
		freq = prom_getपूर्णांकशेष(node, "clock-frequency", 0);
	अगर (!freq)
		freq = cpuid_to_freq(prom_अ_लोhild(node), cpuid);
	अगर (!freq)
		freq = cpuid_to_freq(prom_माला_लोibling(node), cpuid);

	वापस freq;
पूर्ण

अटल अचिन्हित दीर्घ tick_get_frequency(व्योम)
अणु
	वापस cpuid_to_freq(prom_root_node, hard_smp_processor_id());
पूर्ण

अटल काष्ठा sparc64_tick_ops tick_operations __cacheline_aligned = अणु
	.name		=	"tick",
	.init_tick	=	tick_init_tick,
	.disable_irq	=	tick_disable_irq,
	.get_tick	=	tick_get_tick,
	.add_tick	=	tick_add_tick,
	.add_compare	=	tick_add_compare,
	.get_frequency	=	tick_get_frequency,
	.softपूर्णांक_mask	=	1UL << 0,
पूर्ण;

काष्ठा sparc64_tick_ops *tick_ops __पढ़ो_mostly = &tick_operations;
EXPORT_SYMBOL(tick_ops);

अटल व्योम stick_disable_irq(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"wr	%0, 0x0, %%asr25"
	: /* no outमाला_दो */
	: "r" (TICKCMP_IRQ_BIT));
पूर्ण

अटल व्योम stick_init_tick(व्योम)
अणु
	/* Writes to the %tick and %stick रेजिस्टर are not
	 * allowed on sun4v.  The Hypervisor controls that
	 * bit, per-stअक्रम.
	 */
	अगर (tlb_type != hypervisor) अणु
		tick_disable_protection();
		tick_disable_irq();

		/* Let the user get at STICK too. */
		__यंत्र__ __अस्थिर__(
		"	rd	%%asr24, %%g2\n"
		"	andn	%%g2, %0, %%g2\n"
		"	wr	%%g2, 0, %%asr24"
		: /* no outमाला_दो */
		: "r" (TICK_PRIV_BIT)
		: "g1", "g2");
	पूर्ण

	stick_disable_irq();
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ stick_get_tick(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__("rd	%%asr24, %0"
			     : "=r" (ret));

	वापस ret & ~TICK_PRIV_BIT;
पूर्ण

अटल अचिन्हित दीर्घ stick_add_tick(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ new_tick;

	__यंत्र__ __अस्थिर__("rd	%%asr24, %0\n\t"
			     "add	%0, %1, %0\n\t"
			     "wr	%0, 0, %%asr24\n\t"
			     : "=&r" (new_tick)
			     : "r" (adj));

	वापस new_tick;
पूर्ण

अटल पूर्णांक stick_add_compare(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ orig_tick, new_tick;

	__यंत्र__ __अस्थिर__("rd	%%asr24, %0"
			     : "=r" (orig_tick));
	orig_tick &= ~TICKCMP_IRQ_BIT;

	__यंत्र__ __अस्थिर__("wr	%0, 0, %%asr25"
			     : /* no outमाला_दो */
			     : "r" (orig_tick + adj));

	__यंत्र__ __अस्थिर__("rd	%%asr24, %0"
			     : "=r" (new_tick));
	new_tick &= ~TICKCMP_IRQ_BIT;

	वापस ((दीर्घ)(new_tick - (orig_tick+adj))) > 0L;
पूर्ण

अटल अचिन्हित दीर्घ stick_get_frequency(व्योम)
अणु
	वापस prom_getपूर्णांकशेष(prom_root_node, "stick-frequency", 0);
पूर्ण

अटल काष्ठा sparc64_tick_ops stick_operations __पढ़ो_mostly = अणु
	.name		=	"stick",
	.init_tick	=	stick_init_tick,
	.disable_irq	=	stick_disable_irq,
	.get_tick	=	stick_get_tick,
	.add_tick	=	stick_add_tick,
	.add_compare	=	stick_add_compare,
	.get_frequency	=	stick_get_frequency,
	.softपूर्णांक_mask	=	1UL << 16,
पूर्ण;

/* On Hummingbird the STICK/STICK_CMPR रेजिस्टर is implemented
 * in I/O space.  There are two 64-bit रेजिस्टरs each, the
 * first holds the low 32-bits of the value and the second holds
 * the high 32-bits.
 *
 * Since STICK is स्थिरantly updating, we have to access it carefully.
 *
 * The sequence we use to पढ़ो is:
 * 1) पढ़ो high
 * 2) पढ़ो low
 * 3) पढ़ो high again, अगर it rolled re-पढ़ो both low and high again.
 *
 * Writing STICK safely is also tricky:
 * 1) ग_लिखो low to zero
 * 2) ग_लिखो high
 * 3) ग_लिखो low
 */
अटल अचिन्हित दीर्घ __hbird_पढ़ो_stick(व्योम)
अणु
	अचिन्हित दीर्घ ret, पंचांगp1, पंचांगp2, पंचांगp3;
	अचिन्हित दीर्घ addr = HBIRD_STICK_ADDR+8;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %5, %2\n"
			     "1:\n\t"
			     "sub	%1, 0x8, %1\n\t"
			     "ldxa	[%1] %5, %3\n\t"
			     "add	%1, 0x8, %1\n\t"
			     "ldxa	[%1] %5, %4\n\t"
			     "cmp	%4, %2\n\t"
			     "bne,a,pn	%%xcc, 1b\n\t"
			     " mov	%4, %2\n\t"
			     "sllx	%4, 32, %4\n\t"
			     "or	%3, %4, %0\n\t"
			     : "=&r" (ret), "=&r" (addr),
			       "=&r" (पंचांगp1), "=&r" (पंचांगp2), "=&r" (पंचांगp3)
			     : "i" (ASI_PHYS_BYPASS_EC_E), "1" (addr));

	वापस ret;
पूर्ण

अटल व्योम __hbird_ग_लिखो_stick(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ low = (val & 0xffffffffUL);
	अचिन्हित दीर्घ high = (val >> 32UL);
	अचिन्हित दीर्घ addr = HBIRD_STICK_ADDR;

	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %4\n\t"
			     "add	%0, 0x8, %0\n\t"
			     "stxa	%3, [%0] %4\n\t"
			     "sub	%0, 0x8, %0\n\t"
			     "stxa	%2, [%0] %4"
			     : "=&r" (addr)
			     : "0" (addr), "r" (low), "r" (high),
			       "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

अटल व्योम __hbird_ग_लिखो_compare(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ low = (val & 0xffffffffUL);
	अचिन्हित दीर्घ high = (val >> 32UL);
	अचिन्हित दीर्घ addr = HBIRD_STICKCMP_ADDR + 0x8UL;

	__यंत्र__ __अस्थिर__("stxa	%3, [%0] %4\n\t"
			     "sub	%0, 0x8, %0\n\t"
			     "stxa	%2, [%0] %4"
			     : "=&r" (addr)
			     : "0" (addr), "r" (low), "r" (high),
			       "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

अटल व्योम hbtick_disable_irq(व्योम)
अणु
	__hbird_ग_लिखो_compare(TICKCMP_IRQ_BIT);
पूर्ण

अटल व्योम hbtick_init_tick(व्योम)
अणु
	tick_disable_protection();

	/* XXX This seems to be necessary to 'jumpstart' Hummingbird
	 * XXX पूर्णांकo actually sending STICK पूर्णांकerrupts.  I think because
	 * XXX of how we store %tick_cmpr in head.S this somehow resets the
	 * XXX अणुTICK + STICKपूर्ण पूर्णांकerrupt mux.  -DaveM
	 */
	__hbird_ग_लिखो_stick(__hbird_पढ़ो_stick());

	hbtick_disable_irq();
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ hbtick_get_tick(व्योम)
अणु
	वापस __hbird_पढ़ो_stick() & ~TICK_PRIV_BIT;
पूर्ण

अटल अचिन्हित दीर्घ hbtick_add_tick(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ val;

	val = __hbird_पढ़ो_stick() + adj;
	__hbird_ग_लिखो_stick(val);

	वापस val;
पूर्ण

अटल पूर्णांक hbtick_add_compare(अचिन्हित दीर्घ adj)
अणु
	अचिन्हित दीर्घ val = __hbird_पढ़ो_stick();
	अचिन्हित दीर्घ val2;

	val &= ~TICKCMP_IRQ_BIT;
	val += adj;
	__hbird_ग_लिखो_compare(val);

	val2 = __hbird_पढ़ो_stick() & ~TICKCMP_IRQ_BIT;

	वापस ((दीर्घ)(val2 - val)) > 0L;
पूर्ण

अटल अचिन्हित दीर्घ hbtick_get_frequency(व्योम)
अणु
	वापस prom_getपूर्णांकशेष(prom_root_node, "stick-frequency", 0);
पूर्ण

अटल काष्ठा sparc64_tick_ops hbtick_operations __पढ़ो_mostly = अणु
	.name		=	"hbtick",
	.init_tick	=	hbtick_init_tick,
	.disable_irq	=	hbtick_disable_irq,
	.get_tick	=	hbtick_get_tick,
	.add_tick	=	hbtick_add_tick,
	.add_compare	=	hbtick_add_compare,
	.get_frequency	=	hbtick_get_frequency,
	.softपूर्णांक_mask	=	1UL << 0,
पूर्ण;

अचिन्हित दीर्घ cmos_regs;
EXPORT_SYMBOL(cmos_regs);

अटल काष्ठा resource rtc_cmos_resource;

अटल काष्ठा platक्रमm_device rtc_cmos_device = अणु
	.name		= "rtc_cmos",
	.id		= -1,
	.resource	= &rtc_cmos_resource,
	.num_resources	= 1,
पूर्ण;

अटल पूर्णांक rtc_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा resource *r;

	prपूर्णांकk(KERN_INFO "%pOF: RTC regs at 0x%llx\n",
	       op->dev.of_node, op->resource[0].start);

	/* The CMOS RTC driver only accepts IORESOURCE_IO, so cons
	 * up a fake resource so that the probe works क्रम all हालs.
	 * When the RTC is behind an ISA bus it will have IORESOURCE_IO
	 * alपढ़ोy, whereas when it's behind EBUS is will be IORESOURCE_MEM.
	 */

	r = &rtc_cmos_resource;
	r->flags = IORESOURCE_IO;
	r->name = op->resource[0].name;
	r->start = op->resource[0].start;
	r->end = op->resource[0].end;

	cmos_regs = op->resource[0].start;
	वापस platक्रमm_device_रेजिस्टर(&rtc_cmos_device);
पूर्ण

अटल स्थिर काष्ठा of_device_id rtc_match[] = अणु
	अणु
		.name = "rtc",
		.compatible = "m5819",
	पूर्ण,
	अणु
		.name = "rtc",
		.compatible = "isa-m5819p",
	पूर्ण,
	अणु
		.name = "rtc",
		.compatible = "isa-m5823p",
	पूर्ण,
	अणु
		.name = "rtc",
		.compatible = "ds1287",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rtc_driver = अणु
	.probe		= rtc_probe,
	.driver = अणु
		.name = "rtc",
		.of_match_table = rtc_match,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_bq4802_device = अणु
	.name		= "rtc-bq4802",
	.id		= -1,
	.num_resources	= 1,
पूर्ण;

अटल पूर्णांक bq4802_probe(काष्ठा platक्रमm_device *op)
अणु

	prपूर्णांकk(KERN_INFO "%pOF: BQ4802 regs at 0x%llx\n",
	       op->dev.of_node, op->resource[0].start);

	rtc_bq4802_device.resource = &op->resource[0];
	वापस platक्रमm_device_रेजिस्टर(&rtc_bq4802_device);
पूर्ण

अटल स्थिर काष्ठा of_device_id bq4802_match[] = अणु
	अणु
		.name = "rtc",
		.compatible = "bq4802",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bq4802_driver = अणु
	.probe		= bq4802_probe,
	.driver = अणु
		.name = "bq4802",
		.of_match_table = bq4802_match,
	पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर mostek_पढ़ो_byte(काष्ठा device *dev, u32 ofs)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	व्योम __iomem *regs = (व्योम __iomem *) pdev->resource[0].start;

	वापस पढ़ोb(regs + ofs);
पूर्ण

अटल व्योम mostek_ग_लिखो_byte(काष्ठा device *dev, u32 ofs, u8 val)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	व्योम __iomem *regs = (व्योम __iomem *) pdev->resource[0].start;

	ग_लिखोb(val, regs + ofs);
पूर्ण

अटल काष्ठा m48t59_plat_data m48t59_data = अणु
	.पढ़ो_byte	= mostek_पढ़ो_byte,
	.ग_लिखो_byte	= mostek_ग_लिखो_byte,
पूर्ण;

अटल काष्ठा platक्रमm_device m48t59_rtc = अणु
	.name		= "rtc-m48t59",
	.id		= 0,
	.num_resources	= 1,
	.dev	= अणु
		.platक्रमm_data = &m48t59_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mostek_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;

	/* On an Enterprise प्रणाली there can be multiple mostek घड़ीs.
	 * We should only match the one that is on the central FHC bus.
	 */
	अगर (of_node_name_eq(dp->parent, "fhc") &&
	    !of_node_name_eq(dp->parent->parent, "central"))
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "%pOF: Mostek regs at 0x%llx\n",
	       dp, op->resource[0].start);

	m48t59_rtc.resource = &op->resource[0];
	वापस platक्रमm_device_रेजिस्टर(&m48t59_rtc);
पूर्ण

अटल स्थिर काष्ठा of_device_id mostek_match[] = अणु
	अणु
		.name = "eeprom",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mostek_driver = अणु
	.probe		= mostek_probe,
	.driver = अणु
		.name = "mostek",
		.of_match_table = mostek_match,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_sun4v_device = अणु
	.name		= "rtc-sun4v",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_starfire_device = अणु
	.name		= "rtc-starfire",
	.id		= -1,
पूर्ण;

अटल पूर्णांक __init घड़ी_init(व्योम)
अणु
	अगर (this_is_starfire)
		वापस platक्रमm_device_रेजिस्टर(&rtc_starfire_device);

	अगर (tlb_type == hypervisor)
		वापस platक्रमm_device_रेजिस्टर(&rtc_sun4v_device);

	(व्योम) platक्रमm_driver_रेजिस्टर(&rtc_driver);
	(व्योम) platक्रमm_driver_रेजिस्टर(&mostek_driver);
	(व्योम) platक्रमm_driver_रेजिस्टर(&bq4802_driver);

	वापस 0;
पूर्ण

/* Must be after subsys_initcall() so that busses are probed.  Must
 * be beक्रमe device_initcall() because things like the RTC driver
 * need to see the घड़ी रेजिस्टरs.
 */
fs_initcall(घड़ी_init);

/* Return true अगर this is Hummingbird, aka Ultra-IIe */
अटल bool is_hummingbird(व्योम)
अणु
	अचिन्हित दीर्घ ver, manuf, impl;

	__यंत्र__ __अस्थिर__ ("rdpr %%ver, %0"
			      : "=&r" (ver));
	manuf = ((ver >> 48) & 0xffff);
	impl = ((ver >> 32) & 0xffff);

	वापस (manuf == 0x17 && impl == 0x13);
पूर्ण

काष्ठा freq_table अणु
	अचिन्हित दीर्घ घड़ी_प्रकारick_ref;
	अचिन्हित पूर्णांक ref_freq;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा freq_table, sparc64_freq_table) = अणु 0, 0 पूर्ण;

अचिन्हित दीर्घ sparc64_get_घड़ी_प्रकारick(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा freq_table *ft = &per_cpu(sparc64_freq_table, cpu);

	अगर (ft->घड़ी_प्रकारick_ref)
		वापस ft->घड़ी_प्रकारick_ref;
	वापस cpu_data(cpu).घड़ी_प्रकारick;
पूर्ण
EXPORT_SYMBOL(sparc64_get_घड़ी_प्रकारick);

#अगर_घोषित CONFIG_CPU_FREQ

अटल पूर्णांक sparc64_cpufreq_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				    व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	अचिन्हित पूर्णांक cpu;
	काष्ठा freq_table *ft;

	क्रम_each_cpu(cpu, freq->policy->cpus) अणु
		ft = &per_cpu(sparc64_freq_table, cpu);

		अगर (!ft->ref_freq) अणु
			ft->ref_freq = freq->old;
			ft->घड़ी_प्रकारick_ref = cpu_data(cpu).घड़ी_प्रकारick;
		पूर्ण

		अगर ((val == CPUFREQ_PRECHANGE  && freq->old < freq->new) ||
		    (val == CPUFREQ_POSTCHANGE && freq->old > freq->new)) अणु
			cpu_data(cpu).घड़ी_प्रकारick =
				cpufreq_scale(ft->घड़ी_प्रकारick_ref, ft->ref_freq,
					      freq->new);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block sparc64_cpufreq_notअगरier_block = अणु
	.notअगरier_call	= sparc64_cpufreq_notअगरier
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_sparc64_cpufreq_notअगरier(व्योम)
अणु

	cpufreq_रेजिस्टर_notअगरier(&sparc64_cpufreq_notअगरier_block,
				  CPUFREQ_TRANSITION_NOTIFIER);
	वापस 0;
पूर्ण

core_initcall(रेजिस्टर_sparc64_cpufreq_notअगरier);

#पूर्ण_अगर /* CONFIG_CPU_FREQ */

अटल पूर्णांक sparc64_next_event(अचिन्हित दीर्घ delta,
			      काष्ठा घड़ी_event_device *evt)
अणु
	वापस tick_operations.add_compare(delta) ? -ETIME : 0;
पूर्ण

अटल पूर्णांक sparc64_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	tick_operations.disable_irq();
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device sparc64_घड़ीevent = अणु
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= sparc64_समयr_shutकरोwn,
	.set_next_event		= sparc64_next_event,
	.rating			= 100,
	.shअगरt			= 30,
	.irq			= -1,
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, sparc64_events);

व्योम __irq_entry समयr_पूर्णांकerrupt(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित दीर्घ tick_mask = tick_operations.softपूर्णांक_mask;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *evt = &per_cpu(sparc64_events, cpu);

	clear_softपूर्णांक(tick_mask);

	irq_enter();

	local_cpu_data().irq0_irqs++;
	kstat_incr_irq_this_cpu(0);

	अगर (unlikely(!evt->event_handler)) अणु
		prपूर्णांकk(KERN_WARNING
		       "Spurious SPARC64 timer interrupt on cpu %d\n", cpu);
	पूर्ण अन्यथा
		evt->event_handler(evt);

	irq_निकास();

	set_irq_regs(old_regs);
पूर्ण

व्योम setup_sparc64_समयr(व्योम)
अणु
	काष्ठा घड़ी_event_device *sevt;
	अचिन्हित दीर्घ pstate;

	/* Guarantee that the following sequences execute
	 * unपूर्णांकerrupted.
	 */
	__यंत्र__ __अस्थिर__("rdpr	%%pstate, %0\n\t"
			     "wrpr	%0, %1, %%pstate"
			     : "=r" (pstate)
			     : "i" (PSTATE_IE));

	tick_operations.init_tick();

	/* Restore PSTATE_IE. */
	__यंत्र__ __अस्थिर__("wrpr	%0, 0x0, %%pstate"
			     : /* no outमाला_दो */
			     : "r" (pstate));

	sevt = this_cpu_ptr(&sparc64_events);

	स_नकल(sevt, &sparc64_घड़ीevent, माप(*sevt));
	sevt->cpumask = cpumask_of(smp_processor_id());

	घड़ीevents_रेजिस्टर_device(sevt);
पूर्ण

#घोषणा SPARC64_NSEC_PER_CYC_SHIFT	10UL

अटल काष्ठा घड़ीsource घड़ीsource_tick = अणु
	.rating		= 100,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल अचिन्हित दीर्घ tb_ticks_per_usec __पढ़ो_mostly;

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	अचिन्हित दीर्घ bघड़ी = get_tick();

	जबतक ((get_tick() - bघड़ी) < loops)
		;
पूर्ण
EXPORT_SYMBOL(__delay);

व्योम udelay(अचिन्हित दीर्घ usecs)
अणु
	__delay(tb_ticks_per_usec * usecs);
पूर्ण
EXPORT_SYMBOL(udelay);

अटल u64 घड़ीsource_tick_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस get_tick();
पूर्ण

अटल व्योम __init get_tick_patch(व्योम)
अणु
	अचिन्हित पूर्णांक *addr, *instr, i;
	काष्ठा get_tick_patch *p;

	अगर (tlb_type == spitfire && is_hummingbird())
		वापस;

	क्रम (p = &__get_tick_patch; p < &__get_tick_patch_end; p++) अणु
		instr = (tlb_type == spitfire) ? p->tick : p->stick;
		addr = (अचिन्हित पूर्णांक *)(अचिन्हित दीर्घ)p->addr;
		क्रम (i = 0; i < GET_TICK_NINSTR; i++) अणु
			addr[i] = instr[i];
			/* ensure that address is modअगरied beक्रमe flush */
			wmb();
			flushi(&addr[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init init_tick_ops(काष्ठा sparc64_tick_ops *ops)
अणु
	अचिन्हित दीर्घ freq, quotient, tick;

	freq = ops->get_frequency();
	quotient = घड़ीsource_hz2mult(freq, SPARC64_NSEC_PER_CYC_SHIFT);
	tick = ops->get_tick();

	ops->offset = (tick * quotient) >> SPARC64_NSEC_PER_CYC_SHIFT;
	ops->ticks_per_nsec_quotient = quotient;
	ops->frequency = freq;
	tick_operations = *ops;
	get_tick_patch();
पूर्ण

व्योम __init समय_init_early(व्योम)
अणु
	अगर (tlb_type == spitfire) अणु
		अगर (is_hummingbird()) अणु
			init_tick_ops(&hbtick_operations);
			घड़ीsource_tick.archdata.vघड़ी_mode = VCLOCK_NONE;
		पूर्ण अन्यथा अणु
			init_tick_ops(&tick_operations);
			घड़ीsource_tick.archdata.vघड़ी_mode = VCLOCK_TICK;
		पूर्ण
	पूर्ण अन्यथा अणु
		init_tick_ops(&stick_operations);
		घड़ीsource_tick.archdata.vघड़ी_mode = VCLOCK_STICK;
	पूर्ण
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	अचिन्हित दीर्घ freq;

	freq = tick_operations.frequency;
	tb_ticks_per_usec = freq / USEC_PER_SEC;

	घड़ीsource_tick.name = tick_operations.name;
	घड़ीsource_tick.पढ़ो = घड़ीsource_tick_पढ़ो;

	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_tick, freq);
	prपूर्णांकk("clocksource: mult[%x] shift[%d]\n",
	       घड़ीsource_tick.mult, घड़ीsource_tick.shअगरt);

	sparc64_घड़ीevent.name = tick_operations.name;
	घड़ीevents_calc_mult_shअगरt(&sparc64_घड़ीevent, freq, 4);

	sparc64_घड़ीevent.max_delta_ns =
		घड़ीevent_delta2ns(0x7fffffffffffffffUL, &sparc64_घड़ीevent);
	sparc64_घड़ीevent.max_delta_ticks = 0x7fffffffffffffffUL;
	sparc64_घड़ीevent.min_delta_ns =
		घड़ीevent_delta2ns(0xF, &sparc64_घड़ीevent);
	sparc64_घड़ीevent.min_delta_ticks = 0xF;

	prपूर्णांकk("clockevent: mult[%x] shift[%d]\n",
	       sparc64_घड़ीevent.mult, sparc64_घड़ीevent.shअगरt);

	setup_sparc64_समयr();
पूर्ण

अचिन्हित दीर्घ दीर्घ sched_घड़ी(व्योम)
अणु
	अचिन्हित दीर्घ quotient = tick_operations.ticks_per_nsec_quotient;
	अचिन्हित दीर्घ offset = tick_operations.offset;

	/* Use barrier so the compiler emits the loads first and overlaps load
	 * latency with पढ़ोing tick, because पढ़ोing %tick/%stick is a
	 * post-sync inकाष्ठाion that will flush and restart subsequent
	 * inकाष्ठाions after it commits.
	 */
	barrier();

	वापस ((get_tick() * quotient) >> SPARC64_NSEC_PER_CYC_SHIFT) - offset;
पूर्ण

पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val)
अणु
	*समयr_val = get_tick();
	वापस 0;
पूर्ण
