<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2017 Lucas Stach, Pengutronix
 */

#समावेश <drm/drm_fourcc.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <video/imx-ipu-v3.h>

#समावेश "ipu-prv.h"

#घोषणा IPU_PRG_CTL				0x00
#घोषणा  IPU_PRG_CTL_BYPASS(i)			(1 << (0 + i))
#घोषणा  IPU_PRG_CTL_SOFT_ARID_MASK		0x3
#घोषणा  IPU_PRG_CTL_SOFT_ARID_SHIFT(i)		(8 + i * 2)
#घोषणा  IPU_PRG_CTL_SOFT_ARID(i, v)		((v & 0x3) << (8 + 2 * i))
#घोषणा  IPU_PRG_CTL_SO(i)			(1 << (16 + i))
#घोषणा  IPU_PRG_CTL_VFLIP(i)			(1 << (19 + i))
#घोषणा  IPU_PRG_CTL_BLOCK_MODE(i)		(1 << (22 + i))
#घोषणा  IPU_PRG_CTL_CNT_LOAD_EN(i)		(1 << (25 + i))
#घोषणा  IPU_PRG_CTL_SOFTRST			(1 << 30)
#घोषणा  IPU_PRG_CTL_SHADOW_EN			(1 << 31)

#घोषणा IPU_PRG_STATUS				0x04
#घोषणा  IPU_PRG_STATUS_BUFFER0_READY(i)	(1 << (0 + i * 2))
#घोषणा  IPU_PRG_STATUS_BUFFER1_READY(i)	(1 << (1 + i * 2))

#घोषणा IPU_PRG_QOS				0x08
#घोषणा  IPU_PRG_QOS_ARID_MASK			0xf
#घोषणा  IPU_PRG_QOS_ARID_SHIFT(i)		(0 + i * 4)

#घोषणा IPU_PRG_REG_UPDATE			0x0c
#घोषणा  IPU_PRG_REG_UPDATE_REG_UPDATE		(1 << 0)

#घोषणा IPU_PRG_STRIDE(i)			(0x10 + i * 0x4)
#घोषणा  IPU_PRG_STRIDE_STRIDE_MASK		0x3fff

#घोषणा IPU_PRG_CROP_LINE			0x1c

#घोषणा IPU_PRG_THD				0x20

#घोषणा IPU_PRG_BADDR(i)			(0x24 + i * 0x4)

#घोषणा IPU_PRG_OFFSET(i)			(0x30 + i * 0x4)

#घोषणा IPU_PRG_ILO(i)				(0x3c + i * 0x4)

#घोषणा IPU_PRG_HEIGHT(i)			(0x48 + i * 0x4)
#घोषणा  IPU_PRG_HEIGHT_PRE_HEIGHT_MASK		0xfff
#घोषणा  IPU_PRG_HEIGHT_PRE_HEIGHT_SHIFT	0
#घोषणा  IPU_PRG_HEIGHT_IPU_HEIGHT_MASK		0xfff
#घोषणा  IPU_PRG_HEIGHT_IPU_HEIGHT_SHIFT	16

काष्ठा ipu_prg_channel अणु
	bool			enabled;
	पूर्णांक			used_pre;
पूर्ण;

काष्ठा ipu_prg अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;
	पूर्णांक			id;

	व्योम __iomem		*regs;
	काष्ठा clk		*clk_ipg, *clk_axi;
	काष्ठा regmap		*iomuxc_gpr;
	काष्ठा ipu_pre		*pres[3];

	काष्ठा ipu_prg_channel	chan[3];
पूर्ण;

अटल DEFINE_MUTEX(ipu_prg_list_mutex);
अटल LIST_HEAD(ipu_prg_list);

काष्ठा ipu_prg *
ipu_prg_lookup_by_phandle(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक ipu_id)
अणु
	काष्ठा device_node *prg_node = of_parse_phandle(dev->of_node,
							name, 0);
	काष्ठा ipu_prg *prg;

	mutex_lock(&ipu_prg_list_mutex);
	list_क्रम_each_entry(prg, &ipu_prg_list, list) अणु
		अगर (prg_node == prg->dev->of_node) अणु
			mutex_unlock(&ipu_prg_list_mutex);
			device_link_add(dev, prg->dev,
					DL_FLAG_AUTOREMOVE_CONSUMER);
			prg->id = ipu_id;
			of_node_put(prg_node);
			वापस prg;
		पूर्ण
	पूर्ण
	mutex_unlock(&ipu_prg_list_mutex);

	of_node_put(prg_node);

	वापस शून्य;
