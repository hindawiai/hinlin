<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 MediaTek Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#घोषणा VIO_MOD_TO_REG_IND(m)	((m) / 32)
#घोषणा VIO_MOD_TO_REG_OFF(m)	((m) % 32)

काष्ठा mtk_devapc_vio_dbgs अणु
	जोड़ अणु
		u32 vio_dbg0;
		काष्ठा अणु
			u32 mstid:16;
			u32 dmnid:6;
			u32 vio_w:1;
			u32 vio_r:1;
			u32 addr_h:4;
			u32 resv:4;
		पूर्ण dbg0_bits;
	पूर्ण;

	u32 vio_dbg1;
पूर्ण;

काष्ठा mtk_devapc_data अणु
	/* numbers of violation index */
	u32 vio_idx_num;

	/* reg offset */
	u32 vio_mask_offset;
	u32 vio_sta_offset;
	u32 vio_dbg0_offset;
	u32 vio_dbg1_offset;
	u32 apc_con_offset;
	u32 vio_shअगरt_sta_offset;
	u32 vio_shअगरt_sel_offset;
	u32 vio_shअगरt_con_offset;
पूर्ण;

काष्ठा mtk_devapc_context अणु
	काष्ठा device *dev;
	व्योम __iomem *infra_base;
	काष्ठा clk *infra_clk;
	स्थिर काष्ठा mtk_devapc_data *data;
पूर्ण;

अटल व्योम clear_vio_status(काष्ठा mtk_devapc_context *ctx)
अणु
	व्योम __iomem *reg;
	पूर्णांक i;

	reg = ctx->infra_base + ctx->data->vio_sta_offset;

	क्रम (i = 0; i < VIO_MOD_TO_REG_IND(ctx->data->vio_idx_num) - 1; i++)
		ग_लिखोl(GENMASK(31, 0), reg + 4 * i);

	ग_लिखोl(GENMASK(VIO_MOD_TO_REG_OFF(ctx->data->vio_idx_num) - 1, 0),
	       reg + 4 * i);
पूर्ण

अटल व्योम mask_module_irq(काष्ठा mtk_devapc_context *ctx, bool mask)
अणु
	व्योम __iomem *reg;
	u32 val;
	पूर्णांक i;

	reg = ctx->infra_base + ctx->data->vio_mask_offset;

	अगर (mask)
		val = GENMASK(31, 0);
	अन्यथा
		val = 0;

	क्रम (i = 0; i < VIO_MOD_TO_REG_IND(ctx->data->vio_idx_num) - 1; i++)
		ग_लिखोl(val, reg + 4 * i);

	val = पढ़ोl(reg + 4 * i);
	अगर (mask)
		val |= GENMASK(VIO_MOD_TO_REG_OFF(ctx->data->vio_idx_num) - 1,
			       0);
	अन्यथा
		val &= ~GENMASK(VIO_MOD_TO_REG_OFF(ctx->data->vio_idx_num) - 1,
				0);

	ग_लिखोl(val, reg + 4 * i);
पूर्ण

#घोषणा PHY_DEVAPC_TIMEOUT	0x10000

/*
 * devapc_sync_vio_dbg - करो "shift" mechansim" to get full violation inक्रमmation.
 *                       shअगरt mechanism is depends on devapc hardware design.
 *                       Mediatek devapc set multiple slaves as a group.
 *                       When violation is triggered, violation info is kept
 *                       inside devapc hardware.
 *                       Driver should करो shअगरt mechansim to sync full violation
 *                       info to VIO_DBGs रेजिस्टरs.
 *
 */
अटल पूर्णांक devapc_sync_vio_dbg(काष्ठा mtk_devapc_context *ctx)
अणु
	व्योम __iomem *pd_vio_shअगरt_sta_reg;
	व्योम __iomem *pd_vio_shअगरt_sel_reg;
	व्योम __iomem *pd_vio_shअगरt_con_reg;
	पूर्णांक min_shअगरt_group;
	पूर्णांक ret;
	u32 val;

	pd_vio_shअगरt_sta_reg = ctx->infra_base +
			       ctx->data->vio_shअगरt_sta_offset;
	pd_vio_shअगरt_sel_reg = ctx->infra_base +
			       ctx->data->vio_shअगरt_sel_offset;
	pd_vio_shअगरt_con_reg = ctx->infra_base +
			       ctx->data->vio_shअगरt_con_offset;

	/* Find the minimum shअगरt group which has violation */
	val = पढ़ोl(pd_vio_shअगरt_sta_reg);
	अगर (!val)
		वापस false;

	min_shअगरt_group = __ffs(val);

	/* Assign the group to sync */
	ग_लिखोl(0x1 << min_shअगरt_group, pd_vio_shअगरt_sel_reg);

	/* Start syncing */
	ग_लिखोl(0x1, pd_vio_shअगरt_con_reg);

	ret = पढ़ोl_poll_समयout(pd_vio_shअगरt_con_reg, val, val == 0x3, 0,
				 PHY_DEVAPC_TIMEOUT);
	अगर (ret) अणु
		dev_err(ctx->dev, "%s: Shift violation info failed\n", __func__);
		वापस false;
	पूर्ण

	/* Stop syncing */
	ग_लिखोl(0x0, pd_vio_shअगरt_con_reg);

	/* Write clear */
	ग_लिखोl(0x1 << min_shअगरt_group, pd_vio_shअगरt_sta_reg);

	वापस true;
