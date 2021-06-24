<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयx.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पन.स>

/* IBM Summit (EXA) Cyclone counter code*/
#घोषणा CYCLONE_CBAR_ADDR 0xFEB00CD0
#घोषणा CYCLONE_PMCC_OFFSET 0x51A0
#घोषणा CYCLONE_MPMC_OFFSET 0x51D0
#घोषणा CYCLONE_MPCS_OFFSET 0x51A8
#घोषणा CYCLONE_TIMER_FREQ 100000000

पूर्णांक use_cyclone;
व्योम __init cyclone_setup(व्योम)
अणु
	use_cyclone = 1;
पूर्ण

अटल व्योम __iomem *cyclone_mc;

अटल u64 पढ़ो_cyclone(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)पढ़ोq((व्योम __iomem *)cyclone_mc);
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_cyclone = अणु
        .name           = "cyclone",
        .rating         = 300,
        .पढ़ो           = पढ़ो_cyclone,
        .mask           = (1LL << 40) - 1,
        .flags          = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

पूर्णांक __init init_cyclone_घड़ी(व्योम)
अणु
	u64 __iomem *reg;
	u64 base;	/* saved cyclone base address */
	u64 offset;	/* offset from pageaddr to cyclone_समयr रेजिस्टर */
	पूर्णांक i;
	u32 __iomem *cyclone_समयr;	/* Cyclone MPMC0 रेजिस्टर */

	अगर (!use_cyclone)
		वापस 0;

	prपूर्णांकk(KERN_INFO "Summit chipset: Starting Cyclone Counter.\n");

	/* find base address */
	offset = (CYCLONE_CBAR_ADDR);
	reg = ioremap(offset, माप(u64));
	अगर(!reg)अणु
		prपूर्णांकk(KERN_ERR "Summit chipset: Could not find valid CBAR"
				" register.\n");
		use_cyclone = 0;
		वापस -ENODEV;
	पूर्ण
	base = पढ़ोq(reg);
	iounmap(reg);
	अगर(!base)अणु
		prपूर्णांकk(KERN_ERR "Summit chipset: Could not find valid CBAR"
				" value.\n");
		use_cyclone = 0;
		वापस -ENODEV;
	पूर्ण

	/* setup PMCC */
	offset = (base + CYCLONE_PMCC_OFFSET);
	reg = ioremap(offset, माप(u64));
	अगर(!reg)अणु
		prपूर्णांकk(KERN_ERR "Summit chipset: Could not find valid PMCC"
				" register.\n");
		use_cyclone = 0;
		वापस -ENODEV;
	पूर्ण
	ग_लिखोl(0x00000001,reg);
	iounmap(reg);

	/* setup MPCS */
	offset = (base + CYCLONE_MPCS_OFFSET);
	reg = ioremap(offset, माप(u64));
	अगर(!reg)अणु
		prपूर्णांकk(KERN_ERR "Summit chipset: Could not find valid MPCS"
				" register.\n");
		use_cyclone = 0;
		वापस -ENODEV;
	पूर्ण
	ग_लिखोl(0x00000001,reg);
	iounmap(reg);

	/* map in cyclone_समयr */
	offset = (base + CYCLONE_MPMC_OFFSET);
	cyclone_समयr = ioremap(offset, माप(u32));
	अगर(!cyclone_समयr)अणु
		prपूर्णांकk(KERN_ERR "Summit chipset: Could not find valid MPMC"
				" register.\n");
		use_cyclone = 0;
		वापस -ENODEV;
	पूर्ण

	/*quick test to make sure its ticking*/
	क्रम(i=0; i<3; i++)अणु
		u32 old = पढ़ोl(cyclone_समयr);
		पूर्णांक stall = 100;
		जबतक(stall--) barrier();
		अगर(पढ़ोl(cyclone_समयr) == old)अणु
			prपूर्णांकk(KERN_ERR "Summit chipset: Counter not counting!"
					" DISABLED\n");
			iounmap(cyclone_समयr);
			cyclone_समयr = शून्य;
			use_cyclone = 0;
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	/* initialize last tick */
	cyclone_mc = cyclone_समयr;
	घड़ीsource_cyclone.archdata.fsys_mmio = cyclone_समयr;
	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_cyclone, CYCLONE_TIMER_FREQ);

	वापस 0;
पूर्ण

__initcall(init_cyclone_घड़ी);
