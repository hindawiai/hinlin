<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "ddk750_chip.h"
#समावेश "ddk750_reg.h"
#समावेश "ddk750_power.h"

व्योम ddk750_set_dpms(क्रमागत dpms state)
अणु
	अचिन्हित पूर्णांक value;

	अगर (sm750_get_chip_type() == SM750LE) अणु
		value = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_DPMS_MASK;
		value |= (state << CRT_DISPLAY_CTRL_DPMS_SHIFT);
		poke32(CRT_DISPLAY_CTRL, value);
	पूर्ण अन्यथा अणु
		value = peek32(SYSTEM_CTRL);
		value = (value & ~SYSTEM_CTRL_DPMS_MASK) | state;
		poke32(SYSTEM_CTRL, value);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक get_घातer_mode(व्योम)
अणु
	अगर (sm750_get_chip_type() == SM750LE)
		वापस 0;
	वापस peek32(POWER_MODE_CTRL) & POWER_MODE_CTRL_MODE_MASK;
पूर्ण

/*
 * SM50x can operate in one of three modes: 0, 1 or Sleep.
 * On hardware reset, घातer mode 0 is शेष.
 */
व्योम sm750_set_घातer_mode(अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक ctrl = 0;

	ctrl = peek32(POWER_MODE_CTRL) & ~POWER_MODE_CTRL_MODE_MASK;

	अगर (sm750_get_chip_type() == SM750LE)
		वापस;

	चयन (mode) अणु
	हाल POWER_MODE_CTRL_MODE_MODE0:
		ctrl |= POWER_MODE_CTRL_MODE_MODE0;
		अवरोध;

	हाल POWER_MODE_CTRL_MODE_MODE1:
		ctrl |= POWER_MODE_CTRL_MODE_MODE1;
		अवरोध;

	हाल POWER_MODE_CTRL_MODE_SLEEP:
		ctrl |= POWER_MODE_CTRL_MODE_SLEEP;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Set up other fields in Power Control Register */
	अगर (mode == POWER_MODE_CTRL_MODE_SLEEP) अणु
		ctrl &= ~POWER_MODE_CTRL_OSC_INPUT;
#अगर_घोषित VALIDATION_CHIP
		ctrl &= ~POWER_MODE_CTRL_336CLK;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		ctrl |= POWER_MODE_CTRL_OSC_INPUT;
#अगर_घोषित VALIDATION_CHIP
		ctrl |= POWER_MODE_CTRL_336CLK;
#पूर्ण_अगर
	पूर्ण

	/* Program new घातer mode. */
	poke32(POWER_MODE_CTRL, ctrl);
पूर्ण

व्योम sm750_set_current_gate(अचिन्हित पूर्णांक gate)
अणु
	अगर (get_घातer_mode() == POWER_MODE_CTRL_MODE_MODE1)
		poke32(MODE1_GATE, gate);
	अन्यथा
		poke32(MODE0_GATE, gate);
पूर्ण

/*
 * This function enable/disable the 2D engine.
 */
व्योम sm750_enable_2d_engine(अचिन्हित पूर्णांक enable)
अणु
	u32 gate;

	gate = peek32(CURRENT_GATE);
	अगर (enable)
		gate |= (CURRENT_GATE_DE | CURRENT_GATE_CSC);
	अन्यथा
		gate &= ~(CURRENT_GATE_DE | CURRENT_GATE_CSC);

	sm750_set_current_gate(gate);
पूर्ण

व्योम sm750_enable_dma(अचिन्हित पूर्णांक enable)
अणु
	u32 gate;

	/* Enable DMA Gate */
	gate = peek32(CURRENT_GATE);
	अगर (enable)
		gate |= CURRENT_GATE_DMA;
	अन्यथा
		gate &= ~CURRENT_GATE_DMA;

	sm750_set_current_gate(gate);
पूर्ण

/*
 * This function enable/disable the GPIO Engine
 */
व्योम sm750_enable_gpio(अचिन्हित पूर्णांक enable)
अणु
	u32 gate;

	/* Enable GPIO Gate */
	gate = peek32(CURRENT_GATE);
	अगर (enable)
		gate |= CURRENT_GATE_GPIO;
	अन्यथा
		gate &= ~CURRENT_GATE_GPIO;

	sm750_set_current_gate(gate);
पूर्ण

/*
 * This function enable/disable the I2C Engine
 */
व्योम sm750_enable_i2c(अचिन्हित पूर्णांक enable)
अणु
	u32 gate;

	/* Enable I2C Gate */
	gate = peek32(CURRENT_GATE);
	अगर (enable)
		gate |= CURRENT_GATE_I2C;
	अन्यथा
		gate &= ~CURRENT_GATE_I2C;

	sm750_set_current_gate(gate);
पूर्ण
