<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2007 Eugene Konev <ejka@खोलोwrt.org>
 * Copyright (C) 2009 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/mach-ar7/ar7.h>

#घोषणा BOOT_PLL_SOURCE_MASK	0x3
#घोषणा CPU_PLL_SOURCE_SHIFT	16
#घोषणा BUS_PLL_SOURCE_SHIFT	14
#घोषणा USB_PLL_SOURCE_SHIFT	18
#घोषणा DSP_PLL_SOURCE_SHIFT	22
#घोषणा BOOT_PLL_SOURCE_AFE	0
#घोषणा BOOT_PLL_SOURCE_BUS	0
#घोषणा BOOT_PLL_SOURCE_REF	1
#घोषणा BOOT_PLL_SOURCE_XTAL	2
#घोषणा BOOT_PLL_SOURCE_CPU	3
#घोषणा BOOT_PLL_BYPASS		0x00000020
#घोषणा BOOT_PLL_ASYNC_MODE	0x02000000
#घोषणा BOOT_PLL_2TO1_MODE	0x00008000

#घोषणा TNETD7200_CLOCK_ID_CPU	0
#घोषणा TNETD7200_CLOCK_ID_DSP	1
#घोषणा TNETD7200_CLOCK_ID_USB	2

#घोषणा TNETD7200_DEF_CPU_CLK	211000000
#घोषणा TNETD7200_DEF_DSP_CLK	125000000
#घोषणा TNETD7200_DEF_USB_CLK	48000000

काष्ठा tnetd7300_घड़ी अणु
	u32 ctrl;
#घोषणा PREDIV_MASK	0x001f0000
#घोषणा PREDIV_SHIFT	16
#घोषणा POSTDIV_MASK	0x0000001f
	u32 unused1[3];
	u32 pll;
#घोषणा MUL_MASK	0x0000f000
#घोषणा MUL_SHIFT	12
#घोषणा PLL_MODE_MASK	0x00000001
#घोषणा PLL_NDIV	0x00000800
#घोषणा PLL_DIV		0x00000002
#घोषणा PLL_STATUS	0x00000001
	u32 unused2[3];
पूर्ण;

काष्ठा tnetd7300_घड़ीs अणु
	काष्ठा tnetd7300_घड़ी bus;
	काष्ठा tnetd7300_घड़ी cpu;
	काष्ठा tnetd7300_घड़ी usb;
	काष्ठा tnetd7300_घड़ी dsp;
पूर्ण;

काष्ठा tnetd7200_घड़ी अणु
	u32 ctrl;
	u32 unused1[3];
#घोषणा DIVISOR_ENABLE_MASK 0x00008000
	u32 mul;
	u32 preभाग;
	u32 postभाग;
	u32 postभाग2;
	u32 unused2[6];
	u32 cmd;
	u32 status;
	u32 cmden;
	u32 padding[15];
पूर्ण;

काष्ठा tnetd7200_घड़ीs अणु
	काष्ठा tnetd7200_घड़ी cpu;
	काष्ठा tnetd7200_घड़ी dsp;
	काष्ठा tnetd7200_घड़ी usb;
पूर्ण;

अटल काष्ठा clk bus_clk = अणु
	.rate	= 125000000,
पूर्ण;

अटल काष्ठा clk cpu_clk = अणु
	.rate	= 150000000,
पूर्ण;

अटल काष्ठा clk dsp_clk;
अटल काष्ठा clk vbus_clk;

अटल व्योम approximate(पूर्णांक base, पूर्णांक target, पूर्णांक *preभाग,
			पूर्णांक *postभाग, पूर्णांक *mul)
अणु
	पूर्णांक i, j, k, freq, res = target;
	क्रम (i = 1; i <= 16; i++)
		क्रम (j = 1; j <= 32; j++)
			क्रम (k = 1; k <= 32; k++) अणु
				freq = असल(base / j * i / k - target);
				अगर (freq < res) अणु
					res = freq;
					*mul = i;
					*preभाग = j;
					*postभाग = k;
				पूर्ण
			पूर्ण
पूर्ण

