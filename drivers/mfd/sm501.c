<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/mfd/sm501.c
 *
 * Copyright (C) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	Vincent Sanders <vince@simtec.co.uk>
 *
 * SM501 MFD driver
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/slab.h>

#समावेश <linux/sm501.h>
#समावेश <linux/sm501-regs.h>
#समावेश <linux/serial_8250.h>

#समावेश <linux/पन.स>

काष्ठा sm501_device अणु
	काष्ठा list_head		list;
	काष्ठा platक्रमm_device		pdev;
पूर्ण;

काष्ठा sm501_gpio;

#अगर_घोषित CONFIG_MFD_SM501_GPIO
#समावेश <linux/gpपन.स>

काष्ठा sm501_gpio_chip अणु
	काष्ठा gpio_chip	gpio;
	काष्ठा sm501_gpio	*ourgpio;	/* to get back to parent. */
	व्योम __iomem		*regbase;
	व्योम __iomem		*control;	/* address of control reg. */
पूर्ण;

काष्ठा sm501_gpio अणु
	काष्ठा sm501_gpio_chip	low;
	काष्ठा sm501_gpio_chip	high;
	spinlock_t		lock;

	अचिन्हित पूर्णांक		 रेजिस्टरed : 1;
	व्योम __iomem		*regs;
	काष्ठा resource		*regs_res;
पूर्ण;
#अन्यथा
काष्ठा sm501_gpio अणु
	/* no gpio support, empty definition क्रम sm501_devdata. */
पूर्ण;
#पूर्ण_अगर

काष्ठा sm501_devdata अणु
	spinlock_t			 reg_lock;
	काष्ठा mutex			 घड़ी_lock;
	काष्ठा list_head		 devices;
	काष्ठा sm501_gpio		 gpio;

	काष्ठा device			*dev;
	काष्ठा resource			*io_res;
	काष्ठा resource			*mem_res;
	काष्ठा resource			*regs_claim;
	काष्ठा sm501_platdata		*platdata;


	अचिन्हित पूर्णांक			 in_suspend;
	अचिन्हित दीर्घ			 pm_misc;

	पूर्णांक				 unit_घातer[20];
	अचिन्हित पूर्णांक			 pdev_id;
	अचिन्हित पूर्णांक			 irq;
	व्योम __iomem			*regs;
	अचिन्हित पूर्णांक			 rev;
पूर्ण;


#घोषणा MHZ (1000 * 1000)

#अगर_घोषित DEBUG
अटल स्थिर अचिन्हित पूर्णांक भाग_प्रकारab[] = अणु
	[0]		= 1,
	[1]		= 2,
	[2]		= 4,
	[3]		= 8,
	[4]		= 16,
	[5]		= 32,
	[6]		= 64,
	[7]		= 128,
	[8]		= 3,
	[9]		= 6,
	[10]	        = 12,
	[11]		= 24,
	[12]		= 48,
	[13]		= 96,
	[14]		= 192,
	[15]		= 384,
	[16]		= 5,
	[17]		= 10,
	[18]		= 20,
	[19]		= 40,
	[20]		= 80,
	[21]		= 160,
	[22]		= 320,
	[23]		= 604,
पूर्ण;

अटल अचिन्हित दीर्घ decode_भाग(अचिन्हित दीर्घ pll2, अचिन्हित दीर्घ val,
				अचिन्हित पूर्णांक lshft, अचिन्हित पूर्णांक selbit,
				अचिन्हित दीर्घ mask)
अणु
	अगर (val & selbit)
		pll2 = 288 * MHZ;

	वापस pll2 / भाग_प्रकारab[(val >> lshft) & mask];
पूर्ण

#घोषणा fmt_freq(x) ((x) / MHZ), ((x) % MHZ), (x)

/* sm501_dump_clk
 *
 * Prपूर्णांक out the current घड़ी configuration क्रम the device
*/

अटल व्योम sm501_dump_clk(काष्ठा sm501_devdata *sm)
अणु
	अचिन्हित दीर्घ misct = smc501_पढ़ोl(sm->regs + SM501_MISC_TIMING);
	अचिन्हित दीर्घ pm0 = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_0_CLOCK);
	अचिन्हित दीर्घ pm1 = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_1_CLOCK);
	अचिन्हित दीर्घ pmc = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_CONTROL);
	अचिन्हित दीर्घ sdclk0, sdclk1;
	अचिन्हित दीर्घ pll2 = 0;

	चयन (misct & 0x30) अणु
	हाल 0x00:
		pll2 = 336 * MHZ;
		अवरोध;
	हाल 0x10:
		pll2 = 288 * MHZ;
		अवरोध;
	हाल 0x20:
		pll2 = 240 * MHZ;
		अवरोध;
	हाल 0x30:
		pll2 = 192 * MHZ;
		अवरोध;
	पूर्ण

	sdclk0 = (misct & (1<<12)) ? pll2 : 288 * MHZ;
	sdclk0 /= भाग_प्रकारab[((misct >> 8) & 0xf)];

	sdclk1 = (misct & (1<<20)) ? pll2 : 288 * MHZ;
	sdclk1 /= भाग_प्रकारab[((misct >> 16) & 0xf)];

	dev_dbg(sm->dev, "MISCT=%08lx, PM0=%08lx, PM1=%08lx\n",
		misct, pm0, pm1);

	dev_dbg(sm->dev, "PLL2 = %ld.%ld MHz (%ld), SDCLK0=%08lx, SDCLK1=%08lx\n",
		fmt_freq(pll2), sdclk0, sdclk1);

	dev_dbg(sm->dev, "SDRAM: PM0=%ld, PM1=%ld\n", sdclk0, sdclk1);

	dev_dbg(sm->dev, "PM0[%c]: "
		 "P2 %ld.%ld MHz (%ld), V2 %ld.%ld (%ld), "
		 "M %ld.%ld (%ld), MX1 %ld.%ld (%ld)\n",
		 (pmc & 3 ) == 0 ? '*' : '-',
		 fmt_freq(decode_भाग(pll2, pm0, 24, 1<<29, 31)),
		 fmt_freq(decode_भाग(pll2, pm0, 16, 1<<20, 15)),
		 fmt_freq(decode_भाग(pll2, pm0, 8,  1<<12, 15)),
		 fmt_freq(decode_भाग(pll2, pm0, 0,  1<<4,  15)));

	dev_dbg(sm->dev, "PM1[%c]: "
		"P2 %ld.%ld MHz (%ld), V2 %ld.%ld (%ld), "
		"M %ld.%ld (%ld), MX1 %ld.%ld (%ld)\n",
		(pmc & 3 ) == 1 ? '*' : '-',
		fmt_freq(decode_भाग(pll2, pm1, 24, 1<<29, 31)),
		fmt_freq(decode_भाग(pll2, pm1, 16, 1<<20, 15)),
		fmt_freq(decode_भाग(pll2, pm1, 8,  1<<12, 15)),
		fmt_freq(decode_भाग(pll2, pm1, 0,  1<<4,  15)));
पूर्ण

अटल व्योम sm501_dump_regs(काष्ठा sm501_devdata *sm)
अणु
	व्योम __iomem *regs = sm->regs;

	dev_info(sm->dev, "System Control   %08x\n",
			smc501_पढ़ोl(regs + SM501_SYSTEM_CONTROL));
	dev_info(sm->dev, "Misc Control     %08x\n",
			smc501_पढ़ोl(regs + SM501_MISC_CONTROL));
	dev_info(sm->dev, "GPIO Control Low %08x\n",
			smc501_पढ़ोl(regs + SM501_GPIO31_0_CONTROL));
	dev_info(sm->dev, "GPIO Control Hi  %08x\n",
			smc501_पढ़ोl(regs + SM501_GPIO63_32_CONTROL));
	dev_info(sm->dev, "DRAM Control     %08x\n",
			smc501_पढ़ोl(regs + SM501_DRAM_CONTROL));
	dev_info(sm->dev, "Arbitration Ctrl %08x\n",
			smc501_पढ़ोl(regs + SM501_ARBTRTN_CONTROL));
	dev_info(sm->dev, "Misc Timing      %08x\n",
			smc501_पढ़ोl(regs + SM501_MISC_TIMING));
