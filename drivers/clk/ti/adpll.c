<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/माला.स>

#घोषणा ADPLL_PLLSS_MMR_LOCK_OFFSET	0x00	/* Managed by MPPULL */
#घोषणा ADPLL_PLLSS_MMR_LOCK_ENABLED	0x1f125B64
#घोषणा ADPLL_PLLSS_MMR_UNLOCK_MAGIC	0x1eda4c3d

#घोषणा ADPLL_PWRCTRL_OFFSET		0x00
#घोषणा ADPLL_PWRCTRL_PONIN		5
#घोषणा ADPLL_PWRCTRL_PGOODIN		4
#घोषणा ADPLL_PWRCTRL_RET		3
#घोषणा ADPLL_PWRCTRL_ISORET		2
#घोषणा ADPLL_PWRCTRL_ISOSCAN		1
#घोषणा ADPLL_PWRCTRL_OFFMODE		0

#घोषणा ADPLL_CLKCTRL_OFFSET		0x04
#घोषणा ADPLL_CLKCTRL_CLKDCOLDOEN	29
#घोषणा ADPLL_CLKCTRL_IDLE		23
#घोषणा ADPLL_CLKCTRL_CLKOUTEN		20
#घोषणा ADPLL_CLKINPHIFSEL_ADPLL_S	19	/* REVISIT: which bit? */
#घोषणा ADPLL_CLKCTRL_CLKOUTLDOEN_ADPLL_LJ 19
#घोषणा ADPLL_CLKCTRL_ULOWCLKEN		18
#घोषणा ADPLL_CLKCTRL_CLKDCOLDOPWDNZ	17
#घोषणा ADPLL_CLKCTRL_M2PWDNZ		16
#घोषणा ADPLL_CLKCTRL_M3PWDNZ_ADPLL_S	15
#घोषणा ADPLL_CLKCTRL_LOWCURRSTDBY_ADPLL_S 13
#घोषणा ADPLL_CLKCTRL_LPMODE_ADPLL_S	12
#घोषणा ADPLL_CLKCTRL_REGM4XEN_ADPLL_S	10
#घोषणा ADPLL_CLKCTRL_SELFREQDCO_ADPLL_LJ 10
#घोषणा ADPLL_CLKCTRL_TINITZ		0

#घोषणा ADPLL_TENABLE_OFFSET		0x08
#घोषणा ADPLL_TENABLEDIV_OFFSET		0x8c

#घोषणा ADPLL_M2NDIV_OFFSET		0x10
#घोषणा ADPLL_M2NDIV_M2			16
#घोषणा ADPLL_M2NDIV_M2_ADPLL_S_WIDTH	5
#घोषणा ADPLL_M2NDIV_M2_ADPLL_LJ_WIDTH	7

#घोषणा ADPLL_MN2DIV_OFFSET		0x14
#घोषणा ADPLL_MN2DIV_N2			16

#घोषणा ADPLL_FRACDIV_OFFSET		0x18
#घोषणा ADPLL_FRACDIV_REGSD		24
#घोषणा ADPLL_FRACDIV_FRACTIONALM	0
#घोषणा ADPLL_FRACDIV_FRACTIONALM_MASK	0x3ffff

#घोषणा ADPLL_BWCTRL_OFFSET		0x1c
#घोषणा ADPLL_BWCTRL_BWCONTROL		1
#घोषणा ADPLL_BWCTRL_BW_INCR_DECRZ	0

#घोषणा ADPLL_RESERVED_OFFSET		0x20

#घोषणा ADPLL_STATUS_OFFSET		0x24
#घोषणा ADPLL_STATUS_PONOUT		31
#घोषणा ADPLL_STATUS_PGOODOUT		30
#घोषणा ADPLL_STATUS_LDOPWDN		29
#घोषणा ADPLL_STATUS_RECAL_BSTATUS3	28
#घोषणा ADPLL_STATUS_RECAL_OPPIN	27
#घोषणा ADPLL_STATUS_PHASELOCK		10
#घोषणा ADPLL_STATUS_FREQLOCK		9
#घोषणा ADPLL_STATUS_BYPASSACK		8
#घोषणा ADPLL_STATUS_LOSSREF		6
#घोषणा ADPLL_STATUS_CLKOUTENACK	5
#घोषणा ADPLL_STATUS_LOCK2		4
#घोषणा ADPLL_STATUS_M2CHANGEACK	3
#घोषणा ADPLL_STATUS_HIGHJITTER		1
#घोषणा ADPLL_STATUS_BYPASS		0
#घोषणा ADPLL_STATUS_PREPARED_MASK	(BIT(ADPLL_STATUS_PHASELOCK) | \
					 BIT(ADPLL_STATUS_FREQLOCK))

#घोषणा ADPLL_M3DIV_OFFSET		0x28	/* Only on MPUPLL */
#घोषणा ADPLL_M3DIV_M3			0
#घोषणा ADPLL_M3DIV_M3_WIDTH		5
#घोषणा ADPLL_M3DIV_M3_MASK		0x1f

