<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, 2017-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश "gdsc.h"

#घोषणा PWR_ON_MASK		BIT(31)
#घोषणा EN_REST_WAIT_MASK	GENMASK_ULL(23, 20)
#घोषणा EN_FEW_WAIT_MASK	GENMASK_ULL(19, 16)
#घोषणा CLK_DIS_WAIT_MASK	GENMASK_ULL(15, 12)
#घोषणा SW_OVERRIDE_MASK	BIT(2)
#घोषणा HW_CONTROL_MASK		BIT(1)
#घोषणा SW_COLLAPSE_MASK	BIT(0)
#घोषणा GMEM_CLAMP_IO_MASK	BIT(0)
#घोषणा GMEM_RESET_MASK		BIT(4)

/* CFG_GDSCR */
#घोषणा GDSC_POWER_UP_COMPLETE		BIT(16)
#घोषणा GDSC_POWER_DOWN_COMPLETE	BIT(15)
#घोषणा GDSC_RETAIN_FF_ENABLE		BIT(11)
#घोषणा CFG_GDSCR_OFFSET		0x4

/* Wait 2^n CXO cycles between all states. Here, n=2 (4 cycles). */
#घोषणा EN_REST_WAIT_VAL	(0x2 << 20)
#घोषणा EN_FEW_WAIT_VAL		(0x8 << 16)
#घोषणा CLK_DIS_WAIT_VAL	(0x2 << 12)

#घोषणा RETAIN_MEM		BIT(14)
#घोषणा RETAIN_PERIPH		BIT(13)

#घोषणा TIMEOUT_US		500

#घोषणा करोमुख्य_to_gdsc(करोमुख्य) container_of(करोमुख्य, काष्ठा gdsc, pd)

क्रमागत gdsc_status अणु
	GDSC_OFF,
	GDSC_ON
पूर्ण;