पूर्ण

अटल व्योम sm501_dump_gate(काष्ठा sm501_devdata *sm)
अणु
	dev_info(sm->dev, "CurrentGate      %08x\n",
			smc501_पढ़ोl(sm->regs + SM501_CURRENT_GATE));
	dev_info(sm->dev, "CurrentClock     %08x\n",
			smc501_पढ़ोl(sm->regs + SM501_CURRENT_CLOCK));
	dev_info(sm->dev, "PowerModeControl %08x\n",
			smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_CONTROL));
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम sm501_dump_gate(काष्ठा sm501_devdata *sm) अणु पूर्ण
अटल अंतरभूत व्योम sm501_dump_regs(काष्ठा sm501_devdata *sm) अणु पूर्ण
अटल अंतरभूत व्योम sm501_dump_clk(काष्ठा sm501_devdata *sm) अणु पूर्ण
#पूर्ण_अगर

/* sm501_sync_regs
 *
 * ensure the
*/

अटल व्योम sm501_sync_regs(काष्ठा sm501_devdata *sm)
अणु
	smc501_पढ़ोl(sm->regs);
पूर्ण

अटल अंतरभूत व्योम sm501_mdelay(काष्ठा sm501_devdata *sm, अचिन्हित पूर्णांक delay)
अणु
	/* during suspend/resume, we are currently not allowed to sleep,
	 * so change to using mdelay() instead of msleep() अगर we
	 * are in one of these paths */

	अगर (sm->in_suspend)
		mdelay(delay);
	अन्यथा
		msleep(delay);
पूर्ण

/* sm501_misc_control
 *
 * alters the miscellaneous control parameters
*/

पूर्णांक sm501_misc_control(काष्ठा device *dev,
		       अचिन्हित दीर्घ set, अचिन्हित दीर्घ clear)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ misc;
	अचिन्हित दीर्घ save;
	अचिन्हित दीर्घ to;

	spin_lock_irqsave(&sm->reg_lock, save);

	misc = smc501_पढ़ोl(sm->regs + SM501_MISC_CONTROL);
	to = (misc & ~clear) | set;

	अगर (to != misc) अणु
		smc501_ग_लिखोl(to, sm->regs + SM501_MISC_CONTROL);
		sm501_sync_regs(sm);

		dev_dbg(sm->dev, "MISC_CONTROL %08lx\n", misc);
	पूर्ण

	spin_unlock_irqrestore(&sm->reg_lock, save);
	वापस to;
पूर्ण

EXPORT_SYMBOL_GPL(sm501_misc_control);

/* sm501_modअगरy_reg
 *
 * Modअगरy a रेजिस्टर in the SM501 which may be shared with other
 * drivers.
*/

अचिन्हित दीर्घ sm501_modअगरy_reg(काष्ठा device *dev,
			       अचिन्हित दीर्घ reg,
			       अचिन्हित दीर्घ set,
			       अचिन्हित दीर्घ clear)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ save;

	spin_lock_irqsave(&sm->reg_lock, save);

	data = smc501_पढ़ोl(sm->regs + reg);
	data |= set;
	data &= ~clear;

	smc501_ग_लिखोl(data, sm->regs + reg);
	sm501_sync_regs(sm);

	spin_unlock_irqrestore(&sm->reg_lock, save);

	वापस data;
पूर्ण

EXPORT_SYMBOL_GPL(sm501_modअगरy_reg);

/* sm501_unit_घातer
 *
 * alters the घातer active gate to set specअगरic units on or off
 */

पूर्णांक sm501_unit_घातer(काष्ठा device *dev, अचिन्हित पूर्णांक unit, अचिन्हित पूर्णांक to)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ mode;
	अचिन्हित दीर्घ gate;
	अचिन्हित दीर्घ घड़ी;

	mutex_lock(&sm->घड़ी_lock);

	mode = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_CONTROL);
	gate = smc501_पढ़ोl(sm->regs + SM501_CURRENT_GATE);
	घड़ी = smc501_पढ़ोl(sm->regs + SM501_CURRENT_CLOCK);

	mode &= 3;		/* get current घातer mode */

	अगर (unit >= ARRAY_SIZE(sm->unit_घातer)) अणु
		dev_err(dev, "%s: bad unit %d\n", __func__, unit);
		जाओ alपढ़ोy;
	पूर्ण

	dev_dbg(sm->dev, "%s: unit %d, cur %d, to %d\n", __func__, unit,
		sm->unit_घातer[unit], to);

	अगर (to == 0 && sm->unit_घातer[unit] == 0) अणु
		dev_err(sm->dev, "unit %d is already shutdown\n", unit);
		जाओ alपढ़ोy;
	पूर्ण

	sm->unit_घातer[unit] += to ? 1 : -1;
	to = sm->unit_घातer[unit] ? 1 : 0;

	अगर (to) अणु
		अगर (gate & (1 << unit))
			जाओ alपढ़ोy;
		gate |= (1 << unit);
	पूर्ण अन्यथा अणु
		अगर (!(gate & (1 << unit)))
			जाओ alपढ़ोy;
		gate &= ~(1 << unit);
	पूर्ण

	चयन (mode) अणु
	हाल 1:
		smc501_ग_लिखोl(gate, sm->regs + SM501_POWER_MODE_0_GATE);
		smc501_ग_लिखोl(घड़ी, sm->regs + SM501_POWER_MODE_0_CLOCK);
		mode = 0;
		अवरोध;
	हाल 2:
	हाल 0:
		smc501_ग_लिखोl(gate, sm->regs + SM501_POWER_MODE_1_GATE);
		smc501_ग_लिखोl(घड़ी, sm->regs + SM501_POWER_MODE_1_CLOCK);
		mode = 1;
		अवरोध;

	शेष:
		gate = -1;
		जाओ alपढ़ोy;
	पूर्ण

	smc501_ग_लिखोl(mode, sm->regs + SM501_POWER_MODE_CONTROL);
	sm501_sync_regs(sm);

	dev_dbg(sm->dev, "gate %08lx, clock %08lx, mode %08lx\n",
		gate, घड़ी, mode);

	sm501_mdelay(sm, 16);

 alपढ़ोy:
	mutex_unlock(&sm->घड़ी_lock);
	वापस gate;
पूर्ण

EXPORT_SYMBOL_GPL(sm501_unit_घातer);

/* घड़ी value काष्ठाure. */
काष्ठा sm501_घड़ी अणु
	अचिन्हित दीर्घ mclk;
	पूर्णांक भागider;
	पूर्णांक shअगरt;
	अचिन्हित पूर्णांक m, n, k;
पूर्ण;

/* sm501_calc_घड़ी
 *
 * Calculates the nearest discrete घड़ी frequency that
 * can be achieved with the specअगरied input घड़ी.
 *   the maximum भागisor is 3 or 5
 */

अटल पूर्णांक sm501_calc_घड़ी(अचिन्हित दीर्घ freq,
			    काष्ठा sm501_घड़ी *घड़ी,
			    पूर्णांक max_भाग,
			    अचिन्हित दीर्घ mclk,
			    दीर्घ *best_dअगरf)
