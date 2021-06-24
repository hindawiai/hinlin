<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 SiFive, Inc.
 * Zong Li
 */

#अगर_अघोषित __SIFIVE_CLK_FU740_PRCI_H
#घोषणा __SIFIVE_CLK_FU740_PRCI_H

#समावेश "sifive-prci.h"

#घोषणा NUM_CLOCK_FU740	9

बाह्य काष्ठा __prci_घड़ी __prci_init_घड़ीs_fu740[NUM_CLOCK_FU740];

अटल स्थिर काष्ठा prci_clk_desc prci_clk_fu740 = अणु
	.clks = __prci_init_घड़ीs_fu740,
	.num_clks = ARRAY_SIZE(__prci_init_घड़ीs_fu740),
पूर्ण;

#पूर्ण_अगर /* __SIFIVE_CLK_FU740_PRCI_H */
