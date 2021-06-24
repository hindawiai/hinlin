<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>

#समावेश <video/mipi_display.h>

#समावेश "dsi.h"
#समावेश "dsi.xml.h"
#समावेश "sfpb.xml.h"
#समावेश "dsi_cfg.h"
#समावेश "msm_kms.h"
#समावेश "msm_gem.h"

#घोषणा DSI_RESET_TOGGLE_DELAY_MS 20

अटल पूर्णांक dsi_get_version(स्थिर व्योम __iomem *base, u32 *major, u32 *minor)
अणु
	u32 ver;

	अगर (!major || !minor)
		वापस -EINVAL;

	/*
	 * From DSI6G(v3), addition of a 6G_HW_VERSION रेजिस्टर at offset 0
	 * makes all other रेजिस्टरs 4-byte shअगरted करोwn.
	 *
	 * In order to identअगरy between DSI6G(v3) and beyond, and DSIv2 and
	 * older, we पढ़ो the DSI_VERSION रेजिस्टर without any shअगरt(offset
	 * 0x1f0). In the हाल of DSIv2, this hast to be a non-zero value. In
	 * the हाल of DSI6G, this has to be zero (the offset poपूर्णांकs to a
	 * scratch रेजिस्टर which we never touch)
	 */

	ver = msm_पढ़ोl(base + REG_DSI_VERSION);
	अगर (ver) अणु
		/* older dsi host, there is no रेजिस्टर shअगरt */
		ver = FIELD(ver, DSI_VERSION_MAJOR);
		अगर (ver <= MSM_DSI_VER_MAJOR_V2) अणु
			/* old versions */
			*major = ver;
			*minor = 0;
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * newer host, offset 0 has 6G_HW_VERSION, the rest of the
		 * रेजिस्टरs are shअगरted करोwn, पढ़ो DSI_VERSION again with
		 * the shअगरted offset
		 */
		ver = msm_पढ़ोl(base + DSI_6G_REG_SHIFT + REG_DSI_VERSION);
		ver = FIELD(ver, DSI_VERSION_MAJOR);
		अगर (ver == MSM_DSI_VER_MAJOR_6G) अणु
			/* 6G version */
			*major = ver;
			*minor = msm_पढ़ोl(base + REG_DSI_6G_HW_VERSION);
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा DSI_ERR_STATE_ACK			0x0000
#घोषणा DSI_ERR_STATE_TIMEOUT			0x0001
#घोषणा DSI_ERR_STATE_DLN0_PHY			0x0002
#घोषणा DSI_ERR_STATE_FIFO			0x0004
#घोषणा DSI_ERR_STATE_MDP_FIFO_UNDERFLOW	0x0008
#घोषणा DSI_ERR_STATE_INTERLEAVE_OP_CONTENTION	0x0010
#घोषणा DSI_ERR_STATE_PLL_UNLOCKED		0x0020

#घोषणा DSI_CLK_CTRL_ENABLE_CLKS	\
		(DSI_CLK_CTRL_AHBS_HCLK_ON | DSI_CLK_CTRL_AHBM_SCLK_ON | \
		DSI_CLK_CTRL_PCLK_ON | DSI_CLK_CTRL_DSICLK_ON | \
		DSI_CLK_CTRL_BYTECLK_ON | DSI_CLK_CTRL_ESCCLK_ON | \
		DSI_CLK_CTRL_FORCE_ON_DYN_AHBM_HCLK)

काष्ठा msm_dsi_host अणु
	काष्ठा mipi_dsi_host base;

	काष्ठा platक्रमm_device *pdev;
	काष्ठा drm_device *dev;

	पूर्णांक id;

	व्योम __iomem *ctrl_base;
	काष्ठा regulator_bulk_data supplies[DSI_DEV_REGULATOR_MAX];

	काष्ठा clk *bus_clks[DSI_BUS_CLK_MAX];

	काष्ठा clk *byte_clk;
	काष्ठा clk *esc_clk;
	काष्ठा clk *pixel_clk;
	काष्ठा clk *byte_clk_src;
	काष्ठा clk *pixel_clk_src;
	काष्ठा clk *byte_पूर्णांकf_clk;

	काष्ठा opp_table *opp_table;

	u32 byte_clk_rate;
	u32 pixel_clk_rate;
	u32 esc_clk_rate;

	/* DSI v2 specअगरic घड़ीs */
	काष्ठा clk *src_clk;
	काष्ठा clk *esc_clk_src;
	काष्ठा clk *dsi_clk_src;

	u32 src_clk_rate;

	काष्ठा gpio_desc *disp_en_gpio;
	काष्ठा gpio_desc *te_gpio;

	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd;

	काष्ठा completion dma_comp;
	काष्ठा completion video_comp;
	काष्ठा mutex dev_mutex;
	काष्ठा mutex cmd_mutex;
	spinlock_t पूर्णांकr_lock; /* Protect पूर्णांकerrupt ctrl रेजिस्टर */

	u32 err_work_state;
	काष्ठा work_काष्ठा err_work;
	काष्ठा work_काष्ठा hpd_work;
	काष्ठा workqueue_काष्ठा *workqueue;

	/* DSI 6G TX buffer*/
	काष्ठा drm_gem_object *tx_gem_obj;

	/* DSI v2 TX buffer */
	व्योम *tx_buf;
	dma_addr_t tx_buf_paddr;

	पूर्णांक tx_size;

	u8 *rx_buf;

	काष्ठा regmap *sfpb;

	काष्ठा drm_display_mode *mode;

	/* connected device info */
	काष्ठा device_node *device_node;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक lanes;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित दीर्घ mode_flags;

	/* lane data parsed via DT */
	पूर्णांक dlane_swap;
	पूर्णांक num_data_lanes;

	u32 dma_cmd_ctrl_restore;

	bool रेजिस्टरed;
	bool घातer_on;
	bool enabled;
	पूर्णांक irq;
पूर्ण;

अटल u32 dsi_get_bpp(स्थिर क्रमागत mipi_dsi_pixel_क्रमmat fmt)
अणु
	चयन (fmt) अणु
	हाल MIPI_DSI_FMT_RGB565:		वापस 16;
	हाल MIPI_DSI_FMT_RGB666_PACKED:	वापस 18;
	हाल MIPI_DSI_FMT_RGB666:
	हाल MIPI_DSI_FMT_RGB888:
	शेष:				वापस 24;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 dsi_पढ़ो(काष्ठा msm_dsi_host *msm_host, u32 reg)
अणु
	वापस msm_पढ़ोl(msm_host->ctrl_base + reg);
पूर्ण
अटल अंतरभूत व्योम dsi_ग_लिखो(काष्ठा msm_dsi_host *msm_host, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, msm_host->ctrl_base + reg);
पूर्ण

अटल पूर्णांक dsi_host_regulator_enable(काष्ठा msm_dsi_host *msm_host);
अटल व्योम dsi_host_regulator_disable(काष्ठा msm_dsi_host *msm_host);

अटल स्थिर काष्ठा msm_dsi_cfg_handler *dsi_get_config(
						काष्ठा msm_dsi_host *msm_host)
अणु
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = शून्य;
	काष्ठा device *dev = &msm_host->pdev->dev;
	काष्ठा regulator *gdsc_reg;
	काष्ठा clk *ahb_clk;
	पूर्णांक ret;
	u32 major = 0, minor = 0;

	gdsc_reg = regulator_get(dev, "gdsc");
	अगर (IS_ERR(gdsc_reg)) अणु
		pr_err("%s: cannot get gdsc\n", __func__);
		जाओ निकास;
	पूर्ण

	ahb_clk = msm_clk_get(msm_host->pdev, "iface");
	अगर (IS_ERR(ahb_clk)) अणु
		pr_err("%s: cannot get interface clock\n", __func__);
		जाओ put_gdsc;
	पूर्ण

	pm_runसमय_get_sync(dev);

	ret = regulator_enable(gdsc_reg);
	अगर (ret) अणु
		pr_err("%s: unable to enable gdsc\n", __func__);
		जाओ put_gdsc;
	पूर्ण

	ret = clk_prepare_enable(ahb_clk);
	अगर (ret) अणु
		pr_err("%s: unable to enable ahb_clk\n", __func__);
		जाओ disable_gdsc;
	पूर्ण

	ret = dsi_get_version(msm_host->ctrl_base, &major, &minor);
	अगर (ret) अणु
		pr_err("%s: Invalid version\n", __func__);
		जाओ disable_clks;
	पूर्ण

	cfg_hnd = msm_dsi_cfg_get(major, minor);

	DBG("%s: Version %x:%x\n", __func__, major, minor);

disable_clks:
	clk_disable_unprepare(ahb_clk);
disable_gdsc:
	regulator_disable(gdsc_reg);
	pm_runसमय_put_sync(dev);
put_gdsc:
	regulator_put(gdsc_reg);
निकास:
	वापस cfg_hnd;
पूर्ण

अटल अंतरभूत काष्ठा msm_dsi_host *to_msm_dsi_host(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा msm_dsi_host, base);
पूर्ण