अणु
	पूर्णांक ret = 0;
	पूर्णांक भागider;
	पूर्णांक shअगरt;
	दीर्घ dअगरf;

	/* try भागiders 1 and 3 क्रम CRT and क्रम panel,
	   try भागider 5 क्रम panel only.*/

	क्रम (भागider = 1; भागider <= max_भाग; भागider += 2) अणु
		/* try all 8 shअगरt values.*/
		क्रम (shअगरt = 0; shअगरt < 8; shअगरt++) अणु
			/* Calculate dअगरference to requested घड़ी */
			dअगरf = DIV_ROUND_CLOSEST(mclk, भागider << shअगरt) - freq;
			अगर (dअगरf < 0)
				dअगरf = -dअगरf;

			/* If it is less than the current, use it */
			अगर (dअगरf < *best_dअगरf) अणु
				*best_dअगरf = dअगरf;

				घड़ी->mclk = mclk;
				घड़ी->भागider = भागider;
				घड़ी->shअगरt = shअगरt;
				ret = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* sm501_calc_pll
 *
 * Calculates the nearest discrete घड़ी frequency that can be
 * achieved using the programmable PLL.
 *   the maximum भागisor is 3 or 5
 */

अटल अचिन्हित दीर्घ sm501_calc_pll(अचिन्हित दीर्घ freq,
					काष्ठा sm501_घड़ी *घड़ी,
					पूर्णांक max_भाग)
अणु
	अचिन्हित दीर्घ mclk;
	अचिन्हित पूर्णांक m, n, k;
	दीर्घ best_dअगरf = 999999999;

	/*
	 * The SM502 datasheet करोesn't specअगरy the min/max values क्रम M and N.
	 * N = 1 at least करोesn't work in practice.
	 */
	क्रम (m = 2; m <= 255; m++) अणु
		क्रम (n = 2; n <= 127; n++) अणु
			क्रम (k = 0; k <= 1; k++) अणु
				mclk = (24000000UL * m / n) >> k;

				अगर (sm501_calc_घड़ी(freq, घड़ी, max_भाग,
						     mclk, &best_dअगरf)) अणु
					घड़ी->m = m;
					घड़ी->n = n;
					घड़ी->k = k;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Return best घड़ी. */
	वापस घड़ी->mclk / (घड़ी->भागider << घड़ी->shअगरt);
पूर्ण

/* sm501_select_घड़ी
 *
 * Calculates the nearest discrete घड़ी frequency that can be
 * achieved using the 288MHz and 336MHz PLLs.
 *   the maximum भागisor is 3 or 5
 */

अटल अचिन्हित दीर्घ sm501_select_घड़ी(अचिन्हित दीर्घ freq,
					काष्ठा sm501_घड़ी *घड़ी,
					पूर्णांक max_भाग)
अणु
	अचिन्हित दीर्घ mclk;
	दीर्घ best_dअगरf = 999999999;

	/* Try 288MHz and 336MHz घड़ीs. */
	क्रम (mclk = 288000000; mclk <= 336000000; mclk += 48000000) अणु
		sm501_calc_घड़ी(freq, घड़ी, max_भाग, mclk, &best_dअगरf);
	पूर्ण

	/* Return best घड़ी. */
	वापस घड़ी->mclk / (घड़ी->भागider << घड़ी->shअगरt);
पूर्ण

/* sm501_set_घड़ी
 *
 * set one of the four घड़ी sources to the बंदst available frequency to
 *  the one specअगरied
*/

अचिन्हित दीर्घ sm501_set_घड़ी(काष्ठा device *dev,
			      पूर्णांक clksrc,
			      अचिन्हित दीर्घ req_freq)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ mode = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_CONTROL);
	अचिन्हित दीर्घ gate = smc501_पढ़ोl(sm->regs + SM501_CURRENT_GATE);
	अचिन्हित दीर्घ घड़ी = smc501_पढ़ोl(sm->regs + SM501_CURRENT_CLOCK);
	अचिन्हित पूर्णांक pll_reg = 0;
	अचिन्हित दीर्घ sm501_freq; /* the actual frequency achieved */
	u64 reg;

	काष्ठा sm501_घड़ी to;

	/* find achivable discrete frequency and setup रेजिस्टर value
	 * accordingly, V2XCLK, MCLK and M1XCLK are the same P2XCLK
	 * has an extra bit क्रम the भागider */

	चयन (clksrc) अणु
	हाल SM501_CLOCK_P2XCLK:
		/* This घड़ी is भागided in half so to achieve the
		 * requested frequency the value must be multiplied by
		 * 2. This घड़ी also has an additional pre भागisor */

		अगर (sm->rev >= 0xC0) अणु
			/* SM502 -> use the programmable PLL */
			sm501_freq = (sm501_calc_pll(2 * req_freq,
						     &to, 5) / 2);
			reg = to.shअगरt & 0x07;/* bottom 3 bits are shअगरt */
			अगर (to.भागider == 3)
				reg |= 0x08; /* /3 भागider required */
			अन्यथा अगर (to.भागider == 5)
				reg |= 0x10; /* /5 भागider required */
			reg |= 0x40; /* select the programmable PLL */
			pll_reg = 0x20000 | (to.k << 15) | (to.n << 8) | to.m;
		पूर्ण अन्यथा अणु
			sm501_freq = (sm501_select_घड़ी(2 * req_freq,
							 &to, 5) / 2);
			reg = to.shअगरt & 0x07;/* bottom 3 bits are shअगरt */
			अगर (to.भागider == 3)
				reg |= 0x08; /* /3 भागider required */
			अन्यथा अगर (to.भागider == 5)
				reg |= 0x10; /* /5 भागider required */
			अगर (to.mclk != 288000000)
				reg |= 0x20; /* which mclk pll is source */
		पूर्ण
		अवरोध;

	हाल SM501_CLOCK_V2XCLK:
		/* This घड़ी is भागided in half so to achieve the
		 * requested frequency the value must be multiplied by 2. */

		sm501_freq = (sm501_select_घड़ी(2 * req_freq, &to, 3) / 2);
		reg=to.shअगरt & 0x07;	/* bottom 3 bits are shअगरt */
		अगर (to.भागider == 3)
			reg |= 0x08;	/* /3 भागider required */
		अगर (to.mclk != 288000000)
			reg |= 0x10;	/* which mclk pll is source */
		अवरोध;

	हाल SM501_CLOCK_MCLK:
	हाल SM501_CLOCK_M1XCLK:
		/* These घड़ीs are the same and not further भागided */

		sm501_freq = sm501_select_घड़ी( req_freq, &to, 3);
		reg=to.shअगरt & 0x07;	/* bottom 3 bits are shअगरt */
		अगर (to.भागider == 3)
			reg |= 0x08;	/* /3 भागider required */
		अगर (to.mclk != 288000000)
			reg |= 0x10;	/* which mclk pll is source */
		अवरोध;

	शेष:
		वापस 0; /* this is bad */
	पूर्ण

	mutex_lock(&sm->घड़ी_lock);

	mode = smc501_पढ़ोl(sm->regs + SM501_POWER_MODE_CONTROL);
	gate = smc501_पढ़ोl(sm->regs + SM501_CURRENT_GATE);
	घड़ी = smc501_पढ़ोl(sm->regs + SM501_CURRENT_CLOCK);

	घड़ी = घड़ी & ~(0xFF << clksrc);
	घड़ी |= reg<<clksrc;

	mode &= 3;	/* find current mode */

	चयन (mode) अणु
	हाल 1:
		smc501_ग_लिखोl(gate, sm->regs + SM501_POWER_MODE_0_GATE);
		smc501_ग_लिखोl(घड़ी, sm->regs + SM501_POWER_MODE_0_CLOCK);
		mode = 0;
		अवरोध;
	हाल 2:
	हाल 0:
		smc501_ग_लिखोl(gate, sm->regs + SM501_POWER_MODE_1_GATE);
		smc501_ग_लिखोl(घड़ी, sm->regs + SM501_POWER_MODE_1_CLOCK);
		mode = 1;
		अवरोध;

	शेष:
		mutex_unlock(&sm->घड़ी_lock);
		वापस -1;
	पूर्ण

	smc501_ग_लिखोl(mode, sm->regs + SM501_POWER_MODE_CONTROL);

	अगर (pll_reg)
		smc501_ग_लिखोl(pll_reg,
				sm->regs + SM501_PROGRAMMABLE_PLL_CONTROL);

	sm501_sync_regs(sm);

	dev_dbg(sm->dev, "gate %08lx, clock %08lx, mode %08lx\n",
		gate, घड़ी, mode);

	sm501_mdelay(sm, 16);
	mutex_unlock(&sm->घड़ी_lock);

	sm501_dump_clk(sm);

	वापस sm501_freq;
