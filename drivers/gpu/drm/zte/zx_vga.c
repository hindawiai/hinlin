<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Sanechips Technology Co., Ltd.
 * Copyright 2017 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "zx_drm_drv.h"
#समावेश "zx_vga_regs.h"
#समावेश "zx_vou.h"

काष्ठा zx_vga_pwrctrl अणु
	काष्ठा regmap *regmap;
	u32 reg;
	u32 mask;
पूर्ण;

काष्ठा zx_vga_i2c अणु
	काष्ठा i2c_adapter adap;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा zx_vga अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा zx_vga_i2c *ddc;
	काष्ठा device *dev;
	व्योम __iomem *mmio;
	काष्ठा clk *i2c_wclk;
	काष्ठा zx_vga_pwrctrl pwrctrl;
	काष्ठा completion complete;
	bool connected;
पूर्ण;

#घोषणा to_zx_vga(x) container_of(x, काष्ठा zx_vga, x)

अटल व्योम zx_vga_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_vga *vga = to_zx_vga(encoder);
	काष्ठा zx_vga_pwrctrl *pwrctrl = &vga->pwrctrl;

	/* Set bit to घातer up VGA DACs */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask,
			   pwrctrl->mask);

	vou_inf_enable(VOU_VGA, encoder->crtc);
पूर्ण

अटल व्योम zx_vga_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_vga *vga = to_zx_vga(encoder);
	काष्ठा zx_vga_pwrctrl *pwrctrl = &vga->pwrctrl;

	vou_inf_disable(VOU_VGA, encoder->crtc);

	/* Clear bit to घातer करोwn VGA DACs */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask, 0);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs zx_vga_encoder_helper_funcs = अणु
	.enable	= zx_vga_encoder_enable,
	.disable = zx_vga_encoder_disable,
पूर्ण;

अटल पूर्णांक zx_vga_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा zx_vga *vga = to_zx_vga(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	/*
	 * Clear both detection bits to चयन I2C bus from device
	 * detecting to EDID पढ़ोing.
	 */
	zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_SEL, 0);

	edid = drm_get_edid(connector, &vga->ddc->adap);
	अगर (!edid) अणु
		/*
		 * If EDID पढ़ोing fails, we set the device state पूर्णांकo
		 * disconnected.  Locking is not required here, since the
		 * VGA_AUTO_DETECT_SEL रेजिस्टर ग_लिखो in irq handler cannot
		 * be triggered when both detection bits are cleared as above.
		 */
		zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_SEL,
			  VGA_DETECT_SEL_NO_DEVICE);
		vga->connected = false;
		वापस 0;
	पूर्ण

	/*
	 * As edid पढ़ोing succeeds, device must be connected, so we set
	 * up detection bit क्रम unplug पूर्णांकerrupt here.
	 */
	zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_SEL, VGA_DETECT_SEL_HAS_DEVICE);

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status
zx_vga_connector_mode_valid(काष्ठा drm_connector *connector,
			    काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_connector_helper_funcs zx_vga_connector_helper_funcs = अणु
	.get_modes = zx_vga_connector_get_modes,
	.mode_valid = zx_vga_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
zx_vga_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा zx_vga *vga = to_zx_vga(connector);

	वापस vga->connected ? connector_status_connected :
				connector_status_disconnected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs zx_vga_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = zx_vga_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक zx_vga_रेजिस्टर(काष्ठा drm_device *drm, काष्ठा zx_vga *vga)
अणु
	काष्ठा drm_encoder *encoder = &vga->encoder;
	काष्ठा drm_connector *connector = &vga->connector;
	काष्ठा device *dev = vga->dev;
	पूर्णांक ret;

	encoder->possible_crtcs = VOU_CRTC_MASK;

	ret = drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_DAC);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init encoder: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &zx_vga_encoder_helper_funcs);

	vga->connector.polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init_with_ddc(drm, connector,
					  &zx_vga_connector_funcs,
					  DRM_MODE_CONNECTOR_VGA,
					  &vga->ddc->adap);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init connector: %d\n", ret);
		जाओ clean_encoder;
	पूर्ण

	drm_connector_helper_add(connector, &zx_vga_connector_helper_funcs);

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to attach encoder: %d\n", ret);
		जाओ clean_connector;
	पूर्ण

	वापस 0;

clean_connector:
	drm_connector_cleanup(connector);
clean_encoder:
	drm_encoder_cleanup(encoder);
	वापस ret;
पूर्ण