#घोषणा ADPLL_RAMPCTRL_OFFSET		0x2c	/* Only on MPUPLL */
#घोषणा ADPLL_RAMPCTRL_CLKRAMPLEVEL	19
#घोषणा ADPLL_RAMPCTRL_CLKRAMPRATE	16
#घोषणा ADPLL_RAMPCTRL_RELOCK_RAMP_EN	0

#घोषणा MAX_ADPLL_INPUTS		3
#घोषणा MAX_ADPLL_OUTPUTS		4
#घोषणा ADPLL_MAX_RETRIES		5

#घोषणा to_dco(_hw)	container_of(_hw, काष्ठा ti_adpll_dco_data, hw)
#घोषणा to_adpll(_hw)	container_of(_hw, काष्ठा ti_adpll_data, dco)
#घोषणा to_clkout(_hw)	container_of(_hw, काष्ठा ti_adpll_clkout_data, hw)

क्रमागत ti_adpll_घड़ीs अणु
	TI_ADPLL_DCO,
	TI_ADPLL_DCO_GATE,
	TI_ADPLL_N2,
	TI_ADPLL_M2,
	TI_ADPLL_M2_GATE,
	TI_ADPLL_BYPASS,
	TI_ADPLL_HIF,
	TI_ADPLL_DIV2,
	TI_ADPLL_CLKOUT,
	TI_ADPLL_CLKOUT2,
	TI_ADPLL_M3,
पूर्ण;

#घोषणा TI_ADPLL_NR_CLOCKS	(TI_ADPLL_M3 + 1)

क्रमागत ti_adpll_inमाला_दो अणु
	TI_ADPLL_CLKINP,
	TI_ADPLL_CLKINPULOW,
	TI_ADPLL_CLKINPHIF,
पूर्ण;

क्रमागत ti_adpll_s_outमाला_दो अणु
	TI_ADPLL_S_DCOCLKLDO,
	TI_ADPLL_S_CLKOUT,
	TI_ADPLL_S_CLKOUTX2,
	TI_ADPLL_S_CLKOUTHIF,
पूर्ण;

क्रमागत ti_adpll_lj_outमाला_दो अणु
	TI_ADPLL_LJ_CLKDCOLDO,
	TI_ADPLL_LJ_CLKOUT,
	TI_ADPLL_LJ_CLKOUTLDO,
पूर्ण;

काष्ठा ti_adpll_platक्रमm_data अणु
	स्थिर bool is_type_s;
	स्थिर पूर्णांक nr_max_inमाला_दो;
	स्थिर पूर्णांक nr_max_outमाला_दो;
	स्थिर पूर्णांक output_index;
पूर्ण;

काष्ठा ti_adpll_घड़ी अणु
	काष्ठा clk *clk;
	काष्ठा clk_lookup *cl;
	व्योम (*unरेजिस्टर)(काष्ठा clk *clk);
पूर्ण;

काष्ठा ti_adpll_dco_data अणु
	काष्ठा clk_hw hw;
पूर्ण;

काष्ठा ti_adpll_clkout_data अणु
	काष्ठा ti_adpll_data *adpll;
	काष्ठा clk_gate gate;
	काष्ठा clk_hw hw;
पूर्ण;

काष्ठा ti_adpll_data अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ti_adpll_platक्रमm_data *c;
	काष्ठा device_node *np;
	अचिन्हित दीर्घ pa;
	व्योम __iomem *iobase;
	व्योम __iomem *regs;
	spinlock_t lock;	/* For ADPLL shared रेजिस्टर access */
	स्थिर अक्षर *parent_names[MAX_ADPLL_INPUTS];
	काष्ठा clk *parent_घड़ीs[MAX_ADPLL_INPUTS];
	काष्ठा ti_adpll_घड़ी *घड़ीs;
	काष्ठा clk_onecell_data outमाला_दो;
	काष्ठा ti_adpll_dco_data dco;
पूर्ण;

अटल स्थिर अक्षर *ti_adpll_clk_get_name(काष्ठा ti_adpll_data *d,
					 पूर्णांक output_index,
					 स्थिर अक्षर *postfix)
अणु
	स्थिर अक्षर *name;
	पूर्णांक err;

	अगर (output_index >= 0) अणु
		err = of_property_पढ़ो_string_index(d->np,
						    "clock-output-names",
						    output_index,
						    &name);
		अगर (err)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		name = devm_kaप्र_लिखो(d->dev, GFP_KERNEL, "%08lx.adpll.%s",
				      d->pa, postfix);
	पूर्ण

	वापस name;
पूर्ण

#घोषणा ADPLL_MAX_CON_ID	16	/* See MAX_CON_ID */