पूर्ण

EXPORT_SYMBOL_GPL(sm501_set_घड़ी);

/* sm501_find_घड़ी
 *
 * finds the बंदst available frequency क्रम a given घड़ी
*/

अचिन्हित दीर्घ sm501_find_घड़ी(काष्ठा device *dev,
			       पूर्णांक clksrc,
			       अचिन्हित दीर्घ req_freq)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ sm501_freq; /* the frequency achieveable by the 501 */
	काष्ठा sm501_घड़ी to;

	चयन (clksrc) अणु
	हाल SM501_CLOCK_P2XCLK:
		अगर (sm->rev >= 0xC0) अणु
			/* SM502 -> use the programmable PLL */
			sm501_freq = (sm501_calc_pll(2 * req_freq,
						     &to, 5) / 2);
		पूर्ण अन्यथा अणु
			sm501_freq = (sm501_select_घड़ी(2 * req_freq,
							 &to, 5) / 2);
		पूर्ण
		अवरोध;

	हाल SM501_CLOCK_V2XCLK:
		sm501_freq = (sm501_select_घड़ी(2 * req_freq, &to, 3) / 2);
		अवरोध;

	हाल SM501_CLOCK_MCLK:
	हाल SM501_CLOCK_M1XCLK:
		sm501_freq = sm501_select_घड़ी(req_freq, &to, 3);
		अवरोध;

	शेष:
		sm501_freq = 0;		/* error */
	पूर्ण

	वापस sm501_freq;
पूर्ण

EXPORT_SYMBOL_GPL(sm501_find_घड़ी);

अटल काष्ठा sm501_device *to_sm_device(काष्ठा platक्रमm_device *pdev)
अणु
	वापस container_of(pdev, काष्ठा sm501_device, pdev);
पूर्ण

/* sm501_device_release
 *
 * A release function क्रम the platक्रमm devices we create to allow us to
 * मुक्त any items we allocated
*/

अटल व्योम sm501_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_sm_device(to_platक्रमm_device(dev)));
पूर्ण

/* sm501_create_subdev
 *
 * Create a skeleton platक्रमm device with resources क्रम passing to a
 * sub-driver
*/

अटल काष्ठा platक्रमm_device *
sm501_create_subdev(काष्ठा sm501_devdata *sm, अक्षर *name,
		    अचिन्हित पूर्णांक res_count, अचिन्हित पूर्णांक platक्रमm_data_size)
अणु
	काष्ठा sm501_device *smdev;

	smdev = kzalloc(माप(काष्ठा sm501_device) +
			(माप(काष्ठा resource) * res_count) +
			platक्रमm_data_size, GFP_KERNEL);
	अगर (!smdev)
		वापस शून्य;

	smdev->pdev.dev.release = sm501_device_release;

	smdev->pdev.name = name;
	smdev->pdev.id = sm->pdev_id;
	smdev->pdev.dev.parent = sm->dev;
	smdev->pdev.dev.coherent_dma_mask = 0xffffffff;

	अगर (res_count) अणु
		smdev->pdev.resource = (काष्ठा resource *)(smdev+1);
		smdev->pdev.num_resources = res_count;
	पूर्ण
	अगर (platक्रमm_data_size)
		smdev->pdev.dev.platक्रमm_data = (व्योम *)(smdev+1);

	वापस &smdev->pdev;
पूर्ण

/* sm501_रेजिस्टर_device
 *
 * Register a platक्रमm device created with sm501_create_subdev()
*/

अटल पूर्णांक sm501_रेजिस्टर_device(काष्ठा sm501_devdata *sm,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sm501_device *smdev = to_sm_device(pdev);
	पूर्णांक ptr;
	पूर्णांक ret;

	क्रम (ptr = 0; ptr < pdev->num_resources; ptr++) अणु
		prपूर्णांकk(KERN_DEBUG "%s[%d] %pR\n",
		       pdev->name, ptr, &pdev->resource[ptr]);
	पूर्ण

	ret = platक्रमm_device_रेजिस्टर(pdev);

	अगर (ret >= 0) अणु
		dev_dbg(sm->dev, "registered %s\n", pdev->name);
		list_add_tail(&smdev->list, &sm->devices);
	पूर्ण अन्यथा
		dev_err(sm->dev, "error registering %s (%d)\n",
			pdev->name, ret);

	वापस ret;
पूर्ण

/* sm501_create_subio
 *
 * Fill in an IO resource क्रम a sub device
*/

अटल व्योम sm501_create_subio(काष्ठा sm501_devdata *sm,
			       काष्ठा resource *res,
			       resource_माप_प्रकार offs,
			       resource_माप_प्रकार size)
अणु
	res->flags = IORESOURCE_MEM;
	res->parent = sm->io_res;
	res->start = sm->io_res->start + offs;
	res->end = res->start + size - 1;
पूर्ण

/* sm501_create_mem
 *
 * Fill in an MEM resource क्रम a sub device
*/

अटल व्योम sm501_create_mem(काष्ठा sm501_devdata *sm,
			     काष्ठा resource *res,
			     resource_माप_प्रकार *offs,
			     resource_माप_प्रकार size)
अणु
	*offs -= size;		/* adjust memory size */

	res->flags = IORESOURCE_MEM;
	res->parent = sm->mem_res;
	res->start = sm->mem_res->start + *offs;
	res->end = res->start + size - 1;
पूर्ण

/* sm501_create_irq
 *
 * Fill in an IRQ resource क्रम a sub device
*/

अटल व्योम sm501_create_irq(काष्ठा sm501_devdata *sm,
			     काष्ठा resource *res)
अणु
	res->flags = IORESOURCE_IRQ;
	res->parent = शून्य;
	res->start = res->end = sm->irq;
पूर्ण

अटल पूर्णांक sm501_रेजिस्टर_usbhost(काष्ठा sm501_devdata *sm,
				  resource_माप_प्रकार *mem_avail)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = sm501_create_subdev(sm, "sm501-usb", 3, 0);
	अगर (!pdev)
		वापस -ENOMEM;

	sm501_create_subio(sm, &pdev->resource[0], 0x40000, 0x20000);
	sm501_create_mem(sm, &pdev->resource[1], mem_avail, 256*1024);
	sm501_create_irq(sm, &pdev->resource[2]);

	वापस sm501_रेजिस्टर_device(sm, pdev);
पूर्ण

अटल व्योम sm501_setup_uart_data(काष्ठा sm501_devdata *sm,
				  काष्ठा plat_serial8250_port *uart_data,
				  अचिन्हित पूर्णांक offset)
अणु
	uart_data->membase = sm->regs + offset;
	uart_data->mapbase = sm->io_res->start + offset;
	uart_data->iotype = UPIO_MEM;
	uart_data->irq = sm->irq;
	uart_data->flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_SHARE_IRQ;
	uart_data->regshअगरt = 2;
	uart_data->uartclk = (9600 * 16);
पूर्ण

अटल पूर्णांक sm501_रेजिस्टर_uart(काष्ठा sm501_devdata *sm, पूर्णांक devices)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा plat_serial8250_port *uart_data;

	pdev = sm501_create_subdev(sm, "serial8250", 0,
				   माप(काष्ठा plat_serial8250_port) * 3);
	अगर (!pdev)
		वापस -ENOMEM;

	uart_data = dev_get_platdata(&pdev->dev);

	अगर (devices & SM501_USE_UART0) अणु
		sm501_setup_uart_data(sm, uart_data++, 0x30000);
		sm501_unit_घातer(sm->dev, SM501_GATE_UART0, 1);
		sm501_modअगरy_reg(sm->dev, SM501_IRQ_MASK, 1 << 12, 0);
		sm501_modअगरy_reg(sm->dev, SM501_GPIO63_32_CONTROL, 0x01e0, 0);
	पूर्ण
	अगर (devices & SM501_USE_UART1) अणु
		sm501_setup_uart_data(sm, uart_data++, 0x30020);
		sm501_unit_घातer(sm->dev, SM501_GATE_UART1, 1);
		sm501_modअगरy_reg(sm->dev, SM501_IRQ_MASK, 1 << 13, 0);
		sm501_modअगरy_reg(sm->dev, SM501_GPIO63_32_CONTROL, 0x1e00, 0);
	पूर्ण

	pdev->id = PLAT8250_DEV_SM501;

	वापस sm501_रेजिस्टर_device(sm, pdev);
पूर्ण

अटल पूर्णांक sm501_रेजिस्टर_display(काष्ठा sm501_devdata *sm,
				  resource_माप_प्रकार *mem_avail)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = sm501_create_subdev(sm, "sm501-fb", 4, 0);
	अगर (!pdev)
		वापस -ENOMEM;

	sm501_create_subio(sm, &pdev->resource[0], 0x80000, 0x10000);
	sm501_create_subio(sm, &pdev->resource[1], 0x100000, 0x50000);
	sm501_create_mem(sm, &pdev->resource[2], mem_avail, *mem_avail);
	sm501_create_irq(sm, &pdev->resource[3]);

	वापस sm501_रेजिस्टर_device(sm, pdev);
पूर्ण

#अगर_घोषित CONFIG_MFD_SM501_GPIO

अटल अंतरभूत काष्ठा sm501_devdata *sm501_gpio_to_dev(काष्ठा sm501_gpio *gpio)
अणु
	वापस container_of(gpio, काष्ठा sm501_devdata, gpio);
पूर्ण

अटल पूर्णांक sm501_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)

