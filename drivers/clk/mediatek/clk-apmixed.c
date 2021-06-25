<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश "clk-mtk.h"

#घोषणा REF2USB_TX_EN		BIT(0)
#घोषणा REF2USB_TX_LPF_EN	BIT(1)
#घोषणा REF2USB_TX_OUT_EN	BIT(2)
#घोषणा REF2USB_EN_MASK		(REF2USB_TX_EN | REF2USB_TX_LPF_EN | \
				 REF2USB_TX_OUT_EN)

काष्ठा mtk_ref2usb_tx अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*base_addr;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_ref2usb_tx *to_mtk_ref2usb_tx(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_ref2usb_tx, hw);
पूर्ण

अटल पूर्णांक mtk_ref2usb_tx_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_ref2usb_tx *tx = to_mtk_ref2usb_tx(hw);

	वापस (पढ़ोl(tx->base_addr) & REF2USB_EN_MASK) == REF2USB_EN_MASK;
पूर्ण

अटल पूर्णांक mtk_ref2usb_tx_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_ref2usb_tx *tx = to_mtk_ref2usb_tx(hw);
	u32 val;

	val = पढ़ोl(tx->base_addr);

	val |= REF2USB_TX_EN;
	ग_लिखोl(val, tx->base_addr);
	udelay(100);

	val |= REF2USB_TX_LPF_EN;
	ग_लिखोl(val, tx->base_addr);

	val |= REF2USB_TX_OUT_EN;
	ग_लिखोl(val, tx->base_addr);

	वापस 0;
पूर्ण

अटल व्योम mtk_ref2usb_tx_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_ref2usb_tx *tx = to_mtk_ref2usb_tx(hw);
	u32 val;

	val = पढ़ोl(tx->base_addr);
	val &= ~REF2USB_EN_MASK;
	ग_लिखोl(val, tx->base_addr);
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_ref2usb_tx_ops = अणु
	.is_prepared	= mtk_ref2usb_tx_is_prepared,
	.prepare	= mtk_ref2usb_tx_prepare,
	.unprepare	= mtk_ref2usb_tx_unprepare,
पूर्ण;

काष्ठा clk * __init mtk_clk_रेजिस्टर_ref2usb_tx(स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name, व्योम __iomem *reg)
अणु
	काष्ठा mtk_ref2usb_tx *tx;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk *clk;

	tx = kzalloc(माप(*tx), GFP_KERNEL);
	अगर (!tx)
		वापस ERR_PTR(-ENOMEM);

	tx->base_addr = reg;
	tx->hw.init = &init;

	init.name = name;
	init.ops = &mtk_ref2usb_tx_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(शून्य, &tx->hw);

	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to register clk %s: %ld\n", name, PTR_ERR(clk));
		kमुक्त(tx);
	पूर्ण

	वापस clk;
पूर्ण