पूर्ण

पूर्णांक ipu_prg_max_active_channels(व्योम)
अणु
	वापस ipu_pre_get_available_count();
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_max_active_channels);

bool ipu_prg_present(काष्ठा ipu_soc *ipu)
अणु
	अगर (ipu->prg_priv)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_present);

bool ipu_prg_क्रमmat_supported(काष्ठा ipu_soc *ipu, uपूर्णांक32_t क्रमmat,
			      uपूर्णांक64_t modअगरier)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);

	अगर (info->num_planes != 1)
		वापस false;

	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल DRM_FORMAT_MOD_VIVANTE_TILED:
	हाल DRM_FORMAT_MOD_VIVANTE_SUPER_TILED:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_क्रमmat_supported);

पूर्णांक ipu_prg_enable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_prg *prg = ipu->prg_priv;

	अगर (!prg)
		वापस 0;

	वापस pm_runसमय_get_sync(prg->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_enable);

व्योम ipu_prg_disable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_prg *prg = ipu->prg_priv;

	अगर (!prg)
		वापस;

	pm_runसमय_put(prg->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_disable);

/*
 * The channel configuartion functions below are not thपढ़ो safe, as they
 * must be only called from the atomic commit path in the DRM driver, which
 * is properly serialized.
 */
अटल पूर्णांक ipu_prg_ipu_to_prg_chan(पूर्णांक ipu_chan)
अणु
	/*
	 * This isn't clearly करोcumented in the RM, but IPU to PRG channel
	 * assignment is fixed, as only with this mapping the control संकेतs
	 * match up.
	 */
	चयन (ipu_chan) अणु
	हाल IPUV3_CHANNEL_MEM_BG_SYNC:
		वापस 0;
	हाल IPUV3_CHANNEL_MEM_FG_SYNC:
		वापस 1;
	हाल IPUV3_CHANNEL_MEM_DC_SYNC:
		वापस 2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ipu_prg_get_pre(काष्ठा ipu_prg *prg, पूर्णांक prg_chan)
अणु
	पूर्णांक i, ret;

	/* channel 0 is special as it is hardwired to one of the PREs */
	अगर (prg_chan == 0) अणु
		ret = ipu_pre_get(prg->pres[0]);
		अगर (ret)
			जाओ fail;
		prg->chan[prg_chan].used_pre = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 1; i < 3; i++) अणु
		ret = ipu_pre_get(prg->pres[i]);
		अगर (!ret) अणु
			u32 val, mux;
			पूर्णांक shअगरt;

			prg->chan[prg_chan].used_pre = i;

			/* configure the PRE to PRG channel mux */
			shअगरt = (i == 1) ? 12 : 14;
			mux = (prg->id << 1) | (prg_chan - 1);
			regmap_update_bits(prg->iomuxc_gpr, IOMUXC_GPR5,
					   0x3 << shअगरt, mux << shअगरt);

			/* check other mux, must not poपूर्णांक to same channel */
			shअगरt = (i == 1) ? 14 : 12;
			regmap_पढ़ो(prg->iomuxc_gpr, IOMUXC_GPR5, &val);
			अगर (((val >> shअगरt) & 0x3) == mux) अणु
				regmap_update_bits(prg->iomuxc_gpr, IOMUXC_GPR5,
						   0x3 << shअगरt,
						   (mux ^ 0x1) << shअगरt);
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

fail:
	dev_err(prg->dev, "could not get PRE for PRG chan %d", prg_chan);
	वापस ret;
पूर्ण

अटल व्योम ipu_prg_put_pre(काष्ठा ipu_prg *prg, पूर्णांक prg_chan)
अणु
	काष्ठा ipu_prg_channel *chan = &prg->chan[prg_chan];

	ipu_pre_put(prg->pres[chan->used_pre]);
	chan->used_pre = -1;