पूर्ण

/*
 * devapc_extract_vio_dbg - extract full violation inक्रमmation after करोing
 *                          shअगरt mechanism.
 */
अटल व्योम devapc_extract_vio_dbg(काष्ठा mtk_devapc_context *ctx)
अणु
	काष्ठा mtk_devapc_vio_dbgs vio_dbgs;
	व्योम __iomem *vio_dbg0_reg;
	व्योम __iomem *vio_dbg1_reg;

	vio_dbg0_reg = ctx->infra_base + ctx->data->vio_dbg0_offset;
	vio_dbg1_reg = ctx->infra_base + ctx->data->vio_dbg1_offset;

	vio_dbgs.vio_dbg0 = पढ़ोl(vio_dbg0_reg);
	vio_dbgs.vio_dbg1 = पढ़ोl(vio_dbg1_reg);

	/* Prपूर्णांक violation inक्रमmation */
	अगर (vio_dbgs.dbg0_bits.vio_w)
		dev_info(ctx->dev, "Write Violation\n");
	अन्यथा अगर (vio_dbgs.dbg0_bits.vio_r)
		dev_info(ctx->dev, "Read Violation\n");

	dev_info(ctx->dev, "Bus ID:0x%x, Dom ID:0x%x, Vio Addr:0x%x\n",
		 vio_dbgs.dbg0_bits.mstid, vio_dbgs.dbg0_bits.dmnid,
		 vio_dbgs.vio_dbg1);
पूर्ण

/*
 * devapc_violation_irq - the devapc Interrupt Service Routine (ISR) will dump
 *                        violation inक्रमmation including which master violates
 *                        access slave.
 */
अटल irqवापस_t devapc_violation_irq(पूर्णांक irq_number, व्योम *data)
अणु
	काष्ठा mtk_devapc_context *ctx = data;

	जबतक (devapc_sync_vio_dbg(ctx))
		devapc_extract_vio_dbg(ctx);

	clear_vio_status(ctx);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * start_devapc - unmask slave's irq to start receiving devapc violation.
 */
अटल व्योम start_devapc(काष्ठा mtk_devapc_context *ctx)
अणु
	ग_लिखोl(BIT(31), ctx->infra_base + ctx->data->apc_con_offset);

	mask_module_irq(ctx, false);
पूर्ण

/*
 * stop_devapc - mask slave's irq to stop service.
 */
अटल व्योम stop_devapc(काष्ठा mtk_devapc_context *ctx)
अणु
	mask_module_irq(ctx, true);

	ग_लिखोl(BIT(2), ctx->infra_base + ctx->data->apc_con_offset);
पूर्ण

अटल स्थिर काष्ठा mtk_devapc_data devapc_mt6779 = अणु
	.vio_idx_num = 511,
	.vio_mask_offset = 0x0,
	.vio_sta_offset = 0x400,
	.vio_dbg0_offset = 0x900,
	.vio_dbg1_offset = 0x904,
	.apc_con_offset = 0xF00,
	.vio_shअगरt_sta_offset = 0xF10,
	.vio_shअगरt_sel_offset = 0xF14,
	.vio_shअगरt_con_offset = 0xF20,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_devapc_dt_match[] = अणु
	अणु
		.compatible = "mediatek,mt6779-devapc",
		.data = &devapc_mt6779,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;

अटल पूर्णांक mtk_devapc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा mtk_devapc_context *ctx;
	u32 devapc_irq;
	पूर्णांक ret;

	अगर (IS_ERR(node))
		वापस -ENODEV;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->data = of_device_get_match_data(&pdev->dev);
	ctx->dev = &pdev->dev;

	ctx->infra_base = of_iomap(node, 0);
	अगर (!ctx->infra_base)
		वापस -EINVAL;

	devapc_irq = irq_of_parse_and_map(node, 0);
	अगर (!devapc_irq)
		वापस -EINVAL;

	ctx->infra_clk = devm_clk_get(&pdev->dev, "devapc-infra-clock");
	अगर (IS_ERR(ctx->infra_clk))
		वापस -EINVAL;

	अगर (clk_prepare_enable(ctx->infra_clk))
		वापस -EINVAL;

	ret = devm_request_irq(&pdev->dev, devapc_irq, devapc_violation_irq,
			       IRQF_TRIGGER_NONE, "devapc", ctx);
	अगर (ret) अणु
		clk_disable_unprepare(ctx->infra_clk);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ctx);

	start_devapc(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_devapc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_devapc_context *ctx = platक्रमm_get_drvdata(pdev);

	stop_devapc(ctx);

	clk_disable_unprepare(ctx->infra_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_devapc_driver = अणु
	.probe = mtk_devapc_probe,
	.हटाओ = mtk_devapc_हटाओ,
	.driver = अणु
		.name = "mtk-devapc",
		.of_match_table = mtk_devapc_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_devapc_driver);

MODULE_DESCRIPTION("Mediatek Device APC Driver");
MODULE_AUTHOR("Neal Liu <neal.liu@mediatek.com>");
MODULE_LICENSE("GPL");
