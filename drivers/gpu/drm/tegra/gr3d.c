<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Avionic Design GmbH
 * Copyright (C) 2013 NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/host1x.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <soc/tegra/pmc.h>

#समावेश "drm.h"
#समावेश "gem.h"
#समावेश "gr3d.h"

काष्ठा gr3d_soc अणु
	अचिन्हित पूर्णांक version;
पूर्ण;

काष्ठा gr3d अणु
	काष्ठा tegra_drm_client client;
	काष्ठा host1x_channel *channel;
	काष्ठा clk *clk_secondary;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst_secondary;
	काष्ठा reset_control *rst;

	स्थिर काष्ठा gr3d_soc *soc;

	DECLARE_BITMAP(addr_regs, GR3D_NUM_REGS);
पूर्ण;

अटल अंतरभूत काष्ठा gr3d *to_gr3d(काष्ठा tegra_drm_client *client)
अणु
	वापस container_of(client, काष्ठा gr3d, client);
पूर्ण

अटल पूर्णांक gr3d_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	अचिन्हित दीर्घ flags = HOST1X_SYNCPT_HAS_BASE;
	काष्ठा gr3d *gr3d = to_gr3d(drm);
	पूर्णांक err;

	gr3d->channel = host1x_channel_request(client);
	अगर (!gr3d->channel)
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
	host1x_channel_put(gr3d->channel);
	वापस err;
पूर्ण

अटल पूर्णांक gr3d_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	काष्ठा gr3d *gr3d = to_gr3d(drm);
	पूर्णांक err;

	err = tegra_drm_unरेजिस्टर_client(dev->dev_निजी, drm);
	अगर (err < 0)
		वापस err;

	host1x_client_iommu_detach(client);
	host1x_syncpt_put(client->syncpts[0]);
	host1x_channel_put(gr3d->channel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops gr3d_client_ops = अणु
	.init = gr3d_init,
	.निकास = gr3d_निकास,
पूर्ण;

अटल पूर्णांक gr3d_खोलो_channel(काष्ठा tegra_drm_client *client,
			     काष्ठा tegra_drm_context *context)
अणु
	काष्ठा gr3d *gr3d = to_gr3d(client);

	context->channel = host1x_channel_get(gr3d->channel);
	अगर (!context->channel)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम gr3d_बंद_channel(काष्ठा tegra_drm_context *context)
अणु
	host1x_channel_put(context->channel);
पूर्ण

अटल पूर्णांक gr3d_is_addr_reg(काष्ठा device *dev, u32 class, u32 offset)
अणु
	काष्ठा gr3d *gr3d = dev_get_drvdata(dev);

	चयन (class) अणु
	हाल HOST1X_CLASS_HOST1X:
		अगर (offset == 0x2b)
			वापस 1;

		अवरोध;

	हाल HOST1X_CLASS_GR3D:
		अगर (offset >= GR3D_NUM_REGS)
			अवरोध;

		अगर (test_bit(offset, gr3d->addr_regs))
			वापस 1;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_drm_client_ops gr3d_ops = अणु
	.खोलो_channel = gr3d_खोलो_channel,
	.बंद_channel = gr3d_बंद_channel,
	.is_addr_reg = gr3d_is_addr_reg,
	.submit = tegra_drm_submit,
पूर्ण;

अटल स्थिर काष्ठा gr3d_soc tegra20_gr3d_soc = अणु
	.version = 0x20,
पूर्ण;

अटल स्थिर काष्ठा gr3d_soc tegra30_gr3d_soc = अणु
	.version = 0x30,
पूर्ण;

अटल स्थिर काष्ठा gr3d_soc tegra114_gr3d_soc = अणु
	.version = 0x35,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_gr3d_match[] = अणु
	अणु .compatible = "nvidia,tegra114-gr3d", .data = &tegra114_gr3d_soc पूर्ण,
	अणु .compatible = "nvidia,tegra30-gr3d", .data = &tegra30_gr3d_soc पूर्ण,
	अणु .compatible = "nvidia,tegra20-gr3d", .data = &tegra20_gr3d_soc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_gr3d_match);

