<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2013, NVIDIA Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश "drm.h"
#समावेश "gem.h"
#समावेश "gr2d.h"

काष्ठा gr2d_soc अणु
	अचिन्हित पूर्णांक version;
पूर्ण;

काष्ठा gr2d अणु
	काष्ठा tegra_drm_client client;
	काष्ठा host1x_channel *channel;
	काष्ठा clk *clk;

	स्थिर काष्ठा gr2d_soc *soc;

	DECLARE_BITMAP(addr_regs, GR2D_NUM_REGS);
पूर्ण;

अटल अंतरभूत काष्ठा gr2d *to_gr2d(काष्ठा tegra_drm_client *client)
अणु
	वापस container_of(client, काष्ठा gr2d, client);
पूर्ण

अटल पूर्णांक gr2d_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	अचिन्हित दीर्घ flags = HOST1X_SYNCPT_HAS_BASE;
	काष्ठा gr2d *gr2d = to_gr2d(drm);
	पूर्णांक err;

	gr2d->channel = host1x_channel_request(client);
	अगर (!gr2d->channel)
		वापस -ENOMEM;

	client->syncpts[0] = host1x_syncpt_request(client, flags);
	अगर (!client->syncpts[0]) अणु
		err = -ENOMEM;
		dev_err(client->dev, "failed to request syncpoint: %d\n", err);
		जाओ put;
	पूर्ण

	err = host1x_client_iommu_attach(client);
	अगर (err < 0) अणु
		dev_err(client->dev, "failed to attach to domain: %d\n", err);
		जाओ मुक्त;
	पूर्ण

	err = tegra_drm_रेजिस्टर_client(dev->dev_निजी, drm);
	अगर (err < 0) अणु
		dev_err(client->dev, "failed to register client: %d\n", err);
		जाओ detach;
	पूर्ण

	वापस 0;

detach:
	host1x_client_iommu_detach(client);
मुक्त:
	host1x_syncpt_put(client->syncpts[0]);
put:
	host1x_channel_put(gr2d->channel);
	वापस err;
पूर्ण

अटल पूर्णांक gr2d_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = dev->dev_निजी;
	काष्ठा gr2d *gr2d = to_gr2d(drm);
	पूर्णांक err;

	err = tegra_drm_unरेजिस्टर_client(tegra, drm);
	अगर (err < 0)
		वापस err;

	host1x_client_iommu_detach(client);
	host1x_syncpt_put(client->syncpts[0]);
	host1x_channel_put(gr2d->channel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops gr2d_client_ops = अणु
	.init = gr2d_init,
	.निकास = gr2d_निकास,
पूर्ण;

अटल पूर्णांक gr2d_खोलो_channel(काष्ठा tegra_drm_client *client,
			     काष्ठा tegra_drm_context *context)
अणु
	काष्ठा gr2d *gr2d = to_gr2d(client);

	context->channel = host1x_channel_get(gr2d->channel);
	अगर (!context->channel)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम gr2d_बंद_channel(काष्ठा tegra_drm_context *context)
अणु
	host1x_channel_put(context->channel);
पूर्ण

अटल पूर्णांक gr2d_is_addr_reg(काष्ठा device *dev, u32 class, u32 offset)
अणु
	काष्ठा gr2d *gr2d = dev_get_drvdata(dev);

	चयन (class) अणु
	हाल HOST1X_CLASS_HOST1X:
		अगर (offset == 0x2b)
			वापस 1;

		अवरोध;

	हाल HOST1X_CLASS_GR2D:
	हाल HOST1X_CLASS_GR2D_SB:
		अगर (offset >= GR2D_NUM_REGS)
			अवरोध;

		अगर (test_bit(offset, gr2d->addr_regs))
			वापस 1;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gr2d_is_valid_class(u32 class)
अणु
	वापस (class == HOST1X_CLASS_GR2D ||
		class == HOST1X_CLASS_GR2D_SB);
पूर्ण

अटल स्थिर काष्ठा tegra_drm_client_ops gr2d_ops = अणु
	.खोलो_channel = gr2d_खोलो_channel,
	.बंद_channel = gr2d_बंद_channel,
	.is_addr_reg = gr2d_is_addr_reg,
	.is_valid_class = gr2d_is_valid_class,
	.submit = tegra_drm_submit,
पूर्ण;

अटल स्थिर काष्ठा gr2d_soc tegra20_gr2d_soc = अणु
	.version = 0x20,
पूर्ण;

अटल स्थिर काष्ठा gr2d_soc tegra30_gr2d_soc = अणु
	.version = 0x30,
पूर्ण;

अटल स्थिर काष्ठा gr2d_soc tegra114_gr2d_soc = अणु
	.version = 0x35,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gr2d_match[] = अणु
	अणु .compatible = "nvidia,tegra114-gr2d", .data = &tegra114_gr2d_soc पूर्ण,
	अणु .compatible = "nvidia,tegra30-gr2d", .data = &tegra30_gr2d_soc पूर्ण,
	अणु .compatible = "nvidia,tegra20-gr2d", .data = &tegra20_gr2d_soc पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gr2d_match);