पूर्ण

व्योम ipu_prg_channel_disable(काष्ठा ipuv3_channel *ipu_chan)
अणु
	पूर्णांक prg_chan = ipu_prg_ipu_to_prg_chan(ipu_chan->num);
	काष्ठा ipu_prg *prg = ipu_chan->ipu->prg_priv;
	काष्ठा ipu_prg_channel *chan;
	u32 val;

	अगर (prg_chan < 0)
		वापस;

	chan = &prg->chan[prg_chan];
	अगर (!chan->enabled)
		वापस;

	pm_runसमय_get_sync(prg->dev);

	val = पढ़ोl(prg->regs + IPU_PRG_CTL);
	val |= IPU_PRG_CTL_BYPASS(prg_chan);
	ग_लिखोl(val, prg->regs + IPU_PRG_CTL);

	val = IPU_PRG_REG_UPDATE_REG_UPDATE;
	ग_लिखोl(val, prg->regs + IPU_PRG_REG_UPDATE);

	pm_runसमय_put(prg->dev);

	ipu_prg_put_pre(prg, prg_chan);

	chan->enabled = false;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_channel_disable);

पूर्णांक ipu_prg_channel_configure(काष्ठा ipuv3_channel *ipu_chan,
			      अचिन्हित पूर्णांक axi_id, अचिन्हित पूर्णांक width,
			      अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक stride,
			      u32 क्रमmat, uपूर्णांक64_t modअगरier, अचिन्हित दीर्घ *eba)
अणु
	पूर्णांक prg_chan = ipu_prg_ipu_to_prg_chan(ipu_chan->num);
	काष्ठा ipu_prg *prg = ipu_chan->ipu->prg_priv;
	काष्ठा ipu_prg_channel *chan;
	u32 val;
	पूर्णांक ret;

	अगर (prg_chan < 0)
		वापस prg_chan;

	chan = &prg->chan[prg_chan];

	अगर (chan->enabled) अणु
		ipu_pre_update(prg->pres[chan->used_pre], *eba);
		वापस 0;
	पूर्ण

	ret = ipu_prg_get_pre(prg, prg_chan);
	अगर (ret)
		वापस ret;

	ipu_pre_configure(prg->pres[chan->used_pre],
			  width, height, stride, क्रमmat, modअगरier, *eba);


	pm_runसमय_get_sync(prg->dev);

	val = (stride - 1) & IPU_PRG_STRIDE_STRIDE_MASK;
	ग_लिखोl(val, prg->regs + IPU_PRG_STRIDE(prg_chan));

	val = ((height & IPU_PRG_HEIGHT_PRE_HEIGHT_MASK) <<
	       IPU_PRG_HEIGHT_PRE_HEIGHT_SHIFT) |
	      ((height & IPU_PRG_HEIGHT_IPU_HEIGHT_MASK) <<
	       IPU_PRG_HEIGHT_IPU_HEIGHT_SHIFT);
	ग_लिखोl(val, prg->regs + IPU_PRG_HEIGHT(prg_chan));

	val = ipu_pre_get_baddr(prg->pres[chan->used_pre]);
	*eba = val;
	ग_लिखोl(val, prg->regs + IPU_PRG_BADDR(prg_chan));

	val = पढ़ोl(prg->regs + IPU_PRG_CTL);
	/* config AXI ID */
	val &= ~(IPU_PRG_CTL_SOFT_ARID_MASK <<
		 IPU_PRG_CTL_SOFT_ARID_SHIFT(prg_chan));
	val |= IPU_PRG_CTL_SOFT_ARID(prg_chan, axi_id);
	/* enable channel */
	val &= ~IPU_PRG_CTL_BYPASS(prg_chan);
	ग_लिखोl(val, prg->regs + IPU_PRG_CTL);

	val = IPU_PRG_REG_UPDATE_REG_UPDATE;
	ग_लिखोl(val, prg->regs + IPU_PRG_REG_UPDATE);

	/* रुको क्रम both द्विगुन buffers to be filled */
	पढ़ोl_poll_समयout(prg->regs + IPU_PRG_STATUS, val,
			   (val & IPU_PRG_STATUS_BUFFER0_READY(prg_chan)) &&
			   (val & IPU_PRG_STATUS_BUFFER1_READY(prg_chan)),
			   5, 1000);

	pm_runसमय_put(prg->dev);

	chan->enabled = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_channel_configure);

