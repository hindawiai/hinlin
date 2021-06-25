<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  include/linux/clkdev.h
 *
 *  Copyright (C) 2008 Russell King.
 *
 * Helper क्रम the clk API to assist looking up a काष्ठा clk.
 */
#अगर_अघोषित __CLKDEV_H
#घोषणा __CLKDEV_H

#समावेश <linux/slab.h>

काष्ठा clk;
काष्ठा clk_hw;
काष्ठा device;

काष्ठा clk_lookup अणु
	काष्ठा list_head	node;
	स्थिर अक्षर		*dev_id;
	स्थिर अक्षर		*con_id;
	काष्ठा clk		*clk;
	काष्ठा clk_hw		*clk_hw;
पूर्ण;

#घोषणा CLKDEV_INIT(d, n, c)	\
	अणु			\
		.dev_id = d,	\
		.con_id = n,	\
		.clk = c,	\
	पूर्ण

काष्ठा clk_lookup *clkdev_alloc(काष्ठा clk *clk, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...) __म_लिखो(3, 4);
काष्ठा clk_lookup *clkdev_hw_alloc(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...) __म_लिखो(3, 4);

व्योम clkdev_add(काष्ठा clk_lookup *cl);
व्योम clkdev_drop(काष्ठा clk_lookup *cl);

काष्ठा clk_lookup *clkdev_create(काष्ठा clk *clk, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...) __म_लिखो(3, 4);
काष्ठा clk_lookup *clkdev_hw_create(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...) __म_लिखो(3, 4);

व्योम clkdev_add_table(काष्ठा clk_lookup *, माप_प्रकार);
पूर्णांक clk_add_alias(स्थिर अक्षर *, स्थिर अक्षर *, स्थिर अक्षर *, काष्ठा device *);

पूर्णांक clk_रेजिस्टर_clkdev(काष्ठा clk *, स्थिर अक्षर *, स्थिर अक्षर *);
पूर्णांक clk_hw_रेजिस्टर_clkdev(काष्ठा clk_hw *, स्थिर अक्षर *, स्थिर अक्षर *);

पूर्णांक devm_clk_hw_रेजिस्टर_clkdev(काष्ठा device *dev, काष्ठा clk_hw *hw,
				स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id);
व्योम devm_clk_release_clkdev(काष्ठा device *dev, स्थिर अक्षर *con_id,
			     स्थिर अक्षर *dev_id);
#पूर्ण_अगर