अणु
	काष्ठा sm501_gpio_chip *smgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ result;

	result = smc501_पढ़ोl(smgpio->regbase + SM501_GPIO_DATA_LOW);
	result >>= offset;

	वापस result & 1UL;
पूर्ण

अटल व्योम sm501_gpio_ensure_gpio(काष्ठा sm501_gpio_chip *smchip,
				   अचिन्हित दीर्घ bit)
अणु
	अचिन्हित दीर्घ ctrl;

	/* check and modअगरy अगर this pin is not set as gpio. */

	अगर (smc501_पढ़ोl(smchip->control) & bit) अणु
		dev_info(sm501_gpio_to_dev(smchip->ourgpio)->dev,
			 "changing mode of gpio, bit %08lx\n", bit);

		ctrl = smc501_पढ़ोl(smchip->control);
		ctrl &= ~bit;
		smc501_ग_लिखोl(ctrl, smchip->control);

		sm501_sync_regs(sm501_gpio_to_dev(smchip->ourgpio));
	पूर्ण
पूर्ण

अटल व्योम sm501_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)

अणु
	काष्ठा sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	काष्ठा sm501_gpio *smgpio = smchip->ourgpio;
	अचिन्हित दीर्घ bit = 1 << offset;
	व्योम __iomem *regs = smchip->regbase;
	अचिन्हित दीर्घ save;
	अचिन्हित दीर्घ val;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d)\n",
		__func__, chip, offset);

	spin_lock_irqsave(&smgpio->lock, save);

	val = smc501_पढ़ोl(regs + SM501_GPIO_DATA_LOW) & ~bit;
	अगर (value)
		val |= bit;
	smc501_ग_लिखोl(val, regs);

	sm501_sync_regs(sm501_gpio_to_dev(smgpio));
	sm501_gpio_ensure_gpio(smchip, bit);

	spin_unlock_irqrestore(&smgpio->lock, save);
पूर्ण

अटल पूर्णांक sm501_gpio_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	काष्ठा sm501_gpio *smgpio = smchip->ourgpio;
	व्योम __iomem *regs = smchip->regbase;
	अचिन्हित दीर्घ bit = 1 << offset;
	अचिन्हित दीर्घ save;
	अचिन्हित दीर्घ ddr;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d)\n",
		__func__, chip, offset);

	spin_lock_irqsave(&smgpio->lock, save);

	ddr = smc501_पढ़ोl(regs + SM501_GPIO_DDR_LOW);
	smc501_ग_लिखोl(ddr & ~bit, regs + SM501_GPIO_DDR_LOW);

	sm501_sync_regs(sm501_gpio_to_dev(smgpio));
	sm501_gpio_ensure_gpio(smchip, bit);

	spin_unlock_irqrestore(&smgpio->lock, save);

	वापस 0;
पूर्ण

