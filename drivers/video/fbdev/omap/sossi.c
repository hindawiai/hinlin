<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP1 Special OptimiSed Screen Interface support
 *
 * Copyright (C) 2004-2005 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/omap-dma.h>

#समावेश "omapfb.h"
#समावेश "lcdc.h"

#घोषणा MODULE_NAME		"omapfb-sossi"

#घोषणा OMAP_SOSSI_BASE         0xfffbac00
#घोषणा SOSSI_ID_REG		0x00
#घोषणा SOSSI_INIT1_REG		0x04
#घोषणा SOSSI_INIT2_REG		0x08
#घोषणा SOSSI_INIT3_REG		0x0c
#घोषणा SOSSI_FIFO_REG		0x10
#घोषणा SOSSI_REOTABLE_REG	0x14
#घोषणा SOSSI_TEARING_REG	0x18
#घोषणा SOSSI_INIT1B_REG	0x1c
#घोषणा SOSSI_FIFOB_REG		0x20

#घोषणा DMA_GSCR          0xfffedc04
#घोषणा DMA_LCD_CCR       0xfffee3c2
#घोषणा DMA_LCD_CTRL      0xfffee3c4
#घोषणा DMA_LCD_LCH_CTRL  0xfffee3ea

#घोषणा CONF_SOSSI_RESET_R      (1 << 23)

#घोषणा RD_ACCESS		0
#घोषणा WR_ACCESS		1

#घोषणा SOSSI_MAX_XMIT_BYTES	(512 * 1024)

अटल काष्ठा अणु
	व्योम __iomem	*base;
	काष्ठा clk	*fck;
	अचिन्हित दीर्घ	fck_hz;
	spinlock_t	lock;
	पूर्णांक		bus_pick_count;
	पूर्णांक		bus_pick_width;
	पूर्णांक		tearsync_mode;
	पूर्णांक		tearsync_line;
	व्योम		(*lcdc_callback)(व्योम *data);
	व्योम		*lcdc_callback_data;
	पूर्णांक		vsync_dma_pending;
	/* timing क्रम पढ़ो and ग_लिखो access */
	पूर्णांक		clk_भाग;
	u8		clk_tw0[2];
	u8		clk_tw1[2];
	/*
	 * अगर last_access is the same as current we करोn't have to change
	 * the timings
	 */
	पूर्णांक		last_access;

	काष्ठा omapfb_device	*fbdev;
पूर्ण sossi;

अटल अंतरभूत u32 sossi_पढ़ो_reg(पूर्णांक reg)
अणु
	वापस पढ़ोl(sossi.base + reg);
पूर्ण

अटल अंतरभूत u16 sossi_पढ़ो_reg16(पूर्णांक reg)
अणु
	वापस पढ़ोw(sossi.base + reg);
पूर्ण

अटल अंतरभूत u8 sossi_पढ़ो_reg8(पूर्णांक reg)
अणु
	वापस पढ़ोb(sossi.base + reg);
पूर्ण

अटल अंतरभूत व्योम sossi_ग_लिखो_reg(पूर्णांक reg, u32 value)
अणु
	ग_लिखोl(value, sossi.base + reg);
पूर्ण

अटल अंतरभूत व्योम sossi_ग_लिखो_reg16(पूर्णांक reg, u16 value)
अणु
	ग_लिखोw(value, sossi.base + reg);
पूर्ण

अटल अंतरभूत व्योम sossi_ग_लिखो_reg8(पूर्णांक reg, u8 value)
अणु
	ग_लिखोb(value, sossi.base + reg);
पूर्ण

अटल व्योम sossi_set_bits(पूर्णांक reg, u32 bits)
अणु
	sossi_ग_लिखो_reg(reg, sossi_पढ़ो_reg(reg) | bits);
पूर्ण

अटल व्योम sossi_clear_bits(पूर्णांक reg, u32 bits)
अणु
	sossi_ग_लिखो_reg(reg, sossi_पढ़ो_reg(reg) & ~bits);
पूर्ण

#घोषणा HZ_TO_PS(x)	(1000000000 / (x / 1000))

