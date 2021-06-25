<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __MXS_CLK_H
#घोषणा __MXS_CLK_H

काष्ठा clk;

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>

#घोषणा SET	0x4
#घोषणा CLR	0x8

बाह्य spinlock_t mxs_lock;

पूर्णांक mxs_clk_रुको(व्योम __iomem *reg, u8 shअगरt);

काष्ठा clk *mxs_clk_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *base, u8 घातer, अचिन्हित दीर्घ rate);

काष्ठा clk *mxs_clk_ref(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *reg, u8 idx);

काष्ठा clk *mxs_clk_भाग(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *reg, u8 shअगरt, u8 width, u8 busy);

काष्ठा clk *mxs_clk_frac(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			 व्योम __iomem *reg, u8 shअगरt, u8 width, u8 busy);

अटल अंतरभूत काष्ठा clk *mxs_clk_fixed(स्थिर अक्षर *name, पूर्णांक rate)
अणु
	वापस clk_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
पूर्ण

अटल अंतरभूत काष्ठा clk *mxs_clk_gate(स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name, व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_रेजिस्टर_gate(शून्य, name, parent_name, CLK_SET_RATE_PARENT,
				 reg, shअगरt, CLK_GATE_SET_TO_DISABLE,
				 &mxs_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *mxs_clk_mux(स्थिर अक्षर *name, व्योम __iomem *reg,
		u8 shअगरt, u8 width, स्थिर अक्षर *स्थिर *parent_names, पूर्णांक num_parents)
अणु
	वापस clk_रेजिस्टर_mux(शून्य, name, parent_names, num_parents,
				CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
				reg, shअगरt, width, 0, &mxs_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *mxs_clk_fixed_factor(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name,
					 CLK_SET_RATE_PARENT, mult, भाग);
पूर्ण

#पूर्ण_अगर /* __MXS_CLK_H */