अटल पूर्णांक ti_adpll_setup_घड़ी(काष्ठा ti_adpll_data *d, काष्ठा clk *घड़ी,
				पूर्णांक index, पूर्णांक output_index, स्थिर अक्षर *name,
				व्योम (*unरेजिस्टर)(काष्ठा clk *clk))
अणु
	काष्ठा clk_lookup *cl;
	स्थिर अक्षर *postfix = शून्य;
	अक्षर con_id[ADPLL_MAX_CON_ID];

	d->घड़ीs[index].clk = घड़ी;
	d->घड़ीs[index].unरेजिस्टर = unरेजिस्टर;

	/* Separate con_id in क्रमmat "pll040dcoclkldo" to fit MAX_CON_ID */
	postfix = म_खोजप(name, '.');
	अगर (postfix && म_माप(postfix) > 1) अणु
		अगर (म_माप(postfix) > ADPLL_MAX_CON_ID)
			dev_warn(d->dev, "clock %s con_id lookup may fail\n",
				 name);
		snम_लिखो(con_id, 16, "pll%03lx%s", d->pa & 0xfff, postfix + 1);
		cl = clkdev_create(घड़ी, con_id, शून्य);
		अगर (!cl)
			वापस -ENOMEM;
		d->घड़ीs[index].cl = cl;
	पूर्ण अन्यथा अणु
		dev_warn(d->dev, "no con_id for clock %s\n", name);
	पूर्ण

	अगर (output_index < 0)
		वापस 0;

	d->outमाला_दो.clks[output_index] = घड़ी;
	d->outमाला_दो.clk_num++;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_adpll_init_भागider(काष्ठा ti_adpll_data *d,
				 क्रमागत ti_adpll_घड़ीs index,
				 पूर्णांक output_index, अक्षर *name,
				 काष्ठा clk *parent_घड़ी,
				 व्योम __iomem *reg,
				 u8 shअगरt, u8 width,
				 u8 clk_भागider_flags)
अणु
	स्थिर अक्षर *child_name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *घड़ी;

	child_name = ti_adpll_clk_get_name(d, output_index, name);
	अगर (!child_name)
		वापस -EINVAL;

	parent_name = __clk_get_name(parent_घड़ी);
	घड़ी = clk_रेजिस्टर_भागider(d->dev, child_name, parent_name, 0,
				     reg, shअगरt, width, clk_भागider_flags,
				     &d->lock);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "failed to register divider %s: %li\n",
			name, PTR_ERR(घड़ी));
		वापस PTR_ERR(घड़ी);
	पूर्ण

	वापस ti_adpll_setup_घड़ी(d, घड़ी, index, output_index, child_name,
				    clk_unरेजिस्टर_भागider);
पूर्ण

अटल पूर्णांक ti_adpll_init_mux(काष्ठा ti_adpll_data *d,
			     क्रमागत ti_adpll_घड़ीs index,
			     अक्षर *name, काष्ठा clk *clk0,
			     काष्ठा clk *clk1,
			     व्योम __iomem *reg,
			     u8 shअगरt)
अणु
	स्थिर अक्षर *child_name;
	स्थिर अक्षर *parents[2];
	काष्ठा clk *घड़ी;

	child_name = ti_adpll_clk_get_name(d, -ENODEV, name);
	अगर (!child_name)
		वापस -ENOMEM;
	parents[0] = __clk_get_name(clk0);
	parents[1] = __clk_get_name(clk1);
	घड़ी = clk_रेजिस्टर_mux(d->dev, child_name, parents, 2, 0,
				 reg, shअगरt, 1, 0, &d->lock);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "failed to register mux %s: %li\n",
			name, PTR_ERR(घड़ी));
		वापस PTR_ERR(घड़ी);
	पूर्ण

	वापस ti_adpll_setup_घड़ी(d, घड़ी, index, -ENODEV, child_name,
				    clk_unरेजिस्टर_mux);
पूर्ण

अटल पूर्णांक ti_adpll_init_gate(काष्ठा ti_adpll_data *d,
			      क्रमागत ti_adpll_घड़ीs index,
			      पूर्णांक output_index, अक्षर *name,
			      काष्ठा clk *parent_घड़ी,
			      व्योम __iomem *reg,
			      u8 bit_idx,
			      u8 clk_gate_flags)
अणु
	स्थिर अक्षर *child_name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *घड़ी;

	child_name = ti_adpll_clk_get_name(d, output_index, name);
	अगर (!child_name)
		वापस -EINVAL;

	parent_name = __clk_get_name(parent_घड़ी);
	घड़ी = clk_रेजिस्टर_gate(d->dev, child_name, parent_name, 0,
				  reg, bit_idx, clk_gate_flags,
				  &d->lock);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "failed to register gate %s: %li\n",
			name, PTR_ERR(घड़ी));
		वापस PTR_ERR(घड़ी);
	पूर्ण

	वापस ti_adpll_setup_घड़ी(d, घड़ी, index, output_index, child_name,
				    clk_unरेजिस्टर_gate);
