<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2016-2018 Xilinx
 */

#अगर_अघोषित __LINUX_CLK_ZYNQMP_H_
#घोषणा __LINUX_CLK_ZYNQMP_H_

#समावेश <linux/spinlock.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>

क्रमागत topology_type अणु
	TYPE_INVALID,
	TYPE_MUX,
	TYPE_PLL,
	TYPE_FIXEDFACTOR,
	TYPE_DIV1,
	TYPE_DIV2,
	TYPE_GATE,
पूर्ण;

/**
 * काष्ठा घड़ी_प्रकारopology - Clock topology
 * @type:	Type of topology
 * @flag:	Topology flags
 * @type_flag:	Topology type specअगरic flag
 */
काष्ठा घड़ी_प्रकारopology अणु
	u32 type;
	u32 flag;
	u32 type_flag;
	u8 custom_type_flag;
पूर्ण;

काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_pll(स्थिर अक्षर *name, u32 clk_id,
				       स्थिर अक्षर * स्थिर *parents,
				       u8 num_parents,
				       स्थिर काष्ठा घड़ी_प्रकारopology *nodes);

काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_gate(स्थिर अक्षर *name, u32 clk_id,
					स्थिर अक्षर * स्थिर *parents,
					u8 num_parents,
					स्थिर काष्ठा घड़ी_प्रकारopology *nodes);

काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_भागider(स्थिर अक्षर *name,
					   u32 clk_id,
					   स्थिर अक्षर * स्थिर *parents,
					   u8 num_parents,
					   स्थिर काष्ठा घड़ी_प्रकारopology *nodes);

काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_mux(स्थिर अक्षर *name, u32 clk_id,
				       स्थिर अक्षर * स्थिर *parents,
				       u8 num_parents,
				       स्थिर काष्ठा घड़ी_प्रकारopology *nodes);

काष्ठा clk_hw *zynqmp_clk_रेजिस्टर_fixed_factor(स्थिर अक्षर *name,
					u32 clk_id,
					स्थिर अक्षर * स्थिर *parents,
					u8 num_parents,
					स्थिर काष्ठा घड़ी_प्रकारopology *nodes);

#पूर्ण_अगर
