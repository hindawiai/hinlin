<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Amlogic Meson AO CEC G12A Controller
 *
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>
#समावेश <linux/clk-provider.h>

/* CEC Registers */

#घोषणा CECB_CLK_CNTL_REG0		0x00

#घोषणा CECB_CLK_CNTL_N1		GENMASK(11, 0)
#घोषणा CECB_CLK_CNTL_N2		GENMASK(23, 12)
#घोषणा CECB_CLK_CNTL_DUAL_EN		BIT(28)
#घोषणा CECB_CLK_CNTL_OUTPUT_EN		BIT(30)
#घोषणा CECB_CLK_CNTL_INPUT_EN		BIT(31)

#घोषणा CECB_CLK_CNTL_REG1		0x04

#घोषणा CECB_CLK_CNTL_M1		GENMASK(11, 0)
#घोषणा CECB_CLK_CNTL_M2		GENMASK(23, 12)
#घोषणा CECB_CLK_CNTL_BYPASS_EN		BIT(24)

/*
 * [14:12] Filter_del. For glitch-filtering CEC line, ignore संकेत
 *       change pulse width < filter_del * T(filter_tick) * 3.
 * [9:8] Filter_tick_sel: Select which periodical pulse क्रम
 *       glitch-filtering CEC line संकेत.
 *  - 0=Use T(xtal)*3 = 125ns;
 *  - 1=Use once-per-1us pulse;
 *  - 2=Use once-per-10us pulse;
 *  - 3=Use once-per-100us pulse.
 * [3]   Sysclk_en. 0=Disable प्रणाली घड़ी; 1=Enable प्रणाली घड़ी.
 * [2:1] cntl_clk
 *  - 0 = Disable clk (Power-off mode)
 *  - 1 = Enable gated घड़ी (Normal mode)
 *  - 2 = Enable मुक्त-run clk (Debug mode)
 * [0] SW_RESET 1=Apply reset; 0=No reset.
 */
#घोषणा CECB_GEN_CNTL_REG		0x08

#घोषणा CECB_GEN_CNTL_RESET		BIT(0)
#घोषणा CECB_GEN_CNTL_CLK_DISABLE	0
#घोषणा CECB_GEN_CNTL_CLK_ENABLE	1
#घोषणा CECB_GEN_CNTL_CLK_ENABLE_DBG	2
#घोषणा CECB_GEN_CNTL_CLK_CTRL_MASK	GENMASK(2, 1)
#घोषणा CECB_GEN_CNTL_SYS_CLK_EN	BIT(3)
#घोषणा CECB_GEN_CNTL_FILTER_TICK_125NS	0
#घोषणा CECB_GEN_CNTL_FILTER_TICK_1US	1
#घोषणा CECB_GEN_CNTL_FILTER_TICK_10US	2
#घोषणा CECB_GEN_CNTL_FILTER_TICK_100US	3
#घोषणा CECB_GEN_CNTL_FILTER_TICK_SEL	GENMASK(9, 8)
#घोषणा CECB_GEN_CNTL_FILTER_DEL	GENMASK(14, 12)

/*
 * [7:0] cec_reg_addr
 * [15:8] cec_reg_wrdata
 * [16] cec_reg_wr
 *  - 0 = Read
 *  - 1 = Write
 * [31:24] cec_reg_rddata
 */
#घोषणा CECB_RW_REG			0x0c

#घोषणा CECB_RW_ADDR			GENMASK(7, 0)
#घोषणा CECB_RW_WR_DATA			GENMASK(15, 8)
#घोषणा CECB_RW_WRITE_EN		BIT(16)
#घोषणा CECB_RW_BUS_BUSY		BIT(23)
#घोषणा CECB_RW_RD_DATA			GENMASK(31, 24)

/*
 * [0] DONE Interrupt
 * [1] End Of Message Interrupt
 * [2] Not Acknowlegde Interrupt
 * [3] Arbitration Loss Interrupt
 * [4] Initiator Error Interrupt
 * [5] Follower Error Interrupt
 * [6] Wake-Up Interrupt
 */
