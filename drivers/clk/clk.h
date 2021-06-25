<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

काष्ठा clk_hw;
काष्ठा device;
काष्ठा of_phandle_args;

#अगर defined(CONFIG_OF) && defined(CONFIG_COMMON_CLK)
काष्ठा clk_hw *of_clk_get_hw(काष्ठा device_node *np,
				    पूर्णांक index, स्थिर अक्षर *con_id);
#अन्यथा /* !CONFIG_COMMON_CLK || !CONFIG_OF */
अटल अंतरभूत काष्ठा clk_hw *of_clk_get_hw(काष्ठा device_node *np,
				    पूर्णांक index, स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
#पूर्ण_अगर

काष्ठा clk_hw *clk_find_hw(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id);

#अगर_घोषित CONFIG_COMMON_CLK
काष्ठा clk *clk_hw_create_clk(काष्ठा device *dev, काष्ठा clk_hw *hw,
			      स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id);
व्योम __clk_put(काष्ठा clk *clk);
#अन्यथा
/* All these casts to aव्योम अगरdefs in clkdev... */
अटल अंतरभूत काष्ठा clk *
clk_hw_create_clk(काष्ठा device *dev, काष्ठा clk_hw *hw, स्थिर अक्षर *dev_id,
		  स्थिर अक्षर *con_id)
अणु
	वापस (काष्ठा clk *)hw;
पूर्ण
अटल अंतरभूत व्योम __clk_put(काष्ठा clk *clk) अणु पूर्ण

#पूर्ण_अगर