अटल u32 ps_to_sossi_ticks(u32 ps, पूर्णांक भाग)
अणु
	u32 clk_period = HZ_TO_PS(sossi.fck_hz) * भाग;
	वापस (clk_period + ps - 1) / clk_period;
पूर्ण

अटल पूर्णांक calc_rd_timings(काष्ठा extअगर_timings *t)
अणु
	u32 tw0, tw1;
	पूर्णांक reon, reoff, recyc, actim;
	पूर्णांक भाग = t->clk_भाग;

	/*
	 * Make sure that after conversion it still holds that:
	 * reoff > reon, recyc >= reoff, actim > reon
	 */
	reon = ps_to_sossi_ticks(t->re_on_समय, भाग);
	/* reon will be exactly one sossi tick */
	अगर (reon > 1)
		वापस -1;

	reoff = ps_to_sossi_ticks(t->re_off_समय, भाग);

	अगर (reoff <= reon)
		reoff = reon + 1;

	tw0 = reoff - reon;
	अगर (tw0 > 0x10)
		वापस -1;

	recyc = ps_to_sossi_ticks(t->re_cycle_समय, भाग);
	अगर (recyc <= reoff)
		recyc = reoff + 1;

	tw1 = recyc - tw0;
	/* values less then 3 result in the SOSSI block resetting itself */
	अगर (tw1 < 3)
		tw1 = 3;
	अगर (tw1 > 0x40)
		वापस -1;

	actim = ps_to_sossi_ticks(t->access_समय, भाग);
	अगर (actim < reoff)
		actim++;
	/*
	 * access समय (data hold समय) will be exactly one sossi
	 * tick
	 */
	अगर (actim - reoff > 1)
		वापस -1;

	t->tim[0] = tw0 - 1;
	t->tim[1] = tw1 - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक calc_wr_timings(काष्ठा extअगर_timings *t)
अणु
	u32 tw0, tw1;
	पूर्णांक weon, weoff, wecyc;
	पूर्णांक भाग = t->clk_भाग;

	/*
	 * Make sure that after conversion it still holds that:
	 * weoff > weon, wecyc >= weoff
	 */
	weon = ps_to_sossi_ticks(t->we_on_समय, भाग);
	/* weon will be exactly one sossi tick */
	अगर (weon > 1)
		वापस -1;

	weoff = ps_to_sossi_ticks(t->we_off_समय, भाग);
	अगर (weoff <= weon)
		weoff = weon + 1;
	tw0 = weoff - weon;
	अगर (tw0 > 0x10)
		वापस -1;

	wecyc = ps_to_sossi_ticks(t->we_cycle_समय, भाग);
	अगर (wecyc <= weoff)
		wecyc = weoff + 1;

	tw1 = wecyc - tw0;
	/* values less then 3 result in the SOSSI block resetting itself */
	अगर (tw1 < 3)
		tw1 = 3;
	अगर (tw1 > 0x40)
		वापस -1;

	t->tim[2] = tw0 - 1;
	t->tim[3] = tw1 - 1;

	वापस 0;
पूर्ण

अटल व्योम _set_timing(पूर्णांक भाग, पूर्णांक tw0, पूर्णांक tw1)
अणु
	u32 l;

#अगर_घोषित VERBOSE
	dev_dbg(sossi.fbdev->dev, "Using TW0 = %d, TW1 = %d, div = %d\n",
		 tw0 + 1, tw1 + 1, भाग);
#पूर्ण_अगर

	clk_set_rate(sossi.fck, sossi.fck_hz / भाग);
	clk_enable(sossi.fck);
	l = sossi_पढ़ो_reg(SOSSI_INIT1_REG);
	l &= ~((0x0f << 20) | (0x3f << 24));
	l |= (tw0 << 20) | (tw1 << 24);
	sossi_ग_लिखो_reg(SOSSI_INIT1_REG, l);
	clk_disable(sossi.fck);
पूर्ण

