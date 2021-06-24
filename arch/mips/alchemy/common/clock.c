<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alchemy घड़ीs.
 *
 * Exposes all configurable पूर्णांकernal घड़ी sources to the clk framework.
 *
 * We have:
 *  - Root source, usually 12MHz supplied by an बाह्यal crystal
 *  - 3 PLLs which generate multiples of root rate [AUX, CPU, AUX2]
 *
 * Dividers:
 *  - 6 घड़ी भागiders with:
 *   * selectable source [one of the PLLs],
 *   * output भागided between [2 .. 512 in steps of 2] (!Au1300)
 *     or [1 .. 256 in steps of 1] (Au1300),
 *   * can be enabled inभागidually.
 *
 * - up to 6 "internal" (fixed) consumers which:
 *   * take either AUXPLL or one of the above 6 भागiders as input,
 *   * भागide this input by 1, 2, or 4 (and 3 on Au1300).
 *   * can be disabled separately.
 *
 * Misc घड़ीs:
 * - sysbus घड़ी: CPU core घड़ी (CPUPLL) भागided by 2, 3 or 4.
 *    depends on board design and should be set by bootloader, पढ़ो-only.
 * - peripheral घड़ी: half the rate of sysbus घड़ी, source क्रम a lot
 *    of peripheral blocks, पढ़ो-only.
 * - memory घड़ी: clk rate to मुख्य memory chips, depends on board
 *    design and is पढ़ो-only,
 * - lrclk: the अटल bus घड़ी संकेत क्रम synchronous operation.
 *    depends on board design, must be set by bootloader,
 *    but may be required to correctly configure devices attached to
 *    the अटल bus. The Au1000/1500/1100 manuals call it LCLK, on
 *    later models it's called RCLK.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

/* Base घड़ी: 12MHz is the शेष in all databooks, and I haven't
 * found any board yet which uses a dअगरferent rate.
 */
#घोषणा ALCHEMY_ROOTCLK_RATE	12000000

/*
 * the पूर्णांकernal sources which can be driven by the PLLs and भागiders.
 * Names taken from the databooks, refer to them क्रम more inक्रमmation,
 * especially which ones are share a घड़ी line.
 */
अटल स्थिर अक्षर * स्थिर alchemy_au1300_पूर्णांकclknames[] = अणु
	"lcd_intclk", "gpemgp_clk", "maempe_clk", "maebsa_clk",
	"EXTCLK0", "EXTCLK1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_au1200_पूर्णांकclknames[] = अणु
	"lcd_intclk", शून्य, शून्य, शून्य, "EXTCLK0", "EXTCLK1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_au1550_पूर्णांकclknames[] = अणु
	"usb_clk", "psc0_intclk", "psc1_intclk", "pci_clko",
	"EXTCLK0", "EXTCLK1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_au1100_पूर्णांकclknames[] = अणु
	"usb_clk", "lcd_intclk", शून्य, "i2s_clk", "EXTCLK0", "EXTCLK1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_au1500_पूर्णांकclknames[] = अणु
	शून्य, "usbd_clk", "usbh_clk", "pci_clko", "EXTCLK0", "EXTCLK1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_au1000_पूर्णांकclknames[] = अणु
	"irda_clk", "usbd_clk", "usbh_clk", "i2s_clk", "EXTCLK0",
	"EXTCLK1"
पूर्ण;

/* aliases क्रम a few on-chip sources which are either shared
 * or have gone through name changes.
 */
अटल काष्ठा clk_aliastable अणु
	अक्षर *alias;
	अक्षर *base;
	पूर्णांक cputype;
पूर्ण alchemy_clk_aliases[] __initdata = अणु
	अणु "usbh_clk", "usb_clk",    ALCHEMY_CPU_AU1100 पूर्ण,
	अणु "usbd_clk", "usb_clk",    ALCHEMY_CPU_AU1100 पूर्ण,
	अणु "irda_clk", "usb_clk",    ALCHEMY_CPU_AU1100 पूर्ण,
	अणु "usbh_clk", "usb_clk",    ALCHEMY_CPU_AU1550 पूर्ण,
	अणु "usbd_clk", "usb_clk",    ALCHEMY_CPU_AU1550 पूर्ण,
	अणु "psc2_intclk", "usb_clk", ALCHEMY_CPU_AU1550 पूर्ण,
	अणु "psc3_intclk", "EXTCLK0", ALCHEMY_CPU_AU1550 पूर्ण,
	अणु "psc0_intclk", "EXTCLK0", ALCHEMY_CPU_AU1200 पूर्ण,
	अणु "psc1_intclk", "EXTCLK1", ALCHEMY_CPU_AU1200 पूर्ण,
	अणु "psc0_intclk", "EXTCLK0", ALCHEMY_CPU_AU1300 पूर्ण,
	अणु "psc2_intclk", "EXTCLK0", ALCHEMY_CPU_AU1300 पूर्ण,
	अणु "psc1_intclk", "EXTCLK1", ALCHEMY_CPU_AU1300 पूर्ण,
	अणु "psc3_intclk", "EXTCLK1", ALCHEMY_CPU_AU1300 पूर्ण,

	अणु शून्य, शून्य, 0 पूर्ण,