अटल व्योम calculate(पूर्णांक base, पूर्णांक target, पूर्णांक *preभाग, पूर्णांक *postभाग,
	पूर्णांक *mul)
अणु
	पूर्णांक पंचांगp_gcd, पंचांगp_base, पंचांगp_freq;

	क्रम (*preभाग = 1; *preभाग <= 32; (*preभाग)++) अणु
		पंचांगp_base = base / *preभाग;
		पंचांगp_gcd = gcd(target, पंचांगp_base);
		*mul = target / पंचांगp_gcd;
		*postभाग = पंचांगp_base / पंचांगp_gcd;
		अगर ((*mul < 1) || (*mul >= 16))
			जारी;
		अगर ((*postभाग > 0) & (*postभाग <= 32))
			अवरोध;
	पूर्ण

	अगर (base / *preभाग * *mul / *postभाग != target) अणु
		approximate(base, target, preभाग, postभाग, mul);
		पंचांगp_freq = base / *preभाग * *mul / *postभाग;
		prपूर्णांकk(KERN_WARNING
		       "Adjusted requested frequency %d to %d\n",
		       target, पंचांगp_freq);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "Clocks: prediv: %d, postdiv: %d, mul: %d\n",
	       *preभाग, *postभाग, *mul);
पूर्ण

अटल पूर्णांक tnetd7300_dsp_घड़ी(व्योम)
अणु
	u32 didr1, didr2;
	u8 rev = ar7_chip_rev();
	didr1 = पढ़ोl((व्योम *)KSEG1ADDR(AR7_REGS_GPIO + 0x18));
	didr2 = पढ़ोl((व्योम *)KSEG1ADDR(AR7_REGS_GPIO + 0x1c));
	अगर (didr2 & (1 << 23))
		वापस 0;
	अगर ((rev >= 0x23) && (rev != 0x57))
		वापस 250000000;
	अगर ((((didr2 & 0x1fff) << 10) | ((didr1 & 0xffc00000) >> 22))
	    > 4208000)
		वापस 250000000;
	वापस 0;
पूर्ण

अटल पूर्णांक tnetd7300_get_घड़ी(u32 shअगरt, काष्ठा tnetd7300_घड़ी *घड़ी,
	u32 *bootcr, u32 bus_घड़ी)
अणु
	पूर्णांक product;
	पूर्णांक base_घड़ी = AR7_REF_CLOCK;
	u32 ctrl = पढ़ोl(&घड़ी->ctrl);
	u32 pll = पढ़ोl(&घड़ी->pll);
	पूर्णांक preभाग = ((ctrl & PREDIV_MASK) >> PREDIV_SHIFT) + 1;
	पूर्णांक postभाग = (ctrl & POSTDIV_MASK) + 1;
	पूर्णांक भागisor = preभाग * postभाग;
	पूर्णांक mul = ((pll & MUL_MASK) >> MUL_SHIFT) + 1;

	चयन ((*bootcr & (BOOT_PLL_SOURCE_MASK << shअगरt)) >> shअगरt) अणु
	हाल BOOT_PLL_SOURCE_BUS:
		base_घड़ी = bus_घड़ी;
		अवरोध;
	हाल BOOT_PLL_SOURCE_REF:
		base_घड़ी = AR7_REF_CLOCK;
		अवरोध;
	हाल BOOT_PLL_SOURCE_XTAL:
		base_घड़ी = AR7_XTAL_CLOCK;
		अवरोध;
	हाल BOOT_PLL_SOURCE_CPU:
		base_घड़ी = cpu_clk.rate;
		अवरोध;
	पूर्ण

	अगर (*bootcr & BOOT_PLL_BYPASS)
		वापस base_घड़ी / भागisor;

	अगर ((pll & PLL_MODE_MASK) == 0)
		वापस (base_घड़ी >> (mul / 16 + 1)) / भागisor;

	अगर ((pll & (PLL_NDIV | PLL_DIV)) == (PLL_NDIV | PLL_DIV)) अणु
		product = (mul & 1) ?
			(base_घड़ी * mul) >> 1 :
			(base_घड़ी * (mul - 1)) >> 2;
		वापस product / भागisor;
	पूर्ण

	अगर (mul == 16)
		वापस base_घड़ी / भागisor;

	वापस base_घड़ी * mul / भागisor;