अटल स्थिर u32 gr3d_addr_regs[] = अणु
	GR3D_IDX_ATTRIBUTE( 0),
	GR3D_IDX_ATTRIBUTE( 1),
	GR3D_IDX_ATTRIBUTE( 2),
	GR3D_IDX_ATTRIBUTE( 3),
	GR3D_IDX_ATTRIBUTE( 4),
	GR3D_IDX_ATTRIBUTE( 5),
	GR3D_IDX_ATTRIBUTE( 6),
	GR3D_IDX_ATTRIBUTE( 7),
	GR3D_IDX_ATTRIBUTE( 8),
	GR3D_IDX_ATTRIBUTE( 9),
	GR3D_IDX_ATTRIBUTE(10),
	GR3D_IDX_ATTRIBUTE(11),
	GR3D_IDX_ATTRIBUTE(12),
	GR3D_IDX_ATTRIBUTE(13),
	GR3D_IDX_ATTRIBUTE(14),
	GR3D_IDX_ATTRIBUTE(15),
	GR3D_IDX_INDEX_BASE,
	GR3D_QR_ZTAG_ADDR,
	GR3D_QR_CTAG_ADDR,
	GR3D_QR_CZ_ADDR,
	GR3D_TEX_TEX_ADDR( 0),
	GR3D_TEX_TEX_ADDR( 1),
	GR3D_TEX_TEX_ADDR( 2),
	GR3D_TEX_TEX_ADDR( 3),
	GR3D_TEX_TEX_ADDR( 4),
	GR3D_TEX_TEX_ADDR( 5),
	GR3D_TEX_TEX_ADDR( 6),
	GR3D_TEX_TEX_ADDR( 7),
	GR3D_TEX_TEX_ADDR( 8),
	GR3D_TEX_TEX_ADDR( 9),
	GR3D_TEX_TEX_ADDR(10),
	GR3D_TEX_TEX_ADDR(11),
	GR3D_TEX_TEX_ADDR(12),
	GR3D_TEX_TEX_ADDR(13),
	GR3D_TEX_TEX_ADDR(14),
	GR3D_TEX_TEX_ADDR(15),
	GR3D_DW_MEMORY_OUTPUT_ADDRESS,
	GR3D_GLOBAL_SURFADDR( 0),
	GR3D_GLOBAL_SURFADDR( 1),
	GR3D_GLOBAL_SURFADDR( 2),
	GR3D_GLOBAL_SURFADDR( 3),
	GR3D_GLOBAL_SURFADDR( 4),
	GR3D_GLOBAL_SURFADDR( 5),
	GR3D_GLOBAL_SURFADDR( 6),
	GR3D_GLOBAL_SURFADDR( 7),
	GR3D_GLOBAL_SURFADDR( 8),
	GR3D_GLOBAL_SURFADDR( 9),
	GR3D_GLOBAL_SURFADDR(10),
	GR3D_GLOBAL_SURFADDR(11),
	GR3D_GLOBAL_SURFADDR(12),
	GR3D_GLOBAL_SURFADDR(13),
	GR3D_GLOBAL_SURFADDR(14),
	GR3D_GLOBAL_SURFADDR(15),
	GR3D_GLOBAL_SPILLSURFADDR,
	GR3D_GLOBAL_SURFOVERADDR( 0),
	GR3D_GLOBAL_SURFOVERADDR( 1),
	GR3D_GLOBAL_SURFOVERADDR( 2),
	GR3D_GLOBAL_SURFOVERADDR( 3),
	GR3D_GLOBAL_SURFOVERADDR( 4),
	GR3D_GLOBAL_SURFOVERADDR( 5),
	GR3D_GLOBAL_SURFOVERADDR( 6),
	GR3D_GLOBAL_SURFOVERADDR( 7),
	GR3D_GLOBAL_SURFOVERADDR( 8),
	GR3D_GLOBAL_SURFOVERADDR( 9),
	GR3D_GLOBAL_SURFOVERADDR(10),
	GR3D_GLOBAL_SURFOVERADDR(11),
	GR3D_GLOBAL_SURFOVERADDR(12),
	GR3D_GLOBAL_SURFOVERADDR(13),
	GR3D_GLOBAL_SURFOVERADDR(14),
	GR3D_GLOBAL_SURFOVERADDR(15),
	GR3D_GLOBAL_SAMP01SURFADDR( 0),
	GR3D_GLOBAL_SAMP01SURFADDR( 1),
	GR3D_GLOBAL_SAMP01SURFADDR( 2),
	GR3D_GLOBAL_SAMP01SURFADDR( 3),
	GR3D_GLOBAL_SAMP01SURFADDR( 4),
	GR3D_GLOBAL_SAMP01SURFADDR( 5),
	GR3D_GLOBAL_SAMP01SURFADDR( 6),
	GR3D_GLOBAL_SAMP01SURFADDR( 7),
	GR3D_GLOBAL_SAMP01SURFADDR( 8),
	GR3D_GLOBAL_SAMP01SURFADDR( 9),
	GR3D_GLOBAL_SAMP01SURFADDR(10),
	GR3D_GLOBAL_SAMP01SURFADDR(11),
	GR3D_GLOBAL_SAMP01SURFADDR(12),
	GR3D_GLOBAL_SAMP01SURFADDR(13),
	GR3D_GLOBAL_SAMP01SURFADDR(14),
	GR3D_GLOBAL_SAMP01SURFADDR(15),
	GR3D_GLOBAL_SAMP23SURFADDR( 0),
	GR3D_GLOBAL_SAMP23SURFADDR( 1),
	GR3D_GLOBAL_SAMP23SURFADDR( 2),
	GR3D_GLOBAL_SAMP23SURFADDR( 3),
	GR3D_GLOBAL_SAMP23SURFADDR( 4),
	GR3D_GLOBAL_SAMP23SURFADDR( 5),
	GR3D_GLOBAL_SAMP23SURFADDR( 6),
	GR3D_GLOBAL_SAMP23SURFADDR( 7),
	GR3D_GLOBAL_SAMP23SURFADDR( 8),
	GR3D_GLOBAL_SAMP23SURFADDR( 9),
	GR3D_GLOBAL_SAMP23SURFADDR(10),
	GR3D_GLOBAL_SAMP23SURFADDR(11),
	GR3D_GLOBAL_SAMP23SURFADDR(12),
	GR3D_GLOBAL_SAMP23SURFADDR(13),
	GR3D_GLOBAL_SAMP23SURFADDR(14),
	GR3D_GLOBAL_SAMP23SURFADDR(15),