#घोषणा CECB_INTR_MASKN_REG		0x10
#घोषणा CECB_INTR_CLR_REG		0x14
#घोषणा CECB_INTR_STAT_REG		0x18

#घोषणा CECB_INTR_DONE			BIT(0)
#घोषणा CECB_INTR_EOM			BIT(1)
#घोषणा CECB_INTR_NACK			BIT(2)
#घोषणा CECB_INTR_ARB_LOSS		BIT(3)
#घोषणा CECB_INTR_INITIATOR_ERR		BIT(4)
#घोषणा CECB_INTR_FOLLOWER_ERR		BIT(5)
#घोषणा CECB_INTR_WAKE_UP		BIT(6)

/* CEC Commands */

#घोषणा CECB_CTRL		0x00

#घोषणा CECB_CTRL_SEND		BIT(0)
#घोषणा CECB_CTRL_TYPE		GENMASK(2, 1)
#घोषणा CECB_CTRL_TYPE_RETRY	0
#घोषणा CECB_CTRL_TYPE_NEW	1
#घोषणा CECB_CTRL_TYPE_NEXT	2

#घोषणा CECB_CTRL2		0x01

#घोषणा CECB_CTRL2_RISE_DEL_MAX	GENMASK(4, 0)

#घोषणा CECB_INTR_MASK		0x02
#घोषणा CECB_LADD_LOW		0x05
#घोषणा CECB_LADD_HIGH		0x06
#घोषणा CECB_TX_CNT		0x07
#घोषणा CECB_RX_CNT		0x08
#घोषणा CECB_STAT0		0x09
#घोषणा CECB_TX_DATA00		0x10
#घोषणा CECB_TX_DATA01		0x11
#घोषणा CECB_TX_DATA02		0x12
#घोषणा CECB_TX_DATA03		0x13
#घोषणा CECB_TX_DATA04		0x14
#घोषणा CECB_TX_DATA05		0x15
#घोषणा CECB_TX_DATA06		0x16
#घोषणा CECB_TX_DATA07		0x17
#घोषणा CECB_TX_DATA08		0x18
#घोषणा CECB_TX_DATA09		0x19
#घोषणा CECB_TX_DATA10		0x1A
#घोषणा CECB_TX_DATA11		0x1B
#घोषणा CECB_TX_DATA12		0x1C
#घोषणा CECB_TX_DATA13		0x1D
#घोषणा CECB_TX_DATA14		0x1E
#घोषणा CECB_TX_DATA15		0x1F
#घोषणा CECB_RX_DATA00		0x20
#घोषणा CECB_RX_DATA01		0x21
#घोषणा CECB_RX_DATA02		0x22
#घोषणा CECB_RX_DATA03		0x23
#घोषणा CECB_RX_DATA04		0x24
#घोषणा CECB_RX_DATA05		0x25
#घोषणा CECB_RX_DATA06		0x26
#घोषणा CECB_RX_DATA07		0x27
#घोषणा CECB_RX_DATA08		0x28
#घोषणा CECB_RX_DATA09		0x29
#घोषणा CECB_RX_DATA10		0x2A
#घोषणा CECB_RX_DATA11		0x2B
#घोषणा CECB_RX_DATA12		0x2C
#घोषणा CECB_RX_DATA13		0x2D
#घोषणा CECB_RX_DATA14		0x2E
#घोषणा CECB_RX_DATA15		0x2F
#घोषणा CECB_LOCK_BUF		0x30

#घोषणा CECB_LOCK_BUF_EN	BIT(0)

#घोषणा CECB_WAKEUPCTRL		0x31

काष्ठा meson_ao_cec_g12a_data अणु
	/* Setup the पूर्णांकernal CECB_CTRL2 रेजिस्टर */
	bool				ctrl2_setup;
पूर्ण;

काष्ठा meson_ao_cec_g12a_device अणु
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा regmap			*regmap;
	काष्ठा regmap			*regmap_cec;
	spinlock_t			cec_reg_lock;
	काष्ठा cec_notअगरier		*notअगरy;
	काष्ठा cec_adapter		*adap;
	काष्ठा cec_msg			rx_msg;
	काष्ठा clk			*oscin;
	काष्ठा clk			*core;
	स्थिर काष्ठा meson_ao_cec_g12a_data *data;
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_ao_cec_g12a_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = CECB_INTR_STAT_REG,
पूर्ण;

