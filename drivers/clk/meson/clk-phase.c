<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "clk-phase.h"

#घोषणा phase_step(_width) (360 / (1 << (_width)))

अटल अंतरभूत काष्ठा meson_clk_phase_data *
meson_clk_phase_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_phase_data *)clk->data;
पूर्ण

अटल पूर्णांक meson_clk_degrees_from_val(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक width)
अणु
	वापस phase_step(width) * val;
पूर्ण

अटल अचिन्हित पूर्णांक meson_clk_degrees_to_val(पूर्णांक degrees, अचिन्हित पूर्णांक width)
अणु
	अचिन्हित पूर्णांक val = DIV_ROUND_CLOSEST(degrees, phase_step(width));

	/*
	 * This last calculation is here क्रम हालs when degrees is rounded
	 * to 360, in which हाल val == (1 << width).
	 */
	वापस val % (1 << width);
पूर्ण

अटल पूर्णांक meson_clk_phase_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_phase_data *phase = meson_clk_phase_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_parm_पढ़ो(clk->map, &phase->ph);

	वापस meson_clk_degrees_from_val(val, phase->ph.width);
पूर्ण

अटल पूर्णांक meson_clk_phase_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_phase_data *phase = meson_clk_phase_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_clk_degrees_to_val(degrees, phase->ph.width);
	meson_parm_ग_लिखो(clk->map, &phase->ph, val);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_clk_phase_ops = अणु
	.get_phase	= meson_clk_phase_get_phase,
	.set_phase	= meson_clk_phase_set_phase,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_phase_ops);

/*
 * This is a special घड़ी क्रम the audio controller.
 * The phase of mst_sclk घड़ी output can be controlled independently
 * क्रम the outside world (ph0), the tdmout (ph1) and tdmin (ph2).
 * Controlling these 3 phases as just one makes things simpler and
 * give the same घड़ी view to all the element on the i2s bus.
 * If necessary, we can still control the phase in the tdm block
 * which makes these independent control redundant.
 */
अटल अंतरभूत काष्ठा meson_clk_triphase_data *
meson_clk_triphase_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_triphase_data *)clk->data;
पूर्ण

अटल पूर्णांक meson_clk_triphase_sync(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_triphase_data *tph = meson_clk_triphase_data(clk);
	अचिन्हित पूर्णांक val;

	/* Get phase 0 and sync it to phase 1 and 2 */
	val = meson_parm_पढ़ो(clk->map, &tph->ph0);
	meson_parm_ग_लिखो(clk->map, &tph->ph1, val);
	meson_parm_ग_लिखो(clk->map, &tph->ph2, val);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_clk_triphase_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_triphase_data *tph = meson_clk_triphase_data(clk);
	अचिन्हित पूर्णांक val;

	/* Phase are in sync, पढ़ोing phase 0 is enough */
	val = meson_parm_पढ़ो(clk->map, &tph->ph0);

	वापस meson_clk_degrees_from_val(val, tph->ph0.width);
पूर्ण

अटल पूर्णांक meson_clk_triphase_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_triphase_data *tph = meson_clk_triphase_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_clk_degrees_to_val(degrees, tph->ph0.width);
	meson_parm_ग_लिखो(clk->map, &tph->ph0, val);
	meson_parm_ग_लिखो(clk->map, &tph->ph1, val);
	meson_parm_ग_लिखो(clk->map, &tph->ph2, val);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_clk_triphase_ops = अणु
	.init		= meson_clk_triphase_sync,
	.get_phase	= meson_clk_triphase_get_phase,
	.set_phase	= meson_clk_triphase_set_phase,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_triphase_ops);

/*
 * This is a special घड़ी क्रम the audio controller.
 * This drive a bit घड़ी inverter क्रम which the
 * opposite value of the inverter bit needs to be manually
 * set पूर्णांकo another bit
 */
अटल अंतरभूत काष्ठा meson_sclk_ws_inv_data *
meson_sclk_ws_inv_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_sclk_ws_inv_data *)clk->data;
पूर्ण

अटल पूर्णांक meson_sclk_ws_inv_sync(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_ws_inv_data *tph = meson_sclk_ws_inv_data(clk);
	अचिन्हित पूर्णांक val;

	/* Get phase and sync the inverted value to ws */
	val = meson_parm_पढ़ो(clk->map, &tph->ph);
	meson_parm_ग_लिखो(clk->map, &tph->ws, val ? 0 : 1);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_sclk_ws_inv_get_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_ws_inv_data *tph = meson_sclk_ws_inv_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_parm_पढ़ो(clk->map, &tph->ph);

	वापस meson_clk_degrees_from_val(val, tph->ph.width);
पूर्ण

अटल पूर्णांक meson_sclk_ws_inv_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_ws_inv_data *tph = meson_sclk_ws_inv_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_clk_degrees_to_val(degrees, tph->ph.width);
	meson_parm_ग_लिखो(clk->map, &tph->ph, val);
	meson_parm_ग_लिखो(clk->map, &tph->ws, val ? 0 : 1);
	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_sclk_ws_inv_ops = अणु
	.init		= meson_sclk_ws_inv_sync,
	.get_phase	= meson_sclk_ws_inv_get_phase,
	.set_phase	= meson_sclk_ws_inv_set_phase,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_sclk_ws_inv_ops);


MODULE_DESCRIPTION("Amlogic phase driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