अटल व्योम dsi_host_regulator_disable(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा regulator_bulk_data *s = msm_host->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = msm_host->cfg_hnd->cfg->reg_cfg.regs;
	पूर्णांक num = msm_host->cfg_hnd->cfg->reg_cfg.num;
	पूर्णांक i;

	DBG("");
	क्रम (i = num - 1; i >= 0; i--)
		अगर (regs[i].disable_load >= 0)
			regulator_set_load(s[i].consumer,
					   regs[i].disable_load);

	regulator_bulk_disable(num, s);
पूर्ण

अटल पूर्णांक dsi_host_regulator_enable(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा regulator_bulk_data *s = msm_host->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = msm_host->cfg_hnd->cfg->reg_cfg.regs;
	पूर्णांक num = msm_host->cfg_hnd->cfg->reg_cfg.num;
	पूर्णांक ret, i;

	DBG("");
	क्रम (i = 0; i < num; i++) अणु
		अगर (regs[i].enable_load >= 0) अणु
			ret = regulator_set_load(s[i].consumer,
						 regs[i].enable_load);
			अगर (ret < 0) अणु
				pr_err("regulator %d set op mode failed, %d\n",
					i, ret);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(num, s);
	अगर (ret < 0) अणु
		pr_err("regulator enable failed, %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	क्रम (i--; i >= 0; i--)
		regulator_set_load(s[i].consumer, regs[i].disable_load);
	वापस ret;
पूर्ण

अटल पूर्णांक dsi_regulator_init(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा regulator_bulk_data *s = msm_host->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = msm_host->cfg_hnd->cfg->reg_cfg.regs;
	पूर्णांक num = msm_host->cfg_hnd->cfg->reg_cfg.num;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++)
		s[i].supply = regs[i].name;

	ret = devm_regulator_bulk_get(&msm_host->pdev->dev, num, s);
	अगर (ret < 0) अणु
		pr_err("%s: failed to init regulator, ret=%d\n",
						__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dsi_clk_init_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	पूर्णांक ret = 0;

	msm_host->src_clk = msm_clk_get(pdev, "src");

	अगर (IS_ERR(msm_host->src_clk)) अणु
		ret = PTR_ERR(msm_host->src_clk);
		pr_err("%s: can't find src clock. ret=%d\n",
			__func__, ret);
		msm_host->src_clk = शून्य;
		वापस ret;
	पूर्ण

	msm_host->esc_clk_src = clk_get_parent(msm_host->esc_clk);
	अगर (!msm_host->esc_clk_src) अणु
		ret = -ENODEV;
		pr_err("%s: can't get esc clock parent. ret=%d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	msm_host->dsi_clk_src = clk_get_parent(msm_host->src_clk);
	अगर (!msm_host->dsi_clk_src) अणु
		ret = -ENODEV;
		pr_err("%s: can't get src clock parent. ret=%d\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dsi_clk_init_6g_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	पूर्णांक ret = 0;

	msm_host->byte_पूर्णांकf_clk = msm_clk_get(pdev, "byte_intf");
	अगर (IS_ERR(msm_host->byte_पूर्णांकf_clk)) अणु
		ret = PTR_ERR(msm_host->byte_पूर्णांकf_clk);
		pr_err("%s: can't find byte_intf clock. ret=%d\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dsi_clk_init(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	स्थिर काष्ठा msm_dsi_config *cfg = cfg_hnd->cfg;
	पूर्णांक i, ret = 0;

	/* get bus घड़ीs */
	क्रम (i = 0; i < cfg->num_bus_clks; i++) अणु
		msm_host->bus_clks[i] = msm_clk_get(pdev,
						cfg->bus_clk_names[i]);
		अगर (IS_ERR(msm_host->bus_clks[i])) अणु
			ret = PTR_ERR(msm_host->bus_clks[i]);
			pr_err("%s: Unable to get %s clock, ret = %d\n",
				__func__, cfg->bus_clk_names[i], ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* get link and source घड़ीs */
	msm_host->byte_clk = msm_clk_get(pdev, "byte");
	अगर (IS_ERR(msm_host->byte_clk)) अणु
		ret = PTR_ERR(msm_host->byte_clk);
		pr_err("%s: can't find dsi_byte clock. ret=%d\n",
			__func__, ret);
		msm_host->byte_clk = शून्य;
		जाओ निकास;
	पूर्ण

	msm_host->pixel_clk = msm_clk_get(pdev, "pixel");
	अगर (IS_ERR(msm_host->pixel_clk)) अणु
		ret = PTR_ERR(msm_host->pixel_clk);
		pr_err("%s: can't find dsi_pixel clock. ret=%d\n",
			__func__, ret);
		msm_host->pixel_clk = शून्य;
		जाओ निकास;
	पूर्ण

	msm_host->esc_clk = msm_clk_get(pdev, "core");
	अगर (IS_ERR(msm_host->esc_clk)) अणु
		ret = PTR_ERR(msm_host->esc_clk);
		pr_err("%s: can't find dsi_esc clock. ret=%d\n",
			__func__, ret);
		msm_host->esc_clk = शून्य;
		जाओ निकास;
	पूर्ण

	msm_host->byte_clk_src = clk_get_parent(msm_host->byte_clk);
	अगर (IS_ERR(msm_host->byte_clk_src)) अणु
		ret = PTR_ERR(msm_host->byte_clk_src);
		pr_err("%s: can't find byte_clk clock. ret=%d\n", __func__, ret);
		जाओ निकास;
	पूर्ण

	msm_host->pixel_clk_src = clk_get_parent(msm_host->pixel_clk);
	अगर (IS_ERR(msm_host->pixel_clk_src)) अणु
		ret = PTR_ERR(msm_host->pixel_clk_src);
		pr_err("%s: can't find pixel_clk clock. ret=%d\n", __func__, ret);
		जाओ निकास;
	पूर्ण

	अगर (cfg_hnd->ops->clk_init_ver)
		ret = cfg_hnd->ops->clk_init_ver(msm_host);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक dsi_bus_clk_enable(काष्ठा msm_dsi_host *msm_host)
अणु
	स्थिर काष्ठा msm_dsi_config *cfg = msm_host->cfg_hnd->cfg;
	पूर्णांक i, ret;

	DBG("id=%d", msm_host->id);

	क्रम (i = 0; i < cfg->num_bus_clks; i++) अणु
		ret = clk_prepare_enable(msm_host->bus_clks[i]);
		अगर (ret) अणु
			pr_err("%s: failed to enable bus clock %d ret %d\n",
				__func__, i, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	क्रम (; i > 0; i--)
		clk_disable_unprepare(msm_host->bus_clks[i]);

	वापस ret;
पूर्ण

अटल व्योम dsi_bus_clk_disable(काष्ठा msm_dsi_host *msm_host)
अणु
	स्थिर काष्ठा msm_dsi_config *cfg = msm_host->cfg_hnd->cfg;
	पूर्णांक i;

	DBG("");

	क्रम (i = cfg->num_bus_clks - 1; i >= 0; i--)
		clk_disable_unprepare(msm_host->bus_clks[i]);
पूर्ण

पूर्णांक msm_dsi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_dsi *msm_dsi = platक्रमm_get_drvdata(pdev);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	अगर (!msm_host->cfg_hnd)
		वापस 0;

	dsi_bus_clk_disable(msm_host);

	वापस 0;
पूर्ण

पूर्णांक msm_dsi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_dsi *msm_dsi = platक्रमm_get_drvdata(pdev);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	अगर (!msm_host->cfg_hnd)
		वापस 0;

	वापस dsi_bus_clk_enable(msm_host);
पूर्ण

पूर्णांक dsi_link_clk_set_rate_6g(काष्ठा msm_dsi_host *msm_host)
अणु
	पूर्णांक ret;

	DBG("Set clk rates: pclk=%d, byteclk=%d",
		msm_host->mode->घड़ी, msm_host->byte_clk_rate);

	ret = dev_pm_opp_set_rate(&msm_host->pdev->dev,
				  msm_host->byte_clk_rate);
	अगर (ret) अणु
		pr_err("%s: dev_pm_opp_set_rate failed %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(msm_host->pixel_clk, msm_host->pixel_clk_rate);
	अगर (ret) अणु
		pr_err("%s: Failed to set rate pixel clk, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	अगर (msm_host->byte_पूर्णांकf_clk) अणु
		ret = clk_set_rate(msm_host->byte_पूर्णांकf_clk,
				   msm_host->byte_clk_rate / 2);
		अगर (ret) अणु
			pr_err("%s: Failed to set rate byte intf clk, %d\n",
			       __func__, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक dsi_link_clk_enable_6g(काष्ठा msm_dsi_host *msm_host)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(msm_host->esc_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi esc clk\n", __func__);
		जाओ error;
	पूर्ण

	ret = clk_prepare_enable(msm_host->byte_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi byte clk\n", __func__);
		जाओ byte_clk_err;
	पूर्ण

	ret = clk_prepare_enable(msm_host->pixel_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi pixel clk\n", __func__);
		जाओ pixel_clk_err;
	पूर्ण

	अगर (msm_host->byte_पूर्णांकf_clk) अणु
		ret = clk_prepare_enable(msm_host->byte_पूर्णांकf_clk);
		अगर (ret) अणु
			pr_err("%s: Failed to enable byte intf clk\n",
			       __func__);
			जाओ byte_पूर्णांकf_clk_err;
		पूर्ण
	पूर्ण

	वापस 0;

byte_पूर्णांकf_clk_err:
	clk_disable_unprepare(msm_host->pixel_clk);
pixel_clk_err:
	clk_disable_unprepare(msm_host->byte_clk);
byte_clk_err:
	clk_disable_unprepare(msm_host->esc_clk);
error:
	वापस ret;
पूर्ण

पूर्णांक dsi_link_clk_set_rate_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	पूर्णांक ret;

	DBG("Set clk rates: pclk=%d, byteclk=%d, esc_clk=%d, dsi_src_clk=%d",
		msm_host->mode->घड़ी, msm_host->byte_clk_rate,
		msm_host->esc_clk_rate, msm_host->src_clk_rate);

	ret = clk_set_rate(msm_host->byte_clk, msm_host->byte_clk_rate);
	अगर (ret) अणु
		pr_err("%s: Failed to set rate byte clk, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(msm_host->esc_clk, msm_host->esc_clk_rate);
	अगर (ret) अणु
		pr_err("%s: Failed to set rate esc clk, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(msm_host->src_clk, msm_host->src_clk_rate);
	अगर (ret) अणु
		pr_err("%s: Failed to set rate src clk, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(msm_host->pixel_clk, msm_host->pixel_clk_rate);
	अगर (ret) अणु
		pr_err("%s: Failed to set rate pixel clk, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dsi_link_clk_enable_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(msm_host->byte_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi byte clk\n", __func__);
		जाओ error;
	पूर्ण

	ret = clk_prepare_enable(msm_host->esc_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi esc clk\n", __func__);
		जाओ esc_clk_err;
	पूर्ण

	ret = clk_prepare_enable(msm_host->src_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi src clk\n", __func__);
		जाओ src_clk_err;
	पूर्ण

	ret = clk_prepare_enable(msm_host->pixel_clk);
	अगर (ret) अणु
		pr_err("%s: Failed to enable dsi pixel clk\n", __func__);
		जाओ pixel_clk_err;
	पूर्ण

	वापस 0;

pixel_clk_err:
	clk_disable_unprepare(msm_host->src_clk);
src_clk_err:
	clk_disable_unprepare(msm_host->esc_clk);
esc_clk_err:
	clk_disable_unprepare(msm_host->byte_clk);
error:
	वापस ret;
पूर्ण

व्योम dsi_link_clk_disable_6g(काष्ठा msm_dsi_host *msm_host)
अणु
	/* Drop the perक्रमmance state vote */
	dev_pm_opp_set_rate(&msm_host->pdev->dev, 0);
	clk_disable_unprepare(msm_host->esc_clk);
	clk_disable_unprepare(msm_host->pixel_clk);
	अगर (msm_host->byte_पूर्णांकf_clk)
		clk_disable_unprepare(msm_host->byte_पूर्णांकf_clk);
	clk_disable_unprepare(msm_host->byte_clk);
पूर्ण

व्योम dsi_link_clk_disable_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	clk_disable_unprepare(msm_host->pixel_clk);
	clk_disable_unprepare(msm_host->src_clk);
	clk_disable_unprepare(msm_host->esc_clk);
	clk_disable_unprepare(msm_host->byte_clk);
पूर्ण

अटल u32 dsi_get_pclk_rate(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi)
अणु
	काष्ठा drm_display_mode *mode = msm_host->mode;
	u32 pclk_rate;

	pclk_rate = mode->घड़ी * 1000;

	/*
	 * For dual DSI mode, the current DRM mode has the complete width of the
	 * panel. Since, the complete panel is driven by two DSI controllers,
	 * the घड़ी rates have to be split between the two dsi controllers.
	 * Adjust the byte and pixel घड़ी rates क्रम each dsi host accordingly.
	 */
	अगर (is_dual_dsi)
		pclk_rate /= 2;

	वापस pclk_rate;
पूर्ण

अटल व्योम dsi_calc_pclk(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi)
अणु
	u8 lanes = msm_host->lanes;
	u32 bpp = dsi_get_bpp(msm_host->क्रमmat);
	u32 pclk_rate = dsi_get_pclk_rate(msm_host, is_dual_dsi);
	u64 pclk_bpp = (u64)pclk_rate * bpp;

	अगर (lanes == 0) अणु
		pr_err("%s: forcing mdss_dsi lanes to 1\n", __func__);
		lanes = 1;
	पूर्ण

	करो_भाग(pclk_bpp, (8 * lanes));

	msm_host->pixel_clk_rate = pclk_rate;
	msm_host->byte_clk_rate = pclk_bpp;

	DBG("pclk=%d, bclk=%d", msm_host->pixel_clk_rate,
				msm_host->byte_clk_rate);

पूर्ण

पूर्णांक dsi_calc_clk_rate_6g(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi)
अणु
	अगर (!msm_host->mode) अणु
		pr_err("%s: mode not set\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dsi_calc_pclk(msm_host, is_dual_dsi);
	msm_host->esc_clk_rate = clk_get_rate(msm_host->esc_clk);
	वापस 0;
पूर्ण

पूर्णांक dsi_calc_clk_rate_v2(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi)
अणु
	u32 bpp = dsi_get_bpp(msm_host->क्रमmat);
	u64 pclk_bpp;
	अचिन्हित पूर्णांक esc_mhz, esc_भाग;
	अचिन्हित दीर्घ byte_mhz;

	dsi_calc_pclk(msm_host, is_dual_dsi);

	pclk_bpp = (u64)dsi_get_pclk_rate(msm_host, is_dual_dsi) * bpp;
	करो_भाग(pclk_bpp, 8);
	msm_host->src_clk_rate = pclk_bpp;

	/*
	 * esc घड़ी is byte घड़ी followed by a 4 bit भागider,
	 * we need to find an escape घड़ी frequency within the
	 * mipi DSI spec range within the maximum भागider limit
	 * We iterate here between an escape घड़ी frequencey
	 * between 20 Mhz to 5 Mhz and pick up the first one
	 * that can be supported by our भागider
	 */

	byte_mhz = msm_host->byte_clk_rate / 1000000;

	क्रम (esc_mhz = 20; esc_mhz >= 5; esc_mhz--) अणु
		esc_भाग = DIV_ROUND_UP(byte_mhz, esc_mhz);

		/*
		 * TODO: Ideally, we shouldn't know what sort of भागider
		 * is available in mmss_cc, we're just assuming that
		 * it'll always be a 4 bit भागider. Need to come up with
		 * a better way here.
		 */
		अगर (esc_भाग >= 1 && esc_भाग <= 16)
			अवरोध;
	पूर्ण

	अगर (esc_mhz < 5)
		वापस -EINVAL;

	msm_host->esc_clk_rate = msm_host->byte_clk_rate / esc_भाग;

	DBG("esc=%d, src=%d", msm_host->esc_clk_rate,
		msm_host->src_clk_rate);

	वापस 0;
पूर्ण

अटल व्योम dsi_पूर्णांकr_ctrl(काष्ठा msm_dsi_host *msm_host, u32 mask, पूर्णांक enable)
अणु
	u32 पूर्णांकr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msm_host->पूर्णांकr_lock, flags);
	पूर्णांकr = dsi_पढ़ो(msm_host, REG_DSI_INTR_CTRL);

	अगर (enable)
		पूर्णांकr |= mask;
	अन्यथा
		पूर्णांकr &= ~mask;

	DBG("intr=%x enable=%d", पूर्णांकr, enable);

	dsi_ग_लिखो(msm_host, REG_DSI_INTR_CTRL, पूर्णांकr);
	spin_unlock_irqrestore(&msm_host->पूर्णांकr_lock, flags);
पूर्ण

अटल अंतरभूत क्रमागत dsi_traffic_mode dsi_get_traffic_mode(स्थिर u32 mode_flags)
अणु
	अगर (mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		वापस BURST_MODE;
	अन्यथा अगर (mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		वापस NON_BURST_SYNCH_PULSE;

	वापस NON_BURST_SYNCH_EVENT;
पूर्ण

अटल अंतरभूत क्रमागत dsi_vid_dst_क्रमmat dsi_get_vid_fmt(
				स्थिर क्रमागत mipi_dsi_pixel_क्रमmat mipi_fmt)
अणु
	चयन (mipi_fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:	वापस VID_DST_FORMAT_RGB888;
	हाल MIPI_DSI_FMT_RGB666:	वापस VID_DST_FORMAT_RGB666_LOOSE;
	हाल MIPI_DSI_FMT_RGB666_PACKED:	वापस VID_DST_FORMAT_RGB666;
	हाल MIPI_DSI_FMT_RGB565:	वापस VID_DST_FORMAT_RGB565;
	शेष:			वापस VID_DST_FORMAT_RGB888;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत dsi_cmd_dst_क्रमmat dsi_get_cmd_fmt(
				स्थिर क्रमागत mipi_dsi_pixel_क्रमmat mipi_fmt)
अणु
	चयन (mipi_fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:	वापस CMD_DST_FORMAT_RGB888;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
	हाल MIPI_DSI_FMT_RGB666:	वापस CMD_DST_FORMAT_RGB666;
	हाल MIPI_DSI_FMT_RGB565:	वापस CMD_DST_FORMAT_RGB565;
	शेष:			वापस CMD_DST_FORMAT_RGB888;
	पूर्ण
पूर्ण

अटल व्योम dsi_ctrl_config(काष्ठा msm_dsi_host *msm_host, bool enable,
			काष्ठा msm_dsi_phy_shared_timings *phy_shared_timings)
अणु
	u32 flags = msm_host->mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat mipi_fmt = msm_host->क्रमmat;
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	u32 data = 0, lane_ctrl = 0;

	अगर (!enable) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_CTRL, 0);
		वापस;
	पूर्ण

	अगर (flags & MIPI_DSI_MODE_VIDEO) अणु
		अगर (flags & MIPI_DSI_MODE_VIDEO_HSE)
			data |= DSI_VID_CFG0_PULSE_MODE_HSA_HE;
		अगर (flags & MIPI_DSI_MODE_VIDEO_HFP)
			data |= DSI_VID_CFG0_HFP_POWER_STOP;
		अगर (flags & MIPI_DSI_MODE_VIDEO_HBP)
			data |= DSI_VID_CFG0_HBP_POWER_STOP;
		अगर (flags & MIPI_DSI_MODE_VIDEO_HSA)
			data |= DSI_VID_CFG0_HSA_POWER_STOP;
		/* Always set low घातer stop mode क्रम BLLP
		 * to let command engine send packets
		 */
		data |= DSI_VID_CFG0_खातापूर्ण_BLLP_POWER_STOP |
			DSI_VID_CFG0_BLLP_POWER_STOP;
		data |= DSI_VID_CFG0_TRAFFIC_MODE(dsi_get_traffic_mode(flags));
		data |= DSI_VID_CFG0_DST_FORMAT(dsi_get_vid_fmt(mipi_fmt));
		data |= DSI_VID_CFG0_VIRT_CHANNEL(msm_host->channel);
		dsi_ग_लिखो(msm_host, REG_DSI_VID_CFG0, data);

		/* Do not swap RGB colors */
		data = DSI_VID_CFG1_RGB_SWAP(SWAP_RGB);
		dsi_ग_लिखो(msm_host, REG_DSI_VID_CFG1, 0);
	पूर्ण अन्यथा अणु
		/* Do not swap RGB colors */
		data = DSI_CMD_CFG0_RGB_SWAP(SWAP_RGB);
		data |= DSI_CMD_CFG0_DST_FORMAT(dsi_get_cmd_fmt(mipi_fmt));
		dsi_ग_लिखो(msm_host, REG_DSI_CMD_CFG0, data);

		data = DSI_CMD_CFG1_WR_MEM_START(MIPI_DCS_WRITE_MEMORY_START) |
			DSI_CMD_CFG1_WR_MEM_CONTINUE(
					MIPI_DCS_WRITE_MEMORY_CONTINUE);
		/* Always insert DCS command */
		data |= DSI_CMD_CFG1_INSERT_DCS_COMMAND;
		dsi_ग_लिखो(msm_host, REG_DSI_CMD_CFG1, data);
	पूर्ण

	dsi_ग_लिखो(msm_host, REG_DSI_CMD_DMA_CTRL,
			DSI_CMD_DMA_CTRL_FROM_FRAME_BUFFER |
			DSI_CMD_DMA_CTRL_LOW_POWER);

	data = 0;
	/* Always assume dedicated TE pin */
	data |= DSI_TRIG_CTRL_TE;
	data |= DSI_TRIG_CTRL_MDP_TRIGGER(TRIGGER_NONE);
	data |= DSI_TRIG_CTRL_DMA_TRIGGER(TRIGGER_SW);
	data |= DSI_TRIG_CTRL_STREAM(msm_host->channel);
	अगर ((cfg_hnd->major == MSM_DSI_VER_MAJOR_6G) &&
		(cfg_hnd->minor >= MSM_DSI_6G_VER_MINOR_V1_2))
		data |= DSI_TRIG_CTRL_BLOCK_DMA_WITHIN_FRAME;
	dsi_ग_लिखो(msm_host, REG_DSI_TRIG_CTRL, data);

	data = DSI_CLKOUT_TIMING_CTRL_T_CLK_POST(phy_shared_timings->clk_post) |
		DSI_CLKOUT_TIMING_CTRL_T_CLK_PRE(phy_shared_timings->clk_pre);
	dsi_ग_लिखो(msm_host, REG_DSI_CLKOUT_TIMING_CTRL, data);

	अगर ((cfg_hnd->major == MSM_DSI_VER_MAJOR_6G) &&
	    (cfg_hnd->minor > MSM_DSI_6G_VER_MINOR_V1_0) &&
	    phy_shared_timings->clk_pre_inc_by_2)
		dsi_ग_लिखो(msm_host, REG_DSI_T_CLK_PRE_EXTEND,
			  DSI_T_CLK_PRE_EXTEND_INC_BY_2_BYTECLK);

	data = 0;
	अगर (!(flags & MIPI_DSI_MODE_EOT_PACKET))
		data |= DSI_EOT_PACKET_CTRL_TX_EOT_APPEND;
	dsi_ग_लिखो(msm_host, REG_DSI_EOT_PACKET_CTRL, data);

	/* allow only ack-err-status to generate पूर्णांकerrupt */
	dsi_ग_लिखो(msm_host, REG_DSI_ERR_INT_MASK0, 0x13ff3fe0);

	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_ERROR, 1);

	dsi_ग_लिखो(msm_host, REG_DSI_CLK_CTRL, DSI_CLK_CTRL_ENABLE_CLKS);

	data = DSI_CTRL_CLK_EN;

	DBG("lane number=%d", msm_host->lanes);
	data |= ((DSI_CTRL_LANE0 << msm_host->lanes) - DSI_CTRL_LANE0);

	dsi_ग_लिखो(msm_host, REG_DSI_LANE_SWAP_CTRL,
		  DSI_LANE_SWAP_CTRL_DLN_SWAP_SEL(msm_host->dlane_swap));

	अगर (!(flags & MIPI_DSI_CLOCK_NON_CONTINUOUS)) अणु
		lane_ctrl = dsi_पढ़ो(msm_host, REG_DSI_LANE_CTRL);
		dsi_ग_लिखो(msm_host, REG_DSI_LANE_CTRL,
			lane_ctrl | DSI_LANE_CTRL_CLKLN_HS_FORCE_REQUEST);
	पूर्ण

	data |= DSI_CTRL_ENABLE;

	dsi_ग_लिखो(msm_host, REG_DSI_CTRL, data);
पूर्ण

अटल व्योम dsi_timing_setup(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi)
अणु
	काष्ठा drm_display_mode *mode = msm_host->mode;
	u32 hs_start = 0, vs_start = 0; /* take sync start as 0 */
	u32 h_total = mode->htotal;
	u32 v_total = mode->vtotal;
	u32 hs_end = mode->hsync_end - mode->hsync_start;
	u32 vs_end = mode->vsync_end - mode->vsync_start;
	u32 ha_start = h_total - mode->hsync_start;
	u32 ha_end = ha_start + mode->hdisplay;
	u32 बहु_शुरू = v_total - mode->vsync_start;
	u32 बहु_पूर्ण = बहु_शुरू + mode->vdisplay;
	u32 hdisplay = mode->hdisplay;
	u32 wc;

	DBG("");

	/*
	 * For dual DSI mode, the current DRM mode has
	 * the complete width of the panel. Since, the complete
	 * panel is driven by two DSI controllers, the horizontal
	 * timings have to be split between the two dsi controllers.
	 * Adjust the DSI host timing values accordingly.
	 */
	अगर (is_dual_dsi) अणु
		h_total /= 2;
		hs_end /= 2;
		ha_start /= 2;
		ha_end /= 2;
		hdisplay /= 2;
	पूर्ण

	अगर (msm_host->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_ACTIVE_H,
			DSI_ACTIVE_H_START(ha_start) |
			DSI_ACTIVE_H_END(ha_end));
		dsi_ग_लिखो(msm_host, REG_DSI_ACTIVE_V,
			DSI_ACTIVE_V_START(बहु_शुरू) |
			DSI_ACTIVE_V_END(बहु_पूर्ण));
		dsi_ग_लिखो(msm_host, REG_DSI_TOTAL,
			DSI_TOTAL_H_TOTAL(h_total - 1) |
			DSI_TOTAL_V_TOTAL(v_total - 1));

		dsi_ग_लिखो(msm_host, REG_DSI_ACTIVE_HSYNC,
			DSI_ACTIVE_HSYNC_START(hs_start) |
			DSI_ACTIVE_HSYNC_END(hs_end));
		dsi_ग_लिखो(msm_host, REG_DSI_ACTIVE_VSYNC_HPOS, 0);
		dsi_ग_लिखो(msm_host, REG_DSI_ACTIVE_VSYNC_VPOS,
			DSI_ACTIVE_VSYNC_VPOS_START(vs_start) |
			DSI_ACTIVE_VSYNC_VPOS_END(vs_end));
	पूर्ण अन्यथा अणु		/* command mode */
		/* image data and 1 byte ग_लिखो_memory_start cmd */
		wc = hdisplay * dsi_get_bpp(msm_host->क्रमmat) / 8 + 1;

		dsi_ग_लिखो(msm_host, REG_DSI_CMD_MDP_STREAM0_CTRL,
			DSI_CMD_MDP_STREAM0_CTRL_WORD_COUNT(wc) |
			DSI_CMD_MDP_STREAM0_CTRL_VIRTUAL_CHANNEL(
					msm_host->channel) |
			DSI_CMD_MDP_STREAM0_CTRL_DATA_TYPE(
					MIPI_DSI_DCS_LONG_WRITE));

		dsi_ग_लिखो(msm_host, REG_DSI_CMD_MDP_STREAM0_TOTAL,
			DSI_CMD_MDP_STREAM0_TOTAL_H_TOTAL(hdisplay) |
			DSI_CMD_MDP_STREAM0_TOTAL_V_TOTAL(mode->vdisplay));
	पूर्ण
पूर्ण

अटल व्योम dsi_sw_reset(काष्ठा msm_dsi_host *msm_host)
अणु
	dsi_ग_लिखो(msm_host, REG_DSI_CLK_CTRL, DSI_CLK_CTRL_ENABLE_CLKS);
	wmb(); /* घड़ीs need to be enabled beक्रमe reset */

	dsi_ग_लिखो(msm_host, REG_DSI_RESET, 1);
	msleep(DSI_RESET_TOGGLE_DELAY_MS); /* make sure reset happen */
	dsi_ग_लिखो(msm_host, REG_DSI_RESET, 0);
पूर्ण

अटल व्योम dsi_op_mode_config(काष्ठा msm_dsi_host *msm_host,
					bool video_mode, bool enable)
अणु
	u32 dsi_ctrl;

	dsi_ctrl = dsi_पढ़ो(msm_host, REG_DSI_CTRL);

	अगर (!enable) अणु
		dsi_ctrl &= ~(DSI_CTRL_ENABLE | DSI_CTRL_VID_MODE_EN |
				DSI_CTRL_CMD_MODE_EN);
		dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_CMD_MDP_DONE |
					DSI_IRQ_MASK_VIDEO_DONE, 0);
	पूर्ण अन्यथा अणु
		अगर (video_mode) अणु
			dsi_ctrl |= DSI_CTRL_VID_MODE_EN;
		पूर्ण अन्यथा अणु		/* command mode */
			dsi_ctrl |= DSI_CTRL_CMD_MODE_EN;
			dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_CMD_MDP_DONE, 1);
		पूर्ण
		dsi_ctrl |= DSI_CTRL_ENABLE;
	पूर्ण

	dsi_ग_लिखो(msm_host, REG_DSI_CTRL, dsi_ctrl);
पूर्ण

अटल व्योम dsi_set_tx_घातer_mode(पूर्णांक mode, काष्ठा msm_dsi_host *msm_host)
अणु
	u32 data;

	data = dsi_पढ़ो(msm_host, REG_DSI_CMD_DMA_CTRL);

	अगर (mode == 0)
		data &= ~DSI_CMD_DMA_CTRL_LOW_POWER;
	अन्यथा
		data |= DSI_CMD_DMA_CTRL_LOW_POWER;

	dsi_ग_लिखो(msm_host, REG_DSI_CMD_DMA_CTRL, data);
पूर्ण

अटल व्योम dsi_रुको4video_करोne(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 ret = 0;
	काष्ठा device *dev = &msm_host->pdev->dev;

	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_VIDEO_DONE, 1);

	reinit_completion(&msm_host->video_comp);

	ret = रुको_क्रम_completion_समयout(&msm_host->video_comp,
			msecs_to_jअगरfies(70));

	अगर (ret == 0)
		DRM_DEV_ERROR(dev, "wait for video done timed out\n");

	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_VIDEO_DONE, 0);
पूर्ण

अटल व्योम dsi_रुको4video_eng_busy(काष्ठा msm_dsi_host *msm_host)
अणु
	अगर (!(msm_host->mode_flags & MIPI_DSI_MODE_VIDEO))
		वापस;

	अगर (msm_host->घातer_on && msm_host->enabled) अणु
		dsi_रुको4video_करोne(msm_host);
		/* delay 4 ms to skip BLLP */
		usleep_range(2000, 4000);
	पूर्ण
पूर्ण

पूर्णांक dsi_tx_buf_alloc_6g(काष्ठा msm_dsi_host *msm_host, पूर्णांक size)
अणु
	काष्ठा drm_device *dev = msm_host->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	uपूर्णांक64_t iova;
	u8 *data;

	data = msm_gem_kernel_new(dev, size, MSM_BO_UNCACHED,
					priv->kms->aspace,
					&msm_host->tx_gem_obj, &iova);

	अगर (IS_ERR(data)) अणु
		msm_host->tx_gem_obj = शून्य;
		वापस PTR_ERR(data);
	पूर्ण

	msm_gem_object_set_name(msm_host->tx_gem_obj, "tx_gem");

	msm_host->tx_size = msm_host->tx_gem_obj->size;

	वापस 0;
पूर्ण

पूर्णांक dsi_tx_buf_alloc_v2(काष्ठा msm_dsi_host *msm_host, पूर्णांक size)
अणु
	काष्ठा drm_device *dev = msm_host->dev;

	msm_host->tx_buf = dma_alloc_coherent(dev->dev, size,
					&msm_host->tx_buf_paddr, GFP_KERNEL);
	अगर (!msm_host->tx_buf)
		वापस -ENOMEM;

	msm_host->tx_size = size;

	वापस 0;
पूर्ण

अटल व्योम dsi_tx_buf_मुक्त(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा drm_device *dev = msm_host->dev;
	काष्ठा msm_drm_निजी *priv;

	/*
	 * This is possible अगर we're tearing down before we've had a chance to
	 * fully initialize. A very real possibility अगर our probe is deferred,
	 * in which हाल we'll hit msm_dsi_host_destroy() without having run
	 * through the dsi_tx_buf_alloc().
	 */
	अगर (!dev)
		वापस;

	priv = dev->dev_निजी;
	अगर (msm_host->tx_gem_obj) अणु
		msm_gem_unpin_iova(msm_host->tx_gem_obj, priv->kms->aspace);
		drm_gem_object_put(msm_host->tx_gem_obj);
		msm_host->tx_gem_obj = शून्य;
	पूर्ण

	अगर (msm_host->tx_buf)
		dma_मुक्त_coherent(dev->dev, msm_host->tx_size, msm_host->tx_buf,
			msm_host->tx_buf_paddr);
पूर्ण

व्योम *dsi_tx_buf_get_6g(काष्ठा msm_dsi_host *msm_host)
अणु
	वापस msm_gem_get_vaddr(msm_host->tx_gem_obj);
पूर्ण

व्योम *dsi_tx_buf_get_v2(काष्ठा msm_dsi_host *msm_host)
अणु
	वापस msm_host->tx_buf;
पूर्ण

व्योम dsi_tx_buf_put_6g(काष्ठा msm_dsi_host *msm_host)
अणु
	msm_gem_put_vaddr(msm_host->tx_gem_obj);
पूर्ण

/*
 * prepare cmd buffer to be txed
 */
अटल पूर्णांक dsi_cmd_dma_add(काष्ठा msm_dsi_host *msm_host,
			   स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	काष्ठा mipi_dsi_packet packet;
	पूर्णांक len;
	पूर्णांक ret;
	u8 *data;

	ret = mipi_dsi_create_packet(&packet, msg);
	अगर (ret) अणु
		pr_err("%s: create packet failed, %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	len = (packet.size + 3) & (~0x3);

	अगर (len > msm_host->tx_size) अणु
		pr_err("%s: packet size is too big\n", __func__);
		वापस -EINVAL;
	पूर्ण

	data = cfg_hnd->ops->tx_buf_get(msm_host);
	अगर (IS_ERR(data)) अणु
		ret = PTR_ERR(data);
		pr_err("%s: get vaddr failed, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/* MSM specअगरic command क्रमmat in memory */
	data[0] = packet.header[1];
	data[1] = packet.header[2];
	data[2] = packet.header[0];
	data[3] = BIT(7); /* Last packet */
	अगर (mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type))
		data[3] |= BIT(6);
	अगर (msg->rx_buf && msg->rx_len)
		data[3] |= BIT(5);

	/* Long packet */
	अगर (packet.payload && packet.payload_length)
		स_नकल(data + 4, packet.payload, packet.payload_length);

	/* Append 0xff to the end */
	अगर (packet.size < len)
		स_रखो(data + packet.size, 0xff, len - packet.size);

	अगर (cfg_hnd->ops->tx_buf_put)
		cfg_hnd->ops->tx_buf_put(msm_host);

	वापस len;
पूर्ण

/*
 * dsi_लघु_पढ़ो1_resp: 1 parameter
 */
अटल पूर्णांक dsi_लघु_पढ़ो1_resp(u8 *buf, स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	u8 *data = msg->rx_buf;
	अगर (data && (msg->rx_len >= 1)) अणु
		*data = buf[1]; /* strip out dcs type */
		वापस 1;
	पूर्ण अन्यथा अणु
		pr_err("%s: read data does not match with rx_buf len %zu\n",
			__func__, msg->rx_len);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * dsi_लघु_पढ़ो2_resp: 2 parameter
 */
अटल पूर्णांक dsi_लघु_पढ़ो2_resp(u8 *buf, स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	u8 *data = msg->rx_buf;
	अगर (data && (msg->rx_len >= 2)) अणु
		data[0] = buf[1]; /* strip out dcs type */
		data[1] = buf[2];
		वापस 2;
	पूर्ण अन्यथा अणु
		pr_err("%s: read data does not match with rx_buf len %zu\n",
			__func__, msg->rx_len);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dsi_दीर्घ_पढ़ो_resp(u8 *buf, स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	/* strip out 4 byte dcs header */
	अगर (msg->rx_buf && msg->rx_len)
		स_नकल(msg->rx_buf, buf + 4, msg->rx_len);

	वापस msg->rx_len;
पूर्ण

पूर्णांक dsi_dma_base_get_6g(काष्ठा msm_dsi_host *msm_host, uपूर्णांक64_t *dma_base)
अणु
	काष्ठा drm_device *dev = msm_host->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	अगर (!dma_base)
		वापस -EINVAL;

	वापस msm_gem_get_and_pin_iova(msm_host->tx_gem_obj,
				priv->kms->aspace, dma_base);
पूर्ण

पूर्णांक dsi_dma_base_get_v2(काष्ठा msm_dsi_host *msm_host, uपूर्णांक64_t *dma_base)
अणु
	अगर (!dma_base)
		वापस -EINVAL;

	*dma_base = msm_host->tx_buf_paddr;
	वापस 0;
पूर्ण

अटल पूर्णांक dsi_cmd_dma_tx(काष्ठा msm_dsi_host *msm_host, पूर्णांक len)
अणु
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	पूर्णांक ret;
	uपूर्णांक64_t dma_base;
	bool triggered;

	ret = cfg_hnd->ops->dma_base_get(msm_host, &dma_base);
	अगर (ret) अणु
		pr_err("%s: failed to get iova: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	reinit_completion(&msm_host->dma_comp);

	dsi_रुको4video_eng_busy(msm_host);

	triggered = msm_dsi_manager_cmd_xfer_trigger(
						msm_host->id, dma_base, len);
	अगर (triggered) अणु
		ret = रुको_क्रम_completion_समयout(&msm_host->dma_comp,
					msecs_to_jअगरfies(200));
		DBG("ret=%d", ret);
		अगर (ret == 0)
			ret = -ETIMEDOUT;
		अन्यथा
			ret = len;
	पूर्ण अन्यथा
		ret = len;

	वापस ret;
पूर्ण

अटल पूर्णांक dsi_cmd_dma_rx(काष्ठा msm_dsi_host *msm_host,
			u8 *buf, पूर्णांक rx_byte, पूर्णांक pkt_size)
अणु
	u32 *temp, data;
	पूर्णांक i, j = 0, cnt;
	u32 पढ़ो_cnt;
	u8 reg[16];
	पूर्णांक repeated_bytes = 0;
	पूर्णांक buf_offset = buf - msm_host->rx_buf;

	temp = (u32 *)reg;
	cnt = (rx_byte + 3) >> 2;
	अगर (cnt > 4)
		cnt = 4; /* 4 x 32 bits रेजिस्टरs only */

	अगर (rx_byte == 4)
		पढ़ो_cnt = 4;
	अन्यथा
		पढ़ो_cnt = pkt_size + 6;

	/*
	 * In हाल of multiple पढ़ोs from the panel, after the first पढ़ो, there
	 * is possibility that there are some bytes in the payload repeating in
	 * the RDBK_DATA रेजिस्टरs. Since we पढ़ो all the parameters from the
	 * panel right from the first byte क्रम every pass. We need to skip the
	 * repeating bytes and then append the new parameters to the rx buffer.
	 */
	अगर (पढ़ो_cnt > 16) अणु
		पूर्णांक bytes_shअगरted;
		/* Any data more than 16 bytes will be shअगरted out.
		 * The temp पढ़ो buffer should alपढ़ोy contain these bytes.
		 * The reमुख्यing bytes in पढ़ो buffer are the repeated bytes.
		 */
		bytes_shअगरted = पढ़ो_cnt - 16;
		repeated_bytes = buf_offset - bytes_shअगरted;
	पूर्ण

	क्रम (i = cnt - 1; i >= 0; i--) अणु
		data = dsi_पढ़ो(msm_host, REG_DSI_RDBK_DATA(i));
		*temp++ = ntohl(data); /* to host byte order */
		DBG("data = 0x%x and ntohl(data) = 0x%x", data, ntohl(data));
	पूर्ण

	क्रम (i = repeated_bytes; i < 16; i++)
		buf[j++] = reg[i];

	वापस j;
पूर्ण

अटल पूर्णांक dsi_cmds2buf_tx(काष्ठा msm_dsi_host *msm_host,
				स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	पूर्णांक len, ret;
	पूर्णांक bllp_len = msm_host->mode->hdisplay *
			dsi_get_bpp(msm_host->क्रमmat) / 8;

	len = dsi_cmd_dma_add(msm_host, msg);
	अगर (!len) अणु
		pr_err("%s: failed to add cmd type = 0x%x\n",
			__func__,  msg->type);
		वापस -EINVAL;
	पूर्ण

	/* क्रम video mode, करो not send cmds more than
	* one pixel line, since it only transmit it
	* during BLLP.
	*/
	/* TODO: अगर the command is sent in LP mode, the bit rate is only
	 * half of esc clk rate. In this हाल, अगर the video is alपढ़ोy
	 * actively streaming, we need to check more carefully अगर the
	 * command can be fit पूर्णांकo one BLLP.
	 */
	अगर ((msm_host->mode_flags & MIPI_DSI_MODE_VIDEO) && (len > bllp_len)) अणु
		pr_err("%s: cmd cannot fit into BLLP period, len=%d\n",
			__func__, len);
		वापस -EINVAL;
	पूर्ण

	ret = dsi_cmd_dma_tx(msm_host, len);
	अगर (ret < len) अणु
		pr_err("%s: cmd dma tx failed, type=0x%x, data0=0x%x, len=%d\n",
			__func__, msg->type, (*(u8 *)(msg->tx_buf)), len);
		वापस -ECOMM;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम dsi_sw_reset_restore(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 data0, data1;

	data0 = dsi_पढ़ो(msm_host, REG_DSI_CTRL);
	data1 = data0;
	data1 &= ~DSI_CTRL_ENABLE;
	dsi_ग_लिखो(msm_host, REG_DSI_CTRL, data1);
	/*
	 * dsi controller need to be disabled beक्रमe
	 * घड़ीs turned on
	 */
	wmb();

	dsi_ग_लिखो(msm_host, REG_DSI_CLK_CTRL, DSI_CLK_CTRL_ENABLE_CLKS);
	wmb();	/* make sure घड़ीs enabled */

	/* dsi controller can only be reset जबतक घड़ीs are running */
	dsi_ग_लिखो(msm_host, REG_DSI_RESET, 1);
	msleep(DSI_RESET_TOGGLE_DELAY_MS); /* make sure reset happen */
	dsi_ग_लिखो(msm_host, REG_DSI_RESET, 0);
	wmb();	/* controller out of reset */
	dsi_ग_लिखो(msm_host, REG_DSI_CTRL, data0);
	wmb();	/* make sure dsi controller enabled again */
पूर्ण

अटल व्योम dsi_hpd_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msm_dsi_host *msm_host =
		container_of(work, काष्ठा msm_dsi_host, hpd_work);

	drm_helper_hpd_irq_event(msm_host->dev);
पूर्ण

अटल व्योम dsi_err_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msm_dsi_host *msm_host =
		container_of(work, काष्ठा msm_dsi_host, err_work);
	u32 status = msm_host->err_work_state;

	pr_err_ratelimited("%s: status=%x\n", __func__, status);
	अगर (status & DSI_ERR_STATE_MDP_FIFO_UNDERFLOW)
		dsi_sw_reset_restore(msm_host);

	/* It is safe to clear here because error irq is disabled. */
	msm_host->err_work_state = 0;

	/* enable dsi error पूर्णांकerrupt */
	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_ERROR, 1);
पूर्ण

अटल व्योम dsi_ack_err_status(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_ACK_ERR_STATUS);

	अगर (status) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_ACK_ERR_STATUS, status);
		/* Writing of an extra 0 needed to clear error bits */
		dsi_ग_लिखो(msm_host, REG_DSI_ACK_ERR_STATUS, 0);
		msm_host->err_work_state |= DSI_ERR_STATE_ACK;
	पूर्ण
पूर्ण

अटल व्योम dsi_समयout_status(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_TIMEOUT_STATUS);

	अगर (status) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_TIMEOUT_STATUS, status);
		msm_host->err_work_state |= DSI_ERR_STATE_TIMEOUT;
	पूर्ण
पूर्ण

अटल व्योम dsi_dln0_phy_err(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_DLN0_PHY_ERR);

	अगर (status & (DSI_DLN0_PHY_ERR_DLN0_ERR_ESC |
			DSI_DLN0_PHY_ERR_DLN0_ERR_SYNC_ESC |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTROL |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP0 |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP1)) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_DLN0_PHY_ERR, status);
		msm_host->err_work_state |= DSI_ERR_STATE_DLN0_PHY;
	पूर्ण
पूर्ण

अटल व्योम dsi_fअगरo_status(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_FIFO_STATUS);

	/* fअगरo underflow, overflow */
	अगर (status) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_FIFO_STATUS, status);
		msm_host->err_work_state |= DSI_ERR_STATE_FIFO;
		अगर (status & DSI_FIFO_STATUS_CMD_MDP_FIFO_UNDERFLOW)
			msm_host->err_work_state |=
					DSI_ERR_STATE_MDP_FIFO_UNDERFLOW;
	पूर्ण
पूर्ण

अटल व्योम dsi_status(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_STATUS0);

	अगर (status & DSI_STATUS0_INTERLEAVE_OP_CONTENTION) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_STATUS0, status);
		msm_host->err_work_state |=
			DSI_ERR_STATE_INTERLEAVE_OP_CONTENTION;
	पूर्ण
पूर्ण

अटल व्योम dsi_clk_status(काष्ठा msm_dsi_host *msm_host)
अणु
	u32 status;

	status = dsi_पढ़ो(msm_host, REG_DSI_CLK_STATUS);

	अगर (status & DSI_CLK_STATUS_PLL_UNLOCKED) अणु
		dsi_ग_लिखो(msm_host, REG_DSI_CLK_STATUS, status);
		msm_host->err_work_state |= DSI_ERR_STATE_PLL_UNLOCKED;
	पूर्ण
पूर्ण

अटल व्योम dsi_error(काष्ठा msm_dsi_host *msm_host)
अणु
	/* disable dsi error पूर्णांकerrupt */
	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_ERROR, 0);

	dsi_clk_status(msm_host);
	dsi_fअगरo_status(msm_host);
	dsi_ack_err_status(msm_host);
	dsi_समयout_status(msm_host);
	dsi_status(msm_host);
	dsi_dln0_phy_err(msm_host);

	queue_work(msm_host->workqueue, &msm_host->err_work);
पूर्ण

अटल irqवापस_t dsi_host_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा msm_dsi_host *msm_host = ptr;
	u32 isr;
	अचिन्हित दीर्घ flags;

	अगर (!msm_host->ctrl_base)
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&msm_host->पूर्णांकr_lock, flags);
	isr = dsi_पढ़ो(msm_host, REG_DSI_INTR_CTRL);
	dsi_ग_लिखो(msm_host, REG_DSI_INTR_CTRL, isr);
	spin_unlock_irqrestore(&msm_host->पूर्णांकr_lock, flags);

	DBG("isr=0x%x, id=%d", isr, msm_host->id);

	अगर (isr & DSI_IRQ_ERROR)
		dsi_error(msm_host);

	अगर (isr & DSI_IRQ_VIDEO_DONE)
		complete(&msm_host->video_comp);

	अगर (isr & DSI_IRQ_CMD_DMA_DONE)
		complete(&msm_host->dma_comp);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dsi_host_init_panel_gpios(काष्ठा msm_dsi_host *msm_host,
			काष्ठा device *panel_device)
अणु
	msm_host->disp_en_gpio = devm_gpiod_get_optional(panel_device,
							 "disp-enable",
							 GPIOD_OUT_LOW);
	अगर (IS_ERR(msm_host->disp_en_gpio)) अणु
		DBG("cannot get disp-enable-gpios %ld",
				PTR_ERR(msm_host->disp_en_gpio));
		वापस PTR_ERR(msm_host->disp_en_gpio);
	पूर्ण

	msm_host->te_gpio = devm_gpiod_get_optional(panel_device, "disp-te",
								GPIOD_IN);
	अगर (IS_ERR(msm_host->te_gpio)) अणु
		DBG("cannot get disp-te-gpios %ld", PTR_ERR(msm_host->te_gpio));
		वापस PTR_ERR(msm_host->te_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_host_attach(काष्ठा mipi_dsi_host *host,
					काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	पूर्णांक ret;

	अगर (dsi->lanes > msm_host->num_data_lanes)
		वापस -EINVAL;

	msm_host->channel = dsi->channel;
	msm_host->lanes = dsi->lanes;
	msm_host->क्रमmat = dsi->क्रमmat;
	msm_host->mode_flags = dsi->mode_flags;

	/* Some gpios defined in panel DT need to be controlled by host */
	ret = dsi_host_init_panel_gpios(msm_host, &dsi->dev);
	अगर (ret)
		वापस ret;

	DBG("id=%d", msm_host->id);
	अगर (msm_host->dev)
		queue_work(msm_host->workqueue, &msm_host->hpd_work);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_host_detach(काष्ठा mipi_dsi_host *host,
					काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->device_node = शून्य;

	DBG("id=%d", msm_host->id);
	अगर (msm_host->dev)
		queue_work(msm_host->workqueue, &msm_host->hpd_work);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dsi_host_transfer(काष्ठा mipi_dsi_host *host,
					स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	पूर्णांक ret;

	अगर (!msg || !msm_host->घातer_on)
		वापस -EINVAL;

	mutex_lock(&msm_host->cmd_mutex);
	ret = msm_dsi_manager_cmd_xfer(msm_host->id, msg);
	mutex_unlock(&msm_host->cmd_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops dsi_host_ops = अणु
	.attach = dsi_host_attach,
	.detach = dsi_host_detach,
	.transfer = dsi_host_transfer,
पूर्ण;

/*
 * List of supported physical to logical lane mappings.
 * For example, the 2nd entry represents the following mapping:
 *
 * "3012": Logic 3->Phys 0; Logic 0->Phys 1; Logic 1->Phys 2; Logic 2->Phys 3;
 */
अटल स्थिर पूर्णांक supported_data_lane_swaps[][4] = अणु
	अणु 0, 1, 2, 3 पूर्ण,
	अणु 3, 0, 1, 2 पूर्ण,
	अणु 2, 3, 0, 1 पूर्ण,
	अणु 1, 2, 3, 0 पूर्ण,
	अणु 0, 3, 2, 1 पूर्ण,
	अणु 1, 0, 3, 2 पूर्ण,
	अणु 2, 1, 0, 3 पूर्ण,
	अणु 3, 2, 1, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक dsi_host_parse_lane_data(काष्ठा msm_dsi_host *msm_host,
				    काष्ठा device_node *ep)
अणु
	काष्ठा device *dev = &msm_host->pdev->dev;
	काष्ठा property *prop;
	u32 lane_map[4];
	पूर्णांक ret, i, len, num_lanes;

	prop = of_find_property(ep, "data-lanes", &len);
	अगर (!prop) अणु
		DRM_DEV_DEBUG(dev,
			"failed to find data lane mapping, using default\n");
		वापस 0;
	पूर्ण

	num_lanes = len / माप(u32);

	अगर (num_lanes < 1 || num_lanes > 4) अणु
		DRM_DEV_ERROR(dev, "bad number of data lanes\n");
		वापस -EINVAL;
	पूर्ण

	msm_host->num_data_lanes = num_lanes;

	ret = of_property_पढ़ो_u32_array(ep, "data-lanes", lane_map,
					 num_lanes);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to read lane data\n");
		वापस ret;
	पूर्ण

	/*
	 * compare DT specअगरied physical-logical lane mappings with the ones
	 * supported by hardware
	 */
	क्रम (i = 0; i < ARRAY_SIZE(supported_data_lane_swaps); i++) अणु
		स्थिर पूर्णांक *swap = supported_data_lane_swaps[i];
		पूर्णांक j;

		/*
		 * the data-lanes array we get from DT has a logical->physical
		 * mapping. The "data lane swap" रेजिस्टर field represents
		 * supported configurations in a physical->logical mapping.
		 * Translate the DT mapping to what we understand and find a
		 * configuration that works.
		 */
		क्रम (j = 0; j < num_lanes; j++) अणु
			अगर (lane_map[j] < 0 || lane_map[j] > 3)
				DRM_DEV_ERROR(dev, "bad physical lane entry %u\n",
					lane_map[j]);

			अगर (swap[lane_map[j]] != j)
				अवरोध;
		पूर्ण

		अगर (j == num_lanes) अणु
			msm_host->dlane_swap = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dsi_host_parse_dt(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा device *dev = &msm_host->pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *endpoपूर्णांक, *device_node;
	पूर्णांक ret = 0;

	/*
	 * Get the endpoपूर्णांक of the output port of the DSI host. In our हाल,
	 * this is mapped to port number with reg = 1. Don't वापस an error अगर
	 * the remote endpoपूर्णांक isn't defined. It's possible that there is
	 * nothing connected to the dsi output.
	 */
	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(np, 1, -1);
	अगर (!endpoपूर्णांक) अणु
		DRM_DEV_DEBUG(dev, "%s: no endpoint\n", __func__);
		वापस 0;
	पूर्ण

	ret = dsi_host_parse_lane_data(msm_host, endpoपूर्णांक);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: invalid lane configuration %d\n",
			__func__, ret);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Get panel node from the output port's endpoपूर्णांक data */
	device_node = of_graph_get_remote_node(np, 1, 0);
	अगर (!device_node) अणु
		DRM_DEV_DEBUG(dev, "%s: no valid device\n", __func__);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	msm_host->device_node = device_node;

	अगर (of_property_पढ़ो_bool(np, "syscon-sfpb")) अणु
		msm_host->sfpb = syscon_regmap_lookup_by_phandle(np,
					"syscon-sfpb");
		अगर (IS_ERR(msm_host->sfpb)) अणु
			DRM_DEV_ERROR(dev, "%s: failed to get sfpb regmap\n",
				__func__);
			ret = PTR_ERR(msm_host->sfpb);
		पूर्ण
	पूर्ण

	of_node_put(device_node);

err:
	of_node_put(endpoपूर्णांक);

	वापस ret;
पूर्ण

अटल पूर्णांक dsi_host_get_id(काष्ठा msm_dsi_host *msm_host)
अणु
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	स्थिर काष्ठा msm_dsi_config *cfg = msm_host->cfg_hnd->cfg;
	काष्ठा resource *res;
	पूर्णांक i;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dsi_ctrl");
	अगर (!res)
		वापस -EINVAL;

	क्रम (i = 0; i < cfg->num_dsi; i++) अणु
		अगर (cfg->io_start[i] == res->start)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक msm_dsi_host_init(काष्ठा msm_dsi *msm_dsi)
अणु
	काष्ठा msm_dsi_host *msm_host = शून्य;
	काष्ठा platक्रमm_device *pdev = msm_dsi->pdev;
	पूर्णांक ret;

	msm_host = devm_kzalloc(&pdev->dev, माप(*msm_host), GFP_KERNEL);
	अगर (!msm_host) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	msm_host->pdev = pdev;
	msm_dsi->host = &msm_host->base;

	ret = dsi_host_parse_dt(msm_host);
	अगर (ret) अणु
		pr_err("%s: failed to parse dt\n", __func__);
		जाओ fail;
	पूर्ण

	msm_host->ctrl_base = msm_ioremap(pdev, "dsi_ctrl", "DSI CTRL");
	अगर (IS_ERR(msm_host->ctrl_base)) अणु
		pr_err("%s: unable to map Dsi ctrl base\n", __func__);
		ret = PTR_ERR(msm_host->ctrl_base);
		जाओ fail;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	msm_host->cfg_hnd = dsi_get_config(msm_host);
	अगर (!msm_host->cfg_hnd) अणु
		ret = -EINVAL;
		pr_err("%s: get config failed\n", __func__);
		जाओ fail;
	पूर्ण

	msm_host->id = dsi_host_get_id(msm_host);
	अगर (msm_host->id < 0) अणु
		ret = msm_host->id;
		pr_err("%s: unable to identify DSI host index\n", __func__);
		जाओ fail;
	पूर्ण

	/* fixup base address by io offset */
	msm_host->ctrl_base += msm_host->cfg_hnd->cfg->io_offset;

	ret = dsi_regulator_init(msm_host);
	अगर (ret) अणु
		pr_err("%s: regulator init failed\n", __func__);
		जाओ fail;
	पूर्ण

	ret = dsi_clk_init(msm_host);
	अगर (ret) अणु
		pr_err("%s: unable to initialize dsi clks\n", __func__);
		जाओ fail;
	पूर्ण

	msm_host->rx_buf = devm_kzalloc(&pdev->dev, SZ_4K, GFP_KERNEL);
	अगर (!msm_host->rx_buf) अणु
		ret = -ENOMEM;
		pr_err("%s: alloc rx temp buf failed\n", __func__);
		जाओ fail;
	पूर्ण

	msm_host->opp_table = dev_pm_opp_set_clkname(&pdev->dev, "byte");
	अगर (IS_ERR(msm_host->opp_table))
		वापस PTR_ERR(msm_host->opp_table);
	/* OPP table is optional */
	ret = dev_pm_opp_of_add_table(&pdev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(&pdev->dev, "invalid OPP table in device tree\n");
		dev_pm_opp_put_clkname(msm_host->opp_table);
		वापस ret;
	पूर्ण

	init_completion(&msm_host->dma_comp);
	init_completion(&msm_host->video_comp);
	mutex_init(&msm_host->dev_mutex);
	mutex_init(&msm_host->cmd_mutex);
	spin_lock_init(&msm_host->पूर्णांकr_lock);

	/* setup workqueue */
	msm_host->workqueue = alloc_ordered_workqueue("dsi_drm_work", 0);
	INIT_WORK(&msm_host->err_work, dsi_err_worker);
	INIT_WORK(&msm_host->hpd_work, dsi_hpd_worker);

	msm_dsi->id = msm_host->id;

	DBG("Dsi Host %d initialized", msm_host->id);
	वापस 0;

fail:
	वापस ret;
पूर्ण

व्योम msm_dsi_host_destroy(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	dsi_tx_buf_मुक्त(msm_host);
	अगर (msm_host->workqueue) अणु
		flush_workqueue(msm_host->workqueue);
		destroy_workqueue(msm_host->workqueue);
		msm_host->workqueue = शून्य;
	पूर्ण

	mutex_destroy(&msm_host->cmd_mutex);
	mutex_destroy(&msm_host->dev_mutex);

	dev_pm_opp_of_हटाओ_table(&msm_host->pdev->dev);
	dev_pm_opp_put_clkname(msm_host->opp_table);
	pm_runसमय_disable(&msm_host->pdev->dev);
पूर्ण

पूर्णांक msm_dsi_host_modeset_init(काष्ठा mipi_dsi_host *host,
					काष्ठा drm_device *dev)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	पूर्णांक ret;

	msm_host->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (msm_host->irq < 0) अणु
		ret = msm_host->irq;
		DRM_DEV_ERROR(dev->dev, "failed to get irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, msm_host->irq,
			dsi_host_irq, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"dsi_isr", msm_host);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to request IRQ%u: %d\n",
				msm_host->irq, ret);
		वापस ret;
	पूर्ण

	msm_host->dev = dev;
	ret = cfg_hnd->ops->tx_buf_alloc(msm_host, SZ_4K);
	अगर (ret) अणु
		pr_err("%s: alloc tx gem obj failed, %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक msm_dsi_host_रेजिस्टर(काष्ठा mipi_dsi_host *host, bool check_defer)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	पूर्णांक ret;

	/* Register mipi dsi host */
	अगर (!msm_host->रेजिस्टरed) अणु
		host->dev = &msm_host->pdev->dev;
		host->ops = &dsi_host_ops;
		ret = mipi_dsi_host_रेजिस्टर(host);
		अगर (ret)
			वापस ret;

		msm_host->रेजिस्टरed = true;

		/* If the panel driver has not been probed after host रेजिस्टर,
		 * we should defer the host's probe.
		 * It makes sure panel is connected when fbcon detects
		 * connector status and माला_लो the proper display mode to
		 * create framebuffer.
		 * Don't try to defer अगर there is nothing connected to the dsi
		 * output
		 */
		अगर (check_defer && msm_host->device_node) अणु
			अगर (IS_ERR(of_drm_find_panel(msm_host->device_node)))
				अगर (!of_drm_find_bridge(msm_host->device_node))
					वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम msm_dsi_host_unरेजिस्टर(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	अगर (msm_host->रेजिस्टरed) अणु
		mipi_dsi_host_unरेजिस्टर(host);
		host->dev = शून्य;
		host->ops = शून्य;
		msm_host->रेजिस्टरed = false;
	पूर्ण
पूर्ण

पूर्णांक msm_dsi_host_xfer_prepare(काष्ठा mipi_dsi_host *host,
				स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;

	/* TODO: make sure dsi_cmd_mdp is idle.
	 * Since DSI6G v1.2.0, we can set DSI_TRIG_CTRL.BLOCK_DMA_WITHIN_FRAME
	 * to ask H/W to रुको until cmd mdp is idle. S/W रुको is not needed.
	 * How to handle the old versions? Wait क्रम mdp cmd करोne?
	 */

	/*
	 * mdss पूर्णांकerrupt is generated in mdp core घड़ी करोमुख्य
	 * mdp घड़ी need to be enabled to receive dsi पूर्णांकerrupt
	 */
	pm_runसमय_get_sync(&msm_host->pdev->dev);
	cfg_hnd->ops->link_clk_set_rate(msm_host);
	cfg_hnd->ops->link_clk_enable(msm_host);

	/* TODO: vote क्रम bus bandwidth */

	अगर (!(msg->flags & MIPI_DSI_MSG_USE_LPM))
		dsi_set_tx_घातer_mode(0, msm_host);

	msm_host->dma_cmd_ctrl_restore = dsi_पढ़ो(msm_host, REG_DSI_CTRL);
	dsi_ग_लिखो(msm_host, REG_DSI_CTRL,
		msm_host->dma_cmd_ctrl_restore |
		DSI_CTRL_CMD_MODE_EN |
		DSI_CTRL_ENABLE);
	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_CMD_DMA_DONE, 1);

	वापस 0;
पूर्ण

व्योम msm_dsi_host_xfer_restore(काष्ठा mipi_dsi_host *host,
				स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;

	dsi_पूर्णांकr_ctrl(msm_host, DSI_IRQ_MASK_CMD_DMA_DONE, 0);
	dsi_ग_लिखो(msm_host, REG_DSI_CTRL, msm_host->dma_cmd_ctrl_restore);

	अगर (!(msg->flags & MIPI_DSI_MSG_USE_LPM))
		dsi_set_tx_घातer_mode(1, msm_host);

	/* TODO: unvote क्रम bus bandwidth */

	cfg_hnd->ops->link_clk_disable(msm_host);
	pm_runसमय_put_स्वतःsuspend(&msm_host->pdev->dev);
पूर्ण

पूर्णांक msm_dsi_host_cmd_tx(काष्ठा mipi_dsi_host *host,
				स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	वापस dsi_cmds2buf_tx(msm_host, msg);
पूर्ण

पूर्णांक msm_dsi_host_cmd_rx(काष्ठा mipi_dsi_host *host,
				स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	पूर्णांक data_byte, rx_byte, dlen, end;
	पूर्णांक लघु_response, dअगरf, pkt_size, ret = 0;
	अक्षर cmd;
	पूर्णांक rlen = msg->rx_len;
	u8 *buf;

	अगर (rlen <= 2) अणु
		लघु_response = 1;
		pkt_size = rlen;
		rx_byte = 4;
	पूर्ण अन्यथा अणु
		लघु_response = 0;
		data_byte = 10;	/* first पढ़ो */
		अगर (rlen < data_byte)
			pkt_size = rlen;
		अन्यथा
			pkt_size = data_byte;
		rx_byte = data_byte + 6; /* 4 header + 2 crc */
	पूर्ण

	buf = msm_host->rx_buf;
	end = 0;
	जबतक (!end) अणु
		u8 tx[2] = अणुpkt_size & 0xff, pkt_size >> 8पूर्ण;
		काष्ठा mipi_dsi_msg max_pkt_size_msg = अणु
			.channel = msg->channel,
			.type = MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE,
			.tx_len = 2,
			.tx_buf = tx,
		पूर्ण;

		DBG("rlen=%d pkt_size=%d rx_byte=%d",
			rlen, pkt_size, rx_byte);

		ret = dsi_cmds2buf_tx(msm_host, &max_pkt_size_msg);
		अगर (ret < 2) अणु
			pr_err("%s: Set max pkt size failed, %d\n",
				__func__, ret);
			वापस -EINVAL;
		पूर्ण

		अगर ((cfg_hnd->major == MSM_DSI_VER_MAJOR_6G) &&
			(cfg_hnd->minor >= MSM_DSI_6G_VER_MINOR_V1_1)) अणु
			/* Clear the RDBK_DATA रेजिस्टरs */
			dsi_ग_लिखो(msm_host, REG_DSI_RDBK_DATA_CTRL,
					DSI_RDBK_DATA_CTRL_CLR);
			wmb(); /* make sure the RDBK रेजिस्टरs are cleared */
			dsi_ग_लिखो(msm_host, REG_DSI_RDBK_DATA_CTRL, 0);
			wmb(); /* release cleared status beक्रमe transfer */
		पूर्ण

		ret = dsi_cmds2buf_tx(msm_host, msg);
		अगर (ret < msg->tx_len) अणु
			pr_err("%s: Read cmd Tx failed, %d\n", __func__, ret);
			वापस ret;
		पूर्ण

		/*
		 * once cmd_dma_करोne पूर्णांकerrupt received,
		 * वापस data from client is पढ़ोy and stored
		 * at RDBK_DATA रेजिस्टर alपढ़ोy
		 * since rx fअगरo is 16 bytes, dcs header is kept at first loop,
		 * after that dcs header lost during shअगरt पूर्णांकo रेजिस्टरs
		 */
		dlen = dsi_cmd_dma_rx(msm_host, buf, rx_byte, pkt_size);

		अगर (dlen <= 0)
			वापस 0;

		अगर (लघु_response)
			अवरोध;

		अगर (rlen <= data_byte) अणु
			dअगरf = data_byte - rlen;
			end = 1;
		पूर्ण अन्यथा अणु
			dअगरf = 0;
			rlen -= data_byte;
		पूर्ण

		अगर (!end) अणु
			dlen -= 2; /* 2 crc */
			dlen -= dअगरf;
			buf += dlen;	/* next start position */
			data_byte = 14;	/* NOT first पढ़ो */
			अगर (rlen < data_byte)
				pkt_size += rlen;
			अन्यथा
				pkt_size += data_byte;
			DBG("buf=%p dlen=%d diff=%d", buf, dlen, dअगरf);
		पूर्ण
	पूर्ण

	/*
	 * For single Long पढ़ो, अगर the requested rlen < 10,
	 * we need to shअगरt the start position of rx
	 * data buffer to skip the bytes which are not
	 * updated.
	 */
	अगर (pkt_size < 10 && !लघु_response)
		buf = msm_host->rx_buf + (10 - rlen);
	अन्यथा
		buf = msm_host->rx_buf;

	cmd = buf[0];
	चयन (cmd) अणु
	हाल MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
		pr_err("%s: rx ACK_ERR_PACLAGE\n", __func__);
		ret = 0;
		अवरोध;
	हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
		ret = dsi_लघु_पढ़ो1_resp(buf, msg);
		अवरोध;
	हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
		ret = dsi_लघु_पढ़ो2_resp(buf, msg);
		अवरोध;
	हाल MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE:
	हाल MIPI_DSI_RX_DCS_LONG_READ_RESPONSE:
		ret = dsi_दीर्घ_पढ़ो_resp(buf, msg);
		अवरोध;
	शेष:
		pr_warn("%s:Invalid response cmd\n", __func__);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

व्योम msm_dsi_host_cmd_xfer_commit(काष्ठा mipi_dsi_host *host, u32 dma_base,
				  u32 len)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_ग_लिखो(msm_host, REG_DSI_DMA_BASE, dma_base);
	dsi_ग_लिखो(msm_host, REG_DSI_DMA_LEN, len);
	dsi_ग_लिखो(msm_host, REG_DSI_TRIG_DMA, 1);

	/* Make sure trigger happens */
	wmb();
पूर्ण

पूर्णांक msm_dsi_host_set_src_pll(काष्ठा mipi_dsi_host *host,
	काष्ठा msm_dsi_phy *src_phy)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	काष्ठा clk *byte_clk_provider, *pixel_clk_provider;
	पूर्णांक ret;

	ret = msm_dsi_phy_get_clk_provider(src_phy,
				&byte_clk_provider, &pixel_clk_provider);
	अगर (ret) अणु
		pr_info("%s: can't get provider from pll, don't set parent\n",
			__func__);
		वापस 0;
	पूर्ण

	ret = clk_set_parent(msm_host->byte_clk_src, byte_clk_provider);
	अगर (ret) अणु
		pr_err("%s: can't set parent to byte_clk_src. ret=%d\n",
			__func__, ret);
		जाओ निकास;
	पूर्ण

	ret = clk_set_parent(msm_host->pixel_clk_src, pixel_clk_provider);
	अगर (ret) अणु
		pr_err("%s: can't set parent to pixel_clk_src. ret=%d\n",
			__func__, ret);
		जाओ निकास;
	पूर्ण

	अगर (msm_host->dsi_clk_src) अणु
		ret = clk_set_parent(msm_host->dsi_clk_src, pixel_clk_provider);
		अगर (ret) अणु
			pr_err("%s: can't set parent to dsi_clk_src. ret=%d\n",
				__func__, ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (msm_host->esc_clk_src) अणु
		ret = clk_set_parent(msm_host->esc_clk_src, byte_clk_provider);
		अगर (ret) अणु
			pr_err("%s: can't set parent to esc_clk_src. ret=%d\n",
				__func__, ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

व्योम msm_dsi_host_reset_phy(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	dsi_ग_लिखो(msm_host, REG_DSI_PHY_RESET, DSI_PHY_RESET_RESET);
	/* Make sure fully reset */
	wmb();
	udelay(1000);
	dsi_ग_लिखो(msm_host, REG_DSI_PHY_RESET, 0);
	udelay(100);
पूर्ण

व्योम msm_dsi_host_get_phy_clk_req(काष्ठा mipi_dsi_host *host,
			काष्ठा msm_dsi_phy_clk_request *clk_req,
			bool is_dual_dsi)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	पूर्णांक ret;

	ret = cfg_hnd->ops->calc_clk_rate(msm_host, is_dual_dsi);
	अगर (ret) अणु
		pr_err("%s: unable to calc clk rate, %d\n", __func__, ret);
		वापस;
	पूर्ण

	clk_req->bitclk_rate = msm_host->byte_clk_rate * 8;
	clk_req->escclk_rate = msm_host->esc_clk_rate;
पूर्ण

पूर्णांक msm_dsi_host_enable(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_flags & MIPI_DSI_MODE_VIDEO), true);

	/* TODO: घड़ी should be turned off क्रम command mode,
	 * and only turned on beक्रमe MDP START.
	 * This part of code should be enabled once mdp driver support it.
	 */
	/* अगर (msm_panel->mode == MSM_DSI_CMD_MODE) अणु
	 *	dsi_link_clk_disable(msm_host);
	 *	pm_runसमय_put_स्वतःsuspend(&msm_host->pdev->dev);
	 * पूर्ण
	 */
	msm_host->enabled = true;
	वापस 0;
पूर्ण

पूर्णांक msm_dsi_host_disable(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->enabled = false;
	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_flags & MIPI_DSI_MODE_VIDEO), false);

	/* Since we have disabled INTF, the video engine won't stop so that
	 * the cmd engine will be blocked.
	 * Reset to disable video engine so that we can send off cmd.
	 */
	dsi_sw_reset(msm_host);

	वापस 0;
पूर्ण

अटल व्योम msm_dsi_sfpb_config(काष्ठा msm_dsi_host *msm_host, bool enable)
अणु
	क्रमागत sfpb_ahb_arb_master_port_en en;

	अगर (!msm_host->sfpb)
		वापस;

	en = enable ? SFPB_MASTER_PORT_ENABLE : SFPB_MASTER_PORT_DISABLE;

	regmap_update_bits(msm_host->sfpb, REG_SFPB_GPREG,
			SFPB_GPREG_MASTER_PORT_EN__MASK,
			SFPB_GPREG_MASTER_PORT_EN(en));
पूर्ण

पूर्णांक msm_dsi_host_घातer_on(काष्ठा mipi_dsi_host *host,
			काष्ठा msm_dsi_phy_shared_timings *phy_shared_timings,
			bool is_dual_dsi)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;
	पूर्णांक ret = 0;

	mutex_lock(&msm_host->dev_mutex);
	अगर (msm_host->घातer_on) अणु
		DBG("dsi host already on");
		जाओ unlock_ret;
	पूर्ण

	msm_dsi_sfpb_config(msm_host, true);

	ret = dsi_host_regulator_enable(msm_host);
	अगर (ret) अणु
		pr_err("%s:Failed to enable vregs.ret=%d\n",
			__func__, ret);
		जाओ unlock_ret;
	पूर्ण

	pm_runसमय_get_sync(&msm_host->pdev->dev);
	ret = cfg_hnd->ops->link_clk_set_rate(msm_host);
	अगर (!ret)
		ret = cfg_hnd->ops->link_clk_enable(msm_host);
	अगर (ret) अणु
		pr_err("%s: failed to enable link clocks. ret=%d\n",
		       __func__, ret);
		जाओ fail_disable_reg;
	पूर्ण

	ret = pinctrl_pm_select_शेष_state(&msm_host->pdev->dev);
	अगर (ret) अणु
		pr_err("%s: failed to set pinctrl default state, %d\n",
			__func__, ret);
		जाओ fail_disable_clk;
	पूर्ण

	dsi_timing_setup(msm_host, is_dual_dsi);
	dsi_sw_reset(msm_host);
	dsi_ctrl_config(msm_host, true, phy_shared_timings);

	अगर (msm_host->disp_en_gpio)
		gpiod_set_value(msm_host->disp_en_gpio, 1);

	msm_host->घातer_on = true;
	mutex_unlock(&msm_host->dev_mutex);

	वापस 0;

fail_disable_clk:
	cfg_hnd->ops->link_clk_disable(msm_host);
	pm_runसमय_put_स्वतःsuspend(&msm_host->pdev->dev);
fail_disable_reg:
	dsi_host_regulator_disable(msm_host);
unlock_ret:
	mutex_unlock(&msm_host->dev_mutex);
	वापस ret;
पूर्ण

पूर्णांक msm_dsi_host_घातer_off(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);
	स्थिर काष्ठा msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;

	mutex_lock(&msm_host->dev_mutex);
	अगर (!msm_host->घातer_on) अणु
		DBG("dsi host already off");
		जाओ unlock_ret;
	पूर्ण

	dsi_ctrl_config(msm_host, false, शून्य);

	अगर (msm_host->disp_en_gpio)
		gpiod_set_value(msm_host->disp_en_gpio, 0);

	pinctrl_pm_select_sleep_state(&msm_host->pdev->dev);

	cfg_hnd->ops->link_clk_disable(msm_host);
	pm_runसमय_put_स्वतःsuspend(&msm_host->pdev->dev);

	dsi_host_regulator_disable(msm_host);

	msm_dsi_sfpb_config(msm_host, false);

	DBG("-");

	msm_host->घातer_on = false;

unlock_ret:
	mutex_unlock(&msm_host->dev_mutex);
	वापस 0;
पूर्ण

पूर्णांक msm_dsi_host_set_display_mode(काष्ठा mipi_dsi_host *host,
				  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	अगर (msm_host->mode) अणु
		drm_mode_destroy(msm_host->dev, msm_host->mode);
		msm_host->mode = शून्य;
	पूर्ण

	msm_host->mode = drm_mode_duplicate(msm_host->dev, mode);
	अगर (!msm_host->mode) अणु
		pr_err("%s: cannot duplicate mode\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_panel *msm_dsi_host_get_panel(काष्ठा mipi_dsi_host *host)
अणु
	वापस of_drm_find_panel(to_msm_dsi_host(host)->device_node);
पूर्ण

अचिन्हित दीर्घ msm_dsi_host_get_mode_flags(काष्ठा mipi_dsi_host *host)
अणु
	वापस to_msm_dsi_host(host)->mode_flags;
पूर्ण

काष्ठा drm_bridge *msm_dsi_host_get_bridge(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा msm_dsi_host *msm_host = to_msm_dsi_host(host);

	वापस of_drm_find_bridge(msm_host->device_node);
पूर्ण