अटल पूर्णांक sm501_gpio_output(काष्ठा gpio_chip *chip,
			     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा sm501_gpio_chip *smchip = gpiochip_get_data(chip);
	काष्ठा sm501_gpio *smgpio = smchip->ourgpio;
	अचिन्हित दीर्घ bit = 1 << offset;
	व्योम __iomem *regs = smchip->regbase;
	अचिन्हित दीर्घ save;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ ddr;

	dev_dbg(sm501_gpio_to_dev(smgpio)->dev, "%s(%p,%d,%d)\n",
		__func__, chip, offset, value);

	spin_lock_irqsave(&smgpio->lock, save);

	val = smc501_पढ़ोl(regs + SM501_GPIO_DATA_LOW);
	अगर (value)
		val |= bit;
	अन्यथा
		val &= ~bit;
	smc501_ग_लिखोl(val, regs);

	ddr = smc501_पढ़ोl(regs + SM501_GPIO_DDR_LOW);
	smc501_ग_लिखोl(ddr | bit, regs + SM501_GPIO_DDR_LOW);

	sm501_sync_regs(sm501_gpio_to_dev(smgpio));
	smc501_ग_लिखोl(val, regs + SM501_GPIO_DATA_LOW);

	sm501_sync_regs(sm501_gpio_to_dev(smgpio));
	spin_unlock_irqrestore(&smgpio->lock, save);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_chip gpio_chip_ढाँचा = अणु
	.ngpio			= 32,
	.direction_input	= sm501_gpio_input,
	.direction_output	= sm501_gpio_output,
	.set			= sm501_gpio_set,
	.get			= sm501_gpio_get,
पूर्ण;

अटल पूर्णांक sm501_gpio_रेजिस्टर_chip(काष्ठा sm501_devdata *sm,
					      काष्ठा sm501_gpio *gpio,
					      काष्ठा sm501_gpio_chip *chip)
अणु
	काष्ठा sm501_platdata *pdata = sm->platdata;
	काष्ठा gpio_chip *gchip = &chip->gpio;
	पूर्णांक base = pdata->gpio_base;

	chip->gpio = gpio_chip_ढाँचा;

	अगर (chip == &gpio->high) अणु
		अगर (base > 0)
			base += 32;
		chip->regbase = gpio->regs + SM501_GPIO_DATA_HIGH;
		chip->control = sm->regs + SM501_GPIO63_32_CONTROL;
		gchip->label  = "SM501-HIGH";
	पूर्ण अन्यथा अणु
		chip->regbase = gpio->regs + SM501_GPIO_DATA_LOW;
		chip->control = sm->regs + SM501_GPIO31_0_CONTROL;
		gchip->label  = "SM501-LOW";
	पूर्ण

	gchip->base   = base;
	chip->ourgpio = gpio;

	वापस gpiochip_add_data(gchip, chip);
पूर्ण

अटल पूर्णांक sm501_रेजिस्टर_gpio(काष्ठा sm501_devdata *sm)
अणु
	काष्ठा sm501_gpio *gpio = &sm->gpio;
	resource_माप_प्रकार iobase = sm->io_res->start + SM501_GPIO;
	पूर्णांक ret;

	dev_dbg(sm->dev, "registering gpio block %08llx\n",
		(अचिन्हित दीर्घ दीर्घ)iobase);

	spin_lock_init(&gpio->lock);

	gpio->regs_res = request_mem_region(iobase, 0x20, "sm501-gpio");
	अगर (!gpio->regs_res) अणु
		dev_err(sm->dev, "gpio: failed to request region\n");
		वापस -ENXIO;
	पूर्ण

	gpio->regs = ioremap(iobase, 0x20);
	अगर (!gpio->regs) अणु
		dev_err(sm->dev, "gpio: failed to remap registers\n");
		ret = -ENXIO;
		जाओ err_claimed;
	पूर्ण

	/* Register both our chips. */

	ret = sm501_gpio_रेजिस्टर_chip(sm, gpio, &gpio->low);
	अगर (ret) अणु
		dev_err(sm->dev, "failed to add low chip\n");
		जाओ err_mapped;
	पूर्ण

	ret = sm501_gpio_रेजिस्टर_chip(sm, gpio, &gpio->high);
	अगर (ret) अणु
		dev_err(sm->dev, "failed to add high chip\n");
		जाओ err_low_chip;
	पूर्ण

	gpio->रेजिस्टरed = 1;

	वापस 0;

 err_low_chip:
	gpiochip_हटाओ(&gpio->low.gpio);

 err_mapped:
	iounmap(gpio->regs);

 err_claimed:
	release_mem_region(iobase, 0x20);

	वापस ret;
पूर्ण

अटल व्योम sm501_gpio_हटाओ(काष्ठा sm501_devdata *sm)
अणु
	काष्ठा sm501_gpio *gpio = &sm->gpio;
	resource_माप_प्रकार iobase = sm->io_res->start + SM501_GPIO;

	अगर (!sm->gpio.रेजिस्टरed)
		वापस;

	gpiochip_हटाओ(&gpio->low.gpio);
	gpiochip_हटाओ(&gpio->high.gpio);

	iounmap(gpio->regs);
	release_mem_region(iobase, 0x20);
पूर्ण

अटल अंतरभूत पूर्णांक sm501_gpio_isरेजिस्टरed(काष्ठा sm501_devdata *sm)
अणु
	वापस sm->gpio.रेजिस्टरed;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक sm501_रेजिस्टर_gpio(काष्ठा sm501_devdata *sm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sm501_gpio_हटाओ(काष्ठा sm501_devdata *sm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sm501_gpio_isरेजिस्टरed(काष्ठा sm501_devdata *sm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sm501_रेजिस्टर_gpio_i2c_instance(काष्ठा sm501_devdata *sm,
					    काष्ठा sm501_platdata_gpio_i2c *iic)
अणु
	काष्ठा i2c_gpio_platक्रमm_data *icd;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gpiod_lookup_table *lookup;

	pdev = sm501_create_subdev(sm, "i2c-gpio", 0,
				   माप(काष्ठा i2c_gpio_platक्रमm_data));
	अगर (!pdev)
		वापस -ENOMEM;

	/* Create a gpiod lookup using gpiochip-local offsets */
	lookup = devm_kzalloc(&pdev->dev, काष्ठा_size(lookup, table, 3),
			      GFP_KERNEL);
	अगर (!lookup)
		वापस -ENOMEM;

	lookup->dev_id = "i2c-gpio";
	lookup->table[0] = (काष्ठा gpiod_lookup)
		GPIO_LOOKUP_IDX(iic->pin_sda < 32 ? "SM501-LOW" : "SM501-HIGH",
				iic->pin_sda % 32, शून्य, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN);
	lookup->table[1] = (काष्ठा gpiod_lookup)
		GPIO_LOOKUP_IDX(iic->pin_scl < 32 ? "SM501-LOW" : "SM501-HIGH",
				iic->pin_scl % 32, शून्य, 1,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN);
	gpiod_add_lookup_table(lookup);

	icd = dev_get_platdata(&pdev->dev);
	icd->समयout = iic->समयout;
	icd->udelay = iic->udelay;

	/* note, we can't use either of the pin numbers, as the i2c-gpio
	 * driver uses the platक्रमm.id field to generate the bus number
	 * to रेजिस्टर with the i2c core; The i2c core करोesn't have enough
	 * entries to deal with anything we currently use.
	*/

	pdev->id = iic->bus_num;

	dev_info(sm->dev, "registering i2c-%d: sda=%d, scl=%d\n",
		 iic->bus_num,
		 iic->pin_sda, iic->pin_scl);

	वापस sm501_रेजिस्टर_device(sm, pdev);
पूर्ण

अटल पूर्णांक sm501_रेजिस्टर_gpio_i2c(काष्ठा sm501_devdata *sm,
				   काष्ठा sm501_platdata *pdata)
अणु
	काष्ठा sm501_platdata_gpio_i2c *iic = pdata->gpio_i2c;
	पूर्णांक index;
	पूर्णांक ret;

	क्रम (index = 0; index < pdata->gpio_i2c_nr; index++, iic++) अणु
		ret = sm501_रेजिस्टर_gpio_i2c_instance(sm, iic);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* sm501_dbg_regs
 *
 * Debug attribute to attach to parent device to show core रेजिस्टरs
*/

अटल sमाप_प्रकार sm501_dbg_regs(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buff)
अणु
	काष्ठा sm501_devdata *sm = dev_get_drvdata(dev)	;
	अचिन्हित पूर्णांक reg;
	अक्षर *ptr = buff;
	पूर्णांक ret;

	क्रम (reg = 0x00; reg < 0x70; reg += 4) अणु
		ret = प्र_लिखो(ptr, "%08x = %08x\n",
			      reg, smc501_पढ़ोl(sm->regs + reg));
		ptr += ret;
	पूर्ण

	वापस ptr - buff;
पूर्ण


अटल DEVICE_ATTR(dbg_regs, 0444, sm501_dbg_regs, शून्य);

/* sm501_init_reg
 *
 * Helper function क्रम the init code to setup a रेजिस्टर
 *
 * clear the bits which are set in r->mask, and then set
 * the bits set in r->set.
*/

अटल अंतरभूत व्योम sm501_init_reg(काष्ठा sm501_devdata *sm,
				  अचिन्हित दीर्घ reg,
				  काष्ठा sm501_reg_init *r)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = smc501_पढ़ोl(sm->regs + reg);
	पंचांगp &= ~r->mask;
	पंचांगp |= r->set;
	smc501_ग_लिखोl(पंचांगp, sm->regs + reg);
पूर्ण

/* sm501_init_regs
 *
 * Setup core रेजिस्टर values
*/

अटल व्योम sm501_init_regs(काष्ठा sm501_devdata *sm,
			    काष्ठा sm501_initdata *init)
अणु
	sm501_misc_control(sm->dev,
			   init->misc_control.set,
			   init->misc_control.mask);

	sm501_init_reg(sm, SM501_MISC_TIMING, &init->misc_timing);
	sm501_init_reg(sm, SM501_GPIO31_0_CONTROL, &init->gpio_low);
	sm501_init_reg(sm, SM501_GPIO63_32_CONTROL, &init->gpio_high);

	अगर (init->m1xclk) अणु
		dev_info(sm->dev, "setting M1XCLK to %ld\n", init->m1xclk);
		sm501_set_घड़ी(sm->dev, SM501_CLOCK_M1XCLK, init->m1xclk);
	पूर्ण

	अगर (init->mclk) अणु
		dev_info(sm->dev, "setting MCLK to %ld\n", init->mclk);
		sm501_set_घड़ी(sm->dev, SM501_CLOCK_MCLK, init->mclk);
	पूर्ण

पूर्ण

/* Check the PLL sources क्रम the M1CLK and M1XCLK
 *
 * If the M1CLK and M1XCLKs are not sourced from the same PLL, then
 * there is a risk (see errata AB-5) that the SM501 will cease proper
 * function. If this happens, then it is likely the SM501 will
 * hang the प्रणाली.
*/

अटल पूर्णांक sm501_check_घड़ीs(काष्ठा sm501_devdata *sm)
अणु
	अचिन्हित दीर्घ pwrmode = smc501_पढ़ोl(sm->regs + SM501_CURRENT_CLOCK);
	अचिन्हित दीर्घ msrc = (pwrmode & SM501_POWERMODE_M_SRC);
	अचिन्हित दीर्घ m1src = (pwrmode & SM501_POWERMODE_M1_SRC);

	वापस ((msrc == 0 && m1src != 0) || (msrc != 0 && m1src == 0));
पूर्ण

अटल अचिन्हित पूर्णांक sm501_mem_local[] = अणु
	[0]	= 4*1024*1024,
	[1]	= 8*1024*1024,
	[2]	= 16*1024*1024,
	[3]	= 32*1024*1024,
	[4]	= 64*1024*1024,
	[5]	= 2*1024*1024,
पूर्ण;

/* sm501_init_dev
 *
 * Common init code क्रम an SM501
*/

अटल पूर्णांक sm501_init_dev(काष्ठा sm501_devdata *sm)
अणु
	काष्ठा sm501_initdata *idata;
	काष्ठा sm501_platdata *pdata;
	resource_माप_प्रकार mem_avail;
	अचिन्हित दीर्घ dramctrl;
	अचिन्हित दीर्घ devid;
	पूर्णांक ret;

	mutex_init(&sm->घड़ी_lock);
	spin_lock_init(&sm->reg_lock);

	INIT_LIST_HEAD(&sm->devices);

	devid = smc501_पढ़ोl(sm->regs + SM501_DEVICEID);

	अगर ((devid & SM501_DEVICEID_IDMASK) != SM501_DEVICEID_SM501) अणु
		dev_err(sm->dev, "incorrect device id %08lx\n", devid);
		वापस -EINVAL;
	पूर्ण

	/* disable irqs */
	smc501_ग_लिखोl(0, sm->regs + SM501_IRQ_MASK);

	dramctrl = smc501_पढ़ोl(sm->regs + SM501_DRAM_CONTROL);
	mem_avail = sm501_mem_local[(dramctrl >> 13) & 0x7];

	dev_info(sm->dev, "SM501 At %p: Version %08lx, %ld Mb, IRQ %d\n",
		 sm->regs, devid, (अचिन्हित दीर्घ)mem_avail >> 20, sm->irq);

	sm->rev = devid & SM501_DEVICEID_REVMASK;

	sm501_dump_gate(sm);

	ret = device_create_file(sm->dev, &dev_attr_dbg_regs);
	अगर (ret)
		dev_err(sm->dev, "failed to create debug regs file\n");

	sm501_dump_clk(sm);

	/* check to see अगर we have some device initialisation */

	pdata = sm->platdata;
	idata = pdata ? pdata->init : शून्य;

	अगर (idata) अणु
		sm501_init_regs(sm, idata);

		अगर (idata->devices & SM501_USE_USB_HOST)
			sm501_रेजिस्टर_usbhost(sm, &mem_avail);
		अगर (idata->devices & (SM501_USE_UART0 | SM501_USE_UART1))
			sm501_रेजिस्टर_uart(sm, idata->devices);
		अगर (idata->devices & SM501_USE_GPIO)
			sm501_रेजिस्टर_gpio(sm);
	पूर्ण

	अगर (pdata && pdata->gpio_i2c && pdata->gpio_i2c_nr > 0) अणु
		अगर (!sm501_gpio_isरेजिस्टरed(sm))
			dev_err(sm->dev, "no gpio available for i2c gpio.\n");
		अन्यथा
			sm501_रेजिस्टर_gpio_i2c(sm, pdata);
	पूर्ण

	ret = sm501_check_घड़ीs(sm);
	अगर (ret) अणु
		dev_err(sm->dev, "M1X and M clocks sourced from different "
					"PLLs\n");
		वापस -EINVAL;
	पूर्ण

	/* always create a framebuffer */
	sm501_रेजिस्टर_display(sm, &mem_avail);

	वापस 0;
पूर्ण

अटल पूर्णांक sm501_plat_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sm501_devdata *sm;
	पूर्णांक ret;

	sm = kzalloc(माप(*sm), GFP_KERNEL);
	अगर (!sm) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	sm->dev = &dev->dev;
	sm->pdev_id = dev->id;
	sm->platdata = dev_get_platdata(&dev->dev);

	ret = platक्रमm_get_irq(dev, 0);
	अगर (ret < 0)
		जाओ err_res;
	sm->irq = ret;

	sm->io_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	sm->mem_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!sm->io_res || !sm->mem_res) अणु
		dev_err(&dev->dev, "failed to get IO resource\n");
		ret = -ENOENT;
		जाओ err_res;
	पूर्ण

	sm->regs_claim = request_mem_region(sm->io_res->start,
					    0x100, "sm501");
	अगर (!sm->regs_claim) अणु
		dev_err(&dev->dev, "cannot claim registers\n");
		ret = -EBUSY;
		जाओ err_res;
	पूर्ण

	platक्रमm_set_drvdata(dev, sm);

	sm->regs = ioremap(sm->io_res->start, resource_size(sm->io_res));
	अगर (!sm->regs) अणु
		dev_err(&dev->dev, "cannot remap registers\n");
		ret = -EIO;
		जाओ err_claim;
	पूर्ण

	ret = sm501_init_dev(sm);
	अगर (ret)
		जाओ err_unmap;

	वापस 0;

 err_unmap:
	iounmap(sm->regs);
 err_claim:
	release_mem_region(sm->io_res->start, 0x100);
 err_res:
	kमुक्त(sm);
 err1:
	वापस ret;

पूर्ण

#अगर_घोषित CONFIG_PM

/* घातer management support */

अटल व्योम sm501_set_घातer(काष्ठा sm501_devdata *sm, पूर्णांक on)
अणु
	काष्ठा sm501_platdata *pd = sm->platdata;

	अगर (!pd)
		वापस;

	अगर (pd->get_घातer) अणु
		अगर (pd->get_घातer(sm->dev) == on) अणु
			dev_dbg(sm->dev, "is already %d\n", on);
			वापस;
		पूर्ण
	पूर्ण

	अगर (pd->set_घातer) अणु
		dev_dbg(sm->dev, "setting power to %d\n", on);

		pd->set_घातer(sm->dev, on);
		sm501_mdelay(sm, 10);
	पूर्ण
पूर्ण

अटल पूर्णांक sm501_plat_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा sm501_devdata *sm = platक्रमm_get_drvdata(pdev);

	sm->in_suspend = 1;
	sm->pm_misc = smc501_पढ़ोl(sm->regs + SM501_MISC_CONTROL);

	sm501_dump_regs(sm);

	अगर (sm->platdata) अणु
		अगर (sm->platdata->flags & SM501_FLAG_SUSPEND_OFF)
			sm501_set_घातer(sm, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sm501_plat_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sm501_devdata *sm = platक्रमm_get_drvdata(pdev);

	sm501_set_घातer(sm, 1);

	sm501_dump_regs(sm);
	sm501_dump_gate(sm);
	sm501_dump_clk(sm);

	/* check to see अगर we are in the same state as when suspended */

	अगर (smc501_पढ़ोl(sm->regs + SM501_MISC_CONTROL) != sm->pm_misc) अणु
		dev_info(sm->dev, "SM501_MISC_CONTROL changed over sleep\n");
		smc501_ग_लिखोl(sm->pm_misc, sm->regs + SM501_MISC_CONTROL);

		/* our suspend causes the controller state to change,
		 * either by something attempting setup, घातer loss,
		 * or an बाह्यal reset event on घातer change */

		अगर (sm->platdata && sm->platdata->init) अणु
			sm501_init_regs(sm, sm->platdata->init);
		पूर्ण
	पूर्ण

	/* dump our state from resume */

	sm501_dump_regs(sm);
	sm501_dump_clk(sm);

	sm->in_suspend = 0;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा sm501_plat_suspend शून्य
#घोषणा sm501_plat_resume शून्य
#पूर्ण_अगर

/* Initialisation data क्रम PCI devices */

अटल काष्ठा sm501_initdata sm501_pci_initdata = अणु
	.gpio_high	= अणु
		.set	= 0x3F000000,		/* 24bit panel */
		.mask	= 0x0,
	पूर्ण,
	.misc_timing	= अणु
		.set	= 0x010100,		/* SDRAM timing */
		.mask	= 0x1F1F00,
	पूर्ण,
	.misc_control	= अणु
		.set	= SM501_MISC_PNL_24BIT,
		.mask	= 0,
	पूर्ण,

	.devices	= SM501_USE_ALL,

	/* Errata AB-3 says that 72MHz is the fastest available
	 * क्रम 33MHZ PCI with proper bus-mastering operation */

	.mclk		= 72 * MHZ,
	.m1xclk		= 144 * MHZ,
पूर्ण;

अटल काष्ठा sm501_platdata_fbsub sm501_pdata_fbsub = अणु
	.flags		= (SM501FB_FLAG_USE_INIT_MODE |
			   SM501FB_FLAG_USE_HWCURSOR |
			   SM501FB_FLAG_USE_HWACCEL |
			   SM501FB_FLAG_DISABLE_AT_EXIT),
पूर्ण;

अटल काष्ठा sm501_platdata_fb sm501_fb_pdata = अणु
	.fb_route	= SM501_FB_OWN,
	.fb_crt		= &sm501_pdata_fbsub,
	.fb_pnl		= &sm501_pdata_fbsub,
पूर्ण;

अटल काष्ठा sm501_platdata sm501_pci_platdata = अणु
	.init		= &sm501_pci_initdata,
	.fb		= &sm501_fb_pdata,
	.gpio_base	= -1,
पूर्ण;

अटल पूर्णांक sm501_pci_probe(काष्ठा pci_dev *dev,
				     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sm501_devdata *sm;
	पूर्णांक err;

	sm = kzalloc(माप(*sm), GFP_KERNEL);
	अगर (!sm) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	/* set a शेष set of platक्रमm data */
	dev->dev.platक्रमm_data = sm->platdata = &sm501_pci_platdata;

	/* set a hopefully unique id क्रम our child platक्रमm devices */
	sm->pdev_id = 32 + dev->devfn;

	pci_set_drvdata(dev, sm);

	err = pci_enable_device(dev);
	अगर (err) अणु
		dev_err(&dev->dev, "cannot enable device\n");
		जाओ err2;
	पूर्ण

	sm->dev = &dev->dev;
	sm->irq = dev->irq;

#अगर_घोषित __BIG_ENDIAN
	/* अगर the प्रणाली is big-endian, we most probably have a
	 * translation in the IO layer making the PCI bus little endian
	 * so make the framebuffer swapped pixels */

	sm501_fb_pdata.flags |= SM501_FBPD_SWAP_FB_ENDIAN;
#पूर्ण_अगर

	/* check our resources */

	अगर (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&dev->dev, "region #0 is not memory?\n");
		err = -EINVAL;
		जाओ err3;
	पूर्ण

	अगर (!(pci_resource_flags(dev, 1) & IORESOURCE_MEM)) अणु
		dev_err(&dev->dev, "region #1 is not memory?\n");
		err = -EINVAL;
		जाओ err3;
	पूर्ण

	/* make our resources पढ़ोy क्रम sharing */

	sm->io_res = &dev->resource[1];
	sm->mem_res = &dev->resource[0];

	sm->regs_claim = request_mem_region(sm->io_res->start,
					    0x100, "sm501");
	अगर (!sm->regs_claim) अणु
		dev_err(&dev->dev, "cannot claim registers\n");
		err= -EBUSY;
		जाओ err3;
	पूर्ण

	sm->regs = pci_ioremap_bar(dev, 1);
	अगर (!sm->regs) अणु
		dev_err(&dev->dev, "cannot remap registers\n");
		err = -EIO;
		जाओ err4;
	पूर्ण

	sm501_init_dev(sm);
	वापस 0;

 err4:
	release_mem_region(sm->io_res->start, 0x100);
 err3:
	pci_disable_device(dev);
 err2:
	kमुक्त(sm);
 err1:
	वापस err;
पूर्ण

अटल व्योम sm501_हटाओ_sub(काष्ठा sm501_devdata *sm,
			     काष्ठा sm501_device *smdev)
अणु
	list_del(&smdev->list);
	platक्रमm_device_unरेजिस्टर(&smdev->pdev);
पूर्ण

अटल व्योम sm501_dev_हटाओ(काष्ठा sm501_devdata *sm)
अणु
	काष्ठा sm501_device *smdev, *पंचांगp;

	list_क्रम_each_entry_safe(smdev, पंचांगp, &sm->devices, list)
		sm501_हटाओ_sub(sm, smdev);

	device_हटाओ_file(sm->dev, &dev_attr_dbg_regs);

	sm501_gpio_हटाओ(sm);
पूर्ण

अटल व्योम sm501_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा sm501_devdata *sm = pci_get_drvdata(dev);

	sm501_dev_हटाओ(sm);
	iounmap(sm->regs);

	release_mem_region(sm->io_res->start, 0x100);

	pci_disable_device(dev);
पूर्ण

अटल पूर्णांक sm501_plat_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sm501_devdata *sm = platक्रमm_get_drvdata(dev);

	sm501_dev_हटाओ(sm);
	iounmap(sm->regs);

	release_mem_region(sm->io_res->start, 0x100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sm501_pci_tbl[] = अणु
	अणु 0x126f, 0x0501, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, sm501_pci_tbl);

अटल काष्ठा pci_driver sm501_pci_driver = अणु
	.name		= "sm501",
	.id_table	= sm501_pci_tbl,
	.probe		= sm501_pci_probe,
	.हटाओ		= sm501_pci_हटाओ,
पूर्ण;

MODULE_ALIAS("platform:sm501");

अटल स्थिर काष्ठा of_device_id of_sm501_match_tbl[] = अणु
	अणु .compatible = "smi,sm501", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_sm501_match_tbl);

अटल काष्ठा platक्रमm_driver sm501_plat_driver = अणु
	.driver		= अणु
		.name	= "sm501",
		.of_match_table = of_sm501_match_tbl,
	पूर्ण,
	.probe		= sm501_plat_probe,
	.हटाओ		= sm501_plat_हटाओ,
	.suspend	= sm501_plat_suspend,
	.resume		= sm501_plat_resume,
पूर्ण;

अटल पूर्णांक __init sm501_base_init(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&sm501_plat_driver);
	वापस pci_रेजिस्टर_driver(&sm501_pci_driver);
पूर्ण

अटल व्योम __निकास sm501_base_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sm501_plat_driver);
	pci_unरेजिस्टर_driver(&sm501_pci_driver);
पूर्ण

module_init(sm501_base_init);
module_निकास(sm501_base_निकास);

MODULE_DESCRIPTION("SM501 Core Driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>, Vincent Sanders");
MODULE_LICENSE("GPL v2");