अटल स्थिर u32 gr2d_addr_regs[] = अणु
	GR2D_UA_BASE_ADDR,
	GR2D_VA_BASE_ADDR,
	GR2D_PAT_BASE_ADDR,
	GR2D_DSTA_BASE_ADDR,
	GR2D_DSTB_BASE_ADDR,
	GR2D_DSTC_BASE_ADDR,
	GR2D_SRCA_BASE_ADDR,
	GR2D_SRCB_BASE_ADDR,
	GR2D_PATBASE_ADDR,
	GR2D_SRC_BASE_ADDR_SB,
	GR2D_DSTA_BASE_ADDR_SB,
	GR2D_DSTB_BASE_ADDR_SB,
	GR2D_UA_BASE_ADDR_SB,
	GR2D_VA_BASE_ADDR_SB,
पूर्ण;

अटल पूर्णांक gr2d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा host1x_syncpt **syncpts;
	काष्ठा gr2d *gr2d;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	gr2d = devm_kzalloc(dev, माप(*gr2d), GFP_KERNEL);
	अगर (!gr2d)
		वापस -ENOMEM;

	gr2d->soc = of_device_get_match_data(dev);

	syncpts = devm_kzalloc(dev, माप(*syncpts), GFP_KERNEL);
	अगर (!syncpts)
		वापस -ENOMEM;

	gr2d->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(gr2d->clk)) अणु
		dev_err(dev, "cannot get clock\n");
		वापस PTR_ERR(gr2d->clk);
	पूर्ण

	err = clk_prepare_enable(gr2d->clk);
	अगर (err) अणु
		dev_err(dev, "cannot turn on clock\n");
		वापस err;
	पूर्ण

	INIT_LIST_HEAD(&gr2d->client.base.list);
	gr2d->client.base.ops = &gr2d_client_ops;
	gr2d->client.base.dev = dev;
	gr2d->client.base.class = HOST1X_CLASS_GR2D;
	gr2d->client.base.syncpts = syncpts;
	gr2d->client.base.num_syncpts = 1;

	INIT_LIST_HEAD(&gr2d->client.list);
	gr2d->client.version = gr2d->soc->version;
	gr2d->client.ops = &gr2d_ops;

	err = host1x_client_रेजिस्टर(&gr2d->client.base);
	अगर (err < 0) अणु
		dev_err(dev, "failed to register host1x client: %d\n", err);
		clk_disable_unprepare(gr2d->clk);
		वापस err;
	पूर्ण

	/* initialize address रेजिस्टर map */
	क्रम (i = 0; i < ARRAY_SIZE(gr2d_addr_regs); i++)
		set_bit(gr2d_addr_regs[i], gr2d->addr_regs);

	platक्रमm_set_drvdata(pdev, gr2d);

	वापस 0;
पूर्ण

अटल पूर्णांक gr2d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gr2d *gr2d = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&gr2d->client.base);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	clk_disable_unprepare(gr2d->clk);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver tegra_gr2d_driver = अणु
	.driver = अणु
		.name = "tegra-gr2d",
		.of_match_table = gr2d_match,
	पूर्ण,
	.probe = gr2d_probe,
	.हटाओ = gr2d_हटाओ,
पूर्ण;
