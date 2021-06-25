<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#अगर_अघोषित __CLK_CONF_H
#घोषणा __CLK_CONF_H

#समावेश <linux/types.h>

काष्ठा device_node;

#अगर defined(CONFIG_OF) && defined(CONFIG_COMMON_CLK)
पूर्णांक of_clk_set_शेषs(काष्ठा device_node *node, bool clk_supplier);
#अन्यथा
अटल अंतरभूत पूर्णांक of_clk_set_शेषs(काष्ठा device_node *node,
				      bool clk_supplier)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __CLK_CONF_H */