पूर्ण

अटल व्योम tnetd7300_set_घड़ी(u32 shअगरt, काष्ठा tnetd7300_घड़ी *घड़ी,
	u32 *bootcr, u32 frequency)
अणु
	पूर्णांक preभाग, postभाग, mul;
	पूर्णांक base_घड़ी = bus_clk.rate;

	चयन ((*bootcr & (BOOT_PLL_SOURCE_MASK << shअगरt)) >> shअगरt) अणु
	हाल BOOT_PLL_SOURCE_BUS:
		base_घड़ी = bus_clk.rate;
		अवरोध;
	हाल BOOT_PLL_SOURCE_REF:
		base_घड़ी = AR7_REF_CLOCK;
		अवरोध;
	हाल BOOT_PLL_SOURCE_XTAL:
		base_घड़ी = AR7_XTAL_CLOCK;
		अवरोध;
	हाल BOOT_PLL_SOURCE_CPU:
		base_घड़ी = cpu_clk.rate;
		अवरोध;
	पूर्ण

	calculate(base_घड़ी, frequency, &preभाग, &postभाग, &mul);

	ग_लिखोl(((preभाग - 1) << PREDIV_SHIFT) | (postभाग - 1), &घड़ी->ctrl);
	mdelay(1);
	ग_लिखोl(4, &घड़ी->pll);
	जबतक (पढ़ोl(&घड़ी->pll) & PLL_STATUS)
		;
	ग_लिखोl(((mul - 1) << MUL_SHIFT) | (0xff << 3) | 0x0e, &घड़ी->pll);
	mdelay(75);
पूर्ण

अटल व्योम __init tnetd7300_init_घड़ीs(व्योम)
अणु
	u32 *bootcr = (u32 *)ioremap(AR7_REGS_DCL, 4);
	काष्ठा tnetd7300_घड़ीs *घड़ीs =
					ioremap(UR8_REGS_CLOCKS,
					माप(काष्ठा tnetd7300_घड़ीs));

	bus_clk.rate = tnetd7300_get_घड़ी(BUS_PLL_SOURCE_SHIFT,
		&घड़ीs->bus, bootcr, AR7_AFE_CLOCK);

	अगर (*bootcr & BOOT_PLL_ASYNC_MODE)
		cpu_clk.rate = tnetd7300_get_घड़ी(CPU_PLL_SOURCE_SHIFT,
			&घड़ीs->cpu, bootcr, AR7_AFE_CLOCK);
	अन्यथा
		cpu_clk.rate = bus_clk.rate;

	अगर (dsp_clk.rate == 250000000)
		tnetd7300_set_घड़ी(DSP_PLL_SOURCE_SHIFT, &घड़ीs->dsp,
			bootcr, dsp_clk.rate);

	iounmap(घड़ीs);
	iounmap(bootcr);
पूर्ण

अटल व्योम tnetd7200_set_घड़ी(पूर्णांक base, काष्ठा tnetd7200_घड़ी *घड़ी,
	पूर्णांक preभाग, पूर्णांक postभाग, पूर्णांक postभाग2, पूर्णांक mul, u32 frequency)