अटल पूर्णांक zx_vga_pwrctrl_init(काष्ठा zx_vga *vga)
अणु
	काष्ठा zx_vga_pwrctrl *pwrctrl = &vga->pwrctrl;
	काष्ठा device *dev = vga->dev;
	काष्ठा of_phandle_args out_args;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	ret = of_parse_phandle_with_fixed_args(dev->of_node,
				"zte,vga-power-control", 2, 0, &out_args);
	अगर (ret)
		वापस ret;

	regmap = syscon_node_to_regmap(out_args.np);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ out;
	पूर्ण

	pwrctrl->regmap = regmap;
	pwrctrl->reg = out_args.args[0];
	pwrctrl->mask = out_args.args[1];

out:
	of_node_put(out_args.np);
	वापस ret;
पूर्ण

अटल पूर्णांक zx_vga_i2c_पढ़ो(काष्ठा zx_vga *vga, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक len = msg->len;
	u8 *buf = msg->buf;
	u32 offset = 0;
	पूर्णांक i;

	reinit_completion(&vga->complete);

	/* Select combo ग_लिखो */
	zx_ग_लिखोl_mask(vga->mmio + VGA_CMD_CFG, VGA_CMD_COMBO, VGA_CMD_COMBO);
	zx_ग_लिखोl_mask(vga->mmio + VGA_CMD_CFG, VGA_CMD_RW, 0);

	जबतक (len > 0) अणु
		u32 cnt;

		/* Clear RX FIFO */
		zx_ग_लिखोl_mask(vga->mmio + VGA_RXF_CTRL, VGA_RX_FIFO_CLEAR,
			       VGA_RX_FIFO_CLEAR);

		/* Data offset to पढ़ो from */
		zx_ग_लिखोl(vga->mmio + VGA_SUB_ADDR, offset);

		/* Kick off the transfer */
		zx_ग_लिखोl_mask(vga->mmio + VGA_CMD_CFG, VGA_CMD_TRANS,
			       VGA_CMD_TRANS);

		अगर (!रुको_क्रम_completion_समयout(&vga->complete,
						 msecs_to_jअगरfies(1000))) अणु
			DRM_DEV_ERROR(vga->dev, "transfer timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण

		cnt = zx_पढ़ोl(vga->mmio + VGA_RXF_STATUS);
		cnt = (cnt & VGA_RXF_COUNT_MASK) >> VGA_RXF_COUNT_SHIFT;
		/* FIFO status may report more data than we need to पढ़ो */
		cnt = min_t(u32, len, cnt);

		क्रम (i = 0; i < cnt; i++)
			*buf++ = zx_पढ़ोl(vga->mmio + VGA_DATA);

		len -= cnt;
		offset += cnt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zx_vga_i2c_ग_लिखो(काष्ठा zx_vga *vga, काष्ठा i2c_msg *msg)
अणु
	/*
	 * The DDC I2C adapter is only क्रम पढ़ोing EDID data, so we assume
	 * that the ग_लिखो to this adapter must be the EDID data offset.
	 */
	अगर ((msg->len != 1) || ((msg->addr != DDC_ADDR)))
		वापस -EINVAL;

	/* Hardware will take care of the slave address shअगरting */
	zx_ग_लिखोl(vga->mmio + VGA_DEVICE_ADDR, msg->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक zx_vga_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			   पूर्णांक num)
अणु
	काष्ठा zx_vga *vga = i2c_get_adapdata(adap);
	काष्ठा zx_vga_i2c *ddc = vga->ddc;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&ddc->lock);

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD)
			ret = zx_vga_i2c_पढ़ो(vga, &msgs[i]);
		अन्यथा
			ret = zx_vga_i2c_ग_लिखो(vga, &msgs[i]);

		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

	mutex_unlock(&ddc->lock);

	वापस ret;
पूर्ण

अटल u32 zx_vga_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm zx_vga_algorithm = अणु
	.master_xfer	= zx_vga_i2c_xfer,
	.functionality	= zx_vga_i2c_func,
पूर्ण;

अटल पूर्णांक zx_vga_ddc_रेजिस्टर(काष्ठा zx_vga *vga)
अणु
	काष्ठा device *dev = vga->dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा zx_vga_i2c *ddc;
	पूर्णांक ret;

	ddc = devm_kzalloc(dev, माप(*ddc), GFP_KERNEL);
	अगर (!ddc)
		वापस -ENOMEM;

	vga->ddc = ddc;
	mutex_init(&ddc->lock);

	adap = &ddc->adap;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DDC;
	adap->dev.parent = dev;
	adap->algo = &zx_vga_algorithm;
	snम_लिखो(adap->name, माप(adap->name), "zx vga i2c");

	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to add I2C adapter: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_adapdata(adap, vga);

	वापस 0;
पूर्ण

