<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hisilicon Hi3620 घड़ी gate driver
 *
 * Copyright (c) 2012-2013 Hisilicon Limited.
 * Copyright (c) 2012-2013 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 *	   Xin Li <li.xin@linaro.org>
 */

#अगर_अघोषित	__HISI_CLK_H
#घोषणा	__HISI_CLK_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

काष्ठा platक्रमm_device;

काष्ठा hisi_घड़ी_data अणु
	काष्ठा clk_onecell_data	clk_data;
	व्योम __iomem		*base;
पूर्ण;

काष्ठा hisi_fixed_rate_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	अक्षर			*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		fixed_rate;
पूर्ण;

काष्ठा hisi_fixed_factor_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	अक्षर			*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		mult;
	अचिन्हित दीर्घ		भाग;
	अचिन्हित दीर्घ		flags;
पूर्ण;

काष्ठा hisi_mux_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*स्थिर *parent_names;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u8			mux_flags;
	u32			*table;
	स्थिर अक्षर		*alias;
पूर्ण;

काष्ठा hisi_phase_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_names;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u32			*phase_degrees;
	u32			*phase_regvals;
	u8			phase_num;
पूर्ण;

काष्ठा hisi_भागider_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u8			भाग_flags;
	काष्ठा clk_भाग_प्रकारable	*table;
	स्थिर अक्षर		*alias;
पूर्ण;

काष्ठा hi6220_भागider_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u32			mask_bit;
	स्थिर अक्षर		*alias;
पूर्ण;

काष्ठा hisi_gate_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			bit_idx;
	u8			gate_flags;
	स्थिर अक्षर		*alias;
पूर्ण;

काष्ठा clk *hisi_रेजिस्टर_clkgate_sep(काष्ठा device *, स्थिर अक्षर *,
				स्थिर अक्षर *, अचिन्हित दीर्घ,
				व्योम __iomem *, u8,
				u8, spinlock_t *);
काष्ठा clk *hi6220_रेजिस्टर_clkभाग(काष्ठा device *dev, स्थिर अक्षर *name,
	स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags, व्योम __iomem *reg,
	u8 shअगरt, u8 width, u32 mask_bit, spinlock_t *lock);

काष्ठा hisi_घड़ी_data *hisi_clk_alloc(काष्ठा platक्रमm_device *, पूर्णांक);
काष्ठा hisi_घड़ी_data *hisi_clk_init(काष्ठा device_node *, पूर्णांक);
पूर्णांक hisi_clk_रेजिस्टर_fixed_rate(स्थिर काष्ठा hisi_fixed_rate_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);
पूर्णांक hisi_clk_रेजिस्टर_fixed_factor(स्थिर काष्ठा hisi_fixed_factor_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);
पूर्णांक hisi_clk_रेजिस्टर_mux(स्थिर काष्ठा hisi_mux_घड़ी *, पूर्णांक,
				काष्ठा hisi_घड़ी_data *);
काष्ठा clk *clk_रेजिस्टर_hisi_phase(काष्ठा device *dev,
				स्थिर काष्ठा hisi_phase_घड़ी *clks,
				व्योम __iomem *base, spinlock_t *lock);
पूर्णांक hisi_clk_रेजिस्टर_phase(काष्ठा device *dev,
				स्थिर काष्ठा hisi_phase_घड़ी *clks,
				पूर्णांक nums, काष्ठा hisi_घड़ी_data *data);
पूर्णांक hisi_clk_रेजिस्टर_भागider(स्थिर काष्ठा hisi_भागider_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);
पूर्णांक hisi_clk_रेजिस्टर_gate(स्थिर काष्ठा hisi_gate_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);
व्योम hisi_clk_रेजिस्टर_gate_sep(स्थिर काष्ठा hisi_gate_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);
व्योम hi6220_clk_रेजिस्टर_भागider(स्थिर काष्ठा hi6220_भागider_घड़ी *,
				पूर्णांक, काष्ठा hisi_घड़ी_data *);

#घोषणा hisi_clk_unरेजिस्टर(type) \
अटल अंतरभूत \
व्योम hisi_clk_unरेजिस्टर_##type(स्थिर काष्ठा hisi_##type##_घड़ी *clks, \
				पूर्णांक nums, काष्ठा hisi_घड़ी_data *data) \
अणु \
	काष्ठा clk **घड़ीs = data->clk_data.clks; \
	पूर्णांक i; \
	क्रम (i = 0; i < nums; i++) अणु \
		पूर्णांक id = clks[i].id; \
		अगर (घड़ीs[id])  \
			clk_unरेजिस्टर_##type(घड़ीs[id]); \
	पूर्ण \
पूर्ण

hisi_clk_unरेजिस्टर(fixed_rate)
hisi_clk_unरेजिस्टर(fixed_factor)
hisi_clk_unरेजिस्टर(mux)
hisi_clk_unरेजिस्टर(भागider)
hisi_clk_unरेजिस्टर(gate)

#पूर्ण_अगर	/* __HISI_CLK_H */