अणु
	prपूर्णांकk(KERN_INFO
		"Clocks: base = %d, frequency = %u, prediv = %d, "
		"postdiv = %d, postdiv2 = %d, mul = %d\n",
		base, frequency, preभाग, postभाग, postभाग2, mul);

	ग_लिखोl(0, &घड़ी->ctrl);
	ग_लिखोl(DIVISOR_ENABLE_MASK | ((preभाग - 1) & 0x1F), &घड़ी->preभाग);
	ग_लिखोl((mul - 1) & 0xF, &घड़ी->mul);

	जबतक (पढ़ोl(&घड़ी->status) & 0x1)
		; /* nop */

	ग_लिखोl(DIVISOR_ENABLE_MASK | ((postभाग - 1) & 0x1F), &घड़ी->postभाग);

	ग_लिखोl(पढ़ोl(&घड़ी->cmden) | 1, &घड़ी->cmden);
	ग_लिखोl(पढ़ोl(&घड़ी->cmd) | 1, &घड़ी->cmd);

	जबतक (पढ़ोl(&घड़ी->status) & 0x1)
		; /* nop */

	ग_लिखोl(DIVISOR_ENABLE_MASK | ((postभाग2 - 1) & 0x1F), &घड़ी->postभाग2);

	ग_लिखोl(पढ़ोl(&घड़ी->cmden) | 1, &घड़ी->cmden);
	ग_लिखोl(पढ़ोl(&घड़ी->cmd) | 1, &घड़ी->cmd);

	जबतक (पढ़ोl(&घड़ी->status) & 0x1)
		; /* nop */

	ग_लिखोl(पढ़ोl(&घड़ी->ctrl) | 1, &घड़ी->ctrl);
पूर्ण

अटल पूर्णांक tnetd7200_get_घड़ी_base(पूर्णांक घड़ी_id, u32 *bootcr)
अणु
	अगर (*bootcr & BOOT_PLL_ASYNC_MODE)
		/* Async */
		चयन (घड़ी_id) अणु
		हाल TNETD7200_CLOCK_ID_DSP:
			वापस AR7_REF_CLOCK;
		शेष:
			वापस AR7_AFE_CLOCK;
		पूर्ण
	अन्यथा
		/* Sync */
		अगर (*bootcr & BOOT_PLL_2TO1_MODE)
			/* 2:1 */
			चयन (घड़ी_id) अणु
			हाल TNETD7200_CLOCK_ID_DSP:
				वापस AR7_REF_CLOCK;
			शेष:
				वापस AR7_AFE_CLOCK;
			पूर्ण
		अन्यथा
			/* 1:1 */
			वापस AR7_REF_CLOCK;
पूर्ण


