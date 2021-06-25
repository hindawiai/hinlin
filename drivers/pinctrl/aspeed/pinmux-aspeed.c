<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (C) 2019 IBM Corp. */

/* Pieces to enable drivers to implement the .set callback */

#समावेश "pinmux-aspeed.h"

अटल स्थिर अक्षर *स्थिर aspeed_pinmux_ips[] = अणु
	[ASPEED_IP_SCU] = "SCU",
	[ASPEED_IP_GFX] = "GFX",
	[ASPEED_IP_LPC] = "LPC",
पूर्ण;

अटल अंतरभूत व्योम aspeed_sig_desc_prपूर्णांक_val(
		स्थिर काष्ठा aspeed_sig_desc *desc, bool enable, u32 rv)
अणु
	pr_debug("Want %s%X[0x%08X]=0x%X, got 0x%X from 0x%08X\n",
			aspeed_pinmux_ips[desc->ip], desc->reg,
			desc->mask, enable ? desc->enable : desc->disable,
			(rv & desc->mask) >> __ffs(desc->mask), rv);
पूर्ण

/**
 * aspeed_sig_desc_eval() - Query the enabled or disabled state of a संकेत
 * descriptor.
 *
 * @desc: The संकेत descriptor of पूर्णांकerest
 * @enabled: True to query the enabled state, false to query disabled state
 * @map: The IP block's regmap instance
 *
 * Return: 1 अगर the descriptor's bitfield is configured to the state
 * selected by @enabled, 0 अगर not, and less than zero अगर an unrecoverable
 * failure occurred
 *
 * Evaluation of descriptor state is non-trivial in that it is not a binary
 * outcome: The bitfields can be greater than one bit in size and thus can take
 * a value that is neither the enabled nor disabled state recorded in the
 * descriptor (typically this means a dअगरferent function to the one of पूर्णांकerest
 * is enabled). Thus we must explicitly test क्रम either condition as required.
 */
पूर्णांक aspeed_sig_desc_eval(स्थिर काष्ठा aspeed_sig_desc *desc,
			 bool enabled, काष्ठा regmap *map)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक raw;
	u32 want;

	अगर (!map)
		वापस -ENODEV;

	ret = regmap_पढ़ो(map, desc->reg, &raw);
	अगर (ret)
		वापस ret;

	aspeed_sig_desc_prपूर्णांक_val(desc, enabled, raw);
	want = enabled ? desc->enable : desc->disable;

	वापस ((raw & desc->mask) >> __ffs(desc->mask)) == want;
पूर्ण

/**
 * Query the enabled or disabled state क्रम a mux function's संकेत on a pin
 *
 * @ctx: The driver context क्रम the pinctrl IP
 * @expr: An expression controlling the संकेत क्रम a mux function on a pin
 * @enabled: True to query the enabled state, false to query disabled state
 *
 * Return: 1 अगर the expression composed by @enabled evaluates true, 0 अगर not,
 * and less than zero अगर an unrecoverable failure occurred.
 *
 * A mux function is enabled or disabled अगर the function's संकेत expression
 * क्रम each pin in the function's pin group evaluates true क्रम the desired
 * state. An संकेत expression evaluates true अगर all of its associated संकेत
 * descriptors evaluate true क्रम the desired state.
 *
 * If an expression's state is described by more than one bit, either through
 * multi-bit bitfields in a single संकेत descriptor or through multiple संकेत
 * descriptors of a single bit then it is possible क्रम the expression to be in
 * neither the enabled nor disabled state. Thus we must explicitly test क्रम
 * either condition as required.
 */
पूर्णांक aspeed_sig_expr_eval(काष्ठा aspeed_pinmux_data *ctx,
			 स्थिर काष्ठा aspeed_sig_expr *expr, bool enabled)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (ctx->ops->eval)
		वापस ctx->ops->eval(ctx, expr, enabled);

	क्रम (i = 0; i < expr->ndescs; i++) अणु
		स्थिर काष्ठा aspeed_sig_desc *desc = &expr->descs[i];

		ret = aspeed_sig_desc_eval(desc, enabled, ctx->maps[desc->ip]);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	वापस 1;
पूर्ण