पूर्ण;

#घोषणा IOMEM(x)	((व्योम __iomem *)(KSEG1ADDR(CPHYSADDR(x))))

/* access locks to SYS_FREQCTRL0/1 and SYS_CLKSRC रेजिस्टरs */
अटल spinlock_t alchemy_clk_fg0_lock;
अटल spinlock_t alchemy_clk_fg1_lock;
अटल DEFINE_SPINLOCK(alchemy_clk_csrc_lock);

/* CPU Core घड़ी *****************************************************/

अटल अचिन्हित दीर्घ alchemy_clk_cpu_recalc(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ t;

	/*
	 * On early Au1000, sys_cpupll was ग_लिखो-only. Since these
	 * silicon versions of Au1000 are not sold, we करोn't bend
	 * over backwards trying to determine the frequency.
	 */
	अगर (unlikely(au1xxx_cpu_has_pll_wo()))
		t = 396000000;
	अन्यथा अणु
		t = alchemy_rdsys(AU1000_SYS_CPUPLL) & 0x7f;
		अगर (alchemy_get_cputype() < ALCHEMY_CPU_AU1300)
			t &= 0x3f;
		t *= parent_rate;
	पूर्ण

	वापस t;
पूर्ण

व्योम __init alchemy_set_lpj(व्योम)
अणु
	preset_lpj = alchemy_clk_cpu_recalc(शून्य, ALCHEMY_ROOTCLK_RATE);
	preset_lpj /= 2 * HZ;
पूर्ण

अटल स्थिर काष्ठा clk_ops alchemy_clkops_cpu = अणु
	.recalc_rate	= alchemy_clk_cpu_recalc,
पूर्ण;

अटल काष्ठा clk __init *alchemy_clk_setup_cpu(स्थिर अक्षर *parent_name,
						पूर्णांक ctype)
अणु
	काष्ठा clk_init_data id;
	काष्ठा clk_hw *h;
	काष्ठा clk *clk;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस ERR_PTR(-ENOMEM);

	id.name = ALCHEMY_CPU_CLK;
	id.parent_names = &parent_name;
	id.num_parents = 1;
	id.flags = 0;
	id.ops = &alchemy_clkops_cpu;
	h->init = &id;

	clk = clk_रेजिस्टर(शून्य, h);
	अगर (IS_ERR(clk)) अणु
		pr_err("failed to register clock\n");
		kमुक्त(h);
	पूर्ण

	वापस clk;
पूर्ण

/* AUXPLLs ************************************************************/

काष्ठा alchemy_auxpll_clk अणु
	काष्ठा clk_hw hw;
	अचिन्हित दीर्घ reg;	/* au1300 has also AUXPLL2 */
	पूर्णांक maxmult;		/* max multiplier */
पूर्ण;
#घोषणा to_auxpll_clk(x) container_of(x, काष्ठा alchemy_auxpll_clk, hw)

अटल अचिन्हित दीर्घ alchemy_clk_aux_recalc(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_auxpll_clk *a = to_auxpll_clk(hw);

	वापस (alchemy_rdsys(a->reg) & 0xff) * parent_rate;
पूर्ण

अटल पूर्णांक alchemy_clk_aux_setr(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_auxpll_clk *a = to_auxpll_clk(hw);
	अचिन्हित दीर्घ d = rate;

	अगर (rate)
		d /= parent_rate;
	अन्यथा
		d = 0;

	/* minimum is 84MHz, max is 756-1032 depending on variant */
	अगर (((d < 7) && (d != 0)) || (d > a->maxmult))
		वापस -EINVAL;

	alchemy_wrsys(d, a->reg);
	वापस 0;
पूर्ण

अटल दीर्घ alchemy_clk_aux_roundr(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा alchemy_auxpll_clk *a = to_auxpll_clk(hw);
	अचिन्हित दीर्घ mult;

	अगर (!rate || !*parent_rate)
		वापस 0;

	mult = rate / (*parent_rate);

	अगर (mult && (mult < 7))
		mult = 7;
	अगर (mult > a->maxmult)
		mult = a->maxmult;

	वापस (*parent_rate) * mult;
पूर्ण

अटल स्थिर काष्ठा clk_ops alchemy_clkops_aux = अणु
	.recalc_rate	= alchemy_clk_aux_recalc,
	.set_rate	= alchemy_clk_aux_setr,
	.round_rate	= alchemy_clk_aux_roundr,
पूर्ण;

अटल काष्ठा clk __init *alchemy_clk_setup_aux(स्थिर अक्षर *parent_name,
						अक्षर *name, पूर्णांक maxmult,
						अचिन्हित दीर्घ reg)
अणु
	काष्ठा clk_init_data id;
	काष्ठा clk *c;
	काष्ठा alchemy_auxpll_clk *a;

	a = kzalloc(माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस ERR_PTR(-ENOMEM);

	id.name = name;
	id.parent_names = &parent_name;
	id.num_parents = 1;
	id.flags = CLK_GET_RATE_NOCACHE;
	id.ops = &alchemy_clkops_aux;

	a->reg = reg;
	a->maxmult = maxmult;
	a->hw.init = &id;

	c = clk_रेजिस्टर(शून्य, &a->hw);
	अगर (!IS_ERR(c))
		clk_रेजिस्टर_clkdev(c, name, शून्य);
	अन्यथा
		kमुक्त(a);

	वापस c;
पूर्ण

/* sysbus_clk *********************************************************/

अटल काष्ठा clk __init  *alchemy_clk_setup_sysbus(स्थिर अक्षर *pn)
अणु
	अचिन्हित दीर्घ v = (alchemy_rdsys(AU1000_SYS_POWERCTRL) & 3) + 2;
	काष्ठा clk *c;

	c = clk_रेजिस्टर_fixed_factor(शून्य, ALCHEMY_SYSBUS_CLK,
				      pn, 0, 1, v);
	अगर (!IS_ERR(c))
		clk_रेजिस्टर_clkdev(c, ALCHEMY_SYSBUS_CLK, शून्य);
	वापस c;
पूर्ण

/* Peripheral Clock ***************************************************/

अटल काष्ठा clk __init *alchemy_clk_setup_periph(स्थिर अक्षर *pn)
अणु
	/* Peripheral घड़ी runs at half the rate of sysbus clk */
	काष्ठा clk *c;

	c = clk_रेजिस्टर_fixed_factor(शून्य, ALCHEMY_PERIPH_CLK,
				      pn, 0, 1, 2);
	अगर (!IS_ERR(c))
		clk_रेजिस्टर_clkdev(c, ALCHEMY_PERIPH_CLK, शून्य);
	वापस c;
पूर्ण

/* mem घड़ी **********************************************************/

अटल काष्ठा clk __init *alchemy_clk_setup_mem(स्थिर अक्षर *pn, पूर्णांक ct)
अणु
	व्योम __iomem *addr = IOMEM(AU1000_MEM_PHYS_ADDR);
	अचिन्हित दीर्घ v;
	काष्ठा clk *c;
	पूर्णांक भाग;

	चयन (ct) अणु
	हाल ALCHEMY_CPU_AU1550:
	हाल ALCHEMY_CPU_AU1200:
		v = __raw_पढ़ोl(addr + AU1550_MEM_SDCONFIGB);
		भाग = (v & (1 << 15)) ? 1 : 2;
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		v = __raw_पढ़ोl(addr + AU1550_MEM_SDCONFIGB);
		भाग = (v & (1 << 31)) ? 1 : 2;
		अवरोध;
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
	शेष:
		भाग = 2;
		अवरोध;
	पूर्ण

	c = clk_रेजिस्टर_fixed_factor(शून्य, ALCHEMY_MEM_CLK, pn,
				      0, 1, भाग);
	अगर (!IS_ERR(c))
		clk_रेजिस्टर_clkdev(c, ALCHEMY_MEM_CLK, शून्य);
	वापस c;
पूर्ण

/* lrclk: बाह्यal synchronous अटल bus घड़ी ***********************/

अटल काष्ठा clk __init *alchemy_clk_setup_lrclk(स्थिर अक्षर *pn, पूर्णांक t)
अणु
	/* Au1000, Au1500: MEM_STCFG0[11]: If bit is set, lrclk=pclk/5,
	 * otherwise lrclk=pclk/4.
	 * All other variants: MEM_STCFG0[15:13] = भागisor.
	 * L/RCLK = periph_clk / (भागisor + 1)
	 * On Au1000, Au1500, Au1100 it's called LCLK,
	 * on later models it's called RCLK, but it's the same thing.
	 */
	काष्ठा clk *c;
	अचिन्हित दीर्घ v = alchemy_rdsmem(AU1000_MEM_STCFG0);

	चयन (t) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
		v = 4 + ((v >> 11) & 1);
		अवरोध;
	शेष:	/* all other models */
		v = ((v >> 13) & 7) + 1;
	पूर्ण
	c = clk_रेजिस्टर_fixed_factor(शून्य, ALCHEMY_LR_CLK,
				      pn, 0, 1, v);
	अगर (!IS_ERR(c))
		clk_रेजिस्टर_clkdev(c, ALCHEMY_LR_CLK, शून्य);
	वापस c;
पूर्ण

/* Clock भागiders and muxes *******************************************/

/* data क्रम fgen and csrc mux-भागiders */
काष्ठा alchemy_fgcs_clk अणु
	काष्ठा clk_hw hw;
	spinlock_t *reglock;	/* रेजिस्टर lock		  */
	अचिन्हित दीर्घ reg;	/* SYS_FREQCTRL0/1		  */
	पूर्णांक shअगरt;		/* offset in रेजिस्टर		  */
	पूर्णांक parent;		/* parent beक्रमe disable [Au1300] */
	पूर्णांक isen;		/* is it enabled?		  */
	पूर्णांक *dt;		/* भागidertable क्रम csrc	  */
पूर्ण;
#घोषणा to_fgcs_clk(x) container_of(x, काष्ठा alchemy_fgcs_clk, hw)

अटल दीर्घ alchemy_calc_भाग(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate,
			       पूर्णांक scale, पूर्णांक maxभाग, अचिन्हित दीर्घ *rv)
अणु
	दीर्घ भाग1, भाग2;

	भाग1 = prate / rate;
	अगर ((prate / भाग1) > rate)
		भाग1++;

	अगर (scale == 2) अणु	/* only भाग-by-multiple-of-2 possible */
		अगर (भाग1 & 1)
			भाग1++;	/* stay <=prate */
	पूर्ण

	भाग2 = (भाग1 / scale) - 1;	/* value to ग_लिखो to रेजिस्टर */

	अगर (भाग2 > maxभाग)
		भाग2 = maxभाग;
	अगर (rv)
		*rv = भाग2;

	भाग1 = ((भाग2 + 1) * scale);
	वापस भाग1;
पूर्ण

अटल पूर्णांक alchemy_clk_fgcs_detr(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req,
				 पूर्णांक scale, पूर्णांक maxभाग)
अणु
	काष्ठा clk_hw *pc, *bpc, *मुक्त;
	दीर्घ tdv, tpr, pr, nr, br, bpr, dअगरf, lastdअगरf;
	पूर्णांक j;

	lastdअगरf = पूर्णांक_उच्च;
	bpr = 0;
	bpc = शून्य;
	br = -EINVAL;
	मुक्त = शून्य;

	/* look at the rates each enabled parent supplies and select
	 * the one that माला_लो बंदst to but not over the requested rate.
	 */
	क्रम (j = 0; j < 7; j++) अणु
		pc = clk_hw_get_parent_by_index(hw, j);
		अगर (!pc)
			अवरोध;

		/* अगर this parent is currently unused, remember it.
		 * XXX: we would actually want clk_has_active_children()
		 * but this is a good-enough approximation क्रम now.
		 */
		अगर (!clk_hw_is_prepared(pc)) अणु
			अगर (!मुक्त)
				मुक्त = pc;
		पूर्ण

		pr = clk_hw_get_rate(pc);
		अगर (pr < req->rate)
			जारी;

		/* what can hardware actually provide */
		tdv = alchemy_calc_भाग(req->rate, pr, scale, maxभाग, शून्य);
		nr = pr / tdv;
		dअगरf = req->rate - nr;
		अगर (nr > req->rate)
			जारी;

		अगर (dअगरf < lastdअगरf) अणु
			lastdअगरf = dअगरf;
			bpr = pr;
			bpc = pc;
			br = nr;
		पूर्ण
		अगर (dअगरf == 0)
			अवरोध;
	पूर्ण

	/* अगर we couldn't get the exact rate we wanted from the enabled
	 * parents, maybe we can tell an available disabled/inactive one
	 * to give us a rate we can भागide करोwn to the requested rate.
	 */
	अगर (lastdअगरf && मुक्त) अणु
		क्रम (j = (maxभाग == 4) ? 1 : scale; j <= maxभाग; j += scale) अणु
			tpr = req->rate * j;
			अगर (tpr < 0)
				अवरोध;
			pr = clk_hw_round_rate(मुक्त, tpr);

			tdv = alchemy_calc_भाग(req->rate, pr, scale, maxभाग,
					       शून्य);
			nr = pr / tdv;
			dअगरf = req->rate - nr;
			अगर (nr > req->rate)
				जारी;
			अगर (dअगरf < lastdअगरf) अणु
				lastdअगरf = dअगरf;
				bpr = pr;
				bpc = मुक्त;
				br = nr;
			पूर्ण
			अगर (dअगरf == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (br < 0)
		वापस br;

	req->best_parent_rate = bpr;
	req->best_parent_hw = bpc;
	req->rate = br;

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv1_en(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v |= (1 << 1) << c->shअगरt;
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv1_isen(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v = alchemy_rdsys(c->reg) >> (c->shअगरt + 1);

	वापस v & 1;
पूर्ण

अटल व्योम alchemy_clk_fgv1_dis(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~((1 << 1) << c->shअगरt);
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);
पूर्ण

अटल पूर्णांक alchemy_clk_fgv1_setp(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	अगर (index)
		v |= (1 << c->shअगरt);
	अन्यथा
		v &= ~(1 << c->shअगरt);
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल u8 alchemy_clk_fgv1_getp(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);

	वापस (alchemy_rdsys(c->reg) >> c->shअगरt) & 1;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv1_setr(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ भाग, v, flags, ret;
	पूर्णांक sh = c->shअगरt + 2;

	अगर (!rate || !parent_rate || rate > (parent_rate / 2))
		वापस -EINVAL;
	ret = alchemy_calc_भाग(rate, parent_rate, 2, 512, &भाग);
	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~(0xff << sh);
	v |= भाग << sh;
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ alchemy_clk_fgv1_recalc(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v = alchemy_rdsys(c->reg) >> (c->shअगरt + 2);

	v = ((v & 0xff) + 1) * 2;
	वापस parent_rate / v;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv1_detr(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req)
अणु
	वापस alchemy_clk_fgcs_detr(hw, req, 2, 512);
पूर्ण

/* Au1000, Au1100, Au15x0, Au12x0 */
अटल स्थिर काष्ठा clk_ops alchemy_clkops_fgenv1 = अणु
	.recalc_rate	= alchemy_clk_fgv1_recalc,
	.determine_rate	= alchemy_clk_fgv1_detr,
	.set_rate	= alchemy_clk_fgv1_setr,
	.set_parent	= alchemy_clk_fgv1_setp,
	.get_parent	= alchemy_clk_fgv1_getp,
	.enable		= alchemy_clk_fgv1_en,
	.disable	= alchemy_clk_fgv1_dis,
	.is_enabled	= alchemy_clk_fgv1_isen,
पूर्ण;

अटल व्योम __alchemy_clk_fgv2_en(काष्ठा alchemy_fgcs_clk *c)
अणु
	अचिन्हित दीर्घ v = alchemy_rdsys(c->reg);

	v &= ~(3 << c->shअगरt);
	v |= (c->parent & 3) << c->shअगरt;
	alchemy_wrsys(v, c->reg);
	c->isen = 1;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv2_en(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ flags;

	/* enable by setting the previous parent घड़ी */
	spin_lock_irqsave(c->reglock, flags);
	__alchemy_clk_fgv2_en(c);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv2_isen(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);

	वापस ((alchemy_rdsys(c->reg) >> c->shअगरt) & 3) != 0;
पूर्ण

अटल व्योम alchemy_clk_fgv2_dis(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~(3 << c->shअगरt);	/* set input mux to "disabled" state */
	alchemy_wrsys(v, c->reg);
	c->isen = 0;
	spin_unlock_irqrestore(c->reglock, flags);
पूर्ण

अटल पूर्णांक alchemy_clk_fgv2_setp(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(c->reglock, flags);
	c->parent = index + 1;	/* value to ग_लिखो to रेजिस्टर */
	अगर (c->isen)
		__alchemy_clk_fgv2_en(c);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल u8 alchemy_clk_fgv2_getp(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ flags, v;

	spin_lock_irqsave(c->reglock, flags);
	v = c->parent - 1;
	spin_unlock_irqrestore(c->reglock, flags);
	वापस v;
पूर्ण

/* fg0-2 and fg4-6 share a "scale"-bit. With this bit cleared, the
 * भागiders behave exactly as on previous models (भागiders are multiples
 * of 2); with the bit set, भागiders are multiples of 1, halving their
 * range, but making them also much more flexible.
 */
अटल पूर्णांक alchemy_clk_fgv2_setr(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	पूर्णांक sh = c->shअगरt + 2;
	अचिन्हित दीर्घ भाग, v, flags, ret;

	अगर (!rate || !parent_rate || rate > parent_rate)
		वापस -EINVAL;

	v = alchemy_rdsys(c->reg) & (1 << 30); /* test "scale" bit */
	ret = alchemy_calc_भाग(rate, parent_rate, v ? 1 : 2,
			       v ? 256 : 512, &भाग);

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~(0xff << sh);
	v |= (भाग & 0xff) << sh;
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ alchemy_clk_fgv2_recalc(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	पूर्णांक sh = c->shअगरt + 2;
	अचिन्हित दीर्घ v, t;

	v = alchemy_rdsys(c->reg);
	t = parent_rate / (((v >> sh) & 0xff) + 1);
	अगर ((v & (1 << 30)) == 0)		/* test scale bit */
		t /= 2;

	वापस t;
पूर्ण

अटल पूर्णांक alchemy_clk_fgv2_detr(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	पूर्णांक scale, maxभाग;

	अगर (alchemy_rdsys(c->reg) & (1 << 30)) अणु
		scale = 1;
		maxभाग = 256;
	पूर्ण अन्यथा अणु
		scale = 2;
		maxभाग = 512;
	पूर्ण

	वापस alchemy_clk_fgcs_detr(hw, req, scale, maxभाग);
पूर्ण

/* Au1300 larger input mux, no separate disable bit, flexible भागider */
अटल स्थिर काष्ठा clk_ops alchemy_clkops_fgenv2 = अणु
	.recalc_rate	= alchemy_clk_fgv2_recalc,
	.determine_rate	= alchemy_clk_fgv2_detr,
	.set_rate	= alchemy_clk_fgv2_setr,
	.set_parent	= alchemy_clk_fgv2_setp,
	.get_parent	= alchemy_clk_fgv2_getp,
	.enable		= alchemy_clk_fgv2_en,
	.disable	= alchemy_clk_fgv2_dis,
	.is_enabled	= alchemy_clk_fgv2_isen,
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_clk_fgv1_parents[] = अणु
	ALCHEMY_CPU_CLK, ALCHEMY_AUXPLL_CLK
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_clk_fgv2_parents[] = अणु
	ALCHEMY_AUXPLL2_CLK, ALCHEMY_CPU_CLK, ALCHEMY_AUXPLL_CLK
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_clk_fgen_names[] = अणु
	ALCHEMY_FG0_CLK, ALCHEMY_FG1_CLK, ALCHEMY_FG2_CLK,
	ALCHEMY_FG3_CLK, ALCHEMY_FG4_CLK, ALCHEMY_FG5_CLK पूर्ण;

अटल पूर्णांक __init alchemy_clk_init_fgens(पूर्णांक ctype)
अणु
	काष्ठा clk *c;
	काष्ठा clk_init_data id;
	काष्ठा alchemy_fgcs_clk *a;
	अचिन्हित दीर्घ v;
	पूर्णांक i, ret;

	चयन (ctype) अणु
	हाल ALCHEMY_CPU_AU1000...ALCHEMY_CPU_AU1200:
		id.ops = &alchemy_clkops_fgenv1;
		id.parent_names = alchemy_clk_fgv1_parents;
		id.num_parents = 2;
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		id.ops = &alchemy_clkops_fgenv2;
		id.parent_names = alchemy_clk_fgv2_parents;
		id.num_parents = 3;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	id.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE;

	a = kzalloc((माप(*a)) * 6, GFP_KERNEL);
	अगर (!a)
		वापस -ENOMEM;

	spin_lock_init(&alchemy_clk_fg0_lock);
	spin_lock_init(&alchemy_clk_fg1_lock);
	ret = 0;
	क्रम (i = 0; i < 6; i++) अणु
		id.name = alchemy_clk_fgen_names[i];
		a->shअगरt = 10 * (i < 3 ? i : i - 3);
		अगर (i > 2) अणु
			a->reg = AU1000_SYS_FREQCTRL1;
			a->reglock = &alchemy_clk_fg1_lock;
		पूर्ण अन्यथा अणु
			a->reg = AU1000_SYS_FREQCTRL0;
			a->reglock = &alchemy_clk_fg0_lock;
		पूर्ण

		/* शेष to first parent अगर bootloader has set
		 * the mux to disabled state.
		 */
		अगर (ctype == ALCHEMY_CPU_AU1300) अणु
			v = alchemy_rdsys(a->reg);
			a->parent = (v >> a->shअगरt) & 3;
			अगर (!a->parent) अणु
				a->parent = 1;
				a->isen = 0;
			पूर्ण अन्यथा
				a->isen = 1;
		पूर्ण

		a->hw.init = &id;
		c = clk_रेजिस्टर(शून्य, &a->hw);
		अगर (IS_ERR(c))
			ret++;
		अन्यथा
			clk_रेजिस्टर_clkdev(c, id.name, शून्य);
		a++;
	पूर्ण

	वापस ret;
पूर्ण

/* पूर्णांकernal sources muxes *********************************************/

अटल पूर्णांक alchemy_clk_csrc_isen(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v = alchemy_rdsys(c->reg);

	वापस (((v >> c->shअगरt) >> 2) & 7) != 0;
पूर्ण

अटल व्योम __alchemy_clk_csrc_en(काष्ठा alchemy_fgcs_clk *c)
अणु
	अचिन्हित दीर्घ v = alchemy_rdsys(c->reg);

	v &= ~((7 << 2) << c->shअगरt);
	v |= ((c->parent & 7) << 2) << c->shअगरt;
	alchemy_wrsys(v, c->reg);
	c->isen = 1;
पूर्ण

अटल पूर्णांक alchemy_clk_csrc_en(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ flags;

	/* enable by setting the previous parent घड़ी */
	spin_lock_irqsave(c->reglock, flags);
	__alchemy_clk_csrc_en(c);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल व्योम alchemy_clk_csrc_dis(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~((3 << 2) << c->shअगरt);	/* mux to "disabled" state */
	alchemy_wrsys(v, c->reg);
	c->isen = 0;
	spin_unlock_irqrestore(c->reglock, flags);
पूर्ण

अटल पूर्णांक alchemy_clk_csrc_setp(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(c->reglock, flags);
	c->parent = index + 1;	/* value to ग_लिखो to रेजिस्टर */
	अगर (c->isen)
		__alchemy_clk_csrc_en(c);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल u8 alchemy_clk_csrc_getp(काष्ठा clk_hw *hw)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);

	वापस c->parent - 1;
पूर्ण

अटल अचिन्हित दीर्घ alchemy_clk_csrc_recalc(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ v = (alchemy_rdsys(c->reg) >> c->shअगरt) & 3;

	वापस parent_rate / c->dt[v];
पूर्ण

अटल पूर्णांक alchemy_clk_csrc_setr(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	अचिन्हित दीर्घ d, v, flags;
	पूर्णांक i;

	अगर (!rate || !parent_rate || rate > parent_rate)
		वापस -EINVAL;

	d = (parent_rate + (rate / 2)) / rate;
	अगर (d > 4)
		वापस -EINVAL;
	अगर ((d == 3) && (c->dt[2] != 3))
		d = 4;

	क्रम (i = 0; i < 4; i++)
		अगर (c->dt[i] == d)
			अवरोध;

	अगर (i >= 4)
		वापस -EINVAL;	/* oops */

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~(3 << c->shअगरt);
	v |= (i & 3) << c->shअगरt;
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_clk_csrc_detr(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req)
अणु
	काष्ठा alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	पूर्णांक scale = c->dt[2] == 3 ? 1 : 2; /* au1300 check */

	वापस alchemy_clk_fgcs_detr(hw, req, scale, 4);
पूर्ण

अटल स्थिर काष्ठा clk_ops alchemy_clkops_csrc = अणु
	.recalc_rate	= alchemy_clk_csrc_recalc,
	.determine_rate	= alchemy_clk_csrc_detr,
	.set_rate	= alchemy_clk_csrc_setr,
	.set_parent	= alchemy_clk_csrc_setp,
	.get_parent	= alchemy_clk_csrc_getp,
	.enable		= alchemy_clk_csrc_en,
	.disable	= alchemy_clk_csrc_dis,
	.is_enabled	= alchemy_clk_csrc_isen,
पूर्ण;

अटल स्थिर अक्षर * स्थिर alchemy_clk_csrc_parents[] = अणु
	/* disabled at index 0 */ ALCHEMY_AUXPLL_CLK,
	ALCHEMY_FG0_CLK, ALCHEMY_FG1_CLK, ALCHEMY_FG2_CLK,
	ALCHEMY_FG3_CLK, ALCHEMY_FG4_CLK, ALCHEMY_FG5_CLK
पूर्ण;

/* भागider tables */
अटल पूर्णांक alchemy_csrc_dt1[] = अणु 1, 4, 1, 2 पूर्ण;	/* rest */
अटल पूर्णांक alchemy_csrc_dt2[] = अणु 1, 4, 3, 2 पूर्ण;	/* Au1300 */

अटल पूर्णांक __init alchemy_clk_setup_imux(पूर्णांक ctype)
अणु
	काष्ठा alchemy_fgcs_clk *a;
	स्थिर अक्षर * स्थिर *names;
	काष्ठा clk_init_data id;
	अचिन्हित दीर्घ v;
	पूर्णांक i, ret, *dt;
	काष्ठा clk *c;

	id.ops = &alchemy_clkops_csrc;
	id.parent_names = alchemy_clk_csrc_parents;
	id.num_parents = 7;
	id.flags = CLK_SET_RATE_PARENT | CLK_GET_RATE_NOCACHE;

	dt = alchemy_csrc_dt1;
	चयन (ctype) अणु
	हाल ALCHEMY_CPU_AU1000:
		names = alchemy_au1000_पूर्णांकclknames;
		अवरोध;
	हाल ALCHEMY_CPU_AU1500:
		names = alchemy_au1500_पूर्णांकclknames;
		अवरोध;
	हाल ALCHEMY_CPU_AU1100:
		names = alchemy_au1100_पूर्णांकclknames;
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		names = alchemy_au1550_पूर्णांकclknames;
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		names = alchemy_au1200_पूर्णांकclknames;
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		dt = alchemy_csrc_dt2;
		names = alchemy_au1300_पूर्णांकclknames;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	a = kसुस्मृति(6, माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस -ENOMEM;

	ret = 0;

	क्रम (i = 0; i < 6; i++) अणु
		id.name = names[i];
		अगर (!id.name)
			जाओ next;

		a->shअगरt = i * 5;
		a->reg = AU1000_SYS_CLKSRC;
		a->reglock = &alchemy_clk_csrc_lock;
		a->dt = dt;

		/* शेष to first parent घड़ी अगर mux is initially
		 * set to disabled state.
		 */
		v = alchemy_rdsys(a->reg);
		a->parent = ((v >> a->shअगरt) >> 2) & 7;
		अगर (!a->parent) अणु
			a->parent = 1;
			a->isen = 0;
		पूर्ण अन्यथा
			a->isen = 1;

		a->hw.init = &id;
		c = clk_रेजिस्टर(शून्य, &a->hw);
		अगर (IS_ERR(c))
			ret++;
		अन्यथा
			clk_रेजिस्टर_clkdev(c, id.name, शून्य);
next:
		a++;
	पूर्ण

	वापस ret;
पूर्ण


/**********************************************************************/


#घोषणा ERRCK(x)						\
	अगर (IS_ERR(x)) अणु					\
		ret = PTR_ERR(x);				\
		जाओ out;					\
	पूर्ण

अटल पूर्णांक __init alchemy_clk_init(व्योम)
अणु
	पूर्णांक ctype = alchemy_get_cputype(), ret, i;
	काष्ठा clk_aliastable *t = alchemy_clk_aliases;
	काष्ठा clk *c;

	/* Root of the Alchemy घड़ी tree: बाह्यal 12MHz crystal osc */
	c = clk_रेजिस्टर_fixed_rate(शून्य, ALCHEMY_ROOT_CLK, शून्य,
					   0, ALCHEMY_ROOTCLK_RATE);
	ERRCK(c)

	/* CPU core घड़ी */
	c = alchemy_clk_setup_cpu(ALCHEMY_ROOT_CLK, ctype);
	ERRCK(c)

	/* AUXPLLs: max 1GHz on Au1300, 748MHz on older models */
	i = (ctype == ALCHEMY_CPU_AU1300) ? 84 : 63;
	c = alchemy_clk_setup_aux(ALCHEMY_ROOT_CLK, ALCHEMY_AUXPLL_CLK,
				  i, AU1000_SYS_AUXPLL);
	ERRCK(c)

	अगर (ctype == ALCHEMY_CPU_AU1300) अणु
		c = alchemy_clk_setup_aux(ALCHEMY_ROOT_CLK,
					  ALCHEMY_AUXPLL2_CLK, i,
					  AU1300_SYS_AUXPLL2);
		ERRCK(c)
	पूर्ण

	/* sysbus घड़ी: cpu core घड़ी भागided by 2, 3 or 4 */
	c = alchemy_clk_setup_sysbus(ALCHEMY_CPU_CLK);
	ERRCK(c)

	/* peripheral घड़ी: runs at half rate of sysbus clk */
	c = alchemy_clk_setup_periph(ALCHEMY_SYSBUS_CLK);
	ERRCK(c)

	/* SDR/DDR memory घड़ी */
	c = alchemy_clk_setup_mem(ALCHEMY_SYSBUS_CLK, ctype);
	ERRCK(c)

	/* L/RCLK: बाह्यal अटल bus घड़ी क्रम synchronous mode */
	c = alchemy_clk_setup_lrclk(ALCHEMY_PERIPH_CLK, ctype);
	ERRCK(c)

	/* Frequency भागiders 0-5 */
	ret = alchemy_clk_init_fgens(ctype);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* भागing muxes क्रम पूर्णांकernal sources */
	ret = alchemy_clk_setup_imux(ctype);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* set up aliases drivers might look क्रम */
	जबतक (t->base) अणु
		अगर (t->cputype == ctype)
			clk_add_alias(t->alias, शून्य, t->base, शून्य);
		t++;
	पूर्ण

	pr_info("Alchemy clocktree installed\n");
	वापस 0;

out:
	वापस ret;
पूर्ण
postcore_initcall(alchemy_clk_init);