/*
 * The AO-CECB embeds a dual/भागider to generate a more precise
 * 32,768KHz घड़ी क्रम CEC core घड़ी.
 *                      ______   ______
 *                     |      | |      |
 *         ______      | Div1 |-| Cnt1 |       ______
 *        |      |    /|______| |______|\     |      |
 * Xtal-->| Gate |---|  ______   ______  X-X--| Gate |-->
 *        |______| |  \|      | |      |/  |  |______|
 *                 |   | Div2 |-| Cnt2 |   |
 *                 |   |______| |______|   |
 *                 |_______________________|
 *
 * The भागiding can be चयनed to single or dual, with a counter
 * क्रम each भागider to set when the चयनing is करोne.
 * The entire भागiding mechanism can be also bypassed.
 */

काष्ठा meson_ao_cec_g12a_duaद_भाग_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा hw_to_meson_ao_cec_g12a_duaद_भाग_clk(_hw)			\
	container_of(_hw, काष्ठा meson_ao_cec_g12a_duaद_भाग_clk, hw)	\

अटल अचिन्हित दीर्घ
meson_ao_cec_g12a_duaद_भाग_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा meson_ao_cec_g12a_duaद_भाग_clk *duaद_भाग_clk =
		hw_to_meson_ao_cec_g12a_duaद_भाग_clk(hw);
	अचिन्हित दीर्घ n1;
	u32 reg0, reg1;

	regmap_पढ़ो(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0, &reg0);
	regmap_पढ़ो(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0, &reg1);

	अगर (reg1 & CECB_CLK_CNTL_BYPASS_EN)
		वापस parent_rate;

	अगर (reg0 & CECB_CLK_CNTL_DUAL_EN) अणु
		अचिन्हित दीर्घ n2, m1, m2, f1, f2, p1, p2;

		n1 = FIELD_GET(CECB_CLK_CNTL_N1, reg0) + 1;
		n2 = FIELD_GET(CECB_CLK_CNTL_N2, reg0) + 1;

		m1 = FIELD_GET(CECB_CLK_CNTL_M1, reg1) + 1;
		m2 = FIELD_GET(CECB_CLK_CNTL_M1, reg1) + 1;

		f1 = DIV_ROUND_CLOSEST(parent_rate, n1);
		f2 = DIV_ROUND_CLOSEST(parent_rate, n2);

		p1 = DIV_ROUND_CLOSEST(100000000 * m1, f1 * (m1 + m2));
		p2 = DIV_ROUND_CLOSEST(100000000 * m2, f2 * (m1 + m2));

		वापस DIV_ROUND_UP(100000000, p1 + p2);
	पूर्ण

	n1 = FIELD_GET(CECB_CLK_CNTL_N1, reg0) + 1;

	वापस DIV_ROUND_CLOSEST(parent_rate, n1);
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_duaद_भाग_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा meson_ao_cec_g12a_duaद_भाग_clk *duaद_भाग_clk =
		hw_to_meson_ao_cec_g12a_duaद_भाग_clk(hw);


	/* Disable Input & Output */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN,
			   0);

	/* Set N1 & N2 */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_N1,
			   FIELD_PREP(CECB_CLK_CNTL_N1, 733 - 1));

	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_N2,
			   FIELD_PREP(CECB_CLK_CNTL_N2, 732 - 1));

	/* Set M1 & M2 */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_M1,
			   FIELD_PREP(CECB_CLK_CNTL_M1, 8 - 1));

	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_M2,
			   FIELD_PREP(CECB_CLK_CNTL_M2, 11 - 1));

	/* Enable Dual भागisor */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_DUAL_EN, CECB_CLK_CNTL_DUAL_EN);

	/* Disable भागisor bypass */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_BYPASS_EN, 0);

	/* Enable Input & Output */
	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN);

	वापस 0;
पूर्ण

