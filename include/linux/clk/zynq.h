<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 Xilinx Inc.
 * Copyright (C) 2012 National Instruments
 */

#अगर_अघोषित __LINUX_CLK_ZYNQ_H_
#घोषणा __LINUX_CLK_ZYNQ_H_

#समावेश <linux/spinlock.h>

व्योम zynq_घड़ी_init(व्योम);

काष्ठा clk *clk_रेजिस्टर_zynq_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *pll_ctrl, व्योम __iomem *pll_status, u8 lock_index,
		spinlock_t *lock);
#पूर्ण_अगर