पूर्ण;

अटल पूर्णांक gr3d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा host1x_syncpt **syncpts;
	काष्ठा gr3d *gr3d;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	gr3d = devm_kzalloc(&pdev->dev, माप(*gr3d), GFP_KERNEL);
	अगर (!gr3d)
		वापस -ENOMEM;

	gr3d->soc = of_device_get_match_data(&pdev->dev);

	syncpts = devm_kzalloc(&pdev->dev, माप(*syncpts), GFP_KERNEL);
	अगर (!syncpts)
		वापस -ENOMEM;

	gr3d->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(gr3d->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(gr3d->clk);
	पूर्ण

	gr3d->rst = devm_reset_control_get(&pdev->dev, "3d");
	अगर (IS_ERR(gr3d->rst)) अणु
		dev_err(&pdev->dev, "cannot get reset\n");
		वापस PTR_ERR(gr3d->rst);
	पूर्ण

	अगर (of_device_is_compatible(np, "nvidia,tegra30-gr3d")) अणु
		gr3d->clk_secondary = devm_clk_get(&pdev->dev, "3d2");
		अगर (IS_ERR(gr3d->clk_secondary)) अणु
			dev_err(&pdev->dev, "cannot get secondary clock\n");
			वापस PTR_ERR(gr3d->clk_secondary);
		पूर्ण

		gr3d->rst_secondary = devm_reset_control_get(&pdev->dev,
								"3d2");
		अगर (IS_ERR(gr3d->rst_secondary)) अणु
			dev_err(&pdev->dev, "cannot get secondary reset\n");
			वापस PTR_ERR(gr3d->rst_secondary);
		पूर्ण
	पूर्ण

	err = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_3D, gr3d->clk,
						gr3d->rst);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to power up 3D unit\n");
		वापस err;
	पूर्ण

	अगर (gr3d->clk_secondary) अणु
		err = tegra_घातergate_sequence_घातer_up(TEGRA_POWERGATE_3D1,
							gr3d->clk_secondary,
							gr3d->rst_secondary);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"failed to power up secondary 3D unit\n");
			वापस err;
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&gr3d->client.base.list);
	gr3d->client.base.ops = &gr3d_client_ops;
	gr3d->client.base.dev = &pdev->dev;
	gr3d->client.base.class = HOST1X_CLASS_GR3D;
	gr3d->client.base.syncpts = syncpts;
	gr3d->client.base.num_syncpts = 1;

	INIT_LIST_HEAD(&gr3d->client.list);
	gr3d->client.version = gr3d->soc->version;
	gr3d->client.ops = &gr3d_ops;

	err = host1x_client_रेजिस्टर(&gr3d->client.base);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	/* initialize address रेजिस्टर map */
	क्रम (i = 0; i < ARRAY_SIZE(gr3d_addr_regs); i++)
		set_bit(gr3d_addr_regs[i], gr3d->addr_regs);

	platक्रमm_set_drvdata(pdev, gr3d);

	वापस 0;
पूर्ण

अटल पूर्णांक gr3d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gr3d *gr3d = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&gr3d->client.base);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	अगर (gr3d->clk_secondary) अणु
		reset_control_निश्चित(gr3d->rst_secondary);
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_3D1);
		clk_disable_unprepare(gr3d->clk_secondary);
	पूर्ण

	reset_control_निश्चित(gr3d->rst);
	tegra_घातergate_घातer_off(TEGRA_POWERGATE_3D);
	clk_disable_unprepare(gr3d->clk);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver tegra_gr3d_driver = अणु
	.driver = अणु
		.name = "tegra-gr3d",
		.of_match_table = tegra_gr3d_match,
	पूर्ण,
	.probe = gr3d_probe,
	.हटाओ = gr3d_हटाओ,
पूर्ण;