अटल व्योम meson_ao_cec_g12a_duaद_भाग_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा meson_ao_cec_g12a_duaद_भाग_clk *duaद_भाग_clk =
		hw_to_meson_ao_cec_g12a_duaद_भाग_clk(hw);

	regmap_update_bits(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN,
			   0);
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_duaद_भाग_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा meson_ao_cec_g12a_duaद_भाग_clk *duaद_भाग_clk =
		hw_to_meson_ao_cec_g12a_duaद_भाग_clk(hw);
	पूर्णांक val;

	regmap_पढ़ो(duaद_भाग_clk->regmap, CECB_CLK_CNTL_REG0, &val);

	वापस !!(val & (CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN));
पूर्ण

अटल स्थिर काष्ठा clk_ops meson_ao_cec_g12a_duaद_भाग_clk_ops = अणु
	.recalc_rate	= meson_ao_cec_g12a_duaद_भाग_clk_recalc_rate,
	.is_enabled	= meson_ao_cec_g12a_duaद_भाग_clk_is_enabled,
	.enable		= meson_ao_cec_g12a_duaद_भाग_clk_enable,
	.disable	= meson_ao_cec_g12a_duaद_भाग_clk_disable,
पूर्ण;

अटल पूर्णांक meson_ao_cec_g12a_setup_clk(काष्ठा meson_ao_cec_g12a_device *ao_cec)
अणु
	काष्ठा meson_ao_cec_g12a_duaद_भाग_clk *duaद_भाग_clk;
	काष्ठा device *dev = &ao_cec->pdev->dev;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *clk;
	अक्षर *name;

	duaद_भाग_clk = devm_kzalloc(dev, माप(*duaद_भाग_clk), GFP_KERNEL);
	अगर (!duaद_भाग_clk)
		वापस -ENOMEM;

	name = kaप्र_लिखो(GFP_KERNEL, "%s#dualdiv_clk", dev_name(dev));
	अगर (!name)
		वापस -ENOMEM;

	parent_name = __clk_get_name(ao_cec->oscin);

	init.name = name;
	init.ops = &meson_ao_cec_g12a_duaद_भाग_clk_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	duaद_भाग_clk->regmap = ao_cec->regmap;
	duaद_भाग_clk->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &duaद_भाग_clk->hw);
	kमुक्त(name);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to register clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ao_cec->core = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_पढ़ो(व्योम *context, अचिन्हित पूर्णांक addr,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = context;
	u32 reg = FIELD_PREP(CECB_RW_ADDR, addr);
	पूर्णांक ret = 0;

	ret = regmap_ग_लिखो(ao_cec->regmap, CECB_RW_REG, reg);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(ao_cec->regmap, CECB_RW_REG, reg,
				       !(reg & CECB_RW_BUS_BUSY),
				       5, 1000);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(ao_cec->regmap, CECB_RW_REG, &reg);

	*data = FIELD_GET(CECB_RW_RD_DATA, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक addr,
				   अचिन्हित पूर्णांक data)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = context;
	u32 reg = FIELD_PREP(CECB_RW_ADDR, addr) |
		  FIELD_PREP(CECB_RW_WR_DATA, data) |
		  CECB_RW_WRITE_EN;

	वापस regmap_ग_लिखो(ao_cec->regmap, CECB_RW_REG, reg);
पूर्ण

अटल स्थिर काष्ठा regmap_config meson_ao_cec_g12a_cec_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.reg_पढ़ो = meson_ao_cec_g12a_पढ़ो,
	.reg_ग_लिखो = meson_ao_cec_g12a_ग_लिखो,
	.max_रेजिस्टर = 0xffff,
पूर्ण;

अटल अंतरभूत व्योम
meson_ao_cec_g12a_irq_setup(काष्ठा meson_ao_cec_g12a_device *ao_cec,
			    bool enable)
अणु
	u32 cfg = CECB_INTR_DONE | CECB_INTR_EOM | CECB_INTR_NACK |
		  CECB_INTR_ARB_LOSS | CECB_INTR_INITIATOR_ERR |
		  CECB_INTR_FOLLOWER_ERR;

	regmap_ग_लिखो(ao_cec->regmap, CECB_INTR_MASKN_REG,
		     enable ? cfg : 0);
पूर्ण

अटल व्योम meson_ao_cec_g12a_irq_rx(काष्ठा meson_ao_cec_g12a_device *ao_cec)
अणु
	पूर्णांक i, ret = 0;
	u32 val;

	ret = regmap_पढ़ो(ao_cec->regmap_cec, CECB_RX_CNT, &val);

	ao_cec->rx_msg.len = val;
	अगर (ao_cec->rx_msg.len > CEC_MAX_MSG_SIZE)
		ao_cec->rx_msg.len = CEC_MAX_MSG_SIZE;

	क्रम (i = 0; i < ao_cec->rx_msg.len; i++) अणु
		ret |= regmap_पढ़ो(ao_cec->regmap_cec,
				   CECB_RX_DATA00 + i, &val);

		ao_cec->rx_msg.msg[i] = val & 0xff;
	पूर्ण

	ret |= regmap_ग_लिखो(ao_cec->regmap_cec, CECB_LOCK_BUF, 0);
	अगर (ret)
		वापस;

	cec_received_msg(ao_cec->adap, &ao_cec->rx_msg);
पूर्ण

अटल irqवापस_t meson_ao_cec_g12a_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = data;
	u32 stat;

	regmap_पढ़ो(ao_cec->regmap, CECB_INTR_STAT_REG, &stat);
	अगर (stat)
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t meson_ao_cec_g12a_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = data;
	u32 stat;

	regmap_पढ़ो(ao_cec->regmap, CECB_INTR_STAT_REG, &stat);
	regmap_ग_लिखो(ao_cec->regmap, CECB_INTR_CLR_REG, stat);

	अगर (stat & CECB_INTR_DONE)
		cec_transmit_attempt_करोne(ao_cec->adap, CEC_TX_STATUS_OK);

	अगर (stat & CECB_INTR_EOM)
		meson_ao_cec_g12a_irq_rx(ao_cec);

	अगर (stat & CECB_INTR_NACK)
		cec_transmit_attempt_करोne(ao_cec->adap, CEC_TX_STATUS_NACK);

	अगर (stat & CECB_INTR_ARB_LOSS) अणु
		regmap_ग_लिखो(ao_cec->regmap_cec, CECB_TX_CNT, 0);
		regmap_update_bits(ao_cec->regmap_cec, CECB_CTRL,
				   CECB_CTRL_SEND | CECB_CTRL_TYPE, 0);
		cec_transmit_attempt_करोne(ao_cec->adap, CEC_TX_STATUS_ARB_LOST);
	पूर्ण

	/* Initiator reports an error on the CEC bus */
	अगर (stat & CECB_INTR_INITIATOR_ERR)
		cec_transmit_attempt_करोne(ao_cec->adap, CEC_TX_STATUS_ERROR);

	/* Follower reports a receive error, just reset RX buffer */
	अगर (stat & CECB_INTR_FOLLOWER_ERR)
		regmap_ग_लिखो(ao_cec->regmap_cec, CECB_LOCK_BUF, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
meson_ao_cec_g12a_set_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = adap->priv;
	पूर्णांक ret = 0;

	अगर (logical_addr == CEC_LOG_ADDR_INVALID) अणु
		/* Assume this will allways succeed */
		regmap_ग_लिखो(ao_cec->regmap_cec, CECB_LADD_LOW, 0);
		regmap_ग_लिखो(ao_cec->regmap_cec, CECB_LADD_HIGH, 0);

		वापस 0;
	पूर्ण अन्यथा अगर (logical_addr < 8) अणु
		ret = regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_LOW,
					 BIT(logical_addr),
					 BIT(logical_addr));
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_HIGH,
					 BIT(logical_addr - 8),
					 BIT(logical_addr - 8));
	पूर्ण

	/* Always set Broadcast/Unरेजिस्टरed 15 address */
	ret |= regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_HIGH,
				  BIT(CEC_LOG_ADDR_UNREGISTERED - 8),
				  BIT(CEC_LOG_ADDR_UNREGISTERED - 8));

	वापस ret ? -EIO : 0;
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				 u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = adap->priv;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret = 0;
	u32 val;
	पूर्णांक i;

	/* Check अगर RX is in progress */
	ret = regmap_पढ़ो(ao_cec->regmap_cec, CECB_LOCK_BUF, &val);
	अगर (ret)
		वापस ret;
	अगर (val & CECB_LOCK_BUF_EN)
		वापस -EBUSY;

	/* Check अगर TX Busy */
	ret = regmap_पढ़ो(ao_cec->regmap_cec, CECB_CTRL, &val);
	अगर (ret)
		वापस ret;
	अगर (val & CECB_CTRL_SEND)
		वापस -EBUSY;

	चयन (संकेत_मुक्त_समय) अणु
	हाल CEC_SIGNAL_FREE_TIME_RETRY:
		type = CECB_CTRL_TYPE_RETRY;
		अवरोध;
	हाल CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		type = CECB_CTRL_TYPE_NEXT;
		अवरोध;
	हाल CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
	शेष:
		type = CECB_CTRL_TYPE_NEW;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < msg->len; i++)
		ret |= regmap_ग_लिखो(ao_cec->regmap_cec, CECB_TX_DATA00 + i,
				    msg->msg[i]);

	ret |= regmap_ग_लिखो(ao_cec->regmap_cec, CECB_TX_CNT, msg->len);
	अगर (ret)
		वापस -EIO;

	ret = regmap_update_bits(ao_cec->regmap_cec, CECB_CTRL,
				 CECB_CTRL_SEND |
				 CECB_CTRL_TYPE,
				 CECB_CTRL_SEND |
				 FIELD_PREP(CECB_CTRL_TYPE, type));

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = adap->priv;

	meson_ao_cec_g12a_irq_setup(ao_cec, false);

	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_RESET, CECB_GEN_CNTL_RESET);

	अगर (!enable)
		वापस 0;

	/* Setup Filter */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_FILTER_TICK_SEL |
			   CECB_GEN_CNTL_FILTER_DEL,
			   FIELD_PREP(CECB_GEN_CNTL_FILTER_TICK_SEL,
				      CECB_GEN_CNTL_FILTER_TICK_1US) |
			   FIELD_PREP(CECB_GEN_CNTL_FILTER_DEL, 7));

	/* Enable System Clock */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_SYS_CLK_EN,
			   CECB_GEN_CNTL_SYS_CLK_EN);

	/* Enable gated घड़ी (Normal mode). */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_CLK_CTRL_MASK,
			    FIELD_PREP(CECB_GEN_CNTL_CLK_CTRL_MASK,
				       CECB_GEN_CNTL_CLK_ENABLE));

	/* Release Reset */
	regmap_update_bits(ao_cec->regmap, CECB_GEN_CNTL_REG,
			   CECB_GEN_CNTL_RESET, 0);

	अगर (ao_cec->data->ctrl2_setup)
		regmap_ग_लिखो(ao_cec->regmap_cec, CECB_CTRL2,
			     FIELD_PREP(CECB_CTRL2_RISE_DEL_MAX, 2));

	meson_ao_cec_g12a_irq_setup(ao_cec, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops meson_ao_cec_g12a_ops = अणु
	.adap_enable = meson_ao_cec_g12a_adap_enable,
	.adap_log_addr = meson_ao_cec_g12a_set_log_addr,
	.adap_transmit = meson_ao_cec_g12a_transmit,
पूर्ण;

अटल पूर्णांक meson_ao_cec_g12a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec;
	काष्ठा device *hdmi_dev;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret, irq;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(&pdev->dev);
	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	ao_cec = devm_kzalloc(&pdev->dev, माप(*ao_cec), GFP_KERNEL);
	अगर (!ao_cec)
		वापस -ENOMEM;

	ao_cec->data = of_device_get_match_data(&pdev->dev);
	अगर (!ao_cec->data) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_init(&ao_cec->cec_reg_lock);
	ao_cec->pdev = pdev;

	ao_cec->adap = cec_allocate_adapter(&meson_ao_cec_g12a_ops, ao_cec,
					    "meson_g12a_ao_cec",
					    CEC_CAP_DEFAULTS |
					    CEC_CAP_CONNECTOR_INFO,
					    CEC_MAX_LOG_ADDRS);
	अगर (IS_ERR(ao_cec->adap))
		वापस PTR_ERR(ao_cec->adap);

	ao_cec->adap->owner = THIS_MODULE;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ out_probe_adapter;
	पूर्ण

	ao_cec->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					       &meson_ao_cec_g12a_regmap_conf);
	अगर (IS_ERR(ao_cec->regmap)) अणु
		ret = PTR_ERR(ao_cec->regmap);
		जाओ out_probe_adapter;
	पूर्ण

	ao_cec->regmap_cec = devm_regmap_init(&pdev->dev, शून्य, ao_cec,
					   &meson_ao_cec_g12a_cec_regmap_conf);
	अगर (IS_ERR(ao_cec->regmap_cec)) अणु
		ret = PTR_ERR(ao_cec->regmap_cec);
		जाओ out_probe_adapter;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					meson_ao_cec_g12a_irq,
					meson_ao_cec_g12a_irq_thपढ़ो,
					0, शून्य, ao_cec);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request failed\n");
		जाओ out_probe_adapter;
	पूर्ण

	ao_cec->oscin = devm_clk_get(&pdev->dev, "oscin");
	अगर (IS_ERR(ao_cec->oscin)) अणु
		dev_err(&pdev->dev, "oscin clock request failed\n");
		ret = PTR_ERR(ao_cec->oscin);
		जाओ out_probe_adapter;
	पूर्ण

	ret = meson_ao_cec_g12a_setup_clk(ao_cec);
	अगर (ret)
		जाओ out_probe_adapter;

	ret = clk_prepare_enable(ao_cec->core);
	अगर (ret) अणु
		dev_err(&pdev->dev, "core clock enable failed\n");
		जाओ out_probe_adapter;
	पूर्ण

	device_reset_optional(&pdev->dev);

	platक्रमm_set_drvdata(pdev, ao_cec);

	ao_cec->notअगरy = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, शून्य,
							ao_cec->adap);
	अगर (!ao_cec->notअगरy) अणु
		ret = -ENOMEM;
		जाओ out_probe_core_clk;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(ao_cec->adap, &pdev->dev);
	अगर (ret < 0)
		जाओ out_probe_notअगरy;

	/* Setup Hardware */
	regmap_ग_लिखो(ao_cec->regmap, CECB_GEN_CNTL_REG, CECB_GEN_CNTL_RESET);

	वापस 0;