bool ipu_prg_channel_configure_pending(काष्ठा ipuv3_channel *ipu_chan)
अणु
	पूर्णांक prg_chan = ipu_prg_ipu_to_prg_chan(ipu_chan->num);
	काष्ठा ipu_prg *prg = ipu_chan->ipu->prg_priv;
	काष्ठा ipu_prg_channel *chan;

	अगर (prg_chan < 0)
		वापस false;

	chan = &prg->chan[prg_chan];
	WARN_ON(!chan->enabled);

	वापस ipu_pre_update_pending(prg->pres[chan->used_pre]);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_prg_channel_configure_pending);

अटल पूर्णांक ipu_prg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा ipu_prg *prg;
	u32 val;
	पूर्णांक i, ret;

	prg = devm_kzalloc(dev, माप(*prg), GFP_KERNEL);
	अगर (!prg)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	prg->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(prg->regs))
		वापस PTR_ERR(prg->regs);


	prg->clk_ipg = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(prg->clk_ipg))
		वापस PTR_ERR(prg->clk_ipg);

	prg->clk_axi = devm_clk_get(dev, "axi");
	अगर (IS_ERR(prg->clk_axi))
		वापस PTR_ERR(prg->clk_axi);

	prg->iomuxc_gpr =
		syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	अगर (IS_ERR(prg->iomuxc_gpr))
		वापस PTR_ERR(prg->iomuxc_gpr);

	क्रम (i = 0; i < 3; i++) अणु
		prg->pres[i] = ipu_pre_lookup_by_phandle(dev, "fsl,pres", i);
		अगर (!prg->pres[i])
			वापस -EPROBE_DEFER;
	पूर्ण

	ret = clk_prepare_enable(prg->clk_ipg);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(prg->clk_axi);
	अगर (ret) अणु
		clk_disable_unprepare(prg->clk_ipg);
		वापस ret;
	पूर्ण

	/* init to मुक्त running mode */
	val = पढ़ोl(prg->regs + IPU_PRG_CTL);
	val |= IPU_PRG_CTL_SHADOW_EN;
	ग_लिखोl(val, prg->regs + IPU_PRG_CTL);

	/* disable address threshold */
	ग_लिखोl(0xffffffff, prg->regs + IPU_PRG_THD);

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	prg->dev = dev;
	platक्रमm_set_drvdata(pdev, prg);
	mutex_lock(&ipu_prg_list_mutex);
	list_add(&prg->list, &ipu_prg_list);
	mutex_unlock(&ipu_prg_list_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_prg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipu_prg *prg = platक्रमm_get_drvdata(pdev);

	mutex_lock(&ipu_prg_list_mutex);
	list_del(&prg->list);
	mutex_unlock(&ipu_prg_list_mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक prg_suspend(काष्ठा device *dev)
अणु
	काष्ठा ipu_prg *prg = dev_get_drvdata(dev);

	clk_disable_unprepare(prg->clk_axi);
	clk_disable_unprepare(prg->clk_ipg);

	वापस 0;
पूर्ण

अटल पूर्णांक prg_resume(काष्ठा device *dev)
अणु
	काष्ठा ipu_prg *prg = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(prg->clk_ipg);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(prg->clk_axi);
	अगर (ret) अणु
		clk_disable_unprepare(prg->clk_ipg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops prg_pm_ops = अणु
	SET_RUNTIME_PM_OPS(prg_suspend, prg_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ipu_prg_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6qp-prg", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver ipu_prg_drv = अणु
	.probe		= ipu_prg_probe,
	.हटाओ		= ipu_prg_हटाओ,
	.driver		= अणु
		.name	= "imx-ipu-prg",
		.pm	= &prg_pm_ops,
		.of_match_table = ipu_prg_dt_ids,
	पूर्ण,
पूर्ण;