/* Returns 1 अगर GDSC status is status, 0 अगर not, and < 0 on error */
अटल पूर्णांक gdsc_check_status(काष्ठा gdsc *sc, क्रमागत gdsc_status status)
अणु
	अचिन्हित पूर्णांक reg;
	u32 val;
	पूर्णांक ret;

	अगर (sc->flags & POLL_CFG_GDSCR)
		reg = sc->gdscr + CFG_GDSCR_OFFSET;
	अन्यथा अगर (sc->gds_hw_ctrl)
		reg = sc->gds_hw_ctrl;
	अन्यथा
		reg = sc->gdscr;

	ret = regmap_पढ़ो(sc->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (sc->flags & POLL_CFG_GDSCR) अणु
		चयन (status) अणु
		हाल GDSC_ON:
			वापस !!(val & GDSC_POWER_UP_COMPLETE);
		हाल GDSC_OFF:
			वापस !!(val & GDSC_POWER_DOWN_COMPLETE);
		पूर्ण
	पूर्ण

	चयन (status) अणु
	हाल GDSC_ON:
		वापस !!(val & PWR_ON_MASK);
	हाल GDSC_OFF:
		वापस !(val & PWR_ON_MASK);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gdsc_hwctrl(काष्ठा gdsc *sc, bool en)
अणु
	u32 val = en ? HW_CONTROL_MASK : 0;

	वापस regmap_update_bits(sc->regmap, sc->gdscr, HW_CONTROL_MASK, val);
पूर्ण

अटल पूर्णांक gdsc_poll_status(काष्ठा gdsc *sc, क्रमागत gdsc_status status)
अणु
	kसमय_प्रकार start;

	start = kसमय_get();
	करो अणु
		अगर (gdsc_check_status(sc, status))
			वापस 0;
	पूर्ण जबतक (kसमय_us_delta(kसमय_get(), start) < TIMEOUT_US);

	अगर (gdsc_check_status(sc, status))
		वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gdsc_toggle_logic(काष्ठा gdsc *sc, क्रमागत gdsc_status status)
अणु
	पूर्णांक ret;
	u32 val = (status == GDSC_ON) ? 0 : SW_COLLAPSE_MASK;

	अगर (status == GDSC_ON && sc->rsupply) अणु
		ret = regulator_enable(sc->rsupply);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = regmap_update_bits(sc->regmap, sc->gdscr, SW_COLLAPSE_MASK, val);
	अगर (ret)
		वापस ret;

	/* If disabling votable gdscs, करोn't poll on status */
	अगर ((sc->flags & VOTABLE) && status == GDSC_OFF) अणु
		/*
		 * Add a लघु delay here to ensure that an enable
		 * right after it was disabled करोes not put it in an
		 * unknown state
		 */
		udelay(TIMEOUT_US);
		वापस 0;
	पूर्ण

	अगर (sc->gds_hw_ctrl) अणु
		/*
		 * The gds hw controller निश्चितs/de-निश्चितs the status bit soon
		 * after it receives a घातer on/off request from a master.
		 * The controller then takes around 8 xo cycles to start its
		 * पूर्णांकernal state machine and update the status bit. During
		 * this समय, the status bit करोes not reflect the true status
		 * of the core.
		 * Add a delay of 1 us between writing to the SW_COLLAPSE bit
		 * and polling the status bit.
		 */
		udelay(1);
	पूर्ण

	ret = gdsc_poll_status(sc, status);
	WARN(ret, "%s status stuck at 'o%s'", sc->pd.name, status ? "ff" : "n");

	अगर (!ret && status == GDSC_OFF && sc->rsupply) अणु
		ret = regulator_disable(sc->rsupply);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक gdsc_deनिश्चित_reset(काष्ठा gdsc *sc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sc->reset_count; i++)
		sc->rcdev->ops->deनिश्चित(sc->rcdev, sc->resets[i]);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gdsc_निश्चित_reset(काष्ठा gdsc *sc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sc->reset_count; i++)
		sc->rcdev->ops->निश्चित(sc->rcdev, sc->resets[i]);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gdsc_क्रमce_mem_on(काष्ठा gdsc *sc)
अणु
	पूर्णांक i;
	u32 mask = RETAIN_MEM;

	अगर (!(sc->flags & NO_RET_PERIPH))
		mask |= RETAIN_PERIPH;

	क्रम (i = 0; i < sc->cxc_count; i++)
		regmap_update_bits(sc->regmap, sc->cxcs[i], mask, mask);
पूर्ण

अटल अंतरभूत व्योम gdsc_clear_mem_on(काष्ठा gdsc *sc)
अणु
	पूर्णांक i;
	u32 mask = RETAIN_MEM;

	अगर (!(sc->flags & NO_RET_PERIPH))
		mask |= RETAIN_PERIPH;

	क्रम (i = 0; i < sc->cxc_count; i++)
		regmap_update_bits(sc->regmap, sc->cxcs[i], mask, 0);
पूर्ण

अटल अंतरभूत व्योम gdsc_deनिश्चित_clamp_io(काष्ठा gdsc *sc)
अणु
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_CLAMP_IO_MASK, 0);
पूर्ण

अटल अंतरभूत व्योम gdsc_निश्चित_clamp_io(काष्ठा gdsc *sc)
अणु
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_CLAMP_IO_MASK, 1);
पूर्ण

अटल अंतरभूत व्योम gdsc_निश्चित_reset_aon(काष्ठा gdsc *sc)
अणु
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_RESET_MASK, 1);
	udelay(1);
	regmap_update_bits(sc->regmap, sc->clamp_io_ctrl,
			   GMEM_RESET_MASK, 0);
पूर्ण

अटल व्योम gdsc_retain_ff_on(काष्ठा gdsc *sc)
अणु
	u32 mask = GDSC_RETAIN_FF_ENABLE;

	regmap_update_bits(sc->regmap, sc->gdscr, mask, mask);
पूर्ण