अटल व्योम __init tnetd7200_init_घड़ीs(व्योम)
अणु
	u32 *bootcr = (u32 *)ioremap(AR7_REGS_DCL, 4);
	काष्ठा tnetd7200_घड़ीs *घड़ीs =
					ioremap(AR7_REGS_CLOCKS,
					माप(काष्ठा tnetd7200_घड़ीs));
	पूर्णांक cpu_base, cpu_mul, cpu_preभाग, cpu_postभाग;
	पूर्णांक dsp_base, dsp_mul, dsp_preभाग, dsp_postभाग;
	पूर्णांक usb_base, usb_mul, usb_preभाग, usb_postभाग;

	cpu_base = tnetd7200_get_घड़ी_base(TNETD7200_CLOCK_ID_CPU, bootcr);
	dsp_base = tnetd7200_get_घड़ी_base(TNETD7200_CLOCK_ID_DSP, bootcr);

	अगर (*bootcr & BOOT_PLL_ASYNC_MODE) अणु
		prपूर्णांकk(KERN_INFO "Clocks: Async mode\n");

		prपूर्णांकk(KERN_INFO "Clocks: Setting DSP clock\n");
		calculate(dsp_base, TNETD7200_DEF_DSP_CLK,
			&dsp_preभाग, &dsp_postभाग, &dsp_mul);
		bus_clk.rate =
			((dsp_base / dsp_preभाग) * dsp_mul) / dsp_postभाग;
		tnetd7200_set_घड़ी(dsp_base, &घड़ीs->dsp,
			dsp_preभाग, dsp_postभाग * 2, dsp_postभाग, dsp_mul * 2,
			bus_clk.rate);

		prपूर्णांकk(KERN_INFO "Clocks: Setting CPU clock\n");
		calculate(cpu_base, TNETD7200_DEF_CPU_CLK, &cpu_preभाग,
			&cpu_postभाग, &cpu_mul);
		cpu_clk.rate =
			((cpu_base / cpu_preभाग) * cpu_mul) / cpu_postभाग;
		tnetd7200_set_घड़ी(cpu_base, &घड़ीs->cpu,
			cpu_preभाग, cpu_postभाग, -1, cpu_mul,
			cpu_clk.rate);

	पूर्ण अन्यथा
		अगर (*bootcr & BOOT_PLL_2TO1_MODE) अणु
			prपूर्णांकk(KERN_INFO "Clocks: Sync 2:1 mode\n");

			prपूर्णांकk(KERN_INFO "Clocks: Setting CPU clock\n");
			calculate(cpu_base, TNETD7200_DEF_CPU_CLK, &cpu_preभाग,
				&cpu_postभाग, &cpu_mul);
			cpu_clk.rate = ((cpu_base / cpu_preभाग) * cpu_mul)
								/ cpu_postभाग;
			tnetd7200_set_घड़ी(cpu_base, &घड़ीs->cpu,
				cpu_preभाग, cpu_postभाग, -1, cpu_mul,
				cpu_clk.rate);

			prपूर्णांकk(KERN_INFO "Clocks: Setting DSP clock\n");
			calculate(dsp_base, TNETD7200_DEF_DSP_CLK, &dsp_preभाग,
				&dsp_postभाग, &dsp_mul);
			bus_clk.rate = cpu_clk.rate / 2;
			tnetd7200_set_घड़ी(dsp_base, &घड़ीs->dsp,
				dsp_preभाग, dsp_postभाग * 2, dsp_postभाग,
				dsp_mul * 2, bus_clk.rate);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "Clocks: Sync 1:1 mode\n");

			prपूर्णांकk(KERN_INFO "Clocks: Setting DSP clock\n");
			calculate(dsp_base, TNETD7200_DEF_DSP_CLK, &dsp_preभाग,
				&dsp_postभाग, &dsp_mul);
			bus_clk.rate = ((dsp_base / dsp_preभाग) * dsp_mul)
								/ dsp_postभाग;
			tnetd7200_set_घड़ी(dsp_base, &घड़ीs->dsp,
				dsp_preभाग, dsp_postभाग * 2, dsp_postभाग,
				dsp_mul * 2, bus_clk.rate);

			cpu_clk.rate = bus_clk.rate;
		पूर्ण

	prपूर्णांकk(KERN_INFO "Clocks: Setting USB clock\n");
	usb_base = bus_clk.rate;
	calculate(usb_base, TNETD7200_DEF_USB_CLK, &usb_preभाग,
		&usb_postभाग, &usb_mul);
	tnetd7200_set_घड़ी(usb_base, &घड़ीs->usb,
		usb_preभाग, usb_postभाग, -1, usb_mul,
		TNETD7200_DEF_USB_CLK);

	dsp_clk.rate = cpu_clk.rate;

	iounmap(घड़ीs);
	iounmap(bootcr);
पूर्ण

/*
 * Linux घड़ी API
 */
पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
पूर्ण
EXPORT_SYMBOL(clk_disable);

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk->rate;
पूर्ण
EXPORT_SYMBOL(clk_get_rate);

काष्ठा clk *clk_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	अगर (!म_भेद(id, "bus"))
		वापस &bus_clk;
	/* cpmac and vbus share the same rate */
	अगर (!म_भेद(id, "cpmac"))
		वापस &vbus_clk;
	अगर (!म_भेद(id, "cpu"))
		वापस &cpu_clk;
	अगर (!म_भेद(id, "dsp"))
		वापस &dsp_clk;
	अगर (!म_भेद(id, "vbus"))
		वापस &vbus_clk;
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL(clk_get);

व्योम clk_put(काष्ठा clk *clk)
अणु
पूर्ण
EXPORT_SYMBOL(clk_put);

व्योम __init ar7_init_घड़ीs(व्योम)
अणु
	चयन (ar7_chip_id()) अणु
	हाल AR7_CHIP_7100:
	हाल AR7_CHIP_7200:
		tnetd7200_init_घड़ीs();
		अवरोध;
	हाल AR7_CHIP_7300:
		dsp_clk.rate = tnetd7300_dsp_घड़ी();
		tnetd7300_init_घड़ीs();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* adjust vbus घड़ी rate */
	vbus_clk.rate = bus_clk.rate / 2;
पूर्ण

/* dummy functions, should not be called */
दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_round_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	WARN_ON(clk);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(clk_get_parent);