out_probe_notअगरy:
	cec_notअगरier_cec_adap_unरेजिस्टर(ao_cec->notअगरy, ao_cec->adap);

out_probe_core_clk:
	clk_disable_unprepare(ao_cec->core);

out_probe_adapter:
	cec_delete_adapter(ao_cec->adap);

	dev_err(&pdev->dev, "CEC controller registration failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_g12a_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ao_cec_g12a_device *ao_cec = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(ao_cec->core);

	cec_notअगरier_cec_adap_unरेजिस्टर(ao_cec->notअगरy, ao_cec->adap);

	cec_unरेजिस्टर_adapter(ao_cec->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_ao_cec_g12a_data ao_cec_g12a_data = अणु
	.ctrl2_setup = false,
पूर्ण;

अटल स्थिर काष्ठा meson_ao_cec_g12a_data ao_cec_sm1_data = अणु
	.ctrl2_setup = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_ao_cec_g12a_of_match[] = अणु
	अणु
		.compatible = "amlogic,meson-g12a-ao-cec",
		.data = &ao_cec_g12a_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-sm1-ao-cec",
		.data = &ao_cec_sm1_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_ao_cec_g12a_of_match);

अटल काष्ठा platक्रमm_driver meson_ao_cec_g12a_driver = अणु
	.probe   = meson_ao_cec_g12a_probe,
	.हटाओ  = meson_ao_cec_g12a_हटाओ,
	.driver  = अणु
		.name = "meson-ao-cec-g12a",
		.of_match_table = of_match_ptr(meson_ao_cec_g12a_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_ao_cec_g12a_driver);

MODULE_DESCRIPTION("Meson AO CEC G12A Controller driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL");
