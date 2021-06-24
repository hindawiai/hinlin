<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Structures used by ASPEED घड़ी drivers
 *
 * Copyright 2019 IBM Corp.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>

काष्ठा clk_भाग_प्रकारable;
काष्ठा regmap;

/**
 * काष्ठा aspeed_gate_data - Aspeed gated घड़ीs
 * @घड़ी_idx: bit used to gate this घड़ी in the घड़ी रेजिस्टर
 * @reset_idx: bit used to reset this IP in the reset रेजिस्टर. -1 अगर no
 *             reset is required when enabling the घड़ी
 * @name: the घड़ी name
 * @parent_name: the name of the parent घड़ी
 * @flags: standard घड़ी framework flags
 */
काष्ठा aspeed_gate_data अणु
	u8		घड़ी_idx;
	s8		reset_idx;
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*parent_name;
	अचिन्हित दीर्घ	flags;
पूर्ण;

/**
 * काष्ठा aspeed_clk_gate - Aspeed specअगरic clk_gate काष्ठाure
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर controlling gate
 * @घड़ी_idx:	bit used to gate this घड़ी in the घड़ी रेजिस्टर
 * @reset_idx:	bit used to reset this IP in the reset रेजिस्टर. -1 अगर no
 *		reset is required when enabling the घड़ी
 * @flags:	hardware-specअगरic flags
 * @lock:	रेजिस्टर lock
 *
 * Some of the घड़ीs in the Aspeed SoC must be put in reset beक्रमe enabling.
 * This modअगरied version of clk_gate allows an optional reset bit to be
 * specअगरied.
 */
काष्ठा aspeed_clk_gate अणु
	काष्ठा clk_hw	hw;
	काष्ठा regmap	*map;
	u8		घड़ी_idx;
	s8		reset_idx;
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_aspeed_clk_gate(_hw) container_of(_hw, काष्ठा aspeed_clk_gate, hw)

/**
 * काष्ठा aspeed_reset - Aspeed reset controller
 * @map: regmap to access the containing प्रणाली controller
 * @rcdev: reset controller device
 */
काष्ठा aspeed_reset अणु
	काष्ठा regmap			*map;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

#घोषणा to_aspeed_reset(p) container_of((p), काष्ठा aspeed_reset, rcdev)

/**
 * काष्ठा aspeed_clk_soc_data - Aspeed SoC specअगरic भागisor inक्रमmation
 * @भाग_प्रकारable: Common भागider lookup table
 * @eclk_भाग_प्रकारable: Divider lookup table क्रम ECLK
 * @mac_भाग_प्रकारable: Divider lookup table क्रम MAC (Ethernet) घड़ीs
 * @calc_pll: Callback to maculate common PLL settings
 */
काष्ठा aspeed_clk_soc_data अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
	स्थिर काष्ठा clk_भाग_प्रकारable *eclk_भाग_प्रकारable;
	स्थिर काष्ठा clk_भाग_प्रकारable *mac_भाग_प्रकारable;
	काष्ठा clk_hw *(*calc_pll)(स्थिर अक्षर *name, u32 val);
पूर्ण;