अटल irqवापस_t zx_vga_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zx_vga *vga = dev_id;

	drm_helper_hpd_irq_event(vga->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t zx_vga_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zx_vga *vga = dev_id;
	u32 status;

	status = zx_पढ़ोl(vga->mmio + VGA_I2C_STATUS);

	/* Clear पूर्णांकerrupt status */
	zx_ग_लिखोl_mask(vga->mmio + VGA_I2C_STATUS, VGA_CLEAR_IRQ,
		       VGA_CLEAR_IRQ);

	अगर (status & VGA_DEVICE_CONNECTED) अणु
		/*
		 * Since VGA_DETECT_SEL bits need to be reset क्रम चयनing DDC
		 * bus from device detection to EDID पढ़ो, rather than setting
		 * up HAS_DEVICE bit here, we need to करो that in .get_modes
		 * hook क्रम unplug detecting after EDID पढ़ो succeeds.
		 */
		vga->connected = true;
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर (status & VGA_DEVICE_DISCONNECTED) अणु
		zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_SEL,
			  VGA_DETECT_SEL_NO_DEVICE);
		vga->connected = false;
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर (status & VGA_TRANS_DONE) अणु
		complete(&vga->complete);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम zx_vga_hw_init(काष्ठा zx_vga *vga)
अणु
	अचिन्हित दीर्घ ref = clk_get_rate(vga->i2c_wclk);
	पूर्णांक भाग;

	/*
	 * Set up I2C fast speed भागider per क्रमmula below to get 400kHz.
	 *   scl = ref / ((भाग + 1) * 4)
	 */
	भाग = DIV_ROUND_UP(ref / 1000, 400 * 4) - 1;
	zx_ग_लिखोl(vga->mmio + VGA_CLK_DIV_FS, भाग);

	/* Set up device detection */
	zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_PARA, 0x80);
	zx_ग_लिखोl(vga->mmio + VGA_AUTO_DETECT_SEL, VGA_DETECT_SEL_NO_DEVICE);

	/*
	 * We need to poke monitor via DDC bus to get connection irq
	 * start working.
	 */
	zx_ग_लिखोl(vga->mmio + VGA_DEVICE_ADDR, DDC_ADDR);
	zx_ग_लिखोl_mask(vga->mmio + VGA_CMD_CFG, VGA_CMD_TRANS, VGA_CMD_TRANS);
पूर्ण

अटल पूर्णांक zx_vga_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा resource *res;
	काष्ठा zx_vga *vga;
	पूर्णांक irq;
	पूर्णांक ret;

	vga = devm_kzalloc(dev, माप(*vga), GFP_KERNEL);
	अगर (!vga)
		वापस -ENOMEM;

	vga->dev = dev;
	dev_set_drvdata(dev, vga);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vga->mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vga->mmio))
		वापस PTR_ERR(vga->mmio);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	vga->i2c_wclk = devm_clk_get(dev, "i2c_wclk");
	अगर (IS_ERR(vga->i2c_wclk)) अणु
		ret = PTR_ERR(vga->i2c_wclk);
		DRM_DEV_ERROR(dev, "failed to get i2c_wclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_vga_pwrctrl_init(vga);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init power control: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_vga_ddc_रेजिस्टर(vga);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register ddc: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_vga_रेजिस्टर(drm, vga);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register vga: %d\n", ret);
		वापस ret;
	पूर्ण

	init_completion(&vga->complete);

	ret = devm_request_thपढ़ोed_irq(dev, irq, zx_vga_irq_handler,
					zx_vga_irq_thपढ़ो, IRQF_SHARED,
					dev_name(dev), vga);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to request threaded irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(vga->i2c_wclk);
	अगर (ret)
		वापस ret;

	zx_vga_hw_init(vga);

	वापस 0;
पूर्ण

अटल व्योम zx_vga_unbind(काष्ठा device *dev, काष्ठा device *master,
			  व्योम *data)
अणु
	काष्ठा zx_vga *vga = dev_get_drvdata(dev);

	clk_disable_unprepare(vga->i2c_wclk);
पूर्ण

अटल स्थिर काष्ठा component_ops zx_vga_component_ops = अणु
	.bind = zx_vga_bind,
	.unbind = zx_vga_unbind,
पूर्ण;

अटल पूर्णांक zx_vga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &zx_vga_component_ops);
पूर्ण

अटल पूर्णांक zx_vga_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &zx_vga_component_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zx_vga_of_match[] = अणु
	अणु .compatible = "zte,zx296718-vga", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zx_vga_of_match);

काष्ठा platक्रमm_driver zx_vga_driver = अणु
	.probe = zx_vga_probe,
	.हटाओ = zx_vga_हटाओ,
	.driver	= अणु
		.name = "zx-vga",
		.of_match_table	= zx_vga_of_match,
	पूर्ण,
पूर्ण;