अटल पूर्णांक gdsc_enable(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा gdsc *sc = करोमुख्य_to_gdsc(करोमुख्य);
	पूर्णांक ret;

	अगर (sc->pwrsts == PWRSTS_ON)
		वापस gdsc_deनिश्चित_reset(sc);

	अगर (sc->flags & SW_RESET) अणु
		gdsc_निश्चित_reset(sc);
		udelay(1);
		gdsc_deनिश्चित_reset(sc);
	पूर्ण

	अगर (sc->flags & CLAMP_IO) अणु
		अगर (sc->flags & AON_RESET)
			gdsc_निश्चित_reset_aon(sc);
		gdsc_deनिश्चित_clamp_io(sc);
	पूर्ण

	ret = gdsc_toggle_logic(sc, GDSC_ON);
	अगर (ret)
		वापस ret;

	अगर (sc->pwrsts & PWRSTS_OFF)
		gdsc_क्रमce_mem_on(sc);

	/*
	 * If घड़ीs to this घातer करोमुख्य were alपढ़ोy on, they will take an
	 * additional 4 घड़ी cycles to re-enable after the घातer करोमुख्य is
	 * enabled. Delay to account क्रम this. A delay is also needed to ensure
	 * घड़ीs are not enabled within 400ns of enabling घातer to the
	 * memories.
	 */
	udelay(1);

	/* Turn on HW trigger mode अगर supported */
	अगर (sc->flags & HW_CTRL) अणु
		ret = gdsc_hwctrl(sc, true);
		अगर (ret)
			वापस ret;
		/*
		 * Wait क्रम the GDSC to go through a घातer करोwn and
		 * up cycle.  In हाल a firmware ends up polling status
		 * bits क्रम the gdsc, it might पढ़ो an 'on' status beक्रमe
		 * the GDSC can finish the घातer cycle.
		 * We रुको 1us beक्रमe वापसing to ensure the firmware
		 * can't immediately poll the status bits.
		 */
		udelay(1);
	पूर्ण

	अगर (sc->flags & RETAIN_FF_ENABLE)
		gdsc_retain_ff_on(sc);

	वापस 0;
पूर्ण

अटल पूर्णांक gdsc_disable(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा gdsc *sc = करोमुख्य_to_gdsc(करोमुख्य);
	पूर्णांक ret;

	अगर (sc->pwrsts == PWRSTS_ON)
		वापस gdsc_निश्चित_reset(sc);

	/* Turn off HW trigger mode अगर supported */
	अगर (sc->flags & HW_CTRL) अणु
		ret = gdsc_hwctrl(sc, false);
		अगर (ret < 0)
			वापस ret;
		/*
		 * Wait क्रम the GDSC to go through a घातer करोwn and
		 * up cycle.  In हाल we end up polling status
		 * bits क्रम the gdsc beक्रमe the घातer cycle is completed
		 * it might पढ़ो an 'on' status wrongly.
		 */
		udelay(1);

		ret = gdsc_poll_status(sc, GDSC_ON);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sc->pwrsts & PWRSTS_OFF)
		gdsc_clear_mem_on(sc);

	ret = gdsc_toggle_logic(sc, GDSC_OFF);
	अगर (ret)
		वापस ret;

	अगर (sc->flags & CLAMP_IO)
		gdsc_निश्चित_clamp_io(sc);

	वापस 0;
पूर्ण

अटल पूर्णांक gdsc_init(काष्ठा gdsc *sc)
अणु
	u32 mask, val;
	पूर्णांक on, ret;

	/*
	 * Disable HW trigger: collapse/restore occur based on रेजिस्टरs ग_लिखोs.
	 * Disable SW override: Use hardware state-machine क्रम sequencing.
	 * Configure रुको समय between states.
	 */
	mask = HW_CONTROL_MASK | SW_OVERRIDE_MASK |
	       EN_REST_WAIT_MASK | EN_FEW_WAIT_MASK | CLK_DIS_WAIT_MASK;
	val = EN_REST_WAIT_VAL | EN_FEW_WAIT_VAL | CLK_DIS_WAIT_VAL;
	ret = regmap_update_bits(sc->regmap, sc->gdscr, mask, val);
	अगर (ret)
		वापस ret;

	/* Force gdsc ON अगर only ON state is supported */
	अगर (sc->pwrsts == PWRSTS_ON) अणु
		ret = gdsc_toggle_logic(sc, GDSC_ON);
		अगर (ret)
			वापस ret;
	पूर्ण

	on = gdsc_check_status(sc, GDSC_ON);
	अगर (on < 0)
		वापस on;

	/*
	 * Votable GDSCs can be ON due to Vote from other masters.
	 * If a Votable GDSC is ON, make sure we have a Vote.
	 */
	अगर ((sc->flags & VOTABLE) && on)
		gdsc_enable(&sc->pd);

	/*
	 * Make sure the retain bit is set अगर the GDSC is alपढ़ोy on, otherwise
	 * we end up turning off the GDSC and destroying all the रेजिस्टर
	 * contents that we thought we were saving.
	 */
	अगर ((sc->flags & RETAIN_FF_ENABLE) && on)
		gdsc_retain_ff_on(sc);

	/* If ALWAYS_ON GDSCs are not ON, turn them ON */
	अगर (sc->flags & ALWAYS_ON) अणु
		अगर (!on)
			gdsc_enable(&sc->pd);
		on = true;
		sc->pd.flags |= GENPD_FLAG_ALWAYS_ON;
	पूर्ण

	अगर (on || (sc->pwrsts & PWRSTS_RET))
		gdsc_क्रमce_mem_on(sc);
	अन्यथा
		gdsc_clear_mem_on(sc);

	अगर (!sc->pd.घातer_off)
		sc->pd.घातer_off = gdsc_disable;
	अगर (!sc->pd.घातer_on)
		sc->pd.घातer_on = gdsc_enable;
	pm_genpd_init(&sc->pd, शून्य, !on);

	वापस 0;
पूर्ण

पूर्णांक gdsc_रेजिस्टर(काष्ठा gdsc_desc *desc,
		  काष्ठा reset_controller_dev *rcdev, काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret;
	काष्ठा genpd_onecell_data *data;
	काष्ठा device *dev = desc->dev;
	काष्ठा gdsc **scs = desc->scs;
	माप_प्रकार num = desc->num;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->करोमुख्यs = devm_kसुस्मृति(dev, num, माप(*data->करोमुख्यs),
				     GFP_KERNEL);
	अगर (!data->करोमुख्यs)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		अगर (!scs[i] || !scs[i]->supply)
			जारी;

		scs[i]->rsupply = devm_regulator_get(dev, scs[i]->supply);
		अगर (IS_ERR(scs[i]->rsupply))
			वापस PTR_ERR(scs[i]->rsupply);
	पूर्ण

	data->num_करोमुख्यs = num;
	क्रम (i = 0; i < num; i++) अणु
		अगर (!scs[i])
			जारी;
		scs[i]->regmap = regmap;
		scs[i]->rcdev = rcdev;
		ret = gdsc_init(scs[i]);
		अगर (ret)
			वापस ret;
		data->करोमुख्यs[i] = &scs[i]->pd;
	पूर्ण

	/* Add subकरोमुख्यs */
	क्रम (i = 0; i < num; i++) अणु
		अगर (!scs[i])
			जारी;
		अगर (scs[i]->parent)
			pm_genpd_add_subकरोमुख्य(scs[i]->parent, &scs[i]->pd);
	पूर्ण

	वापस of_genpd_add_provider_onecell(dev->of_node, data);
पूर्ण

व्योम gdsc_unरेजिस्टर(काष्ठा gdsc_desc *desc)
अणु
	पूर्णांक i;
	काष्ठा device *dev = desc->dev;
	काष्ठा gdsc **scs = desc->scs;
	माप_प्रकार num = desc->num;

	/* Remove subकरोमुख्यs */
	क्रम (i = 0; i < num; i++) अणु
		अगर (!scs[i])
			जारी;
		अगर (scs[i]->parent)
			pm_genpd_हटाओ_subकरोमुख्य(scs[i]->parent, &scs[i]->pd);
	पूर्ण
	of_genpd_del_provider(dev->of_node);
पूर्ण

/*
 * On SDM845+ the GPU GX करोमुख्य is *almost* entirely controlled by the GMU
 * running in the CX करोमुख्य so the CPU करोesn't need to know anything about the
 * GX करोमुख्य EXCEPT....
 *
 * Hardware स्थिरraपूर्णांकs dictate that the GX be घातered करोwn beक्रमe the CX. If
 * the GMU crashes it could leave the GX on. In order to successfully bring back
 * the device the CPU needs to disable the GX headचयन. There being no sane
 * way to reach in and touch that रेजिस्टर from deep inside the GPU driver we
 * need to set up the infraकाष्ठाure to be able to ensure that the GPU can
 * ensure that the GX is off during this super special हाल. We करो this by
 * defining a GX gdsc with a dummy enable function and a "default" disable
 * function.
 *
 * This allows us to attach with genpd_dev_pm_attach_by_name() in the GPU
 * driver. During घातer up, nothing will happen from the CPU (and the GMU will
 * घातer up normally but during घातer करोwn this will ensure that the GX करोमुख्य
 * is *really* off - this gives us a semi standard way of करोing what we need.
 */
पूर्णांक gdsc_gx_करो_nothing_enable(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	/* Do nothing but give genpd the impression that we were successful */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gdsc_gx_करो_nothing_enable);