पूर्ण

अटल पूर्णांक ti_adpll_init_fixed_factor(काष्ठा ti_adpll_data *d,
				      क्रमागत ti_adpll_घड़ीs index,
				      अक्षर *name,
				      काष्ठा clk *parent_घड़ी,
				      अचिन्हित पूर्णांक mult,
				      अचिन्हित पूर्णांक भाग)
अणु
	स्थिर अक्षर *child_name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *घड़ी;

	child_name = ti_adpll_clk_get_name(d, -ENODEV, name);
	अगर (!child_name)
		वापस -ENOMEM;

	parent_name = __clk_get_name(parent_घड़ी);
	घड़ी = clk_रेजिस्टर_fixed_factor(d->dev, child_name, parent_name,
					  0, mult, भाग);
	अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	वापस ti_adpll_setup_घड़ी(d, घड़ी, index, -ENODEV, child_name,
				    clk_unरेजिस्टर);
पूर्ण

अटल व्योम ti_adpll_set_idle_bypass(काष्ठा ti_adpll_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 v;

	spin_lock_irqsave(&d->lock, flags);
	v = पढ़ोl_relaxed(d->regs + ADPLL_CLKCTRL_OFFSET);
	v |= BIT(ADPLL_CLKCTRL_IDLE);
	ग_लिखोl_relaxed(v, d->regs + ADPLL_CLKCTRL_OFFSET);
	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

अटल व्योम ti_adpll_clear_idle_bypass(काष्ठा ti_adpll_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 v;

	spin_lock_irqsave(&d->lock, flags);
	v = पढ़ोl_relaxed(d->regs + ADPLL_CLKCTRL_OFFSET);
	v &= ~BIT(ADPLL_CLKCTRL_IDLE);
	ग_लिखोl_relaxed(v, d->regs + ADPLL_CLKCTRL_OFFSET);
	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

अटल bool ti_adpll_घड़ी_is_bypass(काष्ठा ti_adpll_data *d)
अणु
	u32 v;

	v = पढ़ोl_relaxed(d->regs + ADPLL_STATUS_OFFSET);

	वापस v & BIT(ADPLL_STATUS_BYPASS);
पूर्ण

/*
 * Locked and bypass are not actually mutually exclusive:  अगर you only care
 * about the DCO घड़ी and not CLKOUT you can clear M2PWDNZ beक्रमe enabling
 * the PLL, resulting in status (FREQLOCK | PHASELOCK | BYPASS) after lock.
 */
अटल bool ti_adpll_is_locked(काष्ठा ti_adpll_data *d)
अणु
	u32 v = पढ़ोl_relaxed(d->regs + ADPLL_STATUS_OFFSET);

	वापस (v & ADPLL_STATUS_PREPARED_MASK) == ADPLL_STATUS_PREPARED_MASK;
पूर्ण

अटल पूर्णांक ti_adpll_रुको_lock(काष्ठा ti_adpll_data *d)
अणु
	पूर्णांक retries = ADPLL_MAX_RETRIES;

	करो अणु
		अगर (ti_adpll_is_locked(d))
			वापस 0;
		usleep_range(200, 300);
	पूर्ण जबतक (retries--);

	dev_err(d->dev, "pll failed to lock\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ti_adpll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_dco_data *dco = to_dco(hw);
	काष्ठा ti_adpll_data *d = to_adpll(dco);

	ti_adpll_clear_idle_bypass(d);
	ti_adpll_रुको_lock(d);

	वापस 0;
पूर्ण

अटल व्योम ti_adpll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_dco_data *dco = to_dco(hw);
	काष्ठा ti_adpll_data *d = to_adpll(dco);

	ti_adpll_set_idle_bypass(d);
पूर्ण

अटल पूर्णांक ti_adpll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_dco_data *dco = to_dco(hw);
	काष्ठा ti_adpll_data *d = to_adpll(dco);

	वापस ti_adpll_is_locked(d);
पूर्ण

/*
 * Note that the DCO घड़ी is never subject to bypass: अगर the PLL is off,
 * dcoclk is low.
 */
अटल अचिन्हित दीर्घ ti_adpll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ti_adpll_dco_data *dco = to_dco(hw);
	काष्ठा ti_adpll_data *d = to_adpll(dco);
	u32 frac_m, भागider, v;
	u64 rate;
	अचिन्हित दीर्घ flags;

	अगर (ti_adpll_घड़ी_is_bypass(d))
		वापस 0;

	spin_lock_irqsave(&d->lock, flags);
	frac_m = पढ़ोl_relaxed(d->regs + ADPLL_FRACDIV_OFFSET);
	frac_m &= ADPLL_FRACDIV_FRACTIONALM_MASK;
	rate = (u64)पढ़ोw_relaxed(d->regs + ADPLL_MN2DIV_OFFSET) << 18;
	rate += frac_m;
	rate *= parent_rate;
	भागider = (पढ़ोw_relaxed(d->regs + ADPLL_M2NDIV_OFFSET) + 1) << 18;
	spin_unlock_irqrestore(&d->lock, flags);

	करो_भाग(rate, भागider);

	अगर (d->c->is_type_s) अणु
		v = पढ़ोl_relaxed(d->regs + ADPLL_CLKCTRL_OFFSET);
		अगर (v & BIT(ADPLL_CLKCTRL_REGM4XEN_ADPLL_S))
			rate *= 4;
		rate *= 2;
	पूर्ण

	वापस rate;
पूर्ण

/* PLL parent is always clkinp, bypass only affects the children */
अटल u8 ti_adpll_get_parent(काष्ठा clk_hw *hw)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops ti_adpll_ops = अणु
	.prepare = ti_adpll_prepare,
	.unprepare = ti_adpll_unprepare,
	.is_prepared = ti_adpll_is_prepared,
	.recalc_rate = ti_adpll_recalc_rate,
	.get_parent = ti_adpll_get_parent,
पूर्ण;

अटल पूर्णांक ti_adpll_init_dco(काष्ठा ti_adpll_data *d)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk *घड़ी;
	स्थिर अक्षर *postfix;
	पूर्णांक width, err;

	d->outमाला_दो.clks = devm_kसुस्मृति(d->dev,
				       MAX_ADPLL_OUTPUTS,
				       माप(काष्ठा clk *),
				       GFP_KERNEL);
	अगर (!d->outमाला_दो.clks)
		वापस -ENOMEM;

	अगर (d->c->output_index < 0)
		postfix = "dco";
	अन्यथा
		postfix = शून्य;

	init.name = ti_adpll_clk_get_name(d, d->c->output_index, postfix);
	अगर (!init.name)
		वापस -EINVAL;

	init.parent_names = d->parent_names;
	init.num_parents = d->c->nr_max_inमाला_दो;
	init.ops = &ti_adpll_ops;
	init.flags = CLK_GET_RATE_NOCACHE;
	d->dco.hw.init = &init;

	अगर (d->c->is_type_s)
		width = 5;
	अन्यथा
		width = 4;

	/* Internal input घड़ी भागider N2 */
	err = ti_adpll_init_भागider(d, TI_ADPLL_N2, -ENODEV, "n2",
				    d->parent_घड़ीs[TI_ADPLL_CLKINP],
				    d->regs + ADPLL_MN2DIV_OFFSET,
				    ADPLL_MN2DIV_N2, width, 0);
	अगर (err)
		वापस err;

	घड़ी = devm_clk_रेजिस्टर(d->dev, &d->dco.hw);
	अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	वापस ti_adpll_setup_घड़ी(d, घड़ी, TI_ADPLL_DCO, d->c->output_index,
				    init.name, शून्य);
पूर्ण

अटल पूर्णांक ti_adpll_clkout_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_clkout_data *co = to_clkout(hw);
	काष्ठा clk_hw *gate_hw = &co->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस clk_gate_ops.enable(gate_hw);
पूर्ण

अटल व्योम ti_adpll_clkout_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_clkout_data *co = to_clkout(hw);
	काष्ठा clk_hw *gate_hw = &co->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);
	clk_gate_ops.disable(gate_hw);
पूर्ण

अटल पूर्णांक ti_adpll_clkout_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_clkout_data *co = to_clkout(hw);
	काष्ठा clk_hw *gate_hw = &co->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस clk_gate_ops.is_enabled(gate_hw);
पूर्ण

/* Setting PLL bypass माला_दो clkout and clkoutx2 पूर्णांकo bypass */
अटल u8 ti_adpll_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_adpll_clkout_data *co = to_clkout(hw);
	काष्ठा ti_adpll_data *d = co->adpll;

	वापस ti_adpll_घड़ी_is_bypass(d);
पूर्ण

अटल पूर्णांक ti_adpll_init_clkout(काष्ठा ti_adpll_data *d,
				क्रमागत ti_adpll_घड़ीs index,
				पूर्णांक output_index, पूर्णांक gate_bit,
				अक्षर *name, काष्ठा clk *clk0,
				काष्ठा clk *clk1)
अणु
	काष्ठा ti_adpll_clkout_data *co;
	काष्ठा clk_init_data init;
	काष्ठा clk_ops *ops;
	स्थिर अक्षर *parent_names[2];
	स्थिर अक्षर *child_name;
	काष्ठा clk *घड़ी;
	पूर्णांक err;

	co = devm_kzalloc(d->dev, माप(*co), GFP_KERNEL);
	अगर (!co)
		वापस -ENOMEM;
	co->adpll = d;

	err = of_property_पढ़ो_string_index(d->np,
					    "clock-output-names",
					    output_index,
					    &child_name);
	अगर (err)
		वापस err;

	ops = devm_kzalloc(d->dev, माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	init.name = child_name;
	init.ops = ops;
	init.flags = 0;
	co->hw.init = &init;
	parent_names[0] = __clk_get_name(clk0);
	parent_names[1] = __clk_get_name(clk1);
	init.parent_names = parent_names;
	init.num_parents = 2;

	ops->get_parent = ti_adpll_clkout_get_parent;
	ops->determine_rate = __clk_mux_determine_rate;
	अगर (gate_bit) अणु
		co->gate.lock = &d->lock;
		co->gate.reg = d->regs + ADPLL_CLKCTRL_OFFSET;
		co->gate.bit_idx = gate_bit;
		ops->enable = ti_adpll_clkout_enable;
		ops->disable = ti_adpll_clkout_disable;
		ops->is_enabled = ti_adpll_clkout_is_enabled;
	पूर्ण

	घड़ी = devm_clk_रेजिस्टर(d->dev, &co->hw);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "failed to register output %s: %li\n",
			name, PTR_ERR(घड़ी));
		वापस PTR_ERR(घड़ी);
	पूर्ण

	वापस ti_adpll_setup_घड़ी(d, घड़ी, index, output_index, child_name,
				    शून्य);
पूर्ण

अटल पूर्णांक ti_adpll_init_children_adpll_s(काष्ठा ti_adpll_data *d)
अणु
	पूर्णांक err;

	अगर (!d->c->is_type_s)
		वापस 0;

	/* Internal mux, sources from भागider N2 or clkinpulow */
	err = ti_adpll_init_mux(d, TI_ADPLL_BYPASS, "bypass",
				d->घड़ीs[TI_ADPLL_N2].clk,
				d->parent_घड़ीs[TI_ADPLL_CLKINPULOW],
				d->regs + ADPLL_CLKCTRL_OFFSET,
				ADPLL_CLKCTRL_ULOWCLKEN);
	अगर (err)
		वापस err;

	/* Internal भागider M2, sources DCO */
	err = ti_adpll_init_भागider(d, TI_ADPLL_M2, -ENODEV, "m2",
				    d->घड़ीs[TI_ADPLL_DCO].clk,
				    d->regs + ADPLL_M2NDIV_OFFSET,
				    ADPLL_M2NDIV_M2,
				    ADPLL_M2NDIV_M2_ADPLL_S_WIDTH,
				    CLK_DIVIDER_ONE_BASED);
	अगर (err)
		वापस err;

	/* Internal fixed भागider, after M2 beक्रमe clkout */
	err = ti_adpll_init_fixed_factor(d, TI_ADPLL_DIV2, "div2",
					 d->घड़ीs[TI_ADPLL_M2].clk,
					 1, 2);
	अगर (err)
		वापस err;

	/* Output clkout with a mux and gate, sources from भाग2 or bypass */
	err = ti_adpll_init_clkout(d, TI_ADPLL_CLKOUT, TI_ADPLL_S_CLKOUT,
				   ADPLL_CLKCTRL_CLKOUTEN, "clkout",
				   d->घड़ीs[TI_ADPLL_DIV2].clk,
				   d->घड़ीs[TI_ADPLL_BYPASS].clk);
	अगर (err)
		वापस err;

	/* Output clkoutx2 with a mux and gate, sources from M2 or bypass */
	err = ti_adpll_init_clkout(d, TI_ADPLL_CLKOUT2, TI_ADPLL_S_CLKOUTX2, 0,
				   "clkout2", d->घड़ीs[TI_ADPLL_M2].clk,
				   d->घड़ीs[TI_ADPLL_BYPASS].clk);
	अगर (err)
		वापस err;

	/* Internal mux, sources from DCO and clkinphअगर */
	अगर (d->parent_घड़ीs[TI_ADPLL_CLKINPHIF]) अणु
		err = ti_adpll_init_mux(d, TI_ADPLL_HIF, "hif",
					d->घड़ीs[TI_ADPLL_DCO].clk,
					d->parent_घड़ीs[TI_ADPLL_CLKINPHIF],
					d->regs + ADPLL_CLKCTRL_OFFSET,
					ADPLL_CLKINPHIFSEL_ADPLL_S);
		अगर (err)
			वापस err;
	पूर्ण

	/* Output clkouthअगर with a भागider M3, sources from hअगर */
	err = ti_adpll_init_भागider(d, TI_ADPLL_M3, TI_ADPLL_S_CLKOUTHIF, "m3",
				    d->घड़ीs[TI_ADPLL_HIF].clk,
				    d->regs + ADPLL_M3DIV_OFFSET,
				    ADPLL_M3DIV_M3,
				    ADPLL_M3DIV_M3_WIDTH,
				    CLK_DIVIDER_ONE_BASED);
	अगर (err)
		वापस err;

	/* Output घड़ी dcoclklकरो is the DCO */

	वापस 0;
पूर्ण

अटल पूर्णांक ti_adpll_init_children_adpll_lj(काष्ठा ti_adpll_data *d)
अणु
	पूर्णांक err;

	अगर (d->c->is_type_s)
		वापस 0;

	/* Output clkdcolकरो, gated output of DCO */
	err = ti_adpll_init_gate(d, TI_ADPLL_DCO_GATE, TI_ADPLL_LJ_CLKDCOLDO,
				 "clkdcoldo", d->घड़ीs[TI_ADPLL_DCO].clk,
				 d->regs + ADPLL_CLKCTRL_OFFSET,
				 ADPLL_CLKCTRL_CLKDCOLDOEN, 0);
	अगर (err)
		वापस err;

	/* Internal भागider M2, sources from DCO */
	err = ti_adpll_init_भागider(d, TI_ADPLL_M2, -ENODEV,
				    "m2", d->घड़ीs[TI_ADPLL_DCO].clk,
				    d->regs + ADPLL_M2NDIV_OFFSET,
				    ADPLL_M2NDIV_M2,
				    ADPLL_M2NDIV_M2_ADPLL_LJ_WIDTH,
				    CLK_DIVIDER_ONE_BASED);
	अगर (err)
		वापस err;

	/* Output clkoutlकरो, gated output of M2 */
	err = ti_adpll_init_gate(d, TI_ADPLL_M2_GATE, TI_ADPLL_LJ_CLKOUTLDO,
				 "clkoutldo", d->घड़ीs[TI_ADPLL_M2].clk,
				 d->regs + ADPLL_CLKCTRL_OFFSET,
				 ADPLL_CLKCTRL_CLKOUTLDOEN_ADPLL_LJ,
				 0);
	अगर (err)
		वापस err;

	/* Internal mux, sources from भागider N2 or clkinpulow */
	err = ti_adpll_init_mux(d, TI_ADPLL_BYPASS, "bypass",
				d->घड़ीs[TI_ADPLL_N2].clk,
				d->parent_घड़ीs[TI_ADPLL_CLKINPULOW],
				d->regs + ADPLL_CLKCTRL_OFFSET,
				ADPLL_CLKCTRL_ULOWCLKEN);
	अगर (err)
		वापस err;

	/* Output clkout, sources M2 or bypass */
	err = ti_adpll_init_clkout(d, TI_ADPLL_CLKOUT, TI_ADPLL_S_CLKOUT,
				   ADPLL_CLKCTRL_CLKOUTEN, "clkout",
				   d->घड़ीs[TI_ADPLL_M2].clk,
				   d->घड़ीs[TI_ADPLL_BYPASS].clk);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम ti_adpll_मुक्त_resources(काष्ठा ti_adpll_data *d)
अणु
	पूर्णांक i;

	क्रम (i = TI_ADPLL_M3; i >= 0; i--) अणु
		काष्ठा ti_adpll_घड़ी *ac = &d->घड़ीs[i];

		अगर (!ac || IS_ERR_OR_शून्य(ac->clk))
			जारी;
		अगर (ac->cl)
			clkdev_drop(ac->cl);
		अगर (ac->unरेजिस्टर)
			ac->unरेजिस्टर(ac->clk);
	पूर्ण
पूर्ण

/* MPU PLL manages the lock रेजिस्टर क्रम all PLLs */
अटल व्योम ti_adpll_unlock_all(व्योम __iomem *reg)
अणु
	u32 v;

	v = पढ़ोl_relaxed(reg);
	अगर (v == ADPLL_PLLSS_MMR_LOCK_ENABLED)
		ग_लिखोl_relaxed(ADPLL_PLLSS_MMR_UNLOCK_MAGIC, reg);
पूर्ण

अटल पूर्णांक ti_adpll_init_रेजिस्टरs(काष्ठा ti_adpll_data *d)
अणु
	पूर्णांक रेजिस्टर_offset = 0;

	अगर (d->c->is_type_s) अणु
		रेजिस्टर_offset = 8;
		ti_adpll_unlock_all(d->iobase + ADPLL_PLLSS_MMR_LOCK_OFFSET);
	पूर्ण

	d->regs = d->iobase + रेजिस्टर_offset + ADPLL_PWRCTRL_OFFSET;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_adpll_init_inमाला_दो(काष्ठा ti_adpll_data *d)
अणु
	स्थिर अक्षर *error = "need at least %i inputs";
	काष्ठा clk *घड़ी;
	पूर्णांक nr_inमाला_दो;

	nr_inमाला_दो = of_clk_get_parent_count(d->np);
	अगर (nr_inमाला_दो < d->c->nr_max_inमाला_दो) अणु
		dev_err(d->dev, error, nr_inमाला_दो);
		वापस -EINVAL;
	पूर्ण
	of_clk_parent_fill(d->np, d->parent_names, nr_inमाला_दो);

	घड़ी = devm_clk_get(d->dev, d->parent_names[0]);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "could not get clkinp\n");
		वापस PTR_ERR(घड़ी);
	पूर्ण
	d->parent_घड़ीs[TI_ADPLL_CLKINP] = घड़ी;

	घड़ी = devm_clk_get(d->dev, d->parent_names[1]);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(d->dev, "could not get clkinpulow clock\n");
		वापस PTR_ERR(घड़ी);
	पूर्ण
	d->parent_घड़ीs[TI_ADPLL_CLKINPULOW] = घड़ी;

	अगर (d->c->is_type_s) अणु
		घड़ी =  devm_clk_get(d->dev, d->parent_names[2]);
		अगर (IS_ERR(घड़ी)) अणु
			dev_err(d->dev, "could not get clkinphif clock\n");
			वापस PTR_ERR(घड़ी);
		पूर्ण
		d->parent_घड़ीs[TI_ADPLL_CLKINPHIF] = घड़ी;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ti_adpll_platक्रमm_data ti_adpll_type_s = अणु
	.is_type_s = true,
	.nr_max_inमाला_दो = MAX_ADPLL_INPUTS,
	.nr_max_outमाला_दो = MAX_ADPLL_OUTPUTS,
	.output_index = TI_ADPLL_S_DCOCLKLDO,
पूर्ण;

अटल स्थिर काष्ठा ti_adpll_platक्रमm_data ti_adpll_type_lj = अणु
	.is_type_s = false,
	.nr_max_inमाला_दो = MAX_ADPLL_INPUTS - 1,
	.nr_max_outमाला_दो = MAX_ADPLL_OUTPUTS - 1,
	.output_index = -EINVAL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_adpll_match[] = अणु
	अणु .compatible = "ti,dm814-adpll-s-clock", &ti_adpll_type_s पूर्ण,
	अणु .compatible = "ti,dm814-adpll-lj-clock", &ti_adpll_type_lj पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_adpll_match);