अटल व्योम _set_bits_per_cycle(पूर्णांक bus_pick_count, पूर्णांक bus_pick_width)
अणु
	u32 l;

	l = sossi_पढ़ो_reg(SOSSI_INIT3_REG);
	l &= ~0x3ff;
	l |= ((bus_pick_count - 1) << 5) | ((bus_pick_width - 1) & 0x1f);
	sossi_ग_लिखो_reg(SOSSI_INIT3_REG, l);
पूर्ण

अटल व्योम _set_tearsync_mode(पूर्णांक mode, अचिन्हित line)
अणु
	u32 l;

	l = sossi_पढ़ो_reg(SOSSI_TEARING_REG);
	l &= ~(((1 << 11) - 1) << 15);
	l |= line << 15;
	l &= ~(0x3 << 26);
	l |= mode << 26;
	sossi_ग_लिखो_reg(SOSSI_TEARING_REG, l);
	अगर (mode)
		sossi_set_bits(SOSSI_INIT2_REG, 1 << 6);	/* TE logic */
	अन्यथा
		sossi_clear_bits(SOSSI_INIT2_REG, 1 << 6);
पूर्ण

अटल अंतरभूत व्योम set_timing(पूर्णांक access)
अणु
	अगर (access != sossi.last_access) अणु
		sossi.last_access = access;
		_set_timing(sossi.clk_भाग,
			    sossi.clk_tw0[access], sossi.clk_tw1[access]);
	पूर्ण
पूर्ण

अटल व्योम sossi_start_transfer(व्योम)
अणु
	/* WE */
	sossi_clear_bits(SOSSI_INIT2_REG, 1 << 4);
	/* CS active low */
	sossi_clear_bits(SOSSI_INIT1_REG, 1 << 30);
पूर्ण

अटल व्योम sossi_stop_transfer(व्योम)
अणु
	/* WE */
	sossi_set_bits(SOSSI_INIT2_REG, 1 << 4);
	/* CS active low */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 30);
पूर्ण

अटल व्योम रुको_end_of_ग_लिखो(व्योम)
अणु
	/* Beक्रमe पढ़ोing we must check अगर some writings are going on */
	जबतक (!(sossi_पढ़ो_reg(SOSSI_INIT2_REG) & (1 << 3)));
पूर्ण

