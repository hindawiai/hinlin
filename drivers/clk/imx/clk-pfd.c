<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_pfd - IMX PFD घड़ी
 * @hw:		घड़ी source
 * @reg:	PFD रेजिस्टर address
 * @idx:	the index of PFD encoded in the रेजिस्टर
 *
 * PFD घड़ी found on i.MX6 series.  Each रेजिस्टर क्रम PFD has 4 clk_pfd
 * data encoded, and member idx is used to specअगरy the one.  And each
 * रेजिस्टर has SET, CLR and TOG रेजिस्टरs at offset 0x4 0x8 and 0xc.
 */
काष्ठा clk_pfd अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		idx;
पूर्ण;

#घोषणा to_clk_pfd(_hw) container_of(_hw, काष्ठा clk_pfd, hw)

#घोषणा SET	0x4
#घोषणा CLR	0x8
#घोषणा OTG	0xc

अटल पूर्णांक clk_pfd_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfd *pfd = to_clk_pfd(hw);

	ग_लिखोl_relaxed(1 << ((pfd->idx + 1) * 8 - 1), pfd->reg + CLR);

	वापस 0;
पूर्ण

अटल व्योम clk_pfd_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfd *pfd = to_clk_pfd(hw);

	ग_लिखोl_relaxed(1 << ((pfd->idx + 1) * 8 - 1), pfd->reg + SET);
पूर्ण

अटल अचिन्हित दीर्घ clk_pfd_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pfd *pfd = to_clk_pfd(hw);
	u64 पंचांगp = parent_rate;
	u8 frac = (पढ़ोl_relaxed(pfd->reg) >> (pfd->idx * 8)) & 0x3f;

	पंचांगp *= 18;
	करो_भाग(पंचांगp, frac);

	वापस पंचांगp;
पूर्ण

अटल दीर्घ clk_pfd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	u64 पंचांगp = *prate;
	u8 frac;

	पंचांगp = पंचांगp * 18 + rate / 2;
	करो_भाग(पंचांगp, rate);
	frac = पंचांगp;
	अगर (frac < 12)
		frac = 12;
	अन्यथा अगर (frac > 35)
		frac = 35;
	पंचांगp = *prate;
	पंचांगp *= 18;
	करो_भाग(पंचांगp, frac);

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक clk_pfd_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pfd *pfd = to_clk_pfd(hw);
	u64 पंचांगp = parent_rate;
	u8 frac;

	पंचांगp = पंचांगp * 18 + rate / 2;
	करो_भाग(पंचांगp, rate);
	frac = पंचांगp;
	अगर (frac < 12)
		frac = 12;
	अन्यथा अगर (frac > 35)
		frac = 35;

	ग_लिखोl_relaxed(0x3f << (pfd->idx * 8), pfd->reg + CLR);
	ग_लिखोl_relaxed(frac << (pfd->idx * 8), pfd->reg + SET);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pfd_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pfd *pfd = to_clk_pfd(hw);

	अगर (पढ़ोl_relaxed(pfd->reg) & (1 << ((pfd->idx + 1) * 8 - 1)))
		वापस 0;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pfd_ops = अणु
	.enable		= clk_pfd_enable,
	.disable	= clk_pfd_disable,
	.recalc_rate	= clk_pfd_recalc_rate,
	.round_rate	= clk_pfd_round_rate,
	.set_rate	= clk_pfd_set_rate,
	.is_enabled     = clk_pfd_is_enabled,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pfd(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *reg, u8 idx)
अणु
	काष्ठा clk_pfd *pfd;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pfd = kzalloc(माप(*pfd), GFP_KERNEL);
	अगर (!pfd)
		वापस ERR_PTR(-ENOMEM);

	pfd->reg = reg;
	pfd->idx = idx;

	init.name = name;
	init.ops = &clk_pfd_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	pfd->hw.init = &init;
	hw = &pfd->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pfd);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