अटल पूर्णांक ti_adpll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा ti_adpll_platक्रमm_data *pdata;
	काष्ठा ti_adpll_data *d;
	काष्ठा resource *res;
	पूर्णांक err;

	match = of_match_device(ti_adpll_match, dev);
	अगर (match)
		pdata = match->data;
	अन्यथा
		वापस -ENODEV;

	d = devm_kzalloc(dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;
	d->dev = dev;
	d->np = node;
	d->c = pdata;
	dev_set_drvdata(d->dev, d);
	spin_lock_init(&d->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	d->pa = res->start;

	d->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(d->iobase)) अणु
		dev_err(dev, "could not get IO base: %li\n",
			PTR_ERR(d->iobase));
		वापस PTR_ERR(d->iobase);
	पूर्ण

	err = ti_adpll_init_रेजिस्टरs(d);
	अगर (err)
		वापस err;

	err = ti_adpll_init_inमाला_दो(d);
	अगर (err)
		वापस err;

	d->घड़ीs = devm_kसुस्मृति(d->dev,
				 TI_ADPLL_NR_CLOCKS,
				 माप(काष्ठा ti_adpll_घड़ी),
				 GFP_KERNEL);
	अगर (!d->घड़ीs)
		वापस -ENOMEM;

	err = ti_adpll_init_dco(d);
	अगर (err) अणु
		dev_err(dev, "could not register dco: %i\n", err);
		जाओ मुक्त;
	पूर्ण

	err = ti_adpll_init_children_adpll_s(d);
	अगर (err)
		जाओ मुक्त;
	err = ti_adpll_init_children_adpll_lj(d);
	अगर (err)
		जाओ मुक्त;

	err = of_clk_add_provider(d->np, of_clk_src_onecell_get, &d->outमाला_दो);
	अगर (err)
		जाओ मुक्त;

	वापस 0;

मुक्त:
	WARN_ON(1);
	ti_adpll_मुक्त_resources(d);

	वापस err;
पूर्ण

अटल पूर्णांक ti_adpll_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_adpll_data *d = dev_get_drvdata(&pdev->dev);

	ti_adpll_मुक्त_resources(d);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_adpll_driver = अणु
	.driver = अणु
		.name = "ti-adpll",
		.of_match_table = ti_adpll_match,
	पूर्ण,
	.probe = ti_adpll_probe,
	.हटाओ = ti_adpll_हटाओ,
पूर्ण;

अटल पूर्णांक __init ti_adpll_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ti_adpll_driver);
पूर्ण
core_initcall(ti_adpll_init);

अटल व्योम __निकास ti_adpll_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ti_adpll_driver);
पूर्ण
module_निकास(ti_adpll_निकास);

MODULE_DESCRIPTION("Clock driver for dm814x ADPLL");
MODULE_ALIAS("platform:dm814-adpll-clock");
MODULE_AUTHOR("Tony LIndgren <tony@atomide.com>");
MODULE_LICENSE("GPL v2");