अटल व्योम send_data(स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	जबतक (len >= 4) अणु
		sossi_ग_लिखो_reg(SOSSI_FIFO_REG, *(स्थिर u32 *) data);
		len -= 4;
		data += 4;
	पूर्ण
	जबतक (len >= 2) अणु
		sossi_ग_लिखो_reg16(SOSSI_FIFO_REG, *(स्थिर u16 *) data);
		len -= 2;
		data += 2;
	पूर्ण
	जबतक (len) अणु
		sossi_ग_लिखो_reg8(SOSSI_FIFO_REG, *(स्थिर u8 *) data);
		len--;
		data++;
	पूर्ण
पूर्ण

अटल व्योम set_cycles(अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ nr_cycles = len / (sossi.bus_pick_width / 8);

	BUG_ON((nr_cycles - 1) & ~0x3ffff);

	sossi_clear_bits(SOSSI_INIT1_REG, 0x3ffff);
	sossi_set_bits(SOSSI_INIT1_REG, (nr_cycles - 1) & 0x3ffff);
पूर्ण

अटल पूर्णांक sossi_convert_timings(काष्ठा extअगर_timings *t)
अणु
	पूर्णांक r = 0;
	पूर्णांक भाग = t->clk_भाग;

	t->converted = 0;

	अगर (भाग <= 0 || भाग > 8)
		वापस -1;

	/* no CS on SOSSI, so ignore cson, csoff, cs_pulsewidth */
	अगर ((r = calc_rd_timings(t)) < 0)
		वापस r;

	अगर ((r = calc_wr_timings(t)) < 0)
		वापस r;

	t->tim[4] = भाग;

	t->converted = 1;

	वापस 0;
पूर्ण

अटल व्योम sossi_set_timings(स्थिर काष्ठा extअगर_timings *t)
अणु
	BUG_ON(!t->converted);

	sossi.clk_tw0[RD_ACCESS] = t->tim[0];
	sossi.clk_tw1[RD_ACCESS] = t->tim[1];

	sossi.clk_tw0[WR_ACCESS] = t->tim[2];
	sossi.clk_tw1[WR_ACCESS] = t->tim[3];

	sossi.clk_भाग = t->tim[4];
पूर्ण

अटल व्योम sossi_get_clk_info(u32 *clk_period, u32 *max_clk_भाग)
अणु
	*clk_period = HZ_TO_PS(sossi.fck_hz);
	*max_clk_भाग = 8;
पूर्ण

अटल व्योम sossi_set_bits_per_cycle(पूर्णांक bpc)
अणु
	पूर्णांक bus_pick_count, bus_pick_width;

	/*
	 * We set explicitly the the bus_pick_count as well, although
	 * with remapping/reordering disabled it will be calculated by HW
	 * as (32 / bus_pick_width).
	 */
	चयन (bpc) अणु
	हाल 8:
		bus_pick_count = 4;
		bus_pick_width = 8;
		अवरोध;
	हाल 16:
		bus_pick_count = 2;
		bus_pick_width = 16;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण
	sossi.bus_pick_width = bus_pick_width;
	sossi.bus_pick_count = bus_pick_count;
पूर्ण

अटल पूर्णांक sossi_setup_tearsync(अचिन्हित pin_cnt,
				अचिन्हित hs_pulse_समय, अचिन्हित vs_pulse_समय,
				पूर्णांक hs_pol_inv, पूर्णांक vs_pol_inv, पूर्णांक भाग)
अणु
	पूर्णांक hs, vs;
	u32 l;

	अगर (pin_cnt != 1 || भाग < 1 || भाग > 8)
		वापस -EINVAL;

	hs = ps_to_sossi_ticks(hs_pulse_समय, भाग);
	vs = ps_to_sossi_ticks(vs_pulse_समय, भाग);
	अगर (vs < 8 || vs <= hs || vs >= (1 << 12))
		वापस -गलत_तर्क;
	vs /= 8;
	vs--;
	अगर (hs > 8)
		hs = 8;
	अगर (hs)
		hs--;

	dev_dbg(sossi.fbdev->dev,
		"setup_tearsync: hs %d vs %d hs_inv %d vs_inv %d\n",
		hs, vs, hs_pol_inv, vs_pol_inv);

	clk_enable(sossi.fck);
	l = sossi_पढ़ो_reg(SOSSI_TEARING_REG);
	l &= ~((1 << 15) - 1);
	l |= vs << 3;
	l |= hs;
	अगर (hs_pol_inv)
		l |= 1 << 29;
	अन्यथा
		l &= ~(1 << 29);
	अगर (vs_pol_inv)
		l |= 1 << 28;
	अन्यथा
		l &= ~(1 << 28);
	sossi_ग_लिखो_reg(SOSSI_TEARING_REG, l);
	clk_disable(sossi.fck);

	वापस 0;
पूर्ण

अटल पूर्णांक sossi_enable_tearsync(पूर्णांक enable, अचिन्हित line)
अणु
	पूर्णांक mode;

	dev_dbg(sossi.fbdev->dev, "tearsync %d line %d\n", enable, line);
	अगर (line >= 1 << 11)
		वापस -EINVAL;
	अगर (enable) अणु
		अगर (line)
			mode = 2;		/* HS or VS */
		अन्यथा
			mode = 3;		/* VS only */
	पूर्ण अन्यथा
		mode = 0;
	sossi.tearsync_line = line;
	sossi.tearsync_mode = mode;

	वापस 0;
पूर्ण

अटल व्योम sossi_ग_लिखो_command(स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	clk_enable(sossi.fck);
	set_timing(WR_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_clear_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(len);
	sossi_start_transfer();
	send_data(data, len);
	sossi_stop_transfer();
	रुको_end_of_ग_लिखो();
	clk_disable(sossi.fck);
पूर्ण

अटल व्योम sossi_ग_लिखो_data(स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	clk_enable(sossi.fck);
	set_timing(WR_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(len);
	sossi_start_transfer();
	send_data(data, len);
	sossi_stop_transfer();
	रुको_end_of_ग_लिखो();
	clk_disable(sossi.fck);
पूर्ण

अटल व्योम sossi_transfer_area(पूर्णांक width, पूर्णांक height,
				व्योम (callback)(व्योम *data), व्योम *data)
अणु
	BUG_ON(callback == शून्य);

	sossi.lcdc_callback = callback;
	sossi.lcdc_callback_data = data;

	clk_enable(sossi.fck);
	set_timing(WR_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	_set_tearsync_mode(sossi.tearsync_mode, sossi.tearsync_line);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(width * height * sossi.bus_pick_width / 8);

	sossi_start_transfer();
	अगर (sossi.tearsync_mode) अणु
		/*
		 * Wait क्रम the sync संकेत and start the transfer only
		 * then. We can't seem to be able to use HW sync DMA क्रम
		 * this since LCD DMA shows huge latencies, as अगर it
		 * would ignore some of the DMA requests from SoSSI.
		 */
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&sossi.lock, flags);
		sossi.vsync_dma_pending++;
		spin_unlock_irqrestore(&sossi.lock, flags);
	पूर्ण अन्यथा
		/* Just start the transfer right away. */
		omap_enable_lcd_dma();
पूर्ण

अटल व्योम sossi_dma_callback(व्योम *data)
अणु
	omap_stop_lcd_dma();
	sossi_stop_transfer();
	clk_disable(sossi.fck);
	sossi.lcdc_callback(sossi.lcdc_callback_data);
पूर्ण

अटल व्योम sossi_पढ़ो_data(व्योम *data, अचिन्हित पूर्णांक len)
अणु
	clk_enable(sossi.fck);
	set_timing(RD_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(len);
	sossi_start_transfer();
	जबतक (len >= 4) अणु
		*(u32 *) data = sossi_पढ़ो_reg(SOSSI_FIFO_REG);
		len -= 4;
		data += 4;
	पूर्ण
	जबतक (len >= 2) अणु
		*(u16 *) data = sossi_पढ़ो_reg16(SOSSI_FIFO_REG);
		len -= 2;
		data += 2;
	पूर्ण
	जबतक (len) अणु
		*(u8 *) data = sossi_पढ़ो_reg8(SOSSI_FIFO_REG);
		len--;
		data++;
	पूर्ण
	sossi_stop_transfer();
	clk_disable(sossi.fck);
पूर्ण

अटल irqवापस_t sossi_match_irq(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sossi.lock, flags);
	अगर (sossi.vsync_dma_pending) अणु
		sossi.vsync_dma_pending--;
		omap_enable_lcd_dma();
	पूर्ण
	spin_unlock_irqrestore(&sossi.lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sossi_init(काष्ठा omapfb_device *fbdev)
अणु
	u32 l, k;
	काष्ठा clk *fck;
	काष्ठा clk *dpll1out_ck;
	पूर्णांक r;

	sossi.base = ioremap(OMAP_SOSSI_BASE, SZ_1K);
	अगर (!sossi.base) अणु
		dev_err(fbdev->dev, "can't ioremap SoSSI\n");
		वापस -ENOMEM;
	पूर्ण

	sossi.fbdev = fbdev;
	spin_lock_init(&sossi.lock);

	dpll1out_ck = clk_get(fbdev->dev, "ck_dpll1out");
	अगर (IS_ERR(dpll1out_ck)) अणु
		dev_err(fbdev->dev, "can't get DPLL1OUT clock\n");
		वापस PTR_ERR(dpll1out_ck);
	पूर्ण
	/*
	 * We need the parent घड़ी rate, which we might भागide further
	 * depending on the timing requirements of the controller. See
	 * _set_timings.
	 */
	sossi.fck_hz = clk_get_rate(dpll1out_ck);
	clk_put(dpll1out_ck);

	fck = clk_get(fbdev->dev, "ck_sossi");
	अगर (IS_ERR(fck)) अणु
		dev_err(fbdev->dev, "can't get SoSSI functional clock\n");
		वापस PTR_ERR(fck);
	पूर्ण
	sossi.fck = fck;

	/* Reset and enable the SoSSI module */
	l = omap_पढ़ोl(MOD_CONF_CTRL_1);
	l |= CONF_SOSSI_RESET_R;
	omap_ग_लिखोl(l, MOD_CONF_CTRL_1);
	l &= ~CONF_SOSSI_RESET_R;
	omap_ग_लिखोl(l, MOD_CONF_CTRL_1);

	clk_enable(sossi.fck);
	l = omap_पढ़ोl(ARM_IDLECT2);
	l &= ~(1 << 8);			/* DMACK_REQ */
	omap_ग_लिखोl(l, ARM_IDLECT2);

	l = sossi_पढ़ो_reg(SOSSI_INIT2_REG);
	/* Enable and reset the SoSSI block */
	l |= (1 << 0) | (1 << 1);
	sossi_ग_लिखो_reg(SOSSI_INIT2_REG, l);
	/* Take SoSSI out of reset */
	l &= ~(1 << 1);
	sossi_ग_लिखो_reg(SOSSI_INIT2_REG, l);

	sossi_ग_लिखो_reg(SOSSI_ID_REG, 0);
	l = sossi_पढ़ो_reg(SOSSI_ID_REG);
	k = sossi_पढ़ो_reg(SOSSI_ID_REG);

	अगर (l != 0x55555555 || k != 0xaaaaaaaa) अणु
		dev_err(fbdev->dev,
			"invalid SoSSI sync pattern: %08x, %08x\n", l, k);
		r = -ENODEV;
		जाओ err;
	पूर्ण

	अगर ((r = omap_lcdc_set_dma_callback(sossi_dma_callback, शून्य)) < 0) अणु
		dev_err(fbdev->dev, "can't get LCDC IRQ\n");
		r = -ENODEV;
		जाओ err;
	पूर्ण

	l = sossi_पढ़ो_reg(SOSSI_ID_REG); /* Component code */
	l = sossi_पढ़ो_reg(SOSSI_ID_REG);
	dev_info(fbdev->dev, "SoSSI version %d.%d initialized\n",
		l >> 16, l & 0xffff);

	l = sossi_पढ़ो_reg(SOSSI_INIT1_REG);
	l |= (1 << 19); /* DMA_MODE */
	l &= ~(1 << 31); /* REORDERING */
	sossi_ग_लिखो_reg(SOSSI_INIT1_REG, l);

	अगर ((r = request_irq(INT_1610_SoSSI_MATCH, sossi_match_irq,
			     IRQ_TYPE_EDGE_FALLING,
	     "sossi_match", sossi.fbdev->dev)) < 0) अणु
		dev_err(sossi.fbdev->dev, "can't get SoSSI match IRQ\n");
		जाओ err;
	पूर्ण

	clk_disable(sossi.fck);
	वापस 0;

err:
	clk_disable(sossi.fck);
	clk_put(sossi.fck);
	वापस r;
पूर्ण

अटल व्योम sossi_cleanup(व्योम)
अणु
	omap_lcdc_मुक्त_dma_callback();
	clk_put(sossi.fck);
	iounmap(sossi.base);
पूर्ण

काष्ठा lcd_ctrl_extअगर omap1_ext_अगर = अणु
	.init			= sossi_init,
	.cleanup		= sossi_cleanup,
	.get_clk_info		= sossi_get_clk_info,
	.convert_timings	= sossi_convert_timings,
	.set_timings		= sossi_set_timings,
	.set_bits_per_cycle	= sossi_set_bits_per_cycle,
	.setup_tearsync		= sossi_setup_tearsync,
	.enable_tearsync	= sossi_enable_tearsync,
	.ग_लिखो_command		= sossi_ग_लिखो_command,
	.पढ़ो_data		= sossi_पढ़ो_data,
	.ग_लिखो_data		= sossi_ग_लिखो_data,
	.transfer_area		= sossi_transfer_area,

	.max_transmit_size	= SOSSI_MAX_XMIT_BYTES,
पूर्ण;

